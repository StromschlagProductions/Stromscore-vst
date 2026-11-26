# Gemeinsame musikalische Fähigkeiten – Williams und Herrmann

Stand: 26.11.2026, Engine `ddad94b`, Branch `develop/composition-core-prototype`.
Die erste [Williams-P1-Hörabnahme](john-williams/P1_ARPEGGIO_AUDIT.md) akzeptiert
P1 als brauchbare Entwicklungsgrundlage, noch nicht als fertiges Künstlerprofil. Dieser Bericht dokumentiert Forschungsabgleich und Empfehlungen. Er gibt
keine weitere Implementierung frei. Engine, GUI, Laufzeitdaten und musikalische
Auswahl bleiben unverändert.

## Grundlage und Aussagegrenzen

- [Herrmann: neue Tiefenrecherche](bernard-herrmann/Spannungsgrammatik_Tiefenrecherche.md), vollständig gelesen; zusätzliches Material zum [bisherigen Stilprofil](bernard-herrmann/Stilprofil_Bernard_Herrmann.txt), kein Ersatz durch ein neues kanonisches Vorlageninventar.
- [Williams: kanonische Forschung](john-williams/STROMSCORE_John_Williams_Profil_Kanonisch.md), besonders A/B, F.3 und die Entwicklung-/Übergangsstudien; [Bestandsabgleich und Fahrplan](john-williams/IMPLEMENTATION_PLAN.md) sowie der tatsächliche [P1-Umfang](john-williams/P1.md).
- Tatsächliche Implementierung in den unten verlinkten Dateien. Der historische Bestandsabgleich vor P1 ist nicht mit dem heutigen Implementierungsstand gleichzusetzen.
- [Projektweite Ausrichtung](../MUSICAL_DIRECTION.md): Horror, Thriller, Mystery und zurückhaltendes Underscoring haben Vorrang. Helle, ruhige, warme und lyrische Bereiche bleiben erhalten. Kein neuer XYZ-Bias und keine Laufzeitquoten.

Die Evidenzzeichen N/I/H/E der Forschung werden als **Angaben ihrer Autoren**
übernommen, nicht als hier unabhängig bestätigte Quellenprüfung. Externe Aufsätze,
Partituren und Hörbelege wurden für diesen technischen Abgleich nicht neu geprüft.
Herrmanns konkrete Vorlagen und Modellstudien fehlen noch. Die Empfehlungen der
Recherche, etwa eine „Modul-Engine“, sind Forschungsinhalt und kein Architekturauftrag.
Archivfassungen und doppelte Beschreibungen desselben Materials zählen nicht als
zusätzliches Vokabular.

## 1. Bestand und gemeinsame Lücken im Produktionspfad

