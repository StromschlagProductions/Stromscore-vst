# Erster validierter Harmonieimport: WC-H01, WC-H11 und WC-H19

Ausgangspunkt `e1b1de4`, Entwicklungsbranch `develop/composition-core-prototype`.

Die verbindliche Folgeaufgabe zur genreabhängigen Künstlerauswahl und zu einem musikalisch eigenständigen Wang-Chung-Profil steht in [COMPOSER_PROFILE_ROADMAP.md](COMPOSER_PROFILE_ROADMAP.md). Sie wurde **nicht** in diesen Import vorgezogen. Keine neue Künstleridentität, keine Künstlergewichte, keine GUI- oder Engine-Regeländerung.

## Eingefügte Daten

| ID / Referenz | Name | Akkorde (ganze Takte) | Explizite relative Bassnoten | Modusvorgabe | XYZ |
|---|---|---|---|---|---|
| 2037 / WC-H01 | Mixolydischer Kreis mit Sus-Auflösung | C(2), Bb(2), F/A(2), Csus2(1), C(1) | 0,10,9,0,0 | mixolydian, Zentrum C | .75/.50/.30 |
| 2038 / WC-H11 | Dorische Wendung | Cm7(2), F/C(2), Cm7(2), F/A(1), Bb(1) | 0,0,0,9,10 | dorian, Zentrum C | .40/.50/.30 |
| 2039 / WC-H19 | Dunkle Quint-Maschine | C5(6), Ab5(1), Bb5(1) | 0,8,10 | automatic, Bezug C; keine feste Modusbehauptung | .15/.90/.20 |

Alle drei sind `protected`, dauern acht Takte und stehen nur im Pop/Rock-Pool. Die bisherigen 84 IDs, Inhalte und Reihenfolgen sind erhalten; die drei neuen IDs stehen an den bisherigen Pop/Rock-Indexpositionen 36–38. Gesamt: 87 Vorlagen, davon 48 Score und 39 Pop/Rock. Die vorhandenen 18 Akkordtypen und maximal acht Slots reichen aus.

Harmonische Fakten, Quellen und explizite Bassangaben liegen in `data/harmony/catalog.json`; Zuordnung und Standardbegleitung in `arrangements.json`; redaktionelle Hinweise in `notes.json`. Die generierten Laufzeitkataloge und beide `WENDUNGEN_INVENTAR`-Dateien sind aktualisiert. Die Nutzerreferenzen WC-H01/WC-H11/WC-H19 sind einzeln dokumentiert, ohne Behauptung einer Originaltranskription oder exklusiven Künstlerzugehörigkeit.

Das gemeinsame Rezept verwendet vorhandene neutrale Mittel: ArpUp/ArpCircle, BassHeld/BassQuarter und PadHeld. Bestehende Intensitätsregeln dürfen daraus zum Beispiel Achtelbass ableiten. Es wird kein besonderer Hook (`hook: null`), kein Sechzehntel-Motor und keine Rhythmusvorlage aus der Forschungsuntersuchung zusätzlich importiert. Alle drei bisherigen Profile gewichten jede neue ID mit 1. Die Instrumentierung bleibt frei.

## Musikalischer Nachweis

Tonklassen: 0=C, 1=Db, 2=D, 3=Eb, 4=E, 5=F, 6=Gb, 7=G, 8=Ab, 9=A, 10=Bb, 11=B/H.

- **WC-H01:** Klassen je Akkord {0,4,7}, {10,2,5}, {5,9,0}, {0,2,7}, {0,4,7}; Bass C–Bb–A–C–C. Wechsel an Taktanfängen 0/2/4/6/7. Bb gehört zum gesamten mixolydischen Kontext, die Csus2-Fläche erhält keine Terz. Geschützte Begleitung fügt auch bei hohem Z keine Septime hinzu.
- **WC-H11:** Klassen {0,3,7,10}, {5,9,0}, {0,3,7,10}, {5,9,0}, {10,2,5}; Bass C–C–C–A–Bb. Wechsel 0/2/4/6/7. F/C und F/A haben denselben Akkordgrundton und dieselben harmonischen Klassen, aber verschiedene Bassvorgaben. Das A bleibt als dorische große Sexte verfügbar und erklingt in den F-Dur-Feldern.
- **WC-H19:** Klassen {0,7}, {8,3}, {10,5}; Bass C–Ab–Bb. Wechsel 0/6/7. Keine Terz in den definierten oder tatsächlich geprüften Harmonie-/Arp-Klassen, auch bei hoher Intensität und hohem Z. Oktavverdopplung, Register-/Lagenwechsel und reduzierte Besetzung sind Ausgestaltung, keine neue Akkordfarbe.

