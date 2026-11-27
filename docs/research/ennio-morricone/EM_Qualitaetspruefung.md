# EM_Qualitaetspruefung – maschinelle Prüfergebnisse der Morricone-Vorlagenbibliothek

Stand: 27.11.2026. Alle Ergebnisse stammen aus einem tatsächlichen Prüflauf über das gemeinsame Datenmodell, die gerenderten Ereignisse, die geschriebenen MIDI-Dateien (zurückgelesen) und die CSV. **Eine Hörprüfung hat nicht stattgefunden.**

## 1. Übersicht

| Kategorie | Anzahl |
|---|---|
| H Harmonik | 119 |
| U Übergänge | 50 |
| R Rhythmik | 64 |
| B Bass | 52 |
| C Mikrozellen | 46 |
| M Motive | 50 |
| P Phrasen | 22 |
| K Module | 38 |
| EF Ereignisfelder | 16 |
| T Transformationen | 20 |
| S Modellstudien | 57 |
| **Summe Vorlagen** | **534** |
| MIDI-Studien (S + EF) | 73 |

Hinweis: Die Anzahl ist kein Beleg für musikalische Vielfalt. Vielfalt wird unten über Duplikatprüfung, Akkordqualitäten, Säulen- und XYZ-Abdeckung beurteilt.

## 2. Ergebnisse je Prüfpunkt

| Prüfpunkt | Ergebnis | Status |
|---|---|---|
| Eindeutige IDs | 534 IDs, Duplikate: 0, alle mit Präfix EM: ja | bestanden |
| Querverweise | 654 Verweise geprüft, ungültig: 0 | bestanden |
| Tatsächliche musikalische Duplikate | exakte Duplikate: 0; reine Oktavverschiebungen ganzer H-Sätze: 0; Lagenvarianten gleicher Pitch-Classes mit anderer Stimmverteilung (beabsichtigt): 1 | bestanden |
| Akkordqualitäten (H, alle Klänge) | Fehler: 0 (Oberstimmen ⊆ Akkord, alle wesentlichen Akkordtöne in Ober- oder Bassstimme) | bestanden |
| Akkordqualitäten (U, alle Zustände) | Fehler: 0 | bestanden |
| Gemeinsamtöne (U) | gemeinsame Pitch-Classes, die in beiden Voicings vorkommen, aber nicht in derselben Tonhöhe liegen bleiben: 0 | bestanden |
| Tatsächliches Halten deklarierter Gemeinsamtöne (MIDI) | 50/50 Übergänge bestanden; 132 gehaltene Töne über den Wechselzeitpunkt hinweg als eine gebundene Note geprüft | bestanden |
| Stimmführungsintervalle (U) | Sprünge > Quinte in Oberstimmen: 0; Quint-/Oktavparallelen: 0 | bestanden |
| Bassbewegungen (U) | Beträge (Halbtöne: Anzahl): 0: 17, 1: 7, 2: 8, 3: 6, 4: 6, 5: 8, 7: 6, 9: 1 | bestanden |
| Auflösungsziele (Vorhalte V) | unaufgelöste deklarierte Vorhalte in Studien: 0 | bestanden |
| Intervallangaben (M, B) | Intervalle aus Tonhöhen neu berechnet; Taktsummen-Fehler M: 0; Zelltöne außerhalb der deklarierten Zelle: 0 | bestanden |
| Vollständige Tonhöhen-/Rhythmuszyklen | R: 64 Zyklen berechnet (kgV Periode/Takt); B: 52 Zyklen (kgV Ton-/Einsatzperiode) | bestanden |
| Tonfunktionen (alle Studien) | A 7104, T 2148, V 2, F 79, U 139; davon F deklariert (Farbton/Ereignisfeld): 53; **F ohne Deklaration: 0** | bestanden |
| Harmonische Kontexte während langer Noten | Noten über mehrere Harmonien: 517; davon mit Funktionswechsel: 8 (alle Pedale/gebundene Gemeinsamtöne; Liste in CSV-Spalte funktionsfolge) | bestanden |
| Geschützte Konsonanz (Schicht K) | K-Töne lokal geprüft; global gegen die dissonante Umgebung: A 42, T 56, F 0 | bestanden |
| MIDI/CSV-Übereinstimmung | 73/73 Studien identisch (Spur, Tick, Dauer, Note, Velocity) | bestanden |
| Note-on/off-Bilanz | 73/73 Dateien ausgeglichen, keine hängenden Noten; PPQ 960 | bestanden |
| Unbeabsichtigte Notenüberlagerungen | nach Gleichtonhygiene: 0; dabei gekürzte frühere Noten: 4 (Neuanschlag derselben Tonhöhe in derselben Rolle) | bestanden |
| Rollenregister | Verstöße gegen die Präferenzbereiche: 0 | bestanden |
| Polyphonie je Rolle | Überschreitungen (LF 6, KF 6, LB 2, KB 2, AR 3, TU 4, GS 2, HM 1, ST 1): 0 | bestanden |
| Fester Stich-Trigger | ST-Ereignisse mit anderer Note als 36: 0 Studien | bestanden |
| Gate-Zuordnungen | rollenabhängige Gates (KB 0,85; AR 0,6–0,9; HM/GS 0,95; TU 0,9) im Rendern angewandt; Überlagerungen siehe oben | bestanden |

