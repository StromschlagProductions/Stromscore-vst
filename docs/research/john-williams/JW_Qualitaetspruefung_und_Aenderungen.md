# STROMSCORE – John Williams: Qualitätsprüfung und Änderungen

Stand: 26.11.2026 · bezieht sich auf `STROMSCORE_John_Williams_Profil_Kanonisch.md`, `JW_Studien_Ereignisse_Kanonisch.csv` und `JW_Studien_MIDI_Kanonisch.zip`.

## 1 Maschinelle Prüfungen

| Prüfung | Ergebnis |
|---|---|
| Eindeutige IDs | 276 IDs, keine Dubletten |
| Akkorddefinitionen | alle 526 Akkordsymbole in 76 Harmonievorlagen parsebar (inkl. Polychorde `X|Y`, Tonklassenmengen `{…}`); Tonklassen maschinell abgeleitet |
| Taktdauern Harmonik | jede Vorlage summiert auf 8 Takte |
| Tonvorratszugehörigkeit | jeder Akkord gegen seinen angegebenen Vorrat geprüft (Pantriadisch/Chromatisch ausgenommen); keine Abweichung. Studien: Fläche, Bass, Arpeggio, Tupfer gegen den Vorrat der Studie; bewusst freie Rollen sind als `syst_frei` markiert (JW-S19, JW-S30: Dissonanzbass) |
| Rhythmusraster | 48 Rhythmus- und 40 Bassvorlagen: Länge = Takte × Schritte, zulässige Zeichen, kein Haltezeichen nach Pause |
| Motive und Phrasen | 48 Motive, 24 Phrasen: alle Taktsummen korrekt; Intervalle im Dokument werden aus den Tönen berechnet, nicht von Hand eingetragen |
| Intervall- und Konturangaben (Textbeschreibungen) | alle 48 Motive und 24 Phrasen manuell gegen die berechneten Intervalle geprüft: 5 Fehler gefunden und korrigiert (Abschnitt 2) |
| Transpositionsgleiche Harmonievorlagen | keine (Vergleich relativ zum ersten Grundton, mit Bass und Dauern); keine identischen Klangmengen |
| MIDI | 40 Dateien, PPQ {960}, je Rolle eine Spur |
| Note-on/Note-off | 0 Fehler (keine offenen, doppelten oder überlappenden gleichen Töne in einer Spur) |
| MIDI-Notenbereich | 0 Noten außerhalb MIDI 21–108 |
| CSV ↔ MIDI | CSV 7662 Noten, aus MIDI rekonstruiert 7662 Noten, identisch: ja |
| Dokumentation ↔ Daten | Akkordtabellen, Raster, Tonklassen, Rollenverläufe und Notenzahlen im Dokument werden aus denselben Daten erzeugt wie MIDI und CSV; alle Querverweise (JW-…) im Dokument existieren. Dynamik-Angaben im Text sind jetzt in den MIDI-Daten umgesetzt (vorher nicht, siehe 2) |
| Haltetöne über Akkordwechsel | 0 Konflikte nach Korrektur (vorher 3 in JW-S01) |
| XYZ-Anker | alle Werte 0–1; Matrix im Hauptdokument (J) aus den Ankern berechnet |

## 2 Gefundene Fehler und durchgeführte Korrekturen

