# Echtzeit-Performance und Stabilität – Referenz b969932

## Auftrag und Aussagegrenze

Untersuchungsbasis ist Dark Synth P2 (`b969932`) auf `develop/composition-core-prototype`. Die musikalische Abnahme von Dark Synth bleibt offen. Dieses Paket verändert keine musikalischen Regeln, Gewichte, Vorlagen, Notendauern, Anschlagsstärken, CC-Kurven oder Langzeitstrategien. Es fügt keine Latenz, GUI-Elemente oder Parameter hinzu.

Die Messungen untersuchen seltene Blockspitzen getrennt von der durchschnittlichen Last. Ein bestandener Funktionstest oder ein niedriger Mittelwert garantiert keine Echtzeitfähigkeit auf jeder DAW-/Instrumentenkonfiguration. Die ausführlichen Messungen stammen aus einer geteilten Linux-Umgebung; Windows wird zusätzlich funktional einschließlich pluginval geprüft. Externe Instrumente und Studio Ones eigener Audiothread-Scheduler gehören nicht zum Messaufbau. Der interne Vorhörsynth ist in der Hauptmatrix aus; seine DSP-Leistung wird hier nicht als separat verbessert ausgegeben. Seine Generatorinstanz verwendet dieselben optimierten Funktionen.

## Referenzen und Korrektur der bisherigen Messmethodik

Berücksichtigt wurden `tools/layer_performance.cpp`, `tools/dark_synth_realtime.cpp` und die Berichte zu Herrmann/Dark Synth, insbesondere `docs/research/dark-synth/P2_VALIDATION.md` und dessen CPU-CSV. Diese älteren Mikrobenchmarks verwendeten unter anderem `std::clock()`, O1 und teilweise aktive Assertions. Auf dieser Umgebung war die Auflösung der Prozess-CPU-Uhr für sehr kurze Blöcke nicht ausreichend: Viele Einzelwerte waren null, während einzelne Sprünge zu große Spitzen suggerieren konnten. Außerdem umfasst Prozess-CPU-Zeit gegebenenfalls weitere Threads.

Die neue Hauptmessung verwendet identische Release-Einstellungen vor/nach der Änderung. Standalone: GCC 14.2, `-O3 -DNDEBUG`, ohne Fast-Math. Gesamtprozessor: tatsächlicher `StromscoreProcessor::processBlock`, CMake Release mit den bestehenden JUCE-LTO-Einstellungen. Der Generator wird ergänzend getrennt untersucht. Instrumentierte Profilerläufe dienen zur Ursachenlokalisierung, nicht als absolute Latenzmessung.

## Aufbau der abschließenden Messungen

- 48 kHz, 4/4, D, 100 BPM; 64, 128, 256, 512 und 1024 Samples.
- Neutral SCORE, John Barry, Bernard Herrmann, John Williams, Ennio Morricone, Dark Synth sowie Neutral POP/ROCK.
- Ruhe, zwei intensive statische XYZ-Zustände, schnelle XYZ-Fahrten, Stop/Seek/Loop, Profilwechselketten und CC-Betrieb. Motivische Stimmen sind für den Belastungstest aktiviert.
- Hauptmatrix: 32 Takte pro Fall, zwei Wiederholungen. Vorher/Nachher laufen unmittelbar nacheinander; die Reihenfolge wird bei der zweiten Wiederholung umgekehrt.
- Zusätzliche 128-Takt-Läufe mit vier Instanzen: gleicher Thread (gemeinsames Blockbudget) sowie beim vollständigen Prozessor unabhängige parallele Worker. Identische Einstellungen müssen zwischen Instanzen identische MIDI-Prüfsummen liefern.
- GUI-Prüfung: tatsächlicher Editor mit Native-Peer, laufender Message-Loop und zeitlich getakteter Wiedergabe. Acht Takte ergeben 19,2 Sekunden tatsächliche Laufzeit je GUI-Fall. Keine GUI-Arbeit wird in den Audiothread verlagert.

Szenarienummern in den Rohdaten: 0 = Ruhe, 1 = dunkler intensiver Zustand, 2 = heller intensiver Zustand, 3 = schnelle XYZ-Fahrt, 4 = Stop/Seek/Loop, 5 = Profilwechselkette, 6 = CC mit XYZ-Bewegung.

