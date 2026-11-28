# Bernard Herrmann – aktualisierter Implementierungsplan

28.11.2026 · `develop/composition-core-prototype` · geprüfter Quellstand **`58ea29d`**.
Nur Analyse und Vorbereitung. Keine HE-Vorlage neu aktiviert, keine Engine-,
GUI- oder Runtime-Datenänderung. Carpenter P1 ist technisch ausgeliefert; seine
musikalische Hörabnahme bleibt abzuwarten. Williams P2/P3 und Morricone P1 sind
positiv gehört, jedoch nicht exhaustiv über sämtliche Parameter geprüft.

## 1. Entscheidung und Umfang

Empfehlung: **ein zusammenhängendes Herrmann-Paket „Klangobjekte, Pedale und
Module“**, keine Reihe öffentlich ausgelieferter Mini-Prototypen. Es soll aus dem
bisherigen reinen Harmoniepräferenzprofil ein hörbar eigenständiges Underscoring-
Profil machen: latente Stasis, chromatische Pendel, verbindliche Gemeinsamton-
Gelenke, eigenständiger Bass, obsessive kurze Zellen und bewusst leere Fenster.
Das Profil muss schon ohne HM und GS musikalisch tragen; beide bleiben optional.

Variante C ist verbindlich: gemeinsame Kompositionsmechanismen und passende
Profil-/Quellendaten, Stilfamilien nur zur GUI-Organisation. Das vorhandene
Herrmann-Profil erweitern, kein zweites „Herrmann neu“, kein SYNTH-Unterkern und
keine Instrumentenvorschrift. Die bestehende SCORE-/POP/ROCK-Oberfläche muss für
Herrmann nicht umgebaut werden. Die 39 Pop/Rock-Wendungen bleiben vollständig.

Das Paket hat einen umfangreichen, konkret benannten **Kandidatenrahmen von
47 H-, 28 R-, 18 B- und 22 M-Grundformen**. Das sind 115 Quell-IDs, weder115 neue
Katalogeinträge noch115 schon implementierte Vorlagen. Harmonie-Dubletten werden
über stabile Bestands-IDs und zusätzliche Herkunft/Strategiedaten angebunden.
Zeitliche Harmonieeignung, Spielweise und Originaltreue entscheiden die endgültige
Freigabe, nicht eine Importquote. Modellstudien sind Abnahmereferenzen, keine
zusätzlichen automatisch importierten Musikstücke.

Polychorde/Verschmelzung bleiben der nächste zusammenhängende Erweiterungsblock.
Sie sind nicht mit zwei Sequencern erledigt und werden für dieses erste große
Paket nicht durch Klangmengen-Vereinigung oder Weglassen einer Komponente imitiert.
Das ist die wichtigste verbleibende Grenze gegenüber der gesamten Herrmann-Grammatik.

## 2. Quellenrang und Fortschreibung aller 343 IDs

Maßgeblich bleiben kanonisches [Vokabular](STROMSCORE_Bernard_Herrmann_Vokabular_Kanonisch.md),
CSV, MIDI und [Qualitätsprüfung](HE_Qualitaetspruefung.md). Die
[Tiefenrecherche](Spannungsgrammatik_Tiefenrecherche.md) liefert wissenschaftliche
Verfahrensgrundlagen; konkrete Vorlagen sind eigene Konstruktionen, keine
Transkriptionen. BH-Fassungen nicht parallel importieren; der
[BH-/HE-Abgleich](BH_HE_CROSSWALK.md) bleibt relevant.

Das ursprüngliche [technische Inventar](TECHNICAL_INVENTORY.json), seine
Bewertungsquelle und [XYZ-Diagnose](XYZ_COVERAGE.json) bleiben als Befund zu
`023b0a6` unverändert. Sie sind **keine aktuelle Liste fehlender Kernfunktionen**.
Der neue [maschinenlesbare Abgleich aller343 IDs](CAPABILITY_REVIEW_58ea29d.json)
hält alte Einstufung, aktuelle Grundform-Einstufung, Fähigkeitsfortschritt,
konkrete Grenzen und Paketkandidaten getrennt fest.

