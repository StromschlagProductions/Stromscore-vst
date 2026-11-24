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

## Teil 1b.2b – Zusammenhängender Motivkern (Basis `7496c47`)

Die oben für Teil 1b.2a beschriebene Einheitenmischung ist in diesem Teil aufgehoben. Score-Material, aufgenommene Pop-Noten und nominale Varianten verwenden denselben expliziten 64-Bit-Typ `musicaltime::Tick` mit 960 PPQ. `timeScale` und die genreabhängige Einheit von `originTick` entfallen; der Ursprung heißt jetzt `originTime`. Kein zweiter Motivspeicher und keine Rückrechnung des gesamten Materials in ein Rasterformat.

### Musikalische Bedeutung der Daten

| Daten | Bedeutung / Einheit |
| --- | --- |
| `RememberedMotif::Note::at`, `MotifFigure::notes[].at` | Relative Position ab Motivbeginn, Tick |
| `Note::length`, `MotifFigure::span`, `cycleLength` | Dauer, Tick; die aufgenommene Zyklusdauer enthält auch Schlussstille |
| `MotifUse::originTime`, `MotifReferencePlan::originTime` | Absolute Position auf der gemeinsamen musikalischen Zeitleiste, Tick |
| `MotifCapture::begin/end`, `MotifOccurrence::begin/end`, `MotifPlacement::begin` | Absolute Aufnahme-/Wiederkehrpositionen, Tick |
| `MotifHandoffPlan::begin/end` | Relative Grenzen ab `PlayableHandoff::origin`, jeweils Tick |
| `DialoguePlan::answerBegin/answerEnd`, `MotifWindow::begin/end` | Absolute Antwort-/Reservierungsgrenzen, Tick; Ende exklusiv |
| `recurrenceOrigin`, `recurrenceWindow`, `HarmonicEntryRecord::begin` | Absoluter Bezug, Fensterdauer bzw. historische Übergangsposition, Tick |
| `introduction`, `recurrenceEpoch`, `ordinal`, `first`, `count`, Noten-/Musterindex | Dimensionslose Abschnitts-, Wiederkehr- oder Ereignisnummern, unverändert ganzzahlig |

Positionen und Dauern teilen bewusst denselben gemeinsamen Zeittyp, ihre unterschiedlichen Bezüge sind in Feldern, Schnittstellen und dieser Tabelle festgelegt. Es gibt keine implizite Ganzzahl-zu-Tick-Konvertierung. Insbesondere wird eine Abschnittsnummer nicht als PPQ-Position interpretiert.

**Normalisierte Vorlagen sind keine absoluten Sechzehntelnoten:** `Motif::on[]` beschreibt dimensionslose Sechzehntel **eines Taktes**. `motifTemplatePosition()` realisiert diese Anteile mit der tatsächlichen Taktlänge und der bisherigen Abrundung aufs Spielraster. Beispiel: Anteil 4 entspricht in 3/8 rechnerisch 360 PPQ; die bisherige Spielregel realisiert 240 PPQ. In 5/8 sind es 600 → 480, in 7/8 840 → 720 PPQ. Diese bewusst erhaltene Quantisierung verhindert neue Einsatzpositionen; die tatsächlich realisierten Positionen werden anschließend in PPQ gespeichert. Bereits gespeicherte Noten und abgeleitete Varianten werden nicht erneut taktproportional skaliert. Feinere Einsätze bedürfen einer späteren Scheduler-Arbeit und sind hier nicht aktiviert.

### Aufgenommenes Pop-Material und Swing

Die Aufnahme erfasst weiterhin tatsächlich ausgegebene Note-ons/-offs einschließlich Swing und Sample-zu-PPQ-Rundung. `performedTiming` bezeichnet ausschließlich diesen zeitlichen Bezug, **keine alternative Einheit**. Für die vorhandene Hook-Wiedergabe rekonstruiert `performanceMaterial()` daraus nominale PPQ-Positionen unter Verwendung des aufgenommenen Swing-Werts; die bisherige Performance-Schicht wendet Swing wie bisher an. Originalaufnahme und publizierter Katalog bleiben unverändert. Es wird weder eine zweite Motiv-Engine noch ein normalisiertes Raster-Speicherformat verwendet.

