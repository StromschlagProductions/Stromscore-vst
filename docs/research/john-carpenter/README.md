# John Carpenter – wissenschaftliche Forschungsgrundlage

Archiviert am 27.11.2026 auf `develop/composition-core-prototype`, Ausgangspunkt
`38d2238`. Beide Berichte wurden vollständig gelesen und bytegleich übernommen:

1. [STROMSCORE_John_Carpenter_Tiefenrecherche.md](STROMSCORE_John_Carpenter_Tiefenrecherche.md)
2. [STROMSCORE_John_Carpenter_Tiefenrecherche_Vertiefung.md](STROMSCORE_John_Carpenter_Tiefenrecherche_Vertiefung.md)

Der erste Upload hieß `STROMSCORE_ Musikwissenschaftliche Tiefenrecherche zu John Carpenter.md`;
lediglich der Dateiname wurde wie beauftragt vereinheitlicht. Originalnamen,
Dateigrößen und SHA-256 stehen im [Archivmanifest](ARCHIVE_MANIFEST.json).
Die Dateien werden durch `-text` in `.gitattributes` vor einer automatischen
Zeilenendenkonvertierung geschützt.

**Bei Widersprüchen gilt die korrigierte Vertiefung.** Die erste Recherche bleibt
zur Nachvollziehbarkeit unverändert erhalten. Die beiden Texte sind ergänzende
Forschung, keine zwei additiv zu importierenden Vokabularsammlungen. Die kanonische
Carpenter-Vorlagenbibliothek stand in dieser ersten Phase noch aus. Damals wurden keine Vorlagen-IDs vergeben,
keine Einzelfiguren zur Implementierung ausgewählt und keine Profilgewichte festgelegt.

## Maßgebliche Korrekturen

| Frühe Verengung / Vorschlag | Für den weiteren Abgleich maßgeblich |
|---|---|
| Zelle höchstens zwei bis vier Töne, niemals intervallisch ändern | Kurze Sequencer-Zellen sind eine Präferenz; längere Figuren, einzelne veränderte Töne und lyrische Linien bleiben möglich (Vertiefung §§5/8). |
| Leere Quinten und Reibung als gesamte Harmonik | Auch Mollakkordfolgen, diatonische Zirkulation, schreitende Akkorde und Umfärbung einer unveränderten Figur berücksichtigen (§§3/4). Kein Septakkordverbot aus fehlendem Beleg ableiten. |
| Puls und Arpeggio als obligatorische Identität | Pulslose Felder, lange Einzelklänge, gehaltene Akkorde und Stille sind eigenständige Möglichkeiten (§6). Keine Pflicht auf LB/AR/ST oder eine bestimmte Besetzung. |
| Tritonus als belegtes Halloween-Kernintervall | C♯–F♯ und C–F sind reine Quarten, jeweils fünf Halbtöne; die Vertiefung korrigiert den übernommenen Analysefehler (§2). |
| The-Thing-Herzschlag als Carpenter-Beleg | Morricones Thema von den Carpenter/Howarth-Zusatzcues trennen. Letztere begründen vor allem Drones/Stinger, keine Vereinnahmung des Bassmotivs (§§0/3.5). |
| Fester 8/16/32/64-Takt-Atemzyklus und höchstens eine Änderung | Acht alternative Entwicklungsstrategien, einschließlich unveränderter Stasis und gekoppeltem Schichttausch (§7.2). Keine obligatorische Steigerung/Reduktion. |
| Stinger stets abseits des Pulses, Cluster auf ST | Asynchronität nur Präferenz. ST bleibt fester, nicht transponierter Trigger; tonale Mehrklänge benötigen geeignete TU/KF-Ziele (§§8/9). |
| CC74, neue Rhythmusspur oder zusätzliche Ausgänge als nächster Ausbau | Nicht beschlossen. Instrumentierung, Effektproduktion und Kompositionsfähigkeit getrennt halten (§9 und aktueller Anwenderauftrag). |

