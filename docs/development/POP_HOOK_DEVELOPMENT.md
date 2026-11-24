# Flexible Hook-Entwicklung für Pop/Rock

Ausgangspunkt `2566894`, Entwicklungsbranch `develop/composition-core-prototype`.

## Rollen und bewusste Begrenzung

Die neutrale `HookPolicy` unterscheidet zwei musikalische Funktionen. Diese vorläufige
Zuordnung beschreibt die aktuelle Kompositionsstrategie, keine Künstlerzuweisung:

- **Kontinuierlich:** alle generischen Hooks, eigene Folgen standardmäßig sowie die
  Studien 2028 (Tanzflächenlicht), 2031 (Stahlpuls), 2032 (Drahtseil), 2033 (Sequenzmotor).
  Der bisherige `leadHook()` bleibt unverändert zuständig. Es gelten keine Score-Motivpausen.
- **Phrasenbezogen:** 2029 (Gegenlicht), 2030 (Rückspiegel), 2034 (Spiegelpalast),
  2035 (Sonntagmorgen), 2036 (Licht im Fenster). Die erste tatsächlich gespielte Figur
  wird weiterhin aufgenommen; danach übernimmt der gemeinsame Wiederkehrplaner.

`FreeCompositionPolicy::popHooks` enthält Aktivierung, neun Rollenentscheidungen,
eine ausdrücklich optierbare Phrasenrolle für eigene Folgen (`phrasedCustom`, neutral AUS)
und eine reguläre `MotifRecurrencePolicy`. Der Test unter gehaltener eigener Cmaj7-Harmonie
aktiviert diese gemeinsame Datenoption ausdrücklich. Es gibt keine neue GUI und keine
automatische Umdeutung beliebiger eigener Ostinati als melodische Themen.

Neutral, Barry und Herrmann verwenden dieselbe neue Hook-Policy; Score benutzt weiterhin
seine bisherige Policy. Die Instrumente, Artikulationen und MIDI-Ziele bestimmen nicht,
welche musikalische Rolle gewählt wird. Die Hauptmelodie bleibt in Pop/Rock deaktiviert.
Der bisher in Pop nicht ausgewertete Score-Motivschalter wird nicht umgedeutet.

## Gemeinsame Architektur

`MotifCatalog`, getrennte `VoiceState`-/`MotifUse`-Zustände, `deriveMotif()`, `recurrenceSlot()`,
`planRecurrence()`, die harmonische Vorprüfung und `planMotifNote()` werden wiederverwendet.
Es gibt keine eigene Pop-Motivengine. `leadHook()` erfüllt weiterhin die kontinuierliche
Rolle und liefert die reale Einführung, statt als zweite alte Engine parallel mitzuspielen.

Die Aufnahme bleibt unverändert in 960 PPQ gespeichert (`timeScale=240`).
`performanceMaterial()` erzeugt eine temporäre Projektion in Generator-Sechzehntel:
Die bei der Aufnahme gespeicherte Swing-Einstellung dient dazu, die ursprünglichen
Rastereinsätze und Notenenden wiederzugewinnen. Erst die normale Wiedergabe wendet den
aktuellen Swing erneut an. Quellnotizen, Quellidentität, aufgenommene Dauern und Rhythmus
werden nicht überschrieben; Varianten entstehen ausschließlich aus dieser Quelle.
Die gemeinsame Ableitung kann nun auch Originalfiguren mit bis zu acht Noten verarbeiten.

Bei phrasenbezogenen Wiederholungen wird der letzte Gate-Endpunkt auf die ursprüngliche
Figurengrenze begrenzt. Das entfernt einen eventuellen Legatoüberhang in die geplante Pause.
Bei harmonischer Anpassung können benachbarte Töne zusammenfallen; in diesem Fall endet
der erste Ton am erneuten Anschlag, entsprechend den realen MIDI-Notenregeln. Beides
betrifft die Realisierung, nicht das gespeicherte Original.