| ID | Befund | Art | Korrektur |
|---|---|---|---|
| JW-M24 | „Ganzton auf, Tritonus ab“, aber D3 → F♯2 ist eine kleine Sexte abwärts | Intervallfehler | F♯2 → A♭2 (Tritonus) |
| JW-M30 | „Halbton und kleine Terz im Wechsel“, aber B4 → G4 ist eine große Terz | Intervallfehler | Tonfolge C–B–A♭–G–E–E♭ (alle Hex-C) |
| JW-S09 | Gegenstimme übernahm die fehlerhafte Folge aus JW-M30 | Folgefehler | korrigiert, MIDI neu |
| JW-M20 | als „große Sexte“ beschrieben, E4 → C5 ist eine kleine Sexte | Textfehler | Kontur und Invariante korrigiert |
| JW-T06 | „die Sexte wird zur kleinen Sexte“ – tatsächlich wird aus E–C (klein) E♭–C (groß) | Textfehler | Beschreibung umgekehrt |
| JW-P10 | „Gipfel Takt 3“, G5 erscheint bereits in Takt 2 | Textfehler | Beschreibung korrigiert |
| JW-H37 | Name „Diatonische …“, E7 enthält G♯ | Bezeichnung | umbenannt in „Quintfallsequenz mit Septimen und Zwischendominante“ |
| JW-H43 | Variante „B7“ enthält A, nicht in Ungarisch-Moll | Variantenfehler | Variante B/D♯ (im Vorrat) |
| JW-H13, H15, H35, H50 | Varianten verlassen den Tonvorrat (B♭, G♯, A♭m, F♯) | fehlende Kennzeichnung | bewusst zulässig, jetzt als [systemfremd] markiert |
| JW-H35 | Evidenz [H]; der zweite Durchgang bestätigt Murphys I–iii („Loss Gesture“) | Evidenz | auf [I] angehoben, Text präzisiert |
| JW-S01 | Lange Fläche hielt D♭/C aus Takt 7 über Cm in Takt 8 (D♭, F, A♭ gegen Cm) | unbeabsichtigte Dissonanz | Neuanschlag pro Takt |
| JW-S02, S05, S07, S08, S12, S14, S15 | Dynamikverlauf im Text beschrieben, aber nicht in den Noten | Doku ≠ Daten | Dynamik je Takt in die Daten übernommen, MIDI neu |
| JW-H48, JW-S16, B.4 | „höchstens 4 Takte“ / „nach 4 Takten auflösen“ | Einschränkung | gestrichen; Zuspitzung darf bestehen bleiben |
| JW-S13, A.5 | „deshalb schweigt das Arpeggio“ | Einschränkung | als Möglichkeit formuliert |

**Geprüft und unverändert gelassen (bewusste Dissonanzen):** Pedale unter wechselnden Klängen (z. B. JW-S03, JW-T03), Dissonanzbässe (JW-H17, H46, H58, JW-S04, S19, S30), Nebentöne auf Zählzeiten in Phrasen (Vorhalte, Durchgänge, oktatonische Skalentöne über statischem Klang in JW-P06, JW-S12). Die Gegenstimme in JW-S12 hat nur 2 von 14 Akkordtönen auf Zählzeiten – das ist das Verfahren „oktatonische Melodie über wiederholtem Akkord“; alle Töne gehören zum Vorrat Okt-A.

## 3 Zurückgenommene oder umgeschriebene Regeln

| Vorfassung | jetzt |
|---|---|
| I-1.2 Vorlagen-Rotation (keine Vorlage zweimal hintereinander) | I-1.2 Wiederholung erlaubt, nur leicht geringeres Gewicht |
| I-2.3 Oktatonik-Deckel 40 % | I-2.3 Oktatonik als Farbe neben anderen, ohne Obergrenze |
| I-5.3 Taktwechsel als Verfahren | I-5.3 Taktart-Vorlagen nur bei passender Host-Taktart, keine Änderung der Host-Taktart |
| I-7.2 Höchstzahl gleichzeitiger Rollen | I-7.2 Lagentrennung statt Höchstzahl |
| I-9.2 Spitze höchstens 4 Takte | I-9.2 Zuspitzung bleibt, solange gewählt |
| A.5 „dann schweigt das Arpeggio“ | Arpeggio wird entlastet, kann aber weiterlaufen |
| J.2 40-%-Aussage zur Oktatonik | Vielfalt im Bestand statt Quote |
| Neu | I.0 Tabelle zur unabhängigen Wirkung von X, Y, Z mit Belegen und Demonstrationsstudien JW-S29/S30 |

## 4 Zusätzliche Vorlagen

