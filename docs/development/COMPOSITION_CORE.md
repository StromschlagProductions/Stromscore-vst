# Gemeinsamer Kompositionskern – erster synthetischer Prototyp

Entwicklungsstand 2.2, noch keine Veröffentlichung. Der gemeinsame neue Kern soll den
freien Modus und die späteren Künstlerprofile versorgen. Keine Rückwärtskompatibilität,
kein eingefrorener 2.1-Kern und keine dauerhafte Kompatibilitätsschicht sind vorgesehen.
Die Künstlerforschung ist noch nicht vollständig; dieser Schritt enthält keine Künstlerprofile.

## Umfang dieses Schritts

`Source/CompositionCore.h` ist JUCE-unabhängig und verwendet ausschließlich den vorhandenen
begrenzten Voicing-Solver aus `VoiceLeading.h`, nicht den alten `Generator`.

Ein synthetischer Szenenauftrag enthält zwei verbindliche Harmonien mit je bis zu fünf
unterschiedlichen Pflichttonklassen und einen unabhängigen Pedalbass. Jede Harmonie dauert
zwei 4/4-Takte. Die vier Takte sind die Grenze dieses Prüffalls, kein allgemeines Formmodell.

Ablauf: Request -> Validierung -> Voicing -> fester Plan -> MIDI-Ereignisse.
Tonumfang, Kanalwahl und Mute sind verbindlich. Intensität steuert hier ausschließlich
Velocity; auch leise bleiben sämtliche geforderten Akkordfarben vorhanden. Eine unmögliche
Pflichttonklasse führt zu `requiredToneUnavailable` und einem leeren, ungültigen Plan.
Es gibt in diesem Schritt keinen stillen musikalischen Ersatzweg. Unterstützt sind hier
8–384 kHz und 10–400 BPM; nicht endliche Werte und ungültige Bereiche werden abgelehnt.

Der Plan speichert Rolle, absolute Tonhöhe, Kanal, Velocity und Anfang/Ende in szenenlokalen
Samples. Der Compiler übersetzt die musikalischen Viertelpositionen bei festem Tempo und
fester Samplerate. Das ist eine erste Renderrepräsentation, noch nicht das allgemeine Modell
für Form, Harmonieabsicht, Motividentität und Spielabsichten.

Konfigurations-ID und Revision sind explizit. `randomKey` stellt eine zustandslose,
domänentrennte Schlüsselableitung bereit. Der synthetische Fall trifft bewusst noch keine
Zufallsentscheidungen; die Schlüsselableitung ist noch keine Motiv- oder Variationsengine.

## Aufrufvertrag

1. `Compiler::compile(request)` außerhalb des Audiocallbacks aufrufen und Fehler prüfen.
2. Gültigen Plan mit `Renderer::setNextScene` vormerken.
3. `start()` beginnt eine neue Szene und übernimmt den vorgemerkten Plan.
4. `process(position, samples, discontinuity)` erhält eine halboffene szenenlokale
   Samplezeitspanne. Ereignis-Offsets sind relativ zu diesem Aufruf.
5. Alle zurückgegebenen Ereignisse ausgeben, auch von `start()` und `stop()`.

Alle Aufrufe an einem Renderer erfolgen im selben Thread. Sichere Veröffentlichung von
Plänen zwischen UI/Planung und Audiothread ist Aufgabe eines späteren Processor-Adapters.
Ein Planwechsel ohne neuen Szenenstart bleibt vorgemerkt. Ein ungültiger neuer Plan ersetzt
keinen zuvor gültig vorgemerkten Plan.

Positionssprünge beenden alte physische Noten und rekonstruieren die am Ziel gehaltenen
Töne aus dem aktiven Plan. Ein Loop verwendet denselben Plan und damit denselben Ausschnitt.
`discontinuity=true` kennzeichnet einen expliziten Sprung auch dann, wenn er numerisch an
die erwartete Position führt. Vorgemerkte Konfigurationen werden bei Seek/Loop nicht aktiv.
Negative Positionen, ungültige Blocklängen und Zeitüberlauf beenden gehaltene Noten.

Bei einer Blockgrenze genau am Szenenende liegen die dortigen Note-offs im nächsten Block.
Beendet der Aufrufer die Verarbeitung dort, muss er `stop()` ausgeben. Stoppen ist idempotent.
Es wird keine unbekannte Live-Historie rekonstruiert. Tempoänderungen, DAW-Taktbezug und
DAW-Loop-Erkennung sind noch nicht angebunden.

## Notenbesitz und Grenzen

Der Renderer aggregiert aktive Ansprüche nach Kanal und Tonhöhe vor der MIDI-Ausgabe.
Gemeinsame Akkordtöne werden gehalten, und das Ende eines Flächenanspruchs beendet keinen
weiterhin vom Pedalbass beanspruchten Ton. Bei einer Diskontinuität wird hingegen ausdrücklich
neu angeschlagen. Notenenden werden vor neuen Anschlägen am selben Zeitpunkt ausgegeben.

Maximal elf Notenspannen: zweimal fünf Flächentöne plus ein Pedal. Ein Block untersucht
höchstens 22 verschiedene Spanngrenzen, unabhängig von seiner Länge. Der Ereignispuffer
fasst 44 Ereignisse: pro Spanne höchstens Anfang/Ende sowie Reserve für alte Note-offs und
Rekonstruktion. Die private Planrepräsentation ist nur über den validierenden Compiler befüllbar.
Keine Heap-Allokation, Dateioperation, Parser oder Locks im Renderer.

## Tests und nächste Schritte

`CompositionCoreTests` ist in CTest sowie im Linux-Processor-Build registriert. Der reguläre
Windows-Standardbuild baut das Testziel ebenfalls. Prüfungen umfassen:

- gleiche zeitgestempelte Ausgabe bei Blöcken von einem Sample bis über Szenenlänge;
- vollständige Pflichttonklassen, leise Septimen, Transpositionen und Register;
- gemeinsame Töne und Notenbesitz auf geteiltem Kanal;
- Validierungsfehler und keine abspielbaren Teilpläne;
- kanonische Seek-Rekonstruktion, Loop, vorgemerkter Wechsel, Stop und Zeitüberlauf;
- Allokationsfreiheit und ausgeglichene physische Noten;
- verschiedene Tempi/Sampleraten sowie getrennte Zufallsschlüssel.

