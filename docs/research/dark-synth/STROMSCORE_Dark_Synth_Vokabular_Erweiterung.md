# STROMSCORE – Dark Synth: Konsolidierung und Vokabularerweiterung

*Erweiterungsbibliothek zum Carpenter-Profil · Stand: 28. November 2026*

Dark Synth ersetzt langfristig das John-Carpenter-Profil. Die 405 Carpenter-IDs (JC-…) bleiben **unverändert** das Fundament und werden hier nicht erneut ausgegeben. Diese Datei enthält ausschließlich neue Vorlagen mit eigenen DS-IDs und verweist, wo ein Verfahren schon existiert, auf die vorhandene JC-ID.

| Bibliothek | neu | Orientierung |
|---|---|---|
| Harmonik (DS-H) | 65 | 40–60 |
| Bassfiguren und -rotationen (DS-B) | 21 | 20–30 |
| Rhythmus (DS-R) | 13 | 25–40 mit Q |
| Sequencer (DS-Q) | 22 | 25–40 mit R |
| Tupfer-Motive (DS-TU) | 28 | 30–40 mit TO |
| Tupfer-Operationen (DS-TO) | 7 | 30–40 mit TU |
| Lead-Motive (DS-HM) | 18 | 15–25 |
| Entwicklung und Übergänge (DS-E) | 18 | 15–20 |
| Klangmodulation (DS-K, getrennt) | 10 | – |
| Studien (DS-S) | 30 | 20–30 |
| optionale Modulationsstudien (DS-MS) | 4 | getrennt |

Alle konkreten Tonfolgen, Klangketten und Rhythmen sind **eigene Konstruktionen (E)**. Das Evidenzfeld jeder Vorlage bezeichnet das zugrunde liegende *Verfahren*. Keine Vorlage kopiert ein Soundtrack-Thema.

## Inhalt

1. Konventionen
2. Abgleich mit dem vorhandenen Vokabular
3. Korrigierte Regeln und geprüfte Recherche-Angaben
4. Engine: vorhanden und neu
5. DS-H Harmonik
6. DS-B Bass
7. DS-R Rhythmus und DS-Q Sequencer
8. Tupfer (TU) als eigenständige Rolle
9. DS-HM optionale Lead-Motive
10. DS-E Entwicklung und Übergänge
11. Klangmodulation (getrennt)
12. DS-S Studien
13. XYZ-Feld
14. Prioritäten für die Umsetzung
15. Quellenlage und Grenzen

## 1. Konventionen

Es gelten alle Konventionen der Carpenter-Bibliothek: 960 PPQ, relative Tonhöhen (0 = Grundton der Tonart), Rollenregister, Tonfunktionen A/T/V/F/U, Evidenz N/I/H/E, XYZ-Anker und Gültigkeitsbereich.

Neu bzw. präzisiert:

- **Akkordnamen** stehen in der Bezugstonart **A** (Stufe 0 = A) und werden maschinell gegen die klingenden Tonklassen geprüft. Schreibweise mit ♯/♭; **H** = B natural, **B♭** = B-flat.
- **Strenge Verträglichkeit:** In allen DS-Studien gilt ein Tonvorratston nicht automatisch als T, wenn er eine kleine None über einem klingenden Akkordton bildet. Solche Töne müssen ausdrücklich als F oder U autorisiert sein.
- **Fester Oberbau (`*`):** Bei Bassrotationen bleibt die LF-Stimmenlage identisch; der Klangname ergibt sich aus Oberbau + Basston.
- **ST** bleibt Kanal 7, Note 36, nie transponiert. Kanäle 1–9 wie bisher: LF 1, KF 2, LB 3, KB 4, AR 5, TU 6, ST 7, GS 8, HM 9.
- **Perioden** werden in Sechzehnteln angegeben. Die Wiederkehr am Taktanfang ist das kleinste gemeinsame Vielfache (kgV) aus Periode und Taktlänge; bei Ton- und Rhythmuszyklus zusätzlich das kgV beider Zyklen. Alle Angaben sind nachgerechnet.

## 2. Abgleich mit dem vorhandenen Vokabular

| Verfahren aus der Dark-Synth-Recherche | bereits vorhanden (JC) | neu (DS) | Bewertung |
|---|---|---|---|
| Handgespielte Ostinati über Referenzpuls | JC-Q001–JC-Q067, Regel 7 | DS-Q (Ergänzung) | vorhanden; DS ergänzt Farben |
| Hinzufügen und Entfernen von Schichten | JC-T007, JC-T011, JC-T013, JC-T014 | – | vorhanden |
| Blocktransposition | JC-T001, JC-H015, JC-H084 | DS-H Kraftvoller Halbtonblock | vorhanden; eine kraftvolle Variante neu |
| Reduktion und Wiederaufnahme | JC-T011, JC-T014, JC-S36 | DS-E07 Gefrieren | vorhanden; Gefrieren neu |
| Unabhängige Perioden / Phasen | JC-Q043, JC-Q044, JC-R062, JC-R063, JC-T015 | DS-R 10/12/13er, DS-E02 | Fähigkeit vorhanden; neu sind 10/12/13er-Perioden mit berechneter Wiederkehr |
| Glocken, Kanon | JC-M018, JC-M040, JC-S13 | DS-TU T1, DS-Q Glocken-Ostinato | vorhanden; Glocke als eigenständiges TU-Ereignis neu |
| Echo als komponierte Dynamik | JC-M004 | DS-TO Echo-Operationen | neu: Echo bezieht sich auf die tatsächlich gespielten Sequencer-Töne |
| Gate-Variation | JC-R038–JC-R040, JC-T009 | DS-E08 Gate-Atmung (pro Abschnitt, überlappungsfrei) | erweitert |
| Akzentwanderung | JC-R059, JC-T010 | – | vorhanden |
| Ereignisfelder mit Abstandsreihe | JC-EF01–JC-EF12 | DS-S10, DS-S16, DS-S29, DS-S30 | vorhanden; neue Felder mit TU-Gedächtnis |
| Hexatonischer Pol | JC-H041 Kalte Mediante (identisch) | – | **Redundanz erkannt**: keine neue Vorlage, Studie DS-S12 nutzt JC-H041 |
| Dur über fremdem Pedal | JC-H068 | – | vorhanden |
| Großterz-Zyklus | JC-H085 (Dur, aufwärts) | DS-H Großterzfall in Dur-Septakkorden, Große Terz im Puls | Variante neu (maj7, abwärts; Puls-Fassung) |
| Dur-Septakkord über Moll (Schattenpaar) | – | DS-H DH1 (6 Vorlagen), DS-Q01 | neu |
| Bassrotation unter festem Oberbau | Fähigkeit: gehaltene Oberstimmen | DS-H DH2 (8 Vorlagen) | neu als Vokabular |
| Mehrgliedrige Ketten mit gemeinsamen Tönen | JC-H023–JC-H030 (bis 5 Glieder) | DS-H DH3 (9 Vorlagen, bis 12 Glieder) | erweitert |
| Sakral und choralartig | – | DS-H DH6, DS-HM Choral-Melodie | neu |
| Tarnhelm (Moll → Moll große Terz tiefer) | – | DS-H Tarnhelm-Schritt, Doppel-Tarnhelm | neu |
| Nostalgische Dur-Harmonik mit Moll-iv | – | DS-H DH8 (8 Vorlagen) | neu |
| Spieluhr-Motive | – | DS-TU T2, DS-Q Spieluhr-Sequenz, DS-HM Spieluhr-Lead | neu |
| TU-Motivgedächtnis, Fragment-Exposition | Motivgedächtnis im Kern vorhanden | DS-TU T4, DS-TO, DS-E01, DS-E06 | neu für die Rolle TU |
| Klang ohne Notenänderung | – | DS-K, DS-MS (getrennt) | neu, optional |

**Tonklassen-Verwandtschaften:** Keine DS-Sequenz und kein DS-Motiv teilt die Tonklassenfolge (ab drei Tönen) einer JC-Vorlage; die Erweiterung ist auch auf dieser Ebene neu.

## 3. Korrigierte Regeln und geprüfte Recherche-Angaben

### 3.1 Feste Grenzen werden zu Präferenzen

| Vorschlag der Recherche | neue Fassung | Stufe |
|---|---|---|
| Pendel höchstens 4 Zyklen unverändert (P-1) | Keine Höchstzahl. Pendel dürfen beliebig lange unverändert laufen; Abwechslung entsteht wahlweise durch Bass, Lage, drittes Glied, Tupfer oder Klang. | Präferenz |
| Pendel alle 16–32 Takte um ein drittes Glied erweitern (P-3) | Option. Vorlagen mit drittem Glied stehen bereit (DS-H Pendel mit drittem Glied, Schattenpaar mit Fluchtweg). | Option |
| Mindestens 60 % der TU-Ereignisse aus Keimen | Keine Quote. TU kann ganz aus Keimen, ganz aus Einzeltönen oder gemischt bestehen. | Präferenz |
| Periodenschichtung nur ab Z ≥ 0,4 | Keine Schwelle. Höhere Z-Werte bevorzugen sie; auch bei niedriger Z ist sie zulässig (DS-S07 bei Z 0,45, DS-S22 bei Z 0,4). | Präferenz |
| Höchstens eine Unruheachse pro Abschnitt | Präferenz, keine Regel; mehrere Unruhequellen sind möglich, wenn bewusst gewählt. | Präferenz |
| Höchstens zwei Rollen gleichzeitig mit Klangbogen | Keine pauschale Begrenzung. | Präferenz |
| Kein V–I | Kein generelles Verbot. V–I ist eine seltene Option (DS-H Choral mit Dominante, Evidenz H). | Option |
| Jeder Zustandswechsel braucht ein Gelenk | Gelenk ist Empfehlung; harter Schnitt zulässig (DS-E18). | Präferenz |
| Tarnhelm höchstens 1× pro 32 Takte | Keine Häufigkeitsgrenze; als Pendel (DS-H Tarnhelm-Schritt) ebenfalls zulässig. | Präferenz |
| Mutation alle 8–16 Takte | Keine feste Taktzahl; Mutation ist ein Ereignis, kein Takt. | Option |
| Nach Reduktion nie identische Wiederaufnahme | Beides zulässig: identisch (JC-T011) oder verändert (DS-S06). | Präferenz |
| Entwicklung/Steigerung | Nie erzwungen. Unveränderte, hypnotische Musik ist ein legitimes Ergebnis (DS-S07: 128 Takte Stasis). | Grundsatz |

### 3.2 Nachgeprüfte Angaben aus der Dark-Synth-Recherche

- **Kette K1 „Nebelgang“:** Die Recherche behauptet, jeder Schritt behalte mindestens zwei Töne. Em7 → Fmaj7/C teilt nur **E**. Korrigierte Fassung DS-H „Nebelgang“ mit Cmaj7 statt Fmaj7/C (Em7 → Cmaj7 teilt E, G, H).
- **Kette K2:** Im F♯m7 ist E die **kleine Septime (♭7)**, nicht „7“. Korrigiert in DS-H „Liegeton E über chromatischen Klängen“.
- **Bassrotation:** G unter A–C–E–G ergibt **G6/9sus4** (C ist Quarte), nicht „G6/9 ohne Terz“. B♭ ergibt **B♭maj7(9,♯11,13)** ohne Terz und Quinte. D ergibt D9sus4, F ergibt Fmaj9, C ergibt C6 – bestätigt.
- **Perioden:** 16 gegen 12 Sechzehntel → Wiederkehr nach 48 = 3 Takten; 16 gegen 10 → 80 = 5 Takte; 16 gegen 13 → 208 = 13 Takte – alle bestätigt. Zusätzlich: 7er-Periode → 7 Takte; Ton- und Rhythmuszyklus 6 gegen 8 → 3 Takte.
- **Hexatonischer Pol** (Am ↔ C♯) ist im Carpenter-Profil bereits als JC-H041 vorhanden und wurde nicht dupliziert.
- **„Schattenpaar“ (Cmaj7 über e-Moll):** Die DS-Vorlagen nutzen nur das Prinzip ♭VImaj7 über Moll; das Schatten-Arpeggio (DS-Q01) hat eine andere Kontur und ein anderes Raster als das bekannte Titelthema.

## 4. Engine: vorhanden und neu

| Fähigkeit | Status | Verwendung |
|---|---|---|
| Unabhängige Drones und Basssequenzen | vorhanden (P1) | alle Studien |
| Eigenständige AR/GS-Sequencer, vollständige Tonfolgen | vorhanden (P1) | DS-Q |
| Unabhängige rhythmische Perioden und Phasen | vorhanden (P1) | DS-R 10/12/13/7er |
| Gehaltene Oberstimmen | vorhanden (P1) | Bassrotation DH2 |
| Motivgedächtnis im Kompositionskern | vorhanden (P1) | Grundlage für TU |
| Fester Oberbau mit Klangnamen aus Oberbau + Bass | **neu** (Auswertung der Tonfunktionen gegen den Gesamtklang) | DH2 |
| TU-Zugriff auf das Motivgedächtnis mit Operationen (Fragment, Transposition, Oktave, Umkehrung, Augmentation, Anpassen, Echo) | **neu** | DS-TU, DS-TO |
| Echo aus den tatsächlich gespielten Tönen einer anderen Rolle | **neu** | DS-TO Echo |
| Lückenplatzierung (TU sucht eine Stelle ohne Sequencer-Einsatz) | **neu** | DS-S mit TU-Ereignissen ohne feste Position |
| Gefrieren (Sequencer stoppt, Ton bleibt) | **neu** | DS-S13, DS-S06 |
| Gate-Kurve je Abschnitt ohne Überlappung | **neu** (Erweiterung der vorhandenen Gate-Listen) | DS-S22 |
| Ein-Schritt-Mutation ab einem Takt | **neu** | DS-S22, DS-S17 |
| Strenge Verträglichkeit (♭9-Prüfung) | **neu** | alle DS-Studien |
| Abstrakte Klangkurven mit eigener Periode, Ausgabe auf frei zuordenbare Controller | **neu, optional** | DS-K, DS-MS |

## 5. DS-H Harmonik

Segmente laufen zyklisch, solange die Vorlage aktiv ist. Ein einzelner Klang darf beliebig lange stehen.

### DH1 – Schattenpaar (Dur-Septakkord über Moll)

#### DS-H01 Schattenpaar ♭VImaj7

- **Charakter:** Moll und Dur-Septakkord auf ♭VI teilen drei Töne; ein heller Klang über dunklem Zentrum.
- **Klangfolge (in A):** T1–4 Am · T5–8 Fmaj7
- **Periode:** 8 Takte
- **Modus / Bass:** Äolisch (natürliches Moll) / Akkordgrundton
- **XYZ:** Anker (0,57 / 0,30 / 0,20); X 0,35–0,80 · Y 0,00–0,60 · Z 0,00–0,40; Z-Charakter neutral
- **Evidenz:** I – begründete Interpretation; Konstruktion E

#### DS-H02 Schattenpaar mit Fluchtweg

- **Charakter:** Drei Pendelzyklen, dann ein Ausweg über Dm(add9); 20-Takt-Periode.
- **Klangfolge (in A):** T1–2 Am · T3–4 Fmaj7 · T5–6 Am · T7–8 Fmaj7 · T9–10 Am · T11–12 Fmaj7 · T13–14 Dm(add9) · T15–16 Fmaj7 · T17–20 Am
- **Periode:** 20 Takte (gegen 8er-Phrasen: Wiederkehr nach 40 Takten)
- **Modus / Bass:** Äolisch (natürliches Moll) / Akkordgrundton
- **XYZ:** Anker (0,57 / 0,35 / 0,20); X 0,35–0,80 · Y 0,00–0,70 · Z 0,00–0,40; Z-Charakter neutral
- **Evidenz:** I – begründete Interpretation; Konstruktion E

#### DS-H03 Schattenpaar über Grundtonpedal

- **Charakter:** Der Grundton bleibt im Bass liegen; im Fmaj7 ist er Terz und Akkordton.
- **Klangfolge (in A):** T1–4 Am7 · T5–8 Fmaj7
- **Periode:** 8 Takte
- **Modus / Bass:** Äolisch (natürliches Moll) / Pedal auf dem Grundton (unabhängig)
- **XYZ:** Anker (0,53 / 0,35 / 0,20); X 0,30–0,75 · Y 0,00–0,70 · Z 0,00–0,40; Z-Charakter neutral
- **Evidenz:** I – begründete Interpretation; Konstruktion E

#### DS-H04 Schattenpaar in Dur

- **Charakter:** Imaj7 und IVmaj7; warm, schwebend, nostalgisch.
- **Klangfolge (in A):** T1–4 Amaj7 · T5–8 Dmaj7
- **Periode:** 8 Takte
- **Modus / Bass:** Ionisch (Dur) / Akkordgrundton
- **XYZ:** Anker (0,75 / 0,30 / 0,17); X 0,55–0,95 · Y 0,00–0,60 · Z 0,00–0,35; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H05 Schattenpaar mit None

- **Charakter:** Beide Klänge mit None; weicher, elektronisch-nostalgisch.
- **Klangfolge (in A):** T1–4 Am(add9) · T5–8 Fmaj9
- **Periode:** 8 Takte
- **Modus / Bass:** Äolisch (natürliches Moll) / Akkordgrundton
- **XYZ:** Anker (0,62 / 0,30 / 0,20); X 0,40–0,85 · Y 0,00–0,60 · Z 0,00–0,40; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H06 Dreifacher Schatten

- **Charakter:** Das Pendel wird durch Cmaj7 zu einem Dreiklang-Kreis erweitert.
- **Klangfolge (in A):** T1–4 Am · T5–8 Fmaj7 · T9–12 Cmaj7 · T13–16 Fmaj7
- **Periode:** 16 Takte
- **Modus / Bass:** Äolisch (natürliches Moll) / Akkordgrundton
- **XYZ:** Anker (0,62 / 0,35 / 0,20); X 0,40–0,85 · Y 0,00–0,70 · Z 0,00–0,40; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

### DH2 – Bassrotation unter festem Oberbau

#### DS-H07 Bassrotation unter Am7-Oberbau

- **Charakter:** Oberbau A–C–E–G bleibt identisch; acht Basstöne erzeugen acht Bedeutungen.
- **Klangfolge (in A):** T1–2 Am7 · T3–4 Fmaj9 · T5–6 D9sus4 · T7–8 Fmaj9 · T9–10 Am7 · T11–12 B♭maj7(9,♯11,13) · T13–14 G6/9sus4 · T15–16 Am7
- **Fester Oberbau:** 1 ♭3 5 ♭7; nur der Bass wandert (1, ♭6, 4, ♭6, 1, ♭2, ♭7, 1)
- **Periode:** 16 Takte
- **Modus / Bass:** Äolisch (natürliches Moll) / Akkordgrundton
- **XYZ:** Anker (0,50 / 0,35 / 0,25); X 0,20–0,80 · Y 0,00–0,70 · Z 0,00–0,50; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H08 Pendel im Bass

- **Charakter:** Der Mollklang bleibt stehen; nur der Bass pendelt zwischen 1 und ♭6.
- **Klangfolge (in A):** T1–4 Am · T5–8 Fmaj7
- **Fester Oberbau:** 1 ♭3 5; nur der Bass wandert (1, ♭6)
- **Periode:** 8 Takte
- **Modus / Bass:** Äolisch (natürliches Moll) / Akkordgrundton
- **XYZ:** Anker (0,53 / 0,30 / 0,20); X 0,30–0,75 · Y 0,00–0,60 · Z 0,00–0,40; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H09 Bassrotation unter Mollklang, dorisch

- **Charakter:** Am bleibt; der Bass wandert über C, D und F♯ und hellt auf.
- **Klangfolge (in A):** T1–4 Am · T5–8 C6(no5) · T9–12 D9(no3) · T13–16 F♯m7♭5
- **Fester Oberbau:** 1 ♭3 5; nur der Bass wandert (1, ♭3, 4, 6)
- **Periode:** 16 Takte
- **Modus / Bass:** Dorisch / Akkordgrundton
- **XYZ:** Anker (0,62 / 0,30 / 0,23); X 0,40–0,85 · Y 0,00–0,60 · Z 0,00–0,45; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H10 Bassrotation unter Cmaj7-Oberbau

- **Charakter:** Heller Oberbau C–E–G–H über vier Basstönen.
- **Klangfolge (in A):** T1–4 Cmaj7 · T5–8 Am9 · T9–12 Fmaj9♯11(no3) · T13–16 Em(♭6)
- **Fester Oberbau:** ♭3 5 ♭7 2+1Okt; nur der Bass wandert (♭3, 1, ♭6, 5)
- **Periode:** 16 Takte
- **Modus / Bass:** Äolisch (natürliches Moll) / Akkordgrundton
- **XYZ:** Anker (0,75 / 0,30 / 0,20); X 0,55–0,95 · Y 0,00–0,60 · Z 0,00–0,40; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H11 Halbton-Bassrotation

- **Charakter:** Am bleibt; der Bass weicht einen Halbton nach oben und unten aus.
- **Klangfolge (in A):** T1–4 Am · T5–8 B♭maj9♯11(no3,no5) · T9–12 Am · T13–16 G♯+(♭9)
- **Fester Oberbau:** 1 ♭3 5; nur der Bass wandert (1, ♭2, 1, 7)
- **Periode:** 16 Takte
- **Modus / Bass:** Chromatisch (frei, nur Akkordtöne + autorisierte Töne) / Akkordgrundton
- **XYZ:** Anker (0,20 / 0,35 / 0,75); X 0,00–0,40 · Y 0,00–0,70 · Z 0,50–1,00; Z-Charakter psychologisch
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H12 Rufbass-Rotation unter Quinte

- **Charakter:** Nur A und E oben; der Bass macht daraus sus2, maj7 und 6.
- **Klangfolge (in A):** T1–4 A5 · T5–8 Dsus2 · T9–12 Fmaj7(no5) · T13–16 C6(no5)
- **Fester Oberbau:** 1 5; nur der Bass wandert (1, 4, ♭6, ♭3)
- **Periode:** 16 Takte
- **Modus / Bass:** Äolisch (natürliches Moll) / Akkordgrundton
- **XYZ:** Anker (0,55 / 0,25 / 0,20); X 0,30–0,80 · Y 0,00–0,50 · Z 0,00–0,40; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H13 Dur-Oberbau mit wanderndem Bass

- **Charakter:** A-Dur bleibt; der Bass erzeugt F♯m7, Dmaj9 und die Terzlage.
- **Klangfolge (in A):** T1–4 A · T5–8 F♯m7 · T9–12 Dmaj9(no3) · T13–16 A/C♯
- **Fester Oberbau:** 1 3 5; nur der Bass wandert (1, 6, 4, 3)
- **Periode:** 16 Takte
- **Modus / Bass:** Ionisch (Dur) / Akkordgrundton
- **XYZ:** Anker (0,80 / 0,30 / 0,20); X 0,60–1,00 · Y 0,00–0,60 · Z 0,00–0,40; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H14 Choral-Oberbau über schreitendem Bass