Lagenvarianten (gleiche Pitch-Class-Folge, andere Stimmverteilung – beabsichtigt, z. B. Reibung eng vs. offen): EM-H001/EM-H002

## 3. Übergänge im Detail (Halten im MIDI)

| Übergang | gehaltene Töne geprüft | Ergebnis | Solver-Hinweis |
|---|---|---|---|
| EM-U001 | 2 | bestanden | – |
| EM-U002 | 3 | bestanden | – |
| EM-U003 | 1 | bestanden | – |
| EM-U004 | 2 | bestanden | – |
| EM-U005 | 3 | bestanden | Zustand 1: nur 3 von 4 gewünschten Haltetönen lösbar |
| EM-U006 | 2 | bestanden | – |
| EM-U007 | 3 | bestanden | – |
| EM-U008 | 3 | bestanden | – |
| EM-U009 | 2 | bestanden | – |
| EM-U010 | 2 | bestanden | – |
| EM-U011 | 2 | bestanden | – |
| EM-U012 | 2 | bestanden | – |
| EM-U013 | 3 | bestanden | – |
| EM-U014 | 3 | bestanden | – |
| EM-U015 | 3 | bestanden | – |
| EM-U016 | 3 | bestanden | – |
| EM-U017 | 3 | bestanden | – |
| EM-U018 | 3 | bestanden | – |
| EM-U019 | 2 | bestanden | – |
| EM-U020 | 3 | bestanden | Zustand 1: nur 3 von 4 gewünschten Haltetönen lösbar |
| EM-U021 | 1 | bestanden | – |
| EM-U022 | 2 | bestanden | – |
| EM-U023 | 1 | bestanden | – |
| EM-U024 | 2 | bestanden | – |
| EM-U025 | 3 | bestanden | – |
| EM-U026 | 1 | bestanden | – |
| EM-U027 | 1 | bestanden | – |
| EM-U028 | 2 | bestanden | – |
| EM-U029 | 11 | bestanden | – |
| EM-U030 | 10 | bestanden | – |
| EM-U031 | 2 | bestanden | Zustand 1: nur 3 von 4 gewünschten Haltetönen lösbar |
| EM-U032 | 2 | bestanden | Zustand 1: nur 3 von 4 gewünschten Haltetönen lösbar |
| EM-U033 | 3 | bestanden | – |
| EM-U034 | 1 | bestanden | – |
| EM-U035 | 3 | bestanden | – |
| EM-U036 | 3 | bestanden | – |
| EM-U037 | 2 | bestanden | – |
| EM-U038 | 3 | bestanden | – |
| EM-U039 | 3 | bestanden | – |
| EM-U040 | 6 | bestanden | Zustand 3: nur 1 von 2 gewünschten Haltetönen lösbar |
| EM-U041 | 4 | bestanden | – |
| EM-U042 | 1 | bestanden | – |
| EM-U043 | 2 | bestanden | – |
| EM-U044 | 1 | bestanden | – |
| EM-U045 | 1 | bestanden | – |
| EM-U046 | 2 | bestanden | Zustand 1: nur 2 von 3 gewünschten Haltetönen lösbar |
| EM-U047 | 3 | bestanden | – |
| EM-U048 | 1 | bestanden | Zustand 1: nur 3 von 4 gewünschten Haltetönen lösbar |
| EM-U049 | 2 | bestanden | Zustand 1: nur 2 von 3 gewünschten Haltetönen lösbar |
| EM-U050 | 3 | bestanden | – |

## 4. Mikrozellen: Inversion und Permutation

