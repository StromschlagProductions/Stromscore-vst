# Gemeinsame musikalische Zeitbasis und Ereignisausführung

**Aktueller Stand nach Teil 2b: abgeschlossen.** Die produktive Planung, Ereignisausführung und Notenverwaltung verwenden 64-Bit-Ticks mit 960 PPQ. Eigenständige Einsatz-, Struktur-, Kontroll- und Fristquellen ersetzen den universellen Schrittaufruf. Musikalische Musterraster und Controller-Abtastraten bleiben als bewusst definierte Auflösungen erhalten. Die folgenden Abschnitte dokumentieren die historischen Zwischenstände; maßgeblich für den Abschluss sind Teil 2b und dessen Prüfungsbilanz am Dokumentende.

## Historie: Zeitmodell Teil 1a – gemeinsame Ganzzahlbasis und Notenansprüche

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

## Teil 2a – Ereignisdispatcher, Swing-Domänen, Notenenden und Chase

Basis `17b15a4`, Branch `develop/composition-core-prototype`. Der beauftragte Teil 2 wird in zwei fachlich zusammenhängende Teile gegliedert:

1. **Dieser Commit:** den gemeinsamen Dispatcher, nominale Strukturereignisse, rhythmische Performance, reale Notenansprüche und den Chase vorhandener Pläne gemeinsam umstellen.
2. **Noch offen, Teil 2b:** die schrittbezogenen Mustererzeuger und sämtliche Planungs-/Kontrollaufrufe vollständig auf eigenständige PPQ-Ereignispläne umstellen. Insbesondere geplante Notenanfänge müssen unabhängig von den bisherigen Sechzehntelaufrufen registriert werden.

Die Teilung hält die eng gekoppelten Ausführungs-, Freigabe- und Chase-Komponenten zusammen. Sie vermeidet, zugleich sämtliche vorhandenen Begleitmuster und deren musikalische Indizes umzuschreiben. **Teil 2 insgesamt ist damit ausdrücklich noch nicht abgeschlossen.**

### Neuer gemeinsamer Ausführungspfad

`MusicalExecution.h` beschreibt eine maßgebliche musikalische Tickposition und ihre Ausführungsdomäne:

- `Timing::nominal`: Harmonie-, Takt-, Phrasen-/Szenengrenzen und deren gehaltene Stimmen. Ihre Performanceposition entspricht exakt der musikalischen Position.
- `Timing::groove`: dafür vorgesehene rhythmische Noten und ihre Enden. Erst bei Ausführung/Chase wird aus dem nominalen Tick die bisherige Double-Swing-Performanceposition und daraus der Sampleoffset berechnet.

`Generator::process()` führt drei Ereignisquellen zusammen: nominale Vorbereitung/Strukturgrenzen, rhythmische Einsätze und die früheste aktive Notenfrist. Der frühere äußere `for(k++ ...)`-Schritt-Scheduler sowie `stepOn()` und `releaseDue(step)` sind entfernt. Notenenden benötigen keinen zufällig passenden Aufruf eines rhythmischen Musters mehr. Harmonie-/Metrik-/Szenengrenzen werden zusätzlich direkt aus der musikalischen Zeitleiste abgefragt, auch wenn zu diesem Zeitpunkt kein rhythmischer Anschlag ausgeführt wird.

`prepareAt(Tick)` und `renderRhythmAt(Tick)` teilen sich dieselben bestehenden musikalischen Entscheidungen; es gibt keine zweite Kompositions-Engine. Die strukturelle Ausgabe und rhythmische Ausgabe sind getrennt. Dynamik-CCs vor gehaltenen strukturellen Einsätzen werden nominal veröffentlicht; die sonstige bisherige Performance-Expression bleibt bei den rhythmischen Aufrufen. Das verhindert, dass ein vorgezogener gehaltener Akkord seine notwendige Expression erst beim späteren Swing-Anschlag erhält.

Der Dispatcher besitzt weiterhin eine **240-PPQ-Kontroll-/Musterquelle** für die noch nicht migrierten Erzeuger. Diese ist nicht mehr die einzige Ausführungsuhr: Ein Notenende oder eine strukturelle Grenze bei z. B. Tick 37 wird unabhängig davon ausgeführt. Die Quelle und die alten Musteradapter sind jedoch eine echte verbleibende Kopplung für Teil 2b; sie werden nicht als vollständige Rasterunabhängigkeit ausgegeben.

### Eine Zeitbasis, zwei musikalische Ausführungsdomänen