- **Charakter:** Am in Choral-Lage, der Bass schreitet A–G–F–E.
- **Klangfolge (in A):** T1–4 Am · T5–8 G6/9sus4 · T9–12 Fmaj7 · T13–16 Am/E
- **Fester Oberbau:** ♭3 5 1+1Okt; nur der Bass wandert (1, ♭7, ♭6, 5)
- **Periode:** 16 Takte
- **Modus / Bass:** Äolisch (natürliches Moll) / Akkordgrundton
- **XYZ:** Anker (0,53 / 0,50 / 0,20); X 0,30–0,75 · Y 0,20–0,80 · Z 0,00–0,40; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

### DH3 – Mehrgliedrige Ketten

#### DS-H15 Nebelgang

- **Charakter:** Acht Glieder, jedes behält mindestens zwei Töne; korrigierte Fassung der Recherche-Kette K1.
- **Klangfolge (in A):** T1–2 Am · T3–4 Fmaj7 · T5–6 Dm9 · T7–8 B♭maj7 · T9–10 Gsus2 · T11–12 Em7 · T13–14 Cmaj7 · T15–16 Am(add9)
- **Periode:** 16 Takte
- **Modus / Bass:** Äolisch (natürliches Moll) / Akkordgrundton
- **XYZ:** Anker (0,53 / 0,40 / 0,28); X 0,30–0,75 · Y 0,10–0,70 · Z 0,10–0,45; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H16 Terzkaskade

- **Charakter:** Grundtöne fallen in Terzen; phrygisch dunkel.
- **Klangfolge (in A):** T1–2 Am · T3–4 Fmaj7 · T5–6 Dm7 · T7–8 B♭maj7 · T9–10 Gm · T11–12 Am
- **Periode:** 12 Takte (gegen 8er-Phrasen: Wiederkehr nach 24 Takten)
- **Modus / Bass:** Phrygisch / Akkordgrundton
- **XYZ:** Anker (0,40 / 0,50 / 0,30); X 0,20–0,60 · Y 0,20–0,80 · Z 0,10–0,50; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H17 Aufsteigende Lichtkette

- **Charakter:** Sieben Glieder, die Bässe steigen in Terzen; hell, offen.
- **Klangfolge (in A):** T1–2 Am · T3–4 Cmaj7 · T5–6 Em7 · T7–8 Gmaj7 · T9–10 Dsus2 · T11–12 Fmaj7 · T13–16 Am
- **Periode:** 16 Takte
- **Modus / Bass:** Dorisch / Akkordgrundton
- **XYZ:** Anker (0,70 / 0,40 / 0,20); X 0,50–0,90 · Y 0,10–0,70 · Z 0,00–0,40; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H18 Mollkreis mit Moll-v

- **Charakter:** Die Moll-v ersetzt die Dominante; schließt ohne Kadenz.
- **Klangfolge (in A):** T1–2 Am · T3–4 Dm · T5–6 Em · T7–8 Fmaj7 · T9–10 Dm · T11–12 Em7 · T13–16 Am
- **Periode:** 16 Takte
- **Modus / Bass:** Äolisch (natürliches Moll) / Akkordgrundton
- **XYZ:** Anker (0,45 / 0,50 / 0,20); X 0,25–0,65 · Y 0,20–0,80 · Z 0,00–0,40; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H19 Dorische Wanderung

- **Charakter:** Dur-IV und ♭VII hellen den Mollkreis auf.
- **Klangfolge (in A):** T1–2 Am · T3–4 D · T5–6 Em · T7–8 G · T9–10 C · T11–14 Am
- **Periode:** 14 Takte (gegen 8er-Phrasen: Wiederkehr nach 56 Takten)
- **Modus / Bass:** Dorisch / Akkordgrundton
- **XYZ:** Anker (0,65 / 0,50 / 0,20); X 0,45–0,85 · Y 0,20–0,80 · Z 0,00–0,40; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H20 Phrygische Kette

- **Charakter:** ♭II umrahmt die Kette; fremd, ritualhaft.
- **Klangfolge (in A):** T1–2 Am · T3–4 B♭ · T5–6 Gm · T7–8 Fmaj7 · T9–10 B♭maj7 · T11–14 Am
- **Periode:** 14 Takte (gegen 8er-Phrasen: Wiederkehr nach 56 Takten)
- **Modus / Bass:** Phrygisch / Akkordgrundton
- **XYZ:** Anker (0,30 / 0,50 / 0,40); X 0,10–0,50 · Y 0,20–0,80 · Z 0,20–0,60; Z-Charakter psychologisch
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H21 Asymmetrische Kette

- **Charakter:** Verweildauern 3-1-2-2-4-2-2; kein Glied wiederholt seine Länge regelmäßig.
- **Klangfolge (in A):** T1–3 Am · T4–4 Fmaj7 · T5–6 C · T7–8 G · T9–12 Am · T13–14 Em · T15–16 Fmaj7
- **Periode:** 16 Takte
- **Modus / Bass:** Äolisch (natürliches Moll) / Akkordgrundton
- **XYZ:** Anker (0,53 / 0,50 / 0,30); X 0,30–0,75 · Y 0,20–0,80 · Z 0,10–0,50; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H22 Moll-Septkette

- **Charakter:** Septakkorde in mittlerer Lage; Wärme ohne Dur-Tonika.
- **Klangfolge (in A):** T1–2 Am7 · T3–4 Dm7 · T5–6 Em7 · T7–8 Fmaj7 · T9–10 Cmaj7 · T11–12 G · T13–16 Am7
- **Periode:** 16 Takte
- **Modus / Bass:** Äolisch (natürliches Moll) / Akkordgrundton
- **XYZ:** Anker (0,57 / 0,35 / 0,20); X 0,35–0,80 · Y 0,00–0,70 · Z 0,00–0,40; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H23 Lange Nachtkette

- **Charakter:** Zwölf Glieder, 24-Takt-Periode; Wiederkehr erst nach drei 8er-Phrasen.
- **Klangfolge (in A):** T1–2 Am · T3–4 Fmaj7 · T5–6 Dm7 · T7–8 Em7 · T9–10 Cmaj7 · T11–12 Fmaj7 · T13–14 G · T15–16 Em7 · T17–18 Am7 · T19–20 Dm9 · T21–22 Fmaj7 · T23–24 Am
- **Periode:** 24 Takte (gegen 8er-Phrasen: Wiederkehr nach 24 Takten)
- **Modus / Bass:** Äolisch (natürliches Moll) / Akkordgrundton
- **XYZ:** Anker (0,53 / 0,40 / 0,23); X 0,30–0,75 · Y 0,10–0,70 · Z 0,00–0,45; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

### DH4 – Gehaltene Oberstimme

#### DS-H24 Liegeton E über chromatischen Klängen

- **Charakter:** E bleibt in allen Klängen (5, 7, ♭3, ♭7); korrigierte Fassung von K2.
- **Klangfolge (in A):** T1–4 Am · T5–8 Fmaj7 · T9–12 C♯m · T13–16 F♯m7 · T17–20 Am
- **Periode:** 20 Takte (gegen 8er-Phrasen: Wiederkehr nach 40 Takten)
- **Modus / Bass:** Chromatisch (frei, nur Akkordtöne + autorisierte Töne) / Akkordgrundton
- **XYZ:** Anker (0,57 / 0,30 / 0,50); X 0,35–0,80 · Y 0,00–0,60 · Z 0,30–0,70; Z-Charakter psychologisch
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H25 Liegeton Grundton

- **Charakter:** A liegt in jedem Klang; die Bedeutung wechselt von 1 über 3 und 5 zur 7.
- **Klangfolge (in A):** T1–4 Am · T5–8 Fmaj7 · T9–12 Dm · T13–16 B♭maj7
- **Periode:** 16 Takte
- **Modus / Bass:** Phrygisch / Akkordgrundton
- **XYZ:** Anker (0,43 / 0,30 / 0,30); X 0,20–0,65 · Y 0,00–0,60 · Z 0,10–0,50; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H26 Liegeton C, chromatisch

- **Charakter:** C bleibt; G♯-Dur und Fm färben es unheimlich.
- **Klangfolge (in A):** T1–4 Am · T5–8 Fmaj7 · T9–12 G♯ · T13–16 Fm · T17–20 Am
- **Periode:** 20 Takte (gegen 8er-Phrasen: Wiederkehr nach 40 Takten)
- **Modus / Bass:** Chromatisch (frei, nur Akkordtöne + autorisierte Töne) / Akkordgrundton
- **XYZ:** Anker (0,38 / 0,30 / 0,53); X 0,15–0,60 · Y 0,00–0,60 · Z 0,30–0,75; Z-Charakter psychologisch
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H27 Liegeton ♭7

- **Charakter:** G bleibt über Em7, Cmaj7, Am7, D♯maj7 und G.
- **Klangfolge (in A):** T1–4 Em7 · T5–8 Cmaj7 · T9–12 Am7 · T13–16 D♯maj7 · T17–20 G
- **Periode:** 20 Takte (gegen 8er-Phrasen: Wiederkehr nach 40 Takten)
- **Modus / Bass:** Chromatisch (frei, nur Akkordtöne + autorisierte Töne) / Akkordgrundton
- **XYZ:** Anker (0,53 / 0,30 / 0,40); X 0,30–0,75 · Y 0,00–0,60 · Z 0,20–0,60; Z-Charakter psychologisch
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

### DH5 – Wechselnde Klänge über konstantem Drone

#### DS-H28 Drone-Wechsel phrygisch

- **Charakter:** Konstanter Grund-Drone; B♭ und Gm reiben phrygisch, Fmaj7 wärmt (Recherche-Kette K3).
- **Klangfolge (in A):** T1–4 Am · T5–8 B♭ · T9–12 Gm · T13–16 Fmaj7
- **Periode:** 16 Takte
- **Modus / Bass:** Phrygisch / Pedal auf dem Grundton (unabhängig)
- **XYZ:** Anker (0,33 / 0,35 / 0,40); X 0,10–0,55 · Y 0,00–0,70 · Z 0,20–0,60; Z-Charakter psychologisch
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H29 Dur-Schichten über Drone

- **Charakter:** C, G und F über dem Grundton; der Drone bleibt Tonvorratston.
- **Klangfolge (in A):** T1–4 C · T5–8 G · T9–12 F · T13–16 Am
- **Periode:** 16 Takte
- **Modus / Bass:** Äolisch (natürliches Moll) / Pedal auf dem Grundton (unabhängig)
- **XYZ:** Anker (0,62 / 0,35 / 0,20); X 0,40–0,85 · Y 0,00–0,70 · Z 0,00–0,40; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H30 Choralwechsel über Drone

- **Charakter:** Dm, Am, Fmaj7, Gsus2 über A; sakral ruhig.
- **Klangfolge (in A):** T1–4 Dm · T5–8 Am · T9–12 Fmaj7 · T13–16 Gsus2
- **Periode:** 16 Takte
- **Modus / Bass:** Äolisch (natürliches Moll) / Pedal auf dem Grundton (unabhängig)
- **XYZ:** Anker (0,53 / 0,50 / 0,17); X 0,30–0,75 · Y 0,20–0,80 · Z 0,00–0,35; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H31 Fremdklang über Drone

- **Charakter:** D♯-Dur (Tritonus) und B♭ über dem Grundton; der Drone wird autorisierte Reibung.
- **Klangfolge (in A):** T1–4 Am · T5–8 D♯ · T9–12 Am · T13–16 B♭
- **Periode:** 16 Takte
- **Modus / Bass:** Chromatisch (frei, nur Akkordtöne + autorisierte Töne) / Pedal auf dem Grundton (unabhängig)
- **XYZ:** Anker (0,20 / 0,65 / 0,75); X 0,00–0,40 · Y 0,30–1,00 · Z 0,50–1,00; Z-Charakter psychologisch
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H32 Lichtwechsel über Drone

- **Charakter:** A, D, E, D über A; warm, weit, ohne Kadenzziel.
- **Klangfolge (in A):** T1–4 A · T5–8 D · T9–12 E · T13–16 D
- **Periode:** 16 Takte
- **Modus / Bass:** Ionisch (Dur) / Pedal auf dem Grundton (unabhängig)
- **XYZ:** Anker (0,85 / 0,30 / 0,17); X 0,70–1,00 · Y 0,00–0,60 · Z 0,00–0,35; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H33 Schwebeklänge über Drone

- **Charakter:** Vier sus2-Klänge à 8 Takte über dem Grundton; sehr langsam.
- **Klangfolge (in A):** T1–8 Asus2 · T9–16 Dsus2 · T17–24 Gsus2 · T25–32 Csus2
- **Periode:** 32 Takte
- **Modus / Bass:** Äolisch (natürliches Moll) / Pedal auf dem Grundton (unabhängig)
- **XYZ:** Anker (0,68 / 0,25 / 0,15); X 0,45–0,90 · Y 0,00–0,50 · Z 0,00–0,30; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H34 Gruftklang

- **Charakter:** Offener Moll und tiefes ♭VI über dem Drone, je 16 Takte; fast regungslos.
- **Klangfolge (in A):** T1–16 Am · T17–32 F
- **Periode:** 32 Takte
- **Modus / Bass:** Äolisch (natürliches Moll) / Pedal auf dem Grundton (unabhängig)
- **XYZ:** Anker (0,15 / 0,20 / 0,15); X 0,00–0,30 · Y 0,00–0,40 · Z 0,00–0,30; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H35 Tiefe Quartklang-Ruhe

- **Charakter:** sus4 und sus2 über dem Grundton; dunkel, ohne Terz, ohne Bewegung.
- **Klangfolge (in A):** T1–16 Asus4 · T17–32 Dsus2
- **Periode:** 32 Takte
- **Modus / Bass:** Äolisch (natürliches Moll) / Pedal auf dem Grundton (unabhängig)
- **XYZ:** Anker (0,17 / 0,20 / 0,15); X 0,00–0,35 · Y 0,00–0,40 · Z 0,00–0,30; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

### DH8 – Nostalgisch und hell

#### DS-H36 Drängende Lichtkette

- **Charakter:** Rasch wechselnde Dur-Kette mit iii und vi; Aufbruch, Flucht mit Hoffnung.
- **Klangfolge (in A):** T1–2 A · T3–4 C♯m · T5–6 D · T7–8 E · T9–10 F♯m · T11–12 D
- **Periode:** 12 Takte (gegen 8er-Phrasen: Wiederkehr nach 24 Takten)
- **Modus / Bass:** Ionisch (Dur) / Akkordgrundton
- **XYZ:** Anker (0,70 / 0,80 / 0,70); X 0,40–1,00 · Y 0,60–1,00 · Z 0,40–1,00; Z-Charakter mechanisch
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

### DH7 – Unheimliche Konsonanz

#### DS-H37 Große Terz im Puls

- **Charakter:** Dur-Klänge springen in großen Terzen; kraftvoll und haltlos.
- **Klangfolge (in A):** T1–2 A · T3–4 F · T5–6 A · T7–8 C♯
- **Periode:** 8 Takte
- **Modus / Bass:** Chromatisch (frei, nur Akkordtöne + autorisierte Töne) / Akkordgrundton
- **XYZ:** Anker (0,70 / 0,80 / 0,70); X 0,40–1,00 · Y 0,60–1,00 · Z 0,40–1,00; Z-Charakter psychologisch
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

### DH6 – Sakral und choralartig

#### DS-H38 Choral i–iv–♭VI–♭VII

- **Charakter:** Langsamer Moll-Choral ohne Dominante; Orgel- oder Chorlage.
- **Klangfolge (in A):** T1–4 Am · T5–8 Dm · T9–12 F · T13–16 G · T17–20 Am
- **Periode:** 20 Takte (gegen 8er-Phrasen: Wiederkehr nach 40 Takten)
- **Modus / Bass:** Äolisch (natürliches Moll) / Akkordgrundton
- **XYZ:** Anker (0,40 / 0,65 / 0,17); X 0,20–0,60 · Y 0,30–1,00 · Z 0,00–0,35; Z-Charakter neutral
- **Evidenz:** I – begründete Interpretation; Konstruktion E

#### DS-H39 Plagaler Dur-Choral mit Moll-iv

- **Charakter:** I–IV–iv–I; die Moll-iv als einzige Trübung.
- **Klangfolge (in A):** T1–4 A · T5–8 D · T9–12 Dm · T13–16 A
- **Periode:** 16 Takte
- **Modus / Bass:** Ionisch (Dur) / Akkordgrundton
- **XYZ:** Anker (0,80 / 0,55 / 0,15); X 0,60–1,00 · Y 0,20–0,90 · Z 0,00–0,30; Z-Charakter neutral
- **Evidenz:** I – begründete Interpretation; Konstruktion E

#### DS-H40 Choral mit Dominante

- **Charakter:** i–iv–V–i. V–I ist hier bewusst zugelassen (Option, kein Standard).
- **Klangfolge (in A):** T1–4 Am · T5–8 Dm · T9–12 E · T13–16 Am
- **Periode:** 16 Takte
- **Modus / Bass:** Harmonisch Moll / Akkordgrundton
- **XYZ:** Anker (0,40 / 0,65 / 0,20); X 0,20–0,60 · Y 0,30–1,00 · Z 0,00–0,40; Z-Charakter neutral
- **Evidenz:** H – Hypothese; Konstruktion E

#### DS-H41 Requiem-Kette

- **Charakter:** Sechs Choralglieder à 4 Takte; schwer, trauernd.
- **Klangfolge (in A):** T1–4 Am · T5–8 Em · T9–12 F · T13–16 C · T17–20 Dm · T21–24 Am
- **Periode:** 24 Takte (gegen 8er-Phrasen: Wiederkehr nach 24 Takten)
- **Modus / Bass:** Äolisch (natürliches Moll) / Akkordgrundton
- **XYZ:** Anker (0,38 / 0,70 / 0,15); X 0,15–0,60 · Y 0,40–1,00 · Z 0,00–0,30; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H42 Phrygischer Choral

- **Charakter:** Ritualhafte ♭II-Wendung.
- **Klangfolge (in A):** T1–4 Am · T5–8 B♭ · T9–12 Gm · T13–16 Am
- **Periode:** 16 Takte
- **Modus / Bass:** Phrygisch / Akkordgrundton
- **XYZ:** Anker (0,30 / 0,65 / 0,30); X 0,10–0,50 · Y 0,30–1,00 · Z 0,10–0,50; Z-Charakter psychologisch
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H43 Dorischer Choral

- **Charakter:** Dur-IV aus dem Dorischen; hell sakral.
- **Klangfolge (in A):** T1–4 Am · T5–8 G · T9–12 D · T13–16 Am
- **Periode:** 16 Takte
- **Modus / Bass:** Dorisch / Akkordgrundton
- **XYZ:** Anker (0,65 / 0,55 / 0,17); X 0,45–0,85 · Y 0,20–0,90 · Z 0,00–0,35; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

### DH7 – Unheimliche Konsonanz

#### DS-H44 Tarnhelm-Schritt

- **Charakter:** Moll zu Moll eine große Terz tiefer; filmisches Zeichen der dunklen Seite (Lehman, allgemein belegt).
- **Klangfolge (in A):** T1–4 Am · T5–8 Fm
- **Periode:** 8 Takte
- **Modus / Bass:** Chromatisch (frei, nur Akkordtöne + autorisierte Töne) / Akkordgrundton
- **XYZ:** Anker (0,33 / 0,35 / 0,62); X 0,10–0,55 · Y 0,00–0,70 · Z 0,40–0,85; Z-Charakter psychologisch
- **Evidenz:** N – Verfahren nachgewiesen; Konstruktion E

#### DS-H45 Doppel-Tarnhelm

- **Charakter:** Mollklänge im Großterzzirkel abwärts; nach 12 Takten wieder am Ausgang.
- **Klangfolge (in A):** T1–4 Am · T5–8 Fm · T9–12 C♯m · T13–16 Am
- **Periode:** 16 Takte
- **Modus / Bass:** Chromatisch (frei, nur Akkordtöne + autorisierte Töne) / Akkordgrundton
- **XYZ:** Anker (0,30 / 0,45 / 0,72); X 0,10–0,50 · Y 0,10–0,80 · Z 0,50–0,95; Z-Charakter psychologisch
- **Evidenz:** I – begründete Interpretation; Konstruktion E

#### DS-H46 Spieluhr-Dur über Moll-Drone

- **Charakter:** Hoher C-Dur-Klang über dem tiefen Grundton; Unschuld im falschen Kontext.
- **Klangfolge (in A):** T1–16 C
- **Periode:** 16 Takte
- **Modus / Bass:** Äolisch (natürliches Moll) / Pedal auf dem Grundton (unabhängig)
- **XYZ:** Anker (0,75 / 0,25 / 0,53); X 0,55–0,95 · Y 0,00–0,50 · Z 0,30–0,75; Z-Charakter psychologisch
- **Evidenz:** I – begründete Interpretation; Konstruktion E

#### DS-H47 Großterzfall in Dur-Septakkorden

- **Charakter:** Amaj7–Fmaj7–C♯maj7; glänzend, ohne Halt. 12-Takt-Periode.
- **Klangfolge (in A):** T1–4 Amaj7 · T5–8 Fmaj7 · T9–12 C♯maj7
- **Periode:** 12 Takte (gegen 8er-Phrasen: Wiederkehr nach 24 Takten)
- **Modus / Bass:** Chromatisch (frei, nur Akkordtöne + autorisierte Töne) / Akkordgrundton
- **XYZ:** Anker (0,75 / 0,40 / 0,62); X 0,55–0,95 · Y 0,10–0,70 · Z 0,40–0,85; Z-Charakter psychologisch
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H48 Tritonus-Spiegel

- **Charakter:** Am und D♯-Dur: beide konsonant, zusammen ortlos.
- **Klangfolge (in A):** T1–8 Am · T9–16 D♯
- **Periode:** 16 Takte
- **Modus / Bass:** Chromatisch (frei, nur Akkordtöne + autorisierte Töne) / Akkordgrundton
- **XYZ:** Anker (0,55 / 0,30 / 0,72); X 0,35–0,75 · Y 0,00–0,60 · Z 0,50–0,95; Z-Charakter psychologisch
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H49 Lichtreibung maj7♯11

- **Charakter:** Imaj7 mit hoher ♯11 als stehende Reibung, dann IVmaj7; hell, gläsern, beunruhigend.
- **Klangfolge (in A):** T1–8 Amaj7 · T9–16 Dmaj7
- **Autorisierte Reibung im Klang:** ♯4/♭5+1Okt (U)
- **Periode:** 16 Takte
- **Modus / Bass:** Lydisch / Akkordgrundton
- **XYZ:** Anker (0,82 / 0,30 / 0,75); X 0,65–1,00 · Y 0,00–0,60 · Z 0,50–1,00; Z-Charakter psychologisch
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H50 Helle Ortlosigkeit

