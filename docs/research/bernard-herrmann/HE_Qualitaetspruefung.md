# STROMSCORE – Bernard Herrmann: Qualitätsprüfung der kanonischen Endfassung

Stand: 27.11.2026 · prüft `STROMSCORE_Bernard_Herrmann_Vokabular_Kanonisch.md`, `HE_Studien_Ereignisse.csv`, `HE_Studien_MIDI.zip`. Ersetzt den Prüfbericht vom selben Morgen. Keine erneute Tiefenrecherche; alle Verfahrensbelege stammen aus `STROMSCORE_Bernard_Herrmann_Tiefenrecherche.md`.

## 1 Bestand

| Bereich | Ziel | erste Fassung | Endfassung | neu |
|---|---|---|---|---|
| Harmonik | 80–100 | 98 | 101 | HE-H99, HE-H100, HE-H101 |
| Rhythmus | 60–80 | 63 | 66 | HE-R64, HE-R65, HE-R66 |
| Bass | 40–50 | 42 | 45 | HE-B43, HE-B44, HE-B45 |
| Motive | 50–60 | 52 | 57 | HE-M53, HE-M54, HE-M55, HE-M56, HE-M57 |
| Phrasen | 15–25 | 18 | 21 | HE-P19, HE-P20, HE-P21 |
| Modellstudien | 30–40 | 34 | 40 | HE-S35, HE-S36, HE-S37, HE-S38, HE-S39, HE-S40 |
| Transformationen | 12–16 | 13 | 13 | — |

Alle bisherigen IDs sind erhalten; neue IDs sind fortlaufend angehängt. Die Ergänzungen sind in die eine kanonische Datei integriert, es gibt keine getrennte Ergänzungsbibliothek. HE-H101 überschreitet die Zielspanne der Harmonik um eins; die drei neuen Harmonien füllen Lücken (helle Bedrohung, kraftvolle Ruhe, kalte Mystery) und sind keine Varianten vorhandener Vorlagen.

## 2 Korrekturen aus dem Prüfauftrag

| Stelle | Befund | Korrektur |
|---|---|---|
| HE-H03 | Text behauptete „kein gemeinsamer Ton“; CmM7 und D♭mM7 teilen C. | Text: C bleibt liegen und wird von Grundton zu großer Septime umgedeutet; Bassvariante entsprechend präzisiert. |
| HE-H48 | Text behauptete zwei verschiedene Ganztonreihen; C+ und D+ gehören beide zu Ganzton-0. | Text und Tonvorrat (jetzt Ganzton-0) korrigiert; die Variante mit D♭+ ist als Wechsel der Ganztonreihe gekennzeichnet. |
| HE-H50 | „Alle zwölf Töne“ falsch; die Fünfklänge ergeben zehn Tonklassen. | Text: zehn Tonklassen, es fehlen F♯ und G. |
| HE-M11, HE-P08 | D♭5 → C4 sind 13 Halbtöne (kleine None), nicht große Septime. | Tonfolge auf C4 → D♭3 geändert (11 Halbtöne abwärts = große Septime, Umkehrung des Halbtons C–D♭ aufwärts). |
| HE-R43 | Name „Achttaktabstand“, Raster zeigt vier Takte. | Name „Viertaktabstand“; Verweis in HE-M41 angepasst. |
| HE-B32, HE-B33 | Zwei Einsätze, vier Töne – zwei Töne erklangen nie. | Länge auf acht Takte, vier Einsätze im Zweitaktabstand passend zu HE-H98 bzw. HE-H08/H39. HE-B32 verweist nur noch auf HE-H98 (bei HE-H41 ist die Folge aufsteigend; Umkehrung angegeben). |
| Okt-A, Okt-B | Etiketten ohne Definition im Dokument. | Exakte Tonklassen in Abschnitt 0; Zuordnungen geprüft (nur HE-H19, H20, H25, alle Klangtöne liegen im Vorrat); ausdrücklich keine oktatonische Grammatik. |
| HE-H38 | Verweis auf HE-H54 (Moll über Moll im Halbton) passte nicht. | Verweis auf HE-H56 (getrennt) und HE-H57 (verschmolzen). |
| HE-H71 / HE-H73 | Behauptung „gleiche Töne“ falsch (F–F♯–G–A♭ gegenüber C–D♭–D). | Variante beschreibt jetzt den engen Cluster aus denselben vier Tönen; HE-H73 als anderer Cluster benannt. |
| HE-B08 | Verweis auf HE-M31 statt der chromatischen Gegenstimme. | Verweis auf HE-M32. |

