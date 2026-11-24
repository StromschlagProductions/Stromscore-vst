# Zeitmodell Teil 1a: gemeinsame Ganzzahlbasis und Notenansprüche

Ausgangspunkt `427a068`, Branch `develop/composition-core-prototype`.

Der erlaubte erste Zeitmodellschritt wird bewusst weiter geteilt: Dieser Commit führt die gemeinsame Einheit ein und migriert aktive Notenansprüche sowie die bereits vorhandenen PPQ-Grenzen. **Er ist keine vollständige Migration aller Planungsdaten.** Insbesondere bleiben Rasterindizes, Phrasen und Motivvarianten vorerst in ihren bisherigen Einheiten. Keine gebrochenen Akkorddauern, zusätzlichen Slots, neuen Einsätze, verändertes Swing oder neue harmonische Ereignisplanung.

## Entscheidung: 960 Ticks je Viertelnote

`MusicalTime.h` definiert eine vorzeichenbehaftete 64-Bit-Ganzzahl in einem expliziten `Tick`-Werttyp. Eine bisherige Sechzehntel-Rasterposition entspricht exakt 240 Ticks. `Tick` ist nicht implizit aus einer Ganzzahl konstruierbar; Rasterindizes müssen ausdrücklich mit `fromGridStep()` umgerechnet werden. Das verhindert in der migrierten Notenverwaltung versehentliche Vergleiche mit einem Rasterindex. Größe und Ausrichtung entsprechen weiterhin einer 64-Bit-Zahl, ohne zusätzliche Felder oder Allokationen je Anspruch.

Die Wahl wurde gegen alle vom Generator unterstützten Taktarten geprüft: Zähler 1–16, Nenner 1/2/4/8/16. Taktlänge = Zähler × 4 × 960 / Nenner. Alle Takte sowie deren Halb- und Viertelteilungen sind damit ganzzahlig darstellbar:

| Takt | ganzer Takt | halber Takt | Vierteltakt |
|---|---:|---:|---:|
| 4/4 | 3840 | 1920 | 960 |
| 3/4 | 2880 | 1440 | 720 |
| 6/8 | 2880 | 1440 | 720 |
| 3/8 | 1440 | 720 | 360 |
| 1/16 | 240 | 120 | 60 |

960 = 2⁶ × 3 × 5. Neben geraden Unterteilungen sind beispielsweise Achteltriolen (320), Sechzehnteltriolen (160) und fünf gleich große Teile einer Viertelnote (192) exakt darstellbar. Diese Möglichkeiten werden **nicht aktiviert**. Septolen bzw. beliebige rationale Unterteilungen sind nicht pauschal exakt darstellbar; künftige Anforderungen müssen dies ausdrücklich validieren, statt zu runden. Die Auflösung deckt die konkret benötigten Taktbruchteile vollständig ab und stimmt mit bestehender Motivaufnahme und SMF-Export überein; eine zweite feinere Ganzzahluhr ist daher nicht nötig.

## Tatsächlich migrierte Komponenten

- `Generator::Active`: Anfang und Ende jedes aktiven MIDI-Notenanspruchs sind jetzt `Tick`-Werte in 960 PPQ (`startTime`, `endTime`).
- `noteOn()`, `releaseDue()`, `cut()`, `releaseHeld()` und `releaseOthers()`: ausdrücklich umgerechnete Zeitwerte bei Vergleichen, Verlängerungen, Legato-Enden und geteilten MIDI-Kanalansprüchen. Vergleich und Notenbesitz behalten ihre bisherige Reihenfolge.
- `kStep` wird aus den gemeinsamen Konstanten 240/960 abgeleitet und bleibt exakt .25 Viertelnoten.
- Tatsächliche Pop/Rock-Motivaufnahme: 960-PPQ-Zeitstempel, Start, Zykluslänge und der Faktor 240 kommen nun aus der gemeinsamen Zeitquelle. Aufgezeichnete Werte, Swing und Motividentitäten bleiben erhalten. Es wird keine zweite Aufnahmeimplementierung eingeführt.
- SMF-Export: Auflösung und Umrechnung von Host-/Samplepositionen verwenden dieselbe Zeitquelle. Die bisherige Rundung zur nächsten ganzen Tickposition bleibt bestehen; positive Halbwerte werden wie zuvor von null weg gerundet.