| Zelle | Inversion = Permutation? | gleiche Menge nach Transposition um |
|---|---|---|
| EM-C001 | nein | 3 |
| EM-C002 | nein | 2 |
| EM-C003 | nein | 5 |
| EM-C004 | nein | 1 |
| EM-C005 | ja | 0, 6 |
| EM-C006 | nein | – |
| EM-C007 | nein | 2 |
| EM-C008 | nein | – |
| EM-C009 | nein | – |
| EM-C010 | nein | – |
| EM-C011 | ja | 0 |
| EM-C012 | nein | – |
| EM-C013 | nein | – |
| EM-C014 | nein | – |
| EM-C015 | nein | – |
| EM-C016 | nein | – |
| EM-C017 | ja | 0, 4, 8 |
| EM-C018 | nein | 6 |
| EM-C019 | nein | 2 |
| EM-C020 | nein | 4 |
| EM-C021 | nein | – |
| EM-C022 | nein | 9 |
| EM-C023 | nein | 9 |
| EM-C024 | nein | 5 |
| EM-C025 | nein | 3 |
| EM-C026 | nein | 5 |
| EM-C027 | nein | 8 |
| EM-C028 | nein | – |
| EM-C029 | nein | 4 |
| EM-C030 | nein | 8 |
| EM-C031 | nein | 9 |
| EM-C032 | nein | 3 |
| EM-C033 | nein | 7 |
| EM-C034 | nein | – |
| EM-C035 | nein | – |
| EM-C036 | nein | – |
| EM-C037 | nein | 6 |
| EM-C038 | nein | 2, 8 |
| EM-C039 | nein | – |
| EM-C040 | ja | 0 |
| EM-C041 | nein | 11 |
| EM-C042 | nein | 10 |
| EM-C043 | nein | 10 |
| EM-C044 | nein | 4 |
| EM-C045 | nein | – |
| EM-C046 | nein | 1 |

Zellgrößen: 2 Töne: 7, 3 Töne: 15, 4 Töne: 16, 5 Töne: 3, 6 Töne: 1, 7 Töne: 4

## 5. Ereignisfelder (in den Studien gemessen)

| Studie | Feld | Ereignisse | Antworten | Abstandsverstöße | Zellbindung | Imitation in Zelle | max. je Takt (Grenze) | Takte ohne Ereignis |
|---|---|---|---|---|---|---|---|---|
| EM-S010 | EM-EF13 | 59 | 46 | 0 | ja | ja | 6 (6) | 1 |
| EM-S011 | EM-EF08 | 25 | 19 | 0 | ja | ja | 3 (3) | 1 |
| EM-S024 | EM-EF04 | 18 | 17 | 0 | ja | ja | 2 (2) | 1 |
| EM-S038 | EM-EF05 | 2 | 0 | 0 | ja | ja | 1 (1) | 14 |
| EM-S040 | EM-EF15 | 13 | 0 | 0 | ja | ja | 3 (3) | 1 |
| EM-S042 | EM-EF07 | 9 | 0 | 0 | ja | ja | 2 (2) | 5 |
| EM-S051 | EM-EF14 | 71 | 0 | 0 | ja | ja | 2 (2) | 0 |
| EM-EF01 | EM-EF01 | 10 | 0 | 0 | ja | ja | 2 (2) | 7 |
| EM-EF02 | EM-EF02 | 12 | 12 | 0 | ja | ja | 2 (2) | 6 |
| EM-EF03 | EM-EF03 | 18 | 13 | 0 | ja | ja | 2 (2) | 0 |
| EM-EF04 | EM-EF04 | 17 | 15 | 0 | ja | ja | 2 (2) | 1 |
| EM-EF05 | EM-EF05 | 5 | 0 | 0 | ja | ja | 1 (1) | 11 |
| EM-EF06 | EM-EF06 | 24 | 16 | 0 | ja | ja | 3 (3) | 0 |
| EM-EF07 | EM-EF07 | 11 | 0 | 0 | ja | ja | 2 (2) | 6 |
| EM-EF08 | EM-EF08 | 24 | 24 | 0 | ja | ja | 3 (3) | 0 |
| EM-EF09 | EM-EF09 | 2 | 0 | 0 | ja | ja | 1 (1) | 14 |
| EM-EF10 | EM-EF10 | 66 | 0 | 0 | ja | ja | 6 (16) | 0 |
| EM-EF11 | EM-EF11 | 8 | 5 | 0 | ja | ja | 1 (1) | 8 |
| EM-EF12 | EM-EF12 | 18 | 18 | 0 | ja | ja | 2 (2) | 1 |
| EM-EF13 | EM-EF13 | 71 | 53 | 0 | ja | ja | 6 (6) | 1 |
| EM-EF14 | EM-EF14 | 21 | 0 | 0 | ja | ja | 2 (2) | 0 |
| EM-EF15 | EM-EF15 | 25 | 0 | 0 | ja | ja | 3 (3) | 3 |
| EM-EF16 | EM-EF16 | 19 | 15 | 0 | ja | ja | 2 (2) | 0 |