| Fähigkeit | Tatsächlich vorhanden bei `ddad94b` | Gemeinsam benötigte Erweiterung / Grenze |
|---|---|---|
| Harmonie und Farben | [HarmonyTypes.h](../../Source/HarmonyTypes.h): `HarmonyTemplate`, relative Wurzeln, expliziter `Chord.bass`, XYZ, Herkunft, geschützte Färbung; validierte Quelldaten → statische Laufzeitkataloge. 181 Einträge, darunter 49 Williams-Harmonien. | Weiterverwenden. Ein Akkordtyp oder eine Folge ist noch kein musikalischer Systemkontext mehrerer Rollen. Keine neuen Künstlerzweige pro Akkord. |
| Harmonische Tonvorräte | [ModalContext.h](../../Source/ModalContext.h): Ionisch, Mixolydisch, Dorisch, Äolisch; eindeutige, mehrdeutige und inkompatible Kontexte. `ScoreEngine::modalContextFor` prüft das gesamte Wendungsvokabular einschließlich Bass. | Lydisch/Phrygisch, Okt-/Hexatonik und Ganzton fehlen als Kontexte. Rollen brauchen einen ausdrücklich geltenden Vorrat, Zentrum und zeitliche Gültigkeit; Schichten können unterschiedliche Vorräte benötigen. Nicht jede pantriadische Folge hat eine gemeinsame Skala. |
| Nicht-Akkordtöne | `planPassingTone`, `ScoreEngine::addPassingTone`: kontrollierte diatonische Durchgänge in geeigneten phrasierenden Pop-Hooks; `planBassPhrase` nutzt denselben Baustein. Score-Motive werden über harmonische Masken realisiert. | Vorratstöne außerhalb des aktuellen Akkords sind für Score nicht allgemein autorisiert. Durchgang mit Auflösung, bleibende Dissonanz und Pedal sind unterschiedliche musikalische Funktionen. Nicht alle dürfen derselben Auflösungspflicht unterliegen. |
| Erweiterte Akkorddefinitionen | [ChordTypes.generated.h](../../Source/ChordTypes.generated.h): 27 exakte Typen, darunter mMaj7/mMaj9, Aug, HalfDim, Dim7 und **Dom7b9 bereits vorhanden**. Quelldefinitionen in `data/harmony/chord_types.json`. | Fehlende einfache Typen können bedarfsgerecht über den vorhandenen Validator ergänzt werden. `ChordShape::iv[5]` ist eine reale Grenze; größere Mengen und Komponentenstruktur sind eine gesonderte Aufgabe. Keine ähnlich benannten Ersatzklänge. |
| Polychorde / harmonische Schichten | [HarmonyTypes.h](../../Source/HarmonyTypes.h), [CompositionCore.h](../../Source/CompositionCore.h): ein Akkordobjekt pro Harmonie-Slot, eine Flächenlage und ein Bassanker. | Keine zwei gleichzeitig eigenständigen Akkordkomponenten mit eigener Lage, Bewegung und Einsatzzeit. Die Vereinigung ihrer Tonklassen verliert Schichtidentität und Register. Sechstönige Dreiklangspaare überschreiten zudem das Fünf-Intervall-Format. |
| Dissonanzbässe | Explizite Bass-Tonklasse darf außerhalb des Akkords liegen; Williams H17/H46 sind in P1 mit ihren Bassvorgaben importiert. `ScoreEngine::{bassRoot,chordFor}` und Bassstimmführung setzen sie um. | Datenvorgabe vorhanden, frei geplante Dissonanzbassfolge nicht. Beabsichtigte Halbton-/Tritonusreibung ausdrücklich autorisieren, statt sie durch gewöhnliche Akkordtonanpassung zu beseitigen. |
| Eigenständige Bass-Tonfolgen | [BassPhrase.h](../../Source/BassPhrase.h): begrenzte melodische Pop-Bassphrase, Ziel-/Akkordtöne und Durchgänge. `ScoreEngine::melodicBassAllowed` begrenzt sie auf geeignete automatische Pop/Rock-4/4-Kontexte mit Follow EIN. [RoleRhythm.h](../../Source/RoleRhythm.h) bietet einen kleinen relativen Tonzyklus. | Kein gemeinsamer Score-Cantus oder frei definierter chromatischer Bassbogen. Eine begrenzte transponierbare Folge unter expliziten Harmonie-/Dissonanzregeln kann beide Künstler versorgen. Bassverzicht bleibt zulässig. |
| Harmonisch unabhängige Pedale | `BassPedal`, `pedalRoot()` und Williams B01 erlauben Liegetöne unter wechselnden Akkorden. Explizite wiederholte Slash-Bässe können eine vorgegebene Dissonanz tragen. | Reguläres Pedal ist an den ersten Bassanker gebunden; die P1-B01-Zelle ist Tonikapedal mit Schutz gegen widersprechende Bassvorgaben. Kein beliebig gewähltes, abschnittsübergreifendes hohes/tiefes Doppelpedal mit eigener Lebensdauer. Follow AUS ist keine solche Funktion. |
| Parallele Akkordführung | [VoiceLeading.h](../../Source/VoiceLeading.h) und `CompositionCore::leadEntry`: Gemeintöne und kurze Wege, Registerkontrolle und Übergangshistorie. | Das optimiert einzelne Lagen, garantiert aber weder dieselbe Umkehrung noch einen festen Transpositionsvektor aller Stimmen. Exaktes Planing braucht eine eigene begrenzte Bewegungsabsicht; normale Stimmführung bleibt als Alternative bestehen. |
| Kurze repetitive Module | [CompositionCore.h](../../Source/CompositionCore.h): tatsächliche Motivaufnahme, unveränderliches Material, unabhängige Verwendung, frühe Reprise, Rhythmusvariation/Sequenz/Fragment/Augmentation; maximal acht Originalnoten und zwei Materialien pro Szene. Kleine Zellen passen grundsätzlich. | Wiederkehr mit Atempausen ist nicht dasselbe wie ein kontinuierliches Ostinato. Es fehlen rollenbezogene Module mit eigener Wiederholungsfunktion, begrenztem a–a–b-/Unterbrechungsplan und gezielter Rollenwanderung. Keine zweite Motivimplementierung nötig. |
| Koordinierte rhythmische Schichten | [RhythmPlan.h](../../Source/RhythmPlan.h): begrenzter Pop-Bass/Arp-Interlock. [RoleRhythm.h](../../Source/RoleRhythm.h) plus `ScoreEngine::roleRhythm`: zwölf R- und drei B-Quellen in Williams P1, gemeinsame Kurzflächen-/Bass-Einsätze; vorhandene Motiv-/Arp-Reservierungen. | P1 ist auf 4/4, zwei Takte und Sechzehntelraster begrenzt; kein allgemeiner Mehrperiodenplan. Triolen, Hemiolen, gezielte Phasenverschiebung und unterschiedlich lange Zellen sind getrennt zu erschließen. |
| Variable Synchronität / Registertrennung | Instrumentenregister, Oktaven und feste Rollen-/Artikulationsfähigkeiten; Melodie→Dialog- und Dialog→Arp-Antwortfenster. [CompositionCore.h](../../Source/CompositionCore.h): `RoleNeed`, `suitable`, `planMelodyHandoff`; Vordergrundkoordination im Adapter. | Keine geplante Entwicklung von versetzten zu gemeinsamen Einsätzen bei gleichem Material, kein gemeinsamer Registerabstandsplan. Zwei monodische Figuren und zwei polyphone Harmonieschichten sind verschiedene Anforderungen. |
| Längere Entwicklung | Motivwiederkehr, Varianten, Szenenaufbau/-ende, Ereignisdichte und Rollenpausen sind aktiv. `planLinePhrase` erzeugt kurze Zielton-Gedanken; der Adapter nutzt sie für freie Score-Gegenstimme ohne Motiv. | Keine verschachtelte Modulform, langfristige Liquidation, kontrapunktische Außenstimmenentwicklung oder längere Ziel-/Spannungsbögen. Lange Forschungsphrasen lassen sich nicht durch Erhöhen einer Arraygröße vollständig implementieren. |