Lokal: `cmake -S . -B build-core -DENGINE_ONLY=ON`, danach bauen und CTest ausführen.
Sanitizer gemäß dem bestehenden Linux-Workflow verwenden.

## Erste Integration in den freien Modus

Der freie Modus verwendet jetzt `composition::planHarmony` für die zyklische Flächen-
und Bassplanung. Der vollständige Pfad lautet:

APVTS/Controller -> `Generator` (Wendung und Parameter) -> `HarmonicRequest` ->
`HarmonicPlan` -> Flächen-/Bassmuster -> Notenbesitzverwaltung -> `EventList` ->
`PluginProcessor::emit` -> Host-MIDI. Vorhören und MIDI-Dateiexport verwenden ebenfalls
`Generator` und damit denselben neuen Planer.

Der Adapter in `prepareVoicingPlan` übersetzt die vorhandenen Wendungen, eigene Akkorde,
Follow, Durchgangsdominanten, Register, Oktaven und Tonumfänge in maximal 16 vorbereitete
Harmonieplätze. Er liefert ausdrücklich die gewünschte Dominantauflösung und geschützte
Linien; der Kern kennt keine Genre- oder Wendungsindizes. Die vorhandene Drahtseil-Linie
bleibt als `preservePad` geschützt. Der eigentliche zyklische Planungsalgorithmus und seine
Ergebnisdaten liegen ausschließlich im neuen Kern; die alte Planungsimplementierung ist
entfernt. Der synthetische Compiler verwendet denselben Planungseinstieg linear.

Die Planung arbeitet vor dem Oktavoffset. Im freien Modus bleibt die bestehende Behandlung
sehr enger Tonumfänge aktiv: vorbereitete Anker können gefaltet werden; fehlende ursprüngliche
Tonklassen werden im Plan als `unavailable` mitgeführt. Das ist ausdrücklich eine andere
Anforderung als die strikte Ablehnung unmöglicher Pflichtnoten im synthetischen Prüffall.
Musikalische Prioritäten für spätere Profile sind damit noch nicht festgelegt.

Der zeitunabhängige Plan ist eine Funktion seiner Eingaben und wird im Generator gecacht.
Seek/Loop setzen den Cache zurück und bauen ihn aus aktuellen Einstellungen neu auf;
die vorhandene Notenverwaltung beendet alte Ansprüche und rekonstruiert gehaltene Töne.
Szenenstart/-ende, Wurf, Fahrt und MIDI-Zeitsteuerung bleiben in diesem Schritt im Generator.
Bei unverändertem Szenenbezug und gleichen Einstellungen liefern Loop-Wiederholungen
identische Harmoniepläne. Unbekannte Live-Historie wird nicht nachgebildet. Die bisherigen
Regeln für Loop vor Szenenbeginn und manuelles Szenenende bleiben bestehen; ein neuer
allgemeiner Konfigurationswechsel im Plugin ist noch nicht eingeführt.

Keine separate Legacy-Engine und kein alternativer Laufzeitmodus wurden hinzugefügt.
Die noch nicht herausgelösten Teile des Generators sind der nächste Umbaugegenstand.
Es gibt keine neue GUI und keine neuen Künstlerprofile. `VERSION` bleibt für diesen
Entwicklungsschritt auf 2.2; Veröffentlichung und Push sind nicht beauftragt.

## Zusätzliche Integrationsprüfungen

- Alle 84 Wendungen an ihren XYZ-Ankern: gemeinsamer Plan aufgebaut, physische MIDI-Noten
  ausgeglichen, Ereignisgleichheit bei 512 und 8192 Samples über acht Takte hinaus.
- Eigene Harmonik auf gemeinsamem Kanal: Seek/Loop, geänderte Harmonie/Register,
  Stop/Start mit neuem Szenenwurf, keine doppelt offenen oder hängenden Noten.
- Processor-Pfad mit vorhandenen Parametern: eigene Folge, Fläche/Bass, Tonumfänge,
  Kanalteilung, Seek/Loop und Stopp; Allokationsprüfung im vorbereiteten Audioblock.
- Kernvalidierung für begrenzte Plätze, negative oktavrelative Lagen, deaktivierte Plätze,
  geschützte Linien und weitergereichte Farbdiagnose.
- Bestehende Engine-, Voicing-, Processor-, Export-, GUI- und Releaseprüfungen bleiben aktiv.

## Nächster kleiner Schritt

Als Nächstes die Harmonieabsicht (Tonmaterial, Bassfunktion und zeitliche Plätze) aus den
Wendungstabellen in ein eigenes musikalisches Modell überführen. Damit kann auch die
Ankerbildung aus `Generator` herausgelöst werden. Noch nicht in den gemeinsamen Kern
umgestellt sind Wendungsauswahl/XYZ-Reaktion, Form, Motive/Gedächtnis, Rhythmus und
Ebenenkoordination sowie allgemeine Artikulation/CC-Planung. Die vorhandenen Funktionen
sind weiter nutzbar; ihre innere Modularisierung ist noch nicht abgeschlossen.

Technische Tests ersetzen keine Hörabnahme mit Zielinstrumenten.

## Lokal geprüfter Integrationsstand (23. November 2026)

Linux, GCC 14.2, JUCE 8.0.9:

- Release-Testbuild unter Xvfb: CTest 4/4 (CompositionCore, Engine, VoiceLeading, Processor).
- ASan/UBSan-Enginebuild: CTest 3/3, keine gemeldeten Speicher-/Undefined-Behavior-Fehler.
- Python-Releaseprüfer: 7/7.
- `git diff --check`: erfolgreich.

Der vollständige Processor-Lauf enthält auch die vorhandenen Live-/Export-, State-, CC-,
GUI- und Allokationsprüfungen. Windows, pluginval und eine musikalische Hörabnahme wurden
in diesem Integrationsschritt nicht ausgeführt. Es wurde kein Release erstellt.

## Zweiter Integrationsschritt: Absicht, Akkordzeit und Anker

