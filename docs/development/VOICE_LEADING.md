# STROMSCORE 2.0 – Stimmführung und Bedienkorrekturen

Diese Analyse dokumentiert die Entwicklung von **Version 2.0**, deren Veröffentlichung der Auftraggeber am 22. November 2026 freigegeben hat. Basis ist die veröffentlichte Version 1.9, Commit `22be37ee755391f3651d7f5718c2e3d302c722ea`. `VERSION` ist jetzt 2.0; die Plugin-Kennung bleibt erhalten. Zusätzlich sind die gesammelten Fahrt- und CC-Bedienkorrekturen enthalten. Keine Änderungen an Phrasierung und Motiventwicklung. Die Freigabe ist keine Behauptung einer hier durchgeführten Hörbewertung.

## Analyse der bisherigen Engine

Die reine C++-Engine in `Source/ScoreEngine.h` trennt harmonischen Vorrat, Szenen-/Stimmungswahl, Muster und MIDI-Notenbesitz:

- 48 Score- und 36 Pop-Rock-Wendungen liefern Akkorde mit Grundton, Qualität, Dauer und optional eigenständigem Basston. Eigene Akkordfolgen werden in dieselbe Datenstruktur übersetzt.
- `locate`/`chordFor` bestimmen Harmonie, Durchgangsdominante und das Folgen bzw. Liegenbleiben einer Ebene. `padType` ergänzt bestimmte einfache Dreiklänge um Unruhefarben.
- `padChord` setzte in 1.9 rootbezogene weite/enge Lagen. Bei eigenen Folgen wählte Variation zusätzlich wechselnde Lagen. Eine mehrstimmige Optimierung zwischen Akkorden gab es nicht.
- Vor jedem Musikraster wurden fällige Noten beendet. Ein gemeinsamer Akkordton konnte daher selbst bei gleicher MIDI-Tonhöhe nicht über die Akkordgrenze liegen bleiben.
- Der Bass trägt Grund-/Slash-/Pedaltöne und eigene rhythmische Figuren. Seine Funktion ist nicht die einer beliebig invertierbaren Fläche.
- Die Gegenstimme hat bereits harmonische Zieltonsuche und Legato; Arpeggios, Tupfer und Stich besitzen bewusste Konturen bzw. Schlagfunktionen. Sie werden deshalb nicht auf Flächenstimmführung umgestellt.
- `Active` verwaltet seit 1.9 getrennte Ansprüche je Ausgang auf gemeinsam genutzte MIDI-Noten. Diese Buchführung bleibt zuständig für Kanalteilung, Mute und Note-offs.
- Der Prozessor übernimmt Transport, CCs, State, Preview und MIDI-Dateiexport. Diese Schnittstellen bleiben unverändert.

## Gezielte Änderungen

### Vollständiger harmonischer Satz

`Source/VoiceLeading.h` sucht innerhalb eines festen, begrenzten Kandidatenraums nach einer Lage für **sämtliche vom Harmoniemodul gelieferten Akkordtonklassen**. Septimen, Nonen, Alterationen und bewusste Quinten-/Quartenfarben werden nicht als „unwichtige“ Stimmen gestrichen. Vorhandene Verdopplungen bleiben grundsätzlich Teil der Besetzung, soweit der Tonumfang dies erlaubt.

Bewertet werden gemeinsame klingende Töne, geordnete Stimmbewegung, große Sprünge, Oberstimmenbewegung, tiefe enge Sekunden, Abstand zwischen Stimmen sowie Abweichung von Register und Weite des ursprünglichen Satzes. Dadurch sind Umkehrungen und Registerwechsel möglich; es ist kein unabhängiges Runden jeder Stimme auf den nächstgelegenen Ton. Bei Dominantauflösungen in Quartbeziehung werden Septimabstieg und Terz-/Leittonauflösung zusätzlich weich bevorzugt, ohne Farbnoten pauschal zu verbieten.

Der ausdrücklich ausgearbeitete chromatische Satz von **Drahtseil** hat Vorrang vor der allgemeinen Optimierung. Die Grundtonbetonung und leisere zusätzliche Oberoktavverdopplung bleiben erhalten.