- **Charakter:** Zwei Dur-Septakkorde im Tritonusabstand; schön und haltlos.
- **Klangfolge (in A):** T1–4 Amaj7 · T5–8 D♯maj7
- **Periode:** 8 Takte
- **Modus / Bass:** Chromatisch (frei, nur Akkordtöne + autorisierte Töne) / Akkordgrundton
- **XYZ:** Anker (0,80 / 0,35 / 0,80); X 0,60–1,00 · Y 0,00–0,70 · Z 0,60–1,00; Z-Charakter psychologisch
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

### DH8 – Nostalgisch und hell

#### DS-H51 Nostalgie hell

- **Charakter:** Imaj7–iii7–IVmaj7–iv6; warm, wehmütig, kein Horror (Recherche-Kette K4).
- **Klangfolge (in A):** T1–4 Amaj7 · T5–8 C♯m7 · T9–12 Dmaj7 · T13–16 Dm6 · T17–20 Amaj7
- **Periode:** 20 Takte (gegen 8er-Phrasen: Wiederkehr nach 40 Takten)
- **Modus / Bass:** Ionisch (Dur) / Akkordgrundton
- **XYZ:** Anker (0,82 / 0,30 / 0,17); X 0,65–1,00 · Y 0,00–0,60 · Z 0,00–0,35; Z-Charakter neutral
- **Evidenz:** I – begründete Interpretation; Konstruktion E

#### DS-H52 Imaj7–vi9-Wiege

- **Charakter:** Zwei weiche Klänge mit gemeinsamen Tönen; Erinnerung.
- **Klangfolge (in A):** T1–4 Amaj7 · T5–8 F♯m9
- **Periode:** 8 Takte
- **Modus / Bass:** Ionisch (Dur) / Akkordgrundton
- **XYZ:** Anker (0,80 / 0,30 / 0,17); X 0,60–1,00 · Y 0,00–0,60 · Z 0,00–0,35; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H53 Weicher Kreis mit Moll-iv

- **Charakter:** I–vi–IV–iv; Doo-Wop-nahe Wärme mit Trübung am Ende.
- **Klangfolge (in A):** T1–2 A · T3–4 F♯m · T5–6 D · T7–8 Dm
- **Periode:** 8 Takte
- **Modus / Bass:** Ionisch (Dur) / Akkordgrundton
- **XYZ:** Anker (0,80 / 0,40 / 0,20); X 0,60–1,00 · Y 0,10–0,70 · Z 0,00–0,40; Z-Charakter neutral
- **Evidenz:** I – begründete Interpretation; Konstruktion E

#### DS-H54 Sus2-Lichtung

- **Charakter:** Offene sus2-Klänge, einmal F♯m7; hell und ruhig.
- **Klangfolge (in A):** T1–4 Asus2 · T5–8 Dsus2 · T9–12 F♯m7 · T13–16 Dsus2
- **Periode:** 16 Takte
- **Modus / Bass:** Ionisch (Dur) / Akkordgrundton
- **XYZ:** Anker (0,82 / 0,25 / 0,15); X 0,65–1,00 · Y 0,00–0,50 · Z 0,00–0,30; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H55 Add9-Wiege mit Moll-iv

- **Charakter:** Variante der Nostalgie-Kette mit None und maj9.
- **Klangfolge (in A):** T1–4 A(add9) · T5–8 C♯m7 · T9–12 Dmaj9 · T13–16 Dm6
- **Periode:** 16 Takte
- **Modus / Bass:** Ionisch (Dur) / Akkordgrundton
- **XYZ:** Anker (0,80 / 0,30 / 0,17); X 0,60–1,00 · Y 0,00–0,60 · Z 0,00–0,35; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H56 Warmes ♭VII

- **Charakter:** Mixolydische Wärme, A–G–D–A.
- **Klangfolge (in A):** T1–4 A · T5–8 G · T9–12 D · T13–16 A
- **Periode:** 16 Takte
- **Modus / Bass:** Mixolydisch / Akkordgrundton
- **XYZ:** Anker (0,80 / 0,50 / 0,17); X 0,60–1,00 · Y 0,20–0,80 · Z 0,00–0,35; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H57 Erinnerungs-Dur mit ♭VI

- **Charakter:** Fmaj7 als entlehnter Schatten in Dur; Sehnsucht.
- **Klangfolge (in A):** T1–4 Amaj7 · T5–8 Fmaj7 · T9–12 Amaj7 · T13–16 D6
- **Periode:** 16 Takte
- **Modus / Bass:** Ionisch (Dur) / Akkordgrundton
- **XYZ:** Anker (0,80 / 0,40 / 0,28); X 0,60–1,00 · Y 0,10–0,70 · Z 0,10–0,45; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

### DH9 – Intensiv und bedrohlich

#### DS-H58 Halbtonkette über Pedal

- **Charakter:** Am, B♭, Am, G♯m über gehaltenem Grundton; bedrängend.
- **Klangfolge (in A):** T1–2 Am · T3–4 B♭ · T5–6 Am · T7–8 G♯m
- **Periode:** 8 Takte
- **Modus / Bass:** Chromatisch (frei, nur Akkordtöne + autorisierte Töne) / Pedal auf dem Grundton (unabhängig)
- **XYZ:** Anker (0,20 / 0,70 / 0,80); X 0,00–0,40 · Y 0,40–1,00 · Z 0,60–1,00; Z-Charakter psychologisch
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H59 Diatonischer Sekundchor

- **Charakter:** A, H, C, D als enger Chorklang; Ortlosigkeit ohne Chromatik. Nur kurz einsetzen.
- **Klangfolge (in A):** T1–16 Klangfeld
- **Autorisierte Reibung im Klang:** 2 (U), 4 (U)
- **Periode:** 16 Takte
- **Modus / Bass:** Äolisch (natürliches Moll) / kein Bass empfohlen
- **XYZ:** Anker (0,30 / 0,50 / 0,70); X 0,10–0,50 · Y 0,20–0,80 · Z 0,50–0,90; Z-Charakter psychologisch
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H60 Verminderte Schwelle

- **Charakter:** Am mit verminderten Klängen auf D♯ und G♯; zuckend.
- **Klangfolge (in A):** T1–2 Am · T3–4 D♯dim · T5–6 Am · T7–8 G♯dim
- **Periode:** 8 Takte
- **Modus / Bass:** Harmonisch Moll / Akkordgrundton
- **XYZ:** Anker (0,23 / 0,65 / 0,75); X 0,00–0,45 · Y 0,30–1,00 · Z 0,50–1,00; Z-Charakter psychologisch
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H61 Moll über Tritonusbass

- **Charakter:** Am bleibt oben, der Bass fällt auf den Tritonus.
- **Klangfolge (in A):** T1–8 Am · T9–16 Am/D♯
- **Fester Oberbau:** 1 ♭3 5; nur der Bass wandert (1, ♯4/♭5)
- **Periode:** 16 Takte
- **Modus / Bass:** Chromatisch (frei, nur Akkordtöne + autorisierte Töne) / Akkordgrundton
- **XYZ:** Anker (0,20 / 0,65 / 0,80); X 0,00–0,40 · Y 0,30–1,00 · Z 0,60–1,00; Z-Charakter psychologisch
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H62 Kraftvoller Halbtonblock

- **Charakter:** Power-Quinten rücken einen Halbton auf und ab.
- **Klangfolge (in A):** T1–2 A5 · T3–4 B♭5 · T5–6 A5 · T7–8 G♯5
- **Periode:** 8 Takte
- **Modus / Bass:** Chromatisch (frei, nur Akkordtöne + autorisierte Töne) / Akkordgrundton
- **XYZ:** Anker (0,23 / 0,80 / 0,75); X 0,00–0,45 · Y 0,60–1,00 · Z 0,50–1,00; Z-Charakter mechanisch
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

### DH10 – Pendel-Varianten

#### DS-H63 Pendel 2+1

- **Charakter:** Asymmetrische Verweildauer; 3-Takt-Periode läuft gegen 4er-Phrasen.
- **Klangfolge (in A):** T1–2 Am · T3–3 Fmaj7
- **Periode:** 3 Takte (gegen 8er-Phrasen: Wiederkehr nach 24 Takten)
- **Modus / Bass:** Äolisch (natürliches Moll) / Akkordgrundton
- **XYZ:** Anker (0,53 / 0,45 / 0,40); X 0,30–0,75 · Y 0,10–0,80 · Z 0,20–0,60; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H64 Pendel 4+2 mit Farbwechsel

- **Charakter:** Das zweite Pendelglied wechselt die Farbe; 12-Takt-Periode.
- **Klangfolge (in A):** T1–4 Am · T5–6 Fmaj7 · T7–10 Am · T11–12 Dm9
- **Periode:** 12 Takte (gegen 8er-Phrasen: Wiederkehr nach 24 Takten)
- **Modus / Bass:** Äolisch (natürliches Moll) / Akkordgrundton
- **XYZ:** Anker (0,53 / 0,40 / 0,30); X 0,30–0,75 · Y 0,10–0,70 · Z 0,10–0,50; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

#### DS-H65 Pendel mit drittem Glied

- **Charakter:** Zwei Zyklen, dann C(add9) als Ausblick.
- **Klangfolge (in A):** T1–2 Am · T3–4 Fmaj7 · T5–6 Am · T7–8 Fmaj7 · T9–12 C(add9)
- **Periode:** 12 Takte (gegen 8er-Phrasen: Wiederkehr nach 24 Takten)
- **Modus / Bass:** Äolisch (natürliches Moll) / Akkordgrundton
- **XYZ:** Anker (0,57 / 0,40 / 0,20); X 0,35–0,80 · Y 0,10–0,70 · Z 0,00–0,40; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Konstruktion E

## 6. DS-B Bass

Die eigentliche Bassrotation steckt in den DH2-Harmonien (LB folgt dem Basston). Die folgenden Figuren sind eigenständige oder akkordgebundene Bassmuster.

#### DS-B01 Oktavpuls mit Lücke

- **Charakter:** Oktavpuls mit Atemloch; folgt dem Akkordgrundton.
- **Typ / Bindung:** Puls / **akkordgebunden**
- **Tonfolge:** 1 1+1Okt 1 1 1+1Okt 1 1+1Okt
- **Intervalle:** Oktave↑, Oktave↓, Prime, Oktave↑, Oktave↓, Oktave↑
- **Rhythmus:** DS-R01 Oktavpuls mit Lücke – 7 Einsätze, Periode 16 Sechzehntel; Positionen 0, 480, 960, 1920, 2400, 2880, 3360 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 1+1Okt=A, 1=A, 1=A, 1+1Okt=A, 1=A, 1+1Okt=A
- **Identität:** Rhythmus (Einsätze und Akzente bleiben); **Variationen:** JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **XYZ:** Anker (0,50 / 0,60 / 0,40); X 0,00–1,00 · Y 0,30–0,90 · Z 0,20–0,60; Z-Charakter mechanisch
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-B02 Kriechbass ♭2–7

- **Charakter:** Grundton von oben und unten im Halbton umkrochen.
- **Typ / Bindung:** Chromatisch / **eigenständig**
- **Tonfolge:** 1 ♭2 1 7-1Okt
- **Intervalle:** kleine Sekunde↑, kleine Sekunde↓, kleine Sekunde↓
- **Rhythmus:** JC-R001 Viertelpuls – 4 Einsätze, Periode 16 Sechzehntel; Positionen 0, 960, 1920, 2880 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, ♭2=U, 1=A, 7-1Okt=U
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,23 / 0,55 / 0,75); X 0,00–0,45 · Y 0,20–0,90 · Z 0,50–1,00; Z-Charakter psychologisch
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-B03 Pendel mit Vorschlag

- **Charakter:** ♭6 kurz, Quinte lang; melancholisch.
- **Typ / Bindung:** Melodisch / **eigenständig**
- **Tonfolge:** ♭6-1Okt 5-1Okt
- **Intervalle:** kleine Sekunde↓
- **Rhythmus:** DS-R02 Pendel mit Vorschlag – 4 Einsätze, Periode 16 Sechzehntel; Positionen 0, 480, 1920, 2400 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): ♭6-1Okt=T, 5-1Okt=A
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,47 / 0,30 / 0,20); X 0,25–0,70 · Y 0,00–0,60 · Z 0,00–0,40; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-B04 Rufbass

- **Charakter:** Langer Grundton, Pause, Quinte–♭6 als Antwort; dialogtauglich.
- **Typ / Bindung:** Melodisch / **eigenständig**
- **Tonfolge:** 1 5 ♭6
- **Intervalle:** Quinte↑, kleine Sekunde↑
- **Rhythmus:** DS-R03 Rufbass-Rhythmus – 3 Einsätze, Periode 32 Sechzehntel; Positionen 0, 5760, 6240 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 32 Sechzehntel; **Wiederkehr am Taktanfang:** nach 2 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 5=A, ♭6=F
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T011 Unterbrechung und Wiederaufnahme
- **XYZ:** Anker (0,40 / 0,30 / 0,23); X 0,00–0,80 · Y 0,00–0,60 · Z 0,00–0,45; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-B05 Quint-Tresillo

- **Charakter:** 3+3+2 mit Quinte auf dem dritten Schlag.
- **Typ / Bindung:** Rhythmus / **akkordgebunden**
- **Tonfolge:** 1 1 5
- **Intervalle:** Prime, Quinte↑
- **Rhythmus:** JC-R020 Tresillo – 3 Einsätze, Periode 16 Sechzehntel; Positionen 0, 1440, 2880 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 1=A, 5=A
- **Identität:** Rhythmus (Einsätze und Akzente bleiben); **Variationen:** JC-T003 Oktavverlagerung, JC-T010 Akzentgruppen-Variation
- **XYZ:** Anker (0,50 / 0,60 / 0,40); X 0,00–1,00 · Y 0,30–0,90 · Z 0,20–0,60; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-B06 Rotationsbass in Achteln

- **Charakter:** Achtelfigur, die jede Bassrotation mitgeht.
- **Typ / Bindung:** Melodisch / **akkordgebunden**
- **Tonfolge:** 1 1 1+1Okt 1 5 1 1+1Okt 1
- **Intervalle:** Prime, Oktave↑, Oktave↓, Quinte↑, Quinte↓, Oktave↑, Oktave↓
- **Rhythmus:** JC-R002 Achtelpuls – 8 Einsätze, Periode 16 Sechzehntel; Positionen 0, 480, 960, 1440, 1920, 2400, 2880, 3360 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 1=A, 1+1Okt=A, 1=A, 5=A, 1=A, 1+1Okt=A, 1=A
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,50 / 0,70 / 0,40); X 0,00–1,00 · Y 0,40–1,00 · Z 0,20–0,60; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-B07 Nostalgie-Rollbass

- **Charakter:** Gebundene Achtel Grundton–Quinte–Oktave; warm.
- **Typ / Bindung:** Melodisch / **akkordgebunden**
- **Tonfolge:** 1 5 1+1Okt 5
- **Intervalle:** Quinte↑, Quarte↑, Quarte↓
- **Rhythmus:** JC-R014 Legato-Achtel – 8 Einsätze, Periode 16 Sechzehntel; Positionen 0, 480, 960, 1440, 1920, 2400, 2880, 3360 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 5=A, 1+1Okt=A, 5=A
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **XYZ:** Anker (0,70 / 0,50 / 0,20); X 0,40–1,00 · Y 0,20–0,80 · Z 0,00–0,40; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-B08 Rotationsfigur 1–♭6–4–♭6

- **Charakter:** Die Bassrotation als eigenständige Halbe-Figur.
- **Typ / Bindung:** Schreitend / **eigenständig**
- **Tonfolge:** 1 ♭6-1Okt 4-1Okt ♭6-1Okt
- **Intervalle:** große Terz↓, kleine Terz↓, kleine Terz↑
- **Rhythmus:** JC-R006 Halbe-Puls – 2 Einsätze, Periode 16 Sechzehntel; Positionen 0, 1920 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 32 Sechzehntel; **Wiederkehr am Taktanfang:** nach 2 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, ♭6-1Okt=T, 4-1Okt=T, ♭6-1Okt=T
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **XYZ:** Anker (0,47 / 0,35 / 0,20); X 0,20–0,75 · Y 0,00–0,70 · Z 0,00–0,40; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-B09 Verschobener Doppelschlag

- **Charakter:** Doppelschlag mit eigenem Abstand und Quinte; kein bekannter Herzschlag.
- **Typ / Bindung:** Puls / **eigenständig**
- **Tonfolge:** 1 5-1Okt
- **Intervalle:** Quarte↓
- **Rhythmus:** DS-R12 Weiter Doppelschlag – 2 Einsätze, Periode 16 Sechzehntel; Positionen 0, 960 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 5-1Okt=A
- **Identität:** Rhythmus (Einsätze und Akzente bleiben); **Variationen:** JC-T003 Oktavverlagerung, JC-T011 Unterbrechung und Wiederaufnahme
- **XYZ:** Anker (0,50 / 0,35 / 0,40); X 0,00–1,00 · Y 0,00–0,70 · Z 0,20–0,60; Z-Charakter psychologisch
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-B10 12er-Bassperiode

- **Charakter:** Punktierte Achtel gegen den Takt; Wiederkehr nach 3 Takten.
- **Typ / Bindung:** Rhythmus / **eigenständig**
- **Tonfolge:** 1 1 5 1
- **Intervalle:** Prime, Quinte↑, Quinte↓
- **Rhythmus:** DS-R04 12er-Periode – 4 Einsätze, Periode 12 Sechzehntel; Positionen 0, 720, 1440, 2160 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 12 Sechzehntel; **Wiederkehr am Taktanfang:** nach 3 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 1=A, 5=A, 1=A
- **Identität:** Zyklus (Verschiebung gegen den Takt gehört zur Identität); **Variationen:** JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,50 / 0,60 / 0,55); X 0,00–1,00 · Y 0,30–0,90 · Z 0,30–0,80; Z-Charakter mechanisch
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-B11 13er-Bassperiode

- **Charakter:** Fünf Schläge in 13 Sechzehnteln; Wiederkehr nach 13 Takten.
- **Typ / Bindung:** Rhythmus / **eigenständig**
- **Tonfolge:** 1 1 5 1 ♭6
- **Intervalle:** Prime, Quinte↑, Quinte↓, kleine Sexte↑
- **Rhythmus:** DS-R06 13er-Periode – 5 Einsätze, Periode 13 Sechzehntel; Positionen 0, 720, 1440, 2160, 2640 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 13 Sechzehntel; **Wiederkehr am Taktanfang:** nach 13 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 1=A, 5=A, 1=A, ♭6=U
- **Identität:** Zyklus (Verschiebung gegen den Takt gehört zur Identität); **Variationen:** JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,30 / 0,70 / 0,80); X 0,00–0,60 · Y 0,40–1,00 · Z 0,60–1,00; Z-Charakter psychologisch
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-B12 10er-Bassperiode

- **Charakter:** Vier Schläge in 10 Sechzehnteln; Wiederkehr nach 5 Takten.
- **Typ / Bindung:** Rhythmus / **eigenständig**
- **Tonfolge:** 1 1+1Okt 1 5
- **Intervalle:** Oktave↑, Oktave↓, Quinte↑
- **Rhythmus:** DS-R07 10er-Periode – 4 Einsätze, Periode 10 Sechzehntel; Positionen 0, 480, 1200, 1680 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 10 Sechzehntel; **Wiederkehr am Taktanfang:** nach 5 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 1+1Okt=A, 1=A, 5=A
- **Identität:** Zyklus (Verschiebung gegen den Takt gehört zur Identität); **Variationen:** JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,50 / 0,60 / 0,65); X 0,00–1,00 · Y 0,30–0,90 · Z 0,40–0,90; Z-Charakter mechanisch
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-B13 Oktav-Orgelpunkt

- **Charakter:** Ganze Noten; nach vier Takten eine Oktave höher, dann zurück.
- **Typ / Bindung:** Drone / **eigenständig**
- **Tonfolge:** 1 1 1 1 1+1Okt 1+1Okt 1+1Okt 1+1Okt
- **Intervalle:** Prime, Prime, Prime, Oktave↑, Prime, Prime, Prime
- **Rhythmus:** JC-R019 Ganze Noten – 1 Einsätze, Periode 16 Sechzehntel; Positionen 0 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 128 Sechzehntel; **Wiederkehr am Taktanfang:** nach 8 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 1=A, 1=A, 1=A, 1+1Okt=A, 1+1Okt=A, 1+1Okt=A, 1+1Okt=A
- **Identität:** Tonhöhe (Rhythmus variabel); **Variationen:** JC-T003 Oktavverlagerung, JC-T012 Langfristige Stasis
- **XYZ:** Anker (0,50 / 0,65 / 0,15); X 0,00–1,00 · Y 0,30–1,00 · Z 0,00–0,30; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-B14 Choralbass mit Quintvorschlag

- **Charakter:** Viertel auf dem Grundton, die letzte auf der Quinte. Nicht unter verminderten Klängen.
- **Typ / Bindung:** Schreitend / **akkordgebunden**
- **Tonfolge:** 1 1 1 5
- **Intervalle:** Prime, Prime, Quinte↑
- **Rhythmus:** JC-R001 Viertelpuls – 4 Einsätze, Periode 16 Sechzehntel; Positionen 0, 960, 1920, 2880 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 1=A, 1=A, 5=A
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,50 / 0,65 / 0,20); X 0,00–1,00 · Y 0,30–1,00 · Z 0,00–0,40; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-B15 6/8-Wiegebass

- **Charakter:** Wiegend im 6/8.
- **Typ / Bindung:** Melodisch / **akkordgebunden**
- **Tonfolge:** 1 1 5 1+1Okt 5 1
- **Intervalle:** Prime, Quinte↑, Quarte↑, Quarte↓, Quinte↓
- **Rhythmus:** JC-R031 6/8-Hemiole – 6 Einsätze, Periode 12 Sechzehntel; Positionen 0, 480, 960, 1440, 1920, 2400 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 12 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 1=A, 5=A, 1+1Okt=A, 5=A, 1=A
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,50 / 0,50 / 0,40); X 0,20–0,80 · Y 0,20–0,80 · Z 0,20–0,60; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-B16 Antwortbass

- **Charakter:** Ein Ruf, dann ein kurzes Paar; Platz für Tupfer.
- **Typ / Bindung:** Melodisch / **eigenständig**
- **Tonfolge:** 1 5-1Okt ♭7-1Okt
- **Intervalle:** Quarte↓, kleine Terz↑
- **Rhythmus:** DS-R13 Antwortbass-Rhythmus – 3 Einsätze, Periode 16 Sechzehntel; Positionen 0, 1920, 2400 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 5-1Okt=A, ♭7-1Okt=T
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,45 / 0,40 / 0,30); X 0,10–0,80 · Y 0,10–0,70 · Z 0,10–0,50; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-B17 Galopp-Oktave