Die Umgebung stellt drei sichtbare CPUs bei einer cgroup-Quote von zwei CPU-Kernen bereit (`200000 100000`). Keine erhöhte Echtzeitpriorität. Für die abschließenden Vergleichsmatrizen laufen keine Compiler, Sanitizer oder anderen Prüfprogramme parallel. Unkontrollierte externe Last des geteilten Systems kann dennoch verbleiben. Ungepacete parallele Worker sind ein Belastungstest, kein Nachbau der DAW-Threadplanung.

Gemessen werden Thread-CPU-Zeit mit `CLOCK_THREAD_CPUTIME_ID` und monotone Wandzeit. Ausgewiesen werden Durchschnitt, Median, p95, p99, p99.9, Maximum und Anzahl strikter Budgetüberschreitungen. Timer-/Messaufrufe sind nicht künstlich herausgerechnet. Die MIDI-Prüfsummenbildung und Berichtsausgabe erfolgen außerhalb des gemessenen `processBlock`-Abschnitts. Prozess-Gesamtzeiten enthalten zusätzlich Tool, Automation, GUI und Start/Ende und sind entsprechend separat bezeichnet.

Die Testautomation setzt Parameter vor dem gemessenen Aufruf. Deren Übernahme, musikalische Neuplanung, MIDI-Ausgabe und Zustandsveröffentlichung innerhalb von `processBlock` sind enthalten; der externe Setter-/Host-Benachrichtigungsaufruf selbst ist kein Bestandteil der Blockstatistik. Konstruktor und `prepareToPlay` gehören ebenfalls zur separat gemessenen Prozesslaufzeit, nicht zur Audioblockzeit. Die erste tatsächlich durch `processBlock` ausgelöste musikalische Planung ist hingegen enthalten.

Eine leere Messhülle über 100.000 Wiederholungen benötigte im Median 0,175 µs Thread-CPU und 0,382 µs Wandzeit. Auch ohne Plugin-Arbeit trat dabei ein einzelner Ausreißer von etwa 448 µs auf (`CLOCK_CALIBRATION.json`). Seltene Maxima können deshalb Messaufrufe und Kernel-Effekte enthalten. Reproduzierbare teure musikalische Prüfpfade sind davon zu unterscheiden. Aus einer Wandzeitüberschreitung allein folgt keine entsprechende CPU-Last des Plugins; umgekehrt werden hohe Thread-CPU-Werte nicht pauschal als Scheduling-Verzögerung abgetan.

| Samples | Blockbudget bei 48 kHz |
|---:|---:|
| 64 | 1,333 ms |
| 128 | 2,667 ms |
| 256 | 5,333 ms |
| 512 | 10,667 ms |
| 1024 | 21,333 ms |

Es werden keine Quantile verschiedener Läufe als vermeintlich gepooltes Quantil zusammengemittelt. Die Rohdaten enthalten jede Einzelmessung und beide Wiederholungen. Ein Maximum bleibt ein Einzelereignis; wiederholte Kontextspitzen und nicht reproduzierbare Ausreißer werden getrennt bewertet. Insbesondere werden Thread-CPU-Ausreißer nicht pauschal als reine Scheduling-Pausen ausgegeben.

## Identifizierte Engpässe

### Vollständiger Instrumentenkatalog bei Einzelabfragen

Viele Figuren-, Register-, Motiv- und Bassprüfungen fragten `outputCatalog(s)[output]` ab. Dafür wurden alle neun Zielbeschreibungen aufgebaut, obwohl nur ein Ziel benötigt wurde. Der instrumentierte Release-Herrmann-Lauf über 128 Takte zeigte 10.316.692 Aufrufe des vollständigen Katalogs. Nach der Umstellung verbleiben 4.526.720 vollständige Abfragen; Einzelabfragen verwenden gezielt eine Zielbeschreibung. Die Profiler-Selbstzeiten sind wegen Instrumentierung/Sampling keine eigenständige Deadline-Aussage.

Die Stammdaten bleiben an einer Stelle definiert. `ScoreEngine.h::outputDescription` erzeugt exakt denselben Eintrag wie der bisherige Gesamtkatalog. Unveränderliche Standards sind konstante Daten ohne dynamische Erstinitialisierung. Verfügbarkeit, Mute/Solo, Genre, unabhängige Lang-/Kurz-Artikulationen, Tonumfang, Polyphonie, Dauergrenzen und fester Stich-Trigger bleiben unverändert. Kein instanzübergreifender veränderlicher Cache.

