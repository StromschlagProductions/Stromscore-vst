# Dark Synth P2 – Produktions- und Prüfprotokoll

## Reproduzierbare Produktion

Vergleichsbasis `eb32983`; dieselben Parameter, separater eingefrorener Vorher-Renderer. Die Diagnoseinstrumentierung wird ausschließlich im Offline-Renderer kompiliert und ist nicht Bestandteil des Plugins. `scripts/validate_dark_synth.py` prüft Notenbesitz und schreibt SMFs/JSON; die Quellenspalte stammt direkt vom ausgegebenen Note-on, nicht aus einem nachträglich betrachteten Auswahlplan.

- 588 zusätzliche bytegleiche MIDI-Vergleiche außerhalb Dark Synth einschließlich aller bisherigen Profile und POP/ROCK.
- 1029 normale 64-Takt-Produktionen auf 7³ XYZ-Knoten, je drei Variation/Seed/Abwechslungskombinationen.
- Neun 128-Takt-Hörstudien, statisch, langsam/schnell gefahren, TU allein und mit anderen Rollen; Blockvergleich 127/512 Samples.
- 50 zusätzliche Transport-/Register-/manuelle Fälle, zwölf Transpositionen, Swing, 3/8, 5/8, 7/8 und Blockvergleich 512/2048.
- 94 verschiedene Harmonien regulär gewählt; 132 unterschiedliche tatsächlich gespielte Figurenquellen einschließlich JC.

## XYZ-Kandidatenabdeckung

Tatsächliche `Generator::candidates`-Auswahl, 13³ XYZ-Punkte × Variety 0/.5/1 = 6.591 Anfragen. Distanz ist absolute euklidische XYZ-Distanz zum nächsten Anker, keine stilistische Qualitätsmessung. Ein Kandidat bedeutet nicht ausreichende musikalische Vielfalt.

| Stand | Kandidaten min / Median / max | Nur ein Kandidat | Kein Kandidat | Nächster Anker Mittel / Maximum |
|---|---|---:|---:|---|
| P1 | 1 / 2 / 25 | 3069 | 0 | 0.260 / 0.622 |
| P2 | 1 / 4 / 66 | 2338 | 0 | 0.208 / 0.515 |

Die weiche XYZ/Variety-Auswahl wurde nicht ersetzt. Randbereiche und ein enger Kandidatenkreis können trotz Katalogvergrößerung geringe momentane Auswahl besitzen. Nicht jede erreichbare Harmonie erlaubt jede einzelne Figur. Keine Gewichtsanpassung zur künstlichen Vollständigkeit der Verbraucherliste.

## Rollen in den 128-Takt-Beispielen

Zellen: physische Note-ons / Anteil klingender Zeit in Prozent. Ein Polyphonieklang wird bei der klingenden Zeit nur einmal gezählt.

| Beispiel | LF | KF | LB | KB | AR | TU | ST | GS | HM |
|---|---|---|---|---|---|---|---|---|---|
| 01-warm-pulseless | 86 / 100.0 | 0 / 0.0 | 9 / 37.5 | 185 / 18.7 | 0 / 0.0 | 56 / 16.9 | 0 / 0.0 | 0 / 0.0 | 0 / 0.0 |
| 02-shadow-rotation | 99 / 100.0 | 0 / 0.0 | 12 / 46.9 | 95 / 14.8 | 0 / 0.0 | 71 / 17.6 | 0 / 0.0 | 0 / 0.0 | 0 / 0.0 |
| 03-two-periods | 86 / 100.0 | 0 / 0.0 | 1 / 6.2 | 892 / 39.0 | 392 / 17.2 | 50 / 5.7 | 74 / 7.0 | 392 / 17.1 | 59 / 19.1 |
| 04-ritual | 105 / 100.0 | 776 / 37.9 | 0 / 0.0 | 444 / 43.4 | 784 / 34.5 | 52 / 10.2 | 89 / 8.3 | 0 / 0.0 | 0 / 0.0 |
| 05-high-unrest | 100 / 100.0 | 0 / 0.0 | 8 / 50.0 | 1127 / 24.9 | 1391 / 28.3 | 53 / 11.0 | 82 / 7.7 | 1154 / 19.7 | 58 / 19.7 |
| 06-bright-unease | 128 / 100.0 | 0 / 0.0 | 32 / 100.0 | 0 / 0.0 | 0 / 0.0 | 70 / 6.8 | 0 / 0.0 | 0 / 0.0 | 0 / 0.0 |
| 07-slow-xyz | 122 / 100.0 | 353 / 13.0 | 10 / 29.5 | 655 / 26.5 | 895 / 46.8 | 64 / 3.9 | 53 / 5.0 | 348 / 13.0 | 38 / 11.9 |
| 08-fast-xyz | 117 / 100.0 | 268 / 9.9 | 18 / 18.4 | 741 / 34.8 | 965 / 41.8 | 64 / 3.8 | 64 / 6.1 | 596 / 19.4 | 14 / 3.9 |
| 09-TU-alone | 0 / 0.0 | 0 / 0.0 | 0 / 0.0 | 0 / 0.0 | 0 / 0.0 | 68 / 18.0 | 0 / 0.0 | 0 / 0.0 | 0 / 0.0 |