- **Charakter:** Triolischer Galopp im Oktavwechsel.
- **Typ / Bindung:** Rhythmus / **akkordgebunden**
- **Tonfolge:** 1 1+1Okt
- **Intervalle:** Oktave↑
- **Rhythmus:** JC-R067 Galopp-Triole – 8 Einsätze, Periode 16 Sechzehntel; Positionen 0, 640, 960, 1600, 1920, 2560, 2880, 3520 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 1+1Okt=A
- **Identität:** Rhythmus (Einsätze und Akzente bleiben); **Variationen:** JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,50 / 0,80 / 0,75); X 0,00–1,00 · Y 0,60–1,00 · Z 0,50–1,00; Z-Charakter mechanisch
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-B18 Kriechende Halbe mit Leitton

- **Charakter:** Halbe: Grundton, Leitton, Grundton, ♭7.
- **Typ / Bindung:** Chromatisch / **eigenständig**
- **Tonfolge:** 1 7-1Okt 1 ♭7-1Okt
- **Intervalle:** kleine Sekunde↓, kleine Sekunde↑, große Sekunde↓
- **Rhythmus:** JC-R006 Halbe-Puls – 2 Einsätze, Periode 16 Sechzehntel; Positionen 0, 1920 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 32 Sechzehntel; **Wiederkehr am Taktanfang:** nach 2 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 7-1Okt=U, 1=A, ♭7-1Okt=T
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,25 / 0,40 / 0,62); X 0,00–0,50 · Y 0,10–0,70 · Z 0,40–0,85; Z-Charakter psychologisch
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-B19 Wechselbass 1–♭6

- **Charakter:** Zwei Takte Grundton, zwei Takte ♭6; erzeugt das Schattenpaar allein aus dem Bass.
- **Typ / Bindung:** Schreitend / **eigenständig**
- **Tonfolge:** 1 1 ♭6-1Okt ♭6-1Okt
- **Intervalle:** Prime, große Terz↓, Prime
- **Rhythmus:** JC-R019 Ganze Noten – 1 Einsätze, Periode 16 Sechzehntel; Positionen 0 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 64 Sechzehntel; **Wiederkehr am Taktanfang:** nach 4 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 1=A, ♭6-1Okt=T, ♭6-1Okt=T
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **XYZ:** Anker (0,53 / 0,30 / 0,17); X 0,30–0,75 · Y 0,00–0,60 · Z 0,00–0,35; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-B20 Dur-Wiegebass

- **Charakter:** Gebundene Achtel 1–5–3–5 in Dur; nur über Dur-Grundklang.
- **Typ / Bindung:** Melodisch / **eigenständig**
- **Tonfolge:** 1 5 3 5
- **Intervalle:** Quinte↑, kleine Terz↓, kleine Terz↑
- **Rhythmus:** JC-R014 Legato-Achtel – 8 Einsätze, Periode 16 Sechzehntel; Positionen 0, 480, 960, 1440, 1920, 2400, 2880, 3360 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Durdreiklang, Ionisch (Dur)): 1=A, 5=A, 3=A, 5=A
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,80 / 0,40 / 0,17); X 0,60–1,00 · Y 0,10–0,70 · Z 0,00–0,35; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-B21 Sakraler Grundbass

- **Charakter:** Halbe Grundton und Oktave; Orgelpedal-artig.
- **Typ / Bindung:** Schreitend / **akkordgebunden**
- **Tonfolge:** 1 1+1Okt
- **Intervalle:** Oktave↑
- **Rhythmus:** JC-R006 Halbe-Puls – 2 Einsätze, Periode 16 Sechzehntel; Positionen 0, 1920 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 1+1Okt=A
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,50 / 0,65 / 0,17); X 0,00–1,00 · Y 0,30–1,00 · Z 0,00–0,35; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

## 7. DS-R Rhythmus und DS-Q Sequencer

### DS-R

| ID | Name | Takt | Raster | Muster | Periode (16tel) | Wiederkehr am Taktanfang | Evidenz |
|---|---|---|---|---|---|---|---|
| DS-R01 | Oktavpuls mit Lücke | 4/4 | 16 | `x.x.x...x.x.x.x.` | 16 | 1 Takt(e) | E |
| DS-R02 | Pendel mit Vorschlag | 4/4 | 16 | `x_x_____x_x_____` | 16 | 1 Takt(e) | E |
| DS-R03 | Rufbass-Rhythmus | 4/4 | 16 | `x_______................x.x.....` | 32 | 2 Takt(e) | E |
| DS-R04 | 12er-Periode | 4/4 | 16 | `x..x..x..x..` | 12 | 3 Takt(e) | E |
| DS-R05 | 12er-Gegenzelle | 4/4 | 16 | `x..x.x..x.x.` | 12 | 3 Takt(e) | E |
| DS-R06 | 13er-Periode | 4/4 | 16 | `x..x..x..x.x.` | 13 | 13 Takt(e) | N |
| DS-R07 | 10er-Periode | 4/4 | 16 | `x.x..x.x..` | 10 | 5 Takt(e) | E |
| DS-R08 | 16er-Lückenzelle | 4/4 | 16 | `x.xx.x.xx.x.xx.x` | 16 | 1 Takt(e) | E |
| DS-R09 | Spieluhr-Rhythmus | 4/4 | 16 | `x.x.x.....x.x...` | 16 | 1 Takt(e) | E |
| DS-R10 | Verzögerter Step | 4/4 | 32 | `x...x...x...x...x...x...x....x..` | 16 | 1 Takt(e) | N |
| DS-R11 | 7er-Periode | 4/4 | 16 | `Xxxxxxx` | 7 | 7 Takt(e) | H |
| DS-R12 | Weiter Doppelschlag | 4/4 | 16 | `X...x...........` | 16 | 1 Takt(e) | E |
| DS-R13 | Antwortbass-Rhythmus | 4/4 | 16 | `x.......x.x.....` | 16 | 1 Takt(e) | E |

- **DS-R01:** Sieben Schläge, ein Atemloch nach der zweiten Zählzeit.
- **DS-R02:** Achtel, dann punktierte Viertel; zweimal pro Takt.
- **DS-R03:** Langer Ton, Pause, kurze Antwort im zweiten Takt.
- **DS-R04:** Vier punktierte Achtel = 12 Sechzehntel; trifft den Takt alle 3 Takte wieder.
- **DS-R05:** Fünf Schläge in 12 Sechzehnteln; Partner zu 16er-Zellen.
- **DS-R06:** 13 Sechzehntel; Wiederkehr am Taktanfang erst nach 13 Takten (Periodenprinzip nach Disasterpeace, eigene Konstruktion).
- **DS-R07:** 10 Sechzehntel; Wiederkehr nach 5 Takten.
- **DS-R08:** Zehn Schläge mit festen Lücken; Raum für Einwürfe.
- **DS-R09:** Drei Töne, Pause, zwei Töne; wie aufgezogen.
- **DS-R10:** Achtel; der letzte Schlag kommt eine 32stel zu spät (verzögerter Trigger nach Franke, eigene Konstruktion).
- **DS-R11:** Sieben Sechzehntel; Wiederkehr nach 7 Takten. Prog-Assoziation, nicht belegt.
- **DS-R12:** Doppelschlag mit größerem Abstand als ein Herzschlag; bewusst nicht der bekannte Puls.
- **DS-R13:** Ein Schlag, dann ein kurzes Paar auf der Drei.

### DS-Q

#### DS-Q01 Schattenpaar-Arpeggio

- **Charakter:** Töne des ♭VImaj7 über dem Mollzentrum, in Triolen; nicht die Kontur des bekannten Titelthemas.
- **Tonfolge:** ♭6-1Okt ♭3 1 5 ♭3 1+1Okt
- **Intervalle:** Quinte↑, kleine Terz↓, Quinte↑, große Terz↓, große Sexte↑
- **Rhythmus:** JC-R032 Achteltriolen betont – 12 Einsätze, Periode 16 Sechzehntel; Positionen 0, 320, 640, 960, 1280, 1600, 1920, 2240, 2560, 2880, 3200, 3520 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): ♭6-1Okt=F, ♭3=A, 1=A, 5=A, ♭3=A, 1+1Okt=A
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **XYZ:** Anker (0,60 / 0,40 / 0,23); X 0,35–0,85 · Y 0,10–0,70 · Z 0,00–0,45; Z-Charakter neutral
- **Evidenz:** I – begründete Interpretation; Tonfolge E

#### DS-Q02 Melancholisches Arpeggio 6 gegen 8

- **Charakter:** Sechs Töne auf acht gebundenen Achteln; trifft sich nach 3 Takten.
- **Tonfolge:** 1 5 ♭7 ♭3+1Okt ♭7 5
- **Intervalle:** Quinte↑, kleine Terz↑, Quarte↑, Quarte↓, kleine Terz↓
- **Rhythmus:** JC-R014 Legato-Achtel – 8 Einsätze, Periode 16 Sechzehntel; Positionen 0, 480, 960, 1440, 1920, 2400, 2880, 3360 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 48 Sechzehntel; **Wiederkehr am Taktanfang:** nach 3 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 5=A, ♭7=T, ♭3+1Okt=A, ♭7=T, 5=A
- **Identität:** Zyklus (Verschiebung gegen den Takt gehört zur Identität); **Variationen:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **XYZ:** Anker (0,55 / 0,30 / 0,28); X 0,35–0,75 · Y 0,00–0,60 · Z 0,10–0,45; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-Q03 16er-Lückenzelle

- **Charakter:** Zehn Töne, Lücken an festen Stellen.
- **Tonfolge:** 1 5 1+1Okt 5 ♭3+1Okt 1+1Okt 5 1+1Okt 1 ♭7
- **Intervalle:** Quinte↑, Quarte↑, Quarte↓, kleine Sexte↑, kleine Terz↓, Quarte↓, Quarte↑, Oktave↓, kleine Septime↑
- **Rhythmus:** DS-R08 16er-Lückenzelle – 10 Einsätze, Periode 16 Sechzehntel; Positionen 0, 480, 720, 1200, 1680, 1920, 2400, 2880, 3120, 3600 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 5=A, 1+1Okt=A, 5=A, ♭3+1Okt=A, 1+1Okt=A, 5=A, 1+1Okt=A, 1=A, ♭7=T
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T001 Blocktransposition, JC-T002 Einzeltonvariation, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,40 / 0,60 / 0,50); X 0,00–0,80 · Y 0,30–0,90 · Z 0,30–0,70; Z-Charakter mechanisch
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-Q04 12er-Gegenzelle

- **Charakter:** Fünf Töne in 12 Sechzehnteln; gegen eine 16er-Zelle Wiederkehr nach 3 Takten.
- **Tonfolge:** 1+1Okt 5 ♭3 5 ♭7
- **Intervalle:** Quarte↓, große Terz↓, große Terz↑, kleine Terz↑
- **Rhythmus:** DS-R05 12er-Gegenzelle – 5 Einsätze, Periode 12 Sechzehntel; Positionen 0, 720, 1200, 1920, 2400 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 12 Sechzehntel; **Wiederkehr am Taktanfang:** nach 3 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+1Okt=A, 5=A, ♭3=A, 5=A, ♭7=T
- **Identität:** Zyklus (Verschiebung gegen den Takt gehört zur Identität); **Variationen:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,40 / 0,60 / 0,60); X 0,00–0,80 · Y 0,30–0,90 · Z 0,40–0,80; Z-Charakter mechanisch
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-Q05 13er-Zelle

- **Charakter:** Fünf Töne in 13 Sechzehnteln; Wiederkehr nach 13 Takten.
- **Tonfolge:** 1 5 ♭3 ♭7 ♭6
- **Intervalle:** Quinte↑, große Terz↓, Quinte↑, große Sekunde↓
- **Rhythmus:** DS-R06 13er-Periode – 5 Einsätze, Periode 13 Sechzehntel; Positionen 0, 720, 1440, 2160, 2640 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 13 Sechzehntel; **Wiederkehr am Taktanfang:** nach 13 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 5=A, ♭3=A, ♭7=T, ♭6=T
- **Identität:** Zyklus (Verschiebung gegen den Takt gehört zur Identität); **Variationen:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,30 / 0,60 / 0,80); X 0,00–0,60 · Y 0,20–1,00 · Z 0,60–1,00; Z-Charakter psychologisch
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-Q06 10er-Zelle

- **Charakter:** Vier Töne in 10 Sechzehnteln; Wiederkehr nach 5 Takten.
- **Tonfolge:** 1 1+1Okt 5 1+1Okt
- **Intervalle:** Oktave↑, Quarte↓, Quarte↑
- **Rhythmus:** DS-R07 10er-Periode – 4 Einsätze, Periode 10 Sechzehntel; Positionen 0, 480, 1200, 1680 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 10 Sechzehntel; **Wiederkehr am Taktanfang:** nach 5 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 1+1Okt=A, 5=A, 1+1Okt=A
- **Identität:** Zyklus (Verschiebung gegen den Takt gehört zur Identität); **Variationen:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,40 / 0,60 / 0,65); X 0,00–0,80 · Y 0,30–0,90 · Z 0,40–0,90; Z-Charakter mechanisch
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-Q07 Spieluhr-Sequenz

- **Charakter:** Hohe, aufgezogene Figur; Kinderlied-nah, aber eigene Kontur.
- **Tonfolge:** 1+2Okt ♭3+2Okt 5+2Okt 2+2Okt 1+2Okt
- **Intervalle:** kleine Terz↑, große Terz↑, Quarte↓, große Sekunde↓
- **Rhythmus:** DS-R09 Spieluhr-Rhythmus – 5 Einsätze, Periode 16 Sechzehntel; Positionen 0, 480, 960, 2400, 2880 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+2Okt=A, ♭3+2Okt=A, 5+2Okt=A, 2+2Okt=T, 1+2Okt=A
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T003 Oktavverlagerung, JC-T005 Motivfragmentierung
- **XYZ:** Anker (0,70 / 0,30 / 0,45); X 0,40–1,00 · Y 0,00–0,60 · Z 0,20–0,70; Z-Charakter psychologisch
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-Q08 Glocken-Ostinato 3 gegen 8

- **Charakter:** Drei Glockentöne auf acht Achteln; Wiederkehr nach 3 Takten.
- **Tonfolge:** 1+2Okt 5+1Okt ♭7+1Okt
- **Intervalle:** Quarte↓, kleine Terz↑
- **Rhythmus:** JC-R002 Achtelpuls – 8 Einsätze, Periode 16 Sechzehntel; Positionen 0, 480, 960, 1440, 1920, 2400, 2880, 3360 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 48 Sechzehntel; **Wiederkehr am Taktanfang:** nach 3 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+2Okt=A, 5+1Okt=A, ♭7+1Okt=T
- **Identität:** Zyklus (Verschiebung gegen den Takt gehört zur Identität); **Variationen:** JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **XYZ:** Anker (0,70 / 0,30 / 0,50); X 0,40–1,00 · Y 0,00–0,60 · Z 0,30–0,70; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-Q09 Nostalgie-Wiege in Dur

- **Charakter:** Imaj7-Töne auf und ab in Triolen; warm, langsam.
- **Tonfolge:** 1 3 5 7 5 3
- **Intervalle:** große Terz↑, kleine Terz↑, große Terz↑, große Terz↓, kleine Terz↓
- **Rhythmus:** JC-R032 Achteltriolen betont – 12 Einsätze, Periode 16 Sechzehntel; Positionen 0, 320, 640, 960, 1280, 1600, 1920, 2240, 2560, 2880, 3200, 3520 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Dur mit großer Septime, Ionisch (Dur)): 1=A, 3=A, 5=A, 7=A, 5=A, 3=A
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung, JC-T009 Gate-Veränderung
- **XYZ:** Anker (0,82 / 0,30 / 0,17); X 0,65–1,00 · Y 0,00–0,60 · Z 0,00–0,35; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-Q10 Prog-Ostinato 7 gegen 16

- **Charakter:** Sieben Töne auf 7-Sechzehntel-Periode; Wiederkehr nach 7 Takten. Assoziation italienischer Prog, nicht belegt.
- **Tonfolge:** 1 1+1Okt ♭7 5 ♭3 5 ♭7
- **Intervalle:** Oktave↑, große Sekunde↓, kleine Terz↓, große Terz↓, große Terz↑, kleine Terz↑
- **Rhythmus:** DS-R11 7er-Periode – 7 Einsätze, Periode 7 Sechzehntel; Positionen 0, 240, 480, 720, 960, 1200, 1440 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 7 Sechzehntel; **Wiederkehr am Taktanfang:** nach 7 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 1+1Okt=A, ♭7=T, 5=A, ♭3=A, 5=A, ♭7=T
- **Identität:** Zyklus (Verschiebung gegen den Takt gehört zur Identität); **Variationen:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,30 / 0,70 / 0,80); X 0,00–0,60 · Y 0,40–1,00 · Z 0,60–1,00; Z-Charakter mechanisch
- **Evidenz:** H – Hypothese; Tonfolge E

#### DS-Q11 Dorische Pendelsequenz

- **Charakter:** Grundton, große Sexte, Quinte; kühl hell.
- **Tonfolge:** 1 6 5 6
- **Intervalle:** große Sexte↑, große Sekunde↓, große Sekunde↑
- **Rhythmus:** JC-R013 Staccato-Achtel – 8 Einsätze, Periode 16 Sechzehntel; Positionen 0, 480, 960, 1440, 1920, 2400, 2880, 3360 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Dorisch): 1=A, 6=T, 5=A, 6=T
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,65 / 0,45 / 0,40); X 0,45–0,85 · Y 0,20–0,70 · Z 0,20–0,60; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-Q12 Halbton-Echo-Zelle

- **Charakter:** Zucken zur ♭2, Sprung zur Oktave.
- **Tonfolge:** 1 ♭2 1 1+1Okt
- **Intervalle:** kleine Sekunde↑, kleine Sekunde↓, Oktave↑
- **Rhythmus:** JC-R003 Sechzehntelpuls – 16 Einsätze, Periode 16 Sechzehntel; Positionen 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, ♭2=U, 1=A, 1+1Okt=A
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,20 / 0,70 / 0,80); X 0,00–0,40 · Y 0,40–1,00 · Z 0,60–1,00; Z-Charakter psychologisch
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-Q13 Gefrier-Zelle

- **Charakter:** Für die Strategie Gefrieren: läuft, stoppt auf der Quinte, die als Fläche weiterklingt.
- **Tonfolge:** 1 5 1+1Okt 5 ♭3+1Okt 5 1+1Okt 5
- **Intervalle:** Quinte↑, Quarte↑, Quarte↓, kleine Sexte↑, kleine Sexte↓, Quarte↑, Quarte↓
- **Rhythmus:** JC-R003 Sechzehntelpuls – 16 Einsätze, Periode 16 Sechzehntel; Positionen 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 5=A, 1+1Okt=A, 5=A, ♭3+1Okt=A, 5=A, 1+1Okt=A, 5=A
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,45 / 0,55 / 0,40); X 0,20–0,70 · Y 0,30–0,80 · Z 0,20–0,60; Z-Charakter mechanisch
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-Q14 Verzögerte Achtelzelle

- **Charakter:** Achtelzelle, deren letzter Schlag eine 32stel zu spät kommt.
- **Tonfolge:** 1 5 1 1+1Okt 1 5 1 ♭7
- **Intervalle:** Quinte↑, Quinte↓, Oktave↑, Oktave↓, Quinte↑, Quinte↓, kleine Septime↑
- **Rhythmus:** DS-R10 Verzögerter Step – 8 Einsätze, Periode 16 Sechzehntel; Positionen 0, 480, 960, 1440, 1920, 2400, 2880, 3480 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 5=A, 1=A, 1+1Okt=A, 1=A, 5=A, 1=A, ♭7=T
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,45 / 0,50 / 0,50); X 0,00–0,90 · Y 0,20–0,80 · Z 0,30–0,70; Z-Charakter mechanisch
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-Q15 Quartenkreis

- **Charakter:** Quarten auf und ab in Triolen; schwebend, modal.
- **Tonfolge:** 1 4 ♭7 ♭3+1Okt ♭7 4
- **Intervalle:** Quarte↑, Quarte↑, Quarte↑, Quarte↓, Quarte↓
- **Rhythmus:** JC-R032 Achteltriolen betont – 12 Einsätze, Periode 16 Sechzehntel; Positionen 0, 320, 640, 960, 1280, 1600, 1920, 2240, 2560, 2880, 3200, 3520 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Dorisch): 1=A, 4=T, ♭7=T, ♭3+1Okt=A, ♭7=T, 4=T
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **XYZ:** Anker (0,62 / 0,50 / 0,40); X 0,40–0,85 · Y 0,20–0,80 · Z 0,20–0,60; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-Q16 Rollende Dur-Zelle

- **Charakter:** Imaj7 in Sechzehnteln; hell, drängend.
- **Tonfolge:** 1+1Okt 3+1Okt 5+1Okt 7+1Okt
- **Intervalle:** große Terz↑, kleine Terz↑, große Terz↑
- **Rhythmus:** JC-R003 Sechzehntelpuls – 16 Einsätze, Periode 16 Sechzehntel; Positionen 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Dur mit großer Septime, Ionisch (Dur)): 1+1Okt=A, 3+1Okt=A, 5+1Okt=A, 7+1Okt=A
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **XYZ:** Anker (0,82 / 0,70 / 0,55); X 0,65–1,00 · Y 0,40–1,00 · Z 0,30–0,80; Z-Charakter mechanisch
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-Q17 Moll-Wiege mit ♭6-Fluchtton

- **Charakter:** Der ♭6 ist der einzige Fluchtton.
- **Tonfolge:** 1 ♭3 5 ♭6 5 ♭3
- **Intervalle:** kleine Terz↑, große Terz↑, kleine Sekunde↑, kleine Sekunde↓, große Terz↓
- **Rhythmus:** JC-R032 Achteltriolen betont – 12 Einsätze, Periode 16 Sechzehntel; Positionen 0, 320, 640, 960, 1280, 1600, 1920, 2240, 2560, 2880, 3200, 3520 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, ♭3=A, 5=A, ♭6=T, 5=A, ♭3=A
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **XYZ:** Anker (0,43 / 0,40 / 0,40); X 0,20–0,65 · Y 0,10–0,70 · Z 0,20–0,60; Z-Charakter psychologisch
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-Q18 Choral-Repetition

- **Charakter:** Orgelartige Viertel auf Oktave und Quinte.
- **Tonfolge:** 1+1Okt 1+1Okt 5 5
- **Intervalle:** Prime, Quarte↓, Prime
- **Rhythmus:** JC-R001 Viertelpuls – 4 Einsätze, Periode 16 Sechzehntel; Positionen 0, 960, 1920, 2880 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1+1Okt=A, 1+1Okt=A, 5=A, 5=A
- **Identität:** Rhythmus (Einsätze und Akzente bleiben); **Variationen:** JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **XYZ:** Anker (0,45 / 0,70 / 0,20); X 0,20–0,70 · Y 0,40–1,00 · Z 0,00–0,40; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-Q19 Atmende Quintzelle