Ein aktiver Notenanspruch speichert genau eine musikalische `endTime` plus die Domäne, in der dieses Ende ausgeführt wird. Es gibt keine parallele gespeicherte Raster-/PPQ-/Samplefrist. Die aktuelle Performance-PPQ ist eine Host-/Ausgabegrenze, keine zweite musikalische Uhr.

`limitClaim()` vergleicht bei geteilten Kanälen die tatsächlich wirksamen Fristen. Nominale Szenenschnitte dürfen eine geswingte Note rechtzeitig beenden. Gehaltene nominale Stimmen übernehmen nicht versehentlich das Swing-Ende einer rhythmischen Stimme. Eine dimensionlose `attack`-Identität fasst physische Angriffe am selben Ausführungszeitpunkt zusammen; zwei verschiedene Zeitpunkte mit demselben früheren Musterindex gelten nicht mehr fälschlich als gleichzeitiger Anschlag.

Swing wird nicht auf PPQ gerundet. Auf den vorhandenen Sechzehnteln bleibt die bisherige Abbildung `(cell + delay) * .25` mit `.333/.667` exakt erhalten. Zwischen diesen Positionen ist die Performanceabbildung stückweise linear und streng monoton. `nominalAt()` invertiert sie für den Planungs-/Chase-Lookup. Der Lookup verwendet Tickpositionen; die endgültige Gateprüfung verwendet weiterhin die ungerundete Performanceposition.

### Reihenfolge gleichzeitig auftretender Ereignisse

Innerhalb eines gemeinsamen Performancezeitpunkts gilt:

1. Abgelaufene Ansprüche freigeben; genau gleichzeitig endende lange Flächentöne vorläufig zurückstellen.
2. Nominalen Kontext vorbereiten: Harmonie-/Szenenzustand, notwendige Controller und gehaltene Stimmen aktualisieren. Gemeinsame Akkordtöne können ihre Ansprüche verlängern.
3. Gleichzeitig anstehende rhythmische Einsätze ausführen. Gemeinsame MIDI-Töne erhalten innerhalb desselben Ausführungszeitpunkts nur einen physischen Angriff.
4. Nicht verlängerte Flächenansprüche und sonstige fällige Ansprüche vollständig freigeben.

Ohne gleichzeitig anstehenden rhythmischen Einsatz wird die abschließende Flächenfreigabe unmittelbar nach dem Strukturereignis vorgenommen. Für reine Fristereignisse ist keine zusätzliche musikalische Erzeugung erforderlich. Diese Reihenfolge schützt sowohl gemeinsame Akkordtöne als auch die vorhandene Kanal-/Notenbesitzverwaltung.

### Gezielte Verhaltenskorrekturen

**Swingverschobene strukturelle Grenzen:** Bei 3/8, 5/8 oder 7/8 liegt jeder zweite Taktbeginn auf einer zuvor verzögerten Sechzehntelphase. Der alte Scheduler verschob dort auch den Akkordwechsel und die gehaltenen Stimmen. Sie werden jetzt nominal ausgeführt; rhythmische Figuren behalten ihren vorgesehenen Swing.

Für gerichtete Beispiele mit bestehenden eigenen Akkorden C-Dur → F-Moll, 120 BPM und Swing .5 ergibt sich beim ersten Akkordwechsel:

| Takt | Bisheriger Bass-/Akkordeinsatz, Sample | Nominaler neuer Einsatz, Sample | Korrektur |
| --- | ---: | ---: | ---: |
| 3/8 | 38001 | 36000 | 2001 Samples früher |
| 5/8 | 62001 | 60000 | 2001 Samples früher |
| 7/8 | 86001 | 84000 | 2001 Samples früher |
| 6/8 | 72000 | 72000 | Unverändert |

Diese Beispiele werden als `held-*-8-before.mid` / `held-*-8-after.mid` im Ausgabeverzeichnis von `compare_execution_time.py` erzeugt. Es werden keine neuen Katalogeinträge oder musikalischen Regeln eingeführt.

**Vorzeitiger Chase eines geswingten Motivtons:** Der alte Chase konnte nach dem nominalen Beginn, aber noch vor dem tatsächlichen Swing-Anschlag bereits den neuen Motivton ausgeben. Für vorhandene Motiv-, freie Linien-, Bassphrasen- und Antwortpläne erfolgt die Prüfung nun gegen tatsächlichen Performancebeginn und tatsächliches Performanceende. Vor dem verzögerten Anschlag bleibt gegebenenfalls der vorherige Ton hörbar; nach dem Anschlag wird der neue Ton rekonstruiert. Das gespeicherte Motiv bleibt unverändert.

