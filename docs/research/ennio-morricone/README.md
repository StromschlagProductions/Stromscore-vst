# Ennio Morricone – Forschungsarchiv und kanonische Vorlagenbibliothek

Stand 27.11.2026; technischer Abgleich gegen **4c43bd2** auf
`develop/composition-core-prototype`. Nur Dokumentation, keine Aktivierung.
Die laufende Pedal-Hörabnahme und die akzeptierte Williams-P2/P3-Referenz bleiben
unverändert. Kein Push, kein Release.

## Verbindliche Quelldateien

- `STROMSCORE_Ennio_Morricone_Vokabular_Kanonisch.md`
- `EM_Studien_Ereignisse.csv`
- `EM_Studien_MIDI.zip`
- `EM_Qualitaetspruefung.md`

Das ist die maßgebliche Vorlagenbibliothek: **534 eindeutige IDs**, 73 MIDI-Studien,
9752 Noten bei 960 PPQ. Definitionen/Studien derselben EF-ID zählen einmal; T-IDs
stehen in einer Tabelle. CSV und MIDI sind zwei Darstellungen derselben Studien,
keine zusätzlichen musikalischen Vorlagen. Studien sind eigene Konstruktionen,
keine Filmthemen oder Transkriptionen; es gibt keine musikalische Hörprüfung der
Bibliothek. Die beiliegende Qualitätsprüfung ist eine Quelle, kein ungeprüft
übernommenes Zertifikat für den Kompositionskern.

## Wissenschaftliche Grundlagen – separat, unverändert

- `STROMSCORE_Ennio_Morricone_Tiefenrecherche.md`: Upload „Ennio Morricone Stilprofil
  für STROMSCORE_ Mikrozelle, immobilità dinamica und partitura multipla.md“.
- `STROMSCORE_Ennio_Morricone_Nachtrag_Lolita_Lyrik.md`: einmalige kanonische Ablage
  des Lolita-Nachtrags, keine zweite Kopie unter früherem Namen.
- `STROMSCORE_Ennio_Morricone_Tiefenrecherche_Vertiefung.md`: Upload „Ennio Morricone
  für STROMSCORE_ Mikrozellen, Partitura multipla und rhythmische Schichtung.md“.

[ARCHIVE_MANIFEST.json](ARCHIVE_MANIFEST.json) dokumentiert Originalnamen, Dateigrößen
und SHA-256. Alle sieben Inhalte sind bytegleich. Originale werden nicht still
berichtigt; vorhandene Irrtümer, Überholungen und N/I/H/E-Einstufungen bleiben
als Forschungsprovenienz erhalten. Aussagen über bereits bestehende Fähigkeiten
werden anhand des Codes überprüft. Empfehlungen im Quelltext sind keine
Autorisierung für zusätzliche Entwicklungsschritte oder Instrumentierungszwänge.

Lolita/Love in the Morning und The Untouchables sind persönliche Prioritäten des
Anwenders. Ein späteres **gemeinsames Morricone-Profil**, keine Trennung von Lyrik
und Experiment; keine obligatorische Melodie, Arpeggio-, Puls-, Pedal- oder
Ankerschicht. Neun bestehende Ziele, keine neue GUI. Die Referenzkanäle GS7/HM8/ST10
werden bei einem späteren Import rollenbezogen zugeordnet, **nicht** zur neuen
STROMSCORE-Standardbelegung. ST bleibt Trigger36.

## Unsere Analyse – getrennt von den Originalen

- [Implementierungsplan](IMPLEMENTATION_PLAN.md): Fähigkeiten, gemeinsame Prioritäten,
  frühester begrenzter Übergangsgrammatik-Schritt und konkrete Testkriterien.
- [Prüfprotokoll](VERIFICATION.md): Umfang und Grenzen der durchgeführten Checks.
- [Fehler/Klärungen](ERRATA.md): alle angefragten H-Fälle, neue R-Metadatenbefunde,
  Zellidentität, Normalformkonvention, Gate-/Instrumenten- und Evidenzgrenzen.
- [Vollständiges lesbares Inventar](TECHNICAL_INVENTORY.md).
- [Vollständiges maschinenlesbares Inventar](TECHNICAL_INVENTORY.json): alle534IDs
  mit individuellen Quellenfakten, Begründungen, Codebezügen und Abhängigkeiten.
- `SOURCE_RECORDS.json`: vollständige extrahierte Felder, Ton-/Zeitdaten und
  Mehrschichten; **kein** Laufzeitimportformat.
- `VALIDATION_RESULTS.json`, `AUDIT_SUMMARY.json`: formale Prüfungen und Zählungen.
- `TRANSITION_AUDIT.json`, `ENGINE_PROBE_RESULTS.json`: alle50U, Pflicht-/Optionaltöne,
  Stimmenzuordnung und unveränderter Core-Probe in zwölf Transpositionen.
- `CELL_IDENTITY_AUDIT.json`, `INSTRUMENT_CONSTRAINTS.json`: tatsächliche Studiennoten
  und abweichende Generatorannahmen.
- `XYZ_COMPATIBILITY.json`, `PAIR_COMPATIBILITY.jsonl`: dichtes Raster, unveränderter
  Ankerfilter und ganze formale H/B/C/M-Horizonte. Kein Versprechen eines fertigen
  oder ästhetisch überzeugenden Profils.
- `MODULE_COMPATIBILITY.json`, `MODULE_TRIPLES.jsonl`: alle8436Dreierkombinationen
  als vorläufige notwendige Prüfungen; keine pauschale Mehrfachfreigabe.

Reproduktion: nacheinander `python3 audit.py`, `python3 assess.py`,
`python3 compatibility.py`, danach `python3 verify.py` in diesem Ordner (oder über deren Repositorypfade).
Die Skripte verändern ausschließlich unsere abgeleiteten Dokumente; der C++-Probe
wird temporär gebaut. Keine Engine-/GUI-/Katalogdatei und kein Original werden verändert.

## Implementierungsfortschritt

[P1 – gemeinsame Übergangsgrammatik und hörbarer Prototyp](P1.md) dokumentiert
den nachfolgenden Implementierungsschritt. Die obige Bestandsaufnahme bleibt
eine historische Prüfung gegen `4c43bd2`; ihre Einstufungen werden nicht
rückwirkend als damalige Engine-Fähigkeiten umgeschrieben.