| Bereich | Gesamt | D | A | E | K |
|---|---:|---:|---:|---:|---:|
| Harmonik | 101 | 34 | 15 | 50 | 2 |
| Rhythmik | 66 | 0 | 31 | 34 | 1 |
| Bass | 45 | 0 | 8 | 34 | 3 |
| Motive | 57 | 0 | 31 | 25 | 1 |
| Phrasen | 21 | 0 | 0 | 21 | 0 |
| Studien | 40 | 0 | 3 | 37 | 0 |
| Transformationen | 13 | 0 | 0 | 13 | 0 |
| **Summe** | **343** | **34** | **88** | **214** | **7** |

D: Grundform mit bestehenden Mechanismen darstellbar, Import trotzdem nötig.
A: vorhandene musikalische Grundfähigkeit, begrenzte Daten-/Verbraucheranbindung
und Kontextprüfung nötig. E: mindestens ein wesentliches Verfahren, eine exakte
Klangdefinition oder ein geeigneter Fähigkeitsvertrag fehlt weiterhin. E bedeutet
nicht zwangsläufig großen Architekturumbau. K: inhaltliche Frage offen.
**122 D/A-Grundformen sind keine122 vollständig produktionsfertigen Vorlagen.**
Optionale Varianten und geforderte Mehrrollenprozesse werden nicht mitgezählt.

16 bisherige E-Einstufungen können konservativ zu A fortgeschrieben werden:

- H08/H15/H21/H22/H32/H33/H35/H76/H93: feste chromatische Parallel-Lagen lassen
  sich inzwischen als vollständige `HarmonyVoicing`-Folge ausdrücken.
- H23/H43: der tiefe C-Pedal-Grundfall nutzt die vorhandene unabhängige Lebensdauer;
  hohe/innere Varianten folgen daraus nicht.
- R11/R29/R30/R63: unabhängige vollständige Perioden sind vorhanden; die genaue
  Rollen-/Figurenanbindung fehlt weiterhin.
- B20: kurzer einzelner Bassimpuls mit langer Leerstelle ist ein darstellbarer
  vollständiger Zyklus, keine neue Bass-Kompositionsengine nötig.

Viele weitere E-Vorlagen sind jetzt **teilweise** realisierbar. Ihre Einstufung
bleibt bewusst E, wenn die musikalisch entscheidende Restanforderung fehlt.
Ein Beispiel ist B14: die Tonfolge ist speicherbar, aber die langen Gates und ihre
Spielweise passen nicht zum vorhandenen Kurz-Bass-Verbraucher.

## 3. Wiederverwendbare Implementierung und ihre tatsächlichen Grenzen