Die Aufnahme wird vor den musikalischen Schritten aus den bereits ausgegebenen Ereignissen
fortgeschrieben. Ihre Fertigstellung hängt dadurch nicht vom Ende eines Hostblocks ab.
Das war für eine deterministische Umschaltung von Aufnahme auf geplante Wiedergabe nötig.

## Harmonie und ausschließlich Sequenzierung

Die Pop-Policy erlaubt sieben Originalgelegenheiten und eine Sequenzgelegenheit in einer
achtteiligen Folge; die erste Sequenz ist Gelegenheit 6. Rhythmuskürzung, Fragmentierung
und Augmentation werden für Pop in diesem Schritt nicht aktiviert. Mindestpause ist
zunächst zwei Takte; ruhige und bewegtere Abstände verwenden die vorhandenen gemeinsamen
Gelegenheitsregeln. Kontinuierliche Rollen umgehen diese Planung vollständig.

Eine Originalwiederkehr darf durch `adaptChordTones` im gemeinsamen Planer einzelne
Tonhöhen an vorhandene Akkordtöne anpassen. Zuerst werden zulässige Tonklassen während
der jeweiligen Note ermittelt; anschließend wird die gesamte Realisierung innerhalb
des Registers geprüft. Diese Option ist neutral nur für Pop aktiviert. Einsätze bleiben
erhalten, das Original bleibt unverändert. Die exakte Intervallfolge kann sich dabei ändern;
„Original“ bezeichnet hier das Verfahren ohne zusätzliche motivische Transformation,
nicht die Garantie identischer absoluter Tonhöhen bei anderer Harmonie.

Eine Sequenz bleibt dagegen intervallisch streng: die ersten zwei Originaltöne mit ihrem
Einsatzabstand, danach dieselbe Figur sieben Halbtöne höher. Eine gemeinsame Transposition
muss die vollständige Sequenz in die aktuelle Harmonie und den Tonumfang bringen. Kein
Einzelton wird dabei passend gebogen. Ist sie ungeeignet, wird die Originalrealisierung
geprüft; passt auch diese nicht vollständig, bleibt die Gelegenheit still.

Zeitbedarf, erlaubte Notendauern, Mindestpause, Szenenende und Register werden vor der
Ausgabe geprüft. Die bestehende Auto-Arp-Reservierung verwendet dieselbe tatsächlich
geplante Figur. Keine unnötige Reservierung ohne spielbare Figur. Manuelle Arp-Figuren,
Bass und Akzente werden nicht zu einer allgemeinen Orchestrierung zusammengefasst.
Es wird keine neue Pop-Frage–Antwort-Funktion aktiviert.

## Reproduzierbarer 128-Takt-Vergleich

`HookDevelopmentProbe` und `compare_hook_development.py` bauen temporär den tatsächlichen
Ausgangsstand `2566894`. Acht Situationen werden bei 90, 120 und 173 Host-BPM untersucht,
mit und ohne Swing: Pedal- und Tanzostinato, intensive/ruhige/lyrische/synkopierte Hooks,
wechselndes XY und eine gehaltene eigene Harmonie mit expliziter Phrasenrolle.

24 Vorher-/Nachher-Vergleichspaare über jeweils 128 Takte, zusätzlich 48 Vergleiche mit
127/8192 statt 512 Samples. Der ausgeschaltete neue Policy-Bereich muss den Ausgangsstand
vollständig reproduzieren. Die beiden kontinuierlichen Fälle müssen auch bei aktivierter
Policy vollständig bytegleich bleiben. Die Quellaufnahme bleibt in allen Fällen gleich.

Bei 90 und 120 BPM stimmen die Blockgrößen bytegenau überein. Bei 173 BPM erlaubt die
Prüfung maximal **ein Sample** Rundungsunterschied, bei identischen Ereignissen, Noten,
Velocities und Plänen. Dieser Unterschied ist bereits in der vorherigen Engine sichtbar
und wurde hier nicht durch eine allgemeine Transportüberarbeitung beseitigt.

