# John Barry – Phase 3: rhythmisches und motivisches Vokabular

Ausgangspunkt `9b572b8`, Branch `develop/composition-core-prototype`, 25. November 2026. Diese Phase ergänzt den gemeinsamen Score-Barry-Pfad. Neutral, Herrmann, Pop/Rock, GUI, Harmoniekatalog und Profilgewichte werden nicht verändert.

## Hörbar wirksamer Umfang

**16 kanonische Rhythmusvorlagen** liefern echte Einsatz-, Akzent-, Halte- und Pausendaten für Bass und/oder Bewegung. **20 kurze Motivvorlagen** können die erste tatsächlich gespielte Geste von Melodie oder Dialog bilden. Die neue Bibliothek ist kein zweites Motivgedächtnis: Erst die ausgegebenen MIDI-Noten werden im vorhandenen gemeinsamen Katalog veröffentlicht. Wiederkehr, Rhythmusvariation, Fragment, Sequenz, Augmentation, harmonische Anpassung und explizite Antworten verwenden anschließend ausschließlich diesen gespeicherten Ursprung.

Die Hauptmelodie bleibt standardmäßig AUS. Profilwahl allein aktiviert keine neue Instrumentenrolle. Die bisherigen Motivschalter gelten unabhängig für Melodie und Dialog. Bei Motiv AUS bleiben deren vorhandene freie Linienpfade erhalten.

## Daten und musikalische Herkunft

Maßgeblich ist die bereinigte Gesamtfassung `shared/Musikalisches_Vokabular_Gesamtfassung_2026-11-24.txt`, zusammen mit dem Barry-Stilprofil. Originale und Archivfassungen werden nicht geändert; Archive liefern kein zusätzliches Material. `BH` bezeichnet in Forschungs-IDs Herrmann und wird nicht als Black-Hole-Material importiert. Die Rhythmus-Aliasse R16/R23 bleiben unter ihren kanonischen Formen R12/R21.

`scripts/build_barry_vocabulary.py` liest alle 25 kanonischen JB-R und 26 JB-M, prüft Rasterlängen, Taktart, Notenpositionen/-dauern, Reihenfolge, Grenzen und MIDI-Tonhöhen und erzeugt:

- `data/barry/vocabulary.json`: vollständiges Inventar einschließlich bewusst zurückgestellter Formen und Begründungen, XYZ, Meter, Quellenbezug und Evidenz.
- `Source/BarryVocabulary.generated.h`: ausschließlich die 16 bzw. 20 freigegebenen statischen Laufzeitvorlagen.

`--check` ist in CMake beim Konfigurieren und im Build angeschlossen. Abweichungen zwischen Forschung, JSON und Header verhindern den Build. UTF-8 wird ausdrücklich gelesen/geschrieben, einschließlich unter Windows. Im Audiothread finden keine Dateien, Parser oder Datenvalidierungen statt.

[N], [I], [H] bewerten die in der Forschung beschriebene Verfahren-Evidenz. **Sämtliche konkreten Rhythmen und Tonfolgen bleiben eigene Konstruktionen [E]**, auch bei einem Verfahren [N]. Keine Original-Cue-Transkription und keine neue unabhängige Quellenverifikation wird behauptet.

## Ein gemeinsamer musikalischer Zusammenhang

### Rhythmuswahl und Kontinuität

Beim Beginn einer Wendung beziehungsweise beim nächsten Phrasenbeginn wird eine passende R-Vorlage anhand des aktuellen XYZ gewählt. Ein kleiner gemeinsamer Cache hält diese Entscheidung bis zum nächsten musikalischen Neueinstieg fest. Bewegungen des XYZ steuern weiterhin Energie, Dynamik, Rollenaktivität und Harmonie, zerschneiden aber nicht laufend die gewählte Zelle. Bass und Bewegung greifen auf dieselbe Entscheidung zu; sie würfeln keine getrennten Muster. Bei unveränderter Wendung kann eine reine XYZ-Fahrt deshalb bis zum nächsten achtaktigen Phrasenbeginn brauchen, bevor eine andere R-Zelle gewählt wird. Das ist musikalische Musterstabilität, keine technische Startlatenz; Dynamik, Aktivität und die bestehenden Harmonieentscheidungen reagieren weiterhin nach ihren vorhandenen Regeln.

Die Auswahl verwendet die bestehende gewichtete XYZ-Metrik (X / 0,7Y / 0,8Z), bleibt aber auf einen redaktionell gesetzten Radius von **0,25** begrenzt. Das ist eine musikalische Schutzentscheidung, kein empirischer Stil-Messwert. Ohne ausreichend nahe R-Vorlage arbeitet die bereits vorhandene Barry-Auto-Begleitung weiter. Diese Begrenzung verhindert beispielsweise, dass ein entfernter Bossa-Entwurf den warmen, ruhigen Hörfall zu einem dauernden Synkopenbass macht.