- **Charakter:** Für Gate-Atmung gedacht.
- **Tonfolge:** 5 1+1Okt ♭3+1Okt 1+1Okt
- **Intervalle:** Quarte↑, kleine Terz↑, kleine Terz↓
- **Rhythmus:** JC-R002 Achtelpuls – 8 Einsätze, Periode 16 Sechzehntel; Positionen 0, 480, 960, 1440, 1920, 2400, 2880, 3360 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 5=A, 1+1Okt=A, ♭3+1Okt=A, 1+1Okt=A
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung, JC-T009 Gate-Veränderung
- **XYZ:** Anker (0,50 / 0,50 / 0,30); X 0,20–0,80 · Y 0,20–0,80 · Z 0,10–0,50; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-Q20 Mutationszelle

- **Charakter:** Für Ein-Schritt-Mutation gedacht (Franke-Prinzip, eigene Tonfolge).
- **Tonfolge:** 1 1+1Okt ♭3 5 1 1+1Okt ♭3 ♭7
- **Intervalle:** Oktave↑, große Sexte↓, große Terz↑, Quinte↓, Oktave↑, große Sexte↓, Quinte↑
- **Rhythmus:** JC-R003 Sechzehntelpuls – 16 Einsätze, Periode 16 Sechzehntel; Positionen 0, 240, 480, 720, 960, 1200, 1440, 1680, 1920, 2160, 2400, 2640, 2880, 3120, 3360, 3600 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 1+1Okt=A, ♭3=A, 5=A, 1=A, 1+1Okt=A, ♭3=A, ♭7=T
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T002 Einzeltonvariation, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,45 / 0,60 / 0,50); X 0,10–0,80 · Y 0,30–0,90 · Z 0,30–0,70; Z-Charakter mechanisch
- **Evidenz:** N – Verfahren nachgewiesen; Tonfolge E

#### DS-Q21 Triolen-Kettenläufer

- **Charakter:** Folgt dem Akkordgrundton; trägt mehrgliedrige Ketten.
- **Tonfolge:** 1 5 1+1Okt 5 1 5
- **Intervalle:** Quinte↑, Quarte↑, Quarte↓, Quinte↓, Quinte↑
- **Rhythmus:** JC-R032 Achteltriolen betont – 12 Einsätze, Periode 16 Sechzehntel; Positionen 0, 320, 640, 960, 1280, 1600, 1920, 2240, 2560, 2880, 3200, 3520 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 16 Sechzehntel; **Wiederkehr am Taktanfang:** nach 1 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 5=A, 1+1Okt=A, 5=A, 1=A, 5=A
- **Identität:** Kontur (Intervallfolge und Rhythmus bleiben); **Variationen:** JC-T003 Oktavverlagerung, JC-T008 Harmonische Umfärbung
- **XYZ:** Anker (0,50 / 0,50 / 0,30); X 0,20–0,80 · Y 0,20–0,80 · Z 0,10–0,50; Z-Charakter neutral
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

#### DS-Q22 Antwortlücken-Sequenz

- **Charakter:** Drei Töne auf sieben Schläge mit Atemloch; lässt Platz für TU-Antworten. Wiederkehr nach 3 Takten.
- **Tonfolge:** 1 5 1+1Okt
- **Intervalle:** Quinte↑, Quarte↑
- **Rhythmus:** DS-R01 Oktavpuls mit Lücke – 7 Einsätze, Periode 16 Sechzehntel; Positionen 0, 480, 960, 1920, 2400, 2880, 3360 Ticks
- **Gemeinsame Periode Ton × Rhythmus:** 48 Sechzehntel; **Wiederkehr am Taktanfang:** nach 3 Takt(en)
- **Tonfunktionen** (Bezug Molldreiklang, Äolisch (natürliches Moll)): 1=A, 5=A, 1+1Okt=A
- **Identität:** Zyklus (Verschiebung gegen den Takt gehört zur Identität); **Variationen:** JC-T001 Blocktransposition, JC-T003 Oktavverlagerung
- **XYZ:** Anker (0,40 / 0,60 / 0,40); X 0,00–0,80 · Y 0,30–0,90 · Z 0,20–0,60; Z-Charakter mechanisch
- **Evidenz:** E – eigenständige Gestaltung; Tonfolge E

**Kombinationen mit berechneter Gesamtwiederkehr:** DS-Q03 (16) + DS-Q04 (12) → 3 Takte; DS-Q03 + DS-Q06 (10) → 5 Takte; DS-Q03 + DS-Q05 (13) → 13 Takte; DS-Q03 + DS-Q10 (7) → 7 Takte; mit einer 8-Takt-Harmonie jeweils kgV mit 8 (24, 40, 104, 56 Takte).

## 8. Tupfer (TU) als eigenständige Rolle

TU ist eine **tonale Ereignisrolle mit optionalem Motivgedächtnis**. Sie braucht weder Sequencer noch Hauptmelodie und ist nie dauerhaft aktiv.

**Grundsätze (Präferenzen, keine Quoten):**

- **Register:** bevorzugt mindestens eine Quarte über oder unter jedem gleichzeitig klingenden Sequencer-Ton; Standardlage zwei Oktaven über der TU-Basis. Tiefe Glocken sind ein bewusster Registersprung.
- **Platzierung:** Ereignisse ohne feste Position suchen eine Stelle im Takt ohne Sequencer-, Bass- oder Stab-Einsatz (Lückenplatzierung); bevorzugt Phrasenenden und leere Zählzeiten.
- **Pausen:** Abstand zwischen Ereignissen frei; lange Leere ist zulässig.
- **Gedächtnis:** 0–3 Keime pro Stück. Keime kehren als Original, Fragment, Transposition, Oktave, Umkehrung, Augmentation, Anpassung oder Echo wieder. Einzeltöne sind gleichberechtigt.
- **Tonfunktion:** Glocken und Antworten meist A; Spieluhren A/T; Fragen enden auf autorisiertem U; Reibungsglocken F.
- **Zusammenspiel:** Echo greift die tatsächlich gespielten Sequencer-Töne auf; Dialog-Paare antworten im Takt nach dem Ruf.
- **Pitch-Bend und Controller:** optional und instrumentabhängig (T6); die MIDI-Studien enthalten keine Bend-Daten.

### Ereignistypen T1–T8

| Typ | Funktion | Vorlagen |
|---|---|---|
| T1 | Glockenschlag | DS-TU01, DS-TU02, DS-TU03, DS-TU04, DS-TU05 |
| T2 | Spieluhr-Splitter | DS-TU06, DS-TU07, DS-TU08, DS-TU09, DS-TU10 |
| T3 | Frage ohne Antwort | DS-TU11, DS-TU12, DS-TU13, DS-TU14 |
| T4 | Fragment-Keim | DS-TU15, DS-TU16, DS-TU17, DS-TU18, DS-TU19 |
| T5 | Echo und rhythmischer Einwurf | DS-TU26, DS-TU27, DS-TU28, DS-TO01, DS-TO02, DS-TO03, DS-TO04 |
| T6 | Fallender Ton | DS-TU20, DS-TU21, DS-TU22 |
| T7 | Dialog-Antwort | DS-TU23, DS-TU24, DS-TU25 |
| T8 | Erinnerung | DS-TO05, DS-TO06, DS-TO07 |

### DS-TU Motive

#### DS-TU01 Glockenschlag Quinte (T1)

- **Charakter:** Ein lang ausklingender Ton; Glockenschlag nach Bernstein/Goblin-Prinzip.
- **Noten:** 5+2Okt @ 0, Dauer 3840, v104
- **Tonfunktionen:** 5+2Okt=A (Bezug Molldreiklang, Äolisch (natürliches Moll))
- **Register:** TU-Basis + 31…31 Halbtöne; **XYZ:** X 0,00–1,00 · Y 0,00–0,70 · Z 0,00–0,50; **Evidenz:** N – Verfahren nachgewiesen

#### DS-TU02 Glockenschlag Grundton (T1)

- **Charakter:** Ruhiger Einzelton auf dem Zentrum.
- **Noten:** 1+2Okt @ 0, Dauer 3840, v104
- **Tonfunktionen:** 1+2Okt=A (Bezug Molldreiklang, Äolisch (natürliches Moll))
- **Register:** TU-Basis + 24…24 Halbtöne; **XYZ:** X 0,00–1,00 · Y 0,00–0,70 · Z 0,00–0,50; **Evidenz:** N – Verfahren nachgewiesen

#### DS-TU03 Glockenschlag ♭2 (T1)

- **Charakter:** Glocke auf dem Halbtonnachbarn; bewusst akkordfremd.
- **Noten:** ♭2+2Okt @ 0, Dauer 3840, v100
- **Tonfunktionen:** ♭2+2Okt=F (Bezug Molldreiklang, Äolisch (natürliches Moll))
- **Register:** TU-Basis + 25…25 Halbtöne; **XYZ:** X 0,00–0,50 · Y 0,00–0,70 · Z 0,40–0,90; **Evidenz:** E – eigenständige Gestaltung

#### DS-TU04 Tiefe Glocke (T1)

- **Charakter:** Registersprung nach unten; Totenglocke.
- **Noten:** 1+1Okt @ 0, Dauer 5760, v110
- **Tonfunktionen:** 1+1Okt=A (Bezug Molldreiklang, Äolisch (natürliches Moll))
- **Register:** TU-Basis + 12…12 Halbtöne; **XYZ:** X 0,00–0,60 · Y 0,30–1,00 · Z 0,00–0,50; **Evidenz:** N – Verfahren nachgewiesen

#### DS-TU05 Doppelglocke (T1)

- **Charakter:** Grundton, dann leisere Quinte.
- **Noten:** 1+2Okt @ 0, Dauer 1920, v104; 5+2Okt @ 1920, Dauer 3840, v84
- **Intervalle:** Quinte↑
- **Tonfunktionen:** 1+2Okt=A, 5+2Okt=A (Bezug Molldreiklang, Äolisch (natürliches Moll))
- **Register:** TU-Basis + 24…31 Halbtöne; **XYZ:** X 0,00–1,00 · Y 0,00–0,70 · Z 0,00–0,50; **Evidenz:** E – eigenständige Gestaltung

#### DS-TU06 Spieluhr ♭3–2–5 (T2)

- **Charakter:** Hoher, leiser Splitter; Spieluhr-Prinzip, eigene Tonfolge.
- **Noten:** ♭3+2Okt @ 0, Dauer 480, v92; 2+2Okt @ 480, Dauer 480, v88; 5+2Okt @ 960, Dauer 960, v96
- **Intervalle:** kleine Sekunde↓, Quarte↑
- **Tonfunktionen:** ♭3+2Okt=A, 2+2Okt=T, 5+2Okt=A (Bezug Molldreiklang, Äolisch (natürliches Moll))
- **Register:** TU-Basis + 26…31 Halbtöne; **XYZ:** X 0,30–0,90 · Y 0,00–0,60 · Z 0,10–0,60; **Evidenz:** N – Verfahren nachgewiesen

#### DS-TU07 Spieluhr 5–6–5 (T2)

- **Charakter:** Dorische Sexte als Lichtpunkt.
- **Noten:** 5+2Okt @ 0, Dauer 480, v92; 6+2Okt @ 480, Dauer 480, v88; 5+2Okt @ 960, Dauer 960, v96
- **Intervalle:** große Sekunde↑, große Sekunde↓
- **Tonfunktionen:** 5+2Okt=A, 6+2Okt=T, 5+2Okt=A (Bezug Molldreiklang, Dorisch)
- **Register:** TU-Basis + 31…33 Halbtöne; **XYZ:** X 0,50–1,00 · Y 0,00–0,60 · Z 0,10–0,50; **Evidenz:** E – eigenständige Gestaltung

#### DS-TU08 Dur-Spieluhr 3–2–1–5 (T2)

- **Charakter:** Kindlich-diatonisch; über Moll-Drone unheimlich.
- **Noten:** 3+2Okt @ 0, Dauer 480, v92; 2+2Okt @ 480, Dauer 480, v88; 1+2Okt @ 960, Dauer 480, v90; 5+2Okt @ 1440, Dauer 1440, v96
- **Intervalle:** große Sekunde↓, große Sekunde↓, Quinte↑
- **Tonfunktionen:** 3+2Okt=A, 2+2Okt=T, 1+2Okt=A, 5+2Okt=A (Bezug Durdreiklang, Ionisch (Dur))
- **Register:** TU-Basis + 24…31 Halbtöne; **XYZ:** X 0,55–1,00 · Y 0,00–0,60 · Z 0,00–0,70; **Evidenz:** E – eigenständige Gestaltung

#### DS-TU09 Spieluhr 1–5–♭6–5 (T2)

- **Charakter:** Kurzer Aufstieg mit ♭6-Schatten.
- **Noten:** 1+2Okt @ 0, Dauer 480, v92; 5+2Okt @ 480, Dauer 480, v88; ♭6+2Okt @ 960, Dauer 480, v90; 5+2Okt @ 1440, Dauer 1440, v96
- **Intervalle:** Quinte↑, kleine Sekunde↑, kleine Sekunde↓
- **Tonfunktionen:** 1+2Okt=A, 5+2Okt=A, ♭6+2Okt=T, 5+2Okt=A (Bezug Molldreiklang, Äolisch (natürliches Moll))
- **Register:** TU-Basis + 24…32 Halbtöne; **XYZ:** X 0,20–0,80 · Y 0,00–0,60 · Z 0,20–0,70; **Evidenz:** E – eigenständige Gestaltung

#### DS-TU10 Fallender Spieluhr-Splitter (T2)

- **Charakter:** Oktave, Quinte, ♭3 abwärts.
- **Noten:** 1+3Okt @ 0, Dauer 480, v92; 5+2Okt @ 480, Dauer 480, v88; ♭3+2Okt @ 960, Dauer 1440, v96
- **Intervalle:** Quarte↓, große Terz↓
- **Tonfunktionen:** 1+3Okt=A, 5+2Okt=A, ♭3+2Okt=A (Bezug Molldreiklang, Äolisch (natürliches Moll))
- **Register:** TU-Basis + 27…36 Halbtöne; **XYZ:** X 0,30–0,90 · Y 0,00–0,60 · Z 0,10–0,60; **Evidenz:** E – eigenständige Gestaltung

#### DS-TU11 Frage zum Tritonus (T3)

- **Charakter:** Endet offen auf dem Tritonus.
- **Noten:** 1+2Okt @ 0, Dauer 480, v94; ♭3+2Okt @ 480, Dauer 480, v90; ♯4/♭5+2Okt @ 960, Dauer 1920, v96
- **Intervalle:** kleine Terz↑, kleine Terz↑
- **Tonfunktionen:** 1+2Okt=A, ♭3+2Okt=A, ♯4/♭5+2Okt=U (Bezug Molldreiklang, Äolisch (natürliches Moll))
- **Register:** TU-Basis + 24…30 Halbtöne; **XYZ:** X 0,00–0,50 · Y 0,00–0,70 · Z 0,50–1,00; **Evidenz:** E – eigenständige Gestaltung

#### DS-TU12 Frage zum Leitton (T3)

- **Charakter:** Quinte, ♭6, Leitton; bleibt hängen.
- **Noten:** 5+2Okt @ 0, Dauer 480, v94; ♭6+2Okt @ 480, Dauer 480, v90; 7+2Okt @ 960, Dauer 1920, v96
- **Intervalle:** kleine Sekunde↑, kleine Terz↑
- **Tonfunktionen:** 5+2Okt=A, ♭6+2Okt=T, 7+2Okt=U (Bezug Molldreiklang, Äolisch (natürliches Moll))
- **Register:** TU-Basis + 31…35 Halbtöne; **XYZ:** X 0,10–0,60 · Y 0,00–0,70 · Z 0,40–0,90; **Evidenz:** E – eigenständige Gestaltung

#### DS-TU13 Frage zur ♭2 (T3)

- **Charakter:** Grundton, None, ♭2; eng und ungelöst.
- **Noten:** 1+2Okt @ 0, Dauer 480, v94; 2+2Okt @ 480, Dauer 480, v90; ♭2+2Okt @ 960, Dauer 1920, v96
- **Intervalle:** große Sekunde↑, kleine Sekunde↓
- **Tonfunktionen:** 1+2Okt=A, 2+2Okt=T, ♭2+2Okt=U (Bezug Molldreiklang, Äolisch (natürliches Moll))
- **Register:** TU-Basis + 24…26 Halbtöne; **XYZ:** X 0,00–0,50 · Y 0,00–0,70 · Z 0,40–0,90; **Evidenz:** E – eigenständige Gestaltung

#### DS-TU14 Frage zur großen Sexte (T3)

- **Charakter:** Helle, offene Frage in Moll.
- **Noten:** 1+2Okt @ 0, Dauer 960, v94; 5+2Okt @ 960, Dauer 480, v90; 6+2Okt @ 1440, Dauer 2400, v96
- **Intervalle:** Quinte↑, große Sekunde↑
- **Tonfunktionen:** 1+2Okt=A, 5+2Okt=A, 6+2Okt=U (Bezug Molldreiklang, Äolisch (natürliches Moll))
- **Register:** TU-Basis + 24…33 Halbtöne; **XYZ:** X 0,40–0,90 · Y 0,00–0,60 · Z 0,30–0,70; **Evidenz:** E – eigenständige Gestaltung

#### DS-TU15 Keim A: Quinte–♭6 (T4)

- **Charakter:** Zweitonkeim für die Fragment-Exposition (Suspiria-Prinzip, eigene Tonfolge).
- **Noten:** 5+2Okt @ 0, Dauer 960, v96; ♭6+2Okt @ 960, Dauer 1920, v96
- **Intervalle:** kleine Sekunde↑
- **Tonfunktionen:** 5+2Okt=A, ♭6+2Okt=F (Bezug Molldreiklang, Äolisch (natürliches Moll))
- **Register:** TU-Basis + 31…32 Halbtöne; **XYZ:** X 0,10–0,80 · Y 0,00–0,70 · Z 0,10–0,60; **Evidenz:** N – Verfahren nachgewiesen

#### DS-TU16 Keim A erweitert (T4)

- **Charakter:** Viertonstufe desselben Keims.
- **Noten:** 5+2Okt @ 0, Dauer 960, v96; ♭6+2Okt @ 960, Dauer 960, v96; 5+2Okt @ 1920, Dauer 960, v92; ♭3+2Okt @ 2880, Dauer 1920, v96
- **Intervalle:** kleine Sekunde↑, kleine Sekunde↓, große Terz↓
- **Tonfunktionen:** 5+2Okt=A, ♭6+2Okt=F, 5+2Okt=A, ♭3+2Okt=A (Bezug Molldreiklang, Äolisch (natürliches Moll))
- **Register:** TU-Basis + 27…32 Halbtöne; **XYZ:** X 0,10–0,80 · Y 0,00–0,70 · Z 0,10–0,60; **Evidenz:** E – eigenständige Gestaltung

#### DS-TU17 Keim B: Terz–Grundton–♭7 (T4)

- **Charakter:** Fallender Dreitonkeim.
- **Noten:** ♭3+2Okt @ 0, Dauer 960, v96; 1+2Okt @ 960, Dauer 960, v92; ♭7+1Okt @ 1920, Dauer 1920, v96
- **Intervalle:** kleine Terz↓, große Sekunde↓
- **Tonfunktionen:** ♭3+2Okt=A, 1+2Okt=A, ♭7+1Okt=T (Bezug Molldreiklang, Äolisch (natürliches Moll))
- **Register:** TU-Basis + 22…27 Halbtöne; **XYZ:** X 0,20–0,80 · Y 0,00–0,70 · Z 0,00–0,50; **Evidenz:** E – eigenständige Gestaltung

#### DS-TU18 Keim C: Quart-Ruf (T4)

- **Charakter:** Grundton, Quarte, ♭3; Rufcharakter.
- **Noten:** 1+2Okt @ 0, Dauer 480, v96; 4+2Okt @ 480, Dauer 1440, v96; ♭3+2Okt @ 1920, Dauer 1920, v92
- **Intervalle:** Quarte↑, große Sekunde↓
- **Tonfunktionen:** 1+2Okt=A, 4+2Okt=T, ♭3+2Okt=A (Bezug Molldreiklang, Äolisch (natürliches Moll))
- **Register:** TU-Basis + 24…29 Halbtöne; **XYZ:** X 0,20–0,80 · Y 0,00–0,70 · Z 0,10–0,50; **Evidenz:** E – eigenständige Gestaltung

#### DS-TU19 Keim D: Dur-Licht (T4)

- **Charakter:** Terz, Quinte, große Septime in Dur.
- **Noten:** 3+2Okt @ 0, Dauer 960, v96; 5+2Okt @ 960, Dauer 960, v92; 7+2Okt @ 1920, Dauer 1920, v96
- **Intervalle:** kleine Terz↑, große Terz↑
- **Tonfunktionen:** 3+2Okt=A, 5+2Okt=A, 7+2Okt=T (Bezug Durdreiklang, Ionisch (Dur))
- **Register:** TU-Basis + 28…35 Halbtöne; **XYZ:** X 0,60–1,00 · Y 0,00–0,60 · Z 0,00–0,40; **Evidenz:** E – eigenständige Gestaltung

#### DS-TU20 Fallender hoher Grundton (T6)

- **Charakter:** Optional mit Pitch-Bend abwärts (Bernstein-Prinzip; Bend-Bereich instrumentabhängig).
- **Noten:** 1+3Okt @ 0, Dauer 1920, v100
- **Tonfunktionen:** 1+3Okt=A (Bezug Molldreiklang, Äolisch (natürliches Moll))
- **Register:** TU-Basis + 36…36 Halbtöne; **XYZ:** X 0,00–0,80 · Y 0,00–0,70 · Z 0,30–0,80; **Evidenz:** N – Verfahren nachgewiesen

#### DS-TU21 Fallende Quinte (T6)

- **Charakter:** Langer Ton; Bend optional.
- **Noten:** 5+2Okt @ 0, Dauer 2880, v100
- **Tonfunktionen:** 5+2Okt=A (Bezug Molldreiklang, Äolisch (natürliches Moll))
- **Register:** TU-Basis + 31…31 Halbtöne; **XYZ:** X 0,00–0,80 · Y 0,00–0,70 · Z 0,30–0,80; **Evidenz:** N – Verfahren nachgewiesen

#### DS-TU22 Fallender Ton als Paar (T6)

- **Charakter:** Kurzer Anlauf, dann der fallende Ton (Bend optional).
- **Noten:** 5+2Okt @ 0, Dauer 480, v90; 1+3Okt @ 480, Dauer 2400, v100
- **Intervalle:** Quarte↑
- **Tonfunktionen:** 5+2Okt=A, 1+3Okt=A (Bezug Molldreiklang, Äolisch (natürliches Moll))
- **Register:** TU-Basis + 31…36 Halbtöne; **XYZ:** X 0,00–0,80 · Y 0,00–0,70 · Z 0,30–0,80; **Evidenz:** E – eigenständige Gestaltung

#### DS-TU23 Antwort Quarte abwärts (T7)

