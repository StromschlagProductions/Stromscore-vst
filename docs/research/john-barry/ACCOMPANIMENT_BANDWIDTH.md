# Barry – Bandbreite der automatischen Begleitung

Ausgangspunkt: `11abda9`, `develop/composition-core-prototype`.
Dieser Schritt ändert ausschließlich die automatische Score-Barry-Begleitung.
Harmoniekatalog, XYZ-Auswahl, Profilgewichte, Forschungsoriginale, Motivkern,
Melodie-/Dialogplanung und GUI bleiben unverändert.

## Befund und Ursache

Der Anwenderbefund ist durch den Produktionspfad erklärbar, unabhängig von der
bereits behobenen Profilwechsel-Blockade:

- `Generator::choosePad()` gab im Barry-Auto-Pfad **immer `PadHeld`** zurück.
  Kein Intensitäts- oder Unruhewert konnte eine kurze Fläche auswählen.
- `rawBassPattern()` verließ den Barry-Zweig vor den bestehenden
  intensitätsabhängigen Bassentscheidungen. Die Barry-Spielrezepte bevorzugen
  ausschließlich gehaltenen Bass/Pedal bzw. gehaltenen Bass/Halbe.
- `arpeggioPeriod()` begrenzte die nicht ausdrücklich notierte Auto-Bewegung auf
  Achtel. Nur ausgewählte notierte Rhythmuszellen konnten das überschreiten.
- `authoredRhythmBar()` unterdrückte Bassvorlagen unter Bassintensität 0,30,
  obwohl etwa JB-R01 und JB-R11 ihre eigenen Anker bei Y = 0,15 haben.
- Der Rhythmusselektor deckt bewusst nur einen Radius von 0,25 in der vorhandenen
  gewichteten XYZ-Metrik ab. Außerhalb passender R-Zellen blieb deshalb gerade
  die sehr statische Rückfallstrategie übrig. Diese Auswahlgrenze wurde nicht
  durch eine erzwungene entfernte Rhythmusvorlage ersetzt.

Die bisherigen isolierten Vorlagentests verwendeten passende Custom-Harmonik,
Solo-Bass/Arp und für die R-Prüfung einen künstlichen Layer-Boost auf maximale
Intensität. Die Farbtests prüften zudem ausdrücklich manuell gehaltene Flächen.
Sie bewiesen die Darstellbarkeit der Zellen und Akkorde, aber nicht die
musikalische Bandbreite der tatsächlichen Auto-Begleitung im Feld. Die neuen
Tests prüfen deshalb ausdrücklich auch Auto-Fläche und echte R-Anker ohne Boost.

## Begrenzte musikalische Änderung

Alle Entscheidungen verwenden vorhandene Figuren und denselben Dispatcher.
Es gibt kein neues Rhythmussystem und keine neuen Harmonievorlagen.

### Fläche

Manuelle Spielweisen und Szeneneinstieg-Overrides behalten Vorrang. Bei Auto:

| Kontext, Intensität der Flächenrolle | Vorhandene Spielweise |
|---|---|
| Y < 0,55 bzw. ruhiger mittlerer Kontext | Gehalten |
| Y ≥ 0,55 und Z ≥ 0,40 | Kurze Synkopenschläge auf den Achtel-Offbeats |
| Y ≥ 0,80, Z < 0,60 | Viertelpuls |
| Y ≥ 0,80, Z ≥ 0,60 | Viertel-Staccato |
| Y ≥ 0,60, Z ≥ 0,95 | Gehackte Achtel als begrenzte Zuspitzung |

Die Priorität ist von unten nach oben zu lesen: Die Eskalationszone hat Vorrang.
Unterhalb dieser obersten Zone behalten ausgewählte statische Diminutionszellen
JB-R05/JB-R26 ihr gehaltenes harmonisches Fundament. Die Harmonie wird dadurch
nicht schneller gewechselt oder umgefärbt.

### Bass

