# STROMSCORE – John Williams: Kanonische Gesamtfassung (Profil, Vokabular, Studien, Generatorpräferenzen)

Stand: 26.11.2026 · **kanonische Fassung**, ersetzt die Forschungsfassung vom selben Tag vollständig · Bezugstonart C · Zeitbasis 960 PPQ · zugehörig: `JW_Studien_Ereignisse_Kanonisch.csv`, `JW_Studien_MIDI_Kanonisch.zip` (40 MIDI-Dateien, je Rolle eine Spur), `JW_Qualitaetspruefung_und_Aenderungen.md` (gefundene Fehler, Korrekturen, Prüfergebnisse).

Bestand: 76 harmonische Wendungen, 48 Rhythmus-, 40 Bass-, 48 Motiv- und 24 Phrasenvorlagen, 30 Modellstudien (davon vier über 16 bzw. 32 Takte), 10 Übergangsstudien. Alle bisherigen IDs bleiben gültig; neue Einträge tragen fortlaufende IDs (JW-H58 ff., JW-R37 ff., JW-B31 ff., JW-M35 ff., JW-P19 ff., JW-S17 ff., JW-T09 ff.). Korrigierte Einträge sind in der Qualitätsprüfung aufgeführt.

## Inhalt

- **0** Lesehinweise, Evidenz und Notation
- **A** Musikwissenschaftliches Williams-Stilprofil
- **B** Harmonische Systeme und vertiefte Oktatonik-Untersuchung
- **C** Harmonisches Vokabular (JW-H01–H76)
- **D** Rhythmisches Vokabular (JW-R01–R48)
- **E** Bassvokabular (JW-B01–B40)
- **F** Motive (JW-M01–M48) und Phrasen (JW-P01–P24)
- **G** Koordinierte Modellstudien (JW-S01–S30), davon längere Entwicklungen
- **H** Übergangsstudien (JW-T01–T10)
- **I** Generatorpräferenzen (überarbeitet) und unabhängige Wirkung von X, Y, Z
- **J** XYZ-Abdeckungsmatrix
- **K** Vergleich mit John Barry
- **L** Technische Umsetzbarkeit (vorläufig)
- **M** Qualitätsprüfung und Forschungslücken
- **N** Quellenverzeichnis

## 0 Lesehinweise, Evidenz und Notation

**Evidenzklassen** (je Aussage getrennt für Verfahren und konkrete Vorlage): **N** durch eine konkrete, eingesehene Quelle nachgewiesen · **I** begründete musikalische Interpretation · **H** plausible, nicht ausreichend belegte Hypothese · **E** eigene Konstruktion für STROMSCORE. Alle konkreten Akkordfolgen, Raster, Basslinien, Motive, Phrasen und Studien sind **E**; die Klasse in der Kopfzeile jeder Vorlage betrifft das zugrunde liegende Verfahren. Quellenkürzel S1–S23 stehen in Abschnitt N, dort auch, was tatsächlich eingesehen und was nur bibliografisch identifiziert wurde.

**Was nicht vorlag.** Keine Partituren, keine Notenausschnitte, keine eigenen Höranalysen ganzer Filme. Die dichtesten Primärbelege sind Frank Lehmans Thematische Kataloge zu Star Wars (S1) und Indiana Jones (S2), seine Kadenzstudie (S3), eine Unterrichtsanalyse des E.T.-Flugthemas (S12) sowie Abstracts und Kursübersichten. Häufigkeitsangaben („oft“, „typisch“) stehen nur dort, wo eine Quelle sie macht; sonst wird nur „belegt in …“ gesagt.

**Notation.**

- Akkorde ASCII (`b` = ♭, `#` = ♯) in Bezugstonart C. `X|Y` = Polychord (X über Y), `{C Db E}` = ausdrücklich notierte Tonklassenmenge, `Cq` = Quartenakkord C–F–B♭. Tonklassen und Bass sind maschinell aus dem Symbol abgeleitet.
- Tonvorräte: **Okt-A** = C D♭ E♭ E F♯ G A B♭ (Halbton-Ganzton ab C), **Okt-B** = C♯ D E F G A♭ B♭ B (Halbton-Ganzton ab C♯), **Okt-C** = D E♭ F F♯ A♭ A B C (Halbton-Ganzton ab D), **Hex-C** = C E♭ E G A♭ B, **Ganzton-0** = C D E F♯ G♯ A♯, **Ungarisch-Moll** = C D E♭ F♯ G A♭ B; dazu Dur, Lydisch, Mixolydisch, Dorisch, Phrygisch, Äolisch, Moll harmonisch, „Moll gesamt“ (äolisch + 6 + 7), „Dur-Moll-Mischung“; **Pantriadisch** = Dreiklänge beliebiger Wurzel ohne gemeinsame Skala (nicht prüfbar).
- Raster: 4/4 und 2/2 = 16 Schritte pro Takt (Sechzehntel), 3/4 und 6/8 = 12, 5/4 = 20, 7/8 = 14, 3/2 = 24, **4/4T** = 12 Achteltriolen. `X` Einsatz mit Akzent, `x` Einsatz, `-` halten, `.` Pause, `|` Taktstrich. Bei 960 PPQ ist ein Sechzehntelschritt 240 Ticks, ein Triolenschritt 320 Ticks.
- Melodien: `Ton/Dauer` in Schritten (C4 = MIDI 60), `r` = Pause; jede Taktsumme ist geprüft.
- Rollenkürzel: LF Lange Fläche · KF Kurze Fläche · LB Langer Bass · KB Kurzer Bass · AR Arpeggio · TU Tupfer · ST Stich · GS Gegenstimme · HM Hauptmelodie.
- XYZ: X dunkel → hell, Y zurückhaltend → kraftvoll, Z stabil → unruhig, je 0–1. Region D/m/H, R/m/I, S/m/U mit Grenzen 0,40 und 0,60; für die Eckmatrix (J) gilt die Grenze 0,5. Alle Anker sind Setzungen [E], keine Messungen.

## A Musikwissenschaftliches Williams-Stilprofil

### A.1 Grundhaltung

Williams’ Musik für Star Wars, Indiana Jones und E.T. ist tonal verankert, aber selten funktional im engen Sinn. Lehman beschreibt den „Hollywood-Klang“ als Wirkung von Chromatik, die Zentrumsbezug, Diatonik und Funktionalität der Dreiklänge aufhebt, und rückt die „pantriadische“ Chromatik, also Dreiklänge beliebiger Wurzel in nicht-funktionaler Folge, ins Zentrum des Staunens (S4 über Rezension und Verlagstext) [N]. Für die Generatorlogik heißt das: Grundmaterial bleibt der Dreiklang, die Fortschreitung ist das Stilmerkmal.

Vier Schichten lassen sich unterscheiden, die in den Quellen konkret belegt sind:

| Schicht | Belege | Wirkungsfeld |
|---|---|---|
| Modale Dur-Färbung: mixolydisches ♭VII, lydisches II♯ | Hauptthema „mit mixolydischen und quartalen Einfärbungen“, Yoda- und Rose-Thema mit lydischem II♯, „Victory Fanfare“ als „lehrbuchhaft lydisch“ (S1); Schneller ordnet ♭VII dem Heroischen, II♯ der Magie, dem Staunen und dem Flug zu (S6) [N] | Heroik, Abenteuer, Staunen |
| Chromatische Mediantik und Dreiklangsketten | Tonart rückt um eine chromatische große Terz (Happy Landings), chromatisch modulierende Kadenzen in Harry Potter, E.T., Jurassic Park (S1, S3) [N] | Staunen, Triumph, Epik |
| Mollklänge in symmetrischen Abständen | Imperator: Mollklänge in chromatischen Kleinterzen oder Tritoni; Imperial March: Hexatonik, i↔♭vi als Leitharmonie; Map-Thema Cm↔F♯m; Jabba: chromatische Transformationen zwischen Molldreiklängen (S1) [N] | Bedrohung, dunkle Macht, Geheimnis |
| Symmetrische Skalen und Polychorde in Action | „Octatonic Battle Motif“ (Yavin), „Quartal Canon“, „Martial Chords“ (Holst-Polychorde), Hoth 3m3 mit oktatonischem Bass- und Akkordostinato, oktatonischer Trompetenmelodie und atonalen Synkopenpassagen (S1); Richards nennt Oktatonik, Hexatonik und Ungarisch-Moll als die drei Hauptskalen klassischer Actionmusik, dazu Dissonanzbässe und Polychorde (S10) [N] | Action, Kampf, höchste Unruhe |

### A.2 Harmonische Bewegung

- **Lange Liegeklänge** sind belegt: Hauptthema-Fortsetzung „harmonisch statisch, meist über Dominantpedal“, Rebellenfanfare „oft über statischem Orgelpunkt“, Han-und-Leia-Thema „oft mit Tonikapedal“ (S1) [N]. Liegeklänge sind also auch bei Williams Grundvokabular, aber sie tragen darüber bewegte Harmonik oder Melodik.
- **Wechsel einzelner Stimmen im stabilen Klang:** E.T.-Flugthema mit inneren Tonika- und Dominantpedalen, Oktavsprung-Pedalen, Zusatztonklängen C2/G7sus4 (S12) [N]; Hoth endet mit „lydischem Nachglühen“ (S1) [N].
- **Plötzliche Kontraste:** Kontrastteile mit Grundtönen im Terzabstand, nicht-funktionale chromatische Bassverbindungen, verminderte Septakkorde statt V (S12) [N]; chromatisch modulierende Kadenzauflösung als eigener Typ (S3) [N].
- **Mehrere Wechsel pro Takt** in Action: die Quellen nennen dies nicht als Zahl; die Vorlagen JW-H48 und JW-H53 setzen es als [I] um.
- **Sequenzen:** „Rising sequence that ends on a dissonant chord“ und Gegenbewegung M2–M3 (Hoth n, t), Triolensequenzen (S1) [N].

### A.3 Rhythmus, Metrum, Bass

Belegt sind Marschrhythmen („Martial Rhythm“), synkopierte Militärfiguren, ein „Heavy mixed meter ostinato“ (Asymmetrical Martial Ostinato, Episode I), Repetitionstriolen und „chugging chromatic string texture“ (Hoth x, y), wechselnde Akzente und Metren in der TIE-Fighter-Szene (S1, S21) [N]; im E.T.-Flugthema 2/2 mit eingeschobenen 3/2-Takten, Achtelostinato, Kreuzrhythmen und Triolen nur in der Coda (S12) [N]. Der Bass ist eigenständig: tiefes Klavier als Hauptostinato (Hoth i), synkopierte Basslinie mit chromatischer Aktivität darüber (Hoth u), Gegenbewegung (Hoth t), Dissonanzbässe (S1, S10) [N]. Pedale sind eine Möglichkeit unter vielen – genau das unterscheidet das Profil von einer verpflichtenden Pedal-Logik (Abschnitt 16 des Auftrags).

### A.4 Zentrale Forschungsfrage: Musik ohne Hauptmelodie

Die Underscore-Cues zwischen den Themen arbeiten nach den Quellen mit fünf Mitteln, die alle ohne Hauptmelodie wirken:

1. **Ostinato als Träger** (Hoth i, l; Imperial Troops Ostinato; Escape Ostinato; Battle of Naboo Ostinato, S1) [N]. Im Generator: Bass- oder Akkordostinato ist die Hauptrolle, nicht Begleitung.
2. **Harmonik als Ereignis**: der Klangwechsel selbst ist die Mitteilung (Medianten, Tritonus-Mollwechsel, Dissonanzbass) [N]. Bei abgeschalteter Melodie muss der harmonische Rhythmus deshalb hörbar bleiben (Studien JW-S03, S04, S12).
3. **Akkordrepetition mit wechselnder Akzentlage** (Repetitionsakkord-Ostinato, Martial Chords) [N].
4. **Fragmentierte Motive in Nebenrollen** (Gegenstimme, Tupfer, Stich): Incidental Motifs wie Chromatic Knell, Tremulous Double Neighbor, Semitonal Slip sind kurze Zellen, keine Themen (S1) [N].
5. **Registerbewegung und Schichtwechsel**: Rollen lösen einander ab statt sich zu addieren (Interpretation [I], umgesetzt in allen Studien; siehe Rollenverläufe).

Alle 16 Modellstudien sind so gebaut, dass sie ohne Hauptmelodie vollständig sind; neun davon haben gar keine.

### A.5 Rollenkoordination und Dramaturgie

| Frage des Auftrags | Antwort für das Williams-Profil | Evidenz |
|---|---|---|
| Wann übernimmt der Bass den Antrieb? | Bevorzugt bei hohem Y und Z, wenn die Harmonie pro Takt oder schneller wechselt; das Arpeggio wird dann entlastet (leiser, höher, lückenhaft), muss aber nicht schweigen (JW-S13 ohne, JW-S19 und JW-S20 mit Arpeggio). | Hoth i (tiefes Klavier als Hauptostinato) [N], Präferenz [I] |
| Wann übernehmen kurze Akkorde die Bewegung? | Bei statischer Harmonie mit Spannung (oktatonischer Liegeklang, Marsch): Repetitionsakkorde oder Marschrhythmus (JW-S02, JW-S12). | Hoth l [N] |
| Wann schweigt das Arpeggio? | Es kann pausieren, wenn Bass oder Kurze Fläche den Puls schon tragen (Marsch, Trauer, Bassmotor); das ist eine Gewichtung, keine Sperre. | [I] |
| Spannung durch Harmonie statt Noten? | Steigender oktatonischer Bass unter gleichbleibendem Rhythmus (JW-S12 T1–4), Dissonanzbass unter statischem Moll (JW-S04). | Richards (Dissonanzbass) [N], Umsetzung [E] |
| Intensität durch Schichtung? | Rollen kommen hinzu, ohne dass einzelne dichter werden (JW-T04: Fläche, Bass, Kurze Fläche nacheinander). | [I] |
| Überladung vermeiden? | Über Lagentrennung und Ablösung statt über eine Höchstzahl: Tupfer und Arpeggio teilen sich ungern dieselbe Lage; Melodie und Gegenstimme wechseln sich bevorzugt ab. In den Studien setzen höchstens 6 Rollen pro Takt neu ein – das ist ein Ergebnis, keine Vorgabe. | [E] |
| Kontinuität bei Stimmungswechsel? | Mindestens ein Element bleibt: Pedalton, gemeinsamer Ton, Motivkontur oder Rolle (Übergänge JW-T01–T08). | Leitmotivtransformation (S1, S17) [N], Regel [E] |

### A.6 Motivik

Lehmans Leitmotiv-Kriterien (Unverwechselbarkeit, Wiederkehr in mehr als drei Cues, Variation, Absicht; S1) sind für das Motivgedächtnis direkt brauchbar. Belegte Transformationen: Moduswechsel (Hauptthema in Yavin von Dur/Mixolydisch nach Moll/Phrygisch), Umharmonisierung, Fragmentierung, Kanon (Hoth p, q), Sequenz (S1) [N]. Belegte Konturtypen: Richards’ „struggle“-Kontur (auf–ab–höher), Zielton als höchster oder letzter Ton, Zielton durch höheren Nachbarton verschoben (S11) [N]. Belegte Intervallzellen: verminderte Terz als „Bösewicht-Intervall“, Repetition plus kleine Terz, lydischer Doppelnachbar 6→♯4→5, ♭6–5–♯4, pentatonische Melodik (S1, S2) [N].

## B Harmonische Systeme und vertiefte Oktatonik-Untersuchung

### B.1 Übersicht der Systeme

Unterschieden werden **Tonvorrat** (welche Töne erlaubt sind), **Zentrum** (welcher Ton als Ruhepunkt gilt), **melodische Skala** (aus welchen Tönen Linien gebildet werden) und **Akkordfunktion** (was ein Klang im Verlauf tut). Ein Tonvorrat legt keine Stimmung fest; die Wirkung entsteht aus Register, Rhythmus und Kontext.

| System | Tonvorrat | Belegt bei Williams | Typische Funktion im Vokabular | Vorlagen |
|---|---|---|---|---|
| Dur | — | Jurassic-Park-Thema fast nur I, IV, V (S11) | Wärme, Heimkehr | JW-H21, JW-H28, JW-H35, JW-H36, JW-H75 |
| Lydisch | — | II♯ (Yoda, Rose), Victory Fanfare, Lydian Heroics, Lydian Tag, Hoth z (S1); Schneller: Magie/Flug (S6) | Staunen, Flug, Nachglühen | JW-H03, JW-H04, JW-H05, JW-H62 |
| Mixolydisch | — | Hauptthema mixolydisch/quartal (S1); ♭VII heroisch (S6) | Heroik, Aufbruch | JW-H01, JW-H27, JW-H65 |
| Dorisch | — | nicht ausdrücklich; Gral-Thema „modal flexibel“ (S2) | Mystik [I] | JW-H11, JW-H42 |
| Phrygisch | — | Imperials ♭2; Hauptthema in Yavin phrygisch umgefärbt (S1) | Lauern, Kampf in Moll | JW-H41, JW-H53 |
| Äolisch | — | Yavin-Moll (S1) | Heroischer Kampf in Moll | JW-H53, JW-H56, JW-H57 |
| Okt-A | C D♭ E♭ E F♯ G A B♭ (Halbton-Ganzton ab C) | Battle Motif, Hoth i/l/p, Boba Fett, It’s a Trap, Space Battle Vamp, Nazi-Motiv (S1, S2) | Spannung, Action, Bedrohung | JW-H12, JW-H14, JW-H15, JW-H16, JW-H17, JW-H18, JW-H19, JW-H20, JW-H21, JW-H22, JW-H46, JW-H47, JW-H48, JW-H54, JW-H74 |
| Hex-C | C E♭ E G A♭ B | Imperial March 10f–g, Droids, Anakin (hexatonischer Pol), Trauermarsch (S1) | Unheimliches, dunkle Magie | JW-H13, JW-H23, JW-H24, JW-H25, JW-H29, JW-H45, JW-H50, JW-H66 |
| Ganzton-0 | C D E F♯ G♯ A♯ | nicht belegt | Magie, Traum [H] | JW-H26 |
| Ungarisch-Moll | C D E♭ F♯ G A♭ B | als Action-Skala bei Richards (S10) | exotische Bedrohung [I] | JW-H43 |
| Pantriadisch | — | Kernbegriff bei Lehman (S4) | Staunen, Wanderung, Humor | JW-H08, JW-H09, JW-H30, JW-H37, JW-H40, JW-H49, JW-H51, JW-H52, JW-H58, JW-H60, JW-H61, JW-H63, JW-H64, JW-H67, JW-H68, JW-H70, JW-H72, JW-H76 |

Weitere verwendete Tonvorräte: Dur-Moll-Mischung (JW-H02, JW-H06, JW-H07, JW-H10, JW-H31, JW-H32, JW-H33, JW-H38, JW-H55), Moll gesamt/harmonisch (JW-H34, JW-H44, JW-H53, JW-H69), Chromatisch (JW-H39, JW-H71, JW-H73, JW-H75), Okt-B/Okt-C nur in Wechseln (JW-H20, JW-H48). **Bitonalität/Polytonalität** ist als Polychord belegt (Death Star „polychordal“, Martial Chords, Revelations, Funeral; S1) [N]; eine durchgehende Bitonalität zweier Tonarten ist in den eingesehenen Quellen nicht belegt.

### B.2 Oktatonik: was belegt ist

| Stelle | Befund (Quelle) | Evidenz |
|---|---|---|
| Battle of Hoth, 3m3 „Snow Battle“ | Cue ohne Leitmotive, dicht mit eigenem Material: Hauptostinato im tiefen Klavier mit „oktatonischer Disposition, die es mit viel Material der Schlacht teilt“ (i); „oktatonisches Repetitionsakkord-Ostinato“, verwandt mit dem Dark-Side-Ostinato (l); „oktatonische Melodie für Trompeten“, von Posaunen im Kanon beantwortet (p); atonale, stark synkopierte Passagen (o); ansteigende Sequenz mit dissonantem Schlussakkord (n); Gegenbewegung M2–M3 (t) (S1) | N |
| Hoth, weitere | Im Podcast-Index zur Hoth-Sequenz genannt: Tonklassenmengen 4-19, 6-Z19, 5-32, 8-28 (= oktatonischer Vorrat) und 6-20 (= hexatonischer Vorrat), „Alpha chords“ (S13; nur Episodenindex, Zuordnung zu Takten unbekannt) | N |
| Battle of Yavin | „Octatonic Battle Motif“ als markantestes von mehreren Kampfmotiven, später in Sail Barge Battle und Superstructure Chase verarbeitet; dazu Quartal Canon, Syncopated Military Figure, Holst-Polychorde am Höhepunkt (S1) | N |
| Episode IV, Imperials | Repetition + kleine Terz, ♭2 „deutet Phrygisch, Oktatonik an“, oktatonische Implikation durch Dreiklänge im Kleinterzabstand (S1) | N |
| Episode IV, Major Trouble | chromatisch verwandte Durklänge harmonisieren eine oktatonische Melodie über dissonanten Bässen (S1) | N |
| Episode V, Boba Fett | vollständig oktatonischer Tonvorrat, fast nur kleine Parallelterzen (S1) | N |
| Episode VI | „It’s a Trap“-A-Motiv nervös oktatonisch mit verminderten Dreiklängen; Space Battle Vamp synkopiert oktatonisch in kleinen Parallelterzen; Scout Walkers „oktatonische Geste“ (S1) | N |
| Episode VIII | „Whirling Octatonicism“ in der Schlacht von Crait (S1) | N |
| Indiana Jones | Nazi-Motiv in „oktatonischer Konstruktion“ (S2); Richards’ Studie zu „In the Jungle“ (Raiders) behandelt oktatonische Akkorde (Ankündigung, Inhalt nicht eingesehen) | N |
| Desert Chase | **nicht verifiziert.** Lehmans IJ-Katalog führt nur Transkriptionen (Nazi Convoy, Climactic Ostinato) und verweist für die Analyse auf McCauley 2018 (nicht eingesehen) (S2, S23). Eine oktatonische Struktur von Desert Chase wird hier deshalb nicht behauptet. | N |

### B.3 Struktur der drei oktatonischen Vorräte

Jeder oktatonische Vorrat ist unter Transposition um eine kleine Terz invariant. Daraus folgt alles Weitere [N, Musiktheorie].

| Vorrat | Töne | Durdreiklänge | Molldreiklänge | Dominantseptakkorde | verminderte Septakkorde |
|---|---|---|---|---|---|
| Okt-A | C D♭ E♭ E F♯ G A B♭ (Halbton-Ganzton ab C) | C, E♭, F♯, A | Cm, E♭m, F♯m, Am | C7, E♭7, F♯7, A7 | {C E♭ F♯ A} und {D♭ E G B♭} |
| Okt-B | C♯ D E F G A♭ B♭ B (Halbton-Ganzton ab C♯) | D♭, E, G, B♭ | D♭m, Em, Gm, B♭m | D♭7, E7, G7, B♭7 | {D♭ E G B♭} und {D F A♭ B} |
| Okt-C | D E♭ F F♯ A♭ A B C (Halbton-Ganzton ab D) | D, F, A♭, B | Dm, Fm, A♭m, Bm | D7, F7, A♭7, B7 | {C E♭ F♯ A} und {D F A♭ B} |

- **Gemeinsamer verminderter Septakkord als Gelenk:** Okt-A ∩ Okt-C = {C E♭ F♯ A}, Okt-A ∩ Okt-B = {D♭ E G B♭}, Okt-B ∩ Okt-C = {D F A♭ B}. Jeder Wechsel zwischen zwei Vorräten kann über genau einen gemeinsamen verminderten Septakkord laufen (JW-H20) [N als Mengenlehre, Anwendung E].
- **Akkordstrukturen innerhalb eines Vorrats:** vier Dur- und vier Molldreiklänge im Kleinterzabstand, vier Dominantseptakkorde, 7♭9-Klänge, m(add♯4) (= C E♭ F♯ G), (014)- und (0134)-Zellen (C D♭ E / C D♭ E♭ E). Polychorde aus zwei Dreiklängen im Tritonusabstand (F♯|C) oder Kleinterzabstand (E♭|A) bleiben im Vorrat (JW-H22).
- **Fortschreitungen:** (a) ein Klang, Bewegung nur rhythmisch (JW-H18); (b) Tritonuspendel (JW-H14, H15); (c) Kleinterzzyklus (JW-H12, H16); (d) Durklang über Bass einen Halbton höher – alle Basstöne bleiben im Vorrat (JW-H17); (e) Dreiklänge über einem oktatonischen Basslauf (JW-H19).
- **Bass:** Pedal auf einem Vorratston (C unter Okt-A); Kleinterzsprünge C–E♭–F♯–A (JW-B08); Skalenlauf (JW-B07); Halbton-Dissonanzbass (JW-B09).
- **Begleitung und Ostinato:** Repetitionsakkord (JW-R08), 3+3+2-Sechzehntel im Bass (JW-R07), synkopierte Kleinterzparallelen (JW-M11).
- **Melodische Zellen:** Repetition + kleine Terz (JW-M05), verminderte Arpeggien mit Halbtonversatz (JW-M12), oktatonischer Lauf (JW-M32), Linie über Liegeklang (JW-P06).
- **Koordination:** Alle Rollen im selben Vorrat; Gegenstimme darf Skalentöne außerhalb des Akkords verwenden (Durchgang), Bass und Flächen bleiben Akkord- oder Vorratstöne. In den Studien JW-S04, S12, S13 ist dies maschinell geprüft (Abschnitt M).
- **Wechsel tonal ↔ oktatonisch:** über einen Dreiklang, der in beiden liegt (C-Dur gehört zu C-Dur und Okt-A), oder über den verminderten Septakkord (JW-H21). Rückweg gleich.

### B.4 Oktatonik nach Intensität und Unruhe

| Stufe | Z | Y | Verfahren | Vorlagen |
|---|---|---|---|---|
| 1 Färbung | 0,45–0,60 | 0,2–0,5 | Ein oktatonischer Liegeklang oder ♭2/Kleinterzfärbung über Moll; keine Skalenläufe | JW-H41, JW-H54, JW-M05 |
| 2 Pendel | 0,55–0,70 | 0,3–0,6 | Tritonus- oder Kleinterzpendel in langen Werten | JW-H14, JW-H12, JW-H15 |
| 3 Ostinato | 0,60–0,75 | 0,5–0,8 | Liegeklang + Repetitionsakkorde, Bass 3+3+2, Melodie aus dem Vorrat | JW-H18, JW-R07, JW-R08, JW-P06 |
| 4 Bewegter Bass | 0,65–0,80 | 0,6–0,85 | Klangwechsel pro Takt, Basslauf oder Dissonanzbass | JW-H16, JW-H17, JW-H19 |
| 5 Vorratswechsel | 0,75–0,90 | 0,7–0,9 | Wechsel über verminderten Septakkord | JW-H20 |
| 6 Zuspitzung | > 0,90 | > 0,85 | Zwei Vorräte im Halbtaktwechsel oder (014)-Zellen; alle Schichten auf gemeinsamem Akzentgerüst; darf so lange bestehen, wie die Stimmung gewählt ist | JW-H47, JW-H48, JW-S16 |

**Keine Quote.** Oktatonik soll die dunklen und actionreichen Bereiche nicht allein füllen. Das wird über Vielfalt im Bestand erreicht, nicht über eine Begrenzung: in denselben Regionen stehen hexatonische (JW-H13, H23, H45, H66, H68), modale (JW-H41, H53, H56, H69), polychordale (JW-H22, H71), planende (JW-H58, H64, H70), pantriadische (JW-H67, H76) und Ungarisch-Moll-Vorlagen (JW-H43). Leise Oktatonik (Stufe 1–2 und JW-H74, JW-S23) ist ausdrücklich Teil des Bestands.

### B.5 Hexatonik, Ganzton, Medianten, neo-riemannsche Beziehungen

- **Hexatonisch (Hex-C = C E♭ E G A♭ B):** enthält C, Cm, E, Em, A♭, A♭m; der hexatonische Pol C ↔ A♭m ist bei Lehman für Anakin und den Trauermarsch belegt (S1) [N]. P/L-Zyklus C–Cm–A♭–A♭m–E–Em (JW-H25) [N als Theorie, Anwendung I].
- **Chromatische Medianten:** Großterzrückung (JW-H08, H29, H49), CMCR (JW-H09), Kleinterzbeziehungen in Moll (JW-H12). Lehman 2013 typisiert die chromatisch modulierenden Kadenzauflösungen nach Grundtonabstand (Typen 0–IV) (S3) [N].
- **Plagal- und Subtonikalkadenzen:** gemischte Plagalkadenz („Hollywood Cadence“), Subtonikal-Halbschluss ♭VII–V im Star-Wars-Hauptthema (S3) [N] → JW-H02, JW-H10.
- **Tritonusbeziehungen:** Dur–Dur mit Weltraumbezug (Murphy 2006, S7), Moll–Moll mit tödlicher Gefahr (Murphy, zitiert bei Schneller, S6) [N]; für Williams als Einzelbelege nur das Map-Thema (S1).
- **Ganztonharmonik:** in den eingesehenen Quellen kein Williams-Beleg; JW-H26 und JW-M31 sind als [H] gekennzeichnet und sollten im Profil niedrig gewichtet werden.

### B.6 Ergänzungen aus dem zweiten Durchgang (Verfahren → Vorlagen)

| Verfahren | Beleg | Evidenz | umgesetzt in |
|---|---|---|---|
| Leise Oktatonik (Terzparallelen in tiefen Holzbläsern, Dreiklangspaar im Kleinterzabstand) | Boba Fett, Imperials, Nazi-Motiv (S24, S2); Set 5-32 im Snow Battle (S35, sekundär) | N / I | JW-H74, JW-M42, JW-B40, JW-S23, JW-T10 |
| Dissonanzbass unter Dur (beweglich) und unter Planing | Jawas 7b, TIE-Fighter-Bass aus Nicht-Akkordtönen, Major Trouble (S24) | N | JW-H58, JW-H59, JW-B31, JW-B32, JW-S17, JW-S19, JW-S30 |
| Parallele Dreiklangsführung (Planing) über Pedal, mit Großterzrückung | Happy Landings, Rebel Fanfare, Trumpet Cascade, Ewoks 19b (S24) | N | JW-H58, JW-H60, JW-H64, JW-H70, JW-S20 |
| Planing erster Umkehrungen in Moll | Darth Maul (S24) | N | JW-H70 |
| Lydische I↔II-Schleife; Maj7-Mixolydisch ohne Dominante | Victory Fanfare, Cloud City (S24) | N | JW-H62, JW-H63, JW-S19 |
| Unregelmäßige Achtelgruppen, Hemiole 6/8 gegen 3/4 | TIE Fighter, Finn/Pursuit (S24); Poe/Heroics (S30) | N | JW-R37, JW-R38, JW-R44, JW-S19, JW-S30 |
| Tritonusoszillation von Mollklängen, stufenweiser Abstieg, Kleinterzkette zur überhöhten Kadenz | Lade-Thema, Map Room: Dawn (S25) | N | JW-H67, JW-H76, JW-S22 |
| Choral/Chant mit langsamem harmonischem Rhythmus; hexatonisch-polares Polychord | Trauermarsch, Lament, Battle of the Heroes (S24) | N | JW-H68, JW-R46, JW-M43 |
| Dies-irae-Typen (x, y mit erhöhter 7. Stufe, Umkehrung) | Schneller, Émergences 2025 (S28) | N | JW-H69, JW-B35, JW-M44, JW-M45, JW-S21, JW-S26 |
| Ostinato, das sich den Akkorden anpasst (lang-lang-kurz-kurz-lang) | Duel of the Fates 25b (S24) | N | JW-R43, JW-B34 |
| Staccato-Kontrapunkt, isolierte Einwürfe, Stille, synkopierte 6/8-Figur | E.T.: Halloween, New Home, Bait for E.T., The Closet (S26) | N | JW-R39, JW-R40, JW-R41, JW-R47, JW-H73, JW-M35, JW-M36 |
| Arpeggien mit genau einem Fremdton, stufenweise versetzt | Mystery/Kamino (S24) | N | JW-H72, JW-M47, JW-P22, JW-S24 |
| Halbton-Mollpaar als überlagerter Klang | Sith-Dolch, Map-Thema (S24) | N | JW-H71, JW-M48, JW-S28 |
| Cluster öffnet sich zu Dur | Close Encounters (S29, nur Auszug) | N | JW-H75, JW-T09 |
| Gleiches Material in zwei Intensitätsstufen (Register, Besetzung, Dynamik) | Keys’ Theme in E.T., Boba Fett nur in Fagotten (S26, S24) | N / I | JW-S29, Präferenz I.0 |
| Themenlänge im Mittel 8,8 Takte; Varianten statt Austausch | Star-Wars-Themenkorpus (S27); Richards 2018 (über Zitat) | N | JW-P24 (6 Takte), JW-S25–S28 |

Begriffe ohne öffentliche Definition (Richards’ „Alpha chord“, „action extensions“) werden nicht als Akkorddefinition verwendet; JW-H74 nennt nur die mögliche Verbindung als Hypothese.

## C Harmonisches Vokabular (76 Vorlagen)

Alle Folgen 8 Takte; Tonklassen und Bass maschinell aus dem Symbol; Tonvorrat je Akkord geprüft. Varianten, die den Vorrat bewusst verlassen, sind mit [systemfremd] markiert.

### C.1 Bestand (JW-H01–H57, geprüft und teilweise korrigiert)

#### JW-H01 · Mixolydische Fanfarenachse

- **XYZ-Anker:** 0,80 / 0,75 / 0,30 (HIS) · **Taktart:** 4/4 · **Tonvorrat:** Mixolydisch · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 2 | T1 | C E G | C | Mixolydisch |
| 2 | `Bb` | 1 | T3 | B♭ D F | B♭ | Mixolydisch |
| 3 | `F` | 1 | T4 | F A C | F | Mixolydisch |
| 4 | `C` | 2 | T5 | C E G | C | Mixolydisch |
| 5 | `Gsus4` | 1 | T7 | G C D | G | Mixolydisch |
| 6 | `C` | 1 | T8 | C E G | C | Mixolydisch |

- **Wirkung:** Offene, heroische Helligkeit ohne Leittonzwang; der ♭VII-Klang hält die Musik in Bewegung.
- **Harmonisches Zentrum:** C mixolydisch
- **Bassführung:** Grundtöne C–B♭–F–C, Takt 7 G als Quintbass; Bass darf B♭→F als Quartfall springen.
- **Begleitformen:** JW-R01, JW-R31, JW-R10
- **Variation:** B♭ durch B♭sus2 ersetzen; Takt 7 als Gsus4→G halbieren.
- **Williams-Verfahren:** Mixolydische Subtonika als Heldenfarbe; Hauptthema mit mixolydischen und quartalen Einfärbungen. Quellen: S6, S1.
- **Stimmungen:** Heroik, Abenteuer

#### JW-H02 · Subtonischer Halbschluss (♭VII–V)

- **XYZ-Anker:** 0,75 / 0,70 / 0,40 (HIm) · **Taktart:** 4/4 · **Tonvorrat:** Dur-Moll-Mischung · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 2 | T1 | C E G | C | Dur-Moll-Mischung |
| 2 | `F` | 1 | T3 | F A C | F | Dur-Moll-Mischung |
| 3 | `Bb` | 1 | T4 | B♭ D F | B♭ | Dur-Moll-Mischung |
| 4 | `C` | 2 | T5 | C E G | C | Dur-Moll-Mischung |
| 5 | `Bb` | 1 | T7 | B♭ D F | B♭ | Dur-Moll-Mischung |
| 6 | `G` | 1 | T8 | G B D | G | Dur-Moll-Mischung |

- **Wirkung:** Phrase endet offen auf V, über den Umweg ♭VII; klingt nach Aufbruch, nicht nach Schluss.
- **Harmonisches Zentrum:** C, Halbschluss auf G
- **Bassführung:** Grundtöne; letzter Takt G im Bass als Ziel.
- **Begleitformen:** JW-R31, JW-R01
- **Variation:** Takt 8 G7sus4→G; Fortsetzung mit JW-H01 oder JW-H08.
- **Williams-Verfahren:** Lehmans „subtonic half cadence“ (♭VII–V), für das Star-Wars-Hauptthema nachgewiesen. Quellen: S3.
- **Stimmungen:** Abenteuer, Heroik

#### JW-H03 · Lydische Schwebe (II♯ über Tonikapedal)

- **XYZ-Anker:** 0,85 / 0,30 / 0,25 (HRS) · **Taktart:** 4/4 · **Tonvorrat:** Lydisch · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 2 | T1 | C E G | C | Lydisch |
| 2 | `D/C` | 2 | T3 | C D F♯ A | C | Lydisch |
| 3 | `C` | 2 | T5 | C E G | C | Lydisch |
| 4 | `D/C` | 1 | T7 | C D F♯ A | C | Lydisch |
| 5 | `Cmaj7` | 1 | T8 | C E G B | C | Lydisch |

- **Wirkung:** Staunen, Magie, Schweben; der D-Dur-Klang über C färbt, ohne zu modulieren.
- **Harmonisches Zentrum:** C lydisch
- **Bassführung:** Pedal C über alle 8 Takte.
- **Begleitformen:** JW-R14, JW-R12, JW-R15
- **Variation:** D/C als Dadd9/C; im zweiten Durchgang Em/C statt D/C.
- **Williams-Verfahren:** Lydische Supertonika (II♯) als Zeichen für Magie, Staunen und Flug; Yoda- und Rose-Thema mit lydischem II♯. Quellen: S6, S1.
- **Stimmungen:** Staunen, Magie, Wärme

#### JW-H04 · Lydischer Aufschwung

- **XYZ-Anker:** 0,90 / 0,65 / 0,35 (HIS) · **Taktart:** 4/4 · **Tonvorrat:** Lydisch · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 2 | T1 | C E G | C | Lydisch |
| 2 | `D` | 1 | T3 | D F♯ A | D | Lydisch |
| 3 | `Em` | 1 | T4 | E G B | E | Lydisch |
| 4 | `Am` | 1 | T5 | A C E | A | Lydisch |
| 5 | `D` | 1 | T6 | D F♯ A | D | Lydisch |
| 6 | `C` | 1 | T7 | C E G | C | Lydisch |
| 7 | `C` | 1 | T8 | C E G | C | Lydisch |

- **Wirkung:** Aufsteigende Helligkeit, jugendlicher Mut; jeder zweite Klang enthält F♯.
- **Harmonisches Zentrum:** C lydisch
- **Bassführung:** Bass steigt C–D–E, fällt A–D, Ziel C; Takt 7–8 Pedal C.
- **Begleitformen:** JW-R03, JW-R14, JW-R31
- **Variation:** D durch D/F♯ ersetzen (Bass stufenweise C–D–E–F♯).
- **Williams-Verfahren:** Lydische Heroik (Incidental Motif „Lydian Heroics“, Anakin-Material); hier als Akkordfolge abstrahiert. Quellen: S1, S6.
- **Stimmungen:** Abenteuer, Staunen, Heroik

#### JW-H05 · Lydisches Nachglühen

- **XYZ-Anker:** 0,85 / 0,15 / 0,20 (HRS) · **Taktart:** 4/4 · **Tonvorrat:** Lydisch · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 2 | T1 | C E G | C | Lydisch |
| 2 | `Cmaj7#11` | 2 | T3 | C E G B F♯ | C | Lydisch |
| 3 | `C6/9` | 2 | T5 | C E G A D | C | Lydisch |
| 4 | `Cmaj7` | 1 | T7 | C E G B | C | Lydisch |
| 5 | `C` | 1 | T8 | C E G | C | Lydisch |

- **Wirkung:** Ruhiger Ausklang nach einem Höhepunkt; ein einziger Klang, nur eine Innenstimme bewegt sich.
- **Harmonisches Zentrum:** C lydisch
- **Bassführung:** Pedal C; keine Bassbewegung.
- **Begleitformen:** JW-R12, JW-R14
- **Variation:** F♯ als Haltenote der Gegenstimme statt im Akkord.
- **Williams-Verfahren:** Hoth-Sequenz endet mit „Lydian afterglow“ (Lehman, Motiv 4m2 z); Veränderung einzelner Stimmen im stabilen Akkord. Quellen: S1.
- **Stimmungen:** Wärme, Staunen, Epische Weite

#### JW-H06 · Tonikapedal mit Mischklängen

- **XYZ-Anker:** 0,65 / 0,35 / 0,20 (HRS) · **Taktart:** 4/4 · **Tonvorrat:** Dur-Moll-Mischung · **Kategorie:** universell · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 2 | T1 | C E G | C | Dur-Moll-Mischung |
| 2 | `F/C` | 1 | T3 | C F A | C | Dur-Moll-Mischung |
| 3 | `Fm/C` | 1 | T4 | C F A♭ | C | Dur-Moll-Mischung |
| 4 | `C` | 2 | T5 | C E G | C | Dur-Moll-Mischung |
| 5 | `Ab/C` | 1 | T7 | C A♭ E♭ | C | Dur-Moll-Mischung |
| 6 | `C` | 1 | T8 | C E G | C | Dur-Moll-Mischung |

- **Wirkung:** Geborgenheit mit leichtem Schatten; Moll-Subdominante und ♭VI über liegendem C.
- **Harmonisches Zentrum:** C
- **Bassführung:** Pedal C (lang oder als Oktavpendel).
- **Begleitformen:** JW-R12, JW-R16, JW-R14
- **Variation:** Fm/C als Fm6/C; Ab/C als Abmaj7/C.
- **Williams-Verfahren:** Liebesthema mit Tonika-Orgelpunkt (Han and Leia), Happy Landings über statischem Tonika-Pedal. Quellen: S1.
- **Stimmungen:** Wärme, Romantik

#### JW-H07 · Dominantpedal mit wechselnden Oberklängen

- **XYZ-Anker:** 0,60 / 0,60 / 0,45 (mmm) · **Taktart:** 4/4 · **Tonvorrat:** Dur-Moll-Mischung · **Kategorie:** universell · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C/G` | 2 | T1 | G C E | G | Dur-Moll-Mischung |
| 2 | `F/G` | 2 | T3 | G F A C | G | Dur-Moll-Mischung |
| 3 | `Eb/G` | 1 | T5 | G E♭ B♭ | G | Dur-Moll-Mischung |
| 4 | `F/G` | 1 | T6 | G F A C | G | Dur-Moll-Mischung |
| 5 | `G` | 2 | T7 | G B D | G | Dur-Moll-Mischung |

- **Wirkung:** Erwartung, Anlauf vor einem Höhepunkt; der Bass verspricht eine Auflösung, die noch nicht kommt.
- **Harmonisches Zentrum:** C (Halbschluss)
- **Bassführung:** Pedal G über alle Takte; Schluss offen.
- **Begleitformen:** JW-R03, JW-R29, JW-R13
- **Variation:** Takt 5–6 halbtaktig Eb/G–F/G; danach JW-H01.
- **Williams-Verfahren:** Fortsetzung des Hauptthemas harmonisch statisch über Dominantpedal (Lehman 1b). Quellen: S1.
- **Stimmungen:** Dramatische Spannung, Abenteuer

#### JW-H08 · Chromatische Großterz-Rückung

- **XYZ-Anker:** 0,80 / 0,65 / 0,40 (HIm) · **Taktart:** 4/4 · **Tonvorrat:** Pantriadisch · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 2 | T1 | C E G | C | Pantriadisch |
| 2 | `G` | 1 | T3 | G B D | G | Pantriadisch |
| 3 | `C` | 1 | T4 | C E G | C | Pantriadisch |
| 4 | `E` | 2 | T5 | E A♭ B | E | Pantriadisch |
| 5 | `B` | 1 | T7 | B E♭ F♯ | B | Pantriadisch |
| 6 | `E` | 1 | T8 | E A♭ B | E | Pantriadisch |

- **Wirkung:** Plötzlicher Helligkeitsschub; dieselbe Wendung eine große Terz höher.
- **Harmonisches Zentrum:** C → E
- **Bassführung:** Grundtöne; Rückung C→E ohne Vorbereitung, gemeinsamer Ton E.
- **Begleitformen:** JW-R01, JW-R31, JW-R03
- **Variation:** Rückung nach A♭ (abwärts) für dunklere Wirkung.
- **Williams-Verfahren:** Tonart rückt um eine chromatische große Terz (Happy Landings, Lehman 40); chromatische Medianten. Quellen: S1, S4.
- **Stimmungen:** Heroik, Abenteuer, Staunen

#### JW-H09 · Chromatisch modulierende Kadenzauflösung

- **XYZ-Anker:** 0,75 / 0,55 / 0,45 (Hmm) · **Taktart:** 4/4 · **Tonvorrat:** Pantriadisch · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 2 | T1 | C E G | C | Pantriadisch |
| 2 | `F/A` | 1 | T3 | A F C | A | Pantriadisch |
| 3 | `G` | 1 | T4 | G B D | G | Pantriadisch |
| 4 | `E` | 2 | T5 | E A♭ B | E | Pantriadisch |
| 5 | `A/E` | 1 | T7 | E A D♭ | E | Pantriadisch |
| 6 | `E` | 1 | T8 | E A♭ B | E | Pantriadisch |

- **Wirkung:** Die Dominante löst nicht in die Tonika, sondern in einen chromatisch verwandten Klang auf: Überraschung, Wunder.
- **Harmonisches Zentrum:** C → E
- **Bassführung:** Bass C–A–G, dann E-Pedal; G→E als Fall um eine kleine Terz.
- **Begleitformen:** JW-R14, JW-R13, JW-R31
- **Variation:** Ziel A♭ oder B statt E (andere CMCR-Typen).
- **Williams-Verfahren:** Lehmans CMCR (chromatically modulating cadential resolution), für Harry Potter, E.T. und Jurassic Park belegt. Quellen: S3.
- **Stimmungen:** Staunen, Epische Weite

#### JW-H10 · Gemischte Plagalkadenz

- **XYZ-Anker:** 0,70 / 0,45 / 0,15 (HmS) · **Taktart:** 4/4 · **Tonvorrat:** Dur-Moll-Mischung · **Kategorie:** universell · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 2 | T1 | C E G | C | Dur-Moll-Mischung |
| 2 | `F` | 1 | T3 | F A C | F | Dur-Moll-Mischung |
| 3 | `Fm` | 1 | T4 | F A♭ C | F | Dur-Moll-Mischung |
| 4 | `C` | 1 | T5 | C E G | C | Dur-Moll-Mischung |
| 5 | `Dm7b5` | 1 | T6 | D F A♭ C | D | Dur-Moll-Mischung |
| 6 | `G7` | 1 | T7 | G B D F | G | Dur-Moll-Mischung |
| 7 | `C` | 1 | T8 | C E G | C | Dur-Moll-Mischung |

- **Wirkung:** Heimkehr, Wärme, Abschluss mit einem Hauch Wehmut.
- **Harmonisches Zentrum:** C
- **Bassführung:** C–F–F–C–D–G–C; Takt 4 Bass F, in der Mittelstimme A→A♭.
- **Begleitformen:** JW-R12, JW-R16, JW-R14
- **Variation:** Dm7b5 durch Fm6 ersetzen.
- **Williams-Verfahren:** Mixed plagal cadence (6̂–♭6̂–5̂), Lehmans „Hollywood Cadence“. Quellen: S3.
- **Stimmungen:** Wärme, Romantik, Trauer

#### JW-H11 · Moll-Tonika zur Dur-Subdominante

- **XYZ-Anker:** 0,40 / 0,30 / 0,35 (mRS) · **Taktart:** 4/4 · **Tonvorrat:** Dorisch · **Kategorie:** universell · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 2 | T1 | C E♭ G | C | Dorisch |
| 2 | `F` | 2 | T3 | F A C | F | Dorisch |
| 3 | `Cm` | 2 | T5 | C E♭ G | C | Dorisch |
| 4 | `F/A` | 1 | T7 | A F C | A | Dorisch |
| 5 | `Cm` | 1 | T8 | C E♭ G | C | Dorisch |

- **Wirkung:** Schwelle ins Fremde, Märchenhaftes; Moll, aber nicht traurig.
- **Harmonisches Zentrum:** C dorisch
- **Bassführung:** C–F–C–A–C.
- **Begleitformen:** JW-R14, JW-R16
- **Variation:** F als Fadd9; Cm als Cm7.
- **Williams-Verfahren:** i–IV („Fantasy Fifth“) begleitet in Hollywoodfilmen das Überschreiten in wundersame Welten (Patrick 2023); für Williams nicht einzeln belegt. Quellen: S9.
- **Stimmungen:** Geheimnis, Magie, Staunen

#### JW-H12 · Moll-Dreiklänge im Kleinterzzyklus

- **XYZ-Anker:** 0,15 / 0,35 / 0,55 (DRm) · **Taktart:** 4/4 · **Tonvorrat:** Okt-A · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 2 | T1 | C E♭ G | C | Okt-A |
| 2 | `Ebm` | 1 | T3 | E♭ F♯ B♭ | E♭ | Okt-A |
| 3 | `Cm` | 1 | T4 | C E♭ G | C | Okt-A |
| 4 | `F#m` | 1 | T5 | F♯ A D♭ | F♯ | Okt-A |
| 5 | `Cm` | 1 | T6 | C E♭ G | C | Okt-A |
| 6 | `Am` | 1 | T7 | A C E | A | Okt-A |
| 7 | `Cm` | 1 | T8 | C E♭ G | C | Okt-A |

- **Wirkung:** Unheimliche Macht, irrational wirkende Fortschreitung, aber jeder Klang ist ein einfacher Mollakkord.
- **Harmonisches Zentrum:** C (mollzentriert)
- **Bassführung:** Grundtöne; zwischen den Klängen immer zurück zu C.
- **Begleitformen:** JW-R12, JW-R26, JW-R08
- **Variation:** Ebm und Am vertauschen; F♯m auf zwei Takte dehnen.
- **Williams-Verfahren:** Imperator-Thema: Mollklänge in chromatischen Kleinterz- oder Tritonusschritten (Lehman 17; Richards). Quellen: S1, S11.
- **Stimmungen:** Angst, Geheimnis, Lauern

#### JW-H13 · Moll-Pendel i–♭vi (hexatonisch)

- **XYZ-Anker:** 0,15 / 0,75 / 0,40 (DIm) · **Taktart:** 4/4 · **Tonvorrat:** Hex-C · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 1 | T1 | C E♭ G | C | Hex-C |
| 2 | `Abm/C` | 1 | T2 | C A♭ B E♭ | C | Hex-C |
| 3 | `Cm` | 1 | T3 | C E♭ G | C | Hex-C |
| 4 | `Abm/C` | 1 | T4 | C A♭ B E♭ | C | Hex-C |
| 5 | `Cm` | 1 | T5 | C E♭ G | C | Hex-C |
| 6 | `Abm/C` | 1 | T6 | C A♭ B E♭ | C | Hex-C |
| 7 | `Em/B` | 1 | T7 | B E G | B | Hex-C |
| 8 | `Cm` | 1 | T8 | C E♭ G | C | Hex-C |

- **Wirkung:** Marschierende Bedrohung; zwei Mollklänge mit gemeinsamem Ton E♭.
- **Harmonisches Zentrum:** C (moll)
- **Bassführung:** Pedal C, Takt 7 Ausweichung nach B.
- **Begleitformen:** JW-R01, JW-R23, JW-R22
- **Variation:** Abm/C durch Abm(add9)/C [systemfremd: B♭ liegt nicht in Hex-C]; Takt 7 Cm(b6) (im Vorrat).
- **Williams-Verfahren:** Imperial-March-Material: Mollklänge, i↔♭vi als eigene Leitharmonie, Hexatonik (Lehman 10f–g; Richards). Quellen: S1, S11.
- **Stimmungen:** Angst, Dramatische Spannung

#### JW-H14 · Tritonus-Mollwechsel

- **XYZ-Anker:** 0,20 / 0,45 / 0,60 (Dmm) · **Taktart:** 4/4 · **Tonvorrat:** Okt-A · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 2 | T1 | C E♭ G | C | Okt-A |
| 2 | `F#m` | 2 | T3 | F♯ A D♭ | F♯ | Okt-A |
| 3 | `Cm` | 2 | T5 | C E♭ G | C | Okt-A |
| 4 | `F#m` | 1 | T7 | F♯ A D♭ | F♯ | Okt-A |
| 5 | `Cm` | 1 | T8 | C E♭ G | C | Okt-A |

- **Wirkung:** Tödliche Gefahr, die von einem Ort oder Gegenstand ausgeht.
- **Harmonisches Zentrum:** C ↔ F♯ (zweideutig)
- **Bassführung:** Grundtöne C und F♯ oder Pedal C (dann Dissonanzbass unter F♯m).
- **Begleitformen:** JW-R26, JW-R12, JW-R07
- **Variation:** Mit Dur statt Moll siehe JW-H15.
- **Williams-Verfahren:** Mollklänge im Tritonusabstand stehen für tödliche Bedrohung (Murphy, zitiert bei Schneller; Lade-Thema); Map-Thema Cm↔F♯m (Lehman 48). Quellen: S6, S1, S2.
- **Stimmungen:** Angst, Geheimnis, Unbehagen

#### JW-H15 · Dur-Tritonus-Schweben

- **XYZ-Anker:** 0,70 / 0,30 / 0,50 (HRm) · **Taktart:** 4/4 · **Tonvorrat:** Okt-A · **Kategorie:** universell · **Evidenz:** Verfahren [H], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 2 | T1 | C E G | C | Okt-A |
| 2 | `F#` | 2 | T3 | F♯ B♭ D♭ | F♯ | Okt-A |
| 3 | `C` | 2 | T5 | C E G | C | Okt-A |
| 4 | `F#` | 1 | T7 | F♯ B♭ D♭ | F♯ | Okt-A |
| 5 | `C` | 1 | T8 | C E G | C | Okt-A |

- **Wirkung:** Weite des Weltraums, Fremdheit ohne Bedrohung.
- **Harmonisches Zentrum:** C ↔ F♯
- **Bassführung:** Pedal C oder Wechsel C–F♯ in langen Werten.
- **Begleitformen:** JW-R12, JW-R15, JW-R14
- **Variation:** F♯ als F♯sus2 [systemfremd: G♯ liegt nicht in Okt-A].
- **Williams-Verfahren:** Major tritone progression mit Weltraumassoziation (Murphy 2006); für Williams als Verfahren übernommen, nicht einzeln belegt. Quellen: S7.
- **Stimmungen:** Staunen, Magie, Epische Weite

#### JW-H16 · Kleinterz-Durzyklus

- **XYZ-Anker:** 0,55 / 0,70 / 0,75 (mIU) · **Taktart:** 4/4 · **Tonvorrat:** Okt-A · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 1 | T1 | C E G | C | Okt-A |
| 2 | `Eb` | 1 | T2 | E♭ G B♭ | E♭ | Okt-A |
| 3 | `F#` | 1 | T3 | F♯ B♭ D♭ | F♯ | Okt-A |
| 4 | `A` | 1 | T4 | A D♭ E | A | Okt-A |
| 5 | `C` | 1 | T5 | C E G | C | Okt-A |
| 6 | `Eb` | 1 | T6 | E♭ G B♭ | E♭ | Okt-A |
| 7 | `F#` | 1 | T7 | F♯ B♭ D♭ | F♯ | Okt-A |
| 8 | `A` | 1 | T8 | A D♭ E | A | Okt-A |

- **Wirkung:** Getriebene, glänzende Unruhe; jeder Takt ein neuer Durklang, alles im selben Tonvorrat.
- **Harmonisches Zentrum:** kein festes Zentrum (C als Rahmen)
- **Bassführung:** Grundtöne oder Pedal C (dann ab F♯ dissonant).
- **Begleitformen:** JW-R03, JW-R09, JW-R07
- **Variation:** Halbtaktig verdoppeln; Richtung umkehren (C–A–F♯–E♭).
- **Williams-Verfahren:** „Major Trouble“: chromatisch verwandte Durklänge harmonisieren eine oktatonische Melodie über dissonantem Bass (Lehman, Incidental 15); Imperials: Dreiklänge im Kleinterzabstand. Quellen: S1.
- **Stimmungen:** Action, Abenteuer, Dramatische Spannung

#### JW-H17 · Durklang über Halbton-Bass

- **XYZ-Anker:** 0,30 / 0,85 / 0,80 (DIU) · **Taktart:** 4/4 · **Tonvorrat:** Okt-A · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C/Db` | 2 | T1 | D♭ C E G | D♭ | Okt-A |
| 2 | `Eb/E` | 2 | T3 | E E♭ G B♭ | E | Okt-A |
| 3 | `F#/G` | 2 | T5 | G F♯ B♭ D♭ | G | Okt-A |
| 4 | `A/Bb` | 2 | T7 | B♭ A D♭ E | B♭ | Okt-A |

- **Wirkung:** Harte, kraftvolle Unruhe; jeder Klang steht auf einem Bass einen Halbton über seinem Grundton.
- **Harmonisches Zentrum:** kein festes Zentrum
- **Bassführung:** Bass D♭–E–G–B♭ steigt in kleinen Terzen; alle Basstöne gehören zum selben Tonvorrat.
- **Begleitformen:** JW-R07, JW-R08, JW-R25
- **Variation:** Absteigend spielen; nur zwei Klänge pendeln (C/D♭–F♯/G).
- **Williams-Verfahren:** Durakkord mit dissonantem Bass (Richards, Kurskapitel „Major Chord + Dissonant Bass“); Abstand +1 eigene Deutung. Quellen: S10.
- **Stimmungen:** Action, Angst

#### JW-H18 · Oktatonischer Liegeklang mit Repetition

- **XYZ-Anker:** 0,25 / 0,60 / 0,65 (DmU) · **Taktart:** 4/4 · **Tonvorrat:** Okt-A · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm(add#4)` | 8 | T1 | C E♭ F♯ G | C | Okt-A |

- **Wirkung:** Gespannte Ruhe; der Klang bleibt, Spannung kommt aus Rhythmus und Melodie.
- **Harmonisches Zentrum:** C
- **Bassführung:** Pedal C; keine Bassbewegung.
- **Begleitformen:** JW-R08, JW-R07, JW-R26
- **Variation:** Klang halbtaktig zwischen Cm(add#4) und Cdim7 wechseln.
- **Williams-Verfahren:** Hoth-Cue 3m3: oktatonisches Repetitionsakkord-Ostinato (Lehman, Motiv l); Richards: wiederholter Akkord mit oktatonischer Melodie. Quellen: S1, S10.
- **Stimmungen:** Lauern, Dramatische Spannung, Unbehagen

#### JW-H19 · Oktatonischer Basslauf

- **XYZ-Anker:** 0,35 / 0,65 / 0,70 (DIU) · **Taktart:** 4/4 · **Tonvorrat:** Okt-A · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 1 | T1 | C E♭ G | C | Okt-A |
| 2 | `A/Db` | 1 | T2 | D♭ A E | D♭ | Okt-A |
| 3 | `Eb` | 1 | T3 | E♭ G B♭ | E♭ | Okt-A |
| 4 | `C/E` | 1 | T4 | E C G | E | Okt-A |
| 5 | `F#m` | 1 | T5 | F♯ A D♭ | F♯ | Okt-A |
| 6 | `Eb/G` | 1 | T6 | G E♭ B♭ | G | Okt-A |
| 7 | `Am` | 1 | T7 | A C E | A | Okt-A |
| 8 | `F#/Bb` | 1 | T8 | B♭ F♯ D♭ | B♭ | Okt-A |

- **Wirkung:** Unaufhaltsames Steigen; jeder Takt ein Basston höher, darüber wechselnde Dreiklänge.
- **Harmonisches Zentrum:** C → offen
- **Bassführung:** Bass C–D♭–E♭–E–F♯–G–A–B♭ (Okt-A aufwärts).
- **Begleitformen:** JW-R03, JW-R29, JW-R07
- **Variation:** Abwärts als Spannungsabbau; halbtaktig für Zuspitzung.
- **Williams-Verfahren:** Richards: oktatonische Melodie-/Basskombination mit bewegtem Bass; Dreiklänge aus einem Tonvorrat. Quellen: S10.
- **Stimmungen:** Dramatische Spannung, Action

#### JW-H20 · Wechsel zwischen zwei oktatonischen Tonvorräten

- **XYZ-Anker:** 0,30 / 0,70 / 0,75 (DIU) · **Taktart:** 4/4 · **Tonvorrat:** Okt-A → Okt-C · **Kategorie:** Verfahren mit Planung · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 1 | T1 | C E♭ G | C | Okt-A |
| 2 | `Ebm` | 1 | T2 | E♭ F♯ B♭ | E♭ | Okt-A |
| 3 | `A/Db` | 1 | T3 | D♭ A E | D♭ | Okt-A |
| 4 | `Cdim7` | 1 | T4 | C E♭ F♯ A | C | Okt-C |
| 5 | `D` | 1 | T5 | D F♯ A | D | Okt-C |
| 6 | `F` | 1 | T6 | F A C | F | Okt-C |
| 7 | `Ab` | 1 | T7 | A♭ C E♭ | A♭ | Okt-C |
| 8 | `B` | 1 | T8 | B E♭ F♯ | B | Okt-C |

- **Wirkung:** Neue Spannungsfarbe ohne Bruch; der verminderte Septakkord verbindet beide Vorräte.
- **Harmonisches Zentrum:** C, Schluss auf B als Leitklang
- **Bassführung:** Grundtöne; Takt 4 C als gemeinsamer Ton.
- **Begleitformen:** JW-R07, JW-R03, JW-R25
- **Variation:** Rückweg Okt-C → Okt-A über dasselbe Cdim7.
- **Williams-Verfahren:** Okt-A und Okt-C teilen C E♭ F♯ A (Cdim7); Richards: aufeinanderfolgende oktatonische Tonvorräte. Konkrete Folge eigene Konstruktion. Quellen: S10.
- **Stimmungen:** Dramatische Spannung, Action

#### JW-H21 · Vermindertes Gelenk zwischen Tonal und Oktatonik

- **XYZ-Anker:** 0,50 / 0,50 / 0,60 (mmm) · **Taktart:** 4/4 · **Tonvorrat:** Dur → Okt-A · **Kategorie:** Verfahren mit Planung · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 2 | T1 | C E G | C | Dur |
| 2 | `Am` | 1 | T3 | A C E | A | Dur |
| 3 | `Cdim7` | 1 | T4 | C E♭ F♯ A | C | Okt-A |
| 4 | `Eb` | 1 | T5 | E♭ G B♭ | E♭ | Okt-A |
| 5 | `F#` | 1 | T6 | F♯ B♭ D♭ | F♯ | Okt-A |
| 6 | `Cdim7` | 1 | T7 | C E♭ F♯ A | C | Okt-A |
| 7 | `C` | 1 | T8 | C E G | C | Okt-A |

- **Wirkung:** Tonale Szene kippt in Gefahr und kehrt zurück; der Wechsel klingt organisch.
- **Harmonisches Zentrum:** C
- **Bassführung:** C–A–A–E♭–F♯–A–C (Bass hält A unter Cdim7).
- **Begleitformen:** JW-R14, JW-R03
- **Variation:** Cdim7 durch C7b9 ersetzen (tonal deutbar).
- **Williams-Verfahren:** Verminderter Septakkord als Verbindungsglied (eigene Ableitung aus der Struktur; Pearson: dim7 ersetzt V im E.T.-Flugthema). Quellen: S12, S10.
- **Stimmungen:** Unbehagen, Abenteuer

#### JW-H22 · Polychord-Schläge („Holst-Akkorde“)

- **XYZ-Anker:** 0,20 / 0,90 / 0,70 (DIU) · **Taktart:** 4/4 · **Tonvorrat:** Okt-A · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `F#\|C` | 2 | T1 | C E G F♯ B♭ D♭ | C | Okt-A |
| 2 | `Eb\|A` | 2 | T3 | A D♭ E E♭ G B♭ | A | Okt-A |
| 3 | `F#\|C` | 2 | T5 | C E G F♯ B♭ D♭ | C | Okt-A |
| 4 | `C5` | 2 | T7 | C G | C | Okt-A |

- **Wirkung:** Wuchtige, kriegerische Gewalt.
- **Harmonisches Zentrum:** C
- **Bassführung:** Pedal C bzw. A; Takt 7–8 leere Quinte als Ruhepunkt.
- **Begleitformen:** JW-R22, JW-R01, JW-R21
- **Variation:** Oberer Klang D♭ statt F♯ (dissonanter, nicht oktatonisch).
- **Williams-Verfahren:** Martial Chords: dissonantes, hämmerndes Polychord nach Holsts „Mars“, von Williams „Holst chords“ genannt (Lehman, Incidental 3). Quellen: S1.
- **Stimmungen:** Action, Angst, Heroik

#### JW-H23 · Moll-Polychord-Oszillation

- **XYZ-Anker:** 0,10 / 0,40 / 0,55 (Dmm) · **Taktart:** 4/4 · **Tonvorrat:** Hex-C · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 1 | T1 | C E♭ G | C | Hex-C |
| 2 | `Abm\|Cm` | 1 | T2 | C E♭ G A♭ B | C | Hex-C |
| 3 | `Cm` | 1 | T3 | C E♭ G | C | Hex-C |
| 4 | `Abm\|Cm` | 1 | T4 | C E♭ G A♭ B | C | Hex-C |
| 5 | `Cm` | 1 | T5 | C E♭ G | C | Hex-C |
| 6 | `Abm\|Cm` | 1 | T6 | C E♭ G A♭ B | C | Hex-C |
| 7 | `Abm` | 1 | T7 | A♭ B E♭ | A♭ | Hex-C |
| 8 | `Cm` | 1 | T8 | C E♭ G | C | Hex-C |

- **Wirkung:** Dunkle Magie, verdorbene Macht; zwei Mollklänge verschwimmen ineinander.
- **Harmonisches Zentrum:** C (moll)
- **Bassführung:** Pedal C.
- **Begleitformen:** JW-R12, JW-R26
- **Variation:** Abm|Cm nur in Streichertremolo.
- **Williams-Verfahren:** Polychordische Oszillation chromatisch verwandter Mollklänge (Sith-Artefakte, Lehman 60a). Quellen: S1.
- **Stimmungen:** Magie, Angst, Geheimnis

#### JW-H24 · Hexatonischer Pol

- **XYZ-Anker:** 0,45 / 0,35 / 0,50 (mRm) · **Taktart:** 4/4 · **Tonvorrat:** Hex-C · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 2 | T1 | C E G | C | Hex-C |
| 2 | `Abm` | 2 | T3 | A♭ B E♭ | A♭ | Hex-C |
| 3 | `C` | 2 | T5 | C E G | C | Hex-C |
| 4 | `Abm` | 1 | T7 | A♭ B E♭ | A♭ | Hex-C |
| 5 | `C` | 1 | T8 | C E G | C | Hex-C |

- **Wirkung:** Unheimliches Staunen; maximal fremder Klang bei minimaler Stimmbewegung.
- **Harmonisches Zentrum:** C
- **Bassführung:** Pedal C (dann Abm/C) oder Grundton A♭.
- **Begleitformen:** JW-R12, JW-R15
- **Variation:** Abm über C-Pedal als Polychord.
- **Williams-Verfahren:** Hexatonischer Pol (Cohn); Lehman: Anakin-Material mit hexatonischem Pol (♭vi), Trauermarsch zu hexatonisch-polarem Polychord. Quellen: S1, S19.
- **Stimmungen:** Magie, Geheimnis, Staunen

#### JW-H25 · Hexatonischer Zyklus

- **XYZ-Anker:** 0,45 / 0,45 / 0,60 (mmm) · **Taktart:** 4/4 · **Tonvorrat:** Hex-C · **Kategorie:** Verfahren mit Planung · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 1 | T1 | C E G | C | Hex-C |
| 2 | `Cm` | 1 | T2 | C E♭ G | C | Hex-C |
| 3 | `Ab` | 1 | T3 | A♭ C E♭ | A♭ | Hex-C |
| 4 | `Abm` | 1 | T4 | A♭ B E♭ | A♭ | Hex-C |
| 5 | `E` | 1 | T5 | E A♭ B | E | Hex-C |
| 6 | `Em` | 1 | T6 | E G B | E | Hex-C |
| 7 | `C` | 2 | T7 | C E G | C | Hex-C |

- **Wirkung:** Wanderung durch fremde Klänge, Stimmen bewegen sich nur in Halbtönen.
- **Harmonisches Zentrum:** Zyklus zurück zu C
- **Bassführung:** Grundtöne C–C–A♭–A♭–E–E–C oder Pedal C.
- **Begleitformen:** JW-R14, JW-R15, JW-R12
- **Variation:** Rückwärts; nur halber Zyklus (C–Cm–A♭–A♭m).
- **Williams-Verfahren:** P/L-Zyklus innerhalb eines hexatonischen Systems (Cohn); Hexatonik bei Williams belegt (Droids, Imperial March, Lehman). Quellen: S1, S19, S4.
- **Stimmungen:** Magie, Staunen, Unbehagen

#### JW-H26 · Ganztonfläche

- **XYZ-Anker:** 0,60 / 0,25 / 0,60 (mRm) · **Taktart:** 4/4 · **Tonvorrat:** Ganzton-0 · **Kategorie:** universell · **Evidenz:** Verfahren [H], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Caug` | 2 | T1 | C E A♭ | C | Ganzton-0 |
| 2 | `D7#5/C` | 2 | T3 | C D F♯ B♭ | C | Ganzton-0 |
| 3 | `C7#5` | 2 | T5 | C E A♭ B♭ | C | Ganzton-0 |
| 4 | `Caug` | 2 | T7 | C E A♭ | C | Ganzton-0 |

- **Wirkung:** Schwebende Orientierungslosigkeit, Traum, Zauberei.
- **Harmonisches Zentrum:** kein Zentrum (C als Rahmen)
- **Bassführung:** Pedal C.
- **Begleitformen:** JW-R15, JW-R12
- **Variation:** Nur als Übergangsfläche (4 Takte).
- **Williams-Verfahren:** Ganztonharmonik ist in den eingesehenen Williams-Quellen nicht ausdrücklich belegt; Verfahren als Hypothese. Keine direkte Quelle.
- **Stimmungen:** Magie, Geheimnis

#### JW-H27 · Quartenkette

- **XYZ-Anker:** 0,70 / 0,75 / 0,50 (HIm) · **Taktart:** 4/4 · **Tonvorrat:** Mixolydisch · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cq` | 1 | T1 | C F B♭ | C | Mixolydisch |
| 2 | `Dq` | 1 | T2 | D G C | D | Mixolydisch |
| 3 | `Eq` | 1 | T3 | E A D | E | Mixolydisch |
| 4 | `Dq` | 1 | T4 | D G C | D | Mixolydisch |
| 5 | `Cq` | 1 | T5 | C F B♭ | C | Mixolydisch |
| 6 | `Aq` | 1 | T6 | A D G | A | Mixolydisch |
| 7 | `Gq` | 1 | T7 | G C F | G | Mixolydisch |
| 8 | `Cq` | 1 | T8 | C F B♭ | C | Mixolydisch |

- **Wirkung:** Archaisch-heroische Kraft, offen und hart.
- **Harmonisches Zentrum:** C mixolydisch
- **Bassführung:** Grundtöne der Quartenstapel.
- **Begleitformen:** JW-R01, JW-R04, JW-R27
- **Variation:** Im Kanon versetzt (Kurze Fläche gegen Gegenstimme).
- **Williams-Verfahren:** Quartale Einfärbungen im Hauptthema, Quartenkanon in der Schlacht von Yavin (Lehman 1a, Incidental 21); Superman-Fanfare mit Quartenakkorden (Richards). Quellen: S1, S11.
- **Stimmungen:** Heroik, Abenteuer, Action

#### JW-H28 · Sus-Pendel C2 – G7sus4

- **XYZ-Anker:** 0,80 / 0,45 / 0,35 (HmS) · **Taktart:** 4/4 · **Tonvorrat:** Dur · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Csus2` | 1 | T1 | C D G | C | Dur |
| 2 | `G7sus4` | 1 | T2 | G C D F | G | Dur |
| 3 | `Csus2` | 1 | T3 | C D G | C | Dur |
| 4 | `G7sus4` | 1 | T4 | G C D F | G | Dur |
| 5 | `Am7` | 1 | T5 | A C E G | A | Dur |
| 6 | `Fsus2` | 1 | T6 | F G C | F | Dur |
| 7 | `G7sus4` | 1 | T7 | G C D F | G | Dur |
| 8 | `Csus2` | 1 | T8 | C D G | C | Dur |

- **Wirkung:** Schwebende Vorfreude, Bewegung ohne Ankunft.
- **Harmonisches Zentrum:** C
- **Bassführung:** Bass C–G–C–G–A–F–G–C.
- **Begleitformen:** JW-R14, JW-R03
- **Variation:** Takt 5–6 halbtaktig; Csus2→C erst im letzten Takt.
- **Williams-Verfahren:** E.T.-Flugmusik: Wechsel C2 / G7sus4 über Achtelostinato (Pearson-Analyse); Verfolgungsthema mit sus- und Quartklängen (Lehman 50). Quellen: S12, S1.
- **Stimmungen:** Staunen, Abenteuer, Verspieltheit

#### JW-H29 · Großterzzyklus in Dur

- **XYZ-Anker:** 0,70 / 0,55 / 0,50 (Hmm) · **Taktart:** 4/4 · **Tonvorrat:** Hex-C · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 1 | T1 | C E G | C | Hex-C |
| 2 | `Ab` | 1 | T2 | A♭ C E♭ | A♭ | Hex-C |
| 3 | `C` | 1 | T3 | C E G | C | Hex-C |
| 4 | `E` | 1 | T4 | E A♭ B | E | Hex-C |
| 5 | `Ab` | 1 | T5 | A♭ C E♭ | A♭ | Hex-C |
| 6 | `E` | 1 | T6 | E A♭ B | E | Hex-C |
| 7 | `C` | 2 | T7 | C E G | C | Hex-C |

- **Wirkung:** Flug, Aufbruch, ein Glanz nach dem anderen.
- **Harmonisches Zentrum:** C
- **Bassführung:** Grundtöne; Takte 4–6 alternativ Pedal E.
- **Begleitformen:** JW-R14, JW-R03, JW-R31
- **Variation:** Halbtaktig in Action-Bereichen.
- **Williams-Verfahren:** Kontrastteile mit Akkordgrundtönen im Terzabstand (Pearson, E.T.); chromatische Großterzbeziehungen (Lehman). Quellen: S12, S1.
- **Stimmungen:** Staunen, Abenteuer

#### JW-H30 · Chromatischer Basslink

- **XYZ-Anker:** 0,55 / 0,40 / 0,45 (mmm) · **Taktart:** 4/4 · **Tonvorrat:** Pantriadisch · **Kategorie:** universell · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Am` | 1 | T1 | A C E | A | Pantriadisch |
| 2 | `Fm/Ab` | 1 | T2 | A♭ F C | A♭ | Pantriadisch |
| 3 | `Eb/G` | 1 | T3 | G E♭ B♭ | G | Pantriadisch |
| 4 | `D/F#` | 1 | T4 | F♯ D A | F♯ | Pantriadisch |
| 5 | `Dm/F` | 1 | T5 | F D A | F | Pantriadisch |
| 6 | `C/E` | 1 | T6 | E C G | E | Pantriadisch |
| 7 | `Fmaj7` | 1 | T7 | F A C E | F | Pantriadisch |
| 8 | `G` | 1 | T8 | G B D | G | Pantriadisch |

- **Wirkung:** Wehmütiges Gleiten zwischen nicht-funktionalen Klängen; der Bass hält alles zusammen.
- **Harmonisches Zentrum:** C (Halbschluss)
- **Bassführung:** Bass A–A♭–G–F♯–F–E–F–G (chromatisch fallend, dann Aufschwung).
- **Begleitformen:** JW-R16, JW-R14, JW-R12
- **Variation:** Bass in Viertelnoten durchlaufen lassen.
- **Williams-Verfahren:** Nicht-funktionale chromatische Bassverbindungen im E.T.-Flugthema (Pearson); konkrete Folge eigene Konstruktion. Quellen: S12.
- **Stimmungen:** Romantik, Trauer, Staunen

#### JW-H31 · Verminderter Septakkord statt Dominante

- **XYZ-Anker:** 0,65 / 0,45 / 0,35 (HmS) · **Taktart:** 4/4 · **Tonvorrat:** Dur-Moll-Mischung · **Kategorie:** universell · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 2 | T1 | C E G | C | Dur-Moll-Mischung |
| 2 | `F` | 1 | T3 | F A C | F | Dur-Moll-Mischung |
| 3 | `Am` | 1 | T4 | A C E | A | Dur-Moll-Mischung |
| 4 | `Dm7` | 1 | T5 | D F A C | D | Dur-Moll-Mischung |
| 5 | `Bdim7` | 1 | T6 | B D F A♭ | B | Dur-Moll-Mischung |
| 6 | `C` | 2 | T7 | C E G | C | Dur-Moll-Mischung |

- **Wirkung:** Rückkehr zur Tonika mit erhöhtem Spannungsmoment.
- **Harmonisches Zentrum:** C
- **Bassführung:** C–F–A–D–B–C.
- **Begleitformen:** JW-R14, JW-R16
- **Variation:** Bdim7 auf C-Pedal (Bdim7/C).
- **Williams-Verfahren:** Verminderte Septakkorde ersetzen V vor Wiedereintritt der Tonika (Pearson, E.T.). Quellen: S12.
- **Stimmungen:** Wärme, Abenteuer

#### JW-H32 · Dur-Moll-Terz gleichzeitig

- **XYZ-Anker:** 0,55 / 0,30 / 0,45 (mRm) · **Taktart:** 4/4 · **Tonvorrat:** Dur-Moll-Mischung · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 2 | T1 | C E G | C | Dur-Moll-Mischung |
| 2 | `F` | 1 | T3 | F A C | F | Dur-Moll-Mischung |
| 3 | `Ab` | 1 | T4 | A♭ C E♭ | A♭ | Dur-Moll-Mischung |
| 4 | `C` | 2 | T5 | C E G | C | Dur-Moll-Mischung |
| 5 | `C(addb3)` | 2 | T7 | C E♭ E G | C | Dur-Moll-Mischung |

- **Wirkung:** Bittersüßes, fremdartiges Leuchten; große und kleine Terz klingen zusammen.
- **Harmonisches Zentrum:** C
- **Bassführung:** Pedal C.
- **Begleitformen:** JW-R12, JW-R14
- **Variation:** E♭ nur in der Gegenstimme.
- **Williams-Verfahren:** Querstand E♭ gegen E in der Coda des E.T.-Flugthemas (Pearson). Quellen: S12.
- **Stimmungen:** Magie, Trauer, Unbehagen

#### JW-H33 · Heroische Mischung ♭VI–♭VII–I

- **XYZ-Anker:** 0,80 / 0,85 / 0,30 (HIS) · **Taktart:** 4/4 · **Tonvorrat:** Dur-Moll-Mischung · **Kategorie:** universell · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 2 | T1 | C E G | C | Dur-Moll-Mischung |
| 2 | `Am` | 1 | T3 | A C E | A | Dur-Moll-Mischung |
| 3 | `F` | 1 | T4 | F A C | F | Dur-Moll-Mischung |
| 4 | `Ab` | 1 | T5 | A♭ C E♭ | A♭ | Dur-Moll-Mischung |
| 5 | `Bb` | 1 | T6 | B♭ D F | B♭ | Dur-Moll-Mischung |
| 6 | `C` | 2 | T7 | C E G | C | Dur-Moll-Mischung |

- **Wirkung:** Triumphaler Schluss, Ankunft mit Glanz.
- **Harmonisches Zentrum:** C
- **Bassführung:** C–A–F–A♭–B♭–C (letzte drei Bässe stufenweise).
- **Begleitformen:** JW-R31, JW-R01, JW-R10
- **Variation:** Ab und Bb halbtaktig in einem Takt.
- **Williams-Verfahren:** Modale Mischung mit Heldenassoziation (Schneller); ♭VI–♭VII–I als Hollywoodkadenz (Lehman 2013). Quellen: S6, S3.
- **Stimmungen:** Heroik, Epische Weite

#### JW-H34 · Moll-Trauer mit Sextakkord

- **XYZ-Anker:** 0,25 / 0,30 / 0,20 (DRS) · **Taktart:** 4/4 · **Tonvorrat:** Moll gesamt · **Kategorie:** universell · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 2 | T1 | C E♭ G | C | Moll gesamt |
| 2 | `Abmaj7` | 1 | T3 | A♭ C E♭ G | A♭ | Moll gesamt |
| 3 | `Fm6` | 1 | T4 | F A♭ C D | F | Moll gesamt |
| 4 | `Cm/G` | 1 | T5 | G C E♭ | G | Moll gesamt |
| 5 | `G7sus4` | 1 | T6 | G C D F | G | Moll gesamt |
| 6 | `G7` | 1 | T7 | G B D F | G | Moll gesamt |
| 7 | `Cm` | 1 | T8 | C E♭ G | C | Moll gesamt |

- **Wirkung:** Melancholie, Verlust, gefasst.
- **Harmonisches Zentrum:** C-Moll
- **Bassführung:** C–A♭–F–G–G–G–C.
- **Begleitformen:** JW-R12, JW-R16
- **Variation:** Fm6 als Dm7b5/F.
- **Williams-Verfahren:** Allgemeine spätromantische Mollharmonik; Lament-Material mit 4–3-Vorhalten und Pedalen (Lehman 37b). Quellen: S1.
- **Stimmungen:** Trauer

#### JW-H35 · Undulation Tonika–Mediante

- **XYZ-Anker:** 0,50 / 0,25 / 0,15 (mRS) · **Taktart:** 4/4 · **Tonvorrat:** Dur · **Kategorie:** universell · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 1 | T1 | C E G | C | Dur |
| 2 | `Em/B` | 1 | T2 | B E G | B | Dur |
| 3 | `C` | 1 | T3 | C E G | C | Dur |
| 4 | `Em/B` | 1 | T4 | B E G | B | Dur |
| 5 | `Am` | 1 | T5 | A C E | A | Dur |
| 6 | `Em` | 1 | T6 | E G B | E | Dur |
| 7 | `F` | 1 | T7 | F A C | F | Dur |
| 8 | `C` | 1 | T8 | C E G | C | Dur |

- **Wirkung:** Leise Trauer, Erinnerung; zwei Klänge wiegen hin und her.
- **Harmonisches Zentrum:** C
- **Bassführung:** C–B–C–B–A–E–F–C.
- **Begleitformen:** JW-R16, JW-R12
- **Variation:** C ↔ Abm statt C ↔ Em [verlässt den Dur-Vorrat bewusst: hexatonischer Pol, dunkler].
- **Williams-Verfahren:** Murphy: I–iii („Loss Gesture“, M4m) als Klang von Verlust und Sentiment in Hollywood-Musik (Horner-Beispiele); für Williams nicht einzeln belegt, daher Übertragung. Quellen: S8.
- **Stimmungen:** Trauer, Wärme

#### JW-H36 · Pandiatonische Add-Fläche

- **XYZ-Anker:** 0,75 / 0,20 / 0,10 (HRS) · **Taktart:** 4/4 · **Tonvorrat:** Dur · **Kategorie:** universell · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cadd9` | 2 | T1 | C E G D | C | Dur |
| 2 | `Fadd9/C` | 2 | T3 | C F A G | C | Dur |
| 3 | `Am7` | 2 | T5 | A C E G | A | Dur |
| 4 | `Gsus4` | 1 | T7 | G C D | G | Dur |
| 5 | `Cadd9` | 1 | T8 | C E G D | C | Dur |

- **Wirkung:** Wärme, Kindheit, Geborgenheit; alle Klänge aus derselben Dur-Tonleiter, aber mit Zusatztönen.
- **Harmonisches Zentrum:** C
- **Bassführung:** Pedal C, Takt 5–6 A, Takt 7 G.
- **Begleitformen:** JW-R14, JW-R12
- **Variation:** Fadd9/C als Fmaj7/C.
- **Williams-Verfahren:** Zusatzton-Durklänge (C2) im E.T.-Flugthema (Pearson); pandiatonische Deutung eigene Interpretation. Quellen: S12.
- **Stimmungen:** Wärme, Romantik

#### JW-H37 · Quintfallsequenz mit Septimen und Zwischendominante

- **XYZ-Anker:** 0,60 / 0,45 / 0,25 (mmS) · **Taktart:** 4/4 · **Tonvorrat:** Pantriadisch · **Kategorie:** universell · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cmaj7` | 1 | T1 | C E G B | C | Pantriadisch |
| 2 | `Fmaj7` | 1 | T2 | F A C E | F | Pantriadisch |
| 3 | `Bm7b5` | 1 | T3 | B D F A | B | Pantriadisch |
| 4 | `E7` | 1 | T4 | E A♭ B D | E | Pantriadisch |
| 5 | `Am7` | 1 | T5 | A C E G | A | Pantriadisch |
| 6 | `Dm7` | 1 | T6 | D F A C | D | Pantriadisch |
| 7 | `G7sus4` | 1 | T7 | G C D F | G | Pantriadisch |
| 8 | `Cmaj7` | 1 | T8 | C E G B | C | Pantriadisch |

- **Wirkung:** Romantischer Fluss; die Harmonie zieht unausweichlich zur Tonika.
- **Harmonisches Zentrum:** C
- **Bassführung:** Quintfall C–F–B–E–A–D–G–C.
- **Begleitformen:** JW-R16, JW-R14
- **Variation:** Halbtaktig in der zweiten Hälfte (Beschleunigung).
- **Williams-Verfahren:** Harmonische Sequenz; allgemeine Hollywood-Romantik (eigene Konstruktion, Verfahren universell). Keine direkte Quelle.
- **Stimmungen:** Romantik, Wärme

#### JW-H38 · Romantische Mischklänge über Pedal

- **XYZ-Anker:** 0,60 / 0,35 / 0,30 (mRS) · **Taktart:** 4/4 · **Tonvorrat:** Dur-Moll-Mischung · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cmaj7` | 1 | T1 | C E G B | C | Dur-Moll-Mischung |
| 2 | `Fm6/C` | 1 | T2 | C F A♭ D | C | Dur-Moll-Mischung |
| 3 | `Cmaj7` | 1 | T3 | C E G B | C | Dur-Moll-Mischung |
| 4 | `Abmaj7/C` | 1 | T4 | C A♭ E♭ G | C | Dur-Moll-Mischung |
| 5 | `Fmaj7` | 1 | T5 | F A C E | F | Dur-Moll-Mischung |
| 6 | `Fm6` | 1 | T6 | F A♭ C D | F | Dur-Moll-Mischung |
| 7 | `Csus4` | 1 | T7 | C F G | C | Dur-Moll-Mischung |
| 8 | `C` | 1 | T8 | C E G | C | Dur-Moll-Mischung |

- **Wirkung:** Zärtlichkeit mit Duft und Schatten.
- **Harmonisches Zentrum:** C
- **Bassführung:** Pedal C Takt 1–4, dann F–F–C–C.
- **Begleitformen:** JW-R16, JW-R12
- **Variation:** Abmaj7/C als Abmaj7#11/C.
- **Williams-Verfahren:** Luke-und-Leia-Thema: Betonung von Pedalen und gemischten, chromatischen Klängen (Lehman 20). Quellen: S1.
- **Stimmungen:** Romantik, Wärme

#### JW-H39 · Chromatisch fallender Lamentobass

- **XYZ-Anker:** 0,25 / 0,45 / 0,40 (Dmm) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Kategorie:** universell · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 1 | T1 | C E♭ G | C | Chromatisch |
| 2 | `G/B` | 1 | T2 | B G D | B | Chromatisch |
| 3 | `Gm/Bb` | 1 | T3 | B♭ G D | B♭ | Chromatisch |
| 4 | `F/A` | 1 | T4 | A F C | A | Chromatisch |
| 5 | `Fm/Ab` | 1 | T5 | A♭ F C | A♭ | Chromatisch |
| 6 | `Cm/G` | 1 | T6 | G C E♭ | G | Chromatisch |
| 7 | `D7/F#` | 1 | T7 | F♯ D A C | F♯ | Chromatisch |
| 8 | `G` | 1 | T8 | G B D | G | Chromatisch |

- **Wirkung:** Unausweichliches Sinken, tragisch.
- **Harmonisches Zentrum:** C-Moll (Halbschluss)
- **Bassführung:** C–B–B♭–A–A♭–G–F♯–G.
- **Begleitformen:** JW-R12, JW-R16, JW-R13
- **Variation:** Halbtaktig als Spannungssequenz.
- **Williams-Verfahren:** Lament-Material, langsamer chromatischer Fall (Lehman 37b, Incidental 44 „Slow Chromatic Plunge“). Quellen: S1.
- **Stimmungen:** Trauer, Dramatische Spannung

#### JW-H40 · Gemeinsamer-Ton-Wanderung über C

- **XYZ-Anker:** 0,30 / 0,25 / 0,40 (DRm) · **Taktart:** 4/4 · **Tonvorrat:** Pantriadisch · **Kategorie:** universell · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 1 | T1 | C E♭ G | C | Pantriadisch |
| 2 | `Ab/C` | 1 | T2 | C A♭ E♭ | C | Pantriadisch |
| 3 | `Am/C` | 1 | T3 | C A E | C | Pantriadisch |
| 4 | `F/C` | 1 | T4 | C F A | C | Pantriadisch |
| 5 | `Fm/C` | 1 | T5 | C F A♭ | C | Pantriadisch |
| 6 | `F#dim/C` | 1 | T6 | C F♯ A | C | Pantriadisch |
| 7 | `Ab/C` | 1 | T7 | C A♭ E♭ | C | Pantriadisch |
| 8 | `Cm` | 1 | T8 | C E♭ G | C | Pantriadisch |

- **Wirkung:** Geheimnisvolles Driften; jeder Klang enthält C, sonst ändert sich alles.
- **Harmonisches Zentrum:** C
- **Bassführung:** Pedal C.
- **Begleitformen:** JW-R12, JW-R15
- **Variation:** C liegt in der Oberstimme statt im Bass.
- **Williams-Verfahren:** Modulation über gemeinsame Töne, pantriadische Chromatik (Lehman 2018, Begriff „pantriadic“). Quellen: S4.
- **Stimmungen:** Geheimnis, Magie, Unbehagen

#### JW-H41 · Phrygische Lauer-Achse

- **XYZ-Anker:** 0,15 / 0,25 / 0,45 (DRm) · **Taktart:** 4/4 · **Tonvorrat:** Phrygisch · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 2 | T1 | C E♭ G | C | Phrygisch |
| 2 | `Db/C` | 1 | T3 | C D♭ F A♭ | C | Phrygisch |
| 3 | `Cm` | 1 | T4 | C E♭ G | C | Phrygisch |
| 4 | `Cm` | 2 | T5 | C E♭ G | C | Phrygisch |
| 5 | `Db/C` | 1 | T7 | C D♭ F A♭ | C | Phrygisch |
| 6 | `Cm` | 1 | T8 | C E♭ G | C | Phrygisch |

- **Wirkung:** Lauern, Schleichen; ein einziger fremder Halbton über liegendem Moll.
- **Harmonisches Zentrum:** C phrygisch
- **Bassführung:** Pedal C.
- **Begleitformen:** JW-R26, JW-R07, JW-R11
- **Variation:** Db/C als Dbmaj7/C.
- **Williams-Verfahren:** Imperials-Motiv: ♭2 deutet Phrygisch/Oktatonik an (Lehman 6); Hauptthema in Yavin nach Moll/Phrygisch umgefärbt. Quellen: S1.
- **Stimmungen:** Lauern, Angst

#### JW-H42 · Dorisch-mystische Fläche

- **XYZ-Anker:** 0,35 / 0,30 / 0,25 (DRS) · **Taktart:** 4/4 · **Tonvorrat:** Dorisch · **Kategorie:** universell · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm7` | 2 | T1 | C E♭ G B♭ | C | Dorisch |
| 2 | `Dm7` | 2 | T3 | D F A C | D | Dorisch |
| 3 | `Cm7` | 1 | T5 | C E♭ G B♭ | C | Dorisch |
| 4 | `Ebmaj7` | 1 | T6 | E♭ G B♭ D | E♭ | Dorisch |
| 5 | `Bbsus2` | 1 | T7 | B♭ C F | B♭ | Dorisch |
| 6 | `Cm` | 1 | T8 | C E♭ G | C | Dorisch |

- **Wirkung:** Rätsel, archaische Ruhe, weder hell noch traurig.
- **Harmonisches Zentrum:** C dorisch
- **Bassführung:** C–D–C–E♭–B♭–C.
- **Begleitformen:** JW-R12, JW-R14
- **Variation:** Dm7 als F/D.
- **Williams-Verfahren:** Modale Harmonik; Gral-Thema mit modaler Flexibilität (Lehman, IJ-Katalog); konkrete Folge eigene Konstruktion. Quellen: S2.
- **Stimmungen:** Geheimnis, Magie

#### JW-H43 · Ungarisch-Moll-Aktionsklang

- **XYZ-Anker:** 0,20 / 0,75 / 0,65 (DIU) · **Taktart:** 4/4 · **Tonvorrat:** Ungarisch-Moll · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `CmM7` | 2 | T1 | C E♭ G B | C | Ungarisch-Moll |
| 2 | `Ab` | 1 | T3 | A♭ C E♭ | A♭ | Ungarisch-Moll |
| 3 | `B` | 1 | T4 | B E♭ F♯ | B | Ungarisch-Moll |
| 4 | `CmM7` | 2 | T5 | C E♭ G B | C | Ungarisch-Moll |
| 5 | `Ebaug` | 1 | T7 | E♭ G B | E♭ | Ungarisch-Moll |
| 6 | `G` | 1 | T8 | G B D | G | Ungarisch-Moll |

- **Wirkung:** Exotische, scharfe Bedrohung im Kampf.
- **Harmonisches Zentrum:** C
- **Bassführung:** C–A♭–B–C–E♭–G.
- **Begleitformen:** JW-R07, JW-R25
- **Variation:** B als B/D♯ (Terzbass, D♯ = E♭ im Vorrat). Korrigiert: die frühere Variante „B7“ enthielt A, das nicht im Vorrat liegt.
- **Williams-Verfahren:** Ungarisch-Moll als eine der drei Hauptskalen klassischer Actionmusik (Richards, Kursübersicht); konkrete Folge eigene Konstruktion. Quellen: S10.
- **Stimmungen:** Action, Angst, Magie

#### JW-H44 · Moll mit kleiner Sexte, ausgehalten

- **XYZ-Anker:** 0,20 / 0,65 / 0,50 (DIm) · **Taktart:** 4/4 · **Tonvorrat:** Moll harm. · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm(b6)` | 4 | T1 | C E♭ G A♭ | C | Moll harm. |
| 2 | `CmM7b6` | 2 | T5 | C E♭ G B A♭ | C | Moll harm. |
| 3 | `Cm(b6)` | 2 | T7 | C E♭ G A♭ | C | Moll harm. |

- **Wirkung:** Lange Spannungsstrecke auf einem Klang; Unruhe ohne Akkordwechsel.
- **Harmonisches Zentrum:** C
- **Bassführung:** Pedal C.
- **Begleitformen:** JW-R07, JW-R08, JW-R25
- **Variation:** A♭ nur in der Gegenstimme.
- **Williams-Verfahren:** Richards: Actionakkorde m(♭6), mM7(♭6) als Erweiterung eines Einzelklangs über lange Passagen (Kursübersicht). Quellen: S10.
- **Stimmungen:** Dramatische Spannung, Action, Lauern

#### JW-H45 · Übermäßig mit großer Septime

- **XYZ-Anker:** 0,45 / 0,60 / 0,70 (mmU) · **Taktart:** 4/4 · **Tonvorrat:** Hex-C · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `CaugM7` | 2 | T1 | C E A♭ B | C | Hex-C |
| 2 | `CaugM7#9` | 2 | T3 | C E A♭ B E♭ | C | Hex-C |
| 3 | `Abm` | 2 | T5 | A♭ B E♭ | A♭ | Hex-C |
| 4 | `C` | 2 | T7 | C E G | C | Hex-C |

- **Wirkung:** Magische Bedrohung, glänzend und instabil.
- **Harmonisches Zentrum:** C
- **Bassführung:** Pedal C, Takt 5–6 A♭.
- **Begleitformen:** JW-R15, JW-R08
- **Variation:** Ohne Auflösung nach C (Ende auf Abm).
- **Williams-Verfahren:** Richards: hexatonische Vierklänge mM7 und augM7, Actionklang augM7(♯9); alle Töne im hexatonischen Vorrat. Quellen: S10.
- **Stimmungen:** Magie, Dramatische Spannung

#### JW-H46 · Dissonanzbass unter statischem Moll

- **XYZ-Anker:** 0,15 / 0,60 / 0,70 (DmU) · **Taktart:** 4/4 · **Tonvorrat:** Okt-A · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm/F#` | 2 | T1 | F♯ C E♭ G | F♯ | Okt-A |
| 2 | `Cm/Db` | 2 | T3 | D♭ C E♭ G | D♭ | Okt-A |
| 3 | `Cm/F#` | 2 | T5 | F♯ C E♭ G | F♯ | Okt-A |
| 4 | `Cm` | 2 | T7 | C E♭ G | C | Okt-A |

- **Wirkung:** Bodenloses Unbehagen; oben bleibt alles, unten rutscht der Boden weg.
- **Harmonisches Zentrum:** C
- **Bassführung:** Bass F♯–D♭–F♯–C.
- **Begleitformen:** JW-R07, JW-R26
- **Variation:** Bass nur auf Zählzeit 1, sonst Pause.
- **Williams-Verfahren:** Richards: Mollakkord mit dissonantem Bass (Kursübersicht „Minor Chord + Dissonant Bass“). Quellen: S10.
- **Stimmungen:** Unbehagen, Angst

#### JW-H47 · Atonale (014)-Zellen im Kleinterzabstand

- **XYZ-Anker:** 0,20 / 0,85 / 0,95 (DIU) · **Taktart:** 4/4 · **Tonvorrat:** Okt-A · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `{C Db E}` | 1 | T1 | C D♭ E | C | Okt-A |
| 2 | `{F# G Bb}` | 1 | T2 | F♯ G B♭ | F♯ | Okt-A |
| 3 | `{Eb E G}` | 1 | T3 | E♭ E G | E♭ | Okt-A |
| 4 | `{A Bb Db}` | 1 | T4 | A B♭ D♭ | A | Okt-A |
| 5 | `{C Db E}` | 1 | T5 | C D♭ E | C | Okt-A |
| 6 | `{F# G Bb}` | 1 | T6 | F♯ G B♭ | F♯ | Okt-A |
| 7 | `{Eb E G}` | 1 | T7 | E♭ E G | E♭ | Okt-A |
| 8 | `{A Bb Db}` | 1 | T8 | A B♭ D♭ | A | Okt-A |

- **Wirkung:** Höchste Unruhe, rhythmischer Kampf, ohne tonalen Halt.
- **Harmonisches Zentrum:** kein Zentrum
- **Bassführung:** Tiefster Ton jeder Zelle als Bass.
- **Begleitformen:** JW-R04, JW-R25, JW-R07
- **Variation:** Zellen halbtaktig für die letzte Zuspitzungsstufe.
- **Williams-Verfahren:** Atonale, stark synkopierte Passagen im Hoth-Cue (Lehman, Motiv o); Richards: atonale Dreitonklänge, (014). Kleinterzanordnung eigene Konstruktion. Quellen: S1, S10.
- **Stimmungen:** Action, Angst

#### JW-H48 · Zwei oktatonische Vorräte im Halbtaktwechsel

- **XYZ-Anker:** 0,30 / 0,95 / 1,00 (DIU) · **Taktart:** 4/4 · **Tonvorrat:** Okt-A → Okt-B · **Kategorie:** Verfahren mit Planung · **Evidenz:** Verfahren [E], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C/Db` | ½ | T1 | D♭ C E G | D♭ | Okt-A |
| 2 | `Db/D` | ½ | T1+½ | D D♭ F A♭ | D | Okt-B |
| 3 | `C/Db` | ½ | T2 | D♭ C E G | D♭ | Okt-A |
| 4 | `Db/D` | ½ | T2+½ | D D♭ F A♭ | D | Okt-B |
| 5 | `C/Db` | ½ | T3 | D♭ C E G | D♭ | Okt-A |
| 6 | `Db/D` | ½ | T3+½ | D D♭ F A♭ | D | Okt-B |
| 7 | `C/Db` | ½ | T4 | D♭ C E G | D♭ | Okt-A |
| 8 | `Db/D` | ½ | T4+½ | D D♭ F A♭ | D | Okt-B |
| 9 | `C/Db` | 1 | T5 | D♭ C E G | D♭ | Okt-A |
| 10 | `Db/D` | 1 | T6 | D D♭ F A♭ | D | Okt-B |
| 11 | `C/Db` | 1 | T7 | D♭ C E G | D♭ | Okt-A |
| 12 | `Db/D` | 1 | T8 | D D♭ F A♭ | D | Okt-B |

- **Wirkung:** Äußerste Zuspitzung (Z > 0,9), aber geordnet: zwei Klänge, regelmäßiger Wechsel.
- **Harmonisches Zentrum:** kein Zentrum
- **Bassführung:** Bass D♭–D Halbtonpendel.
- **Begleitformen:** JW-R25, JW-R09
- **Variation:** Kann beliebig lange stehen bleiben; Auflösung bei Bedarf in JW-H16 oder JW-H19.
- **Williams-Verfahren:** Eigene Konstruktion für die letzten 5–10 % des Unruhebereichs; Grundlage Richards „simultaneous/successive scales“. Quellen: S10.
- **Stimmungen:** Action

#### JW-H49 · Heroische Medianten-Rückung

- **XYZ-Anker:** 0,85 / 0,90 / 0,45 (HIm) · **Taktart:** 4/4 · **Tonvorrat:** Pantriadisch · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 2 | T1 | C E G | C | Pantriadisch |
| 2 | `E` | 2 | T3 | E A♭ B | E | Pantriadisch |
| 3 | `C` | 1 | T5 | C E G | C | Pantriadisch |
| 4 | `Ab` | 1 | T6 | A♭ C E♭ | A♭ | Pantriadisch |
| 5 | `Bb` | 1 | T7 | B♭ D F | B♭ | Pantriadisch |
| 6 | `C` | 1 | T8 | C E G | C | Pantriadisch |

- **Wirkung:** Triumph mit Überraschung; der Glanz kommt von einem unerwarteten Klang.
- **Harmonisches Zentrum:** C
- **Bassführung:** C–E–C–A♭–B♭–C.
- **Begleitformen:** JW-R31, JW-R10, JW-R01
- **Variation:** E als Rückung (bleibt dort) statt Rückkehr.
- **Williams-Verfahren:** Fanfaren verbinden kontrastierende Tonarten (Amblard, IRCAM); chromatische Medianten (Lehman). Quellen: S22, S4.
- **Stimmungen:** Heroik, Epische Weite

#### JW-H50 · Pantriadisches Staunen über Pedal

- **XYZ-Anker:** 0,75 / 0,40 / 0,50 (Hmm) · **Taktart:** 4/4 · **Tonvorrat:** Hex-C · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cmaj7` | 2 | T1 | C E G B | C | Hex-C |
| 2 | `Ab/C` | 1 | T3 | C A♭ E♭ | C | Hex-C |
| 3 | `E/C` | 1 | T4 | C E A♭ B | C | Hex-C |
| 4 | `Ab/C` | 1 | T5 | C A♭ E♭ | C | Hex-C |
| 5 | `E/C` | 1 | T6 | C E A♭ B | C | Hex-C |
| 6 | `Cmaj7` | 2 | T7 | C E G B | C | Hex-C |

- **Wirkung:** Staunen mit leichtem Schauer; Klänge wechseln auf großer Terz über liegendem C.
- **Harmonisches Zentrum:** C
- **Bassführung:** Pedal C.
- **Begleitformen:** JW-R15, JW-R14, JW-R12
- **Variation:** E/C mit zusätzlichem F♯ (lydisch gefärbt) [systemfremd: F♯ liegt nicht in Hex-C].
- **Williams-Verfahren:** Nicht-funktionale pantriadische Chromatik als Klang des Wunders (Lehman 2018). Quellen: S4.
- **Stimmungen:** Staunen, Magie

#### JW-H51 · Scherzando-Chromatik

- **XYZ-Anker:** 0,75 / 0,50 / 0,70 (HmU) · **Taktart:** 4/4 · **Tonvorrat:** Pantriadisch · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 1 | T1 | C E G | C | Pantriadisch |
| 2 | `Eb` | 1 | T2 | E♭ G B♭ | E♭ | Pantriadisch |
| 3 | `C` | 1 | T3 | C E G | C | Pantriadisch |
| 4 | `Ab` | 1 | T4 | A♭ C E♭ | A♭ | Pantriadisch |
| 5 | `F` | 1 | T5 | F A C | F | Pantriadisch |
| 6 | `Db` | 1 | T6 | D♭ F A♭ | D♭ | Pantriadisch |
| 7 | `G7` | 1 | T7 | G B D F | G | Pantriadisch |
| 8 | `C` | 1 | T8 | C E G | C | Pantriadisch |

- **Wirkung:** Verspielt, frech; Ausflüge mit sicherer Heimkehr.
- **Harmonisches Zentrum:** C
- **Bassführung:** C–E♭–C–A♭–F–D♭–G–C, staccato.
- **Begleitformen:** JW-R33, JW-R17
- **Variation:** Db durch Gb (Tritonus) für mehr Witz.
- **Williams-Verfahren:** Jar-Jar-Material voller chromatischer Abschweifungen und Überraschungen (Lehman 28). Quellen: S1.
- **Stimmungen:** Verspieltheit

#### JW-H52 · Marsch mit einem chromatischen Moment

- **XYZ-Anker:** 0,80 / 0,45 / 0,45 (Hmm) · **Taktart:** 4/4 · **Tonvorrat:** Pantriadisch · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 1 | T1 | C E G | C | Pantriadisch |
| 2 | `F` | 1 | T2 | F A C | F | Pantriadisch |
| 3 | `D7/F#` | 1 | T3 | F♯ D A C | F♯ | Pantriadisch |
| 4 | `G` | 1 | T4 | G B D | G | Pantriadisch |
| 5 | `C` | 1 | T5 | C E G | C | Pantriadisch |
| 6 | `F` | 1 | T6 | F A C | F | Pantriadisch |
| 7 | `F#dim7` | 1 | T7 | F♯ A C E♭ | F♯ | Pantriadisch |
| 8 | `C/G` | 1 | T8 | G C E | G | Pantriadisch |

- **Wirkung:** Gutmütige, mechanische Verspieltheit.
- **Harmonisches Zentrum:** C
- **Bassführung:** C–F–F♯–G–C–F–F♯–G (♯4 als einziger chromatischer Ton).
- **Begleitformen:** JW-R33, JW-R24
- **Variation:** Takt 7 nur als Durchgangsbass.
- **Williams-Verfahren:** Droid-Marsch: tritonales ♯4→1 als einziger chromatischer Moment (Lehman 26). Quellen: S1.
- **Stimmungen:** Verspieltheit, Wärme

#### JW-H53 · Aeolisch-phrygischer Action-Halbtaktwechsel

- **XYZ-Anker:** 0,30 / 0,80 / 0,60 (DIm) · **Taktart:** 4/4 · **Tonvorrat:** Äolisch → Phrygisch → Moll harm. · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | ½ | T1 | C E♭ G | C | Äolisch |
| 2 | `Ab` | ½ | T1+½ | A♭ C E♭ | A♭ | Äolisch |
| 3 | `Bb` | ½ | T2 | B♭ D F | B♭ | Äolisch |
| 4 | `Cm` | ½ | T2+½ | C E♭ G | C | Äolisch |
| 5 | `Cm` | ½ | T3 | C E♭ G | C | Äolisch |
| 6 | `Db` | ½ | T3+½ | D♭ F A♭ | D♭ | Phrygisch |
| 7 | `Bb` | ½ | T4 | B♭ D F | B♭ | Äolisch |
| 8 | `Cm` | ½ | T4+½ | C E♭ G | C | Äolisch |
| 9 | `Ab` | ½ | T5 | A♭ C E♭ | A♭ | Äolisch |
| 10 | `Bb` | ½ | T5+½ | B♭ D F | B♭ | Äolisch |
| 11 | `Cm` | ½ | T6 | C E♭ G | C | Äolisch |
| 12 | `Eb` | ½ | T6+½ | E♭ G B♭ | E♭ | Äolisch |
| 13 | `Db` | ½ | T7 | D♭ F A♭ | D♭ | Phrygisch |
| 14 | `Bb` | ½ | T7+½ | B♭ D F | B♭ | Äolisch |
| 15 | `G` | 1 | T8 | G B D | G | Moll harm. |

- **Wirkung:** Heldenhafter Kampf in Moll; schneller harmonischer Rhythmus.
- **Harmonisches Zentrum:** C-Moll/phrygisch
- **Bassführung:** Grundtöne in Halben; Takt 8 G.
- **Begleitformen:** JW-R03, JW-R23, JW-R01
- **Variation:** Takt 8 G als Dissonanzbass G unter Ab.
- **Williams-Verfahren:** Hauptthema in der Schlacht von Yavin von Dur/Mixolydisch nach Moll/Phrygisch umgefärbt (Lehman). Quellen: S1.
- **Stimmungen:** Action, Heroik, Dramatische Spannung

#### JW-H54 · Oktatonische Moll-Parallelterzen über Pedal

- **XYZ-Anker:** 0,25 / 0,45 / 0,70 (DmU) · **Taktart:** 4/4 · **Tonvorrat:** Okt-A · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 2 | T1 | C E♭ G | C | Okt-A |
| 2 | `Ebm/C` | 2 | T3 | C E♭ F♯ B♭ | C | Okt-A |
| 3 | `F#m/C` | 2 | T5 | C F♯ A D♭ | C | Okt-A |
| 4 | `Cm` | 2 | T7 | C E♭ G | C | Okt-A |

- **Wirkung:** Nervöses Schwirren, Lauern mit Energie.
- **Harmonisches Zentrum:** C
- **Bassführung:** Pedal C.
- **Begleitformen:** JW-R26, JW-R07, JW-R04
- **Variation:** Klänge halbtaktig, Pedal pausiert.
- **Williams-Verfahren:** Kopfgeldjäger-Motiv vollständig oktatonisch mit fast nur kleinen Terzen (Lehman 14); Space Battle Vamp synkopiert in Moll-Parallelterzen. Quellen: S1.
- **Stimmungen:** Lauern, Unbehagen, Dramatische Spannung

#### JW-H55 · Epische Breite mit langem harmonischem Rhythmus

- **XYZ-Anker:** 0,70 / 0,55 / 0,20 (HmS) · **Taktart:** 4/4 · **Tonvorrat:** Dur-Moll-Mischung · **Kategorie:** universell · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 4 | T1 | C E G | C | Dur-Moll-Mischung |
| 2 | `Ab` | 2 | T5 | A♭ C E♭ | A♭ | Dur-Moll-Mischung |
| 3 | `Bb` | 2 | T7 | B♭ D F | B♭ | Dur-Moll-Mischung |

- **Wirkung:** Weite Landschaft, Ankunft eines großen Moments; jeder Klang darf atmen.
- **Harmonisches Zentrum:** C (offen zu C)
- **Bassführung:** Grundtöne in Ganzen; B♭→C als Fortsetzung.
- **Begleitformen:** JW-R12, JW-R13, JW-R14
- **Variation:** Ab als Ab/C, Bb als Bb/C (Pedalfassung).
- **Williams-Verfahren:** Langer harmonischer Rhythmus über breiten Flächen; ♭VI–♭VII als modale Mischung (Schneller). Quellen: S6.
- **Stimmungen:** Epische Weite, Heroik

#### JW-H56 · Archaische Mollkadenz

- **XYZ-Anker:** 0,20 / 0,75 / 0,25 (DIS) · **Taktart:** 4/4 · **Tonvorrat:** Äolisch · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 2 | T1 | C E♭ G | C | Äolisch |
| 2 | `Bb` | 1 | T3 | B♭ D F | B♭ | Äolisch |
| 3 | `Cm` | 1 | T4 | C E♭ G | C | Äolisch |
| 4 | `Fm` | 1 | T5 | F A♭ C | F | Äolisch |
| 5 | `Ab` | 1 | T6 | A♭ C E♭ | A♭ | Äolisch |
| 6 | `Gm` | 1 | T7 | G B♭ D | G | Äolisch |
| 7 | `Cm` | 1 | T8 | C E♭ G | C | Äolisch |

- **Wirkung:** Dunkle, feierliche Macht; kraftvoll, aber harmonisch fest – kein Leitton, keine Chromatik.
- **Harmonisches Zentrum:** C äolisch
- **Bassführung:** C–B♭–C–F–A♭–G–C, Grundtöne in Ganzen.
- **Begleitformen:** JW-R31, JW-R12, JW-R35
- **Variation:** Gm durch Bbsus2/G; als Choral in Halben.
- **Williams-Verfahren:** Lade-Thema mit „archaischen Kadenzen“ und Oszillation zwischen Mollklängen, Gral-Thema mit kirchlich klingenden Kadenzen (Lehman, IJ-Katalog); Moll-v statt V als archaische Farbe. Quellen: S2.
- **Stimmungen:** Angst, Epische Weite, Geheimnis

#### JW-H57 · Schweres Moll über Orgelpunkt

- **XYZ-Anker:** 0,15 / 0,85 / 0,20 (DIS) · **Taktart:** 4/4 · **Tonvorrat:** Äolisch · **Kategorie:** universell · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 2 | T1 | C E♭ G | C | Äolisch |
| 2 | `Ab/C` | 2 | T3 | C A♭ E♭ | C | Äolisch |
| 3 | `Fm/C` | 2 | T5 | C F A♭ | C | Äolisch |
| 4 | `Cm` | 2 | T7 | C E♭ G | C | Äolisch |

- **Wirkung:** Bedrohliche Ruhe vor dem Sturm: laut, dunkel, aber ohne Unruhe.
- **Harmonisches Zentrum:** C-Moll
- **Bassführung:** Pedal C in Ganzen, Oktavverdopplung.
- **Begleitformen:** JW-R31, JW-R13, JW-R35
- **Variation:** Fm/C durch Fm6/C.
- **Williams-Verfahren:** Pedale unter Mollklängen; eigene Konstruktion für den Bereich dunkel-kraftvoll-stabil. Keine direkte Quelle.
- **Stimmungen:** Angst, Epische Weite

### C.2 Ergänzung für die schwach besetzten Bereiche (JW-H58–H76)

| Bereich | Vorlagen |
|---|---|
| HRU (hell, zurückhaltend, unruhig) | JW-H58, JW-H59, JW-H60, JW-H61, JW-H75 |
| HIU (hell, kraftvoll, unruhig) | JW-H62, JW-H63, JW-H64, JW-H65, JW-H66 |
| DIS (dunkel, kraftvoll, stabil) | JW-H67, JW-H68, JW-H69 |
| DRU (dunkel, zurückhaltend, unruhig) | JW-H71, JW-H72, JW-H73, JW-H74 |
| DIU (dunkel, kraftvoll, unruhig) | JW-H70, JW-H76 |

#### JW-H58 · Staccato-Planing über Pedal

- **XYZ-Anker:** 0,75 / 0,25 / 0,70 (HRU) · **Taktart:** 4/4 · **Tonvorrat:** Pantriadisch · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 1 | T1 | C E G | C | Pantriadisch |
| 2 | `D/C` | 1 | T2 | C D F♯ A | C | Pantriadisch |
| 3 | `E/C` | 1 | T3 | C E A♭ B | C | Pantriadisch |
| 4 | `D/C` | 1 | T4 | C D F♯ A | C | Pantriadisch |
| 5 | `C` | 1 | T5 | C E G | C | Pantriadisch |
| 6 | `Bb/C` | 1 | T6 | C B♭ D F | C | Pantriadisch |
| 7 | `Ab/C` | 1 | T7 | C A♭ E♭ | C | Pantriadisch |
| 8 | `Bb/C` | 1 | T8 | C B♭ D F | C | Pantriadisch |

- **Wirkung:** Neugierig, verschmitzt, leicht nervös; Durdreiklänge wandern parallel über einem liegenden C.
- **Harmonisches Zentrum:** C (Pedal)
- **Bassführung:** Pedal C; über D/C und E/C entsteht ein Dissonanzbass (C ist kein Akkordton).
- **Begleitformen:** JW-R42, JW-R39, JW-R33
- **Variation:** Planing abwärts beginnen (C–B♭–A♭); Bass als Oom-pah (JW-B31) statt Pedal.
- **Williams-Verfahren:** Jawas: gedämpftes Blech plant Dreiklänge über beweglichem, dissonantem Bass; Happy Landings: Planing von Durdreiklängen über Tonikapedal (Lehman, Kat. 7b, 40). Quellen: S24.
- **Stimmungen:** Verspieltheit, Staunen, Geheimnis

#### JW-H59 · Lydisch-♯2-Farbe

- **XYZ-Anker:** 0,70 / 0,30 / 0,65 (HRU) · **Taktart:** 4/4 · **Tonvorrat:** Lydisch-♯2 · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 2 | T1 | C E G | C | Lydisch-♯2 |
| 2 | `Am/C` | 1 | T3 | C A E | C | Lydisch-♯2 |
| 3 | `C` | 1 | T4 | C E G | C | Lydisch-♯2 |
| 4 | `B/C` | 1 | T5 | C B E♭ F♯ | C | Lydisch-♯2 |
| 5 | `C` | 1 | T6 | C E G | C | Lydisch-♯2 |
| 6 | `Em/C` | 1 | T7 | C E G B | C | Lydisch-♯2 |
| 7 | `C` | 1 | T8 | C E G | C | Lydisch-♯2 |

- **Wirkung:** Fremdartige, helle Neugier; Dur mit übermäßiger Sekunde und übermäßiger Quarte.
- **Harmonisches Zentrum:** C
- **Bassführung:** Pedal C; B/C als scharfe Reibung (Bass unter Leittonklang).
- **Begleitformen:** JW-R40, JW-R42, JW-R11
- **Variation:** Am/C durch F♯m7b5/C (F♯ A C E, im Vorrat); B/C nur halbtaktig.
- **Williams-Verfahren:** Jawas-Thema folgt teilweise einer lydisch-♯9-Skala, mit tritonusreicher Harmonisierung über Oom-pah-Bass (Lehman, Kat. 7). Quellen: S24.
- **Stimmungen:** Magie, Verspieltheit, Geheimnis

#### JW-H60 · Maj7-Plagalpendel mit parallelem Abstieg

- **XYZ-Anker:** 0,75 / 0,35 / 0,55 (HRm) · **Taktart:** 4/4 · **Tonvorrat:** Pantriadisch · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cmaj7` | 1 | T1 | C E G B | C | Pantriadisch |
| 2 | `Fmaj7` | 1 | T2 | F A C E | F | Pantriadisch |
| 3 | `Cmaj7` | 1 | T3 | C E G B | C | Pantriadisch |
| 4 | `Fmaj7` | 1 | T4 | F A C E | F | Pantriadisch |
| 5 | `Eb` | 1 | T5 | E♭ G B♭ | E♭ | Pantriadisch |
| 6 | `D` | 1 | T6 | D F♯ A | D | Pantriadisch |
| 7 | `Db` | 1 | T7 | D♭ F A♭ | D♭ | Pantriadisch |
| 8 | `C` | 1 | T8 | C E G | C | Pantriadisch |

- **Wirkung:** Weise, leicht schelmische Helligkeit; Pendel I↔IV, dann eine Kette paralleler Durklänge abwärts.
- **Harmonisches Zentrum:** C
- **Bassführung:** C–F–C–F, dann chromatisch E♭–D–D♭–C (parallel zur Oberstimme).
- **Begleitformen:** JW-R39, JW-R14, JW-R45
- **Variation:** Abstieg in Ganztönen (E♭–D♭–B–A).
- **Williams-Verfahren:** Yoda B: Oszillation von maj7-Akkorden im plagalen Verhältnis IV↔I, abwärts laufende Kette paralleler Durakkorde, hohe Holzbläser (Lehman, Kat. 12b). Quellen: S24.
- **Stimmungen:** Verspieltheit, Wärme, Magie

#### JW-H61 · Sus-Farbwechsel über Pedal

- **XYZ-Anker:** 0,70 / 0,20 / 0,60 (HRm) · **Taktart:** 4/4 · **Tonvorrat:** Pantriadisch · **Kategorie:** universell · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Csus2` | 1 | T1 | C D G | C | Pantriadisch |
| 2 | `Dsus2/C` | 1 | T2 | C D E A | C | Pantriadisch |
| 3 | `Fsus2/C` | 1 | T3 | C F G | C | Pantriadisch |
| 4 | `Ebsus2/C` | 1 | T4 | C E♭ F B♭ | C | Pantriadisch |
| 5 | `Csus2` | 1 | T5 | C D G | C | Pantriadisch |
| 6 | `Absus2/C` | 1 | T6 | C A♭ B♭ E♭ | C | Pantriadisch |
| 7 | `Bbsus2/C` | 1 | T7 | C B♭ F | C | Pantriadisch |
| 8 | `Csus2` | 1 | T8 | C D G | C | Pantriadisch |

- **Wirkung:** Leise, bewegliche Helligkeit; jeder Takt eine andere Farbe, nie eine Auflösung.
- **Harmonisches Zentrum:** C (Pedal)
- **Bassführung:** Pedal C.
- **Begleitformen:** JW-R40, JW-R14, JW-R11
- **Variation:** Nur die hellen Farben (D, F) für X > 0,8.
- **Williams-Verfahren:** Parallele, nicht-funktionale Klangfarben über Pedal (Planing-Prinzip); sus-Klänge als häufige Akkordtypen im Star-Wars-Themenkorpus (Arthur/Lehman/McNamara). Folge eigene Konstruktion. Quellen: S27, S24.
- **Stimmungen:** Staunen, Geheimnis

#### JW-H62 · Lydische I↔II-Schleife

- **XYZ-Anker:** 0,90 / 0,80 / 0,65 (HIU) · **Taktart:** 4/4 · **Tonvorrat:** Lydisch · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | ½ | T1 | C E G | C | Lydisch |
| 2 | `D` | ½ | T1+½ | D F♯ A | D | Lydisch |
| 3 | `C` | ½ | T2 | C E G | C | Lydisch |
| 4 | `D` | ½ | T2+½ | D F♯ A | D | Lydisch |
| 5 | `C` | ½ | T3 | C E G | C | Lydisch |
| 6 | `D` | ½ | T3+½ | D F♯ A | D | Lydisch |
| 7 | `C` | ½ | T4 | C E G | C | Lydisch |
| 8 | `D` | ½ | T4+½ | D F♯ A | D | Lydisch |
| 9 | `C` | ½ | T5 | C E G | C | Lydisch |
| 10 | `D` | ½ | T5+½ | D F♯ A | D | Lydisch |
| 11 | `C` | ½ | T6 | C E G | C | Lydisch |
| 12 | `D` | ½ | T6+½ | D F♯ A | D | Lydisch |
| 13 | `Em` | 1 | T7 | E G B | E | Lydisch |
| 14 | `D` | 1 | T8 | D F♯ A | D | Lydisch |

- **Wirkung:** Siegesfreude in Bewegung; zwei helle Klänge kreisen, die Phrase kann beliebig lange laufen.
- **Harmonisches Zentrum:** C lydisch
- **Bassführung:** C–D halbtaktig, Takt 7–8 E–D (offen, Schleifenanschluss).
- **Begleitformen:** JW-R37, JW-R48, JW-R38
- **Variation:** Ganztaktig für weniger Unruhe; Takt 8 als C statt D (geschlossen).
- **Williams-Verfahren:** Victory Fanfare: „textbook lydian“, Harmonie als I↔II♯-Schleife, kurze wiederholbare Fanfare (Lehman, Kat. 22). Quellen: S24.
- **Stimmungen:** Heroik, Abenteuer

#### JW-H63 · Mixolydische Maj7-Farbe ohne Dominante

- **XYZ-Anker:** 0,80 / 0,60 / 0,50 (Hmm) · **Taktart:** 4/4 · **Tonvorrat:** Pantriadisch · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cmaj7` | 2 | T1 | C E G B | C | Pantriadisch |
| 2 | `Fmaj7` | 1 | T3 | F A C E | F | Pantriadisch |
| 3 | `Bbmaj7` | 1 | T4 | B♭ D F A | B♭ | Pantriadisch |
| 4 | `Cmaj7` | 1 | T5 | C E G B | C | Pantriadisch |
| 5 | `Dbmaj7` | 1 | T6 | D♭ F A♭ C | D♭ | Pantriadisch |
| 6 | `Bbmaj7` | 1 | T7 | B♭ D F A | B♭ | Pantriadisch |
| 7 | `Cmaj7` | 1 | T8 | C E G B | C | Pantriadisch |

- **Wirkung:** Schwebende Pracht in Bewegung; die Tonika wird durch IV, ♭VII und ♭II verlängert, nie durch V.
- **Harmonisches Zentrum:** C
- **Bassführung:** C–F–B♭–C–D♭–B♭–C.
- **Begleitformen:** JW-R37, JW-R14, JW-R48
- **Variation:** Dbmaj7 durch Bb6 (weniger fremd).
- **Williams-Verfahren:** Cloud City: Dur mit mixolydischer Harmonisierung, fast alle Akkorde mit großer Septime, vermeidet die Dominante zugunsten von IV, ♭VII, ♭II (Lehman, Kat. 15). Quellen: S24.
- **Stimmungen:** Staunen, Abenteuer, Epische Weite

#### JW-H64 · Dur-Planing über Pedal mit Großterzrückung

- **XYZ-Anker:** 0,85 / 0,85 / 0,60 (HIm) · **Taktart:** 4/4 · **Tonvorrat:** Pantriadisch · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | ½ | T1 | C E G | C | Pantriadisch |
| 2 | `Bb/C` | ½ | T1+½ | C B♭ D F | C | Pantriadisch |
| 3 | `Ab/C` | ½ | T2 | C A♭ E♭ | C | Pantriadisch |
| 4 | `Bb/C` | ½ | T2+½ | C B♭ D F | C | Pantriadisch |
| 5 | `C` | ½ | T3 | C E G | C | Pantriadisch |
| 6 | `D/C` | ½ | T3+½ | C D F♯ A | C | Pantriadisch |
| 7 | `Eb/C` | ½ | T4 | C E♭ G B♭ | C | Pantriadisch |
| 8 | `F/C` | ½ | T4+½ | C F A | C | Pantriadisch |
| 9 | `E` | ½ | T5 | E A♭ B | E | Pantriadisch |
| 10 | `D/E` | ½ | T5+½ | E D F♯ A | E | Pantriadisch |
| 11 | `C/E` | ½ | T6 | E C G | E | Pantriadisch |
| 12 | `D/E` | ½ | T6+½ | E D F♯ A | E | Pantriadisch |
| 13 | `E` | ½ | T7 | E A♭ B | E | Pantriadisch |
| 14 | `F#/E` | ½ | T7+½ | E F♯ B♭ D♭ | E | Pantriadisch |
| 15 | `G/E` | ½ | T8 | E G B D | E | Pantriadisch |
| 16 | `A/E` | ½ | T8+½ | E A D♭ | E | Pantriadisch |

- **Wirkung:** Strahlendes Abenteuer; Klänge folgen der Melodie im Gleichschritt, dann springt alles eine große Terz höher.
- **Harmonisches Zentrum:** C → E
- **Bassführung:** Pedal C (Takt 1–4), Pedal E (Takt 5–8).
- **Begleitformen:** JW-R48, JW-R37, JW-R09
- **Variation:** Rückung abwärts (nach A♭) für dunklere Wendung.
- **Williams-Verfahren:** Happy Landings: parallele Durdreiklänge in Grundstellung über statischem Tonikapedal, am Ende Rückung um eine chromatische große Terz aufwärts (Lehman, Kat. 40). Quellen: S24.
- **Stimmungen:** Abenteuer, Heroik, Action

#### JW-H65 · Sus- und Quartenpuls

- **XYZ-Anker:** 0,75 / 0,75 / 0,70 (HIU) · **Taktart:** 4/4 · **Tonvorrat:** Mixolydisch · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Csus4` | ½ | T1 | C F G | C | Mixolydisch |
| 2 | `Csus2` | ½ | T1+½ | C D G | C | Mixolydisch |
| 3 | `Bbsus2` | 1 | T2 | B♭ C F | B♭ | Mixolydisch |
| 4 | `Fsus2` | ½ | T3 | F G C | F | Mixolydisch |
| 5 | `Gsus4` | ½ | T3+½ | G C D | G | Mixolydisch |
| 6 | `Csus2` | 1 | T4 | C D G | C | Mixolydisch |
| 7 | `Csus4` | ½ | T5 | C F G | C | Mixolydisch |
| 8 | `Csus2` | ½ | T5+½ | C D G | C | Mixolydisch |
| 9 | `Bbsus2` | 1 | T6 | B♭ C F | B♭ | Mixolydisch |
| 10 | `Fsus2` | ½ | T7 | F G C | F | Mixolydisch |
| 11 | `Gsus4` | ½ | T7+½ | G C D | G | Mixolydisch |
| 12 | `Csus2` | 1 | T8 | C D G | C | Mixolydisch |

- **Wirkung:** Drängende Helligkeit ohne Leittonziel; offen klingende Klänge, unregelmäßig betont.
- **Harmonisches Zentrum:** C mixolydisch
- **Bassführung:** C–C–B♭–F–G–C (wiederholt).
- **Begleitformen:** JW-R38, JW-R37, JW-R48
- **Variation:** Gsus4 als Gq (reiner Quartenklang).
- **Williams-Verfahren:** Finn/Pursuit: schneller unregelmäßiger Puls, getragen von sus- und Quartenklängen (Lehman, Kat. 50). Quellen: S24.
- **Stimmungen:** Abenteuer, Action

#### JW-H66 · Hexatonische Halbtonrutsche in Durklängen

- **XYZ-Anker:** 0,70 / 0,70 / 0,65 (HIU) · **Taktart:** 4/4 · **Tonvorrat:** Hex-C · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | ½ | T1 | C E G | C | Hex-C |
| 2 | `E/B` | ½ | T1+½ | B E A♭ | B | Hex-C |
| 3 | `C` | 1 | T2 | C E G | C | Hex-C |
| 4 | `Ab` | ½ | T3 | A♭ C E♭ | A♭ | Hex-C |
| 5 | `E/G#` | ½ | T3+½ | A♭ E B | A♭ | Hex-C |
| 6 | `Ab` | 1 | T4 | A♭ C E♭ | A♭ | Hex-C |
| 7 | `E` | ½ | T5 | E A♭ B | E | Hex-C |
| 8 | `Ab/Eb` | ½ | T5+½ | E♭ A♭ C | E♭ | Hex-C |
| 9 | `E` | 1 | T6 | E A♭ B | E | Hex-C |
| 10 | `C` | ½ | T7 | C E G | C | Hex-C |
| 11 | `E/B` | ½ | T7+½ | B E A♭ | B | Hex-C |
| 12 | `C` | 1 | T8 | C E G | C | Hex-C |

- **Wirkung:** Federnde, helle Unruhe; Dur, aber immer einen Halbton daneben.
- **Harmonisches Zentrum:** C
- **Bassführung:** C–B–C, A♭–G♯–A♭, E–E♭–E, C–B–C (Bass taucht jeweils einen Halbton ab).
- **Begleitformen:** JW-R37, JW-R44, JW-R09
- **Variation:** Rutsche aufwärts statt abwärts (C–C♯ wäre systemfremd; daher nur Bassrutsche).
- **Williams-Verfahren:** Semitonal Slip: wiederholte Halbton-Tauchgeste in parallelen großen Terzen, hexatonische Implikation (Lehman, Kat. 27, Asteroid Field). Quellen: S24.
- **Stimmungen:** Abenteuer, Action, Verspieltheit

#### JW-H67 · Tritonusoszillation mit stufenweisem Abstieg

- **XYZ-Anker:** 0,15 / 0,75 / 0,35 (DIS) · **Taktart:** 4/4 · **Tonvorrat:** Pantriadisch · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 1 | T1 | C E♭ G | C | Pantriadisch |
| 2 | `F#m` | 1 | T2 | F♯ A D♭ | F♯ | Pantriadisch |
| 3 | `Cm` | 1 | T3 | C E♭ G | C | Pantriadisch |
| 4 | `F#m` | 1 | T4 | F♯ A D♭ | F♯ | Pantriadisch |
| 5 | `Bbm` | 1 | T5 | B♭ D♭ F | B♭ | Pantriadisch |
| 6 | `Abm` | 1 | T6 | A♭ B E♭ | A♭ | Pantriadisch |
| 7 | `Gm` | 1 | T7 | G B♭ D | G | Pantriadisch |
| 8 | `Cm` | 1 | T8 | C E♭ G | C | Pantriadisch |

- **Wirkung:** Dunkle, unausweichliche Größe; zwei Mollklänge im Tritonusabstand, dann ein langsamer Abstieg.
- **Harmonisches Zentrum:** C-Moll
- **Bassführung:** C–F♯–C–F♯–B♭–A♭–G–C in Ganzen, tiefe Lage.
- **Begleitformen:** JW-R46, JW-R45, JW-R43
- **Variation:** Takt 5–7 als Kleinterzkette (C–E♭–F♯) für die Steigerung.
- **Williams-Verfahren:** Lade-Thema: fast nur Molldreiklänge, Leitharmonie als Tritonusoszillation zwischen Tonika und T6, zweite Phrase stufenweise abwärts, archaische Kadenzen (Lehman, JFM 2012/13, S. 182–183; Kat.). Quellen: S25, S2.
- **Stimmungen:** Angst, Epische Weite, Geheimnis

#### JW-H68 · Chromatischer Mollchoral zum hexatonischen Polychord

- **XYZ-Anker:** 0,10 / 0,65 / 0,40 (DIm) · **Taktart:** 4/4 · **Tonvorrat:** Pantriadisch · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 2 | T1 | C E♭ G | C | Pantriadisch |
| 2 | `Bm` | 1 | T3 | B D F♯ | B | Pantriadisch |
| 3 | `Bbm` | 1 | T4 | B♭ D♭ F | B♭ | Pantriadisch |
| 4 | `Am` | 1 | T5 | A C E | A | Pantriadisch |
| 5 | `Abm` | 1 | T6 | A♭ B E♭ | A♭ | Pantriadisch |
| 6 | `E\|Cm` | 2 | T7 | C E♭ G E A♭ B | C | Pantriadisch |

- **Wirkung:** Trauerzug, Feierlichkeit mit Schrecken; langsame chromatische Grundtonschritte, Ziel ein Doppelklang.
- **Harmonisches Zentrum:** C-Moll
- **Bassführung:** C–B–B♭–A–A♭–C (Polychord über C).
- **Begleitformen:** JW-R46, JW-R35
- **Variation:** Bm/Bbm/Am mit kleiner Sexte (m(b6)) für mehr Reibung.
- **Williams-Verfahren:** Trauermarsch (Episode I): langsamer Melodieabstieg, innere Dissonanzen, chromatische Grundtonschritte zu hexatonisch-polarem Polychord (Lehman, Kat. 31). Quellen: S24.
- **Stimmungen:** Trauer, Angst, Epische Weite

#### JW-H69 · Dies-irae-Bass, choralartig (Typ 2)

- **XYZ-Anker:** 0,15 / 0,80 / 0,25 (DIS) · **Taktart:** 4/4 · **Tonvorrat:** Moll harm. · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 1 | T1 | C E♭ G | C | Moll harm. |
| 2 | `G/B` | 1 | T2 | B G D | B | Moll harm. |
| 3 | `Cm` | 1 | T3 | C E♭ G | C | Moll harm. |
| 4 | `Fm/Ab` | 1 | T4 | A♭ F C | A♭ | Moll harm. |
| 5 | `G/B` | 1 | T5 | B G D | B | Moll harm. |
| 6 | `Cm/G` | 1 | T6 | G C E♭ | G | Moll harm. |
| 7 | `Fm/Ab` | 1 | T7 | A♭ F C | A♭ | Moll harm. |
| 8 | `Ab` | 1 | T8 | A♭ C E♭ | A♭ | Moll harm. |

- **Wirkung:** Schwere, archaische Drohung; die Basslinie folgt der Dies-irae-Kontur mit erhöhter 7. Stufe.
- **Harmonisches Zentrum:** C-Moll (harmonisch)
- **Bassführung:** C–B–C–A♭–B–G–A♭–A♭ (Dies-irae-Anfang, Stufen 1–7–1–6–7–5–6–6).
- **Begleitformen:** JW-R43, JW-R46, JW-R35
- **Variation:** Typ 1 (nur Töne 1–4, sequenziert); Umkehrung (Typ 5) als Steigerung.
- **Williams-Verfahren:** Schneller: Dies-irae-Typ 2 (Segment y mit erhöhter 7. Stufe) lässt sich in oktatonische und harmonisch-moll Tonfelder einfügen; Einsatz als Begleitfigur oder Bassmotiv (Émergences 2025). Der gregorianische Hymnus ist gemeinfrei. Quellen: S28.
- **Stimmungen:** Angst, Dramatische Spannung, Epische Weite

#### JW-H70 · Planing erster Umkehrungen in Moll

- **XYZ-Anker:** 0,20 / 0,70 / 0,55 (DIm) · **Taktart:** 4/4 · **Tonvorrat:** Pantriadisch · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm/Eb` | 1 | T1 | E♭ C G | E♭ | Pantriadisch |
| 2 | `C#m/E` | 1 | T2 | E D♭ A♭ | E | Pantriadisch |
| 3 | `Dm/F` | 1 | T3 | F D A | F | Pantriadisch |
| 4 | `C#m/E` | 1 | T4 | E D♭ A♭ | E | Pantriadisch |
| 5 | `Cm/Eb` | 1 | T5 | E♭ C G | E♭ | Pantriadisch |
| 6 | `Bm/D` | 1 | T6 | D B F♯ | D | Pantriadisch |
| 7 | `Bbm/Db` | 1 | T7 | D♭ B♭ F | D♭ | Pantriadisch |
| 8 | `Bm/D` | 1 | T8 | D B F♯ | D | Pantriadisch |

- **Wirkung:** Schleichende, gewaltbereite Bedrohung; Mollsextakkorde folgen einer chromatischen Linie im Gleichschritt.
- **Harmonisches Zentrum:** kein festes Zentrum (C als Rahmen)
- **Bassführung:** Bass E♭–E–F–E–E♭–D–D♭–D (Terzbass, chromatisch).
- **Begleitformen:** JW-R43, JW-R25, JW-R46
- **Variation:** Halbtaktig für mehr Unruhe.
- **Williams-Verfahren:** Darth Maul: ausschließlich Moll-Sextakkorde, die einer chromatischen Melodielinie im Gleichschritt folgen; pantriadisch; tiefes Blech und Holz (Lehman, Kat. 27). Quellen: S24.
- **Stimmungen:** Angst, Lauern, Action

#### JW-H71 · Halbton-Mollpaar (überlagert)

- **XYZ-Anker:** 0,15 / 0,25 / 0,65 (DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 1 | T1 | C E♭ G | C | Chromatisch |
| 2 | `C#m\|Cm` | 1 | T2 | C E♭ G D♭ E A♭ | C | Chromatisch |
| 3 | `Cm` | 2 | T3 | C E♭ G | C | Chromatisch |
| 4 | `C#m\|Cm` | 1 | T5 | C E♭ G D♭ E A♭ | C | Chromatisch |
| 5 | `Cm` | 1 | T6 | C E♭ G | C | Chromatisch |
| 6 | `Bm\|Cm` | 1 | T7 | C E♭ G B D F♯ | C | Chromatisch |
| 7 | `Cm` | 1 | T8 | C E♭ G | C | Chromatisch |

- **Wirkung:** Lautloses Grauen; zwei Mollklänge einen Halbton auseinander schimmern ineinander.
- **Harmonisches Zentrum:** C-Moll
- **Bassführung:** Pedal C oder kein Bass.
- **Begleitformen:** JW-R47, JW-R36, JW-R45
- **Variation:** Paar im Tritonusabstand (F♯m|Cm, Okt-A) für die Map-Fassung.
- **Williams-Verfahren:** Sith-Dolch: Gegenüberstellung zweier Molldreiklänge im Halbtonabstand, Holzbläser (Lehman, Kat. 60b); Map-Thema: zwei pendelnde Mollklänge, die sich überlappen können (Kat. 48). Quellen: S24.
- **Stimmungen:** Angst, Geheimnis, Unbehagen

#### JW-H72 · Arpeggien mit Fremdton, stufenweise versetzt

- **XYZ-Anker:** 0,30 / 0,20 / 0,65 (DRU) · **Taktart:** 4/4 · **Tonvorrat:** Pantriadisch · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm(b6)` | 1 | T1 | C E♭ G A♭ | C | Pantriadisch |
| 2 | `Dm(addb9)` | 1 | T2 | D F A E♭ | D | Pantriadisch |
| 3 | `EbmM7` | 1 | T3 | E♭ F♯ B♭ D | E♭ | Pantriadisch |
| 4 | `Dm(b6)` | 1 | T4 | D F A B♭ | D | Pantriadisch |
| 5 | `Cm(addb9)` | 1 | T5 | C E♭ G D♭ | C | Pantriadisch |
| 6 | `BmM7` | 1 | T6 | B D F♯ B♭ | B | Pantriadisch |
| 7 | `Cm(b6)` | 1 | T7 | C E♭ G A♭ | C | Pantriadisch |
| 8 | `Cm` | 1 | T8 | C E♭ G | C | Pantriadisch |

- **Wirkung:** Rätselhafte Kälte; jedes Arpeggio hat einen Ton zu viel.
- **Harmonisches Zentrum:** C-Moll
- **Bassführung:** Grundtöne C–D–E♭–D–C–B–C–C.
- **Begleitformen:** JW-R45, JW-R15, JW-R47
- **Variation:** Nur aufwärts versetzen (C–D–E♭–F).
- **Williams-Verfahren:** Mystery (Kamino): jedes arpeggierte Moll enthält genau einen Zusatzton (♭6, ♯7 oder ♭9), aufeinanderfolgende Arpeggien stufenweise transponiert (Lehman, Kat. 34). Quellen: S24.
- **Stimmungen:** Geheimnis, Unbehagen, Magie

#### JW-H73 · Hohe Pedale, leise Reibungen

- **XYZ-Anker:** 0,35 / 0,10 / 0,55 (DRm) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C5` | 2 | T1 | C G | C | Chromatisch |
| 2 | `{C D G}` | 1 | T3 | C D G | C | Chromatisch |
| 3 | `C5` | 1 | T4 | C G | C | Chromatisch |
| 4 | `{C Db G}` | 1 | T5 | C D♭ G | C | Chromatisch |
| 5 | `C5` | 1 | T6 | C G | C | Chromatisch |
| 6 | `{B C G}` | 1 | T7 | B C G | B | Chromatisch |
| 7 | `Cmaj9` | 1 | T8 | C E G B D | C | Chromatisch |

- **Wirkung:** Lauschen im Schrank: fast nichts klingt, aber jede kleine Reibung zählt.
- **Harmonisches Zentrum:** C
- **Bassführung:** Kein durchgehender Bass; einzelne tiefe Töne als Einwurf (JW-B37).
- **Begleitformen:** JW-R47, JW-R40
- **Variation:** Schluss auf C5 statt Cmaj9 (offen).
- **Williams-Verfahren:** E.T., „The Closet“: nur Pedaltöne, fragmentarische Töne und leicht dissonante Harmonien, hohe Streicherpedale mit seltenen leisen Klaviereinzeltönen, Schluss auf CM9 (Normandie). Quellen: S26.
- **Stimmungen:** Lauern, Unbehagen, Geheimnis

#### JW-H74 · Leise Oktatonik: Mollklänge im Kleinterzabstand

- **XYZ-Anker:** 0,20 / 0,20 / 0,60 (DRm) · **Taktart:** 4/4 · **Tonvorrat:** Okt-A · **Kategorie:** Williams-Präferenz · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 2 | T1 | C E♭ G | C | Okt-A |
| 2 | `Ebm\|Cm` | 2 | T3 | C E♭ G F♯ B♭ | C | Okt-A |
| 3 | `Cm` | 1 | T5 | C E♭ G | C | Okt-A |
| 4 | `Am\|F#m` | 1 | T6 | F♯ A D♭ C E | F♯ | Okt-A |
| 5 | `Ebm\|Cm` | 1 | T7 | C E♭ G F♯ B♭ | C | Okt-A |
| 6 | `Cm` | 1 | T8 | C E♭ G | C | Okt-A |

- **Wirkung:** Gedämpfte Bedrohung; zwei Mollklänge teilen einen Ton und liegen ganz in einem oktatonischen Vorrat.
- **Harmonisches Zentrum:** C-Moll
- **Bassführung:** Pedal C oder Kleinterz-Pedalwechsel (JW-B40).
- **Begleitformen:** JW-R47, JW-R36, JW-R45
- **Variation:** Ebm|Cm als Arpeggio statt Klang (leiser).
- **Williams-Verfahren:** Leise Oktatonik belegt (Boba Fett in Fagotten, Imperials-Motiv in tiefen Holzbläsern; Lehman, Kat. 14, 6); Snow Battle mit Set 5-32 aus zwei Mollklängen im Kleinterzabstand (Sewell, sekundär); Deutung als Richards’ „Alpha“-Typ unbestätigt [H]. Quellen: S1, S35.
- **Stimmungen:** Lauern, Angst, Geheimnis

#### JW-H75 · Cluster öffnet sich zu Dur

- **XYZ-Anker:** 0,55 / 0,45 / 0,60 (mmm) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch → Dur · **Kategorie:** Verfahren mit Planung · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `{B C Db}` | 1 | T1 | B C D♭ | B | Chromatisch |
| 2 | `{Bb B C Db D}` | 1 | T2 | B♭ B C D♭ D | B♭ | Chromatisch |
| 3 | `{A Bb B C Db D Eb}` | 2 | T3 | A B♭ B C D♭ D E♭ | A | Chromatisch |
| 4 | `{G A B C D E}` | 1 | T5 | G A B C D E | G | Dur |
| 5 | `Cadd9` | 1 | T6 | C E G D | C | Dur |
| 6 | `C` | 2 | T7 | C E G | C | Dur |

- **Wirkung:** Vom Unbegreiflichen zum Licht: ein wachsender Cluster weicht einem klaren Dreiklang.
- **Harmonisches Zentrum:** Cluster → C
- **Bassführung:** Kein Bass bis Takt 5, dann C.
- **Begleitformen:** JW-R13, JW-R46
- **Variation:** Umgekehrt (Dur zerfällt zum Cluster) für Bedrohung.
- **Williams-Verfahren:** Close Encounters: registral und dynamisch wachsender chromatischer Cluster weicht einem C-Dur-Dreiklang; Polarität Cluster-Atonalität ↔ Tonalität (Schneller 2014, nur Auszug). Quellen: S29.
- **Stimmungen:** Staunen, Magie, Geheimnis

#### JW-H76 · Pantriadische Kleinterzkette zur überhöhten Kadenz

- **XYZ-Anker:** 0,30 / 0,55 / 0,55 (Dmm) · **Taktart:** 4/4 · **Tonvorrat:** Pantriadisch · **Kategorie:** Verfahren mit Planung · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 2 | T1 | C E♭ G | C | Pantriadisch |
| 2 | `Ebm` | 1 | T3 | E♭ F♯ B♭ | E♭ | Pantriadisch |
| 3 | `F#m` | 1 | T4 | F♯ A D♭ | F♯ | Pantriadisch |
| 4 | `Am` | 1 | T5 | A C E | A | Pantriadisch |
| 5 | `Cm` | 1 | T6 | C E♭ G | C | Pantriadisch |
| 6 | `G#7` | 1 | T7 | A♭ C E♭ F♯ | A♭ | Pantriadisch |
| 7 | `C#m` | 1 | T8 | D♭ E A♭ | D♭ | Pantriadisch |

- **Wirkung:** Zentrisches Moll löst sich in eine Kette und landet überhöht auf einem fremden Ziel.
- **Harmonisches Zentrum:** C-Moll → C♯-Moll
- **Bassführung:** C–E♭–F♯–A–C–G♯–C♯.
- **Begleitformen:** JW-R46, JW-R13, JW-R45
- **Variation:** Ziel cis-Moll als neue Tonika stehen lassen.
- **Williams-Verfahren:** Map Room: Dawn: zentrisches c-Moll, Kleinterzketten (c, es, fis), überbetonte Kadenz nach cis-Moll (Lehman, JFM 2012/13). Quellen: S25.
- **Stimmungen:** Staunen, Dramatische Spannung, Geheimnis

## D Rhythmisches Vokabular (48 Vorlagen)

Gleiches Tempo, andere Wirkung: Intensität und Unruhe entstehen aus Gruppierung, Akzentlage, Synkopen, Kreuzrhythmus und Pausen, nicht nur aus mehr Noten. Taktarten der Vorlagen gelten nur, wenn der Host diese Taktart vorgibt; eine Vorlage ändert nie die Taktart.

#### JW-R01 · Marsch-Grundrhythmus

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,55 / 0,70 / 0,40 (mIm) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  X..xX...X..xX.x.|X..xX...X.x.X---
ST  X...............|X.......X.......
```
- **Einsätze gesamt:** KF 13, ST 3 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KF, ST, KB
- **Harmonische Voraussetzung:** beliebig, bevorzugt 1–2 Akkorde pro Takt
- **Wirkung:** Militärische Entschlossenheit, punktierter Antrieb.
- **Varianten/Verdichtung:** Takt 2 als Fill ersetzen; ST nur jeden zweiten Durchgang.
- **Quellen:** S1

#### JW-R02 · Repetitions-Triolen

- **Taktart:** 4/4T (12 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,40 / 0,75 / 0,60 (mIm) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  XxxXxxXxxXxx|XxxXxxX--...
```
- **Einsätze gesamt:** KF 19 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KF, ST
- **Harmonische Voraussetzung:** ein Akkord pro Takt; Tonrepetition auf einem Akkordton
- **Wirkung:** Gespannte Erregung durch schnelle Tonrepetition (Repetitionstriolen im Hoth-Material; schnelle Blechrepetitionen als Williams-Merkmal).
- **Varianten/Verdichtung:** Nur Zählzeit 1 und 3 als Triole, sonst Viertel.
- **Quellen:** S1, S22

#### JW-R03 · Achtelmotor mit 3+3+2-Akzent

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,55 / 0,60 / 0,60 (mmm) · **Evidenz:** Verfahren [I], Raster [E]

```
AR  X.x.x.X.x.x.X.x.|X.x.x.X.x.x.X.x.
KB  X.....X.....X...|X.....X.....X...
```
- **Einsätze gesamt:** AR 16, KB 6 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** AR, KF, KB
- **Harmonische Voraussetzung:** Akkordwechsel höchstens pro Takt
- **Wirkung:** Vorwärtsdrang mit leichter Schieflage; verschobene Akzente halten den Hörer aus dem Gleichgewicht.
- **Varianten/Verdichtung:** Akzent auf 3+2+3 verschieben; KB nur auf Zählzeit 1.
- **Quellen:** S21, S1

#### JW-R04 · Synkopierte Militärfigur

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,45 / 0,75 / 0,70 (mIU) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  X..X..X.X..X.X..|X..X..X.X.......
ST  ..............X.|................
```
- **Einsätze gesamt:** KF 10, ST 1 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KF, ST, GS
- **Harmonische Voraussetzung:** Dur oder Moll, auch Quartenklänge
- **Wirkung:** Kampfeslust; die Synkope reißt nach vorne (Syncopated Military Figure, Yavin).
- **Varianten/Verdichtung:** Mit JW-R07 im Bass koppeln (Akzente decken sich auf 1).
- **Quellen:** S1

#### JW-R05 · Asymmetrisches 7/8-Ostinato (2+2+3)

- **Taktart:** 7/8 (14 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,35 / 0,70 / 0,70 (DIU) · **Evidenz:** Verfahren [N], Raster [E]

```
KB  X...X...X.x.x.|X...X...X.x.x.
ST  X.............|X.......X.....
```
- **Einsätze gesamt:** KB 10, ST 3 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KB, KF, ST
- **Harmonische Voraussetzung:** ein Klang über 2–4 Takte
- **Wirkung:** Drängende Schwere mit hinkendem Puls (Asymmetrical Martial Ostinato, Episode I).
- **Varianten/Verdichtung:** Gruppierung 3+2+2; KF auf die Dreiergruppe.
- **Quellen:** S1

#### JW-R06 · 5/4-Ostinato (3+2)

- **Taktart:** 5/4 (20 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,35 / 0,70 / 0,65 (DIU) · **Evidenz:** Verfahren [I], Raster [E]

```
KF  X.x.x.x.x.x.X.x.x.x.|X.x.x.x.x.x.X.x.x.x.
KB  X-----x.....X---x...|X-----x.....X---x...
```
- **Einsätze gesamt:** KF 20, KB 8 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KF, KB
- **Harmonische Voraussetzung:** ein Klang oder Pendel
- **Wirkung:** Unruhiger Marsch, der nie ganz aufgeht.
- **Varianten/Verdichtung:** 2+3 statt 3+2; im letzten Takt 4/4 einschieben.
- **Quellen:** S1

#### JW-R07 · Tiefes Sechzehntel-Ostinato 3+3+2

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,25 / 0,70 / 0,75 (DIU) · **Evidenz:** Verfahren [N], Raster [E]

```
KB  X-xX-xX-X-xX-xX-|X-xX-xX-X-xX-xX-
```
- **Einsätze gesamt:** KB 20 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KB (auch tiefes Klavier), AR
- **Harmonische Voraussetzung:** oktatonisch oder Moll, Pedal oder Zelle
- **Wirkung:** Bedrohlicher Motor (Hoth 3m3: Hauptostinato im tiefen Klavier).
- **Varianten/Verdichtung:** Akzente 3+3+3+3+2+2; zweite Hälfte eine Oktave tiefer.
- **Quellen:** S1

#### JW-R08 · Repetitionsakkord-Ostinato

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,30 / 0,65 / 0,70 (DIU) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  X.xxX.xxX.xxX.xx|X.xxX.xxX.x.X...
```
- **Einsätze gesamt:** KF 21 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KF
- **Harmonische Voraussetzung:** ein oktatonischer Klang
- **Wirkung:** Gespannter Stillstand, maschinell (Hoth 3m3: oktatonisches Repetitionsakkord-Ostinato).
- **Varianten/Verdichtung:** Nur Zählzeiten 1 und 3 mit Sechzehntelpaar.
- **Quellen:** S1

#### JW-R09 · Hetzende Sechzehntel mit Lücken

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,50 / 0,80 / 0,85 (mIU) · **Evidenz:** Verfahren [I], Raster [E]

```
AR  XxxxXxx.XxxxXx..|XxxxXxx.XxXxXxXx
```
- **Einsätze gesamt:** AR 28 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** AR, GS
- **Harmonische Voraussetzung:** schneller harmonischer Rhythmus möglich
- **Wirkung:** Verfolgung; die Lücken machen das Ostinato atemlos statt gleichförmig.
- **Varianten/Verdichtung:** Lücken verschieben; letzte Zählzeit als Abriss.
- **Quellen:** S1

#### JW-R10 · Fanfaren-Auftakt

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,80 / 0,80 / 0,30 (HIS) · **Evidenz:** Verfahren [I], Raster [E]

```
HM  X-----------.xxx|X---------------
ST  ................|X...............
```
- **Einsätze gesamt:** HM 5, ST 1 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** HM, KF, ST
- **Harmonische Voraussetzung:** Zielklang auf Takt 2
- **Wirkung:** Aufbruch, Signal; der Auftakt zielt auf den Klang.
- **Varianten/Verdichtung:** Auftakt als Triole (in 4/4T).
- **Quellen:** S1

#### JW-R11 · Verstreute Tupfer

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,40 / 0,25 / 0,55 (mRm) · **Evidenz:** Verfahren [I], Raster [E]

```
TU  x.....x...x.....|..x.....x.....x.
```
- **Einsätze gesamt:** TU 6 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** TU
- **Harmonische Voraussetzung:** beliebig
- **Wirkung:** Huschende Bewegung im Dunkeln (Pizzicato-Strom im Dschungel).
- **Varianten/Verdichtung:** Positionen pro Durchgang würfeln (nur gerade Schritte).
- **Quellen:** S20

#### JW-R12 · Atmende Liegefläche

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,50 / 0,20 / 0,20 (mRS) · **Evidenz:** Verfahren [U], Raster [E]

```
LF  X---------------|------------....
```
- **Einsätze gesamt:** LF 1 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** LF, LB
- **Harmonische Voraussetzung:** beliebig
- **Wirkung:** Ruhe, Raum für Dialog.
- **Varianten/Verdichtung:** Ende in Takt 2 auf Zählzeit 3 vorziehen.

#### JW-R13 · Anschwellende Fläche (4 Takte)

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,55 / 0,50 / 0,45 (mmm) · **Evidenz:** Verfahren [U], Raster [E]

```
LF  X---------------|----------------|X---------------|----------------
ST  ................|................|................|............X...
```
- **Einsätze gesamt:** LF 2, ST 1 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** LF, ST
- **Harmonische Voraussetzung:** ein Klang oder Pedal
- **Wirkung:** Erwartung, Spannungsaufbau ohne mehr Noten.
- **Varianten/Verdichtung:** Dynamik pp→f über 4 Takte; ST optional.

#### JW-R14 · Harfen-/Celesta-Achtel

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,75 / 0,30 / 0,35 (HRS) · **Evidenz:** Verfahren [N], Raster [E]

```
AR  X.x.x.x.x.x.x.x.|x.x.x.x.x.x.x.x.
```
- **Einsätze gesamt:** AR 16 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** AR
- **Harmonische Voraussetzung:** ein Klang pro Takt
- **Wirkung:** Zartes, glitzerndes Fließen (homorhythmisches Achtelostinato im E.T.-Flugthema).
- **Varianten/Verdichtung:** Nur die zweite Takthälfte; Richtung pro Takt wechseln.
- **Quellen:** S12, S20

#### JW-R15 · Aufsteigendes Sechzehntel-Arpeggio

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,60 / 0,45 / 0,60 (mmm) · **Evidenz:** Verfahren [N], Raster [E]

```
AR  XxxxXxxxXxxxXxxx|XxxxXxxxXxxx----
```
- **Einsätze gesamt:** AR 28 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** AR
- **Harmonische Voraussetzung:** Polychord oder hexatonischer Klang
- **Wirkung:** Sternenhimmel, Funkeln (polychordale Arpeggien, Starry Night).
- **Varianten/Verdichtung:** Nur aufwärts; zweite Hälfte als Haltenote.
- **Quellen:** S1

#### JW-R16 · 6/8-Wiegen

- **Taktart:** 6/8 (12 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,60 / 0,30 / 0,25 (mRS) · **Evidenz:** Verfahren [U], Raster [E]

```
AR  X.x.x.X.x.x.|X.x.x.X.x.x.
KB  X-----x-----|X-----......
```
- **Einsätze gesamt:** AR 12, KB 3 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** AR, KB, LF
- **Harmonische Voraussetzung:** ein Klang pro Takt
- **Wirkung:** Romantische Wiegebewegung.
- **Varianten/Verdichtung:** Bass nur auf 1.

#### JW-R17 · 3/4-Scherzo

- **Taktart:** 3/4 (12 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,75 / 0,45 / 0,50 (Hmm) · **Evidenz:** Verfahren [U], Raster [E]

```
KB  X...........|X...........
KF  ....x...x...|....x...x...
```
- **Einsätze gesamt:** KB 2, KF 4 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KB, KF
- **Harmonische Voraussetzung:** ein Klang pro Takt
- **Wirkung:** Verspielter Tanz.
- **Varianten/Verdichtung:** KF staccato; jeder vierte Takt mit Pause auf 2.

#### JW-R18 · 3/2-Einschub

- **Taktart:** 3/2 (24 Schritte/Takt) · **Länge:** 1 Takt(e) · **XYZ-Anker:** 0,70 / 0,50 / 0,40 (Hmm) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  X-------x-------x-------
KB  X---------------x-------
```
- **Einsätze gesamt:** KF 3, KB 2 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KF, KB, LF
- **Harmonische Voraussetzung:** Phrasendehnung, ein Klang
- **Wirkung:** Atem wird länger, Phrase weitet sich (3/2-Takte im E.T.-Flugthema).
- **Varianten/Verdichtung:** Zwischen 2/2-Takten einfügen.
- **Quellen:** S12

#### JW-R19 · Hemiole im 3/4

- **Taktart:** 3/4 (12 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,60 / 0,50 / 0,55 (mmm) · **Evidenz:** Verfahren [U], Raster [E]

```
KF  X.......X...|....X.......
LB  X-----------|X-----------
```
- **Einsätze gesamt:** KF 3, LB 2 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KF, LB
- **Harmonische Voraussetzung:** Kadenz oder Pendel
- **Wirkung:** Metrische Verschiebung, Schwung vor dem Ziel.
- **Varianten/Verdichtung:** Vor einer Kadenz einsetzen.

#### JW-R20 · Drei gegen vier (punktierte Achtel)

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,45 / 0,60 / 0,70 (mmU) · **Evidenz:** Verfahren [I], Raster [E]

```
AR  X..x..x..x..x..x|..x..x..x..x..x.
KB  X...X...X...X...|X...X...X...X...
```
- **Einsätze gesamt:** AR 11, KB 8 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** AR gegen KB
- **Harmonische Voraussetzung:** ein Klang
- **Wirkung:** Zwei Zeitschichten; Unruhe bei gleichem Tempo.
- **Varianten/Verdichtung:** AR ohne KB für schwebende Unruhe.
- **Quellen:** S21

#### JW-R21 · Stich am Phrasenende

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,40 / 0,70 / 0,50 (mIm) · **Evidenz:** Verfahren [U], Raster [E]

```
ST  ................|............X---
```
- **Einsätze gesamt:** ST 1 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** ST
- **Harmonische Voraussetzung:** Zielklang
- **Wirkung:** Punkt hinter der Phrase.
- **Varianten/Verdichtung:** Auf Zählzeit 1 des Folgetakts verschieben.

#### JW-R22 · Hämmernde 5/4-Schläge

- **Taktart:** 5/4 (20 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,20 / 0,90 / 0,70 (DIU) · **Evidenz:** Verfahren [I], Raster [E]

```
KF  X.X.X...X.X.X...X.X.|X.X.X...X.X.X...X...
ST  X...................|X...............X...
```
- **Einsätze gesamt:** KF 15, ST 3 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KF, ST
- **Harmonische Voraussetzung:** Polychord
- **Wirkung:** Unerbittliche Gewalt (Martial Chords nach Holsts „Mars“; Rhythmus eigene Konstruktion).
- **Varianten/Verdichtung:** Nur KF ohne ST in leiseren Stufen.
- **Quellen:** S1

#### JW-R23 · Punktierter Basso ostinato

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,40 / 0,65 / 0,45 (mIm) · **Evidenz:** Verfahren [I], Raster [E]

```
KB  X--xX---X--xX---|X--xX---X--xX.x.
```
- **Einsätze gesamt:** KB 13 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KB
- **Harmonische Voraussetzung:** Grundton oder Pendel
- **Wirkung:** Entschlossener Schritt.
- **Varianten/Verdichtung:** Oktavsprung auf den Sechzehnteln.
- **Quellen:** S1

#### JW-R24 · Pendel-Viertel

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,65 / 0,45 / 0,30 (HmS) · **Evidenz:** Verfahren [U], Raster [E]

```
KB  X...x...X...x...|X...x...X...x...
```
- **Einsätze gesamt:** KB 8 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KB
- **Harmonische Voraussetzung:** 1–2 Akkorde pro Takt
- **Wirkung:** Gutmütiger Schritt.
- **Varianten/Verdichtung:** Staccato für Humor, legato für Marsch.

#### JW-R25 · Synkopierter Bass

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,35 / 0,75 / 0,75 (DIU) · **Evidenz:** Verfahren [N], Raster [E]

```
KB  X..X..X...X..X..|X..X..X...X.X.X.
```
- **Einsätze gesamt:** KB 11 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KB
- **Harmonische Voraussetzung:** Moll, oktatonisch
- **Wirkung:** Kampfgetümmel (Hoth 4m1: synkopierte Basslinie mit chromatischer Aktivität darüber).
- **Varianten/Verdichtung:** Über statischem Klang mit chromatischer Oberstimme.
- **Quellen:** S1

#### JW-R26 · Lauernder Herzschlag

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,20 / 0,25 / 0,45 (DRm) · **Evidenz:** Verfahren [U], Raster [E]

```
KB  X.......x.......|X.......x.......
TU  ......x.........|..........x.....
```
- **Einsätze gesamt:** KB 4, TU 2 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KB, TU
- **Harmonische Voraussetzung:** Moll, Pedal
- **Wirkung:** Schleichen, Lauern.
- **Varianten/Verdichtung:** KB nur Zählzeit 1; TU in hoher Lage.

#### JW-R27 · Kaskadeneinsätze

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,75 / 0,80 / 0,60 (HIm) · **Evidenz:** Verfahren [N], Raster [E]

```
GS  XxxxXxxx........|....XxxxXxxx....
HM  ........XxxxXxxx|........XxxxX---
```
- **Einsätze gesamt:** GS 16, HM 13 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** GS, HM (versetzt)
- **Harmonische Voraussetzung:** Quartenklang oder Dur
- **Wirkung:** Aufschäumende Energie (Cascading Trumpet Lines, Endor).
- **Varianten/Verdichtung:** Dritte Stimme zwei Achtel später.
- **Quellen:** S1

#### JW-R28 · Ausdünnung (4 Takte)

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,45 / 0,50 / 0,45 (mmm) · **Evidenz:** Verfahren [U], Raster [E]

```
KF  X.xxX.xxX.xxX.xx|X.x.X.x.X.x.X.x.|X...X...X...X...|X-------........
```
- **Einsätze gesamt:** KF 25 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KF oder AR
- **Harmonische Voraussetzung:** beliebig
- **Wirkung:** Abbau ohne Bruch.
- **Varianten/Verdichtung:** Als Übergang zu JW-R12.

#### JW-R29 · Verdichtung (4 Takte)

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,45 / 0,65 / 0,60 (mIm) · **Evidenz:** Verfahren [I], Raster [E]

```
AR  X...X...X...X...|X.x.X.x.X.x.X.x.|X.xxX.xxX.xxX.xx|XxxxXxxxXxxxXxxx
```
- **Einsätze gesamt:** AR 40 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** AR oder KF
- **Harmonische Voraussetzung:** Pedal oder steigender Bass
- **Wirkung:** Steigender Druck vor einem Höhepunkt (Steigerung von Rhythmus, Schwung und Textur vor großem Crescendo).
- **Varianten/Verdichtung:** Gleichzeitig Register anheben.
- **Quellen:** S13

#### JW-R30 · Schlag und Stille

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,30 / 0,60 / 0,50 (Dmm) · **Evidenz:** Verfahren [U], Raster [E]

```
ST  X...............|................
LF  ................|........X-------
```
- **Einsätze gesamt:** ST 1, LF 1 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** ST, LF
- **Harmonische Voraussetzung:** Schlag auf Dissonanz, Fläche danach leise
- **Wirkung:** Schock, danach Leere.
- **Varianten/Verdichtung:** Pause auf 3 Takte verlängern.

#### JW-R31 · Heroisches Alla breve

- **Taktart:** 2/2 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,80 / 0,75 / 0,30 (HIS) · **Evidenz:** Verfahren [U], Raster [E]

```
KF  X.......X...x.x.|X.......X.......
KB  X.......X.......|X.......X.......
```
- **Einsätze gesamt:** KF 6, KB 4 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KF, KB, ST
- **Harmonische Voraussetzung:** Dur, Mixolydisch
- **Wirkung:** Breiter heroischer Schritt.
- **Varianten/Verdichtung:** Punktierung x.x. → x--x.

#### JW-R32 · 6/8-Abenteuergalopp

- **Taktart:** 6/8 (12 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,65 / 0,70 / 0,55 (HIm) · **Evidenz:** Verfahren [U], Raster [E]

```
KB  X-xX-xX-xX-x|X-xX-xX-----
KF  ...x.....x..|...x........
```
- **Einsätze gesamt:** KB 13, KF 3 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KB, KF
- **Harmonische Voraussetzung:** 1 Akkord pro Takt
- **Wirkung:** Galopp, Abenteuer.
- **Varianten/Verdichtung:** KF auf jede Achtel für Steigerung.

#### JW-R33 · Staccato-Humor

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,75 / 0,40 / 0,60 (Hmm) · **Evidenz:** Verfahren [I], Raster [E]

```
KF  x.x...x.x.x.....|x...x.x.....x...
```
- **Einsätze gesamt:** KF 9 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KF, KB, TU
- **Harmonische Voraussetzung:** Dur, chromatische Ausflüge
- **Wirkung:** Tollpatschig, verspielt (Jar Jars stolpernde Triolen, hier als Achtel).
- **Varianten/Verdichtung:** Pause an anderer Stelle (Witz durch Ausbleiben).
- **Quellen:** S1

#### JW-R34 · Magische Triolen-Tupfer

- **Taktart:** 4/4T (12 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,75 / 0,25 / 0,55 (HRm) · **Evidenz:** Verfahren [U], Raster [E]

```
TU  x..x..x.x...|..x..x......
```
- **Einsätze gesamt:** TU 6 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** TU, AR
- **Harmonische Voraussetzung:** lydisch, hexatonisch
- **Wirkung:** Glitzern, Zauber.
- **Varianten/Verdichtung:** Nur hohe Lage; jede zweite Note ausdünnen.

#### JW-R35 · Gedämpfter Trauermarsch

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,20 / 0,35 / 0,20 (DRS) · **Evidenz:** Verfahren [U], Raster [E]

```
KF  X.......X.......|X.......X...x...
ST  X...............|................
```
- **Einsätze gesamt:** KF 5, ST 1 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KF, ST, LB
- **Harmonische Voraussetzung:** Moll, langsamer harmonischer Rhythmus
- **Wirkung:** Gefasste Schwere.
- **Varianten/Verdichtung:** ST nur alle vier Takte.

#### JW-R36 · Unregelmäßiges Klopfen

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,20 / 0,25 / 0,75 (DRU) · **Evidenz:** Verfahren [E], Raster [E]

```
TU  x.....x.....x...|...x.......x....
KB  X...............|........x.......
```
- **Einsätze gesamt:** TU 5, KB 2 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** TU, KB
- **Harmonische Voraussetzung:** Moll oder oktatonischer Liegeklang
- **Wirkung:** Leise, nervöse Unberechenbarkeit.
- **Varianten/Verdichtung:** Abstände zufällig zwischen 3 und 7 Achteln wählen.

#### JW-R37 · Wechselnde Akzentgruppen 3+3+2 | 2+3+3

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,75 / 0,70 / 0,70 (HIU) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  X.x.x.X.x.x.X.x.|X.x.X.x.x.X.x.x.
```
- **Einsätze gesamt:** KF 16 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KF, AR, KB
- **Harmonische Voraussetzung:** stehende oder halbtaktig pendelnde Harmonie
- **Wirkung:** Unruhe durch Akzentordnung bei gleicher Notenzahl (TIE-Fighter-Figur: Staccato-Achtel in unregelmäßigen Gruppen; Gruppenfolge hier eigen).
- **Varianten/Verdichtung:** Takte 1/2 tauschen; nur jede zweite Achtel spielen (Akzente bleiben).
- **Quellen:** S24

#### JW-R38 · Puls 2+2+2+2 | 3+2+3

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,75 / 0,75 / 0,70 (HIU) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  X.x.X.x.X.x.X.x.|X.x.x.X.x.X.x.x.
KB  X.......X.......|X.....X...X.....
```
- **Einsätze gesamt:** KF 16, KB 5 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KF, KB
- **Harmonische Voraussetzung:** sus- und Quartenklänge
- **Wirkung:** Drängender, unregelmäßiger Puls (Finn/Pursuit-Prinzip, Gruppenfolge eigen).
- **Varianten/Verdichtung:** Gruppierung pro Durchgang wechseln (2+3+3, 3+3+2).
- **Quellen:** S24

#### JW-R39 · Staccato-Duett

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,75 / 0,25 / 0,65 (HRU) · **Evidenz:** Verfahren [N], Raster [E]

```
TU  x.x...x.x.......|....x.x...x.x...
GS  ........x...x.x.|x.x.............
```
- **Einsätze gesamt:** TU 8, GS 5 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** TU + GS (zwei Holzbläser), kein Bass nötig
- **Harmonische Voraussetzung:** Dur, Planing
- **Wirkung:** Neugieriger Kontrapunkt (E.T., Halloween: zwei Staccato-Oboen im Kontrapunkt, sequenziert mit wechselnder Besetzung).
- **Varianten/Verdichtung:** Sequenz: zweiter Durchgang eine Stufe höher; Instrument wechseln.
- **Quellen:** S26

#### JW-R40 · Isolierte Einwürfe mit Ausstieg (4 Takte)

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,70 / 0,15 / 0,55 (HRm) · **Evidenz:** Verfahren [N], Raster [E]

```
TU  x...............|........x.......|................|....x...........
GS  ........x.......|................|x...............|................
```
- **Einsätze gesamt:** TU 3, GS 2 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** TU, GS (wechselnde Instrumente)
- **Harmonische Voraussetzung:** beliebig, leise
- **Wirkung:** Kurze Einwürfe wandern zwischen Instrumenten, Stille gliedert (E.T., „E.T.’s New Home“: isolierte steigende Quinten, Musik setzt aus).
- **Varianten/Verdichtung:** Dritter Takt ganz still lassen.
- **Quellen:** S26

#### JW-R41 · Synkopierte 6/8-Figur

- **Taktart:** 6/8 (12 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,70 / 0,40 / 0,60 (Hmm) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  X..x.x..x...|X..x.x......
KB  X.....x.....|X...........
```
- **Einsätze gesamt:** KF 7, KB 3 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KF, TU, GS
- **Harmonische Voraussetzung:** Quintpendel, Dur
- **Wirkung:** Federnde, verschobene Bewegung (E.T., „Bait for E.T.“: synkopierte 6/8-Figur mit Quintpendel).
- **Varianten/Verdichtung:** Intensität über Besetzung steigern, Rhythmus behalten.
- **Quellen:** S26

#### JW-R42 · Oom-pah mit verschobenen Nachschlägen

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,75 / 0,30 / 0,60 (HRm) · **Evidenz:** Verfahren [N], Raster [E]

```
KB  X.......X.......|X.......X.......
KF  ....x.....x.x...|....x...x.....x.
```
- **Einsätze gesamt:** KB 4, KF 6 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KB + KF (staccato)
- **Harmonische Voraussetzung:** Dur mit fremden Tönen, Planing
- **Wirkung:** Gutmütig, aber schief (Jawas: Oom-pah-Bass, tritonusreiche Harmonisierung; Diminutive Creatures: Staccato-Vamp).
- **Varianten/Verdichtung:** Nachschlag regelmäßig (2, 4) für weniger Unruhe.
- **Quellen:** S24

#### JW-R43 · Lang-lang-kurz-kurz-lang

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,20 / 0,75 / 0,45 (DIm) · **Evidenz:** Verfahren [N], Raster [E]

```
KB  X---x---x-x-x---|X---x---x-x-x---
```
- **Einsätze gesamt:** KB 10 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KB, KF
- **Harmonische Voraussetzung:** passt sich jedem Akkord an
- **Wirkung:** Unbeirrbarer Schritt (Duel-of-the-Fates-Ostinato: unveränderlicher Rhythmus lang-lang-kurz-kurz-lang, passt sich den Akkorden an).
- **Varianten/Verdichtung:** Als Akkordostinato in der Kurzen Fläche.
- **Quellen:** S24

#### JW-R44 · Hemiole 6/8 gegen 3/4

- **Taktart:** 6/8 (12 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,70 / 0,65 / 0,65 (HIU) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  X.....x.....|X.....x.....
KB  X...x...x...|X...x...x...
```
- **Einsätze gesamt:** KF 4, KB 6 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KF gegen KB
- **Harmonische Voraussetzung:** ein Klang pro Takt
- **Wirkung:** Zwei gleichzeitige Metren (Poe-Motiv und Heroics: Hemiole 6/8 gegen 3/4-Begleitung, Richards).
- **Varianten/Verdichtung:** Schichten tauschen.
- **Quellen:** S24

#### JW-R45 · Leise Triolenarpeggien abwärts

- **Taktart:** 4/4T (12 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,35 / 0,20 / 0,50 (DRm) · **Evidenz:** Verfahren [N], Raster [E]

```
AR  Xxxxxxxxxxxx|Xxxxxxxxxxxx
```
- **Einsätze gesamt:** AR 24 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** AR (Harfe, Celesta, gedämpfte Streicher)
- **Harmonische Voraussetzung:** Moll mit ♭6, Polychord
- **Wirkung:** Geheimnisvolles Rieseln (Revelations: wiederholte Triolen, abwärts arpeggierte Mollklänge, ♭6 betont).
- **Varianten/Verdichtung:** Jede zweite Triole auslassen.
- **Quellen:** S24

#### JW-R46 · Choral in Halben mit sparsamem Akzent

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,15 / 0,75 / 0,25 (DIS) · **Evidenz:** Verfahren [I], Raster [E]

```
KF  X-------X-------|X-------X-------
ST  X...............|................
```
- **Einsätze gesamt:** KF 4, ST 1 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KF (Blech), ST
- **Harmonische Voraussetzung:** langsamer harmonischer Rhythmus
- **Wirkung:** Schwere ohne Hektik (Choral- und Chant-Satz mit langsamem harmonischem Rhythmus).
- **Varianten/Verdichtung:** ST nur alle vier Takte.
- **Quellen:** S24

#### JW-R47 · Hohes Pedal, tiefe Einzeltöne

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,30 / 0,10 / 0,55 (DRm) · **Evidenz:** Verfahren [N], Raster [E]

```
LF  X---------------|----------------
TU  ..........x.....|...x............
```
- **Einsätze gesamt:** LF 1, TU 2 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** LF hoch, TU tief (Klavier)
- **Harmonische Voraussetzung:** Pedal, leise Reibung
- **Wirkung:** Lauschen (E.T., „The Closet“: hohe Streicherpedale, selten leise Klaviereinzeltöne).
- **Varianten/Verdichtung:** Einzelton nur jeden zweiten Takt.
- **Quellen:** S26

#### JW-R48 · Gemeinsames Akzentgerüst

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,75 / 0,80 / 0,70 (HIU) · **Evidenz:** Verfahren [E], Raster [E]

```
KB  X..x..x.X..x..x.|X..x..x.X..x..x.
KF  X.....x.X.....x.|X.....x.X.....x.
ST  X.......X.......|X...............
```
- **Einsätze gesamt:** KB 12, KF 8, ST 3 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Rollen:** KB, KF, ST (alle Akzente fallen zusammen)
- **Harmonische Voraussetzung:** beliebig
- **Wirkung:** Viele Schichten, eine Ordnung: Unruhe ohne Durcheinander.
- **Varianten/Verdichtung:** ST weglassen für mittlere Intensität.

## E Bassvokabular (40 Vorlagen)

Töne: `R` Grundton, `b` notierter Bass, `3`/`5` Terz/Quinte, `8`/`-8` Oktave darüber/darunter, `+1` Halbton über dem Grundton, `n` Halbton unter dem nächsten Grundton, `d` diatonischer Durchgang zum nächsten Grundton, `P(x)` fester Ton (akkordunabhängig). Tonfolgen laufen zyklisch über die Einsätze, auch über Wiederholungen des Rasters hinweg. 37 der 40 Vorlagen bewegen sich.

#### JW-B01 · Tonikapedal, lang

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,60 / 0,25 / 0,15 (mRS) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  X---------------|----------------
Töne  P(C2)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** liegt unter allen Klängen
- **Akkordwechsel:** ignoriert Akkordwechsel
- **Artikulation:** legato, ohne Neuansatz
- **Wirkung:** Geborgenheit, Ruhe
- **Kombination:** JW-H03, JW-H06, JW-H38; LF, AR
- **Quellen:** S1

#### JW-B02 · Dominantpedal mit Neuansatz

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,60 / 0,55 / 0,45 (mmm) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  X-------X-------|X-------X-------
Töne  P(G1)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** liegt unter wechselnden Klängen
- **Akkordwechsel:** ignoriert Wechsel; letzter Takt Auflösung nach C
- **Artikulation:** Halbe, leicht betont
- **Wirkung:** Erwartung
- **Kombination:** JW-H07; KF, ST
- **Quellen:** S1

#### JW-B03 · Oktavsprung-Pedal

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,70 / 0,45 / 0,35 (HmS) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  X.x.X.x.X.x.X.x.|X.x.X.x.X.x.X.x.
Töne  R 8   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Grundton und Oktave
- **Akkordwechsel:** wechselt mit dem Akkord auf Zählzeit 1
- **Artikulation:** non legato, Achtel
- **Wirkung:** Leichtes Fliegen, Puls ohne Schwere
- **Kombination:** JW-H28, JW-H29; AR, HM
- **Quellen:** S12

#### JW-B04 · Grundton–Quinte-Marsch

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,65 / 0,50 / 0,30 (HmS) · **Evidenz:** Verfahren [U], Vorlage [E]

```
Bass  X...x...X...x...|X...x...X...x...
Töne  R 5   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Grundton, Quinte darunter oder darüber
- **Akkordwechsel:** Wechsel auf Zählzeit 1 oder 3
- **Artikulation:** staccato bis portato
- **Wirkung:** Marschieren, Gutmütigkeit
- **Kombination:** JW-H52, JW-H31; KF (JW-R24)

#### JW-B05 · Chromatischer Lamentofall

- **Taktart:** 4/4 · **Länge:** 8 Takt(e) · **XYZ-Anker:** 0,25 / 0,40 / 0,40 (Dmm) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  X---------------|X---------------|X---------------|X---------------|X---------------|X---------------|X---------------|X---------------
Töne  b   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** notierter Bass jedes Akkords
- **Akkordwechsel:** ein Ton pro Takt, chromatisch fallend
- **Artikulation:** legato
- **Wirkung:** Tragik, unausweichliches Sinken
- **Kombination:** JW-H39, JW-H30; LF
- **Quellen:** S1

#### JW-B06 · Chromatisch steigender Spannungsbass

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,40 / 0,60 / 0,55 (mmm) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  X-------X-------|X-------X-------
Töne  R n   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Grundton, dann Halbton unter dem nächsten Grundton
- **Akkordwechsel:** n zielt auf den nächsten Takt
- **Artikulation:** Halbe, Crescendo
- **Wirkung:** Steigende Spannung
- **Kombination:** JW-H19, JW-H16; AR (JW-R29)

#### JW-B07 · Oktatonischer Basslauf

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,30 / 0,65 / 0,75 (DIU) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  X.x.x.x.x.x.x.x.|X.x.x.x.x.x.x.x.
Töne  P(C2) P(Db2) P(Eb2) P(E2) P(F#2) P(G2) P(A2) P(Bb2)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** läuft durch Okt-A, unabhängig vom Akkord
- **Akkordwechsel:** Akkord muss aus Okt-A stammen
- **Artikulation:** Achtel, legato oder marcato
- **Wirkung:** Unruhiges Steigen, Kampf
- **Kombination:** JW-H18, JW-H20; KF (JW-R08)
- **Quellen:** S10

#### JW-B08 · Kleinterz-Sprungbass

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,25 / 0,60 / 0,70 (DmU) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  X...X...X...X...|X...X...X...X...
Töne  P(C2) P(Eb2) P(F#2) P(A2)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** umspielt den verminderten Septakkord
- **Akkordwechsel:** über Okt-A-Klängen
- **Artikulation:** marcato
- **Wirkung:** Bedrohliches Kreisen
- **Kombination:** JW-H12, JW-H16; KF
- **Quellen:** S1

#### JW-B09 · Halbton-Dissonanzbass

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,25 / 0,80 / 0,75 (DIU) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  X-------X-------|X-------X-------
Töne  +1   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** ein Halbton über dem Akkordgrundton
- **Akkordwechsel:** mit jedem Akkord neu
- **Artikulation:** tenuto, schwer
- **Wirkung:** Harte Reibung, Gefahr
- **Kombination:** JW-H17, JW-H46; KF, ST
- **Quellen:** S10

#### JW-B10 · Tritonus-Pendel

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,20 / 0,45 / 0,60 (Dmm) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  X-------X-------|X-------X-------
Töne  R P(F#1)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Grundton C und F♯ im Wechsel
- **Akkordwechsel:** über statischem Moll oder Cm↔F♯m
- **Artikulation:** Halbe, dunkel
- **Wirkung:** Unheimliche Leere
- **Kombination:** JW-H14, JW-H46
- **Quellen:** S6

#### JW-B11 · Punktiertes Marschmotiv

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,55 / 0,65 / 0,45 (mIm) · **Evidenz:** Verfahren [U], Vorlage [E]

```
Bass  X--xX---X--xX---|X--xX---X--xX.x.
Töne  R 5 R R 5 R R 5 R R 5 R 5   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Grundton mit Quint-Anlauf
- **Akkordwechsel:** Wechsel auf Zählzeit 1
- **Artikulation:** marcato
- **Wirkung:** Entschlossenheit, Abenteuer
- **Kombination:** JW-H01, JW-H53; KF (JW-R01)

#### JW-B12 · Synkopierte Basslinie

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,35 / 0,75 / 0,75 (DIU) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  X..X..X...X..X..|X..X..X...X.X.X.
Töne  R 8 R 5 R 8 R 5 R 3 5   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Akkordtöne, Akzent auf Synkopen
- **Akkordwechsel:** über statischem Klang
- **Artikulation:** staccato, kräftig
- **Wirkung:** Kampfgetümmel
- **Kombination:** JW-H44, JW-H18; GS chromatisch
- **Quellen:** S1

#### JW-B13 · Gegenbewegung zur Oberstimme

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,45 / 0,55 / 0,55 (mmm) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  X-------X-------|X-------X-------
Töne  P(C2) P(Bb1) P(Ab1) P(Gb1)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Bass fällt in Ganztönen, während eine Oberstimme in großen Terzen steigt
- **Akkordwechsel:** Akkorde folgen der Stimmführung
- **Artikulation:** legato
- **Wirkung:** Aufziehen, Weitung
- **Kombination:** JW-H25; GS oder HM steigend
- **Quellen:** S1

#### JW-B14 · Staccato-Wanderbass

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,75 / 0,40 / 0,55 (Hmm) · **Evidenz:** Verfahren [U], Vorlage [E]

```
Bass  x.x.x.x.x.x.x.x.|x.x.x.x.x.x.x.x.
Töne  R d d 5 R d d 5   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Akkordtöne und diatonische Durchgänge
- **Akkordwechsel:** Durchgänge zielen auf den nächsten Grundton
- **Artikulation:** staccato, leicht
- **Wirkung:** Humor, Geschäftigkeit
- **Kombination:** JW-H51, JW-H52; KF (JW-R33)

#### JW-B15 · Durchgangsbass zwischen Grundtönen

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,60 / 0,35 / 0,30 (mRS) · **Evidenz:** Verfahren [U], Vorlage [E]

```
Bass  X-------x---x---|X-------x---x---
Töne  R d d   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** zwei Durchgangstöne zum nächsten Grundton
- **Akkordwechsel:** nur bei Akkordwechsel pro Takt
- **Artikulation:** legato
- **Wirkung:** Fluss, Wärme
- **Kombination:** JW-H37, JW-H10

#### JW-B16 · Terzbass (Sextakkordlinie)

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,65 / 0,30 / 0,30 (HRS) · **Evidenz:** Verfahren [U], Vorlage [E]

```
Bass  X---------------|X---------------
Töne  3   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Terz jedes Akkords im Bass
- **Akkordwechsel:** Ergibt stufenweise Linie bei Quintfall
- **Artikulation:** legato
- **Wirkung:** Leichtigkeit, Schweben
- **Kombination:** JW-H37, JW-H35

#### JW-B17 · Bass nur auf Akzenten

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,40 / 0,60 / 0,50 (mmm) · **Evidenz:** Verfahren [U], Vorlage [E]

```
Bass  X...............|..........X.....
Töne  R R   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Grundton
- **Akkordwechsel:** nur der erste Akkord je Takt
- **Artikulation:** kurz, schwer
- **Wirkung:** Luft für andere Rollen
- **Kombination:** JW-R04, JW-R30; ST

#### JW-B18 · Ostinato 3+3+2

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,55 / 0,65 / 0,60 (mIm) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  X..x..x.X..x..x.|X..x..x.X..x..x.
Töne  R 5 8 R 5 8   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Akkordtöne
- **Akkordwechsel:** Wechsel nur auf Zählzeit 1
- **Artikulation:** marcato
- **Wirkung:** Drängende Energie
- **Kombination:** JW-H01, JW-H16; AR
- **Quellen:** S1

#### JW-B19 · Tiefe Achtelrepetition mit Akzentversatz

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,35 / 0,55 / 0,60 (Dmm) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  X.x.x.X.x.x.X.x.|x.X.x.x.X.x.x.X.
Töne  R   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** ein Ton
- **Akkordwechsel:** Wechsel mit Akkord
- **Artikulation:** non legato
- **Wirkung:** Puls, gespannte Erwartung
- **Kombination:** JW-H18, JW-H41; LF
- **Quellen:** S21

#### JW-B20 · Registersprung bei Abschnittswechsel

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,35 / 0,60 / 0,30 (DmS) · **Evidenz:** Verfahren [U], Vorlage [E]

```
Bass  X---------------|X---------------
Töne  R -8   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Grundton, im zweiten Takt eine Oktave tiefer
- **Akkordwechsel:** Markiert neuen Abschnitt
- **Artikulation:** Fermate-artig
- **Wirkung:** Vertiefung, Gewicht
- **Kombination:** JW-H55, JW-H33

#### JW-B21 · Dorische Stufenlinie

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,35 / 0,35 / 0,30 (DRS) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  X-------x-------|X-------x-------
Töne  P(C2) P(D2) P(Eb2) P(F2)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** stufenweise in C dorisch
- **Akkordwechsel:** Akkorde aus C dorisch
- **Artikulation:** legato
- **Wirkung:** Rätsel, Gehen
- **Kombination:** JW-H42, JW-H11
- **Quellen:** S2

#### JW-B22 · Lydisches Nachbarton-Ostinato

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,85 / 0,40 / 0,40 (Hmm) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  X...x...X...x...|X...x...X...x...
Töne  P(C2) P(D2) P(E2) P(F#2)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** C–D–E–F♯, kehrt zu C zurück
- **Akkordwechsel:** über C-lydischen Klängen
- **Artikulation:** legato
- **Wirkung:** Neugier, Leichtigkeit
- **Kombination:** JW-H03, JW-H04
- **Quellen:** S6

#### JW-B23 · Hexatonischer Stufenbass

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,40 / 0,40 / 0,55 (mmm) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  X-------X-------|X-------X-------
Töne  P(C2) P(B1) P(Ab1) P(G1)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Halbton und kleine Terz im Wechsel
- **Akkordwechsel:** über Hex-C-Klängen
- **Artikulation:** legato
- **Wirkung:** Fremdes Sinken
- **Kombination:** JW-H24, JW-H25, JW-H45
- **Quellen:** S1

#### JW-B24 · Lang–kurz-Wechsel

- **Taktart:** 4/4 · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,45 / 0,50 / 0,45 (mmm) · **Evidenz:** Verfahren [U], Vorlage [E]

```
Bass  X---------------|----------------|X.x.X.x.X.x.X.x.|X.x.X.x.X---....
Töne  R   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Grundton
- **Akkordwechsel:** langer Ton → Achtel bei Intensitätsanstieg
- **Artikulation:** legato → marcato
- **Wirkung:** Erwachen der Bewegung
- **Kombination:** Übergangsstudien; JW-R29

#### JW-B25 · Bass als Motor (Sechzehntel)

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,45 / 0,85 / 0,80 (mIU) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  XxxxXxxxXxxxXxxx|XxxxXxxxXxxxXxxx
Töne  R R 8 R   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Grundton mit Oktavtupfern
- **Akkordwechsel:** Wechsel auf Zählzeit 1
- **Artikulation:** staccato, gleichmäßig
- **Wirkung:** Hetzjagd, Bass übernimmt den Antrieb
- **Kombination:** JW-H16, JW-H53; ohne AR
- **Quellen:** S1

#### JW-B26 · Wiederkehrendes Bassmotiv (Vierton)

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,30 / 0,45 / 0,45 (Dmm) · **Evidenz:** Verfahren [E], Vorlage [E]

```
Bass  X...x...x...x---|X...x...x...x---
Töne  R P(Eb2) P(D2) P(G1)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** eigene Zelle C–E♭–D–G (relativ: 1, ♭3, 2, 5)
- **Akkordwechsel:** wird mit dem Zentrum transponiert
- **Artikulation:** portato
- **Wirkung:** Erkennungszeichen im Bass
- **Kombination:** Motivgedächtnis (JW-M); JW-H34, JW-H42

#### JW-B27 · Heroischer Quintfall-Bass

- **Taktart:** 2/2 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,80 / 0,75 / 0,30 (HIS) · **Evidenz:** Verfahren [U], Vorlage [E]

```
Bass  X.......X.......|X---------------
Töne  R 5 R   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Grundton, Quinte tiefer, Grundton
- **Akkordwechsel:** Wechsel pro Takt
- **Artikulation:** marcato
- **Wirkung:** Heldenhafter Schritt
- **Kombination:** JW-H01, JW-H33; KF (JW-R31)

#### JW-B28 · Bewusste Basspause

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,55 / 0,30 / 0,40 (mRm) · **Evidenz:** Verfahren [U], Vorlage [E]

```
Bass  ................|X---------------
Töne  R   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Bass setzt einen Takt aus und kehrt mit dem Zielklang zurück
- **Akkordwechsel:** Rückkehr auf neuem Akkord
- **Artikulation:** Pause, dann legato
- **Wirkung:** Schweben, dann Boden
- **Kombination:** JW-H03, JW-H50; LF ohne Bass

#### JW-B29 · Lydischer Oktav-Motor

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,80 / 0,80 / 0,70 (HIU) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  X.xX.xX.X.xX.xX.|X.xX.xX.X.xX.xX.
Töne  R 8 5 R 8 R 5 8 R 5   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Grundton, Oktave, Quinte im 3+3+2-Muster
- **Akkordwechsel:** Wechsel auf Zählzeit 1
- **Artikulation:** staccato, hell
- **Wirkung:** Helle Hetzjagd
- **Kombination:** JW-H04, JW-H16; AR (JW-R09)

#### JW-B30 · Schwebender Hochbass

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,75 / 0,30 / 0,60 (HRm) · **Evidenz:** Verfahren [E], Vorlage [E]

```
Bass  X.......x.....x.|....x.......x...
Töne  R 5 8 5 R   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Grundton, Quinte, Oktave in hoher Basslage (ab C3)
- **Akkordwechsel:** unregelmäßige Einsätze, Wechsel mit Akkord
- **Artikulation:** leicht, pizzicato
- **Wirkung:** Helles Schweben mit Unruhe
- **Kombination:** JW-H25, JW-H15; TU

#### JW-B31 · Oom-pah-Bass, beweglich

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,75 / 0,30 / 0,60 (HRm) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  X...x...X...x...|X...x...X...x...
Töne  R 5 +1 5   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Grundton, Quinte, Halbton über dem Grundton als Reibung
- **Akkordwechsel:** Wechsel auf Zählzeit 1
- **Artikulation:** staccato
- **Wirkung:** Schief-gutmütig
- **Kombination:** JW-H58, JW-H59; KF (JW-R42)
- **Quellen:** S24

#### JW-B32 · Bass auf Nicht-Akkordtönen

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,70 / 0,75 / 0,75 (HIU) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  X.x.X.x.X.x.X.x.|X.x.X.x.X.x.X.x.
Töne  +1 +1 n n   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Halbton über dem Grundton, dann Halbton unter dem nächsten Grundton
- **Akkordwechsel:** zielt auf den nächsten Klang
- **Artikulation:** staccato
- **Wirkung:** Instabile Kraft unter heller Harmonie
- **Kombination:** JW-H64, JW-H62; KF (JW-R37)
- **Quellen:** S24

#### JW-B33 · Tiefes oktatonisches Klavier-Ostinato

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,25 / 0,45 / 0,70 (DmU) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  X-xX-xX-X-xX-xX-|X-xX-xX-X-xX-xX-
Töne  P(C2) P(C2) P(Db2) P(Db2) P(Eb2) P(C2) P(C2) P(Gb1) P(Gb1) P(A1)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Okt-A unabhängig vom Akkord
- **Akkordwechsel:** Akkord aus Okt-A
- **Artikulation:** staccato, tief
- **Wirkung:** Drohender Motor, auch leise spielbar
- **Kombination:** JW-H74, JW-H18; KF (JW-R08)
- **Quellen:** S1

#### JW-B34 · Lang-lang-kurz-kurz-lang-Bass

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,20 / 0,75 / 0,45 (DIm) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  X---x---x-x-x---|X---x---x-x-x---
Töne  R 5 8 5 R   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Akkordtöne, passt sich jedem Klang an
- **Akkordwechsel:** Wechsel auf Zählzeit 1
- **Artikulation:** marcato
- **Wirkung:** Unbeirrbarer Schritt
- **Kombination:** JW-H67, JW-H69, JW-H70
- **Quellen:** S24

#### JW-B35 · Dies-irae-Cantus im Bass

- **Taktart:** 4/4 · **Länge:** 8 Takt(e) · **XYZ-Anker:** 0,15 / 0,80 / 0,25 (DIS) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  X---------------|X---------------|X---------------|X---------------|X---------------|X---------------|X---------------|X---------------
Töne  P(C2) P(B1) P(C2) P(Ab1) P(B1) P(G1) P(Ab1) P(Ab1)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Cantus, Akkorde darüber nach JW-H69
- **Akkordwechsel:** ein Ton pro Takt
- **Artikulation:** legato, schwer
- **Wirkung:** Archaische Drohung
- **Kombination:** JW-H69; LF, KF (JW-R43)
- **Quellen:** S28

#### JW-B36 · Chromatischer Gegenbass zu steigenden Klängen

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,65 / 0,60 / 0,60 (Hmm) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  X-------X-------|X-------X-------
Töne  P(C2) P(B1) P(Bb1) P(A1)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** fällt chromatisch, während die Klänge (Planing) steigen
- **Akkordwechsel:** unabhängig vom Akkordgrundton
- **Artikulation:** legato
- **Wirkung:** Weitung, Spannung
- **Kombination:** JW-H58, JW-H64
- **Quellen:** S24

#### JW-B37 · Tiefer Einwurf unter hohem Pedal

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,30 / 0,10 / 0,55 (DRm) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  ................|..........x.....
Töne  P(C1)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** einzelner tiefster Ton, sonst kein Bass
- **Akkordwechsel:** unabhängig
- **Artikulation:** leise, kurz
- **Wirkung:** Lauern, Abgrund
- **Kombination:** JW-H73; LF hoch (JW-R47)
- **Quellen:** S26

#### JW-B38 · Synkopierter Quintpendel-Bass (6/8)

- **Taktart:** 6/8 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,70 / 0,40 / 0,55 (Hmm) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  X..x..X.....|X..x........
Töne  R 5 R R 5   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Grundton und Quinte
- **Akkordwechsel:** Wechsel pro Takt
- **Artikulation:** pizzicato
- **Wirkung:** Federnder Schritt
- **Kombination:** JW-R41; JW-H28
- **Quellen:** S26

#### JW-B39 · Galopp-Bass 6/8

- **Taktart:** 6/8 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,80 / 0,75 / 0,60 (HIm) · **Evidenz:** Verfahren [U], Vorlage [E]

```
Bass  X-xX-xX-xX-x|X-xX-xX-----
Töne  R R 5   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Grundton, Quinte
- **Akkordwechsel:** Wechsel pro Takt
- **Artikulation:** marcato
- **Wirkung:** Helles Vorwärts
- **Kombination:** JW-H62, JW-H04; KF (JW-R44)

#### JW-B40 · Kleinterz-Pedalwechsel (leise)

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,20 / 0,20 / 0,60 (DRm) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  X---------------|----------------
Töne  P(C2) P(Eb2) P(F#2) P(A1)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Pedal wechselt alle zwei Takte um eine kleine Terz
- **Akkordwechsel:** über Okt-A-Klängen
- **Artikulation:** pp, legato
- **Wirkung:** Leise Verschiebung des Bodens
- **Kombination:** JW-H74, JW-H12
- **Quellen:** S1

## F Motivisches und melodisches Vokabular

### F.1 Kurze Motive (48)

#### JW-M01 · Quintaufschwung mit Doppelschlag

- **Töne/Dauern:** `C4/4 G4/8 A4/2 G4/1 F#4/1 | G4/8 D4/8` (Taktart 4/4) · **Kontext:** `C` | `G/D`
- **Intervalle (Halbtöne):** +7 +2 -2 -1 +1 -5 · **Ambitus:** 9 · **XYZ:** 0,75 / 0,45 / 0,35 (HmS) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** legato, Doppelschlag leicht · **Kontur:** Sprung aufwärts, Kreisen, Quartfall
- **Wiederkehr:** früh vollständig wiederholen, dann nur Takt 1 · **Transformationen:** Umkehrung (Quintfall, Quartaufschlag), Vergrößerung
- **Muss erhalten bleiben:** Quintsprung + Doppelschlag + Quartfall
- **Verfahren:** Steigende Quinte, später zur fallenden Quarte umgekehrt, mit Drehfigur (Pearson, E.T.-Flugthema). (S12)

#### JW-M02 · Kampfkontur

- **Töne/Dauern:** `C4/4 G4/4 F4/2 E4/2 C5/4 | B4/4 G5/12` (Taktart 4/4) · **Kontext:** `C` | `G`
- **Intervalle (Halbtöne):** +7 -2 -1 +8 -1 +8 · **Ambitus:** 19 · **XYZ:** 0,70 / 0,70 / 0,45 (HIm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** marcato, Ziel gehalten · **Kontur:** steigt, sinkt kurz, steigt höher
- **Wiederkehr:** als Kopf jeder Heldenphrase · **Transformationen:** Sequenz um eine Stufe aufwärts; Ziel auf Terz statt Quinte
- **Muss erhalten bleiben:** Richtung auf–ab–auf, Zielton höchster Ton
- **Verfahren:** Richards: „struggle“-Kontur im Force- und Superman-Thema. (S11)

#### JW-M03 · Zielton mit Obersekund-Vorhalt

- **Töne/Dauern:** `E4/2 G4/2 C5/4 E5/4 D5/4 | C5/16` (Taktart 4/4) · **Kontext:** `C` | `C`
- **Intervalle (Halbtöne):** +3 +5 +4 -2 -2 · **Ambitus:** 12 · **XYZ:** 0,70 / 0,55 / 0,30 (HmS) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** Vorhalt betont, Auflösung leiser · **Kontur:** Aufstieg, Vorhalt von oben, Ziel
- **Wiederkehr:** Schluss jeder zweiten Phrase · **Transformationen:** Vorhalt chromatisch (D♭ statt D) für Dunkelheit
- **Muss erhalten bleiben:** Ziel nach Vorhalt um eine Stufe verschoben
- **Verfahren:** Richards: Zielton durch höheren Nachbarton verdrängt (Superman-Analyse). (S11)

#### JW-M04 · Quartsignal

- **Töne/Dauern:** `G4/2 C5/2 G4/2 C5/2 F5/8 | E5/16` (Taktart 4/4) · **Kontext:** `Cq` | `C`
- **Intervalle (Halbtöne):** +5 -5 +5 +5 -1 · **Ambitus:** 10 · **XYZ:** 0,70 / 0,75 / 0,40 (HIm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** marcato, Blechsignal · **Kontur:** Quartpendel, Sprung zur Quarte darüber
- **Wiederkehr:** als Antwort im Kanon (versetzt um 1 Takt) · **Transformationen:** Transposition um Quarte; Kanon zweier Rollen
- **Muss erhalten bleiben:** Quartintervalle
- **Verfahren:** Quartenkanon in der Schlacht von Yavin (Lehman, Incidental 21); Quarten in der Hauptthema-Fanfare. (S1)

#### JW-M05 · Repetition und kleine Terz

- **Töne/Dauern:** `C4/2 C4/2 C4/2 Eb4/10 | D4/4 Db4/12` (Taktart 4/4) · **Kontext:** `Cm` | `Db/C`
- **Intervalle (Halbtöne):** +0 +0 +3 -1 -1 · **Ambitus:** 3 · **XYZ:** 0,20 / 0,45 / 0,50 (Dmm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** tenuto, letzte Note Tremolo · **Kontur:** Tonrepetition, Terz aufwärts, Abstieg zum ♭2
- **Wiederkehr:** sehr früh wiederkehrend, Motivgedächtnis-Anker · **Transformationen:** Harmonisierung mit Dreiklängen im Kleinterzabstand
- **Muss erhalten bleiben:** Repetition + kleine Terz + ♭2
- **Verfahren:** Imperials-Motiv: wiederholter Anfangston, kleine Terz aufwärts, ♭2 (Lehman 6). Konkrete Töne eigen. (S1)

#### JW-M06 · Sechsfache Repetition mit Halbtonfall

- **Töne/Dauern:** `G3/1 G3/1 G3/1 G3/1 G3/1 G3/1 F#3/10 | r/16` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** +0 +0 +0 +0 +0 -1 · **Ambitus:** 1 · **XYZ:** 0,20 / 0,40 / 0,60 (Dmm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** staccato, tief (Fagott-Lage) · **Kontur:** Repetition, Halbton abwärts
- **Wiederkehr:** als Gegenstimme, nie als Hauptmelodie · **Transformationen:** chromatische untere Nachbarnote variieren
- **Muss erhalten bleiben:** Repetitionszahl ≥ 4, Halbtonfall
- **Verfahren:** Kopfgeldjäger-Motiv: schnelle sechsfache Repetition, dann Halbtonfall (Lehman 14). (S1)

#### JW-M07 · Verminderte Terz (Gegenspieler)

- **Töne/Dauern:** `Db4/4 C4/4 B3/8 | C4/16` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** -1 -1 +1 · **Ambitus:** 2 · **XYZ:** 0,15 / 0,40 / 0,55 (Dmm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** schwer, legato · **Kontur:** Umspielung des Grundtons von oben und unten
- **Wiederkehr:** Signatur des Gegenspielers · **Transformationen:** Vergrößerung ×2
- **Muss erhalten bleiben:** D♭→B (verminderte Terz) als Rahmen
- **Verfahren:** Verminderte Terz als typisches „Bösewicht“-Intervall bei Williams (Lehman 61). (S1)

#### JW-M08 · Lydischer Doppelnachbar

- **Töne/Dauern:** `A4/4 F#4/4 G4/8 | E4/16` (Taktart 4/4) · **Kontext:** `C` | `C`
- **Intervalle (Halbtöne):** -3 +1 -3 · **Ambitus:** 5 · **XYZ:** 0,85 / 0,25 / 0,30 (HRS) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** dolce, legato · **Kontur:** 6 → ♯4 → 5, dann Terz
- **Wiederkehr:** als Kopf eines Freundschafts- oder Staunensmotivs · **Transformationen:** in Moll mit ♮6 (dorisch)
- **Muss erhalten bleiben:** 6–♯4–5
- **Verfahren:** Lydischer Doppelnachbar 6→♯4→5 im Freundschaftsthema (Lehman 57). (S1)

#### JW-M09 · ♭6–5–♯4-Zelle

- **Töne/Dauern:** `Ab4/4 G4/4 F#4/8 | G4/16` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** -1 -1 +1 · **Ambitus:** 2 · **XYZ:** 0,20 / 0,45 / 0,55 (Dmm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** portato, gedeckt · **Kontur:** chromatischer Abstieg um den Quintton
- **Wiederkehr:** kurz, häufig · **Transformationen:** Rückkehr nach G auslassen (offen)
- **Muss erhalten bleiben:** ♭6–5–♯4
- **Verfahren:** Bad-Guys-Thema (Dial of Destiny): ♭6–5–♯4-Zelle (Lehman, IJ-Katalog). (S2)

#### JW-M10 · Pentatonischer Hüpfer

- **Töne/Dauern:** `C5/2 A4/2 G4/4 E4/2 G4/2 A4/4 | C5/2 D5/2 E5/12` (Taktart 4/4) · **Kontext:** `C` | `Am7`
- **Intervalle (Halbtöne):** -3 -2 -3 +3 +2 +3 +2 +2 · **Ambitus:** 12 · **XYZ:** 0,80 / 0,45 / 0,50 (Hmm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** staccato, frech · **Kontur:** Bogen ab–auf
- **Wiederkehr:** Kinder-/Gefährtenmotiv · **Transformationen:** lydisch harmonisieren (D/C unter Takt 2)
- **Muss erhalten bleiben:** pentatonischer Tonvorrat
- **Verfahren:** Short-Round-Thema: pentatonische Melodie mit lydischer Harmonik (Lehman, IJ-Katalog). (S2)

#### JW-M11 · Oktatonische Synkope in Unterterzen

- **Töne/Dauern:** `Bb4/2 r/2 A4/2 G4/2 r/2 F#4/2 E4/4 | Eb4/2 r/2 Db4/2 Eb4/2 r/2 E4/2 F#4/4` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** -1 -2 -1 -2 -1 -2 +2 +1 +2 · **Ambitus:** 9 · **XYZ:** 0,30 / 0,65 / 0,80 (DIU) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** staccato, mit paralleler kleiner Unterterz · **Kontur:** fallend, dann steigend
- **Wiederkehr:** zweimal hintereinander, dann Pause · **Transformationen:** auf Okt-B transponieren (+1)
- **Muss erhalten bleiben:** Okt-A-Töne, Synkopen auf den Achtel-Nachschlägen
- **Verfahren:** Space Battle Vamp: synkopierte oktatonische Figur in kleinen Parallelterzen (Lehman, Incidental 38). (S1)

#### JW-M12 · Nervöses vermindertes Arpeggio

- **Töne/Dauern:** `C5/1 A4/1 F#4/1 Eb4/1 C5/1 A4/1 F#4/1 Eb4/1 Db5/1 Bb4/1 G4/1 E4/1 Db5/4 | r/16` (Taktart 4/4) · **Kontext:** `Cdim7` | `Cdim7`
- **Intervalle (Halbtöne):** -3 -3 -3 +9 -3 -3 -3 +10 -3 -3 -3 +9 · **Ambitus:** 10 · **XYZ:** 0,30 / 0,60 / 0,80 (DmU) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** spiccato · **Kontur:** fallende verminderte Klänge, Sequenz +1
- **Wiederkehr:** als Einwurf zwischen Blockakkorden · **Transformationen:** Richtung umkehren
- **Muss erhalten bleiben:** verminderte Dreiklänge, Halbtonversatz
- **Verfahren:** „It’s a Trap“-A-Motiv: nervöse oktatonische Figur, arpeggierte verminderte Dreiklänge (Lehman 21). (S1)

#### JW-M13 · Chromatische Glockenfigur

- **Töne/Dauern:** `E4/4 Eb4/4 D4/4 Db4/4 | C4/16` (Taktart 4/4) · **Kontext:** `C` | `C`
- **Intervalle (Halbtöne):** -1 -1 -1 -1 · **Ambitus:** 4 · **XYZ:** 0,30 / 0,35 / 0,45 (DRm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** tenuto, glockig · **Kontur:** chromatischer Fall über eine große Terz
- **Wiederkehr:** als Zeitzeichen, Wiederkehr in Abständen · **Transformationen:** aufwärts als Frage
- **Muss erhalten bleiben:** fünf Töne, chromatisch
- **Verfahren:** „Chromatic Knell“: einfache chromatische Fünftonfigur (Lehman, Incidental 23). (S1)

#### JW-M14 · Zitternder chromatischer Doppelnachbar

- **Töne/Dauern:** `C5/2 Db5/2 B4/2 C5/10 | r/16` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** +1 -2 +1 · **Ambitus:** 2 · **XYZ:** 0,30 / 0,25 / 0,65 (DRU) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** leise, Tremolo · **Kontur:** Umspielung
- **Wiederkehr:** unregelmäßig wiederholen · **Transformationen:** auf anderem Akkordton
- **Muss erhalten bleiben:** Halbton oben/unten
- **Verfahren:** „Tremulous Double Neighbor“ (Lehman, Incidental 60). (S1)

#### JW-M15 · Seufzerkette

- **Töne/Dauern:** `Ab4/3 G4/5 Gb4/3 F4/5 | Eb4/3 D4/13` (Taktart 4/4) · **Kontext:** `Fm6` | `G7sus4`
- **Intervalle (Halbtöne):** -1 -1 -1 -2 -1 · **Ambitus:** 6 · **XYZ:** 0,25 / 0,30 / 0,35 (DRS) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** legato, Seufzer betont · **Kontur:** Halbtonfälle paarweise
- **Wiederkehr:** als Gegenstimme unter Dialog · **Transformationen:** Diatonisch statt chromatisch
- **Muss erhalten bleiben:** paarweise Fallfiguren
- **Verfahren:** Reihe chromatischer Seufzer (Lehman 36, „Gloomy Courtship“). (S1)

#### JW-M16 · Triolensequenz (fallend, steigend gekettet)

- **Töne/Dauern:** `G4/1 F4/1 E4/1 A4/1 G4/1 F4/1 B4/1 A4/1 G4/1 C5/3 | E5/12` (Taktart 4/4T) · **Kontext:** `C` | `C`
- **Intervalle (Halbtöne):** -2 -1 +5 -2 -2 +6 -2 -2 +5 +4 · **Ambitus:** 12 · **XYZ:** 0,75 / 0,50 / 0,45 (Hmm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** leggiero · **Kontur:** fallende Triolen in steigender Sequenz
- **Wiederkehr:** als Überleitung · **Transformationen:** Sequenzschritt Terz statt Sekunde
- **Muss erhalten bleiben:** Triolen fallend, Sequenz steigend
- **Verfahren:** Absteigende Triolen in aufsteigender Sequenz (Lehman, Leia-Konzertmaterial). (S1)

#### JW-M17 · Heroische Tetrachorde

- **Töne/Dauern:** `C5/4 Bb4/4 A4/4 G4/4 | F5/4 Eb5/4 D5/4 C5/4` (Taktart 4/4) · **Kontext:** `C` | `F`
- **Intervalle (Halbtöne):** -2 -1 -2 +10 -2 -1 -2 · **Ambitus:** 10 · **XYZ:** 0,75 / 0,75 / 0,40 (HIm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** marcato · **Kontur:** zwei fallende Tetrachorde, der zweite eine Quarte höher
- **Wiederkehr:** in Schlachtmusik wiederholt · **Transformationen:** Kanon in der Gegenstimme
- **Muss erhalten bleiben:** Tetrachord abwärts
- **Verfahren:** Heroic Descending Tetrachords (Lehman, Incidental 18). (S1)

#### JW-M18 · Steigende Quartenkette

- **Töne/Dauern:** `D4/2 G4/2 C5/2 F5/2 E5/8 | r/16` (Taktart 4/4) · **Kontext:** `Cq` | `Cq`
- **Intervalle (Halbtöne):** +5 +5 +5 -1 · **Ambitus:** 15 · **XYZ:** 0,65 / 0,70 / 0,55 (HIm) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** marcato · **Kontur:** drei Quarten aufwärts, Sekunde zurück
- **Wiederkehr:** kurz und oft · **Transformationen:** Kanon im Abstand einer Halben
- **Muss erhalten bleiben:** Quartstapel
- **Verfahren:** Quartenkanon (Lehman, Incidental 21). Töne eigen. (S1)

#### JW-M19 · Synkopierte Militärzelle

- **Töne/Dauern:** `C5/3 C5/3 C5/2 G4/4 Bb4/4 | C5/16` (Taktart 4/4) · **Kontext:** `C` | `C`
- **Intervalle (Halbtöne):** +0 +0 -5 +3 +2 · **Ambitus:** 5 · **XYZ:** 0,55 / 0,70 / 0,55 (mIm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** marcato · **Kontur:** Repetition 3+3+2, Quartfall, Rückkehr
- **Wiederkehr:** im Bass oder Blech · **Transformationen:** rhythmisch verkleinern
- **Muss erhalten bleiben:** 3+3+2-Repetition
- **Verfahren:** Syncopated Military Figure (Lehman, Incidental 22). (S1)

#### JW-M20 · Romantischer Sextaufschwung

- **Töne/Dauern:** `E4/4 C5/8 B4/4 | A4/12 G4/4` (Taktart 4/4) · **Kontext:** `Am7` | `Fmaj7`
- **Intervalle (Halbtöne):** +8 -1 -2 -2 · **Ambitus:** 8 · **XYZ:** 0,60 / 0,40 / 0,25 (mmS) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** espressivo · **Kontur:** kleine Sexte aufwärts, Stufenabstieg
- **Wiederkehr:** als Liebesmotiv · **Transformationen:** Moll-Variante E♭–C (dann große Sexte)
- **Muss erhalten bleiben:** Sextsprung aufwärts + Stufenabstieg
- **Verfahren:** Spätromantische Liebeskontur (allgemein).

#### JW-M21 · Wiegenterzen

- **Töne/Dauern:** `E5/4 D5/2 C5/4 D5/2 | E5/6 G4/6` (Taktart 6/8) · **Kontext:** `C` | `C`
- **Intervalle (Halbtöne):** -2 -2 +2 +2 -9 · **Ambitus:** 9 · **XYZ:** 0,70 / 0,20 / 0,20 (HRS) · **Evidenz:** Verfahren [E], Töne [E]
- **Artikulation:** dolce · **Kontur:** Pendel um D
- **Wiederkehr:** mehrfach, leise · **Transformationen:** in Terzen gedoppelt
- **Muss erhalten bleiben:** 6/8-Lang-kurz
- **Verfahren:** Eigene Konstruktion.

#### JW-M22 · Staunen: Nonensprung

- **Töne/Dauern:** `C4/4 D5/8 C5/2 B4/2 | G4/16` (Taktart 4/4) · **Kontext:** `Cmaj7` | `Cmaj7`
- **Intervalle (Halbtöne):** +14 -2 -1 -4 · **Ambitus:** 14 · **XYZ:** 0,80 / 0,30 / 0,40 (HRm) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** pp, offen · **Kontur:** großer Sprung, Stufenabstieg
- **Wiederkehr:** einmal pro Szene · **Transformationen:** Sprung zur Dezime
- **Muss erhalten bleiben:** großer Sprung aufwärts (≥ Oktave)
- **Verfahren:** Weite Sprünge als Staunensgeste (Interpretation).

#### JW-M23 · Quarte–Tritonus-Rätsel

- **Töne/Dauern:** `C4/6 F4/2 B4/8 | Bb4/16` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** +5 +6 -1 · **Ambitus:** 11 · **XYZ:** 0,30 / 0,25 / 0,50 (DRm) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** pp, gehaucht · **Kontur:** Quarte, Tritonus darüber, Halbtonfall
- **Wiederkehr:** chromatisch versetzt wiederholen · **Transformationen:** Halbton auf- oder abwärts transponieren
- **Muss erhalten bleiben:** Quarte+Tritonus
- **Verfahren:** Mystery-Motiv wird chromatisch auf- und abwärts versetzt (Lehman 34). (S1)

#### JW-M24 · Tiefe Lauerzelle

- **Töne/Dauern:** `C3/2 r/2 D3/2 r/2 Ab2/6 r/2 | r/16` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** +2 -6 · **Ambitus:** 6 · **XYZ:** 0,15 / 0,20 / 0,45 (DRm) · **Evidenz:** Verfahren [E], Töne [E]
- **Artikulation:** pizzicato oder tiefes Klavier · **Kontur:** Ganzton auf, Tritonus ab
- **Wiederkehr:** mit wachsendem Abstand · **Transformationen:** Pausen verkürzen (Annäherung)
- **Muss erhalten bleiben:** tiefe Lage, Pausen
- **Verfahren:** Eigene Konstruktion.

#### JW-M25 · Chromatischer Stolperer

- **Töne/Dauern:** `G4/1 r/1 G#4/1 r/1 A4/2 C5/2 r/2 B4/1 Bb4/1 A4/4 | r/16` (Taktart 4/4) · **Kontext:** `C` | `C`
- **Intervalle (Halbtöne):** +1 +1 +3 -1 -1 -1 · **Ambitus:** 5 · **XYZ:** 0,75 / 0,40 / 0,60 (Hmm) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** staccato · **Kontur:** chromatisch hoch, Sprung, chromatisch zurück
- **Wiederkehr:** als Witz nach Pausen · **Transformationen:** Pause an anderer Stelle
- **Muss erhalten bleiben:** Chromatik + Pause
- **Verfahren:** Chromatische Triolenfigur bei Jar Jar (Lehman, Incidental 47); hier geradtaktig. (S1)

#### JW-M26 · Mechanischer Marschgruß

- **Töne/Dauern:** `C5/2 C5/2 G4/2 E4/2 F#4/2 G4/2 r/4 | r/16` (Taktart 4/4) · **Kontext:** `C` | `C`
- **Intervalle (Halbtöne):** +0 -5 -3 +2 +1 · **Ambitus:** 8 · **XYZ:** 0,80 / 0,45 / 0,45 (Hmm) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** staccato · **Kontur:** Repetition, Fall, ♯4 als Leitton zu 5
- **Wiederkehr:** als Figur einer verspielten Figur · **Transformationen:** Rhythmus punktieren
- **Muss erhalten bleiben:** ♯4→5
- **Verfahren:** Droid-Marsch: ♯4→1 als einziger chromatischer Moment (Lehman 26). (S1)

#### JW-M27 · Abenteueraufruf

- **Töne/Dauern:** `G4/1 A4/1 B4/2 C5/4 E5/4 D5/4 | G5/16` (Taktart 4/4) · **Kontext:** `C` | `G`
- **Intervalle (Halbtöne):** +2 +2 +1 +4 -2 +5 · **Ambitus:** 12 · **XYZ:** 0,80 / 0,70 / 0,40 (HIm) · **Evidenz:** Verfahren [E], Töne [E]
- **Artikulation:** marcato · **Kontur:** Lauf aufwärts, Ziel Quinte
- **Wiederkehr:** als Phraseneröffnung · **Transformationen:** Ziel auf Oktave
- **Muss erhalten bleiben:** Auftaktlauf + Ziel
- **Verfahren:** Eigene Konstruktion nach Auftakt-Verfahren.

#### JW-M28 · Moll-Klagezelle i–♭6–5

- **Töne/Dauern:** `C4/6 Eb4/2 Ab4/8 | G4/16` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** +3 +5 -1 · **Ambitus:** 8 · **XYZ:** 0,20 / 0,40 / 0,35 (DmS) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** legato · **Kontur:** Terz, Quarte, Halbtonfall
- **Wiederkehr:** als dunkles Hauptmotiv · **Transformationen:** Ab4 durch A4 (dorisch, heller)
- **Muss erhalten bleiben:** ♭6→5
- **Verfahren:** Allgemeine Mollgeste (Interpretation).

#### JW-M29 · Phrygischer Abstieg

- **Töne/Dauern:** `Db5/4 C5/4 Bb4/4 Ab4/4 | G4/16` (Taktart 4/4) · **Kontext:** `Db/C` | `Cm`
- **Intervalle (Halbtöne):** -1 -2 -2 -1 · **Ambitus:** 6 · **XYZ:** 0,20 / 0,55 / 0,45 (Dmm) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** tenuto · **Kontur:** stufenweise vom ♭2 zur Quinte
- **Wiederkehr:** im Blech · **Transformationen:** oktatonisch: Db–C–Bb–A–G
- **Muss erhalten bleiben:** Abstieg beginnt auf ♭2
- **Verfahren:** Phrygische Färbung (Lehman 6; Yavin-Umfärbung). (S1)

#### JW-M30 · Hexatonische Linie

- **Töne/Dauern:** `C5/2 B4/2 Ab4/2 G4/2 E4/4 Eb4/4 | r/16` (Taktart 4/4) · **Kontext:** `C` | `Abm`
- **Intervalle (Halbtöne):** -1 -3 -1 -3 -1 · **Ambitus:** 9 · **XYZ:** 0,45 / 0,35 / 0,55 (mRm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** legato · **Kontur:** Halbton und kleine Terz im Wechsel
- **Wiederkehr:** über JW-H24/H25 · **Transformationen:** Umkehrung
- **Muss erhalten bleiben:** Hex-C-Töne
- **Verfahren:** Hexatonische Tonfolgen (Lehman: Droids aus übermäßigen Sekunden und hexatonischer Skala). (S1)

#### JW-M31 · Ganztonschwebe

- **Töne/Dauern:** `C5/4 D5/4 E5/4 F#5/4 | G#5/8 F#5/8` (Taktart 4/4) · **Kontext:** `Caug` | `Caug`
- **Intervalle (Halbtöne):** +2 +2 +2 +2 -2 · **Ambitus:** 8 · **XYZ:** 0,60 / 0,20 / 0,55 (mRm) · **Evidenz:** Verfahren [H], Töne [E]
- **Artikulation:** pp, flautando · **Kontur:** Ganztonaufstieg
- **Wiederkehr:** einmal · **Transformationen:** rückwärts
- **Muss erhalten bleiben:** Ganztöne
- **Verfahren:** Hypothese (nicht belegt).

#### JW-M32 · Oktatonischer Verbindungslauf

- **Töne/Dauern:** `C4/1 Db4/1 Eb4/1 E4/1 F#4/1 G4/1 A4/1 Bb4/1 C5/8 | r/16` (Taktart 4/4) · **Kontext:** `Cdim7` | `Cdim7`
- **Intervalle (Halbtöne):** +1 +2 +1 +2 +1 +2 +1 +2 · **Ambitus:** 12 · **XYZ:** 0,35 / 0,75 / 0,75 (DIU) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** brillant · **Kontur:** Skala aufwärts
- **Wiederkehr:** als Auftakt zu einem Schlag · **Transformationen:** abwärts; Okt-B
- **Muss erhalten bleiben:** Halbton-Ganzton-Folge
- **Verfahren:** Richards: oktatonische Verbindungsläufe („Connective Scale Runs“, Kursübersicht). (S10)

#### JW-M33 · Kurze Antwortfigur

- **Töne/Dauern:** `r/8 E5/2 D5/2 C5/4 | r/16` (Taktart 4/4) · **Kontext:** `C` | `C`
- **Intervalle (Halbtöne):** -2 -2 · **Ambitus:** 4 · **XYZ:** 0,70 / 0,30 / 0,30 (HRS) · **Evidenz:** Verfahren [E], Töne [E]
- **Artikulation:** leicht · **Kontur:** Stufenabstieg in Antwort
- **Wiederkehr:** nach jeder Hauptmelodie-Phrase · **Transformationen:** auf Terz enden
- **Muss erhalten bleiben:** drei Töne nach Pause
- **Verfahren:** Eigene Konstruktion (Frage-Antwort).

#### JW-M34 · Schwere Quint-Oktav-Zelle

- **Töne/Dauern:** `C3/4 G3/4 C4/8 | Bb3/4 Ab3/4 G3/8` (Taktart 4/4) · **Kontext:** `Cm` | `Fm`
- **Intervalle (Halbtöne):** +7 +5 -2 -2 -1 · **Ambitus:** 12 · **XYZ:** 0,15 / 0,80 / 0,25 (DIS) · **Evidenz:** Verfahren [E], Töne [E]
- **Artikulation:** marcato, tiefes Blech · **Kontur:** Quinte und Quarte aufwärts, Stufenabstieg
- **Wiederkehr:** als Kopf eines dunklen Hauptmotivs · **Transformationen:** Augmentation ×2 als Choral
- **Muss erhalten bleiben:** leere Intervalle aufwärts, Stufen abwärts
- **Verfahren:** Eigene Konstruktion für dunkel-kraftvoll-stabil.

#### JW-M35 · Synkopiertes Quintpendel (6/8)

- **Töne/Dauern:** `C5/3 G4/2 C5/1 G5/3 C5/3 | r/12` (Taktart 6/8) · **Kontext:** `C` | `C`
- **Intervalle (Halbtöne):** -5 +5 +7 -7 · **Ambitus:** 12 · **XYZ:** 0,70 / 0,40 / 0,60 (Hmm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** staccato, federnd · **Kontur:** Quinte ab, Quinte auf, Quarte ab
- **Wiederkehr:** Kern einer Szene, früh zweimal · **Transformationen:** Besetzung steigern bei gleichem Rhythmus (Intensität)
- **Muss erhalten bleiben:** Quintpendel + Synkope
- **Verfahren:** E.T., „Bait for E.T.“: synkopierte Figur mit steigenden und fallenden reinen Quinten (Normandie). (S26)

#### JW-M36 · Isolierter Quinteinwurf

- **Töne/Dauern:** `r/8 G4/2 D5/6 | r/16` (Taktart 4/4) · **Kontext:** `C` | `C`
- **Intervalle (Halbtöne):** +7 · **Ambitus:** 7 · **XYZ:** 0,70 / 0,15 / 0,50 (HRm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** pizzicato oder Celesta · **Kontur:** eine steigende Quinte nach Pause
- **Wiederkehr:** zwischen Instrumenten weiterreichen · **Transformationen:** Quarte statt Quinte (dunkler)
- **Muss erhalten bleiben:** Sprung aufwärts nach Stille
- **Verfahren:** E.T., „E.T.’s New Home“: isolierte steigende reine Quinten, zwischen Instrumenten weitergereicht (Normandie). (S26)

#### JW-M37 · Lydisch-♯2-Hüpfer

- **Töne/Dauern:** `C5/1 r/1 D#5/1 E5/1 F#5/2 E5/2 r/2 B4/2 C5/4 | r/16` (Taktart 4/4) · **Kontext:** `C` | `C`
- **Intervalle (Halbtöne):** +3 +1 +2 -2 -5 +1 · **Ambitus:** 7 · **XYZ:** 0,70 / 0,30 / 0,65 (HRU) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** staccato, Englischhorn-Lage · **Kontur:** Umspielung mit übermäßiger Sekunde
- **Wiederkehr:** als Figur einer kleinen Kreatur · **Transformationen:** auf Pentatonik reduzieren (ohne D♯, F♯)
- **Muss erhalten bleiben:** übermäßige Sekunde C–D♯ und ♯4
- **Verfahren:** Jawas: lydisch-♯9-Skala, extreme Chromatik (Lehman, Kat. 7). (S24)

#### JW-M38 · Wrong-note-Punktierung

- **Töne/Dauern:** `G4/3 A4/1 F#5/3 G5/1 E5/4 r/4 | r/16` (Taktart 4/4) · **Kontext:** `C` | `C`
- **Intervalle (Halbtöne):** +2 +9 +1 -3 · **Ambitus:** 12 · **XYZ:** 0,75 / 0,35 / 0,65 (HRU) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** staccato, punktiert · **Kontur:** punktierter Aufschwung zum ♯4, Auflösung
- **Wiederkehr:** als Antwort auf Dur-Motive · **Transformationen:** B♭ statt F♯ (♭7 statt ♯4)
- **Muss erhalten bleiben:** punktiert + ♯4 auf Akzent
- **Verfahren:** Ewoks: staccato punktierte Rhythmen, oft akzentuierte ♯4 und ♭5 (Lehman, Kat. 19). (S24)

#### JW-M39 · Hexatonische Abwärtszelle, synkopiert

- **Töne/Dauern:** `r/2 E5/2 D#5/2 B4/4 G#4/2 E4/4 | r/16` (Taktart 4/4) · **Kontext:** `E` | `E`
- **Intervalle (Halbtöne):** -1 -4 -3 -4 · **Ambitus:** 12 · **XYZ:** 0,70 / 0,35 / 0,60 (HRm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** leicht, Holzbläser solo · **Kontur:** Halbton, kleine Terz, große Terz abwärts
- **Wiederkehr:** wiederholt mit Synkope · **Transformationen:** auf C transponieren (C–B–G–E… im Vorrat Hex-C)
- **Muss erhalten bleiben:** Abwärtsrichtung, Halbton am Anfang
- **Verfahren:** Droids: wiederholte absteigende 3–4-Ton-Motive, nicht-funktional, übermäßige Sekunden und hexatonische Skala, Synkopen (Lehman, Kat. 13). (S24)

#### JW-M40 · Galoppzelle

- **Töne/Dauern:** `G4/2 A4/1 B4/1 C5/4 E5/2 D5/1 C5/1 G5/4 | r/16` (Taktart 4/4) · **Kontext:** `C` | `C`
- **Intervalle (Halbtöne):** +2 +2 +1 +4 -2 -2 +7 · **Ambitus:** 12 · **XYZ:** 0,75 / 0,70 / 0,60 (HIm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** marcato · **Kontur:** zweimal Achtel–Sechzehntel–Sechzehntel–Viertel
- **Wiederkehr:** als Ostinato in Gegenstimme oder Kurzer Fläche · **Transformationen:** Tonhöhen frei, Rhythmus fest
- **Muss erhalten bleiben:** Rhythmus 2–1–1–4
- **Verfahren:** Galopp-Ostinato Achtel-Sechzehntel-Sechzehntel-Viertel (Rey, Lehman Kat.). (S24)

#### JW-M41 · Sechzehntel-Fanfarenkopf mit Staccato-Achtel

- **Töne/Dauern:** `C5/1 D5/1 E5/1 G5/1 C6/2 r/2 G5/1 A5/1 B5/1 D6/1 E6/2 r/2 | r/16` (Taktart 4/4) · **Kontext:** `C` | `G`
- **Intervalle (Halbtöne):** +2 +2 +3 +5 -5 +2 +2 +3 +2 · **Ambitus:** 16 · **XYZ:** 0,85 / 0,80 / 0,60 (HIm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** brillant · **Kontur:** zwei Anläufe, zweiter höher
- **Wiederkehr:** zweimal, dann Fragment · **Transformationen:** zweiter Anlauf in Quinten
- **Muss erhalten bleiben:** 4 Sechzehntel + Achtel
- **Verfahren:** Luke in Exile, Fanfare: vier Sechzehntel und eine Staccato-Achtel (Lehman, Kat.). (S24)

#### JW-M42 · Leiser Kleinterz-Kreisel (oktatonisch)

- **Töne/Dauern:** `C4/2 Eb4/2 Db4/2 E4/2 Eb4/4 r/4 | r/16` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** +3 -2 +3 -1 · **Ambitus:** 4 · **XYZ:** 0,20 / 0,20 / 0,60 (DRm) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** pp, tiefe Holzbläser, mit paralleler kleiner Unterterz · **Kontur:** kreist um E♭
- **Wiederkehr:** mehrmals, mit Pausen · **Transformationen:** auf Okt-B (+1) versetzen
- **Muss erhalten bleiben:** Okt-A-Töne, kleine Terzen
- **Verfahren:** Boba Fett: oktatonisch in kleinen Parallelterzen, Fagotte (Lehman, Kat. 14). Töne eigen. (S24)

#### JW-M43 · Choralabstieg 5→3 mit ♭6-Reibung

- **Töne/Dauern:** `G4/8 Ab4/4 G4/4 | F4/8 Eb4/8` (Taktart 4/4) · **Kontext:** `Cm` | `Fm`
- **Intervalle (Halbtöne):** +1 -1 -2 -2 · **Ambitus:** 5 · **XYZ:** 0,15 / 0,65 / 0,30 (DIS) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** legato, Chor oder Blech · **Kontur:** Quinte, ♭6-Nebenton, Abstieg zur Terz
- **Wiederkehr:** als Choralkopf · **Transformationen:** Augmentation ×2
- **Muss erhalten bleiben:** 5–♭6–5–4–3
- **Verfahren:** Trauermarsch: langsamer Abstieg 5 → 3 in Moll, innere Dissonanzen mit kleinen Sexten (Lehman, Kat. 31). (S24)

#### JW-M44 · Dies-irae-Kopf (Typ 1)

- **Töne/Dauern:** `C4/4 B3/4 C4/4 A3/4 | r/16` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** -1 +1 -3 · **Ambitus:** 3 · **XYZ:** 0,15 / 0,55 / 0,35 (DmS) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** legato, dunkel · **Kontur:** Halbton ab, zurück, kleine Terz ab
- **Wiederkehr:** sequenziert (Typ 1) · **Transformationen:** Typ 2: Fortsetzung mit erhöhter 7. Stufe
- **Muss erhalten bleiben:** Töne 1–4 der Dies-irae-Kontur
- **Verfahren:** Schneller: Dies-irae-Typ 1 = Segment x (Töne 1–4), sequenzierbar; gregorianischer Hymnus, gemeinfrei (Émergences 2025). (S28)

#### JW-M45 · Dies-irae-Umkehrung (Typ 5)

- **Töne/Dauern:** `C4/4 Db4/4 C4/4 Eb4/4 | r/16` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** +1 -1 +3 · **Ambitus:** 3 · **XYZ:** 0,15 / 0,70 / 0,55 (DIm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** marcato · **Kontur:** Halbton auf, zurück, kleine Terz auf
- **Wiederkehr:** als Steigerung nach JW-M44 · **Transformationen:** transponieren in kleinen Terzen
- **Muss erhalten bleiben:** gespiegelte Kontur von JW-M44
- **Verfahren:** Schneller: Typ 5 als Umkehrung (Burning Homestead als Steigerung). (S28)

#### JW-M46 · Spannungszelle 1–3–2–x–1, synkopiert

- **Töne/Dauern:** `C4/2 Eb4/3 D4/3 B3/4 C4/4 | r/16` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** +3 -1 -3 +1 · **Ambitus:** 4 · **XYZ:** 0,20 / 0,40 / 0,60 (Dmm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** portato, tief · **Kontur:** Terz auf, Sekunde ab, Leitton, Grundton
- **Wiederkehr:** pulsierend wiederholt · **Transformationen:** x = A♭ oder F♯ statt B
- **Muss erhalten bleiben:** 1→3→2→x→1
- **Verfahren:** Tension (TFA/TLJ): 1→3→2→x→1 in Moll, oft synkopiert, tiefe Besetzung mit pulsierender Begleitung (Lehman, Kat. 52). (S24)

#### JW-M47 · Arpeggio mit Fremdton (♭6)

- **Töne/Dauern:** `C4/2 Eb4/2 G4/2 Ab4/2 G4/2 Eb4/2 C4/4 | r/16` (Taktart 4/4) · **Kontext:** `Cm(b6)` | `Cm`
- **Intervalle (Halbtöne):** +3 +4 +1 -1 -4 -3 · **Ambitus:** 8 · **XYZ:** 0,30 / 0,20 / 0,60 (DRm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** leggiero, Harfe/Celesta · **Kontur:** Moll aufwärts mit ♭6-Spitze
- **Wiederkehr:** stufenweise transponiert · **Transformationen:** Fremdton ♯7 oder ♭9 statt ♭6
- **Muss erhalten bleiben:** genau ein Zusatzton
- **Verfahren:** Mystery (Kamino): arpeggierte Akkorde mit genau einem Zusatzton (Lehman, Kat. 34). (S24)

#### JW-M48 · Halbton-Mollpaar in hoher Lage

- **Töne/Dauern:** `G5/4 G#5/4 G5/4 E5/4 | Eb5/16` (Taktart 4/4) · **Kontext:** `C#m|Cm` | `Cm`
- **Intervalle (Halbtöne):** +1 -1 -3 -1 · **Ambitus:** 5 · **XYZ:** 0,15 / 0,20 / 0,65 (DRU) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** pp, gedämpft · **Kontur:** Halbtonpendel, Fall zur Terz
- **Wiederkehr:** beständig, ausdruckslos · **Transformationen:** Tritonuspaar (F♯m) statt Halbton
- **Muss erhalten bleiben:** Halbtonpendel zwischen den Klängen
- **Verfahren:** Sith-Dolch: zwei Mollklänge im Halbtonabstand, Holzbläser; Map: gedämpft, ausdruckslos, beharrlich (Lehman, Kat. 60b, 48). (S24)

### F.2 Längere Phrasen (24; Längen 4, 6 und 8 Takte)

#### JW-P01 · Heroische Kampfphrase (4 Takte)

- **Taktart:** 4/4 · **Akkorde je Takt:** `C` | `Bb` | `F` | `C` · **XYZ:** 0,80 / 0,75 / 0,35 (HIS)
- **Töne/Dauern:** `G4/4 C5/4 D5/2 E5/2 G5/4 | F5/6 D5/2 Bb4/8 | A4/4 C5/4 F5/4 E5/2 D5/2 | E5/4 G5/12`
- **Gipfel:** G5 in Takt 1, 4 · **Schlusston:** G · **Artikulation:** marcato
- **Verfahren:** Kampfkontur (JW-M02), Zielton = höchster Ton am Schluss · **Bauplan:** Kopf M02 → Abstieg → Anlauf → Ziel · **Evidenz:** [E]

#### JW-P02 · Lyrische Frage–Antwort (8 Takte)

- **Taktart:** 4/4 · **Akkorde je Takt:** `Cmaj7` | `Fmaj7` | `Bm7b5` | `E7` | `Am7` | `Dm7` | `G7sus4` | `Cmaj7` · **XYZ:** 0,60 / 0,40 / 0,25 (mmS)
- **Töne/Dauern:** `E4/4 G4/4 B4/8 | A4/12 C5/4 | B4/4 A4/4 F4/8 | G#4/12 r/4 | E4/4 G4/4 C5/8 | D5/4 C5/4 A4/8 | G4/4 F4/4 D5/8 | C5/16`
- **Gipfel:** D5 in Takt 6, 7 · **Schlusston:** C · **Artikulation:** espressivo
- **Verfahren:** Antwort beginnt mit denselben Tönen wie die Frage; Frage endet offen auf der Terz von E7 · **Bauplan:** Frage (1–4) / Antwort (5–8) · **Evidenz:** [E]

#### JW-P03 · Lydischer Aufbruch (4 Takte)

- **Taktart:** 4/4 · **Akkorde je Takt:** `C` | `D` | `Em` | `C` · **XYZ:** 0,90 / 0,60 / 0,40 (Hmm)
- **Töne/Dauern:** `C5/2 D5/2 E5/4 G5/4 E5/4 | F#5/4 A5/4 F#5/4 D5/4 | E5/4 B4/4 G4/4 B4/4 | C5/16`
- **Gipfel:** A5 in Takt 2 · **Schlusston:** C · **Artikulation:** leggiero
- **Verfahren:** Lydischer ♯4 im Gipfeltakt · **Bauplan:** Anlauf → Gipfel (Takt 2) → Abstieg → Ziel · **Evidenz:** [E]

#### JW-P04 · Lauernde Gegenstimme (4 Takte)

- **Taktart:** 4/4 · **Akkorde je Takt:** `Cm` | `Db/C` | `Cm` | `Cm` · **XYZ:** 0,15 / 0,20 / 0,45 (DRm)
- **Töne/Dauern:** `C4/2 r/2 Db4/2 r/10 | Eb4/2 r/2 Db4/2 r/2 C4/8 | r/8 G3/2 r/2 Ab3/4 | G3/16`
- **Gipfel:** E♭4 in Takt 2 · **Schlusston:** G · **Artikulation:** pizzicato/staccato
- **Verfahren:** Pausen als Teil der Phrase; ♭2 phrygisch · **Bauplan:** Zelle → Erweiterung → Abstieg in die Tiefe · **Evidenz:** [E]

#### JW-P05 · Kleinterzsequenz der Bedrohung (4 Takte)

- **Taktart:** 4/4 · **Akkorde je Takt:** `Cm` | `Ebm` | `F#m` | `Am` · **XYZ:** 0,20 / 0,55 / 0,65 (DmU)
- **Töne/Dauern:** `G4/2 G4/2 G4/4 Eb4/8 | Gb4/2 Gb4/2 Gb4/4 Bb4/8 | A4/2 A4/2 A4/4 C#5/8 | C5/2 C5/2 C5/4 E5/8`
- **Gipfel:** E5 in Takt 4 · **Schlusston:** E · **Artikulation:** tenuto
- **Verfahren:** Repetitionszelle (JW-M05) in Kleinterzsequenz, alle Töne Okt-A · **Bauplan:** Zelle ×4 transponiert · **Evidenz:** [E]

#### JW-P06 · Oktatonische Actionlinie (4 Takte)

- **Taktart:** 4/4 · **Akkorde je Takt:** `Cm(add#4)` | `Cm(add#4)` | `Cm(add#4)` | `Cm(add#4)` · **XYZ:** 0,30 / 0,75 / 0,75 (DIU)
- **Töne/Dauern:** `G4/2 F#4/2 Eb4/2 C4/2 Db4/2 Eb4/2 E4/4 | F#4/2 G4/2 A4/2 Bb4/2 A4/2 G4/2 F#4/4 | G4/2 A4/2 Bb4/2 C5/2 Db5/2 Eb5/2 C5/4 | Eb5/2 F#5/2 G5/12`
- **Gipfel:** G5 in Takt 4 · **Schlusston:** G · **Artikulation:** marcato
- **Verfahren:** Okt-A über statischem Klang; Höhepunkt am Ende · **Bauplan:** Abstieg → Anstieg in Wellen → Ziel · **Evidenz:** [E]

#### JW-P07 · Staunen über Pedal (8 Takte)

- **Taktart:** 4/4 · **Akkorde je Takt:** `Cmaj7` | `Cmaj7` | `Ab/C` | `E/C` | `Ab/C` | `E/C` | `Cmaj7` | `Cmaj7` · **XYZ:** 0,75 / 0,40 / 0,45 (Hmm)
- **Töne/Dauern:** `G4/4 C5/4 E5/8 | D5/4 B4/4 G4/8 | Ab4/4 C5/4 Eb5/8 | E5/4 G#5/4 B5/8 | C6/8 Ab5/8 | G#5/4 E5/4 B4/8 | C5/8 E5/8 | G5/16`
- **Gipfel:** C6 in Takt 5 · **Schlusston:** G · **Artikulation:** dolce → espressivo
- **Verfahren:** Gipfel in Takt 5 (0,56 der Länge); jede Note Akkordton · **Bauplan:** Ruhe → Großterzwechsel → Gipfel → Heimkehr · **Evidenz:** [E]

#### JW-P08 · Trauerphrase (8 Takte)

- **Taktart:** 4/4 · **Akkorde je Takt:** `Cm` | `Cm` | `Abmaj7` | `Fm6` | `Cm/G` | `G7sus4` | `G7` | `Cm` · **XYZ:** 0,25 / 0,30 / 0,20 (DRS)
- **Töne/Dauern:** `G4/8 Eb4/4 D4/4 | C4/12 r/4 | Eb4/4 G4/4 C5/8 | Ab4/8 F4/4 D4/4 | Eb4/8 G4/8 | C5/8 F4/8 | B3/8 D4/4 F4/4 | C4/16`
- **Gipfel:** C5 in Takt 3, 6 · **Schlusston:** C · **Artikulation:** legato, leise
- **Verfahren:** Atempause in Takt 2; Gipfel C5 zweimal (Takt 3, 6) als bewusster Rückbezug · **Bauplan:** Fall → Atem → Aufschwung → Fall · **Evidenz:** [E]

#### JW-P09 · Verspielte Staccatophrase (4 Takte)

- **Taktart:** 4/4 · **Akkorde je Takt:** `C` | `Eb` | `C` | `Ab` · **XYZ:** 0,75 / 0,40 / 0,60 (Hmm)
- **Töne/Dauern:** `E5/2 r/2 G5/2 E5/2 C5/4 r/4 | G5/2 r/2 Bb5/2 G5/2 Eb5/4 r/4 | C5/2 E5/2 G5/2 E5/2 C5/4 r/4 | Ab4/2 C5/2 Eb5/4 C5/8`
- **Gipfel:** B♭5 in Takt 2 · **Schlusston:** C · **Artikulation:** staccato
- **Verfahren:** Pausen an gleicher Stelle, dann Bruch des Musters in Takt 3 · **Bauplan:** Zelle → chromatische Rückung → Rückkehr → Ausweichung · **Evidenz:** [E]

#### JW-P10 · Heroischer Mollmarsch (4 Takte)

- **Taktart:** 4/4 · **Akkorde je Takt:** `Cm`+`Ab` | `Bb`+`Cm` | `Cm`+`Db` | `Bb`+`Cm` · **XYZ:** 0,30 / 0,80 / 0,60 (DIm)
- **Töne/Dauern:** `C5/3 C5/1 Eb5/4 Ab4/8 | D5/3 D5/1 F5/4 G5/8 | G5/3 G5/1 Eb5/4 F5/8 | D5/4 Bb4/4 C5/8`
- **Gipfel:** G5 in Takt 2, 3 · **Schlusston:** C · **Artikulation:** marcato, punktiert
- **Verfahren:** Punktierter Kopf in jeder Zelle; Gipfel G5 wird in Takt 2 erreicht und in Takt 3 mit neuem Anlauf bestätigt · **Bauplan:** Zelle ×3 sequenziert → Schluss · **Evidenz:** [E]

#### JW-P11 · Dorische Mystik (8 Takte)

- **Taktart:** 4/4 · **Akkorde je Takt:** `Cm7` | `Cm7` | `Dm7` | `Dm7` | `Cm7` | `Ebmaj7` | `Bbsus2` | `Cm` · **XYZ:** 0,35 / 0,30 / 0,30 (DRS)
- **Töne/Dauern:** `C5/6 Bb4/2 G4/8 | Eb4/12 r/4 | F4/6 A4/2 D5/8 | C5/12 r/4 | Bb4/6 G4/2 Eb5/8 | D5/8 Bb4/8 | C5/8 F4/8 | C5/16`
- **Gipfel:** E♭5 in Takt 5 · **Schlusston:** C · **Artikulation:** pp, ruhig
- **Verfahren:** Lang-kurz-lang-Rhythmus als Identität; zwei Atempausen · **Bauplan:** A (1–2) A′ (3–4) B (5–8) · **Evidenz:** [E]

#### JW-P12 · Romantischer Bogen (8 Takte)

- **Taktart:** 4/4 · **Akkorde je Takt:** `Cmaj7` | `Fm6/C` | `Cmaj7` | `Abmaj7/C` | `Fmaj7` | `Fm6` | `Csus4` | `C` · **XYZ:** 0,60 / 0,40 / 0,30 (mmS)
- **Töne/Dauern:** `G4/4 E5/8 D5/4 | C5/8 Ab4/8 | B4/4 C5/4 E5/8 | Eb5/8 G5/8 | A5/12 G5/4 | F5/8 D5/4 C5/4 | F5/8 E5/8 | E5/4 C5/12`
- **Gipfel:** A5 in Takt 5 · **Schlusston:** C · **Artikulation:** espressivo
- **Verfahren:** Gipfel A5 in Takt 5; Mollschatten in Takt 2 und 4 · **Bauplan:** Sextsprung → Schatten → Anstieg → Gipfel → Lösung · **Evidenz:** [E]

#### JW-P13 · Kleinterz-Durzyklus (8 Takte)

- **Taktart:** 4/4 · **Akkorde je Takt:** `C` | `Eb` | `F#` | `A` | `C` | `Eb` | `F#` | `A` · **XYZ:** 0,55 / 0,75 / 0,75 (mIU)
- **Töne/Dauern:** `G4/2 C5/2 E5/2 C5/2 G5/4 E5/4 | Bb4/2 Eb5/2 G5/2 Eb5/2 Bb5/4 G5/4 | C#4/2 F#4/2 A#4/2 F#4/2 C#5/4 A#4/4 | E4/2 A4/2 C#5/2 A4/2 E5/4 C#5/4 | G4/2 C5/2 E5/2 C5/2 G5/4 E5/4 | Bb4/2 Eb5/2 G5/2 Eb5/2 Bb5/4 G5/4 | C#5/2 F#5/2 A#5/2 F#5/2 C#6/8 | A5/16`
- **Gipfel:** D♭6 in Takt 7 · **Schlusston:** A · **Artikulation:** marcato
- **Verfahren:** Zelle bleibt, Harmonie wandert; Registerwechsel in Takt 3 hält die Linie im Rahmen; Gipfel Takt 7 · **Bauplan:** Zelle ×7 transponiert → Halt · **Evidenz:** [E]

#### JW-P14 · Triumphphrase (8 Takte)

- **Taktart:** 4/4 · **Akkorde je Takt:** `C` | `C` | `Am` | `F` | `Ab` | `Bb` | `C` | `C` · **XYZ:** 0,85 / 0,85 / 0,35 (HIS)
- **Töne/Dauern:** `G4/4 C5/8 E5/4 | G5/12 E5/4 | C5/4 A4/4 E5/8 | F5/8 A5/8 | Ab5/8 Eb5/4 C5/4 | D5/4 F5/4 Bb5/8 | C6/16 | C6/8 G5/8`
- **Gipfel:** C6 in Takt 7, 8 · **Schlusston:** G · **Artikulation:** marcato, breit
- **Verfahren:** Gipfel C6 in Takt 7 (0,75); ♭VI–♭VII als Anlauf · **Bauplan:** Aufruf → Bestätigung → Umweg → Anlauf → Gipfel · **Evidenz:** [E]

#### JW-P15 · Lydisches Rätsel (4 Takte)

- **Taktart:** 4/4 · **Akkorde je Takt:** `C` | `C` | `D/C` | `D/C` · **XYZ:** 0,85 / 0,25 / 0,35 (HRS)
- **Töne/Dauern:** `E5/8 D5/4 C5/4 | G4/16 | F#5/8 E5/4 D5/4 | A4/16`
- **Gipfel:** F♯5 in Takt 3 · **Schlusston:** A · **Artikulation:** pp
- **Verfahren:** Sequenz um einen Ganzton, offenes Ende auf A (Quinte von D) · **Bauplan:** Zelle → Halt → Sequenz → offener Halt · **Evidenz:** [E]

#### JW-P16 · Hexatonischer Bogen (8 Takte)

- **Taktart:** 4/4 · **Akkorde je Takt:** `C` | `Cm` | `Ab` | `Abm` | `E` | `Em` | `C` | `C` · **XYZ:** 0,45 / 0,40 / 0,55 (mmm)
- **Töne/Dauern:** `E4/4 G4/4 C5/8 | Eb5/8 G4/8 | Ab4/4 C5/4 Eb5/8 | B4/8 Eb5/8 | E5/4 G#5/4 B5/8 | G5/8 E5/8 | C5/8 G4/8 | C5/16`
- **Gipfel:** B5 in Takt 5 · **Schlusston:** C · **Artikulation:** legato
- **Verfahren:** Halbtonverschiebungen der Melodie folgen den P/L-Schritten · **Bauplan:** Zyklus → Gipfel Takt 5 → Heimkehr · **Evidenz:** [E]

#### JW-P17 · Walzer-Scherzo (8 Takte)

- **Taktart:** 3/4 · **Akkorde je Takt:** `C` | `G7` | `G7` | `C` | `F` | `C` | `G7` | `C` · **XYZ:** 0,75 / 0,45 / 0,50 (Hmm)
- **Töne/Dauern:** `E5/2 F5/2 G5/8 | F5/4 D5/4 B4/4 | G4/4 r/2 A4/2 B4/4 | C5/12 | A5/2 G5/2 F5/8 | E5/4 G5/4 C5/4 | D5/4 B4/4 F5/4 | E5/8 r/4`
- **Gipfel:** A5 in Takt 5 · **Schlusston:** E · **Artikulation:** leggiero
- **Verfahren:** Pause als Witz in Takt 3; Frage endet auf C (Takt 4), Antwort auf E (offen) · **Bauplan:** Frage (1–4) / Antwort (5–8) · **Evidenz:** [E]

#### JW-P18 · Archaische Mollhymne (4 Takte)

- **Taktart:** 4/4 · **Akkorde je Takt:** `Cm` | `Bb` | `Fm` | `Cm` · **XYZ:** 0,20 / 0,75 / 0,25 (DIS)
- **Töne/Dauern:** `C4/8 Eb4/4 G4/4 | F4/8 D4/8 | Ab4/8 F4/4 C5/4 | G4/16`
- **Gipfel:** C5 in Takt 3 · **Schlusston:** G · **Artikulation:** marcato, breit
- **Verfahren:** nur Akkordtöne auf Zählzeiten, Schluss auf der Quinte (fest, nicht offen) · **Bauplan:** Aufschwung → Fall → Gipfel → Halt · **Evidenz:** [E]

#### JW-P19 · Neugieriges Staccato-Planing (4 Takte)

- **Taktart:** 4/4 · **Akkorde je Takt:** `C` | `D/C` | `E/C` | `D/C` · **XYZ:** 0,75 / 0,25 / 0,70 (HRU)
- **Töne/Dauern:** `E5/1 r/1 G5/1 r/1 C6/2 r/6 G5/2 E5/2 | F#5/1 r/1 A5/1 r/1 D6/2 r/6 A5/2 F#5/2 | G#5/1 r/1 B5/1 r/1 E6/2 r/6 B5/2 G#5/2 | A5/2 F#5/2 D5/4 C5/8`
- **Gipfel:** E6 in Takt 3 · **Schlusston:** C · **Artikulation:** staccato
- **Verfahren:** Zelle wandert mit den Klängen parallel (Planing); Schluss auf dem Pedalton C · **Bauplan:** Zelle ×3 sequenziert → Schluss · **Evidenz:** [E]

#### JW-P20 · Lydische Schleifenphrase (8 Takte)

- **Taktart:** 4/4 · **Akkorde je Takt:** `C`+`D` | `C`+`D` | `C`+`D` | `C`+`D` | `C`+`D` | `C`+`D` | `Em` | `D` · **XYZ:** 0,90 / 0,80 / 0,65 (HIU)
- **Töne/Dauern:** `G5/4 E5/4 F#5/4 A5/4 | C6/4 G5/4 A5/4 D6/4 | E6/8 D6/4 F#5/4 | G5/2 C6/2 E6/4 D6/8 | C6/4 E6/4 D6/8 | G6/8 F#6/4 E6/4 | B5/4 G5/4 E5/8 | F#5/4 A5/4 D6/8`
- **Gipfel:** G6 in Takt 6 · **Schlusston:** D · **Artikulation:** marcato, leicht
- **Verfahren:** Gipfel G6 in Takt 6; offenes Ende auf D für die Schleife · **Bauplan:** Anlauf → Bestätigung → Gipfel → offener Halt · **Evidenz:** [E]

#### JW-P21 · Archaischer Choral über Dies-irae-Bass (8 Takte)

- **Taktart:** 4/4 · **Akkorde je Takt:** `Cm` | `G/B` | `Cm` | `Fm/Ab` | `G/B` | `Cm/G` | `Fm/Ab` | `Ab` · **XYZ:** 0,15 / 0,75 / 0,25 (DIS)
- **Töne/Dauern:** `G4/16 | G4/8 D4/8 | Eb4/16 | C4/8 F4/8 | D4/16 | Eb4/8 G4/8 | Ab4/8 F4/8 | Eb4/16`
- **Gipfel:** A♭4 in Takt 7 · **Schlusston:** E♭ · **Artikulation:** legato, Chor
- **Verfahren:** Oberstimme in Ganzen und Halben, nur Akkordtöne; Gipfel A♭4 in Takt 7 · **Bauplan:** Choralzeilen 2 + 2 + 4 · **Evidenz:** [E]

#### JW-P22 · Spannungsphrase mit Atempausen (4 Takte)

- **Taktart:** 4/4 · **Akkorde je Takt:** `Cm(b6)` | `Dm(addb9)` | `EbmM7` | `Dm(b6)` · **XYZ:** 0,30 / 0,20 / 0,65 (DRU)
- **Töne/Dauern:** `C4/2 Eb4/2 Ab4/4 r/8 | D4/2 F4/2 Eb4/4 r/8 | Eb4/2 Gb4/2 D5/4 r/8 | D4/2 F4/2 Bb4/4 r/8`
- **Gipfel:** D5 in Takt 3 · **Schlusston:** B♭ · **Artikulation:** pp
- **Verfahren:** jede Zelle endet auf dem Zusatzton, dann halber Takt Stille · **Bauplan:** Zelle ×4 stufenweise versetzt · **Evidenz:** [E]

#### JW-P23 · Frage hoch – Antwort tief (8 Takte)

- **Taktart:** 4/4 · **Akkorde je Takt:** `Cmaj7` | `Fmaj7` | `Cmaj7` | `Fmaj7` | `Eb` | `D` | `Db` | `C` · **XYZ:** 0,75 / 0,35 / 0,55 (HRm)
- **Töne/Dauern:** `E6/3 r/1 B5/2 r/2 G5/4 r/4 | A5/3 r/1 E5/2 r/2 C5/4 r/4 | E4/3 r/1 B3/2 r/2 G3/4 r/4 | A3/3 r/1 E3/2 r/2 C3/4 r/4 | G5/4 Bb5/4 Eb6/8 | F#5/4 A5/4 D6/8 | F5/4 Ab5/4 Db6/8 | E5/4 G5/4 C6/8`
- **Gipfel:** E6 in Takt 1 · **Schlusston:** C · **Artikulation:** staccato, dann legato
- **Verfahren:** Frage–Antwort über das Register (Takte 1–2 hoch, 3–4 zwei Oktaven tiefer), dann paralleler Abstieg · **Bauplan:** Frage / Antwort / Planing-Abstieg · **Evidenz:** [E]

#### JW-P24 · Asymmetrische 6-Takt-Phrase (3 + 3)

- **Taktart:** 4/4 · **Akkorde je Takt:** `Cm` | `F#m` | `Cm` | `F#m` | `Bbm` | `Abm` · **XYZ:** 0,15 / 0,70 / 0,35 (DIS)
- **Töne/Dauern:** `G4/8 C5/8 | C#5/12 r/4 | Eb5/8 G5/8 | F#5/8 A4/8 | Bb4/4 Db5/4 F5/8 | Eb5/16`
- **Gipfel:** G5 in Takt 3 · **Schlusston:** E♭ · **Artikulation:** marcato, breit
- **Verfahren:** zwei Dreitaktgruppen; Gipfel F5 in Takt 5, Schluss auf der Quinte von A♭m · **Bauplan:** 3 + 3 Takte · **Evidenz:** [E]

### F.3 Wiedererkennbarkeit, Motivgedächtnis und Übergabe zwischen Rollen

| Eigenschaft | bei Variation | Begründung |
|---|---|---|
| Kontur (Richtungsfolge) und relative Sprunggrößen | erhalten; Intervalle dürfen sich bei Harmonie- oder Systemwechsel um einen Halbton ändern | Moduswechsel des Hauptthemas bleibt erkennbar (S1) [N] |
| Rhythmus des Kopfes (erste 3–5 Töne) | erhalten; Vergrößerung/Verkleinerung ×2 erlaubt | Zellenrhythmen als Identität: Galopp, Fanfarenkopf, lang-lang-kurz-kurz-lang (S24) [N] |
| Zielton (Position und Länge) | erhalten, im neuen Klang Akkordton | Richards zum Zielton (S11) [N] |
| Charakteristisches Intervall (verm. Terz, ♯4, kleine Terz nach Repetition, übermäßige Sekunde) | erhalten | Lehman-Katalog (S1, S24) [N] |
| Harmonik, Register, Besetzung, Tempo, Artikulation | frei | Williams: Themen „in Dur, Moll, schnell, langsam, umgekehrt, gedehnt“ (zit. in S25) [N] |

**Verfahren mit dem vorhandenen Motivgedächtnis** [E]: (1) früh zweimal unverändert etablieren; (2) danach Fragmente in Nebenrollen; (3) Umharmonisierung mit gleichem Zielton; (4) Systemwechsel: jeden Ton auf den nächsten Ton des neuen Vorrats verschieben, Richtung und Rhythmus behalten, Anfangs- und Zielton als Akkordtöne setzen (JW-T04, JW-T06, JW-T08, JW-T10); (5) Vergrößerung bei sinkender Intensität, Kanon bei steigender; (6) **Übergabe Gegenstimme → Hauptmelodie** mit derselben Phrase (JW-S25, Takte 9–16 → 17–24) und Rückgabe als Fragment (Takte 29–30); (7) Frage–Antwort über das Register (JW-P23). Ein überzeugendes Motiv darf lange wiederkehren; es gibt keine Pflicht, nach einer Taktzahl zu wechseln.

## G Vollständig koordinierte Modellstudien (30)

Jede Studie ist aus den Vorlagen C–F zusammengesetzt. Die Tabellen enthalten Einsatzpositionen (Raster), Dauern (aus dem Raster), Tonhöhenregeln, Dynamik und aktive Takte; die erzeugten Noten stehen vollständig in `JW_Studien_Ereignisse_Kanonisch.csv` und als MIDI (960 PPQ, eine Spur pro Rolle) im Archiv. Die MIDI-Programme dienen nur dem Probehören. Studien ohne Hauptmelodie: 19 von 30.

### G.1 Bestand (JW-S01–S16, geprüft)

### JW-S01 · Lauern im Dunkeln

- **Charakter:** Jemand schleicht durch einen dunklen Gang; noch ist nichts geschehen.
- **XYZ-Anker:** 0,15 / 0,20 / 0,45 (DRm) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 66–80 (MIDI-Beispiel ♩ = 72) · **Harmonik:** JW-H41 · **Tonvorrat:** Phrygisch
- **Akkorde je Takt:** `Cm` | `Cm` | `Db/C` | `Cm` | `Cm` | `Cm` | `Db/C` | `Cm`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 48, 3 Stimmen | 5, 6, 7, 8 | 40 · Dynamik je Takt ×1,00 1,00 1,00 1,00 0,80 0,90 1,00 1,10 |
| LB Langer Bass | `X---------------\|----------------  (wiederholt)` | fest: C2 | 1–8 | 55 |
| KB Kurzer Bass | `X.......x.......  (wiederholt)` | Bass-Töne `R` ab MIDI 24 | 5, 6, 7, 8 | 60 |
| TU Tupfer | `......x.........\|..........x.....  (wiederholt)` | oberster Akkordton ab MIDI 79, dann abwärts zyklisch | 1–8 | 45 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 60 |

- **Nicht beteiligt:** Kurze Fläche, Arpeggio, Stich, Hauptmelodie
- **Gegenstimme:** `r/16 | r/16 | C4/2 r/2 Db4/2 r/10 | Eb4/2 r/2 Db4/2 r/2 C4/8 | r/16 | r/16 | r/8 G3/2 r/2 Ab3/4 | G3/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   · · · · ● ● ● ●
LB   ● ○ ● ○ ● ○ ● ○
KB   · · · · ● ● ● ●
TU   ● ● ● ● ● ● ● ●
GS   · · ● ● · · ● ●
```

- **Zusammenhang der Rollen:** Pedal C trägt alles; Tupfer und Herzschlag teilen sich die Zählzeiten (Tupfer auf Offbeats, Herzschlag auf 1 und 3). Die Gegenstimme antwortet nur dort, wo der D♭-Klang erscheint.
- **Dynamik:** pp durchgehend; Fläche ab Takt 5 von pp zu p. · **Pausen:** Takte 1–2 und 5–6 ohne Melodie; in der Gegenstimme mehr Pause als Ton.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Gegenstimme trägt der Wechsel Cm ↔ D♭/C zusammen mit Tupfern und Herzschlag die Szene.
- **Variation:** Tupfer-Positionen verschieben; Herzschlag schon ab Takt 1; D♭/C durch D♭maj7/C ersetzen. · **Fortsetzung:** Übergang JW-T01 (Lauern → Angst) oder Wiederholung mit Gegenstimme eine Oktave tiefer.
- **Bezug:** JW-H41, JW-R26, JW-B01, JW-P04
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 1 3 2 4 3 5 4; Melodietöne auf Zählzeiten als Akkordton: GS 6/8; MIDI `JW-S01.mid`, 40 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 6/2/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S02 · Marschierende Bedrohung

- **Charakter:** Eine Übermacht rückt an; die Lage ist klar und ausweglos.
- **XYZ-Anker:** 0,15 / 0,80 / 0,35 (DIS) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 88–104 (MIDI-Beispiel ♩ = 96) · **Harmonik:** JW-H13 · **Tonvorrat:** Hex-C
- **Akkorde je Takt:** `Cm` | `Abm/C` | `Cm` | `Abm/C` | `Cm` | `Abm/C` | `Em/B` | `Cm`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 55, 3 Stimmen | 1–8 | 55 |
| KF Kurze Fläche | `X..xX...X..xX.x.\|X..xX...X.x.X---  (wiederholt)` | Akkordtöne eng ab MIDI 48, 3 Stimmen | 1–8 | 85 |
| LB Langer Bass | `X-------X-------  (wiederholt)` | fest: C2 | 1–8 | 80 |
| ST Stich | `X...............\|X.......X.......  (wiederholt)` | fest: C2 G2 | 1–8 | 95 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 80 |

- **Nicht beteiligt:** Kurzer Bass, Arpeggio, Tupfer, Hauptmelodie
- **Gegenstimme:** `r/16 | C4/6 Eb4/2 Ab4/8 | G4/16 | r/16 | r/16 | C4/6 Eb4/2 Ab4/8 | G4/16 | r/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ● ● ● ● ● ● ●
KF   ● ● ● ● ● ● ● ●
LB   ● ● ● ● ● ● ● ●
ST   ● ● ● ● ● ● ● ●
GS   · ● ● · · ● ● ·
```

- **Zusammenhang der Rollen:** Kurze Fläche und Stich teilen den Marschrhythmus (Stich auf 1, Fläche füllt); der Pedalbass liegt in Halben. Kein Arpeggio, kein Kurzer Bass: die Intensität entsteht aus Schichtung und Register, nicht aus mehr Noten.
- **Dynamik:** f, Akzente ff; Takt 7 (Em/B) einen Grad leiser als Fremdkörper. · **Pausen:** Gegenstimme pausiert in den Takten 1, 4–5 und 8.
- **Ohne Hauptmelodie/Gegenstimme:** Funktioniert ohne Gegenstimme vollständig: Marschrhythmus und Hexatonik tragen.
- **Variation:** Abm/C halbtaktig mit Cm wechseln; im zweiten Durchgang kurzer Bass mit JW-B11 dazu. · **Fortsetzung:** JW-T02 (Angst → Action) oder JW-H22 als Steigerung.
- **Bezug:** JW-H13, JW-R01, JW-M28
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 4 5 5 4 4 5 5 4; Melodietöne auf Zählzeiten als Akkordton: GS 6/6; MIDI `JW-S02.mid`, 220 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 8/0/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S03 · Geheimnis

- **Charakter:** Ein verlassener Raum gibt sein Geheimnis preis.
- **XYZ-Anker:** 0,30 / 0,25 / 0,40 (DRm) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 54–66 (MIDI-Beispiel ♩ = 60) · **Harmonik:** JW-H40 · **Tonvorrat:** Pantriadisch
- **Akkorde je Takt:** `Cm` | `Ab/C` | `Am/C` | `F/C` | `Fm/C` | `F#dim/C` | `Ab/C` | `Cm`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 55, 4 Stimmen | 1–8 | 50 |
| LB Langer Bass | `X---------------\|----------------  (wiederholt)` | fest: C2 | 1–8 | 50 |
| AR Arpeggio | `X.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.  (wiederholt)` | Akkordtöne (4) ab MIDI 67 über 2 Oktaven, aufwärts zyklisch | 3, 4, 7, 8 | 45 |
| TU Tupfer | `x.....x...x.....\|..x.....x.....x.  (wiederholt)` | oberster Akkordton ab MIDI 84, dann abwärts zyklisch | 1, 2, 5, 6 | 40 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 55 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Stich, Hauptmelodie
- **Gegenstimme:** `C4/6 F4/2 B4/8 | Bb4/16 | r/16 | r/16 | C4/6 F4/2 B4/8 | A4/16 | r/16 | r/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ● ● ● ● ● ● ●
LB   ● ○ ● ○ ● ○ ● ○
AR   · · ● ● · · ● ●
TU   ● ● · · ● ● · ·
GS   ● ● · · ● ● · ·
```

- **Zusammenhang der Rollen:** Alle Klänge enthalten C; der liegende Ton ist der Faden. Tupfer und Arpeggio lösen einander ab (nie gleichzeitig), die Gegenstimme erscheint nur in den Tupfer-Takten.
- **Dynamik:** pp bis p; Arpeggio ein Grad leiser als die Fläche. · **Pausen:** Gegenstimme schweigt Takte 3–4 und 7–8.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Gegenstimme bleibt die Wanderung über gemeinsame Töne voll wirksam.
- **Variation:** C in die Oberstimme legen (Bass pausiert); Tupfer in Triolen (JW-R34). · **Fortsetzung:** JW-T03 (Geheimnis → Staunen).
- **Bezug:** JW-H40, JW-R14, JW-R11, JW-M23
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 4 3 3 2 4 3 3 2; Melodietöne auf Zählzeiten als Akkordton: GS 3/6; MIDI `JW-S03.mid`, 74 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 4/4/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S04 · Psychologisches Unbehagen

- **Charakter:** Dunkel, leise, aber innerlich hochgradig unruhig: jemand ahnt, dass er belogen wird.
- **XYZ-Anker:** 0,20 / 0,25 / 0,75 (DRU) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 60–72 (MIDI-Beispiel ♩ = 66) · **Harmonik:** JW-H46 · **Tonvorrat:** Okt-A
- **Akkorde je Takt:** `Cm/F#` | `Cm/F#` | `Cm/Db` | `Cm/Db` | `Cm/F#` | `Cm/F#` | `Cm` | `Cm`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X---------------\|----------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 55, 3 Stimmen | 1–8 | 45 |
| LB Langer Bass | `X---------------\|----------------  (wiederholt)` | Bass-Töne `b` ab MIDI 30 | 1–8 | 55 |
| AR Arpeggio | `X..x..x..x..x..x\|..x..x..x..x..x.  (wiederholt)` | Akkordtöne (4) ab MIDI 67 über 2 Oktaven, aufwärts zyklisch | 1–8 | 45 |
| TU Tupfer | `x...........x...\|......x.........  (wiederholt)` | oberster Akkordton ab MIDI 86, dann abwärts zyklisch | 1–8 | 40 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 50 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Stich, Hauptmelodie
- **Gegenstimme:** `r/16 | r/16 | r/16 | C5/2 Db5/2 Bb4/2 C5/10 | r/16 | r/16 | r/16 | C5/2 Db5/2 Bb4/2 C5/10`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ○ ● ○ ● ○ ● ○
LB   ● ○ ● ○ ● ○ ● ○
AR   ● ● ● ● ● ● ● ●
TU   ● ● ● ● ● ● ● ●
GS   · · · ● · · · ●
```

- **Zusammenhang der Rollen:** Unruhe entsteht aus dem Dissonanzbass unter unverändertem Cm und aus dem 3-gegen-4 des Arpeggios, nicht aus Tempo. Die Fläche bleibt stehen; nur der Boden wechselt.
- **Dynamik:** pp; Arpeggio ohne Akzente gleichmäßig leise. · **Pausen:** Gegenstimme nur in den Takten 4 und 8.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Gegenstimme bleibt die Unruhe erhalten; sie liegt im Bass und in der Rhythmusschicht.
- **Variation:** Bass nur auf Zählzeit 1, sonst Pause; Arpeggio rückwärts. · **Fortsetzung:** Weiter mit JW-H14 (Tritonus-Mollwechsel) oder JW-T07.
- **Bezug:** JW-H46, JW-R20, JW-B09, JW-M14
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 4 2 4 3 4 2 4 3; Melodietöne auf Zählzeiten als Akkordton: GS 2/4; MIDI `JW-S04.mid`, 80 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 5/3/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S05 · Trauer

- **Charakter:** Abschied; jemand bleibt allein zurück.
- **XYZ-Anker:** 0,25 / 0,25 / 0,15 (DRS) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 56–66 (MIDI-Beispiel ♩ = 63) · **Harmonik:** JW-H34 · **Tonvorrat:** Moll gesamt
- **Akkorde je Takt:** `Cm` | `Cm` | `Abmaj7` | `Fm6` | `Cm/G` | `G7sus4` | `G7` | `Cm`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 53, 4 Stimmen | 1–8 | 50 |
| LB Langer Bass | `X---------------  (wiederholt)` | Bass-Töne `b` ab MIDI 36 | 1–8 | 55 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 50 |
| HM Hauptmelodie | — | notiert (siehe unten) | 1–8 | 70 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Arpeggio, Tupfer, Stich
- **Hauptmelodie:** `G4/8 Eb4/4 D4/4 | C4/12 r/4 | Eb4/4 G4/4 C5/8 | Ab4/8 F4/4 D4/4 | Eb4/8 G4/8 | C5/8 F4/8 | B3/8 D4/4 F4/4 | C4/16`
- **Gegenstimme:** `Eb3/16 | D3/8 Eb3/8 | C3/16 | C3/8 D3/8 | Eb3/16 | F3/8 Eb3/8 | D3/16 | Eb3/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ● ● ● ● ● ● ●
LB   ● ● ● ● ● ● ● ●
GS   ● ● ● ● ● ● ● ●
HM   ● ● ● ● ● ● ● ●
```

- **Zusammenhang der Rollen:** Nur vier Rollen. Die Gegenstimme bewegt sich in Ganzen und Halben unter der Melodie und füllt deren Atempause in Takt 2.
- **Dynamik:** p, Melodie mp; Takt 3 Höhepunkt mp, Takt 8 pp. · **Pausen:** Melodie atmet in Takt 2; keine Rhythmusrollen.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Hauptmelodie trägt die Gegenstimme mit den Akkorden; die Studie bleibt eine vollständige Trauerfläche.
- **Variation:** Melodie in die Gegenstimme legen (eine Oktave tiefer), Hauptmelodie aus. · **Fortsetzung:** Wiederholung mit JW-H35 (Undulation) oder JW-T05 rückwärts.
- **Bezug:** JW-H34, JW-P08, JW-B05
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 4 4 4 4 4 4 4 4; Melodietöne auf Zählzeiten als Akkordton: HM 17/18, GS 9/11; MIDI `JW-S05.mid`, 64 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): HM 17/1/0, GS 9/2/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S06 · Wärme und Geborgenheit

- **Charakter:** Ein Kind wird zu Bett gebracht; draußen ist es still.
- **XYZ-Anker:** 0,75 / 0,20 / 0,10 (HRS) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 70–84 (MIDI-Beispiel ♩ = 76) · **Harmonik:** JW-H36 · **Tonvorrat:** Dur
- **Akkorde je Takt:** `Cadd9` | `Cadd9` | `Fadd9/C` | `Fadd9/C` | `Am7` | `Am7` | `Gsus4` | `Cadd9`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X---------------\|----------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 55, 4 Stimmen | 1–8 | 45 |
| LB Langer Bass | `X---------------\|----------------  (wiederholt)` | Bass-Töne `b` ab MIDI 36 | 1–8 | 50 |
| AR Arpeggio | `X.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.  (wiederholt)` | Akkordtöne (4) ab MIDI 67 über 2 Oktaven, auf und ab | 1–8 | 50 |
| TU Tupfer | `x...............\|........x.......  (wiederholt)` | oberster Akkordton ab MIDI 84, dann abwärts zyklisch | 1–8 | 40 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 55 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Stich, Hauptmelodie
- **Gegenstimme:** `r/16 | r/8 E5/2 D5/2 C5/4 | r/16 | r/8 A4/2 G4/2 F4/4 | r/16 | r/8 E5/2 D5/2 C5/4 | r/16 | r/8 D5/2 C5/2 G4/4`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ○ ● ○ ● ○ ● ○
LB   ● ○ ● ○ ● ○ ● ○
AR   ● ● ● ● ● ● ● ●
TU   ● ● ● ● ● ● ● ●
GS   · ● · ● · ● · ●
```

- **Zusammenhang der Rollen:** Arpeggio auf und ab in Achteln, Tupfer markiert nur zwei Punkte pro zwei Takte. Die Gegenstimme antwortet jeweils im zweiten Takt, also nach einer Phrase der Sprecher.
- **Dynamik:** p; Arpeggio pp. · **Pausen:** Gegenstimme nur in geraden Takten.
- **Ohne Hauptmelodie/Gegenstimme:** Studie ist ohne Hauptmelodie gebaut.
- **Variation:** Arpeggio nur aufwärts; Am7 durch Fmaj7/A. · **Fortsetzung:** JW-T05 (Wärme → Melancholie).
- **Bezug:** JW-H36, JW-R14, JW-M33
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 4 3 4 3 4 3 4 3; Melodietöne auf Zählzeiten als Akkordton: GS 8/8; MIDI `JW-S06.mid`, 102 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 11/1/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S07 · Romantik

- **Charakter:** Zwei Menschen, ein Balkon, ein unausgesprochenes Gefühl.
- **XYZ-Anker:** 0,60 / 0,40 / 0,25 (mmS) · **Länge:** 8 Takte · **Taktart:** 6/8 · **Tempo:** ♩. = 50–60 (MIDI-Beispiel ♩ = 84) · **Harmonik:** JW-H38 · **Tonvorrat:** Dur-Moll-Mischung
- **Akkorde je Takt:** `Cmaj7` | `Fm6/C` | `Cmaj7` | `Abmaj7/C` | `Fmaj7` | `Fm6` | `Csus4` | `C`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X-----------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 55, 3 Stimmen | 5, 6, 7, 8 | 40 |
| KB Kurzer Bass | `X-----x-----\|X-----......  (wiederholt)` | Bass-Töne `b 5` ab MIDI 36 | 1–8 | 55 |
| AR Arpeggio | `X.x.x.X.x.x.  (wiederholt)` | Akkordtöne (4) ab MIDI 60 über 2 Oktaven, aufwärts zyklisch | 1–8 | 50 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 50 |
| HM Hauptmelodie | — | notiert (siehe unten) | 1–8 | 70 |

- **Nicht beteiligt:** Kurze Fläche, Langer Bass, Tupfer, Stich
- **Hauptmelodie:** `G4/4 E5/6 D5/2 | C5/6 Ab4/6 | B4/2 C5/4 E5/6 | Eb5/6 G5/6 | A5/8 G5/4 | F5/6 D5/2 C5/4 | F5/6 E5/6 | E5/4 C5/8`
- **Gegenstimme:** `r/12 | r/6 F3/2 Ab3/2 C4/2 | r/12 | r/6 Ab3/2 C4/2 Eb4/2 | r/12 | r/12 | r/12 | r/12`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   · · · · ● ● ● ●
KB   ● ● ● ● ● ● ● ●
AR   ● ● ● ● ● ● ● ●
GS   · ● · ● · · · ·
HM   ● ● ● ● ● ● ● ●
```

- **Zusammenhang der Rollen:** 6/8-Wiegen im Arpeggio, Bass mit Quint-Nachschlag. Die Mollschatten (Takt 2 und 4) beantwortet die Gegenstimme mit einem Arpeggio-Anstieg in der Tiefe.
- **Dynamik:** p → mf in Takt 5 (Gipfel A5) → p. · **Pausen:** Bass pausiert in der zweiten Hälfte jedes zweiten Takts.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Melodie bleibt eine wiegende Liebesfläche mit Mollschatten.
- **Variation:** Hauptmelodie aus, Gegenstimme in allen Takten; 4/4-Fassung mit JW-P12. · **Fortsetzung:** JW-T06 (Romantik → Bedrohung).
- **Bezug:** JW-H38, JW-R16, JW-P12
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 4 3 4 4 4 4 4; Melodietöne auf Zählzeiten als Akkordton: HM 11/12, GS 2/2; MIDI `JW-S07.mid`, 97 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): HM 16/3/0, GS 6/0/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S08 · Staunen und Entdeckung

- **Charakter:** Die Tür öffnet sich; dahinter liegt etwas Unbegreifliches.
- **XYZ-Anker:** 0,80 / 0,35 / 0,50 (HRm) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 60–72 (MIDI-Beispiel ♩ = 66) · **Harmonik:** JW-H50 · **Tonvorrat:** Hex-C
- **Akkorde je Takt:** `Cmaj7` | `Cmaj7` | `Ab/C` | `E/C` | `Ab/C` | `E/C` | `Cmaj7` | `Cmaj7`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 60, 4 Stimmen | 1–8 | 45 |
| LB Langer Bass | `X---------------\|----------------  (wiederholt)` | fest: C2 | 3, 4, 5, 6, 7, 8 | 50 |
| AR Arpeggio | `XxxxXxxxXxxxXxxx\|XxxxXxxxXxxx----  (wiederholt)` | Akkordtöne (4) ab MIDI 72 über 2 Oktaven, aufwärts zyklisch | 3, 4, 5, 6 | 40 |
| TU Tupfer | `x.....x...x.....\|..x.....x.....x.  (wiederholt)` | oberster Akkordton ab MIDI 88, dann abwärts zyklisch | 1, 2, 7, 8 | 35 |
| HM Hauptmelodie | — | notiert (siehe unten) | 1–8 | 65 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Stich, Gegenstimme
- **Hauptmelodie:** `G4/4 C5/4 E5/8 | D5/4 B4/4 G4/8 | Ab4/4 C5/4 Eb5/8 | E5/4 G#5/4 B5/8 | C6/8 Ab5/8 | G#5/4 E5/4 B4/8 | C5/8 E5/8 | G5/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ● ● ● ● ● ● ●
LB   · · ● ○ ● ○ ● ○
AR   · · ● ● ● ● · ·
TU   ● ● · · · · ● ●
HM   ● ● ● ● ● ● ● ●
```

- **Zusammenhang der Rollen:** Der Bass setzt zwei Takte aus und kommt mit dem ersten Großterzwechsel. Tupfer (außen) und Sechzehntel-Arpeggio (Mitte) lösen sich ab.
- **Dynamik:** pp → mp (Takt 5) → pp. · **Pausen:** Bass Takte 1–2; Arpeggio nur in der Mitte.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Melodie: der Großterzwechsel über Pedal und der Wechsel Tupfer–Arpeggio tragen.
- **Variation:** E/C durch E/C mit F♯ (lydisch). · **Fortsetzung:** JW-T04 (Staunen → Triumph).
- **Bezug:** JW-H50, JW-R15, JW-B28, JW-P07
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 3 4 3 4 3 4 3; Melodietöne auf Zählzeiten als Akkordton: HM 19/20; MIDI `JW-S08.mid`, 117 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): HM 19/0/1
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S09 · Magie und Fremdartigkeit

- **Charakter:** Hell, leise, unruhig: ein Zauber wirkt, ohne dass jemand ihn versteht.
- **XYZ-Anker:** 0,70 / 0,25 / 0,70 (HRU) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 66–80 (MIDI-Beispiel ♩ = 72) · **Harmonik:** JW-H25 · **Tonvorrat:** Hex-C
- **Akkorde je Takt:** `C` | `Cm` | `Ab` | `Abm` | `E` | `Em` | `C` | `C`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 60, 3 Stimmen | 1–8 | 40 |
| LB Langer Bass | `X---------------  (wiederholt)` | Bass-Töne `R` ab MIDI 36 | 1–8 | 40 |
| AR Arpeggio | `X..x..x..x..x..x\|..x..x..x..x..x.  (wiederholt)` | Akkordtöne (4) ab MIDI 72 über 2 Oktaven, aufwärts zyklisch | 1–8 | 45 |
| TU Tupfer | `x...x...x...x...  (wiederholt)` | oberster Akkordton ab MIDI 86, dann abwärts zyklisch | 1–8 | 30 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 50 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Stich, Hauptmelodie
- **Gegenstimme:** `r/16 | C5/2 B4/2 Ab4/2 G4/2 E4/4 Eb4/4 | r/16 | r/16 | r/16 | C5/2 B4/2 Ab4/2 G4/2 E4/4 Eb4/4 | r/16 | r/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ● ● ● ● ● ● ●
LB   ● ● ● ● ● ● ● ●
AR   ● ● ● ● ● ● ● ●
TU   ● ● ● ● ● ● ● ●
GS   · ● · · · ● · ·
```

- **Zusammenhang der Rollen:** Arpeggio in punktierten Achteln gegen Tupfer in Vierteln (3 gegen 4); alle Töne aus einem hexatonischen Vorrat. Helligkeit kommt aus Register und Durklängen, Unruhe aus der Kreuzrhythmik.
- **Dynamik:** pp; Tupfer ppp. · **Pausen:** Gegenstimme nur in Takt 2 und 6.
- **Ohne Hauptmelodie/Gegenstimme:** Studie ist ohne Hauptmelodie gebaut.
- **Variation:** Tupfer ganz weglassen (stabiler); Zyklus rückwärts. · **Fortsetzung:** JW-H24 (hexatonischer Pol) oder JW-S08.
- **Bezug:** JW-H25, JW-R20, JW-M30
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 4 5 4 4 4 5 4 4; Melodietöne auf Zählzeiten als Akkordton: GS 3/8; MIDI `JW-S09.mid`, 120 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 6/6/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S10 · Verspieltheit

- **Charakter:** Ein tollpatschiger Helfer stolpert durch die Werkstatt.
- **XYZ-Anker:** 0,75 / 0,40 / 0,60 (Hmm) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 112–132 (MIDI-Beispiel ♩ = 120) · **Harmonik:** JW-H51 · **Tonvorrat:** Pantriadisch
- **Akkorde je Takt:** `C` | `Eb` | `C` | `Ab` | `F` | `Db` | `G7` | `C`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `x.x...x.x.x.....\|x...x.x.....x...  (wiederholt)` | Akkordtöne eng ab MIDI 60, 3 Stimmen | 1–8 | 60 |
| KB Kurzer Bass | `x.x.x.x.x.x.x.x.  (wiederholt)` | Bass-Töne `R d d 5` ab MIDI 36 | 1–8 | 65 |
| ST Stich | `................\|............X...  (wiederholt)` | fest: C3 G3 | 8 | 80 |
| HM Hauptmelodie | — | notiert (siehe unten) | 1–8 | 70 |

- **Nicht beteiligt:** Lange Fläche, Langer Bass, Arpeggio, Tupfer, Gegenstimme
- **Hauptmelodie:** `E5/2 r/2 G5/2 E5/2 C5/4 r/4 | G5/2 r/2 Bb5/2 G5/2 Eb5/4 r/4 | C5/2 E5/2 G5/2 E5/2 C5/4 r/4 | Ab4/2 C5/2 Eb5/4 C5/8 | A5/2 r/2 C6/2 A5/2 F5/4 r/4 | Ab5/2 r/2 F5/2 Db5/2 Ab4/4 r/4 | B4/2 D5/2 F5/2 D5/2 B4/4 r/4 | C5/4 r/4 G4/2 r/2 C5/4`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
KF   ● ● ● ● ● ● ● ●
KB   ● ● ● ● ● ● ● ●
ST   · · · · · · · ●
HM   ● ● ● ● ● ● ● ●
```

- **Zusammenhang der Rollen:** Staccato-Wanderbass und lückenhafte kurze Fläche; die Pausen stehen an verschiedenen Stellen, damit nie ein Raster entsteht. Stich nur als Pointe in Takt 8.
- **Dynamik:** mp, staccato; Stich f. · **Pausen:** Fläche mit großen Lücken; Hauptmelodie mit Viertelpausen.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Melodie: Wanderbass und lückenhafte Fläche ergeben einen verspielten Begleitsatz mit chromatischen Überraschungen.
- **Variation:** Db durch Gb (Tritonus) für mehr Witz; Bass pausiert in Takt 6. · **Fortsetzung:** JW-H52 (Marsch mit chromatischem Moment).
- **Bezug:** JW-H51, JW-R33, JW-B14, JW-P09
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 3 3 3 3 3 3 4; Melodietöne auf Zählzeiten als Akkordton: HM 24/24; MIDI `JW-S10.mid`, 207 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): HM 33/0/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S11 · Helle Verfolgungsjagd

- **Charakter:** Hell, kraftvoll, hochgradig unruhig: die Helden jagen hinter etwas her, mit Freude.
- **XYZ-Anker:** 0,80 / 0,75 / 0,70 (HIU) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 132–152 (MIDI-Beispiel ♩ = 144) · **Harmonik:** JW-H04 · **Tonvorrat:** Lydisch
- **Akkorde je Takt:** `C` | `C` | `D` | `Em` | `Am` | `D` | `C` | `C`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `X..X..X.X..X.X..\|X..X..X.X.......  (wiederholt)` | Akkordtöne eng ab MIDI 60, 3 Stimmen | 3, 4, 5, 6, 7, 8 | 80 |
| KB Kurzer Bass | `X..x..x.X..x..x.  (wiederholt)` | Bass-Töne `R 5 8 R 5 8` ab MIDI 36 | 1–8 | 80 |
| AR Arpeggio | `XxxxXxx.XxxxXx..\|XxxxXxx.XxXxXxXx  (wiederholt)` | Akkordtöne (4) ab MIDI 67 über 2 Oktaven, aufwärts zyklisch | 1–8 | 65 |
| ST Stich | `X...............\|................  (wiederholt)` | fest: C2 | 1, 5 | 100 |
| HM Hauptmelodie | — | notiert (siehe unten) | 1–8 | 90 |

- **Nicht beteiligt:** Lange Fläche, Langer Bass, Tupfer, Gegenstimme
- **Hauptmelodie:** `C5/2 D5/2 E5/4 G5/4 E5/4 | G5/12 r/4 | F#5/4 A5/4 F#5/4 D5/4 | E5/4 B4/4 G4/4 B4/4 | C5/4 E5/4 A5/4 C6/4 | D6/8 A5/4 F#5/4 | G5/4 E5/4 C5/4 D5/4 | C5/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
KF   · · ● ● ● ● ● ●
KB   ● ● ● ● ● ● ● ●
AR   ● ● ● ● ● ● ● ●
ST   ● · · · ● · · ·
HM   ● ● ● ● ● ● ● ●
```

- **Zusammenhang der Rollen:** Der Bass gibt 3+3+2 vor, das Arpeggio hetzt in Sechzehnteln mit Lücken, die kurze Fläche setzt Synkopen erst ab Takt 3. Kein Liegeklang: Helligkeit kommt aus Lydisch und hoher Lage.
- **Dynamik:** f; Stich ff in Takt 1 und 5. · **Pausen:** Arpeggio-Lücken auf Zählzeit 2 und 4; Melodie atmet in Takt 2.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Melodie bleiben Bassmotor, Arpeggio und Synkopen als vollständiger Actionsatz.
- **Variation:** Fläche schon ab Takt 1; Arpeggio nur jede zweite Zählzeit für Y < 0,7. · **Fortsetzung:** JW-S14 (Triumph) oder JW-T08 (Action → Ruhe).
- **Bezug:** JW-H04, JW-R09, JW-R04, JW-B18, JW-P03
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 4 3 4 4 5 4 4 4; Melodietöne auf Zählzeiten als Akkordton: HM 24/25; MIDI `JW-S11.mid`, 278 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): HM 24/2/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S12 · Dramatische Spannung

- **Charakter:** Die Zeit läuft ab; jeder Takt bringt die Gefahr näher.
- **XYZ-Anker:** 0,35 / 0,60 / 0,65 (DmU) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 100–116 (MIDI-Beispiel ♩ = 108) · **Harmonik:** JW-H19 · **Tonvorrat:** Okt-A
- **Akkorde je Takt:** `Cm` | `A/Db` | `Eb` | `C/E` | `F#m` | `Eb/G` | `Am` | `F#/Bb`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 60, 3 Stimmen | 1, 2, 3, 4 | 45 |
| KF Kurze Fläche | `X.xxX.xxX.xxX.xx\|X.xxX.xxX.x.X...  (wiederholt)` | Akkordtöne eng ab MIDI 55, 3 Stimmen | 1–8 | 70 |
| LB Langer Bass | `X---------------  (wiederholt)` | Bass-Töne `b` ab MIDI 36 | 1–8 | 70 |
| AR Arpeggio | `X...X...X...X...\|X.x.X.x.X.x.X.x.\|X.xxX.xxX.xxX.xx\|XxxxXxxxXxxxXxxx  (wiederholt)` | Akkordtöne (4) ab MIDI 67 über 2 Oktaven, aufwärts zyklisch | 5, 6, 7, 8 | 60 |
| ST Stich | `................\|............X---  (wiederholt)` | fest: C2 F#2 | 8 | 100 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 70 |

- **Nicht beteiligt:** Kurzer Bass, Tupfer, Hauptmelodie
- **Gegenstimme:** `r/16 | r/16 | r/16 | r/16 | G4/2 F#4/2 Eb4/2 C4/2 Db4/2 Eb4/2 E4/4 | F#4/2 G4/2 A4/2 Bb4/2 A4/2 G4/2 F#4/4 | G4/2 A4/2 Bb4/2 C5/2 Db5/2 Eb5/2 C5/4 | Eb5/2 F#5/2 G5/12`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ● ● ● · · · ·
KF   ● ● ● ● ● ● ● ●
LB   ● ● ● ● ● ● ● ●
AR   · · · · ● ● ● ●
ST   · · · · · · · ●
GS   · · · · ● ● ● ●
```

- **Zusammenhang der Rollen:** Der Bass steigt pro Takt einen oktatonischen Schritt; darüber Repetitionsakkorde. Ab Takt 5 löst das sich verdichtende Arpeggio die Liegefläche ab. Spannung durch Harmonie (steigender Bass) statt zusätzlicher Noten in den ersten vier Takten.
- **Dynamik:** mp → f; Stich ff im letzten Viertel. · **Pausen:** Gegenstimme Takte 1–4; Fläche Takte 5–8.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Gegenstimme bleibt die Steigerung durch Basslauf und Verdichtung vollständig.
- **Variation:** Bass abwärts als Entspannung; Repetitionsakkorde halbtaktig wechseln. · **Fortsetzung:** JW-T07 oder JW-S13.
- **Bezug:** JW-H19, JW-R08, JW-R29, JW-B07, JW-P06
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 3 3 3 4 4 4 5; Melodietöne auf Zählzeiten als Akkordton: GS 2/14; MIDI `JW-S12.mid`, 300 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 9/15/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S13 · Dunkle Action

- **Charakter:** Kampf in einer Halle; kein Ausweg, nur Vorwärts.
- **XYZ-Anker:** 0,30 / 0,85 / 0,80 (DIU) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 144–160 (MIDI-Beispiel ♩ = 152) · **Harmonik:** JW-H17 · **Tonvorrat:** Okt-A
- **Akkorde je Takt:** `C/Db` | `C/Db` | `Eb/E` | `Eb/E` | `F#/G` | `F#/G` | `A/Bb` | `A/Bb`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `X..X..X.X..X.X..\|X..X..X.X.......  (wiederholt)` | Akkordtöne eng ab MIDI 55, 3 Stimmen | 1–8 | 90 |
| KB Kurzer Bass | `XxxxXxxxXxxxXxxx  (wiederholt)` | Bass-Töne `b` ab MIDI 36 | 1–8 | 85 |
| ST Stich | `X...............\|X.......X.......  (wiederholt)` | fest: Db2 G2 | 1–8 | 100 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 85 |

- **Nicht beteiligt:** Lange Fläche, Langer Bass, Arpeggio, Tupfer, Hauptmelodie
- **Gegenstimme:** `r/16 | r/16 | Bb4/2 r/2 A4/2 G4/2 r/2 F#4/2 E4/4 | Eb4/2 r/2 Db4/2 Eb4/2 r/2 E4/2 F#4/4 | r/16 | r/16 | Bb4/2 r/2 A4/2 G4/2 r/2 F#4/2 E4/4 | Eb4/2 r/2 Db4/2 Eb4/2 r/2 E4/2 F#4/4`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
KF   ● ● ● ● ● ● ● ●
KB   ● ● ● ● ● ● ● ●
ST   ● ● ● ● ● ● ● ●
GS   · · ● ● · · ● ●
```

- **Zusammenhang der Rollen:** Der Bass übernimmt den Antrieb (Sechzehntel); das Arpeggio pausiert hier, um den Bass hörbar zu halten – ein leises Arpeggio in hoher Lage wäre ebenso möglich. Kurze Fläche synkopiert, Stich markiert 1 und die Takthälfte. Die Basstöne steigen in kleinen Terzen über die Abschnitte.
- **Dynamik:** ff; Gegenstimme f. · **Pausen:** Keine Liegefläche; Gegenstimme pausiert Takte 1–2 und 5–6.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Gegenstimme bleibt ein vollständiger Actionblock.
- **Variation:** Fläche in Takt 7–8 auf Halbe (Breite vor Abschluss); Bass in Achteln für Y < 0,75. · **Fortsetzung:** JW-S16 (Zuspitzung) oder JW-T08.
- **Bezug:** JW-H17, JW-B25, JW-R04, JW-M11
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 3 4 4 3 3 4 4; Melodietöne auf Zählzeiten als Akkordton: GS 7/12; MIDI `JW-S13.mid`, 292 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 11/9/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S14 · Triumph

- **Charakter:** Sieg; die Helden stehen vor der jubelnden Menge.
- **XYZ-Anker:** 0,85 / 0,85 / 0,30 (HIS) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 96–112 (MIDI-Beispiel ♩ = 104) · **Harmonik:** JW-H33 · **Tonvorrat:** Dur-Moll-Mischung
- **Akkorde je Takt:** `C` | `C` | `Am` | `F` | `Ab` | `Bb` | `C` | `C`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 48, 4 Stimmen | 1–8 | 70 |
| KF Kurze Fläche | `X.......X...x.x.\|X.......X.......  (wiederholt)` | Akkordtöne eng ab MIDI 55, 4 Stimmen | 1–8 | 80 |
| KB Kurzer Bass | `X.......X.......  (wiederholt)` | Bass-Töne `R 5` ab MIDI 36 | 1–8 | 85 |
| AR Arpeggio | `X.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.  (wiederholt)` | Akkordtöne (4) ab MIDI 72 über 2 Oktaven, aufwärts zyklisch | 5, 6, 7, 8 | 55 |
| ST Stich | `................\|............X---  (wiederholt)` | fest: C2 C3 | 4, 8 | 100 |
| HM Hauptmelodie | — | notiert (siehe unten) | 1–8 | 95 |

- **Nicht beteiligt:** Langer Bass, Tupfer, Gegenstimme
- **Hauptmelodie:** `G4/4 C5/8 E5/4 | G5/12 E5/4 | C5/4 A4/4 E5/8 | F5/8 A5/8 | Ab5/8 Eb5/4 C5/4 | D5/4 F5/4 Bb5/8 | C6/16 | C6/8 G5/8`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ● ● ● ● ● ● ●
KF   ● ● ● ● ● ● ● ●
KB   ● ● ● ● ● ● ● ●
AR   · · · · ● ● ● ●
ST   · · · ● · · · ●
HM   ● ● ● ● ● ● ● ●
```

- **Zusammenhang der Rollen:** Breite Halbe im Bass, Alla-breve-Akzente in der kurzen Fläche, liegender Blechteppich. Das Achtel-Arpeggio kommt erst mit ♭VI–♭VII und gibt dem Anlauf Bewegung.
- **Dynamik:** f → ff (Takt 7). · **Pausen:** Stich nur am Ende von Takt 4 und 8.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Melodie trägt die Kadenz ♭VI–♭VII–I mit Schichtung.
- **Variation:** Hauptmelodie aus: Kurze Fläche spielt Viertel, Arpeggio ab Takt 1. · **Fortsetzung:** Wiederholung eine große Terz höher (JW-H49).
- **Bezug:** JW-H33, JW-R31, JW-P14
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 4 4 4 5 5 5 5 6; Melodietöne auf Zählzeiten als Akkordton: HM 19/19; MIDI `JW-S14.mid`, 167 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): HM 19/0/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S15 · Epische Weite

- **Charakter:** Weite Landschaft, ein Schiff am Horizont.
- **XYZ-Anker:** 0,70 / 0,55 / 0,20 (HmS) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 54–66 (MIDI-Beispiel ♩ = 60) · **Harmonik:** JW-H55 · **Tonvorrat:** Dur-Moll-Mischung
- **Akkorde je Takt:** `C` | `C` | `C` | `C` | `Ab` | `Ab` | `Bb` | `Bb`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X---------------\|----------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 55, 4 Stimmen | 1–8 | 55 |
| LB Langer Bass | `X---------------  (wiederholt)` | Bass-Töne `R -8` ab MIDI 36 | 1–8 | 60 |
| AR Arpeggio | `X.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.  (wiederholt)` | Akkordtöne (4) ab MIDI 67 über 2 Oktaven, aufwärts zyklisch | 5, 6, 7, 8 | 45 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 55 |
| HM Hauptmelodie | — | notiert (siehe unten) | 1–8 | 75 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Tupfer, Stich
- **Hauptmelodie:** `G4/8 C5/8 | E5/12 D5/4 | G5/16 | E5/8 C5/8 | Eb5/8 C5/8 | Ab5/16 | F5/8 D5/8 | Bb4/8 D5/8`
- **Gegenstimme:** `r/16 | r/16 | r/16 | r/16 | C4/16 | Eb4/16 | D4/16 | F4/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ○ ● ○ ● ○ ● ○
LB   ● ● ● ● ● ● ● ●
AR   · · · · ● ● ● ●
GS   · · · · ● ● ● ●
HM   ● ● ● ● ● ● ● ●
```

- **Zusammenhang der Rollen:** Vier Takte ein Klang; der Bass wechselt das Register statt der Harmonie. Mit ♭VI kommt Bewegung im Arpeggio und eine Gegenstimme in Ganzen.
- **Dynamik:** mp → mf. · **Pausen:** Arpeggio erst ab Takt 5.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Melodie: Registerwechsel im Bass und Arpeggio-Einsatz ergeben die Weite.
- **Variation:** Ab/C und Bb/C (Pedalfassung). · **Fortsetzung:** Schluss auf C mit JW-H33 (Takte 7–8).
- **Bezug:** JW-H55, JW-B20, JW-R14
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 2 3 2 5 4 5 4; Melodietöne auf Zählzeiten als Akkordton: HM 13/14, GS 4/4; MIDI `JW-S15.mid`, 70 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): HM 13/1/0, GS 4/0/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S16 · Zuspitzung (Unruhe > 0,9)

- **Charakter:** Letzte Sekunden vor der Katastrophe.
- **XYZ-Anker:** 0,30 / 0,95 / 0,98 (DIU) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 152–168 (MIDI-Beispiel ♩ = 160) · **Harmonik:** JW-H48 · **Tonvorrat:** Okt-A/Okt-B im Wechsel
- **Akkorde je Takt:** `C/Db`+`Db/D` | `C/Db`+`Db/D` | `C/Db`+`Db/D` | `C/Db`+`Db/D` | `C/Db` | `Db/D` | `C/Db` | `Db/D`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `X.xxX.xxX.xxX.xx\|X.xxX.xxX.x.X...  (wiederholt)` | Akkordtöne eng ab MIDI 60, 3 Stimmen | 1–8 | 85 |
| KB Kurzer Bass | `X-xX-xX-X-xX-xX-  (wiederholt)` | Bass-Töne `b` ab MIDI 36 | 1–8 | 90 |
| AR Arpeggio | `XxxxXxx.XxxxXx..\|XxxxXxx.XxXxXxXx  (wiederholt)` | Akkordtöne (4) ab MIDI 72 über 2 Oktaven, aufwärts zyklisch | 1–8 | 70 |
| ST Stich | `X.......X.......  (wiederholt)` | fest: Db2 D2 | 1, 2, 3, 4 | 105 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 90 |

- **Nicht beteiligt:** Lange Fläche, Langer Bass, Tupfer, Hauptmelodie
- **Gegenstimme:** `r/16 | r/16 | r/16 | C4/1 Db4/1 Eb4/1 E4/1 F#4/1 G4/1 A4/1 Bb4/1 C5/8 | r/16 | r/16 | r/16 | C#4/1 D4/1 E4/1 F4/1 G4/1 Ab4/1 Bb4/1 B4/1 C#5/8`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
KF   ● ● ● ● ● ● ● ●
KB   ● ● ● ● ● ● ● ●
AR   ● ● ● ● ● ● ● ●
ST   ● ● ● ● · · · ·
GS   · · · ● · · · ●
```

- **Zusammenhang der Rollen:** Zwei oktatonische Vorräte im Halbtaktwechsel, aber alle Schichten teilen dasselbe Akzentgerüst: Stich auf jedem Klangwechsel, Bass in 3+3+2, Fläche auf den Vierteln. Ab Takt 5 wechselt die Harmonie nur noch taktweise; das ist eine ruhigere Stufe innerhalb der Spitze.
- **Dynamik:** ff durchgehend; Stich nur Takte 1–4. · **Pausen:** Gegenstimme nur in Takt 4 und 8 (Läufe als Signal).
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Gegenstimme vollständig; die Läufe sind nur Signal.
- **Variation:** Für Z > 0,9 gedacht; darf so lange stehen bleiben, wie die Stimmung gewählt ist. Rückweg bei sinkendem Z über JW-S13 oder JW-H19. · **Fortsetzung:** JW-S13, JW-T08.
- **Bezug:** JW-H48, JW-R07, JW-R08, JW-R09, JW-M32
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 4 4 4 5 3 3 3 4; Melodietöne auf Zählzeiten als Akkordton: GS 3/6; MIDI `JW-S16.mid`, 478 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 9/0/9
- **Haltetöne über Akkordwechsel:** keine Konflikte

### G.2 Ergänzung für die schwach besetzten Bereiche (JW-S17–S24)

### JW-S17 · Neugierige Werkstatt

- **Charakter:** Hell, leise, unruhig: jemand untersucht neugierig eine fremde Werkstatt.
- **XYZ-Anker:** 0,75 / 0,25 / 0,70 (HRU) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 96–112 (MIDI-Beispiel ♩ = 104) · **Harmonik:** JW-H58 · **Tonvorrat:** Pantriadisch
- **Akkorde je Takt:** `C` | `D/C` | `E/C` | `D/C` | `C` | `Bb/C` | `Ab/C` | `Bb/C`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `....x.....x.x...\|....x...x.....x.  (wiederholt)` | Akkordtöne eng ab MIDI 60, 3 Stimmen | 1–8 | 55 |
| KB Kurzer Bass | `X.......X.......  (wiederholt)` | Bass-Töne `b 5` ab MIDI 36 | 1–8 | 55 |
| TU Tupfer | `x.x...x.x.......\|....x.x...x.x...  (wiederholt)` | oberster Akkordton ab MIDI 84, dann abwärts zyklisch | 1–8 | 45 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 60 |

- **Nicht beteiligt:** Lange Fläche, Langer Bass, Arpeggio, Stich, Hauptmelodie
- **Gegenstimme:** `E5/1 r/1 G5/1 r/1 C6/2 r/6 G5/2 E5/2 | F#5/1 r/1 A5/1 r/1 D6/2 r/6 A5/2 F#5/2 | G#5/1 r/1 B5/1 r/1 E6/2 r/6 B5/2 G#5/2 | A5/2 F#5/2 D5/4 C5/8 | E5/1 r/1 G5/1 r/1 C6/2 r/6 G5/2 E5/2 | D5/1 r/1 F5/1 r/1 Bb5/2 r/6 F5/2 D5/2 | C5/1 r/1 Eb5/1 r/1 Ab5/2 r/6 Eb5/2 C5/2 | D5/2 F5/2 Bb4/4 C5/8`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
KF   ● ● ● ● ● ● ● ●
KB   ● ● ● ● ● ● ● ●
TU   ● ● ● ● ● ● ● ●
GS   ● ● ● ● ● ● ● ●
```

- **Zusammenhang der Rollen:** Oom-pah-Bass auf C (über D/C und E/C ein Dissonanzbass), Nachschläge der Kurzen Fläche an verschobenen Stellen, Tupfer im Staccato-Duett mit der Gegenstimme. Unruhe kommt aus Akzentlage und Planing, nicht aus Tempo.
- **Dynamik:** pp bis p, alles staccato. · **Pausen:** Große Lücken in allen Rollen; die Gegenstimme hat in jedem Takt sechs Sechzehntel Pause.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Gegenstimme tragen Oom-pah, schiefe Nachschläge und Tupfer die Szene allein.
- **Variation:** Planing abwärts beginnen; Nachschläge regelmäßig für weniger Unruhe. · **Fortsetzung:** JW-S25 (32-Takt-Entwicklung) oder JW-S10.
- **Bezug:** JW-H58, JW-R42, JW-R39, JW-B31, JW-P19
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 4 4 4 4 4 4 4 4; Melodietöne auf Zählzeiten als Akkordton: GS 24/24; MIDI `JW-S17.mid`, 155 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 38/0/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S18 · Lydisch-♯2-Rätsel

- **Charakter:** Eine kleine, fremde Kreatur huscht durch den Sand.
- **XYZ-Anker:** 0,70 / 0,30 / 0,65 (HRU) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 76–92 (MIDI-Beispiel ♩ = 84) · **Harmonik:** JW-H59 · **Tonvorrat:** Lydisch-♯2
- **Akkorde je Takt:** `C` | `C` | `Am/C` | `C` | `B/C` | `C` | `Em/C` | `C`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LB Langer Bass | `X---------------\|----------------  (wiederholt)` | fest: C2 | 1–8 | 45 |
| AR Arpeggio | `X.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.  (wiederholt)` | Akkordtöne (4) ab MIDI 67 über 2 Oktaven, auf und ab | 3, 4, 7, 8 | 40 |
| TU Tupfer | `x...............\|........x.......\|................\|....x...........  (wiederholt)` | oberster Akkordton ab MIDI 84, dann abwärts zyklisch | 1–8 | 45 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 55 |

- **Nicht beteiligt:** Lange Fläche, Kurze Fläche, Kurzer Bass, Stich, Hauptmelodie
- **Gegenstimme:** `C5/1 r/1 D#5/1 E5/1 F#5/2 E5/2 r/2 B4/2 C5/4 | r/16 | r/16 | G4/3 A4/1 F#5/3 G5/1 E5/4 r/4 | r/8 D#5/2 F#5/2 B5/4 | r/16 | E5/1 r/1 G5/1 B5/1 r/12 | C5/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LB   ● ○ ● ○ ● ○ ● ○
AR   · · ● ● · · ● ●
TU   ● ● · ● ● ● · ●
GS   ● · · ● ● · ● ●
```

- **Zusammenhang der Rollen:** Pedal C trägt; Tupfer als isolierte Einwürfe, das Arpeggio nur in den Takten 3–4 und 7–8. Die Gegenstimme führt die systemtypischen Töne D♯ und F♯ als Erkennungszeichen.
- **Dynamik:** pp; Gegenstimme p. · **Pausen:** Takte 2–3 und 6 ohne Gegenstimme; Takt 3 ohne Tupfer.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Gegenstimme: Pedal, Einwürfe und die scharfe B/C-Reibung tragen.
- **Variation:** B/C nur halbtaktig; Gegenstimme in Englischhorn-Lage (eine Oktave tiefer). · **Fortsetzung:** JW-S17 oder JW-H58.
- **Bezug:** JW-H59, JW-R40, JW-M37, JW-M38
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 1 2 3 3 1 3 3; Melodietöne auf Zählzeiten als Akkordton: GS 8/10; MIDI `JW-S18.mid`, 61 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 14/5/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S19 · Lydische Schleife mit wechselnden Akzenten

- **Charakter:** Siegesfreudige Verfolgung im Sonnenlicht.
- **XYZ-Anker:** 0,90 / 0,80 / 0,65 (HIU) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 126–144 (MIDI-Beispiel ♩ = 138) · **Harmonik:** JW-H62 · **Tonvorrat:** Lydisch
- **Bewusst systemfremd:** Rolle(n) KB (siehe Zusammenhang).
- **Akkorde je Takt:** `C`+`D` | `C`+`D` | `C`+`D` | `C`+`D` | `C`+`D` | `C`+`D` | `Em` | `D`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `X.x.x.X.x.x.X.x.\|X.x.X.x.x.X.x.x.  (wiederholt)` | Akkordtöne eng ab MIDI 60, 3 Stimmen | 1–8 | 80 |
| KB Kurzer Bass | `X.x.X.x.X.x.X.x.  (wiederholt)` | Bass-Töne `R R n n` ab MIDI 36 | 1–8 | 75 |
| AR Arpeggio | `X.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.  (wiederholt)` | Akkordtöne (4) ab MIDI 72 über 2 Oktaven, aufwärts zyklisch | 1–8 | 50 |
| ST Stich | `X.......X.......\|X...............  (wiederholt)` | fest: G2 D3 | 1–8 | 95 |
| HM Hauptmelodie | — | notiert (siehe unten) | 1–8 | 95 |

- **Nicht beteiligt:** Lange Fläche, Langer Bass, Tupfer, Gegenstimme
- **Hauptmelodie:** `G5/4 E5/4 F#5/4 A5/4 | C6/4 G5/4 A5/4 D6/4 | E6/8 D6/4 F#5/4 | G5/2 C6/2 E6/4 D6/8 | C6/4 E6/4 D6/8 | G6/8 F#6/4 E6/4 | B5/4 G5/4 E5/8 | F#5/4 A5/4 D6/8`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
KF   ● ● ● ● ● ● ● ●
KB   ● ● ● ● ● ● ● ●
AR   ● ● ● ● ● ● ● ●
ST   ● ● ● ● ● ● ● ●
HM   ● ● ● ● ● ● ● ●
```

- **Zusammenhang der Rollen:** Die Harmonie kreist (C↔D), die Akzente der Kurzen Fläche wandern (3+3+2 / 2+3+3), der Bass setzt vor jedem Klangwechsel einen Halbton-Leitton (bewusst systemfremd). Arpeggio und bewegter Bass spielen gleichzeitig; das Arpeggio bleibt leise und hoch.
- **Dynamik:** f; Hauptmelodie ff. · **Pausen:** Stich nur dreimal in zwei Takten.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Melodie: kreisende Harmonie, wandernde Akzente und Bass-Leittöne bleiben hörbar unruhig und hell.
- **Variation:** Ganztaktige Schleife für weniger Unruhe; Bass ohne Leittöne (stabiler). · **Fortsetzung:** JW-S20 oder JW-S14.
- **Bezug:** JW-H62, JW-R37, JW-B32, JW-P20
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 5 5 5 5 5 5 5 5; Melodietöne auf Zählzeiten als Akkordton: HM 25/26; MIDI `JW-S19.mid`, 371 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): HM 26/1/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S20 · Planing-Jagd mit Großterzrückung

- **Charakter:** Gleiter jagen durch eine Schlucht; dann öffnet sich der Himmel.
- **XYZ-Anker:** 0,85 / 0,85 / 0,60 (HIm) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 120–140 (MIDI-Beispiel ♩ = 132) · **Harmonik:** JW-H64 · **Tonvorrat:** Pantriadisch
- **Akkorde je Takt:** `C`+`Bb/C` | `Ab/C`+`Bb/C` | `C`+`D/C` | `Eb/C`+`F/C` | `E`+`D/E` | `C/E`+`D/E` | `E`+`F#/E` | `G/E`+`A/E`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `X.....x.X.....x.  (wiederholt)` | Akkordtöne eng ab MIDI 60, 3 Stimmen | 1–8 | 85 |
| LB Langer Bass | `X-------X-------  (wiederholt)` | Bass-Töne `b` ab MIDI 36 | 1–8 | 80 |
| KB Kurzer Bass | `X..x..x.X..x..x.  (wiederholt)` | Bass-Töne `b` ab MIDI 48 | 1–8 | 70 |
| AR Arpeggio | `XxxxXxx.XxxxXx..\|XxxxXxx.XxXxXxXx  (wiederholt)` | Akkordtöne (4) ab MIDI 72 über 2 Oktaven, aufwärts zyklisch | 1–8 | 60 |
| ST Stich | `X.......X.......\|X...............  (wiederholt)` | fest: C2 E2 | 1–8 | 95 |

- **Nicht beteiligt:** Lange Fläche, Tupfer, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
KF   ● ● ● ● ● ● ● ●
LB   ● ● ● ● ● ● ● ●
KB   ● ● ● ● ● ● ● ●
AR   ● ● ● ● ● ● ● ●
ST   ● ● ● ● ● ● ● ●
```

- **Zusammenhang der Rollen:** Alle Schichten teilen das Akzentgerüst (JW-R48). Die Kurze Fläche folgt den parallelen Klängen, Pedal C, ab Takt 5 Pedal E. Der Glanzeffekt in Takt 5 kommt von der Rückung, nicht von zusätzlichen Rollen.
- **Dynamik:** f, ab Takt 5 ff. · **Pausen:** keine längeren Pausen; Stich spart in Takt 2.
- **Ohne Hauptmelodie/Gegenstimme:** Studie ist ohne Melodie gebaut.
- **Variation:** Rückung abwärts; Arpeggio nur ab Takt 5. · **Fortsetzung:** JW-S14 (Triumph).
- **Bezug:** JW-H64, JW-R48, JW-R09
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 5 5 5 5 5 5 5 5; keine Melodierolle; MIDI `JW-S20.mid`, 288 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S21 · Dies-irae-Choral

- **Charakter:** Ein Tempel, Fackeln, ein Ritual, das nicht aufzuhalten ist.
- **XYZ-Anker:** 0,15 / 0,80 / 0,25 (DIS) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 58–72 (MIDI-Beispiel ♩ = 66) · **Harmonik:** JW-H69 · **Tonvorrat:** Moll harm.
- **Akkorde je Takt:** `Cm` | `G/B` | `Cm` | `Fm/Ab` | `G/B` | `Cm/G` | `Fm/Ab` | `Ab`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 48, 4 Stimmen | 1–8 | 70 |
| KF Kurze Fläche | `X---x---x-x-x---  (wiederholt)` | Akkordtöne eng ab MIDI 55, 3 Stimmen | 5, 6, 7, 8 | 75 |
| LB Langer Bass | `X---------------  (wiederholt)` | Bass-Töne `P(C2) P(B1) P(C2) P(Ab1) P(B1) P(G1) P(Ab1) P(Ab1)` ab MIDI 36 | 1–8 | 85 |
| ST Stich | `X...............\|................  (wiederholt)` | fest: C2 G2 | 1, 5 | 100 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 65 |

- **Nicht beteiligt:** Kurzer Bass, Arpeggio, Tupfer, Hauptmelodie
- **Gegenstimme:** `G4/16 | G4/8 D4/8 | Eb4/16 | C4/8 F4/8 | D4/16 | Eb4/8 G4/8 | Ab4/8 F4/8 | Eb4/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ● ● ● ● ● ● ●
KF   · · · · ● ● ● ●
LB   ● ● ● ● ● ● ● ●
ST   ● · · · ● · · ·
GS   ● ● ● ● ● ● ● ●
```

- **Zusammenhang der Rollen:** Der Bass singt die Dies-irae-Kontur in Ganzen; die Fläche liegt schwer darüber. Ab Takt 5 kommt das Lang-lang-kurz-kurz-lang-Ostinato hinzu – Kraft ohne Hektik. Die Gegenstimme ist ein Choral in Akkordtönen.
- **Dynamik:** f, Stich ff (Takt 1 und 5). · **Pausen:** keine schnellen Werte; die Kurze Fläche schweigt in den ersten vier Takten.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Gegenstimme: Bass-Cantus und Choralfläche tragen allein.
- **Variation:** Gegenstimme aus (reiner Choral); Ostinato in der Kurzen Fläche schon ab Takt 1. · **Fortsetzung:** JW-S26 (16-Takt-Fassung).
- **Bezug:** JW-H69, JW-B35, JW-R43, JW-P21
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 4 3 3 3 5 4 4 4; Melodietöne auf Zählzeiten als Akkordton: GS 12/12; MIDI `JW-S21.mid`, 88 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 12/0/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S22 · Tritonus-Oszillation in Triolen

- **Charakter:** Die Lade wird geöffnet; etwas Uraltes erwacht.
- **XYZ-Anker:** 0,15 / 0,75 / 0,35 (DIS) · **Länge:** 8 Takte · **Taktart:** 4/4T · **Tempo:** ♩ = 66–80 (MIDI-Beispiel ♩ = 72) · **Harmonik:** JW-H67 · **Tonvorrat:** Pantriadisch
- **Akkorde je Takt:** `Cm` | `F#m` | `Cm` | `F#m` | `Bbm` | `Abm` | `Gm` | `Cm`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X-----------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 48, 3 Stimmen | 1–8 | 65 |
| KF Kurze Fläche | `X-----x-----  (wiederholt)` | Akkordtöne eng ab MIDI 55, 3 Stimmen | 5, 6, 7, 8 | 70 |
| LB Langer Bass | `X-----------  (wiederholt)` | Bass-Töne `R` ab MIDI 36 | 1–8 | 75 |
| AR Arpeggio | `Xxxxxxxxxxxx  (wiederholt)` | Akkordtöne (4) ab MIDI 60 über 2 Oktaven, auf und ab | 1–8 | 50 |
| ST Stich | `X...........\|............  (wiederholt)` | fest: C2 G2 | 1, 5 | 95 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 75 |

- **Nicht beteiligt:** Kurzer Bass, Tupfer, Hauptmelodie
- **Gegenstimme:** `G4/6 C5/6 | C#5/9 r/3 | Eb5/6 G5/6 | F#5/6 A4/6 | Bb4/3 Db5/3 F5/6 | Eb5/12 | D5/6 Bb4/6 | C5/12`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ● ● ● ● ● ● ●
KF   · · · · ● ● ● ●
LB   ● ● ● ● ● ● ● ●
AR   ● ● ● ● ● ● ● ●
ST   ● · · · ● · · ·
GS   ● ● ● ● ● ● ● ●
```

- **Zusammenhang der Rollen:** Mollklänge im Tritonusabstand, darunter Grundtöne in Ganzen; Triolenarpeggien rollen leise in der Mitte. Ab Takt 5 stufenweiser Abstieg und Halbe in der Kurzen Fläche.
- **Dynamik:** mf → f. · **Pausen:** Stich nur zweimal.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Gegenstimme: Tritonusoszillation und Triolenarpeggio tragen.
- **Variation:** Takte 5–7 als Kleinterzkette (C–E♭–F♯). · **Fortsetzung:** JW-H76 (Kleinterzkette zur überhöhten Kadenz).
- **Bezug:** JW-H67, JW-R45, JW-R46, JW-P24
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 5 4 4 4 6 5 5 5; Melodietöne auf Zählzeiten als Akkordton: GS 8/8; MIDI `JW-S22.mid`, 170 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 14/0/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S23 · Leise Oktatonik

- **Charakter:** Jemand steht im Dunkeln hinter der Tür und atmet nicht.
- **XYZ-Anker:** 0,20 / 0,20 / 0,60 (DRm) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 54–66 (MIDI-Beispiel ♩ = 60) · **Harmonik:** JW-H74 · **Tonvorrat:** Okt-A
- **Akkorde je Takt:** `Cm` | `Cm` | `Ebm|Cm` | `Ebm|Cm` | `Cm` | `Am|F#m` | `Ebm|Cm` | `Cm`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 72, 3 Stimmen | 1–8 | 35 |
| LB Langer Bass | `X---------------\|----------------  (wiederholt)` | Bass-Töne `P(C2) P(Eb2) P(F#2) P(A1)` ab MIDI 36 | 1–8 | 45 |
| TU Tupfer | `..........x.....\|...x............  (wiederholt)` | oberster Akkordton ab MIDI 43, dann abwärts zyklisch | 1–8 | 40 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 45 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Arpeggio, Stich, Hauptmelodie
- **Gegenstimme:** `r/16 | C4/2 Eb4/2 Db4/2 E4/2 Eb4/4 r/4 | r/16 | r/16 | r/16 | C4/2 Eb4/2 Db4/2 E4/2 Eb4/4 r/4 | r/16 | r/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ● ● ● ● ● ● ●
LB   ● ○ ● ○ ● ○ ● ○
TU   ● ● ● ● ● ● ● ●
GS   · ● · · · ● · ·
```

- **Zusammenhang der Rollen:** Alle Rollen teilen den Vorrat Okt-A: hohe Fläche, tiefe Einzeltöne, Pedalwechsel in kleinen Terzen (unter Cm in Takt 5–8 als Dissonanzbass). Die Gegenstimme kreist zweimal leise um E♭; dazwischen Stille.
- **Dynamik:** ppp bis pp. · **Pausen:** Takte 3–5 und 7–8 ohne Gegenstimme; keine Rhythmusrollen.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Gegenstimme bleibt eine vollständige, sehr leise Spannungsfläche.
- **Variation:** Polychorde als Arpeggio statt als Klang. · **Fortsetzung:** JW-S28 (32-Takt-Lauern) oder JW-S04.
- **Bezug:** JW-H74, JW-B40, JW-R47, JW-M42
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 3 3 2 3 3 3 2; Melodietöne auf Zählzeiten als Akkordton: GS 4/6; MIDI `JW-S23.mid`, 58 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 6/4/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S24 · Rätselhafte Arpeggien

- **Charakter:** Ein Labor, in dem niemand mehr ist.
- **XYZ-Anker:** 0,30 / 0,20 / 0,65 (DRU) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 63–76 (MIDI-Beispiel ♩ = 69) · **Harmonik:** JW-H72 · **Tonvorrat:** Pantriadisch
- **Akkorde je Takt:** `Cm(b6)` | `Dm(addb9)` | `EbmM7` | `Dm(b6)` | `Cm(addb9)` | `BmM7` | `Cm(b6)` | `Cm`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LB Langer Bass | `X---------------\|----------------  (wiederholt)` | fest: C2 | 1–8 | 40 |
| AR Arpeggio | `X.x.x.x.........  (wiederholt)` | Akkordtöne (4) ab MIDI 60 über 2 Oktaven, aufwärts zyklisch | 1–8 | 45 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 55 |

- **Nicht beteiligt:** Lange Fläche, Kurze Fläche, Kurzer Bass, Tupfer, Stich, Hauptmelodie
- **Gegenstimme:** `C4/2 Eb4/2 Ab4/4 r/8 | D4/2 F4/2 Eb4/4 r/8 | Eb4/2 Gb4/2 D5/4 r/8 | D4/2 F4/2 Bb4/4 r/8 | C4/2 Eb4/2 Db4/4 r/8 | B3/2 D4/2 A#4/4 r/8 | C4/2 Eb4/2 Ab4/4 r/8 | C4/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LB   ● ○ ● ○ ● ○ ● ○
AR   ● ● ● ● ● ● ● ●
GS   ● ● ● ● ● ● ● ●
```

- **Zusammenhang der Rollen:** Das Arpeggio spielt jeweils einen halben Takt und schweigt dann; jeder Klang enthält genau einen Zusatzton. Die Gegenstimme beantwortet die Stille.
- **Dynamik:** pp. · **Pausen:** jede zweite Takthälfte ohne Arpeggio; Gegenstimme mit Achtel- bzw. Halbe-Pausen.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Gegenstimme: Arpeggio und Stille wechseln sich ab.
- **Variation:** Arpeggio nur aufwärts versetzen (C–D–E♭–F). · **Fortsetzung:** JW-S03 oder JW-S23.
- **Bezug:** JW-H72, JW-P22, JW-M47
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 2 3 2 3 2 3 2; Melodietöne auf Zählzeiten als Akkordton: GS 15/15; MIDI `JW-S24.mid`, 58 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 22/0/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### G.3 Längere Entwicklungen und Achsen-Demonstrationen (JW-S25–S30)

JW-S25 und JW-S28 (32 Takte) sowie JW-S26 und JW-S27 (16 Takte) halten XYZ konstant und variieren über Schichtwechsel, Register und Motivübergabe, ohne die Harmonie auszutauschen. JW-S29 und JW-S30 trennen die Achsen: dieselbe Musik einmal nur in der Intensität, einmal nur in der Unruhe verändert.

### JW-S25 · 32 Takte gleiche Stimmung: Planing-Scherzo

- **Charakter:** Ein weiser alter Wächter zeigt einem Kind seinen Garten (eine Stimmung, 32 Takte).
- **XYZ-Anker:** 0,75 / 0,35 / 0,55 (HRm) · **Länge:** 32 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 88–104 (MIDI-Beispiel ♩ = 96) · **Harmonik:** JW-H60 (4 Durchgänge) · **Tonvorrat:** Pantriadisch
- **Akkorde je Takt:** `Cmaj7` | `Fmaj7` | `Cmaj7` | `Fmaj7` | `Eb` | `D` | `Db` | `C` (×4)

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `....x.....x.x...\|....x...x.....x.  (wiederholt)` | Akkordtöne eng ab MIDI 60, 3 Stimmen | 17, 18, 19, 20, 21, 22, 23, 24 | 55 |
| LB Langer Bass | `X---------------\|----------------  (wiederholt)` | fest: C2 | 29, 30, 31, 32 | 45 |
| KB Kurzer Bass | `X...x...X...x...  (wiederholt)` | Bass-Töne `R 5` ab MIDI 36 | 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28 | 55 |
| AR Arpeggio | `X.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.  (wiederholt)` | Akkordtöne (4) ab MIDI 67 über 2 Oktaven, aufwärts zyklisch | 9, 10, 11, 12, 13, 14, 15, 16 | 40 |
| TU Tupfer | `x.x...x.x.......\|....x.x...x.x...  (wiederholt)` | oberster Akkordton ab MIDI 84, dann abwärts zyklisch | 1, 2, 3, 4, 5, 6, 7, 8, 25, 26, 27, 28, 29, 30, 31, 32 | 45 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–32 | 60 |
| HM Hauptmelodie | — | notiert (siehe unten) | 1–32 | 70 |

- **Nicht beteiligt:** Lange Fläche, Stich
- **Hauptmelodie:** `r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | E6/3 r/1 B5/2 r/2 G5/4 r/4 | A5/3 r/1 E5/2 r/2 C5/4 r/4 | E4/3 r/1 B3/2 r/2 G3/4 r/4 | A3/3 r/1 E3/2 r/2 C3/4 r/4 | G5/4 Bb5/4 Eb6/8 | F#5/4 A5/4 D6/8 | F5/4 Ab5/4 Db6/8 | E5/4 G5/4 C6/8 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16`
- **Gegenstimme:** `r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | E6/3 r/1 B5/2 r/2 G5/4 r/4 | A5/3 r/1 E5/2 r/2 C5/4 r/4 | E4/3 r/1 B3/2 r/2 G3/4 r/4 | A3/3 r/1 E3/2 r/2 C3/4 r/4 | G5/4 Bb5/4 Eb6/8 | F#5/4 A5/4 D6/8 | F5/4 Ab5/4 Db6/8 | E5/4 G5/4 C6/8 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | E6/3 r/1 B5/2 r/2 G5/4 r/4 | A5/3 r/1 E5/2 r/2 C5/4 r/4 | r/16 | r/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32
KF   · · · · · · · · · · · · · · · · ● ● ● ● ● ● ● ● · · · · · · · ·
LB   · · · · · · · · · · · · · · · · · · · · · · · · · · · · ● ○ ● ○
KB   ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● · · · ·
AR   · · · · · · · · ● ● ● ● ● ● ● ● · · · · · · · · · · · · · · · ·
TU   ● ● ● ● ● ● ● ● · · · · · · · · · · · · · · · · ● ● ● ● ● ● ● ●
GS   · · · · · · · · ● ● ● ● ● ● ● ● · · · · · · · · · · · · ● ● · ·
HM   · · · · · · · · · · · · · · · · ● ● ● ● ● ● ● ● · · · · · · · ·
```

- **Zusammenhang der Rollen:** Harmonie (JW-H60) und Grundrhythmus bleiben 32 Takte gleich. Es wechseln nur Schichten: A Tupfer + Oom-pah; B Arpeggio + Gegenstimme mit der Frage-Antwort-Phrase; C dieselbe Phrase in der Hauptmelodie, Nachschläge statt Arpeggio (Übergabe Gegenstimme → Hauptmelodie); D Ausdünnung, Fragment der Phrase, Pedal.
- **Dynamik:** p gleichbleibend. · **Pausen:** Abschnitt D lässt den Bass ab Takt 29 fallen (Pedal).
- **Ohne Hauptmelodie/Gegenstimme:** Abschnitt A und D sind ohne Melodie; ohne Melodien bleibt der Schichtwechsel der Entwicklungsträger.
- **Variation:** Abschnittsreihenfolge B–A–C–D; Phrase in C eine Oktave tiefer. · **Fortsetzung:** Neuer Durchgang mit anderer Harmonie aus derselben Region (JW-H58).
- **Bezug:** JW-H60, JW-P23, JW-R39, JW-R42
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 2 2 2 2 3 2 2 1; Melodietöne auf Zählzeiten als Akkordton: HM 24/24, GS 26/30; MIDI `JW-S25.mid`, 368 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): HM 24/0/0, GS 26/4/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S26 · 16 Takte dunkle Größe

- **Charakter:** Die Armee des Gegners zieht vorbei; kein Laut außer dem Marsch.
- **XYZ-Anker:** 0,15 / 0,80 / 0,25 (DIS) · **Länge:** 16 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 58–72 (MIDI-Beispiel ♩ = 66) · **Harmonik:** JW-H69 (2 Durchgänge) · **Tonvorrat:** Moll harm.
- **Akkorde je Takt:** `Cm` | `G/B` | `Cm` | `Fm/Ab` | `G/B` | `Cm/G` | `Fm/Ab` | `Ab` (×2)

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 48, 4 Stimmen | 1–16 | 65 |
| KF Kurze Fläche | `X---x---x-x-x---  (wiederholt)` | Akkordtöne eng ab MIDI 55, 3 Stimmen | 9, 10, 11, 12, 13, 14, 15, 16 | 75 |
| LB Langer Bass | `X---------------  (wiederholt)` | Bass-Töne `P(C2) P(B1) P(C2) P(Ab1) P(B1) P(G1) P(Ab1) P(Ab1)` ab MIDI 36 | 1–16 | 80 |
| ST Stich | `X...............\|................  (wiederholt)` | fest: C2 G2 | 9, 13 | 100 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–16 | 65 |

- **Nicht beteiligt:** Kurzer Bass, Arpeggio, Tupfer, Hauptmelodie
- **Gegenstimme:** `r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | G4/16 | G4/8 D4/8 | Eb4/16 | C4/8 F4/8 | D4/16 | Eb4/8 G4/8 | Ab4/8 F4/8 | Eb4/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
LF   ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ●
KF   · · · · · · · · ● ● ● ● ● ● ● ●
LB   ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ●
ST   · · · · · · · · ● · · · ● · · ·
GS   · · · · · · · · ● ● ● ● ● ● ● ●
```

- **Zusammenhang der Rollen:** Zweimal dieselbe Akkordfolge: zuerst nur Bass-Cantus und Fläche, dann Ostinato, Stich und Choralstimme. Variation durch Hinzunahme, nicht durch neues Material.
- **Dynamik:** mf, zweite Hälfte f. · **Pausen:** Takte 1–8 ohne Rhythmusrollen.
- **Ohne Hauptmelodie/Gegenstimme:** Erste Hälfte ist ohne Melodie; die Entwicklung funktioniert auch ohne Choralstimme.
- **Variation:** Zweite Hälfte als Dies-irae-Umkehrung (JW-M45) in der Gegenstimme. · **Fortsetzung:** JW-T02 (Angst → Action) oder JW-S22.
- **Bezug:** JW-H69, JW-B35, JW-R43, JW-P21
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 2 2 2 2 2 2 2 5 4 4 4 5 4 4 4; Melodietöne auf Zählzeiten als Akkordton: GS 12/12; MIDI `JW-S26.mid`, 165 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 12/0/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S27 · 16 Takte heller Abenteuerbogen

- **Charakter:** Ein Schiff weicht Asteroiden aus – erst konzentriert, dann übermütig.
- **XYZ-Anker:** 0,70 / 0,70 / 0,65 (HIU) · **Länge:** 16 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 116–132 (MIDI-Beispiel ♩ = 126) · **Harmonik:** JW-H66 (2 Durchgänge) · **Tonvorrat:** Hex-C
- **Akkorde je Takt:** `C`+`E/B` | `C` | `Ab`+`E/G#` | `Ab` | `E`+`Ab/Eb` | `E` | `C`+`E/B` | `C` (×2)

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `X.x.x.X.x.x.X.x.\|X.x.X.x.x.X.x.x.  (wiederholt)` | Akkordtöne eng ab MIDI 60, 3 Stimmen | 1–16 | 70 |
| KB Kurzer Bass | `X.......X.......\|X.....X...X.....  (wiederholt)` | Bass-Töne `b` ab MIDI 36 | 1–16 | 75 |
| AR Arpeggio | `XxxxXxx.XxxxXx..\|XxxxXxx.XxXxXxXx  (wiederholt)` | Akkordtöne (4) ab MIDI 72 über 2 Oktaven, aufwärts zyklisch | 9, 10, 11, 12, 13, 14, 15, 16 | 60 |
| ST Stich | `X.......X.......\|X...............  (wiederholt)` | fest: C2 G2 | 9, 10, 11, 12, 13, 14, 15, 16 | 95 |
| HM Hauptmelodie | — | notiert (siehe unten) | 1–16 | 90 |

- **Nicht beteiligt:** Lange Fläche, Langer Bass, Tupfer, Gegenstimme
- **Hauptmelodie:** `r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | G5/4 E5/4 G#5/4 B5/4 | C6/8 G5/8 | Ab5/4 Eb5/4 E5/4 B5/4 | C6/8 Ab5/8 | B5/4 G#5/4 C6/4 Eb6/4 | E6/12 B5/4 | G5/4 C6/4 B5/4 G#5/4 | C6/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
KF   ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ●
KB   ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ●
AR   · · · · · · · · ● ● ● ● ● ● ● ●
ST   · · · · · · · · ● ● ● ● ● ● ● ●
HM   · · · · · · · · ● ● ● ● ● ● ● ●
```

- **Zusammenhang der Rollen:** Harmonie und Bass bleiben 16 Takte gleich. In der zweiten Hälfte kommen Sechzehntel-Arpeggio, Stich und die Hauptmelodie hinzu; die Kurze Fläche behält ihr Akzentmuster.
- **Dynamik:** mf → f. · **Pausen:** Hauptmelodie erst ab Takt 9.
- **Ohne Hauptmelodie/Gegenstimme:** Erste Hälfte ist ohne Melodie; Akzentmuster und Halbtonrutschen tragen.
- **Variation:** Arpeggio in der ersten Hälfte statt Kurzer Fläche. · **Fortsetzung:** JW-S20.
- **Bezug:** JW-H66, JW-R37, JW-R38, JW-R09
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 2 2 2 2 2 2 2 5 5 5 5 5 5 5 5; Melodietöne auf Zählzeiten als Akkordton: HM 23/23; MIDI `JW-S27.mid`, 551 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): HM 23/0/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S28 · 32 Takte Lauern: Bewegung und Stille

- **Charakter:** Eine Wohnung bei Nacht; jemand ist da, der nicht da sein dürfte (eine Stimmung, 32 Takte).
- **XYZ-Anker:** 0,15 / 0,25 / 0,65 (DRU) · **Länge:** 32 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 56–69 (MIDI-Beispiel ♩ = 63) · **Harmonik:** JW-H71 (4 Durchgänge) · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `Cm` | `C#m|Cm` | `Cm` | `Cm` | `C#m|Cm` | `Cm` | `Bm|Cm` | `Cm` (×4)

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 72, 3 Stimmen | 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 25, 26, 27, 28, 29, 30, 31, 32 | 35 |
| KB Kurzer Bass | `X-xX-xX-X-xX-xX-  (wiederholt)` | Bass-Töne `P(C2) P(C2) P(Db2) P(Db2) P(Eb2) P(C2) P(C2) P(Gb1) P(Gb1) P(A1)` ab MIDI 36 | 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28 | 45 |
| TU Tupfer | `..........x.....\|...x............  (wiederholt)` | oberster Akkordton ab MIDI 43, dann abwärts zyklisch | 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28 | 40 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–32 | 45 |

- **Nicht beteiligt:** Kurze Fläche, Langer Bass, Arpeggio, Stich, Hauptmelodie
- **Gegenstimme:** `r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | G5/4 G#5/4 G5/4 E5/4 | Eb5/16 | r/16 | r/16 | G5/4 G#5/4 G5/4 E5/4 | Eb5/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | G5/4 G#5/4 G5/4 E5/4 | Eb5/16 | r/16 | r/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32
LF   ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● · · · · · · · · ● ● ● ● ● ● ● ●
KB   · · · · · · · · · · · · · · · · ● ● ● ● ● ● ● ● ● ● ● ● · · · ·
TU   ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● · · · ·
GS   · · · · · · · · ● ● · · ● ● · · · · · · · · · · · · · · ● ● · ·
```

- **Zusammenhang der Rollen:** Die Halbton-Mollpaare bleiben 32 Takte. A: hohe Fläche + tiefe Einzeltöne. B: das Halbton-Motiv in hoher Lage. C: die Fläche verstummt, ein leises tiefes Oktatonik-Ostinato beginnt (Bewegung). D: Ostinato bricht nach Takt 28 ab, Fläche kehrt zurück, das Motiv ein letztes Mal.
- **Dynamik:** ppp bis pp, Ostinato pp. · **Pausen:** Takte 17–24 ohne Fläche; Takte 29–32 ohne Tupfer und Bass.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Gegenstimme bleibt der Wechsel Fläche – Ostinato – Stille als Entwicklung.
- **Variation:** Ostinato schon in B; Motiv nur einmal. · **Fortsetzung:** JW-T01 (Lauern → Angst).
- **Bezug:** JW-H71, JW-B33, JW-R47, JW-M48
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 2 2 2 2 2 2 2 3 3 2 2 3 3 2 2 2 2 2 2 2 2 2 2 3 3 3 3 2 2 1 1; Melodietöne auf Zählzeiten als Akkordton: GS 13/15; MIDI `JW-S28.mid`, 262 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 13/2/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S29 · Intensität ohne Unruhe (16 Takte)

- **Charakter:** Dieselbe Bedrohung, erst leise, dann mit voller Macht – ohne dass sie hektischer wird.
- **XYZ-Anker:** 0,15 / 0,25 / 0,55 (DRm) → 0,15 / 0,80 / 0,55 (DIm), Fahrt in der zweiten Hälfte · **Länge:** 16 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 70–84 (MIDI-Beispiel ♩ = 76) · **Harmonik:** JW-H12 (2 Durchgänge) · **Tonvorrat:** Okt-A
- **Akkorde je Takt:** `Cm` | `Ebm` | `Cm` | `F#m` | `Cm` | `Am` | `Cm` | `Cm` (×2)

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 55, 3 Stimmen | 1–16 | 45 |
| KF Kurze Fläche | `X-------X-------  (wiederholt)` | Akkordtöne eng ab MIDI 48, 4 Stimmen | 9, 10, 11, 12, 13, 14, 15, 16 | 75 |
| LB Langer Bass | `X---------------\|----------------  (wiederholt)` | fest: C2 | 1–16 | 55 |
| ST Stich | `X...............  (wiederholt)` | fest: C2 G2 | 9, 10, 11, 12, 13, 14, 15, 16 | 90 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–16 | 60 |
| HM Hauptmelodie | — | notiert (siehe unten) | 1–16 | 75 |

- **Nicht beteiligt:** Kurzer Bass, Arpeggio, Tupfer
- **Hauptmelodie:** `r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | C5/2 C5/2 C5/2 Eb5/10 | F#5/4 Eb5/12 | C5/2 C5/2 C5/2 Eb5/10 | A5/4 F#5/12 | C5/2 C5/2 C5/2 Eb5/10 | E5/4 C5/12 | G5/4 Eb5/12 | C5/16`
- **Gegenstimme:** `C4/2 C4/2 C4/2 Eb4/10 | Gb4/4 Eb4/12 | C4/2 C4/2 C4/2 Eb4/10 | A4/4 F#4/12 | C4/2 C4/2 C4/2 Eb4/10 | E4/4 C4/12 | G4/4 Eb4/12 | C4/16 | C4/2 C4/2 C4/2 Eb4/10 | Gb4/4 Eb4/12 | C4/2 C4/2 C4/2 Eb4/10 | A4/4 F#4/12 | C4/2 C4/2 C4/2 Eb4/10 | E4/4 C4/12 | G4/4 Eb4/12 | C4/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
LF   ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ●
KF   · · · · · · · · ● ● ● ● ● ● ● ●
LB   ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○
ST   · · · · · · · · ● ● ● ● ● ● ● ●
GS   ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ●
HM   · · · · · · · · ● ● ● ● ● ● ● ●
```

- **Zusammenhang der Rollen:** Takte 1–8 und 9–16 haben identische Harmonie, harmonischen Rhythmus, Motiv und Akzentordnung. Für Y steigen nur Lage (Motiv in der Hauptmelodie eine Oktave höher, Gegenstimme verdoppelt), Besetzung (Choralschläge in Halben, Stich auf jeder Eins) und Dynamik. Keine neuen Synkopen, keine schnelleren Werte: Z bleibt gleich.
- **Dynamik:** pp (1–8) → f (9–16). · **Pausen:** Erste Hälfte nur drei Rollen.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Melodien: Fläche, Pedal, dann Choralschläge und Stich – die Steigerung bleibt hörbar.
- **Variation:** Zweite Hälfte ohne Hauptmelodie: Intensität allein über Besetzung. · **Fortsetzung:** JW-S30 (Gegenstück für Z).
- **Bezug:** JW-H12, JW-M05 (Rhythmusidentität), JW-R46
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 2 3 2 3 2 3 2 6 5 6 5 6 5 6 5; Melodietöne auf Zählzeiten als Akkordton: HM 15/15, GS 30/30; MIDI `JW-S29.mid`, 183 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): HM 21/0/0, GS 42/0/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-S30 · Unruhe ohne Intensität (16 Takte)

- **Charakter:** Eine Gruppe bricht auf; dieselbe Musik, aber plötzlich liegt Nervosität in der Luft.
- **XYZ-Anker:** 0,75 / 0,50 / 0,25 (HmS) → 0,75 / 0,50 / 0,80 (HmU), Fahrt in der zweiten Hälfte · **Länge:** 16 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 104–120 (MIDI-Beispiel ♩ = 112) · **Harmonik:** JW-H01 (2 Durchgänge) · **Tonvorrat:** Mixolydisch
- **Bewusst systemfremd:** Rolle(n) KB (siehe Zusammenhang).
- **Akkorde je Takt:** `C` | `C` | `Bb` | `F` | `C` | `C` | `Gsus4` | `C` (×2)

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `X.x.X.x.X.x.X.x.\|X.x.X.x.X.x.X.x.\|X.x.X.x.X.x.X.x.\|X.x.X.x.X.x.X.x.\|X.x.X.x.X.x.X.x.\|X.x.X.x.X.x.X.x.\|X.x.X.x.X.x.X.x.\|X.x.X.x.X.x.X.x.\|X.x.x.X.x.x.X.x.\|X.x.X.x.x.X.x.x.\|X.x.x.X.x.x.X.x.\|X.x.X.x.x.X.x.x.\|X.x.x.X.x.x.X.x.\|X.x.X.x.x.X.x.x.\|X.x.x.X.x.x.X.x.\|X.x.X.x.x.X.x.x.` | Akkordtöne eng ab MIDI 60, 3 Stimmen | 1–16 | 65 |
| KB Kurzer Bass | `X.x.X.x.X.x.X.x.  (wiederholt)` | Bass-Töne `Takt 1–8: R · Takt 9–16: +1 +1 n n` ab MIDI 36 | 1–16 | 65 |
| AR Arpeggio | `X.x.x.x.x.x.x.x.\|X.x.x.x.x.x.x.x.\|X.x.x.x.x.x.x.x.\|X.x.x.x.x.x.x.x.\|X.x.x.x.x.x.x.x.\|X.x.x.x.x.x.x.x.\|X.x.x.x.x.x.x.x.\|X.x.x.x.x.x.x.x.\|X..x..x..x..x..x\|..x..x..x..x..x.\|X..x..x..x..x..x\|..x..x..x..x..x.\|X..x..x..x..x..x\|..x..x..x..x..x.\|X..x..x..x..x..x\|..x..x..x..x..x.` | Akkordtöne (4) ab MIDI 72 über 2 Oktaven, aufwärts zyklisch | 1–16 | 50 |

- **Nicht beteiligt:** Lange Fläche, Langer Bass, Tupfer, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
KF   ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ●
KB   ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ●
AR   ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ●
```

- **Zusammenhang der Rollen:** Harmonie, Lautstärke, Register, Rollen und Notenwerte bleiben gleich. Für Z ändern sich nur die Ordnung der Akzente in der Kurzen Fläche (Akzent auf jeder Viertel → 3+3+2 / 2+3+3), die Arpeggio-Gruppierung (gerade Achtel → punktierte Achtel gegen den Puls) und die Tonwahl des Basses (Grundton → Halbton-Dissonanzbass, bewusst systemfremd). Die Notenzahl sinkt in der unruhigen Hälfte sogar leicht (siehe Prüfung).
- **Dynamik:** mf gleichbleibend. · **Pausen:** keine.
- **Ohne Hauptmelodie/Gegenstimme:** Studie ist ohne Melodie gebaut.
- **Variation:** Nur den Bass ändern (kleinster Unruheschritt). · **Fortsetzung:** JW-S11 oder JW-S19.
- **Bezug:** JW-H01, JW-R37, JW-R20, JW-B32
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3; keine Melodierolle; MIDI `JW-S30.mid`, 620 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte

## H Musikalische Übergangsstudien (10)

Jeder Übergang dauert 8 Takte; mindestens ein Element bleibt erhalten. JW-T09 und JW-T10 zeigen Wechsel zwischen atonalem, tonalem, modalem und symmetrischem Tonvorrat.

### JW-T01 · Lauern → Angst

- **Von → nach:** JW-S01 → JW-S02 · **XYZ:** 0,15 / 0,20 / 0,45 → 0,15 / 0,80 / 0,35 · **Taktart:** 4/4 · **Tempo (MIDI):** ♩ = 84
- **Akkorde je Takt:** `Cm` | `Db/C` | `Cm` | `Db/C` | `Cm` | `Abm/C` | `Cm` | `Abm/C`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 55, 3 Stimmen | 3, 4, 5, 6, 7, 8 | 45 · Dynamik je Takt ×1,00 1,00 0,80 0,90 1,00 1,10 1,20 1,30 |
| KF Kurze Fläche | `X..xX...X..xX.x.\|X..xX...X.x.X---  (wiederholt)` | Akkordtöne eng ab MIDI 48, 3 Stimmen | 5, 6, 7, 8 | 80 |
| LB Langer Bass | `X---------------\|----------------  (wiederholt)` | fest: C2 | 1–8 | 60 |
| KB Kurzer Bass | `X.......x.......\|X.......x.......\|X.......x.......\|X.......x.......\|X--xX---X--xX---\|X--xX---X--xX---\|X--xX---X--xX---\|X--xX---X--xX---` | Bass-Töne `R` ab MIDI 36 | 1–8 | 70 · Dynamik je Takt ×0,80 0,80 0,90 0,90 1,00 1,10 1,20 1,20 |
| TU Tupfer | `......x.........\|..........x.....  (wiederholt)` | oberster Akkordton ab MIDI 79, dann abwärts zyklisch | 1, 2, 3 | 45 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 70 |

- **Nicht beteiligt:** Arpeggio, Stich, Hauptmelodie
- **Gegenstimme:** `r/16 | C4/2 C4/2 C4/2 Eb4/10 | Db4/16 | r/16 | r/16 | C4/2 C4/2 Eb4/12 | Eb4/16 | r/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   · · ● ● ● ● ● ●
KF   · · · · ● ● ● ●
LB   ● ○ ● ○ ● ○ ● ○
KB   ● ● ● ● ● ● ● ●
TU   ● ● ● · · · · ·
GS   · ● ● · · ● ● ·
```

| bleibt | ändert sich | Gelenk |
|---|---|---|
| Pedal C, Cm als Tonika, Gegenstimmen-Motiv (Repetition + kleine Terz, JW-M05). | D♭/C (phrygisch) wird zu A♭m/C (hexatonisch); Herzschlag wird punktierter Marsch; Tupfer verschwinden, Kurze Fläche kommt. | Gemeinsamer Ton C und E♭; das Motiv wird in Takt 6 rhythmisch verkürzt (zwei statt drei Repetitionen). |

- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 3 5 2 4 4 5 3; Melodietöne auf Zählzeiten als Akkordton: GS 5/6; MIDI `JW-T01.mid`, 144 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 7/0/2
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-T02 · Angst → Action

- **Von → nach:** JW-S02 → JW-S13 · **XYZ:** 0,15 / 0,80 / 0,35 → 0,30 / 0,85 / 0,80 · **Taktart:** 4/4 · **Tempo (MIDI):** ♩ = 120
- **Akkorde je Takt:** `Cm` | `Abm/C` | `Cm` | `Abm/C` | `C/Db` | `Eb/E` | `F#/G` | `A/Bb`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `X..xX...X..xX.x.\|X..xX...X.x.X---\|X..xX...X..xX.x.\|X..xX...X.x.X---\|X..X..X.X..X.X..\|X..X..X.X.......\|X..X..X.X..X.X..\|X..X..X.X.......` | Akkordtöne eng ab MIDI 48, 3 Stimmen | 1–8 | 85 |
| LB Langer Bass | `X-------X-------  (wiederholt)` | fest: C2 | 1, 2, 3, 4 | 75 |
| KB Kurzer Bass | `XxxxXxxxXxxxXxxx  (wiederholt)` | Bass-Töne `b` ab MIDI 36 | 5, 6, 7, 8 | 85 |
| ST Stich | `X...............\|X.......X.......\|X...............\|X.......X.......\|X.......X.......\|X.......X.......\|X.......X.......\|X.......X.......` | fest: C2 G2 | 1–8 | 95 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 85 |

- **Nicht beteiligt:** Lange Fläche, Arpeggio, Tupfer, Hauptmelodie
- **Gegenstimme:** `r/16 | C4/6 Eb4/2 Ab4/8 | G4/16 | r/16 | Bb4/2 r/2 A4/2 G4/2 r/2 F#4/2 E4/4 | Eb4/2 r/2 Db4/2 Eb4/2 r/2 E4/2 F#4/4 | Bb4/2 r/2 A4/2 G4/2 r/2 F#4/2 E4/4 | Eb4/2 r/2 Db4/2 Eb4/2 r/2 E4/2 F#4/4`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
KF   ● ● ● ● ● ● ● ●
LB   ● ● ● ● · · · ·
KB   · · · · ● ● ● ●
ST   ● ● ● ● ● ● ● ●
GS   · ● ● · ● ● ● ●
```

| bleibt | ändert sich | Gelenk |
|---|---|---|
| Kurze Fläche und Stich als Rollen; Grundtempo-Gefühl (Viertel); Tonvorrat-Nähe (Cm liegt in Okt-A). | Pedal hört auf, der Kurze Bass übernimmt mit Sechzehnteln den Antrieb; Marsch wird zur Synkope; hexatonisch → oktatonisch mit Dissonanzbass. | Takt 5: Cm-Töne C und E♭ bleiben im neuen Klang C/D♭ bzw. E♭/E; der Stich wird vom Takt- zum Halbtaktschlag. |

- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 4 4 3 4 4 4 4; Melodietöne auf Zählzeiten als Akkordton: GS 7/15; MIDI `JW-T02.mid`, 262 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 14/0/10
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-T03 · Geheimnis → Staunen

- **Von → nach:** JW-S03 → JW-S08 · **XYZ:** 0,30 / 0,25 / 0,40 → 0,80 / 0,35 / 0,50 · **Taktart:** 4/4 · **Tempo (MIDI):** ♩ = 62
- **Akkorde je Takt:** `Cm` | `Ab/C` | `Am/C` | `F/C` | `Cmaj7` | `Ab/C` | `E/C` | `Cmaj7`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 55, 4 Stimmen | 1–8 | 48 · Dynamik je Takt ×1,00 1,00 1,00 1,00 1,05 1,10 1,15 1,10 |
| LB Langer Bass | `X---------------\|----------------  (wiederholt)` | fest: C2 | 1–8 | 50 |
| AR Arpeggio | `XxxxXxxxXxxxXxxx\|XxxxXxxxXxxx----  (wiederholt)` | Akkordtöne (4) ab MIDI 72 über 2 Oktaven, aufwärts zyklisch | 5, 6, 7, 8 | 40 |
| TU Tupfer | `x.....x...x.....\|..x.....x.....x.  (wiederholt)` | oberster Akkordton ab MIDI 84, dann abwärts zyklisch | 1, 2, 3, 4 | 40 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 55 |
| HM Hauptmelodie | — | notiert (siehe unten) | 1–8 | 65 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Stich
- **Hauptmelodie:** `r/16 | r/16 | r/16 | r/16 | G4/4 C5/4 E5/8 | Eb5/4 C5/4 Ab4/8 | B4/4 E5/4 G#5/8 | G5/16`
- **Gegenstimme:** `C4/6 F4/2 B4/8 | Bb4/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ● ● ● ● ● ● ●
LB   ● ○ ● ○ ● ○ ● ○
AR   · · · · ● ● ● ●
TU   ● ● ● ● · · · ·
GS   ● ● · · · · · ·
HM   · · · · ● ● ● ●
```

| bleibt | ändert sich | Gelenk |
|---|---|---|
| Pedal C und die Klänge mit gemeinsamem Ton C; Ab/C kommt in beiden Hälften vor. | Cm wird Cmaj7 (E♭ → E), Tupfer werden Sechzehntel-Arpeggio, die Gegenstimme macht der Hauptmelodie Platz. | Takt 4 → 5: F/C → Cmaj7 mit gemeinsamen Tönen C und F→E als einzige Halbtonbewegung. |

- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 4 3 3 2 4 3 4 3; Melodietöne auf Zählzeiten als Akkordton: HM 10/10, GS 1/3; MIDI `JW-T03.mid`, 108 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): HM 10/0/0, GS 1/3/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-T04 · Staunen → Triumph

- **Von → nach:** JW-S08 → JW-S14 · **XYZ:** 0,80 / 0,35 / 0,50 → 0,85 / 0,85 / 0,30 · **Taktart:** 4/4 · **Tempo (MIDI):** ♩ = 96
- **Akkorde je Takt:** `Cmaj7` | `Ab/C` | `E/C` | `Cmaj7` | `C` | `E` | `Ab` | `Bb`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 55, 4 Stimmen | 1–8 | 50 · Dynamik je Takt ×0,80 0,85 0,90 1,00 1,20 1,30 1,40 1,50 |
| KF Kurze Fläche | `X.......X...x.x.\|X.......X.......  (wiederholt)` | Akkordtöne eng ab MIDI 55, 4 Stimmen | 5, 6, 7, 8 | 80 |
| LB Langer Bass | `X---------------\|----------------  (wiederholt)` | fest: C2 | 1, 2, 3, 4 | 55 |
| KB Kurzer Bass | `X.......X.......  (wiederholt)` | Bass-Töne `R 5` ab MIDI 36 | 5, 6, 7, 8 | 85 |
| AR Arpeggio | `XxxxXxxxXxxxXxxx\|XxxxXxxxXxxxXxxx\|XxxxXxxxXxxxXxxx\|XxxxXxxxXxxx----\|X.x.x.x.x.x.x.x.\|X.x.x.x.x.x.x.x.\|X.x.x.x.x.x.x.x.\|X.x.x.x.x.x.x.x.` | Akkordtöne (4) ab MIDI 72 über 2 Oktaven, aufwärts zyklisch | 1–8 | 50 |
| ST Stich | `................\|............X---  (wiederholt)` | fest: C2 C3 | 8 | 100 |
| HM Hauptmelodie | — | notiert (siehe unten) | 1–8 | 80 · Dynamik je Takt ×0,80 0,80 1,00 1,00 1,15 1,20 1,25 1,30 |

- **Nicht beteiligt:** Tupfer, Gegenstimme
- **Hauptmelodie:** `C5/4 G5/8 A5/2 G5/1 F#5/1 | G5/8 Eb5/8 | r/16 | r/16 | C5/4 G5/8 A5/2 G5/1 F#5/1 | G#5/8 E5/8 | Ab5/4 Eb5/4 C5/4 Eb5/4 | F5/4 Bb5/12`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ● ● ● ● ● ● ●
KF   · · · · ● ● ● ●
LB   ● ○ ● ○ · · · ·
KB   · · · · ● ● ● ●
AR   ● ● ● ● ● ● ● ●
ST   · · · · · · · ●
HM   ● ● · · ● ● ● ●
```

| bleibt | ändert sich | Gelenk |
|---|---|---|
| Motiv JW-M01 (Quintaufschwung mit Doppelschlag) erscheint in beiden Hälften; Arpeggio-Rolle bleibt, wird ruhiger, aber kräftiger. | Pedal → schreitender Bass, Großterzwechsel → ♭VI–♭VII-Anlauf, Hinzukommen der Kurzen Fläche, Crescendo der Fläche. | Takt 2 und 6: dasselbe Motiv endet einmal auf E♭ (über A♭/C), einmal auf E (über E): harmonische Anpassung bei gleicher Kontur. |

- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 4 3 3 2 5 5 5 6; Melodietöne auf Zählzeiten als Akkordton: HM 13/16; MIDI `JW-T04.mid`, 185 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): HM 15/5/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-T05 · Wärme → Melancholie

- **Von → nach:** JW-S06 → JW-S05 · **XYZ:** 0,75 / 0,20 / 0,10 → 0,25 / 0,25 / 0,15 · **Taktart:** 4/4 · **Tempo (MIDI):** ♩ = 70
- **Akkorde je Takt:** `Cadd9` | `Fadd9/C` | `Am7` | `Fmaj7` | `Fm6` | `Cm/G` | `G7sus4` | `Cm`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 55, 4 Stimmen | 1–8 | 45 |
| LB Langer Bass | `X---------------  (wiederholt)` | Bass-Töne `b` ab MIDI 36 | 1–8 | 50 |
| AR Arpeggio | `X.x.x.x.x.x.x.x.\|X.x.x.x.x.x.x.x.\|X.x.x.x.x.x.x.x.\|X.x.x.x.x.x.x.x.\|X...X...X...X...\|X-------........\|................\|................` | Akkordtöne (4) ab MIDI 67 über 2 Oktaven, auf und ab | 1–8 | 48 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 55 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Tupfer, Stich, Hauptmelodie
- **Gegenstimme:** `r/16 | r/8 A4/2 G4/2 F4/4 | r/16 | r/8 A4/2 G4/2 F4/4 | Ab4/3 G4/5 Gb4/3 F4/5 | Eb4/3 D4/13 | r/16 | r/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ● ● ● ● ● ● ●
LB   ● ● ● ● ● ● ● ●
AR   ● ● ● ● ● ● · ·
GS   · ● · ● ● ● · ·
```

| bleibt | ändert sich | Gelenk |
|---|---|---|
| Fläche, Bassrolle und Register; die Antwortfigur der Gegenstimme hat dieselbe Stelle im Takt. | A → A♭ (Fmaj7 → Fm6), dann E → E♭; Arpeggio dünnt aus (Achtel → Viertel → Halbe → Pause); Antwortfigur wird Seufzerkette. | Takt 4 → 5: nur ein Ton ändert sich (A → A♭); die Gegenstimme beginnt die Seufzerkette auf genau diesem Ton. |

- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 4 3 4 4 4 2 2; Melodietöne auf Zählzeiten als Akkordton: GS 6/7; MIDI `JW-T05.mid`, 85 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 8/3/1
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-T06 · Romantik → Bedrohung

- **Von → nach:** JW-S07 → JW-H14 · **XYZ:** 0,60 / 0,40 / 0,25 → 0,20 / 0,45 / 0,60 · **Taktart:** 4/4 · **Tempo (MIDI):** ♩ = 72
- **Akkorde je Takt:** `Cmaj7` | `Fm6/C` | `Cmaj7` | `Abmaj7/C` | `Cm` | `F#m` | `Cm` | `F#m`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 55, 3 Stimmen | 1–8 | 45 |
| LB Langer Bass | `X---------------\|----------------  (wiederholt)` | fest: C2 | 1, 2, 3, 4 | 50 |
| KB Kurzer Bass | `X-------X-------  (wiederholt)` | Bass-Töne `R` ab MIDI 30 | 5, 6, 7, 8 | 60 |
| AR Arpeggio | `X.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.  (wiederholt)` | Akkordtöne (4) ab MIDI 67 über 2 Oktaven, aufwärts zyklisch | 1, 2, 3, 4 | 48 |
| TU Tupfer | `x.....x...x.....\|..x.....x.....x.  (wiederholt)` | oberster Akkordton ab MIDI 84, dann abwärts zyklisch | 6, 7, 8 | 40 |
| HM Hauptmelodie | — | notiert (siehe unten) | 1–8 | 65 |

- **Nicht beteiligt:** Kurze Fläche, Stich, Gegenstimme
- **Hauptmelodie:** `E4/4 C5/8 B4/4 | Ab4/12 G4/4 | r/16 | r/16 | Eb4/4 C5/8 B4/4 | A4/12 F#4/4 | r/16 | r/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ● ● ● ● ● ● ●
LB   ● ○ ● ○ · · · ·
KB   · · · · ● ● ● ●
AR   ● ● ● ● · · · ·
TU   · · · · · ● ● ●
HM   ● ● · · ● ● · ·
```

| bleibt | ändert sich | Gelenk |
|---|---|---|
| Liebesmotiv (JW-M20) mit gleicher Kontur und gleichem Rhythmus; Fläche und Register. | Dur → Moll, Pedal → Tritonusbass (C–F♯), Arpeggio verstummt, verstreute Tupfer kommen; aus der kleinen Sexte E–C wird die große Sexte E♭–C (Korrektur gegenüber der Vorfassung, die es umgekehrt beschrieb). | Takt 4 → 5: Abmaj7/C → Cm (gemeinsame Töne C, E♭, G); das Motiv erscheint in Takt 5 in Moll. |

- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 4 3 3 2 3 4 3 3; Melodietöne auf Zählzeiten als Akkordton: HM 8/10; MIDI `JW-T06.mid`, 85 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): HM 8/2/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-T07 · Ruhige Spannung → hochgradige Unruhe

- **Von → nach:** JW-H18 → JW-S16 · **XYZ:** 0,25 / 0,45 / 0,50 → 0,30 / 0,90 / 0,95 · **Taktart:** 4/4 · **Tempo (MIDI):** ♩ = 132
- **Akkorde je Takt:** `Cm(add#4)` | `Cm(add#4)` | `Cm(add#4)` | `Cm(add#4)` | `C/Db` | `Eb/E` | `F#/G` | `A/Bb`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 55, 4 Stimmen | 1, 2, 3, 4 | 45 |
| KF Kurze Fläche | `X.xxX.xxX.xxX.xx\|X.xxX.xxX.x.X...  (wiederholt)` | Akkordtöne eng ab MIDI 55, 3 Stimmen | 3, 4, 5, 6, 7, 8 | 75 |
| KB Kurzer Bass | `X.x.x.X.x.x.X.x.\|x.X.x.x.X.x.x.X.\|X.x.x.X.x.x.X.x.\|x.X.x.x.X.x.x.X.\|X-xX-xX-X-xX-xX-\|X-xX-xX-X-xX-xX-\|X-xX-xX-X-xX-xX-\|X-xX-xX-X-xX-xX-` | Bass-Töne `b` ab MIDI 36 | 1–8 | 75 |
| AR Arpeggio | `X...X...X...X...\|X.x.X.x.X.x.X.x.\|X.xxX.xxX.xxX.xx\|XxxxXxxxXxxxXxxx  (wiederholt)` | Akkordtöne (4) ab MIDI 67 über 2 Oktaven, aufwärts zyklisch | 5, 6, 7, 8 | 65 |
| ST Stich | `X.......X.......  (wiederholt)` | fest: Db2 G2 | 7, 8 | 100 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 70 |

- **Nicht beteiligt:** Langer Bass, Tupfer, Hauptmelodie
- **Gegenstimme:** `r/16 | G4/2 F#4/2 Eb4/2 C4/2 Db4/2 Eb4/2 E4/4 | r/16 | F#4/2 G4/2 A4/2 Bb4/2 A4/2 G4/2 F#4/4 | r/16 | r/16 | r/16 | Eb5/2 F#5/2 G5/12`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ● ● ● · · · ·
KF   · · ● ● ● ● ● ●
KB   ● ● ● ● ● ● ● ●
AR   · · · · ● ● ● ●
ST   · · · · · · ● ●
GS   · ● · ● · · · ●
```

| bleibt | ändert sich | Gelenk |
|---|---|---|
| Tonvorrat Okt-A in allen acht Takten; Bassrolle; die oktatonische Gegenstimmenlinie. | Statischer Klang → Dissonanzbass-Akkorde pro Takt; Achtel mit Akzentversatz → 3+3+2-Sechzehntel; Repetitionsakkorde ab Takt 3; Arpeggio verdichtet sich; Stich erst am Schluss. | Unruhe steigt zuerst durch Akzentversatz (Takt 1–4, gleiches Tempo, gleiche Notenzahl), dann durch Harmoniewechsel, zuletzt durch Dichte. |

- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 3 3 4 3 3 4 5; Melodietöne auf Zählzeiten als Akkordton: GS 4/10; MIDI `JW-T07.mid`, 342 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 9/8/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-T08 · Action → ruhige Entspannung

- **Von → nach:** JW-S11 → JW-H05 · **XYZ:** 0,55 / 0,80 / 0,75 → 0,85 / 0,15 / 0,20 · **Taktart:** 4/4 · **Tempo (MIDI):** ♩ = 120
- **Akkorde je Takt:** `C` | `Eb` | `F#` | `A` | `C` | `Cmaj7#11` | `C6/9` | `C`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 55, 4 Stimmen | 4, 5, 6, 7, 8 | 40 |
| KF Kurze Fläche | `X..X..X.X..X.X..\|X..X..X.X..X.X..\|X..X..X.X..X.X..\|X-------........\|................\|................\|................\|................` | Akkordtöne eng ab MIDI 55, 3 Stimmen | 1–8 | 80 |
| LB Langer Bass | `X---------------\|----------------  (wiederholt)` | fest: C2 | 5, 6, 7, 8 | 45 |
| KB Kurzer Bass | `XxxxXxxxXxxxXxxx\|XxxxXxxxXxxxXxxx\|X.x.x.X.x.x.X.x.\|X.......x.......\|................\|................\|................\|................` | Bass-Töne `R` ab MIDI 36 | 1–8 | 80 |
| AR Arpeggio | `XxxxXxx.XxxxXx..\|XxxxXxx.XxxxXx..\|................\|................\|X.x.x.x.x.x.x.x.\|X.x.x.x.x.x.x.x.\|X.x.x.x.x.x.x.x.\|X.x.x.x.x.x.x.x.` | Akkordtöne (4) ab MIDI 67 über 2 Oktaven, aufwärts zyklisch | 1–8 | 50 · Dynamik je Takt ×1,20 1,20 1,00 1,00 0,70 0,70 0,65 0,60 |
| ST Stich | `................\|............X---  (wiederholt)` | fest: C2 | 4 | 95 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 75 · Dynamik je Takt ×1,20 1,20 1,00 1,00 0,70 0,70 0,65 0,60 |

- **Nicht beteiligt:** Tupfer, Hauptmelodie
- **Gegenstimme:** `C5/4 G5/4 F5/2 E5/2 C6/4 | Bb5/4 G5/12 | r/16 | r/16 | C5/8 G5/8 | F#5/4 E5/4 C6/8 | A5/8 G5/8 | G5/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   · · · ● ● ● ● ●
KF   ● ● ● ● · · · ·
LB   · · · · ● ○ ● ○
KB   ● ● ● ● · · · ·
AR   ● ● · · ● ● ● ●
ST   · · · ● · · · ·
GS   ● ● · · ● ● ● ●
```

| bleibt | ändert sich | Gelenk |
|---|---|---|
| Kampfkontur der Gegenstimme (JW-M02): in Takt 1–2 marcato, in Takt 5–8 doppelt so langsam; Grundton C als Rahmen. | Bassmotor → Achtel → Pause → Pedal; Synkopen hören mit einer gehaltenen Note auf; Sechzehntel-Arpeggio → zwei Takte Stille → ruhige Achtel; Kleinterzzyklus → lydisches Nachglühen. | Takt 4: Schluss-Stich und ein gehaltener Akkord, danach zwei Takte Stille im Arpeggio; das Motiv kehrt vergrößert zurück (F → F♯ und B → A als harmonische Anpassung). |

- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 4 4 2 4 4 3 4 3; Melodietöne auf Zählzeiten als Akkordton: GS 13/14; MIDI `JW-T08.mid`, 192 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 14/1/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-T09 · Cluster → Dur (atonal → tonal)

- **Von → nach:** JW-S24 → JW-S08 · **XYZ:** 0,40 / 0,40 / 0,70 → 0,80 / 0,40 / 0,30 · **Taktart:** 4/4 · **Tempo (MIDI):** ♩ = 60
- **Akkorde je Takt:** `{B C Db}` | `{Bb B C Db D}` | `{A Bb B C Db D Eb}` | `{A Bb B C Db D Eb}` | `{G A B C D E}` | `Cadd9` | `C` | `C`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 60, 7 Stimmen | 1–8 | 55 |
| LB Langer Bass | `X---------------  (wiederholt)` | Bass-Töne `R` ab MIDI 36 | 5, 6, 7, 8 | 55 |
| AR Arpeggio | `X.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.  (wiederholt)` | Akkordtöne (4) ab MIDI 67 über 2 Oktaven, aufwärts zyklisch | 6, 7, 8 | 45 |
| TU Tupfer | `x.....x...x.....\|..x.....x.....x.  (wiederholt)` | oberster Akkordton ab MIDI 86, dann abwärts zyklisch | 1, 2, 3, 4 | 40 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ● ● ● ● ● ● ●
LB   · · · · ● ● ● ●
AR   · · · · · ● ● ●
TU   ● ● ● ● · · · ·
```

| bleibt | ändert sich | Gelenk |
|---|---|---|
| Lange Fläche in derselben Lage; Grundton C ist im Cluster von Anfang an enthalten. | Cluster wächst (3 → 5 → 7 Töne), wird pandiatonisch und öffnet sich zu C-Dur; Bass kommt erst mit dem tonalen Klang; Tupfer werden Arpeggio. | Takt 5: der Cluster wird zur pandiatonischen Menge (nur Dur-Töne), danach Cadd9 → C (Close-Encounters-Prinzip). |

- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 2 2 2 2 3 3 3; keine Melodierolle; MIDI `JW-T09.mid`, 78 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte

### JW-T10 · Tonal → leise Oktatonik

- **Von → nach:** JW-H34 → JW-S23 · **XYZ:** 0,25 / 0,25 / 0,20 → 0,20 / 0,20 / 0,60 · **Taktart:** 4/4 · **Tempo (MIDI):** ♩ = 60
- **Akkorde je Takt:** `Cm` | `Fm/C` | `Cm` | `Ab/C` | `Cm` | `Ebm|Cm` | `Cm` | `Am|F#m`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 55, 3 Stimmen | 1–8 | 40 |
| LB Langer Bass | `X---------------  (wiederholt)` | fest: C2 | 1–8 | 45 |
| AR Arpeggio | `X.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.  (wiederholt)` | Akkordtöne (4) ab MIDI 67 über 2 Oktaven, aufwärts zyklisch | 1, 2, 3, 4 | 40 · Dynamik je Takt ×1,00 0,90 0,80 0,70 1,00 1,00 1,00 1,00 |
| TU Tupfer | `..........x.....\|...x............  (wiederholt)` | oberster Akkordton ab MIDI 43, dann abwärts zyklisch | 5, 6, 7, 8 | 40 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 45 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Stich, Hauptmelodie
- **Gegenstimme:** `r/16 | r/16 | r/16 | r/16 | r/16 | C4/2 Eb4/2 Db4/2 E4/2 Eb4/4 r/4 | r/16 | r/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ● ● ● ● ● ● ●
LB   ● ● ● ● ● ● ● ●
AR   ● ● ● ● · · · ·
TU   · · · · ● ● ● ●
GS   · · · · · ● · ·
```

| bleibt | ändert sich | Gelenk |
|---|---|---|
| Pedal C, Cm als Ruhepunkt (Cm gehört zu C-Moll und zu Okt-A), Lage der Fläche. | Äolische Nachbarklänge (Fm, A♭) werden zu Kleinterz-Polychorden; Arpeggio dünnt aus, tiefe Einzeltöne übernehmen; die Gegenstimme bringt den oktatonischen Kreisel. | Takt 5: Cm als gemeinsamer Klang beider Systeme; der erste systemtypische Ton (G♭) erscheint im Polychord in Takt 6. |

- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 3 3 3 3 4 3 3; Melodietöne auf Zählzeiten als Akkordton: GS 2/3; MIDI `JW-T10.mid`, 77 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 3/0/2
- **Haltetöne über Akkordwechsel:** keine Konflikte

## I Generatorpräferenzen (überarbeitet)

Die Regeln der Vorfassung enthielten Einschränkungen, die eine funktionierende Engine beschneiden würden (Oktatonik-Quote, Rollenhöchstzahl, Rotationspflicht, Zeitlimit für Zuspitzungen, Taktwechsel durch Vorlagen). Sie sind **zurückgenommen** (Liste in der Qualitätsprüfung). Alle folgenden Einträge sind Gewichtungen: sie verändern Wahrscheinlichkeiten, sperren nichts und überschreiben keine Benutzer- oder Host-Einstellung. Gewichtswerte sind [E].

### I.0 Unabhängige Wirkung von Färbung, Intensität und Unruhe

| Stellgröße | wirkt vor allem auf | wirkt nicht automatisch auf | Beleg | Demonstration |
|---|---|---|---|---|
| Akkordqualität, Tonvorrat (lydisch … phrygisch, hexatonisch, oktatonisch), Lage der Farbe | X (Färbung) | Notenzahl, Tempo | Moduswechsel desselben Themas (S1); Schneller zu ♭VII/II♯ (S6) | JW-T05, JW-T06 |
| Register, Verdopplung, Besetzungsstärke, Dynamik, Akzentstärke | Y (Intensität) | Harmonie, Akzentordnung, harmonischer Rhythmus | Keys’ Theme leise (Harfe/Celesta) und laut (Trompeten/Pauke) mit gleicher Harmonik; Boba Fett: unruhig, aber nur Fagotte (S26, S24) | JW-S29: Notenzahl 49 → 134 (nur durch Verdopplung und zusätzliche Besetzung, keine kürzeren Werte), mittlere Velocity 44 → 95; Akzentordnung, Harmonie und harmonischer Rhythmus identisch |
| Akzentordnung, Gruppierung, Synkope, Kreuzrhythmus | Z (Unruhe) | Lautstärke, Notenzahl | TIE-Figur, Finn-Puls (S24) | JW-S30: Notenzahl 320 → 300, mittlere Velocity 69 → 69 |
| Dissonanzbass (Nicht-Akkordton, Pedal unter wechselnden Dreiklängen) | Z | Y | Jawas, TIE, Major Trouble (S24) | JW-S04, JW-S30 (zweite Hälfte) |
| Wechsel des Tonvorrats (diatonisch → lydisch-♯2 → hexatonisch/oktatonisch), Fragmentierung | Z (und X) | Y | Ark/Map Room, E.T. New Home (S25, S26) | JW-T09, JW-T10 |
| Dichte (mehr Einsätze) | Y und Z gleichzeitig | — | nur als letzte Stufe genutzt | JW-R29 |
| Ausdünnung | kann Y erhöhen (Spannungsspitze) | — | E.T., „Losing E.T.“: tiefe Lage fällt weg, nur hohe Streicher bleiben (S26) | JW-S28 Takte 29–32 |

**Bevorzugte Reihenfolge für steigendes Z** [E aus N]: 1. Akzentordnung, 2. Dissonanzbass, 3. Tonvorratswechsel, 4. erst dann Dichte. **Für steigendes Y**: Register und Verdopplung, Besetzung (Blech, Chor), Dynamik; dasselbe Material bleibt.

### I.1 Vokabular und Systemwahl

| Präferenz | Zweck | Evidenz | XYZ-Abhängigkeit | Situationen | Kombination | weniger geeignet | Eingangsdaten | hörbares Ergebnis | Variation |
|---|---|---|---|---|---|---|---|---|---|
| I-1.1 Systemwahl nach XYZ | Farben passend zum Feld | B.1, S1, S6, S24 [N/I] | X hoch: Lydisch/Mixolydisch/Dur/Planing 3, Hexatonik 2; X niedrig: Moll/Phrygisch/Hexatonik/Pantriadik 3, Oktatonik 2–3 je nach Z | immer | mit I-3.x | Ganztonvorlagen (Hypothese) niedriger gewichten | XYZ, aktueller Vorrat | Farbe folgt dem Feld | Vorrat innerhalb einer Szene beibehalten oder über Gelenk wechseln |
| I-1.2 Vielfalt durch Auswahl, nicht durch Zwang | Gleichförmigkeit vermeiden | Barry-Erfahrung [E] | unabhängig | lange Szenen | mit I-9.1 | wenn ein Motiv oder Ostinato gerade trägt | Verlauf | Wiederholung erlaubt; eine kürzlich gespielte Vorlage erhält nur leicht geringeres Gewicht | Variante derselben Vorlage bevorzugen |

### I.2 Auswahlpräferenzen

| Präferenz | Zweck | Evidenz | XYZ-Abhängigkeit | Situationen | Kombination | weniger geeignet | Eingangsdaten | hörbares Ergebnis | Variation |
|---|---|---|---|---|---|---|---|---|---|
| I-2.1 Lange Klänge | Ruhe, Raum für Dialog | S1 [N] | Y niedrig höher gewichtet | Dialog | mit Arpeggio, Tupfern, Einwürfen | — | Akkord, Dauer | stehende Fläche | Stimmwechsel im Klang (JW-H05, H61) |
| I-2.2 Bewegung auch bei niedriger Intensität | Zurückhaltung ist nicht Stillstand | Auftrag; E.T.-Cues (S26) | Kurze Fläche, Kurzer Bass, Tupfer auch bei Y < 0,3 möglich | immer | — | — | — | leise, bewegliche Musik | JW-R39, JW-R40, JW-R42 |
| I-2.3 Oktatonik als Farbe neben anderen | Merkmal ohne Dominanz | S1, S24 [N] | Gewicht steigt mit Z und sinkt mit X, ohne Obergrenze | Spannung, Action, auch leise | mit Hexatonik, Planing, Polychord | — | XYZ | abwechslungsreiche dunkle Bereiche | leise Fassungen JW-H74, JW-S23 einbeziehen |

### I.3 Harmonische Verfahren

| Präferenz | Zweck | Evidenz | XYZ-Abhängigkeit | Situationen | Kombination | weniger geeignet | Eingangsdaten | hörbares Ergebnis | Variation |
|---|---|---|---|---|---|---|---|---|---|
| I-3.1 Mediantrückung bei Staunen/Triumph | Glanz durch Überraschung | S1, S3, S24 [N] | X > 0,6, Y > 0,4 höher gewichtet | Höhepunkt, Ankunft | mit Planing (JW-H64) | — | Klang, Zielklang | neuer Klang eine große Terz entfernt | auf- oder abwärts |
| I-3.2 Planing über Pedal | Bewegung bei stabiler Farbe | S24 [N] | alle X; Z mittel bis hoch | Abenteuer, Neugier, dunkle Gewalt (Moll-Sextakkorde) | mit I-4.2 | — | Melodie oder Linie | parallele Dreiklänge folgen einer Linie | Dur, Moll, erste Umkehrung |
| I-3.3 Spannung durch Harmonie statt Noten | Unruhe ohne Dichte | S10, S24 [N] | Z steigt bei konstantem Y | lange Szenen | mit I-5.1 | — | Harmonie, Bass | Bass steigt oder wird dissonant | Basslauf, Pedalwechsel |
| I-3.4 Systemwechsel über Gelenk | organische Farbwechsel | B.3, S25, S29 [N/E] | bei Änderung von X oder Z | Übergänge | mit I-8.1 | — | alter/neuer Vorrat | Wechsel über gemeinsamen Klang, verm. Septakkord oder Cluster | JW-H20, H21, H75, JW-T09, T10 |

### I.4 Bassverfahren

| Präferenz | Zweck | Evidenz | XYZ-Abhängigkeit | Situationen | Kombination | weniger geeignet | Eingangsdaten | hörbares Ergebnis | Variation |
|---|---|---|---|---|---|---|---|---|---|
| I-4.1 Bass übernimmt Antrieb | Energie bündeln | S1 [N] | Y und Z hoch höher gewichtet | Action | Arpeggio darf weiterlaufen (leiser, höher) oder pausieren | — | Harmonie | Sechzehntel- oder 3+3+2-Bass | JW-B25, B29, B33 |
| I-4.2 Dissonanzbass | Instabilität unter klarer Farbe | S24 [N] | Z mittel bis hoch, alle X | Neugier, Verfolgung, Unbehagen | mit Planing | — | Akkordgrundton, nächster Grundton | Bass auf Nicht-Akkordton, als [systemfremd] markiert, wenn außerhalb des Vorrats | JW-B09, B31, B32 |
| I-4.3 Akkordunabhängiger Bass | eigene Linie | S1, S28 [N] | beliebig | Choral, Ostinato, Lauf | — | — | Tonvorrat | Cantus, Skalenlauf, Kleinterz-Pedal | JW-B07, B33, B35, B40 |

### I.5 Rhythmische Verfahren

| Präferenz | Zweck | Evidenz | XYZ-Abhängigkeit | Situationen | Kombination | weniger geeignet | Eingangsdaten | hörbares Ergebnis | Variation |
|---|---|---|---|---|---|---|---|---|---|
| I-5.1 Akzentordnung vor Tempo | Unruhe ohne Dichte | S21, S24 [N] | Z steigt | Spannung, Abenteuer | mit I-3.3 | — | Raster | wechselnde Gruppen, Synkopen, 3 gegen 4 | JW-R03, R20, R37, R38 |
| I-5.2 Gemeinsames Akzentgerüst | viele Schichten, eine Ordnung | [E] | Y und Z hoch | Action, Zuspitzung | mit I-4.1 | — | Raster aller Rollen | Klangwechsel und Akzente fallen zusammen | JW-R48, JW-S16, JW-S20 |
| I-5.3 Taktarten | passendes Material zur Host-Taktart | S1, S12 [N] | unabhängig | nur wenn der Host die Taktart vorgibt | — | keine Änderung der Host-Taktart | Host-Taktart | Vorlagen in 7/8, 5/4, 6/8, 3/2 nur bei passender Taktart | JW-R05, R06, R16, R18, R41, R44 |

### I.6 Motivregeln

| Präferenz | Zweck | Evidenz | XYZ-Abhängigkeit | Situationen | Kombination | weniger geeignet | Eingangsdaten | hörbares Ergebnis | Variation |
|---|---|---|---|---|---|---|---|---|---|
| I-6.1 Etablieren vor Variieren | Erkennbarkeit | S1, Erfahrung Motivgedächtnis | unabhängig | erste Szene eines Motivs | — | — | Motivgedächtnis | zweimal unverändert, dann Fragmente | beliebig lange Wiederkehr erlaubt |
| I-6.2 Systemübertragung | Wiederkehr in neuer Farbe | S1, S25 [N] | bei Vorratswechsel | Übergänge | mit I-3.4 | — | Motiv, Vorrat | gleiche Kontur, neue Intervalle | F.3 |
| I-6.3 Zielton planen | Phrasen mit Richtung | S11 [N] | unabhängig | Hauptmelodie, Gegenstimme | mit I-3.1 | — | Schlussklang | Zielton Akkordton | Zielton durch Obersekunde verschieben |
| I-6.4 Übergabe zwischen Rollen | Kontinuität ohne Daueraktivität | [E] | unabhängig | lange Szenen | — | — | Motiv | Gegenstimme → Hauptmelodie → Fragment | JW-S25 |

### I.7 Rollenkoordination

| Präferenz | Zweck | Evidenz | XYZ-Abhängigkeit | Situationen | Kombination | weniger geeignet | Eingangsdaten | hörbares Ergebnis | Variation |
|---|---|---|---|---|---|---|---|---|---|
| I-7.1 Ablösen statt Addieren (bevorzugt) | Durchhörbarkeit | [I] | Y niedrig stärker gewichtet | Dialog | — | Höhepunkte | aktive Rollen | Tupfer ↔ Arpeggio, Gegenstimme ↔ Hauptmelodie | Rollenverläufe G/H |
| I-7.2 Lagentrennung | Klarheit bei vielen Rollen | [E] | mit Y steigend wichtiger | Action | — | — | Register | gleichzeitige Rollen in getrennten Lagen statt Rollenhöchstzahl | JW-S19 (Arpeggio hoch über Bass) |
| I-7.3 Gleiche Tonvorräte für mehrere Rollen | geschlossener Klang | S24 [I] | symmetrische Systeme | Oktatonik, Hexatonik | mit I-4.3 | — | Tonvorrat | Tupfer, Gegenstimme, Bass im selben Vorrat | JW-S23, JW-S27 |

### I.8 Übergänge

| Präferenz | Zweck | Evidenz | XYZ-Abhängigkeit | Situationen | Kombination | weniger geeignet | Eingangsdaten | hörbares Ergebnis | Variation |
|---|---|---|---|---|---|---|---|---|---|
| I-8.1 Ein Element bleibt | Kontinuität | [E] | bei jedem Wechsel | Stimmungsfahrt | mit I-3.4 | — | alte/neue Vorlage | Pedal, gemeinsamer Ton, Motiv oder Rolle bleibt | JW-T01–T10 |
| I-8.2 Ausdünnen oder Verdichten nach Richtung | sauberer Wechsel | [I] | Richtung von Y | Entspannung / Steigerung | — | — | — | Arpeggio wird Viertel, Halbe, Pause bzw. umgekehrt | JW-R28, JW-R29 |

### I.9 Längerfristige Entwicklung

| Präferenz | Zweck | Evidenz | XYZ-Abhängigkeit | Situationen | Kombination | weniger geeignet | Eingangsdaten | hörbares Ergebnis | Variation |
|---|---|---|---|---|---|---|---|---|---|
| I-9.1 Schichtwechsel bei gleicher Stimmung | Entwicklung über Minuten | Halloween-, Keys-, Flying-Prinzip (S26) [N] | bei statischem XYZ | lange Szenen | mit I-6.4 | — | Laufzeit | Schichten, Register, Rollen wechseln, Harmonie darf bleiben | JW-S25–S28 |
| I-9.2 Zuspitzung halten | gewählte Stimmung respektieren | Auftrag | Z > 0,9 | Höhepunkt | mit I-5.2 | — | gewähltes XYZ | bleibt bestehen, solange der Anwender sie wählt; Variation innerhalb (z. B. Halbtakt- und Taktwechsel in JW-S16) | JW-S16 |

## J XYZ-Abdeckungsmatrix (aktualisiert)

Eckbereiche (Grenze 0,5). Zelle: Anzahl und IDs (ohne Präfix). Studien mit XYZ-Fahrt (JW-S29, S30) stehen beim Startpunkt.

| Ecke | Harmonik | Rhythmik | Bass | Motive | Phrasen | Studien |
|---|---|---|---|---|---|---|
| DRS (dunkel / zurückhaltend / stabil) | 6: H11, H34, H39, H40, H41, H42 | 2: R26, R35 | 3: B05, B21, B26 | 4: M13, M15, M24, M28 | 3: P04, P08, P11 | 3: S01, S03, S05 |
| DRU (dunkel / zurückhaltend / unruhig) | 10: H12, H14, H23, H24, H25, H54, H71, H72, H73, H74 | 4: R11, R36, R45, R47 | 5: B10, B23, B33, B37, B40 | 11: M05, M06, M07, M09, M14, M23, M30, M42, M46, M47, M48 | 2: P16, P22 | 5: S04, S23, S24, S28, S29 |
| DIS (dunkel / kraftvoll / stabil) | 6: H13, H56, H57, H67, H68, H69 | 4: R23, R28, R43, R46 | 4: B20, B24, B34, B35 | 4: M29, M34, M43, M44 | 3: P18, P21, P24 | 4: S02, S21, S22, S26 |
| DIU (dunkel / kraftvoll / unruhig) | 14: H17, H18, H19, H20, H22, H43, H44, H45, H46, H47, H48, H53, H70, H76 | 12: R02, R04, R05, R06, R07, R08, R20, R21, R22, R25, R29, R30 | 9: B06, B07, B08, B09, B12, B13, B17, B19, B25 | 4: M11, M12, M32, M45 | 3: P05, P06, P10 | 3: S12, S13, S16 |
| HRS (hell / zurückhaltend / stabil) | 13: H03, H05, H06, H10, H28, H30, H31, H32, H35, H36, H37, H38, H52 | 4: R12, R14, R16, R24 | 6: B01, B03, B15, B16, B22, B28 | 7: M01, M08, M20, M21, M22, M26, M33 | 4: P02, P07, P12, P15 | 2: S06, S07 |
| HRU (hell / zurückhaltend / unruhig) | 8: H15, H26, H50, H58, H59, H60, H61, H75 | 8: R15, R17, R33, R34, R39, R40, R41, R42 | 4: B14, B30, B31, B38 | 8: M10, M25, M31, M35, M36, M37, M38, M39 | 4: P09, P17, P19, P23 | 6: S08, S09, S10, S17, S18, S25 |
| HIS (hell / kraftvoll / stabil) | 9: H01, H02, H04, H07, H08, H09, H33, H49, H55 | 5: R01, R10, R13, R18, R31 | 4: B02, B04, B11, B27 | 6: M02, M03, M04, M16, M17, M27 | 3: P01, P03, P14 | 3: S14, S15, S30 |
| HIU (hell / kraftvoll / unruhig) | 10: H16, H21, H27, H29, H51, H62, H63, H64, H65, H66 | 9: R03, R09, R19, R27, R32, R37, R38, R44, R48 | 5: B18, B29, B32, B36, B39 | 4: M18, M19, M40, M41 | 2: P13, P20 | 4: S11, S19, S20, S27 |

### J.1 Vielfalt innerhalb der Ecken (nicht nur Anzahl)

| Ecke | Tonvorräte der Harmonik | harmonischer Rhythmus (Wechsel pro 8 Takte) | Rhythmus-Taktarten | Bassarten (fest/beweglich) |
|---|---|---|---|---|
| DRS | Dorisch 2, Moll gesamt 1, Chromatisch 1, Pantriadisch 1, Phrygisch 1 | 5, 6, 7, 8 | 4/4 2 | 0 fest, 3 beweglich |
| DRU | Okt-A 4, Hex-C 3, Chromatisch 2, Pantriadisch 1 | 4, 5, 6, 7, 8 | 4/4 3, 4/4T 1 | 1 fest, 4 beweglich |
| DIS | Äolisch 2, Pantriadisch 2, Hex-C 1, Moll harm. 1 | 4, 6, 7, 8 | 4/4 4 | 0 fest, 4 beweglich |
| DIU | Okt-A 6, Pantriadisch 2, Okt-A/Okt-C 1, Ungarisch-Moll 1, Moll harm. 1, Hex-C 1, Okt-A/Okt-B 1, Äolisch/Phrygisch/Moll harm. 1 | 1, 3, 4, 6, 7, 8, 12, 15 | 4/4 8, 5/4 2, 4/4T 1, 7/8 1 | 0 fest, 9 beweglich |
| HRS | Dur-Moll-Mischung 5, Dur 3, Pantriadisch 3, Lydisch 2 | 5, 6, 7, 8 | 4/4 3, 6/8 1 | 1 fest, 5 beweglich |
| HRU | Pantriadisch 3, Okt-A 1, Ganzton-0 1, Hex-C 1, Lydisch-♯2 1, Chromatisch/Dur 1 | 4, 5, 6, 7, 8 | 4/4 5, 3/4 1, 4/4T 1, 6/8 1 | 0 fest, 4 beweglich |
| HIS | Dur-Moll-Mischung 4, Pantriadisch 3, Mixolydisch 1, Lydisch 1 | 3, 5, 6, 7 | 4/4 3, 3/2 1, 2/2 1 | 1 fest, 3 beweglich |
| HIU | Pantriadisch 3, Mixolydisch 2, Hex-C 2, Okt-A 1, Dur/Okt-A 1, Lydisch 1 | 7, 8, 12, 14, 16 | 4/4 6, 6/8 2, 3/4 1 | 0 fest, 5 beweglich |

### J.2 Zwischenbereiche, Ränder, Spitzenunruhe

- **Harmonik nach Feinregion (0,4/0,6):** DIS 4, DIU 7, DIm 5, DRS 2, DRU 2, DRm 5, DmU 3, Dmm 4, HIS 3, HIU 3, HIm 5, HRS 4, HRU 2, HRm 3, HmS 4, HmU 1, Hmm 5, mIU 1, mRS 3, mRm 3, mmS 1, mmU 1, mmm 5.
- **X ≤ 0,15 (sehr dunkel):** JW-H12, JW-H13, JW-H23, JW-H41, JW-H46, JW-H57, JW-H67, JW-H68, JW-H69, JW-H71, JW-R46, JW-B35, JW-M07, JW-M24, JW-M34, JW-M43, JW-M44, JW-M45, JW-M48, JW-P04, JW-P21, JW-P24, JW-S01, JW-S02, JW-S21, JW-S22, JW-S26, JW-S28, JW-S29
- **X ≥ 0,85 (sehr hell):** JW-H03, JW-H04, JW-H05, JW-H49, JW-H62, JW-H64, JW-B22, JW-M08, JW-M41, JW-P03, JW-P14, JW-P15, JW-P20, JW-S14, JW-S19, JW-S20
- **Y ≤ 0,2 (sehr leise):** JW-H05, JW-H36, JW-H61, JW-H72, JW-H73, JW-H74, JW-R12, JW-R40, JW-R45, JW-R47, JW-B37, JW-B40, JW-M21, JW-M24, JW-M31, JW-M36, JW-M42, JW-M47, JW-M48, JW-P04, JW-P22, JW-S01, JW-S06, JW-S23, JW-S24
- **Y ≥ 0,85 (sehr kraftvoll):** JW-H17, JW-H22, JW-H33, JW-H47, JW-H48, JW-H49, JW-H57, JW-H64, JW-R22, JW-B25, JW-P14, JW-S13, JW-S14, JW-S16, JW-S20
- **Z ≥ 0,9 (letzte 10 % Unruhe):** JW-H47, JW-H48, JW-S16
- **Z ≤ 0,15 (sehr stabil):** JW-H10, JW-H35, JW-H36, JW-B01, JW-S05, JW-S06
- **Übergänge zwischen Nachbarbereichen:** JW-T01 DRS → DIS; JW-T02 DIS → DIU; JW-T03 DRS → HRU; JW-T04 HRU → HIS; JW-T05 HRS → DRS; JW-T06 HRS → DRU; JW-T07 DRU → DIU; JW-T08 HIU → HRS; JW-T09 DRU → HRS; JW-T10 DRS → DRU.
- **Redundanz Harmonik:** identische Akkordfolgen: keine; transpositionsgleiche Folgen: siehe Qualitätsprüfung.
- **Bewertung:** Die vier im Auftrag genannten Bereiche haben jetzt jeweils mehrere unterschiedliche Verfahren (HRU: Planing, Lydisch-♯2, Plagalpendel, Sus-Farben, hexatonischer Zyklus; HIU: lydische Schleife, Planing mit Rückung, Sus-/Quartenpuls, Halbtonrutsche, Kleinterz-Durzyklus; DIS: archaische Kadenz, hexatonisches Pendel, Tritonusoszillation, Dies-irae-Choral, Mollchoral; DRU: Dissonanzbass, Polychord-Oszillation, leise Oktatonik, Fremdton-Arpeggien, Halbtonpaare, hohe Pedale). Am dünnsten bleibt der Ganzton-Bereich (nur Hypothese).

## K Vergleich mit John Barry

Grundlage: Barry-Gesamtfassung vom 24.11.2026 (46 Barry-Harmonievorlagen) und diese Fassung. Die Tabelle beschreibt Schwerpunkte der Vokabulare, nicht Grenzen der Komponisten.

| Dimension | Barry (Vokabular) | Williams (Vokabular) | gemeinsam/universell |
|---|---|---|---|
| Harmonische Bewegung | sehr langsam, Farbe im Klang (mM7, m6, add2) | von Liegeklang bis Halbtaktwechsel; Klangwechsel als Ereignis (Medianten, Tritonus, Planing) | Pedal unter wechselnden Oberklängen |
| Harmonische Systeme | Dur/Moll, wenige modale Wendungen | zusätzlich Lydisch(-♯2), Oktatonik, Hexatonik, Polychorde, Cluster | Mischung (♭VI, ♭VII, iv), Phrygisch |
| Bassführung | Pedal oder Pendel | zusätzlich Dissonanzbass, Cantus, Basslauf, Bass als Motor | Lamentobass, Oktavpendel |
| Rhythmische Vielfalt | Ostinato, Achtel, Diminution, Stille | wechselnde Akzentgruppen, Hemiole, Taktwechsel (wenn Host), Kreuzrhythmus | Ostinato als Träger |
| Melodische Kontur | lange Haltetöne, Stufen und Terzen | Sprünge als Phrasenkopf, Kampfkontur, Staccato-Zellen | Zielton auf Akkordton |
| Motivische Entwicklung | Wiederholung und Umbesetzung | Transformation über Modus und System, Kanon, Übergabe zwischen Rollen | frühe vollständige Wiederkehr |
| Intensität/Unruhe | Schichtung über Pedal | Y über Register/Besetzung, Z über Akzentordnung und Dissonanzbass (JW-S29/S30) | Steigerung durch Register |

| Ecke | Barry | Williams | typischer Unterschied |
|---|---|---|---|
| DRS | 10 | 6 | Barry: Ein-Akkord-Ostinato mM7 · Williams: Mollklänge im Kleinterzzyklus, phrygische Färbung, Lamento |
| DRU | 2 | 10 | Barry: chromatische Linie über Pedal · Williams: Dissonanzbass, Halbton-/Tritonus-Mollpaare, leise Oktatonik, Fremdton-Arpeggien |
| DIS | 6 | 6 | Barry: wuchtiges Mollpedal · Williams: Dies-irae-Choral, Tritonusoszillation, hexatonisches Pendel, archaische Kadenz |
| DIU | 8 | 14 | Barry: Moll-Motor mit Pendel · Williams: Oktatonik, Planing in Moll, Ungarisch-Moll, Polychorde |
| HRS | 10 | 13 | Barry: Dur mit add9, lange Klänge · Williams: lydische Schwebe, pandiatonische Fläche |
| HRU | 2 | 8 | Barry: wenige, überwiegend Extrapolation · Williams: Staccato-Planing, Lydisch-♯2, Plagalpendel mit Parallelabstieg |
| HIS | 4 | 9 | Barry: Fanfare mit langem Klang · Williams: ♭VI–♭VII–I, Mixolydisch, Medianten |
| HIU | 4 | 10 | Barry: wenige, überwiegend Extrapolation · Williams: lydische Schleife, Planing mit Rückung, Sus-Puls, Halbtonrutsche |

## L Technische Umsetzbarkeit (vorläufig, ohne Kenntnis des aktuellen Quellcodes)

| Kategorie | Inhalt | Vorlagen/Präferenzen |
|---|---|---|
| Direkt übernehmbare Datenvorlagen | Akkordfolgen mit Dauern, Raster, Bassraster mit relativen und festen Tönen, Motive und Phrasen (Ton/Dauer), Studien als Ereignisliste (CSV) | C–H |
| Musikalische Auswahlpräferenzen | Gewichte nach XYZ, keine Sperren | I.0–I.9 |
| Vermutlich bereits vorhanden | Akkordbasierte Rollen, Pedal/bewegter Bass, Arpeggio, Motivgedächtnis mit früher Wiederkehr und harmonischer Anpassung, Frage–Antwort, fließende Übergänge, Rollenkoordination | I-2.x, I-6.1, I-6.3, I-7.1 |
| Kleine notwendige Erweiterungen | (1) optionales Feld **Tonvorrat** je Vorlage oder Akkord, gemeinsam für mehrere Rollen (Oktatonik, Hexatonik, Lydisch-♯2); (2) Akkordsymbole als **Polychord** `X\|Y` und als **Tonklassenmenge** `{…}`; (3) feste, akkordunabhängige Basstöne `P(x)` (Cantus, Lauf); (4) gemeinsames Akzentgerüst für mehrere Rollen; (5) Kennzeichnung „systemfremd erlaubt“ pro Rolle (Dissonanzbass) | JW-H22, H47, H71, H74, H75; JW-B33, B35; JW-R48; JW-S19 |
| Komplexer, zunächst nicht notwendig | Systemübertragung von Motiven mit automatischer Intervallanpassung; Abschnittsplanung über 32 Takte; neo-riemannsche Operatoren als Generator | I-6.2, JW-S25, JW-S28 |

**Kontinuität bei XYZ-Veränderungen** [vorläufig]: Die Übergangsstudien zeigen, dass dafür keine neue Planung nötig ist, wenn beim Wechsel ein Element (Pedal, gemeinsamer Ton, Motiv, Rolle) gehalten wird. Das lässt sich als Präferenz (I-8.1) über die vorhandene Übergangslogik abbilden.

## M Qualitätsprüfung und Forschungslücken

Alle Prüfergebnisse, gefundenen Fehler und Korrekturen stehen in `JW_Qualitaetspruefung_und_Aenderungen.md`. Kurzfassung: 276 IDs, alle eindeutig; alle Taktdauern, Akkorddefinitionen, Tonvorräte, Raster und MIDI-Daten geprüft; CSV und MIDI stimmen überein.

| Lücke (akzeptiert) | Folge |
|---|---|
| Keine Partituren; Belege auf Cue- und Timecode-Ebene | Vorlagen übertragen Verfahren, rekonstruieren keine Takte |
| Richards’ „Alpha chord“, „action extensions“, Dissonanzbass-Akkorde nur als Kursgliederung | als Kategorien genutzt, nicht als Definition |
| Asteroid Field, Battle of Endor, Mine Car Chase, Hook, Jurassic Park, Harry Potter ohne taktgenaue Analyse | helle Action stützt sich auf Katalogeinträge (Planing, lydische Schleife, Semitonal Slip) |
| Close Encounters nur auszugsweise | JW-H75 als einziges Cluster-Verfahren |
| Ganztonharmonik nicht belegt | JW-H26, JW-M31 als Hypothese |
| Normandie (E.T.) ist eine studentische Arbeit | Belege aus E.T.-Underscore als N markiert, aber mit Quellenhinweis |

## N Quellenverzeichnis

| Kürzel | Quelle | Status |
|---|---|---|
| S1 | Lehman, Frank: *Complete Catalogue of the Musical Themes of Star Wars*, Stand 23.03.2023, franklehman.com/starwars | eingesehen |
| S2 | Lehman, Frank: *A Guide to the Musical Themes of the Indiana Jones Films*, Stand 2023, franklehman.com | eingesehen |
| S3 | Lehman, Frank: „Hollywood Cadences“. *Music Theory Online* 19.4 (2013) | eingesehen (erste Hälfte) |
| S4 | Lehman, Frank: *Hollywood Harmony*. Oxford University Press 2018 | Leseprobe (Inhalt, Einleitung) und Rezension |
| S5 | Lehman, Frank: *The Skywalker Symphonies*. Oxford University Press 2026 | nur Verlagsabstract |
| S6 | Schneller, Tom: „Modal Interchange and Semantic Resonance in Themes by John Williams“. *Journal of Film Music* 6.1, 49–74, DOI 10.1558/jfm.v6i1.49 | Abstract, Auszug |
| S7 | Murphy, Scott: „The Major Tritone Progression in Recent Hollywood Science Fiction Films“. *MTO* 12.2 (2006) | Abstract, Tabellen |
| S8 | Murphy, Scott: „Scoring Loss in Some Recent Popular Film and Television“. *Music Theory Spectrum* 36.2 (2014), 295–314, DOI 10.1093/mts/mtu014 | Abstract, Auszug |
| S9 | Patrick, Morgan: „The Fantasy Fifth“. *Intégral* 36 (2023) | eingesehen (Definitionsteil) |
| S10 | Richards, Mark: Kursübersichten *Action-Music Harmony* 1–4 und Oktatonik-Lektionen, filmmusicnotes.com | nur Gliederungen |
| S11 | Richards, Mark: Themenanalysen auf filmmusicnotes.com (Force, Imperial March, Emperor, Superman, Hedwig, Jurassic Park) | Auszüge |
| S12 | Pearson Edexcel: *John Williams, E.T.: Flying Theme* (A-Level Set Work 45) | eingesehen |
| S13 | *Star Wars Music Minute*, „ESB 6: Battle of Hoth Set Theory“ | Episodenindex |
| S16 | Audissino, Emilio: *The Film Music of John Williams*. University of Wisconsin Press 2021 | bibliografisch |
| S17 | Bribitzer-Stull, Matthew: *Understanding the Leitmotif*. Cambridge University Press 2015 | bibliografisch |
| S18 | Richards, Mark: „Film Music Themes: Analysis and Corpus Study“. *MTO* 22.1 (2016) | Abstract |
| S19 | Cohn, Richard: „Uncanny Resemblances“ (2004); *Audacious Euphony* (2012) | bibliografisch |
| S20 | Movie Music UK, Filmtracks: Rezensionen | eingesehen |
| S21 | Berklee Online: „How John Williams’s Star Wars Scores Defined the Sound of Modern Cinema“ | Auszug |
| S22 | Amblard, Jacques: „Survey of works by John Williams“, IRCAM | Auszug |
| S24 | Lehman, Frank: *Complete Catalogue of the Musical Themes of Star Wars*, Stand 19.06.2023 | eingesehen (zweiter Durchgang) |
| S25 | Lehman, Frank: „Music Theory through the Lens of Film“. *Journal of Film Music* 5.1–2 (2012/13), 177–196, DOI 10.1558/jfm.v5i1-2.177 | eingesehen |
| S26 | Normandie, Robert: *John Williams and His Music for E.T.: The Extra-Terrestrial*, jwfan.com 2021 (studentische Arbeit) | eingesehen |
| S27 | Arthur, Claire / Lehman, Frank / McNamara, John: Star Wars Thematic Corpus (SWTC), *Empirical Musicology Review*, arXiv:2309.03298 | eingesehen |
| S28 | Schneller, Tom: „Day of Wrath“. *Émergences* 2 (2025), DOI 10.35562/emergences.378 | teilweise eingesehen |
| S29 | Schneller, Tom: „Sweet Fulfillment: Allusion and Teleological Genesis in John Williams’s Close Encounters of the Third Kind“. *Musical Quarterly* 97.1 (2014), 98–131, DOI 10.1093/musqtl/gdu001 | Auszüge |
| S30 | Richards, Mark: Beiträge auf filmmusicnotes.com (Hemiole Poe/Heroics); „The Use of Variation in John Williams’s Film Music Themes“, in Audissino (Hg.), *John Williams: Music for Films, Television and the Concert Stage*, Brepols 2018 | Auszug bzw. über Zitat |
| S31 | Tripp: „The British Invasion“. *Émergences* 1 (2025), DOI 10.35562/emergences.128 | teilweise |
| S32 | Lehman, Frank: „Remembering Petticoat Lane, Revisited“. *Émergences* 2 (2025), DOI 10.35562/emergences.297 | Anfang |
| S33 | Zacharopoulos, Konstantinos: „Musical Syntax in John Williams’s Film Music Themes“, in *Contemporary Film Music*, Palgrave 2017, 237–262 | Abstract |
| S34 | The Legacy of John Williams: „Jaws at 45“ (2020) | Publikumsquelle |
| S35 | Sewell, Dominic: Forenbeitrag (VI-Control) zu Snow Battle und Set 5-32 | sekundär |
| S15 | Rossi, Jérôme: „Le dynamisme harmonique dans l’écriture filmique de John Williams“ (2011) | bibliografisch, Abruf blockiert |
| S23 | McCauley, David (2018): Analyse zu „Desert Chase“ (Verweis in S2) | nicht ermittelt |
