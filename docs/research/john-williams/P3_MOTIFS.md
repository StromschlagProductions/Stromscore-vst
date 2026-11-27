# Williams P3 – charakteristische kurze Motivvorlagen

Ausgangspunkt: `a8efd75`, `develop/composition-core-prototype`. P2 ist technisch
geprüft, aber noch nicht musikalisch abgenommen. Die positive Anwenderabnahme der
Arpeggio-Phrasierung `2c6f366` bleibt gültig; P3 ist ein eigener Hörschritt.
Kein Push, kein Release, keine GUI- oder Ausgangserweiterung.

## Umfang und musikalische Bedeutung

Alle 48 kanonischen M-Grundvorlagen wurden einzeln geprüft. **32 vollständige
einstimmige Grundformen** sind registriert, **16 ausdrücklich zurückgestellt**.
Es wurden keine Töne entfernt, Figuren auf acht Noten gekürzt, charakteristische
Spitzen abgeschnitten oder Terzparallelen als angeblich gleichwertige Einzelstimme
importiert. Die kanonischen Forschungsoriginale bleiben unverändert.

Importiert werden Tonfolge, Einsatzrhythmus, notierte Dauern und Pausen,
Harmoniebezug, XYZ-Anker und Herkunft. Konkrete Töne sind laut Forschung **eigene
Konstruktionen (E)**, keine Transkriptionen bekannter Filmthemen. Die jeweiligen
Evidenzklassen des Verfahrens bleiben im Original nachlesbar.

Die Quellen umfassen nicht nur helle Signale: chromatische Glocke und
Doppelnachbarn, Halbtonreibungen, Moll-Klage, synkopierte Spannungszellen und
Repetition mit Halbtonfall stehen neben Quintsprüngen, Kampfkonturen,
Nonensprüngen, Galopp und Quartsprung/Tritonus-Rätsel. Die vorgeschriebenen
Kanon-, Parallelstimmen-, Rollenübergabe- und Langformentwicklungen der Recherche
sind damit **nicht automatisch umgesetzt**. Vorhandene Wiederkehr, Variation und
Rollenkoordination bleiben die gemeinsame Produktionsgrundlage.

## Gemeinsamer Daten- und Produktionspfad

* `scripts/build_williams_motifs.py` prüft den kanonischen SHA-256, sämtliche 48 IDs,
  Quelltöne, Pausen und Zweitaktsummen. Er erzeugt `data/williams/motifs.json` mit
  der vollständigen Entscheidungsliste und `Source/WilliamsMotifs.generated.h`
  ausschließlich mit freigegebenem Material. CMake prüft Daten-/Header-Drift.
* `Source/AuthoredMotifSource.h::AuthoredMotifSource` ist der gemeinsame kurze
  Vorlagentyp. Barry verwendet denselben Typ mit unveränderten Grunddaten und
  weiterhin akkordtongebundener Semantik. Zusätzliche Harmonie-/Melodietonmasken
  sind optional; es gibt keine zweite Williams-Motivengine.
* `ScoreEngine.h::authoredMotif` benutzt den vorhandenen Vorlagenpfad auch für
  Williams Score. Er prüft **alle** Töne und Dauern gegen geplante Harmonie,
  Instrumentenannahmen, Register und verfügbare Zeit. Ganze Oktavversetzungen
  erhalten die Originalintervalle. Auswahl aus kompatiblen Vorlagen in der
  gewichteten XYZ-Nähe; Radius 0,25, Gewichte `exp(-score/0,025)`, deterministische
  gewichtete Auswahl aus Seed, Variation, Stimme und Abschnitt. Der kleine
  Registerkostenanteil bleibt Bestandteil des Abstands. Keine Notendichtequote,
  keine Veränderung der harmonischen XYZ-Auswahl oder Aktivierungsschwellen.
* `authoredPitchMask` autorisiert Nicht-Akkordtöne über ihre **explizite
  Quellharmonie einschließlich Bassbezug**. Ein C-Motiv macht daraus keinen
  beliebigen Tonvorrat für einen fremden Akkord. Enthält die aktuelle Harmonie
  keine passende Quellenbeziehung, wird die Figur verworfen. Ein Ton, der im
  anderen Quellabschnitt nur Akkordton war, wird dadurch nicht überall zum
  zulässigen Fremdton. Akkordfarben der Begleitung werden nicht verändert.
