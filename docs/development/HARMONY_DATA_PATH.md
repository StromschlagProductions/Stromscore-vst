# Gemeinsamer validierter Harmonie-Datenpfad

Ausgangspunkt: `2322d6b`, Entwicklungsbranch `develop/composition-core-prototype`.
Keine neuen Wendungen, Akkordtypen, Profile oder musikalischen Auswahlregeln.

## Datenhoheit und Trennung

`data/harmony/` ist die einzige bearbeitete Quelle des ausgelieferten Katalogs:

| Datei | Inhalt |
|---|---|
| `chord_types.json` | Die bisherigen 18 Akkorddefinitionen einschließlich exakter Intervalle, Enumwerte und Reihenfolge der eigenen Akkordwahl. |
| `catalog.json` | 84 stabile IDs, Namen, relative Grundtöne, Akkordtypen, explizite relative Basstonklassen oder `null`, ganze Taktlängen, tonales Zentrum/Modus, statische XYZ-Anker, Genre-Eignung, Quellenreferenzen und geordnete Genre-Pools. |
| `arrangements.json` | Unabhängige, gemeinsam nutzbare Standardrezepte für die bisherigen Arp-/Bass-/Flächen-/Hook-Muster und ID-basierte Bindungen. Keine Instrumentenzuweisung. |
| `profiles.json` | Die drei vorhandenen Profilidentitäten und ihre ID-basierten harmonischen Präferenzgewichte. Fehlendes Gewicht bedeutet 1. |
| `notes.json` | Unveränderte redaktionelle Beschreibungen und Instrumentierungshinweise für die Anzeige, ohne ausführbare Routingwirkung. |

Eine harmonische ID kann in mehreren Genre-Pools stehen und beliebig viele Profile können dieselbe ID gewichten. Die bisherigen Genre-Reihenfolgen bleiben erhalten. Quellenreferenzen dokumentieren Herkunft; enthaltene historische Künstlernennungen sind keine verifizierten Stilzuweisungen. Die alten Quellen wurden übernommen, keine neue musikalische Forschung importiert.

## Validierung und Build

```sh
python3 scripts/generate_harmony_catalog.py
python3 scripts/generate_harmony_catalog.py --check
```

Der erste Befehl validiert zunächst alle Quellen und erzeugt anschließend deterministische, eingecheckte C++17-Header. Der zweite prüft ohne Änderungen, ob Quellen gültig und Ausgaben aktuell sind. CMake prüft beim Konfigurieren und im Build; ein falscher oder veralteter Katalog verhindert den Build. Python 3 ist damit eine Buildvoraussetzung, keine Plugin-Laufzeitabhängigkeit.

Geprüft werden insbesondere eindeutige IDs/Symbole, reservierte IDs, vollständige Felder, eindeutige JSON-Schlüssel, bekannte Akkorddefinitionen, Tonklassen 0–11, Bassdefinitionen, 1–8 Slots, positive ganze Taktlängen mit Summe 8, endliche statische XYZ-Werte in [0,1], Genre-/Pool-Konsistenz, Quellen-, Rezept- und Profilreferenzen sowie positive darstellbare Profilgewichte. Unbekannte Akkordnamen werden abgewiesen, niemals angenähert. Ein Semantikfingerabdruck schützt die bestehenden 18 Akkordformen vor versehentlicher Umdefinition; echte neue Typen benötigen einen gesonderten Engine-Schritt.

Ein expliziter Modus wird gegen den gesamten Akkord- und Bassvorrat geprüft. `automatic` erhält die bisherige laufzeitseitige Moduserkennung; alle bestehenden Einträge verwenden unverändert Zentrum 0/automatic. Ein Slash-Bass muss nicht selbst Akkordton sein, beispielsweise B-Dur über C im deutschen Sprachgebrauch (Bb/C). `null` bedeutet keine gesonderte Bassvorgabe; die Benutzereinstellung „Folgt Akkorden“ bleibt unverändert.

Potenzielle Dubletten werden über acht harmonische Takte einschließlich Bass, unter Berücksichtigung zyklisch verschobener Startphasen, gefunden. Acht bestehende Gruppen werden in `HARMONY_DATA_VALIDATION.json` gemeldet. Keine transpositionsübergreifende Analyse und kein Urteil über die musikalische Gleichwertigkeit unterschiedlicher Einstiegsphasen/Strategien. Keine automatische Zusammenlegung oder Änderung von IDs.

## Laufzeit und Skalierung

`HarmonyTypes.h` definiert die reinen harmonischen Daten. `HarmonyCatalog.generated.h` enthält statische Vorlagen und eine binäre ID-Suche. `HarmonyStrategies.generated.h` enthält getrennte Standardrezepte/Pool-Indizes; `HarmonyPreferences.generated.h` die Profilgewichte; `ProfileIdentity.generated.h` die Profilidentitäten. `WendungId.h`, `ChordTypes.generated.h` und `WendungInfo.h` werden ebenfalls aus denselben Quellen erzeugt.

`HarmonyRuntime.h` erzeugt daraus zur Compilezeit die kompakten Wiedergabeansichten für den vorhandenen Renderer. Es gibt keinen zweiten handgepflegten Katalog, keine zweite Engine und keinen Loader im Plugin. Die Modusmetadaten werden bereits in `Generator::modalContextFor()` verwendet. Auswahlformel, XYZ-Abstände, Variety und Profilgewichte bleiben unverändert.

Die feste 64er-Grenze ist entfernt: temporäre Kandidatenfelder erhalten ihre Größe aus den tatsächlich generierten Genre-Pools. Der Custom-Sentinel liegt mindestens hinter allen Katalogindizes (bei kleinen Pools weiterhin 1000). Dieser Wert begrenzt keine Kataloggröße. Grenzen ergeben sich aus darstellbaren IDs/Indizes und realem Speicher bzw. Rechenbudget, nicht aus einer weiteren festen musikalischen Obergrenze.