Die metrischen Angaben werden respektiert: R04/R17/R26 nur in 3/4, R11 nur in 6/8, andere freigegebene R in 4/4. Der Host bestimmt Taktart und Tempo. Es gibt keine automatische Taktartumschaltung, Tempoänderung oder Skalierung eines 4/4-Rasters in einen anderen Takt.

`X`/`x` erzeugen Anschläge, `-` setzt die vorherige Note fort, `.` bedeutet Notenende/Pause. Großes X erhält einen kleinen Akzent; seine numerische Velocity-Stärke ist Engine-Ausgestaltung. Die Muster werden als vorhandene `RhythmPlan`-Ereignisse mit 960-PPQ-Ticks bereitgestellt, nicht durch einen neuen Scheduler. Das Arp verwendet die vorhandenen harmonisch passenden Figuren. Sein Figurenfortschritt wird aus den tatsächlichen Anschlägen der Zelle abgeleitet und nicht bei jedem Akkordwechsel neu zufällig versetzt.

R05 und R26 erlauben gezielt Sechzehntelverdichtung und sind damit eine ausdrücklich geplante Ausnahme vom Phase-2-Auto-Achtellimit. Ihr Fundament bleibt während der Zelle unverändert. Dafür müssen Akkorddauern und Zellengröße zusammenpassen; bei einem unpassend gelegenen untertaktigen Wendungsneustart wird diese statische Zelle nicht gewählt. R05 kann somit auch über einem Vier-Takt-Feld innerhalb eines langsamen Akkordpendels arbeiten, statt eine volle achtaktige Ein-Akkord-Wendung zu verlangen.

Ein kalter Seek erzeugt keine Zelle vor ihrem Szenen-/Harmonieeintritt. Die begrenzte Chase-Rekonstruktion verwendet dieselben vorhandenen Emittenten und gilt nur für bereits sinnvoll platzierte Zellereignisse. Die bekannte fehlende musikalische Vorgeschichte beim kalten Seek bleibt akzeptiert.

### Bass, Register und Spielweise

Die neue Basszelle gilt nur für Auto. Unter Bassintensität 0,30 bleibt die bisherige ruhige Bassentscheidung erhalten. Manuelle Muster, Szeneneinstieg-Overrides und vorhandene Ausdünnung behalten Vorrang. Die notierte Basstonklasse kommt weiterhin aus der aktuellen Harmonie einschließlich Slash-Vorgaben; Follow AUS behält seine vorhandene Tonikafunktion.

Längere Bassgates gehen an Bass Lang, kurze Impulse an Bass Kurz. Dauer, Spielweise, Rollenfähigkeit, Verfügbarkeit und Tonumfang werden vor Ausgabe mit dem vorhandenen Fähigkeitsmodell geprüft. Ungeeignete Verbindungen werden nicht still auf einen anderen Patch umgeleitet. Ein neuer Bassanschlag beendet alte Ansprüche dieser Bassrolle, sodass beim Wechsel von gehaltenem Fundament zu rhythmischer Figur keine zweite Basslage versehentlich stehen bleibt.

Arp-Daten gelten nur bei Auto-Figur **und** Auto-Tempo. Manuelle Figur/Rate behalten ihren bisherigen Pfad. Geteilte physische MIDI-Kanäle führen für diese neue Zweistimmen-Koordination zum bisherigen Verhalten. Stich wird nicht als gestimmte Pauke interpretiert. Die Fähigkeiten externer Patches bleiben unbekannt; es gibt keine neue Instrumentierungs- oder Keyswitch-Engine.

### Motive: ganze Gestalt prüfen, tatsächliche Gestalt merken

Eine Initialgeste wird nur gewählt, wenn ihr vollständiger kurzer Verlauf in der aktuellen und bereits geplanten Harmonik spielbar ist. Die Tonfolge wird als Ganzes transponiert und ins geeignete Register gelegt. Einzelne problematische Töne werden nicht beliebig auf Akkordtöne zurechtgebogen. Bei absehbarem Konflikt entfällt diese Vorlage; der vorhandene gemeinsame Pfad kann eine geeignete freie Anfangsgeste liefern.

Das erlaubt auch chromatische Motivzellen, wenn ihre Töne tatsächlich durch den Klang getragen werden: etwa H–C über Moll-Major oder Maj7. Es ist **keine** allgemeine Freigabe chromatischer Nicht-Akkordtöne. Manche in der Forschung als Nicht-Akkordtonform beschriebene Motive werden deshalb nur in einer anderen passenden Harmonisierung zugelassen. Beispielsweise ist der D-Ton von M03 im Moll-Major-Nonenfeld ein definierter Klangton; M10/M20 funktionieren vollständig in einem add9-Kontext.

Die Anfangswahl folgt XYZ und harmonischer Eignung. Nach dem ersten wirklich ausgegebenen Ton wird die gewählte Quellfigur für diese Aufnahme festgehalten. Bei späteren unvorhersehbaren Harmonieänderungen wird der noch nicht gespielte Teil erneut geprüft; bereits gehörtes Material wird nicht umgeschrieben oder mit einer neuen Zufallsfigur zusammengeklebt.