* Bei expliziter Oktatonik müssen **sämtliche** harmonischen und melodischen
  Quelltöne zum transponierten gemeinsamen Kontext passen. M06 und M45 können
  dessen zusätzliche Töne nutzen; andere Quellen erhalten keine pauschale
  Oktatonikfreigabe. Insbesondere werden weder D noch B in Okt-A/C hineingedeutet.
* `planMotifNote` spielt die geeignete Grundform. **Nur tatsächlich ausgegebene
  Noten** werden im vorhandenen `RememberedMotif` erfasst. Herkunfts-ID
  `50000 + M-Nummer` und tatsächliche Intervall-/Zeitidentität bleiben getrennt.
  Die beiden Stimmen behalten unabhängige Verwendung und Fortschritte.
* Nach dem ersten gehörten Ton bleibt die Quelle fest. Ein bereits frei
  begonnener Gedanke kann auch dann keine Vorlagen-ID mehr erhalten, wenn später
  eine Quelle zur Harmonie passt. Das verhindert eine falsche Quellenzuweisung
  und gemischte Originale bei XYZ-Veränderungen. XYZ kann keine fremde
  Vorlage in den bereits begonnenen Gedanken spleißen. Harmonieänderungen werden
  bei Wiederkehr, Fortsetzung und verbleibenden Noten mit demselben autorisierten
  Kontext geprüft (`motifPitchMask`, `remainingMotifFits`, `continueMotif`,
  `motifOccurrence`). Unspielbare Gelegenheiten dürfen pausieren.
* Frühe Originalreprise, spätere rhythmische Variation, Sequenz, Fragment und
  Augmentation nutzen den bestehenden Kern und das unveränderliche Original.
  M06 wird ausdrücklich **nur dem Dialog** angeboten; M22 ist ausdrücklich
  **einmalige Einführung je Stimmenzustand**, keine automatisch wiederholte
  Staunensschleife. Eine globale Einmaligkeit über beide unabhängigen Stimmen
  hinweg ist damit noch nicht umgesetzt; die Forschungsanweisung „einmal pro
  Szene“ ist in diesem verfahrensbezogenen Teil zurückgestellt. Beide Stimmen
  können die Grundform jeweils einmal unabhängig vorstellen.
* Die Hauptmelodie bleibt standardmäßig AUS. Aktivierung, Mute/Solo, Motiv- und
  Legatoschalter bleiben maßgeblich. Legato AUS verändert die Artikulation,
  nicht die notierten Einsätze. Tremolo, Pizzicato, Spiccato und Instrumentnamen
  der Forschung sind **keine erkannte externe Patchfähigkeit** und lösen keine
  neuen Keyswitches oder zwangsweise Instrumentierung aus.

Alle Laufzeitdaten sind statisch. Keine Dateioperationen, Datenvalidierungen oder
Heap-Allokationen wurden in den Audiothread eingeführt. Notierte Sechzehntelzahlen
sind Quelldaten/Musterindizes, keine alternative Laufzeituhr; beim Vorlageneintritt
werden daraus exakte 960-PPQ-Ticks. Gespeicherte Motive und Varianten bleiben Tick-Daten.

## Einzelbewertung aller 48 Quellen

„Eingebunden“ bedeutet eine vollständige, musikalisch prüfbare Grundform im
Produktionspfad, **keine Garantie ihrer Auswahl in jeder Umgebung**. Manche
Grundformen benötigen Harmonie- oder Taktkonstellationen, die der aktuelle
49er-Harmoniepool und die Einführungsfenster selten gemeinsam anbieten.
Wiederkehranweisungen der Forschung wie Kanon oder Wechselinstrumentierung sind
außerhalb der ausdrücklich genannten Regeln keine neu implementierte Formgrammatik.