Die aktiven Zeitwerte sind **nominale musikalische Zeitpunkte**, nicht nachträglich quantisierte Swing-Samplepositionen. Die Veröffentlichung ihrer MIDI-Ereignisse erfolgt weiterhin ausschließlich durch den bisherigen Scheduler.

## Verbleibende Repräsentationen

| Bereich | Gegenwärtige Einheit / Zweck |
|---|---|
| Rhythmische Figuren, `nowStep`, `Pos`, Szenen-/Phrasenpositionen, Zufallsschlüssel | Ganzzahlige Sechzehntel-Rasterindizes; noch nicht migriert. |
| `ChordTimeline`, Harmonie-/Bass-/freie Linienplanung, Motivfenster, Wiederkehr/Variationen | Bisherige Planung in Rasterindizes. Keine feineren Zeitpunkte. |
| Score-Motivmaterial und normalisierte Pop-Wiedergabefiguren | Relative Rasterwerte (`timeScale=1`). Diese sind nicht bereits 960-PPQ-Daten. |
| Tatsächlich aufgezeichnetes Pop-Material | Relative 960-PPQ-Werte, bestehender expliziter Maßstab 240 je Rastereinheit. |
| Host-PPQ / Swing-Verschiebung | Double an der Host-/Schedulergrenze, unverändert. |
| Blockoffset und Ausgabe | Ganzzahlige Samples. |
| MIDI-Datei | Ganzzahlige 960-PPQ-Zeitstempel. |
| Bestehender separater `Compiler`/`Plan`-Prüfpfad im Kern | `NoteSpan`-Grenzen und Planlänge bereits in ganzzahligen Samples, aus BPM/Samplerate kompiliert. Keine Migration dieses zusätzlichen Kern-Prüfpfads in diesem Teil. |

Diese Einheiten werden hier nicht durch beliebige neue Zwischenauflösungen ergänzt. Die noch benötigte Konvertierung Rasterindex→Tick liegt an der Ereignisverwaltungsgrenze. Planung und Ereignisauslösung behalten die bisherigen APIs; eine kommende Umstellung dieser APIs muss explizit erfolgen. Der neue Werttyp allein macht den Scheduler nicht fähig, Ereignisse zwischen zwei Rasterpositionen auszulösen.

Swing kann beliebige kontinuierliche Werte annehmen. Seine bisherige Double-Verschiebung wird deshalb in diesem Schritt nicht auf 960 PPQ gerundet: Das könnte bereits bestehende Samplepositionen verändern. `when = (k + swingDelay(k)) * kStep` und die Sample-Rundung bleiben unverändert. Die bereits vorhandene Aufnahme quantisiert dagegen weiterhin die tatsächlich gespielte Position auf 960 PPQ, genau wie zuvor.

Der bestehende Hostpositionsbereich bis |PPQ|=1e9 benötigt höchstens ungefähr 9.6e11 Ticks; das liegt deutlich innerhalb int64. Die Konvertierungsfunktionen erwarten gültige, begrenzte Eingaben entsprechend dem vorhandenen Transportvertrag. Nichtendliche Hostwerte werden weiterhin durch den bisherigen Generator-Eingang abgefangen. Das interne Szenenende-Sentinel bleibt in der nicht migrierten Planung und wird nicht als Notenanspruch multipliziert.

## Prüfungen

`MusicalTimeTests.cpp` prüft alle 80 unterstützten Taktarten, Halb-/Vierteltakt-Darstellbarkeit, ausgewählte Teilungsnenner, negative/positive Positionsgrenzen und eine Million ganzzahlige Fortschreibungen ohne Drift. Dazu kommen allokationsfreie Notenansprüche bei geteiltem MIDI-Kanal und wiederholtem Szenenstart/-stopp.

`compare_musical_time.py` vergleicht die vollständigen MIDI-Bytes gegen `427a068`. Alle 87 produktiven Wendungen in allen drei Profilen werden mit linearem und Seek-/Loop-/Neustart-Transport geprüft. Weitere Fälle kreuzen 4/4, 3/4, 6/8, 3/8, 90/120/173 BPM und Swing 0/.2/.5. Zwei zusätzliche Referenzwendungsfälle prüfen die vollständige Menge aller 80 unterstützten Taktarten auch anhand echter MIDI-Bytes. Motivbetrieb und beide melodischen Stimmen sind angefordert; bestehende Genre-Verfügbarkeiten bleiben maßgeblich. Zusätzliche 4096-Takt-Läufe prüfen Langzeitverhalten. Blockgrößen 127/480/512/8192 werden ergänzend verglichen; der bestehende Rundungsspielraum beträgt dort höchstens ein Sample bei sonst identischen Ereignissen. Der Vorher-/Nachher-Vergleich selbst ist bytegenau.

