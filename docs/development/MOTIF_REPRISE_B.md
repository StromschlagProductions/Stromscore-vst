# Motivik B – harmonisch konsistente, erkennbare Wiederkehr

Referenz: musikalisch abgenommenes `9a8d01c`; Fehlerkorrektur A: `b4a5184`.
Diese Arbeit ändert weder Katalog, Profilgewichte, GUI noch Begleitmuster. Die
positiv abgenommene Begleitung bleibt erhalten. Ausschließlich ihre bereits
bestehenden Arpeggio-Reservierungen folgen den korrigierten Motivfenstern.

## Technische Umsetzung

`CompositionPolicy.h::MotifRecurrencePolicy` enthält `establishOriginal` und
`preserveContour`, für alle bisherigen Profile zunächst gleich aktiviert.
`ScoreEngine.h::motifOccurrence()` bietet nach der Einführung eine frühe vollständige
Reprise an. Mindestens zwei stille Takte und die tatsächlich verfügbare Phrase/
Harmonie begrenzen sie. Der ursprüngliche Gedanke wird auf ganze Takte aufgerundet;
Legato-AUS darf durch verkürzte Gates keinen früheren Einsatz erzeugen. Pro
Wiederkehrhorizont bleibt höchstens eine tatsächlich begonnene Figur erlaubt.

`CompositionCore.h::MotifRepriseProgress` ist unabhängiger Stimmenzustand. Erst die
wirklich ausgegebenen Note-ons einer vollständigen Originalreprise etablieren das
Material. Eine Berechnung, Reservierung oder Fragmentwiedergabe genügt nicht.
Vor diesem Nachweis werden weder stärkere Varianten noch Fragmente oder zusätzliche
Durchgangstöne anstelle des Originals eingesetzt. Danach bleibt die vorhandene
zurückhaltende Variationsstrategie verfügbar. Das gespeicherte Original bleibt
unverändert; Melodie und Dialog teilen Material, aber keinen Fortschritt.

`fittedMotifDegree()` verschiebt zunächst die ganze Vorlagenkontur in den verfügbaren
Akkordtonvorrat. Nur falls dieser dafür zu eng ist, wird ihre Spannweite proportional
komprimiert. Die bisherige unabhängige Begrenzung aller Stufen konnte eine ganze
Figur unbeabsichtigt auf denselben Ton zusammenziehen. Ein real nur eintönig
spielbarer Bereich kann selbstverständlich keine Mehrtonkontur garantieren.

`continueMotif()` nutzt die vorhandene begrenzte harmonische Realisierung für eine
bereits begonnene Originalreprise: Der tatsächlich gehörte Anfang bleibt exakt
fixiert; ausschließlich zukünftige Noten dürfen an die aktuelle Harmonie angepasst
werden. Einsatzzeiten und Konturrichtung bleiben erhalten, Intervallschritte ändern
sich höchstens um zwei Halbtöne. Der stärkste Schritt bleibt bei neuen Einsätzen
exakt; bei festem gehörtem Präfix darf er um höchstens einen Halbton abweichen.
Notenlängen dürfen nach den vorhandenen Regeln an Harmoniegrenzen verkürzt werden.
Wenn das nicht passt, entfällt der Rest. Varianten werden damit nicht fortlaufend
umgeformt. Keine zusätzliche Motiv-Engine oder veränderte Harmonieplanung.

Der Dispatcher erhält weiterhin den bestehenden Veröffentlichungstermin der
wirklich gespielten Einführung, auch wenn seine lokale Vorschau schon vollständig
ist. Warmes Chase rekonstruiert frühere Einsätze ohne deren Pausenbudget für einen
zukünftigen Einsatz zu verbrauchen. Die vorhandene Dialog–Arpeggio-Antwort direkt
nach einer Einführung bleibt ausdrücklich erhalten.

## Reproduzierbare musikalische Ergebnisse

