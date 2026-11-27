# Bernard Herrmann – Forschungsbibliothek

Stand: 27.11.2026. Technischer Abgleich: `023b0a6`, Williams P2/P3 einschließlich
Build-Pfadkorrektur. Deren musikalische Hörabnahme steht weiterhin aus.

Maßgebliche **kanonische Vorlagenbibliothek** ist dieses zusammengehörige Paket:

- [STROMSCORE_Bernard_Herrmann_Vokabular_Kanonisch.md](STROMSCORE_Bernard_Herrmann_Vokabular_Kanonisch.md)
- [HE_Studien_Ereignisse.csv](HE_Studien_Ereignisse.csv)
- [HE_Studien_MIDI.zip](HE_Studien_MIDI.zip)
- [HE_Qualitaetspruefung.md](HE_Qualitaetspruefung.md)

Alle vier Uploads sind bytegleich unter ihren Originalnamen ohne Upload-Suffix
archiviert. Dateigrößen und SHA-256 stehen in
[VALIDATION_RESULTS.json](VALIDATION_RESULTS.json), Feld `archived_files`.
CSV und MIDI sind zwei Darstellungen derselben Studien, keine zusätzlichen Vorlagen.
101 H + 66 R + 45 B + 57 M + 21 P + 40 S + 13 T = **343 eindeutige HE-IDs**;
53 MIDI-Dateien enthalten **5.328 Noten** bei **960 PPQ**.

[Spannungsgrammatik_Tiefenrecherche.md](Spannungsgrammatik_Tiefenrecherche.md)
bleibt die separate wissenschaftliche Grundlage. Das alte
[Stilprofil](Stilprofil_Bernard_Herrmann.txt) und BH-Material in der historischen
[Gesamtfassung](../shared/Musikalisches_Vokabular_Gesamtfassung_2026-11-24.txt)
bleiben nachvollziehbar erhalten, werden aber nicht zusätzlich importiert.
[BH-/HE-Abgleich](BH_HE_CROSSWALK.md) dokumentiert Überdeckungen und Unterschiede.
Die kanonischen Vorlagen haben für einen späteren HE-Import Vorrang.

Die Evidenzzeichen der Forschung sind Quellenangaben ihrer Autoren. Konstruierte
Vorlagen sind keine Filmtranskriptionen. Dokumentrezepte, Vereinfachungen und
Generatorvorschläge erteilen keine Implementierungsfreigabe. Insbesondere keine
Komponente entfernen, Zyklen zurücksetzen oder beabsichtigte Dissonanzen korrigieren.

## Technische Arbeitsunterlagen

- [Implementierungsplan und kritischer Abgleich](IMPLEMENTATION_PLAN.md)
- [343 Einzelbewertungen, lesbar](TECHNICAL_INVENTORY.md)
- [343 Einzelbewertungen, vollständige Daten](TECHNICAL_INVENTORY.json)
- [Gemeinsame Fähigkeiten Williams/Herrmann/SYNTH](../SHARED_MUSICAL_CAPABILITIES.md)
- [XYZ-Diagnose](XYZ_COVERAGE.json)

Reproduktion ausschließlich offline, im Repository:

```sh
python docs/research/bernard-herrmann/audit.py
python docs/research/bernard-herrmann/crosswalk.py
python docs/research/bernard-herrmann/coverage.py
```

`assessment.json` enthält die fachlich redigierten Einstufungen und Fähigkeiten.
`audit.py` ergänzt die tatsächlichen Quellfiguren, Akkorde, Zeitwerte, Referenzen,
MIDI-Prüfung und aktuellen Ausgabegrenzen. `coverage.py` benötigt einen C++17-
Compiler und ruft die unveränderten Engine-Funktionen für XYZ-Gewicht und Variety
auf; temporäre Programme liegen außerhalb des Repositorys. Keine dieser Dateien
ist Teil von CMake, Plugin, Runtime-Datengenerierung oder Audiothread.