## 3 Systematische Durchsicht: weitere gefundene und behobene Widersprüche

- **HE-R10 und HE-R57 (Hemiolen):** Das Raster `x..x..x..x..` in 6/8 bzw. 3/4 sind vier punktierte Achtel, also weder 6/8 noch 3/4. Neu: gleichmäßige Achtel mit Akzenten auf 1 und 4 (6/8) bzw. 1, 3 und 5 (3/4); HE-R57 heißt jetzt „Hemiolenwechsel 3/4 ↔ 6/8“. Dieselbe Korrektur in HE-S13 und HE-S33; in HE-S33 lesen Fläche und Bass jetzt nachweislich jeweils die andere Taktart (vorher widersprach der Text dem Raster).
- **HE-R19:** Die dritte Aussage beginnt auf Zählzeit 3, also zwei Schläge später, nicht einen.
- **HE-S02 und HE-S27 (Abschnitt 4):** Das Raster `x.......` erzeugte Sechzehntel statt der beschriebenen Halben. Jetzt `x-------........` (Halbe, dann Stille). Notenzahl und Velocity der Paare bleiben gleich.
- **HE-S15:** Die Kurze Fläche spielte in der Kaskade einen vierstimmigen Cluster statt des einen beschriebenen Tons G4. Jetzt eigene Komponente `{G}` für Takt 1–2.
- **HE-S10:** Text „eine Sexte höher“ – tatsächlich eine Oktave (MIDI 64 → 76). Text korrigiert.
- **HE-T10:** Text „eine Oktave höher“ – tatsächlich zwei Oktaven (MIDI 47 → 71). Text korrigiert.
- **HE-H53:** Variante „eine Oktave tiefer = HE-H54“ falsch (HE-H54 ist ein anderer Polychord). Jetzt: zwei Oktaven tiefer = Verschmelzung (HE-H60); kleine Sekunden = HE-H54.
- **HE-H85:** Verweis „E/C = Polarität wie HE-H58“ ungenau; jetzt: mit vollständigem C-Dur darunter wird daraus HE-H58.
- **HE-B39:** 13 Töne bei 11 Einsätzen; die letzten beiden Töne erklangen nie. Tonfolge auf die 11 Töne des Subjekts HE-M41 gekürzt.
- **HE-B42:** Pedal G3 rieb gegen den ersten Bezugsklang C+ (HE-H13) im Halbton, ohne dass das beabsichtigt war. Bezug jetzt HE-H10/H01; für übermäßige und Ganztonklänge G♯3 angegeben.
- **HE-M27, HE-M34, HE-M47:** Kontextklang so gesetzt, dass die Tonfunktion stimmt (die Dissonanz D♭ liegt jetzt über C-Moll, nicht im Kontextklang selbst).
- **Artikulation:** Formulierungen wie „gezupft“ in HE-R32, HE-R53, HE-B11, HE-B35, HE-S19, HE-S25 ersetzt durch Notenlängen; die Klangfarbe entscheidet das Instrument.
- **HE-S25:** In den Stationen ohne Kurze Fläche hält jetzt eine leise Lange Fläche den Klang, damit die Rollenwanderung nicht als Ausdünnung wirkt (siehe Abschnitt 6).

