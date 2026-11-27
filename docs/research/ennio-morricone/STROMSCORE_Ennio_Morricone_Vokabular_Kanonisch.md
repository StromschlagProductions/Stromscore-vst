# STROMSCORE – Ennio Morricone: Kanonisches musikalisches Vokabular (Phase 2)

Stand: 27.11.2026 · Modus SCORE (mit SYNTH-Hinweisen) · Zeitbasis 960 PPQ · alle Vorlagen mit Präfix EM

## 0. Grundlagen, Konventionen und Grenzen

**Forschungsgrundlage (alle drei gemeinsam berücksichtigt):** STROMSCORE_Ennio_Morricone_Tiefenrecherche.md (Prinzipien: Mikrozelle, immobilità dinamica, partitura multipla, doppelte Ästhetik), STROMSCORE_Ennio_Morricone_Nachtrag_Lolita_Lyrik.md (Moll-add9, Plagal-Terzkette, None als Gemeinsamton, aufgeschobene Auflösung), STROMSCORE_Ennio_Morricone_Tiefenrecherche_Vertiefung.md (Zellen-Datentyp, Modulkombinatorik, Polyperiodik, Gewicht statt Dichte, gelenkte Ereignisfelder). Keine neue Quellenrecherche.

**Was diese Bibliothek ist:** ein eigenständiges, algorithmisch implementierbares Vokabular, das Morricones *werkübergreifend belegte Verfahren* in neue musikalische Konstruktionen übersetzt. Keine Vorlage kopiert oder rekonstruiert ein bekanntes Thema. **Konkrete Akkordfolgen aus *Lolita* oder *Love in the Morning* sind weiterhin nicht belegt und werden nirgends behauptet;** die lyrische Säule leitet sich aus der in den Berichten dokumentierten Grammatik ab (Taggs Moll-add9, Plagal-Terzkette, dorische Dur-IV, None als Bindeton, gestaffelte Einsätze laut Lyne). Studie EM-S052 trägt ausdrücklich den Zusatz „kein Lolita-Zitat“.

**Hörprüfung:** Es hat **keine** Hörprüfung stattgefunden. Alle Qualitätsaussagen in diesem Dokument und in EM_Qualitaetspruefung.md sind maschinelle Prüfungen der Daten (siehe dort).

**Konventionen**
- Relative Tonhöhen: 0 = Tonzentrum (Tonika) in Oktave 3, 12 = Tonika eine Oktave höher, negative Werte darunter. Beim Rendern der Studien: MIDI = Zentrum + relativ, Zentrum = 48 + Tonika (Tonika E…H) bzw. 60 + Tonika (Tonika C…E♭).
- Tonnamen: deutsche Bezeichnung **H** für B♮; B♭ wird immer mit Vorzeichen geschrieben; Vorzeichen als ♯ und ♭. Die Schreibweise in den Daten ist enharmonisch vereinfacht (z. B. E♭ statt D♯).
- Stufen über dem Tonzentrum: 1, ♭2, 2, ♭3, 3, 4, ♯4/♭5, 5, ♭6, 6, ♭7, 7. Intervallrollen im Akkord: 1, ♭9, 9, ♭3, 3, 4/11, ♯11/♭5, 5, ♭6/♭13, 6/13, ♭7, 7.
- Takt 4/4 = 3840 Ticks, Viertel = 960, Achtel = 480, Sechzehntel = 240, Achteltriole = 320.
- Rollen: LF Lange Fläche · KF Kurze Fläche · LB Langer Bass · KB Kurzer Bass · AR Arpeggio/Sequencer · TU Tupfer (harmonisch nutzbar) · ST Stich (MIDI-Note 36, nie transponiert, ohne Tonhöhenfunktion) · GS Gegenstimme (optional) · HM Hauptmelodie (optional). Keine neuen Rollen, Ausgänge, GUI-Regler oder verpflichtende CC-Steuerung.
- Rollenregister sind Präferenzen (Prüfbereiche: LF 43–86, KF 28–90, LB 24–55, KB 24–60, AR 48–93, TU 40–100, GS 50–88, HM 57–96), keine starren Regeln.
- Ametrische Ereignisse werden als unregelmäßige musikalische Zeitpositionen im Tickraster ausgedrückt (kein Millisekunden-Scheduler).

**Evidenzkennzeichnung:** N – nachvollziehbar nachgewiesenes Verfahren · I – begründete musikalische Interpretation · H – plausible, nicht ausreichend belegte Hypothese · E – eigenständige algorithmische Gestaltung. Die Kennzeichnung einer Vorlage bezieht sich auf das zugrunde liegende *Verfahren*; jede konkrete Vorlage ist eine eigenständige Konstruktion. Verfahren aus Morricones Konzertmusik (*Ut*, *Suoni per Dino*, Drittes Konzert, *Vuoto d'anima piena*, Missa) werden als solche benannt und nicht automatisch als typische Filmmusikverfahren deklariert.

## 1. Musiktheoretische Korrekturen

Korrekturen des Lolita-Nachtrags (vom Anwender vorgegeben, geprüft und übernommen):
- A–C–E–H ist **Am(add9)**, nicht Am9 (Am9 enthält zusätzlich G). Entsprechend ist G–H–D–A **G(add9)**, nicht G9. In dieser Bibliothek heißen die Qualitäten `madd9` bzw. `add9`; `m9`/`9` bezeichnen nur Klänge mit kleiner Septime.
- H über D-Moll ist die **große Sexte** (13), nicht eine ♯11 oder None.
- Ein liegendes C beim Wechsel Am → A bleibt **kleine Terz**, also bewusst akkordfremde Färbung (F) gegen A-Dur; die große Terz entsteht erst durch C♯. Die Fortsetzungstabelle des Nachtrags („C → Wechsel zur großen Terz“) war in dieser Formulierung ungenau.
- Akkorderweiterungen (add9, 6, maj7, ♯11) sind **nicht** pauschal auflösungspflichtig. add9 ist Akkordton (Funktion A), außer eine Vorlage deklariert ausdrücklich einen Vorhalt (Funktion V mit Ziel), z. B. EM-U035.

Weitere eigenständig geprüfte Punkte:
- Die Soundfly-Beschreibung „Am9 → G9“ (Lolita-Nachtrag 4.2) betrifft nach den angegebenen Tönen (A C E H / G H D A) tatsächlich **Am(add9) → G(add9)**; die Gemeinsamtöne A und H bleiben gültig.
- Die Nummer des von De Palma gewählten Triumphthemas ist widersprüchlich belegt (Variante sechs vs. sieben); keine Vorlage stützt sich darauf.
- Die Vertiefung schlug „maximal zwei gleichzeitig aktive Zellen“ und „höchstens zwei thematische Schichten“ vor; diese globalen Grenzen werden gemäß Auftrag **nicht** übernommen. Entscheidend ist die geprüfte Verträglichkeit (Abschnitt 13).
- Die Vertiefung schlug eine Mindeststillequote und eine obligatorische Ankerschicht für Ereignisfelder vor; beide werden **nicht** global übernommen. EF-Vorlagen definieren Dichten und Mindestabstände einzeln; Anker sind optional.

## 2. Datenmodell und algorithmische Voraussetzungen

Dokumentation, Ereignisdaten (EM_Studien_Ereignisse.csv) und MIDI-Studien (EM_Studien_MIDI.zip) entstehen aus **einem** strukturierten Datenmodell (Python-Spezifikationen → Realisierung → Rendern → Prüfung). Die folgenden Fähigkeiten werden von den Vorlagen vorausgesetzt. Sie werden **nicht** als in STROMSCORE vorhanden angenommen; Status „neu“ heißt: muss im gemeinsamen Kern ergänzt werden (keine zweite Engine).

| Fähigkeit | Wofür | Status |
|---|---|---|
| Explizite Tonvorräte und Akkordqualitäten inkl. madd9, add9, m6, m7b5, mmaj7, maj7♯11, 7♭9, Klangobjekte (Mengen ohne Grundtonqualität) | H, U | laut Anwender teils geplant; Qualitätenliste erweitern |
| Stimmführungs-Solver mit Gemeinsamton-Priorität, Haltewünschen, Vermeidung von Parallelen und Lagenstil (eng/weit/Reibung eng/offen) | H, U, S | neu als Übergangsabsicht der bestehenden Stimmführung |
| Übergangsabsichten (Halten bestimmter Töne, Vorhalt mit Ziel und Verzögerung, ausbleibende Auflösung, gestaffelte Einsätze) | U | neu |
| Tonfunktionen A/T/V/F/U je Ton und je harmonischem Segment (auch während langer Noten) | alle | bestehend (A/T/V/F/U), Segmentauswertung neu |
| Schichtbezogene Harmonie (lokal) neben globaler Harmonie; geschützte Konsonanz | H (AB), S | neu |
| Pedal und dissonanzautorisierter Bass als eigene Basstypen | B, H | Pedal geplant; Typ DIS neu |
| Zellen-Datentyp (Menge/Klasse/Ordnung/Rhythmus/Kern+Austausch) mit Permutator, Oktavierung, Austauschton | C, M, K, EF | neu |
| Unabhängige Periodenlängen je Rolle (Polyperiodik), Gesamtzyklusberechnung | R, B, K | geplant (unabhängige rhythmische Perioden) |
| Additive Motiventhüllung / Verkürzung über Durchläufe | M, P, T | neu |
| Modulpool mit Längen-, Register-, Zell- und Harmoniemetadaten, Kompatibilitätsprüfung, Wechsel an Modulgrenzen | K | neu (Schichtrotation geplant) |
| Ereignisfeld-Gesprächsmodus (Antwortfenster, Imitation/Widerspruch/Schweigen), Mindestabstände, Dichtebereiche | EF | Ereignisfeld geplant; Gesprächsmodus neu |
| Gleichtonhygiene: frühere Note endet beim Neuanschlag derselben Tonhöhe in derselben Rolle | Rendern | neu (in den Studien angewandt) |

## 3. Harmonische Absicht

- **A** Akkordton der lokalen Harmonie (inkl. deklarierter Erweiterungen wie 9 in add9, 6 in m6, 7 in maj7).
- **T** zulässiger Tonvorratston (im Modus, nicht im Akkord).
- **V** Vorhalt/Durchgang mit konkretem Auflösungsziel (Ziel-Tonhöhe und Zeitpunkt sind Teil der Vorlage; geprüft).
- **F** bewusst akkordfremder Ton (deklariert, z. B. Farbton einer KERN-Zelle, Ereignisfeldton außerhalb der Harmonie).
- **U** bewusst unaufgelöste Dissonanz (dissonanzautorisierte Schichten, Pedale gegen die Oberharmonik, Klangobjekte).

**Lokal vs. global.** Jede Schicht kann eine eigene lokale Harmonie tragen. Die globale Harmonie ist die der tragenden LF/LB-Schicht. Eine Schicht mit **geschützter Konsonanz** (Kennung K) wird gegen ihre *eigene* lokale Harmonie geprüft und muss dort A/T sein; gegen die globale Harmonie darf sie F/U erzeugen, ohne ihre Identität zu verlieren (doppelte Ästhetik). Dissonante Schichten tragen die Kennung D.

**Lange Noten.** Für jede Note wird die Funktion in jedem harmonischen Segment berechnet, das sie überspannt (CSV-Spalte `funktionsfolge`, z. B. A→T→A). Pedale dürfen dabei zu U werden; ein Wechsel A→F ohne Deklaration wird als Fehler gemeldet.

**Konsonanz/Dissonanz** wird nicht anhand einer globalen Skala beurteilt, sondern gegen den lokalen Akkord (Intervallklassen 1, 2, 6, 10, 11 gelten als dissonant gegen einen Akkordton).

## 4. XYZ-Modell

Jede Vorlage hat einen XYZ-Anker und einen Gültigkeitsbereich (Standard: Anker ±0,20; „beliebig“ = färbungs- bzw. dimensionsunabhängig, musikalisch begründet bei Rhythmus-, Bass- und Modulvorlagen).

**X – harmonische Färbung (dunkel → hell)** wird *nicht* allein durch Register, Dur/Moll oder Dissonanz bestimmt, sondern durch das Zusammenspiel von: Modus (phrygisch → äolisch → dorisch → mixolydisch/ionisch → lydisch), Akkordqualität (m7b5/dim → madd9 → m6/dorische IV → add9/6/9 → maj7♯11), Lage der Reibung (eng = dunkler, offen = kühler/heller), Position der None/Sexte (Bindeton oben = heller), Bassverzicht (heller, schwebend) und Grad der Auflösungsverweigerung. Hell bedeutet nicht fröhlich: helle Vorlagen tragen fast immer eine Mollterz-Berührung, eine lydische Fremdheit oder einen offenen Schluss.

**Y – Intensität (zurückhaltend → kraftvoll)** wird *nicht* allein durch Schichtzahl und Velocity bestimmt, sondern durch: Gewicht (Register, Oktavdopplung im Bass), Klangbreite (eng → weit), Dauer der Oberstimme (lange Werte = kraftvoll ohne Hektik), Kraft der Bassfunktion (Pedal → Quintfall → Gewichtsfigur), Akzentdichte statt Notendichte, und Monumentalität der Harmoniefolge (Tonikapedal, äolische Rotation). Kraftvoll heißt nicht hektisch: die Studien EM-S007, EM-S015, EM-S048 erreichen hohes Y ohne höhere Notendichte in der Oberstimme.

**Z – Unruhe (stabil → unruhig)** wird *nicht* allein durch Notendichte oder Permutationsrate bestimmt, sondern durch: Auflösungsverweigerung (Vorhalte bleiben stehen), Periodeninkongruenz (3 gegen 4, 5 gegen 4), Akzentverschiebung, Unregelmäßigkeit der Abstände (Variationskoeffizient der Einsatzabstände), Anteil dissonanter Schichten, Antwortlogik (Widerspruch statt Zustimmung) und Stille als Erwartungsbruch.

**Mechanische vs. psychologische Unruhe.** Mechanisch = regelmäßiger, dichter Puls mit verschobenen Akzenten oder inkongruenten Perioden (z. B. EM-R048, EM-R035, EM-B036, EM-S039). Psychologisch = geringe Dichte, unregelmäßige Abstände, ausbleibende Antworten, unaufgelöste Vorhalte (z. B. EM-R049, EM-R045, EM-EF05, EM-S038). Die Zuordnung der R-Vorlagen ab Z ≥ 0,5 wird maschinell aus Dichte und Regelmäßigkeit berechnet (Spalte „Unruhe-Typ“).

**Die acht Eckbereiche (nächstgelegene Vorlagen und Studien, maschinell nach Abstand ermittelt):**

| Ecke | Charakter | Harmonik/Übergänge | Studien |
|---|---|---|---|
| 0 / 0 / 0 | dunkel · zurückhaltend · stabil (latente Bedrohung / dunkle Ruhe) | EM-H106, EM-H088, EM-U049, EM-H001, EM-H006 | EM-S053, EM-S027, EM-EF09, EM-EF11 |
| 0 / 0 / 1 | dunkel · zurückhaltend · unruhig (Paranoia bei geringer Dichte) | EM-H108, EM-H080, EM-H107, EM-H110, EM-H113 | EM-S038, EM-S011, EM-EF08, EM-EF05 |
| 0 / 1 / 0 | dunkel · kraftvoll · stabil (tragische Monumentalität) | EM-H111, EM-H045, EM-H042, EM-H041, EM-H044 | EM-S054, EM-S007, EM-S045, EM-S015 |
| 0 / 1 / 1 | dunkel · kraftvoll · unruhig (bedrohliche Action / akuter Horror) | EM-H112, EM-H085, EM-H110, EM-H114, EM-H105 | EM-S040, EM-EF15, EM-EF13, EM-S010 |
| 1 / 0 / 0 | hell · zurückhaltend · stabil (kalte Klarheit / zarte Helle) | EM-H021, EM-H026, EM-H020, EM-U041, EM-H028 | EM-S032, EM-S046, EM-S005, EM-S026 |
| 1 / 0 / 1 | hell · zurückhaltend · unruhig (kalte Mystery, unheimliche Schönheit) | EM-H115, EM-H093, EM-H116, EM-H113, EM-H103 | EM-S055, EM-S041, EM-S009, EM-EF06 |
| 1 / 1 / 0 | hell · kraftvoll · stabil (erhabene, lyrische Kraft) | EM-H117, EM-H118, EM-H047, EM-H043, EM-H100 | EM-S056, EM-S048, EM-S019, EM-S007 |
| 1 / 1 / 1 | hell · kraftvoll · unruhig (gleißende Unruhe, mechanische Unruhe hell) | EM-H119, EM-H114, EM-H116, EM-H118, EM-H069 | EM-S057, EM-S047, EM-EF13, EM-S010 |

Übergangsbereiche: die vollständige 3×3×3-Abdeckung (Werte 0 / 0,5 / 1) mit Vorlagenzahlen je Kategorie steht in EM_Qualitaetspruefung.md, Abschnitt XYZ.

**Besonders wichtige Charaktere → Einstieg in die Bibliothek**

| Charakter | Vorlagen | Studien |
|---|---|---|
| Dunkle, zurückhaltende, stabile Bedrohung | EM-H088, EM-H077, EM-H106, EM-B004, EM-B052, EM-R002 | EM-S053, EM-S038, EM-S013 |
| Kalte, helle Mystery | EM-H103, EM-H098, EM-H071, EM-H115, EM-C020, EM-R026 | EM-S012, EM-S047, EM-S032, EM-S055 |
| Melancholische Schönheit | EM-H004, EM-H051, EM-U001, EM-U029, EM-C009 | EM-S001, EM-S002, EM-S020, EM-S052 |
| Schönheit und Bedrohung gleichzeitig | EM-H091, EM-H094, EM-H096, EM-U048, EM-EF04 | EM-S008, EM-S024, EM-S009, EM-S050 |
| Psychologische Unruhe bei geringer Dichte | EM-R049, EM-R045, EM-EF05, EM-U039 | EM-S038, EM-EF05 |
| Mechanische Unruhe | EM-R048, EM-R035, EM-B036, EM-C044, EM-H114, EM-H119 | EM-S039, EM-S057 |
| Kraftvolle Musik ohne Hektik | EM-R013, EM-R014, EM-B030, EM-B031, EM-M045 | EM-S015, EM-S023, EM-S048 |
| Tragische Monumentalität | EM-H041, EM-H044, EM-H045, EM-H111, EM-H117, EM-B034, EM-M014 | EM-S007, EM-S045, EM-S054, EM-S056 |
| Bedrohliche Action | EM-B032, EM-B014, EM-R021, EM-R053, EM-H079, EM-H112 | EM-S042, EM-S015 |
| Experimenteller Horror | EM-H085, EM-H090, EM-EF13, EM-EF15, EM-C021 | EM-S010, EM-S040, EM-S014 |

## 5. Zwei gleichwertige Säulen

Säule **A – Lyrik und emotionale Harmonik**, Säule **B – Experiment, Spannung und Horror**, Verbindung **AB – Schönheit und Bedrohung gleichzeitig**. Es gibt keinen Säulen-Schalter: die Säule ergibt sich aus XYZ-Position und Vorlagenwahl; AB-Vorlagen koppeln eine geschützte konsonante Schicht (K) mit einer dissonanten Schicht (D).

| Kategorie | A | AB | B |
|---|---|---|---|
| H | 67 | 19 | 33 |
| U | 47 | 0 | 3 |
| R | 12 | 16 | 36 |
| B | 18 | 6 | 28 |
| C | 20 | 7 | 19 |
| M | 32 | 11 | 7 |
| P | 14 | 6 | 2 |
| EF | 4 | 5 | 7 |
| S | 30 | 12 | 15 |

Rhythmus- und Bassvorlagen sind naturgemäß häufiger der Spannungssäule zugeordnet; die lyrische Säule wird in H (lyrische Harmonik), U (Übergänge), M (Melodik), P (Phrasen) und S (Studien) mindestens gleich stark versorgt. Viele Rhythmen sind färbungsunabhängig (X beliebig) und dienen beiden Säulen.

## 6. H – Harmonik

Je Vorlage: Akkordfolge mit realisierten Stimmen (Oberstimmen LF, Bass LB, relativ zum Tonzentrum), Einsatz-Tick, Dauer, Intervallrolle jeder Oberstimme im Akkord, Bassfunktion, Reibungslage bei Moll-add9-Klängen sowie die Übergänge zwischen aufeinanderfolgenden Klängen (Gemeinsamtöne, gehaltene Töne, Bewegungen, Bass). Alle Oberstimmen sind Funktion A (Erweiterungen sind deklarierte Akkordtöne). Zyklus = Summe der Dauern; die Vorlage wiederholt sich ohne erzwungene Veränderung.

### EM-H001 – Moll-add9-Stasis, Reibung eng
- **Charakter:** intim schmerzend, stehend · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,30 / 0,20 / 0,20 · **Gültigkeit:** X 0,10–0,50 · Y 0,00–0,40 · Z 0,00–0,40
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** crunch
- **Progression (Notation):** `0:madd9*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | [1] Moll-add9 | -12 | [+2, +3, +7, +12] | 9, ♭3, 5, 1 | A | eng (Halbton) |

- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Reibungslage crunch; Lage (Stil crunch) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C025, EM-C027, EM-C032, EM-C039, EM-C045
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten madd9; Stimmführungs-Solver mit Gemeinsamton-Priorität; Lagenregel crunch
- **Evidenz:** N – nachgewiesenes Verfahren (Tagg: madd9, Halbton 2–♭3); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H002 – Moll-add9-Stasis, Reibung offen
- **Charakter:** kühl-schwebende Trauer · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,50 / 0,20 / 0,10 · **Gültigkeit:** X 0,30–0,70 · Y 0,00–0,40 · Z 0,00–0,30
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** offen
- **Progression (Notation):** `0:madd9*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |

- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Reibungslage offen; Lage (Stil offen) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C003, EM-C011, EM-C026, EM-C028, EM-C042
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten madd9; Stimmführungs-Solver mit Gemeinsamton-Priorität; Lagenregel offen
- **Evidenz:** N – nachgewiesenes Verfahren (Tagg: madd9; Lagenregel E); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H003 – Moll-add9 mit Terzumkehrung
- **Charakter:** leicht schwankend, verletzlich · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,35 / 0,25 / 0,30 · **Gültigkeit:** X 0,15–0,55 · Y 0,05–0,45 · Z 0,10–0,50
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** crunch
- **Progression (Notation):** `0:madd9*2 | 0:madd9/3*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-add9 | -12 | [+2, +3, +7, +12] | 9, ♭3, 5, 1 | A | eng (Halbton) |
| 2 | 7680 | 7680 | [1] Moll-add9 / Bass [♭3] | -9 | [+2, +3, +7, +12] | 9, ♭3, 5, 1 | A | eng (Halbton) |

- **Übergänge:** 1→2: gemeinsam {1, 2, ♭3, 5}; gehalten +2, +3, +7, +12; bewegt keine; Bass +3
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Reibungslage crunch; Lage (Stil crunch) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C001, EM-C008, EM-C009, EM-C025, EM-C027
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten madd9; Stimmführungs-Solver mit Gemeinsamton-Priorität; Lagenregel crunch
- **Evidenz:** N – nachgewiesenes Verfahren (Tagg; Umkehrung E); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H004 – Moll-add9 – ♭VI-maj7 – iv-add9 – Rückkehr
- **Charakter:** wehmütige Kreisbewegung · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,40 / 0,35 / 0,20 · **Gültigkeit:** X 0,20–0,60 · Y 0,15–0,55 · Z 0,00–0,40
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** offen
- **Progression (Notation):** `0:madd9*2 | 8:maj7*2 | 5:madd9*2 | 0:madd9*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 7680 | 7680 | [♭6] große Septime | -16 | [-5, +3, +12, +15] | 7, 5, 3, 5 | A | – |
| 3 | 15360 | 7680 | [4] Moll-add9 | -19 | [-4, +7, +12, +17] | ♭3, 9, 5, 1 | A | offen (gr. Septime/kl. None) |
| 4 | 23040 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |

- **Übergänge:** 1→2: gemeinsam {1, ♭3, 5}; gehalten -5, +12, +15; bewegt St2 +2→+3 (+1); Bass -4 · 2→3: gemeinsam {1, 5, ♭6}; gehalten +12; bewegt St1 -5→-4 (+1), St2 +3→+7 (+4), St4 +15→+17 (+2); Bass -3 · 3→4: gemeinsam {1, 5}; gehalten +12; bewegt St1 -4→-5 (-1), St2 +7→+2 (-5), St4 +17→+15 (-2); Bass +7
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Reibungslage offen; Lage (Stil offen) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C010, EM-C013, EM-C030, EM-C043, EM-C042
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten madd9, maj7; Stimmführungs-Solver mit Gemeinsamton-Priorität; Lagenregel offen
- **Evidenz:** I – begründete Interpretation (madd9 + plagale Moll-Bewegung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H005 – Fallende Moll-add9-Kette
- **Charakter:** sinkende Sehnsucht · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,35 / 0,40 / 0,30 · **Gültigkeit:** X 0,15–0,55 · Y 0,20–0,60 · Z 0,10–0,50
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:madd9*2 | 10:add9*2 | 8:add9*2 | 7:m7*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 7680 | 7680 | [♭7] Dur-add9 | -14 | [-7, +2, +12, +14] | 5, 3, 9, 3 | A | – |
| 3 | 15360 | 7680 | [♭6] Dur-add9 | -16 | [-2, +0, +12, +15] | 9, 3, 3, 5 | A | – |
| 4 | 23040 | 7680 | [5] Moll-Sept | -17 | [-2, +2, +10, +17] | ♭3, 5, ♭3, ♭7 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, 2}; gehalten +2, +12; bewegt St1 -5→-7 (-2), St4 +15→+14 (-1); Bass -2 · 2→3: gemeinsam {1, ♭7}; gehalten +12; bewegt St1 -7→-2 (+5), St2 +2→+0 (-2), St4 +14→+15 (+1); Bass -2 · 3→4: gemeinsam {♭7}; gehalten -2; bewegt St2 +0→+2 (+2), St3 +12→+10 (-2), St4 +15→+17 (+2); Bass -1
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C001, EM-C008, EM-C009, EM-C025, EM-C027
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, m7, madd9; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** I – begründete Interpretation (stufenweise fallende Mollharmonik); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H006 – Moll-Plagalpendel mit add9
- **Charakter:** Trauer ohne Ziel · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,25 / 0,30 / 0,15 · **Gültigkeit:** X 0,05–0,45 · Y 0,10–0,50 · Z 0,00–0,35
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** crunch
- **Progression (Notation):** `0:madd9*2 | 5:madd9*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-add9 | -12 | [+2, +3, +7, +12] | 9, ♭3, 5, 1 | A | eng (Halbton) |
| 2 | 7680 | 7680 | [4] Moll-add9 | -7 | [+0, +5, +7, +8] | 5, 1, 9, ♭3 | A | eng (Halbton) |

- **Übergänge:** 1→2: gemeinsam {1, 5}; gehalten +7; bewegt St1 +2→+0 (-2), St2 +3→+5 (+2), St4 +12→+8 (-4); Bass +5
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Reibungslage crunch; Lage (Stil crunch) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C025, EM-C027, EM-C032, EM-C039, EM-C045
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten madd9; Stimmführungs-Solver mit Gemeinsamton-Priorität; Lagenregel crunch
- **Evidenz:** I – begründete Interpretation (plagale Bewegung, madd9); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H007 – Dorisches Dur-IV-Pendel mit add9
- **Charakter:** herbe Hoffnung · **Säule:** A · **Modus/Tonvorrat:** dorisch {1, 2, ♭3, 4, 5, 6, ♭7}
- **XYZ-Anker:** 0,55 / 0,35 / 0,20 · **Gültigkeit:** X 0,35–0,75 · Y 0,15–0,55 · Z 0,00–0,40
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** offen
- **Progression (Notation):** `0:madd9*2 | 5:add9*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 7680 | 7680 | [4] Dur-add9 | -7 | [-5, +0, +9, +17] | 9, 5, 3, 1 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, 5}; gehalten -5; bewegt St2 +2→+0 (-2), St3 +12→+9 (-3), St4 +15→+17 (+2); Bass +5
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Reibungslage offen; Lage (Stil offen) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C002, EM-C007, EM-C012, EM-C040, EM-C003
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C017, EM-C035) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, madd9; Stimmführungs-Solver mit Gemeinsamton-Priorität; Lagenregel offen
- **Evidenz:** N – nachgewiesenes Verfahren (i–IV–i (filmmusicnotes: Cheyenne, GBU)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H008 – Dorisch mit ♭VII-Ausweichung
- **Charakter:** erzählend, offen · **Säule:** A · **Modus/Tonvorrat:** dorisch {1, 2, ♭3, 4, 5, 6, ♭7}
- **XYZ-Anker:** 0,55 / 0,40 / 0,25 · **Gültigkeit:** X 0,35–0,75 · Y 0,20–0,60 · Z 0,05–0,45
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** None
- **Progression (Notation):** `0:min*1 | 5:maj*1 | 0:madd9*1 | 10:add9*1`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 3840 | [1] Moll | -12 | [+0, +3, +7, +12] | 1, ♭3, 5, 1 | A | – |
| 2 | 3840 | 3840 | [4] Dur | -7 | [+0, +5, +9, +12] | 5, 1, 3, 5 | A | – |
| 3 | 7680 | 3840 | [1] Moll-add9 | -12 | [+0, +3, +7, +14] | 1, ♭3, 5, 9 | A | offen (gr. Septime/kl. None) |
| 4 | 11520 | 3840 | [♭7] Dur-add9 | -14 | [+0, +2, +5, +14] | 9, 3, 5, 3 | A | – |

- **Übergänge:** 1→2: gemeinsam {1}; gehalten +0, +12; bewegt St2 +3→+5 (+2), St3 +7→+9 (+2); Bass +5 · 2→3: gemeinsam {1}; gehalten +0; bewegt St2 +5→+3 (-2), St3 +9→+7 (-2), St4 +12→+14 (+2); Bass -5 · 3→4: gemeinsam {1, 2}; gehalten +0, +14; bewegt St2 +3→+2 (-1), St3 +7→+5 (-2); Bass -2
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C002, EM-C007, EM-C012, EM-C040, EM-C003
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C017, EM-C035) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, madd9, maj, min; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** I – begründete Interpretation (dorische Dur-IV + ♭VII); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H009 – Moll-add9 über ♭III-maj7 zur Subdominante
- **Charakter:** sanft aufhellend, dann zurücksinkend · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,50 / 0,30 / 0,20 · **Gültigkeit:** X 0,30–0,70 · Y 0,10–0,50 · Z 0,00–0,40
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:madd9*2 | 3:maj7*2 | 5:m7*2 | 0:madd9*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 7680 | 7680 | [♭3] große Septime | -9 | [-5, +2, +10, +15] | 3, 7, 5, 1 | A | – |
| 3 | 15360 | 7680 | [4] Moll-Sept | -7 | [-4, +5, +12, +15] | ♭3, 1, 5, ♭7 | A | – |
| 4 | 23040 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |

- **Übergänge:** 1→2: gemeinsam {2, ♭3, 5}; gehalten -5, +2, +15; bewegt St3 +12→+10 (-2); Bass +3 · 2→3: gemeinsam {♭3}; gehalten +15; bewegt St1 -5→-4 (+1), St2 +2→+5 (+3), St3 +10→+12 (+2); Bass +2 · 3→4: gemeinsam {1, ♭3}; gehalten +12, +15; bewegt St1 -4→-5 (-1), St2 +5→+2 (-3); Bass -5
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C003, EM-C011, EM-C026, EM-C028, EM-C042
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten m7, madd9, maj7; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** I – begründete Interpretation (Terzverwandtschaft diatonisch); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H010 – Moll-add9 – ♭VI-add9 – ♭III-add9 – ♭VII-sus2
- **Charakter:** weite, schwebende Landschaft · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,55 / 0,50 / 0,20 · **Gültigkeit:** X 0,35–0,75 · Y 0,30–0,70 · Z 0,00–0,40
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:madd9*2 | 8:add9*2 | 3:add9*2 | 10:sus2*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 7680 | 7680 | [♭6] Dur-add9 | -16 | [-2, +3, +12, +15] | 9, 5, 3, 5 | A | – |
| 3 | 15360 | 7680 | [♭3] Dur-add9 | -21 | [-2, +3, +7, +17] | 5, 1, 3, 9 | A | – |
| 4 | 23040 | 7680 | [♭7] sus2 | -14 | [-2, +0, +5, +17] | 1, 9, 5, 5 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, ♭3}; gehalten +12, +15; bewegt St1 -5→-2 (+3), St2 +2→+3 (+1); Bass -4 · 2→3: gemeinsam {♭3, ♭7}; gehalten -2, +3; bewegt St3 +12→+7 (-5), St4 +15→+17 (+2); Bass -5 · 3→4: gemeinsam {4, ♭7}; gehalten -2, +17; bewegt St2 +3→+0 (-3), St3 +7→+5 (-2); Bass +7
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C002, EM-C007, EM-C012, EM-C040, EM-C003
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, madd9, sus2; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (add9-Farben ohne Kadenz); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H011 – Halbverminderter Weg zum offenen Halbschluss
- **Charakter:** bange Erwartung · **Säule:** A · **Modus/Tonvorrat:** harm_moll {1, 2, ♭3, 4, 5, ♭6, 7}
- **XYZ-Anker:** 0,25 / 0,40 / 0,45 · **Gültigkeit:** X 0,05–0,45 · Y 0,20–0,60 · Z 0,25–0,65
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:madd9*2 | 2:m7b5*2 | 7:7sus4*2 | 7:7*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 7680 | 7680 | [2] halbvermindert | -10 | [-4, +2, +12, +17] | ♯11/♭5, 1, ♭7, ♭3 | A | – |
| 3 | 15360 | 7680 | [5] Sept-sus4 | -17 | [-5, +2, +12, +17] | 1, 5, 4/11, ♭7 | A | – |
| 4 | 23040 | 7680 | [5] Dominantsept | -17 | [-5, +2, +11, +17] | 1, 5, 3, ♭7 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, 2}; gehalten +2, +12; bewegt St1 -5→-4 (+1), St4 +15→+17 (+2); Bass +2 · 2→3: gemeinsam {1, 2, 4}; gehalten +2, +12, +17; bewegt St1 -4→-5 (-1); Bass -7 · 3→4: gemeinsam {2, 4, 5}; gehalten -5, +2, +17; bewegt St3 +12→+11 (-1); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U014, EM-U015, EM-U017; Zellen EM-C027, EM-C032, EM-C039, EM-C045, EM-C001
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten 7, 7sus4, m7b5, madd9; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** N – nachgewiesenes Verfahren (Tagg: halbverminderte Akkorde; Halbschluss); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H012 – Halbvermindert über Tonikapedal
- **Charakter:** Schmerz im Stillstand · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,20 / 0,25 / 0,35 · **Gültigkeit:** X 0,00–0,40 · Y 0,05–0,45 · Z 0,15–0,55
- **Rollen:** LF (Oberstimmen), LB (Bass, Pedal) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:madd9*2 | 2:m7b5/0*2 | 0:madd9*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 7680 | 7680 | [2] halbvermindert / Bass [1] | -12 | [-4, +2, +12, +17] | ♯11/♭5, 1, ♭7, ♭3 | A | – |
| 3 | 15360 | 15360 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |

- **Übergänge:** 1→2: gemeinsam {1, 2}; gehalten +2, +12; bewegt St1 -5→-4 (+1), St4 +15→+17 (+2); Bass +0 · 2→3: gemeinsam {1, 2}; gehalten +2, +12; bewegt St1 -4→-5 (-1), St4 +17→+15 (-2); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass: Pedal (A/U je Segment)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C025, EM-C027, EM-C032, EM-C039, EM-C045
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten m7b5, madd9; Stimmführungs-Solver mit Gemeinsamton-Priorität; Pedalrolle
- **Evidenz:** N – nachgewiesenes Verfahren (Tagg: halbvermindert; Pedal); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H013 – Dorische Moll-6-Subdominante zur Tonika
- **Charakter:** trostlose Wärme · **Säule:** A · **Modus/Tonvorrat:** dorisch {1, 2, ♭3, 4, 5, 6, ♭7}
- **XYZ-Anker:** 0,45 / 0,25 / 0,15 · **Gültigkeit:** X 0,25–0,65 · Y 0,05–0,45 · Z 0,00–0,35
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** None
- **Progression (Notation):** `5:m6*2 | 0:madd9*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [4] Moll-Sexte | -7 | [+0, +5, +8, +14] | 5, 1, ♭3, 6/13 | A | – |
| 2 | 7680 | 7680 | [1] Moll-add9 | -12 | [+0, +3, +7, +14] | 1, ♭3, 5, 9 | A | offen (gr. Septime/kl. None) |

- **Übergänge:** 1→2: gemeinsam {1, 2}; gehalten +0, +14; bewegt St2 +5→+3 (-2), St3 +8→+7 (-1); Bass -5
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U006, EM-U017, EM-U019; Zellen EM-C042, EM-C003, EM-C010, EM-C011, EM-C013
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C017, EM-C035) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten m6, madd9; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** I – begründete Interpretation (plagal, dorische Sexte); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H014 – Äolische Kadenz ♭VI–♭VII–i
- **Charakter:** würdiger Abschluss ohne Dominante · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,40 / 0,55 / 0,15 · **Gültigkeit:** X 0,20–0,60 · Y 0,35–0,75 · Z 0,00–0,35
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** weit
- **Progression (Notation):** `8:maj7*2 | 10:add9*2 | 0:madd9*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [♭6] große Septime | -16 | [-4, +0, +7, +15] | 1, 3, 7, 5 | A | – |
| 2 | 7680 | 7680 | [♭7] Dur-add9 | -14 | [-7, +0, +10, +14] | 5, 9, 1, 3 | A | – |
| 3 | 15360 | 15360 | [1] Moll-add9 | -12 | [-5, +3, +12, +14] | 5, ♭3, 1, 9 | A | offen (gr. Septime/kl. None) |

- **Übergänge:** 1→2: gemeinsam {1}; gehalten +0; bewegt St1 -4→-7 (-3), St3 +7→+10 (+3), St4 +15→+14 (-1); Bass +2 · 2→3: gemeinsam {1, 2}; gehalten +14; bewegt St1 -7→-5 (+2), St2 +0→+3 (+3), St3 +10→+12 (+2); Bass +2
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C010, EM-C013, EM-C030, EM-C043, EM-C042
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, madd9, maj7; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** I – begründete Interpretation (Kadenzvermeidung (Smith)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H015 – Moll-add9 mit Moll-v und ♭VI
- **Charakter:** melancholisch fließend · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,45 / 0,35 / 0,25 · **Gültigkeit:** X 0,25–0,65 · Y 0,15–0,55 · Z 0,05–0,45
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:madd9*2 | 7:m7*2 | 8:maj7*2 | 3:add9*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 7680 | 7680 | [5] Moll-Sept | -17 | [-5, +2, +10, +17] | 1, 5, ♭3, ♭7 | A | – |
| 3 | 15360 | 7680 | [♭6] große Septime | -16 | [-5, +3, +12, +20] | 7, 5, 3, 1 | A | – |
| 4 | 23040 | 7680 | [♭3] Dur-add9 | -21 | [-5, +3, +10, +17] | 3, 1, 5, 9 | A | – |

- **Übergänge:** 1→2: gemeinsam {2, 5}; gehalten -5, +2; bewegt St3 +12→+10 (-2), St4 +15→+17 (+2); Bass -5 · 2→3: gemeinsam {5}; gehalten -5; bewegt St2 +2→+3 (+1), St3 +10→+12 (+2), St4 +17→+20 (+3); Bass +1 · 3→4: gemeinsam {♭3, 5}; gehalten -5, +3; bewegt St3 +12→+10 (-2), St4 +20→+17 (-3); Bass -5
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C042, EM-C003, EM-C010, EM-C011, EM-C013
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, m7, madd9, maj7; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** I – begründete Interpretation (modale Dominante (Moll-v)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H016 – Plagale Terzkette I–vi–IV–I in add9-Farben
- **Charakter:** zärtlich, innig · **Säule:** A · **Modus/Tonvorrat:** ionisch {1, 2, 3, 4, 5, 6, 7}
- **XYZ-Anker:** 0,75 / 0,30 / 0,15 · **Gültigkeit:** X 0,55–0,95 · Y 0,10–0,50 · Z 0,00–0,35
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:add9*2 | 9:m7*2 | 5:maj7*2 | 0:add9*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |
| 2 | 7680 | 7680 | [6] Moll-Sept | -15 | [-5, +0, +12, +16] | ♭7, ♭3, ♭3, 5 | A | – |
| 3 | 15360 | 7680 | [4] große Septime | -19 | [-3, +0, +12, +16] | 3, 5, 5, 7 | A | – |
| 4 | 23040 | 7680 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, 3, 5}; gehalten -5, +12, +16; bewegt St2 +2→+0 (-2); Bass -3 · 2→3: gemeinsam {1, 3, 6}; gehalten +0, +12, +16; bewegt St1 -5→-3 (+2); Bass -4 · 3→4: gemeinsam {1, 3}; gehalten +12, +16; bewegt St1 -3→-5 (-2), St2 +0→+2 (+2); Bass +7
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U007, EM-U008, EM-U009, EM-U010, EM-U011, EM-U016, EM-U030, EM-U041; Zellen EM-C006, EM-C029, EM-C031, EM-C041, EM-C020
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C014, EM-C015, EM-C018) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, m7, maj7; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** N – nachgewiesenes Verfahren (Plagal-Terzkette (filmmusicnotes)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H017 – Plagale Terzkette mit iii-Einschub
- **Charakter:** erinnernd, still · **Säule:** A · **Modus/Tonvorrat:** ionisch {1, 2, 3, 4, 5, 6, 7}
- **XYZ-Anker:** 0,70 / 0,25 / 0,20 · **Gültigkeit:** X 0,50–0,90 · Y 0,05–0,45 · Z 0,00–0,40
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `9:m7*2 | 4:m7*2 | 5:maj7*2 | 0:add9*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [6] Moll-Sept | -15 | [-8, +0, +9, +19] | 5, ♭3, 1, ♭7 | A | – |
| 2 | 7680 | 7680 | [3] Moll-Sept | -20 | [-8, +2, +11, +19] | 1, ♭7, 5, ♭3 | A | – |
| 3 | 15360 | 7680 | [4] große Septime | -19 | [-8, +0, +9, +17] | 7, 5, 3, 1 | A | – |
| 4 | 23040 | 7680 | [1] Dur-add9 | -12 | [-8, +0, +7, +14] | 3, 1, 5, 9 | A | – |

- **Übergänge:** 1→2: gemeinsam {3, 5}; gehalten -8, +19; bewegt St2 +0→+2 (+2), St3 +9→+11 (+2); Bass -5 · 2→3: gemeinsam {3}; gehalten -8; bewegt St2 +2→+0 (-2), St3 +11→+9 (-2), St4 +19→+17 (-2); Bass +1 · 3→4: gemeinsam {1, 3}; gehalten -8, +0; bewegt St3 +9→+7 (-2), St4 +17→+14 (-3); Bass +7
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U007, EM-U008, EM-U009, EM-U010, EM-U011, EM-U016, EM-U030, EM-U041; Zellen EM-C020, EM-C006, EM-C029, EM-C031, EM-C041
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C014, EM-C015, EM-C018) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, m7, maj7; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** N – nachgewiesenes Verfahren ((I)–vi–(iii)–IV–I); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H018 – Stufenweise gefüllter Plagalbass
- **Charakter:** gesanglich, tröstend · **Säule:** A · **Modus/Tonvorrat:** ionisch {1, 2, 3, 4, 5, 6, 7}
- **XYZ-Anker:** 0,75 / 0,35 / 0,20 · **Gültigkeit:** X 0,55–0,95 · Y 0,15–0,55 · Z 0,00–0,40
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:add9*1 | 7:maj/11*1 | 9:m7*1 | 4:min/11*1 | 5:maj7*1 | 0:maj/4*1 | 2:m7*1 | 0:add9*1`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 3840 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |
| 2 | 3840 | 3840 | [5] Dur / Bass [7] | -13 | [-5, +2, +11, +14] | 1, 5, 3, 5 | A | – |
| 3 | 7680 | 3840 | [6] Moll-Sept | -15 | [-5, +0, +9, +16] | ♭7, ♭3, 1, 5 | A | – |
| 4 | 11520 | 3840 | [3] Moll / Bass [7] | -13 | [-5, -1, +7, +16] | ♭3, 5, ♭3, 1 | A | – |
| 5 | 15360 | 3840 | [4] große Septime | -19 | [-7, +0, +9, +16] | 1, 5, 3, 7 | A | – |
| 6 | 19200 | 3840 | [1] Dur / Bass [3] | -20 | [-8, +0, +7, +16] | 3, 1, 5, 3 | A | – |
| 7 | 23040 | 3840 | [2] Moll-Sept | -22 | [-7, +0, +9, +14] | ♭3, ♭7, 5, 1 | A | – |
| 8 | 26880 | 3840 | [1] Dur-add9 | -12 | [-8, +0, +7, +14] | 3, 1, 5, 9 | A | – |

- **Übergänge:** 1→2: gemeinsam {2, 5}; gehalten -5, +2; bewegt St3 +12→+11 (-1), St4 +16→+14 (-2); Bass -1 · 2→3: gemeinsam {5}; gehalten -5; bewegt St2 +2→+0 (-2), St3 +11→+9 (-2), St4 +14→+16 (+2); Bass -2 · 3→4: gemeinsam {3, 5}; gehalten -5, +16; bewegt St2 +0→-1 (-1), St3 +9→+7 (-2); Bass +2 · 4→5: gemeinsam {3}; gehalten +16; bewegt St1 -5→-7 (-2), St2 -1→+0 (+1), St3 +7→+9 (+2); Bass -6 · 5→6: gemeinsam {1, 3}; gehalten +0, +16; bewegt St1 -7→-8 (-1), St3 +9→+7 (-2); Bass -1 · 6→7: gemeinsam {1}; gehalten +0; bewegt St1 -8→-7 (+1), St3 +7→+9 (+2), St4 +16→+14 (-2); Bass -2 · 7→8: gemeinsam {1, 2}; gehalten +0, +14; bewegt St1 -7→-8 (-1), St3 +9→+7 (-2); Bass +10
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U007, EM-U008, EM-U009, EM-U010, EM-U011, EM-U013, EM-U016, EM-U030; Zellen EM-C006, EM-C029, EM-C031, EM-C041, EM-C020
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C014, EM-C015, EM-C018) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, m7, maj, maj7, min; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** N – nachgewiesenes Verfahren (Terzkette mit stufenweisem Bass); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H019 – Fallende Terzkette zum Halbschluss
- **Charakter:** offen fragend · **Säule:** A · **Modus/Tonvorrat:** ionisch {1, 2, 3, 4, 5, 6, 7}
- **XYZ-Anker:** 0,70 / 0,35 / 0,30 · **Gültigkeit:** X 0,50–0,90 · Y 0,15–0,55 · Z 0,10–0,50
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:add9*2 | 9:m7*2 | 5:maj7*2 | 2:m7*1 | 7:sus4*1`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |
| 2 | 7680 | 7680 | [6] Moll-Sept | -15 | [-5, +0, +12, +16] | ♭7, ♭3, ♭3, 5 | A | – |
| 3 | 15360 | 7680 | [4] große Septime | -19 | [-3, +0, +12, +16] | 3, 5, 5, 7 | A | – |
| 4 | 23040 | 3840 | [2] Moll-Sept | -22 | [-3, +0, +12, +17] | 5, ♭7, ♭7, ♭3 | A | – |
| 5 | 26880 | 3840 | [5] sus4 | -17 | [-5, +0, +12, +14] | 1, 4/11, 4/11, 5 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, 3, 5}; gehalten -5, +12, +16; bewegt St2 +2→+0 (-2); Bass -3 · 2→3: gemeinsam {1, 3, 6}; gehalten +0, +12, +16; bewegt St1 -5→-3 (+2); Bass -4 · 3→4: gemeinsam {1, 4, 6}; gehalten -3, +0, +12; bewegt St4 +16→+17 (+1); Bass -3 · 4→5: gemeinsam {1, 2}; gehalten +0, +12; bewegt St1 -3→-5 (-2), St4 +17→+14 (-3); Bass +5
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U007, EM-U008, EM-U009, EM-U010, EM-U011, EM-U013, EM-U016, EM-U030; Zellen EM-C020, EM-C006, EM-C029, EM-C031, EM-C041
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C014, EM-C015, EM-C018) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, m7, maj7, sus4; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** N – nachgewiesenes Verfahren (I–vi–IV–ii–V (filmmusicnotes)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H020 – Plagaler Wechsel über Tonikapedal
- **Charakter:** atmend, ruhig · **Säule:** A · **Modus/Tonvorrat:** ionisch {1, 2, 3, 4, 5, 6, 7}
- **XYZ-Anker:** 0,80 / 0,20 / 0,10 · **Gültigkeit:** X 0,60–1,00 · Y 0,00–0,40 · Z 0,00–0,30
- **Rollen:** LF (Oberstimmen), LB (Bass, Pedal) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** None
- **Progression (Notation):** `0:add9*2 | 5:add9/0*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |
| 2 | 7680 | 7680 | [4] Dur-add9 / Bass [1] | -12 | [-5, +0, +9, +17] | 9, 5, 3, 1 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, 5}; gehalten -5; bewegt St2 +2→+0 (-2), St3 +12→+9 (-3), St4 +16→+17 (+1); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass: Pedal (A/U je Segment)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U007, EM-U011, EM-U016, EM-U030, EM-U034, EM-U041, EM-U044; Zellen EM-C006, EM-C029, EM-C031, EM-C041, EM-C020
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C014, EM-C015, EM-C018) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9; Stimmführungs-Solver mit Gemeinsamton-Priorität; Pedalrolle
- **Evidenz:** I – begründete Interpretation (IV/I über Pedal); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H021 – Lydisches Schweben I-maj7 – IV-maj7♯11
- **Charakter:** kalt-hell, schwerelos · **Säule:** A · **Modus/Tonvorrat:** lydisch {1, 2, 3, ♯4/♭5, 5, 6, 7}
- **XYZ-Anker:** 0,90 / 0,20 / 0,15 · **Gültigkeit:** X 0,70–1,00 · Y 0,00–0,40 · Z 0,00–0,35
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:maj7*2 | 5:maj7#11*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] große Septime | -12 | [-5, +0, +11, +16] | 5, 1, 7, 3 | A | – |
| 2 | 7680 | 7680 | [4] maj7♯11 | -7 | [-3, +0, +11, +16] | 3, 5, ♯11/♭5, 7 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, 3, 7}; gehalten +0, +11, +16; bewegt St1 -5→-3 (+2); Bass +5
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U018, EM-U031; Zellen EM-C034, EM-C006, EM-C029, EM-C031, EM-C041
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C013, EM-C014, EM-C025, EM-C027) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten maj7, maj7#11; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (lydische Farbe (nicht belegt, kein Verbot)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H022 – Dur-add9 mit Moll-♭VI-Einfärbung
- **Charakter:** goldene Wehmut · **Säule:** A · **Modus/Tonvorrat:** dur_moll_gemischt {1, 2, ♭3, 3, 4, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,70 / 0,40 / 0,25 · **Gültigkeit:** X 0,50–0,90 · Y 0,20–0,60 · Z 0,05–0,45
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:add9*2 | 8:add9*2 | 0:add9*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |
| 2 | 7680 | 7680 | [♭6] Dur-add9 | -16 | [-2, +3, +12, +15] | 9, 5, 3, 5 | A | – |
| 3 | 15360 | 15360 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |

- **Übergänge:** 1→2: gemeinsam {1}; gehalten +12; bewegt St1 -5→-2 (+3), St2 +2→+3 (+1), St4 +16→+15 (-1); Bass -4 · 2→3: gemeinsam {1}; gehalten +12; bewegt St1 -2→-5 (-3), St2 +3→+2 (-1), St4 +15→+16 (+1); Bass +4
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U007, EM-U011, EM-U016, EM-U030, EM-U041, EM-U044; Zellen EM-C020, EM-C006, EM-C029, EM-C031, EM-C041
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (Modalmischung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H023 – Dur-Tonika mit Moll-Subdominante
- **Charakter:** Wärme, die sich eintrübt · **Säule:** A · **Modus/Tonvorrat:** dur_moll_gemischt {1, 2, ♭3, 3, 4, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,60 / 0,30 / 0,25 · **Gültigkeit:** X 0,40–0,80 · Y 0,10–0,50 · Z 0,05–0,45
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:add9*2 | 5:m6*2 | 0:add9*2 | 5:m6*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |
| 2 | 7680 | 7680 | [4] Moll-Sexte | -7 | [-4, +2, +12, +17] | ♭3, 6/13, 5, 1 | A | – |
| 3 | 15360 | 7680 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |
| 4 | 23040 | 7680 | [4] Moll-Sexte | -7 | [-4, +2, +12, +17] | ♭3, 6/13, 5, 1 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, 2}; gehalten +2, +12; bewegt St1 -5→-4 (+1), St4 +16→+17 (+1); Bass +5 · 2→3: gemeinsam {1, 2}; gehalten +2, +12; bewegt St1 -4→-5 (-1), St4 +17→+16 (-1); Bass -5 · 3→4: gemeinsam {1, 2}; gehalten +2, +12; bewegt St1 -5→-4 (+1), St4 +16→+17 (+1); Bass +5
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U006, EM-U007, EM-U011, EM-U016, EM-U030, EM-U041, EM-U044; Zellen EM-C007, EM-C012, EM-C017, EM-C040, EM-C002
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, m6; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** I – begründete Interpretation (Dur/Moll-Umfärbung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H024 – Gleicher Grundton Dur–Moll
- **Charakter:** Licht verlischt · **Säule:** A · **Modus/Tonvorrat:** dur_moll_gemischt {1, 2, ♭3, 3, 4, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,50 / 0,25 / 0,30 · **Gültigkeit:** X 0,30–0,70 · Y 0,05–0,45 · Z 0,10–0,50
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** None
- **Progression (Notation):** `0:add9*2 | 0:madd9*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |
| 2 | 7680 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |

- **Übergänge:** 1→2: gemeinsam {1, 2, 5}; gehalten -5, +2, +12; bewegt St4 +16→+15 (-1); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U007, EM-U011, EM-U016; Zellen EM-C003, EM-C011, EM-C026, EM-C028, EM-C042
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, madd9; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** N – nachgewiesenes Verfahren (Dur/Moll-Wechsel (filmmusicnotes, Crisis-Blog I)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H025 – vi-m9 – IV-maj7 – I-6/9
- **Charakter:** nachdenklich, warm · **Säule:** A · **Modus/Tonvorrat:** ionisch {1, 2, 3, 4, 5, 6, 7}
- **XYZ-Anker:** 0,70 / 0,30 / 0,15 · **Gültigkeit:** X 0,50–0,90 · Y 0,10–0,50 · Z 0,00–0,35
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `9:m9*2 | 5:maj7*2 | 0:6/9*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [6] Moll-None | -15 | [-8, +0, +11, +19] | 5, ♭3, 9, ♭7 | A | offen (gr. Septime/kl. None) |
| 2 | 7680 | 7680 | [4] große Septime | -19 | [-8, +0, +9, +17] | 7, 5, 3, 1 | A | – |
| 3 | 15360 | 15360 | [1] Dur-Sexte / Bass [6] | -15 | [-8, +0, +9, +19] | 3, 1, 6/13, 5 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, 3, 6}; gehalten -8, +0; bewegt St3 +11→+9 (-2), St4 +19→+17 (-2); Bass -4 · 2→3: gemeinsam {1, 3, 6}; gehalten -8, +0, +9; bewegt St4 +17→+19 (+2); Bass +4
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U009, EM-U042, EM-U050; Zellen EM-C020, EM-C006, EM-C029, EM-C031, EM-C041
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C014, EM-C015, EM-C018) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten 6, m9, maj7; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (Erweiterte Farben); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H026 – Dur-6/9-Klangfeld
- **Charakter:** stehendes Licht · **Säule:** A · **Modus/Tonvorrat:** pentaton_dur {1, 2, 3, 5, 6}
- **XYZ-Anker:** 0,85 / 0,20 / 0,10 · **Gültigkeit:** X 0,65–1,00 · Y 0,00–0,40 · Z 0,00–0,30
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:6/9*8`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 30720 | [1] Dur-Sexte / Bass [6] | -15 | [-8, +0, +9, +19] | 3, 1, 6/13, 5 | A | – |

- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U050; Zellen EM-C029, EM-C031, EM-C020, EM-C007, EM-C002
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C013, EM-C014, EM-C015, EM-C018) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten 6; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** I – begründete Interpretation (immobilità dinamica); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H027 – Stufenweise fallend diatonisch zur Tonika
- **Charakter:** abendlich · **Säule:** A · **Modus/Tonvorrat:** ionisch {1, 2, 3, 4, 5, 6, 7}
- **XYZ-Anker:** 0,70 / 0,30 / 0,20 · **Gültigkeit:** X 0,50–0,90 · Y 0,10–0,50 · Z 0,00–0,40
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** None
- **Progression (Notation):** `5:maj7*1 | 4:m7*1 | 2:m7*1 | 0:add9*1`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 3840 | [4] große Septime | -7 | [+0, +4, +5, +9] | 5, 7, 1, 3 | A | – |
| 2 | 3840 | 3840 | [3] Moll-Sept | -8 | [+2, +4, +7, +11] | ♭7, 1, ♭3, 5 | A | – |
| 3 | 7680 | 3840 | [2] Moll-Sept | -10 | [+2, +5, +9, +12] | 1, ♭3, 5, ♭7 | A | – |
| 4 | 11520 | 3840 | [1] Dur-add9 | -12 | [+2, +4, +7, +12] | 9, 3, 5, 1 | A | – |

- **Übergänge:** 1→2: gemeinsam {3}; gehalten +4; bewegt St1 +0→+2 (+2), St3 +5→+7 (+2), St4 +9→+11 (+2); Bass -1 · 2→3: gemeinsam {2}; gehalten +2; bewegt St2 +4→+5 (+1), St3 +7→+9 (+2), St4 +11→+12 (+1); Bass -2 · 3→4: gemeinsam {1, 2}; gehalten +2, +12; bewegt St2 +5→+4 (-1), St3 +9→+7 (-2); Bass -2
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U007, EM-U009, EM-U011, EM-U013, EM-U016, EM-U030, EM-U041, EM-U042; Zellen EM-C020, EM-C006, EM-C029, EM-C031, EM-C041
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C014, EM-C015, EM-C018) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, m7, maj7; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (diatonische Parallelführung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H028 – Pedalplagal vi/I – IV/I
- **Charakter:** sanft leuchtend · **Säule:** A · **Modus/Tonvorrat:** ionisch {1, 2, 3, 4, 5, 6, 7}
- **XYZ-Anker:** 0,80 / 0,25 / 0,10 · **Gültigkeit:** X 0,60–1,00 · Y 0,05–0,45 · Z 0,00–0,30
- **Rollen:** LF (Oberstimmen), LB (Bass, Pedal) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:add9*2 | 9:min/0*2 | 5:maj/0*2 | 0:add9*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |
| 2 | 7680 | 7680 | [6] Moll / Bass [1] | -12 | [-3, +0, +12, +16] | 1, ♭3, ♭3, 5 | A | – |
| 3 | 15360 | 7680 | [4] Dur / Bass [1] | -12 | [-3, +0, +12, +17] | 3, 5, 5, 1 | A | – |
| 4 | 23040 | 7680 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, 3}; gehalten +12, +16; bewegt St1 -5→-3 (+2), St2 +2→+0 (-2); Bass +0 · 2→3: gemeinsam {1, 6}; gehalten -3, +0, +12; bewegt St4 +16→+17 (+1); Bass +0 · 3→4: gemeinsam {1}; gehalten +12; bewegt St1 -3→-5 (-2), St2 +0→+2 (+2), St4 +17→+16 (-1); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass: Pedal (A/U je Segment)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U007, EM-U011, EM-U016, EM-U022, EM-U030, EM-U041, EM-U044; Zellen EM-C006, EM-C029, EM-C031, EM-C041, EM-C020
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C014, EM-C015, EM-C018) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, maj, min; Stimmführungs-Solver mit Gemeinsamton-Priorität; Pedalrolle
- **Evidenz:** I – begründete Interpretation (Plagal über Pedal); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H029 – ii-m9 – I/3 – IV – I
- **Charakter:** hymnisch, verhalten · **Säule:** A · **Modus/Tonvorrat:** ionisch {1, 2, 3, 4, 5, 6, 7}
- **XYZ-Anker:** 0,75 / 0,45 / 0,15 · **Gültigkeit:** X 0,55–0,95 · Y 0,25–0,65 · Z 0,00–0,35
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `2:m9*2 | 0:maj/4*2 | 5:add9*2 | 0:add9*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [2] Moll-None | -10 | [-3, +0, +5, +16] | 5, ♭7, ♭3, 9 | A | offen (gr. Septime/kl. None) |
| 2 | 7680 | 7680 | [1] Dur / Bass [3] | -8 | [-5, +0, +4, +16] | 5, 1, 3, 3 | A | – |
| 3 | 15360 | 7680 | [4] Dur-add9 | -7 | [-5, +0, +9, +17] | 9, 5, 3, 1 | A | – |
| 4 | 23040 | 7680 | [1] Dur-add9 | -12 | [-5, +0, +4, +14] | 5, 1, 3, 9 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, 3}; gehalten +0, +16; bewegt St1 -3→-5 (-2), St3 +5→+4 (-1); Bass +2 · 2→3: gemeinsam {1, 5}; gehalten -5, +0; bewegt St3 +4→+9 (+5), St4 +16→+17 (+1); Bass +1 · 3→4: gemeinsam {1, 5}; gehalten -5, +0; bewegt St3 +9→+4 (-5), St4 +17→+14 (-3); Bass -5
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U007, EM-U011, EM-U016, EM-U030, EM-U034, EM-U041, EM-U044; Zellen EM-C006, EM-C029, EM-C031, EM-C041, EM-C020
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C014, EM-C015, EM-C018) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, m9, maj; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (Umkehrungsbass); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H030 – Dur-maj7 im Halbtonwechsel zur Moll-Variante
- **Charakter:** zärtlich verunsichert · **Säule:** A · **Modus/Tonvorrat:** dur_moll_gemischt {1, 2, ♭3, 3, 4, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,55 / 0,20 / 0,40 · **Gültigkeit:** X 0,35–0,75 · Y 0,00–0,40 · Z 0,20–0,60
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** None
- **Progression (Notation):** `0:maj7*2 | 0:mmaj7*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] große Septime | -12 | [-5, +0, +11, +16] | 5, 1, 7, 3 | A | – |
| 2 | 7680 | 7680 | [1] Moll mit gr. Septime | -12 | [-5, +0, +11, +15] | 5, 1, 7, ♭3 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, 5, 7}; gehalten -5, +0, +11; bewegt St4 +16→+15 (-1); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U018, EM-U031; Zellen EM-C002, EM-C033, EM-C007, EM-C012, EM-C017
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten maj7, mmaj7; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (Dur/Moll-Umfärbung bei liegender Septime); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H031 – Andalusischer Abstieg mit add9-Tonika
- **Charakter:** schicksalhaft, offen · **Säule:** A · **Modus/Tonvorrat:** harm_moll {1, 2, ♭3, 4, 5, ♭6, 7}
- **XYZ-Anker:** 0,30 / 0,50 / 0,35 · **Gültigkeit:** X 0,10–0,50 · Y 0,30–0,70 · Z 0,15–0,55
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** None
- **Progression (Notation):** `0:madd9*1 | 10:maj*1 | 8:maj7*1 | 7:maj*1`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 3840 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 3840 | 3840 | [♭7] Dur | -14 | [-7, +2, +10, +14] | 5, 3, 1, 3 | A | – |
| 3 | 7680 | 3840 | [♭6] große Septime | -16 | [-5, +0, +8, +15] | 7, 3, 1, 5 | A | – |
| 4 | 11520 | 3840 | [5] Dur | -17 | [-5, -1, +11, +14] | 1, 3, 3, 5 | A | – |

- **Übergänge:** 1→2: gemeinsam {2}; gehalten +2; bewegt St1 -5→-7 (-2), St3 +12→+10 (-2), St4 +15→+14 (-1); Bass -2 · 2→3: gemeinsam {}; gehalten keine; bewegt St1 -7→-5 (+2), St2 +2→+0 (-2), St3 +10→+8 (-2), St4 +14→+15 (+1); Bass -2 · 3→4: gemeinsam {5}; gehalten -5; bewegt St2 +0→-1 (-1), St3 +8→+11 (+3), St4 +15→+14 (-1); Bass -1
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C027, EM-C032, EM-C039, EM-C045, EM-C001
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten madd9, maj, maj7; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** H – Hypothese (fallender Mollbass (Hooktheory, Crowdsourcing)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H032 – Diatonischer Lamentobass
- **Charakter:** Klage · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,25 / 0,40 / 0,30 · **Gültigkeit:** X 0,05–0,45 · Y 0,20–0,60 · Z 0,10–0,50
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** None
- **Progression (Notation):** `0:madd9*1 | 0:min/10*1 | 5:min/8*1 | 7:sus4*1`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 3840 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 3840 | 3840 | [1] Moll / Bass [♭7] | -14 | [-5, +3, +12, +15] | 5, ♭3, 1, ♭3 | F (dissonanzautorisiert) | – |
| 3 | 7680 | 3840 | [4] Moll / Bass [♭6] | -16 | [-4, +0, +12, +17] | ♭3, 5, 5, 1 | A | – |
| 4 | 11520 | 3840 | [5] sus4 | -17 | [-5, +0, +12, +14] | 1, 4/11, 4/11, 5 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, ♭3, 5}; gehalten -5, +12, +15; bewegt St2 +2→+3 (+1); Bass -2 · 2→3: gemeinsam {1}; gehalten +12; bewegt St1 -5→-4 (+1), St2 +3→+0 (-3), St4 +15→+17 (+2); Bass -2 · 3→4: gemeinsam {1}; gehalten +0, +12; bewegt St1 -4→-5 (-1), St4 +17→+14 (-3); Bass -1
- **Tonfunktionen:** Oberstimmen A; Bass teils F (dissonanzautorisiert)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C025, EM-C027, EM-C032, EM-C039, EM-C045
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten madd9, min, sus4; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (stufenweise fallender Bass); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H033 – Chromatischer Lamentobass
- **Charakter:** Klage mit Schmerzspitze · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,20 / 0,45 / 0,45 · **Gültigkeit:** X 0,00–0,40 · Y 0,25–0,65 · Z 0,25–0,65
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 6 Takte (23040 Ticks) · **Stil:** None
- **Progression (Notation):** `0:madd9*1 | 7:min/10*1 | 5:maj/9*1 | 5:min/8*1 | 7:sus4*1 | 7:7*1`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 3840 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 3840 | 3840 | [5] Moll / Bass [♭7] | -14 | [-5, +2, +10, +14] | 1, 5, ♭3, 5 | A | – |
| 3 | 7680 | 3840 | [4] Dur / Bass [6] | -15 | [-3, +0, +9, +17] | 3, 5, 3, 1 | A | – |
| 4 | 11520 | 3840 | [4] Moll / Bass [♭6] | -16 | [-4, +0, +12, +17] | ♭3, 5, 5, 1 | A | – |
| 5 | 15360 | 3840 | [5] sus4 | -17 | [-5, +0, +12, +14] | 1, 4/11, 4/11, 5 | A | – |
| 6 | 19200 | 3840 | [5] Dominantsept | -17 | [-5, +5, +11, +14] | 1, ♭7, 3, 5 | A | – |

- **Übergänge:** 1→2: gemeinsam {2, 5}; gehalten -5, +2; bewegt St3 +12→+10 (-2), St4 +15→+14 (-1); Bass -2 · 2→3: gemeinsam {}; gehalten keine; bewegt St1 -5→-3 (+2), St2 +2→+0 (-2), St3 +10→+9 (-1), St4 +14→+17 (+3); Bass -1 · 3→4: gemeinsam {1, 4}; gehalten +0, +17; bewegt St1 -3→-4 (-1), St3 +9→+12 (+3); Bass -1 · 4→5: gemeinsam {1}; gehalten +0, +12; bewegt St1 -4→-5 (-1), St4 +17→+14 (-3); Bass -1 · 5→6: gemeinsam {2, 5}; gehalten -5, +14; bewegt St2 +0→+5 (+5), St3 +12→+11 (-1); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C025, EM-C027, EM-C032, EM-C039, EM-C045
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten 7, madd9, maj, min, sus4; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (chromatische Bassbewegung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H034 – Moll-Pendel i–♭VII über Tonikapedal
- **Charakter:** stoisch, trauernd · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,30 / 0,30 / 0,15 · **Gültigkeit:** X 0,10–0,50 · Y 0,10–0,50 · Z 0,00–0,35
- **Rollen:** LF (Oberstimmen), LB (Bass, Pedal) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** None
- **Progression (Notation):** `0:madd9*2 | 10:add9/0*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 7680 | 7680 | [♭7] Dur-add9 / Bass [1] | -12 | [-2, +2, +12, +17] | 1, 3, 9, 5 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, 2}; gehalten +2, +12; bewegt St1 -5→-2 (+3), St4 +15→+17 (+2); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass: Pedal (A/U je Segment)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C025, EM-C027, EM-C032, EM-C039, EM-C045
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, madd9; Stimmführungs-Solver mit Gemeinsamton-Priorität; Pedalrolle
- **Evidenz:** I – begründete Interpretation (Pedal unter Wechselharmonik); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H035 – Dominantpedal unter Tonika und Subdominante
- **Charakter:** drängende Schwere · **Säule:** A · **Modus/Tonvorrat:** harm_moll {1, 2, ♭3, 4, 5, ♭6, 7}
- **XYZ-Anker:** 0,20 / 0,55 / 0,50 · **Gültigkeit:** X 0,00–0,40 · Y 0,35–0,75 · Z 0,30–0,70
- **Rollen:** LF (Oberstimmen), LB (Bass, Pedal) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:min/7*2 | 5:min/7*2 | 7:7sus4*2 | 7:7*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll / Bass [5] | -17 | [+0, +3, +7, +12] | 1, ♭3, 5, 1 | A | – |
| 2 | 7680 | 7680 | [4] Moll / Bass [5] | -17 | [+0, +5, +8, +12] | 5, 1, ♭3, 5 | Pedal | – |
| 3 | 15360 | 7680 | [5] Sept-sus4 | -17 | [+0, +5, +7, +14] | 4/11, ♭7, 1, 5 | A | – |
| 4 | 23040 | 7680 | [5] Dominantsept | -17 | [-1, +5, +7, +14] | 3, ♭7, 1, 5 | A | – |

- **Übergänge:** 1→2: gemeinsam {1}; gehalten +0, +12; bewegt St2 +3→+5 (+2), St3 +7→+8 (+1); Bass +0 · 2→3: gemeinsam {1, 4}; gehalten +0, +5; bewegt St3 +8→+7 (-1), St4 +12→+14 (+2); Bass +0 · 3→4: gemeinsam {2, 4, 5}; gehalten +5, +7, +14; bewegt St1 +0→-1 (-1); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass: Pedal (A/U je Segment)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U014, EM-U015, EM-U023, EM-U028, EM-U037, EM-U038, EM-U040, EM-U045; Zellen EM-C027, EM-C032, EM-C039, EM-C045, EM-C001
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten 7, 7sus4, min; Stimmführungs-Solver mit Gemeinsamton-Priorität; Pedalrolle
- **Evidenz:** I – begründete Interpretation (Orgelpunkt auf 5); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H036 – Quartvorhalt zur Mollterz, verzögert
- **Charakter:** Atemholen · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,35 / 0,25 / 0,25 · **Gültigkeit:** X 0,15–0,55 · Y 0,05–0,45 · Z 0,05–0,45
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:sus4*2 | 0:madd9*2 | 0:min*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] sus4 | -12 | [-7, +0, +7, +19] | 4/11, 1, 5, 5 | A | – |
| 2 | 7680 | 7680 | [1] Moll-add9 | -12 | [-5, +0, +3, +14] | 5, 1, ♭3, 9 | A | offen (gr. Septime/kl. None) |
| 3 | 15360 | 15360 | [1] Moll | -12 | [-5, +0, +3, +15] | 5, 1, ♭3, ♭3 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, 5}; gehalten +0; bewegt St1 -7→-5 (+2), St3 +7→+3 (-4), St4 +19→+14 (-5); Bass +0 · 2→3: gemeinsam {1, ♭3, 5}; gehalten -5, +0, +3; bewegt St4 +14→+15 (+1); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C001, EM-C008, EM-C009, EM-C025, EM-C027
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten madd9, min, sus4; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** I – begründete Interpretation (Vorhalt mit Auflösungsziel); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H037 – Dominante ohne Tonika
- **Charakter:** Erwartung bleibt offen · **Säule:** A · **Modus/Tonvorrat:** harm_moll {1, 2, ♭3, 4, 5, ♭6, 7}
- **XYZ-Anker:** 0,30 / 0,40 / 0,40 · **Gültigkeit:** X 0,10–0,50 · Y 0,20–0,60 · Z 0,20–0,60
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `5:m9*2 | 7:7sus4*2 | 7:7*2 | 5:m9*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [4] Moll-None | -7 | [+0, +7, +8, +15] | 5, 9, ♭3, ♭7 | A | eng (Halbton) |
| 2 | 7680 | 7680 | [5] Sept-sus4 | -17 | [+0, +2, +7, +17] | 4/11, 5, 1, ♭7 | A | – |
| 3 | 15360 | 7680 | [5] Dominantsept | -17 | [-1, +2, +7, +17] | 3, 5, 1, ♭7 | A | – |
| 4 | 23040 | 7680 | [4] Moll-None | -19 | [-4, +0, +7, +15] | ♭3, 5, 9, ♭7 | A | offen (gr. Septime/kl. None) |

- **Übergänge:** 1→2: gemeinsam {1, 4, 5}; gehalten +0; bewegt St2 +7→+2 (-5), St3 +8→+7 (-1), St4 +15→+17 (+2); Bass -10 · 2→3: gemeinsam {2, 4, 5}; gehalten +2, +7, +17; bewegt St1 +0→-1 (-1); Bass +0 · 3→4: gemeinsam {4, 5}; gehalten +7; bewegt St1 -1→-4 (-3), St2 +2→+0 (-2), St4 +17→+15 (-2); Bass -2
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U014, EM-U015, EM-U037; Zellen EM-C027, EM-C032, EM-C039, EM-C045, EM-C001
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten 7, 7sus4, m9; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** N – nachgewiesenes Verfahren (aufgeschobene Auflösung (Smith)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H038 – Seltene funktionale Auflösung iv–V–i
- **Charakter:** Erfüllung nach langem Warten · **Säule:** A · **Modus/Tonvorrat:** harm_moll {1, 2, ♭3, 4, 5, ♭6, 7}
- **XYZ-Anker:** 0,35 / 0,45 / 0,20 · **Gültigkeit:** X 0,15–0,55 · Y 0,25–0,65 · Z 0,00–0,40
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `5:madd9*2 | 7:sus4*1 | 7:maj*1 | 0:madd9*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [4] Moll-add9 | -7 | [+0, +5, +7, +8] | 5, 1, 9, ♭3 | A | eng (Halbton) |
| 2 | 7680 | 3840 | [5] sus4 | -17 | [+0, +2, +7, +12] | 4/11, 5, 1, 4/11 | A | – |
| 3 | 11520 | 3840 | [5] Dur | -17 | [-1, +2, +7, +14] | 3, 5, 1, 5 | A | – |
| 4 | 15360 | 15360 | [1] Moll-add9 | -12 | [+0, +2, +7, +15] | 1, 9, 5, ♭3 | A | offen (gr. Septime/kl. None) |

- **Übergänge:** 1→2: gemeinsam {1, 5}; gehalten +0, +7; bewegt St2 +5→+2 (-3), St4 +8→+12 (+4); Bass -10 · 2→3: gemeinsam {2, 5}; gehalten +2, +7; bewegt St1 +0→-1 (-1), St4 +12→+14 (+2); Bass +0 · 3→4: gemeinsam {2, 5}; gehalten +2, +7; bewegt St1 -1→+0 (+1), St4 +14→+15 (+1); Bass +5
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C001, EM-C008, EM-C009, EM-C027, EM-C032
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten madd9, maj, sus4; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** I – begründete Interpretation (funktional, sparsam); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H039 – Offener Schluss auf ♭VI
- **Charakter:** unvollendet · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,45 / 0,35 / 0,25 · **Gültigkeit:** X 0,25–0,65 · Y 0,15–0,55 · Z 0,05–0,45
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:madd9*2 | 3:add9*2 | 10:add9*2 | 8:maj7*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 7680 | 7680 | [♭3] Dur-add9 | -9 | [-5, +5, +10, +15] | 3, 9, 5, 1 | A | – |
| 3 | 15360 | 7680 | [♭7] Dur-add9 | -14 | [+0, +5, +10, +14] | 9, 5, 1, 3 | A | – |
| 4 | 23040 | 7680 | [♭6] große Septime | -16 | [+0, +7, +8, +15] | 3, 7, 1, 5 | A | – |

- **Übergänge:** 1→2: gemeinsam {♭3, 5}; gehalten -5, +15; bewegt St2 +2→+5 (+3), St3 +12→+10 (-2); Bass +3 · 2→3: gemeinsam {4, ♭7}; gehalten +5, +10; bewegt St1 -5→+0 (+5), St4 +15→+14 (-1); Bass -5 · 3→4: gemeinsam {1}; gehalten +0; bewegt St2 +5→+7 (+2), St3 +10→+8 (-2), St4 +14→+15 (+1); Bass -2
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C042, EM-C003, EM-C010, EM-C011, EM-C013
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, madd9, maj7; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (bewusst offener Schluss); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H040 – Offener Schluss auf IV in Dur
- **Charakter:** Frage ins Licht · **Säule:** A · **Modus/Tonvorrat:** ionisch {1, 2, 3, 4, 5, 6, 7}
- **XYZ-Anker:** 0,80 / 0,30 / 0,25 · **Gültigkeit:** X 0,60–1,00 · Y 0,10–0,50 · Z 0,05–0,45
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:add9*2 | 4:m7*2 | 9:m7*2 | 5:maj7#11*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |
| 2 | 7680 | 7680 | [3] Moll-Sept | -8 | [-5, +2, +11, +16] | ♭3, ♭7, 5, 1 | A | – |
| 3 | 15360 | 7680 | [6] Moll-Sept | -15 | [-5, +0, +9, +16] | ♭7, ♭3, 1, 5 | A | – |
| 4 | 23040 | 7680 | [4] maj7♯11 | -19 | [-1, +0, +9, +16] | ♯11/♭5, 5, 3, 7 | A | – |

- **Übergänge:** 1→2: gemeinsam {2, 3, 5}; gehalten -5, +2, +16; bewegt St3 +12→+11 (-1); Bass +4 · 2→3: gemeinsam {3, 5}; gehalten -5, +16; bewegt St2 +2→+0 (-2), St3 +11→+9 (-2); Bass -7 · 3→4: gemeinsam {1, 3, 6}; gehalten +0, +9, +16; bewegt St1 -5→-1 (+4); Bass -4
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U007, EM-U008, EM-U010, EM-U011, EM-U016, EM-U030, EM-U041, EM-U044; Zellen EM-C006, EM-C029, EM-C031, EM-C041, EM-C020
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C014, EM-C015, EM-C018) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, m7, maj7#11; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (offener plagaler Schluss); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H041 – Weite äolische Rotation i–♭VI–♭III–♭VII
- **Charakter:** episch-tragisch · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,35 / 0,85 / 0,25 · **Gültigkeit:** X 0,15–0,55 · Y 0,65–1,00 · Z 0,05–0,45
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:min*2 | 8:maj*2 | 3:maj*2 | 10:maj*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll | -12 | [-5, +0, +3, +15] | 5, 1, ♭3, ♭3 | A | – |
| 2 | 7680 | 7680 | [♭6] Dur | -16 | [-4, +0, +3, +15] | 1, 3, 5, 5 | A | – |
| 3 | 15360 | 7680 | [♭3] Dur | -21 | [-5, -2, +3, +15] | 3, 5, 1, 1 | A | – |
| 4 | 23040 | 7680 | [♭7] Dur | -14 | [-7, -2, +5, +14] | 5, 1, 5, 3 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, ♭3}; gehalten +0, +3, +15; bewegt St1 -5→-4 (+1); Bass -4 · 2→3: gemeinsam {♭3}; gehalten +3, +15; bewegt St1 -4→-5 (-1), St2 +0→-2 (-2); Bass -5 · 3→4: gemeinsam {♭7}; gehalten -2; bewegt St1 -5→-7 (-2), St3 +3→+5 (+2), St4 +15→+14 (-1); Bass +7
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U028, EM-U040, EM-U045, EM-U048; Zellen EM-C001, EM-C008, EM-C009, EM-C025, EM-C027
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten maj, min; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** I – begründete Interpretation (diatonische Monumentalität); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H042 – Phrygisch-neapolitanische Tragik
- **Charakter:** Schicksal, unausweichlich · **Säule:** A · **Modus/Tonvorrat:** phrygisch {1, ♭2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,20 / 0,80 / 0,35 · **Gültigkeit:** X 0,00–0,40 · Y 0,60–1,00 · Z 0,15–0,55
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:madd9*2 | 1:maj7*2 | 0:madd9*2 | 8:maj*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 7680 | 7680 | [♭2] große Septime | -11 | [-4, +1, +12, +17] | 5, 1, 7, 3 | A | – |
| 3 | 15360 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 4 | 23040 | 7680 | [♭6] Dur | -16 | [-4, +0, +12, +15] | 1, 3, 3, 5 | A | – |

- **Übergänge:** 1→2: gemeinsam {1}; gehalten +12; bewegt St1 -5→-4 (+1), St2 +2→+1 (-1), St4 +15→+17 (+2); Bass +1 · 2→3: gemeinsam {1}; gehalten +12; bewegt St1 -4→-5 (-1), St2 +1→+2 (+1), St4 +17→+15 (-2); Bass -1 · 3→4: gemeinsam {1, ♭3}; gehalten +12, +15; bewegt St1 -5→-4 (+1), St2 +2→+0 (-2); Bass -4
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C014, EM-C004, EM-C025, EM-C027, EM-C032
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C020, EM-C029, EM-C035) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten madd9, maj, maj7; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (♭II (nicht belegt, kein Verbot)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H043 – Dorischer Quintfall-Zirkel
- **Charakter:** kraftvoll, erhaben · **Säule:** A · **Modus/Tonvorrat:** dorisch {1, 2, ♭3, 4, 5, 6, ♭7}
- **XYZ-Anker:** 0,55 / 0,80 / 0,20 · **Gültigkeit:** X 0,35–0,75 · Y 0,60–1,00 · Z 0,00–0,40
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:min*2 | 5:maj*2 | 10:maj*2 | 3:maj*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll | -12 | [-5, +0, +3, +15] | 5, 1, ♭3, ♭3 | A | – |
| 2 | 7680 | 7680 | [4] Dur | -7 | [-3, +0, +5, +17] | 3, 5, 1, 1 | A | – |
| 3 | 15360 | 7680 | [♭7] Dur | -14 | [-2, +2, +5, +17] | 1, 3, 5, 5 | A | – |
| 4 | 23040 | 7680 | [♭3] Dur | -9 | [-2, +3, +7, +15] | 5, 1, 3, 1 | A | – |

- **Übergänge:** 1→2: gemeinsam {1}; gehalten +0; bewegt St1 -5→-3 (+2), St3 +3→+5 (+2), St4 +15→+17 (+2); Bass +5 · 2→3: gemeinsam {4}; gehalten +5, +17; bewegt St1 -3→-2 (+1), St2 +0→+2 (+2); Bass -7 · 3→4: gemeinsam {♭7}; gehalten -2; bewegt St2 +2→+3 (+1), St3 +5→+7 (+2), St4 +17→+15 (-2); Bass +5
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U022, EM-U028, EM-U040, EM-U045, EM-U048; Zellen EM-C002, EM-C007, EM-C012, EM-C040, EM-C003
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C017, EM-C035) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten maj, min; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** I – begründete Interpretation (dorische Dur-IV); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H044 – Monumentaler Halbschluss mit ♭9
- **Charakter:** tragischer Höhepunkt ohne Erlösung · **Säule:** A · **Modus/Tonvorrat:** harm_moll {1, 2, ♭3, 4, 5, ♭6, 7}
- **XYZ-Anker:** 0,20 / 0,90 / 0,45 · **Gültigkeit:** X 0,00–0,40 · Y 0,70–1,00 · Z 0,25–0,65
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:madd9*2 | 8:add#11*2 | 5:m9*2 | 7:7b9*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 7680 | 7680 | [♭6] add♯11 | -16 | [-4, +2, +12, +15] | 1, ♯11/♭5, 3, 5 | A | – |
| 3 | 15360 | 7680 | [4] Moll-None | -19 | [-4, +7, +12, +15] | ♭3, 9, 5, ♭7 | A | offen (gr. Septime/kl. None) |
| 4 | 23040 | 7680 | [5] Sept-♭9 | -17 | [-4, +5, +11, +14] | ♭9, ♭7, 3, 5 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, 2, ♭3}; gehalten +2, +12, +15; bewegt St1 -5→-4 (+1); Bass -4 · 2→3: gemeinsam {1, ♭3, ♭6}; gehalten -4, +12, +15; bewegt St2 +2→+7 (+5); Bass -3 · 3→4: gemeinsam {4, 5, ♭6}; gehalten -4; bewegt St2 +7→+5 (-2), St3 +12→+11 (-1), St4 +15→+14 (-1); Bass +2
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C027, EM-C032, EM-C039, EM-C045, EM-C001
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten 7b9, add#11, m9, madd9; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (Halbschluss, aufgeschobene Auflösung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H045 – Tonikapedal mit Mollsubdominante, monumental
- **Charakter:** würdige Klage · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,30 / 0,75 / 0,15 · **Gültigkeit:** X 0,10–0,50 · Y 0,55–0,95 · Z 0,00–0,35
- **Rollen:** LF (Oberstimmen), LB (Bass, Pedal) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:madd9*2 | 5:min/0*2 | 8:maj/0*2 | 0:madd9*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 7680 | 7680 | [4] Moll / Bass [1] | -12 | [-4, +0, +12, +17] | ♭3, 5, 5, 1 | A | – |
| 3 | 15360 | 7680 | [♭6] Dur / Bass [1] | -12 | [-4, +0, +12, +15] | 1, 3, 3, 5 | A | – |
| 4 | 23040 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |

- **Übergänge:** 1→2: gemeinsam {1}; gehalten +12; bewegt St1 -5→-4 (+1), St2 +2→+0 (-2), St4 +15→+17 (+2); Bass +0 · 2→3: gemeinsam {1, ♭6}; gehalten -4, +0, +12; bewegt St4 +17→+15 (-2); Bass +0 · 3→4: gemeinsam {1, ♭3}; gehalten +12, +15; bewegt St1 -4→-5 (-1), St2 +0→+2 (+2); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass: Pedal (A/U je Segment)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C025, EM-C027, EM-C032, EM-C039, EM-C045
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten madd9, maj, min; Stimmführungs-Solver mit Gemeinsamton-Priorität; Pedalrolle
- **Evidenz:** I – begründete Interpretation (Pedal + Schichtakkumulation); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H046 – Dur-Moll-Doppelklang auf gleicher Wurzel
- **Charakter:** Stolz und Trauer zugleich · **Säule:** A · **Modus/Tonvorrat:** dur_moll_gemischt {1, 2, ♭3, 3, 4, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,55 / 0,75 / 0,35 · **Gültigkeit:** X 0,35–0,75 · Y 0,55–0,95 · Z 0,15–0,55
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:add9*1 | 8:maj*1 | 0:add9*1 | 5:min*1`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 3840 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |
| 2 | 3840 | 3840 | [♭6] Dur | -16 | [-4, +0, +12, +15] | 1, 3, 3, 5 | A | – |
| 3 | 7680 | 3840 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |
| 4 | 11520 | 3840 | [4] Moll | -7 | [-4, +0, +12, +17] | ♭3, 5, 5, 1 | A | – |

- **Übergänge:** 1→2: gemeinsam {1}; gehalten +12; bewegt St1 -5→-4 (+1), St2 +2→+0 (-2), St4 +16→+15 (-1); Bass -4 · 2→3: gemeinsam {1}; gehalten +12; bewegt St1 -4→-5 (-1), St2 +0→+2 (+2), St4 +15→+16 (+1); Bass +4 · 3→4: gemeinsam {1}; gehalten +12; bewegt St1 -5→-4 (+1), St2 +2→+0 (-2), St4 +16→+17 (+1); Bass +5
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U007, EM-U011, EM-U016, EM-U023, EM-U030, EM-U038, EM-U041, EM-U044; Zellen EM-C002, EM-C033, EM-C007, EM-C012, EM-C017
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, maj, min; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (Modalmischung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H047 – ♭VI-maj7 – I-Dur: Licht aus dem Moll
- **Charakter:** Aufbruch mit Schatten · **Säule:** A · **Modus/Tonvorrat:** dur_moll_gemischt {1, 2, ♭3, 3, 4, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,65 / 0,70 / 0,25 · **Gültigkeit:** X 0,45–0,85 · Y 0,50–0,90 · Z 0,05–0,45
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** weit
- **Progression (Notation):** `8:maj7*2 | 10:add9*2 | 0:add9*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [♭6] große Septime | -16 | [-4, +0, +7, +15] | 1, 3, 7, 5 | A | – |
| 2 | 7680 | 7680 | [♭7] Dur-add9 | -14 | [-7, +0, +10, +14] | 5, 9, 1, 3 | A | – |
| 3 | 15360 | 15360 | [1] Dur-add9 | -12 | [-8, +0, +7, +14] | 3, 1, 5, 9 | A | – |

- **Übergänge:** 1→2: gemeinsam {1}; gehalten +0; bewegt St1 -4→-7 (-3), St3 +7→+10 (+3), St4 +15→+14 (-1); Bass +2 · 2→3: gemeinsam {1, 2}; gehalten +0, +14; bewegt St1 -7→-8 (-1), St3 +10→+7 (-3); Bass +2
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U007, EM-U011, EM-U016, EM-U030, EM-U041, EM-U044; Zellen EM-C020, EM-C007, EM-C012, EM-C017, EM-C040
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, maj7; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (picardische Wendung über ♭VII); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H048 – Moll-add9 mit Dur-Sexte im Bass (iv/6)
- **Charakter:** ehrenhaft, ernst · **Säule:** A · **Modus/Tonvorrat:** dorisch {1, 2, ♭3, 4, 5, 6, ♭7}
- **XYZ-Anker:** 0,50 / 0,60 / 0,25 · **Gültigkeit:** X 0,30–0,70 · Y 0,40–0,80 · Z 0,05–0,45
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:madd9*2 | 5:maj/9*2 | 3:maj*2 | 10:add9*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 7680 | 7680 | [4] Dur / Bass [6] | -15 | [-3, +0, +12, +17] | 3, 5, 5, 1 | A | – |
| 3 | 15360 | 7680 | [♭3] Dur | -21 | [-2, +3, +10, +19] | 5, 1, 5, 3 | A | – |
| 4 | 23040 | 7680 | [♭7] Dur-add9 | -14 | [-2, +2, +12, +17] | 1, 3, 9, 5 | A | – |

- **Übergänge:** 1→2: gemeinsam {1}; gehalten +12; bewegt St1 -5→-3 (+2), St2 +2→+0 (-2), St4 +15→+17 (+2); Bass -3 · 2→3: gemeinsam {}; gehalten keine; bewegt St1 -3→-2 (+1), St2 +0→+3 (+3), St3 +12→+10 (-2), St4 +17→+19 (+2); Bass -6 · 3→4: gemeinsam {♭7}; gehalten -2; bewegt St2 +3→+2 (-1), St3 +10→+12 (+2), St4 +19→+17 (-2); Bass +7
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C003, EM-C011, EM-C026, EM-C028, EM-C042
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C017, EM-C035) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, madd9, maj; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (dorische Bassumkehrung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H049 – Sus2-Fläche mit wechselnder Bassstufe
- **Charakter:** unbestimmt, weit · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,50 / 0,45 / 0,30 · **Gültigkeit:** X 0,30–0,70 · Y 0,25–0,65 · Z 0,10–0,50
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:sus2*2 | 0:sus2/8*2 | 0:sus2/5*2 | 0:sus2/7*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] sus2 | -12 | [-5, +2, +12, +19] | 5, 9, 1, 5 | A | – |
| 2 | 7680 | 7680 | [1] sus2 / Bass [♭6] | -16 | [-5, +2, +12, +19] | 5, 9, 1, 5 | F (dissonanzautorisiert) | – |
| 3 | 15360 | 7680 | [1] sus2 / Bass [4] | -19 | [-5, +2, +12, +19] | 5, 9, 1, 5 | F (dissonanzautorisiert) | – |
| 4 | 23040 | 7680 | [1] sus2 / Bass [5] | -17 | [-5, +2, +12, +19] | 5, 9, 1, 5 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, 2, 5}; gehalten -5, +2, +12, +19; bewegt keine; Bass -4 · 2→3: gemeinsam {1, 2, 5}; gehalten -5, +2, +12, +19; bewegt keine; Bass -3 · 3→4: gemeinsam {1, 2, 5}; gehalten -5, +2, +12, +19; bewegt keine; Bass +2
- **Tonfunktionen:** Oberstimmen A; Bass teils F (dissonanzautorisiert)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C003, EM-C011, EM-C026, EM-C028, EM-C042
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten sus2; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (konstante Oberstimmen, bewegter Bass); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H050 – Moll-maj9 als dunkle Schönheit
- **Charakter:** geheimnisvolle Melancholie · **Säule:** A · **Modus/Tonvorrat:** mel_moll {1, 2, ♭3, 4, 5, 6, 7}
- **XYZ-Anker:** 0,30 / 0,25 / 0,40 · **Gültigkeit:** X 0,10–0,50 · Y 0,05–0,45 · Z 0,20–0,60
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:m(maj9)*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | [1] Moll-maj9 | -12 | [-5, +2, +11, +15] | 5, 9, 7, ♭3 | A | offen (gr. Septime/kl. None) |

- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C039, EM-C001, EM-C008, EM-C009, EM-C010
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C017, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten m(maj9); Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (erweiterte Mollfarbe); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H051 – Selbsttragende Gemeinsamton-Kette (None-Bindung)
- **Charakter:** fließende Melancholie · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,45 / 0,30 / 0,20 · **Gültigkeit:** X 0,25–0,65 · Y 0,10–0,50 · Z 0,00–0,40
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:madd9*2 | 10:add9*2 | 3:maj7*2 | 8:maj7*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 7680 | 7680 | [♭7] Dur-add9 | -14 | [-7, +2, +12, +14] | 5, 3, 9, 3 | A | – |
| 3 | 15360 | 7680 | [♭3] große Septime | -9 | [-5, +2, +10, +14] | 3, 7, 5, 7 | A | – |
| 4 | 23040 | 7680 | [♭6] große Septime | -16 | [-5, +0, +8, +15] | 7, 3, 1, 5 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, 2}; gehalten +2, +12; bewegt St1 -5→-7 (-2), St4 +15→+14 (-1); Bass -2 · 2→3: gemeinsam {2, ♭7}; gehalten +2, +14; bewegt St1 -7→-5 (+2), St3 +12→+10 (-2); Bass +5 · 3→4: gemeinsam {♭3, 5}; gehalten -5; bewegt St2 +2→+0 (-2), St3 +10→+8 (-2), St4 +14→+15 (+1); Bass -7
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C042, EM-C003, EM-C010, EM-C011, EM-C013
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, madd9, maj7; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** N – nachgewiesenes Verfahren (Am(add9)→G(add9)-Bindung (Soundfly, korrigiert)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H052 – Liegende Quinte, wandernde Terzen
- **Charakter:** unruhige Zärtlichkeit · **Säule:** A · **Modus/Tonvorrat:** dur_moll_gemischt {1, 2, ♭3, 3, 4, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,45 / 0,30 / 0,45 · **Gültigkeit:** X 0,25–0,65 · Y 0,10–0,50 · Z 0,25–0,65
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** eng
- **Progression (Notation):** `0:min*1 | 0:maj*1 | 8:maj*1 | 5:min/8*1`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 3840 | [1] Moll | -12 | [+0, +3, +7, +12] | 1, ♭3, 5, 1 | A | – |
| 2 | 3840 | 3840 | [1] Dur | -12 | [+0, +4, +7, +12] | 1, 3, 5, 1 | A | – |
| 3 | 7680 | 3840 | [♭6] Dur | -16 | [+0, +3, +8, +12] | 3, 5, 1, 3 | A | – |
| 4 | 11520 | 3840 | [4] Moll / Bass [♭6] | -16 | [+0, +5, +8, +12] | 5, 1, ♭3, 5 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, 5}; gehalten +0, +7, +12; bewegt St2 +3→+4 (+1); Bass +0 · 2→3: gemeinsam {1}; gehalten +0, +12; bewegt St2 +4→+3 (-1), St3 +7→+8 (+1); Bass -4 · 3→4: gemeinsam {1, ♭6}; gehalten +0, +8, +12; bewegt St2 +3→+5 (+2); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil eng) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U023, EM-U028, EM-U038, EM-U040, EM-U045, EM-U048; Zellen EM-C042, EM-C003, EM-C010, EM-C011, EM-C013
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten maj, min; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (chromatische Einzelstimme); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H053 – Oberstimme fest, Harmonien darunter wechseln
- **Charakter:** Reharmonisierungsfeld · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,50 / 0,30 / 0,25 · **Gültigkeit:** X 0,30–0,70 · Y 0,10–0,50 · Z 0,05–0,45
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:madd9*2 | 5:m7*2 | 8:maj7#11*2 | 10:add9*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 7680 | 7680 | [4] Moll-Sept | -7 | [-4, +5, +12, +15] | ♭3, 1, 5, ♭7 | A | – |
| 3 | 15360 | 7680 | [♭6] maj7♯11 | -16 | [-5, +2, +12, +15] | 7, ♯11/♭5, 3, 5 | A | – |
| 4 | 23040 | 7680 | [♭7] Dur-add9 | -14 | [-7, +2, +12, +14] | 5, 3, 9, 3 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, ♭3}; gehalten +12, +15; bewegt St1 -5→-4 (+1), St2 +2→+5 (+3); Bass +5 · 2→3: gemeinsam {1, ♭3, ♭6}; gehalten +12, +15; bewegt St1 -4→-5 (-1), St2 +5→+2 (-3); Bass -9 · 3→4: gemeinsam {1, 2}; gehalten +2, +12; bewegt St1 -5→-7 (-2), St4 +15→+14 (-1); Bass +2
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C003, EM-C011, EM-C026, EM-C028, EM-C042
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, m7, madd9, maj7#11; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** I – begründete Interpretation (identischer Ton über verändertem Unterbau); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H054 – Zwei-Akkord-Atmung m9 – maj7
- **Charakter:** ruhig atmend · **Säule:** A · **Modus/Tonvorrat:** dorisch {1, 2, ♭3, 4, 5, 6, ♭7}
- **XYZ-Anker:** 0,55 / 0,20 / 0,10 · **Gültigkeit:** X 0,35–0,75 · Y 0,00–0,40 · Z 0,00–0,30
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:m9*4 | 3:maj7*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | [1] Moll-None | -12 | [-2, +2, +7, +15] | ♭7, 9, 5, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 15360 | 15360 | [♭3] große Septime | -9 | [-2, +2, +7, +15] | 5, 7, 3, 1 | A | – |

- **Übergänge:** 1→2: gemeinsam {2, ♭3, 5, ♭7}; gehalten -2, +2, +7, +15; bewegt keine; Bass +3
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U021; Zellen EM-C002, EM-C007, EM-C012, EM-C040, EM-C003
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C017, EM-C035) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten m9, maj7; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** I – begründete Interpretation (immobilità dinamica); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H055 – Moll-add11-Fläche (Quartfarbe)
- **Charakter:** herb, offen · **Säule:** A · **Modus/Tonvorrat:** dorisch {1, 2, ♭3, 4, 5, 6, ♭7}
- **XYZ-Anker:** 0,45 / 0,25 / 0,20 · **Gültigkeit:** X 0,25–0,65 · Y 0,05–0,45 · Z 0,00–0,40
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:m7add11*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | [1] Moll-Sept-add11 | -12 | [-7, +3, +10, +19] | 4/11, ♭3, ♭7, 5 | A | – |

- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C042, EM-C003, EM-C010, EM-C011, EM-C013
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C017, EM-C035) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten m7add11; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (erweiterte Farbe); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H056 – Plagale Mollterzkette i–♭VI–iv–i
- **Charakter:** dunkle Innigkeit · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,35 / 0,30 / 0,15 · **Gültigkeit:** X 0,15–0,55 · Y 0,10–0,50 · Z 0,00–0,35
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:madd9*2 | 8:maj7*2 | 5:madd9*2 | 0:min*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 7680 | 7680 | [♭6] große Septime | -16 | [-5, +3, +12, +15] | 7, 5, 3, 5 | A | – |
| 3 | 15360 | 7680 | [4] Moll-add9 | -19 | [-5, +5, +12, +20] | 9, 1, 5, ♭3 | A | weit (25 HT) |
| 4 | 23040 | 7680 | [1] Moll | -12 | [-5, +3, +12, +19] | 5, ♭3, 1, 5 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, ♭3, 5}; gehalten -5, +12, +15; bewegt St2 +2→+3 (+1); Bass -4 · 2→3: gemeinsam {1, 5, ♭6}; gehalten -5, +12; bewegt St2 +3→+5 (+2), St4 +15→+20 (+5); Bass -3 · 3→4: gemeinsam {1, 5}; gehalten -5, +12; bewegt St2 +5→+3 (-2), St4 +20→+19 (-1); Bass +7
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C001, EM-C008, EM-C009, EM-C025, EM-C027
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten madd9, maj7, min; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** I – begründete Interpretation (Moll-Analogon der Plagal-Terzkette); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H057 – Terzverwandte Dur-Mediante ♭III–I
- **Charakter:** Erinnerung, Glanz · **Säule:** A · **Modus/Tonvorrat:** dur_moll_gemischt {1, 2, ♭3, 3, 4, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,70 / 0,40 / 0,30 · **Gültigkeit:** X 0,50–0,90 · Y 0,20–0,60 · Z 0,10–0,50
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:add9*2 | 3:add9*2 | 0:add9*2 | 9:m7*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |
| 2 | 7680 | 7680 | [♭3] Dur-add9 | -9 | [-5, +3, +10, +17] | 3, 1, 5, 9 | A | – |
| 3 | 15360 | 7680 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |
| 4 | 23040 | 7680 | [6] Moll-Sept | -15 | [-5, +0, +12, +16] | ♭7, ♭3, ♭3, 5 | A | – |

- **Übergänge:** 1→2: gemeinsam {5}; gehalten -5; bewegt St2 +2→+3 (+1), St3 +12→+10 (-2), St4 +16→+17 (+1); Bass +3 · 2→3: gemeinsam {5}; gehalten -5; bewegt St2 +3→+2 (-1), St3 +10→+12 (+2), St4 +17→+16 (-1); Bass -3 · 3→4: gemeinsam {1, 3, 5}; gehalten -5, +12, +16; bewegt St2 +2→+0 (-2); Bass -3
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U007, EM-U008, EM-U010, EM-U011, EM-U016, EM-U030, EM-U041, EM-U044; Zellen EM-C020, EM-C006, EM-C029, EM-C031, EM-C041
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, m7; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (chromatische Mediante (nicht belegt, kein Verbot)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H058 – Moll-6/9 mit liegender Sexte
- **Charakter:** zarte Resignation · **Säule:** A · **Modus/Tonvorrat:** dorisch {1, 2, ♭3, 4, 5, 6, ♭7}
- **XYZ-Anker:** 0,50 / 0,25 / 0,20 · **Gültigkeit:** X 0,30–0,70 · Y 0,05–0,45 · Z 0,00–0,40
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:m6/9*2 | 5:9*2 | 0:m6/9*2 | 10:maj7*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-Sexte / Bass [6] | -15 | [-3, +0, +7, +15] | 6/13, 1, 5, ♭3 | A | – |
| 2 | 7680 | 7680 | [4] Dominant-None | -19 | [-3, +0, +7, +15] | 3, 5, 9, ♭7 | A | – |
| 3 | 15360 | 7680 | [1] Moll-Sexte / Bass [6] | -15 | [-3, +0, +7, +15] | 6/13, 1, 5, ♭3 | A | – |
| 4 | 23040 | 7680 | [♭7] große Septime | -14 | [-3, +2, +5, +14] | 7, 3, 5, 3 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, ♭3, 5, 6}; gehalten -3, +0, +7, +15; bewegt keine; Bass -4 · 2→3: gemeinsam {1, ♭3, 5, 6}; gehalten -3, +0, +7, +15; bewegt keine; Bass +4 · 3→4: gemeinsam {6}; gehalten -3; bewegt St2 +0→+2 (+2), St3 +7→+5 (-2), St4 +15→+14 (-1); Bass +1
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U032; Zellen EM-C003, EM-C011, EM-C026, EM-C028, EM-C042
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C017, EM-C035) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten 9, m6, maj7; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (liegende Sexte); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H059 – Dur-add9 über wechselnden Bässen (Sext-Terz)
- **Charakter:** Sehnsucht nach Ferne · **Säule:** A · **Modus/Tonvorrat:** ionisch {1, 2, 3, 4, 5, 6, 7}
- **XYZ-Anker:** 0,80 / 0,35 / 0,20 · **Gültigkeit:** X 0,60–1,00 · Y 0,15–0,55 · Z 0,00–0,40
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:add9*2 | 0:add9/9*2 | 0:add9/5*2 | 0:add9/7*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |
| 2 | 7680 | 7680 | [1] Dur-add9 / Bass [6] | -15 | [-5, +2, +12, +16] | 5, 9, 1, 3 | F (dissonanzautorisiert) | – |
| 3 | 15360 | 7680 | [1] Dur-add9 / Bass [4] | -19 | [-5, +2, +12, +16] | 5, 9, 1, 3 | F (dissonanzautorisiert) | – |
| 4 | 23040 | 7680 | [1] Dur-add9 / Bass [5] | -17 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, 2, 3, 5}; gehalten -5, +2, +12, +16; bewegt keine; Bass -3 · 2→3: gemeinsam {1, 2, 3, 5}; gehalten -5, +2, +12, +16; bewegt keine; Bass -4 · 3→4: gemeinsam {1, 2, 3, 5}; gehalten -5, +2, +12, +16; bewegt keine; Bass +2
- **Tonfunktionen:** Oberstimmen A; Bass teils F (dissonanzautorisiert)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U007, EM-U011, EM-U016, EM-U030, EM-U041, EM-U044; Zellen EM-C006, EM-C029, EM-C031, EM-C041, EM-C020
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C014, EM-C015, EM-C018) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (konstante Oberstimmen über wanderndem Bass); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H060 – Moll-Tonika mit maj7-Subdominante (dorisch-lydisch)
- **Charakter:** melancholische Weite · **Säule:** A · **Modus/Tonvorrat:** dorisch {1, 2, ♭3, 4, 5, 6, ♭7}
- **XYZ-Anker:** 0,65 / 0,30 / 0,20 · **Gültigkeit:** X 0,45–0,85 · Y 0,10–0,50 · Z 0,00–0,40
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:m9*2 | 5:maj7#11*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-None | -12 | [-2, +2, +7, +15] | ♭7, 9, 5, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 7680 | 7680 | [4] maj7♯11 | -7 | [-1, +0, +9, +16] | ♯11/♭5, 5, 3, 7 | A | – |

- **Übergänge:** 1→2: gemeinsam {1}; gehalten keine; bewegt St1 -2→-1 (+1), St2 +2→+0 (-2), St3 +7→+9 (+2), St4 +15→+16 (+1); Bass +5
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U021; Zellen EM-C007, EM-C012, EM-C040, EM-C002, EM-C031
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C017, EM-C035) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten m9, maj7#11; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (erweiterte Farben); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H061 – Ausgedehnte Plagalkette über 8 Takte
- **Charakter:** lyrische Entwicklung · **Säule:** A · **Modus/Tonvorrat:** ionisch {1, 2, 3, 4, 5, 6, 7}
- **XYZ-Anker:** 0,70 / 0,35 / 0,25 · **Gültigkeit:** X 0,50–0,90 · Y 0,15–0,55 · Z 0,05–0,45
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:add9*1 | 9:m7*1 | 5:maj7*1 | 2:m7*1 | 9:m7/7*1 | 5:maj/9*1 | 7:sus4*1 | 5:add9*1`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 3840 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |
| 2 | 3840 | 3840 | [6] Moll-Sept | -15 | [-5, +0, +12, +16] | ♭7, ♭3, ♭3, 5 | A | – |
| 3 | 7680 | 3840 | [4] große Septime | -19 | [-3, +0, +12, +16] | 3, 5, 5, 7 | A | – |
| 4 | 11520 | 3840 | [2] Moll-Sept | -22 | [-3, +0, +12, +17] | 5, ♭7, ♭7, ♭3 | A | – |
| 5 | 15360 | 3840 | [6] Moll-Sept / Bass [5] | -17 | [-3, +0, +12, +16] | 1, ♭3, ♭3, 5 | A | – |
| 6 | 19200 | 3840 | [4] Dur / Bass [6] | -15 | [-3, +0, +12, +17] | 3, 5, 5, 1 | A | – |
| 7 | 23040 | 3840 | [5] sus4 | -17 | [-5, +0, +12, +14] | 1, 4/11, 4/11, 5 | A | – |
| 8 | 26880 | 3840 | [4] Dur-add9 | -19 | [-5, +0, +9, +17] | 9, 5, 3, 1 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, 3, 5}; gehalten -5, +12, +16; bewegt St2 +2→+0 (-2); Bass -3 · 2→3: gemeinsam {1, 3, 6}; gehalten +0, +12, +16; bewegt St1 -5→-3 (+2); Bass -4 · 3→4: gemeinsam {1, 4, 6}; gehalten -3, +0, +12; bewegt St4 +16→+17 (+1); Bass -3 · 4→5: gemeinsam {1, 6}; gehalten -3, +0, +12; bewegt St4 +17→+16 (-1); Bass +5 · 5→6: gemeinsam {1, 6}; gehalten -3, +0, +12; bewegt St4 +16→+17 (+1); Bass +2 · 6→7: gemeinsam {1}; gehalten +0, +12; bewegt St1 -3→-5 (-2), St4 +17→+14 (-3); Bass -2 · 7→8: gemeinsam {1, 5}; gehalten -5, +0; bewegt St3 +12→+9 (-3), St4 +14→+17 (+3); Bass -2
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U007, EM-U008, EM-U009, EM-U010, EM-U011, EM-U013, EM-U016, EM-U022; Zellen EM-C020, EM-C006, EM-C029, EM-C031, EM-C041
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C014, EM-C015, EM-C018) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, m7, maj, maj7, sus4; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** I – begründete Interpretation (Varianten der Terzkette); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H062 – Halbverminderte Farbe als Umfärbung der iv
- **Charakter:** Bitternis · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,30 / 0,30 / 0,35 · **Gültigkeit:** X 0,10–0,50 · Y 0,10–0,50 · Z 0,15–0,55
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `5:m7*2 | 2:m7b5*2 | 5:m7*2 | 0:madd9*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [4] Moll-Sept | -7 | [+0, +5, +8, +15] | 5, 1, ♭3, ♭7 | A | – |
| 2 | 7680 | 7680 | [2] halbvermindert | -10 | [+0, +5, +8, +14] | ♭7, ♭3, ♯11/♭5, 1 | A | – |
| 3 | 15360 | 7680 | [4] Moll-Sept | -7 | [+0, +5, +8, +15] | 5, 1, ♭3, ♭7 | A | – |
| 4 | 23040 | 7680 | [1] Moll-add9 | -12 | [+0, +2, +7, +15] | 1, 9, 5, ♭3 | A | offen (gr. Septime/kl. None) |

- **Übergänge:** 1→2: gemeinsam {1, 4, ♭6}; gehalten +0, +5, +8; bewegt St4 +15→+14 (-1); Bass -3 · 2→3: gemeinsam {1, 4, ♭6}; gehalten +0, +5, +8; bewegt St4 +14→+15 (+1); Bass +3 · 3→4: gemeinsam {1, ♭3}; gehalten +0, +15; bewegt St2 +5→+2 (-3), St3 +8→+7 (-1); Bass -5
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C025, EM-C027, EM-C032, EM-C039, EM-C045
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten m7, m7b5, madd9; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** N – nachgewiesenes Verfahren (Tagg: halbvermindert); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H063 – Dur-Tonika mit Moll-add9-Antwort einen Ton tiefer
- **Charakter:** Freude, die zweifelt · **Säule:** A · **Modus/Tonvorrat:** mixolydisch {1, 2, 3, 4, 5, 6, ♭7}
- **XYZ-Anker:** 0,75 / 0,40 / 0,25 · **Gültigkeit:** X 0,55–0,95 · Y 0,20–0,60 · Z 0,05–0,45
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:add9*2 | 10:add9*2 | 5:add9*2 | 0:add9*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |
| 2 | 7680 | 7680 | [♭7] Dur-add9 | -14 | [-2, +2, +12, +17] | 1, 3, 9, 5 | A | – |
| 3 | 15360 | 7680 | [4] Dur-add9 | -19 | [-3, +7, +12, +17] | 3, 9, 5, 1 | A | – |
| 4 | 23040 | 7680 | [1] Dur-add9 | -12 | [+2, +7, +12, +16] | 9, 5, 1, 3 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, 2}; gehalten +2, +12; bewegt St1 -5→-2 (+3), St4 +16→+17 (+1); Bass -2 · 2→3: gemeinsam {1, 4}; gehalten +12, +17; bewegt St1 -2→-3 (-1), St2 +2→+7 (+5); Bass -5 · 3→4: gemeinsam {1, 5}; gehalten +7, +12; bewegt St1 -3→+2 (+5), St4 +17→+16 (-1); Bass +7
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U007, EM-U011, EM-U016, EM-U030, EM-U034, EM-U041, EM-U044; Zellen EM-C029, EM-C031, EM-C020, EM-C007, EM-C012
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C014, EM-C015, EM-C018) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** I – begründete Interpretation (mixolydisches ♭VII); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H064 – Tragische Pendelterz i–♭VI im weiten Satz
- **Charakter:** Untergang, gefasst · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,30 / 0,65 / 0,20 · **Gültigkeit:** X 0,10–0,50 · Y 0,45–0,85 · Z 0,00–0,40
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:madd9*2 | 8:maj7*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 7680 | 7680 | [♭6] große Septime | -16 | [-5, +3, +12, +15] | 7, 5, 3, 5 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, ♭3, 5}; gehalten -5, +12, +15; bewegt St2 +2→+3 (+1); Bass -4
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C025, EM-C027, EM-C032, EM-C039, EM-C045
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten madd9, maj7; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** I – begründete Interpretation (Terzpendel); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H065 – Chromatischer Dreitoncluster eng
- **Charakter:** beklemmende Dichte · **Säule:** B · **Modus/Tonvorrat:** chromatisch {1, ♭2, 2, ♭3, 3, 4, ♯4/♭5, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,15 / 0,30 / 0,50 · **Gültigkeit:** X 0,00–0,35 · Y 0,10–0,50 · Z 0,30–0,70
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** eng
- **Progression (Notation):** `{0,1,2}:Cluster3*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | Klangobjekt „Cluster3“ {1, ♭2, 2} | -12 | [+1, +2, +12] | ♭9, 9, 1 | A | – |

- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil eng) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C004, EM-C015, EM-C019, EM-C005, EM-C014
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten Klangobjekt; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** N – nachgewiesenes Verfahren (Cluster (cuebycue: string clusters)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H066 – Vierton-Halbtonballung mit Tritonus-Anker
- **Charakter:** starre Bedrohung · **Säule:** B · **Modus/Tonvorrat:** chromatisch {1, ♭2, 2, ♭3, 3, 4, ♯4/♭5, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,10 / 0,35 / 0,40 · **Gültigkeit:** X 0,00–0,30 · Y 0,15–0,55 · Z 0,20–0,60
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** None
- **Progression (Notation):** `{0,6,7,8}:Ballung4*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | Klangobjekt „Ballung4“ {1, ♯4/♭5, 5, ♭6} | -12 | [-6, +0, +8, +19] | ♯11/♭5, 1, ♭6/♭13, 5 | A | – |

- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C021, EM-C004, EM-C015, EM-C019, EM-C005
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten Klangobjekt; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** N – nachgewiesenes Verfahren (Suoni-per-Dino-Typ (Halbtoncluster + Tritonus)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H067 – Gespreizter Cluster (gr. Septimen/kl. Nonen)
- **Charakter:** kalte Spannung · **Säule:** B · **Modus/Tonvorrat:** chromatisch {1, ♭2, 2, ♭3, 3, 4, ♯4/♭5, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,55 / 0,30 / 0,45 · **Gültigkeit:** X 0,35–0,75 · Y 0,10–0,50 · Z 0,25–0,65
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** weit
- **Progression (Notation):** `{0,1,2,3}:Spreizcluster*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | Klangobjekt „Spreizcluster“ {1, ♭2, 2, ♭3} | -12 | [+0, +2, +3, +13] | 1, 9, ♭3, ♭9 | A | – |

- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C002, EM-C033, EM-C007, EM-C012, EM-C017
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten Klangobjekt; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** I – begründete Interpretation (Cluster, Registerspreizung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H068 – Moll über ♭II-Dur (Polychord)
- **Charakter:** doppelbödige Gefahr · **Säule:** B · **Modus/Tonvorrat:** phrygisch {1, ♭2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,15 / 0,50 / 0,55 · **Gültigkeit:** X 0,00–0,35 · Y 0,30–0,70 · Z 0,35–0,75
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** weit
- **Progression (Notation):** `{0,3,7,1,5,8}:Polychord i/♭II*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | Klangobjekt „Polychord i/♭II“ {1, ♭2, ♭3, 4, 5, ♭6} | -12 | [-7, -4, +0, +3, +13, +19] | 4/11, ♭6/♭13, 1, ♭3, ♭9, 5 | A | – |

- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C004, EM-C014, EM-C025, EM-C027, EM-C032
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten Klangobjekt; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** N – nachgewiesenes Verfahren (Polytonalität (Corbella: politonali)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H069 – Dur über Tritonus-Dur (Polychord)
- **Charakter:** gleißende Unruhe · **Säule:** B · **Modus/Tonvorrat:** oktatonisch_HG {1, ♭2, ♭3, 3, ♯4/♭5, 5, 6, ♭7}
- **XYZ-Anker:** 0,70 / 0,55 / 0,65 · **Gültigkeit:** X 0,50–0,90 · Y 0,35–0,75 · Z 0,45–0,85
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** weit
- **Progression (Notation):** `{0,4,7,6,10,1}:Polychord I/♯IV*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | Klangobjekt „Polychord I/♯IV“ {1, ♭2, 3, ♯4/♭5, 5, ♭7} | -12 | [-6, -2, +0, +4, +13, +19] | ♯11/♭5, ♭7, 1, 3, ♭9, 5 | A | – |

- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C033, EM-C034, EM-C042, EM-C001, EM-C008
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten Klangobjekt; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** N – nachgewiesenes Verfahren (Polytonalität); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H070 – Quartenschichtung
- **Charakter:** fremd, ruhig · **Säule:** B · **Modus/Tonvorrat:** pentaton_moll {1, ♭3, 4, 5, ♭7}
- **XYZ-Anker:** 0,55 / 0,25 / 0,25 · **Gültigkeit:** X 0,35–0,75 · Y 0,05–0,45 · Z 0,05–0,45
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** weit
- **Progression (Notation):** `{0,5,10,3}:Quartenturm*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | Klangobjekt „Quartenturm“ {1, ♭3, 4, ♭7} | -12 | [-2, +0, +5, +15] | ♭7, 1, 4/11, ♭3 | A | – |

- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C040, EM-C003, EM-C011, EM-C042, EM-C013
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten Klangobjekt; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (quartale Klangobjekte); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H071 – Ganztonfeld
- **Charakter:** traumhaft, haltlos · **Säule:** B · **Modus/Tonvorrat:** ganzton {1, 2, 3, ♯4/♭5, ♭6, ♭7}
- **XYZ-Anker:** 0,65 / 0,20 / 0,45 · **Gültigkeit:** X 0,45–0,85 · Y 0,00–0,40 · Z 0,25–0,65
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** weit
- **Progression (Notation):** `{0,2,4,6,8,10}:Ganzton*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | Klangobjekt „Ganzton“ {1, 2, 3, ♯4/♭5, ♭6, ♭7} | -12 | [-4, -2, +0, +2, +6, +16] | ♭6/♭13, ♭7, 1, 9, ♯11/♭5, 3 | A | – |

- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C020, EM-C017, EM-C002, EM-C038, EM-C030
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten Klangobjekt; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (symmetrischer Tonvorrat (nicht belegt)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H072 – Oktatonisches Feld
- **Charakter:** lauernd, symmetrisch · **Säule:** B · **Modus/Tonvorrat:** oktatonisch_HG {1, ♭2, ♭3, 3, ♯4/♭5, 5, 6, ♭7}
- **XYZ-Anker:** 0,30 / 0,35 / 0,55 · **Gültigkeit:** X 0,10–0,50 · Y 0,15–0,55 · Z 0,35–0,75
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** weit
- **Progression (Notation):** `{0,1,3,4,6,7,9,10}:Oktatonik*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | Klangobjekt „Oktatonik“ {1, ♭2, ♭3, 3, ♯4/♭5, 5, 6, ♭7} | -12 | [-3, +1, +4, +6, +7, +15] | 6/13, ♭9, 3, ♯11/♭5, 5, ♭3 | A | – |

- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C016, EM-C018, EM-C036, EM-C046, EM-C001
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten Klangobjekt; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (symmetrischer Tonvorrat); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H073 – Pseudoserieller Siebenton-Vorrat
- **Charakter:** rationale Kälte · **Säule:** B · **Modus/Tonvorrat:** chromatisch {1, ♭2, 2, ♭3, 3, 4, ♯4/♭5, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,40 / 0,30 / 0,50 · **Gültigkeit:** X 0,20–0,60 · Y 0,10–0,50 · Z 0,30–0,70
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** weit
- **Progression (Notation):** `{0,1,4,5,6,9,11}:Pool7*8`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 30720 | Klangobjekt „Pool7“ {1, ♭2, 3, 4, ♯4/♭5, 6, 7} | -12 | [-7, -3, -1, +4, +13, +18] | 4/11, 6/13, 7, 3, ♭9, ♯11/♭5 | A | – |

- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C013, EM-C022, EM-C030, EM-C035, EM-C038
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten Klangobjekt; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** N – nachgewiesenes Verfahren (pseudoserieller Ansatz (Grove/Miceli)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H074 – Kerntöne mit wechselndem Farbton
- **Charakter:** kaum merkliche Verschiebung · **Säule:** B · **Modus/Tonvorrat:** chromatisch {1, ♭2, 2, ♭3, 3, 4, ♯4/♭5, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,45 / 0,25 / 0,30 · **Gültigkeit:** X 0,25–0,65 · Y 0,05–0,45 · Z 0,10–0,50
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** weit
- **Progression (Notation):** `{0,3,4,6,7,9}:Kern+2*4 | {0,3,4,6,7,9}:Kern+11*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | Klangobjekt „Kern+2“ {1, ♭3, 3, ♯4/♭5, 5, 6} | -12 | [-3, +0, +4, +6, +7, +15] | 6/13, 1, 3, ♯11/♭5, 5, ♭3 | A | – |
| 2 | 15360 | 15360 | Klangobjekt „Kern+11“ {1, ♭3, 3, ♯4/♭5, 5, 6} | -12 | [-3, +0, +4, +6, +7, +15] | 6/13, 1, 3, ♯11/♭5, 5, ♭3 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, ♭3, 3, ♯4/♭5, 5, 6}; gehalten -3, +0, +4, +6, +7, +15; bewegt keine; Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme); EM-T010 (Farbtonaustausch)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C038, EM-C042, EM-C003, EM-C010, EM-C011
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten Klangobjekt; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** N – nachgewiesenes Verfahren (Ut: 6 gemeinsame + wechselnder 7. Ton (Wilcox)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H075 – Moll-maj7 stehend (Noir-Farbe)
- **Charakter:** elegante Bedrohung · **Säule:** B · **Modus/Tonvorrat:** harm_moll {1, 2, ♭3, 4, 5, ♭6, 7}
- **XYZ-Anker:** 0,25 / 0,30 / 0,35 · **Gültigkeit:** X 0,05–0,45 · Y 0,10–0,50 · Z 0,15–0,55
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:mmaj7*8`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 30720 | [1] Moll mit gr. Septime | -12 | [-1, +3, +7, +12] | 7, ♭3, 5, 1 | A | – |

- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C027, EM-C032, EM-C039, EM-C045, EM-C001
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten mmaj7; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (erweiterte Mollfarbe); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H076 – Verminderter Septakkord als Mysteryfeld
- **Charakter:** unaufgelöste Frage · **Säule:** B · **Modus/Tonvorrat:** oktatonisch_GH {1, 2, ♭3, 4, ♯4/♭5, ♭6, 6, 7}
- **XYZ-Anker:** 0,40 / 0,25 / 0,55 · **Gültigkeit:** X 0,20–0,60 · Y 0,05–0,45 · Z 0,35–0,75
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:dim7*4 | 3:dim7*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | [1] vermindert-Sept | -12 | [-3, +0, +6, +15] | 6/13, 1, ♯11/♭5, ♭3 | A | – |
| 2 | 15360 | 15360 | [♭3] vermindert-Sept | -9 | [-3, +0, +6, +15] | ♯11/♭5, 6/13, ♭3, 1 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, ♭3, ♯4/♭5, 6}; gehalten -3, +0, +6, +15; bewegt keine; Bass +3
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C013, EM-C030, EM-C038, EM-C001, EM-C009
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten dim7; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (symmetrischer Klang, ohne Auflösung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H077 – Halbvermindert über tiefem Pedal
- **Charakter:** schleichende Gefahr · **Säule:** B · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,15 / 0,30 / 0,40 · **Gültigkeit:** X 0,00–0,35 · Y 0,10–0,50 · Z 0,20–0,60
- **Rollen:** LF (Oberstimmen), LB (Bass, Pedal) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `2:m7b5/0*4 | 0:madd9*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | [2] halbvermindert / Bass [1] | -12 | [-7, +2, +12, +20] | ♭3, 1, ♭7, ♯11/♭5 | A | – |
| 2 | 15360 | 15360 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |

- **Übergänge:** 1→2: gemeinsam {1, 2}; gehalten +2, +12; bewegt St1 -7→-5 (+2), St4 +20→+15 (-5); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass: Pedal (A/U je Segment)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C025, EM-C027, EM-C032, EM-C039, EM-C045
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten m7b5, madd9; Stimmführungs-Solver mit Gemeinsamton-Priorität; Pedalrolle
- **Evidenz:** I – begründete Interpretation (halbvermindert + Pedal); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H078 – Gleitende Parallelakkorde über Pedal
- **Charakter:** Schwindel · **Säule:** B · **Modus/Tonvorrat:** chromatisch {1, ♭2, 2, ♭3, 3, 4, ♯4/♭5, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,20 / 0,35 / 0,65 · **Gültigkeit:** X 0,00–0,40 · Y 0,15–0,55 · Z 0,45–0,85
- **Rollen:** LF (Oberstimmen), LB (Bass, Pedal) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** eng
- **Progression (Notation):** `0:min*1 | 11:min/0*1 | 10:min/0*1 | 11:min/0*1`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 3840 | [1] Moll | -12 | [+0, +3, +7, +12] | 1, ♭3, 5, 1 | A | – |
| 2 | 3840 | 3840 | [7] Moll / Bass [1] | -12 | [-1, +2, +6, +11] | 1, ♭3, 5, 1 | Pedal | – |
| 3 | 7680 | 3840 | [♭7] Moll / Bass [1] | -12 | [-2, +1, +5, +10] | 1, ♭3, 5, 1 | Pedal | – |
| 4 | 11520 | 3840 | [7] Moll / Bass [1] | -12 | [-1, +2, +6, +11] | 1, ♭3, 5, 1 | Pedal | – |

- **Übergänge:** 1→2: gemeinsam {}; gehalten keine; bewegt St1 +0→-1 (-1), St2 +3→+2 (-1), St3 +7→+6 (-1), St4 +12→+11 (-1); Bass +0 · 2→3: gemeinsam {}; gehalten keine; bewegt St1 -1→-2 (-1), St2 +2→+1 (-1), St3 +6→+5 (-1), St4 +11→+10 (-1); Bass +0 · 3→4: gemeinsam {}; gehalten keine; bewegt St1 -2→-1 (+1), St2 +1→+2 (+1), St3 +5→+6 (+1), St4 +10→+11 (+1); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass: Pedal (A/U je Segment)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil eng) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge EM-U028, EM-U040, EM-U045, EM-U048; Zellen EM-C005, EM-C014, EM-C037, EM-C004, EM-C015
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten min; Stimmführungs-Solver mit Gemeinsamton-Priorität; Pedalrolle
- **Evidenz:** E – eigenständige Gestaltung (Pedal + chromatische Parallelen); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H079 – Phrygisches Pendel i–♭II
- **Charakter:** bedrohliche Nähe · **Säule:** B · **Modus/Tonvorrat:** phrygisch {1, ♭2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,15 / 0,40 / 0,45 · **Gültigkeit:** X 0,00–0,35 · Y 0,20–0,60 · Z 0,25–0,65
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** None
- **Progression (Notation):** `0:min*2 | 1:maj*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll | -12 | [+0, +3, +7, +12] | 1, ♭3, 5, 1 | A | – |
| 2 | 7680 | 7680 | [♭2] Dur | -11 | [-4, +5, +8, +13] | 5, 3, 5, 1 | A | – |

- **Übergänge:** 1→2: gemeinsam {}; gehalten keine; bewegt St1 +0→-4 (-4), St2 +3→+5 (+2), St3 +7→+8 (+1), St4 +12→+13 (+1); Bass +1
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge EM-U028, EM-U040, EM-U045, EM-U048; Zellen EM-C004, EM-C014, EM-C025, EM-C027, EM-C032
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten maj, min; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (phrygische Halbtonnähe); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H080 – Lokrische ♭5-Fläche
- **Charakter:** Instabilität · **Säule:** B · **Modus/Tonvorrat:** chromatisch {1, ♭2, 2, ♭3, 3, 4, ♯4/♭5, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,15 / 0,25 / 0,60 · **Gültigkeit:** X 0,00–0,35 · Y 0,05–0,45 · Z 0,40–0,80
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:m7b5*4 | 0:dim*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | [1] halbvermindert | -12 | [-2, +0, +6, +15] | ♭7, 1, ♯11/♭5, ♭3 | A | – |
| 2 | 15360 | 15360 | [1] vermindert | -12 | [-6, +0, +6, +15] | ♯11/♭5, 1, ♯11/♭5, ♭3 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, ♭3, ♯4/♭5}; gehalten +0, +6, +15; bewegt St1 -2→-6 (-4); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C004, EM-C015, EM-C019, EM-C021, EM-C005
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten dim, m7b5; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (verminderte Quinte als Grund); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H081 – Tritonus-Dyadenfeld
- **Charakter:** nackte Spannung · **Säule:** B · **Modus/Tonvorrat:** chromatisch {1, ♭2, 2, ♭3, 3, 4, ♯4/♭5, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,25 / 0,20 / 0,45 · **Gültigkeit:** X 0,05–0,45 · Y 0,00–0,40 · Z 0,25–0,65
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `{0,6}:Tritonus*4 | {1,7}:Tritonus+1*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | Klangobjekt „Tritonus“ {1, ♯4/♭5} | -12 | [+0, +6, +12] | 1, ♯11/♭5, 1 | A | – |
| 2 | 15360 | 15360 | Klangobjekt „Tritonus+1“ {♭2, 5} | -11 | [-5, +7, +13] | ♯11/♭5, ♯11/♭5, 1 | A | – |

- **Übergänge:** 1→2: gemeinsam {}; gehalten keine; bewegt St1 +0→-5 (-5), St2 +6→+7 (+1), St3 +12→+13 (+1); Bass +1
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge EM-U047; Zellen EM-C005, EM-C014, EM-C016, EM-C018, EM-C032
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten Klangobjekt; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** N – nachgewiesenes Verfahren (Tritonus (Suoni per Dino)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H082 – Hexatonisches Schaukeln (übermäßig)
- **Charakter:** surreal, schwebend · **Säule:** B · **Modus/Tonvorrat:** hexaton_aug {1, ♭3, 3, 5, ♭6, 7}
- **XYZ-Anker:** 0,50 / 0,25 / 0,55 · **Gültigkeit:** X 0,30–0,70 · Y 0,05–0,45 · Z 0,35–0,75
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:aug*2 | 4:min*2 | 8:aug*2 | 0:min*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] übermäßig | -12 | [-4, +0, +4, +16] | ♭6/♭13, 1, 3, 3 | A | – |
| 2 | 7680 | 7680 | [3] Moll | -8 | [-5, -1, +4, +16] | ♭3, 5, 1, 1 | A | – |
| 3 | 15360 | 7680 | [♭6] übermäßig | -16 | [-4, +0, +4, +16] | 1, 3, ♭6/♭13, ♭6/♭13 | A | – |
| 4 | 23040 | 7680 | [1] Moll | -12 | [-5, +0, +7, +15] | 5, 1, 5, ♭3 | A | – |

- **Übergänge:** 1→2: gemeinsam {3}; gehalten +4, +16; bewegt St1 -4→-5 (-1), St2 +0→-1 (-1); Bass +4 · 2→3: gemeinsam {3}; gehalten +4, +16; bewegt St1 -5→-4 (+1), St2 -1→+0 (+1); Bass -8 · 3→4: gemeinsam {1}; gehalten +0; bewegt St1 -4→-5 (-1), St3 +4→+7 (+3), St4 +16→+15 (-1); Bass +4
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge EM-U028, EM-U040, EM-U045, EM-U048; Zellen EM-C033, EM-C017, EM-C030, EM-C001, EM-C008
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten aug, min; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (hexatonische Nachbarschaft); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H083 – Chromatische Dur-Medianten-Kette
- **Charakter:** Unwirklichkeit · **Säule:** B · **Modus/Tonvorrat:** chromatisch {1, ♭2, 2, ♭3, 3, 4, ♯4/♭5, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,65 / 0,35 / 0,50 · **Gültigkeit:** X 0,45–0,85 · Y 0,15–0,55 · Z 0,30–0,70
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:maj*2 | 8:maj*2 | 4:maj*2 | 0:maj*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Dur | -12 | [+0, +4, +7, +12] | 1, 3, 5, 1 | A | – |
| 2 | 7680 | 7680 | [♭6] Dur | -16 | [+0, +3, +8, +12] | 3, 5, 1, 3 | A | – |
| 3 | 15360 | 7680 | [3] Dur | -20 | [-4, +4, +8, +11] | 3, 1, 3, 5 | A | – |
| 4 | 23040 | 7680 | [1] Dur | -12 | [+0, +4, +7, +12] | 1, 3, 5, 1 | A | – |

- **Übergänge:** 1→2: gemeinsam {1}; gehalten +0, +12; bewegt St2 +4→+3 (-1), St3 +7→+8 (+1); Bass -4 · 2→3: gemeinsam {♭6}; gehalten +8; bewegt St1 +0→-4 (-4), St2 +3→+4 (+1), St4 +12→+11 (-1); Bass -4 · 3→4: gemeinsam {3}; gehalten +4; bewegt St1 -4→+0 (+4), St3 +8→+7 (-1), St4 +11→+12 (+1); Bass +8
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C020, EM-C007, EM-C012, EM-C017, EM-C040
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten maj; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (Medianten (nicht belegt, kein Verbot)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H084 – Konsonanter Dreiklang plus Nachbarton-Störung
- **Charakter:** gestörte Ruhe · **Säule:** B · **Modus/Tonvorrat:** chromatisch {1, ♭2, 2, ♭3, 3, 4, ♯4/♭5, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,30 / 0,25 / 0,45 · **Gültigkeit:** X 0,10–0,50 · Y 0,05–0,45 · Z 0,25–0,65
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `{0,3,7,8}:m(b6)*4 | {0,3,7,6}:m+♯4*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | Klangobjekt „m(b6)“ {1, ♭3, 5, ♭6} | -12 | [-4, +0, +7, +15] | ♭6/♭13, 1, 5, ♭3 | A | – |
| 2 | 15360 | 15360 | Klangobjekt „m+♯4“ {1, ♭3, ♯4/♭5, 5} | -12 | [-6, +0, +7, +15] | ♯11/♭5, 1, 5, ♭3 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, ♭3, 5}; gehalten +0, +7, +15; bewegt St1 -4→-6 (-2); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme); EM-T010 (Farbtonaustausch)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C016, EM-C018, EM-C025, EM-C027, EM-C032
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten Klangobjekt; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (Fremdton als Klangobjekt); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H085 – Zwölfton-Aggregat in drei Tetrachorden
- **Charakter:** totale Verdichtung · **Säule:** B · **Modus/Tonvorrat:** chromatisch {1, ♭2, 2, ♭3, 3, 4, ♯4/♭5, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,30 / 0,70 / 0,80 · **Gültigkeit:** X 0,10–0,50 · Y 0,50–0,90 · Z 0,60–1,00
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** weit
- **Progression (Notation):** `{0,1,4,5}:Tetra1*2 | {2,3,6,7}:Tetra2*2 | {8,9,10,11}:Tetra3*2 | {0,1,4,5}:Tetra1*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | Klangobjekt „Tetra1“ {1, ♭2, 3, 4} | -12 | [-7, +1, +12, +16] | 4/11, ♭9, 1, 3 | A | – |
| 2 | 7680 | 7680 | Klangobjekt „Tetra2“ {2, ♭3, ♯4/♭5, 5} | -10 | [-6, +2, +7, +15] | 3, 1, 4/11, ♭9 | A | – |
| 3 | 15360 | 7680 | Klangobjekt „Tetra3“ {♭6, 6, ♭7, 7} | -16 | [-3, -1, +10, +20] | ♭9, ♭3, 9, 1 | A | – |
| 4 | 23040 | 7680 | Klangobjekt „Tetra1“ {1, ♭2, 3, 4} | -12 | [-7, +1, +12, +16] | 4/11, ♭9, 1, 3 | A | – |

- **Übergänge:** 1→2: gemeinsam {}; gehalten keine; bewegt St1 -7→-6 (+1), St2 +1→+2 (+1), St3 +12→+7 (-5), St4 +16→+15 (-1); Bass +2 · 2→3: gemeinsam {}; gehalten keine; bewegt St1 -6→-3 (+3), St2 +2→-1 (-3), St3 +7→+10 (+3), St4 +15→+20 (+5); Bass -6 · 3→4: gemeinsam {}; gehalten keine; bewegt St1 -3→-7 (-4), St2 -1→+1 (+2), St3 +10→+12 (+2), St4 +20→+16 (-4); Bass +4
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C016, EM-C018, EM-C025, EM-C027, EM-C032
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten Klangobjekt; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** N – nachgewiesenes Verfahren (zwölftönige Fragmente (De Rosa, Argento-Trilogie)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H086 – B-A-C-H-Klangobjekt
- **Charakter:** verschlüsselte Strenge · **Säule:** B · **Modus/Tonvorrat:** chromatisch {1, ♭2, 2, ♭3, 3, 4, ♯4/♭5, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,40 / 0,30 / 0,40 · **Gültigkeit:** X 0,20–0,60 · Y 0,10–0,50 · Z 0,20–0,60
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** weit
- **Progression (Notation):** `{10,9,0,11}:BACH*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | Klangobjekt „BACH“ {1, 6, ♭7, 7} | -14 | [-2, +0, +11, +21] | 1, 9, ♭9, 7 | A | – |

- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C013, EM-C022, EM-C030, EM-C035, EM-C042
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten Klangobjekt; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** N – nachgewiesenes Verfahren (Tonbuchstaben-Kode (Morricone, Life Notes)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H087 – Sechstonfeld chromatisch aufsteigend (Ricercar-Typ)
- **Charakter:** gelehrte Unruhe · **Säule:** B · **Modus/Tonvorrat:** chromatisch {1, ♭2, 2, ♭3, 3, 4, ♯4/♭5, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,35 / 0,35 / 0,55 · **Gültigkeit:** X 0,15–0,55 · Y 0,15–0,55 · Z 0,35–0,75
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** weit
- **Progression (Notation):** `{0,1,2,3,4,5}:Hexachord-chrom*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | Klangobjekt „Hexachord-chrom“ {1, ♭2, 2, ♭3, 3, 4} | -12 | [-7, +0, +1, +3, +14, +16] | 4/11, 1, ♭9, ♭3, 9, 3 | A | – |

- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C001, EM-C008, EM-C009, EM-C024, EM-C044
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten Klangobjekt; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** N – nachgewiesenes Verfahren (chromatische Sechstonfolge (Frescobaldi-Kode, abstrahiert)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H088 – Dunkles Quint-Drone mit kleiner None
- **Charakter:** Grabesruhe · **Säule:** B · **Modus/Tonvorrat:** phrygisch {1, ♭2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,05 / 0,20 / 0,20 · **Gültigkeit:** X 0,00–0,25 · Y 0,00–0,40 · Z 0,00–0,40
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** weit
- **Progression (Notation):** `{0,7,1}:Quinte+♭9*8`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 30720 | Klangobjekt „Quinte+♭9“ {1, ♭2, 5} | -12 | [-5, +1, +12] | 5, ♭9, 1 | A | – |

- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C004, EM-C014, EM-C032, EM-C046, EM-C001
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten Klangobjekt; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** I – begründete Interpretation (Drone + Halbtonreibung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H089 – Akkordpendel Moll – Moll einen Tritonus entfernt
- **Charakter:** zerrissenes Bewusstsein · **Säule:** B · **Modus/Tonvorrat:** oktatonisch_HG {1, ♭2, ♭3, 3, ♯4/♭5, 5, 6, ♭7}
- **XYZ-Anker:** 0,20 / 0,40 / 0,70 · **Gültigkeit:** X 0,00–0,40 · Y 0,20–0,60 · Z 0,50–0,90
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** None
- **Progression (Notation):** `0:min*2 | 6:min*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll | -12 | [+0, +3, +7, +12] | 1, ♭3, 5, 1 | A | – |
| 2 | 7680 | 7680 | [♯4/♭5] Moll | -18 | [-3, +1, +6, +13] | ♭3, 5, 1, 5 | A | – |

- **Übergänge:** 1→2: gemeinsam {}; gehalten keine; bewegt St1 +0→-3 (-3), St2 +3→+1 (-2), St3 +7→+6 (-1), St4 +12→+13 (+1); Bass -6
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge EM-U028, EM-U040, EM-U045, EM-U048; Zellen EM-C005, EM-C014, EM-C004, EM-C015, EM-C016
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten min; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (Tritonusbeziehung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H090 – Verdichtendes Cluster über Grundton
- **Charakter:** wachsende Enge · **Säule:** B · **Modus/Tonvorrat:** chromatisch {1, ♭2, 2, ♭3, 3, 4, ♯4/♭5, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,10 / 0,60 / 0,60 · **Gültigkeit:** X 0,00–0,30 · Y 0,40–0,80 · Z 0,40–0,80
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** weit
- **Progression (Notation):** `{0,7}:Quinte*2 | {0,7,8}:+♭6*2 | {0,7,8,1}:+♭2*2 | {0,7,8,1,6}:+♯4*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | Klangobjekt „Quinte“ {1, 5} | -12 | [-5, +0, +12] | 5, 1, 1 | A | – |
| 2 | 7680 | 7680 | Klangobjekt „+♭6“ {1, 5, ♭6} | -12 | [-4, +8, +19] | ♭6/♭13, ♭6/♭13, 5 | A | – |
| 3 | 15360 | 7680 | Klangobjekt „+♭2“ {1, ♭2, 5, ♭6} | -12 | [-5, +1, +12, +20] | 5, ♭9, 1, ♭6/♭13 | A | – |
| 4 | 23040 | 7680 | Klangobjekt „+♯4“ {1, ♭2, ♯4/♭5, 5, ♭6} | -12 | [-6, -4, +1, +12, +19] | ♯11/♭5, ♭6/♭13, ♭9, 1, 5 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, 5}; gehalten keine; bewegt St1 -5→-4 (+1), St2 +0→+8 (+8), St3 +12→+19 (+7); Bass +0 · 2→3: gemeinsam {1, 5, ♭6}; gehalten keine; bewegt St1 -4→-5 (-1), St2 +8→+12 (+4), St3 +19→+20 (+1); Bass +0 · 3→4: gemeinsam {1, ♭2, 5, ♭6}; gehalten +1, +12; bewegt St1 -5→-6 (-1), St4 +20→+19 (-1); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C021, EM-C004, EM-C015, EM-C019, EM-C005
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten Klangobjekt; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** I – begründete Interpretation (schichtweise Verdichtung (Filmtracks: Contamination)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H091 – Moll-add9 (geschützt) über Halbtoncluster tief
- **Charakter:** Schönheit über dem Abgrund · **Säule:** AB · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,35 / 0,35 / 0,45 · **Gültigkeit:** X 0,15–0,55 · Y 0,15–0,55 · Z 0,25–0,65
- **Rollen:** LF (Oberstimmen), LB (Bass); zweite Schicht: KF · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** offen
- **Progression (Notation):** `0:madd9*4 || {1,2,3}:Tiefcluster*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| D | 0 | 15360 | Klangobjekt „Tiefcluster“ {♭2, 2, ♭3} (Rolle KF) | – | [-23, -22, -21] | dissonante Schicht | – | – |

- **Tonfunktionen:** Oberstimmen A; Bass A; Schicht D: U/F gegen die globale Harmonie, Schicht LF geschützt konsonant (K)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Reibungslage offen; Lage (Stil offen) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis der geschützten Schicht, Wechsel nur der dissonanten Schicht (Farbtonaustausch), Ereignisfeld
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C001, EM-C008, EM-C009, EM-C025, EM-C027
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten madd9; Stimmführungs-Solver mit Gemeinsamton-Priorität; Lagenregel offen; Schichtharmonie (lokal/global)
- **Evidenz:** N – nachgewiesenes Verfahren (doppelte Ästhetik (De Rosa)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H092 – Dur-add9 (geschützt) über Tritonus-Pedal
- **Charakter:** trügerische Helle · **Säule:** AB · **Modus/Tonvorrat:** ionisch {1, 2, 3, 4, 5, 6, 7}
- **XYZ-Anker:** 0,75 / 0,30 / 0,45 · **Gültigkeit:** X 0,55–0,95 · Y 0,10–0,50 · Z 0,25–0,65
- **Rollen:** LF (Oberstimmen), LB (Bass); zweite Schicht: LB2 · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:add9*4 || {6}:Tritonuspedal*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |
| D | 0 | 15360 | Klangobjekt „Tritonuspedal“ {♯4/♭5} (Rolle LB2) | – | [-18] | dissonante Schicht | – | – |

- **Tonfunktionen:** Oberstimmen A; Bass A; Schicht D: U/F gegen die globale Harmonie, Schicht LF geschützt konsonant (K)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis der geschützten Schicht, Wechsel nur der dissonanten Schicht (Farbtonaustausch), Ereignisfeld
- **Geeignete Kombinationen:** Übergänge EM-U007, EM-U011, EM-U016, EM-U030, EM-U041, EM-U044; Zellen EM-C006, EM-C029, EM-C031, EM-C041, EM-C020
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9; Stimmführungs-Solver mit Gemeinsamton-Priorität; Schichtharmonie (lokal/global)
- **Evidenz:** I – begründete Interpretation (Konsonanz in bedrohlichem Kontext); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H093 – Wiegenlied-Harmonik I–IV gegen Spreizcluster
- **Charakter:** verstörende Unschuld · **Säule:** AB · **Modus/Tonvorrat:** ionisch {1, 2, 3, 4, 5, 6, 7}
- **XYZ-Anker:** 0,80 / 0,25 / 0,60 · **Gültigkeit:** X 0,60–1,00 · Y 0,05–0,45 · Z 0,40–0,80
- **Rollen:** LF (Oberstimmen), LB (Bass); zweite Schicht: KF · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** eng
- **Progression (Notation):** `0:maj*2 | 5:maj/0*2 || {1,6,11}:Störfeld*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Dur | -12 | [+0, +4, +7, +12] | 1, 3, 5, 1 | A | – |
| 2 | 7680 | 7680 | [4] Dur / Bass [1] | -12 | [+0, +5, +9, +12] | 5, 1, 3, 5 | A | – |
| D | 0 | 15360 | Klangobjekt „Störfeld“ {♭2, ♯4/♭5, 7} (Rolle KF) | – | [+13, +23, +30] | dissonante Schicht | – | – |

- **Übergänge:** 1→2: gemeinsam {1}; gehalten +0, +12; bewegt St2 +4→+5 (+1), St3 +7→+9 (+2); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass A; Schicht D: U/F gegen die globale Harmonie, Schicht LF geschützt konsonant (K)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil eng) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis der geschützten Schicht, Wechsel nur der dissonanten Schicht (Farbtonaustausch), Ereignisfeld
- **Geeignete Kombinationen:** Übergänge EM-U022; Zellen EM-C006, EM-C029, EM-C031, EM-C041, EM-C020
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten maj; Stimmführungs-Solver mit Gemeinsamton-Priorität; Schichtharmonie (lokal/global)
- **Evidenz:** N – nachgewiesenes Verfahren (Spieluhr gegen Diskordanz (Untouchables, Giallo)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H094 – Dorisches Pendel gegen Pool7-Schicht
- **Charakter:** edle Unruhe · **Säule:** AB · **Modus/Tonvorrat:** dorisch {1, 2, ♭3, 4, 5, 6, ♭7}
- **XYZ-Anker:** 0,55 / 0,45 / 0,60 · **Gültigkeit:** X 0,35–0,75 · Y 0,25–0,65 · Z 0,40–0,80
- **Rollen:** LF (Oberstimmen), LB (Bass); zweite Schicht: KF · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** offen
- **Progression (Notation):** `0:madd9*2 | 5:add9*2 || {1,4,6,8,11}:Gegenpool*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 7680 | 7680 | [4] Dur-add9 | -7 | [-5, +0, +9, +17] | 9, 5, 3, 1 | A | – |
| D | 0 | 15360 | Klangobjekt „Gegenpool“ {♭2, 3, ♯4/♭5, ♭6, 7} (Rolle KF) | – | [+13, +16, +18, +20, +23] | dissonante Schicht | – | – |

- **Übergänge:** 1→2: gemeinsam {1, 5}; gehalten -5; bewegt St2 +2→+0 (-2), St3 +12→+9 (-3), St4 +15→+17 (+2); Bass +5
- **Tonfunktionen:** Oberstimmen A; Bass A; Schicht D: U/F gegen die globale Harmonie, Schicht LF geschützt konsonant (K)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Reibungslage offen; Lage (Stil offen) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis der geschützten Schicht, Wechsel nur der dissonanten Schicht (Farbtonaustausch), Ereignisfeld
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C002, EM-C007, EM-C012, EM-C040, EM-C003
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, madd9; Stimmführungs-Solver mit Gemeinsamton-Priorität; Lagenregel offen; Schichtharmonie (lokal/global)
- **Evidenz:** I – begründete Interpretation (doppelte Ästhetik); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H095 – Plagal-Terzkette über tiefem ♭2-Pedal
- **Charakter:** Zärtlichkeit unter Druck · **Säule:** AB · **Modus/Tonvorrat:** ionisch {1, 2, 3, 4, 5, 6, 7}
- **XYZ-Anker:** 0,70 / 0,35 / 0,50 · **Gültigkeit:** X 0,50–0,90 · Y 0,15–0,55 · Z 0,30–0,70
- **Rollen:** LF (Oberstimmen), LB (Bass); zweite Schicht: LB2 · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:add9*2 | 9:m7*2 | 5:maj7*2 | 0:add9*2 || {1}:♭2-Pedal*8`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |
| 2 | 7680 | 7680 | [6] Moll-Sept | -15 | [-5, +0, +12, +16] | ♭7, ♭3, ♭3, 5 | A | – |
| 3 | 15360 | 7680 | [4] große Septime | -19 | [-3, +0, +12, +16] | 3, 5, 5, 7 | A | – |
| 4 | 23040 | 7680 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |
| D | 0 | 30720 | Klangobjekt „♭2-Pedal“ {♭2} (Rolle LB2) | – | [-23] | dissonante Schicht | – | – |

- **Übergänge:** 1→2: gemeinsam {1, 3, 5}; gehalten -5, +12, +16; bewegt St2 +2→+0 (-2); Bass -3 · 2→3: gemeinsam {1, 3, 6}; gehalten +0, +12, +16; bewegt St1 -5→-3 (+2); Bass -4 · 3→4: gemeinsam {1, 3}; gehalten +12, +16; bewegt St1 -3→-5 (-2), St2 +0→+2 (+2); Bass +7
- **Tonfunktionen:** Oberstimmen A; Bass A; Schicht D: U/F gegen die globale Harmonie, Schicht LF geschützt konsonant (K)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis der geschützten Schicht, Wechsel nur der dissonanten Schicht (Farbtonaustausch), Ereignisfeld
- **Geeignete Kombinationen:** Übergänge EM-U007, EM-U008, EM-U009, EM-U010, EM-U011, EM-U016, EM-U030, EM-U041; Zellen EM-C020, EM-C006, EM-C029, EM-C031, EM-C041
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, m7, maj7; Stimmführungs-Solver mit Gemeinsamton-Priorität; Schichtharmonie (lokal/global)
- **Evidenz:** E – eigenständige Gestaltung (geschützte Konsonanz + Pedal); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H096 – Moll-add9 gegen Tritonus-Dyaden oben
- **Charakter:** schöner Schmerz, kaltes Licht · **Säule:** AB · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,40 / 0,30 / 0,55 · **Gültigkeit:** X 0,20–0,60 · Y 0,10–0,50 · Z 0,35–0,75
- **Rollen:** LF (Oberstimmen), LB (Bass); zweite Schicht: TU · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** crunch
- **Progression (Notation):** `0:madd9*4 || {6,0}:Tritonus hoch*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | [1] Moll-add9 | -12 | [+2, +3, +7, +12] | 9, ♭3, 5, 1 | A | eng (Halbton) |
| D | 0 | 15360 | Klangobjekt „Tritonus hoch“ {1, ♯4/♭5} (Rolle TU) | – | [+24, +30] | dissonante Schicht | – | – |

- **Tonfunktionen:** Oberstimmen A; Bass A; Schicht D: U/F gegen die globale Harmonie, Schicht LF geschützt konsonant (K)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Reibungslage crunch; Lage (Stil crunch) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis der geschützten Schicht, Wechsel nur der dissonanten Schicht (Farbtonaustausch), Ereignisfeld
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C010, EM-C013, EM-C030, EM-C043, EM-C042
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten madd9; Stimmführungs-Solver mit Gemeinsamton-Priorität; Lagenregel crunch; Schichtharmonie (lokal/global)
- **Evidenz:** I – begründete Interpretation (doppelte Ästhetik); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H097 – Halbschluss gegen Cluster-Fläche
- **Charakter:** unerfüllte Erwartung, bedroht · **Säule:** AB · **Modus/Tonvorrat:** harm_moll {1, 2, ♭3, 4, 5, ♭6, 7}
- **XYZ-Anker:** 0,30 / 0,55 / 0,65 · **Gültigkeit:** X 0,10–0,50 · Y 0,35–0,75 · Z 0,45–0,85
- **Rollen:** LF (Oberstimmen), LB (Bass); zweite Schicht: KF · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** None
- **Progression (Notation):** `5:m9*2 | 7:7sus4*2 || {8,9,10}:Clusterfläche*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [4] Moll-None | -7 | [+0, +7, +8, +15] | 5, 9, ♭3, ♭7 | A | eng (Halbton) |
| 2 | 7680 | 7680 | [5] Sept-sus4 | -17 | [+0, +2, +7, +17] | 4/11, 5, 1, ♭7 | A | – |
| D | 0 | 15360 | Klangobjekt „Clusterfläche“ {♭6, 6, ♭7} (Rolle KF) | – | [+20, +21, +22] | dissonante Schicht | – | – |

- **Übergänge:** 1→2: gemeinsam {1, 4, 5}; gehalten +0; bewegt St2 +7→+2 (-5), St3 +8→+7 (-1), St4 +15→+17 (+2); Bass -10
- **Tonfunktionen:** Oberstimmen A; Bass A; Schicht D: U/F gegen die globale Harmonie, Schicht LF geschützt konsonant (K)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis der geschützten Schicht, Wechsel nur der dissonanten Schicht (Farbtonaustausch), Ereignisfeld
- **Geeignete Kombinationen:** Übergänge EM-U014, EM-U015, EM-U037; Zellen EM-C027, EM-C032, EM-C039, EM-C045, EM-C001
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten 7sus4, m9; Stimmführungs-Solver mit Gemeinsamton-Priorität; Schichtharmonie (lokal/global)
- **Evidenz:** E – eigenständige Gestaltung (doppelte Ästhetik); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H098 – Lydisches Licht über chromatisch fallendem Bass
- **Charakter:** gleißende Bedrohung · **Säule:** AB · **Modus/Tonvorrat:** lydisch {1, 2, 3, ♯4/♭5, 5, 6, 7}
- **XYZ-Anker:** 0,85 / 0,40 / 0,55 · **Gültigkeit:** X 0,65–1,00 · Y 0,20–0,60 · Z 0,35–0,75
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:maj7*1 | 0:maj7/11*1 | 0:maj7/10*1 | 0:maj7/9*1`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 3840 | [1] große Septime | -12 | [-5, +0, +11, +16] | 5, 1, 7, 3 | A | – |
| 2 | 3840 | 3840 | [1] große Septime / Bass [7] | -13 | [-5, +0, +11, +16] | 5, 1, 7, 3 | A | – |
| 3 | 7680 | 3840 | [1] große Septime / Bass [♭7] | -14 | [-5, +0, +11, +16] | 5, 1, 7, 3 | F (dissonanzautorisiert) | – |
| 4 | 11520 | 3840 | [1] große Septime / Bass [6] | -15 | [-5, +0, +11, +16] | 5, 1, 7, 3 | F (dissonanzautorisiert) | – |

- **Übergänge:** 1→2: gemeinsam {1, 3, 5, 7}; gehalten -5, +0, +11, +16; bewegt keine; Bass -1 · 2→3: gemeinsam {1, 3, 5, 7}; gehalten -5, +0, +11, +16; bewegt keine; Bass -1 · 3→4: gemeinsam {1, 3, 5, 7}; gehalten -5, +0, +11, +16; bewegt keine; Bass -1
- **Tonfunktionen:** Oberstimmen A; Bass teils F (dissonanzautorisiert)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis der geschützten Schicht, Wechsel nur der dissonanten Schicht (Farbtonaustausch), Ereignisfeld
- **Geeignete Kombinationen:** Übergänge EM-U018, EM-U031; Zellen EM-C034, EM-C006, EM-C029, EM-C031, EM-C041
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten maj7; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (konsonante Oberstimmen, dissonanzautorisierter Bass); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H099 – Konsonante Moll-Fläche mit wanderndem Fremdton
- **Charakter:** Gift im Gesang · **Säule:** AB · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,35 / 0,25 / 0,50 · **Gültigkeit:** X 0,15–0,55 · Y 0,05–0,45 · Z 0,30–0,70
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** None
- **Progression (Notation):** `0:madd9*1 | {0,2,3,7,8}:+♭6*1 | {0,2,3,7,6}:+♯4*1 | 0:madd9*1`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 3840 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 3840 | 3840 | Klangobjekt „+♭6“ {1, 2, ♭3, 5, ♭6} | -12 | [-4, +0, +2, +7, +15] | ♭6/♭13, 1, 9, 5, ♭3 | A | – |
| 3 | 7680 | 3840 | Klangobjekt „+♯4“ {1, 2, ♭3, ♯4/♭5, 5} | -12 | [-6, +0, +2, +7, +15] | ♯11/♭5, 1, 9, 5, ♭3 | A | – |
| 4 | 11520 | 3840 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |

- **Übergänge:** 1→2: gemeinsam {1, 2, ♭3, 5}; gehalten +2, +15; bewegt St1 -5→-4 (+1), St3 +12→+15 (+3); Bass +0 · 2→3: gemeinsam {1, 2, ♭3, 5}; gehalten +0, +2, +7, +15; bewegt St1 -4→-6 (-2); Bass +0 · 3→4: gemeinsam {1, 2, ♭3, 5}; gehalten +2, +15; bewegt St1 -6→-5 (+1), St2 +0→+2 (+2), St4 +7→+2 (-5); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis der geschützten Schicht, Wechsel nur der dissonanten Schicht (Farbtonaustausch), Ereignisfeld
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C001, EM-C008, EM-C009, EM-C025, EM-C027
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten Klangobjekt, madd9; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** I – begründete Interpretation (Kern + wechselnder Farbton); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H100 – Monumentale Dur-Kette gegen dunkles Drone
- **Charakter:** Triumph mit Schatten · **Säule:** AB · **Modus/Tonvorrat:** ionisch {1, 2, 3, 4, 5, 6, 7}
- **XYZ-Anker:** 0,65 / 0,80 / 0,45 · **Gültigkeit:** X 0,45–0,85 · Y 0,60–1,00 · Z 0,25–0,65
- **Rollen:** LF (Oberstimmen), LB (Bass); zweite Schicht: LB2 · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:add9*2 | 5:maj*2 | 9:min*2 | 7:sus4*2 || {1,8}:Drone ♭2/♭6*8`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |
| 2 | 7680 | 7680 | [4] Dur | -7 | [-3, +0, +12, +17] | 3, 5, 5, 1 | A | – |
| 3 | 15360 | 7680 | [6] Moll | -15 | [-3, +0, +12, +16] | 1, ♭3, ♭3, 5 | A | – |
| 4 | 23040 | 7680 | [5] sus4 | -17 | [-5, +0, +12, +14] | 1, 4/11, 4/11, 5 | A | – |
| D | 0 | 30720 | Klangobjekt „Drone ♭2/♭6“ {♭2, ♭6} (Rolle LB2) | – | [-23, -16] | dissonante Schicht | – | – |

- **Übergänge:** 1→2: gemeinsam {1}; gehalten +12; bewegt St1 -5→-3 (+2), St2 +2→+0 (-2), St4 +16→+17 (+1); Bass +5 · 2→3: gemeinsam {1, 6}; gehalten -3, +0, +12; bewegt St4 +17→+16 (-1); Bass -8 · 3→4: gemeinsam {1}; gehalten +0, +12; bewegt St1 -3→-5 (-2), St4 +16→+14 (-2); Bass -2
- **Tonfunktionen:** Oberstimmen A; Bass A; Schicht D: U/F gegen die globale Harmonie, Schicht LF geschützt konsonant (K)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis der geschützten Schicht, Wechsel nur der dissonanten Schicht (Farbtonaustausch), Ereignisfeld
- **Geeignete Kombinationen:** Übergänge EM-U007, EM-U011, EM-U016, EM-U022, EM-U030, EM-U041, EM-U044; Zellen EM-C020, EM-C007, EM-C012, EM-C040, EM-C002
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, maj, min, sus4; Stimmführungs-Solver mit Gemeinsamton-Priorität; Schichtharmonie (lokal/global)
- **Evidenz:** E – eigenständige Gestaltung (doppelte Ästhetik, Monumentalität); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H101 – Dorisches i–IV mit chromatischer Mittelstimme
- **Charakter:** Zwielicht · **Säule:** AB · **Modus/Tonvorrat:** dorisch {1, 2, ♭3, 4, 5, 6, ♭7}
- **XYZ-Anker:** 0,45 / 0,30 / 0,55 · **Gültigkeit:** X 0,25–0,65 · Y 0,10–0,50 · Z 0,35–0,75
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** eng
- **Progression (Notation):** `0:min*1 | 8:maj/0*1 | 5:maj/0*1 | 0:m7*1`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 3840 | [1] Moll | -12 | [+0, +3, +7, +12] | 1, ♭3, 5, 1 | A | – |
| 2 | 3840 | 3840 | [♭6] Dur / Bass [1] | -12 | [+0, +3, +8, +12] | 3, 5, 1, 3 | A | – |
| 3 | 7680 | 3840 | [4] Dur / Bass [1] | -12 | [+0, +5, +9, +12] | 5, 1, 3, 5 | A | – |
| 4 | 11520 | 3840 | [1] Moll-Sept | -12 | [+3, +7, +10, +12] | ♭3, 5, ♭7, 1 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, ♭3}; gehalten +0, +3, +12; bewegt St3 +7→+8 (+1); Bass +0 · 2→3: gemeinsam {1}; gehalten +0, +12; bewegt St2 +3→+5 (+2), St3 +8→+9 (+1); Bass +0 · 3→4: gemeinsam {1}; gehalten +12; bewegt St1 +0→+3 (+3), St2 +5→+7 (+2), St3 +9→+10 (+1); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil eng) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis der geschützten Schicht, Wechsel nur der dissonanten Schicht (Farbtonaustausch), Ereignisfeld
- **Geeignete Kombinationen:** Übergänge EM-U022, EM-U028, EM-U040, EM-U045, EM-U048; Zellen EM-C042, EM-C003, EM-C010, EM-C011, EM-C013
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten m7, maj, min; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (chromatische Stimmführung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H102 – Moll-add9 über Phrygisch-Pendel im Bass
- **Charakter:** Gefahr hinter Melancholie · **Säule:** AB · **Modus/Tonvorrat:** phrygisch {1, ♭2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,25 / 0,35 / 0,50 · **Gültigkeit:** X 0,05–0,45 · Y 0,15–0,55 · Z 0,30–0,70
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** offen
- **Progression (Notation):** `0:madd9*2 | 0:madd9/1*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 7680 | 7680 | [1] Moll-add9 / Bass [♭2] | -11 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | F (dissonanzautorisiert) | offen (gr. Septime/kl. None) |

- **Übergänge:** 1→2: gemeinsam {1, 2, ♭3, 5}; gehalten -5, +2, +12, +15; bewegt keine; Bass +1
- **Tonfunktionen:** Oberstimmen A; Bass teils F (dissonanzautorisiert)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Reibungslage offen; Lage (Stil offen) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis der geschützten Schicht, Wechsel nur der dissonanten Schicht (Farbtonaustausch), Ereignisfeld
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C014, EM-C025, EM-C027, EM-C032, EM-C046
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten madd9; Stimmführungs-Solver mit Gemeinsamton-Priorität; Lagenregel offen
- **Evidenz:** E – eigenständige Gestaltung (dissonanzautorisierter Bass); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H103 – Kalte Mystery: sus2-Quinten über Ganztonbass
- **Charakter:** kristallin, unbestimmt · **Säule:** AB · **Modus/Tonvorrat:** ganzton {1, 2, 3, ♯4/♭5, ♭6, ♭7}
- **XYZ-Anker:** 0,80 / 0,20 / 0,45 · **Gültigkeit:** X 0,60–1,00 · Y 0,00–0,40 · Z 0,25–0,65
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:sus2*2 | 0:sus2/10*2 | 0:sus2/8*2 | 0:sus2/6*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] sus2 | -12 | [-5, +2, +12, +19] | 5, 9, 1, 5 | A | – |
| 2 | 7680 | 7680 | [1] sus2 / Bass [♭7] | -14 | [-5, +2, +12, +19] | 5, 9, 1, 5 | F (dissonanzautorisiert) | – |
| 3 | 15360 | 7680 | [1] sus2 / Bass [♭6] | -16 | [-5, +2, +12, +19] | 5, 9, 1, 5 | F (dissonanzautorisiert) | – |
| 4 | 23040 | 7680 | [1] sus2 / Bass [♯4/♭5] | -18 | [-5, +2, +12, +19] | 5, 9, 1, 5 | F (dissonanzautorisiert) | – |

- **Übergänge:** 1→2: gemeinsam {1, 2, 5}; gehalten -5, +2, +12, +19; bewegt keine; Bass -2 · 2→3: gemeinsam {1, 2, 5}; gehalten -5, +2, +12, +19; bewegt keine; Bass -2 · 3→4: gemeinsam {1, 2, 5}; gehalten -5, +2, +12, +19; bewegt keine; Bass -2
- **Tonfunktionen:** Oberstimmen A; Bass teils F (dissonanzautorisiert)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis der geschützten Schicht, Wechsel nur der dissonanten Schicht (Farbtonaustausch), Ereignisfeld
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C020, EM-C017, EM-C002, EM-C038, EM-C030
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten sus2; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (konsonante Oberstimmen über symmetrischem Bass); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H104 – Moll-add9 mit hohem ♭9-Glockenton
- **Charakter:** Totenglocke über Trauer · **Säule:** AB · **Modus/Tonvorrat:** phrygisch {1, ♭2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,20 / 0,30 / 0,40 · **Gültigkeit:** X 0,00–0,40 · Y 0,10–0,50 · Z 0,20–0,60
- **Rollen:** LF (Oberstimmen), LB (Bass); zweite Schicht: TU · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** offen
- **Progression (Notation):** `0:madd9*4 || {1}:♭9 hoch*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| D | 0 | 15360 | Klangobjekt „♭9 hoch“ {♭2} (Rolle TU) | – | [+25] | dissonante Schicht | – | – |

- **Tonfunktionen:** Oberstimmen A; Bass A; Schicht D: U/F gegen die globale Harmonie, Schicht LF geschützt konsonant (K)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Reibungslage offen; Lage (Stil offen) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme); EM-T010 (Farbtonaustausch)
- **Entwicklung:** Stasis der geschützten Schicht, Wechsel nur der dissonanten Schicht (Farbtonaustausch), Ereignisfeld
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C014, EM-C004, EM-C025, EM-C027, EM-C032
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten madd9; Stimmführungs-Solver mit Gemeinsamton-Priorität; Lagenregel offen; Schichtharmonie (lokal/global)
- **Evidenz:** E – eigenständige Gestaltung (geschützte Konsonanz + Fremdton-Schicht); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H105 – Tragik und Drohung: ♭VI–♭II über Tonikapedal
- **Charakter:** Schicksalsschwere · **Säule:** AB · **Modus/Tonvorrat:** phrygisch {1, ♭2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,15 / 0,80 / 0,50 · **Gültigkeit:** X 0,00–0,35 · Y 0,60–1,00 · Z 0,30–0,70
- **Rollen:** LF (Oberstimmen), LB (Bass, Pedal) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** weit
- **Progression (Notation):** `8:maj*2 | 1:maj/0*2 | 0:madd9*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [♭6] Dur | -12 | [-4, +0, +3, +15] | 1, 3, 5, 5 | A | – |
| 2 | 7680 | 7680 | [♭2] Dur / Bass [1] | -12 | [-4, +1, +5, +13] | 5, 1, 3, 1 | Pedal | – |
| 3 | 15360 | 15360 | [1] Moll-add9 | -12 | [-5, +0, +3, +14] | 5, 1, ♭3, 9 | A | offen (gr. Septime/kl. None) |

- **Übergänge:** 1→2: gemeinsam {♭6}; gehalten -4; bewegt St2 +0→+1 (+1), St3 +3→+5 (+2), St4 +15→+13 (-2); Bass +0 · 2→3: gemeinsam {}; gehalten keine; bewegt St1 -4→-5 (-1), St2 +1→+0 (-1), St3 +5→+3 (-2), St4 +13→+14 (+1); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass: Pedal (A/U je Segment)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis der geschützten Schicht, Wechsel nur der dissonanten Schicht (Farbtonaustausch), Ereignisfeld
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C004, EM-C014, EM-C025, EM-C027, EM-C032
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten madd9, maj; Stimmführungs-Solver mit Gemeinsamton-Priorität; Pedalrolle
- **Evidenz:** E – eigenständige Gestaltung (Pedal + phrygische Harmonik); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H106 – Tiefe Moll-add9-Lage über Grundtonpedal
- **Charakter:** dunkle, stehende Bedrohung · **Säule:** AB · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,10 / 0,10 / 0,10 · **Gültigkeit:** X 0,00–0,30 · Y 0,00–0,30 · Z 0,00–0,30
- **Rollen:** LF (Oberstimmen), LB (Bass, Pedal) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** offen
- **Progression (Notation):** `0:madd9*4 | 8:maj7/0*4`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 15360 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 15360 | 15360 | [♭6] große Septime / Bass [1] | -12 | [-5, +0, +8, +15] | 7, 3, 1, 5 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, ♭3, 5}; gehalten -5, +15; bewegt St2 +2→+0 (-2), St3 +12→+8 (-4); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass: Pedal (A/U je Segment)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Reibungslage offen; Lage (Stil offen) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis der geschützten Schicht, Wechsel nur der dissonanten Schicht (Farbtonaustausch), Ereignisfeld
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C025, EM-C027, EM-C032, EM-C039, EM-C045
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten madd9, maj7; Stimmführungs-Solver mit Gemeinsamton-Priorität; Lagenregel offen; Pedalrolle
- **Evidenz:** I – begründete Interpretation (madd9 (Tagg) + Pedal, tiefe Lage); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H107 – Halbtonschatten über Tonikapedal
- **Charakter:** dunkel, leise schwankend · **Säule:** B · **Modus/Tonvorrat:** phrygisch {1, ♭2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,10 / 0,10 / 0,50 · **Gültigkeit:** X 0,00–0,30 · Y 0,00–0,30 · Z 0,30–0,70
- **Rollen:** LF (Oberstimmen), LB (Bass, Pedal) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** eng
- **Progression (Notation):** `0:min*2 | 1:maj/0*2 | 0:min*2 | 11:dim/0*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll | -12 | [+0, +3, +7, +12] | 1, ♭3, 5, 1 | A | – |
| 2 | 7680 | 7680 | [♭2] Dur / Bass [1] | -12 | [+1, +5, +8, +13] | 1, 3, 5, 1 | Pedal | – |
| 3 | 15360 | 7680 | [1] Moll | -12 | [+0, +3, +7, +12] | 1, ♭3, 5, 1 | A | – |
| 4 | 23040 | 7680 | [7] vermindert / Bass [1] | -12 | [-1, +2, +5, +11] | 1, ♭3, ♯11/♭5, 1 | Pedal | – |

- **Übergänge:** 1→2: gemeinsam {}; gehalten keine; bewegt St1 +0→+1 (+1), St2 +3→+5 (+2), St3 +7→+8 (+1), St4 +12→+13 (+1); Bass +0 · 2→3: gemeinsam {}; gehalten keine; bewegt St1 +1→+0 (-1), St2 +5→+3 (-2), St3 +8→+7 (-1), St4 +13→+12 (-1); Bass +0 · 3→4: gemeinsam {}; gehalten keine; bewegt St1 +0→-1 (-1), St2 +3→+2 (-1), St3 +7→+5 (-2), St4 +12→+11 (-1); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass: Pedal (A/U je Segment)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil eng) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge EM-U028, EM-U040, EM-U045, EM-U048; Zellen EM-C004, EM-C014, EM-C025, EM-C027, EM-C032
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten dim, maj, min; Stimmführungs-Solver mit Gemeinsamton-Priorität; Pedalrolle
- **Evidenz:** E – eigenständige Gestaltung (Pedal + chromatische Nachbarklänge); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H108 – Tritonusballung tief, unruhig wechselnd
- **Charakter:** lauernde Instabilität · **Säule:** B · **Modus/Tonvorrat:** chromatisch {1, ♭2, 2, ♭3, 3, 4, ♯4/♭5, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,10 / 0,15 / 0,90 · **Gültigkeit:** X 0,00–0,30 · Y 0,00–0,35 · Z 0,70–1,00
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** weit
- **Progression (Notation):** `{0,1,6}:Tritonusballung*2 | {0,6,7}:Tritonusballung gespiegelt*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | Klangobjekt „Tritonusballung“ {1, ♭2, ♯4/♭5} | -12 | [-6, +1, +12] | ♯11/♭5, ♭9, 1 | A | – |
| 2 | 7680 | 7680 | Klangobjekt „Tritonusballung gespiegelt“ {1, ♯4/♭5, 5} | -12 | [-5, +6, +12] | 5, ♯11/♭5, 1 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, ♯4/♭5}; gehalten +12; bewegt St1 -6→-5 (+1), St2 +1→+6 (+5); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C021, EM-C004, EM-C015, EM-C019, EM-C005
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten Klangobjekt; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** N – nachgewiesenes Verfahren (Suoni-per-Dino-Typ (Halbton + Tritonus)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H109 – Dunkle Moll-Subdominante, stehend
- **Charakter:** schwer, ohne Ausweg · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,10 / 0,50 / 0,10 · **Gültigkeit:** X 0,00–0,30 · Y 0,30–0,70 · Z 0,00–0,30
- **Rollen:** LF (Oberstimmen), LB (Bass, Pedal) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** None
- **Progression (Notation):** `0:m7*2 | 5:m7/0*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-Sept | -12 | [-2, +0, +7, +15] | ♭7, 1, 5, ♭3 | A | – |
| 2 | 7680 | 7680 | [4] Moll-Sept / Bass [1] | -12 | [-4, +0, +5, +15] | ♭3, 5, 1, ♭7 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, ♭3}; gehalten +0, +15; bewegt St1 -2→-4 (-2), St3 +7→+5 (-2); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass: Pedal (A/U je Segment)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C025, EM-C027, EM-C032, EM-C039, EM-C045
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten m7; Stimmführungs-Solver mit Gemeinsamton-Priorität; Pedalrolle
- **Evidenz:** I – begründete Interpretation (plagale Mollbewegung über Pedal); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H110 – Phrygischer Halbtondruck
- **Charakter:** drängende Gefahr · **Säule:** B · **Modus/Tonvorrat:** phrygisch {1, ♭2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,10 / 0,50 / 0,90 · **Gültigkeit:** X 0,00–0,30 · Y 0,30–0,70 · Z 0,70–1,00
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** None
- **Progression (Notation):** `0:min*1 | 1:maj*1 | 0:min*1 | 1:maj7*1`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 3840 | [1] Moll | -12 | [+0, +3, +7, +12] | 1, ♭3, 5, 1 | A | – |
| 2 | 3840 | 3840 | [♭2] Dur | -11 | [-4, +5, +8, +13] | 5, 3, 5, 1 | A | – |
| 3 | 7680 | 3840 | [1] Moll | -12 | [+0, +3, +7, +12] | 1, ♭3, 5, 1 | A | – |
| 4 | 11520 | 3840 | [♭2] große Septime | -11 | [+0, +5, +8, +12] | 7, 3, 5, 7 | A | – |

- **Übergänge:** 1→2: gemeinsam {}; gehalten keine; bewegt St1 +0→-4 (-4), St2 +3→+5 (+2), St3 +7→+8 (+1), St4 +12→+13 (+1); Bass +1 · 2→3: gemeinsam {}; gehalten keine; bewegt St1 -4→+0 (+4), St2 +5→+3 (-2), St3 +8→+7 (-1), St4 +13→+12 (-1); Bass -1 · 3→4: gemeinsam {1}; gehalten +0, +12; bewegt St2 +3→+5 (+2), St3 +7→+8 (+1); Bass +1
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge EM-U028, EM-U040, EM-U045, EM-U048; Zellen EM-C004, EM-C014, EM-C025, EM-C027, EM-C032
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten maj, maj7, min; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (♭II-Pendel, chromatisch); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H111 – Tragischer Orgelpunkt, monumental dunkel
- **Charakter:** Verhängnis in breiten Flächen · **Säule:** A · **Modus/Tonvorrat:** aeolisch {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **XYZ-Anker:** 0,15 / 0,90 / 0,10 · **Gültigkeit:** X 0,00–0,35 · Y 0,70–1,00 · Z 0,00–0,30
- **Rollen:** LF (Oberstimmen), LB (Bass, Pedal) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:madd9*2 | 8:maj/0*2 | 5:m7/0*2 | 7:sus4/0*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Moll-add9 | -12 | [-5, +2, +12, +15] | 5, 9, 1, ♭3 | A | offen (gr. Septime/kl. None) |
| 2 | 7680 | 7680 | [♭6] Dur / Bass [1] | -12 | [-4, +0, +12, +15] | 1, 3, 3, 5 | A | – |
| 3 | 15360 | 7680 | [4] Moll-Sept / Bass [1] | -12 | [-4, +5, +12, +15] | ♭3, 1, 5, ♭7 | A | – |
| 4 | 23040 | 7680 | [5] sus4 / Bass [1] | -12 | [-5, +2, +12, +19] | 1, 5, 4/11, 1 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, ♭3}; gehalten +12, +15; bewegt St1 -5→-4 (+1), St2 +2→+0 (-2); Bass +0 · 2→3: gemeinsam {1, ♭3, ♭6}; gehalten -4, +12, +15; bewegt St2 +0→+5 (+5); Bass +0 · 3→4: gemeinsam {1}; gehalten +12; bewegt St1 -4→-5 (-1), St2 +5→+2 (-3), St4 +15→+19 (+4); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass: Pedal (A/U je Segment)
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020; Zellen EM-C025, EM-C027, EM-C032, EM-C039, EM-C045
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C015, EM-C016, EM-C035, EM-C036) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten m7, madd9, maj, sus4; Stimmführungs-Solver mit Gemeinsamton-Priorität; Pedalrolle
- **Evidenz:** I – begründete Interpretation (madd9 + Pedal; aufgeschobene Auflösung (Smith)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H112 – Moll gegen Tritonus und ♭II
- **Charakter:** bedrohliche Action · **Säule:** B · **Modus/Tonvorrat:** chromatisch {1, ♭2, 2, ♭3, 3, 4, ♯4/♭5, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,10 / 0,90 / 0,90 · **Gültigkeit:** X 0,00–0,30 · Y 0,70–1,00 · Z 0,70–1,00
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** None
- **Progression (Notation):** `0:min*1 | 6:dim*1 | 1:maj*1 | 0:min*1`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 3840 | [1] Moll | -12 | [+0, +3, +7, +12] | 1, ♭3, 5, 1 | A | – |
| 2 | 3840 | 3840 | [♯4/♭5] vermindert | -18 | [+0, +6, +9, +12] | ♯11/♭5, 1, ♭3, ♯11/♭5 | A | – |
| 3 | 7680 | 3840 | [♭2] Dur | -11 | [-4, +5, +8, +13] | 5, 3, 5, 1 | A | – |
| 4 | 11520 | 3840 | [1] Moll | -12 | [+0, +3, +7, +12] | 1, ♭3, 5, 1 | A | – |

- **Übergänge:** 1→2: gemeinsam {1}; gehalten +0, +12; bewegt St2 +3→+6 (+3), St3 +7→+9 (+2); Bass -6 · 2→3: gemeinsam {}; gehalten keine; bewegt St1 +0→-4 (-4), St2 +6→+5 (-1), St3 +9→+8 (-1), St4 +12→+13 (+1); Bass +7 · 3→4: gemeinsam {}; gehalten keine; bewegt St1 -4→+0 (+4), St2 +5→+3 (-2), St3 +8→+7 (-1), St4 +13→+12 (-1); Bass -1
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge EM-U028, EM-U040, EM-U045, EM-U048; Zellen EM-C021, EM-C004, EM-C015, EM-C019, EM-C005
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten dim, maj, min; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (chromatische Blockverschiebung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H113 – Zwei Ganztonfelder im Wechsel
- **Charakter:** schwerelos und verunsichert · **Säule:** B · **Modus/Tonvorrat:** chromatisch {1, ♭2, 2, ♭3, 3, 4, ♯4/♭5, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,50 / 0,15 / 0,90 · **Gültigkeit:** X 0,30–0,70 · Y 0,00–0,35 · Z 0,70–1,00
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** weit
- **Progression (Notation):** `{0,2,4,6}:Ganztonfeld A*2 | {1,3,5,7}:Ganztonfeld B*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | Klangobjekt „Ganztonfeld A“ {1, 2, 3, ♯4/♭5} | -12 | [-6, +2, +12, +16] | ♯11/♭5, 9, 1, 3 | A | – |
| 2 | 7680 | 7680 | Klangobjekt „Ganztonfeld B“ {♭2, ♭3, 4, 5} | -11 | [-5, +3, +13, +17] | ♯11/♭5, 9, 1, 3 | A | – |

- **Übergänge:** 1→2: gemeinsam {}; gehalten keine; bewegt St1 -6→-5 (+1), St2 +2→+3 (+1), St3 +12→+13 (+1), St4 +16→+17 (+1); Bass +1
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge EM-U047; Zellen EM-C003, EM-C011, EM-C026, EM-C028, EM-C038
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten Klangobjekt; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** I – begründete Interpretation (symmetrische Tonvorräte); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H114 – Mollblöcke im Kleinterzabstand
- **Charakter:** mechanische Unruhe, kraftvoll · **Säule:** B · **Modus/Tonvorrat:** oktatonisch_HG {1, ♭2, ♭3, 3, ♯4/♭5, 5, 6, ♭7}
- **XYZ-Anker:** 0,50 / 0,90 / 0,90 · **Gültigkeit:** X 0,30–0,70 · Y 0,70–1,00 · Z 0,70–1,00
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** None
- **Progression (Notation):** `0:min*1 | 3:min*1 | 6:min*1 | 9:min*1`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 3840 | [1] Moll | -12 | [+0, +3, +7, +12] | 1, ♭3, 5, 1 | A | – |
| 2 | 3840 | 3840 | [♭3] Moll | -9 | [-2, +3, +6, +15] | 5, 1, ♭3, 1 | A | – |
| 3 | 7680 | 3840 | [♯4/♭5] Moll | -6 | [-3, +1, +6, +18] | ♭3, 5, 1, 1 | A | – |
| 4 | 11520 | 3840 | [6] Moll | -15 | [-3, +0, +9, +16] | 1, ♭3, 1, 5 | A | – |

- **Übergänge:** 1→2: gemeinsam {♭3}; gehalten +3; bewegt St1 +0→-2 (-2), St3 +7→+6 (-1), St4 +12→+15 (+3); Bass +3 · 2→3: gemeinsam {♯4/♭5}; gehalten +6; bewegt St1 -2→-3 (-1), St2 +3→+1 (-2), St4 +15→+18 (+3); Bass +3 · 3→4: gemeinsam {6}; gehalten -3; bewegt St2 +1→+0 (-1), St3 +6→+9 (+3), St4 +18→+16 (-2); Bass -9
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge EM-U028, EM-U040, EM-U045, EM-U048; Zellen EM-C042, EM-C033, EM-C001, EM-C008, EM-C044
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten min; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (oktatonische Blockverschiebung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H115 – Lydisches Licht mit Quart-Quint-Reibung
- **Charakter:** kaltes Licht, gestört · **Säule:** AB · **Modus/Tonvorrat:** lydisch {1, 2, 3, ♯4/♭5, 5, 6, 7}
- **XYZ-Anker:** 0,90 / 0,15 / 0,90 · **Gültigkeit:** X 0,70–1,00 · Y 0,00–0,35 · Z 0,70–1,00
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:maj7*2 | {0,6,7,11}:lydischer Reibungsklang*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] große Septime | -12 | [-5, +0, +11, +16] | 5, 1, 7, 3 | A | – |
| 2 | 7680 | 7680 | Klangobjekt „lydischer Reibungsklang“ {1, ♯4/♭5, 5, 7} | -12 | [-5, +0, +11, +18] | 5, 1, 7, ♯11/♭5 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, 5, 7}; gehalten -5, +0, +11; bewegt St4 +16→+18 (+2); Bass +0
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis der geschützten Schicht, Wechsel nur der dissonanten Schicht (Farbtonaustausch), Ereignisfeld
- **Geeignete Kombinationen:** Übergänge EM-U018, EM-U031; Zellen EM-C034, EM-C006, EM-C029, EM-C031, EM-C041
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten Klangobjekt, maj7; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (helle Fläche + geschützte Reibung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H116 – Dur-add9 mit übermäßigem Schatten
- **Charakter:** helle Unruhe, zweideutig · **Säule:** AB · **Modus/Tonvorrat:** dur_moll_gemischt {1, 2, ♭3, 3, 4, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,90 / 0,50 / 0,90 · **Gültigkeit:** X 0,70–1,00 · Y 0,30–0,70 · Z 0,70–1,00
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** None
- **Progression (Notation):** `0:add9*2 | 0:aug*2 | 4:min*2 | 0:add9*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |
| 2 | 7680 | 7680 | [1] übermäßig | -12 | [-4, +0, +12, +16] | ♭6/♭13, 1, 1, 3 | A | – |
| 3 | 15360 | 7680 | [3] Moll | -8 | [-5, +4, +11, +16] | ♭3, 1, 5, 1 | A | – |
| 4 | 23040 | 7680 | [1] Dur-add9 | -12 | [-5, +4, +14, +16] | 5, 3, 9, 3 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, 3}; gehalten +12, +16; bewegt St1 -5→-4 (+1), St2 +2→+0 (-2); Bass +0 · 2→3: gemeinsam {3}; gehalten +16; bewegt St1 -4→-5 (-1), St2 +0→+4 (+4), St3 +12→+11 (-1); Bass +4 · 3→4: gemeinsam {3, 5}; gehalten -5, +4, +16; bewegt St3 +11→+14 (+3); Bass -4
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis der geschützten Schicht, Wechsel nur der dissonanten Schicht (Farbtonaustausch), Ereignisfeld
- **Geeignete Kombinationen:** Übergänge EM-U007, EM-U011, EM-U016, EM-U030, EM-U041, EM-U044; Zellen EM-C006, EM-C029, EM-C031, EM-C041, EM-C020
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, aug, min; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (Dur/Moll- und Ganztonfärbung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H117 – Hymnische Helle mit plagaler Weite
- **Charakter:** groß, hell, nicht triumphierend · **Säule:** A · **Modus/Tonvorrat:** ionisch {1, 2, 3, 4, 5, 6, 7}
- **XYZ-Anker:** 0,90 / 0,90 / 0,10 · **Gültigkeit:** X 0,70–1,00 · Y 0,70–1,00 · Z 0,00–0,30
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:add9*2 | 5:add9/0*2 | 9:m7*2 | 5:maj7*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |
| 2 | 7680 | 7680 | [4] Dur-add9 / Bass [1] | -12 | [-5, +0, +9, +17] | 9, 5, 3, 1 | A | – |
| 3 | 15360 | 7680 | [6] Moll-Sept | -15 | [-5, +0, +9, +16] | ♭7, ♭3, 1, 5 | A | – |
| 4 | 23040 | 7680 | [4] große Septime | -19 | [-7, +0, +9, +16] | 1, 5, 3, 7 | A | – |

- **Übergänge:** 1→2: gemeinsam {1, 5}; gehalten -5; bewegt St2 +2→+0 (-2), St3 +12→+9 (-3), St4 +16→+17 (+1); Bass +0 · 2→3: gemeinsam {1, 5, 6}; gehalten -5, +0, +9; bewegt St4 +17→+16 (-1); Bass -3 · 3→4: gemeinsam {1, 3, 6}; gehalten +0, +9, +16; bewegt St1 -5→-7 (-2); Bass -4
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Umfärbung, Atmung (gestaffelte Einsätze), Rotation mit verwandten H-Vorlagen
- **Geeignete Kombinationen:** Übergänge EM-U007, EM-U008, EM-U009, EM-U010, EM-U011, EM-U016, EM-U030, EM-U034; Zellen EM-C006, EM-C029, EM-C031, EM-C041, EM-C020
- **Ungeeignete Kombinationen:** Zellen mit überwiegend modusfremden Tönen (EM-C014, EM-C015, EM-C018) außer als ausdrücklich deklarierte D-Schicht; dissonanzautorisierte Bässe (Typ DIS) bei Z < 0,5
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, m7, maj7; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** I – begründete Interpretation (plagale Bewegung, add9, offener Schluss); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H118 – Helle Kraft mit Moll-Subdominante
- **Charakter:** leuchtend und schmerzlich · **Säule:** AB · **Modus/Tonvorrat:** dur_moll_gemischt {1, 2, ♭3, 3, 4, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,90 / 0,90 / 0,50 · **Gültigkeit:** X 0,70–1,00 · Y 0,70–1,00 · Z 0,30–0,70
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 8 Takte (30720 Ticks) · **Stil:** weit
- **Progression (Notation):** `0:add9*2 | 5:min*2 | 8:maj*2 | 0:add9*2`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 7680 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |
| 2 | 7680 | 7680 | [4] Moll | -7 | [-4, +0, +12, +17] | ♭3, 5, 5, 1 | A | – |
| 3 | 15360 | 7680 | [♭6] Dur | -16 | [-4, +0, +12, +15] | 1, 3, 3, 5 | A | – |
| 4 | 23040 | 7680 | [1] Dur-add9 | -12 | [-5, +2, +12, +16] | 5, 9, 1, 3 | A | – |

- **Übergänge:** 1→2: gemeinsam {1}; gehalten +12; bewegt St1 -5→-4 (+1), St2 +2→+0 (-2), St4 +16→+17 (+1); Bass +5 · 2→3: gemeinsam {1, ♭6}; gehalten -4, +0, +12; bewegt St4 +17→+15 (-2); Bass -9 · 3→4: gemeinsam {1}; gehalten +12; bewegt St1 -4→-5 (-1), St2 +0→+2 (+2), St4 +15→+16 (+1); Bass +4
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil weit) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis der geschützten Schicht, Wechsel nur der dissonanten Schicht (Farbtonaustausch), Ereignisfeld
- **Geeignete Kombinationen:** Übergänge EM-U007, EM-U011, EM-U016, EM-U023, EM-U030, EM-U038, EM-U041, EM-U044; Zellen EM-C006, EM-C029, EM-C031, EM-C041, EM-C020
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten add9, maj, min; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** I – begründete Interpretation (Dur/Moll-Umfärbung (iv, ♭VI in Dur)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-H119 – Dur-Blöcke im Ganztonabstand
- **Charakter:** hell, mechanisch getrieben · **Säule:** B · **Modus/Tonvorrat:** chromatisch {1, ♭2, 2, ♭3, 3, 4, ♯4/♭5, 5, ♭6, 6, ♭7, 7}
- **XYZ-Anker:** 0,90 / 0,90 / 0,90 · **Gültigkeit:** X 0,70–1,00 · Y 0,70–1,00 · Z 0,70–1,00
- **Rollen:** LF (Oberstimmen), LB (Bass) · **Takt:** 4/4 · **Zyklus:** 4 Takte (15360 Ticks) · **Stil:** None
- **Progression (Notation):** `0:maj*1 | 2:maj*1 | 4:maj*1 | 6:maj*1`

| # | Tick | Dauer | Klang | Bass (rel) | Oberstimmen (rel) | Rollen im Akkord | Bassfunktion | Reibung |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 3840 | [1] Dur | -12 | [+0, +4, +7, +12] | 1, 3, 5, 1 | A | – |
| 2 | 3840 | 3840 | [2] Dur | -10 | [-3, +2, +6, +14] | 5, 1, 3, 1 | A | – |
| 3 | 7680 | 3840 | [3] Dur | -8 | [-1, +4, +8, +11] | 5, 1, 3, 5 | A | – |
| 4 | 11520 | 3840 | [♯4/♭5] Dur | -6 | [-2, +1, +6, +13] | 3, 5, 1, 5 | A | – |

- **Übergänge:** 1→2: gemeinsam {}; gehalten keine; bewegt St1 +0→-3 (-3), St2 +4→+2 (-2), St3 +7→+6 (-1), St4 +12→+14 (+2); Bass +2 · 2→3: gemeinsam {}; gehalten keine; bewegt St1 -3→-1 (+2), St2 +2→+4 (+2), St3 +6→+8 (+2), St4 +14→+11 (-3); Bass +2 · 3→4: gemeinsam {}; gehalten keine; bewegt St1 -1→-2 (-1), St2 +4→+1 (-3), St3 +8→+6 (-2), St4 +11→+13 (+2); Bass +2
- **Tonfunktionen:** Oberstimmen A; Bass A
- **Identität:** Folge der Klangqualitäten und Bassstufen; Lage (Stil None) ist Teil der Identität, Oktavierung des Gesamtsatzes nicht.
- **Transformation:** EM-T009 (Umfärbung eines Melodietons), EM-T012 (gestaffelter Aufbau), EM-T016 (Stasis), EM-T013/EM-T014 (Reduktion/Wiederaufnahme)
- **Entwicklung:** Stasis, Ereignisfeld, Verdichtung nur an XYZ-Übergängen, Reduktion und Wiederaufnahme
- **Geeignete Kombinationen:** Übergänge – (Vorlage als Feld); Zellen EM-C034, EM-C006, EM-C029, EM-C031, EM-C041
- **Ungeeignete Kombinationen:** Kombination mit einer zweiten harmonietragenden Fläche ohne gemeinsame Töne; ST darf keine Tonhöhenrolle übernehmen
- **Algorithmische Voraussetzungen:** Akkordqualitäten maj; Stimmführungs-Solver mit Gemeinsamton-Priorität
- **Evidenz:** E – eigenständige Gestaltung (Blockverschiebung, symmetrisch); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

## 7. U – Harmonische Übergänge und Stimmführung (höchste Priorität)

Jeder Übergang ist eine Kette von Zuständen mit exakten relativen Tonhöhen aller Stimmen (vier Oberstimmen LF + Bass LB; Polychord-Ziel mit sechs Oberstimmen). Zustand 0 ist vorgegeben, Folgezustände wurden mit dem Solver unter den Haltewünschen bestimmt und maschinell geprüft: Akkordidentität, tatsächliches Halten (im gerenderten MIDI über den Wechselzeitpunkt hinweg), Bewegungsintervalle (keine Stimme > Quinte), keine Quint-/Oktavparallelen, Vorhaltauflösung. Wechsel am Takt 2 (Tick 3840), sofern nicht anders angegeben; Zustände dauern bis zum nächsten Zustand bzw. einen Takt.

### EM-U001 – Liegende None wird Terz (i-add9 → ♭VII-add9)
- **Modus:** aeolisch · **XYZ-Anker:** 0,45 / 0,30 / 0,20 · **Gültigkeit:** X 0,30–0,60 · Y 0,10–0,50 · Z 0,00–0,40 · **Takt:** 4/4
- **Auflösungsabsicht:** modale Fortsetzung, keine Auflösungspflicht

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Moll-add9 | t (Tonika) | -12 | [+0, +3, +7, +14] | 1, ♭3, 5, 9 |
| 1 | 3840 | [♭7] Dur-add9 | ♭VII (modale Subtonika) | -14 | [+0, +2, +5, +14] | 9, 3, 5, 3 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 2} · tatsächlich gehalten: +0 (Rolle 1 → 9, Tonfunktion A→A), +14 (Rolle 9 → 3, Tonfunktion A→A) · bewegt: Stimme 2: +3→+2, ↓kl. Sekunde (-1); Stimme 3: +7→+5, ↓gr. Sekunde (-2) · Bass ↓gr. Sekunde (-2)
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung –
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** N – nachgewiesenes Verfahren (Am(add9)→G(add9): A und H bleiben liegen (Soundfly, korrigierte Akkordbezeichnung)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U002 – Drei liegende Töne zur ♭VI-maj7
- **Modus:** aeolisch · **XYZ-Anker:** 0,40 / 0,30 / 0,15 · **Gültigkeit:** X 0,25–0,55 · Y 0,10–0,50 · Z 0,00–0,35 · **Takt:** 4/4
- **Auflösungsabsicht:** weiches Absinken ohne Auflösungsziel

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Moll-add9 | t | -12 | [+0, +3, +7, +14] | 1, ♭3, 5, 9 |
| 1 | 3840 | [♭6] große Septime | ♭VI (Tonikagegenklang) | -16 | [+0, +3, +7, +15] | 3, 5, 7, 5 |

- **Wechsel 0→1:** Gemeinsamtöne {1, ♭3, 5} · tatsächlich gehalten: +0 (Rolle 1 → 3, Tonfunktion A→A), +3 (Rolle ♭3 → 5, Tonfunktion A→A), +7 (Rolle 5 → 7, Tonfunktion A→A) · bewegt: Stimme 4: +14→+15, ↑kl. Sekunde (+1) · Bass ↓gr. Terz (-4)
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung –
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** I – begründete Interpretation (Gemeinsamton-Priorität); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U003 – Moll-Plagalschritt mit None-Bindung (i → iv-add9)
- **Modus:** aeolisch · **XYZ-Anker:** 0,30 / 0,30 / 0,15 · **Gültigkeit:** X 0,15–0,45 · Y 0,10–0,50 · Z 0,00–0,35 · **Takt:** 4/4
- **Auflösungsabsicht:** plagale Bewegung, offen für Rückkehr

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Moll-add9 | t | -12 | [-5, +2, +3, +7] | 5, 9, ♭3, 5 |
| 1 | 3840 | [4] Moll-add9 | s (Mollsubdominante) | -7 | [-5, +0, +7, +8] | 9, 5, 9, ♭3 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 5} · tatsächlich gehalten: -5 (Rolle 5 → 9, Tonfunktion A→A) · bewegt: Stimme 2: +2→+0, ↓gr. Sekunde (-2); Stimme 3: +3→+7, ↑gr. Terz (+4); Stimme 4: +7→+8, ↑kl. Sekunde (+1) · Bass ↑Quarte (+5)
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung EM-U043, EM-U049
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** I – begründete Interpretation (plagale Moll-Bewegung, madd9 (Tagg)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U004 – Dorische Aufhellung (i-add9 → IV-add9)
- **Modus:** dorisch · **XYZ-Anker:** 0,55 / 0,30 / 0,20 · **Gültigkeit:** X 0,40–0,70 · Y 0,10–0,50 · Z 0,00–0,40 · **Takt:** 4/4
- **Auflösungsabsicht:** Umfärbung ♭3→♮6-Raum, kein Ziel

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Moll-add9 | t | -12 | [+0, +3, +7, +14] | 1, ♭3, 5, 9 |
| 1 | 3840 | [4] Dur-add9 | S (Dur-Subdominante, dorisch) | -7 | [+0, +5, +7, +9] | 5, 1, 9, 3 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 5} · tatsächlich gehalten: +0 (Rolle 1 → 5, Tonfunktion A→A), +7 (Rolle 5 → 9, Tonfunktion A→A) · bewegt: Stimme 2: +3→+5, ↑gr. Sekunde (+2); Stimme 4: +14→+9, ↓Quarte (-5) · Bass ↑Quarte (+5)
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung EM-U034
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** N – nachgewiesenes Verfahren (i–IV–i (filmmusicnotes: Cheyenne)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U005 – Terzumkehrung bei liegendem Klang
- **Modus:** aeolisch · **XYZ-Anker:** 0,35 / 0,25 / 0,30 · **Gültigkeit:** X 0,20–0,50 · Y 0,05–0,45 · Z 0,10–0,50 · **Takt:** 4/4
- **Auflösungsabsicht:** Bewegung nur im Bass, Klangidentität bleibt

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Moll-add9 | t | -12 | [-5, +2, +3, +7] | 5, 9, ♭3, 5 |
| 1 | 3840 | [1] Moll-add9 | t⁶ (Tonika, Terz im Bass) | -9 | [-5, +2, +3, +12] | 5, 9, ♭3, 1 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 2, ♭3, 5} · tatsächlich gehalten: -5 (Rolle 5 → 5, Tonfunktion A→A), +2 (Rolle 9 → 9, Tonfunktion A→A), +3 (Rolle ♭3 → ♭3, Tonfunktion A→A) · bewegt: Stimme 4: +7→+12, ↑Quarte (+5) · Bass ↑kl. Terz (+3)
- **Hinweis Solver:** Zustand 1: nur 3 von 4 gewünschten Haltetönen lösbar (alle gemeinsamen Pitch-Classes, die in beiden Voicings vorkommen, bleiben dennoch gehalten – siehe Prüfung).
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020, EM-U024, EM-U027
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** E – eigenständige Gestaltung (Umkehrung als Bassbewegung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U006 – Liegende Sexte wird None (iv-m6 → i-add9)
- **Modus:** dorisch · **XYZ-Anker:** 0,45 / 0,25 / 0,15 · **Gültigkeit:** X 0,30–0,60 · Y 0,05–0,45 · Z 0,00–0,35 · **Takt:** 4/4
- **Auflösungsabsicht:** plagale Rückkehr, sanft

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [4] Moll-Sexte | s⁶ (dorische Subdominante) | -7 | [+0, +2, +5, +8] | 5, 6/13, 1, ♭3 |
| 1 | 3840 | [1] Moll-add9 | t | -12 | [+0, +2, +3, +7] | 1, 9, ♭3, 5 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 2} · tatsächlich gehalten: +0 (Rolle 5 → 1, Tonfunktion A→A), +2 (Rolle 6/13 → 9, Tonfunktion A→A) · bewegt: Stimme 3: +5→+3, ↓gr. Sekunde (-2); Stimme 4: +8→+7, ↓kl. Sekunde (-1) · Bass ↓Quarte (-5)
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020, EM-U024, EM-U027
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** I – begründete Interpretation (plagal, Gemeinsamton-Funktionswechsel); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U007 – Plagal-Terzkette Schritt 1 (I-add9 → vi-m7)
- **Modus:** ionisch · **XYZ-Anker:** 0,75 / 0,30 / 0,15 · **Gültigkeit:** X 0,60–0,90 · Y 0,10–0,50 · Z 0,00–0,35 · **Takt:** 4/4
- **Auflösungsabsicht:** Terzfall im Bass, Fortsetzung zu IV erwartet

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Dur-add9 | T | -12 | [-5, +2, +4, +12] | 5, 9, 3, 1 |
| 1 | 3840 | [6] Moll-Sept | Tp (Tonikaparallele) | -15 | [-5, +0, +4, +12] | ♭7, ♭3, 5, ♭3 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 3, 5} · tatsächlich gehalten: -5 (Rolle 5 → ♭7, Tonfunktion A→A), +4 (Rolle 3 → 5, Tonfunktion A→A), +12 (Rolle 1 → ♭3, Tonfunktion A→A) · bewegt: Stimme 2: +2→+0, ↓gr. Sekunde (-2) · Bass ↓kl. Terz (-3)
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung EM-U008, EM-U010
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** N – nachgewiesenes Verfahren (I–vi–IV–I (filmmusicnotes)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U008 – Plagal-Terzkette Schritt 2 (vi-m7 → IV-maj7)
- **Modus:** ionisch · **XYZ-Anker:** 0,75 / 0,30 / 0,15 · **Gültigkeit:** X 0,60–0,90 · Y 0,10–0,50 · Z 0,00–0,35 · **Takt:** 4/4
- **Auflösungsabsicht:** weiterer Terzfall, offen

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [6] Moll-Sept | Tp | -15 | [-5, +0, +4, +9] | ♭7, ♭3, 5, 1 |
| 1 | 3840 | [4] große Septime | S | -19 | [-7, +0, +4, +9] | 1, 5, 7, 3 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 3, 6} · tatsächlich gehalten: +0 (Rolle ♭3 → 5, Tonfunktion A→A), +4 (Rolle 5 → 7, Tonfunktion A→A), +9 (Rolle 1 → 3, Tonfunktion A→A) · bewegt: Stimme 1: -5→-7, ↓gr. Sekunde (-2) · Bass ↓gr. Terz (-4)
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung EM-U009, EM-U042
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** N – nachgewiesenes Verfahren (Plagal-Terzkette); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U009 – Plagal-Terzkette Schluss (IV-maj7 → I-add9)
- **Modus:** ionisch · **XYZ-Anker:** 0,75 / 0,25 / 0,10 · **Gültigkeit:** X 0,60–0,90 · Y 0,05–0,45 · Z 0,00–0,30 · **Takt:** 4/4
- **Auflösungsabsicht:** plagaler Schluss, ruhig

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [4] große Septime | S | -19 | [-3, +0, +4, +9] | 3, 5, 7, 3 |
| 1 | 3840 | [1] Dur-add9 | T | -12 | [-5, +0, +4, +14] | 5, 1, 3, 9 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 3} · tatsächlich gehalten: +0 (Rolle 5 → 1, Tonfunktion A→A), +4 (Rolle 7 → 3, Tonfunktion A→A) · bewegt: Stimme 1: -3→-5, ↓gr. Sekunde (-2); Stimme 4: +9→+14, ↑Quarte (+5) · Bass ↑Quinte (+7)
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung EM-U007, EM-U011, EM-U016, EM-U030, EM-U041, EM-U044
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** N – nachgewiesenes Verfahren (Plagal-Terzkette); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U010 – iii-Einschub (vi-m7 → iii-m7)
- **Modus:** ionisch · **XYZ-Anker:** 0,70 / 0,25 / 0,20 · **Gültigkeit:** X 0,55–0,85 · Y 0,05–0,45 · Z 0,00–0,40 · **Takt:** 4/4
- **Auflösungsabsicht:** Zwischenstation zur IV

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [6] Moll-Sept | Tp | -15 | [-5, +0, +4, +9] | ♭7, ♭3, 5, 1 |
| 1 | 3840 | [3] Moll-Sept | Dp (Dominantparallele) | -8 | [-5, +2, +4, +11] | ♭3, ♭7, 1, 5 |

- **Wechsel 0→1:** Gemeinsamtöne {3, 5} · tatsächlich gehalten: -5 (Rolle ♭7 → ♭3, Tonfunktion A→A), +4 (Rolle 5 → 1, Tonfunktion A→A) · bewegt: Stimme 2: +0→+2, ↑gr. Sekunde (+2); Stimme 4: +9→+11, ↑gr. Sekunde (+2) · Bass ↑Quinte (+7)
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung –
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** N – nachgewiesenes Verfahren ((I)–vi–(iii)–IV–I (filmmusicnotes)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U011 – Stufenweiser Bass 1→7 (I-add9 → V/7)
- **Modus:** ionisch · **XYZ-Anker:** 0,75 / 0,35 / 0,20 · **Gültigkeit:** X 0,60–0,90 · Y 0,15–0,55 · Z 0,00–0,40 · **Takt:** 4/4
- **Auflösungsabsicht:** Durchgangsakkord, Bass weiter abwärts erwartet

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Dur-add9 | T | -12 | [-5, +2, +4, +12] | 5, 9, 3, 1 |
| 1 | 3840 | [5] Dur | D⁶ (Durchgang) | -13 | [-5, +2, +7, +11] | 1, 5, 1, 3 |

- **Wechsel 0→1:** Gemeinsamtöne {2, 5} · tatsächlich gehalten: -5 (Rolle 5 → 1, Tonfunktion A→A), +2 (Rolle 9 → 5, Tonfunktion A→A) · bewegt: Stimme 3: +4→+7, ↑kl. Terz (+3); Stimme 4: +12→+11, ↓kl. Sekunde (-1) · Bass ↓kl. Sekunde (-1)
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung –
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** I – begründete Interpretation (stufenweise gefüllte Terzkette); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U012 – Durchgang V-add9/7 → vi-m7 mit liegender None
- **Modus:** ionisch · **XYZ-Anker:** 0,70 / 0,35 / 0,20 · **Gültigkeit:** X 0,55–0,85 · Y 0,15–0,55 · Z 0,00–0,40 · **Takt:** 4/4
- **Auflösungsabsicht:** Bassschritt 7→6, Oberstimmen fast liegend

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [5] Dur-add9 | D⁶ (Durchgang) | -13 | [-5, +2, +9, +11] | 1, 5, 9, 3 |
| 1 | 3840 | [6] Moll-Sept | Tp | -15 | [-5, +4, +9, +12] | ♭7, 5, 1, ♭3 |

- **Wechsel 0→1:** Gemeinsamtöne {5, 6} · tatsächlich gehalten: -5 (Rolle 1 → ♭7, Tonfunktion A→A), +9 (Rolle 9 → 1, Tonfunktion A→A) · bewegt: Stimme 2: +2→+4, ↑gr. Sekunde (+2); Stimme 4: +11→+12, ↑kl. Sekunde (+1) · Bass ↓gr. Sekunde (-2)
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung EM-U008, EM-U010
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** E – eigenständige Gestaltung (stufenweiser Bass, Gemeinsamtöne); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U013 – Nur der Bass geht: ii-m7 → V-7sus4
- **Modus:** ionisch · **XYZ-Anker:** 0,65 / 0,35 / 0,35 · **Gültigkeit:** X 0,50–0,80 · Y 0,15–0,55 · Z 0,15–0,55 · **Takt:** 4/4
- **Auflösungsabsicht:** Halbschluss, Auflösung aufgeschoben

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [2] Moll-Sept | Sp | -10 | [+0, +5, +9, +14] | ♭7, ♭3, 5, 1 |
| 1 | 3840 | [5] Sept-sus4 | D (sus, Halbschluss) | -17 | [+0, +5, +7, +14] | 4/11, ♭7, 1, 5 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 2, 4} · tatsächlich gehalten: +0 (Rolle ♭7 → 4/11, Tonfunktion A→A), +5 (Rolle ♭3 → ♭7, Tonfunktion A→A), +14 (Rolle 1 → 5, Tonfunktion A→A) · bewegt: Stimme 3: +9→+7, ↓gr. Sekunde (-2) · Bass ↓Quinte (-7)
- **Zulässige Fortsetzungen:** stimmgleich anschließend EM-U014, EM-U015, EM-U037; mit Neuverteilung –
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** N – nachgewiesenes Verfahren (aufgeschobene Auflösung (Smith)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U014 – Quartvorhalt mit Auflösungsziel (V-7sus4 → V-7)
- **Modus:** ionisch · **XYZ-Anker:** 0,60 / 0,35 / 0,40 · **Gültigkeit:** X 0,45–0,75 · Y 0,15–0,55 · Z 0,20–0,60 · **Takt:** 4/4
- **Auflösungsabsicht:** Vorhalt C→H löst nach einem halben Takt auf

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [5] Sept-sus4 | D (sus) | -17 | [+0, +5, +7, +14] | 4/11, ♭7, 1, 5 |
| 1 | 3840 | [5] Dominantsept | D⁷ | -17 | [-1, +5, +7, +14] | 3, ♭7, 1, 5 |

- **Wechsel 0→1:** Gemeinsamtöne {2, 4, 5} · tatsächlich gehalten: +5 (Rolle ♭7 → ♭7, Tonfunktion A→A), +7 (Rolle 1 → 1, Tonfunktion A→A), +14 (Rolle 5 → 5, Tonfunktion A→A) · bewegt: Stimme 1: +0→-1, ↓kl. Sekunde (-1) · Bass gehalten
- **Vorhalt:** in Zustand 1 erklingt +0 statt -1 (Funktion V), Auflösung nach 1920 Ticks auf -1
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung –
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“, Vorhalt mit Ziel; Stimmführungs-Solver
- **Evidenz:** I – begründete Interpretation (Vorhalt mit Auflösungsziel); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U015 – Seltene funktionale Auflösung (V-7sus4 → I-add9)
- **Modus:** ionisch · **XYZ-Anker:** 0,70 / 0,40 / 0,15 · **Gültigkeit:** X 0,55–0,85 · Y 0,20–0,60 · Z 0,00–0,35 · **Takt:** 4/4
- **Auflösungsabsicht:** funktionale Auflösung, sparsam einsetzen

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [5] Sept-sus4 | D (sus) | -17 | [+0, +5, +7, +14] | 4/11, ♭7, 1, 5 |
| 1 | 3840 | [1] Dur-add9 | T | -12 | [+0, +4, +7, +14] | 1, 3, 5, 9 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 2, 5} · tatsächlich gehalten: +0 (Rolle 4/11 → 1, Tonfunktion A→A), +7 (Rolle 1 → 5, Tonfunktion A→A), +14 (Rolle 5 → 9, Tonfunktion A→A) · bewegt: Stimme 2: +5→+4, ↓kl. Sekunde (-1) · Bass ↑Quarte (+5)
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung EM-U007, EM-U011, EM-U016, EM-U030, EM-U041, EM-U044
- **Ungeeignete Kombinationen:** EM-U013 (direkt nach funktionaler Auflösung erneuter Halbschluss: Kadenzmechanik); generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** I – begründete Interpretation (Kadenz als Ausnahme); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U016 – Dur→Moll bei gleichem Grundton (eine Stimme sinkt)
- **Modus:** dur_moll_gemischt · **XYZ-Anker:** 0,50 / 0,25 / 0,30 · **Gültigkeit:** X 0,35–0,65 · Y 0,05–0,45 · Z 0,10–0,50 · **Takt:** 4/4
- **Auflösungsabsicht:** Umfärbung, kein Funktionswechsel

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Dur-add9 | T (Dur) | -12 | [-5, +2, +4, +12] | 5, 9, 3, 1 |
| 1 | 3840 | [1] Moll-add9 | t (Moll) | -12 | [-5, +2, +3, +12] | 5, 9, ♭3, 1 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 2, 5} · tatsächlich gehalten: -5 (Rolle 5 → 5, Tonfunktion A→A), +2 (Rolle 9 → 9, Tonfunktion A→A), +12 (Rolle 1 → 1, Tonfunktion A→A) · bewegt: Stimme 3: +4→+3, ↓kl. Sekunde (-1) · Bass gehalten
- **Zulässige Fortsetzungen:** stimmgleich anschließend EM-U017; mit Neuverteilung EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U019, EM-U020, EM-U024, EM-U027, EM-U029
- **Ungeeignete Kombinationen:** EM-U017 (sofortiges Zurückschalten Moll→Dur wirkt als Flackern; nur bei hohem Z); generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** N – nachgewiesenes Verfahren (Dur/Moll-Wechsel); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U017 – Moll→Dur bei gleichem Grundton (Aufhellung)
- **Modus:** dur_moll_gemischt · **XYZ-Anker:** 0,60 / 0,30 / 0,25 · **Gültigkeit:** X 0,45–0,75 · Y 0,10–0,50 · Z 0,05–0,45 · **Takt:** 4/4
- **Auflösungsabsicht:** Aufhellung ohne Triumph

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Moll-add9 | t | -12 | [-5, +2, +3, +12] | 5, 9, ♭3, 1 |
| 1 | 3840 | [1] Dur-add9 | T | -12 | [-5, +2, +4, +12] | 5, 9, 3, 1 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 2, 5} · tatsächlich gehalten: -5 (Rolle 5 → 5, Tonfunktion A→A), +2 (Rolle 9 → 9, Tonfunktion A→A), +12 (Rolle 1 → 1, Tonfunktion A→A) · bewegt: Stimme 3: +3→+4, ↑kl. Sekunde (+1) · Bass gehalten
- **Zulässige Fortsetzungen:** stimmgleich anschließend EM-U007, EM-U011, EM-U016, EM-U041, EM-U044; mit Neuverteilung EM-U030
- **Ungeeignete Kombinationen:** EM-U016 (sofortiges Zurückschalten Dur→Moll wirkt als Flackern; nur bei hohem Z); generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** N – nachgewiesenes Verfahren (Dur/Moll-Wechsel); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U018 – Liegende große Septime bei Dur→Moll (maj7 → m-maj7)
- **Modus:** dur_moll_gemischt · **XYZ-Anker:** 0,40 / 0,25 / 0,40 · **Gültigkeit:** X 0,25–0,55 · Y 0,05–0,45 · Z 0,20–0,60 · **Takt:** 4/4
- **Auflösungsabsicht:** Verdunklung, Septime bleibt als Fremdheitsfarbe

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] große Septime | T⁷ | -12 | [-5, +4, +7, +11] | 5, 3, 5, 7 |
| 1 | 3840 | [1] Moll mit gr. Septime | t (mit gr. Septime) | -12 | [-5, +3, +7, +11] | 5, ♭3, 5, 7 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 5, 7} · tatsächlich gehalten: -5 (Rolle 5 → 5, Tonfunktion A→A), +7 (Rolle 5 → 5, Tonfunktion A→A), +11 (Rolle 7 → 7, Tonfunktion A→A) · bewegt: Stimme 2: +4→+3, ↓kl. Sekunde (-1) · Bass gehalten
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung –
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** E – eigenständige Gestaltung (liegende Septime); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U019 – Moll-add9 → ♭VI-add9 (aeolische Mediante)
- **Modus:** aeolisch · **XYZ-Anker:** 0,40 / 0,35 / 0,20 · **Gültigkeit:** X 0,25–0,55 · Y 0,15–0,55 · Z 0,00–0,40 · **Takt:** 4/4
- **Auflösungsabsicht:** Abdunkeln nach unten, offen

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Moll-add9 | t | -12 | [+0, +3, +7, +14] | 1, ♭3, 5, 9 |
| 1 | 3840 | [♭6] Dur-add9 | ♭VI | -16 | [+0, +3, +8, +10] | 3, 5, 1, 9 |

- **Wechsel 0→1:** Gemeinsamtöne {1, ♭3} · tatsächlich gehalten: +0 (Rolle 1 → 3, Tonfunktion A→A), +3 (Rolle ♭3 → 5, Tonfunktion A→A) · bewegt: Stimme 3: +7→+8, ↑kl. Sekunde (+1); Stimme 4: +14→+10, ↓gr. Terz (-4) · Bass ↓gr. Terz (-4)
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung –
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** I – begründete Interpretation (Terzverwandtschaft); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U020 – Lamento 1: Bass sinkt unter liegender Fläche (i → i/♭7)
- **Modus:** aeolisch · **XYZ-Anker:** 0,30 / 0,35 / 0,30 · **Gültigkeit:** X 0,15–0,45 · Y 0,15–0,55 · Z 0,10–0,50 · **Takt:** 4/4
- **Auflösungsabsicht:** Bass setzt Abstieg fort

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Moll-add9 | t | -12 | [-5, +2, +3, +7] | 5, 9, ♭3, 5 |
| 1 | 3840 | [1] Moll-None | t⁷ (Septime im Bass, Durchgang) | -14 | [-5, +2, +3, +12] | 5, 9, ♭3, 1 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 2, ♭3, 5} · tatsächlich gehalten: -5 (Rolle 5 → 5, Tonfunktion A→A), +2 (Rolle 9 → 9, Tonfunktion A→A), +3 (Rolle ♭3 → ♭3, Tonfunktion A→A) · bewegt: Stimme 4: +7→+12, ↑Quarte (+5) · Bass ↓gr. Sekunde (-2)
- **Hinweis Solver:** Zustand 1: nur 3 von 4 gewünschten Haltetönen lösbar (alle gemeinsamen Pitch-Classes, die in beiden Voicings vorkommen, bleiben dennoch gehalten – siehe Prüfung).
- **Zulässige Fortsetzungen:** stimmgleich anschließend EM-U021; mit Neuverteilung –
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** E – eigenständige Gestaltung (Lamentobass); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U021 – Lamento 2: ♭7 → dorische 6 im Bass (→ IV/3)
- **Modus:** dorisch · **XYZ-Anker:** 0,35 / 0,40 / 0,35 · **Gültigkeit:** X 0,20–0,50 · Y 0,20–0,60 · Z 0,15–0,55 · **Takt:** 4/4
- **Auflösungsabsicht:** chromatischer Abstieg geht weiter

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Moll-None | t⁷ | -14 | [-5, +2, +3, +12] | 5, 9, ♭3, 1 |
| 1 | 3840 | [4] Dur | S³ (IV mit Terz im Bass) | -15 | [-3, +0, +5, +12] | 3, 5, 1, 5 |

- **Wechsel 0→1:** Gemeinsamtöne {1} · tatsächlich gehalten: +12 (Rolle 1 → 5, Tonfunktion A→A) · bewegt: Stimme 1: -5→-3, ↑gr. Sekunde (+2); Stimme 2: +2→+0, ↓gr. Sekunde (-2); Stimme 3: +3→+5, ↑gr. Sekunde (+2) · Bass ↓kl. Sekunde (-1)
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung EM-U022
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** E – eigenständige Gestaltung (chromatischer Lamentobass); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U022 – Lamento 3: Dur-IV/3 → Moll-iv/3 (F♯→F in zwei Stimmen)
- **Modus:** aeolisch · **XYZ-Anker:** 0,25 / 0,45 / 0,45 · **Gültigkeit:** X 0,10–0,40 · Y 0,25–0,65 · Z 0,25–0,65 · **Takt:** 4/4
- **Auflösungsabsicht:** Schmerzspitze, weiter zur Dominante

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [4] Dur | S³ | -15 | [-3, +0, +5, +9] | 3, 5, 1, 3 |
| 1 | 3840 | [4] Moll | s³ | -16 | [-4, +0, +5, +12] | ♭3, 5, 1, 5 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 4} · tatsächlich gehalten: +0 (Rolle 5 → 5, Tonfunktion A→A), +5 (Rolle 1 → 1, Tonfunktion A→A) · bewegt: Stimme 1: -3→-4, ↓kl. Sekunde (-1); Stimme 4: +9→+12, ↑kl. Terz (+3) · Bass ↓kl. Sekunde (-1)
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung EM-U023, EM-U038
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** E – eigenständige Gestaltung (chromatische Stimmführung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U023 – Lamento 4: iv/3 → V-sus4 (Ankunft auf 5)
- **Modus:** harm_moll · **XYZ-Anker:** 0,25 / 0,45 / 0,40 · **Gültigkeit:** X 0,10–0,40 · Y 0,25–0,65 · Z 0,20–0,60 · **Takt:** 4/4
- **Auflösungsabsicht:** Halbschluss mit Vorhalt, Auflösung offen

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [4] Moll | s³ | -16 | [-4, +0, +5, +8] | ♭3, 5, 1, ♭3 |
| 1 | 3840 | [5] sus4 | D (sus) | -17 | [-5, +0, +2, +12] | 1, 4/11, 5, 4/11 |

- **Wechsel 0→1:** Gemeinsamtöne {1} · tatsächlich gehalten: +0 (Rolle 5 → 4/11, Tonfunktion A→A) · bewegt: Stimme 1: -4→-5, ↓kl. Sekunde (-1); Stimme 3: +5→+2, ↓kl. Terz (-3); Stimme 4: +8→+12, ↑gr. Terz (+4) · Bass ↓kl. Sekunde (-1)
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung –
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** E – eigenständige Gestaltung (Halbschluss); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U024 – Halbverminderte Eintrübung (i-add9 → iiø7)
- **Modus:** harm_moll · **XYZ-Anker:** 0,25 / 0,35 / 0,40 · **Gültigkeit:** X 0,10–0,40 · Y 0,15–0,55 · Z 0,20–0,60 · **Takt:** 4/4
- **Auflösungsabsicht:** Spannung, Dominante erwartet

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Moll-add9 | t | -12 | [+0, +3, +7, +14] | 1, ♭3, 5, 9 |
| 1 | 3840 | [2] halbvermindert | sø (halbverminderte Subdominante) | -10 | [+0, +5, +8, +14] | ♭7, ♭3, ♯11/♭5, 1 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 2} · tatsächlich gehalten: +0 (Rolle 1 → ♭7, Tonfunktion A→A), +14 (Rolle 9 → 1, Tonfunktion A→A) · bewegt: Stimme 2: +3→+5, ↑gr. Sekunde (+2); Stimme 3: +7→+8, ↑kl. Sekunde (+1) · Bass ↑gr. Sekunde (+2)
- **Zulässige Fortsetzungen:** stimmgleich anschließend EM-U025; mit Neuverteilung –
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** N – nachgewiesenes Verfahren (Tagg: halbvermindert); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U025 – iiø7 → V7♭9: drei Gemeinsamtöne, ein Halbtonschritt
- **Modus:** harm_moll · **XYZ-Anker:** 0,20 / 0,45 / 0,50 · **Gültigkeit:** X 0,05–0,35 · Y 0,25–0,65 · Z 0,30–0,70 · **Takt:** 4/4
- **Auflösungsabsicht:** Dominantspannung, Auflösung optional

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [2] halbvermindert | sø | -10 | [+0, +5, +8, +14] | ♭7, ♭3, ♯11/♭5, 1 |
| 1 | 3840 | [5] Sept-♭9 | D⁷♭⁹ | -17 | [-1, +5, +8, +14] | 3, ♭7, ♭9, 5 |

- **Wechsel 0→1:** Gemeinsamtöne {2, 4, ♭6} · tatsächlich gehalten: +5 (Rolle ♭3 → ♭7, Tonfunktion A→A), +8 (Rolle ♯11/♭5 → ♭9, Tonfunktion A→A), +14 (Rolle 1 → 5, Tonfunktion A→A) · bewegt: Stimme 1: +0→-1, ↓kl. Sekunde (-1) · Bass ↓Quinte (-7)
- **Zulässige Fortsetzungen:** stimmgleich anschließend EM-U026; mit Neuverteilung –
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** E – eigenständige Gestaltung (chromatische Stimmführung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U026 – Funktionale Auflösung V7♭9 → i-add9
- **Modus:** harm_moll · **XYZ-Anker:** 0,30 / 0,45 / 0,20 · **Gültigkeit:** X 0,15–0,45 · Y 0,25–0,65 · Z 0,00–0,40 · **Takt:** 4/4
- **Auflösungsabsicht:** echte Auflösung (G♯→A, F→E), sparsam

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [5] Sept-♭9 | D⁷♭⁹ | -17 | [-1, +5, +8, +14] | 3, ♭7, ♭9, 5 |
| 1 | 3840 | [1] Moll-add9 | t | -12 | [+0, +3, +7, +14] | 1, ♭3, 5, 9 |

- **Wechsel 0→1:** Gemeinsamtöne {2, 5} · tatsächlich gehalten: +14 (Rolle 5 → 9, Tonfunktion A→A) · bewegt: Stimme 1: -1→+0, ↑kl. Sekunde (+1); Stimme 2: +5→+3, ↓gr. Sekunde (-2); Stimme 3: +8→+7, ↓kl. Sekunde (-1) · Bass ↑Quarte (+5)
- **Zulässige Fortsetzungen:** stimmgleich anschließend EM-U001, EM-U002, EM-U004, EM-U019, EM-U024, EM-U029, EM-U033; mit Neuverteilung EM-U003, EM-U005, EM-U017, EM-U020, EM-U027, EM-U035, EM-U039, EM-U046
- **Ungeeignete Kombinationen:** EM-U024 (Auflösung sofort wieder eintrüben: Kreisen ohne Aussage); generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** I – begründete Interpretation (funktionale Auflösung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U027 – Wechselklang über Tonikapedal (i → ♭VII/1)
- **Modus:** aeolisch · **XYZ-Anker:** 0,30 / 0,25 / 0,15 · **Gültigkeit:** X 0,15–0,45 · Y 0,05–0,45 · Z 0,00–0,35 · **Takt:** 4/4
- **Auflösungsabsicht:** Pendel, Rückkehr erwartet

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Moll-add9 | t | -12 | [-5, +2, +3, +7] | 5, 9, ♭3, 5 |
| 1 | 3840 | [♭7] Dur-add9 | ♭VII über Pedal | -12 | [-7, +2, +5, +10] | 5, 3, 5, 1 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 2} · tatsächlich gehalten: +2 (Rolle 9 → 3, Tonfunktion A→A) · bewegt: Stimme 1: -5→-7, ↓gr. Sekunde (-2); Stimme 3: +3→+5, ↑gr. Sekunde (+2); Stimme 4: +7→+10, ↑kl. Terz (+3) · Bass gehalten
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung –
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** I – begründete Interpretation (Pedal unter Wechselharmonik); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U028 – Subdominante über Dominantpedal (i/5 → iv/5)
- **Modus:** harm_moll · **XYZ-Anker:** 0,20 / 0,50 / 0,50 · **Gültigkeit:** X 0,05–0,35 · Y 0,30–0,70 · Z 0,30–0,70 · **Takt:** 4/4
- **Auflösungsabsicht:** Druck auf die Dominante, Auflösung offen

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Moll | t⁶₄ über Pedal | -17 | [+0, +3, +7, +12] | 1, ♭3, 5, 1 |
| 1 | 3840 | [4] Moll | s über Dominantpedal | -17 | [+0, +5, +8, +12] | 5, 1, ♭3, 5 |

- **Wechsel 0→1:** Gemeinsamtöne {1} · tatsächlich gehalten: +0 (Rolle 1 → 5, Tonfunktion A→A), +12 (Rolle 1 → 5, Tonfunktion A→A) · bewegt: Stimme 2: +3→+5, ↑gr. Sekunde (+2); Stimme 3: +7→+8, ↑kl. Sekunde (+1) · Bass gehalten
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung EM-U023, EM-U038
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** I – begründete Interpretation (Orgelpunkt auf 5); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U029 – Reharmonisierung: liegendes H über vier Unterbauten
- **Modus:** aeolisch · **XYZ-Anker:** 0,50 / 0,30 / 0,25 · **Gültigkeit:** X 0,35–0,65 · Y 0,10–0,50 · Z 0,05–0,45 · **Takt:** 4/4
- **Auflösungsabsicht:** gleicher Ton, fünf Bedeutungen; kein Schlussziel

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Moll-add9 | t (H = 9) | -12 | [+0, +3, +7, +14] | 1, ♭3, 5, 9 |
| 1 | 3840 | [♭6] maj7♯11 | ♭VI (H = ♯11) | -16 | [+0, +3, +7, +14] | 3, 5, 7, ♯11/♭5 |
| 2 | 7680 | [4] Moll-Sexte | s (H = 6) | -19 | [+0, +5, +8, +14] | 5, 1, ♭3, 6/13 |
| 3 | 11520 | [♭7] Dur-add9 | ♭VII (H = 3) | -14 | [+0, +5, +10, +14] | 9, 5, 1, 3 |
| 4 | 15360 | [1] Moll-add9 | t (H = 9) | -12 | [+0, +3, +7, +14] | 1, ♭3, 5, 9 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 2, ♭3, 5} · tatsächlich gehalten: +0 (Rolle 1 → 3, Tonfunktion A→A), +3 (Rolle ♭3 → 5, Tonfunktion A→A), +7 (Rolle 5 → 7, Tonfunktion A→A), +14 (Rolle 9 → ♯11/♭5, Tonfunktion A→A) · bewegt: keine · Bass ↓gr. Terz (-4)
- **Wechsel 1→2:** Gemeinsamtöne {1, 2, ♭6} · tatsächlich gehalten: +0 (Rolle 3 → 5, Tonfunktion A→A), +14 (Rolle ♯11/♭5 → 6/13, Tonfunktion A→A) · bewegt: Stimme 2: +3→+5, ↑gr. Sekunde (+2); Stimme 3: +7→+8, ↑kl. Sekunde (+1) · Bass ↓kl. Terz (-3)
- **Wechsel 2→3:** Gemeinsamtöne {1, 2, 4} · tatsächlich gehalten: +0 (Rolle 5 → 9, Tonfunktion A→A), +5 (Rolle 1 → 5, Tonfunktion A→A), +14 (Rolle 6/13 → 3, Tonfunktion A→A) · bewegt: Stimme 3: +8→+10, ↑gr. Sekunde (+2) · Bass ↑Quarte (+5)
- **Wechsel 3→4:** Gemeinsamtöne {1, 2} · tatsächlich gehalten: +0 (Rolle 9 → 1, Tonfunktion A→A), +14 (Rolle 3 → 9, Tonfunktion A→A) · bewegt: Stimme 2: +5→+3, ↓gr. Sekunde (-2); Stimme 3: +10→+7, ↓kl. Terz (-3) · Bass ↑gr. Sekunde (+2)
- **Reharmonisierter Motivton:** +14 liegt über alle Zustände (eine einzige gebundene Note im MIDI).
- **Zulässige Fortsetzungen:** stimmgleich anschließend EM-U001, EM-U002, EM-U004, EM-U019, EM-U024, EM-U029, EM-U033; mit Neuverteilung EM-U003, EM-U005, EM-U017, EM-U020, EM-U027, EM-U035, EM-U039, EM-U046
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Halten Motivton“; Stimmführungs-Solver
- **Evidenz:** I – begründete Interpretation (identischer Ton über verändertem Unterbau); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U030 – Reharmonisierung Dur: liegendes E über Terzkette
- **Modus:** ionisch · **XYZ-Anker:** 0,75 / 0,30 / 0,15 · **Gültigkeit:** X 0,60–0,90 · Y 0,10–0,50 · Z 0,00–0,35 · **Takt:** 4/4
- **Auflösungsabsicht:** Melodieton bleibt, Harmonie erzählt

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Dur-add9 | T (E = 3) | -12 | [-5, +2, +7, +16] | 5, 9, 5, 3 |
| 1 | 3840 | [6] Moll-Sept | Tp (E = 5) | -15 | [-5, +0, +7, +16] | ♭7, ♭3, ♭7, 5 |
| 2 | 7680 | [4] große Septime | S (E = 7) | -19 | [-7, +0, +9, +16] | 1, 5, 3, 7 |
| 3 | 11520 | [2] Moll-None | Sp (E = 9) | -10 | [-7, +0, +9, +16] | ♭3, ♭7, 5, 9 |
| 4 | 15360 | [1] Dur-add9 | T (E = 3) | -12 | [-8, +2, +7, +16] | 3, 9, 5, 3 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 3, 5} · tatsächlich gehalten: -5 (Rolle 5 → ♭7, Tonfunktion A→A), +7 (Rolle 5 → ♭7, Tonfunktion A→A), +16 (Rolle 3 → 5, Tonfunktion A→A) · bewegt: Stimme 2: +2→+0, ↓gr. Sekunde (-2) · Bass ↓kl. Terz (-3)
- **Wechsel 1→2:** Gemeinsamtöne {1, 3, 6} · tatsächlich gehalten: +0 (Rolle ♭3 → 5, Tonfunktion A→A), +16 (Rolle 5 → 7, Tonfunktion A→A) · bewegt: Stimme 1: -5→-7, ↓gr. Sekunde (-2); Stimme 3: +7→+9, ↑gr. Sekunde (+2) · Bass ↓gr. Terz (-4)
- **Wechsel 2→3:** Gemeinsamtöne {1, 3, 4, 6} · tatsächlich gehalten: -7 (Rolle 1 → ♭3, Tonfunktion A→A), +0 (Rolle 5 → ♭7, Tonfunktion A→A), +9 (Rolle 3 → 5, Tonfunktion A→A), +16 (Rolle 7 → 9, Tonfunktion A→A) · bewegt: keine · Bass ↑gr. Sexte (+9)
- **Wechsel 3→4:** Gemeinsamtöne {1, 2, 3} · tatsächlich gehalten: +16 (Rolle 9 → 3, Tonfunktion A→A) · bewegt: Stimme 1: -7→-8, ↓kl. Sekunde (-1); Stimme 2: +0→+2, ↑gr. Sekunde (+2); Stimme 3: +9→+7, ↓gr. Sekunde (-2) · Bass ↓gr. Sekunde (-2)
- **Reharmonisierter Motivton:** +16 liegt über alle Zustände (eine einzige gebundene Note im MIDI).
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung EM-U007, EM-U011, EM-U016, EM-U030, EM-U041, EM-U044
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Halten Motivton“; Stimmführungs-Solver
- **Evidenz:** I – begründete Interpretation (Reharmonisierung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U031 – Bass sinkt unter konstanten Oberstimmen (I-maj7 → vi-9)
- **Modus:** ionisch · **XYZ-Anker:** 0,70 / 0,25 / 0,15 · **Gültigkeit:** X 0,55–0,85 · Y 0,05–0,45 · Z 0,00–0,35 · **Takt:** 4/4
- **Auflösungsabsicht:** Umdeutung ohne Oberstimmenbewegung

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] große Septime | T⁷ | -12 | [-5, +4, +7, +11] | 5, 3, 5, 7 |
| 1 | 3840 | [6] Moll-None | Tp⁹ | -15 | [-5, +4, +11, +12] | ♭7, 5, 9, ♭3 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 3, 5, 7} · tatsächlich gehalten: -5 (Rolle 5 → ♭7, Tonfunktion A→A), +4 (Rolle 3 → 5, Tonfunktion A→A) · bewegt: Stimme 3: +7→+11, ↑gr. Terz (+4); Stimme 4: +11→+12, ↑kl. Sekunde (+1) · Bass ↓kl. Terz (-3)
- **Hinweis Solver:** Zustand 1: nur 3 von 4 gewünschten Haltetönen lösbar (alle gemeinsamen Pitch-Classes, die in beiden Voicings vorkommen, bleiben dennoch gehalten – siehe Prüfung).
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung –
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** E – eigenständige Gestaltung (Bass unter konstanten Oberstimmen); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U032 – Dorische Sexte bleibt, Bass steigt zur IV-9
- **Modus:** dorisch · **XYZ-Anker:** 0,55 / 0,30 / 0,15 · **Gültigkeit:** X 0,40–0,70 · Y 0,10–0,50 · Z 0,00–0,35 · **Takt:** 4/4
- **Auflösungsabsicht:** Aufhellung durch Bass, Oberstimmen liegen

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Moll-Sexte | t⁶ | -12 | [-5, +3, +7, +9] | 5, ♭3, 5, 6/13 |
| 1 | 3840 | [4] Dominant-None | S⁹ | -7 | [-5, +3, +9, +12] | 9, ♭7, 3, 5 |

- **Wechsel 0→1:** Gemeinsamtöne {1, ♭3, 5, 6} · tatsächlich gehalten: -5 (Rolle 5 → 9, Tonfunktion A→A), +3 (Rolle ♭3 → ♭7, Tonfunktion A→A) · bewegt: Stimme 3: +7→+9, ↑gr. Sekunde (+2); Stimme 4: +9→+12, ↑kl. Terz (+3) · Bass ↑Quarte (+5)
- **Hinweis Solver:** Zustand 1: nur 3 von 4 gewünschten Haltetönen lösbar (alle gemeinsamen Pitch-Classes, die in beiden Voicings vorkommen, bleiben dennoch gehalten – siehe Prüfung).
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung –
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** E – eigenständige Gestaltung (liegende Sexte); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U033 – Gestaffelter Übergang zur ♭III-maj7
- **Modus:** aeolisch · **XYZ-Anker:** 0,50 / 0,30 / 0,20 · **Gültigkeit:** X 0,35–0,65 · Y 0,10–0,50 · Z 0,00–0,40 · **Takt:** 4/4
- **Auflösungsabsicht:** Klang baut sich stimmweise um

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Moll-add9 | t | -12 | [+0, +3, +7, +14] | 1, ♭3, 5, 9 |
| 1 | 3840 | [♭3] große Septime | tP (♭III) | -9 | [-2, +3, +7, +14] | 5, 1, 3, 7 |

- **Wechsel 0→1:** Gemeinsamtöne {2, ♭3, 5} · tatsächlich gehalten: +3 (Rolle ♭3 → 1, Tonfunktion A→A), +7 (Rolle 5 → 3, Tonfunktion A→A), +14 (Rolle 9 → 7, Tonfunktion A→A) · bewegt: Stimme 1: +0→-2, ↓gr. Sekunde (-2) · Bass ↑kl. Terz (+3)
- **Gestaffelte Einsätze:** bewegte Stimmen erreichen ihr Ziel versetzt um 0, 480, 960, 1440 Ticks; die alte Tonhöhe klingt bis dahin weiter; liegende Stimmen bleiben gebunden.
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung –
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“, gestaffelte Einsätze; Stimmführungs-Solver
- **Evidenz:** N – nachgewiesenes Verfahren (gestaffelte Einsätze (Lyne zu Lolita, Presseheft)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U034 – Gestaffelte Rückkehr IV-add9 → I-add9
- **Modus:** ionisch · **XYZ-Anker:** 0,75 / 0,25 / 0,10 · **Gültigkeit:** X 0,60–0,90 · Y 0,05–0,45 · Z 0,00–0,30 · **Takt:** 4/4
- **Auflösungsabsicht:** plagale Rückkehr, Stimme für Stimme

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [4] Dur-add9 | S | -19 | [-3, +0, +5, +7] | 3, 5, 1, 9 |
| 1 | 3840 | [1] Dur-add9 | T | -12 | [+0, +2, +4, +7] | 1, 9, 3, 5 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 5} · tatsächlich gehalten: +7 (Rolle 9 → 5, Tonfunktion A→A) · bewegt: Stimme 1: -3→+0, ↑kl. Terz (+3); Stimme 2: +0→+2, ↑gr. Sekunde (+2); Stimme 3: +5→+4, ↓kl. Sekunde (-1) · Bass ↑Quinte (+7)
- **Gestaffelte Einsätze:** bewegte Stimmen erreichen ihr Ziel versetzt um 0, 960, 1920, 2880 Ticks; die alte Tonhöhe klingt bis dahin weiter; liegende Stimmen bleiben gebunden.
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung EM-U007, EM-U011, EM-U016, EM-U030, EM-U041, EM-U044
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“, gestaffelte Einsätze; Stimmführungs-Solver
- **Evidenz:** N – nachgewiesenes Verfahren (gestaffelte Einsätze); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U035 – Nonvorhalt löst zur Prime (i-add9 → i)
- **Modus:** aeolisch · **XYZ-Anker:** 0,35 / 0,25 / 0,15 · **Gültigkeit:** X 0,20–0,50 · Y 0,05–0,45 · Z 0,00–0,35 · **Takt:** 4/4
- **Auflösungsabsicht:** echte Auflösung 9→8 am Taktbeginn

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Moll-add9 | t (mit None) | -12 | [-5, +3, +7, +14] | 5, ♭3, 5, 9 |
| 1 | 3840 | [1] Moll | t (rein) | -12 | [-5, +3, +7, +12] | 5, ♭3, 5, 1 |

- **Wechsel 0→1:** Gemeinsamtöne {1, ♭3, 5} · tatsächlich gehalten: -5 (Rolle 5 → 5, Tonfunktion A→A), +3 (Rolle ♭3 → ♭3, Tonfunktion A→A), +7 (Rolle 5 → 5, Tonfunktion A→A) · bewegt: Stimme 4: +14→+12, ↓gr. Sekunde (-2) · Bass gehalten
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung EM-U028, EM-U040, EM-U045, EM-U048
- **Ungeeignete Kombinationen:** EM-U035 (Vorhalt-Auflösung unmittelbar wiederholen: Manierismus); generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** E – eigenständige Gestaltung (Vorhalt mit Auflösungsziel; add9 ist hier bewusst als Vorhalt gesetzt); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U036 – Verzögerter Quartvorhalt (i-sus4 → i)
- **Modus:** aeolisch · **XYZ-Anker:** 0,35 / 0,25 / 0,30 · **Gültigkeit:** X 0,20–0,50 · Y 0,05–0,45 · Z 0,10–0,50 · **Takt:** 4/4
- **Auflösungsabsicht:** Auflösung D→C erst auf Schlag 4 des Zieltakts

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] sus4 | t (sus) | -12 | [-5, +0, +5, +7] | 5, 1, 4/11, 5 |
| 1 | 3840 | [1] Moll | t | -12 | [-5, +0, +3, +7] | 5, 1, ♭3, 5 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 5} · tatsächlich gehalten: -5 (Rolle 5 → 5, Tonfunktion A→A), +0 (Rolle 1 → 1, Tonfunktion A→A), +7 (Rolle 5 → 5, Tonfunktion A→A) · bewegt: Stimme 3: +5→+3, ↓gr. Sekunde (-2) · Bass gehalten
- **Vorhalt:** in Zustand 1 erklingt +5 statt +3 (Funktion V), Auflösung nach 2880 Ticks auf +3
- **Zulässige Fortsetzungen:** stimmgleich anschließend EM-U045, EM-U048; mit Neuverteilung EM-U028, EM-U040
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“, Vorhalt mit Ziel; Stimmführungs-Solver
- **Evidenz:** I – begründete Interpretation (verzögerte Auflösung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U037 – Ausbleibende Auflösung: Vorhalt wird umgedeutet (E7sus4 → F-maj7)
- **Modus:** aeolisch · **XYZ-Anker:** 0,35 / 0,35 / 0,45 · **Gültigkeit:** X 0,20–0,50 · Y 0,15–0,55 · Z 0,25–0,65 · **Takt:** 4/4
- **Auflösungsabsicht:** Vorhaltston A wird Terz von F – Auflösung bleibt aus

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [5] Sept-sus4 | D (sus) | -17 | [+0, +5, +7, +14] | 4/11, ♭7, 1, 5 |
| 1 | 3840 | [♭6] große Septime | ♭VI | -16 | [+0, +3, +7, +15] | 3, 5, 7, 5 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 5} · tatsächlich gehalten: +0 (Rolle 4/11 → 3, Tonfunktion A→A), +7 (Rolle 1 → 7, Tonfunktion A→A) · bewegt: Stimme 2: +5→+3, ↓gr. Sekunde (-2); Stimme 4: +14→+15, ↑kl. Sekunde (+1) · Bass ↑kl. Sekunde (+1)
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung –
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** E – eigenständige Gestaltung (aufgeschobene Auflösung (Smith)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U038 – Modale Umfärbung der Subdominante (iv → IV)
- **Modus:** dorisch · **XYZ-Anker:** 0,55 / 0,30 / 0,30 · **Gültigkeit:** X 0,40–0,70 · Y 0,10–0,50 · Z 0,10–0,50 · **Takt:** 4/4
- **Auflösungsabsicht:** Aufhellung eines Klangs, Funktion bleibt

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [4] Moll | s (äolisch) | -19 | [-4, +0, +5, +12] | ♭3, 5, 1, 5 |
| 1 | 3840 | [4] Dur | S (dorisch) | -19 | [-3, +0, +5, +12] | 3, 5, 1, 5 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 4} · tatsächlich gehalten: +0 (Rolle 5 → 5, Tonfunktion A→A), +5 (Rolle 1 → 1, Tonfunktion A→A), +12 (Rolle 5 → 5, Tonfunktion A→A) · bewegt: Stimme 1: -4→-3, ↑kl. Sekunde (+1) · Bass gehalten
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung EM-U022
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** I – begründete Interpretation (dorische Dur-IV); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U039 – Phrygische Verdunklung der None (H → B♭)
- **Modus:** phrygisch · **XYZ-Anker:** 0,15 / 0,25 / 0,45 · **Gültigkeit:** X 0,00–0,30 · Y 0,05–0,45 · Z 0,25–0,65 · **Takt:** 4/4
- **Auflösungsabsicht:** Dissonanz bleibt stehen (U)

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Moll-add9 | t (add9) | -12 | [-5, +2, +3, +7] | 5, 9, ♭3, 5 |
| 1 | 3840 | Klangobjekt „Klangobjekt“ {1, ♭2, ♭3, 5} | t mit ♭9 (bewusst unaufgelöst) | -12 | [-5, +1, +3, +7] | 5, ♭2, ♭3, 5 |

- **Wechsel 0→1:** Gemeinsamtöne {1, ♭3, 5} · tatsächlich gehalten: -5 (Rolle 5 → 5, Tonfunktion A→A), +3 (Rolle ♭3 → ♭3, Tonfunktion A→A), +7 (Rolle 5 → 5, Tonfunktion A→A) · bewegt: Stimme 2: +2→+1, ↓kl. Sekunde (-1) · Bass gehalten
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung –
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** E – eigenständige Gestaltung (Fremdton-Umfärbung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U040 – Chromatische Mittelstimme 5–♯5–6–♭7 über Tonikabass
- **Modus:** dorisch · **XYZ-Anker:** 0,45 / 0,30 / 0,45 · **Gültigkeit:** X 0,30–0,60 · Y 0,10–0,50 · Z 0,25–0,65 · **Takt:** 4/4
- **Auflösungsabsicht:** Linie trägt die Harmonie, kein Ziel

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Moll | t | -12 | [-5, +0, +3, +12] | 5, 1, ♭3, 1 |
| 1 | 3840 | [♭6] Dur | ♭VI/1 | -12 | [-4, +0, +3, +12] | 1, 3, 5, 3 |
| 2 | 7680 | [4] Dur | IV/1 | -12 | [-3, +0, +5, +12] | 3, 5, 1, 5 |
| 3 | 11520 | [1] Moll-Sept | t⁷ | -12 | [-2, +0, +7, +15] | ♭7, 1, 5, ♭3 |

- **Wechsel 0→1:** Gemeinsamtöne {1, ♭3} · tatsächlich gehalten: +0 (Rolle 1 → 3, Tonfunktion A→A), +3 (Rolle ♭3 → 5, Tonfunktion A→A), +12 (Rolle 1 → 3, Tonfunktion A→A) · bewegt: Stimme 1: -5→-4, ↑kl. Sekunde (+1) · Bass gehalten
- **Wechsel 1→2:** Gemeinsamtöne {1} · tatsächlich gehalten: +0 (Rolle 3 → 5, Tonfunktion A→A), +12 (Rolle 3 → 5, Tonfunktion A→A) · bewegt: Stimme 1: -4→-3, ↑kl. Sekunde (+1); Stimme 3: +3→+5, ↑gr. Sekunde (+2) · Bass gehalten
- **Wechsel 2→3:** Gemeinsamtöne {1} · tatsächlich gehalten: +0 (Rolle 5 → 1, Tonfunktion A→A) · bewegt: Stimme 1: -3→-2, ↑kl. Sekunde (+1); Stimme 3: +5→+7, ↑gr. Sekunde (+2); Stimme 4: +12→+15, ↑kl. Terz (+3) · Bass gehalten
- **Hinweis Solver:** Zustand 3: nur 1 von 2 gewünschten Haltetönen lösbar (alle gemeinsamen Pitch-Classes, die in beiden Voicings vorkommen, bleiben dennoch gehalten – siehe Prüfung).
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung –
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** E – eigenständige Gestaltung (chromatische Einzelstimme); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U041 – Plagaler Nachbarklang über Tonikabass (I → IV/1 → I)
- **Modus:** ionisch · **XYZ-Anker:** 0,80 / 0,20 / 0,10 · **Gültigkeit:** X 0,65–0,95 · Y 0,00–0,40 · Z 0,00–0,30 · **Takt:** 4/4
- **Auflösungsabsicht:** Pendel, ruhig atmend

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Dur-add9 | T | -12 | [-5, +2, +4, +12] | 5, 9, 3, 1 |
| 1 | 3840 | [4] Dur-add9 | S⁶₄ (Nachbarklang) | -12 | [-5, -3, +5, +12] | 9, 3, 1, 5 |
| 2 | 7680 | [1] Dur-add9 | T | -12 | [-5, +2, +4, +12] | 5, 9, 3, 1 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 5} · tatsächlich gehalten: -5 (Rolle 5 → 9, Tonfunktion A→A), +12 (Rolle 1 → 5, Tonfunktion A→A) · bewegt: Stimme 2: +2→-3, ↓Quarte (-5); Stimme 3: +4→+5, ↑kl. Sekunde (+1) · Bass gehalten
- **Wechsel 1→2:** Gemeinsamtöne {1, 5} · tatsächlich gehalten: -5 (Rolle 9 → 5, Tonfunktion A→A), +12 (Rolle 5 → 1, Tonfunktion A→A) · bewegt: Stimme 2: -3→+2, ↑Quarte (+5); Stimme 3: +5→+4, ↓kl. Sekunde (-1) · Bass gehalten
- **Zulässige Fortsetzungen:** stimmgleich anschließend EM-U007, EM-U011, EM-U016, EM-U041, EM-U044; mit Neuverteilung EM-U030
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** I – begründete Interpretation (Plagal über Pedal); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U042 – Dur-Halbschluss IV-maj7 → V-sus4
- **Modus:** ionisch · **XYZ-Anker:** 0,70 / 0,35 / 0,30 · **Gültigkeit:** X 0,55–0,85 · Y 0,15–0,55 · Z 0,10–0,50 · **Takt:** 4/4
- **Auflösungsabsicht:** Halbschluss, bleibt offen

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [4] große Septime | S | -19 | [-3, +0, +4, +9] | 3, 5, 7, 3 |
| 1 | 3840 | [5] sus4 | D (sus) | -17 | [-5, +0, +7, +14] | 1, 4/11, 1, 5 |

- **Wechsel 0→1:** Gemeinsamtöne {1} · tatsächlich gehalten: +0 (Rolle 5 → 4/11, Tonfunktion A→A) · bewegt: Stimme 1: -3→-5, ↓gr. Sekunde (-2); Stimme 3: +4→+7, ↑kl. Terz (+3); Stimme 4: +9→+14, ↑Quarte (+5) · Bass ↑gr. Sekunde (+2)
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung –
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** N – nachgewiesenes Verfahren (Halbschluss (filmmusicnotes: Cheyenne B)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U043 – Moll-Halbschluss iv-add9 → V
- **Modus:** harm_moll · **XYZ-Anker:** 0,30 / 0,40 / 0,35 · **Gültigkeit:** X 0,15–0,45 · Y 0,20–0,60 · Z 0,15–0,55 · **Takt:** 4/4
- **Auflösungsabsicht:** Halbschluss, Dominante steht

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [4] Moll-add9 | s | -19 | [-5, +0, +7, +8] | 9, 5, 9, ♭3 |
| 1 | 3840 | [5] Dur | D | -17 | [-5, +2, +7, +11] | 1, 5, 1, 3 |

- **Wechsel 0→1:** Gemeinsamtöne {5} · tatsächlich gehalten: -5 (Rolle 9 → 1, Tonfunktion A→A), +7 (Rolle 9 → 1, Tonfunktion A→A) · bewegt: Stimme 2: +0→+2, ↑gr. Sekunde (+2); Stimme 4: +8→+11, ↑kl. Terz (+3) · Bass ↑gr. Sekunde (+2)
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung –
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** I – begründete Interpretation (Halbschluss); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U044 – Dur-Mediante abwärts (I-add9 → ♭VI-add9)
- **Modus:** dur_moll_gemischt · **XYZ-Anker:** 0,65 / 0,35 / 0,35 · **Gültigkeit:** X 0,50–0,80 · Y 0,15–0,55 · Z 0,15–0,55 · **Takt:** 4/4
- **Auflösungsabsicht:** Farbwechsel, Rückkehr oder Weiterführung

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Dur-add9 | T | -12 | [-5, +2, +4, +12] | 5, 9, 3, 1 |
| 1 | 3840 | [♭6] Dur-add9 | ♭VI (Variante) | -16 | [-4, -2, +3, +12] | 1, 9, 5, 3 |

- **Wechsel 0→1:** Gemeinsamtöne {1} · tatsächlich gehalten: +12 (Rolle 1 → 3, Tonfunktion A→A) · bewegt: Stimme 1: -5→-4, ↑kl. Sekunde (+1); Stimme 2: +2→-2, ↓gr. Terz (-4); Stimme 3: +4→+3, ↓kl. Sekunde (-1) · Bass ↓gr. Terz (-4)
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung –
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** E – eigenständige Gestaltung (Modalmischung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U045 – Phrygisch-tragischer Schritt (i → ♭II-maj7)
- **Modus:** phrygisch · **XYZ-Anker:** 0,20 / 0,65 / 0,40 · **Gültigkeit:** X 0,05–0,35 · Y 0,45–0,85 · Z 0,20–0,60 · **Takt:** 4/4
- **Auflösungsabsicht:** Schicksalsgeste, Rückkehr erwartet

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Moll | t | -12 | [-5, +0, +3, +7] | 5, 1, ♭3, 5 |
| 1 | 3840 | [♭2] große Septime | ♭II (neapolitanisch) | -11 | [-4, +0, +1, +5] | 5, 7, 1, 3 |

- **Wechsel 0→1:** Gemeinsamtöne {1} · tatsächlich gehalten: +0 (Rolle 1 → 7, Tonfunktion A→A) · bewegt: Stimme 1: -5→-4, ↑kl. Sekunde (+1); Stimme 3: +3→+1, ↓gr. Sekunde (-2); Stimme 4: +7→+5, ↓gr. Sekunde (-2) · Bass ↑kl. Sekunde (+1)
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung –
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** E – eigenständige Gestaltung (phrygische Harmonik); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U046 – Modale Dominante (i-add9 → v-m7)
- **Modus:** aeolisch · **XYZ-Anker:** 0,40 / 0,30 / 0,25 · **Gültigkeit:** X 0,25–0,55 · Y 0,10–0,50 · Z 0,05–0,45 · **Takt:** 4/4
- **Auflösungsabsicht:** weiche Spannung ohne Leitton

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Moll-add9 | t | -12 | [-5, +2, +3, +7] | 5, 9, ♭3, 5 |
| 1 | 3840 | [5] Moll-Sept | d (Moll-Dominante) | -17 | [-5, +2, +5, +10] | 1, 5, ♭7, ♭3 |

- **Wechsel 0→1:** Gemeinsamtöne {2, 5} · tatsächlich gehalten: -5 (Rolle 5 → 1, Tonfunktion A→A), +2 (Rolle 9 → 5, Tonfunktion A→A) · bewegt: Stimme 3: +3→+5, ↑gr. Sekunde (+2); Stimme 4: +7→+10, ↑kl. Terz (+3) · Bass ↓Quarte (-5)
- **Hinweis Solver:** Zustand 1: nur 2 von 3 gewünschten Haltetönen lösbar (alle gemeinsamen Pitch-Classes, die in beiden Voicings vorkommen, bleiben dennoch gehalten – siehe Prüfung).
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung –
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** I – begründete Interpretation (modale Harmonik); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U047 – Cluster mündet in Moll-add9 (Dissonanz → Konsonanz)
- **Modus:** aeolisch · **XYZ-Anker:** 0,30 / 0,40 / 0,40 · **Gültigkeit:** X 0,15–0,45 · Y 0,20–0,60 · Z 0,20–0,60 · **Takt:** 4/4
- **Auflösungsabsicht:** Auflösung der Ballung in Tonalität

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | Klangobjekt „Klangobjekt“ {♭2, 2, ♭3, 5} | Klangobjekt (U) | -12 | [+1, +2, +3, +7] | ♭2, 2, ♭3, 5 |
| 1 | 3840 | [1] Moll-add9 | t | -12 | [+0, +2, +3, +7] | 1, 9, ♭3, 5 |

- **Wechsel 0→1:** Gemeinsamtöne {2, ♭3, 5} · tatsächlich gehalten: +2 (Rolle 2 → 9, Tonfunktion A→A), +3 (Rolle ♭3 → ♭3, Tonfunktion A→A), +7 (Rolle 5 → 5, Tonfunktion A→A) · bewegt: Stimme 1: +1→+0, ↓kl. Sekunde (-1) · Bass gehalten
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020, EM-U024, EM-U027
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** I – begründete Interpretation (Despair: Schichtakkumulation mündet in Tonalität (Filmtracks)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U048 – Konsonanz erhält Polychord-Schatten (i → i + ♭II)
- **Modus:** phrygisch · **XYZ-Anker:** 0,15 / 0,50 / 0,55 · **Gültigkeit:** X 0,00–0,30 · Y 0,30–0,70 · Z 0,35–0,75 · **Takt:** 4/4
- **Auflösungsabsicht:** Bedrohung tritt hinzu, nichts löst sich

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Moll | t | -12 | [-5, +0, +3, +7] | 5, 1, ♭3, 5 |
| 1 | 3840 | Klangobjekt „Klangobjekt“ {1, ♭2, ♭3, 4, 5, ♭6} | Polychord i/♭II (U) | -12 | [-5, -4, +0, +3, +13, +17] | 5, ♭6, 1, ♭3, ♭2, 4 |

- **Wechsel 0→1:** Gemeinsamtöne {1, ♭3, 5} · tatsächlich gehalten: -5 (Rolle 5 → 5, Tonfunktion A→A), +0 (Rolle 1 → 1, Tonfunktion A→A), +3 (Rolle ♭3 → ♭3, Tonfunktion A→A) · bewegt: Stimme 4: +7→+3, ↓gr. Terz (-4) · Bass gehalten
- **Hinweis Solver:** Zustand 1: nur 3 von 4 gewünschten Haltetönen lösbar (alle gemeinsamen Pitch-Classes, die in beiden Voicings vorkommen, bleiben dennoch gehalten – siehe Prüfung).
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung –
- **Ungeeignete Kombinationen:** EM-U001 (Polychord-Bedrohung direkt in lyrische Modalfortsetzung: Bruch ohne Vermittlung; besser über EM-U047); generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** N – nachgewiesenes Verfahren (Polytonalität (Corbella)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U049 – Plagale Rückkehr iv-add9 → i-add9 mit liegender None
- **Modus:** aeolisch · **XYZ-Anker:** 0,30 / 0,25 / 0,10 · **Gültigkeit:** X 0,15–0,45 · Y 0,05–0,45 · Z 0,00–0,30 · **Takt:** 4/4
- **Auflösungsabsicht:** plagaler Schluss, weich

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [4] Moll-add9 | s | -19 | [-5, +0, +7, +8] | 9, 5, 9, ♭3 |
| 1 | 3840 | [1] Moll-add9 | t | -12 | [-5, +0, +2, +3] | 5, 1, 9, ♭3 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 5} · tatsächlich gehalten: -5 (Rolle 9 → 5, Tonfunktion A→A), +0 (Rolle 5 → 1, Tonfunktion A→A) · bewegt: Stimme 3: +7→+2, ↓Quarte (-5); Stimme 4: +8→+3, ↓Quarte (-5) · Bass ↑Quinte (+7)
- **Hinweis Solver:** Zustand 1: nur 2 von 3 gewünschten Haltetönen lösbar (alle gemeinsamen Pitch-Classes, die in beiden Voicings vorkommen, bleiben dennoch gehalten – siehe Prüfung).
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung EM-U001, EM-U002, EM-U003, EM-U004, EM-U005, EM-U017, EM-U019, EM-U020, EM-U024, EM-U027
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** I – begründete Interpretation (plagale Moll-Bewegung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-U050 – Dur-Sexte über Terzbass wird Sept (I/3 → IV-maj7)
- **Modus:** ionisch · **XYZ-Anker:** 0,75 / 0,30 / 0,20 · **Gültigkeit:** X 0,60–0,90 · Y 0,10–0,50 · Z 0,00–0,40 · **Takt:** 4/4
- **Auflösungsabsicht:** Bass im Halbtonschritt, warm

| Zustand | Tick | Harmonie | Funktion | Bass | Oberstimmen (rel) | Rollen im Akkord |
|---|---|---|---|---|---|---|
| 0 | 0 | [1] Dur-Sexte | T⁶ (Terz im Bass) | -8 | [-3, +0, +7, +9] | 6/13, 1, 5, 6/13 |
| 1 | 3840 | [4] große Septime | S⁷ | -7 | [-3, +0, +4, +9] | 3, 5, 7, 3 |

- **Wechsel 0→1:** Gemeinsamtöne {1, 3, 6} · tatsächlich gehalten: -3 (Rolle 6/13 → 3, Tonfunktion A→A), +0 (Rolle 1 → 5, Tonfunktion A→A), +9 (Rolle 6/13 → 3, Tonfunktion A→A) · bewegt: Stimme 3: +7→+4, ↓kl. Terz (-3) · Bass ↑kl. Sekunde (+1)
- **Zulässige Fortsetzungen:** stimmgleich anschließend –; mit Neuverteilung EM-U009, EM-U042
- **Ungeeignete Kombinationen:** Übergänge mit abweichendem Ausgangsakkord ohne Neuverteilung; generell: Quint-/Oktavparallelen beim Verketten (maschinell geprüft), unmittelbare Wiederholung desselben Vorhalts
- **Algorithmische Voraussetzungen:** Übergangsabsicht „Gemeinsamtöne halten“; Stimmführungs-Solver
- **Evidenz:** E – eigenständige Gestaltung (stufenweiser Bass über Umkehrungen); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

## 8. R – Rhythmik

Raster-Notation: X = betonter Einsatz (Velocity +12 gegenüber x), x = Einsatz, . = Pause, - = Haltebogen. Kein Muster wird als belegter Originalrhythmus Morricones ausgegeben. Periode = Musterlänge; Gesamtzyklus = kgV(Periode, Taktlänge). Unruhe-Typ wird ab Z ≥ 0,5 aus Dichte und Regelmäßigkeit (Variationskoeffizient der Einsatzabstände, VK) berechnet.

### EM-R001 – Herzschlag einfach
- **Charakter:** körperlich, latent · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,30 / 0,30 · **Gültigkeit:** X 0,00–1,00 · Y 0,10–0,50 · Z 0,10–0,50
- **Muster:** `X..x............` · **Einsätze (Ticks):** 0, 720 · **Akzente:** 0 · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 2,00 Einsätze/Takt · **VK:** 0,62 · **Unruhe-Typ:** –
- **Rollen:** KB LB ST · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R022, EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R002, EM-R003, EM-R013, EM-R015, EM-R019
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** N – nachgewiesenes Verfahren (Herzschlag (cuebycue, Bird)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R002 – Herzschlag, ein Schlag pro zwei Takte
- **Charakter:** fast erstarrt · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,15 / 0,25 · **Gültigkeit:** X 0,00–1,00 · Y 0,00–0,35 · Z 0,05–0,45
- **Muster:** `X..x............................` · **Einsätze (Ticks):** 0, 720 · **Akzente:** 0 · **Periode:** 7680 Ticks
- **Gesamtzyklus:** 7680 Ticks (2.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 1,00 Einsätze/Takt · **VK:** 0,81 · **Unruhe-Typ:** –
- **Rollen:** KB LB ST · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R022, EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R001, EM-R003, EM-R013, EM-R015, EM-R019
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** I – begründete Interpretation (Puls bei geringer Dichte (Wilcox: Ut)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R003 – Herzschlag synkopisch verschoben
- **Charakter:** aus dem Tritt · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,35 / 0,55 · **Gültigkeit:** X 0,00–1,00 · Y 0,15–0,55 · Z 0,35–0,75
- **Muster:** `X..x......x..x..` · **Einsätze (Ticks):** 0, 720, 2400, 3120 · **Akzente:** 0 · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 4,00 Einsätze/Takt · **VK:** 0,43 · **Unruhe-Typ:** psychologisch
- **Rollen:** KB ST · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R007, EM-R009, EM-R012, EM-R014, EM-R017
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R001, EM-R002, EM-R013, EM-R019, EM-R026
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** E – eigenständige Gestaltung (Herzschlag + Verschiebung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R004 – Gleichmäßige Achtel
- **Charakter:** mechanisch stabil · **Säule:** B · **Takt:** 4/4 · **Raster:** e (480 Ticks)
- **XYZ-Anker:** beliebig / 0,40 / 0,40 · **Gültigkeit:** X 0,00–1,00 · Y 0,20–0,60 · Z 0,20–0,60
- **Muster:** `xxxxxxxx` · **Einsätze (Ticks):** 0, 480, 960, 1440, 1920, 2400, 2880, 3360 · **Akzente:** keine · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 8,00 Einsätze/Takt · **VK:** 0,00 · **Unruhe-Typ:** –
- **Rollen:** KB AR · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R005, EM-R006, EM-R008, EM-R013, EM-R016
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** N – nachgewiesenes Verfahren (pulsierender Einzeltonbass (Filmtracks: The Thing)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R005 – Achtel, Akzent 3+3+2
- **Charakter:** drängend ohne Tempo · **Säule:** B · **Takt:** 4/4 · **Raster:** e (480 Ticks)
- **XYZ-Anker:** beliebig / 0,50 / 0,45 · **Gültigkeit:** X 0,00–1,00 · Y 0,30–0,70 · Z 0,25–0,65
- **Muster:** `XxxXxxXx` · **Einsätze (Ticks):** 0, 480, 960, 1440, 1920, 2400, 2880, 3360 · **Akzente:** 0, 1440, 2880 · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 8,00 Einsätze/Takt · **VK:** 0,00 · **Unruhe-Typ:** –
- **Rollen:** KB AR KF · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R004, EM-R006, EM-R008, EM-R013, EM-R016
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** E – eigenständige Gestaltung (Akzentgruppen); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R006 – Achtel, Akzent 2+3+3
- **Charakter:** kippend · **Säule:** B · **Takt:** 4/4 · **Raster:** e (480 Ticks)
- **XYZ-Anker:** beliebig / 0,50 / 0,50 · **Gültigkeit:** X 0,00–1,00 · Y 0,30–0,70 · Z 0,30–0,70
- **Muster:** `XxXxxXxx` · **Einsätze (Ticks):** 0, 480, 960, 1440, 1920, 2400, 2880, 3360 · **Akzente:** 0, 960, 2400 · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 8,00 Einsätze/Takt · **VK:** 0,00 · **Unruhe-Typ:** mechanisch
- **Rollen:** KB AR KF · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R004, EM-R005, EM-R008, EM-R013, EM-R016
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** E – eigenständige Gestaltung (Akzentgruppen); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R007 – Fünfer-Zelle gegen 4/4 (Sechzehntel)
- **Charakter:** unaufhörlich verschoben · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,45 / 0,60 · **Gültigkeit:** X 0,00–1,00 · Y 0,25–0,65 · Z 0,40–0,80
- **Muster:** `Xxx.x` · **Einsätze (Ticks):** 0, 240, 480, 960 · **Akzente:** 0 · **Periode:** 1200 Ticks
- **Gesamtzyklus:** 19200 Ticks (5.00 Takte) · **inkongruent zum Takt:** ja · **Dichte:** 12,80 Einsätze/Takt · **VK:** 0,35 · **Unruhe-Typ:** mechanisch
- **Rollen:** AR KB TU · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R003, EM-R015, EM-R021, EM-R045, EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R008, EM-R013, EM-R019, EM-R026, EM-R029
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** unabhängige Periodenlänge je Rolle
- **Evidenz:** N – nachgewiesenes Verfahren (Zyklus gegen Takt (Wilcox: Se telefonando)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R008 – Dreier-Zelle gegen 4/4
- **Charakter:** kreisend · **Säule:** AB · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,40 / 0,50 · **Gültigkeit:** X 0,00–1,00 · Y 0,20–0,60 · Z 0,30–0,70
- **Muster:** `X.x` · **Einsätze (Ticks):** 0, 480 · **Akzente:** 0 · **Periode:** 720 Ticks
- **Gesamtzyklus:** 11520 Ticks (3.00 Takte) · **inkongruent zum Takt:** ja · **Dichte:** 10,67 Einsätze/Takt · **VK:** 0,33 · **Unruhe-Typ:** mechanisch
- **Rollen:** AR TU · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R004, EM-R005, EM-R006, EM-R007, EM-R009
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** unabhängige Periodenlänge je Rolle
- **Evidenz:** N – nachgewiesenes Verfahren (3 gegen 4 (Wilcox)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R009 – Siebener-Zelle
- **Charakter:** irrational kreisend · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,45 / 0,65 · **Gültigkeit:** X 0,00–1,00 · Y 0,25–0,65 · Z 0,45–0,85
- **Muster:** `X.x.xx.` · **Einsätze (Ticks):** 0, 480, 960, 1200 · **Akzente:** 0 · **Periode:** 1680 Ticks
- **Gesamtzyklus:** 26880 Ticks (7.00 Takte) · **inkongruent zum Takt:** ja · **Dichte:** 9,14 Einsätze/Takt · **VK:** 0,25 · **Unruhe-Typ:** mechanisch
- **Rollen:** AR · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R003, EM-R015, EM-R021, EM-R022, EM-R045
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R008, EM-R013, EM-R027, EM-R035, EM-R036
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** unabhängige Periodenlänge je Rolle
- **Evidenz:** E – eigenständige Gestaltung (unabhängige Periodenlängen); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R010 – Ternäre Wiege 12/8
- **Charakter:** sinnlich, schaukelnd · **Säule:** A · **Takt:** 12/8 · **Raster:** e (480 Ticks)
- **XYZ-Anker:** beliebig / 0,30 / 0,20 · **Gültigkeit:** X 0,00–1,00 · Y 0,10–0,50 · Z 0,00–0,40
- **Muster:** `X.xX.xX.xX.x` · **Einsätze (Ticks):** 0, 960, 1440, 2400, 2880, 3840, 4320, 5280 · **Akzente:** 0, 1440, 2880, 4320 · **Periode:** 5760 Ticks
- **Gesamtzyklus:** 5760 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 8,00 Einsätze/Takt · **VK:** 0,33 · **Unruhe-Typ:** –
- **Rollen:** AR KB LF · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** –
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R059
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** N – nachgewiesenes Verfahren (ternärer Rhythmus für sinnliche Szenen (Morricone zu Indagine)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R011 – Achteltriolen über 4/4
- **Charakter:** fließend, rund · **Säule:** A · **Takt:** 4/4 · **Raster:** t (320 Ticks)
- **XYZ-Anker:** beliebig / 0,35 / 0,30 · **Gültigkeit:** X 0,00–1,00 · Y 0,15–0,55 · Z 0,10–0,50
- **Muster:** `xxxxxxxxxxxx` · **Einsätze (Ticks):** 0, 320, 640, 960, 1280, 1600, 1920, 2240, 2560, 2880, 3200, 3520 · **Akzente:** keine · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 12,00 Einsätze/Takt · **VK:** 0,00 · **Unruhe-Typ:** –
- **Rollen:** AR · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R012, EM-R035, EM-R036, EM-R037, EM-R046
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** I – begründete Interpretation (ternäre Bewegung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R012 – Zwei gegen drei (zwei Schichten)
- **Charakter:** schwebende Reibung · **Säule:** AB · **Takt:** 4/4 · **Raster:** t (320 Ticks)
- **XYZ-Anker:** beliebig / 0,35 / 0,50 · **Gültigkeit:** X 0,00–1,00 · Y 0,15–0,55 · Z 0,30–0,70
- **Schicht „duole“: Muster:** `x..x..x..x..` · **Einsätze (Ticks):** 0, 960, 1920, 2880 · **Akzente:** keine · **Periode:** 3840 Ticks
- **Schicht „triole“: Muster:** `x.x.x.x.x.x.` · **Einsätze (Ticks):** 0, 640, 1280, 1920, 2560, 3200 · **Akzente:** keine · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 8,00 Einsätze/Takt · **VK:** 0,33 · **Unruhe-Typ:** mechanisch
- **Rollen:** AR TU KB · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R011, EM-R017, EM-R019, EM-R026, EM-R030
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster; mehrschichtiges Muster
- **Evidenz:** I – begründete Interpretation (Polyrhythmik (Wilcox: Missa, Mission)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R013 – Untouchables-Prinzip: schneller Boden, langsame Oberstimme
- **Charakter:** Kraft ohne Hektik · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,80 / 0,40 · **Gültigkeit:** X 0,00–1,00 · Y 0,60–1,00 · Z 0,20–0,60
- **Schicht „boden“: Muster:** `xxxxxxxxxxxxxxxx` · **Einsätze (Ticks):** 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600 · **Akzente:** keine · **Periode:** 3840 Ticks
- **Schicht „oben“: Muster:** `X-------------------------------` · **Einsätze (Ticks):** 0 · **Akzente:** 0 · **Periode:** 7680 Ticks
- **Gesamtzyklus:** 7680 Ticks (2.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 8,00 Einsätze/Takt · **VK:** 1,94 · **Unruhe-Typ:** –
- **Rollen:** AR KB HM GS LF · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** –
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R001, EM-R002, EM-R003, EM-R004, EM-R005
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster; mehrschichtiges Muster
- **Evidenz:** I – begründete Interpretation (zwei Zeitschichten (NPR, Movie Music UK)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R014 – Gewichtsfigur fünf Ereignisse, Raum am Taktende
- **Charakter:** schwer, entschlossen · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,80 / 0,35 · **Gültigkeit:** X 0,00–1,00 · Y 0,60–1,00 · Z 0,15–0,55
- **Muster:** `X.x.xX.x........` · **Einsätze (Ticks):** 0, 480, 960, 1200, 1680 · **Akzente:** 0, 1200 · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 5,00 Einsätze/Takt · **VK:** 0,91 · **Unruhe-Typ:** –
- **Rollen:** KB LB · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R003, EM-R015, EM-R021, EM-R045
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R013, EM-R023, EM-R030, EM-R035, EM-R036
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** I – begründete Interpretation (Gewicht statt Dichte; Fünftonfigur (movie-wave, nur Rezension)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R015 – Gedoppelter Akzentpuls 3+3+2 (Sechzehntel)
- **Charakter:** hart, präzise · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,75 / 0,45 · **Gültigkeit:** X 0,00–1,00 · Y 0,55–0,95 · Z 0,25–0,65
- **Muster:** `X..x..x.X..x..x.` · **Einsätze (Ticks):** 0, 720, 1440, 1920, 2640, 3360 · **Akzente:** 0, 1920 · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 6,00 Einsätze/Takt · **VK:** 0,18 · **Unruhe-Typ:** –
- **Rollen:** KB AR ST · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R007, EM-R009, EM-R014, EM-R022, EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R001, EM-R002, EM-R013, EM-R019, EM-R026
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** I – begründete Interpretation (Klavier mit Perkussion gedoppelt (NPR)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R016 – Schlag und Antwort (tief/hoch)
- **Charakter:** Gewichtung und Luft · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,60 / 0,35 · **Gültigkeit:** X 0,00–1,00 · Y 0,40–0,80 · Z 0,15–0,55
- **Schicht „tief“: Muster:** `X.......X.......` · **Einsätze (Ticks):** 0, 1920 · **Akzente:** 0, 1920 · **Periode:** 3840 Ticks
- **Schicht „hoch“: Muster:** `..x...x...x...x.` · **Einsätze (Ticks):** 480, 1440, 2400, 3360 · **Akzente:** keine · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 6,00 Einsätze/Takt · **VK:** 0,35 · **Unruhe-Typ:** –
- **Rollen:** ST KB AR · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R022, EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R004, EM-R005, EM-R006, EM-R008, EM-R013
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster; mehrschichtiges Muster
- **Evidenz:** I – begründete Interpretation (Bass Drum gegen Besen (Smith)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R017 – Stampfende Viertel
- **Charakter:** unerbittlich · **Säule:** B · **Takt:** 4/4 · **Raster:** q (960 Ticks)
- **XYZ-Anker:** beliebig / 0,70 / 0,30 · **Gültigkeit:** X 0,00–1,00 · Y 0,50–0,90 · Z 0,10–0,50
- **Muster:** `XxXx` · **Einsätze (Ticks):** 0, 960, 1920, 2880 · **Akzente:** 0, 1920 · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 4,00 Einsätze/Takt · **VK:** 0,00 · **Unruhe-Typ:** –
- **Rollen:** KB ST · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R003, EM-R022, EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R004, EM-R005, EM-R006, EM-R012, EM-R013
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** I – begründete Interpretation („simple pounding“ (Filmtracks)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R018 – Zögernder Einzeleinsatz
- **Charakter:** unentschlossen · **Säule:** AB · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,20 / 0,45 · **Gültigkeit:** X 0,00–1,00 · Y 0,00–0,40 · Z 0,25–0,65
- **Muster:** `x..........x....` · **Einsätze (Ticks):** 0, 2640 · **Akzente:** keine · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 2,00 Einsätze/Takt · **VK:** 0,38 · **Unruhe-Typ:** –
- **Rollen:** TU KF · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R019, EM-R026, EM-R035, EM-R036, EM-R037
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** N – nachgewiesenes Verfahren (Version mit zögernden Pausen (cuebycue)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R019 – Großer Leerraum: ein Ereignis in zwei Takten
- **Charakter:** Stille trägt · **Säule:** AB · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,15 / 0,20 · **Gültigkeit:** X 0,00–1,00 · Y 0,00–0,35 · Z 0,00–0,40
- **Muster:** `X...............................` · **Einsätze (Ticks):** 0 · **Akzente:** 0 · **Periode:** 7680 Ticks
- **Gesamtzyklus:** 7680 Ticks (2.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 0,50 Einsätze/Takt · **VK:** 0,00 · **Unruhe-Typ:** –
- **Rollen:** TU ST KF · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R001, EM-R002, EM-R003, EM-R005, EM-R006
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** N – nachgewiesenes Verfahren (Stille als Ereignis (Wilcox)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R020 – Puls mit kurzem Aussetzen
- **Charakter:** Atemaussetzer · **Säule:** B · **Takt:** 4/4 · **Raster:** e (480 Ticks)
- **XYZ-Anker:** beliebig / 0,50 / 0,55 · **Gültigkeit:** X 0,00–1,00 · Y 0,30–0,70 · Z 0,35–0,75
- **Muster:** `xxxxxxxxxxxx....` · **Einsätze (Ticks):** 0, 480, 960, 1440, 1920, 2400, 2880, 3360, 3840, 4320, 4800, 5280 · **Akzente:** keine · **Periode:** 7680 Ticks
- **Gesamtzyklus:** 7680 Ticks (2.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 6,00 Einsätze/Takt · **VK:** 0,83 · **Unruhe-Typ:** psychologisch
- **Rollen:** KB AR · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R004, EM-R005, EM-R006, EM-R008, EM-R013
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** N – nachgewiesenes Verfahren („briefly drops out“ (cuebycue)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R021 – Synkopierter Bass A
- **Charakter:** nervös federnd · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,55 / 0,55 · **Gültigkeit:** X 0,00–1,00 · Y 0,35–0,75 · Z 0,35–0,75
- **Muster:** `X..x..x...x.x...` · **Einsätze (Ticks):** 0, 720, 1440, 2400, 2880 · **Akzente:** 0 · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 5,00 Einsätze/Takt · **VK:** 0,23 · **Unruhe-Typ:** mechanisch
- **Rollen:** KB · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R007, EM-R009, EM-R014, EM-R022, EM-R027
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R001, EM-R002, EM-R013, EM-R035, EM-R036
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** N – nachgewiesenes Verfahren (synkopierter Bass (cuebycue: Cat o' Nine Tails)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R022 – Synkopierter Bass B (Auftakt-Akzent)
- **Charakter:** lauernd · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,45 / 0,60 · **Gültigkeit:** X 0,00–1,00 · Y 0,25–0,65 · Z 0,40–0,80
- **Muster:** `.X..x..X..x.....` · **Einsätze (Ticks):** 240, 960, 1680, 2400 · **Akzente:** 240, 1680 · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 4,00 Einsätze/Takt · **VK:** 0,43 · **Unruhe-Typ:** psychologisch
- **Rollen:** KB · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R001, EM-R002, EM-R003, EM-R008, EM-R009
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R013, EM-R050
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** E – eigenständige Gestaltung (Synkopierung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R023 – Zwölf-Ereignis-Figur über zwei Takte
- **Charakter:** obsessiv · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,60 / 0,60 · **Gültigkeit:** X 0,00–1,00 · Y 0,40–0,80 · Z 0,40–0,80
- **Muster:** `X.x.xx.x..x.x...X..x.x..x.x.....` · **Einsätze (Ticks):** 0, 480, 960, 1200, 1680, 2400, 2880, 3840, 4560, 5040, 5760, 6240 · **Akzente:** 0, 3840 · **Periode:** 7680 Ticks
- **Gesamtzyklus:** 7680 Ticks (2.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 6,00 Einsätze/Takt · **VK:** 0,47 · **Unruhe-Typ:** psychologisch
- **Rollen:** KB · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** –
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R001, EM-R002, EM-R013, EM-R014, EM-R017
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** N – nachgewiesenes Verfahren (12-Ton-Bassrhythmus (cuebycue)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R024 – Spieluhr-Achtel mit Atemlücke
- **Charakter:** kindlich, unbeirrt · **Säule:** AB · **Takt:** 4/4 · **Raster:** e (480 Ticks)
- **XYZ-Anker:** beliebig / 0,20 / 0,25 · **Gültigkeit:** X 0,00–1,00 · Y 0,00–0,40 · Z 0,05–0,45
- **Muster:** `xxxxxxx.` · **Einsätze (Ticks):** 0, 480, 960, 1440, 1920, 2400, 2880 · **Akzente:** keine · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 7,00 Einsätze/Takt · **VK:** 0,31 · **Unruhe-Typ:** –
- **Rollen:** AR TU · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R004, EM-R005, EM-R006, EM-R008, EM-R013
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** N – nachgewiesenes Verfahren (Spieluhr-Wiederholung (Argento; Untouchables)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R025 – Spieluhr 3/4
- **Charakter:** Walzer der Unschuld · **Säule:** AB · **Takt:** 3/4 · **Raster:** e (480 Ticks)
- **XYZ-Anker:** beliebig / 0,20 / 0,30 · **Gültigkeit:** X 0,00–1,00 · Y 0,00–0,40 · Z 0,10–0,50
- **Muster:** `xxxxxx` · **Einsätze (Ticks):** 0, 480, 960, 1440, 1920, 2400 · **Akzente:** keine · **Periode:** 2880 Ticks
- **Gesamtzyklus:** 2880 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 6,00 Einsätze/Takt · **VK:** 0,00 · **Unruhe-Typ:** –
- **Rollen:** AR TU · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** –
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** –
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** I – begründete Interpretation (Spieluhr); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R026 – Glocke alle fünf Viertel
- **Charakter:** zeitlos mahnend · **Säule:** AB · **Takt:** 4/4 · **Raster:** q (960 Ticks)
- **XYZ-Anker:** beliebig / 0,25 / 0,35 · **Gültigkeit:** X 0,00–1,00 · Y 0,05–0,45 · Z 0,15–0,55
- **Muster:** `X....` · **Einsätze (Ticks):** 0 · **Akzente:** 0 · **Periode:** 4800 Ticks
- **Gesamtzyklus:** 19200 Ticks (5.00 Takte) · **inkongruent zum Takt:** ja · **Dichte:** 0,80 Einsätze/Takt · **VK:** 0,00 · **Unruhe-Typ:** –
- **Rollen:** TU ST LF · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R001, EM-R002, EM-R003, EM-R007, EM-R008
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** unabhängige Periodenlänge je Rolle
- **Evidenz:** I – begründete Interpretation (Periode gegen Takt); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R027 – Kontrahierende Terzpaare
- **Charakter:** enger werdend (in sich) · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,45 / 0,60 · **Gültigkeit:** X 0,00–1,00 · Y 0,25–0,65 · Z 0,40–0,80
- **Muster:** `x...x...x..x..x.x.x.xx` · **Einsätze (Ticks):** 0, 960, 1920, 2640, 3360, 3840, 4320, 4800, 5040 · **Akzente:** keine · **Periode:** 5280 Ticks
- **Gesamtzyklus:** 42240 Ticks (11.00 Takte) · **inkongruent zum Takt:** ja · **Dichte:** 6,55 Einsätze/Takt · **VK:** 0,44 · **Unruhe-Typ:** psychologisch
- **Rollen:** AR KB · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R003, EM-R021, EM-R022, EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R008, EM-R009, EM-R013, EM-R035, EM-R036
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** unabhängige Periodenlänge je Rolle
- **Evidenz:** N – nachgewiesenes Verfahren (rhythmische Kontraktion (Wilcox: Drittes Konzert)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R028 – Daktylus
- **Charakter:** drängend-tänzerisch · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,55 / 0,45 · **Gültigkeit:** X 0,00–1,00 · Y 0,35–0,75 · Z 0,25–0,65
- **Muster:** `X.xx` · **Einsätze (Ticks):** 0, 480, 720 · **Akzente:** 0 · **Periode:** 960 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 12,00 Einsätze/Takt · **VK:** 0,35 · **Unruhe-Typ:** –
- **Rollen:** KB AR · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R022, EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R001, EM-R002, EM-R008, EM-R013, EM-R023
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** E – eigenständige Gestaltung (rhythmische Zelle); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R029 – Anapäst
- **Charakter:** anlaufend · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,55 / 0,50 · **Gültigkeit:** X 0,00–1,00 · Y 0,35–0,75 · Z 0,30–0,70
- **Muster:** `xxX.` · **Einsätze (Ticks):** 0, 240, 480 · **Akzente:** 480 · **Periode:** 960 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 12,00 Einsätze/Takt · **VK:** 0,35 · **Unruhe-Typ:** psychologisch
- **Rollen:** KB AR ST · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R007, EM-R008, EM-R013, EM-R019, EM-R026
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** E – eigenständige Gestaltung (rhythmische Zelle); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R030 – Mehrdeutiger Doppelpuls (Jambus/Trochäus)
- **Charakter:** ruhig-unheimlich · **Säule:** B · **Takt:** 4/4 · **Raster:** q (960 Ticks)
- **XYZ-Anker:** beliebig / 0,20 / 0,35 · **Gültigkeit:** X 0,00–1,00 · Y 0,00–0,40 · Z 0,15–0,55
- **Schicht „a“: Muster:** `x.........` · **Einsätze (Ticks):** 0 · **Akzente:** keine · **Periode:** 9600 Ticks
- **Schicht „b“: Muster:** `.....x....` · **Einsätze (Ticks):** 4800 · **Akzente:** keine · **Periode:** 9600 Ticks
- **Gesamtzyklus:** 19200 Ticks (5.00 Takte) · **inkongruent zum Takt:** ja · **Dichte:** 0,80 Einsätze/Takt · **VK:** 0,00 · **Unruhe-Typ:** –
- **Rollen:** ST TU LB · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R007, EM-R012, EM-R014, EM-R017, EM-R019
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** unabhängige Periodenlänge je Rolle; mehrschichtiges Muster
- **Evidenz:** N – nachgewiesenes Verfahren (gleiche Anschläge, Abstand macht Metrum mehrdeutig (Covell: Suoni per Dino)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R031 – Lange Note mit spätem Nachschlag
- **Charakter:** Seufzer · **Säule:** A · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,30 / 0,25 · **Gültigkeit:** X 0,00–1,00 · Y 0,10–0,50 · Z 0,05–0,45
- **Muster:** `X-------......x.` · **Einsätze (Ticks):** 0, 3360 · **Akzente:** 0 · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 2,00 Einsätze/Takt · **VK:** 0,75 · **Unruhe-Typ:** –
- **Rollen:** LF KF GS · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R005, EM-R006, EM-R013, EM-R019, EM-R026
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** E – eigenständige Gestaltung (rhythmischer Leerraum); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R032 – Ternäre Fanfarenzelle
- **Charakter:** würdig, aufrichtend · **Säule:** A · **Takt:** 4/4 · **Raster:** t (320 Ticks)
- **XYZ-Anker:** beliebig / 0,65 / 0,30 · **Gültigkeit:** X 0,00–1,00 · Y 0,45–0,85 · Z 0,10–0,50
- **Muster:** `X.xX..x.....` · **Einsätze (Ticks):** 0, 640, 960, 1920 · **Akzente:** 0, 960 · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 4,00 Einsätze/Takt · **VK:** 0,62 · **Unruhe-Typ:** –
- **Rollen:** KF HM · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R019, EM-R039, EM-R052, EM-R062
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** E – eigenständige Gestaltung (ternäre Zelle); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R033 – Hemiole 3/4 (2+2+2)
- **Charakter:** breiter werdend · **Säule:** A · **Takt:** 3/4 · **Raster:** e (480 Ticks)
- **XYZ-Anker:** beliebig / 0,50 / 0,35 · **Gültigkeit:** X 0,00–1,00 · Y 0,30–0,70 · Z 0,15–0,55
- **Muster:** `X.X.X.` · **Einsätze (Ticks):** 0, 960, 1920 · **Akzente:** 0, 960, 1920 · **Periode:** 2880 Ticks
- **Gesamtzyklus:** 2880 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 3,00 Einsätze/Takt · **VK:** 0,00 · **Unruhe-Typ:** –
- **Rollen:** KF KB · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** –
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** –
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** E – eigenständige Gestaltung (Akzentverschiebung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R034 – 5/4 als 3+2
- **Charakter:** schreitend, unregelmäßig · **Säule:** AB · **Takt:** 5/4 · **Raster:** e (480 Ticks)
- **XYZ-Anker:** beliebig / 0,45 / 0,40 · **Gültigkeit:** X 0,00–1,00 · Y 0,25–0,65 · Z 0,20–0,60
- **Muster:** `X.x.xX.x.x` · **Einsätze (Ticks):** 0, 960, 1920, 2400, 3360, 4320 · **Akzente:** 0, 2400 · **Periode:** 4800 Ticks
- **Gesamtzyklus:** 4800 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 6,00 Einsätze/Takt · **VK:** 0,28 · **Unruhe-Typ:** –
- **Rollen:** KB AR · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** –
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** –
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** E – eigenständige Gestaltung (unregelmäßige Taktgruppe); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R035 – Polyperiodik 3 gegen 4 (Schichten)
- **Charakter:** mechanisch verzahnt · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,45 / 0,55 · **Gültigkeit:** X 0,00–1,00 · Y 0,25–0,65 · Z 0,35–0,75
- **Schicht „drei“: Muster:** `X..` · **Einsätze (Ticks):** 0 · **Akzente:** 0 · **Periode:** 720 Ticks
- **Schicht „vier“: Muster:** `X...` · **Einsätze (Ticks):** 0 · **Akzente:** 0 · **Periode:** 960 Ticks
- **Gesamtzyklus:** 11520 Ticks (3.00 Takte) · **inkongruent zum Takt:** ja · **Dichte:** 1,33 Einsätze/Takt · **VK:** 0,00 · **Unruhe-Typ:** psychologisch
- **Rollen:** AR KB TU · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R022, EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R001, EM-R002, EM-R003, EM-R004, EM-R005
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** unabhängige Periodenlänge je Rolle; mehrschichtiges Muster
- **Evidenz:** N – nachgewiesenes Verfahren (inkongruente Perioden (Miceli: periodicità oscillante)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R036 – Polyperiodik 5 gegen 4 (Schichten)
- **Charakter:** rastlos verzahnt · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,50 / 0,65 · **Gültigkeit:** X 0,00–1,00 · Y 0,30–0,70 · Z 0,45–0,85
- **Schicht „fuenf“: Muster:** `X....` · **Einsätze (Ticks):** 0 · **Akzente:** 0 · **Periode:** 1200 Ticks
- **Schicht „vier“: Muster:** `X...` · **Einsätze (Ticks):** 0 · **Akzente:** 0 · **Periode:** 960 Ticks
- **Gesamtzyklus:** 19200 Ticks (5.00 Takte) · **inkongruent zum Takt:** ja · **Dichte:** 0,80 Einsätze/Takt · **VK:** 0,00 · **Unruhe-Typ:** psychologisch
- **Rollen:** AR KB TU · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R022, EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R001, EM-R002, EM-R003, EM-R004, EM-R005
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** unabhängige Periodenlänge je Rolle; mehrschichtiges Muster
- **Evidenz:** N – nachgewiesenes Verfahren (inkongruente Perioden); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R037 – Polyperiodik 7 gegen 8 (Schichten)
- **Charakter:** fast synchron, driftend · **Säule:** B · **Takt:** 4/4 · **Raster:** e (480 Ticks)
- **XYZ-Anker:** beliebig / 0,35 / 0,45 · **Gültigkeit:** X 0,00–1,00 · Y 0,15–0,55 · Z 0,25–0,65
- **Schicht „sieben“: Muster:** `X......` · **Einsätze (Ticks):** 0 · **Akzente:** 0 · **Periode:** 3360 Ticks
- **Schicht „acht“: Muster:** `X.......` · **Einsätze (Ticks):** 0 · **Akzente:** 0 · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 26880 Ticks (7.00 Takte) · **inkongruent zum Takt:** ja · **Dichte:** 0,14 Einsätze/Takt · **VK:** 0,00 · **Unruhe-Typ:** –
- **Rollen:** AR TU · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R022, EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R004, EM-R005, EM-R006, EM-R007, EM-R008
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** unabhängige Periodenlänge je Rolle; mehrschichtiges Muster
- **Evidenz:** E – eigenständige Gestaltung (Phasenversatz); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R038 – Schnelle Repetition gegen lange Akkorde
- **Charakter:** zitternde Ruhe · **Säule:** AB · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,45 / 0,45 · **Gültigkeit:** X 0,00–1,00 · Y 0,25–0,65 · Z 0,25–0,65
- **Schicht „rep“: Muster:** `xxxxxxxxxxxxxxxx` · **Einsätze (Ticks):** 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600 · **Akzente:** keine · **Periode:** 3840 Ticks
- **Schicht „akk“: Muster:** `X-------X-------` · **Einsätze (Ticks):** 0, 1920 · **Akzente:** 0, 1920 · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 16,00 Einsätze/Takt · **VK:** 0,00 · **Unruhe-Typ:** –
- **Rollen:** AR LF KF · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** –
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R004, EM-R005, EM-R006, EM-R007, EM-R008
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster; mehrschichtiges Muster
- **Evidenz:** I – begründete Interpretation (schnelle Unterschicht gegen langsame Oberstimme); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R039 – Anschlag mit leisem Echo
- **Charakter:** Nachhall der Angst · **Säule:** AB · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,30 / 0,35 · **Gültigkeit:** X 0,00–1,00 · Y 0,10–0,50 · Z 0,15–0,55
- **Muster:** `X...x...........` · **Einsätze (Ticks):** 0, 960 · **Akzente:** 0 · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 2,00 Einsätze/Takt · **VK:** 0,50 · **Unruhe-Typ:** –
- **Rollen:** TU KF · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R005, EM-R006, EM-R007, EM-R012, EM-R019
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** I – begründete Interpretation (Echo-Effekt (NPR: Klavier/Perkussion)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R040 – Zweiunddreißigstel-Zittern
- **Charakter:** mechanische Erregung · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,40 / 0,75 · **Gültigkeit:** X 0,00–1,00 · Y 0,20–0,60 · Z 0,55–0,95
- **Muster:** `xxxxxxxxxxxxxxxx` · **Einsätze (Ticks):** 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600 · **Akzente:** keine · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 16,00 Einsätze/Takt · **VK:** 0,00 · **Unruhe-Typ:** mechanisch
- **Rollen:** AR · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** –
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R004, EM-R005, EM-R006, EM-R007, EM-R008
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** E – eigenständige Gestaltung (mechanische Unruhe); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R041 – Ametrische Einzelereignisse (lose)
- **Charakter:** schwebend, unvorhersehbar · **Säule:** B · **Takt:** 4/4 · **Raster:** @ (ametrisch, explizite Ticks)
- **XYZ-Anker:** beliebig / 0,25 / 0,60 · **Gültigkeit:** X 0,00–1,00 · Y 0,05–0,45 · Z 0,40–0,80
- **Muster:** `@0,1130,2970,5210,6990` · **Einsätze (Ticks):** 0, 1130, 2970, 5210, 6990 · **Akzente:** 0 · **Periode:** 7680 Ticks
- **Gesamtzyklus:** 7680 Ticks (2.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 2,50 Einsätze/Takt · **VK:** 0,36 · **Unruhe-Typ:** psychologisch
- **Rollen:** TU ST · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** –
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** –
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster; unregelmäßige Tickpositionen
- **Evidenz:** N – nachgewiesenes Verfahren (kein präzises Metrum (Morricone zu Bird)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R042 – Ametrische Ereignisse (dichter)
- **Charakter:** nervöse Streuung · **Säule:** B · **Takt:** 4/4 · **Raster:** @ (ametrisch, explizite Ticks)
- **XYZ-Anker:** beliebig / 0,45 / 0,80 · **Gültigkeit:** X 0,00–1,00 · Y 0,25–0,65 · Z 0,60–1,00
- **Muster:** `@0,410,1260,1580,2900,3310,4870,5020,6400` · **Einsätze (Ticks):** 0, 410, 1260, 1580, 2900, 3310, 4870, 5020, 6400 · **Akzente:** 0 · **Periode:** 7680 Ticks
- **Gesamtzyklus:** 7680 Ticks (2.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 4,50 Einsätze/Takt · **VK:** 0,60 · **Unruhe-Typ:** psychologisch
- **Rollen:** TU ST KF · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** –
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** –
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster; unregelmäßige Tickpositionen
- **Evidenz:** N – nachgewiesenes Verfahren (ametrische Multipla); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R043 – Rubato-Zögern über zwei Takte
- **Charakter:** atmend, zögernd · **Säule:** A · **Takt:** 4/4 · **Raster:** @ (ametrisch, explizite Ticks)
- **XYZ-Anker:** beliebig / 0,25 / 0,35 · **Gültigkeit:** X 0,00–1,00 · Y 0,05–0,45 · Z 0,15–0,55
- **Muster:** `@0,1100,1780,4140,5600` · **Einsätze (Ticks):** 0, 1100, 1780, 4140, 5600 · **Akzente:** 0 · **Periode:** 7680 Ticks
- **Gesamtzyklus:** 7680 Ticks (2.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 2,50 Einsätze/Takt · **VK:** 0,40 · **Unruhe-Typ:** –
- **Rollen:** TU HM GS · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** –
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** –
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster; unregelmäßige Tickpositionen
- **Evidenz:** E – eigenständige Gestaltung (unregelmäßige Zeitpositionen); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R044 – Schritt-Puls mit Pause auf 4
- **Charakter:** gefasst schreitend · **Säule:** A · **Takt:** 4/4 · **Raster:** e (480 Ticks)
- **XYZ-Anker:** beliebig / 0,40 / 0,20 · **Gültigkeit:** X 0,00–1,00 · Y 0,20–0,60 · Z 0,00–0,40
- **Muster:** `x.x.x...` · **Einsätze (Ticks):** 0, 960, 1920 · **Akzente:** keine · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 3,00 Einsätze/Takt · **VK:** 0,35 · **Unruhe-Typ:** –
- **Rollen:** KB LB · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R004, EM-R005, EM-R006, EM-R012, EM-R013
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** E – eigenständige Gestaltung (rhythmischer Leerraum); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R045 – Unregelmäßiger Herzschlag (Paranoia)
- **Charakter:** panisch verdeckt · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,40 / 0,70 · **Gültigkeit:** X 0,00–1,00 · Y 0,20–0,60 · Z 0,50–0,90
- **Muster:** `X..x........X.x.......X..x......` · **Einsätze (Ticks):** 0, 720, 2880, 3360, 5280, 6000 · **Akzente:** 0, 2880, 5280 · **Periode:** 7680 Ticks
- **Gesamtzyklus:** 7680 Ticks (2.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 3,00 Einsätze/Takt · **VK:** 0,52 · **Unruhe-Typ:** psychologisch
- **Rollen:** KB ST · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R007, EM-R009, EM-R014, EM-R022, EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R001, EM-R002, EM-R013, EM-R019, EM-R026
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** E – eigenständige Gestaltung (Herzschlag + Unregelmäßigkeit); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R046 – Triolischer Boden, Viertel oben
- **Charakter:** getragen, drängend · **Säule:** AB · **Takt:** 4/4 · **Raster:** t (320 Ticks)
- **XYZ-Anker:** beliebig / 0,55 / 0,40 · **Gültigkeit:** X 0,00–1,00 · Y 0,35–0,75 · Z 0,20–0,60
- **Schicht „boden“: Muster:** `xxxxxxxxxxxx` · **Einsätze (Ticks):** 0, 320, 640, 960, 1280, 1600, 1920, 2240, 2560, 2880, 3200, 3520 · **Akzente:** keine · **Periode:** 3840 Ticks
- **Schicht „oben“: Muster:** `x..x..x..x..` · **Einsätze (Ticks):** 0, 960, 1920, 2880 · **Akzente:** keine · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 12,00 Einsätze/Takt · **VK:** 0,00 · **Unruhe-Typ:** –
- **Rollen:** AR KB LF · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R011, EM-R012, EM-R017, EM-R026, EM-R035
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster; mehrschichtiges Muster
- **Evidenz:** I – begründete Interpretation (Schichten unterschiedlicher Teilung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R047 – Dreiviertel-Periode über 4/4 (lange Atmung)
- **Charakter:** ruhig verschoben · **Säule:** AB · **Takt:** 4/4 · **Raster:** q (960 Ticks)
- **XYZ-Anker:** beliebig / 0,25 / 0,30 · **Gültigkeit:** X 0,00–1,00 · Y 0,05–0,45 · Z 0,10–0,50
- **Muster:** `X..` · **Einsätze (Ticks):** 0 · **Akzente:** 0 · **Periode:** 2880 Ticks
- **Gesamtzyklus:** 11520 Ticks (3.00 Takte) · **inkongruent zum Takt:** ja · **Dichte:** 1,33 Einsätze/Takt · **VK:** 0,00 · **Unruhe-Typ:** –
- **Rollen:** TU LF KB · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R001, EM-R002, EM-R003, EM-R004, EM-R005
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** unabhängige Periodenlänge je Rolle
- **Evidenz:** E – eigenständige Gestaltung (Periode 3 Viertel); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R048 – Mechanische Akzentwanderung (jede dritte Sechzehntel)
- **Charakter:** Maschine mit Fehler · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,50 / 0,70 · **Gültigkeit:** X 0,00–1,00 · Y 0,30–0,70 · Z 0,50–0,90
- **Muster:** `Xxx` · **Einsätze (Ticks):** 0, 240, 480 · **Akzente:** 0 · **Periode:** 720 Ticks
- **Gesamtzyklus:** 11520 Ticks (3.00 Takte) · **inkongruent zum Takt:** ja · **Dichte:** 16,00 Einsätze/Takt · **VK:** 0,00 · **Unruhe-Typ:** mechanisch
- **Rollen:** AR · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R007, EM-R008, EM-R013, EM-R029, EM-R035
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** unabhängige Periodenlänge je Rolle
- **Evidenz:** E – eigenständige Gestaltung (Akzentverschiebung, mechanische Unruhe); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R049 – Psychologische Unruhe bei geringer Dichte
- **Charakter:** Beklemmung · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,20 / 0,75 · **Gültigkeit:** X 0,00–1,00 · Y 0,00–0,40 · Z 0,55–0,95
- **Muster:** `x.....x.........x..........x....` · **Einsätze (Ticks):** 0, 1440, 3840, 6480 · **Akzente:** keine · **Periode:** 7680 Ticks
- **Gesamtzyklus:** 7680 Ticks (2.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 2,00 Einsätze/Takt · **VK:** 0,32 · **Unruhe-Typ:** psychologisch
- **Rollen:** TU KF ST · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R022, EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R015, EM-R018, EM-R019, EM-R026, EM-R035
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** E – eigenständige Gestaltung (Unruhe ohne Dichte); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R050 – Akzentgruppen 3+3+3+3+2+2
- **Charakter:** drängend asymmetrisch · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,60 / 0,55 · **Gültigkeit:** X 0,00–1,00 · Y 0,40–0,80 · Z 0,35–0,75
- **Muster:** `XxxXxxXxxXxxXxXx` · **Einsätze (Ticks):** 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600 · **Akzente:** 0, 720, 1440, 2160, 2880, 3360 · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 16,00 Einsätze/Takt · **VK:** 0,00 · **Unruhe-Typ:** mechanisch
- **Rollen:** AR KB · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** –
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R001, EM-R002, EM-R003, EM-R004, EM-R005
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** E – eigenständige Gestaltung (Akzentgruppen); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R051 – Akzentgruppen 2+2+3+2+3+2+2
- **Charakter:** tänzerisch nervös · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,55 / 0,60 · **Gültigkeit:** X 0,00–1,00 · Y 0,35–0,75 · Z 0,40–0,80
- **Muster:** `XxXxXxxXxXxxXxXx` · **Einsätze (Ticks):** 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600 · **Akzente:** 0, 480, 960, 1680, 2160, 2880, 3360 · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 16,00 Einsätze/Takt · **VK:** 0,00 · **Unruhe-Typ:** mechanisch
- **Rollen:** AR · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** –
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R004, EM-R005, EM-R006, EM-R007, EM-R008
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** E – eigenständige Gestaltung (Akzentgruppen); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R052 – Halbe Noten, schwer
- **Charakter:** monumental, ruhig · **Säule:** A · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,80 / 0,15 · **Gültigkeit:** X 0,00–1,00 · Y 0,60–1,00 · Z 0,00–0,35
- **Muster:** `X-------X-------` · **Einsätze (Ticks):** 0, 1920 · **Akzente:** 0, 1920 · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 2,00 Einsätze/Takt · **VK:** 0,00 · **Unruhe-Typ:** –
- **Rollen:** LF KB LB KF · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R004, EM-R005, EM-R006, EM-R012, EM-R013
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** E – eigenständige Gestaltung (Kraft ohne Hektik); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R053 – Marcato-Block mit Stille
- **Charakter:** drei Schläge, dann nichts · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,75 / 0,45 · **Gültigkeit:** X 0,00–1,00 · Y 0,55–0,95 · Z 0,25–0,65
- **Muster:** `X.X.X...........` · **Einsätze (Ticks):** 0, 480, 960 · **Akzente:** 0, 480, 960 · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 3,00 Einsätze/Takt · **VK:** 0,88 · **Unruhe-Typ:** –
- **Rollen:** KF ST KB · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R004, EM-R005, EM-R006, EM-R007, EM-R013
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** I – begründete Interpretation („little blocks of notes“ (NPR)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R054 – Kleine Notenblöcke
- **Charakter:** pochend · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,55 / 0,45 · **Gültigkeit:** X 0,00–1,00 · Y 0,35–0,75 · Z 0,25–0,65
- **Muster:** `xxxx....xxxx....` · **Einsätze (Ticks):** 0, 240, 480, 720, 1920, 2160, 2400, 2640 · **Akzente:** keine · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 8,00 Einsätze/Takt · **VK:** 0,87 · **Unruhe-Typ:** –
- **Rollen:** KF AR · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R012, EM-R046, EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R008, EM-R013, EM-R018, EM-R019, EM-R028
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** I – begründete Interpretation (Notenblöcke in Streichern (NPR)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R055 – Späte Antwort am Taktende
- **Charakter:** Nachsatz · **Säule:** AB · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,35 / 0,45 · **Gültigkeit:** X 0,00–1,00 · Y 0,15–0,55 · Z 0,25–0,65
- **Muster:** `.......X.......x` · **Einsätze (Ticks):** 1680, 3600 · **Akzente:** 1680 · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 2,00 Einsätze/Takt · **VK:** 0,00 · **Unruhe-Typ:** –
- **Rollen:** TU KF · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R008, EM-R012, EM-R018, EM-R019, EM-R024
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R038
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** E – eigenständige Gestaltung (Antwortlogik); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R056 – Lyrische Antizipation
- **Charakter:** Sehnsucht greift vor · **Säule:** A · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,35 / 0,25 · **Gültigkeit:** X 0,00–1,00 · Y 0,15–0,55 · Z 0,05–0,45
- **Muster:** `X-----x-X-------` · **Einsätze (Ticks):** 0, 1440, 1920 · **Akzente:** 0, 1920 · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 3,00 Einsätze/Takt · **VK:** 0,47 · **Unruhe-Typ:** –
- **Rollen:** HM GS · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R013
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** E – eigenständige Gestaltung (Antizipation (nicht belegt, kein Verbot)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R057 – Halbe-Triolen gegen Takt
- **Charakter:** breites Ziehen · **Säule:** A · **Takt:** 4/4 · **Raster:** @ (ametrisch, explizite Ticks)
- **XYZ-Anker:** beliebig / 0,40 / 0,35 · **Gültigkeit:** X 0,00–1,00 · Y 0,20–0,60 · Z 0,15–0,55
- **Muster:** `@0,1280,2560` · **Einsätze (Ticks):** 0, 1280, 2560 · **Akzente:** 0 · **Periode:** 7680 Ticks
- **Gesamtzyklus:** 7680 Ticks (2.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 1,50 Einsätze/Takt · **VK:** 0,71 · **Unruhe-Typ:** –
- **Rollen:** LF KF GS · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** –
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** –
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster; unregelmäßige Tickpositionen
- **Evidenz:** E – eigenständige Gestaltung (ternäre Dehnung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R058 – Wiege 6/8
- **Charakter:** zart wiegend · **Säule:** A · **Takt:** 6/8 · **Raster:** e (480 Ticks)
- **XYZ-Anker:** beliebig / 0,25 / 0,20 · **Gültigkeit:** X 0,00–1,00 · Y 0,05–0,45 · Z 0,00–0,40
- **Muster:** `X.xx.x` · **Einsätze (Ticks):** 0, 960, 1440, 2400 · **Akzente:** 0 · **Periode:** 2880 Ticks
- **Gesamtzyklus:** 2880 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 4,00 Einsätze/Takt · **VK:** 0,33 · **Unruhe-Typ:** –
- **Rollen:** AR KB · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** –
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** –
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** I – begründete Interpretation (ternäre Bewegung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R059 – Sinnliche Zwölfachtel
- **Charakter:** warm schwingend · **Säule:** A · **Takt:** 12/8 · **Raster:** e (480 Ticks)
- **XYZ-Anker:** beliebig / 0,35 / 0,25 · **Gültigkeit:** X 0,00–1,00 · Y 0,15–0,55 · Z 0,05–0,45
- **Muster:** `X.xx.xX.xx.x` · **Einsätze (Ticks):** 0, 960, 1440, 2400, 2880, 3840, 4320, 5280 · **Akzente:** 0, 2880 · **Periode:** 5760 Ticks
- **Gesamtzyklus:** 5760 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 8,00 Einsätze/Takt · **VK:** 0,33 · **Unruhe-Typ:** –
- **Rollen:** AR KB · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** –
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R010
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** N – nachgewiesenes Verfahren (ternärer Rhythmus (Morricone zu Indagine)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R060 – Tiefe Unisono-Achtel mit Atempause
- **Charakter:** kraftvoll, beherrscht · **Säule:** B · **Takt:** 4/4 · **Raster:** e (480 Ticks)
- **XYZ-Anker:** beliebig / 0,75 / 0,35 · **Gültigkeit:** X 0,00–1,00 · Y 0,55–0,95 · Z 0,15–0,55
- **Muster:** `xxxxxx..` · **Einsätze (Ticks):** 0, 480, 960, 1440, 1920, 2400 · **Akzente:** keine · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 6,00 Einsätze/Takt · **VK:** 0,56 · **Unruhe-Typ:** –
- **Rollen:** KB AR · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R004, EM-R005, EM-R006, EM-R008, EM-R013
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** I – begründete Interpretation (Gewichtsschicht mit Leerraum); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R061 – Halbtaktstoß
- **Charakter:** schwerer Atem · **Säule:** B · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,65 / 0,30 · **Gültigkeit:** X 0,00–1,00 · Y 0,45–0,85 · Z 0,10–0,50
- **Muster:** `X.......X.......` · **Einsätze (Ticks):** 0, 1920 · **Akzente:** 0, 1920 · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 2,00 Einsätze/Takt · **VK:** 0,00 · **Unruhe-Typ:** –
- **Rollen:** KB ST LB · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R022, EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R004, EM-R005, EM-R006, EM-R012, EM-R013
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** E – eigenständige Gestaltung (Gewicht); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R062 – Ein Schlag in vier Takten
- **Charakter:** Fermate des Raums · **Säule:** AB · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,15 / 0,15 · **Gültigkeit:** X 0,00–1,00 · Y 0,00–0,35 · Z 0,00–0,35
- **Muster:** `X...............................................................` · **Einsätze (Ticks):** 0 · **Akzente:** 0 · **Periode:** 15360 Ticks
- **Gesamtzyklus:** 15360 Ticks (4.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 0,25 Einsätze/Takt · **VK:** 0,00 · **Unruhe-Typ:** –
- **Rollen:** ST TU KF · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R001, EM-R002, EM-R003, EM-R005, EM-R006
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** N – nachgewiesenes Verfahren (Stille (Wilcox; Union Station: Musik fällt weg)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R063 – Sprechpausen-Puls (1 und 3)
- **Charakter:** dialogfreundlich · **Säule:** AB · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,25 / 0,20 · **Gültigkeit:** X 0,00–1,00 · Y 0,05–0,45 · Z 0,00–0,40
- **Muster:** `x.......x.......` · **Einsätze (Ticks):** 0, 1920 · **Akzente:** keine · **Periode:** 3840 Ticks
- **Gesamtzyklus:** 3840 Ticks (1.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 2,00 Einsätze/Takt · **VK:** 0,00 · **Unruhe-Typ:** –
- **Rollen:** KB LB TU · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R004, EM-R005, EM-R006, EM-R012, EM-R013
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** E – eigenständige Gestaltung (Puls mit Raum); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-R064 – Additive Pulsöffnung (1 → 2 → 3 Ereignisse)
- **Charakter:** langsames Erwachen · **Säule:** AB · **Takt:** 4/4 · **Raster:** s (240 Ticks)
- **XYZ-Anker:** beliebig / 0,35 / 0,40 · **Gültigkeit:** X 0,00–1,00 · Y 0,15–0,55 · Z 0,20–0,60
- **Muster:** `X...............X.......X.......X....X....X.....` · **Einsätze (Ticks):** 0, 3840, 5760, 7680, 8880, 10080 · **Akzente:** 0, 3840, 5760, 7680, 8880, 10080 · **Periode:** 11520 Ticks
- **Gesamtzyklus:** 11520 Ticks (3.00 Takte) · **inkongruent zum Takt:** nein · **Dichte:** 2,00 Einsätze/Takt · **VK:** 0,47 · **Unruhe-Typ:** –
- **Rollen:** TU KF KB · **Notendauern:** bis zum nächsten Einsatz bzw. Haltebogen, rollenabhängiges Gate (KB 0,85, AR 0,6–0,9)
- **Geeignete Kombinationen (komplementär, ≤ 25 % gemeinsame Einsätze):** EM-R055
- **Ungeeignete Kombinationen (redundant, ≥ 90 % gleiche Einsätze in gleicher Rolle):** EM-R013, EM-R019, EM-R023, EM-R026, EM-R035
- **Transformation:** EM-T006/EM-T007 (Kontraktion/Extension), EM-T008 (Phasenversatz), EM-T005 (additiv) · **Entwicklung:** Stasis, Atmung (Ein-/Ausblenden einzelner Einsätze), Reduktion und Wiederaufnahme
- **Algorithmische Voraussetzungen:** Taktraster
- **Evidenz:** N – nachgewiesenes Verfahren (additive Enthüllung (Filmtracks: Nitti 2→4→7→10)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

## 9. B – Bassführung

Typ **AKK** = akkordgebunden (die Figur setzt die passende Harmoniefolge voraus), **EIG** = eigenständig (eigene Linie; Tonvorrat muss passen), **DIS** = ausdrücklich dissonanzautorisiert (Töne tragen F/U gegen die Oberharmonik). Negative Dauer = Pause. Ton- und Rhythmusperiode dürfen verschieden lang sein; der Gesamtzyklus wird berechnet.

### EM-B001 – Tonikapedal lang
- **Charakter:** Fundament, Ruhe · **Säule:** AB · **Typ:** EIG · **Rollen:** LB
- **XYZ-Anker:** beliebig / 0,30 / 0,10 · **Gültigkeit:** X 0,00–1,00 · Y 0,10–0,50 · Z 0,00–0,30 · **Takt:** 4/4
- **Töne (rel):** [-12] · **Intervalle:** –
- **Rhythmus:** eigene Dauern: 15360 · **Gesamtzyklus:** 1 Ereignisse / 15360 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H091, EM-H092, EM-H093, EM-H094, EM-H095, EM-H096 · **Ungeeignete:** –; nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** N – nachgewiesenes Verfahren (Pedal (Hauptbericht)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B002 – Dominantpedal
- **Charakter:** Erwartung · **Säule:** A · **Typ:** EIG · **Rollen:** LB
- **XYZ-Anker:** beliebig / 0,45 / 0,40 · **Gültigkeit:** X 0,00–1,00 · Y 0,25–0,65 · Z 0,20–0,60 · **Takt:** 4/4
- **Töne (rel):** [-17] · **Intervalle:** –
- **Rhythmus:** eigene Dauern: 15360 · **Gesamtzyklus:** 1 Ereignisse / 15360 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **Ungeeignete:** EM-H071, EM-H076, EM-H103 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** I – begründete Interpretation (Orgelpunkt auf 5); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B003 – Quint-Drone
- **Charakter:** archaisch, leer · **Säule:** AB · **Typ:** EIG · **Rollen:** LB
- **XYZ-Anker:** 0,20 / 0,30 / 0,10 · **Gültigkeit:** X 0,00–0,40 · Y 0,10–0,50 · Z 0,00–0,30 · **Takt:** 4/4
- **Töne (rel):** [-24, -17] · **Intervalle:** +7
- **Rhythmus:** eigene Dauern: 15360 · **Gesamtzyklus:** 2 Ereignisse / 30720 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H091, EM-H092, EM-H093, EM-H094, EM-H095, EM-H096 · **Ungeeignete:** EM-H071, EM-H076, EM-H103 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** N – nachgewiesenes Verfahren (Drone (GINC: B♭-Drone, Wilcox)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B004 – ♭2-Pedal
- **Charakter:** drohende Nähe · **Säule:** B · **Typ:** DIS · **Rollen:** LB
- **XYZ-Anker:** 0,10 / 0,35 / 0,45 · **Gültigkeit:** X 0,00–0,30 · Y 0,15–0,55 · Z 0,25–0,65 · **Takt:** 4/4
- **Töne (rel):** [-11] · **Intervalle:** –
- **Rhythmus:** eigene Dauern: 15360 · **Gesamtzyklus:** 1 Ereignisse / 15360 Ticks
- **Harmonische Voraussetzung:** keine (Reibung beabsichtigt, Funktion U)
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H068, EM-H069, EM-H072 · **Ungeeignete:** –; nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** E – eigenständige Gestaltung (dissonanzautorisierter Pedalton); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B005 – Tritonus-Pedal
- **Charakter:** Unheil · **Säule:** B · **Typ:** DIS · **Rollen:** LB
- **XYZ-Anker:** 0,15 / 0,35 / 0,50 · **Gültigkeit:** X 0,00–0,35 · Y 0,15–0,55 · Z 0,30–0,70 · **Takt:** 4/4
- **Töne (rel):** [-18] · **Intervalle:** –
- **Rhythmus:** eigene Dauern: 15360 · **Gesamtzyklus:** 1 Ereignisse / 15360 Ticks
- **Harmonische Voraussetzung:** keine (Reibung beabsichtigt, Funktion U)
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H069, EM-H071, EM-H072 · **Ungeeignete:** –; nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** E – eigenständige Gestaltung (Tritonus (Suoni per Dino)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B006 – Herzschlag Einzelton
- **Charakter:** latent lebendig · **Säule:** B · **Typ:** EIG · **Rollen:** KB
- **XYZ-Anker:** beliebig / 0,35 / 0,30 · **Gültigkeit:** X 0,00–1,00 · Y 0,15–0,55 · Z 0,10–0,50 · **Takt:** 4/4
- **Töne (rel):** [-12, -12] · **Intervalle:** +0
- **Rhythmus:** EM-R001 (Periode 3840 Ticks, 2 Einsätze) · **Gesamtzyklus:** 2 Ereignisse / 3840 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H068, EM-H069, EM-H070 · **Ungeeignete:** –; nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** N – nachgewiesenes Verfahren (Herzschlag (cuebycue)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B007 – Herzschlag Grundton–Quinte tief
- **Charakter:** schwerer Puls · **Säule:** B · **Typ:** EIG · **Rollen:** KB
- **XYZ-Anker:** beliebig / 0,50 / 0,30 · **Gültigkeit:** X 0,00–1,00 · Y 0,30–0,70 · Z 0,10–0,50 · **Takt:** 4/4
- **Töne (rel):** [-12, -19] · **Intervalle:** -7
- **Rhythmus:** EM-R001 (Periode 3840 Ticks, 2 Einsätze) · **Gesamtzyklus:** 2 Ereignisse / 3840 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H068, EM-H070, EM-H073 · **Ungeeignete:** EM-H021, EM-H026, EM-H069, EM-H071, EM-H072 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** E – eigenständige Gestaltung (Herzschlag); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B008 – Pulsierender Einzeltonbass (Achtel)
- **Charakter:** mechanische Bedrohung · **Säule:** B · **Typ:** EIG · **Rollen:** KB
- **XYZ-Anker:** beliebig / 0,45 / 0,40 · **Gültigkeit:** X 0,00–1,00 · Y 0,25–0,65 · Z 0,20–0,60 · **Takt:** 4/4
- **Töne (rel):** [-12] · **Intervalle:** –
- **Rhythmus:** EM-R004 (Periode 3840 Ticks, 8 Einsätze) · **Gesamtzyklus:** 8 Ereignisse / 3840 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H068, EM-H069, EM-H070 · **Ungeeignete:** –; nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** N – nachgewiesenes Verfahren (pulsierender Bass (Filmtracks: The Thing)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B009 – Pulsierender Einzelton mit Akzent 3+3+2
- **Charakter:** drängender Puls · **Säule:** B · **Typ:** EIG · **Rollen:** KB
- **XYZ-Anker:** beliebig / 0,55 / 0,45 · **Gültigkeit:** X 0,00–1,00 · Y 0,35–0,75 · Z 0,25–0,65 · **Takt:** 4/4
- **Töne (rel):** [-12] · **Intervalle:** –
- **Rhythmus:** EM-R005 (Periode 3840 Ticks, 8 Einsätze) · **Gesamtzyklus:** 8 Ereignisse / 3840 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H068, EM-H069, EM-H070 · **Ungeeignete:** –; nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** E – eigenständige Gestaltung (Akzentgruppen); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B010 – Fünftonfigur modal
- **Charakter:** obsessiv kreisend · **Säule:** B · **Typ:** EIG · **Rollen:** KB
- **XYZ-Anker:** 0,35 / 0,50 / 0,55 · **Gültigkeit:** X 0,15–0,55 · Y 0,30–0,70 · Z 0,35–0,75 · **Takt:** 4/4
- **Töne (rel):** [-12, -9, -7, -9, -14] · **Intervalle:** +3, +2, -2, -5
- **Rhythmus:** EM-R007 (Periode 1200 Ticks, 4 Einsätze) · **Gesamtzyklus:** 20 Ereignisse / 96000 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H068, EM-H070, EM-H073 · **Ungeeignete:** EM-H011, EM-H016, EM-H017, EM-H018, EM-H019 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** N – nachgewiesenes Verfahren (5-Ton-Bassfigur (cuebycue: Cat o' Nine Tails)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B011 – Fünftonfigur dissonanzautorisiert
- **Charakter:** verbissen · **Säule:** B · **Typ:** DIS · **Rollen:** KB
- **XYZ-Anker:** 0,15 / 0,50 / 0,65 · **Gültigkeit:** X 0,00–0,35 · Y 0,30–0,70 · Z 0,45–0,85 · **Takt:** 4/4
- **Töne (rel):** [-12, -11, -12, -6, -7] · **Intervalle:** +1, -1, +6, -1
- **Rhythmus:** EM-R007 (Periode 1200 Ticks, 4 Einsätze) · **Gesamtzyklus:** 20 Ereignisse / 96000 Ticks
- **Harmonische Voraussetzung:** keine (Reibung beabsichtigt, Funktion U)
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H073, EM-H074, EM-H078 · **Ungeeignete:** –; nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** E – eigenständige Gestaltung (chromatische Figur); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B012 – Sechstonfigur Bogen
- **Charakter:** federnd, geschlossen · **Säule:** B · **Typ:** EIG · **Rollen:** KB
- **XYZ-Anker:** 0,40 / 0,55 / 0,50 · **Gültigkeit:** X 0,20–0,60 · Y 0,35–0,75 · Z 0,30–0,70 · **Takt:** 4/4
- **Töne (rel):** [-12, -5, -2, +0, -2, -5] · **Intervalle:** +7, +3, +2, -2, -3
- **Rhythmus:** EM-R021 (Periode 3840 Ticks, 5 Einsätze) · **Gesamtzyklus:** 30 Ereignisse / 23040 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H068, EM-H069, EM-H070 · **Ungeeignete:** EM-H011, EM-H016, EM-H017, EM-H018, EM-H019 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** N – nachgewiesenes Verfahren (6-Ton-Basspattern (cuebycue)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B013 – Achttonfigur mit Wendung
- **Charakter:** rastlos · **Säule:** B · **Typ:** EIG · **Rollen:** KB
- **XYZ-Anker:** 0,35 / 0,55 / 0,55 · **Gültigkeit:** X 0,15–0,55 · Y 0,35–0,75 · Z 0,35–0,75 · **Takt:** 4/4
- **Töne (rel):** [-12, -12, -14, -12, -9, -7, -9, -14] · **Intervalle:** +0, -2, +2, +3, +2, -2, -5
- **Rhythmus:** EM-R004 (Periode 3840 Ticks, 8 Einsätze) · **Gesamtzyklus:** 8 Ereignisse / 3840 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H068, EM-H070, EM-H073 · **Ungeeignete:** EM-H011, EM-H016, EM-H017, EM-H018, EM-H019 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** N – nachgewiesenes Verfahren (8-Ton-Basspattern (cuebycue)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B014 – Zwölftonfigur synkopisch
- **Charakter:** obsessive Spannung · **Säule:** B · **Typ:** EIG · **Rollen:** KB
- **XYZ-Anker:** 0,30 / 0,60 / 0,65 · **Gültigkeit:** X 0,10–0,50 · Y 0,40–0,80 · Z 0,45–0,85 · **Takt:** 4/4
- **Töne (rel):** [-12, -9, -7, -6, -7, -9, -12, -14, -12, -9, -2, -5] · **Intervalle:** +3, +2, +1, -1, -2, -3, -2, +2, +3, +7, -3
- **Rhythmus:** EM-R023 (Periode 7680 Ticks, 12 Einsätze) · **Gesamtzyklus:** 12 Ereignisse / 7680 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H073, EM-H074, EM-H078 · **Ungeeignete:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** N – nachgewiesenes Verfahren (12-Ton-Bassrhythmus (cuebycue)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B015 – Stufenweise fallend dorisch
- **Charakter:** gefasste Wehmut · **Säule:** A · **Typ:** EIG · **Rollen:** LB
- **XYZ-Anker:** 0,50 / 0,35 / 0,20 · **Gültigkeit:** X 0,30–0,70 · Y 0,15–0,55 · Z 0,00–0,40 · **Takt:** 4/4
- **Töne (rel):** [-12, -14, -15, -17] · **Intervalle:** -2, -1, -2
- **Rhythmus:** eigene Dauern: 3840 · **Gesamtzyklus:** 4 Ereignisse / 15360 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H007, EM-H008, EM-H013, EM-H022, EM-H023, EM-H024 · **Ungeeignete:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** I – begründete Interpretation (stufenweiser Bass); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B016 – Lamento diatonisch
- **Charakter:** Klage · **Säule:** A · **Typ:** EIG · **Rollen:** LB
- **XYZ-Anker:** 0,30 / 0,40 / 0,30 · **Gültigkeit:** X 0,10–0,50 · Y 0,20–0,60 · Z 0,10–0,50 · **Takt:** 4/4
- **Töne (rel):** [-12, -14, -16, -17] · **Intervalle:** -2, -2, -1
- **Rhythmus:** eigene Dauern: 3840 · **Gesamtzyklus:** 4 Ereignisse / 15360 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **Ungeeignete:** EM-H007, EM-H008, EM-H011, EM-H013, EM-H016 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** E – eigenständige Gestaltung (Lamentobass); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B017 – Lamento chromatisch
- **Charakter:** Schmerz · **Säule:** A · **Typ:** EIG · **Rollen:** LB
- **XYZ-Anker:** 0,25 / 0,45 / 0,45 · **Gültigkeit:** X 0,05–0,45 · Y 0,25–0,65 · Z 0,25–0,65 · **Takt:** 4/4
- **Töne (rel):** [-12, -14, -15, -16, -17] · **Intervalle:** -2, -1, -1, -1
- **Rhythmus:** eigene Dauern: 3840 · **Gesamtzyklus:** 5 Ereignisse / 19200 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H022, EM-H023, EM-H024, EM-H030, EM-H046, EM-H047 · **Ungeeignete:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** E – eigenständige Gestaltung (chromatischer Bass); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B018 – Plagalbass i–iv–i
- **Charakter:** dunkle Ruhe · **Säule:** A · **Typ:** AKK · **Rollen:** LB
- **XYZ-Anker:** 0,35 / 0,25 / 0,10 · **Gültigkeit:** X 0,15–0,55 · Y 0,05–0,45 · Z 0,00–0,30 · **Takt:** 4/4
- **Töne (rel):** [-12, -7, -12] · **Intervalle:** +5, -5
- **Rhythmus:** eigene Dauern: 7680, 7680, 7680 · **Gesamtzyklus:** 3 Ereignisse / 23040 Ticks
- **Harmonische Voraussetzung:** Harmoniefolge mit passender Bassstufe
- **Geeignete Kombinationen:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **Ungeeignete:** EM-H021, EM-H026, EM-H069, EM-H071, EM-H072 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** I – begründete Interpretation (plagal); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B019 – Terzkettenbass Dur 1–6–4–1
- **Charakter:** zärtlich · **Säule:** A · **Typ:** AKK · **Rollen:** LB
- **XYZ-Anker:** 0,75 / 0,30 / 0,15 · **Gültigkeit:** X 0,55–0,95 · Y 0,10–0,50 · Z 0,00–0,35 · **Takt:** 4/4
- **Töne (rel):** [-12, -15, -19, -12] · **Intervalle:** -3, -4, +7
- **Rhythmus:** eigene Dauern: 7680 · **Gesamtzyklus:** 4 Ereignisse / 30720 Ticks
- **Harmonische Voraussetzung:** Harmoniefolge mit passender Bassstufe
- **Geeignete Kombinationen:** EM-H007, EM-H008, EM-H013, EM-H016, EM-H017, EM-H018 · **Ungeeignete:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** N – nachgewiesenes Verfahren (Plagal-Terzkette (filmmusicnotes)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B020 – Gefüllte Terzkette (stufenweise)
- **Charakter:** gesanglicher Bass · **Säule:** A · **Typ:** AKK · **Rollen:** LB
- **XYZ-Anker:** 0,75 / 0,35 / 0,20 · **Gültigkeit:** X 0,55–0,95 · Y 0,15–0,55 · Z 0,00–0,40 · **Takt:** 4/4
- **Töne (rel):** [-12, -13, -15, -17, -19, -20, -22, -12] · **Intervalle:** -1, -2, -2, -2, -1, -2, +10
- **Rhythmus:** eigene Dauern: 3840 · **Gesamtzyklus:** 8 Ereignisse / 30720 Ticks
- **Harmonische Voraussetzung:** Harmoniefolge mit passender Bassstufe
- **Geeignete Kombinationen:** EM-H016, EM-H017, EM-H018, EM-H019, EM-H020, EM-H022 · **Ungeeignete:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** N – nachgewiesenes Verfahren (stufenweise gefüllte Terzkette); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B021 – Umkehrungsbass 1–3–4–5
- **Charakter:** aufsteigend tröstend · **Säule:** A · **Typ:** AKK · **Rollen:** LB
- **XYZ-Anker:** 0,70 / 0,40 / 0,20 · **Gültigkeit:** X 0,50–0,90 · Y 0,20–0,60 · Z 0,00–0,40 · **Takt:** 4/4
- **Töne (rel):** [-12, -8, -7, -5] · **Intervalle:** +4, +1, +2
- **Rhythmus:** eigene Dauern: 3840 · **Gesamtzyklus:** 4 Ereignisse / 15360 Ticks
- **Harmonische Voraussetzung:** Harmoniefolge mit passender Bassstufe
- **Geeignete Kombinationen:** EM-H016, EM-H017, EM-H018, EM-H019, EM-H020, EM-H022 · **Ungeeignete:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** E – eigenständige Gestaltung (Bassführung über Umkehrungen); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B022 – Späte Grundtonsetzung
- **Charakter:** Erlösung am Ende · **Säule:** A · **Typ:** EIG · **Rollen:** LB
- **XYZ-Anker:** beliebig / 0,30 / 0,20 · **Gültigkeit:** X 0,00–1,00 · Y 0,10–0,50 · Z 0,00–0,40 · **Takt:** 4/4
- **Töne (rel):** [-12] · **Intervalle:** –
- **Rhythmus:** eigene Dauern: Pause 11520, 3840 · **Gesamtzyklus:** 2 Ereignisse / 15360 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **Ungeeignete:** –; nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme, späte Setzung
- **Evidenz:** N – nachgewiesenes Verfahren (später Grundton (Wilcox: Viertes Konzert)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B023 – Bewusster Bassverzicht
- **Charakter:** schwebend, körperlos · **Säule:** AB · **Typ:** EIG · **Rollen:** LB KB
- **XYZ-Anker:** beliebig / 0,15 / 0,20 · **Gültigkeit:** X 0,00–1,00 · Y 0,00–0,35 · Z 0,00–0,40 · **Takt:** 4/4
- **Töne (rel):** – (Bassverzicht) · **Intervalle:** –
- **Rhythmus:** – · **Gesamtzyklus:** 0 Ereignisse / 0 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H091, EM-H092, EM-H093, EM-H094, EM-H095, EM-H096 · **Ungeeignete:** –; nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** I – begründete Interpretation (Bassverzicht (Giallo-Texturen, cuebycue)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B024 – Gleicher Bass unter wechselnder Harmonik (neu angeschlagen je Halbtakt)
- **Charakter:** Halt im Wandel · **Säule:** A · **Typ:** EIG · **Rollen:** LB
- **XYZ-Anker:** beliebig / 0,30 / 0,20 · **Gültigkeit:** X 0,00–1,00 · Y 0,10–0,50 · Z 0,00–0,40 · **Takt:** 4/4
- **Töne (rel):** [-12] · **Intervalle:** –
- **Rhythmus:** eigene Dauern: 1920 · **Gesamtzyklus:** 1 Ereignisse / 1920 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **Ungeeignete:** –; nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** I – begründete Interpretation (konstanter Bass unter wechselnder Oberharmonik); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B025 – Bewegter Bass unter konstanten Oberstimmen
- **Charakter:** Boden verschiebt sich · **Säule:** A · **Typ:** DIS · **Rollen:** LB
- **XYZ-Anker:** 0,50 / 0,40 / 0,30 · **Gültigkeit:** X 0,30–0,70 · Y 0,20–0,60 · Z 0,10–0,50 · **Takt:** 4/4
- **Töne (rel):** [-12, -16, -19, -17] · **Intervalle:** -4, -3, +2
- **Rhythmus:** eigene Dauern: 7680 · **Gesamtzyklus:** 4 Ereignisse / 30720 Ticks
- **Harmonische Voraussetzung:** keine (Reibung beabsichtigt, Funktion U)
- **Geeignete Kombinationen:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **Ungeeignete:** –; nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** I – begründete Interpretation (bewegter Bass unter konstanten Klangfeldern); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B026 – Chromatisch steigend
- **Charakter:** wachsende Gefahr · **Säule:** B · **Typ:** DIS · **Rollen:** LB KB
- **XYZ-Anker:** 0,20 / 0,50 / 0,60 · **Gültigkeit:** X 0,00–0,40 · Y 0,30–0,70 · Z 0,40–0,80 · **Takt:** 4/4
- **Töne (rel):** [-12, -11, -10, -9] · **Intervalle:** +1, +1, +1
- **Rhythmus:** eigene Dauern: 3840 · **Gesamtzyklus:** 4 Ereignisse / 15360 Ticks
- **Harmonische Voraussetzung:** keine (Reibung beabsichtigt, Funktion U)
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H073, EM-H074, EM-H078 · **Ungeeignete:** –; nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** E – eigenständige Gestaltung (chromatische Bassbewegung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B027 – Chromatisches Wechselpendel
- **Charakter:** Zittern im Grund · **Säule:** B · **Typ:** DIS · **Rollen:** KB
- **XYZ-Anker:** 0,20 / 0,35 / 0,55 · **Gültigkeit:** X 0,00–0,40 · Y 0,15–0,55 · Z 0,35–0,75 · **Takt:** 4/4
- **Töne (rel):** [-12, -11, -12, -13] · **Intervalle:** +1, -1, -1
- **Rhythmus:** EM-R044 (Periode 3840 Ticks, 3 Einsätze) · **Gesamtzyklus:** 12 Ereignisse / 15360 Ticks
- **Harmonische Voraussetzung:** keine (Reibung beabsichtigt, Funktion U)
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H073, EM-H074, EM-H078 · **Ungeeignete:** –; nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** E – eigenständige Gestaltung (chromatische Bassbewegung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B028 – Quintfallbass dorisch
- **Charakter:** erhaben fortschreitend · **Säule:** A · **Typ:** AKK · **Rollen:** LB
- **XYZ-Anker:** 0,55 / 0,75 / 0,20 · **Gültigkeit:** X 0,35–0,75 · Y 0,55–0,95 · Z 0,00–0,40 · **Takt:** 4/4
- **Töne (rel):** [-12, -7, -14, -9] · **Intervalle:** +5, -7, +5
- **Rhythmus:** eigene Dauern: 7680 · **Gesamtzyklus:** 4 Ereignisse / 30720 Ticks
- **Harmonische Voraussetzung:** Harmoniefolge mit passender Bassstufe
- **Geeignete Kombinationen:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **Ungeeignete:** EM-H011, EM-H016, EM-H017, EM-H018, EM-H019 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** I – begründete Interpretation (dorischer Quintfall); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B029 – Oktavpuls
- **Charakter:** elastische Kraft · **Säule:** B · **Typ:** EIG · **Rollen:** KB
- **XYZ-Anker:** beliebig / 0,65 / 0,45 · **Gültigkeit:** X 0,00–1,00 · Y 0,45–0,85 · Z 0,25–0,65 · **Takt:** 4/4
- **Töne (rel):** [-24, -12] · **Intervalle:** +12
- **Rhythmus:** EM-R004 (Periode 3840 Ticks, 8 Einsätze) · **Gesamtzyklus:** 8 Ereignisse / 3840 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H068, EM-H069, EM-H070 · **Ungeeignete:** –; nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** E – eigenständige Gestaltung (Oktavierung als Gewicht); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B030 – Gewichtsschicht Fünf-Ereignis-Figur
- **Charakter:** Kraft ohne Hektik · **Säule:** B · **Typ:** EIG · **Rollen:** KB
- **XYZ-Anker:** 0,35 / 0,80 / 0,35 · **Gültigkeit:** X 0,15–0,55 · Y 0,60–1,00 · Z 0,15–0,55 · **Takt:** 4/4
- **Töne (rel):** [-12, -17, -14, -12, -9] · **Intervalle:** -5, +3, +2, +3
- **Rhythmus:** EM-R014 (Periode 3840 Ticks, 5 Einsätze) · **Gesamtzyklus:** 5 Ereignisse / 3840 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H068, EM-H069, EM-H070 · **Ungeeignete:** EM-H011, EM-H016, EM-H017, EM-H018, EM-H019 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** I – begründete Interpretation (tiefe Gewichtsschicht (Untouchables-Prinzip, eigene Tonfolge)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B031 – Gewichtsschicht oktavgedoppelt
- **Charakter:** massiv, beherrscht · **Säule:** B · **Typ:** EIG · **Rollen:** KB
- **XYZ-Anker:** 0,30 / 0,90 / 0,35 · **Gültigkeit:** X 0,10–0,50 · Y 0,70–1,00 · Z 0,15–0,55 · **Takt:** 4/4
- **Töne (rel):** [-24, -29, -26, -24, -21] · **Intervalle:** -5, +3, +2, +3
- **Rhythmus:** EM-R014 (Periode 3840 Ticks, 5 Einsätze) · **Gesamtzyklus:** 5 Ereignisse / 3840 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H068, EM-H069, EM-H070 · **Ungeeignete:** EM-H011, EM-H016, EM-H017, EM-H018, EM-H019 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** I – begründete Interpretation (Dopplung als Y-Funktion); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B032 – Synkopierter Groove-Bass
- **Charakter:** rhythmische Spannung (Giallo-inspiriert) · **Säule:** B · **Typ:** EIG · **Rollen:** KB
- **XYZ-Anker:** 0,40 / 0,60 / 0,55 · **Gültigkeit:** X 0,20–0,60 · Y 0,40–0,80 · Z 0,35–0,75 · **Takt:** 4/4
- **Töne (rel):** [-12, -12, -5, -2, +0, -2] · **Intervalle:** +0, +7, +3, +2, -2
- **Rhythmus:** EM-R021 (Periode 3840 Ticks, 5 Einsätze) · **Gesamtzyklus:** 30 Ereignisse / 23040 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H068, EM-H069, EM-H070 · **Ungeeignete:** EM-H011, EM-H016, EM-H017, EM-H018, EM-H019 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** N – nachgewiesenes Verfahren (Groove-Bass (Corbella: jazz-rockige Dynamik)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B033 – Ostinato aus zwei Kleinterzpaaren im Tritonusabstand (oktatonisch)
- **Charakter:** verkettet, unruhig · **Säule:** B · **Typ:** EIG · **Rollen:** KB AR
- **XYZ-Anker:** 0,30 / 0,45 / 0,60 · **Gültigkeit:** X 0,10–0,50 · Y 0,25–0,65 · Z 0,40–0,80 · **Takt:** 4/4
- **Töne (rel):** [-12, -9, -6, -3] · **Intervalle:** +3, +3, +3
- **Rhythmus:** EM-R027 (Periode 5280 Ticks, 9 Einsätze) · **Gesamtzyklus:** 36 Ereignisse / 42240 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H069, EM-H072, EM-H073 · **Ungeeignete:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** N – nachgewiesenes Verfahren (zwei Paare kleiner Terzen (Wilcox: Drittes Konzert)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B034 – Tragischer Abstieg in Halben über die Oktave
- **Charakter:** unaufhaltsamer Fall · **Säule:** A · **Typ:** EIG · **Rollen:** LB
- **XYZ-Anker:** 0,30 / 0,70 / 0,30 · **Gültigkeit:** X 0,10–0,50 · Y 0,50–0,90 · Z 0,10–0,50 · **Takt:** 4/4
- **Töne (rel):** [-12, -14, -16, -17, -19, -21, -22, -24] · **Intervalle:** -2, -2, -1, -2, -2, -1, -2
- **Rhythmus:** eigene Dauern: 1920 · **Gesamtzyklus:** 8 Ereignisse / 15360 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **Ungeeignete:** EM-H007, EM-H008, EM-H011, EM-H013, EM-H016 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** E – eigenständige Gestaltung (stufenweiser Bass); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B035 – Drone mit langsamer Nachbarnote
- **Charakter:** kaum merkliche Verschiebung · **Säule:** AB · **Typ:** DIS · **Rollen:** LB
- **XYZ-Anker:** 0,25 / 0,25 / 0,30 · **Gültigkeit:** X 0,05–0,45 · Y 0,05–0,45 · Z 0,10–0,50 · **Takt:** 4/4
- **Töne (rel):** [-12, -11, -12] · **Intervalle:** +1, -1
- **Rhythmus:** eigene Dauern: 15360, 3840, 11520 · **Gesamtzyklus:** 3 Ereignisse / 30720 Ticks
- **Harmonische Voraussetzung:** keine (Reibung beabsichtigt, Funktion U)
- **Geeignete Kombinationen:** EM-H102, EM-H104, EM-H105 · **Ungeeignete:** –; nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** E – eigenständige Gestaltung (Drone + Halbton); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B036 – Tremolo-Bass (Sechzehntel)
- **Charakter:** Erregung · **Säule:** B · **Typ:** EIG · **Rollen:** KB
- **XYZ-Anker:** beliebig / 0,55 / 0,75 · **Gültigkeit:** X 0,00–1,00 · Y 0,35–0,75 · Z 0,55–0,95 · **Takt:** 4/4
- **Töne (rel):** [-12] · **Intervalle:** –
- **Rhythmus:** EM-R040 (Periode 3840 Ticks, 16 Einsätze) · **Gesamtzyklus:** 16 Ereignisse / 3840 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H068, EM-H069, EM-H070 · **Ungeeignete:** –; nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** E – eigenständige Gestaltung (mechanische Unruhe); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B037 – Wechselton-Herzschlag (Halbton)
- **Charakter:** kranker Puls · **Säule:** B · **Typ:** DIS · **Rollen:** KB
- **XYZ-Anker:** 0,15 / 0,40 / 0,55 · **Gültigkeit:** X 0,00–0,35 · Y 0,20–0,60 · Z 0,35–0,75 · **Takt:** 4/4
- **Töne (rel):** [-12, -13] · **Intervalle:** -1
- **Rhythmus:** EM-R001 (Periode 3840 Ticks, 2 Einsätze) · **Gesamtzyklus:** 2 Ereignisse / 3840 Ticks
- **Harmonische Voraussetzung:** keine (Reibung beabsichtigt, Funktion U)
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H073, EM-H074, EM-H075 · **Ungeeignete:** –; nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** E – eigenständige Gestaltung (Herzschlag + Halbtonreibung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B038 – Quart-Quint-Pendel in Halben
- **Charakter:** archaisch, ruhig · **Säule:** AB · **Typ:** EIG · **Rollen:** LB
- **XYZ-Anker:** beliebig / 0,40 / 0,20 · **Gültigkeit:** X 0,00–1,00 · Y 0,20–0,60 · Z 0,00–0,40 · **Takt:** 4/4
- **Töne (rel):** [-12, -17] · **Intervalle:** -5
- **Rhythmus:** eigene Dauern: 1920 · **Gesamtzyklus:** 2 Ereignisse / 3840 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H091, EM-H092, EM-H093, EM-H094, EM-H095, EM-H096 · **Ungeeignete:** EM-H071, EM-H076, EM-H103 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** E – eigenständige Gestaltung (Pendel); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B039 – Pedalrepetition Viertel mit Pausen
- **Charakter:** geduldig lauernd · **Säule:** B · **Typ:** EIG · **Rollen:** KB
- **XYZ-Anker:** beliebig / 0,35 / 0,30 · **Gültigkeit:** X 0,00–1,00 · Y 0,15–0,55 · Z 0,10–0,50 · **Takt:** 4/4
- **Töne (rel):** [-12] · **Intervalle:** –
- **Rhythmus:** EM-R044 (Periode 3840 Ticks, 3 Einsätze) · **Gesamtzyklus:** 3 Ereignisse / 3840 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H068, EM-H069, EM-H070 · **Ungeeignete:** –; nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** E – eigenständige Gestaltung (Puls mit Leerraum); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B040 – Tritonussprung-Figur
- **Charakter:** zerrissen · **Säule:** B · **Typ:** DIS · **Rollen:** KB
- **XYZ-Anker:** 0,15 / 0,55 / 0,65 · **Gültigkeit:** X 0,00–0,35 · Y 0,35–0,75 · Z 0,45–0,85 · **Takt:** 4/4
- **Töne (rel):** [-12, -6, -12, -18] · **Intervalle:** +6, -6, -6
- **Rhythmus:** EM-R028 (Periode 960 Ticks, 3 Einsätze) · **Gesamtzyklus:** 12 Ereignisse / 3840 Ticks
- **Harmonische Voraussetzung:** keine (Reibung beabsichtigt, Funktion U)
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H069, EM-H071, EM-H072 · **Ungeeignete:** –; nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** N – nachgewiesenes Verfahren (Tritonus (Suoni per Dino)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B041 – Ganztonabstieg
- **Charakter:** Schwerelosigkeit nach unten · **Säule:** B · **Typ:** DIS · **Rollen:** LB
- **XYZ-Anker:** 0,55 / 0,30 / 0,45 · **Gültigkeit:** X 0,35–0,75 · Y 0,10–0,50 · Z 0,25–0,65 · **Takt:** 4/4
- **Töne (rel):** [-12, -14, -16, -18] · **Intervalle:** -2, -2, -2
- **Rhythmus:** eigene Dauern: 3840 · **Gesamtzyklus:** 4 Ereignisse / 15360 Ticks
- **Harmonische Voraussetzung:** keine (Reibung beabsichtigt, Funktion U)
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H071, EM-H073, EM-H074 · **Ungeeignete:** –; nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** E – eigenständige Gestaltung (symmetrischer Bass); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B042 – Terzpendel i–♭VI
- **Charakter:** Schicksalspendel · **Säule:** A · **Typ:** AKK · **Rollen:** LB
- **XYZ-Anker:** 0,30 / 0,60 / 0,20 · **Gültigkeit:** X 0,10–0,50 · Y 0,40–0,80 · Z 0,00–0,40 · **Takt:** 4/4
- **Töne (rel):** [-12, -16] · **Intervalle:** -4
- **Rhythmus:** eigene Dauern: 7680 · **Gesamtzyklus:** 2 Ereignisse / 15360 Ticks
- **Harmonische Voraussetzung:** Harmoniefolge mit passender Bassstufe
- **Geeignete Kombinationen:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **Ungeeignete:** EM-H007, EM-H008, EM-H013, EM-H016, EM-H017 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** I – begründete Interpretation (Terzpendel); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B043 – Halbschlussbass 4–5
- **Charakter:** offen endend · **Säule:** A · **Typ:** AKK · **Rollen:** LB
- **XYZ-Anker:** 0,40 / 0,40 / 0,35 · **Gültigkeit:** X 0,20–0,60 · Y 0,20–0,60 · Z 0,15–0,55 · **Takt:** 4/4
- **Töne (rel):** [-19, -17] · **Intervalle:** +2
- **Rhythmus:** eigene Dauern: 7680 · **Gesamtzyklus:** 2 Ereignisse / 15360 Ticks
- **Harmonische Voraussetzung:** Harmoniefolge mit passender Bassstufe
- **Geeignete Kombinationen:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **Ungeeignete:** EM-H021, EM-H026, EM-H069, EM-H071, EM-H072 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** N – nachgewiesenes Verfahren (Halbschluss); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B044 – Phrygischer Fall ♭2–1
- **Charakter:** Absinken in die Gefahr · **Säule:** B · **Typ:** AKK · **Rollen:** LB
- **XYZ-Anker:** 0,15 / 0,45 / 0,40 · **Gültigkeit:** X 0,00–0,35 · Y 0,25–0,65 · Z 0,20–0,60 · **Takt:** 4/4
- **Töne (rel):** [-11, -12] · **Intervalle:** -1
- **Rhythmus:** eigene Dauern: 7680 · **Gesamtzyklus:** 2 Ereignisse / 15360 Ticks
- **Harmonische Voraussetzung:** Harmoniefolge mit passender Bassstufe
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H068, EM-H069, EM-H072 · **Ungeeignete:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** E – eigenständige Gestaltung (phrygische Kadenz); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B045 – Zellgebundene Bassfigur (Modul 4 Schläge)
- **Charakter:** kohärent, stoisch · **Säule:** B · **Typ:** EIG · **Rollen:** KB
- **XYZ-Anker:** 0,35 / 0,40 / 0,40 · **Gültigkeit:** X 0,15–0,55 · Y 0,20–0,60 · Z 0,20–0,60 · **Takt:** 4/4
- **Töne (rel):** [-12, -9, -7] · **Intervalle:** +3, +2
- **Rhythmus:** EM-R044 (Periode 3840 Ticks, 3 Einsätze) · **Gesamtzyklus:** 3 Ereignisse / 3840 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H068, EM-H070, EM-H073 · **Ungeeignete:** EM-H016, EM-H017, EM-H018, EM-H019, EM-H020 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** N – nachgewiesenes Verfahren (Zellbindung (Corbella: ineinanderpassende Module)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B046 – Ametrischer Einzeltonbass
- **Charakter:** Ereignis aus der Tiefe · **Säule:** B · **Typ:** EIG · **Rollen:** KB
- **XYZ-Anker:** 0,20 / 0,30 / 0,55 · **Gültigkeit:** X 0,00–0,40 · Y 0,10–0,50 · Z 0,35–0,75 · **Takt:** 4/4
- **Töne (rel):** [-12, -18, -12] · **Intervalle:** -6, +6
- **Rhythmus:** EM-R041 (Periode 7680 Ticks, 5 Einsätze) · **Gesamtzyklus:** 15 Ereignisse / 23040 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H069, EM-H071, EM-H072 · **Ungeeignete:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** N – nachgewiesenes Verfahren (ametrisch (Morricone zu Bird)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B047 – Antwortbass (zwei Schläge nach dem Ruf)
- **Charakter:** Gespräch mit der Tiefe · **Säule:** AB · **Typ:** EIG · **Rollen:** KB
- **XYZ-Anker:** beliebig / 0,30 / 0,40 · **Gültigkeit:** X 0,00–1,00 · Y 0,10–0,50 · Z 0,20–0,60 · **Takt:** 4/4
- **Töne (rel):** [-12, -14] · **Intervalle:** -2
- **Rhythmus:** eigene Dauern: Pause 1920, 480, Pause 1440, 480 · **Gesamtzyklus:** 4 Ereignisse / 4320 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H091, EM-H094, EM-H096, EM-H099, EM-H101, EM-H102 · **Ungeeignete:** EM-H011, EM-H016, EM-H017, EM-H018, EM-H019 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** N – nachgewiesenes Verfahren (Gesprächslogik (Wilcox: GINC)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B048 – Wiegenbass 12/8
- **Charakter:** schaukelnd, warm · **Säule:** A · **Typ:** AKK · **Rollen:** KB
- **XYZ-Anker:** 0,60 / 0,30 / 0,20 · **Gültigkeit:** X 0,40–0,80 · Y 0,10–0,50 · Z 0,00–0,40 · **Takt:** 4/4
- **Töne (rel):** [-12, -5, +0, -5] · **Intervalle:** +7, +5, -5
- **Rhythmus:** EM-R010 (Periode 5760 Ticks, 8 Einsätze) · **Gesamtzyklus:** 8 Ereignisse / 5760 Ticks
- **Harmonische Voraussetzung:** Harmoniefolge mit passender Bassstufe
- **Geeignete Kombinationen:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **Ungeeignete:** EM-H071, EM-H076, EM-H103 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** I – begründete Interpretation (ternäre Bewegung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B049 – Unisono-Stoß tief
- **Charakter:** Schlag ins Mark · **Säule:** B · **Typ:** EIG · **Rollen:** KB
- **XYZ-Anker:** beliebig / 0,85 / 0,45 · **Gültigkeit:** X 0,00–1,00 · Y 0,65–1,00 · Z 0,25–0,65 · **Takt:** 4/4
- **Töne (rel):** [-24] · **Intervalle:** –
- **Rhythmus:** EM-R053 (Periode 3840 Ticks, 3 Einsätze) · **Gesamtzyklus:** 3 Ereignisse / 3840 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H068, EM-H069, EM-H070 · **Ungeeignete:** –; nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** I – begründete Interpretation (Marcato-Block (NPR)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B050 – Sext-Terz-Kette abwärts
- **Charakter:** Erinnerung sinkt · **Säule:** A · **Typ:** AKK · **Rollen:** LB
- **XYZ-Anker:** 0,60 / 0,35 / 0,20 · **Gültigkeit:** X 0,40–0,80 · Y 0,15–0,55 · Z 0,00–0,40 · **Takt:** 4/4
- **Töne (rel):** [-12, -15, -19, -22] · **Intervalle:** -3, -4, -3
- **Rhythmus:** eigene Dauern: 7680 · **Gesamtzyklus:** 4 Ereignisse / 30720 Ticks
- **Harmonische Voraussetzung:** Harmoniefolge mit passender Bassstufe
- **Geeignete Kombinationen:** EM-H007, EM-H008, EM-H013, EM-H016, EM-H017, EM-H018 · **Ungeeignete:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** I – begründete Interpretation (Terzkette); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B051 – Tonika–♭7–♭6-Schreiten in Vierteln
- **Charakter:** erzählend, ernst · **Säule:** A · **Typ:** EIG · **Rollen:** KB
- **XYZ-Anker:** 0,35 / 0,45 / 0,25 · **Gültigkeit:** X 0,15–0,55 · Y 0,25–0,65 · Z 0,05–0,45 · **Takt:** 4/4
- **Töne (rel):** [-12, -14, -16, -14] · **Intervalle:** -2, -2, +2
- **Rhythmus:** EM-R044 (Periode 3840 Ticks, 3 Einsätze) · **Gesamtzyklus:** 12 Ereignisse / 15360 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **Ungeeignete:** EM-H007, EM-H008, EM-H011, EM-H013, EM-H016 (Bastöne modusfremd); nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** E – eigenständige Gestaltung (stufenweiser Bass); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-B052 – Herzschlag mit später Pause
- **Charakter:** stockender Atem · **Säule:** B · **Typ:** EIG · **Rollen:** KB
- **XYZ-Anker:** beliebig / 0,25 / 0,35 · **Gültigkeit:** X 0,00–1,00 · Y 0,05–0,45 · Z 0,15–0,55 · **Takt:** 4/4
- **Töne (rel):** [-12, -12] · **Intervalle:** +0
- **Rhythmus:** EM-R002 (Periode 7680 Ticks, 2 Einsätze) · **Gesamtzyklus:** 2 Ereignisse / 7680 Ticks
- **Harmonische Voraussetzung:** Töne im Tonvorrat der Harmonie
- **Geeignete Kombinationen:** EM-H065, EM-H066, EM-H067, EM-H068, EM-H069, EM-H070 · **Ungeeignete:** –; nie zwei Bassvorlagen mit konkurrierendem Grundton gleichzeitig
- **Transformation:** EM-T002 (Oktavdopplung als Y-Gewicht), EM-T006/EM-T007, EM-T013 · **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Evidenz:** E – eigenständige Gestaltung (Herzschlag, geringe Dichte); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

## 10. C – Mikrozellen

Die Zelle ist Material, kein Motiv (Vertiefung 1.2). Identitätstypen: MENGE (exakte Pitch-Class-Menge), KLASSE (intervallische Identität unter Transposition), ORD (geordnete Intervallzelle), RHY (rhythmisch identifizierbare Zelle), KERN (stabile Kerntöne + wechselnder Farbton). **Inversion ist nicht automatisch Permutation:** Sie ist es nur, wenn die gespiegelte Menge exakt dieselbe Tonhöhenmenge ist; sonst entsteht eine andere Tonhöhenmenge mit gleicher Intervallklasse (Spalte „Inversion“). Keine zwanghafte Permutation: Permutationswechsel erfolgen an Blockgrenzen (typisch 4–8 Takte).

### EM-C001 – Kleinterz-Dyade
- **Charakter:** fragend, klein · **Säule:** AB · **Typ:** MENGE · **Größe:** 2 Töne
- **Tonhöhenmenge (Stufen):** {1, ♭3}
- **Primform:** [0, 3] · **Intervallvektor:** <001000>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 3 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** ja
- **Zulässige Permutationen:** alle 2 Ordnungen · **Transposition:** Tn um Akkordgrundton · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** Moll- oder dorisches Feld · **Rollen:** TU AR KB
- **XYZ-Anker:** 0,35 / beliebig / beliebig · **Gültigkeit:** X 0,15–0,55 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C002 (1 gem.), EM-C003 (1 gem.), EM-C011 (1 gem.), EM-C020 (1 gem.), EM-C025 (2 gem.), EM-C030 (1 gem.)
- **Evidenz:** N – nachgewiesenes Verfahren (kleine Terz (Wilcox: Drittes Konzert)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C002 – Ganzton-Dyade
- **Charakter:** suchend · **Säule:** AB · **Typ:** MENGE · **Größe:** 2 Töne
- **Tonhöhenmenge (Stufen):** {1, 2}
- **Primform:** [0, 2] · **Intervallvektor:** <010000>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 2 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** ja
- **Zulässige Permutationen:** alle 2 Ordnungen · **Transposition:** Tn · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** diatonisch · **Rollen:** TU AR
- **XYZ-Anker:** 0,55 / beliebig / beliebig · **Gültigkeit:** X 0,35–0,75 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C003 (1 gem.), EM-C011 (1 gem.), EM-C020 (2 gem.), EM-C025 (1 gem.), EM-C030 (1 gem.)
- **Evidenz:** I – begründete Interpretation (gr. Sekunde (filmmusicnotes: Frank-Zelle enthält gr. Sekunde)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C003 – Quart-Dyade
- **Charakter:** offen, archaisch · **Säule:** AB · **Typ:** MENGE · **Größe:** 2 Töne
- **Tonhöhenmenge (Stufen):** {1, 4}
- **Primform:** [0, 5] · **Intervallvektor:** <000010>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 5 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** ja
- **Zulässige Permutationen:** alle 2 Ordnungen · **Transposition:** Tn · **Oktavierung:** ±2 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** modal · **Rollen:** TU KB AR
- **XYZ-Anker:** 0,50 / beliebig / beliebig · **Gültigkeit:** X 0,30–0,70 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C002 (1 gem.), EM-C011 (2 gem.), EM-C020 (1 gem.), EM-C025 (2 gem.), EM-C030 (1 gem.)
- **Evidenz:** I – begründete Interpretation (Quarte (Frank-Zelle)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C004 – Halbton-Dyade
- **Charakter:** beklemmend · **Säule:** B · **Typ:** MENGE · **Größe:** 2 Töne
- **Tonhöhenmenge (Stufen):** {1, ♭2}
- **Primform:** [0, 1] · **Intervallvektor:** <100000>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 1 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** ja
- **Zulässige Permutationen:** alle 2 Ordnungen · **Transposition:** Tn · **Oktavierung:** ±2 Okt. (Spreizung zu gr. Septime/kl. None)
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** beliebig, als F/U-Schicht · **Rollen:** TU AR KF
- **XYZ-Anker:** 0,15 / beliebig / beliebig · **Gültigkeit:** X 0,00–0,35 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C002 (1 gem.), EM-C003 (1 gem.), EM-C005 (1 gem.), EM-C011 (1 gem.), EM-C014 (2 gem.)
- **Evidenz:** N – nachgewiesenes Verfahren (Halbtonballung (Suoni per Dino)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C005 – Tritonus-Dyade
- **Charakter:** unheilvoll · **Säule:** B · **Typ:** MENGE · **Größe:** 2 Töne
- **Tonhöhenmenge (Stufen):** {1, ♯4/♭5}
- **Primform:** [0, 6] · **Intervallvektor:** <000001>
- **Inversion:** ergibt dieselbe Tonhöhenmenge (= Permutation) · **Inversion zulässig:** ja
- **Zulässige Permutationen:** alle 2 Ordnungen · **Transposition:** Tn · **Oktavierung:** ±2 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** beliebig, als F/U-Schicht · **Rollen:** TU ST-frei AR
- **XYZ-Anker:** 0,20 / beliebig / beliebig · **Gültigkeit:** X 0,00–0,40 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C002 (1 gem.), EM-C003 (1 gem.), EM-C004 (1 gem.), EM-C011 (1 gem.), EM-C014 (1 gem.)
- **Evidenz:** N – nachgewiesenes Verfahren (Tritonus (Suoni per Dino)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C006 – Absteigende Stufenzelle 1–7–5 (Dur)
- **Charakter:** einfach, unerschütterlich · **Säule:** A · **Typ:** KLASSE · **Größe:** 3 Töne
- **Tonhöhenmenge (Stufen):** {1, 7, 5} · feste Ordnung: 1 → 7 → 5
- **Primform:** [0, 1, 5] · **Intervallvektor:** <100110>
- **Inversion:** ergibt eine andere Mengenklasse-Lage; nur intervallische Identität bleibt · **Inversion zulässig:** nein
- **Zulässige Permutationen:** alle 6 Ordnungen, keine unmittelbare Wiederholung derselben Ordnung · **Transposition:** nur Tn mit Harmonie · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei; Zyklus 3 gegen Takt 4 bevorzugt · **Harmonische Voraussetzung:** Dur, Tonika oder Subdominante · **Rollen:** AR HM TU
- **XYZ-Anker:** 0,75 / beliebig / beliebig · **Gültigkeit:** X 0,55–0,95 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C002 (1 gem.), EM-C003 (1 gem.), EM-C007 (2 gem.), EM-C008 (2 gem.), EM-C009 (1 gem.)
- **Evidenz:** N – nachgewiesenes Verfahren (Drei-Ton-Zelle 8–7–5 (Wilcox: Se telefonando/The Falls) – Verfahren, kein Thema); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C007 – Sus2-Quintzelle
- **Charakter:** weit, unberührt · **Säule:** A · **Typ:** MENGE · **Größe:** 3 Töne
- **Tonhöhenmenge (Stufen):** {1, 2, 5}
- **Primform:** [0, 2, 7] · **Intervallvektor:** <010020>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 2 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** ja
- **Zulässige Permutationen:** alle 6 Ordnungen · **Transposition:** Tn · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** Tonika, ♭VI, ♭III, IV · **Rollen:** AR TU HM
- **XYZ-Anker:** 0,60 / beliebig / beliebig · **Gültigkeit:** X 0,40–0,80 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C002 (2 gem.), EM-C003 (1 gem.), EM-C006 (2 gem.), EM-C008 (2 gem.), EM-C009 (2 gem.)
- **Evidenz:** I – begründete Interpretation (diatonische Zelle); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C008 – Molldreiklang-Zelle
- **Charakter:** trauernd schlicht · **Säule:** A · **Typ:** MENGE · **Größe:** 3 Töne
- **Tonhöhenmenge (Stufen):** {1, ♭3, 5}
- **Primform:** [0, 3, 7] · **Intervallvektor:** <001110>
- **Inversion:** ergibt eine andere Mengenklasse-Lage; nur intervallische Identität bleibt · **Inversion zulässig:** nein
- **Zulässige Permutationen:** alle 6 Ordnungen · **Transposition:** Tn · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** Moll-Tonika · **Rollen:** AR TU
- **XYZ-Anker:** 0,35 / beliebig / beliebig · **Gültigkeit:** X 0,15–0,55 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (2 gem.), EM-C002 (1 gem.), EM-C003 (1 gem.), EM-C006 (2 gem.), EM-C007 (2 gem.), EM-C009 (2 gem.)
- **Evidenz:** I – begründete Interpretation (Dreiklang als Zelle); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C009 – Reibungskern 1–2–♭3
- **Charakter:** schmerzend nah · **Säule:** A · **Typ:** MENGE · **Größe:** 3 Töne
- **Tonhöhenmenge (Stufen):** {1, 2, ♭3}
- **Primform:** [0, 1, 3] · **Intervallvektor:** <111000>
- **Inversion:** ergibt eine andere Mengenklasse-Lage; nur intervallische Identität bleibt · **Inversion zulässig:** nein
- **Zulässige Permutationen:** alle 6 Ordnungen · **Transposition:** nur mit Harmonie · **Oktavierung:** ±1 Okt.; Halbton 2–♭3 eng oder offen
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** Moll-add9-Feld · **Rollen:** TU AR GS
- **XYZ-Anker:** 0,35 / beliebig / beliebig · **Gültigkeit:** X 0,15–0,55 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (2 gem.), EM-C002 (2 gem.), EM-C003 (1 gem.), EM-C006 (1 gem.), EM-C007 (2 gem.), EM-C008 (2 gem.)
- **Evidenz:** N – nachgewiesenes Verfahren (madd9-Reibung (Tagg)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C010 – Moll-add9-Zelle
- **Charakter:** melancholische Identität · **Säule:** A · **Typ:** MENGE · **Größe:** 4 Töne
- **Tonhöhenmenge (Stufen):** {1, 2, ♭3, 5}
- **Primform:** [0, 2, 3, 7] · **Intervallvektor:** <111120>
- **Inversion:** ergibt eine andere Mengenklasse-Lage; nur intervallische Identität bleibt · **Inversion zulässig:** nein
- **Zulässige Permutationen:** alle 24 Ordnungen · **Transposition:** nur mit Harmonie · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** i(add9), iv(add9) bei Tn=5 · **Rollen:** AR TU HM
- **XYZ-Anker:** 0,40 / beliebig / beliebig · **Gültigkeit:** X 0,20–0,60 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (2 gem.), EM-C002 (2 gem.), EM-C003 (1 gem.), EM-C006 (2 gem.), EM-C007 (3 gem.), EM-C008 (3 gem.)
- **Evidenz:** N – nachgewiesenes Verfahren (madd9 (Tagg)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C011 – Quart-Quint-Zelle
- **Charakter:** erhaben leer · **Säule:** AB · **Typ:** MENGE · **Größe:** 3 Töne
- **Tonhöhenmenge (Stufen):** {1, 4, 5}
- **Primform:** [0, 2, 7] · **Intervallvektor:** <010020>
- **Inversion:** ergibt dieselbe Tonhöhenmenge (= Permutation) · **Inversion zulässig:** ja
- **Zulässige Permutationen:** alle 6 Ordnungen · **Transposition:** Tn · **Oktavierung:** ±2 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** modal, quartal · **Rollen:** KB AR TU
- **XYZ-Anker:** 0,50 / beliebig / beliebig · **Gültigkeit:** X 0,30–0,70 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C002 (1 gem.), EM-C003 (2 gem.), EM-C020 (1 gem.), EM-C025 (3 gem.), EM-C030 (1 gem.)
- **Evidenz:** I – begründete Interpretation (Quarte/Quinte (Frank-Zelle)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C012 – Pentatonischer Dreiton aufwärts
- **Charakter:** sanft · **Säule:** A · **Typ:** MENGE · **Größe:** 3 Töne
- **Tonhöhenmenge (Stufen):** {1, 2, 4}
- **Primform:** [0, 2, 5] · **Intervallvektor:** <011010>
- **Inversion:** ergibt eine andere Mengenklasse-Lage; nur intervallische Identität bleibt · **Inversion zulässig:** ja
- **Zulässige Permutationen:** alle 6 Ordnungen · **Transposition:** Tn · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** pentatonisch, dorisch · **Rollen:** HM AR TU
- **XYZ-Anker:** 0,60 / beliebig / beliebig · **Gültigkeit:** X 0,40–0,80 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C002 (2 gem.), EM-C003 (2 gem.), EM-C006 (1 gem.), EM-C007 (2 gem.), EM-C008 (1 gem.)
- **Evidenz:** E – eigenständige Gestaltung (pentatonische Zelle); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C013 – Moll-pentatonischer Dreiton
- **Charakter:** erdig · **Säule:** A · **Typ:** MENGE · **Größe:** 3 Töne
- **Tonhöhenmenge (Stufen):** {1, ♭3, 4}
- **Primform:** [0, 2, 5] · **Intervallvektor:** <011010>
- **Inversion:** ergibt eine andere Mengenklasse-Lage; nur intervallische Identität bleibt · **Inversion zulässig:** ja
- **Zulässige Permutationen:** alle 6 Ordnungen · **Transposition:** Tn · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** Moll, dorisch · **Rollen:** HM AR KB
- **XYZ-Anker:** 0,40 / beliebig / beliebig · **Gültigkeit:** X 0,20–0,60 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (2 gem.), EM-C002 (1 gem.), EM-C003 (2 gem.), EM-C006 (1 gem.), EM-C007 (1 gem.), EM-C008 (2 gem.)
- **Evidenz:** E – eigenständige Gestaltung (pentatonische Zelle); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C014 – Phrygischer Dreiton
- **Charakter:** dunkel-sakral · **Säule:** B · **Typ:** MENGE · **Größe:** 3 Töne
- **Tonhöhenmenge (Stufen):** {1, ♭2, ♭3}
- **Primform:** [0, 1, 3] · **Intervallvektor:** <111000>
- **Inversion:** ergibt eine andere Mengenklasse-Lage; nur intervallische Identität bleibt · **Inversion zulässig:** ja
- **Zulässige Permutationen:** alle 6 Ordnungen · **Transposition:** Tn · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** phrygisch · **Rollen:** TU AR GS
- **XYZ-Anker:** 0,20 / beliebig / beliebig · **Gültigkeit:** X 0,00–0,40 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (2 gem.), EM-C002 (1 gem.), EM-C003 (1 gem.), EM-C004 (2 gem.), EM-C005 (1 gem.), EM-C011 (1 gem.)
- **Evidenz:** E – eigenständige Gestaltung (modale Zelle); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C015 – Halbton-Tritonus-Dreiton
- **Charakter:** Bedrohung, kompakt · **Säule:** B · **Typ:** KLASSE · **Größe:** 3 Töne
- **Tonhöhenmenge (Stufen):** {1, ♭2, ♯4/♭5}
- **Primform:** [0, 1, 6] · **Intervallvektor:** <100011>
- **Inversion:** ergibt eine andere Mengenklasse-Lage; nur intervallische Identität bleibt · **Inversion zulässig:** ja
- **Zulässige Permutationen:** alle 6 Ordnungen · **Transposition:** Tn frei · **Oktavierung:** ±2 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** F/U-Schicht · **Rollen:** TU AR KB
- **XYZ-Anker:** 0,15 / beliebig / beliebig · **Gültigkeit:** X 0,00–0,35 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C002 (1 gem.), EM-C003 (1 gem.), EM-C004 (2 gem.), EM-C005 (2 gem.), EM-C011 (1 gem.)
- **Evidenz:** E – eigenständige Gestaltung (Halbton + Tritonus); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C016 – Halbton-Terz-Dreiton
- **Charakter:** verzerrte Kindlichkeit · **Säule:** B · **Typ:** KLASSE · **Größe:** 3 Töne
- **Tonhöhenmenge (Stufen):** {1, ♭2, 3}
- **Primform:** [0, 1, 4] · **Intervallvektor:** <101100>
- **Inversion:** ergibt eine andere Mengenklasse-Lage; nur intervallische Identität bleibt · **Inversion zulässig:** ja
- **Zulässige Permutationen:** alle 6 Ordnungen · **Transposition:** Tn frei · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** F-Schicht oder harm. Moll · **Rollen:** TU AR
- **XYZ-Anker:** 0,30 / beliebig / beliebig · **Gültigkeit:** X 0,10–0,50 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C002 (1 gem.), EM-C003 (1 gem.), EM-C004 (2 gem.), EM-C005 (1 gem.), EM-C011 (1 gem.)
- **Evidenz:** E – eigenständige Gestaltung (chromatische Zelle); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C017 – Übermäßige Terzenzelle
- **Charakter:** traumhaft symmetrisch · **Säule:** B · **Typ:** KLASSE · **Größe:** 3 Töne
- **Tonhöhenmenge (Stufen):** {1, 3, ♭6}
- **Primform:** [0, 4, 8] · **Intervallvektor:** <000300>
- **Inversion:** ergibt dieselbe Tonhöhenmenge (= Permutation) · **Inversion zulässig:** ja
- **Zulässige Permutationen:** alle 6 Ordnungen · **Transposition:** nur T4-symmetrisch (3 Lagen) · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** hexatonisch/Ganzton · **Rollen:** AR TU
- **XYZ-Anker:** 0,60 / beliebig / beliebig · **Gültigkeit:** X 0,40–0,80 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C002 (1 gem.), EM-C003 (1 gem.), EM-C004 (1 gem.), EM-C005 (1 gem.), EM-C011 (1 gem.)
- **Evidenz:** E – eigenständige Gestaltung (symmetrischer Vorrat); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C018 – Verminderte Terzenzelle
- **Charakter:** lauernd · **Säule:** B · **Typ:** KLASSE · **Größe:** 3 Töne
- **Tonhöhenmenge (Stufen):** {1, ♭3, ♯4/♭5}
- **Primform:** [0, 3, 6] · **Intervallvektor:** <002001>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 6 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** ja
- **Zulässige Permutationen:** alle 6 Ordnungen · **Transposition:** Tn · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** oktatonisch, harm. Moll · **Rollen:** AR TU
- **XYZ-Anker:** 0,30 / beliebig / beliebig · **Gültigkeit:** X 0,10–0,50 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (2 gem.), EM-C002 (1 gem.), EM-C003 (1 gem.), EM-C004 (1 gem.), EM-C005 (2 gem.), EM-C011 (1 gem.)
- **Evidenz:** E – eigenständige Gestaltung (symmetrischer Vorrat); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C019 – Chromatischer Dreiton
- **Charakter:** kriechend · **Säule:** B · **Typ:** MENGE · **Größe:** 3 Töne
- **Tonhöhenmenge (Stufen):** {1, ♭2, 2}
- **Primform:** [0, 1, 2] · **Intervallvektor:** <210000>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 2 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** ja
- **Zulässige Permutationen:** alle 6 Ordnungen · **Transposition:** Tn · **Oktavierung:** ±2 Okt. (Spreizung)
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** Cluster-Schicht · **Rollen:** TU AR KF
- **XYZ-Anker:** 0,15 / beliebig / beliebig · **Gültigkeit:** X 0,00–0,35 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C002 (2 gem.), EM-C003 (1 gem.), EM-C004 (2 gem.), EM-C005 (1 gem.), EM-C011 (1 gem.)
- **Evidenz:** N – nachgewiesenes Verfahren (Cluster (cuebycue)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C020 – Ganztondreiton
- **Charakter:** schwebend · **Säule:** AB · **Typ:** MENGE · **Größe:** 3 Töne
- **Tonhöhenmenge (Stufen):** {1, 2, 3}
- **Primform:** [0, 2, 4] · **Intervallvektor:** <020100>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 4 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** ja
- **Zulässige Permutationen:** alle 6 Ordnungen · **Transposition:** Tn · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** Ganzton oder Dur/lydisch · **Rollen:** AR TU
- **XYZ-Anker:** 0,65 / beliebig / beliebig · **Gültigkeit:** X 0,45–0,85 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C002 (2 gem.), EM-C003 (1 gem.), EM-C011 (1 gem.), EM-C030 (1 gem.)
- **Evidenz:** E – eigenständige Gestaltung (Ganztonzelle); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C021 – Vierton-Ballung mit Tritonus-Anker
- **Charakter:** starre Bedrohung · **Säule:** B · **Typ:** MENGE · **Größe:** 4 Töne
- **Tonhöhenmenge (Stufen):** {1, 3, 4, ♯4/♭5}
- **Primform:** [0, 1, 2, 6] · **Intervallvektor:** <210111>
- **Inversion:** ergibt eine andere Mengenklasse-Lage; nur intervallische Identität bleibt · **Inversion zulässig:** ja
- **Zulässige Permutationen:** alle 24 Ordnungen · **Transposition:** Tn · **Oktavierung:** ±2 Okt.
- **Rhythmische Voraussetzung:** frei; weite Abstände bevorzugt · **Harmonische Voraussetzung:** nur als Klangobjekt · **Rollen:** KF TU ST-frei
- **XYZ-Anker:** 0,10 / beliebig / beliebig · **Gültigkeit:** X 0,00–0,30 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C002 (1 gem.), EM-C003 (2 gem.), EM-C004 (1 gem.), EM-C005 (2 gem.), EM-C011 (2 gem.)
- **Evidenz:** N – nachgewiesenes Verfahren (Suoni per Dino: A, D♭, D, E♭ (Covell) – Mengentyp, nicht Werkzitat); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C022 – B-A-C-H geordnet
- **Charakter:** verschlüsselt · **Säule:** B · **Typ:** ORD · **Größe:** 4 Töne
- **Tonhöhenmenge (Stufen):** {♭7, 6, 1, 7} · feste Ordnung: ♭7 → 6 → 1 → 7
- **Primform:** [0, 1, 2, 3] · **Intervallvektor:** <321000>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 9 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** nein
- **Zulässige Permutationen:** nur Rotation der festen Ordnung · **Transposition:** Tn frei (Kode bleibt erkennbar) · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** chromatisch/frei · **Rollen:** TU GS AR
- **XYZ-Anker:** 0,40 / beliebig / beliebig · **Gültigkeit:** X 0,20–0,60 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C002 (1 gem.), EM-C003 (1 gem.), EM-C004 (1 gem.), EM-C005 (1 gem.), EM-C011 (1 gem.)
- **Evidenz:** N – nachgewiesenes Verfahren (Tonbuchstaben-Kode (Morricone, Life Notes)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C023 – B-A-C-H als Menge
- **Charakter:** verborgen · **Säule:** B · **Typ:** MENGE · **Größe:** 4 Töne
- **Tonhöhenmenge (Stufen):** {6, ♭7, 7, 1}
- **Primform:** [0, 1, 2, 3] · **Intervallvektor:** <321000>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 9 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** ja
- **Zulässige Permutationen:** alle 24 Ordnungen · **Transposition:** Tn · **Oktavierung:** ±2 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** chromatisch · **Rollen:** TU AR KF
- **XYZ-Anker:** 0,35 / beliebig / beliebig · **Gültigkeit:** X 0,15–0,55 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C002 (1 gem.), EM-C003 (1 gem.), EM-C004 (1 gem.), EM-C005 (1 gem.), EM-C011 (1 gem.)
- **Evidenz:** N – nachgewiesenes Verfahren (Kode-Permutation (Battista zu Musica per una fine)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C024 – Chromatischer Sechston (Ricercar-Typ)
- **Charakter:** gelehrte Unruhe · **Säule:** B · **Typ:** ORD · **Größe:** 6 Töne
- **Tonhöhenmenge (Stufen):** {1, ♭2, 2, ♭3, 3, 4} · feste Ordnung: 1 → ♭2 → 2 → ♭3 → 3 → 4
- **Primform:** [0, 1, 2, 3, 4, 5] · **Intervallvektor:** <543210>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 5 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** nein
- **Zulässige Permutationen:** nur Rotation der festen Ordnung · **Transposition:** Tn · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** langsam, Halbe bevorzugt · **Harmonische Voraussetzung:** frei · **Rollen:** GS TU LF
- **XYZ-Anker:** 0,35 / beliebig / beliebig · **Gültigkeit:** X 0,15–0,55 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (2 gem.), EM-C002 (2 gem.), EM-C003 (2 gem.), EM-C004 (2 gem.), EM-C005 (1 gem.), EM-C011 (2 gem.)
- **Evidenz:** N – nachgewiesenes Verfahren (Frescobaldi-Kode (abstrahiert, kein Zitat)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C025 – Äolisch-phrygischer Austauschkern
- **Charakter:** kaum merkliche Eintrübung · **Säule:** AB · **Typ:** KERN · **Größe:** 7 Töne
- **Tonhöhenmenge (Stufen):** {1, ♭3, 4, 5, ♭6, ♭7} · Austauschtöne: 2 | ♭2
- **Primform:** [0, 2, 4, 5, 7, 9] · **Intervallvektor:** <143250>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 3 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** nein
- **Zulässige Permutationen:** alle 720 Ordnungen · **Transposition:** nur mit Tonzentrum · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** Moll-Feld · **Rollen:** AR TU LF
- **XYZ-Anker:** 0,30 / beliebig / beliebig · **Gültigkeit:** X 0,10–0,50 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (2 gem.), EM-C002 (1 gem.), EM-C003 (2 gem.), EM-C011 (3 gem.), EM-C030 (2 gem.)
- **Evidenz:** N – nachgewiesenes Verfahren (6 gemeinsame + wechselnder 7. Ton (Wilcox: Ut-Prinzip)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C026 – Dorisch-äolischer Austauschkern
- **Charakter:** Licht und Schatten der Sexte · **Säule:** A · **Typ:** KERN · **Größe:** 7 Töne
- **Tonhöhenmenge (Stufen):** {1, 2, ♭3, 4, 5, ♭7} · Austauschtöne: 6 | ♭6
- **Primform:** [0, 2, 4, 5, 7, 9] · **Intervallvektor:** <143250>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 5 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** nein
- **Zulässige Permutationen:** alle 720 Ordnungen · **Transposition:** nur mit Tonzentrum · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** Moll-Tonika, iv/IV · **Rollen:** AR TU HM
- **XYZ-Anker:** 0,50 / beliebig / beliebig · **Gültigkeit:** X 0,30–0,70 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (2 gem.), EM-C002 (2 gem.), EM-C003 (2 gem.), EM-C006 (2 gem.), EM-C007 (3 gem.), EM-C008 (3 gem.)
- **Evidenz:** N – nachgewiesenes Verfahren (Austauschton (Ut-Prinzip)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C027 – Zwei Kleinterzpaare
- **Charakter:** verkettet · **Säule:** B · **Typ:** ORD · **Größe:** 4 Töne
- **Tonhöhenmenge (Stufen):** {1, ♭3, 4, ♭6} · feste Ordnung: 1 → ♭3 → 4 → ♭6
- **Primform:** [0, 3, 5, 8] · **Intervallvektor:** <012120>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 8 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** nein
- **Zulässige Permutationen:** keine (Ordnung = Identität) · **Transposition:** Tn · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** rhythmische Kontraktion/Extension (EM-R027) · **Harmonische Voraussetzung:** Moll, aeolisch · **Rollen:** KB AR
- **XYZ-Anker:** 0,30 / beliebig / beliebig · **Gültigkeit:** X 0,10–0,50 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (2 gem.), EM-C002 (1 gem.), EM-C003 (2 gem.), EM-C004 (1 gem.), EM-C005 (1 gem.), EM-C011 (2 gem.)
- **Evidenz:** N – nachgewiesenes Verfahren (zwei Paare kleiner Terzen (Wilcox)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C028 – Dorischer Pentachord
- **Charakter:** erzählend · **Säule:** A · **Typ:** MENGE · **Größe:** 5 Töne
- **Tonhöhenmenge (Stufen):** {1, 2, ♭3, 4, 5}
- **Primform:** [0, 2, 3, 5, 7] · **Intervallvektor:** <132130>
- **Inversion:** ergibt eine andere Mengenklasse-Lage; nur intervallische Identität bleibt · **Inversion zulässig:** nein
- **Zulässige Permutationen:** alle 120 Ordnungen · **Transposition:** Tn · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** dorisch/äolisch · **Rollen:** HM GS TU
- **XYZ-Anker:** 0,50 / beliebig / beliebig · **Gültigkeit:** X 0,30–0,70 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (2 gem.), EM-C002 (2 gem.), EM-C003 (2 gem.), EM-C006 (2 gem.), EM-C007 (3 gem.), EM-C008 (3 gem.)
- **Evidenz:** I – begründete Interpretation (modale Zelle (≤7 Töne, Morricone)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C029 – Dur-Pentatonik
- **Charakter:** hell, nicht fröhlich · **Säule:** A · **Typ:** MENGE · **Größe:** 5 Töne
- **Tonhöhenmenge (Stufen):** {1, 2, 3, 5, 6}
- **Primform:** [0, 2, 4, 7, 9] · **Intervallvektor:** <032140>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 4 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** nein
- **Zulässige Permutationen:** alle 120 Ordnungen · **Transposition:** Tn · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** Dur, lydisch · **Rollen:** HM AR TU
- **XYZ-Anker:** 0,75 / beliebig / beliebig · **Gültigkeit:** X 0,55–0,95 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C002 (2 gem.), EM-C003 (1 gem.), EM-C006 (2 gem.), EM-C007 (3 gem.), EM-C008 (2 gem.)
- **Evidenz:** I – begründete Interpretation (modale Zelle); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C030 – Kleinsext-Dyade (Glocke)
- **Charakter:** klagend-hell · **Säule:** AB · **Typ:** MENGE · **Größe:** 2 Töne
- **Tonhöhenmenge (Stufen):** {1, ♭6}
- **Primform:** [0, 4] · **Intervallvektor:** <000100>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 8 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** ja
- **Zulässige Permutationen:** alle 2 Ordnungen · **Transposition:** Tn · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** Repetition bevorzugt · **Harmonische Voraussetzung:** Moll, ♭VI · **Rollen:** TU GS
- **XYZ-Anker:** 0,40 / beliebig / beliebig · **Gültigkeit:** X 0,20–0,60 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C002 (1 gem.), EM-C003 (1 gem.), EM-C011 (1 gem.), EM-C020 (1 gem.), EM-C025 (2 gem.)
- **Evidenz:** N – nachgewiesenes Verfahren (wiederholte kleine Sexte (Bissett: Bird-Prolog)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C031 – Quint-Sekund-Kette
- **Charakter:** kristallin · **Säule:** A · **Typ:** MENGE · **Größe:** 4 Töne
- **Tonhöhenmenge (Stufen):** {1, 2, 5, 6}
- **Primform:** [0, 2, 5, 7] · **Intervallvektor:** <021030>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 9 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** ja
- **Zulässige Permutationen:** alle 24 Ordnungen · **Transposition:** Tn · **Oktavierung:** ±2 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** Dur, sus, lydisch · **Rollen:** AR TU
- **XYZ-Anker:** 0,75 / beliebig / beliebig · **Gültigkeit:** X 0,55–0,95 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C002 (2 gem.), EM-C003 (1 gem.), EM-C006 (2 gem.), EM-C007 (3 gem.), EM-C008 (2 gem.)
- **Evidenz:** E – eigenständige Gestaltung (quintverwandt); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C032 – Moll mit kleiner Sexte
- **Charakter:** tragisch weich · **Säule:** A · **Typ:** MENGE · **Größe:** 4 Töne
- **Tonhöhenmenge (Stufen):** {1, ♭3, 5, ♭6}
- **Primform:** [0, 1, 5, 8] · **Intervallvektor:** <101220>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 3 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** nein
- **Zulässige Permutationen:** alle 24 Ordnungen · **Transposition:** Tn · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** Moll, ♭VI-maj7 · **Rollen:** TU AR GS
- **XYZ-Anker:** 0,30 / beliebig / beliebig · **Gültigkeit:** X 0,10–0,50 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (2 gem.), EM-C002 (1 gem.), EM-C003 (1 gem.), EM-C006 (2 gem.), EM-C007 (2 gem.), EM-C008 (3 gem.)
- **Evidenz:** E – eigenständige Gestaltung (Moll + ♭6); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C033 – Dur-Moll-Terz-Zelle
- **Charakter:** Freude und Trauer zugleich · **Säule:** A · **Typ:** MENGE · **Größe:** 4 Töne
- **Tonhöhenmenge (Stufen):** {1, ♭3, 3, 5}
- **Primform:** [0, 3, 4, 7] · **Intervallvektor:** <102210>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 7 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** nein
- **Zulässige Permutationen:** alle 24 Ordnungen, keine unmittelbare Wiederholung derselben Ordnung · **Transposition:** nur mit Harmonie · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** Dur-Tonika (♭3 als F) · **Rollen:** AR TU HM
- **XYZ-Anker:** 0,55 / beliebig / beliebig · **Gültigkeit:** X 0,35–0,75 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (2 gem.), EM-C002 (1 gem.), EM-C003 (1 gem.), EM-C006 (2 gem.), EM-C007 (2 gem.), EM-C008 (3 gem.)
- **Evidenz:** I – begründete Interpretation (beide Terzen (Crisis-Blog, Laienquelle)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C034 – Lydischer Vierton
- **Charakter:** kalte Klarheit · **Säule:** A · **Typ:** MENGE · **Größe:** 4 Töne
- **Tonhöhenmenge (Stufen):** {1, 3, ♯4/♭5, 5}
- **Primform:** [0, 1, 3, 7] · **Intervallvektor:** <111111>
- **Inversion:** ergibt eine andere Mengenklasse-Lage; nur intervallische Identität bleibt · **Inversion zulässig:** nein
- **Zulässige Permutationen:** alle 24 Ordnungen · **Transposition:** Tn · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** lydisch, maj7♯11 · **Rollen:** AR TU
- **XYZ-Anker:** 0,85 / beliebig / beliebig · **Gültigkeit:** X 0,65–1,00 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C002 (1 gem.), EM-C003 (1 gem.), EM-C006 (2 gem.), EM-C007 (2 gem.), EM-C008 (2 gem.)
- **Evidenz:** E – eigenständige Gestaltung (lydische Farbe); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C035 – Pseudoserieller Siebenton
- **Charakter:** rationale Kälte · **Säule:** B · **Typ:** KLASSE · **Größe:** 7 Töne
- **Tonhöhenmenge (Stufen):** {1, ♭2, 3, 4, ♯4/♭5, 6, 7}
- **Primform:** [0, 1, 2, 4, 7, 8, 9] · **Intervallvektor:** <433452>
- **Inversion:** ergibt eine andere Mengenklasse-Lage; nur intervallische Identität bleibt · **Inversion zulässig:** ja
- **Zulässige Permutationen:** alle 5040 Ordnungen, keine unmittelbare Wiederholung derselben Ordnung · **Transposition:** Tn frei · **Oktavierung:** ±2 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** keine (atonal) · **Rollen:** TU AR GS LF
- **XYZ-Anker:** 0,40 / beliebig / beliebig · **Gültigkeit:** X 0,20–0,60 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C003 (2 gem.), EM-C004 (2 gem.), EM-C005 (2 gem.), EM-C015 (3 gem.), EM-C016 (3 gem.), EM-C021 (4 gem.)
- **Evidenz:** N – nachgewiesenes Verfahren (≤7 Töne (Morricone); pseudo-seriell (Grove)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C036 – Allintervall-Vierton
- **Charakter:** maximale Vielfalt auf kleinem Raum · **Säule:** B · **Typ:** KLASSE · **Größe:** 4 Töne
- **Tonhöhenmenge (Stufen):** {1, ♭2, 3, ♯4/♭5}
- **Primform:** [0, 1, 4, 6] · **Intervallvektor:** <111111>
- **Inversion:** ergibt eine andere Mengenklasse-Lage; nur intervallische Identität bleibt · **Inversion zulässig:** ja
- **Zulässige Permutationen:** alle 24 Ordnungen · **Transposition:** Tn frei · **Oktavierung:** ±2 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** atonal · **Rollen:** TU AR
- **XYZ-Anker:** 0,30 / beliebig / beliebig · **Gültigkeit:** X 0,10–0,50 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C002 (1 gem.), EM-C003 (1 gem.), EM-C004 (2 gem.), EM-C005 (2 gem.), EM-C011 (1 gem.)
- **Evidenz:** E – eigenständige Gestaltung (Allintervall-Tetrachord); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C037 – Doppel-Halbton
- **Charakter:** zweifach eng · **Säule:** B · **Typ:** KLASSE · **Größe:** 4 Töne
- **Tonhöhenmenge (Stufen):** {1, ♭2, 4, ♯4/♭5}
- **Primform:** [0, 1, 5, 6] · **Intervallvektor:** <200121>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 6 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** ja
- **Zulässige Permutationen:** alle 24 Ordnungen · **Transposition:** Tn frei · **Oktavierung:** ±2 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** atonal · **Rollen:** TU KF
- **XYZ-Anker:** 0,20 / beliebig / beliebig · **Gültigkeit:** X 0,00–0,40 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C002 (1 gem.), EM-C003 (2 gem.), EM-C004 (2 gem.), EM-C005 (2 gem.), EM-C011 (2 gem.)
- **Evidenz:** E – eigenständige Gestaltung (Halbtonpaare); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C038 – Tritonus-Ganzton-Vierton
- **Charakter:** gespaltene Symmetrie · **Säule:** B · **Typ:** KLASSE · **Größe:** 4 Töne
- **Tonhöhenmenge (Stufen):** {1, 2, ♯4/♭5, ♭6}
- **Primform:** [0, 2, 6, 8] · **Intervallvektor:** <020202>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 2, 8 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** ja
- **Zulässige Permutationen:** alle 24 Ordnungen · **Transposition:** Tn (T6-symmetrisch) · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** Ganzton/oktatonisch · **Rollen:** AR TU
- **XYZ-Anker:** 0,45 / beliebig / beliebig · **Gültigkeit:** X 0,25–0,65 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C002 (2 gem.), EM-C003 (1 gem.), EM-C004 (1 gem.), EM-C005 (2 gem.), EM-C011 (1 gem.)
- **Evidenz:** E – eigenständige Gestaltung (symmetrische Menge); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C039 – Klagezelle abwärts (geordnet)
- **Charakter:** Seufzerkette · **Säule:** A · **Typ:** ORD · **Größe:** 5 Töne
- **Tonhöhenmenge (Stufen):** {5, 4, ♭3, 2, 1} · feste Ordnung: 5 → 4 → ♭3 → 2 → 1
- **Primform:** [0, 2, 3, 5, 7] · **Intervallvektor:** <132130>
- **Inversion:** ergibt eine andere Mengenklasse-Lage; nur intervallische Identität bleibt · **Inversion zulässig:** nein
- **Zulässige Permutationen:** keine (Ordnung = Identität) · **Transposition:** nur mit Harmonie · **Oktavierung:** Einzelton ±1 Okt. nur am Ende
- **Rhythmische Voraussetzung:** lang–kurz-Seufzer · **Harmonische Voraussetzung:** Moll · **Rollen:** HM GS TU
- **XYZ-Anker:** 0,30 / beliebig / beliebig · **Gültigkeit:** X 0,10–0,50 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (2 gem.), EM-C002 (2 gem.), EM-C003 (2 gem.), EM-C006 (2 gem.), EM-C007 (3 gem.), EM-C008 (3 gem.)
- **Evidenz:** E – eigenständige Gestaltung (absteigende Linie); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C040 – Sehnsuchtszelle Quarte + Sekunde (geordnet)
- **Charakter:** Aufbruch ins Offene · **Säule:** A · **Typ:** ORD · **Größe:** 3 Töne
- **Tonhöhenmenge (Stufen):** {1, 4, 5} · feste Ordnung: 1 → 4 → 5
- **Primform:** [0, 2, 7] · **Intervallvektor:** <010020>
- **Inversion:** ergibt dieselbe Tonhöhenmenge (= Permutation) · **Inversion zulässig:** nein
- **Zulässige Permutationen:** nur Rotation der festen Ordnung · **Transposition:** Tn · **Oktavierung:** letzter Ton ±1 Okt.
- **Rhythmische Voraussetzung:** erster Ton lang · **Harmonische Voraussetzung:** Tonika/Subdominante · **Rollen:** HM GS
- **XYZ-Anker:** 0,60 / beliebig / beliebig · **Gültigkeit:** X 0,40–0,80 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C002 (1 gem.), EM-C003 (2 gem.), EM-C006 (2 gem.), EM-C007 (2 gem.), EM-C008 (2 gem.)
- **Evidenz:** E – eigenständige Gestaltung (Intervallthema (Morricone: Thema aus Intervallen)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C041 – Große-Septime-Zelle
- **Charakter:** zärtliche Spannung · **Säule:** A · **Typ:** MENGE · **Größe:** 4 Töne
- **Tonhöhenmenge (Stufen):** {1, 3, 5, 7}
- **Primform:** [0, 1, 5, 8] · **Intervallvektor:** <101220>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 11 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** nein
- **Zulässige Permutationen:** alle 24 Ordnungen · **Transposition:** Tn · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** maj7-Felder · **Rollen:** AR TU
- **XYZ-Anker:** 0,75 / beliebig / beliebig · **Gültigkeit:** X 0,55–0,95 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C002 (1 gem.), EM-C003 (1 gem.), EM-C006 (3 gem.), EM-C007 (2 gem.), EM-C008 (2 gem.)
- **Evidenz:** E – eigenständige Gestaltung (maj7); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C042 – Moll-Septzelle
- **Charakter:** nachdenklich · **Säule:** A · **Typ:** MENGE · **Größe:** 4 Töne
- **Tonhöhenmenge (Stufen):** {1, ♭3, 5, ♭7}
- **Primform:** [0, 3, 5, 8] · **Intervallvektor:** <012120>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 10 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** nein
- **Zulässige Permutationen:** alle 24 Ordnungen · **Transposition:** Tn · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** m7, dorisch · **Rollen:** AR TU
- **XYZ-Anker:** 0,45 / beliebig / beliebig · **Gültigkeit:** X 0,25–0,65 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (2 gem.), EM-C002 (1 gem.), EM-C003 (1 gem.), EM-C006 (2 gem.), EM-C007 (2 gem.), EM-C008 (3 gem.)
- **Evidenz:** E – eigenständige Gestaltung (m7); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C043 – Äolischer Heptachord
- **Charakter:** voller Modus · **Säule:** A · **Typ:** MENGE · **Größe:** 7 Töne
- **Tonhöhenmenge (Stufen):** {1, 2, ♭3, 4, 5, ♭6, ♭7}
- **Primform:** [0, 1, 3, 5, 6, 8, 10] · **Intervallvektor:** <254361>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 10 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** nein
- **Zulässige Permutationen:** alle 5040 Ordnungen, keine unmittelbare Wiederholung derselben Ordnung · **Transposition:** Tn · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** aeolisch · **Rollen:** HM GS AR
- **XYZ-Anker:** 0,40 / beliebig / beliebig · **Gültigkeit:** X 0,20–0,60 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (2 gem.), EM-C002 (2 gem.), EM-C003 (2 gem.), EM-C007 (3 gem.), EM-C008 (3 gem.), EM-C009 (3 gem.)
- **Evidenz:** I – begründete Interpretation (Siebenton-Zelle aus Modus (Morricone)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C044 – Oktatonischer Tetrachord
- **Charakter:** geometrische Spannung · **Säule:** B · **Typ:** KLASSE · **Größe:** 4 Töne
- **Tonhöhenmenge (Stufen):** {1, ♭2, ♭3, 3}
- **Primform:** [0, 1, 3, 4] · **Intervallvektor:** <212100>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 4 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** ja
- **Zulässige Permutationen:** alle 24 Ordnungen · **Transposition:** Tn (T3-Familie) · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** oktatonisch · **Rollen:** AR TU
- **XYZ-Anker:** 0,35 / beliebig / beliebig · **Gültigkeit:** X 0,15–0,55 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (2 gem.), EM-C002 (1 gem.), EM-C003 (1 gem.), EM-C004 (2 gem.), EM-C005 (1 gem.), EM-C011 (1 gem.)
- **Evidenz:** E – eigenständige Gestaltung (oktatonischer Ausschnitt); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C045 – Klage-Moll mit ♭6 und 2
- **Charakter:** verwundbar · **Säule:** A · **Typ:** MENGE · **Größe:** 4 Töne
- **Tonhöhenmenge (Stufen):** {1, 2, ♭3, ♭6}
- **Primform:** [0, 1, 3, 7] · **Intervallvektor:** <111111>
- **Inversion:** ergibt eine andere Mengenklasse-Lage; nur intervallische Identität bleibt · **Inversion zulässig:** nein
- **Zulässige Permutationen:** alle 24 Ordnungen · **Transposition:** nur mit Harmonie · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** frei · **Harmonische Voraussetzung:** Moll, ♭VI-add9 · **Rollen:** TU GS AR
- **XYZ-Anker:** 0,30 / beliebig / beliebig · **Gültigkeit:** X 0,10–0,50 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (2 gem.), EM-C002 (2 gem.), EM-C003 (1 gem.), EM-C006 (1 gem.), EM-C007 (2 gem.), EM-C008 (2 gem.)
- **Evidenz:** E – eigenständige Gestaltung (Moll-add9 + ♭6); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-C046 – Zweitonpaar steigend (kleine Sekunde) für Pulsfelder
- **Charakter:** elektronisch kalt · **Säule:** B · **Typ:** RHY · **Größe:** 2 Töne
- **Tonhöhenmenge (Stufen):** {1, ♭2} · feste Ordnung: 1 → ♭2
- **Primform:** [0, 1] · **Intervallvektor:** <100000>
- **Inversion:** ergibt dieselbe Menge nach Transposition um 1 (gleiche Klasse, andere Tonhöhen) · **Inversion zulässig:** nein
- **Zulässige Permutationen:** keine · **Transposition:** Tn · **Oktavierung:** ±1 Okt.
- **Rhythmische Voraussetzung:** Paar auf Zählzeit 1 und 3 (EM-R063) · **Harmonische Voraussetzung:** beliebig über Puls · **Rollen:** AR TU
- **XYZ-Anker:** 0,30 / beliebig / beliebig · **Gültigkeit:** X 0,10–0,50 · Y 0,00–1,00 · Z 0,00–1,00
- **Zulässige Kombinationen (gemeinsame Töne, Vereinigung ≤ 7 Töne):** EM-C001 (1 gem.), EM-C002 (1 gem.), EM-C003 (1 gem.), EM-C004 (2 gem.), EM-C005 (1 gem.), EM-C011 (1 gem.)
- **Evidenz:** I – begründete Interpretation (steigende Zweitonpaare über Pulsbass (Filmtracks: The Thing) – eigene Intervallwahl); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

## 11. M – Motive und Melodik

33 von 50 Motiven sind zellunabhängig. Notation: Tonhöhe relativ (12 = Tonika Oktave 4), Dauer in Ticks.

### EM-M001 – Nonen-Seufzer (9→1)
- **Charakter:** sanft lösend · **Säule:** A · **Typ:** Intervallmotiv · **Modus:** aeolisch · **Takt:** 4/4 · **Länge:** 1 Takte
- **Töne/Dauern:** +14/1920 +12/1920
- **Intervalle:** -2 · **Ambitus:** +12 bis +14 · **Zelle:** zellunabhängig
- **Rollen:** HM GS TU · **XYZ-Anker:** 0,40 / 0,25 / 0,20 · **Gültigkeit:** X 0,20–0,60 · Y 0,05–0,45 · Z 0,00–0,40
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** –
- **Evidenz:** I – begründete Interpretation (None als Melodieton über Moll); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M002 – Terz-Seufzer mit Nachklang
- **Charakter:** verletzlich · **Säule:** A · **Typ:** Intervallmotiv · **Modus:** aeolisch · **Takt:** 4/4 · **Länge:** 2 Takte
- **Töne/Dauern:** +15/2880 +14/960 +12/3840
- **Intervalle:** -1, -2 · **Ambitus:** +12 bis +15 · **Zelle:** zellunabhängig
- **Rollen:** HM GS · **XYZ-Anker:** 0,35 / 0,25 / 0,20 · **Gültigkeit:** X 0,15–0,55 · Y 0,05–0,45 · Z 0,00–0,40
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** –
- **Evidenz:** I – begründete Interpretation (Reibung ♭3–2); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M003 – Aufsteigende Sehnsucht 5–1–2–♭3
- **Charakter:** Hoffnung im Moll · **Säule:** A · **Typ:** Intervallmotiv · **Modus:** aeolisch · **Takt:** 4/4 · **Länge:** 2 Takte
- **Töne/Dauern:** +7/960 +12/960 +14/1920 +15/3840
- **Intervalle:** +5, +2, +1 · **Ambitus:** +7 bis +15 · **Zelle:** EM-C010 (Töne ⊆ Zelle geprüft)
- **Rollen:** HM GS · **XYZ-Anker:** 0,45 / 0,35 / 0,20 · **Gültigkeit:** X 0,25–0,65 · Y 0,15–0,55 · Z 0,00–0,40
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H071, EM-H103
- **Evidenz:** E – eigenständige Gestaltung (Thema aus Intervallen); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M004 – Großer Sextaufschwung (Dur)
- **Charakter:** Weite, Verlangen · **Säule:** A · **Typ:** Intervallmotiv · **Modus:** ionisch · **Takt:** 4/4 · **Länge:** 2 Takte
- **Töne/Dauern:** +7/1920 +16/1920 +14/960 +12/960 +11/1920
- **Intervalle:** +9, -2, -2, -1 · **Ambitus:** +7 bis +16 · **Zelle:** zellunabhängig
- **Rollen:** HM · **XYZ-Anker:** 0,75 / 0,40 / 0,20 · **Gültigkeit:** X 0,55–0,95 · Y 0,20–0,60 · Z 0,00–0,40
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H016, EM-H017, EM-H018, EM-H019, EM-H020, EM-H021 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H001, EM-H002, EM-H003, EM-H004
- **Evidenz:** E – eigenständige Gestaltung (Intervallthema; Sexte (filmmusicnotes: Jill)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M005 – Quarte und Sekunde, offen endend
- **Charakter:** Aufbruch · **Säule:** A · **Typ:** Intervallmotiv · **Modus:** dorisch · **Takt:** 4/4 · **Länge:** 2 Takte
- **Töne/Dauern:** +12/1920 +17/960 +19/960 +19/3840
- **Intervalle:** +5, +2, +0 · **Ambitus:** +12 bis +19 · **Zelle:** EM-C040 (Töne ⊆ Zelle geprüft)
- **Rollen:** HM GS · **XYZ-Anker:** 0,55 / 0,40 / 0,25 · **Gültigkeit:** X 0,35–0,75 · Y 0,20–0,60 · Z 0,05–0,45
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H002, EM-H003, EM-H004, EM-H005, EM-H007, EM-H008 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H071, EM-H076, EM-H103
- **Evidenz:** E – eigenständige Gestaltung (Intervallzelle); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M006 – Kleinterz-Pendel
- **Charakter:** fragend · **Säule:** AB · **Typ:** Intervallmotiv · **Modus:** aeolisch · **Takt:** 4/4 · **Länge:** 1 Takte
- **Töne/Dauern:** +12/960 +15/960 +12/960 +15/960
- **Intervalle:** +3, -3, +3 · **Ambitus:** +12 bis +15 · **Zelle:** EM-C001 (Töne ⊆ Zelle geprüft)
- **Rollen:** TU AR GS · **XYZ-Anker:** 0,35 / 0,25 / 0,30 · **Gültigkeit:** X 0,15–0,55 · Y 0,05–0,45 · Z 0,10–0,50
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H016, EM-H017, EM-H018, EM-H019
- **Evidenz:** N – nachgewiesenes Verfahren (kleine Terz); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M007 – Tritonus-Ruf
- **Charakter:** unheilvoll · **Säule:** B · **Typ:** Intervallmotiv · **Modus:** chromatisch · **Takt:** 4/4 · **Länge:** 1 Takte
- **Töne/Dauern:** +12/1920 +18/1920
- **Intervalle:** +6 · **Ambitus:** +12 bis +18 · **Zelle:** EM-C005 (Töne ⊆ Zelle geprüft)
- **Rollen:** TU GS · **XYZ-Anker:** 0,15 / 0,30 / 0,50 · **Gültigkeit:** X 0,00–0,35 · Y 0,10–0,50 · Z 0,30–0,70
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H065, EM-H066, EM-H072, EM-H073, EM-H076, EM-H078 · **ungeeignet (≥ 2 modusfremde Töne):** –
- **Evidenz:** N – nachgewiesenes Verfahren (Tritonus); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M008 – Halbton-Wechselnote
- **Charakter:** Zweifel · **Säule:** B · **Typ:** Intervallmotiv · **Modus:** chromatisch · **Takt:** 4/4 · **Länge:** 1 Takte
- **Töne/Dauern:** +12/960 +13/960 +12/1920
- **Intervalle:** +1, -1 · **Ambitus:** +12 bis +13 · **Zelle:** EM-C004 (Töne ⊆ Zelle geprüft)
- **Rollen:** TU GS · **XYZ-Anker:** 0,20 / 0,25 / 0,45 · **Gültigkeit:** X 0,00–0,40 · Y 0,05–0,45 · Z 0,25–0,65
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002, EM-T017 nur Y-gekoppelt
- **Geeignete Harmonik:** EM-H042, EM-H065, EM-H066, EM-H068, EM-H072, EM-H073 · **ungeeignet (≥ 2 modusfremde Töne):** –
- **Evidenz:** N – nachgewiesenes Verfahren (Halbton); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M009 – Kleine-Sexte-Glocke
- **Charakter:** klagende Glocke · **Säule:** AB · **Typ:** Intervallmotiv · **Modus:** aeolisch · **Takt:** 4/4 · **Länge:** 1 Takte
- **Töne/Dauern:** +12/1920 +20/1920
- **Intervalle:** +8 · **Ambitus:** +12 bis +20 · **Zelle:** EM-C030 (Töne ⊆ Zelle geprüft)
- **Rollen:** TU GS · **XYZ-Anker:** 0,40 / 0,20 / 0,30 · **Gültigkeit:** X 0,20–0,60 · Y 0,00–0,40 · Z 0,10–0,50
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** –
- **Evidenz:** N – nachgewiesenes Verfahren (kleine Sexte repetiert (Bissett)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M010 – Quintfall mit Nachschlag
- **Charakter:** würdig · **Säule:** A · **Typ:** Intervallmotiv · **Modus:** dorisch · **Takt:** 4/4 · **Länge:** 1 Takte
- **Töne/Dauern:** +19/2880 +12/960
- **Intervalle:** -7 · **Ambitus:** +12 bis +19 · **Zelle:** EM-C011 (Töne ⊆ Zelle geprüft)
- **Rollen:** HM KF · **XYZ-Anker:** 0,50 / 0,55 / 0,20 · **Gültigkeit:** X 0,30–0,70 · Y 0,35–0,75 · Z 0,00–0,40
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** –
- **Evidenz:** E – eigenständige Gestaltung (Quinte); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M011 – Gesangliche Moll-Linie über acht Takte
- **Charakter:** lyrische Melancholie · **Säule:** A · **Typ:** Bogen · **Modus:** aeolisch · **Takt:** 4/4 · **Länge:** 8 Takte
- **Töne/Dauern:** +12/1920 +14/960 +15/960 +17/2880 +15/960 +14/1920 +12/960 +10/960 +12/3840 +15/1920 +17/960 +19/960 +20/2880 +19/960 +17/1920 +15/960 +14/960 +14/3840
- **Intervalle:** +2, +1, +2, -2, -1, -2, -2, +2, +3, +2, +2, +1, -1, -2, -2, -1, +0 · **Ambitus:** +10 bis +20 · **Zelle:** zellunabhängig
- **Rollen:** HM · **XYZ-Anker:** 0,40 / 0,35 / 0,20 · **Gültigkeit:** X 0,20–0,60 · Y 0,15–0,55 · Z 0,00–0,40
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H016, EM-H017, EM-H018, EM-H019
- **Evidenz:** E – eigenständige Gestaltung (lange Linie, Wiederkehr mit Erweiterung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M012 – Dur-Bogen mit verzögertem Höhepunkt
- **Charakter:** zärtliche Erfüllung · **Säule:** A · **Typ:** Bogen · **Modus:** ionisch · **Takt:** 4/4 · **Länge:** 8 Takte
- **Töne/Dauern:** +16/1920 +14/960 +12/960 +14/3840 +16/1920 +17/960 +19/960 +21/2880 +19/960 +17/1920 +16/960 +14/960 +16/1920 +19/1920 +24/2880 +21/960 +19/3840
- **Intervalle:** -2, -2, +2, +2, +1, +2, +2, -2, -2, -1, -2, +2, +3, +5, -3, -2 · **Ambitus:** +12 bis +24 · **Zelle:** zellunabhängig
- **Rollen:** HM · **XYZ-Anker:** 0,75 / 0,40 / 0,20 · **Gültigkeit:** X 0,55–0,95 · Y 0,20–0,60 · Z 0,00–0,40
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H016, EM-H017, EM-H018, EM-H019, EM-H020, EM-H022 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H001, EM-H002, EM-H003, EM-H004
- **Evidenz:** E – eigenständige Gestaltung (verzögerter Höhepunkt); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M013 – Dorischer Erzählbogen
- **Charakter:** herbe Erzählung · **Säule:** A · **Typ:** Bogen · **Modus:** dorisch · **Takt:** 4/4 · **Länge:** 8 Takte
- **Töne/Dauern:** +12/1440 +14/480 +15/1920 +21/1920 +19/1920 +17/960 +15/960 +14/1920 +12/3840 +14/1440 +15/480 +17/1920 +21/960 +22/960 +21/1920 +19/1920 +17/1920 +19/3840
- **Intervalle:** +2, +1, +6, -2, -2, -2, -1, -2, +2, +1, +2, +4, +1, -1, -2, -2, +2 · **Ambitus:** +12 bis +22 · **Zelle:** zellunabhängig
- **Rollen:** HM · **XYZ-Anker:** 0,55 / 0,40 / 0,25 · **Gültigkeit:** X 0,35–0,75 · Y 0,20–0,60 · Z 0,05–0,45
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H007, EM-H008, EM-H013, EM-H022, EM-H023, EM-H024 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H001, EM-H002, EM-H003, EM-H004
- **Evidenz:** E – eigenständige Gestaltung (dorische Sexte als Farbe); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M014 – Weit gespannte Klage
- **Charakter:** tragisch · **Säule:** A · **Typ:** Bogen · **Modus:** harm_moll · **Takt:** 4/4 · **Länge:** 8 Takte
- **Töne/Dauern:** +24/3840 +23/1920 +20/1920 +22/1920 +20/960 +19/960 +17/3840 +15/1920 +14/1920 +12/1920 +11/1920 +12/7680
- **Intervalle:** -1, -3, +2, -2, -1, -2, -2, -1, -2, -1, +1 · **Ambitus:** +11 bis +24 · **Zelle:** zellunabhängig
- **Rollen:** HM GS · **XYZ-Anker:** 0,25 / 0,60 / 0,30 · **Gültigkeit:** X 0,05–0,45 · Y 0,40–0,80 · Z 0,10–0,50
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H024, EM-H052, EM-H065, EM-H066, EM-H073, EM-H074 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H001, EM-H002, EM-H003, EM-H004
- **Evidenz:** E – eigenständige Gestaltung (langsame Linie, chromatisch gefärbt); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M015 – Atmende Linie mit Pausen
- **Charakter:** dialogfreundlich lyrisch · **Säule:** A · **Typ:** Bogen · **Modus:** aeolisch · **Takt:** 4/4 · **Länge:** 6 Takte
- **Töne/Dauern:** +15/1920 +14/1920 +12/3840 Pause/3840 +14/1920 +15/1920 +19/3840 Pause/3840
- **Intervalle:** -1, -2, +2, +1, +4 · **Ambitus:** +12 bis +19 · **Zelle:** zellunabhängig
- **Rollen:** HM TU · **XYZ-Anker:** 0,45 / 0,20 / 0,20 · **Gültigkeit:** X 0,25–0,65 · Y 0,00–0,40 · Z 0,00–0,40
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H016, EM-H017, EM-H018, EM-H019
- **Evidenz:** E – eigenständige Gestaltung (Leerraum zwischen Phrasen); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M016 – Lydische Schwebelinie
- **Charakter:** kalt-hell · **Säule:** A · **Typ:** Bogen · **Modus:** lydisch · **Takt:** 4/4 · **Länge:** 4 Takte
- **Töne/Dauern:** +19/1920 +18/1920 +16/3840 +14/1920 +16/1920 +18/3840
- **Intervalle:** -1, -2, -2, +2, +2 · **Ambitus:** +14 bis +19 · **Zelle:** zellunabhängig
- **Rollen:** HM GS · **XYZ-Anker:** 0,90 / 0,25 / 0,20 · **Gültigkeit:** X 0,70–1,00 · Y 0,05–0,45 · Z 0,00–0,40
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H021, EM-H083, EM-H098, EM-H115, EM-H119 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H001, EM-H002, EM-H003, EM-H004
- **Evidenz:** E – eigenständige Gestaltung (lydische Quarte); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M017 – Dur-Moll-Schatten in der Linie
- **Charakter:** Freude wird zweifelhaft · **Säule:** A · **Typ:** Bogen · **Modus:** dur_moll_gemischt · **Takt:** 4/4 · **Länge:** 4 Takte
- **Töne/Dauern:** +16/1920 +19/1920 +21/1920 +19/960 +16/960 +15/3840 +14/1920 +12/1920
- **Intervalle:** +3, +2, -2, -3, -1, -1, -2 · **Ambitus:** +12 bis +21 · **Zelle:** zellunabhängig
- **Rollen:** HM · **XYZ-Anker:** 0,60 / 0,30 / 0,30 · **Gültigkeit:** X 0,40–0,80 · Y 0,10–0,50 · Z 0,10–0,50
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H022, EM-H023, EM-H024, EM-H030, EM-H046, EM-H047 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H001, EM-H002, EM-H003, EM-H004
- **Evidenz:** E – eigenständige Gestaltung (Dur/Moll-Wechsel in der Melodie); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M018 – Hymnische Breite
- **Charakter:** monumental, gefasst · **Säule:** A · **Typ:** Bogen · **Modus:** ionisch · **Takt:** 4/4 · **Länge:** 8 Takte
- **Töne/Dauern:** +12/3840 +19/1920 +17/1920 +16/1920 +14/1920 +16/3840 +21/3840 +19/1920 +17/1920 +16/1920 +14/1920 +12/3840
- **Intervalle:** +7, -2, -1, -2, +2, +5, -2, -2, -1, -2, -2 · **Ambitus:** +12 bis +21 · **Zelle:** zellunabhängig
- **Rollen:** HM KF · **XYZ-Anker:** 0,70 / 0,80 / 0,15 · **Gültigkeit:** X 0,50–0,90 · Y 0,60–1,00 · Z 0,00–0,35
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H016, EM-H017, EM-H018, EM-H019, EM-H020, EM-H022 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H001, EM-H002, EM-H003, EM-H004
- **Evidenz:** E – eigenständige Gestaltung (Monumentalität durch Dauer); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M019 – Fragment: zwei Töne Sehnsucht
- **Charakter:** Erinnerungssplitter · **Säule:** A · **Typ:** Fragment · **Modus:** aeolisch · **Takt:** 4/4 · **Länge:** 1 Takte
- **Töne/Dauern:** +14/960 +15/2880
- **Intervalle:** +1 · **Ambitus:** +14 bis +15 · **Zelle:** EM-C009 (Töne ⊆ Zelle geprüft)
- **Rollen:** TU GS · **XYZ-Anker:** 0,40 / 0,15 / 0,30 · **Gültigkeit:** X 0,20–0,60 · Y 0,00–0,35 · Z 0,10–0,50
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** –
- **Evidenz:** I – begründete Interpretation (Motivfragmentierung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M020 – Fragment: fallende Terz
- **Charakter:** Resignation · **Säule:** A · **Typ:** Fragment · **Modus:** aeolisch · **Takt:** 4/4 · **Länge:** 1 Takte
- **Töne/Dauern:** +15/1920 +12/1920
- **Intervalle:** -3 · **Ambitus:** +12 bis +15 · **Zelle:** zellunabhängig
- **Rollen:** TU GS · **XYZ-Anker:** 0,35 / 0,15 / 0,25 · **Gültigkeit:** X 0,15–0,55 · Y 0,00–0,35 · Z 0,05–0,45
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** –
- **Evidenz:** I – begründete Interpretation (Fragment); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M021 – Fragment: Vorhalt ohne Auflösung
- **Charakter:** unvollendet · **Säule:** A · **Typ:** Fragment · **Modus:** aeolisch · **Takt:** 4/4 · **Länge:** 1 Takte
- **Töne/Dauern:** +17/3840
- **Intervalle:**  · **Ambitus:** +17 bis +17 · **Zelle:** zellunabhängig
- **Rollen:** TU GS · **XYZ-Anker:** 0,30 / 0,20 / 0,40 · **Gültigkeit:** X 0,10–0,50 · Y 0,00–0,40 · Z 0,20–0,60
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** –
- **Evidenz:** E – eigenständige Gestaltung (unaufgelöster Vorhalt (U)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M022 – Fragment: Doppelton-Echo
- **Charakter:** Nachhall · **Säule:** AB · **Typ:** Fragment · **Modus:** aeolisch · **Takt:** 4/4 · **Länge:** 1 Takte
- **Töne/Dauern:** +19/480 Pause/480 +19/480 Pause/480 Pause/1920
- **Intervalle:** +0 · **Ambitus:** +19 bis +19 · **Zelle:** zellunabhängig
- **Rollen:** TU · **XYZ-Anker:** 0,40 / 0,20 / 0,35 · **Gültigkeit:** X 0,20–0,60 · Y 0,00–0,40 · Z 0,15–0,55
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H071, EM-H076, EM-H103
- **Evidenz:** I – begründete Interpretation (Echo); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M023 – Frage (offen auf 5)
- **Charakter:** fragend · **Säule:** A · **Typ:** Frage · **Modus:** aeolisch · **Takt:** 4/4 · **Länge:** 2 Takte
- **Töne/Dauern:** +12/960 +14/960 +15/960 +17/960 +19/3840
- **Intervalle:** +2, +1, +2, +2 · **Ambitus:** +12 bis +19 · **Zelle:** zellunabhängig
- **Rollen:** HM GS · **XYZ-Anker:** 0,45 / 0,30 / 0,30 · **Gültigkeit:** X 0,25–0,65 · Y 0,10–0,50 · Z 0,10–0,50
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H021, EM-H026, EM-H069, EM-H071
- **Evidenz:** E – eigenständige Gestaltung (Frage-Antwort (GINC-Gesprächslogik)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M024 – Antwort (zurück auf 1)
- **Charakter:** antwortend · **Säule:** A · **Typ:** Antwort · **Modus:** aeolisch · **Takt:** 4/4 · **Länge:** 2 Takte
- **Töne/Dauern:** +17/960 +15/960 +14/960 +15/960 +12/3840
- **Intervalle:** -2, -1, +1, -3 · **Ambitus:** +12 bis +17 · **Zelle:** zellunabhängig
- **Rollen:** GS HM · **XYZ-Anker:** 0,45 / 0,30 / 0,20 · **Gültigkeit:** X 0,25–0,65 · Y 0,10–0,50 · Z 0,00–0,40
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H016, EM-H017, EM-H018, EM-H019
- **Evidenz:** E – eigenständige Gestaltung (Antwort); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M025 – Frage im Dur (offen auf 2)
- **Charakter:** zögernd hoffend · **Säule:** A · **Typ:** Frage · **Modus:** ionisch · **Takt:** 4/4 · **Länge:** 2 Takte
- **Töne/Dauern:** +16/1920 +19/960 +21/960 +14/3840
- **Intervalle:** +3, +2, -7 · **Ambitus:** +14 bis +21 · **Zelle:** zellunabhängig
- **Rollen:** HM · **XYZ-Anker:** 0,75 / 0,30 / 0,30 · **Gültigkeit:** X 0,55–0,95 · Y 0,10–0,50 · Z 0,10–0,50
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H016, EM-H017, EM-H018, EM-H019, EM-H020, EM-H021 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H001, EM-H002, EM-H003, EM-H004
- **Evidenz:** E – eigenständige Gestaltung (Frage); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M026 – Antwort im Dur (Terz)
- **Charakter:** tröstend · **Säule:** A · **Typ:** Antwort · **Modus:** ionisch · **Takt:** 4/4 · **Länge:** 2 Takte
- **Töne/Dauern:** +17/1920 +16/960 +14/960 +16/3840
- **Intervalle:** -1, -2, +2 · **Ambitus:** +14 bis +17 · **Zelle:** zellunabhängig
- **Rollen:** HM GS · **XYZ-Anker:** 0,75 / 0,30 / 0,20 · **Gültigkeit:** X 0,55–0,95 · Y 0,10–0,50 · Z 0,00–0,40
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H016, EM-H017, EM-H018, EM-H019, EM-H020, EM-H022 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H001, EM-H002, EM-H003, EM-H004
- **Evidenz:** E – eigenständige Gestaltung (Antwort); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M027 – Widersprechende Antwort (chromatisch)
- **Charakter:** Einspruch · **Säule:** B · **Typ:** Antwort · **Modus:** chromatisch · **Takt:** 4/4 · **Länge:** 2 Takte
- **Töne/Dauern:** +18/960 +13/960 +12/1920 +13/1920 +12/1920
- **Intervalle:** -5, -1, +1, -1 · **Ambitus:** +12 bis +18 · **Zelle:** EM-C015 (Töne ⊆ Zelle geprüft)
- **Rollen:** GS TU · **XYZ-Anker:** 0,25 / 0,35 / 0,55 · **Gültigkeit:** X 0,05–0,45 · Y 0,15–0,55 · Z 0,35–0,75
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H065, EM-H066, EM-H072, EM-H073, EM-H074, EM-H078 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H001, EM-H002, EM-H003, EM-H004
- **Evidenz:** N – nachgewiesenes Verfahren (Widerspruch (GINC: disagree in sound)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M028 – Gegenmotiv in Vierteln gegen lange Linie
- **Charakter:** bewegte Begleitstimme · **Säule:** A · **Typ:** Gegenmotiv · **Modus:** aeolisch · **Takt:** 4/4 · **Länge:** 4 Takte
- **Töne/Dauern:** +3/960 +5/960 +7/960 +8/960 +7/960 +5/960 +3/960 +2/960 +0/960 +2/960 +3/960 +7/960 +5/3840
- **Intervalle:** +2, +2, +1, -1, -2, -2, -1, -2, +2, +1, +4, -2 · **Ambitus:** +0 bis +8 · **Zelle:** zellunabhängig
- **Rollen:** GS · **XYZ-Anker:** 0,40 / 0,40 / 0,30 · **Gültigkeit:** X 0,20–0,60 · Y 0,20–0,60 · Z 0,10–0,50
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H016, EM-H017, EM-H018, EM-H019
- **Evidenz:** N – nachgewiesenes Verfahren (rhythmisch komplementärer Kontrapunkt (Mission, Movie Music UK)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M029 – Gegenmotiv in Halben (langsam gegen bewegte Oberstimme)
- **Charakter:** ruhender Gegenpol · **Säule:** A · **Typ:** Gegenmotiv · **Modus:** aeolisch · **Takt:** 4/4 · **Länge:** 4 Takte
- **Töne/Dauern:** +7/1920 +8/1920 +7/1920 +5/1920 +3/1920 +2/1920 +3/3840
- **Intervalle:** +1, -1, -2, -2, -1, +1 · **Ambitus:** +2 bis +8 · **Zelle:** zellunabhängig
- **Rollen:** GS · **XYZ-Anker:** 0,35 / 0,35 / 0,20 · **Gültigkeit:** X 0,15–0,55 · Y 0,15–0,55 · Z 0,00–0,40
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H016, EM-H017, EM-H018, EM-H019
- **Evidenz:** I – begründete Interpretation (Komplementärregel); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M030 – Chorartiges Gegenmotiv (Quarten)
- **Charakter:** sakral, fremd · **Säule:** AB · **Typ:** Gegenmotiv · **Modus:** dorisch · **Takt:** 4/4 · **Länge:** 3 Takte
- **Töne/Dauern:** +5/1920 +10/1920 +9/1920 +5/1920 +3/3840
- **Intervalle:** +5, -1, -4, -2 · **Ambitus:** +3 bis +10 · **Zelle:** zellunabhängig
- **Rollen:** GS LF · **XYZ-Anker:** 0,50 / 0,40 / 0,30 · **Gültigkeit:** X 0,30–0,70 · Y 0,20–0,60 · Z 0,10–0,50
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H007, EM-H008, EM-H013, EM-H022, EM-H023, EM-H024 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H011, EM-H016, EM-H017, EM-H018
- **Evidenz:** I – begründete Interpretation (Chor als zweites Modul (Miceli: Mission)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M031 – Additives Motiv Stufe 1 (2 Töne)
- **Charakter:** Ankündigung · **Säule:** AB · **Typ:** Additiv · **Modus:** aeolisch · **Takt:** 4/4 · **Länge:** 1 Takte
- **Töne/Dauern:** +19/960 +17/960 Pause/1920
- **Intervalle:** -2 · **Ambitus:** +17 bis +19 · **Zelle:** zellunabhängig
- **Rollen:** TU HM · **XYZ-Anker:** 0,35 / 0,40 / 0,35 · **Gültigkeit:** X 0,15–0,55 · Y 0,20–0,60 · Z 0,15–0,55
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002, EM-T005 (additive Stufen)
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H071, EM-H103
- **Evidenz:** N – nachgewiesenes Verfahren (additive Enthüllung (Filmtracks: Nitti)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M032 – Additives Motiv Stufe 2 (4 Töne)
- **Charakter:** Annäherung · **Säule:** AB · **Typ:** Additiv · **Modus:** aeolisch · **Takt:** 4/4 · **Länge:** 1 Takte
- **Töne/Dauern:** +19/960 +17/960 +15/960 +14/960
- **Intervalle:** -2, -2, -1 · **Ambitus:** +14 bis +19 · **Zelle:** zellunabhängig
- **Rollen:** TU HM · **XYZ-Anker:** 0,35 / 0,45 / 0,40 · **Gültigkeit:** X 0,15–0,55 · Y 0,25–0,65 · Z 0,20–0,60
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002, EM-T005 (additive Stufen)
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H021, EM-H026, EM-H069, EM-H071
- **Evidenz:** N – nachgewiesenes Verfahren (additive Enthüllung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M033 – Additives Motiv Stufe 3 (7 Töne)
- **Charakter:** Gestalt wird sichtbar · **Säule:** AB · **Typ:** Additiv · **Modus:** aeolisch · **Takt:** 4/4 · **Länge:** 2 Takte
- **Töne/Dauern:** +19/960 +17/960 +15/960 +14/960 +15/960 +12/960 +10/1920
- **Intervalle:** -2, -2, -1, +1, -3, -2 · **Ambitus:** +10 bis +19 · **Zelle:** zellunabhängig
- **Rollen:** TU HM · **XYZ-Anker:** 0,35 / 0,50 / 0,40 · **Gültigkeit:** X 0,15–0,55 · Y 0,30–0,70 · Z 0,20–0,60
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002, EM-T005 (additive Stufen)
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H016, EM-H017, EM-H018, EM-H019
- **Evidenz:** N – nachgewiesenes Verfahren (additive Enthüllung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M034 – Additives Motiv Stufe 4 (10 Töne)
- **Charakter:** vollständige Gestalt · **Säule:** AB · **Typ:** Additiv · **Modus:** aeolisch · **Takt:** 4/4 · **Länge:** 3 Takte
- **Töne/Dauern:** +19/960 +17/960 +15/960 +14/960 +15/960 +12/960 +10/960 +12/960 +14/1920 +7/1920
- **Intervalle:** -2, -2, -1, +1, -3, -2, +2, +2, -7 · **Ambitus:** +7 bis +19 · **Zelle:** zellunabhängig
- **Rollen:** HM · **XYZ-Anker:** 0,35 / 0,55 / 0,40 · **Gültigkeit:** X 0,15–0,55 · Y 0,35–0,75 · Z 0,20–0,60
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002, EM-T005 (additive Stufen)
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H016, EM-H017, EM-H018, EM-H019
- **Evidenz:** N – nachgewiesenes Verfahren (additive Enthüllung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M035 – Wandermotiv tief (Ausgangslage)
- **Charakter:** verborgen · **Säule:** A · **Typ:** Wanderung · **Modus:** aeolisch · **Takt:** 4/4 · **Länge:** 2 Takte
- **Töne/Dauern:** +0/1920 +2/960 +3/960 +7/3840
- **Intervalle:** +2, +1, +4 · **Ambitus:** +0 bis +7 · **Zelle:** EM-C010 (Töne ⊆ Zelle geprüft)
- **Rollen:** GS TU KB · **XYZ-Anker:** 0,35 / 0,20 / 0,20 · **Gültigkeit:** X 0,15–0,55 · Y 0,00–0,40 · Z 0,00–0,40
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H071, EM-H103
- **Evidenz:** N – nachgewiesenes Verfahren (Registerwanderung (OUP-Blog: von einer Stimme zum Orchester)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M036 – Wandermotiv hoch (Zielregister)
- **Charakter:** offenbart · **Säule:** A · **Typ:** Wanderung · **Modus:** aeolisch · **Takt:** 4/4 · **Länge:** 2 Takte
- **Töne/Dauern:** +24/1920 +26/960 +27/960 +31/3840
- **Intervalle:** +2, +1, +4 · **Ambitus:** +24 bis +31 · **Zelle:** EM-C010 (Töne ⊆ Zelle geprüft)
- **Rollen:** HM · **XYZ-Anker:** 0,40 / 0,60 / 0,20 · **Gültigkeit:** X 0,20–0,60 · Y 0,40–0,80 · Z 0,00–0,40
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H071, EM-H103
- **Evidenz:** N – nachgewiesenes Verfahren (Registerwanderung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M037 – Verzögerte Erfüllung (Halteton vor dem Ziel)
- **Charakter:** Warten auf das Licht · **Säule:** A · **Typ:** Bogen · **Modus:** ionisch · **Takt:** 4/4 · **Länge:** 6 Takte
- **Töne/Dauern:** +12/960 +14/960 +16/960 +17/960 +19/3840 +19/1920 +21/1920 +21/3840 +24/7680
- **Intervalle:** +2, +2, +1, +2, +0, +2, +0, +3 · **Ambitus:** +12 bis +24 · **Zelle:** zellunabhängig
- **Rollen:** HM · **XYZ-Anker:** 0,75 / 0,45 / 0,30 · **Gültigkeit:** X 0,55–0,95 · Y 0,25–0,65 · Z 0,10–0,50
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H016, EM-H017, EM-H018, EM-H019, EM-H020, EM-H022 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H001, EM-H002, EM-H003, EM-H004
- **Evidenz:** E – eigenständige Gestaltung (verzögerter Höhepunkt); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M038 – Erwartung ohne Erfüllung
- **Charakter:** Hoffnung verweht · **Säule:** A · **Typ:** Bogen · **Modus:** aeolisch · **Takt:** 4/4 · **Länge:** 4 Takte
- **Töne/Dauern:** +12/960 +14/960 +15/960 +17/960 +19/3840 +20/1920 +19/1920 +17/3840
- **Intervalle:** +2, +1, +2, +2, +1, -1, -2 · **Ambitus:** +12 bis +20 · **Zelle:** zellunabhängig
- **Rollen:** HM · **XYZ-Anker:** 0,35 / 0,35 / 0,40 · **Gültigkeit:** X 0,15–0,55 · Y 0,15–0,55 · Z 0,20–0,60
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H016, EM-H017, EM-H018, EM-H019
- **Evidenz:** E – eigenständige Gestaltung (Zielton bleibt aus); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M039 – Zellmelodie Sus2 (drei Töne, drei Lagen)
- **Charakter:** schlicht, immer gleich · **Säule:** A · **Typ:** Zellmotiv · **Modus:** ionisch · **Takt:** 4/4 · **Länge:** 2 Takte
- **Töne/Dauern:** +12/1920 +14/960 +19/960 +14/3840
- **Intervalle:** +2, +5, -5 · **Ambitus:** +12 bis +19 · **Zelle:** EM-C007 (Töne ⊆ Zelle geprüft)
- **Rollen:** HM AR TU · **XYZ-Anker:** 0,65 / 0,30 / 0,20 · **Gültigkeit:** X 0,45–0,85 · Y 0,10–0,50 · Z 0,00–0,40
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H002, EM-H004, EM-H007, EM-H008, EM-H009, EM-H010 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H042, EM-H068, EM-H069, EM-H070
- **Evidenz:** N – nachgewiesenes Verfahren (Mikrozelle); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M040 – Zellmelodie pentatonisch
- **Charakter:** einfach, nicht naiv · **Säule:** A · **Typ:** Zellmotiv · **Modus:** pentaton_dur · **Takt:** 4/4 · **Länge:** 2 Takte
- **Töne/Dauern:** +16/960 +14/960 +12/1920 +19/960 +16/960 +14/1920
- **Intervalle:** -2, -2, +7, -3, -2 · **Ambitus:** +12 bis +19 · **Zelle:** EM-C029 (Töne ⊆ Zelle geprüft)
- **Rollen:** HM AR · **XYZ-Anker:** 0,75 / 0,30 / 0,20 · **Gültigkeit:** X 0,55–0,95 · Y 0,10–0,50 · Z 0,00–0,40
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H016, EM-H017, EM-H018, EM-H019, EM-H020, EM-H021 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H001, EM-H002, EM-H003, EM-H004
- **Evidenz:** N – nachgewiesenes Verfahren (Mikrozelle); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M041 – B-A-C-H-Linie (gestreckt)
- **Charakter:** verschlüsselte Strenge · **Säule:** B · **Typ:** Zellmotiv · **Modus:** chromatisch · **Takt:** 4/4 · **Länge:** 2 Takte
- **Töne/Dauern:** +22/1920 +21/1920 +24/1920 +23/1920
- **Intervalle:** -1, +3, -1 · **Ambitus:** +21 bis +24 · **Zelle:** EM-C022 (Töne ⊆ Zelle geprüft)
- **Rollen:** GS TU · **XYZ-Anker:** 0,40 / 0,30 / 0,40 · **Gültigkeit:** X 0,20–0,60 · Y 0,10–0,50 · Z 0,20–0,60
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H023, EM-H024, EM-H030, EM-H046, EM-H047, EM-H052 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H001, EM-H002, EM-H003, EM-H004
- **Evidenz:** N – nachgewiesenes Verfahren (Tonbuchstaben-Kode); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M042 – Pseudoserielle Linie
- **Charakter:** kalte Logik · **Säule:** B · **Typ:** Zellmotiv · **Modus:** chromatisch · **Takt:** 4/4 · **Länge:** 2 Takte
- **Töne/Dauern:** +12/960 +13/960 +16/1920 +17/960 +18/960 +21/960 +23/960
- **Intervalle:** +1, +3, +1, +1, +3, +2 · **Ambitus:** +12 bis +23 · **Zelle:** EM-C035 (Töne ⊆ Zelle geprüft)
- **Rollen:** GS TU · **XYZ-Anker:** 0,40 / 0,35 / 0,50 · **Gültigkeit:** X 0,20–0,60 · Y 0,15–0,55 · Z 0,30–0,70
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H065, EM-H067, EM-H073, EM-H074, EM-H078, EM-H080 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H001, EM-H002, EM-H003, EM-H004
- **Evidenz:** N – nachgewiesenes Verfahren (pseudoseriell); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M043 – Wiegenlied-Zelle (Spieluhr)
- **Charakter:** verstörende Unschuld · **Säule:** AB · **Typ:** Zellmotiv · **Modus:** ionisch · **Takt:** 4/4 · **Länge:** 1 Takte
- **Töne/Dauern:** +19/480 +16/480 +19/480 +16/480 +21/480 +19/480 +16/960
- **Intervalle:** -3, +3, -3, +5, -2, -3 · **Ambitus:** +16 bis +21 · **Zelle:** EM-C029 (Töne ⊆ Zelle geprüft)
- **Rollen:** AR TU · **XYZ-Anker:** 0,80 / 0,20 / 0,30 · **Gültigkeit:** X 0,60–1,00 · Y 0,00–0,40 · Z 0,10–0,50
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H016, EM-H017, EM-H018, EM-H019, EM-H020, EM-H021 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H001, EM-H002, EM-H003, EM-H004
- **Evidenz:** N – nachgewiesenes Verfahren (kindliche Themen in atonalem Umfeld (De Rosa)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M044 – Wiegenlied-Zelle 3/4
- **Charakter:** Walzer der Unschuld · **Säule:** AB · **Typ:** Zellmotiv · **Modus:** ionisch · **Takt:** 3/4 · **Länge:** 2 Takte
- **Töne/Dauern:** +24/960 +19/960 +21/960 +19/2880
- **Intervalle:** -5, +2, -2 · **Ambitus:** +19 bis +24 · **Zelle:** EM-C031 (Töne ⊆ Zelle geprüft)
- **Rollen:** AR TU · **XYZ-Anker:** 0,80 / 0,20 / 0,30 · **Gültigkeit:** X 0,60–1,00 · Y 0,00–0,40 · Z 0,10–0,50
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H007, EM-H008, EM-H016, EM-H017, EM-H018, EM-H019 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H071, EM-H076, EM-H103
- **Evidenz:** N – nachgewiesenes Verfahren (Spieluhr); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M045 – Langsame Oberstimme über Pulsboden
- **Charakter:** unbeirrbar · **Säule:** B · **Typ:** Bogen · **Modus:** aeolisch · **Takt:** 4/4 · **Länge:** 6 Takte
- **Töne/Dauern:** +19/7680 +17/3840 +15/3840 +14/7680
- **Intervalle:** -2, -2, -1 · **Ambitus:** +14 bis +19 · **Zelle:** zellunabhängig
- **Rollen:** HM GS · **XYZ-Anker:** 0,35 / 0,80 / 0,35 · **Gültigkeit:** X 0,15–0,55 · Y 0,60–1,00 · Z 0,15–0,55
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H021, EM-H026, EM-H069, EM-H071
- **Evidenz:** I – begründete Interpretation (langsame Mundharmonika gegen treibenden Boden (NPR)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M046 – Kraftvoll-ruhige Signallinie
- **Charakter:** entschlossen, nicht hektisch · **Säule:** B · **Typ:** Bogen · **Modus:** dorisch · **Takt:** 4/4 · **Länge:** 3 Takte
- **Töne/Dauern:** +12/2880 +19/960 +17/1920 +15/1920 +14/3840
- **Intervalle:** +7, -2, -2, -1 · **Ambitus:** +12 bis +19 · **Zelle:** zellunabhängig
- **Rollen:** HM KF · **XYZ-Anker:** 0,45 / 0,85 / 0,30 · **Gültigkeit:** X 0,25–0,65 · Y 0,65–1,00 · Z 0,10–0,50
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H021, EM-H026, EM-H069, EM-H071
- **Evidenz:** E – eigenständige Gestaltung (Kraft ohne Hektik); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M047 – Fallende Chromatiklinie (Halbtonrückung-fähig)
- **Charakter:** Unentrinnbarkeit · **Säule:** AB · **Typ:** Bogen · **Modus:** chromatisch · **Takt:** 4/4 · **Länge:** 3 Takte
- **Töne/Dauern:** +19/1920 +18/1920 +17/1920 +16/1920 +15/3840
- **Intervalle:** -1, -1, -1, -1 · **Ambitus:** +15 bis +19 · **Zelle:** zellunabhängig
- **Rollen:** GS HM · **XYZ-Anker:** 0,25 / 0,50 / 0,50 · **Gültigkeit:** X 0,05–0,45 · Y 0,30–0,70 · Z 0,30–0,70
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002, EM-T017 nur Y-gekoppelt
- **Geeignete Harmonik:** EM-H065, EM-H066, EM-H073, EM-H074, EM-H078, EM-H080 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H001, EM-H002, EM-H003, EM-H004
- **Evidenz:** N – nachgewiesenes Verfahren (langsam bewegte chromatische Melodie (Wilcox: Vuoto d'anima piena)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M048 – Sechzehn-Takt-Linie mit B-Teil-Verdichtung
- **Charakter:** lyrische Entwicklung · **Säule:** A · **Typ:** Bogen · **Modus:** ionisch · **Takt:** 4/4 · **Länge:** 16 Takte
- **Töne/Dauern:** +16/3840 +14/1920 +12/1920 +14/1920 +16/1920 +19/3840 +21/3840 +19/1920 +17/1920 +16/1920 +14/1920 +16/3840 +21/1920 +23/960 +24/960 +26/960 +24/960 +23/960 +21/960 +24/3840 +23/1920 +21/1920 +19/3840 +17/1920 +16/1920 +14/1920 +12/1920 +12/3840
- **Intervalle:** -2, -2, +2, +2, +3, +2, -2, -2, -1, -2, +2, +5, +2, +1, +2, -2, -1, -2, +3, -1, -2, -2, -2, -1, -2, -2, +0 · **Ambitus:** +12 bis +26 · **Zelle:** zellunabhängig
- **Rollen:** HM · **XYZ-Anker:** 0,75 / 0,45 / 0,25 · **Gültigkeit:** X 0,55–0,95 · Y 0,25–0,65 · Z 0,05–0,45
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H016, EM-H017, EM-H018, EM-H019, EM-H020, EM-H022 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H001, EM-H002, EM-H003, EM-H004
- **Evidenz:** I – begründete Interpretation (verdichteter B-Teil (italianpiano, Blog-Analyse)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M049 – Gegenmotiv Achteltriolen (ternär)
- **Charakter:** sinnliche Bewegung · **Säule:** A · **Typ:** Gegenmotiv · **Modus:** dorisch · **Takt:** 4/4 · **Länge:** 1 Takte
- **Töne/Dauern:** +12/320 +14/320 +15/320 +17/320 +15/320 +14/320 +12/1920
- **Intervalle:** +2, +1, +2, -2, -1, -2 · **Ambitus:** +12 bis +17 · **Zelle:** zellunabhängig
- **Rollen:** GS AR · **XYZ-Anker:** 0,50 / 0,35 / 0,30 · **Gültigkeit:** X 0,30–0,70 · Y 0,15–0,55 · Z 0,10–0,50
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H016, EM-H017, EM-H018, EM-H019
- **Evidenz:** N – nachgewiesenes Verfahren (ternärer Rhythmus (Morricone zu Indagine)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-M050 – Monumentaler Ruf in Oktaven
- **Charakter:** tragische Größe · **Säule:** A · **Typ:** Bogen · **Modus:** aeolisch · **Takt:** 4/4 · **Länge:** 4 Takte
- **Töne/Dauern:** +12/1920 +24/1920 +22/1920 +20/1920 +19/7680
- **Intervalle:** +12, -2, -2, -1 · **Ambitus:** +12 bis +24 · **Zelle:** zellunabhängig
- **Rollen:** HM KF · **XYZ-Anker:** 0,30 / 0,90 / 0,25 · **Gültigkeit:** X 0,10–0,50 · Y 0,70–1,00 · Z 0,05–0,45
- **Akzent:** erste Note jeder Phrase +6 Velocity, lange Werte nicht nachakzentuieren · **Transformation:** EM-T004 (Kopfmotiv), EM-T009 (Umfärbung), EM-T003 (Rollenwanderung), EM-T002
- **Geeignete Harmonik:** EM-H001, EM-H002, EM-H003, EM-H004, EM-H005, EM-H006 · **ungeeignet (≥ 2 modusfremde Töne):** EM-H016, EM-H017, EM-H018, EM-H019
- **Evidenz:** E – eigenständige Gestaltung (Oktavdopplung als Gewicht); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

## 12. P – Phrasen

### EM-P001 – Wiederkehr mit Erweiterung (a a′ b a″)
- **Charakter:** lyrische Entwicklung · **Säule:** A · **Länge:** 8 Takte · **Harmonie:** EM-H004 · **XYZ-Anker:** 0,45 / 0,35 / 0,20
- **Bauplan:** T1–2 HM: EM-M003; T3–4 HM: EM-M003 + EM-T009; T5–6 HM: EM-M023; T7–8 HM: EM-M024
- **Evidenz:** E – eigenständige Gestaltung (Phrase n+1 variiert Phrase n (filmmusicnotes)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-P002 – Additive Enthüllung über vier Phrasen
- **Charakter:** Gestalt wird sichtbar · **Säule:** AB · **Länge:** 16 Takte · **Harmonie:** EM-H034 · **XYZ-Anker:** 0,35 / 0,45 / 0,40
- **Bauplan:** T1–4 TU: EM-M031; T5–8 TU: EM-M032; T9–12 TU: EM-M033; T13–16 HM: EM-M034
- **Evidenz:** N – nachgewiesenes Verfahren (additive Enthüllung (Filmtracks)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-P003 – Verkürzung zum Fragment
- **Charakter:** Erinnerung verblasst · **Säule:** A · **Länge:** 8 Takte · **Harmonie:** EM-H006 · **XYZ-Anker:** 0,35 / 0,25 / 0,30
- **Bauplan:** T1–2 HM: EM-M011 + EM-T004:6; T3–4 HM: EM-M011 + EM-T004:4; T5–6 TU: EM-M019; T7–8 TU: EM-M020
- **Evidenz:** I – begründete Interpretation (Fragmentierung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-P004 – Verzögerter Höhepunkt (8 Takte)
- **Charakter:** Erfüllung kommt spät · **Säule:** A · **Länge:** 8 Takte · **Harmonie:** EM-H016 · **XYZ-Anker:** 0,75 / 0,40 / 0,20
- **Bauplan:** T1–8 HM: EM-M012
- **Evidenz:** E – eigenständige Gestaltung (verzögerter Höhepunkt); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-P005 – Frage – Antwort zwischen HM und GS
- **Charakter:** Zwiegespräch · **Säule:** A · **Länge:** 8 Takte · **Harmonie:** EM-H007 · **XYZ-Anker:** 0,55 / 0,35 / 0,25
- **Bauplan:** T1–2 HM: EM-M023; T3–4 GS: EM-M024; T5–6 HM: EM-M005; T7–8 GS: EM-M024 + EM-T009
- **Evidenz:** N – nachgewiesenes Verfahren (Gesprächslogik (Wilcox: GINC)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-P006 – Kontrapunkt: lange Linie gegen bewegtes Gegenmotiv
- **Charakter:** verwoben · **Säule:** A · **Länge:** 8 Takte · **Harmonie:** EM-H005 · **XYZ-Anker:** 0,40 / 0,45 / 0,30
- **Bauplan:** T1–8 HM: EM-M011; T1–4 GS: EM-M028; T5–8 GS: EM-M029
- **Evidenz:** N – nachgewiesenes Verfahren (kontrapunktische Kombinierbarkeit (Movie Music UK: Mission)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-P007 – Harmonische Umfärbung eines gleichbleibenden Motivs
- **Charakter:** ein Ton, viele Bedeutungen · **Säule:** A · **Länge:** 8 Takte · **Harmonie:** EM-H053 · **XYZ-Anker:** 0,50 / 0,30 / 0,25
- **Bauplan:** T1–2 HM: EM-M001; T3–4 HM: EM-M001 + EM-T009; T5–6 HM: EM-M001 + EM-T009; T7–8 HM: EM-M001 + EM-T009
- **Evidenz:** I – begründete Interpretation (identische Melodie über verändertem Unterbau); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-P008 – Bewusst offene Phrase
- **Charakter:** Frage bleibt stehen · **Säule:** A · **Länge:** 8 Takte · **Harmonie:** EM-H037 · **XYZ-Anker:** 0,35 / 0,35 / 0,40
- **Bauplan:** T1–4 HM: EM-M038; T5–8 TU: EM-M021
- **Evidenz:** N – nachgewiesenes Verfahren (aufgeschobene Auflösung (Smith)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-P009 – Reduktion und Wiederaufnahme (16 Takte)
- **Charakter:** Atem holen · **Säule:** AB · **Länge:** 16 Takte · **Harmonie:** EM-H001 · **XYZ-Anker:** 0,35 / 0,30 / 0,20
- **Bauplan:** T1–4 HM: EM-M011 + EM-T004:6; T5–8 TU: EM-M019; T9–12 –: (Reduktion) + EM-T013; T13–16 HM: EM-M011 + EM-T014
- **Evidenz:** I – begründete Interpretation (Reduktion als Schlussstrategie (Wilcox)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-P010 – Registerwanderung tief → hoch
- **Charakter:** Offenbarung · **Säule:** A · **Länge:** 8 Takte · **Harmonie:** EM-H010 · **XYZ-Anker:** 0,50 / 0,50 / 0,20
- **Bauplan:** T1–2 GS: EM-M035; T3–4 GS: EM-M035 + EM-T002:+12; T5–8 HM: EM-M036
- **Evidenz:** N – nachgewiesenes Verfahren (Registerwanderung (OUP-Blog)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-P011 – Sechzehn Takte mit verdichtetem B-Teil
- **Charakter:** lyrische Großform · **Säule:** A · **Länge:** 16 Takte · **Harmonie:** EM-H061 · **XYZ-Anker:** 0,75 / 0,45 / 0,25
- **Bauplan:** T1–16 HM: EM-M048
- **Evidenz:** I – begründete Interpretation (verdichteter B-Teil (italianpiano)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-P012 – Monumentale Klagephrase
- **Charakter:** tragisch, getragen · **Säule:** A · **Länge:** 8 Takte · **Harmonie:** EM-H041 · **XYZ-Anker:** 0,25 / 0,75 / 0,30
- **Bauplan:** T1–8 HM: EM-M014
- **Evidenz:** E – eigenständige Gestaltung (Monumentalität durch Dauer); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-P013 – Spieluhr über Cluster (Schönheit und Bedrohung)
- **Charakter:** verstörende Unschuld · **Säule:** AB · **Länge:** 8 Takte · **Harmonie:** EM-H093 · **XYZ-Anker:** 0,80 / 0,25 / 0,60
- **Bauplan:** T1–8 AR: EM-M043
- **Evidenz:** N – nachgewiesenes Verfahren (Spieluhr gegen Diskordanz); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-P014 – Langsame Oberstimme über Gewichtsboden
- **Charakter:** Kraft ohne Hektik · **Säule:** B · **Länge:** 8 Takte · **Harmonie:** EM-H034 · **XYZ-Anker:** 0,35 / 0,80 / 0,35
- **Bauplan:** T1–8 HM: EM-M045
- **Evidenz:** I – begründete Interpretation (zwei Zeitschichten (NPR)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-P015 – Halbtonrückung als Y-Ereignis
- **Charakter:** Steigerung bei Intensitätswechsel · **Säule:** AB · **Länge:** 8 Takte · **Harmonie:** EM-H006 · **XYZ-Anker:** 0,30 / 0,60 / 0,45
- **Bauplan:** T1–4 HM: EM-M047; T5–8 HM: EM-M047 + EM-T017
- **Evidenz:** N – nachgewiesenes Verfahren (Halbtonrückung (Wilcox)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-P016 – Zellphrase mit Permutation je Durchlauf
- **Charakter:** gleich und anders · **Säule:** AB · **Länge:** 8 Takte · **Harmonie:** EM-H007 · **XYZ-Anker:** 0,45 / 0,25 / 0,35
- **Bauplan:** T1–2 TU: EM-C010 + EM-T001; T3–4 TU: EM-C010 + EM-T001; T5–6 TU: EM-C010 + EM-T002; T7–8 TU: EM-C010 + EM-T001
- **Evidenz:** N – nachgewiesenes Verfahren (Mikrozelle); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-P017 – B-A-C-H-Phrase mit Rotation
- **Charakter:** verborgene Ordnung · **Säule:** B · **Länge:** 8 Takte · **Harmonie:** EM-H073 · **XYZ-Anker:** 0,40 / 0,30 / 0,45
- **Bauplan:** T1–2 GS: EM-C022; T3–4 GS: EM-C022 + EM-T020; T5–6 GS: EM-C022 + EM-T020; T7–8 GS: EM-C022 + EM-T020
- **Evidenz:** N – nachgewiesenes Verfahren (Tonbuchstaben-Kode); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-P018 – Dur-Frage, Moll-Antwort
- **Charakter:** Licht und Schatten · **Säule:** A · **Länge:** 8 Takte · **Harmonie:** EM-H024 · **XYZ-Anker:** 0,55 / 0,30 / 0,30
- **Bauplan:** T1–4 HM: EM-M025; T5–8 HM: EM-M020
- **Evidenz:** E – eigenständige Gestaltung (Dur/Moll-Wechsel); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-P019 – Ternäre lyrische Phrase
- **Charakter:** sinnlich · **Säule:** A · **Länge:** 8 Takte · **Harmonie:** EM-H013 · **XYZ-Anker:** 0,50 / 0,35 / 0,30
- **Bauplan:** T1–4 GS: EM-M049; T5–8 HM: EM-M013 + EM-T004:5
- **Evidenz:** N – nachgewiesenes Verfahren (ternärer Rhythmus); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-P020 – Gegenmotiv-Rollentausch
- **Charakter:** Stimmen tauschen die Bedeutung · **Säule:** A · **Länge:** 16 Takte · **Harmonie:** EM-H056 · **XYZ-Anker:** 0,35 / 0,40 / 0,25
- **Bauplan:** T1–8 HM: EM-M011; T1–8 GS: EM-M029; T9–16 GS: EM-M011 + EM-T003; T9–16 HM: EM-M029 + EM-T003
- **Evidenz:** N – nachgewiesenes Verfahren (Rollenwanderung); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-P021 – Widerspruchsphrase
- **Charakter:** Einspruch gegen die Schönheit · **Säule:** AB · **Länge:** 8 Takte · **Harmonie:** EM-H094 · **XYZ-Anker:** 0,50 / 0,40 / 0,55
- **Bauplan:** T1–2 HM: EM-M023; T3–4 GS: EM-M027; T5–6 HM: EM-M023 + EM-T009; T7–8 GS: EM-M027 + EM-T019
- **Evidenz:** N – nachgewiesenes Verfahren (Gesprächslogik: Widerspruch); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-P022 – Hymnische Breite (16 Takte, 2× 8)
- **Charakter:** tragische Monumentalität · **Säule:** A · **Länge:** 16 Takte · **Harmonie:** EM-H043 · **XYZ-Anker:** 0,55 / 0,85 / 0,20
- **Bauplan:** T1–8 HM: EM-M018; T9–16 HM: EM-M018 + EM-T009
- **Evidenz:** E – eigenständige Gestaltung (Monumentalität); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

## 13. K – Kombinierbare Module (partitura multipla)

Module sind nicht-thematische (bzw. ausdrücklich thematisch gekennzeichnete) Einheiten von 4, 8, 12, 16 oder 32 Schlägen. Sie referenzieren H/R/B/C/M-Vorlagen statt Daten zu duplizieren. Harmonische Rolle: TRAEGT (definiert Harmonie), FAERBT (konsonant zur Harmonie), FSCHICHT (bewusst dissonant), NEUTRAL (ST). Die Paarprüfung ist regelbasiert (Rollen, konkurrierende Grundtöne, Register/Polyphonie, Thematik, Tonvorrat, ametrische Felder, Periodenverhältnis); Dreierkombinationen werden zusätzlich auf Oktavraum-Häufung, F-Schichten ohne Träger und thematische Konkurrenz geprüft. Austausch, Wiederholung und Unterbrechung nur an Modulgrenzen; bei festem Y bleibt die Zahl aktiver Module konstant, nur die Auswahl rotiert.

### EM-K001 – Moll-add9-Fläche eng
- **Art:** KLANG · **Rolle:** LF · **Länge:** 16 Schläge (15360 Ticks) · **Periode:** 15360 Ticks · **Quelle:** EM-H001
- **Tonvorrat:** {1, 2, ♭3, 5} · **Register (rel):** +2 … +12 · **Polyphonie:** 4 · **harmonische Absicht:** TRAEGT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K008, EM-K009, EM-K010, EM-K011, EM-K012, EM-K014, EM-K015, EM-K020, EM-K022, EM-K023, EM-K024, EM-K025, EM-K028, EM-K032, EM-K033, EM-K034, EM-K037
- **Bedingt:** EM-K013 (inkongruente Perioden 15360/1200 Ticks (Phasenversatz beabsichtigt?)); EM-K016 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K017 (inkongruente Perioden 15360/5760 Ticks (Phasenversatz beabsichtigt?)); EM-K018 (inkongruente Perioden 15360/720 Ticks (Phasenversatz beabsichtigt?)); EM-K019 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord); inkongruente Perioden 15360/5280 Ticks (Phasenversatz beabsichtigt?)); EM-K021 (inkongruente Perioden 15360/720 Ticks (Phasenversatz beabsichtigt?)); EM-K026 (färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K027 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K029 (färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K038 (inkongruente Perioden 15360/4800 Ticks (Phasenversatz beabsichtigt?))
- **Ungeeignet:** EM-K002 (gleiche Rolle LF doppelt belegt; Registerkollision (10 HT Überlappung bei 8 Stimmen)); EM-K003 (gleiche Rolle LF doppelt belegt; Registerkollision (10 HT Überlappung bei 8 Stimmen)); EM-K004 (gleiche Rolle LF doppelt belegt; Registerkollision (10 HT Überlappung bei 8 Stimmen)); EM-K005 (gleiche Rolle LF doppelt belegt; Registerkollision (10 HT Überlappung bei 10 Stimmen); zwei harmonietragende Flächen mit < 2 gemeinsamen Tönen (Polytonalität nur als Absicht in H-Vorlagen)); EM-K006 (Registerkollision (10 HT Überlappung bei 8 Stimmen)); EM-K007 (Registerkollision (10 HT Überlappung bei 8 Stimmen)); EM-K030 (Registerkollision (10 HT Überlappung bei 8 Stimmen); färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K031 (Registerkollision (10 HT Überlappung bei 8 Stimmen); färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K035 (gleiche Rolle LF doppelt belegt; Registerkollision (10 HT Überlappung bei 10 Stimmen)); EM-K036 (gleiche Rolle LF doppelt belegt; Registerkollision (10 HT Überlappung bei 8 Stimmen))
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (16 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K002 – Moll-add9-Fläche offen
- **Art:** KLANG · **Rolle:** LF · **Länge:** 16 Schläge (15360 Ticks) · **Periode:** 15360 Ticks · **Quelle:** EM-H002
- **Tonvorrat:** {1, 2, ♭3, 5} · **Register (rel):** -5 … +15 · **Polyphonie:** 4 · **harmonische Absicht:** TRAEGT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K008, EM-K009, EM-K010, EM-K011, EM-K012, EM-K014, EM-K015, EM-K020, EM-K022, EM-K023, EM-K024, EM-K025, EM-K028, EM-K032, EM-K033, EM-K034, EM-K037
- **Bedingt:** EM-K013 (inkongruente Perioden 15360/1200 Ticks (Phasenversatz beabsichtigt?)); EM-K016 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K017 (inkongruente Perioden 15360/5760 Ticks (Phasenversatz beabsichtigt?)); EM-K018 (inkongruente Perioden 15360/720 Ticks (Phasenversatz beabsichtigt?)); EM-K019 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord); inkongruente Perioden 15360/5280 Ticks (Phasenversatz beabsichtigt?)); EM-K021 (inkongruente Perioden 15360/720 Ticks (Phasenversatz beabsichtigt?)); EM-K026 (färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K027 (Registerüberlappung 8 HT: Oktavlage trennen; färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K029 (färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K038 (inkongruente Perioden 15360/4800 Ticks (Phasenversatz beabsichtigt?))
- **Ungeeignet:** EM-K001 (gleiche Rolle LF doppelt belegt; Registerkollision (10 HT Überlappung bei 8 Stimmen)); EM-K003 (gleiche Rolle LF doppelt belegt; Registerkollision (20 HT Überlappung bei 8 Stimmen)); EM-K004 (gleiche Rolle LF doppelt belegt; Registerkollision (20 HT Überlappung bei 8 Stimmen)); EM-K005 (gleiche Rolle LF doppelt belegt; Registerkollision (20 HT Überlappung bei 10 Stimmen); zwei harmonietragende Flächen mit < 2 gemeinsamen Tönen (Polytonalität nur als Absicht in H-Vorlagen)); EM-K006 (Registerkollision (20 HT Überlappung bei 8 Stimmen)); EM-K007 (Registerkollision (13 HT Überlappung bei 8 Stimmen)); EM-K030 (Registerkollision (20 HT Überlappung bei 8 Stimmen); färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K031 (Registerkollision (12 HT Überlappung bei 8 Stimmen); färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K035 (gleiche Rolle LF doppelt belegt; Registerkollision (19 HT Überlappung bei 10 Stimmen)); EM-K036 (gleiche Rolle LF doppelt belegt; Registerkollision (20 HT Überlappung bei 8 Stimmen))
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (16 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K003 – Dorisches Pendel
- **Art:** KLANG · **Rolle:** LF · **Länge:** 16 Schläge (15360 Ticks) · **Periode:** 15360 Ticks · **Quelle:** EM-H007
- **Tonvorrat:** {1, 2, ♭3, 4, 5, 6} · **Register (rel):** -5 … +17 · **Polyphonie:** 4 · **harmonische Absicht:** TRAEGT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K008, EM-K009, EM-K010, EM-K011, EM-K012, EM-K014, EM-K015, EM-K016, EM-K020, EM-K022, EM-K023, EM-K024, EM-K025, EM-K028, EM-K029, EM-K032, EM-K033, EM-K034, EM-K037
- **Bedingt:** EM-K013 (inkongruente Perioden 15360/1200 Ticks (Phasenversatz beabsichtigt?)); EM-K017 (inkongruente Perioden 15360/5760 Ticks (Phasenversatz beabsichtigt?)); EM-K018 (inkongruente Perioden 15360/720 Ticks (Phasenversatz beabsichtigt?)); EM-K019 (inkongruente Perioden 15360/5280 Ticks (Phasenversatz beabsichtigt?)); EM-K021 (inkongruente Perioden 15360/720 Ticks (Phasenversatz beabsichtigt?)); EM-K026 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K027 (Registerüberlappung 8 HT: Oktavlage trennen); EM-K038 (inkongruente Perioden 15360/4800 Ticks (Phasenversatz beabsichtigt?))
- **Ungeeignet:** EM-K001 (gleiche Rolle LF doppelt belegt; Registerkollision (10 HT Überlappung bei 8 Stimmen)); EM-K002 (gleiche Rolle LF doppelt belegt; Registerkollision (20 HT Überlappung bei 8 Stimmen)); EM-K004 (gleiche Rolle LF doppelt belegt; Registerkollision (22 HT Überlappung bei 8 Stimmen)); EM-K005 (gleiche Rolle LF doppelt belegt; Registerkollision (22 HT Überlappung bei 10 Stimmen)); EM-K006 (Registerkollision (22 HT Überlappung bei 8 Stimmen)); EM-K007 (Registerkollision (13 HT Überlappung bei 8 Stimmen)); EM-K030 (Registerkollision (22 HT Überlappung bei 8 Stimmen)); EM-K031 (Registerkollision (12 HT Überlappung bei 8 Stimmen)); EM-K035 (gleiche Rolle LF doppelt belegt; Registerkollision (20 HT Überlappung bei 10 Stimmen)); EM-K036 (gleiche Rolle LF doppelt belegt; Registerkollision (21 HT Überlappung bei 8 Stimmen))
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (16 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K004 – Dur-6/9-Licht
- **Art:** KLANG · **Rolle:** LF · **Länge:** 16 Schläge (15360 Ticks) · **Periode:** 30720 Ticks · **Quelle:** EM-H026
- **Tonvorrat:** {1, 3, 5, 6} · **Register (rel):** -8 … +19 · **Polyphonie:** 4 · **harmonische Absicht:** TRAEGT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K008, EM-K009, EM-K010, EM-K011, EM-K012, EM-K014, EM-K016, EM-K020, EM-K022, EM-K024, EM-K025, EM-K032, EM-K033, EM-K034, EM-K037
- **Bedingt:** EM-K013 (inkongruente Perioden 30720/1200 Ticks (Phasenversatz beabsichtigt?)); EM-K015 (Registerüberlappung 8 HT: Oktavlage trennen); EM-K017 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord); inkongruente Perioden 30720/5760 Ticks (Phasenversatz beabsichtigt?)); EM-K018 (inkongruente Perioden 30720/720 Ticks (Phasenversatz beabsichtigt?)); EM-K019 (färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord); inkongruente Perioden 30720/5280 Ticks (Phasenversatz beabsichtigt?)); EM-K021 (inkongruente Perioden 30720/720 Ticks (Phasenversatz beabsichtigt?)); EM-K023 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K026 (Registerüberlappung 9 HT: Oktavlage trennen; färbendes Modul bringt 5 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K027 (Registerüberlappung 8 HT: Oktavlage trennen; färbendes Modul bringt 4 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K028 (färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K029 (färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K038 (inkongruente Perioden 30720/4800 Ticks (Phasenversatz beabsichtigt?))
- **Ungeeignet:** EM-K001 (gleiche Rolle LF doppelt belegt; Registerkollision (10 HT Überlappung bei 8 Stimmen)); EM-K002 (gleiche Rolle LF doppelt belegt; Registerkollision (20 HT Überlappung bei 8 Stimmen)); EM-K003 (gleiche Rolle LF doppelt belegt; Registerkollision (22 HT Überlappung bei 8 Stimmen)); EM-K005 (gleiche Rolle LF doppelt belegt; Registerkollision (25 HT Überlappung bei 10 Stimmen)); EM-K006 (Registerkollision (25 HT Überlappung bei 8 Stimmen)); EM-K007 (Registerkollision (13 HT Überlappung bei 8 Stimmen)); EM-K030 (Registerkollision (22 HT Überlappung bei 8 Stimmen); färbendes Modul bringt 4 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K031 (Registerkollision (12 HT Überlappung bei 8 Stimmen); färbendes Modul bringt 4 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K035 (gleiche Rolle LF doppelt belegt; Registerkollision (20 HT Überlappung bei 10 Stimmen)); EM-K036 (gleiche Rolle LF doppelt belegt; Registerkollision (21 HT Überlappung bei 8 Stimmen))
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (16 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K005 – Pseudoserielle Fläche
- **Art:** KLANG · **Rolle:** LF · **Länge:** 16 Schläge (15360 Ticks) · **Periode:** 30720 Ticks · **Quelle:** EM-H073
- **Tonvorrat:** {1, ♭2, 3, 4, ♯4/♭5, 6, 7} · **Register (rel):** -7 … +18 · **Polyphonie:** 6 · **harmonische Absicht:** TRAEGT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K008, EM-K009, EM-K010, EM-K011, EM-K012, EM-K014, EM-K015, EM-K016, EM-K020, EM-K022, EM-K024, EM-K025, EM-K032, EM-K033, EM-K034, EM-K037
- **Bedingt:** EM-K013 (inkongruente Perioden 30720/1200 Ticks (Phasenversatz beabsichtigt?)); EM-K017 (färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord); inkongruente Perioden 30720/5760 Ticks (Phasenversatz beabsichtigt?)); EM-K018 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord); inkongruente Perioden 30720/720 Ticks (Phasenversatz beabsichtigt?)); EM-K019 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord); inkongruente Perioden 30720/5280 Ticks (Phasenversatz beabsichtigt?)); EM-K021 (inkongruente Perioden 30720/720 Ticks (Phasenversatz beabsichtigt?)); EM-K023 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K028 (färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K029 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K038 (inkongruente Perioden 30720/4800 Ticks (Phasenversatz beabsichtigt?))
- **Ungeeignet:** EM-K001 (gleiche Rolle LF doppelt belegt; Registerkollision (10 HT Überlappung bei 10 Stimmen); zwei harmonietragende Flächen mit < 2 gemeinsamen Tönen (Polytonalität nur als Absicht in H-Vorlagen)); EM-K002 (gleiche Rolle LF doppelt belegt; Registerkollision (20 HT Überlappung bei 10 Stimmen); zwei harmonietragende Flächen mit < 2 gemeinsamen Tönen (Polytonalität nur als Absicht in H-Vorlagen)); EM-K003 (gleiche Rolle LF doppelt belegt; Registerkollision (22 HT Überlappung bei 10 Stimmen)); EM-K004 (gleiche Rolle LF doppelt belegt; Registerkollision (25 HT Überlappung bei 10 Stimmen)); EM-K006 (Registerkollision (24 HT Überlappung bei 10 Stimmen)); EM-K007 (Registerkollision (13 HT Überlappung bei 10 Stimmen)); EM-K026 (Registerkollision (8 HT Überlappung bei 7 Stimmen); färbendes Modul bringt 5 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K027 (Registerkollision (8 HT Überlappung bei 7 Stimmen); färbendes Modul bringt 4 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K030 (Registerkollision (22 HT Überlappung bei 10 Stimmen); färbendes Modul bringt 4 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K031 (Registerkollision (12 HT Überlappung bei 10 Stimmen); färbendes Modul bringt 4 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K035 (gleiche Rolle LF doppelt belegt; Registerkollision (20 HT Überlappung bei 12 Stimmen)); EM-K036 (gleiche Rolle LF doppelt belegt; Registerkollision (21 HT Überlappung bei 10 Stimmen))
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (16 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K006 – Halbtonballung tief
- **Art:** EXPERIMENT · **Rolle:** KF · **Länge:** 16 Schläge (15360 Ticks) · **Periode:** 15360 Ticks · **Quelle:** EM-H066
- **Tonvorrat:** {1, ♯4/♭5, 5, ♭6} · **Register (rel):** -6 … +19 · **Polyphonie:** 4 · **harmonische Absicht:** FSCHICHT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K008, EM-K009, EM-K010, EM-K011, EM-K012, EM-K014, EM-K015, EM-K016, EM-K020, EM-K022, EM-K023, EM-K024, EM-K025, EM-K028, EM-K029, EM-K032, EM-K033, EM-K034, EM-K037
- **Bedingt:** EM-K013 (inkongruente Perioden 15360/1200 Ticks (Phasenversatz beabsichtigt?)); EM-K017 (inkongruente Perioden 15360/5760 Ticks (Phasenversatz beabsichtigt?)); EM-K018 (inkongruente Perioden 15360/720 Ticks (Phasenversatz beabsichtigt?)); EM-K019 (inkongruente Perioden 15360/5280 Ticks (Phasenversatz beabsichtigt?)); EM-K021 (inkongruente Perioden 15360/720 Ticks (Phasenversatz beabsichtigt?)); EM-K026 (Registerüberlappung 9 HT: Oktavlage trennen); EM-K027 (Registerüberlappung 8 HT: Oktavlage trennen); EM-K038 (inkongruente Perioden 15360/4800 Ticks (Phasenversatz beabsichtigt?))
- **Ungeeignet:** EM-K001 (Registerkollision (10 HT Überlappung bei 8 Stimmen)); EM-K002 (Registerkollision (20 HT Überlappung bei 8 Stimmen)); EM-K003 (Registerkollision (22 HT Überlappung bei 8 Stimmen)); EM-K004 (Registerkollision (25 HT Überlappung bei 8 Stimmen)); EM-K005 (Registerkollision (24 HT Überlappung bei 10 Stimmen)); EM-K007 (Registerkollision (13 HT Überlappung bei 8 Stimmen)); EM-K030 (Registerkollision (22 HT Überlappung bei 8 Stimmen)); EM-K031 (Registerkollision (12 HT Überlappung bei 8 Stimmen)); EM-K035 (Registerkollision (20 HT Überlappung bei 10 Stimmen)); EM-K036 (Registerkollision (21 HT Überlappung bei 8 Stimmen))
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (16 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K007 – Spreizcluster hoch
- **Art:** EXPERIMENT · **Rolle:** KF · **Länge:** 16 Schläge (15360 Ticks) · **Periode:** 15360 Ticks · **Quelle:** EM-H067
- **Tonvorrat:** {1, ♭2, 2, ♭3} · **Register (rel):** +0 … +13 · **Polyphonie:** 4 · **harmonische Absicht:** FSCHICHT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K008, EM-K009, EM-K010, EM-K011, EM-K012, EM-K014, EM-K015, EM-K016, EM-K020, EM-K022, EM-K023, EM-K024, EM-K025, EM-K026, EM-K028, EM-K029, EM-K032, EM-K033, EM-K034, EM-K037
- **Bedingt:** EM-K013 (inkongruente Perioden 15360/1200 Ticks (Phasenversatz beabsichtigt?)); EM-K017 (inkongruente Perioden 15360/5760 Ticks (Phasenversatz beabsichtigt?)); EM-K018 (inkongruente Perioden 15360/720 Ticks (Phasenversatz beabsichtigt?)); EM-K019 (inkongruente Perioden 15360/5280 Ticks (Phasenversatz beabsichtigt?)); EM-K021 (inkongruente Perioden 15360/720 Ticks (Phasenversatz beabsichtigt?)); EM-K027 (Registerüberlappung 8 HT: Oktavlage trennen); EM-K038 (inkongruente Perioden 15360/4800 Ticks (Phasenversatz beabsichtigt?))
- **Ungeeignet:** EM-K001 (Registerkollision (10 HT Überlappung bei 8 Stimmen)); EM-K002 (Registerkollision (13 HT Überlappung bei 8 Stimmen)); EM-K003 (Registerkollision (13 HT Überlappung bei 8 Stimmen)); EM-K004 (Registerkollision (13 HT Überlappung bei 8 Stimmen)); EM-K005 (Registerkollision (13 HT Überlappung bei 10 Stimmen)); EM-K006 (Registerkollision (13 HT Überlappung bei 8 Stimmen)); EM-K030 (Registerkollision (13 HT Überlappung bei 8 Stimmen)); EM-K031 (Registerkollision (12 HT Überlappung bei 8 Stimmen)); EM-K035 (Registerkollision (13 HT Überlappung bei 10 Stimmen)); EM-K036 (Registerkollision (13 HT Überlappung bei 8 Stimmen))
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (16 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K008 – Tonikapedal
- **Art:** BASS · **Rolle:** LB · **Länge:** 16 Schläge (15360 Ticks) · **Periode:** – Ticks · **Quelle:** EM-B001
- **Tonvorrat:** {1} · **Register (rel):** -12 … -12 · **Polyphonie:** 1 · **harmonische Absicht:** TRAEGT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K001, EM-K002, EM-K003, EM-K004, EM-K005, EM-K006, EM-K007, EM-K011, EM-K012, EM-K013, EM-K014, EM-K015, EM-K016, EM-K017, EM-K018, EM-K019, EM-K020, EM-K021, EM-K022, EM-K023, EM-K024, EM-K025, EM-K026, EM-K027, EM-K028, EM-K029, EM-K030, EM-K031, EM-K032, EM-K033, EM-K034, EM-K035, EM-K036, EM-K038
- **Ungeeignet:** EM-K009 (gleiche Rolle LB doppelt belegt); EM-K010 (gleiche Rolle LB doppelt belegt; Bass-F-Schicht gegen tragenden Bass: nur bei Z ≥ 0,5); EM-K037 (gleiche Rolle LB doppelt belegt)
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (16 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K009 – Quint-Drone
- **Art:** BASS · **Rolle:** LB · **Länge:** 16 Schläge (15360 Ticks) · **Periode:** – Ticks · **Quelle:** EM-B003
- **Tonvorrat:** {1, 5} · **Register (rel):** -24 … -17 · **Polyphonie:** 2 · **harmonische Absicht:** TRAEGT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K001, EM-K002, EM-K003, EM-K004, EM-K005, EM-K006, EM-K007, EM-K011, EM-K012, EM-K013, EM-K014, EM-K015, EM-K016, EM-K017, EM-K018, EM-K019, EM-K020, EM-K021, EM-K022, EM-K023, EM-K024, EM-K025, EM-K026, EM-K027, EM-K028, EM-K029, EM-K030, EM-K031, EM-K032, EM-K033, EM-K034, EM-K035, EM-K036, EM-K038
- **Ungeeignet:** EM-K008 (gleiche Rolle LB doppelt belegt); EM-K010 (gleiche Rolle LB doppelt belegt; Bass-F-Schicht gegen tragenden Bass: nur bei Z ≥ 0,5); EM-K037 (gleiche Rolle LB doppelt belegt)
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (16 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K010 – ♭2-Pedal
- **Art:** BASS · **Rolle:** LB · **Länge:** 16 Schläge (15360 Ticks) · **Periode:** – Ticks · **Quelle:** EM-B004
- **Tonvorrat:** {♭2} · **Register (rel):** -11 … -11 · **Polyphonie:** 1 · **harmonische Absicht:** FSCHICHT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K001, EM-K002, EM-K003, EM-K004, EM-K005, EM-K006, EM-K007, EM-K016, EM-K017, EM-K018, EM-K019, EM-K020, EM-K021, EM-K022, EM-K023, EM-K024, EM-K025, EM-K026, EM-K027, EM-K028, EM-K029, EM-K030, EM-K031, EM-K032, EM-K033, EM-K034, EM-K035, EM-K036, EM-K038
- **Bedingt:** EM-K011 (Bass-F-Schicht gegen tragenden Bass: nur bei Z ≥ 0,5); EM-K012 (Bass-F-Schicht gegen tragenden Bass: nur bei Z ≥ 0,5); EM-K013 (Bass-F-Schicht gegen tragenden Bass: nur bei Z ≥ 0,5); EM-K014 (Bass-F-Schicht gegen tragenden Bass: nur bei Z ≥ 0,5); EM-K015 (Bass-F-Schicht gegen tragenden Bass: nur bei Z ≥ 0,5)
- **Ungeeignet:** EM-K008 (gleiche Rolle LB doppelt belegt; Bass-F-Schicht gegen tragenden Bass: nur bei Z ≥ 0,5); EM-K009 (gleiche Rolle LB doppelt belegt; Bass-F-Schicht gegen tragenden Bass: nur bei Z ≥ 0,5); EM-K037 (gleiche Rolle LB doppelt belegt; Bass-F-Schicht gegen tragenden Bass: nur bei Z ≥ 0,5)
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (16 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K011 – Herzschlag
- **Art:** BASS · **Rolle:** KB · **Länge:** 4 Schläge (3840 Ticks) · **Periode:** 3840 Ticks · **Quelle:** EM-B006 + EM-R001
- **Tonvorrat:** {1} · **Register (rel):** -12 … -12 · **Polyphonie:** 1 · **harmonische Absicht:** TRAEGT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K001, EM-K002, EM-K003, EM-K004, EM-K005, EM-K006, EM-K007, EM-K008, EM-K009, EM-K016, EM-K020, EM-K022, EM-K023, EM-K024, EM-K025, EM-K026, EM-K027, EM-K028, EM-K029, EM-K030, EM-K031, EM-K032, EM-K033, EM-K034, EM-K035, EM-K036, EM-K037
- **Bedingt:** EM-K010 (Bass-F-Schicht gegen tragenden Bass: nur bei Z ≥ 0,5); EM-K017 (inkongruente Perioden 3840/5760 Ticks (Phasenversatz beabsichtigt?)); EM-K018 (inkongruente Perioden 3840/720 Ticks (Phasenversatz beabsichtigt?)); EM-K019 (inkongruente Perioden 3840/5280 Ticks (Phasenversatz beabsichtigt?)); EM-K021 (inkongruente Perioden 3840/720 Ticks (Phasenversatz beabsichtigt?)); EM-K038 (inkongruente Perioden 3840/4800 Ticks (Phasenversatz beabsichtigt?))
- **Ungeeignet:** EM-K012 (gleiche Rolle KB doppelt belegt); EM-K013 (gleiche Rolle KB doppelt belegt; inkongruente Perioden 3840/1200 Ticks (Phasenversatz beabsichtigt?)); EM-K014 (gleiche Rolle KB doppelt belegt); EM-K015 (gleiche Rolle KB doppelt belegt)
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (4 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K012 – Achtelpuls Einzelton
- **Art:** BASS · **Rolle:** KB · **Länge:** 4 Schläge (3840 Ticks) · **Periode:** 3840 Ticks · **Quelle:** EM-B008 + EM-R004
- **Tonvorrat:** {1} · **Register (rel):** -12 … -12 · **Polyphonie:** 1 · **harmonische Absicht:** TRAEGT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K001, EM-K002, EM-K003, EM-K004, EM-K005, EM-K006, EM-K007, EM-K008, EM-K009, EM-K016, EM-K020, EM-K022, EM-K023, EM-K024, EM-K025, EM-K026, EM-K027, EM-K028, EM-K029, EM-K030, EM-K031, EM-K032, EM-K033, EM-K034, EM-K035, EM-K036, EM-K037
- **Bedingt:** EM-K010 (Bass-F-Schicht gegen tragenden Bass: nur bei Z ≥ 0,5); EM-K017 (inkongruente Perioden 3840/5760 Ticks (Phasenversatz beabsichtigt?)); EM-K018 (inkongruente Perioden 3840/720 Ticks (Phasenversatz beabsichtigt?)); EM-K019 (inkongruente Perioden 3840/5280 Ticks (Phasenversatz beabsichtigt?)); EM-K021 (inkongruente Perioden 3840/720 Ticks (Phasenversatz beabsichtigt?)); EM-K038 (inkongruente Perioden 3840/4800 Ticks (Phasenversatz beabsichtigt?))
- **Ungeeignet:** EM-K011 (gleiche Rolle KB doppelt belegt); EM-K013 (gleiche Rolle KB doppelt belegt; inkongruente Perioden 3840/1200 Ticks (Phasenversatz beabsichtigt?)); EM-K014 (gleiche Rolle KB doppelt belegt); EM-K015 (gleiche Rolle KB doppelt belegt)
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (4 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K013 – Fünftonfigur modal
- **Art:** OSTINATO · **Rolle:** KB · **Länge:** 4 Schläge (3840 Ticks) · **Periode:** 1200 Ticks · **Quelle:** EM-B010 + EM-R007
- **Tonvorrat:** {1, ♭3, 4, ♭7} · **Register (rel):** -14 … -7 · **Polyphonie:** 1 · **harmonische Absicht:** TRAEGT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K008, EM-K009, EM-K024, EM-K025, EM-K026, EM-K027, EM-K028, EM-K029, EM-K034, EM-K037, EM-K038
- **Bedingt:** EM-K001 (inkongruente Perioden 15360/1200 Ticks (Phasenversatz beabsichtigt?)); EM-K002 (inkongruente Perioden 15360/1200 Ticks (Phasenversatz beabsichtigt?)); EM-K003 (inkongruente Perioden 15360/1200 Ticks (Phasenversatz beabsichtigt?)); EM-K004 (inkongruente Perioden 30720/1200 Ticks (Phasenversatz beabsichtigt?)); EM-K005 (inkongruente Perioden 30720/1200 Ticks (Phasenversatz beabsichtigt?)); EM-K006 (inkongruente Perioden 15360/1200 Ticks (Phasenversatz beabsichtigt?)); EM-K007 (inkongruente Perioden 15360/1200 Ticks (Phasenversatz beabsichtigt?)); EM-K010 (Bass-F-Schicht gegen tragenden Bass: nur bei Z ≥ 0,5); EM-K016 (inkongruente Perioden 1200/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K017 (inkongruente Perioden 1200/5760 Ticks (Phasenversatz beabsichtigt?)); EM-K018 (inkongruente Perioden 1200/720 Ticks (Phasenversatz beabsichtigt?)); EM-K019 (inkongruente Perioden 1200/5280 Ticks (Phasenversatz beabsichtigt?)) …
- **Ungeeignet:** EM-K011 (gleiche Rolle KB doppelt belegt; inkongruente Perioden 3840/1200 Ticks (Phasenversatz beabsichtigt?)); EM-K012 (gleiche Rolle KB doppelt belegt; inkongruente Perioden 3840/1200 Ticks (Phasenversatz beabsichtigt?)); EM-K014 (gleiche Rolle KB doppelt belegt; inkongruente Perioden 1200/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K015 (gleiche Rolle KB doppelt belegt; inkongruente Perioden 1200/3840 Ticks (Phasenversatz beabsichtigt?))
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (4 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K014 – Gewichtsfigur
- **Art:** BASS · **Rolle:** KB · **Länge:** 4 Schläge (3840 Ticks) · **Periode:** 3840 Ticks · **Quelle:** EM-B030 + EM-R014
- **Tonvorrat:** {1, ♭3, 5, ♭7} · **Register (rel):** -17 … -9 · **Polyphonie:** 1 · **harmonische Absicht:** TRAEGT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K001, EM-K002, EM-K003, EM-K004, EM-K005, EM-K006, EM-K007, EM-K008, EM-K009, EM-K016, EM-K020, EM-K022, EM-K023, EM-K024, EM-K025, EM-K026, EM-K027, EM-K028, EM-K029, EM-K030, EM-K031, EM-K032, EM-K033, EM-K034, EM-K035, EM-K036, EM-K037
- **Bedingt:** EM-K010 (Bass-F-Schicht gegen tragenden Bass: nur bei Z ≥ 0,5); EM-K017 (inkongruente Perioden 3840/5760 Ticks (Phasenversatz beabsichtigt?)); EM-K018 (inkongruente Perioden 3840/720 Ticks (Phasenversatz beabsichtigt?)); EM-K019 (inkongruente Perioden 3840/5280 Ticks (Phasenversatz beabsichtigt?)); EM-K021 (inkongruente Perioden 3840/720 Ticks (Phasenversatz beabsichtigt?)); EM-K038 (inkongruente Perioden 3840/4800 Ticks (Phasenversatz beabsichtigt?))
- **Ungeeignet:** EM-K011 (gleiche Rolle KB doppelt belegt); EM-K012 (gleiche Rolle KB doppelt belegt); EM-K013 (gleiche Rolle KB doppelt belegt; inkongruente Perioden 1200/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K015 (gleiche Rolle KB doppelt belegt)
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (4 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K015 – Groove-Bass synkopisch
- **Art:** BASS · **Rolle:** KB · **Länge:** 4 Schläge (3840 Ticks) · **Periode:** 3840 Ticks · **Quelle:** EM-B032 + EM-R021
- **Tonvorrat:** {1, 5, ♭7} · **Register (rel):** -12 … +0 · **Polyphonie:** 1 · **harmonische Absicht:** TRAEGT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K001, EM-K002, EM-K003, EM-K005, EM-K006, EM-K007, EM-K008, EM-K009, EM-K016, EM-K020, EM-K022, EM-K023, EM-K024, EM-K025, EM-K026, EM-K027, EM-K028, EM-K029, EM-K030, EM-K031, EM-K032, EM-K033, EM-K034, EM-K035, EM-K036, EM-K037
- **Bedingt:** EM-K004 (Registerüberlappung 8 HT: Oktavlage trennen); EM-K010 (Bass-F-Schicht gegen tragenden Bass: nur bei Z ≥ 0,5); EM-K017 (inkongruente Perioden 3840/5760 Ticks (Phasenversatz beabsichtigt?)); EM-K018 (inkongruente Perioden 3840/720 Ticks (Phasenversatz beabsichtigt?)); EM-K019 (inkongruente Perioden 3840/5280 Ticks (Phasenversatz beabsichtigt?)); EM-K021 (inkongruente Perioden 3840/720 Ticks (Phasenversatz beabsichtigt?)); EM-K038 (inkongruente Perioden 3840/4800 Ticks (Phasenversatz beabsichtigt?))
- **Ungeeignet:** EM-K011 (gleiche Rolle KB doppelt belegt); EM-K012 (gleiche Rolle KB doppelt belegt); EM-K013 (gleiche Rolle KB doppelt belegt; inkongruente Perioden 1200/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K014 (gleiche Rolle KB doppelt belegt)
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (4 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K016 – Spieluhr-Ostinato
- **Art:** OSTINATO · **Rolle:** AR · **Länge:** 4 Schläge (3840 Ticks) · **Periode:** 3840 Ticks · **Quelle:** EM-M043 + EM-R024
- **Tonvorrat:** {3, 5, 6} · **Register (rel):** +16 … +21 · **Polyphonie:** 1 · **harmonische Absicht:** FAERBT · **thematisch:** ja
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K003, EM-K004, EM-K005, EM-K006, EM-K007, EM-K008, EM-K009, EM-K010, EM-K011, EM-K012, EM-K014, EM-K015, EM-K020, EM-K022, EM-K023, EM-K024, EM-K025, EM-K030, EM-K031, EM-K032, EM-K033, EM-K034, EM-K036, EM-K037
- **Bedingt:** EM-K001 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K002 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K013 (inkongruente Perioden 1200/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K017 (inkongruente Perioden 3840/5760 Ticks (Phasenversatz beabsichtigt?)); EM-K018 (inkongruente Perioden 3840/720 Ticks (Phasenversatz beabsichtigt?)); EM-K019 (inkongruente Perioden 3840/5280 Ticks (Phasenversatz beabsichtigt?)); EM-K021 (inkongruente Perioden 3840/720 Ticks (Phasenversatz beabsichtigt?)); EM-K026 (zwei thematische Schichten: rhythmische Komplementarität prüfen (Mission-Prinzip)); EM-K027 (zwei thematische Schichten: rhythmische Komplementarität prüfen (Mission-Prinzip)); EM-K028 (zwei thematische Schichten: rhythmische Komplementarität prüfen (Mission-Prinzip)); EM-K029 (zwei thematische Schichten: rhythmische Komplementarität prüfen (Mission-Prinzip)); EM-K035 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)) …
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (4 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K017 – Moll-add9-Arpeggio ternär
- **Art:** OSTINATO · **Rolle:** AR · **Länge:** 12 Schläge (11520 Ticks) · **Periode:** 5760 Ticks · **Quelle:** EM-C010 + EM-R010
- **Tonvorrat:** {1, 2, ♭3, 5} · **Register (rel):** +12 … +23 · **Polyphonie:** 1 · **harmonische Absicht:** FAERBT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K008, EM-K009, EM-K010, EM-K027, EM-K028, EM-K029, EM-K034, EM-K037
- **Bedingt:** EM-K001 (inkongruente Perioden 15360/5760 Ticks (Phasenversatz beabsichtigt?)); EM-K002 (inkongruente Perioden 15360/5760 Ticks (Phasenversatz beabsichtigt?)); EM-K003 (inkongruente Perioden 15360/5760 Ticks (Phasenversatz beabsichtigt?)); EM-K004 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord); inkongruente Perioden 30720/5760 Ticks (Phasenversatz beabsichtigt?)); EM-K005 (färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord); inkongruente Perioden 30720/5760 Ticks (Phasenversatz beabsichtigt?)); EM-K006 (inkongruente Perioden 15360/5760 Ticks (Phasenversatz beabsichtigt?)); EM-K007 (inkongruente Perioden 15360/5760 Ticks (Phasenversatz beabsichtigt?)); EM-K011 (inkongruente Perioden 3840/5760 Ticks (Phasenversatz beabsichtigt?)); EM-K012 (inkongruente Perioden 3840/5760 Ticks (Phasenversatz beabsichtigt?)); EM-K013 (inkongruente Perioden 1200/5760 Ticks (Phasenversatz beabsichtigt?)); EM-K014 (inkongruente Perioden 3840/5760 Ticks (Phasenversatz beabsichtigt?)); EM-K015 (inkongruente Perioden 3840/5760 Ticks (Phasenversatz beabsichtigt?)) …
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (12 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K018 – Sus2-Zelle 3 gegen 4
- **Art:** ZELLE · **Rolle:** AR · **Länge:** 4 Schläge (3840 Ticks) · **Periode:** 720 Ticks · **Quelle:** EM-C007 + EM-R008
- **Tonvorrat:** {1, 2, 5} · **Register (rel):** +12 … +23 · **Polyphonie:** 1 · **harmonische Absicht:** FAERBT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K008, EM-K009, EM-K010, EM-K027, EM-K028, EM-K029, EM-K034, EM-K037
- **Bedingt:** EM-K001 (inkongruente Perioden 15360/720 Ticks (Phasenversatz beabsichtigt?)); EM-K002 (inkongruente Perioden 15360/720 Ticks (Phasenversatz beabsichtigt?)); EM-K003 (inkongruente Perioden 15360/720 Ticks (Phasenversatz beabsichtigt?)); EM-K004 (inkongruente Perioden 30720/720 Ticks (Phasenversatz beabsichtigt?)); EM-K005 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord); inkongruente Perioden 30720/720 Ticks (Phasenversatz beabsichtigt?)); EM-K006 (inkongruente Perioden 15360/720 Ticks (Phasenversatz beabsichtigt?)); EM-K007 (inkongruente Perioden 15360/720 Ticks (Phasenversatz beabsichtigt?)); EM-K011 (inkongruente Perioden 3840/720 Ticks (Phasenversatz beabsichtigt?)); EM-K012 (inkongruente Perioden 3840/720 Ticks (Phasenversatz beabsichtigt?)); EM-K013 (inkongruente Perioden 1200/720 Ticks (Phasenversatz beabsichtigt?)); EM-K014 (inkongruente Perioden 3840/720 Ticks (Phasenversatz beabsichtigt?)); EM-K015 (inkongruente Perioden 3840/720 Ticks (Phasenversatz beabsichtigt?)) …
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (4 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K019 – Kleinterzpaare kontrahierend
- **Art:** OSTINATO · **Rolle:** AR · **Länge:** 8 Schläge (7680 Ticks) · **Periode:** 5280 Ticks · **Quelle:** EM-C027 + EM-R027
- **Tonvorrat:** {1, ♭3, 4, ♭6} · **Register (rel):** +12 … +23 · **Polyphonie:** 1 · **harmonische Absicht:** FAERBT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K008, EM-K009, EM-K010, EM-K027, EM-K028, EM-K029, EM-K034, EM-K037
- **Bedingt:** EM-K001 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord); inkongruente Perioden 15360/5280 Ticks (Phasenversatz beabsichtigt?)); EM-K002 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord); inkongruente Perioden 15360/5280 Ticks (Phasenversatz beabsichtigt?)); EM-K003 (inkongruente Perioden 15360/5280 Ticks (Phasenversatz beabsichtigt?)); EM-K004 (färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord); inkongruente Perioden 30720/5280 Ticks (Phasenversatz beabsichtigt?)); EM-K005 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord); inkongruente Perioden 30720/5280 Ticks (Phasenversatz beabsichtigt?)); EM-K006 (inkongruente Perioden 15360/5280 Ticks (Phasenversatz beabsichtigt?)); EM-K007 (inkongruente Perioden 15360/5280 Ticks (Phasenversatz beabsichtigt?)); EM-K011 (inkongruente Perioden 3840/5280 Ticks (Phasenversatz beabsichtigt?)); EM-K012 (inkongruente Perioden 3840/5280 Ticks (Phasenversatz beabsichtigt?)); EM-K013 (inkongruente Perioden 1200/5280 Ticks (Phasenversatz beabsichtigt?)); EM-K014 (inkongruente Perioden 3840/5280 Ticks (Phasenversatz beabsichtigt?)); EM-K015 (inkongruente Perioden 3840/5280 Ticks (Phasenversatz beabsichtigt?)) …
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (8 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K020 – Zweitonpaare (Halbton) über Puls
- **Art:** ZELLE · **Rolle:** AR · **Länge:** 4 Schläge (3840 Ticks) · **Periode:** 3840 Ticks · **Quelle:** EM-C046 + EM-R063
- **Tonvorrat:** {1, ♭2} · **Register (rel):** +12 … +23 · **Polyphonie:** 1 · **harmonische Absicht:** FSCHICHT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K001, EM-K002, EM-K003, EM-K004, EM-K005, EM-K006, EM-K007, EM-K008, EM-K009, EM-K010, EM-K011, EM-K012, EM-K014, EM-K015, EM-K016, EM-K027, EM-K028, EM-K029, EM-K030, EM-K031, EM-K032, EM-K033, EM-K034, EM-K035, EM-K036, EM-K037
- **Bedingt:** EM-K013 (inkongruente Perioden 1200/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K017 (Registerüberlappung 11 HT: Oktavlage trennen; inkongruente Perioden 5760/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K018 (Registerüberlappung 11 HT: Oktavlage trennen; inkongruente Perioden 720/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K019 (Registerüberlappung 11 HT: Oktavlage trennen; inkongruente Perioden 5280/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K021 (Registerüberlappung 11 HT: Oktavlage trennen; inkongruente Perioden 3840/720 Ticks (Phasenversatz beabsichtigt?)); EM-K022 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K023 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K024 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K025 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K026 (Registerüberlappung 8 HT: Oktavlage trennen); EM-K038 (Registerüberlappung 11 HT: Oktavlage trennen; inkongruente Perioden 3840/4800 Ticks (Phasenversatz beabsichtigt?))
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (4 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K021 – Chromatische Dreiton-Repetition
- **Art:** EXPERIMENT · **Rolle:** AR · **Länge:** 4 Schläge (3840 Ticks) · **Periode:** 720 Ticks · **Quelle:** EM-C019 + EM-R035
- **Tonvorrat:** {1, ♭2, 2} · **Register (rel):** +12 … +23 · **Polyphonie:** 1 · **harmonische Absicht:** FSCHICHT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K008, EM-K009, EM-K010, EM-K027, EM-K028, EM-K029, EM-K034, EM-K037
- **Bedingt:** EM-K001 (inkongruente Perioden 15360/720 Ticks (Phasenversatz beabsichtigt?)); EM-K002 (inkongruente Perioden 15360/720 Ticks (Phasenversatz beabsichtigt?)); EM-K003 (inkongruente Perioden 15360/720 Ticks (Phasenversatz beabsichtigt?)); EM-K004 (inkongruente Perioden 30720/720 Ticks (Phasenversatz beabsichtigt?)); EM-K005 (inkongruente Perioden 30720/720 Ticks (Phasenversatz beabsichtigt?)); EM-K006 (inkongruente Perioden 15360/720 Ticks (Phasenversatz beabsichtigt?)); EM-K007 (inkongruente Perioden 15360/720 Ticks (Phasenversatz beabsichtigt?)); EM-K011 (inkongruente Perioden 3840/720 Ticks (Phasenversatz beabsichtigt?)); EM-K012 (inkongruente Perioden 3840/720 Ticks (Phasenversatz beabsichtigt?)); EM-K013 (inkongruente Perioden 1200/720 Ticks (Phasenversatz beabsichtigt?)); EM-K014 (inkongruente Perioden 3840/720 Ticks (Phasenversatz beabsichtigt?)); EM-K015 (inkongruente Perioden 3840/720 Ticks (Phasenversatz beabsichtigt?)) …
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (4 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K022 – Klavierglocke selten
- **Art:** EINZEL · **Rolle:** TU · **Länge:** 16 Schläge (15360 Ticks) · **Periode:** 7680 Ticks · **Quelle:** EM-C030 + EM-R019
- **Tonvorrat:** {1, ♭6} · **Register (rel):** +12 … +23 · **Polyphonie:** 1 · **harmonische Absicht:** FAERBT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K001, EM-K002, EM-K003, EM-K004, EM-K005, EM-K006, EM-K007, EM-K008, EM-K009, EM-K010, EM-K011, EM-K012, EM-K014, EM-K015, EM-K016, EM-K027, EM-K028, EM-K029, EM-K030, EM-K031, EM-K032, EM-K033, EM-K034, EM-K035, EM-K036, EM-K037
- **Bedingt:** EM-K013 (inkongruente Perioden 1200/7680 Ticks (Phasenversatz beabsichtigt?)); EM-K017 (Registerüberlappung 11 HT: Oktavlage trennen; inkongruente Perioden 5760/7680 Ticks (Phasenversatz beabsichtigt?)); EM-K018 (Registerüberlappung 11 HT: Oktavlage trennen; inkongruente Perioden 720/7680 Ticks (Phasenversatz beabsichtigt?)); EM-K019 (Registerüberlappung 11 HT: Oktavlage trennen; inkongruente Perioden 5280/7680 Ticks (Phasenversatz beabsichtigt?)); EM-K020 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K021 (Registerüberlappung 11 HT: Oktavlage trennen; inkongruente Perioden 720/7680 Ticks (Phasenversatz beabsichtigt?)); EM-K023 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K024 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K025 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K026 (Registerüberlappung 8 HT: Oktavlage trennen); EM-K038 (Registerüberlappung 11 HT: Oktavlage trennen; inkongruente Perioden 7680/4800 Ticks (Phasenversatz beabsichtigt?))
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (16 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K023 – Zögernde Reibungstöne
- **Art:** EINZEL · **Rolle:** TU · **Länge:** 4 Schläge (3840 Ticks) · **Periode:** 3840 Ticks · **Quelle:** EM-C009 + EM-R018
- **Tonvorrat:** {1, 2, ♭3} · **Register (rel):** +12 … +23 · **Polyphonie:** 1 · **harmonische Absicht:** FAERBT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K001, EM-K002, EM-K003, EM-K006, EM-K007, EM-K008, EM-K009, EM-K010, EM-K011, EM-K012, EM-K014, EM-K015, EM-K016, EM-K027, EM-K028, EM-K029, EM-K030, EM-K031, EM-K032, EM-K033, EM-K034, EM-K035, EM-K036, EM-K037
- **Bedingt:** EM-K004 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K005 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K013 (inkongruente Perioden 1200/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K017 (Registerüberlappung 11 HT: Oktavlage trennen; inkongruente Perioden 5760/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K018 (Registerüberlappung 11 HT: Oktavlage trennen; inkongruente Perioden 720/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K019 (Registerüberlappung 11 HT: Oktavlage trennen; inkongruente Perioden 5280/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K020 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K021 (Registerüberlappung 11 HT: Oktavlage trennen; inkongruente Perioden 720/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K022 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K024 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K025 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K026 (Registerüberlappung 8 HT: Oktavlage trennen) …
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (4 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K024 – Tritonus-Einwürfe ametrisch
- **Art:** PULSLOS · **Rolle:** TU · **Länge:** 8 Schläge (7680 Ticks) · **Periode:** 7680 Ticks (ametrisch) · **Quelle:** EM-C005 + EM-R041
- **Tonvorrat:** {1, ♯4/♭5} · **Register (rel):** +12 … +23 · **Polyphonie:** 1 · **harmonische Absicht:** FSCHICHT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K001, EM-K002, EM-K003, EM-K004, EM-K005, EM-K006, EM-K007, EM-K008, EM-K009, EM-K010, EM-K011, EM-K012, EM-K013, EM-K014, EM-K015, EM-K016, EM-K027, EM-K028, EM-K029, EM-K030, EM-K031, EM-K032, EM-K033, EM-K034, EM-K035, EM-K036, EM-K037
- **Bedingt:** EM-K017 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K018 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K019 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K020 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K021 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K022 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K023 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K026 (Registerüberlappung 8 HT: Oktavlage trennen); EM-K038 (Registerüberlappung 11 HT: Oktavlage trennen)
- **Ungeeignet:** EM-K025 (zwei ametrische Tonhöhenfelder ohne Anker konkurrieren; Registerüberlappung 11 HT: Oktavlage trennen)
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (8 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K025 – Pseudoserielle Streuung
- **Art:** PULSLOS · **Rolle:** TU · **Länge:** 8 Schläge (7680 Ticks) · **Periode:** 7680 Ticks (ametrisch) · **Quelle:** EM-C035 + EM-R042
- **Tonvorrat:** {1, ♭2, 3, 4, ♯4/♭5, 6, 7} · **Register (rel):** +12 … +23 · **Polyphonie:** 1 · **harmonische Absicht:** FSCHICHT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K001, EM-K002, EM-K003, EM-K004, EM-K005, EM-K006, EM-K007, EM-K008, EM-K009, EM-K010, EM-K011, EM-K012, EM-K013, EM-K014, EM-K015, EM-K016, EM-K027, EM-K028, EM-K029, EM-K030, EM-K031, EM-K032, EM-K033, EM-K034, EM-K035, EM-K036, EM-K037
- **Bedingt:** EM-K017 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K018 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K019 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K020 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K021 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K022 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K023 (Registerüberlappung 11 HT: Oktavlage trennen); EM-K026 (Registerüberlappung 8 HT: Oktavlage trennen); EM-K038 (Registerüberlappung 11 HT: Oktavlage trennen)
- **Ungeeignet:** EM-K024 (zwei ametrische Tonhöhenfelder ohne Anker konkurrieren; Registerüberlappung 11 HT: Oktavlage trennen)
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (8 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K026 – Lyrische Moll-Linie
- **Art:** LYRIK · **Rolle:** HM · **Länge:** 32 Schläge (30720 Ticks) · **Periode:** – Ticks · **Quelle:** EM-M011
- **Tonvorrat:** {1, 2, ♭3, 4, 5, ♭6, ♭7} · **Register (rel):** +10 … +20 · **Polyphonie:** 1 · **harmonische Absicht:** FAERBT · **thematisch:** ja
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K007, EM-K008, EM-K009, EM-K010, EM-K011, EM-K012, EM-K013, EM-K014, EM-K015, EM-K030, EM-K031, EM-K032, EM-K033, EM-K034, EM-K037
- **Bedingt:** EM-K001 (färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K002 (färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K003 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K004 (Registerüberlappung 9 HT: Oktavlage trennen; färbendes Modul bringt 5 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K006 (Registerüberlappung 9 HT: Oktavlage trennen); EM-K016 (zwei thematische Schichten: rhythmische Komplementarität prüfen (Mission-Prinzip)); EM-K017 (Registerüberlappung 8 HT: Oktavlage trennen); EM-K018 (Registerüberlappung 8 HT: Oktavlage trennen); EM-K019 (Registerüberlappung 8 HT: Oktavlage trennen); EM-K020 (Registerüberlappung 8 HT: Oktavlage trennen); EM-K021 (Registerüberlappung 8 HT: Oktavlage trennen); EM-K022 (Registerüberlappung 8 HT: Oktavlage trennen) …
- **Ungeeignet:** EM-K005 (Registerkollision (8 HT Überlappung bei 7 Stimmen); färbendes Modul bringt 5 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K028 (gleiche Rolle HM doppelt belegt; zwei thematische Hauptstimmen)
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (32 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K027 – Gegenmotiv Viertel
- **Art:** LYRIK · **Rolle:** GS · **Länge:** 16 Schläge (15360 Ticks) · **Periode:** – Ticks · **Quelle:** EM-M028
- **Tonvorrat:** {1, 2, ♭3, 4, 5, ♭6} · **Register (rel):** +0 … +8 · **Polyphonie:** 1 · **harmonische Absicht:** FAERBT · **thematisch:** ja
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K008, EM-K009, EM-K010, EM-K011, EM-K012, EM-K013, EM-K014, EM-K015, EM-K017, EM-K018, EM-K019, EM-K020, EM-K021, EM-K022, EM-K023, EM-K024, EM-K025, EM-K032, EM-K033, EM-K034, EM-K037, EM-K038
- **Bedingt:** EM-K001 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K002 (Registerüberlappung 8 HT: Oktavlage trennen; färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K003 (Registerüberlappung 8 HT: Oktavlage trennen); EM-K004 (Registerüberlappung 8 HT: Oktavlage trennen; färbendes Modul bringt 4 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K006 (Registerüberlappung 8 HT: Oktavlage trennen); EM-K007 (Registerüberlappung 8 HT: Oktavlage trennen); EM-K016 (zwei thematische Schichten: rhythmische Komplementarität prüfen (Mission-Prinzip)); EM-K026 (zwei thematische Schichten: rhythmische Komplementarität prüfen (Mission-Prinzip)); EM-K028 (zwei thematische Schichten: rhythmische Komplementarität prüfen (Mission-Prinzip)); EM-K029 (zwei thematische Schichten: rhythmische Komplementarität prüfen (Mission-Prinzip)); EM-K030 (Registerüberlappung 8 HT: Oktavlage trennen); EM-K031 (Registerüberlappung 8 HT: Oktavlage trennen) …
- **Ungeeignet:** EM-K005 (Registerkollision (8 HT Überlappung bei 7 Stimmen); färbendes Modul bringt 4 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K035 (Registerkollision (8 HT Überlappung bei 7 Stimmen); färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord))
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (16 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K028 – Langsame Oberstimme
- **Art:** LYRIK · **Rolle:** HM · **Länge:** 16 Schläge (15360 Ticks) · **Periode:** – Ticks · **Quelle:** EM-M045
- **Tonvorrat:** {2, ♭3, 4, 5} · **Register (rel):** +14 … +19 · **Polyphonie:** 1 · **harmonische Absicht:** FAERBT · **thematisch:** ja
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K001, EM-K002, EM-K003, EM-K006, EM-K007, EM-K008, EM-K009, EM-K010, EM-K011, EM-K012, EM-K013, EM-K014, EM-K015, EM-K017, EM-K018, EM-K019, EM-K020, EM-K021, EM-K022, EM-K023, EM-K024, EM-K025, EM-K030, EM-K031, EM-K032, EM-K033, EM-K034, EM-K036, EM-K037, EM-K038
- **Bedingt:** EM-K004 (färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K005 (färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K016 (zwei thematische Schichten: rhythmische Komplementarität prüfen (Mission-Prinzip)); EM-K027 (zwei thematische Schichten: rhythmische Komplementarität prüfen (Mission-Prinzip)); EM-K029 (zwei thematische Schichten: rhythmische Komplementarität prüfen (Mission-Prinzip)); EM-K035 (färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord))
- **Ungeeignet:** EM-K026 (gleiche Rolle HM doppelt belegt; zwei thematische Hauptstimmen)
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (16 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K029 – Chorartiges Quartengegenmotiv
- **Art:** LYRIK · **Rolle:** GS · **Länge:** 12 Schläge (11520 Ticks) · **Periode:** – Ticks · **Quelle:** EM-M030
- **Tonvorrat:** {♭3, 4, 6, ♭7} · **Register (rel):** +3 … +10 · **Polyphonie:** 1 · **harmonische Absicht:** FAERBT · **thematisch:** ja
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K003, EM-K006, EM-K007, EM-K008, EM-K009, EM-K010, EM-K011, EM-K012, EM-K013, EM-K014, EM-K015, EM-K017, EM-K018, EM-K019, EM-K020, EM-K021, EM-K022, EM-K023, EM-K024, EM-K025, EM-K030, EM-K031, EM-K032, EM-K033, EM-K034, EM-K037, EM-K038
- **Bedingt:** EM-K001 (färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K002 (färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K004 (färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K005 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K016 (zwei thematische Schichten: rhythmische Komplementarität prüfen (Mission-Prinzip)); EM-K026 (zwei thematische Schichten: rhythmische Komplementarität prüfen (Mission-Prinzip)); EM-K027 (zwei thematische Schichten: rhythmische Komplementarität prüfen (Mission-Prinzip)); EM-K028 (zwei thematische Schichten: rhythmische Komplementarität prüfen (Mission-Prinzip)); EM-K035 (färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K036 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord))
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (12 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K030 – Marcato-Blöcke
- **Art:** MEHRSTIMMIG · **Rolle:** KF · **Länge:** 4 Schläge (3840 Ticks) · **Periode:** 3840 Ticks · **Quelle:** EM-H034 + EM-R053
- **Tonvorrat:** {1, 2, ♭3, 4, 5, ♭7} · **Register (rel):** -5 … +17 · **Polyphonie:** 4 · **harmonische Absicht:** FAERBT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K008, EM-K009, EM-K010, EM-K011, EM-K012, EM-K014, EM-K015, EM-K016, EM-K020, EM-K022, EM-K023, EM-K024, EM-K025, EM-K026, EM-K028, EM-K029, EM-K032, EM-K033, EM-K034, EM-K037
- **Bedingt:** EM-K013 (inkongruente Perioden 1200/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K017 (inkongruente Perioden 5760/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K018 (inkongruente Perioden 720/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K019 (inkongruente Perioden 5280/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K021 (inkongruente Perioden 720/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K027 (Registerüberlappung 8 HT: Oktavlage trennen); EM-K038 (inkongruente Perioden 3840/4800 Ticks (Phasenversatz beabsichtigt?))
- **Ungeeignet:** EM-K001 (Registerkollision (10 HT Überlappung bei 8 Stimmen); färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K002 (Registerkollision (20 HT Überlappung bei 8 Stimmen); färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K003 (Registerkollision (22 HT Überlappung bei 8 Stimmen)); EM-K004 (Registerkollision (22 HT Überlappung bei 8 Stimmen); färbendes Modul bringt 4 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K005 (Registerkollision (22 HT Überlappung bei 10 Stimmen); färbendes Modul bringt 4 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K006 (Registerkollision (22 HT Überlappung bei 8 Stimmen)); EM-K007 (Registerkollision (13 HT Überlappung bei 8 Stimmen)); EM-K031 (Registerkollision (12 HT Überlappung bei 8 Stimmen)); EM-K035 (Registerkollision (20 HT Überlappung bei 10 Stimmen); färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K036 (Registerkollision (21 HT Überlappung bei 8 Stimmen); färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord))
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (4 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K031 – Notenblöcke pochend
- **Art:** MEHRSTIMMIG · **Rolle:** KF · **Länge:** 4 Schläge (3840 Ticks) · **Periode:** 3840 Ticks · **Quelle:** EM-H006 + EM-R054
- **Tonvorrat:** {1, 2, ♭3, 4, 5, ♭6} · **Register (rel):** +0 … +12 · **Polyphonie:** 4 · **harmonische Absicht:** FAERBT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K008, EM-K009, EM-K010, EM-K011, EM-K012, EM-K014, EM-K015, EM-K016, EM-K020, EM-K022, EM-K023, EM-K024, EM-K025, EM-K026, EM-K028, EM-K029, EM-K032, EM-K033, EM-K034, EM-K037
- **Bedingt:** EM-K013 (inkongruente Perioden 1200/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K017 (inkongruente Perioden 5760/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K018 (inkongruente Perioden 720/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K019 (inkongruente Perioden 5280/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K021 (inkongruente Perioden 720/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K027 (Registerüberlappung 8 HT: Oktavlage trennen); EM-K038 (inkongruente Perioden 3840/4800 Ticks (Phasenversatz beabsichtigt?))
- **Ungeeignet:** EM-K001 (Registerkollision (10 HT Überlappung bei 8 Stimmen); färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K002 (Registerkollision (12 HT Überlappung bei 8 Stimmen); färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K003 (Registerkollision (12 HT Überlappung bei 8 Stimmen)); EM-K004 (Registerkollision (12 HT Überlappung bei 8 Stimmen); färbendes Modul bringt 4 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K005 (Registerkollision (12 HT Überlappung bei 10 Stimmen); färbendes Modul bringt 4 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K006 (Registerkollision (12 HT Überlappung bei 8 Stimmen)); EM-K007 (Registerkollision (12 HT Überlappung bei 8 Stimmen)); EM-K030 (Registerkollision (12 HT Überlappung bei 8 Stimmen)); EM-K035 (Registerkollision (12 HT Überlappung bei 10 Stimmen); färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K036 (Registerkollision (12 HT Überlappung bei 8 Stimmen); färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord))
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (4 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K032 – Stich: Schlag und Antwort
- **Art:** RHYTHMUS · **Rolle:** ST · **Länge:** 4 Schläge (3840 Ticks) · **Periode:** 3840 Ticks · **Quelle:** EM-R016
- **Tonvorrat:** {– (Stich)} · **Register (rel):** – · **Polyphonie:** 1 · **harmonische Absicht:** NEUTRAL · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K001, EM-K002, EM-K003, EM-K004, EM-K005, EM-K006, EM-K007, EM-K008, EM-K009, EM-K010, EM-K011, EM-K012, EM-K014, EM-K015, EM-K016, EM-K020, EM-K022, EM-K023, EM-K024, EM-K025, EM-K026, EM-K027, EM-K028, EM-K029, EM-K030, EM-K031, EM-K033, EM-K034, EM-K035, EM-K036, EM-K037
- **Bedingt:** EM-K013 (inkongruente Perioden 1200/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K017 (inkongruente Perioden 5760/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K018 (inkongruente Perioden 720/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K019 (inkongruente Perioden 5280/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K021 (inkongruente Perioden 720/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K038 (inkongruente Perioden 3840/4800 Ticks (Phasenversatz beabsichtigt?))
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (4 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K033 – Stich: Halbtaktstoß
- **Art:** RHYTHMUS · **Rolle:** ST · **Länge:** 4 Schläge (3840 Ticks) · **Periode:** 3840 Ticks · **Quelle:** EM-R061
- **Tonvorrat:** {– (Stich)} · **Register (rel):** – · **Polyphonie:** 1 · **harmonische Absicht:** NEUTRAL · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K001, EM-K002, EM-K003, EM-K004, EM-K005, EM-K006, EM-K007, EM-K008, EM-K009, EM-K010, EM-K011, EM-K012, EM-K014, EM-K015, EM-K016, EM-K020, EM-K022, EM-K023, EM-K024, EM-K025, EM-K026, EM-K027, EM-K028, EM-K029, EM-K030, EM-K031, EM-K032, EM-K034, EM-K035, EM-K036, EM-K037
- **Bedingt:** EM-K013 (inkongruente Perioden 1200/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K017 (inkongruente Perioden 5760/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K018 (inkongruente Perioden 720/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K019 (inkongruente Perioden 5280/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K021 (inkongruente Perioden 720/3840 Ticks (Phasenversatz beabsichtigt?)); EM-K038 (inkongruente Perioden 3840/4800 Ticks (Phasenversatz beabsichtigt?))
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (4 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K034 – Stich: ametrisch
- **Art:** RHYTHMUS · **Rolle:** ST · **Länge:** 8 Schläge (7680 Ticks) · **Periode:** 7680 Ticks (ametrisch) · **Quelle:** EM-R041
- **Tonvorrat:** {– (Stich)} · **Register (rel):** – · **Polyphonie:** 1 · **harmonische Absicht:** NEUTRAL · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K001, EM-K002, EM-K003, EM-K004, EM-K005, EM-K006, EM-K007, EM-K008, EM-K009, EM-K010, EM-K011, EM-K012, EM-K013, EM-K014, EM-K015, EM-K016, EM-K017, EM-K018, EM-K019, EM-K020, EM-K021, EM-K022, EM-K023, EM-K024, EM-K025, EM-K026, EM-K027, EM-K028, EM-K029, EM-K030, EM-K031, EM-K032, EM-K033, EM-K035, EM-K036, EM-K037, EM-K038
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (8 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K035 – Ganztonfeld schwebend
- **Art:** PULSLOS · **Rolle:** LF · **Länge:** 16 Schläge (15360 Ticks) · **Periode:** 15360 Ticks · **Quelle:** EM-H071
- **Tonvorrat:** {1, 2, 3, ♯4/♭5, ♭6, ♭7} · **Register (rel):** -4 … +16 · **Polyphonie:** 6 · **harmonische Absicht:** TRAEGT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K008, EM-K009, EM-K010, EM-K011, EM-K012, EM-K014, EM-K015, EM-K020, EM-K022, EM-K023, EM-K024, EM-K025, EM-K032, EM-K033, EM-K034, EM-K037
- **Bedingt:** EM-K013 (inkongruente Perioden 1200/15360 Ticks (Phasenversatz beabsichtigt?)); EM-K016 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K017 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord); inkongruente Perioden 5760/15360 Ticks (Phasenversatz beabsichtigt?)); EM-K018 (inkongruente Perioden 720/15360 Ticks (Phasenversatz beabsichtigt?)); EM-K019 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord); inkongruente Perioden 5280/15360 Ticks (Phasenversatz beabsichtigt?)); EM-K021 (inkongruente Perioden 720/15360 Ticks (Phasenversatz beabsichtigt?)); EM-K026 (färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K028 (färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K029 (färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K038 (inkongruente Perioden 15360/4800 Ticks (Phasenversatz beabsichtigt?))
- **Ungeeignet:** EM-K001 (gleiche Rolle LF doppelt belegt; Registerkollision (10 HT Überlappung bei 10 Stimmen)); EM-K002 (gleiche Rolle LF doppelt belegt; Registerkollision (19 HT Überlappung bei 10 Stimmen)); EM-K003 (gleiche Rolle LF doppelt belegt; Registerkollision (20 HT Überlappung bei 10 Stimmen)); EM-K004 (gleiche Rolle LF doppelt belegt; Registerkollision (20 HT Überlappung bei 10 Stimmen)); EM-K005 (gleiche Rolle LF doppelt belegt; Registerkollision (20 HT Überlappung bei 12 Stimmen)); EM-K006 (Registerkollision (20 HT Überlappung bei 10 Stimmen)); EM-K007 (Registerkollision (13 HT Überlappung bei 10 Stimmen)); EM-K027 (Registerkollision (8 HT Überlappung bei 7 Stimmen); färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K030 (Registerkollision (20 HT Überlappung bei 10 Stimmen); färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K031 (Registerkollision (12 HT Überlappung bei 10 Stimmen); färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K036 (gleiche Rolle LF doppelt belegt; Registerkollision (20 HT Überlappung bei 10 Stimmen))
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (16 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K036 – Plagal-Terzkette (Dur)
- **Art:** KLANG · **Rolle:** LF · **Länge:** 32 Schläge (30720 Ticks) · **Periode:** 30720 Ticks · **Quelle:** EM-H016
- **Tonvorrat:** {1, 2, 3, 4, 5, 6} · **Register (rel):** -5 … +16 · **Polyphonie:** 4 · **harmonische Absicht:** TRAEGT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K008, EM-K009, EM-K010, EM-K011, EM-K012, EM-K014, EM-K015, EM-K016, EM-K020, EM-K022, EM-K023, EM-K024, EM-K025, EM-K028, EM-K032, EM-K033, EM-K034, EM-K037
- **Bedingt:** EM-K013 (inkongruente Perioden 1200/30720 Ticks (Phasenversatz beabsichtigt?)); EM-K017 (inkongruente Perioden 5760/30720 Ticks (Phasenversatz beabsichtigt?)); EM-K018 (inkongruente Perioden 720/30720 Ticks (Phasenversatz beabsichtigt?)); EM-K019 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord); inkongruente Perioden 5280/30720 Ticks (Phasenversatz beabsichtigt?)); EM-K021 (inkongruente Perioden 720/30720 Ticks (Phasenversatz beabsichtigt?)); EM-K026 (färbendes Modul bringt 3 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K027 (Registerüberlappung 8 HT: Oktavlage trennen; färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K029 (färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K038 (inkongruente Perioden 30720/4800 Ticks (Phasenversatz beabsichtigt?))
- **Ungeeignet:** EM-K001 (gleiche Rolle LF doppelt belegt; Registerkollision (10 HT Überlappung bei 8 Stimmen)); EM-K002 (gleiche Rolle LF doppelt belegt; Registerkollision (20 HT Überlappung bei 8 Stimmen)); EM-K003 (gleiche Rolle LF doppelt belegt; Registerkollision (21 HT Überlappung bei 8 Stimmen)); EM-K004 (gleiche Rolle LF doppelt belegt; Registerkollision (21 HT Überlappung bei 8 Stimmen)); EM-K005 (gleiche Rolle LF doppelt belegt; Registerkollision (21 HT Überlappung bei 10 Stimmen)); EM-K006 (Registerkollision (21 HT Überlappung bei 8 Stimmen)); EM-K007 (Registerkollision (13 HT Überlappung bei 8 Stimmen)); EM-K030 (Registerkollision (21 HT Überlappung bei 8 Stimmen); färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K031 (Registerkollision (12 HT Überlappung bei 8 Stimmen); färbendes Modul bringt 2 Fremdtöne ein (T/F-Prüfung je Akkord)); EM-K035 (gleiche Rolle LF doppelt belegt; Registerkollision (20 HT Überlappung bei 10 Stimmen))
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (32 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K037 – Dorischer Quintfallbass
- **Art:** BASS · **Rolle:** LB · **Länge:** 32 Schläge (30720 Ticks) · **Periode:** – Ticks · **Quelle:** EM-B028
- **Tonvorrat:** {1, ♭3, 4, ♭7} · **Register (rel):** -14 … -7 · **Polyphonie:** 1 · **harmonische Absicht:** TRAEGT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K001, EM-K002, EM-K003, EM-K004, EM-K005, EM-K006, EM-K007, EM-K011, EM-K012, EM-K013, EM-K014, EM-K015, EM-K016, EM-K017, EM-K018, EM-K019, EM-K020, EM-K021, EM-K022, EM-K023, EM-K024, EM-K025, EM-K026, EM-K027, EM-K028, EM-K029, EM-K030, EM-K031, EM-K032, EM-K033, EM-K034, EM-K035, EM-K036, EM-K038
- **Ungeeignet:** EM-K008 (gleiche Rolle LB doppelt belegt); EM-K009 (gleiche Rolle LB doppelt belegt); EM-K010 (gleiche Rolle LB doppelt belegt; Bass-F-Schicht gegen tragenden Bass: nur bei Z ≥ 0,5)
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (32 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

### EM-K038 – Tritonus-Dyaden hoch
- **Art:** EXPERIMENT · **Rolle:** TU · **Länge:** 16 Schläge (15360 Ticks) · **Periode:** 4800 Ticks · **Quelle:** EM-C005 + EM-R026
- **Tonvorrat:** {1, ♯4/♭5} · **Register (rel):** +12 … +23 · **Polyphonie:** 1 · **harmonische Absicht:** FSCHICHT · **thematisch:** nein
- **Identität:** Quelle + Rolle + Periode; Modul bleibt unverändert, Kombination wechselt (EM-T011)
- **Frei kombinierbar mit:** EM-K008, EM-K009, EM-K010, EM-K013, EM-K027, EM-K028, EM-K029, EM-K034, EM-K037
- **Bedingt:** EM-K001 (inkongruente Perioden 15360/4800 Ticks (Phasenversatz beabsichtigt?)); EM-K002 (inkongruente Perioden 15360/4800 Ticks (Phasenversatz beabsichtigt?)); EM-K003 (inkongruente Perioden 15360/4800 Ticks (Phasenversatz beabsichtigt?)); EM-K004 (inkongruente Perioden 30720/4800 Ticks (Phasenversatz beabsichtigt?)); EM-K005 (inkongruente Perioden 30720/4800 Ticks (Phasenversatz beabsichtigt?)); EM-K006 (inkongruente Perioden 15360/4800 Ticks (Phasenversatz beabsichtigt?)); EM-K007 (inkongruente Perioden 15360/4800 Ticks (Phasenversatz beabsichtigt?)); EM-K011 (inkongruente Perioden 3840/4800 Ticks (Phasenversatz beabsichtigt?)); EM-K012 (inkongruente Perioden 3840/4800 Ticks (Phasenversatz beabsichtigt?)); EM-K014 (inkongruente Perioden 3840/4800 Ticks (Phasenversatz beabsichtigt?)); EM-K015 (inkongruente Perioden 3840/4800 Ticks (Phasenversatz beabsichtigt?)); EM-K016 (inkongruente Perioden 3840/4800 Ticks (Phasenversatz beabsichtigt?)) …
- **Austausch/Wiederholung/Unterbrechung:** nur an Modulgrenzen (16 Schläge); Wiederholung unbegrenzt (Stasis zulässig); Unterbrechung ganzer Module als Reduktion; bei inkongruenter Periode läuft das Modul über die Grenze bis zum eigenen Zyklusende weiter

**Geprüfte Dreierkombinationen:** 5145 frei, 945 bedingt, 2346 durch ein ungeeignetes Paar ausgeschlossen. Beispiele frei kombinierbarer Dreiergruppen: EM-K001 + EM-K008 + EM-K011; EM-K001 + EM-K008 + EM-K012; EM-K001 + EM-K008 + EM-K014; EM-K001 + EM-K008 + EM-K015; EM-K001 + EM-K008 + EM-K020; EM-K001 + EM-K008 + EM-K022; EM-K001 + EM-K008 + EM-K023; EM-K001 + EM-K008 + EM-K024; EM-K001 + EM-K008 + EM-K025; EM-K001 + EM-K008 + EM-K028.

## 14. EF – Ereignisfelder

Gelenkte Improvisation, kein Zufall (Vertiefung 4.2): Material (Zelle) und Rahmen sind fixiert, Zeitpunkte werden regelgebunden gewählt (deterministischer Seed je Studie). Dichten und Mindestabstände sind je Feld definiert; es gibt keine globale Stillequote und keine Pflicht-Ankerschicht. Antworten: Imitation (Ton aus derselben Zelle), Widerspruch (Komplementärton bzw. Tritonus), Schweigen. Geräuschhaftes läuft ausschließlich über ST (Note 36).

### EM-EF01 – Pulsloses Moll-add9-Feld mit seltenen Tupfern
- **Säule:** A · **Zelle:** EM-C010 · **Rollen:** TU · **Register (rel):** +12 … +31
- **Dichte:** 0–2 Ereignisse/Takt · **Mindestabstand:** 1440 Ticks · **Antwort (Imitation/Widerspruch/Schweigen):** keine Antwortlogik · **Antwortfenster:** – Ticks
- **Anker:** LF Moll-add9 offen (EM-H002) · **Stille:** keine feste Stillephase
- **XYZ-Anker:** 0,45 / 0,15 / 0,25 · **Studie:** EM-EF01 (16 Takte)
- **Evidenz:** I – begründete Interpretation (immobilità dinamica + Einzelklang); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-EF02 – Ereignis und Echo
- **Säule:** AB · **Zelle:** EM-C030 · **Rollen:** TU KF · **Register (rel):** +12 … +31
- **Dichte:** 0–2 Ereignisse/Takt · **Mindestabstand:** 1920 Ticks · **Antwort (Imitation/Widerspruch/Schweigen):** (1.0, 0.0, 0.0) · **Antwortfenster:** (480, 960) Ticks
- **Anker:** LB Tonikapedal · **Stille:** keine feste Stillephase
- **XYZ-Anker:** 0,40 / 0,20 / 0,30 · **Studie:** EM-EF02 (16 Takte)
- **Evidenz:** I – begründete Interpretation (Echo (NPR)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-EF03 – Ruf und Zustimmung
- **Säule:** A · **Zelle:** EM-C028 · **Rollen:** TU GS · **Register (rel):** +7 … +26
- **Dichte:** 1–2 Ereignisse/Takt · **Mindestabstand:** 1920 Ticks · **Antwort (Imitation/Widerspruch/Schweigen):** (0.8, 0.0, 0.2) · **Antwortfenster:** (960, 1920) Ticks
- **Anker:** LF dorisch (EM-H007) · **Stille:** keine feste Stillephase
- **XYZ-Anker:** 0,55 / 0,25 / 0,30 · **Studie:** EM-EF03 (16 Takte)
- **Evidenz:** N – nachgewiesenes Verfahren (Gesprächslogik: zustimmen (Wilcox)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-EF04 – Ruf und Widerspruch
- **Säule:** AB · **Zelle:** EM-C010 · **Rollen:** TU GS · **Register (rel):** +7 … +29
- **Dichte:** 1–2 Ereignisse/Takt · **Mindestabstand:** 1440 Ticks · **Antwort (Imitation/Widerspruch/Schweigen):** (0.2, 0.7, 0.1) · **Antwortfenster:** (480, 1440) Ticks
- **Anker:** LF Moll-add9 (geschützt) · **Stille:** keine feste Stillephase
- **XYZ-Anker:** 0,40 / 0,30 / 0,55 · **Studie:** EM-EF04 (16 Takte)
- **Evidenz:** N – nachgewiesenes Verfahren (Gesprächslogik: widersprechen (Wilcox)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-EF05 – Ausbleibende Antwort
- **Säule:** B · **Zelle:** EM-C015 · **Rollen:** TU · **Register (rel):** +5 … +31
- **Dichte:** 0–1 Ereignisse/Takt · **Mindestabstand:** 3840 Ticks · **Antwort (Imitation/Widerspruch/Schweigen):** (0.1, 0.1, 0.8) · **Antwortfenster:** (960, 1920) Ticks
- **Anker:** ankerlos (Kohärenz über die Zelle) · **Stille:** je 2 Takt(e) nach 6 Takten
- **XYZ-Anker:** 0,20 / 0,15 / 0,50 · **Studie:** EM-EF05 (16 Takte)
- **Evidenz:** I – begründete Interpretation (Schweigen als Antwort); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-EF06 – Konsonanter Anker, experimentelle Umgebung
- **Säule:** AB · **Zelle:** EM-C035 · **Rollen:** TU KF · **Register (rel):** -2 … +36
- **Dichte:** 1–3 Ereignisse/Takt · **Mindestabstand:** 720 Ticks · **Antwort (Imitation/Widerspruch/Schweigen):** (0.3, 0.4, 0.3) · **Antwortfenster:** (240, 960) Ticks
- **Anker:** LF Dur-add9 geschützt + LB Pedal · **Stille:** keine feste Stillephase
- **XYZ-Anker:** 0,70 / 0,30 / 0,60 · **Studie:** EM-EF06 (16 Takte)
- **Evidenz:** N – nachgewiesenes Verfahren (doppelte Ästhetik (De Rosa)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-EF07 – Dissonanter Anker (Tritonus-Pedal)
- **Säule:** B · **Zelle:** EM-C014 · **Rollen:** TU · **Register (rel):** +5 … +29
- **Dichte:** 0–2 Ereignisse/Takt · **Mindestabstand:** 1440 Ticks · **Antwort (Imitation/Widerspruch/Schweigen):** (0.4, 0.3, 0.3) · **Antwortfenster:** (480, 1440) Ticks
- **Anker:** LB Tritonus-Pedal (EM-B005) · **Stille:** keine feste Stillephase
- **XYZ-Anker:** 0,15 / 0,30 / 0,55 · **Studie:** EM-EF07 (16 Takte)
- **Evidenz:** I – begründete Interpretation (dissonanter Anker); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-EF08 – Ankerlose, kohärente Textur (eine Zelle)
- **Säule:** B · **Zelle:** EM-C036 · **Rollen:** TU KF · **Register (rel):** +0 … +36
- **Dichte:** 1–3 Ereignisse/Takt · **Mindestabstand:** 600 Ticks · **Antwort (Imitation/Widerspruch/Schweigen):** (0.5, 0.3, 0.2) · **Antwortfenster:** (240, 720) Ticks
- **Anker:** ankerlos (Kohärenz über die Zelle) · **Stille:** keine feste Stillephase
- **XYZ-Anker:** 0,30 / 0,30 / 0,70 · **Studie:** EM-EF08 (16 Takte)
- **Evidenz:** N – nachgewiesenes Verfahren (Zellbindung statt Anker (Corbella: ineinanderpassend)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-EF09 – Lange Stille mit Einzelglocke
- **Säule:** AB · **Zelle:** EM-C030 · **Rollen:** TU ST · **Register (rel):** +12 … +28
- **Dichte:** 0–1 Ereignisse/Takt · **Mindestabstand:** 7680 Ticks · **Antwort (Imitation/Widerspruch/Schweigen):** keine Antwortlogik · **Antwortfenster:** – Ticks
- **Anker:** ankerlos (Kohärenz über die Zelle) · **Stille:** je 4 Takt(e) nach 4 Takten
- **XYZ-Anker:** 0,40 / 0,10 / 0,30 · **Studie:** EM-EF09 (16 Takte)
- **Evidenz:** N – nachgewiesenes Verfahren (Stille als Ereignis (Wilcox)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-EF10 – Gestaffelte Klangereignisse (Akkord tropft)
- **Säule:** A · **Zelle:** EM-C010 · **Rollen:** TU · **Register (rel):** +0 … +26
- **Dichte:** 2–4 Ereignisse/Takt · **Mindestabstand:** 480 Ticks · **Antwort (Imitation/Widerspruch/Schweigen):** keine Antwortlogik · **Antwortfenster:** – Ticks
- **Anker:** ankerlos (Kohärenz über die Zelle) · **Stille:** keine feste Stillephase · gestaffelte Klangereignisse
- **XYZ-Anker:** 0,45 / 0,25 / 0,25 · **Studie:** EM-EF10 (16 Takte)
- **Evidenz:** N – nachgewiesenes Verfahren (gestaffelte Einsätze (Lyne)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-EF11 – Lyrische Einzelereignisse (Seufzer-Splitter)
- **Säule:** A · **Zelle:** EM-C009 · **Rollen:** TU GS · **Register (rel):** +12 … +27
- **Dichte:** 0–1 Ereignisse/Takt · **Mindestabstand:** 2880 Ticks · **Antwort (Imitation/Widerspruch/Schweigen):** (0.6, 0.0, 0.4) · **Antwortfenster:** (960, 1920) Ticks
- **Anker:** LF i-add9 → ♭VI-maj7 (EM-U002) · **Stille:** keine feste Stillephase
- **XYZ-Anker:** 0,40 / 0,20 / 0,25 · **Studie:** EM-EF11 (16 Takte)
- **Evidenz:** I – begründete Interpretation (Fragment als Ereignis); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-EF12 – Kontrast: hoch gegen tief
- **Säule:** B · **Zelle:** EM-C037 · **Rollen:** TU KF · **Register (rel):** -12 … +36
- **Dichte:** 1–2 Ereignisse/Takt · **Mindestabstand:** 1440 Ticks · **Antwort (Imitation/Widerspruch/Schweigen):** (0.0, 1.0, 0.0) · **Antwortfenster:** (240, 480) Ticks
- **Anker:** ankerlos (Kohärenz über die Zelle) · **Stille:** keine feste Stillephase
- **XYZ-Anker:** 0,25 / 0,45 / 0,60 · **Studie:** EM-EF12 (16 Takte)
- **Evidenz:** E – eigenständige Gestaltung (Kontrast der Register); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-EF13 – Kontrolliert chaotische Textur (komponierte Unordnung)
- **Säule:** B · **Zelle:** EM-C035 · **Rollen:** TU KF AR · **Register (rel):** -5 … +36
- **Dichte:** 3–6 Ereignisse/Takt · **Mindestabstand:** 240 Ticks · **Antwort (Imitation/Widerspruch/Schweigen):** (0.3, 0.5, 0.2) · **Antwortfenster:** (120, 480) Ticks
- **Anker:** LF pseudoserielle Fläche · **Stille:** je 1 Takt(e) nach 8 Takten
- **XYZ-Anker:** 0,30 / 0,70 / 0,85 · **Studie:** EM-EF13 (16 Takte)
- **Evidenz:** N – nachgewiesenes Verfahren (totale Serialisierung (Morricone zu Bird)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-EF14 – B-A-C-H-Streuung, ametrisch
- **Säule:** B · **Zelle:** EM-C023 · **Rollen:** TU · **Register (rel):** +9 … +33
- **Dichte:** 1–2 Ereignisse/Takt · **Mindestabstand:** 960 Ticks · **Antwort (Imitation/Widerspruch/Schweigen):** (0.5, 0.2, 0.3) · **Antwortfenster:** (480, 1440) Ticks
- **Anker:** ankerlos (Kohärenz über die Zelle) · **Stille:** keine feste Stillephase
- **XYZ-Anker:** 0,40 / 0,25 / 0,50 · **Studie:** EM-EF14 (16 Takte)
- **Evidenz:** N – nachgewiesenes Verfahren (Kode als Zelle); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-EF15 – Akuter Horror: Ballung und Stich
- **Säule:** B · **Zelle:** EM-C021 · **Rollen:** KF ST · **Register (rel):** -12 … +36
- **Dichte:** 1–3 Ereignisse/Takt · **Mindestabstand:** 480 Ticks · **Antwort (Imitation/Widerspruch/Schweigen):** (0.0, 0.6, 0.4) · **Antwortfenster:** (120, 360) Ticks
- **Anker:** ankerlos (Kohärenz über die Zelle) · **Stille:** je 1 Takt(e) nach 4 Takten
- **XYZ-Anker:** 0,10 / 0,90 / 0,90 · **Studie:** EM-EF15 (16 Takte)
- **Evidenz:** I – begründete Interpretation (Verdichtung (Contamination) + Stille); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

### EM-EF16 – Gesprächsfeld mit Kleinsext-Anker (Bird-Prinzip)
- **Säule:** AB · **Zelle:** EM-C035 · **Rollen:** TU KF · **Register (rel):** -2 … +33
- **Dichte:** 1–2 Ereignisse/Takt · **Mindestabstand:** 960 Ticks · **Antwort (Imitation/Widerspruch/Schweigen):** (0.4, 0.4, 0.2) · **Antwortfenster:** (480, 1440) Ticks
- **Anker:** TU repetierte kleine Sexte + LF Haltepitch · **Stille:** keine feste Stillephase
- **XYZ-Anker:** 0,45 / 0,30 / 0,55 · **Studie:** EM-EF16 (16 Takte)
- **Evidenz:** N – nachgewiesenes Verfahren (Sext-Dyade und Haltepitch als Anker (Bissett)); die konkrete Vorlage selbst ist eine eigenständige Konstruktion (E)

## 15. T – Transformationsverfahren

| ID | Verfahren | Wirkung | Parameter | Invarianten | Gefahren | Evidenz |
|---|---|---|---|---|---|---|
| EM-T001 | Permutation | Reihenfolge einer Zelle ändern | Ordnung aus zulässigen Permutationen; keine sofortige Wiederholung | Tonhöhenmenge, Intervallvektor | zwanghafte Dauerpermutation zerstört Wiedererkennbarkeit | N – Mikrozelle ohne feste Tonfolge (filmmusicnotes) |
| EM-T002 | Oktavverlagerung | Einzeltöne um ±12/±24 versetzen | max. Versatz je Ton (Z-abhängig), Rollenregister | Pitch-Class-Menge | Registerkollision mit anderen Rollen | N – letzter Ton oktavversetzt (filmmusicnotes) |
| EM-T003 | Rollenwanderung | Material wechselt die Rolle (TU→GS→HM, KB→AR) | Zielrolle, Registeranpassung | Zellidentität bzw. Motivkontur | zwei Rollen gleichzeitig mit identischem Material ohne Absicht | N – Jills Thema: Einzelstimme → Orchester (OUP-Blog) |
| EM-T004 | Fragmentierung/Trunkierung | Motiv auf erste n Töne kürzen | n (2–3 typisch) | Kopfmotiv | Fragmente ohne Kopf verlieren Identität | N – Nitti-Motiv oft auf 2–3 Töne gekürzt (Filmtracks) |
| EM-T005 | Additive Enthüllung | Motiv wächst über Stufen (2→4→7→n Töne) | Stufenfolge, Wiederholungen je Stufe | Reihenfolge der Töne | zu schnelle Enthüllung = Eskalation | N – Nitti 2→4→7→10 (Filmtracks) |
| EM-T006 | Rhythmische Kontraktion | Dauern schrittweise verkürzen | Faktor je Durchlauf (z. B. 0,75) | Tonfolge | Hektik; nur bei steigendem Z oder als Episode | N – rhythmische Kontraktionen (Wilcox: Drittes Konzert) |
| EM-T007 | Rhythmische Extension | Dauern schrittweise dehnen | Faktor je Durchlauf (z. B. 1,5) | Tonfolge | Zerfall in Einzeltöne | N – Extensionen (Wilcox); Zelle von 2 auf 3 Takte gedehnt (filmmusicnotes) |
| EM-T008 | Phasenversatz | Periode einer Schicht ≠ Taktlänge | Periodenlänge in Ticks | Material der Schicht | Kollision mit Dialogakzenten | N – 3 gegen 4 (Wilcox: Se telefonando) |
| EM-T009 | Harmonische Umfärbung | gleicher Ton/gleiches Motiv über neuem Unterbau | Zielharmonie aus H/U | Melodietöne | Unbeabsichtigte F/U-Töne | I – identische Melodie über verändertem Unterbau |
| EM-T010 | Farbtonaustausch | Austauschton einer KERN-Zelle wechseln | Austauschpaar, Intervall in Takten | Kerntöne | Wechsel zu häufig = Flackern | N – Ut: wechselnder 7. Ton (Wilcox) |
| EM-T011 | Modulrotation | Kombination aktiver Module an Modulgrenzen wechseln | Pool, Mindestabstand bis Wiederholung | Anzahl aktiver Module bei festem Y | Kombination ohne Kompatibilitätsprüfung | N – partitura multipla (Corbella) |
| EM-T012 | Gestaffelter Klangaufbau | Stimmen eines Klangs nacheinander einsetzen | Einsatzabstände je Stimme | Klangidentität | zu kleine Abstände wirken wie Fehler | N – gestaffelte Streichereinsätze (Lyne, Presseheft Lolita) |
| EM-T013 | Reduktion | Schichten schrittweise entfernen | Reihenfolge der Rollen, Ziel-Schichtzahl | verbleibender Kern | Reduktion als erzwungene Deeskalation bei festem XYZ | N – Reduktion als Schluss (Wilcox: Missa) |
| EM-T014 | Wiederaufnahme | entfernte Schichten zurückholen | Reihenfolge, Abstand | Identität des Kerns | erzwungene Eskalation | I – Reduktion und Wiederaufnahme (Carpenter-Strategie, Morricone-Relevanz hoch) |
| EM-T015 | Geschützte harmonische Identität | Schicht bleibt intern konsonant, auch gegen dissonante Nachbarschicht | Schicht-Harmonie (lokal) | lokale Tonfunktionen A/T | Verwechslung lokal/global in der Prüfung | N – doppelte Ästhetik (De Rosa) |
| EM-T016 | Langfristige Stasis | Material bleibt, nur Parameter innerhalb der Rolle atmen | Velocity-/Registerbereich | Harmonie, Zelle, Tempo | Monotonie ohne Mikroveränderung | N – immobilità dinamica (Miceli, Smith) |
| EM-T017 | Halbtonrückung (nur Y-gekoppelt) | Block einen Halbton höher | Auslöser: Y-Änderung | Intervallstruktur | nie automatisch bei festem XYZ | N – Durchläufe je einen Halbton höher (Wilcox: Vuoto d'anima piena) |
| EM-T018 | Motivverkürzung über Zeit | Motiv wird über Durchläufe kürzer (Gegenrichtung zu T005) | Stufenfolge | Kopfmotiv | Verschwinden ohne Absicht | I – Reduktion auf Zelle (Wilcox) |
| EM-T019 | Inversion (Spiegelung) | Intervallrichtung umkehren | Achse | Intervallklasse; Tonhöhenmenge nur bei symmetrischen Zellen | Inversion ≠ Permutation, außer bei symmetrischer Menge | N – Intervallbeziehungen auch invertiert (filmmusicnotes) |
| EM-T020 | Rotation der Ordnung | zyklische Verschiebung einer geordneten Zelle | Schrittweite | zyklische Ordnung | bei ORD-Zellen die einzige zulässige Umordnung | E – Rotation (Carpenter-Strategie) |

## 16. S – Modellstudien und Langzeitentwicklung

57 Modellstudien (zusätzlich 16 EF-Studien). Ohne HM und GS: 41; ohne Arpeggio (AR): 43; ohne durchlaufenden Puls (keine AR/KB-Schicht): 39. Längen: 10× 8 Takte, 34× 16 Takte, 5× 32 Takte, 8× 64 Takte. Alle Studien liegen als MIDI (eine Spur je Rolle, benannt „Rolle – Bezeichnung“) und als Ereignisdaten in der CSV vor.

**Entwicklungsstrategien bei unveränderter XYZ-Position:** Stasis, Rotation, Atmung, Wanderung, Umfärbung, Ereignisfeld, Blockverschiebung, Reduktion und Wiederaufnahme sowie ergänzend Zellpermutation, additive Motiventhüllung, Modul-Kombinatorik, Motivverkürzung, rhythmische Kontraktion/Extension, Wechsel einzelner Farbtöne. Es gibt keine verpflichtenden Veränderungen nach festen Zeitintervallen und keine erzwungene Eskalation oder Deeskalation; die in den Studien gewählten Zeitpunkte sind Beispiele. Verdichtung (EM-S014) und Polychord-Schatten (EM-S049) sind ausdrücklich an XYZ-Übergänge gebunden.

### EM-S001 – Lyrische Melancholie ohne Hauptmelodie
- **Säule:** A · **Länge:** 16 Takte · **Tonika:** A · **Modus:** aeolisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,40 / 0,30 / 0,20
- **Rollenspuren:** LF, LB, TU · **Ereignisse:** 64 (4,00 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H004 (gestaffelt 0/480/960/1440) · cell EM-C009 EM-R018 TU (T3–16; Permutation alle 4 Takte)
- **Entwicklung:** Stasis, Umfärbung
- **Tonfunktionen (gezählt):** A 55, T 9, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 3
- **Datei:** EM-S001_Lyrische_Melancholie_ohne_Hauptmelodie.mid

### EM-S002 – Moll-add9 mit liegenden Gemeinsamtönen (liegendes H, fünf Bedeutungen)
- **Säule:** A · **Länge:** 16 Takte · **Tonika:** A · **Modus:** aeolisch · **Tempo:** 58 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,50 / 0,30 / 0,25
- **Rollenspuren:** LF, LB, TU · **Ereignisse:** 38 (2,40 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** uchain EM-U029 · cell EM-C001 EM-R019 TU (T5–16)
- **Entwicklung:** Umfärbung, Stasis
- **Tonfunktionen (gezählt):** A 38, T 0, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 16
- **Datei:** EM-S002_Moll_add9_mit_liegenden_Gemeinsamtoenen_liegendes_H_fuenf_Be.mid

### EM-S003 – Gestaffelte Streicherklänge
- **Säule:** A · **Länge:** 16 Takte · **Tonika:** D · **Modus:** aeolisch · **Tempo:** 56 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,55 / 0,45 / 0,20
- **Rollenspuren:** LF, LB · **Ereignisse:** 36 (2,20 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H010 (gestaffelt 0/960/1920/2880)
- **Entwicklung:** Atmung, gestaffelter Klangaufbau
- **Tonfunktionen (gezählt):** A 36, T 0, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 2
- **Datei:** EM-S003_Gestaffelte_Streicherklaenge.mid

### EM-S004 – Sanfte chromatische Stimmführung über Tonikabass
- **Säule:** A · **Länge:** 16 Takte · **Tonika:** E · **Modus:** dorisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,45 / 0,30 / 0,45
- **Rollenspuren:** LF, LB · **Ereignisse:** 38 (2,40 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** uchain EM-U040
- **Entwicklung:** Wanderung (einer Stimme), Rotation
- **Tonfunktionen (gezählt):** A 38, T 0, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 10
- **Datei:** EM-S004_Sanfte_chromatische_Stimmfuehrung_ueber_Tonikabass.mid

### EM-S005 – Plagale Terzkette mit Gemeinsamton-Bindung
- **Säule:** A · **Länge:** 16 Takte · **Tonika:** D · **Modus:** ionisch · **Tempo:** 62 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,75 / 0,30 / 0,15
- **Rollenspuren:** LF, LB, TU · **Ereignisse:** 52 (3,20 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** uchain EM-U007+EM-U008+EM-U009 · cell EM-C029 EM-R039 TU (T7–16; Permutation alle 4 Takte)
- **Entwicklung:** Rotation
- **Tonfunktionen (gezählt):** A 46, T 6, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 20
- **Datei:** EM-S005_Plagale_Terzkette_mit_Gemeinsamton_Bindung.mid

### EM-S006 – Dorisches Pendel mit Austauschton
- **Säule:** A · **Länge:** 32 Takte · **Tonika:** E · **Modus:** dorisch · **Tempo:** 64 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,55 / 0,35 / 0,20
- **Rollenspuren:** LF, LB, TU · **Ereignisse:** 151 (4,70 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H007 · bass EM-B038 · cell EM-C026 EM-R047 TU (T5–32; Farbtonwechsel alle 8 Takte)
- **Entwicklung:** Stasis, Farbtonaustausch
- **Tonfunktionen (gezählt):** A 134, T 14, V 0, F 3 (davon deklariert 3), U 0; Noten über mehrere Harmonien 1
- **Datei:** EM-S006_Dorisches_Pendel_mit_Austauschton.mid

### EM-S007 – Tragische Monumentalität
- **Säule:** A · **Länge:** 16 Takte · **Tonika:** C · **Modus:** moll_gemischt · **Tempo:** 54 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,35 / 0,85 / 0,25
- **Rollenspuren:** LF, LB, HM · **Ereignisse:** 64 (4,00 pro Takt ohne ST) · **ohne HM/GS:** nein · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H041 · bass EM-B034 · motif EM-M014 HM (T5–16)
- **Entwicklung:** Stasis (hohes Y ohne Dichte)
- **Tonfunktionen (gezählt):** A 41, T 23, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 8
- **Datei:** EM-S007_Tragische_Monumentalitaet.mid

### EM-S008 – Schönheit und Bedrohung: Moll-add9 über tiefem Cluster
- **Säule:** AB · **Länge:** 16 Takte · **Tonika:** A · **Modus:** aeolisch · **Tempo:** 58 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,35 / 0,35 / 0,45
- **Rollenspuren:** LF, KF, LB, TU · **Ereignisse:** 49 (3,10 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H091 · cell EM-C009 EM-R049 TU
- **Entwicklung:** Stasis, Ereignisfeld
- **Tonfunktionen (gezählt):** A 45, T 0, V 0, F 0 (davon deklariert 0), U 4; Noten über mehrere Harmonien 5
- **Datei:** EM-S008_Schoenheit_und_Bedrohung_Moll_add9_ueber_tiefem_Cluster.mid

### EM-S009 – Konsonante Spieluhr über dissonanter Fläche
- **Säule:** AB · **Länge:** 16 Takte · **Tonika:** F · **Modus:** ionisch · **Tempo:** 66 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,75 / 0,25 / 0,55
- **Rollenspuren:** KF, LB, AR · **Ereignisse:** 118 (7,40 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** nein · **Puls:** ja
- **Schichten:** harm EM-H066 · harm EM-H020 (geschützte Konsonanz (K)) · bass EM-B005 · motif EM-M043 AR (T3–16; geschützte Konsonanz (K))
- **Entwicklung:** Stasis, geschützte Identität
- **Tonfunktionen (gezählt):** A 88, T 30, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 0
- **Datei:** EM-S009_Konsonante_Spieluhr_ueber_dissonanter_Flaeche.mid

### EM-S010 – Experimentelles Klangfeld (komponierte Unordnung)
- **Säule:** B · **Länge:** 16 Takte · **Tonika:** H · **Modus:** chromatisch · **Tempo:** 70 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,30 / 0,65 / 0,80
- **Rollenspuren:** LF, KF, TU · **Ereignisse:** 111 (6,90 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H073 · ef EM-EF13
- **Entwicklung:** Ereignisfeld
- **Tonfunktionen (gezählt):** A 79, T 32, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 7
- **Datei:** EM-S010_Experimentelles_Klangfeld_komponierte_Unordnung.mid

### EM-S011 – Atonale Textur mit Zellkohärenz
- **Säule:** B · **Länge:** 16 Takte · **Tonika:** F♯ · **Modus:** chromatisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,30 / 0,30 / 0,70
- **Rollenspuren:** LF, KF, TU · **Ereignisse:** 50 (3,10 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H072 · ef EM-EF08
- **Entwicklung:** Ereignisfeld, Stasis
- **Tonfunktionen (gezählt):** A 43, T 7, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 6
- **Datei:** EM-S011_Atonale_Textur_mit_Zellkohaerenz.mid

### EM-S012 – Pulslose Mystery (kalt, hell)
- **Säule:** AB · **Länge:** 16 Takte · **Tonika:** E · **Modus:** ganzton · **Tempo:** 56 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,80 / 0,20 / 0,45
- **Rollenspuren:** LF, LB, TU · **Ereignisse:** 25 (1,60 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H103 · cell EM-C020 EM-R026 TU
- **Entwicklung:** Stasis, Wanderung
- **Tonfunktionen (gezählt):** A 15, T 4, V 0, F 0 (davon deklariert 0), U 6; Noten über mehrere Harmonien 4
- **Datei:** EM-S012_Pulslose_Mystery_kalt_hell.mid

### EM-S013 – Elektronische Zweitonzellen über Basspuls
- **Säule:** B · **Länge:** 32 Takte · **Tonika:** E · **Modus:** phrygisch · **Tempo:** 88 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,25 / 0,45 / 0,40
- **Rollenspuren:** LF, KB, AR · **Ereignisse:** 283 (8,80 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** nein · **Puls:** ja
- **Schichten:** harm EM-H088 · bass EM-B008 (Pause T17–20) · cell EM-C046 EM-R063 AR (T5–32)
- **Entwicklung:** Stasis, Reduktion und Wiederaufnahme
- **Tonfunktionen (gezählt):** A 283, T 0, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 3
- **Datei:** EM-S013_Elektronische_Zweitonzellen_ueber_Basspuls.mid

### EM-S014 – Orchestrale Spannung: Schichtzuwachs mündet in Ballung
- **Säule:** B · **Länge:** 16 Takte · **Tonika:** D · **Modus:** chromatisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,15 / 0,60 / 0,60
- **Rollenspuren:** LF, LB, ST · **Ereignisse:** 58 (2,10 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H090 · bass EM-B001 · st EM-R053 (T9–16)
- **Entwicklung:** Verdichtung (an XYZ-Übergang gebunden)
- **Tonfunktionen (gezählt):** A 34, T 0, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 4
- **Datei:** EM-S014_Orchestrale_Spannung_Schichtzuwachs_muendet_in_Ballung.mid

### EM-S015 – Rhythmische Kraft ohne Hektik (Untouchables-Prinzip, eigene Töne)
- **Säule:** B · **Länge:** 32 Takte · **Tonika:** D · **Modus:** aeolisch · **Tempo:** 96 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,35 / 0,85 / 0,35
- **Rollenspuren:** LF, KB, AR, ST, HM · **Ereignisse:** 892 (26,00 pro Takt ohne ST) · **ohne HM/GS:** nein · **ohne AR:** nein · **Puls:** ja
- **Schichten:** harm EM-H034 · bass EM-B030 · bass EM-B031 (T9–32; Pause T25–26) · cell EM-C011 EM-R013 AR · motif EM-M045 HM (T9–32) · st EM-R016 (Pause T25–26)
- **Entwicklung:** Stasis, Atmung, Reduktion und Wiederaufnahme
- **Tonfunktionen (gezählt):** A 573, T 259, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 2
- **Datei:** EM-S015_Rhythmische_Kraft_ohne_Hektik_Untouchables_Prinzip_eigene_To.mid

### EM-S016 – Langsame Oberstimme über bewegter Unterschicht
- **Säule:** A · **Länge:** 16 Takte · **Tonika:** G · **Modus:** aeolisch · **Tempo:** 72 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,40 / 0,55 / 0,30
- **Rollenspuren:** LF, LB, AR, HM · **Ereignisse:** 231 (14,40 pro Takt ohne ST) · **ohne HM/GS:** nein · **ohne AR:** nein · **Puls:** ja
- **Schichten:** harm EM-H005 · cell EM-C010 EM-R011 AR · motif EM-M045 HM (T5–16)
- **Entwicklung:** Stasis, Wanderung
- **Tonfunktionen (gezählt):** A 227, T 4, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 6
- **Datei:** EM-S016_Langsame_Oberstimme_ueber_bewegter_Unterschicht.mid

### EM-S017 – Additive Motiventhüllung
- **Säule:** AB · **Länge:** 16 Takte · **Tonika:** C · **Modus:** aeolisch · **Tempo:** 64 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,35 / 0,45 / 0,40
- **Rollenspuren:** LF, KB, TU, HM · **Ereignisse:** 118 (7,40 pro Takt ohne ST) · **ohne HM/GS:** nein · **ohne AR:** ja · **Puls:** ja
- **Schichten:** harm EM-H034 · bass EM-B039 · phrase EM-P002
- **Entwicklung:** Additive Motiventhüllung
- **Tonfunktionen (gezählt):** A 98, T 20, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 2
- **Datei:** EM-S017_Additive_Motiventhuellung.mid

### EM-S018 – Kombinierbare modulare Textur (32 Takte)
- **Säule:** AB · **Länge:** 32 Takte · **Tonika:** A · **Modus:** aeolisch · **Tempo:** 64 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,40 / 0,35 / 0,35
- **Rollenspuren:** LF, LB, KB, AR, TU · **Ereignisse:** 186 (5,80 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** nein · **Puls:** ja
- **Schichten:** Module: T1–8: EM-K002+EM-K008+EM-K023 | T9–16: EM-K002+EM-K011+EM-K018 | T17–24: EM-K003+EM-K009+EM-K017 | T25–32: EM-K002+EM-K008+EM-K022
- **Entwicklung:** Modul-Kombinatorik, Rotation
- **Tonfunktionen (gezählt):** A 174, T 12, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 9
- **Datei:** EM-S018_Kombinierbare_modulare_Textur_32_Takte.mid

### EM-S019 – Längere lyrische Entwicklung (16 Takte)
- **Säule:** A · **Länge:** 16 Takte · **Tonika:** F · **Modus:** ionisch · **Tempo:** 66 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,75 / 0,45 / 0,25
- **Rollenspuren:** LF, LB, HM · **Ereignisse:** 69 (4,30 pro Takt ohne ST) · **ohne HM/GS:** nein · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H061 · phrase EM-P011
- **Entwicklung:** Wiederkehr und Erweiterung
- **Tonfunktionen (gezählt):** A 57, T 12, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 11
- **Datei:** EM-S019_Laengere_lyrische_Entwicklung_16_Takte.mid

### EM-S020 – 64 Takte: Moll-Lyrik mit Rotation und Reduktion
- **Säule:** A · **Länge:** 64 Takte · **Tonika:** A · **Modus:** aeolisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,40 / 0,30 / 0,20
- **Rollenspuren:** LF, LB, TU, GS · **Ereignisse:** 230 (3,60 pro Takt ohne ST) · **ohne HM/GS:** nein · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H004 (Pause T41–44; Rotation EM-H004→EM-H015→EM-H056→EM-H009; gestaffelt 0/480/960/1440; Atmung Stimmenzahl 4,4,4,4,4,4,4,4,4,4,3,3,3,3,4,4) · cell EM-C010 EM-R018 TU (T9–64; Pause T33–40; Permutation alle 8 Takte) · motif EM-M019 GS (T49–64)
- **Entwicklung:** Rotation, Umfärbung, Reduktion und Wiederaufnahme, Zellpermutation
- **Tonfunktionen (gezählt):** A 201, T 29, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 8
- **Datei:** EM-S020_64_Takte_Moll_Lyrik_mit_Rotation_und_Reduktion.mid

### EM-S021 – 64 Takte: Dorische Atmung mit Farbtonwechsel
- **Säule:** A · **Länge:** 64 Takte · **Tonika:** D · **Modus:** dorisch · **Tempo:** 58 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,55 / 0,20 / 0,10
- **Rollenspuren:** LF, LB, TU · **Ereignisse:** 217 (3,40 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H054 (Atmung Stimmenzahl 4,3,4,2) · bass EM-B038 · cell EM-C026 EM-R047 TU (T9–64; Farbtonwechsel alle 16 Takte)
- **Entwicklung:** Stasis, Atmung, Farbtonaustausch
- **Tonfunktionen (gezählt):** A 157, T 56, V 0, F 4 (davon deklariert 4), U 0; Noten über mehrere Harmonien 6
- **Datei:** EM-S021_64_Takte_Dorische_Atmung_mit_Farbtonwechsel.mid

### EM-S022 – 64 Takte: Elektronischer Puls mit Reduktion und Wiederaufnahme
- **Säule:** B · **Länge:** 64 Takte · **Tonika:** E · **Modus:** phrygisch · **Tempo:** 92 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,25 / 0,45 / 0,40
- **Rollenspuren:** LF, KB, AR, TU · **Ereignisse:** 651 (10,20 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** nein · **Puls:** ja
- **Schichten:** harm EM-H088 · bass EM-B008 (Pause T33–36) · cell EM-C046 EM-R063 AR (T9–64; Pause T29–40) · cell EM-C014 EM-R041 TU (T33–64; Permutation alle 8 Takte)
- **Entwicklung:** Stasis, Reduktion und Wiederaufnahme, Rotation
- **Tonfunktionen (gezählt):** A 626, T 25, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 3
- **Datei:** EM-S022_64_Takte_Elektronischer_Puls_mit_Reduktion_und_Wiederaufnahm.mid

### EM-S023 – 64 Takte: Kraft ohne Hektik mit additiver Enthüllung
- **Säule:** B · **Länge:** 64 Takte · **Tonika:** D · **Modus:** aeolisch · **Tempo:** 96 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,35 / 0,80 / 0,35
- **Rollenspuren:** LF, KB, AR, TU, ST, HM · **Ereignisse:** 1528 (22,10 pro Takt ohne ST) · **ohne HM/GS:** nein · **ohne AR:** nein · **Puls:** ja
- **Schichten:** harm EM-H034 · bass EM-B030 (Pause T49–50) · cell EM-C011 EM-R013 AR (T5–64; Pause T49–50) · motif EM-M034 TU (T9–40; additive Stufen 2→2→4→4→7→7→10→10) · motif EM-M045 HM (T41–64) · st EM-R016 (T5–64; Pause T49–50)
- **Entwicklung:** Additive Motiventhüllung, Atmung, Reduktion und Wiederaufnahme
- **Tonfunktionen (gezählt):** A 972, T 440, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 2
- **Datei:** EM-S023_64_Takte_Kraft_ohne_Hektik_mit_additiver_Enthuellung.mid

### EM-S024 – 64 Takte: Schönheit und Bedrohung im Wechselgespräch
- **Säule:** AB · **Länge:** 64 Takte · **Tonika:** E · **Modus:** dorisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,55 / 0,40 / 0,55
- **Rollenspuren:** LF, KF, LB, TU, GS · **Ereignisse:** 340 (5,30 pro Takt ohne ST) · **ohne HM/GS:** nein · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H094 · cell EM-C009 EM-R018 TU (T1–32; Permutation alle 8 Takte) · ef EM-EF04 (T33–48) · cell EM-C009 EM-R049 TU (T49–64)
- **Entwicklung:** Ereignisfeld, Stasis, Umfärbung
- **Tonfunktionen (gezählt):** A 212, T 38, V 0, F 10 (davon deklariert 0), U 80; Noten über mehrere Harmonien 86
- **Datei:** EM-S024_64_Takte_Schoenheit_und_Bedrohung_im_Wechselgespraech.mid

### EM-S025 – 64 Takte: Partitura-multipla-Rotation
- **Säule:** AB · **Länge:** 64 Takte · **Tonika:** A · **Modus:** aeolisch · **Tempo:** 66 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,35 / 0,40 / 0,40
- **Rollenspuren:** LF, KF, LB, KB, AR, TU · **Ereignisse:** 417 (6,50 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** nein · **Puls:** ja
- **Schichten:** Module: T1–8: EM-K001+EM-K008+EM-K022 | T9–16: EM-K001+EM-K013+EM-K023 | T17–24: EM-K002+EM-K011+EM-K019 | T25–32: EM-K006+EM-K010+EM-K024 | T33–40: EM-K002+EM-K008+EM-K017 | T41–48: EM-K005+EM-K009+EM-K025 | T49–56: EM-K001+EM-K012+EM-K020 | T57–64: EM-K002+EM-K008+EM-K022
- **Entwicklung:** Modul-Kombinatorik, Rotation, Blockverschiebung
- **Tonfunktionen (gezählt):** A 308, T 87, V 0, F 0 (davon deklariert 0), U 22; Noten über mehrere Harmonien 20
- **Datei:** EM-S025_64_Takte_Partitura_multipla_Rotation.mid

### EM-S026 – 64 Takte: Plagale Erinnerung in Dur
- **Säule:** A · **Länge:** 64 Takte · **Tonika:** D · **Modus:** ionisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,75 / 0,30 / 0,15
- **Rollenspuren:** LF, LB, TU, GS · **Ereignisse:** 238 (3,70 pro Takt ohne ST) · **ohne HM/GS:** nein · **ohne AR:** ja · **Puls:** nein
- **Schichten:** uchain EM-U007+EM-U008+EM-U009+EM-U041 · cell EM-C029 EM-R039 TU (T9–56; Permutation alle 8 Takte) · motif EM-M026 GS (T33–48)
- **Entwicklung:** Rotation, Wanderung, Reduktion und Wiederaufnahme
- **Tonfunktionen (gezählt):** A 197, T 41, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 66
- **Datei:** EM-S026_64_Takte_Plagale_Erinnerung_in_Dur.mid

### EM-S027 – Moll-add9 in drei Lagen (eng, offen, Terzbass)
- **Säule:** A · **Länge:** 16 Takte · **Tonika:** H · **Modus:** aeolisch · **Tempo:** 58 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,35 / 0,25 / 0,25
- **Rollenspuren:** LF, LB · **Ereignisse:** 21 (1,30 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H001 (Rotation EM-H001→EM-H002→EM-H003; gestaffelt 0/480/960/1440)
- **Entwicklung:** Umfärbung durch Lage
- **Tonfunktionen (gezählt):** A 21, T 0, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 2
- **Datei:** EM-S027_Moll_add9_in_drei_Lagen_eng_offen_Terzbass.mid

### EM-S028 – Halbverminderter Weg zum offenen Halbschluss
- **Säule:** A · **Länge:** 8 Takte · **Tonika:** G · **Modus:** harm_moll · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,25 / 0,40 / 0,45
- **Rollenspuren:** LF, LB, TU · **Ereignisse:** 27 (3,40 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H011 · cell EM-C009 EM-R031 TU
- **Entwicklung:** aufgeschobene Auflösung
- **Tonfunktionen (gezählt):** A 21, T 6, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 5
- **Datei:** EM-S028_Halbverminderter_Weg_zum_offenen_Halbschluss.mid

### EM-S029 – Chromatisches Lamento mit Gegenstimme
- **Säule:** A · **Länge:** 16 Takte · **Tonika:** A · **Modus:** aeolisch · **Tempo:** 56 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,25 / 0,45 / 0,40
- **Rollenspuren:** LF, LB, GS · **Ereignisse:** 53 (3,30 pro Takt ohne ST) · **ohne HM/GS:** nein · **ohne AR:** ja · **Puls:** nein
- **Schichten:** uchain EM-U020+EM-U021+EM-U022+EM-U023 · motif EM-M029 GS (T9–16)
- **Entwicklung:** Wanderung (Bass), Rotation
- **Tonfunktionen (gezählt):** A 44, T 9, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 22
- **Datei:** EM-S029_Chromatisches_Lamento_mit_Gegenstimme.mid

### EM-S030 – Dur/Moll-Umfärbung bei gleichem Grundton
- **Säule:** A · **Länge:** 16 Takte · **Tonika:** C · **Modus:** dur_moll_gemischt · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,55 / 0,25 / 0,30
- **Rollenspuren:** LF, LB, TU · **Ereignisse:** 34 (2,10 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H024 (gestaffelt 0/480/960/1440) · cell EM-C033 EM-R019 TU
- **Entwicklung:** Umfärbung
- **Tonfunktionen (gezählt):** A 34, T 0, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 2
- **Datei:** EM-S030_Dur_Moll_Umfaerbung_bei_gleichem_Grundton.mid

### EM-S031 – Reharmonisierung eines liegenden Melodietons (Dur)
- **Säule:** A · **Länge:** 16 Takte · **Tonika:** E♭ · **Modus:** ionisch · **Tempo:** 58 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,75 / 0,30 / 0,15
- **Rollenspuren:** LF, LB · **Ereignisse:** 38 (2,40 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** uchain EM-U030
- **Entwicklung:** Umfärbung, Stasis
- **Tonfunktionen (gezählt):** A 38, T 0, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 23
- **Datei:** EM-S031_Reharmonisierung_eines_liegenden_Melodietons_Dur.mid

### EM-S032 – Lydisches Licht (hell, nicht fröhlich)
- **Säule:** A · **Länge:** 16 Takte · **Tonika:** F · **Modus:** lydisch · **Tempo:** 56 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,90 / 0,20 / 0,20
- **Rollenspuren:** LF, LB, AR · **Ereignisse:** 184 (11,50 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** nein · **Puls:** ja
- **Schichten:** harm EM-H021 (gestaffelt 0/960/1920/2880) · cell EM-C034 EM-R011 AR (T5–16)
- **Entwicklung:** Stasis, Atmung
- **Tonfunktionen (gezählt):** A 130, T 54, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 0
- **Datei:** EM-S032_Lydisches_Licht_hell_nicht_froehlich.mid

### EM-S033 – Dominantpedal-Drang
- **Säule:** A · **Länge:** 16 Takte · **Tonika:** D · **Modus:** harm_moll · **Tempo:** 66 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,20 / 0,55 / 0,50
- **Rollenspuren:** LF, LB, KB · **Ereignisse:** 114 (7,10 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** ja
- **Schichten:** harm EM-H035 · bass EM-B009 (T5–16)
- **Entwicklung:** Stasis mit Druck
- **Tonfunktionen (gezählt):** A 82, T 32, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 11
- **Datei:** EM-S033_Dominantpedal_Drang.mid

### EM-S034 – Vorhaltstudie: Halbschluss und verzögerte Auflösung
- **Säule:** A · **Länge:** 8 Takte · **Tonika:** C · **Modus:** ionisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,60 / 0,35 / 0,40
- **Rollenspuren:** LF, LB · **Ereignisse:** 16 (2,00 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** uchain EM-U013+EM-U014
- **Entwicklung:** verzögerte Auflösung
- **Tonfunktionen (gezählt):** A 14, T 0, V 2, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 8
- **Datei:** EM-S034_Vorhaltstudie_Halbschluss_und_verzoegerte_Aufloesung.mid

### EM-S035 – Bewusst offene Schlüsse mit Fragmenten
- **Säule:** A · **Länge:** 8 Takte · **Tonika:** A · **Modus:** aeolisch · **Tempo:** 58 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,45 / 0,30 / 0,30
- **Rollenspuren:** LF, LB, TU · **Ereignisse:** 16 (2,00 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H039 · motif EM-M021 TU (T5–8)
- **Entwicklung:** offene Phrase
- **Tonfunktionen (gezählt):** A 16, T 0, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 5
- **Datei:** EM-S035_Bewusst_offene_Schluesse_mit_Fragmenten.mid

### EM-S036 – Frage und Antwort zwischen HM und GS
- **Säule:** A · **Länge:** 8 Takte · **Tonika:** E · **Modus:** dorisch · **Tempo:** 64 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,55 / 0,35 / 0,25
- **Rollenspuren:** LF, LB, GS, HM · **Ereignisse:** 36 (4,50 pro Takt ohne ST) · **ohne HM/GS:** nein · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H007 · phrase EM-P005
- **Entwicklung:** motivische Antwort
- **Tonfunktionen (gezählt):** A 28, T 8, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 1
- **Datei:** EM-S036_Frage_und_Antwort_zwischen_HM_und_GS.mid

### EM-S037 – Kontrapunkt: lange Linie gegen bewegtes Gegenmotiv
- **Säule:** A · **Länge:** 8 Takte · **Tonika:** G · **Modus:** aeolisch · **Tempo:** 62 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,40 / 0,45 / 0,30
- **Rollenspuren:** LF, LB, GS, HM · **Ereignisse:** 54 (6,80 pro Takt ohne ST) · **ohne HM/GS:** nein · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H005 · phrase EM-P006
- **Entwicklung:** Kontrapunkt
- **Tonfunktionen (gezählt):** A 39, T 15, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 3
- **Datei:** EM-S037_Kontrapunkt_lange_Linie_gegen_bewegtes_Gegenmotiv.mid

### EM-S038 – Paranoia bei geringer Notendichte
- **Säule:** B · **Länge:** 16 Takte · **Tonika:** C♯ · **Modus:** aeolisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,20 / 0,25 / 0,75
- **Rollenspuren:** LF, KB, TU · **Ereignisse:** 28 (1,80 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** ja
- **Schichten:** harm EM-H077 · bass EM-B052 · ef EM-EF05
- **Entwicklung:** Ereignisfeld, Stasis
- **Tonfunktionen (gezählt):** A 27, T 0, V 0, F 1 (davon deklariert 1), U 0; Noten über mehrere Harmonien 3
- **Datei:** EM-S038_Paranoia_bei_geringer_Notendichte.mid

### EM-S039 – Mechanische Unruhe (Akzentwanderung)
- **Säule:** B · **Länge:** 16 Takte · **Tonika:** F · **Modus:** oktatonisch_HG · **Tempo:** 100 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,35 / 0,50 / 0,70
- **Rollenspuren:** LF, KB, AR · **Ereignisse:** 365 (22,80 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** nein · **Puls:** ja
- **Schichten:** harm EM-H072 · bass EM-B033 · cell EM-C044 EM-R048 AR
- **Entwicklung:** Phasenversatz, Stasis
- **Tonfunktionen (gezählt):** A 365, T 0, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 6
- **Datei:** EM-S039_Mechanische_Unruhe_Akzentwanderung.mid

### EM-S040 – Akuter Horror: Ballung, Stich, Stille
- **Säule:** B · **Länge:** 8 Takte · **Tonika:** B♭ · **Modus:** chromatisch · **Tempo:** 70 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,10 / 0,90 / 0,90
- **Rollenspuren:** KF, LB, ST · **Ereignisse:** 50 (2,60 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** bass EM-B026 · ef EM-EF15 · st EM-R053
- **Entwicklung:** Ereignisfeld mit Stille
- **Tonfunktionen (gezählt):** A 0, T 21, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 0
- **Datei:** EM-S040_Akuter_Horror_Ballung_Stich_Stille.mid

### EM-S041 – Spieluhr gegen Störfeld
- **Säule:** AB · **Länge:** 8 Takte · **Tonika:** G · **Modus:** ionisch · **Tempo:** 70 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,80 / 0,25 / 0,60
- **Rollenspuren:** LF, KF, LB, AR · **Ereignisse:** 73 (9,10 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** nein · **Puls:** ja
- **Schichten:** harm EM-H093 · phrase EM-P013
- **Entwicklung:** geschützte Identität
- **Tonfunktionen (gezählt):** A 39, T 28, V 0, F 0 (davon deklariert 0), U 6; Noten über mehrere Harmonien 9
- **Datei:** EM-S041_Spieluhr_gegen_Stoerfeld.mid

### EM-S042 – Giallo-inspirierter Groove mit Einwürfen
- **Säule:** B · **Länge:** 16 Takte · **Tonika:** E · **Modus:** phrygisch · **Tempo:** 104 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,20 / 0,60 / 0,55
- **Rollenspuren:** LF, KB, TU · **Ereignisse:** 121 (7,60 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** ja
- **Schichten:** harm EM-H079 · bass EM-B032 · ef EM-EF07 (T5–16)
- **Entwicklung:** Stasis, Ereignisfeld
- **Tonfunktionen (gezählt):** A 62, T 59, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 2
- **Datei:** EM-S042_Giallo_inspirierter_Groove_mit_Einwuerfen.mid

### EM-S043 – B-A-C-H-Ordnung über Drone
- **Säule:** B · **Länge:** 8 Takte · **Tonika:** C · **Modus:** chromatisch · **Tempo:** 58 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,40 / 0,30 / 0,45
- **Rollenspuren:** LF, LB, GS · **Ereignisse:** 23 (2,90 pro Takt ohne ST) · **ohne HM/GS:** nein · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H086 · bass EM-B035 · phrase EM-P017
- **Entwicklung:** Rotation der Ordnung
- **Tonfunktionen (gezählt):** A 22, T 0, V 0, F 0 (davon deklariert 0), U 1; Noten über mehrere Harmonien 4
- **Datei:** EM-S043_B_A_C_H_Ordnung_ueber_Drone.mid

### EM-S044 – Ternäre Sinnlichkeit (12/8)
- **Säule:** A · **Länge:** 16 Takte · **Tonika:** A · **Modus:** dorisch · **Tempo:** 52 BPM · **Takt:** 12/8 · **XYZ-Anker:** 0,50 / 0,35 / 0,25
- **Rollenspuren:** LF, KB, AR · **Ereignisse:** 282 (17,60 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** nein · **Puls:** ja
- **Schichten:** harm EM-H013 · bass EM-B048 · cell EM-C010 EM-R059 AR
- **Entwicklung:** Stasis, Atmung
- **Tonfunktionen (gezählt):** A 250, T 32, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 2
- **Datei:** EM-S044_Ternaere_Sinnlichkeit_12_8.mid

### EM-S045 – Tragische Pendelterz mit schweren Halben
- **Säule:** A · **Länge:** 16 Takte · **Tonika:** F · **Modus:** aeolisch · **Tempo:** 56 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,30 / 0,70 / 0,20
- **Rollenspuren:** LF, KF, LB · **Ereignisse:** 211 (13,20 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H064 · bass EM-B042 · Module: T1–16: EM-K030
- **Entwicklung:** Stasis (hohes Y)
- **Tonfunktionen (gezählt):** A 139, T 72, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 3
- **Datei:** EM-S045_Tragische_Pendelterz_mit_schweren_Halben.mid

### EM-S046 – Gestaffelte plagale Rückkehr in Dur
- **Säule:** A · **Länge:** 8 Takte · **Tonika:** G · **Modus:** ionisch · **Tempo:** 58 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,75 / 0,25 / 0,10
- **Rollenspuren:** LF, LB · **Ereignisse:** 28 (3,50 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** uchain EM-U034+EM-U041
- **Entwicklung:** gestaffelter Klangaufbau
- **Tonfunktionen (gezählt):** A 26, T 2, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 10
- **Datei:** EM-S046_Gestaffelte_plagale_Rueckkehr_in_Dur.mid

### EM-S047 – Kalte Mystery: lydisches Licht über fallendem Bass
- **Säule:** AB · **Länge:** 16 Takte · **Tonika:** D · **Modus:** lydisch · **Tempo:** 58 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,85 / 0,40 / 0,55
- **Rollenspuren:** LF, LB, TU · **Ereignisse:** 33 (2,10 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H098 · cell EM-C031 EM-R026 TU
- **Entwicklung:** Stasis, Wanderung (Bass)
- **Tonfunktionen (gezählt):** A 19, T 6, V 0, F 0 (davon deklariert 0), U 8; Noten über mehrere Harmonien 4
- **Datei:** EM-S047_Kalte_Mystery_lydisches_Licht_ueber_fallendem_Bass.mid

### EM-S048 – Kraftvoll ohne Hektik, lyrisch-erhaben
- **Säule:** A · **Länge:** 16 Takte · **Tonika:** D · **Modus:** dorisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,55 / 0,85 / 0,20
- **Rollenspuren:** LF, LB, HM · **Ereignisse:** 51 (3,20 pro Takt ohne ST) · **ohne HM/GS:** nein · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H043 · bass EM-B028 · motif EM-M046 HM (T5–16)
- **Entwicklung:** Stasis (hohes Y)
- **Tonfunktionen (gezählt):** A 38, T 13, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 9
- **Datei:** EM-S048_Kraftvoll_ohne_Hektik_lyrisch_erhaben.mid

### EM-S049 – Polychord-Schatten und Rückweg
- **Säule:** B · **Länge:** 8 Takte · **Tonika:** A · **Modus:** phrygisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,15 / 0,50 / 0,55
- **Rollenspuren:** LF, LB, TU · **Ereignisse:** 43 (5,40 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** uchain EM-U048+EM-U047 · cell EM-C015 EM-R018 TU
- **Entwicklung:** Verdichtung und Auflösung (an XYZ-Übergang gebunden)
- **Tonfunktionen (gezählt):** A 35, T 0, V 0, F 0 (davon deklariert 0), U 8; Noten über mehrere Harmonien 9
- **Datei:** EM-S049_Polychord_Schatten_und_Rueckweg.mid

### EM-S050 – Trügerische Helle: Dur-add9 über Tritonuspedal
- **Säule:** AB · **Länge:** 16 Takte · **Tonika:** C · **Modus:** ionisch · **Tempo:** 64 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,75 / 0,30 / 0,45
- **Rollenspuren:** LF, LB, KB, AR · **Ereignisse:** 93 (5,80 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** nein · **Puls:** ja
- **Schichten:** harm EM-H092 · motif EM-M043 AR (T5–16)
- **Entwicklung:** Stasis, geschützte Identität
- **Tonfunktionen (gezählt):** A 77, T 12, V 0, F 0 (davon deklariert 0), U 4; Noten über mehrere Harmonien 5
- **Datei:** EM-S050_Truegerische_Helle_Dur_add9_ueber_Tritonuspedal.mid

### EM-S051 – 64 Takte: Pulslose Mystery mit seltenem Stich
- **Säule:** B · **Länge:** 64 Takte · **Tonika:** G · **Modus:** oktatonisch_GH · **Tempo:** 54 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,40 / 0,20 / 0,55
- **Rollenspuren:** LF, TU, ST · **Ereignisse:** 91 (1,20 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H076 (Pause T25–28) · ef EM-EF14 (T5–60) · st EM-R062 (T17–64)
- **Entwicklung:** Stasis, Ereignisfeld, lange Stille
- **Tonfunktionen (gezählt):** A 38, T 20, V 0, F 21 (davon deklariert 21), U 0; Noten über mehrere Harmonien 13
- **Datei:** EM-S051_64_Takte_Pulslose_Mystery_mit_seltenem_Stich.mid

### EM-S052 – Morgendliche Zärtlichkeit (Ableitung aus der werkübergreifenden Grammatik, kein Lolita-Zitat)
- **Säule:** A · **Länge:** 32 Takte · **Tonika:** F · **Modus:** aeolisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,50 / 0,25 / 0,15
- **Rollenspuren:** LF, LB, TU · **Ereignisse:** 132 (4,10 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H051 (Rotation EM-H051→EM-H053; gestaffelt 0/480/960/1440) · cell EM-C045 EM-R039 TU (T5–32; Permutation alle 8 Takte)
- **Entwicklung:** Rotation, Umfärbung, Atmung
- **Tonfunktionen (gezählt):** A 115, T 17, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 2
- **Datei:** EM-S052_Morgendliche_Zaertlichkeit_Ableitung_aus_der_werkuebergreife.mid

### EM-S053 – Dunkle, stehende Bedrohung (tief, leise, stabil)
- **Säule:** AB · **Länge:** 16 Takte · **Tonika:** D · **Modus:** aeolisch · **Tempo:** 52 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,20 / 0,20 / 0,20
- **Rollenspuren:** LF, LB, TU · **Ereignisse:** 20 (1,20 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H106 · bass EM-B003 · cell EM-C009 EM-R019 TU (T5–16)
- **Entwicklung:** Stasis
- **Tonfunktionen (gezählt):** A 18, T 2, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 2
- **Datei:** EM-S053_Dunkle_stehende_Bedrohung_tief_leise_stabil.mid

### EM-S054 – Dunkle Monumentalität ohne Hektik
- **Säule:** A · **Länge:** 16 Takte · **Tonika:** C · **Modus:** aeolisch · **Tempo:** 52 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,20 / 0,80 / 0,20
- **Rollenspuren:** LF, LB, GS · **Ereignisse:** 76 (4,80 pro Takt ohne ST) · **ohne HM/GS:** nein · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H111 (gestaffelt 0/480/960/1440) · bass EM-B034 · motif EM-M050 GS (T5–16)
- **Entwicklung:** Stasis (hohes Y über Gewicht)
- **Tonfunktionen (gezählt):** A 55, T 21, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 3
- **Datei:** EM-S054_Dunkle_Monumentalitaet_ohne_Hektik.mid

### EM-S055 – Kaltes, gestörtes Licht (hell, leise, unruhig)
- **Säule:** AB · **Länge:** 16 Takte · **Tonika:** E · **Modus:** lydisch · **Tempo:** 56 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,79 / 0,21 / 0,79
- **Rollenspuren:** LF, LB, TU · **Ereignisse:** 40 (2,50 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H115 · cell EM-C034 EM-R049 TU (T3–16)
- **Entwicklung:** Ereignisfeld, Umfärbung
- **Tonfunktionen (gezählt):** A 33, T 7, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 4
- **Datei:** EM-S055_Kaltes_gestoertes_Licht_hell_leise_unruhig.mid

### EM-S056 – Helle hymnische Kraft (hell, kraftvoll, stabil)
- **Säule:** A · **Länge:** 16 Takte · **Tonika:** C · **Modus:** ionisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,80 / 0,80 / 0,20
- **Rollenspuren:** LF, LB, HM · **Ereignisse:** 62 (3,90 pro Takt ohne ST) · **ohne HM/GS:** nein · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H117 (gestaffelt 0/480/960/1440) · bass EM-B021 · motif EM-M018 HM (T5–16)
- **Entwicklung:** Stasis, Atmung
- **Tonfunktionen (gezählt):** A 52, T 10, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 2
- **Datei:** EM-S056_Helle_hymnische_Kraft_hell_kraftvoll_stabil.mid

### EM-S057 – Helle mechanische Unruhe (hell, kraftvoll, unruhig)
- **Säule:** B · **Länge:** 16 Takte · **Tonika:** C · **Modus:** chromatisch · **Tempo:** 104 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,79 / 0,79 / 0,79
- **Rollenspuren:** KF, KB, AR, ST · **Ereignisse:** 424 (25,00 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** nein · **Puls:** ja
- **Schichten:** harm EM-H119 · bass EM-B032 · cell EM-C020 EM-R048 AR · st EM-R016 (T5–16)
- **Entwicklung:** Blockverschiebung, Phasenversatz
- **Tonfunktionen (gezählt):** A 174, T 226, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 0
- **Datei:** EM-S057_Helle_mechanische_Unruhe_hell_kraftvoll_unruhig.mid

### EM-EF01 – Ereignisfeld: Pulsloses Moll-add9-Feld mit seltenen Tupfern
- **Säule:** A · **Länge:** 16 Takte · **Tonika:** A · **Modus:** aeolisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,45 / 0,15 / 0,25
- **Rollenspuren:** LF, LB, TU · **Ereignisse:** 15 (0,90 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H002 · ef EM-EF01
- **Entwicklung:** Ereignisfeld
- **Tonfunktionen (gezählt):** A 15, T 0, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 5
- **Datei:** EM-EF01_Ereignisfeld_Pulsloses_Moll_add9_Feld_mit_seltenen_Tupfern.mid

### EM-EF02 – Ereignisfeld: Ereignis und Echo
- **Säule:** AB · **Länge:** 16 Takte · **Tonika:** D · **Modus:** aeolisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,40 / 0,20 / 0,30
- **Rollenspuren:** KF, LB, TU · **Ereignisse:** 28 (1,80 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** bass EM-B001 · ef EM-EF02
- **Entwicklung:** Ereignisfeld
- **Tonfunktionen (gezählt):** A 0, T 28, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 0
- **Datei:** EM-EF02_Ereignisfeld_Ereignis_und_Echo.mid

### EM-EF03 – Ereignisfeld: Ruf und Zustimmung
- **Säule:** A · **Länge:** 16 Takte · **Tonika:** E · **Modus:** aeolisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,55 / 0,25 / 0,30
- **Rollenspuren:** LF, LB, TU, GS · **Ereignisse:** 64 (4,00 pro Takt ohne ST) · **ohne HM/GS:** nein · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H007 · ef EM-EF03
- **Entwicklung:** Ereignisfeld
- **Tonfunktionen (gezählt):** A 58, T 6, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 3
- **Datei:** EM-EF03_Ereignisfeld_Ruf_und_Zustimmung.mid

### EM-EF04 – Ereignisfeld: Ruf und Widerspruch
- **Säule:** AB · **Länge:** 16 Takte · **Tonika:** H · **Modus:** aeolisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,40 / 0,30 / 0,55
- **Rollenspuren:** LF, LB, TU, GS · **Ereignisse:** 37 (2,30 pro Takt ohne ST) · **ohne HM/GS:** nein · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H001 · ef EM-EF04
- **Entwicklung:** Ereignisfeld
- **Tonfunktionen (gezählt):** A 26, T 4, V 0, F 7 (davon deklariert 0), U 0; Noten über mehrere Harmonien 7
- **Datei:** EM-EF04_Ereignisfeld_Ruf_und_Widerspruch.mid

### EM-EF05 – Ereignisfeld: Ausbleibende Antwort
- **Säule:** B · **Länge:** 16 Takte · **Tonika:** C♯ · **Modus:** chromatisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,20 / 0,15 / 0,50
- **Rollenspuren:** TU · **Ereignisse:** 5 (0,30 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** ef EM-EF05
- **Entwicklung:** Ereignisfeld
- **Tonfunktionen (gezählt):** A 0, T 5, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 0
- **Datei:** EM-EF05_Ereignisfeld_Ausbleibende_Antwort.mid

### EM-EF06 – Ereignisfeld: Konsonanter Anker, experimentelle Umgebung
- **Säule:** AB · **Länge:** 16 Takte · **Tonika:** F · **Modus:** aeolisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,70 / 0,30 / 0,60
- **Rollenspuren:** LF, KF, LB, TU · **Ereignisse:** 45 (2,80 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H026 · ef EM-EF06
- **Entwicklung:** Ereignisfeld
- **Tonfunktionen (gezählt):** A 19, T 12, V 0, F 14 (davon deklariert 10), U 0; Noten über mehrere Harmonien 5
- **Datei:** EM-EF06_Ereignisfeld_Konsonanter_Anker_experimentelle_Umgebung.mid

### EM-EF07 – Ereignisfeld: Dissonanter Anker (Tritonus-Pedal)
- **Säule:** B · **Länge:** 16 Takte · **Tonika:** E · **Modus:** chromatisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,15 / 0,30 / 0,55
- **Rollenspuren:** LB, TU · **Ereignisse:** 15 (0,90 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** bass EM-B005 · ef EM-EF07
- **Entwicklung:** Ereignisfeld
- **Tonfunktionen (gezählt):** A 0, T 15, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 0
- **Datei:** EM-EF07_Ereignisfeld_Dissonanter_Anker_Tritonus_Pedal.mid

### EM-EF08 – Ereignisfeld: Ankerlose, kohärente Textur (eine Zelle)
- **Säule:** B · **Länge:** 16 Takte · **Tonika:** G · **Modus:** chromatisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,30 / 0,30 / 0,70
- **Rollenspuren:** KF, TU · **Ereignisse:** 48 (3,00 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** ef EM-EF08
- **Entwicklung:** Ereignisfeld
- **Tonfunktionen (gezählt):** A 0, T 48, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 0
- **Datei:** EM-EF08_Ereignisfeld_Ankerlose_kohaerente_Textur_eine_Zelle.mid

### EM-EF09 – Ereignisfeld: Lange Stille mit Einzelglocke
- **Säule:** AB · **Länge:** 16 Takte · **Tonika:** A · **Modus:** aeolisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,40 / 0,10 / 0,30
- **Rollenspuren:** TU · **Ereignisse:** 2 (0,10 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** ef EM-EF09
- **Entwicklung:** Ereignisfeld
- **Tonfunktionen (gezählt):** A 0, T 2, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 0
- **Datei:** EM-EF09_Ereignisfeld_Lange_Stille_mit_Einzelglocke.mid

### EM-EF10 – Ereignisfeld: Gestaffelte Klangereignisse (Akkord tropft)
- **Säule:** A · **Länge:** 16 Takte · **Tonika:** C · **Modus:** aeolisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,45 / 0,25 / 0,25
- **Rollenspuren:** TU · **Ereignisse:** 66 (4,10 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** ef EM-EF10
- **Entwicklung:** Ereignisfeld
- **Tonfunktionen (gezählt):** A 0, T 66, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 0
- **Datei:** EM-EF10_Ereignisfeld_Gestaffelte_Klangereignisse_Akkord_tropft.mid

### EM-EF11 – Ereignisfeld: Lyrische Einzelereignisse (Seufzer-Splitter)
- **Säule:** A · **Länge:** 16 Takte · **Tonika:** D · **Modus:** aeolisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,40 / 0,20 / 0,25
- **Rollenspuren:** LF, LB, TU, GS · **Ereignisse:** 48 (3,00 pro Takt ohne ST) · **ohne HM/GS:** nein · **ohne AR:** ja · **Puls:** nein
- **Schichten:** uchain EM-U002 · ef EM-EF11
- **Entwicklung:** Ereignisfeld
- **Tonfunktionen (gezählt):** A 46, T 2, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 3
- **Datei:** EM-EF11_Ereignisfeld_Lyrische_Einzelereignisse_Seufzer_Splitter.mid

### EM-EF12 – Ereignisfeld: Kontrast: hoch gegen tief
- **Säule:** B · **Länge:** 16 Takte · **Tonika:** F♯ · **Modus:** chromatisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,25 / 0,45 / 0,60
- **Rollenspuren:** KF, TU · **Ereignisse:** 36 (2,20 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** ef EM-EF12
- **Entwicklung:** Ereignisfeld
- **Tonfunktionen (gezählt):** A 0, T 36, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 0
- **Datei:** EM-EF12_Ereignisfeld_Kontrast_hoch_gegen_tief.mid

### EM-EF13 – Ereignisfeld: Kontrolliert chaotische Textur (komponierte Unordnung)
- **Säule:** B · **Länge:** 16 Takte · **Tonika:** H · **Modus:** chromatisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,30 / 0,70 / 0,85
- **Rollenspuren:** LF, KF, TU · **Ereignisse:** 130 (8,10 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** harm EM-H073 · ef EM-EF13
- **Entwicklung:** Ereignisfeld
- **Tonfunktionen (gezählt):** A 97, T 33, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 7
- **Datei:** EM-EF13_Ereignisfeld_Kontrolliert_chaotische_Textur_komponierte_Unor.mid

### EM-EF14 – Ereignisfeld: B-A-C-H-Streuung, ametrisch
- **Säule:** B · **Länge:** 16 Takte · **Tonika:** C · **Modus:** chromatisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,40 / 0,25 / 0,50
- **Rollenspuren:** TU · **Ereignisse:** 21 (1,30 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** ef EM-EF14
- **Entwicklung:** Ereignisfeld
- **Tonfunktionen (gezählt):** A 0, T 21, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 0
- **Datei:** EM-EF14_Ereignisfeld_B_A_C_H_Streuung_ametrisch.mid

### EM-EF15 – Ereignisfeld: Akuter Horror: Ballung und Stich
- **Säule:** B · **Länge:** 16 Takte · **Tonika:** B♭ · **Modus:** chromatisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,10 / 0,90 / 0,90
- **Rollenspuren:** KF, ST · **Ereignisse:** 40 (1,60 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** ef EM-EF15
- **Entwicklung:** Ereignisfeld
- **Tonfunktionen (gezählt):** A 0, T 25, V 0, F 0 (davon deklariert 0), U 0; Noten über mehrere Harmonien 0
- **Datei:** EM-EF15_Ereignisfeld_Akuter_Horror_Ballung_und_Stich.mid

### EM-EF16 – Ereignisfeld: Gesprächsfeld mit Kleinsext-Anker (Bird-Prinzip)
- **Säule:** AB · **Länge:** 16 Takte · **Tonika:** A · **Modus:** aeolisch · **Tempo:** 60 BPM · **Takt:** 4/4 · **XYZ-Anker:** 0,45 / 0,30 / 0,55
- **Rollenspuren:** LF, KF, TU · **Ereignisse:** 59 (3,70 pro Takt ohne ST) · **ohne HM/GS:** ja · **ohne AR:** ja · **Puls:** nein
- **Schichten:** cell EM-C030 EM-R047 TU · harm EM-H088 · ef EM-EF16
- **Entwicklung:** Ereignisfeld
- **Tonfunktionen (gezählt):** A 15, T 25, V 0, F 19 (davon deklariert 14), U 0; Noten über mehrere Harmonien 3
- **Datei:** EM-EF16_Ereignisfeld_Gespraechsfeld_mit_Kleinsext_Anker_Bird_Prinzip.mid

## 17. Langfristige Entwicklung über 8, 16, 32 und 64 Takte

| Zeitraum | Was bleibt | Was sich ändern darf | Vorlagen/Studien |
|---|---|---|---|
| 8 Takte | Harmoniefolge, Zellmenge, Tempo, Register | Ordnung einer Zelle, Velocity-Atem, einzelne TU-Ereignisse | EM-S028, EM-S034, EM-S035, EM-S046 |
| 16 Takte | Klangidentität, Bassfunktion | Rotation verwandter H-Vorlagen, Permutation an Blockgrenzen, Beginn additiver Enthüllung | EM-S001–S005, EM-S017, EM-S027 |
| 32 Takte | Tonvorrat-Kern, Puls | Farbtonaustausch, Modulkombination, Rollenwanderung, Reduktion | EM-S006, EM-S013, EM-S015, EM-S018, EM-S052 |
| 64 Takte | Grundcharakter der XYZ-Position | Reduktion und Wiederaufnahme, mehrfache Rotation, vollständige Enthüllung, Gesprächsphasen | EM-S020–S026, EM-S051 |

Wiedererkennbarkeit entsteht durch die konstante Zelle bzw. Klangqualität und die liegenden Gemeinsamtöne; Vielfalt durch Rotation der Ordnung, Umfärbung desselben Tons und Modulwechsel. Ohne harmonische Bewegung tragen Lage, Staffelung, Farbtonwechsel und Ereignisdichte (immobilità dinamica).

## 18. Verbleibende Unsicherheiten

- Keine Hörprüfung; Klangqualität, Balance und Wirkung der Studien sind ungeprüft.
- Lolita/Love in the Morning: keine belegten Akkordfolgen; die lyrische Säule ist werkübergreifend abgeleitet.
- Untouchables: Taktart, Tempo und Bassfigur der Titelmusik sind unbelegt; die Untouchables-inspirierten Vorlagen bilden nur das belegte *Prinzip* (zwei Zeitschichten, Gewicht statt Dichte, additive Enthüllung) mit eigenen Tönen nach.
- Crowdsourcing-Belege (Hooktheory) sind als H gekennzeichnet.
- Rollenregister und Gate-Werte sind Präferenzen ohne Instrumentenbindung.