### Wiederholte exakte Motivplatzierung

`ScoreEngine.h::authoredMotif` berechnete für jeden möglichen Basiston erneut dieselben Tonhöhen- und Registerbedingungen. Bei bereits aufgenommenem Material wurde dessen einzig zulässige Basis innerhalb der 128er-Schleife immer wieder aus dem gleichen ersten aufgenommenen Ton ermittelt. Diese Arbeit multipliziert sich durch die bestehenden Vordergrund-, Antwort- und Arpeggio-Vorprüfungen.

`AuthoredMotifSource.h::placeAuthoredMotif` bildet jetzt einmal die Schnittmenge zulässiger Basistonklassen und die exakten Registergrenzen der vollständigen Figur. Danach werden ausschließlich die gleichen zulässigen Basen in unveränderter aufsteigender Reihenfolge geprüft. Die vorhandene Oktavbedingung, Provenienzbindung, Abstandskosten und Gleichstandsentscheidung bleiben erhalten. Es erfolgt keine Tonänderung, neue Transformation oder Lockerung einer Eignungsbedingung.

100.000 direkte Differentialfälle vergleichen Ergebnis und Kosten mit der ursprünglichen vollständigen Suche. Die Instrumentenprojektion wird zusätzlich in 3.456 Fällen mit der unveränderten Testreferenz aus b969932 verglichen. Diese Referenz ist ausschließlich Testcode, kein paralleler Produktionspfad.

### Weitere untersuchte Pfade

Die harmonische XYZ-/Variety-Auswahl und Profilgewichte wurden nicht verändert. Suchzahlen sind im Verhältnis zu wiederholten musikalischen Vorprüfungen begrenzt. Es werden keine Approximationen von `exp`, anderen Gewichten oder Zufallsindizes eingeführt.

Stimmführungsplanung, Motivwiederkehr/-realisierung, koordinierte Rollen, ganze Sequencerperioden und TU-Antworten können an gemeinsamen Grenzen zusätzliche Arbeit erzeugen. Deren musikalisch erforderliche Prüfungen werden nicht gekürzt, auf spätere Blöcke verschoben oder durch unvollständig gekennzeichnete Cachetreffer ersetzt. Insbesondere bleiben XYZ-abhängige Harmoniebezüge bereits vorbereiteter Motivpläne korrekt.

Profilwechsel und Positionssprünge behalten ihre bisherige Rekonstruktion und sichere Notenfreigabe. Es gibt keine zusätzlichen Zustände, die auf Seek/Loop gesondert invalidiert werden müssten. Die Latenzmeldung bleibt unverändert.

Die bestehende CC-Ausgabe einschließlich Abschaltreset bleibt unangetastet. Im tatsächlichen Prozessor wird auch das wiederholte Ein-/Ausschalten mit XYZ-Bewegung gemessen. Der Generator-Vergleich enthält zusätzlich durchgehend aktive CC-Ausgabe. Die Szenarien sind innerhalb derselben Messebene identisch, nicht als identische Generator-/Prozessor-Parametrisierung auszugeben.

`PluginProcessor::publish` und `PluginEditor::timerCallback` kommunizieren über die vorhandenen atomaren Zustandswerte. GUI-Formatierung und Rendering erfolgen im Message-Thread. Es wurden weder Locks noch eine neue Publikationsarchitektur eingeführt. Ein übergreifender Settings-/Plan-Cache wurde bewusst vermieden, da dafür sämtliche musikalischen Zustandsabhängigkeiten abgesichert werden müssten.

## Ergebnisse

Die vollständige Einzelprozessor-Hauptmatrix umfasst **21.873.600 gemessene Blöcke über beide Stände**. Bei identischem Wiedergabeumfang sank die aufsummierte gemessene Thread-CPU-Zeit von **194,305 auf 163,149 Sekunden (−16,0 %)**. Das ist eine Aussage über diesen definierten Belastungsmix, keine allgemeine CPU-Garantie und kein gepooltes Quantil.