`HARMONY_IMPORT_MUSICAL_RESULTS.json` enthält erwartete Klassen, Wechselpositionen, tatsächliche Klassen nach MIDI-Ausgang und die im ersten Zyklus **klingenden** Klassen je Slot, einschließlich gehaltener Töne. Bass und melodische Nicht-Akkordtöne sind getrennt ausgewiesen. Ein chromatischer Bassannäherungston ist keine zusätzliche Flächenfarbe. Die manuelle Kontrollbegleitung verwendet gehaltene Fläche/Bässe und ein Akkordarpeggio; die automatische Begleitung darf ihre bisherigen rhythmischen und Bassannäherungsregeln nutzen.

Mit „Folgt Akkorden“ AUS bleiben Fläche, Bass und Arp auf dem Anfangsbezug C; die laufenden Slash-Vorgaben werden nicht erzwungen. Mit EIN greifen die expliziten Bassvorgaben. Das Verhalten wurde nicht durch Vorlagendaten übergangen. Die bisherige sehr niedrige Intensitäts-Ruhezone unterhalb der Still-Schwelle kann Harmonie gezielt halten; sie wurde nicht abgeschafft. Die zeitlichen Datenprüfungen verwenden Intensitäten oberhalb dieser Zone.

### Modale Grenze bei WC-H19

Die Vorlage selbst behauptet ausdrücklich keinen eindeutigen Modus. Ihre sechs harmonischen Tonklassen sind äolisch kompatibel. Die vorhandene automatische Erkennung betrachtet aber ausschließlich Ionisch, Mixolydisch, Dorisch und Äolisch; innerhalb dieser eingeschränkten Menge liefert sie `aeolian/unique`. Das ist ein technischer Schätzwert, keine gesicherte umfassende modale Bestimmung. Er wurde nicht als feste Modusvorgabe gespeichert und ergänzt keine Terz im harmonischen Quintklang. Eine explizite Kennzeichnung „kompatibel, aber nicht bestimmt“ für melodische Strategien wäre ein gesonderter kleiner Metadaten-/Modellschritt, kein stillschweigender Bestandteil dieses Imports.

### Melodische Grenze

Die eigenständige Hauptmelodie ist im vorhandenen Pop/Rock-Fähigkeitsmodell deaktiviert. Tests schalten sie EIN/AUS und prüfen das unveränderte Ergebnis; Kanal 9 bleibt hier leer. Die Dialog-/Gegenstimme ist unabhängig verfügbar. Ohne besondere Hook-Zuordnung verwenden die neuen harmonischen Vorlagen deren vorhandene generische Linienfunktion. Es wurde keine neue Motiv- oder Entwicklungsstrategie erfunden. Melodische Nicht-Akkordtöne werden nicht pauschal als Verletzung der harmonischen Definition gewertet; ihre bisherigen Verfahren bleiben erhalten.

## XYZ-Diagnose mit unverändertem Algorithmus

21×21×21 Rasterpunkte einschließlich sämtlicher Randflächen und acht exakter Ecken; Variety 0/.25/.5/.75/1. Sowohl `Generator::candidates()` als auch `pick()` und deren echte Float-Gewichte werden aus beiden kompilierten Versionen ausgewertet. Die Übersicht trennt den minimalen absoluten euklidischen XYZ-Abstand vom mit Y=.7/Z=.8 gewichteten Abstand und protokolliert auch den Abstand der tatsächlich gewählten Wendung. Kleine Unterschiede zwischen Menü- und Pick-Kandidaten durch die vorhandene Epsilon-Regel werden separat erfasst.

Harmonische Familien bedeuten hier exakt denselben achtaktigen Tonklassen-/Grundton-/Bassverlauf, einschließlich zyklisch verschobener Startphase. Keine subjektive Stilfamilie und keine automatische transpositionsübergreifende Gleichsetzung. Vorhandene Dubletten werden nicht mehrfach als musikalisch eigenständige Familie gezählt.