`RememberedMotif.vocabularyId` enthält ausschließlich optionale Herkunft. Die musikalische Identität wird weiter aus tatsächlich ausgegebenen Intervallen, relativen Tick-Positionen, Dauern und Zykluslänge gebildet. Tonhöhen und Artikulation des gehörten Materials werden aufgezeichnet. Die Anschlagsabsicht bleibt wie im gemeinsamen Score-Pfad gespeichert; aktuelle Dynamik wird bei der Ausgabe angewendet und nicht versehentlich doppelt eingerechnet. Ein später Einstieg mitten in eine Zelle speichert die gehörte Teilfolge mit korrektem Bezug, ohne den ersten gehörten Ton fälschlich als ersten Ton der Vorlage zu behandeln.

Legato AUS verkürzt Gates über die vorhandene Artikulationsfunktion, Legato EIN erhält die notierten Haltewerte und ausdrücklich notierte Pausen. Die beiden Stimmen behalten unabhängige Zustände und Cursor. Es gibt keine automatische Übernahme aus dem Material der anderen Stimme. Ihre gemeinsame Rollenplanung und die vorhandenen Auto-Arp-Reservierungen bleiben maßgeblich: Eine spielbare Vordergrundfigur kann dem automatischen Arp Platz abverlangen; Antworten und ruhige Zwischenräume bleiben erhalten.

### Nachgewiesene Loop-Korrektur im neuen Vorlagenpfad

Eine zusätzliche Rücksprungprüfung hat bei M19 einen Fehler des neuen Pfads aufgedeckt: Nach der Einführung von MIDI **60–67–72–76–74–72** wurde die gelernte Figur beim Rücksprung durch die bisherige lokale Akkordtonleiter auf **67–74–79–84–79–79** umgebogen. Bei einer bereits eingeführten kanonischen Gestalt wird nun ihre tatsächliche Lage wiederverwendet und erneut auf harmonische Eignung und Register geprüft. Ungeeignete Wiederholungen entfallen.

Die bei der Aufnahme aktive Artikulation wird als Aufführungsmetadatum gespeichert (`legatoAtCapture`), getrennt von der musikalischen Identität. Bereits verkürzte Gates werden bei unveränderter Artikulation nicht nochmals verkürzt. Ein Regressionstest vergleicht Tonhöhen, Einsätze, Dauern und Anschlagsstärken vor/nach dem Rücksprung für Melodie und Dialog mit Legato EIN/AUS. Beide Stimmen besitzen weiterhin ihre eigenen Zustände. Diese Korrektur betrifft ausschließlich neu eingeführtes Barry-Vorlagenmaterial; das bisherige Material ohne Herkunfts-ID bleibt unverändert.

## The Black Hole und A View to a Kill

- **Black Hole:** R04 liefert den sechsachteligen 3/4-Schwung; R26 verdichtet die Oberbewegung im zweiten Takt zu zwölf Sechzehnteln über gehaltenem Bass. M17 ist eine kurze kreisende 3/4-Geste und kann über geeignetem Moll-Major-Feld mit H–C-Farbe erklingen. R05/M07 ergänzen verwandte Diminutions-/Kurzgesten in 4/4. Weder genaue Originalnoten noch Blaster-Beam-Instrumentierung werden rekonstruiert.
- **A View to a Kill:** Die synkopierten R14-/R20-Kontexte, kurze Zeichen und deren gemeinsame Wiederkehr liefern eine erste dunkle Motorik-/Gegenspielerfacette. M11 ist ein eigener, hypothetischer Dreitonentwurf und wird nur in passender Tonhöhenstruktur ausgegeben. Das tatsächliche Zorin-Motiv ist weiterhin unbekannt. **M26 bleibt zurückgestellt**, weil seine explizite obere/untere Umspielung eine noch nicht vorhandene kontrollierte Nicht-Akkordtonrealisierung benötigt. Die warme Seite bleibt durch die bestehenden add9/Maj7-Harmonien und spielbare M08/M10/M19/M20 zugänglich.

## Vollständiges Vorlageninventar

„Aktiv“ bedeutet: Datenpfad und vollständige Ausführung vorhanden, unter Prüfung von Kontext, Taktart, Rollen und Schaltern. Es bedeutet nicht, dass jede Vorlage bei jedem XYZ oder im automatischen Standardkatalog an ihrem eigenen Anker gewählt wird. Ungeeignete Kombinationen dürfen ausdrücklich aussetzen.

### Rhythmus: alle 25 kanonischen Formen