`ChordIntent` beschreibt Tonmaterial als Intervalle, unabhängigen Bassbezug,
Register-/Voicingabsicht und eine geschützte Linie ohne Kenntnis von Katalogindizes.
`buildAnchor` übernimmt nun Spreizung, Zusatzoktave und Tonumfangsfaltung samt
Diagnose fehlender Tonklassen. `canonicalPad` im Generator ist entfernt. Der Generator
übersetzt die vorhandenen Akkordqualitäten, Follow-Einstellungen und Variationsentscheidungen
in diese Absicht; neue Künstlerregeln wurden nicht eingeführt.

`ChordTimeline` beschreibt bis zu acht Akkordplätze mit individuellen Dauern, Anfang,
Ende, Einstieg an einem Akkordplatz und gehaltenem Akkord. Die Zeitbasis sind ganzzahlige
musikalische Ticks; die bestehende Taktgruppierung bestimmt deren Anzahl je Takt.
`locateChord` wird tatsächlich vom laufenden Generator verwendet und bestimmt die
Akkordgrenzen einschließlich des bis zur Phrasengrenze gehaltenen letzten Akkords.
Die bestehende Auswahl und zeitliche Abspaltung einer Durchgangsdominante verbleiben
im Adapter. Ein neues Übergangsmodell ist damit noch nicht implementiert.

Der neue Pfad gilt für alle 84 Wendungen und eigene Folgen. Ein Profil kann später
anderes Tonmaterial, andere Ankerabsichten und andere Zeitpläne liefern. Die aktuelle
Katalogübersetzung bleibt getrennt von diesen allgemeinen Kerndaten.

Zusätzliche Prüfungen: erwartete breite/enge Anker, leise Farbnoten, geschützte Linie,
fehlende Tonklassen bei engem Umfang sowie nicht gleich lange Plätze und exakte Grenzen
bei unterschiedlichen Taktlängen. Der Processor-Live-/Exportvergleich prüft jetzt eine
1/3/2/2-Taktfolge. Bestehende 84-Anker-, Transport-, Bereichs- und Notenbesitztests bleiben aktiv.

Der nächste sinnvolle Schritt ist, die bisher im Adapter gewählten Übergänge samt
harmonischer Auflösungsabsicht als explizite Übergangsdaten zu modellieren. Neue
musikalische Übergangsverfahren oder Künstlerzuordnungen bleiben gesonderte Aufgaben.

Prüfergebnis dieses zweiten Schritts: Linux/Xvfb CTest 4/4, ASan/UBSan 3/3,
Python-Releaseprüfer 7/7 bestanden. Ein zusätzlicher temporärer A/B-Renderer gegen
Commit 0f5370c erzeugte für 252 Fälle (84 Wendungsanker, Durchgangsakkorde aktiv,
drei Bereichseinstellungen, je acht Takte) identische MIDI-Ereignisprüfsummen.
Dies ist eine begrenzte technische Verhaltensprüfung, keine allgemeine
Kompatibilitätsanforderung oder musikalische Hörabnahme. Windows/pluginval wurden
auch in diesem Schritt nicht ausgeführt.

## Dritter Integrationsschritt: Übergang und Auflösungsabsicht

`TransitionIntent` trennt direkten Wechsel und die bisherige Durchgangsdominante,
Zielgrundton und Annäherungsgrundton. `freeTransition` ist die vorhandene Strategie
(aktivierter Schalter, Intensität ab 0,6, keine gehaltene Harmonie). Sie ist ein
Erzeuger von Absichten; spätere Strategien können dieselben Daten liefern.
`TransitionPlacement` beschreibt das musikalische Zeitfenster in der letzten
Betonungsgruppe eines mindestens einen Takt langen Akkords. Die bisherigen
Schwellen-, Grundton- und Zeitfensterregeln im Generator sind dadurch ersetzt.

`ResolutionIntent` beschreibt die nach unten aufzulösende Septime und die nach oben
aufzulösende Terz als Tonklassen. `dominantResolution` erzeugt diese Absicht für die
bestehende Dominantbewegung zur Quinte darunter. Der Adapter liefert nur Akkordfakten;
der Voicing-Solver übersetzt die Absicht weiterhin in seine vorhandenen weichen Kosten.
MIDI-Erzeugung und Notenbesitz entscheiden nicht über diese harmonische Absicht.

Katalogwahl/Wechselraster, Follow-Vorrang und die melodischen Vorhalte der Gegenstimme
sind nicht neu gestaltet. Es gibt keinen allgemeinen Übergangsgraphen und keine neuen
musikalischen Übergangstechniken. Der Kern kennt weiterhin keine Künstlerzuordnung.

Neue Tests prüfen Schwellwerte, deaktivierte/liegende Harmonik, kurze Akkorde,
Zeitfenster bei verschiedenen Taktlängen und Auflösungsabsichten in allen Tonarten.
Der bestehende Live-/Exportvergleich wird sowohl ohne als auch mit Durchgangsakkorden
bei ungleich langen Akkordplätzen ausgeführt.

Standort: Der produktiv angebundene Kern enthält nun begrenzte harmonische Planung,
Ankerbildung, Akkordzeitdaten sowie die bisherigen Übergangs-/Auflösungsabsichten.
Das ist ein geprüfter harmonischer Teilkern, keine fertige allgemeine Kompositionsengine.
Form, Motivmodell/-gedächtnis, Rhythmus-/Phrasenplanung, Ebenenkoordination und ein
allgemeiner Artikulationsadapter fehlen weiterhin im neuen Kern; bestehende Verfahren
liegen dafür noch im Generator. Der synthetische Renderer ist nicht der vollständige
Renderer des freien Modus.

Eine neue hörbare Fähigkeit muss nicht auf den Abschluss aller Umbauten warten.
Als nächsten ausdrücklich beauftragten Funktionsschritt bietet sich eine kleine,
deterministische Motivwiederaufnahme nach einer definierten Pause an. Dafür wären
minimale Motividentität, begrenztes Gedächtnis und die Anbindung an die Gegenstimme
Bestandteil genau dieses Funktionsschritts. Eine vollständige Formgrammatik oder die
Künstlerforschung sind dafür keine Voraussetzung. Dies ist ein Vorschlag, noch kein
Implementierungsauftrag; dieser Commit implementiert keine Motivneuerung.

