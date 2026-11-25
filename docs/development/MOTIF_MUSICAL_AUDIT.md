# Kritische musikalische Untersuchung: Melodie, Dialog und Motivik

25. November 2026 · `develop/composition-core-prototype` · **9a8d01c**.
Nur Untersuchung, Dokumentation und exportierte Hörbeispiele. Keine Engineänderung.

Die grundsätzlich positive Anwenderabnahme von Barry und Neutral ist als
[Referenz](ACCEPTED_REFERENCE_9a8d01c.md) dokumentiert. Die Begleitung wird hier nicht
neu bewertet und wurde nicht verändert.

## Ergebnis und Einordnung des Hörbefunds

**Das Motivgedächtnis ist im unbegrenzten Modus aktiv und bleibt erhalten.** Es gibt
keine generelle Abschaltung ohne Fahrt oder Szenenlänge. Die Schwäche liegt in der
musikalischen Nutzung dieses Gedächtnisses:

1. Eine Stimme behält üblicherweise ihren ersten abgeschlossenen Gedanken für die
   gesamte Szene. Sie erhält dadurch Wiedererkennung, aber keinen allmählich
   aufgebauten Themenvorrat. Beide Stimmen besitzen weiterhin unabhängige Zustände.
2. Die erste Wiederkehr kann weit vom ersten Auftreten entfernt liegen. Bereits
   der normale Abstand von acht Takten entspricht hier 19,2 Sekunden. Ein belegter
   statischer Neutral-Fall wiederholt sein Hauptmotiv erst **107 Takte später**.
3. Die eingeführten Score-Motive bestehen überwiegend aus vier oder fünf Anschlägen;
   Barry kann acht verwenden. Häufig sind das aber nur zwei bis vier verschiedene
   Tonhöhen. Eine Kontur kann durch lokale Begrenzung sogar auf eine Tonhöhe fallen.
4. Das Variationsprogramm zählt vorgesehene Gelegenheiten, nicht erfolgreich gehörte
   vollständige Wiederholungen. Ein Fragment oder eine veränderte Gestalt kann daher
   die erste tatsächlich gespielte Rückkehr sein, bevor sich das Original eingeprägt hat.
5. Die Hauptmelodie besitzt keine mit Motiven verbundene längere Zielton-/Bogenplanung.
   Die vorhandene freie Phrasenplanung gilt nur für die Score-Gegenstimme bei Motiv AUS.
6. Unter XYZ-Bewegung ist ein zusätzlicher **konkreter Widerspruch im Harmoniebezug**
   der Motivplanung nachweisbar: Vorhersage und laufende Wendungsposition können
   auseinanderfallen, während ein zwischengespeicherter Rückkehrplan gültig bleibt.
7. Der Pop-Dialog ist oft ein motorischer, aus der jeweiligen Harmonie neu erzeugter
   Hook. Ein gespeichertes Original existiert, bestimmt aber nicht jede dieser Noten.
   Eine aktive Motivfunktion bedeutet dort nicht automatisch eine thematische Reprise.

Der Eindruck kurzer Einzelgesten ist damit nachvollziehbar. Die Messung belegt aber
**keine allgemeine Scheduler-Kürzung aller Motive auf zwei bis drei Noten**: In den
statischen Score-Läufen wurden alle tatsächlich angesetzten Rückkehrfiguren vollständig
abgespielt. Manche dieser Figuren sind absichtlich nur zwei-/dreitönige Fragmente.
Vollständige Ausführung, Materialherkunft und musikalische Wiedererkennbarkeit sind drei
unterschiedliche Kriterien.

## Untersuchungsaufbau und Nachprüfbarkeit

- 126 Konfigurationen, jeweils zweimal: direkt gegen unveränderte Produktionsheader
  und mit einem nur lesenden Zustandsbeobachter. **Alle 126 vollständigen MIDI-Ströme
  sind bytegleich.** Der Beobachter steht ausschließlich in einer Offline-Headerkopie.
- 72 Hauptfälle: drei Kontexte × acht XYZ-Verläufe × Variation 1/3/7. Neutral Score,
  Barry Score und Neutral Pop/Rock. Seed 0, Variety 0,5, Inertia EIN.
- Hauptfälle: 128 Takte = **5:07,2 Minuten**, 100 BPM, 4/4, D, 48 kHz, beide Stimmen
  und beide Motiv-/Legatoschalter EIN. Begleitrollen aktiv, getrennte neun MIDI-Kanäle,
  Standardregister, keine eigene Patch-Erkennung. Aufbau AUS, Szene unbegrenzt,
  **interne Fahrt AUS**. Langläufe: sechs Fälle über 512 Takte = 20:28,8 Minuten.