| ID | Grundform | XYZ | Entscheidung | Produktionsnachweis |
|---|---|---|---|---|
| JW-M01 | Quintaufschwung mit Doppelschlag | 0.75 / 0.45 / 0.35 | In dieser Matrix nicht nachgewiesen |
| JW-M02 | Kampfkontur | 0.7 / 0.7 / 0.45 | In dieser Matrix nicht nachgewiesen |
| JW-M03 | Zielton mit Obersekund-Vorhalt | 0.7 / 0.55 / 0.3 | 231 ausgeführte Noten |
| JW-M04 | Quartsignal | 0.7 / 0.75 / 0.4 | Zurückgestellt: Exakter dreitöniger Quartklang Cq fehlt; kein Ersatz durch den vierstimmigen Quartaltyp |
| JW-M05 | Repetition und kleine Terz | 0.2 / 0.45 / 0.5 | In dieser Matrix nicht nachgewiesen |
| JW-M06 | Sechsfache Repetition mit Halbtonfall | 0.2 / 0.4 / 0.6 | 2336 ausgeführte Noten |
| JW-M07 | Verminderte Terz (Gegenspieler) | 0.15 / 0.4 / 0.55 | In dieser Matrix nicht nachgewiesen |
| JW-M08 | Lydischer Doppelnachbar | 0.85 / 0.25 / 0.3 | 550 ausgeführte Noten |
| JW-M09 | ♭6–5–♯4-Zelle | 0.2 / 0.45 / 0.55 | In dieser Matrix nicht nachgewiesen |
| JW-M10 | Pentatonischer Hüpfer | 0.8 / 0.45 / 0.5 | Zurückgestellt: Neun Originaltöne überschreiten die Acht-Noten-Grenze |
| JW-M11 | Oktatonische Synkope in Unterterzen | 0.3 / 0.65 / 0.8 | Zurückgestellt: Zehn Töne und verpflichtende parallele Unterterzen benötigen polyphones Motivmaterial |
| JW-M12 | Nervöses vermindertes Arpeggio | 0.3 / 0.6 / 0.8 | Zurückgestellt: 13 Originaltöne überschreiten die Acht-Noten-Grenze |
| JW-M13 | Chromatische Glockenfigur | 0.3 / 0.35 / 0.45 | 61 ausgeführte Noten |
| JW-M14 | Zitternder chromatischer Doppelnachbar | 0.3 / 0.25 / 0.65 | 16 ausgeführte Noten |
| JW-M15 | Seufzerkette | 0.25 / 0.3 / 0.35 | In dieser Matrix nicht nachgewiesen |
| JW-M16 | Triolensequenz (fallend, steigend gekettet) | 0.75 / 0.5 / 0.45 | Zurückgestellt: Elf Originaltöne und noch fehlender Triolen-Vorlageneintritt |
| JW-M17 | Heroische Tetrachorde | 0.75 / 0.75 / 0.4 | In dieser Matrix nicht nachgewiesen |
| JW-M18 | Steigende Quartenkette | 0.65 / 0.7 / 0.55 | Zurückgestellt: Exakter dreitöniger Quartklang Cq fehlt |
| JW-M19 | Synkopierte Militärzelle | 0.55 / 0.7 / 0.55 | 33 ausgeführte Noten |
| JW-M20 | Romantischer Sextaufschwung | 0.6 / 0.4 / 0.25 | In dieser Matrix nicht nachgewiesen |
| JW-M21 | Wiegenterzen | 0.7 / 0.2 / 0.2 | 177 ausgeführte Noten |
| JW-M22 | Staunen: Nonensprung | 0.8 / 0.3 / 0.4 | 165 ausgeführte Noten |
| JW-M23 | Quarte–Tritonus-Rätsel | 0.3 / 0.25 / 0.5 | 20 ausgeführte Noten |
| JW-M24 | Tiefe Lauerzelle | 0.15 / 0.2 / 0.45 | Zurückgestellt: Tiefe Quelllage Ab2–D3 benötigt eine ausdrückliche Register-/Rollenvorgabe; bloßes Hochoktavieren wäre untreu |
| JW-M25 | Chromatischer Stolperer | 0.75 / 0.4 / 0.6 | 38 ausgeführte Noten |
| JW-M26 | Mechanischer Marschgruß | 0.8 / 0.45 / 0.45 | 2640 ausgeführte Noten |
| JW-M27 | Abenteueraufruf | 0.8 / 0.7 / 0.4 | 1521 ausgeführte Noten |
| JW-M28 | Moll-Klagezelle i–♭6–5 | 0.2 / 0.4 / 0.35 | 170 ausgeführte Noten |
| JW-M29 | Phrygischer Abstieg | 0.2 / 0.55 / 0.45 | In dieser Matrix nicht nachgewiesen |
| JW-M30 | Hexatonische Linie | 0.45 / 0.35 / 0.55 | Zurückgestellt: Gemeinsamer expliziter Hexatonik-Kontext fehlt |
| JW-M31 | Ganztonschwebe | 0.6 / 0.2 / 0.55 | Zurückgestellt: Gemeinsamer expliziter Ganzton-Kontext fehlt |
| JW-M32 | Oktatonischer Verbindungslauf | 0.35 / 0.75 / 0.75 | Zurückgestellt: Neun Originaltöne überschreiten die Acht-Noten-Grenze |
| JW-M33 | Kurze Antwortfigur | 0.7 / 0.3 / 0.3 | Zurückgestellt: Antwortgebundene Quelle benötigt einen ausdrücklichen Rollenauftrag; keine freie Einführung als Ersatz |
| JW-M34 | Schwere Quint-Oktav-Zelle | 0.15 / 0.8 / 0.25 | In dieser Matrix nicht nachgewiesen |
| JW-M35 | Synkopiertes Quintpendel (6/8) | 0.7 / 0.4 / 0.6 | 184 ausgeführte Noten |
| JW-M36 | Isolierter Quinteinwurf | 0.7 / 0.15 / 0.5 | In dieser Matrix nicht nachgewiesen |
| JW-M37 | Lydisch-♯2-Hüpfer | 0.7 / 0.3 / 0.65 | 1345 ausgeführte Noten |
| JW-M38 | Wrong-note-Punktierung | 0.75 / 0.35 / 0.65 | 66 ausgeführte Noten |
| JW-M39 | Hexatonische Abwärtszelle, synkopiert | 0.7 / 0.35 / 0.6 | Zurückgestellt: Gemeinsamer expliziter Hexatonik-Kontext fehlt |
| JW-M40 | Galoppzelle | 0.75 / 0.7 / 0.6 | 80 ausgeführte Noten |
| JW-M41 | Sechzehntel-Fanfarenkopf mit Staccato-Achtel | 0.85 / 0.8 / 0.6 | Zurückgestellt: Zehn Originaltöne überschreiten die Acht-Noten-Grenze |
| JW-M42 | Leiser Kleinterz-Kreisel (oktatonisch) | 0.2 / 0.2 / 0.6 | Zurückgestellt: Verpflichtende parallele Unterterzen benötigen polyphones Motivmaterial; keine einstimmige Reduktion |
| JW-M43 | Choralabstieg 5→3 mit ♭6-Reibung | 0.15 / 0.65 / 0.3 | In dieser Matrix nicht nachgewiesen |
| JW-M44 | Dies-irae-Kopf (Typ 1) | 0.15 / 0.55 / 0.35 | 325 ausgeführte Noten |
| JW-M45 | Dies-irae-Umkehrung (Typ 5) | 0.15 / 0.7 / 0.55 | 1604 ausgeführte Noten |
| JW-M46 | Spannungszelle 1–3–2–x–1, synkopiert | 0.2 / 0.4 / 0.6 | 20 ausgeführte Noten |
| JW-M47 | Arpeggio mit Fremdton (♭6) | 0.3 / 0.2 / 0.6 | Zurückgestellt: Exakte Akkorddefinition Cm(b6) fehlt; das charakteristische Ab darf nicht entfallen |
| JW-M48 | Halbton-Mollpaar in hoher Lage | 0.15 / 0.2 / 0.65 | Zurückgestellt: Getrennte Polychord-Komponenten, Registerbedeutung und Kontext fehlen |