| ID | Name | XYZ | Evidenz | Status |
|---|---|---|---|---|
| JB-R01 | Halbe-Note-Bass | 0.45 / 0.15 / 0.1 | [I], Raster [E] | Aktiv: bass |
| JB-R02 | Viertel-Puls mit Akzent | 0.4 / 0.4 / 0.3 | [I], Raster [E] | Aktiv: bass |
| JB-R03 | Achtel-Ostinato (Barry: Pendel-Ostinato, Herrmann: Staccato-Repetition) | 0.35 / 0.55 / 0.5 | [N], Raster [E] | Aktiv: movement |
| JB-R04 | 3/4-Schwung (Black Hole) | 0.3 / 0.55 / 0.5 | [N], Raster [E] | Aktiv: movement |
| JB-R05 | Diminution der Oberfigur | 0.3 / 0.75 / 0.7 | [N], Raster [E] | Aktiv: bass, movement |
| JB-R06 | A-A-B-Phrase | 0.45 / 0.35 / 0.3 | [N], Raster [E] | Zurückgestellt: A-A-B form planning |
| JB-R07 | Stille vor Aktion | 0.4 / 0.2 / 0.35 | [N], Raster [E] | Zurückgestellt: Whole-texture silence, not only one muted part |
| JB-R08 | Zeitlupen-Aktion | 0.3 / 0.5 / 0.55 | [N], Raster [E] | Aktiv: bass, movement |
| JB-R09 | Pauken-Marsch | 0.5 / 0.65 / 0.4 | [N], Raster [E] | Zurückgestellt: Tuned percussion plus chordal role not identified by MIDI patches |
| JB-R10 | Bossa-Synkope | 0.55 / 0.3 / 0.25 | [H], Raster [E] | Aktiv: bass |
| JB-R11 | Wiege 6/8 | 0.6 / 0.15 / 0.1 | [I], Raster [E] | Aktiv: bass |
| JB-R12 | Gehaltene Ganze (ruhend oder anschwellend) | 0.5 / 0.1 / 0.1 | [I], Raster [E] | Zurückgestellt: Held pad exists; exact two-bar retrigger/envelope not imported |
| JB-R13 | Achtel-Drive | 0.4 / 0.8 / 0.7 | [I], Raster [E] | Aktiv: movement |
| JB-R14 | Bond-Synkope | 0.35 / 0.6 / 0.5 | [I], Raster [E] | Aktiv: movement |
| JB-R15 | Sechzehntel-Teppich (Barry: Motor, Herrmann: Tremolo) | 0.3 / 0.9 / 0.8 | [H], Raster [E] | Zurückgestellt: Dense hypothetical motor deferred for underscoring |
| JB-R17 | 3/4-Bass ruhig (1–2) | 0.65 / 0.2 / 0.1 | [I], Raster [E] | Aktiv: bass |
| JB-R18 | Off-Beat-Ostinato | 0.5 / 0.55 / 0.5 | [I], Raster [E] | Aktiv: movement |
| JB-R19 | Ausdünnung | 0.4 / 0.4 / 0.3 | [I], Raster [E] | Zurückgestellt: Whole-texture eight-stage density procedure |
| JB-R20 | Zweitakt-Stau mit Auftakt | 0.45 / 0.7 / 0.6 | [I], Raster [E] | Aktiv: movement |
| JB-R21 | Flirren / Schimmer (gleichmäßiger Achtel-Teppich) | 0.2 / 0.2 / 0.65 | [H], Raster [E] | Zurückgestellt: Pad/reinstrumentation role, not an Arp substitute |
| JB-R22 | Wucht-Viertel | 0.2 / 0.85 / 0.3 | [H], Raster [E] | Aktiv: bass |
| JB-R24 | Triumph-Marsch | 0.9 / 0.85 / 0.3 | [H], Raster [E] | Aktiv: bass |
| JB-R25 | Helle Hetzjagd | 0.85 / 0.9 / 0.8 | [H], Raster [E] | Zurückgestellt: Dense hypothetical motor deferred for underscoring |
| JB-R26 | 3/4-Wirbel mit Diminution | 0.3 / 0.65 / 0.55 | [I], Raster [E] | Aktiv: bass, movement |
| JB-R27 | Unruhe-Tupfer | 0.25 / 0.2 / 0.75 | [H], Raster [E] | Zurückgestellt: Accent-role plan outside this two-part step |

R12 bezeichnet eine bereits grundsätzlich vorhandene Fähigkeit; exaktes zweittaktiges Retrigger-/Dynamikverhalten wird hier nicht als neu importiert behauptet. R15/R25 wären als nacktes Einsatzraster technisch darstellbar, bleiben aber musikalisch bewusst zurückgestellt: Ein dauerhafter hypothetischer Sechzehntelteppich ist kein notwendiger erster Underscoring-Baustein. R05/R26 verdichten dagegen gezielt nur einen Teil ihrer Zelle. Die weiteren zurückgestellten Formen verlangen Form-/Gesamttextur-, zusätzliche Akkordrollen- oder Akzentplanung, die dieser Schritt nicht vorwegnimmt.

### Motivik: alle 26 kurzen Grundformen