| Kontext | Änderung aufsummierte CPU-Zeit | Median des gepaarten p99.9-Verhältnisses nachher/vorher | CPU-Budgetüberschreitungen bei 128 Samples vorher → nachher |
|---|---:|---:|---:|
| Neutral SCORE | −6,5 % | 1,001 | 51 → 27 |
| John Barry | −36,4 % | 0,707 | 142 → 114 |
| Bernard Herrmann | −9,2 % | 0,888 | 116 → 92 |
| John Williams | −12,2 % | 0,885 | 155 → 133 |
| Ennio Morricone | −9,1 % | 0,912 | 35 → 44 |
| Dark Synth | −12,0 % | 0,882 | 32 → 50 |
| Neutral POP/ROCK | −5,0 % | 0,955 | 29 → 38 |

Die CPU-Zeiten sind aus Blockmittelwert × Blockzahl summiert. Die p99.9-Verhältnisse sind der Median gepaarter Einzelversuchsverhältnisse über fünf Puffergrößen, sieben Szenarien und beide Wiederholungen; sie sind keine zusammengefassten Blockquantile. Die 128-Sample-Spalte umfasst je Profil und Stand 403.200 Blöcke (14 Versuche). Über alle Profile sind es **560 → 498 CPU-Überschreitungen** bei jeweils 2.822.400 Blöcken. Verschlechterungen einzelner Kontexte werden ausdrücklich nicht ausgeblendet.

**Keine vollständige Beseitigung der Spitzen:** Das größte Einzelprozessor-CPU-Maximum der gesamten Hauptmatrix beträgt vorher 53,955 ms und nachher 74,775 ms. Trotz geringerer Gesamtarbeit und meist günstigerer p99.9-Werte bleiben damit einzelne deutliche Budgetüberschreitungen bestehen. Insbesondere ist Neutral beim p99.9 praktisch unverändert. Die verbleibenden Ausreißer lassen sich nicht allein mit der behobenen Redundanz erklären und werden nicht pauschal dem Betriebssystem zugeschrieben.

Die drei größten Nachher-Maxima wurden zusätzlich je fünfmal gepaart wiederholt (30 weitere Renderläufe, 15/15 identische Vorher-/Nachher-MIDI-Prüfsummen). Williams mit 256 Samples/schneller XYZ-Fahrt lag nachher in diesen Läufen bei 2,769–5,116 ms CPU-Maximum; der ursprüngliche 74,775-ms-Wert trat dabei nicht erneut auf. Im Williams-CC-Fall mit 512 Samples trat jedoch erneut ein CPU-Ausreißer von **63,938 ms** auf, bei einem Median der fünf Laufmaxima von 3,087 ms. Es wäre deshalb fachlich falsch, sämtliche hohen Werte als reine Wandzeit-Unterbrechungen oder als erledigt auszugeben. Diese seltenen CPU-Ausreißer sind noch nicht abschließend kausal zugeordnet. Barry/128/Transportwechsel lag im Median der fünf CPU-Maxima bei 3,148 → 2,112 ms; auch dort blieben einzelne Überschreitungen. Vollständige Gegenwerte und Wandzeiten: `PEAK_RECHECK.jsonl` und letzter Abschnitt von `RESULTS.md`.

Alle detaillierten Zahlen einschließlich Mittelwert, Median, p95, p99, p99.9, Maximum und Überschreitungen für Thread-CPU und Wandzeit stehen in [RESULTS.md](realtime-performance/RESULTS.md). Darin sind auch serielle/parallele Vierinstanzläufe und die tatsächliche GUI ausgewiesen. Die [Grafik](realtime-performance/TAIL_COMPARISON.svg) zeigt die Spannweite beider 128-Sample-XYZ-Läufe. Sämtliche Versuchsstatistiken stehen unverändert in `ENGINE_PAIRED.jsonl` und `PROCESSOR_PAIRED.jsonl`; `SUMMARY.json` enthält die Zusammenfassung.

Gleichzeitig anfallende Planungsgrenzen mehrerer Instanzen können sich auf demselben Audiothread weiterhin addieren. Die Optimierung verteilt keine musikalisch erforderliche Arbeit auf spätere Blöcke, ändert kein Ereignis und führt keinen spekulativen Settings-/Plan-Cache ein. Sie reduziert nachgewiesene redundante Arbeit, garantiert aber weder aussetzerfreien 64-/128-Sample-Betrieb noch eine maximale Callback-Dauer. Die praktische Stabilität muss zusätzlich auf dem jeweiligen Studio-One-System mit dessen externen Instrumenten beurteilt werden.

## Musikalische und technische Regression