- **Harmonische Wendungen (19):** DIS: JW-H67, JW-H68, JW-H69; DIU: JW-H70, JW-H76; DRU: JW-H71, JW-H72, JW-H73, JW-H74; HIU: JW-H62, JW-H63, JW-H64, JW-H65, JW-H66; HRU: JW-H58, JW-H59, JW-H60, JW-H61, JW-H75
- **Rhythmusvorlagen (12):** DIS: JW-R43, JW-R46; DRU: JW-R45, JW-R47; HIU: JW-R37, JW-R38, JW-R44, JW-R48; HRU: JW-R39, JW-R40, JW-R41, JW-R42
- **Bassvorlagen (10):** DIS: JW-B34, JW-B35; DRU: JW-B33, JW-B37, JW-B40; HIU: JW-B32, JW-B36, JW-B39; HRU: JW-B31, JW-B38
- **Motive (14):** DIS: JW-M43, JW-M44; DIU: JW-M45; DRU: JW-M42, JW-M46, JW-M47, JW-M48; HIU: JW-M40, JW-M41; HRU: JW-M35, JW-M36, JW-M37, JW-M38, JW-M39
- **Phrasen (6):** DIS: JW-P21, JW-P24; DRU: JW-P22; HIU: JW-P20; HRU: JW-P19, JW-P23
- **Modellstudien (14):** DIS: JW-S21, JW-S22, JW-S26; DRU: JW-S23, JW-S24, JW-S28, JW-S29; HIS: JW-S30; HIU: JW-S19, JW-S20, JW-S27; HRU: JW-S17, JW-S18, JW-S25
- **Übergangsstudien (2):** DRS: JW-T10; DRU: JW-T09

## 5 Prüfprotokoll der Studien