Prüfergebnis des dritten Schritts: finaler Linux/Xvfb-CTest 4/4, ASan/UBSan 3/3,
Python-Releaseprüfer 7/7 bestanden. Seek/Loop wird im eigenen Harmonieablauf ohne und
mit Durchgangsdominante sowie am Zeitpunkt innerhalb des Durchgangs geprüft.
252 temporäre A/B-Renderfälle gegen 4dfb4c3 liefern identische Ereignisprüfsummen.
Windows/pluginval und Hörabnahme wurden nicht ausgeführt. Keine Veröffentlichung.

## Erste neue Fähigkeit: aufgezeichnete Motivwiederkehr

`RememberedMotif` speichert genau ein tatsächlich ausgegebenes Motiv je Szene,
maximal fünf Noten. Daten: Anfang relativ zum Phrasenbeginn, Notenlänge, Intervall
zum ersten physischen MIDI-Ton und ursprüngliche Anschlagabsicht. Eine Inhaltskennung
wird aus Rhythmus, Dauern und Intervallen gebildet. Sie ist kein Zufallsschlüssel.
Erst mindestens zwei erfasste Anschläge ergeben ein abgeschlossenes Motiv.
Die Beobachtung erfolgt nach der Notenausgabe und berücksichtigt nur wirklich erzeugte
Note-ons des Gegenstimmenausgangs, einschließlich dessen Bereichs-/Oktavabbildung.

Im freien **Score-Modus** verwendet der vorhandene Motivschalter jetzt dieses Verfahren.
Die Einführung liegt in den ersten zwei Takten einer Phrase, sobald die Gegenstimme
aktiv ist. Es folgt eine vollständige Phrase ohne Gegenstimmenmotiv und ohne deren
Ersatzlinie. In der übernächsten Phrase kehrt das gespeicherte Motiv zurück; danach
wechseln Zwischenphrase und Wiederkehr. Innerhalb der übrigen Takte bleibt die
Gegenstimme bei aktiviertem Motiv ebenfalls frei. Das ersetzt die bisherige fortlaufende
A/A'/B/A''-Neuberechnung. Pop-Rock behält vorerst seine Hook-Ausgabe; die Gedächtnisdaten
im gemeinsamen Kern sind nicht genrespezifisch.

Die Wiederkehr erhält den aufgezeichneten Rhythmus und die Intervallziele. Diese werden
auf die aktuelle Akkordtonleiter und den zulässigen Bereich abgebildet. Sehr enge Bereiche
können Intervalle zusammenfallen lassen; die rhythmische Identität bleibt erhalten.
Weder neue Künstlerregeln noch eine Formgrammatik oder ein neuer Regler wurden ergänzt.

Transportvertrag: Ein vollständiges Szenengedächtnis bleibt bei Seek/Loop erhalten und
wird nicht aus dem Wurf neu aufgebaut. Die Einführung kann beim Loop ebenfalls aus diesem
Speicher wiedergegeben werden. Unvollständige Aufzeichnungen werden bei Sprüngen verworfen.
Stop/Start und ein neuer Szenenbeginn leeren das Gedächtnis. Ein frischer Seek ohne
vorherige Aufführung kann keine historische Wiederkehr liefern: er darf eine neue
Einführung erzeugen. Gleichheit gilt bei gleichem Szenengedächtnis und Steuerungsverlauf;
ein unbekannter vergangener Verlauf wird nicht rekonstruiert. Ein frischer MIDI-Export
spielt die Szene vollständig von Beginn und erfasst seine Einführung genauso wie live.

Tests vergleichen tatsächliche MIDI-Anschläge der Einführung und der Wiederkehr in
statischer Harmonik, prüfen eine vollständig anschlagfreie Zwischenphrase, die gespeicherten
Intervalle gegen die ausgegebenen Noten, Identität trotz Variationsänderung, Seek/Loop,
Szenenneustart und Blockgrößen. Der Live-/Exportvergleich enthält zusätzlich 24 Takte mit
aktiver Gegenstimme und Wiederkehr. MIDI-Nachweise ersetzen keine subjektive Hörabnahme
mit geeigneten Instrumenten.

Nächster möglicher Schritt: eine begrenzte, explizite Wiederkehrvariation, die Motividentität
und Rhythmusbezug erhält. Diese ist noch nicht implementiert oder beauftragt.

Vor einer erfolgreichen Einführung bleibt außerhalb ihres Zeitfensters die normale
Gegenstimme verfügbar. So wird ein später Eintritt während des Aufbaus nicht stumm;
die nächste passende Phrase kann das erste Motiv einführen. Bei sehr kurzen eigenen
Phrasen wird die Einführung spätestens beim Abschnittswechsel abgeschlossen.

Prüfstand der Motivwiederkehr: Linux/Xvfb CTest 4/4, ASan/UBSan 3/3 und
Python-Releaseprüfer 7/7 bestanden. Die Motivprüfung umfasst auch eintaktige eigene
Phrasen und Ereignisgleichheit bei 512/8192 Samples. Im Processor wurde der
Live-/Exportvergleich zusätzlich über 24 Takte mit aktiver Gegenstimme bestanden.
README und integrierte Hilfe beschreiben das neue Verhalten des vorhandenen Schalters.
Windows/pluginval und subjektive Hörabnahme wurden nicht ausgeführt.

## Kontrollierte rhythmische Wiederkehrvariation

Die erste Wiederkehr bleibt unverändert. Bei der zweiten wird die längste gespeicherte
Note halbiert (mindestens ein Tick, bei Gleichstand die früheste). Danach wechseln
unveränderte und variierte Wiederkehr. Einsatzzeiten, Intervallziele, Speicherinhalt und
Motivkennung bleiben gleich. Die artikulierte Variante begrenzt zusätzlich alle Dauern
auf den nächsten Einsatz bzw. das Fensterende und hat daher keine Legatoüberlappungen.
Die unveränderte Wiederkehr behält das vorhandene Legato. Bei ausschließlich eintickigen
Noten ist keine weitere Verkürzung möglich; dann bleibt die Figur unverändert.
Die Wahl folgt der Abschnittsposition relativ zur tatsächlichen Einführung, keinem
laufenden Zufallszähler. Seek/Loop verwenden daher dieselbe Variante bei gleichem
Szenengedächtnis. Keine zusätzlichen Parameter oder Künstlerprofile.

