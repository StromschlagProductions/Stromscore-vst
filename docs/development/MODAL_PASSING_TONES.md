# Modaler Tonvorrat und kontrollierte Durchgangstöne

Basis `1fa718f`, Entwicklungsbranch `develop/composition-core-prototype`.
Keine neuen Wendungen, Akkorde, Bassverfahren, Profile oder GUI-Parameter.

## Architektur und musikalischer Bezug

Die vorhandene Tonart ist eine Transposition in zwölf Halbtonklassen. Wendungen speichern
relative Akkordgrundtöne, Qualitäten, optional eigene Basstonklassen und Dauern. `kShapes`
liefert die Akkordintervalle; `counterLadder()` und die harmonische Motivvorprüfung arbeiten
bislang weitgehend mit Akkordtonklassen. Vorhandene chromatische Annäherungen oder pauschale
Vorhalte sind kein Modell eines zusammenhängenden diatonischen Modus.

`Source/ModalContext.h` ergänzt eine gemeinsame, vom Genre und MIDI-Ausgang unabhängige
Tonhöhenbeschreibung:

| Modus | Relative Halbtonklassen |
|---|---|
| Ionisch | 0, 2, 4, 5, 7, 9, 11 |
| Mixolydisch | 0, 2, 4, 5, 7, 9, 10 |
| Dorisch | 0, 2, 3, 5, 7, 9, 10 |
| Äolisch | 0, 2, 3, 5, 7, 8, 10 |

`modalMask()` transponiert diesen Vorrat. `modalContext()` wertet den gesamten harmonischen
Vorrat aus, nicht jeden Akkord für sich. Der Adapter `modalContextFor()` übergibt alle
Akkordtonklassen und ausdrücklich gesetzten Basstonklassen der vollständigen Wendung.
Dauern und Akkordauswahl werden dabei nicht verändert. Auch ein kurzer nicht passender
Farbakkord verhindert zunächst eine automatische eindeutige Zuordnung.

Das benannte Zentrum ist `Settings.key + passing.tonicOffset` (neutral Offset 0).
Automatisch muss dazu eine Akkordgrundton-Evidenz in der Wendung vorliegen. Dies ist
**kein beliebiges Erraten einer Tonika aus einem Tonvorrat**: relative Modi wären sonst
prinzipiell mehrdeutig. Ein Profil kann später Modus und Zentrum ausdrücklich vorgeben.
Auch eine solche Vorgabe muss mit sämtlichen Tonklassen kompatibel sein; sie legitimiert
keine fremden Töne. Ohne eindeutigen Kontext erfolgt keine neue Verzierung.

Die Statuswerte sind `unique`, `ambiguous`, `incompatible` und `unspecified`.
`incompatible` bedeutet außerhalb der vier unterstützten Modi am benannten Zentrum,
nicht den Beweis, dass eine Wendung grundsätzlich unmusikalisch oder ohne anderen Modus sei.
Chromatische/modal gemischte Folgen werden damit konservativ abgelehnt, nicht automatisch
zu einem einzelnen Akkordmodus umgedeutet.

| Vorhandene Wendung | Befund am relativen Zentrum 0 |
|---|---|
| 2015 C–B♭–F–C | eindeutig mixolydisch kompatibel |
| 2019 B♭–F–C | eindeutig mixolydisch kompatibel |
| 2012 Cm–F | eindeutig dorisch kompatibel innerhalb dieses Modells |
| 2025 Cm9–F7–Cm9–E♭maj7–F7 | dorisch kompatibel, einschließlich None/Septimen |
| 2017 C5–B♭5–F5–C5 | mehrdeutig: Terzen/modal unterscheidende Töne fehlen |
| 2001 Cm–D♭ | nicht kompatibel mit den vier Modi am Zentrum C |
| 2029 Cmaj7–B♭maj7–Dm7–Gsus4 | gemischter Vorrat; B und B♭ verhindern eindeutige Eignung |
| 2034 mit E7, Am7 und G7 | chromatisch gemischt; keine neue Verzierung |
| 2035 C–F–Am7–G | eindeutig ionisch kompatibel |

Die Einstufungen gelten transponiert in allen zwölf Tonarten. Eine bloße C-Dur-Triade
bleibt automatisch zwischen Ionisch und Mixolydisch mehrdeutig. Eine ausdrückliche
kompatible Vorgabe kann diesen Fall auflösen. Das ist eine technische Eignungsprüfung,
keine Künstlerzuordnung.

## Ein einziges neues melodisches Verfahren

`planPassingTone()` plant ausschließlich einen **diatonischen Durchgangston** zwischen
zwei bereits realisierten Akkord-Zielnoten. Er verlangt:

- gültigen eindeutigen modalen Kontext und kompatible vollständige Akkordfakten;
- zwei geeignete Akkordtöne und genau einen dazwischenliegenden Skalenton;
- gleichgerichtete Schritte von jeweils einem oder zwei Halbtönen;
- einen kurzen schwachen Rastereinsatz, mindestens eine Zeiteinheit pro Note;
- Zielauflösung vor dem Ende derselben Harmonieregion;
- gültigen Tonumfang und zulässige Notendauer;
- keinen Halbtonkonflikt zum Akkordgrundton oder vorgegebenen Slash-Bass.

Ein diatonischer Halbton gegen die unmittelbar folgende Auflösungsnote ist bewusst
erlaubt, beispielsweise F→E über C-Dur. Ein zusätzlicher Halbton zu anderen Akkordtönen
ist in diesem ersten Schritt verboten. G→F→E kann daher zulässig sein, E→F→G über
weiterhin vorhandenem E wird verworfen. Ein führendes B direkt neben dem Bass C wird
hier ebenfalls nicht als neuer Durchgangston eingesetzt. Das ist eine konservative
Regel für kontrollierte Dissonanz, kein allgemeines Verbot diatonischer Halbtonschritte.

`addPassingTone()` wendet diese gemeinsame Planung zunächst nur auf passende originale
phrasenbezogene Pop-Hook-Realisierungen an. Kontinuierliche Ostinati, Einführungen und
Sequenzen bleiben unverändert. In der aktuellen neutralen Rollenzuordnung ist vor allem
2035 geeignet. Die mixolydischen und dorischen Kandidaten besitzen damit die technische
Grundlage, ihre derzeit kontinuierlichen Figuren werden aber nicht entgegen der
Rollenentscheidung verändert.

Die gemeinsame `PassingPolicy` enthält Aktivierung, Gelegenheitsabstand, Mindestabstand
zwischen Zielnoten, maximale Dauer sowie optionale Modus-/Zentrumsvorgabe. Neutral werden
höchstens bei jeder dritten Wiederkehrgelegenheit geeignete Stellen geprüft und maximal
zwei Sechzehntel zugelassen. Pro Figur höchstens ein erfolgreicher Durchgang. Es gibt
keine Zielquote für Nicht-Akkordtöne: ohne geeignete Stelle entfällt die Verzierung ohne
Nachholen oder Ausgleich an anderer Stelle.

## Erhaltene Motive und Zeitplanung

Die Verzierung wird erst nach der bisherigen harmonischen Figurenrealisierung an der
gewählten Wiederkehrposition ergänzt. Alle bisherigen Zielnoten, Tonhöhen und Einsätze
bleiben erhalten. Falls nötig endet nur die vorangehende Note vor dem Durchgangston.
Ein schwächerer Anschlag (sechs Velocity-Stufen unter der Zielnote) kennzeichnet den
kurzen Durchgang. Die Zielnote bleibt unverändert und ist die bereits geplante Auflösung.

Die veröffentlichte Quelle im `MotifCatalog` wird weder überschrieben noch neu gehasht.
`MotifFigure::passingIndex` kennzeichnet nur die temporäre Ausführung. Figurenbeginn,
Ende, Wiederkehrzeitpunkt, Mindestpause und Sequenzentscheidung bleiben gleich. Die
bestehenden Notenausgabe-, Seek- und Arp-Reservierungspfade verwenden dieselbe dekorierte
Figur. Es gibt keinen zweiten Tonhöhen- oder Motivgenerator für Pop.

Score erhält keine neuen Töne und keine neue Modusauswahl. Die neuen gemeinsamen Daten
sind zunächst nur beim beschriebenen Pop-Realisierungsschritt aktiv. Bestehende Bass-
Annäherungen und Score-Vorhalte werden nicht pauschal ersetzt.

## Konkreter MIDI-Nachweis über 128 Takte

2035, C-Ionisch, 120 BPM, 48 kHz. Das Original enthält unter anderem **G5 (79) → E5 (76)**.
Bei Wiederkehren ab Takt 32, 64 und 96 kommt jeweils **F5 (77)** dazwischen:

| Wiederkehrbeginn (0-basiert) | F-Einsatz relativ | F-Dauer | Reale Auflösung |
|---|---:|---:|---|
| Takt 32 | 17 Sechzehntel | 1 Sechzehntel | E bei relativ 18 |
| Takt 64 | 17 Sechzehntel | 1 Sechzehntel | E bei relativ 18 |
| Takt 96 | 17 Sechzehntel | 1 Sechzehntel | E bei relativ 18 |

Beim ersten Ereignis beginnt F bei Sample 3174000 mit Velocity 68. Sein Note-off und
das bereits vorhandene E mit Velocity 74 folgen bei Sample 3180000. Der Durchgang
schließt damit tatsächlich schrittweise G–F–E, nicht nur als Planbehauptung. Die Tonika
C und die nächste Harmoniegrenze werden nicht verletzt. Keine wichtige Motivnote wird
durch einen zufälligen Fremdton ersetzt.