126 vollständige Produktionsrenderings plus gleichlange Diagnosegegenstücke;
Hauptmatrix je 128 Takte bei 100 BPM, 4/4, D, Variationen 1/3/7. Interne Fahrt,
Szenenbegrenzung und Aufbau AUS. Sechs statische Positionen sowie langsame und schnelle
externe XYZ-Fahrten je Kontext. Ergänzungen: Einzelstimmen, Motiv AUS, feste Harmonien,
begrenzte Szene, Aufbau, enge Register, 3/4, Tonarten und sechs 512-Takt-Läufe.
Alle Diagnose-/Produktionsströme sind identisch. Rohdaten bleiben außerhalb des
Repositorys; Konfigurationen, Quellheader-Prüfsummen und Auswertung stehen in
`MOTIF_REPRISE_RESULTS.json`.

Abstand vom Einführungsbeginn zur ersten **vollständig ausgeführten Originalreprise**
der Hauptmelodie, Median nur über tatsächlich erfolgreiche Fälle:

| Kontext | Bewegung | Referenz | Nur A | A+B |
|---|---|---:|---:|---:|
| Neutral | statisch, 18 Fälle | 12 Takte | 12 | 4 |
| Barry | statisch, 18 Fälle | 8 | 8 | 3 |
| Pop/Rock | statisch, 18 Fälle | 8 | 8 | 4 |
| Neutral | langsame Fahrt, 3 Fälle | 24 | 24 | 24 |
| Barry | langsame Fahrt, 3 Fälle | 8 | 8 | 3,75 |
| Pop/Rock | langsame Fahrt, 3 Fälle | 8 | 8 | 4 |
| Neutral | schnelle Fahrt, 3 Fälle | 24 | keine vollständige | 24 |
| Barry | schnelle Fahrt, 3 Fälle | 8 | 8 | 3 |
| Pop/Rock | schnelle Fahrt, 3 Fälle | 8 | 24 | 6 (2/3 Fälle) |

Die schnelle Pop-Fahrt bleibt ein Gegenbeispiel: In einem Fall gelingt keine ganze
Originalreprise. Die frühere Ausgabe ist dabei kein korrekter Qualitätsmaßstab,
weil sie zwischengespeichertes Material teilweise gegen veraltete Harmonie spielte.
Kein Anspruch auf Wiederkehr innerhalb weniger Phrasen bei jeder Parameterfahrt.

In den statischen Hauptmelodieläufen steigt die Zahl vollständig gespielter
Originalreprisen von 118 auf 133 (Neutral), 120 auf 138 (Barry) und 92 auf 116 (Pop).
Varianten/Fragmente bleiben ausdrücklich möglich. Vollständige Figur bedeutet
nicht automatisch unveränderte Tonintervalle: Harmonische Anpassungen sind separat
gekennzeichnet. Quellenidentität allein beweist ebenfalls keine Wiedererkennbarkeit.

Die mediane Gate-Auslastung der Hauptmelodie bleibt in statischen Läufen
zurückhaltend: Neutral 17,38 → 18,95 %, Barry 9,77 → 10,55 %, Pop 14,55 → 17,33 %.
Die vorhandenen expliziten Melodie–Dialog-Übernahmen bleiben dort erhalten
(Neutral 3, Barry 57 Materialreferenz-Übernahmen über jeweils 18 Läufe).
Ein positiver Median beseitigt keine Einzelfalllücke: Die längste Hauptmelodie-Stille
bei statischem Neutral beträgt noch 242,4 Sekunden statt 252 Sekunden.

## Konkrete Hörstellen

Das ZIP `MOTIF_REPRISE_AB.zip` enthält vier wirkliche 128-Takt-A/B-Läufe, jeweils
Gesamtmix und nachträglich gefilterte Melodie/Dialog-Spuren: 16 MIDI-Dateien, dazu
Notentabellen, Herkunftsreferenzen, Marker und Anleitung. Keine Neukomposition für
Solo-Spuren, keine erfundenen Ersatznoten.