Unter Y = 0,30 bleibt die generative Präferenz für gehaltenen Bass erhalten.
Geeignete notierte ruhige Basszellen dürfen dort nun trotzdem tatsächlich spielen;
im Ruhemodus wird keine solche Basszelle erzwungen.

Außerhalb einer notierten Basszelle werden die bisherigen bewegten Bassmuster
wieder erreichbar: Bei mittlerer Energie (Y ≥ 0,55 bis 0,80) und Unruhe Z ≥ 0,50
ein Viertelpuls; bei hoher Intensität die bereits vorhandenen Achtelentscheidungen.
Ab Y ≥ 0,60 und Z ≥ 0,95 kann das vorhandene Grundton-/Quintpendel übernehmen.
Es entsteht kein zweiter Sechzehntel-Motor im tiefen Register. Notierte Basszellen
behalten ihren Vorrang – insbesondere darf der lange Bass einer Diminutionszelle
lang bleiben, während sich deren Oberfigur verdichtet.

Follow EIN/AUS und explizite Bassvorgaben verwenden weiterhin die vorhandenen
harmonischen Funktionen. Die bereits vorhandenen Bassmuster können ihre bisherigen
chromatischen Annäherungen verwenden; es wurde keine neue Bassphrasenplanung ergänzt.

### Arpeggio und Black Hole

Die Barry-Policy erlaubt jetzt als schnellsten Auto-Wert Sechzehntel. Außerhalb
notierter Zellen werden diese nur ab Arp-Intensität 0,65 **und** Unruhe 0,60
freigegeben. Ruhigere Kontexte behalten Viertel/Achtel. Manuelle Figur und Rate
sind davon ausgenommen.

Im 3/4-Auto-Kontext mit Z ≥ 0,40 wird die vorhandene Kreisfigur bevorzugt.
Das erschließt insbesondere JB-R04 und JB-R26 als tatsächlich kreisende Figuren.
Der Host muss dafür **3/4** liefern; ein 4/4-Projekt wird nicht heimlich umgetaktet.

- JB-R04: sechs Achtelanschläge pro 3/4-Takt.
- JB-R26: sechs Achtel, dann zwölf Sechzehntel im zweiten 3/4-Takt.
- JB-R05 in 4/4: 4 → 8 → 16 → 8 Anschläge über vier Takte.

Die notierten Raster, Pausen und Akzente werden nicht durch die neue Auto-Rate
ersetzt. Motiv- und Antwortreservierungen dürfen das Arp weiterhin gezielt
aussetzen lassen. Keine dieser Zellen wird als Originaltranskription ausgegeben:
Der kreisende Typ und die Diminution orientieren sich an der Forschung,
die konkreten Raster sind eigene Konstruktionen.

### Wechsel der Lang-/Kurz-Spielweise

Beim ersten tatsächlich ausgegebenen kurzen Auto-Anschlag beendet `noteOn()`
alte Ansprüche des langen Patches **derselben Begleitrolle**. Sonst könnte ein
zuvor acht Takte gehaltener Klang den neu gewählten Rhythmus weiterhin verdecken.
Andere Rollen und manuelle Muster werden dabei nicht verändert. Die bestehende
MIDI-Verwaltung berücksichtigt weiterhin gemeinsame physische Kanäle und Noten.

## Prüfungen und reproduzierbare Messung

- `Tests/BarryAccompanimentTests.cpp`: echte lange/kurze Auto-Ausgaben,
  Energie/Unruhe und die Eskalationszone, Freigabe langer Patches beim Wechsel,
  sieben Basszellen an ihren tatsächlichen XYZ-Ankern ohne Layer-Boost,
  Seek/Loop/Neustart, Swing, sechs Taktarten und Blockgrößen 127/512/8192.
- `BarryVocabularyTests`: weiterhin exakte Ausführung aller 16 bereits aktiven
  R-Vorlagen in passenden isolierten Kontexten; R05/R14/R26 zusätzlich mit
  automatischer produktiver Harmonieauswahl. Die 20 Motivvorlagen bleiben geschützt.