**Wichtige Abgrenzungen:** `ScoreEngine::ArpOctatonic` verwendet bereits eine
Halbton-Ganzton-Figur; dadurch erhalten Bass, Harmonie und Motive keinen gemeinsamen
oktatonischen Kontext. Die spezielle offene/reduzierte Akkordbesetzung aus
[ChordDisposition.h](../../Source/ChordDisposition.h) ist im Adapter auf geeignete
Pop-Flächen begrenzt; Score besitzt dennoch Umkehrungen und Registerstimmführung.
Der bestehende Herrmann-Profileintrag ist weiterhin `harmonySelectionOnly`: Er nutzt
Harmoniegewichte und neutrale Policies, keine bereits implementierte Herrmann-Grammatik.

## 2. Gemeinsame Bausteine, unterschiedliche musikalische Absichten

| Gemeinsames Verfahren | Williams-Schwerpunkt | Herrmann-Schwerpunkt laut neuer Forschung |
|---|---|---|
| Vorräte und Klangobjekte | Oktatonische Rollenbeziehungen, Hexatonik und modale Kontexte; bestehende H12/H14/H17/H19 bzw. H24/H25 liefern anschlussfähige Harmonik. | Klangobjekte mMaj7/Aug/ø7, Ganztonbeziehungen und hexatonische Verbindungen; **keine durchgängige Oktatonik als gesichertes Herrmann-System behaupten**. Ein geschichteter Klang muss nicht auf eine Skala reduziert werden. |
| Bass/Pedal | Beweglicher Systembass, Dissonanzbass, Pedal als eine Möglichkeit; etwa B07/B09/B31/B33/B35 als spätere geprüfte Anwendungsfälle. | Halbton-/Tritonuspedal, Pendel, Bassinterpunktion und Gegenbewegung. Gemeinsames oder tiefes/hohes Pedal kann den Klangwechsel überdauern. |
| Repetition und Entwicklung | Erkennbare Reprise, Sequenz, kurze Zellen und später längere gerichtete Bögen. | Kurze Zellen, bewusst unveränderte Wiederholung, modulare Unterbrechung/Kürzung und später Liquidation. Permanente Variation wäre hier ebenfalls ein musikalischer Fehler. |
| Polyklang und Rollenbeziehung | Polychorde, parallele Dreiklänge, koordinierte Action- und Mystery-Schichten; z. B. H22/H68/H71 und Planing H58/H60/H70. | Zwei Mollkomponenten im Halbton-/Tritonusabstand als besondere Klangoption; getrennte Einsätze/Register für latente Spannung, synchronere/parallele Führung als mögliche Zuspitzung. |
| Langzeitverlauf | Zielbewegung, Umharmonisierung, motivische und abschnittsübergreifende Entwicklung. | Verweilen, wiederkehrende Blöcke, Register-/Rollenwanderung und allmähliche Verschmelzung; auch Lyrik und lange Linien bleiben zulässig. |