Die Auswertung vergleicht die tatsächlichen Noten mit dem realisierten Plan, Einsätze,
Gate-Enden, Herkunft vom Original, harmonische Eignung in den fest definierten Verläufen,
Mindestpausen, MIDI-Notenbesitz und fehlende Auto-Arp-Anschläge im aktiven Figurenfenster.
Statistiken enthalten nur tatsächlich mit Note-ons begonnene Figuren, keine lediglich
vorausberechneten Möglichkeiten. Bei dynamischem XY wird zusätzlich der vollständige
Ereignisstrom über Blockgrößen verglichen; unbekannte historische Automation wird nicht
als vollständige harmonische Vergangenheit rekonstruiert.

### Messergebnisse bei 120 BPM

Aktiver Takt bedeutet: mindestens ein Teil einer Hook-Note klingt in diesem Takt.
Das ist kein Maß für durchgehende Lautstärke oder subjektive Dichte.

| Fall | Hook-Anschläge vorher → nachher | Aktive Takte vorher → nachher | Realisierte Wiederkehren |
|---|---:|---:|---|
| pedal-ostinato | 256 → 256 | 128 → 128 | {} |
| intense-melodic | 448 → 82 | 128 → 25 | {'0': 10, '3': 1} |
| quiet-melodic | 192 → 25 | 128 → 17 | {'0': 7} |
| lyrical | 320 → 41 | 128 → 17 | {'0': 7} |
| syncopated-melodic | 320 → 60 | 128 → 24 | {'0': 11} |
| dance-ostinato | 512 → 512 | 128 → 128 | {} |
| XY-changes | 320 → 26 | 128 → 9 | {'0': 2, '3': 1} |
| held-harmony | 1024 → 93 | 128 → 13 | {'0': 10, '3': 1} |

Verfahren 0 = Originalrealisierung, 3 = Sequenz. Leere Zählung bedeutet bei den beiden
Ostinati nicht Stille: sie laufen unverändert kontinuierlich. Die ruhigeren Fälle bleiben
bewusst sparsam. Auch bei XY-Wechseln können längere themenfreie Abschnitte bleiben;
die Policy garantiert keine maximale Pause. Mehr Sequenzen oder mehr aktive Takte sind
kein Qualitätsziel. Die derzeitige neutrale Phrasenstrategie ist deutlich zurückhaltender
als die bisher durchlaufenden melodischen Hooks und muss gehört werden.

Die intensive Studie kehrt bei Takt 8, 24, 32, 44, 56, 64, 72, 88, 96, 108 und 120 zurück:
zehn Originalrealisierungen und eine Sequenz. Im ruhigen Fall sind es sieben Original-
wiederkehren bei 16/32/48/64/80/96/112; die angeforderte Sequenz wird dort verworfen.
Die neun Sequenzen der gesamten Matrix sind neun tatsächlich erklungene Figuren,
keine bloß abweichenden Policy-Werte.

### Konkretes Beispiel: 2034 bei 120 BPM und Swing 0,3

Die eingeführte Quelle beginnt mit MIDI 72→76 (C–E), Abstand vier Sechzehntel. Bei Takt 64
realisiert die Sequenz MIDI **72, 76, 79, 83** (C–E, G–B), mit Rastereinsätzen
**0, 4, 10, 14** und Gates **4, 6, 4, 7**. Die zweite Terz ist sieben Halbtöne versetzt.
Swing verschiebt die tatsächlichen Anschläge auf Samplepositionen
6144000, 6168000, 6205201 und 6229201 bei 48 kHz. Der musikalische Bedarf beträgt
21 Sechzehntel; die Begleitreservierung endet mit den tatsächlichen Noten, nicht nach
pauschal zwei Takten. B bleibt beim dortigen Wechsel von Cmaj7 zu E7 ein Akkordton.

Der ursprüngliche Hook wird als tatsächliches Material eingeführt. Bis seine letzten
aufgenommenen Noten beendet sind, bleibt der Live-Einführungspfad zuständig. Wegen der
bestehenden Legatobindung kann dabei der Anfang des nächsten Zyklus noch anklingen.
Das erklärt beispielsweise drei aktive Einführungstakte statt einer idealisierten
starren Zweitakt-Einführung. Es wurden keine zusätzlichen Einführungsnoten erfunden.