- Statisch: (0,20/0,45/0,40), (0,25/0,85/0,65), (0,80/0,30/0,10),
  (0,85/0,85/0,30), (0,50/0,90/0,90), (1/1/1).
- Langsame/schnelle externe XYZ-Fahrt: X = 0,5 + 0,4 sin(2πq/P),
  Y = 0,85 + 0,1 sin(2πq/(1,3P)+0,3),
  Z = 0,4 + 0,35 sin(2πq/(1,7P)+0,7), q in Viertelnoten;
  P = 64 bzw. 8 Viertel. Parameterwerte alle Sechzehntel gesetzt. Dies simuliert
  laufende Bedienung/Automation ohne Aktivierung der internen Fahrt.
- Kontrollen: Stimmen einzeln, Motive AUS, zwei feste eigene Harmoniefolgen,
  begrenzte 64-Takt-Szene, Aufbau EIN, drei zusätzliche Pop-Positionen, Barry 3/4,
  Tonarten C/F und größerer erlaubter Hauptmelodieumfang.
- Zwölf weitere Produktionsrenderings vergleichen sechs Hauptfälle mit Blockgrößen
  127/8192 gegen 512: **alle bytegleich**. Das Parameteränderungsraster ist dabei gleich.
- Sämtliche 126 Ausgaben ohne doppelte aktive Kanal-/Ton-Paare, verwaiste Note-offs,
  hängende Noten am Ende oder Null-Dauer-Noten.

[Messdaten](MOTIF_MUSICAL_AUDIT_MEASUREMENTS.json),
[Reproduktionsskripte und Methodengrenzen](motif-audit/README.md),
[MIDI-Hörpaket](MOTIF_MUSICAL_AUDIT_MIDI.zip).

Es sind echte `Generator::process()`-Ausgaben mit fortlaufendem simuliertem Hosttransport,
keine isolierten Vorlagentests. Keine neue Studio-One-/VST3-Abnahme und kein erneuter
Live-/Export-Integrationstest. Die MIDI-Dateien dienen der jetzt möglichen Hörprüfung;
eine akustische Qualitätsabnahme wird nicht behauptet. Erhaltene Velocity und Gate
beweisen nicht, dass ein konkreter externer Patch im Mix ausreichend hörbar ist.

## 1. Gedächtnis, Aufnahme und unbegrenzte Wiedergabe

[CompositionCore.h](../../Source/CompositionCore.h): `RememberedMotif` (Zeile 37),
`MotifCatalog` (203), `MotifUse` (225), Performanceaufnahme (252).
[ScoreEngine.h](../../Source/ScoreEngine.h): `motifAvailableUntil` (1072),
`motifStep` (1640), `capturePerformance` (3412), Reset/Profile/Transport (289, 536, 573).

Der Katalog enthält höchstens zwei abgeschlossene unveränderliche Materialien, bei
unserem Umfang eines je Stimme. Register und Herkunft sind vom eigenen Gebrauchszustand
getrennt. Die Identität entsteht aus relativen Tonhöhen, relativen Einsätzen, Dauern und
Zyklusdauer; eine reine Transposition oder andere Velocity ändert diese Identität nicht.
Beide Stimmen können unabhängig denselben Inhalt mit derselben ID erfassen. Das ist
keine automatische gegenseitige Übernahme.

`sceneEndTime` ist im unbegrenzten Modus leer; die Verfügbarkeitsgrenze schaltet die
Motivplanung deshalb nicht ab. Alle sechs 512-Takt-Läufe behalten pro Stimme ein
Original. **Keine Ersetzung abgeschlossener Originale** in der Hauptmatrix. Auch die
Kontrolle mit 64-Takt-Szenenlänge erzeugt in allen drei Kontexten zunächst dieselben
Original-IDs wie ihr unbegrenztes Gegenstück. Erst Szenenende/Reset hat andere Folgen.
Normale XYZ-Änderungen löschen den Katalog nicht.

Eine wichtige Genauigkeitsgrenze: Score erfasst tatsächlich ausgegebene Tonhöhen und
Einsätze, aber die **geplante** Dauer der Note. Bei späterer monophoner Freigabe kann
sie länger gespeichert sein als die echte MIDI-Dauer. In den 24 Neutral-Hauptfällen
betreffen solche Abweichungen zehn eingeführte Noten; bei Barry/Pop hier keine. Beispiel
Neutral dunkel, Variation 1, Dialog: viermal MIDI 86, erste gespeicherte Dauer 2,25
Viertel, tatsächlich 2 Viertel bis zum erneuten Anschlag derselben Note. Pop-Aufnahme
berücksichtigt dagegen tatsächliche Freigaben. Kein Verlust des Speichers, aber eine
kleine Abweichung zwischen geplantem und tatsächlich erklungenem Rhythmusbild.