| Fähigkeit / Code | Jetzt tatsächlich vorhanden | Für Herrmann noch zu tun |
|---|---|---|
| [HarmonyTypes.h](../../../Source/HarmonyTypes.h), `HarmonyTemplate`, validierter Generator | 225 Vorlagen,27 Akkordtypen, stabile IDs, Herkunft, XYZ, geschützte Farbe, Slash-Bass; acht Slots/acht ganze Takte. | HE-Daten/Pool importieren; neue exakte Typdefinitionen bei Bedarf. Keine ungeprüften Ersatztypen oder globale XYZ-Änderung. |
| `ScoreEngine::prepareVoicingPlan`, [VoiceLeading.h](../../../Source/VoiceLeading.h)::`VoiceBinding`, `HarmonyVoicing.held` | Notierte vollständige Lagen, verbindliche gemeinsame absolute Töne und Erhalt derselben MIDI-Note auf LF. Ganze Lage darf oktaviert werden. | H03 und passende Gelenke explizit markieren; identitätskritische Parallel-Lagen dürfen bei Registermangel nicht unbemerkt durch freie Umkehrungen ersetzt werden. Pflichtbindung auch bei Peaks/Wechseln prüfen. |
| [PedalPlan.h](../../../Source/PedalPlan.h), `permits`, `Active::pedalOwner` | Tiefer monophoner Anspruch mit eigener Lebensdauer; Slash-Konfliktprüfung und ausdrückliche lokale Dissonanzautorisierung; kein zwangsläufiger Akkord-Neuanschlag. | `preparePedal` ist noch Williams-spezifisch; `prepareSequencePedal` bindet an Tonika/Carpenter-Daten. HE-Pedalton und Lebensdauer als Quellendaten anschließen. Hohe/innere/mehrere Pedale fehlen. |
| [SequencePlan.h](../../../Source/SequencePlan.h)::`SequenceSource/SequenceUse` | Bis32 Tonpositionen/64 Einsätze, Tick-Gates/Akzente, unabhängige Quellenverwendungen, vollständiger Ton-/Rhythmuszyklus, Identität. | Quellen selbst sind kein aus tatsächlich gespielter Linie neu gebildeter Motivkatalog. HE-Zellen passend als Begleitzyklus oder erinnerte Melodie behandeln, nicht diese Identitäten gleichsetzen. |
| `SequenceSource::cycle`, `SequenceUse::next/tone` | Gesamtzyklus `Rhythmusperiode × Tonzahl/gcd(Tonzahl,Einsatzanzahl)`; keine notwendigen Takt-Resets. | B24:3 Tonpositionen gegen16 Einsätze über3Takte ergibt9Takte Gesamtzyklus. Akkordrelative R/8/R-Referenzen müssen ihre Phase beim Harmoniebezugwechsel behalten. |
| [SequenceAdapter.h](../../../Source/SequenceAdapter.h), `prepareSequences/renderSequences` | LB-Pedal neben KB, eigenständige AR-/GS-Begleitung, ganze Figuren statt zufälliger Notenlöschung. | Der aktuelle Adapter hat drei feste Performer KB/AR/GS,4/4/Auto/Follow-Bedingungen, einen festen KF-Viertelpuls und eine TU-Echoquelle. Kein unverändert übernehmbarer allgemeiner HE-Rhythmusverbraucher. Begrenzte Rollen-/Quellansichten erweitern, keine Kopie. |
| `sequencePitch/sequenceFits` | Akkordprüfung über die ganze Gate-Dauer und geplante Harmonie, Register-/Spielweisenprüfung. T verwendet den gemeinsamen Modus. | F/U außerhalb der Akkordmaske sind derzeit eng an passenden Dur-/Molldreiklang gebunden, V fehlt. Diese Freigabe gilt nicht automatisch für mMaj7, Polychorde oder andere HE-Kontexte. |
| [CompositionCore.h](../../../Source/CompositionCore.h)::`RememberedMotif/MotifCatalog/MotifUse`, [AuthoredMotifSource.h](../../../Source/AuthoredMotifSource.h) | Tatsächlich gespieltes Original, unabhängige Stimmenzustände, frühe Reprise, Rhythmusvariation/Fragment/Sequenz/Augmentation, lokale Quellmasken. | Melodischer Speicher weiterhin8 Noten/2 Materialien pro Szene; Autorenauswahl/Provenienz noch Barry/Williams-spezifisch. HE-Pool anschließen, V-Auflösung und F/U-Erhalt bei Varianten prüfen. |
| `LayerCycle::active`, Arp-Phrasierung und Rollenfenster | Begrenzte zyklische Schichtung bei statischem XYZ, Unterbrechung und Wiederaufnahme, auch kontinuierliche Figuren möglich. | Keine fertige HE-Modulgrammatik für3→2Takte, Bar-Form, Rollenwanderung oder variable Interpunktionsabstände. Nicht das Carpenter-Schichtschema als Herrmann-Rezept kopieren. |
| [MusicalTime.h](../../../Source/MusicalTime.h), [MusicalExecution.h](../../../Source/MusicalExecution.h) | 64Bit/960 PPQ, exakte beliebige Tick-Ereignisse, Harmonie vom Swing getrennt. | Keine neue Uhr. 320-Tick-Triolen sind darstellbar; `AuthoredMotifSource.at/lengths` und andere Eingänge verwenden noch Sechzehntelzählung. Hemiolen/triolische Vorlagen brauchen exakte Verbraucher. |
| `CompositionCore::PlayingTrack/RoleNeed/suitable`, `ScoreEngine::outputCatalog` | Rollen, Spielweisen, Instrumentannahmen und MIDI-Adressen getrennt; GS als Begleitsequenz möglich. | Kein allgemeiner Komponenten-, Kanon- oder Rollenwanderungsplan. Externe Patches weiterhin unbekannt. Keine zusätzlichen Ausgänge begründet. |