Der Identitätshash enthält relative PPQ-Positionen, Dauern, Intervalle und die explizite Zyklusdauer; Capture-Herkunft, Stimme, Transposition und frühere Speicherskala sind keine Identitätsmerkmale. Die internen Hashwerte ändern sich gegenüber älteren Commits. Sie sind keine Seed-Eingaben für die Notenwahl. Gleiches Material mit gleicher Zyklusdauer erhält unabhängig vom Beobachtungs-/Aufnahmepfad dieselbe Identität. Die Wiederkehrreferenz bleibt bei einer nominalen Performance-Ableitung die Identität des tatsächlich aufgenommenen Originals.

### Migrierte Verbraucher und entfernte Brücken

- Identitätsbildung, Aufnahme, unveränderlicher Katalog, Stimmenreferenzen, Originalwiedergabe sowie rhythmische Variation, Fragment, Sequenz und Augmentation rechnen in PPQ.
- Wiederkehrfenster, Kandidaten, Mindestpausen, Variantenlängen, Harmonieprüfung und Antwortpläne verwenden PPQ. Harmonieabfragen gehen unmittelbar an `ChordTimeline`; die frühere Raster-Rückgabe von `motifHarmonyAt()` entfällt.
- Die unmittelbar abhängige Durchgangstonplanung verwendet ebenfalls Tick-Positionen/-Dauern. Die ausgeklammerte Bassplanung konvertiert ausschließlich an ihrem Aufruf dieser gemeinsamen Funktion.
- Arpeggio-Motivreservierungen sind als direkte Verbraucher ebenfalls Tick-Fenster. Ihre vormals erforderlichen PPQ→Raster→PPQ-Brücken entfallen. Die eigentliche rhythmische Verzahnungsplanung bleibt unverändert.
- Motivnoten geben ihre Tick-Enden unmittelbar an die bereits migrierten aktiven MIDI-Notenansprüche. Der alte `noteOn(...endStep...)`-Einstieg bleibt nur für noch rasterbasierte Stimmen; er konvertiert einmal an dieser Grenze.
- Phrasen-/Harmoniegrenzen in `locate()` werden nicht mehr unnötig von Tick ins Raster und zurück gerechnet. Die Wendungsübergangshistorie speichert Tick. Ihr Cache-Schlüssel verwendet ausdrücklich die bisherige diskrete Ereignisnummer, um dessen Verhalten zu erhalten.
- Mindestartikulation, Legatoüberhang und bestehende rhythmische Halbierung bleiben musikalisch auf ihrem bisherigen Sechzehntel-Quantum (240 PPQ). Insbesondere halbiert eine rhythmische Variante eine ungerade Rasterlänge weiterhin abgerundet; eine Migration darf nicht beiläufig neue Halbrasterpositionen erzeugen.

### Verbleibende Rasterabhängigkeiten / Grenzen

**Teil 1b.2 ist für den zusammenhängenden Phrasen-/Motivbereich abgeschlossen; die gesamte Engine ist noch nicht vollständig migriert.**

1. Scheduler, `nowStep`, `Pos::k`, `Meter::len/pos`, Swing-Rasterphase und die metrische Einsatzabfrage bleiben auf dem bestehenden Sechzehntel-Spielraster. Die read-only Inspektion `inspectMotifOccurrence(step,...)` nimmt ebenfalls einen Scheduler-Schritt entgegen und liefert einen PPQ-Plan. Nominale Pop-Aufbereitung benutzt das bisherige Raster nur zur Inversion der vorhandenen Swing-Performance; keine neue Swing-Regel.
2. Bass-/freie Linienpläne einschließlich Atempausen, `pendingAt/pendingEnd`, Basspaar-/Dispositionpositionen, rhythmische Verzahnungspläne, Szeneneintritts-/Ausstiegsmarker und Drive-Hilfszustände bleiben außerhalb dieses Auftrags. Die bestehenden `gridChord*`, `gridPhrase*`, `sceneGrid` usw. dienen nur ihren verbleibenden Verbrauchern.
3. Instrumentenfähigkeits-/Rollenanforderungen (`minDuration/maxDuration`) sind weiterhin in ausdrücklich dokumentierten Sechzehntel-Einheiten konfiguriert. Die Durchgangston-Policy selbst ist bereits auf Tick-Dauern umgestellt. An der Motiv-/Durchgangston-Grenze werden aus den Instrumentengrenzen Tick-Dauern; die eigentlichen Pläne speichern keine Rasterkopien. Eine Umstellung des gesamten Fähigkeits-/Policy-Katalogs ist hier nicht erfolgt.
4. Die Motiv-Vorabprüfung muss für die noch rasterbasierte Adapterposition `locate(step)` einmal exakt an dessen Grenze konvertieren. Neue feinere Figuren werden produktiv weiterhin nicht erzeugt. Die reinen Motiv-/Antwortplaner und die Aufnahme können dagegen auch nicht rastergebundene PPQ-Grenzen exakt darstellen; dafür gibt es gezielte Tests.
5. Bestehende Grenzen des Verhaltens bleiben bestehen: acht Quellnoten, begrenzter Szenenkatalog, bisherige Wiederkehr-/Antwortbedingungen und der bekannte kalte-Seek-Kontext der Übergangsstimmführung. Keine neuen Kompositionsregeln und keine Ausweitung der Antwortfunktion auf weitere Taktarten.