- **Charakter:** Zweitonantwort 4 → 1.
- **Noten:** 4+2Okt @ 0, Dauer 480, v96; 1+2Okt @ 480, Dauer 1440, v96
- **Intervalle:** Quarte↓
- **Tonfunktionen:** 4+2Okt=T, 1+2Okt=A (Bezug Molldreiklang, Äolisch (natürliches Moll))
- **Register:** TU-Basis + 24…29 Halbtöne; **XYZ:** X 0,20–0,90 · Y 0,00–0,70 · Z 0,00–0,50; **Evidenz:** E – eigenständige Gestaltung

#### DS-TU24 Antwort Halbton (T7)

- **Charakter:** ♭6 → 5; seufzend.
- **Noten:** ♭6+2Okt @ 0, Dauer 480, v96; 5+2Okt @ 480, Dauer 1440, v96
- **Intervalle:** kleine Sekunde↓
- **Tonfunktionen:** ♭6+2Okt=T, 5+2Okt=A (Bezug Molldreiklang, Äolisch (natürliches Moll))
- **Register:** TU-Basis + 31…32 Halbtöne; **XYZ:** X 0,00–0,60 · Y 0,00–0,70 · Z 0,20–0,70; **Evidenz:** E – eigenständige Gestaltung

#### DS-TU25 Antwort Oktave (T7)

- **Charakter:** Grundton springt zur Oktave; Signal.
- **Noten:** 1+2Okt @ 0, Dauer 480, v96; 1+3Okt @ 480, Dauer 1440, v96
- **Intervalle:** Oktave↑
- **Tonfunktionen:** 1+2Okt=A, 1+3Okt=A (Bezug Molldreiklang, Äolisch (natürliches Moll))
- **Register:** TU-Basis + 24…36 Halbtöne; **XYZ:** X 0,20–1,00 · Y 0,10–0,80 · Z 0,00–0,50; **Evidenz:** E – eigenständige Gestaltung

#### DS-TU26 Rhythmischer Dreifachton (T5)

- **Charakter:** Kurzer Einwurf aus drei gleichen Tönen.
- **Noten:** 1+2Okt @ 0, Dauer 240, v100; 1+2Okt @ 240, Dauer 240, v90; 1+2Okt @ 480, Dauer 480, v100
- **Intervalle:** Prime, Prime
- **Tonfunktionen:** 1+2Okt=A, 1+2Okt=A, 1+2Okt=A (Bezug Molldreiklang, Äolisch (natürliches Moll))
- **Register:** TU-Basis + 24…24 Halbtöne; **XYZ:** X 0,00–1,00 · Y 0,30–1,00 · Z 0,30–0,80; **Evidenz:** E – eigenständige Gestaltung

#### DS-TU27 Einwurf Quinte–Oktave (T5)

- **Charakter:** Zweitoniger Akzent-Einwurf.
- **Noten:** 5+2Okt @ 0, Dauer 240, v100; 1+3Okt @ 240, Dauer 720, v100
- **Intervalle:** Quarte↑
- **Tonfunktionen:** 5+2Okt=A, 1+3Okt=A (Bezug Molldreiklang, Äolisch (natürliches Moll))
- **Register:** TU-Basis + 31…36 Halbtöne; **XYZ:** X 0,00–1,00 · Y 0,30–1,00 · Z 0,20–0,70; **Evidenz:** E – eigenständige Gestaltung

#### DS-TU28 Leiser Nachschlag (T5)

- **Charakter:** Ein Ton auf dem Offbeat; nach einem Phrasenende.
- **Noten:** 1+2Okt @ 480, Dauer 480, v72
- **Tonfunktionen:** 1+2Okt=A (Bezug Molldreiklang, Äolisch (natürliches Moll))
- **Register:** TU-Basis + 24…24 Halbtöne; **XYZ:** X 0,00–1,00 · Y 0,00–0,50 · Z 0,00–0,60; **Evidenz:** E – eigenständige Gestaltung

### DS-TO Operationen (Echo und Erinnerung)

| ID | Name | Typ | Operation | Beschreibung | Evidenz |
|---|---|---|---|---|---|
| DS-TO01 | Echo +12, zwei Töne | T5 | `echo:2:12:3:0.7` | Wiederholt die letzten zwei Töne eines Sequencers eine Oktave höher, 3/16 später, 30 % leiser. | N |
| DS-TO02 | Echo +24, ein Ton | T5 | `echo:1:24:2:0.6` | Ein einzelner Ton zwei Oktaven höher, 1/8 später. | N |
| DS-TO03 | Echo +12, drei Töne | T5 | `echo:3:12:2:0.65` | Drei Töne als hohe Antwort. | N |
| DS-TO04 | Tiefes Schattenecho | T5 | `echo:2:-12:4:0.6` | Zwei Töne eine Oktave tiefer, eine Viertel später; Schatten statt Echo. | E |
| DS-TO05 | Erinnerung angepasst | T8 | `fit` | Ein Keim kehrt nach einem Klangwechsel wieder; jeder Ton wird auf den nächsten Akkordton (±1–2 Halbtöne) gerückt. | E |
| DS-TO06 | Erinnerung transponiert | T8 | `trans` | Ein Keim kehrt als Ganzes um ein Intervall verschoben wieder (z. B. nach einer Terzschwelle −4). | E |
| DS-TO07 | Erinnerung als Fragment in fremder Lage | T8 | `frag+oct` | Nur zwei Töne des Keims, eine Oktave versetzt. | E |

Echo-Parameter: `echo:Anzahl Töne:Intervall:Verzögerung in 16teln:Velocity-Faktor`. Anpassen: jeder Ton rückt auf den nächstgelegenen Akkordton (±1 oder ±2 Halbtöne), sonst bleibt er.

## 9. DS-HM optionale Lead-Motive

HM bleibt optional. Viele Lead-Motive sind Endgestalten von TU-Keimen (Fragment-Exposition).

- **DS-HM01 Vollgestalt von Keim A** (8 Töne, 3,00 Takte): 5+1Okt ♭6+1Okt 5+1Okt ♭3+1Okt 4+1Okt ♭3+1Okt 2+1Okt 1+1Okt – Endgestalt der Fragment-Exposition von Keim A (eigene Melodie). XYZ X 0,20–0,80 · Y 0,10–0,70 · Z 0,10–0,50; N – Verfahren nachgewiesen
- **DS-HM02 Vollgestalt von Keim B** (7 Töne, 3,00 Takte): ♭3+1Okt 1+1Okt ♭7 1+1Okt ♭3+1Okt 5+1Okt 4+1Okt – Endgestalt von Keim B; fällt, steigt, bleibt offen auf der Quarte. XYZ X 0,25–0,80 · Y 0,10–0,70 · Z 0,00–0,45; E – eigenständige Gestaltung
- **DS-HM03 Nostalgische Linie in Dur** (8 Töne, 3,00 Takte): 3+1Okt 2+1Okt 1+1Okt 7 6 5 6 7 – Absteigend, wieder ansteigend zur Septime; Erinnerung. XYZ X 0,60–1,00 · Y 0,00–0,60 · Z 0,00–0,35; E – eigenständige Gestaltung
- **DS-HM04 Melancholische Bogenlinie** (6 Töne, 3,00 Takte): 1+1Okt ♭3+1Okt 5+1Okt ♭7+1Okt ♭6+1Okt 5+1Okt – Aufstieg zur ♭7, Rückfall über ♭6. XYZ X 0,30–0,75 · Y 0,00–0,60 · Z 0,00–0,40; E – eigenständige Gestaltung
- **DS-HM05 Choral-Melodie** (5 Töne, 4,00 Takte): 5+1Okt 4+1Okt ♭3+1Okt 2+1Okt 1+1Okt – Langsame Oberstimme für Choralketten, vier Takte. XYZ X 0,20–0,70 · Y 0,30–1,00 · Z 0,00–0,30; E – eigenständige Gestaltung
- **DS-HM06 Spieluhr-Lead** (7 Töne, 1,00 Takte): 1+2Okt ♭3+2Okt 2+2Okt 1+2Okt ♭7+1Okt 1+2Okt 5+1Okt – Sieben kurze hohe Töne; eigene Kontur, keine Kinderreim-Kopie. XYZ X 0,35–0,90 · Y 0,00–0,60 · Z 0,20–0,70; E – eigenständige Gestaltung
- **DS-HM07 Frage-Antwort-Lead** (8 Töne, 2,50 Takte): 1+1Okt ♭3+1Okt 5+1Okt ♭6+1Okt 5+1Okt ♭3+1Okt 2+1Okt 1+1Okt – Aufsteigende Frage, fallende Antwort über drei Takte. XYZ X 0,30–0,75 · Y 0,10–0,70 · Z 0,10–0,50; E – eigenständige Gestaltung
- **DS-HM08 Dorische Erinnerung** (5 Töne, 2,00 Takte): 1+1Okt 2+1Okt ♭3+1Okt 6+1Okt 5+1Okt – Bis zur großen Sexte; kühl hoffend. XYZ X 0,50–0,90 · Y 0,00–0,60 · Z 0,00–0,40; E – eigenständige Gestaltung
- **DS-HM09 Weite Klage mit Rückfall** (4 Töne, 2,00 Takte): 1+1Okt ♭7+1Okt ♭6+1Okt 5+1Okt – Septsprung, dann zwei Stufen abwärts. XYZ X 0,30–0,80 · Y 0,00–0,60 · Z 0,00–0,40; E – eigenständige Gestaltung
- **DS-HM10 Erinnerungslinie hell** (6 Töne, 3,00 Takte): 5+1Okt 6+1Okt 7+1Okt 1+2Okt 7+1Okt 5+1Okt – Zur Oktave und zurück; hell, nicht fröhlich. XYZ X 0,65–1,00 · Y 0,10–0,70 · Z 0,00–0,35; E – eigenständige Gestaltung
- **DS-HM11 Bedrohliche Lead-Zelle** (5 Töne, 2,00 Takte): 1+1Okt ♭2+1Okt 1+1Okt ♭7 ♭2+1Okt – Grundton und ♭2 umkreisen sich. XYZ X 0,00–0,40 · Y 0,20–0,90 · Z 0,50–0,95; E – eigenständige Gestaltung
- **DS-HM12 Phrygische Linie** (5 Töne, 2,00 Takte): 1+1Okt ♭2+1Okt ♭3+1Okt ♭2+1Okt 1+1Okt – Ritualhafte Kleinsekund-Linie. XYZ X 0,00–0,45 · Y 0,10–0,80 · Z 0,30–0,80; E – eigenständige Gestaltung
- **DS-HM13 Sechston-Lead mit ♭6** (6 Töne, 2,00 Takte): 5+1Okt ♭6+1Okt 4+1Okt ♭3+1Okt 2+1Okt 1+1Okt – Sechs Töne, fallend über ♭6, 4, ♭3, 2. XYZ X 0,20–0,70 · Y 0,10–0,70 · Z 0,20–0,60; E – eigenständige Gestaltung
- **DS-HM14 Große Linie ohne Triumph** (6 Töne, 4,00 Takte): 1+1Okt 5+1Okt 1+2Okt ♭7+1Okt ♭6+1Okt 5+1Okt – Kulmination zur Oktave, dann Abstieg; kein Dur-Ziel. XYZ X 0,30–0,80 · Y 0,50–1,00 · Z 0,00–0,40; E – eigenständige Gestaltung
- **DS-HM15 Schattenmelodie** (4 Töne, 1,50 Takte): 1+1Okt ♭3+1Okt 5+1Okt ♭6+1Okt – A–C–E–F: über Am mit ♭6-Schatten, über Fmaj7 ganz Akkordton. XYZ X 0,35–0,80 · Y 0,00–0,60 · Z 0,00–0,40; E – eigenständige Gestaltung
- **DS-HM16 Ruhige Zweiphrasen-Linie** (5 Töne, 4,00 Takte): 5+1Okt ♭3+1Okt 4+1Okt ♭3+1Okt 1+1Okt – Zwei kurze Phrasen mit langem Schlusston. XYZ X 0,30–0,75 · Y 0,00–0,50 · Z 0,00–0,30; E – eigenständige Gestaltung
- **DS-HM17 Endgestalt von Keim C** (6 Töne, 2,00 Takte): 1+1Okt 4+1Okt ♭3+1Okt 1+1Okt ♭7 1+1Okt – Keim C (Quart-Ruf) mit fallender Fortsetzung. XYZ X 0,20–0,80 · Y 0,00–0,70 · Z 0,10–0,50; E – eigenständige Gestaltung
- **DS-HM18 Hymnische Quartlinie** (4 Töne, 3,00 Takte): 1+1Okt 4+1Okt ♭7+1Okt 5+1Okt – Quartschritte aufwärts, Quinte als langer Schluss. XYZ X 0,30–0,80 · Y 0,40–1,00 · Z 0,00–0,35; E – eigenständige Gestaltung

## 10. DS-E Entwicklung und Übergänge

Ergänzt die acht vorhandenen Strategien (Stasis, Rotation, Atmung, Wanderung, Umfärbung, Ereignisfeld, Blockverschiebung, Reduktion und Wiederaufnahme). Übergänge gelten nur bei tatsächlicher XYZ-Veränderung; bei konstanter Position wird nichts erzwungen.

#### DS-E01 Fragment-Exposition (Entwicklung)

- **Prinzip:** Ein Motiv erscheint zuerst als Zweitonkeim im Tupfer, später erweitert, zuletzt vollständig (optional in HM).
- **Verfahren:** (1) Keim (2 Töne) an 1–3 Stellen. (2) Erweiterung (3–5 Töne) frühestens nach der ersten Wiederkehr. (3) Vollgestalt optional in HM oder AR. (4) Rückweg erlaubt: nach der Vollgestalt wieder nur der Keim.
- **XYZ-Bezug:** konstante oder wandernde Position; **Evidenz:** N – Verfahren nachgewiesen; **Studien:** DS-S01, DS-S03, DS-S06, DS-S19

#### DS-E02 Periodenschichtung (Entwicklung)

- **Prinzip:** Zwei Schichten mit unterschiedlicher Periodenlänge auf gemeinsamer Uhr; ihr gemeinsamer Wiederkehrpunkt ist das kleinste gemeinsame Vielfache.
- **Verfahren:** (1) Perioden in Sechzehnteln bestimmen (z. B. 16 und 12). (2) Wiederkehr = kgV (16, 12) = 48 Sechzehntel = 3 Takte. (3) Mit Harmonieperiode (z. B. 8 Takte) verrechnen: kgV(3, 8) = 24 Takte. (4) Keine Z-Mindestschwelle; die Wahl ist eine Präferenz nach Kontext.
- **XYZ-Bezug:** jede Position; bei hoher Z bevorzugt; **Evidenz:** N – Verfahren nachgewiesen; **Studien:** DS-S07, DS-S14

#### DS-E03 Bassrotation unter Konstanz (Entwicklung)

- **Prinzip:** Der Oberbau bleibt unverändert, nur der Bass wandert; die Bedeutung des Klangs kippt.
- **Verfahren:** (1) Oberbau als feste Tonmenge. (2) Bassfolge aus Tönen, die mit dem Oberbau benennbare Klänge ergeben. (3) Jeder Basston ändert die Tonfunktionen aller Oberstimmen.
- **XYZ-Bezug:** alle X; dunkel: Halbtonbässe, hell: Terz- und Quartbässe; **Evidenz:** E – eigenständige Gestaltung; **Studien:** DS-S04, DS-S05

#### DS-E04 Klangbogen (Klang)

- **Prinzip:** Eine Rolle öffnet und schließt sich klanglich über 16–64 Takte, ohne Notenänderung (nur in Modulationsstudien).
- **Verfahren:** (1) Abstrakte Dimension wählen (Helligkeit, Ausklang …). (2) Bogenform mit eigener Periode, nicht synchron zur Harmonie. (3) Zuordnung zum Instrument nimmt der Anwender vor.
- **XYZ-Bezug:** jede Position; **Evidenz:** N – Verfahren nachgewiesen; **Studien:** DS-MS01, DS-MS02, DS-MS03, DS-MS04

#### DS-E05 Rollentausch (Entwicklung)

- **Prinzip:** Eine Figur wechselt die Rolle und verändert dabei ihre Gestalt: AR → TU (ausgedünnt), KB → LB (verlängert), AR → LF (augmentiert).
- **Verfahren:** (1) Quellrolle endet an einer Phrasengrenze. (2) Zielrolle übernimmt dieselbe Tonfolge mit Ausdünnung (Positionen weglassen), Verlängerung oder Augmentation. (3) Register der Zielrolle beachten.
- **XYZ-Bezug:** konstante Position; **Evidenz:** E – eigenständige Gestaltung; **Studien:** DS-S21

#### DS-E06 Erinnerungsrückkehr (Entwicklung)

- **Prinzip:** Ein früher gehörtes Fragment kehrt in fremder Harmonik wieder, angepasst oder transponiert.
- **Verfahren:** (1) Keim aus dem Motivgedächtnis. (2) Nach Klangwechsel: Anpassung (nächster Akkordton) oder Transposition. (3) Die Kontur bleibt erkennbar.
- **XYZ-Bezug:** konstante oder wandernde Position; **Evidenz:** E – eigenständige Gestaltung; **Studien:** DS-S03, DS-S06, DS-S10, DS-S11, DS-S25, DS-S30

#### DS-E07 Gefrieren (Entwicklung)

- **Prinzip:** Ein Sequencer stoppt; sein letzter Ton klingt als Fläche weiter.
- **Verfahren:** (1) Sequencer endet an Phrasengrenze. (2) Ein Zellton (meist Quinte) wird als Halteton in LF übernommen. (3) Optional später identische oder veränderte Wiederaufnahme.
- **XYZ-Bezug:** konstante Position; **Evidenz:** E – eigenständige Gestaltung; **Studien:** DS-S06, DS-S13

#### DS-E08 Gate-Atmung (Entwicklung)

- **Prinzip:** Gleiche Noten, wandernde Tondauern.
- **Verfahren:** (1) Gate-Faktor je Abschnitt (z. B. 0,3 → 0,55 → 0,8 → 0,55). (2) Kein Überlappen: Dauer höchstens bis zum nächsten Einsatz.
- **XYZ-Bezug:** konstante Position; **Evidenz:** N – Verfahren nachgewiesen; **Studien:** DS-S22

#### DS-E09 Ein-Schritt-Mutation (Entwicklung)

- **Prinzip:** An einem Zeitpunkt ändert sich genau ein Schritt einer Zelle (Ton, Oktave oder Pause).
- **Verfahren:** (1) Position und Änderung festlegen. (2) Gilt ab diesem Takt für alle folgenden Zyklen. (3) Keine feste Taktzahl; Mutation ist Option, keine Pflicht.
- **XYZ-Bezug:** konstante Position; **Evidenz:** N – Verfahren nachgewiesen; **Studien:** DS-S22

#### DS-E10 Inkommensurable Schichtperioden (Langzeit)

- **Prinzip:** Harmonie, Sequencer und Tupfer-Wiederkehr haben teilerfremde Perioden; kein Durchgang gleicht dem vorigen.
- **Verfahren:** (1) Perioden wählen (z. B. Harmonie 8, Sequencer 3, Tupfer 5 Takte). (2) Gesamtwiederkehr = kgV (hier 120 Takte). (3) Jede Schicht bleibt für sich hypnotisch.
- **XYZ-Bezug:** konstante Position; **Evidenz:** N – Verfahren nachgewiesen; **Studien:** DS-S06

#### DS-E11 Seitwärtsentwicklung (Langzeit)

- **Prinzip:** Farbwechsel ohne Intensitätsänderung: Harmonie wechselt die Kategorie, Dichte und Lautstärke bleiben.
- **Verfahren:** (1) Gleiche Rollen und Dichte. (2) Harmonievorlage wechselt an Phrasengrenzen (z. B. Schattenpaar → Drone-Wechsel). (3) Kein Spannungsaufbau.
- **XYZ-Bezug:** konstante Position; **Evidenz:** E – eigenständige Gestaltung; **Studien:** DS-S23

#### DS-E12 Bewegung und Stillstand (Langzeit)

- **Prinzip:** Phasen mit Sequencer wechseln mit Phasen reiner Fläche.
- **Verfahren:** (1) Stillstand 8–16 Takte, Bewegung 16–32 Takte. (2) Rückkehr der Bewegung darf verändert sein (Register, Bass).
- **XYZ-Bezug:** konstante Position; **Evidenz:** I – begründete Interpretation; **Studien:** DS-S06

#### DS-E13 Übergang ruhig → bedrohlich (Übergang)

- **Prinzip:** Bass rückt auf ♭2 oder ♭6, Tupfer wechselt von A- zu F/U-Tönen, Pulsdichte steigt.
- **Verfahren:** (1) Gelenk empfohlen, nicht verpflichtend (gemeinsamer Ton oder gehaltener Bass). (2) Nur bei tatsächlicher XYZ-Veränderung.
- **XYZ-Bezug:** XYZ-Fahrt; **Evidenz:** E – eigenständige Gestaltung; **Studien:** dokumentiert

#### DS-E14 Übergang bedrohlich → ruhig (Übergang)

- **Prinzip:** Reduktion auf Drone und ein Tupfer-Echo, oder Gefrieren.
- **Verfahren:** (1) Dichte wird entfernt, nicht ausgeblendet. (2) Kadenz nicht nötig.
- **XYZ-Bezug:** XYZ-Fahrt; **Evidenz:** E – eigenständige Gestaltung; **Studien:** dokumentiert

#### DS-E15 Übergang ruhig → melancholisch (Übergang)

- **Prinzip:** Schattenpaar einführen, Tupfer-Fragment in Mittellage, langsame Öffnung.
- **Verfahren:** (1) Harmonie wechselt zu DH1/DH8. (2) Fragment-Exposition beginnt.
- **XYZ-Bezug:** XYZ-Fahrt; **Evidenz:** E – eigenständige Gestaltung; **Studien:** dokumentiert

#### DS-E16 Übergang melancholisch → bedrohlich (Übergang)

- **Prinzip:** Tarnhelm-Schritt; ein bekanntes Fragment kehrt verfremdet wieder.
- **Verfahren:** (1) DH7 Tarnhelm. (2) Erinnerung angepasst.
- **XYZ-Bezug:** XYZ-Fahrt; **Evidenz:** E – eigenständige Gestaltung; **Studien:** dokumentiert

#### DS-E17 Übergang bedrohlich → melancholisch (Übergang)

- **Prinzip:** Nach dem Höhepunkt ein Takt Stille, dann Choral.
- **Verfahren:** (1) Stille 1 Takt. (2) Choralvorlage (DH6), gemeinsamer Ton als Option.
- **XYZ-Bezug:** XYZ-Fahrt; **Evidenz:** E – eigenständige Gestaltung; **Studien:** dokumentiert

#### DS-E18 Offener Schluss oder harter Schnitt (Übergang)