Gestaffelte Felder (EM-EF10) zählen jeden Akkordton als Ereignis; die Grenze ist dort Dichte × Zellgröße.

## 6. Modul-Kombinierbarkeit

Paare: 417 frei, 210 bedingt, 76 ungeeignet (von 703).
Dreierkombinationen: 5145 frei, 945 bedingt, 2346 paarweise ausgeschlossen.

Beispiele bedingter Dreiergruppen mit Begründung:
- EM-K001 + EM-K016 + EM-K026: Hauptmelodie plus weiteres thematisches Modul: Komplementarität erforderlich
- EM-K001 + EM-K016 + EM-K028: Hauptmelodie plus weiteres thematisches Modul: Komplementarität erforderlich
- EM-K001 + EM-K026 + EM-K027: Hauptmelodie plus weiteres thematisches Modul: Komplementarität erforderlich
- EM-K001 + EM-K026 + EM-K029: Hauptmelodie plus weiteres thematisches Modul: Komplementarität erforderlich
- EM-K001 + EM-K027 + EM-K028: Hauptmelodie plus weiteres thematisches Modul: Komplementarität erforderlich
- EM-K001 + EM-K027 + EM-K029: drei Module im selben Oktavraum um rel 6
- EM-K001 + EM-K028 + EM-K029: Hauptmelodie plus weiteres thematisches Modul: Komplementarität erforderlich
- EM-K002 + EM-K016 + EM-K026: Hauptmelodie plus weiteres thematisches Modul: Komplementarität erforderlich
- EM-K002 + EM-K016 + EM-K028: Hauptmelodie plus weiteres thematisches Modul: Komplementarität erforderlich
- EM-K002 + EM-K026 + EM-K027: Hauptmelodie plus weiteres thematisches Modul: Komplementarität erforderlich
- EM-K002 + EM-K026 + EM-K029: Hauptmelodie plus weiteres thematisches Modul: Komplementarität erforderlich
- EM-K002 + EM-K027 + EM-K028: Hauptmelodie plus weiteres thematisches Modul: Komplementarität erforderlich
- EM-K002 + EM-K027 + EM-K029: drei Module im selben Oktavraum um rel 6
- EM-K002 + EM-K028 + EM-K029: Hauptmelodie plus weiteres thematisches Modul: Komplementarität erforderlich
- EM-K003 + EM-K016 + EM-K026: Hauptmelodie plus weiteres thematisches Modul: Komplementarität erforderlich

In den Studien verwendete Modulkombinationen (Paarstatus):
- EM-S018 ab Takt 1: EM-K002 + EM-K008 + EM-K023 → frei, frei, frei
- EM-S018 ab Takt 9: EM-K002 + EM-K011 + EM-K018 → frei, bedingt, bedingt
- EM-S018 ab Takt 17: EM-K003 + EM-K009 + EM-K017 → frei, bedingt, frei
- EM-S018 ab Takt 25: EM-K002 + EM-K008 + EM-K022 → frei, frei, frei
- EM-S025 ab Takt 1: EM-K001 + EM-K008 + EM-K022 → frei, frei, frei
- EM-S025 ab Takt 9: EM-K001 + EM-K013 + EM-K023 → bedingt, frei, bedingt
- EM-S025 ab Takt 17: EM-K002 + EM-K011 + EM-K019 → frei, bedingt, bedingt
- EM-S025 ab Takt 25: EM-K006 + EM-K010 + EM-K024 → frei, frei, frei
- EM-S025 ab Takt 33: EM-K002 + EM-K008 + EM-K017 → frei, bedingt, frei
- EM-S025 ab Takt 41: EM-K005 + EM-K009 + EM-K025 → frei, frei, frei
- EM-S025 ab Takt 49: EM-K001 + EM-K012 + EM-K020 → frei, frei, frei
- EM-S025 ab Takt 57: EM-K002 + EM-K008 + EM-K022 → frei, frei, frei
- EM-S045 ab Takt 1: EM-K030 → Einzelmodul

Bedingte Paare in den Studien sind beabsichtigt (z. B. inkongruente Perioden als Phasenversatz) und musikalisch begründet; ungeeignete Paare werden in keiner Studie verwendet.

## 7. XYZ-Abdeckung (3×3×3-Raster)