## 2. Tatsächliche Motivlängen und Tonhöhenvielfalt

`motifFor` (ScoreEngine.h:1022) wählt aus sieben Einsatzmustern und sechs Konturen;
`planMotifNote` (1383) übersetzt diese lokal in eine Akkordtonleiter. Je nach Intensität
werden drei bis fünf gedachte Anschläge auf weniger reduziert. Die einzelnen
Konturindizes werden begrenzt, nicht die ganze Kontur gemeinsam in eine geeignete Lage
verschoben. Dadurch können verschiedene geplante Stufen auf denselben Ton fallen.

| Kontext, je 24 Hauptläufe | Hauptmelodie: gespeicherte Anschläge | Dialog: gespeicherte Anschläge | Auffälligkeit |
|---|---|---|---|
| Neutral Score | 3: 2 Fälle; 4: 10; 5: 12 | ebenso | Ein Dialogoriginal besitzt vier Anschläge, aber nur eine Tonhöhe |
| Barry Score | 4: 13; 5: 5; 7: 1; 8: 5 | 3: 2; 4: 14; 5: 3; 7: 2; 8: 3 | Acht Hauptmelodieoriginale und zwölf Dialogoriginale besitzen nur zwei Tonhöhen |
| Pop/Rock | 3: 2; 4: 10; 5: 12 | 6: 1; 8: 23 | Drei Hauptmelodieoriginale besitzen nur eine Tonhöhe; Dialogaufnahme oft motorischer Hook |

Generische Score-Gedanken belegen hier bis zu zwei Takte, teilweise mit langem letzten
Ton. Acht Barry-Anschläge können nur einen Takt lang sein. **Anschlagszahl ist keine
Phrasenlänge und keine Qualitätsskala.** Zwei gute Töne können ein starkes Motiv sein;
eine kaum variierte Viertelrepetition ist aber noch keine längere Melodielinie.

Das Speichermaximum acht Noten und das abgeleitete Maximum zehn Noten begrenzen die
aktuelle Motivarchitektur. Längere freie Ausgaben können durch Aneinanderreihung entstehen,
werden aber dadurch nicht zu einem vorausgeplanten Bogen mit Zielton und Kadenz.

## 3. Einführung, Wiederkehr, Varianten und Verwerfungen

`motifOccurrence` (ScoreEngine.h:1185), `recurrenceSlot` / `planRecurrence`
(CompositionCore.h:294/320), `MotifRecurrencePolicy` (CompositionPolicy.h:29).

Die Einführung liegt im ersten geeigneten, höchstens zweitäktigen
Fenster einer Phrase. Die Stimme kann später beginnen, wenn Rollen oder Harmonik den
ersten Versuch verhindern. Nach abgeschlossener Aufnahme läuft die Wiederkehr relativ
zum eigenen Einführungszeitpunkt in **achtaktigen Planungshorizonten**. Es gibt innerhalb
dieser Horizonte flexible harmonische Einsatzstellen; die Planung ist dennoch nicht
vollständig von diesem Raster gelöst.

Normale berechtigte Horizonte folgen dem Abstandsmuster 1/2/1 × acht Takte, ruhige
Kontexte 2/2/2 × acht Takte. Mindestens zwei stille Takte werden für vollständige
Wiederkehr berücksichtigt; Antworten brauchen zusätzlichen Platz. Harmonieprüfung,
Register und Rollenfenster können weitere Gelegenheiten verwerfen. Ein abgelehnter
Plan bleibt im jeweiligen Cachehorizont abgelehnt. Eine neue passende Harmonie innerhalb
dieses Horizonts löst nicht automatisch eine neue Prüfung aus.

| Kontext, beide Stimmen zusammen, 24 Hauptläufe | Gehörte Rückkehrfiguren | vollständig ausgeführte Figuren | Original / Rhythmus / Fragment / Sequenz / Augmentation | Abgelehnte berechtigte Cachehorizonte |
|---|---:|---:|---|---:|
| Neutral Score | 370 | 368 | 254 / 46 / 56 / 6 / 8 | 51 |
| Barry Score | 403 | 403 | 224 / 83 / 44 / 18 / 34 | 13 |
| Pop/Rock | 247 | 228 | 161 / 29 / 40 / 12 / 5 | 0 |

Dies sind tatsächliche Noten in Rückkehrfenstern, **keine Wahrscheinlichkeitsschätzung**.
Vollständig bedeutet: alle Töne der gewählten Figur; ein vollständiges Fragment bleibt
kürzer als das Original. Pop-Teilausführungen sind insbesondere beim Wechsel zwischen
motorischem und phrasenbezogenem Hookgebrauch zu untersuchen, nicht als genereller
Scheduler-Ausfall zu deuten. Motorische Neu-Erzeugung zählt in dieser Tabelle nicht als
Rückkehr gespeicherten Materials. Explizite Dialogantworten sind separat erfasst.