| ID | Name | XYZ | Evidenz | Status |
|---|---|---|---|---|
| JB-M01 | Spinnender Moll-Dur-Aufstieg | 0.2 / 0.45 / 0.4 | [N], Töne [E] | Aktiv bei vollständiger harmonischer Eignung |
| JB-M02 | Septimen-Wiegen | 0.25 / 0.3 / 0.25 | [I], Töne [E] | Aktiv bei vollständiger harmonischer Eignung |
| JB-M03 | Fallendes Moll-Dreiklangsmotiv | 0.25 / 0.3 / 0.2 | [I], Töne [E] | Aktiv bei vollständiger harmonischer Eignung |
| JB-M04 | Quartaufschlag mit Leitton | 0.35 / 0.4 / 0.3 | [N], Töne [E] | Aktiv bei vollständiger harmonischer Eignung |
| JB-M05 | Chromatik aufwärts über Pedal | 0.3 / 0.6 / 0.65 | [N], Töne [E] | Zurückgestellt: Chromatic non-chord path needs explicit resolution/pedal semantics |
| JB-M06 | Chromatik abwärts über Pedal | 0.2 / 0.6 / 0.65 | [N], Töne [E] | Zurückgestellt: Chromatic non-chord path needs explicit resolution/pedal semantics |
| JB-M07 | Diminuierte Oberzelle | 0.3 / 0.65 / 0.6 | [N], Töne [E] | Aktiv bei vollständiger harmonischer Eignung |
| JB-M08 | Terzaufstieg hell | 0.8 / 0.35 / 0.15 | [I], Töne [E] | Aktiv bei vollständiger harmonischer Eignung |
| JB-M09 | Lange Liebeslinie | 0.75 / 0.25 / 0.1 | [I], Töne [E] | Zurückgestellt: Original tone set has no exact chord-tone realization in the Barry harmony pool |
| JB-M10 | Seufzer | 0.65 / 0.15 / 0.1 | [I], Töne [E] | Aktiv bei vollständiger harmonischer Eignung |
| JB-M11 | Drei-Ton-Warnung | 0.15 / 0.55 / 0.5 | [H], Töne [E] | Aktiv bei vollständiger harmonischer Eignung |
| JB-M12 | Fanfarenruf | 0.8 / 0.55 / 0.2 | [I], Töne [E] | Aktiv bei vollständiger harmonischer Eignung |
| JB-M13 | Spy-Riff synkopiert | 0.25 / 0.55 / 0.45 | [I], Töne [E] | Aktiv bei vollständiger harmonischer Eignung |
| JB-M14 | Staccato-Repetition mit Mollsext | 0.25 / 0.6 / 0.5 | [I], Töne [E] | Aktiv bei vollständiger harmonischer Eignung |
| JB-M15 | Quint-Sprung-Echo | 0.4 / 0.35 / 0.25 | [I], Töne [E] | Aktiv bei vollständiger harmonischer Eignung |
| JB-M16 | Wehmuts-Linie | 0.3 / 0.25 / 0.2 | [I], Töne [E] | Aktiv bei vollständiger harmonischer Eignung |
| JB-M17 | 3/4-Schwungmelodie | 0.3 / 0.5 / 0.4 | [I], Töne [E] | Aktiv bei vollständiger harmonischer Eignung |
| JB-M18 | Verfolgungs-Sechzehntel | 0.25 / 0.85 / 0.75 | [H], Töne [E] | Zurückgestellt: More than eight original notes |
| JB-M19 | Hornruf Dur | 0.85 / 0.5 / 0.2 | [I], Töne [E] | Aktiv bei vollständiger harmonischer Eignung |
| JB-M20 | Abgesang | 0.6 / 0.15 / 0.1 | [I], Töne [E] | Aktiv bei vollständiger harmonischer Eignung |
| JB-M21 | Flackernde Halbtöne | 0.15 / 0.3 / 0.6 | [H], Töne [E] | Aktiv bei vollständiger harmonischer Eignung |
| JB-M22 | Massiver Unisono-Schlag | 0.15 / 0.85 / 0.25 | [H], Töne [E] | Aktiv bei vollständiger harmonischer Eignung |
| JB-M23 | Flirrende Terzen | 0.85 / 0.25 / 0.6 | [H], Töne [E] | Aktiv bei vollständiger harmonischer Eignung |
| JB-M24 | Triumphruf | 0.9 / 0.85 / 0.2 | [H], Töne [E] | Aktiv bei vollständiger harmonischer Eignung |
| JB-M25 | Helle Hetzjagd | 0.85 / 0.9 / 0.85 | [H], Töne [E] | Zurückgestellt: More than eight original notes |
| JB-M26 | Dreitonzelle des Gegenspielers | 0.2 / 0.5 / 0.45 | [I], Töne [E] | Zurückgestellt: Chromatic non-chord path needs explicit resolution/pedal semantics |