Die Matrix umfasst acht Situationen × drei Tempi (90/120/173 BPM), jeweils 128 Takte,
mit/ohne Swing: kontinuierliche Pedal-/Tanzfiguren, intensive/ruhige/lyrische/synkopierte
Hooks, XY-Wechsel und gehaltene Harmonie. Mit und ohne neue Strategie werden dieselben
Quellen und identischen Wiederkehr-/Sequenzpläne nachgewiesen. In der gesamten Matrix
entstehen **neun tatsächlich aufgelöste Durchgangstöne** (drei pro Tempo im geeigneten
Fall); die anderen sieben Situationen bleiben jeweils MIDI-identisch. Diese geringe
Häufigkeit ist ein Messbefund der konservativen Eignungsregeln, kein Qualitätsziel.

`ModalTests` prüft alle vier Modi und positive Durchgänge in sämtlichen zwölf
Transpositionen, die genannten Wendungs-IDs, mehrdeutige/inkompatible Kontexte,
explizite Vorgaben, Widersprüche, Grundton-/Bass-/sonstige Halbtonkonflikte, Register,
zu kurze Zeitfenster, Harmoniegrenzen und einen wirklichen Seek in einen klingenden
Durchgangston. Der 128-Takt-Durchlauf prüft die unveränderte Quellidentität und arbeitet
ohne Allokationen im Audiothread.

`compare_modal.py` prüft jede tatsächliche neue Note und ihr reales Note-off sowie den
bestehenden Zielanschlag, Quelle, erhaltene Zielnoten und 127/512/8192-Sample-Blöcke.
Bei 90/120 BPM bleibt die Ausgabe über Blockgrößen bytegleich; bei 173 BPM gilt die
schon vorher vorhandene Grenze von maximal einem Sample bei gleichen musikalischen
Ereignissen. Die bestehende Hook-Vergleichsprobe deaktiviert nur diese neue Verzierung
als historische Kontrollkonfiguration. Score- und Groove-Regressionen laufen weiter.

MIDI-Paare und Messwerte liegen unter `/workspace/work/modal-passing`:
`case-4-without.mid` / `case-4-with.mid` (128 Takte, 4:16 Minuten bei 120 BPM).
Kanal 8 ist die Hook, Kanal 5 der Arp. `MODAL_PASSING_COMPARISON.json` enthält
Häufigkeiten, konkrete Auflösungsereignisse und vollständige MIDI-Prüfsummen.

## Grenzen

Die Eignung ist relativ zum benannten Zentrum und dem vollständigen Vorrat der Wendung,
nicht eine umfassende Tonartenanalyse. Sekundärdominanten, Mischungen und andere Modi
führen häufig bewusst zum bisherigen Verhalten. Ein erkanntes Modusvokabular allein
ändert weder die Rollenverteilung noch die kontinuierliche Groovefunktion einer Figur.

Durchgänge werden nur in unveränderten Figurenverfahren und innerhalb einer einzigen
Harmonieregion geprüft. Kein freier Lauf über Akkordgrenzen, keine Wechselnoten,
Vorhalte, chromatischen Durchgänge oder zusätzliche Bassnoten. Die schwache Position
bezieht sich zunächst auf das Sechzehntel-/Viertelraster. Eine vollständige metrische
Akzentgrammatik ist nicht Bestandteil dieses Schritts.

Der bestehende Planungshorizont und dessen Latching bei Live-Einstellungsänderungen
bleiben erhalten. Die Einschränkung harmonischer Eintrittslagen bei kaltem Seek wird
nicht verändert. Der Plugin-Dateiexport bleibt auf 64 Takte begrenzt; die separate
MIDI-/Generator-Matrix umfasst die geforderten 128 Takte. Die tatsächliche musikalische
Qualität mit den vorgesehenen Instrumenten bleibt bis zum Hörtest vorläufig.


Die historischen Vergleichstests lesen ihre Header jetzt aus der Dateiliste des jeweils
festgehaltenen Git-Stands (`reference_headers.py`). Neue aktuelle Header werden dadurch
nicht fälschlich in älteren Ständen vorausgesetzt; die bisherigen MIDI-Assertions bleiben
erhalten. Es wird keine Kompatibilitätsschicht in das Plugin eingebaut.


Abschließend bestanden: 21/21 Kern-/Vergleichstests, 1/1 Processor-Test mit zusätzlicher
ionischer Hook und realem Durchgangston im Live-/SMF-Vergleich über 64 Takte,
3/3 ASan-/UBSan-Läufe (ModalTests, HookDevelopmentTests, EngineTests) sowie 7/7
Paketprüfungen. Die erweiterten ModalTests einschließlich wiederholtem Seek/Loop und
anschließender Zielauflösung wurden zusätzlich frisch mit ASan/UBSan geprüft.
Die neue Matrix enthält 24 Vergleichspaare über je 128 Takte und 48 zusätzliche
Blockgrößenvergleiche. Keine Änderungen an GUI, Wendungsinventar oder Profilgewichten.
Kein Push, kein Release.