| Kennzahl | 36 Wendungen | 39 Wendungen |
|---|---:|---:|
| Mittlerer nächster absoluter XYZ-Abstand | .3097 | .2964 |
| Maximaler nächster absoluter XYZ-Abstand | .9431 | .8958 |
| Mittlerer nächster gewichteter Abstand | .2563 | .2417 |
| Mittlere Kandidatenzahl, Variety .5 | 3.0632 | 2.9121 |
| Mittlere harmonische Familien, Variety .5 | 3.0412 | 2.8945 |
| Rasterpunkte mit nur einem Kandidaten, Variety .5 | 2510/9261 | 3267/9261 |
| Mittlere Kandidatenzahl, Variety 1 | 8.6770 | 8.6979 |

Die Ankernähe verbessert sich, die lokale Auswahlvielfalt bei mittlerer Variety aber teilweise **verschlechtert** sich. Der relative Schwellwert orientiert sich am nun besseren Bestgewicht und verdrängt dadurch alte, weiter entfernte Kandidaten. Bei Variety .5 betrifft die Verdrängung mindestens eines alten Kandidaten 1648/9261 Punkte. Dies ist eine erwartete Auswirkung des unveränderten Auswahlverfahrens, keine Veranlassung, Koordinaten willkürlich zu verschieben.

Acht exakte Ecken, Variety .5; absolute Distanz zum nächsten Anker:

| XYZ | Kandidaten vorher→nachher | Distanz vorher→nachher | Gewählte ID vorher→nachher (Variation 1, Salt 0) |
|---|---|---|---|
| 0/0/0 | 2→2 | .407→.407 | 2002→2002 |
| 0/0/1 | 2→2 | .721→.721 | 2001→2001 |
| 0/1/0 | 4→1 | .439→.269 | 2010→2039 |
| 0/1/1 | 2→2 | .308→.308 | 2006→2006 |
| 1/0/0 | 3→3 | .427→.427 | 2018→2018 |
| 1/0/1 | 2→1 | .943→.896 | 2023→2037 |
| 1/1/0 | 1→1 | .206→.206 | 2020→2020 |
| 1/1/1 | 1→1 | .787→.787 | 2017→2017 |

Auch nach dem Import bleiben besonders an hellen, stark unruhigen Rändern große Abstände bzw. geringe Auswahl bestehen. Drei Vorlagen schließen keine allgemeine XYZ-Abdeckungslücke. `HARMONY_IMPORT_COVERAGE.json` dokumentiert alle fünf Variety-Werte und sämtliche Ecken einschließlich konkreter Kandidaten-IDs/Familien.

## Testtrennung und Reproduktion

- **Unveränderter Renderer bei expliziter Auswahl:** 504 vollständige 32-Takt-Vergleiche der bisherigen 84 IDs × drei Profile × linear/Seek-Loop-Neustart gegen `e1b1de4`, mit Swing und eingeschalteten Durchgängen. Bytevergleich aller Note-/CC-Ereignisse einschließlich Kanal, Ausgang und Zeitposition. `HARMONY_IMPORT_REGRESSION.json` enthält die Prüfsummen.
- **Testinstrumentierung:** `HarmonyImportFixtures.py` kopiert tatsächliche Header in das Buildverzeichnis. Ausschließlich für die explizite Auswahl werden dort `pick()` und automatisches Neuwählen am Wechselpunkt auf die gewünschte ID festgelegt; Renderer, Vorlagendaten, Instrumentenmodell und Transport bleiben unverändert. Kein solcher Schalter und keine Testvariable gelangen in den produktiven Generator.
- **Historische Funktionsvergleiche:** Die bestehenden Entwicklungsvergleiche von Bass, Rhythmus, Hooks usw. verwenden dieselbe aktuelle Engine mit dem ausdrücklich auf die alten 36 Kandidaten begrenzten Testpool. Dadurch testen sie weiter ihre jeweilige musikalische Funktion und vermischen diese nicht mit absichtlich geänderter automatischer Auswahl. Das ist ein Testdatensatz, keine parallele Legacy-Engine. Der eigentliche Plugin-Build verwendet ausschließlich den vollständigen 39er-Pool.
- **Vollständiger neuer Pool:** `HarmonyImportTests.cpp`, `HarmonyImportProbe`/`analyze_harmony_import.py` und der tatsächliche Processor prüfen die echte 39er-Auswahl separat. Die neue Matrix umfasst 1296 Acht-Takt-Renderings mit zwölf Transpositionen, Z=.1/.6/.95, Y=.25/.65/.95, beiden Follow-Zuständen und automatischer/manueller Begleitung. Zusätzliche 8/32/128-Takt-Läufe schalten Dialog und Hauptmelodie unabhängig EIN/AUS. Seek, Loop, Szenenneustart, 127/480/512/8192-Sample-Blöcke, 90/120/173 BPM und Swing werden geprüft. 480 ist die Exportblockgröße; einzelne samplegenaue Rundungsdifferenzen werden auf höchstens ein Sample begrenzt.
- **Real-Time:** Automatische Wiedergabe jeder neuen Wendung über 8/32/128 Takte sowie Probe-Renderings laufen mit Allokationswächter. Der Processor-Test prüft zusätzlich C-Heap-Aufrufe. Neue Daten sind statisch generiert; keine Dateioperation, Validierung oder Heap-Allokation im Audiothread. Der maximale Kandidaten-Scratch bleibt bei 48, weil der Score-Pool weiterhin größer ist.