Kernprüfungen belegen Identität, Unterschied und zulässige Dauern ohne Überschneidung.
Ein MIDI-Test vergleicht Einsatzzeiten, Tonhöhen und tatsächlich ausgegebene Dauern
zwischen erster und zweiter Wiederkehr. Der Live-/Exportvergleich läuft über 40 Takte,
sodass auch die variierte Wiederkehr enthalten ist.

Der 40-Takt-Vergleich deckte zusätzlich eine Abweichung des Offline-Zeitrasters auf.
Der Export verwendet nun einen ganzzahligen Samplezähler statt aufaddierter PPQ-Werte.
Dies verhindert kumulierte Gleitkommadrift über lange Abläufe. Die musikalischen
Vergleichsassertionen wurden beibehalten.

Prüfergebnis: Linux/Xvfb CTest 4/4 einschließlich strengem 40-Takt-Live-/Exportvergleich,
ASan/UBSan 3/3 und Python-Releaseprüfer 7/7 bestanden. Windows/pluginval und eine
subjektive Hörabnahme wurden nicht durchgeführt. Kein Push oder Release.

## Erste Frage–Antwort-Koordination

Begrenzter Kontext: Score, Motiv aktiv, explizite Arp-Figur Zelle (ArpCell), Aufbau aus,
beide Ebenen tatsächlich aktiv, 4/4 und mindestens vier Takte je Phrase. Andere
Einstellungen behalten ihre bisherigen Verfahren. Die Funktion erfordert keine neue GUI.

`DialoguePlan` reserviert den Arp in den ersten vier Takten. Die Gegenstimme stellt das
Motiv in den ersten zwei Takten vor. Erst nach diesem Fenster kann der Arp mit den ersten
maximal drei tatsächlich gespeicherten Tönen antworten, im Fenster der folgenden zwei
Takte. Die Gegenstimme bleibt dort durch den Motivplan stumm. Ohne vollständige Aufzeichnung
entsteht keine erfundene Antwort. In den übrigen Takten darf der normale Arp weiterlaufen.
In den bisherigen Zwischenphrasen ohne Frage wird keine Antwort erzeugt.

Rollen-/Fensterentscheidung liegt im Kern; der MIDI-Adapter übernimmt gespeicherte
Einsatzabstände und Intervallziele, passt die Töne an aktuelle Akkordtöne und den Arp-Bereich
an und begrenzt Dauern auf nächsten Einsatz/Fensterende. Ist kein Akkordton im erlaubten
Bereich vorhanden, bleibt die Antwort aus. Die vorhandene Notenbesitzverwaltung schützt
auch geteilte MIDI-Kanäle. Der Speicher bleibt das Gedächtnis der Frage, keine Rückkopplung
der Antwort in die Quelle. Noch keine freie Strategieauswahl oder allgemeine Ebenengrammatik.

Tests prüfen tatsächliche Frage-/Antwort-MIDI-Anschläge, die getrennten Fenster, Tonumfang,
geteilten Kanal, Blockgrößen, Seek/Loop und Szenenneustart. Der 40-Takt-Live-/Exportvergleich
enthält einen zusätzlichen Dialogfall. Subjektive musikalische Hörabnahme bleibt offen.

Prüfergebnis: finaler Linux/Xvfb-CTest 4/4, ASan/UBSan 3/3 und Python-Releaseprüfer
7/7 bestanden. Einschließlich des zusätzlichen Dialogfalls über 40 Takte mit
Live-/Exportgleichheit. Windows/pluginval und Hörabnahme wurden nicht durchgeführt.

## Rollen, Spielweisen, Instrumente und MIDI-Ziele

`MusicalRole` beschreibt zunächst Führung, Begleitung und Antwort. `RoleNeed` enthält
benötigte Spielweise, Tonhöhenverhalten, Bereich, Polyphonie und minimale/maximale
Notendauer in musikalischen Ticks. `PlayingTrack` benennt eine verfügbare Spielmöglichkeit
mit einer opaken ID und expliziten Instrumentenfähigkeiten. `MidiTarget` und die
Bindung im Generator sind davon getrennt. Rollenwahl enthält keine MIDI-Kanalnummer.

Tonhöhenverhalten unterscheidet unbekannt, tonhöhensteuerbar und geräuschhaft.
Unabhängig davon unterscheidet die Notenadressierung freie Tonhöhen und feste Trigger.
Ein tonales Einzelsample kann damit ebenfalls ein fester Trigger sein; geräuschhaft ist
nicht gleichbedeutend mit atonaler Musik. Unbekannte Fähigkeiten werden nicht als
universell geeignet behandelt. Lang/kurz sind getrennte Spielweisen mit expliziten
Fähigkeitsbits; ein Instrument mit ausschließlich kurzer Spielweise wird nicht für
gehaltene Figuren ausgewählt. Fehlende Dauern, Polyphonie oder Bereichseignung führen
zu keiner Zuweisung statt zu einem stillen Ersatzpatch.

`assignDialogue` wählt unterschiedliche geeignete Spur-IDs für Frage und Antwort.
`DialoguePlan` reserviert nun eine Antwortspur statt eines Arp-Ausgangs und referenziert
über `sourceMotif` die inhaltliche Motivkennung. Das Motivgedächtnis enthält weiterhin
keine Ausgänge/Kanäle; sein Speicherort bleibt vorerst der Generator, noch kein
mehrstimmiger Motivkatalog. Der aktuelle Adapter bindet die gewählten IDs an die bisherigen
Gegenstimmen-/Arp-Ausgänge und damit an die vorhandenen MIDI-Kanalparameter.
Keine neue frei konfigurierbare Spurverwaltung oder Umbelegung im UI wurde eingeführt.

Wichtig: Ohne Patch-Konfiguration beschreibt der Adapter nur die bisherigen Annahmen
seiner Erzeuger: tonhöhensteuerbare Gegenstimme mit Legatoüberlappung und tonhöhensteuerbare
kurze Antwort. Er kann die tatsächlichen Fähigkeiten einer externen Library nicht erkennen.
Die vorhandenen Lang-/Kurz-Ausgänge von Fläche/Bass bleiben unverändert. Das Modell erlaubt,
sie später als getrennte Spielmöglichkeiten mit unterschiedlichen Instrumentenfähigkeiten
zu registrieren; sie werden in diesem kleinen Schritt nicht zu Dialogkandidaten gemacht.
Der feste Stich bleibt ebenfalls außerhalb der melodischen Kandidaten.