Automatisch geprüft und ohne weiteren Befund:

- gemeinsame Töne aller 173 Klangwechsel in HE-H gegen die Wirkungstexte mit Aussagen über gemeinsame Töne (13 Vorlagen) abgeglichen;
- Tonklassen-Summen aller Aussagen „acht/zehn/sechs Tonklassen“;
- 461 Melodieintervalle in Motiven und Phrasen gegen Namen und Konturangaben (Halbton, Septime, None, Tritonus, Quarte);
- Einsätze gegen Tonfolgen aller Bassvorlagen: alle Tonfolgen werden vollständig gespielt; einzige bewusste Abweichung HE-B24 (Dreierzyklus der Töne gegen 16 Einsätze = unabhängiger Zyklus, so gekennzeichnet);
- Polychorde: Intervall der Grundtöne gegen die Komponentenbeschreibung (15 + 3 neue);
- alle Verweise auf HE-IDs (existieren und passen inhaltlich; die Durchsicht ergab die oben genannten Fälle).

## 4 Technische Prüfungen (erneut durchgeführt)

| Prüfung | Ergebnis |
|---|---|
| IDs eindeutig | ja |
| Querverweise vorhanden | ja |
| Akkordsymbole lesbar, je Harmonievorlage 8 Takte | ja (101) |
| Akkordtöne im angegebenen Tonvorrat (außer „Chromatisch“) | ja |
| Raster: Schrittzahl und Taktzahl (R, B, Studien) | ja |
| Melodietokens: Taktsummen | ja |
| Tonhöhen 21–108 | ja (HE-S35 lag zunächst über 108; Lage korrigiert) |
| Haltetöne von LF/KF/AR/TU in fremde Akkorde | keine |
| MIDI-Dateien | 53, PPQ 960 |
| Noten CSV = Noten MIDI | 5328 = 5328, identisch: ja |
| Note-on/Note-off-Fehler | 0 |
| Überlagerung gleicher Tonhöhen in einer Spur | 0 (die Erzeugung kürzt oder entfernt sie; Zähler je Studie 0) |
| Stich: fester Trigger C2, höchstens einer je Abschnitt | ja |
| Prüfskript-Fehlerliste | leer |

## 5 Gleiches Material, andere Wirkung

| Studie / Abschnitt | Noten | Velocity-Werte | Tonklassen (einheitlich mit ♭ notiert) |
|---|---|---|---|
| HE-S01 (getrennt, lang) | 20 | 38 42 45 | C E♭ G B |
| HE-S02 (kurz, synchron) | 20 | 38 42 45 | C E♭ G B |
| HE-S06 (Schichten getrennt) | 24 | 45 | C D♭ E♭ F♯ G A |
| HE-S07 (verschmolzen) | 24 | 45 | C D♭ E♭ F♯ G A |
| HE-S27 Abschnitt 1 | 24 | 50 | C D E♭ F♯ G B |
| HE-S27 Abschnitt 2 | 24 | 50 | C D E♭ F♯ G B |
| HE-S27 Abschnitt 3 | 24 | 50 | C D E♭ F♯ G B |
| HE-S27 Abschnitt 4 | 24 | 50 | C D E♭ F♯ G B |
| HE-S22 Takt 1–4 | 26 | 46 | C D E♭ F♯ G B |
| HE-S22 Takt 5–8 | 26 | 46 | C D E♭ F♯ G B |
| HE-S22 Takt 9–12 | 26 | 46 | C D E♭ F♯ G B |
| HE-S22 Takt 13–16 | 26 | 46 | C D E♭ F♯ G B |

## 6 Langfristige Entwicklung