Von 48 ersten tatsächlich gespielten Neutral-Rückkehren waren nur 32 nominell Original,
elf bereits rhythmisch verändert, vier fragmentiert und eine augmentiert. Auch
„Original“ kann harmonisch angepasst sein. Das Variationsordinal wird aus dem
Gelegenheitshorizont ermittelt, nicht aus bisher erfolgreich gehörten Wiederholungen.
Das schwächt das musikalische Einprägen, obwohl die Herkunfts-ID unverändert bleibt.

### Typische Aktivität – kein musikalisches Abnahmeziel

Median der Note-ons je Stimme in 128 Takten. Statisch umfasst 18 Läufe, jede Fahrt drei.
Die maximale Stille ist jeweils der schlechteste Wert einer einzelnen Hauptmelodie
innerhalb der jeweiligen Gruppe, nicht die gemeinsame Stille beider Stimmen.

| Kontext | Statisch Melodie / Dialog | Langsame Fahrt M / D | Schnelle Fahrt M / D | Längste Melodiestille statisch / langsam / schnell |
|---|---:|---:|---:|---|
| Neutral Score | 46 / 45,5 | 49 / 37 | 52 / 38 | 252 / 52,8 / 52,8 s |
| Barry Score | 47 / 62,5 | 47 / 56 | 47 / 77 | 36,6 / 74,4 / 79,2 s |
| Pop/Rock | 43 / 436 | 45 / 420 | 38 / 394 | 93,3 / 52,8 / 72 s |

Die höhere Präsenz der Gegenstimme ist bei Pop besonders deutlich und konzeptionell
mit ihrer Hookfunktion verbunden. Bei Barry trägt auch der große Anteil vierteiliger
Unisono-/Quintzellen dazu bei, dass trotz verlässlicher Wiederkehr wenig Melodiebogen
entsteht. Eine starre Quote höherer Notenzahlen wäre keine passende Antwort.

## 4. Konkrete musikalische Beispiele

MIDI-Nummern sind eindeutig; Tonbezeichnungen hier mit C4 = MIDI 60.
Zeitpositionen innerhalb des Gedankens in Viertelnoten ab 0. Takte im Hörpaket ab 1.
Alle Beispiele entstammen ungekürzten tatsächlichen 128-Takt-Ausgaben.

### A. Neutral: echter fünftöniger Gedanke, aber späte Wiederkehr

Hördatei 01, XYZ 0,25/0,85/0,65, Variation 1.
Original-ID `4390449307237864383`, Hauptmelodie:

| Position | MIDI / Ton | Dauer in Vierteln |
|---:|---|---:|
| 0 | 77 / F5 | 2 |
| 2 | 74 / D5 | 1 |
| 3 | 69 / A4 | 0,5 |
| 3,5 | 77 / F5 | 0,5 |
| 4 | 80 / As5 | 4 |

Das Original enthält vier Tonhöhen und eine markante lange Schlussnote. Seine
Wiederkehr beginnt in den Takten **25, 33, 45, 57, 65, 73, 89, 97, 109, 121**.
Intervalle zwischen gehörten Rückkehren: 8–16 Takte. Der Dialog hat einen eigenen
Gedanken, eigene Pausen und eigene Wiederkehr; dies ist kein durchgehendes gemeinsames
Thema. Akkordkontexte und reale transponierte Rückkehrnoten stehen im CSV/JSON des Pakets.

### B. Neutral: harmonisch spezifischer erster Gedanke bleibt lange gestrandet

Hördatei 02, XYZ 0,85/0,85/0,30, Variation 3.
Original-ID `6913414142713153477`, Einführung über **W1046, A°7**:

`C5 – Es5 – A4 – C5 – Fis5` = MIDI `72,75,69,72,78`.
Einsätze **0; 2; 3; 3,5; 4**,
Dauern `2; 1; 0,5; 0,5; 4` Viertel. Zwei Takte Gesamtausdehnung.

Der verminderte Klang prägt die Intervallstruktur mit einer Tritonusbewegung. Die
nachfolgenden ausgewählten Wendungen enthalten überwiegend andere Klangtypen. Die
begrenzte Anpassung schützt Richtung und stärkstes Intervall; dadurch passt das
Original selten vollständig. Erste tatsächlich gespielte Rückkehr **Takt 108**,
also 4:16,8 nach Beginn. Dazwischen längste Hauptmelodiestille **252 Sekunden**.
Auch diese Wiederkehr ist bereits angepasst: letzter relativer Abstand +7 statt +6.
Der Dialog spielt im selben Lauf 55 Noten; es handelt sich nicht um eine globale
Transport- oder Speicherblockade.