Der heutige Herrmann-Eintrag ist weiterhin `harmonySelectionOnly=true` und erhält
in `compositionProfiles` die neutrale Policy. Es gibt noch keinen HE-Runtime-Pool.
Eine Auswahl im GUI allein würde die neuen Quellen deshalb nicht aktivieren.

### Dauer und Notenbesitz sind echte musikalische Voraussetzungen

Die Standardannahmen bleiben KF/TU maximal720, KB960, AR7680 Ticks; LB ist
sustained/monophon, LF sustained/bis6 Stimmen. Die aktive Figurenstrategie ändert
nur KB/AR/GS zu detached/monophon und48..3840Ticks. Sie macht **nicht** alle
externen Patches lang spielfähig. B14/B15 mit7680-Tick-Gates passen selbst dort
nicht. B30 mit1920Ticks ist nicht schon deshalb legato-fähig.

Für lange monophone Basslinien den passenden bestehenden **LB-Verbraucher** an den
Figurenplan anbinden; dabei LB-Pedal und LB-Linie auf demselben Ziel als alternative
Besitzansprüche behandeln. Kein stilles KB→LB-Rerouting einer laufenden manuellen
Figur. LB+KB je eine Stimme ist möglich (B04); zwei gleichzeitige LB-Töne (B43)
bleiben unzulässig. Mute/Solo, Kanalgleichheit und manuelle Spielweisen haben Vorrang.

## 4. Musikalisch repräsentativer Paketkandidat

Die vollständigen ID-Listen stehen auch im neuen JSON. Kandidat bedeutet:
Quellinhalt vorab prüfen, nicht blind registrieren. Strenge Voraussetzungen jeder
Figur entscheiden, ob sie im Produktionsbetrieb wirklich auftreten kann.

### Harmonie – 47 Grundformen

H01, H02, H03, H05, H06, H07, H08, H09, H10, H11, H13, H14, H15, H16, H17,
H18, H19, H20, H21, H22, H23, H24, H25, H28, H30, H32, H33, H35, H36,
H37, H38, H39, H40, H41, H42, H43, H45, H46, H48, H66, H67, H76, H78,
H82, H85, H93, H96 (jeweils Präfix `HE-`).

Das umfasst mMaj7/mMaj9, übermäßige/halbverminderte Klangobjekte, lokale Okt-A/B-
Klänge, chromatische Parallelität, nichtfunktionale Terzbeziehungen, tiefe
Dissonanz-/Slash-Bässe, lyrische/offene Entwicklungen und kalte helle Hochlagen.
H40/H42 sind als **notierte Akkordfolge** nutzbar; daraus folgt noch keine freie
hexatonische Melodik. H13/H48 verlangen als Akkordobjekte keine neue Ganztonskala.
H87/H88 bleiben wegen3/4-/6/8-Quellbindung außerhalb des4/4-Erstkandidaten.

Strikte Dubletten aus dem historischen Inventar erneut gegen den225er-Katalog
abgleichen. Etwa H01/H10 können vorhandenes geschütztes Material referenzieren;
H32 kann trotz gleicher Ton-/Bass-/Dauerfolge einen zusätzlichen exakten
Parallel-Lagenplan benötigen. Eine gleiche Tonklassenliste macht keine gleiche
musikalische Vorlage. Stabile Bestands-IDs erhalten; neue IDs erst beim Import
festlegen. Kein Zwang,47 physisch neue Harmonieeinträge anzulegen.

### Rhythmik – 28 Grundformen

R01, R02, R08, R09, R11, R14, R15, R16, R17, R18, R20, R27, R28, R29,
R30, R33, R35, R36, R37, R45, R47, R54, R55, R58, R59, R60, R63, R64.

Kurze Pulse, Punktierungen, synkopierte Interpunktion, Atemflächen, lange Leere,
Hochlagenpaare und unabhängige Zyklen bilden einen Kontrast; keine Pflicht zu
Dauer-Arpeggien. R11/R29 benötigen einen gemeinsamen Beginn, aber eigene laufende
Phasen. R60 braucht einen gemeinsamen KF/KB-Einsatzplan, keine zwei Zufallsmuster.
R49/ST-Ereignisbindung ist eine gesonderte Anforderung, kein periodischer Effekt.