| Studie | Takte | Rollen | Noten | max. neu einsetzende Rollen/Takt | Melodierollen Akkordton/Systemton/systemfremd | korrigierte Überlappungen |
|---|---|---|---|---|---|---|
| JW-S01 | 8 | LF, LB, KB, TU, GS | 40 | 5 | GS 6/2/0 | 0 |
| JW-S02 | 8 | LF, KF, LB, ST, GS | 220 | 5 | GS 8/0/0 | 0 |
| JW-S03 | 8 | LF, LB, AR, TU, GS | 74 | 4 | GS 4/4/0 | 0 |
| JW-S04 | 8 | LF, LB, AR, TU, GS | 80 | 4 | GS 5/3/0 | 0 |
| JW-S05 | 8 | LF, LB, GS, HM | 64 | 4 | HM 17/1/0, GS 9/2/0 | 0 |
| JW-S06 | 8 | LF, LB, AR, TU, GS | 102 | 4 | GS 11/1/0 | 0 |
| JW-S07 | 8 | LF, KB, AR, GS, HM | 97 | 4 | HM 16/3/0, GS 6/0/0 | 0 |
| JW-S08 | 8 | LF, LB, AR, TU, HM | 117 | 4 | HM 19/0/1 | 0 |
| JW-S09 | 8 | LF, LB, AR, TU, GS | 120 | 5 | GS 6/6/0 | 0 |
| JW-S10 | 8 | KF, KB, ST, HM | 207 | 4 | HM 33/0/0 | 0 |
| JW-S11 | 8 | KF, KB, AR, ST, HM | 278 | 5 | HM 24/2/0 | 0 |
| JW-S12 | 8 | LF, KF, LB, AR, ST, GS | 300 | 5 | GS 9/15/0 | 0 |
| JW-S13 | 8 | KF, KB, ST, GS | 292 | 4 | GS 11/9/0 | 0 |
| JW-S14 | 8 | LF, KF, KB, AR, ST, HM | 167 | 6 | HM 19/0/0 | 0 |
| JW-S15 | 8 | LF, LB, AR, GS, HM | 70 | 5 | HM 13/1/0, GS 4/0/0 | 0 |
| JW-S16 | 8 | KF, KB, AR, ST, GS | 478 | 5 | GS 9/0/9 | 0 |
| JW-S17 | 8 | KF, KB, TU, GS | 155 | 4 | GS 38/0/0 | 0 |
| JW-S18 | 8 | LB, AR, TU, GS | 61 | 3 | GS 14/5/0 | 0 |
| JW-S19 | 8 | KF, KB, AR, ST, HM | 371 | 5 | HM 26/1/0 | 0 |
| JW-S20 | 8 | KF, LB, KB, AR, ST | 288 | 5 | — | 0 |
| JW-S21 | 8 | LF, KF, LB, ST, GS | 88 | 5 | GS 12/0/0 | 0 |
| JW-S22 | 8 | LF, KF, LB, AR, ST, GS | 170 | 6 | GS 14/0/0 | 0 |
| JW-S23 | 8 | LF, LB, TU, GS | 58 | 3 | GS 6/4/0 | 0 |
| JW-S24 | 8 | LB, AR, GS | 58 | 3 | GS 22/0/0 | 0 |
| JW-S25 | 32 | KF, LB, KB, AR, TU, GS, HM | 368 | 3 | HM 24/0/0, GS 26/4/0 | 0 |
| JW-S26 | 16 | LF, KF, LB, ST, GS | 165 | 5 | GS 12/0/0 | 0 |
| JW-S27 | 16 | KF, KB, AR, ST, HM | 551 | 5 | HM 23/0/0 | 0 |
| JW-S28 | 32 | LF, KB, TU, GS | 262 | 3 | GS 13/2/0 | 0 |
| JW-S29 | 16 | LF, KF, LB, ST, GS, HM | 183 | 6 | HM 21/0/0, GS 42/0/0 | 0 |
| JW-S30 | 16 | KF, KB, AR | 620 | 3 | — | 0 |
| JW-T01 | 8 | LF, KF, LB, KB, TU, GS | 144 | 5 | GS 7/0/2 | 0 |
| JW-T02 | 8 | KF, LB, KB, ST, GS | 262 | 4 | GS 14/0/10 | 0 |
| JW-T03 | 8 | LF, LB, AR, TU, GS, HM | 108 | 4 | HM 10/0/0, GS 1/3/0 | 0 |
| JW-T04 | 8 | LF, KF, LB, KB, AR, ST, HM | 185 | 6 | HM 15/5/0 | 0 |
| JW-T05 | 8 | LF, LB, AR, GS | 85 | 4 | GS 8/3/1 | 0 |
| JW-T06 | 8 | LF, LB, KB, AR, TU, HM | 85 | 4 | HM 8/2/0 | 0 |
| JW-T07 | 8 | LF, KF, KB, AR, ST, GS | 342 | 5 | GS 9/8/0 | 0 |
| JW-T08 | 8 | LF, KF, LB, KB, AR, ST, GS | 192 | 4 | GS 14/1/0 | 0 |
| JW-T09 | 8 | LF, LB, AR, TU | 78 | 3 | — | 0 |
| JW-T10 | 8 | LF, LB, AR, TU, GS | 77 | 4 | GS 3/0/2 | 0 |

## 6 Verbleibende Unsicherheiten

- Alle konkreten Vorlagen sind eigene Konstruktionen [E]; die Belege betreffen Verfahren auf Cue-Ebene, keine Partiturtakte.
- Richards’ „Alpha chord“ und „action extensions“ sind nicht öffentlich definiert und werden nicht als Akkorddefinition verwendet; JW-H74 nennt die Verbindung nur als Hypothese.
- E.T.-Belege stammen überwiegend aus einer studentischen Arbeit (Normandie).
- Ganztonharmonik (JW-H26, JW-M31) bleibt Hypothese.
- Stimmführung der Flächen ist in den MIDI-Beispielen einfach (enge Lage ab festem Ton); im Plugin sollte die vorhandene Stimmführung greifen.
- Tempo-, Dynamik- und XYZ-Werte sind Setzungen; die Hörabnahme entscheidet, besonders bei JW-S16, S19, S20, S28, S29 und S30.