- **Prinzip:** Enden ohne Kadenz: Liegeton mit Klangschließung, offener U-Ton oder harter Schnitt ohne Gelenk.
- **Verfahren:** (1) Ein harter Schnitt ist zulässig; ein Gelenk ist eine Option, keine Pflicht. (2) V–I ist nicht verboten, aber nicht Standard.
- **XYZ-Bezug:** jede Position; **Evidenz:** E – eigenständige Gestaltung; **Studien:** dokumentiert

## 11. Klangmodulation (getrennt dokumentiert)

Klangentwicklung ist keine Komposition. STROMSCORE beschreibt sie mit **abstrakten Dimensionen**: Helligkeit, Schärfe/Resonanz, Ausklang/Länge, Bewegung/Modulationstiefe, Nähe/Raum, Gewicht. Die Zuordnung zu MIDI-Controllern trifft der Anwender je Instrument und Preset. Es gibt keine feste Belegung.

| ID | Name | Dimension | Kurve | Periode | Anwendung | Evidenz |
|---|---|---|---|---|---|---|
| DS-K01 | Helligkeitsbogen | Helligkeit | Bogen (0 → 1 → 0,3) | 40 Takte | stehende Sequencer-Zelle; Entwicklung ohne Notenänderung | N |
| DS-K02 | Ausklang-Atmung | Ausklang/Länge | Atmung (Sinus, sehr langsam) | 12 Takte | Arpeggio oder Glocken; gegen 8-Takt-Harmonie verschoben | E |
| DS-K03 | Gegenlauf Fläche/Sequencer | Helligkeit | Gegenläufige Rampen (eine öffnet, eine schließt) | 32 Takte | schützt Dialog: Gesamthelligkeit bleibt etwa konstant | E |
| DS-K04 | Treppe an Phrasengrenzen | Helligkeit | Treppe (Stufen alle 8 Takte) | 32 Takte | Seitwärtsentwicklung, ohne Gleiten | E |
| DS-K05 | Schärfe-Ereignis | Schärfe/Resonanz | Ereignis (kurzer Ausschlag, Abklingen über 1 Takt) | 1 Takte | Tupfer-Ereignisse hörbar machen | E |
| DS-K06 | Bewegungstiefe nach Unruhe | Bewegung/Modulationstiefe | Rampe, Tiefe folgt Z | 16 Takte | psychologische Unruhe ohne Notenänderung | E |
| DS-K07 | Raumtiefe-Drift | Nähe/Raum | langsame Rampe | 64 Takte | lange Dialogszenen; Fläche rückt nach hinten | E |
| DS-K08 | Gewicht nach Intensität | Gewicht | Treppe nach Y | 16 Takte | kraftvoll ohne Notendichte | E |
| DS-K09 | Schließung zum Schluss | Helligkeit | Rampe 1 → 0 | 8 Takte | offener Schluss ohne Kadenz | E |
| DS-K10 | Unregelmäßige Atmung | Bewegung/Modulationstiefe | Atmung mit wechselnder Periode (12, 10, 14 Takte) | 12 Takte | psychologische Unruhe, Disasterpeace-Prinzip „randomness in the sound“ als Klangverlauf | N |

**Prinzipien:** eigene Periode je Rolle, nicht synchron zur Harmonie; Gegenlauf schützt Dialog; X steuert Helligkeit, Y Gewicht, Z Bewegung und Unregelmäßigkeit; keine Simulation von Klangbewegung durch Noten.

**Optionale Modulationsstudien** liegen getrennt im Ordner `optional_Modulation/` des ZIP. Die Kurven stehen dort auf den General-Purpose-Controllern **CC16–CC19 (GP1–GP4)** – ausdrücklich als Platzhalter zum Umleiten in der DAW, nicht als Empfehlung einer Belegung. Die normalen Studien enthalten keine Controller-Daten.

- **DS-MS01 Klangbogen auf stehender Zelle:** 64 Takte dieselbe Zelle; Helligkeitsbogen über 40 Takte, Ausklang-Atmung über 12 Takte. Kurven: AR Helligkeit auf GP1 (bogen); AR Ausklang auf GP2 (atmung)
- **DS-MS02 Gegenlauf Fläche und Sequencer:** Fläche schließt sich, Sequencer öffnet sich über 32 Takte; Gesamthelligkeit etwa konstant. Kurven: LF Helligkeit auf GP1 (rampe); AR Helligkeit auf GP1 (rampe); LF Helligkeit auf GP1 (rampe); AR Helligkeit auf GP1 (rampe)
- **DS-MS03 Treppe an Phrasengrenzen:** Helligkeit in Stufen alle 8 Takte; Notenmaterial unverändert. Kurven: AR Helligkeit auf GP1 (treppe); LF Helligkeit auf GP1 (treppe)
- **DS-MS04 Schärfe-Ereignisse im Tupfer:** Jedes Tupfer-Ereignis bekommt einen kurzen Schärfe-Ausschlag; die Fläche driftet langsam nach hinten. Kurven: TU Schärfe auf GP3 (ereignis); LF Raum auf GP4 (rampe)

## 12. DS-S Studien

Studien sind mögliche musikalische Verläufe, keine verpflichtenden Formpläne. Tempo ist ein Vorschlag. Alle Studien laufen bei **konstanter XYZ-Position**.

| ID | Name | Takte | XYZ | Strategie | ohne |
|---|---|---|---|---|---|
| DS-S01 | Warme Erinnerung | 64 | 0,85/0,15/0,10 | Fragment-Exposition | AR, GS, HM, Puls |
| DS-S02 | Warme Erinnerung mit langsamem Arpeggio | 32 | 0,80/0,30/0,15 | Stasis | GS, HM |
| DS-S03 | Schattenpaar mit Fluchtweg | 40 | 0,60/0,40/0,25 | Fragment-Exposition | GS |
| DS-S04 | Bassrotation unter gehaltenem Oberbau | 64 | 0,45/0,25/0,20 | Bassrotation unter Konstanz | AR, GS, HM, Puls |
| DS-S05 | Bassrotation mit Puls und Echo | 32 | 0,60/0,55/0,40 | Bassrotation unter Konstanz | GS, HM |
| DS-S06 | Nebelgang über 128 Takte | 128 | 0,45/0,35/0,30 | Inkommensurable Schichtperioden | – |
| DS-S07 | Hypnotische Stasis mit Periodenschichtung | 128 | 0,40/0,50/0,45 | Stasis | HM |
| DS-S08 | Sakraler Choral | 40 | 0,30/0,75/0,15 | Stasis | AR, GS |
| DS-S09 | Ritual mit Puls | 32 | 0,20/0,80/0,50 | Stasis | GS, HM |
| DS-S10 | Spieluhr über Drone | 64 | 0,70/0,10/0,55 | Ereignisfeld | AR, GS, HM, Puls |
| DS-S11 | Tarnhelm-Schwelle | 32 | 0,30/0,40/0,60 | Erinnerungsrückkehr | AR, GS, HM, Puls |
| DS-S12 | Hexatonischer Pol | 32 | 0,50/0,20/0,70 | Stasis | AR, GS, HM, Puls |
| DS-S13 | Gefrieren | 32 | 0,40/0,60/0,40 | Gefrieren | GS, HM |
| DS-S14 | Bedrohliche Jagd ohne Hektik | 32 | 0,15/0,85/0,85 | Periodenschichtung | AR, HM |
| DS-S15 | Orgelchoral, dunkel und ruhig | 48 | 0,10/0,85/0,10 | Stasis | AR, GS, HM |
| DS-S16 | Flüstern | 48 | 0,10/0,10/0,85 | Ereignisfeld | AR, GS, HM, Puls |
| DS-S17 | Aufbruch | 32 | 0,85/0,80/0,75 | Stasis | HM |
| DS-S18 | Weite ohne Triumph | 32 | 0,85/0,80/0,15 | Stasis | GS |
| DS-S19 | Fragment-Exposition über 64 Takte | 64 | 0,45/0,40/0,30 | Fragment-Exposition | GS |
| DS-S20 | Dialog Gegenstimme – Tupfer | 32 | 0,30/0,40/0,50 | Stasis | AR, HM, Puls |
| DS-S21 | Rollentausch Sequencer → Tupfer | 32 | 0,40/0,45/0,35 | Rollentausch | GS, HM |
| DS-S22 | Gate-Atmung und Ein-Schritt-Mutation | 64 | 0,50/0,50/0,40 | Gate-Atmung | GS, HM |
| DS-S23 | Seitwärtsentwicklung | 64 | 0,55/0,35/0,25 | Seitwärtsentwicklung | GS, HM |
| DS-S24 | Tritonus-Spiegel | 32 | 0,60/0,30/0,75 | Stasis | AR, GS, HM, Puls |
| DS-S25 | Lichtwechsel über Drone | 48 | 0,90/0,25/0,10 | Ereignisfeld | AR, GS, HM, Puls |
| DS-S26 | Moll-Septkette mit Antwortbass | 32 | 0,35/0,30/0,30 | Stasis | AR, GS, HM |
| DS-S27 | Drone-Wechsel phrygisch | 32 | 0,25/0,30/0,55 | Stasis | AR, GS, HM |
| DS-S28 | Liegeton E über chromatischen Klängen | 40 | 0,55/0,45/0,50 | Umfärbung | AR, GS, HM |
| DS-S29 | Gruft | 48 | 0,10/0,10/0,10 | Stasis | AR, GS, HM, Puls |
| DS-S30 | Glasnebel | 48 | 0,85/0,10/0,80 | Ereignisfeld | AR, GS, HM, Puls |

#### DS-S01 Warme Erinnerung

- **Zweck:** Hell, leise, ruhig: Imaj7–vi9 mit Keim-Fragmenten im Tupfer; kein Sequencer, kein Puls.
- **Eckdaten:** 64 Takte 4/4, 66 BPM, Tonart A, Ionisch (Dur); XYZ (0,85 / 0,15 / 0,10), neutral
- **Harmonie:** ab T1 DS-H52 Imaj7–vi9-Wiege
- **Schichten:**
  - LF aus Harmonie
  - LB aus Harmonie
  - TU-Gedächtnis, Keim DS-TU19 Keim D: Dur-Licht: T5 frag, T13 frag, T21 Original, T33 frag+oct, T45 Original, T57 frag
- **Strategien:** Fragment-Exposition; DS-E01 Fragment-Exposition
- **MIDI:** `DS-S01_Warme_Erinnerung.mid` · Spuren LF, LB, TU · 102 Noten · Funktionen {'A': 102}

#### DS-S02 Warme Erinnerung mit langsamem Arpeggio

- **Zweck:** Add9-Kette mit Moll-iv, leise Dur-Wiege im Sequencer, Spieluhr-Splitter in den Lücken.
- **Eckdaten:** 32 Takte 4/4, 72 BPM, Tonart D, Ionisch (Dur); XYZ (0,80 / 0,30 / 0,15), neutral
- **Harmonie:** ab T1 DS-H55 Add9-Wiege mit Moll-iv
- **Schichten:**
  - LF aus Harmonie
  - LB aus Harmonie
  - AR: DS-Q21 Triolen-Kettenläufer, folgt Akkorden
  - TU-Gedächtnis, Keim DS-TU08 Dur-Spieluhr 3–2–1–5: T4 fit, T11 fit, T20 fit, T27 fit
- **Strategien:** Stasis; JC-T012 Langfristige Stasis
- **MIDI:** `DS-S02_Warme_Erinnerung_mit_langsamem_Arpeggio.mid` · Spuren LF, LB, AR, TU · 442 Noten · Funktionen {'A': 442}

#### DS-S03 Schattenpaar mit Fluchtweg

- **Zweck:** Nostalgisch: Schattenpaar mit Ausweg, Schatten-Arpeggio, Keim A wird bis zur Lead-Melodie entfaltet.
- **Eckdaten:** 40 Takte 4/4, 84 BPM, Tonart E, Äolisch (natürliches Moll); XYZ (0,60 / 0,40 / 0,25), neutral
- **Harmonie:** ab T1 DS-H02 Schattenpaar mit Fluchtweg
- **Schichten:**
  - LF aus Harmonie
  - LB aus Harmonie
  - AR: DS-Q01 Schattenpaar-Arpeggio (T5-40)
  - TU-Gedächtnis, Keim DS-TU15 Keim A: Quinte–♭6: T3 Original, T11 Original, T19 Original, T23 fit
  - HM: DS-HM01 Vollgestalt von Keim A an T29
- **Strategien:** Fragment-Exposition; DS-E01 Fragment-Exposition, DS-E06 Erinnerungsrückkehr
- **MIDI:** `DS-S03_Schattenpaar_mit_Fluchtweg.mid` · Spuren LF, LB, AR, TU, HM · 530 Noten · Funktionen {'A': 474, 'F': 37, 'T': 17, 'V': 2}

#### DS-S04 Bassrotation unter gehaltenem Oberbau

- **Zweck:** Am7 bleibt 64 Takte identisch; acht Basstöne geben acht Bedeutungen. Pulslos.
- **Eckdaten:** 64 Takte 4/4, 70 BPM, Tonart A, Äolisch (natürliches Moll); XYZ (0,45 / 0,25 / 0,20), neutral
- **Harmonie:** ab T1 DS-H07 Bassrotation unter Am7-Oberbau
- **Schichten:**
  - LF aus Harmonie
  - LB aus Harmonie
  - TU-Gedächtnis, Keim DS-TU06 Spieluhr ♭3–2–5: T6 Original, T15 Original, T29 Original, T38 fit, T51 Original, T60 frag+fit
- **Strategien:** Bassrotation unter Konstanz; DS-E03 Bassrotation unter Konstanz
- **MIDI:** `DS-S04_Bassrotation_unter_gehaltenem_Oberbau.mid` · Spuren LF, LB, TU · 177 Noten · Funktionen {'A': 173, 'T': 4}

#### DS-S05 Bassrotation mit Puls und Echo

- **Zweck:** Cmaj7-Oberbau über wanderndem Bass, Achtelbass folgt, Tupfer antwortet als Echo des Sequencers.
- **Eckdaten:** 32 Takte 4/4, 96 BPM, Tonart D, Äolisch (natürliches Moll); XYZ (0,60 / 0,55 / 0,40), mechanisch
- **Harmonie:** ab T1 DS-H10 Bassrotation unter Cmaj7-Oberbau
- **Schichten:**
  - LF aus Harmonie
  - LB aus Harmonie
  - KB: DS-B06 Rotationsbass in Achteln
  - AR: DS-Q22 Antwortlücken-Sequenz
  - TU-Gedächtnis, Keim DS-TU28 Leiser Nachschlag: T4 Echo, T9 Echo, T16 Echo, T21 Echo, T28 Echo
- **Strategien:** Bassrotation unter Konstanz; DS-E03 Bassrotation unter Konstanz
- **MIDI:** `DS-S05_Bassrotation_mit_Puls_und_Echo.mid` · Spuren LF, LB, KB, AR, TU · 529 Noten · Funktionen {'A': 414, 'T': 115}

#### DS-S06 Nebelgang über 128 Takte

- **Zweck:** Etablierung, Bewegung, Stillstand, veränderte Wiederaufnahme, offener Schluss – bei unveränderter XYZ-Position.
- **Eckdaten:** 128 Takte 4/4, 84 BPM, Tonart A, Äolisch (natürliches Moll); XYZ (0,45 / 0,35 / 0,30), neutral
- **Harmonie:** ab T1 DS-H07 Bassrotation unter Am7-Oberbau, ab T33 DS-H15 Nebelgang, ab T49 DS-H08 Pendel im Bass, ab T65 JC-H002 Oktavsäule, ab T81 DS-H07 Bassrotation unter Am7-Oberbau, ab T113 DS-H65 Pendel mit drittem Glied
- **Schichten:**
  - LF aus Harmonie
  - LB aus Harmonie
  - AR: DS-Q03 16er-Lückenzelle (T9-40)
  - AR: DS-Q03 16er-Lückenzelle (T81-112), Oktave +1
  - GS: DS-Q04 12er-Gegenzelle (T89-104)
  - KB: DS-B04 Rufbass (T25-40,97-112)
  - LF Halteton 5 (T49-56, Gefrieren)
  - TU-Gedächtnis, Keim DS-TU15 Keim A: Quinte–♭6: T5 Original, T13 Original, T21 Original, T28 Echo, T45 frag, T69 Original, T77 fit, T113 frag+oct, T101 Echo, T117 Original
  - HM: DS-HM01 Vollgestalt von Keim A an T53
- **Strategien:** Inkommensurable Schichtperioden; DS-E10 Inkommensurable Schichtperioden, DS-E07 Gefrieren, DS-E12 Bewegung und Stillstand, DS-E01 Fragment-Exposition, DS-E06 Erinnerungsrückkehr
- **MIDI:** `DS-S06_Nebelgang_ueber_128_Takte.mid` · Spuren LF, LB, KB, AR, TU, GS, HM · 1067 Noten · Funktionen {'A': 1027, 'F': 19, 'T': 20, 'V': 1}

#### DS-S07 Hypnotische Stasis mit Periodenschichtung

- **Zweck:** 128 Takte: 16er-, 12er- und Bassperiode auf gemeinsamer Uhr; Gesamtwiederkehr nach 24 Takten. Sonst nichts.
- **Eckdaten:** 128 Takte 4/4, 100 BPM, Tonart E, Äolisch (natürliches Moll); XYZ (0,40 / 0,50 / 0,45), mechanisch
- **Harmonie:** ab T1 DS-H03 Schattenpaar über Grundtonpedal
- **Schichten:**
  - LF aus Harmonie
  - LB: JC-B001 Tiefer Grundton-Drone
  - AR: DS-Q03 16er-Lückenzelle
  - GS: DS-Q04 12er-Gegenzelle, Oktave +1
  - KB: DS-B01 Oktavpuls mit Lücke
- **Strategien:** Stasis; DS-E02 Periodenschichtung, JC-T012 Langfristige Stasis
- **MIDI:** `DS-S07_Hypnotische_Stasis_mit_Periodenschichtung.mid` · Spuren LF, LB, KB, AR, GS · 3158 Noten · Funktionen {'A': 3009, 'T': 149}

#### DS-S08 Sakraler Choral

- **Zweck:** Kraftvoll, ruhig: Moll-Choral mit Orgelbass und langsamer Oberstimme.
- **Eckdaten:** 40 Takte 4/4, 60 BPM, Tonart D, Äolisch (natürliches Moll); XYZ (0,30 / 0,75 / 0,15), neutral
- **Harmonie:** ab T1 DS-H38 Choral i–iv–♭VI–♭VII
- **Schichten:**
  - LF aus Harmonie
  - LB aus Harmonie
  - KB: DS-B21 Sakraler Grundbass
  - HM: DS-HM05 Choral-Melodie an T1, T21
- **Strategien:** Stasis; JC-T012 Langfristige Stasis
- **MIDI:** `DS-S08_Sakraler_Choral.mid` · Spuren LF, LB, KB, HM · 130 Noten · Funktionen {'A': 126, 'T': 4}

#### DS-S09 Ritual mit Puls

- **Zweck:** Phrygischer Choral über Choralbass und orgelartiger Repetition; ein Stich.
- **Eckdaten:** 32 Takte 4/4, 88 BPM, Tonart A, Phrygisch; XYZ (0,20 / 0,80 / 0,50), psychologisch
- **Harmonie:** ab T1 DS-H42 Phrygischer Choral
- **Schichten:**
  - LF aus Harmonie
  - KB: DS-B14 Choralbass mit Quintvorschlag
  - AR: DS-Q18 Choral-Repetition, folgt Akkorden
  - ST an T17
- **Strategien:** Stasis; JC-T012 Langfristige Stasis
- **MIDI:** `DS-S09_Ritual_mit_Puls.mid` · Spuren LF, KB, AR, ST · 281 Noten · Funktionen {'A': 280, 'ST': 1}

#### DS-S10 Spieluhr über Drone

- **Zweck:** Hell, leise, unruhig: hoher Durklang über Moll-Drone, Dur-Spieluhr in unregelmäßigen Abständen. 64 Takte.
- **Eckdaten:** 64 Takte 4/4, 60 BPM, Tonart C, Äolisch (natürliches Moll); XYZ (0,70 / 0,10 / 0,55), psychologisch
- **Harmonie:** ab T1 DS-H46 Spieluhr-Dur über Moll-Drone
- **Schichten:**
  - LF aus Harmonie
  - LB: JC-B001 Tiefer Grundton-Drone
  - TU-Gedächtnis, Keim DS-TU08 Dur-Spieluhr 3–2–1–5: T5 trans, T12 trans, T20 trans, T31 trans+frag, T37 trans, T50 trans, T58 trans+frag
- **Hinweis:** Die Dur-Spieluhr wird um +3 Halbtöne auf den hohen E♭-Klang (♭III) gelegt; über dem C-Drone ist sie diatonisch, aber falsch verortet.
- **Strategien:** Ereignisfeld; DS-E06 Erinnerungsrückkehr
- **MIDI:** `DS-S10_Spieluhr_ueber_Drone.mid` · Spuren LF, LB, TU · 37 Noten · Funktionen {'A': 30, 'T': 2, 'V': 5}

#### DS-S11 Tarnhelm-Schwelle

- **Zweck:** Mollklänge im Großterzzirkel; der Spieluhr-Splitter kehrt nach jeder Schwelle angepasst wieder.
- **Eckdaten:** 32 Takte 4/4, 72 BPM, Tonart A, Chromatisch (frei, nur Akkordtöne + autorisierte Töne); XYZ (0,30 / 0,40 / 0,60), psychologisch
- **Harmonie:** ab T1 DS-H45 Doppel-Tarnhelm
- **Schichten:**
  - LF aus Harmonie
  - LB aus Harmonie
  - TU-Gedächtnis, Keim DS-TU06 Spieluhr ♭3–2–5: T2 Original, T6 fit, T10 fit, T18 Original, T22 trans, T30 fit
- **Strategien:** Erinnerungsrückkehr; DS-E06 Erinnerungsrückkehr
- **MIDI:** `DS-S11_Tarnhelm_Schwelle.mid` · Spuren LF, LB, TU · 50 Noten · Funktionen {'A': 47, 'T': 3}

#### DS-S12 Hexatonischer Pol

- **Zweck:** Zwei konsonante Klänge ohne gemeinsamen Ton (vorhandene Vorlage JC-H041); nur Fläche und Glockenschläge.
- **Eckdaten:** 32 Takte 4/4, 64 BPM, Tonart E, Chromatisch (frei, nur Akkordtöne + autorisierte Töne); XYZ (0,50 / 0,20 / 0,70), psychologisch
- **Harmonie:** ab T1 JC-H041 Kalte Mediante
- **Schichten:**
  - LF aus Harmonie
  - TU-Gedächtnis, Keim DS-TU02 Glockenschlag Grundton: T3 Original, T7 trans, T19 Original, T23 trans
- **Strategien:** Stasis; JC-T012 Langfristige Stasis
- **MIDI:** `DS-S12_Hexatonischer_Pol.mid` · Spuren LF, TU · 28 Noten · Funktionen {'A': 28}

#### DS-S13 Gefrieren

