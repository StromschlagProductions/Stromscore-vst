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