Die bisherigen Gesamttests für Motivwiederkehr, Transformationen, Bass, Harmonik, Notenbilanzen und Live-/SMF-Gleichheit bleiben zusätzlich aktiv. Die explizite Auswahl ist wie zuvor ein isolierter Testeingriff in kopierte Header, kein neuer Produktionsparameter.

## Nächste getrennt testbare Teile

1. **Motivdaten und deren Planungsgrenzen migrieren:** Aufgezeichnetes und normalisiertes Material auf eindeutig bezeichnete Zeit-/Rasterdaten umstellen. Identitätsbildung, Variationen, Mindestabstände, Kapazitätsgrenzen wie 4096 und alle Schwellen müssen dabei konsistent skaliert werden; ein bloßes Multiplizieren der Notenwerte wäre falsch. Zufalls- und Musterindizes bleiben getrennt, damit ihre musikalischen Ergebnisse erhalten bleiben.
2. **Planungspositionen migrieren:** `Pos`, `ChordTimeline`, Harmonie-, Bass- und Phrasenfenster sowie Szenengrenzen in dieselbe Tickbasis überführen. Rasterbasierte Regeln an ausdrücklich benannten Grenzen anbinden. Ganze Akkordtakte und acht Slots bleiben dabei zunächst erhalten.
3. **Scheduler-Schnittstelle entkoppeln:** Rhythmische Einsatzpositionen mit dem bisherigen Swing-Vertrag und harmonische Ereignisse mit eigener nomineller Tickposition zusammenführen; Priorität von Note-Off, gehaltenen gemeinsamen Flächentönen, Harmonieänderung und neuen Note-Ons ausdrücklich festlegen. Erst dann kann die Notenverwaltung ihre feinere Auflösung tatsächlich nutzen.
4. **Danach harmonische Dauern und Slotkapazität erweitern**, einschließlich exakter Vierteltakte in 3/8. Die aktuelle Vorbereitung allein aktiviert diese noch nicht.

Keine neue Legacy-Engine, keine neue GUI und keine harmonischen oder rhythmischen Vorlagen. Der hier verbleibende Rasteradapter ist ein ausdrücklich begrenzter Migrationsschritt, keine dauerhafte Parallelarchitektur.

## Abschlussprüfung

37/37 Gesamttests bestanden. Die zusätzliche Zeitregression liefert 973 bytegleiche vollständige Vorher-/Nachher-Renderings gegen `427a068`, einschließlich aller 87 produktiven Wendungen und vorhandenen Profile. 1353 zusätzliche Blockgrößenvergleiche bestanden mit maximal einem Sample Rundungsspielraum bei identischen Ereignissen; drei 4096-Takt-Läufe enthalten keine neue zeitliche Drift. Prüfsummen und Fallparameter stehen in `MUSICAL_TIME_REGRESSION.json`.

ASan/UBSan für `MusicalTimeTests` und bestehende `EngineTests` ohne Befund. 7/7 Paketprüf-Fixtures bestanden. Tatsächlicher Processor-Gesamttest einschließlich bestehender 54 Import-Live-/SMF-Fälle bestanden. Linux-VST3 erfolgreich gebaut und Bundle-/ELF-/Versionsmetadaten geprüft. Kein Windows-/pluginval-Lauf, kein Push und kein Release in diesem Auftrag.

## Teil 1b.1 – harmonische Zeitleiste und Übergangsplatzierung

Aufbauend auf `9745fbe`. Der zulässige Umfang wird nochmals geteilt: Dieser Schritt migriert den gemeinsamen harmonischen Positionsplan, nicht die gesamte Phrasen- und Motivverwaltung. Die obige Tabelle beschreibt den Ausgangsstand von Teil 1a; für die folgenden Komponenten ist sie jetzt ersetzt:

- `composition::ChordTimeline`: Phrasen-/Abschnittsfenster `begin/end` und alle Akkorddauern sind `musicaltime::Tick` mit 960 PPQ.
- `ChordPosition`: Beginn und Ende des gefundenen harmonischen Slots sind derselbe starke Zeittyp.
- `TransitionPlacement` und `placeTransition()`: Beginn/Ende, Taktlänge und die Position der letzten metrischen Gruppe sind nun Tick-Werte. Keine zeitliche Gleitkommaentscheidung im Planer.
- `Generator::locate()` und `motifHarmonyAt()` liefern ihre harmonischen Fakten an denselben migrierten Kern. Die harmonische Eignungsprüfung von Motivfiguren erhält damit dieselben Akkord-/Übergangsgrenzen wie die Live-Wiedergabe.
- Der Zeittyp besitzt Addition, Subtraktion und Ordnung ausschließlich zwischen Tick-Werten. Rasterindices werden nicht implizit konvertiert.