```sh
cmake -S . -B build -DENGINE_ONLY=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

Der tatsächliche `ProcessorTests`-Gesamttest baut mit JUCE und enthält nun 54 Live-/SMF-Vergleiche an den drei neuen exakten Ankern: die Abdeckung aller zwölf Transpositionen kommt aus der Kernmatrix, die Processor-Fälle prüfen ergänzend C/F/H, beide Follow-Zustände und alle drei vorhandenen Profile. Dabei bleibt die automatische Auswahl aktiv; die gewählte neue ID wird geprüft.

## Hördateien und nächste Schritte

`HARMONY_IMPORT_MIDI.zip` enthält drei 128-Takt-Vergleichsgruppen (alter 36er-Pool automatisch / neuer 39er-Pool automatisch / neue Vorlage explizit) und einen bytegleichen alten Kontrollfall vor/nach dem Import. Gleiche XYZ-Anker und gleiche Instrumentbelegung verwenden. Eine geänderte automatische Auswahl ist ausdrücklich kein isolierter Qualitätsnachweis für Stimmführung oder Instrumentierung.

Die enthaltene deutsche Anleitung erklärt neun MIDI-Ziele, Tempo und Testlänge: 8 Takte = 16 Sekunden, 32 Takte = 1:04, 128 Takte = 4:16 bei 120 BPM. Die ZIP ist ein Entwicklungs-Hörvergleich, kein Plugin-Release.

Als nächste kleine Schritte kommen ein Hörtest dieser drei Vorlagen und anschließend die erste klar begrenzte Aufgabe aus der verbindlichen Profil-Roadmap in Betracht. Keine weiteren Vorlagen, Gewichte oder musikalischen Verfahren wurden vorgezogen. Musikalische Qualitätsaussagen bleiben bis zum Hörtest vorläufig.

## Abschlussprüfung

33/33 Gesamttests bestanden. 504 fest ausgewählte alte MIDI-Renderings bytegleich zu `e1b1de4`; neue 39er-Auswahl separat diagnostiziert. 1296 neue Matrixrenderings plus 8/32/128-Takt-, Stimmen-, Transport-, Tempo-, Swing- und Blockgrößenprüfungen bestanden. Tatsächlicher Processor: 54 zusätzliche Live-/SMF-Fälle und bestehender Gesamttest bestanden. ASan/UBSan für Import- und Engine-Tests ohne Befund, 7/7 Paketprüf-Fixtures bestanden. Linux-VST3 mit vollständigem 39er-Pool erfolgreich gebaut; Bundle-/ELF-/Versionsmetadaten geprüft. Elf MIDI-Dateien samt Anleitung und Prüfsummen archiviert; SMF-Header/Trackstruktur und ZIP-CRC geprüft. Kein Windows-/pluginval-Lauf und kein Release in diesem Auftrag.