Das sind **Präferenzen und konkrete spätere Planungsregeln**, keine Verbote für
andere Verfahren. Aus der Recherche folgen weder eine allgemeine Melodiesperre
noch verpflichtende Pedale, eine feste Zahl aktiver Rollen oder Polyakkorde nur
oberhalb einer erfundenen Intensitätsschwelle. Herrmanns klangliche „Fusion“ ist
nicht vollständig aus MIDI ableitbar: Synchronität, Abstand und Parallelführung
sind planbar; Homogenität, Sordino oder Obertonschärfe externer Patches sind unbekannt.
Velocity ersetzt diese Eigenschaften nicht. Die neuen acht XYZ-Eckbeschreibungen
sind Forschungsmodelle, keine bereits validierten Anker oder Abdeckungsmessung.

## 3. Abhängigkeiten und Konsequenzen für den Williams-Fahrplan

**Tonvorrat, Akkorddefinition und Schichtzugehörigkeit trennen.** Ein größerer
Akkordtyp löst nicht die melodische Zulässigkeit seiner Umgebung; eine gemeinsame
Maske ersetzt keine zwei Schichten. Zunächst nur den Kontext und die Verbraucher
erweitern, die der nächste musikalische Test braucht. Kein allgemeiner Systemkatalog
oder neuer Symbolparser auf Vorrat.

**Bassabsicht getrennt autorisieren.** Harmonieanker, feste Bassvorgabe, frei
bewegte Linie und unabhängiges Pedal haben verschiedene Aufgaben. Explizite
Slash-Bässe und beide Follow-Stellungen müssen klaren Vorrang/Fallback behalten.
Eine gewünschte Dissonanz darf außerhalb der Oberklangmaske liegen, ohne automatisch
Fehler oder aufzulösender Durchgang zu sein. Das hebt Register-/Dauerregeln nicht auf.

**Mehrschichtigkeit braucht mehr als Tonklassen.** Vor einem Polychordimport müssen
Komponenten, getrennte Register, Einsätze und Notenbesitz definiert sein. Erst dann
lassen sich gleichzeitige Reibung und zeitversetzte Klangflächen unterscheiden.
Ein einzelner zusätzlicher Klangtyp ist davon unabhängig und kann früher folgen.
Planing, metrische Koordination und Vorratskontext sind keine vollständigen
gegenseitigen Voraussetzungen; nicht alles zu einem großen Umbau bündeln.

**Vorhandene Zeitbasis und Instrumentenprüfung weiterverwenden.**
[MusicalTime.h](../../Source/MusicalTime.h) und
[MusicalExecution.h](../../Source/MusicalExecution.h) bieten 64-Bit-Ticks/960 PPQ,
nominale Harmonie und Groove-Ereignisse. 320-Tick-Triolen sind darstellbar, aber noch
kein angebundener Vorlagengenerator. Acht Slots/ganze Takte bleiben eine Grenze
des Harmoniemodells, keine erneut zu öffnende Scheduler-Baustelle. Halbtaktige
Harmonie ist keine Voraussetzung für ein unabhängiges Pedal oder zwei überlagerte
ganztaktige Klänge.