Einteilung der Studien über 16 und 32 Takte: **stehende Position** HE-S24, HE-S25, HE-S26, HE-S40 · **XYZ-Fahrt** HE-S21, HE-S22, HE-S23, HE-S27 (Vorführung). Kennzahlen je Abschnitt stehen im Vokabular (Abschnitt H). Geprüft: Bei stehender Position steigen oder fallen mittlere Velocity und Zahl klingender Töne nicht gerichtet über die Studie; Wechsel bleiben im Band und kehren zurück. Keine Studie enthält eine Zeitgrenze oder eine erzwungene Rückführung.

## 7 Dissonanz und harmonische Absicht in den Studien

Alle notierten Linien (Gegenstimme, Hauptmelodie und Linien in Tupfer oder Kurzem Bass) nach den fünf Tonfunktionen, gegen den Klang am Notenbeginn (mit Pedalton) und den Tonvorrat der Studie:

| Studie | Rolle | A | T | V | F | U | Absicht |
|---|---|---|---|---|---|---|---|
| HE-S05 | GS | 3 | 0 | 1 | 1 | 0 | chromatische Linie gegen steigenden Bass |
| HE-S11 | GS | 17 | 0 | 1 | 0 | 0 | überwiegend Klangtöne |
| HE-S16 | GS | 9 | 0 | 5 | 1 | 0 | Seufzerpaare |
| HE-S21 | KB | 32 | 0 | 24 | 40 | 0 | chromatisches Fugato-Subjekt und leere Skalen über statischem Cm – Reibung gewollt |
| HE-S21 | GS | 24 | 0 | 18 | 30 | 0 | chromatisches Fugato-Subjekt und leere Skalen über statischem Cm – Reibung gewollt |
| HE-S21 | HM | 12 | 0 | 9 | 13 | 1 | chromatisches Fugato-Subjekt und leere Skalen über statischem Cm – Reibung gewollt |
| HE-S21 | TU | 10 | 0 | 9 | 0 | 1 | chromatisches Fugato-Subjekt und leere Skalen über statischem Cm – Reibung gewollt |
| HE-S25 | GS | 5 | 0 | 3 | 2 | 0 | Nebennotenzelle um das Binnenpedal |
| HE-S26 | TU | 14 | 0 | 2 | 1 | 0 | Tupferzellen: Seufzer, Halbtonpaar, Vorschlag |
| HE-S29 | TU | 8 | 0 | 4 | 3 | 1 | Doppelnachbar-Zellen um Klangtöne |
| HE-S30 | GS | 6 | 0 | 1 | 0 | 0 | lyrische Vorhaltpaare, Schluss auf großer Septime |
| HE-S30 | HM | 11 | 2 | 2 | 0 | 0 | lyrische Vorhaltpaare, Schluss auf großer Septime |
| HE-S32 | GS | 15 | 0 | 0 | 0 | 0 | überwiegend Klangtöne |
| HE-S35 | TU | 3 | 0 | 0 | 0 | 1 | Glockenruf im Tritonus |
| HE-S36 | TU | 15 | 0 | 2 | 0 | 0 | Ganztonspirale auf der Reihe des gerade klingenden Felds |
| HE-S38 | GS | 5 | 0 | 1 | 1 | 1 | helle Drohzelle: Tritonus und Halbtonfall |
| HE-S39 | GS | 6 | 0 | 0 | 0 | 0 | Großterzlinie auf Klangtönen |
| HE-T02 | GS | 7 | 0 | 7 | 1 | 0 | Vierton-Prototyp: Vorhalte auf schwerer Zeit |
| HE-T02 | TU | 2 | 0 | 1 | 1 | 1 | Vierton-Prototyp: Vorhalte auf schwerer Zeit |
| HE-T05 | GS | 12 | 0 | 12 | 0 | 0 | Prototyp rhythmisch transformiert |
| HE-T07 | GS | 4 | 0 | 4 | 0 | 0 | Prototyp in wechselnden Rollen |
| HE-T07 | TU | 4 | 0 | 4 | 0 | 0 | Prototyp in wechselnden Rollen |
| HE-T07 | KB | 7 | 0 | 6 | 0 | 0 | Prototyp in wechselnden Rollen |