Statisches XYZ bedeutet hier nicht statische Harmonie: Variety 0,5 lässt weiterhin
unterschiedliche Wendungen zu. Die ursprüngliche Prägung bleibt jedoch lange dieselbe.
Dies ist ein konkreter Beleg für ein musikalisch wenig hilfreiches Gedächtnisverhalten.

### C. Barry: nachweisbare Vorlage und echte kurze Antwort

Hördatei 04, XYZ 0,25/0,85/0,65, Variation 1.
`JB-M22 „Massiver Unisono-Schlag“`, ID `6005005923726776492`:

- Hauptmelodie Takt 1 über **W30020, D-Moll**: `D4–D4–A4–D4`, MIDI
  `62,62,69,62`, vier Viertel, Einsätze 0/1/2/3. Kein längerer Melodiebogen.
- Wiederkehr Takt 9 unverändert; Takt 25 verkürzt nur die erste Note auf eine Achtel,
  alle Einsätze bleiben gleich. Takt 46 verwendet die Schlussfigur `D–A–D`.
- Die Sequenz Takt 81 der eigenen Dialogwiederkehr wird aus den ersten beiden
  wiederholten Tönen abgeleitet: rhythmisch verwandt, aber musikalisch schwächer als
  die charakteristische Quintfigur. Ein korrekt ausgeführtes Verfahren entwickelt
  also nicht zwangsläufig das charakteristischste Merkmal.
- Der Dialog nimmt unabhängig ein eigenes `D3–D3–A3–D3` auf. Gleiche Identität,
  andere Aufnahme, Referenz und Fortschritt.
- **Explizite** Übernahme der Melodiereferenz in den Takten **18, 50, 82, 114**.
  Tatsächliche erste Antwort: MIDI `62,69,62` = `D4–A4–D4`, je eine Viertel.
  Die Antwort ist die dreitönige Schlussfigur der wirklich eingeführten Melodie.
  Sie liegt im vorgesehenen ruhigen Antwortfenster, nicht über einer führenden Phrase.

Diese Übergabe funktioniert technisch und strukturell. Sie ist bewusst selten und
macht aus zwei eigenständigen Stimmen noch keinen mehrtaktigen Frage-Antwort-Bogen.

### D. Barry: mehr Töne sind möglich, Register und Abstand bleiben entscheidend

Hördatei 05, dunkel, Variation 1: `JB-M15`, tatsächlich
`D4–A4–D5–A4–D4`, MIDI `62,69,74,69,62`, Einsätze 0/1/2/4/6,
Dauern 1/1/2/2/2 Viertel. Zwei Takte mit Aufstieg und Rückkehr, erste Reprise Takt 9.
Beide Stimmen beginnen in diesem Fall in derselben Lage. Die ganze Zelle muss ins
Hauptmelodieregister 60–84 passen; die bevorzugte Oktavierung wird gegebenenfalls
zurückgenommen. Mit nur im Test erweitertem Register 60–96 liegt die Hauptmelodie
zwölf Halbtöne höher, ohne neue Noten oder andere Motivfunktion. Das illustriert eine
Registerbegrenzung; es ist keine Empfehlung, externe Patches ungeprüft zu erweitern.

Hördatei 06, langsame XYZ-Fahrt: `JB-M07` über W30035, **Dm(maj7)**:
`A4–D5–Cis5–D5–A4–D5–Cis5–D5`, MIDI `69,74,73,74,69,74,73,74`.
Acht Achtel, nur drei verschiedene Tonhöhen, Original-ID `4227336714085171529`.
Erste Reprise Takt 33, danach 57, 89 (Augmentation) und 107 (rhythmisch verändert).
In 512 Takten derselben Fahrt bleibt das Original erhalten, wird 16-mal wiederaufgenommen,
und die Hauptmelodie schweigt maximal 132 Sekunden zusammenhängend.
Die charakteristische Zelle wird tatsächlich ausgegeben; ihre sparsame Verwendung und
harmonische Spezialisierung sind das Problem, nicht fehlende Anbindung der Barry-Daten.

### E. Pop: gespeicherter Hook und laufender Hook sind zu unterscheiden

Hördatei 08, XYZ 0,88/0,48/0,03, Variation 1: Bei Variety 0,5 werden u.a.
W2018/2019/2026/2035 gewählt; die XYZ-Position erzwingt keine einzelne Wendung.
Aufgenommener Dialoghook: MIDI `72,72,79,72,84,72,79,76`, Achtel-Einsätze
0/0,5/1/1,5/2/2,5/3/3,5. Charakteristische Folge: `C5,C5,G5,C5,C6,C5,G5,E5`.