## Musikalische Grenzen

* Acht Noten im unveränderlichen Original und monophone Motivplanung bleiben die
  bewusste bestehende Grenze. Es gibt weiterhin keine Langphrasenengine.
* Zwei harmonische Quellabschnitte autorisieren die notierten Figuren, aber keine
  allgemeine lydische, hexatonische, phrygische oder chromatische Grammatik.
  M08/M37 etwa spielen ihre ausdrücklich notierte Färbung über passender
  Quellharmonie; daraus folgt kein neuer gemeinsamer Lydisch-Kontext.
* Ein passend transponierter Registerbereich ist erforderlich. Noten werden nicht
  einzeln in eine enge Lage gefaltet. Einige Quellen sind deshalb für einen
  konfigurierten Ausgang nicht verfügbar.
* In diesem Schritt ist die Williams-Vorlagenauswahl auf Katalogharmonik
  begrenzt. Eigene Akkordfolgen behalten die bisherige freie Motivbildung.
  Es wird keine automatische passende Begleitharmonie zu einer Motivquelle ergänzt.
* Ein neues Motiv wird nicht allein wegen eines anderen XY-Bereichs in ein bereits
  aufgenommenes Original gewechselt. Das gemeinsame begrenzte Gedächtnis und
  seine vorhandene Szenen-/Variationssemantik bleiben erhalten. Lange XYZ-Fahrten
  sind keine zwangsläufige Demonstration aller 32 Quellen.
