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
