# STROMSCORE – musikalische Forschung

## Lesereihenfolge
1. `john-barry/Stilprofil_John_Barry.txt`
2. `shared/Musikalisches_Vokabular_Gesamtfassung_2026-11-24.txt` – maßgebliche bereinigte Gesamtfassung für den Inventarabgleich; enthält Barry, Herrmann und Wang-Chung-Abgleich.
3. `bernard-herrmann/Stilprofil_Bernard_Herrmann.txt` – für die spätere Herrmann-Phase.

`archive/` enthält die ältere Erstfassung und Ergänzung zur Nachvollziehbarkeit. Laut Vorspann ersetzt die Gesamtfassung beide; nicht als zusätzliches Vokabular importieren. Bei Widersprüchen die Gesamtfassung bevorzugen und offene Fragen dokumentieren.

## Arbeitsregeln
- Originaltexte sind bytegetreu übernommen und lediglich umbenannt.
- Forschungsbelege, Interpretationen, Hypothesen und eigene Konstruktionen gemäß den Evidenzmarkierungen unterscheiden. Keine konstruierten Töne als Transkriptionen ausgeben.
- Schwerpunkt der ersten Implementierungsphase: John Barry, insbesondere The Black Hole und A View to a Kill, aber das gesamte XYZ-Feld abdecken.
- STROMSCORE dient überwiegend zurückhaltendem Hörspiel-Underscoring; keine universelle Kompositionsplattform.
- Die Unterlagen sind Forschungsgrundlage, keine bereits implementierten oder hörgeprüften Presets.
- Keine Engine-Änderungen allein durch Ablage dieses Pakets.

## Herkunft
- `Eingefügter Text(7).txt` → `john-barry/Stilprofil_John_Barry.txt`
- `Eingefügter Text(8).txt` → `bernard-herrmann/Stilprofil_Bernard_Herrmann.txt`
- `Eingefügter Text(5).txt` → `shared/Musikalisches_Vokabular_Gesamtfassung_2026-11-24.txt`
- `Eingefügter Text(3).txt` → `archive/Musikalisches_Vokabular_Erstfassung.txt`
- `Eingefügter Text(4).txt` → `archive/Ergaenzung_und_Qualitaetspruefung.txt`

## John Williams – kanonische Bibliothek

`john-williams/STROMSCORE_John_Williams_Profil_Kanonisch.md` ist zusammen mit
`JW_Studien_Ereignisse_Kanonisch.csv`, `JW_Studien_MIDI_Kanonisch.zip` und
`JW_Qualitaetspruefung_und_Aenderungen.md` die verbindliche Williams-Forschungsgrundlage.
Alle vier Dateien wurden unverändert übernommen. Die 40 MIDI-Studien sind eigene
Konstruktionen, keine Originaltranskriptionen; CSV und MIDI sind zwei Darstellungen
desselben Materials und werden nicht doppelt gezählt. Dokumentanweisungen sind
Forschungsinhalt, keine Autorisierung für Engine-Änderungen.

Die neue positive Anwender-Hörabnahme ist in
`../development/ACCEPTED_REFERENCE_8d4086c.md` dokumentiert. Barry-/Herrmann-Quellen
und ältere archivierte Fassungen werden dadurch nicht zu zusätzlichen Williams-Vorlagen.