- `ProcessorTests`: zusätzliche echte Live-/Exportfälle mit allen Rollen,
  Auto-Begleitung, hoher Intensität und Z = 0,85 bzw. 1,00.
- `scripts/analyze_barry_accompaniment.py --output <Ordner>` kompiliert dieselbe
  Produktionsprobe gegen `11abda9` und den Arbeitsstand und rendert je 128 Takte.
  Statische Rand-/Mittelpositionen, langsame/schnelle Fahrten, Variationen,
  Follow, Swing, 3/4/4/4/6/8 sowie manuelle Regressionen werden getrennt geprüft.

Die Probe protokolliert zusätzlich die tatsächlich im Generator gehaltene R-ID.
Eine R-ID ist allein kein Beweis für einen gespielten Rhythmus: Die Auswertung
verknüpft sie mit realen Bass-/Arp-Note-ons; exakte Rastergleichheit wird separat
durch die Vorlagentests geprüft. Keine Auswahlstatistik ersetzt die MIDI-Ausgabe.

Bei nichtganzzahliger Samples-pro-Viertel-Auflösung bleibt die bereits vorhandene
Rundungsabweichung bis zu einem Sample zwischen Blockgrößen gesondert sichtbar.
Die Tests verlangen gleiche Notendaten und gleiche 960-PPQ-Positionen; der
Scheduler wird in diesem Auftrag nicht verändert. Der Vergleich enthält dafür
eigene manuelle Kontrollfälle auf beiden Revisionen bei 90 und 173 BPM.

## Tatsächliche MIDI-Ausgabe über 128 Takte

Die Auswertung enthält **80 Vorher-/Nachher-Paare**. Tonart D, 100 BPM,
Variation 3 sofern nicht anders angegeben, Abwechslung 0,5, Trägheit EIN,
Melodie und beide Motivschalter EIN, kein Szenenaufbau, keine Layer-Boosts.
Die zusätzlichen Tempo-/Follow-/Swing-/Variationsfälle sind in
`ACCOMPANIMENT_BANDWIDTH_MEASUREMENTS.json` einzeln beschrieben.

**19 geschützte Vergleichspaare** (Neutral/Herrmann Score, alle bisherigen
Pop/Rock-Profilparameterwerte, vollständig manuelle Begleitung und
Tempo-Kontrollen) behalten sämtliche musikalischen MIDI-Ereignisse einschließlich
Reihenfolge und Samplepositionen exakt bei. Zusätzlich bleiben in sämtlichen
Vergleichspaaren die zeitlich bestimmten Ereignisse von Melodie, Dialog,
Tupfer und Stich erhalten. Zwischen unterschiedlichen Rollen gleichzeitig
auftretende Ereignisse können in den veränderten Barry-Fällen anders im
Ausgabepuffer stehen; das ist keine Änderung ihrer Töne, Dauern oder Einsätze.
Alle Notenledger enden ausgeglichen.

### Anschläge und gehaltene/kurze Ziele

Die Zahlen zählen **unterschiedliche Anschlagszeitpunkte pro MIDI-Ziel**, bei
Flächen also Akkordanschläge statt jeden gleichzeitig gespielten Akkordton.
L/K bedeutet Lang-/Kurz-Ausgang. Arp-Zahlen berücksichtigen die unveränderten
Motivreservierungen; deshalb sind sie nicht einfach 128 × Rasterlänge.