Die neun MIDI-Ziele sind keine neun frei austauschbaren Harmonieschichten.
Lang-/Kurzpatches dürfen unterschiedlich sein; Dialog besitzt intern Polyphonie 2,
Melodie 1 und kann deshalb keinen zweiten Dreiklang übernehmen. Der Stich bleibt
fester Trigger. Erst geeignete Rollen/Ziele validieren, dann ausgeben; keine
stille Umadressierung. Ob spätere konkrete Schichtstudien zusätzliche gleichartige
Ausgänge benötigen, ist offen und kein Anlass für eine jetzige Routingänderung.

Die Williams-Fortschreibung stellt Kontext und Bass bereits hoch. Diese Richtung
wird bestätigt. Gegenüber der **historischen** Reihenfolge P2 Klangtypen → P3 Rhythmus
→ P4 Kontext empfiehlt sich jedoch, den ersten wirklich benutzten Kontext früher
anzusetzen und kleine Pedal-/Bass- und Modulaufgaben vor komplexe Langphrasen zu
ziehen. Planing und minimale Synchronitäts-/Registerkoordination sollten ebenfalls
nicht pauschal bis nach langer Melodieplanung warten. Das verbessert spannungsvolle
Musik auch bei ausgeschalteter Melodie und Gegenstimme. Die 27 noch offenen
Williams-Harmonien behalten ihre dokumentierten Voraussetzungen; kein Ersatzimport.

Insbesondere Williams H47/H48 und die äußersten Unruhebereiche werden durch einen
neuen Kontext oder mehr rhythmische Aktivität allein nicht vollständig erschlossen:
Exakte Mengenklänge beziehungsweise das Halbtakt-/Slotmodell fehlen weiterhin.
Die P1-Abdeckung bleibt der dokumentierte Stand; aus Herrmanns acht Eckbeschreibungen
wurde keine neue numerische Katalogabdeckung berechnet.

## 4. Empfohlene kleine Schritte nach der P1-Hörabnahme

Reihenfolge als Vorschlag, **nicht als freigegebene Implementierungsserie**:

| Schritt | Begrenztes Ergebnis | Konkretes Prüfkriterium |
|---|---|---|
| 0 – Forschung nacharbeiten | Herrmann-Klangpaare, Bass/Pedal und kurze Zellen als exakte transponierbare Vorlagen/Modellstudien mit Evidenz, Dauern und Rollen ausarbeiten. | Eindeutige Noten, Bass, Register, Funktion, Zyklus und Varianten; Originalquellen/Interpretationen/Konstruktionen getrennt. Kein Import ungeklärter Beispiele. Kann schon dokumentarisch parallel zur Hörabnahme erfolgen. |
| 1 – Ein gemeinsamer Kontext mit echtem Verbraucher | Zunächst ein expliziter oktatonischer Kontext für einen bestehenden Williams-Score-Motivpfad; enger Umfang, kein bloß unbenutztes Maskenmodell. Zentrum, Gültigkeit, erlaubter Nicht-Akkordton und Originalmaterial unterscheiden. | Alle zwölf Transpositionen; tatsächlicher Vorratston außerhalb eines Akkords bleibt bei korrekter Funktion erhalten; unbekannter Kontext unverändert; Originalsicherheit, XYZ-Wechsel, Reprise und Live/Export. Anschließend Hexatonik/Lydisch, für Herrmann bedarfsgerecht Ganzton. |
| 2 – Eine unabhängige Bass-/Pedalabsicht | Zuerst ein ausdrücklich notiertes Pedal mit eigener zeitlicher Gültigkeit; danach eine kurze transponierbare Bassfolge. Bestehende Bassplanung/Instrumentenprüfung nutzen. | Fester Pedalton unter zwei Oberklängen, nachweisbarer Halbton-/Tritonusbezug und korrektes Ende; Slash-/Follow-/Manuell-Konflikte führen zu definiertem Fallback. Kein Pflichtpedal. |
| 3 – Kurzes Modul mit Wiederholungsfunktion | Vorhandenes Motivmaterial und P1-Einsatzpläne für ein kontinuierliches oder ein unterbrochenes Modul nutzen; zuerst zwei Rollen, keine Formgrammatik. | Unveränderte Zellidentität über mehrere Wiederholungen; bewusste Pause/Interpunktion, keine Score-Mindestpause im kontinuierlichen Ostinato, keine konkurrierenden Notenansprüche. |
| 4 – Eine genaue Lagenbewegung / Rollenbeziehung | Planing als begrenzte Alternative zur kleinsten Stimmbewegung; getrennt davon ein Test „versetzt vs. synchron“ mit zwei bestehenden geeigneten Rollen und definiertem Registerabstand. | Gleiche Tonfolge/Rhythmusgrundlage, nachgewiesene Parallelintervalle bzw. Einsatzabstände; keine Registerverletzung. Mehr Intensität muss nicht mehr Anschläge bedeuten. |
| 5 – Konkrete fehlende Klangtypen und erster Zweischichtklang | Kleine exakte Typen unabhängig früher einschiebbar, sobald eine geprüfte Vorlage sie verlangt. Erster Polychord erst mit klarer Komponenten-/Registerbedeutung und ausreichender Kapazität. | Exakte Tonklassen, Transposition, geschützte Farbe; beide Komponenten hör-/messbar getrennt und gemeinsam ausführbar. m1m und m11m dürfen registral nicht verwechselt werden. Kein ungeeigneter Stich-/Dialog-Ersatz. |
| 6 – Bedarfsgerechte Rhythmus-/Zeitdaten | Triolen/Hemiolen, unterschiedliche Zellperioden und danach separat halbtaktige Harmonie/mehr Slots. Bestehenden Dispatcher anbinden. | Richtige Onsets/Dauern und Akzente bei passendem Hostmetrum, kein Abschneiden in unpassendem Metrum, Harmonie swingfrei; Lang-/Kurzfähigkeiten einhalten. |
| 7 – Längere Entwicklung | Erst auf den erprobten Bausteinen: Modulverkürzung, Rollenwanderung, Registerentwicklung und später längere Melodiebögen. | Mindestens 128 Takte bei festem XYZ und langsamen/schnellen Fahrten; erkennbare Kontinuität und zulässige Statik, keine erzwungene Spannungsauflösung oder Dauer-Leadrolle. |

Für jeden späteren Engine-Schritt gelten zusätzlich die Referenzvergleiche für
Neutral/Barry/Pop, Mute/Solo/Motiv/Follow, unbegrenzte Wiedergabe ohne Fahrt,
Seek/Loop/Neustart, Notenbilanz, Blockgrößen, echter Prozessor-Live-/Exportvergleich
und Echtzeit-/Sanitizerprüfungen. Messbare Unterschiede ersetzen keine Hörabnahme.

## 5. Offene Forschungsfragen vor verbindlichen Herrmann-Daten

1. **Konkreter Notationsfehler:** §3 nennt G–B–D einen übermäßigen Dreiklang. Diese Noten bilden G-Dur; übermäßig wäre beispielsweise G–B–D♯. Welche Töne tatsächlich gemeint sind, muss am Beleg geprüft werden. Keine automatische Korrektur im Archiv oder Import.
2. **Begriffsschärfe:** mMaj7 ist nicht wörtlich ein Dur- plus Molldreiklang. Entscheidend sind {0,3,7,11}; tatsächliche Polychorde separat definieren. Die französische Sexte einschließlich Bass/Enharmonik benötigt eine exakte Vorgabe; nicht still durch vorhandenes Dom7 ersetzen. Dom7b9 benötigt dagegen keinen neuen Typ.
3. **Register ist Teil des Materials:** Der berichtete Psycho-Cluster in großen Septimen ist nicht dieselbe Lage wie ein kompakter Halbtoncluster. Halbton-/große-Septim-Schichtung gleicher Tonklassen, Parallelität und Schichtbesitz in Studien ausdrücklich notieren.
4. **Evidenzgrenzen:** Schneller teilweise nur über Snippets; bestimmte Maj7-Parallelen ausdrücklich H. Oktatonik ist für Herrmann nicht als durchgehendes System belegt; Ganzton bei Williams in der kanonischen Forschung nur H. Gemeinsame Technik darf nicht in eine unbelegte Stilbehauptung umschlagen.
5. **Klangwirkung:** „Verschmelzung“ und Dissonanzkennzahlen sind zu prüfende musikalische Modelle, keine gemessenen universellen Bedrohungswerte. Sordino lässt sich nicht durch Velocity vortäuschen; externe Patchfähigkeiten sind nicht bekannt. Keine Neuzuordnung der XYZ-Achsen aus einem Forschungsrezept ableiten.