**Nicht rastergebundene Fristen und Szenenenden:** Die Ausführung einer fälligen Note bzw. eines bereits bekannten Szenenendes zwischen zwei bisherigen Sechzehnteln wird nicht mehr bis zum nächsten Musteraufruf verschoben. Die regulären Benutzerparameter erzeugen in diesem Schritt weiterhin keine neuen feineren musikalischen Muster.

### Tests dieses Teils

`ExecutionTests` erhält ausschließlich in einer offline kopierten Test-Headerfassung Friend-Zugriff. Damit werden tatsächliche `Generator`-Notenansprüche mit nicht rastergebundenen Enden und ein Szenenende bei Tick 37 eingespeist. Die Tests prüfen echte MIDI-Freigaben, geteilte Kanäle mit verschiedenen Ausführungsdomänen, Blockgrößen 127/512/8192 und vollständige Notenbilanzen. Die produktive Plugin-API enthält diesen Zugriff nicht.

Weitere Tests prüfen die unveränderte Swingabbildung an bestehenden Musterplätzen, Monotonie und Inversion, Ereignispriorität, gehaltene Akkordwechsel in allen 80 unterstützten Taktarten bei Swing .3/1 sowie wiederholten Chase vor und nach einem tatsächlich eingeführten verzögerten Motivton. Vorhandene Engine-, Motiv-, Bass-, Linien-, Transport-, Loop- und Echtzeittests bleiben aktiv.

`compare_execution_time.py` ersetzt für diesen Commit den unveränderten Bytevergleich als CTest-Einstieg durch eine streng klassifizierte Auswertung: Ohne Swing sowie in unverändert erwarteten linearen metrischen Kontexten müssen vollständige MIDI-Bytes gleich bleiben. Auch in den zugelassenen Swing-/Chase-Korrekturkontexten müssen sämtliche Ereignisdaten und Ereignisanzahlen erhalten bleiben; Zeitänderungen werden mit Prüfsummen, Anzahl, Sampleverschiebung und Beispielen einzeln protokolliert. Die zusätzliche gerichtete Prüfung kontrolliert alte Swing-Einsätze und neue nominale Bass-/Akkordgrenzen ausdrücklich anhand ihrer tatsächlichen Samples.

### Ausdrücklicher Rest für Teil 2b

**Die musikalische Planung und Ereigniserzeugung sind noch nicht vollständig vom alten Ausführungsraster entkoppelt.** Der Dispatcher, die unabhängigen nominalen Grenzen und die reale Fristverwaltung sind umgestellt. Es verbleiben:

- die 240-PPQ-Vorbereitung und daran angeschlossene alte Musteraufrufe; Notenanfänge beliebig fein aufgelöster Planergebnisse werden noch nicht allgemein als eigene Quellen angemeldet;
- `Meter::len/groupStart`, `Pos::k/pos`, `nowStep` als bisherige Muster-/Zufallsindizes sowie `gridChord*` / `gridPhrase*` und einzelne Step-Überladungen als Adapter der Erzeuger;
- rhythmische Einsatzprädikate und manche Notendauern in den unmittelbar gerenderten Bass-, Arpeggio-, Akzent- und Hook-Funktionen;
- ein ausdrücklicher Revisions-/Invalidierungsvertrag für Parameteränderungen zwischen nominaler Vorbereitung und verzögerter Ausführung;
- die vollständige Rekonstruktion durchlaufender, nicht als eigenständiger zeitlicher Linienplan vorliegender Begleit-/Hook-Muster beim Chase. Der Chase vorhandener Pläne ist korrigiert; es wird keine allgemeine neue Replay-Engine vorgetäuscht;
- die bereits bekannte fehlende Vorgeschichte der harmonischen Übergangsstimmführung bei kaltem Seek. Diese musikalische Zustandsgrenze ist nicht durch den neuen Ausführungsdispatcher behoben.

Die verbleibenden Mustererzeuger, ihre PPQ-Planungsaufrufe und ihre Chase-Rekonstruktion sollten gemeinsam migriert werden. Ein bloßes Umbenennen ihrer Schrittindizes würde diese Abhängigkeiten verdecken. In diesem Commit wird dieser zweite Umbau nicht zusätzlich begonnen. Keine GUI-Änderung, keine Künstlerprofile, keine neue harmonische oder motivische Funktion, kein Push und kein Release.