Tests: opake/neugeordnete IDs ohne MIDI-Abhängigkeit, ungeeignete Tonhöhen-/Triggerarten,
Polyphonie, Bereiche, Dauern und Artikulationen. Die vorhandenen MIDI-Dialog-, Transport-
und Live-/Exporttests bleiben aktiv. Die sechs künftigen Bediengruppen und neun Standardziele
sind beschlossen, werden hier aber weder im UI noch als feste musikalische Grenze umgesetzt.

Später ergänzen: vom Nutzer beziehungsweise Patchadapter deklarierte Fähigkeiten,
mehrere Spielmöglichkeiten pro Instrument und bedarfsgerechte Registrierung der bisherigen
Lang-/Kurz-Ziele. Keyswitches, Library-spezifisches Legato, Releasezeiten und Controller-
Semantik sind nicht implementiert. Nächster kleiner Schritt: die bestehenden Ausgänge
in einem einheitlichen, validierten Fähigkeitskatalog des Adapters beschreiben.

Prüfergebnis: finaler Linux/Xvfb-CTest 4/4 und ASan/UBSan 3/3 bestanden;
Python-Releaseprüfer 7/7 bestanden. Einschließlich bestehender Dialog-/Bereichs-/Kanalteilungs-,
Seek-/Loop-/Szenenstart- und Live-/Exportprüfungen. Windows/pluginval und subjektive
Hörabnahme wurden nicht durchgeführt. Kein Push und kein Release.

## Einheitlicher Katalog der acht bisherigen Ausgabegruppen

`outputCatalog(Settings)` ist nun die gemeinsame Quelle der Standardfähigkeiten und
MIDI-Bindungen. Der Dialogadapter pflegt keine eigenen Fähigkeiten mehr. Jedes Ziel
hat eindeutige Ausgabe-/Spur-ID, Standardverwendung, Spielweise, Tonumfang, Polyphonie,
Tick-Dauerbereich, Rollenfreigaben und Verfügbarkeit. `validOutputs` prüft Vollständigkeit,
Eindeutigkeit, Kanäle, Bereiche, Dauern und Triggernoten; Kanalteilung ist ausdrücklich erlaubt.
Alle Einträge sind als Generatorannahme markiert, `externalPatchKnown` ist immer false.

| Ziel | Standardverwendung | Spielweise | angenommene MIDI-Polyphonie | maximale Gate-Dauer (Ticks) |
|---|---|---|---:|---:|
| Fläche lang | gehaltener Harmoniesatz | gehalten | 6 | 2^24 |
| Fläche kurz | Akkordimpulse und Riss | kurz | 9 einschließlich Zusatzstößen | 3 |
| Bass lang | Fundament, Pedal | gehalten | 1 | 2^24 |
| Bass kurz | rhythmische Bassfiguren | kurz | 1 | 4 |
| Arp | Arpeggio, Figur, Dialogantwort | kurz | 1 | 32 |
| Tupfer | Farbeinwurf/Reibung | kurz | 4 als konservatives Überlappungsbudget | 3 |
| Stich | Akzentschlag | kurz | 1 | 2 |
| Gegenstimme | Linie, Motiv, Frage | gehalten | 2 einschließlich Legato | 2^24 |

Minimale Gate-Dauer jeweils ein Tick. Die großen Lang-Dauergrenzen sind konservative
Modellbudgets für die gegenwärtig unterstützten langen Abläufe, keine Messung einer Library.
Diese Angaben beschreiben die MIDI-Anforderungen des internen Erzeugers, nicht Klangdauer,
Release, realistisches Instrumentenregister oder tatsächliche Patch-Polyphonie.

Tonhöhen werden standardmäßig als steuerbar vorausgesetzt. Bei festem Stich gilt dagegen:
feste Notenadressierung, eingestellte Triggernote als Bereich, Tonhöhenverhalten unbekannt.
Ein fester Trigger beweist weder einen geräuschhaften noch einen gestimmten Sampleklang.
Die tatsächliche Stichausgabe verwendet dieselbe Adressierungsfunktion des Katalogmodells;
Harmonie, Oktave und musikalische Bereichsfaltung verändern die feste Taste nicht.
Ohne festen Stich bleiben dessen bisherige harmonisch abgeleitete Noten erhalten.

Tonumfänge kommen aus den vorhandenen Bereichseinstellungen, sonst MIDI 0–127.
Lang und kurz besitzen getrennte Fähigkeitseinträge und MIDI-Ziele, auch wenn sie bisher
noch dieselbe Bereichseinstellung der Bediengruppe verwenden. Unterschiedliche Patch-
Fähigkeiten sind dadurch darstellbar, ohne im jetzigen UI zusätzliche Angaben einzuführen.
`available` bedeutet durch Mute/Solo freigegeben; Szene, Intensität und zeitliche Rollenfenster
bleiben zusätzliche musikalische Bedingungen. Ein globales Ressourcenbudget eines gemeinsam
benutzten externen Instruments ist damit noch nicht modelliert.

Tests prüfen alle acht Registrierungen, doppelte Ziel-/Spur-IDs, Lang/Kurz-Eignung,
Mute/Solo, feste Trigger trotz Oktav-/Bereichseinstellungen und die Ablehnung als Melodie.
Bestehende physische MIDI-/Trigger-, Transport- und Live-/Exportprüfungen bleiben aktiv.

Danach ist eine eigenständige Hauptmelodie als nächster begrenzter Auftrag sinnvoll:
zusätzliche Spielspur und neuntes Standardziel auf Basis des gemeinsamen Modells, mit
zunächst nur einem vorhandenen Motivverfahren. Der Katalog allein komponiert noch keine
Hauptmelodie; deren Phrasierung und Zusammenspiel mit dem Dialog benötigen eigene Regeln
und Tests. Eine vollständige Orchestrierungs- oder Artikulationsengine ist dafür keine
Voraussetzung. In diesem Schritt wurde diese Spur nicht ergänzt.

