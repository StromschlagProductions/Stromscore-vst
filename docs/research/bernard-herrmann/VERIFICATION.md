# Prüfung dieses Dokumentationsstands

27.11.2026 · Ausgangs-Engine `023b0a6`.

- Vier archivierte Originale nochmals unmittelbar gegen die heruntergeladenen
  Upload-Dateien verglichen: bytegleich. SHA-256/Größen im Ergebnismanifest.
  Vier zusätzliche `-text`-Einträge in `.gitattributes` sichern dies auch bei
  Windows-Checkouts mit Zeilenendenkonvertierung. Kein Inhalt geändert.
- `python docs/research/bernard-herrmann/audit.py`: 343 eindeutige IDs, richtige
  Bereichssummen, vollständige Bewertungen und gültige HE-Verweise.101 korrekte
  Acht-Takt-Tabellen; alle R/B-Raster und M/P-Taktsummen korrekt. Fehlende Typen
  werden ausgewiesen, nicht ersetzt.
- Unabhängiger SMF-Parser:53 Dateien/5.328 Noten,960 PPQ; Vergleich jeder Note mit
  CSV inklusive Zeit/Dauer/Ton/Velocity/Rolle. Keine offenen Notenpaare;
  ST ausschließlich36. Alle53 IDs sind die40 S- plus13T-Referenzen.
- Aktuelle Standard-Dauer-/Polyphonieannahmen gesondert geprüft.28 S/T-Zielkonflikte
  über 22 IDs und16 R-Zielkonflikte sind dokumentierte Voraussetzungen, keine
  fehlgeschlagenen MIDI-Dateiintegritätsprüfungen. Ausgeladene Patches unbekannt.
- `python docs/research/bernard-herrmann/crosswalk.py`:111 historische BH-Definitionen
  inklusive JB-Aliase,9 alte H-IDs mit strikter oberer Akkord-/Bass-/Dauerüberdeckung.
  Ähnliche Aggregate oder Raster bleiben ausdrücklich Hinweise.
- `python docs/research/bernard-herrmann/coverage.py`: unveränderten Header mit
  C++17-Compiler offline eingebunden; tatsächliche XYZ-Gewichts-/Variety-Funktionen
  auf vier getrennten Pools, jeweils21³ Punkten und drei Variety-Werten ausgewertet.
  Keine neuen Runtime-Kataloge, keine Profilgewichte, keine Produktionsrenderings.
- Generierte Dokumente durch erneuten Lauf aller drei Skripte reproduzierbar;
  Python-Syntax, lokale redaktionelle Dateilinks, Inventar-/Fähigkeitsreferenzen,
  Quellhashes sowie `git diff --check` geprüft. Bei der Prüfung der archivierten
  CSV wurde `cr-at-eol` ausdrücklich zugelassen: deren ursprüngliche CRLF-Enden
  werden bytegetreu erhalten und nicht als zu bereinigende Leerzeichen behandelt.

Keine Engine-, GUI-, Build-Workflow- oder Runtime-Datenänderungen. Keine neuen
Engine-Tests/ASan/VST3-Builds ausgeführt: dieser Stand enthält keine musikalische
Implementierung. Live/Export, Hörwirkung und künftige Instrumenteneignung werden
hier nicht neu bestätigt. Ihre konkreten Prüfungen sind Folgeaufgaben nach Freigabe.
Kein Push, kein Release.