| Kontext XYZ, 4/4 | Stand | Fläche L / K | Bass L / K | Arp |
|---|---|---:|---:|---:|
| Warm 0,80 / 0,30 / 0,10 | vorher | 27 / 0 | 31 / 0 | 486 |
| Warm 0,80 / 0,30 / 0,10 | nachher | 27 / 0 | 31 / 0 | 486 |
| Mittel 0,00 / 0,60 / 0,50 | vorher | 32 / 0 | 128 / 0 | 898 |
| Mittel 0,00 / 0,60 / 0,50 | nachher | 0 / 512 | 0 / 544 | 898 |
| Hoch, Z = 0,94: 0,85 / 0,95 / 0,94 | vorher | 96 / 0 | 192 / 0 | 956 |
| Hoch, Z = 0,94: 0,85 / 0,95 / 0,94 | nachher | 0 / 512 | 0 / 1.024 | 1.912 |
| Zuspitzung: 0,85 / 0,95 / 0,95 | vorher | 96 / 0 | 192 / 0 | 956 |
| Zuspitzung: 0,85 / 0,95 / 0,95 | nachher | 0 / 1.024 | 0 / 1.024 | 1.912 |
| Maximum: 0,85 / 1,00 / 1,00 | vorher | 96 / 0 | 192 / 0 | 956 |
| Maximum: 0,85 / 1,00 / 1,00 | nachher | 0 / 1.024 | 0 / 1.024 | 1.912 |

Im warmen Vergleich bleiben nicht nur diese Zähler, sondern alle MIDI-Ereignisse
unverändert. Die mediane Länge von Fläche/Bass beträgt dort weiterhin 9,6 s.
Im kräftigen Z=0,94-Fall sinkt die mediane Flächendauer von 4,8 s auf 0,15 s;
der Bass verwendet Achtelgates von 0,30 s statt der zuvor medianen 1,05 s.
Ab Z=0,95 kommen acht statt vier kurze Flächenanschläge pro Takt hinzu, während
der Bass bei acht Einsätzen bleibt, aber als kürzer artikuliertes Tonpendel
mit 0,15-s-Gates spielt. Das Arp wird nicht zusätzlich über Sechzehntel hinaus
beschleunigt. Die Zuspitzung aktiviert also nicht drei immer schnellere Motoren.

Auch geringe Intensität kann nun notierte Bewegung tragen: JB-R01 an
0,45 / 0,15 / 0,10 liefert **256 statt 39 Bassanschlägen**, weiterhin am Langziel,
mit median 1,2 s. JB-R11 (6/8) liefert **256 kurze statt 26 langer Bassanschläge**.
JB-R17 (ruhiges 3/4) liefert **256 kurze statt 28 langer Bassanschläge**.
Diese Fälle sind keine hohe Dichte, sondern jeweils zwei bewusst gesetzte
Basstöne pro Takt. Die ruhige Flächenausgabe bleibt dort unverändert.

Die kontinuierlichen Fahrten zeigen ebenfalls kurze und lange Phasen statt
eines dauernden Kurzmodus. Je 128 Takte, Variation startet bei 3 und wird
in Achtaktabschnitten zyklisch verändert:

| Fahrt | Stand | Fläche L / K | Bass L / K | Arp |
|---|---|---:|---:|---:|
| Langsame XYZ-Fahrt | vorher | 53 / 0 | 58 / 260 | 740 |
| Langsame XYZ-Fahrt | nachher | 24 / 303 | 20 / 576 | 849 |
| Schnelle XYZ-Fahrt | vorher | 249 / 0 | 181 / 223 | 738 |
| Schnelle XYZ-Fahrt | nachher | 146 / 279 | 95 / 496 | 854 |

Die drei unterschiedlichen Startvariationen 1/3/7 liefern nachweisbar
unterschiedliche vollständige Renderings. Ihre jeweils passenden
Vorher-/Nachher-Vergleiche schützen trotzdem die melodischen Rollen.

### Tatsächlich verwendete R-Zellen

In der Langzeitmatrix sind alle 16 bereits aktiven IDs mit Anschlägen ihrer
jeweils notierten Rolle vertreten:
**R01, R02, R03, R04, R05, R08, R10, R11, R13, R14, R17, R18, R20,
R22, R24 und R26**. Ein Bassanschlag wird nur einer R-ID zugerechnet, wenn
diese auch eine Bassvorlage besitzt; entsprechend beim Arp nur einer
Bewegungsvorlage. Generische Rückfallanschläge bei einer bloß im Cache
stehenden, für eine andere Rolle geltenden R-ID zählen nicht als ihre Ausführung.