Auch „Fläche bleibt auf Grundakkord“ behält jetzt die Qualität des ersten Akkords. In 1.9 konnte dieser Modus eine vorgegebene Septime/None bereits vor dem Voicing in einen einfachen Dur-/Molldreiklang verwandeln. Bass-/Arp-Tonikamodi werden dadurch nicht verändert.

### Tatsächlich gehaltene gemeinsame Noten

Nur fällige Ansprüche der **langen Fläche** werden am exakten Musikraster bis zur Zielakkordentscheidung aufgeschoben. Passende Noten werden verlängert; nicht mehr benötigte Töne werden danach beendet. Stimmungswechsel verwenden denselben Abgleich. Ein vorhandener anderer Besitzer derselben physischen MIDI-Note bleibt geschützt.

Kurze Flächen artikulieren weiterhin neu. Bassrhythmen und die Legato-Zeit der Gegenstimme werden nicht verlängert oder umgedeutet. Ein bewusst kräftiger Zieleinsatz einer Fahrt darf weiterhin neu anschlagen. Bei gemeinsamem Kanal und identischer Tonhöhe kann eine andere rhythmische Ebene die physische Note neu artikulieren; MIDI 1.0 bietet dort keine voneinander unabhängigen Stimmen.

### Bass mit eigener Funktion

Für den Bass werden nur Oktavlagen des vorgegebenen harmonischen Basstons gesucht. Slash-Bässe bleiben Slash-Bässe; Orgelpunkt und Puls-Einstieg behalten ihren bisherigen Bezug. Rhythmik, Oktavfiguren und melodische Intervalle der Bassmuster bleiben erhalten. Walking-/chromatische Annäherungen zielen auf die tatsächlich geplante Oktave des nächsten Basstons bzw. der Durchgangsdominante.

### Reproduzierbarkeit und Transport

Ein zunächst erprobter Verlaufsspeicher wurde verworfen: Nach einem Sprung konnte er andere Lagen liefern als im Gesamtdurchlauf. Stattdessen wird ein **deterministischer harmonischer Plan** für bis zu acht Akkorde und ihre Durchgangsdominanten berechnet. Ein vorbereitender und ein gespeicherter Umlauf liefern einen begrenzten zyklischen Kontext. Es gibt weder eine unbeschränkte Rückschau noch eine von der CPU-Geschwindigkeit abhängige Konvergenzschleife.

Der Plan hängt von Harmonie, Variation, Register, Tonumfang und den bestehenden musikalischen Einstellungen ab. Er wird wiederverwendet, solange sich diese Voraussetzungen nicht ändern. Klanglich gleiche Voraussetzungen führen zu gleichen Lagen; die zuvor zufällig abgespielten Audioblöcke sind kein zusätzlicher Eingang. Tests vergleichen kontinuierliche Wiedergabe und kalten Einstieg in mehreren Phrasen, einschließlich Durchgangsdominanten und unterschiedlichen Blockgrößen.

Die vorhandene Szenenregel aus 1.9 bleibt bestehen: Ein neuer Wiedergabestart kann einen neuen Aufbau definieren; ein Stimmungswechsel kann eine andere Wendung auslösen. Der Plan rekonstruiert keine unbekannte frühere DAW-Automation. Er wählt den Satz der tatsächlich von der Engine bestimmten Zielharmonie. An einem Wendungswechsel wird deshalb nicht um jeden Preis eine alte Registerlage erzwungen.

### Tonumfang und physikalische Grenzen

Der Oktavregler transponiert den geplanten Satz unverändert um zwölf Halbtöne je Stufe. Er löst keine eigenständige Neuverteilung der Stimmen aus. Bestehende Tonumfangsgrenzen können danach eine Faltung des Satzes erzwingen. Ab zwölf verfügbaren Halbtönen ist jede Tonklasse darstellbar; die Tests prüfen inklusive Nonen und Septimen auch genau solche Oktavfenster.