Prüfergebnis: Linux/Xvfb CTest 4/4, ASan/UBSan 3/3 und Python-Releaseprüfer 7/7 bestanden.
252 zusätzliche temporäre Vergleichsrenderings gegen 6e8ddd2 ergeben identische
MIDI-Ereignisprüfsummen. Windows/pluginval und subjektive Hörabnahme wurden nicht ausgeführt.
Keine neue Melodiespur, GUI, Patch-Erkennung oder Artikulationsengine ergänzt.

## Optionale eigenständige Melodiespielspur mit Underscoring-Priorität

Neuntes Standardziel `OutMelody`, eigener Kanal (Vorgabe 9), eigene sechste Bediengruppe,
Mute/Solo, Intensitätsversatz, Oktave und separater Bereich (Vorgabe MIDI 60–84).
`melodie` ist standardmäßig aus und wird im bestehenden Parameter-/State-System gespeichert.
Der Score arbeitet dann weiterhin mit den bisherigen acht Zielen. Pop/Rock ignoriert die
neue Vordergrundaktivierung musikalisch. Keine Künstlerprofile oder allgemeine Orchestrierung.

Der Kern unterscheidet mit `ForegroundPlan` ausdrücklich angeforderten Vordergrund von
Hintergrund. Er prüft eine geeignete Führungsspielmöglichkeit anhand der Rollen-/Fähigkeitsdaten;
die konkrete Bindung an Ziel 9 erfolgt im freien Adapter. Der Katalog enthält jetzt neun
registrierte Ziele; Melodie ist tonhöhensteuerbar, gehalten, monophon und als reine
Generatorannahme gekennzeichnet. Externe Patch-Fähigkeiten bleiben unbekannt.

Die neue Stimme verwendet exakt das vorhandene Motivverfahren. Seit der unten
beschriebenen Trennung sind Materialkatalog und Verwendungszustände getrennt. `motifStep` und die harmonische Tonleiteranpassung nehmen nun das Ziel als Adapter-
Argument an. Es gibt keinen zweiten unabhängigen Motivgenerator. Einführung (höchstens zwei
Takte), komplette Zwischenphrase, Wiederkehr und rhythmische Variante bleiben erhalten.
Das Material ist über seine Inhaltskennung identifizierbar, unabhängig vom Wiedergabeziel.
Noten der Hauptmelodie überlappen nicht und enden spätestens an der aktuellen Harmoniegrenze.
Ist kein Akkordton im erlaubten Bereich vorhanden, entfällt der Einsatz.

Solange die aktivierte Melodie ihre Vordergrundrolle tatsächlich übernimmt, werden gehaltene
Gegenstimmenansprüche beendet und die Gegenstimme pausiert. Der frühere Gegenstimme–Arp-
Dialog wird bei aktivierter Melodie nicht zusätzlich gestartet; der Arp bleibt normale
Begleitung. Bass und Harmonie werden nicht verdrängt. Auch innerhalb der Vordergrundzuweisung
bleibt die Melodie über ganze Zwischenphrasen still. Sie ist kein dauernder Notenstrom und
kein obligatorisches Zentrum der Musik. Ohne Aktivierung bleiben Bass-/Ostinatomotive und
bisherige Motivfunktionen erreichbar.

Die neue Karte ergänzt nur Aktivierung und vorhandene Ebenen-/Routingbedienung. Das Fenster
wird zur Aufnahme der sechsten Karte breiter, die übrigen Gruppen behalten ihre Namen/Größe.
Der vorhandene VST3-MIDI-Ausgabebus unterstützt bereits 16 Kanäle. Alle relevanten Routing-,
Aktivitäts-, Controller-, Notenbesitz-, State- und Exportpfade durchlaufen nun neun Ziele;
ein zweiter MIDI-Bus ist dafür nicht erforderlich.

Prüfstand: finaler Linux/Xvfb-CTest 4/4, ASan/UBSan 3/3 und Python-Releaseprüfer 7/7.
Die neue Melodie ist als physische MIDI-Ausgabe auf Standardkanal 9 und nach State-Restore
auf Kanal 15 geprüft. Weitere Tests: monophone Notenbilanz, Akkordtonklassen, Register,
Einführung/Wiederkehr, Zwischenpause, Blockgrößen, Seek/Loop/Neustart, ausgeschaltete bzw.
gemutete Melodie ohne Verlust der bisherigen Funktion, Pop/Rock unverändert und 40-Takt-
Live-/Exportvergleich. Inaktive Melodie erzeugt keine zusätzliche leere MIDI-Exportspur;
ein Solo-Schalter der deaktivierten Melodie schaltet die Begleitung nicht stumm.
252 temporäre Vergleichsrenderings ohne Melodie gegen ce0db82 liefern identische
MIDI-Ereignisprüfsummen.

Linux-VST3 (x86-64) und echtes JUCE-Screenshotwerkzeug erfolgreich gebaut. Die gerenderte
Oberfläche zeigt alle sechs Karten einschließlich Aktivierung, Kanal und Bereich der Melodie
vollständig; Bilder liegen nur im temporären Prüfverzeichnis, nicht als Release-Assets.
Der Processor-Ausgabepfad ist geprüft; ein tatsächlicher DAW-/VST3-Hostlauf, Windows,
pluginval und eine subjektive Hörabnahme mit Zielinstrumenten wurden nicht durchgeführt.

Verbleibende Grenzen dieses damaligen Stands: das inzwischen aufgetrennte Motivgedächtnis
(siehe unten), die bisher dokumentierten Grenzen bei unbekannter Seek-/Automationshistorie und die bestehenden GUI-Exportlängen
8/16/32 (intern bis 64 Takte). Der nächste kleine musikalische Schritt könnte eine gezielte
Dialogantwort auf die neue Melodie statt der jetzigen Pause sein. Er ist nicht implementiert.


## Unabhängige Melodie-Phrasierung und Motivwahl

`melodieLegato` und `melodieMotiv` sind eigene automatisierbare Bool-Parameter mit
Vorgabe an; Settings, State und GUI verwenden dieselben Werte. Die alten Schalter
`legato` und `motiv` steuern weiterhin nur die Gegenstimme. Die Aktivierung bleibt separat.
Die Melodie verwendet die gemeinsame harmonische Linienfunktion: Motiv an delegiert
an `motifStep`, Motiv aus bildet Akkordtonlinien ohne Lesen oder Schreiben des Motivspeichers.
Keine zweite Motiv-Engine.