Anzahl Vorlagen, deren Gültigkeitsbereich den Rasterpunkt enthält (Dimensionen „beliebig“ zählen überall), sowie Studien mit Anker im Umkreis ±0,3.

| X | Y | Z | H | U | R | B | C | M | S/EF |
|---|---|---|---|---|---|---|---|---|---|
| 0,00 | 0,00 | 0,00 | 2 | 0 | 2 | 1 | 7 | 0 | 1 |
| 0,00 | 0,00 | 0,50 | 1 | 0 | 3 | 0 | 7 | 0 | 6 |
| 0,00 | 0,00 | 1,00 | 1 | 0 | 0 | 0 | 7 | 0 | 1 |
| 0,00 | 0,50 | 0,00 | 1 | 0 | 2 | 5 | 7 | 0 | 2 |
| 0,00 | 0,50 | 0,50 | 11 | 1 | 37 | 17 | 7 | 1 | 15 |
| 0,00 | 0,50 | 1,00 | 1 | 0 | 1 | 0 | 7 | 0 | 3 |
| 0,00 | 1,00 | 0,00 | 1 | 0 | 1 | 0 | 7 | 0 | 1 |
| 0,00 | 1,00 | 0,50 | 3 | 0 | 2 | 1 | 7 | 0 | 1 |
| 0,00 | 1,00 | 1,00 | 1 | 0 | 0 | 0 | 7 | 0 | 2 |
| 0,50 | 0,00 | 0,00 | 3 | 0 | 2 | 1 | 34 | 2 | 19 |
| 0,50 | 0,00 | 0,50 | 2 | 0 | 3 | 0 | 34 | 4 | 27 |
| 0,50 | 0,00 | 1,00 | 1 | 0 | 0 | 0 | 34 | 0 | 2 |
| 0,50 | 0,50 | 0,00 | 13 | 6 | 2 | 9 | 34 | 7 | 25 |
| 0,50 | 0,50 | 0,50 | 21 | 7 | 37 | 20 | 34 | 12 | 47 |
| 0,50 | 0,50 | 1,00 | 1 | 0 | 1 | 0 | 34 | 0 | 5 |
| 0,50 | 1,00 | 0,00 | 1 | 0 | 1 | 0 | 34 | 1 | 3 |
| 0,50 | 1,00 | 0,50 | 1 | 0 | 2 | 3 | 34 | 2 | 6 |
| 0,50 | 1,00 | 1,00 | 1 | 0 | 0 | 0 | 34 | 0 | 1 |
| 1,00 | 0,00 | 0,00 | 3 | 0 | 2 | 1 | 1 | 0 | 5 |
| 1,00 | 0,00 | 0,50 | 1 | 0 | 3 | 0 | 1 | 2 | 6 |
| 1,00 | 0,00 | 1,00 | 1 | 0 | 0 | 0 | 1 | 0 | 1 |
| 1,00 | 0,50 | 0,00 | 1 | 0 | 2 | 4 | 1 | 0 | 6 |
| 1,00 | 0,50 | 0,50 | 1 | 0 | 37 | 8 | 1 | 0 | 9 |
| 1,00 | 0,50 | 1,00 | 1 | 0 | 1 | 0 | 1 | 0 | 2 |
| 1,00 | 1,00 | 0,00 | 1 | 0 | 1 | 0 | 1 | 0 | 1 |
| 1,00 | 1,00 | 0,50 | 1 | 0 | 2 | 1 | 1 | 0 | 2 |
| 1,00 | 1,00 | 1,00 | 1 | 0 | 0 | 0 | 1 | 0 | 1 |

Alle 27 Rasterpunkte sind mit mindestens einer H-Vorlage und einer Studie im Umkreis versorgt.

## 8. Säulenbalance

| Kategorie | A Lyrik | AB Verbindung | B Experiment |
|---|---|---|---|
| H | 67 | 19 | 33 |
| R | 12 | 16 | 36 |
| B | 18 | 6 | 28 |
| C | 20 | 7 | 19 |
| M | 32 | 11 | 7 |
| U | 47 | 0 | 3 |
| P | 14 | 6 | 2 |
| EF | 4 | 5 | 7 |
| S | 30 | 12 | 15 |
| **Summe** | **244** | **82** | **150** |

Modellstudien: 57; ohne HM und GS 41 (Mehrheit verlangt: > 28); ohne AR 43; ohne durchlaufenden Puls 39; 64-Takt-Studien 8 (verlangt: ≥ 6).

## 9. Studien – Kennzahlen