### Bass – 18 Grundformen

B01, B02, B03, B05, B10, B11, B14, B15, B16, B18, B20, B24, B25, B27,
B30, B34, B35, B42.

Einzelpedal, gewollter Neuansatz, wiederholter Puls, Halbton-/Tritonuspendel,
spärliche Interpunktion, offene Quintenlage und fehlender Tiefbass sind verschiedene
Funktionen. B14/B15/B25 verlangen lange LB-Linien; B24 vollständige Phasenführung;
B42 einen ausdrücklich passenden hohen Bassregisterplan. B02/B03 dürfen nicht
auf Tonika zurückkorrigiert werden. Kombinationsverweise sind vor Verwendung als
konkreter Harmoniebezug zu prüfen: z.B. B01 verweist auch auf H44 mit noch fehlendem
7b5-Typ. Der Grundfall ist ohne dessen passenden Kontext kein freier „unter allem“-
Fremdtonpass. Quellen, deren korrekter Kontext im Paket fehlt, bleiben zurückgestellt.

### Kurze Motive – 22 Grundformen

M01, M02, M03, M04, M05, M07, M09, M11, M13, M14, M15, M16, M19, M27,
M31, M34, M36, M38, M43, M48, M56, M57.

Kurze Nebennoten-/Seufzerzellen, Vierton-Prototyp, Halbton als große Septime,
Tritonusfall, chromatische Linien und helle weite Zellen; nicht nur Horror-Schläge.
M56 ist über AugMaj7 als Akkordtonlinie möglich, ohne vorher eine vollständige
Hexatonikgrammatik zu entwickeln. HM bleibt optional, GS kann nach Rollenplan
Begleiter oder melodischer Träger sein, nicht beides unkoordiniert.

Die22 Quellen sind keine bereits belegte Produktionsauswahl. Für jede Quelle
muss der zeitlich richtige Kontext erreicht werden; mehrere genannte Kontextklänge
nicht blind maskenweise vereinigen. Bei unklarer zeitlicher Reihenfolge erst
klären oder einen eindeutig belegten gültigen Fall wählen. M30/M40 benötigen
zusätzliche passende Kontext-/Zeitverläufe; M55 insbesondere **C→F#/C**, nicht
C/F#. Sie werden nicht allein wegen attraktiver Namen in den Erstkandidaten gezählt.
M46 als geplante Umkehrungsantwort bleibt von einer bloß spielbaren Zweitonfolge
zu unterscheiden. Keine Vorlage auf zwei Töne kürzen, um die Importzahl zu erhöhen.

## 5. Notwendige Arbeit innerhalb dieses einen Pakets

Diese Reihenfolge sind interne Prüfgates eines Auftrags, keine neuen Einzel-
Prototypen mit jeweils eigener Freigabe/Windows-Auslieferung.