Der bisherige Aufrufer arbeitet noch mit Rasterindices. Deshalb werden dessen Grenzen am Eintritt mit `fromGridStep()` umgerechnet und an der Rückgabe mit `toExactGridStep()` wieder in die noch benötigte Einheit überführt. Diese begrenzte Brücke setzt exakt rastergebundene Werte voraus; ein Debug-Assert prüft diese Invariante. Sie ist kein Konverter für künftig frei eingegebene feinere Dauern. Alle produktiven Dauern bleiben ganze Takte, und die Slotanzahl bleibt acht. Der gemeinsame Planer selbst kann bereits etwa eine Grenze bei 360 PPQ-Ticks darstellen; der alte Scheduler darf damit noch nicht gespeist werden.

### Achtel-Taktarten und Tests

Gezielte Kernprüfungen für 3/8, 5/8 und 7/8 prüfen wechselnde Akkorddauern, Abschnittsanfänge und -enden sowie Positionen einen Tick vor und genau auf einer Grenze. Ein feineres Vierteltaktfenster wird ausschließlich im Kernplaner geprüft, ohne neue klingende Ereignisse zu aktivieren. Bestehende Haltelogik und Übergangsstrategien bleiben unverändert.

Die Zeitregression verwendet jetzt `9745fbe` als Basis. Zusätzlich zur vollständigen bisherigen Abdeckung kreuzt sie ausdrücklich 3/8, 5/8 und 7/8 mit Tempo, Swing, Transportwechseln, aktivem Motivbetrieb und verschiedenen Blockgrößen. Der tatsächliche Processor-Test veröffentlicht Host-Taktarten 3/8, 5/8 und 7/8 und vergleicht jede der drei importierten Wendungen in allen vorhandenen Profilen und beiden Follow-Zuständen mit dem SMF-Export. Notenenden werden einschließlich der abschließenden Note-Off-Bilanzen geprüft. Kein neuer GUI-Taktarteneintrag.

### Ausdrücklich noch im alten Raster

- `Generator::Pos` einschließlich globaler Phrasenanfänge/-enden, `nowStep`, Akkordgrenzen auf der noch nicht migrierten Adapterseite.
- Szenen-/Aufbau-/Endzustände und die zeitliche Historie tatsächlich gehörter Wendungsübergänge.
- Bassphrasen, freie Linienphrasen, Atempausen und rhythmische Einsatz-/Reservierungsfenster außerhalb der harmonischen Zeitleiste.
- Score-Motivspeicherung, normalisierte Wiedergabefiguren, Wiederkehrabstände, Varianten und Frage-/Antwortfenster. Die harmonische Zeitabfrage ist migriert, die übrigen Motivdaten noch nicht. Tatsächlich aufgenommenes Pop-Material bleibt wie schon zuvor in 960 PPQ und wird für die bisherige Wiedergabe normalisiert.
- Zufalls-/Musterindizes und der gesamte rhythmische Scheduler einschließlich Swing. Diese Indizes sind nicht durch bloßes Multiplizieren in Zeitstempel umzudeuten.
- Der samplebasierte `Compiler`/`Plan`-Prüfpfad bleibt unverändert.

Damit ist der ursprüngliche Auftrag **nicht als vollständige Planungsmigration abgeschlossen**. Als nächste klar getrennte Teilaufgaben verbleiben erst die Adapter-/Phrasenpositionen und anschließend die Motivdaten einschließlich Identitätsnormalisierung und Variationsschwellen. Eine direkte Skalierung würde unter anderem die bisherigen Mindestlängen, 4096-Grenzen und identitätsabhängigen Entscheidungen verändern. Erst danach folgt die separat beauftragte Scheduler-Entkopplung. Keiner dieser weiteren Schritte wurde hier begonnen.

### Abschlussprüfung Teil 1b.1