Eine Position ist trotzdem kein exklusives Preset: Im R05-nahen 4/4-Fall
0,30 / 0,75 / 0,70 wechseln bei Abwechslung 0,5 geeignete R05- und R13-Kontexte,
weil nicht jede gewählte Harmonie die notwendige vierteilige statische Zelle
trägt. In der tatsächlichen R05-Zelle bleiben die gehaltenen Fundamente
erhalten; im anderen Kontext darf die Begleitung nun rhythmisch werden.
Die exakten vollständigen Zellraster werden zusätzlich isoliert und mit
geeigneter automatischer Harmonie geprüft, nicht aus einem Auswahlzähler vermutet.

### Hörbares R26-Beispiel

Produktiver 3/4-Fall, XYZ 0,30 / 0,65 / 0,55, ab Takt 3. Die ersten beiden
Takte können durch die unveränderte Melodieeinführung für das Arp reserviert sein.
Die folgenden Einsatzzeiten sind absolute Viertelnotenpositionen:

```text
Einsätze: 6  6,5 7  7,5 8  8,5 | 9  9,25 9,5 9,75 10 10,25 10,5 10,75 11 11,25 11,5 11,75
Vorher:  81 77  74 69  65 62  | 81 77   74  69   65 62    81   77    74 69    65   62
Nachher: 69 65  62 65  69 74  | 77 81   77  74   69 65    62   65    69 74    77   81
```

Die Zahlen sind tatsächlich ausgegebene MIDI-Tonhöhen. Vorher läuft eine
absteigende Figur wieder von oben an; nachher entsteht eine Kreisbewegung.
Die rhythmische Verdichtung bleibt sechs Achtel → zwölf Sechzehntel.
Im gesamten R26-Vergleich bleiben **128 lange Bassanschläge und 969 Arp-Anschläge**
erhalten – ein Beispiel dafür, dass eine musikalische Änderung nicht allein
durch mehr Noten nachgewiesen wird. Zusätzlich prüft der kontrollierte
R26-Test die symmetrische Kreisfolge über einem MinMaj9-Feld mit drei Variationen.

### Zeitrundung und Audio-Thread

Bei 173 BPM zeigt der isolierte neue Auto-Fall eine maximale Blockdifferenz von
einem Sample (D, MinMaj7 über acht Takte, XYZ 0,85 / 0,95 / 0,85, 16 gerenderte
Takte, Blöcke 512/127); Notendaten und 960-PPQ-Positionen stimmen überein. Die gezielte
Kontrolle gegen `11abda9` zeigt dieselbe Abweichung bereits mit den dort manuell
gewählten identischen Staccato-/Achtelbass-/Sechzehntel-Arp-Figuren. Deren
vollständige Ereignisprüfsumme entspricht dem neuen Auto-Fall. Es wurde kein
Zeitbasis-Umbau vorgenommen. Die separaten produktiven manuellen Tempo-Kontrollen
bei 90/173 BPM sind in beiden Revisionen ohne Sampleabweichung; die Toleranz wird
also nicht pauschal als Abweichung aller Fälle ausgegeben.

Die zusätzlichen Laufzeitentscheidungen verwenden vorhandene Daten, feste
Muster und die begrenzte aktive Notenliste. Es gibt keine neuen Audiothread-
Dateioperationen, Parser oder Heap-Allokationen. Die Prozessortests prüfen die
Verarbeitung weiterhin mit Allokations-/C-Heap-Wächtern.

### MIDI-Hörvergleiche