Die bisherige Transport-Sprungerkennung mit einer Toleranz von .05 Viertelnoten bleibt in diesem ersten Teil erhalten. Sehr kleine Positionsdiskontinuitäten sind damit noch nicht allgemein als eigenständige Transportereignisse modelliert. Auch dies gehört zum abschließenden Transport-/Aufrufvertrag in Teil 2b.

### Abschlussprüfung Teil 2a

40/40 Gesamttests im vollständigen Lauf bestanden. Die Ausführungsmatrix gegen `17b15a4` enthält 1217 vollständige Vorher-/Nachher-Renderings: 1119 sind bytegleich; 98 enthalten ausschließlich Zeitkorrekturen. Sämtliche MIDI-Ereignisdaten einschließlich Noten, Velocities, Zielen und Ereignisanzahlen bleiben in dieser Matrix gleich. Insgesamt werden 5040 geänderte Zeitstempel dokumentiert; sie liegen 555 bis 2668 Samples früher. Die gerichteten Beispiele und die vier zusätzlichen Referenzfälle sind enthalten. Details, Prüfsummen und Einzelbeispiele: `MUSICAL_EXECUTION_2A_REGRESSION.json`.

Alle 1985 Blockgrößenvergleiche bestanden. Wie bisher gilt bei nicht ganzzahligen Samplepositionen höchstens ein Sample Rundungsspielraum zwischen verschiedenen Blockgrößen, bei identischer Ereignisfolge und sonst identischen MIDI-Daten. Die unverändert erwarteten Vorher-/Nachher-Kontexte werden ohne Toleranz byteweise verglichen. Die separate Chase-Prüfung weist die Korrektur des vorzeitig ausgegebenen Motivtons ausdrücklich nach; sie wird nicht als bloße Zeitverschiebung aller denkbaren Chase-Situationen verallgemeinert.

ASan/UBSan für Execution, MusicalTime, MotifTime, BassPhrase, RhythmPlan, PlanningTime, CompositionCore und Engine ohne Befund (`detect_leaks=0`, keine LeakSanitizer-Aussage). 7/7 Paketprüf-Fixtures bestanden. Der echte Processor-Gesamttest einschließlich 216 Live-/SMF-Vergleichen und geschlossenen Großblock-Notenbilanzen bestanden. Linux-x64-VST3 gebaut; ELF, Bundle und Versionsmetadaten 2.2 geprüft. Keine GUI-/Profiländerungen, kein Windows-/pluginval-Lauf, kein Push und kein Release.

Keine neuen Heap-Allokationen oder Dateioperationen im Audiothread. Der geprüfte Linux-x64-`Generator` wächst durch Domänen-/Angriffsmetadaten der bestehenden festen Notenansprüche und den Dispatcherzustand von 15768 auf 17352 Byte; `Settings` bleibt bei 1080 Byte. Die Ausführung iteriert über fällige Ereignisse und die vorhandenen musikalischen Musterquellen, nicht über jedes einzelne PPQ-Tick.

## Teil 2b – eigenständige Einsätze, Kontrollereignisse und vollständiger Muster-Chase

Basis `1481a4f`, Branch `develop/composition-core-prototype`.

### Ausführung ohne universellen Sechzehntel-Taktgeber

`Generator::process()` fragt jetzt drei eigenständige Quellen ab: nominale Struktur-/Kontrollereignisse, konkrete rhythmische Einsätze und aktive Notenfristen. Die zuvor unbedingt fortgeschriebenen `pulse += 240` und `control += 240` sind entfernt. `nextOnset(Tick)` meldet harmonisch relativ gestartete Arpeggios aus ihrem Tick-Anker und ihrer eigenen musikalischen Periode sowie Bass-/Liniennoten, Motivnoten, Varianten, Antwortnoten, Abschluss- und Wiederkehrfenster unmittelbar in PPQ. Auch ein Anfang bei Tick 37 benötigt keinen passenden Musteraufruf. `nextBoundary(Tick)` liefert weiterhin die ungeswingten harmonischen, metrischen und Szenengrenzen, einschließlich der Bassvorbereitung in der zweiten Takthälfte.

Die vorhandenen Begleitvokabeln behalten ihre musikalischen Einsatzplätze. `templateOnset()` durchsucht deren begrenzte symbolische Plätze innerhalb eines Takts, ohne dabei Generatorzustand oder Zufallszahlen fortzuschreiben. Der folgende Taktbeginn ist ein eigener Auffrischungspunkt: Sein gegebenenfalls verzögerter rhythmischer Anschlag darf nicht hinter dem Suchhorizont verschwinden. Dies ist eine Abfrage musikalischer Vorlagen, keine Abtastung aller 960 Ticks und kein universeller Schritt-Scheduler. Ein gehaltenes Arrangement ohne rhythmische Stimmen und ohne Dynamik-/Fahrtsteuerung benötigt keine Sechzehntelaufrufe.