Die acht Strategien **S1–S8** sind lokale Bezeichnungen der Vertiefung (§7.2), keine
kanonischen Vorlagen-IDs und keine bereits implementierten Engine-Modi. Ihre
Einzelbewertung und der gemeinsame Fahrplan stehen im
[gemeinsamen Fähigkeitsbericht](../SHARED_MUSICAL_CAPABILITIES.md#carpenter-acht-entwicklungsstrategien).
Williams/Herrmann verwenden weiterhin denselben Kern; es wird keine separate
SYNTH-Kompositionsengine geplant.

## Evidenz und offene Fragen

N/I/H/E und V/S/W/O/U sind Kennzeichnungen der Autoren, keine hier erneut
bestätigten externen Belege. Die Vertiefung legt ausdrücklich offen: keine eigene
Audioanalyse, teilweise zusammengefasste Volltextauswertung, Donnelly/Burnand/Mera
nicht im Primärtext verfügbar, mehrere Detailbeschreibungen aus Rezensionen oder
Crowd-Analysen. Die Quelllinks wurden in diesem Auftrag nicht extern neu geprüft.

Unabhängige Perioden und Phasenverschiebung sind als Carpenter-Merkmal weiterhin
unbelegt. Gemeinsame Uhr, Triolen, ungerade Taktart und unabhängige Periode sind
verschiedene Sachverhalte. Der Vorschlag der Vertiefung, aus Triolen/5/4 bereits
eine schwache Periodenpräferenz abzuleiten (§5.2), wird nicht als gesicherte
Stilregel übernommen. Exakte Harmonien, Zeitverläufe, Transpositionsfolgen und
Vorlagenfähigkeit werden erst mit der kanonischen Bibliothek geprüft.

Eine automatische Erkennung laufender Hörspieldialoge ist nicht vorhanden.
Die Registerempfehlung der Recherche autorisiert weder einen Dialogdetektor noch
eine neue pauschale Mittellagensperre. Hörtests mit Sprache bleiben erforderlich.
Ebenso ist stufenloses Ausblenden eines gehaltenen externen Instruments nicht durch
Änderung der Anschlagsvelocity realisierbar. Keine neuen CC-/Klangsteuerungen aus
der Strategie „Atmung“ ableiten.

## Prüfung dieses Archivierungsstands

Bytevergleich mit beiden Uploads und SHA-256-Prüfung auch der Git-Blobs;
Dateilinks und alle acht Strategiezeilen kontrolliert. Quellcodeabgleich u.a. mit
`CompositionCore.h`, `CompositionPolicy.h`, `AuthoredMotifSource.h`, `RoleRhythm.h`,
`ArpeggioPhrase.h`, `MusicalExecution.h` und den jeweiligen Verbrauchern in
`ScoreEngine.h`. Engine, Laufzeitdaten, GUI und Build-Workflow bleiben unverändert.
Keine neuen Renderings, Klangbeispiele, Sanitizer- oder Plugin-Builds: dieser Auftrag
enthält ausschließlich Archivierung, Analyse und Dokumentation. Keine Aussage
über die musikalische Hörabnahme von Williams P2/P3 oder eines Carpenter-Profils.

## Kanonische Vorlagenbibliothek – Fortschreibung nach `4937722`

Die oben beschriebene erste Archivierungsphase bleibt historisch nachvollziehbar.
Inzwischen ist die separate kanonische Bibliothek vollständig und bytegleich
unter ihren Originalnamen archiviert:

- [STROMSCORE_John_Carpenter_Vokabular_Kanonisch.md](STROMSCORE_John_Carpenter_Vokabular_Kanonisch.md)
- [JC_Studien_Ereignisse.csv](JC_Studien_Ereignisse.csv)
- [JC_Studien_MIDI.zip](JC_Studien_MIDI.zip)
- [JC_Qualitaetspruefung.md](JC_Qualitaetspruefung.md)

[CANONICAL_MANIFEST.json](CANONICAL_MANIFEST.json) dokumentiert Bytes/SHA-256.
Die ursprünglichen zwei Tiefenrecherchen bleiben unverändert und separat; bei
Widersprüchen zwischen ihnen hat weiterhin die Vertiefung Vorrang. Konkrete
kanonische Vorlagen sind 405eindeutige JC-IDs, keine zusätzlichen Importkopien der
Recherche-Beispiele. CSV und MIDI sind dieselben54 Studien in zwei Darstellungen.
Anwenderentscheidungen (u.a. Registerpräferenz, keine obligatorischen Rollen,
keine automatische Follow-Umschaltung) haben Vorrang vor Dokumentrezepten.

### Vollständiger Abgleich

- [Technische Einzelbewertungen, lesbar](TECHNICAL_INVENTORY.md)
- [Alle405 Datensätze, maschinenlesbar](TECHNICAL_INVENTORY.json)
- [Fehlerliste und offene Entscheidungen](ERRATA.md)
- [Gemeinsame Zyklen aller Q/B und Perioden aller R](CYCLE_ANALYSIS.json)
- [MIDI-/CSV-/Funktions-/Registerprüfung](VALIDATION_RESULTS.json)
- [XYZ-Kompatibilität und Vergleich zur bestehenden Auswahl](XYZ_COMPATIBILITY.json)
- [Alle20.328 Paarprüfungen mit Gegenbeispielen](PAIR_COMPATIBILITY.jsonl)
- [Kleine Implementierungsschritte und Ergebnisgrenzen](IMPLEMENTATION_PLAN.md)

D: 21 / A: 87 / E: 288 / K: 9 sind technische Grundform-/Anbindungsurteile, keine Import- oder
Hörfreigabe. Referenzstudien sind keine aktuellen Engine-Renderings. Insbesondere
S35-Rotation, Gate-Listen und lokale T-Kontexte bleiben offen. Die ursprüngliche
Aussage „kanonische Bibliothek steht aus“ im historischen Abschnitt oben ist damit
überholt; die Grundsätze zu Evidenz, Instrumentierung und noch offenen CC-/Routing-
Fragen bleiben bestehen.

Reproduzierbar aus dem Repository, ausschließlich offline:

```sh
python docs/research/john-carpenter/audit.py
python docs/research/john-carpenter/compatibility.py
```

`assessment.json` enthält fachlich redigierte Urteile; `audit.py` ergänzt konkrete
Quellwerte und einen unabhängigen SMF-Parser. `compatibility.py` prüft Paare und
bindet für die reine XYZ-Gewichtsdiagnose den unveränderten Engine-Header mit einem
C++17-Compiler (`c++`) ein. Temporäre Programme verbleiben außerhalb des Repositorys.
Keine Datei ist in Plugin, CMake oder Runtime-Datengenerierung eingebunden.
Archivebytes/Git-Blobs, SHA-256, vollständige IDs, alle acht Strategiezuordnungen,
Dateilinks, reproduzierbare Ausgaben und Dokumentationsumfang wurden geprüft.
Kein neuer Engine-/VST3-/Sanitizerlauf für reine Dokumentation; keine Aktivierung,
kein Push, kein Release.

## Carpenter P1 – Fortschreibung

Die erste begrenzte Profilimplementierung nutzt den gemeinsamen Kern und ist
im bestehenden SCORE-Komponistenmenü wählbar. Kanonische Originale bleiben
unverändert; alte technische Klassifikationen sind historische Bestandsaufnahmen.
Aktueller Umfang und Grenzen: [P1.md](P1.md), vollständige ID-Zuordnung
[P1_IMPLEMENTED_IDS.json](P1_IMPLEMENTED_IDS.json),
[Studio-One-Hörtest](P1_STUDIO_ONE.md) und
[MIDI-Hörstudien](P1_MIDI_LISTENING.zip). Noch keine Anwender-Hörabnahme von P1.
