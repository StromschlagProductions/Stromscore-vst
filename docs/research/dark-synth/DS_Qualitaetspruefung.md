# DS – Qualitätsprüfung der Dark-Synth-Erweiterung

*Stand: 28. November 2026 · gilt für STROMSCORE_Dark_Synth_Vokabular_Erweiterung.md, DS_Studien_Ereignisse.csv, DS_Studien_MIDI.zip*

## 1. Verfahren

Bibliothek, CSV und MIDI entstehen aus demselben Datenmodell wie das Carpenter-Profil. Die MIDI-Dateien werden mit der unabhängigen Bibliothek mido zurückgelesen und Note für Note (und Controller für Controller) mit der CSV verglichen. Die Carpenter-Bibliothek wurde nach den Engine-Erweiterungen erneut vollständig geprüft (23 von 23 Prüfungen bestanden).

## 2. Maschinelle Prüfungen

| # | Prüfung | Ergebnis | Details |
|---|---|---|---|
| 1 | MIDI-Rücklesung (mido) = CSV (Noten und Controller) | bestanden | 34 Dateien, 15035 Noten, 1463 Controller-Ereignisse; Abweichungen in 0 Dateien |
| 2 | Note-on/off-Bilanz | bestanden | offene/verwaiste Ereignisse: 0 |
| 3 | Auflösung 960 PPQ | bestanden | assert in allen Dateien |
| 4 | Keine Notenüberlagerungen gleicher Tonhöhe in einer Spur | bestanden | 0 [] |
| 5 | ST: Kanal 7, Note 36, nicht transponiert | bestanden | 4 Stich-Ereignisse |
| 6 | Rollenregister eingehalten | bestanden | [] |
| 7 | Harmonische Verträglichkeit (strenge Prüfung, ♭9 über Akkordton gilt nicht als T) | bestanden | Funktionen: {'A': 13827, 'F': 63, 'T': 951, 'V': 13, 'ST': 4, 'U': 177}; unautorisiert: 0 |
| 8 | Akkordbezeichnungen = klingende Tonklassen (alle DS-H-Segmente, Bezug A) | bestanden | 274 Segmente geprüft, Fehler: []; Negativtest mit absichtlich falschen Namen: alle erkannt |
| 9 | Alle 405 JC-IDs unverändert vorhanden | bestanden | JC-IDs: 405 |
| 10 | DS-IDs eindeutig | bestanden | 236 DS-IDs; Duplikate [] |
| 11 | Querverweise auf JC- und DS-IDs gültig | bestanden | ungültig: [] |
| 12 | Keine DS-Vorlage ist inhaltsgleich mit einer JC-Vorlage oder einer anderen DS-Vorlage | bestanden | inhaltsgleich mit JC: [] |
| 13 | Periodenangaben in den Vorlagentexten = berechnetes kgV mit dem Takt | bestanden | 56 Perioden berechnet; Abweichungen: [] |
| 14 | Gesamtwiederkehr der Periodenschichtung per Simulation bestätigt | bestanden | DS-S07: kgV = 24 Takte, Simulation deckungsgleich; DS-MS01: kgV = 8 Takte, Simulation deckungsgleich |
| 15 | Tupfer-Gedächtnis: Motividentität nach Transformation | bestanden | 117 TU-Ereignisse; Operationen {'frag': 9, 'orig': 42, 'frag+oct': 2, 'fit': 42, 'frag+fit': 3, 'echo': 7, 'trans': 10, 'trans+frag': 2}; Fehler [] |
| 16 | Tupfer hörbar: Abstand ≥ Quarte zu jedem gleichzeitig klingenden oder einsetzenden Sequencer-Ton | bestanden | 266 TU-Noten, Verstöße 0 |
| 17 | Modulationsdaten nur in den optionalen Modulationsstudien (GP-Controller 16–19) | bestanden | CC in Normalstudien: 0; verwendete CC: [16, 17, 18, 19] |
| 18 | 20–30 Studien, davon ≥ 4 × 64 und ≥ 2 × 128 Takte bei konstanter XYZ-Position | bestanden | {'studien': 30, 'modulation': 4, 'ohne_HM': 25, 'ohne_GS': 25, 'ohne_AR': 17, 'pulslos': 11, 't64': 6, 't128': 2} |
| 19 | Studien ohne HM, GS, AR und ohne durchgehenden Puls vorhanden | bestanden | {'studien': 30, 'modulation': 4, 'ohne_HM': 25, 'ohne_GS': 25, 'ohne_AR': 17, 'pulslos': 11, 't64': 6, 't128': 2} |
| 20 | Alle acht XYZ-Ecken mit mindestens einer DS-Studie | bestanden | leer: [] |
| 21 | DS-Harmonik deckt jede der 27 Zellen mit ≥ 2 Vorlagen | bestanden | Lücken: [] |