37/37 Gesamttests bestanden. 1117 vollständige Vorher-/Nachher-Renderings bytegleich zu `9745fbe`, einschließlich aller 87 produktiven Wendungen und aller vorhandenen Profile. 1785 zusätzliche Blockgrößenvergleiche bestanden; Prüfparameter und Prüfsummen in `MUSICAL_TIME_1B_REGRESSION.json`. Langzeitfälle umfassen 4096 Takte, weitere Fälle alle 80 unterstützten Taktarten und explizit 3/8, 5/8, 7/8. Tatsächlicher Processor: vorhandene 54 Live-/SMF-Fälle plus je 54 für die drei zusätzlichen Achtel-Taktarten bestanden; Notenbilanzen geschlossen. ASan/UBSan für MusicalTime, CompositionCore und Engine ohne Befund. 7/7 Paketprüf-Fixtures bestanden. Linux-VST3 erfolgreich gebaut und Bundle-/ELF-/Versionsmetadaten geprüft. Kein Windows-/pluginval-Lauf, kein Push und kein Release.

## Teil 1b.2a – globale Szenen-/Wendungszeiten und Adapterfenster

Ausgangspunkt `c85d888`. Dieser Auftrag wird erneut geteilt: Der zusammenhängende erste Teil betrifft **gespeicherte absolute Szenen-/Wendungspositionen und die Akkord-/Phrasenfenster des Adapters**. Motivspeicherung, Wiederkehr und Varianten werden hier ausdrücklich noch nicht umgestellt.

### Migriert

- `Generator::Pos` speichert `chordStartTime`, `chordEndTime`, `phraseStartTime`, `phraseEndTime` als gemeinsame 64-Bit-`Tick`-Werte in 960 PPQ. Aus der harmonischen Zeitleiste werden Akkordgrenzen unmittelbar als Tick übernommen. Temporäre lokale Phrasenfenster für die Wiedergabe geplanter Motivfiguren werden ebenfalls als Tick gespeichert; ihre noch rasterbasierten Eingaben werden ausdrücklich konvertiert.
- `sceneTime` ist der absolute Szenenbeginn, `wendungTime` der Beginn des laufenden harmonischen Abschnitts, jeweils in derselben Einheit.
- `sceneEndTime` und `manualEndTime` sind optionale Tick-Werte. Ein nicht angefordertes Ende ist **kein** riesiger oder negativer musikalischer Zeitstempel mehr. Die bisherigen Werte `-1` bzw. `1LL<<60` werden nur bei der Übergabe an noch nicht migrierte Rasterverbraucher rekonstruiert; sie werden nicht mit 240 multipliziert.
- Die gemeinsame harmonische Zeitleiste aus Teil 1b.1 bleibt die einzige harmonische Positionsberechnung. Keine zusätzliche Phrasen-/Harmonie-Engine und keine neuen Einsatzpositionen.

### Zeitpositionen und diskrete Indizes

`phraseIndex`, `Pos::phrase`, `bar`, `barInPhrase`, Slotnummern, Stimmen-/Ausgangsnummern sowie Muster- und Zufallsschlüssel bleiben diskrete Indizes. Beispielsweise ist die Nummer der achten Phrase nicht deren PPQ-Zeitpunkt. `Pos::k`, `nowStep` und metrische Rasterphasen gehören weiterhin zur alten Scheduler-/Musterseite. Deren heutige Sechzehntelstruktur wird durch diese Migration nicht verändert.

Explizite `gridChordStart/End`, `gridPhraseStart/End`, `sceneGrid`, `wendungGrid`, `manualEndGrid` und `sceneEndGrid` begrenzen die Rückgabe an noch rasterbasierte Verbraucher. Sie sind nicht implizite Operatoren des Zeittyps, und es gibt keine zweite gespeicherte Rasterkopie dieser migrierten Felder. Die bereits dokumentierte Exaktheits-Voraussetzung von `toExactGridStep()` gilt weiter. Diese Brücken müssen mit den nachfolgenden Verbrauchermigrationen wieder entfallen.

### Noch nicht migriert / Architekturprobleme

