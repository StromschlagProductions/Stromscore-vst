# STROMSCORE – John Carpenter: Kanonisches musikalisches Vokabular (SYNTH-Modus)

*Phase 2 · Stand: 27. November 2026 · Grundlage: Tiefenrecherche und Vertiefung (bei Widerspruch gilt die Vertiefung)*

Diese Bibliothek beschreibt das John-Carpenter-Profil als **musikalische Grammatik**, nicht als Klangrezept. Alle konkreten Tonfolgen, Klänge, Rhythmen und Motive sind **eigenständige Konstruktionen** auf Basis der erforschten Verfahren. Kein bekanntes Filmthema ist transkribiert oder nachgebaut.

Dokumentation, CSV und MIDI-Studien werden aus **einem** Datenmodell erzeugt. Abweichungen zwischen den Dateien sind dadurch ausgeschlossen und werden zusätzlich maschinell geprüft (siehe JC_Qualitaetspruefung.md).

## Inhalt

1. Konventionen
2. Übersicht und Gewichtung
3. H – Harmonik
4. R – Rhythmik
5. Q – Sequencer-Tonfolgen
6. B – Bassführung
7. M – Motive
8. P – Phrasen
9. T – Transformationsverfahren
10. EF – Ereignisfelder
11. S – Mehrschichtige Modellstudien
12. Langfristige Entwicklung
13. Abgestufte Stilregeln
14. Technische Anforderungen an die Engine

## 1. Konventionen

**Zeitbasis:** 960 PPQ. Ein 4/4-Takt = 3840 Ticks. Raster: Ganze 3840, Halbe 1920, Viertel 960, Achtel 480, Sechzehntel 240, Viertel-Triole 640, Achtel-Triole 320.

**Tonhöhen:** relativ und transponierbar. `0` = Grundton der Tonart in der Basisoktave der Rolle. Negative Werte liegen darunter. Stufenangaben: 1, ♭2, 2, ♭3, 3, 4, ♯4/♭5, 5, ♭6, 6, ♭7, 7; Zusatz „+1Okt“ für höhere Oktaven.

**Basisoktave je Rolle** (Tonart C; für andere Tonarten um deren Abstand zu C verschoben):

| Rolle | Name | Basis (0) | Erlaubter Umfang | Funktion im Carpenter-Profil |
|---|---|---|---|---|
| LF | Lange Fläche | C3 (48) | A1–G6 | Drone, gehaltene Klangfelder, Cluster |
| KF | Kurze Fläche | C3 (48) | E2–C6 | Akkordpulse, selten |
| LB | Langer Bass | C1 (24) | A0–E3 | Pedal, Drone, Akkordgrundton |
| KB | Kurzer Bass | C2 (36) | E1–E4 | Basssequenz, Puls, Riff |
| AR | Arpeggio | C4 (60) | A2–E7 | Sequencer A |
| TU | Tupfer | C4 (60) | C3–C8 | harmonische Einzelereignisse, Glocken, Rufe |
| ST | Stich | C2 (36) | C2–C2 | fester Effekt-Trigger, Note 36 |
| GS | Gegenstimme | C4 (60) | C2–C7 | Sequencer B, Kanonstimme, Gegenmotiv (optional) |
| HM | Hauptmelodie | C3 (48) | C3–C7 | Lead-Linie (optional) |

Die Mittellage (etwa E2–C4, Grundtonbereich der Sprechstimme) wird in den Vorlagen sparsam besetzt. Das ist für Hörspiel zwingend (siehe Regel 9).

**Tonfunktionen** (wie im Bernard-Herrmann-Profil), jeweils gegen den tatsächlich klingenden Klang berechnet:

- **A** – Akkordton des klingenden Klangs.
- **T** – zulässiger Tonvorratston (im Modus, nicht im Klang).
- **V** – Vorhalt oder Durchgang mit konkretem Auflösungsziel (nächster Ton derselben Rolle, Halb- oder Ganztonschritt, Akkordton).
- **F** – bewusst akkordfremder Ton (gewollte Färbung, keine Auflösung nötig).
- **U** – bewusst unaufgelöste Dissonanz.

F und U entstehen **nur** durch ausdrückliche Autorisierung: in der Vorlage (Feld „Autorisierte Reibungen“), im Klang selbst (Zusatztöne mit F/U), durch ein als *Dissonanzpedal* gebundenes Bass-Pedal oder durch eine deklarierte Blocktransposition (JC-T001). Eine allgemeine Harmoniekorrektur darf diese Töne **nicht** entfernen. Ein Ton ohne jede dieser Begründungen ist ein Fehler (intern „X“) und kommt in den Studien nicht vor.

**Evidenz:** Jede Vorlage nennt die Evidenz des *Verfahrens* (N/I/H/E). Die konkrete Tonfolge ist immer **E** (eigenständige Konstruktion).

**XYZ:** X = Färbung dunkel→hell, Y = Intensität, Z = Unruhe, je 0–1. Jede Vorlage hat einen Anker (Mittelpunkt) und einen Gültigkeitsbereich. Rhythmische Vorlagen sind meist färbungsunabhängig (X 0–1). Z-Charakter: *mechanisch* (regelmäßig, kleinteilig) oder *psychologisch* (unregelmäßig, reibend, bei geringer Dichte); intern, ohne eigenen Regler.

**Bindung (Bass):** *akkordgebunden* = folgt dem Akkordgrundton; *eigenständig* = folgt nicht (Schalter „Folgt Akkorden“ aus); *Dissonanzpedal* = hält auch gegen fremde Klänge, Reibungen sind autorisiert.

**Akzente:** X = 112, x = 88, o = 62 (Velocity vor Rollenskalierung).

## 2. Übersicht und Gewichtung

| Bibliothek | Anzahl | Zielgröße |
|---|---|---|
| H | 88 | 70–90 |
| R | 67 | 60–80 |
| Q | 67 | 60–80 |
| B | 52 | 45–60 |
| M | 45 | 40–50 |
| P | 16 | 15–20 |
| T | 16 | 12–18 |
| EF | 12 | eigene Gruppe |
| S | 42 | 35–45 |

**Evidenz der Verfahren je Bibliothek:**

| | N | I | H | E |
|---|---|---|---|---|
| H | 19 | 39 | 19 | 11 |
| R | 18 | 25 | 2 | 22 |
| Q | 18 | 35 | 6 | 8 |
| B | 18 | 26 | 2 | 6 |
| M | 8 | 23 | 5 | 9 |

**Gewichtung für die Engine (Vorschlag):** N-Verfahren Grundgewicht 1,0; I 0,8; H 0,3 (nur bei passender XYZ-Lage, nie als Standard); E 0,6. Keine Vorlage ist verpflichtend; Stilmittel bleiben optional (Lehre aus dem Barry-Profil).

## 3. H – Harmonik

Ein einzelner Klang darf über beliebig lange Zeit das vollständige harmonische Material bilden. Akkordwechsel sind nie erzwungen. Segmente werden zyklisch wiederholt, solange die Vorlage aktiv ist.

### H1 – Leere Quint- und Oktavflächen

#### JC-H001 Kalte Quintleere

- **Charakter:** Eine leere Quinte als vollständiges harmonisches Material, beliebig lang haltbar.
- **XYZ:** Anker (0,25 / 0,30 / 0,20); gültig X: 0,00–0,50 · Y: 0,00–0,60 · Z: 0,00–0,40; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–8: Grundton 1 – leere Quinte: 1 (Prime, A), 5 (Quinte, A)
- **Entwicklungsstrategien:** Stasis, Atmung, Ereignisfeld, Blockverschiebung
- **Geeignet mit:** alle Bass- und Sequencer-Vorlagen; Ereignisfelder. **Ungeeignet:** –
- **Fähigkeiten:** unabhängiges Pedal
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Konstruktion E

#### JC-H002 Oktavsäule

- **Charakter:** Nur Grundton und Oktave; kein Tongeschlecht, maximale Offenheit für andere Schichten.
- **XYZ:** Anker (0,20 / 0,25 / 0,15); gültig X: 0,00–0,40 · Y: 0,00–0,50 · Z: 0,00–0,30; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–8: Grundton 1 – Oktave: 1 (Prime, A), 1+1Okt (Oktave, A)
- **Entwicklungsstrategien:** Stasis, Atmung, Ereignisfeld, Blockverschiebung
- **Geeignet mit:** alle Bass- und Sequencer-Vorlagen; Ereignisfelder. **Ungeeignet:** –
- **Fähigkeiten:** unabhängiges Pedal
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Konstruktion E

#### JC-H003 Quint-Oktav-Turm

- **Charakter:** Breiter Turm aus Quinten und Oktaven; Kraft ohne Bewegung.
- **XYZ:** Anker (0,35 / 0,70 / 0,20); gültig X: 0,00–0,70 · Y: 0,40–1,00 · Z: 0,00–0,40; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–8: Grundton 1 – Quint-Oktav-Turm: 1 (Prime, A), 5 (Quinte, A), 1+1Okt (Oktave, A), 5+1Okt (Quinte + 1 Okt., A)
- **Entwicklungsstrategien:** Stasis, Atmung, Ereignisfeld, Blockverschiebung
- **Geeignet mit:** alle Bass- und Sequencer-Vorlagen; Ereignisfelder. **Ungeeignet:** –
- **Fähigkeiten:** mehrstimmige LF-Rolle (≥ 4 Stimmen), unabhängiges Pedal, exakte weite Lage (Stimmen > 1,5 Oktaven über Grundton)
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Konstruktion E

#### JC-H004 Quintenstapel mit None

- **Charakter:** Zwei Quinten übereinander; die None klingt hell und kalt, nicht süß.
- **XYZ:** Anker (0,65 / 0,30 / 0,15); gültig X: 0,40–0,90 · Y: 0,00–0,60 · Z: 0,00–0,30; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–8: Grundton 1 – Quintenstapel: 1 (Prime, A), 5 (Quinte, A), 2+1Okt (große Sekunde + 1 Okt., T)
- **Entwicklungsstrategien:** Stasis, Atmung, Ereignisfeld, Blockverschiebung
- **Geeignet mit:** alle Bass- und Sequencer-Vorlagen; Ereignisfelder. **Ungeeignet:** –
- **Fähigkeiten:** unabhängiges Pedal
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H005 Quartleere

- **Charakter:** Quarte über dem Grundton; schwebend, ohne Grundtonsicherheit.
- **XYZ:** Anker (0,55 / 0,25 / 0,30); gültig X: 0,30–0,80 · Y: 0,00–0,50 · Z: 0,10–0,50; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Quinte im Bass
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–8: Grundton 1 – Quarte + Oktave: 1 (Prime, A), 4 (Quarte, A), 1+1Okt (Oktave, A)
- **Entwicklungsstrategien:** Stasis, Atmung, Ereignisfeld, Blockverschiebung
- **Geeignet mit:** alle Bass- und Sequencer-Vorlagen; Ereignisfelder. **Ungeeignet:** –
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H006 Quintpendel Grundton–♭VI

- **Charakter:** Zwei leere Quinten im Kleinsexten-Abstand; dunkel, kein Tongeschlecht.
- **XYZ:** Anker (0,20 / 0,50 / 0,20); gültig X: 0,00–0,40 · Y: 0,20–0,80 · Z: 0,00–0,40; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–4: Grundton 1 – leere Quinte: 1 (Prime, A), 5 (Quinte, A)
  - T5–8: Grundton ♭6 – leere Quinte: ♭6 (Prime, A), ♭3+1Okt (Quinte, A)
- **Entwicklungsstrategien:** Stasis, Atmung, Ereignisfeld, Blockverschiebung
- **Geeignet mit:** alle Bass- und Sequencer-Vorlagen; Ereignisfelder. **Ungeeignet:** –
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H007 Quintpendel Grundton–♭VII

- **Charakter:** Leere Quinten im Ganztonabstand; rockige Herkunft, ruhig gehalten.
- **XYZ:** Anker (0,30 / 0,60 / 0,20); gültig X: 0,10–0,50 · Y: 0,30–0,90 · Z: 0,00–0,40; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–4: Grundton 1 – leere Quinte: 1 (Prime, A), 5 (Quinte, A)
  - T5–8: Grundton ♭7 – leere Quinte: ♭7 (Prime, A), 4+1Okt (Quinte, A)
- **Entwicklungsstrategien:** Stasis, Atmung, Ereignisfeld, Blockverschiebung
- **Geeignet mit:** alle Bass- und Sequencer-Vorlagen; Ereignisfelder. **Ungeeignet:** –
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H008 Weite Quinte

- **Charakter:** Quinte unten, Doppeloktave oben, leere Mitte für Sprache.
- **XYZ:** Anker (0,65 / 0,20 / 0,15); gültig X: 0,40–0,90 · Y: 0,00–0,40 · Z: 0,00–0,30; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: kein Bass empfohlen
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – weite Quinte (Quinte + Doppeloktave): 1 (Prime, A), 5 (Quinte, A), 1+2Okt (2 Oktaven, A)
- **Entwicklungsstrategien:** Stasis, Atmung, Ereignisfeld, Blockverschiebung
- **Geeignet mit:** alle Bass- und Sequencer-Vorlagen; Ereignisfelder. **Ungeeignet:** –
- **Fähigkeiten:** exakte weite Lage (Stimmen > 1,5 Oktaven über Grundton)
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

### H2 – Halbtonreibungen

#### JC-H009 Quinte mit ♭2

- **Charakter:** Leere Quinte, darüber der obere Halbtonnachbar des Grundtons; die Reibung bleibt stehen.
- **XYZ:** Anker (0,15 / 0,30 / 0,70); gültig X: 0,00–0,30 · Y: 0,00–0,60 · Z: 0,40–1,00; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Phrygisch
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–8: Grundton 1 – leere Quinte: 1 (Prime, A), 5 (Quinte, A), ♭2+1Okt (kleine Sekunde + 1 Okt., U)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld, Reduktion und Wiederaufnahme
- **Geeignet mit:** Drone, Pedal, seltene TU-Ereignisse. **Ungeeignet:** weitere Reibungen in AR/GS ohne Absicht (Kumulation)
- **Fähigkeiten:** Dissonanz-Autorisierung im Klang, unabhängiges Pedal
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Konstruktion E

#### JC-H010 Quinte mit ♭6-Nachbar

- **Charakter:** Die kleine Sexte liegt einen Halbton über der Quinte und drückt auf sie.
- **XYZ:** Anker (0,20 / 0,30 / 0,55); gültig X: 0,00–0,40 · Y: 0,00–0,60 · Z: 0,30–0,80; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–8: Grundton 1 – leere Quinte: 1 (Prime, A), 5 (Quinte, A), ♭6+1Okt (kleine Sexte + 1 Okt., F)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld, Reduktion und Wiederaufnahme
- **Geeignet mit:** Drone, Pedal, seltene TU-Ereignisse. **Ungeeignet:** weitere Reibungen in AR/GS ohne Absicht (Kumulation)
- **Fähigkeiten:** Dissonanz-Autorisierung im Klang, unabhängiges Pedal, exakte weite Lage (Stimmen > 1,5 Oktaven über Grundton)
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Konstruktion E

#### JC-H011 Quinte mit großer Septime

- **Charakter:** Der Leitton reibt an der Oktave, ohne sich aufzulösen.
- **XYZ:** Anker (0,40 / 0,25 / 0,65); gültig X: 0,20–0,60 · Y: 0,00–0,50 · Z: 0,40–0,90; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Harmonisch Moll
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–8: Grundton 1 – leere Quinte: 1 (Prime, A), 5 (Quinte, A), 7 (große Septime, U)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld, Reduktion und Wiederaufnahme
- **Geeignet mit:** Drone, Pedal, seltene TU-Ereignisse. **Ungeeignet:** weitere Reibungen in AR/GS ohne Absicht (Kumulation)
- **Fähigkeiten:** Dissonanz-Autorisierung im Klang, unabhängiges Pedal
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H012 Oktave mit Tritonus

- **Charakter:** Tritonus in leerer Oktave. Als Kernintervall bei Carpenter nicht belegt; markierte Ableitung.
- **XYZ:** Anker (0,15 / 0,50 / 0,80); gültig X: 0,00–0,30 · Y: 0,20–0,80 · Z: 0,60–1,00; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Lokrisch
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–8: Grundton 1 – Oktave: 1 (Prime, A), 1+1Okt (Oktave, A), ♯4/♭5 (Tritonus, U)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld, Reduktion und Wiederaufnahme
- **Geeignet mit:** Drone, Pedal, seltene TU-Ereignisse. **Ungeeignet:** weitere Reibungen in AR/GS ohne Absicht (Kumulation)
- **Fähigkeiten:** Dissonanz-Autorisierung im Klang, unabhängiges Pedal
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Konstruktion E

#### JC-H013 Moll mit ♭2 oben

- **Charakter:** Molldreiklang mit hoher ♭2; dunkel, ungelöst.
- **XYZ:** Anker (0,15 / 0,45 / 0,65); gültig X: 0,00–0,30 · Y: 0,20–0,70 · Z: 0,40–0,90; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Phrygisch
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–8: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A), ♭2+1Okt (kleine Sekunde + 1 Okt., U)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld, Reduktion und Wiederaufnahme
- **Geeignet mit:** Drone, Pedal, seltene TU-Ereignisse. **Ungeeignet:** weitere Reibungen in AR/GS ohne Absicht (Kumulation)
- **Fähigkeiten:** mehrstimmige LF-Rolle (≥ 4 Stimmen), Dissonanz-Autorisierung im Klang, unabhängiges Pedal
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H014 Doppelte Halbtonreibung

- **Charakter:** Grundton und Quinte haben je einen oberen Halbtonnachbarn; dichteste Zweiton-Reibung.
- **XYZ:** Anker (0,12 / 0,65 / 0,80); gültig X: 0,00–0,25 · Y: 0,30–1,00 · Z: 0,60–1,00; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Phrygisch
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–8: Grundton 1 – leere Quinte: 1 (Prime, A), 5 (Quinte, A), ♭2 (kleine Sekunde, U), ♭6 (kleine Sexte, F)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld, Reduktion und Wiederaufnahme
- **Geeignet mit:** Drone, Pedal, seltene TU-Ereignisse. **Ungeeignet:** weitere Reibungen in AR/GS ohne Absicht (Kumulation)
- **Fähigkeiten:** mehrstimmige LF-Rolle (≥ 4 Stimmen), Dissonanz-Autorisierung im Klang, unabhängiges Pedal
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H015 Halbton-Blockpendel der Quinte

- **Charakter:** Die ganze leere Quinte rückt einen Halbton hoch und wieder zurück.
- **XYZ:** Anker (0,30 / 0,65 / 0,75); gültig X: 0,00–0,60 · Y: 0,30–1,00 · Z: 0,50–1,00; Z-Charakter mechanisch
- **Modus (Tonvorrat):** Chromatisch (frei, nur Akkordtöne + autorisierte Töne)
- **Rollen:** LF (Klang); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–4: Grundton 1 – leere Quinte: 1 (Prime, A), 5 (Quinte, A)
  - T5–8: Grundton ♭2 – leere Quinte: ♭2 (Prime, A), ♭6 (Quinte, A)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld, Reduktion und Wiederaufnahme
- **Geeignet mit:** Drone, Pedal, seltene TU-Ereignisse. **Ungeeignet:** weitere Reibungen in AR/GS ohne Absicht (Kumulation)
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Konstruktion E

#### JC-H016 Wandernder Reibungston

- **Charakter:** Quinte bleibt; der Reibungston wechselt von oben (♭2) nach unten (Leitton).
- **XYZ:** Anker (0,20 / 0,30 / 0,65); gültig X: 0,00–0,40 · Y: 0,00–0,60 · Z: 0,40–0,90; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Harmonisch Moll
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–4: Grundton 1 – leere Quinte: 1 (Prime, A), 5 (Quinte, A), ♭2+1Okt (kleine Sekunde + 1 Okt., U)
  - T5–8: Grundton 1 – leere Quinte: 1 (Prime, A), 5 (Quinte, A), 7 (große Septime, U)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld, Reduktion und Wiederaufnahme
- **Geeignet mit:** Drone, Pedal, seltene TU-Ereignisse. **Ungeeignet:** weitere Reibungen in AR/GS ohne Absicht (Kumulation)
- **Fähigkeiten:** Dissonanz-Autorisierung im Klang, unabhängiges Pedal
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

### H3 – Mollakkord-Pulse

#### JC-H017 Moll-Grundklang für Pulse

- **Charakter:** Schlichter Mollklang für kurze Akkordpulse (KF).
- **XYZ:** Anker (0,30 / 0,55 / 0,30); gültig X: 0,10–0,50 · Y: 0,20–0,90 · Z: 0,00–0,60; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang), KF (Pulse); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–8: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
- **Entwicklungsstrategien:** Rotation, Atmung
- **Geeignet mit:** KF-Pulse (JC-R007, JC-R006), akkordgebundene Bässe. **Ungeeignet:** dichte Sequenzen in derselben Lage wie KF
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Konstruktion E

#### JC-H018 Offener Moll für Pulse

- **Charakter:** Moll mit Terz eine Oktave höher; weniger dumpf als enge Lage.
- **XYZ:** Anker (0,40 / 0,50 / 0,25); gültig X: 0,20–0,60 · Y: 0,20–0,80 · Z: 0,00–0,50; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang), KF (Pulse); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–8: Grundton 1 – offener Moll (Quinte + Dezime): 1 (Prime, A), 5 (Quinte, A), ♭3+1Okt (kleine Terz + 1 Okt., A)
- **Entwicklungsstrategien:** Rotation, Atmung
- **Geeignet mit:** KF-Pulse (JC-R007, JC-R006), akkordgebundene Bässe. **Ungeeignet:** dichte Sequenzen in derselben Lage wie KF
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Konstruktion E

#### JC-H019 Mollpuls i–♭VI

- **Charakter:** Langsamer Wechsel; ♭VI hält zwei Töne gemeinsam.
- **XYZ:** Anker (0,30 / 0,60 / 0,40); gültig X: 0,10–0,50 · Y: 0,30–0,90 · Z: 0,20–0,60; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang), KF (Pulse); Bass: Akkordgrundton (LB/KB)
- **Periode:** 4 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–2: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T3–4: Grundton ♭6 – Durdreiklang: ♭6 (Prime, A), 1+1Okt (große Terz, A), ♭3+1Okt (Quinte, A)
- **Entwicklungsstrategien:** Rotation, Atmung
- **Geeignet mit:** KF-Pulse (JC-R007, JC-R006), akkordgebundene Bässe. **Ungeeignet:** dichte Sequenzen in derselben Lage wie KF
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Konstruktion E

#### JC-H020 Mollpuls i–iv

- **Charakter:** Plagale Mollbewegung ohne Dominante.
- **XYZ:** Anker (0,20 / 0,60 / 0,35); gültig X: 0,00–0,40 · Y: 0,30–0,90 · Z: 0,10–0,60; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang), KF (Pulse); Bass: Akkordgrundton (LB/KB)
- **Periode:** 4 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–2: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T3–4: Grundton 4 – Molldreiklang: 4 (Prime, A), ♭6 (kleine Terz, A), 1+1Okt (Quinte, A)
- **Entwicklungsstrategien:** Rotation, Atmung
- **Geeignet mit:** KF-Pulse (JC-R007, JC-R006), akkordgebundene Bässe. **Ungeeignet:** dichte Sequenzen in derselben Lage wie KF
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H021 Mollpuls i–♭II

- **Charakter:** Phrygischer Halbtonwechsel; plausible Ableitung, nicht belegt.
- **XYZ:** Anker (0,15 / 0,65 / 0,65); gültig X: 0,00–0,30 · Y: 0,30–1,00 · Z: 0,40–0,90; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Phrygisch
- **Rollen:** LF (Klang), KF (Pulse); Bass: Akkordgrundton (LB/KB)
- **Periode:** 4 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–2: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T3–4: Grundton ♭2 – Durdreiklang: ♭2 (Prime, A), 4 (große Terz, A), ♭6 (Quinte, A)
- **Entwicklungsstrategien:** Rotation, Atmung
- **Geeignet mit:** KF-Pulse (JC-R007, JC-R006), akkordgebundene Bässe. **Ungeeignet:** dichte Sequenzen in derselben Lage wie KF
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Konstruktion E

#### JC-H022 Mollpuls i–v

- **Charakter:** Moll-Quintwechsel; die Molldominante vermeidet Kadenzwirkung.
- **XYZ:** Anker (0,30 / 0,60 / 0,30); gültig X: 0,10–0,50 · Y: 0,30–0,90 · Z: 0,10–0,50; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang), KF (Pulse); Bass: Akkordgrundton (LB/KB)
- **Periode:** 4 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–2: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T3–4: Grundton 5 – Molldreiklang: 5 (Prime, A), ♭7 (kleine Terz, A), 2+1Okt (Quinte, A)
- **Entwicklungsstrategien:** Rotation, Atmung
- **Geeignet mit:** KF-Pulse (JC-R007, JC-R006), akkordgebundene Bässe. **Ungeeignet:** dichte Sequenzen in derselben Lage wie KF
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

### H4 – Diatonische Moll-Kreisfolgen

#### JC-H023 Äolischer Kreis

- **Charakter:** Vier diatonische Klänge ohne V–I; kreist statt zu schließen.
- **XYZ:** Anker (0,50 / 0,60 / 0,30); gültig X: 0,30–0,70 · Y: 0,30–0,90 · Z: 0,10–0,50; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang), KF (Pulse); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–2: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T3–4: Grundton ♭6 – Durdreiklang: ♭6 (Prime, A), 1+1Okt (große Terz, A), ♭3+1Okt (Quinte, A)
  - T5–6: Grundton 4 – Molldreiklang: 4 (Prime, A), ♭6 (kleine Terz, A), 1+1Okt (Quinte, A)
  - T7–8: Grundton ♭7 – Durdreiklang: ♭7 (Prime, A), 2+1Okt (große Terz, A), 4+1Okt (Quinte, A)
- **Entwicklungsstrategien:** Rotation, Wanderung, Umfärbung
- **Geeignet mit:** akkordgebundene Bässe, eigenständige Riffs mit Prüfung. **Ungeeignet:** eigenständige Sequenzen mit Terz-Bezug ohne Prüfung gegen ii°
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Konstruktion E

#### JC-H024 Kreis mit vermindertem ii

- **Charakter:** Der verminderte Klang am Ende öffnet den Kreis, statt ihn zu schließen.
- **XYZ:** Anker (0,40 / 0,60 / 0,50); gültig X: 0,20–0,60 · Y: 0,30–0,90 · Z: 0,30–0,70; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang), KF (Pulse); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–2: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T3–4: Grundton ♭6 – Durdreiklang: ♭6 (Prime, A), 1+1Okt (große Terz, A), ♭3+1Okt (Quinte, A)
  - T5–6: Grundton 4 – Molldreiklang: 4 (Prime, A), ♭6 (kleine Terz, A), 1+1Okt (Quinte, A)
  - T7–8: Grundton 2 – verminderter Dreiklang: 2 (Prime, A), 4 (kleine Terz, A), ♭6 (Tritonus, A)
- **Entwicklungsstrategien:** Rotation, Wanderung, Umfärbung
- **Geeignet mit:** akkordgebundene Bässe, eigenständige Riffs mit Prüfung. **Ungeeignet:** eigenständige Sequenzen mit Terz-Bezug ohne Prüfung gegen ii°
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Konstruktion E

#### JC-H025 Fünfgliedriger Kreis

- **Charakter:** Fünf Klänge à 2 Takte = 10-Takt-Periode; läuft gegen 8er-Phrasen.
- **XYZ:** Anker (0,50 / 0,60 / 0,40); gültig X: 0,30–0,70 · Y: 0,30–0,90 · Z: 0,20–0,60; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang), KF (Pulse); Bass: Akkordgrundton (LB/KB)
- **Periode:** 10 Takte (nicht 2ⁿ – läuft gegen 8er-Phrasen)
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–2: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T3–4: Grundton ♭6 – Durdreiklang: ♭6 (Prime, A), 1+1Okt (große Terz, A), ♭3+1Okt (Quinte, A)
  - T5–6: Grundton 4 – Molldreiklang: 4 (Prime, A), ♭6 (kleine Terz, A), 1+1Okt (Quinte, A)
  - T7–8: Grundton ♭3 – Durdreiklang: ♭3 (Prime, A), 5 (große Terz, A), ♭7 (Quinte, A)
  - T9–10: Grundton 2 – verminderter Dreiklang: 2 (Prime, A), 4 (kleine Terz, A), ♭6 (Tritonus, A)
- **Entwicklungsstrategien:** Rotation, Wanderung, Umfärbung
- **Geeignet mit:** akkordgebundene Bässe, eigenständige Riffs mit Prüfung. **Ungeeignet:** eigenständige Sequenzen mit Terz-Bezug ohne Prüfung gegen ii°
- **Fähigkeiten:** ungerade Harmonieperiode
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Konstruktion E

#### JC-H026 Abwärts-Kreis ♭VII–♭VI

- **Charakter:** Rockige Moll-Kreisfolge, kraftvoll und gerade.
- **XYZ:** Anker (0,50 / 0,70 / 0,20); gültig X: 0,30–0,70 · Y: 0,40–1,00 · Z: 0,00–0,40; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang), KF (Pulse); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–2: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T3–4: Grundton ♭7 – Durdreiklang: ♭7 (Prime, A), 2+1Okt (große Terz, A), 4+1Okt (Quinte, A)
  - T5–6: Grundton ♭6 – Durdreiklang: ♭6 (Prime, A), 1+1Okt (große Terz, A), ♭3+1Okt (Quinte, A)
  - T7–8: Grundton ♭7 – Durdreiklang: ♭7 (Prime, A), 2+1Okt (große Terz, A), 4+1Okt (Quinte, A)
- **Entwicklungsstrategien:** Rotation, Wanderung, Umfärbung
- **Geeignet mit:** akkordgebundene Bässe, eigenständige Riffs mit Prüfung. **Ungeeignet:** eigenständige Sequenzen mit Terz-Bezug ohne Prüfung gegen ii°
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H027 Kreis i–iv–♭VII–♭III

- **Charakter:** Quartschritte aufwärts; heller, fast heroisch.
- **XYZ:** Anker (0,65 / 0,60 / 0,20); gültig X: 0,40–0,90 · Y: 0,30–0,90 · Z: 0,00–0,40; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang), KF (Pulse); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–2: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T3–4: Grundton 4 – Molldreiklang: 4 (Prime, A), ♭6 (kleine Terz, A), 1+1Okt (Quinte, A)
  - T5–6: Grundton ♭7 – Durdreiklang: ♭7 (Prime, A), 2+1Okt (große Terz, A), 4+1Okt (Quinte, A)
  - T7–8: Grundton ♭3 – Durdreiklang: ♭3 (Prime, A), 5 (große Terz, A), ♭7 (Quinte, A)
- **Entwicklungsstrategien:** Rotation, Wanderung, Umfärbung
- **Geeignet mit:** akkordgebundene Bässe, eigenständige Riffs mit Prüfung. **Ungeeignet:** eigenständige Sequenzen mit Terz-Bezug ohne Prüfung gegen ii°
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H028 Langsamer Zweiklang-Kreis

- **Charakter:** Ein Wechsel alle 8 Takte; kaum wahrnehmbare Bewegung.
- **XYZ:** Anker (0,40 / 0,30 / 0,15); gültig X: 0,20–0,60 · Y: 0,00–0,60 · Z: 0,00–0,30; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang), KF (Pulse); Bass: Akkordgrundton (LB/KB)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–8: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T9–16: Grundton ♭6 – Durdreiklang: ♭6 (Prime, A), 1+1Okt (große Terz, A), ♭3+1Okt (Quinte, A)
- **Entwicklungsstrategien:** Rotation, Wanderung, Umfärbung
- **Geeignet mit:** akkordgebundene Bässe, eigenständige Riffs mit Prüfung. **Ungeeignet:** eigenständige Sequenzen mit Terz-Bezug ohne Prüfung gegen ii°
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H029 Kreis i–♭III–♭VII–iv

- **Charakter:** Durlastige Moll-Zirkulation; melancholisch hell.
- **XYZ:** Anker (0,60 / 0,50 / 0,20); gültig X: 0,40–0,80 · Y: 0,20–0,80 · Z: 0,00–0,40; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang), KF (Pulse); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–2: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T3–4: Grundton ♭3 – Durdreiklang: ♭3 (Prime, A), 5 (große Terz, A), ♭7 (Quinte, A)
  - T5–6: Grundton ♭7 – Durdreiklang: ♭7 (Prime, A), 2+1Okt (große Terz, A), 4+1Okt (Quinte, A)
  - T7–8: Grundton 4 – Molldreiklang: 4 (Prime, A), ♭6 (kleine Terz, A), 1+1Okt (Quinte, A)
- **Entwicklungsstrategien:** Rotation, Wanderung, Umfärbung
- **Geeignet mit:** akkordgebundene Bässe, eigenständige Riffs mit Prüfung. **Ungeeignet:** eigenständige Sequenzen mit Terz-Bezug ohne Prüfung gegen ii°
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H030 Kreis mit unaufgelöster Dominante

- **Charakter:** Dur-Dominante, die trugschlüssig nach ♭VI weicht; markierte Ableitung.
- **XYZ:** Anker (0,40 / 0,70 / 0,50); gültig X: 0,20–0,60 · Y: 0,40–1,00 · Z: 0,30–0,70; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Harmonisch Moll
- **Rollen:** LF (Klang), KF (Pulse); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–2: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T3–4: Grundton 4 – Molldreiklang: 4 (Prime, A), ♭6 (kleine Terz, A), 1+1Okt (Quinte, A)
  - T5–6: Grundton 5 – Durdreiklang: 5 (Prime, A), 7 (große Terz, A), 2+1Okt (Quinte, A)
  - T7–8: Grundton ♭6 – Durdreiklang: ♭6 (Prime, A), 1+1Okt (große Terz, A), ♭3+1Okt (Quinte, A)
- **Entwicklungsstrategien:** Rotation, Wanderung, Umfärbung
- **Geeignet mit:** akkordgebundene Bässe, eigenständige Riffs mit Prüfung. **Ungeeignet:** eigenständige Sequenzen mit Terz-Bezug ohne Prüfung gegen ii°
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Konstruktion E

### H5 – Schreitende Akkorde

#### JC-H031 Phrygischer Abstieg

- **Charakter:** Absteigender Bass in Stufen bis zur Dur-Quinte; endet offen.
- **XYZ:** Anker (0,30 / 0,70 / 0,40); gültig X: 0,10–0,50 · Y: 0,40–1,00 · Z: 0,20–0,60; Z-Charakter neutral
- **Modus (Tonvorrat):** Harmonisch Moll
- **Rollen:** LF (Klang); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–2: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T3–4: Grundton ♭7 – Durdreiklang: ♭7 (Prime, A), 2+1Okt (große Terz, A), 4+1Okt (Quinte, A)
  - T5–6: Grundton ♭6 – Durdreiklang: ♭6 (Prime, A), 1+1Okt (große Terz, A), ♭3+1Okt (Quinte, A)
  - T7–8: Grundton 5 – Durdreiklang: 5 (Prime, A), 7 (große Terz, A), 2+1Okt (Quinte, A)
- **Entwicklungsstrategien:** Umfärbung, Ereignisfeld
- **Geeignet mit:** Pedal oder akkordgebundener Bass, zögernde TU-Figuren. **Ungeeignet:** dichte Sequenzen, die das Schreiten verdecken
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Konstruktion E

#### JC-H032 Aufwärts schreitend

- **Charakter:** Bass steigt stufenweise; jeder Schritt wird heller.
- **XYZ:** Anker (0,40 / 0,50 / 0,40); gültig X: 0,20–0,60 · Y: 0,20–0,80 · Z: 0,20–0,60; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–2: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T3–4: Grundton 2 – verminderter Dreiklang: 2 (Prime, A), 4 (kleine Terz, A), ♭6 (Tritonus, A)
  - T5–6: Grundton ♭3 – Durdreiklang: ♭3 (Prime, A), 5 (große Terz, A), ♭7 (Quinte, A)
  - T7–8: Grundton 4 – Molldreiklang: 4 (Prime, A), ♭6 (kleine Terz, A), 1+1Okt (Quinte, A)
- **Entwicklungsstrategien:** Umfärbung, Ereignisfeld
- **Geeignet mit:** Pedal oder akkordgebundener Bass, zögernde TU-Figuren. **Ungeeignet:** dichte Sequenzen, die das Schreiten verdecken
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H033 Schreitende leere Quinten abwärts

- **Charakter:** Power-Quinten schreiten nach unten; dunkel und schwer.
- **XYZ:** Anker (0,20 / 0,70 / 0,25); gültig X: 0,00–0,40 · Y: 0,40–1,00 · Z: 0,00–0,50; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–2: Grundton 1 – leere Quinte: 1 (Prime, A), 5 (Quinte, A)
  - T3–4: Grundton ♭7 – leere Quinte: ♭7 (Prime, A), 4+1Okt (Quinte, A)
  - T5–6: Grundton ♭6 – leere Quinte: ♭6 (Prime, A), ♭3+1Okt (Quinte, A)
  - T7–8: Grundton 5 – leere Quinte: 5 (Prime, A), 2+1Okt (Quinte, A)
- **Entwicklungsstrategien:** Umfärbung, Ereignisfeld
- **Geeignet mit:** Pedal oder akkordgebundener Bass, zögernde TU-Figuren. **Ungeeignet:** dichte Sequenzen, die das Schreiten verdecken
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Konstruktion E

#### JC-H034 Schreitend über Pedal

- **Charakter:** Oberklänge schreiten, der Bass hält den Grundton.
- **XYZ:** Anker (0,40 / 0,50 / 0,30); gültig X: 0,20–0,60 · Y: 0,20–0,80 · Z: 0,10–0,50; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–4: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T5–8: Grundton ♭7 – Durdreiklang: ♭7 (Prime, A), 2+1Okt (große Terz, A), 4+1Okt (Quinte, A)
  - T9–12: Grundton ♭6 – Durdreiklang: ♭6 (Prime, A), 1+1Okt (große Terz, A), ♭3+1Okt (Quinte, A)
  - T13–16: Grundton ♭7 – Durdreiklang: ♭7 (Prime, A), 2+1Okt (große Terz, A), 4+1Okt (Quinte, A)
- **Entwicklungsstrategien:** Umfärbung, Ereignisfeld
- **Geeignet mit:** Pedal oder akkordgebundener Bass, zögernde TU-Figuren. **Ungeeignet:** dichte Sequenzen, die das Schreiten verdecken
- **Fähigkeiten:** unabhängiges Pedal
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Konstruktion E

#### JC-H035 Chromatische Moll-Parallelen

- **Charakter:** Parallel gleitende Molldreiklänge; unheimlich, nicht belegt.
- **XYZ:** Anker (0,15 / 0,65 / 0,80); gültig X: 0,00–0,30 · Y: 0,30–1,00 · Z: 0,60–1,00; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Chromatisch (frei, nur Akkordtöne + autorisierte Töne)
- **Rollen:** LF (Klang); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–2: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T3–4: Grundton 7 – Molldreiklang: 7 (Prime, A), 2+1Okt (kleine Terz, A), ♯4/♭5+1Okt (Quinte, A)
  - T5–6: Grundton ♭7 – Molldreiklang: ♭7 (Prime, A), ♭2+1Okt (kleine Terz, A), 4+1Okt (Quinte, A)
  - T7–8: Grundton 7 – Molldreiklang: 7 (Prime, A), 2+1Okt (kleine Terz, A), ♯4/♭5+1Okt (Quinte, A)
- **Entwicklungsstrategien:** Umfärbung, Ereignisfeld
- **Geeignet mit:** Pedal oder akkordgebundener Bass, zögernde TU-Figuren. **Ungeeignet:** dichte Sequenzen, die das Schreiten verdecken
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Konstruktion E

#### JC-H036 Terzschritte i–♭III–v–♭VII

- **Charakter:** Terzverwandtschaften; weich, schwebend.
- **XYZ:** Anker (0,50 / 0,45 / 0,20); gültig X: 0,30–0,70 · Y: 0,20–0,70 · Z: 0,00–0,40; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Akkordgrundton (LB/KB)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–4: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T5–8: Grundton ♭3 – Durdreiklang: ♭3 (Prime, A), 5 (große Terz, A), ♭7 (Quinte, A)
  - T9–12: Grundton 5 – Molldreiklang: 5 (Prime, A), ♭7 (kleine Terz, A), 2+1Okt (Quinte, A)
  - T13–16: Grundton ♭7 – Durdreiklang: ♭7 (Prime, A), 2+1Okt (große Terz, A), 4+1Okt (Quinte, A)
- **Entwicklungsstrategien:** Umfärbung, Ereignisfeld
- **Geeignet mit:** Pedal oder akkordgebundener Bass, zögernde TU-Figuren. **Ungeeignet:** dichte Sequenzen, die das Schreiten verdecken
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

### H6 – Moll-Dur-Umfärbungen

#### JC-H037 Moll wird Dur

- **Charakter:** Nur die Terz wechselt; Licht ohne Auflösung.
- **XYZ:** Anker (0,60 / 0,30 / 0,30); gültig X: 0,40–0,80 · Y: 0,00–0,60 · Z: 0,10–0,50; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–4: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T5–8: Grundton 1 – Durdreiklang: 1 (Prime, A), 3 (große Terz, A), 5 (Quinte, A)
- **Entwicklungsstrategien:** Umfärbung, Ereignisfeld
- **Geeignet mit:** lange Flächen, Glocken, lyrische Linien. **Ungeeignet:** Blockverschiebung gleichzeitig mit Umfärbung
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H038 Dur-Ziel einen Ganzton höher

- **Charakter:** Moll, dann Dur einen Ganzton höher; nach dem Fog-Hinweis abgeleitet.
- **XYZ:** Anker (0,70 / 0,55 / 0,30); gültig X: 0,50–0,90 · Y: 0,20–0,90 · Z: 0,10–0,50; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Akkordgrundton (LB/KB)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–8: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T9–16: Grundton 2 – Durdreiklang: 2 (Prime, A), ♯4/♭5 (große Terz, A), 6 (Quinte, A)
- **Entwicklungsstrategien:** Umfärbung, Ereignisfeld
- **Geeignet mit:** lange Flächen, Glocken, lyrische Linien. **Ungeeignet:** Blockverschiebung gleichzeitig mit Umfärbung
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Konstruktion E

#### JC-H039 Dur wird Moll

- **Charakter:** Verdunkelung durch die Terz allein.
- **XYZ:** Anker (0,40 / 0,30 / 0,40); gültig X: 0,20–0,60 · Y: 0,00–0,60 · Z: 0,20–0,60; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–4: Grundton 1 – Durdreiklang: 1 (Prime, A), 3 (große Terz, A), 5 (Quinte, A)
  - T5–8: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
- **Entwicklungsstrategien:** Umfärbung, Ereignisfeld
- **Geeignet mit:** lange Flächen, Glocken, lyrische Linien. **Ungeeignet:** Blockverschiebung gleichzeitig mit Umfärbung
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H040 Moll und Dur-IV

- **Charakter:** Dorische Dur-Subdominante; kühl und hell.
- **XYZ:** Anker (0,70 / 0,35 / 0,20); gültig X: 0,50–0,90 · Y: 0,10–0,60 · Z: 0,00–0,40; Z-Charakter neutral
- **Modus (Tonvorrat):** Dorisch
- **Rollen:** LF (Klang); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–4: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T5–8: Grundton 4 – Durdreiklang: 4 (Prime, A), 6 (große Terz, A), 1+1Okt (Quinte, A)
- **Entwicklungsstrategien:** Umfärbung, Ereignisfeld
- **Geeignet mit:** lange Flächen, Glocken, lyrische Linien. **Ungeeignet:** Blockverschiebung gleichzeitig mit Umfärbung
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H041 Kalte Mediante

- **Charakter:** Moll zur Dur-Mediante; glasig, entrückt. Nicht belegt.
- **XYZ:** Anker (0,75 / 0,40 / 0,60); gültig X: 0,50–1,00 · Y: 0,10–0,70 · Z: 0,30–0,90; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Chromatisch (frei, nur Akkordtöne + autorisierte Töne)
- **Rollen:** LF (Klang); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–4: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T5–8: Grundton 3 – Durdreiklang: 3 (Prime, A), ♭6 (große Terz, A), 7 (Quinte, A)
- **Entwicklungsstrategien:** Umfärbung, Ereignisfeld
- **Geeignet mit:** lange Flächen, Glocken, lyrische Linien. **Ungeeignet:** Blockverschiebung gleichzeitig mit Umfärbung
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Konstruktion E

#### JC-H042 Dur-Lichtung

- **Charakter:** Lange Mollfläche öffnet sich zum parallelen Dur.
- **XYZ:** Anker (0,70 / 0,25 / 0,15); gültig X: 0,50–0,90 · Y: 0,00–0,50 · Z: 0,00–0,30; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Akkordgrundton (LB/KB)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–8: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T9–16: Grundton ♭3 – Durdreiklang: ♭3 (Prime, A), 5 (große Terz, A), ♭7 (Quinte, A)
- **Entwicklungsstrategien:** Umfärbung, Ereignisfeld
- **Geeignet mit:** lange Flächen, Glocken, lyrische Linien. **Ungeeignet:** Blockverschiebung gleichzeitig mit Umfärbung
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

### H7 – Gehaltene Mehrklänge

#### JC-H043 Moll add9 Fläche

- **Charakter:** Gehaltener Moll mit None; ruhig, leicht bitter.
- **XYZ:** Anker (0,60 / 0,25 / 0,15); gültig X: 0,40–0,80 · Y: 0,00–0,50 · Z: 0,00–0,30; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – Moll add9: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A), 2+1Okt (große Sekunde + 1 Okt., A)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld, Umfärbung
- **Geeignet mit:** Drone, Ereignisfelder, langsame Motive. **Ungeeignet:** Arpeggien, die den Klang ausbuchstabieren (Verlust der Fläche)
- **Fähigkeiten:** mehrstimmige LF-Rolle (≥ 4 Stimmen), unabhängiges Pedal
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H044 Kalter sus2

- **Charakter:** Kein Tongeschlecht, aber Bewegung im Klang.
- **XYZ:** Anker (0,75 / 0,25 / 0,15); gültig X: 0,50–1,00 · Y: 0,00–0,50 · Z: 0,00–0,30; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – sus2: 1 (Prime, A), 2 (große Sekunde, A), 5 (Quinte, A)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld, Umfärbung
- **Geeignet mit:** Drone, Ereignisfelder, langsame Motive. **Ungeeignet:** Arpeggien, die den Klang ausbuchstabieren (Verlust der Fläche)
- **Fähigkeiten:** unabhängiges Pedal
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H045 Gehaltener sus4

- **Charakter:** Quarte statt Terz; wartend.
- **XYZ:** Anker (0,60 / 0,30 / 0,25); gültig X: 0,40–0,80 · Y: 0,00–0,60 · Z: 0,10–0,40; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – sus4: 1 (Prime, A), 4 (Quarte, A), 5 (Quinte, A)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld, Umfärbung
- **Geeignet mit:** Drone, Ereignisfelder, langsame Motive. **Ungeeignet:** Arpeggien, die den Klang ausbuchstabieren (Verlust der Fläche)
- **Fähigkeiten:** unabhängiges Pedal
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H046 Breiter Moll mit Doppeloktave

- **Charakter:** Mehrstimmiger, weit gelegter Mollklang; Kraft ohne Bewegung.
- **XYZ:** Anker (0,30 / 0,70 / 0,15); gültig X: 0,00–0,60 · Y: 0,40–1,00 · Z: 0,00–0,30; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – offener Moll mit Doppeloktave: 1 (Prime, A), 5 (Quinte, A), ♭3+1Okt (kleine Terz + 1 Okt., A), 1+2Okt (2 Oktaven, A)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld, Umfärbung
- **Geeignet mit:** Drone, Ereignisfelder, langsame Motive. **Ungeeignet:** Arpeggien, die den Klang ausbuchstabieren (Verlust der Fläche)
- **Fähigkeiten:** mehrstimmige LF-Rolle (≥ 4 Stimmen), unabhängiges Pedal, exakte weite Lage (Stimmen > 1,5 Oktaven über Grundton)
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Konstruktion E

#### JC-H047 Moll mit ♭6 oben

- **Charakter:** Offener Moll, darüber die kleine Sexte als Schatten.
- **XYZ:** Anker (0,30 / 0,30 / 0,40); gültig X: 0,10–0,50 · Y: 0,00–0,60 · Z: 0,20–0,60; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – offener Moll (Quinte + Dezime): 1 (Prime, A), 5 (Quinte, A), ♭3+1Okt (kleine Terz + 1 Okt., A), ♭6+1Okt (kleine Sexte + 1 Okt., F)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld, Umfärbung
- **Geeignet mit:** Drone, Ereignisfelder, langsame Motive. **Ungeeignet:** Arpeggien, die den Klang ausbuchstabieren (Verlust der Fläche)
- **Fähigkeiten:** mehrstimmige LF-Rolle (≥ 4 Stimmen), Dissonanz-Autorisierung im Klang, unabhängiges Pedal, exakte weite Lage (Stimmen > 1,5 Oktaven über Grundton)
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H048 Moll-Septakkord

- **Charakter:** Septakkord als stilistisch plausible Ableitung; weich.
- **XYZ:** Anker (0,60 / 0,25 / 0,15); gültig X: 0,40–0,80 · Y: 0,00–0,50 · Z: 0,00–0,30; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – Moll-Septakkord: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A), ♭7 (kleine Septime, A)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld, Umfärbung
- **Geeignet mit:** Drone, Ereignisfelder, langsame Motive. **Ungeeignet:** Arpeggien, die den Klang ausbuchstabieren (Verlust der Fläche)
- **Fähigkeiten:** mehrstimmige LF-Rolle (≥ 4 Stimmen), unabhängiges Pedal
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Konstruktion E

#### JC-H049 Moll mit großer Septime

- **Charakter:** Mystery-Klang mit Leittonspannung; markierte Ableitung.
- **XYZ:** Anker (0,60 / 0,25 / 0,60); gültig X: 0,40–0,80 · Y: 0,00–0,50 · Z: 0,40–0,80; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Harmonisch Moll
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – Moll mit großer Septime: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A), 7 (große Septime, A)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld, Umfärbung
- **Geeignet mit:** Drone, Ereignisfelder, langsame Motive. **Ungeeignet:** Arpeggien, die den Klang ausbuchstabieren (Verlust der Fläche)
- **Fähigkeiten:** mehrstimmige LF-Rolle (≥ 4 Stimmen), unabhängiges Pedal
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Konstruktion E

#### JC-H050 Quartenstapel

- **Charakter:** Vier Quarten übereinander; modale, unbestimmte Farbe.
- **XYZ:** Anker (0,70 / 0,30 / 0,30); gültig X: 0,50–0,90 · Y: 0,00–0,60 · Z: 0,10–0,50; Z-Charakter neutral
- **Modus (Tonvorrat):** Dorisch
- **Rollen:** LF (Klang); Bass: kein Bass empfohlen
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – Quartenstapel: 1 (Prime, A), 4 (Quarte, A), ♭7 (kleine Septime, A), ♭3+1Okt (kleine Terz + 1 Okt., A)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld, Umfärbung
- **Geeignet mit:** Drone, Ereignisfelder, langsame Motive. **Ungeeignet:** Arpeggien, die den Klang ausbuchstabieren (Verlust der Fläche)
- **Fähigkeiten:** mehrstimmige LF-Rolle (≥ 4 Stimmen)
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Konstruktion E

### H8 – Reharmonisierung gleichbleibender Figuren

#### JC-H051 Achse Grundton

- **Charakter:** Alle Klänge enthalten den Grundton; eine darüber liegende Figur auf 1 bleibt Akkordton.
- **XYZ:** Anker (0,40 / 0,40 / 0,30); gültig X: 0,20–0,60 · Y: 0,10–0,70 · Z: 0,10–0,50; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Akkordgrundton (LB/KB)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–4: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T5–8: Grundton ♭6 – Durdreiklang: ♭6 (Prime, A), 1+1Okt (große Terz, A), ♭3+1Okt (Quinte, A)
  - T9–12: Grundton 4 – Molldreiklang: 4 (Prime, A), ♭6 (kleine Terz, A), 1+1Okt (Quinte, A)
  - T13–16: Grundton ♭6 – Durdreiklang: ♭6 (Prime, A), 1+1Okt (große Terz, A), ♭3+1Okt (Quinte, A)
- **Entwicklungsstrategien:** Umfärbung, Wanderung
- **Geeignet mit:** konstante Figuren (Identität „Tonhöhe“), Achsenmotive. **Ungeeignet:** Figuren mit Tönen außerhalb der Achse
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H052 Achse Quinte

- **Charakter:** Alle Klänge enthalten die Quinte des Grundtons.
- **XYZ:** Anker (0,50 / 0,40 / 0,30); gültig X: 0,30–0,70 · Y: 0,10–0,70 · Z: 0,10–0,50; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Akkordgrundton (LB/KB)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–4: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T5–8: Grundton ♭3 – Durdreiklang: ♭3 (Prime, A), 5 (große Terz, A), ♭7 (Quinte, A)
  - T9–12: Grundton 5 – Molldreiklang: 5 (Prime, A), ♭7 (kleine Terz, A), 2+1Okt (Quinte, A)
  - T13–16: Grundton ♭3 – Durdreiklang: ♭3 (Prime, A), 5 (große Terz, A), ♭7 (Quinte, A)
- **Entwicklungsstrategien:** Umfärbung, Wanderung
- **Geeignet mit:** konstante Figuren (Identität „Tonhöhe“), Achsenmotive. **Ungeeignet:** Figuren mit Tönen außerhalb der Achse
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H053 Achse kleine Terz

- **Charakter:** Alle Klänge enthalten die kleine Terz; die Figur wird umgefärbt.
- **XYZ:** Anker (0,60 / 0,35 / 0,20); gültig X: 0,40–0,80 · Y: 0,10–0,60 · Z: 0,00–0,40; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Akkordgrundton (LB/KB)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–4: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T5–8: Grundton ♭6 – Durdreiklang: ♭6 (Prime, A), 1+1Okt (große Terz, A), ♭3+1Okt (Quinte, A)
  - T9–12: Grundton ♭3 – Durdreiklang: ♭3 (Prime, A), 5 (große Terz, A), ♭7 (Quinte, A)
  - T13–16: Grundton ♭6 – Durdreiklang: ♭6 (Prime, A), 1+1Okt (große Terz, A), ♭3+1Okt (Quinte, A)
- **Entwicklungsstrategien:** Umfärbung, Wanderung
- **Geeignet mit:** konstante Figuren (Identität „Tonhöhe“), Achsenmotive. **Ungeeignet:** Figuren mit Tönen außerhalb der Achse
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H054 Achse Quinte, Dur/Moll/sus4

- **Charakter:** Grundton und Quinte bleiben, nur die Terz wechselt.
- **XYZ:** Anker (0,50 / 0,30 / 0,30); gültig X: 0,30–0,70 · Y: 0,00–0,60 · Z: 0,10–0,50; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–2: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T3–4: Grundton 1 – Durdreiklang: 1 (Prime, A), 3 (große Terz, A), 5 (Quinte, A)
  - T5–6: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T7–8: Grundton 1 – sus4: 1 (Prime, A), 4 (Quarte, A), 5 (Quinte, A)
- **Entwicklungsstrategien:** Umfärbung, Wanderung
- **Geeignet mit:** konstante Figuren (Identität „Tonhöhe“), Achsenmotive. **Ungeeignet:** Figuren mit Tönen außerhalb der Achse
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H055 Achse ♭6, phrygisch

- **Charakter:** Gemeinsamer Ton ♭6; dunkle, fremde Umfärbung.
- **XYZ:** Anker (0,20 / 0,50 / 0,60); gültig X: 0,00–0,40 · Y: 0,20–0,80 · Z: 0,40–0,80; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Phrygisch
- **Rollen:** LF (Klang); Bass: Akkordgrundton (LB/KB)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–4: Grundton ♭6 – Durdreiklang: ♭6 (Prime, A), 1+1Okt (große Terz, A), ♭3+1Okt (Quinte, A)
  - T5–8: Grundton ♭2 – Durdreiklang: ♭2 (Prime, A), 4 (große Terz, A), ♭6 (Quinte, A)
  - T9–12: Grundton 4 – Molldreiklang: 4 (Prime, A), ♭6 (kleine Terz, A), 1+1Okt (Quinte, A)
  - T13–16: Grundton ♭2 – Durdreiklang: ♭2 (Prime, A), 4 (große Terz, A), ♭6 (Quinte, A)
- **Entwicklungsstrategien:** Umfärbung, Wanderung
- **Geeignet mit:** konstante Figuren (Identität „Tonhöhe“), Achsenmotive. **Ungeeignet:** Figuren mit Tönen außerhalb der Achse
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Konstruktion E

#### JC-H056 Achse ♭7

- **Charakter:** Gemeinsamer Ton ♭7; kreisend, ohne Tonika.
- **XYZ:** Anker (0,60 / 0,40 / 0,20); gültig X: 0,40–0,80 · Y: 0,10–0,70 · Z: 0,00–0,40; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Akkordgrundton (LB/KB)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–4: Grundton ♭3 – Durdreiklang: ♭3 (Prime, A), 5 (große Terz, A), ♭7 (Quinte, A)
  - T5–8: Grundton 5 – Molldreiklang: 5 (Prime, A), ♭7 (kleine Terz, A), 2+1Okt (Quinte, A)
  - T9–12: Grundton ♭7 – Durdreiklang: ♭7 (Prime, A), 2+1Okt (große Terz, A), 4+1Okt (Quinte, A)
  - T13–16: Grundton 5 – Molldreiklang: 5 (Prime, A), ♭7 (kleine Terz, A), 2+1Okt (Quinte, A)
- **Entwicklungsstrategien:** Umfärbung, Wanderung
- **Geeignet mit:** konstante Figuren (Identität „Tonhöhe“), Achsenmotive. **Ungeeignet:** Figuren mit Tönen außerhalb der Achse
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

### H9 – Cluster und grundtonlose Klangfelder

#### JC-H057 Enger Halbtoncluster

- **Charakter:** Drei Halbtöne übereinander; Klangfläche statt Akkord.
- **XYZ:** Anker (0,15 / 0,30 / 0,80); gültig X: 0,00–0,30 · Y: 0,00–0,60 · Z: 0,60–1,00; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Chromatisch (frei, nur Akkordtöne + autorisierte Töne)
- **Rollen:** LF (Klang); Bass: kein Bass empfohlen
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – Halbtoncluster (3): 1 (Prime, A), ♭2 (kleine Sekunde, U), 2 (große Sekunde, U)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld, Blockverschiebung
- **Geeignet mit:** Drone, Stiche, sehr seltene Einzeltöne. **Ungeeignet:** melodische HM-Linien, Durchgänge
- **Fähigkeiten:** Dissonanz-Autorisierung im Klang
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Konstruktion E

#### JC-H058 Ganztoncluster

- **Charakter:** Weicher als der Halbtoncluster; diffus, nebelhaft.
- **XYZ:** Anker (0,60 / 0,25 / 0,60); gültig X: 0,30–0,90 · Y: 0,00–0,50 · Z: 0,40–0,80; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Chromatisch (frei, nur Akkordtöne + autorisierte Töne)
- **Rollen:** LF (Klang); Bass: kein Bass empfohlen
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – Ganztoncluster (3): 1 (Prime, A), 2 (große Sekunde, U), 3 (große Terz, U)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld, Blockverschiebung
- **Geeignet mit:** Drone, Stiche, sehr seltene Einzeltöne. **Ungeeignet:** melodische HM-Linien, Durchgänge
- **Fähigkeiten:** Dissonanz-Autorisierung im Klang
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H059 Spiegelcluster um die Oktave

- **Charakter:** Grundton, darüber große Septime und ♭9; die Oktave fehlt bewusst.
- **XYZ:** Anker (0,40 / 0,25 / 0,80); gültig X: 0,20–0,60 · Y: 0,00–0,50 · Z: 0,60–1,00; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Chromatisch (frei, nur Akkordtöne + autorisierte Töne)
- **Rollen:** LF (Klang); Bass: kein Bass empfohlen
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – Spiegelcluster um die Oktave: 1 (Prime, A), 7 (große Septime, U), ♭2+1Okt (kleine Sekunde + 1 Okt., U)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld, Blockverschiebung
- **Geeignet mit:** Drone, Stiche, sehr seltene Einzeltöne. **Ungeeignet:** melodische HM-Linien, Durchgänge
- **Fähigkeiten:** Dissonanz-Autorisierung im Klang
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Konstruktion E

#### JC-H060 Doppeltritonus

- **Charakter:** Zwei Tritoni im Halbtonabstand; grundtonlos, bedrohlich.
- **XYZ:** Anker (0,15 / 0,65 / 0,85); gültig X: 0,00–0,30 · Y: 0,30–1,00 · Z: 0,70–1,00; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Chromatisch (frei, nur Akkordtöne + autorisierte Töne)
- **Rollen:** LF (Klang); Bass: kein Bass empfohlen
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – Doppeltritonus: 1 (Prime, A), ♭2 (kleine Sekunde, U), ♯4/♭5 (Tritonus, U), 5 (Quinte, U)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld, Blockverschiebung
- **Geeignet mit:** Drone, Stiche, sehr seltene Einzeltöne. **Ungeeignet:** melodische HM-Linien, Durchgänge
- **Fähigkeiten:** mehrstimmige LF-Rolle (≥ 4 Stimmen), Dissonanz-Autorisierung im Klang
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Konstruktion E

#### JC-H061 Quartklang mit Reibung

- **Charakter:** Quarte mit angelehnten Halbtönen.
- **XYZ:** Anker (0,40 / 0,35 / 0,70); gültig X: 0,20–0,60 · Y: 0,10–0,60 · Z: 0,50–0,90; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Chromatisch (frei, nur Akkordtöne + autorisierte Töne)
- **Rollen:** LF (Klang); Bass: kein Bass empfohlen
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – Quartklang mit Reibung: 1 (Prime, A), 4 (Quarte, A), ♯4/♭5 (Tritonus, U), 7 (große Septime, U)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld, Blockverschiebung
- **Geeignet mit:** Drone, Stiche, sehr seltene Einzeltöne. **Ungeeignet:** melodische HM-Linien, Durchgänge
- **Fähigkeiten:** mehrstimmige LF-Rolle (≥ 4 Stimmen), Dissonanz-Autorisierung im Klang
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Konstruktion E

#### JC-H062 Wanderndes Cluster

- **Charakter:** Der Cluster kriecht um einen Halbton auf und ab.
- **XYZ:** Anker (0,15 / 0,50 / 0,85); gültig X: 0,00–0,30 · Y: 0,20–0,80 · Z: 0,70–1,00; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Chromatisch (frei, nur Akkordtöne + autorisierte Töne)
- **Rollen:** LF (Klang); Bass: kein Bass empfohlen
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–4: Grundton 1 – Halbtoncluster (3): 1 (Prime, A), ♭2 (kleine Sekunde, U), 2 (große Sekunde, U)
  - T5–8: Grundton ♭2 – Halbtoncluster (3): ♭2 (Prime, A), 2 (kleine Sekunde, U), ♭3 (große Sekunde, U)
  - T9–12: Grundton 1 – Halbtoncluster (3): 1 (Prime, A), ♭2 (kleine Sekunde, U), 2 (große Sekunde, U)
  - T13–16: Grundton 7 – Halbtoncluster (3): 7 (Prime, A), 1+1Okt (kleine Sekunde, U), ♭2+1Okt (große Sekunde, U)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld, Blockverschiebung
- **Geeignet mit:** Drone, Stiche, sehr seltene Einzeltöne. **Ungeeignet:** melodische HM-Linien, Durchgänge
- **Fähigkeiten:** Dissonanz-Autorisierung im Klang
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Konstruktion E

### H10 – Bluesisch geprägte Intervallbewegungen

#### JC-H063 Kleinterz-Pendel der Quinten

- **Charakter:** Leere Quinten im Kleinterzabstand; Riff-Grundlage.
- **XYZ:** Anker (0,30 / 0,70 / 0,30); gültig X: 0,10–0,50 · Y: 0,40–1,00 · Z: 0,10–0,50; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang), KF (Pulse); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–4: Grundton 1 – leere Quinte: 1 (Prime, A), 5 (Quinte, A)
  - T5–8: Grundton ♭3 – leere Quinte: ♭3 (Prime, A), ♭7 (Quinte, A)
- **Entwicklungsstrategien:** Rotation, Stasis
- **Geeignet mit:** eigenständige Bassriffs, Oktavbässe. **Ungeeignet:** pulslose Ereignisfelder
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Konstruktion E

#### JC-H064 Quinten i–iv

- **Charakter:** Power-Quinten auf Grundton und Quarte.
- **XYZ:** Anker (0,40 / 0,70 / 0,20); gültig X: 0,20–0,60 · Y: 0,40–1,00 · Z: 0,00–0,40; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang), KF (Pulse); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–4: Grundton 1 – leere Quinte: 1 (Prime, A), 5 (Quinte, A)
  - T5–8: Grundton 4 – leere Quinte: 4 (Prime, A), 1+1Okt (Quinte, A)
- **Entwicklungsstrategien:** Rotation, Stasis
- **Geeignet mit:** eigenständige Bassriffs, Oktavbässe. **Ungeeignet:** pulslose Ereignisfelder
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Konstruktion E

#### JC-H065 Kleinterzkette

- **Charakter:** Quinten auf Grundton, ♭3 und ♭5; bluesige Chromatik, markiert.
- **XYZ:** Anker (0,30 / 0,75 / 0,65); gültig X: 0,00–0,60 · Y: 0,50–1,00 · Z: 0,40–0,90; Z-Charakter mechanisch
- **Modus (Tonvorrat):** Chromatisch (frei, nur Akkordtöne + autorisierte Töne)
- **Rollen:** LF (Klang), KF (Pulse); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–2: Grundton 1 – leere Quinte: 1 (Prime, A), 5 (Quinte, A)
  - T3–4: Grundton ♭3 – leere Quinte: ♭3 (Prime, A), ♭7 (Quinte, A)
  - T5–6: Grundton ♯4/♭5 – leere Quinte: ♯4/♭5 (Prime, A), ♭2+1Okt (Quinte, A)
  - T7–8: Grundton ♭3 – leere Quinte: ♭3 (Prime, A), ♭7 (Quinte, A)
- **Entwicklungsstrategien:** Rotation, Stasis
- **Geeignet mit:** eigenständige Bassriffs, Oktavbässe. **Ungeeignet:** pulslose Ereignisfelder
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Konstruktion E

#### JC-H066 Riffgerüst i–♭VII–♭VI

- **Charakter:** Tragendes Gerüst für Bassriffs; gerade und schwer.
- **XYZ:** Anker (0,30 / 0,75 / 0,30); gültig X: 0,10–0,50 · Y: 0,50–1,00 · Z: 0,10–0,50; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang), KF (Pulse); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–4: Grundton 1 – leere Quinte: 1 (Prime, A), 5 (Quinte, A)
  - T5–6: Grundton ♭7 – leere Quinte: ♭7 (Prime, A), 4+1Okt (Quinte, A)
  - T7–8: Grundton ♭6 – leere Quinte: ♭6 (Prime, A), ♭3+1Okt (Quinte, A)
- **Entwicklungsstrategien:** Rotation, Stasis
- **Geeignet mit:** eigenständige Bassriffs, Oktavbässe. **Ungeeignet:** pulslose Ereignisfelder
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H067 Moll-Pentatonik-Feld

- **Charakter:** Moll-Septakkord mit Undezime: alle fünf pentatonischen Töne in einem Klang; Rahmen für Riffs.
- **XYZ:** Anker (0,50 / 0,55 / 0,20); gültig X: 0,30–0,70 · Y: 0,30–0,80 · Z: 0,00–0,40; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang), KF (Pulse); Bass: Akkordgrundton (LB/KB)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – Moll-Septakkord: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A), ♭7 (kleine Septime, A), 4+1Okt (Quarte + 1 Okt., T)
- **Entwicklungsstrategien:** Rotation, Stasis
- **Geeignet mit:** eigenständige Bassriffs, Oktavbässe. **Ungeeignet:** pulslose Ereignisfelder
- **Fähigkeiten:** mehrstimmige LF-Rolle (≥ 4 Stimmen)
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Konstruktion E

### H11 – Konsonante Klänge in bedrohlichem Kontext

#### JC-H068 Dur über fremdem Pedal

- **Charakter:** Reiner Durklang einen Ganzton über dem gehaltenen Grundton.
- **XYZ:** Anker (0,60 / 0,50 / 0,60); gültig X: 0,40–0,80 · Y: 0,20–0,80 · Z: 0,40–0,80; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Chromatisch (frei, nur Akkordtöne + autorisierte Töne)
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–8: Grundton 2 – Durdreiklang: 2 (Prime, A), ♯4/♭5 (große Terz, A), 6 (Quinte, A)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld
- **Geeignet mit:** einsame hohe Töne, Pedal (autorisiert). **Ungeeignet:** zusätzliche Reibungen in TU/GS
- **Fähigkeiten:** unabhängiges Pedal
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H069 Hoher kalter Durklang

- **Charakter:** Durdreiklang hoch gelegt, ohne Bass; Glas, nicht Freude.
- **XYZ:** Anker (0,85 / 0,20 / 0,15); gültig X: 0,70–1,00 · Y: 0,00–0,40 · Z: 0,00–0,30; Z-Charakter neutral
- **Modus (Tonvorrat):** Ionisch (Dur)
- **Rollen:** LF (Klang); Bass: kein Bass empfohlen
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – Durdreiklang: 1+1Okt (Oktave, A), 3+1Okt (große Terz + 1 Okt., A), 5+1Okt (Quinte + 1 Okt., A)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld
- **Geeignet mit:** einsame hohe Töne, Pedal (autorisiert). **Ungeeignet:** zusätzliche Reibungen in TU/GS
- **Fähigkeiten:** exakte weite Lage (Stimmen > 1,5 Oktaven über Grundton)
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H070 Gespreizter Moll

- **Charakter:** Grundton tief, Quinte und Terz sehr hoch; konsonant, aber leer.
- **XYZ:** Anker (0,70 / 0,20 / 0,15); gültig X: 0,50–0,90 · Y: 0,00–0,40 · Z: 0,00–0,30; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: kein Bass empfohlen
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – gespreizter Moll: 1 (Prime, A), 5+1Okt (Quinte + 1 Okt., A), ♭3+2Okt (kleine Terz + 2 Okt., A)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld
- **Geeignet mit:** einsame hohe Töne, Pedal (autorisiert). **Ungeeignet:** zusätzliche Reibungen in TU/GS
- **Fähigkeiten:** exakte weite Lage (Stimmen > 1,5 Oktaven über Grundton)
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H071 ♭VI als Zentrum

- **Charakter:** Durklang auf ♭VI über Moll-Grundton; Mehrdeutigkeit ohne Dissonanz.
- **XYZ:** Anker (0,60 / 0,25 / 0,25); gültig X: 0,40–0,80 · Y: 0,00–0,50 · Z: 0,10–0,40; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton ♭6 – Durdreiklang: ♭6 (Prime, A), 1+1Okt (große Terz, A), ♭3+1Okt (Quinte, A)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld
- **Geeignet mit:** einsame hohe Töne, Pedal (autorisiert). **Ungeeignet:** zusätzliche Reibungen in TU/GS
- **Fähigkeiten:** unabhängiges Pedal
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H072 Lydische Helle

- **Charakter:** Dur mit hoher ♯4; kalt glänzend, nicht fröhlich. Modale Ableitung.
- **XYZ:** Anker (0,85 / 0,25 / 0,30); gültig X: 0,70–1,00 · Y: 0,00–0,50 · Z: 0,10–0,50; Z-Charakter neutral
- **Modus (Tonvorrat):** Lydisch
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – lydischer Durklang: 1 (Prime, A), 3 (große Terz, A), 5 (Quinte, A), ♯4/♭5+1Okt (Tritonus + 1 Okt., A)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld
- **Geeignet mit:** einsame hohe Töne, Pedal (autorisiert). **Ungeeignet:** zusätzliche Reibungen in TU/GS
- **Fähigkeiten:** mehrstimmige LF-Rolle (≥ 4 Stimmen), unabhängiges Pedal
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Konstruktion E

#### JC-H073 Glasiges Dur add9

- **Charakter:** Dur mit None, hoch; Mystery-Licht.
- **XYZ:** Anker (0,85 / 0,20 / 0,15); gültig X: 0,70–1,00 · Y: 0,00–0,40 · Z: 0,00–0,30; Z-Charakter neutral
- **Modus (Tonvorrat):** Ionisch (Dur)
- **Rollen:** LF (Klang); Bass: kein Bass empfohlen
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – Dur add9: 1 (Prime, A), 3 (große Terz, A), 5 (Quinte, A), 2+1Okt (große Sekunde + 1 Okt., A)
- **Entwicklungsstrategien:** Stasis, Ereignisfeld
- **Geeignet mit:** einsame hohe Töne, Pedal (autorisiert). **Ungeeignet:** zusätzliche Reibungen in TU/GS
- **Fähigkeiten:** mehrstimmige LF-Rolle (≥ 4 Stimmen)
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Konstruktion E

### HX – Ergänzte Mystery-, Melancholie- und Helligkeitsfarben

#### JC-H074 Phrygische Mystery

- **Charakter:** ♭II-Dur über Moll im Wechsel; fremd, aber ruhig.
- **XYZ:** Anker (0,20 / 0,30 / 0,50); gültig X: 0,00–0,40 · Y: 0,00–0,60 · Z: 0,30–0,70; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Phrygisch
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–4: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T5–8: Grundton ♭2 – Durdreiklang: ♭2 (Prime, A), 4 (große Terz, A), ♭6 (Quinte, A)
- **Entwicklungsstrategien:** Stasis, Umfärbung, Ereignisfeld
- **Geeignet mit:** je nach Farbe: Glocken, lyrische Linien, Uhrwerk. **Ungeeignet:** Kombination mehrerer modaler Farben gleichzeitig
- **Fähigkeiten:** unabhängiges Pedal
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Konstruktion E

#### JC-H075 Dorische Kälte

- **Charakter:** Moll mit großer Sexte; kühl, unbestimmt.
- **XYZ:** Anker (0,70 / 0,25 / 0,20); gültig X: 0,50–0,90 · Y: 0,00–0,50 · Z: 0,00–0,40; Z-Charakter neutral
- **Modus (Tonvorrat):** Dorisch
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – Moll mit großer Sexte: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A), 6 (große Sexte, A)
- **Entwicklungsstrategien:** Stasis, Umfärbung, Ereignisfeld
- **Geeignet mit:** je nach Farbe: Glocken, lyrische Linien, Uhrwerk. **Ungeeignet:** Kombination mehrerer modaler Farben gleichzeitig
- **Fähigkeiten:** mehrstimmige LF-Rolle (≥ 4 Stimmen), unabhängiges Pedal
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Konstruktion E

#### JC-H076 Übermäßiger Schatten

- **Charakter:** Moll und übermäßiger ♭III; unheimliche Erweiterung.
- **XYZ:** Anker (0,40 / 0,30 / 0,60); gültig X: 0,20–0,60 · Y: 0,00–0,60 · Z: 0,40–0,80; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Harmonisch Moll
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–8: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T9–16: Grundton ♭3 – übermäßiger Dreiklang: ♭3 (Prime, A), 5 (große Terz, A), 7 (kleine Sexte, A)
- **Entwicklungsstrategien:** Stasis, Umfärbung, Ereignisfeld
- **Geeignet mit:** je nach Farbe: Glocken, lyrische Linien, Uhrwerk. **Ungeeignet:** Kombination mehrerer modaler Farben gleichzeitig
- **Fähigkeiten:** unabhängiges Pedal
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Konstruktion E

#### JC-H077 Melancholischer Kreis

- **Charakter:** Langsamer Kreis mit Durklängen; Trauer ohne Pathos.
- **XYZ:** Anker (0,60 / 0,30 / 0,15); gültig X: 0,40–0,80 · Y: 0,00–0,60 · Z: 0,00–0,30; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Akkordgrundton (LB/KB)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–4: Grundton 1 – Molldreiklang: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A)
  - T5–8: Grundton ♭6 – Durdreiklang: ♭6 (Prime, A), 1+1Okt (große Terz, A), ♭3+1Okt (Quinte, A)
  - T9–12: Grundton ♭3 – Durdreiklang: ♭3 (Prime, A), 5 (große Terz, A), ♭7 (Quinte, A)
  - T13–16: Grundton ♭7 – Durdreiklang: ♭7 (Prime, A), 2+1Okt (große Terz, A), 4+1Okt (Quinte, A)
- **Entwicklungsstrategien:** Stasis, Umfärbung, Ereignisfeld
- **Geeignet mit:** je nach Farbe: Glocken, lyrische Linien, Uhrwerk. **Ungeeignet:** Kombination mehrerer modaler Farben gleichzeitig
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H078 Melancholie add9 nach ♭VI maj7

- **Charakter:** Weiche Erweiterungen; melancholisch, elektronisch.
- **XYZ:** Anker (0,60 / 0,25 / 0,15); gültig X: 0,40–0,80 · Y: 0,00–0,50 · Z: 0,00–0,30; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Akkordgrundton (LB/KB)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–8: Grundton 1 – Moll add9: 1 (Prime, A), ♭3 (kleine Terz, A), 5 (Quinte, A), 2+1Okt (große Sekunde + 1 Okt., A)
  - T9–16: Grundton ♭6 – Dur mit großer Septime: ♭6 (Prime, A), 1+1Okt (große Terz, A), ♭3+1Okt (Quinte, A), 5+1Okt (große Septime, A)
- **Entwicklungsstrategien:** Stasis, Umfärbung, Ereignisfeld
- **Geeignet mit:** je nach Farbe: Glocken, lyrische Linien, Uhrwerk. **Ungeeignet:** Kombination mehrerer modaler Farben gleichzeitig
- **Fähigkeiten:** mehrstimmige LF-Rolle (≥ 4 Stimmen)
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Konstruktion E

#### JC-H079 Lokrische Leere

- **Charakter:** Tritonus und Oktave; leer und unsicher.
- **XYZ:** Anker (0,15 / 0,30 / 0,75); gültig X: 0,00–0,30 · Y: 0,00–0,60 · Z: 0,50–1,00; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Lokrisch
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – Tritonus + Oktave: 1 (Prime, A), ♯4/♭5 (Tritonus, A), 1+1Okt (Oktave, A)
- **Entwicklungsstrategien:** Stasis, Umfärbung, Ereignisfeld
- **Geeignet mit:** je nach Farbe: Glocken, lyrische Linien, Uhrwerk. **Ungeeignet:** Kombination mehrerer modaler Farben gleichzeitig
- **Fähigkeiten:** unabhängiges Pedal
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Konstruktion E

#### JC-H080 Übermäßige Schwebe

- **Charakter:** Übermäßiger Dreiklang; ohne Zentrum, kalt.
- **XYZ:** Anker (0,50 / 0,25 / 0,70); gültig X: 0,30–0,70 · Y: 0,00–0,50 · Z: 0,50–0,90; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Chromatisch (frei, nur Akkordtöne + autorisierte Töne)
- **Rollen:** LF (Klang); Bass: kein Bass empfohlen
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – übermäßiger Dreiklang: 1 (Prime, A), 3 (große Terz, A), ♭6 (kleine Sexte, A)
- **Entwicklungsstrategien:** Stasis, Umfärbung, Ereignisfeld
- **Geeignet mit:** je nach Farbe: Glocken, lyrische Linien, Uhrwerk. **Ungeeignet:** Kombination mehrerer modaler Farben gleichzeitig
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Konstruktion E

#### JC-H081 Heller Quint-Oktav-Turm

- **Charakter:** Quint-Oktav-Turm eine Oktave höher, ohne Bass; kraftvoll, kalt, unbewegt.
- **XYZ:** Anker (0,85 / 0,80 / 0,20); gültig X: 0,70–1,00 · Y: 0,60–1,00 · Z: 0,00–0,40; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: kein Bass empfohlen
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – Quint-Oktav-Turm: 1+1Okt (Oktave, A), 5+1Okt (Quinte + 1 Okt., A), 1+2Okt (2 Oktaven, A), 5+2Okt (Quinte + 2 Okt., A)
- **Entwicklungsstrategien:** Stasis, Umfärbung, Ereignisfeld
- **Geeignet mit:** je nach Farbe: Glocken, lyrische Linien, Uhrwerk. **Ungeeignet:** Kombination mehrerer modaler Farben gleichzeitig
- **Fähigkeiten:** mehrstimmige LF-Rolle (≥ 4 Stimmen), exakte weite Lage (Stimmen > 1,5 Oktaven über Grundton)
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H082 Kraftvolles offenes Dur

- **Charakter:** Offener Durklang mit Dezime; Größe ohne Jubel.
- **XYZ:** Anker (0,80 / 0,80 / 0,20); gültig X: 0,60–1,00 · Y: 0,60–1,00 · Z: 0,00–0,40; Z-Charakter neutral
- **Modus (Tonvorrat):** Ionisch (Dur)
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – offener Dur: 1 (Prime, A), 5 (Quinte, A), 3+1Okt (große Terz + 1 Okt., A)
- **Entwicklungsstrategien:** Stasis, Umfärbung, Ereignisfeld
- **Geeignet mit:** je nach Farbe: Glocken, lyrische Linien, Uhrwerk. **Ungeeignet:** Kombination mehrerer modaler Farben gleichzeitig
- **Fähigkeiten:** unabhängiges Pedal
- **Evidenz:** Verfahren I – begründete Interpretation; Konstruktion E

#### JC-H083 Lydischer Klangwechsel

- **Charakter:** Lydisches I–II; hell, drängend, nicht fröhlich. Modale Ableitung.
- **XYZ:** Anker (0,85 / 0,75 / 0,60); gültig X: 0,70–1,00 · Y: 0,50–1,00 · Z: 0,30–0,90; Z-Charakter neutral
- **Modus (Tonvorrat):** Lydisch
- **Rollen:** LF (Klang); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–4: Grundton 1 – lydischer Durklang: 1 (Prime, A), 3 (große Terz, A), 5 (Quinte, A), ♯4/♭5+1Okt (Tritonus + 1 Okt., A)
  - T5–8: Grundton 2 – Durdreiklang: 2 (Prime, A), ♯4/♭5 (große Terz, A), 6 (Quinte, A)
- **Entwicklungsstrategien:** Stasis, Umfärbung, Ereignisfeld
- **Geeignet mit:** je nach Farbe: Glocken, lyrische Linien, Uhrwerk. **Ungeeignet:** Kombination mehrerer modaler Farben gleichzeitig
- **Fähigkeiten:** mehrstimmige LF-Rolle (≥ 4 Stimmen)
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Konstruktion E

#### JC-H084 Helles Halbton-Blockpendel

- **Charakter:** sus2-Klang rückt einen Halbton hoch und zurück; helle Variante der Blockverschiebung.
- **XYZ:** Anker (0,80 / 0,65 / 0,80); gültig X: 0,60–1,00 · Y: 0,30–1,00 · Z: 0,60–1,00; Z-Charakter mechanisch
- **Modus (Tonvorrat):** Chromatisch (frei, nur Akkordtöne + autorisierte Töne)
- **Rollen:** LF (Klang); Bass: Akkordgrundton (LB/KB)
- **Periode:** 8 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–4: Grundton 1 – sus2: 1 (Prime, A), 2 (große Sekunde, A), 5 (Quinte, A)
  - T5–8: Grundton ♭2 – sus2: ♭2 (Prime, A), ♭3 (große Sekunde, A), ♭6 (Quinte, A)
- **Entwicklungsstrategien:** Stasis, Umfärbung, Ereignisfeld
- **Geeignet mit:** je nach Farbe: Glocken, lyrische Linien, Uhrwerk. **Ungeeignet:** Kombination mehrerer modaler Farben gleichzeitig
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Konstruktion E

#### JC-H085 Großterz-Zyklus

- **Charakter:** Durklänge im Großterzabstand, 6-Takt-Periode; glänzend und haltlos.
- **XYZ:** Anker (0,75 / 0,70 / 0,75); gültig X: 0,50–1,00 · Y: 0,40–1,00 · Z: 0,50–1,00; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Chromatisch (frei, nur Akkordtöne + autorisierte Töne)
- **Rollen:** LF (Klang); Bass: Akkordgrundton (LB/KB)
- **Periode:** 6 Takte (nicht 2ⁿ – läuft gegen 8er-Phrasen)
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–2: Grundton 1 – Durdreiklang: 1 (Prime, A), 3 (große Terz, A), 5 (Quinte, A)
  - T3–4: Grundton 3 – Durdreiklang: 3 (Prime, A), ♭6 (große Terz, A), 7 (Quinte, A)
  - T5–6: Grundton ♭6 – Durdreiklang: ♭6 (Prime, A), 1+1Okt (große Terz, A), ♭3+1Okt (Quinte, A)
- **Entwicklungsstrategien:** Stasis, Umfärbung, Ereignisfeld
- **Geeignet mit:** je nach Farbe: Glocken, lyrische Linien, Uhrwerk. **Ungeeignet:** Kombination mehrerer modaler Farben gleichzeitig
- **Fähigkeiten:** ungerade Harmonieperiode
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Konstruktion E

#### JC-H086 Gläserne Reibung

- **Charakter:** Hoher sus2 mit ♭9; hell, leise, beunruhigend.
- **XYZ:** Anker (0,85 / 0,20 / 0,80); gültig X: 0,70–1,00 · Y: 0,00–0,40 · Z: 0,60–1,00; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Ionisch (Dur)
- **Rollen:** LF (Klang); Bass: kein Bass empfohlen
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – sus2: 1+1Okt (Oktave, A), 2+1Okt (große Sekunde + 1 Okt., A), 5+1Okt (Quinte + 1 Okt., A), ♭2+2Okt (kleine Sekunde + 2 Okt., U)
- **Entwicklungsstrategien:** Stasis, Umfärbung, Ereignisfeld
- **Geeignet mit:** je nach Farbe: Glocken, lyrische Linien, Uhrwerk. **Ungeeignet:** Kombination mehrerer modaler Farben gleichzeitig
- **Fähigkeiten:** mehrstimmige LF-Rolle (≥ 4 Stimmen), Dissonanz-Autorisierung im Klang, exakte weite Lage (Stimmen > 1,5 Oktaven über Grundton)
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Konstruktion E

#### JC-H087 Heller Ganztoncluster

- **Charakter:** Ganztoncluster hoch gelegt; Nebel aus Licht.
- **XYZ:** Anker (0,80 / 0,25 / 0,80); gültig X: 0,60–1,00 · Y: 0,00–0,50 · Z: 0,60–1,00; Z-Charakter psychologisch
- **Modus (Tonvorrat):** Chromatisch (frei, nur Akkordtöne + autorisierte Töne)
- **Rollen:** LF (Klang); Bass: kein Bass empfohlen
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – Ganztoncluster (3): 1+1Okt (Oktave, A), 2+1Okt (große Sekunde + 1 Okt., U), 3+1Okt (große Terz + 1 Okt., U)
- **Entwicklungsstrategien:** Stasis, Umfärbung, Ereignisfeld
- **Geeignet mit:** je nach Farbe: Glocken, lyrische Linien, Uhrwerk. **Ungeeignet:** Kombination mehrerer modaler Farben gleichzeitig
- **Fähigkeiten:** Dissonanz-Autorisierung im Klang
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Konstruktion E

#### JC-H088 Tiefe Mollsäule

- **Charakter:** Offener Moll sehr tief; dunkle Ruhe.
- **XYZ:** Anker (0,15 / 0,50 / 0,15); gültig X: 0,00–0,30 · Y: 0,00–1,00 · Z: 0,00–0,30; Z-Charakter neutral
- **Modus (Tonvorrat):** Äolisch (natürliches Moll)
- **Rollen:** LF (Klang); Bass: Pedal auf Grundton (LB, unabhängig)
- **Periode:** 16 Takte
- **Klänge (relativ, Intervall vom Klanggrundton, Funktion):**
  - T1–16: Grundton 1 – offener Moll (Quinte + Dezime): 1 (Prime, A), 5 (Quinte, A), ♭3+1Okt (kleine Terz + 1 Okt., A)
- **Entwicklungsstrategien:** Stasis, Umfärbung, Ereignisfeld
- **Geeignet mit:** je nach Farbe: Glocken, lyrische Linien, Uhrwerk. **Ungeeignet:** Kombination mehrerer modaler Farben gleichzeitig
- **Fähigkeiten:** unabhängiges Pedal
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Konstruktion E

## 4. R – Rhythmik

Muster: X Akzent, x normal, o leise, . Pause, _ Verlängerung. Positionen in Ticks ab Periodenbeginn. Ungerade Metrik ist eine charakteristische Möglichkeit, kein Pflichtmerkmal.

#### JC-R001 Viertelpuls

- **Charakter:** Gleichmäßiger Viertelpuls; der Referenzpuls der Howarth-Ära.
- **Taktart / Raster / Periode:** 4/4 · 4 · 3840 Ticks = 1,00 Takte
- **Muster:** `xxxx`
- **Einsätze (4):** 0, 960, 1920, 2880 (! = Akzent, ° = leise)
- **Notendauern:** 480 Ticks (Gate 0,50)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,60 / 0,20); gültig X: 0,00–1,00 · Y: 0,20–1,00 · Z: 0,00–0,40 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren

#### JC-R002 Achtelpuls

- **Charakter:** Durchlaufende Achtel; Grundlage pulsierender Bässe.
- **Taktart / Raster / Periode:** 4/4 · 8 · 3840 Ticks = 1,00 Takte
- **Muster:** `xxxxxxxx`
- **Einsätze (8):** 0, 480, 960, 1440, 1920, 2400, 2880, 3360 (! = Akzent, ° = leise)
- **Notendauern:** 216 Ticks (Gate 0,45)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,60 / 0,40); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,20–0,60 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren

#### JC-R003 Sechzehntelpuls

- **Charakter:** Dichter Maschinenpuls; nur mit sehr kurzem Gate.
- **Taktart / Raster / Periode:** 4/4 · 16 · 3840 Ticks = 1,00 Takte
- **Muster:** `xxxxxxxxxxxxxxxx`
- **Einsätze (16):** 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600 (! = Akzent, ° = leise)
- **Notendauern:** 84 Ticks (Gate 0,35)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,70 / 0,70); gültig X: 0,00–1,00 · Y: 0,40–1,00 · Z: 0,40–1,00 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren

#### JC-R004 Achtel mit Taktakzent

- **Charakter:** Erste Achtel betont; ordnet den Puls.
- **Taktart / Raster / Periode:** 4/4 · 8 · 3840 Ticks = 1,00 Takte
- **Muster:** `Xxxxxxxx`
- **Einsätze (8):** 0!, 480, 960, 1440, 1920, 2400, 2880, 3360 (! = Akzent, ° = leise)
- **Notendauern:** 216 Ticks (Gate 0,45)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,60 / 0,30); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,10–0,50 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren

#### JC-R005 Achtel mit Offbeat-Akzent

- **Charakter:** Betonte Offbeats; treibend, rockig.
- **Taktart / Raster / Periode:** 4/4 · 8 · 3840 Ticks = 1,00 Takte
- **Muster:** `xXxXxXxX`
- **Einsätze (8):** 0, 480!, 960, 1440!, 1920, 2400!, 2880, 3360! (! = Akzent, ° = leise)
- **Notendauern:** 216 Ticks (Gate 0,45)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,70 / 0,50); gültig X: 0,00–1,00 · Y: 0,40–1,00 · Z: 0,30–0,70 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren I – begründete Interpretation

#### JC-R006 Halbe-Puls

- **Charakter:** Zwei lange Schläge pro Takt; ruhig, schwer.
- **Taktart / Raster / Periode:** 4/4 · 2 · 3840 Ticks = 1,00 Takte
- **Muster:** `xx`
- **Einsätze (2):** 0, 1920 (! = Akzent, ° = leise)
- **Notendauern:** 1632 Ticks (Gate 0,85)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,50 / 0,15); gültig X: 0,00–1,00 · Y: 0,00–1,00 · Z: 0,00–0,30 · färbungsunabhängig; Z-Charakter neutral
- **Evidenz:** Verfahren I – begründete Interpretation

#### JC-R007 Ein Schlag pro Takt

- **Charakter:** Ein kurzer Schlag am Taktanfang, dann Leere.
- **Taktart / Raster / Periode:** 4/4 · 1 · 3840 Ticks = 1,00 Takte
- **Muster:** `x`
- **Einsätze (1):** 0 (! = Akzent, ° = leise)
- **Notendauern:** 768 Ticks (Gate 0,20)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,25 / 0,20); gültig X: 0,00–1,00 · Y: 0,00–0,50 · Z: 0,00–0,40 · färbungsunabhängig; Z-Charakter neutral
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren

#### JC-R008 Herzschlag

- **Charakter:** Schwer–leicht-Paar, dann Pause; der Fog/Assault-Herzschlag als Verfahren.
- **Taktart / Raster / Periode:** 4/4 · 16 · 3840 Ticks = 1,00 Takte
- **Muster:** `X..x............`
- **Einsätze (2):** 0!, 720 (! = Akzent, ° = leise)
- **Notendauern:** 72 Ticks (Gate 0,30)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,45 / 0,45); gültig X: 0,00–1,00 · Y: 0,10–0,80 · Z: 0,20–0,70 · färbungsunabhängig; Z-Charakter psychologisch
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren

#### JC-R009 Langsamer Herzschlag

- **Charakter:** Ein Herzschlag-Paar alle zwei Takte.
- **Taktart / Raster / Periode:** 4/4 · 16 · 7680 Ticks = 2,00 Takte
- **Muster:** `X..x............................`
- **Einsätze (2):** 0!, 720 (! = Akzent, ° = leise)
- **Notendauern:** 72 Ticks (Gate 0,30)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,30 / 0,30); gültig X: 0,00–1,00 · Y: 0,00–0,60 · Z: 0,10–0,50 · färbungsunabhängig; Z-Charakter psychologisch
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren

#### JC-R010 Doppelter Herzschlag

- **Charakter:** Zwei Paare pro Takt; erregter Puls bei gleichem Tempo.
- **Taktart / Raster / Periode:** 4/4 · 16 · 3840 Ticks = 1,00 Takte
- **Muster:** `X..x....X..x....`
- **Einsätze (4):** 0!, 720, 1920!, 2640 (! = Akzent, ° = leise)
- **Notendauern:** 72 Ticks (Gate 0,30)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,60 / 0,60); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,40–0,80 · färbungsunabhängig; Z-Charakter psychologisch
- **Evidenz:** Verfahren I – begründete Interpretation

#### JC-R011 Stockender Herzschlag

- **Charakter:** Drei-Takt-Periode, das Paar verschiebt sich und fällt einmal aus.
- **Taktart / Raster / Periode:** 4/4 · 16 · 11520 Ticks = 3,00 Takte
- **Muster:** `X..x................X..x........................`
- **Einsätze (4):** 0!, 720, 4800!, 5520 (! = Akzent, ° = leise)
- **Notendauern:** 72 Ticks (Gate 0,30)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,35 / 0,80); gültig X: 0,00–1,00 · Y: 0,00–0,70 · Z: 0,60–1,00 · färbungsunabhängig; Z-Charakter psychologisch
- **Evidenz:** Verfahren E – eigenständige Gestaltung

#### JC-R012 Gedämpfter Einzelschlag

- **Charakter:** Zwei leise Schläge, dann ein ganzer Takt Stille.
- **Taktart / Raster / Periode:** 4/4 · 16 · 7680 Ticks = 2,00 Takte
- **Muster:** `o.......o.......................`
- **Einsätze (2):** 0°, 1920° (! = Akzent, ° = leise)
- **Notendauern:** 84 Ticks (Gate 0,35)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,20 / 0,20); gültig X: 0,00–1,00 · Y: 0,00–0,40 · Z: 0,00–0,40 · färbungsunabhängig; Z-Charakter psychologisch
- **Evidenz:** Verfahren I – begründete Interpretation

#### JC-R013 Staccato-Achtel

- **Charakter:** Sehr kurze Achtel; tickend, trocken.
- **Taktart / Raster / Periode:** 4/4 · 8 · 3840 Ticks = 1,00 Takte
- **Muster:** `xxxxxxxx`
- **Einsätze (8):** 0, 480, 960, 1440, 1920, 2400, 2880, 3360 (! = Akzent, ° = leise)
- **Notendauern:** 106 Ticks (Gate 0,22)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,50 / 0,55); gültig X: 0,00–1,00 · Y: 0,20–0,80 · Z: 0,30–0,80 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren

#### JC-R014 Legato-Achtel

- **Charakter:** Fast gebundene Achtel; ein ziehender Strom.
- **Taktart / Raster / Periode:** 4/4 · 8 · 3840 Ticks = 1,00 Takte
- **Muster:** `xxxxxxxx`
- **Einsätze (8):** 0, 480, 960, 1440, 1920, 2400, 2880, 3360 (! = Akzent, ° = leise)
- **Notendauern:** 456 Ticks (Gate 0,95)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,60 / 0,20); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,00–0,40 · färbungsunabhängig; Z-Charakter neutral
- **Evidenz:** Verfahren I – begründete Interpretation

#### JC-R015 Galopp

- **Charakter:** Lang–kurz–kurz; Verfolgung.
- **Taktart / Raster / Periode:** 4/4 · 16 · 3840 Ticks = 1,00 Takte
- **Muster:** `x.xxx.xxx.xxx.xx`
- **Einsätze (12):** 0, 480, 720, 960, 1440, 1680, 1920, 2400, 2640, 2880, 3360, 3600 (! = Akzent, ° = leise)
- **Notendauern:** 96 Ticks (Gate 0,40)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,75 / 0,75); gültig X: 0,00–1,00 · Y: 0,50–1,00 · Z: 0,50–1,00 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren I – begründete Interpretation

#### JC-R016 Triolen-Repetition

- **Charakter:** Durchlaufende Achteltriolen; kreisend.
- **Taktart / Raster / Periode:** 4/4 · 8t · 3840 Ticks = 1,00 Takte
- **Muster:** `xxxxxxxxxxxx`
- **Einsätze (12):** 0, 320, 640, 960, 1280, 1600, 1920, 2240, 2560, 2880, 3200, 3520 (! = Akzent, ° = leise)
- **Notendauern:** 128 Ticks (Gate 0,40)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,70 / 0,55); gültig X: 0,00–1,00 · Y: 0,40–1,00 · Z: 0,30–0,80 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren I – begründete Interpretation

#### JC-R017 Viertel-Triolen

- **Charakter:** Drei gegen zwei Viertel; das Prince-of-Darkness-Triolenverfahren.
- **Taktart / Raster / Periode:** 4/4 · 4t · 3840 Ticks = 1,00 Takte
- **Muster:** `Xxxxxx`
- **Einsätze (6):** 0!, 640, 1280, 1920, 2560, 3200 (! = Akzent, ° = leise)
- **Notendauern:** 384 Ticks (Gate 0,60)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,40 / 0,40); gültig X: 0,00–1,00 · Y: 0,10–0,70 · Z: 0,20–0,60 · färbungsunabhängig; Z-Charakter psychologisch
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren

#### JC-R018 Punktierte Viertel

- **Charakter:** 3+3+2 in Sechzehnteln gedehnt; schwerfälliges Schreiten.
- **Taktart / Raster / Periode:** 4/4 · 16 · 3840 Ticks = 1,00 Takte
- **Muster:** `x.....x.....x...`
- **Einsätze (3):** 0, 1440, 2880 (! = Akzent, ° = leise)
- **Notendauern:** 168 Ticks (Gate 0,70)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,50 / 0,40); gültig X: 0,00–1,00 · Y: 0,20–0,80 · Z: 0,20–0,60 · färbungsunabhängig; Z-Charakter neutral
- **Evidenz:** Verfahren I – begründete Interpretation

#### JC-R019 Ganze Noten

- **Charakter:** Ein Klang pro Takt, voll gehalten.
- **Taktart / Raster / Periode:** 4/4 · 1 · 3840 Ticks = 1,00 Takte
- **Muster:** `x`
- **Einsätze (1):** 0 (! = Akzent, ° = leise)
- **Notendauern:** 3763 Ticks (Gate 0,98)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,50 / 0,10); gültig X: 0,00–1,00 · Y: 0,00–1,00 · Z: 0,00–0,20 · färbungsunabhängig; Z-Charakter neutral
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren

#### JC-R020 Tresillo

- **Charakter:** 3+3+2 Achtel mit Akzent auf der Eins.
- **Taktart / Raster / Periode:** 4/4 · 8 · 3840 Ticks = 1,00 Takte
- **Muster:** `X..x..x.`
- **Einsätze (3):** 0!, 1440, 2880 (! = Akzent, ° = leise)
- **Notendauern:** 192 Ticks (Gate 0,40)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,60 / 0,40); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,20–0,60 · färbungsunabhängig; Z-Charakter neutral
- **Evidenz:** Verfahren I – begründete Interpretation

#### JC-R021 Synkope über den Taktstrich

- **Charakter:** Schläge vor dem Taktanfang, übergebunden; die Eins fehlt.
- **Taktart / Raster / Periode:** 4/4 · 8 · 7680 Ticks = 2,00 Takte
- **Muster:** `x......x_......x`
- **Einsätze (3):** 0, 3360, 7200 (! = Akzent, ° = leise)
- **Notendauern:** 408, 816 Ticks (Gate 0,85)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,45 / 0,50); gültig X: 0,00–1,00 · Y: 0,20–0,70 · Z: 0,30–0,70 · färbungsunabhängig; Z-Charakter psychologisch
- **Evidenz:** Verfahren E – eigenständige Gestaltung

#### JC-R022 Vorgezogener Schlag

- **Charakter:** Die letzte Achtel zieht den nächsten Takt vor.
- **Taktart / Raster / Periode:** 4/4 · 8 · 3840 Ticks = 1,00 Takte
- **Muster:** `x.....x_`
- **Einsätze (2):** 0, 2880 (! = Akzent, ° = leise)
- **Notendauern:** 288, 576 Ticks (Gate 0,60)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,50 / 0,40); gültig X: 0,00–1,00 · Y: 0,20–0,80 · Z: 0,20–0,60 · färbungsunabhängig; Z-Charakter neutral
- **Evidenz:** Verfahren I – begründete Interpretation

#### JC-R023 Sechzehntel-Synkope

- **Charakter:** 3+3+4+3+3; rollend, nicht gerade.
- **Taktart / Raster / Periode:** 4/4 · 16 · 3840 Ticks = 1,00 Takte
- **Muster:** `x..x..x...x..x..`
- **Einsätze (5):** 0, 720, 1440, 2400, 3120 (! = Akzent, ° = leise)
- **Notendauern:** 84 Ticks (Gate 0,35)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,70 / 0,60); gültig X: 0,00–1,00 · Y: 0,40–1,00 · Z: 0,40–0,80 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren I – begründete Interpretation

#### JC-R024 5/4 als 3+3+2+2

- **Charakter:** Die belegte Halloween-Gruppierung als allgemeines Verfahren (eigene Konstruktion).
- **Taktart / Raster / Periode:** 5/4 · 8 · 4800 Ticks = 1,00 Takte
- **Muster:** `XxxXxxXxXx`
- **Einsätze (10):** 0!, 480, 960, 1440!, 1920, 2400, 2880!, 3360, 3840!, 4320 (! = Akzent, ° = leise)
- **Notendauern:** 192 Ticks (Gate 0,40)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,65 / 0,65); gültig X: 0,00–1,00 · Y: 0,30–1,00 · Z: 0,40–0,90 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren

#### JC-R025 5/4 als 2+3 Viertel

- **Charakter:** Fünfertakt in Vierteln; schwankend.
- **Taktart / Raster / Periode:** 5/4 · 4 · 4800 Ticks = 1,00 Takte
- **Muster:** `XxXxx`
- **Einsätze (5):** 0!, 960, 1920!, 2880, 3840 (! = Akzent, ° = leise)
- **Notendauern:** 480 Ticks (Gate 0,50)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,50 / 0,50); gültig X: 0,00–1,00 · Y: 0,20–0,80 · Z: 0,30–0,70 · färbungsunabhängig; Z-Charakter neutral
- **Evidenz:** Verfahren I – begründete Interpretation

#### JC-R026 7/8 als 2+2+3

- **Charakter:** Siebener mit langem Schluss; stolpernd.
- **Taktart / Raster / Periode:** 7/8 · 8 · 3360 Ticks = 1,00 Takte
- **Muster:** `XxXxXxx`
- **Einsätze (7):** 0!, 480, 960!, 1440, 1920!, 2400, 2880 (! = Akzent, ° = leise)
- **Notendauern:** 192 Ticks (Gate 0,40)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,60 / 0,60); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,40–0,80 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren E – eigenständige Gestaltung

#### JC-R027 7/8 als 3+2+2

- **Charakter:** Siebener mit langem Beginn.
- **Taktart / Raster / Periode:** 7/8 · 8 · 3360 Ticks = 1,00 Takte
- **Muster:** `XxxXxXx`
- **Einsätze (7):** 0!, 480, 960, 1440!, 1920, 2400!, 2880 (! = Akzent, ° = leise)
- **Notendauern:** 192 Ticks (Gate 0,40)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,60 / 0,60); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,40–0,80 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren E – eigenständige Gestaltung

#### JC-R028 4/4 als 3+3+3+3+2+2

- **Charakter:** Asymmetrische Akzente im geraden Takt, Notendichte konstant.
- **Taktart / Raster / Periode:** 4/4 · 16 · 3840 Ticks = 1,00 Takte
- **Muster:** `XxxXxxXxxXxxXxXx`
- **Einsätze (16):** 0!, 240, 480, 720!, 960, 1200, 1440!, 1680, 1920, 2160!, 2400, 2640, 2880!, 3120, 3360!, 3600 (! = Akzent, ° = leise)
- **Notendauern:** 84 Ticks (Gate 0,35)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,70 / 0,65); gültig X: 0,00–1,00 · Y: 0,40–1,00 · Z: 0,40–0,90 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren I – begründete Interpretation

#### JC-R029 4/4 als 3+3+2 Achtel

- **Charakter:** Durchlaufende Achtel, nur die Betonung ist ungerade.
- **Taktart / Raster / Periode:** 4/4 · 8 · 3840 Ticks = 1,00 Takte
- **Muster:** `XxxXxxXx`
- **Einsätze (8):** 0!, 480, 960, 1440!, 1920, 2400, 2880!, 3360 (! = Akzent, ° = leise)
- **Notendauern:** 202 Ticks (Gate 0,42)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,60 / 0,50); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,30–0,70 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren I – begründete Interpretation

#### JC-R030 9/8 als 2+2+2+3

- **Charakter:** Neuner mit verlängertem Schlussglied.
- **Taktart / Raster / Periode:** 9/8 · 8 · 4320 Ticks = 1,00 Takte
- **Muster:** `XxXxXxXxx`
- **Einsätze (9):** 0!, 480, 960!, 1440, 1920!, 2400, 2880!, 3360, 3840 (! = Akzent, ° = leise)
- **Notendauern:** 202 Ticks (Gate 0,42)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,60 / 0,60); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,40–0,80 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren E – eigenständige Gestaltung

#### JC-R031 6/8-Hemiole

- **Charakter:** Im 6/8 wie 3/4 betont; die Takteinheit schwankt.
- **Taktart / Raster / Periode:** 6/8 · 8 · 2880 Ticks = 1,00 Takte
- **Muster:** `XxXxXx`
- **Einsätze (6):** 0!, 480, 960!, 1440, 1920!, 2400 (! = Akzent, ° = leise)
- **Notendauern:** 216 Ticks (Gate 0,45)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,50 / 0,50); gültig X: 0,00–1,00 · Y: 0,20–0,80 · Z: 0,30–0,70 · färbungsunabhängig; Z-Charakter psychologisch
- **Evidenz:** Verfahren E – eigenständige Gestaltung

#### JC-R032 Achteltriolen betont

- **Charakter:** Klare Dreiergruppen.
- **Taktart / Raster / Periode:** 4/4 · 8t · 3840 Ticks = 1,00 Takte
- **Muster:** `XxxXxxXxxXxx`
- **Einsätze (12):** 0!, 320, 640, 960!, 1280, 1600, 1920!, 2240, 2560, 2880!, 3200, 3520 (! = Akzent, ° = leise)
- **Notendauern:** 122 Ticks (Gate 0,38)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,60 / 0,40); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,20–0,60 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren I – begründete Interpretation

#### JC-R033 Triolen mit Lücke

- **Charakter:** Jede dritte Triole fehlt; hinkend.
- **Taktart / Raster / Periode:** 4/4 · 8t · 3840 Ticks = 1,00 Takte
- **Muster:** `Xx.Xx.Xx.Xx.`
- **Einsätze (8):** 0!, 320, 960!, 1280, 1920!, 2240, 2880!, 3200 (! = Akzent, ° = leise)
- **Notendauern:** 122 Ticks (Gate 0,38)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,50 / 0,50); gültig X: 0,00–1,00 · Y: 0,20–0,80 · Z: 0,30–0,70 · färbungsunabhängig; Z-Charakter psychologisch
- **Evidenz:** Verfahren E – eigenständige Gestaltung

#### JC-R034 Kriechende Triolen

- **Charakter:** Zwei lange Viertel-Triolen pro Takt; schleppend.
- **Taktart / Raster / Periode:** 4/4 · 4t · 3840 Ticks = 1,00 Takte
- **Muster:** `x..x..`
- **Einsätze (2):** 0, 1920 (! = Akzent, ° = leise)
- **Notendauern:** 576 Ticks (Gate 0,90)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,30 / 0,30); gültig X: 0,00–1,00 · Y: 0,00–0,60 · Z: 0,10–0,50 · färbungsunabhängig; Z-Charakter psychologisch
- **Evidenz:** Verfahren I – begründete Interpretation

#### JC-R035 Triolen-Herzschlag

- **Charakter:** Herzschlag in Triolen; weicher als in Sechzehnteln.
- **Taktart / Raster / Periode:** 4/4 · 8t · 3840 Ticks = 1,00 Takte
- **Muster:** `X.x.........`
- **Einsätze (2):** 0!, 640 (! = Akzent, ° = leise)
- **Notendauern:** 128 Ticks (Gate 0,40)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,40 / 0,50); gültig X: 0,00–1,00 · Y: 0,10–0,70 · Z: 0,30–0,70 · färbungsunabhängig; Z-Charakter psychologisch
- **Evidenz:** Verfahren E – eigenständige Gestaltung

#### JC-R036 12/8 schreitend

- **Charakter:** Wiegendes Schreiten im Zwölfer.
- **Taktart / Raster / Periode:** 12/8 · 8 · 5760 Ticks = 1,00 Takte
- **Muster:** `X..x..X..x..`
- **Einsätze (4):** 0!, 1440, 2880!, 4320 (! = Akzent, ° = leise)
- **Notendauern:** 336 Ticks (Gate 0,70)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,50 / 0,20); gültig X: 0,00–1,00 · Y: 0,20–0,80 · Z: 0,00–0,40 · färbungsunabhängig; Z-Charakter neutral
- **Evidenz:** Verfahren I – begründete Interpretation

#### JC-R037 Staccatissimo-Achtel

- **Charakter:** Extrem kurze Töne; fast nur Klick.
- **Taktart / Raster / Periode:** 4/4 · 8 · 3840 Ticks = 1,00 Takte
- **Muster:** `xxxxxxxx`
- **Einsätze (8):** 0, 480, 960, 1440, 1920, 2400, 2880, 3360 (! = Akzent, ° = leise)
- **Notendauern:** 58 Ticks (Gate 0,12)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,45 / 0,65); gültig X: 0,00–1,00 · Y: 0,20–0,70 · Z: 0,40–0,90 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren I – begründete Interpretation

#### JC-R038 Gate-Wechsel lang–kurz

- **Charakter:** Lange und kurze Achtel im Wechsel bei gleicher Dichte.
- **Taktart / Raster / Periode:** 4/4 · 8 · 3840 Ticks = 1,00 Takte
- **Muster:** `xxxxxxxx`
- **Einsätze (8):** 0, 480, 960, 1440, 1920, 2400, 2880, 3360 (! = Akzent, ° = leise)
- **Notendauern:** 96, 432 Ticks (Gate 0,50, Gate-Liste)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,55 / 0,40); gültig X: 0,00–1,00 · Y: 0,30–0,80 · Z: 0,20–0,60 · färbungsunabhängig; Z-Charakter neutral
- **Evidenz:** Verfahren E – eigenständige Gestaltung

#### JC-R039 Wachsendes Gate

- **Charakter:** Über vier Takte werden die Töne länger.
- **Taktart / Raster / Periode:** 4/4 · 8 · 15360 Ticks = 4,00 Takte
- **Muster:** `xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx`
- **Einsätze (32):** 0, 480, 960, 1440, 1920, 2400, 2880, 3360, 3840, 4320, 4800, 5280, 5760, 6240, 6720, 7200, 7680, 8160, 8640, 9120, 9600, 10080, 10560, 11040, 11520, 12000, 12480, 12960, 13440, 13920, 14400, 14880 (! = Akzent, ° = leise)
- **Notendauern:** 72, 168, 288, 432 Ticks (Gate 0,50, Gate-Liste)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,50 / 0,30); gültig X: 0,00–1,00 · Y: 0,20–0,80 · Z: 0,10–0,50 · färbungsunabhängig; Z-Charakter neutral
- **Evidenz:** Verfahren E – eigenständige Gestaltung

#### JC-R040 Schrumpfendes Gate

- **Charakter:** Über vier Takte werden die Töne kürzer.
- **Taktart / Raster / Periode:** 4/4 · 8 · 15360 Ticks = 4,00 Takte
- **Muster:** `xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx`
- **Einsätze (32):** 0, 480, 960, 1440, 1920, 2400, 2880, 3360, 3840, 4320, 4800, 5280, 5760, 6240, 6720, 7200, 7680, 8160, 8640, 9120, 9600, 10080, 10560, 11040, 11520, 12000, 12480, 12960, 13440, 13920, 14400, 14880 (! = Akzent, ° = leise)
- **Notendauern:** 72, 168, 288, 432 Ticks (Gate 0,50, Gate-Liste)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,50 / 0,50); gültig X: 0,00–1,00 · Y: 0,20–0,80 · Z: 0,30–0,70 · färbungsunabhängig; Z-Charakter psychologisch
- **Evidenz:** Verfahren E – eigenständige Gestaltung

#### JC-R041 Drei Takte an, einer aus

- **Charakter:** Der Puls atmet: drei Takte, dann ein leerer Takt.
- **Taktart / Raster / Periode:** 4/4 · 8 · 15360 Ticks = 4,00 Takte
- **Muster:** `xxxxxxxxxxxxxxxxxxxxxxxx........`
- **Einsätze (24):** 0, 480, 960, 1440, 1920, 2400, 2880, 3360, 3840, 4320, 4800, 5280, 5760, 6240, 6720, 7200, 7680, 8160, 8640, 9120, 9600, 10080, 10560, 11040 (! = Akzent, ° = leise)
- **Notendauern:** 216 Ticks (Gate 0,45)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,55 / 0,40); gültig X: 0,00–1,00 · Y: 0,20–0,90 · Z: 0,20–0,60 · färbungsunabhängig; Z-Charakter neutral
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren

#### JC-R042 Zwei an, zwei aus

- **Charakter:** Gleichmäßiges Ein- und Aussetzen.
- **Taktart / Raster / Periode:** 4/4 · 8 · 15360 Ticks = 4,00 Takte
- **Muster:** `xxxxxxxxxxxxxxxx................`
- **Einsätze (16):** 0, 480, 960, 1440, 1920, 2400, 2880, 3360, 3840, 4320, 4800, 5280, 5760, 6240, 6720, 7200 (! = Akzent, ° = leise)
- **Notendauern:** 216 Ticks (Gate 0,45)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,45 / 0,40); gültig X: 0,00–1,00 · Y: 0,10–0,80 · Z: 0,20–0,60 · färbungsunabhängig; Z-Charakter neutral
- **Evidenz:** Verfahren I – begründete Interpretation

#### JC-R043 Fehlende Zählzeit

- **Charakter:** Jeder Takt endet mit einer Lücke.
- **Taktart / Raster / Periode:** 4/4 · 8 · 3840 Ticks = 1,00 Takte
- **Muster:** `xxxxxx..`
- **Einsätze (6):** 0, 480, 960, 1440, 1920, 2400 (! = Akzent, ° = leise)
- **Notendauern:** 216 Ticks (Gate 0,45)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,50 / 0,50); gültig X: 0,00–1,00 · Y: 0,20–0,80 · Z: 0,30–0,70 · färbungsunabhängig; Z-Charakter psychologisch
- **Evidenz:** Verfahren E – eigenständige Gestaltung

#### JC-R044 Sieben an, einer aus

- **Charakter:** Lange Puls-Phase mit einem einzigen Atemloch.
- **Taktart / Raster / Periode:** 4/4 · 8 · 30720 Ticks = 8,00 Takte
- **Muster:** `xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx........`
- **Einsätze (56):** 0, 480, 960, 1440, 1920, 2400, 2880, 3360, 3840, 4320, 4800, 5280, 5760, 6240, 6720, 7200, 7680, 8160, 8640, 9120, 9600, 10080, 10560, 11040, 11520, 12000, 12480, 12960, 13440, 13920, 14400, 14880, 15360, 15840, 16320, 16800, 17280, 17760, 18240, 18720, 19200, 19680, 20160, 20640, 21120, 21600, 22080, 22560, 23040, 23520, 24000, 24480, 24960, 25440, 25920, 26400 (! = Akzent, ° = leise)
- **Notendauern:** 216 Ticks (Gate 0,45)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,55 / 0,30); gültig X: 0,00–1,00 · Y: 0,20–0,90 · Z: 0,10–0,50 · färbungsunabhängig; Z-Charakter neutral
- **Evidenz:** Verfahren E – eigenständige Gestaltung

#### JC-R045 Ein Ton alle zwei Takte

- **Charakter:** Maximaler Leerraum mit festem Wiederkehrpunkt.
- **Taktart / Raster / Periode:** 4/4 · 16 · 7680 Ticks = 2,00 Takte
- **Muster:** `x...............................`
- **Einsätze (1):** 0 (! = Akzent, ° = leise)
- **Notendauern:** 72 Ticks (Gate 0,30)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,20 / 0,20); gültig X: 0,00–1,00 · Y: 0,00–0,40 · Z: 0,00–0,40 · färbungsunabhängig; Z-Charakter neutral
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren

#### JC-R046 Einsamer Offbeat

- **Charakter:** Ein Ton auf der Zwei-und; nie auf der Eins.
- **Taktart / Raster / Periode:** 4/4 · 8 · 3840 Ticks = 1,00 Takte
- **Muster:** `.x......`
- **Einsätze (1):** 480 (! = Akzent, ° = leise)
- **Notendauern:** 144 Ticks (Gate 0,30)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,25 / 0,40); gültig X: 0,00–1,00 · Y: 0,00–0,50 · Z: 0,20–0,60 · färbungsunabhängig; Z-Charakter psychologisch
- **Evidenz:** Verfahren E – eigenständige Gestaltung

#### JC-R047 Halber Takt, dann Stille

- **Charakter:** Kurzer Puls-Ausbruch, drei Takte Leere.
- **Taktart / Raster / Periode:** 4/4 · 8 · 15360 Ticks = 4,00 Takte
- **Muster:** `xxxx............................`
- **Einsätze (4):** 0, 480, 960, 1440 (! = Akzent, ° = leise)
- **Notendauern:** 216 Ticks (Gate 0,45)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,30 / 0,40); gültig X: 0,00–1,00 · Y: 0,00–0,60 · Z: 0,20–0,60 · färbungsunabhängig; Z-Charakter psychologisch
- **Evidenz:** Verfahren E – eigenständige Gestaltung

#### JC-R048 Abstandsreihe 5-3-7

- **Charakter:** Ereignisse nach 5, 3 und 7 Takten; 15-Takt-Periode, ohne Zufall.
- **Taktart / Raster / Periode:** 4/4 · 1 · 57600 Ticks = 15,00 Takte
- **Muster:** `x....x..x......`
- **Einsätze (3):** 0, 19200, 30720 (! = Akzent, ° = leise)
- **Notendauern:** 960 Ticks (Gate 0,25)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,25 / 0,60); gültig X: 0,00–1,00 · Y: 0,00–0,50 · Z: 0,20–1,00 · färbungsunabhängig; Z-Charakter psychologisch
- **Evidenz:** Verfahren E – eigenständige Gestaltung

#### JC-R049 Abstandsreihe 7-11

- **Charakter:** Zwei Ereignisse in 18 Takten.
- **Taktart / Raster / Periode:** 4/4 · 1 · 69120 Ticks = 18,00 Takte
- **Muster:** `x......x..........`
- **Einsätze (2):** 0, 26880 (! = Akzent, ° = leise)
- **Notendauern:** 960 Ticks (Gate 0,25)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,20 / 0,35); gültig X: 0,00–1,00 · Y: 0,00–0,40 · Z: 0,10–0,60 · färbungsunabhängig; Z-Charakter psychologisch
- **Evidenz:** Verfahren E – eigenständige Gestaltung

#### JC-R050 Verschobenes Einzelereignis

- **Charakter:** Sechs-Takt-Periode, zwei Ereignisse an ungeraden Positionen.
- **Taktart / Raster / Periode:** 4/4 · 16 · 23040 Ticks = 6,00 Takte
- **Muster:** `......x......................................x..................................................`
- **Einsätze (2):** 1440, 10800 (! = Akzent, ° = leise)
- **Notendauern:** 72 Ticks (Gate 0,30)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,25 / 0,70); gültig X: 0,00–1,00 · Y: 0,00–0,50 · Z: 0,40–1,00 · färbungsunabhängig; Z-Charakter psychologisch
- **Evidenz:** Verfahren E – eigenständige Gestaltung

#### JC-R051 Seltenes Doppelereignis

- **Charakter:** Ein kurzes Paar, dann fast sechs Takte nichts.
- **Taktart / Raster / Periode:** 4/4 · 16 · 23040 Ticks = 6,00 Takte
- **Muster:** `x.x.............................................................................................`
- **Einsätze (2):** 0, 480 (! = Akzent, ° = leise)
- **Notendauern:** 72 Ticks (Gate 0,30)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,25 / 0,55); gültig X: 0,00–1,00 · Y: 0,00–0,50 · Z: 0,30–0,80 · färbungsunabhängig; Z-Charakter psychologisch
- **Evidenz:** Verfahren E – eigenständige Gestaltung

#### JC-R052 Komplement A: Schlag

- **Charakter:** Auf den Zählzeiten; Partner zu Komplement B.
- **Taktart / Raster / Periode:** 4/4 · 8 · 3840 Ticks = 1,00 Takte
- **Muster:** `x.x.x.x.`
- **Einsätze (4):** 0, 960, 1920, 2880 (! = Akzent, ° = leise)
- **Notendauern:** 216 Ticks (Gate 0,45)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,60 / 0,40); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,20–0,60 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren

#### JC-R053 Komplement B: Offbeat

- **Charakter:** Zwischen den Zählzeiten; Partner zu Komplement A.
- **Taktart / Raster / Periode:** 4/4 · 8 · 3840 Ticks = 1,00 Takte
- **Muster:** `.x.x.x.x`
- **Einsätze (4):** 480, 1440, 2400, 3360 (! = Akzent, ° = leise)
- **Notendauern:** 216 Ticks (Gate 0,45)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,60 / 0,40); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,20–0,60 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren

#### JC-R054 Tresillo-Komplement

- **Charakter:** Füllt genau die Lücken des Tresillo.
- **Taktart / Raster / Periode:** 4/4 · 8 · 3840 Ticks = 1,00 Takte
- **Muster:** `.xx.xx.x`
- **Einsätze (5):** 480, 960, 1920, 2400, 3360 (! = Akzent, ° = leise)
- **Notendauern:** 192 Ticks (Gate 0,40)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,60 / 0,50); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,30–0,70 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren I – begründete Interpretation

#### JC-R055 Kreuz A

- **Charakter:** Sechzehntel-Figur der ersten Takthälfte.
- **Taktart / Raster / Periode:** 4/4 · 16 · 3840 Ticks = 1,00 Takte
- **Muster:** `x.x..x.x........`
- **Einsätze (4):** 0, 480, 1200, 1680 (! = Akzent, ° = leise)
- **Notendauern:** 84 Ticks (Gate 0,35)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,70 / 0,60); gültig X: 0,00–1,00 · Y: 0,40–1,00 · Z: 0,40–0,80 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren I – begründete Interpretation

#### JC-R056 Kreuz B

- **Charakter:** Ergänzt Kreuz A zur lückenlosen Halbtakt-Fläche.
- **Taktart / Raster / Periode:** 4/4 · 16 · 3840 Ticks = 1,00 Takte
- **Muster:** `.x.xx.x.........`
- **Einsätze (4):** 240, 720, 960, 1440 (! = Akzent, ° = leise)
- **Notendauern:** 84 Ticks (Gate 0,35)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,70 / 0,60); gültig X: 0,00–1,00 · Y: 0,40–1,00 · Z: 0,40–0,80 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren I – begründete Interpretation

#### JC-R057 Verdichtungsleiter

- **Charakter:** Dichte verdoppelt sich je Takt bei gleicher Harmonie.
- **Taktart / Raster / Periode:** 4/4 · 8 · 15360 Ticks = 4,00 Takte
- **Muster:** `x.......x...x...x.x.x.x.xxxxxxxx`
- **Einsätze (15):** 0, 3840, 5760, 7680, 8640, 9600, 10560, 11520, 12000, 12480, 12960, 13440, 13920, 14400, 14880 (! = Akzent, ° = leise)
- **Notendauern:** 192 Ticks (Gate 0,40)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,60 / 0,50); gültig X: 0,00–1,00 · Y: 0,20–1,00 · Z: 0,20–0,80 · färbungsunabhängig; Z-Charakter neutral
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren

#### JC-R058 Stolper-Achtel

- **Charakter:** Gleiche Dichte wie Achtel, eine Achtel verrutscht; Halloween-III-Verfahren.
- **Taktart / Raster / Periode:** 4/4 · 16 · 3840 Ticks = 1,00 Takte
- **Muster:** `x.x.x.x..xx.x.x.`
- **Einsätze (8):** 0, 480, 960, 1440, 2160, 2400, 2880, 3360 (! = Akzent, ° = leise)
- **Notendauern:** 84 Ticks (Gate 0,35)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,65 / 0,75); gültig X: 0,00–1,00 · Y: 0,30–1,00 · Z: 0,50–1,00 · färbungsunabhängig; Z-Charakter psychologisch
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren

#### JC-R059 Wandernder Akzent

- **Charakter:** Achtel bleiben, der Akzent rückt pro Takt weiter.
- **Taktart / Raster / Periode:** 4/4 · 8 · 15360 Ticks = 4,00 Takte
- **Muster:** `XxxxxxxxxXxxxxxxxxXxxxxxxxxXxxxx`
- **Einsätze (32):** 0!, 480, 960, 1440, 1920, 2400, 2880, 3360, 3840, 4320!, 4800, 5280, 5760, 6240, 6720, 7200, 7680, 8160, 8640!, 9120, 9600, 10080, 10560, 11040, 11520, 12000, 12480, 12960!, 13440, 13920, 14400, 14880 (! = Akzent, ° = leise)
- **Notendauern:** 202 Ticks (Gate 0,42)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,60 / 0,60); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,40–0,80 · färbungsunabhängig; Z-Charakter psychologisch
- **Evidenz:** Verfahren E – eigenständige Gestaltung

#### JC-R060 Rotierende Lücke

- **Charakter:** Pro Takt fehlt eine andere Achtel.
- **Taktart / Raster / Periode:** 4/4 · 8 · 15360 Ticks = 4,00 Takte
- **Muster:** `.xxxxxxxxx.xxxxxxxxx.xxxxxxxxx.x`
- **Einsätze (28):** 480, 960, 1440, 1920, 2400, 2880, 3360, 3840, 4320, 5280, 5760, 6240, 6720, 7200, 7680, 8160, 8640, 9120, 10080, 10560, 11040, 11520, 12000, 12480, 12960, 13440, 13920, 14880 (! = Akzent, ° = leise)
- **Notendauern:** 202 Ticks (Gate 0,42)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,60 / 0,60); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,40–0,80 · färbungsunabhängig; Z-Charakter psychologisch
- **Evidenz:** Verfahren E – eigenständige Gestaltung

#### JC-R061 Uhrwerk tick-tack

- **Charakter:** Gleichmäßiges Ticken mit schwach–stark; das Uhrwerk-Verfahren aus Halloween III.
- **Taktart / Raster / Periode:** 4/4 · 16 · 3840 Ticks = 1,00 Takte
- **Muster:** `XoxoXoxoXoxoXoxo`
- **Einsätze (16):** 0!, 240°, 480, 720°, 960!, 1200°, 1440, 1680°, 1920!, 2160°, 2400, 2640°, 2880!, 3120°, 3360, 3600° (! = Akzent, ° = leise)
- **Notendauern:** 48 Ticks (Gate 0,20)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,50 / 0,70); gültig X: 0,00–1,00 · Y: 0,20–0,80 · Z: 0,50–0,90 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren

#### JC-R062 Dreier-Uhrwerk im Vierer

- **Charakter:** Drei-Sechzehntel-Periode über geradem Takt; unabhängige Periode, für Carpenter nicht belegt.
- **Taktart / Raster / Periode:** 4/4 · 16 · 720 Ticks = 0,19 Takte · **unabhängige Periode** (gemeinsame SYNTH-Fähigkeit)
- **Muster:** `Xxx`
- **Einsätze (3):** 0!, 240, 480 (! = Akzent, ° = leise)
- **Notendauern:** 60 Ticks (Gate 0,25)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,65 / 0,80); gültig X: 0,00–1,00 · Y: 0,30–1,00 · Z: 0,60–1,00 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung)

#### JC-R063 Fünfer-Uhrwerk im Vierer

- **Charakter:** Fünf-Sechzehntel-Periode; unabhängige Periode, nicht belegt.
- **Taktart / Raster / Periode:** 4/4 · 16 · 1200 Ticks = 0,31 Takte · **unabhängige Periode** (gemeinsame SYNTH-Fähigkeit)
- **Muster:** `Xxxxx`
- **Einsätze (5):** 0!, 240, 480, 720, 960 (! = Akzent, ° = leise)
- **Notendauern:** 60 Ticks (Gate 0,25)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,60 / 0,80); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,60–1,00 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung)

#### JC-R064 Zweitakt-Ostinato

- **Charakter:** Zwei Takte mit unterschiedlicher zweiter Hälfte.
- **Taktart / Raster / Periode:** 4/4 · 16 · 7680 Ticks = 2,00 Takte
- **Muster:** `X.x.x..xX.x..x.xX.x.x..x.xx.x...`
- **Einsätze (15):** 0!, 480, 960, 1680, 1920!, 2400, 3120, 3600, 3840!, 4320, 4800, 5520, 6000, 6240, 6720 (! = Akzent, ° = leise)
- **Notendauern:** 84 Ticks (Gate 0,35)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,70 / 0,50); gültig X: 0,00–1,00 · Y: 0,40–1,00 · Z: 0,30–0,70 · färbungsunabhängig; Z-Charakter neutral
- **Evidenz:** Verfahren I – begründete Interpretation

#### JC-R065 Viertakt-Phrase mit Schlussluft

- **Charakter:** Drei volle Takte, der vierte endet halb.
- **Taktart / Raster / Periode:** 4/4 · 8 · 15360 Ticks = 4,00 Takte
- **Muster:** `xxxxxxxxxxxxxxxxxxxxxxxxxxxx....`
- **Einsätze (28):** 0, 480, 960, 1440, 1920, 2400, 2880, 3360, 3840, 4320, 4800, 5280, 5760, 6240, 6720, 7200, 7680, 8160, 8640, 9120, 9600, 10080, 10560, 11040, 11520, 12000, 12480, 12960 (! = Akzent, ° = leise)
- **Notendauern:** 216 Ticks (Gate 0,45)
- **Akzentregel:** gleichmäßig (x = 88); Akzente nur über JC-T010
- **XYZ:** Anker (0,50 / 0,60 / 0,30); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,10–0,50 · färbungsunabhängig; Z-Charakter neutral
- **Evidenz:** Verfahren I – begründete Interpretation

#### JC-R066 Schwere Halbe und Viertel

- **Charakter:** Halbe, dann zwei Viertel; Kraft ohne Hektik.
- **Taktart / Raster / Periode:** 4/4 · 4 · 3840 Ticks = 1,00 Takte
- **Muster:** `X_xx`
- **Einsätze (3):** 0!, 1920, 2880 (! = Akzent, ° = leise)
- **Notendauern:** 864, 1728 Ticks (Gate 0,90)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,75 / 0,20); gültig X: 0,00–1,00 · Y: 0,50–1,00 · Z: 0,00–0,40 · färbungsunabhängig; Z-Charakter neutral
- **Evidenz:** Verfahren I – begründete Interpretation

#### JC-R067 Galopp-Triole

- **Charakter:** Lang–kurz in Triolen; reitende Verfolgung.
- **Taktart / Raster / Periode:** 4/4 · 8t · 3840 Ticks = 1,00 Takte
- **Muster:** `X.xX.xX.xX.x`
- **Einsätze (8):** 0!, 640, 960!, 1600, 1920!, 2560, 2880!, 3520 (! = Akzent, ° = leise)
- **Notendauern:** 144 Ticks (Gate 0,45)
- **Akzentregel:** Akzent nach Muster; Velocity X 112 / x 88 / o 62
- **XYZ:** Anker (0,50 / 0,75 / 0,70); gültig X: 0,00–1,00 · Y: 0,50–1,00 · Z: 0,50–0,90 · färbungsunabhängig; Z-Charakter mechanisch
- **Evidenz:** Verfahren E – eigenständige Gestaltung

## 5. Q – Sequencer-Tonfolgen

Sequencer-Tonfolgen sind keine Akkordarpeggien: sie sind eigenständige Figuren mit fester Identität. Bezugston 0 ist der Grundton der Tonart (Schalter „Folgt Akkorden“ aus) oder, wenn ausdrücklich gewünscht, der jeweilige Akkordgrundton. Geeignet für AR und GS, tiefe Fassungen für KB.

#### JC-Q001 Einzelton-Achtelstrom

- **Charakter:** Ein einziger Ton im Achtelpuls; trägt über jeder Harmonie, die ihn enthält.
- **Tonfolge (1 Töne):** 0 → 1
- **Rhythmus:** JC-R002 Achtelpuls (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 216 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A
- **Identität:** Erhalten: Tonhöhe(n). Variabel: Rhythmus, Gate, Akzente, Dichte.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung, JC-T011 Unterbrechung und Wiederaufnahme, JC-T016 Velocity-Atmung
- **Entwicklungsstrategien:** Stasis, Umfärbung, Atmung
- **XYZ:** Anker (0,50 / 0,50 / 0,35); gültig X: 0,00–1,00 · Y: 0,20–0,80 · Z: 0,10–0,60; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-Q002 Betonte Quint-Repetition

- **Charakter:** Die Quinte als Repetitionston; neutraler als der Grundton.
- **Tonfolge (1 Töne):** +7 → 5
- **Rhythmus:** JC-R004 Achtel mit Taktakzent (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 216 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 5=A
- **Identität:** Erhalten: Tonhöhe(n). Variabel: Rhythmus, Gate, Akzente, Dichte.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung, JC-T010 Akzentgruppen-Variation
- **Entwicklungsstrategien:** Stasis, Umfärbung, Atmung
- **XYZ:** Anker (0,50 / 0,60 / 0,30); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,10–0,50; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q003 Reibungs-Repetition ♭2

- **Charakter:** Staccato-Repetition auf dem oberen Halbtonnachbarn; bewusst ungelöst.
- **Tonfolge (1 Töne):** +1 → ♭2
- **Rhythmus:** JC-R013 Staccato-Achtel (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 106 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** ♭2=U · autorisiert: ♭2→U
- **Identität:** Erhalten: Tonhöhe(n). Variabel: Rhythmus, Gate, Akzente, Dichte.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung, JC-T011 Unterbrechung und Wiederaufnahme
- **Entwicklungsstrategien:** Stasis, Umfärbung, Atmung
- **XYZ:** Anker (0,20 / 0,40 / 0,75); gültig X: 0,00–0,40 · Y: 0,10–0,70 · Z: 0,50–1,00; Z-Charakter psychologisch
- **Fähigkeiten:** Dissonanz-Autorisierung
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q004 Oktav-Wiege

- **Charakter:** Grundton und Oktave im Wechsel; das belegte „Oktav-Wiegen“ als eigene Figur.
- **Tonfolge (2 Töne):** 0 +12 → 1 1+1Okt
- **Intervalle:** Oktave↑
- **Rhythmus:** JC-R002 Achtelpuls (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 216 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1+1Okt=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung, JC-T010 Akzentgruppen-Variation, JC-T011 Unterbrechung und Wiederaufnahme
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,50 / 0,60 / 0,40); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,20–0,60; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-Q005 Quint-Wiege

- **Charakter:** Grundton–Quinte; leer, stabil.
- **Tonfolge (2 Töne):** 0 +7 → 1 5
- **Intervalle:** Quinte↑
- **Rhythmus:** JC-R002 Achtelpuls (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 216 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 5=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung, JC-T010 Akzentgruppen-Variation
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,50 / 0,55 / 0,30); gültig X: 0,00–1,00 · Y: 0,20–0,90 · Z: 0,10–0,50; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q006 Quartfall-Staccato

- **Charakter:** Grundton und tiefere Quinte, sehr kurz.
- **Tonfolge (2 Töne):** 0 -5 → 1 5-1Okt
- **Intervalle:** Quarte↓
- **Rhythmus:** JC-R013 Staccato-Achtel (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 106 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 5-1Okt=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,50 / 0,50 / 0,40); gültig X: 0,00–1,00 · Y: 0,20–0,80 · Z: 0,20–0,60; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q007 Halbton-Wiege

- **Charakter:** Sechzehntel zwischen Grundton und ♭2; nervös, ohne Auflösung.
- **Tonfolge (2 Töne):** 0 +1 → 1 ♭2
- **Intervalle:** kleine Sekunde↑
- **Rhythmus:** JC-R003 Sechzehntelpuls (4/4, 16 Einsätze, Periode 3840 Ticks); Positionen: 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600; Dauern: 84 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, ♭2=U · autorisiert: ♭2→U
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung, JC-T013 Kontrollierte Verdichtung, JC-T014 Kontrollierte Reduktion
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,20 / 0,65 / 0,80); gültig X: 0,00–0,40 · Y: 0,30–1,00 · Z: 0,60–1,00; Z-Charakter psychologisch
- **Fähigkeiten:** Dissonanz-Autorisierung
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-Q008 Ganzton-Wiege

- **Charakter:** Gebundenes Pendel zur None; leise Unruhe.
- **Tonfolge (2 Töne):** 0 +2 → 1 2
- **Intervalle:** große Sekunde↑
- **Rhythmus:** JC-R014 Legato-Achtel (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 456 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 2=T
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,55 / 0,40 / 0,40); gültig X: 0,30–0,80 · Y: 0,10–0,70 · Z: 0,20–0,60; Z-Charakter psychologisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q009 Kleinterz im Tresillo

- **Charakter:** Grundton–Terz–Grundton auf 3+3+2.
- **Tonfolge (3 Töne):** 0 +3 0 → 1 ♭3 1
- **Intervalle:** kleine Terz↑, kleine Terz↓
- **Rhythmus:** JC-R020 Tresillo (4/4, 3 Einsätze, Periode 3840 Ticks); Positionen: 0, 1440, 2880; Dauern: 192 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, ♭3=A, 1=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T010 Akzentgruppen-Variation
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,35 / 0,60 / 0,40); gültig X: 0,10–0,60 · Y: 0,30–0,90 · Z: 0,20–0,60; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q010 Leitton-Zucken

- **Charakter:** Oktave, Grundton, Leitton, Grundton; der Leitton zieht, löst sich aber nie.
- **Tonfolge (4 Töne):** +12 0 +11 0 → 1+1Okt 1 7 1
- **Intervalle:** Oktave↓, große Septime↑, große Septime↓
- **Rhythmus:** JC-R003 Sechzehntelpuls (4/4, 16 Einsätze, Periode 3840 Ticks); Positionen: 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600; Dauern: 84 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Harmonisch Moll
- **Tonfunktionen:** 1+1Okt=A, 1=A, 7=T, 1=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T002 Einzeltonvariation, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,30 / 0,70 / 0,70); gültig X: 0,10–0,50 · Y: 0,40–1,00 · Z: 0,50–0,90; Z-Charakter psychologisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q011 Quint–Oktav–Quint

- **Charakter:** Viertonzelle aus Quinte und Oktave; neutral gegenüber Dur/Moll.
- **Tonfolge (4 Töne):** 0 +7 +12 +7 → 1 5 1+1Okt 5
- **Intervalle:** Quinte↑, Quarte↑, Quarte↓
- **Rhythmus:** JC-R003 Sechzehntelpuls (4/4, 16 Einsätze, Periode 3840 Ticks); Positionen: 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600; Dauern: 84 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 5=A, 1+1Okt=A, 5=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T002 Einzeltonvariation, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung, JC-T010 Akzentgruppen-Variation
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,50 / 0,65 / 0,50); gültig X: 0,00–1,00 · Y: 0,30–1,00 · Z: 0,30–0,70; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-Q012 Moll-Triolenaufstieg

- **Charakter:** Molldreiklang in Achteltriolen; kreisend.
- **Tonfolge (3 Töne):** 0 +3 +7 → 1 ♭3 5
- **Intervalle:** kleine Terz↑, große Terz↑
- **Rhythmus:** JC-R032 Achteltriolen betont (4/4, 12 Einsätze, Periode 3840 Ticks); Positionen: 0, 320, 640, 960, 1280, 1600, 1920, 2240, 2560, 2880, 3200, 3520; Dauern: 122 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, ♭3=A, 5=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,40 / 0,60 / 0,40); gültig X: 0,20–0,60 · Y: 0,30–0,90 · Z: 0,20–0,60; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q013 Quinte mit Halbtonschatten

- **Charakter:** Die Quinte wird vom ♭6 bedrängt.
- **Tonfolge (4 Töne):** 0 +7 +8 +7 → 1 5 ♭6 5
- **Intervalle:** Quinte↑, kleine Sekunde↑, kleine Sekunde↓
- **Rhythmus:** JC-R003 Sechzehntelpuls (4/4, 16 Einsätze, Periode 3840 Ticks); Positionen: 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600; Dauern: 84 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 5=A, ♭6=T, 5=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T002 Einzeltonvariation, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,25 / 0,65 / 0,60); gültig X: 0,00–0,50 · Y: 0,30–1,00 · Z: 0,40–0,80; Z-Charakter psychologisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-Q014 Fünfer-Zelle 3+3+2+2

- **Charakter:** Eigene Konstruktion im belegten 5/4-Akzentverfahren; Kontur und Gruppierung sind die Identität.
- **Tonfolge (10 Töne):** 0 +10 +3 0 +10 +3 0 +7 0 +5 → 1 ♭7 ♭3 1 ♭7 ♭3 1 5 1 4
- **Intervalle:** kleine Septime↑, Quinte↓, kleine Terz↓, kleine Septime↑, Quinte↓, kleine Terz↓, Quinte↑, Quinte↓, Quarte↑
- **Rhythmus:** JC-R024 5/4 als 3+3+2+2 (5/4, 10 Einsätze, Periode 4800 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360, 3840, 4320; Dauern: 192 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, ♭7=T, ♭3=A, 1=A, ♭7=T, ♭3=A, 1=A, 5=A, 1=A, 4=T
- **Identität:** Erhalten: Akzentgruppierung und Kontur. Variabel: Transposition, Gate, Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T002 Einzeltonvariation, JC-T003 Oktavverlagerung, JC-T010 Akzentgruppen-Variation
- **Entwicklungsstrategien:** Stasis, Blockverschiebung
- **XYZ:** Anker (0,30 / 0,70 / 0,75); gültig X: 0,00–0,60 · Y: 0,40–1,00 · Z: 0,50–1,00; Z-Charakter mechanisch
- **Fähigkeiten:** lange Sequenz (> 8 Töne)
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-Q015 Uhrwerk-Quinte

- **Charakter:** Tick-tack zwischen Grundton und Quinte; jede achte Note ein Halbton höher.
- **Tonfolge (8 Töne):** 0 +7 0 +7 0 +7 0 +8 → 1 5 1 5 1 5 1 ♭6
- **Intervalle:** Quinte↑, Quinte↓, Quinte↑, Quinte↓, Quinte↑, Quinte↓, kleine Sexte↑
- **Rhythmus:** JC-R061 Uhrwerk tick-tack (4/4, 16 Einsätze, Periode 3840 Ticks); Positionen: 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600; Dauern: 48 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 5=A, 1=A, 5=A, 1=A, 5=A, 1=A, ♭6=T
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T002 Einzeltonvariation, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,50 / 0,50 / 0,70); gültig X: 0,00–1,00 · Y: 0,20–0,80 · Z: 0,50–0,90; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-Q016 Fallendes Uhrwerk

- **Charakter:** Absteigende Viertonzelle im Tick-Raster; verrinnende Zeit.
- **Tonfolge (4 Töne):** +12 +10 +8 +7 → 1+1Okt ♭7 ♭6 5
- **Intervalle:** große Sekunde↓, große Sekunde↓, kleine Sekunde↓
- **Rhythmus:** JC-R061 Uhrwerk tick-tack (4/4, 16 Einsätze, Periode 3840 Ticks); Positionen: 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600; Dauern: 48 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1+1Okt=A, ♭7=T, ♭6=T, 5=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,30 / 0,50 / 0,70); gültig X: 0,00–0,60 · Y: 0,20–0,80 · Z: 0,50–0,90; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-Q017 Melancholische Achtelkette

- **Charakter:** Gebundene Achtel um die Mollterz; die None als Durchgang.
- **Tonfolge (8 Töne):** +7 +3 0 +3 +7 +3 +2 +3 → 5 ♭3 1 ♭3 5 ♭3 2 ♭3
- **Intervalle:** große Terz↓, kleine Terz↓, kleine Terz↑, große Terz↑, große Terz↓, kleine Sekunde↓, kleine Sekunde↑
- **Rhythmus:** JC-R014 Legato-Achtel (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 456 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 5=A, ♭3=A, 1=A, ♭3=A, 5=A, ♭3=A, 2=T, ♭3=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T002 Einzeltonvariation, JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,50 / 0,30 / 0,20); gültig X: 0,30–0,70 · Y: 0,00–0,60 · Z: 0,00–0,40; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q018 Dur-Wiege

- **Charakter:** Durfigur für Umfärbungs-Abschnitte; kalt durch Register, nicht durch Harmonik.
- **Tonfolge (4 Töne):** 0 +4 +7 +4 → 1 3 5 3
- **Intervalle:** große Terz↑, kleine Terz↑, kleine Terz↓
- **Rhythmus:** JC-R002 Achtelpuls (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 216 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Durdreiklang auf 1, Tonvorrat Ionisch (Dur)
- **Tonfunktionen:** 1=A, 3=A, 5=A, 3=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,80 / 0,40 / 0,20); gültig X: 0,60–1,00 · Y: 0,10–0,70 · Z: 0,00–0,40; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q019 Paarweise Tonwechsel

- **Charakter:** Rhythmus konstant, Tonhöhe wechselt in Paaren.
- **Tonfolge (8 Töne):** 0 0 +3 +3 +5 +5 +3 +3 → 1 1 ♭3 ♭3 4 4 ♭3 ♭3
- **Intervalle:** Prime, kleine Terz↑, Prime, große Sekunde↑, Prime, große Sekunde↓, Prime
- **Rhythmus:** JC-R002 Achtelpuls (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 216 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1=A, ♭3=A, ♭3=A, 4=T, 4=T, ♭3=A, ♭3=A
- **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T002 Einzeltonvariation, JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **Entwicklungsstrategien:** Stasis, Rotation, Atmung
- **XYZ:** Anker (0,50 / 0,60 / 0,40); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,20–0,60; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q020 Wandernde Betonung

- **Charakter:** Feste Viertonfolge; der Akzent rückt jeden Takt weiter.
- **Tonfolge (4 Töne):** 0 +7 +12 +7 → 1 5 1+1Okt 5
- **Intervalle:** Quinte↑, Quarte↑, Quarte↓
- **Rhythmus:** JC-R059 Wandernder Akzent (4/4, 32 Einsätze, Periode 15360 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360, 3840, 4320, 4800, 5280, 5760, 6240, 6720, 7200, 7680, 8160, 8640, 9120, 9600, 10080, 10560, 11040, 11520, 12000, 12480, 12960, 13440, 13920, 14400, 14880; Dauern: 202 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 5=A, 1+1Okt=A, 5=A
- **Identität:** Erhalten: Tonhöhe(n). Variabel: Rhythmus, Gate, Akzente, Dichte.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T010 Akzentgruppen-Variation
- **Entwicklungsstrategien:** Stasis, Umfärbung, Atmung
- **XYZ:** Anker (0,50 / 0,60 / 0,60); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,40–0,80; Z-Charakter psychologisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Tonfolge E

#### JC-Q021 Blockzelle Oktave–Quarte

- **Charakter:** Für Halbton-Blocktransposition gedacht; die Intervalle bleiben immer gleich.
- **Tonfolge (4 Töne):** 0 +12 +5 +12 → 1 1+1Okt 4 1+1Okt
- **Intervalle:** Oktave↑, Quinte↓, Quinte↑
- **Rhythmus:** JC-R003 Sechzehntelpuls (4/4, 16 Einsätze, Periode 3840 Ticks); Positionen: 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600; Dauern: 84 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1+1Okt=A, 4=T, 1+1Okt=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,35 / 0,65 / 0,55); gültig X: 0,00–0,70 · Y: 0,30–1,00 · Z: 0,30–0,80; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-Q022 Zelle mit Einzeltonvariation

- **Charakter:** Achtton-Figur; nur die letzte Note weicht ab.
- **Tonfolge (8 Töne):** 0 +7 +3 +7 0 +7 +3 +8 → 1 5 ♭3 5 1 5 ♭3 ♭6
- **Intervalle:** Quinte↑, große Terz↓, große Terz↑, Quinte↓, Quinte↑, große Terz↓, Quarte↑
- **Rhythmus:** JC-R003 Sechzehntelpuls (4/4, 16 Einsätze, Periode 3840 Ticks); Positionen: 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600; Dauern: 84 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 5=A, ♭3=A, 5=A, 1=A, 5=A, ♭3=A, ♭6=T
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T002 Einzeltonvariation, JC-T003 Oktavverlagerung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,35 / 0,60 / 0,50); gültig X: 0,00–0,70 · Y: 0,30–0,90 · Z: 0,30–0,70; Z-Charakter psychologisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q023 Achsenpendel

- **Charakter:** Grundton–Quinte gegen wechselnde Oberklänge (H8); wird umgefärbt, nicht verändert.
- **Tonfolge (4 Töne):** 0 +7 0 +12 → 1 5 1 1+1Okt
- **Intervalle:** Quinte↑, Quinte↓, Oktave↑
- **Rhythmus:** JC-R014 Legato-Achtel (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 456 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 5=A, 1=A, 1+1Okt=A
- **Identität:** Erhalten: Tonhöhe(n). Variabel: Rhythmus, Gate, Akzente, Dichte.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Umfärbung, Atmung
- **XYZ:** Anker (0,50 / 0,50 / 0,30); gültig X: 0,00–1,00 · Y: 0,20–0,80 · Z: 0,10–0,50; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q024 Komplementär-Sequenz A

- **Charakter:** Auf den Zählzeiten; mit Komplementär-Sequenz B zu kombinieren.
- **Tonfolge (2 Töne):** 0 +12 → 1 1+1Okt
- **Intervalle:** Oktave↑
- **Rhythmus:** JC-R052 Komplement A: Schlag (4/4, 4 Einsätze, Periode 3840 Ticks); Positionen: 0, 960, 1920, 2880; Dauern: 216 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1+1Okt=A
- **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **Entwicklungsstrategien:** Stasis, Rotation, Atmung
- **XYZ:** Anker (0,50 / 0,60 / 0,40); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,20–0,60; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-Q025 Komplementär-Sequenz B

- **Charakter:** Auf den Offbeats; füllt Sequenz A.
- **Tonfolge (2 Töne):** +7 +3 → 5 ♭3
- **Intervalle:** große Terz↓
- **Rhythmus:** JC-R053 Komplement B: Offbeat (4/4, 4 Einsätze, Periode 3840 Ticks); Positionen: 480, 1440, 2400, 3360; Dauern: 216 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 5=A, ♭3=A
- **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **Entwicklungsstrategien:** Stasis, Rotation, Atmung
- **XYZ:** Anker (0,50 / 0,60 / 0,40); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,20–0,60; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-Q026 Endlosband

- **Charakter:** Für unveränderte Wiederholung über viele Minuten konstruiert.
- **Tonfolge (8 Töne):** 0 +12 +7 +12 0 +12 +7 +10 → 1 1+1Okt 5 1+1Okt 1 1+1Okt 5 ♭7
- **Intervalle:** Oktave↑, Quarte↓, Quarte↑, Oktave↓, Oktave↑, Quarte↓, kleine Terz↑
- **Rhythmus:** JC-R003 Sechzehntelpuls (4/4, 16 Einsätze, Periode 3840 Ticks); Positionen: 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600; Dauern: 84 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1+1Okt=A, 5=A, 1+1Okt=A, 1=A, 1+1Okt=A, 5=A, ♭7=T
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T012 Langfristige Stasis
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,50 / 0,60 / 0,40); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,20–0,60; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-Q027 Lange Sechzehntelreise

- **Charakter:** Sechzehn verschiedene Positionen in einem Takt; eher Linie als Zelle.
- **Tonfolge (16 Töne):** 0 +3 +7 +10 +12 +10 +7 +3 0 +3 +7 +12 +15 +12 +10 +7 → 1 ♭3 5 ♭7 1+1Okt ♭7 5 ♭3 1 ♭3 5 1+1Okt ♭3+1Okt 1+1Okt ♭7 5
- **Intervalle:** kleine Terz↑, große Terz↑, kleine Terz↑, große Sekunde↑, große Sekunde↓, kleine Terz↓, große Terz↓, kleine Terz↓, kleine Terz↑, große Terz↑, Quarte↑, kleine Terz↑, kleine Terz↓, große Sekunde↓, kleine Terz↓
- **Rhythmus:** JC-R003 Sechzehntelpuls (4/4, 16 Einsätze, Periode 3840 Ticks); Positionen: 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600; Dauern: 84 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, ♭3=A, 5=A, ♭7=T, 1+1Okt=A, ♭7=T, 5=A, ♭3=A, 1=A, ♭3=A, 5=A, 1+1Okt=A, ♭3+1Okt=A, 1+1Okt=A, ♭7=T, 5=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T005 Motivfragmentierung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,45 / 0,70 / 0,50); gültig X: 0,20–0,70 · Y: 0,40–1,00 · Z: 0,30–0,70; Z-Charakter mechanisch
- **Fähigkeiten:** lange Sequenz (> 8 Töne)
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q028 Fallende Triolenkette

- **Charakter:** Zwei Takte; der obere Ton sinkt stufenweise.
- **Tonfolge (24 Töne):** 0 +7 +12 0 +7 +12 0 +7 +10 0 +7 +10 0 +5 +8 0 +5 +8 0 +3 +7 0 +3 +7 → 1 5 1+1Okt 1 5 1+1Okt 1 5 ♭7 1 5 ♭7 1 4 ♭6 1 4 ♭6 1 ♭3 5 1 ♭3 5
- **Intervalle:** Quinte↑, Quarte↑, Oktave↓, Quinte↑, Quarte↑, Oktave↓, Quinte↑, kleine Terz↑, kleine Septime↓, Quinte↑, kleine Terz↑, kleine Septime↓, Quarte↑, kleine Terz↑, kleine Sexte↓, Quarte↑, kleine Terz↑, kleine Sexte↓, kleine Terz↑, große Terz↑, Quinte↓, kleine Terz↑, große Terz↑
- **Rhythmus:** JC-R032 Achteltriolen betont (4/4, 12 Einsätze, Periode 3840 Ticks); Positionen: 0, 320, 640, 960, 1280, 1600, 1920, 2240, 2560, 2880, 3200, 3520; Dauern: 122 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 5=A, 1+1Okt=A, 1=A, 5=A, 1+1Okt=A, 1=A, 5=A, ♭7=T, 1=A, 5=A, ♭7=T, 1=A, 4=T, ♭6=T, 1=A, 4=T, ♭6=T, 1=A, ♭3=A, 5=A, 1=A, ♭3=A, 5=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T005 Motivfragmentierung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,40 / 0,60 / 0,40); gültig X: 0,20–0,60 · Y: 0,30–0,90 · Z: 0,20–0,60; Z-Charakter neutral
- **Fähigkeiten:** lange Sequenz (> 8 Töne)
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q029 Chromatische Umspielung

- **Charakter:** Grundton, ♭2, None, ♭2; enge Chromatik.
- **Tonfolge (4 Töne):** 0 +1 +2 +1 → 1 ♭2 2 ♭2
- **Intervalle:** kleine Sekunde↑, kleine Sekunde↑, kleine Sekunde↓
- **Rhythmus:** JC-R003 Sechzehntelpuls (4/4, 16 Einsätze, Periode 3840 Ticks); Positionen: 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600; Dauern: 84 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, ♭2=U, 2=T, ♭2=U · autorisiert: ♭2→U
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,20 / 0,65 / 0,80); gültig X: 0,00–0,40 · Y: 0,30–1,00 · Z: 0,60–1,00; Z-Charakter psychologisch
- **Fähigkeiten:** Dissonanz-Autorisierung
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q030 Kriechende Chromatik oben

- **Charakter:** Halbtonabstieg von der Oktave; ohne Ziel wiederholt.
- **Tonfolge (4 Töne):** +12 +11 +10 +9 → 1+1Okt 7 ♭7 6
- **Intervalle:** kleine Sekunde↓, kleine Sekunde↓, kleine Sekunde↓
- **Rhythmus:** JC-R013 Staccato-Achtel (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 106 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1+1Okt=A, 7=U, ♭7=T, 6=U · autorisiert: 7→U, 6→U
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,25 / 0,50 / 0,80); gültig X: 0,00–0,50 · Y: 0,20–0,80 · Z: 0,60–1,00; Z-Charakter psychologisch
- **Fähigkeiten:** Dissonanz-Autorisierung
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Tonfolge E

#### JC-Q031 Tritonus-Wippe

- **Charakter:** Grundton–Tritonus. Kernintervall nicht belegt; markierte Ableitung.
- **Tonfolge (2 Töne):** 0 +6 → 1 ♯4/♭5
- **Intervalle:** Tritonus↑
- **Rhythmus:** JC-R013 Staccato-Achtel (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 106 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, ♯4/♭5=U · autorisiert: ♯4/♭5→U
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,15 / 0,60 / 0,85); gültig X: 0,00–0,30 · Y: 0,30–0,90 · Z: 0,70–1,00; Z-Charakter psychologisch
- **Fähigkeiten:** Dissonanz-Autorisierung
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Tonfolge E

#### JC-Q032 Quart-Quint-Leiter

- **Charakter:** Grundton, Quarte, Quinte, Oktave; offen, ohne Terz.
- **Tonfolge (4 Töne):** 0 +5 +7 +12 → 1 4 5 1+1Okt
- **Intervalle:** Quarte↑, große Sekunde↑, Quarte↑
- **Rhythmus:** JC-R003 Sechzehntelpuls (4/4, 16 Einsätze, Periode 3840 Ticks); Positionen: 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600; Dauern: 84 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 4=T, 5=A, 1+1Okt=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,50 / 0,65 / 0,40); gültig X: 0,00–1,00 · Y: 0,30–1,00 · Z: 0,20–0,60; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q033 Hohe Glockenfigur

- **Charakter:** Hohe Quint-Oktav-Figur in Triolen; Glocken-Charakter der Fog-Familie.
- **Tonfolge (4 Töne):** +12 +19 +24 +19 → 1+1Okt 5+1Okt 1+2Okt 5+1Okt
- **Intervalle:** Quinte↑, Quarte↑, Quarte↓
- **Rhythmus:** JC-R016 Triolen-Repetition (4/4, 12 Einsätze, Periode 3840 Ticks); Positionen: 0, 320, 640, 960, 1280, 1600, 1920, 2240, 2560, 2880, 3200, 3520; Dauern: 128 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1+1Okt=A, 5+1Okt=A, 1+2Okt=A, 5+1Okt=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T006 Rollenwanderung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,80 / 0,30 / 0,30); gültig X: 0,60–1,00 · Y: 0,00–0,60 · Z: 0,10–0,50; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-Q034 Lydisches Glas

- **Charakter:** Dur mit großer Septime und ♯4; kalt hell, modale Ableitung.
- **Tonfolge (4 Töne):** 0 +7 +11 +18 → 1 5 7 ♯4/♭5+1Okt
- **Intervalle:** Quinte↑, große Terz↑, Quinte↑
- **Rhythmus:** JC-R032 Achteltriolen betont (4/4, 12 Einsätze, Periode 3840 Ticks); Positionen: 0, 320, 640, 960, 1280, 1600, 1920, 2240, 2560, 2880, 3200, 3520; Dauern: 122 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Durdreiklang auf 1, Tonvorrat Lydisch
- **Tonfunktionen:** 1=A, 5=A, 7=T, ♯4/♭5+1Okt=T
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,85 / 0,30 / 0,30); gültig X: 0,70–1,00 · Y: 0,00–0,60 · Z: 0,10–0,50; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Tonfolge E

#### JC-Q035 Phrygische Zelle

- **Charakter:** Grundton und ♭2 umrahmen die Quinte; modal dunkel.
- **Tonfolge (4 Töne):** 0 +1 +7 +1 → 1 ♭2 5 ♭2
- **Intervalle:** kleine Sekunde↑, Tritonus↑, Tritonus↓
- **Rhythmus:** JC-R013 Staccato-Achtel (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 106 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Phrygisch
- **Tonfunktionen:** 1=A, ♭2=T, 5=A, ♭2=T
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,20 / 0,50 / 0,60); gültig X: 0,00–0,40 · Y: 0,20–0,80 · Z: 0,40–0,80; Z-Charakter psychologisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Tonfolge E

#### JC-Q036 Dorische Helle

- **Charakter:** Die große Sexte hellt den Moll auf.
- **Tonfolge (4 Töne):** 0 +9 +7 +3 → 1 6 5 ♭3
- **Intervalle:** große Sexte↑, große Sekunde↓, große Terz↓
- **Rhythmus:** JC-R014 Legato-Achtel (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 456 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Dorisch
- **Tonfunktionen:** 1=A, 6=T, 5=A, ♭3=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,70 / 0,35 / 0,30); gültig X: 0,50–0,90 · Y: 0,10–0,60 · Z: 0,10–0,50; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Tonfolge E

#### JC-Q037 Leitton unter der Quinte

- **Charakter:** Quinte–Grundton–Quinte–Leitton; Spannung von unten.
- **Tonfolge (4 Töne):** +7 0 +7 -1 → 5 1 5 7-1Okt
- **Intervalle:** Quinte↓, Quinte↑, kleine Sexte↓
- **Rhythmus:** JC-R002 Achtelpuls (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 216 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Harmonisch Moll
- **Tonfunktionen:** 5=A, 1=A, 5=A, 7-1Okt=T
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T002 Einzeltonvariation, JC-T003 Oktavverlagerung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,40 / 0,60 / 0,60); gültig X: 0,20–0,60 · Y: 0,30–0,90 · Z: 0,40–0,80; Z-Charakter psychologisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q038 Kleinterz-Riff

- **Charakter:** Bluesig geprägte Achtelfigur um den Grundton.
- **Tonfolge (8 Töne):** 0 0 +3 0 +5 0 +3 0 → 1 1 ♭3 1 4 1 ♭3 1
- **Intervalle:** Prime, kleine Terz↑, kleine Terz↓, Quarte↑, Quarte↓, kleine Terz↑, kleine Terz↓
- **Rhythmus:** JC-R002 Achtelpuls (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 216 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1=A, ♭3=A, 1=A, 4=T, 1=A, ♭3=A, 1=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T010 Akzentgruppen-Variation
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,30 / 0,75 / 0,40); gültig X: 0,10–0,50 · Y: 0,50–1,00 · Z: 0,20–0,60; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-Q039 Herzschlag-Quinte

- **Charakter:** Herzschlag-Paar auf Grundton und Quinte.
- **Tonfolge (2 Töne):** 0 +7 → 1 5
- **Intervalle:** Quinte↑
- **Rhythmus:** JC-R008 Herzschlag (4/4, 2 Einsätze, Periode 3840 Ticks); Positionen: 0, 720; Dauern: 72 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 5=A
- **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T011 Unterbrechung und Wiederaufnahme
- **Entwicklungsstrategien:** Stasis, Rotation, Atmung
- **XYZ:** Anker (0,50 / 0,45 / 0,45); gültig X: 0,00–1,00 · Y: 0,10–0,80 · Z: 0,20–0,70; Z-Charakter psychologisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q040 Triolen gegen Viertel

- **Charakter:** Drei Töne auf Viertel-Triolen; der Takt verschwimmt.
- **Tonfolge (3 Töne):** 0 +7 +3 → 1 5 ♭3
- **Intervalle:** Quinte↑, große Terz↓
- **Rhythmus:** JC-R017 Viertel-Triolen (4/4, 6 Einsätze, Periode 3840 Ticks); Positionen: 0, 640, 1280, 1920, 2560, 3200; Dauern: 384 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 5=A, ♭3=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,35 / 0,40 / 0,50); gültig X: 0,00–0,70 · Y: 0,10–0,70 · Z: 0,30–0,70; Z-Charakter psychologisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-Q041 Sequenz mit Atemloch

- **Charakter:** Läuft drei Takte, setzt einen Takt aus, kehrt identisch zurück.
- **Tonfolge (4 Töne):** 0 +7 +12 +7 → 1 5 1+1Okt 5
- **Intervalle:** Quinte↑, Quarte↑, Quarte↓
- **Rhythmus:** JC-R041 Drei Takte an, einer aus (4/4, 24 Einsätze, Periode 15360 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360, 3840, 4320, 4800, 5280, 5760, 6240, 6720, 7200, 7680, 8160, 8640, 9120, 9600, 10080, 10560, 11040; Dauern: 216 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 5=A, 1+1Okt=A, 5=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T011 Unterbrechung und Wiederaufnahme
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,50 / 0,60 / 0,40); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,20–0,60; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-Q042 Zelle mit wandernder Lücke

- **Charakter:** Pro Takt fehlt ein anderer Ton; die Tonfolge bleibt.
- **Tonfolge (4 Töne):** 0 +3 +7 +3 → 1 ♭3 5 ♭3
- **Intervalle:** kleine Terz↑, große Terz↑, große Terz↓
- **Rhythmus:** JC-R060 Rotierende Lücke (4/4, 28 Einsätze, Periode 15360 Ticks); Positionen: 480, 960, 1440, 1920, 2400, 2880, 3360, 3840, 4320, 5280, 5760, 6240, 6720, 7200, 7680, 8160, 8640, 9120, 10080, 10560, 11040, 11520, 12000, 12480, 12960, 13440, 13920, 14880; Dauern: 202 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, ♭3=A, 5=A, ♭3=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T010 Akzentgruppen-Variation, JC-T011 Unterbrechung und Wiederaufnahme
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,40 / 0,60 / 0,60); gültig X: 0,00–0,80 · Y: 0,30–0,90 · Z: 0,40–0,80; Z-Charakter psychologisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Tonfolge E

#### JC-Q043 Phasenzelle 5 gegen 16

- **Charakter:** Fünftoniger Zyklus im Sechzehntelpuls; verschiebt sich gegen den Takt. Gemeinsame SYNTH-Fähigkeit, bei Carpenter nicht belegt.
- **Tonfolge (5 Töne):** 0 +7 +12 +7 +3 → 1 5 1+1Okt 5 ♭3
- **Intervalle:** Quinte↑, Quarte↑, Quarte↓, große Terz↓
- **Rhythmus:** JC-R003 Sechzehntelpuls (4/4, 16 Einsätze, Periode 3840 Ticks); Positionen: 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600; Dauern: 84 Ticks
- **Zyklus:** **unabhängiger Tonhöhenzyklus** (5 gegen 16) – gemeinsame SYNTH-Fähigkeit
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 5=A, 1+1Okt=A, 5=A, ♭3=A
- **Identität:** Erhalten: Tonhöhenzyklus und Raster; die Verschiebung gegen den Takt gehört zur Identität.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T015 Phasenversatz
- **Entwicklungsstrategien:** Stasis (Phasenverschiebung erzeugt Bewegung von selbst)
- **XYZ:** Anker (0,40 / 0,70 / 0,80); gültig X: 0,00–0,80 · Y: 0,40–1,00 · Z: 0,60–1,00; Z-Charakter mechanisch
- **Fähigkeiten:** unabhängiger Tonhöhenzyklus
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Tonfolge E

#### JC-Q044 Dreierschleife

- **Charakter:** Drei Töne auf acht Achtel; kehrt erst nach drei Takten zum Start zurück.
- **Tonfolge (3 Töne):** 0 +12 +7 → 1 1+1Okt 5
- **Intervalle:** Oktave↑, Quarte↓
- **Rhythmus:** JC-R002 Achtelpuls (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 216 Ticks
- **Zyklus:** **unabhängiger Tonhöhenzyklus** (3 gegen 8) – gemeinsame SYNTH-Fähigkeit
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1+1Okt=A, 5=A
- **Identität:** Erhalten: Tonhöhenzyklus und Raster; die Verschiebung gegen den Takt gehört zur Identität.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T015 Phasenversatz
- **Entwicklungsstrategien:** Stasis (Phasenverschiebung erzeugt Bewegung von selbst)
- **XYZ:** Anker (0,40 / 0,60 / 0,70); gültig X: 0,00–0,80 · Y: 0,30–0,90 · Z: 0,50–0,90; Z-Charakter mechanisch
- **Fähigkeiten:** unabhängiger Tonhöhenzyklus
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Tonfolge E

#### JC-Q045 Siebener-Kette

- **Charakter:** Siebentonfigur im 7/8.
- **Tonfolge (7 Töne):** 0 +7 +12 +7 0 +5 +3 → 1 5 1+1Okt 5 1 4 ♭3
- **Intervalle:** Quinte↑, Quarte↑, Quarte↓, Quinte↓, Quarte↑, große Sekunde↓
- **Rhythmus:** JC-R026 7/8 als 2+2+3 (7/8, 7 Einsätze, Periode 3360 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880; Dauern: 192 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 5=A, 1+1Okt=A, 5=A, 1=A, 4=T, ♭3=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T010 Akzentgruppen-Variation
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,35 / 0,60 / 0,60); gültig X: 0,00–0,70 · Y: 0,30–0,90 · Z: 0,40–0,80; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Tonfolge E

#### JC-Q046 Neuner-Bogen

- **Charakter:** Neuntonfigur im 9/8 mit ♭6 im Schlussglied.
- **Tonfolge (9 Töne):** 0 +3 +7 +3 0 +3 +7 +8 +7 → 1 ♭3 5 ♭3 1 ♭3 5 ♭6 5
- **Intervalle:** kleine Terz↑, große Terz↑, große Terz↓, kleine Terz↓, kleine Terz↑, große Terz↑, kleine Sekunde↑, kleine Sekunde↓
- **Rhythmus:** JC-R030 9/8 als 2+2+2+3 (9/8, 9 Einsätze, Periode 4320 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360, 3840; Dauern: 202 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, ♭3=A, 5=A, ♭3=A, 1=A, ♭3=A, 5=A, ♭6=T, 5=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T010 Akzentgruppen-Variation
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,30 / 0,60 / 0,60); gültig X: 0,00–0,60 · Y: 0,30–0,90 · Z: 0,40–0,80; Z-Charakter psychologisch
- **Fähigkeiten:** lange Sequenz (> 8 Töne)
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Tonfolge E

#### JC-Q047 Stolper-Oktave

- **Charakter:** Oktav-Wiege im Stolper-Rhythmus.
- **Tonfolge (8 Töne):** 0 +12 0 +12 0 +12 +7 +12 → 1 1+1Okt 1 1+1Okt 1 1+1Okt 5 1+1Okt
- **Intervalle:** Oktave↑, Oktave↓, Oktave↑, Oktave↓, Oktave↑, Quarte↓, Quarte↑
- **Rhythmus:** JC-R058 Stolper-Achtel (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 2160, 2400, 2880, 3360; Dauern: 84 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1+1Okt=A, 1=A, 1+1Okt=A, 1=A, 1+1Okt=A, 5=A, 1+1Okt=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T010 Akzentgruppen-Variation
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,35 / 0,60 / 0,70); gültig X: 0,00–0,70 · Y: 0,30–0,90 · Z: 0,50–0,90; Z-Charakter psychologisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-Q048 Galopp-Quinte

- **Charakter:** Grundton lang, Quinte doppelt kurz; Verfolgung.
- **Tonfolge (3 Töne):** 0 +7 +7 → 1 5 5
- **Intervalle:** Quinte↑, Prime
- **Rhythmus:** JC-R015 Galopp (4/4, 12 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 720, 960, 1440, 1680, 1920, 2400, 2640, 2880, 3360, 3600; Dauern: 96 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 5=A, 5=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,35 / 0,75 / 0,70); gültig X: 0,00–0,70 · Y: 0,50–1,00 · Z: 0,50–0,90; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q049 Hohe Klingel-Arpeggien

- **Charakter:** Hohe Mollarpeggien in Triolen; das Fog-Verfahren als eigene Figur.
- **Tonfolge (6 Töne):** +12 +15 +19 +24 +19 +15 → 1+1Okt ♭3+1Okt 5+1Okt 1+2Okt 5+1Okt ♭3+1Okt
- **Intervalle:** kleine Terz↑, große Terz↑, Quarte↑, Quarte↓, große Terz↓
- **Rhythmus:** JC-R032 Achteltriolen betont (4/4, 12 Einsätze, Periode 3840 Ticks); Positionen: 0, 320, 640, 960, 1280, 1600, 1920, 2240, 2560, 2880, 3200, 3520; Dauern: 122 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1+1Okt=A, ♭3+1Okt=A, 5+1Okt=A, 1+2Okt=A, 5+1Okt=A, ♭3+1Okt=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,75 / 0,40 / 0,40); gültig X: 0,50–1,00 · Y: 0,10–0,70 · Z: 0,20–0,60; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-Q050 Melancholische Abwärtslinie

- **Charakter:** Gebundene, fallende Linie mit Rückschwung.
- **Tonfolge (8 Töne):** +15 +14 +12 +10 +12 +10 +8 +7 → ♭3+1Okt 2+1Okt 1+1Okt ♭7 1+1Okt ♭7 ♭6 5
- **Intervalle:** kleine Sekunde↓, große Sekunde↓, große Sekunde↓, große Sekunde↑, große Sekunde↓, große Sekunde↓, kleine Sekunde↓
- **Rhythmus:** JC-R014 Legato-Achtel (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 456 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** ♭3+1Okt=A, 2+1Okt=T, 1+1Okt=A, ♭7=T, 1+1Okt=A, ♭7=T, ♭6=T, 5=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,50 / 0,30 / 0,20); gültig X: 0,30–0,70 · Y: 0,00–0,60 · Z: 0,00–0,40; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q051 Kleinsext-Wiege

- **Charakter:** Grundton und ♭6; dunkel, schwer.
- **Tonfolge (2 Töne):** 0 +8 → 1 ♭6
- **Intervalle:** kleine Sexte↑
- **Rhythmus:** JC-R002 Achtelpuls (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 216 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, ♭6=T
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,25 / 0,50 / 0,50); gültig X: 0,00–0,50 · Y: 0,20–0,80 · Z: 0,30–0,70; Z-Charakter psychologisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q052 Oktavleiter

- **Charakter:** Über zwei Oktaven gespannt; nur Grundton.
- **Tonfolge (4 Töne):** 0 +12 +24 +12 → 1 1+1Okt 1+2Okt 1+1Okt
- **Intervalle:** Oktave↑, Oktave↑, Oktave↓
- **Rhythmus:** JC-R003 Sechzehntelpuls (4/4, 16 Einsätze, Periode 3840 Ticks); Positionen: 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600; Dauern: 84 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1+1Okt=A, 1+2Okt=A, 1+1Okt=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,50 / 0,70 / 0,50); gültig X: 0,00–1,00 · Y: 0,40–1,00 · Z: 0,30–0,70; Z-Charakter mechanisch
- **Fähigkeiten:** exaktes Register (Umfang > 1,5 Oktaven)
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q053 Nadelstich-Repetition

- **Charakter:** Ein sehr hoher Ton, extrem kurz wiederholt.
- **Tonfolge (1 Töne):** +24 → 1+2Okt
- **Rhythmus:** JC-R037 Staccatissimo-Achtel (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 58 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1+2Okt=A
- **Identität:** Erhalten: Tonhöhe(n). Variabel: Rhythmus, Gate, Akzente, Dichte.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung, JC-T011 Unterbrechung und Wiederaufnahme
- **Entwicklungsstrategien:** Stasis, Umfärbung, Atmung
- **XYZ:** Anker (0,70 / 0,30 / 0,75); gültig X: 0,40–1,00 · Y: 0,00–0,60 · Z: 0,50–1,00; Z-Charakter psychologisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q054 Langsame Halbe-Zelle

- **Charakter:** Vier Töne in Halben; Zelle ohne Hast.
- **Tonfolge (4 Töne):** 0 +7 +8 +7 → 1 5 ♭6 5
- **Intervalle:** Quinte↑, kleine Sekunde↑, kleine Sekunde↓
- **Rhythmus:** JC-R006 Halbe-Puls (4/4, 2 Einsätze, Periode 3840 Ticks); Positionen: 0, 1920; Dauern: 1632 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 5=A, ♭6=T, 5=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,30 / 0,30 / 0,40); gültig X: 0,00–0,60 · Y: 0,00–0,60 · Z: 0,20–0,60; Z-Charakter psychologisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q055 Langsame Abstiegsglocke

- **Charakter:** Ein Ton pro Takt, stufenweise fallend.
- **Tonfolge (4 Töne):** 0 -2 -4 -5 → 1 ♭7-1Okt ♭6-1Okt 5-1Okt
- **Intervalle:** große Sekunde↓, große Sekunde↓, kleine Sekunde↓
- **Rhythmus:** JC-R019 Ganze Noten (4/4, 1 Einsätze, Periode 3840 Ticks); Positionen: 0; Dauern: 3763 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, ♭7-1Okt=T, ♭6-1Okt=T, 5-1Okt=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T006 Rollenwanderung, JC-T008 Harmonische Umfärbung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,55 / 0,25 / 0,20); gültig X: 0,30–0,80 · Y: 0,00–0,50 · Z: 0,00–0,40; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q056 Uhrwerk mit Fehlschlag

- **Charakter:** Tick-tack, jeder achte Schlag landet auf dem Tritonus.
- **Tonfolge (8 Töne):** +12 +7 +12 +7 +12 +7 +12 +6 → 1+1Okt 5 1+1Okt 5 1+1Okt 5 1+1Okt ♯4/♭5
- **Intervalle:** Quarte↓, Quarte↑, Quarte↓, Quarte↑, Quarte↓, Quarte↑, Tritonus↓
- **Rhythmus:** JC-R061 Uhrwerk tick-tack (4/4, 16 Einsätze, Periode 3840 Ticks); Positionen: 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600; Dauern: 48 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1+1Okt=A, 5=A, 1+1Okt=A, 5=A, 1+1Okt=A, 5=A, 1+1Okt=A, ♯4/♭5=U · autorisiert: ♯4/♭5→U
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T002 Einzeltonvariation, JC-T003 Oktavverlagerung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,25 / 0,50 / 0,80); gültig X: 0,00–0,50 · Y: 0,20–0,80 · Z: 0,60–1,00; Z-Charakter psychologisch
- **Fähigkeiten:** Dissonanz-Autorisierung
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Tonfolge E

#### JC-Q057 Asymmetrische Achtelzelle

- **Charakter:** Dreiergruppen mit Zweier-Schluss bei durchlaufenden Achteln.
- **Tonfolge (8 Töne):** 0 +7 +12 0 +7 +12 0 +10 → 1 5 1+1Okt 1 5 1+1Okt 1 ♭7
- **Intervalle:** Quinte↑, Quarte↑, Oktave↓, Quinte↑, Quarte↑, Oktave↓, kleine Septime↑
- **Rhythmus:** JC-R029 4/4 als 3+3+2 Achtel (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 202 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 5=A, 1+1Okt=A, 1=A, 5=A, 1+1Okt=A, 1=A, ♭7=T
- **Identität:** Erhalten: Akzentgruppierung und Kontur. Variabel: Transposition, Gate, Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T010 Akzentgruppen-Variation
- **Entwicklungsstrategien:** Stasis, Blockverschiebung
- **XYZ:** Anker (0,35 / 0,60 / 0,50); gültig X: 0,00–0,70 · Y: 0,30–0,90 · Z: 0,30–0,70; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q058 Kreuz-Sequenz A

- **Charakter:** Partner zu Kreuz-Sequenz B.
- **Tonfolge (4 Töne):** 0 +12 +7 +12 → 1 1+1Okt 5 1+1Okt
- **Intervalle:** Oktave↑, Quarte↓, Quarte↑
- **Rhythmus:** JC-R055 Kreuz A (4/4, 4 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 1200, 1680; Dauern: 84 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1+1Okt=A, 5=A, 1+1Okt=A
- **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **Entwicklungsstrategien:** Stasis, Rotation, Atmung
- **XYZ:** Anker (0,40 / 0,70 / 0,60); gültig X: 0,00–0,80 · Y: 0,40–1,00 · Z: 0,40–0,80; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q059 Kreuz-Sequenz B

- **Charakter:** Partner zu Kreuz-Sequenz A.
- **Tonfolge (4 Töne):** +3 +10 +3 +7 → ♭3 ♭7 ♭3 5
- **Intervalle:** Quinte↑, Quinte↓, große Terz↑
- **Rhythmus:** JC-R056 Kreuz B (4/4, 4 Einsätze, Periode 3840 Ticks); Positionen: 240, 720, 960, 1440; Dauern: 84 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** ♭3=A, ♭7=T, ♭3=A, 5=A
- **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **Entwicklungsstrategien:** Stasis, Rotation, Atmung
- **XYZ:** Anker (0,40 / 0,70 / 0,60); gültig X: 0,00–0,80 · Y: 0,40–1,00 · Z: 0,40–0,80; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q060 Terz-Quint-Achse

- **Charakter:** Für Umfärbung über H8-Achsen gedacht.
- **Tonfolge (4 Töne):** +3 +7 +12 +7 → ♭3 5 1+1Okt 5
- **Intervalle:** große Terz↑, Quarte↑, Quarte↓
- **Rhythmus:** JC-R002 Achtelpuls (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 216 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** ♭3=A, 5=A, 1+1Okt=A, 5=A
- **Identität:** Erhalten: Tonhöhe(n). Variabel: Rhythmus, Gate, Akzente, Dichte.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **Entwicklungsstrategien:** Stasis, Umfärbung, Atmung
- **XYZ:** Anker (0,55 / 0,45 / 0,30); gültig X: 0,30–0,80 · Y: 0,20–0,70 · Z: 0,10–0,50; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q061 Halbton-Umspielung

- **Charakter:** Grundton von oben und unten im Halbton umkreist.
- **Tonfolge (4 Töne):** 0 +1 0 +11 → 1 ♭2 1 7
- **Intervalle:** kleine Sekunde↑, kleine Sekunde↓, große Septime↑
- **Rhythmus:** JC-R003 Sechzehntelpuls (4/4, 16 Einsätze, Periode 3840 Ticks); Positionen: 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600; Dauern: 84 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, ♭2=U, 1=A, 7=U · autorisiert: ♭2→U, 7→U
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,20 / 0,70 / 0,80); gültig X: 0,00–0,40 · Y: 0,40–1,00 · Z: 0,60–1,00; Z-Charakter psychologisch
- **Fähigkeiten:** Dissonanz-Autorisierung
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q062 Septimen-Wippe

- **Charakter:** Grundton, ♭7, Terz, ♭7; rockig, kurz.
- **Tonfolge (4 Töne):** 0 +10 +3 +10 → 1 ♭7 ♭3 ♭7
- **Intervalle:** kleine Septime↑, Quinte↓, Quinte↑
- **Rhythmus:** JC-R013 Staccato-Achtel (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 106 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, ♭7=T, ♭3=A, ♭7=T
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,40 / 0,55 / 0,40); gültig X: 0,20–0,60 · Y: 0,30–0,80 · Z: 0,20–0,60; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q063 Zweitakt-Wanderung

- **Charakter:** Zwei Takte Sechzehntel; der zweite Takt beugt die Figur über ♭6 und None.
- **Tonfolge (32 Töne):** 0 +3 +7 +12 +7 +3 0 +3 0 +3 +7 +12 +7 +3 0 +3 0 +3 +8 +12 +8 +3 0 +3 0 +2 +7 +10 +7 +2 0 +2 → 1 ♭3 5 1+1Okt 5 ♭3 1 ♭3 1 ♭3 5 1+1Okt 5 ♭3 1 ♭3 1 ♭3 ♭6 1+1Okt ♭6 ♭3 1 ♭3 1 2 5 ♭7 5 2 1 2
- **Intervalle:** kleine Terz↑, große Terz↑, Quarte↑, Quarte↓, große Terz↓, kleine Terz↓, kleine Terz↑, kleine Terz↓, kleine Terz↑, große Terz↑, Quarte↑, Quarte↓, große Terz↓, kleine Terz↓, kleine Terz↑, kleine Terz↓, kleine Terz↑, Quarte↑, große Terz↑, große Terz↓, Quarte↓, kleine Terz↓, kleine Terz↑, kleine Terz↓, große Sekunde↑, Quarte↑, kleine Terz↑, kleine Terz↓, Quarte↓, große Sekunde↓, große Sekunde↑
- **Rhythmus:** JC-R003 Sechzehntelpuls (4/4, 16 Einsätze, Periode 3840 Ticks); Positionen: 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600; Dauern: 84 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, ♭3=A, 5=A, 1+1Okt=A, 5=A, ♭3=A, 1=A, ♭3=A, 1=A, ♭3=A, 5=A, 1+1Okt=A, 5=A, ♭3=A, 1=A, ♭3=A, 1=A, ♭3=A, ♭6=T, 1+1Okt=A, ♭6=T, ♭3=A, 1=A, ♭3=A, 1=A, 2=T, 5=A, ♭7=T, 5=A, 2=T, 1=A, 2=T
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,45 / 0,70 / 0,50); gültig X: 0,20–0,70 · Y: 0,40–1,00 · Z: 0,30–0,70; Z-Charakter mechanisch
- **Fähigkeiten:** lange Sequenz (> 8 Töne)
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q064 Sextklage

- **Charakter:** Quinte und ♭6 im Wechsel, einmal zur ♭7 ausgreifend.
- **Tonfolge (8 Töne):** +7 +8 +7 +8 +7 +8 +10 +8 → 5 ♭6 5 ♭6 5 ♭6 ♭7 ♭6
- **Intervalle:** kleine Sekunde↑, kleine Sekunde↓, kleine Sekunde↑, kleine Sekunde↓, kleine Sekunde↑, große Sekunde↑, große Sekunde↓
- **Rhythmus:** JC-R013 Staccato-Achtel (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 106 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 5=A, ♭6=T, 5=A, ♭6=T, 5=A, ♭6=T, ♭7=T, ♭6=T
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T002 Einzeltonvariation, JC-T003 Oktavverlagerung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,25 / 0,50 / 0,60); gültig X: 0,00–0,50 · Y: 0,20–0,80 · Z: 0,40–0,80; Z-Charakter psychologisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-Q065 Triolenpaar

- **Charakter:** Herzschlag in Triolen auf Grundton und Quinte.
- **Tonfolge (2 Töne):** 0 +7 → 1 5
- **Intervalle:** Quinte↑
- **Rhythmus:** JC-R035 Triolen-Herzschlag (4/4, 2 Einsätze, Periode 3840 Ticks); Positionen: 0, 640; Dauern: 128 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 5=A
- **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T011 Unterbrechung und Wiederaufnahme
- **Entwicklungsstrategien:** Stasis, Rotation, Atmung
- **XYZ:** Anker (0,50 / 0,40 / 0,50); gültig X: 0,00–1,00 · Y: 0,10–0,70 · Z: 0,30–0,70; Z-Charakter psychologisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Tonfolge E

#### JC-Q066 Ganzton-Glocke

- **Charakter:** Hohe None und Oktave; hell, kalt kreisend.
- **Tonfolge (4 Töne):** +14 +12 +14 +19 → 2+1Okt 1+1Okt 2+1Okt 5+1Okt
- **Intervalle:** große Sekunde↓, große Sekunde↑, Quarte↑
- **Rhythmus:** JC-R016 Triolen-Repetition (4/4, 12 Einsätze, Periode 3840 Ticks); Positionen: 0, 320, 640, 960, 1280, 1600, 1920, 2240, 2560, 2880, 3200, 3520; Dauern: 128 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 2+1Okt=T, 1+1Okt=A, 2+1Okt=T, 5+1Okt=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T006 Rollenwanderung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,75 / 0,30 / 0,40); gültig X: 0,50–1,00 · Y: 0,00–0,60 · Z: 0,20–0,60; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Tonfolge E

#### JC-Q067 Oktav-Synkope

- **Charakter:** Tresillo mit Oktavsprung auf der Vier-und.
- **Tonfolge (3 Töne):** 0 +12 +12 → 1 1+1Okt 1+1Okt
- **Intervalle:** Oktave↑, Prime
- **Rhythmus:** JC-R020 Tresillo (4/4, 3 Einsätze, Periode 3840 Ticks); Positionen: 0, 1440, 2880; Dauern: 192 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1+1Okt=A, 1+1Okt=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T010 Akzentgruppen-Variation
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,40 / 0,60 / 0,50); gültig X: 0,00–0,80 · Y: 0,30–0,90 · Z: 0,30–0,70; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

**Komplementäre Paare:** JC-Q024 + JC-Q025 (Schlag/Offbeat), JC-Q058 + JC-Q059 (Kreuz A/B). Kombinationen gleicher Identität in derselben Lage sind ungeeignet (Verschmelzung).

## 6. B – Bassführung

Drei Bindungen werden streng unterschieden: **akkordgebunden**, **eigenständig**, **Dissonanzpedal** (ausdrücklich autorisiert). Rhythmus 0 = durchgehend gehalten; −N = alle N Takte neu angeschlagen.

#### JC-B001 Tiefer Grundton-Drone

- **Charakter:** Ein tiefer Ton über die gesamte Dauer; Howarths „hold note“ als Verfahren.
- **Typ / Bindung:** Drone / **eigenständig**
- **Tonfolge:** 1 (durchgehend gehalten)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A
- **Identität:** Erhalten: Tonhöhe(n). Variabel: Rhythmus, Gate, Akzente, Dichte.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T012 Langfristige Stasis
- **Entwicklungsstrategien:** Stasis, Umfärbung, Atmung
- **XYZ:** Anker (0,50 / 0,50 / 0,50); gültig X: 0,00–1,00 · Y: 0,00–1,00 · Z: 0,00–1,00; Z-Charakter neutral
- **Fähigkeiten:** Halteton über beliebig viele Takte
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-B002 Quint-Drone

- **Charakter:** Die Quinte im Bass; schwebender als der Grundton.
- **Typ / Bindung:** Drone / **eigenständig**
- **Tonfolge:** 5 (durchgehend gehalten)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 5=A
- **Identität:** Erhalten: Tonhöhe(n). Variabel: Rhythmus, Gate, Akzente, Dichte.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T012 Langfristige Stasis
- **Entwicklungsstrategien:** Stasis, Umfärbung, Atmung
- **XYZ:** Anker (0,50 / 0,30 / 0,30); gültig X: 0,20–0,80 · Y: 0,00–0,60 · Z: 0,10–0,50; Z-Charakter neutral
- **Fähigkeiten:** Halteton über beliebig viele Takte
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-B003 Drone mit Neuanschlag

- **Charakter:** Der Drone wird alle vier Takte neu angeschlagen; gibt Halt ohne Puls.
- **Typ / Bindung:** Drone / **eigenständig**
- **Tonfolge:** 1 (alle 4 Takte neu angeschlagen)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A
- **Identität:** Erhalten: Tonhöhe(n). Variabel: Rhythmus, Gate, Akzente, Dichte.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung, JC-T012 Langfristige Stasis
- **Entwicklungsstrategien:** Stasis, Umfärbung, Atmung
- **XYZ:** Anker (0,50 / 0,30 / 0,20); gültig X: 0,00–1,00 · Y: 0,00–0,60 · Z: 0,00–0,40; Z-Charakter neutral
- **Fähigkeiten:** Halteton über beliebig viele Takte
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-B004 Atmender Drone

- **Charakter:** Neuanschlag alle zwei Takte; zusammen mit Velocity-Atmung (T16).
- **Typ / Bindung:** Drone / **eigenständig**
- **Tonfolge:** 1 (alle 2 Takte neu angeschlagen)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A
- **Identität:** Erhalten: Tonhöhe(n). Variabel: Rhythmus, Gate, Akzente, Dichte.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T012 Langfristige Stasis, JC-T016 Velocity-Atmung
- **Entwicklungsstrategien:** Stasis, Umfärbung, Atmung
- **XYZ:** Anker (0,50 / 0,25 / 0,20); gültig X: 0,00–1,00 · Y: 0,00–0,50 · Z: 0,00–0,40; Z-Charakter neutral
- **Fähigkeiten:** Halteton über beliebig viele Takte
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Tonfolge E

#### JC-B005 Unabhängiges Pedal

- **Charakter:** Hält den Grundton auch unter fremden Klängen; Reibungen sind ausdrücklich autorisiert.
- **Typ / Bindung:** Pedal / **Dissonanzpedal**
- **Tonfolge:** 1 (durchgehend gehalten)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A
- **Identität:** Erhalten: Tonhöhe(n). Variabel: Rhythmus, Gate, Akzente, Dichte.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T012 Langfristige Stasis
- **Entwicklungsstrategien:** Stasis, Umfärbung, Atmung
- **XYZ:** Anker (0,50 / 0,45 / 0,50); gültig X: 0,00–1,00 · Y: 0,00–0,90 · Z: 0,00–1,00; Z-Charakter neutral
- **Fähigkeiten:** Halteton über beliebig viele Takte
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-B006 Fremdpedal ♭2

- **Charakter:** Pedal einen Halbton über dem Grundton; unheimliche Basis.
- **Typ / Bindung:** Pedal / **Dissonanzpedal**
- **Tonfolge:** ♭2 (durchgehend gehalten)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** ♭2=U · autorisiert: ♭2→U
- **Identität:** Erhalten: Tonhöhe(n). Variabel: Rhythmus, Gate, Akzente, Dichte.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T012 Langfristige Stasis
- **Entwicklungsstrategien:** Stasis, Umfärbung, Atmung
- **XYZ:** Anker (0,20 / 0,40 / 0,80); gültig X: 0,00–0,40 · Y: 0,00–0,80 · Z: 0,60–1,00; Z-Charakter psychologisch
- **Fähigkeiten:** Dissonanz-Autorisierung, Halteton über beliebig viele Takte
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Tonfolge E

#### JC-B007 Quint-Pedal

- **Charakter:** Pedal auf der Quinte; Akkorde darüber wirken wie Umkehrungen.
- **Typ / Bindung:** Pedal / **eigenständig**
- **Tonfolge:** 5 (alle 8 Takte neu angeschlagen)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 5=A
- **Identität:** Erhalten: Tonhöhe(n). Variabel: Rhythmus, Gate, Akzente, Dichte.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T012 Langfristige Stasis
- **Entwicklungsstrategien:** Stasis, Umfärbung, Atmung
- **XYZ:** Anker (0,50 / 0,35 / 0,35); gültig X: 0,20–0,80 · Y: 0,00–0,70 · Z: 0,10–0,60; Z-Charakter neutral
- **Fähigkeiten:** Halteton über beliebig viele Takte
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-B008 Tritonus-Pedal

- **Charakter:** Pedal auf dem Tritonus; nicht belegt, markierte Ableitung.
- **Typ / Bindung:** Pedal / **Dissonanzpedal**
- **Tonfolge:** ♯4/♭5 (durchgehend gehalten)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** ♯4/♭5=U · autorisiert: ♯4/♭5→U
- **Identität:** Erhalten: Tonhöhe(n). Variabel: Rhythmus, Gate, Akzente, Dichte.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T012 Langfristige Stasis
- **Entwicklungsstrategien:** Stasis, Umfärbung, Atmung
- **XYZ:** Anker (0,15 / 0,60 / 0,85); gültig X: 0,00–0,30 · Y: 0,30–0,90 · Z: 0,70–1,00; Z-Charakter psychologisch
- **Fähigkeiten:** Dissonanz-Autorisierung, Halteton über beliebig viele Takte
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Tonfolge E

#### JC-B009 Pulsierender Achtelbass

- **Charakter:** Achtel auf dem jeweiligen Akkordgrundton.
- **Typ / Bindung:** Puls / **akkordgebunden**
- **Tonfolge (1 Töne):** 0 → 1
- **Rhythmus:** JC-R002 Achtelpuls (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 216 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A
- **Identität:** Erhalten: Tonhöhe(n). Variabel: Rhythmus, Gate, Akzente, Dichte.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Umfärbung, Atmung
- **XYZ:** Anker (0,50 / 0,65 / 0,45); gültig X: 0,00–1,00 · Y: 0,30–1,00 · Z: 0,20–0,70; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-B010 Stoischer Achtelbass

- **Charakter:** Achtel auf dem Grundton, folgt den Akkorden bewusst nicht.
- **Typ / Bindung:** Puls / **eigenständig**
- **Tonfolge (1 Töne):** 0 → 1
- **Rhythmus:** JC-R002 Achtelpuls (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 216 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A
- **Identität:** Erhalten: Tonhöhe(n). Variabel: Rhythmus, Gate, Akzente, Dichte.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Umfärbung, Atmung
- **XYZ:** Anker (0,50 / 0,65 / 0,45); gültig X: 0,00–1,00 · Y: 0,30–1,00 · Z: 0,20–0,70; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-B011 Tiefer Viertelpuls

- **Charakter:** Viertel tief; ruhige, schwere Bewegung.
- **Typ / Bindung:** Puls / **akkordgebunden**
- **Tonfolge (1 Töne):** 0 → 1
- **Rhythmus:** JC-R001 Viertelpuls (4/4, 4 Einsätze, Periode 3840 Ticks); Positionen: 0, 960, 1920, 2880; Dauern: 480 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A
- **Identität:** Erhalten: Tonhöhe(n). Variabel: Rhythmus, Gate, Akzente, Dichte.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Umfärbung, Atmung
- **XYZ:** Anker (0,50 / 0,60 / 0,25); gültig X: 0,00–1,00 · Y: 0,20–1,00 · Z: 0,00–0,50; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-B012 Sechzehntelbass

- **Charakter:** Dichter Puls, sehr kurzes Gate.
- **Typ / Bindung:** Puls / **akkordgebunden**
- **Tonfolge (1 Töne):** 0 → 1
- **Rhythmus:** JC-R003 Sechzehntelpuls (4/4, 16 Einsätze, Periode 3840 Ticks); Positionen: 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600; Dauern: 84 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A
- **Identität:** Erhalten: Tonhöhe(n). Variabel: Rhythmus, Gate, Akzente, Dichte.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Umfärbung, Atmung
- **XYZ:** Anker (0,50 / 0,75 / 0,70); gültig X: 0,00–1,00 · Y: 0,50–1,00 · Z: 0,40–1,00; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-B013 Herzschlag-Bass

- **Charakter:** Schwer–leicht auf dem Grundton; das Herzschlag-Verfahren.
- **Typ / Bindung:** Puls / **eigenständig**
- **Tonfolge (2 Töne):** 0 0 → 1 1
- **Intervalle:** Prime
- **Rhythmus:** JC-R008 Herzschlag (4/4, 2 Einsätze, Periode 3840 Ticks); Positionen: 0, 720; Dauern: 72 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1=A
- **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T011 Unterbrechung und Wiederaufnahme
- **Entwicklungsstrategien:** Stasis, Rotation, Atmung
- **XYZ:** Anker (0,50 / 0,45 / 0,45); gültig X: 0,00–1,00 · Y: 0,10–0,80 · Z: 0,20–0,70; Z-Charakter psychologisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-B014 Langsamer Herzschlag-Bass

- **Charakter:** Ein Herzschlag-Paar alle zwei Takte.
- **Typ / Bindung:** Puls / **eigenständig**
- **Tonfolge (2 Töne):** 0 0 → 1 1
- **Intervalle:** Prime
- **Rhythmus:** JC-R009 Langsamer Herzschlag (4/4, 2 Einsätze, Periode 7680 Ticks); Positionen: 0, 720; Dauern: 72 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1=A
- **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T011 Unterbrechung und Wiederaufnahme
- **Entwicklungsstrategien:** Stasis, Rotation, Atmung
- **XYZ:** Anker (0,50 / 0,30 / 0,50); gültig X: 0,00–1,00 · Y: 0,00–0,60 · Z: 0,10–0,90; Z-Charakter psychologisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-B015 Offbeat-Bass

- **Charakter:** Nur auf den Offbeats; Partner zu einem Puls auf den Zählzeiten.
- **Typ / Bindung:** Puls / **akkordgebunden**
- **Tonfolge (1 Töne):** 0 → 1
- **Rhythmus:** JC-R053 Komplement B: Offbeat (4/4, 4 Einsätze, Periode 3840 Ticks); Positionen: 480, 1440, 2400, 3360; Dauern: 216 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A
- **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Rotation, Atmung
- **XYZ:** Anker (0,50 / 0,60 / 0,50); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,30–0,70; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-B016 Tresillo-Grundton

- **Charakter:** 3+3+2 auf dem Grundton.
- **Typ / Bindung:** Rhythmus / **akkordgebunden**
- **Tonfolge (1 Töne):** 0 → 1
- **Rhythmus:** JC-R020 Tresillo (4/4, 3 Einsätze, Periode 3840 Ticks); Positionen: 0, 1440, 2880; Dauern: 192 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A
- **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T010 Akzentgruppen-Variation
- **Entwicklungsstrategien:** Stasis, Rotation, Atmung
- **XYZ:** Anker (0,50 / 0,60 / 0,40); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,20–0,60; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-B017 Galopp-Bass

- **Charakter:** Lang–kurz–kurz im Bass; Verfolgung.
- **Typ / Bindung:** Rhythmus / **akkordgebunden**
- **Tonfolge (1 Töne):** 0 → 1
- **Rhythmus:** JC-R015 Galopp (4/4, 12 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 720, 960, 1440, 1680, 1920, 2400, 2640, 2880, 3360, 3600; Dauern: 96 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A
- **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Rotation, Atmung
- **XYZ:** Anker (0,50 / 0,80 / 0,75); gültig X: 0,00–1,00 · Y: 0,60–1,00 · Z: 0,50–1,00; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-B018 Stolper-Bass

- **Charakter:** Achtel mit verrutschter Zählzeit.
- **Typ / Bindung:** Rhythmus / **eigenständig**
- **Tonfolge (1 Töne):** 0 → 1
- **Rhythmus:** JC-R058 Stolper-Achtel (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 2160, 2400, 2880, 3360; Dauern: 84 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A
- **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Rotation, Atmung
- **XYZ:** Anker (0,50 / 0,60 / 0,70); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,50–0,90; Z-Charakter psychologisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-B019 Fünfer-Akzentbass

- **Charakter:** Achtel im 5/4 mit 3+3+2+2-Akzenten auf einem Ton.
- **Typ / Bindung:** Rhythmus / **eigenständig**
- **Tonfolge (1 Töne):** 0 → 1
- **Rhythmus:** JC-R024 5/4 als 3+3+2+2 (5/4, 10 Einsätze, Periode 4800 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360, 3840, 4320; Dauern: 192 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A
- **Identität:** Erhalten: Akzentgruppierung und Kontur. Variabel: Transposition, Gate, Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T010 Akzentgruppen-Variation
- **Entwicklungsstrategien:** Stasis, Blockverschiebung
- **XYZ:** Anker (0,50 / 0,70 / 0,65); gültig X: 0,00–1,00 · Y: 0,40–1,00 · Z: 0,40–0,90; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-B020 Synkopen-Bass

- **Charakter:** Schläge vor dem Taktstrich, übergebunden; die Eins bleibt leer.
- **Typ / Bindung:** Rhythmus / **eigenständig**
- **Tonfolge (3 Töne):** 0 -5 0 → 1 5-1Okt 1
- **Intervalle:** Quarte↓, Quarte↑
- **Rhythmus:** JC-R021 Synkope über den Taktstrich (4/4, 3 Einsätze, Periode 7680 Ticks); Positionen: 0, 3360, 7200; Dauern: 408, 816 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 5-1Okt=A, 1=A
- **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T010 Akzentgruppen-Variation
- **Entwicklungsstrategien:** Stasis, Rotation, Atmung
- **XYZ:** Anker (0,50 / 0,45 / 0,50); gültig X: 0,00–1,00 · Y: 0,20–0,70 · Z: 0,30–0,70; Z-Charakter psychologisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Tonfolge E

#### JC-B021 Moll-Riff

- **Charakter:** Eigenständige Achtel-Basssequenz in Riff-Tradition (eigene Konstruktion).
- **Typ / Bindung:** Melodisch / **eigenständig**
- **Tonfolge (8 Töne):** 0 0 +3 0 +5 +3 0 -2 → 1 1 ♭3 1 4 ♭3 1 ♭7-1Okt
- **Intervalle:** Prime, kleine Terz↑, kleine Terz↓, Quarte↑, große Sekunde↓, kleine Terz↓, große Sekunde↓
- **Rhythmus:** JC-R002 Achtelpuls (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 216 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1=A, ♭3=A, 1=A, 4=T, ♭3=A, 1=A, ♭7-1Okt=T
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T010 Akzentgruppen-Variation
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,35 / 0,75 / 0,40); gültig X: 0,10–0,60 · Y: 0,50–1,00 · Z: 0,20–0,60; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-B022 Quart-Riff

- **Charakter:** Quarte und Quinte umkreisen den Grundton.
- **Typ / Bindung:** Melodisch / **eigenständig**
- **Tonfolge (8 Töne):** 0 +5 0 +7 0 +5 +3 0 → 1 4 1 5 1 4 ♭3 1
- **Intervalle:** Quarte↑, Quarte↓, Quinte↑, Quinte↓, Quarte↑, große Sekunde↓, kleine Terz↓
- **Rhythmus:** JC-R002 Achtelpuls (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 216 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 4=T, 1=A, 5=A, 1=A, 4=T, ♭3=A, 1=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T010 Akzentgruppen-Variation
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,35 / 0,75 / 0,40); gültig X: 0,10–0,60 · Y: 0,50–1,00 · Z: 0,20–0,60; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-B023 Paarweise fallende Basssequenz

- **Charakter:** Achtelpaare steigen stufenweise ab; kehrt jeden Takt zurück.
- **Typ / Bindung:** Melodisch / **eigenständig**
- **Tonfolge (8 Töne):** 0 0 -2 -2 -4 -4 -5 -5 → 1 1 ♭7-1Okt ♭7-1Okt ♭6-1Okt ♭6-1Okt 5-1Okt 5-1Okt
- **Intervalle:** Prime, große Sekunde↓, Prime, große Sekunde↓, Prime, kleine Sekunde↓, Prime
- **Rhythmus:** JC-R002 Achtelpuls (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 216 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1=A, ♭7-1Okt=T, ♭7-1Okt=T, ♭6-1Okt=T, ♭6-1Okt=T, 5-1Okt=A, 5-1Okt=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,35 / 0,70 / 0,30); gültig X: 0,10–0,60 · Y: 0,40–1,00 · Z: 0,10–0,50; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-B024 Kreisender Triolenbass

- **Charakter:** Kreisende Moll-Triolen; weich treibend.
- **Typ / Bindung:** Melodisch / **eigenständig**
- **Tonfolge (6 Töne):** 0 +3 +5 +7 +5 +3 → 1 ♭3 4 5 4 ♭3
- **Intervalle:** kleine Terz↑, große Sekunde↑, große Sekunde↑, große Sekunde↓, große Sekunde↓
- **Rhythmus:** JC-R032 Achteltriolen betont (4/4, 12 Einsätze, Periode 3840 Ticks); Positionen: 0, 320, 640, 960, 1280, 1600, 1920, 2240, 2560, 2880, 3200, 3520; Dauern: 122 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, ♭3=A, 4=T, 5=A, 4=T, ♭3=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,40 / 0,65 / 0,40); gültig X: 0,20–0,60 · Y: 0,40–0,90 · Z: 0,20–0,60; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-B025 Fünfer-Basssequenz

- **Charakter:** Melodische Bassfigur im 5/4.
- **Typ / Bindung:** Melodisch / **eigenständig**
- **Tonfolge (10 Töne):** 0 0 +3 0 -2 0 0 +7 0 +5 → 1 1 ♭3 1 ♭7-1Okt 1 1 5 1 4
- **Intervalle:** Prime, kleine Terz↑, kleine Terz↓, große Sekunde↓, große Sekunde↑, Prime, Quinte↑, Quinte↓, Quarte↑
- **Rhythmus:** JC-R024 5/4 als 3+3+2+2 (5/4, 10 Einsätze, Periode 4800 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360, 3840, 4320; Dauern: 192 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1=A, ♭3=A, 1=A, ♭7-1Okt=T, 1=A, 1=A, 5=A, 1=A, 4=T
- **Identität:** Erhalten: Akzentgruppierung und Kontur. Variabel: Transposition, Gate, Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T010 Akzentgruppen-Variation
- **Entwicklungsstrategien:** Stasis, Blockverschiebung
- **XYZ:** Anker (0,30 / 0,70 / 0,70); gültig X: 0,00–0,60 · Y: 0,40–1,00 · Z: 0,50–0,90; Z-Charakter mechanisch
- **Fähigkeiten:** lange Sequenz (> 8 Töne)
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Tonfolge E

#### JC-B026 Oktav-Achtelbass

- **Charakter:** Grundton–Oktave in Achteln; der klassische Synth-Bass als Verfahren.
- **Typ / Bindung:** Oktave / **akkordgebunden**
- **Tonfolge (2 Töne):** 0 +12 → 1 1+1Okt
- **Intervalle:** Oktave↑
- **Rhythmus:** JC-R002 Achtelpuls (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 216 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1+1Okt=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,50 / 0,70 / 0,40); gültig X: 0,00–1,00 · Y: 0,40–1,00 · Z: 0,20–0,60; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-B027 Oktavsprung-Viertel

- **Charakter:** Ruhiger Oktavwechsel in Vierteln.
- **Typ / Bindung:** Oktave / **akkordgebunden**
- **Tonfolge (2 Töne):** 0 +12 → 1 1+1Okt
- **Intervalle:** Oktave↑
- **Rhythmus:** JC-R001 Viertelpuls (4/4, 4 Einsätze, Periode 3840 Ticks); Positionen: 0, 960, 1920, 2880; Dauern: 480 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1+1Okt=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,50 / 0,60 / 0,30); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,10–0,50; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-B028 Oktav-Tresillo

- **Charakter:** Tresillo, der dritte Schlag springt zur Oktave.
- **Typ / Bindung:** Oktave / **akkordgebunden**
- **Tonfolge (3 Töne):** 0 0 +12 → 1 1 1+1Okt
- **Intervalle:** Prime, Oktave↑
- **Rhythmus:** JC-R020 Tresillo (4/4, 3 Einsätze, Periode 3840 Ticks); Positionen: 0, 1440, 2880; Dauern: 192 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1=A, 1+1Okt=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T010 Akzentgruppen-Variation
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,50 / 0,70 / 0,40); gültig X: 0,00–1,00 · Y: 0,40–1,00 · Z: 0,20–0,60; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-B029 Chromatischer Kriechbass aufwärts

- **Charakter:** Ein Halbton pro Takt nach oben.
- **Typ / Bindung:** Chromatisch / **eigenständig**
- **Tonfolge (4 Töne):** 0 +1 +2 +3 → 1 ♭2 2 ♭3
- **Intervalle:** kleine Sekunde↑, kleine Sekunde↑, kleine Sekunde↑
- **Rhythmus:** JC-R019 Ganze Noten (4/4, 1 Einsätze, Periode 3840 Ticks); Positionen: 0; Dauern: 3763 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, ♭2=U, 2=T, ♭3=A · autorisiert: ♭2→U
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,25 / 0,60 / 0,75); gültig X: 0,00–0,50 · Y: 0,30–0,90 · Z: 0,50–1,00; Z-Charakter psychologisch
- **Fähigkeiten:** Dissonanz-Autorisierung
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-B030 Chromatischer Kriechbass abwärts

- **Charakter:** Ein Halbton pro Takt nach unten; ohne Ziel.
- **Typ / Bindung:** Chromatisch / **eigenständig**
- **Tonfolge (4 Töne):** 0 -1 -2 -3 → 1 7-1Okt ♭7-1Okt 6-1Okt
- **Intervalle:** kleine Sekunde↓, kleine Sekunde↓, kleine Sekunde↓
- **Rhythmus:** JC-R019 Ganze Noten (4/4, 1 Einsätze, Periode 3840 Ticks); Positionen: 0; Dauern: 3763 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 7-1Okt=U, ♭7-1Okt=T, 6-1Okt=U · autorisiert: 7→U, 6→U
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,30 / 0,40 / 0,75); gültig X: 0,00–0,60 · Y: 0,00–0,80 · Z: 0,50–1,00; Z-Charakter psychologisch
- **Fähigkeiten:** Dissonanz-Autorisierung
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-B031 Halbtonversetzter Achtelbass

- **Charakter:** Achtelbass, jeder zweite Takt einen Halbton höher (Blockverschiebung).
- **Typ / Bindung:** Chromatisch / **eigenständig**
- **Tonfolge (16 Töne):** 0 0 0 0 0 0 0 0 +1 +1 +1 +1 +1 +1 +1 +1 → 1 1 1 1 1 1 1 1 ♭2 ♭2 ♭2 ♭2 ♭2 ♭2 ♭2 ♭2
- **Intervalle:** Prime, Prime, Prime, Prime, Prime, Prime, Prime, kleine Sekunde↑, Prime, Prime, Prime, Prime, Prime, Prime, Prime
- **Rhythmus:** JC-R002 Achtelpuls (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 216 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1=A, 1=A, 1=A, 1=A, 1=A, 1=A, 1=A, ♭2=U, ♭2=U, ♭2=U, ♭2=U, ♭2=U, ♭2=U, ♭2=U, ♭2=U · autorisiert: ♭2→U
- **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Rotation, Atmung
- **XYZ:** Anker (0,20 / 0,70 / 0,75); gültig X: 0,00–0,40 · Y: 0,40–1,00 · Z: 0,50–1,00; Z-Charakter mechanisch
- **Fähigkeiten:** lange Sequenz (> 8 Töne), Dissonanz-Autorisierung
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-B032 Kriechen um kleine Terz und Halbton

- **Charakter:** Bass steigt erst eine kleine Terz, dann einen Halbton; belegtes Verfahren, eigene Tonfolge.
- **Typ / Bindung:** Chromatisch / **eigenständig**
- **Tonfolge (4 Töne):** 0 0 +3 +4 → 1 1 ♭3 3
- **Intervalle:** Prime, kleine Terz↑, kleine Sekunde↑
- **Rhythmus:** JC-R019 Ganze Noten (4/4, 1 Einsätze, Periode 3840 Ticks); Positionen: 0; Dauern: 3763 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1=A, ♭3=A, 3=U · autorisiert: 3→U
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,25 / 0,60 / 0,65); gültig X: 0,00–0,50 · Y: 0,30–0,90 · Z: 0,40–0,90; Z-Charakter psychologisch
- **Fähigkeiten:** Dissonanz-Autorisierung
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-B033 Schreitender Bass abwärts

- **Charakter:** Halbe Noten stufenweise ab und zurück; Fog-artiges Schreiten.
- **Typ / Bindung:** Schreitend / **eigenständig**
- **Tonfolge (8 Töne):** 0 -2 -4 -5 -7 -5 -4 -2 → 1 ♭7-1Okt ♭6-1Okt 5-1Okt 4-1Okt 5-1Okt ♭6-1Okt ♭7-1Okt
- **Intervalle:** große Sekunde↓, große Sekunde↓, kleine Sekunde↓, große Sekunde↓, große Sekunde↑, kleine Sekunde↑, große Sekunde↑
- **Rhythmus:** JC-R006 Halbe-Puls (4/4, 2 Einsätze, Periode 3840 Ticks); Positionen: 0, 1920; Dauern: 1632 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, ♭7-1Okt=T, ♭6-1Okt=T, 5-1Okt=A, 4-1Okt=T, 5-1Okt=A, ♭6-1Okt=T, ♭7-1Okt=T
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,45 / 0,40 / 0,20); gültig X: 0,20–0,70 · Y: 0,10–0,70 · Z: 0,00–0,40; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-B034 Schreitender Bass aufwärts

- **Charakter:** Ein Ton pro Takt, stufenweise steigend.
- **Typ / Bindung:** Schreitend / **eigenständig**
- **Tonfolge (4 Töne):** 0 +2 +3 +5 → 1 2 ♭3 4
- **Intervalle:** große Sekunde↑, kleine Sekunde↑, große Sekunde↑
- **Rhythmus:** JC-R019 Ganze Noten (4/4, 1 Einsätze, Periode 3840 Ticks); Positionen: 0; Dauern: 3763 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 2=T, ♭3=A, 4=T
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,55 / 0,40 / 0,25); gültig X: 0,30–0,80 · Y: 0,10–0,70 · Z: 0,10–0,40; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-B035 Quintfall-Schritte

- **Charakter:** Grundton, Quinte, ♭7, Quarte; ruhiges Schreiten.
- **Typ / Bindung:** Schreitend / **eigenständig**
- **Tonfolge (4 Töne):** 0 -5 -2 -7 → 1 5-1Okt ♭7-1Okt 4-1Okt
- **Intervalle:** Quarte↓, kleine Terz↑, Quarte↓
- **Rhythmus:** JC-R019 Ganze Noten (4/4, 1 Einsätze, Periode 3840 Ticks); Positionen: 0; Dauern: 3763 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 5-1Okt=A, ♭7-1Okt=T, 4-1Okt=T
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,45 / 0,50 / 0,20); gültig X: 0,20–0,70 · Y: 0,20–0,80 · Z: 0,00–0,40; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-B036 Bewegter Bass unter Fläche

- **Charakter:** Viertelbewegung unter stehender Quintfläche.
- **Typ / Bindung:** Bewegt / **eigenständig**
- **Tonfolge (4 Töne):** 0 +3 +5 +3 → 1 ♭3 4 ♭3
- **Intervalle:** kleine Terz↑, große Sekunde↑, große Sekunde↓
- **Rhythmus:** JC-R001 Viertelpuls (4/4, 4 Einsätze, Periode 3840 Ticks); Positionen: 0, 960, 1920, 2880; Dauern: 480 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, ♭3=A, 4=T, ♭3=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,45 / 0,50 / 0,30); gültig X: 0,20–0,70 · Y: 0,20–0,80 · Z: 0,10–0,50; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-B037 Quint-Quart-Wechsel

- **Charakter:** Bewegung ohne Terz; passt unter leere Flächen.
- **Typ / Bindung:** Bewegt / **eigenständig**
- **Tonfolge (4 Töne):** 0 +7 +5 +7 → 1 5 4 5
- **Intervalle:** Quinte↑, große Sekunde↓, große Sekunde↑
- **Rhythmus:** JC-R001 Viertelpuls (4/4, 4 Einsätze, Periode 3840 Ticks); Positionen: 0, 960, 1920, 2880; Dauern: 480 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 5=A, 4=T, 5=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,45 / 0,55 / 0,20); gültig X: 0,20–0,70 · Y: 0,30–0,80 · Z: 0,00–0,40; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-B038 Bass auf Schlag

- **Charakter:** Schläge auf den Zählzeiten; Partner zu Offbeat-Sequencern.
- **Typ / Bindung:** Komplementär / **akkordgebunden**
- **Tonfolge (1 Töne):** 0 → 1
- **Rhythmus:** JC-R052 Komplement A: Schlag (4/4, 4 Einsätze, Periode 3840 Ticks); Positionen: 0, 960, 1920, 2880; Dauern: 216 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A
- **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung
- **Entwicklungsstrategien:** Stasis, Rotation, Atmung
- **XYZ:** Anker (0,50 / 0,60 / 0,40); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,20–0,60; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-B039 Tresillo-Komplementbass

- **Charakter:** Füllt die Lücken eines Tresillo im Sequencer.
- **Typ / Bindung:** Komplementär / **akkordgebunden**
- **Tonfolge (1 Töne):** 0 → 1
- **Rhythmus:** JC-R054 Tresillo-Komplement (4/4, 5 Einsätze, Periode 3840 Ticks); Positionen: 480, 960, 1920, 2400, 3360; Dauern: 192 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A
- **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung
- **Entwicklungsstrategien:** Stasis, Rotation, Atmung
- **XYZ:** Anker (0,50 / 0,60 / 0,50); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,30–0,70; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-B040 Kreuz-Bass

- **Charakter:** Sechzehntel-Kreuz im Bass; Partner zu Kreuz B.
- **Typ / Bindung:** Komplementär / **akkordgebunden**
- **Tonfolge (4 Töne):** 0 0 +12 0 → 1 1 1+1Okt 1
- **Intervalle:** Prime, Oktave↑, Oktave↓
- **Rhythmus:** JC-R055 Kreuz A (4/4, 4 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 1200, 1680; Dauern: 84 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1=A, 1+1Okt=A, 1=A
- **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung
- **Entwicklungsstrategien:** Stasis, Rotation, Atmung
- **XYZ:** Anker (0,50 / 0,70 / 0,60); gültig X: 0,00–1,00 · Y: 0,40–1,00 · Z: 0,40–0,80; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-B041 Bewusster Bassverzicht

- **Charakter:** Kein Bass. Belegt in pulslosen und hohen Texturen; wird ausdrücklich gewählt, nicht weggelassen.
- **Typ / Bindung:** Verzicht / **eigenständig**
- **Tonfolge:** keine (bewusster Verzicht)
- **XYZ:** X: 0,00–1,00 · Y: 0,00–1,00 · Z: 0,00–1,00
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren

#### JC-B042 Herzschlag mit Oktave

- **Charakter:** Herzschlag von oben nach unten; schwerer Aufprall.
- **Typ / Bindung:** Puls / **eigenständig**
- **Tonfolge (2 Töne):** +12 0 → 1+1Okt 1
- **Intervalle:** Oktave↓
- **Rhythmus:** JC-R008 Herzschlag (4/4, 2 Einsätze, Periode 3840 Ticks); Positionen: 0, 720; Dauern: 72 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1+1Okt=A, 1=A
- **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T011 Unterbrechung und Wiederaufnahme
- **Entwicklungsstrategien:** Stasis, Rotation, Atmung
- **XYZ:** Anker (0,50 / 0,60 / 0,50); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,30–0,70; Z-Charakter psychologisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-B043 Gedämpfter Einzelschlag-Bass

- **Charakter:** Zwei leise Schläge, ein Takt Stille.
- **Typ / Bindung:** Puls / **eigenständig**
- **Tonfolge (2 Töne):** 0 0 → 1 1
- **Intervalle:** Prime
- **Rhythmus:** JC-R012 Gedämpfter Einzelschlag (4/4, 2 Einsätze, Periode 7680 Ticks); Positionen: 0, 1920; Dauern: 84 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1=A
- **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T011 Unterbrechung und Wiederaufnahme
- **Entwicklungsstrategien:** Stasis, Rotation, Atmung
- **XYZ:** Anker (0,50 / 0,20 / 0,25); gültig X: 0,00–1,00 · Y: 0,00–0,40 · Z: 0,00–0,50; Z-Charakter psychologisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-B044 Ein Bassschlag pro Takt

- **Charakter:** Ein kurzer tiefer Schlag am Taktanfang.
- **Typ / Bindung:** Puls / **akkordgebunden**
- **Tonfolge (1 Töne):** 0 → 1
- **Rhythmus:** JC-R007 Ein Schlag pro Takt (4/4, 1 Einsätze, Periode 3840 Ticks); Positionen: 0; Dauern: 768 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A
- **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Rotation, Atmung
- **XYZ:** Anker (0,50 / 0,30 / 0,20); gültig X: 0,00–1,00 · Y: 0,00–0,60 · Z: 0,00–0,40; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-B045 Halbe Grundton–Quinte

- **Charakter:** Ruhige Halbe zwischen Grundton und tiefer Quinte.
- **Typ / Bindung:** Schreitend / **akkordgebunden**
- **Tonfolge (2 Töne):** 0 -5 → 1 5-1Okt
- **Intervalle:** Quarte↓
- **Rhythmus:** JC-R006 Halbe-Puls (4/4, 2 Einsätze, Periode 3840 Ticks); Positionen: 0, 1920; Dauern: 1632 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 5-1Okt=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,50 / 0,55 / 0,15); gültig X: 0,00–1,00 · Y: 0,10–1,00 · Z: 0,00–0,30; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-B046 Uhrwerk-Bass

- **Charakter:** Ticken im Bass, jeder dritte Schlag oktaviert.
- **Typ / Bindung:** Rhythmus / **eigenständig**
- **Tonfolge (4 Töne):** 0 0 +12 0 → 1 1 1+1Okt 1
- **Intervalle:** Prime, Oktave↑, Oktave↓
- **Rhythmus:** JC-R061 Uhrwerk tick-tack (4/4, 16 Einsätze, Periode 3840 Ticks); Positionen: 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600; Dauern: 48 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1=A, 1+1Okt=A, 1=A
- **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Rotation, Atmung
- **XYZ:** Anker (0,50 / 0,60 / 0,70); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,50–0,90; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-B047 Kriechende Triolen tief

- **Charakter:** Tiefe Triolenfigur mit ♭2; das kriechende Prince-of-Darkness-Verfahren, eigene Tonfolge.
- **Typ / Bindung:** Chromatisch / **eigenständig**
- **Tonfolge (6 Töne):** 0 +1 +3 +1 0 -2 → 1 ♭2 ♭3 ♭2 1 ♭7-1Okt
- **Intervalle:** kleine Sekunde↑, große Sekunde↑, große Sekunde↓, kleine Sekunde↓, große Sekunde↓
- **Rhythmus:** JC-R017 Viertel-Triolen (4/4, 6 Einsätze, Periode 3840 Ticks); Positionen: 0, 640, 1280, 1920, 2560, 3200; Dauern: 384 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, ♭2=U, ♭3=A, ♭2=U, 1=A, ♭7-1Okt=T · autorisiert: ♭2→U
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,20 / 0,50 / 0,60); gültig X: 0,00–0,40 · Y: 0,20–0,80 · Z: 0,40–0,80; Z-Charakter psychologisch
- **Fähigkeiten:** Dissonanz-Autorisierung
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-B048 Achtelbass mit Atemloch

- **Charakter:** Achtelbass mit einem Atemloch alle acht Takte.
- **Typ / Bindung:** Puls / **akkordgebunden**
- **Tonfolge (1 Töne):** 0 → 1
- **Rhythmus:** JC-R044 Sieben an, einer aus (4/4, 56 Einsätze, Periode 30720 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360, 3840, 4320, 4800, 5280, 5760, 6240, 6720, 7200, 7680, 8160, 8640, 9120, 9600, 10080, 10560, 11040, 11520, 12000, 12480, 12960, 13440, 13920, 14400, 14880, 15360, 15840, 16320, 16800, 17280, 17760, 18240, 18720, 19200, 19680, 20160, 20640, 21120, 21600, 22080, 22560, 23040, 23520, 24000, 24480, 24960, 25440, 25920, 26400; Dauern: 216 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A
- **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T011 Unterbrechung und Wiederaufnahme
- **Entwicklungsstrategien:** Stasis, Rotation, Atmung
- **XYZ:** Anker (0,50 / 0,60 / 0,30); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,10–0,50; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Tonfolge E

#### JC-B049 Lang–kurz-Bass

- **Charakter:** Achtel mit abwechselnd langem und kurzem Gate.
- **Typ / Bindung:** Puls / **akkordgebunden**
- **Tonfolge (1 Töne):** 0 → 1
- **Rhythmus:** JC-R038 Gate-Wechsel lang–kurz (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 432, 96 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A
- **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **Entwicklungsstrategien:** Stasis, Rotation, Atmung
- **XYZ:** Anker (0,50 / 0,55 / 0,40); gültig X: 0,00–1,00 · Y: 0,30–0,80 · Z: 0,20–0,60; Z-Charakter neutral
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Tonfolge E

#### JC-B050 Synkopiertes Riff

- **Charakter:** Rollende Sechzehntelsynkope mit ♭7 und tiefer Quinte.
- **Typ / Bindung:** Melodisch / **eigenständig**
- **Tonfolge (5 Töne):** 0 0 -2 0 -5 → 1 1 ♭7-1Okt 1 5-1Okt
- **Intervalle:** Prime, große Sekunde↓, große Sekunde↑, Quarte↓
- **Rhythmus:** JC-R023 Sechzehntel-Synkope (4/4, 5 Einsätze, Periode 3840 Ticks); Positionen: 0, 720, 1440, 2400, 3120; Dauern: 84 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1=A, ♭7-1Okt=T, 1=A, 5-1Okt=A
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T010 Akzentgruppen-Variation
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,35 / 0,75 / 0,60); gültig X: 0,10–0,60 · Y: 0,50–1,00 · Z: 0,40–0,80; Z-Charakter mechanisch
- **Fähigkeiten:** Standard
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-B051 Blue-Note-Bass

- **Charakter:** Viertel aufwärts zur ♭5; bluesige Ableitung, eher POP/ROCK.
- **Typ / Bindung:** Melodisch / **eigenständig**
- **Tonfolge (4 Töne):** 0 +3 +5 +6 → 1 ♭3 4 ♯4/♭5
- **Intervalle:** kleine Terz↑, große Sekunde↑, kleine Sekunde↑
- **Rhythmus:** JC-R001 Viertelpuls (4/4, 4 Einsätze, Periode 3840 Ticks); Positionen: 0, 960, 1920, 2880; Dauern: 480 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, ♭3=A, 4=T, ♯4/♭5=U · autorisiert: ♯4/♭5→U
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,30 / 0,65 / 0,60); gültig X: 0,10–0,50 · Y: 0,40–0,90 · Z: 0,40–0,80; Z-Charakter psychologisch
- **Fähigkeiten:** Dissonanz-Autorisierung
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Tonfolge E

#### JC-B052 Zweitakt-Bassriff

- **Charakter:** Zwei Takte; Schlusswendung einmal über ♭6, einmal über die Quarte.
- **Typ / Bindung:** Melodisch / **eigenständig**
- **Tonfolge (16 Töne):** 0 0 +12 0 +10 0 +7 +8 0 0 +12 0 +10 0 +7 +5 → 1 1 1+1Okt 1 ♭7 1 5 ♭6 1 1 1+1Okt 1 ♭7 1 5 4
- **Intervalle:** Prime, Oktave↑, Oktave↓, kleine Septime↑, kleine Septime↓, Quinte↑, kleine Sekunde↑, kleine Sexte↓, Prime, Oktave↑, Oktave↓, kleine Septime↑, kleine Septime↓, Quinte↑, große Sekunde↓
- **Rhythmus:** JC-R002 Achtelpuls (4/4, 8 Einsätze, Periode 3840 Ticks); Positionen: 0, 480, 960, 1440, 1920, 2400, 2880, 3360; Dauern: 216 Ticks
- **Zyklus:** gekoppelt (Tonfolge und Rhythmus enden gemeinsam)
- **Harmonische Voraussetzung:** Bezugsklang Molldreiklang auf 1, Tonvorrat Äolisch (natürliches Moll)
- **Tonfunktionen:** 1=A, 1=A, 1+1Okt=A, 1=A, ♭7=T, 1=A, 5=A, ♭6=T, 1=A, 1=A, 1+1Okt=A, 1=A, ♭7=T, 1=A, 5=A, 4=T
- **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Wiederholung/Variation:** unbegrenzt wiederholbar; Variation nicht in festen Zeitabständen. Zulässig: JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T010 Akzentgruppen-Variation
- **Entwicklungsstrategien:** Stasis, Blockverschiebung, Rotation, Umfärbung
- **XYZ:** Anker (0,35 / 0,75 / 0,40); gültig X: 0,10–0,60 · Y: 0,50–1,00 · Z: 0,20–0,60; Z-Charakter neutral
- **Fähigkeiten:** lange Sequenz (> 8 Töne)
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

**Wirkungstabelle (I):** Ruhe – Drone, Halbe; latente Bedrohung – Pedal, langsamer Herzschlag, Kriechbass; Verfolgung – Galopp, Oktav-Achtel, Sechzehntel; Eskalation – Kriechen um kleine Terz/Halbton, Blockversatz; akuter Horror – Wegfall des Basses oder Fremdpedal.

## 7. M – Motive

Positionen und Dauern in Sechzehnteln (× 240 Ticks). Tonhöhen relativ zur Basisoktave der Rolle; `12` = Grundton eine Oktave über der Basis. HM und GS bleiben optional; jedes Motiv funktioniert auch in TU.

#### JC-M001 Einsamer hoher Ruf

- **Charakter:** Ein einziger hoher Ton über tiefem Feld.
- **Noten (1):** 1+2Okt @ 0 Ticks, 3840 Ticks
- **Länge:** 3840 Ticks (1,00 Takte 4/4)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+2Okt=A
- **Rollen:** TU HM; **Identität:** Erhalten: Tonhöhe(n). Variabel: Rhythmus, Gate, Akzente, Dichte.
- **Variation:** JC-T003 Oktavverlagerung, JC-T006 Rollenwanderung, JC-T011 Unterbrechung und Wiederaufnahme
- **XYZ:** Anker (0,65 / 0,25 / 0,25); gültig X: 0,30–1,00 · Y: 0,00–0,50 · Z: 0,00–0,50; Z-Charakter neutral
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-M002 Ruf mit Halbtonfall

- **Charakter:** Hoher Grundton sinkt zum Leitton und bleibt dort.
- **Noten (2):** 1+2Okt @ 0 Ticks, 1920 Ticks; 7+1Okt @ 1920 Ticks, 5760 Ticks
- **Länge:** 7680 Ticks (2,00 Takte 4/4)
- **Intervalle:** kleine Sekunde↓
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+2Okt=A, 7+1Okt=U
- **Rollen:** TU HM; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T006 Rollenwanderung
- **XYZ:** Anker (0,40 / 0,30 / 0,65); gültig X: 0,10–0,70 · Y: 0,00–0,60 · Z: 0,40–0,90; Z-Charakter psychologisch
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-M003 Oktave sinkt zur Quinte

- **Charakter:** Kurzer Anstoß, langes Ausklingen auf der Quinte.
- **Noten (2):** 1+2Okt @ 0 Ticks, 960 Ticks; 5+1Okt @ 960 Ticks, 6720 Ticks
- **Länge:** 7680 Ticks (2,00 Takte 4/4)
- **Intervalle:** Quarte↓
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+2Okt=A, 5+1Okt=A
- **Rollen:** TU HM; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T006 Rollenwanderung
- **XYZ:** Anker (0,50 / 0,30 / 0,25); gültig X: 0,20–0,80 · Y: 0,00–0,60 · Z: 0,00–0,50; Z-Charakter neutral
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-M004 Fernes Echo

- **Charakter:** Drei gleiche Töne, jeder leiser; Echo ohne Delay-Effekt, als komponierte Dynamik.
- **Noten (3):** 1+2Okt @ 0 Ticks, 480 Ticks; 1+2Okt @ 1440 Ticks, 480 Ticks, v60; 1+2Okt @ 2880 Ticks, 480 Ticks, v40
- **Länge:** 3360 Ticks (0,88 Takte 4/4)
- **Intervalle:** Prime, Prime
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+2Okt=A, 1+2Okt=A, 1+2Okt=A
- **Rollen:** TU; **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Variation:** JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **XYZ:** Anker (0,70 / 0,20 / 0,35); gültig X: 0,40–1,00 · Y: 0,00–0,40 · Z: 0,10–0,60; Z-Charakter psychologisch
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Tonfolge E

#### JC-M005 Mechanischer Dreiton

- **Charakter:** Zwei Ticks, der dritte rutscht einen Halbton hoch.
- **Noten (3):** 1+1Okt @ 0 Ticks, 240 Ticks; 1+1Okt @ 480 Ticks, 240 Ticks; ♭2+1Okt @ 960 Ticks, 240 Ticks
- **Länge:** 1200 Ticks (0,31 Takte 4/4)
- **Intervalle:** Prime, kleine Sekunde↑
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+1Okt=A, 1+1Okt=A, ♭2+1Okt=U
- **Rollen:** TU GS; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **XYZ:** Anker (0,30 / 0,50 / 0,70); gültig X: 0,00–0,60 · Y: 0,20–0,80 · Z: 0,50–0,90; Z-Charakter mechanisch
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Tonfolge E

#### JC-M006 Melancholische Zelle

- **Charakter:** Terz, Durchgang, Grundton; ein Seufzer.
- **Noten (3):** ♭3+1Okt @ 0 Ticks, 1440 Ticks; 2+1Okt @ 1440 Ticks, 480 Ticks; 1+1Okt @ 1920 Ticks, 1920 Ticks
- **Länge:** 3840 Ticks (1,00 Takte 4/4)
- **Intervalle:** kleine Sekunde↓, große Sekunde↓
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): ♭3+1Okt=A, 2+1Okt=V, 1+1Okt=A
- **Rollen:** HM GS TU; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **XYZ:** Anker (0,50 / 0,30 / 0,20); gültig X: 0,30–0,70 · Y: 0,00–0,60 · Z: 0,00–0,40; Z-Charakter neutral
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-M007 Melancholische Zelle in Dur

- **Charakter:** Dieselbe Kontur mit Durterz; Licht, das nicht tröstet.
- **Noten (3):** 3+1Okt @ 0 Ticks, 1440 Ticks; 2+1Okt @ 1440 Ticks, 480 Ticks; 1+1Okt @ 1920 Ticks, 1920 Ticks
- **Länge:** 3840 Ticks (1,00 Takte 4/4)
- **Intervalle:** große Sekunde↓, große Sekunde↓
- **Tonfunktionen** (Bezug Durdreiklang, Ionisch (Dur)): 3+1Okt=A, 2+1Okt=V, 1+1Okt=A
- **Rollen:** HM GS TU; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **XYZ:** Anker (0,70 / 0,25 / 0,20); gültig X: 0,50–0,90 · Y: 0,00–0,50 · Z: 0,00–0,40; Z-Charakter neutral
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-M008 Sextsprung

- **Charakter:** Grundton springt zur ♭6; dunkle Öffnung.
- **Noten (2):** 1+1Okt @ 0 Ticks, 1920 Ticks; ♭6+1Okt @ 1920 Ticks, 1920 Ticks
- **Länge:** 3840 Ticks (1,00 Takte 4/4)
- **Intervalle:** kleine Sexte↑
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+1Okt=A, ♭6+1Okt=T
- **Rollen:** HM GS TU; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,25 / 0,40 / 0,40); gültig X: 0,00–0,50 · Y: 0,10–0,70 · Z: 0,20–0,60; Z-Charakter psychologisch
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-M009 Tritonus-Ruf

- **Charakter:** Grundton zum Tritonus; nicht belegt, markiert.
- **Noten (2):** 1+1Okt @ 0 Ticks, 2880 Ticks; ♯4/♭5+1Okt @ 2880 Ticks, 4800 Ticks
- **Länge:** 7680 Ticks (2,00 Takte 4/4)
- **Intervalle:** Tritonus↑
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+1Okt=A, ♯4/♭5+1Okt=U
- **Rollen:** HM TU; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,15 / 0,50 / 0,80); gültig X: 0,00–0,30 · Y: 0,20–0,80 · Z: 0,60–1,00; Z-Charakter psychologisch
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Tonfolge E

#### JC-M010 Halbton-Seufzer

- **Charakter:** ♭6 sinkt zur Quinte; der Vorhalt löst sich, die Stimmung nicht.
- **Noten (2):** ♭6+1Okt @ 0 Ticks, 2880 Ticks; 5+1Okt @ 2880 Ticks, 4800 Ticks
- **Länge:** 7680 Ticks (2,00 Takte 4/4)
- **Intervalle:** kleine Sekunde↓
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): ♭6+1Okt=T, 5+1Okt=A
- **Rollen:** HM GS TU; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T006 Rollenwanderung
- **XYZ:** Anker (0,30 / 0,30 / 0,40); gültig X: 0,00–0,60 · Y: 0,00–0,60 · Z: 0,20–0,60; Z-Charakter psychologisch
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-M011 Sechston-Fragment

- **Charakter:** Sechs Töne über zwei Takte; längeres Fragment wie im Prince-of-Darkness-Verfahren, eigene Tonfolge.
- **Noten (6):** 1+1Okt @ 0 Ticks, 960 Ticks; ♭3+1Okt @ 960 Ticks, 960 Ticks; 5+1Okt @ 1920 Ticks, 960 Ticks; ♭6+1Okt @ 2880 Ticks, 1920 Ticks; 5+1Okt @ 4800 Ticks, 960 Ticks; ♭3+1Okt @ 5760 Ticks, 1920 Ticks
- **Länge:** 7680 Ticks (2,00 Takte 4/4)
- **Intervalle:** kleine Terz↑, große Terz↑, kleine Sekunde↑, kleine Sekunde↓, große Terz↓
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+1Okt=A, ♭3+1Okt=A, 5+1Okt=A, ♭6+1Okt=T, 5+1Okt=A, ♭3+1Okt=A
- **Rollen:** HM GS; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T001 Blocktransposition, JC-T005 Motivfragmentierung, JC-T008 Harmonische Umfärbung
- **XYZ:** Anker (0,45 / 0,40 / 0,30); gültig X: 0,20–0,70 · Y: 0,10–0,70 · Z: 0,10–0,50; Z-Charakter neutral
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-M012 Lyrische Linie

- **Charakter:** Sieben Töne, drei Takte; melancholisch, für die Christine-/Leuchtturm-Familie.
- **Noten (7):** 5+1Okt @ 0 Ticks, 1920 Ticks; 4+1Okt @ 1920 Ticks, 960 Ticks; ♭3+1Okt @ 2880 Ticks, 960 Ticks; 2+1Okt @ 3840 Ticks, 1920 Ticks; 1+1Okt @ 5760 Ticks, 960 Ticks; 2+1Okt @ 6720 Ticks, 960 Ticks; ♭3+1Okt @ 7680 Ticks, 3840 Ticks
- **Länge:** 11520 Ticks (3,00 Takte 4/4)
- **Intervalle:** große Sekunde↓, große Sekunde↓, kleine Sekunde↓, große Sekunde↓, große Sekunde↑, kleine Sekunde↑
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 5+1Okt=A, 4+1Okt=V, ♭3+1Okt=A, 2+1Okt=T, 1+1Okt=A, 2+1Okt=V, ♭3+1Okt=A
- **Rollen:** HM; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T005 Motivfragmentierung, JC-T008 Harmonische Umfärbung, JC-T006 Rollenwanderung
- **XYZ:** Anker (0,55 / 0,30 / 0,20); gültig X: 0,30–0,80 · Y: 0,00–0,60 · Z: 0,00–0,40; Z-Charakter neutral
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-M013 Frage und Antwort

- **Charakter:** Aufsteigende Frage, fallende Antwort; als Prinzip nur angedeutet belegt.
- **Noten (6):** 1+1Okt @ 0 Ticks, 960 Ticks; ♭3+1Okt @ 960 Ticks, 960 Ticks; 5+1Okt @ 1920 Ticks, 1920 Ticks; 5+1Okt @ 3840 Ticks, 960 Ticks; 4+1Okt @ 4800 Ticks, 960 Ticks; 1+1Okt @ 5760 Ticks, 1920 Ticks
- **Länge:** 7680 Ticks (2,00 Takte 4/4)
- **Intervalle:** kleine Terz↑, große Terz↑, Prime, große Sekunde↓, Quarte↓
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+1Okt=A, ♭3+1Okt=A, 5+1Okt=A, 5+1Okt=A, 4+1Okt=T, 1+1Okt=A
- **Rollen:** HM GS; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T005 Motivfragmentierung, JC-T006 Rollenwanderung
- **XYZ:** Anker (0,50 / 0,30 / 0,25); gültig X: 0,30–0,70 · Y: 0,00–0,60 · Z: 0,00–0,50; Z-Charakter neutral
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Tonfolge E

#### JC-M014 Blockverschiebungs-Motiv

- **Charakter:** Kurzer Aufschwung; für Halbton-Blocktransposition gedacht.
- **Noten (3):** 1+1Okt @ 0 Ticks, 480 Ticks; 5+1Okt @ 480 Ticks, 480 Ticks; 1+2Okt @ 960 Ticks, 960 Ticks
- **Länge:** 1920 Ticks (0,50 Takte 4/4)
- **Intervalle:** Quinte↑, Quarte↑
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+1Okt=A, 5+1Okt=A, 1+2Okt=A
- **Rollen:** TU GS; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,35 / 0,65 / 0,65); gültig X: 0,00–0,70 · Y: 0,30–1,00 · Z: 0,40–0,90; Z-Charakter mechanisch
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-M015 Wiederholung mit Einzeltonvariation

- **Charakter:** Zweimal dieselbe Figur, nur der letzte Ton fällt zum Leitton.
- **Noten (8):** 1+1Okt @ 0 Ticks, 960 Ticks; ♭3+1Okt @ 960 Ticks, 960 Ticks; 1+1Okt @ 1920 Ticks, 960 Ticks; 2+1Okt @ 2880 Ticks, 960 Ticks; 1+1Okt @ 3840 Ticks, 960 Ticks; ♭3+1Okt @ 4800 Ticks, 960 Ticks; 1+1Okt @ 5760 Ticks, 960 Ticks; 7 @ 6720 Ticks, 960 Ticks
- **Länge:** 7680 Ticks (2,00 Takte 4/4)
- **Intervalle:** kleine Terz↑, kleine Terz↓, große Sekunde↑, große Sekunde↓, kleine Terz↑, kleine Terz↓, kleine Sekunde↓
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+1Okt=A, ♭3+1Okt=A, 1+1Okt=A, 2+1Okt=V, 1+1Okt=A, ♭3+1Okt=A, 1+1Okt=A, 7=U
- **Rollen:** GS TU; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T002 Einzeltonvariation, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,30 / 0,45 / 0,50); gültig X: 0,00–0,60 · Y: 0,20–0,70 · Z: 0,30–0,70; Z-Charakter psychologisch
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-M016 Wanderzelle

- **Charakter:** Für Rollenwanderung konstruiert: klingt in jeder Lage und Rolle gleich erkennbar.
- **Noten (4):** 5+1Okt @ 0 Ticks, 960 Ticks; ♭6+1Okt @ 960 Ticks, 960 Ticks; 5+1Okt @ 1920 Ticks, 960 Ticks; ♭3+1Okt @ 2880 Ticks, 2880 Ticks
- **Länge:** 5760 Ticks (1,50 Takte 4/4)
- **Intervalle:** kleine Sekunde↑, kleine Sekunde↓, große Terz↓
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 5+1Okt=A, ♭6+1Okt=V, 5+1Okt=A, ♭3+1Okt=A
- **Rollen:** HM TU GS; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T006 Rollenwanderung, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,40 / 0,40 / 0,40); gültig X: 0,10–0,70 · Y: 0,10–0,70 · Z: 0,20–0,60; Z-Charakter neutral
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-M017 Achsenmotiv

- **Charakter:** Nur Grundton und Quinte; bleibt über allen H8-Achsen Akkordton.
- **Noten (3):** 5+1Okt @ 0 Ticks, 1920 Ticks; 1+1Okt @ 1920 Ticks, 1920 Ticks; 5+1Okt @ 3840 Ticks, 3840 Ticks
- **Länge:** 7680 Ticks (2,00 Takte 4/4)
- **Intervalle:** Quinte↓, Quinte↑
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 5+1Okt=A, 1+1Okt=A, 5+1Okt=A
- **Rollen:** HM TU; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T008 Harmonische Umfärbung, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,50 / 0,30 / 0,20); gültig X: 0,20–0,80 · Y: 0,00–0,60 · Z: 0,00–0,40; Z-Charakter neutral
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-M018 Glocken-Kanonkopf

- **Charakter:** Kurzer Glockenkopf für Kanon-Einsätze (Fog-„round“-Verfahren).
- **Noten (4):** 1+2Okt @ 0 Ticks, 480 Ticks; 5+1Okt @ 960 Ticks, 480 Ticks; ♭7+1Okt @ 1920 Ticks, 480 Ticks; 5+1Okt @ 2880 Ticks, 480 Ticks
- **Länge:** 3360 Ticks (0,88 Takte 4/4)
- **Intervalle:** Quarte↓, kleine Terz↑, kleine Terz↓
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+2Okt=A, 5+1Okt=A, ♭7+1Okt=T, 5+1Okt=A
- **Rollen:** TU GS; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T006 Rollenwanderung, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,75 / 0,25 / 0,30); gültig X: 0,50–1,00 · Y: 0,00–0,50 · Z: 0,10–0,50; Z-Charakter neutral
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-M019 Hohe Klage

- **Charakter:** Hoch gelegte Terz–None–Grundton-Bewegung.
- **Noten (3):** ♭3+2Okt @ 0 Ticks, 2880 Ticks; 2+2Okt @ 2880 Ticks, 960 Ticks; 1+2Okt @ 3840 Ticks, 3840 Ticks
- **Länge:** 7680 Ticks (2,00 Takte 4/4)
- **Intervalle:** kleine Sekunde↓, große Sekunde↓
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): ♭3+2Okt=A, 2+2Okt=V, 1+2Okt=A
- **Rollen:** HM TU; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **XYZ:** Anker (0,65 / 0,25 / 0,20); gültig X: 0,40–0,90 · Y: 0,00–0,50 · Z: 0,00–0,40; Z-Charakter neutral
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-M020 Tiefes Grollmotiv

- **Charakter:** Tiefer Grundton, Halbton hoch, zurück; drohend.
- **Noten (3):** 1 @ 0 Ticks, 1920 Ticks; ♭2 @ 1920 Ticks, 1920 Ticks; 1 @ 3840 Ticks, 3840 Ticks
- **Länge:** 7680 Ticks (2,00 Takte 4/4)
- **Intervalle:** kleine Sekunde↑, kleine Sekunde↓
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, ♭2=U, 1=A
- **Rollen:** GS; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,15 / 0,50 / 0,70); gültig X: 0,00–0,30 · Y: 0,20–0,80 · Z: 0,50–0,90; Z-Charakter psychologisch
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-M021 Uhrwerk-Signal

- **Charakter:** Drei Ticks, der vierte fällt einen Halbton.
- **Noten (4):** 1+2Okt @ 0 Ticks, 240 Ticks; 1+2Okt @ 480 Ticks, 240 Ticks; 1+2Okt @ 960 Ticks, 240 Ticks; 7+1Okt @ 1440 Ticks, 480 Ticks
- **Länge:** 1920 Ticks (0,50 Takte 4/4)
- **Intervalle:** Prime, Prime, kleine Sekunde↓
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+2Okt=A, 1+2Okt=A, 1+2Okt=A, 7+1Okt=U
- **Rollen:** TU; **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Variation:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,30 / 0,50 / 0,75); gültig X: 0,00–0,60 · Y: 0,20–0,80 · Z: 0,50–1,00; Z-Charakter mechanisch
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Tonfolge E

#### JC-M022 Nachklang-Melodie

- **Charakter:** Langsamer Abstieg nach dem Ereignis; das Fog-Nachklang-Verfahren, eigene Tonfolge.
- **Noten (4):** 1+2Okt @ 0 Ticks, 1920 Ticks; ♭7+1Okt @ 1920 Ticks, 1920 Ticks; ♭6+1Okt @ 3840 Ticks, 1920 Ticks; 5+1Okt @ 5760 Ticks, 5760 Ticks
- **Länge:** 11520 Ticks (3,00 Takte 4/4)
- **Intervalle:** große Sekunde↓, große Sekunde↓, kleine Sekunde↓
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+2Okt=A, ♭7+1Okt=T, ♭6+1Okt=T, 5+1Okt=A
- **Rollen:** HM TU; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T003 Oktavverlagerung, JC-T005 Motivfragmentierung, JC-T008 Harmonische Umfärbung
- **XYZ:** Anker (0,65 / 0,25 / 0,15); gültig X: 0,40–0,90 · Y: 0,00–0,50 · Z: 0,00–0,30; Z-Charakter neutral
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-M023 Zögernde Klavierfigur

- **Charakter:** Drei vereinzelte Töne mit wachsenden Abständen.
- **Noten (3):** 1+1Okt @ 0 Ticks, 480 Ticks; ♭3+1Okt @ 1440 Ticks, 480 Ticks; 5+1Okt @ 3360 Ticks, 480 Ticks
- **Länge:** 3840 Ticks (1,00 Takte 4/4)
- **Intervalle:** kleine Terz↑, große Terz↑
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+1Okt=A, ♭3+1Okt=A, 5+1Okt=A
- **Rollen:** TU; **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Variation:** JC-T003 Oktavverlagerung, JC-T004 Rhythmische Transformation
- **XYZ:** Anker (0,45 / 0,20 / 0,40); gültig X: 0,20–0,70 · Y: 0,00–0,40 · Z: 0,20–0,60; Z-Charakter psychologisch
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-M024 Langsamer Zweiton

- **Charakter:** Terz zur None, je ein Takt.
- **Noten (2):** ♭3+1Okt @ 0 Ticks, 3840 Ticks; 2+1Okt @ 3840 Ticks, 3840 Ticks
- **Länge:** 7680 Ticks (2,00 Takte 4/4)
- **Intervalle:** kleine Sekunde↓
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): ♭3+1Okt=A, 2+1Okt=T
- **Rollen:** HM GS; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **XYZ:** Anker (0,50 / 0,20 / 0,15); gültig X: 0,30–0,70 · Y: 0,00–0,40 · Z: 0,00–0,30; Z-Charakter neutral
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-M025 Dur-Licht-Motiv

- **Charakter:** Durterz, Quinte, große Septime; kaltes Licht.
- **Noten (3):** 3+1Okt @ 0 Ticks, 1920 Ticks; 5+1Okt @ 1920 Ticks, 1920 Ticks; 7+1Okt @ 3840 Ticks, 3840 Ticks
- **Länge:** 7680 Ticks (2,00 Takte 4/4)
- **Intervalle:** kleine Terz↑, große Terz↑
- **Tonfunktionen** (Bezug Durdreiklang, Ionisch (Dur)): 3+1Okt=A, 5+1Okt=A, 7+1Okt=T
- **Rollen:** HM TU; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **XYZ:** Anker (0,85 / 0,25 / 0,15); gültig X: 0,70–1,00 · Y: 0,00–0,50 · Z: 0,00–0,30; Z-Charakter neutral
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Tonfolge E

#### JC-M026 Phrygischer Ruf

- **Charakter:** Grundton zur ♭2; modal.
- **Noten (2):** 1+1Okt @ 0 Ticks, 1440 Ticks; ♭2+1Okt @ 1440 Ticks, 2400 Ticks
- **Länge:** 3840 Ticks (1,00 Takte 4/4)
- **Intervalle:** kleine Sekunde↑
- **Tonfunktionen** (Bezug Molldreiklang, Phrygisch): 1+1Okt=A, ♭2+1Okt=T
- **Rollen:** HM TU; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,20 / 0,30 / 0,50); gültig X: 0,00–0,40 · Y: 0,00–0,60 · Z: 0,30–0,70; Z-Charakter psychologisch
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Tonfolge E

#### JC-M027 Dorischer Aufstieg

- **Charakter:** Bis zur großen Sexte aufsteigend; kühl hoffend.
- **Noten (4):** 1+1Okt @ 0 Ticks, 960 Ticks; 2+1Okt @ 960 Ticks, 960 Ticks; ♭3+1Okt @ 1920 Ticks, 960 Ticks; 6+1Okt @ 2880 Ticks, 2880 Ticks
- **Länge:** 5760 Ticks (1,50 Takte 4/4)
- **Intervalle:** große Sekunde↑, kleine Sekunde↑, Tritonus↑
- **Tonfunktionen** (Bezug Molldreiklang, Dorisch): 1+1Okt=A, 2+1Okt=V, ♭3+1Okt=A, 6+1Okt=T
- **Rollen:** HM; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **XYZ:** Anker (0,70 / 0,30 / 0,20); gültig X: 0,50–0,90 · Y: 0,00–0,60 · Z: 0,00–0,40; Z-Charakter neutral
- **Evidenz:** Verfahren H – Hypothese (markierte Ableitung); Tonfolge E

#### JC-M028 Quintsprung-Signal

- **Charakter:** Kurzer Grundton, lange Quinte.
- **Noten (2):** 1+1Okt @ 0 Ticks, 960 Ticks; 5+1Okt @ 960 Ticks, 2880 Ticks
- **Länge:** 3840 Ticks (1,00 Takte 4/4)
- **Intervalle:** Quinte↑
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+1Okt=A, 5+1Okt=A
- **Rollen:** HM TU GS; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,50 / 0,50 / 0,25); gültig X: 0,00–1,00 · Y: 0,20–0,80 · Z: 0,00–0,50; Z-Charakter neutral
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-M029 Oktavsprung-Signal

- **Charakter:** Schneller Oktavsprung als Signal.
- **Noten (2):** 1+1Okt @ 0 Ticks, 480 Ticks; 1+2Okt @ 480 Ticks, 3360 Ticks
- **Länge:** 3840 Ticks (1,00 Takte 4/4)
- **Intervalle:** Oktave↑
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+1Okt=A, 1+2Okt=A
- **Rollen:** TU HM; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,50 / 0,60 / 0,40); gültig X: 0,00–1,00 · Y: 0,30–0,90 · Z: 0,20–0,60; Z-Charakter neutral
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-M030 Breiter Vierton-Abstieg

- **Charakter:** Weit gespannte absteigende Viertonlinie; das „Evil“-Verfahren als eigene Konstruktion.
- **Noten (4):** 1+2Okt @ 0 Ticks, 1920 Ticks; ♭6+1Okt @ 1920 Ticks, 1920 Ticks; 4+1Okt @ 3840 Ticks, 1920 Ticks; ♭3+1Okt @ 5760 Ticks, 1920 Ticks
- **Länge:** 7680 Ticks (2,00 Takte 4/4)
- **Intervalle:** große Terz↓, kleine Terz↓, große Sekunde↓
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+2Okt=A, ♭6+1Okt=T, 4+1Okt=T, ♭3+1Okt=A
- **Rollen:** HM GS TU; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T006 Rollenwanderung
- **XYZ:** Anker (0,30 / 0,40 / 0,40); gültig X: 0,00–0,60 · Y: 0,10–0,70 · Z: 0,20–0,60; Z-Charakter psychologisch
- **Evidenz:** Verfahren N – nachgewiesenes Verfahren; Tonfolge E

#### JC-M031 Fragmentkern

- **Charakter:** Die ersten zwei Töne des Sechston-Fragments; Material für Fragmentierung.
- **Noten (2):** 1+1Okt @ 0 Ticks, 960 Ticks; ♭3+1Okt @ 960 Ticks, 960 Ticks
- **Länge:** 1920 Ticks (0,50 Takte 4/4)
- **Intervalle:** kleine Terz↑
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+1Okt=A, ♭3+1Okt=A
- **Rollen:** TU GS; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,40 / 0,30 / 0,30); gültig X: 0,10–0,70 · Y: 0,00–0,60 · Z: 0,10–0,50; Z-Charakter neutral
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Tonfolge E

#### JC-M032 Synkopiertes Fragment

- **Charakter:** Vier Töne gegen den Schlag.
- **Noten (4):** 1+1Okt @ 0 Ticks, 720 Ticks; ♭3+1Okt @ 720 Ticks, 1200 Ticks; 5+1Okt @ 1920 Ticks, 720 Ticks; 4+1Okt @ 2640 Ticks, 1200 Ticks
- **Länge:** 3840 Ticks (1,00 Takte 4/4)
- **Intervalle:** kleine Terz↑, große Terz↑, große Sekunde↓
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+1Okt=A, ♭3+1Okt=A, 5+1Okt=A, 4+1Okt=T
- **Rollen:** HM GS; **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Variation:** JC-T001 Blocktransposition, JC-T004 Rhythmische Transformation
- **XYZ:** Anker (0,45 / 0,45 / 0,45); gültig X: 0,20–0,70 · Y: 0,20–0,70 · Z: 0,30–0,60; Z-Charakter neutral
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Tonfolge E

#### JC-M033 Stockendes Fragment

- **Charakter:** Zweimal die Quinte, dann zögernd die ♭6.
- **Noten (3):** 5+1Okt @ 0 Ticks, 480 Ticks; 5+1Okt @ 720 Ticks, 480 Ticks; ♭6+1Okt @ 1920 Ticks, 1440 Ticks
- **Länge:** 3360 Ticks (0,88 Takte 4/4)
- **Intervalle:** Prime, kleine Sekunde↑
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 5+1Okt=A, 5+1Okt=A, ♭6+1Okt=T
- **Rollen:** TU GS; **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Variation:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,30 / 0,35 / 0,60); gültig X: 0,00–0,60 · Y: 0,10–0,60 · Z: 0,40–0,80; Z-Charakter psychologisch
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Tonfolge E

#### JC-M034 Weite Klage

- **Charakter:** Septsprung nach oben, lang gehalten.
- **Noten (2):** 1+1Okt @ 0 Ticks, 1920 Ticks; ♭7+1Okt @ 1920 Ticks, 5760 Ticks
- **Länge:** 7680 Ticks (2,00 Takte 4/4)
- **Intervalle:** kleine Septime↑
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+1Okt=A, ♭7+1Okt=T
- **Rollen:** HM; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **XYZ:** Anker (0,55 / 0,30 / 0,20); gültig X: 0,30–0,80 · Y: 0,00–0,60 · Z: 0,00–0,40; Z-Charakter neutral
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-M035 Tiefe Echo-Antwort

- **Charakter:** Tiefe Antwort auf ein hohes Motiv.
- **Noten (3):** 5 @ 0 Ticks, 1920 Ticks; ♭3 @ 1920 Ticks, 1920 Ticks; 1 @ 3840 Ticks, 3840 Ticks
- **Länge:** 7680 Ticks (2,00 Takte 4/4)
- **Intervalle:** große Terz↓, kleine Terz↓
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 5=A, ♭3=A, 1=A
- **Rollen:** GS; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T003 Oktavverlagerung, JC-T006 Rollenwanderung
- **XYZ:** Anker (0,35 / 0,30 / 0,20); gültig X: 0,10–0,60 · Y: 0,00–0,60 · Z: 0,00–0,40; Z-Charakter neutral
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-M036 Chromatischer Schatten

- **Charakter:** Quinte gleitet chromatisch zur Quarte.
- **Noten (3):** 5+1Okt @ 0 Ticks, 960 Ticks; ♯4/♭5+1Okt @ 960 Ticks, 960 Ticks; 4+1Okt @ 1920 Ticks, 1920 Ticks
- **Länge:** 3840 Ticks (1,00 Takte 4/4)
- **Intervalle:** kleine Sekunde↓, kleine Sekunde↓
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 5+1Okt=A, ♯4/♭5+1Okt=U, 4+1Okt=T
- **Rollen:** GS TU; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,25 / 0,40 / 0,60); gültig X: 0,00–0,50 · Y: 0,10–0,70 · Z: 0,40–0,80; Z-Charakter psychologisch
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-M037 Leittonsuche

- **Charakter:** Leitton, der sich spät und leise auflöst.
- **Noten (2):** 7 @ 0 Ticks, 1920 Ticks; 1+1Okt @ 1920 Ticks, 5760 Ticks
- **Länge:** 7680 Ticks (2,00 Takte 4/4)
- **Intervalle:** kleine Sekunde↑
- **Tonfunktionen** (Bezug Molldreiklang, Harmonisch Moll): 7=T, 1+1Okt=A
- **Rollen:** HM GS; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,40 / 0,30 / 0,40); gültig X: 0,20–0,60 · Y: 0,00–0,60 · Z: 0,20–0,60; Z-Charakter psychologisch
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-M038 Melancholie in Halben

- **Charakter:** Vier Halbe; ruhige, offene Linie.
- **Noten (4):** 5+1Okt @ 0 Ticks, 1920 Ticks; ♭3+1Okt @ 1920 Ticks, 1920 Ticks; 4+1Okt @ 3840 Ticks, 1920 Ticks; 2+1Okt @ 5760 Ticks, 1920 Ticks
- **Länge:** 7680 Ticks (2,00 Takte 4/4)
- **Intervalle:** große Terz↓, große Sekunde↑, kleine Terz↓
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 5+1Okt=A, ♭3+1Okt=A, 4+1Okt=T, 2+1Okt=T
- **Rollen:** HM GS; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **XYZ:** Anker (0,50 / 0,25 / 0,15); gültig X: 0,30–0,70 · Y: 0,00–0,50 · Z: 0,00–0,30; Z-Charakter neutral
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-M039 Hoher Ton mit Nachschlag

- **Charakter:** Ein sehr hoher Ton, ein leiser Nachhall-Ton.
- **Noten (2):** 5+2Okt @ 0 Ticks, 2880 Ticks; 5+2Okt @ 3360 Ticks, 480 Ticks, v55
- **Länge:** 3840 Ticks (1,00 Takte 4/4)
- **Intervalle:** Prime
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 5+2Okt=A, 5+2Okt=A
- **Rollen:** TU; **Identität:** Erhalten: Einsatzpositionen und Akzente. Variabel: Tonhöhen (einzeln oder paarweise), Oktave.
- **Variation:** JC-T003 Oktavverlagerung, JC-T004 Rhythmische Transformation
- **XYZ:** Anker (0,75 / 0,20 / 0,40); gültig X: 0,50–1,00 · Y: 0,00–0,40 · Z: 0,20–0,60; Z-Charakter psychologisch
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Tonfolge E

#### JC-M040 Drei Glocken

- **Charakter:** Grundton, Quinte, Oktave aufsteigend; hell, kalt.
- **Noten (3):** 1+2Okt @ 0 Ticks, 960 Ticks; 5+2Okt @ 960 Ticks, 960 Ticks; 1+3Okt @ 1920 Ticks, 1920 Ticks
- **Länge:** 3840 Ticks (1,00 Takte 4/4)
- **Intervalle:** Quinte↑, Quarte↑
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+2Okt=A, 5+2Okt=A, 1+3Okt=A
- **Rollen:** TU; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T003 Oktavverlagerung, JC-T006 Rollenwanderung
- **XYZ:** Anker (0,80 / 0,25 / 0,20); gültig X: 0,60–1,00 · Y: 0,00–0,50 · Z: 0,00–0,40; Z-Charakter neutral
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Tonfolge E

#### JC-M041 Offene Frage

- **Charakter:** Aufsteigend, endet auf der Quinte; keine Antwort.
- **Noten (4):** 1+1Okt @ 0 Ticks, 960 Ticks; 2+1Okt @ 960 Ticks, 960 Ticks; ♭3+1Okt @ 1920 Ticks, 960 Ticks; 5+1Okt @ 2880 Ticks, 4800 Ticks
- **Länge:** 7680 Ticks (2,00 Takte 4/4)
- **Intervalle:** große Sekunde↑, kleine Sekunde↑, große Terz↑
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+1Okt=A, 2+1Okt=V, ♭3+1Okt=A, 5+1Okt=A
- **Rollen:** HM GS; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T005 Motivfragmentierung, JC-T008 Harmonische Umfärbung
- **XYZ:** Anker (0,50 / 0,30 / 0,30); gültig X: 0,30–0,70 · Y: 0,00–0,60 · Z: 0,10–0,50; Z-Charakter neutral
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-M042 Kreisen um die Quinte

- **Charakter:** Quinte von oben und unten umspielt.
- **Noten (4):** 5+1Okt @ 0 Ticks, 960 Ticks; ♭6+1Okt @ 960 Ticks, 960 Ticks; 5+1Okt @ 1920 Ticks, 960 Ticks; 4+1Okt @ 2880 Ticks, 960 Ticks
- **Länge:** 3840 Ticks (1,00 Takte 4/4)
- **Intervalle:** kleine Sekunde↑, kleine Sekunde↓, große Sekunde↓
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 5+1Okt=A, ♭6+1Okt=V, 5+1Okt=A, 4+1Okt=T
- **Rollen:** GS TU; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T006 Rollenwanderung
- **XYZ:** Anker (0,30 / 0,40 / 0,50); gültig X: 0,00–0,60 · Y: 0,10–0,70 · Z: 0,30–0,70; Z-Charakter psychologisch
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-M043 Langer Choralton

- **Charakter:** Ein Ton über zwei Takte; Kraft durch Dauer.
- **Noten (1):** 1+1Okt @ 0 Ticks, 7680 Ticks
- **Länge:** 7680 Ticks (2,00 Takte 4/4)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+1Okt=A
- **Rollen:** HM; **Identität:** Erhalten: Tonhöhe(n). Variabel: Rhythmus, Gate, Akzente, Dichte.
- **Variation:** JC-T003 Oktavverlagerung, JC-T006 Rollenwanderung
- **XYZ:** Anker (0,50 / 0,70 / 0,15); gültig X: 0,00–1,00 · Y: 0,40–1,00 · Z: 0,00–0,30; Z-Charakter neutral
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-M044 Zweiton-Stoß

- **Charakter:** Harter Halbton-Stoß; für akuten Horror, harmonisch statt Effekt.
- **Noten (2):** 1+2Okt @ 0 Ticks, 240 Ticks, v120; ♭2+2Okt @ 240 Ticks, 720 Ticks, v120
- **Länge:** 960 Ticks (0,25 Takte 4/4)
- **Intervalle:** kleine Sekunde↑
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+2Okt=A, ♭2+2Okt=U
- **Rollen:** TU; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,20 / 0,85 / 0,85); gültig X: 0,00–0,40 · Y: 0,70–1,00 · Z: 0,70–1,00; Z-Charakter psychologisch
- **Evidenz:** Verfahren I – begründete Interpretation; Tonfolge E

#### JC-M045 Rückkehr nach Pause

- **Charakter:** Ein Zweiton, eineinhalb Takte Stille, identische Wiederkehr.
- **Noten (4):** 5+1Okt @ 0 Ticks, 960 Ticks; ♭3+1Okt @ 960 Ticks, 2880 Ticks; 5+1Okt @ 7680 Ticks, 960 Ticks; ♭3+1Okt @ 8640 Ticks, 2880 Ticks
- **Länge:** 11520 Ticks (3,00 Takte 4/4)
- **Intervalle:** große Terz↓, große Terz↑, große Terz↓
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 5+1Okt=A, ♭3+1Okt=A, 5+1Okt=A, ♭3+1Okt=A
- **Rollen:** TU GS; **Identität:** Erhalten: Intervallfolge und Rhythmus. Variabel: Transpositionsstufe, Oktave, Rolle, Gate, Unterbau.
- **Variation:** JC-T011 Unterbrechung und Wiederaufnahme, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,45 / 0,25 / 0,30); gültig X: 0,20–0,70 · Y: 0,00–0,50 · Z: 0,10–0,50; Z-Charakter neutral
- **Evidenz:** Verfahren E – eigenständige Gestaltung; Tonfolge E

## 8. P – Phrasen

#### JC-P001 Wiederaufnahme nach Atemloch

- **Zweck:** Eine Figur pausiert und kehrt unverändert zurück.
- **Bauplan:**
  - T1–12: Figur läuft (z. B. JC-Q011).
  - T13–16: Pause der Figur, Fläche hält.
  - T17: identische Wiederaufnahme am Zyklusanfang.
- **Vorlagen:** JC-Q011, JC-T011
- **XYZ:** X: 0,00–1,00 · Y: 0,20–0,80 · Z: 0,20–0,60; **Evidenz:** N – nachgewiesenes Verfahren

#### JC-P002 Fragmentierung eines Motivs

- **Zweck:** Ein Motiv wird schrittweise auf seinen Kern reduziert.
- **Bauplan:**
  - T1–2: ganzes Motiv (JC-M011).
  - T9–10: erste Hälfte.
  - T17: nur Fragmentkern (JC-M031).
  - T25: ein einzelner Ton des Kerns.
- **Vorlagen:** JC-M011, JC-M031, JC-T005
- **XYZ:** X: 0,20–0,70 · Y: 0,00–0,60 · Z: 0,20–0,60; **Evidenz:** I – begründete Interpretation

#### JC-P003 Verlängerung durch Haltedauer

- **Zweck:** Ein Motiv wird durch Dehnung seines letzten Tons verlängert, nicht durch neue Töne.
- **Bauplan:**
  - Motiv erklingt normal.
  - Bei Wiederholung wird der Schlusston auf 2–4 Takte gedehnt.
  - Darunter bleibt die Fläche unverändert.
- **Vorlagen:** JC-M003, JC-M022
- **XYZ:** X: 0,20–0,80 · Y: 0,00–0,50 · Z: 0,00–0,40; **Evidenz:** I – begründete Interpretation

#### JC-P004 Verkürzung durch Abbruch

- **Zweck:** Ein Motiv bricht vor seinem Ende ab; die Lücke wird nicht gefüllt.
- **Bauplan:**
  - Erste Fassung: vollständig.
  - Zweite Fassung: die letzten zwei Töne fehlen.
  - Dritte Fassung: nur der erste Ton, dann Stille.
- **Vorlagen:** JC-M012, JC-T005
- **XYZ:** X: 0,20–0,70 · Y: 0,00–0,60 · Z: 0,30–0,70; **Evidenz:** E – eigenständige Gestaltung

#### JC-P005 Wiederkehr nach langer Pause

- **Zweck:** Ein Motiv kehrt nach 12–24 Takten Stille unverändert zurück.
- **Bauplan:**
  - Motiv einmal.
  - 12–24 Takte nur Fläche (Ereignisfeld ohne Ereignis).
  - Identische Wiederkehr, gleiche Lage.
- **Vorlagen:** JC-M045, JC-EF10
- **XYZ:** X: 0,00–1,00 · Y: 0,00–0,40 · Z: 0,00–0,50; **Evidenz:** N – nachgewiesenes Verfahren

#### JC-P006 Melodische Umfärbung

- **Zweck:** Ein Motiv erklingt zweimal über verschiedenen Klängen.
- **Bauplan:**
  - T1–4: Motiv über Moll (H017).
  - T5–8: dasselbe Motiv über ♭VI (H051 zweiter Klang).
  - Tonfunktionen ändern sich, die Tonhöhen nicht.
- **Vorlagen:** JC-M017, JC-H051, JC-T008
- **XYZ:** X: 0,20–0,80 · Y: 0,00–0,60 · Z: 0,10–0,50; **Evidenz:** N – nachgewiesenes Verfahren

#### JC-P007 Rollenwechsel HM → TU → GS

- **Zweck:** Ein Motiv wandert durch drei Rollen.
- **Bauplan:**
  - T1: HM.
  - T9: TU eine Oktave höher.
  - T17: GS eine Oktave tiefer.
  - T25: HM, identisch mit T1.
- **Vorlagen:** JC-M016, JC-T006
- **XYZ:** X: 0,10–0,70 · Y: 0,10–0,70 · Z: 0,20–0,60; **Evidenz:** N – nachgewiesenes Verfahren

#### JC-P008 Lyrische elektronische Entwicklung

- **Zweck:** Eine längere Linie wird in drei Stufen entfaltet.
- **Bauplan:**
  - Stufe 1: Fragmentkern über Drone.
  - Stufe 2: Sechston-Fragment.
  - Stufe 3: lyrische Linie (JC-M012) über Melancholie-Kreis.
  - Zurück zu Stufe 1, nicht gesteigert.
- **Vorlagen:** JC-M031, JC-M011, JC-M012, JC-H077
- **XYZ:** X: 0,30–0,80 · Y: 0,00–0,60 · Z: 0,00–0,40; **Evidenz:** I – begründete Interpretation

#### JC-P009 Gleichbleibende Spannung durch Rotation

- **Zweck:** Kontrollierte Veränderung bei konstanter Dichte.
- **Bauplan:**
  - Schichtpool KB, AR, GS; immer zwei aktiv.
  - Wechsel alle 16 Takte, gekoppelt (eine raus, eine rein).
  - Harmonie konstant.
- **Vorlagen:** JC-T007, JC-S35
- **XYZ:** X: 0,00–1,00 · Y: 0,30–0,80 · Z: 0,20–0,60; **Evidenz:** N – nachgewiesenes Verfahren

#### JC-P010 Frage ohne Antwort

- **Zweck:** Eine Frage wird mehrfach gestellt; die Antwort bleibt aus.
- **Bauplan:**
  - Frage (JC-M041) alle 8 Takte.
  - Zwischen den Fragen nur Fläche.
  - Keine Antwortphrase.
- **Vorlagen:** JC-M041
- **XYZ:** X: 0,30–0,70 · Y: 0,00–0,50 · Z: 0,20–0,60; **Evidenz:** E – eigenständige Gestaltung

#### JC-P011 Echo-Antwort aus der Tiefe

- **Zweck:** Ein hohes Motiv wird tief beantwortet.
- **Bauplan:**
  - Hoch: JC-M019 in TU.
  - Zwei Takte später: JC-M035 in GS.
  - Keine Überlappung; Mittellage frei.
- **Vorlagen:** JC-M019, JC-M035
- **XYZ:** X: 0,20–0,70 · Y: 0,00–0,60 · Z: 0,10–0,50; **Evidenz:** I – begründete Interpretation

#### JC-P012 Blockverschiebung als Phrase

- **Zweck:** Die Fläche rückt einen Halbton und kehrt zurück.
- **Bauplan:**
  - T1–8: Grundstufe.
  - T9–12: +1 Halbton.
  - T13–16: Grundstufe.
  - Wiederholung ohne Steigerung.
- **Vorlagen:** JC-T001, JC-H015
- **XYZ:** X: 0,00–0,50 · Y: 0,30–1,00 · Z: 0,40–0,90; **Evidenz:** N – nachgewiesenes Verfahren

#### JC-P013 Kanoneinsatz

- **Zweck:** Ein Glockenkopf wird versetzt imitiert.
- **Bauplan:**
  - TU: JC-M018 auf Zählzeit 1.
  - GS: dasselbe eine Oktave tiefer, zwei Viertel später.
  - Wiederholung alle 2 Takte.
- **Vorlagen:** JC-M018, JC-S13
- **XYZ:** X: 0,50–1,00 · Y: 0,00–0,50 · Z: 0,10–0,50; **Evidenz:** N – nachgewiesenes Verfahren

#### JC-P014 Nachklang nach dem Ereignis

- **Zweck:** Nach einem Stinger folgt eine langsame Trauerlinie.
- **Bauplan:**
  - ST auf Takt t.
  - t bis t+2: nur Drone.
  - t+3: JC-M022 in HM oder TU.
  - Danach wieder Ereignisfeld.
- **Vorlagen:** JC-M022, JC-EF01
- **XYZ:** X: 0,30–0,90 · Y: 0,00–0,50 · Z: 0,00–0,40; **Evidenz:** N – nachgewiesenes Verfahren

#### JC-P015 Verdichtungsleiter mit Rückfall

- **Zweck:** Dichte steigt in vier Stufen und fällt schlagartig zurück.
- **Bauplan:**
  - T1–4: R007-Puls.
  - T5–8: R002.
  - T9–12: R003.
  - T13: Reduktion auf Drone.
- **Vorlagen:** JC-R007, JC-R002, JC-R003, JC-T013, JC-T014
- **XYZ:** X: 0,00–0,60 · Y: 0,30–1,00 · Z: 0,40–1,00; **Evidenz:** N – nachgewiesenes Verfahren

#### JC-P016 Ruhige Antwort auf Unruhe

- **Zweck:** Eine unruhige Figur endet in einem Halteton.
- **Bauplan:**
  - T1–6: JC-Q007 Halbton-Wiege.
  - T7–8: nur ein Halteton (JC-M043).
  - Wiederholung.
- **Vorlagen:** JC-Q007, JC-M043
- **XYZ:** X: 0,00–0,50 · Y: 0,20–0,80 · Z: 0,40–0,90; **Evidenz:** E – eigenständige Gestaltung

## 9. T – Transformationsverfahren

#### JC-T001 Blocktransposition

- **Zweck:** Verschiebt eine ganze Figur oder Fläche um ein festes Intervall, ohne ihre Intervalle zu ändern.
- **Algorithmus:**
  1. Wähle Schicht(en) und Intervall d (Standard ±1 Halbton, zulässig ±2, ±5, ±7).
  2. Addiere d zu allen Tonhöhen ab Takt t bis Takt t+L.
  3. Gehört die Fläche dazu (LF/LB), entsteht eine Blockverschiebung des ganzen Feldes; bleibt der Bass stehen, entsteht eine autorisierte Reibung (Tonfunktion U).
  4. Rückkehr nach L Takten optional; keine automatische Rückkehr erzwingen.
- **Parameter:** d, t, L, betroffene Rollen; **Invarianten:** Intervallfolge, Rhythmus, Akzente
- **Evidenz:** N – nachgewiesenes Verfahren; **in Studien:** JC-S18, JC-S22, JC-S40

#### JC-T002 Einzeltonvariation

- **Zweck:** Ersetzt genau einen Ton einer Figur, alle anderen bleiben gleich.
- **Algorithmus:**
  1. Wähle Position p in der Figur (nicht den ersten Ton der Akzentgruppe).
  2. Ersetze die Tonhöhe durch einen Nachbarton (±1 oder ±2 Halbtöne) oder den nächsten Akkordton.
  3. Prüfe die Tonfunktion gegen den klingenden Kontext; ein neuer F/U-Ton braucht eine Autorisierung.
  4. Variation gilt für ganze Zyklen, nicht für einzelne zufällige Wiederholungen.
- **Parameter:** p, Ersatzton, Gültigkeitsdauer; **Invarianten:** Rhythmus, Akzentmuster, übrige Töne
- **Evidenz:** I – begründete Interpretation; **in Studien:** nur dokumentiert

#### JC-T003 Oktavverlagerung

- **Zweck:** Verlegt eine Figur oder ein Motiv um ±12 oder ±24 Halbtöne.
- **Algorithmus:**
  1. Addiere 12·k zu allen Tönen der Schicht.
  2. Prüfe Rollenumfang (Registertabelle).
  3. Bei Bass: keine Verlagerung über die Mittellage, damit Platz für Sprache bleibt.
- **Parameter:** k, Rolle; **Invarianten:** Alle Intervalle, Rhythmus
- **Evidenz:** N – nachgewiesenes Verfahren; **in Studien:** JC-S07

#### JC-T004 Rhythmische Transformation

- **Zweck:** Ändert das Raster einer Figur (Augmentation, Diminution, Wechsel gerade/triolisch).
- **Algorithmus:**
  1. Augmentation: Rasterwert verdoppeln (Achtel → Viertel).
  2. Diminution: Rasterwert halbieren.
  3. Triolisierung: Raster 8 → 8t bei gleicher Tonfolge.
  4. Tonfolge und Akzentpositionen relativ zur Figur bleiben erhalten.
- **Parameter:** Faktor oder Zielraster; **Invarianten:** Tonfolge, relative Akzente
- **Evidenz:** I – begründete Interpretation; **in Studien:** nur dokumentiert

#### JC-T005 Motivfragmentierung

- **Zweck:** Verwendet nur einen Teil eines Motivs.
- **Algorithmus:**
  1. Wähle zusammenhängende Teilmenge (Kopf, Mitte oder Schluss), mindestens zwei Töne.
  2. Behalte die Originaldauern.
  3. Fragment darf allein, wiederholt oder mit Pause erscheinen.
- **Parameter:** Start, Länge; **Invarianten:** Intervalle und Dauern des Fragments
- **Evidenz:** I – begründete Interpretation; **in Studien:** nur dokumentiert

#### JC-T006 Rollenwanderung

- **Zweck:** Ein Motiv wechselt die Rolle (HM → TU → GS) bei gleicher Tonfolge.
- **Algorithmus:**
  1. Wähle Zielrolle und Oktavlage.
  2. Übertrage Tonfolge und Dauern unverändert.
  3. Die bisherige Rolle pausiert während der Wanderung.
  4. Harmonie bleibt gleich (sonst ist es Umfärbung).
- **Parameter:** Zielrolle, Oktave, Takt; **Invarianten:** Tonfolge, Rhythmus
- **Evidenz:** N – nachgewiesenes Verfahren; **in Studien:** JC-S09, JC-S11, JC-S13, JC-S27, JC-S31

#### JC-T007 Schichtrotation

- **Zweck:** Tauscht aktive Schichten, ohne die Gesamtdichte zu verändern.
- **Algorithmus:**
  1. Definiere Schichtenpool und Zahl gleichzeitig aktiver Schichten n.
  2. An einem Wechselpunkt verlässt eine Schicht, eine andere tritt ein (gekoppelter Wechsel).
  3. Wechselpunkte an Phrasengrenzen (8, 16, 32 Takte), nicht in festen kurzen Abständen.
- **Parameter:** Pool, n, Wechselpunkte; **Invarianten:** Gesamtdichte, Harmonie
- **Evidenz:** N – nachgewiesenes Verfahren; **in Studien:** JC-S07, JC-S19, JC-S21, JC-S35

#### JC-T008 Harmonische Umfärbung

- **Zweck:** Unter einer unveränderten Figur wechselt der harmonische Unterbau.
- **Algorithmus:**
  1. Wähle eine H8-Achse oder eine Folge, deren Klänge möglichst viele Figurtöne enthalten.
  2. Berechne für jeden Figurton die Tonfunktion im neuen Kontext.
  3. Neue F-Töne nur, wenn die Umfärbung sie ausdrücklich will.
- **Parameter:** Ziel-Harmonie, Takt; **Invarianten:** Figur (Tonhöhen, Rhythmus)
- **Evidenz:** N – nachgewiesenes Verfahren; **in Studien:** JC-S09, JC-S10, JC-S12, JC-S24, JC-S27, JC-S29, JC-S34

#### JC-T009 Gate-Veränderung

- **Zweck:** Ändert nur die Tondauern bei gleichen Einsätzen.
- **Algorithmus:**
  1. Setze Gate-Faktor g (0,1–0,98) oder Gate-Kurve über mehrere Takte.
  2. Einsätze und Tonhöhen bleiben.
  3. Keine Verwendung zur Simulation von Hüllkurven- oder Filterbewegung.
- **Parameter:** g oder Kurve; **Invarianten:** Einsätze, Tonfolge
- **Evidenz:** I – begründete Interpretation; **in Studien:** nur dokumentiert

#### JC-T010 Akzentgruppen-Variation

- **Zweck:** Ändert die Betonungsgruppierung bei gleicher Notendichte.
- **Algorithmus:**
  1. Ersetze Akzentmuster (z. B. 4×2 → 3+3+2) durch Velocity-Umverteilung.
  2. Notendichte und Tonhöhen bleiben.
  3. Ungerade Gruppierungen sind Option, kein Standard.
- **Parameter:** Gruppierung; **Invarianten:** Einsätze, Tonfolge
- **Evidenz:** N – nachgewiesenes Verfahren; **in Studien:** JC-S22, JC-S37

#### JC-T011 Unterbrechung und Wiederaufnahme

- **Zweck:** Setzt eine Schicht für eine Strecke aus und lässt sie identisch zurückkehren.
- **Algorithmus:**
  1. Definiere Pausenstrecke (1–8 Takte).
  2. Bei Rückkehr: gleiche Phase (Neustart am Zyklusanfang) oder durchlaufende Phase (als ob sie weitergelaufen wäre).
  3. Keine Veränderung der Figur bei Rückkehr.
- **Parameter:** Pausenlänge, Phasenmodus; **Invarianten:** Figur
- **Evidenz:** N – nachgewiesenes Verfahren; **in Studien:** JC-S05, JC-S19, JC-S36

#### JC-T012 Langfristige Stasis

- **Zweck:** Hält alle Parameter über lange Zeit konstant.
- **Algorithmus:**
  1. Keine Transformation aktiv.
  2. Optional nur Velocity-Mikrovariation (±6) zur Belebung, keine Tonhöhenänderung.
  3. Gilt als vollwertiges Ergebnis, nicht als Fehlerzustand.
- **Parameter:** Dauer; **Invarianten:** Alles
- **Evidenz:** N – nachgewiesenes Verfahren; **in Studien:** JC-S01, JC-S02, JC-S03, JC-S04, JC-S06, JC-S08, JC-S14, JC-S15, JC-S20, JC-S25, JC-S26, JC-S28, JC-S30, JC-S32, JC-S33, JC-S39, JC-S41, JC-S42, JC-EF01, JC-EF02, JC-EF03, JC-EF04, JC-EF05, JC-EF06, JC-EF07, JC-EF08, JC-EF09, JC-EF10, JC-EF11, JC-EF12

#### JC-T013 Kontrollierte Verdichtung

- **Zweck:** Erhöht die Ereignisdichte schrittweise.
- **Algorithmus:**
  1. Füge Schichten in definierter Reihenfolge hinzu oder schalte auf dichteres Raster (z. B. R007 → R002).
  2. Je Schritt nur eine Änderung.
  3. Nur bei tatsächlicher XYZ-Veränderung (Y oder Z steigt) oder in ausdrücklich gerichteten Studien.
- **Parameter:** Reihenfolge, Schrittweite; **Invarianten:** Harmonie, Figuren
- **Evidenz:** N – nachgewiesenes Verfahren; **in Studien:** JC-S16, JC-S18

#### JC-T014 Kontrollierte Reduktion

- **Zweck:** Verringert die Dichte schrittweise oder schlagartig.
- **Algorithmus:**
  1. Entferne Schichten in umgekehrter Reihenfolge oder alle auf einmal (Horror durch Reduktion).
  2. Der zuletzt verbleibende Ton ist meist der Drone oder ein einzelner hoher Ton.
- **Parameter:** Reihenfolge, Ziel-Rest; **Invarianten:** Harmonie
- **Evidenz:** N – nachgewiesenes Verfahren; **in Studien:** JC-S17, JC-S23, JC-S36

#### JC-T015 Phasenversatz

- **Zweck:** Lässt eine Figur mit eigener Periode gegen den Takt laufen.
- **Algorithmus:**
  1. Tonhöhenzyklus der Länge n über Rhythmus mit m Einsätzen, n teilt m nicht.
  2. Gemeinsame SYNTH-Fähigkeit; im Carpenter-Profil nur als gekennzeichnete Hypothese.
- **Parameter:** n, m; **Invarianten:** Tonfolge, Raster
- **Evidenz:** H – Hypothese (markierte Ableitung); **in Studien:** JC-S38

#### JC-T016 Velocity-Atmung

- **Zweck:** Formt lange Abschnitte nur über die Anschlagsdynamik.
- **Algorithmus:**
  1. Velocity-Kurve über 8–32 Takte (z. B. 60 → 85 → 60).
  2. Wirkt nur bei neu angeschlagenen Noten; gehaltene Drones bleiben unverändert.
  3. Keine CC-Steuerung vorausgesetzt.
- **Parameter:** Kurve, Länge; **Invarianten:** Tonhöhen, Rhythmus
- **Evidenz:** E – eigenständige Gestaltung; **in Studien:** nur dokumentiert

## 10. EF – Ereignisfelder (pulslose Atmosphären)

Ereignisfelder hängen weder von einem Arpeggio noch von einem durchlaufenden Basspuls ab. Die Ereignisabstände folgen einer **deterministischen Abstandsreihe** (kein Zufall); Kandidaten rotieren in fester Reihenfolge. Längere Abschnitte ohne neues Ereignis sind ausdrücklich zulässig.

#### JC-EF01 Tiefer Grund, ferne Glocke

- **Charakter:** Oktavsäule; drei verschiedene hohe Ereignisse in großen, unregelmäßigen Abständen.
- **XYZ-Anker:** (0,50 / 0,10 / 0,20); Tonart E, Äolisch (natürliches Moll), 64 Takte, 60 BPM (Vorschlag)
- **Harmonisches Grundfeld:** ab T1 JC-H002 Oktavsäule
- **Haltedauer:** Klang über die gesamte Dauer bzw. bis zum nächsten Klangwechsel; keine Neuanschläge außer Klangwechsel
- **Pedal/Bass:** Grundton durchgehend  – LB: JC-B001 Tiefer Grundton-Drone
- **Zulässige Einzelereignisse:** TU-Ereignisfeld: Kandidaten JC-M001 Einsamer hoher Ruf, JC-M018 Glocken-Kanonkopf, JC-M039 Hoher Ton mit Nachschlag; Abstände 7-5-9 Takte; Start T5
- **Ereignisabstände / Mindestabstand:** 7-5-9 Takte, zyklisch; mindestens 4 Takte
- **Register:** LB tief, TU hoch, Mitte leer
- **Dissonanzabsicht:** keine; rein konsonant
- **Langfristig bei konstanter XYZ-Position:** Ereignisse rotieren, die Abstandsreihe bleibt; keine Verdichtung.
- **MIDI:** `JC-EF01_Tiefer_Grund_ferne_Glocke.mid` · Spuren LF, LB, TU

#### JC-EF02 Reibungsfeld ♭2

- **Charakter:** Quinte mit ♭2; hohe ♭2-Töne und der Halbtonfall-Ruf, selten ein Stich.
- **XYZ-Anker:** (0,10 / 0,20 / 0,60); Tonart A, Phrygisch, 64 Takte, 56 BPM (Vorschlag)
- **Harmonisches Grundfeld:** ab T1 JC-H009 Quinte mit ♭2
- **Haltedauer:** Klang über die gesamte Dauer bzw. bis zum nächsten Klangwechsel; keine Neuanschläge außer Klangwechsel
- **Pedal/Bass:** Grundton  – LB: JC-B001 Tiefer Grundton-Drone
- **Zulässige Einzelereignisse:** TU-Ereignisfeld: Kandidaten N:25:12:U, JC-M002 Ruf mit Halbtonfall, N:13:8:U, ST; Abstände 6-9-4-11 Takte; Start T4
- **Ereignisabstände / Mindestabstand:** 6-9-4-11; mindestens 4 Takte
- **Register:** TU hoch, Feldtöne über C5
- **Dissonanzabsicht:** ♭2 ausdrücklich U, nie aufgelöst
- **Langfristig bei konstanter XYZ-Position:** Feldtöne und Stich wechseln; Reibungsdichte bleibt konstant.
- **MIDI:** `JC-EF02_Reibungsfeld_b2.mid` · Spuren LF, LB, TU, ST

#### JC-EF03 Paranoia-Feld

- **Charakter:** Quinte mit ♭6-Nachbar; stockende und chromatische Fragmente, ein Stich je Zyklus.
- **XYZ-Anker:** (0,10 / 0,30 / 0,85); Tonart D, Äolisch (natürliches Moll), 48 Takte, 62 BPM (Vorschlag)
- **Harmonisches Grundfeld:** ab T1 JC-H010 Quinte mit ♭6-Nachbar
- **Haltedauer:** Klang über die gesamte Dauer bzw. bis zum nächsten Klangwechsel; keine Neuanschläge außer Klangwechsel
- **Pedal/Bass:** Pedal  – LB: JC-B005 Unabhängiges Pedal
- **Zulässige Einzelereignisse:** GS-Ereignisfeld: Kandidaten JC-M033 Stockendes Fragment, JC-M036 Chromatischer Schatten, ST; Abstände 5-3-7 Takte; Start T3
- **Ereignisabstände / Mindestabstand:** 5-3-7; mindestens 3 Takte
- **Register:** GS Mittellage oberhalb C4
- **Dissonanzabsicht:** ♭6 als F, ♯4 (chromatischer Schatten) als U
- **Langfristig bei konstanter XYZ-Position:** Die Abstandsreihe ist kurz; Unruhe durch Unregelmäßigkeit, nicht Dichte.
- **MIDI:** `JC-EF03_Paranoia_Feld.mid` · Spuren LF, LB, ST, GS

#### JC-EF04 Kaltes Licht

- **Charakter:** Glasiges Dur add9 ohne Bass; Drei Glocken und Quintsprung-Signale.
- **XYZ-Anker:** (0,90 / 0,10 / 0,15); Tonart G, Ionisch (Dur), 48 Takte, 66 BPM (Vorschlag)
- **Harmonisches Grundfeld:** ab T1 JC-H073 Glasiges Dur add9
- **Haltedauer:** Klang über die gesamte Dauer bzw. bis zum nächsten Klangwechsel; keine Neuanschläge außer Klangwechsel
- **Pedal/Bass:** kein Bass (bewusster Bassverzicht)
- **Zulässige Einzelereignisse:** TU-Ereignisfeld: Kandidaten JC-M040 Drei Glocken, JC-M028 Quintsprung-Signal; Abstände 8-6 Takte; Start T3
- **Ereignisabstände / Mindestabstand:** 8-6; mindestens 6 Takte
- **Register:** alles über C4
- **Dissonanzabsicht:** keine
- **Langfristig bei konstanter XYZ-Position:** Ereignisse wechseln; Klangfeld unverändert. Hell, nicht fröhlich: kein Bass, hohe Lage.
- **MIDI:** `JC-EF04_Kaltes_Licht.mid` · Spuren LF, TU

#### JC-EF05 Melancholisches Feld

- **Charakter:** Langsamer Zweiklang-Kreis; seltene lange Zweitöne und zögernde Figuren.
- **XYZ-Anker:** (0,50 / 0,20 / 0,20); Tonart A, Äolisch (natürliches Moll), 64 Takte, 70 BPM (Vorschlag)
- **Harmonisches Grundfeld:** ab T1 JC-H028 Langsamer Zweiklang-Kreis
- **Haltedauer:** Klang über die gesamte Dauer bzw. bis zum nächsten Klangwechsel; keine Neuanschläge außer Klangwechsel
- **Pedal/Bass:** Akkordgrundton – LB aus Harmonie
- **Zulässige Einzelereignisse:** HM-Ereignisfeld: Kandidaten JC-M024 Langsamer Zweiton, JC-M006 Melancholische Zelle; Abstände 8-8-6-10 Takte; Start T5; TU-Ereignisfeld: Kandidaten JC-M023 Zögernde Klavierfigur; Abstände 16 Takte; Start T13
- **Ereignisabstände / Mindestabstand:** 8-8-6-10 / 16; mindestens 6 Takte
- **Register:** HM um C4–C5
- **Dissonanzabsicht:** Durchgänge (V) nur innerhalb der Motive
- **Langfristig bei konstanter XYZ-Position:** Akkordwechsel alle 8 Takte sind die einzige regelmäßige Bewegung.
- **MIDI:** `JC-EF05_Melancholisches_Feld.mid` · Spuren LF, LB, TU, HM

#### JC-EF06 Herzschlag im Nebel

- **Charakter:** Leere Quinte, langsamer Herzschlag, gelegentliche hohe Töne.
- **XYZ-Anker:** (0,30 / 0,30 / 0,40); Tonart E, Äolisch (natürliches Moll), 48 Takte, 64 BPM (Vorschlag)
- **Harmonisches Grundfeld:** ab T1 JC-H001 Kalte Quintleere
- **Haltedauer:** Klang über die gesamte Dauer bzw. bis zum nächsten Klangwechsel; keine Neuanschläge außer Klangwechsel
- **Pedal/Bass:** Herzschlag  statt Drone – KB: JC-B014 Langsamer Herzschlag-Bass
- **Zulässige Einzelereignisse:** TU-Ereignisfeld: Kandidaten N:19:16, N:24:8, JC-M003 Oktave sinkt zur Quinte; Abstände 9-7 Takte; Start T6
- **Ereignisabstände / Mindestabstand:** 9-7; mindestens 6 Takte
- **Register:** TU über C5
- **Dissonanzabsicht:** keine
- **Langfristig bei konstanter XYZ-Position:** Herzschlag konstant; Ereignisse rotieren.
- **MIDI:** `JC-EF06_Herzschlag_im_Nebel.mid` · Spuren LF, KB, TU

#### JC-EF07 Grollen

- **Charakter:** Lokrische Leere; tiefes Grollmotiv in der Gegenstimme, selten.
- **XYZ-Anker:** (0,10 / 0,40 / 0,60); Tonart D, Lokrisch, 48 Takte, 58 BPM (Vorschlag)
- **Harmonisches Grundfeld:** ab T1 JC-H079 Lokrische Leere
- **Haltedauer:** Klang über die gesamte Dauer bzw. bis zum nächsten Klangwechsel; keine Neuanschläge außer Klangwechsel
- **Pedal/Bass:** Grundton  – LB: JC-B001 Tiefer Grundton-Drone
- **Zulässige Einzelereignisse:** GS-Ereignisfeld: Kandidaten JC-M020 Tiefes Grollmotiv; Abstände 7-5-9 Takte; Start T4
- **Ereignisabstände / Mindestabstand:** 7-5-9; mindestens 5 Takte
- **Register:** GS tief (C2–C3)
- **Dissonanzabsicht:** ♭2 im Grollmotiv als U; Tritonus im Klang
- **Langfristig bei konstanter XYZ-Position:** Ein einziges Ereignis, gleich bleibend; Bedrohung durch Wiederkehr.
- **MIDI:** `JC-EF07_Grollen.mid` · Spuren LF, LB, GS

#### JC-EF08 Akkordwechsel als Ereignis

- **Charakter:** Keine Einzelereignisse; nur der Klang wechselt in unregelmäßigen Abständen.
- **XYZ-Anker:** (0,40 / 0,20 / 0,20); Tonart C, Äolisch (natürliches Moll), 64 Takte, 60 BPM (Vorschlag)
- **Harmonisches Grundfeld:** ab T1 JC-H043 Moll add9 Fläche, ab T12 JC-H071 ♭VI als Zentrum, ab T19 JC-H043 Moll add9 Fläche, ab T33 JC-H045 Gehaltener sus4, ab T44 JC-H043 Moll add9 Fläche, ab T57 JC-H071 ♭VI als Zentrum
- **Haltedauer:** Klang über die gesamte Dauer bzw. bis zum nächsten Klangwechsel; keine Neuanschläge außer Klangwechsel
- **Pedal/Bass:** Pedal  – LB: JC-B005 Unabhängiges Pedal
- **Zulässige Einzelereignisse:** nur Klangwechsel
- **Ereignisabstände / Mindestabstand:** 11-7-14-11-13; mindestens 7 Takte
- **Register:** LF Mittellage, LB tief
- **Dissonanzabsicht:** keine; nur Mehrdeutigkeit
- **Langfristig bei konstanter XYZ-Position:** Die Klangfolge ist das Ereignisfeld; 7 bis 14 Takte ohne jede Änderung.
- **MIDI:** `JC-EF08_Akkordwechsel_als_Ereignis.mid` · Spuren LF, LB

#### JC-EF09 Kraftvolles Feld ohne Bewegung

- **Charakter:** Breiter Moll über Pedal; lange Choraltöne und seltene Stiche.
- **XYZ-Anker:** (0,30 / 0,85 / 0,15); Tonart C, Äolisch (natürliches Moll), 48 Takte, 64 BPM (Vorschlag)
- **Harmonisches Grundfeld:** ab T1 JC-H046 Breiter Moll mit Doppeloktave
- **Haltedauer:** Klang über die gesamte Dauer bzw. bis zum nächsten Klangwechsel; keine Neuanschläge außer Klangwechsel
- **Pedal/Bass:** Pedal  – LB: JC-B005 Unabhängiges Pedal
- **Zulässige Einzelereignisse:** HM-Ereignisfeld: Kandidaten JC-M043 Langer Choralton, JC-M043 Langer Choralton; Abstände 8-12 Takte; Start T5; ST-Ereignisfeld: Kandidaten ST; Abstände 16 Takte; Start T17
- **Ereignisabstände / Mindestabstand:** 8-12 / 16; mindestens 8 Takte
- **Register:** LF breit, HM Mitte-hoch
- **Dissonanzabsicht:** keine
- **Langfristig bei konstanter XYZ-Position:** Kraft durch Dauer und Lautstärke; Dichte bleibt minimal.
- **MIDI:** `JC-EF09_Kraftvolles_Feld_ohne_Bewegung.mid` · Spuren LF, LB, ST, HM

#### JC-EF10 Leerraum mit Wiederkehr

- **Charakter:** Leere Quinte; ein Zweiton kehrt nach langen Pausen identisch zurück.
- **XYZ-Anker:** (0,30 / 0,10 / 0,30); Tonart G, Äolisch (natürliches Moll), 64 Takte, 60 BPM (Vorschlag)
- **Harmonisches Grundfeld:** ab T1 JC-H001 Kalte Quintleere
- **Haltedauer:** Klang über die gesamte Dauer bzw. bis zum nächsten Klangwechsel; keine Neuanschläge außer Klangwechsel
- **Pedal/Bass:** Grundton  – LB: JC-B001 Tiefer Grundton-Drone
- **Zulässige Einzelereignisse:** TU-Ereignisfeld: Kandidaten JC-M045 Rückkehr nach Pause; Abstände 16-12 Takte; Start T3
- **Ereignisabstände / Mindestabstand:** 16-12; mindestens 12 Takte
- **Register:** TU um C5
- **Dissonanzabsicht:** keine
- **Langfristig bei konstanter XYZ-Position:** Bis zu 14 Takte ohne neues Ereignis; ausdrücklich zulässig.
- **MIDI:** `JC-EF10_Leerraum_mit_Wiederkehr.mid` · Spuren LF, LB, TU

#### JC-EF11 Uhr im leeren Haus

- **Charakter:** Moll add9; ein Uhrwerk-Signal in kurzen, unregelmäßigen Abständen.
- **XYZ-Anker:** (0,40 / 0,20 / 0,60); Tonart A, Äolisch (natürliches Moll), 48 Takte, 72 BPM (Vorschlag)
- **Harmonisches Grundfeld:** ab T1 JC-H043 Moll add9 Fläche
- **Haltedauer:** Klang über die gesamte Dauer bzw. bis zum nächsten Klangwechsel; keine Neuanschläge außer Klangwechsel
- **Pedal/Bass:** kein Bass
- **Zulässige Einzelereignisse:** TU-Ereignisfeld: Kandidaten JC-M021 Uhrwerk-Signal; Abstände 5-7-4 Takte; Start T2
- **Ereignisabstände / Mindestabstand:** 5-7-4; mindestens 4 Takte
- **Register:** TU über C5
- **Dissonanzabsicht:** Leitton im Signal als U
- **Langfristig bei konstanter XYZ-Position:** Mechanisches Signal bei geringer Dichte: psychologische Unruhe.
- **MIDI:** `JC-EF11_Uhr_im_leeren_Haus.mid` · Spuren LF, TU

#### JC-EF12 Fernes Echo über Dur-Fremdklang

- **Charakter:** Dur einen Ganzton über dem Pedal; leise Echo-Ereignisse.
- **XYZ-Anker:** (0,65 / 0,15 / 0,50); Tonart E, Chromatisch (frei, nur Akkordtöne + autorisierte Töne), 48 Takte, 62 BPM (Vorschlag)
- **Harmonisches Grundfeld:** ab T1 JC-H068 Dur über fremdem Pedal
- **Haltedauer:** Klang über die gesamte Dauer bzw. bis zum nächsten Klangwechsel; keine Neuanschläge außer Klangwechsel
- **Pedal/Bass:** Pedal , autorisiert – LB: JC-B005 Unabhängiges Pedal
- **Zulässige Einzelereignisse:** TU-Ereignisfeld: Kandidaten JC-M004 Fernes Echo; Abstände 6-10-8 Takte; Start T4
- **Ereignisabstände / Mindestabstand:** 6-10-8; mindestens 6 Takte
- **Register:** TU hoch
- **Dissonanzabsicht:** Pedal gegen Fremdklang als autorisierte Reibung
- **Langfristig bei konstanter XYZ-Position:** Hell und bedrohlich zugleich; Ereignisse sehr leise.
- **MIDI:** `JC-EF12_Fernes_Echo_ueber_Dur_Fremdklang.mid` · Spuren LF, LB, TU

## 11. S – Mehrschichtige Modellstudien

Jede Studie liegt als MIDI-Datei mit benannten Rollenspuren vor. Tempo ist ein Vorschlag (STROMSCORE hat keinen festen BPM). Studien mit „XYZ-Fahrt“ zeigen Entwicklung **aufgrund tatsächlicher XYZ-Veränderung**; alle übrigen zeigen Entwicklung bei **unveränderter** Position.

#### JC-S01 Drone allein

- **Zweck:** Ein Klang, nichts sonst; Grundzustand für dunkle Ruhe.
- **Eckdaten:** 32 Takte 4/4, 60 BPM (Vorschlag), Tonart E, Äolisch (natürliches Moll)
- **XYZ:** (0,10 / 0,10 / 0,10), Z-Charakter neutral · konstante Position
- **Harmonie:** ab T1 JC-H002 Oktavsäule
- **Schichten:**
  - LF aus Harmonie
  - LB: JC-B001 Tiefer Grundton-Drone
- **Entwicklungsstrategie:** Stasis; **Transformationen:** JC-T012 Langfristige Stasis
- **Merkmale:** ohne AR, ohne HM/GS, pulslos
- **MIDI:** `JC-S01_Drone_allein.mid` · Spuren LF, LB · 3 Noten · Funktionen {'A': 3}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S02 Drone mit seltenen Einzelereignissen

- **Zweck:** Leere Quinte mit ♭2; vier hohe Rufe und ein Stich in 64 Takten.
- **Eckdaten:** 64 Takte 4/4, 58 BPM (Vorschlag), Tonart A, Phrygisch
- **XYZ:** (0,10 / 0,20 / 0,50), Z-Charakter psychologisch · konstante Position
- **Harmonie:** ab T1 JC-H009 Quinte mit ♭2
- **Schichten:**
  - LF aus Harmonie
  - LB: JC-B001 Tiefer Grundton-Drone
  - TU: JC-M001 Einsamer hoher Ruf an T9, T22, T41, T57
  - ST (Note 36) an T33
- **Entwicklungsstrategie:** Ereignisfeld; **Transformationen:** JC-T012 Langfristige Stasis
- **Merkmale:** ohne AR, ohne HM/GS, pulslos
- **MIDI:** `JC-S02_Drone_mit_seltenen_Einzelereignissen.mid` · Spuren LF, LB, TU, ST · 9 Noten · Funktionen {'A': 7, 'U': 1, 'ST': 1}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S03 Hoher Einzelton über tiefem Feld

- **Zweck:** Weite Quinte, darüber alle vier Takte ein hoher Ton mit leisem Nachschlag.
- **Eckdaten:** 32 Takte 4/4, 64 BPM (Vorschlag), Tonart D, Äolisch (natürliches Moll)
- **XYZ:** (0,60 / 0,10 / 0,30), Z-Charakter psychologisch · konstante Position
- **Harmonie:** ab T1 JC-H008 Weite Quinte
- **Schichten:**
  - LF aus Harmonie
  - LB: JC-B001 Tiefer Grundton-Drone
  - TU: JC-M039 Hoher Ton mit Nachschlag, Oktave -1 an T3, T7, T11, T15, T19, T23, T27, T31
- **Entwicklungsstrategie:** Stasis; **Transformationen:** JC-T012 Langfristige Stasis
- **Merkmale:** ohne AR, ohne HM/GS, pulslos
- **MIDI:** `JC-S03_Hoher_Einzelton_ueber_tiefem_Feld.mid` · Spuren LF, LB, TU · 20 Noten · Funktionen {'A': 20}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S04 Puls allein

- **Zweck:** Nur der Herzschlag-Bass; harmonischer Kontext Oktavsäule (nicht gespielt).
- **Eckdaten:** 16 Takte 4/4, 72 BPM (Vorschlag), Tonart C, Äolisch (natürliches Moll)
- **XYZ:** (0,20 / 0,30 / 0,40), Z-Charakter psychologisch · konstante Position
- **Harmonie:** ab T1 JC-H002 Oktavsäule
- **Schichten:**
  - KB: JC-B013 Herzschlag-Bass
- **Entwicklungsstrategie:** Stasis; **Transformationen:** JC-T012 Langfristige Stasis
- **Merkmale:** ohne AR, ohne HM/GS
- **MIDI:** `JC-S04_Puls_allein.mid` · Spuren KB · 32 Noten · Funktionen {'A': 32}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S05 Puls und Drone

- **Zweck:** Leere Quinte und pulsierender Achtelbass; der Puls atmet in zwei Phasen.
- **Eckdaten:** 32 Takte 4/4, 96 BPM (Vorschlag), Tonart E, Äolisch (natürliches Moll)
- **XYZ:** (0,20 / 0,50 / 0,30), Z-Charakter mechanisch · konstante Position
- **Harmonie:** ab T1 JC-H001 Kalte Quintleere
- **Schichten:**
  - LF aus Harmonie
  - KB: JC-B010 Stoischer Achtelbass (T1-12,17-28)
- **Entwicklungsstrategie:** Atmung; **Transformationen:** JC-T011 Unterbrechung und Wiederaufnahme
- **Merkmale:** ohne AR, ohne HM/GS
- **MIDI:** `JC-S05_Puls_und_Drone.mid` · Spuren LF, KB · 194 Noten · Funktionen {'A': 194}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S06 Basssequenz und statische Fläche

- **Zweck:** Eigenständiges Moll-Riff unter gehaltenem Moll add9.
- **Eckdaten:** 32 Takte 4/4, 104 BPM (Vorschlag), Tonart A, Äolisch (natürliches Moll)
- **XYZ:** (0,30 / 0,60 / 0,30), Z-Charakter neutral · konstante Position
- **Harmonie:** ab T1 JC-H043 Moll add9 Fläche
- **Schichten:**
  - LF aus Harmonie
  - KB: JC-B021 Moll-Riff
- **Entwicklungsstrategie:** Stasis; **Transformationen:** JC-T012 Langfristige Stasis
- **Merkmale:** ohne AR, ohne HM/GS
- **MIDI:** `JC-S06_Basssequenz_und_statische_Flaeche.mid` · Spuren LF, KB · 260 Noten · Funktionen {'A': 196, 'T': 64}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S07 Basssequenz und höherer Sequencer

- **Zweck:** Oktav-Achtelbass und Quint-Oktav-Zelle; ab Takt 17 rotiert der Sequencer ins Arpeggio-Register höher.
- **Eckdaten:** 32 Takte 4/4, 112 BPM (Vorschlag), Tonart D, Äolisch (natürliches Moll)
- **XYZ:** (0,40 / 0,70 / 0,50), Z-Charakter mechanisch · konstante Position
- **Harmonie:** ab T1 JC-H017 Moll-Grundklang für Pulse
- **Schichten:**
  - LF aus Harmonie
  - KB: JC-B026 Oktav-Achtelbass
  - AR: JC-Q011 Quint–Oktav–Quint (T1-16)
  - GS: JC-Q011 Quint–Oktav–Quint (T17-32), Oktave +1
- **Entwicklungsstrategie:** Rotation; **Transformationen:** JC-T007 Schichtrotation, JC-T003 Oktavverlagerung
- **Merkmale:** mit Sequencer und Gegenstimme
- **MIDI:** `JC-S07_Basssequenz_und_hoeherer_Sequencer.mid` · Spuren LF, KB, AR, GS · 771 Noten · Funktionen {'A': 771}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S08 Komplementäre repetitive Schichten

- **Zweck:** Zwei Sequencer greifen ineinander (Schlag/Offbeat) über tiefem Drone.
- **Eckdaten:** 32 Takte 4/4, 108 BPM (Vorschlag), Tonart G, Äolisch (natürliches Moll)
- **XYZ:** (0,40 / 0,60 / 0,60), Z-Charakter mechanisch · konstante Position
- **Harmonie:** ab T1 JC-H017 Moll-Grundklang für Pulse
- **Schichten:**
  - LB: JC-B001 Tiefer Grundton-Drone
  - AR: JC-Q024 Komplementär-Sequenz A
  - GS: JC-Q025 Komplementär-Sequenz B
- **Entwicklungsstrategie:** Stasis; **Transformationen:** JC-T012 Langfristige Stasis
- **Merkmale:** mit Sequencer und Gegenstimme
- **MIDI:** `JC-S08_Komplementaere_repetitive_Schichten.mid` · Spuren LB, AR, GS · 257 Noten · Funktionen {'A': 257}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S09 Pulslose Mystery

- **Zweck:** Kalter sus2 färbt sich nach 32 Takten lydisch um; Glocken-Kanon ohne Bass.
- **Eckdaten:** 64 Takte 4/4, 60 BPM (Vorschlag), Tonart H, Lydisch
- **XYZ:** (0,85 / 0,10 / 0,30), Z-Charakter neutral · konstante Position
- **Harmonie:** ab T1 JC-H044 Kalter sus2, ab T33 JC-H072 Lydische Helle
- **Schichten:**
  - LF aus Harmonie
  - TU: JC-M040 Drei Glocken, Oktave -1 an T5, T13, T21, T29, T37, T45, T53, T61
  - GS: JC-M040 Drei Glocken, Oktave -1 an T5, T13, T21, T29, T37, T45, T53, T61
- **Entwicklungsstrategie:** Umfärbung; **Transformationen:** JC-T008 Harmonische Umfärbung, JC-T006 Rollenwanderung
- **Merkmale:** ohne AR, pulslos
- **MIDI:** `JC-S09_Pulslose_Mystery.mid` · Spuren LF, TU, GS · 55 Noten · Funktionen {'A': 55}
- **Evidenz:** I – begründete Interpretation

#### JC-S10 Gehaltene, mehrstimmige Klangfelder

- **Zweck:** Breiter Moll über Pedal; ab Takt 17 wird ♭VI zum Zentrum.
- **Eckdaten:** 32 Takte 4/4, 70 BPM (Vorschlag), Tonart C, Äolisch (natürliches Moll)
- **XYZ:** (0,30 / 0,75 / 0,10), Z-Charakter neutral · konstante Position
- **Harmonie:** ab T1 JC-H046 Breiter Moll mit Doppeloktave, ab T17 JC-H071 ♭VI als Zentrum
- **Schichten:**
  - LF aus Harmonie
  - LB: JC-B005 Unabhängiges Pedal
- **Entwicklungsstrategie:** Umfärbung; **Transformationen:** JC-T008 Harmonische Umfärbung
- **Merkmale:** ohne AR, ohne HM/GS, pulslos
- **MIDI:** `JC-S10_Gehaltene_mehrstimmige_Klangfelder.mid` · Spuren LF, LB · 8 Noten · Funktionen {'A': 8}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S11 Melancholie mit lyrischer Linie

- **Zweck:** Langsamer Kreis mit Durklängen; lyrische Linie zweimal, vereinzelte Klavierfigur.
- **Eckdaten:** 32 Takte 4/4, 76 BPM (Vorschlag), Tonart A, Äolisch (natürliches Moll)
- **XYZ:** (0,55 / 0,30 / 0,20), Z-Charakter neutral · konstante Position
- **Harmonie:** ab T1 JC-H077 Melancholischer Kreis
- **Schichten:**
  - LF aus Harmonie
  - LB aus Harmonie
  - HM: JC-M012 Lyrische Linie an T5, T21
  - TU: JC-M023 Zögernde Klavierfigur an T13, T29
- **Entwicklungsstrategie:** Wanderung; **Transformationen:** JC-T006 Rollenwanderung
- **Merkmale:** ohne AR, pulslos
- **MIDI:** `JC-S11_Melancholie_mit_lyrischer_Linie.mid` · Spuren LF, LB, TU, HM · 46 Noten · Funktionen {'A': 32, 'T': 10, 'V': 4}
- **Evidenz:** I – begründete Interpretation

#### JC-S12 Melancholie ohne Melodie

- **Zweck:** add9 und ♭VI maj7 mit gebundener Achtelkette; trägt ohne HM und GS.
- **Eckdaten:** 32 Takte 4/4, 84 BPM (Vorschlag), Tonart E, Äolisch (natürliches Moll)
- **XYZ:** (0,50 / 0,35 / 0,20), Z-Charakter neutral · konstante Position
- **Harmonie:** ab T1 JC-H078 Melancholie add9 nach ♭VI maj7
- **Schichten:**
  - LF aus Harmonie
  - LB aus Harmonie
  - AR: JC-Q017 Melancholische Achtelkette (T5-32)
- **Entwicklungsstrategie:** Umfärbung; **Transformationen:** JC-T008 Harmonische Umfärbung
- **Merkmale:** ohne HM/GS
- **MIDI:** `JC-S12_Melancholie_ohne_Melodie.mid` · Spuren LF, LB, AR · 235 Noten · Funktionen {'A': 219, 'V': 16}
- **Evidenz:** I – begründete Interpretation

#### JC-S13 Glocken- und Kanonstruktur

- **Zweck:** Quintenstapel; Glockenkopf im Tupfer, um zwei Viertel versetzt in der Gegenstimme.
- **Eckdaten:** 32 Takte 4/4, 80 BPM (Vorschlag), Tonart D, Äolisch (natürliches Moll)
- **XYZ:** (0,80 / 0,20 / 0,30), Z-Charakter neutral · konstante Position
- **Harmonie:** ab T1 JC-H004 Quintenstapel mit None
- **Schichten:**
  - LF aus Harmonie
  - TU: JC-M018 Glocken-Kanonkopf, Oktave -1 an T1, T3, T5, T7, T9, T11, T13, T15, T17, T19, T21, T23, T25, T27, T29, T31
  - GS: JC-M018 Glocken-Kanonkopf, Oktave -1 an T1, T3, T5, T7, T9, T11, T13, T15, T17, T19, T21, T23, T25, T27, T29, T31
- **Entwicklungsstrategie:** Stasis; **Transformationen:** JC-T006 Rollenwanderung
- **Merkmale:** ohne AR, pulslos
- **MIDI:** `JC-S13_Glocken_und_Kanonstruktur.mid` · Spuren LF, TU, GS · 131 Noten · Funktionen {'A': 98, 'T': 33}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S14 Kraft ohne Notendichte

- **Zweck:** Quint-Oktav-Turm, schwere Halbe-Akkorde und ein langer Choralton.
- **Eckdaten:** 32 Takte 4/4, 72 BPM (Vorschlag), Tonart C, Äolisch (natürliches Moll)
- **XYZ:** (0,30 / 0,90 / 0,10), Z-Charakter neutral · konstante Position
- **Harmonie:** ab T1 JC-H003 Quint-Oktav-Turm
- **Schichten:**
  - LF aus Harmonie
  - LB: JC-B045 Halbe Grundton–Quinte, Oktave +1
  - KF aus Harmonie
  - HM: JC-M043 Langer Choralton an T9, T17, T25
- **Entwicklungsstrategie:** Stasis; **Transformationen:** JC-T012 Langfristige Stasis
- **Merkmale:** ohne AR
- **MIDI:** `JC-S14_Kraft_ohne_Notendichte.mid` · Spuren LF, KF, LB, HM · 215 Noten · Funktionen {'A': 215}
- **Evidenz:** I – begründete Interpretation

#### JC-S15 Psychologische Unruhe ohne Sequencer

- **Zweck:** Wandernder Reibungston über Pedal; seltene, unregelmäßige Tupfer und ein Stich.
- **Eckdaten:** 32 Takte 4/4, 66 BPM (Vorschlag), Tonart F, Harmonisch Moll
- **XYZ:** (0,20 / 0,30 / 0,80), Z-Charakter psychologisch · konstante Position
- **Harmonie:** ab T1 JC-H016 Wandernder Reibungston
- **Schichten:**
  - LF aus Harmonie
  - LB: JC-B005 Unabhängiges Pedal
  - TU: JC-M005 Mechanischer Dreiton an T6, T19
  - GS: JC-M033 Stockendes Fragment, Oktave -1 an T11, T27
  - ST (Note 36) an T23
- **Entwicklungsstrategie:** Ereignisfeld; **Transformationen:** JC-T012 Langfristige Stasis
- **Merkmale:** ohne AR, pulslos
- **MIDI:** `JC-S15_Psychologische_Unruhe_ohne_Sequencer.mid` · Spuren LF, LB, TU, ST, GS · 24 Noten · Funktionen {'A': 11, 'U': 10, 'T': 2, 'ST': 1}
- **Evidenz:** I – begründete Interpretation

#### JC-S16 Mechanische Unruhe

- **Zweck:** Uhrwerk-Quinte, ab Takt 9 Uhrwerk-Bass, ab 17 fallendes Uhrwerk in der Gegenstimme.
- **Eckdaten:** 32 Takte 4/4, 100 BPM (Vorschlag), Tonart A, Äolisch (natürliches Moll)
- **XYZ:** (0,40 / 0,55 / 0,85), Z-Charakter mechanisch · **XYZ-Fahrt** (gerichtete Entwicklung nur bei tatsächlicher Veränderung)
- **Harmonie:** ab T1 JC-H001 Kalte Quintleere
- **Schichten:**
  - LF aus Harmonie
  - AR: JC-Q015 Uhrwerk-Quinte
  - KB: JC-B046 Uhrwerk-Bass (T9-32)
  - GS: JC-Q016 Fallendes Uhrwerk (T17-32), Oktave +1
- **Entwicklungsstrategie:** Rotation; **Transformationen:** JC-T013 Kontrollierte Verdichtung
- **Hinweis:** Gerichtete Verdichtung: nur zulässig, wenn Z tatsächlich steigt (XYZ-Fahrt).
- **Merkmale:** mit Sequencer und Gegenstimme
- **MIDI:** `JC-S16_Mechanische_Unruhe.mid` · Spuren LF, KB, AR, GS · 1154 Noten · Funktionen {'A': 962, 'T': 128, 'V': 64}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S17 Akuter Horror durch Reduktion

- **Zweck:** Acht Takte dichte Halbtonreibung, dann Stich und Absturz auf einen Ton; später ein Halbton-Stoß.
- **Eckdaten:** 16 Takte 4/4, 120 BPM (Vorschlag), Tonart E, Phrygisch
- **XYZ:** (0,10 / 0,90 / 0,90), Z-Charakter psychologisch · **XYZ-Fahrt** (gerichtete Entwicklung nur bei tatsächlicher Veränderung)
- **Harmonie:** ab T1 JC-H014 Doppelte Halbtonreibung, ab T9 JC-H002 Oktavsäule
- **Schichten:**
  - LF aus Harmonie
  - AR: JC-Q007 Halbton-Wiege (T1-8)
  - KB: JC-B012 Sechzehntelbass (T1-8)
  - LB: JC-B001 Tiefer Grundton-Drone (T9-16)
  - ST (Note 36) an T9
  - TU: JC-M044 Zweiton-Stoß, Oktave -1 an T13
- **Entwicklungsstrategie:** Reduktion und Wiederaufnahme; **Transformationen:** JC-T014 Kontrollierte Reduktion
- **Merkmale:** ohne HM/GS
- **MIDI:** `JC-S17_Akuter_Horror_durch_Reduktion.mid` · Spuren LF, LB, KB, AR, TU, ST · 264 Noten · Funktionen {'A': 196, 'U': 66, 'F': 1, 'ST': 1}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S18 Akuter Horror durch Verdichtung

- **Zweck:** Halbton-Blockpendel der Fläche; Schichten treten nacheinander ein.
- **Eckdaten:** 16 Takte 4/4, 132 BPM (Vorschlag), Tonart C, Chromatisch (frei, nur Akkordtöne + autorisierte Töne)
- **XYZ:** (0,10 / 1,00 / 1,00), Z-Charakter mechanisch · **XYZ-Fahrt** (gerichtete Entwicklung nur bei tatsächlicher Veränderung)
- **Harmonie:** ab T1 JC-H015 Halbton-Blockpendel der Quinte
- **Schichten:**
  - LF aus Harmonie
  - KB: JC-B012 Sechzehntelbass
  - AR: JC-Q021 Blockzelle Oktave–Quarte (T5-16), folgt Akkorden
  - GS: JC-Q007 Halbton-Wiege (T9-16), Oktave +1, folgt Akkorden
  - ST (Note 36) an T13, T15
- **Entwicklungsstrategie:** Blockverschiebung; **Transformationen:** JC-T001 Blocktransposition, JC-T013 Kontrollierte Verdichtung
- **Merkmale:** mit Sequencer und Gegenstimme
- **MIDI:** `JC-S18_Akuter_Horror_durch_Verdichtung.mid` · Spuren LF, KB, AR, ST, GS · 586 Noten · Funktionen {'A': 472, 'T': 48, 'U': 64, 'ST': 2}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S19 Entwicklung durch Schichtung bei unveränderter Harmonik

- **Zweck:** 64 Takte eine leere Quinte; Schichten kommen und gehen ohne Gesamtsteigerung.
- **Eckdaten:** 64 Takte 4/4, 100 BPM (Vorschlag), Tonart G, Äolisch (natürliches Moll)
- **XYZ:** (0,30 / 0,50 / 0,40), Z-Charakter mechanisch · konstante Position
- **Harmonie:** ab T1 JC-H001 Kalte Quintleere
- **Schichten:**
  - LF aus Harmonie
  - LB: JC-B001 Tiefer Grundton-Drone
  - KB: JC-B010 Stoischer Achtelbass (T9-56)
  - AR: JC-Q026 Endlosband (T17-32,41-56)
  - GS: JC-Q005 Quint-Wiege (T25-40), Oktave +1
  - TU: JC-M001 Einsamer hoher Ruf, Oktave -1 an T49, T61
- **Entwicklungsstrategie:** Atmung; **Transformationen:** JC-T007 Schichtrotation, JC-T011 Unterbrechung und Wiederaufnahme
- **Merkmale:** mit Sequencer und Gegenstimme
- **MIDI:** `JC-S19_Entwicklung_durch_Schichtung_bei_unveraenderter_Harmonik.mid` · Spuren LF, LB, KB, AR, TU, GS · 1029 Noten · Funktionen {'A': 965, 'T': 64}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S20 Hypnotische Stasis

- **Zweck:** Endlosband über stoischem Achtelbass, 64 Takte unverändert.
- **Eckdaten:** 64 Takte 4/4, 108 BPM (Vorschlag), Tonart D, Äolisch (natürliches Moll)
- **XYZ:** (0,30 / 0,50 / 0,30), Z-Charakter mechanisch · konstante Position
- **Harmonie:** ab T1 JC-H017 Moll-Grundklang für Pulse
- **Schichten:**
  - LF aus Harmonie
  - KB: JC-B010 Stoischer Achtelbass
  - AR: JC-Q026 Endlosband
- **Entwicklungsstrategie:** Stasis; **Transformationen:** JC-T012 Langfristige Stasis
- **Merkmale:** ohne HM/GS
- **MIDI:** `JC-S20_Hypnotische_Stasis.mid` · Spuren LF, KB, AR · 1539 Noten · Funktionen {'A': 1411, 'T': 128}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S21 Bedrohliche Action

- **Zweck:** Abwärts-Kreis mit Oktav-Achtelbass und Galopp-Quinte; Stiche an Phrasenanfängen.
- **Eckdaten:** 32 Takte 4/4, 138 BPM (Vorschlag), Tonart E, Äolisch (natürliches Moll)
- **XYZ:** (0,30 / 0,90 / 0,70), Z-Charakter mechanisch · konstante Position
- **Harmonie:** ab T1 JC-H026 Abwärts-Kreis ♭VII–♭VI
- **Schichten:**
  - LF aus Harmonie
  - KB: JC-B026 Oktav-Achtelbass
  - AR: JC-Q048 Galopp-Quinte (T1-16,25-32), folgt Akkorden
  - GS: JC-Q047 Stolper-Oktave (T17-24), Oktave +1, folgt Akkorden
  - ST (Note 36) an T9, T25
- **Entwicklungsstrategie:** Rotation; **Transformationen:** JC-T007 Schichtrotation
- **Merkmale:** mit Sequencer und Gegenstimme
- **MIDI:** `JC-S21_Bedrohliche_Action.mid` · Spuren LF, KB, AR, ST, GS · 658 Noten · Funktionen {'A': 656, 'ST': 2}
- **Evidenz:** I – begründete Interpretation

#### JC-S22 Fünfer-Zelle mit Blockverschiebung

- **Zweck:** 5/4, Akzente 3+3+2+2; Fläche und Zelle rücken gemeinsam einen Halbton tiefer.
- **Eckdaten:** 32 Takte 5/4, 136 BPM (Vorschlag), Tonart F♯, Chromatisch (frei, nur Akkordtöne + autorisierte Töne)
- **XYZ:** (0,20 / 0,80 / 0,80), Z-Charakter mechanisch · konstante Position
- **Harmonie:** ab T1 JC-H001 Kalte Quintleere, ab T9 JC-H001 Kalte Quintleere (Block -1), ab T17 JC-H001 Kalte Quintleere, ab T25 JC-H001 Kalte Quintleere (Block -1)
- **Schichten:**
  - LF aus Harmonie
  - KB: JC-B019 Fünfer-Akzentbass, folgt Akkorden
  - AR: JC-Q014 Fünfer-Zelle 3+3+2+2, folgt Akkorden
- **Entwicklungsstrategie:** Blockverschiebung; **Transformationen:** JC-T001 Blocktransposition, JC-T010 Akzentgruppen-Variation
- **Merkmale:** ohne HM/GS
- **MIDI:** `JC-S22_Fuenfer_Zelle_mit_Blockverschiebung.mid` · Spuren LF, KB, AR · 648 Noten · Funktionen {'A': 488, 'T': 160}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S23 Hohe Arpeggien über tiefer Resonanz

- **Zweck:** Weite Quinte, hohe Moll-Arpeggien in Triolen, später eine Nachklang-Linie.
- **Eckdaten:** 32 Takte 4/4, 88 BPM (Vorschlag), Tonart A, Äolisch (natürliches Moll)
- **XYZ:** (0,60 / 0,40 / 0,40), Z-Charakter neutral · konstante Position
- **Harmonie:** ab T1 JC-H008 Weite Quinte
- **Schichten:**
  - LF aus Harmonie
  - LB: JC-B001 Tiefer Grundton-Drone
  - AR: JC-Q049 Hohe Klingel-Arpeggien (T1-24)
  - HM: JC-M022 Nachklang-Melodie an T25
- **Entwicklungsstrategie:** Stasis; **Transformationen:** JC-T014 Kontrollierte Reduktion
- **Merkmale:** mit Sequencer und Gegenstimme
- **MIDI:** `JC-S23_Hohe_Arpeggien_ueber_tiefer_Resonanz.mid` · Spuren LF, LB, AR, HM · 296 Noten · Funktionen {'A': 198, 'T': 98}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S24 Schreitende Akkorde unter Klavier

- **Zweck:** Oberklänge schreiten über gehaltenem Pedal; vereinzelte zögernde Figur.
- **Eckdaten:** 32 Takte 4/4, 70 BPM (Vorschlag), Tonart E, Äolisch (natürliches Moll)
- **XYZ:** (0,40 / 0,30 / 0,30), Z-Charakter neutral · konstante Position
- **Harmonie:** ab T1 JC-H034 Schreitend über Pedal
- **Schichten:**
  - LF aus Harmonie
  - LB: JC-B005 Unabhängiges Pedal
  - TU: JC-M023 Zögernde Klavierfigur an T4, T12, T20, T28
- **Entwicklungsstrategie:** Umfärbung; **Transformationen:** JC-T008 Harmonische Umfärbung
- **Merkmale:** ohne AR, ohne HM/GS, pulslos
- **MIDI:** `JC-S24_Schreitende_Akkorde_unter_Klavier.mid` · Spuren LF, LB, TU · 37 Noten · Funktionen {'A': 33, 'T': 4}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S25 Uhrwerk der verrinnenden Zeit

- **Zweck:** Gehaltene Mollfläche, fallendes Uhrwerk leise, seltene Uhrwerk-Signale.
- **Eckdaten:** 32 Takte 4/4, 92 BPM (Vorschlag), Tonart C, Äolisch (natürliches Moll)
- **XYZ:** (0,40 / 0,30 / 0,70), Z-Charakter mechanisch · konstante Position
- **Harmonie:** ab T1 JC-H043 Moll add9 Fläche
- **Schichten:**
  - LF aus Harmonie
  - AR: JC-Q016 Fallendes Uhrwerk
  - TU: JC-M021 Uhrwerk-Signal an T7, T18, T29
- **Entwicklungsstrategie:** Stasis; **Transformationen:** JC-T012 Langfristige Stasis
- **Merkmale:** ohne HM/GS
- **MIDI:** `JC-S25_Uhrwerk_der_verrinnenden_Zeit.mid` · Spuren LF, AR, TU · 528 Noten · Funktionen {'A': 269, 'T': 128, 'V': 128, 'U': 3}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S26 Herzschlag unter Mollkreis

- **Zweck:** Kreis mit vermindertem ii; der Herzschlag bleibt auf dem Grundton.
- **Eckdaten:** 32 Takte 4/4, 80 BPM (Vorschlag), Tonart D, Äolisch (natürliches Moll)
- **XYZ:** (0,30 / 0,40 / 0,50), Z-Charakter psychologisch · konstante Position
- **Harmonie:** ab T1 JC-H024 Kreis mit vermindertem ii
- **Schichten:**
  - LF aus Harmonie
  - KB: JC-B013 Herzschlag-Bass
- **Entwicklungsstrategie:** Stasis; **Transformationen:** JC-T012 Langfristige Stasis
- **Merkmale:** ohne AR, ohne HM/GS
- **MIDI:** `JC-S26_Herzschlag_unter_Mollkreis.mid` · Spuren LF, KB · 96 Noten · Funktionen {'A': 80, 'T': 16}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S27 Obsession: Wanderzelle mit Umfärbung

- **Zweck:** Ein Motiv wandert HM → TU → GS → HM; ab Takt 33 färbt sich die Achse Dur/Moll um.
- **Eckdaten:** 64 Takte 4/4, 84 BPM (Vorschlag), Tonart A, Äolisch (natürliches Moll)
- **XYZ:** (0,40 / 0,30 / 0,45), Z-Charakter psychologisch · konstante Position
- **Harmonie:** ab T1 JC-H051 Achse Grundton, ab T33 JC-H054 Achse Quinte, Dur/Moll/sus4
- **Schichten:**
  - LF aus Harmonie
  - LB: JC-B005 Unabhängiges Pedal
  - HM: JC-M016 Wanderzelle an T1, T5, T9, T13, T49, T53, T57, T61
  - TU: JC-M016 Wanderzelle an T17, T21, T25, T29
  - GS: JC-M016 Wanderzelle, Oktave -1 an T33, T37, T41, T45
- **Entwicklungsstrategie:** Wanderung; **Transformationen:** JC-T006 Rollenwanderung, JC-T008 Harmonische Umfärbung
- **Merkmale:** ohne AR, pulslos
- **MIDI:** `JC-S27_Obsession_Wanderzelle_mit_Umfaerbung.mid` · Spuren LF, LB, TU, GS, HM · 101 Noten · Funktionen {'A': 77, 'V': 16, 'T': 8}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S28 Hell und bedrohlich

- **Zweck:** Reiner Durklang einen Ganzton über dem gehaltenen Grundton; einsamer Ruf.
- **Eckdaten:** 32 Takte 4/4, 64 BPM (Vorschlag), Tonart E, Chromatisch (frei, nur Akkordtöne + autorisierte Töne)
- **XYZ:** (0,70 / 0,30 / 0,60), Z-Charakter psychologisch · konstante Position
- **Harmonie:** ab T1 JC-H068 Dur über fremdem Pedal
- **Schichten:**
  - LF aus Harmonie
  - LB: JC-B005 Unabhängiges Pedal
  - TU: JC-M001 Einsamer hoher Ruf, Oktave -1 an T9, T25
- **Entwicklungsstrategie:** Stasis; **Transformationen:** JC-T012 Langfristige Stasis
- **Merkmale:** ohne AR, ohne HM/GS, pulslos
- **MIDI:** `JC-S28_Hell_und_bedrohlich.mid` · Spuren LF, LB, TU · 6 Noten · Funktionen {'A': 3, 'T': 3}
- **Evidenz:** I – begründete Interpretation

#### JC-S29 Kriechende Triolen und langfristige Bedrohung

- **Zweck:** Tiefe Triolenfigur, Moll mit ♭6; Sechston-Fragment wird bei Takt 41 umgefärbt.
- **Eckdaten:** 64 Takte 4/4, 88 BPM (Vorschlag), Tonart D, Äolisch (natürliches Moll)
- **XYZ:** (0,20 / 0,60 / 0,50), Z-Charakter psychologisch · konstante Position
- **Harmonie:** ab T1 JC-H047 Moll mit ♭6 oben, ab T41 JC-H051 Achse Grundton
- **Schichten:**
  - LF aus Harmonie
  - KB: JC-B047 Kriechende Triolen tief
  - AR: JC-Q040 Triolen gegen Viertel (T17-48)
  - HM: JC-M011 Sechston-Fragment an T25, T45
- **Entwicklungsstrategie:** Umfärbung; **Transformationen:** JC-T008 Harmonische Umfärbung
- **Merkmale:** mit Sequencer und Gegenstimme
- **MIDI:** `JC-S29_Kriechende_Triolen_und_langfristige_Bedrohung.mid` · Spuren LF, KB, AR, HM · 604 Noten · Funktionen {'A': 396, 'F': 2, 'U': 128, 'T': 77, 'V': 1}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S30 Warme Mollfläche mit Uhrwerk

- **Zweck:** Breiter Moll, ein Akkordschlag pro Takt, Uhrwerk-Quinte; warm statt kalt.
- **Eckdaten:** 32 Takte 4/4, 96 BPM (Vorschlag), Tonart G, Äolisch (natürliches Moll)
- **XYZ:** (0,30 / 0,50 / 0,60), Z-Charakter mechanisch · konstante Position
- **Harmonie:** ab T1 JC-H046 Breiter Moll mit Doppeloktave
- **Schichten:**
  - LF aus Harmonie
  - KF aus Harmonie
  - AR: JC-Q015 Uhrwerk-Quinte
- **Entwicklungsstrategie:** Stasis; **Transformationen:** JC-T012 Langfristige Stasis
- **Merkmale:** ohne HM/GS
- **MIDI:** `JC-S30_Warme_Mollflaeche_mit_Uhrwerk.mid` · Spuren LF, KF, AR · 612 Noten · Funktionen {'A': 548, 'T': 64}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S31 Kalter Leitton und lyrische Linie

- **Zweck:** Moll mit großer Septime; der kalte Ruf kehrt wieder, die lyrische Linie zweimal.
- **Eckdaten:** 32 Takte 4/4, 72 BPM (Vorschlag), Tonart C, Harmonisch Moll
- **XYZ:** (0,45 / 0,30 / 0,50), Z-Charakter psychologisch · konstante Position
- **Harmonie:** ab T1 JC-H049 Moll mit großer Septime
- **Schichten:**
  - LF aus Harmonie
  - LB: JC-B001 Tiefer Grundton-Drone
  - TU: JC-M002 Ruf mit Halbtonfall, Oktave -1 an T1, T9, T17, T25
  - HM: JC-M012 Lyrische Linie an T5, T21
- **Entwicklungsstrategie:** Wanderung; **Transformationen:** JC-T006 Rollenwanderung
- **Merkmale:** ohne AR, pulslos
- **MIDI:** `JC-S31_Kalter_Leitton_und_lyrische_Linie.mid` · Spuren LF, LB, TU, HM · 27 Noten · Funktionen {'A': 21, 'V': 4, 'T': 2}
- **Evidenz:** I – begründete Interpretation

#### JC-S32 Moll-Kreis mit Zweiton-Stampfen

- **Zweck:** Fünfgliedriger Kreis, Oktav-Achtelbass, Herzschlag-Quinte als stampfendes Motiv.
- **Eckdaten:** 40 Takte 4/4, 104 BPM (Vorschlag), Tonart E, Äolisch (natürliches Moll)
- **XYZ:** (0,50 / 0,70 / 0,40), Z-Charakter neutral · konstante Position
- **Harmonie:** ab T1 JC-H025 Fünfgliedriger Kreis
- **Schichten:**
  - LF aus Harmonie
  - KB: JC-B026 Oktav-Achtelbass
  - GS: JC-Q039 Herzschlag-Quinte, folgt nicht
- **Entwicklungsstrategie:** Stasis; **Transformationen:** JC-T012 Langfristige Stasis
- **Merkmale:** ohne AR
- **MIDI:** `JC-S32_Moll_Kreis_mit_Zweiton_Stampfen.mid` · Spuren LF, KB, GS · 452 Noten · Funktionen {'A': 412, 'T': 40}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S33 Herzschlag allein, hohe Klagelaute

- **Zweck:** Nur Herzschlag; darüber selten der Halbton-Seufzer in hoher Lage.
- **Eckdaten:** 32 Takte 4/4, 76 BPM (Vorschlag), Tonart A, Äolisch (natürliches Moll)
- **XYZ:** (0,15 / 0,40 / 0,50), Z-Charakter psychologisch · konstante Position
- **Harmonie:** ab T1 JC-H002 Oktavsäule
- **Schichten:**
  - KB: JC-B013 Herzschlag-Bass
  - TU: JC-M010 Halbton-Seufzer an T6, T15, T27
- **Entwicklungsstrategie:** Ereignisfeld; **Transformationen:** JC-T012 Langfristige Stasis
- **Merkmale:** ohne AR, ohne HM/GS
- **MIDI:** `JC-S33_Herzschlag_allein_hohe_Klagelaute.mid` · Spuren KB, TU · 70 Noten · Funktionen {'A': 64, 'T': 6}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S34 Dur-Lichtung

- **Zweck:** Moll öffnet sich nach acht Takten zum parallelen Dur; hohe Glockenfigur.
- **Eckdaten:** 32 Takte 4/4, 80 BPM (Vorschlag), Tonart F, Äolisch (natürliches Moll)
- **XYZ:** (0,75 / 0,30 / 0,20), Z-Charakter neutral · konstante Position
- **Harmonie:** ab T1 JC-H042 Dur-Lichtung
- **Schichten:**
  - LF aus Harmonie
  - LB aus Harmonie
  - AR: JC-Q033 Hohe Glockenfigur, Oktave -1
- **Entwicklungsstrategie:** Umfärbung; **Transformationen:** JC-T008 Harmonische Umfärbung
- **Merkmale:** ohne HM/GS
- **MIDI:** `JC-S34_Dur_Lichtung.mid` · Spuren LF, LB, AR · 394 Noten · Funktionen {'A': 298, 'T': 96}
- **Evidenz:** I – begründete Interpretation

#### JC-S35 Atmung: Pulsschichten kommen und gehen

- **Zweck:** Immer zwei von drei Pulsschichten aktiv; Wechsel gekoppelt alle 16 Takte.
- **Eckdaten:** 64 Takte 4/4, 100 BPM (Vorschlag), Tonart C, Äolisch (natürliches Moll)
- **XYZ:** (0,35 / 0,55 / 0,35), Z-Charakter mechanisch · konstante Position
- **Harmonie:** ab T1 JC-H028 Langsamer Zweiklang-Kreis
- **Schichten:**
  - LF aus Harmonie
  - LB aus Harmonie
  - KB: JC-B009 Pulsierender Achtelbass (T1-32)
  - AR: JC-Q005 Quint-Wiege (T1-16,33-64), folgt Akkorden
  - GS: JC-Q025 Komplementär-Sequenz B (T17-32,49-64), Oktave +1, folgt nicht
  - TU: JC-M028 Quintsprung-Signal (T33-48) an T36, T44
- **Entwicklungsstrategie:** Rotation; **Transformationen:** JC-T007 Schichtrotation
- **Merkmale:** mit Sequencer und Gegenstimme
- **MIDI:** `JC-S35_Atmung_Pulsschichten_kommen_und_gehen.mid` · Spuren LF, LB, KB, AR, TU, GS · 790 Noten · Funktionen {'A': 757, 'T': 33}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S36 Reduktion und Wiederaufnahme

- **Zweck:** Volle Schichtung, zweimal Absturz auf den Drone, identische Wiederkehr.
- **Eckdaten:** 64 Takte 4/4, 112 BPM (Vorschlag), Tonart E, Äolisch (natürliches Moll)
- **XYZ:** (0,20 / 0,60 / 0,50), Z-Charakter mechanisch · konstante Position
- **Harmonie:** ab T1 JC-H001 Kalte Quintleere
- **Schichten:**
  - LB: JC-B001 Tiefer Grundton-Drone
  - LF aus Harmonie
  - KB: JC-B010 Stoischer Achtelbass (T1-16,21-40,45-64)
  - AR: JC-Q011 Quint–Oktav–Quint (T1-16,21-40,45-64)
- **Entwicklungsstrategie:** Reduktion und Wiederaufnahme; **Transformationen:** JC-T011 Unterbrechung und Wiederaufnahme, JC-T014 Kontrollierte Reduktion
- **Merkmale:** ohne HM/GS
- **MIDI:** `JC-S36_Reduktion_und_Wiederaufnahme.mid` · Spuren LF, LB, KB, AR · 1351 Noten · Funktionen {'A': 1351}
- **Evidenz:** N – nachgewiesenes Verfahren

#### JC-S37 Wandernde Lücke

- **Zweck:** Gleiches Tempo, steigende Unruhe durch Lücken und Stolpern statt durch Dichte.
- **Eckdaten:** 32 Takte 4/4, 104 BPM (Vorschlag), Tonart D, Äolisch (natürliches Moll)
- **XYZ:** (0,30 / 0,50 / 0,60), Z-Charakter psychologisch · konstante Position
- **Harmonie:** ab T1 JC-H001 Kalte Quintleere
- **Schichten:**
  - LF aus Harmonie
  - KB: JC-B010 Stoischer Achtelbass (T1-16)
  - KB: JC-B018 Stolper-Bass (T17-32)
  - AR: JC-Q042 Zelle mit wandernder Lücke
- **Entwicklungsstrategie:** Stasis; **Transformationen:** JC-T010 Akzentgruppen-Variation
- **Merkmale:** ohne HM/GS
- **MIDI:** `JC-S37_Wandernde_Luecke.mid` · Spuren LF, KB, AR · 482 Noten · Funktionen {'A': 370, 'T': 112}
- **Evidenz:** E – eigenständige Gestaltung

#### JC-S38 Phasenzelle (gemeinsame SYNTH-Fähigkeit)

- **Zweck:** Fünftoniger Zyklus gegen 16tel-Raster. Für Carpenter nicht belegt; Hypothese.
- **Eckdaten:** 32 Takte 4/4, 112 BPM (Vorschlag), Tonart A, Äolisch (natürliches Moll)
- **XYZ:** (0,50 / 0,60 / 0,80), Z-Charakter mechanisch · konstante Position
- **Harmonie:** ab T1 JC-H004 Quintenstapel mit None
- **Schichten:**
  - LF aus Harmonie
  - KB: JC-B009 Pulsierender Achtelbass
  - AR: JC-Q043 Phasenzelle 5 gegen 16
- **Entwicklungsstrategie:** Stasis; **Transformationen:** JC-T015 Phasenversatz
- **Merkmale:** ohne HM/GS
- **MIDI:** `JC-S38_Phasenzelle_gemeinsame_SYNTH_Faehigkeit.mid` · Spuren LF, KB, AR · 771 Noten · Funktionen {'A': 668, 'T': 103}
- **Evidenz:** H – Hypothese (markierte Ableitung)

#### JC-S39 Siebener-Kette im 7/8

- **Zweck:** Siebentonfigur über Drone; seltene Rufe.
- **Eckdaten:** 32 Takte 7/8, 126 BPM (Vorschlag), Tonart H, Äolisch (natürliches Moll)
- **XYZ:** (0,30 / 0,60 / 0,70), Z-Charakter mechanisch · konstante Position
- **Harmonie:** ab T1 JC-H001 Kalte Quintleere
- **Schichten:**
  - LF aus Harmonie
  - LB: JC-B001 Tiefer Grundton-Drone
  - AR: JC-Q045 Siebener-Kette
  - TU: JC-M029 Oktavsprung-Signal, Oktave -1 an T9, T25
- **Entwicklungsstrategie:** Stasis; **Transformationen:** JC-T012 Langfristige Stasis
- **Merkmale:** ohne HM/GS
- **MIDI:** `JC-S39_Siebener_Kette_im_7_8.mid` · Spuren LF, LB, AR, TU · 231 Noten · Funktionen {'A': 167, 'T': 64}
- **Evidenz:** E – eigenständige Gestaltung

#### JC-S40 Cluster-Feld mit Kriechbass

- **Zweck:** Wanderndes Cluster, abwärts kriechender Bass, ein Stich.
- **Eckdaten:** 32 Takte 4/4, 60 BPM (Vorschlag), Tonart D♭, Chromatisch (frei, nur Akkordtöne + autorisierte Töne)
- **XYZ:** (0,05 / 0,40 / 0,95), Z-Charakter psychologisch · konstante Position
- **Harmonie:** ab T1 JC-H062 Wanderndes Cluster
- **Schichten:**
  - LF aus Harmonie
  - LB: JC-B030 Chromatischer Kriechbass abwärts
  - ST (Note 36) an T21
- **Entwicklungsstrategie:** Blockverschiebung; **Transformationen:** JC-T001 Blocktransposition
- **Merkmale:** ohne AR, ohne HM/GS
- **MIDI:** `JC-S40_Cluster_Feld_mit_Kriechbass.mid` · Spuren LF, LB, ST · 50 Noten · Funktionen {'A': 14, 'U': 25, 'T': 10, 'ST': 1}
- **Evidenz:** E – eigenständige Gestaltung

#### JC-S41 Lydisches Glas über Pedal

- **Zweck:** Lydischer Durklang hoch, gläserne Sequenz, tiefer Drone.
- **Eckdaten:** 32 Takte 4/4, 76 BPM (Vorschlag), Tonart F, Lydisch
- **XYZ:** (0,90 / 0,30 / 0,40), Z-Charakter neutral · konstante Position
- **Harmonie:** ab T1 JC-H072 Lydische Helle
- **Schichten:**
  - LF aus Harmonie
  - LB: JC-B001 Tiefer Grundton-Drone
  - AR: JC-Q034 Lydisches Glas
- **Entwicklungsstrategie:** Stasis; **Transformationen:** JC-T012 Langfristige Stasis
- **Merkmale:** ohne HM/GS
- **MIDI:** `JC-S41_Lydisches_Glas_ueber_Pedal.mid` · Spuren LF, LB, AR · 389 Noten · Funktionen {'A': 293, 'T': 96}
- **Evidenz:** H – Hypothese (markierte Ableitung)

#### JC-S42 Bluesiges Riffgerüst

- **Zweck:** Zweitakt-Bassriff über Quint-Gerüst; Kraft mit rockiger Herkunft.
- **Eckdaten:** 32 Takte 4/4, 116 BPM (Vorschlag), Tonart E, Äolisch (natürliches Moll)
- **XYZ:** (0,30 / 0,85 / 0,40), Z-Charakter neutral · konstante Position
- **Harmonie:** ab T1 JC-H066 Riffgerüst i–♭VII–♭VI
- **Schichten:**
  - LF aus Harmonie
  - KB: JC-B052 Zweitakt-Bassriff
- **Entwicklungsstrategie:** Stasis; **Transformationen:** JC-T012 Langfristige Stasis
- **Hinweis:** Riff bleibt eigenständig; Reibungen gegen ♭VII/♭VI sind Tonvorratstöne.
- **Merkmale:** ohne AR, ohne HM/GS
- **MIDI:** `JC-S42_Bluesiges_Riffgeruest.mid` · Spuren LF, KB · 280 Noten · Funktionen {'A': 136, 'T': 144}
- **Evidenz:** I – begründete Interpretation

## 12. Langfristige Entwicklung

Bei unveränderter XYZ-Position wird **keine** gerichtete Eskalation oder Deeskalation erzwungen. Bewusst unveränderte, hypnotische Musik ist ein legitimes Ergebnis. Variation geschieht nicht in festen Zeitabständen, sondern an Phrasengrenzen und nach der gewählten Strategie.

| Strategie | Prinzip | 8 Takte | 16 Takte | 32 Takte | 64 Takte | Studien |
|---|---|---|---|---|---|---|
| Stasis | Alle Schichten unverändert. | Keine Änderung. | Keine Änderung. | Keine Änderung; optional Velocity-Mikrovariation. | Keine Änderung über 64 Takte. | JC-S20, JC-S01, JC-S06 |
| Rotation | Gleich viele aktive Schichten, gekoppelte Wechsel. | – | Eine Schicht raus, eine rein. | Zweiter gekoppelter Wechsel oder Rückkehr. | Zyklus über 2–4 Wechsel, ohne Netto-Steigerung. | JC-S35, JC-S07, JC-S21 |
| Atmung | Schichten blenden ein und aus, Mittelwert konstant. | Eine Schicht setzt aus. | Rückkehr der Schicht. | Zweite Schicht atmet versetzt. | Überlagerte Ein-/Aus-Zyklen. | JC-S19, JC-S05 |
| Wanderung | Ein Motiv wechselt Rolle oder Register. | – | Wechsel der Rolle. | Zweiter Wechsel. | Rückkehr zur Ausgangsrolle. | JC-S27, JC-S11, JC-S31 |
| Umfärbung | Figur bleibt, Unterbau wechselt. | – | Zweiter Klang. | Klangfolge durchlaufen. | Neue Achse ab Takt 33. | JC-S27, JC-S29, JC-S09, JC-S10 |
| Ereignisfeld | Fläche + seltene Ereignisse. | 0–1 Ereignis. | 1–2 Ereignisse. | 2–5 Ereignisse. | 4–10 Ereignisse, Abstandsreihe unverändert. | JC-EF01–EF12, JC-S02 |
| Blockverschiebung | Ganze Zelle/Fläche rückt um Halbton. | Grundstufe. | Verschiebung für 4–8 Takte. | Rückkehr und Wiederholung. | Pendel ohne Steigerung. | JC-S22, JC-S18, JC-S40 |
| Reduktion und Wiederaufnahme | Phasen mit nur einem Element. | – | Absturz auf Drone (4 Takte). | Identische Wiederkehr. | Zweiter Absturz, Wiederkehr. | JC-S36, JC-S17 |

**64-Takt-Modellstudien:** JC-S02 (Ereignisfeld), JC-S09 (Umfärbung), JC-S19 (Atmung), JC-S20 (Stasis), JC-S27 (Wanderung), JC-S29 (Umfärbung), JC-S35 (Rotation), JC-S36 (Reduktion und Wiederaufnahme), JC-EF01 (Ereignisfeld), JC-EF02 (Ereignisfeld), JC-EF05 (Ereignisfeld), JC-EF08 (Ereignisfeld), JC-EF10 (Ereignisfeld).

**Entwicklung durch tatsächliche XYZ-Veränderung (getrennt zu behandeln):** JC-S16 Mechanische Unruhe, JC-S17 Akuter Horror durch Reduktion, JC-S18 Akuter Horror durch Verdichtung. Diese Verdichtungen und Reduktionen sind nur zulässig, wenn der Anwender Y oder Z tatsächlich verändert.

**Wie Entwicklung ohne neue Akkordfolge entsteht (Zusammenfassung):** Schichtwechsel (Rotation, Atmung), Rollen- und Registerwanderung, Umfärbung unter fester Figur, Blockverschiebung, Ereignisse im Feld, Reduktion mit identischer Wiederkehr. Neue Noten sind die seltenste Quelle von Veränderung.

## 13. Abgestufte Stilregeln

Stufen: **V** zwingend · **S** starke Präferenz · **W** schwache Präferenz · **O** Option · **U** unbelegt. Keine absoluten Verbote aus fehlenden Belegen.

| Regel | Stufe |
|---|---|
| Sequencer-Zellen bevorzugt kurz (2–4 Töne); Motive 2–8 Töne zulässig | S |
| Intervallkontur als Identitätsanker; Einzeltonvariation erlaubt | S |
| Gemeinsames Tonzentrum von Pedal und Figur; Bass darf schreiten und Kreisfolgen tragen | S |
| Kein V–I als Formschluss; Abschluss durch Schichtabbau | S |
| Höchstens eine Veränderung je Ereignispunkt (Standard, Strategien dürfen abweichen) | W |
| Höchste Dramatik durch Reduktion; Verdichtung als Option | S |
| Referenzpuls exakt; Handschichten leicht humanisiert (nicht in den MIDI-Studien, Engine-Aufgabe) | S |
| Ungerade Akzentgruppen und Triolen als Option | W |
| Mittellage bei Dialog ausdünnen | V |
| Stich technisch fest (Note 36), nie transponiert | V |
| Stich asynchron zum Puls | W |
| Ein Teil der Vorlagen ist pulslos | V |
| Diatonische Moll-Kreisfolgen ohne Dominante | S |
| Melodische Identität bei Umfärbung erhalten | S |
| Gemeinsames Raster; unabhängige Perioden nur als Option | S |
| Ereignisarmut ist ein Wert (16+ Takte ohne neues Ereignis) | S |
| Septimen, Nonen, Modi als gekennzeichnete Option (H) | O |
| Tritonus als Kernintervall | U |

## 14. Technische Anforderungen an die Engine

Gemeinsame Fähigkeiten statt einer zweiten Kompositionsengine. Was das Carpenter-Profil von der gemeinsamen Engine braucht:

| Fähigkeit | Beispiele | Status |
|---|---|---|
| Halteton über beliebig viele Takte (LF, LB) ohne Neuanschlag | JC-B001, JC-H001, alle EF | gemeinsam |
| Mehrstimmige LF bis 5 Stimmen, exakte weite Lage | JC-H046, JC-H073, JC-H081 | gemeinsam |
| Unabhängiges Pedal mit Dissonanz-Autorisierung | JC-B005, JC-B006, JC-H068 | gemeinsam |
| Schalter „Folgt Akkorden“ je Rolle | JC-B010 vs. JC-B009 | vorhanden |
| Tonfunktions-Berechnung A/T/V/F/U gegen klingenden Kontext; keine Korrektur von F/U | alle | gemeinsam (wie Herrmann) |
| Blocktransposition ganzer Schichten mit Autorisierung | JC-T001, JC-S18, JC-S22 | gemeinsam |
| Schicht-Scheduler (Ein/Aus nach Taktbereichen, gekoppelte Wechsel) | JC-T007, JC-S35 | gemeinsam |
| Ereignisfeld mit deterministischer Abstandsreihe und Kandidatenrotation | JC-EF01–12 | gemeinsam |
| Akzentmuster unabhängig vom Taktmaß (Velocity) | JC-R024, JC-R028 | gemeinsam |
| Taktarten 5/4, 7/8, 9/8, 6/8, 12/8 | JC-R024–R036, JC-S22, JC-S39 | vorhanden (Takt einstellbar) |
| Unabhängige Tonhöhenzyklen / Perioden (Phasenversatz) | JC-Q043, JC-Q044, JC-R062 | gemeinsame SYNTH-Fähigkeit; im Carpenter-Profil H, niedrig gewichtet |
| Kanon: koordinierte Parallelstimmen mit Zeitversatz | JC-S13, JC-S09 | gemeinsam |
| Rollenwanderung eines Motivs | JC-T006, JC-S27 | gemeinsam |
| Gate-Listen je Einsatz | JC-R038–R040 | gemeinsam |

**Nicht vorausgesetzt:** elektronische Percussion-Spur, MIDI-CC (CC74/CC1), zusätzliche MIDI-Ausgänge, bestimmte Synthesizer. Filter-, LFO- und Delay-Bewegungen werden nicht durch Notenfolgen simuliert; das „Ferne Echo“ (JC-M004) ist komponierte Dynamik und kein Delay-Ersatz.