**Ergebnis:** 21 von 21 Prüfungen bestanden.

**Während der Erstellung gefunden und musikalisch behoben:**

- Strenge ♭9-Prüfung: Dur-Wiege über iii7 (DS-S02), Dur-Sechzehntel über Moll-vi (DS-S17), Moll-Arpeggio über v (DS-S19), Dur-Wiege über ♭VImaj7 (DS-S18) → Sequencer folgt dem Akkord bzw. wurde ersetzt.
- Schatten-Töne (♭6 über Moll) im Schatten-Arpeggio, Keim A und Rufbass sind gewollt → ausdrücklich als F autorisiert, nicht stillschweigend als T geführt.
- Glockenschläge im hexatonischen Pol lagen auf dem falschen Klang (DS-S12) → Positionen korrigiert.
- Nebelgang über 128 Takte: 16er- und 12er-Zelle rieben mit Em7 und G (C über H) → Sequencer laufen nur über Klänge, deren Töne sie enthalten.
- Hexatonischer Pol war inhaltsgleich mit JC-H041 → DS-Vorlage gestrichen, Studie nutzt JC-H041.
- Ein TU-Fragment lag weniger als eine Quarte neben dem oktavierten Sequencer (DS-S06) → verlegt.
- Zwei XYZ-Ecken ohne Studie und Lücken der DS-Harmonik in hellen/kraftvollen/unruhigen Zellen → zwei Studien (DS-S29, DS-S30) und sechs Harmonievorlagen ergänzt.

## 3. Kennzahlen

- studien: **30**
- modulation: **4**
- ohne_HM: **25**
- ohne_GS: **25**
- ohne_AR: **17**
- pulslos: **11**
- t64: **6**
- t128: **2**
- Tonfunktionen aller 15035 Noten: A 13827, T 951, U 177, F 63, V 13, ST 4

## 4. Perioden (berechnet)