* Geeignete Harmonik, Einführungsfenster und Rollenpriorität sind zusätzliche
  Voraussetzungen neben XYZ. Registrierungszahl, Auswahlzahl, Notenzahl und
  subjektive stilistische Erkennbarkeit sind unterschiedliche Befunde.
* Die Begleitharmonik, Bass-, Flächen-, Akzent- und Arpeggioverfahren wurden nicht
  verändert. Andere Motivfenster können über die **bestehende** Rollenkoordination
  andere Auto-Arp-Pausen verursachen. Die abgenommene Arp-Phrasierungsstrategie,
  Arp-Tempo, Tonwahl und Muster sind unverändert.
* Kaltes Seek besitzt weiterhin keine erfundene musikalische Vorgeschichte.
  Technischer Determinismus beweist weder Filmassoziation noch musikalische Qualität.

## Hörabnahme

`P3_MOTIFS_AB.zip` enthält tatsächliche Engine-A/B-Ausgaben gegen `a8efd75`;
keine nachträglich komponierten Demonstrationslinien. Gleiche Instrumente und
Lautstärken verwenden; zunächst Melodie und Dialog getrennt hören, anschließend
mit der Begleitung. Die zusammenhängenden Dateien haben je 128 Takte bei 100 BPM.
Notennamen können in Hosts oktavversetzt angezeigt werden; MIDI-Notennummern sind
maßgeblich. Konkrete Einstellungen, Herkunfts-IDs, Wiederkehr und Varianten stehen
in `P3_MOTIFS_RESULTS.json`. P3 und P2 warten auf die musikalische Anwenderabnahme.

## Produktionsnachweise und A/B-Ergebnis

* **156 reale A/B-Paare**: 13 XYZ-Fälle einschließlich langsamer/schneller Fahrt
  über 128 Takte; alle 49 Harmonieanker über 64 Takte; sechs Referenzanker in
  sämtlichen zwölf Transpositionen über 128 Takte; zusätzliche Seeds; vier
  6/8-Fälle über 128 Takte, Dialog allein und beide melodischen Stimmen.
* **20 Quellen tatsächlich hörbar ausgeführt**, nicht nur gewichtet oder als
  Testdaten registriert: JW-M03, JW-M06, JW-M08, JW-M13, JW-M14, JW-M19, JW-M21, JW-M22, JW-M23, JW-M25, JW-M26, JW-M27, JW-M28, JW-M35, JW-M37, JW-M38, JW-M40, JW-M44, JW-M45, JW-M46.
* **11.582 zu Vorlagenplänen zugeordnete Note-ons** über die gesamte Matrix.
  Das ist eine Summe vieler Vergleichsläufe, keine Aktivitätsquote und kein
  musikalisches Qualitätsziel. Jede solche Note wurde gegen den tatsächlichen
  autorisierten Harmoniebezug geprüft. Die Diagnoseversion liefert bytegleich
  dieselben Ereignisse wie die unveränderte Produktionsabfrage.