Es erklingen 208 Dialog-Note-ons, aber nur vier tatsächlich ausgeführte gespeicherte
Rückkehrpläne. Zwischenzeitlich wird der Hook aus aktueller Harmonie neu erzeugt.
Die erste gespeicherte Rückkehr liegt 44 Takte nach seiner Einführung. Ein Hörer kann
rhythmische Verwandtschaft wahrnehmen, ohne dieselbe Tonfigur wiederzuerkennen.
In den schnellen Pop-Hauptfahrten sind von 16 Rückkehrfiguren des Dialogs nur eine
vollständig ausgeführt; die übrigen werden beim wechselnden Verwendungskontext nur
teilweise hörbar. Das verlangt eine gezielte Anschlussuntersuchung der Hook-Übergänge,
keine pauschale Einführung von Score-Pausen in kontinuierliche Ostinati.

## 5. Harmoniebezug und Transformationen unter XYZ-Bewegung

### Konkreter Planwiderspruch, nicht nur subjektiv „zu viel Variation“

`motifHarmonyAt` (ScoreEngine.h:1085) setzt die aktuelle Wendung für die Vorhersage
an den Phrasenanfang. `locate` (1686) benutzt dagegen den tatsächlichen Wendungseintritt
`max(wendungTime, phraseStart)`. Nach einem Wechsel innerhalb einer Phrase können beide
verschiedene Akkorde für denselben Zeitpunkt liefern.

Zusätzlich prüft der Rückkehrcache (1204) Epoche, Material-ID, Einführungszeit und
Fensterlänge, aber nicht Wendungseintritt oder harmonischen Kontext. Eine inzwischen
unpassende erfolgreiche oder gescheiterte Planung bleibt deshalb erhalten.

**Beleg in Hördatei 03:** Hauptmelodieplan für Tick 414720 (Takt 109, 4:19,2) wird
bei beobachtetem Tick 399377 unter W1017 aufgebaut. Bei tatsächlicher Ausführung gilt
W1012, Grundakkord **D-Dur**. Die Hauptmelodie spielt als ersten Ton **MIDI 70 / B4
(deutsch B, international Bb4)**. Die Vorhersagefunktion meldet zur selben Zeit einen
anderen Grundton: relativ 6, also As statt D. Der alte Plan verwendet weiterhin
Grundlage 70. Die folgenden Töne sind `65,62,70,74`, Einsätze 2/3/3,5/4 Viertel.

Die erlaubte automatische Färbung von D-Dur zu Dmaj7 erklärt diesen ersten B-Ton
nicht; Passing ist in diesem Test AUS. Hier ist also nicht bloß eine bewusst geplante
melodische Durchgangsnote mit Zielauflösung dokumentiert. Harmonie selbst wird korrekt
weitergeführt, der Motivplan passt zeitlich nicht zuverlässig dazu.

In den statischen Hauptfällen wurde kein Rückkehrbeginn außerhalb der definierten
Grundakkordtonklassen gezählt. Unter Bewegung kommen solche Töne vor. Die JSON-Zahl
`off_chord_onsets` ist **nur ein Diagnoseindikator**: Sie zählt gegen den Grundakkord,
nicht sämtliche zulässigen Färbungen, und beweist für sich keine musikalisch falsche
Note. Der obige Einzelfall wurde separat auf automatische Färbung geprüft.

### Welche Identität wird geschützt?

`deriveMotif` (CompositionCore.h:91):
- Rhythmus: gezielte Gate-Verkürzung, unveränderte Einsatzzeiten.
- Fragment: letztes Zwei-/Dreitonsegment; der Anfang wird bewusst nicht bewahrt.
- Sequenz: erste zwei Noten plus versetzte Wiederholung, nicht notwendig die
  charakteristischsten zwei Noten des ganzen Gedankens.
- Augmentation: doppelte Einsätze und Dauern; kann durch verfügbare Harmonie/Fenster scheitern.

`realizeScoreMotif` (138) begrenzt Einzeltonanpassungen, erhält Bewegungsrichtung und
stärkstes benachbartes Intervall; Dauern können an geeigneten Grenzen gekürzt werden.
Das ist keine wahllose gleichzeitige Mutation. Es schützt aber auch eine harmonisch
sehr spezielle Tritonusfigur so stark, dass sie über viele Folgewendungen nicht passt.
Umgekehrt ändern manche „Original“-Rückkehren ihre relativen Intervalle: in der
Hauptmatrix Neutral 103 solcher gehörten Figuren, Barry 20, Pop 49. Diese Zahlen
bedeuten nicht automatisch Unkenntlichkeit; hörbare Wirkung hängt von der Zelle ab.

**Eine stabile Quellen-ID besagt ausschließlich „aus demselben Original abgeleitet“.**
Sie misst weder Wahrnehmbarkeit noch gleiche Kontur. Das ist bei künftigen Tests getrennt
zu bewerten: tatsächliche Intervallfolge, Einsatzfolge, charakteristische Zelle, Kontext.

