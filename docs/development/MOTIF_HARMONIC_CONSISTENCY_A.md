# Motivik – Schritt A: harmonisch konsistente Planung

Ausgangspunkt: `9a8d01c`, Branch `develop/composition-core-prototype`.
Die [positiv abgenommene Referenz](ACCEPTED_REFERENCE_9a8d01c.md) bleibt Grundlage.

## Korrektur

`Generator::motifHarmonyAt()` benutzt jetzt unmittelbar `locate()` und `chordFor()`.
Damit haben Vorprüfung und Ausgabe dieselbe harmonische Zeitachse, einschließlich
Wendungseintritt mitten in der Phrase, Akkordbasis nach dem Ruhemodus, tatsächlichen
Phrasengrenzen und bereits vorhandenen harmonischen Zwischenakkorden.

Die Rückkehr-Caches speichern zusätzlich den musikalisch relevanten Harmoniekontext:
Wendung samt Akkordinhalt, Eintrittszeit, Akkordbasis, Ruhemodus, Tonart, Takt-/Phrasenlänge,
wirksame Zwischenakkord-Einstellung, Swing und Instrumentenbereich/Dauergrenzen.
Eine noch nicht begonnene Planung wird bei geändertem Kontext neu geprüft. Bei einer
solchen Neuberechnung liegen neue Kandidaten nicht vor dem aktuellen Zeitpunkt.
Auch ein früher gescheiterter Plan kann nach einem tatsächlichen Harmoniewechsel neu
geprüft werden; eine bloße XYZ-Bewegung ohne geänderten Harmoniekontext ist kein Reset.

Bei einer bereits tatsächlich angeschlagenen Figur wird der gehörte Anfang nicht neu
berechnet. Die noch kommenden Noten werden gemeinsam geprüft. Passen sie weiterhin,
bleibt die Figur erhalten; andernfalls entfallen die restlichen Anschläge in diesem
Planungshorizont. Bereits gestartete Gates können bei unvorhersehbaren späteren
Parameteränderungen ausklingen; die Vergangenheit wird nicht umgeschrieben.
Dies ist keine neue Motivtransformation und kein Neustart mitten im Gedanken.

## Gezielte Nachweise

- `MotifConsistencyTests`: tatsächliche und vorhergesagte Akkorde/Grenzen stimmen bei
  Wendungseintritten außerhalb des Taktrasters, Ruhemodus, anderer Akkordbasis sowie
  mit/ohne Zwischenakkorde überein; 3/4, 4/4, 5/4, 7/4 und entsprechende /8-Taktarten.
- Vorprüfung verändert den eigentlichen Cache nicht. Geänderte Harmoniekontexte
  erneuern vorbereitete Pläne; bereits gespielte Anfänge werden nicht erneut gestartet.
- 126 Konfigurationen aus der Motivuntersuchung erneut vollständig gerendert,
  einschließlich unbegrenzter Wiedergabe, statischem XYZ und Fahrten sowie 512-Takt-
  Langläufen. Diagnose- und direkte Produktionsausgabe sind jeweils bytegleich.
- In diesen Beobachtungen **0 Widersprüche** zwischen vorhergesagter und tatsächlicher
  harmonischer Position. Gegenüber der Referenz ändern sich 26 der 126 MIDI-Ströme.
  Die statischen musikalischen Beispiele bleiben in Schritt A erhalten.
- **837.906 geschützte Ereignisse** von Fläche, Bass, Akzenten und Controllern sind
  gegenüber `9a8d01c` unverändert. Kein Eingriff in harmonische Auswahl oder Begleitregeln.
- Gesonderte 16-Fälle-Regression protokolliert ausschließlich in Offline-Headerkopien
  die tatsächlich ausgewertete vorhandene Arpeggio-Reservierungsbedingung. Jeder
  entfernte bzw. hinzugefügte Arpeggio-Anschlag muss einer entsprechenden Änderung
  dieser Bedingung am selben Zeitpunkt entsprechen. Keine pauschale Ausnahme für Arp.
- Gezielte Tests zusätzlich mit ASan/UBSan ohne Befund; `NoAllocations` um Verarbeitung
  und Planprüfung. Keine neuen Dateioperationen oder Heap-Allokationen im Audiopfad.

Der Anwender hat unmittelbar aus korrigierten Motivfenstern entstehende Arpeggio-
Pausenänderungen ausdrücklich zugelassen. Muster, Tempo, Tonwahl und eigenständige
Begleitregeln werden nicht verändert. Die [Ergebnistabelle](MOTIF_HARMONIC_CONSISTENCY_A_RESULTS.json)
enthält sämtliche geänderten Arpeggio-Anschläge der gesonderten Regression.

## Abgrenzung

Noch keine frühe Reprise, keine neue Variation, keine veränderte Konturerzeugung.
Diese musikalische Verbesserung folgt getrennt in Schritt B. Ungeeignete Motive
können weiterhin lange pausieren. Kein neues Profil, keine GUI- oder Scheduleränderung.
Keine allgemeine Architekturänderung, kein Push und kein Release.

## Teststand beim separaten A-Commit

Gezielte CTest-Gruppe: 4/4 (`MusicalTime`, `Execution`, `ScoreRealization`,
`MotifConsistency`), zusätzliche 16-Fälle-Arpeggio-Regression, 126 vollständige
Produktions-/Diagnosevergleiche und ASan/UBSan bestanden. Tatsächlicher Plugin-
Prozessor: 2/2 Tests einschließlich Live-/Exportvergleich bestanden.
Die umfangreichen regulären Gruppen `MusicalExecutionRegression` und
`HarmonyDataRegression` bestanden ebenfalls. Der zwischenzeitliche vollständige
Suite-Lauf wird nicht als vollständige A-Abnahme ausgegeben: Die vollständige
reguläre Suite wird am zusammengeführten Endstand von Schritt B abgeschlossen.