Alle angeschlossenen Erzeuger erhalten `Tick`-Positionen: Motive, Varianten, Antworten, freie Linien, Hook-Noten, Arpeggios, Akzente und Rhythmusausgabe. Ihre Notenenden werden direkt als Tick-Dauern berechnet. Die Step-Überladungen von `noteOn()`, `padChord()` und `cut()`, die `gridChord*`-/`gridPhrase*`-Brücken sowie `nowStep` und der ganzzahlige Chase-Zeitstempel sind entfernt. Szenenstart, Fahrt und Übergangshistorie verwenden die gemeinsame Zeit ebenfalls direkt.

Ein Einsatzplan darf nach einer Zustandsänderung neue gegenwärtige oder zukünftige Ereignisse anmelden, jedoch keine vergangenen. Die nominalen und rhythmischen Suchgrenzen laufen deshalb strikt vorwärts. Eine Vorschau (`motifOccurrence(..., preview=true)`) verwendet nur eine begrenzte lokale Kopie des abgeleiteten Wiederkehr-Caches. Sie verändert weder den tatsächlichen Cache noch Material, Cursor oder Wiederkehrzustand einer Stimme. Erst nach nominaler Kontextvorbereitung wird die musikalische Entscheidung wie bisher gespeichert. Auch ein bewusst stilles Wiederkehrfenster besitzt ein eigenes Planungsereignis an seinem Beginn; hierfür ist keine zufällig aktive Begleitstimme oder Controller-Abtastung nötig. Nach nominaler Vorbereitung wird ein genau gleichzeitig neu angemeldeter rhythmischer Einsatz noch vor der abschließenden Freigabe gemeinsamer Flächentöne berücksichtigt. Die in Teil 2a festgelegte Ereignispriorität und die beiden Ausführungsdomänen bleiben bestehen.

### Zeitabhängige Kontrolle und Parameteränderungen

Die bestehenden Dynamikbögen behalten ausdrücklich ihre Sechzehntel-Abtastrate als **Controllerkurve**. Diese Quelle ist nur bei aktivierter CC-Dynamik vorhanden. Die bestehende Fahrt behält ebenfalls ihre musikalische Kontrollauflösung, solange sie eingeschaltet ist. Ihr Einschaltwunsch wird an der tatsächlichen Tick-Position verriegelt; die abgetastete Kurvenposition darf ihn nicht auf einen früheren Takt zurückdatieren. Blockweise Einsatzabfragen verwenden den zuletzt ausgewerteten Fahrtpunkt, bis ein Kontrollereignis ihn aktualisiert, und fallen nicht zwischen zwei Blöcken auf den rohen Ausgangspunkt A zurück. Keine dieser Auflösungen begrenzt andere Planungsereignisse oder Notenfristen. Hüllkurven und Dichtemasken werden zusätzlich am tatsächlich benötigten Einsatz ausgewertet.

Blockweise geänderte Einstellungen erzeugen ein eigenes Kontrollereignis an der Hostposition. `sameSettings()` vergleicht die Werte der Parameter, Routen und Policies ausdrücklich, einschließlich Arrays. Es werden weder Paddingbytes verglichen noch kollisionsbehaftete Hashes als Revisionsnachweis benutzt. Der vorherige Parametersatz benötigt festen Objektspeicher; keine Allokation im Audiothread. Bereits vorhandene musikalische Plan-/Cacheentscheidungen werden dabei nicht pauschal verworfen oder Motive neu erfunden. Beispielsweise wird eine Endanforderung zwischen zwei Musterplätzen sofort wirksam. Ein Mute-/Unmute-Wechsel nach nominaler Vorbereitung und vor einem verzögerten Anschlag wirkt ebenfalls vor dessen tatsächlicher Ausgabe; bereits vergangene Anschläge werden nicht nachgeholt. Diese präzisere Parameterübernahme ist gegenüber den alten regelmäßigen Kontrollaufrufen beabsichtigt.

### Verbleibende Indizes sind musikalische Symbole