Es gibt keine neuen Heap-Allokationen, Dateizugriffe oder Laufzeitvalidierungen im Audiothread. Die gespeicherten Motivzeitfelder ersetzen gleich breite 64-Bit-Zahlen; der bisherige Skalenparameter entfällt. Auf dem geprüften Linux-x64-Build bleiben `Generator` (15176 Byte), `RememberedMotif` (232), `MotifUse` (256) und `MotifOccurrence` (312) gleich groß. Die auf 64-Bit-Dauern umgestellte `PassingPolicy` wächst von 24 auf 32 Byte; `Settings` wächst einschließlich Ausrichtung von 1060 auf 1080 Byte. Das ist fester Konfigurations-/Stack-Speicher, kein zusätzlicher Heap im Prozesspfad. Audio-/Hostpositionen und Sampleoffsets bleiben Grenzrepräsentationen.

### Nachweise

`MotifTimeTests` prüft gemeinsame Identität von Beobachtung und tatsächlicher Aufnahme, exakte nicht rastergebundene PPQ-Noten und Dauern, große absolute Positionen, unveränderliche Originale, Augmentation, unabhängige Stimmenreferenzen, Wiederkehr-/Antwortfenster und exklusive Reservierungsenden. Für 3/8, 5/8 und 7/8 werden jeweils Score und explizit phrasenbezogene Pop-Hooks über 128 Takte einschließlich Rücksprüngen und Neustart geprüft. Die übrigen Pop-Tests decken unverändert kontinuierliche Hooks und tatsächlich ausgegebene Aufnahme-/Notenendzeiten ab.

Historische Analyse-Probes geben ausschließlich für ihre bestehenden Berichte weiterhin Sechzehntel-Anzeigeeinheiten aus (`tools/TimeDiagnostics.h`); das ist kein Laufzeit-Speicheradapter. Historische Vergleiche prüfen Noten-/Rhythmus-/Dauerdaten statt unzulässig alte und neue interne Identitätshashes gleichzusetzen. Identitätskonstanz und Quellenbezug innerhalb eines Renderings bleiben vollständig geprüft. Vollständige MIDI-Bytevergleiche bleiben unverändert streng.

### Abschlussprüfung Teil 1b.2b

Alle 38 Gesamttests bestanden: 36 im Gesamtlauf und die zwei historischen Hook-/Modal-Vergleiche nach Umstellung ihres versionsübergreifenden Hashvergleichs im gezielten Wiederholungslauf. Dabei bleiben die vollständigen aufgenommenen Noten-/Rhythmus-/Dauerdaten und die MIDI-Bytevergleiche geprüft; aktuelle Identitäten werden innerhalb derselben Implementierung weiterhin strikt verglichen.