* Originale bleiben im gezielten 128-Takt-Test unverändert identifiziert;
  vollständige Reprisen und spätere Varianten sind tatsächlich ausgeführt.
  Die folgende Gruppenstatistik zählt beobachtete Figuren, nicht Absichten:

| Figur | Beobachtete Gruppen |
|---|---:|
| Einführung | 267 |
| Original-Wiederkehr | 1172 |
| Rhythmische Variante | 323 |
| Sequenz | 87 |
| Fragment | 205 |
| Augmentation | 89 |

Die zwölf registrierten, in dieser Matrix **nicht** nachgewiesenen Quellen sind:
JW-M01, JW-M02, JW-M05, JW-M07, JW-M09, JW-M15, JW-M17, JW-M20, JW-M29, JW-M34, JW-M36, JW-M43. Ihr vollständiger Quellplan wird in allen zwölf
Transpositionen mit passenden synthetischen Harmonien geprüft. Das ersetzt keinen
Produktionsnachweis. Beispielsweise braucht M02 einen zum Einführungsfenster
passenden C→G-Verlauf, M01 zusätzlich G/D, M15 Fm6→G7sus4 und M20 Am7→Fmaj7.
Diese Beziehungen sind nicht schon deshalb verfügbar, weil deren einzelne Klänge
irgendwo im 49er-Katalog vorkommen. Seltene XYZ-/Register-/Rollenbedingungen und
wenige geprüfte Seeds sind weitere Gründe für einen fehlenden Nachweis.
**32 registrierte Grundformen sind keine Behauptung, im Hörbetrieb seien bereits
alle 32 gleich gut erreichbar.** Es wurden dafür weder Harmonien verändert noch
unpassende Quellen erzwungen.

### Konkrete tatsächliche Notenfolgen

1. **Galopp M40, XYZ 0,85 / 0,85 / 0,85, D, Hauptmelodie:**
   MIDI `69–71–73–74–78–76–74–81` = `A4–B4–C#5–D5–F#5–E5–D5–A5`.
   Einsätze in Viertelnoten ab Beginn:
   `0 / 0,5 / 0,75 / 1 / 2 / 2,5 / 2,75 / 3`.
   Das sind beide vollständigen `2–1–1–4`-Galoppgruppen der Quelle. Takt 2 bleibt
   ohne weitere Motivanschläge. Dieselbe achttönige Kontur erscheint in diesem
   Lauf erstmals wieder bei Viertelnote 128, also nach **32 Takten**; weitere
   Originale bei 352 und 384. Diese lange erste Lücke ist ausdrücklich eine
   bestehende Kombination aus Wiederkehrplanung, Harmonieeignung und Rollen,
   keine versprochene frühe Reprise jedes neuen Motivs.
2. **Abenteueraufruf M27, XYZ 0,85 / 0,85 / 0,20, D, Hauptmelodie:**
   `69–71–73–74–78–76–81`, Einsätze
   `0 / 0,25 / 0,5 / 1 / 2 / 3 / 4`.
   Vollständige erste Reprise ab Viertelnote 32 (**acht Takte**), spätere
   rhythmische Variante ab 96. Das Original bleibt unverändert gespeichert.
3. **Dunkle Repetition M06, XYZ 0,15 / 0,25 / 0,80, D, Dialog:**
   `57–57–57–57–57–57–56` = `A3` sechsmal, dann `G#3`.
   Erste Einführung in diesem Lauf ab Viertelnote 64; sechs Sechzehntel und
   anschließender gehaltenener Halbtonfall, danach die notierte Pause.
   Vollständige Reprise ab 80, also **vier Takte** nach der Einführung;
   weitere bei 112, rhythmische Variation bei 176. Keine Übernahme durch die
   Hauptmelodie. In expliziter Oktatonik werden G und F# der C-Quelle zu A und
   G# transponiert, ohne die charakteristische Halbtonbewegung wegzurunden.