`Pos::k`, `Pos::pos`, `Meter::len/groupStart`, Musterplätze, harmonische Slotnummern, Phrasennummern und die daraus gebildeten Zufallsschlüssel bleiben dimensionslose Indizes. Die vorhandene Akzentlotterie, Hook-Kontur und Arpeggiorichtung erhalten so ihre bisherige Bedeutung. Ihre Positionsermittlung erfolgt aus der maßgeblichen Tick-Zeit. Diese Indizes werden nicht mehr als gespeicherte musikalische Zeit oder universelle Ereignisuhr zurückgegeben.

Das bestehende Score-Einführungsmotiv realisiert seine taktbezogenen Vorlagensymbole weiterhin auf den bisherigen musikalischen Sechzehnteln; die bestehenden Pop-Hooks besitzen ebenfalls ihre bisherigen Einsatzvokabeln. Die zeitliche Interpretation der tatsächlich aufgenommenen Pop-Noten entfernt den beim Einspielen verwendeten Swing über dieselbe Ausführungsabbildung. Die bisherige Quantisierung dieser Hook-Vokabeln wird nicht als neue musikalische Funktion verändert. Gespeichertes Material, abgeleitete Varianten und ihre konkret geplanten Einsätze besitzen weiterhin ausschließlich Tick-Zeiten.

### Chase und kleine Positionssprünge

Der Chase vorhandener Bass-, Linien-, Motiv- und Antwortpläne verwendet weiterhin die tatsächlichen geswingten Anfangs-/Endpositionen. Zusätzlich werden noch klingende unmittelbare Bass-, Flächen-, Arpeggio- und Akzentmuster aus denselben Einsatzprädikaten und Erzeugern rekonstruiert. Der begrenzte Rückblick deckt deren maximale Gates bzw. zwei Hook-Takte ab; er rendert keine ganze Szene nach. Abgelaufene oder noch nicht angeschlagene Noten werden an der gemeinsamen Notenausgabegrenze verworfen. Motiv-/Antwortreservierungen bleiben dabei wirksam.

`hookNote()` berechnet eine konkrete Hook-Note ohne Aufnahme oder MIDI-Ausgabe. Normale Wiedergabe und Chase verwenden genau diese Berechnung. Der Chase stellt nur den letzten noch klingenden Hook-Ton und gegebenenfalls seinen tatsächlichen Legato-Überhang her. Fällt ein regulärer Anschlag desselben MIDI-Tons genau auf das Seek-Ziel, haben dessen Artikulation und Velocity Vorrang vor dem rekonstruierten Überhang; Artikulationslücken bleiben still. Aufnahme und Motivkatalog werden dadurch nicht mit einer erfundenen vergangenen Performance gefüllt. Nicht motivische lokale Linien einschließlich Vorhaltsauflösung werden aus ihrem aktuellen harmonischen Abschnitt rekonstruiert. CCs erhalten beim Chase ihren aktuellen Wert.

Die alte Sprungtoleranz von 0,05 Viertelnoten verdeckte echte kleine Seeks und kurze Loops. Sie ist ersetzt durch eine Sampledauer, mindestens den numerischen Genauigkeitsspielraum der Host-PPQ. Ein Sprung um 0,01 Viertelnoten löst daher unmittelbar Freigabe und Chase aus; Positionsrauschen unter einem Sample beendet keine laufenden Noten. Ein Sample Rundungsspielraum ist hier notwendig: Bei 173 BPM sind 64 Viertelnoten 1 065 433,526 Samples lang; ein auf ganze Samples begrenzter Hostabschnitt kann dadurch rund 0,53 Samples von seiner nominalen PPQ-Grenze abweichen. Das darf keinen Notenreset auslösen. Ein zusätzlicher Grenztest prüft 0,75 Samples ohne Reset und 1,5 Samples mit Reset. Kein neuer Transportparameter.

**Bewusste Unterschiede gegenüber `1481a4f`:** An einem Positionssprung können zusätzlich rekonstruierte, am Ziel tatsächlich noch klingende Begleit-/Hook-/Linientöne und aktuelle CCs erscheinen. Die dazugehörigen Freigaben folgen ihren ursprünglichen musikalischen Fristen; bei geteilten Kanälen kann sich deshalb der Zeitpunkt einer physischen Freigabe ändern. Kleine zuvor übersehene Sprünge werden nun erkannt. Normale durchlaufende Kompositionen sollen unverändert bleiben. Die 98 in Teil 2a korrigierten Renderings werden zusätzlich gegen `17b15a4` und ihre bereits dokumentierten Prüfsummen kontrolliert, nicht stillschweigend zur neuen neutralen Referenz erklärt.

### Gezielt ergänzte Nachweise