1117 vollständige Renderings sind bytegleich zur Basis `7496c47`; 1785 Blockgrößenvergleiche bestanden. Vollständige Fallliste/Prüfsummen: `MUSICAL_TIME_1B2B_REGRESSION.json`. Die bisherigen Renderings bei nicht ganzzahligen Samplepositionen erlauben wie zuvor höchstens einen Sample Unterschied zwischen Blockgrößen, bei unveränderter Ereignisfolge und sämtlichen übrigen MIDI-Daten. Die identischen Vorher-/Nachher-Konfigurationen werden ohne Toleranz byteweise verglichen. Alle 87 produktiven Wendungen, alle vorhandenen Profile, sämtliche 80 unterstützten Taktarten und die bestehenden 4096-Takt-Langzeitfälle sind enthalten. Es war keine musikalische Verhaltenskorrektur erforderlich.

ASan/UBSan für MusicalTime, MotifTime, CompositionCore und Engine bestanden (`detect_leaks=0`, keine LeakSanitizer-Aussage). 7/7 Paketprüf-Fixtures bestanden. Der echte Processor-Gesamttest einschließlich 216 Live-/SMF-Fällen in 4/4, 3/8, 5/8 und 7/8 ist bestanden; der Großblocktest meldet 872 Note-ons, 872 Note-offs und keine Notenverwaltungsfehler. Linux-x64-VST3 gebaut, ELF/Bundle und Versionsmetadaten 2.2 geprüft. Kein Windows-/pluginval-Lauf, kein Push, kein Release.

## Teil 1b.3 – Bass, freie Linien, Rhythmus und Instrumentendauern

Basis `cb25399`, Branch `develop/composition-core-prototype`. Dieser Teil vervollständigt die angeforderte **Datenmigration der musikalischen Planer und ihrer unmittelbar zugehörigen Verbraucher**. Er führt keine neue musikalische Strategie ein und beginnt die Scheduler-/Swing-Entkopplung aus Teil 2 nicht.

### Migrierte Daten und Verbraucher

| Bereich | Musikalische Zeitwerte in 960 PPQ | Weiterhin dimensionslos |
| --- | --- | --- |
| Bass | `BassAttack::duration`; `BassPhraseRequest::begin/middle/end/barDuration/minDuration/maxDuration`; `BassPhrasePlan`-Grenzen, Notenanfänge und -längen | Funk-Musterplatz, Tonhöhenintervalle, Noten-/Akkordindex, Auflösungsreferenz |
| Freie Linien | `LinePhraseRequest::begin/end/pulse`; `LinePhrasePlan::begin/end/arrival/breath`, alle Notenanfänge/-enden | Tonleiterindex, Zieltonklasse, Anzahl der Phrasentöne, Konturentscheidung |
| Rhythmische Verzahnung | `RhythmPlanRequest::subdivision/minDuration/maxDuration`; `RhythmPlan::Onset::at/source/length` | `bar` ist eine Taktnummer; Referenz-/Bewegungs-/Ergebnismasken und ihre 16 Musterplätze sind keine Zeitstempel |
| Instrumente / Rollen | `InstrumentCapabilities` und `RoleNeed::minDuration/maxDuration`; der gemeinsame MIDI-Zielkatalog liefert direkt Tick-Dauern | Polyphonie, Artikulationsbits, MIDI-Ziel und Rolle |
| Hilfszustände | Basspaar-Anfang, Vorhaltsbeginn/-ende, gespeicherter Besetzungszeitpunkt, Hysterese-Beginn, Szeneneintritt und Ausklanggrenzen | Cache-/Zufallsschlüssel, Szenen-/Aufbautaktzahl, Drive-Generation und normalisierter Drive-Fortschritt |
| Neutrale Texture-Policy | `autoArpeggioDuration()` liefert eine musikalische Tick-Dauer | Aktivitätsschwellen, Hysterese-Taktanzahl und Musterwahl |

Absolute Positionen sind unter anderem Bassnotenanfänge, Phrasengrenzen, Atempausenbeginn und Vorhaltszeiten. `RhythmPlan::Onset::at/source` sind dagegen **relative Positionen innerhalb eines Musterzyklus**; `length`, `pulse`, `subdivision` und Instrumentengrenzen sind Dauern. Alle verwenden den gemeinsamen starken `Tick`-Typ, ohne implizite Ganzzahlkonvertierung. Bar-/Muster-/Notennummern werden nicht durch numerisches Skalieren als Zeitstempel ausgegeben.