MIDI-Paare und vollständige Prüfsummen/Pläne liegen unter `/workspace/work/hook-development`;
`intense-melodic-before.mid` und `intense-melodic-after.mid` eignen sich zum direkten
Vergleich mit identischen Patches. Kanal 8 ist die Hook, Kanal 5 der Arp. Die Dateien
enthalten 128 Takte bei 120 BPM, also 4:16 Minuten. Die kompakte Auswertung steht in
`POP_HOOK_DEVELOPMENT_COMPARISON.json`.

## Tests, Einschränkungen und Scope

`HookDevelopmentTests` prüft einen echten 128-Takt-Durchlauf ohne Allokationen,
Quellidentität, tatsächliche Original- und Sequenzpläne sowie wiederholten Seek/Loop
mitten in gehaltene Noten. Aufnahme-/Stimmen-/Neustarttests bleiben bestehen. Historische
Testprobes deaktivieren den neuen Pop-Bereich ausdrücklich als Kontrollkonfiguration;
die echten neuen Defaults werden separat über 128 Takte geprüft. Das ist keine zweite
Produktionsengine. Score-Daten und Score-Strategien bleiben unverändert.

Der Processor-Test enthält zusätzlich eine phrasenbezogene Pop-Studie mit Auto-Arp und
Live-/SMF-Vergleich über 64 Takte. Die bestehende Exportbegrenzung von 64 Takten bleibt.
Die erste neutrale Sequenzgelegenheit liegt bei Takt 64 und wird daher durch die separaten
128-Takt-Generator-/MIDI-Vergleiche geprüft; der normale 64-Takt-Pluginexport enthält sie
noch nicht. Diese Grenze wurde nicht als zusätzliche Exportfunktion verändert.

Weitere Grenzen: erste tatsächliche Quelle pro Stimme statt beliebig vieler Themen;
keine Verwendung auf geteilten Hook-Kanälen; keine allgemeine Komplementärrhythmik,
Formgrammatik, Bass-Neuplanung oder modalen Nicht-Akkordtöne. Die Rollenliste ist eine
vorläufige neutrale Datenentscheidung. Original-Harmonieanpassung kann genaue Intervalle
ändern, Sequenzen bleiben streng. Die Klangmöglichkeiten externer Patches sind weiterhin
nicht automatisch bekannt. Gespeicherte Anschlagsstärken bleiben Materialbestandteil;
eine zusätzliche motivische Dynamikentwicklung wurde nicht eingeführt.

Die Projektion arbeitet mit der bei Aufnahme bekannten Swing-Einstellung. Beliebige
Änderungen der Swingkurve während einer Aufnahme werden nicht als vollständige historische
Steuerkurve gespeichert. Kalter Seek ohne eingeführtes Material erzeugt keine erfundene
Motivvergangenheit; bekannte Quellen und die unveränderten Beschränkungen harmonischer
Eintrittslagen sind von dieser Frage zu unterscheiden. Siehe
`COLD_SEEK_HARMONIC_TRANSITIONS.md`.

Die musikalische Qualitätsbewertung bleibt bis zum Hörtest ausdrücklich vorläufig.


Abschließende Ergebnisse: 19/19 Kern-/Vergleichstests, 1/1 Processor-Live-/Exporttest
(einschließlich zusätzlicher phrasenbezogener Pop-Studie), 3/3 ASan-/UBSan-Läufe
(HookDevelopmentTests, PopMemoryTests, EngineTests) und 7/7 Paketprüfungen bestanden.
24 Vergleichspaare über je 128 Takte und 48 Blockgrößenvergleiche der neuen Strategie;
252 bytegenaue historische Kontrollfälle einschließlich aller Score-Anker und aller drei
Profile. Kein Push, keine neue GUI, kein Release.