`ExecutionTests` prüft tatsächliche Motivanfänge bei Tick 37 und 517 sowie Arpeggios mit einem harmonischen Anker bei Tick 37 und eigener relativer Periode mit ihren Freigaben in 3/8, 5/8 und 7/8, Swing 0/.5/1 sowie Blockgrößen 127/512/8192. Weitere Prüfungen betreffen die Abwesenheit einer Sechzehntelquelle bei gehaltenen Texturen, kleine Vorwärts-/Rückwärtssprünge, toleriertes Hostrauschen, Endanforderung bei Tick 37, nicht verändernde Vorschauen über Wiederkehrgrenzen, Materialisierung stiller Wiederkehrfenster, Parameterwechsel vor verzögerten Anschlägen, unveränderte Akzente bei mit Chase zusammenfallenden Hook-Einsätzen und tatsächliche Hook-Gates/-Pausen beim kalten Chase. Bestehende gemeinsame Notenansprüche, alle 80 Taktarten und Motiv-Chase-Tests bleiben enthalten.

`compare_execution_time.py --completion` vergleicht dieselbe vollständige Matrix mit `1481a4f`. Durchlaufende Fälle müssen bytegleich bleiben. Bei expliziten Sprungrouten werden sämtliche hinzugefügten/entfallenen Ereignisse einzeln protokolliert; normale Angriffe dürfen auch dort weder verschwinden noch verschoben werden. Zusätzliche Angriffe sind nur an den ausdrücklichen Transportgrenzen zulässig, geänderte Freigaben müssen zu den rekonstruierten Ansprüchen gehören. Der separate Teil-2a-Lauf prüft zusätzlich alle damaligen Vorher-/Nachher-Prüfsummen einschließlich der 98 Korrekturfälle.

### Fachliche Grenze des Chase

Ein kalter Seek kennt weiterhin keine nie gespielte musikalische Vorgeschichte: insbesondere die tatsächlich gehörte harmonische Übergangslage sowie noch nicht eingeführtes Motivmaterial. Das ist eine Grenze des verfügbaren musikalischen Zustands, keine übrig gebliebene Schritt-Scheduler-Abhängigkeit. Es wird weder eine zweite Engine noch eine allgemeine Replay-/Orchestrierungsarchitektur eingeführt. Ein kalter Einstieg kann deshalb musikalisch von einem kontinuierlich erreichten Zeitpunkt abweichen, obwohl alle Ereignisse exakt zum vorgesehenen Zeitpunkt ausgeführt werden.

Die historischen Katalog-/Akkorddefinitionsvergleiche behalten ihre Bytegleichheit für kontinuierliche Wiedergabe. `transport_regression.py` erlaubt ausschließlich deklarierte Chase-Angriffe an den jeweiligen Sprunggrenzen und bilanzierte zugehörige Freigaben; reguläre Angriffe dürfen nicht verschwinden. Ersetzt ein unmittelbar beim Chase gesendeter CC den sonst später identisch gesendeten ersten Controllerwert, wird auch diese eng begrenzte Verschiebung geprüft. Katalogfakten, Tonklassen, Rezepte und Profilgewichte werden weiterhin exakt verglichen.


### Abschlussprüfung Teil 2b

40/40 konfigurierte Kernprüfungen bestanden, in zwei vollständig abgeglichenen Gruppen mit 37 und 3 eindeutig benannten Tests. Alle historischen Prüfungen bleiben aktiv; Abweichungen an ausdrücklich definierten Transportgrenzen werden eng begrenzt als Chase-Ergänzungen geprüft. Insbesondere bestehen wieder die modalen XYZ-Wechsel, die 128-Takt-Übergangsvergleiche und die Blockgrößenprüfung der katalogbasierten Begleitkoordination. Die neue Vorschauprüfung schützt gegen vorzeitig gespeicherte Wiederkehrpläne; ein weiterer Test materialisiert ein bewusst stilles Fenster ohne Begleit-/CC-Schrittquelle.

Die vollständige Ausführungsmatrix gegen `1481a4f` umfasst **1313 Renderings**: 743 sind vollständig bytegleich, 570 enthalten ausschließlich die dokumentierten Transport-/Chase-Ergänzungen. Sämtliche durchlaufenden Fälle sind bytegleich. In der gesamten Matrix bleiben alle bisherigen Note-ons und Note-offs einschließlich Zeit, Ton, Velocity, Kanal und Ausgang erhalten. Hinzu kommen 2600 Chase-Note-ons und exakt 2600 zugehörige Note-offs. Außerdem erscheinen 256 unmittelbar rekonstruierte CC-Ereignisse; 216 sonst später identisch gesendete erste CC-Werte entfallen durch die bestehende Dublettenunterdrückung. Jeder einzelne Delta-Datensatz einschließlich Prüfsummen ist in `MUSICAL_EXECUTION_2B_REGRESSION.json` enthalten.