Die bestehenden musikalischen Konstanten bleiben erhalten: eine Sechzehntelnote = 240 PPQ, eine Viertelnote = 960 PPQ. `musicaltime::sixteenth/quarter` benennen diese Dauern ausdrücklich. Der Bass-Funkplan behält seine vorhandenen Einsatzplätze und seine bisherige 4/4-Eignungsprüfung. Die Linienplanung behält das bestehende Legato-/Absetzmaß von einer Sechzehntelnote und dieselbe Phrasenkontur. Bei 3/8, 5/8 und 7/8 wird keine bislang ungeeignete Bassstrategie neu freigeschaltet.

### Entfernte Rasterbrücken

- Bass- und Linienplaner nehmen ihre harmonischen und globalen Abschnittsgrenzen direkt als Tick entgegen. Ihr Ergebnis wird einschließlich Notenenden unmittelbar an die Tick-basierte Notenverwaltung übergeben.
- Der Bassplan ruft die gemeinsame Durchgangstonplanung ohne die bisherigen Raster→Tick-Konvertierungen auf. Motiv-, Bass-, Linien- und Instrumenten-Dauerprüfungen teilen jetzt dieselbe Einheit.
- Instrumentengrenzen werden nicht mehr an jedem Motiv-/Rhythmus-/Bassverbraucher mit 240 multipliziert. Auch die Standardbelegung aller neun Ziele enthält bereits musikalische Tick-Dauern.
- Die rhythmische Verzahnung erzeugt Tick-Einsätze und -Dauern aus dimensionslosen Bitmasken und einer ausdrücklich benannten Unterteilungsdauer. Ihre Suche `RhythmPlan::at()` erwartet einen Tick-Offset.
- `bassPairStart`, `pendingAt` und der gespeicherte Besetzungszeitpunkt verwenden optionale Tick-Positionen statt negativer Raster-Sentinels. `pendingEnd`, Hysterese- und Ausklangzeiten verwenden Tick. Ein fehlender Szeneneintritt wird als fehlender optionaler Zeitpunkt dargestellt, statt als extrem weit zurückliegender Rasterwert.
- `sceneGrid()`, `wendungGrid()`, `manualEndGrid()` und `sceneEndGrid()` sind entfernt. Szenenenden und Anwesenheitsprüfungen verwenden die bestehenden optionalen Tick-Werte direkt. Der harmonische Übergangsaufruf in `locate()` verliert ebenfalls seinen unnötigen Tick→Raster→Tick-Umweg.
- Gehaltene Harmonie und Bass geben ihre harmonischen Notenenden direkt als Tick weiter. `noteOn`, `cut` und `padChord` besitzen weiterhin ausdrücklich begrenzte Aufrufe von der noch rasterbasierten Ausführungsseite; dort wird einmal konvertiert. Es werden keine parallelen gespeicherten Rasterkopien der migrierten Planungszeiten geführt.

Die Zustandsmigration verändert weder die Ausdünnungsentscheidung noch Anschlagsstärken, harmonisches Material, Motive, Rollenpriorität oder Komponistengewichte. Instrumentengrenzen bleiben dokumentierte Standardannahmen des Generators; die tatsächlichen Fähigkeiten eines extern geladenen Patches werden dadurch nicht bekannt.

### Arbeitet danach die gesamte musikalische Planung unabhängig vom Ausführungsraster?

**Nein, noch nicht der gesamte Generator.** Die Daten und Schnittstellen der zusammenhängenden Harmonie-, Motiv-, Bass-, freien Linien-, Antwort- und rhythmischen Einsatzplaner sind nun PPQ-basiert. Die reinen Planer können passende nicht rastergebundene Tick-Grenzen darstellen. Daraus folgt aber noch keine unabhängige produktive Ereignisplanung: Der Adapter ruft sie weiterhin aus dem alten Sechzehntel-Scheduler auf und leitet an mehreren Stellen Metrik, Musterfortschritt und Ereignisauslösung aus dessen Schrittindex ab.

Die vorhandenen Sechzehntel-Funkfiguren und Bitmasken bleiben musikalisches Vokabular; ihre Rasterung ist nicht automatisch ein fehlerhafter Zeittyp. Entscheidend ist die noch bestehende Kopplung ihrer Realisierung und Veröffentlichung an `k/nowStep`, `Pos::pos` und den Scheduler. Neue feinere Einsätze werden in diesem Teil ausdrücklich nicht erzeugt.