| Studie | Takte | Ereignisse | Rollen | A | T | V | F | U | MIDI=CSV | Bilanz |
|---|---|---|---|---|---|---|---|---|---|---|
| EM-S001 | 16 | 64 | LF LB TU | 55 | 9 | 0 | 0 | 0 | ja | ok |
| EM-S002 | 16 | 38 | LF LB TU | 38 | 0 | 0 | 0 | 0 | ja | ok |
| EM-S003 | 16 | 36 | LF LB | 36 | 0 | 0 | 0 | 0 | ja | ok |
| EM-S004 | 16 | 38 | LF LB | 38 | 0 | 0 | 0 | 0 | ja | ok |
| EM-S005 | 16 | 52 | LF LB TU | 46 | 6 | 0 | 0 | 0 | ja | ok |
| EM-S006 | 32 | 151 | LF LB TU | 134 | 14 | 0 | 3 | 0 | ja | ok |
| EM-S007 | 16 | 64 | LF LB HM | 41 | 23 | 0 | 0 | 0 | ja | ok |
| EM-S008 | 16 | 49 | LF KF LB TU | 45 | 0 | 0 | 0 | 4 | ja | ok |
| EM-S009 | 16 | 118 | KF LB AR | 88 | 30 | 0 | 0 | 0 | ja | ok |
| EM-S010 | 16 | 111 | LF KF TU | 79 | 32 | 0 | 0 | 0 | ja | ok |
| EM-S011 | 16 | 50 | LF KF TU | 43 | 7 | 0 | 0 | 0 | ja | ok |
| EM-S012 | 16 | 25 | LF LB TU | 15 | 4 | 0 | 0 | 6 | ja | ok |
| EM-S013 | 32 | 283 | LF KB AR | 283 | 0 | 0 | 0 | 0 | ja | ok |
| EM-S014 | 16 | 58 | LF LB ST | 34 | 0 | 0 | 0 | 0 | ja | ok |
| EM-S015 | 32 | 892 | LF KB AR ST HM | 573 | 259 | 0 | 0 | 0 | ja | ok |
| EM-S016 | 16 | 231 | LF LB AR HM | 227 | 4 | 0 | 0 | 0 | ja | ok |
| EM-S017 | 16 | 118 | LF KB TU HM | 98 | 20 | 0 | 0 | 0 | ja | ok |
| EM-S018 | 32 | 186 | LF LB KB AR TU | 174 | 12 | 0 | 0 | 0 | ja | ok |
| EM-S019 | 16 | 69 | LF LB HM | 57 | 12 | 0 | 0 | 0 | ja | ok |
| EM-S020 | 64 | 230 | LF LB TU GS | 201 | 29 | 0 | 0 | 0 | ja | ok |
| EM-S021 | 64 | 217 | LF LB TU | 157 | 56 | 0 | 4 | 0 | ja | ok |
| EM-S022 | 64 | 651 | LF KB AR TU | 626 | 25 | 0 | 0 | 0 | ja | ok |
| EM-S023 | 64 | 1528 | LF KB AR TU ST HM | 972 | 440 | 0 | 0 | 0 | ja | ok |
| EM-S024 | 64 | 340 | LF KF LB TU GS | 212 | 38 | 0 | 10 | 80 | ja | ok |
| EM-S025 | 64 | 417 | LF KF LB KB AR TU | 308 | 87 | 0 | 0 | 22 | ja | ok |
| EM-S026 | 64 | 238 | LF LB TU GS | 197 | 41 | 0 | 0 | 0 | ja | ok |
| EM-S027 | 16 | 21 | LF LB | 21 | 0 | 0 | 0 | 0 | ja | ok |
| EM-S028 | 8 | 27 | LF LB TU | 21 | 6 | 0 | 0 | 0 | ja | ok |
| EM-S029 | 16 | 53 | LF LB GS | 44 | 9 | 0 | 0 | 0 | ja | ok |
| EM-S030 | 16 | 34 | LF LB TU | 34 | 0 | 0 | 0 | 0 | ja | ok |
| EM-S031 | 16 | 38 | LF LB | 38 | 0 | 0 | 0 | 0 | ja | ok |
| EM-S032 | 16 | 184 | LF LB AR | 130 | 54 | 0 | 0 | 0 | ja | ok |
| EM-S033 | 16 | 114 | LF LB KB | 82 | 32 | 0 | 0 | 0 | ja | ok |
| EM-S034 | 8 | 16 | LF LB | 14 | 0 | 2 | 0 | 0 | ja | ok |
| EM-S035 | 8 | 16 | LF LB TU | 16 | 0 | 0 | 0 | 0 | ja | ok |
| EM-S036 | 8 | 36 | LF LB GS HM | 28 | 8 | 0 | 0 | 0 | ja | ok |
| EM-S037 | 8 | 54 | LF LB GS HM | 39 | 15 | 0 | 0 | 0 | ja | ok |
| EM-S038 | 16 | 28 | LF KB TU | 27 | 0 | 0 | 1 | 0 | ja | ok |
| EM-S039 | 16 | 365 | LF KB AR | 365 | 0 | 0 | 0 | 0 | ja | ok |
| EM-S040 | 8 | 50 | KF LB ST | 0 | 21 | 0 | 0 | 0 | ja | ok |
| EM-S041 | 8 | 73 | LF KF LB AR | 39 | 28 | 0 | 0 | 6 | ja | ok |
| EM-S042 | 16 | 121 | LF KB TU | 62 | 59 | 0 | 0 | 0 | ja | ok |
| EM-S043 | 8 | 23 | LF LB GS | 22 | 0 | 0 | 0 | 1 | ja | ok |
| EM-S044 | 16 | 282 | LF KB AR | 250 | 32 | 0 | 0 | 0 | ja | ok |
| EM-S045 | 16 | 211 | LF KF LB | 139 | 72 | 0 | 0 | 0 | ja | ok |
| EM-S046 | 8 | 28 | LF LB | 26 | 2 | 0 | 0 | 0 | ja | ok |
| EM-S047 | 16 | 33 | LF LB TU | 19 | 6 | 0 | 0 | 8 | ja | ok |
| EM-S048 | 16 | 51 | LF LB HM | 38 | 13 | 0 | 0 | 0 | ja | ok |
| EM-S049 | 8 | 43 | LF LB TU | 35 | 0 | 0 | 0 | 8 | ja | ok |
| EM-S050 | 16 | 93 | LF LB KB AR | 77 | 12 | 0 | 0 | 4 | ja | ok |
| EM-S051 | 64 | 91 | LF TU ST | 38 | 20 | 0 | 21 | 0 | ja | ok |
| EM-S052 | 32 | 132 | LF LB TU | 115 | 17 | 0 | 0 | 0 | ja | ok |
| EM-S053 | 16 | 20 | LF LB TU | 18 | 2 | 0 | 0 | 0 | ja | ok |
| EM-S054 | 16 | 76 | LF LB GS | 55 | 21 | 0 | 0 | 0 | ja | ok |
| EM-S055 | 16 | 40 | LF LB TU | 33 | 7 | 0 | 0 | 0 | ja | ok |
| EM-S056 | 16 | 62 | LF LB HM | 52 | 10 | 0 | 0 | 0 | ja | ok |
| EM-S057 | 16 | 424 | KF KB AR ST | 174 | 226 | 0 | 0 | 0 | ja | ok |
| EM-EF01 | 16 | 15 | LF LB TU | 15 | 0 | 0 | 0 | 0 | ja | ok |
| EM-EF02 | 16 | 28 | KF LB TU | 0 | 28 | 0 | 0 | 0 | ja | ok |
| EM-EF03 | 16 | 64 | LF LB TU GS | 58 | 6 | 0 | 0 | 0 | ja | ok |
| EM-EF04 | 16 | 37 | LF LB TU GS | 26 | 4 | 0 | 7 | 0 | ja | ok |
| EM-EF05 | 16 | 5 | TU | 0 | 5 | 0 | 0 | 0 | ja | ok |
| EM-EF06 | 16 | 45 | LF KF LB TU | 19 | 12 | 0 | 14 | 0 | ja | ok |
| EM-EF07 | 16 | 15 | LB TU | 0 | 15 | 0 | 0 | 0 | ja | ok |
| EM-EF08 | 16 | 48 | KF TU | 0 | 48 | 0 | 0 | 0 | ja | ok |
| EM-EF09 | 16 | 2 | TU | 0 | 2 | 0 | 0 | 0 | ja | ok |
| EM-EF10 | 16 | 66 | TU | 0 | 66 | 0 | 0 | 0 | ja | ok |
| EM-EF11 | 16 | 48 | LF LB TU GS | 46 | 2 | 0 | 0 | 0 | ja | ok |
| EM-EF12 | 16 | 36 | KF TU | 0 | 36 | 0 | 0 | 0 | ja | ok |
| EM-EF13 | 16 | 130 | LF KF TU | 97 | 33 | 0 | 0 | 0 | ja | ok |
| EM-EF14 | 16 | 21 | TU | 0 | 21 | 0 | 0 | 0 | ja | ok |
| EM-EF15 | 16 | 40 | KF ST | 0 | 25 | 0 | 0 | 0 | ja | ok |
| EM-EF16 | 16 | 59 | LF KF TU | 15 | 25 | 0 | 19 | 0 | ja | ok |