## Reichweite und Nichtverwendung

| Familie | registriert | ausführbar/Teilfähigkeit | in Produktion beobachtet |
|---|---:|---:|---:|
| H | 65 | 64 | 64 |
| B | 21 | 21 | 18 |
| Q | 22 | 22 | 22 |
| TU | 28 | 28 | 27 |
| E | 18 | 11 | 0 |
| HM | 18 | 4 | 4 |
| R | 13 | 13 | 12 |
| TO | 7 | 7 | 7 |
| K | 10 | 0 | 0 |
| S | 30 | 0 | 0 |
| MS | 4 | 0 | 0 |

Neue ausführbare Q/B/TU/HM ohne beobachteten Note-on: `DS-B05, DS-B09, DS-B17, DS-TU10`. Diese Fälle sind keine musikalischen Erfolgsnachweise. Individuelle Eignungsgrenzen/kleine Auswahlfenster bleiben möglich; Sicherheitsregeln wurden dafür nicht global gelockert.

## Gefrieren und Antwortende: gesonderte Nachweise

In der normalen Atlas-/Hörstichprobe erklangen 182 Q13-Anschläge, aber kein langes Freeze-Gate; das längste betrug 0,0875 Viertel. Das integrierte Gefrieren wird deshalb nicht als im Atlas gehörtes Ergebnis ausgegeben. Ein gezielter physischer Verbrauchertest verwendet Q13 im harmonisch geeigneten H61-Kontext: Der letzte Ton vor Takt 24 wird ohne Neuanschlag bis zum Ende von Takt 32 gehalten und dort genau einmal freigegeben. Ein zusätzlicher Test prüft die bis zum vollständigen Quellenzyklus reichende Antwortreservierung nach Ende des kurzen TU-Gates sowie ihre Aufhebung beim Muten. Das sind ergänzende kontrollierte Verbrauchertests, keine reguläre Auswahlstatistik.

## Technische Tests

- **67/67 Kerntests erfolgreich:** vollständiger CTest-Durchlauf; vier zunächst veraltete Bestandsassertionen (276/30/27) wurden auf den erweiterten, weiterhin exakt geprüften Bestand angepasst. Die vier betroffenen Tests bestanden im gezielten Wiederholungslauf. Keine musikalische Quellenänderung währenddessen.
- **11/11 tatsächliche Prozessorprüfungen erfolgreich**, darunter 38 automatische Dark-Synth-Live-/SMF-Fälle sowie Profilwechsel, CC, Transport, manuelle Einstellungen und die bisherigen Profile. C++- und C-Heap-Wächter im Audiopfad ohne Befund.
- **11/11 ASan/UBSan-Prüfungen erfolgreich**, einschließlich Dark Synth, unabhängigen Sequenzen, harmonischen Schichten, Pedalen, Motiv-/Planungszeit, Ausführung, Williams-Motiven, Realisierung und Reprise; Leak-/Fehlerabbruch aktiv.
- **7/7 Paketprüfer-Tests erfolgreich. Linux-VST3 gebaut.**
- Harmonie-Datenregression zusätzlich: **1.008 vollständige 64-Takt-MIDI-Vergleiche und 2.016 Blockgrößenvergleiche**, vollständige bisherige Katalogfakten gleich.
- Unabhängiger CSV-/MIDI-Abgleich und Erzeugungsdriftprüfung erfolgreich. 42 musikalische Header blieben während der Abschlussprüfungen bytegleich zum eingefrorenen Implementierungsstand.
- **Windows-Freigabegate:** der bestehende `development-windows.yml`-Workflow baut x64, führt die dort verfügbaren Regressionstests, Paketprüfung und pluginval **Strictness 8** aus. Das Windows-Artefakt gilt erst bei erfolgreichem zugehörigem Workflow als freigegeben; dessen endgültiges Ergebnis wird zusammen mit dem Download gemeldet. Kein offizielles Release/Tag.