Alle Laufzeitdaten sind unveränderlich und statisch. Keine Dateioperationen, Validierungen oder neuen Heap-Allokationen im Audiothread. Auswahl bleibt eine lineare Pooldurchmusterung mit binärer Präferenzsuche je Kandidat; Stack-Scratch-Speicher wächst linear mit dem größten Pool. Der synthetische Test mit 1284 Vorlagen, 1248 Score-Kandidaten und 40 Profilen prüft Auswahl oberhalb Index 1000 und allokationsfreie Verarbeitung. Das ist ein Skalierungsnachweis, kein universelles Echtzeitbudget für beliebig große Kataloge. Sehr große zukünftige Sammlungen benötigen zusätzlich Worst-Case-Laufzeitmessungen und gegebenenfalls vorbereitete Auswahlindizes.

## Bestehende Grenzen und nächste kleine Schritte

1. **Vorlagengetreue Akkordfarbe:** Die bestehende automatische Färbung (`padType`) darf weiterhin abhängig von Unruhe Akkordqualitäten verändern. Der Datenpfad unterstützt deshalb zunächst ausdrücklich nur das unveränderte Rezept `coloration: free`; `literal` wird abgewiesen. Vor einem musikalisch verbindlichen Import eine kleine, getestete Strategie für unveränderte bzw. erlaubte Akkordfarben anschließen. Sie muss auch Bassanker, Moduserkennung und charakteristische Sus-/Quintklänge konsistent behandeln.
2. **H01/H11/H19 einzeln importieren:** Nach diesem Farbschutz benötigen diese drei Vorlagen weder neue Akkordtypen noch kürzere Slots: H01 = C(2), Bb(2), F/A(2), Csus2(1), C(1); H11 = Cm7(2), F/C(2), Cm7(2), F/A(1), Bb(1); H19 = C5(6), Ab5(1), Bb5(1). Mixolydisch bzw. dorisch lassen sich explizit validieren; die Quintfolge erlaubt allein keine eindeutige Mollterzannahme. Für jeden Import stabile neue ID, geprüfte Quelle, statische vorläufige XYZ-Anker und beide Follow-Zustände prüfen. Kein automatischer Import von Tempo-, Bassrhythmus-, Motiv- oder Dramaturgieanweisungen aus der Untersuchung.
3. **Weitere Vokabulare separat prüfen:** H01/H11/H19 sind hier nur Voraussetzungenbeschreibungen, keine ausgelieferten Einträge. Halbtaktwechsel, mehr als acht Slots, neue Akkordtypen sowie dynamische XYZ-Verläufe werden weiterhin ausdrücklich abgewiesen und benötigen unabhängige Engine-/Schema-Schritte.
4. **Verbleibende bestehende Sonderstrategie:** Drei bereits vorhandene Drahtseil-ID-Prüfungen im Generator bleiben zum Schutz des musikalischen Verhaltens bestehen. Vorlagenübergreifende Verallgemeinerung dieser Schutzregel ist ein späterer kleiner Strategieschritt; sie wurde nicht in harmonische Fakten oder neue Künstlerlogik eingebaut. Die bisher ID-basierte Hook-Zuordnung ist bereits in gemeinsame Rezeptdaten überführt.

## Nachweise

`HARMONY_DATA_REGRESSION.json` enthält alle 504 Vergleichsergebnisse gegen `2322d6b`: jede der 84 Wendungen, alle drei Profile, linearer Transport sowie Seek/Loop/Neustart, jeweils 64 Takte mit vollständigen Note-/CC-Ereignissen. Alle Ausgaben und vollständigen Katalog-/Akkord-/Rezept-/Gewichts-/Anzeigefakten stimmen bytegenau überein. Weitere 1008 Vergleiche mit Blockgrößen 127 und 8192 stimmen mit 512 überein. Die Probes schneiden Blöcke an Takt- und Testschnittgrenzen ab. Das ersetzt nicht beliebige Tests sämtlicher DAW-Blockteilungen.

Gezielte Tests: `HarmonyCatalogTests.cpp`, `HarmonyDataTests.py` (fehlerhafte Quellen, Reproduzierbarkeit, gemeinsam verwendete Einträge, großer kompilierter Katalog), `compare_harmony_data.py` und der vorhandene Gesamt-/Processor-Testbestand. Der große synthetische Test lässt sich mit `HARMONY_TEST_SANITIZE=1 ASAN_OPTIONS=detect_leaks=0 python3 Tests/HarmonyDataTests.py HarmonyDataTests.test_large_shared_catalog_compiles_and_selects` unter ASan/UBSan ausführen. Es werden dadurch keine neuen produktiven Vorlagen oder Profile angelegt.

Abschlussprüfung: 30/30 CTest-Gesamttests bestanden (einschließlich bestehender Regressionen und neuer Datenpfadtests); Processor-Test mit Live-/Export- und Heap-Prüfungen bestanden; drei separate ASan/UBSan-Läufe für HarmonyCatalog, HarmonicProfile und Engine sowie der große synthetische Katalog ohne Befund; 7/7 Paketprüf-Fixtures bestanden. Linux-VST3 erfolgreich gebaut und Bundle/ELF/Versionsmetadaten geprüft. Kein Windows-Build oder pluginval-Lauf in diesem Auftrag, kein Releasepaket erzeugt. Die MIDI-Regressionszusammenfassung enthält 504 bytegleiche Vorher-/Nachher-Läufe und 1008 zusätzliche bytegleiche Blockgrößenvergleiche.