Ein Fenster C3–E3 kann G und B eines Cmaj7 nicht enthalten. Keine Stimmführung kann gleichzeitig diese Grenze einhalten und die fehlenden Töne spielen. Die bestehende Faltungs-/Ersatzregel für solche unvollständig spielbaren Fenster bleibt begrenzt; zusätzlich liefert `unavailablePadPitchClasses()` die nicht darstellbaren Tonklassen für Tests/Diagnose. Es wird weder heimlich der Tonumfang erweitert noch behauptet, ein solcher Satz sei vollständig.

## Automatisierte Prüfung und A/B-Dateien

`VoiceLeadingTests` ist ein eigener CTest-Eintrag neben Engine und Processor. CMake liest die Referenz-Engine aus dem fest angegebenen 1.9-Commit; der Entwicklungsstand wird somit nicht mit einem beweglichen `main` verglichen. Die CI lädt dafür die Git-Historie. Bei einem Quellarchiv ohne Referenzobjekt laufen die eigenständigen Invarianten; CMake meldet dann ausdrücklich, dass der A/B-Teil fehlt.

Geprüft werden:

- alle 18 Akkordqualitäten, zwölf Tonarten, drei Register und zwei Fensterbreiten (12 bzw. 24 verfügbare Halbtöne), einschließlich erhaltener Farben und gültiger Note-on/off-Bilanzen;
- sämtliche 84 Stock-Wendungen, eigene Folgen, Grundakkord-Halten, Autorensatz von Drahtseil, Slash-Bässe und Walking-Annäherungen;
- kurze wiederholte Akkorde ohne unbeabsichtigtes Zusammenbinden;
- Stimmungswechsel mit identischer Ausgabe bei verschiedenen Blockgrößen;
- kalter Einstieg versus durchgehende Wiedergabe, auch in späteren Phrasen und mit Durchgangsdominanten;
- unveränderte CC-Zeitpunkte/-Werte und unveränderte Arp-/Akzent-/Gegenstimmen-Ausgabe gegenüber 1.9 in den statischen Vergleichsfällen;
- tatsächliche Live-/MIDI-Datei-Gleichheit im Prozessor, einschließlich gehaltenen Noten, Routing und CC-Arbeitsbereich;
- vorhandene Legato-, Reset-, Bypass-, State-, Kanalteilungs- und Echtzeit-Allokationstests.

Die fünf A/B-Fälle sind:

| Datei | Harmonie, Bezugstonart C |
|---|---|
| `maj7_ii9_V7` | Cmaj7 – Am7 – Dm9 – G7 |
| `minor_line` | Am – Am(maj7) – Am7 – Am6 |
| `quartal_sus` | Quartenklang auf C – Fsus4 – B♭add9 – Quartenklang auf C |
| `chromatic_mediants` | C – E – A♭ – C |
| `slash_bass` | Stock-Wendung Licht im Fenster: Am – C/G – Fmaj7 – E7 |

Für jeden Fall entstehen zwei MIDI-Dateien (1.9 und Entwicklung) sowie `comparison.csv` mit tatsächlich klingenden MIDI-Tönen, gemeinsamen Tonklassen, gehaltenen Tönen, Wiederanschlägen und einer bidirektionalen Tonabstandsmetrik. Die Metrik summiert jeweils den nächsten Abstand von jedem alten zum neuen und von jedem neuen zum alten Satz. Sie ist **kein Hörurteil und keine vollständige Zuordnung individueller Orchesterstimmen**.

Im lokalen Vergleich: 14 erneute Anschläge tatsächlich gemeinsamer MIDI-Töne in 1.9 gegenüber 0 im Entwicklungsstand; summierter bidirektionaler Abstand 321 gegenüber 84 Halbtönen. Diese Zahlen gelten für die fünf Fälle, nicht als allgemeine Qualitätsgarantie für alle Musik.

Lokal unabhängig von JUCE wiederholbar:

```sh
python tools/compare_voice_leading.py --output /tmp/stromscore-voice-leading
```