## Echtzeit-Rechenzeit

O1-Mikromessung, 48 kHz, 512 Samples, je 64 Takte; Prozess-CPU-Zeit (`std::clock`), nicht Echtzeit-Wandzeit oder garantierte Deadline. CSV-Zeilen: XYZ, erste Planung, p99, Maximum in Millisekunden. Allocationsprüfungen des tatsächlichen Prozessors ergänzen die Messung.

```
generator_bytes,27824
0,0,0,first_cpu_ms,0.138,p99_cpu_ms,0.015,max_cpu_ms,0.33
0.1,0.1,0.9,first_cpu_ms,0.127,p99_cpu_ms,0.027,max_cpu_ms,0.342
0.2,0.8,0.9,first_cpu_ms,0.273,p99_cpu_ms,0.157,max_cpu_ms,2.231
0.85,0.2,0.15,first_cpu_ms,0.239,p99_cpu_ms,0.031,max_cpu_ms,0.369
0.5,0.5,0.5,first_cpu_ms,1.085,p99_cpu_ms,0.058,max_cpu_ms,1.135
0.8,0.8,0.8,first_cpu_ms,0.54,p99_cpu_ms,0.148,max_cpu_ms,4.252
```

Der Generator belegt in dieser Messkonfiguration 27.824 statt 21.632 Bytes (fester Instanzspeicher). Über die sechs untersuchten Positionen: erste Planung höchstens 1,085 ms, p99 höchstens 0,157 ms, Maximum 4,252 ms; Referenzmaximum 4,355 ms. Einzelne reguläre Planungskosten steigen. Das ist keine Aussage über alle möglichen musikalischen Zustände. Die vollständigen CPU-Zeilen stehen in `P2_CPU_PROFILE.csv` und `P1_CPU_PROFILE.csv`.

Kleine Puffer und externe DAW-/Instrumentenlast können hörbare Aussetzer verursachen. Die hier gemessenen Rechenzeitspitzen sind offen ausgewiesen, keine universelle Freigabe beliebiger Puffergrößen. Die Anpassung der Festton-Suche überspringt nur mathematisch unmögliche Platzierungen.

## Reproduktion

```sh
python scripts/build_dark_synth.py --check
python Tests/DarkSynthDataTests.py
python Tests/ReleaseTests.py
c++ -O1 -std=c++17 -ISource tools/dark_synth_realtime.cpp -o /tmp/ds-cpu
/tmp/ds-cpu
# Vorher-/Nachher-Renderer aus den jeweiligen Headern bauen:
python Tests/ExecutionFixtures.py /tmp/ds-headers
c++ -O1 -std=c++17 -DSTROMSCORE_DIAGNOSTIC_EVENTS=1 -DSEQUENCE_DIAGNOSTICS=1 -DDARK_SYNTH_DIAGNOSTICS=1 -I/tmp/ds-headers tools/williams_probe.cpp -o /tmp/ds-audit/current
python scripts/validate_dark_synth.py /tmp/ds-audit
```

`/tmp/ds-audit/before` muss zuvor mit den Headern aus `eb32983` kompiliert werden. Keine Tests ändern musikalische Produktionsparameter zur Erzwingung einer Importquote.