Die kurze Acht-Noten-Speichergrenze wird nicht auf Vorrat erweitert. Die Originale M18/M25 werden nicht still gekürzt. Die optionalen Forschungsvariationen jeder R/M-Zeile (etwa Krebs, Umkehrung, zusätzliche Auftakte oder frei umgestellte Takte) sind nicht pauschal implementiert; verfügbar bleiben die ausdrücklich beschriebenen Grundfassungen und die vorhandenen gemeinsamen Motivtransformationen. M05/M06, M09 und M26 werden nicht durch ähnlich klingende, musikalisch andere Tonfolgen ersetzt. Lange P/L/A/F-Bögen, A–A–B-Form, komplexe Chromatik, Reinstrumentierung und motivabhängige Schichtentwicklung bleiben spätere Aufgaben.

## Reproduzierbare Prüfungen und Ergebnisse

- `BarryVocabularyTests`: alle 16 R als tatsächliche Ausgaben im passenden Kontext; R05/R14/R26 zusätzlich mit echter automatischer Harmonieauswahl. Alle 20 M werden vollständig gespielt, mit dem tatsächlich gespeicherten Material verglichen und auf beiden melodischen Rollen in zwölf Transpositionen mit geeigneten Tonumfängen geprüft. Außerdem Artikulations-/Motiv-/Mute-Verhalten, späte Aktivierung, kalter Seek, Notengate-Bilanz, Original-Unveränderlichkeit, Wiederkehr, identische M19-Loop-Gestalt und Gates beider Stimmen mit beiden Legato-Zuständen, verschiedene Hosttempi, Swing und Blockgrößen.
- `scripts/analyze_barry_cells.py --output <Ordner>`: 32 Vergleichspaare gegen 9b572b8, je 128 Takte, statisches und bewegtes XYZ, manuelle Begleitung sowie Positionssprünge/Neustart. Die Produktionsheader werden ohne historische Test-Umschaltung kompiliert. Für Barry werden zusätzlich Blockgrößen 127 und 8192 gegen 512 verglichen.
- `tools/barry_cells_coverage.cpp`: reale Motiveinführung über 7³ XYZ-Punkte einschließlich aller Ränder, für 4/4, 3/4 und 6/8 sowie Variety 0 / 0,5 / 1; kein Ersatzalgorithmus. Eine solo aktivierte Hauptmelodie ermöglicht die getrennte Beobachtung ihrer tatsächlich verwendeten Vorlage. Niedrige Aktivitätsschwellen werden dabei nicht künstlich übergangen.
- Vollständige Regression, Plugin-Live-/Exportfälle, Sanitizer und Build: abschließende Ergebnisse unten.

### Tatsächliche 128-Takte-Ausgabe

64 Renderings (32 vorher/nachher-Paare) gegen 9b572b8. Alle **25 vollständigen MIDI-Vergleichspaare außerhalb von Score-Barry sind bytegleich**, einschließlich Neutral/Herrmann und aller bisherigen Pop-Profilparameterwerte. Die sieben Barry-Fälle stimmen zusätzlich in 14 Vergleichen der Blockgrößen 127/8192 mit 512 überein. Alle aktuellen Notenledger sind ausgeglichen; keine doppelt belegten physischen Notengates, keine hängenden Noten und keine zeitliche Überlagerung von Melodie und Dialog.

| Kontext, 128 Takte | Stand | Bass Note-ons | Arp Note-ons | Melodie Note-ons / Gate | Dialog Note-ons / Gate | längste gemeinsame melodische Pause |
|---|---|---|---|---|---|---|
| dunkel/intensiv | Phase 2 | 310 | 790 | 58 / 18.95 % | 64 / 23.24 % | 14 s |
| dunkel/intensiv | Phase 3 | 512 | 898 | 47 / 9.77 % | 61 / 16.02 % | 14 s |
| warm/ruhig | Phase 2 | 42 | 454 | 30 / 11.28 % | 31 / 12.11 % | 20 s |
| warm/ruhig | Phase 3 | 42 | 469 | 31 / 4.30 % | 43 / 6.25 % | 14.5 s |
| XYZ-Fahrt | Phase 2 | 259 | 926 | 58 / 18.16 % | 34 / 11.72 % | 20 s |
| XYZ-Fahrt | Phase 3 | 339 | 763 | 58 / 19.73 % | 57 / 14.21 % | 14 s |
| hell/intensiv/unruhig | Phase 2 | 184 | 846 | 58 / 17.38 % | 60 / 17.19 % | 13 s |
| hell/intensiv/unruhig | Phase 3 | 184 | 898 | 47 / 9.77 % | 93 / 15.43 % | 14 s |
| sehr ruhig/dunkel | Phase 2 | 52 | 0 | 0 / 0.00 % | 0 / 0.00 % | 256 s |
| sehr ruhig/dunkel | Phase 3 | 52 | 0 | 0 / 0.00 % | 0 / 0.00 % | 256 s |