Oder regulär über CMake/CTest; die Ergebnisse liegen in `build/voice-leading-comparison`. Der Windows-Testworkflow hängt sie als **Stromscore-VoiceLeading-Comparisons** an. Die Windows-VST3 liegt als normales Actions-Testartefakt vor, **nicht als Release**.

## Musikalische Beurteilung

Beide MIDI-Fassungen mit **denselben Instrumenten, Artikulationen, Kanälen, Tempo und Mischereinstellungen** importieren. Die Vergleichsdateien verwenden C als Bezugstonart, 120 BPM, 4/4 und die gewohnten Ausgangskanäle. CC-Ausgabe ist in diesen Hörvergleichsdateien aus, um die Satzänderung isoliert beurteilen zu können; ihre technische Gleichheit wird separat getestet.

Zuerst Fläche allein, dann Fläche und Bass, anschließend das ganze Arrangement prüfen. Besonders auf gemeinsame Töne, Lage/Weite, erhaltene Septimen/Nonen und die Bewegung in den Akkordwechseln achten. Auch mehrere Wiederholungen und einen Einstieg mitten im Cue vergleichen.

Der interne Testklang und geringere Tonbewegung beweisen keine natürliche Orchesterwirkung. **Eine tatsächliche Hörbewertung mit den Ziel-Libraries wurde noch nicht durchgeführt.** Ergebnisse und Gewichtungen sind deshalb ausdrücklich zur musikalischen Beurteilung vorgesehen. Die neue Stimmführung ist eine begrenzte Heuristik, kein vollständiges Modell instrumentenspezifischen Orchestersatzes.

Entwicklungsbuild und 1.9 besitzen dieselbe VST3-Identität: Für den Plugin-A/B-Test die gesicherte stabile Datei jeweils ersetzen, statt beide gleichzeitig als verschiedene Instrumente zu installieren. Für den MIDI-A/B-Test ist kein Austausch nötig. Die Veröffentlichung wurde durch den Auftraggeber freigegeben; Phrasierung und Motiventwicklung bleiben spätere Aufgaben.


## Fahrt und Bedienung (2.0)

Die drei reproduzierten Fehler aus 1.9 waren: linke Gesten wählten bei sichtbarem B den nächstgelegenen Punkt; die Sichtbarkeit eines ohne Fahrt gesetzten B ging beim Editor-Neuöffnen verloren; ein Neustart vor dem nächsten Sechzehntel konnte durch die alte Ankunftsmeldung wieder ausgeschaltet werden.

Jetzt wählen Maustasten strikt A/B. Eine eigene, nicht als Host-Parameter exponierte Fahrtgeneration trennt neue Starts von alten Audioblockmeldungen. Der Audiopfad beobachtet Ausschalten/Neustart auch zwischen Rasterpunkten. Ziel-Sichtbarkeit wird als zusätzliche Projekteigenschaft gespeichert; alte Projekte ohne diese Eigenschaft werden anhand der Zielparameter/Fahrt migriert. Bestehende Parameter-IDs und Kanalbelegung bleiben erhalten.

Hinfahrten verwenden beim Retargeting einen neuen Kurvenabschnitt ab der Position der bisherigen Kurve am Änderungsrasterpunkt. Die Restdauer bleibt gleich. Bei Rückfahrten bleibt das ursprüngliche A das Ziel. DAW-Sprünge rekonstruieren die kanonische Kurve aus den dann gültigen Parametern; vorherige nicht automatisierte manuelle Ziele bilden keine historische Timeline. Der Export beginnt weiterhin eine frische Szene. Die Fahrt arbeitet wie bisher auf dem musikalischen Sechzehntelraster, nicht mit einer neu eingeführten samplegenauen Bewegungsautomation.

Tests decken alle vier Kurven, Retargeting, Rückfahrt, schnellen Neustart, Seek/Loop, Stopp, manuelle Übernahme, Editor-/Projekt-Wiederherstellung und Kanalzuordnungen einschließlich geteilter Kanäle ab. Die bestehenden Export-, CC-, Notenbesitz-, Legato- und Stimmführungstests laufen zusätzlich.