Legato bedeutet im derzeit monophonen Generator-Fähigkeitsmodell aneinandergrenzende
Notengates, keine überlappenden Note-ons oder Bibliotheks-Legatoartikulation. Getrennte
Artikulation kürzt die verfügbare Gatezeit um eine Sechzehntel, soweit mindestens eine
Sechzehntel verbleibt. Aufgezeichnete Pausen, Variationskürzungen, nächste Einsätze und
Akkordgrenzen werden respektiert. Externe Patch-Artikulationen bleiben unbekannt.

Die in bd8aebf dokumentierte Kopplung des gemeinsamen Motivgedächtnisses und
Liniencursors wurde im folgenden Architektur-Schritt beseitigt (siehe unten).

Prüfstand dieses Schritts: Linux/Xvfb CTest 4/4, ASan/UBSan 3/3 und
Python-Releaseprüfer 7/7 bestanden. Neue Tests prüfen getrennte Schalter, Gateunterschiede
bei unveränderten Anschlägen/Tonhöhen, leeres Motivgedächtnis im reinen Linienmodus,
Blockgrößen, Seek/Loop/Neustart, State-Restore, GUI-Bindungen und Live-/Exportgleichheit
auch ohne Motiv und ohne Legato. Linux-VST3 und Screenshotwerkzeug gebaut; echte
GUI-Renderings visuell geprüft. Kein DAW-Hostlauf, Windows/pluginval oder Hörtest.


## Gemeinsames Material, unabhängige Stimmenzustände

`RememberedMotif` beschreibt ausschließlich tatsächlich gespielte Noten: relativer
Einsatz, Dauer, Intervall, Ursprungston und Anschlagstärke. Die Inhaltskennung entsteht
weiterhin aus Intervallen, Einsätzen und Dauern. Einführungszeitpunkt und Wiederkehrphase
sind keine Eigenschaften des Materials mehr. Die gemeinsame Variationsfunktion erzeugt
eine Wiedergabevariante, ohne das Originalmaterial zu verändern.

Der szenenlokale `MotifCatalog` hält höchstens zwei abgeschlossene, unveränderliche Motive
(ein selbst eingeführtes Motiv pro der beiden derzeitigen Stimmen). Keine Heap-Allokation,
Verdrängung oder automatische Materialwahl. Unvollständiges Material wird nicht registriert;
bei voller Kapazität wird eine Veröffentlichung ausdrücklich abgelehnt. Identische Inhalte
dürfen getrennte Referenzen haben; es gibt keine automatische Zusammenlegung/Übernahme.

Jede Stimme besitzt einen `MotifUse`: eigenen Aufnahmeentwurf, optionale Katalogreferenz
und eigenen Einführungszeitpunkt. Wiederkehr und jede zweite variierte Wiederkehr werden
deterministisch aus Szenenphrase und diesem eigenen Zeitpunkt berechnet; es gibt keinen
geteilten veränderlichen Wiederkehrzähler. Der Adapter hält zwei getrennte `VoiceState`s
für Dialog/Gegenstimme und Melodie, einschließlich letztem Linienton und Vorhaltszustand.
Die Zuordnung auf die beiden bestehenden Ausgänge ist allein Aufgabe des Adapters.

Motiv aus umgeht nur die Motivverwendung dieser Stimme. Aufnahmen, Referenzen und Material
der anderen Stimme werden nicht verändert. Bereits vorhandenes eigenes Material bleibt
für späteres Wiedereinschalten erhalten. Die Vordergrundplanung bleibt unverändert: aktive
Melodie pausiert die Gegenstimme; es gibt keine neu aktivierte simultane Doppelmelodie.
Der bestehende Gegenstimme–Arp-Dialog liest ausschließlich den Dialogkontext.

Eine künftige Rollenplanung kann mit `MotifReferencePlan` eine Materialreferenz und einen
eigenen Einführungszeitpunkt ausdrücklich anfordern. `MotifUse::adopt` validiert die
Referenz; mehrere Verwendungen können dasselbe unveränderliche Material referenzieren,
ohne einen Verwendungszustand zu teilen. Dieser Vorbereitungspfad ist im Kern getestet,
aber wird vom freien Adapter nicht aufgerufen. Keine neue Übergabe-, Frage–Antwort- oder
Orchestrierungsfunktion aktiviert. Die spätere Rollenplanung muss weiterhin passende
Spielweisen, Register und Instrumentenfähigkeiten prüfen, bevor sie eine Übergabe rendert.

Szenenneustart leert Katalog und beide Zustände zusammen. Seek/Loop innerhalb einer Szene
behalten abgeschlossene eigene Motive, verwerfen wie bisher unvollständige Aufnahmen und
rekonstruieren die Liniencursor. Die vorhandene Grenze bleibt: ein frischer Einstieg kann
keine niemals gespielte Motivhistorie erfinden; Live-Automation wird im Export nicht
nachträglich rekonstruiert.

Prüfstand: vollständiger Linux/Xvfb-CTest 4/4, ASan/UBSan 3/3 und Python-Releaseprüfer
7/7 bestanden; Linux-VST3 gebaut. Neue Tests: getrennte Einführungs-/Wiederkehr-/
Variationsphasen bei gemeinsamer Materialreferenz, ungültige Referenz, keine implizite
Übernahme, zwei tatsächlich eingeführte Motive beim Vordergrundwechsel, unabhängige
Motivschalter und Liniencursor sowie gemeinsamer Szenenreset und Seek/Loop. Bestehende
Transport-, Register-, Notenbilanz- und Live-/Exporttests bestehen weiter.
Zusätzlich liefern 1008 temporäre 40-Sekunden-Vergleichsrenderings aller bestehenden
Wendungen in drei Registerkonfigurationen und vier statischen Motiv-/Melodie-Kombinationen
identische MIDI-Ereignisprüfsummen gegenüber bd8aebf. Der Vergleich betrifft unveränderte
Einstellungen, nicht die absichtlich entkoppelten Stimmenwechsel. Kein Windows/pluginval,
DAW-Hostlauf oder subjektiver Hörtest.