| Intern | Konkrete Arbeit | Nachweis vor Integration |
|---|---|---|
| A: Daten und Quellen | HE-Harmoniepool/Provenienz, geschützte Farben, exakte notierte Lagen und Quellenansichten an vorhandene Profil-Policy anbinden. Nur benötigte HE-Kontextdaten. | Echte Auswahl/Wirkung aller freigegebenen Quellen; Dubletten, stabile IDs, vollständige Akkordfarben, H03-Gelenk und H15/H32-Parallelintervalle. Kein stilles generatives Voicing bei unspielbarer Pflichtlage. |
| B: Pedal-/Bassverwendung | Quellton, Bezug, Beginn/Ende und explizite Neuansätze an vorhandenen Pedal-/Figurenkern; LB-Linien und KB-Pulse getrennt nach Spielweise/Notenbesitz. | B02/B03 transponieren mit dem Zusammenhang; B14/B15 vollständige lange Gates, keine automatischen Reattacks; Folge/Ruhe/Mute/Transport sicher. Kein globales Überschreiben manueller Follow-AUS-Entscheidungen. |
| C: Tonabsicht | Eng begrenzte quellengebundene A/T/V/F/U-Daten; V mit konkretem Ziel und Frist, F/U mit Gültigkeitskontext. Bestehende P3-Masken und geplante Harmonik nutzen. | M03: schwere Dissonanz, leichte Auflösung; F/U bleiben in erlaubtem Kontext, verschwinden aber nicht durch automatische Korrektur. Bei neuer ungeeigneter Harmonie Figur sauber verwerfen, nicht beliebige Fremdtöne lizenzieren. |
| D: Rhythmus und kurze Module | Gemeinsame Quellzyklen auf benötigte geeignete Rollen anbinden; KF/LF/TU nicht per Carpenter-Sonderpuls ersetzen. Ganze Zelle/Pause/Rückkehr und begrenzte Alternative bei stehendem XYZ. | R11/R29/R63/B24 ohne Phasenverlust; vollständiger Ton-/Rhythmuszyklus. Wiederaufnahme bezieht sich auf tatsächlich verwendetes Material; keine zufällige Kombination sämtlicher Parameter. Konkrete HE-T01-Kürzung bleibt gesondert, falls nicht sauber darstellbar. |
| E: Profilkoordination | Die Daten gemeinsam mit Harmonien, Rollenpriorität, Register, manueller Bedienung und vorhandenen Vordergrund-/Arp-Fenstern prüfen. | HM/GS AUS: Profil bleibt erkennbar. Beide EIN: keine ungeplante Konkurrenz; GS-Begleitzyklus wird nicht von optionaler HM pauschal gesperrt. Keine Held-/Pedal-/Arp-Pflicht, keine starre Aktivitätsquote. |
| F: Produktionsabnahme | Statische und dynamische XYZ-Tests, Quellennachweise, A/B-MIDI und gesamte technische Regression. | Nicht nur Einzelvorlagen: volle Produktionsläufe müssen richtige Tonfolge, Gate, Harmoniebezug, Phase, Pause und tatsächliche Vorlagenvielfalt nachweisen. |

Die größten Arbeiten sind **B/C/D als begrenzte Verbraucher-/Absichtsfortschreibung**,
nicht der Harmonieimport. Kein neuer Scheduler, keine universelle Orchestrierung,
keine zusätzliche Benutzeroberfläche und keine neue Künstlerengine. Nicht jede
kompatible Grundform muss zu jedem XYZ-Punkt eine spielbare Besetzung erzwingen.

## 6. Noch fehlende gemeinsame Fähigkeiten und bewusste Rückstellungen