### In Teil 2 aufzulösende Abhängigkeiten

1. **Ausführungsuhr und Eintritt in die Planung:** `process`, `stepOn`, `chase`, `locate(step)` und die read-only Inspektionsaufrufe arbeiten noch mit Scheduler-Schritten. `Meter::len/groupStart` beschreibt weiterhin dessen Raster. Tick-basierte musikalische Positionen und metrische Gruppen müssen ohne Rückrechnung in alte Ausführungsschritte bereitgestellt werden.
2. **Ereigniserzeugung und Notenenden:** Zahlreiche unmittelbar gerenderte Begleit-/Akzent-/Hook-Muster entscheiden ihre Einsätze noch über `p.pos`, `% rate`, `gridChord*` und `gridPhrase*`. Auch die verbleibenden Step-Aufrufe von `noteOn/cut/padChord`, `releaseDue` und `releaseOthers` müssen an einen gemeinsamen Tick-Ereignispfad angeschlossen werden. Die gespeicherten Notenansprüche sind schon Tick-basiert; ihre Veröffentlichung wird noch nur an Ausführungsschritten geprüft.
3. **Swing getrennt behandeln:** Die bisherigen Double-Swing-Positionen und die Abbildung auf Samples dürfen nicht beiläufig auf PPQ gerundet werden. Rhythmische Performanceverschiebung und nominale Harmonieposition benötigen getrennte Behandlung. Die vorhandene Pop-Aufbereitung invertiert die aufgezeichnete Swing-Performance weiterhin anhand der bisherigen Musterplätze; sie speichert dabei ausschließlich PPQ-Daten.
4. **Seek/Loop und konkurrierende Noten:** Der Chase der rhythmischen Verzahnung konvertiert ihre Tick-Einsätze noch ausdrücklich an die bestehende Swing-/Arpeggio-Ausführungsschnittstelle. Der Bass-Chase benötigt den bisherigen diskreten Ereignisindex noch für metrische Akzente und deterministischen Jitter. Freigabe alter Ansprüche, Harmonieänderung, gehaltene gemeinsame Töne und neue Note-ons benötigen eine klar definierte gemeinsame Ereignisreihenfolge auch zwischen alten Rasterpositionen.
5. **Muster- und Zufallsindizes erhalten:** Arpeggio-Tonfolge, Jitter und manche Akkordlagen nutzen bisher aus Rasterpositionen abgeleitete Schlüssel. Diese dürfen nicht durch einen bloßen Wechsel von 1 auf 240 verändert werden. Bei der neuen Ereignisplanung sind ausdrücklich definierte Ereignis-/Musterordnungen erforderlich; derzeit verbleiben dafür exakte Tick→Schritt-Grenzen.
6. **Taktbezogene Vorlagen und vorhandener Prüfpfad:** Die bereits dokumentierte Abrundung normalisierter Motivvorlagen auf die bisherige musikalische Rasterung bleibt erhalten. Eine spätere feinere Realisierung ist eine gesondert zu prüfende Verhaltensänderung. Der bestehende zusätzliche `Compiler/Plan`-Prüfpfad speichert kompilierte Ausgabe in Samples; das ist eine Ausgabedarstellung, keine zweite musikalische PPQ-Uhr. Seine Rolle gegenüber dem produktiven Ereignispfad sollte in Teil 2 geklärt werden.

Die bestehende Einschränkung der harmonischen Übergangsstimmführung bei kaltem Seek bleibt unverändert. Keine neue Form-, Artikulations- oder Orchestrierungsengine und kein weiterer eigenständig begonnener Entwicklungsschritt.

### Gezielt ergänzte Nachweise

`PlanningTimeTests` prüft die starken Zeittypen, eine Bassphrase ab einer großen nicht rastergebundenen Position, Akkordgrenzen, Tonvorrat und Instrumenten-Dauergrenzen einschließlich Abweichungen von genau einem Tick. In 3/8, 5/8 und 7/8 werden freie Linien mit passenden PPQ-Pulsen sowie relative rhythmische Einsätze mit einer nicht an 240 gebundenen Unterteilungsdauer geprüft. Die bisherigen Eignungsgrenzen der Bassstrategie bleiben ausdrücklich geschützt.