## 10. Technische Voraussetzungen (nicht als vorhanden angenommen)

Siehe Vokabular Abschnitt 2: Übergangsabsichten im Stimmführungs-Solver, Schichtharmonie lokal/global, Zellen-Datentyp mit Permutator und Austauschton, Polyperiodik je Rolle, additive Enthüllung, Modulpool mit Kompatibilitätsprüfung, Ereignisfeld-Gesprächsmodus, Gleichtonhygiene.

## 11. Korrekturen und Anpassungen während des Prüflaufs

- Drei U-Ausgangsvoicings korrigiert (falsche Tonhöhe für F♯/F bzw. fehlender Grundton), danach alle Zustände akkordrein.
- Eine Lamento-Progression (EM-H033) und eine chromatische Mittelstimmen-Progression (EM-H101) wegen falscher Bassakkorde neu gesetzt.
- Exakte Rhythmus- und Bass-Duplikate entfernt (EM-R024, EM-R039, EM-B024 neu gefasst); Zweischicht-Harmonik wird jetzt inklusive dissonanter Schicht auf Duplikate geprüft.
- Taktsummen von zwei Motiven (EM-M022, EM-M049) korrigiert; drei Zellbezüge von Motiven korrigiert.
- Registerzentrum je Tonika angepasst (C…E♭ eine Oktave höher), dadurch keine Registerverstöße mehr.
- Undeklarierte Fremdtöne beseitigt: Zellen folgen der lokalen Harmonie per Anpassung an den nächsten Akkordton, Austauschtöne und Ereignisfeldtöne sind als F deklariert, dissonanzautorisierte Bässe als U.
- EM-B033 auf zwei Kleinterzpaare im Tritonusabstand (oktatonisch) umgestellt, EM-C046 auf Halbtonpaar, EM-K020 als F-Schicht gekennzeichnet.
- Zweiter Prüflauf: Die Ereignisfeld-Messung zählte die Feldereignisse nicht (Filter auf fehlende statt deklarierte Absicht „EF“); korrigiert, die Tabelle in Abschnitt 5 enthält jetzt die tatsächlichen Ereigniszahlen, Dichtemaxima und stillen Takte.
- Zweiter Prüflauf: Töne ohne Akkordkontext (reine Ereignisfelder) wurden klassifiziert, aber nicht in die Tonfunktions-Statistik übernommen; korrigiert. Töne der dissonanten Schicht ohne Akkordkontext gelten als U.
- Zweiter Prüflauf: Der Zufallsgenerator der Ereignisfelder hing von Pythons prozessabhängigem String-Hash ab und war damit nicht reproduzierbar; ersetzt durch CRC32 der Studien-ID. Zwei aufeinanderfolgende Läufe liefern jetzt identische Ergebnisse.
- Zweiter Prüflauf: Antworttöne der Ereignisfelder werden in das Präferenzregister der antwortenden Rolle oktaviert (vorher zwei Registerüberschreitungen in EM-EF11 und EM-EF15).
- Zweiter Prüflauf: Spurnamen der MIDI-Dateien werden als Latin-1 mit einfachem Bindestrich geschrieben (vorher UTF-8 mit Gedankenstrich, was viele DAWs als Zeichensalat anzeigen); Umlaute bleiben erhalten, z. B. „LF - Lange Fläche“.
- Zweiter Prüflauf: XYZ-Ecken und Randbereiche ergänzt (EM-H106 bis EM-H119, Studien EM-S053 bis EM-S057), weil mehrere Eckbereiche (u. a. hell/kraftvoll/stabil, hell/kraftvoll/unruhig, dunkel/kraftvoll/stabil) weder eine direkte H-Vorlage noch eine Studie im Umkreis hatten.

## 12. Verbleibende Unsicherheiten

- **Keine Hörprüfung.** Wirkung, Balance und Orchestrierbarkeit der Studien sind ungeprüft; die Studien sind Datenbelege der Vorlagen, keine fertigen Kompositionen.
- Die Modulprüfung ist regelbasiert; Klangfarben- und Dynamikwirkungen der DAW-Instrumente bleiben unberücksichtigt.
- Ereignisfelder nutzen einen deterministischen Seed (CRC32 der Studien-ID); andere Seeds erzeugen andere, regelgleiche Felder.
- Belege: siehe Evidenzkennung je Vorlage; Lolita-Akkordfolgen und Untouchables-Rhythmusdetails bleiben unbelegt.