Die kürzeren neuen Gesten benötigen häufig weniger Gate-Zeit, ohne minutenlange gemeinsame Blockaden zu erzeugen. Das beweist keine höhere musikalische Qualität. Insbesondere der intensive dunkle Kontext wird im Bass rhythmischer (512 statt 310 Anschläge); das ist eine bewusste Begleitänderung und als solche zu hören. Der warme Bass bleibt bei 42 Anschlägen, der sehr ruhige Fall unverändert bei 24 Flächen- und 52 Bassanschlägen. Manuelle Bass-/Arp-Muster bleiben im entsprechenden Hörvergleich unverändert, während die aktivierten melodischen Rollen bewusst neues Material spielen.

### XYZ- und Kontextabdeckung

7³ Punkte je Kombination aus drei Variety-Werten und drei Taktarten ergeben 3.087 tatsächlich gerenderte Einführungen. Tonart A und der vorhandene Standardtonumfang der Hauptmelodie werden beibehalten. Die Rhythmusspalte zählt passende Kandidaten nach dem echten neuen Selektor unter den harmonischen Zeitbedingungen, nicht automatisch ausgegebene Ereignisse bei deaktivierten Rollen. Die vollständige harmonische XYZ-Auswahl bleibt gegenüber Phase 2 unverändert.

| Variety | Takt | Punkte mit tatsächlich gespeichertem JB-M / 343 | unterschiedliche JB-M im Raster | Punkte mit R-Kandidat / 343 |
|---|---|---|---|---|
| 0 | 4/4 | 245 | 12 | 125 |
| 0 | 3/4 | 82 | 1 | 54 |
| 0 | 6/8 | 0 | 0 | 20 |
| 0.5 | 4/4 | 245 | 12 | 125 |
| 0.5 | 3/4 | 73 | 1 | 54 |
| 0.5 | 6/8 | 0 | 0 | 20 |
| 1 | 4/4 | 245 | 13 | 128 |
| 1 | 3/4 | 51 | 1 | 54 |
| 1 | 6/8 | 0 | 0 | 20 |

Bei 4/4 entsprechen die 98 Einführungen ohne kanonische M-ID den beiden untersuchten Y-Ebenen unter der Aktivitätsschwelle. Die aktive Hauptmelodie verwendet dort im Raster tatsächlich kanonisches Material. In 3/4 steht nur M17 zur Verfügung; ungeeignete Harmonik führt zum vorhandenen generativen Pfad. 6/8 hat eine eigene Bass-Rhythmusvorlage R11, aber keine kanonische kurze JB-M im passenden Metrum; der bestehende Motivpfad bleibt dort erhalten.

Nicht alle 20 M werden in jedem groben Raster oder unter dem Standardregister gewählt. Die detaillierten IDs und Häufigkeiten stehen in `PHASE_3_MEASUREMENTS.json`; eigene Akkordfolgen, andere passende Register/Transpositionen und andere Auswahlwürfe erschließen zusätzliche geeignete Kombinationen. Die vollständige Ausführung aller 20 wird separat mit passenden realen Akkordtypen geprüft. Beispielsweise kann der weite M19-Bogen in A unter dem Standardbereich 60–84 unspielbar sein und wird dann korrekt durch eine geeignete Figur ersetzt. Kein Ton wird zum Erzwingen dieser Vorlage einzeln oktaviert.

Alle 16 R sind an ihrem Anker in geeigneten Kontexten tatsächliche Auswahlgewinner und wurden als MIDI-Einsatzraster geprüft. R05, R14 und R26 sind zusätzlich mit automatischer produktiver Harmonieauswahl nachgewiesen. Neue R-Lücken an den äußeren XYZ-Rändern sind bewusst erlaubt: Dort bleibt die bereits funktionierende Barry-Begleitung erhalten, statt entfernte oder unpassend dichte Studien zu erzwingen. Das ist keine vollständige neue rhythmische Feldabdeckung.

### Konkrete kurze Gesten

Bezug C, Legato EIN, in einem jeweils passenden Klangfeld; Oktave/Register können die vollständige Figur transponieren:

- M01: MIDI 72–75–79–83–79–75, Einsätze bei Tick 0/480/960/1440/1920/2400, je 480 Ticks; Zyklus 3.840 Ticks. Die folgenden 960 Ticks sind eine Viertelpause, nicht zwei Viertel wie eine widersprüchliche Textzeile der Forschung behauptet.
- M17 als Dialoggestalt: C5–H4–C5–G4, Einsätze 0/960/1440/1920, Dauern 960/480/480/960; ein 3/4-Takt von 2.880 Ticks. Die Hauptmelodie kann die ganze Figur höher legen, soweit ihr Register passt.
- R05: Bass je ein gehaltener Anschlag pro Takt; Bewegung 4 → 8 → 16 → 8 Anschläge über vier Takte. R26: gehaltener Dreiviertelbass und 6 → 12 Anschläge über zwei 3/4-Takte. Motivreservierungen können diese Begleitanschläge gezielt unterdrücken.

Die unveränderte Wiederkehr bleibt Bestandteil der gemeinsamen Variationsfolge. Der Test vergleicht das gespeicherte Original nach neun und nach 128 Takten; seine musikalische Identität bleibt gleich.