* Neutral, XYZ 0,85/0,85/0,30, Variation 3: C5–Es5–A4–C5–Fis5
  (MIDI 72/75/69/72/78) über vermindertem Septakkord, relative Einsätze
  0/2/3/3,5/4 Viertel. Früher nächste Reprise Takt 108; jetzt Takt 5,
  vollständig um einen Halbton transponiert: 73/76/70/73/79.
* Barry, XYZ 0,25/0,85/0,65, Variation 1: M22, D4–D4–A4–D4
  (62/62/69/62), Viertelraster. Früher erste Reprise Takt 9, jetzt Takt 4:
  Es4–Es4–B4–Es4 (63/63/70/63). Unabhängige Dialogantworten mit anhören.
* Barry M07 auf langsamer Fahrt: A4–D5–Cis5–D5 zweimal als Achtelzelle.
  Die Halbtonbeziehung begrenzt passende Wiederkehren bei wechselnder Harmonie;
  dieser Grenzfall wird ausdrücklich mitgeliefert.
* Pop: motorischen Dialoghook und zurückhaltende Hauptmelodie getrennt verfolgen.
  Kontinuierliche Hooks werden nicht künstlich zu pausierenden Score-Motiven gemacht.

Diese MIDI-Nachweise zeigen frühere vollständige Wiederkehr und bewahrte Konturen.
Ob dadurch die musikalische Wiedererkennbarkeit im Hörspielmix ausreichend besser
wird, bleibt der Hörabnahme vorbehalten.

## Schutz der Begleitung und Testmethodik

In allen 126 Fällen bleiben 837.906 Ereignisse von Fläche, Bass und Akzenten
nach kanonischer Sortierung identisch zu `9a8d01c` und Schritt A. Samplezeit,
Ziel, Kanal, Tonhöhe, Velocity und Note-on/-off bleiben exakt erhalten. Lediglich
gleichzeitige Freigaben verschiedener physischer Noten können in anderer
Interleaving-Reihenfolge im Eventpuffer stehen, weil die aktive Notenliste auch
die geänderten melodischen Noten enthält. Die Reihenfolge desselben physischen
Tons bleibt streng erhalten. Dafür wird kein musikalischer Patch zurückgebogen.
Die verwendeten harmonischen Katalog-IDs bleiben
gleich. Arpeggioänderungen werden separat durch `MotifWindowRegression` geprüft:
Jeder hinzugekommene/entfallene Anschlag muss exakt durch einen geänderten Wert der
bestehenden Motivreservierung erklärt sein. Die 22 geprüften Fälle einschließlich jedes hinzugekommenen/entfallenen
Anschlags stehen in `MOTIF_REPRISE_ARP_WINDOWS.json`: über die 16 automatischen
Vergleichsläufe entfallen 819 Arp-Anschläge und kommen 52 zurück; in allen sechs
manuellen Kontrollen ändern sich null Anschläge. Ereignistupel enthalten
Sampleposition (48 kHz), Ausgabeindex, MIDI-Kanal, Tonhöhe, Velocity und Typ.
Manuell gewählte Arpeggiofiguren bleiben
gleich. Keine geänderte Arp-Tonwahl, kein neues Muster und kein anderes Tempo.

Historische Einzel-Feature-Experimente verwenden über `Tests/MotifExperiment.h`
explizit deaktivierte neue Reprisen-/Konturpräferenzen, damit beispielsweise ein
Akkordbesetzungs-Test weiterhin genau diese Änderung isoliert. Dieser Helfer ist
nur offline eingebunden, niemals im Plugin. Die neuen Standardwerte werden durch
`MotifReprise`, die 126 tatsächlichen Produktionsläufe, die Reservierungsregression
und echte Plugin-Prozessor-/Exportprüfungen getestet. Historische Aktivitätsprüfungen
schützen Fläche/Bass/Akzente sowie Notenbuchhaltung und Rollenüberschneidung; sie
verlangen keine unveränderten melodischen oder reservierungsbedingten Arp-Ströme.

## Grenzen