| Bereich | Repräsentative HE-IDs | Sachlich fehlend / nächster Zusammenhang |
|---|---|---|
| Polychorde und harmonische Schichten | H51–H63, H89/H92/H99; S06/S07/S22/S27/S32 | Zwei Komponenten mit eigener Identität/Tonmaske, Bezug, Register, Einsatz, Dauer; danach Verschmelzungsrelation. Ein gemeinsames Slot-Aggregat genügt nicht. Erst zwei Komponenten und geprüfte Zustände, keine universelle Polychordplattform. |
| Komponentenbeziehungen ohne mehr Noten | S06↔S07, T08/T13 | Genau gleiche Tonklassen/Notenzahl/Velocity, andere Lage/Zeit/Gates; Klangfarbe bleibt in der DAW. S06-AR ist eine monophone Brechung und bereits geeignet; fehlend ist der harmonische Komponentenbezug. S07-KF-Halbe1920 braucht geeigneten Dauervertrag. |
| Hohe/innere/mehfache Pedale | H64/H68/H69, B06/B43, S09/S29 | Aktueller Bassanspruch ist kein outputunabhängiger hoher Anspruch. H64: G ist über Db eine autorisierte Fremdnote; H68: F#6 ist nicht in Cm. `VoiceBinding` verlangt Zieltongültigkeit und ersetzt das nicht. Mehrere Claims mit sicherem Notenbesitz und geeigneten Zielen entwickeln, keine Fremdtöne zum Akkord hinzuerfinden. |
| Exakte weitere Klangobjekte | H12/H26/H29/H31/H34/H44/H49/H72/H73/H77/H81/H83/H97/H101 | Vieles ist bedarfsgerechte exakte Typdatenarbeit innerhalb vorhandener fünf Intervalle; größere Aggregate benötigen getrennte Prüfung. Quartal/Cluster nicht auf ähnliche Typen umbenennen. |
| Ganzton/Hexatonik | H49/H50, M28/M50/M54, S18/S36 | Gemeinsame transponierbare Vorräte plus konkrete Gültigkeit/Referenz; die zwölf Gesamttonklassen wechselnder Systeme sind kein frei lizenzierter Vorrat. Okt-A/B nur für passende lokale Quellen, keine Herrmann-Oktatonikpflicht. |
| Pulslose Ereignisfelder | S31, Teile S26/S35, R49/R50 | Ein stilles LF-Feld oder TU-Echo alle16Takte ist kein generatives pulsloses Feld. Kontext-/Ereignisanlass, variable Leerräume und Wiederaufnahmeregel fehlen. Dispatcher wiederverwenden; keinen Klangteppich durch zufällige Einzelnote pro Takt ersetzen. |
| Vollständige Moduloperationen | R19/R21–R26/R39/R40/R48/R61/R62; T01/T03/T05/T09/T11/T12 | Identische Zelle kann schon pausieren; konkrete Kürzung/Verlängerung, Interpunktionsabstand und Originalbezug nicht allgemein fertig. Begrenzte Paket-Atmung ist keine komplette Modulgrammatik. |
| Dynamische Parallelführung | T04, H61, P12 | Feste H-Lagen sind schon darstellbar; beliebige mehrrollige Struktur samt Bass/Komponenten zur Laufzeit exakt verschieben bleibt eigener Vorgang. |
| Triolen/Hemiolen | R05/R10/R13/R57/R65, M54, S33/S40 | Exakte Ereignisdaten/Betonungen durch die benötigten Verbraucher führen. 320Ticks passen zur Zeitbasis; Motivquantum/Autoreneingaben/Spielweise beachten. Kein neuer Swing-/Schedulerumbau. |
| Rollenwanderung und längere Formen | M21/M32/M35/M41, P01–P21, S21/S25/S30/S40 | Referenzierte Zellen/Antworten sind Teilfähigkeiten, kein Kanon/Fugato oder langer gemeinsamer Zielbogen.32 Sequenztonpositionen ersetzen weder8-Noten-Motivgedächtnis noch Langphrasenplanung. |

Reihenfolge nach dem empfohlenen Paket: **zweikomponentige Harmonik und geprüfte
Verschmelzungszustände**, anschließend damit zusammen benötigte hohe Pedale und
Register-/Tonabsichten; Ganzton/Hexatonik bedarfsgerecht vor passenden Quellen;
danach gezielte Moduloperationen/Ereignisfelder und schließlich Rollenwanderung/
lange Formen. Triolen können bei einer konkret priorisierten Quelle vorgezogen
werden, ohne dafür die abgeschlossene Zeitbasisbaustelle wieder zu öffnen.
Alle diese Fähigkeiten können Williams, Morricone und spätere SYNTH-Profile nutzen.

## 7. XYZ und Instrumente: keine globale Neuordnung

Harmonien weiter mit echtem XYZ/Variety auswählen. Bei ausdrücklich „alle X“-
Rhythmen/Bässen/Motiven die Quelle lokal nach Y/Z gewichten und ihre harmonische
Voraussetzung unabhängig prüfen. Die derzeitige Sequencer-Domainprüfung verwendet
alle drei Achsen; bloß ihren Mittelpunkt auf dunkles X zu setzen würde helle
Herrmann-Bereiche unbeabsichtigt sperren. Weiche „eher“-Angaben sind Präferenzen,
keine automatisch harten Ausschlüsse. Keine Änderung der globalen XYZ-Geometrie.

Hohe Y-Werte sollen auch Registermasse/Artikulationskontrast zulassen, nicht nur
mehr Anschläge; Z kann bei gehaltenem Klang aus Reibung, Akzent und Unterbrechung
wirken. Ohne Komponentenplan ist eine echte Verschmelzungsachse noch nicht
vollständig realisierbar. Dieses Defizit nicht durch globale Velocity oder mehr
Noten kaschieren. Statische Position über mindestens128Takte bleibt Hauptfall;
keine obligatorische Eskalation/Entspannung, keine Zeitgrenze.