### Abschließende technische Prüfung

- **51/51 Gesamttests bestanden**. Nach der zusätzlichen Korrektur des neuen Loop-Wiedergabepfads wurden die sechs betroffenen Gruppen `ScoreRealization`, `RoleCoordination`, `Barry`, `BarryVocabulary`, `HarmonicProfiles` und `Policy` frisch gebaut und **6/6 erneut bestanden**. Die vollständige historische Suite wurde nach dieser ausschließlich Barry-Vorlagen betreffenden Korrektur nicht noch einmal wiederholt; die 64 produktiven Vergleichsrenderings wurden dagegen vollständig erneut erzeugt.
- **ASan/UBSan:** die drei frisch gebauten CTest-Gruppen `ScoreRealization`, `RoleCoordination` und `Barry` bestanden. Der abschließend korrigierte `BarryVocabularyTests` wurde separat mit `-O1 -g -fsanitize=address,undefined -fno-sanitize-recover=undefined -fno-omit-frame-pointer` neu kompiliert und vollständig bestanden. Beim zusätzlichen Dialog-Loop-Test musste der Motivschalter ausdrücklich eingeschaltet werden; die vorangegangene Testfassung hatte freie Linien statt Motivmaterial geprüft. Keine Sanitizer-Meldungen in den erfolgreich abgeschlossenen Prüfungen. Leak-Erkennung war wie im vorhandenen Sanitizer-Aufbau deaktiviert.
- **Echter Plugin-Prozessor:** komplette `ProcessorTests` erfolgreich, einschließlich Live-/Exportgleichheit, Barry-Kontexten, Transport, Allokationswächtern und bestehenden GUI-/State-Prüfungen. Die 216 ausgegebenen Importfälle bestanden; der große Block blieb mit 872 Note-ons und 872 Note-offs ausgeglichen.
- **Linux-x64-VST3:** erfolgreich neu gebaut. Ein Windows-Build wurde in diesem Auftrag nicht gestartet.
- **7/7 Paketprüftests** bestanden; beide Offline-Datengeneratoren bestehen `--check`, `git diff --check` ist sauber.
- Die neun bereits vorhandenen Forschungs-/Planungsdateien sind gegenüber `9b572b8` bytegleich. Auch Harmoniekatalog, Akkordtypen und harmonische Profilgewichte wurden nicht geändert.

`PHASE_3_MEASUREMENTS.json` enthält die finalen 64 MIDI-Ergebnisse, die neun Rasterzusammenfassungen und SHA-256-Werte der tatsächlich dafür kompilierten Produktionsheader. Der neue Laufzeitpfad verwendet statische Vorlagendaten und begrenzte Stack-/Wertstrukturen; Dateioperationen und Parsing finden ausschließlich offline statt. Die geprüften Verarbeitungsaufrufe bleiben ohne Heap-Allokationen.

## Hörabnahme

Score, John Barry, Aufbau AUS, Bass und Arp jeweils Auto, Arp-Tempo Auto. 120 BPM als Vergleichstempo; das Hosttempo bleibt frei. Beide Motivschalter EIN; Melodie optional einschalten. Zunächst gleiche Instrumente für A/B verwenden, nicht den Klangwechsel als Stilnachweis werten.

- 4/4, XYZ 0,30 / 0,75 / 0,70: R05-Verdichtung über passendem langsamem Farbpendel; M07 kann eine achttonige kurze Geste liefern.
- 4/4, XYZ 0,35 / 0,60 / 0,50: R14-Synkope. Für das reine Einsatzraster zunächst beide melodischen Rollen muten, danach wieder aktivieren und deren Vorrang hören.
- 3/4, XYZ 0,30 / 0,65 / 0,55: R26, Achtel → Sechzehntel über gehaltenem Fundament. XYZ 0,30 / 0,50 / 0,40 zusätzlich für M17 im geeigneten Moll-Major-Kontext vergleichen.
- 4/4, XYZ 0,80 / 0,30 / 0,10: warmer ruhiger Vergleich; kein erzwungener entfernter Bossa-Motor. Bei sehr ruhigem 0,15 / 0,20 / 0,80 bleibt die vorhandene zurückhaltende Textur zulässig.

Mindestens 64, besser 128 Takte hören, damit Einführung, Pausen, Wiederkehr und gemeinsame Varianten erkennbar werden. Die ersten ein bis zwei Takte allein prüfen nicht das Motivgedächtnis. Für die isolierte neue Rhythmik dürfen die melodischen Rollen zunächst stumm sein; beim Wiedereinschalten muss das Arp den tatsächlichen Motivfenstern Platz lassen.

Musikalische Überzeugungskraft und stilistische Authentizität bleiben bis zur Hörabnahme vorläufig. Die angegebenen Hörkontexte sind keine Rekonstruktion bestimmter Film-Cues. Nach diesem Schritt wurden keine weiteren Funktionen begonnen.