## 6. Frage–Antwort und unterschiedliche Rollen

`playableMelodyHandoff` (ScoreEngine.h:2880), `planMelodyHandoff`
(CompositionCore.h:432), `melodicRoleWindow` (ScoreEngine.h:1565).

Explizite Melodie→Dialog-Antworten benötigen Score, 4/4, Aufbau AUS, beide Stimmen
und Motivfunktionen geeignet/aktiv, getrennte nutzbare Kanäle und mindestens vier
Phrasentakte. Nur ein ausgewählter ruhiger Horizont pro Vierergruppe kommt infrage,
also ungefähr ein Angebot pro 32 Takte, das auch entfallen kann. Die Schlussfigur muss
harmonisch und hinsichtlich des Registers passen. Unter den 24 Hauptläufen gab es
3 reale Referenzübernahmen bei Neutral und 75 bei Barry. Das sind keine dauernden
Dialoge. Einzelne Übernahmen wurden mit den echten Antwortnoten abgeglichen (Beispiel C).

Pop besitzt diese explizite Melodie→Dialog-Übernahme nicht; dort wechseln priorisierte
Melodie- und Hookfenster. Eine ausbleibende gemeinsame Themenentwicklung ist damit
teilweise eine fehlende Fähigkeit und kein ausgefallener vorhandener Plan.

Die Rollenkoordination verhindert absichtlich konkurrierende Vordergrundstimmen.
Aus eigenständigen Stimmen mit disjunkten Fenstern entsteht aber nicht automatisch
musikalisch aufeinander bezogenes Fragen und Antworten. Auch dieselbe unabhängig
gebildete M22-Zelle beider Stimmen ersetzt keine geplante Entwicklung.

## 7. Barry-Vokabular: Anbindung vorhanden, Themenentwicklung begrenzt

`authoredMotif` (ScoreEngine.h:1311),
[data/barry/vocabulary.json](../../data/barry/vocabulary.json),
kanonische Forschung unter [docs/research](../research/).

26 kanonische Motivdatensätze, davon 20 aktiviert; sechs begründet zurückgestellt.
Die aktiven Zellen werden nach XYZ-Nähe und vollständiger Spielbarkeit gewählt, nicht
aufgrund einer bloßen Profilbezeichnung. In den Hauptläufen wurden tatsächlich
**JB-M07, M08, M12, M15, M22, M23 und M24** erfasst. Die Beschränkung auf sieben
in dieser Matrix ist kein Nachweis, dass die übrigen dreizehn nie erreichbar wären.
Der erste spielbare Gedanke wird festgehalten; spätere XYZ-Bereiche wählen kein neues
Original. Darum entsteht bei einer langen Feldfahrt kein Durchlauf durch die Bibliothek.

Ein Barry-Original kann innerhalb einer Lage sehr wirksam sein, bleibt hier aber eine
kurze Zelle. Black-Hole-/dramatische Wiederholungszellen und massive Unisonoschläge
sind nicht automatisch geeignete längere Hauptmelodiephrasen. Die Forschung unterscheidet
belegte Stilmerkmale und konstruierte Vorlagen; deren Kennzeichnungen bleiben erhalten.

## 8. Längere Phrasen und Entwicklung in Richtung eines Williams-Profils

`freeLinePhrase` (ScoreEngine.h:3522) und `planLinePhrase` (CompositionCore.h:474)
kennen Zielton, Kontur, Schlussbewegung und Atemstelle. Diese Fähigkeit greift aber nur
bei geeigneter **freier Gegenstimme mit Motiv AUS**. Motiv EIN aktiviert also nicht
„freie Phrase plus Gedächtnis“, sondern einen anderen Produktionspfad. Die Hauptmelodie
hat weder diese gemeinsame Zielplanung noch eine mehrteilige Motivausarbeitung.

Für längere thematische Gedanken fehlen insbesondere:

- Verbindung einer erkennbaren Anfangszelle mit geplantem Ziel, harmonischen
  Zwischenstationen, Fortspinnung und Schluss; offene/geschlossene Antworten.
- Mehr als ein musikalisch kuratierter Gedanke pro Stimme sowie gezielte
  Wiedereinführung nach Kontrast, statt dauerhafter Bindung ans erste Original.
- Bewertung, **welcher** Teil eines Motivs charakteristisch ist; heutige Fragment-
  und Sequenzbildung arbeitet mit festen Anfangs-/Endpositionen.
- Geplante Score-Nichtakkordtöne und deren Auflösung über mehrere Noten, anstatt
  überwiegend vollständige Akkordtonverträglichkeit ganzer Gates zu verlangen.