- `RememberedMotif`, `MotifUse`, normalisierte Notenfiguren, Wiederkehrphasen und -fenster, Varianten sowie musikalische Frage-/Antwortpläne verwenden noch ihre bisherigen Einheiten. Tatsächliche Pop-Aufnahmen besitzen weiterhin ihre schon vorhandenen 960-PPQ-Werte und `timeScale=240`; Score-/normalisierte Daten verwenden Rasterwerte. **Diese Einheitenmischung ist nicht behoben.**
- Die zeitliche Historie gehörter Wendungsübergänge (`HarmonicEntryRecord::begin`) ist noch rasterbasiert und enthält auch bestehende hashrelevante Eingaben. Szeneneinstiegs-/Ausstiegsmarkierungen der Ebenen, Drive-Abschnitte und weitere Hilfszustände bleiben ebenfalls im Raster.
- Bass- und Linienpläne, Atempausen, rhythmische Reservierungen und der Scheduler einschließlich Swing bleiben in diesem Schritt unverändert. Sie konsumieren die migrierten Grenzen über die expliziten Rasterbrücken.
- Bestehende Aufrufer-/Inspektionsfunktionen für Motive und Linien akzeptieren weiterhin Rasterindizes, teilweise noch mit historisch `tick` benannten Parametern. Auch diese APIs sind noch nicht vollständig einheitlich typisiert.
- Einige Ableitungen werden noch auf der Rasterseite gerechnet und danach als Tick gespeichert. Das schafft eindeutige Zustandsdaten, ersetzt aber noch nicht sämtliche zeitliche Rechnung durch PPQ-Rechnung.
- Die optionalen Endwerte benötigen geringfügig mehr festen Objektspeicher als die früheren Sentinel-Ganzzahlen; `std::optional<Tick>` benötigt keinen Heap. Die vier Adaptergrenzen ersetzen gleich breite 64-Bit-Felder. Inspektion und Test-Snapshots kopieren den Generator nur außerhalb der Audioverarbeitung.

Eine vollständige Motivmigration im selben Commit würde Identitätshashes, gespeicherte Rhythmen, Herkunftsreferenzen, Wiederkehrzähler und Grenzen der Transformationen gleichzeitig berühren. Es reicht nicht, Zahlenwerte zu skalieren: Mindestdauern und die bisherigen 4096-Grenzen sowie beide Bedeutungen von `timeScale` müssten mitmigriert und Identitäten ausdrücklich kanonisiert werden. Dies bleibt ein separater Teil. Dieser Commit wird daher **nicht als vollständiger Abschluss von Teil 1b.2** ausgewiesen.

### Prüfungen dieses Teils

Die gezielte Inspektion prüft bei 3/8, 5/8 und 7/8 tatsächliche gespeicherte Szenen-/Phrasen-/Akkordzeiten in 960 PPQ, mehrfachen Rücksprung, zwei Phrasen, exakte enthaltene Grenzen und optionale Szenenenden. Die bestehenden Motiv-, Varianten- und Antworttests bleiben aktiv und sichern unverändertes Verhalten ihrer noch nicht migrierten Daten.

Die vollständige Zeitregression verwendet `c85d888` als Basis und prüft weiterhin alle 87 produktiven Wendungen und vorhandenen Profile, Taktarten, Tempi, Swing, Seek/Loop, verschiedene Blockgrößen und 4096-Takt-Läufe. Die tatsächlichen Live-/SMF-Tests für 3/8, 5/8 und 7/8 bleiben Teil des Processor-Gesamttests. Es werden keine neuen musikalischen Regeln, GUI- oder Profiländerungen eingeführt.

Nächster abzugrenzender Teil ist die gemeinsame Motivdatenrepräsentation einschließlich Identitätsnormalisierung und ihrer zeitlichen Verwendung. Alternativ kann zunächst die restliche globale Übergangshistorie isoliert migriert werden. **Keiner dieser Folgeschritte wird hier eigenständig begonnen.**

### Abschlussprüfung Teil 1b.2a

37/37 Gesamttests bestanden. 1117 vollständige Vorher-/Nachher-Renderings bytegleich zu `c85d888`; 1785 zusätzliche Blockgrößenvergleiche bestanden. Details und Prüfsummen: `MUSICAL_TIME_1B2_REGRESSION.json`. Die Abdeckung umfasst alle 87 produktiven Wendungen, sämtliche vorhandenen Profile, alle 80 unterstützten Taktarten, insbesondere 3/8, 5/8 und 7/8, sowie 4096-Takt-Langzeitfälle. Die tatsächlichen 216 Processor-Live-/SMF-Fälle und der bestehende Processor-Gesamttest sind bestanden. ASan/UBSan für MusicalTime, CompositionCore und Engine ohne Befund. 7/7 Paketprüf-Fixtures bestanden. Linux-VST3 erfolgreich gebaut; Bundle-/ELF-/Versionsmetadaten geprüft. Kein Windows-/pluginval-Lauf, kein Push und kein Release.
