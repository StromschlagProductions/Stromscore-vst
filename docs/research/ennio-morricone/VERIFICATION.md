# Prüfprotokoll – Morricone-Archiv und Bestandsaufnahme

27.11.2026, Entwicklungsbranch `develop/composition-core-prototype`.
Produktionsreferenz: `4c43bd2`. Ausschließlich Offline-Analyse.

## Durchgeführte Prüfungen

- Sieben Originaldateien gegen SHA-256 und Bytezahl geprüft; Lolita-Nachtrag
  genau einmal archiviert. ZIP-Integrität ohne Fehler.
- 534 eindeutige IDs vollständig extrahiert und einzeln in beiden Inventaren
  erfasst, einschließlich zusammengeführter EF-Fundstellen und T-Tabelle.
- Alle 73 MIDI-Studien mit 9752 Noten gegen CSV verglichen: Rolle, Einsatz,
  Dauer, Tonhöhe und Velocity stimmen überein. Auflösung 960 PPQ; Notenbilanz
  ausgeglichen; keine Überlagerung derselben physischen Kanal-/Tonhöhe.
  Alle 280 Stich-Noten verwenden Trigger 36.
- Zellmengen, Intervallvektoren, Primform-Äquivalenz, symbolische Rhythmen,
  Motivlängen einschließlich Pausen sowie vollständige Perioden geprüft.
  Widersprüche stehen separat in `ERRATA.md`, nicht in korrigierten Originalen.
- 50 U-Vorlagen mit 59 Übergängen strukturell untersucht. Den unveränderten
  C++-Stimmführungs-Solver in zwölf Transpositionen aufgerufen: 708 Fälle,
  Ziel-Tonklassen erhalten; zwei Pflichttonverluste bei U040 dokumentiert.
  Dies ist ein Solver-Test, kein vollständiger Produktionsrender.
- 1331 XYZ-Punkte mit drei Variety-Einstellungen, 16280 formale Materialpaare
  und 8436 Modul-Dreierkombinationen untersucht. Die Vorfilter liefern keine
  automatische musikalische oder instrumentale Freigabe.
- Produktionsquellen einschließlich GUI bytegleich mit `4c43bd2` geprüft.
  Keine neue Vorlage aktiviert, keine Änderung des laufenden Pedalstands.

Die vollständige Analyse wurde zweimal ausgeführt; sämtliche abgeleiteten
JSON-/JSONL-Dateien waren bytegleich. Die sieben Originale wurden zusätzlich
als tatsächlich vorgemerkte Git-Blobs gegen das Manifest geprüft. Der
Whitespace-Check berücksichtigt die unverändert archivierten CRLF-Zeilen der CSV.

## Reproduktion

Im Repository nacheinander ausführen:

```sh
python3 docs/research/ennio-morricone/audit.py
python3 docs/research/ennio-morricone/assess.py
python3 docs/research/ennio-morricone/compatibility.py
python3 docs/research/ennio-morricone/verify.py
```

Der C++-Probe wird temporär kompiliert. Die Analyse benötigt keine externe
Python-Bibliothek und schreibt ausschließlich abgeleitete Forschungsdateien.
Es wurden keine DSP-Gesamttests, kein neuer Plugin-Build und keine musikalische
Hörabnahme vorgenommen: Engine und GUI sind unverändert. Die festgestellten
Quellenwidersprüche bleiben offene Entscheidungen und werden nicht durch einen
bestandenen Archiv-/Analysecheck als behoben ausgegeben.
