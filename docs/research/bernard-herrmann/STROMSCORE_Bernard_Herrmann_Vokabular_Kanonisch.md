# STROMSCORE – Bernard Herrmann: Kanonisches musikalisches Vokabular

Stand: 27.11.2026 · **kanonische Endfassung** (ersetzt die Fassung vom selben Morgen vollständig; IDs erhalten, neue IDs fortlaufend) · Bezugstonart C · Zeitbasis 960 PPQ · Grundlage: `STROMSCORE_Bernard_Herrmann_Tiefenrecherche.md` · zugehörig: `HE_Studien_Ereignisse.csv`, `HE_Studien_MIDI.zip` (53 MIDI-Dateien, je Rolle eine Spur), `HE_Qualitaetspruefung.md`.

Bestand: **101** harmonische Vorlagen (davon 16 Polychorde mit Komponentenbeschreibung), **66** Rhythmus-, **45** Bass-, **57** Motiv- und **21** Phrasenvorlagen, **40** Modellstudien (davon 6 über 16 und 2 über 32 Takte) und **13** Transformationsstudien.

## Inhalt

- **0** Lesehinweise, Evidenz, Notation
- **A** Übertragungsregeln aus der Tiefenrecherche
- **B** Harmonisches Vokabular (HE-H)
- **C** Polychorde: Übersicht der Komponenten
- **D** Rhythmisches Vokabular (HE-R)
- **E** Bassvokabular (HE-B)
- **F** Motive (HE-M)
- **G** Phrasen (HE-P)
- **H** Modellstudien (HE-S)
- **I** Transformationsverfahren (HE-T)
- **J** XYZ-Abdeckung und Färbungsbereiche
- **K** Hinweise für den Generator
- **L** Technische Rollenanforderungen
- **M** Quellen

## 0 Lesehinweise, Evidenz, Notation

**Evidenz.** Die Klasse in jeder Kopfzeile betrifft das *Verfahren*: **N** in einer eingesehenen Quelle nachgewiesen · **I** begründete musikalische Interpretation · **H** plausible, nicht ausreichend belegte Hypothese · **E** eigene Konstruktion für STROMSCORE. Alle konkreten Akkordfolgen, Raster, Basslinien, Motive, Phrasen und Studien sind eigene Konstruktionen [E]: keine Transkriptionen, keine Nachbildungen bekannter Themen. Wo ein belegter Cue als Vorbild dient, ist nur das Verfahren übernommen; Tonhöhen, Transposition und Dauer sind neu. Quellenkürzel S1–S19 in Abschnitt L.

**IDs.** Präfix **HE-** (Herrmann), damit es nicht mit den BH-IDs der Barry/Herrmann-Konsolidierung vom 24.11.2026 kollidiert. Die BH-IDs bleiben gültig; Entsprechungen stehen in der Qualitätsprüfung.

**Notation.**

- Akkorde ASCII in C (`b` = ♭, `#` = ♯). `X|Y` = Polychord, X über Y; `{C Db E}` = ausdrücklich notierte Tonklassenmenge; `mM7` = Moll mit großer Septime; `7b5` auf F♯ oder C = französische Sexte; `it6` = italienische Sexte; `9#5` = Ganztonklang; `dimM7` = vermindert mit großer Septime.
- Tonvorräte: **Ganzton-0** = C D E F♯ G♯ B♭; **Ganzton-1** = D♭ E♭ F G A B; **Hex-C** = C E♭ E G A♭ B; „Chromatisch“ heißt: kein gemeinsamer Vorrat, Klangobjekte stehen für sich (bei Herrmann der Normalfall). Herrmanns Harmonik wird hier als Folge von **Klangobjekten** beschrieben, nicht als Skalensystem. Oktatonik wird nicht als System angesetzt (Tiefenrecherche §3).
- **Okt-A** = {C, D♭, E♭, E, F♯, G, A, B♭} (Halbton–Ganzton ab C) und **Okt-B** = {D♭, D, E, F, G, A♭, B♭, B} (Halbton–Ganzton ab D♭). Beide sind nur Etiketten für Klänge, die vollständig darin liegen (verminderte und halbverminderte Septakkorde, Dominantsept mit kleiner None: HE-H19, HE-H20, HE-H25); sie dienen als Tonfilter für Arpeggio und Tupfer. Eine oktatonische Herrmann-Grammatik wird ausdrücklich nicht angenommen.
- **„Chromatisch“ heißt nicht „jeder Ton erlaubt“.** Für Arpeggio, Tupfer und erzeugte Linien gelten bei chromatischen Vorlagen nur die Töne des gerade klingenden Klangobjekts und ein ausdrücklich genanntes Pedal oder Hochpedal. Andere Töne sind nur zulässig als Vorhalt bzw. Durchgang mit stufenweiser Auflösung oder als in der Vorlage genannte, bewusst unaufgelöste Reibung.
- **Tonfunktionen** bei Motiven, Phrasen und Bassfiguren: **A** Akkordton · **T** Ton des angegebenen Vorrats · **V** Vorhalt oder Durchgang mit Auflösungsziel (`V→Ziel`) · **F** bewusst akkordfremd innerhalb der Figur · **U** bewusst unaufgelöste Dissonanz am Ende. F und U sind Herrmann-Merkmale und dürfen von einer Harmoniekorrektur nicht entfernt werden.
- **Färbungsbereich** (Rhythmus, Bass, Motive, Phrasen): für welche X-Werte die Vorlage taugt. „Färbungsunabhängig“ heißt: die Vorlage wird nach Y und Z gewählt, die Färbung kommt aus Harmonik und Lage.
- **Technische Anforderungen:** Fähigkeiten, die eine Vorlage über eine einfache Rolle hinaus braucht (Abschnitt L). Sie sind nicht automatisch in STROMSCORE vorhanden.
- Raster: 4/4 = 16 Schritte pro Takt (Sechzehntel, 240 Ticks), 3/4 und 6/8 = 12, 5/4 = 20, **4/4T** = 12 Achteltriolen (320 Ticks). `X` Einsatz mit Akzent, `x` Einsatz, `-` halten, `.` Pause, `|` Taktstrich.
- Melodien: `Ton/Dauer` in Schritten (C4 = MIDI 60), `r` = Pause; jede Taktsumme ist maschinell geprüft.
- Bass-Tonregeln: `R` Grundton, `b` notierter Bass, `3`/`5` Terz/Quinte, `8`/`-8` Oktave, `+1` Halbton über dem Grundton, `n` Halbton unter dem nächsten Grundton, `d` Durchgang, `P(x)` fester Ton.
- Rollen: LF Lange Fläche · KF Kurze Fläche · LB Langer Bass · KB Kurzer Bass · AR Arpeggio · TU Tupfer · ST Stich · GS Gegenstimme · HM Hauptmelodie. **ST** ist ausschließlich ein fester, nie transponierter Trigger (in den MIDI-Dateien C2 = MIDI 36). **GS und HM** sind optional; jede Vorlage und jede Studie funktioniert ohne sie.
- Rollenangaben in Vorlagen sind Vorschläge, keine Pflichtbesetzung. Instrumentation ist nicht Teil der Grammatik; wo eine Quelle Instrumente nennt, steht das nur als Begründung des Verfahrens.
- XYZ: X dunkel → hell, Y zurückhaltend → kraftvoll, Z stabil → unruhig, je 0–1. Region D/m/H, R/m/I, S/m/U mit Grenzen 0,40 und 0,60; Ecken mit Grenze 0,50. Alle Anker sind Setzungen [E]. **Hell ist nicht fröhlich, niedrige Unruhe ist nicht Sicherheit, niedrige Intensität ist nicht geringe psychologische Spannung** – die Wirkungstexte jeder Vorlage sagen, welche Spannung gemeint ist.

## A Übertragungsregeln aus der Tiefenrecherche

Keine neue Stilzusammenfassung, nur die Regeln, nach denen das Vokabular gebaut ist:

- **Klangobjekt statt Funktion.** Akkorde werden gehalten, wiederholt oder in ein Nachbarobjekt mit gemeinsamen Tönen überführt, nicht kadenziert (HE-H01–H31). Funktionale Wendungen kommen nur als Attrappe vor (HE-H30, HE-H82). [N: S2, S4, S6]
- **Modulform.** Musik besteht aus Bewegungsmodulen (Ostinato, Arpeggio) und Interpunktionsmodulen (Schläge, Stiche); Module werden gekürzt, verlängert, gestrichen und umgestellt (HE-R14–R26, HE-S24, HE-T01, HE-T11). [N: S7, S4]
- **Vierton-Prototyp.** Dissonanz auf schwerer, Auflösung auf leichter Zeit, stufenweise; Varianten Nebennote, Umkehrung, Vorhalt (HE-M03–M07). [N: S7]
- **Verschmelzung vor Dichte.** Dasselbe Material wirkt latent, wenn es getrennt (versetzt, registerfern, verschieden lang) erklingt, und akut, wenn es verschmolzen (gleichzeitig, ineinander, gleich lang) erklingt. Steigerungshebel in dieser Reihenfolge: Verschmelzung, Register, Dissonanzschärfe, Dynamik, Dichte (HE-S01/S02, HE-S06/S07, HE-S22, HE-S27, HE-T08, HE-T10). [N: S1]
- **Pedal als Blick.** Ein Liegeton bleibt, während sich seine Bedeutung im Klang ändert (HE-H44, HE-H64, HE-H69, HE-S19, HE-S29). [N: S5, S9]
- **Bass in Tritonus- oder Halbtonbeziehung** zum Oberklang, unabhängig von der Harmonie; Bassverzicht ist ein eigener Zustand (HE-B01–B07, HE-B42). [N: S1, S4]
- **Stiche ereignisgebunden und selten**, nie periodisch (HE-R49, HE-R50; in den Studien höchstens ein Stich je Abschnitt).
- **Melodie optional.** Spannungsfelder brauchen keine Hauptmelodie; wenn eine Linie auftritt, dann als 2–4-Ton-Zelle oder Bar-Form. Lyrische Linien entstehen aus demselben Prototyp, nur länger und aufwärts sequenziert (HE-M30, HE-P13). [N: S7]
- **Gleichbleibende Spannung ist legitim.** Variation innerhalb des Moduls verhindert Monotonie, ohne Spannung abzubauen (HE-S25, HE-S26, HE-T03). Es gibt keine Zeitgrenze, nach der deeskaliert werden muss.

## B Harmonisches Vokabular (HE-H01–H101)

Jede Vorlage hat acht Takte. Die Tabelle gibt die Tonklassen jedes Klangs (Bass zuerst) maschinell aus dem Symbol an.

### B.1 Moll mit großer Septime

#### HE-H01 · Eingefrorener Moll-Dur-Septakkord

- **XYZ-Anker:** 0,20 / 0,25 / 0,40 (Region DRm, Ecke DRS) · **Taktart:** 4/4 · **Tonvorrat:** Moll harm. · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `CmM7` | 8 | T1 | C E♭ G B | C | Moll harm. |

- **Wirkung:** Ein Klang, der nichts will und nirgends hinführt; die große Septime B reibt dauerhaft am Grundton C. Die Unruhe liegt im Klang, nicht in der Bewegung.
- **Bassführung:** Grundton C2 liegend; kein Wechsel.
- **Begleitformen:** HE-R02, HE-R36, HE-R58
- **Variation:** Septime in die Oberstimme legen (B5) oder in die Mitte (B4); Wirkung wechselt von kalt zu dumpf, ohne dass sich der Akkord ändert.
- **Herrmann-Verfahren:** Moll mit großer Septime als selbständiges, unaufgelöstes Klangobjekt; bei Herrmann teilweise Signatur eines ganzen Films. Quellen: S6, S4, S2.
- **Stimmungen:** latente Bedrohung, Unbehagen

#### HE-H02 · Moll-Dur-Septakkord über der Quinte

- **XYZ-Anker:** 0,20 / 0,35 / 0,55 (Region DRm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Moll harm. · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `CmM7/G` | 8 | T1 | G C E♭ B | G | Moll harm. |

- **Wirkung:** Wie HE-H01, aber ohne Boden: die Quinte im Bass lässt den Klang wie auf einer Kante stehen.
- **Bassführung:** G1 liegend; wahlweise G1–C2 im Abstand von vier Takten getauscht.
- **Begleitformen:** HE-R14, HE-R03
- **Variation:** Takt 5–8 Bass C2 statt G1 (Boden kehrt zurück, Klang bleibt).
- **Herrmann-Verfahren:** Der Hitchcock-Klang erscheint in einem belegten Fall in der zweiten Umkehrung; hier als Dauerzustand. Quellen: S4.
- **Stimmungen:** Unbehagen, Paranoia

#### HE-H03 · Halbtonpendel zweier Moll-Dur-Septakkorde

- **XYZ-Anker:** 0,15 / 0,45 / 0,70 (Region DmU, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `CmM7` | 2 | T1 | C E♭ G B | C | Chromatisch |
| 2 | `DbmM7` | 2 | T3 | D♭ E A♭ C | D♭ | Chromatisch |
| 3 | `CmM7` | 2 | T5 | C E♭ G B | C | Chromatisch |
| 4 | `DbmM7` | 2 | T7 | D♭ E A♭ C | D♭ | Chromatisch |

- **Wirkung:** Dasselbe Objekt rückt einen Halbton und kehrt zurück. Nur C bleibt liegen und wird dabei umgedeutet: in C-Moll Grundton, in D♭-Moll große Septime. Alle anderen Töne verschieben sich; der Wechsel wirkt als Ruck um einen festen Punkt.
- **Bassführung:** Grundtöne C–D♭ parallel; alternativ Pedal C (dann liegt unter D♭mM7 dessen eigene große Septime im Bass).
- **Begleitformen:** HE-R01, HE-R21, HE-R27
- **Variation:** Pendel auf einen Takt je Seite beschleunigen, ohne Tempo zu ändern; oder D♭mM7 nur im vierten Takt.
- **Herrmann-Verfahren:** Halbtonpendel ganzer Klänge (belegt als Wechsel zweier Moll-Tonarten im Halbtonabstand); hier mit dem mM7-Objekt kombiniert. Quellen: S4, S3.
- **Stimmungen:** Paranoia, obsessive Wiederholung
- **Technische Anforderungen:** Pedal über Akkordwechsel

#### HE-H04 · Septime kommt und geht

- **XYZ-Anker:** 0,25 / 0,20 / 0,35 (Region DRS, Ecke DRS) · **Taktart:** 4/4 · **Tonvorrat:** Moll harm. · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 2 | T1 | C E♭ G | C | Moll harm. |
| 2 | `CmM7` | 2 | T3 | C E♭ G B | C | Moll harm. |
| 3 | `Cm` | 2 | T5 | C E♭ G | C | Moll harm. |
| 4 | `CmM7` | 2 | T7 | C E♭ G B | C | Moll harm. |

- **Wirkung:** Ein ruhiger Mollklang, in dem sich alle zwei Takte eine einzige Stimme um einen Halbton hebt; man hört die Störung eher, als dass man sie benennen kann.
- **Bassführung:** C2 liegend, keine Bewegung.
- **Begleitformen:** HE-R58, HE-R59
- **Variation:** Septime nur im Tupfer statt in der Fläche; oder dritter Durchgang mit B♭ statt B (Cm7: die Störung „verschwindet“ kurz).
- **Herrmann-Verfahren:** Spannung bei kaum wechselndem Akkord durch Bewegung einer Innenstimme gegen einen Liegeklang [I]. Quellen: S5.
- **Stimmungen:** subliminale Spannung, Melancholie

#### HE-H05 · Moll-Dur-Septakkord über Tritonusbass

- **XYZ-Anker:** 0,10 / 0,30 / 0,75 (Region DRU, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `CmM7/F#` | 8 | T1 | F♯ C E♭ G B | F♯ | Chromatisch |

- **Wirkung:** Leise und fast unbewegt, aber haltlos: der Bass steht im Tritonus zum Grundton.
- **Bassführung:** F♯1 liegend; Oberklang ohne C im Bass.
- **Begleitformen:** HE-R58, HE-R18
- **Variation:** F♯ im Bass erst ab Takt 5, vorher C (Boden bricht weg).
- **Herrmann-Verfahren:** Tritonus-Dissonanzbass unter einem Mollklang ist als Schlussklang belegt; hier mit dem mM7-Objekt verbunden. Quellen: S4, S1.
- **Stimmungen:** psychologische Spannung, Unbehagen

#### HE-H06 · Moll-Dur-Septakkord ↔ übermäßiger Dreiklang

- **XYZ-Anker:** 0,30 / 0,25 / 0,55 (Region DRm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Moll harm. · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `CmM7` | 2 | T1 | C E♭ G B | C | Moll harm. |
| 2 | `Ebaug` | 2 | T3 | E♭ G B | E♭ | Moll harm. |
| 3 | `CmM7` | 2 | T5 | C E♭ G B | C | Moll harm. |
| 4 | `Ebaug` | 2 | T7 | E♭ G B | E♭ | Moll harm. |

- **Wirkung:** Der Moll-Anteil verschwindet und kehrt zurück; der übermäßige Kern E♭–G–B bleibt stehen und schillert.
- **Bassführung:** C2 im mM7-Takt, Pause oder E♭2 im aug-Takt (bassloser Moment).
- **Begleitformen:** HE-R13, HE-R06
- **Variation:** Wechsel nur durch Weglassen des C (keine neue Note nötig).
- **Herrmann-Verfahren:** Im mM7 steckt ein übermäßiger Dreiklang; der Klang oszilliert zwischen Moll und Ganztonsymmetrie. Quellen: S6, S5.
- **Stimmungen:** mysteriös, surreal

#### HE-H07 · Liegender Hitchcock-Klang über fallendem Bass

- **XYZ-Anker:** 0,15 / 0,35 / 0,60 (Region DRm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `CmM7` | 2 | T1 | C E♭ G B | C | Chromatisch |
| 2 | `CmM7/B` | 2 | T3 | B C E♭ G | B | Chromatisch |
| 3 | `CmM7/Bb` | 2 | T5 | B♭ C E♭ G B | B♭ | Chromatisch |
| 4 | `CmM7/A` | 2 | T7 | A C E♭ G B | A | Chromatisch |

- **Wirkung:** Oben ändert sich nichts, unten sinkt der Boden um je einen Halbton; der Klang wird mit jedem Schritt fremder.
- **Bassführung:** C2–B1–B♭1–A1, je zwei Takte, ohne Durchgang.
- **Begleitformen:** HE-R02, HE-R16
- **Variation:** Bass weiter bis F♯1 führen (Tritonus) und dort liegen lassen.
- **Herrmann-Verfahren:** Fallender Bass unter festem Liegeton ist belegt (D wiederholt, Bass fällt); hier unter einem ganzen Klangobjekt. Quellen: S5.
- **Stimmungen:** langsam wachsende Bedrohung

#### HE-H08 · Moll-Dur-Septakkorde in kleinen Terzen

- **XYZ-Anker:** 0,20 / 0,55 / 0,70 (Region DmU, Ecke DIU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `CmM7` | 2 | T1 | C E♭ G B | C | Chromatisch |
| 2 | `EbmM7` | 2 | T3 | E♭ G♭ B♭ D | E♭ | Chromatisch |
| 3 | `F#mM7` | 2 | T5 | F♯ A C♯ F | F♯ | Chromatisch |
| 4 | `AmM7` | 2 | T7 | A C E G♯ | A | Chromatisch |

- **Wirkung:** Das Objekt wandert symmetrisch aufwärts; jede Station ist gleich gebaut, darum entsteht kein Ziel.
- **Bassführung:** Grundtöne C–E♭–F♯–A, Lage halten (keine Oktavsprünge).
- **Begleitformen:** HE-R27, HE-R39
- **Variation:** Rückwärts (abwärts) für Ausweglosigkeit; Wechsel halbtaktig für Eskalation.
- **Herrmann-Verfahren:** Gleich gebaute Klänge in symmetrischen Abständen (Terzbeziehungen als Herrmann-Mittel) [I]. Quellen: S11.
- **Stimmungen:** Eskalation, Paranoia

#### HE-H09 · Mollphrase endet auf dem Hitchcock-Klang

- **XYZ-Anker:** 0,25 / 0,30 / 0,45 (Region DRm, Ecke DRS) · **Taktart:** 4/4 · **Tonvorrat:** Moll harm. · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 2 | T1 | C E♭ G | C | Moll harm. |
| 2 | `Fm` | 2 | T3 | F A♭ C | F | Moll harm. |
| 3 | `Ab` | 2 | T5 | A♭ C E♭ | A♭ | Moll harm. |
| 4 | `CmM7` | 2 | T7 | C E♭ G B | C | Moll harm. |

- **Wirkung:** Eine fast gewöhnliche Mollfolge, die nicht schließt, sondern in einem eingefrorenen Klang stehen bleibt.
- **Bassführung:** C–F–A♭–C, Grundtöne.
- **Begleitformen:** HE-R16, HE-R50
- **Variation:** Schlussklang länger halten und Fläche ausdünnen; A♭ durch A♭maj7 ersetzen.
- **Herrmann-Verfahren:** Herrmanns tonale Sprache, „die man selten auflöst“ (Interviewfrage, unwidersprochen); der mM7 schließt einen belegten Cue. Quellen: S2, S4.
- **Stimmungen:** Tragik, Unbehagen

#### HE-H10 · Moll-Dur-Septnonakkord in hoher Lage

- **XYZ-Anker:** 0,55 / 0,20 / 0,45 (Region mRm, Ecke HRS) · **Taktart:** 4/4 · **Tonvorrat:** Moll harm. · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `CmM9` | 8 | T1 | C E♭ G B D | C | Moll harm. |

- **Wirkung:** Kalte, glasige Helligkeit; leise und schön, aber nicht freundlich.
- **Bassführung:** Kein Bass oder C3 sehr leise; Klang ab C5.
- **Begleitformen:** HE-R36, HE-R18
- **Variation:** None D als Tupfer statt in der Fläche; Septime weglassen (kühler, weniger fremd).
- **Herrmann-Verfahren:** Helligkeit durch Lage und Farbe, nicht durch Dur [I]; mM7-Objekt mit hinzugefügter None. Quellen: S1.
- **Stimmungen:** kalte Helligkeit, unheimliche Schönheit

#### HE-H11 · Tritonuspendel des Moll-Dur-Septakkords

- **XYZ-Anker:** 0,15 / 0,60 / 0,80 (Region DmU, Ecke DIU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `CmM7` | 4 | T1 | C E♭ G B | C | Chromatisch |
| 2 | `F#mM7` | 4 | T5 | F♯ A C♯ F | F♯ | Chromatisch |

- **Wirkung:** Zwei gleich gebaute Klänge ohne gemeinsamen Ton im größtmöglichen Abstand; der Wechsel wirkt wie ein Sturz.
- **Bassführung:** C2 → F♯1; oder Pedal C2 durchgehend (dann F♯mM7 über C).
- **Begleitformen:** HE-R15, HE-R33
- **Variation:** Wechsel alle zwei Takte; zweiter Klang nur in Kurzer Fläche (Oberklang bleibt lang).
- **Herrmann-Verfahren:** Tritonusbeziehung als Kontrastmaximum (Leydon: Herrmann kombiniert Klänge im Halbton- oder Tritonusabstand „for maximum contrast“). Quellen: S10, S1.
- **Stimmungen:** akuter Horror, Eskalation

#### HE-H12 · Moll-Dur-Septakkord mit kleiner Sexte

- **XYZ-Anker:** 0,10 / 0,35 / 0,60 (Region DRm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Moll harm. · **Evidenz:** Verfahren [E], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `CmM7b6` | 8 | T1 | C E♭ G B A♭ | C | Moll harm. |

- **Wirkung:** Dichter, dunkler Klang mit zwei Halbtonreibungen (G–A♭, B–C); bleibt leise trotzdem gespannt.
- **Bassführung:** C2 liegend.
- **Begleitformen:** HE-R58, HE-R35
- **Variation:** A♭ nur als Tupfer im Takt 4 und 8.
- **Herrmann-Verfahren:** Erweiterung des mM7-Objekts um einen weiteren Halbtonnachbarn [E]. Keine direkte Quelle.
- **Stimmungen:** Unbehagen, dunkle Monumentalität

### B.2 Übermäßige Klänge

#### HE-H13 · Übermäßiger Dreiklang als Achse

- **XYZ-Anker:** 0,45 / 0,20 / 0,55 (Region mRm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Ganzton-0 · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Caug` | 8 | T1 | C E G♯ | C | Ganzton-0 |

- **Wirkung:** Schwebend, ohne Schwerpunkt; jeder Ton könnte Grundton sein.
- **Bassführung:** Kein Bass oder E2 (gleichwertig zu C).
- **Begleitformen:** HE-R13, HE-R06
- **Variation:** Bass wechselt zwischen C, E, G♯ alle zwei Takte – derselbe Klang, drei Deutungen.
- **Herrmann-Verfahren:** Übermäßiger Dreiklang als symmetrische Achse einer zweitaktigen Arpeggiofigur „mit mehreren Symmetrieachsen“. Quellen: S5, S9.
- **Stimmungen:** Schwindel, mysteriös

#### HE-H14 · Kippende Achse

- **XYZ-Anker:** 0,35 / 0,25 / 0,50 (Region DRm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Caug` | 2 | T1 | C E G♯ | C | Chromatisch |
| 2 | `Am/C` | 2 | T3 | C A E | C | Chromatisch |
| 3 | `Caug` | 2 | T5 | C E G♯ | C | Chromatisch |
| 4 | `Ab/C` | 2 | T7 | C A♭ E♭ | C | Chromatisch |

- **Wirkung:** Ein Ton der symmetrischen Achse rutscht einen Halbton – einmal nach oben, einmal nach unten – und die Symmetrie kippt in einen gewöhnlichen Dreiklang.
- **Bassführung:** C2 liegend (gemeinsamer Ton aller Klänge).
- **Begleitformen:** HE-R13, HE-R18
- **Variation:** Kippen nur in einer Rolle (Tupfer), Fläche bleibt übermäßig.
- **Herrmann-Verfahren:** Wirkung an der Grenze zwischen Symmetrie und Diatonik: ein chromatisch rutschender Ton „kippt“ die übermäßige Figur. Quellen: S5.
- **Stimmungen:** surreal, mysteriös

#### HE-H15 · Übermäßige Dreiklänge chromatisch abwärts

- **XYZ-Anker:** 0,35 / 0,45 / 0,70 (Region DmU, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Ganzton-0 → Ganzton-1 · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Caug` | 2 | T1 | C E G♯ | C | Ganzton-0 |
| 2 | `Baug` | 2 | T3 | B D♯ G | B | Ganzton-1 |
| 3 | `Bbaug` | 2 | T5 | B♭ D F♯ | B♭ | Ganzton-0 |
| 4 | `Aaug` | 2 | T7 | A C♯ F | A | Ganzton-1 |

- **Wirkung:** Gleitender, schwindelnder Abstieg; nach vier Schritten ist man wieder beim Ausgangsklang (es gibt nur vier übermäßige Dreiklänge).
- **Bassführung:** Kein Bass, oder Bass folgt parallel (C–B–B♭–A).
- **Begleitformen:** HE-R11, HE-R39
- **Variation:** Wechsel halbtaktig; zweiter Durchgang aufwärts.
- **Herrmann-Verfahren:** Chromatische Verschiebung ganzer Strukturen [N] mit symmetrischem Objekt [I]. Quellen: S4.
- **Stimmungen:** Schwindel, Eskalation

#### HE-H16 · Übermäßiger Dreiklang mit großer Septime

- **XYZ-Anker:** 0,55 / 0,25 / 0,55 (Region mRm, Ecke HRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `CaugM7` | 8 | T1 | C E G♯ B | C | Chromatisch |

- **Wirkung:** Heller, gläserner Klang mit einer kalten Kante (B gegen C).
- **Bassführung:** C2 oder kein Bass.
- **Begleitformen:** HE-R36, HE-R13
- **Variation:** B als Hochpedal (B6) statt in der Fläche.
- **Herrmann-Verfahren:** Verwandt mit dem Vertigo-Rahmen (übermäßiger Dreiklang in einem mM7-Klang) [I]. Quellen: S6.
- **Stimmungen:** kalte Helligkeit, surreal

#### HE-H17 · Übermäßig ↔ Moll mit zwei gemeinsamen Tönen

- **XYZ-Anker:** 0,30 / 0,30 / 0,45 (Region DRm, Ecke DRS) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Caug` | 2 | T1 | C E G♯ | C | Chromatisch |
| 2 | `Fm/C` | 2 | T3 | C F A♭ | C | Chromatisch |
| 3 | `Caug` | 2 | T5 | C E G♯ | C | Chromatisch |
| 4 | `Fm/C` | 2 | T7 | C F A♭ | C | Chromatisch |

- **Wirkung:** Weiches Pendeln: nur E bewegt sich nach F; der Klang atmet zwischen Schweben und Klage.
- **Bassführung:** C2 liegend.
- **Begleitformen:** HE-R54, HE-R37
- **Variation:** F nur halbtaktig (Vorhalt-Wirkung).
- **Herrmann-Verfahren:** Übergang über gemeinsame Töne (Herrmanns Klangwechsel teilen gemeinsame Töne mit Vorgänger und Nachfolger). Quellen: S6.
- **Stimmungen:** Melancholie, mysteriös

#### HE-H18 · Übermäßiger Dreiklang über Halbtonpedal

- **XYZ-Anker:** 0,20 / 0,35 / 0,70 (Region DRU, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Caug/Db` | 8 | T1 | D♭ C E G♯ | D♭ | Chromatisch |

- **Wirkung:** Die Schwebe bekommt einen falschen Boden: D♭ steht unter C, die Symmetrie klingt bedrohlich.
- **Bassführung:** D♭1 liegend.
- **Begleitformen:** HE-R58, HE-R18
- **Variation:** D♭ erst ab Takt 5.
- **Herrmann-Verfahren:** Systemfremder Ton als Halbtonnachbar des Pedals [I]. Quellen: S5.
- **Stimmungen:** Unbehagen, latente Bedrohung

### B.3 Halbvermindert und vermindert

#### HE-H19 · Halbverminderter Liegeklang

- **XYZ-Anker:** 0,25 / 0,20 / 0,45 (Region DRm, Ecke DRS) · **Taktart:** 4/4 · **Tonvorrat:** Okt-A · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm7b5` | 8 | T1 | C E♭ G♭ B♭ | C | Okt-A |

- **Wirkung:** Gedämpft, fragend, ohne Gewicht; der Klang fragt, ohne eine Antwort zu erwarten.
- **Bassführung:** C2 liegend.
- **Begleitformen:** HE-R02, HE-R59
- **Variation:** Lage wechseln: tief = dumpf, hoch = gläsern.
- **Herrmann-Verfahren:** Halbverminderte Akkorde als Herrmann-Klangobjekte (belegt im „City“-Cue). Quellen: S4.
- **Stimmungen:** Unbehagen, mysteriös

#### HE-H20 · Vermindert färbt sich halbvermindert

- **XYZ-Anker:** 0,25 / 0,35 / 0,55 (Region DRm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Okt-A · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cdim7` | 2 | T1 | C E♭ G♭ A | C | Okt-A |
| 2 | `Cm7b5` | 2 | T3 | C E♭ G♭ B♭ | C | Okt-A |
| 3 | `Cdim7` | 2 | T5 | C E♭ G♭ A | C | Okt-A |
| 4 | `Cm7b5` | 2 | T7 | C E♭ G♭ B♭ | C | Okt-A |

- **Wirkung:** Eine Stimme hebt sich einen Halbton (A→B♭); der Klang wird weicher und zugleich unbestimmter.
- **Bassführung:** C2 liegend.
- **Begleitformen:** HE-R02, HE-R20
- **Variation:** Umfärbung in jedem Takt statt alle zwei Takte.
- **Herrmann-Verfahren:** Ein verminderter Akkord, dessen Umkehrungen durch einen Halbtonschritt halbvermindert werden (Psycho, „The City“, T. 1–3). Quellen: S4.
- **Stimmungen:** Unbehagen, Paranoia

#### HE-H21 · Zwei verminderte Septakkorde im Halbtonabstand

- **XYZ-Anker:** 0,20 / 0,55 / 0,75 (Region DmU, Ecke DIU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cdim7` | 2 | T1 | C E♭ G♭ A | C | Chromatisch |
| 2 | `C#dim7` | 2 | T3 | C♯ E G A♯ | C♯ | Chromatisch |
| 3 | `Cdim7` | 2 | T5 | C E♭ G♭ A | C | Chromatisch |
| 4 | `C#dim7` | 2 | T7 | C♯ E G A♯ | C♯ | Chromatisch |

- **Wirkung:** Zwei symmetrische Klänge, die zusammen acht Töne abdecken; der Wechsel wirkt wie Einstürzen.
- **Bassführung:** C2–C♯2 parallel oder kein Bass.
- **Begleitformen:** HE-R51, HE-R52
- **Variation:** Als Kaskade (Töne nacheinander von oben nach unten) statt als Block.
- **Herrmann-Verfahren:** Kaskade, die mit zwei verminderten Septakkorden im Halbtonabstand endet (Husarik über „The City“ und „The Stairs“). Quellen: S3.
- **Stimmungen:** akuter Horror, Eskalation

#### HE-H22 · Halbverminderte Akkorde parallel abwärts

- **XYZ-Anker:** 0,20 / 0,45 / 0,65 (Region DmU, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm7b5` | 2 | T1 | C E♭ G♭ B♭ | C | Chromatisch |
| 2 | `Bm7b5` | 2 | T3 | B D F A | B | Chromatisch |
| 3 | `Bbm7b5` | 2 | T5 | B♭ D♭ E A♭ | B♭ | Chromatisch |
| 4 | `Am7b5` | 2 | T7 | A C E♭ G | A | Chromatisch |

- **Wirkung:** Gleich gebaute Klänge sinken in Halbtönen; kein Ziel, nur Abwärts.
- **Bassführung:** Parallel C–B–B♭–A.
- **Begleitformen:** HE-R02, HE-R25
- **Variation:** Dreitaktige Gruppen statt zweitaktiger (verschiebt den Wechsel gegen die Periode).
- **Herrmann-Verfahren:** Absteigende Parallelklänge (belegt mit Maj7 und m7 in „The Toys“); hier mit halbverminderten. Quellen: S4.
- **Stimmungen:** langsam wachsende Bedrohung

#### HE-H23 · Verminderte Septakkorde über festem Pedal

- **XYZ-Anker:** 0,20 / 0,40 / 0,70 (Region DmU, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cdim7` | 2 | T1 | C E♭ G♭ A | C | Chromatisch |
| 2 | `C#dim7/C` | 2 | T3 | C C♯ E G A♯ | C | Chromatisch |
| 3 | `Ddim7/C` | 2 | T5 | C D F A♭ B | C | Chromatisch |
| 4 | `C#dim7/C` | 2 | T7 | C C♯ E G A♯ | C | Chromatisch |

- **Wirkung:** Das Pedal bleibt, die drei möglichen verminderten Septakkorde wechseln darüber; C ist erst Grundton, dann Halbtonreibung, dann Septime.
- **Bassführung:** C2 liegend.
- **Begleitformen:** HE-R03, HE-R33
- **Variation:** D-Klang auslassen (nur Halbtonpendel über Pedal).
- **Herrmann-Verfahren:** Liegeton, der sich zu jedem neuen Klang anders verhält [I]. Quellen: S5.
- **Stimmungen:** Paranoia, Eskalation
- **Technische Anforderungen:** Pedal über Akkordwechsel

#### HE-H24 · Halbvermindert ↔ Moll-Dur-Septakkord

- **XYZ-Anker:** 0,25 / 0,25 / 0,50 (Region DRm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm7b5` | 2 | T1 | C E♭ G♭ B♭ | C | Chromatisch |
| 2 | `EbmM7` | 2 | T3 | E♭ G♭ B♭ D | E♭ | Chromatisch |
| 3 | `Cm7b5` | 2 | T5 | C E♭ G♭ B♭ | C | Chromatisch |
| 4 | `EbmM7` | 2 | T7 | E♭ G♭ B♭ D | E♭ | Chromatisch |

- **Wirkung:** Drei gemeinsame Töne (E♭, G♭, B♭); nur C wird zu D. Der Wechsel ist fast unhörbar und trotzdem ein Farbschlag.
- **Bassführung:** C2 → E♭2 oder durchgehend E♭2.
- **Begleitformen:** HE-R17, HE-R36
- **Variation:** Bass bleibt E♭; dann ist nur ein einziger Ton verschieden.
- **Herrmann-Verfahren:** Pendel zweier Klangobjekte mit gemeinsamen Tönen (Empfehlung des Berichts) [I]. Quellen: S5, S6.
- **Stimmungen:** subliminale Spannung, mysteriös

### B.4 Dominantklänge und übermäßige Sexten

#### HE-H25 · Dominantsept mit kleiner None, nicht aufgelöst

- **XYZ-Anker:** 0,25 / 0,40 / 0,60 (Region Dmm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Okt-B · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `G7b9` | 8 | T1 | G B D F A♭ | G | Okt-B |

- **Wirkung:** Erwartung ohne Erfüllung; der Klang zieht nach C, kommt dort aber nie an.
- **Bassführung:** G1 liegend.
- **Begleitformen:** HE-R15, HE-R50
- **Variation:** None nur im Tupfer; Klang zwei Takte lang ganz ausgespart (Leere als Erwartung).
- **Herrmann-Verfahren:** Dominantseptakkord mit hinzugefügter kleiner None, am Cue-Ende länger ausgehalten (Psycho, Prelude T. 21; „Discovery“). Quellen: S4.
- **Stimmungen:** latente Bedrohung, Thriller

#### HE-H26 · Dominantsept ↔ französische Sexte im Tritonus

- **XYZ-Anker:** 0,30 / 0,20 / 0,55 (Region DRm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Mixolydisch → Ganzton-0 · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C7` | 2 | T1 | C E G B♭ | C | Mixolydisch |
| 2 | `F#7b5` | 2 | T3 | F♯ A♯ C E | F♯ | Ganzton-0 |
| 3 | `C7` | 2 | T5 | C E G B♭ | C | Mixolydisch |
| 4 | `F#7b5` | 2 | T7 | F♯ A♯ C E | F♯ | Ganzton-0 |

- **Wirkung:** Drei gemeinsame Töne (C, E, B♭/A♯); der Wechsel ist ein Schatten, kein Schritt.
- **Bassführung:** C2 ↔ F♯1 oder Pedal E (gemeinsamer Ton).
- **Begleitformen:** HE-R03, HE-R37
- **Variation:** Bass bleibt C; nur die Oberstimmen G→F♯ ändern sich.
- **Herrmann-Verfahren:** Dominantsept alterniert mit französischer Sexte im Tritonusabstand (drei gemeinsame Töne), Vertigo „Madeleine’s Car“. Quellen: S5, S12.
- **Stimmungen:** Obsession, mysteriös

#### HE-H27 · Klangkreis um ein Binnenpedal

- **XYZ-Anker:** 0,30 / 0,25 / 0,60 (Region DRm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Mixolydisch → Ganzton-0 · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C7` | 2 | T1 | C E G B♭ | C | Mixolydisch |
| 2 | `F#7b5` | 2 | T3 | F♯ A♯ C E | F♯ | Ganzton-0 |
| 3 | `Eaug` | 2 | T5 | E G♯ C | E | Ganzton-0 |
| 4 | `C7` | 2 | T7 | C E G B♭ | C | Mixolydisch |

- **Wirkung:** Alle Klänge teilen den Ton E; er wird zum Blick, um den die Harmonie kreist.
- **Bassführung:** E2 als Binnenpedal (nicht im tiefsten Register); darunter optional C1 leise.
- **Begleitformen:** HE-R03, HE-R53
- **Variation:** Pedal-E als Tupfer repetieren (HE-R36).
- **Herrmann-Verfahren:** Dominantsept, französische Sexte und übermäßige Dreiklänge kreisen um ein Binnenpedal (Vertigo, Smith); eigene Klangfolge. Quellen: S5, S12.
- **Stimmungen:** Obsession, Bann
- **Technische Anforderungen:** Pedal über Akkordwechsel

#### HE-H28 · Dominantsept mit kleiner None in Halbtonrückung

- **XYZ-Anker:** 0,25 / 0,55 / 0,75 (Region DmU, Ecke DIU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `G7b9` | 2 | T1 | G B D F A♭ | G | Chromatisch |
| 2 | `Ab7b9` | 2 | T3 | A♭ C E♭ G♭ A | A♭ | Chromatisch |
| 3 | `G7b9` | 2 | T5 | G B D F A♭ | G | Chromatisch |
| 4 | `Ab7b9` | 2 | T7 | A♭ C E♭ G♭ A | A♭ | Chromatisch |

- **Wirkung:** Zwei unaufgelöste Spannungsklänge im Halbtonpendel; Thriller-Drängen ohne Ziel.
- **Bassführung:** G1–A♭1.
- **Begleitformen:** HE-R15, HE-R33
- **Variation:** Rückung nur in der Kurzen Fläche; Lange Fläche hält G7♭9.
- **Herrmann-Verfahren:** Halbtonpendel [N] mit Dom7♭9-Objekt [I]. Quellen: S4.
- **Stimmungen:** Thriller, Eskalation

#### HE-H29 · Französische Sexte als kalter Liegeklang

- **XYZ-Anker:** 0,45 / 0,20 / 0,50 (Region mRm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Ganzton-0 · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C7b5` | 8 | T1 | C E G♭ B♭ | C | Ganzton-0 |

- **Wirkung:** Ganztonnaher, schwebender Klang ohne Richtung; Geheimnis und Unentschiedenheit.
- **Bassführung:** C2 oder F♯1 (beide Tritonuspole gleichwertig).
- **Begleitformen:** HE-R36, HE-R13
- **Variation:** Bass zwischen C und F♯ alle vier Takte tauschen.
- **Herrmann-Verfahren:** Ganztonklänge bewirken nach Cooper „suspension and irresolution“ und damit eine Aura des Geheimnisvollen. Quellen: S9, S5.
- **Stimmungen:** mysteriös, kalte Helligkeit

#### HE-H30 · Übermäßige Sexte ohne Dominante

- **XYZ-Anker:** 0,25 / 0,35 / 0,45 (Region DRm, Ecke DRS) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Ab7` | 2 | T1 | A♭ C E♭ G♭ | A♭ | Chromatisch |
| 2 | `Cm/G` | 2 | T3 | G C E♭ | G | Chromatisch |
| 3 | `Ab7` | 2 | T5 | A♭ C E♭ G♭ | A♭ | Chromatisch |
| 4 | `Cm/G` | 2 | T7 | G C E♭ | G | Chromatisch |

- **Wirkung:** Die übermäßige Sexte (A♭–F♯) zielt auf den Quartsextakkord – und dort bleibt es stehen, die Dominante folgt nie.
- **Bassführung:** A♭1–G1 Halbton abwärts, zurück.
- **Begleitformen:** HE-R46, HE-R54
- **Variation:** A♭7 als Deutsche Sexte mit E♭ in der Oberstimme; Wiederholung ohne Rückkehr (nur Takte 1–4).
- **Herrmann-Verfahren:** Tonal resonant, funktional entkernt: Funktionswendungen werden angedeutet, nicht vollzogen [I]. Quellen: S2.
- **Stimmungen:** Tragik, Erwartung

#### HE-H31 · Italienische Sexte als nackter Dreiklang

- **XYZ-Anker:** 0,25 / 0,15 / 0,50 (Region DRm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [E], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Abit6` | 8 | T1 | A♭ C F♯ | A♭ | Chromatisch |

- **Wirkung:** Drei Töne, eine Spannung; sehr leise in tiefer Lage wie ein unausgesprochener Vorwurf.
- **Bassführung:** A♭1 liegend.
- **Begleitformen:** HE-R58, HE-R35
- **Variation:** F♯ als Hochpedal (F♯5).
- **Herrmann-Verfahren:** Übermäßige-Sexte-Klang als Objekt ohne Auflösung [E]. Keine direkte Quelle.
- **Stimmungen:** subliminale Spannung, latente Bedrohung

### B.5 Chromatische Strukturverschiebung

#### HE-H32 · Große Septakkorde gleiten abwärts

- **XYZ-Anker:** 0,55 / 0,35 / 0,55 (Region mRm, Ecke HRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [H], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cmaj7` | 2 | T1 | C E G B | C | Chromatisch |
| 2 | `Bmaj7` | 2 | T3 | B D♯ F♯ A♯ | B | Chromatisch |
| 3 | `Bbmaj7` | 2 | T5 | B♭ D F A | B♭ | Chromatisch |
| 4 | `Amaj7` | 2 | T7 | A C♯ E G♯ | A | Chromatisch |

- **Wirkung:** Weicher, heller Klang, der wie in einen Abgrund rutscht; schön und haltlos zugleich.
- **Bassführung:** Parallel C–B–B♭–A.
- **Begleitformen:** HE-R02, HE-R40
- **Variation:** Halbtaktig; oder nur zwei Schritte und zurück.
- **Herrmann-Verfahren:** Chromatisch gleitende Maj7-Akkorde (Journey, „The Bridge/Vines“) nur aus einer nicht verifizierten Notizquelle; als Parallelverfahren mit „The Toys“ abgesichert. Quellen: S19, S4.
- **Stimmungen:** unheimliche Schönheit, surreal

#### HE-H33 · Moll-Septakkorde parallel abwärts

- **XYZ-Anker:** 0,20 / 0,35 / 0,55 (Region DRm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm7` | 2 | T1 | C E♭ G B♭ | C | Chromatisch |
| 2 | `Bm7` | 2 | T3 | B D F♯ A | B | Chromatisch |
| 3 | `Bbm7` | 2 | T5 | B♭ D♭ F A♭ | B♭ | Chromatisch |
| 4 | `Am7` | 2 | T7 | A C E G | A | Chromatisch |

- **Wirkung:** Dumpfes, gleichförmiges Sinken; Puppenhaus-Kälte.
- **Bassführung:** Doppelpedal möglich (HE-B04) statt Parallelbass.
- **Begleitformen:** HE-R04, HE-R25
- **Variation:** Über Doppelpedal statt Parallelbass – die Parallelen reiben am Boden.
- **Herrmann-Verfahren:** Absteigende Parallel-Septakkorde (Maj7 und m7) in den Violinen, Psycho „The Toys“. Quellen: S4.
- **Stimmungen:** Unbehagen, Tragik

#### HE-H34 · Reibungsvierklang in schneller Parallelbewegung

- **XYZ-Anker:** 0,15 / 0,70 / 0,85 (Region DIU, Ecke DIU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `{C D Eb B}` | 1 | T1 | C D E♭ B | C | Chromatisch |
| 2 | `{Db Eb E C}` | 1 | T2 | D♭ E♭ E C | D♭ | Chromatisch |
| 3 | `{D E F Db}` | 1 | T3 | D E F D♭ | D | Chromatisch |
| 4 | `{Db Eb E C}` | 1 | T4 | D♭ E♭ E C | D♭ | Chromatisch |
| 5 | `{C D Eb B}` | 1 | T5 | C D E♭ B | C | Chromatisch |
| 6 | `{B Db D Bb}` | 1 | T6 | B D♭ D B♭ | B | Chromatisch |
| 7 | `{Bb C Db A}` | 1 | T7 | B♭ C D♭ A | B♭ | Chromatisch |
| 8 | `{B Db D Bb}` | 1 | T8 | B D♭ D B♭ | B | Chromatisch |

- **Wirkung:** Ein enger Vierklang mit Sekundreibungen rast als Block auf und ab; Panik ohne Richtung.
- **Bassführung:** Kein eigener Bass oder tiefstes Klangglied verdoppelt.
- **Begleitformen:** HE-R12, HE-R45
- **Variation:** Innerhalb eines Takts mehrfach wechseln (Achtel).
- **Herrmann-Verfahren:** Schnelle Parallelbewegung eines Vierklangs C/D/E♭/B („Discovery“, T. 26–35); Bewegungsplan eigen. Quellen: S4.
- **Stimmungen:** akuter Horror, Eskalation

#### HE-H35 · Parallele Molldreiklänge chromatisch steigend

- **XYZ-Anker:** 0,20 / 0,65 / 0,75 (Region DIU, Ecke DIU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 1 | T1 | C E♭ G | C | Chromatisch |
| 2 | `C#m` | 1 | T2 | C♯ E G♯ | C♯ | Chromatisch |
| 3 | `Dm` | 1 | T3 | D F A | D | Chromatisch |
| 4 | `Ebm` | 1 | T4 | E♭ G♭ B♭ | E♭ | Chromatisch |
| 5 | `Em` | 1 | T5 | E G B | E | Chromatisch |
| 6 | `Fm` | 1 | T6 | F A♭ C | F | Chromatisch |
| 7 | `F#m` | 1 | T7 | F♯ A C♯ | F♯ | Chromatisch |
| 8 | `Gm` | 1 | T8 | G B♭ D | G | Chromatisch |

- **Wirkung:** Unaufhaltsames Steigen; jeder Takt ist einen Halbton höher und gleich gebaut.
- **Bassführung:** Parallel C–G aufwärts; alternativ Pedal C (wachsende Reibung).
- **Begleitformen:** HE-R43, HE-R39
- **Variation:** Über Pedal C2: Reibung wächst Takt für Takt, ohne dass Noten hinzukommen.
- **Herrmann-Verfahren:** Kanonische Parallel-Molldreiklänge, chromatisch steigend (Moreira über The Naked and the Dead). Quellen: S1.
- **Stimmungen:** Eskalation, Thriller
- **Technische Anforderungen:** Kanon/koordinierte Parallelstimmen

#### HE-H36 · Halbtonpendel ganzer Molltonarten

- **XYZ-Anker:** 0,20 / 0,45 / 0,60 (Region Dmm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 4 | T1 | C E♭ G | C | Chromatisch |
| 2 | `C#m` | 4 | T5 | C♯ E G♯ | C♯ | Chromatisch |

- **Wirkung:** Großflächiger, unaufgelöster Wechsel; die neue Tonart ist nur ein Halbton entfernt und fühlt sich doch fremd an.
- **Bassführung:** C2 → C♯2.
- **Begleitformen:** HE-R01, HE-R22
- **Variation:** Zweite Hälfte nur zwei Takte (Bar-Form 4+2).
- **Herrmann-Verfahren:** Wechsel E♭-Moll (T. 37–40) → E-Moll (T. 41–44), Psycho-Prelude. Quellen: S4, S3.
- **Stimmungen:** Thriller, Paranoia

#### HE-H37 · Moll in Ganztönen abwärts

- **XYZ-Anker:** 0,15 / 0,40 / 0,55 (Region Dmm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 2 | T1 | C E♭ G | C | Chromatisch |
| 2 | `Bbm` | 2 | T3 | B♭ D♭ F | B♭ | Chromatisch |
| 3 | `Abm` | 2 | T5 | A♭ B E♭ | A♭ | Chromatisch |
| 4 | `F#m` | 2 | T7 | F♯ A C♯ | F♯ | Chromatisch |

- **Wirkung:** Langsames, schweres Absinken; nach drei Schritten ist der Tritonus erreicht.
- **Bassführung:** C–B♭–A♭–F♯ tief, je zwei Takte.
- **Begleitformen:** HE-R08, HE-R09
- **Variation:** Ab Takt 7 Pedal F♯ halten und Oberklang zurück nach Cm führen (Cm über F♯).
- **Herrmann-Verfahren:** Parallele Strukturverschiebung [N]; Ganztonabstand eigene Wahl [I]. Quellen: S4.
- **Stimmungen:** dunkle Monumentalität, Tragik

### B.6 Nicht-funktionale Dreiklangsfolgen, hexatonische und Großterz-Beziehungen

#### HE-H38 · Dur-Tritonuspolarität

- **XYZ-Anker:** 0,55 / 0,30 / 0,55 (Region mRm, Ecke HRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 2 | T1 | C E G | C | Chromatisch |
| 2 | `F#` | 2 | T3 | F♯ A♯ C♯ | F♯ | Chromatisch |
| 3 | `C` | 4 | T5 | C E G | C | Chromatisch |

- **Wirkung:** Zwei helle Durklänge ohne gemeinsamen Ton; Helligkeit wird fremd, nicht froh.
- **Bassführung:** C2 – F♯1 – C2.
- **Begleitformen:** HE-R02, HE-R56
- **Variation:** F♯ nur einen Takt; oder beide Klänge gleichzeitig: getrennt zwischen Pedalen (HE-H56) oder verschmolzen (HE-H57).
- **Herrmann-Verfahren:** Dur–Tritonus–Dur-Folge im Vorspann von The Day the Earth Stood Still, später vertikalisiert (Moreira). Quellen: S1.
- **Stimmungen:** kalte Helligkeit, surreal

#### HE-H39 · Mollklänge in kleinen Terzen

- **XYZ-Anker:** 0,20 / 0,40 / 0,55 (Region Dmm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 2 | T1 | C E♭ G | C | Chromatisch |
| 2 | `Ebm` | 2 | T3 | E♭ G♭ B♭ | E♭ | Chromatisch |
| 3 | `F#m` | 2 | T5 | F♯ A C♯ | F♯ | Chromatisch |
| 4 | `Am` | 2 | T7 | A C E | A | Chromatisch |

- **Wirkung:** Jeder Schritt verdunkelt anders; der Kreis schließt sich nach vier Stationen.
- **Bassführung:** C–E♭–F♯–A.
- **Begleitformen:** HE-R22, HE-R33
- **Variation:** Abwärts gelesen (C–A–F♯–E♭) für Sinken.
- **Herrmann-Verfahren:** Terzbeziehungen und symmetrische Folgen [I]. Quellen: S11.
- **Stimmungen:** mysteriös, Paranoia

#### HE-H40 · Hexatonischer Pol

- **XYZ-Anker:** 0,40 / 0,30 / 0,55 (Region mRm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Hex-C · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 4 | T1 | C E G | C | Hex-C |
| 2 | `Abm` | 4 | T5 | A♭ B E♭ | A♭ | Hex-C |

- **Wirkung:** Dur kippt in ein Moll eine große Terz tiefer; kein Ton bleibt liegen, aber jeder bewegt sich nur einen Halbton (C→B, E→E♭, G→A♭) – das Vertraute wird unheimlich.
- **Bassführung:** C2 → A♭1.
- **Begleitformen:** HE-R16, HE-R54
- **Variation:** Rückweg A♭m → C; oder Pol nur in der Langen Fläche, Bass bleibt C (Abm/C).
- **Herrmann-Verfahren:** Hexatonische Pole als Agenten des Unheimlichen (Smith mit Cohn), strukturell in Vertigo. Quellen: S5.
- **Stimmungen:** unheimlich, mysteriös

#### HE-H41 · Großterzzyklus in Dur

- **XYZ-Anker:** 0,75 / 0,55 / 0,35 (Region HmS, Ecke HIS) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 2 | T1 | C E G | C | Chromatisch |
| 2 | `E` | 2 | T3 | E G♯ B | E | Chromatisch |
| 3 | `Ab` | 2 | T5 | A♭ C E♭ | A♭ | Chromatisch |
| 4 | `C` | 2 | T7 | C E G | C | Chromatisch |

- **Wirkung:** Breites, geheimnisvolles Staunen; die Klänge steigen hell und kommen am Ausgang wieder an – keine Freude, sondern Ehrfurcht.
- **Bassführung:** C–E–A♭–C in weiter Lage.
- **Begleitformen:** HE-R54, HE-R41
- **Variation:** Statt Rückkehr zu C in Takt 7 einen Ganzton-Ausschnitt anhängen (HE-H47).
- **Herrmann-Verfahren:** Großterzzyklus in Dur (Vertigo, „Dawn“, T. 25 ff., nach Cooper über Smith); eigene Transposition und Dauer. Quellen: S5, S9.
- **Stimmungen:** geheimnisvolles Staunen, dunkle Monumentalität

#### HE-H42 · Hexatonischer Zyklus

- **XYZ-Anker:** 0,45 / 0,35 / 0,55 (Region mRm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Hex-C · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 1 | T1 | C E G | C | Hex-C |
| 2 | `Cm` | 1 | T2 | C E♭ G | C | Hex-C |
| 3 | `Ab` | 1 | T3 | A♭ C E♭ | A♭ | Hex-C |
| 4 | `Abm` | 1 | T4 | A♭ B E♭ | A♭ | Hex-C |
| 5 | `E` | 1 | T5 | E G♯ B | E | Hex-C |
| 6 | `Em` | 1 | T6 | E G B | E | Hex-C |
| 7 | `C` | 2 | T7 | C E G | C | Hex-C |

- **Wirkung:** Jeder Schritt bewegt genau einen Ton um einen Halbton; der Weg ist glatt und führt doch in fremde Gegenden.
- **Bassführung:** Grundtöne C–C–A♭–A♭–E–E–C, Lage halten.
- **Begleitformen:** HE-R17, HE-R13
- **Variation:** Nur die ersten vier Klänge pendeln (C–Cm–A♭–A♭m–A♭–C).
- **Herrmann-Verfahren:** Hexatonische Organisation ist für Vertigo belegt [N]; der vollständige Zyklus als Akkordkette ist Interpretation [I]. Quellen: S5.
- **Stimmungen:** surreal, mysteriös

#### HE-H43 · Neapolitanischer Schatten ohne Kadenz

- **XYZ-Anker:** 0,20 / 0,25 / 0,45 (Region DRm, Ecke DRS) · **Taktart:** 4/4 · **Tonvorrat:** Phrygisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 2 | T1 | C E♭ G | C | Phrygisch |
| 2 | `Db/C` | 2 | T3 | C D♭ F A♭ | C | Phrygisch |
| 3 | `Cm` | 2 | T5 | C E♭ G | C | Phrygisch |
| 4 | `Db/C` | 2 | T7 | C D♭ F A♭ | C | Phrygisch |

- **Wirkung:** Ein Halbton-Schatten legt sich über das Moll und zieht sich zurück; das Pedal C hält alles fest.
- **Bassführung:** C2 liegend.
- **Begleitformen:** HE-R58, HE-R18
- **Variation:** D♭ nur als Tupferakkord, Fläche bleibt Cm.
- **Herrmann-Verfahren:** Klangpendel mit gemeinsamem Ton über Pedal [I]; neapolitanischer Klang ohne Dominantfolge. Quellen: S5.
- **Stimmungen:** latente Bedrohung, Melancholie
- **Technische Anforderungen:** Pedal über Akkordwechsel

#### HE-H44 · Liegeton im Bass wird umgedeutet

- **XYZ-Anker:** 0,25 / 0,30 / 0,55 (Region DRm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 2 | T1 | C E♭ G | C | Chromatisch |
| 2 | `Ab/C` | 2 | T3 | C A♭ E♭ | C | Chromatisch |
| 3 | `Dbmaj7/C` | 2 | T5 | C D♭ F A♭ | C | Chromatisch |
| 4 | `F#7b5/C` | 2 | T7 | C F♯ A♯ E | C | Chromatisch |

- **Wirkung:** Der Bass C bleibt; darüber ist er nacheinander Grundton, Terz, große Septime und Tritonus. Bedrohung wächst, ohne dass der Bass sich bewegt.
- **Bassführung:** C2 liegend, keine Bewegung.
- **Begleitformen:** HE-R02, HE-R39
- **Variation:** Reihenfolge umkehren (Spannung nimmt ab, Bass bleibt).
- **Herrmann-Verfahren:** Liegeton, der sich zu jedem neuen Klang anders verhält (Konsonanz → Septime → Tritonus) [I]. Quellen: S5.
- **Stimmungen:** langsam wachsende Bedrohung, mysteriös
- **Technische Anforderungen:** Pedal über Akkordwechsel

#### HE-H45 · Dur-Moll-Umfärbung gleichen Grundtons

- **XYZ-Anker:** 0,40 / 0,20 / 0,35 (Region mRS, Ecke DRS) · **Taktart:** 4/4 · **Tonvorrat:** Dur-Moll-Mischung · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 4 | T1 | C E G | C | Dur-Moll-Mischung |
| 2 | `Cm` | 4 | T5 | C E♭ G | C | Dur-Moll-Mischung |

- **Wirkung:** Eine einzige Terz senkt sich; Licht wird zu Schatten. Melancholie ohne Drama.
- **Bassführung:** C2 liegend.
- **Begleitformen:** HE-R54, HE-R46
- **Variation:** Umgekehrt (Moll → Dur) als trügerische Aufhellung.
- **Herrmann-Verfahren:** Klangwechsel über gemeinsame Töne [I]. Quellen: S6.
- **Stimmungen:** Melancholie, Tragik

#### HE-H46 · Mollfolge mit offenem Ausgang

- **XYZ-Anker:** 0,20 / 0,30 / 0,30 (Region DRS, Ecke DRS) · **Taktart:** 4/4 · **Tonvorrat:** Moll gesamt · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 2 | T1 | C E♭ G | C | Moll gesamt |
| 2 | `Abmaj7` | 2 | T3 | A♭ C E♭ G | A♭ | Moll gesamt |
| 3 | `Fm6` | 2 | T5 | F A♭ C D | F | Moll gesamt |
| 4 | `CmM7` | 2 | T7 | C E♭ G B | C | Moll gesamt |

- **Wirkung:** Getragene, dunkle Folge; die letzte Station ist nicht Ruhe, sondern der eingefrorene Moll-Dur-Klang.
- **Bassführung:** C–A♭–F–C, stufenweise Mittelstimmen.
- **Begleitformen:** HE-R54, HE-R37
- **Variation:** Takt 7–8 länger halten (vier Takte) und ausdünnen.
- **Herrmann-Verfahren:** Funktional entkernte Molltonalität [I], Schluss auf dem mM7-Objekt [N]. Quellen: S2, S4.
- **Stimmungen:** Tragik, Melancholie

#### HE-H47 · Großterzschritt in einen Ganztonausschnitt

- **XYZ-Anker:** 0,65 / 0,45 / 0,45 (Region Hmm, Ecke HRS) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 2 | T1 | C E G | C | Chromatisch |
| 2 | `E` | 2 | T3 | E G♯ B | E | Chromatisch |
| 3 | `{Ab Bb C D E}` | 4 | T5 | A♭ B♭ C D E | A♭ | Chromatisch |

- **Wirkung:** Zwei helle Klänge, dann löst sich die Harmonie in einen schwebenden Ganztonvorrat auf; Staunen wird Entrückung.
- **Bassführung:** C–E, dann A♭1 liegend.
- **Begleitformen:** HE-R13, HE-R54
- **Variation:** Ganztonausschnitt als Arpeggio statt als Fläche.
- **Herrmann-Verfahren:** Großterzzyklus, danach ein fünftöniger Ganzton-Ausschnitt (Vertigo, „Dawn“). Quellen: S9, S5.
- **Stimmungen:** geheimnisvolles Staunen, surreal

#### HE-H48 · Übermäßige Dreiklänge im Ganztonabstand

- **XYZ-Anker:** 0,50 / 0,30 / 0,55 (Region mRm, Ecke HRU) · **Taktart:** 4/4 · **Tonvorrat:** Ganzton-0 · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Caug` | 2 | T1 | C E G♯ | C | Ganzton-0 |
| 2 | `Daug` | 2 | T3 | D F♯ A♯ | D | Ganzton-0 |
| 3 | `Caug` | 2 | T5 | C E G♯ | C | Ganzton-0 |
| 4 | `Daug` | 2 | T7 | D F♯ A♯ | D | Ganzton-0 |

- **Wirkung:** Zwei übermäßige Dreiklänge derselben Ganztonreihe (C–E–G♯ und D–F♯–A♯) wechseln ohne gemeinsamen Ton; zusammen füllen sie die ganze Reihe. Die Schwebe bekommt einen Puls, bleibt aber in einem Vorrat.
- **Bassführung:** Kein Bass oder C2/D2 sehr leise.
- **Begleitformen:** HE-R13, HE-R37
- **Variation:** Halbtonabstand (C aug – D♭ aug): dann zwei verschiedene Ganztonreihen, deutlich schärfer.
- **Herrmann-Verfahren:** Übermäßige Dreiklänge auf zwei Stufen um einen gemeinsamen Ton (in Vertigo auf E♭ und D, Smith) [N]; Ganztonabstand eigene Wahl [I]. Quellen: S5.
- **Stimmungen:** Schwindel, mysteriös

### B.7 Ganzton

#### HE-H49 · Ganztonfeld

- **XYZ-Anker:** 0,50 / 0,20 / 0,55 (Region mRm, Ecke HRU) · **Taktart:** 4/4 · **Tonvorrat:** Ganzton-0 · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C9#5` | 8 | T1 | C E G♯ B♭ D | C | Ganzton-0 |

- **Wirkung:** Fünf Töne der Ganztonreihe gleichzeitig; Schweben ohne Schwerpunkt, Traum, Fremdheit.
- **Bassführung:** Kein Bass oder C2 pp.
- **Begleitformen:** HE-R13, HE-R36
- **Variation:** Bass auf jedem der sechs Töne möglich, ohne den Klang zu ändern.
- **Herrmann-Verfahren:** Ganztonklänge als Mittel der Schwebe und Unaufgelöstheit (Cooper über Smith). Quellen: S9.
- **Stimmungen:** surreal, mysteriös

#### HE-H50 · Beide Ganztonhälften im Wechsel

- **XYZ-Anker:** 0,40 / 0,40 / 0,70 (Region mmU, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C9#5` | 2 | T1 | C E G♯ B♭ D | C | Chromatisch |
| 2 | `Db9#5` | 2 | T3 | D♭ F A B E♭ | D♭ | Chromatisch |
| 3 | `C9#5` | 2 | T5 | C E G♯ B♭ D | C | Chromatisch |
| 4 | `Db9#5` | 2 | T7 | D♭ F A B E♭ | D♭ | Chromatisch |

- **Wirkung:** Zwei Schwebefelder im Halbtonabstand aus verschiedenen Ganztonreihen; die notierten Fünfklänge ergeben zusammen zehn Tonklassen (es fehlen F♯ und G). Die Schwebe wird zur Drohung.
- **Bassführung:** C2–D♭2.
- **Begleitformen:** HE-R27, HE-R21
- **Variation:** Wechsel nur im Arpeggio, Fläche bleibt auf C9♯5.
- **Herrmann-Verfahren:** Halbtonpendel [N] mit Ganztonklängen [I]. Quellen: S4, S9.
- **Stimmungen:** Paranoia, surreal

### B.8 Polychorde

#### HE-H51 · Moll über Moll im Tritonus, getrennt

- **XYZ-Anker:** 0,15 / 0,25 / 0,65 (Region DRU, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `F#m\|Cm` | 8 | T1 | C E♭ G F♯ A C♯ | C | Chromatisch |

- **Wirkung:** Zwei klar unterscheidbare Schichten; keine Panik, sondern das Gefühl, dass zwei Wirklichkeiten zugleich gelten.
- **Bassführung:** C2 als tiefster Ton der unteren Schicht.
- **Begleitformen:** HE-R06, HE-R18
- **Variation:** Obere Schicht nur in den Takten 3–4 und 7–8.
- **Herrmann-Verfahren:** Präferenz für zwei Molldreiklänge im Tritonusabstand (m6m); getrennte Schichten = latente, rätselhafte Wirkung (Moreira). Quellen: S1, S10.
- **Stimmungen:** latente Bedrohung, surreal
- **Polychord als Komponenten** (getrennt; Synchronität: versetzt: obere Schicht setzt nie mit der unteren ein; Intervallbeziehung: Grundtöne im Tritonus (6 Halbtöne); keine gemeinsamen Töne; Abstand zwischen den Schichten mehr als eine Oktave):

| Komponente | Tonhöhen | Register | Rollen |
|---|---|---|---|
| unten: C-Moll | C3 E♭3 G3 | MIDI 48–55 | LF (gehalten) |
| oben: F♯-Moll | F♯5 A5 C♯6 | MIDI 78–85 | TU oder AR (vereinzelt) |

  Erwartete Wirkung: rätselhaft, latent; die Schichten sind einzeln hörbar.
- **Technische Anforderungen:** Exakte Registervorgabe, Mehrere harmonische Komponenten

#### HE-H52 · Moll über Moll im Tritonus, verschmolzen

- **XYZ-Anker:** 0,15 / 0,85 / 0,70 (Region DIU, Ecke DIU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `F#m\|Cm` | 8 | T1 | C E♭ G F♯ A C♯ | C | Chromatisch |

- **Wirkung:** Dieselben sechs Tonklassen wie HE-H51, aber eng, gleichzeitig und gleich gefärbt: ein einziger schneidender Klang.
- **Bassführung:** C2 + C1 Oktave.
- **Begleitformen:** HE-R41, HE-R14
- **Variation:** Nur als Schlag (HE-R14) statt gehalten.
- **Herrmann-Verfahren:** Verschmelzung durch Synchronität, Parallelführung, Registernähe und gleiche Klangfarbe steigert die Bedrohung (Moreira). Quellen: S1.
- **Stimmungen:** akuter Horror
- **Polychord als Komponenten** (verschmolzen; Synchronität: synchron, gleiche Dauer, gleiche Velocity; Intervallbeziehung: Tritonus; Schichten überlappen im Register (F♯4 liegt zwischen E♭4 und G4)):

| Komponente | Tonhöhen | Register | Rollen |
|---|---|---|---|
| unten: C-Moll | C4 E♭4 G4 | MIDI 60–67 | KF + LF |
| oben: F♯-Moll | F♯4 A4 C♯5 | MIDI 66–73 | KF + LF |

  Erwartete Wirkung: akut, schneidend; die Teilklänge sind nicht mehr einzeln hörbar.
- **Technische Anforderungen:** Exakte Registervorgabe, Mehrere harmonische Komponenten

#### HE-H53 · Moll über Moll in großer Septime, weit

- **XYZ-Anker:** 0,15 / 0,30 / 0,60 (Region DRm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Bm\|Cm` | 8 | T1 | C E♭ G B D F♯ | C | Chromatisch |

- **Wirkung:** Die Reibung liegt in großen Septimen statt in kleinen Sekunden; bedrohlich, aber noch nicht schreiend.
- **Bassführung:** C2.
- **Begleitformen:** HE-R16, HE-R59
- **Variation:** Obere Schicht zwei Oktaven tiefer, zwischen die Töne der unteren (Verschmelzung, siehe HE-H60); für kleine Sekunden statt großer Septimen HE-H54.
- **Herrmann-Verfahren:** Halbtonverwandte Mollschichten werden öfter als große Septime (ro11) als als kleine Sekunde gestapelt; weite Lage weniger scharf (Moreira). Quellen: S1.
- **Stimmungen:** Unbehagen, latente Bedrohung
- **Polychord als Komponenten** (getrennt; Synchronität: synchron gehalten oder oben verzögert; Intervallbeziehung: obere Wurzel eine große Septime über der unteren (11 Halbtöne); C–B, E♭–D, G–F♯ als große Septimen):

| Komponente | Tonhöhen | Register | Rollen |
|---|---|---|---|
| unten: C-Moll | C3 E♭3 G3 | MIDI 48–55 | LF |
| oben: H-Moll | B4 D5 F♯5 | MIDI 71–78 | LF (zweite Lage) oder AR |

  Erwartete Wirkung: kalte, gespannte Ruhe.
- **Technische Anforderungen:** Exakte Registervorgabe, Mehrere harmonische Komponenten

#### HE-H54 · Moll über Moll im Halbton, eng

- **XYZ-Anker:** 0,10 / 0,80 / 0,90 (Region DIU, Ecke DIU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Dbm\|Cm` | 8 | T1 | C E♭ G D♭ E A♭ | C | Chromatisch |

- **Wirkung:** Maximale Nähe: drei echte kleine Sekunden; ein Klang, der weh tut.
- **Bassführung:** C2 + C1.
- **Begleitformen:** HE-R41, HE-R50
- **Variation:** Nur einen Takt lang, dann HE-H53 (Entkopplung: die Bedrohung lauert weiter).
- **Herrmann-Verfahren:** Mollschichten in maximaler Nähe mit drei echten kleinen Sekunden (Moreira über The Naked and the Dead, „The Snake“). Quellen: S1.
- **Stimmungen:** akuter Horror
- **Polychord als Komponenten** (verschmolzen; Synchronität: synchron, Akzent; Intervallbeziehung: Halbton (1); C–D♭, E♭–E, G–A♭ jeweils als kleine Sekunde nebeneinander):

| Komponente | Tonhöhen | Register | Rollen |
|---|---|---|---|
| unten: C-Moll | C4 E♭4 G4 | MIDI 60–67 | KF |
| oben: D♭-Moll | D♭4 E4 A♭4 | MIDI 61–68 | KF |

  Erwartete Wirkung: Schmerz, Schock.
- **Technische Anforderungen:** Exakte Registervorgabe, Mehrere harmonische Komponenten

#### HE-H55 · Polyklang-Pendel mit Registertausch

- **XYZ-Anker:** 0,25 / 0,30 / 0,55 (Region DRm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Em\|{Ab C}` | 2 | T1 | A♭ C E G B | A♭ | Chromatisch |
| 2 | `Fm\|{A Db}` | 2 | T3 | A D♭ F A♭ C | A | Chromatisch |
| 3 | `Em\|{Ab C}` | 2 | T5 | A♭ C E G B | A♭ | Chromatisch |
| 4 | `Fm\|{A Db}` | 2 | T7 | A D♭ F A♭ C | A | Chromatisch |

- **Wirkung:** Zwei getrennte Schichten pendeln gemeinsam einen Halbton; im zweiten Durchgang tauschen sie das Register. Gefahr im Raum, aber noch nicht sichtbar.
- **Bassführung:** Unterste Schicht ist die Dyade; kein zusätzlicher Bass.
- **Begleitformen:** HE-R17, HE-R53
- **Variation:** Registertausch erst nach acht Takten (Wiederholung).
- **Herrmann-Verfahren:** Molldreiklang über einer Dyade, im Wechsel mit derselben Struktur einen Halbton höher; ab T. 9 tauschen die Schichten das Register (North by Northwest, „The House“, Moreira). Quellen: S1.
- **Stimmungen:** latente Bedrohung, Thriller
- **Polychord als Komponenten** (getrennt; Synchronität: getrennt im Register; im Takt gleichzeitig, im zweiten Durchgang Register getauscht (Dreiklang unten, Dyade oben); Intervallbeziehung: Dyade (große Terz) und Molldreiklang: B gegen C bzw. C gegen D♭ als Halbtonreibung zwischen den Schichten):

| Komponente | Tonhöhen | Register | Rollen |
|---|---|---|---|
| Dyade | A♭2 C3 → A2 D♭3 | MIDI 44–49 | LB + LF |
| Molldreiklang | E4 G4 B4 → F4 A♭4 C5 | MIDI 64–72 | KF oder AR |

  Erwartete Wirkung: latente Gefahr.
- **Technische Anforderungen:** Exakte Registervorgabe, Mehrere harmonische Komponenten

#### HE-H56 · Dur zwischen zwei Pedalen im Tritonus

- **XYZ-Anker:** 0,60 / 0,20 / 0,50 (Region mRm, Ecke HRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `F#/C` | 8 | T1 | C F♯ A♯ C♯ | C | Chromatisch |

- **Wirkung:** Ein heller Durklang schwebt zwischen einem tiefen und einem hohen C; schön, still und völlig fremd.
- **Bassführung:** C1 + C2 tief, C6 hoch (Hochpedal).
- **Begleitformen:** HE-R36, HE-R58
- **Variation:** Hochpedal weglassen (wird dunkler, nicht ruhiger).
- **Herrmann-Verfahren:** Durklang in der Mittellage zwischen tiefen und hohen Pedalen im Tritonusabstand (The Day the Earth Stood Still, „Klaatu“, Moreira). Quellen: S1.
- **Stimmungen:** unheimliche Schönheit, kalte Helligkeit
- **Polychord als Komponenten** (getrennt; Synchronität: Pedale liegen, Mittelklang setzt später ein; Intervallbeziehung: Tritonus zwischen Pedal und Grundton des Mittelklangs):

| Komponente | Tonhöhen | Register | Rollen |
|---|---|---|---|
| Pedale | C1 C2 + C6 | MIDI 24/36 und 84 | LB + TU (gehalten) |
| Mittelklang: F♯-Dur | F♯3 A♯3 C♯4 | MIDI 54–61 | LF |

  Erwartete Wirkung: trügerische Ruhe, kalte Schönheit.
- **Technische Anforderungen:** Mehrstimmiger Bass, Exakte Registervorgabe, Mehrere harmonische Komponenten

#### HE-H57 · Dur über Dur im Tritonus, hell verschmolzen

- **XYZ-Anker:** 0,70 / 0,80 / 0,75 (Region HIU, Ecke HIU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `F#\|C` | 8 | T1 | C E G F♯ A♯ C♯ | C | Chromatisch |

- **Wirkung:** Dieselbe Tritonus-Polarität wie HE-H56, aber eng, hoch, synchron und scharf: kalte, gleißende Gefahr.
- **Bassführung:** C2 kurz mit dem Schlag.
- **Begleitformen:** HE-R14, HE-R57
- **Variation:** Als Hemiolen-Schläge (HE-R10).
- **Herrmann-Verfahren:** Polarität bleibt, Spannung steigt durch Verschmelzung und hellere Farbe („Klaatu“ → „The Ray“, Moreira). Quellen: S1.
- **Stimmungen:** kalte Spannung, akuter Horror
- **Polychord als Komponenten** (verschmolzen; Synchronität: synchron, kurz, akzentuiert; Intervallbeziehung: Tritonus; Schichten unmittelbar übereinander (G5–F♯5 Halbton als Nahtstelle)):

| Komponente | Tonhöhen | Register | Rollen |
|---|---|---|---|
| unten: C-Dur | C5 E5 G5 | MIDI 72–79 | KF |
| oben: F♯-Dur | F♯5 A♯5 C♯6 | MIDI 78–85 | KF |

  Erwartete Wirkung: kalte, helle Schärfe.
- **Technische Anforderungen:** Exakte Registervorgabe, Mehrere harmonische Komponenten

#### HE-H58 · Chromatische Mediante über Dur

- **XYZ-Anker:** 0,60 / 0,30 / 0,50 (Region mRm, Ecke HRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `E\|C` | 8 | T1 | C E G G♯ B | C | Chromatisch |

- **Wirkung:** Weniger dissonant als die Mollpolychorde (nur G–G♯ und B–C reiben), aber eindeutig nicht in einer Tonart; fremdes Licht.
- **Bassführung:** C2.
- **Begleitformen:** HE-R13, HE-R36
- **Variation:** Obere Schicht E-Moll statt E-Dur (milder, fast CM7).
- **Herrmann-Verfahren:** Chromatische Mediant-Schichtungen als zweite, mildere Polychord-Familie (Moreira). Quellen: S1.
- **Stimmungen:** surreal, geheimnisvolles Staunen
- **Polychord als Komponenten** (getrennt; Synchronität: unabhängig; obere Schicht als Arpeggio; Intervallbeziehung: große Terz (4); gemeinsamer Ton E):

| Komponente | Tonhöhen | Register | Rollen |
|---|---|---|---|
| unten: C-Dur | C3 E3 G3 | MIDI 48–55 | LF |
| oben: E-Dur | E5 G♯5 B5 | MIDI 76–83 | AR oder TU |

  Erwartete Wirkung: fremde Helligkeit.
- **Technische Anforderungen:** Exakte Registervorgabe, Mehrere harmonische Komponenten

#### HE-H59 · Moll über Moll über tiefer Tritonusdyade

- **XYZ-Anker:** 0,10 / 0,90 / 0,60 (Region DIm, Ecke DIU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Bm\|Fm` | 8 | T1 | F A♭ C B D F♯ | F | Chromatisch |

- **Wirkung:** Drei Schichten: ein tiefer, in Oktaven gedoppelter Tritonus und darüber zwei Mollklänge im Tritonus. Wucht ohne Hektik.
- **Bassführung:** E♭1/E♭2 + A1/A2 (Tritonusdyade in Oktaven).
- **Begleitformen:** HE-R41, HE-R08
- **Variation:** Obere Schicht erst nach zwei Takten dazu (Bass allein droht schon).
- **Herrmann-Verfahren:** Tiefe Tritonusdyade in mehreren Oktaven, darüber ein Moll-Moll-Polyakkord fortissimo (It’s Alive, Moreira Bsp. 2). Quellen: S1.
- **Stimmungen:** dunkle Monumentalität, akuter Horror
- **Polychord als Komponenten** (Dyade getrennt, Mollschichten verschmolzen; Synchronität: Dyade lang; Mollschichten synchron; Intervallbeziehung: Dyade E♭–A (Tritonus); F-Moll und H-Moll im Tritonus; A♭–A und C–B als Halbtonnähte):

| Komponente | Tonhöhen | Register | Rollen |
|---|---|---|---|
| Dyade tief | E♭1 A1 E♭2 A2 | MIDI 27–45 | LB |
| Mitte: F-Moll | F3 A♭3 C4 | MIDI 53–60 | LF |
| oben: H-Moll | B3 D4 F♯4 | MIDI 59–66 | LF + KF |

  Erwartete Wirkung: Masse, Schwere.
- **Technische Anforderungen:** Mehrstimmiger Bass, Exakte Registervorgabe, Mehrere harmonische Komponenten

#### HE-H60 · Polychord rückt zusammen

- **XYZ-Anker:** 0,15 / 0,55 / 0,65 (Region DmU, Ecke DIU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Bm\|Cm` | 8 | T1 | C E♭ G B D F♯ | C | Chromatisch |

- **Wirkung:** Gleiche Töne über acht Takte; die obere Schicht sinkt Takt für Takt näher an die untere, bis beide ineinander liegen. Bedrohung wächst nur durch Lage.
- **Bassführung:** C2 liegend.
- **Begleitformen:** HE-R16, HE-R39
- **Variation:** Rückweg (auseinanderziehen) als Entspannung ohne Materialwechsel.
- **Herrmann-Verfahren:** Intensität eines Polyakkords über Lagenabstand und Verschmelzung steuerbar (Moreira); als Prozess eigene Ableitung [E]. Quellen: S1.
- **Stimmungen:** langsam wachsende Bedrohung
- **Polychord als Komponenten** (getrennt → verschmolzen; Synchronität: ab Takt 5 synchron; Intervallbeziehung: große Septime; ab Takt 5 greifen die Schichten ineinander (B2–C3, D3–E♭3, F♯3–G3 als kleine Sekunden)):

| Komponente | Tonhöhen | Register | Rollen |
|---|---|---|---|
| unten: C-Moll | C3 E♭3 G3 | MIDI 48–55 | LF |
| oben: H-Moll | Takt 1–2: B5 D6 F♯6 · 3–4: B4 D5 F♯5 · 5–8: B2 D3 F♯3 (zwischen den Tönen der unteren Schicht) | MIDI 83 → 47 | KF → LF |

  Erwartete Wirkung: Bedrohung kommt näher.
- **Technische Anforderungen:** Exakte Registervorgabe, Mehrere harmonische Komponenten

#### HE-H61 · Verschmolzene Polychorde parallel steigend

- **XYZ-Anker:** 0,25 / 0,90 / 0,85 (Region DIU, Ecke DIU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Bm\|Cm` | 1 | T1 | C E♭ G B D F♯ | C | Chromatisch |
| 2 | `Cm\|C#m` | 1 | T2 | C♯ E G♯ C E♭ G | C♯ | Chromatisch |
| 3 | `C#m\|Dm` | 1 | T3 | D F A C♯ E G♯ | D | Chromatisch |
| 4 | `Dm\|Ebm` | 1 | T4 | E♭ G♭ B♭ D F A | E♭ | Chromatisch |
| 5 | `Ebm\|Em` | 1 | T5 | E G B E♭ G♭ B♭ | E | Chromatisch |
| 6 | `Em\|Fm` | 1 | T6 | F A♭ C E G B | F | Chromatisch |
| 7 | `Fm\|F#m` | 1 | T7 | F♯ A C♯ F A♭ C | F♯ | Chromatisch |
| 8 | `F#m\|Gm` | 1 | T8 | G B♭ D F♯ A C♯ | G | Chromatisch |

- **Wirkung:** Akute Todesgefahr: ein verschmolzener, greller Doppelklang klettert Halbton für Halbton.
- **Bassführung:** Parallel zur unteren Schicht.
- **Begleitformen:** HE-R41, HE-R12
- **Variation:** Halbtaktig; letzter Klang zwei Takte gehalten.
- **Herrmann-Verfahren:** Parallele, verschmolzene Polyakkorde in großer Septime im Blech bei akuter Todesgefahr (North by Northwest, „The Cliff“, Moreira). Quellen: S1.
- **Stimmungen:** akuter Horror, Eskalation
- **Polychord als Komponenten** (verschmolzen; Synchronität: synchron, parallel; Intervallbeziehung: konstant große Septime):

| Komponente | Tonhöhen | Register | Rollen |
|---|---|---|---|
| unten: Molldreiklang | C4 E♭4 G4 (steigt je Takt einen Halbton) | MIDI 60–74 | KF + LF |
| oben: Molldreiklang eine große Septime höher | B4 D5 F♯5 (steigt parallel) | MIDI 71–85 | KF + LF |

  Erwartete Wirkung: Panik, Absturzgefahr.
- **Technische Anforderungen:** Exakte Registervorgabe, Mehrere harmonische Komponenten, Kanon/koordinierte Parallelstimmen

#### HE-H62 · Unvollständige Schichten werden vollständig

- **XYZ-Anker:** 0,15 / 0,60 / 0,70 (Region DmU, Ecke DIU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `{B D}\|{C Eb}` | 4 | T1 | C E♭ B D | C | Chromatisch |
| 2 | `Bm\|Cm` | 4 | T5 | C E♭ G B D F♯ | C | Chromatisch |

- **Wirkung:** Zuerst nur zwei Dyaden, die Polarität ist zu ahnen; dann treten die fehlenden Töne hinzu und die Bedrohung ist da.
- **Bassführung:** C2.
- **Begleitformen:** HE-R14, HE-R22
- **Variation:** Vollständigen Klang nur zwei Takte und zurück zu den Dyaden.
- **Herrmann-Verfahren:** Polyakkord zuerst unvollständig, dann komplett (Mysterious Island, Riesenkrabbe, Moreira). Quellen: S1.
- **Stimmungen:** langsam wachsende Bedrohung, Eskalation
- **Polychord als Komponenten** (verschmolzen ab Takt 5; Synchronität: synchron; Intervallbeziehung: große Septime; Terzschichten zuerst ohne Quinte):

| Komponente | Tonhöhen | Register | Rollen |
|---|---|---|---|
| unten | C3 E♭3 → C3 E♭3 G3 | MIDI 48–55 | LF |
| oben | B3 D4 → B3 D4 F♯4 | MIDI 59–66 | KF |

  Erwartete Wirkung: Ahnung → Gewissheit.
- **Technische Anforderungen:** Exakte Registervorgabe, Mehrere harmonische Komponenten

#### HE-H63 · Zeitversetzter Polychord

- **XYZ-Anker:** 0,20 / 0,20 / 0,60 (Region DRm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Ebm\|Am` | 8 | T1 | A C E E♭ G♭ B♭ | A | Chromatisch |

- **Wirkung:** Leise und zeitversetzt: die zweite Schicht erscheint immer eine Achtel nach der ersten, wie ein Schatten.
- **Bassführung:** A1.
- **Begleitformen:** HE-R60, HE-R18
- **Variation:** Versatz wächst (Achtel → Viertel → Halbe) = Schichten lösen sich voneinander.
- **Herrmann-Verfahren:** Moll über Moll im Tritonus, zeitversetzt und leise: „suspense more than immediate threat“ (Sisters, „The Scar“, Moreira). Quellen: S1.
- **Stimmungen:** latente Bedrohung, psychologische Spannung
- **Polychord als Komponenten** (getrennt (zeitlich); Synchronität: versetzt um eine Achtel; Intervallbeziehung: Tritonus; E–E♭ als Halbtonnaht):

| Komponente | Tonhöhen | Register | Rollen |
|---|---|---|---|
| unten: A-Moll | A3 C4 E4 | MIDI 57–64 | KF (zuerst) |
| oben: E♭-Moll | E♭4 G♭4 B♭4 | MIDI 63–70 | TU (eine Achtel später) |

  Erwartete Wirkung: Schatten, Unheimlichkeit.
- **Technische Anforderungen:** Exakte Registervorgabe, Mehrere harmonische Komponenten

### B.9 Unabhängige Pedale

#### HE-H64 · Liegeton oben als Blick

- **XYZ-Anker:** 0,25 / 0,25 / 0,45 (Region DRm, Ecke DRS) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 2 | T1 | C E♭ G | C | Chromatisch |
| 2 | `Abmaj7` | 2 | T3 | A♭ C E♭ G | A♭ | Chromatisch |
| 3 | `Ebaug` | 2 | T5 | E♭ G B | E♭ | Chromatisch |
| 4 | `Db` | 2 | T7 | D♭ F A♭ | D♭ | Chromatisch |

- **Wirkung:** Ein hoher Ton G bleibt; darunter wechseln vier Klänge, zu denen er Quinte, große Septime, Terz und Tritonus ist. Obsession: der Blick weicht nicht.
- **Bassführung:** Grundtöne C–A♭–E♭–D♭ tief.
- **Begleitformen:** HE-R36, HE-R53
- **Variation:** Liegeton als Tupfer repetieren (Viertel) statt halten.
- **Herrmann-Verfahren:** Die „obsessive“ Note D in Vertigo, die das Modulieren verhindert (Brown, Smith). Quellen: S5, S9.
- **Stimmungen:** Obsession, Bann
- **Technische Anforderungen:** Pedal über Akkordwechsel

#### HE-H65 · Doppelpedal im Abstand einer None

- **XYZ-Anker:** 0,20 / 0,40 / 0,65 (Region DmU, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Fm7` | 2 | T1 | F A♭ C E♭ | F | Chromatisch |
| 2 | `Em7` | 2 | T3 | E G B D | E | Chromatisch |
| 3 | `Ebm7` | 2 | T5 | E♭ G♭ B♭ D♭ | E♭ | Chromatisch |
| 4 | `Dm7` | 2 | T7 | D F A C | D | Chromatisch |

- **Wirkung:** Unten zwei Pedaltöne (E und F, eine None auseinander) reiben dauerhaft; darüber sinken Septakkorde.
- **Bassführung:** E1 gehalten + F2 im Viertelpuls (HE-B04).
- **Begleitformen:** HE-R04, HE-R02
- **Variation:** Nur das Doppelpedal, keine Oberklänge (reiner Bann).
- **Herrmann-Verfahren:** Doppelpedal-Ostinato: Viola F in Vierteln, Celli pizz. E eine None tiefer, Kontrabass gehaltenes E (Psycho, „The Toys“). Quellen: S4.
- **Stimmungen:** Unbehagen, Obsession
- **Technische Anforderungen:** Mehrstimmiger Bass, Pedal über Akkordwechsel

#### HE-H66 · Dur über Tritonusbass

- **XYZ-Anker:** 0,55 / 0,25 / 0,60 (Region mRm, Ecke HRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C/F#` | 8 | T1 | F♯ C E G | F♯ | Chromatisch |

- **Wirkung:** Hell im Oberklang, haltlos darunter; trügerische Ruhe.
- **Bassführung:** F♯1 liegend.
- **Begleitformen:** HE-R58, HE-R36
- **Variation:** F♯ nur als einzelner Impuls alle vier Takte (HE-B19).
- **Herrmann-Verfahren:** Bass als Tritonus zum Akkordgrundton (Moreira über „Klaatu“). Quellen: S1.
- **Stimmungen:** kalte Helligkeit, Unbehagen

#### HE-H67 · Moll über Halbtonpedal

- **XYZ-Anker:** 0,15 / 0,30 / 0,65 (Region DRU, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Phrygisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm/Db` | 8 | T1 | D♭ C E♭ G | D♭ | Phrygisch |

- **Wirkung:** Ein ruhiger Mollklang, dem der Boden einen Halbton zu hoch steht.
- **Bassführung:** D♭1 liegend.
- **Begleitformen:** HE-R58, HE-R35
- **Variation:** D♭ und C im Bass alle zwei Takte tauschen (HE-B14).
- **Herrmann-Verfahren:** Halbtonbeziehung Pedal–Oberklang als Lauer-Bass [I]. Quellen: S5.
- **Stimmungen:** latente Bedrohung, Unbehagen

#### HE-H68 · Hochpedal über tiefem Moll

- **XYZ-Anker:** 0,45 / 0,15 / 0,55 (Region mRm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 8 | T1 | C E♭ G | C | Chromatisch |

- **Wirkung:** Unten ruhiges Moll, ganz oben ein einzelner, reiner F♯-Ton; kalte Helligkeit, die nicht dazugehört.
- **Bassführung:** C2; Hochpedal F♯6 (in der Tonvorlage nicht enthalten, Rolle TU oder LF lang).
- **Begleitformen:** HE-R58, HE-R18
- **Variation:** Hochpedal B6 statt F♯6 (große Septime, milder).
- **Herrmann-Verfahren:** Hohe, sinusartige Liegetöne als kalte Helligkeit (Theremin-Funktion, Day the Earth) [N]; Tritonusbezug [I]. Quellen: S1.
- **Stimmungen:** kalte Helligkeit, subliminale Spannung
- **Technische Anforderungen:** Exakte Registervorgabe

#### HE-H69 · Mittelklang wechselt zwischen zwei festen Pedalen

- **XYZ-Anker:** 0,45 / 0,25 / 0,55 (Region mRm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Ab/C` | 2 | T1 | C A♭ E♭ | C | Chromatisch |
| 2 | `F#/C` | 2 | T3 | C F♯ A♯ C♯ | C | Chromatisch |
| 3 | `D7/C` | 2 | T5 | C D F♯ A | C | Chromatisch |
| 4 | `F#/C` | 2 | T7 | C F♯ A♯ C♯ | C | Chromatisch |

- **Wirkung:** Tiefes und hohes C bleiben; dazwischen wandern Durklänge, zu denen C Terz, Tritonus und Septime ist.
- **Bassführung:** C1 + C2; Hochpedal C6.
- **Begleitformen:** HE-R36, HE-R16
- **Variation:** Hochpedal nur in den F♯-Takten.
- **Herrmann-Verfahren:** Pedal tief und hoch, Mittelklang dazwischen (Klaatu-Verfahren) verallgemeinert [I]. Quellen: S1.
- **Stimmungen:** unheimliche Schönheit, mysteriös
- **Technische Anforderungen:** Pedal über Akkordwechsel

#### HE-H70 · Fallender Bass unter festem Ton bis zum Tritonus

- **XYZ-Anker:** 0,30 / 0,30 / 0,55 (Region DRm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 2 | T1 | C E G | C | Chromatisch |
| 2 | `E/B` | 2 | T3 | B E G♯ | B | Chromatisch |
| 3 | `Edim/Bb` | 2 | T5 | B♭ E G | B♭ | Chromatisch |
| 4 | `Bb7b5` | 2 | T7 | B♭ D E A♭ | B♭ | Chromatisch |

- **Wirkung:** Der Ton E bleibt oben, der Bass fällt C–B–B♭; am Ende steht E im Tritonus zum Bass.
- **Bassführung:** C2–B1–B♭1–B♭1.
- **Begleitformen:** HE-R36, HE-R25
- **Variation:** Fallen langsamer (vier Takte je Ton).
- **Herrmann-Verfahren:** D wird wiederholt, während der Bass von B♭ nach E fällt, beide Grundtöne einer französischen Sexte (Vertigo, Albtraum, Smith); eigene Töne. Quellen: S5.
- **Stimmungen:** langsam wachsende Bedrohung, Albtraum
- **Technische Anforderungen:** Pedal über Akkordwechsel

### B.10 Cluster und Intervallverzahnung

#### HE-H71 · Cluster aus gestapelten großen Septimen

- **XYZ-Anker:** 0,15 / 0,95 / 0,70 (Region DIU, Ecke DIU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `{Ab G F# F}` | 8 | T1 | A♭ G F♯ F | A♭ | Chromatisch |

- **Wirkung:** Vier Nachbartöne, aber weit gespreizt (je eine große Septime auseinander), von oben nach unten aufgebaut: schreiend, aber nicht matschig.
- **Bassführung:** tiefster Ton F2 (Ende der Kaskade).
- **Begleitformen:** HE-R51, HE-R14
- **Variation:** Eng statt gespreizt: dieselben vier Töne F, F♯, G, A♭ als dichter Cluster in einer Oktave – dumpf statt schneidend. (HE-H73 ist ein anderer, dreitöniger Cluster C–D♭–D in tiefer Lage.)
- **Herrmann-Verfahren:** E♭, E, F, G♭ als absteigende große Septimen gestapelt, von oben nach unten eingesetzt, sffz (Psycho, „The Murder“, T. 1–16); eigene Tonhöhen. Quellen: S4.
- **Stimmungen:** akuter Horror
- **Technische Anforderungen:** Exakte Registervorgabe

#### HE-H72 · Verschränkte Tritoni

- **XYZ-Anker:** 0,15 / 0,70 / 0,80 (Region DIU, Ecke DIU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `{C F# F B}` | 8 | T1 | C F♯ F B | C | Chromatisch |

- **Wirkung:** Zwei Tritoni im Halbtonabstand; ein Klang ohne jede Mitte.
- **Bassführung:** C2 und F2 im Wechsel (HE-B12).
- **Begleitformen:** HE-R33, HE-R12
- **Variation:** Nur ein Tritonus, der zweite als Tupfer.
- **Herrmann-Verfahren:** Ineinander verschränkte Tritoni D/G♯ + G/C♯ ab „The Murder“ T. 18; eigene Transposition. Quellen: S4.
- **Stimmungen:** akuter Horror, Paranoia

#### HE-H73 · Enger Cluster, tief und leise

- **XYZ-Anker:** 0,05 / 0,15 / 0,55 (Region DRm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `{C Db D}` | 8 | T1 | C D♭ D | C | Chromatisch |

- **Wirkung:** Drei Halbtöne dicht beieinander in tiefer Lage, kaum hörbar; ein Druck auf den Ohren.
- **Bassführung:** Der Cluster selbst ist der Bass (C2 D♭2 D2).
- **Begleitformen:** HE-R58, HE-R35
- **Variation:** Ein Ton nach dem anderen hinzufügen (HE-H74).
- **Herrmann-Verfahren:** Tonal abgeleitete Atonalität: Cluster aus Halbtonzellen (Pearson, Husarik) [N]; leise und tief eigene Anwendung [I]. Quellen: S4, S16.
- **Stimmungen:** subliminale Spannung, latente Bedrohung

#### HE-H74 · Cluster wächst Ton um Ton

- **XYZ-Anker:** 0,10 / 0,50 / 0,70 (Region DmU, Ecke DIU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `{C Db}` | 2 | T1 | C D♭ | C | Chromatisch |
| 2 | `{B C Db}` | 2 | T3 | B C D♭ | B | Chromatisch |
| 3 | `{B C Db D}` | 2 | T5 | B C D♭ D | B | Chromatisch |
| 4 | `{Bb B C Db D}` | 2 | T7 | B♭ B C D♭ D | B♭ | Chromatisch |

- **Wirkung:** Je zwei Takte kommt ein Nachbarton hinzu, abwechselnd unten und oben; der Klang wird dichter, nicht lauter.
- **Bassführung:** Tiefster Ton wandert C–B–B–B♭.
- **Begleitformen:** HE-R16, HE-R39
- **Variation:** Gleiche Velocity in allen Takten halten (nur die Reibung steigt).
- **Herrmann-Verfahren:** Steigerung über Dissonanzschärfe vor Dichte [I]; Clustermaterial [N]. Quellen: S4, S1.
- **Stimmungen:** langsam wachsende Bedrohung, Eskalation

#### HE-H75 · Verzahnte große Terzen

- **XYZ-Anker:** 0,25 / 0,50 / 0,75 (Region DmU, Ecke DIU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `{C E Db F}` | 8 | T1 | C E D♭ F | C | Chromatisch |

- **Wirkung:** Zwei große Terzen im Halbtonabstand greifen ineinander; ein stampfender, fremder Klang ohne Grundton.
- **Bassführung:** kein Bass oder C2.
- **Begleitformen:** HE-R06, HE-R01
- **Variation:** Terzen abwechselnd statt gleichzeitig (HE-R06).
- **Herrmann-Verfahren:** Zwei verschränkte große Terzen E/G♯ + F/A als Ostinato (Psycho-Prelude ab T. 29; Pearson vergleicht mit dem Sacre); eigene Töne. Quellen: S4.
- **Stimmungen:** Thriller, Paranoia

### B.11 Helle und dunkle Spannungsfarben

#### HE-H76 · Kalte Dur-Septnonakkorde in Blöcken abwärts

- **XYZ-Anker:** 0,80 / 0,20 / 0,35 (Region HRS, Ecke HRS) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [H], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cmaj9` | 2 | T1 | C E G B D | C | Chromatisch |
| 2 | `Bbmaj9` | 2 | T3 | B♭ D F A C | B♭ | Chromatisch |
| 3 | `Abmaj9` | 2 | T5 | A♭ C E♭ G B♭ | A♭ | Chromatisch |
| 4 | `Gbmaj9` | 2 | T7 | G♭ B♭ D♭ F A♭ | G♭ | Chromatisch |

- **Wirkung:** Hell, klar, lyrisch einfach – und doch fremd, weil die Blöcke nur verschoben werden; Licht ohne Wärme.
- **Bassführung:** kein Bass oder sehr leise Grundtöne.
- **Begleitformen:** HE-R36, HE-R54
- **Variation:** Nur Dreiklänge (C, B♭, A♭, G♭) – noch kühler.
- **Herrmann-Verfahren:** Absteigende Akkordfolgen und kleine verschobene Klangblöcke in heller Besetzung, Dissonanz gemieden (Fahrenheit 451, nach Intrada; populäre Quelle). Quellen: S19.
- **Stimmungen:** kalte Helligkeit, Melancholie

#### HE-H77 · Spieluhr-Dur mit falschem Ton

- **XYZ-Anker:** 0,75 / 0,15 / 0,45 (Region HRm, Ecke HRS) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C` | 2 | T1 | C E G | C | Chromatisch |
| 2 | `Cadd#4` | 2 | T3 | C E F♯ G | C | Chromatisch |
| 3 | `C` | 2 | T5 | C E G | C | Chromatisch |
| 4 | `E/C` | 2 | T7 | C E G♯ B | C | Chromatisch |

- **Wirkung:** Kindliche Helligkeit, in die ein einzelner falscher Ton (F♯) und eine fremde Mediante (E-Dur) einbrechen.
- **Bassführung:** kein Bass oder C3.
- **Begleitformen:** HE-R36, HE-R18
- **Variation:** Falscher Ton nur im Tupfer, Fläche bleibt rein.
- **Herrmann-Verfahren:** Helle Glockenspiel-/Vibraphonfarbe wie eine Spieluhr als Bedrohung (Sisters, Moreira) [N]; Akkordfolge eigene Konstruktion. Quellen: S1.
- **Stimmungen:** unheimliche Schönheit, surreal

#### HE-H78 · Lyrischer Vorhalt-Aufstieg

- **XYZ-Anker:** 0,30 / 0,40 / 0,30 (Region DmS, Ecke DRS) · **Taktart:** 4/4 · **Tonvorrat:** Moll gesamt · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cmadd9` | 2 | T1 | C E♭ G D | C | Moll gesamt |
| 2 | `Ab` | 2 | T3 | A♭ C E♭ | A♭ | Moll gesamt |
| 3 | `Fm9` | 2 | T5 | F A♭ C E♭ G | F | Moll gesamt |
| 4 | `CmM7` | 2 | T7 | C E♭ G B | C | Moll gesamt |

- **Wirkung:** Sehnsucht, die sich hochschraubt und nicht ankommt; endet im eingefrorenen Klang.
- **Bassführung:** C–A♭–F–C.
- **Begleitformen:** HE-R54, HE-R46
- **Variation:** Schlussklang durch Cm ersetzen (Trauer statt Unruhe).
- **Herrmann-Verfahren:** Liebesthemen aus demselben Vierton-Vorhalt-Prototyp, verlängert und aufwärts sequenziert (Schneller); Schluss auf mM7 [I]. Quellen: S7.
- **Stimmungen:** Tragik, Melancholie

#### HE-H79 · Moll-Mauer im Tritonus

- **XYZ-Anker:** 0,10 / 0,85 / 0,30 (Region DIS, Ecke DIS) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 2 | T1 | C E♭ G | C | Chromatisch |
| 2 | `F#m` | 2 | T3 | F♯ A C♯ | F♯ | Chromatisch |
| 3 | `Cm` | 2 | T5 | C E♭ G | C | Chromatisch |
| 4 | `F#m` | 2 | T7 | F♯ A C♯ | F♯ | Chromatisch |

- **Wirkung:** Homogene, schwere Mollblöcke, langsam und laut; Bedrohung durch Masse, nicht durch Tempo.
- **Bassführung:** Oktavbass C1/C2 – F♯1/F♯2.
- **Begleitformen:** HE-R41, HE-R08
- **Variation:** Wechsel nur alle vier Takte (noch statischer).
- **Herrmann-Verfahren:** Homogene Blechblöcke, „a fortress-like wall of sound“, langsam (Torn Curtain, Oxford-Kapitel, Abstract) [N]; Tritonuswahl [I]. Quellen: S15, S10.
- **Stimmungen:** dunkle Monumentalität
- **Technische Anforderungen:** Mehrstimmiger Bass

#### HE-H80 · Orgelpunkt-Säulen

- **XYZ-Anker:** 0,10 / 0,75 / 0,25 (Region DIS, Ecke DIS) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm/G` | 4 | T1 | G C E♭ | G | Chromatisch |
| 2 | `Abm/Eb` | 4 | T5 | E♭ A♭ B | E♭ | Chromatisch |

- **Wirkung:** Zwei breite Mollsäulen in tiefer, voller Lage über Quintbässen; feierlich und finster.
- **Bassführung:** G1 → E♭1, je vier Takte, Oktave verdoppelt.
- **Begleitformen:** HE-R08, HE-R58
- **Variation:** Zweite Säule eine große Terz tiefer statt kleiner Sexte höher (gleich, nur Lage).
- **Herrmann-Verfahren:** Orgel-Pedalpunkte und tiefe Register als Weltfarbe (Journey, Herrmann 1974) [N]; Akkordwahl [I]. Quellen: S15.
- **Stimmungen:** dunkle Monumentalität, Tragik

#### HE-H81 · Leere Quinte mit Halbtonnachbar

- **XYZ-Anker:** 0,20 / 0,20 / 0,40 (Region DRm, Ecke DRS) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `{C G Ab}` | 8 | T1 | C G A♭ | C | Chromatisch |

- **Wirkung:** Hohl und offen; ein einziger Ton zu viel (A♭) macht die Leere unruhig.
- **Bassführung:** C2.
- **Begleitformen:** HE-R58, HE-R35
- **Variation:** A♭ ↔ F♯ alle vier Takte (Halbton → Tritonus).
- **Herrmann-Verfahren:** Systemfremder Halbtonnachbar zu einem stabilen Klang [I]. Quellen: S5.
- **Stimmungen:** subliminale Spannung, latente Bedrohung

#### HE-H82 · Kadenzattrappe

- **XYZ-Anker:** 0,25 / 0,40 / 0,50 (Region Dmm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Moll gesamt · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 2 | T1 | C E♭ G | C | Moll gesamt |
| 2 | `G7b9` | 2 | T3 | G B D F A♭ | G | Moll gesamt |
| 3 | `Ab` | 2 | T5 | A♭ C E♭ | A♭ | Moll gesamt |
| 4 | `G7b9` | 2 | T7 | G B D F A♭ | G | Moll gesamt |

- **Wirkung:** Die Funktion wird angedeutet und verweigert; die Dominante bleibt am Ende stehen.
- **Bassführung:** C–G–A♭–G.
- **Begleitformen:** HE-R15, HE-R21
- **Variation:** Letzte Dominante halten und Fläche ausdünnen statt aufzulösen.
- **Herrmann-Verfahren:** Tonal resonant, aber nicht aufgelöst (Interview 1975) [N/I]. Quellen: S2.
- **Stimmungen:** Thriller, Erwartung

#### HE-H83 · Moll mit kleiner None

- **XYZ-Anker:** 0,15 / 0,25 / 0,60 (Region DRm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Phrygisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm(addb9)` | 8 | T1 | C E♭ G D♭ | C | Phrygisch |

- **Wirkung:** Ein ruhiger Mollklang mit einer eingebauten Halbtonreibung über dem Grundton.
- **Bassführung:** C2.
- **Begleitformen:** HE-R58, HE-R37
- **Variation:** D♭ nur im zweiten und vierten Takt jeder Gruppe.
- **Herrmann-Verfahren:** Halbtonnachbar als systemfremder Ton [I]. Quellen: S5.
- **Stimmungen:** latente Bedrohung, Unbehagen

#### HE-H84 · Verdunkelung durch eine einzige Stimme

- **XYZ-Anker:** 0,20 / 0,30 / 0,55 (Region DRm, Ecke DRU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `CmM7` | 2 | T1 | C E♭ G B | C | Chromatisch |
| 2 | `CdimM7` | 2 | T3 | C E♭ G♭ B | C | Chromatisch |
| 3 | `Cdim7` | 2 | T5 | C E♭ G♭ A | C | Chromatisch |
| 4 | `Cm7b5` | 2 | T7 | C E♭ G♭ B♭ | C | Chromatisch |

- **Wirkung:** Grundton und Terz bleiben; erst sinkt die Quinte, dann die Septime, zuletzt hebt sich die Septime einen Halbton – der Klang verfinstert sich und bleibt fragend stehen.
- **Bassführung:** C2 liegend.
- **Begleitformen:** HE-R16, HE-R59
- **Variation:** Rückwärts für trügerische Erleichterung.
- **Herrmann-Verfahren:** Klangobjekte mit gemeinsamen Tönen als Zustandskette (Empfehlung des Berichts) [I]. Quellen: S6.
- **Stimmungen:** langsam wachsende Bedrohung, Tragik

#### HE-H85 · Moll öffnet sich in die chromatische Mediante

- **XYZ-Anker:** 0,40 / 0,35 / 0,45 (Region mRm, Ecke DRS) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 4 | T1 | C E♭ G | C | Chromatisch |
| 2 | `E` | 4 | T5 | E G♯ B | E | Chromatisch |

- **Wirkung:** Ein Mollklang hellt sich nicht auf, sondern wird entrückt; der neue Durklang wirkt wie ein anderer Raum.
- **Bassführung:** C2 → E2 (oder Pedal C: E/C).
- **Begleitformen:** HE-R54, HE-R13
- **Variation:** E-Dur über liegendem C (E/C); mit vollständigem C-Dur darunter wird daraus der Polychord HE-H58.
- **Herrmann-Verfahren:** Chromatische Mediante ohne Funktion [I]; bei Herrmann als Pantriadik integraler Personalstil (Lehman, Snippet) [N]. Quellen: S11.
- **Stimmungen:** Tragik, geheimnisvolles Staunen

#### HE-H86 · Mollsäulen mit großer Septime im Bass

- **XYZ-Anker:** 0,15 / 0,60 / 0,35 (Region DmS, Ecke DIS) · **Taktart:** 4/4 · **Tonvorrat:** Moll harm. · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 4 | T1 | C E♭ G | C | Moll harm. |
| 2 | `Cm/B` | 4 | T5 | B C E♭ G | B | Moll harm. |

- **Wirkung:** Breit und schwer; im zweiten Teil steht der Klang auf seiner eigenen Septime. Monumental und fremd.
- **Bassführung:** C1/C2 → B0/B1 (Oktaven).
- **Begleitformen:** HE-R08, HE-R41
- **Variation:** B im Bass nur zwei Takte.
- **Herrmann-Verfahren:** Moll-Dur-Objekt mit Septime im Bass [I]. Quellen: S6.
- **Stimmungen:** dunkle Monumentalität
- **Technische Anforderungen:** Mehrstimmiger Bass

#### HE-H87 · Halbverminderter Walzerklang

- **XYZ-Anker:** 0,25 / 0,20 / 0,45 (Region DRm, Ecke DRS) · **Taktart:** 3/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [E], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm7b5` | 4 | T1 | C E♭ G♭ B♭ | C | Chromatisch |
| 2 | `Bm7b5` | 4 | T5 | B D F A | B | Chromatisch |

- **Wirkung:** Ein müder Dreiertakt auf einem fragenden Klang, der einmal einen Halbton absackt.
- **Bassführung:** C2 auf 1, sonst Pause; dann B1.
- **Begleitformen:** HE-R38, HE-R37
- **Variation:** Zweite Hälfte wieder zurück nach Cm7♭5 (Kreislauf).
- **Herrmann-Verfahren:** Leblose Tanzbewegung in zyklischer Wiederholung (Cooper über „Carlotta’s Portrait“) [N] auf eigenes Klangmaterial übertragen [E]. Quellen: S9.
- **Stimmungen:** Melancholie, Bann

#### HE-H88 · Moll-Dur-Septakkord im Sechsachtel

- **XYZ-Anker:** 0,20 / 0,25 / 0,45 (Region DRm, Ecke DRS) · **Taktart:** 6/8 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [E], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `CmM7` | 4 | T1 | C E♭ G B | C | Chromatisch |
| 2 | `AbmM7/C` | 4 | T5 | C A♭ B E♭ G | C | Chromatisch |

- **Wirkung:** Wiegender Dreierpuls auf eingefrorenem Klang; Wiegenlied, das nicht beruhigt.
- **Bassführung:** C2 liegend.
- **Begleitformen:** HE-R56, HE-R10
- **Variation:** Zweiten Klang weglassen (nur mM7).
- **Herrmann-Verfahren:** mM7-Objekt [N] in wiegender Bewegung [E]. Quellen: S6.
- **Stimmungen:** unheimliche Schönheit, psychologische Spannung

### B.12 Helle und kraftvolle Bereiche

#### HE-H89 · Tritonus-Polarität als breite Säule

- **XYZ-Anker:** 0,70 / 0,75 / 0,35 (Region HIS, Ecke HIS) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `F#\|C` | 8 | T1 | C E G F♯ A♯ C♯ | C | Chromatisch |

- **Wirkung:** Laut, hell und ruhig: die beiden Durklänge stehen weit getrennt und lange; Ehrfurcht vor etwas Fremdem, keine Hektik.
- **Bassführung:** C1/C2 Oktave, lang.
- **Begleitformen:** HE-R41, HE-R54
- **Variation:** Obere Schicht erst nach zwei Takten (Säule wächst).
- **Herrmann-Verfahren:** Polychord-Kalibrierung: weite Lage und Trennung mindern die Schärfe, Lautstärke und Höhe erhöhen die Intensität (Moreira); Durpolarität aus Day the Earth. Quellen: S1.
- **Stimmungen:** geheimnisvolles Staunen, dunkle Monumentalität
- **Polychord als Komponenten** (getrennt; Synchronität: synchron, gehalten; Intervallbeziehung: Tritonus; Schichten mehr als eine Oktave getrennt):

| Komponente | Tonhöhen | Register | Rollen |
|---|---|---|---|
| unten: C-Dur | C3 G3 E4 | MIDI 48–64 | LF + LB |
| oben: F♯-Dur | F♯5 A♯5 C♯6 | MIDI 78–85 | LF (zweite Lage) |

  Erwartete Wirkung: erhaben, fremd.
- **Technische Anforderungen:** Exakte Registervorgabe, Mehrere harmonische Komponenten

#### HE-H90 · Helle Ganztonsäule

- **XYZ-Anker:** 0,65 / 0,70 / 0,40 (Region HIm, Ecke HIS) · **Taktart:** 4/4 · **Tonvorrat:** Ganzton-0 · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C9#5` | 8 | T1 | C E G♯ B♭ D | C | Ganzton-0 |

- **Wirkung:** Der Schwebeklang aus HE-H49, aber in hoher, weiter Lage und laut: Entrückung wird zur Erscheinung.
- **Bassführung:** C2 + C3.
- **Begleitformen:** HE-R41, HE-R54
- **Variation:** Mit tiefem F♯1 (Tritonus) statt C.
- **Herrmann-Verfahren:** Ganztonklang [N] mit Intensität durch Register und Lautstärke statt Bewegung [I]. Quellen: S9, S1.
- **Stimmungen:** geheimnisvolles Staunen, surreal

#### HE-H91 · Großer Septakkord mit Tritonus, breit

- **XYZ-Anker:** 0,75 / 0,60 / 0,40 (Region Hmm, Ecke HIS) · **Taktart:** 4/4 · **Tonvorrat:** Lydisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cmaj7#11` | 8 | T1 | C E G B F♯ | C | Lydisch |

- **Wirkung:** Strahlend, aber mit einem fremden Ton (F♯) mitten im Glanz; Ehrfurcht, nicht Jubel.
- **Bassführung:** C2 Oktave.
- **Begleitformen:** HE-R54, HE-R36
- **Variation:** F♯ als Hochpedal isolieren.
- **Herrmann-Verfahren:** Helligkeit ≠ Freude: helle Akkordqualität mit Tritonusbezug (Klaatu-Logik) [I]. Quellen: S1.
- **Stimmungen:** geheimnisvolles Staunen, kalte Helligkeit

#### HE-H92 · Helle Mediantenschläge

- **XYZ-Anker:** 0,70 / 0,75 / 0,70 (Region HIU, Ecke HIU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `E\|C` | 8 | T1 | C E G G♯ B | C | Chromatisch |

- **Wirkung:** HE-H58 verschmolzen, hoch und in unregelmäßigen Schlägen; gleißend und nervös.
- **Bassführung:** C2 kurz mit jedem Schlag.
- **Begleitformen:** HE-R10, HE-R57
- **Variation:** Schläge in Hemiolen.
- **Herrmann-Verfahren:** Verschmelzung und Schärfe steigern die Wirkung bei gleichem Material (Moreira) [N]; Mediantenschicht [N]; Anwendung [I]. Quellen: S1.
- **Stimmungen:** kalte Spannung
- **Polychord als Komponenten** (verschmolzen; Synchronität: synchron, kurz; Intervallbeziehung: große Terz; E gemeinsam, G–G♯ und B–C als Halbtonnähte):

| Komponente | Tonhöhen | Register | Rollen |
|---|---|---|---|
| unten: C-Dur | C5 E5 G5 | MIDI 72–79 | KF |
| oben: E-Dur | E5 G♯5 B5 | MIDI 76–83 | KF |

  Erwartete Wirkung: gleißend.
- **Technische Anforderungen:** Exakte Registervorgabe, Mehrere harmonische Komponenten

#### HE-H93 · Übermäßige Dreiklänge parallel steigend, hell

- **XYZ-Anker:** 0,65 / 0,80 / 0,80 (Region HIU, Ecke HIU) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Caug` | 1 | T1 | C E G♯ | C | Chromatisch |
| 2 | `Dbaug` | 1 | T2 | D♭ F A | D♭ | Chromatisch |
| 3 | `Daug` | 1 | T3 | D F♯ A♯ | D | Chromatisch |
| 4 | `Ebaug` | 1 | T4 | E♭ G B | E♭ | Chromatisch |
| 5 | `Caug` | 1 | T5 | C E G♯ | C | Chromatisch |
| 6 | `Dbaug` | 1 | T6 | D♭ F A | D♭ | Chromatisch |
| 7 | `Daug` | 1 | T7 | D F♯ A♯ | D | Chromatisch |
| 8 | `Ebaug` | 1 | T8 | E♭ G B | E♭ | Chromatisch |

- **Wirkung:** Schnell kletternde, helle Symmetrieklänge in hoher Lage; Taumel, Schwindel im Licht.
- **Bassführung:** kein Bass.
- **Begleitformen:** HE-R12, HE-R11
- **Variation:** Halbtaktig.
- **Herrmann-Verfahren:** Chromatische Verschiebung ganzer Strukturen [N] mit symmetrischem Objekt in heller Lage [I]. Quellen: S4, S5.
- **Stimmungen:** Schwindel, kalte Spannung

#### HE-H94 · Tiefe Moll-Dur-Mauer

- **XYZ-Anker:** 0,10 / 0,80 / 0,30 (Region DIS, Ecke DIS) · **Taktart:** 4/4 · **Tonvorrat:** Moll harm. · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `CmM7` | 8 | T1 | C E♭ G B | C | Moll harm. |

- **Wirkung:** Das Objekt aus HE-H01 in tiefer, enger Lage, laut und homogen: Bedrohung durch Masse.
- **Bassführung:** C1/C2 Oktave.
- **Begleitformen:** HE-R41, HE-R08
- **Variation:** Septime B nur in der tiefsten Lage (B1).
- **Herrmann-Verfahren:** Intensität durch Masse und Homogenität statt Tempo (Torn Curtain, Abstract) [N]; mM7-Objekt [N]. Quellen: S15, S6.
- **Stimmungen:** dunkle Monumentalität
- **Technische Anforderungen:** Mehrstimmiger Bass

#### HE-H95 · Langsamer Clusterblock

- **XYZ-Anker:** 0,10 / 0,85 / 0,40 (Region DIm, Ecke DIS) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `{C Db Eb E}` | 8 | T1 | C D♭ E♭ E | C | Chromatisch |

- **Wirkung:** Ein schwerer, dunkler Klangblock, lange gehalten; nicht hektisch, aber erdrückend.
- **Bassführung:** C1/C2.
- **Begleitformen:** HE-R41, HE-R58
- **Variation:** Ein Ton nach dem anderen abbauen (Entkopplung, nicht Entspannung).
- **Herrmann-Verfahren:** Cluster aus tonalem Kern (Dur-Moll-Terzen E♭/E) [N]; als langsamer Block [I]. Quellen: S4, S16.
- **Stimmungen:** dunkle Monumentalität, akuter Horror

#### HE-H96 · Dur über eigener Septime

- **XYZ-Anker:** 0,65 / 0,15 / 0,40 (Region HRm, Ecke HRS) · **Taktart:** 4/4 · **Tonvorrat:** Dur · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `C/B` | 8 | T1 | B C E G | B | Dur |

- **Wirkung:** Ein heller Dur-Klang, unter dem die große Septime liegt; still, freundlich klingend und doch nicht stimmig.
- **Bassführung:** B1 liegend.
- **Begleitformen:** HE-R58, HE-R36
- **Variation:** B im Bass nur jeden zweiten Takt.
- **Herrmann-Verfahren:** Halbtonbeziehung Bass–Grundton als Lauer-Bass [I]. Quellen: S5.
- **Stimmungen:** trügerische Ruhe, unheimliche Schönheit

#### HE-H97 · Hoher Quintklang mit Tritonus-Hochton

- **XYZ-Anker:** 0,65 / 0,10 / 0,35 (Region HRS, Ecke HRS) · **Taktart:** 4/4 · **Tonvorrat:** Lydisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `{C G D F#}` | 8 | T1 | C G D F♯ | C | Lydisch |

- **Wirkung:** Weit, hell, fast leer; der oberste Ton F♯ steht im Tritonus zum Boden. Kälte ohne Härte.
- **Bassführung:** C2 sehr leise.
- **Begleitformen:** HE-R58, HE-R36
- **Variation:** F♯ als einzelner Tupfer alle vier Takte.
- **Herrmann-Verfahren:** Hohe reine Liegetöne als kalte Helligkeit (Theremin-Funktion, Day the Earth) [N]; Tonwahl [I]. Quellen: S1.
- **Stimmungen:** kalte Helligkeit, subliminale Spannung
- **Technische Anforderungen:** Exakte Registervorgabe

#### HE-H98 · Großterzzyklus in Moll, tief

- **XYZ-Anker:** 0,10 / 0,70 / 0,40 (Region DIm, Ecke DIS) · **Taktart:** 4/4 · **Tonvorrat:** Hex-C · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Cm` | 2 | T1 | C E♭ G | C | Hex-C |
| 2 | `Abm` | 2 | T3 | A♭ B E♭ | A♭ | Hex-C |
| 3 | `Em` | 2 | T5 | E G B | E | Hex-C |
| 4 | `Cm` | 2 | T7 | C E♭ G | C | Hex-C |

- **Wirkung:** Drei Mollklänge im Großterzabstand, tief und breit; düstere Erhabenheit.
- **Bassführung:** C1–A♭0–E1–C1 (Oktaven).
- **Begleitformen:** HE-R08, HE-R41
- **Variation:** Mit Pedal C1 durchgehend (Abm/C, Em/C).
- **Herrmann-Verfahren:** Großterzzyklus [N] in Moll und tiefer Lage [I]. Quellen: S5.
- **Stimmungen:** dunkle Monumentalität, Tragik
- **Technische Anforderungen:** Mehrstimmiger Bass

#### HE-H99 · Dur über Dur im Halbton, hell und breit

- **XYZ-Anker:** 0,65 / 0,80 / 0,40 (Region HIm, Ecke HIS) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [N], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `Db\|C` | 8 | T1 | C E G D♭ F A♭ | C | Chromatisch |

- **Wirkung:** Zwei Durklänge einen Halbton auseinander, hoch, laut und lange gehalten: gleißende, starre Bedrohung. Kein Leitton, keine Kadenz, keine Melodie – deshalb wirkt der helle Klang nicht heroisch, sondern feindlich.
- **Bassführung:** C2 + C1 lang; kein Wechsel.
- **Begleitformen:** HE-R66, HE-R41
- **Variation:** Obere Schicht eine Oktave tiefer und ineinander (verschmolzen, akut); oder nur alle vier Takte neu anschlagen.
- **Herrmann-Verfahren:** Herrmann kombiniert Dur- oder Molldreiklänge, deren Grundtöne eine kleine Sekunde oder einen Tritonus auseinanderliegen (Leydon über Moreira); Intensität durch Höhe und Lautstärke bei langsamem Verlauf (Moreira). Quellen: S10, S1.
- **Stimmungen:** helle Bedrohung, kalte Spannung
- **Polychord als Komponenten** (getrennt im Register, synchron in der Zeit; Synchronität: synchron, lang gehalten; Intervallbeziehung: Halbton (1), gestapelt als große Septime plus Oktave; Nähte C–D♭, E–F, G–A♭ jeweils über eine Oktave verteilt):

| Komponente | Tonhöhen | Register | Rollen |
|---|---|---|---|
| unten: C-Dur | C4 E4 G4 | MIDI 60–67 | LF |
| oben: D♭-Dur | D♭5 F5 A♭5 | MIDI 73–80 | LF (zweite Lage) oder KF gehalten |

  Erwartete Wirkung: starr, gleißend, feindlich.
- **Technische Anforderungen:** Mehrstimmiger Bass, Exakte Registervorgabe, Mehrere harmonische Komponenten

#### HE-H100 · Übermäßige Säulen in hoher, weiter Lage

- **XYZ-Anker:** 0,60 / 0,75 / 0,30 (Region mIS, Ecke HIS) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `CaugM7` | 4 | T1 | C E G♯ B | C | Chromatisch |
| 2 | `DbaugM7` | 4 | T5 | D♭ F A C | D♭ | Chromatisch |

- **Wirkung:** Zwei helle, gläserne Säulen, laut und langsam, ein Halbton auseinander. Erhaben und kalt: Staunen, das nicht tröstet.
- **Bassführung:** C1/C2 → D♭1/D♭2, je vier Takte.
- **Begleitformen:** HE-R66, HE-R54
- **Variation:** Zweite Säule weglassen (acht Takte CaugM7): noch statischer.
- **Herrmann-Verfahren:** Übermäßige Klänge als Achse [N] mit Intensität durch Register und Masse statt Tempo [I]. Quellen: S5, S15.
- **Stimmungen:** geheimnisvolles Staunen, dunkle Monumentalität
- **Technische Anforderungen:** Mehrstimmiger Bass

#### HE-H101 · Kalte Quartenschichten ohne Grundton

- **XYZ-Anker:** 0,70 / 0,10 / 0,40 (Region HRm, Ecke HRS) · **Taktart:** 4/4 · **Tonvorrat:** Chromatisch · **Evidenz:** Verfahren [I], Akkordfolge [E]

| Nr | Akkord | Takte | ab | Tonklassen (Bass zuerst) | Bass | Tonvorrat |
|---|---|---|---|---|---|---|
| 1 | `{B E A D#}` | 4 | T1 | B E A E♭ | B | Chromatisch |
| 2 | `{Bb Eb Ab D}` | 4 | T5 | B♭ E♭ A♭ D | B♭ | Chromatisch |

- **Wirkung:** Vier Töne in Quarten mit einer großen Septime als Rahmen, hoch und sehr leise; nach vier Takten rückt der Block einen Halbton tiefer. Kalte, klare, unbewohnte Helligkeit.
- **Bassführung:** kein Bass.
- **Begleitformen:** HE-R64, HE-R58
- **Variation:** Nur der erste Block (acht Takte) für völligen Stillstand.
- **Herrmann-Verfahren:** Hohe, reine Liegetöne als kalte Helligkeit (Day the Earth) [N]; verschobene Klangblöcke (Fahrenheit 451, populäre Quelle) [H]; Klangbau eigen [I]. Quellen: S1, S19.
- **Stimmungen:** kalte Helligkeit, mysteriös
- **Technische Anforderungen:** Exakte Registervorgabe

## C Polychorde: Übersicht der Komponenten

Ein Polychord wird nie nur als Gesamtsymbol verwendet. Für jeden ist festgelegt, welche Teilklänge in welchem Register und welcher Rolle liegen und ob sie verschmolzen oder getrennt erklingen. **Verschmolzen** heißt: gleichzeitig, gleiche Dauer, Register überlappend oder unmittelbar benachbart, gleiche Velocity – der Hörer nimmt einen Klang wahr. **Getrennt** heißt: zeitversetzt, registerfern (mehr als eine Oktave) oder verschieden artikuliert – der Hörer nimmt zwei Schichten wahr.

| ID | Komponenten (oben → unten) | Intervall der Grundtöne | Verschmolzen/getrennt | Wirkung |
|---|---|---|---|---|
| HE-H51 | F♯-Moll (F♯5 A5 C♯6) / C-Moll (C3 E♭3 G3) | Grundtöne im Tritonus (6 Halbtöne) | getrennt | rätselhaft, latent; die Schichten sind einzeln hörbar |
| HE-H52 | F♯-Moll (F♯4 A4 C♯5) / C-Moll (C4 E♭4 G4) | Tritonus | verschmolzen | akut, schneidend; die Teilklänge sind nicht mehr einzeln hörbar |
| HE-H53 | H-Moll (B4 D5 F♯5) / C-Moll (C3 E♭3 G3) | obere Wurzel eine große Septime über der unteren (11 Halbtöne) | getrennt | kalte, gespannte Ruhe |
| HE-H54 | D♭-Moll (D♭4 E4 A♭4) / C-Moll (C4 E♭4 G4) | Halbton (1) | verschmolzen | Schmerz, Schock |
| HE-H55 | Molldreiklang (E4 G4 B4 → F4 A♭4 C5) / Dyade (A♭2 C3 → A2 D♭3) | Dyade (große Terz) und Molldreiklang: B gegen C bzw. C gegen D♭ als Halbtonreibung zwischen den Schichten | getrennt | latente Gefahr |
| HE-H56 | F♯-Dur (F♯3 A♯3 C♯4) / Pedale (C1 C2 + C6) | Tritonus zwischen Pedal und Grundton des Mittelklangs | getrennt | trügerische Ruhe, kalte Schönheit |
| HE-H57 | F♯-Dur (F♯5 A♯5 C♯6) / C-Dur (C5 E5 G5) | Tritonus | verschmolzen | kalte, helle Schärfe |
| HE-H58 | E-Dur (E5 G♯5 B5) / C-Dur (C3 E3 G3) | große Terz (4) | getrennt | fremde Helligkeit |
| HE-H59 | H-Moll (B3 D4 F♯4) / F-Moll (F3 A♭3 C4) / Dyade tief (E♭1 A1 E♭2 A2) | Dyade E♭–A (Tritonus) | Dyade getrennt, Mollschichten verschmolzen | Masse, Schwere |
| HE-H60 | H-Moll (Takt 1–2: B5 D6 F♯6 · 3–4: B4 D5 F♯5 · 5–8: B2 D3 F♯3 (zwischen den Tönen der unteren Schicht)) / C-Moll (C3 E♭3 G3) | große Septime | getrennt → verschmolzen | Bedrohung kommt näher |
| HE-H61 | Molldreiklang eine große Septime höher (B4 D5 F♯5 (steigt parallel)) / Molldreiklang (C4 E♭4 G4 (steigt je Takt einen Halbton)) | konstant große Septime | verschmolzen | Panik, Absturzgefahr |
| HE-H62 | oben (B3 D4 → B3 D4 F♯4) / unten (C3 E♭3 → C3 E♭3 G3) | große Septime | verschmolzen ab Takt 5 | Ahnung → Gewissheit |
| HE-H63 | E♭-Moll (E♭4 G♭4 B♭4) / A-Moll (A3 C4 E4) | Tritonus | getrennt (zeitlich) | Schatten, Unheimlichkeit |
| HE-H89 | F♯-Dur (F♯5 A♯5 C♯6) / C-Dur (C3 G3 E4) | Tritonus | getrennt | erhaben, fremd |
| HE-H92 | E-Dur (E5 G♯5 B5) / C-Dur (C5 E5 G5) | große Terz | verschmolzen | gleißend |
| HE-H99 | D♭-Dur (D♭5 F5 A♭5) / C-Dur (C4 E4 G4) | Halbton (1), gestapelt als große Septime plus Oktave | getrennt im Register, synchron in der Zeit | starr, gleißend, feindlich |

Präferenzen (Moreira, S1): zwei **Molldreiklänge** im **Tritonus** (HE-H51, H52, H59, H63) oder im **Halbtonverhältnis**, dabei öfter als große Septime (HE-H53, H60, H61) als als kleine Sekunde (HE-H54); daneben die mildere Familie der chromatischen Medianten (HE-H58, H92) und die Dur-Tritonus-Polarität (HE-H56, H57, H89). Die Studien HE-S06/S07, HE-S22, HE-S23, HE-S27, HE-T08 und HE-T13 führen denselben Polychord in verschiedenen Verschmelzungsgraden vor.

## D Rhythmisches Vokabular (HE-R01–R66)

Modultypen: **Bewegung** (durchgehender Fluss), **Interpunktion** (Einschnitt, Schlag, Leere), **Form** (Bar-Form, Kürzung, Verlängerung), **Akzent** (Verschiebung im gleichen Fluss), **Schichtung** (mehrere Schichten, koordiniert oder unabhängig), **Artikulation**, **Prozess** (Verdichtung, Ausdünnung, Beschleunigung ohne Tempoänderung), **Leere**.

Verteilung: Bewegung 21, Interpunktion 16, Schichtung 10, Akzent 5, Form 5, Prozess 5, Leere 3, Artikulation 1.

#### HE-R01 · Gleichmäßige Achtel ohne Akzent

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,25 / 0,40 / 0,55 (Dmm) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  x.x.x.x.x.x.x.x.|x.x.x.x.x.x.x.x.
```
- **Einsätze gesamt:** KF 16 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Bewegung · **Rollen:** KF (auch AR)
- **Harmonische Voraussetzung:** ein Klang oder Pendel alle 2 Takte
- **Wirkung:** Unaufhörlicher Fluss, der nichts betont; Flucht, Zwang, Fortbewegung ohne Ziel.
- **Varianten/Verdichtung:** Letzte Achtel jedes zweiten Takts weglassen (kleines Loch im Fluss).
- **Quellen:** S4, S7
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R02 · Puls statt Rhythmus

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,25 / 0,25 / 0,40 (DRm) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  x...x...x...x...|x...x...x...x...
```
- **Einsätze gesamt:** KF 8 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Bewegung · **Rollen:** KF oder LF (Neuanschlag je Viertel)
- **Harmonische Voraussetzung:** Klangkaskaden, Parallelklänge
- **Wirkung:** Gleichmäßige Viertel ohne rhythmisches Profil; wie ein Gang durch leere Straßen.
- **Varianten/Verdichtung:** Halbe statt Viertel (noch statischer).
- **Quellen:** S4
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R03 · Leises Synkopenostinato

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,25 / 0,20 / 0,65 (DRU) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  x.x---x.x...x.x.|x.x---x.x...x.x.
LB  x---------------|----------------
```
- **Einsätze gesamt:** KF 12, LB 1 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Bewegung · **Rollen:** KF, LB
- **Harmonische Voraussetzung:** Pendel mit gemeinsamen Tönen (HE-H26, HE-H27)
- **Wirkung:** Kaum hörbar, aber nie im Takt ruhend; Beschattung, Verfolgung im Schritttempo. Eigene Variante einer belegten Synkopenfigur (Achtel–Viertel–Achtel-Folge mit Pause).
- **Varianten/Verdichtung:** Viertel an Position 3 durch zwei Achtel ersetzen (dichter, gleiche Akzente).
- **Quellen:** S12, S5
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R04 · Doppelpedal im Viertelpuls

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,20 / 0,30 / 0,50 (DRm) · **Evidenz:** Verfahren [N], Raster [E]

```
LB  x---------------|----------------
KB  x...x...x...x...|x...x...x...x...
```
- **Einsätze gesamt:** LB 1, KB 8 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Bewegung · **Rollen:** LB, KB
- **Harmonische Voraussetzung:** Doppelpedal im None-Abstand (HE-B04)
- **Wirkung:** Ein gehaltener und ein pochender Basston reiben dauerhaft; mechanisch, kalt.
- **Varianten/Verdichtung:** KB nur auf 1 und 3.
- **Quellen:** S4
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R05 · Triolenzelle in Bar-Form

- **Taktart:** 4/4T (12 Schritte/Takt) · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,25 / 0,40 / 0,60 (Dmm) · **Evidenz:** Verfahren [N], Raster [E]

```
AR  xxx.........|xxx.........|xxx.xxx.xxx.|xxx---......
```
- **Einsätze gesamt:** AR 18 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Bewegung · **Rollen:** AR oder KF
- **Harmonische Voraussetzung:** Klangobjekt, ein Klang pro 2 Takte
- **Wirkung:** Kurze Triolenfigur, zweimal gestellt, dann gehäuft (a–a–b); erzeugt Druck ohne Lautstärke.
- **Varianten/Verdichtung:** b-Teil (Takt 3–4) auf einen Takt kürzen.
- **Quellen:** S7, S4
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R06 · Verzahnte Intervallschichten

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,25 / 0,45 / 0,70 (DmU) · **Evidenz:** Verfahren [N], Raster [E]

```
AR  x...x...x...x...|x...x...x...x...
TU  ..x...x...x...x.|..x...x...x...x.
```
- **Einsätze gesamt:** AR 8, TU 8 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Bewegung · **Rollen:** AR, TU (oder KF geteilt)
- **Harmonische Voraussetzung:** zwei Intervalle im Halbtonabstand (HE-H75)
- **Wirkung:** Zwei Schichten wechseln sich im Achtelabstand ab; zusammen ein Motor, einzeln Bruchstücke.
- **Varianten/Verdichtung:** TU um eine Sechzehntel verschieben (..x → ...x): stolpernd.
- **Quellen:** S4
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R07 · Drei Schichten mit eigener Periode

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,25 / 0,40 / 0,60 (Dmm) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  x...x...x...x...|x...x...x...x...|x...x...x...x...|x...x...x...x...
AR  x.x.x...........|........x.x.x...|x.x.x...........|........x.x.x...
TU  ................|..........x.....|................|.....x..........
```
- **Einsätze gesamt:** KF 16, AR 12, TU 2 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Bewegung · **Rollen:** KF (Puls), AR (Zelle), TU (Interpunktion)
- **Harmonische Voraussetzung:** ein Klangfeld
- **Wirkung:** Puls, Zelle und Interpunktion laufen nebeneinander; nur eine Schicht steht vorn, die anderen unterscheiden sich in Lage und Länge.
- **Varianten/Verdichtung:** TU-Positionen bei jeder Wiederholung neu verteilen.
- **Quellen:** S4, S7
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt
- **Technische Anforderungen:** Unabhängige rhythmische Zyklen

#### HE-R08 · Schweres Paukenostinato

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,10 / 0,70 / 0,35 (DIS) · **Evidenz:** Verfahren [N], Raster [E]

```
KB  X..x....X..x....|X..x....X..x....
```
- **Einsätze gesamt:** KB 8 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Bewegung · **Rollen:** KB (tief)
- **Harmonische Voraussetzung:** Mollsäulen, langsamer Klangwechsel
- **Wirkung:** Gewichtiger, langsamer Antrieb unter dunklen Blechblöcken; Schwere ohne Hast.
- **Varianten/Verdichtung:** Doppelschlag nur in Takt 2.
- **Quellen:** S14
- **Färbungsbereich:** bevorzugt X ≤ 0,5 (schwere tiefe Schläge); unter hellem Klang in hoher Lage wird daraus ein mechanischer Puls – dann leiser einsetzen

#### HE-R09 · Marschierendes Tubaostinato

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,15 / 0,55 / 0,35 (DmS) · **Evidenz:** Verfahren [N], Raster [E]

```
KB  x...x...x...x...|x...x...x.x.x...
```
- **Einsätze gesamt:** KB 9 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Bewegung · **Rollen:** KB
- **Harmonische Voraussetzung:** dunkle Pedalharmonik
- **Wirkung:** Unbeirrbarer Schritt; das Unheil geht ruhig weiter.
- **Varianten/Verdichtung:** Grundton–Tritonus im Wechsel (HE-B17).
- **Quellen:** S14
- **Färbungsbereich:** bevorzugt X ≤ 0,5 (Marschschritt in tiefer Lage)

#### HE-R10 · Hemiole 6/8 gegen 3/4

- **Taktart:** 6/8 (12 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,35 / 0,55 / 0,75 (DmU) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  X.x.x.X.x.x.|X.x.X.x.X.x.
KB  x...x...x...|x.....x.....
```
- **Einsätze gesamt:** KF 12, KB 5 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Akzent · **Rollen:** KF, KB
- **Harmonische Voraussetzung:** beliebig
- **Wirkung:** Gleichmäßige Achtel, deren Akzente zwischen 6/8 (1 und 4) und 3/4 (1, 3, 5) wechseln; der Bass liest jeweils die andere Taktart. Unruhe ohne Tempo- und Dichteänderung.
- **Varianten/Verdichtung:** KB-Takte vertauschen: dann lesen beide Rollen gleichzeitig dieselbe Taktart (weniger Reibung).
- **Quellen:** S18
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt
- **Technische Anforderungen:** Unabhängige rhythmische Zyklen

#### HE-R11 · Drei gegen vier

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 3 Takt(e) · **XYZ-Anker:** 0,30 / 0,45 / 0,80 (DmU) · **Evidenz:** Verfahren [I], Raster [E]

```
AR  x..x..x..x..x..x|..x..x..x..x..x.|.x..x..x..x..x..
KF  x...x...x...x...|x...x...x...x...|x...x...x...x...
```
- **Einsätze gesamt:** AR 16, KF 12 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Bewegung · **Rollen:** AR gegen KF
- **Harmonische Voraussetzung:** statischer Klang
- **Wirkung:** Eine Dreiergruppe läuft durch den Vierertakt und trifft erst nach drei Takten wieder auf die Eins.
- **Varianten/Verdichtung:** AR leiser als KF; die Verschiebung soll gespürt, nicht hervorgehoben werden.
- **Quellen:** S4
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt
- **Technische Anforderungen:** Unabhängige rhythmische Zyklen

#### HE-R12 · Rasende Dreiergruppen über langen Basstönen

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,15 / 0,80 / 0,90 (DIU) · **Evidenz:** Verfahren [N], Raster [E]

```
AR  xxxxxxxxxxxxxxxx|xxxxxxxxxxxxxxxx
LB  x---------------|----------------
```
- **Einsätze gesamt:** AR 32, LB 1 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Bewegung · **Rollen:** AR, LB
- **Harmonische Voraussetzung:** Reibungsklänge (HE-H34)
- **Wirkung:** Gehetzte Sechzehntel in 3/8-Gruppen gegen zweitaktige Basstöne; Panik über unbewegtem Boden.
- **Varianten/Verdichtung:** Akzente der AR in Dreiergruppen (X..X..X..) setzen.
- **Quellen:** S4
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R13 · Gegenläufige Triolenspiralen

- **Taktart:** 4/4T (12 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,45 / 0,35 / 0,75 (mRU) · **Evidenz:** Verfahren [N], Raster [E]

```
AR  xxxxxxxxxxxx|xxxxxxxxxxxx
TU  xxxxxxxxxxxx|xxxxxxxxxxxx
```
- **Einsätze gesamt:** AR 24, TU 24 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Bewegung · **Rollen:** AR (aufwärts–abwärts), TU (abwärts–aufwärts)
- **Harmonische Voraussetzung:** symmetrischer Klang (aug, Ganzton)
- **Wirkung:** Zwei Linien kreisen gegeneinander um eine Achse; Schwindel.
- **Varianten/Verdichtung:** TU nur in Takt 2.
- **Quellen:** S6, S5
- **Färbungsbereich:** X ≥ 0,3: die Spiralen brauchen symmetrische, eher helle Klänge
- **Technische Anforderungen:** Kanon/koordinierte Parallelstimmen

#### HE-R14 · Fünf synkopierte Schläge

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,20 / 0,70 / 0,60 (DIm) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  X..X..X...X..X..|................
```
- **Einsätze gesamt:** KF 5 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Interpunktion · **Rollen:** KF (+ LB auf den ersten Schlag)
- **Harmonische Voraussetzung:** Klangobjekt (mM7, Polychord)
- **Wirkung:** Ein Block aus Schlägen, der den Fluss unterbricht; danach ein ganzer Takt Leere.
- **Varianten/Verdichtung:** Nur drei Schläge; oder zweite Hälfte als Echo leiser.
- **Quellen:** S4, S7
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R15 · Punktierte Blockakkorde mit Bassantwort

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,25 / 0,60 / 0,60 (Dmm) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  X--x....X--x....|X--x....X--x....
KB  .....x.......x..|.....x.......x..
```
- **Einsätze gesamt:** KF 8, KB 4 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Interpunktion · **Rollen:** KF, KB
- **Harmonische Voraussetzung:** Spannungsklang (Dom7♭9, mM7)
- **Wirkung:** Akkord fragt, Bass antwortet versetzt; jede Antwort kommt ein wenig zu spät.
- **Varianten/Verdichtung:** KB-Antwort mal eine Achtel später.
- **Quellen:** S4
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R16 · Ein Schlag, dann Leere

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,20 / 0,25 / 0,35 (DRS) · **Evidenz:** Verfahren [I], Raster [E]

```
LF  x---------------|----------------|................|................
```
- **Einsätze gesamt:** LF 1 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Interpunktion · **Rollen:** LF oder KF
- **Harmonische Voraussetzung:** beliebig
- **Wirkung:** Ein Klang, der verklingt und nicht zurückkommt; die Stille danach trägt die Spannung.
- **Varianten/Verdichtung:** Leere auf drei Takte verlängern.
- **Quellen:** S7
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R17 · Zwei Schläge mit wachsendem Abstand

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,25 / 0,30 / 0,60 (DRm) · **Evidenz:** Verfahren [E], Raster [E]

```
KF  x.......x.......|....x...........|..........x.....|...............x
```
- **Einsätze gesamt:** KF 5 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Interpunktion · **Rollen:** KF oder TU
- **Harmonische Voraussetzung:** beliebig
- **Wirkung:** Die Abstände werden größer; man wartet immer länger auf den nächsten Schlag.
- **Varianten/Verdichtung:** Gegenrichtung (Abstände schrumpfen) = HE-R61.
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R18 · Unregelmäßige Tupfer

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,30 / 0,15 / 0,60 (DRm) · **Evidenz:** Verfahren [I], Raster [E]

```
TU  ......x.........|..........x.....|...x............|.............x..
```
- **Einsätze gesamt:** TU 4 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Interpunktion · **Rollen:** TU
- **Harmonische Voraussetzung:** beliebig, bevorzugt Seufzer oder Halbton
- **Wirkung:** Kein Raster erkennbar; jeder Tupfer kommt überraschend, obwohl er leise ist.
- **Varianten/Verdichtung:** Positionen pro Durchgang würfeln (keine zwei auf derselben Zählzeit).
- **Quellen:** S4
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R19 · Dritte Aussage verschoben

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 3 Takt(e) · **XYZ-Anker:** 0,25 / 0,40 / 0,70 (DmU) · **Evidenz:** Verfahren [N], Raster [E]

```
GS  x---x---x-------|x---x---x-------|........x---x---
KF  x...............|x...............|x...............
```
- **Einsätze gesamt:** GS 8, KF 3 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Interpunktion · **Rollen:** GS (Zelle), KF
- **Harmonische Voraussetzung:** statisch
- **Wirkung:** Eine Zelle erscheint zweimal regelmäßig, das dritte Mal zwei Schläge zu spät (Beginn auf Zählzeit 3); der Boden wankt.
- **Varianten/Verdichtung:** Verschiebung um eine Achtel statt um zwei Viertel.
- **Quellen:** S4
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R20 · Ostinato mit eingefügten Pausen

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,25 / 0,35 / 0,65 (DRU) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  x.x.x.x.x.x.x.x.|x.x.x.x.........|x.x.x.x.x.x.x.x.|x.x.............
```
- **Einsätze gesamt:** KF 22 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Interpunktion · **Rollen:** KF oder AR
- **Harmonische Voraussetzung:** statisch
- **Wirkung:** Der Fluss stockt unregelmäßig; das Tempo bleibt, aber das Vorankommen nicht.
- **Varianten/Verdichtung:** Pausen an andere Stellen setzen, nie zweimal gleich.
- **Quellen:** S4
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R21 · Labyrinth: Fluss und Einschnitt

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,25 / 0,50 / 0,65 (DmU) · **Evidenz:** Verfahren [N], Raster [E]

```
AR  x.x.x.x.x.x.x.x.|x.x.x.x.x.x.x.x.|x.x.x.x.x.x.x.x.|................
KF  ................|................|................|X...X...X-------
```
- **Einsätze gesamt:** AR 24, KF 3 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Interpunktion · **Rollen:** AR (Fluss), KF (Einschnitt)
- **Harmonische Voraussetzung:** Pendel, Einschnitt mit fremdem Klang
- **Wirkung:** Drei Takte Bewegung, ein Takt Schlag; ein Labyrinth ohne Ausgang.
- **Varianten/Verdichtung:** Einschnitt nach zwei statt drei Takten.
- **Quellen:** S7
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R22 · Bar-Form 2 + 2 + 4

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 8 Takt(e) · **XYZ-Anker:** 0,25 / 0,40 / 0,55 (Dmm) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  x...x.x.........|................|x...x.x.........|................|x...x.x.x...x.x.|x.x.x.x.........|x...x.x.x...x.x.|x---------------
```
- **Einsätze gesamt:** KF 23 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Form · **Rollen:** KF
- **Harmonische Voraussetzung:** a–a: Klang 1; b: Pendelklang
- **Wirkung:** Zweimal dieselbe Kurzfigur, dann eine längere Fortspinnung; Grundbaustein der Modulform.
- **Varianten/Verdichtung:** b-Teil auf zwei Takte kürzen (2 + 2 + 2).
- **Quellen:** S7, S17
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R23 · Fortschreitende Kürzung

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 6 Takt(e) · **XYZ-Anker:** 0,25 / 0,40 / 0,65 (DmU) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  x.x.x.x.x.x.x.x.|x.x.x.x.x.x.x.x.|................|x.x.x.x.x.x.....|................|x.x.x.x.........
```
- **Einsätze gesamt:** KF 26 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Form · **Rollen:** KF oder AR
- **Harmonische Voraussetzung:** beliebig
- **Wirkung:** Das Modul wird bei jeder Wiederkehr kürzer; die Pausen bleiben – Zerfall.
- **Varianten/Verdichtung:** Statt Pause einen Einzelschlag (HE-R16).
- **Quellen:** S8
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R24 · Verlängerung durch Wiederholung des Schlussglieds

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,25 / 0,40 / 0,55 (Dmm) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  x.x.x...x.x.x...|x.x.x...x.x.x...|x.x.x...x.x.x...|x.x.x...........
```
- **Einsätze gesamt:** KF 21 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Form · **Rollen:** KF
- **Harmonische Voraussetzung:** beliebig
- **Wirkung:** Das Ende kommt nicht; das letzte Glied wird immer wieder angehängt.
- **Varianten/Verdichtung:** Schlussglied einmal mehr (fünf Takte).
- **Quellen:** S7
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R25 · Dreitaktige Perioden

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 3 Takt(e) · **XYZ-Anker:** 0,20 / 0,35 / 0,50 (DRm) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  x...x...x...x...|x...x...x...x...|x...x...x-------
```
- **Einsätze gesamt:** KF 11 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Form · **Rollen:** KF
- **Harmonische Voraussetzung:** Parallelklänge (HE-H22, HE-H33)
- **Wirkung:** Unauffällig ungerade; die Erwartung einer Vierergruppe wird stets enttäuscht.
- **Varianten/Verdichtung:** Klangwechsel alle drei Takte gegen eine zweitaktige Bassperiode.
- **Quellen:** S4
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R26 · Bar-Form 4 + 4 + 4 + 1

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 13 Takt(e) · **XYZ-Anker:** 0,25 / 0,30 / 0,55 (DRm) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  x.x---x.........|x.x---x.........|x.x---x.........|x.x---x.........|x.x---x.........|x.x---x.........|x.x---x.........|x.x---x.........|x.x---x.x.x---x.|x.x---x.x.x---x.|x.x---x.x.x---x.|x.x---x.x.x---x.|x---------------
```
- **Einsätze gesamt:** KF 49 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Form · **Rollen:** KF
- **Harmonische Voraussetzung:** a, a, b (Pendelklang), Schlussklang
- **Wirkung:** Dreimal vier Takte und ein einzelner Takt; das Ende kommt zu früh.
- **Varianten/Verdichtung:** Den Schlusstakt weglassen (offenes Ende).
- **Quellen:** S17
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R27 · Wandernder Akzent

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,25 / 0,35 / 0,70 (DRU) · **Evidenz:** Verfahren [I], Raster [E]

```
KF  X.x.x.x.x.x.x.x.|x.X.x.x.x.x.x.x.|x.x.X.x.x.x.x.x.|x.x.x.X.x.x.x.x.
```
- **Einsätze gesamt:** KF 32 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Akzent · **Rollen:** KF
- **Harmonische Voraussetzung:** statisch
- **Wirkung:** Gleicher Fluss, aber der Schwerpunkt rückt jeden Takt eine Achtel weiter.
- **Varianten/Verdichtung:** Akzent wandert in Dreierschritten (1, 4, 7 …).
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R28 · Achtel in 3 + 3 + 2 und 3 + 2 + 3

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,30 / 0,45 / 0,70 (DmU) · **Evidenz:** Verfahren [E], Raster [E]

```
KF  X.x.x.X.x.x.X.x.|X.x.x.X.x.X.x.x.
```
- **Einsätze gesamt:** KF 16 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Akzent · **Rollen:** KF oder AR
- **Harmonische Voraussetzung:** statisch
- **Wirkung:** Asymmetrische Akzente im geraden Takt; Unruhe ohne Taktwechsel.
- **Varianten/Verdichtung:** Zweiter Takt als 2 + 3 + 3.
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R29 · Drei Viertel gegen vier Viertel

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 3 Takt(e) · **XYZ-Anker:** 0,20 / 0,40 / 0,70 (DmU) · **Evidenz:** Verfahren [I], Raster [E]

```
KF  x...x...x...x...|x...x...x...x...|x...x...x...x...
KB  x.......x...x...|....x...x.......|x...x.......x...
```
- **Einsätze gesamt:** KF 12, KB 8 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Schichtung · **Rollen:** KF, KB
- **Harmonische Voraussetzung:** statisch
- **Wirkung:** Zwei Ostinati mit verschiedenen Zykluslängen; erst nach drei Takten fallen ihre Anfänge wieder zusammen.
- **Varianten/Verdichtung:** KB-Zyklus auf fünf Viertel verlängern.
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt
- **Technische Anforderungen:** Unabhängige rhythmische Zyklen

#### HE-R30 · Fünfer-Zelle im Sechzehntelraster

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 5 Takt(e) · **XYZ-Anker:** 0,30 / 0,40 / 0,75 (DmU) · **Evidenz:** Verfahren [E], Raster [E]

```
AR  x.x..x.x..x.x..x|.x..x.x..x.x..x.|x..x.x..x.x..x.x|..x.x..x.x..x.x.|.x.x..x.x..x.x..
```
- **Einsätze gesamt:** AR 32 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Schichtung · **Rollen:** AR
- **Harmonische Voraussetzung:** statisch
- **Wirkung:** Eine fünfschrittige Zelle verschiebt sich gegen den Takt und kehrt erst nach fünf Takten zurück.
- **Varianten/Verdichtung:** Nur die ersten zwei Takte, dann neu ansetzen.
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt
- **Technische Anforderungen:** Unabhängige rhythmische Zyklen

#### HE-R31 · Fünfvierteltakt, lahmend

- **Taktart:** 5/4 (20 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,25 / 0,30 / 0,60 (DRm) · **Evidenz:** Verfahren [E], Raster [E]

```
KF  x...x...x.......x...|x...x...x.......x...
KB  x...................|x.......x...........
```
- **Einsätze gesamt:** KF 8, KB 3 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Akzent · **Rollen:** KF, KB
- **Harmonische Voraussetzung:** statisch
- **Wirkung:** Ein Schritt fehlt in jeder Gruppe; schleppend, behindert.
- **Varianten/Verdichtung:** KB-Einsatz in Takt 2 auf Zählzeit 4.
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R32 · Lang gegen kurz im Wechsel

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,25 / 0,35 / 0,55 (DRm) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  x---x---x---x---|x.x.x.x.x.x.x.x.|x---x---x---x---|x.x.x.x.x.x.x.x.
```
- **Einsätze gesamt:** KF 24 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Artikulation · **Rollen:** KF
- **Harmonische Voraussetzung:** gleicher Klang
- **Wirkung:** Gleicher Rhythmus der Schwerpunkte, wechselnde Notenlänge (gehalten ↔ kurz). Ob kurz als gezupft erklingt, entscheidet die Instrumentenwahl, nicht die Vorlage.
- **Varianten/Verdichtung:** Kurze Takte nur in jedem dritten Takt.
- **Quellen:** S12
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R33 · Gegenrhythmus im Bass

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,15 / 0,65 / 0,80 (DIU) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  x.x.x.x.x.x.x.x.|x.x.x.x.x.x.x.x.
KB  ..x...x.x.....x.|...x....x...x...
```
- **Einsätze gesamt:** KF 16, KB 7 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Schichtung · **Rollen:** KF, KB
- **Harmonische Voraussetzung:** Tritonus- oder Clusterklang
- **Wirkung:** Gleichmäßige Oberstimmen, versetzte Basseinsätze; die Erde bebt unter einem gleichmäßigen Gang.
- **Varianten/Verdichtung:** KB in Oktaven beginnen, im Tritonus enden (HE-B12).
- **Quellen:** S4
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R34 · Homorhythmik, dann Störung

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,25 / 0,45 / 0,65 (DmU) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  x...x...x...x...|x...x...x...x...|x...x...x...x...|x...x...x...x...
KB  x...x...x...x...|x...x...x...x...|x..x..x..x..x...|.x..x..x..x..x..
```
- **Einsätze gesamt:** KF 16, KB 18 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Schichtung · **Rollen:** KF, KB
- **Harmonische Voraussetzung:** statisch
- **Wirkung:** Alle gehen im Gleichschritt, bis der Bass aus der Reihe fällt.
- **Varianten/Verdichtung:** Störung schon ab Takt 2.
- **Quellen:** S4
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R35 · Leere Takte

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,20 / 0,10 / 0,45 (DRm) · **Evidenz:** Verfahren [I], Raster [E]

```
LF  x---------------|--------........|................|................
TU  ................|................|................|..........x.....
```
- **Einsätze gesamt:** LF 1, TU 1 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Leere · **Rollen:** LF, TU
- **Harmonische Voraussetzung:** beliebig
- **Wirkung:** Ein Klang, eine Stille, ein einzelner Tropfen; die Szene hält den Atem an.
- **Varianten/Verdichtung:** TU in Takt 3 statt 4.
- **Quellen:** S4
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R36 · Repetition auf dem Pedalton

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,40 / 0,15 / 0,40 (mRm) · **Evidenz:** Verfahren [N], Raster [E]

```
TU  x...x...x...x...|x...x...x...x...
```
- **Einsätze gesamt:** TU 8 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Bewegung · **Rollen:** TU (Vibraphon-, Glockenspielfunktion)
- **Harmonische Voraussetzung:** Pedalton = gemeinsamer Ton der Klänge
- **Wirkung:** Ein einziger heller Ton wiederholt sich gleichmäßig über allem; Bann, Gefangensein.
- **Varianten/Verdichtung:** Halbe statt Viertel; oder jede vierte Viertel auslassen.
- **Quellen:** S12, S9
- **Färbungsbereich:** alle X: in hellem Kontext Hochlage (Glockenfunktion), in dunklem Mittellage

#### HE-R37 · Lebloser Tanz auf einem Ton

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,25 / 0,20 / 0,45 (DRm) · **Evidenz:** Verfahren [N], Raster [E]

```
AR  x..xx.x.x..xx.x.|x..xx.x.x..xx.x.
LB  x---------------|----------------
```
- **Einsätze gesamt:** AR 16, LB 1 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Bewegung · **Rollen:** AR (auf einem Ton), LB
- **Harmonische Voraussetzung:** Pedal
- **Wirkung:** Ein Tanzrhythmus ohne Melodie auf einem einzigen Ton; Erinnerung an Leben, ohne Leben.
- **Varianten/Verdichtung:** AR eine Oktave höher, sehr leise.
- **Quellen:** S12, S9
- **Färbungsbereich:** X ≤ 0,6 (Tanz ohne Leben verliert in hellem Kontext seine Schwere)

#### HE-R38 · Müder Dreiertakt

- **Taktart:** 3/4 (12 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,25 / 0,20 / 0,45 (DRm) · **Evidenz:** Verfahren [E], Raster [E]

```
KB  x...........|x...........
KF  ....x...x...|....x...x...
```
- **Einsätze gesamt:** KB 2, KF 4 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Bewegung · **Rollen:** KB, KF
- **Harmonische Voraussetzung:** halbvermindert, mM7
- **Wirkung:** Ein Walzer ohne Schwung; jeder Takt beginnt mit einem schweren Bass, danach zwei müde Akkorde.
- **Varianten/Verdichtung:** KF nur auf Zählzeit 2.
- **Färbungsbereich:** X ≤ 0,6

#### HE-R39 · Verdichtung bei gleichen Schwerpunkten

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,25 / 0,55 / 0,70 (DmU) · **Evidenz:** Verfahren [I], Raster [E]

```
KF  X.......X.......|X...x...X...x...|X.x.x.x.X.x.x.x.|XxxxxxxxXxxxxxxx
```
- **Einsätze gesamt:** KF 30 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Prozess · **Rollen:** KF oder AR
- **Harmonische Voraussetzung:** statisch oder langsamer Wechsel
- **Wirkung:** Die Schwerpunkte bleiben, die Zwischenräume füllen sich; Druck wächst, ohne lauter zu werden.
- **Varianten/Verdichtung:** Erst ab Takt 3 verdichten; Velocity konstant lassen.
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R40 · Ausdünnung

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,25 / 0,30 / 0,45 (DRm) · **Evidenz:** Verfahren [I], Raster [E]

```
KF  x.x.x.x.x.x.x.x.|x...x...x...x...|x.......x.......|x...............
```
- **Einsätze gesamt:** KF 15 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Prozess · **Rollen:** KF oder AR
- **Harmonische Voraussetzung:** beliebig
- **Wirkung:** Der Fluss erstarrt; Spannung bleibt, weil der Klang bleibt.
- **Varianten/Verdichtung:** Ausdünnen nur in einer Rolle, andere bleiben.
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R41 · Alle Schichten synchron

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,10 / 0,85 / 0,35 (DIS) · **Evidenz:** Verfahren [N], Raster [E]

```
LF  X-------X-------|X---------------
KF  X-------X-------|X---------------
KB  X-------X-------|X---------------
```
- **Einsätze gesamt:** LF 3, KF 3, KB 3 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Schichtung · **Rollen:** LF, KF, KB
- **Harmonische Voraussetzung:** Polychord, Mauer, Cluster
- **Wirkung:** Verschmelzung: alle Rollen setzen gemeinsam ein und halten gemeinsam; Wucht.
- **Varianten/Verdichtung:** Nur zwei Schläge im zweiten Takt (X...X...........).
- **Quellen:** S1
- **Färbungsbereich:** alle X: tief und eng = dunkle Mauer, hoch und weit = helle Säule
- **Technische Anforderungen:** Lange Noten in Kurzrolle

#### HE-R42 · Komplementärschichten

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,25 / 0,25 / 0,60 (DRm) · **Evidenz:** Verfahren [I], Raster [E]

```
KF  x.......x.......|x.......x.......
AR  ..x.......x.....|..x.......x.....
TU  .....x.......x..|.....x.......x..
```
- **Einsätze gesamt:** KF 4, AR 4, TU 4 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Schichtung · **Rollen:** KF, AR, TU
- **Harmonische Voraussetzung:** Polychord getrennt
- **Wirkung:** Drei Schichten setzen nie gleichzeitig ein; der Klang zerfällt in Einzelteile.
- **Varianten/Verdichtung:** Eine Rolle aussetzen lassen (Lücke).
- **Quellen:** S1
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R43 · Kanonische Einsätze im Viertaktabstand

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 8 Takt(e) · **XYZ-Anker:** 0,20 / 0,45 / 0,65 (DmU) · **Evidenz:** Verfahren [N], Raster [E]

```
KB  x.x.x.x.x...x...|x.x.x.x.x...x...|x.x.x.x.x...x...|x.x.x.x.x...x...|x.x.x.x.x...x...|x.x.x.x.x...x...|x.x.x.x.x...x...|x.x.x.x.x...x...
GS  ................|................|................|................|x.x.x.x.x...x...|x.x.x.x.x...x...|x.x.x.x.x...x...|x.x.x.x.x...x...
```
- **Einsätze gesamt:** KB 48, GS 24 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Schichtung · **Rollen:** KB, GS (später AR, HM)
- **Harmonische Voraussetzung:** statisch, chromatisch
- **Wirkung:** Eine Stimme nach der anderen nimmt dieselbe Figur auf; der Raum füllt sich unaufhaltsam.
- **Varianten/Verdichtung:** Dritter Einsatz einen Takt früher (HE-R44).
- **Quellen:** S4
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt
- **Technische Anforderungen:** Kanon/koordinierte Parallelstimmen

#### HE-R44 · Einsatz einen Takt zu früh

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 8 Takt(e) · **XYZ-Anker:** 0,20 / 0,50 / 0,70 (DmU) · **Evidenz:** Verfahren [N], Raster [E]

```
KB  x.x.x...x.x.x...|x.x.x...x.x.x...|x.x.x...x.x.x...|x.x.x...x.x.x...|x.x.x...x.x.x...|x.x.x...x.x.x...|x.x.x...x.x.x...|x.x.x...x.x.x...
GS  ................|................|................|................|x.x.x...x.x.x...|x.x.x...x.x.x...|x.x.x...x.x.x...|x.x.x...x.x.x...
AR  ................|................|................|................|................|................|................|x.x.x...x.x.x...
```
- **Einsätze gesamt:** KB 48, GS 24, AR 6 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Schichtung · **Rollen:** KB, GS, AR
- **Harmonische Voraussetzung:** statisch
- **Wirkung:** Die Abstände der Einsätze schrumpfen; die Musik wird ungeduldig.
- **Varianten/Verdichtung:** Einsätze 4 – 3 – 2 Takte.
- **Quellen:** S4
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt
- **Technische Anforderungen:** Kanon/koordinierte Parallelstimmen

#### HE-R45 · Leise Repetition in Sechzehnteln

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,20 / 0,35 / 0,70 (DRU) · **Evidenz:** Verfahren [I], Raster [E]

```
KF  xxxxxxxxxxxxxxxx|xxxxxxxxxxxxxxxx
```
- **Einsätze gesamt:** KF 32 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Bewegung · **Rollen:** KF
- **Harmonische Voraussetzung:** Liegeklang
- **Wirkung:** Zitternde Fläche; Unruhe in der Fläche selbst.
- **Varianten/Verdichtung:** Nur in einer Lage (eine Stimme) statt Akkord.
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R46 · Seufzerpaare

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,25 / 0,20 / 0,40 (DRm) · **Evidenz:** Verfahren [N], Raster [E]

```
GS  X-x.....X-x.....|X-x.............
```
- **Einsätze gesamt:** GS 6 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Interpunktion · **Rollen:** GS, TU, KF
- **Harmonische Voraussetzung:** Halbton abwärts über Klang
- **Wirkung:** Betont–unbetont, lang–kurz; Klage ohne Melodie.
- **Varianten/Verdichtung:** Zweites Paar auslassen.
- **Quellen:** S3
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R47 · Halbtonpendel über Schlagwerkpuls

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,30 / 0,35 / 0,65 (DRU) · **Evidenz:** Verfahren [N], Raster [E]

```
TU  x.x.....x.x.....|x.x.....x.x.....
KB  x.x.x.x.x.x.x.x.|x.x.x.x.x.x.x.x.
```
- **Einsätze gesamt:** TU 8, KB 16 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Bewegung · **Rollen:** TU, KB
- **Harmonische Voraussetzung:** statisch, Halbtonzelle
- **Wirkung:** Ein unpersönlicher Puls, darüber ein zuckendes Halbtonpendel; fremde Intelligenz.
- **Varianten/Verdichtung:** KB ohne Tonhöhe (Stich) – nur wenn ein Schlagwerk-Trigger vorgesehen ist.
- **Quellen:** S13
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R48 · Freie Zellen über gleichmäßigem Bass

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,30 / 0,35 / 0,60 (DRm) · **Evidenz:** Verfahren [N], Raster [E]

```
KB  x.x.x.x.x.x.x.x.|x.x.x.x.x.x.x.x.|x.x.x.x.x.x.x.x.|x.x.x.x.x.x.x.x.
GS  x---x-----......|................|......x---x-----|................
```
- **Einsätze gesamt:** KB 32, GS 4 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Bewegung · **Rollen:** KB, GS
- **Harmonische Voraussetzung:** statisch
- **Wirkung:** Der Bass läuft, eine Linie setzt in unregelmäßigen Abständen mit einer Zweitonzelle ein.
- **Varianten/Verdichtung:** Zellen der GS an wechselnden Stellen.
- **Quellen:** S13
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R49 · Ein Stich nach langem Aufbau

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 8 Takt(e) · **XYZ-Anker:** 0,20 / 0,50 / 0,55 (Dmm) · **Evidenz:** Verfahren [I], Raster [E]

```
ST  ................|................|................|................|................|................|................|........X.......
KF  x...............|x...............|x...............|x...............|x...............|x...............|x...x...x...x...|x...x...........
```
- **Einsätze gesamt:** ST 1, KF 12 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Interpunktion · **Rollen:** ST, KF
- **Harmonische Voraussetzung:** beliebig
- **Wirkung:** Sieben Takte Spannung, dann ein einziger Stich auf das Ereignis; Stiche sind selten und ereignisgebunden.
- **Varianten/Verdichtung:** Stich ganz weglassen – die Erwartung trägt.
- **Quellen:** S1
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R50 · Stich mit Nachhall-Leere

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,15 / 0,80 / 0,60 (DIm) · **Evidenz:** Verfahren [I], Raster [E]

```
ST  X...............|................
LF  X---------------|--------........
```
- **Einsätze gesamt:** ST 1, LF 1 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Interpunktion · **Rollen:** ST, LF
- **Harmonische Voraussetzung:** Polychord verschmolzen
- **Wirkung:** Schreck und danach nichts; die Leere nach dem Stich ist Teil des Stichs.
- **Varianten/Verdichtung:** LF erst eine Viertel nach dem Stich.
- **Quellen:** S1
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R51 · Kaskade von oben nach unten

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,15 / 0,90 / 0,70 (DIU) · **Evidenz:** Verfahren [N], Raster [E]

```
TU  X---------------|--------........
AR  ..X-------------|--------........
KF  ....X-----------|--------........
KB  ......X---------|--------........
```
- **Einsätze gesamt:** TU 1, AR 1, KF 1, KB 1 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Interpunktion · **Rollen:** TU, AR, KF, KB
- **Harmonische Voraussetzung:** Cluster aus großen Septimen
- **Wirkung:** Ein Klang wird von oben nach unten aufgebaut; jeder neue Ton tiefer als der letzte.
- **Varianten/Verdichtung:** Abstände Sechzehntel statt Achtel.
- **Quellen:** S4
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt
- **Technische Anforderungen:** Lange Noten in Kurzrolle

#### HE-R52 · Kaskade aufwärts

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,20 / 0,60 / 0,65 (DmU) · **Evidenz:** Verfahren [N], Raster [E]

```
KB  x---------------|--------........
KF  ..x-------------|--------........
AR  ....x-----------|--------........
TU  ......x---------|--------........
```
- **Einsätze gesamt:** KB 1, KF 1, AR 1, TU 1 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Interpunktion · **Rollen:** KB, KF, AR, TU
- **Harmonische Voraussetzung:** verminderte Klänge
- **Wirkung:** Klangmasse wächst von unten; wie Treppensteigen ins Ungewisse.
- **Varianten/Verdichtung:** Nur drei Rollen.
- **Quellen:** S3
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt
- **Technische Anforderungen:** Lange Noten in Kurzrolle

#### HE-R53 · Rollenwanderung

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 6 Takt(e) · **XYZ-Anker:** 0,25 / 0,30 / 0,60 (DRm) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  x.x---x.x...x.x.|x.x---x.x...x.x.|................|................|................|................
AR  ................|................|x.x---x.x...x.x.|x.x---x.x...x.x.|................|................
KB  ................|................|................|................|x.x---x.x...x.x.|x.x---x.x...x.x.
```
- **Einsätze gesamt:** KF 12, AR 12, KB 12 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Prozess · **Rollen:** KF → AR → KB
- **Harmonische Voraussetzung:** gleicher Klang oder Pendel
- **Wirkung:** Derselbe Rhythmus zieht von Rolle zu Rolle; Farbe und Lage wandern, der Bann bleibt.
- **Varianten/Verdichtung:** Kürzere Notenlängen in der dritten Station.
- **Quellen:** S12
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt
- **Technische Anforderungen:** Rollenwanderung

#### HE-R54 · Atemrhythmus der Fläche

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,40 / 0,25 / 0,25 (mRS) · **Evidenz:** Verfahren [E], Raster [E]

```
LF  x---------------|----x-----------
```
- **Einsätze gesamt:** LF 2 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Bewegung · **Rollen:** LF
- **Harmonische Voraussetzung:** langsamer Klangwechsel
- **Wirkung:** Die Fläche setzt ungleichmäßig neu an (fünf + drei Viertel); ruhig, aber nicht regelmäßig.
- **Varianten/Verdichtung:** Neuansatz eine Viertel später.
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R55 · Kurze Flackerstöße

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,45 / 0,25 / 0,70 (mRU) · **Evidenz:** Verfahren [E], Raster [E]

```
TU  xxxx............|........xxxx....
```
- **Einsätze gesamt:** TU 8 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Interpunktion · **Rollen:** TU
- **Harmonische Voraussetzung:** hoher Klang
- **Wirkung:** Zwischen langen Pausen zuckt etwas auf; nervöse Helligkeit.
- **Varianten/Verdichtung:** Stöße mal drei, mal fünf Sechzehntel.
- **Färbungsbereich:** X ≥ 0,4 (Hochlage)

#### HE-R56 · Düsteres Wiegen

- **Taktart:** 6/8 (12 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,25 / 0,20 / 0,35 (DRS) · **Evidenz:** Verfahren [E], Raster [E]

```
KB  x.....x.....|x.....x.....
TU  ....x.......|....x.......
```
- **Einsätze gesamt:** KB 4, TU 2 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Bewegung · **Rollen:** KB, TU
- **Harmonische Voraussetzung:** mM7, Moll
- **Wirkung:** Wiegen ohne Trost; der Tupfer kommt immer ein wenig zu früh.
- **Varianten/Verdichtung:** TU auf der zweiten Gruppe statt der ersten.
- **Färbungsbereich:** X ≤ 0,6

#### HE-R57 · Hemiolenwechsel 3/4 ↔ 6/8

- **Taktart:** 3/4 (12 Schritte/Takt) · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,40 / 0,60 / 0,85 (mmU) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  X.x.X.x.X.x.|X.x.x.X.x.x.|X.x.x.X.x.x.|X.x.X.x.X.x.
```
- **Einsätze gesamt:** KF 24 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Akzent · **Rollen:** KF
- **Harmonische Voraussetzung:** beliebig
- **Wirkung:** Gleichmäßige Achtel; die Akzente wechseln taktweise zwischen drei Halben (3/4) und zwei punktierten Vierteln (6/8). Der Dreiertakt wird ständig umgedeutet, ohne dass Tempo oder Dichte sich ändern.
- **Varianten/Verdichtung:** Reihenfolge der Takte permutieren.
- **Quellen:** S18
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R58 · Sehr langsamer Puls mit Lücke

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,20 / 0,10 / 0,35 (DRS) · **Evidenz:** Verfahren [E], Raster [E]

```
LF  x-------x-------|x-------........|x-------x-------|........x-------
```
- **Einsätze gesamt:** LF 6 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Leere · **Rollen:** LF oder LB
- **Harmonische Voraussetzung:** beliebig
- **Wirkung:** Halbe Noten, die einmal ausbleiben; fast nichts geschieht, und genau das beunruhigt.
- **Varianten/Verdichtung:** Lücke in einem anderen Takt.
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R59 · Neuansatz nur auf unbetonter Zeit

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,25 / 0,15 / 0,50 (DRm) · **Evidenz:** Verfahren [E], Raster [E]

```
LF  ......x---------|------x---------
```
- **Einsätze gesamt:** LF 2 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Leere · **Rollen:** LF
- **Harmonische Voraussetzung:** beliebig
- **Wirkung:** Die Fläche setzt nie auf der Eins ein; der Boden fehlt, ohne dass etwas laut wird.
- **Varianten/Verdichtung:** Neuansatz auf 4+.
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R60 · Rhythmische Frage und versetzte Antwort

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,25 / 0,30 / 0,60 (DRm) · **Evidenz:** Verfahren [N], Raster [E]

```
KF  x.x.............|................|x.x.............|................
KB  ......x.x.......|................|.........x......|................
```
- **Einsätze gesamt:** KF 4, KB 3 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Interpunktion · **Rollen:** KF, KB
- **Harmonische Voraussetzung:** beliebig
- **Wirkung:** Zwei Schläge fragen, zwei antworten; die zweite Antwort ist kürzer und später.
- **Varianten/Verdichtung:** Antwort im dritten Durchgang ausfallen lassen.
- **Quellen:** S4
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R61 · Schrumpfende Abstände

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,25 / 0,55 / 0,70 (DmU) · **Evidenz:** Verfahren [E], Raster [E]

```
KF  x.......x.......|x.....x.....x...|..x...x...x...x.|..x..x..x.x.x.x.
```
- **Einsätze gesamt:** KF 15 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Prozess · **Rollen:** KF oder KB
- **Harmonische Voraussetzung:** beliebig
- **Wirkung:** Die Schläge rücken zusammen; Beschleunigung ohne Tempoänderung.
- **Varianten/Verdichtung:** Velocity gleich lassen: die Beschleunigung allein steigert.
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R62 · Wachsende Abstände

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,25 / 0,30 / 0,45 (DRm) · **Evidenz:** Verfahren [E], Raster [E]

```
KF  x.x.x.x.x..x..x.|..x...x.....x...|....x...........|x...............
```
- **Einsätze gesamt:** KF 12 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Prozess · **Rollen:** KF
- **Harmonische Voraussetzung:** beliebig
- **Wirkung:** Die Bewegung verlangsamt sich, ohne dass das Tempo sinkt; etwas kommt zum Stehen und lauert.
- **Varianten/Verdichtung:** Letzter Schlag als Stich.
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt

#### HE-R63 · Fünf-Achtel-Figur

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 5 Takt(e) · **XYZ-Anker:** 0,30 / 0,40 / 0,65 (DmU) · **Evidenz:** Verfahren [N], Raster [E]

```
AR  x.x.x.x.x.x.x.x.|x.x.x.x.x.x.x.x.|x.x.x.x.x.x.x.x.|x.x.x.x.x.x.x.x.|x.x.x.x.x.x.x.x.
```
- **Einsätze gesamt:** AR 40 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Schichtung · **Rollen:** AR (Töne in Fünfergruppe)
- **Harmonische Voraussetzung:** statisch
- **Wirkung:** Gleichmäßiger Achtelfluss, dessen Tonmuster sich gegen den Takt verschiebt; die Unruhe liegt in den Tönen, nicht im Raster.
- **Varianten/Verdichtung:** Raster bleibt gleich; die Tonfolge wiederholt sich alle fünf Achtel (siehe HE-M18).
- **Quellen:** S8
- **Färbungsbereich:** färbungsunabhängig – X wird über Harmonik und Lage gewählt
- **Technische Anforderungen:** Unabhängige rhythmische Zyklen

#### HE-R64 · Glasige Repetitionspaare in Hochlage

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,65 / 0,15 / 0,55 (HRm) · **Evidenz:** Verfahren [I], Raster [E]

```
TU  x.x.......x.x...|....x.x.........
```
- **Einsätze gesamt:** TU 6 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Interpunktion · **Rollen:** TU (hohe Lage), auch AR
- **Harmonische Voraussetzung:** heller Klang, Liegeton oder Hochpedal
- **Wirkung:** Zwei schnelle gleiche Töne, dann lange nichts, dann wieder zwei an anderer Stelle: ein Signal ohne Absender. Hell, leise, kalt.
- **Varianten/Verdichtung:** Paare zu Dreiergruppen verlängern (x.x.x).
- **Quellen:** S1
- **Färbungsbereich:** X ≥ 0,4 (Hochlage)

#### HE-R65 · Schwebende Triolen über langer Fläche

- **Taktart:** 4/4T (12 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,60 / 0,30 / 0,70 (mRU) · **Evidenz:** Verfahren [I], Raster [E]

```
AR  x.xx.xx.x...|..x.xx.xx.x.
LF  x-----------|------------
```
- **Einsätze gesamt:** AR 12, LF 1 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Bewegung · **Rollen:** AR, LF
- **Harmonische Voraussetzung:** Ganzton- oder übermäßiger Klang
- **Wirkung:** Unregelmäßig gefüllte Triolen, deren Lücken jeden Takt wandern, über einer stehenden Fläche; Schweben mit Herzklopfen.
- **Varianten/Verdichtung:** AR eine Oktave höher; LF weglassen (bodenlos).
- **Quellen:** S6, S5
- **Färbungsbereich:** X ≥ 0,4

#### HE-R66 · Säule mit spätem Nachschlag

- **Taktart:** 4/4 (16 Schritte/Takt) · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,30 / 0,80 / 0,25 (DIS) · **Evidenz:** Verfahren [I], Raster [E]

```
LF  X---------------|----------------
LB  X---------------|----------------
KF  ................|..........x-----
```
- **Einsätze gesamt:** LF 1, LB 1, KF 1 · Dauern ergeben sich aus `-`, Pausen aus `.`, Akzente aus `X`.
- **Modultyp:** Schichtung · **Rollen:** LF, LB, KF
- **Harmonische Voraussetzung:** Mauer, Polychord, Säulenklang
- **Wirkung:** Ein langer, lauter Klang, in dessen Ausklingen ein einziger später Anschlag fällt; Wucht ohne Bewegung, kraftvoll und ruhig.
- **Varianten/Verdichtung:** Nachschlag auslassen (reine Säule).
- **Quellen:** S15, S1
- **Färbungsbereich:** alle X: tief und eng = dunkle Mauer, hoch und weit = helle Säule
- **Technische Anforderungen:** Lange Noten in Kurzrolle

## E Bassvokabular (HE-B01–B45)

Grundregister R = C2–B2. Feste Töne sind absolut notiert. Bei Pedalen ist die Beziehung zum Oberklang wichtiger als der Ton selbst; beim Transponieren der Harmonik werden `P(x)`-Töne mitverschoben, damit die Beziehung (Tritonus, Halbton) erhalten bleibt.

#### HE-B01 · Langes Pedal, ohne Neuansatz

- **Taktart:** 4/4 · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,20 / 0,15 / 0,30 (DRS) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  x---------------|----------------|----------------|----------------
Töne  P(C2)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** liegt unter allen Klängen; Beziehung zum Oberklang wechselt
- **Akkordwechsel:** ignoriert Akkordwechsel
- **Artikulation:** legato, pp–p
- **Wirkung:** Bann, Stillstand; der Boden hält, obwohl oben alles wandert.
- **Kombination:** HE-H44, HE-H64; LF, TU
- **Quellen:** S5
- **Färbungsbereich:** alle X
- **Tonfunktionen** (gegen HE-H44, je Einsatz): C2 A · Zusammenfassung: Akkordton 1
- **Technische Anforderungen:** Pedal über Akkordwechsel

#### HE-B02 · Tritonuspedal

- **Taktart:** 4/4 · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,15 / 0,20 / 0,65 (DRU) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  x---------------|----------------|----------------|----------------
Töne  P(F#1)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Tritonus zum Grundton des Oberklangs (C)
- **Akkordwechsel:** bleibt
- **Artikulation:** legato, sehr leise
- **Wirkung:** Haltlosigkeit unter ruhigem Klang.
- **Kombination:** HE-H05, HE-H66; LF
- **Quellen:** S1, S4
- **Färbungsbereich:** eher X ≤ 0,6; in hellen Kontexten leiser oder eine Oktave höher
- **Tonfunktionen** (gegen HE-H05, je Einsatz): F♯1 A · Zusammenfassung: Akkordton 1
- **Technische Anforderungen:** Pedal über Akkordwechsel

#### HE-B03 · Halbtonpedal über dem Grundton

- **Taktart:** 4/4 · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,15 / 0,25 / 0,65 (DRU) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  x---------------|----------------|----------------|----------------
Töne  P(Db1)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** kleine None bzw. kleine Sekunde zum Grundton C
- **Akkordwechsel:** bleibt
- **Artikulation:** legato
- **Wirkung:** Ein Klang, dem der Boden nicht passt.
- **Kombination:** HE-H18, HE-H67; LF, TU
- **Quellen:** S5
- **Färbungsbereich:** eher X ≤ 0,6; in hellen Kontexten leiser oder eine Oktave höher
- **Tonfunktionen** (gegen HE-H18, je Einsatz): D♭1 A · Zusammenfassung: Akkordton 1
- **Technische Anforderungen:** Pedal über Akkordwechsel

#### HE-B04 · Doppelpedal im None-Abstand

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,20 / 0,30 / 0,50 (DRm) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  x...x...x...x...|x...x...x...x...
Töne  P(F2)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** mit gehaltenem E1 darunter (zweite Spur LB); E und F reiben dauerhaft
- **Akkordwechsel:** bleibt
- **Artikulation:** KB kurz (Viertel, Abstrich), LB gehalten
- **Wirkung:** Mechanischer, kalter Puls über festgefrorenem Grund.
- **Kombination:** HE-H65, HE-R04; LB + KB
- **Quellen:** S4
- **Färbungsbereich:** alle X
- **Tonfunktionen** (gegen HE-H65, je Einsatz): F2 A · F2 A · F2 A · F2 A · F2 A · F2 A · F2 A · F2 A · Zusammenfassung: Akkordton 8
- **Technische Anforderungen:** Mehrstimmiger Bass

#### HE-B05 · Pedal mit seltenem Neuansatz auf unbetonter Zeit

- **Taktart:** 4/4 · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,20 / 0,15 / 0,50 (DRm) · **Evidenz:** Verfahren [E], Vorlage [E]

```
Bass  ......x---------|----------------|----------------|..........x-----
Töne  P(C2)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Pedal
- **Akkordwechsel:** bleibt
- **Artikulation:** legato, Neuansatz ohne Akzent
- **Wirkung:** Der Boden kommt immer etwas zu spät.
- **Kombination:** HE-H01, HE-R59
- **Färbungsbereich:** alle X
- **Tonfunktionen** (gegen HE-H01, je Einsatz): C2 A · C2 A · Zusammenfassung: Akkordton 2
- **Technische Anforderungen:** Pedal über Akkordwechsel

#### HE-B06 · Tief- und Hochpedal

- **Taktart:** 4/4 · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,45 / 0,20 / 0,50 (mRm) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  x---------------|----------------|----------------|----------------
Töne  P(C1)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** zusammen mit C6 (TU oder LF, gehalten); Mittelklang wechselt
- **Akkordwechsel:** bleibt
- **Artikulation:** legato, gleich leise
- **Wirkung:** Rahmen aus zwei gleichen Tönen; was dazwischen liegt, wirkt gefangen.
- **Kombination:** HE-H56, HE-H69
- **Quellen:** S1
- **Färbungsbereich:** eher X ≤ 0,6; in hellen Kontexten leiser oder eine Oktave höher
- **Tonfunktionen** (gegen HE-H56, je Einsatz): C1 A · Zusammenfassung: Akkordton 1
- **Technische Anforderungen:** Mehrstimmiger Bass, Pedal über Akkordwechsel

#### HE-B07 · Fallender Bass unter festem Ton bis zum Tritonus

- **Taktart:** 4/4 · **Länge:** 8 Takt(e) · **XYZ-Anker:** 0,25 / 0,25 / 0,55 (DRm) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  x---------------|----------------|x---------------|----------------|x---------------|----------------|x---------------|----------------
Töne  P(C2) P(B1) P(Bb1) P(Bb1)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** oberer Liegeton E bleibt (Konsonanz → Tritonus)
- **Akkordwechsel:** fällt alle zwei Takte
- **Artikulation:** legato
- **Wirkung:** Der Boden sinkt langsam weg.
- **Kombination:** HE-H70, HE-H07
- **Quellen:** S5
- **Färbungsbereich:** eher X ≤ 0,6; in hellen Kontexten leiser oder eine Oktave höher
- **Tonfunktionen** (gegen HE-H70, je Einsatz): C2 A · B1 A · B♭1 A · B♭1 A · Zusammenfassung: Akkordton 4
- **Technische Anforderungen:** Pedal über Akkordwechsel

#### HE-B08 · Steigender chromatischer Bass gegen fallende Oberstimme

- **Taktart:** 4/4 · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,20 / 0,40 / 0,55 (Dmm) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  x-------x-------|x-------x-------|x-------x-------|x-------x-------
Töne  P(G1) P(G#1) P(A1) P(Bb1) P(B1) P(C2) P(C#2) P(D2)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Gegenbewegung zu GS (absteigend chromatisch), Konvergenz auf mM7
- **Akkordwechsel:** eigenständig, Halbe
- **Artikulation:** legato, Seufzer umgekehrt
- **Wirkung:** Zwei Linien rücken aufeinander zu; die Begegnung ist unausweichlich.
- **Kombination:** HE-M32, HE-S05
- **Quellen:** S3
- **Färbungsbereich:** eher X ≤ 0,6; in hellen Kontexten leiser oder eine Oktave höher
- **Tonfunktionen:** relativ zum Akkord (Grundton, Terz, Quinte, Oktave) – Akkordtöne

#### HE-B09 · Chromatische Tritonusbewegung

- **Taktart:** 4/4 · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,15 / 0,50 / 0,55 (Dmm) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  x---x---x---x---|x---x---x---x---|x---x---x---x---|x---x---x---x---
Töne  P(C2) P(C#2) P(D2) P(D#2) P(E2) P(F2) P(F#2) P(F#2) P(F2) P(E2) P(Eb2) P(D2) P(C#2) P(C2) P(C2) P(C2)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** durchmisst den Tritonus und kehrt zurück
- **Akkordwechsel:** eigenständig, Viertel
- **Artikulation:** tenuto
- **Wirkung:** Ein Riese, der schrittweise näherkommt und wieder weicht.
- **Kombination:** HE-H79, HE-R09
- **Quellen:** S13
- **Färbungsbereich:** alle X
- **Tonfunktionen** (gegen HE-H79, je Einsatz): C2 A · D♭2 F · D2 V→E♭2 · E♭2 A · E2 F · F2 F · F♯2 F · F♯2 F · F2 F · E2 F · E♭2 F · D2 V→D♭2 · D♭2 A · C2 F · C2 F · C2 U · Zusammenfassung: Akkordton 3, Vorhalt/Durchgang 2, bewusst akkordfremd 10, bewusst unaufgelöst 1

#### HE-B10 · Statischer Bass unter wechselnder Harmonie

- **Taktart:** 4/4 · **Länge:** 8 Takt(e) · **XYZ-Anker:** 0,20 / 0,30 / 0,50 (DRm) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  x-------x-------|x-------x-------|x-------x-------|x-------x-------|x-------x-------|x-------x-------|x-------x-------|x-------x-------
Töne  P(C2)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** C bleibt, darüber wechseln die Klänge (HE-H44, HE-H23)
- **Akkordwechsel:** ignoriert Wechsel, Neuansatz je Halbe
- **Artikulation:** portato
- **Wirkung:** Der Bass weigert sich mitzugehen; die Harmonie bewegt sich gegen ihn.
- **Kombination:** HE-H23, HE-H44
- **Quellen:** S5
- **Färbungsbereich:** alle X
- **Tonfunktionen** (gegen HE-H23, je Einsatz): C2 A · C2 A · C2 A · C2 A · C2 A · C2 A · C2 A · C2 A · C2 A · C2 A · C2 A · C2 A · C2 A · C2 A · C2 A · C2 A · Zusammenfassung: Akkordton 16
- **Technische Anforderungen:** Pedal über Akkordwechsel

#### HE-B11 · Bassantwort nach dem Akkordschlag

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,20 / 0,55 / 0,60 (Dmm) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  .....x.......x..|.....x.......x..
Töne  R   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Grundton des klingenden Klangs
- **Akkordwechsel:** folgt dem Akkord
- **Artikulation:** kurz
- **Wirkung:** Jede Behauptung bekommt eine verspätete, dunkle Antwort.
- **Kombination:** HE-R15, HE-H25
- **Quellen:** S4
- **Färbungsbereich:** alle X; die Lage der Rolle bestimmt die Färbung (tief = dunkel)
- **Tonfunktionen:** relativ zum Akkord (Grundton, Terz, Quinte, Oktave) – Akkordtöne

#### HE-B12 · Versetzte Gegenfigur: Oktave wird Tritonus

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,15 / 0,70 / 0,80 (DIU) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  ..x...x.x.....x.|...x....x...x...
Töne  R -8 R -8 P(F#1) P(C2) P(F#1)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** beginnt in Oktaven, endet im Tritonus
- **Akkordwechsel:** eigenständig
- **Artikulation:** kurz, akzentuiert
- **Wirkung:** Der Bass zerfällt gegen gleichmäßige Oberstimmen.
- **Kombination:** HE-R33, HE-H72
- **Quellen:** S4
- **Färbungsbereich:** eher X ≤ 0,6; in hellen Kontexten leiser oder eine Oktave höher
- **Tonfunktionen** (gegen HE-H72, je Einsatz): C2 A · C1 A · C2 A · C1 A · F♯1 A · C2 A · F♯1 A · Zusammenfassung: Akkordton 7

#### HE-B13 · Oktavierter langsamer Halbtonschritt

- **Taktart:** 4/4 · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,10 / 0,70 / 0,30 (DIS) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  x---------------|----------------|x---------------|----------------
Töne  P(C1) P(B0)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Oktaven C1/C2 bzw. B0/B1 (zweite Stimme im LB)
- **Akkordwechsel:** Halbton nach zwei Takten
- **Artikulation:** legato, schwer
- **Wirkung:** Dramatisches Absacken.
- **Kombination:** HE-H86, HE-H94
- **Quellen:** S4
- **Färbungsbereich:** eher X ≤ 0,6; in hellen Kontexten leiser oder eine Oktave höher
- **Tonfunktionen** (gegen HE-H86, je Einsatz): C1 A · B0 U · Zusammenfassung: Akkordton 1, bewusst unaufgelöst 1
- **Technische Anforderungen:** Mehrstimmiger Bass

#### HE-B14 · Langsames Halbtonpendel

- **Taktart:** 4/4 · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,20 / 0,25 / 0,60 (DRm) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  x---------------|----------------|x---------------|----------------
Töne  P(C2) P(Db2)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Pendel gegen statischen Oberklang
- **Akkordwechsel:** eigenständig
- **Artikulation:** legato
- **Wirkung:** Atmen eines fremden Körpers.
- **Kombination:** HE-H67, HE-H43
- **Quellen:** S4
- **Färbungsbereich:** alle X
- **Tonfunktionen** (gegen HE-H67, je Einsatz): C2 A · D♭2 A · Zusammenfassung: Akkordton 2

#### HE-B15 · Tritonuspendel

- **Taktart:** 4/4 · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,15 / 0,40 / 0,70 (DmU) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  x---------------|----------------|x---------------|----------------
Töne  P(C2) P(F#1)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Pendel unter Oberklang
- **Akkordwechsel:** eigenständig oder mit HE-H11
- **Artikulation:** legato
- **Wirkung:** Der Boden kippt ganz um und zurück.
- **Kombination:** HE-H11, HE-H79
- **Quellen:** S10
- **Färbungsbereich:** eher X ≤ 0,6; in hellen Kontexten leiser oder eine Oktave höher
- **Tonfunktionen** (gegen HE-H11, je Einsatz): C2 A · F♯1 U · Zusammenfassung: Akkordton 1, bewusst unaufgelöst 1

#### HE-B16 · Obsessiver Viertelpuls auf einem Ton

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,20 / 0,35 / 0,45 (DRm) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  x...x...x...x...|x...x...x...x...
Töne  P(C2)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Pedal
- **Akkordwechsel:** ignoriert Wechsel
- **Artikulation:** gleichmäßig, mittellang
- **Wirkung:** Puls statt Rhythmus; ein Uhrwerk, das nicht stehen bleibt.
- **Kombination:** HE-R02, HE-H22
- **Quellen:** S4
- **Färbungsbereich:** alle X
- **Tonfunktionen** (gegen HE-H22, je Einsatz): C2 A · C2 A · C2 A · C2 A · C2 A · C2 A · C2 A · C2 A · Zusammenfassung: Akkordton 8

#### HE-B17 · Marschbass Grundton–Tritonus

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,15 / 0,55 / 0,45 (Dmm) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  x...x...x...x...|x...x...x...x...
Töne  R P(F#1)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Grundton und Tritonus im Wechsel
- **Akkordwechsel:** Grundton folgt dem Akkord, Tritonus fest
- **Artikulation:** marcato, kurz
- **Wirkung:** Ein Schritt, der falsch aufsetzt.
- **Kombination:** HE-R09, HE-H79
- **Quellen:** S14
- **Färbungsbereich:** eher X ≤ 0,6; in hellen Kontexten leiser oder eine Oktave höher
- **Tonfunktionen** (gegen HE-H79, je Einsatz): C2 A · F♯1 F · C2 A · F♯1 F · C2 A · F♯1 F · C2 A · F♯1 U · Zusammenfassung: Akkordton 4, bewusst akkordfremd 3, bewusst unaufgelöst 1

#### HE-B18 · Schweres Paukenmuster

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,10 / 0,70 / 0,35 (DIS) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  X..x....X..x....|X..x....X..x....
Töne  R R 5 R   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Grundton, Quinte als Nebenschlag
- **Akkordwechsel:** Wechsel auf 1
- **Artikulation:** kurz, schwer
- **Wirkung:** Dumpfer, ritueller Antrieb.
- **Kombination:** HE-R08, HE-H80
- **Quellen:** S14
- **Färbungsbereich:** alle X; die Lage der Rolle bestimmt die Färbung (tief = dunkel)
- **Tonfunktionen:** relativ zum Akkord (Grundton, Terz, Quinte, Oktave) – Akkordtöne

#### HE-B19 · Sparsame drohende Impulse

- **Taktart:** 4/4 · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,10 / 0,40 / 0,55 (Dmm) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  x...............|................|..........x.....|................
Töne  P(C1) P(F#1)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** unabhängig vom Oberklang
- **Akkordwechsel:** nimmt keine Rücksicht
- **Artikulation:** kurz, tief, mf
- **Wirkung:** Etwas Großes bewegt sich irgendwo unten, selten und unvorhersehbar.
- **Kombination:** HE-H66, HE-R18
- **Färbungsbereich:** eher X ≤ 0,6; in hellen Kontexten leiser oder eine Oktave höher
- **Tonfunktionen** (gegen HE-H66, je Einsatz): C1 A · F♯1 A · Zusammenfassung: Akkordton 2

#### HE-B20 · Einzelimpuls nach langer Leere

- **Taktart:** 4/4 · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,10 / 0,15 / 0,50 (DRm) · **Evidenz:** Verfahren [E], Vorlage [E]

```
Bass  ................|................|................|......x.........
Töne  P(C1)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** unabhängig
- **Akkordwechsel:** unabhängig
- **Artikulation:** kurz, leise, sehr tief
- **Wirkung:** Drei Takte Nichts, dann ein einziger tiefer Ton.
- **Kombination:** HE-R35, HE-H73
- **Färbungsbereich:** eher X ≤ 0,6; in hellen Kontexten leiser oder eine Oktave höher
- **Tonfunktionen** (gegen HE-H73, je Einsatz): C1 A · Zusammenfassung: Akkordton 1

#### HE-B21 · Später Basseinsatz

- **Taktart:** 4/4 · **Länge:** 8 Takt(e) · **XYZ-Anker:** 0,30 / 0,25 / 0,40 (DRm) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  ................|................|................|................|x---------------|----------------|----------------|----------------
Töne  P(C2)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Musik beginnt bassfrei; der Boden kommt erst in Takt 5
- **Akkordwechsel:** Pedal ab Takt 5
- **Artikulation:** legato
- **Wirkung:** Erst Schweben, dann Gewicht; der Bass ist ein Ereignis.
- **Kombination:** HE-H13, HE-H10
- **Quellen:** S5, S4
- **Färbungsbereich:** alle X
- **Tonfunktionen** (gegen HE-H13, je Einsatz): C2 A · Zusammenfassung: Akkordton 1
- **Technische Anforderungen:** Pedal über Akkordwechsel

#### HE-B22 · Chromatische Dreitonzelle im Bass

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,15 / 0,40 / 0,60 (Dmm) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  x.x.x-----......|x.x.x-----......
Töne  P(C2) P(C#2) P(D2)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** unabhängig; Zelle als Ostinato
- **Akkordwechsel:** bleibt
- **Artikulation:** non legato, letzter Ton lang
- **Wirkung:** Ein zähes, kriechendes Motiv in der Tiefe.
- **Kombination:** HE-M17, HE-H73
- **Quellen:** S4
- **Färbungsbereich:** alle X
- **Tonfunktionen** (gegen HE-H73, je Einsatz): C2 A · D♭2 A · D2 A · C2 A · D♭2 A · D2 A · Zusammenfassung: Akkordton 6

#### HE-B23 · Hemiolische Bassakzente

- **Taktart:** 3/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,30 / 0,50 / 0,75 (DmU) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  x...x...x...|x.....x.....
Töne  R   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Grundton
- **Akkordwechsel:** Wechsel auf 1
- **Artikulation:** kurz
- **Wirkung:** Der Dreiertakt wird von unten umgedeutet.
- **Kombination:** HE-R57, HE-R10
- **Quellen:** S18
- **Färbungsbereich:** alle X; die Lage der Rolle bestimmt die Färbung (tief = dunkel)
- **Tonfunktionen:** relativ zum Akkord (Grundton, Terz, Quinte, Oktave) – Akkordtöne

#### HE-B24 · Bass in Dreiergruppen gegen Vierertakt

- **Taktart:** 4/4 · **Länge:** 3 Takt(e) · **XYZ-Anker:** 0,20 / 0,55 / 0,85 (DmU) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  x..x..x..x..x..x|..x..x..x..x..x.|.x..x..x..x..x..
Töne  R 8 R   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Grundton und Oktave
- **Akkordwechsel:** folgt dem Akkord
- **Artikulation:** kurz
- **Wirkung:** Kreuzrhythmus von unten; der Grund schwankt.
- **Kombination:** HE-R11, HE-H34
- **Quellen:** S4
- **Färbungsbereich:** alle X; die Lage der Rolle bestimmt die Färbung (tief = dunkel)
- **Tonfunktionen:** relativ zum Akkord (Grundton, Terz, Quinte, Oktave) – Akkordtöne
- **Technische Anforderungen:** Unabhängige rhythmische Zyklen

#### HE-B25 · Zweitaktige Basstöne

- **Taktart:** 4/4 · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,20 / 0,50 / 0,60 (Dmm) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  x---------------|----------------|x---------------|----------------
Töne  R   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Grundton, wechselt alle zwei Takte
- **Akkordwechsel:** folgt dem Akkord
- **Artikulation:** legato
- **Wirkung:** Ruhiger Boden unter rasender Bewegung.
- **Kombination:** HE-R12, HE-H34
- **Quellen:** S4
- **Färbungsbereich:** alle X; die Lage der Rolle bestimmt die Färbung (tief = dunkel)
- **Tonfunktionen:** relativ zum Akkord (Grundton, Terz, Quinte, Oktave) – Akkordtöne

#### HE-B26 · Bass steigt, während der Klang sinkt

- **Taktart:** 4/4 · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,30 / 0,45 / 0,60 (Dmm) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  x-------x-------|x-------x-------|x-------x-------|x-------x-------
Töne  P(C2) P(D2) P(E2) P(F#2) P(G#2) P(A#2) P(C3) P(C3)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Ganztonleiter aufwärts gegen absinkende Parallelklänge
- **Akkordwechsel:** eigenständig
- **Artikulation:** legato
- **Wirkung:** Die Schere öffnet sich.
- **Kombination:** HE-H32, HE-H33
- **Quellen:** S6
- **Färbungsbereich:** alle X
- **Tonfunktionen** (gegen HE-H32, je Einsatz): C2 A · D2 V→E2 · E2 A · F♯2 F · A♭2 V→B♭2 · B♭2 A · C3 F · C3 U · Zusammenfassung: Akkordton 3, Vorhalt/Durchgang 2, bewusst akkordfremd 2, bewusst unaufgelöst 1

#### HE-B27 · Rhythmische Frage und Antwort im Bass

- **Taktart:** 4/4 · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,25 / 0,30 / 0,55 (DRm) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  x.x.............|......x.........|x.x.............|.........x......
Töne  R R 5 R R 5   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Grundton; Antwort auf der Quinte
- **Akkordwechsel:** folgt dem Akkord
- **Artikulation:** kurz
- **Wirkung:** Bass stellt eine Frage und bekommt von sich selbst eine kurze, späte Antwort.
- **Kombination:** HE-R60
- **Quellen:** S4
- **Färbungsbereich:** alle X; die Lage der Rolle bestimmt die Färbung (tief = dunkel)
- **Tonfunktionen:** relativ zum Akkord (Grundton, Terz, Quinte, Oktave) – Akkordtöne

#### HE-B28 · Bassostinato in Fünfachteln

- **Taktart:** 4/4 · **Länge:** 5 Takt(e) · **XYZ-Anker:** 0,20 / 0,45 / 0,70 (DmU) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  x.x.x.x.x.x.x.x.|x.x.x.x.x.x.x.x.|x.x.x.x.x.x.x.x.|x.x.x.x.x.x.x.x.|x.x.x.x.x.x.x.x.
Töne  R P(Db2) R P(G1) P(Ab1)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Fünftonfolge gegen den Takt
- **Akkordwechsel:** Grundton folgt nicht
- **Artikulation:** staccato
- **Wirkung:** Ein Muster, das nie auf derselben Zählzeit beginnt.
- **Kombination:** HE-R63, HE-M18
- **Quellen:** S8
- **Färbungsbereich:** eher X ≤ 0,6; in hellen Kontexten leiser oder eine Oktave höher
- **Tonfunktionen:** relativ zum Akkord (Grundton, Terz, Quinte, Oktave) – Akkordtöne
- **Technische Anforderungen:** Unabhängige rhythmische Zyklen

#### HE-B29 · Bass-Seufzer

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,15 / 0,30 / 0,40 (DRm) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  x-------x---....|x-------x---....
Töne  P(Db2) P(C2)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Halbton abwärts auf den Grundton
- **Akkordwechsel:** bleibt
- **Artikulation:** lang–kurz
- **Wirkung:** Klage in der Tiefe.
- **Kombination:** HE-M02, HE-H43
- **Quellen:** S3
- **Färbungsbereich:** alle X
- **Tonfunktionen** (gegen HE-H43, je Einsatz): D♭2 V→C2 · C2 A · D♭2 V→C2 · C2 A · Zusammenfassung: Akkordton 2, Vorhalt/Durchgang 2

#### HE-B30 · Pedal mit unterer Nebennote

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,20 / 0,25 / 0,50 (DRm) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  x-------x---x---|x-------x---x---
Töne  P(C2) P(B1) P(C2)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Pedal, Nebennote kurz
- **Akkordwechsel:** bleibt
- **Artikulation:** legato
- **Wirkung:** Der Boden zuckt kurz und hält wieder.
- **Kombination:** HE-H01, HE-M05
- **Quellen:** S7
- **Färbungsbereich:** eher X ≤ 0,6; in hellen Kontexten leiser oder eine Oktave höher
- **Tonfunktionen** (gegen HE-H01, je Einsatz): C2 A · B1 A · C2 A · C2 A · B1 A · C2 A · Zusammenfassung: Akkordton 6

#### HE-B31 · Ganztonbass abwärts

- **Taktart:** 4/4 · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,25 / 0,35 / 0,50 (DRm) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  x-------x-------|x-------x-------|x-------x-------|x-------x-------
Töne  P(C2) P(Bb1) P(Ab1) P(F#1) P(E1) P(D1) P(C1) P(C1)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Ganztonleiter unter Ganztonklängen oder Moll
- **Akkordwechsel:** eigenständig
- **Artikulation:** legato
- **Wirkung:** Langsames, richtungsloses Hinabsteigen.
- **Kombination:** HE-H49, HE-H37
- **Quellen:** S9
- **Färbungsbereich:** eher X ≤ 0,6; in hellen Kontexten leiser oder eine Oktave höher
- **Tonfunktionen** (gegen HE-H49, je Einsatz): C2 A · B♭1 A · A♭1 A · F♯1 V→E1 · E1 A · D1 A · C1 A · C1 A · Zusammenfassung: Akkordton 7, Vorhalt/Durchgang 1

#### HE-B32 · Großterzbass

- **Taktart:** 4/4 · **Länge:** 8 Takt(e) · **XYZ-Anker:** 0,30 / 0,55 / 0,35 (DmS) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  x---------------|----------------|x---------------|----------------|x---------------|----------------|x---------------|----------------
Töne  P(C2) P(Ab1) P(E1) P(C1)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Großterzzyklus abwärts
- **Akkordwechsel:** mit HE-H98; für den aufsteigenden Dur-Zyklus HE-H41 die Tonfolge umkehren (C–E–A♭–C)
- **Artikulation:** legato
- **Wirkung:** Feierliches, rätselhaftes Sinken.
- **Kombination:** HE-H98
- **Quellen:** S9
- **Färbungsbereich:** eher X ≤ 0,6; in hellen Kontexten leiser oder eine Oktave höher
- **Tonfunktionen** (gegen HE-H98, je Einsatz): C2 A · A♭1 A · E1 A · C1 A · Zusammenfassung: Akkordton 4

#### HE-B33 · Kleinterzbass

- **Taktart:** 4/4 · **Länge:** 8 Takt(e) · **XYZ-Anker:** 0,20 / 0,45 / 0,55 (Dmm) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  x---------------|----------------|x---------------|----------------|x---------------|----------------|x---------------|----------------
Töne  P(C2) P(Eb2) P(F#2) P(A2)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Kleinterzkette aufwärts
- **Akkordwechsel:** mit HE-H39 oder HE-H08
- **Artikulation:** legato
- **Wirkung:** Symmetrisches Steigen ohne Ziel.
- **Kombination:** HE-H08, HE-H39
- **Quellen:** S11
- **Färbungsbereich:** alle X
- **Tonfunktionen** (gegen HE-H08, je Einsatz): C2 A · E♭2 A · F♯2 A · A2 A · Zusammenfassung: Akkordton 4

#### HE-B34 · Bass auf der Quinte

- **Taktart:** 4/4 · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,25 / 0,30 / 0,55 (DRm) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  x---------------|----------------|x---------------|----------------
Töne  5   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Quinte des Akkords statt Grundton
- **Akkordwechsel:** folgt dem Akkord
- **Artikulation:** legato
- **Wirkung:** Klänge stehen auf der Kante (Quartsextwirkung).
- **Kombination:** HE-H02, HE-H30
- **Quellen:** S4
- **Färbungsbereich:** alle X; die Lage der Rolle bestimmt die Färbung (tief = dunkel)
- **Tonfunktionen:** relativ zum Akkord (Grundton, Terz, Quinte, Oktave) – Akkordtöne

#### HE-B35 · Unregelmäßige kurze Viertel

- **Taktart:** 4/4 · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,20 / 0,30 / 0,65 (DRU) · **Evidenz:** Verfahren [E], Vorlage [E]

```
Bass  x.......x...x...|....x...........|x...x.......x...|........x.......
Töne  R   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Grundton
- **Akkordwechsel:** folgt dem Akkord
- **Artikulation:** kurz, ungleiche Abstände
- **Wirkung:** Schritte im Dunkeln, ohne Takt.
- **Kombination:** HE-R18, HE-H43
- **Färbungsbereich:** alle X; die Lage der Rolle bestimmt die Färbung (tief = dunkel)
- **Tonfunktionen:** relativ zum Akkord (Grundton, Terz, Quinte, Oktave) – Akkordtöne

#### HE-B36 · Vorgezogener Basston

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,25 / 0,35 / 0,60 (DRm) · **Evidenz:** Verfahren [E], Vorlage [E]

```
Bass  ..............x-|--------------x-
Töne  n   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Halbton unter dem nächsten Grundton, vor dem Wechsel
- **Akkordwechsel:** nimmt den nächsten Klang vorweg (falsch)
- **Artikulation:** legato
- **Wirkung:** Der Bass ist immer schon woanders.
- **Kombination:** HE-H33, HE-H22
- **Färbungsbereich:** alle X; die Lage der Rolle bestimmt die Färbung (tief = dunkel)
- **Tonfunktionen** (gegen HE-H33, je Einsatz): B2 F · B2 U · Zusammenfassung: bewusst akkordfremd 1, bewusst unaufgelöst 1

#### HE-B37 · Zitternder tiefer Bass

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,10 / 0,40 / 0,70 (DmU) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  xxxxxxxxxxxxxxxx|xxxxxxxxxxxxxxxx
Töne  R   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Grundton
- **Akkordwechsel:** folgt dem Akkord
- **Artikulation:** leise, kurz, dicht
- **Wirkung:** Ein Beben, das man mehr spürt als hört.
- **Kombination:** HE-H73, HE-H95
- **Färbungsbereich:** alle X; die Lage der Rolle bestimmt die Färbung (tief = dunkel)
- **Tonfunktionen:** relativ zum Akkord (Grundton, Terz, Quinte, Oktave) – Akkordtöne

#### HE-B38 · Vom Pedal zum Tritonus und zurück

- **Taktart:** 4/4 · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,20 / 0,25 / 0,60 (DRm) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  x---------------|----------------|x-------x-------|x---------------
Töne  P(C2) P(F#1) P(C2) P(C2)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Tritonus als kurzer Abweg
- **Akkordwechsel:** unabhängig
- **Artikulation:** legato
- **Wirkung:** Der Boden öffnet sich für zwei Halbe und schließt sich wieder.
- **Kombination:** HE-H43, HE-B02
- **Quellen:** S1
- **Färbungsbereich:** eher X ≤ 0,6; in hellen Kontexten leiser oder eine Oktave höher
- **Tonfunktionen** (gegen HE-H43, je Einsatz): C2 A · F♯1 F · C2 A · C2 A · Zusammenfassung: Akkordton 3, bewusst akkordfremd 1

#### HE-B39 · Bass als Fugato-Subjekt

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,20 / 0,45 / 0,60 (Dmm) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  x.x.x.x.x...x...|x.x.x.x.x-------
Töne  P(C2) P(Db2) P(C2) P(B1) P(Bb1) P(A1) P(Ab1) P(G1) P(Ab1) P(G1) P(F#1)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** eigene chromatische Linie, Anfang eines Fugatos
- **Akkordwechsel:** unabhängig
- **Artikulation:** non legato
- **Wirkung:** Eine Stimme beginnt, andere werden folgen.
- **Kombination:** HE-R43, HE-S21
- **Quellen:** S4
- **Färbungsbereich:** eher X ≤ 0,6; in hellen Kontexten leiser oder eine Oktave höher
- **Tonfunktionen:** relativ zum Akkord (Grundton, Terz, Quinte, Oktave) – Akkordtöne
- **Technische Anforderungen:** Kanon/koordinierte Parallelstimmen

#### HE-B40 · Achse mit Halbtonausweichen nach oben

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,20 / 0,30 / 0,55 (DRm) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  x...x...x...x...|x...x...x...x...
Töne  R +1 R R   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Grundton, Halbton darüber
- **Akkordwechsel:** folgt dem Akkord
- **Artikulation:** tenuto
- **Wirkung:** Ein Boden, der einmal pro Takt kurz nachgibt.
- **Kombination:** HE-H36, HE-M01
- **Quellen:** S4
- **Färbungsbereich:** alle X; die Lage der Rolle bestimmt die Färbung (tief = dunkel)
- **Tonfunktionen** (gegen HE-H36, je Einsatz): C2 A · D♭2 V→C2 · C2 A · C2 A · C2 A · D♭2 V→C2 · C2 A · C2 A · Zusammenfassung: Akkordton 6, Vorhalt/Durchgang 2

#### HE-B41 · Konvergenz auf das Pedal

- **Taktart:** 4/4 · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,20 / 0,40 / 0,45 (Dmm) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  x---x---x---x---|x---x---x---x---|x---x---x---x---|x---------------
Töne  P(F1) P(F#1) P(G1) P(G#1) P(A1) P(Bb1) P(B1) P(B1) P(C2) P(C2) P(C2) P(C2) P(C2)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** chromatisch auf C zulaufend, dort liegen
- **Akkordwechsel:** unabhängig
- **Artikulation:** legato
- **Wirkung:** Langsames Heranrücken an einen Ort, von dem es kein Weiter gibt.
- **Kombination:** HE-B08, HE-H09
- **Quellen:** S3
- **Färbungsbereich:** eher X ≤ 0,6; in hellen Kontexten leiser oder eine Oktave höher
- **Tonfunktionen** (gegen HE-H09, je Einsatz): F1 F · F♯1 V→G1 · G1 A · A♭1 F · A1 F · B♭1 F · B1 F · B1 V→C2 · C2 A · C2 A · C2 A · C2 A · C2 A · Zusammenfassung: Akkordton 6, Vorhalt/Durchgang 2, bewusst akkordfremd 5

#### HE-B42 · Bassloser Klang: tiefster Ton in der Mittellage

- **Taktart:** 4/4 · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,55 / 0,10 / 0,40 (mRm) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  x---------------|----------------|x---------------|----------------
Töne  P(G3)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** tiefster Ton liegt über G3; Langer Bass als zartes Pedal
- **Akkordwechsel:** bleibt
- **Artikulation:** legato, pp
- **Wirkung:** Kein Boden; schwebend, entrückt, verletzlich. Der Ton G3 gehört zu HE-H10 und HE-H01; über übermäßigen oder Ganztonklängen (HE-H13, HE-H49) G♯3 nehmen.
- **Kombination:** HE-H10, HE-H01, HE-H13
- **Quellen:** S5, S4
- **Färbungsbereich:** X ≥ 0,4 (bassloser Boden)
- **Tonfunktionen** (gegen HE-H10, je Einsatz): G3 A · G3 A · Zusammenfassung: Akkordton 2
- **Technische Anforderungen:** Pedal über Akkordwechsel, Exakte Registervorgabe

#### HE-B43 · Quint-Orgelpunkt, breit

- **Taktart:** 4/4 · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,40 / 0,80 / 0,20 (mIS) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  x---------------|----------------|x---------------|----------------
Töne  P(C1)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** mit gehaltener Quinte G1 darüber (zweite Stimme im LB); trägt Säulenklänge
- **Akkordwechsel:** bleibt
- **Artikulation:** legato, laut, ohne Neuansatz innerhalb von zwei Takten
- **Wirkung:** Ein breiter, offener Boden für kraftvolle Musik ohne Unruhe.
- **Kombination:** HE-H80, HE-H89, HE-R66
- **Quellen:** S15
- **Färbungsbereich:** alle X: unter dunklen Säulen tief, unter hellen Säulen leiser
- **Tonfunktionen** (gegen HE-H80, je Einsatz): C1 A · C1 A · Zusammenfassung: Akkordton 2
- **Technische Anforderungen:** Mehrstimmiger Bass

#### HE-B44 · Tritonuspedal unter hellen Schlägen

- **Taktart:** 4/4 · **Länge:** 2 Takt(e) · **XYZ-Anker:** 0,65 / 0,80 / 0,70 (HIU) · **Evidenz:** Verfahren [N], Vorlage [E]

```
Bass  x.......x.......|x.......x.......
Töne  P(F#1)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** Tritonus zum Grundton C des hellen Oberklangs
- **Akkordwechsel:** bleibt
- **Artikulation:** kurz bis halbe Note, laut
- **Wirkung:** Unter gleißenden Klängen ein Boden, der falsch steht; helle Bedrohung ohne Heldenton.
- **Kombination:** HE-H99, HE-H57, HE-S38
- **Quellen:** S1
- **Färbungsbereich:** X ≥ 0,5: Tritonusboden unter hellen Schlägen
- **Tonfunktionen** (gegen HE-H99, je Einsatz): F♯1 F · F♯1 F · F♯1 F · F♯1 U · Zusammenfassung: bewusst akkordfremd 3, bewusst unaufgelöst 1
- **Technische Anforderungen:** Pedal über Akkordwechsel

#### HE-B45 · Ganzton-Wechselpedal in der Mittellage

- **Taktart:** 4/4 · **Länge:** 4 Takt(e) · **XYZ-Anker:** 0,60 / 0,15 / 0,55 (mRm) · **Evidenz:** Verfahren [I], Vorlage [E]

```
Bass  x---------------|----------------|x---------------|----------------
Töne  P(G#3) P(A#3)   (je Einsatz, zyklisch)
```
- **Beziehung zur Harmonie:** tiefster Ton über G3; beide Töne gehören zur Ganztonreihe C–D–E–F♯–G♯–A♯
- **Akkordwechsel:** Wechsel alle zwei Takte
- **Artikulation:** legato, pp
- **Wirkung:** Kein Boden, aber ein langsames Pendeln; Schweben mit einem kaum merklichen Atem.
- **Kombination:** HE-H49, HE-S36
- **Quellen:** S5, S9
- **Färbungsbereich:** X ≥ 0,4 (bassloser Boden)
- **Tonfunktionen** (gegen HE-H49, je Einsatz): A♭3 A · B♭3 A · Zusammenfassung: Akkordton 2
- **Technische Anforderungen:** Exakte Registervorgabe

## F Motive (HE-M01–M57)

Zellen aus 2–5 Tönen. Keine Zelle ist dauerhaft vorherrschend; die Spalte „Muss erhalten bleiben“ nennt, woran die Zelle nach einer Transformation wiedererkannt wird (nach den Befunden zu Psycho und Marnie: Intervallrichtung plus Rhythmus *oder* Tonhöhen, S3, S7, S8).

#### HE-M01 · Halbtonschritt aufwärts

- **Töne/Dauern:** `C4/4 Db4/12` (Taktart 4/4) · **Kontext:** `CmM7` | `CmM7`
- **Intervalle (Halbtöne):** +1 · **Ambitus:** 1 · **XYZ:** 0,20 / 0,20 / 0,45 (DRm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** tenuto, zweiter Ton leiser · **Kontur:** ein Schritt aufwärts, dann Stillstand
- **Wiederkehr:** beliebig oft, auch als Ostinato in Achteln (HE-R01) · **Transformationen:** Umkehrung (Halbton abwärts), Oktavversetzung zur großen Septime (HE-M11), Diminution
- **Muss erhalten bleiben:** Richtung und Halbtongröße
- **Verfahren:** Halbtonzelle als Keimzelle eines ganzen Films; als Ostinato, Seufzer und Cluster verarbeitet (Psycho). (S4, S3)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): C4 A · D♭4 U
- **Harmonische Absicht:** unaufgelöste Reibung am Ende ist gewollt (nicht harmonisch korrigieren)

#### HE-M02 · Seufzer

- **Töne/Dauern:** `Eb4/6 D4/2 r/8` (Taktart 4/4) · **Kontext:** `CmM7` | `Cm`
- **Intervalle (Halbtöne):** -1 · **Ambitus:** 1 · **XYZ:** 0,25 / 0,20 / 0,35 (DRS) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** betont–unbetont, lang–kurz · **Kontur:** Halbton abwärts
- **Wiederkehr:** in mehr als der Hälfte aller Cues denkbar; Abstände unregelmäßig · **Transformationen:** Augmentation, Verkürzung auf eine Note, Verschiebung um einen Halbton
- **Muss erhalten bleiben:** Abwärtsrichtung und Betonung auf dem ersten Ton
- **Verfahren:** Seufzermotive in über 20 Cues von Psycho, auch in Vertigo, North by Northwest, Day the Earth (Husarik). (S3)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): E♭4 A · D4 T
- **Harmonische Absicht:** nur Akkord- und Vorratstöne; die Spannung liegt im Kontextklang

#### HE-M03 · Vierton-Prototyp: Dissonanz schwer, Auflösung leicht

- **Töne/Dauern:** `Ab4/4 G4/4 F4/4 Eb4/4` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** -1 -2 -2 · **Ambitus:** 5 · **XYZ:** 0,25 / 0,30 / 0,40 (DRm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** erster und dritter Ton betont · **Kontur:** stufenweise abwärts in zwei Vorhalt-Paaren
- **Wiederkehr:** als Modul zweimal, dann verändert (a–a–b) · **Transformationen:** Wiederholung mit oberer Nebennote, Umkehrung mit unterer Nebennote, Transposition als Vorhalt
- **Muss erhalten bleiben:** Betonung auf den Dissonanzen (1 und 3)
- **Verfahren:** Grundprototyp der Module: stufenweise Dissonanzauflösung in Viertonsegmenten mit „strong-beat dissonance and weak-beat resolution“ (Schneller). (S7)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): A♭4 V→G4 · G4 A · F4 V→E♭4 · E♭4 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M04 · Obere Nebennote, wiederholt

- **Töne/Dauern:** `D4/2 C4/2 D4/2 C4/2 D4/2 C4/6` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** -2 +2 -2 +2 -2 · **Ambitus:** 2 · **XYZ:** 0,25 / 0,30 / 0,55 (DRm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** leicht, gleichmäßig · **Kontur:** Pendel um eine Stufe, endet unten
- **Wiederkehr:** als Teppich unter einer Fläche · **Transformationen:** Halbton statt Ganzton (D♭–C), Augmentation
- **Muss erhalten bleiben:** Pendel und Endton
- **Verfahren:** Variante des Prototyps durch Wiederholung (obere Nebennote). (S7)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): D4 V→C4 · C4 A · D4 V→C4 · C4 A · D4 V→C4 · C4 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M05 · Untere Nebennote

- **Töne/Dauern:** `C4/4 B3/2 C4/10` (Taktart 4/4) · **Kontext:** `CmM7` | `CmM7`
- **Intervalle (Halbtöne):** -1 +1 · **Ambitus:** 1 · **XYZ:** 0,20 / 0,20 / 0,45 (DRm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** legato · **Kontur:** kurzes Absinken, Rückkehr
- **Wiederkehr:** jeden zweiten Takt · **Transformationen:** Ausdehnung (B3 länger), Verdopplung in der Oktave
- **Muss erhalten bleiben:** Rückkehr auf den Ausgangston
- **Verfahren:** Variante des Prototyps durch Umkehrung (untere Nebennote). (S7)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): C4 A · B3 A · C4 A
- **Harmonische Absicht:** nur Akkord- und Vorratstöne; die Spannung liegt im Kontextklang

#### HE-M06 · Vorhalt mit Auflösung

- **Töne/Dauern:** `D4/8 C4/8` (Taktart 4/4) · **Kontext:** `Cm(addb9)` | `Cm`
- **Intervalle (Halbtöne):** -2 · **Ambitus:** 2 · **XYZ:** 0,30 / 0,25 / 0,30 (DRS) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** Vorhalt lang, Auflösung leiser · **Kontur:** Ganzton abwärts
- **Wiederkehr:** am Ende eines Moduls · **Transformationen:** D♭ statt D (schärfer), Auflösung weglassen (HE-M52)
- **Muss erhalten bleiben:** lang auf schwerer Zeit
- **Verfahren:** Variante des Prototyps durch Transposition als Vorhalt. (S7)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, kein gemeinsamer Vorrat – Nicht-Akkordtöne sind Vorhalt, Reibung oder unaufgelöst): D4 V→C4 · C4 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M07 · Appoggiatur im Sprung

- **Töne/Dauern:** `G4/2 Db5/6 C5/8` (Taktart 4/4) · **Kontext:** `C` | `C`
- **Intervalle (Halbtöne):** +6 -1 · **Ambitus:** 6 · **XYZ:** 0,35 / 0,40 / 0,50 (Dmm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** Sprungton betont · **Kontur:** Sprung auf den Halbtonnachbarn, Auflösung
- **Wiederkehr:** selten, als Höhepunkt einer Zelle · **Transformationen:** Sprung größer (Oktave + Halbton, HE-M44)
- **Muss erhalten bleiben:** Halbton von oben
- **Verfahren:** Appoggiatur als Variante des Prototyps. (S7)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Dur): G4 A · D♭5 V→C5 · C5 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M08 · Dreitonzelle chromatisch abwärts

- **Töne/Dauern:** `Ab4/4 G4/4 Gb4/8` (Taktart 4/4) · **Kontext:** `CmM7` | `Cm7b5`
- **Intervalle (Halbtöne):** -1 -1 · **Ambitus:** 2 · **XYZ:** 0,20 / 0,30 / 0,50 (DRm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** tenuto · **Kontur:** zwei Halbtöne abwärts
- **Wiederkehr:** dreimal hintereinander, dritte Aussage verschoben (HE-R19) · **Transformationen:** Ganzton–Halbton statt Halbton–Halbton, Umkehrung
- **Muss erhalten bleiben:** Dreitönigkeit und Abwärtsrichtung
- **Verfahren:** Kurze dreitönige Zellen, mehrfach und verschoben wiederholt (Psycho, „Finale“: drei Aussagen, die dritte um einen Schlag verschoben); eigene Töne. (S4, S3)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, kein gemeinsamer Vorrat – Nicht-Akkordtöne sind Vorhalt, Reibung oder unaufgelöst): A♭4 V→G4 · G4 A · F♯4 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M09 · Symmetrische Nebennotenzelle

- **Töne/Dauern:** `C4/2 Db4/2 Eb4/4 Db4/2 C4/6` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** +1 +2 -2 -1 · **Ambitus:** 3 · **XYZ:** 0,25 / 0,25 / 0,50 (DRm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** legato, gleichmäßig · **Kontur:** auf und spiegelbildlich zurück
- **Wiederkehr:** als einzige „Melodie“ eines Ostinato-Cues · **Transformationen:** Tritonus-Transposition (HE-M10), Umkehrung
- **Muss erhalten bleiben:** Spiegelsymmetrie
- **Verfahren:** Symmetrische Nebennotenzellen und ihre Tritonus-Transposition (Vertigo, „Madeleine’s Car“); eigene Intervallfolge (Halbton–Ganzton). (S5, S12)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): C4 A · D♭4 V→E♭4 · E♭4 A · D♭4 V→C4 · C4 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M10 · Dieselbe Zelle im Tritonus

- **Töne/Dauern:** `F#4/2 G4/2 A4/4 G4/2 F#4/6` (Taktart 4/4) · **Kontext:** `F#7b5` | `C7`
- **Intervalle (Halbtöne):** +1 +2 -2 -1 · **Ambitus:** 3 · **XYZ:** 0,30 / 0,25 / 0,55 (DRm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** legato · **Kontur:** auf und zurück
- **Wiederkehr:** als zweite Aussage nach HE-M09 · **Transformationen:** zurück nach C
- **Muss erhalten bleiben:** Symmetrie und Intervallfolge
- **Verfahren:** Tritonus-Transposition einer Zelle (Smith über Vertigo). (S5)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, kein gemeinsamer Vorrat – Nicht-Akkordtöne sind Vorhalt, Reibung oder unaufgelöst): F♯4 A · G4 F · A4 V→G4 · G4 A · F♯4 U
- **Harmonische Absicht:** unaufgelöste Reibung am Ende ist gewollt (nicht harmonisch korrigieren); akkordfremde Töne innerhalb der Zelle sind Teil der Gestalt (Halbton- oder Tritonusreibung); Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M11 · Halbton als große Septime

- **Töne/Dauern:** `C4/4 Db3/12` (Taktart 4/4) · **Kontext:** `CmM7` | `CmM7`
- **Intervalle (Halbtöne):** -11 · **Ambitus:** 11 · **XYZ:** 0,20 / 0,55 / 0,65 (DmU) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** beide Töne akzentuiert · **Kontur:** großer Sprung abwärts (große Septime)
- **Wiederkehr:** als Verschärfung von HE-M01 · **Transformationen:** zurück in die enge Lage
- **Muss erhalten bleiben:** Tonklassen D♭ und C
- **Verfahren:** Halbtonmotiv zur großen Septime umgekehrt (Psycho, „The Murder“; Pearson): aus dem Halbton aufwärts C–D♭ wird die große Septime abwärts C4–D♭3. (S4)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): C4 A · D♭3 U
- **Harmonische Absicht:** unaufgelöste Reibung am Ende ist gewollt (nicht harmonisch korrigieren)

#### HE-M12 · Zwei verschränkte Halbtöne

- **Töne/Dauern:** `C4/2 Db4/2 E4/2 F4/2 C4/2 Db4/2 E4/2 F4/2` (Taktart 4/4) · **Kontext:** `{C E Db F}` | `{C E Db F}`
- **Intervalle (Halbtöne):** +1 +3 +1 -5 +1 +3 +1 · **Ambitus:** 5 · **XYZ:** 0,25 / 0,45 / 0,70 (DmU) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** gleichmäßig, Achtel · **Kontur:** Doppelpaar aufwärts
- **Wiederkehr:** als Ostinato · **Transformationen:** Paare in Gegenrichtung (F–E, D♭–C)
- **Muss erhalten bleiben:** zwei Halbtonpaare im Abstand einer großen Terz
- **Verfahren:** Intervallverzahnung als Ostinato (Psycho-Prelude ab T. 29). (S4)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, kein gemeinsamer Vorrat – Nicht-Akkordtöne sind Vorhalt, Reibung oder unaufgelöst): C4 A · D♭4 A · E4 A · F4 A · C4 A · D♭4 A · E4 A · F4 A
- **Harmonische Absicht:** nur Akkord- und Vorratstöne; die Spannung liegt im Kontextklang

#### HE-M13 · Kleinterzpendel

- **Töne/Dauern:** `C4/4 Eb4/4 C4/4 Eb4/4` (Taktart 4/4) · **Kontext:** `Cm` | `CmM7`
- **Intervalle (Halbtöne):** +3 -3 +3 · **Ambitus:** 3 · **XYZ:** 0,25 / 0,30 / 0,45 (DRm) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** leicht · **Kontur:** Pendel
- **Wiederkehr:** als Tupfermuster · **Transformationen:** kleine Terz → übermäßige Sekunde (C–D♯ über H-Dur-Klang)
- **Muss erhalten bleiben:** Pendelbewegung
- **Verfahren:** Obsessive Wiederkehr kurzer Intervallfiguren [I].
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): C4 A · E♭4 A · C4 A · E♭4 A
- **Harmonische Absicht:** nur Akkord- und Vorratstöne; die Spannung liegt im Kontextklang

#### HE-M14 · Tritonussprung mit Halbtonrückfall

- **Töne/Dauern:** `C4/4 F#4/4 F4/8` (Taktart 4/4) · **Kontext:** `Cm7b5` | `Cm7b5`
- **Intervalle (Halbtöne):** +6 -1 · **Ambitus:** 6 · **XYZ:** 0,20 / 0,45 / 0,65 (DmU) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** erster Ton kurz, Ziel lang · **Kontur:** Sprung auf, kleiner Fall
- **Wiederkehr:** selten, als Störung · **Transformationen:** Sprung abwärts
- **Muss erhalten bleiben:** Tritonus und folgender Halbton
- **Verfahren:** Tritonus als Herrmann-Intervall (Bass, Polychord) auf die Linie übertragen [I]. (S1)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, kein gemeinsamer Vorrat – Nicht-Akkordtöne sind Vorhalt, Reibung oder unaufgelöst): C4 A · F♯4 A · F4 U
- **Harmonische Absicht:** unaufgelöste Reibung am Ende ist gewollt (nicht harmonisch korrigieren)

#### HE-M15 · Repetierter Ton, Halbton am Ende

- **Töne/Dauern:** `G4/2 G4/2 G4/2 G4/2 G4/2 G4/2 Ab4/4` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** +0 +0 +0 +0 +0 +1 · **Ambitus:** 1 · **XYZ:** 0,25 / 0,35 / 0,55 (DRm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** gleichmäßig, letzter Ton betont · **Kontur:** Stillstand, dann ein Ruck
- **Wiederkehr:** in jedem Takt gleich · **Transformationen:** Repetitionszahl ändern (5, 7)
- **Muss erhalten bleiben:** Repetition und Halbton
- **Verfahren:** Obsessive Repetition auf einem Ton (Vibraphon-D in „Carlotta’s Portrait“) mit Halbtonnachbar [N/I]. (S12)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): G4 A · G4 A · G4 A · G4 A · G4 A · G4 A · A♭4 T
- **Harmonische Absicht:** nur Akkord- und Vorratstöne; die Spannung liegt im Kontextklang

#### HE-M16 · Chromatische Viertonlinie aufwärts

- **Töne/Dauern:** `C4/4 Db4/4 D4/4 Eb4/4` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** +1 +1 +1 · **Ambitus:** 3 · **XYZ:** 0,20 / 0,45 / 0,55 (Dmm) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** crescendo innerhalb der Linie · **Kontur:** stetig aufwärts
- **Wiederkehr:** sequenziert jeweils einen Halbton höher · **Transformationen:** abwärts (Rückzug), in Halben (Drohung)
- **Muss erhalten bleiben:** Halbtonschritte gleicher Richtung
- **Verfahren:** Zelle zur Viertongruppe erweitert (Kompression nach Schneller rückwärts gelesen) [I]. (S8)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): C4 A · D♭4 F · D4 V→E♭4 · E♭4 A
- **Harmonische Absicht:** akkordfremde Töne innerhalb der Zelle sind Teil der Gestalt (Halbton- oder Tritonusreibung); Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M17 · Fünftonerweiterung

- **Töne/Dauern:** `Ab4/2 G4/2 F4/2 Eb4/2 D4/8` (Taktart 4/4) · **Kontext:** `Cm` | `G7b9`
- **Intervalle (Halbtöne):** -1 -2 -2 -1 · **Ambitus:** 6 · **XYZ:** 0,25 / 0,35 / 0,45 (DRm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** erster Ton betont · **Kontur:** stufenweise abwärts
- **Wiederkehr:** als b-Teil einer Bar-Form · **Transformationen:** auf vier Töne kürzen (zurück zu HE-M03)
- **Muss erhalten bleiben:** stufenweiser Abstieg
- **Verfahren:** Erweiterung des Tetrachords zum Fünftonmuster (Marnie, Endless Night; Schneller). (S7, S8)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): A♭4 V→G4 · G4 A · F4 V→E♭4 · E♭4 A · D4 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M18 · Fünftonmuster im Achtelfluss

- **Töne/Dauern:** `C4/2 Db4/2 F4/2 E4/2 Eb4/2 C4/2 Db4/2 F4/2` (Taktart 4/4) · **Kontext:** `{C E Db F}` | `{C E Db F}`
- **Intervalle (Halbtöne):** +1 +4 -1 -1 -3 +1 +4 · **Ambitus:** 5 · **XYZ:** 0,30 / 0,40 / 0,65 (DmU) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** gleichmäßig · **Kontur:** Kreisen, gegen den Takt versetzt
- **Wiederkehr:** durchlaufend (mit HE-R63) · **Transformationen:** einen Ton ersetzen
- **Muss erhalten bleiben:** Fünferperiode
- **Verfahren:** Fünftonmuster als Ostinato (Schneller) [N]; Periodenverschiebung [E]. (S7)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, kein gemeinsamer Vorrat – Nicht-Akkordtöne sind Vorhalt, Reibung oder unaufgelöst): C4 A · D♭4 A · F4 A · E4 A · E♭4 F · C4 A · D♭4 A · F4 A
- **Harmonische Absicht:** akkordfremde Töne innerhalb der Zelle sind Teil der Gestalt (Halbton- oder Tritonusreibung)
- **Technische Anforderungen:** Unabhängige rhythmische Zyklen

#### HE-M19 · Kurze Frage

- **Töne/Dauern:** `C4/4 D4/4 r/8` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** +2 · **Ambitus:** 2 · **XYZ:** 0,30 / 0,25 / 0,40 (DRm) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** offen, zweiter Ton nicht verkürzt · **Kontur:** zwei Töne aufwärts
- **Wiederkehr:** mit HE-M20 als Paar · **Transformationen:** Halbton statt Ganzton
- **Muss erhalten bleiben:** Aufwärtsrichtung
- **Verfahren:** Frage–Antwort aus kleinsten Zellen [I].
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): C4 A · D4 T
- **Harmonische Absicht:** nur Akkord- und Vorratstöne; die Spannung liegt im Kontextklang

#### HE-M20 · Verkürzte Antwort

- **Töne/Dauern:** `r/8 Eb4/2 Db4/6` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** -2 · **Ambitus:** 2 · **XYZ:** 0,25 / 0,25 / 0,45 (DRm) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** zurückgenommen · **Kontur:** zwei Töne abwärts, kürzer
- **Wiederkehr:** nach HE-M19 · **Transformationen:** Antwort bleibt aus
- **Muss erhalten bleiben:** Abwärtsrichtung
- **Verfahren:** Frage–Antwort [I].
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): E♭4 A · D♭4 U
- **Harmonische Absicht:** unaufgelöste Reibung am Ende ist gewollt (nicht harmonisch korrigieren)

#### HE-M21 · Zerfall: vier, drei, zwei Töne

- **Töne/Dauern:** `Ab4/2 G4/2 F4/2 Eb4/2 r/8 | Ab4/2 G4/2 F4/4 r/8 | Ab4/4 G4/4 r/8` (Taktart 4/4) · **Kontext:** `Cm` | `Cm` | `Cm`
- **Intervalle (Halbtöne):** -1 -2 -2 +5 -1 -2 +3 -1 · **Ambitus:** 5 · **XYZ:** 0,25 / 0,25 / 0,50 (DRm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** immer leiser · **Kontur:** stufenweise abwärts, kürzer werdend
- **Wiederkehr:** einmal · **Transformationen:** zuletzt nur Ab allein
- **Muss erhalten bleiben:** Kopf Ab–G bleibt
- **Verfahren:** Fortschreitende Kürzung bis zur Isolierung eines Teils (Schneller über Marnie; Liquidation nach Husarik). (S8, S3)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): A♭4 V→G4 · G4 A · F4 V→E♭4 · E♭4 A · A♭4 V→G4 · G4 A · F4 T · A♭4 V→G4 · G4 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M22 · Verlängerung durch angehängtes Glied

- **Töne/Dauern:** `Ab4/2 G4/2 F4/2 Eb4/2 F4/2 Eb4/2 D4/4` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** -1 -2 -2 +2 -2 -1 · **Ambitus:** 6 · **XYZ:** 0,25 / 0,30 / 0,45 (DRm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** gleichmäßig · **Kontur:** Abstieg mit Nachsatz
- **Wiederkehr:** als b-Teil · **Transformationen:** zweites Anhängsel
- **Muss erhalten bleiben:** Prototyp HE-M03 als Kopf
- **Verfahren:** Modulverlängerung durch Wiederholung des Schlussglieds [N, Schneller „Rainstorm“]. (S7)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): A♭4 V→G4 · G4 A · F4 V→E♭4 · E♭4 A · F4 V→E♭4 · E♭4 A · D4 T
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M23 · Rhythmische Transformation: punktiert

- **Töne/Dauern:** `Ab4/3 G4/1 F4/3 Eb4/1 r/8` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** -1 -2 -2 · **Ambitus:** 5 · **XYZ:** 0,25 / 0,45 / 0,60 (Dmm) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** scharf · **Kontur:** wie HE-M03
- **Wiederkehr:** als Interpunktion · **Transformationen:** Doppelpunktierung
- **Muss erhalten bleiben:** Tonfolge von HE-M03
- **Verfahren:** Herrmann behält Tonhöhen oder Rhythmus der Zelle und ändert das andere [I]. (S4)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): A♭4 V→G4 · G4 A · F4 V→E♭4 · E♭4 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M24 · Augmentation

- **Töne/Dauern:** `Ab4/8 G4/8 | F4/8 Eb4/8` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** -1 -2 -2 · **Ambitus:** 5 · **XYZ:** 0,20 / 0,25 / 0,35 (DRS) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** legato, getragen · **Kontur:** wie HE-M03
- **Wiederkehr:** in der Gegenstimme unter Bewegung · **Transformationen:** nur zwei Töne augmentieren
- **Muss erhalten bleiben:** Tonfolge
- **Verfahren:** Augmentation des Halbtonmotivs (Psycho, „The Murder“ T. 17–28). (S4)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): A♭4 V→G4 · G4 A · F4 V→E♭4 · E♭4 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M25 · Diminution

- **Töne/Dauern:** `Ab4/1 G4/1 F4/1 Eb4/1 r/12` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** -1 -2 -2 · **Ambitus:** 5 · **XYZ:** 0,25 / 0,50 / 0,70 (DmU) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** flüchtig · **Kontur:** wie HE-M03, gehetzt
- **Wiederkehr:** als Tupfer · **Transformationen:** zweimal hintereinander
- **Muss erhalten bleiben:** Tonfolge
- **Verfahren:** Rhythmische Transformation [I].
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): A♭4 V→G4 · G4 A · F4 V→E♭4 · E♭4 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M26 · Fragment: Kopf und Seufzer

- **Töne/Dauern:** `Ab4/4 r/4 G4/6 F#4/2` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** -1 -1 · **Ambitus:** 2 · **XYZ:** 0,25 / 0,20 / 0,50 (DRm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** leise · **Kontur:** Ton, Pause, Seufzer
- **Wiederkehr:** als letzter Rest einer Zelle · **Transformationen:** nur der Seufzer
- **Muss erhalten bleiben:** Seufzer am Ende
- **Verfahren:** Liquidation: zuletzt bleibt der Seufzer allein (Husarik). (S3)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): A♭4 V→G4 · G4 A · F♯4 U
- **Harmonische Absicht:** unaufgelöste Reibung am Ende ist gewollt (nicht harmonisch korrigieren); Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M27 · Dissonanz gegen das Pedal, kontrolliert aufgelöst

- **Töne/Dauern:** `Db4/12 C4/4` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** -1 · **Ambitus:** 1 · **XYZ:** 0,20 / 0,25 / 0,40 (DRm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** Dissonanz lang, Auflösung kurz · **Kontur:** Halbton abwärts auf den Pedalton
- **Wiederkehr:** jede zweite Phrase · **Transformationen:** Auflösung verschieben (erst im nächsten Takt)
- **Muss erhalten bleiben:** Reibung mit dem Pedal
- **Verfahren:** Systemfremder Ton als Halbtonnachbar des Pedals [N]; Auflösung auf leichter Zeit [N]. (S5, S7)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): D♭4 V→C4 · C4 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M28 · Ganztonzelle

- **Töne/Dauern:** `C4/4 D4/4 E4/4 D4/4` (Taktart 4/4) · **Kontext:** `C9#5` | `C9#5`
- **Intervalle (Halbtöne):** +2 +2 -2 · **Ambitus:** 4 · **XYZ:** 0,45 / 0,20 / 0,50 (mRm) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** legato · **Kontur:** auf und zurück
- **Wiederkehr:** als Tupfer in Ganztonfeldern · **Transformationen:** Tritonus-Transposition (F♯–G♯–B♭–G♯)
- **Muss erhalten bleiben:** Ganztonschritte
- **Verfahren:** Ganztonmaterial (Vertigo) [N] als Zelle [I]. (S9)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Ganzton-0): C4 A · D4 A · E4 A · D4 A
- **Harmonische Absicht:** nur Akkord- und Vorratstöne; die Spannung liegt im Kontextklang

#### HE-M29 · Übermäßige Achse, gebrochen

- **Töne/Dauern:** `C4/2 E4/2 G#4/2 E4/2 C4/2 E4/2 G#4/4` (Taktart 4/4) · **Kontext:** `Caug` | `Caug`
- **Intervalle (Halbtöne):** +4 +4 -4 -4 +4 +4 · **Ambitus:** 8 · **XYZ:** 0,45 / 0,30 / 0,60 (mRm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** gleichmäßig · **Kontur:** auf und ab um die Achse
- **Wiederkehr:** im Arpeggio, gegenläufig mit sich selbst · **Transformationen:** Krebs in der zweiten Stimme
- **Muss erhalten bleiben:** Symmetrie
- **Verfahren:** Zweitaktige Arpeggiofigur mit Symmetrieachsen, gegenläufig gespiegelt (Vertigo; Cooper, Murphy). (S9, S6)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Ganzton-0): C4 A · E4 A · A♭4 A · E4 A · C4 A · E4 A · A♭4 A
- **Harmonische Absicht:** nur Akkord- und Vorratstöne; die Spannung liegt im Kontextklang
- **Technische Anforderungen:** Kanon/koordinierte Parallelstimmen

#### HE-M30 · Lyrischer Vorhalt, aufwärts sequenziert

- **Töne/Dauern:** `Eb4/6 D4/2 F4/6 Eb4/2 | G4/6 F4/2 Ab4/8` (Taktart 4/4) · **Kontext:** `Cmadd9` | `Ab`
- **Intervalle (Halbtöne):** -1 +3 -2 +4 -2 +3 · **Ambitus:** 6 · **XYZ:** 0,35 / 0,40 / 0,30 (DmS) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** legato, warm · **Kontur:** Vorhaltpaare steigen
- **Wiederkehr:** als Liebes- oder Trauerlinie · **Transformationen:** auf der Stelle wiederholen (HE-M31)
- **Muss erhalten bleiben:** Vorhalt–Auflösung
- **Verfahren:** Lyrische Linie reiht Vorhalt-Auflösungs-Paare aufwärts (Schneller) [N]; Unterschied zur Spannungszelle liegt in Dauer und Richtung [I]. (S7)
- **Färbungsbereich:** X ≤ 0,5 (Sehnsucht, Trauer)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): E♭4 A · D4 A · F4 V→E♭4 · E♭4 A · G4 T · F4 T · A♭4 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M31 · Spannungszelle auf der Stelle

- **Töne/Dauern:** `Eb4/6 D4/2 Eb4/6 D4/2` (Taktart 4/4) · **Kontext:** `CmM7` | `CmM7`
- **Intervalle (Halbtöne):** -1 +1 -1 · **Ambitus:** 1 · **XYZ:** 0,20 / 0,30 / 0,55 (DRm) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** gleich bleibend · **Kontur:** Pendel ohne Fortgang
- **Wiederkehr:** beliebig lange · **Transformationen:** chromatisch verschieben (E–E♭)
- **Muss erhalten bleiben:** Vorhaltpaar
- **Verfahren:** Gleiches Material wie HE-M30, aber wiederholt statt sequenziert: Obsession, Gefangensein [I]. (S7)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): E♭4 A · D4 V→E♭4 · E♭4 A · D4 T
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M32 · Chromatische Abwärtslinie (Gegenstimme zu HE-B08)

- **Töne/Dauern:** `G4/8 F#4/8 | F4/8 E4/8 | Eb4/8 D4/8 | Db4/8 C4/8` (Taktart 4/4) · **Kontext:** `Cm` | `Cm` | `Cm` | `CmM7`
- **Intervalle (Halbtöne):** -1 -1 -1 -1 -1 -1 -1 · **Ambitus:** 7 · **XYZ:** 0,20 / 0,40 / 0,55 (Dmm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** legato · **Kontur:** stetig abwärts
- **Wiederkehr:** einmal, als Konvergenz · **Transformationen:** in Seufzer gliedern (je zwei Töne gebunden)
- **Muss erhalten bleiben:** Abwärtsrichtung gegen steigenden Bass
- **Verfahren:** Absteigende chromatische Sopranlinie gegen steigenden chromatischen Bass, Konvergenz auf einem Hitchcock-Akkord (Psycho, „The Hill“, Husarik). (S3)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): G4 A · F♯4 F · F4 T · E4 V→E♭4 · E♭4 A · D4 T · D♭4 V→C4 · C4 A
- **Harmonische Absicht:** akkordfremde Töne innerhalb der Zelle sind Teil der Gestalt (Halbton- oder Tritonusreibung); Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M33 · Quarte mit Tritonus

- **Töne/Dauern:** `C4/4 F4/4 B4/8` (Taktart 4/4) · **Kontext:** `{C F B}` | `{C F B}`
- **Intervalle (Halbtöne):** +5 +6 · **Ambitus:** 11 · **XYZ:** 0,30 / 0,35 / 0,60 (DRm) · **Evidenz:** Verfahren [E], Töne [E]
- **Artikulation:** tenuto · **Kontur:** Sprungkette aufwärts
- **Wiederkehr:** als Ruf · **Transformationen:** Umkehrung
- **Muss erhalten bleiben:** Quarte + Tritonus
- **Verfahren:** Intervallfigur [E].
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): C4 A · F4 A · B4 A
- **Harmonische Absicht:** nur Akkord- und Vorratstöne; die Spannung liegt im Kontextklang

#### HE-M34 · Weite None abwärts

- **Töne/Dauern:** `Db5/8 C4/8` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** -13 · **Ambitus:** 13 · **XYZ:** 0,15 / 0,50 / 0,50 (Dmm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** schwer · **Kontur:** großer Fall
- **Wiederkehr:** selten · **Transformationen:** Oktave statt None
- **Muss erhalten bleiben:** kleine None
- **Verfahren:** Oktavversetzte Halbtonzelle [N, Psycho]. (S4)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): D♭5 F · C4 A
- **Harmonische Absicht:** akkordfremde Töne innerhalb der Zelle sind Teil der Gestalt (Halbton- oder Tritonusreibung)

#### HE-M35 · Sinkende Registerkette

- **Töne/Dauern:** `G5/4 F#5/4 r/8 | G4/4 F#4/4 r/8 | G3/4 F#3/4 r/8` (Taktart 4/4) · **Kontext:** `Cm` | `Cm` | `Cm`
- **Intervalle (Halbtöne):** -1 -11 -1 -11 -1 · **Ambitus:** 25 · **XYZ:** 0,20 / 0,30 / 0,40 (DRm) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** gleich · **Kontur:** dieselbe Zelle, jede Aussage eine Oktave tiefer
- **Wiederkehr:** einmal pro Abschnitt · **Transformationen:** Abstand der Aussagen vergrößern
- **Muss erhalten bleiben:** Zelle bleibt identisch
- **Verfahren:** Register als Dramaturgie: Motiv sinkt mit jeder Aussage ab (Journey, nach Herrmanns Konzeption tiefer Register) [N/I]. (S15)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): G5 A · F♯5 F · G4 A · F♯4 F · G3 A · F♯3 U
- **Harmonische Absicht:** unaufgelöste Reibung am Ende ist gewollt (nicht harmonisch korrigieren); akkordfremde Töne innerhalb der Zelle sind Teil der Gestalt (Halbton- oder Tritonusreibung)
- **Technische Anforderungen:** Exakte Registervorgabe

#### HE-M36 · Echofragment in hoher Lage

- **Töne/Dauern:** `r/8 Eb6/2 D6/6` (Taktart 4/4) · **Kontext:** `CmM7` | `CmM7`
- **Intervalle (Halbtöne):** -1 · **Ambitus:** 1 · **XYZ:** 0,50 / 0,10 / 0,40 (mRm) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** sehr leise, hart angeschlagen · **Kontur:** Seufzer hoch
- **Wiederkehr:** als Tupfer nach einer tiefen Aussage · **Transformationen:** Halbton höher
- **Muss erhalten bleiben:** Seufzer
- **Verfahren:** Helle Stabspielfarbe als Bedrohung (Sisters, Moreira) [N]; Echo-Anwendung [I]. (S1)
- **Färbungsbereich:** X ≥ 0,5 (Hochlage); für dunkle Kontexte eine oder zwei Oktaven tiefer legen
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): E♭6 A · D6 T
- **Harmonische Absicht:** nur Akkord- und Vorratstöne; die Spannung liegt im Kontextklang

#### HE-M37 · Zwei-Ton-Motiv mit wachsender Pause

- **Töne/Dauern:** `C4/2 Db4/2 r/12 | r/4 C4/2 Db4/2 r/8 | r/16 | C4/2 Db4/2 r/12` (Taktart 4/4) · **Kontext:** `Cm` | `Cm` | `Cm` | `Cm`
- **Intervalle (Halbtöne):** +1 -1 +1 -1 +1 · **Ambitus:** 1 · **XYZ:** 0,20 / 0,15 / 0,55 (DRm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** gleich leise · **Kontur:** Halbtonpaar, immer seltener
- **Wiederkehr:** unregelmäßig · **Transformationen:** Pause schrumpfen lassen (Gegenrichtung)
- **Muss erhalten bleiben:** Zelle
- **Verfahren:** Pausen zur Steuerung des Fortgangs (Psycho, „The Cellar“) [N]. (S4)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): C4 A · D♭4 V→C4 · C4 A · D♭4 V→C4 · C4 A · D♭4 U
- **Harmonische Absicht:** unaufgelöste Reibung am Ende ist gewollt (nicht harmonisch korrigieren); Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M38 · Zelle mit fremdem Halbton

- **Töne/Dauern:** `G4/4 Ab4/4 G4/4 F#4/4` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** +1 -1 -1 · **Ambitus:** 2 · **XYZ:** 0,20 / 0,25 / 0,55 (DRm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** legato · **Kontur:** Nebennoten oben und unten
- **Wiederkehr:** als Tupfer · **Transformationen:** nur die untere Nebennote
- **Muss erhalten bleiben:** Doppelnachbarschaft
- **Verfahren:** Systemfremder Halbtonnachbar [N, Smith]. (S5)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): G4 A · A♭4 V→G4 · G4 A · F♯4 U
- **Harmonische Absicht:** unaufgelöste Reibung am Ende ist gewollt (nicht harmonisch korrigieren); Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M39 · Spieluhr-Fragment mit falschem Ton

- **Töne/Dauern:** `G5/2 E5/2 C5/2 E5/2 G5/2 F#5/2 E5/4` (Taktart 4/4) · **Kontext:** `C` | `Cadd#4`
- **Intervalle (Halbtöne):** -3 -4 +4 +3 -1 -2 · **Ambitus:** 7 · **XYZ:** 0,75 / 0,15 / 0,45 (HRm) · **Evidenz:** Verfahren [E], Töne [E]
- **Artikulation:** hell, mechanisch gleich · **Kontur:** Dreiklangsbrechung, ein Ton daneben
- **Wiederkehr:** zwei- bis dreimal, dann abbrechen · **Transformationen:** falschen Ton an andere Stelle
- **Muss erhalten bleiben:** mechanische Gleichmäßigkeit
- **Verfahren:** Spieluhrfarbe als Bedrohung (Sisters) [N]; Tonfolge eigen. (S1)
- **Färbungsbereich:** X ≥ 0,6 (Spieluhrfarbe)
- **Tonfunktionen** (gegen den Kontextklang, kein gemeinsamer Vorrat – Nicht-Akkordtöne sind Vorhalt, Reibung oder unaufgelöst): G5 A · E5 A · C5 A · E5 A · G5 A · F♯5 A · E5 A
- **Harmonische Absicht:** nur Akkord- und Vorratstöne; die Spannung liegt im Kontextklang

#### HE-M40 · Gereihte Seufzer abwärts

- **Töne/Dauern:** `Ab4/3 G4/5 F4/3 E4/5 | Eb4/3 D4/5 C4/8` (Taktart 4/4) · **Kontext:** `Fm` | `CmM7`
- **Intervalle (Halbtöne):** -1 -2 -1 -1 -1 -2 · **Ambitus:** 8 · **XYZ:** 0,25 / 0,30 / 0,35 (DRS) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** jedes Paar gebunden · **Kontur:** Klage in Stufen
- **Wiederkehr:** als Trauerlinie · **Transformationen:** Paare im Halbtonabstand statt Ganzton
- **Muss erhalten bleiben:** Seufzerpaare
- **Verfahren:** Seufzermotiv [N] gereiht [I]. (S3)
- **Färbungsbereich:** X ≤ 0,5 (Klage)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): A♭4 A · G4 V→F4 · F4 A · E4 V→E♭4 · E♭4 A · D4 V→C4 · C4 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M41 · Fugato-Subjekt

- **Töne/Dauern:** `C3/2 Db3/2 C3/2 B2/2 Bb2/4 A2/4 | Ab2/2 G2/2 Ab2/2 G2/2 F#2/8` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** +1 -1 -1 -1 -1 -1 -1 +1 -1 -1 · **Ambitus:** 7 · **XYZ:** 0,20 / 0,45 / 0,60 (Dmm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** non legato, gleichmäßig · **Kontur:** kreisen, dann chromatisch abwärts
- **Wiederkehr:** Einsätze im Viertaktabstand (HE-R43) · **Transformationen:** Umkehrung für die zweite Stimme
- **Muss erhalten bleiben:** Kopf C–D♭–C–B
- **Verfahren:** Fugato mit Einsätzen in Acht-Takt-Einheiten (Psycho, „The Cellar“). (S4)
- **Färbungsbereich:** X ≤ 0,4 (Tiefe); für helle Kontexte nicht geeignet
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): C3 A · D♭3 V→C3 · C3 A · B2 T · B♭2 T · A2 T · A♭2 V→G2 · G2 A · A♭2 V→G2 · G2 A · F♯2 U
- **Harmonische Absicht:** unaufgelöste Reibung am Ende ist gewollt (nicht harmonisch korrigieren); Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle
- **Technische Anforderungen:** Kanon/koordinierte Parallelstimmen

#### HE-M42 · Leere Abwärtsskala

- **Töne/Dauern:** `C5/2 B4/2 Bb4/2 A4/2 Ab4/2 G4/2 F#4/2 F4/2` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** -1 -1 -1 -1 -1 -1 -1 · **Ambitus:** 7 · **XYZ:** 0,20 / 0,45 / 0,65 (DmU) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** gleichmäßig, ohne Akzente · **Kontur:** chromatisch abwärts
- **Wiederkehr:** als Kontrasubjekt · **Transformationen:** zwei Oktaven
- **Muss erhalten bleiben:** Gleichmäßigkeit
- **Verfahren:** Kontrasubjekte werden zu „leeren“ chromatischen Abwärtsskalen (Psycho, „The Cellar“ ab T. 45). (S4)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): C5 A · B4 T · B♭4 T · A4 T · A♭4 V→G4 · G4 A · F♯4 F · F4 T
- **Harmonische Absicht:** akkordfremde Töne innerhalb der Zelle sind Teil der Gestalt (Halbton- oder Tritonusreibung); Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M43 · Kreisfigur um einen Ton

- **Töne/Dauern:** `C4/2 B3/2 Db4/2 C4/10` (Taktart 4/4) · **Kontext:** `CmM7` | `CmM7`
- **Intervalle (Halbtöne):** -1 +2 -1 · **Ambitus:** 2 · **XYZ:** 0,20 / 0,25 / 0,50 (DRm) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** legato · **Kontur:** Umspielung, Rückkehr
- **Wiederkehr:** beliebig · **Transformationen:** enger (nur B–C)
- **Muss erhalten bleiben:** Rückkehr auf den Mittelton
- **Verfahren:** Doppelnachbar-Zelle [I].
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): C4 A · B3 A · D♭4 V→C4 · C4 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M44 · Oktavsprung mit Halbton

- **Töne/Dauern:** `C4/2 C5/2 Db5/12` (Taktart 4/4) · **Kontext:** `Cm` | `Cm(addb9)`
- **Intervalle (Halbtöne):** +12 +1 · **Ambitus:** 13 · **XYZ:** 0,20 / 0,60 / 0,65 (DmU) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** Sprung akzentuiert · **Kontur:** Sprung, Reibung
- **Wiederkehr:** als Schreckzelle, selten · **Transformationen:** nach unten
- **Muss erhalten bleiben:** Sprung + Halbton
- **Verfahren:** Halbtonzelle registral erweitert [I]. (S4)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, kein gemeinsamer Vorrat – Nicht-Akkordtöne sind Vorhalt, Reibung oder unaufgelöst): C4 A · C5 A · D♭5 U
- **Harmonische Absicht:** unaufgelöste Reibung am Ende ist gewollt (nicht harmonisch korrigieren)

#### HE-M45 · Quartpendel, chromatisch verschoben

- **Töne/Dauern:** `C4/2 F4/2 C4/2 F4/2 Db4/2 F#4/2 Db4/2 F#4/2` (Taktart 4/4) · **Kontext:** `Cm` | `Db/C`
- **Intervalle (Halbtöne):** +5 -5 +5 -4 +5 -5 +5 · **Ambitus:** 6 · **XYZ:** 0,25 / 0,40 / 0,60 (Dmm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** gleichmäßig · **Kontur:** Pendel, Halbton höher
- **Wiederkehr:** als Ostinato · **Transformationen:** zurückverschieben
- **Muss erhalten bleiben:** Quartpendel
- **Verfahren:** Chromatische Verschiebung einer Struktur [N]. (S4)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, kein gemeinsamer Vorrat – Nicht-Akkordtöne sind Vorhalt, Reibung oder unaufgelöst): C4 A · F4 F · C4 A · F4 F · D♭4 A · F♯4 F · D♭4 A · F♯4 U
- **Harmonische Absicht:** unaufgelöste Reibung am Ende ist gewollt (nicht harmonisch korrigieren); akkordfremde Töne innerhalb der Zelle sind Teil der Gestalt (Halbton- oder Tritonusreibung)

#### HE-M46 · Antwort in Umkehrung

- **Töne/Dauern:** `C4/4 Bb3/4 r/8` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** -2 · **Ambitus:** 2 · **XYZ:** 0,25 / 0,25 / 0,45 (DRm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** leise · **Kontur:** zwei Töne abwärts
- **Wiederkehr:** nach HE-M19 · **Transformationen:** Halbton
- **Muss erhalten bleiben:** Gegenrichtung zur Frage
- **Verfahren:** Umkehrung als Variante (Schneller) [N]. (S7)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): C4 A · B♭3 T
- **Harmonische Absicht:** nur Akkord- und Vorratstöne; die Spannung liegt im Kontextklang

#### HE-M47 · Halbtonpendel mit Terzsprung

- **Töne/Dauern:** `A4/4 G#4/4 A4/4 C5/4` (Taktart 4/4) · **Kontext:** `F` | `F`
- **Intervalle (Halbtöne):** -1 +1 +3 · **Ambitus:** 4 · **XYZ:** 0,35 / 0,20 / 0,45 (DRm) · **Evidenz:** Verfahren [E], Töne [E]
- **Artikulation:** gebunden · **Kontur:** Pendel mit Ausbruch
- **Wiederkehr:** über Habanera-Bass · **Transformationen:** C5 durch B4 ersetzen
- **Muss erhalten bleiben:** Pendel
- **Verfahren:** Terzen über Pedal in „Carlotta’s Portrait“ (Wrobel) als Verfahren [N]; Töne eigen. (S12)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): A4 A · A♭4 V→A4 · A4 A · C5 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M48 · Kalter Ruf in hoher Lage

- **Töne/Dauern:** `C6/8 G6/6 F#6/2 | F#6/16` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** +7 -1 +0 · **Ambitus:** 7 · **XYZ:** 0,55 / 0,10 / 0,45 (mRm) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** ohne Vibrato, gleich leise · **Kontur:** Quinte auf, Halbton ab, liegen
- **Wiederkehr:** selten · **Transformationen:** eine Oktave tiefer
- **Muss erhalten bleiben:** lange Dauern
- **Verfahren:** Hohe, reine Liegetöne (Theremin-Funktion, Day the Earth) [N]; Tonfolge eigen. (S1)
- **Färbungsbereich:** X ≥ 0,5 (Hochlage); für dunkle Kontexte eine oder zwei Oktaven tiefer legen
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): C6 A · G6 A · F♯6 F · F♯6 U
- **Harmonische Absicht:** unaufgelöste Reibung am Ende ist gewollt (nicht harmonisch korrigieren); akkordfremde Töne innerhalb der Zelle sind Teil der Gestalt (Halbton- oder Tritonusreibung)

#### HE-M49 · Monumentale Mollzelle tief

- **Töne/Dauern:** `C2/8 G2/4 Ab2/4 | G2/16` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** +7 +1 -1 · **Ambitus:** 8 · **XYZ:** 0,10 / 0,70 / 0,30 (DIS) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** schwer, gehalten · **Kontur:** Quinte, kleine Sexte, zurück
- **Wiederkehr:** als Bassmotiv unter Blöcken · **Transformationen:** Oktave verdoppeln
- **Muss erhalten bleiben:** Halbton über der Quinte
- **Verfahren:** Tiefe Register und Halbtonreibung [N/I]. (S15)
- **Färbungsbereich:** X ≤ 0,3 (tiefe Mollzelle)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): C2 A · G2 A · A♭2 V→G2 · G2 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M50 · Ganztonabstieg

- **Töne/Dauern:** `E5/4 D5/4 C5/4 Bb4/4 | Ab4/16` (Taktart 4/4) · **Kontext:** `{Ab Bb C D E}` | `{Ab Bb C D E}`
- **Intervalle (Halbtöne):** -2 -2 -2 -2 · **Ambitus:** 8 · **XYZ:** 0,60 / 0,30 / 0,45 (mRm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** legato · **Kontur:** fünf Ganztöne abwärts
- **Wiederkehr:** nach Großterzklängen · **Transformationen:** aufwärts
- **Muss erhalten bleiben:** Ganztonfolge
- **Verfahren:** Fünftöniger Ganztonausschnitt (Vertigo, „Dawn“). (S9)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Ganzton-0): E5 A · D5 A · C5 A · B♭4 A · A♭4 A
- **Harmonische Absicht:** nur Akkord- und Vorratstöne; die Spannung liegt im Kontextklang

#### HE-M51 · Liegeton mit Vorschlag

- **Töne/Dauern:** `F#4/1 G4/15` (Taktart 4/4) · **Kontext:** `CmM7` | `CmM7`
- **Intervalle (Halbtöne):** +1 · **Ambitus:** 1 · **XYZ:** 0,25 / 0,15 / 0,45 (DRm) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** Vorschlag kurz · **Kontur:** Halbton von unten, dann liegen
- **Wiederkehr:** als Tupferhaltung · **Transformationen:** Vorschlag von oben
- **Muss erhalten bleiben:** Halbtonvorschlag
- **Verfahren:** Halbtonnachbar zum Liegeton [I].
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): F♯4 V→G4 · G4 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M52 · Abgebrochene Zelle

- **Töne/Dauern:** `Ab4/4 G4/4 F4/4 r/4` (Taktart 4/4) · **Kontext:** `Cm` | `Cm`
- **Intervalle (Halbtöne):** -1 -2 · **Ambitus:** 3 · **XYZ:** 0,25 / 0,25 / 0,55 (DRm) · **Evidenz:** Verfahren [N], Töne [E]
- **Artikulation:** letzter Ton fehlt · **Kontur:** Abstieg ohne Ziel
- **Wiederkehr:** nach mehreren vollständigen Aussagen · **Transformationen:** noch kürzer (zwei Töne)
- **Muss erhalten bleiben:** Kopf
- **Verfahren:** Kürzung des Prototyps [N, Schneller]. (S7)
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): A♭4 V→G4 · G4 A · F4 T
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M53 · Kalter Glockenruf mit Tritonus

- **Töne/Dauern:** `C6/4 F#6/12` (Taktart 4/4) · **Kontext:** `{C G D F#}` | `{C G D F#}`
- **Intervalle (Halbtöne):** +6 · **Ambitus:** 6 · **XYZ:** 0,70 / 0,10 / 0,40 (HRm) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** hart angeschlagen, ausklingen lassen · **Kontur:** Tritonus aufwärts, liegen
- **Wiederkehr:** selten, in großen Abständen · **Transformationen:** Tritonus abwärts; Halbton statt Tritonus (C6–D♭6)
- **Muss erhalten bleiben:** Tritonus und Lage über C6
- **Verfahren:** Hohe, reine Töne als kalte Helligkeit (Day the Earth) [N]; Tritonus als Herrmann-Intervall [N]; Zelle eigen. (S1)
- **Färbungsbereich:** X ≥ 0,5 (Hochlage); tiefer gelegt verliert die Zelle ihre Kälte
- **Tonfunktionen** (gegen den Kontextklang, kein gemeinsamer Vorrat – Nicht-Akkordtöne sind Vorhalt, Reibung oder unaufgelöst): C6 A · F♯6 A
- **Harmonische Absicht:** nur Akkord- und Vorratstöne; die Spannung liegt im Kontextklang

#### HE-M54 · Ganztonspirale hoch

- **Töne/Dauern:** `C6/1 D6/1 E6/1 F#6/1 E6/1 D6/1 C6/1 Bb5/1 Ab5/1 Bb5/1 C6/2` (Taktart 4/4T) · **Kontext:** `C9#5` | `C9#5`
- **Intervalle (Halbtöne):** +2 +2 +2 -2 -2 -2 -2 -2 +2 +2 · **Ambitus:** 10 · **XYZ:** 0,65 / 0,25 / 0,75 (HRU) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** leicht, gleichmäßig · **Kontur:** auf, ab unter den Ausgang, zurück
- **Wiederkehr:** als Tupferlinie im Ganztonfeld · **Transformationen:** Umkehrung (zuerst abwärts); im Halbtonabstand auf der anderen Ganztonreihe
- **Muss erhalten bleiben:** Ganztonschritte und Kreisbewegung
- **Verfahren:** Gegenläufige Spiralen um symmetrische Achsen (Vertigo; Murphy, Cooper) [N]; Ganztonmaterial [N]; Linie eigen. (S6, S9)
- **Färbungsbereich:** X ≥ 0,5 (Hochlage); für dunkle Kontexte eine oder zwei Oktaven tiefer legen
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Ganzton-0): C6 A · D6 A · E6 A · F♯6 V→E6 · E6 A · D6 A · C6 A · B♭5 A · A♭5 A · B♭5 A · C6 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-M55 · Helle Drohzelle ohne Fanfare

- **Töne/Dauern:** `G5/4 C6/4 F#6/8 | F6/16` (Taktart 4/4) · **Kontext:** `C` | `F#/C`
- **Intervalle (Halbtöne):** +5 +6 -1 · **Ambitus:** 11 · **XYZ:** 0,70 / 0,75 / 0,65 (HIU) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** breit, gleich laut, kein Akzent auf dem Zielton · **Kontur:** Quarte auf, Tritonus auf, Halbton ab
- **Wiederkehr:** zwei- bis dreimal mit Pause · **Transformationen:** im Tritonus transponiert
- **Muss erhalten bleiben:** Quarte–Tritonus–Halbton
- **Verfahren:** Keine Dur-Terz, kein Leitton, kein Zielton auf schwerer Zeit: die Zelle klingt hell und groß, aber nicht heroisch [I]; Tritonusbezug [N]. (S1)
- **Färbungsbereich:** X ≥ 0,5; in dunklem Kontext eine Oktave tiefer als Drohruf verwendbar
- **Tonfunktionen** (gegen den Kontextklang, kein gemeinsamer Vorrat – Nicht-Akkordtöne sind Vorhalt, Reibung oder unaufgelöst): G5 A · C6 A · F♯6 F · F6 U
- **Harmonische Absicht:** unaufgelöste Reibung am Ende ist gewollt (nicht harmonisch korrigieren); akkordfremde Töne innerhalb der Zelle sind Teil der Gestalt (Halbton- oder Tritonusreibung)

#### HE-M56 · Breite Großterzlinie

- **Töne/Dauern:** `C5/8 E5/8 | G#5/16` (Taktart 4/4) · **Kontext:** `CaugM7` | `CaugM7`
- **Intervalle (Halbtöne):** +4 +4 · **Ambitus:** 8 · **XYZ:** 0,60 / 0,70 / 0,30 (mIS) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** legato, getragen, laut · **Kontur:** zwei große Terzen aufwärts
- **Wiederkehr:** über Säulenklängen, einmal je Abschnitt · **Transformationen:** abwärts (G♯–E–C)
- **Muss erhalten bleiben:** große Terzen
- **Verfahren:** Großterzzyklus (Vertigo, „Dawn“) als Linie [N/I]. (S9, S5)
- **Färbungsbereich:** X ≥ 0,5 (Hochlage); für dunkle Kontexte eine oder zwei Oktaven tiefer legen
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Hex-C): C5 A · E5 A · A♭5 A
- **Harmonische Absicht:** nur Akkord- und Vorratstöne; die Spannung liegt im Kontextklang

#### HE-M57 · Flirrende Nebennotenzelle hoch

- **Töne/Dauern:** `E6/1 F6/1 E6/1 D#6/1 E6/4 r/8` (Taktart 4/4) · **Kontext:** `C` | `C`
- **Intervalle (Halbtöne):** +1 -1 -1 +1 · **Ambitus:** 2 · **XYZ:** 0,75 / 0,20 / 0,70 (HRU) · **Evidenz:** Verfahren [I], Töne [E]
- **Artikulation:** sehr leise, schnell · **Kontur:** Doppelnachbar um einen Ton
- **Wiederkehr:** unregelmäßig wiederholen · **Transformationen:** Halbtöne durch Ganztöne ersetzen (Ganztonfeld)
- **Muss erhalten bleiben:** Doppelnachbarschaft
- **Verfahren:** Doppelnachbar-Zelle [I] in heller Stabspielfunktion (Sisters) [N]. (S1)
- **Färbungsbereich:** X ≥ 0,5 (Hochlage); für dunkle Kontexte eine oder zwei Oktaven tiefer legen
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Dur): E6 A · F6 V→E6 · E6 A · E♭6 V→E6 · E6 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

## G Phrasen (HE-P01–P21)

Phrasen sind Baupläne für Zellen: Wiederholung, a–a–b, Unterbrechung, Kürzung, Verlängerung, Wiederaufnahme, Transformation, Übergabe zwischen Rollen. Die angegebenen Rollen sind Vorschläge; dieselbe Phrase kann in Tupfer, Gegenstimme oder Kurzem Bass stehen.

#### HE-P01 · Bar-Form a–a–b

- **Taktart:** 4/4 · **Akkorde je Takt:** `CmM7` | `CmM7` | `CmM7` | `Cm7b5` · **XYZ:** 0,25 / 0,30 / 0,45 (DRm)
- **Töne/Dauern:** `Ab4/2 G4/2 F4/2 Eb4/2 r/8 | Ab4/2 G4/2 F4/2 Eb4/2 r/8 | Ab4/2 G4/2 F4/2 Eb4/2 F4/2 Eb4/2 D4/4 | C4/16`
- **Gipfel:** A♭4 in Takt 1, 2, 3 · **Schlusston:** C · **Artikulation:** leise, gleichmäßig
- **Verfahren:** Zelle zweimal gleich, dann Fortspinnung mit Anhang (HE-M03, HE-M22) · **Bauplan:** a (1 T.) – a (1 T.) – b (2 T.) · **Rollen:** GS, TU, HM · **Evidenz:** Verfahren nach HE-M-Quellen, Phrase [E]
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, kein gemeinsamer Vorrat – Nicht-Akkordtöne sind Vorhalt, Reibung oder unaufgelöst): A♭4 V→G4 · G4 A · F4 V→E♭4 · E♭4 A · A♭4 V→G4 · G4 A · F4 V→E♭4 · E♭4 A · A♭4 V→G4 · G4 A · F4 V→E♭4 · E♭4 A · F4 V→E♭4 · E♭4 A · D4 V→C4 · C4 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-P02 · Bar-Form mit verkürztem b

- **Taktart:** 4/4 · **Akkorde je Takt:** `Cm` | `Cm` | `Cm` | `Cm` · **XYZ:** 0,20 / 0,20 / 0,50 (DRm)
- **Töne/Dauern:** `C4/2 Db4/2 r/12 | C4/2 Db4/2 r/12 | C4/2 Db4/2 Eb4/2 r/10 | r/16`
- **Gipfel:** E♭4 in Takt 3 · **Schlusston:** E♭ · **Artikulation:** pp
- **Verfahren:** Zweitonzelle, b nur um einen Ton erweitert · **Bauplan:** a – a – b (kurz) – Pause · **Rollen:** TU, GS · **Evidenz:** Verfahren nach HE-M-Quellen, Phrase [E]
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): C4 A · D♭4 V→C4 · C4 A · D♭4 V→C4 · C4 A · D♭4 V→E♭4 · E♭4 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-P03 · Russische Puppe

- **Taktart:** 4/4 · **Akkorde je Takt:** `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7` · **XYZ:** 0,20 / 0,35 / 0,50 (DRm)
- **Töne/Dauern:** `Eb4/4 D4/4 r/8 | Eb4/4 D4/4 r/8 | Eb4/2 D4/2 C4/2 B3/2 r/8 | Eb4/2 D4/2 C4/2 B3/2 r/8 | Eb4/2 D4/2 C4/2 B3/2 C4/2 B3/2 r/4 | Eb4/2 D4/2 C4/2 B3/2 C4/2 B3/2 r/4 | Eb4/2 D4/2 C4/2 B3/2 C4/2 B3/2 C4/2 B3/2 | C4/16`
- **Gipfel:** E♭4 in Takt 1, 2, 3, 4, 5, 6, 7 · **Schlusston:** C · **Artikulation:** gleichmäßig, immer etwas länger
- **Verfahren:** Zweitonzelle → Viertongruppe → angehängtes Glied (Kompression rückwärts) · **Bauplan:** a a | A A | A+ A+ | A++ | Ziel · **Rollen:** GS, HM · **Evidenz:** Verfahren nach HE-M-Quellen, Phrase [E]
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): E♭4 A · D4 V→E♭4 · E♭4 A · D4 V→E♭4 · E♭4 A · D4 V→C4 · C4 A · B3 A · E♭4 A · D4 V→C4 · C4 A · B3 A · E♭4 A · D4 V→C4 · C4 A · B3 A · C4 A · B3 A · E♭4 A · D4 V→C4 · C4 A · B3 A · C4 A · B3 A · E♭4 A · D4 V→C4 · C4 A · B3 A · C4 A · B3 A · C4 A · B3 A · C4 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-P04 · Unterbrochene Zelle

- **Taktart:** 4/4 · **Akkorde je Takt:** `Cm` | `Cm` | `Db/C` | `Cm` · **XYZ:** 0,25 / 0,35 / 0,60 (DRm)
- **Töne/Dauern:** `Ab4/2 G4/2 F4/2 Eb4/2 r/8 | Ab4/2 G4/2 r/12 | r/16 | Ab4/2 G4/2 F4/2 Eb4/2 r/8`
- **Gipfel:** A♭4 in Takt 1, 2, 4 · **Schlusston:** E♭ · **Artikulation:** p
- **Verfahren:** Prototyp, abgebrochen; ein Takt Interpunktion (KF/ST), dann wieder vollständig · **Bauplan:** a – a(abgebrochen) – Einschnitt – a · **Rollen:** GS, TU · **Evidenz:** Verfahren nach HE-M-Quellen, Phrase [E]
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, kein gemeinsamer Vorrat – Nicht-Akkordtöne sind Vorhalt, Reibung oder unaufgelöst): A♭4 V→G4 · G4 A · F4 V→E♭4 · E♭4 A · A♭4 V→G4 · G4 A · A♭4 V→G4 · G4 A · F4 V→E♭4 · E♭4 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-P05 · Kürzung bei jeder Wiederholung

- **Taktart:** 4/4 · **Akkorde je Takt:** `Cm` | `Cm` | `Cm` | `Cm` · **XYZ:** 0,20 / 0,25 / 0,55 (DRm)
- **Töne/Dauern:** `G4/2 F#4/2 F4/2 E4/2 Eb4/2 D4/6 | G4/2 F#4/2 F4/2 E4/2 r/8 | G4/2 F#4/2 r/12 | G4/2 r/14`
- **Gipfel:** G4 in Takt 1, 2, 3, 4 · **Schlusston:** G · **Artikulation:** leiser werdend
- **Verfahren:** Liquidation einer chromatischen Linie · **Bauplan:** 6 – 4 – 2 – 1 Töne · **Rollen:** GS, TU · **Evidenz:** Verfahren nach HE-M-Quellen, Phrase [E]
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): G4 A · F♯4 F · F4 T · E4 V→E♭4 · E♭4 A · D4 T · G4 A · F♯4 F · F4 T · E4 F · G4 A · F♯4 V→G4 · G4 A
- **Harmonische Absicht:** akkordfremde Töne innerhalb der Zelle sind Teil der Gestalt (Halbton- oder Tritonusreibung); Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-P06 · Verlängerung statt Schluss

- **Taktart:** 4/4 · **Akkorde je Takt:** `Cm` | `Cm` | `G7b9` | `G7b9` · **XYZ:** 0,25 / 0,40 / 0,55 (Dmm)
- **Töne/Dauern:** `Ab4/2 G4/2 F4/2 Eb4/2 r/8 | Ab4/2 G4/2 F4/2 Eb4/2 F4/2 Eb4/2 r/4 | F4/2 Eb4/2 F4/2 Eb4/2 F4/2 Eb4/2 r/4 | D4/16`
- **Gipfel:** A♭4 in Takt 1, 2 · **Schlusston:** D · **Artikulation:** gleichmäßig
- **Verfahren:** Schlussglied wird angehängt und wiederholt · **Bauplan:** a – a+ – Anhang – Ziel · **Rollen:** GS · **Evidenz:** Verfahren nach HE-M-Quellen, Phrase [E]
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): A♭4 V→G4 · G4 A · F4 V→E♭4 · E♭4 A · A♭4 V→G4 · G4 A · F4 V→E♭4 · E♭4 A · F4 V→E♭4 · E♭4 A · F4 A · E♭4 V→F4 · F4 A · E♭4 V→F4 · F4 A · E♭4 V→D4 · D4 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-P07 · Wiederaufnahme nach Pause

- **Taktart:** 4/4 · **Akkorde je Takt:** `CmM7` | `CmM7` | `CmM7` | `CmM7` · **XYZ:** 0,20 / 0,15 / 0,45 (DRm)
- **Töne/Dauern:** `Eb4/6 D4/2 r/8 | r/16 | r/16 | Eb4/6 D4/2 Eb4/6 D4/2`
- **Gipfel:** E♭4 in Takt 1, 4 · **Schlusston:** D · **Artikulation:** pp
- **Verfahren:** Zelle, zwei Takte Stille, Zelle doppelt · **Bauplan:** a – Pause – Pause – a a · **Rollen:** GS, TU · **Evidenz:** Verfahren nach HE-M-Quellen, Phrase [E]
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): E♭4 A · D4 V→E♭4 · E♭4 A · D4 V→E♭4 · E♭4 A · D4 T
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-P08 · Halbton wird große Septime

- **Taktart:** 4/4 · **Akkorde je Takt:** `CmM7` | `CmM7` | `CmM7` | `CmM7` · **XYZ:** 0,20 / 0,40 / 0,60 (Dmm)
- **Töne/Dauern:** `C4/4 Db4/12 | C4/4 Db4/12 | C4/4 Db3/12 | C4/4 Db3/12`
- **Gipfel:** D♭4 in Takt 1, 2 · **Schlusston:** D♭ · **Artikulation:** zweite Hälfte akzentuiert
- **Verfahren:** HE-M01 → HE-M11: gleiche Tonklassen, Halbton aufwärts wird große Septime abwärts · **Bauplan:** a – a – a′ – a′ · **Rollen:** GS, TU · **Evidenz:** Verfahren nach HE-M-Quellen, Phrase [E]
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): C4 A · D♭4 V→C4 · C4 A · D♭4 V→C4 · C4 A · D♭3 F · C4 A · D♭3 U
- **Harmonische Absicht:** unaufgelöste Reibung am Ende ist gewollt (nicht harmonisch korrigieren); akkordfremde Töne innerhalb der Zelle sind Teil der Gestalt (Halbton- oder Tritonusreibung); Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-P09 · Übergabe zwischen Rollen

- **Taktart:** 4/4 · **Akkorde je Takt:** `Cm` | `Cm` | `Cm` | `Cm` · **XYZ:** 0,25 / 0,30 / 0,50 (DRm)
- **Töne/Dauern:** `Ab4/2 G4/2 F4/2 Eb4/2 r/8 | r/8 Ab5/2 G5/2 F5/2 Eb5/2 | r/16 | Ab2/2 G2/2 F2/2 Eb2/2 r/8`
- **Gipfel:** A♭5 in Takt 2 · **Schlusston:** E♭ · **Artikulation:** gleich
- **Verfahren:** Zelle in GS (Takt 1), TU (Takt 2, höher, versetzt), KB (Takt 4, tief) · **Bauplan:** GS → TU → Pause → KB · **Rollen:** GS, TU, KB · **Evidenz:** Verfahren nach HE-M-Quellen, Phrase [E]
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): A♭4 V→G4 · G4 A · F4 V→E♭4 · E♭4 A · A♭5 V→G5 · G5 A · F5 V→E♭5 · E♭5 A · A♭2 V→G2 · G2 A · F2 V→E♭2 · E♭2 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle
- **Technische Anforderungen:** Rollenwanderung

#### HE-P10 · Dreitaktige Phrase

- **Taktart:** 4/4 · **Akkorde je Takt:** `Cm7b5` | `Bm7b5` | `Bbm7b5` · **XYZ:** 0,20 / 0,30 / 0,50 (DRm)
- **Töne/Dauern:** `Eb4/4 D4/4 C4/8 | D4/4 Db4/4 B3/8 | Db4/4 C4/4 Bb3/8`
- **Gipfel:** E♭4 in Takt 1 · **Schlusston:** B♭ · **Artikulation:** legato
- **Verfahren:** Seufzerpaare über sinkenden Klängen; drei Takte gegen Vierererwartung · **Bauplan:** a – a′ – a″ (je einen Halbton tiefer) · **Rollen:** GS, HM · **Evidenz:** Verfahren nach HE-M-Quellen, Phrase [E]
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, kein gemeinsamer Vorrat – Nicht-Akkordtöne sind Vorhalt, Reibung oder unaufgelöst): E♭4 A · D4 V→C4 · C4 A · D4 A · D♭4 V→B3 · B3 A · D♭4 A · C4 V→B♭3 · B♭3 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-P11 · Frage mit immer kürzerer Antwort

- **Taktart:** 4/4 · **Akkorde je Takt:** `Cm` | `Cm` | `Cm` | `Cm` · **XYZ:** 0,25 / 0,25 / 0,50 (DRm)
- **Töne/Dauern:** `C4/4 D4/4 r/8 | r/8 Eb4/2 Db4/6 | C4/4 D4/4 r/8 | r/12 Eb4/4`
- **Gipfel:** E♭4 in Takt 2, 4 · **Schlusston:** E♭ · **Artikulation:** leise
- **Verfahren:** HE-M19 + HE-M20, zweite Antwort nur ein Ton · **Bauplan:** Frage – Antwort – Frage – Rest · **Rollen:** GS, TU · **Evidenz:** Verfahren nach HE-M-Quellen, Phrase [E]
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): C4 A · D4 V→E♭4 · E♭4 A · D♭4 V→C4 · C4 A · D4 V→E♭4 · E♭4 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-P12 · Sequenz auf der Stelle

- **Taktart:** 4/4 · **Akkorde je Takt:** `CmM7` | `C#mM7` | `CmM7` | `C#mM7` · **XYZ:** 0,20 / 0,35 / 0,60 (DRm)
- **Töne/Dauern:** `Eb4/6 D4/2 r/8 | E4/6 Eb4/2 r/8 | Eb4/6 D4/2 r/8 | E4/6 Eb4/2 r/8`
- **Gipfel:** E4 in Takt 2, 4 · **Schlusston:** E♭ · **Artikulation:** gleich bleibend
- **Verfahren:** Spannungszelle chromatisch verschoben und zurück · **Bauplan:** a – a(+1) – a – a(+1) · **Rollen:** GS · **Evidenz:** Verfahren nach HE-M-Quellen, Phrase [E]
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, kein gemeinsamer Vorrat – Nicht-Akkordtöne sind Vorhalt, Reibung oder unaufgelöst): E♭4 A · D4 V→E4 · E4 A · E♭4 F · E♭4 A · D4 V→E4 · E4 A · E♭4 U
- **Harmonische Absicht:** unaufgelöste Reibung am Ende ist gewollt (nicht harmonisch korrigieren); akkordfremde Töne innerhalb der Zelle sind Teil der Gestalt (Halbton- oder Tritonusreibung); Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-P13 · Lyrische Sequenz aufwärts

- **Taktart:** 4/4 · **Akkorde je Takt:** `Cmadd9` | `Ab` | `Fm9` | `CmM7` · **XYZ:** 0,30 / 0,40 / 0,30 (DmS)
- **Töne/Dauern:** `Eb4/6 D4/2 F4/6 Eb4/2 | G4/6 F4/2 Ab4/8 | C5/6 Bb4/2 Ab4/4 G4/4 | B4/16`
- **Gipfel:** C5 in Takt 3 · **Schlusston:** B · **Artikulation:** legato, warm
- **Verfahren:** Vorhaltpaare steigen, Ziel große Septime · **Bauplan:** a – a(höher) – Gipfel – Ziel ohne Auflösung · **Rollen:** HM, GS · **Evidenz:** Verfahren nach HE-M-Quellen, Phrase [E]
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): E♭4 A · D4 A · F4 V→E♭4 · E♭4 A · G4 T · F4 T · A♭4 A · C5 A · B♭4 V→A♭4 · A♭4 A · G4 A · B4 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-P14 · Liquidation über acht Takte

- **Taktart:** 4/4 · **Akkorde je Takt:** `Cm` | `Cm` | `Cm` | `Cm` | `Cm` | `Cm` | `Cm` | `Cm` · **XYZ:** 0,20 / 0,25 / 0,50 (DRm)
- **Töne/Dauern:** `Ab4/2 G4/2 F4/2 Eb4/2 F4/2 Eb4/2 D4/4 | Ab4/2 G4/2 F4/2 Eb4/2 r/8 | Ab4/2 G4/2 F4/2 Eb4/2 r/8 | Ab4/2 G4/2 r/12 | Ab4/2 G4/2 r/12 | r/16 | Ab4/6 G4/2 r/8 | r/16`
- **Gipfel:** A♭4 in Takt 1, 2, 3, 4, 5, 7 · **Schlusston:** G · **Artikulation:** immer leiser
- **Verfahren:** Fünfton → Vierton → Seufzer allein · **Bauplan:** b – a – a – c – c – Pause – Seufzer – Pause · **Rollen:** GS, TU · **Evidenz:** Verfahren nach HE-M-Quellen, Phrase [E]
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): A♭4 V→G4 · G4 A · F4 V→E♭4 · E♭4 A · F4 V→E♭4 · E♭4 A · D4 T · A♭4 V→G4 · G4 A · F4 V→E♭4 · E♭4 A · A♭4 V→G4 · G4 A · F4 V→E♭4 · E♭4 A · A♭4 V→G4 · G4 A · A♭4 V→G4 · G4 A · A♭4 V→G4 · G4 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-P15 · Dritte Aussage um einen Schlag verschoben

- **Taktart:** 4/4 · **Akkorde je Takt:** `Cm` | `Cm` | `Cm` | `Cm` · **XYZ:** 0,25 / 0,40 / 0,70 (DmU)
- **Töne/Dauern:** `Ab4/4 G4/4 Gb4/8 | Ab4/4 G4/4 Gb4/8 | r/4 Ab4/4 G4/4 Gb4/4 | r/16`
- **Gipfel:** A♭4 in Takt 1, 2, 3 · **Schlusston:** F♯ · **Artikulation:** tenuto
- **Verfahren:** HE-M08 dreimal, die dritte verspätet und verkürzt · **Bauplan:** a – a – a(verschoben) – Pause · **Rollen:** GS, HM · **Evidenz:** Verfahren nach HE-M-Quellen, Phrase [E]
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): A♭4 V→G4 · G4 A · F♯4 F · A♭4 V→G4 · G4 A · F♯4 F · A♭4 V→G4 · G4 A · F♯4 U
- **Harmonische Absicht:** unaufgelöste Reibung am Ende ist gewollt (nicht harmonisch korrigieren); akkordfremde Töne innerhalb der Zelle sind Teil der Gestalt (Halbton- oder Tritonusreibung); Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-P16 · Kanon im Abstand einer Halben

- **Taktart:** 4/4 · **Akkorde je Takt:** `CmM7` | `CmM7` | `CmM7` | `CmM7` · **XYZ:** 0,20 / 0,40 / 0,60 (Dmm)
- **Töne/Dauern:** `C4/2 Db4/2 C4/2 B3/2 Bb3/4 A3/4 | Ab3/2 G3/2 Ab3/2 G3/2 F#3/8 | r/8 C4/2 Db4/2 C4/2 B3/2 | Bb3/4 A3/4 Ab3/8`
- **Gipfel:** D♭4 in Takt 1, 3 · **Schlusston:** A♭ · **Artikulation:** non legato
- **Verfahren:** Subjekt HE-M41 (eine Oktave höher); zweiter Einsatz in einer anderen Rolle (hier im selben Strang versetzt notiert) · **Bauplan:** Subjekt – Subjekt versetzt · **Rollen:** KB, GS · **Evidenz:** Verfahren nach HE-M-Quellen, Phrase [E]
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): C4 A · D♭4 V→C4 · C4 A · B3 A · B♭3 T · A3 T · A♭3 V→G3 · G3 A · A♭3 V→G3 · G3 A · F♯3 F · C4 A · D♭4 V→C4 · C4 A · B3 A · B♭3 T · A3 T · A♭3 T
- **Harmonische Absicht:** akkordfremde Töne innerhalb der Zelle sind Teil der Gestalt (Halbton- oder Tritonusreibung); Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle
- **Technische Anforderungen:** Kanon/koordinierte Parallelstimmen

#### HE-P17 · Sinkende Phrase

- **Taktart:** 4/4 · **Akkorde je Takt:** `Cm` | `Cm` | `Cm` | `Cm` · **XYZ:** 0,15 / 0,30 / 0,40 (DRm)
- **Töne/Dauern:** `G5/4 F#5/4 r/8 | G4/4 F#4/4 r/8 | G3/4 F#3/4 r/8 | G2/16`
- **Gipfel:** G5 in Takt 1 · **Schlusston:** G · **Artikulation:** gleich laut
- **Verfahren:** HE-M35, Schluss auf dem tiefsten Ton · **Bauplan:** a(hoch) – a – a(tief) – Liegeton · **Rollen:** GS → KB · **Evidenz:** Verfahren nach HE-M-Quellen, Phrase [E]
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): G5 A · F♯5 F · G4 A · F♯4 F · G3 A · F♯3 F · G2 A
- **Harmonische Absicht:** akkordfremde Töne innerhalb der Zelle sind Teil der Gestalt (Halbton- oder Tritonusreibung)
- **Technische Anforderungen:** Exakte Registervorgabe, Rollenwanderung

#### HE-P18 · Bar-Form 4 + 4 + 4 + 1 als Melodieplan

- **Taktart:** 4/4 · **Akkorde je Takt:** `CmM7` | `CmM7` | `CmM7` | `CmM7` | `AbmM7/C` | `AbmM7/C` | `AbmM7/C` | `AbmM7/C` | `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7` · **XYZ:** 0,25 / 0,25 / 0,50 (DRm)
- **Töne/Dauern:** `Eb4/6 D4/2 r/8 | r/16 | Eb4/6 D4/2 C4/8 | r/16 | Eb4/6 D4/2 r/8 | r/16 | Eb4/6 D4/2 C4/8 | r/16 | Eb4/6 D4/2 C4/4 B3/4 | C4/6 B3/2 r/8 | Eb4/6 D4/2 C4/4 B3/4 | r/16 | C4/16`
- **Gipfel:** E♭4 in Takt 1, 3, 5, 7, 9, 11 · **Schlusston:** C · **Artikulation:** pp
- **Verfahren:** Vierergruppen aus Seufzer und Pause; drittes Glied länger, ein einzelner Schlusstakt · **Bauplan:** 4 + 4 + 4 + 1 · **Rollen:** GS, TU · **Evidenz:** Verfahren nach HE-M-Quellen, Phrase [E]
- **Färbungsbereich:** alle X; Oktavlage nach X wählen (hoch = hell, tief = dunkel)
- **Tonfunktionen** (gegen den Kontextklang, Vorrat Moll gesamt): E♭4 A · D4 V→E♭4 · E♭4 A · D4 V→C4 · C4 A · E♭4 A · D4 V→E♭4 · E♭4 A · D4 V→C4 · C4 A · E♭4 A · D4 V→C4 · C4 A · B3 A · C4 A · B3 A · E♭4 A · D4 V→C4 · C4 A · B3 A · C4 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-P19 · Kalte Mystery-Phrase

- **Taktart:** 4/4 · **Akkorde je Takt:** `{C G D F#}` | `{C G D F#}` | `{C G D F#}` | `{C G D F#}` · **XYZ:** 0,70 / 0,10 / 0,40 (HRm)
- **Töne/Dauern:** `C6/4 F#6/12 | r/16 | C6/4 F#6/12 | C6/4 Db6/12`
- **Gipfel:** F♯6 in Takt 1, 3 · **Schlusston:** D♭ · **Artikulation:** hart angeschlagen, ausklingen
- **Verfahren:** HE-M53 zweimal, beim dritten Mal Halbton statt Tritonus · **Bauplan:** a – Pause – a – a′ · **Rollen:** TU, GS · **Evidenz:** Verfahren nach HE-M-Quellen, Phrase [E]
- **Färbungsbereich:** X ≥ 0,5 (Hochlage); für dunkle Kontexte eine oder zwei Oktaven tiefer legen
- **Tonfunktionen** (gegen den Kontextklang, kein gemeinsamer Vorrat – Nicht-Akkordtöne sind Vorhalt, Reibung oder unaufgelöst): C6 A · F♯6 A · C6 A · F♯6 A · C6 A · D♭6 U
- **Harmonische Absicht:** unaufgelöste Reibung am Ende ist gewollt (nicht harmonisch korrigieren)

#### HE-P20 · Surreale Spirale mit Abbruch

- **Taktart:** 4/4T · **Akkorde je Takt:** `C9#5` | `C9#5` | `Db9#5` | `C9#5` · **XYZ:** 0,60 / 0,25 / 0,75 (mRU)
- **Töne/Dauern:** `C6/1 D6/1 E6/1 F#6/1 E6/1 D6/1 C6/1 Bb5/1 Ab5/1 Bb5/1 C6/2 | C6/1 D6/1 E6/1 F#6/1 E6/1 D6/1 r/6 | Db6/1 Eb6/1 F6/1 G6/1 F6/1 Eb6/1 Db6/1 B5/1 A5/1 B5/1 Db6/2 | r/12`
- **Gipfel:** G6 in Takt 3 · **Schlusston:** D♭ · **Artikulation:** leicht
- **Verfahren:** HE-M54, abgebrochen, dann auf der anderen Ganztonreihe vollständig · **Bauplan:** a – a(abgebrochen) – a(+1) – Pause · **Rollen:** TU, AR, GS · **Evidenz:** Verfahren nach HE-M-Quellen, Phrase [E]
- **Färbungsbereich:** X ≥ 0,5 (Hochlage); für dunkle Kontexte eine oder zwei Oktaven tiefer legen
- **Tonfunktionen** (gegen den Kontextklang, kein gemeinsamer Vorrat – Nicht-Akkordtöne sind Vorhalt, Reibung oder unaufgelöst): C6 A · D6 A · E6 A · F♯6 V→E6 · E6 A · D6 A · C6 A · B♭5 A · A♭5 A · B♭5 A · C6 A · C6 A · D6 A · E6 A · F♯6 V→E6 · E6 A · D6 A · D♭6 A · E♭6 A · F6 A · G6 V→F6 · F6 A · E♭6 A · D♭6 A · B5 A · A5 A · B5 A · D♭6 A
- **Harmonische Absicht:** Vorhalte bzw. Durchgänge lösen sich stufenweise auf; die Auflösung gehört zur Zelle

#### HE-P21 · Helle Bedrohung, breit

- **Taktart:** 4/4 · **Akkorde je Takt:** `C` | `C` | `F#/C` | `F#/C` · **XYZ:** 0,70 / 0,75 / 0,60 (HIm)
- **Töne/Dauern:** `G5/4 C6/4 F#6/8 | F6/16 | G5/4 C6/4 F#6/8 | F#6/16`
- **Gipfel:** F♯6 in Takt 1, 3, 4 · **Schlusston:** F♯ · **Artikulation:** breit, gleich laut
- **Verfahren:** HE-M55, zweites Mal ohne Halbtonfall (bleibt im Tritonus stehen) · **Bauplan:** a – a′ · **Rollen:** GS, HM · **Evidenz:** Verfahren nach HE-M-Quellen, Phrase [E]
- **Färbungsbereich:** X ≥ 0,5 (Hochlage); für dunkle Kontexte eine oder zwei Oktaven tiefer legen
- **Tonfunktionen** (gegen den Kontextklang, kein gemeinsamer Vorrat – Nicht-Akkordtöne sind Vorhalt, Reibung oder unaufgelöst): G5 A · C6 A · F♯6 F · F6 F · G5 F · C6 A · F♯6 A · F♯6 A
- **Harmonische Absicht:** akkordfremde Töne innerhalb der Zelle sind Teil der Gestalt (Halbton- oder Tritonusreibung)

## H Modellstudien (HE-S01–S40)

Jede Studie ist als MIDI-Datei (`<ID>.mid`, eine Spur je Rolle) und in der CSV enthalten. Die Rasterspalte zeigt das kürzeste wiederkehrende Muster; ausgeschrieben steht jede Note in der CSV. Vier Paare bzw. Gruppen führen vor, dass **dasselbe harmonische Material** seine Wirkung durch Register, Schichtung, Synchronität und Artikulationslänge ändert – bei gleicher Velocity und gleicher Notenzahl:

| Studien | gleiches Material | was sich ändert | Noten |
|---|---|---|---|
| HE-S01 → HE-S02 | C-Moll mit großer Septime, Pedal C | Artikulation (zwei Takte → Halbe), Synchronität, Register des Tupfers | 20 / 20 |
| HE-S06 → HE-S07 | F♯-Moll über C-Moll | Register (Abstand > Oktave → ineinander), Synchronität, Artikulation | 24 / 24 |
| HE-S22 (16 Takte) | H-Moll über C-Moll | Lage und Einsatzzeit der oberen Schicht, sonst nichts | 104 |
| HE-S27 (16 Takte) | H-Moll über C-Moll | vier Abschnitte: getrennt → enges Register → zusätzlich synchron → zusätzlich kurz | 96 (je 24) |

### Langfristige Entwicklung: zwei Arten

Die Studien über 16 und 32 Takte unterscheiden **Entwicklung bei stehender Position** (die Anwenderposition bleibt; variiert werden Rolle, Lage, Pendelklang, Zelle – Klangdichte und Velocity bleiben im selben Band) und **Entwicklung durch eine tatsächliche XYZ-Fahrt** (der Anwender bewegt X, Y oder Z; die Studie zeigt, welche Parameter sich in welcher Reihenfolge ändern). Bei stehender Position gibt es weder erzwungene Eskalation noch erzwungene Beruhigung. Kennzahlen je Abschnitt: Einsätze pro Takt, mittlere Velocity, mittlere Tonhöhe (MIDI), mittlere Zahl gleichzeitig klingender Töne (ohne Stich).

| Studie | Takte | Art | Abschnitt | Einsätze/Takt | Velocity | Tonhöhe | klingende Töne |
|---|---|---|---|---|---|---|---|
| HE-S21 | 16 | Fahrt (Y, Z steigen) | 1–4 | 6,0 | 58 | 38 | 1,0 |
| HE-S21 | 16 | Fahrt (Y, Z steigen) | 5–8 | 12,0 | 56 | 48 | 2,0 |
| HE-S21 | 16 | Fahrt (Y, Z steigen) | 9–12 | 19,5 | 56 | 54 | 4,1 |
| HE-S21 | 16 | Fahrt (Y, Z steigen) | 13–16 | 19,2 | 55 | 55 | 4,0 |
| HE-S22 | 16 | Fahrt (Y steigt nur über Verschmelzung) | 1–4 | 6,5 | 46 | 66 | 4,8 |
| HE-S22 | 16 | Fahrt (Y steigt nur über Verschmelzung) | 5–8 | 6,5 | 46 | 61 | 4,8 |
| HE-S22 | 16 | Fahrt (Y steigt nur über Verschmelzung) | 9–12 | 6,5 | 46 | 55 | 5,1 |
| HE-S22 | 16 | Fahrt (Y steigt nur über Verschmelzung) | 13–16 | 6,5 | 46 | 50 | 5,5 |
| HE-S23 | 16 | Fahrt (Y, Z steigen in vier Hebeln) | 1–4 | 6,5 | 47 | 71 | 3,8 |
| HE-S23 | 16 | Fahrt (Y, Z steigen in vier Hebeln) | 5–8 | 6,0 | 50 | 57 | 3,8 |
| HE-S23 | 16 | Fahrt (Y, Z steigen in vier Hebeln) | 9–12 | 24,5 | 58 | 49 | 4,3 |
| HE-S23 | 16 | Fahrt (Y, Z steigen in vier Hebeln) | 13–16 | 30,5 | 72 | 51 | 4,7 |
| HE-S24 | 16 | stehend | 1–4 | 11,5 | 66 | 66 | 1,7 |
| HE-S24 | 16 | stehend | 5–8 | 11,0 | 60 | 68 | 1,9 |
| HE-S24 | 16 | stehend | 9–12 | 11,5 | 66 | 66 | 1,7 |
| HE-S24 | 16 | stehend | 13–16 | 14,0 | 73 | 67 | 2,1 |
| HE-S25 | 32 | stehend | 1–8 | 18,5 | 44 | 66 | 2,7 |
| HE-S25 | 32 | stehend | 9–16 | 8,6 | 40 | 73 | 4,7 |
| HE-S25 | 32 | stehend | 17–24 | 8,6 | 39 | 46 | 4,5 |
| HE-S25 | 32 | stehend | 25–32 | 20,5 | 42 | 66 | 2,8 |
| HE-S26 | 32 | stehend | 1–8 | 2,5 | 38 | 60 | 3,8 |
| HE-S26 | 32 | stehend | 9–16 | 2,8 | 37 | 59 | 3,8 |
| HE-S26 | 32 | stehend | 17–24 | 2,5 | 38 | 57 | 4,0 |
| HE-S26 | 32 | stehend | 25–32 | 2,4 | 38 | 61 | 3,8 |
| HE-S27 | 16 | Fahrt (Vorführung: Y über Verschmelzung) | 1–4 | 6,0 | 50 | 69 | 4,5 |
| HE-S27 | 16 | Fahrt (Vorführung: Y über Verschmelzung) | 5–8 | 6,0 | 50 | 51 | 4,5 |
| HE-S27 | 16 | Fahrt (Vorführung: Y über Verschmelzung) | 9–12 | 6,0 | 50 | 51 | 6,0 |
| HE-S27 | 16 | Fahrt (Vorführung: Y über Verschmelzung) | 13–16 | 6,0 | 50 | 51 | 3,0 |
| HE-S40 | 16 | stehend | 1–4 | 13,5 | 39 | 84 | 4,0 |
| HE-S40 | 16 | stehend | 5–8 | 13,5 | 39 | 94 | 4,0 |
| HE-S40 | 16 | stehend | 9–12 | 13,5 | 39 | 94 | 4,0 |
| HE-S40 | 16 | stehend | 13–16 | 13,5 | 39 | 84 | 4,0 |

Lesart: In HE-S22 bleiben Einsätze und Velocity gleich; es sinkt nur die obere Schicht, wodurch die Schichten länger gleichzeitig klingen (Verschmelzung). In HE-S27 ändern sich bei gleichen Einsätzen und gleicher Velocity nacheinander Lage, Synchronität (mehr gleichzeitig klingende Töne) und Notenlänge (weniger klingende Töne, aber akuter Schlag). In HE-S24, HE-S26 und HE-S40 wechseln die Kennzahlen innerhalb eines Bandes, ohne Richtung. In HE-S25 schwanken die Einsätze pro Takt mit der Station (Akkordschläge gegenüber Einzeltönen); die Zahl klingender Töne und die Velocity gleichen das aus – es ist ein Wechsel der Gestalt, keine Beruhigung und keine Steigerung. HE-S21 und HE-S23 steigen, weil die Anwenderposition steigt.

Übersicht:

| ID | Name | Takte | XYZ | Ecke | HM | GS | Rollen |
|---|---|---|---|---|---|---|---|
| HE-S01 | Latente Bedrohung ohne Melodie | 8 | 0,20 / 0,20 / 0,40 | DRS | — | — | LF LB TU |
| HE-S02 | Derselbe Klang, kurz und gleichzeitig | 8 | 0,20 / 0,40 / 0,55 | DRU | — | — | KF KB TU |
| HE-S03 | Statisches Unbehagen, hell | 8 | 0,55 / 0,20 / 0,55 | HRU | — | — | LF LB TU |
| HE-S04 | Obsessive Spannung um ein Binnenpedal | 8 | 0,30 / 0,20 / 0,65 | DRU | — | — | KF LB TU |
| HE-S05 | Chromatische Gegenbewegung mit Konvergenz | 8 | 0,20 / 0,35 / 0,55 | DRU | — | ja | LF LB TU GS |
| HE-S06 | Polychord in getrennten Schichten | 8 | 0,15 / 0,25 / 0,65 | DRU | — | — | LF AR |
| HE-S07 | Derselbe Polychord, verschmolzen | 8 | 0,15 / 0,70 / 0,70 | DIU | — | — | LF KF |
| HE-S08 | Polyklang-Pendel mit Registertausch | 8 | 0,25 / 0,30 / 0,55 | DRU | — | — | LF KF |
| HE-S09 | Kalte Helligkeit zwischen zwei Pedalen | 8 | 0,60 / 0,15 / 0,40 | HRS | — | — | LF LB TU |
| HE-S10 | Schwindel: gegenläufige Spiralen | 8 | 0,55 / 0,30 / 0,75 | HRU | — | — | LF AR TU |
| HE-S11 | Spieluhr mit falschem Ton | 8 | 0,75 / 0,15 / 0,45 | HRS | — | ja | KB AR GS |
| HE-S12 | Geheimnisvolles Staunen | 8 | 0,75 / 0,60 / 0,30 | HIS | — | — | LF LB AR |
| HE-S13 | Kalte Spannung in Hemiolen | 8 | 0,70 / 0,75 / 0,80 | HIU | — | — | KF KB ST |
| HE-S14 | Dunkle Monumentalität | 8 | 0,10 / 0,85 / 0,30 | DIS | — | — | LF LB KB |
| HE-S15 | Akuter Horror: Kaskade und verschränkte Tritoni | 8 | 0,15 / 0,90 / 0,80 | DIU | — | — | KF KB AR TU ST |
| HE-S16 | Tragik | 8 | 0,25 / 0,25 / 0,25 | DRS | — | ja | LF LB GS |
| HE-S17 | Paranoia | 8 | 0,20 / 0,25 / 0,75 | DRU | — | — | KF KB TU |
| HE-S18 | Fremder Ort | 8 | 0,50 / 0,20 / 0,55 | HRU | — | — | LF LB AR TU |
| HE-S19 | Lebloser Tanz | 8 | 0,25 / 0,20 / 0,40 | DRS | — | — | LF LB AR TU |
| HE-S20 | Puls statt Rhythmus | 8 | 0,20 / 0,25 / 0,45 | DRS | — | — | KF TU |
| HE-S21 | Fugato als Spannungsmaschine | 16 | 0,20 / 0,40 / 0,60 → 0,20 / 0,60 / 0,75 | DRU | ja | ja | LB KB TU GS HM |
| HE-S22 | Langsam wachsende Bedrohung durch Verschmelzung | 16 | 0,15 / 0,30 / 0,60 → 0,15 / 0,70 / 0,70 | DRU | — | — | LF KF LB |
| HE-S23 | Eskalation in vier Stufen | 16 | 0,15 / 0,40 / 0,60 → 0,20 / 0,90 / 0,85 | DRU | — | — | LF KF KB TU ST |
| HE-S24 | Modul-Labyrinth | 16 | 0,25 / 0,50 / 0,65 | DIU | — | — | KF LB KB AR |
| HE-S25 | Obsession über 32 Takte | 32 | 0,30 / 0,25 / 0,60 | DRU | — | ja | LF KF LB KB AR TU GS |
| HE-S26 | Gleichbleibende latente Spannung über 32 Takte | 32 | 0,20 / 0,15 / 0,40 | DRS | — | — | LF LB TU |
| HE-S27 | Ein Material, vier Behandlungen | 16 | 0,15 / 0,25 / 0,55 → 0,15 / 0,60 / 0,65 | DRU | — | — | LF KF |
| HE-S28 | Frage und Antwort im Thriller | 8 | 0,25 / 0,45 / 0,55 | DRU | — | — | LF KF KB |
| HE-S29 | Mystery: Ein Ton, vier Bedeutungen | 8 | 0,30 / 0,20 / 0,50 | DRU | — | — | LF LB TU |
| HE-S30 | Dunkles Drama | 8 | 0,30 / 0,45 / 0,35 | DRS | ja | ja | LF LB GS HM |
| HE-S31 | Fast nichts | 8 | 0,20 / 0,10 / 0,35 | DRS | — | — | LF TU |
| HE-S32 | Gegenstimme als zweite Polyschicht | 8 | 0,20 / 0,20 / 0,60 | DRU | — | ja | KF LB GS |
| HE-S33 | Hemiolen-Unruhe im Tritonuspendel | 8 | 0,50 / 0,60 / 0,80 | HIU | — | — | KF KB TU |
| HE-S34 | Homorhythmik zerbricht | 8 | 0,15 / 0,75 / 0,85 | DIU | — | — | KF LB KB AR |
| HE-S35 | Kalte, helle Mystery | 8 | 0,70 / 0,15 / 0,40 | HRS | — | — | LF LB AR TU |
| HE-S36 | Helle, surreale Unruhe | 8 | 0,65 / 0,30 / 0,75 | HRU | — | — | LF AR TU |
| HE-S37 | Kraftvoll und ruhig: dunkle Polychord-Säulen | 8 | 0,15 / 0,80 / 0,25 | DIS | — | — | LF KF LB |
| HE-S38 | Helle Bedrohung ohne Heldenton | 8 | 0,70 / 0,80 / 0,70 | HIU | — | ja | KF KB ST GS |
| HE-S39 | Hell, kraftvoll, stabil: kalte Erhabenheit | 8 | 0,65 / 0,75 / 0,30 | HIS | — | ja | LF LB AR GS |
| HE-S40 | Surreale Unruhe bei stehender Position (16 Takte) | 16 | 0,60 / 0,25 / 0,70 | HRU | — | — | LF AR TU |

### HE-S01 · Latente Bedrohung ohne Melodie

- **Charakter:** Ein Zimmer, in dem jemand war. Nichts bewegt sich, aber der Klang stimmt nicht.
- **XYZ-Anker:** 0,20 / 0,20 / 0,40 (DRm) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 54–66 (MIDI-Beispiel ♩ = 60) · **Harmonik:** HE-H01 · **Tonvorrat:** Moll harm.
- **Akkorde je Takt:** `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------\|----------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 51, 3 Stimmen | 1–8 | 42 |
| LB Langer Bass | `x---------------\|----------------  (wiederholt)` | fest: C2 | 1–8 | 45 |
| TU Tupfer | `......x.........\|................\|..........x.....\|................\|...x............\|................\|.............x..\|................` | oberster Akkordton ab MIDI 79, dann abwärts zyklisch | 1–8 | 38 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Arpeggio, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ○ ● ○ ● ○ ● ○
LB   ● ○ ● ○ ● ○ ● ○
TU   ● · ● · ● · ● ·
```

- **Zusammenhang der Rollen:** Ein einziger Klang über acht Takte. Pedal und Fläche liegen, die Tupfer setzen nie auf einer Zählzeit ein und nie zweimal an derselben Stelle. Die Reibung B–C steckt im Klang selbst; es muss nichts geschehen.
- **Dynamik:** pp; Tupfer leiser als die Fläche. · **Pausen:** Ein Tupfer je zwei Takte, nie auf einer Zählzeit; zwischen den Flächen-Neuansätzen zwei Takte.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** Septime B in die Oberstimme (reg 59) legen; Tupfer-Positionen neu verteilen. · **Fortsetzung:** HE-S02 (gleiches Material, verschmolzen) oder HE-T08.
- **Bezug:** HE-H01, HE-R18, HE-B01
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 0 3 0 3 0 3 0; keine Melodierolle; MIDI `HE-S01.mid`, 20 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte

### HE-S02 · Derselbe Klang, kurz und gleichzeitig

- **Charakter:** Dieselben Töne wie HE-S01, aber als Signal: alle zwei Takte ein kurzer, gemeinsamer Schlag.
- **XYZ-Anker:** 0,20 / 0,40 / 0,55 (Dmm) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 54–66 (MIDI-Beispiel ♩ = 60) · **Harmonik:** HE-H01 · **Tonvorrat:** Moll harm.
- **Akkorde je Takt:** `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `x-------........\|................  (wiederholt)` | Akkordtöne eng ab MIDI 51, 3 Stimmen | 1–8 | 42 |
| KB Kurzer Bass | `x-------........\|................  (wiederholt)` | Bass-Töne `P(C2)` ab MIDI 36 | 1–8 | 45 |
| TU Tupfer | `x-------........\|................  (wiederholt)` | oberster Akkordton ab MIDI 67, dann abwärts zyklisch | 1–8 | 38 |

- **Nicht beteiligt:** Lange Fläche, Langer Bass, Arpeggio, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
KF   ● · ● · ● · ● ·
KB   ● · ● · ● · ● ·
TU   ● · ● · ● · ● ·
```

- **Zusammenhang der Rollen:** Gleiche Tonhöhen, gleiche Velocity, gleiche Notenzahl (20) wie HE-S01. Geändert sind nur Artikulationslänge (halbe statt zwei Takte), Synchronität (der Tupfer fällt mit Fläche und Bass zusammen) und Register des Tupfers (eine Oktave tiefer, in den Klang hinein). Aus Schwebe wird ein Puls, aus Ahnung ein Herannahen.
- **Dynamik:** pp wie HE-S01. · **Pausen:** Eineinhalb Takte Stille nach jedem Schlag.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** Schlag auf 2+ statt 1 (synkopierter Puls). · **Fortsetzung:** HE-S07 oder zurück nach HE-S01 (Entkopplung, HE-T13).
- **Bezug:** HE-H01, HE-R16, HE-S01
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 0 3 0 3 0 3 0; keine Melodierolle; MIDI `HE-S02.mid`, 20 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Lange Noten in Kurzrolle

### HE-S03 · Statisches Unbehagen, hell

- **Charakter:** Ein sonniger, leerer Flur in einer Klinik; alles sauber, nichts stimmt.
- **XYZ-Anker:** 0,55 / 0,20 / 0,55 (mRm) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 50–62 (MIDI-Beispiel ♩ = 56) · **Harmonik:** HE-H66 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `C/F#` | `C/F#` | `C/F#` | `C/F#` | `C/F#` | `C/F#` | `C/F#` | `C/F#`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------\|----------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 60, 3 Stimmen | 1–8 | 40 |
| LB Langer Bass | `x---------------\|----------------  (wiederholt)` | fest: F#1 | 1–8 | 42 |
| TU Tupfer | `x...x...x...x...\|x...x...x.......  (wiederholt)` | fest: E6 | 3, 4, 5, 6, 7, 8 | 30 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Arpeggio, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ○ ● ○ ● ○ ● ○
LB   ● ○ ● ○ ● ○ ● ○
TU   · · ● ● ● ● ● ●
```

- **Zusammenhang der Rollen:** C-Dur in der Mitte, Tritonusbass darunter, darüber ein repetierter heller Ton (E, gemeinsamer Ton). Hell heißt hier nicht freundlich: der Boden steht falsch.
- **Dynamik:** pp, Tupfer sehr leise und gleichmäßig. · **Pausen:** Takt 1–2 ohne Tupfer; jede zweite Gruppe endet eine Viertel früher.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** Tupfer-Ton B6 (große Septime über C) statt E6. · **Fortsetzung:** HE-S09 (kalte Helligkeit) oder HE-H38.
- **Bezug:** HE-H66, HE-R36, HE-B02
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 0 3 1 3 1 3 1; keine Melodierolle; MIDI `HE-S03.mid`, 37 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Exakte Registervorgabe

### HE-S04 · Obsessive Spannung um ein Binnenpedal

- **Charakter:** Jemand folgt einem Auto durch die Stadt, immer im gleichen Abstand.
- **XYZ-Anker:** 0,30 / 0,20 / 0,65 (DRU) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 66–80 (MIDI-Beispiel ♩ = 72) · **Harmonik:** HE-H27 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `C7` | `C7` | `F#7b5` | `F#7b5` | `Eaug` | `Eaug` | `C7` | `C7`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `x.x---x.x...x.x.  (wiederholt)` | Akkordtöne eng ab MIDI 58, 3 Stimmen | 1–8 | 45 |
| LB Langer Bass | `x---------------\|----------------  (wiederholt)` | fest: E2 | 1–8 | 38 |
| TU Tupfer | `x.......x.......  (wiederholt)` | fest: E5 | 5, 6, 7, 8 | 30 |

- **Nicht beteiligt:** Lange Fläche, Kurzer Bass, Arpeggio, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
KF   ● ● ● ● ● ● ● ●
LB   ● ○ ● ○ ● ○ ● ○
TU   · · · · ● ● ● ●
```

- **Zusammenhang der Rollen:** Das Synkopenostinato der Kurzen Fläche ändert sich nie; nur die Klänge darunter kreisen. E liegt in allen Klängen und wird vom Langen Bass gehalten (Binnenpedal, nicht im tiefsten Register) und ab Takt 5 vom Tupfer verdoppelt.
- **Dynamik:** pp durchgehend. · **Pausen:** Die Pause am Ende jeder Ostinato-Figur bleibt immer an derselben Stelle.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme; die Zelle HE-M10 kann als Gegenstimme dazutreten.
- **Variation:** Ostinato ab Takt 5 in die Arpeggio-Rolle verlegen (Rollenwanderung, HE-R53). · **Fortsetzung:** HE-S25 (32 Takte) oder HE-T07.
- **Bezug:** HE-H27, HE-R03, HE-R36
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 1 2 1 3 2 3 2; keine Melodierolle; MIDI `HE-S04.mid`, 156 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Exakte Registervorgabe, Rollenwanderung

### HE-S05 · Chromatische Gegenbewegung mit Konvergenz

- **Charakter:** Zwei Menschen gehen in einem dunklen Haus aufeinander zu, ohne es zu wissen.
- **XYZ-Anker:** 0,20 / 0,35 / 0,55 (DRm) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 54–66 (MIDI-Beispiel ♩ = 60) · **Harmonik:** HE-H07 (umgekehrt), HE-B08 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `CmM7/G` | `CmM7/Ab` | `CmM7/A` | `CmM7/Bb` | `CmM7/B` | `CmM7` | `CmM7` | `CmM7`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------\|----------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 60, 2 Stimmen | 1–8 | 40 |
| LB Langer Bass | `x---------------  (wiederholt)` | Bass-Töne `b` ab MIDI 31 | 1–8 | 48 · Dynamik je Takt ×0,90 0,92 0,95 1,00 1,05 1,10 1,00 0,95 |
| TU Tupfer | `x...............\|................  (wiederholt)` | oberster Akkordton ab MIDI 79, dann abwärts zyklisch | 6, 7, 8 | 35 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 50 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Arpeggio, Stich, Hauptmelodie
- **Gegenstimme:** `r/16 | Eb5/16 | D5/16 | Db5/16 | C5/16 | B4/16 | r/16 | r/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ○ ● ○ ● ○ ● ○
LB   ● ● ● ● ● ● ● ●
TU   · · · · · · ● ·
GS   · ● ● ● ● ● · ·
```

- **Zusammenhang der Rollen:** Der Bass steigt in Halbtönen (G–A♭–A–B♭–B–C), die Gegenstimme fällt in Halbtönen (E♭–D–D♭–C–B). In Takt 6 treffen sie auf dem Moll-Dur-Septakkord (Bass C, oben B) zusammen; danach bewegt sich nichts mehr.
- **Dynamik:** pp, Bass Takt 5–6 leicht anwachsend. · **Pausen:** Gegenstimme schweigt in Takt 1 und 7–8.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Gegenstimme bleibt die Steigung des Basses unter der Fläche hörbar, aber die Konvergenz fehlt; die Gegenstimme ist hier wichtiger als jede Hauptmelodie.
- **Variation:** Gegenstimme eine Oktave tiefer (näher am Bass, dichter). · **Fortsetzung:** HE-S16 oder HE-H09.
- **Bezug:** HE-B08, HE-M32, HE-H01
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 2 3 2 3 2 3 1; Melodietöne auf Zählzeiten als Akkordton: GS 3/5; MIDI `HE-S05.mid`, 22 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 3/2/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### HE-S06 · Polychord in getrennten Schichten

- **Charakter:** Zwei Wirklichkeiten zugleich: ein Kind spielt im Garten, und im Haus ist etwas.
- **XYZ-Anker:** 0,15 / 0,25 / 0,65 (DRU) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 52–64 (MIDI-Beispiel ♩ = 58) · **Harmonik:** HE-H51 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `F#m|Cm` | `F#m|Cm` | `F#m|Cm` | `F#m|Cm` | `F#m|Cm` | `F#m|Cm` | `F#m|Cm` | `F#m|Cm`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------\|----------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 48, 3 Stimmen | 1–8 | 45 |
| AR Arpeggio | `....x...x...x---\|................  (wiederholt)` | Akkordtöne (4) ab MIDI 78 über 2 Oktaven, aufwärts zyklisch | 1–8 | 45 |

- **Nicht beteiligt:** Kurze Fläche, Langer Bass, Kurzer Bass, Tupfer, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ○ ● ○ ● ○ ● ○
AR   ● · ● · ● · ● ·
```

- **Zusammenhang der Rollen:** Untere Schicht C-Moll (C3–G3) gehalten, obere Schicht F♯-Moll (F♯5–C♯6) als dreitönige Brechung, nie auf der Eins. Sechs Tonklassen, zwei Schichten, mehr als eine Oktave Abstand.
- **Dynamik:** pp, beide Schichten gleich laut. · **Pausen:** Obere Schicht pausiert jeden zweiten Takt.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** Obere Schicht als Tupfer einzeln (noch weiter auseinander). · **Fortsetzung:** HE-S07 über HE-T08.
- **Bezug:** HE-H51, HE-R42
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 0 2 0 2 0 2 0; keine Melodierolle; MIDI `HE-S06.mid`, 24 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Exakte Registervorgabe, Mehrere harmonische Komponenten

### HE-S07 · Derselbe Polychord, verschmolzen

- **Charakter:** Die beiden Wirklichkeiten fallen zusammen; es ist da.
- **XYZ-Anker:** 0,15 / 0,70 / 0,70 (DIU) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 52–64 (MIDI-Beispiel ♩ = 58) · **Harmonik:** HE-H52 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `F#m|Cm` | `F#m|Cm` | `F#m|Cm` | `F#m|Cm` | `F#m|Cm` | `F#m|Cm` | `F#m|Cm` | `F#m|Cm`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x-------........\|................  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 60, 3 Stimmen | 1–8 | 45 |
| KF Kurze Fläche | `x-------........\|................  (wiederholt)` | Akkordtöne eng ab MIDI 64, 3 Stimmen | 1–8 | 45 |

- **Nicht beteiligt:** Langer Bass, Kurzer Bass, Arpeggio, Tupfer, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● · ● · ● · ● ·
KF   ● · ● · ● · ● ·
```

- **Zusammenhang der Rollen:** Gleiche sechs Tonklassen, gleiche Velocity, gleiche Notenzahl (24) wie HE-S06. Geändert: Register (beide Schichten zwischen C4 und C♯5, ineinander), Synchronität (gleicher Einsatz), Artikulation (beide eine Halbe, dann Stille). Die Wirkung wechselt von rätselhaft zu akut.
- **Dynamik:** pp wie HE-S06 – die Schärfe kommt nicht aus der Lautstärke. · **Pausen:** Eineinhalb Takte Stille nach jedem Schlag.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** Mit Stich nur beim ersten Schlag (Ereignis), nie periodisch. · **Fortsetzung:** HE-S15 oder zurück über HE-T13.
- **Bezug:** HE-H52, HE-R41, HE-S06
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 0 2 0 2 0 2 0; keine Melodierolle; MIDI `HE-S07.mid`, 24 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Lange Noten in Kurzrolle, Exakte Registervorgabe, Mehrere harmonische Komponenten

### HE-S08 · Polyklang-Pendel mit Registertausch

- **Charakter:** Ein Haus auf einem Hügel bei Nacht; jemand beobachtet es, und das Haus beobachtet zurück.
- **XYZ-Anker:** 0,25 / 0,30 / 0,55 (DRm) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 60–72 (MIDI-Beispiel ♩ = 66) · **Harmonik:** HE-H55 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `Em|{Ab C}` | `Em|{Ab C}` | `Fm|{A Db}` | `Fm|{A Db}` | `Em|{Ab C}` | `Em|{Ab C}` | `Fm|{A Db}` | `Fm|{A Db}`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------\|----------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 44, 3 Stimmen | 1–8 | 45 |
| KF Kurze Fläche | `x.....x.....x...  (wiederholt)` | Akkordtöne eng ab MIDI 64, 3 Stimmen | 1–8 | 42 |

- **Nicht beteiligt:** Langer Bass, Kurzer Bass, Arpeggio, Tupfer, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ○ ● ○ ● ○ ● ○
KF   ● ● ● ● ● ● ● ●
```

- **Zusammenhang der Rollen:** Takt 1–4: Dyade tief gehalten, Molldreiklang oben in einer Dreiergruppierung (3+3+2 Achtel). Takt 5–8: Register getauscht – Dreiklang tief gehalten, Dyade oben im selben Rhythmus. Kein Ton kommt hinzu, beide Schichten pendeln gemeinsam einen Halbton.
- **Dynamik:** pp bis p. · **Pausen:** keine; die Unruhe liegt im Pendel und im Registertausch.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** Tausch erst nach acht Takten (16-Takt-Fassung). · **Fortsetzung:** HE-S22 oder HE-T06.
- **Bezug:** HE-H55, HE-R28
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 1 2 1 2 1 2 1; keine Melodierolle; MIDI `HE-S08.mid`, 70 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Exakte Registervorgabe, Mehrere harmonische Komponenten

### HE-S09 · Kalte Helligkeit zwischen zwei Pedalen

- **Charakter:** Ein Raumschiff landet lautlos in einem Park; niemand rührt sich.
- **XYZ-Anker:** 0,60 / 0,15 / 0,40 (mRm) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 46–58 (MIDI-Beispiel ♩ = 52) · **Harmonik:** HE-H56 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `F#/C` | `F#/C` | `F#/C` | `F#/C` | `F#/C` | `F#/C` | `F#/C` | `F#/C`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `....x-----------\|----------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 54, 3 Stimmen | 3, 4, 5, 6, 7, 8 | 38 |
| LB Langer Bass | `x---------------\|----------------  (wiederholt)` | fest: C1 C2 | 1–8 | 40 |
| TU Tupfer | `x---------------\|----------------  (wiederholt)` | fest: C6 | 1–8 | 28 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Arpeggio, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   · · ● ○ ● ○ ● ○
LB   ● ○ ● ○ ● ○ ● ○
TU   ● ○ ● ○ ● ○ ● ○
```

- **Zusammenhang der Rollen:** Tiefes und hohes C liegen von Anfang an; der F♯-Dur-Klang in der Mitte erscheint erst in Takt 3 und setzt nie auf der Eins ein. Drei getrennte Schichten, kein Rhythmus.
- **Dynamik:** ppp–pp; Hochpedal am leisesten. · **Pausen:** Takt 1–2 nur Pedale.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** Mittelklang zwischen F♯ und A♭ wechseln (HE-H69). · **Fortsetzung:** HE-S12 oder HE-T08 (Verschmelzung → HE-H57).
- **Bezug:** HE-H56, HE-B06
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 0 3 0 3 0 3 0; keine Melodierolle; MIDI `HE-S09.mid`, 21 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Mehrstimmiger Bass, Lange Noten in Kurzrolle, Exakte Registervorgabe

### HE-S10 · Schwindel: gegenläufige Spiralen

- **Charakter:** Blick von einem Glockenturm in die Tiefe.
- **XYZ-Anker:** 0,55 / 0,30 / 0,75 (mRU) · **Länge:** 8 Takte · **Taktart:** 4/4T · **Tempo:** ♩ = 63–76 (MIDI-Beispiel ♩ = 69) · **Harmonik:** HE-H48 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `Caug` | `Caug` | `Daug` | `Daug` | `Caug` | `Caug` | `Daug` | `Daug`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x-----------\|------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 72, 3 Stimmen | 1–8 | 30 |
| AR Arpeggio | `xxxxxxxxxxxx  (wiederholt)` | Akkordtöne (4) ab MIDI 64 über 2 Oktaven, auf und ab | 1–8 | 42 |
| TU Tupfer | `xxxxxxxxxxxx  (wiederholt)` | Akkordtöne (4) ab MIDI 76 über 2 Oktaven, aufwärts zyklisch | 3, 4, 5, 6, 7, 8 | 38 |

- **Nicht beteiligt:** Kurze Fläche, Langer Bass, Kurzer Bass, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ○ ● ○ ● ○ ● ○
AR   ● ● ● ● ● ● ● ●
TU   · · ● ● ● ● ● ●
```

- **Zusammenhang der Rollen:** Zwei Brechungen desselben übermäßigen Klangs laufen gegeneinander (eine aufwärts zuerst, eine abwärts zuerst), die zweite eine Oktave höher und ab Takt 3. Kein Bass: der Boden fehlt (HE-B42).
- **Dynamik:** pp, gleichmäßig; Fläche kaum hörbar. · **Pausen:** keine – Schwindel hat keine Pausen.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** Daug durch Dbaug ersetzen (Halbtonabstand, schärfer). · **Fortsetzung:** HE-S18 oder HE-T06.
- **Bezug:** HE-H48, HE-R13, HE-M29
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 1 3 2 3 2 3 2; keine Melodierolle; MIDI `HE-S10.mid`, 180 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Kanon/koordinierte Parallelstimmen

### HE-S11 · Spieluhr mit falschem Ton

- **Charakter:** Ein Kinderzimmer, in dem lange niemand mehr war; die Spieluhr läuft von selbst.
- **XYZ-Anker:** 0,75 / 0,15 / 0,45 (HRm) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 70–84 (MIDI-Beispiel ♩ = 76) · **Harmonik:** HE-H77 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `C` | `C` | `Cadd#4` | `Cadd#4` | `C` | `C` | `E/C` | `E/C`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KB Kurzer Bass | `................\|......x.........  (wiederholt)` | Bass-Töne `P(C1)` ab MIDI 36 | 8 | 40 |
| AR Arpeggio | `x.x.x.x.x.x.x.x.  (wiederholt)` | Akkordtöne (4) ab MIDI 72 über 2 Oktaven, auf und ab | 1–8 | 40 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 45 |

- **Nicht beteiligt:** Lange Fläche, Kurze Fläche, Langer Bass, Tupfer, Stich, Hauptmelodie
- **Gegenstimme:** `r/16 | G5/2 E5/2 C5/2 E5/2 G5/2 F#5/2 E5/4 | r/16 | G5/2 E5/2 C5/2 E5/2 G5/2 F#5/2 E5/4 | r/16 | r/16 | G#5/2 E5/2 C5/2 E5/2 r/8 | r/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
KB   · · · · · · · ●
AR   ● ● ● ● ● ● ● ●
GS   · ● · ● · · ● ·
```

- **Zusammenhang der Rollen:** Die Brechung bleibt mechanisch gleich, auch wenn der Klang einen fremden Ton (F♯) oder eine fremde Mediante (E-Dur) bekommt. Die Gegenstimme bricht zweimal ab. Ein einziger sehr tiefer Ton am Schluss.
- **Dynamik:** p, mechanisch gleich. · **Pausen:** Gegenstimme nur in den Takten 2, 4 und 7.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Gegenstimme trägt die Brechung allein; die falschen Töne liegen bereits in der Harmonik.
- **Variation:** Tempo der Brechung halbieren (Uhrwerk läuft ab). · **Fortsetzung:** HE-S03 oder HE-T11.
- **Bezug:** HE-H77, HE-M39, HE-B20
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 1 2 1 2 1 1 2 2; Melodietöne auf Zählzeiten als Akkordton: GS 10/10; MIDI `HE-S11.mid`, 83 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 17/1/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### HE-S12 · Geheimnisvolles Staunen

- **Charakter:** Eine Höhle öffnet sich zu einem unterirdischen Meer.
- **XYZ-Anker:** 0,75 / 0,60 / 0,30 (HmS) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 48–60 (MIDI-Beispiel ♩ = 54) · **Harmonik:** HE-H41 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `C` | `C` | `E` | `E` | `Ab` | `Ab` | `C` | `C`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------\|----------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 55, 4 Stimmen | 1–8 | 72 |
| LB Langer Bass | `x---------------\|----------------  (wiederholt)` | Bass-Töne `R` ab MIDI 24 | 1–8 | 70 |
| AR Arpeggio | `x...x...x...x...  (wiederholt)` | Akkordtöne (4) ab MIDI 67 über 2 Oktaven, aufwärts zyklisch | 1–8 | 50 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Tupfer, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ○ ● ○ ● ○ ● ○
LB   ● ○ ● ○ ● ○ ● ○
AR   ● ● ● ● ● ● ● ●
```

- **Zusammenhang der Rollen:** Großterzzyklus in weiter Lage (Abstand mindestens eine Quarte zwischen den Stimmen) über tiefem Grundton; das Arpeggio geht ruhig in Vierteln. Hell und kraftvoll, aber ohne Jubel: kein Leitton, keine Kadenz.
- **Dynamik:** mf, Takt 5–6 f. · **Pausen:** keine.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** Takt 7–8 durch Ganztonausschnitt ersetzen (HE-H47). · **Fortsetzung:** HE-H90 oder HE-H89.
- **Bezug:** HE-H41, HE-B32
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 1 3 1 3 1 3 1; keine Melodierolle; MIDI `HE-S12.mid`, 48 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte

### HE-S13 · Kalte Spannung in Hemiolen

- **Charakter:** Eine Verfolgung über ein Glasdach in grellem Licht.
- **XYZ-Anker:** 0,70 / 0,75 / 0,80 (HIU) · **Länge:** 8 Takte · **Taktart:** 3/4 · **Tempo:** ♩ = 120–144 (MIDI-Beispiel ♩ = 132) · **Harmonik:** HE-H92 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `E|C` | `E|C` | `E|C` | `E|C` | `E|C` | `E|C` | `E|C` | `E|C`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `X.x.X.x.X.x.\|X.x.x.X.x.x.\|X.x.x.X.x.x.\|X.x.X.x.X.x.  (wiederholt)` | Akkordtöne eng ab MIDI 60, 6 Stimmen | 1–8 | 78 |
| KB Kurzer Bass | `x...........  (wiederholt)` | Bass-Töne `P(C2)` ab MIDI 36 | 1–8 | 70 |
| ST Stich | `............\|............\|............\|............\|X...........\|............\|............\|............` | fester Trigger C2 (nie transponiert) | 1–8 | 100 |

- **Nicht beteiligt:** Lange Fläche, Langer Bass, Arpeggio, Tupfer, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
KF   ● ● ● ● ● ● ● ●
KB   ● ● ● ● ● ● ● ●
ST   · · · · ● · · ·
```

- **Zusammenhang der Rollen:** Der verschmolzene Doppelklang C-Dur/E-Dur wird in gleichmäßigen Achteln geschlagen; nur die Akzente wechseln taktweise zwischen 3/4 und 6/8. Der Bass hält nur die Eins. Ein einziger Stich in Takt 5.
- **Dynamik:** f, Akzente ff. · **Pausen:** keine.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** Gruppierungen permutieren; Bass auf die Hemiole legen (HE-B23). · **Fortsetzung:** HE-S15 oder HE-T13 (Entkopplung).
- **Bezug:** HE-H92, HE-R57, HE-R49
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 2 2 2 3 2 2 2; keine Melodierolle; MIDI `HE-S13.mid`, 297 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte

### HE-S14 · Dunkle Monumentalität

- **Charakter:** Eine Festung, die sich aus dem Nebel schiebt.
- **XYZ-Anker:** 0,10 / 0,85 / 0,30 (DIS) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 44–56 (MIDI-Beispiel ♩ = 50) · **Harmonik:** HE-H79 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `Cm` | `Cm` | `F#m` | `F#m` | `Cm` | `Cm` | `F#m` | `F#m`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------\|----------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 43, 4 Stimmen | 1–8 | 95 |
| LB Langer Bass | `x---------------\|----------------  (wiederholt)` | Bass-Töne `R` ab MIDI 24 | 1–8 | 95 |
| KB Kurzer Bass | `X..x....X..x....  (wiederholt)` | Bass-Töne `R R 5 R` ab MIDI 36 | 1–8 | 82 |

- **Nicht beteiligt:** Kurze Fläche, Arpeggio, Tupfer, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ○ ● ○ ● ○ ● ○
LB   ● ○ ● ○ ● ○ ● ○
KB   ● ● ● ● ● ● ● ●
```

- **Zusammenhang der Rollen:** Homogene Mollblöcke in tiefer, enger Lage, Oktavbass, schweres Paukenmuster. Langsam: die Intensität kommt aus Masse und Homogenität, nicht aus Bewegung.
- **Dynamik:** ff, ohne Schwankung. · **Pausen:** keine.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** Wechsel nur alle vier Takte. · **Fortsetzung:** HE-H80 oder HE-H94.
- **Bezug:** HE-H79, HE-B18, HE-R08
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 1 3 1 3 1 3 1; keine Melodierolle; MIDI `HE-S14.mid`, 48 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte

### HE-S15 · Akuter Horror: Kaskade und verschränkte Tritoni

- **Charakter:** Der Angriff.
- **XYZ-Anker:** 0,15 / 0,90 / 0,80 (DIU) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 108–132 (MIDI-Beispiel ♩ = 120) · **Harmonik:** HE-H71, HE-H72 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `{Ab G F# F}` | `{Ab G F# F}` | `{C F# F B}` | `{C F# F B}` | `{C F# F B}` | `{C F# F B}` | `{C F# F B}` | `{C F# F B}`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `....X-----------\|--------........\|x.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.` | Akkordtöne eng ab MIDI 60, 4 Stimmen | 1–8 | 96 |
| KB Kurzer Bass | `......X---------\|--------........\|..x...x.x.....x.\|...x....x...x...\|..x...x.x.....x.\|...x....x...x...\|..x...x.x.....x.\|...x....x...x...` | Bass-Töne `P(Ab3) P(Ab3) P(C2) P(C1) P(C2) P(C1) P(F#1) P(C2) P(F#1)` ab MIDI 36 | 1–8 | 100 |
| AR Arpeggio | `..X-------------\|--------........\|................\|................\|................\|................\|................\|................` | fest: F#5 | 1–8 | 110 |
| TU Tupfer | `X---------------\|--------........\|................\|................\|................\|................\|................\|................` | fest: F6 | 1–8 | 110 |
| ST Stich | `................\|................\|X...............\|................\|................\|................\|................\|................` | fester Trigger C2 (nie transponiert) | 1–8 | 100 |

- **Nicht beteiligt:** Lange Fläche, Langer Bass, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
KF   ● ○ ● ● ● ● ● ●
KB   ● ○ ● ● ● ● ● ●
AR   ● ○ · · · · · ·
TU   ● ○ · · · · · ·
ST   · · ● · · · · ·
```

- **Zusammenhang der Rollen:** Takt 1–2: vier Töne werden von oben nach unten im Achtelabstand eingesetzt (F6, F♯5, G4, A♭3 – absteigende große Septimen) und gehalten. Ab Takt 3 schlägt die Kurze Fläche gleichmäßige Achtel auf dem Tritonusklang, der Kurze Bass spielt dagegen versetzte Einsätze, erst in Oktaven, dann im Tritonus. Ein Stich nur zu Beginn von Takt 3.
- **Dynamik:** ff, sffz-Einsätze. · **Pausen:** Nach der Kaskade eine halbe Note Stille.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** Gleichmäßige Achtel in Takt 7–8 durch Pausen unterbrechen (HE-R20). · **Fortsetzung:** HE-T13 (Entkopplung) oder HE-S07.
- **Bezug:** HE-H71, HE-H72, HE-R51, HE-R33, HE-B12
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 4 0 3 2 2 2 2 2; keine Melodierolle; MIDI `HE-S15.mid`, 218 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Lange Noten in Kurzrolle, Exakte Registervorgabe, Mehrere harmonische Komponenten

### HE-S16 · Tragik

- **Charakter:** Nach der Beerdigung, im leeren Wohnzimmer.
- **XYZ-Anker:** 0,25 / 0,25 / 0,25 (DRS) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 50–62 (MIDI-Beispiel ♩ = 56) · **Harmonik:** HE-H46 · **Tonvorrat:** Moll gesamt
- **Akkorde je Takt:** `Cm` | `Cm` | `Abmaj7` | `Abmaj7` | `Fm6` | `Fm6` | `CmM7` | `CmM7`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------\|----------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 53, 4 Stimmen | 1–8 | 48 |
| LB Langer Bass | `x---------------\|----------------  (wiederholt)` | Bass-Töne `b` ab MIDI 36 | 1–8 | 50 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 52 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Arpeggio, Tupfer, Stich, Hauptmelodie
- **Gegenstimme:** `r/16 | Ab4/3 G4/5 F4/3 Eb4/5 | Eb4/3 D4/5 C4/8 | r/16 | Ab4/3 G4/5 F4/3 E4/5 | Eb4/3 D4/5 C4/8 | r/16 | B3/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ○ ● ○ ● ○ ● ○
LB   ● ○ ● ○ ● ○ ● ○
GS   · ● ● · ● ● · ●
```

- **Zusammenhang der Rollen:** Getragene Mollfolge, die nicht schließt, sondern im Moll-Dur-Septakkord stehen bleibt. Die Gegenstimme reiht Seufzerpaare; ihr letzter Ton ist die große Septime B.
- **Dynamik:** p, Takt 3–4 mp. · **Pausen:** Gegenstimme schweigt Takt 1, 4 und 7.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Gegenstimme bleibt eine vollständige, traurige Fläche mit offenem Ende.
- **Variation:** Hauptmelodie HE-P13 statt Gegenstimme (dann GS weglassen). · **Fortsetzung:** HE-S30 oder HE-H45.
- **Bezug:** HE-H46, HE-M40
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 1 3 0 3 1 2 1; Melodietöne auf Zählzeiten als Akkordton: GS 6/9; MIDI `HE-S16.mid`, 34 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 9/5/1
- **Haltetöne über Akkordwechsel:** keine Konflikte

### HE-S17 · Paranoia

- **Charakter:** Jemand ist überzeugt, verfolgt zu werden; vielleicht stimmt es.
- **XYZ-Anker:** 0,20 / 0,25 / 0,75 (DRU) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 76–92 (MIDI-Beispiel ♩ = 84) · **Harmonik:** HE-H03 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `CmM7` | `CmM7` | `DbmM7` | `DbmM7` | `CmM7` | `CmM7` | `DbmM7` | `DbmM7`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `x.x.x.x.x.x.x.x.\|x.x.x.x.........\|x.x.x.x.x.x.x.x.\|x.x.............  (wiederholt)` | Akkordtöne eng ab MIDI 60, 3 Stimmen | 1–8 | 40 |
| KB Kurzer Bass | `x.......x...x...\|....x...........\|x...x.......x...\|........x.......  (wiederholt)` | Bass-Töne `R` ab MIDI 36 | 1–8 | 42 |
| TU Tupfer | `......x.........\|..........x.....\|...x............\|.............x..  (wiederholt)` | oberster Akkordton ab MIDI 80, dann abwärts zyklisch | 1–8 | 36 |

- **Nicht beteiligt:** Lange Fläche, Langer Bass, Arpeggio, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
KF   ● ● ● ● ● ● ● ●
KB   ● ● ● ● ● ● ● ●
TU   ● ● ● ● ● ● ● ●
```

- **Zusammenhang der Rollen:** Der Achtelfluss der Kurzen Fläche stockt unregelmäßig, die Tupfer und der Kurze Bass folgen keinem Raster. Das Halbtonpendel zweier Moll-Dur-Septakkorde ist der einzige Wechsel.
- **Dynamik:** pp; nichts wird lauter. · **Pausen:** Ostinato-Lücken in Takt 2 und 4 jeder Gruppe.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** Lücken an anderen Stellen; Pendel jede Takthälfte. · **Fortsetzung:** HE-S24 oder HE-H11.
- **Bezug:** HE-H03, HE-R20, HE-R18, HE-B35
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 3 3 3 3 3 3 3; keine Melodierolle; MIDI `HE-S17.mid`, 156 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte

### HE-S18 · Fremder Ort

- **Charakter:** Ein Bahnhof, an dem kein Zug hält; alle Uhren zeigen dieselbe Zeit.
- **XYZ-Anker:** 0,50 / 0,20 / 0,55 (mRm) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 54–66 (MIDI-Beispiel ♩ = 60) · **Harmonik:** HE-H49, HE-H50 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `C9#5` | `C9#5` | `C9#5` | `C9#5` | `Db9#5` | `Db9#5` | `C9#5` | `C9#5`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------\|----------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 60, 5 Stimmen | 1–8 | 40 |
| LB Langer Bass | `x---------------\|----------------  (wiederholt)` | fest: G#3 | 1–8 | 32 |
| AR Arpeggio | `..x...x...x...x.  (wiederholt)` | Akkordtöne (4) ab MIDI 72 über 2 Oktaven, auf und ab | 1–8 | 36 |
| TU Tupfer | `................\|..........x-----\|................\|................  (wiederholt)` | fest: F#6 | 1–8 | 28 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ○ ● ○ ● ○ ● ○
LB   ● ○ ● ○ ● ○ ● ○
AR   ● ● ● ● ● ● ● ●
TU   · ● · · · ● · ·
```

- **Zusammenhang der Rollen:** Ganztonfeld ohne Grundton; der tiefste Ton liegt in der Mittellage. In Takt 5–6 rückt das Feld einen Halbton (andere Ganztonreihe) und kehrt zurück. Das Arpeggio setzt nur auf unbetonten Achteln ein, der hohe F♯-Ton erscheint selten.
- **Dynamik:** pp. · **Pausen:** Tupfer nur in Takt 2 und 6.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** Pedal G♯3 ganz weglassen (völlig bodenlos). · **Fortsetzung:** HE-S10 oder HE-H47.
- **Bezug:** HE-H49, HE-H50, HE-B42
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 2 3 1 3 2 3 1; keine Melodierolle; MIDI `HE-S18.mid`, 58 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Exakte Registervorgabe

### HE-S19 · Lebloser Tanz

- **Charakter:** Eine Frau steht vor einem Porträt im Museum, Tag für Tag.
- **XYZ-Anker:** 0,25 / 0,20 / 0,40 (DRm) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 56–70 (MIDI-Beispiel ♩ = 63) · **Harmonik:** HE-H64 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `Cm` | `Cm` | `Abmaj7` | `Abmaj7` | `Ebaug` | `Ebaug` | `Db` | `Db`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------\|----------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 50, 3 Stimmen | 1–8 | 36 |
| LB Langer Bass | `x---------------\|----------------  (wiederholt)` | Bass-Töne `R` ab MIDI 36 | 1–8 | 40 |
| AR Arpeggio | `x..xx.x.x..xx.x.  (wiederholt)` | fest: G3 | 1–8 | 34 |
| TU Tupfer | `x...x...x...x...  (wiederholt)` | fest: G5 | 1–8 | 34 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ○ ● ○ ● ○ ● ○
LB   ● ○ ● ○ ● ○ ● ○
AR   ● ● ● ● ● ● ● ●
TU   ● ● ● ● ● ● ● ●
```

- **Zusammenhang der Rollen:** Der Ton G wird oben in Vierteln repetiert und unten im Tanzrhythmus kurz auf einem Ton wiederholt; darunter wechseln vier Klänge, zu denen G Quinte, große Septime, Terz und Tritonus ist. Der Tanz bewegt sich, aber er kommt nirgends hin.
- **Dynamik:** pp gleichmäßig. · **Pausen:** keine; der Stillstand liegt in der Wiederholung.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme; HE-M47 kann als Gegenstimme dazutreten.
- **Variation:** Tanzfigur eine Oktave höher, Repetition halbieren. · **Fortsetzung:** HE-S26 oder HE-T03.
- **Bezug:** HE-H64, HE-R36, HE-R37
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 4 2 4 2 4 2 4 2; keine Melodierolle; MIDI `HE-S19.mid`, 112 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Exakte Registervorgabe

### HE-S20 · Puls statt Rhythmus

- **Charakter:** Gang durch eine leere Innenstadt am Sonntagmorgen.
- **XYZ-Anker:** 0,20 / 0,25 / 0,45 (DRm) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 60–72 (MIDI-Beispiel ♩ = 66) · **Harmonik:** HE-H22 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `Cm7b5` | `Cm7b5` | `Bm7b5` | `Bm7b5` | `Bbm7b5` | `Bbm7b5` | `Am7b5` | `Am7b5`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `x...x...x...x...  (wiederholt)` | Akkordtöne eng ab MIDI 60, 4 Stimmen | 1–8 | 40 |
| TU Tupfer | `................\|................\|................\|........x-x.....  (wiederholt)` | oberster Akkordton ab MIDI 79, dann abwärts zyklisch | 1–8 | 34 |

- **Nicht beteiligt:** Lange Fläche, Langer Bass, Kurzer Bass, Arpeggio, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
KF   ● ● ● ● ● ● ● ●
TU   · · · ● · · · ●
```

- **Zusammenhang der Rollen:** Gleichmäßige Viertel ohne Akzent, vierstimmig; die halbverminderten Klänge sinken alle zwei Takte einen Halbton. Kein Bass. Ein Tupfer-Seufzer nur am Ende jeder Vierergruppe.
- **Dynamik:** pp. · **Pausen:** keine im Puls.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** Puls in Halben (noch leerer). · **Fortsetzung:** HE-S21 (Fugato) oder HE-H33.
- **Bezug:** HE-H22, HE-R02, HE-M02
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 1 1 1 2 1 1 1 2; keine Melodierolle; MIDI `HE-S20.mid`, 132 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte

### HE-S21 · Fugato als Spannungsmaschine

- **Charakter:** Jemand steigt in einen Keller hinab; mit jeder Stufe wird es enger.
- **XYZ-Anker:** 0,20 / 0,40 / 0,60 (Dmm) → 0,20 / 0,60 / 0,75 (DmU), Fahrt in der zweiten Hälfte · **Länge:** 16 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 88–104 (MIDI-Beispiel ♩ = 96) · **Harmonik:** Cm statisch, Chromatik in den Linien · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `Cm` (×16)

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LB Langer Bass | `................\|................\|................\|................\|................\|................\|................\|................\|x---------------\|----------------\|x---------------\|----------------\|x---------------\|----------------\|x---------------\|----------------` | fest: C1 | 1–16 | 50 |
| KB Kurzer Bass | — | notiert (siehe unten) | 1–16 | 58 |
| TU Tupfer | — | notiert (siehe unten) | 1–16 | 50 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–16 | 55 |
| HM Hauptmelodie | — | notiert (siehe unten) | 1–16 | 55 |

- **Nicht beteiligt:** Lange Fläche, Kurze Fläche, Arpeggio, Stich
- **Hauptmelodie:** `r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | C4/2 Db4/2 C4/2 B3/2 Bb3/4 A3/4 | Ab3/2 G3/2 Ab3/2 G3/2 F#3/8 | G5/2 F#5/2 F5/2 E5/2 Eb5/2 D5/2 Db5/2 C5/2 | B4/2 Bb4/2 A4/2 Ab4/2 G4/8 | C4/2 Db4/2 C4/2 B3/2 Bb3/4 A3/4 | Ab3/2 G3/2 Ab3/2 G3/2 F#3/8 | r/16 | r/16`
- **Gegenstimme:** `r/16 | r/16 | r/16 | r/16 | G3/2 Ab3/2 G3/2 F#3/2 F3/4 E3/4 | Eb3/2 D3/2 Eb3/2 D3/2 C#3/8 | G4/2 F#4/2 F4/2 E4/2 Eb4/2 D4/2 Db4/2 C4/2 | B3/2 Bb3/2 A3/2 Ab3/2 G3/8 | G3/2 Ab3/2 G3/2 F#3/2 F3/4 E3/4 | Eb3/2 D3/2 Eb3/2 D3/2 C#3/8 | G4/2 F#4/2 F4/2 E4/2 Eb4/2 D4/2 Db4/2 C4/2 | B3/2 Bb3/2 A3/2 Ab3/2 G3/8 | G3/2 Ab3/2 G3/2 F#3/2 F3/4 E3/4 | Eb3/2 D3/2 Eb3/2 D3/2 C#3/8 | G4/2 F#4/2 F4/2 E4/2 Eb4/2 D4/2 Db4/2 C4/2 | B3/2 Bb3/2 A3/2 Ab3/2 G3/8`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
LB   · · · · · · · · ● ○ ● ○ ● ○ ● ○
KB   ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ●
TU   · · · · · · · · · · · ● ● ● ● ●
GS   · · · · ● ● ● ● ● ● ● ● ● ● ● ●
HM   · · · · · · · · ● ● ● ● ● ● · ·
```

- **Zusammenhang der Rollen:** Ein chromatisches Subjekt (HE-M41) im Kurzen Bass; Einsätze im Abstand von vier Takten in Gegenstimme (auf G) und Hauptmelodie (auf C, eine Oktave höher), der vierte Einsatz – nur der Kopf, im Tupfer – kommt einen Takt zu früh (Takt 12 statt 13). Kontrasubjekt sind leere chromatische Abwärtsskalen (HE-M42). Ab Takt 9 liegt ein tiefes Pedal C1.
- **Dynamik:** p → mf; jede neue Stimme bringt etwas Lautstärke mit, die einzelnen Stimmen bleiben gleich laut. · **Pausen:** Hauptmelodie pausiert in Takt 15–16; die Fläche fehlt ganz.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Hauptmelodie: Einsätze in KB, GS, TU; die Maschine läuft weiter, nur dünner. Ohne Gegenstimme fehlt der zweite Einsatz, die Wirkung bleibt.
- **Variation:** Hauptmelodie-Einsatz weglassen (drei Stimmen genügen); Einsätze im Achttaktabstand (32 Takte). · **Fortsetzung:** HE-S23 oder HE-T11 (Unterbrechung).
- **Bezug:** HE-M41, HE-M42, HE-R43, HE-R44, HE-B39
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 1 1 1 1 2 2 2 2 4 3 4 4 5 4 4 3; Melodietöne auf Zählzeiten als Akkordton: HM 7/21, GS 21/42; MIDI `HE-S21.mid`, 227 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): HM 12/23/0, GS 24/48/0
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Lange Noten in Kurzrolle, Kanon/koordinierte Parallelstimmen, Notierte Linie in Begleitrolle

### HE-S22 · Langsam wachsende Bedrohung durch Verschmelzung

- **Charakter:** Etwas kommt durch den Wald näher, sehr langsam.
- **XYZ-Anker:** 0,15 / 0,30 / 0,60 (DRm) → 0,15 / 0,70 / 0,70 (DIU), Fahrt in der zweiten Hälfte · **Länge:** 16 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 54–66 (MIDI-Beispiel ♩ = 60) · **Harmonik:** HE-H60 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `Bm|Cm` (×16)

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 48, 3 Stimmen | 1–16 | 46 |
| KF Kurze Fläche | `......x---......\|......x---......\|......x---......\|......x---......\|....x---........\|....x---........\|....x---........\|....x---........\|..x-----........\|..x-----........\|..x-----........\|..x-----........\|x-------........\|x-------........\|x-------........\|x-------........` | Akkordtöne eng ab MIDI 83, 3 Stimmen (Register je Takt: 83 83 83 83 71 71 71 71 59 59 59 59 47 47 47 47) | 1–16 | 46 |
| LB Langer Bass | `x---------------\|----------------  (wiederholt)` | fest: C2 | 1–16 | 46 |

- **Nicht beteiligt:** Kurzer Bass, Arpeggio, Tupfer, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
LF   ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ●
KF   ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ●
LB   ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○
```

- **Zusammenhang der Rollen:** Über 16 Takte ändert sich weder Material noch Velocity noch Notenzahl (je Takt ein C-Moll- und ein H-Moll-Anschlag). Es ändern sich nur Lage und Zeitpunkt der oberen Schicht: sie sinkt alle vier Takte eine Oktave (B5 → B2) und rückt zeitlich an die untere heran (Einsatz auf 2+, 2, 1+, 1). Ab Takt 13 liegen die Schichten ineinander und setzen gleichzeitig ein.
- **Dynamik:** pp konstant (Velocity 46 in allen Rollen). · **Pausen:** Die obere Schicht klingt jeweils nur eine Halbe.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** Rückweg in 16 Takten (Entkopplung) als Fortsetzung – die Bedrohung bleibt, wird aber wieder rätselhaft. · **Fortsetzung:** HE-S23 oder HE-T13.
- **Bezug:** HE-H60, HE-H53, HE-S27
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 2 3 2 3 2 3 2 3 2 3 2 3 2 3 2; keine Melodierolle; MIDI `HE-S22.mid`, 104 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Lange Noten in Kurzrolle, Exakte Registervorgabe, Mehrere harmonische Komponenten

### HE-S23 · Eskalation in vier Stufen

- **Charakter:** Die Gewissheit wächst, dann der Angriff.
- **XYZ-Anker:** 0,15 / 0,40 / 0,60 (Dmm) → 0,20 / 0,90 / 0,85 (DIU), Fahrt in der zweiten Hälfte · **Länge:** 16 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 80–96 (MIDI-Beispiel ♩ = 88) · **Harmonik:** HE-H53 → HE-H54 → HE-H61 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `Bm|Cm` | `Bm|Cm` | `Bm|Cm` | `Bm|Cm` | `Bm|Cm` | `Bm|Cm` | `Bm|Cm` | `Bm|Cm` | `Dbm|Cm` | `Dbm|Cm` | `Dbm|Cm` | `Dbm|Cm` | `C#m|Cm` | `Dm|C#m` | `Ebm|Dm` | `Em|Ebm`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 48, 3 Stimmen | 1–16 | 55 · Dynamik je Takt ×0,85 0,85 0,85 0,85 0,90 0,90 0,90 0,90 1,00 1,00 1,00 1,00 1,15 1,15 1,15 1,15 |
| KF Kurze Fläche | `....x---........\|....x---........\|....x---........\|....x---........\|x---............\|x---............\|x---............\|x---............\|x.x.x...x.x.x...\|x.x.x...x.x.x...\|x.x.x...x.x.x...\|x.x.x...x.x.x...\|X.x.X.x.X.x.X.x.\|X.x.X.x.X.x.X.x.\|X.x.X.x.X.x.X.x.\|X.x.X.x.X.x.X.x.` | Akkordtöne eng ab MIDI 78, 3 Stimmen (Register je Takt: 78 78 78 78 49 49 49 49 49 49 49 49 49 49 49 49) | 1–16 | 58 · Dynamik je Takt ×0,85 0,85 0,85 0,85 0,90 0,90 0,90 0,90 1,00 1,00 1,00 1,00 1,15 1,15 1,15 1,15 |
| KB Kurzer Bass | `................\|................\|................\|................\|................\|................\|................\|................\|..x...x.x.....x.\|...x....x...x...\|..x...x.x.....x.\|...x....x...x...\|..x...x.x.....x.\|...x....x...x...\|..x...x.x.....x.\|...x....x...x...` | Bass-Töne `R -8 R -8 P(F#1)` ab MIDI 36 | 9, 10, 11, 12, 13, 14, 15, 16 | 62 |
| TU Tupfer | `..........x.....\|................\|...x............\|................  (wiederholt)` | oberster Akkordton ab MIDI 74, dann abwärts zyklisch | 1, 2, 3, 4 | 40 |
| ST Stich | `................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|X...............\|................\|................\|................` | fester Trigger C2 (nie transponiert) | 1–16 | 100 |

- **Nicht beteiligt:** Langer Bass, Arpeggio, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
LF   ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ●
KF   ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ●
KB   · · · · · · · · ● ● ● ● ● ● ● ●
TU   ● · ● · · · · · · · · · · · · ·
ST   · · · · · · · · · · · · ● · · ·
```

- **Zusammenhang der Rollen:** Stufe 1 (Takt 1–4): H-Moll über C-Moll, weit getrennt, oben versetzt. Stufe 2 (5–8): gleiche Klänge, obere Schicht ineinander geschoben und synchron – Verschmelzung zuerst. Stufe 3 (9–12): obere Schicht rückt einen Halbton (D♭-Moll, kleine Sekunden statt großer Septimen), der Kurze Bass setzt mit Gegenrhythmus ein – Dissonanzschärfe. Stufe 4 (13–16): verschmolzene Polychorde steigen chromatisch, Akzente, ein Stich zu Beginn – erst jetzt Dichte und Dynamik.
- **Dynamik:** p → mf → f → ff, aber erst ab Stufe 3 deutlich. · **Pausen:** Tupfer nur in Stufe 1; danach keine Pausen mehr in der Kurzen Fläche.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** Stufe 4 weglassen und Stufe 3 halten (Spannung ohne Ausbruch). · **Fortsetzung:** HE-S15, HE-T13 oder Wiederholung von Stufe 4.
- **Bezug:** HE-H53, HE-H54, HE-H61, HE-R33, HE-B12
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 2 3 2 2 2 2 2 3 3 3 3 4 3 3 3; keine Melodierolle; MIDI `HE-S23.mid`, 271 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Exakte Registervorgabe, Mehrere harmonische Komponenten

### HE-S24 · Modul-Labyrinth

- **Charakter:** Flucht im Auto bei Nacht; die Straße nimmt kein Ende.
- **XYZ-Anker:** 0,25 / 0,50 / 0,65 (DmU) · **Länge:** 16 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 100–116 (MIDI-Beispiel ♩ = 108) · **Harmonik:** HE-H36 mit Interpunktion HE-H01, HE-H25 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `Cm` | `Cm` | `Cm` | `CmM7` | `C#m` | `C#m` | `C#m` | `G7b9` | `Cm` | `Cm` | `Cm` | `CmM7` | `C#m` | `C#m` | `G7b9` | `CmM7`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `................\|................\|................\|X..X..X...X..X..\|................\|................\|................\|X--x....X--x....\|................\|................\|................\|X..X..X...X..X..\|................\|................\|X--x....X--x....\|X..X..X...X..X..` | Akkordtöne eng ab MIDI 57, 4 Stimmen | 1–16 | 72 |
| LB Langer Bass | `x---------------\|----------------  (wiederholt)` | fest: C2 | 1–16 | 44 |
| KB Kurzer Bass | `................\|................\|................\|................\|................\|................\|................\|.....x.......x..\|................\|................\|................\|................\|................\|................\|.....x.......x..\|................` | Bass-Töne `R` ab MIDI 36 | 1–16 | 60 |
| AR Arpeggio | `x.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.\|................\|x.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.\|................\|x.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.\|................\|x.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.\|................\|................` | Akkordtöne (4) ab MIDI 60 über 2 Oktaven, auf und ab | 1–16 | 48 |

- **Nicht beteiligt:** Lange Fläche, Tupfer, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
KF   · · · ● · · · ● · · · ● · · ● ●
LB   ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○
KB   · · · · · · · ● · · · · · · ● ·
AR   ● ● ● · ● ● ● · ● ● ● · ● ● · ·
```

- **Zusammenhang der Rollen:** Bewegungsmodul (Arpeggio in Achteln) und zwei Interpunktionsmodule: A = fünf synkopierte Schläge auf dem Moll-Dur-Septakkord, C = punktierte Blockakkorde auf G7♭9 mit Bassantwort. Das Bewegungsmodul erscheint drei-, drei-, drei- und zweimal; A schließt die erste und dritte Gruppe, C wird unregelmäßig eingeschoben. Das Pedal C ist der Leim.
- **Dynamik:** p, Interpunktion mf. · **Pausen:** Arpeggio schweigt in jedem Interpunktionstakt.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** Reihenfolge der Interpunktionen würfeln; Bewegungsmodul 4 Takte lang (Dehnung). · **Fortsetzung:** Wiederholung mit gestrichenen Modulen (HE-T01) oder HE-S23.
- **Bezug:** HE-R21, HE-R14, HE-R15, HE-H36, HE-B11
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 1 2 1 2 1 2 2 2 1 2 1 2 1 3 1; keine Melodierolle; MIDI `HE-S24.mid`, 192 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Pedal über Akkordwechsel

### HE-S25 · Obsession über 32 Takte

- **Charakter:** Tage der Beschattung; jemand wird zur Besessenheit eines anderen.
- **XYZ-Anker:** 0,30 / 0,25 / 0,60 (DRm) · **Länge:** 32 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 66–80 (MIDI-Beispiel ♩ = 72) · **Harmonik:** HE-H26 (Takt 1–16), HE-H27 (17–32) · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `C7` | `C7` | `F#7b5` | `F#7b5` | `C7` | `C7` | `F#7b5` | `F#7b5` | `C7` | `C7` | `F#7b5` | `F#7b5` | `C7` | `C7` | `F#7b5` | `F#7b5` | `C7` | `C7` | `F#7b5` | `F#7b5` | `Eaug` | `Eaug` | `C7` | `C7` | `C7` | `C7` | `F#7b5` | `F#7b5` | `Eaug` | `Eaug` | `C7` | `C7`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `................\|................\|................\|................\|................\|................\|................\|................\|x---------------\|----------------\|x---------------\|----------------\|x---------------\|----------------\|x---------------\|----------------\|x---------------\|----------------\|x---------------\|----------------\|x---------------\|----------------\|x---------------\|----------------\|................\|................\|................\|................\|................\|................\|................\|................` | Akkordtöne ohne Bass, eng ab MIDI 55, 3 Stimmen | 1–32 | 34 |
| KF Kurze Fläche | `x.x---x.x...x.x.\|x.x---x.x...x.x.\|x.x---x.x...x.x.\|x.x---x.x...x.x.\|x.x---x.x...x.x.\|x.x---x.x...x.x.\|x.x---x.x...x.x.\|x.x---x.x...x.x.\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|x.x---x.x...x.x.\|x.x---x.x...x.x.\|x.x---x.x...x.x.\|x.x---x.x...x.x.\|x.x---x.x...x.x.\|x.x---x.x...x.x.\|x.x---x.x...x.x.\|x.x---x.x...x.x.` | Akkordtöne eng ab MIDI 58, 3 Stimmen | 1–32 | 44 |
| LB Langer Bass | `x---------------\|----------------  (wiederholt)` | fest: E2 | 1–32 | 36 |
| KB Kurzer Bass | `................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|x.x...x.x...x.x.\|x.x...x.x...x.x.\|x.x...x.x...x.x.\|x.x...x.x...x.x.\|x.x...x.x...x.x.\|x.x...x.x...x.x.\|x.x...x.x...x.x.\|x.x...x.x...x.x.\|................\|................\|................\|................\|................\|................\|................\|................` | Bass-Töne `R 5 R` ab MIDI 36 | 1–32 | 40 |
| AR Arpeggio | `................\|................\|................\|................\|................\|................\|................\|................\|x.x---x.x...x.x.\|x.x---x.x...x.x.\|x.x---x.x...x.x.\|x.x---x.x...x.x.\|x.x---x.x...x.x.\|x.x---x.x...x.x.\|x.x---x.x...x.x.\|x.x---x.x...x.x.\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................` | Akkordtöne (4) ab MIDI 67 über 2 Oktaven, aufwärts zyklisch | 1–32 | 42 |
| TU Tupfer | `................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|................\|x.......x.......\|x.......x.......\|x.......x.......\|x.......x.......\|x.......x.......\|x.......x.......\|x.......x.......\|x.......x.......` | fest: E5 | 1–32 | 30 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–32 | 44 |

- **Nicht beteiligt:** Stich, Hauptmelodie
- **Gegenstimme:** `r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | E4/2 F4/2 G4/4 F4/2 E4/6 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | E4/2 F4/2 G4/4 F4/2 E4/6 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32
LF   · · · · · · · · ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ · · · · · · · ·
KF   ● ● ● ● ● ● ● ● · · · · · · · · · · · · · · · · ● ● ● ● ● ● ● ●
LB   ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○
KB   · · · · · · · · · · · · · · · · ● ● ● ● ● ● ● ● · · · · · · · ·
AR   · · · · · · · · ● ● ● ● ● ● ● ● · · · · · · · · · · · · · · · ·
TU   · · · · · · · · · · · · · · · · · · · · · · · · ● ● ● ● ● ● ● ●
GS   · · · · · · · · · · · · ● · · · · · · · ● · · · · · · · · · · ·
```

- **Zusammenhang der Rollen:** Der Synkopenrhythmus bleibt 32 Takte lang derselben Gestalt, wandert aber: Kurze Fläche (1–8), Arpeggio (9–16), Kurzer Bass mit kurzen Notenlängen (17–24), wieder Kurze Fläche mit repetiertem Pedalton im Tupfer (25–32). Ab Takt 17 wechselt die Harmonik vom Zweierpendel zum Kreis über Eaug. E liegt die ganze Zeit im Langen Bass. Die Gegenstimme bringt nur zweimal die symmetrische Zelle.
- **Dynamik:** pp über 32 Takte; keine Steigerung. · **Pausen:** In jeder Station schweigen die anderen Bewegungsrollen; in den Stationen ohne Kurze Fläche hält eine leise Lange Fläche den Klang, damit die Klangdichte gleich bleibt.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Gegenstimme unverändert wirksam; sie ist eine Zugabe.
- **Variation:** Stationen in anderer Reihenfolge; Takt 25–32 in höherer Lage der Kurzen Fläche (reg 70). · **Fortsetzung:** beliebig lange weiter mit neuer Station (TU-Repetition allein, HE-R36) oder HE-T08.
- **Bezug:** HE-R03, HE-R53, HE-H26, HE-H27, HE-M10
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 1 2 1 2 1 2 1 3 1 3 1 4 1 3 1 3 1 3 1 4 1 3 1 3 2 3 2 3 2 3 2; Melodietöne auf Zählzeiten als Akkordton: GS 3/6; MIDI `HE-S25.mid`, 450 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 5/5/0
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Exakte Registervorgabe, Rollenwanderung

### HE-S26 · Gleichbleibende latente Spannung über 32 Takte

- **Charakter:** Eine lange Nacht in einem Haus, in dem nichts geschieht – noch nicht.
- **XYZ-Anker:** 0,20 / 0,15 / 0,40 (DRm) · **Länge:** 32 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 50–62 (MIDI-Beispiel ♩ = 56) · **Harmonik:** HE-H01, HE-H67, HE-H05, HE-H01 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7` | `Cm/Db` | `Cm/Db` | `Cm/Db` | `Cm/Db` | `Cm/Db` | `Cm/Db` | `Cm/Db` | `Cm/Db` | `CmM7/F#` | `CmM7/F#` | `CmM7/F#` | `CmM7/F#` | `CmM7/F#` | `CmM7/F#` | `CmM7/F#` | `CmM7/F#` | `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `......x---------\|----------------\|------x---------\|----------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 51, 3 Stimmen | 1–32 | 38 |
| LB Langer Bass | `x---------------\|----------------  (wiederholt)` | Bass-Töne `b` ab MIDI 25 | 1–32 | 40 |
| TU Tupfer | — | notiert (siehe unten) | 1–32 | 34 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Arpeggio, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32
LF   ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○
LB   ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○
TU   · ● · · · · ● · · · ● · ● · · ● · ● · · · ● · · · ● · · · · ● ·
```

- **Zusammenhang der Rollen:** Vier Abschnitte zu acht Takten auf derselben Spannungshöhe: mM7 (1–8), Moll über Halbtonbass D♭ (9–16), mM7 über Tritonusbass (17–24), mM7 (25–32). Die Fläche setzt nur auf unbetonten Zeiten neu an. Der Tupfer wechselt pro Abschnitt die Zelle: Seufzer (HE-M02), Halbtonpaar mit wachsender Pause (HE-M37), Liegeton mit Vorschlag (HE-M51), hohes Echo (HE-M36). Variation verhindert Monotonie, ohne die Spannung abzubauen oder zu steigern.
- **Dynamik:** ppp–pp über die ganze Länge. · **Pausen:** Mehr Pause als Ton im Tupfer.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme; der Tupfer trägt die Zellen.
- **Variation:** Abschnitte umstellen; Abschnitt 3 als 16 Takte (Dehnung). · **Fortsetzung:** HE-S22 (wenn die Szene kippt) oder unverändert weiter.
- **Bezug:** HE-H01, HE-H67, HE-H05, HE-R59, HE-M02, HE-M37, HE-M51, HE-M36
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 1 2 0 2 0 3 0 2 0 3 0 3 0 2 1 2 1 2 0 2 1 2 0 2 1 2 0 2 0 3 0; keine Melodierolle; MIDI `HE-S26.mid`, 81 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Lange Noten in Kurzrolle, Notierte Linie in Begleitrolle

### HE-S27 · Ein Material, vier Behandlungen

- **Charakter:** Vier Fassungen desselben Klangs, als Vorführung für den Generator.
- **XYZ-Anker:** 0,15 / 0,25 / 0,55 (DRm) → 0,15 / 0,60 / 0,65 (DmU), Fahrt in der zweiten Hälfte · **Länge:** 16 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 54–66 (MIDI-Beispiel ♩ = 60) · **Harmonik:** HE-H53 (unverändert) · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `Bm|Cm` (×16)

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------\|x---------------\|x---------------\|x---------------\|x---------------\|x---------------\|x---------------\|x---------------\|x---------------\|x---------------\|x---------------\|x---------------\|x-------........\|x-------........\|x-------........\|x-------........` | Akkordtöne ohne Bass, eng ab MIDI 48, 3 Stimmen | 1–16 | 50 |
| KF Kurze Fläche | `........x-------\|........x-------\|........x-------\|........x-------\|........x-------\|........x-------\|........x-------\|........x-------\|x---------------\|x---------------\|x---------------\|x---------------\|x-------........\|x-------........\|x-------........\|x-------........` | Akkordtöne eng ab MIDI 83, 3 Stimmen (Register je Takt: 83 83 83 83 47 47 47 47 47 47 47 47 47 47 47 47) | 1–16 | 50 |

- **Nicht beteiligt:** Langer Bass, Kurzer Bass, Arpeggio, Tupfer, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
LF   ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ●
KF   ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ●
```

- **Zusammenhang der Rollen:** In allen vier Abschnitten: gleiche Tonklassen, gleiche Velocity (50), gleiche Notenzahl (24 je Abschnitt). Abschnitt 1 (Takt 1–4): Register getrennt (H-Moll ab B5), oben versetzt auf 3, beide lang – rätselhaft. Abschnitt 2 (5–8): nur das Register ändert sich (H-Moll ab B2, zwischen die C-Moll-Töne) – dumpfer, bedrängender. Abschnitt 3 (9–12): zusätzlich gleichzeitig – verschmolzen, bedrohlich. Abschnitt 4 (13–16): zusätzlich kurz (eine Halbe, dann Stille) – ein Signal, akut.
- **Dynamik:** p konstant. · **Pausen:** Abschnitt 4: halber Takt Stille nach jedem Schlag.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** Reihenfolge umkehren (akut → rätselhaft) als Beispiel für Entkopplung. · **Fortsetzung:** HE-S22, HE-S23.
- **Bezug:** HE-H53, HE-S06, HE-S07, HE-S22
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2; keine Melodierolle; MIDI `HE-S27.mid`, 96 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Lange Noten in Kurzrolle, Exakte Registervorgabe, Mehrere harmonische Komponenten

### HE-S28 · Frage und Antwort im Thriller

- **Charakter:** Ein Verhör, bei dem jede Antwort zu spät kommt.
- **XYZ-Anker:** 0,25 / 0,45 / 0,55 (Dmm) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 84–100 (MIDI-Beispiel ♩ = 92) · **Harmonik:** HE-H82 · **Tonvorrat:** Moll gesamt
- **Akkorde je Takt:** `Cm` | `Cm` | `G7b9` | `G7b9` | `Ab` | `Ab` | `G7b9` | `G7b9`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------\|----------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 48, 3 Stimmen | 1–8 | 40 |
| KF Kurze Fläche | `x.x.............\|................  (wiederholt)` | Akkordtöne eng ab MIDI 57, 4 Stimmen | 1–8 | 62 |
| KB Kurzer Bass | `......x.x.......\|................\|.........x......\|................  (wiederholt)` | Bass-Töne `R R 5` ab MIDI 36 | 1–8 | 58 |

- **Nicht beteiligt:** Langer Bass, Arpeggio, Tupfer, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ○ ● ○ ● ○ ● ○
KF   ● · ● · ● · ● ·
KB   ● · ● · ● · ● ·
```

- **Zusammenhang der Rollen:** Die Kurze Fläche fragt mit zwei Schlägen, der Kurze Bass antwortet versetzt; die zweite Antwort ist kürzer und später. Die Harmonik deutet eine Kadenz an und verweigert sie: Am Ende steht G7♭9.
- **Dynamik:** p, Fragen mp. · **Pausen:** Jeder zweite Takt leer bis auf die Fläche.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** Antwort in Takt 7 auslassen. · **Fortsetzung:** HE-S24 oder HE-H25.
- **Bezug:** HE-R60, HE-B27, HE-H82
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 0 3 0 3 0 3 0; keine Melodierolle; MIDI `HE-S28.mid`, 46 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte

### HE-S29 · Mystery: Ein Ton, vier Bedeutungen

- **Charakter:** Ein Detektiv findet an jedem Ort denselben Gegenstand.
- **XYZ-Anker:** 0,30 / 0,20 / 0,50 (DRm) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 52–64 (MIDI-Beispiel ♩ = 58) · **Harmonik:** HE-H44 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `Cm` | `Cm` | `Ab/C` | `Ab/C` | `Dbmaj7/C` | `Dbmaj7/C` | `F#7b5/C` | `F#7b5/C`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------\|----x-----------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 55, 3 Stimmen | 1–8 | 40 |
| LB Langer Bass | `x---------------\|----------------  (wiederholt)` | fest: C2 | 1–8 | 42 |
| TU Tupfer | — | notiert (siehe unten) | 1–8 | 36 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Arpeggio, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ● ● ● ● ● ● ●
LB   ● ○ ● ○ ● ○ ● ○
TU   · ● · ● · ● · ●
```

- **Zusammenhang der Rollen:** Das Pedal C bleibt; darüber ist es nacheinander Grundton, Terz, große Septime und Tritonus. Die Fläche atmet ungleichmäßig (fünf plus drei Viertel). Der Tupfer spielt in jedem zweiten Takt eine Doppelnachbar-Zelle um einen Ton des jeweiligen Klangs.
- **Dynamik:** pp. · **Pausen:** Tupfer nur in geraden Takten.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme; die Zellen liegen im Tupfer.
- **Variation:** Reihenfolge der Klänge umkehren. · **Fortsetzung:** HE-S19 oder HE-S26.
- **Bezug:** HE-H44, HE-R54, HE-M38
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 2 2 2 2 2 2 2; keine Melodierolle; MIDI `HE-S29.mid`, 42 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Notierte Linie in Begleitrolle

### HE-S30 · Dunkles Drama

- **Charakter:** Ein Vater erfährt, wer sein Sohn wirklich ist.
- **XYZ-Anker:** 0,30 / 0,45 / 0,35 (DmS) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 54–66 (MIDI-Beispiel ♩ = 60) · **Harmonik:** HE-H78 · **Tonvorrat:** Moll gesamt
- **Akkorde je Takt:** `Cmadd9` | `Cmadd9` | `Ab` | `Ab` | `Fm9` | `Fm9` | `CmM7` | `CmM7`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------\|----------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 50, 4 Stimmen | 1–8 | 55 |
| LB Langer Bass | `x---------------\|----------------  (wiederholt)` | Bass-Töne `R` ab MIDI 36 | 1–8 | 58 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 48 |
| HM Hauptmelodie | — | notiert (siehe unten) | 1–8 | 64 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Arpeggio, Tupfer, Stich
- **Hauptmelodie:** `Eb4/6 D4/2 F4/6 Eb4/2 | G4/16 | G4/6 F4/2 Ab4/8 | C5/16 | C5/6 Bb4/2 Ab4/4 G4/4 | Ab4/16 | B4/16 | r/16`
- **Gegenstimme:** `r/16 | r/8 Eb4/6 D4/2 | r/16 | r/8 C4/6 Bb3/2 | r/16 | r/8 Ab3/6 G3/2 | r/16 | B3/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ○ ● ○ ● ○ ● ○
LB   ● ○ ● ○ ● ○ ● ○
GS   · ● · ● · ● · ●
HM   ● ● ● ● ● ● ● ·
```

- **Zusammenhang der Rollen:** Die lyrische Linie steigt in Vorhaltpaaren und endet auf der großen Septime über C-Moll; die Gegenstimme antwortet in jedem zweiten Takt mit einem Seufzer, wenn die Hauptmelodie liegt. Kein Rhythmusmodul.
- **Dynamik:** mp, Takt 4–5 mf. · **Pausen:** Hauptmelodie schweigt in Takt 8; Gegenstimme füllt nur Haltetöne.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Hauptmelodie bleibt eine dunkle, unaufgelöste Folge mit Seufzern; ohne beide Melodierollen trägt die Harmonik mit dem offenen Schluss.
- **Variation:** Hauptmelodie weglassen: Fläche, Bass und Seufzer-Gegenstimme genügen. · **Fortsetzung:** HE-S16 oder HE-H45.
- **Bezug:** HE-H78, HE-P13, HE-M40
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 2 3 2 3 2 3 1; Melodietöne auf Zählzeiten als Akkordton: HM 9/11, GS 4/4; MIDI `HE-S30.mid`, 41 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): HM 11/4/0, GS 6/1/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### HE-S31 · Fast nichts

- **Charakter:** Jemand liegt wach und lauscht.
- **XYZ-Anker:** 0,20 / 0,10 / 0,35 (DRS) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 46–58 (MIDI-Beispiel ♩ = 52) · **Harmonik:** HE-H81 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `{C G Ab}` | `{C G Ab}` | `{C G Ab}` | `{C G Ab}` | `{C G Ab}` | `{C G Ab}` | `{C G Ab}` | `{C G Ab}`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x-------x-------\|x-------........\|x-------x-------\|........x-------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 48, 3 Stimmen | 1–8 | 34 |
| TU Tupfer | `................\|................\|................\|..........x.....  (wiederholt)` | oberster Akkordton ab MIDI 80, dann abwärts zyklisch | 1–8 | 30 |

- **Nicht beteiligt:** Kurze Fläche, Langer Bass, Kurzer Bass, Arpeggio, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ● ● ● ● ● ● ●
TU   · · · ● · · · ●
```

- **Zusammenhang der Rollen:** Eine leere Quinte mit einem Halbtonnachbarn in Halben, die einmal pro Gruppe ausbleiben; ein einziger Tupfer pro vier Takte. Sehr leise, kaum Bewegung – und trotzdem nicht beruhigend, weil A♭ an G reibt und die Lücke unvorhersehbar ist.
- **Dynamik:** ppp. · **Pausen:** Lücke in Takt 2 bzw. 4 jeder Gruppe.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** A♭ durch F♯ ersetzen (Halbton → Tritonus). · **Fortsetzung:** HE-S01 oder HE-S26.
- **Bezug:** HE-H81, HE-R58, HE-R35
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 1 1 1 2 1 1 1 2; keine Melodierolle; MIDI `HE-S31.mid`, 38 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte

### HE-S32 · Gegenstimme als zweite Polyschicht

- **Charakter:** Im Spiegel ist für einen Moment ein zweites Gesicht.
- **XYZ-Anker:** 0,20 / 0,20 / 0,60 (DRm) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 54–66 (MIDI-Beispiel ♩ = 60) · **Harmonik:** HE-H63 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `Ebm|Am` | `Ebm|Am` | `Ebm|Am` | `Ebm|Am` | `Ebm|Am` | `Ebm|Am` | `Ebm|Am` | `Ebm|Am`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `x-------........\|................  (wiederholt)` | Akkordtöne eng ab MIDI 57, 3 Stimmen | 1–8 | 40 |
| LB Langer Bass | `x---------------\|----------------  (wiederholt)` | fest: A1 | 1–8 | 36 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 42 |

- **Nicht beteiligt:** Lange Fläche, Kurzer Bass, Arpeggio, Tupfer, Stich, Hauptmelodie
- **Gegenstimme:** `r/2 Eb4/6 Gb4/4 Bb4/4 | Gb4/16 | r/2 Eb4/6 Gb4/4 Bb4/4 | Gb4/8 r/8 | r/2 Eb4/6 Gb4/4 Bb4/4 | Gb4/16 | r/4 Eb4/4 Gb4/4 Bb4/4 | r/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
KF   ● · ● · ● · ● ·
LB   ● ○ ● ○ ● ○ ● ○
GS   ● ● ● ● ● ● ● ·
```

- **Zusammenhang der Rollen:** Untere Schicht A-Moll als kurzer Anschlag alle zwei Takte; die Gegenstimme bringt die obere Schicht E♭-Moll als gebrochene Linie, immer eine Achtel nach dem Anschlag (zeitversetzt). In Takt 7 rückt der Versatz auf eine Viertel: die Schichten lösen sich weiter.
- **Dynamik:** pp, Gegenstimme ein Grad lauter als die Fläche. · **Pausen:** Gegenstimme pausiert in Takt 8.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Gegenstimme fehlt die obere Schicht; dann HE-S06 verwenden (gleiche Idee mit Arpeggio).
- **Variation:** Obere Schicht im Tupfer statt in der Gegenstimme (gleiche Töne, anderer Charakter). · **Fortsetzung:** HE-S06 oder HE-T08.
- **Bezug:** HE-H63, HE-R60
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 1 3 1 3 1 3 0; Melodietöne auf Zählzeiten als Akkordton: GS 12/12; MIDI `HE-S32.mid`, 31 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 15/0/0
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Lange Noten in Kurzrolle, Exakte Registervorgabe, Mehrere harmonische Komponenten

### HE-S33 · Hemiolen-Unruhe im Tritonuspendel

- **Charakter:** Eine Hetzjagd durch ein sonniges Kornfeld.
- **XYZ-Anker:** 0,50 / 0,60 / 0,80 (mmU) · **Länge:** 8 Takte · **Taktart:** 6/8 · **Tempo:** ♪ = 140–160 (MIDI ♩ = 150) (MIDI-Beispiel ♩ = 150) · **Harmonik:** HE-H38 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `C` | `C` | `F#` | `F#` | `C` | `C` | `F#` | `F#`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `X.x.x.X.x.x.\|X.x.X.x.X.x.  (wiederholt)` | Akkordtöne eng ab MIDI 60, 3 Stimmen | 1–8 | 64 |
| KB Kurzer Bass | `x...x...x...\|x.....x.....  (wiederholt)` | Bass-Töne `R` ab MIDI 36 | 1–8 | 60 |
| TU Tupfer | `............\|..........x.\|............\|....x.......  (wiederholt)` | oberster Akkordton ab MIDI 84, dann abwärts zyklisch | 1–8 | 44 |

- **Nicht beteiligt:** Lange Fläche, Langer Bass, Arpeggio, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
KF   ● ● ● ● ● ● ● ●
KB   ● ● ● ● ● ● ● ●
TU   · ● · ● · ● · ●
```

- **Zusammenhang der Rollen:** Die Kurze Fläche spielt durchgehend Achtel; im ersten Takt jeder Gruppe liegen ihre Akzente auf 1 und 4 (6/8), im zweiten auf 1, 3 und 5 (3/4). Der Kurze Bass liest jeweils die andere Taktart. Das Tritonuspendel C ↔ F♯ macht die Helligkeit fremd.
- **Dynamik:** mf, Akzente f. · **Pausen:** Tupfer nur in den Takten 2 und 4 jeder Gruppe.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** KB-Takte vertauschen (beide Rollen in derselben Taktart, weniger Reibung). · **Fortsetzung:** HE-S13 oder HE-T05.
- **Bezug:** HE-R10, HE-B23, HE-H38
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 3 2 3 2 3 2 3; keine Melodierolle; MIDI `HE-S33.mid`, 168 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte

### HE-S34 · Homorhythmik zerbricht

- **Charakter:** Ein Mensch entdeckt die Leiche.
- **XYZ-Anker:** 0,15 / 0,75 / 0,85 (DIU) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 116–138 (MIDI-Beispiel ♩ = 126) · **Harmonik:** HE-H34 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `{C D Eb B}` | `{Db Eb E C}` | `{D E F Db}` | `{Db Eb E C}` | `{C D Eb B}` | `{B Db D Bb}` | `{Bb C Db A}` | `{B Db D Bb}`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `x...x...x...x...\|x...x...x...x...\|x...x...x...x...\|x...x...x...x...\|................\|................\|................\|................` | Akkordtöne eng ab MIDI 60, 4 Stimmen | 1–8 | 78 |
| LB Langer Bass | `................\|................\|................\|................\|x---------------\|----------------\|x---------------\|----------------` | Bass-Töne `R` ab MIDI 24 | 1–8 | 76 |
| KB Kurzer Bass | `x...x...x...x...\|x...x...x...x...\|x..x..x..x..x...\|.x..x..x..x..x..\|................\|................\|................\|................` | Bass-Töne `R 8 R` ab MIDI 36 | 1–8 | 74 |
| AR Arpeggio | `................\|................\|................\|................\|XxxXxxXxxXxxXxxX\|XxxXxxXxxXxxXxxX\|XxxXxxXxxXxxXxxX\|XxxXxxXxxXxxXxxX` | Akkordtöne (4) ab MIDI 62 über 2 Oktaven, auf und ab | 1–8 | 70 |

- **Nicht beteiligt:** Lange Fläche, Tupfer, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
KF   ● ● ● ● · · · ·
LB   · · · · ● ○ ● ○
KB   ● ● ● ● · · · ·
AR   · · · · ● ● ● ●
```

- **Zusammenhang der Rollen:** Takt 1–2: Fläche und Bass im Gleichschritt auf dem Reibungsvierklang; Takt 3–4: der Bass fällt in Dreiergruppen aus dem Takt. Ab Takt 5 rasen Sechzehntel in Dreiergruppen im Arpeggio über zweitaktigen Basstönen; die Kurze Fläche schweigt.
- **Dynamik:** f, ab Takt 5 ff. · **Pausen:** keine.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** Störung schon ab Takt 2. · **Fortsetzung:** HE-S15 oder HE-T13.
- **Bezug:** HE-H34, HE-R34, HE-R12, HE-B24, HE-B25
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 2 2 2 2 1 2 1; keine Melodierolle; MIDI `HE-S34.mid`, 148 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte

### HE-S35 · Kalte, helle Mystery

- **Charakter:** Ein verlassenes Observatorium im Schnee.
- **XYZ-Anker:** 0,70 / 0,15 / 0,40 (HRm) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 48–60 (MIDI-Beispiel ♩ = 54) · **Harmonik:** HE-H97, HE-H101 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `{C G D F#}` | `{C G D F#}` | `{C G D F#}` | `{C G D F#}` | `{B E A D#}` | `{B E A D#}` | `{B E A D#}` | `{B E A D#}`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------\|----------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 55, 4 Stimmen | 1–8 | 34 |
| LB Langer Bass | `x---------------\|----------------\|x---------------\|----------------\|................\|................\|................\|................` | fest: C2 | 1–8 | 26 |
| AR Arpeggio | `................\|................\|..........x.x...\|................\|................\|....x.x.........\|................\|................` | fest: D#6 | 1–8 | 28 |
| TU Tupfer | — | notiert (siehe unten) | 1–8 | 34 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ○ ● ○ ● ○ ● ○
LB   ● ○ ● ○ · · · ·
AR   · · ● · · ● · ·
TU   · ● · · · · ● ·
```

- **Zusammenhang der Rollen:** Quinten- und Quartenklang in offener Lage (C4–G4–D5–F♯5), sehr leise; ab Takt 5 ohne Bass und einen Halbton tiefer gerückt (HE-H101). Der Tupfer spielt zweimal den kalten Glockenruf (Tritonus), das Arpeggio zwei glasige Repetitionspaare (HE-R64). Helligkeit ohne Wärme: keine Terz, kein Grundton im Bass ab Takt 5.
- **Dynamik:** ppp–pp. · **Pausen:** Mehr Stille als Ton; Tupfer nur in Takt 2 und 7.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme; der Tupfer trägt die Zelle.
- **Variation:** Zweiten Block weglassen; Glockenruf mit Halbton statt Tritonus (HE-P19). · **Fortsetzung:** HE-S09 oder HE-S36.
- **Bezug:** HE-H97, HE-H101, HE-M53, HE-R64, HE-P19
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 1 3 0 1 1 2 0; keine Melodierolle; MIDI `HE-S35.mid`, 26 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Lange Noten in Kurzrolle, Exakte Registervorgabe, Mehrere harmonische Komponenten, Notierte Linie in Begleitrolle

### HE-S36 · Helle, surreale Unruhe

- **Charakter:** Ein Traum, in dem die Treppe nach oben immer wieder unten ankommt.
- **XYZ-Anker:** 0,65 / 0,30 / 0,75 (HRU) · **Länge:** 8 Takte · **Taktart:** 4/4T · **Tempo:** ♩ = 66–80 (MIDI-Beispiel ♩ = 72) · **Harmonik:** HE-H50 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `C9#5` | `C9#5` | `Db9#5` | `Db9#5` | `C9#5` | `C9#5` | `Db9#5` | `Db9#5`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x-----------\|------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 74, 3 Stimmen | 1–8 | 28 |
| AR Arpeggio | `x.xx.xx.x...\|..x.xx.xx.x.  (wiederholt)` | Akkordtöne (4) ab MIDI 72 über 2 Oktaven, auf und ab | 1–8 | 40 |
| TU Tupfer | — | notiert (siehe unten) | 1–8 | 34 |

- **Nicht beteiligt:** Kurze Fläche, Langer Bass, Kurzer Bass, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ○ ● ○ ● ○ ● ○
AR   ● ● ● ● ● ● ● ●
TU   · · ● · · · ● ·
```

- **Zusammenhang der Rollen:** Zwei Ganztonfelder im Halbtonabstand wechseln alle zwei Takte; die Triolen des Arpeggios sind unregelmäßig gefüllt, ihre Lücken wandern. Kein Bass. Die Spirale des Tupfers erscheint nur auf der zweiten Ganztonreihe und bricht beim zweiten Mal ab.
- **Dynamik:** pp, Fläche kaum hörbar. · **Pausen:** Tupfer nur in Takt 3 und 7.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** Arpeggio eine Oktave höher (reg 84). · **Fortsetzung:** HE-S40 (16 Takte) oder HE-S10.
- **Bezug:** HE-H50, HE-R65, HE-M54, HE-P20
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 1 3 1 2 1 3 1; keine Melodierolle; MIDI `HE-S36.mid`, 77 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Notierte Linie in Begleitrolle

### HE-S37 · Kraftvoll und ruhig: dunkle Polychord-Säulen

- **Charakter:** Ein Damm, hinter dem das Wasser steht.
- **XYZ-Anker:** 0,15 / 0,80 / 0,25 (DIS) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 44–56 (MIDI-Beispiel ♩ = 50) · **Harmonik:** HE-H59 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `Bm|Fm` | `Bm|Fm` | `Bm|Fm` | `Bm|Fm` | `Bm|Fm` | `Bm|Fm` | `Bm|Fm` | `Bm|Fm`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------\|----------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 53, 3 Stimmen | 1–8 | 92 |
| KF Kurze Fläche | `x---------------\|----------------  (wiederholt)` | Akkordtöne eng ab MIDI 59, 3 Stimmen | 1–8 | 92 |
| LB Langer Bass | `x---------------\|----------------  (wiederholt)` | fest: Eb1 A1 | 1–8 | 90 |

- **Nicht beteiligt:** Kurzer Bass, Arpeggio, Tupfer, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ○ ● ○ ● ○ ● ○
KF   ● ○ ● ○ ● ○ ● ○
LB   ● ○ ● ○ ● ○ ● ○
```

- **Zusammenhang der Rollen:** Drei Schichten: tiefe Tritonusdyade E♭–A, darüber F-Moll und H-Moll, beide gleichzeitig angeschlagen und zwei Takte gehalten. Keine Bewegung, keine Akzentverschiebung: höchste Intensität bei niedriger Unruhe, nur durch Masse und Verschmelzung.
- **Dynamik:** ff gleichmäßig. · **Pausen:** keine.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** Obere Mollschicht erst ab Takt 3 (Säule wächst). · **Fortsetzung:** HE-S14 oder HE-S23 (Stufe 4).
- **Bezug:** HE-H59, HE-R41, HE-R66
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 0 3 0 3 0 3 0; keine Melodierolle; MIDI `HE-S37.mid`, 32 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Mehrstimmiger Bass, Lange Noten in Kurzrolle, Exakte Registervorgabe, Mehrere harmonische Komponenten

### HE-S38 · Helle Bedrohung ohne Heldenton

- **Charakter:** Ein Suchscheinwerfer erfasst den Flüchtenden auf dem Gefängnishof.
- **XYZ-Anker:** 0,70 / 0,80 / 0,70 (HIU) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 88–104 (MIDI-Beispiel ♩ = 96) · **Harmonik:** HE-H99 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `Db|C` | `Db|C` | `Db|C` | `Db|C` | `Db|C` | `Db|C` | `Db|C` | `Db|C`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `X..x..X...x..X..  (wiederholt)` | Akkordtöne eng ab MIDI 72, 6 Stimmen | 1–8 | 86 |
| KB Kurzer Bass | `x.......x.......  (wiederholt)` | Bass-Töne `P(F#1)` ab MIDI 36 | 1–8 | 80 |
| ST Stich | `................\|................\|................\|................\|X...............\|................\|................\|................` | fester Trigger C2 (nie transponiert) | 1–8 | 100 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 78 |

- **Nicht beteiligt:** Lange Fläche, Langer Bass, Arpeggio, Tupfer, Hauptmelodie
- **Gegenstimme:** `r/16 | r/16 | G5/4 C6/4 F#6/8 | F6/16 | r/16 | r/16 | G5/4 C6/4 F#6/8 | F#6/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
KF   ● ● ● ● ● ● ● ●
KB   ● ● ● ● ● ● ● ●
ST   · · · · ● · · ·
GS   · · ● ● · · ● ●
```

- **Zusammenhang der Rollen:** C-Dur und D♭-Dur verschmolzen in hoher Lage, in unregelmäßigen Schlägen; darunter Tritonuspedal F♯. Die Gegenstimme bringt die helle Drohzelle HE-M55 (Quarte, Tritonus, Halbton). Weder Dur-Terz im Melodiezielton noch Leitton noch Kadenz: hell und kraftvoll, aber nicht heroisch. Ein Stich in Takt 5.
- **Dynamik:** f, Schläge ff. · **Pausen:** Gegenstimme in Takt 1–2 und 5–6 still.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Gegenstimme tragen Schläge und Tritonusbass die Bedrohung vollständig.
- **Variation:** Gegenstimme weglassen; Schläge nur auf 1 und 3. · **Fortsetzung:** HE-S13 oder HE-T13 (Entkopplung).
- **Bezug:** HE-H99, HE-M55, HE-B44, HE-P21
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 2 3 3 3 2 3 3; Melodietöne auf Zählzeiten als Akkordton: GS 5/8; MIDI `HE-S38.mid`, 265 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 5/3/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### HE-S39 · Hell, kraftvoll, stabil: kalte Erhabenheit

- **Charakter:** Ein riesiges Eisfeld unter Polarlicht.
- **XYZ-Anker:** 0,65 / 0,75 / 0,30 (HIS) · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo:** ♩ = 46–58 (MIDI-Beispiel ♩ = 52) · **Harmonik:** HE-H100 · **Tonvorrat:** Chromatisch
- **Akkorde je Takt:** `CaugM7` | `CaugM7` | `CaugM7` | `CaugM7` | `DbaugM7` | `DbaugM7` | `DbaugM7` | `DbaugM7`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------\|----------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 60, 4 Stimmen | 1–8 | 86 |
| LB Langer Bass | `x---------------\|----------------  (wiederholt)` | Bass-Töne `R` ab MIDI 24 | 1–8 | 86 |
| AR Arpeggio | `x...x...x...x...  (wiederholt)` | Akkordtöne (4) ab MIDI 72 über 2 Oktaven, aufwärts zyklisch | 1–8 | 56 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 74 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Tupfer, Stich, Hauptmelodie
- **Gegenstimme:** `C5/8 E5/8 | G#5/16 | r/16 | r/16 | Db5/8 F5/8 | A5/16 | r/16 | r/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ○ ● ○ ● ○ ● ○
LB   ● ○ ● ○ ● ○ ● ○
AR   ● ● ● ● ● ● ● ●
GS   ● ● · · ● ● · ·
```

- **Zusammenhang der Rollen:** Zwei übermäßige Säulen mit großer Septime in weiter, hoher Lage über Oktavbass, langsam und laut; das Arpeggio geht ruhig in Vierteln. Die Gegenstimme steigt in großen Terzen (HE-M56). Die Größe kommt aus Lage und Masse; es gibt keine Dur-Kadenz, deshalb keine Freude.
- **Dynamik:** f gleichmäßig; Gegenstimme mf. · **Pausen:** Gegenstimme schweigt in Takt 3–4 und 7–8.
- **Ohne Hauptmelodie/Gegenstimme:** Ohne Gegenstimme bleibt eine vollständige, erhabene Fläche.
- **Variation:** Zweite Säule weglassen (acht Takte CaugM7). · **Fortsetzung:** HE-S12 oder HE-S38.
- **Bezug:** HE-H100, HE-M56, HE-R66
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 4 2 3 1 4 2 3 1; Melodietöne auf Zählzeiten als Akkordton: GS 6/6; MIDI `HE-S39.mid`, 58 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 6/0/0
- **Haltetöne über Akkordwechsel:** keine Konflikte

### HE-S40 · Surreale Unruhe bei stehender Position (16 Takte)

- **Charakter:** Ein Karussell, das sich nachts von selbst dreht.
- **XYZ-Anker:** 0,60 / 0,25 / 0,70 (mRU) · **Länge:** 16 Takte · **Taktart:** 4/4T · **Tempo:** ♩ = 63–76 (MIDI-Beispiel ♩ = 69) · **Harmonik:** HE-H48 · **Tonvorrat:** Ganzton-0
- **Akkorde je Takt:** `Caug` | `Caug` | `Daug` | `Daug` (×4)

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x-----------\|------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 76, 3 Stimmen | 1–16 | 28 |
| AR Arpeggio | `xxxxxxxxxxxx\|xxxxxxxxxxxx\|xxxxxxxxxxxx\|xxxxxxxxxxxx\|............\|............\|............\|............\|xxxxxxxxxxxx\|xxxxxxxxxxxx\|xxxxxxxxxxxx\|xxxxxxxxxxxx\|............\|............\|............\|............` | Akkordtöne (4) ab MIDI 64 über 2 Oktaven, auf und ab (Register je Takt: 64 64 64 64 64 64 64 64 76 76 76 76 76 76 76 76) | 1–16 | 40 |
| TU Tupfer | `............\|............\|............\|............\|xxxxxxxxxxxx\|xxxxxxxxxxxx\|xxxxxxxxxxxx\|xxxxxxxxxxxx\|............\|............\|............\|............\|xxxxxxxxxxxx\|xxxxxxxxxxxx\|xxxxxxxxxxxx\|xxxxxxxxxxxx` | Akkordtöne (4) ab MIDI 76 über 2 Oktaven, aufwärts zyklisch (Register je Takt: 76 76 76 76 76 76 76 76 64 64 64 64 64 64 64 64) | 1–16 | 40 |

- **Nicht beteiligt:** Kurze Fläche, Langer Bass, Kurzer Bass, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
LF   ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○ ● ○
AR   ● ● ● ● · · · · ● ● ● ● · · · ·
TU   · · · · ● ● ● ● · · · · ● ● ● ●
```

- **Zusammenhang der Rollen:** Über 16 Takte bleiben Klangmaterial, Dichte (eine Brechung zu zwölf Triolen je Takt) und Velocity gleich. Entwickelt werden nur Rolle, Richtung und Register: Takt 1–4 Arpeggio aufwärts zuerst in der Mittellage, 5–8 Tupfer abwärts zuerst eine Oktave höher, 9–12 Arpeggio in der hohen Lage, 13–16 Tupfer in der Mittellage. Die XYZ-Position bleibt stehen; nichts eskaliert, nichts beruhigt sich.
- **Dynamik:** pp konstant. · **Pausen:** keine – die Unruhe liegt in der Kreisbewegung.
- **Ohne Hauptmelodie/Gegenstimme:** Hat weder Hauptmelodie noch Gegenstimme.
- **Variation:** Stationen in anderer Reihenfolge; Daug durch Dbaug ersetzen (schärfer, aber dann Position Z höher). · **Fortsetzung:** beliebig weiter mit neuer Station oder HE-S36.
- **Bezug:** HE-H48, HE-R13, HE-T06, HE-T07
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 1 2 1 2 1 2 1 2 1 2 1 2 1 2 1; keine Melodierolle; MIDI `HE-S40.mid`, 216 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Exakte Registervorgabe, Rollenwanderung

## I Transformationsverfahren (HE-T01–T13)

Jedes Verfahren ist eine achttaktige Studie mit MIDI-Datei. Die Spalte „Generatorregel“ formuliert das Verfahren so, dass es auf jede Vorlage anwendbar ist. Kein Verfahren ist Pflicht und keines ist an eine Zeitspanne gebunden.

| ID | Verfahren | Kernregel |
|---|---|---|
| HE-T01 | Kürzung | Kürzen heißt: Module streichen oder ihr Ende abschneiden, nie das Tempo ändern. |
| HE-T02 | Fragmentierung | Beim Fragmentieren bleiben Intervallrichtung und Rhythmus des Kopfs erhalten; Bruchstücke dürfen die Rolle und das Register wechseln. |
| HE-T03 | Wiederholung mit Variation | Bei stehender XYZ-Position je Durchgang höchstens einen Parameter variieren; Spannung weder abbauen noch steigern. |
| HE-T04 | Chromatische Verschiebung | Eine Verschiebung ganzer Strukturen um einen Halbton gilt als Variation, nicht als Szenenwechsel; Rückkehr ist jederzeit möglich (Pendel). |
| HE-T05 | Rhythmische Transformation | Bei rhythmischer Transformation Tonhöhenfolge beibehalten; bei Tonhöhenänderung den Rhythmus beibehalten. |
| HE-T06 | Registerverschiebung | Register ist ein eigener Regler; X (Färbung) darf durch Lage verändert werden, ohne Akkordqualität zu tauschen. |
| HE-T07 | Rollenwechsel | Rollenwechsel ohne Überlappung; die Zelle behält Kontur und Rhythmus, die neue Rolle bestimmt Lage und Artikulation. |
| HE-T08 | Synchronisierung und Entkopplung | Verschmelzungsgrad als stufenloser Parameter: Versatz (Schritte), Lagenabstand (Halbtöne), Artikulationslänge. |
| HE-T09 | Verdichtung / Ausdünnung | Dichte ist der letzte Steigerungshebel; Ausdünnung bedeutet nicht Entspannung, solange Klang und Pedal bleiben. |
| HE-T10 | Langfristige Eskalation | Reihenfolge der Steigerungshebel nach Belegdichte: Verschmelzung, Register, Dissonanzschärfe, Dynamik, Dichte. |
| HE-T11 | Unterbrechung | Unterbrechung = Interpunktionsmodul + optionale Leere; der Fluss kehrt identisch zurück, Variation erst danach. |
| HE-T12 | Wiederaufnahme nach einer Pause | Nach einer Pause dasselbe Modul wieder aufnehmen und genau einen Parameter ändern (hier Bass); keine neue Textur. |
| HE-T13 | Entkopplung (verschmolzen → getrennt) | Nach einem Höhepunkt nicht das Material tauschen, sondern den Verschmelzungsgrad senken. |

### HE-T01 · Kürzung

- **Verfahren:** Kürzung · **XYZ:** 0,25 / 0,40 / 0,55 → 0,25 / 0,30 / 0,60 · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo (MIDI):** ♩ = 96
- **Akkorde je Takt:** `Cm` | `Cm` | `Cm` | `CmM7` | `Cm` | `Cm` | `CmM7` | `CmM7`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `................\|................\|................\|X..X..X...X..X..\|................\|................\|X..X..X.........\|X...............` | Akkordtöne eng ab MIDI 57, 4 Stimmen | 1–8 | 64 |
| LB Langer Bass | `x---------------\|----------------  (wiederholt)` | fest: C2 | 1–8 | 42 |
| AR Arpeggio | `x.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.\|................\|x.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.\|................\|................` | Akkordtöne (4) ab MIDI 60 über 2 Oktaven, auf und ab | 1–8 | 46 |

- **Nicht beteiligt:** Lange Fläche, Kurzer Bass, Tupfer, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
KF   · · · ● · · ● ●
LB   ● ○ ● ○ ● ○ ● ○
AR   ● ● ● · ● ● · ·
```

| bleibt | ändert sich | Gelenk |
|---|---|---|
| Pedal C, Klangmaterial, Bewegungsmodul (Arpeggio) und Interpunktionsmodul (synkopierte Schläge). | Das Bewegungsmodul wird von drei auf zwei Takte gekürzt, die Interpunktion von fünf auf drei und schließlich auf einen Schlag. | Die Interpunktion kommt in der zweiten Hälfte früher; das Gefühl von Enge entsteht ohne neues Material. |

- **Generatorregel:** Kürzen heißt: Module streichen oder ihr Ende abschneiden, nie das Tempo ändern. Die Reihenfolge Bewegung → Interpunktion bleibt erhalten.
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 1 2 1 2 1 2 1; keine Melodierolle; MIDI `HE-T01.mid`, 80 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Pedal über Akkordwechsel

### HE-T02 · Fragmentierung

- **Verfahren:** Fragmentierung · **XYZ:** 0,25 / 0,30 / 0,45 → 0,25 / 0,20 / 0,55 · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo (MIDI):** ♩ = 66
- **Akkorde je Takt:** `Cm` | `Cm` | `Cm` | `Cm` | `Cm` | `Cm` | `Cm` | `Cm`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------\|----------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 48, 3 Stimmen | 1–8 | 38 |
| LB Langer Bass | `x---------------\|----------------  (wiederholt)` | fest: C2 | 1–8 | 38 |
| TU Tupfer | — | notiert (siehe unten) | 1–8 | 36 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 50 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Arpeggio, Stich, Hauptmelodie
- **Gegenstimme:** `Ab4/2 G4/2 F4/2 Eb4/2 r/8 | Ab4/2 G4/2 F4/2 Eb4/2 r/8 | Ab4/2 G4/2 F4/4 r/8 | r/16 | Ab4/2 G4/2 r/12 | r/16 | r/8 Ab4/6 G4/2 | r/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ○ ● ○ ● ○ ● ○
LB   ● ○ ● ○ ● ○ ● ○
TU   · · · ● · ● · ●
GS   ● ● ● · ● · ● ·
```

| bleibt | ändert sich | Gelenk |
|---|---|---|
| Fläche, Pedal, Zellenkopf A♭–G. | Die Viertonzelle zerfällt in Bruchstücke; Teile wandern in den Tupfer, eine Oktave höher und an unregelmäßige Stellen. | Der Kopf A♭–G bleibt in jeder Station erkennbar. |

- **Generatorregel:** Beim Fragmentieren bleiben Intervallrichtung und Rhythmus des Kopfs erhalten; Bruchstücke dürfen die Rolle und das Register wechseln.
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 1 3 1 3 1 3 1; Melodietöne auf Zählzeiten als Akkordton: GS 0/8; MIDI `HE-T02.mid`, 36 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 7/0/8
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Rollenwanderung, Notierte Linie in Begleitrolle

### HE-T03 · Wiederholung mit Variation

- **Verfahren:** Wiederholung mit Variation · **XYZ:** 0,30 / 0,20 / 0,60 → 0,30 / 0,25 / 0,65 · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo (MIDI):** ♩ = 72
- **Akkorde je Takt:** `C7` | `C7` | `F#7b5` | `F#7b5` | `C7` | `C7` | `Eaug` | `Eaug`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `x.x---x.x...x.x.\|x.x---x.x...x.x.\|x.x---x.x...x.x.\|x.x---x.x...x.x.\|x.x---x.x...x.x.\|x.x---x.x...x.x.\|x.x-x.x.x...x.x.\|x.x-x.x.x...x.x.` | Akkordtöne eng ab MIDI 58, 3 Stimmen (Register je Takt: 58 58 58 58 66 66 66 66) | 1–8 | 44 |
| LB Langer Bass | `x---------------\|----------------  (wiederholt)` | fest: E2 | 1–8 | 36 |
| TU Tupfer | `................\|................\|................\|................\|................\|................\|x.......x.......\|x.......x.......` | fest: E5 | 1–8 | 30 |

- **Nicht beteiligt:** Lange Fläche, Kurzer Bass, Arpeggio, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
KF   ● ● ● ● ● ● ● ●
LB   ● ○ ● ○ ● ○ ● ○
TU   · · · · · · ● ●
```

| bleibt | ändert sich | Gelenk |
|---|---|---|
| Rhythmus der Kurzen Fläche, Binnenpedal E. | Takt 5–6: Lage der Fläche eine Sexte höher; Takt 7–8: neuer Pendelklang (Eaug), eine Viertel des Rhythmus geteilt, Tupfer-Repetition kommt dazu. | Jeder Zweitakter variiert genau einen Parameter (Lage, Klang, Rhythmusdetail, Rolle). |

- **Generatorregel:** Bei stehender XYZ-Position je Durchgang höchstens einen Parameter variieren; Spannung weder abbauen noch steigern.
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 1 2 1 2 1 3 2; keine Melodierolle; MIDI `HE-T03.mid`, 158 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Exakte Registervorgabe

### HE-T04 · Chromatische Verschiebung

- **Verfahren:** Chromatische Verschiebung · **XYZ:** 0,20 / 0,40 / 0,55 → 0,20 / 0,45 / 0,65 · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo (MIDI):** ♩ = 88
- **Akkorde je Takt:** `Cm` | `Cm` | `Cm` | `Cm` | `C#m` | `C#m` | `C#m` | `C#m`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------\|----------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 48, 3 Stimmen | 1–8 | 42 |
| KF Kurze Fläche | `x...x.x.x...x.x.  (wiederholt)` | Akkordtöne eng ab MIDI 57, 3 Stimmen | 1–8 | 55 |
| KB Kurzer Bass | `x.......x.......  (wiederholt)` | Bass-Töne `R` ab MIDI 36 | 1–8 | 52 |

- **Nicht beteiligt:** Langer Bass, Arpeggio, Tupfer, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ○ ● ○ ● ○ ● ○
KF   ● ● ● ● ● ● ● ●
KB   ● ● ● ● ● ● ● ●
```

| bleibt | ändert sich | Gelenk |
|---|---|---|
| Alle Rollen, Rhythmen und Lagen. | Die gesamte Textur rückt in Takt 5 einen Halbton höher. | Kein gemeinsamer Ton: der Ruck ist das Ereignis; Rhythmus und Register sichern die Kontinuität. |

- **Generatorregel:** Eine Verschiebung ganzer Strukturen um einen Halbton gilt als Variation, nicht als Szenenwechsel; Rückkehr ist jederzeit möglich (Pendel).
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 2 3 2 3 2 3 2; keine Melodierolle; MIDI `HE-T04.mid`, 172 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte

### HE-T05 · Rhythmische Transformation

- **Verfahren:** Rhythmische Transformation · **XYZ:** 0,25 / 0,30 / 0,45 → 0,25 / 0,45 / 0,65 · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo (MIDI):** ♩ = 80
- **Akkorde je Takt:** `Cm` | `Cm` | `Cm` | `Cm` | `Cm` | `Cm` | `Cm` | `Cm`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------\|----------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 48, 3 Stimmen | 1–8 | 40 |
| LB Langer Bass | `x---------------\|----------------  (wiederholt)` | fest: C2 | 1–8 | 40 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 52 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Arpeggio, Tupfer, Stich, Hauptmelodie
- **Gegenstimme:** `Ab4/4 G4/4 F4/4 Eb4/4 | r/16 | Ab4/3 G4/1 F4/3 Eb4/1 r/8 | r/16 | Ab4/1 G4/1 F4/1 Eb4/1 r/12 | Ab4/1 G4/1 F4/1 Eb4/1 r/4 Ab4/1 G4/1 F4/1 Eb4/1 r/4 | Ab4/8 G4/8 | F4/8 Eb4/8`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ○ ● ○ ● ○ ● ○
LB   ● ○ ● ○ ● ○ ● ○
GS   ● · ● · ● ● ● ●
```

| bleibt | ändert sich | Gelenk |
|---|---|---|
| Tonfolge A♭–G–F–E♭, Fläche, Pedal. | Gleichmäßig → punktiert → Diminution → gehäufte Diminution → Augmentation. | Tonhöhen bleiben, nur der Rhythmus ändert sich; deshalb bleibt die Zelle erkennbar. |

- **Generatorregel:** Bei rhythmischer Transformation Tonhöhenfolge beibehalten; bei Tonhöhenänderung den Rhythmus beibehalten.
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 0 3 0 3 1 3 1; Melodietöne auf Zählzeiten als Akkordton: GS 4/13; MIDI `HE-T05.mid`, 40 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 12/0/12
- **Haltetöne über Akkordwechsel:** keine Konflikte

### HE-T06 · Registerverschiebung

- **Verfahren:** Registerverschiebung · **XYZ:** 0,40 / 0,25 / 0,55 → 0,10 / 0,35 / 0,50 · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo (MIDI):** ♩ = 66
- **Akkorde je Takt:** `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LB Langer Bass | `................\|................\|................\|................\|................\|................\|x---------------\|----------------` | fest: C1 | 1–8 | 44 |
| AR Arpeggio | `x.x.x.x.x.x.x.x.  (wiederholt)` | Akkordtöne (4) ab MIDI 84 über 2 Oktaven, auf und ab (Register je Takt: 84 84 72 72 60 60 48 48) | 1–8 | 44 |

- **Nicht beteiligt:** Lange Fläche, Kurze Fläche, Kurzer Bass, Tupfer, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LB   · · · · · · ● ○
AR   ● ● ● ● ● ● ● ●
```

| bleibt | ändert sich | Gelenk |
|---|---|---|
| Klang, Rhythmus, Velocity, Notenzahl. | Das Arpeggio sinkt alle zwei Takte eine Oktave (C6 → C3); erst in Takt 7 kommt der tiefe Boden. | Gleiche Figur in neuer Lage – kalt und gläsern wird dumpf und schwer. |

- **Generatorregel:** Register ist ein eigener Regler; X (Färbung) darf durch Lage verändert werden, ohne Akkordqualität zu tauschen.
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 1 1 1 1 1 1 2 1; keine Melodierolle; MIDI `HE-T06.mid`, 65 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Exakte Registervorgabe

### HE-T07 · Rollenwechsel

- **Verfahren:** Rollenwechsel · **XYZ:** 0,25 / 0,30 / 0,50 → 0,15 / 0,30 / 0,50 · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo (MIDI):** ♩ = 72
- **Akkorde je Takt:** `Cm` | `Cm` | `Cm` | `Cm` | `Cm` | `Cm` | `Cm` | `Cm`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------\|----------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 48, 3 Stimmen | 1–8 | 38 |
| KB Kurzer Bass | — | notiert (siehe unten) | 1–8 | 55 |
| TU Tupfer | — | notiert (siehe unten) | 1–8 | 40 |
| GS Gegenstimme | — | notiert (siehe unten) | 1–8 | 50 |

- **Nicht beteiligt:** Kurze Fläche, Langer Bass, Arpeggio, Stich, Hauptmelodie
- **Gegenstimme:** `Ab4/2 G4/2 F4/2 Eb4/2 r/8 | Ab4/2 G4/2 F4/2 Eb4/2 r/8 | r/16 | r/16 | r/16 | r/16 | r/16 | r/16`

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ○ ● ○ ● ○ ● ○
KB   · · · · ● ● ● ●
TU   · · ● ● · · · ·
GS   ● ● · · · · · ·
```

| bleibt | ändert sich | Gelenk |
|---|---|---|
| Zelle und Rhythmus. | Die Zelle wandert von der Gegenstimme in den Tupfer (höher, versetzt) und dann in den Kurzen Bass (tief, dreimal). | Lückenlose Übergabe: die neue Rolle setzt erst ein, wenn die alte geschwiegen hat. |

- **Generatorregel:** Rollenwechsel ohne Überlappung; die Zelle behält Kontur und Rhythmus, die neue Rolle bestimmt Lage und Artikulation.
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 1 2 1 2 1 2 1; Melodietöne auf Zählzeiten als Akkordton: GS 0/4; MIDI `HE-T07.mid`, 41 Noten.
- **Tonklassen der Melodierollen** (Akkordton / Systemton / systemfremd): GS 4/0/4
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Lange Noten in Kurzrolle, Rollenwanderung, Notierte Linie in Begleitrolle

### HE-T08 · Synchronisierung: getrennt → verschmolzen

- **Verfahren:** Synchronisierung und Entkopplung · **XYZ:** 0,15 / 0,25 / 0,65 → 0,15 / 0,70 / 0,70 · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo (MIDI):** ♩ = 58
- **Akkorde je Takt:** `F#m|Cm` | `F#m|Cm` | `F#m|Cm` | `F#m|Cm` | `F#m|Cm` | `F#m|Cm` | `F#m|Cm` | `F#m|Cm`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 48, 3 Stimmen (Register je Takt: 48 48 54 54 60 60 60 60) | 1–8 | 45 |
| KF Kurze Fläche | `.........x------\|...........x----\|......x---------\|....x-----------\|..x-------......\|..x-------......\|x-------........\|x-------........` | Akkordtöne eng ab MIDI 78, 3 Stimmen (Register je Takt: 78 78 72 72 66 66 64 64) | 1–8 | 45 |

- **Nicht beteiligt:** Langer Bass, Kurzer Bass, Arpeggio, Tupfer, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ● ● ● ● ● ● ●
KF   ● ● ● ● ● ● ● ●
```

| bleibt | ändert sich | Gelenk |
|---|---|---|
| Sechs Tonklassen (C-Moll + F♯-Moll), Velocity, Notenzahl je Takt. | Die obere Schicht rückt zeitlich und registral an die untere heran, bis beide gleichzeitig und ineinander erklingen (Takt 7–8). | Die Bedrohung steigt durch Verschmelzung, nicht durch neues Material (Verbindung HE-S06 → HE-S07). |

- **Generatorregel:** Verschmelzungsgrad als stufenloser Parameter: Versatz (Schritte), Lagenabstand (Halbtöne), Artikulationslänge.
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 2 2 2 2 2 2 2; keine Melodierolle; MIDI `HE-T08.mid`, 48 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Lange Noten in Kurzrolle, Exakte Registervorgabe, Mehrere harmonische Komponenten

### HE-T09 · Verdichtung und Ausdünnung

- **Verfahren:** Verdichtung / Ausdünnung · **XYZ:** 0,25 / 0,35 / 0,55 → 0,25 / 0,35 / 0,50 · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo (MIDI):** ♩ = 84
- **Akkorde je Takt:** `Cm7b5` | `Cm7b5` | `Cm7b5` | `Cm7b5` | `Bm7b5` | `Bm7b5` | `Bm7b5` | `Bm7b5`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `X.......X.......\|X...x...X...x...\|X.x.x.x.X.x.x.x.\|XxxxxxxxXxxxxxxx\|x.x.x.x.x.x.x.x.\|x...x...x...x...\|x.......x.......\|x...............` | Akkordtöne eng ab MIDI 60, 3 Stimmen | 1–8 | 46 |
| LB Langer Bass | `x---------------\|----------------  (wiederholt)` | fest: C2 | 1–8 | 40 |

- **Nicht beteiligt:** Lange Fläche, Kurzer Bass, Arpeggio, Tupfer, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
KF   ● ● ● ● ● ● ● ●
LB   ● ○ ● ○ ● ○ ● ○
```

| bleibt | ändert sich | Gelenk |
|---|---|---|
| Schwerpunkte (1 und 3), Velocity, Klangfamilie. | Takt 1–4 füllen sich die Zwischenräume bis zu Sechzehnteln; Takt 5–8 dünnen sie auf eine Ganze aus. Der Klang sinkt dabei einen Halbton. | Die Schwerpunkte bleiben stehen; deshalb ist die Verdichtung Druck und nicht Hektik. |

- **Generatorregel:** Dichte ist der letzte Steigerungshebel; Ausdünnung bedeutet nicht Entspannung, solange Klang und Pedal bleiben.
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 1 2 1 2 1 2 1; keine Melodierolle; MIDI `HE-T09.mid`, 139 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte

### HE-T10 · Langfristige Eskalation in fünf Hebeln

- **Verfahren:** Langfristige Eskalation · **XYZ:** 0,15 / 0,25 / 0,55 → 0,20 / 0,90 / 0,80 · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo (MIDI):** ♩ = 84
- **Akkorde je Takt:** `Bm|Cm` | `Bm|Cm` | `Bm|Cm` | `Bm|Cm` | `Dbm|Cm` | `Dbm|Cm` | `Dbm|Cm` | `Dbm|Cm`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------  (wiederholt)` | Akkordtöne ohne Bass, eng ab MIDI 48, 3 Stimmen | 1–8 | 48 · Dynamik je Takt ×1,00 1,00 1,00 1,00 1,00 1,00 1,25 1,35 |
| KF Kurze Fläche | `......x---......\|x-------........\|x-------........\|x-------........\|x-------........\|x-------........\|x-------x-------\|X.x.X.x.X.x.X.x.` | Akkordtöne eng ab MIDI 83, 3 Stimmen (Register je Takt: 83 47 71 71 71 71 71 71) | 1–8 | 48 · Dynamik je Takt ×1,00 1,00 1,00 1,00 1,00 1,00 1,25 1,35 |
| ST Stich | `................\|................\|................\|................\|................\|................\|................\|X...............` | fester Trigger C2 (nie transponiert) | 1–8 | 100 |

- **Nicht beteiligt:** Langer Bass, Kurzer Bass, Arpeggio, Tupfer, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ● ● ● ● ● ● ●
KF   ● ● ● ● ● ● ● ●
ST   · · · · · · · ●
```

| bleibt | ändert sich | Gelenk |
|---|---|---|
| Untere Schicht C-Moll, Grundtempo. | Takt 2 Verschmelzung (obere Schicht ineinander, gleichzeitig); Takt 3 Register (obere Schicht zwei Oktaven höher, heller und wieder getrennt); Takt 5 Dissonanz (H-Moll → D♭-Moll); Takt 7 Dynamik; Takt 8 Dichte und Stich. | Jeder Hebel wird einzeln hinzugefügt und bleibt dann stehen. |

- **Generatorregel:** Reihenfolge der Steigerungshebel nach Belegdichte: Verschmelzung, Register, Dissonanzschärfe, Dynamik, Dichte. Für längere Strecken auf 16 oder 32 Takte dehnen (HE-S23).
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 2 2 2 2 2 2 3; keine Melodierolle; MIDI `HE-T10.mid`, 73 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Lange Noten in Kurzrolle, Exakte Registervorgabe, Mehrere harmonische Komponenten

### HE-T11 · Unterbrechung

- **Verfahren:** Unterbrechung · **XYZ:** 0,25 / 0,45 / 0,65 → 0,25 / 0,45 / 0,65 · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo (MIDI):** ♩ = 108
- **Akkorde je Takt:** `Cm` | `Cm` | `Cm` | `CmM7` | `Cm` | `Cm` | `C#m` | `C#m`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| KF Kurze Fläche | `................\|................\|................\|X..X..X...X..X..\|................\|................\|................\|................` | Akkordtöne eng ab MIDI 57, 4 Stimmen | 1–8 | 70 |
| LB Langer Bass | `x---------------\|----------------\|x---------------\|--------........\|................\|x---------------\|----------------\|----------------` | fest: C2 | 1–8 | 42 |
| AR Arpeggio | `x.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.\|................\|................\|x.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.\|x.x.x.x.x.x.x.x.` | Akkordtöne (4) ab MIDI 60 über 2 Oktaven, auf und ab | 1–8 | 46 |

- **Nicht beteiligt:** Lange Fläche, Kurzer Bass, Tupfer, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
KF   · · · ● · · · ·
LB   ● ○ ● ○ · ● ○ ○
AR   ● ● ● · · ● ● ●
```

| bleibt | ändert sich | Gelenk |
|---|---|---|
| Arpeggio-Fluss vor und nach der Unterbrechung (gleiche Figur). | Takt 4 Interpunktion, Takt 5 völlige Stille (auch das Pedal bricht ab), Takt 6 setzt der Fluss unverändert wieder ein und rückt in Takt 7 einen Halbton. | Die Stille gehört zur Interpunktion; nach ihr ist alles wie vorher – und gerade deshalb nicht. |

- **Generatorregel:** Unterbrechung = Interpunktionsmodul + optionale Leere; der Fluss kehrt identisch zurück, Variation erst danach.
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 2 1 2 1 0 2 1 1; keine Melodierolle; MIDI `HE-T11.mid`, 71 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Pedal über Akkordwechsel

### HE-T12 · Wiederaufnahme nach Pause

- **Verfahren:** Wiederaufnahme nach einer Pause · **XYZ:** 0,20 / 0,20 / 0,40 → 0,15 / 0,25 / 0,60 · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo (MIDI):** ♩ = 60
- **Akkorde je Takt:** `CmM7` | `CmM7` | `CmM7` | `CmM7` | `CmM7/Db` | `CmM7/Db` | `CmM7/Db` | `CmM7/Db`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `x---------------\|----------------\|................\|................\|x---------------\|----------------\|----------------\|----------------` | Akkordtöne ohne Bass, eng ab MIDI 51, 3 Stimmen | 1–8 | 40 |
| LB Langer Bass | `x---------------\|----------------\|................\|................\|x---------------\|----------------\|----------------\|----------------` | Bass-Töne `b` ab MIDI 25 | 1–8 | 40 |
| TU Tupfer | `......x.........\|................\|................\|................\|......x.........\|................\|..........x.....\|................` | oberster Akkordton ab MIDI 79, dann abwärts zyklisch | 1–8 | 34 |

- **Nicht beteiligt:** Kurze Fläche, Kurzer Bass, Arpeggio, Stich, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● ○ · · ● ○ ○ ○
LB   ● ○ · · ● ○ ○ ○
TU   ● · · · ● · ● ·
```

| bleibt | ändert sich | Gelenk |
|---|---|---|
| Klang, Lage, Tupferposition. | Nach zwei Takten Stille kommt alles zurück – nur der Bass steht einen Halbton höher (D♭ statt C). | Wiedererkennen durch Lage und Rhythmus; die eine Änderung im Bass wird dadurch umso deutlicher. |

- **Generatorregel:** Nach einer Pause dasselbe Modul wieder aufnehmen und genau einen Parameter ändern (hier Bass); keine neue Textur.
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 0 0 0 3 0 1 0; keine Melodierolle; MIDI `HE-T12.mid`, 11 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte

### HE-T13 · Entkopplung nach dem Schock

- **Verfahren:** Entkopplung (verschmolzen → getrennt) · **XYZ:** 0,10 / 0,85 / 0,85 → 0,15 / 0,30 / 0,60 · **Länge:** 8 Takte · **Taktart:** 4/4 · **Tempo (MIDI):** ♩ = 72
- **Akkorde je Takt:** `Dbm|Cm` | `Dbm|Cm` | `Bm|Cm` | `Bm|Cm` | `Bm|Cm` | `Bm|Cm` | `Bm|Cm` | `Bm|Cm`

| Rolle | Raster | Tonregel | aktiv in Takt | Grund-Velocity |
|---|---|---|---|---|
| LF Lange Fläche | `X-------........\|................\|x---------------\|----------------\|x---------------\|----------------\|x---------------\|----------------` | Akkordtöne ohne Bass, eng ab MIDI 60, 3 Stimmen | 1–8 | 48 · Dynamik je Takt ×1,60 1,00 1,00 1,00 1,00 1,00 1,00 1,00 |
| KF Kurze Fläche | `X-------........\|................\|....x---........\|................\|......x---......\|................\|........x-------\|................` | Akkordtöne eng ab MIDI 61, 3 Stimmen (Register je Takt: 61 61 59 59 71 71 83 83) | 1–8 | 48 · Dynamik je Takt ×1,60 1,00 1,00 1,00 1,00 1,00 1,00 1,00 |
| ST Stich | `X...............\|................\|................\|................\|................\|................\|................\|................` | fester Trigger C2 (nie transponiert) | 1–8 | 100 |

- **Nicht beteiligt:** Langer Bass, Kurzer Bass, Arpeggio, Tupfer, Gegenstimme, Hauptmelodie

Rollenverlauf (● Einsatz im Takt, ○ klingt weiter, · Pause):

```
     1 2 3 4 5 6 7 8
LF   ● · ● ○ ● ○ ● ○
KF   ● · ● · ● · ● ·
ST   ● · · · · · · ·
```

| bleibt | ändert sich | Gelenk |
|---|---|---|
| Untere Schicht C-Moll, Polychord-Typ (Moll über Moll im Halbtonverhältnis). | Nach dem verschmolzenen Schlag in kleinen Sekunden (D♭-Moll über C-Moll) steht derselbe Typ als große Septime (H-Moll über C-Moll) in immer weiterer Lage und immer späterem Einsatz. | Kein Materialwechsel; die Bedrohung bleibt im Raum, wird aber wieder rätselhaft. |

- **Generatorregel:** Nach einem Höhepunkt nicht das Material tauschen, sondern den Verschmelzungsgrad senken. Keine erzwungene Rückkehr: die Entkopplung ist eine Möglichkeit, keine Pflicht.
- **Prüfung:** gleichzeitig neu einsetzende Rollen je Takt 3 0 2 0 2 0 2 0; keine Melodierolle; MIDI `HE-T13.mid`, 25 Noten.
- **Haltetöne über Akkordwechsel:** keine Konflikte
- **Technische Anforderungen:** Lange Noten in Kurzrolle, Exakte Registervorgabe, Mehrere harmonische Komponenten

## J XYZ-Abdeckung

| Ecke | Beschreibung | H | R | B | M | P | S |
|---|---|---|---|---|---|---|---|
| DRS | dunkel, zurückhaltend, stabil | 15 | 12 | 5 | 18 | 4 | 7 |
| DRU | dunkel, zurückhaltend, unruhig | 40 | 34 | 26 | 25 | 14 | 14 |
| DIS | dunkel, kraftvoll, stabil | 6 | 4 | 5 | 1 | 0 | 2 |
| DIU | dunkel, kraftvoll, unruhig | 16 | 14 | 6 | 4 | 0 | 4 |
| HRS | hell, zurückhaltend, stabil | 7 | 0 | 1 | 5 | 1 | 3 |
| HRU | hell, zurückhaltend, unruhig | 8 | 2 | 1 | 2 | 1 | 5 |
| HIS | hell, kraftvoll, stabil | 6 | 0 | 0 | 1 | 0 | 2 |
| HIU | hell, kraftvoll, unruhig | 3 | 0 | 1 | 1 | 1 | 3 |

**Niedriges Y und niedriges Z** (Y < 0,40 und Z < 0,50): 72 Vorlagen und Studien, darunter HE-H01, HE-H04, HE-H09, HE-H10, HE-H17, HE-H19, HE-H30, HE-H43, HE-H45, HE-H46, HE-H64, HE-H76, HE-H77, HE-H81, HE-H85, HE-H87, HE-H88, HE-H96, HE-H97, HE-H101, HE-R02, HE-R16, HE-R35, HE-R36 usw.. In diesem Bereich liegt bei Herrmann der Bann (Pedal, Repetition, eingefrorener Klang), nicht die Ruhe.

**Rhythmische und harmonische Färbung sind getrennt.** Die Ecken der Rhythmus-, Bass- und Motivspalten geben den Anker an, für den eine Vorlage gesetzt wurde, nicht ihre Grenze. Maßgeblich für die Auswahl ist der **Färbungsbereich** jeder Vorlage:

| Bereich | färbungsunabhängig bzw. alle X | nur hell (X ≥ …) | nur dunkel (X ≤ …) |
|---|---|---|---|
| Rhythmus | 57 | 4 | 5 |
| Bass | 24 | 3 | 18 |
| Motive | 45 | 8 | 4 |
| Phrasen | 18 | 3 | 0 |

Für die hellen Bereiche gibt es außerdem eigens gebaute Vorlagen, die sich in Gestalt und Lage von den dunklen unterscheiden (keine Kopien): kalt-zurückhaltende Mystery HE-H97, HE-H101, HE-R64, HE-M53, HE-P19, HE-S35; hell-unruhig-surreal HE-R65, HE-B45, HE-M54, HE-M57, HE-P20, HE-S36, HE-S40; kraftvoll bei niedriger Unruhe HE-H99, HE-H100, HE-R66, HE-B43, HE-S37, HE-S39; helle, kraftvolle Bedrohung ohne Heldenton HE-H99, HE-B44, HE-M55, HE-P21, HE-S38.

Die Häufung bei dunkel/zurückhaltend/unruhig (DRU) ist gewollt: Herrmanns Spannung ist meist leise und latent. Die hellen Ecken sind mit eigenen Ableitungen besetzt, weil Helligkeit bei Herrmann vor allem als kalte, unheimliche oder entrückte Farbe belegt ist. Damit helle Vorlagen nicht heroisch oder fröhlich wirken, verzichten sie auf Leitton, Dur-Kadenz und Melodieziel auf schwerer Zeit (HE-M55, HE-S38, HE-S39).

## K Hinweise für den Generator

- **Wirkungsregler, nicht Quoten.** X wählt Akkordqualität und Lage (Dur, Mediante, hohe Lage → hell; mM7, Moll, tiefe Lage → dunkel). Y steuert zuerst den Verschmelzungsgrad und das Register, dann Dynamik, zuletzt Dichte. Z steuert Akzentverschiebung, Unterbrechung, ungleiche Zykluslängen, Pendeltempo und systemfremde Halbtöne.
- **Gemeinsame Töne als Gelenk.** Beim Wechsel zwischen Vorlagen zuerst eine Verbindung über gemeinsame Töne oder das Pedal suchen; der Ruck ohne gemeinsamen Ton (Halbton- oder Tritonuspendel) ist ein eigenes Ausdrucksmittel, kein Fehler.
- **Polychorde nur mit Komponentenplan.** Die Komponenten werden getrennten Rollen zugewiesen (Abschnitt C); der Verschmelzungsgrad ist ein Parameter, kein fester Zustand.
- **Stich.** Fester Trigger, ereignisgebunden; der Generator setzt ihn nur auf Anforderung oder beim Übergang in einen verschmolzenen Höhepunkt, nie im Raster.
- **Ohne Melodie vollständig.** Jede Studie ist ohne HM und GS lauffähig; die Spalte „Ohne Hauptmelodie/Gegenstimme“ sagt, was dann trägt.
- **Variation bei stehender Position.** Je Durchgang einen Parameter ändern (Rolle, Lage, Pendelklang, Tupferzelle, Rhythmusdetail); siehe HE-T03, HE-S25, HE-S26.
- **Auswahl nach Färbung.** Zuerst die harmonische Vorlage nach X (und Y, Z) wählen, dann Rhythmus-, Bass- und Motivvorlagen nach Y und Z; nach X nur filtern, wenn ihr Färbungsbereich eingeschränkt ist. Feste Bassöne (`P(x)`) gegen den gewählten Klang prüfen: sie sollen Akkordton, beabsichtigtes Pedal (Halbton, Tritonus) oder Vorhalt sein, nie zufällig reiben.
- **Dissonanz erhalten.** Töne der Klassen F und U in Motiven und Bassfiguren gehören zur Vorlage. Eine Harmoniekorrektur darf nur Töne ändern, die keine der fünf Tonfunktionen erfüllen.
- **Gastaktart.** Vorlagen in 3/4, 6/8, 5/4 und 4/4T sind Angebote; die Taktart des Projekts bleibt maßgeblich. Raster werden bei abweichender Taktart auf das Schrittraster des Hosts abgebildet, nicht der Host umgestellt.

## L Technische Rollenanforderungen

Die folgenden Fähigkeiten gehen über „eine Rolle spielt einen Klang im Raster“ hinaus. Sie sind nicht automatisch in STROMSCORE vorhanden; eine Vorlage, deren Anforderung fehlt, sollte vom Generator nicht oder nur in vereinfachter Form gewählt werden (Vereinfachung in der Spalte rechts). Es werden keine zusätzlichen MIDI-Ausgänge vorausgesetzt; alle Studien verwenden die neun bestehenden Rollen. Artikulation wird nie über Velocity vorgetäuscht: „kurz“ und „lang“ sind Notenlängen; ob kurz gezupft klingt, entscheidet das Instrument.

| Fähigkeit | Vorlagen und Studien | Vereinfachung, falls nicht vorhanden |
|---|---|---|
| Mehrstimmiger Bass | HE-H56, HE-H59, HE-H65, HE-H79, HE-H86, HE-H94, HE-H98, HE-H99, HE-H100, HE-B04, HE-B06, HE-B13, HE-B43, HE-S09, HE-S37 | nur den tiefsten Ton spielen |
| Mehrstimmiger Tupfer | — | nur den obersten Ton spielen |
| Lange Noten in Kurzrolle | HE-R41, HE-R51, HE-R52, HE-R66, HE-S02, HE-S07, HE-S09, HE-S15, HE-S21, HE-S22, HE-S26, HE-S27, HE-S32, HE-S35, HE-S37, HE-T07, HE-T08, HE-T10, HE-T13 | Teil in die Lange Fläche verlegen oder Note kürzen (Wirkung wird weniger massiv) |
| Pedal über Akkordwechsel | HE-H03, HE-H23, HE-H27, HE-H43, HE-H44, HE-H64, HE-H65, HE-H69, HE-H70, HE-B01, HE-B02, HE-B03, HE-B05, HE-B06, HE-B07, HE-B10, HE-B21, HE-B42, HE-B44, HE-S24, HE-T01, HE-T11 | Pedal bei jedem Akkordwechsel neu anschlagen (Bann geht teilweise verloren) |
| Exakte Registervorgabe | HE-H51, HE-H52, HE-H53, HE-H54, HE-H55, HE-H56, HE-H57, HE-H58, HE-H59, HE-H60, HE-H61, HE-H62, HE-H63, HE-H68, HE-H71, HE-H89, HE-H92, HE-H97, HE-H99, HE-H101, HE-B42, HE-B45, HE-M35, HE-P17, HE-S03, HE-S04, HE-S06, HE-S07, HE-S08, HE-S09, HE-S15, HE-S18, HE-S19, HE-S22, HE-S23, HE-S25, HE-S27, HE-S32, HE-S35, HE-S37, HE-S40, HE-T03, HE-T06, HE-T08, HE-T10, HE-T13 | Registerband der Rolle einhalten, Abstand der Schichten möglichst erhalten |
| Mehrere harmonische Komponenten | HE-H51, HE-H52, HE-H53, HE-H54, HE-H55, HE-H56, HE-H57, HE-H58, HE-H59, HE-H60, HE-H61, HE-H62, HE-H63, HE-H89, HE-H92, HE-H99, HE-S06, HE-S07, HE-S08, HE-S15, HE-S22, HE-S23, HE-S27, HE-S32, HE-S35, HE-S37, HE-T08, HE-T10, HE-T13 | nur eine Komponente spielen; dann Vorlage als Einzelklang behandeln |
| Rollenwanderung | HE-R53, HE-P09, HE-P17, HE-S04, HE-S25, HE-S40, HE-T02, HE-T07 | Muster in einer Rolle lassen und nur die Lage wechseln |
| Unabhängige rhythmische Zyklen | HE-R07, HE-R10, HE-R11, HE-R29, HE-R30, HE-R63, HE-B24, HE-B28, HE-M18 | Zyklus nach jedem Takt neu beginnen (Unruhe sinkt) |
| Kanon/koordinierte Parallelstimmen | HE-H35, HE-H61, HE-R13, HE-R43, HE-R44, HE-B39, HE-M29, HE-M41, HE-P16, HE-S10, HE-S21 | nur die erste Stimme spielen |
| Notierte Linie in Begleitrolle | HE-S21, HE-S26, HE-S29, HE-S35, HE-S36, HE-T02, HE-T07 | Linie der Gegenstimme übergeben |

Der Stich bleibt in allen Vorlagen ein seltener, fester, nicht transponierter Trigger (C2); er setzt keine Fähigkeit voraus.

## M Quellen

| Kürzel | Quelle | eingesehen | zitiert in |
|---|---|---|---|
| S1 | Daniel Moreira: „Weird, Menacing, and Colorful: Bernard Herrmann’s Harmonic Polytonality“, Music Theory Online 31/4 (2025) | Volltext (ohne Notenbeispiele) | 47 Vorlagen |
| S2 | Royal S. Brown: Interview mit Bernard Herrmann (1975), Wiederabdruck Bernard Herrmann Society | Volltext | 5 Vorlagen |
| S3 | Stephen Husarik: „Transformation of ‚The Psycho Theme‘ in Bernard Herrmann’s Music for Psycho“, Interdisciplinary Humanities (2009) | Volltext | 15 Vorlagen |
| S4 | Pearson Edexcel: A-Level-Leitfaden zu Psycho (Set Work, partiturbasiert, Taktangaben) | Volltext | 75 Vorlagen |
| S5 | Kenneth M. Smith: „Vertigo’s Musical Gaze: Neo-Riemannian Symmetries and Spirals“, Music Analysis 37/1 (2018) | Autorenmanuskript, Volltext | 42 Vorlagen |
| S6 | Scott Murphy: „Three Audiovisual Correspondences in the Main Title for Vertigo“, Music Theory Online 28/1 (2022) | Volltext, Teile 0–5 | 15 Vorlagen |
| S7 | Tom Schneller: „Easy to Cut: Modular Form in the Film Scores of Bernard Herrmann“, Journal of Film Music 5/1–2 (2012) | nur Suchsnippets (wörtlich, fragmentarisch) | 23 Vorlagen |
| S8 | Tom Schneller: „Unconscious Anchors“ (Marnie) und „Fearful Symmetries“ (Cape Fear) | nur über Snippets bzw. Moreira | 6 Vorlagen |
| S9 | David Cooper: Bernard Herrmann’s Vertigo. A Film Score Handbook | nur über Zitate bei Smith | 19 Vorlagen |
| S10 | Rebecca Leydon (2004) zu The Day the Earth Stood Still | nur über Moreira | 5 Vorlagen |
| S11 | Frank Lehman: Hollywood Harmony (2018) | nur Snippets | 4 Vorlagen |
| S12 | Bill Wrobel: Partitur-„Rundown“ zu Vertigo | informierte Amateurquelle, partiturbasiert | 10 Vorlagen |
| S13 | College Music Symposium: Artikel zu The Day the Earth Stood Still | Volltext | 3 Vorlagen |
| S14 | CBS Music Library Log Books (über Bernard Herrmann Society) | Einträge eingesehen | 4 Vorlagen |
| S15 | Herrmann, LP-Text zu Journey to the Center of the Earth (1974); Oxford-Kapitel „The Curtain Falls: Part 2“ (Abstract) | Zitat bzw. Abstract | 8 Vorlagen |
| S16 | IRCAM, Werkübersicht Bernard Herrmann | Volltext | 2 Vorlagen |
| S17 | Dänischer Fachartikel zu Vertigo (publimus.dk) | nur Snippet | 2 Vorlagen |
| S18 | LA Phil, Werkeinführung North by Northwest Overture | Volltext | 3 Vorlagen |
| S19 | Populäre Quellen: Intrada, Movie Music UK, Scribd-Notizen | niedrigere Qualität, als solche gekennzeichnet | 3 Vorlagen |

Genaue Belegstellen (Cue, Takt) stehen in `STROMSCORE_Bernard_Herrmann_Tiefenrecherche.md`. Für diese Fassung wurde keine weitere Literatur ausgewertet.