Motive, Phrasen und Bassfiguren tragen ihre Tonfunktionen einzeln im Vokabular. Bei den Bassfiguren mit festen Tönen sind alle F- und U-Töne beabsichtigt (Tritonus- und Halbtonpedale, chromatische Annäherung, Vorwegnahme), mit einer Ausnahme, die korrigiert wurde (HE-B42, Abschnitt 3).

## 8 Technische Rollenanforderungen

Jede Vorlage und Studie mit besonderer Anforderung trägt eine Zeile „Technische Anforderungen“; die Matrix mit Vereinfachungen steht in Abschnitt L des Vokabulars. Für Studien werden die Anforderungen aus den Rollendaten bestimmt (mehrstimmige Pedale in Bassrollen, Tonlängen ab einer Halben in Kurzrollen, Pedale über Akkordwechsel, Registervorgaben, Komponenten), für Vorlagen nach Inhalt zugeordnet. Keine Studie braucht zusätzliche MIDI-Ausgänge; mehrstimmige Tupfer kommen nicht vor.

## 9 XYZ-Abdeckung nach der Ergänzung

| Ecke | H | R | B | M | P | S |
|---|---|---|---|---|---|---|
| DRS | 15 | 12 | 5 | 18 | 4 | 7 |
| DRU | 40 | 34 | 26 | 25 | 14 | 14 |
| DIS | 6 | 4 | 5 | 1 | 0 | 2 |
| DIU | 16 | 14 | 6 | 4 | 0 | 4 |
| HRS | 7 | 0 | 1 | 5 | 1 | 3 |
| HRU | 8 | 2 | 1 | 2 | 1 | 5 |
| HIS | 6 | 0 | 0 | 1 | 0 | 2 |
| HIU | 3 | 0 | 1 | 1 | 1 | 3 |

Rhythmus-, Bass- und Motivvorlagen sind zusätzlich mit einem Färbungsbereich versehen; die meisten sind färbungsunabhängig und werden nach Y und Z gewählt. Die neuen hellen und kraftvoll-ruhigen Vorlagen sind eigene Gestalten (Hochlagen-Repetitionspaare, unregelmäßig gefüllte Triolen, Säule mit Nachschlag, Ganztonspirale, Drohzelle ohne Fanfare), keine transponierten Kopien.

## 10 Verhältnis zu den BH-IDs (24.11.2026)

| BH | HE | Bemerkung |
|---|---|---|
| BH-H01 | HE-H01 | gleich |
| BH-H02 | HE-H03 | gleiches Pendel |
| BH-H03 | HE-H79, HE-H11 | als Mauer bzw. mit mM7 |
| BH-H04 | HE-H33 | mit Quelle „The Toys“ |
| BH-H05 | HE-H32 | weiterhin H |
| BH-H06 | HE-H56, HE-H57, HE-H89 | jetzt mit Komponentenplan |
| BH-H07 | HE-H43 | gleiches Verfahren |
| BH-H10 | HE-H41 | Großterzzyklus |
| BH-H14 | HE-H19 | gleich |
| BH-H18 | HE-H21 | gleich |
| BH-H25 | HE-H38 | als Folge |
| BH-H26 | HE-H48 | gleich |
| BH-H29 | HE-H07 | auf mM7 übertragen |
| BH-H31 | HE-H20 | Gegenrichtung |

## 11 Offene Punkte

- Belege zur Modulform (Schneller) liegen nur als wörtliche Snippets vor; Einbettung im Volltext ungeprüft.
- HE-H32, HE-H76 und Teile von HE-H101 stützen sich auf Quellen geringer Qualität (als H gekennzeichnet).
- XYZ-Anker sind Setzungen. Ein Hörtest der MIDI-Dateien mit der eigenen Instrumentierung bleibt der nächste Prüfschritt, besonders für HE-S35–S40.