Die tatsächlichen Achtel-Takt-Renderings prüfen beide Genres und Follow-Zustände, Swing, Szenenaufbau/-ende, geteilte MIDI-Kanäle, vollständige physische Note-Off-Bilanzen und die Blockgrößen 127/512/8192. Die bestehenden Bass-, Linien-, Rhythmus-, Transport- und Processor-Tests bleiben erhalten. Historische Diagnose-Probes konvertieren ausschließlich ihre Berichtseinheit, damit ihre bisherigen Noten-/Rhythmusanalysen vergleichbar bleiben; solche Konvertierungen sind keine Laufzeit-Speicheradapter.

Die Zeitregression gegen `cb25399` ergänzt den bisherigen 1117-Fall-Katalog um 96 gezielte Vorher-/Nachher-Fälle für freie Linien, Szenenaufbau/-ende sowie manuelle Figuren und geteilte Ansprüche. Auch diese kreuzen 4/4, 3/8, 5/8, 7/8, beide Genres, beide Bass-Follow-Zustände und Swing. Ihre zusätzlichen Blockvergleiche ersetzen keine strikten MIDI-Vorher-/Nachher-Bytevergleiche.

### Echtzeit- und Speicherverhalten

Keine neuen Heap-Allokationen, Dateizugriffe oder Katalogvalidierungen im Audiothread. Die vorhandenen `NoAllocations`-Wächter bleiben auch in den neuen tatsächlichen Renderings aktiv. Auf dem geprüften Linux-x64-Build ergeben sich folgende festen Objektgrößen (Byte, vorher → nachher): `Generator` 15176 → 15768, `Settings` 1080 → 1080, `BassPhraseRequest` 88 → 104, `BassPhrasePlan` 2088 → 2600, `LinePhrasePlan` 168 → 168, `RhythmPlan` 208 → 400, `InstrumentCapabilities` 40 → 40, `RoleNeed` 48 → 48. Der Mehrbedarf stammt aus bisher 32-Bit-breiten Bass-/Rhythmusdauern und aus der ausdrücklichen Abwesenheitsdarstellung optionaler Zeitpunkte; er ist fest begrenzt. Die rhythmischen Schleifen iterieren weiterhin über Musterplätze bzw. dieselben musikalischen Sechzehntel, nicht über jedes der 960 PPQ-Ticks.

### Abschlussprüfung Teil 1b.3

39/39 Gesamttests im vollständigen Lauf bestanden. 1213 vollständige Vorher-/Nachher-Renderings sind bytegleich zu `cb25399`; 1977 zusätzliche Blockgrößenvergleiche bestanden. Fallparameter und Prüfsummen: `MUSICAL_TIME_1B3_REGRESSION.json`. Wie bisher gilt nur für verschiedene Blockgrößen bei nicht ganzzahligen Samplepositionen höchstens ein Sample Rundungsspielraum, bei identischer Ereignisfolge und sonst identischen MIDI-Daten; der Vorher-/Nachher-Bytevergleich selbst hat keine Toleranz. Enthalten sind weiterhin alle 87 produktiven Wendungen, vorhandenen Profile, alle 80 unterstützten Taktarten und die 4096-Takt-Langzeitfälle sowie die oben beschriebenen 96 zusätzlichen Planungsfälle. Keine musikalische Fehlerkorrektur oder daraus resultierende MIDI-Abweichung war erforderlich.

ASan/UBSan für MusicalTime, MotifTime, BassPhrase, RhythmPlan, PlanningTime, CompositionCore und Engine ohne Befund (`detect_leaks=0`, keine LeakSanitizer-Aussage). 7/7 Paketprüf-Fixtures bestanden. Der echte Processor-Gesamttest einschließlich aller 216 Live-/SMF-Fälle in 4/4, 3/8, 5/8 und 7/8 ist bestanden; der Großblocktest meldet 872 Note-ons, 872 Note-offs und keine Notenverwaltungsfehler. Linux-x64-VST3 gebaut; ELF, Bundle und Versionsmetadaten 2.2 geprüft. Kein Windows-/pluginval-Lauf, kein Push und kein Release.