Archivintegrität: Der neue Bericht wurde unter verkürztem Dateinamen bytegleich
übernommen (52 801 Bytes; SHA256
`1cd1506276cc3f8da7b4bcd7ca8a0f68fccbfc0a4a458e5afc48e5085fd43005`).
Keine Originaltexte korrigiert, keine Vorlagen erzeugt, keine musikalischen Tests
neu als Hörabnahme ausgegeben. Dieser Dokumentationsstand wartet gemeinsam mit
Williams P1 auf die nächsten Entscheidungen des Anwenders.

## 6. Zukünftiger SYNTH-Modus als gemeinsame Anforderung

Die [übergeordnete Projektentscheidung](../MUSICAL_DIRECTION.md) sieht langfristig
SCORE, SYNTH und POP/ROCK mit demselben Kompositionskern vor. Für SYNTH sind Neutral
Electronic, John Carpenter, Harold Faltermeyer, Jan Hammer, Vangelis, Tangerine
Dream und Jean-Michel Jarre vorgesehen. Carpenter hat wegen KADAITCHA hohe
Forschungspriorität; Referenzschwerpunkt sind *The Fog*, *Christine* und die
elektronischen Passagen aus *The Thing*. Noch keine recherchierte Synth-Stilgrammatik
oder umgesetzte zusätzliche Betriebsart behaupten.

Das ergänzt die gemeinsamen Erweiterungen aus diesem Bericht um folgende
Anwendungsfälle, ohne ihre Implementierung vorwegzunehmen:

| Gemeinsamer Baustein | Zukünftige elektronische Anforderung |
|---|---|
| Kurze Module / Motivverwendung | Eigenständige Sequencer-Figuren und hypnotische Ostinati mit minimaler oder bewusst ausbleibender Variation; kontinuierliche Wiederholung von phrasierender Wiederkehr mit Pause unterscheiden. |
| Koordinierte Einsatzpläne | Ineinandergreifende Schichten, unabhängige Zykluslängen und kontrollierte Phasenverschiebungen; mechanische Präzision muss als musikalische Option erhalten bleiben. |
| Bass- und Harmonieabsichten | Harmonisch unabhängige Basssequenzen und bewusst statische Harmonik; nicht jede Sequenz auf den jeweils nächsten Akkordton reduzieren. |
| Längere Entwicklung | Schichten hinzufügen, entfernen und neu kombinieren, während Material und Puls erkennbar bleiben; Entwicklung benötigt nicht ständig neue Harmonien oder stärkere Motivvariation. |

Die Entscheidung rechtfertigt keine weitere Scheduler-Migration, universelle
Sequencer-Plattform oder getrennte Künstlerengines. Konkrete Tonvorräte, Figuren,
Zyklen und Präferenzen werden erst durch die jeweilige Forschung spezifiziert;
etwa Oktatonik ist keine automatisch übertragene Carpenter-Vorgabe. Die Instrumentierung
bleibt unabhängig: Die Verfahren sollen sowohl mit Orchesterpatches als auch
mit Synthesizern nutzbar sein. Percussion, MIDI-CC-Klangbewegungen und zusätzliche
MIDI-Rollen bleiben offene spätere Untersuchungen. Die neun vorhandenen Ausgabeziele
werden zunächst beibehalten; notwendige Erweiterungen erst nach der Forschung entscheiden.

Dies ist eine dokumentierte Zukunftsanforderung, keine neue Implementierungsphase
oder Änderung der Williams-P1-Hörabnahme und des aktuellen musikalischen Verhaltens.