Die historische Coverage misst getrennte Pools zu `023b0a6`; sie ist kein neuer
Nachweis für diesen47er-Kandidaten. Künftige Auswahlprüfung mit tatsächlichem
Kandidatenpool, Variety0/0,5/1 und dichtem Raster inkl. Rändern: Kandidatenzahl,
absolute Entfernung, musikalisch verschiedene Formen und erreichbare **gespielte**
Rollen getrennt dokumentieren. Erst diese Auswertung darf Abdeckung behaupten.
Keine erfundenen Anker oder Exklusivlisten zur künstlichen Vollversorgung.

Neun bestehende Ziele reichen für den vorgeschlagenen Umfang. LF/KF und LB/KB sind
unterschiedliche Spielweisen; AR mono, GS abhängig von Verwendung, TU kurz/tonal,
ST fest36 und niemals harmonisch transponieren. Externe Patch-Fähigkeiten nicht
als erkannt ausgeben. Vollständige S07/S37-Dauern bzw. Bassdyaden erst nach einem
geeigneten Fähigkeitsvertrag, nicht durch unerlaubtes Kürzen, Vermischen oder
stilles Umrouten. Neue MIDI-Ausgänge sind daraus derzeit nicht begründet.

## 8. Abnahme des zukünftigen Gesamtpakets

- Vorlagengetreue Einzelprüfungen: komplette Notenfolgen, Intervalle, Akzente,
  Tonfunktionen, Gates, Auflösungen, Herkunft und unverändertes Original.
- Produktionsläufe mindestens128Takte, statisches XYZ an acht Ecken und innen,
  langsame/schnelle Fahrten, Variations-/Profilwechsel. Gewählte und tatsächlich
  ausgeführte Quellen mit Ablehnungsgrund unterscheiden; keine bloße Poolstatistik.
- Hörstudien: latente Bedrohung H01/H23 mit Leere; H03/H15-Pendel und feste Lagen;
  heller Tritonusboden H66; kalte Erhabenheit H76/H93; lyrischer H46/H78-Bereich;
  bewegter Bass/individuelle Zyklen; M03-Viertonzelle mit korrekter Auflösung.
  S01/S03/S12 dienen als genaue vorhandene Referenzstudien; ihre kanonischen
  Noten-/Zeit-/Rollenangaben sind separat gegen CSV/MIDI zu prüfen.
- HM/GS AUS, einzeln und zusammen; manuelle Muster, beide Follow-Zustände,
  Mute/Solo und gleiche MIDI-Kanäle. Keine künstliche Vollbesetzung bei ungeeignetem
  Instrument und keine pauschale Rollenblockade bei schweigender Leadstimme.
- Zwölf Transpositionen, mehrere Hosttempi, Swing,3/8/5/8/7/8 und alle unterstützten
  Metren als Regression. Nicht4/4-Quellen nur in ihrer korrekten Taktart ausführen,
  bis dahin sauberen dokumentierten Rückfall statt Rasterumdeutung.
- Stop/Start, später Einstieg, Seek/Loop, Notenenden/Notenbesitz, Blockgrößen,
  tatsächlicher Plugin-Live-/Exportvergleich, Langzeit und keine Audiothread-
  Allokationen. Kaltes Seek kann unbekannte historische XYZ-Verläufe weiterhin
  nicht rekonstruieren; diese akzeptierte Grenze bleibt offen benannt.
- Gesamttests, ASan/UBSan und erst nach Implementierungsfreigabe ein gemeinsamer
  Windows-VST3-/pluginval8-Testbuild für eine zusammenhängende Hörabnahme.
  Neutral, Barry, Williams, Morricone, Carpenter und POP/ROCK absichern.

Die sieben K-Fälle bleiben H04/H71/R12/B08/B28/B39/M08. Neue Technik klärt keine
widersprüchliche Innenstimme, Bassfunktion oder zeitliche Kontextzuordnung.
Funktionale Konflikte an neu angebundenen Quellen ebenfalls dokumentieren und
nicht durch lokale Maskenunion oder angenäherte Akkorde verdecken.

**Aktueller Abschluss:** ausschließlich aktualisierte Planung und dokumentierter
Quellabgleich. Keine neuen Renderings, keine Behauptung über musikalische
Herrmann-Hörqualität, kein Build, kein Push und kein Release. Carpenter P1 zuerst
vom Anwender abnehmen lassen; die nächste Umsetzung bedarf eines neuen Auftrags.