[MIDI-A/B-Paket](ACCOMPANIMENT_BANDWIDTH_MIDI_AB.zip): 16 Standard-MIDI-Dateien,
acht Vorher-/Nachher-Paare zu warm, R04/R05/R26, Z=0,94/0,95/1,00 und schneller
XYZ-Fahrt. Ordner `11abda9` = vorher, `working` = dieser Stand. Das Paket enthält
eine deutschsprachige Kanal-/Tempo-/Taktart-Anleitung. Je 128 Takte bei 100 BPM:
4/4 dauert 5:07,2 Minuten, 3/4 dauert 3:50,4 Minuten. Gleiche geeignete Lang-/Kurz-
Patches für A/B verwenden; es sind MIDI-Ausgaben, keine Audio- oder Original-Cue-Aufnahmen.

## Abschließende technische Prüfung

- **53/53 Core-Tests bestanden**, vollständige reguläre Suite einschließlich
  historischer MIDI-, Scheduler-/Swing-, Harmonie-, Motiv-, Rhythmus-,
  Phrasen- und Begleitvergleiche sowie der Profilwechsel-Regression.
- **2/2 echte Prozessor-/GUI-Gruppen bestanden**, einschließlich der zwei
  zusätzlichen kräftigen/maximalen Barry-Auto-Fälle mit tatsächlicher
  Live-/Exportgleichheit und Note-ons auf Fläche Kurz, Bass Kurz und Arp.
- **ASan/UBSan 3/3 Gruppen bestanden:** `Barry`, `BarryAccompaniment`,
  `BarryVocabulary`. Nach Ergänzung des expliziten R26-Kreisfolgetests wurde
  `BarryAccompaniment` frisch gebaut und nochmals erfolgreich geprüft.
  Leak-Erkennung war wie im vorhandenen Aufbau deaktiviert.
- **80 × 128-Takte-Vergleichspaare** gegen `11abda9` bestanden, zusätzlich
  ausgewählte 127/8192-Blockvergleiche gegen 512. Alle 16 aktiven R-IDs sind
  mit realen Anschlägen ihrer notierten Rollen im Langzeitkorpus vertreten.
- Der neue Bandbreitentest schlägt gegen die unveränderten Header von
  `11abda9` an der fehlenden kurzen Auto-Fläche im mittleren Kontext fehl;
  mit der Korrektur besteht er. Er prüft also eine tatsächlich fehlende Fähigkeit.
- **Linux-x64-VST3 gebaut**, **7/7 Paketprüftests bestanden**.
  Beide Offline-Datenprüfer bleiben erfolgreich; die originalen Forschungsdaten,
  Harmoniedaten, Akkorddefinitionen und Profilgewichte wurden nicht geändert.
- Messdatei gegen die SHA-256-Werte der tatsächlich verwendeten Produktionsheader
  geprüft; MIDI-ZIP mit 16 MIDI-Dateien plus Hörhinweisen auf CRC/Struktur geprüft;
  `git diff --check` sauber.

Kein Windows-Build, Push oder Release in diesem Auftrag. Nach dem lokalen Commit
keine weitere musikalische Entwicklung ohne neuen Auftrag.

## Grenzen

- Kein neuer vollständiger Black-Hole-Cue, keine Langphrasen-/Form- oder
  motivabhängige Schichtentwicklung und keine automatische Instrumentierung.
- Nur die bereits aktiven 16 R-Zellen; zurückgestellte Forschungsformen werden
  nicht neu importiert oder pauschal als implementiert bezeichnet.
- Die vorhandene Zellenauswahl bleibt bis zum nächsten Harmonie-/Phraseneintritt
  stabil; eine XYZ-Fahrt tauscht nicht nach jedem Parameterwert die laufende Zelle.
- Die neue Begleitbandbreite ist durch MIDI nachweisbar. Ob die konkrete Balance
  im Hörspiel und mit den verwendeten Lang-/Kurz-Patches überzeugt, bleibt bis
  zur erneuten Hörabnahme vorläufig. Z ≥ 0,95 ist eine redaktionelle Engine-Entscheidung,
  keine aus Barry-Partituren gemessene Schwelle.