- **939/939 vollständige MIDI-Bytevergleiche gegen b969932 bestanden**, keine wegen Auswahlproblemen übersprungenen Fälle. Verglichen werden absolute Sampleposition, Ziel, Kanal, Note/Controller, Wert und Ereignistyp in unveränderter Reihenfolge; nicht nur Notenzahlen. Rohnachweis: `realtime-performance/MIDI_REGRESSION.json`.
- Enthalten sind die vorhandenen Katalogkontexte, zwölf Transpositionen, 3/8, 5/8, 7/8, Swing, eingeschränkte Bass-/AR-Register, gemeinsame Kanäle, beide Follow-Zustände, manuelle Begleitung, alle melodischen Rollenbesetzungen, Transportwechsel und 128-Takt-XYZ-Fahrten. CC1/CC11 sind ausdrücklich mit erfasst.
- **11/11 tatsächliche Prozessorprüfungen bestanden**: einschließlich Live-/Exportvergleich, Profilwechsel, MIDI-CC, Transport und bisheriger Profile; bestehende C++-/C-Heap-Wächter ohne Befund.
- **12/12 ASan/UBSan-Prüfungen bestanden**, einschließlich der neuen exakten Platzierungs-/Instrumentenbeschreibungstests. Leak-/Fehlerabbruch aktiv.
- **7/7 Paketprüfer-Tests bestanden. Linux-VST3 gebaut.**
- **68/68 Kerntests bestanden**, einschließlich sämtlicher vorhandenen historischen Vergleichsrenderings.
- Windows-x64-Regressionen, Paketprüfung und pluginval Strictness 8 sind verbindliche Gates des zugehörigen DEV-Workflows. Das endgültige Ergebnis wird mit dem Download gemeldet; kein offizielles Release und kein Tag.

## Reproduktion

- `tools/realtime_engine.cpp` + `tools/realtime_probe.h`: vollständige Generatorblöcke, ohne GUI/Prozessorhülle.
- `tools/realtime_processor.cpp`, CMake-Ziel `RealtimeProcessorProbe`: tatsächlicher Prozessor, serielle/parallele Instanzen und GUI.
- `scripts/recheck_realtime_peaks.py BEFORE AFTER`: fünf zusätzliche gepaarte Wiederholungen der drei größten Nachher-Maxima, erst nach der Hauptmatrix ausführen.
- `scripts/report_realtime.py`: Zusammenfassung und statische Vergleichsgrafik aus den unveränderten Messdaten.
- `scripts/measure_realtime.py AFTER OUTPUT.jsonl engine|processor BEFORE`: gepaarte Messmatrix, zwei umgekehrt angeordnete Wiederholungen, MIDI-Prüfsummen- und Instanzunabhängigkeitsprüfung.
- `scripts/compare_realtime_midi.py BEFORE AFTER OUTPUT.json`: vollständige Bytevergleiche der Renderereignisse einschließlich CC und Reihenfolge, nicht nur Notenzahlen.
- `Tests/RealtimeNeutralityTests.cpp`: unabhängige brute-force-Referenz der Basiswahl und unveränderte Instrumentenkatalogreferenz.

Beispiel: Standalone jeweils gegen die Source-Header von b969932 und dem neuen Stand mit `c++ -O3 -DNDEBUG -std=c++17 -I<Source> tools/realtime_engine.cpp -o <binary>` bauen. Für den vollständigen Prozessor `cmake --build <build> --target RealtimeProcessorProbe --config Release` verwenden und beide Binärstände sichern. Unter Linux sind ein Display und die JUCE-Systembibliotheken erforderlich. Bei nacktem Xvfb hält `scripts/headless_realtime.py` die üblichen Fensterprotokoll-Atoms bereit, damit der tatsächliche Editor ohne Fenster-Manager getestet werden kann. Windows-Helfer verwenden `GetThreadTimes`; dessen Auflösung darf nicht ungeprüft mit der Linux-Thread-CPU-Uhr gleichgesetzt werden. Die veröffentlichten Timing-Matrizen stammen aus Linux. Für neue Messungen gelten die dokumentierten Quieszenz- und Reihenfolgebedingungen.

Keine offiziellen Releases/Tags. Nach dem geprüften Windows-DEV-Build endet dieses Arbeitspaket; die musikalische Dark-Synth-Abnahme bleibt eine getrennte Aufgabe.