Alle **2177 Blockgrößenvergleiche** bestanden. Zwischen unterschiedlichen Blockgrößen gilt bei gebrochenen Samplepositionen weiterhin höchstens ein Sample Rundungsspielraum bei identischen Ereignisdaten und gleicher Reihenfolge; der reguläre Vorher-/Nachher-Vergleich selbst bleibt bytegenau. Die Matrix enthält alle 87 produktiven Wendungen, alle vorhandenen Profile, alle 80 unterstützten Taktarten, zusätzliche Dynamik-/Fahrtfälle und drei 4096-Takt-Langzeitläufe. Der gesonderte Teil-2a-Lauf reproduziert alle 1217 damaligen Vorher-/Nachher-Prüfsummen einschließlich der **98 bereits korrigierten Renderings** exakt. Diese Korrekturen wurden nicht zurückgenommen oder als neue Abweichungen von Teil 2b verschleiert.

ASan/UBSan: **8/8 Programme** bestanden (Execution, MusicalTime, MotifTime, BassPhrase, RhythmPlan, PlanningTime, CompositionCore, Engine), jeweils mit `-O1 -g -fno-omit-frame-pointer -fsanitize=address,undefined`. `ASAN_OPTIONS=detect_leaks=0`: keine LeakSanitizer-Aussage. Die allokationsfreien Audio-/MIDI-Prüfungen bleiben aktiv. 7/7 Paketprüf-Fixtures bestanden. Der echte Processor-Test besteht einschließlich aller **216 Live-/SMF-Vergleiche** in 4/4, 3/8, 5/8 und 7/8; der Großblocktest liefert 872 Note-ons, 872 Note-offs und keine Notenverwaltungsfehler.

Linux-x64-VST3 erfolgreich gebaut. ELF, exportierte VST3-Factory und Bundle-Metadaten (Version 2.2) geprüft. Keine GUI-/Profiländerung, kein Windows-/pluginval-Lauf, kein Push und kein Release.

Der gemessene Linux-x64-`Generator` wächst von 17352 auf **18440 Byte**, `Settings` bleibt bei **1080 Byte**. Der feste Mehrbedarf von 1088 Byte entspricht dem optionalen blockübergreifenden Parametersatz. Die Cache-Vorschau kopiert ausschließlich begrenzte abgeleitete Planungsdaten auf dem Stack; es entstehen keine neuen Heap-Allokationen, Dateioperationen oder Harmonie-Datenvalidierungen im Audiothread.

### Abschluss und verbleibende musikalische Raster

Die Zeitbasis-/Scheduler-Baustelle kann damit geschlossen werden. Planung und Ausführung benötigen keinen universellen Sechzehntel-Aufruf mehr. Die vorhandenen musikalischen Figuren verwenden weiterhin ihre eigenen Sechzehntelsymbole, metrischen Gruppen, Phrasennummern und stabilen Zufallsschlüssel. Aktivierte CC- und Fahrtkurven behalten ihre bisherige Abtastauflösung. Read-only-Inspektionshilfen können weiterhin einen ausdrücklich bezeichneten Musterplatz entgegennehmen; diese Diagnosegrenze ist keine Ausführungsuhr oder parallele gespeicherte musikalische Zeit.

Katalogdauern in ganzen Takten und die bisherige harmonische Slotanzahl wurden in diesem Auftrag nicht erweitert. Die oben beschriebene fehlende musikalische Vorgeschichte beim kalten Seek bleibt eine fachliche Zustandsgrenze. Keiner dieser Punkte erfordert eine Rückkehr zum früheren Schritt-Scheduler. Kein weiterer Entwicklungsschritt wurde begonnen.

Reproduktion: Engine-Build mit CMake, anschließend alle CTests; `compare_execution_time.py --completion --probe <HarmonyImportProbe> --output <Verzeichnis>` erzeugt die vollständige Zeitmatrix samt separater Teil-2a-Referenzprüfung. Im Ausgabeverzeichnis stehen zusätzlich `chase-1001-before/after.mid`, `chase-2037-before/after.mid` und die zugehörigen CSV-Dateien als gezielte Hör-/MIDI-Beispiele. Die gerichteten gehaltenen 3/8-, 5/8-, 7/8- und 6/8-Beispiele bleiben ebenfalls enthalten.