- Registerplanung der ganzen Linie, statt lokales Zusammenfallen verschiedener Stufen.
- Entwicklungsentscheidungen nach tatsächlich erklungenen vollständigen Gedanken,
  nicht nur nach verstrichenen Planungsfenstern.

Das sind technische musikalische Voraussetzungen für spätere längere Themen, **keine
bereits abgesicherte John-Williams-Stilgrammatik**. Eine entsprechende kanonische
Williams-Untersuchung liegt hier nicht vor. Kein Anlass für eine neue universelle Engine.

## 9. Empfehlung: kleinster musikalisch wirksamer Folgeschritt

**Zunächst den nachgewiesenen Harmoniebezug des bestehenden Motivplans gezielt absichern;
anschließend eine einzige frühe, vollständige Anker-Reprise vor der ersten Variation.**
Nicht die Begleitung ändern, keine permanent höhere Lead-Aktivität und keine neue Formengine.

1. Enger Korrekturschritt: Motivprüfung und echte Ausführung auf dieselbe bereits
   vorhandene harmonische Zeitleiste beziehen. Bei verändertem Wendungseintritt nur
   noch nicht begonnene Rückkehrpläne prüfen; laufende Gedanken nicht auf jedem
   XYZ-Update zerlegen. Konkreten Fall Takt 109 als Regression verwenden. Harmonie-
   und Begleitereignisse selbst müssen bytegleich bleiben.
2. Kleiner musikalischer Schritt: Nach Einführung genau eine möglichst vollständige,
   noch nicht rhythmisch/fragmentarisch veränderte Reprise bevorzugen, bevor das
   bestehende Variationsprogramm beginnt. Mindestens vorhandene zwei stille Takte,
   tatsächliche Harmonie-/Registereignung und Rollenfenster einhalten. Bei fehlender
   Eignung auslassen oder verschieben; keine Zwangsnoten.
3. Reprise darf innerhalb eines geeigneten bisherigen Horizonts liegen und muss nicht
   erst den nächsten achtaktigen Horizont abwarten. Beispiel B hätte analytisch eine
   verwandte verminderte Harmonie in Takt 5/6, nach einer vollständigen Zweitaktpause;
   die exakte transponierte Kontur könnte dort passen. **Dies ist ein Vorschlag,
   keine bereits erzeugte neue MIDI-Ausgabe.**

Warum zuerst dies: Ein Original muss sich einprägen können, bevor kleine Abwandlungen
als Wiederkehr erkannt werden. Der Eingriff stärkt Zusammenhang, ohne lange Dauersoli
oder neue Motivgeneratoren zu benötigen. Er löst noch nicht die fehlende Langphrase.

Konkrete Abnahmekriterien für einen später autorisierten Auftrag:
- Tatsächliche Einführung und mindestens eine vollständige erkennbare Rückkehr in
  geeigneten Testharmonien; Original unbeschädigt, charakteristische Intervalle und
  Einsätze erhalten. Keine bloße Quellen-ID-Prüfung.
- Keine Variation vor der ersten gehörten Reprise; gescheiterte Gelegenheiten dürfen
  nicht heimlich den Entwicklungsschritt weiterschalten.
- Echte Pause, keine konkurrierenden Vordergrundfenster, keine unpassenden Töne bei
  XYZ-Wechseln; unbegrenzte Wiedergabe und Motivschalter beider Stimmen unabhängig.
- Die bekannten stillen Situationen bleiben zulässig; keine globale Notenquote.
- Harmonie, Bass, Fläche, Arpeggio und Akzente unverändert; Pop-Motorik schützen.
- Konkrete Vorher/Nachher-Hörabnahme derselben MIDI-Szenen.

Danach getrennt prüfen: ganze Konturen registergerecht platzieren, statt Einzeltöne
zusammenzuschieben; geplante Gate-Dauern und echte Aufnahme konsistent machen; schließlich
Zielton-/Atemplanung mit Motivgebrauch verbinden. Das sind keine jetzt ausgeführten Schritte.

## Abschluss und Grenzen

Die Untersuchung bestätigt sowohl funktionierende Originalwiederkehr als auch konkrete
musikalische Schwächen und einen harmonischen Planwiderspruch unter Bewegung. Sie erklärt
nicht jede subjektive Hörsituation: Patchansprache, Lautstärke, Artikulation und Maskierung
wurden nicht akustisch gemessen. Daher sind Aussagen über Wiedererkennbarkeit begründete
strukturelle Bewertungen, noch keine endgültige Hörabnahme.

Keine Engine-/GUI-/Datenkatalogänderungen, kein Commit, kein Push, kein Release.
Der positiv abgenommene Begleitstand bleibt unangetastet. Nach dieser Dokumentation
keine eigenständige Implementierung oder weitere Entwicklung begonnen.