4. **Moll-Klage M28, XYZ 0,15 / 0,20 / 0,20, D:** Hauptmelodie
   `74–77–82–81` = `D5–F5–Bb5–A5`, Einsätze `0 / 1,5 / 2 / 4`.
   Dialog später in eigener Lage `62–65–70–69`, mit unabhängigem Beginn und
   Fortschritt. Beide verweisen auf tatsächlich gehörtes Material; eine gleiche
   Intervall-/Rhythmusidentität bedeutet keine geteilten Cursor.
5. **Langsame Fahrt:** M40 wird ab Viertelnote 64 vollständig eingeführt und
   erscheint insgesamt in fünf achttönigen Figuren. **Schnelle Fahrt:** keine
   kanonische Vorlage nachgewiesen; die frei begonnenen Motive bleiben frei.
   Eine begonnene freie Figur kann auch bei späterer Harmonieeignung keine
   Vorlagen-ID mehr erhalten. Der gezielte Quellbesitztest prüft dies für alle
   32 Quellen und zwölf Transpositionen. Es werden weder gemischte Notenfolgen
   als kanonische Quelle etikettiert noch falsche Fortsetzungen erzwungen.


### Begleitung und Grenzen des Vergleichs

Fläche lang/kurz, Bass lang/kurz, Tupfer und Stich haben in **allen 156 Paaren**
dieselben MIDI-Ereignisse einschließlich Zeit, Tonhöhe, Velocity und Controller.
Die Reihenfolge voneinander unabhängiger gleichzeitiger Ereignisse kann durch
die veränderte melodische Notenverwaltung abweichen; der Vergleich verwendet
für diese Begleitrollen deshalb Ereignismultimengen, keine sinnlose Sortierpflicht.

Auto-Arp-Ereignisse unterscheiden sich in **125 Paaren**, weil die bestehenden
Motivreservierungen andere tatsächliche Vordergrundfenster erhalten. Das ist
keine erneute Arp-Optimierung. `ArpeggioPhrase.h` sowie `arpeggioFigureEnd`,
`playArpeggio`, `arpeggioPeriod` und `roleRhythm` sind gegenüber `a8efd75`
unverändert. Ohne aktive melodische Rollen ist Williams in fünf geprüften
XYZ-Fällen **vollständig bytegleich**. Zusätzlich sind 35 Fälle anderer Profile
bzw. Pop/Rock bytegleich, insgesamt **40 vollständige MIDI-Regressionsfälle**.

14 Wiederholungs-/Blockgrößen-/Transportkontrollen decken beide Follow-Zustände,
Swing, 4/4, 3/8, 5/8, 6/8, 7/8, Stop/Restart, warmen Loop und Vorwärtssprung ab.
Die vier zusätzlichen 6/8-Produktionsfälle führen M21 und M35 tatsächlich aus.
Die Vergleichsdateien verwenden dieselbe Instrumentierung und neun bisherigen
MIDI-Ziele. Die Hauptmelodie bleibt in der Anwendung optional und standardmäßig AUS.

Reproduktion:

```sh
python scripts/build_williams_motifs.py --check
python Tests/WilliamsMotifDataTests.py
python scripts/validate_williams_motifs.py /tmp/stromscore-williams-p3
```

Die Vorlagenanweisungen für Tremolo, Kanon, Instrumentenwechsel und globale
Szenen-Einmaligkeit werden nicht mit dem Notenimport als automatisch erledigt
behauptet. Die Vorlagen sind keine Garantie von Star-Wars-/Indiana-Jones-
Assoziationen. Die musikalische Qualitäts- und Stilabnahme bleibt beim Anwender.