- **Zweck:** Oktavpuls und Gefrier-Zelle laufen 24 Takte, dann bleibt nur die Quinte als Fläche über dem Drone.
- **Eckdaten:** 32 Takte 4/4, 104 BPM, Tonart G, Äolisch (natürliches Moll); XYZ (0,40 / 0,60 / 0,40), mechanisch
- **Harmonie:** ab T1 DS-H64 Pendel 4+2 mit Farbwechsel, ab T25 JC-H001 Kalte Quintleere
- **Schichten:**
  - LF aus Harmonie
  - KB: DS-B01 Oktavpuls mit Lücke (T1-24)
  - AR: DS-Q13 Gefrier-Zelle (T1-24)
  - AR Halteton 5+1Okt (T25-32, Gefrieren)
  - LB: JC-B001 Tiefer Grundton-Drone (T25-32)
- **Strategien:** Gefrieren; DS-E07 Gefrieren
- **MIDI:** `DS-S13_Gefrieren.mid` · Spuren LF, LB, KB, AR · 584 Noten · Funktionen {'A': 584}

#### DS-S14 Bedrohliche Jagd ohne Hektik

- **Zweck:** Dunkel, kraftvoll, unruhig: Halbtonblock, 13er-Bassperiode, Halbton-Echo; die Unruhe liegt im Rhythmus, nicht im Tempo.
- **Eckdaten:** 32 Takte 4/4, 96 BPM, Tonart D, Chromatisch (frei, nur Akkordtöne + autorisierte Töne); XYZ (0,15 / 0,85 / 0,85), mechanisch
- **Harmonie:** ab T1 DS-H62 Kraftvoller Halbtonblock
- **Schichten:**
  - LF aus Harmonie
  - KB: DS-B11 13er-Bassperiode, folgt Akkorden
  - GS: DS-Q12 Halbton-Echo-Zelle (T9-32), folgt Akkorden
  - ST an T9, T25
- **Strategien:** Periodenschichtung; DS-E02 Periodenschichtung
- **MIDI:** `DS-S14_Bedrohliche_Jagd_ohne_Hektik.mid` · Spuren LF, KB, ST, GS · 631 Noten · Funktionen {'A': 494, 'U': 135, 'ST': 2}

#### DS-S15 Orgelchoral, dunkel und ruhig

- **Zweck:** Dunkel, kraftvoll, ruhig: Requiem-Kette, Oktav-Orgelpunkt, tiefe Glocke alle acht Takte.
- **Eckdaten:** 48 Takte 4/4, 58 BPM, Tonart C, Äolisch (natürliches Moll); XYZ (0,10 / 0,85 / 0,10), neutral
- **Harmonie:** ab T1 DS-H41 Requiem-Kette
- **Schichten:**
  - LF aus Harmonie
  - LB: DS-B13 Oktav-Orgelpunkt
  - TU-Gedächtnis, Keim DS-TU04 Tiefe Glocke: T5 fit, T13 fit, T21 fit, T29 fit, T37 fit, T45 fit
- **Strategien:** Stasis; JC-T012 Langfristige Stasis
- **MIDI:** `DS-S15_Orgelchoral_dunkel_und_ruhig.mid` · Spuren LF, LB, TU · 90 Noten · Funktionen {'A': 74, 'T': 16}

#### DS-S16 Flüstern

- **Zweck:** Dunkel, leise, unruhig: Halbton-Bassrotation, Fragen ohne Antwort, ein Stich.
- **Eckdaten:** 48 Takte 4/4, 62 BPM, Tonart F, Chromatisch (frei, nur Akkordtöne + autorisierte Töne); XYZ (0,10 / 0,10 / 0,85), psychologisch
- **Harmonie:** ab T1 DS-H11 Halbton-Bassrotation
- **Schichten:**
  - LF aus Harmonie
  - LB aus Harmonie
  - TU-Gedächtnis, Keim DS-TU11 Frage zum Tritonus: T3 Original, T10 Original, T19 Original, T26 frag, T35 Original, T44 Original
  - ST an T31
- **Strategien:** Ereignisfeld; JC-T012 Langfristige Stasis
- **MIDI:** `DS-S16_Fluestern.mid` · Spuren LF, LB, TU, ST · 66 Noten · Funktionen {'A': 59, 'U': 6, 'ST': 1}

#### DS-S17 Aufbruch

- **Zweck:** Hell, kraftvoll, unruhig: weicher Kreis mit Moll-iv, Rollbass, helle Sechzehntel und verzögerte Achtel.
- **Eckdaten:** 32 Takte 4/4, 120 BPM, Tonart A, Ionisch (Dur); XYZ (0,85 / 0,80 / 0,75), mechanisch
- **Harmonie:** ab T1 DS-H53 Weicher Kreis mit Moll-iv
- **Schichten:**
  - LF aus Harmonie
  - KB: DS-B07 Nostalgie-Rollbass
  - AR: DS-Q16 Rollende Dur-Zelle, folgt nicht
  - GS: DS-Q14 Verzögerte Achtelzelle (T9-32), folgt Akkorden, Mutationen [(1, 7, 2)]
- **Strategien:** Stasis; JC-T012 Langfristige Stasis
- **MIDI:** `DS-S17_Aufbruch.mid` · Spuren LF, KB, AR, GS · 1008 Noten · Funktionen {'A': 720, 'T': 288}

#### DS-S18 Weite ohne Triumph

- **Zweck:** Hell, kraftvoll, ruhig: Dur mit entlehntem ♭VI, Dur-Wiege, helle Erinnerungslinie.
- **Eckdaten:** 32 Takte 4/4, 76 BPM, Tonart E, Ionisch (Dur); XYZ (0,85 / 0,80 / 0,15), neutral
- **Harmonie:** ab T1 DS-H57 Erinnerungs-Dur mit ♭VI
- **Schichten:**
  - LF aus Harmonie
  - LB aus Harmonie
  - AR: DS-Q09 Nostalgie-Wiege in Dur, folgt Akkorden
  - HM: DS-HM10 Erinnerungslinie hell an T17
- **Strategien:** Stasis; JC-T012 Langfristige Stasis
- **MIDI:** `DS-S18_Weite_ohne_Triumph.mid` · Spuren LF, LB, AR, HM · 430 Noten · Funktionen {'A': 413, 'T': 16, 'V': 1}

#### DS-S19 Fragment-Exposition über 64 Takte

- **Zweck:** Keim C erscheint zuerst mit zwei Tönen, dann mit drei, ab Takt 33 als Lead-Melodie; danach wieder nur der Keim.
- **Eckdaten:** 64 Takte 4/4, 80 BPM, Tonart H, Äolisch (natürliches Moll); XYZ (0,45 / 0,40 / 0,30), neutral
- **Harmonie:** ab T1 DS-H18 Mollkreis mit Moll-v
- **Schichten:**
  - LF aus Harmonie
  - LB aus Harmonie
  - AR: DS-Q21 Triolen-Kettenläufer (T9-64), folgt Akkorden
  - TU-Gedächtnis, Keim DS-TU18 Keim C: Quart-Ruf: T3 frag, T11 frag, T19 Original, T27 fit, T57 frag, T63 frag
  - HM: DS-HM17 Endgestalt von Keim C an T33, T45
- **Strategien:** Fragment-Exposition; DS-E01 Fragment-Exposition
- **MIDI:** `DS-S19_Fragment_Exposition_ueber_64_Takte.mid` · Spuren LF, LB, AR, TU, HM · 818 Noten · Funktionen {'A': 811, 'T': 5, 'V': 2}

#### DS-S20 Dialog Gegenstimme – Tupfer

- **Zweck:** GS ruft zwei Takte, TU antwortet im dritten, der vierte bleibt leer.
- **Eckdaten:** 32 Takte 4/4, 80 BPM, Tonart E, Phrygisch; XYZ (0,30 / 0,40 / 0,50), psychologisch
- **Harmonie:** ab T1 DS-H25 Liegeton Grundton
- **Schichten:**
  - LF aus Harmonie
  - LB aus Harmonie
  - GS: DS-HM12 Phrygische Linie an T1, T5, T9, T13, T17, T21, T25, T29
  - TU-Gedächtnis, Keim DS-TU24 Antwort Halbton: T3 Original, T7 Original, T11 Original, T15 Original, T19 Original, T23 Original, T27 Original, T31 Original
- **Strategien:** Stasis; JC-T012 Langfristige Stasis
- **MIDI:** `DS-S20_Dialog_Gegenstimme_Tupfer.mid` · Spuren LF, LB, TU, GS · 92 Noten · Funktionen {'A': 70, 'U': 12, 'V': 2, 'T': 8}

#### DS-S21 Rollentausch Sequencer → Tupfer

- **Zweck:** Die Antwortlücken-Sequenz wandert ausgedünnt in den Tupfer; der Rufbass wird zum Halteton.
- **Eckdaten:** 32 Takte 4/4, 92 BPM, Tonart A, Äolisch (natürliches Moll); XYZ (0,40 / 0,45 / 0,35), neutral
- **Harmonie:** ab T1 DS-H18 Mollkreis mit Moll-v
- **Schichten:**
  - LF aus Harmonie
  - AR: DS-Q22 Antwortlücken-Sequenz (T1-16)
  - TU: DS-Q22 Antwortlücken-Sequenz (T17-32), Oktave +1, Mutationen [(17, 1, None), (17, 2, None)]
  - KB: DS-B04 Rufbass (T1-16)
  - LB Halteton 1 (T17-32, Gefrieren)
- **Strategien:** Rollentausch; DS-E05 Rollentausch
- **MIDI:** `DS-S21_Rollentausch_Sequencer_Tupfer.mid` · Spuren LF, LB, KB, AR, TU · 221 Noten · Funktionen {'A': 178, 'F': 5, 'T': 38}

#### DS-S22 Gate-Atmung und Ein-Schritt-Mutation

- **Zweck:** 64 Takte dieselbe Zelle; Tondauern atmen, an drei Stellen ändert sich genau ein Schritt.
- **Eckdaten:** 64 Takte 4/4, 96 BPM, Tonart F♯, Äolisch (natürliches Moll); XYZ (0,50 / 0,50 / 0,40), mechanisch
- **Harmonie:** ab T1 DS-H05 Schattenpaar mit None
- **Schichten:**
  - LF aus Harmonie
  - KB: JC-B011 Tiefer Viertelpuls
  - AR: DS-Q20 Mutationszelle, Gate-Kurve, Mutationen [(17, 7, -3), (33, 3, 12), (49, 7, None)]
- **Strategien:** Gate-Atmung; DS-E08 Gate-Atmung, DS-E09 Ein-Schritt-Mutation
- **MIDI:** `DS-S22_Gate_Atmung_und_Ein_Schritt_Mutation.mid` · Spuren LF, KB, AR · 1320 Noten · Funktionen {'A': 1304, 'T': 16}

#### DS-S23 Seitwärtsentwicklung

- **Zweck:** Vier Harmoniefamilien nacheinander bei gleicher Dichte; Farbwechsel ohne Intensitätsänderung.
- **Eckdaten:** 64 Takte 4/4, 88 BPM, Tonart D, Äolisch (natürliches Moll); XYZ (0,55 / 0,35 / 0,25), neutral
- **Harmonie:** ab T1 DS-H01 Schattenpaar ♭VImaj7, ab T17 DS-H06 Dreifacher Schatten, ab T33 DS-H30 Choralwechsel über Drone, ab T49 DS-H05 Schattenpaar mit None
- **Schichten:**
  - LF aus Harmonie
  - LB: JC-B005 Unabhängiges Pedal
  - AR: DS-Q21 Triolen-Kettenläufer, folgt Akkorden
- **Strategien:** Seitwärtsentwicklung; DS-E11 Seitwärtsentwicklung
- **MIDI:** `DS-S23_Seitwaertsentwicklung.mid` · Spuren LF, LB, AR · 829 Noten · Funktionen {'A': 829}

#### DS-S24 Tritonus-Spiegel

- **Zweck:** Am und D♯-Dur: konsonant und ortlos; Glockenschläge und eine offene Frage.
- **Eckdaten:** 32 Takte 4/4, 66 BPM, Tonart G, Chromatisch (frei, nur Akkordtöne + autorisierte Töne); XYZ (0,60 / 0,30 / 0,75), psychologisch
- **Harmonie:** ab T1 DS-H48 Tritonus-Spiegel
- **Schichten:**
  - LF aus Harmonie
  - TU-Gedächtnis, Keim DS-TU01 Glockenschlag Quinte: T3 Original, T11 trans, T19 Original, T27 trans
- **Strategien:** Stasis; JC-T012 Langfristige Stasis
- **MIDI:** `DS-S24_Tritonus_Spiegel.mid` · Spuren LF, TU · 16 Noten · Funktionen {'A': 16}

#### DS-S25 Lichtwechsel über Drone

- **Zweck:** Hell, ruhig: A–D–E–D über Grund-Drone, Keim D als seltener Lichtpunkt.
- **Eckdaten:** 48 Takte 4/4, 64 BPM, Tonart F, Ionisch (Dur); XYZ (0,90 / 0,25 / 0,10), neutral
- **Harmonie:** ab T1 DS-H32 Lichtwechsel über Drone
- **Schichten:**
  - LF aus Harmonie
  - LB: JC-B001 Tiefer Grundton-Drone
  - TU-Gedächtnis, Keim DS-TU19 Keim D: Dur-Licht: T5 fit, T18 fit, T33 fit, T44 frag+fit
- **Strategien:** Ereignisfeld; DS-E06 Erinnerungsrückkehr
- **MIDI:** `DS-S25_Lichtwechsel_ueber_Drone.mid` · Spuren LF, LB, TU · 48 Noten · Funktionen {'A': 48}

#### DS-S26 Moll-Septkette mit Antwortbass

- **Zweck:** Septakkorde, ein Ruf im Bass, Tupfer-Antworten in den Lücken.
- **Eckdaten:** 32 Takte 4/4, 84 BPM, Tonart C, Äolisch (natürliches Moll); XYZ (0,35 / 0,30 / 0,30), neutral
- **Harmonie:** ab T1 DS-H22 Moll-Septkette
- **Schichten:**
  - LF aus Harmonie
  - KB: DS-B16 Antwortbass
  - TU-Gedächtnis, Keim DS-TU23 Antwort Quarte abwärts: T3 fit, T7 fit, T12 fit, T15 fit, T19 fit, T24 fit, T28 fit, T31 fit
- **Strategien:** Stasis; JC-T012 Langfristige Stasis
- **MIDI:** `DS-S26_Moll_Septkette_mit_Antwortbass.mid` · Spuren LF, KB, TU · 166 Noten · Funktionen {'A': 138, 'T': 28}

#### DS-S27 Drone-Wechsel phrygisch

- **Zweck:** Dunkel, leise: phrygische Klänge über dem Drone, Kriechbass, Glocke auf ♭2.
- **Eckdaten:** 32 Takte 4/4, 60 BPM, Tonart A, Phrygisch; XYZ (0,25 / 0,30 / 0,55), psychologisch
- **Harmonie:** ab T1 DS-H28 Drone-Wechsel phrygisch
- **Schichten:**
  - LF aus Harmonie
  - LB: JC-B005 Unabhängiges Pedal
  - KB: DS-B02 Kriechbass ♭2–7 (T9-24)
  - TU-Gedächtnis, Keim DS-TU03 Glockenschlag ♭2: T6 Original, T14 Original, T29 Original
- **Strategien:** Stasis; JC-T012 Langfristige Stasis
- **MIDI:** `DS-S27_Drone_Wechsel_phrygisch.mid` · Spuren LF, LB, KB, TU · 94 Noten · Funktionen {'A': 52, 'T': 16, 'U': 24, 'F': 2}

#### DS-S28 Liegeton E über chromatischen Klängen

- **Zweck:** Ein Ton bleibt, die Klänge darunter wandern chromatisch; Quint-Tresillo im Bass.
- **Eckdaten:** 40 Takte 4/4, 76 BPM, Tonart A, Chromatisch (frei, nur Akkordtöne + autorisierte Töne); XYZ (0,55 / 0,45 / 0,50), psychologisch
- **Harmonie:** ab T1 DS-H24 Liegeton E über chromatischen Klängen
- **Schichten:**
  - LF aus Harmonie
  - KB: DS-B05 Quint-Tresillo
  - TU-Gedächtnis, Keim DS-TU05 Doppelglocke: T4 fit, T12 fit, T20 fit, T28 fit, T36 fit
- **Strategien:** Umfärbung; JC-T008 Harmonische Umfärbung
- **MIDI:** `DS-S28_Liegeton_E_ueber_chromatischen_Klaengen.mid` · Spuren LF, KB, TU · 164 Noten · Funktionen {'A': 164}

#### DS-S29 Gruft

- **Zweck:** Dunkel, leise, ruhig: offener Moll und ♭VI über dem Drone, sehr seltene tiefe Glocke. Fast nichts geschieht.
- **Eckdaten:** 48 Takte 4/4, 54 BPM, Tonart E, Äolisch (natürliches Moll); XYZ (0,10 / 0,10 / 0,10), neutral
- **Harmonie:** ab T1 DS-H34 Gruftklang
- **Schichten:**
  - LF aus Harmonie
  - LB: JC-B001 Tiefer Grundton-Drone
  - TU-Gedächtnis, Keim DS-TU04 Tiefe Glocke: T9 Original, T30 fit
- **Strategien:** Stasis; JC-T012 Langfristige Stasis
- **MIDI:** `DS-S29_Gruft.mid` · Spuren LF, LB, TU · 12 Noten · Funktionen {'A': 12}

#### DS-S30 Glasnebel

- **Zweck:** Hell, leise, unruhig: Dur-Septakkorde im Großterzfall, Spieluhr-Splitter und offene Fragen, kein Bass.
- **Eckdaten:** 48 Takte 4/4, 62 BPM, Tonart A, Chromatisch (frei, nur Akkordtöne + autorisierte Töne); XYZ (0,85 / 0,10 / 0,80), psychologisch
- **Harmonie:** ab T1 DS-H47 Großterzfall in Dur-Septakkorden
- **Schichten:**
  - LF aus Harmonie
  - TU-Gedächtnis, Keim DS-TU10 Fallender Spieluhr-Splitter: T3 fit, T9 fit, T17 fit, T22 fit, T31 frag+fit, T38 fit, T45 fit
- **Strategien:** Ereignisfeld; DS-E06 Erinnerungsrückkehr
- **MIDI:** `DS-S30_Glasnebel.mid` · Spuren LF, TU · 68 Noten · Funktionen {'A': 68}

## 13. XYZ-Feld

Mehrere musikalisch verschiedene Lösungen für vergleichbare Positionen (Auswahl):

| Zone | Studien | passende DS-Harmonik (Auszug) |
|---|---|---|
| dunkel / leise / ruhig | DS-S26, DS-S29 | DS-H34 Gruftklang, DS-H35 Tiefe Quartklang-Ruhe |
| dunkel / leise / unruhig | DS-S16 | DS-H11 Halbton-Bassrotation, DS-H45 Doppel-Tarnhelm |
| dunkel / kraftvoll / ruhig | DS-S08, DS-S15 | DS-H42 Phrygischer Choral |
| dunkel / kraftvoll / unruhig | DS-S14 | DS-H31 Fremdklang über Drone, DS-H58 Halbtonkette über Pedal, DS-H60 Verminderte Schwelle, DS-H61 Moll über Tritonusbass, DS-H62 Kraftvoller Halbtonblock |
| hell / leise / ruhig | DS-S01, DS-S02, DS-S25 | DS-H04 Schattenpaar in Dur, DS-H10 Bassrotation unter Cmaj7-Oberbau, DS-H13 Dur-Oberbau mit wanderndem Bass, DS-H17 Aufsteigende Lichtkette, DS-H32 Lichtwechsel über Drone, DS-H33 Schwebeklänge über Drone |
| hell / leise / unruhig | DS-S30 | DS-H49 Lichtreibung maj7♯11, DS-H50 Helle Ortlosigkeit |
| hell / kraftvoll / ruhig | DS-S18 | DS-H39 Plagaler Dur-Choral mit Moll-iv |
| hell / kraftvoll / unruhig | DS-S17 | DS-H36 Drängende Lichtkette, DS-H37 Große Terz im Puls |
| Mitte | DS-S05, DS-S06, DS-S07, DS-S11, DS-S13, DS-S19, DS-S20, DS-S21, DS-S22, DS-S26, DS-S28 | Schattenpaar, Bassrotation, Ketten |

**Interne Unruhe-Arten:** mechanisch (Periodenschichtung, verzögerter Step, Gate-Atmung, Halbtonblock) und psychologisch (F/U-Töne, Tarnhelm, Fragen, unregelmäßige TU-Platzierung, Fremdklang über Drone). Die Wahl folgt dem Z-Charakter der Vorlage, nicht einem festen X-Verhältnis.

## 14. Prioritäten für die Umsetzung

1. **TU-Rolle mit Gedächtnis:** Keimverwaltung, Operationen (DS-TO), Lückenplatzierung, Registerabstand. Behebt die kaum hörbare TU und die fehlenden Einwürfe.
2. **Fester Oberbau mit Bassrotation (DH2)** und mehrgliedrige Ketten (DH3). Behebt eintönige Pendel, ohne Pendel zu verbieten.
3. **Warme und helle Zonen:** DH8, Schattenpaar, Spieluhr in Dur, Lichtwechsel über Drone.
4. **Sakral/Choral und unheimliche Konsonanz** (DH6, DH7) als neue Farben.
5. **Langzeit:** Gefrieren, Gate-Atmung, Ein-Schritt-Mutation, inkommensurable Perioden (berechnete Wiederkehr).
6. **Strenge Verträglichkeitsprüfung** (♭9) für alle Profile übernehmen.
7. **Optional:** abstrakte Klangkurven mit frei zuordenbaren Controllern.

## 15. Quellenlage und Grenzen

- Die Verfahren stützen sich auf die Dark-Synth-Tiefenrecherche und die Carpenter-Forschung. Belegt sind dort vor allem Arbeitsweisen und Klangprinzipien (Franke/Froese, Bernstein, Simonetti, Frizzi, Disasterpeace, Dixon/Stein); harmonisch belegt ist nur wenig (Cmaj7-Arpeggio über e-Moll, D-Moll-Drone bei Suspiria, Tarnhelm allgemein bei Lehman).
- Alle Ketten, Motive, Rhythmen und Studien sind eigene Konstruktionen (E). Kein Thema ist transkribiert; Konturen bekannter Themen (Stranger-Things-Arpeggio, Suspiria-Celesta, Elm-Street-Spieluhr, Herzschlagbass) wurden bewusst vermieden.
- Die Prüfungen sind formal (Tonklassen, Funktionen, Perioden, Identität, Bilanz). Gehört wurden die Studien nicht; die musikalische Abnahme erfolgt beim Hören.
- Die Bezugstonart A der Akkordnamen ist eine Dokumentationskonvention; in den Studien sind die Vorlagen in verschiedene Tonarten transponiert.