| ID | Name | gemeinsame Periode (16tel) | Wiederkehr am Taktanfang |
|---|---|---|---|
| DS-Q01 | Schattenpaar-Arpeggio | 16 | 1 Takt(e) |
| DS-Q02 | Melancholisches Arpeggio 6 gegen 8 | 48 | 3 Takt(e) |
| DS-Q03 | 16er-Lückenzelle | 16 | 1 Takt(e) |
| DS-Q04 | 12er-Gegenzelle | 12 | 3 Takt(e) |
| DS-Q05 | 13er-Zelle | 13 | 13 Takt(e) |
| DS-Q06 | 10er-Zelle | 10 | 5 Takt(e) |
| DS-Q07 | Spieluhr-Sequenz | 16 | 1 Takt(e) |
| DS-Q08 | Glocken-Ostinato 3 gegen 8 | 48 | 3 Takt(e) |
| DS-Q09 | Nostalgie-Wiege in Dur | 16 | 1 Takt(e) |
| DS-Q10 | Prog-Ostinato 7 gegen 16 | 7 | 7 Takt(e) |
| DS-Q11 | Dorische Pendelsequenz | 16 | 1 Takt(e) |
| DS-Q12 | Halbton-Echo-Zelle | 16 | 1 Takt(e) |
| DS-Q13 | Gefrier-Zelle | 16 | 1 Takt(e) |
| DS-Q14 | Verzögerte Achtelzelle | 16 | 1 Takt(e) |
| DS-Q15 | Quartenkreis | 16 | 1 Takt(e) |
| DS-Q16 | Rollende Dur-Zelle | 16 | 1 Takt(e) |
| DS-Q17 | Moll-Wiege mit ♭6-Fluchtton | 16 | 1 Takt(e) |
| DS-Q18 | Choral-Repetition | 16 | 1 Takt(e) |
| DS-Q19 | Atmende Quintzelle | 16 | 1 Takt(e) |
| DS-Q20 | Mutationszelle | 16 | 1 Takt(e) |
| DS-Q21 | Triolen-Kettenläufer | 16 | 1 Takt(e) |
| DS-Q22 | Antwortlücken-Sequenz | 48 | 3 Takt(e) |
| DS-B01 | Oktavpuls mit Lücke | 16 | 1 Takt(e) |
| DS-B02 | Kriechbass ♭2–7 | 16 | 1 Takt(e) |
| DS-B03 | Pendel mit Vorschlag | 16 | 1 Takt(e) |
| DS-B04 | Rufbass | 32 | 2 Takt(e) |
| DS-B05 | Quint-Tresillo | 16 | 1 Takt(e) |
| DS-B06 | Rotationsbass in Achteln | 16 | 1 Takt(e) |
| DS-B07 | Nostalgie-Rollbass | 16 | 1 Takt(e) |
| DS-B08 | Rotationsfigur 1–♭6–4–♭6 | 32 | 2 Takt(e) |
| DS-B09 | Verschobener Doppelschlag | 16 | 1 Takt(e) |
| DS-B10 | 12er-Bassperiode | 12 | 3 Takt(e) |
| DS-B11 | 13er-Bassperiode | 13 | 13 Takt(e) |
| DS-B12 | 10er-Bassperiode | 10 | 5 Takt(e) |
| DS-B13 | Oktav-Orgelpunkt | 128 | 8 Takt(e) |
| DS-B14 | Choralbass mit Quintvorschlag | 16 | 1 Takt(e) |
| DS-B15 | 6/8-Wiegebass | 12 | 1 Takt(e) |
| DS-B16 | Antwortbass | 16 | 1 Takt(e) |
| DS-B17 | Galopp-Oktave | 16 | 1 Takt(e) |
| DS-B18 | Kriechende Halbe mit Leitton | 32 | 2 Takt(e) |
| DS-B19 | Wechselbass 1–♭6 | 64 | 4 Takt(e) |
| DS-B20 | Dur-Wiegebass | 16 | 1 Takt(e) |
| DS-B21 | Sakraler Grundbass | 16 | 1 Takt(e) |
| DS-R01 | Oktavpuls mit Lücke | 16 | 1 Takt(e) |
| DS-R02 | Pendel mit Vorschlag | 16 | 1 Takt(e) |
| DS-R03 | Rufbass-Rhythmus | 32 | 2 Takt(e) |
| DS-R04 | 12er-Periode | 12 | 3 Takt(e) |
| DS-R05 | 12er-Gegenzelle | 12 | 3 Takt(e) |
| DS-R06 | 13er-Periode | 13 | 13 Takt(e) |
| DS-R07 | 10er-Periode | 10 | 5 Takt(e) |
| DS-R08 | 16er-Lückenzelle | 16 | 1 Takt(e) |
| DS-R09 | Spieluhr-Rhythmus | 16 | 1 Takt(e) |
| DS-R10 | Verzögerter Step | 16 | 1 Takt(e) |
| DS-R11 | 7er-Periode | 7 | 7 Takt(e) |
| DS-R12 | Weiter Doppelschlag | 16 | 1 Takt(e) |
| DS-R13 | Antwortbass-Rhythmus | 16 | 1 Takt(e) |

Simulation: DS-S07 – kgV 24 Takte, deckungsgleich; DS-MS01 – kgV 8 Takte, deckungsgleich.

## 5. XYZ-Abdeckung der DS-Vorlagen

