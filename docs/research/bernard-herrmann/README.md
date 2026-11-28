Zweite Hörabnahme und aktuelles Korrekturpaket: [AR und Ruhebereich](P1_AR_QUIET_CORRECTION.md), [bestätigte Referenz2170807](../../development/ACCEPTED_REFERENCE_2170807.md).

Vorheriges Korrekturpaket: [Rollenaktivität, Ursachen und MIDI-A/B](P1_ACTIVITY_CORRECTION.md).

> Musikalische Rückmeldung zu0874b02: Die Herrmann-Handschrift ist positiv gehört; eine erhebliche Bassaktivitätsregression wurde gemeldet. [Geltungsbereich](../../development/ACCEPTED_REFERENCE_0874b02.md).

# Aktueller Stand: Herrmann P1

Implementierung und Grenzen: [P1.md](P1.md), [IDs](P1_IMPLEMENTED_IDS.json), [Hörtest](P1_STUDIO_ONE.md). Carpenter P1 wurde inzwischen vorläufig positiv gehört; Einschränkungen siehe [Abnahme](../../development/ACCEPTED_REFERENCE_58ea29d.md). Die folgenden Bestandsaufnahmen bleiben historische Referenzen.

# Bernard Herrmann – Forschungsbibliothek

Stand: 28.11.2026. Aktueller Planungsabgleich: `58ea29d` einschließlich Carpenter P1.
Williams P2/P3 und Morricone P1 sind positiv gehört; Carpenter P1 wartet noch auf
die musikalische Abnahme. Die ursprüngliche343-ID-Erfassung bleibt als historischer
Befund zu `023b0a6` erhalten.

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

- [Aktualisierter Implementierungsplan](IMPLEMENTATION_PLAN.md)
- [Kompakter Ergebnisbericht zu58ea29d](PLANNING_UPDATE_58ea29d.md)
- [Fortschreibung aller343 IDs zu58ea29d](CAPABILITY_REVIEW_58ea29d.json)
- [Historische343 Einzelbewertungen, lesbar](TECHNICAL_INVENTORY.md)
- [Historische343 Einzelbewertungen, vollständige Daten](TECHNICAL_INVENTORY.json)
- [Gemeinsame Fähigkeiten Williams/Herrmann/SYNTH](../SHARED_MUSICAL_CAPABILITIES.md)
- [XYZ-Diagnose](XYZ_COVERAGE.json)

Historische Erfassungs-/Prüfwerkzeuge, ausschließlich offline im Repository
(nicht zur Erzeugung der redaktionellen58ea29d-Fortschreibung):

```sh
python docs/research/bernard-herrmann/audit.py
python docs/research/bernard-herrmann/crosswalk.py
python docs/research/bernard-herrmann/coverage.py
```

`assessment.json` enthält die fachlich redigierten Einstufungen und Fähigkeiten.
`audit.py` ergänzt die tatsächlichen Quellfiguren, Akkorde, Zeitwerte, Referenzen,
MIDI-Prüfung und den damals redigierten Ausgabegrenzen. Für die heutigen kontextabhängigen
Fähigkeiten ist zusätzlich der aktuelle Quellcodeabgleich maßgeblich. `coverage.py` benötigt einen C++17-
Compiler und ruft die unveränderten Engine-Funktionen für XYZ-Gewicht und Variety
auf; temporäre Programme liegen außerhalb des Repositorys. Keine dieser Dateien
ist Teil von CMake, Plugin, Runtime-Datengenerierung oder Audiothread.