| Paar | Tatsächlicher Kontext | Quellen | Erste Einführung / Reprise |
|---|---|---|---|
| 01-before.mid / 01-after.mid | XYZ (0.15, 0.2, 0.2); Tonart 2 (0=C, 2=D) | JW-M28 | 0.0 s / 28.8 s |
| 02-before.mid / 02-after.mid | XYZ (0.15, 0.25, 0.8); Tonart 2 (0=C, 2=D) | JW-M06 | 38.4 s / 48.0 s |
| 03-before.mid / 03-after.mid | XYZ (0.15, 0.85, 0.2); Tonart 2 (0=C, 2=D) | JW-M44 | 0.0 s / 19.2 s |
| 04-before.mid / 04-after.mid | XYZ (0.85, 0.25, 0.8); Tonart 2 (0=C, 2=D) | JW-M37 | 0.0 s / 12.0 s |
| 05-before.mid / 05-after.mid | XYZ (0.85, 0.85, 0.2); Tonart 2 (0=C, 2=D) | JW-M27 | 0.0 s / 19.2 s |
| 06-before.mid / 06-after.mid | langsame XYZ-Fahrt; Tonart 2 (0=C, 2=D) | JW-M40 | 38.4 s / 67.2 s |
| 07-before.mid / 07-after.mid | schnelle XYZ-Fahrt; Tonart 2 (0=C, 2=D) |  | – / keine nachgewiesen |
| 08-before.mid / 08-after.mid | H03 / XYZ [0.85, 0.3, 0.25]; Tonart 0 (0=C, 2=D) | JW-M08, JW-M26 | 0.0 s / 9.6 s |
| 09-before.mid / 09-after.mid | XYZ (0.85, 0.85, 0.85); Tonart 2 (0=C, 2=D) | JW-M40 | 0.0 s / 76.8 s |

## Technische Abschlussprüfung

* **60/60 Core-Gesamttests**, einschließlich Harmonie-, Scheduler-, Transport-,
  Phrasen-, Motiv-, Rhythmus-, Besetzungs- und MIDI-Regressionen, bestanden.
* Nach der gezielten Quellbesitzabsicherung die betroffenen Williams-/Motiv-/
  Oktatonik-Ziele neu gebaut und **4/4 gezielte CTest-Prüfungen** erneut bestanden.
  Zusätzlich prüfen acht statische/dynamische 128-Takt-Kontexte die tatsächlich
  gespeicherten Noten gegen die kanonische Quelle: jede Position muss passen,
  alle Tonhöhen müssen dieselbe gemeinsame Oktavversetzung besitzen.
* **3/3 echte Plugin-Prozessortests** nach dem finalen Patch bestanden. Die neue
  Williams-Prüfung vergleicht Live-Ausgabe mit dem tatsächlichen SMF-Export in
  acht 64-Takt-Fällen (zwei Harmonien, C/H, gerade/Swing). Keine hängenden Noten,
  keine C-/C++-Heap-Allokationen innerhalb der geprüften Prozessaufrufe.
* **ASan/UBSan** auf dem finalen Motivpfad erfolgreich; keine Befunde.
* **4/4 Offline-Motivdatenprüfungen**, einschließlich Ablehnung von manipulierten
  Manifest-Noten, XYZ und Namen gegenüber dem kanonischen Text, bestanden.
* Gemeinsame Harmonie-, Barry- und Williams-Generierungsprüfungen aktuell;
  **7/7 Paketprüfungen** bestanden. UTF-8 wird beim neuen Import ausdrücklich
  verwendet, unabhängig von der Windows-Systemzeichencodierung.
* **Linux-VST3** aus dem finalen Quellstand gebaut. Kein Windows-CI-Auftrag,
  kein Push, kein Tag und kein Release in diesem Schritt.

Die Datenfingerabdrücke im Ergebnis-JSON stimmen mit dem finalen Engine-Quellstand
überein. Alle 156 A/B-Paare wurden nach der Quellbesitzabsicherung neu erstellt.
Die schnelle Fahrt ist danach vollständig MIDI-bytegleich mit `a8efd75`: der
bestehende freie Gedanke wird weder umetikettiert noch durch eine neue Vorlage
ersetzt. Musikalische Hörabnahme von P2/P3 steht aus.


## Aktualisierter Hörabnahmestand

Der Anwender hat Windows-Build `023b0a6` mit P2/P3 ausdrücklich positiv gehört und als musikalische Entwicklungsgrundlage akzeptiert. Details und Reichweite: [Abgenommene Referenz 023b0a6](../../development/ACCEPTED_REFERENCE_023b0a6.md). Frühere Hinweise auf eine ausstehende Hörabnahme beschreiben den damaligen Stand.