| X | Y | Z | H | R | Q | B | TU+HM | DS-Studien in der Zelle |
|---|---|---|---|---|---|---|---|---|
| 0,17 | 0,17 | 0,17 | 2 | 4 | 0 | 2 | 6 | DS-S29 |
| 0,17 | 0,17 | 0,50 | 5 | 3 | 0 | 3 | 15 | DS-S27 |
| 0,17 | 0,17 | 0,83 | 3 | 0 | 0 | 1 | 4 | DS-S16 |
| 0,17 | 0,50 | 0,17 | 2 | 4 | 0 | 5 | 7 | – |
| 0,17 | 0,50 | 0,50 | 10 | 11 | 6 | 9 | 19 | DS-S11, DS-S20 |
| 0,17 | 0,50 | 0,83 | 8 | 3 | 4 | 4 | 5 | – |
| 0,17 | 0,83 | 0,17 | 2 | 0 | 0 | 3 | 1 | DS-S08, DS-S15 |
| 0,17 | 0,83 | 0,50 | 4 | 7 | 5 | 7 | 4 | DS-S09 |
| 0,17 | 0,83 | 0,83 | 5 | 3 | 4 | 4 | 1 | DS-S14 |
| 0,50 | 0,17 | 0,17 | 18 | 4 | 2 | 5 | 22 | DS-S04, DS-S26 |
| 0,50 | 0,17 | 0,50 | 11 | 3 | 3 | 3 | 28 | – |
| 0,50 | 0,17 | 0,83 | 3 | 0 | 0 | 1 | 4 | DS-S12, DS-S24 |
| 0,50 | 0,50 | 0,17 | 29 | 4 | 5 | 9 | 26 | DS-S03, DS-S06, DS-S19, DS-S23 |
| 0,50 | 0,50 | 0,50 | 16 | 11 | 14 | 9 | 31 | DS-S05, DS-S07, DS-S13, DS-S21, DS-S22, DS-S28 |
| 0,50 | 0,50 | 0,83 | 4 | 3 | 3 | 3 | 4 | – |
| 0,50 | 0,83 | 0,17 | 5 | 0 | 1 | 3 | 4 | – |
| 0,50 | 0,83 | 0,50 | 3 | 7 | 5 | 6 | 3 | – |
| 0,50 | 0,83 | 0,83 | 2 | 3 | 3 | 3 | 0 | – |
| 0,83 | 0,17 | 0,17 | 16 | 4 | 2 | 1 | 14 | DS-S01, DS-S02, DS-S25 |
| 0,83 | 0,17 | 0,50 | 3 | 3 | 2 | 1 | 12 | DS-S10 |
| 0,83 | 0,17 | 0,83 | 3 | 0 | 0 | 0 | 0 | DS-S30 |
| 0,83 | 0,50 | 0,17 | 20 | 4 | 2 | 5 | 14 | – |
| 0,83 | 0,50 | 0,50 | 3 | 11 | 6 | 6 | 14 | – |
| 0,83 | 0,50 | 0,83 | 3 | 3 | 0 | 1 | 0 | – |
| 0,83 | 0,83 | 0,17 | 2 | 0 | 0 | 3 | 0 | DS-S18 |
| 0,83 | 0,83 | 0,50 | 2 | 7 | 1 | 6 | 2 | – |
| 0,83 | 0,83 | 0,83 | 2 | 3 | 0 | 2 | 0 | DS-S17 |

## 6. Verbleibende Unsicherheiten

- **Keine Höranalyse.** Formale Korrektheit ist geprüft, die musikalische Wirkung nicht.
- **Harmonische Belege sind dünn**; die Ketten sind E-Konstruktionen, deren Charakterbeschreibungen Interpretationen sind.
- **Die ♭9-Regel** ist eine Konvention der Prüfung. Einzelne bewusst gesetzte Reibungen (♭6 über Moll) sind deshalb ausdrücklich als F markiert.
- **Lückenplatzierung** prüft nur den ersten Ton eines TU-Ereignisses; die Hörbarkeitsprüfung bewertet zusätzlich jeden TU-Ton gegen klingende Sequencer.
- **Modulationskurven** sind abstrakt; ihre Wirkung hängt vollständig von der Zuordnung im Instrument ab.
- **XYZ-Bereiche** sind Einschätzungen und sollten nach dem Hören nachjustiert werden.