Kein Langphrasenkomponist, keine neue Formgrammatik. Ursprüngliche kurze Zellen
bleiben kurz. Die Maßnahme etabliert das vorhandene Material vor dessen Entwicklung,
behebt aber nicht alle späteren langen Wiederkehrabstände. Schnelle XYZ-Fahrten,
enge Register und ungeeignete Harmonie dürfen weiterhin zu Pausen führen. Kaltes
Seek ohne musikalische Vorgeschichte bleibt die akzeptierte Einschränkung.
Keine Studio-One-/Windows-Hörabnahme in dieser Umgebung; kein Push oder Release.

## Gezielte Prüfungen

* `Execution`, `ScoreRealization`, `MotifConsistency`, `MotifReprise`: 4/4 bestanden.
  Enthalten harmonische Kontextwechsel, unveränderliches Original, tatsächliche
  statt spekulative Etablierung, unabhängige Stimmenzustände, Register, Pause,
  unbegrenzten Neustart sowie warmes Seek/Loop.
* Frisch gebauter JUCE-Plugin-Prozessor: `Processor` und `ProcessorProfileSwitch`,
  2/2 bestanden, einschließlich tatsächlichem Live-/Exportvergleich.
* Aktueller Motivkern separat unter ASan und UBSan: `MotifReprise` und
  `MotifConsistency` bestanden. Die Prüfungen umfassen auch `NoAllocations`-Blöcke.
* Zwölf zusätzliche Produktionsvergleiche bei 127/8192 statt 512 Samples: bytegleich,
  statische und bewegte XYZ-Verläufe in allen drei Kontexten.
* Paketprüfungen `Tests/ReleaseTests.py`: 7/7 bestanden; keine Veröffentlichung.
* Alle 16 MIDI-Dateien erneut decodiert: Ereignisse stimmen vollständig mit den
  tatsächlichen Rohströmen überein. ZIP-CRC und Produktionsheader-Prüfsummen geprüft.

Die historischen Hook-/Modalvergleiche behalten ihre ursprünglichen Referenzen
für statische Fälle. Der externe XYZ-Fahrt-Fall wird zusätzlich bytegenau gegen
`b4a5184` mit derselben historischen Pool-/Rollenfixture verglichen: Der absichtlich
reparierte Harmonie-Cache darf nicht wieder auf die alte Ausgabe zurückregredieren.
Unvollständig ausgeführte dynamische Vorpläne sind keine Pflicht zur Wiedergabe
harmonisch unpassender Restnoten; Notenbilanz, Blockvergleich und der komplette
korrigierte Referenzstrom bleiben streng geprüft. Die isolierten Hooktests setzen
den Motivschalter jetzt ausdrücklich EIN. Der Diagnosezeitpunkt wird bei 173 BPM
auf den tatsächlich gespielten geswingten Einsatz bezogen, statt durch Abrunden
eines samplegerundeten Zeitwerts irrtümlich in der vorigen Planungsposition zu landen.
Diese Korrektur betrifft ausschließlich die Offline-Auswertung, keinen Scheduler.

Die vollständige reguläre Core-Suite besteht nach sauberem Neuaufbau mit **56/56**
Tests (986,25 Sekunden). Darin bestehen auch die vollständige Harmonie-Datenregression,
die Ausführungsregression einschließlich der 98 historischen Zeitkorrekturen,
Score-/Pop-Aktivität, Reservierungen, Hook-/Modalvergleiche, Akkordbesetzung, Bass,
Rhythmus, Wiederkehr, Phrasen, Dichte, Begleitung sowie Transport-/Notenprüfungen.
Zusammen mit den separat frisch gebauten Prozessorprüfungen sind **58/58 CTest-Fälle**
erfolgreich. Die zwei gezielten ASan-/UBSan-Programme und sieben Paketprüfungen
kommen zusätzlich hinzu. Kein behaupteter Studio-One-Hörtest.

Umgesetzt wurden ausschließlich die beauftragten Schritte A und B. Kein Push,
kein Release und kein anschließender Entwicklungsschritt.
