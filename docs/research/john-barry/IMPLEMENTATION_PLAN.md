# John Barry – Bestandsabgleich und Implementierungsplan, Phase 1

Stand: 25. November 2026. Musikalischer und technischer Ausgangsstand:
`f04b96d` auf `develop/composition-core-prototype`.
Dieser Bericht ist Analyse und Planung; keine der vorgeschlagenen Profiländerungen
wurde implementiert oder hörgeprüft.

## 1. Forschungsgrundlage und Ablage

Die sechs Dateien aus `STROMSCORE_Forschung.zip` wurden unverändert übernommen und
separat als `e3161b6` lokal committet. Sowohl die Arbeitsdateien als auch die sechs
Git-Blobs wurden mit den ZIP-Einträgen byteweise verglichen, einschließlich der
ursprünglichen Zeilenenden.

Maßgeblich sind:

- [Barry-Stilprofil](Stilprofil_John_Barry.txt), vollständig gelesen.
- [Bereinigte Gesamtfassung vom 24.11.2026](../shared/Musikalisches_Vokabular_Gesamtfassung_2026-11-24.txt):
  Lesehinweise, Bereinigung/Aliasregeln, alle Barry-Harmonie-, Rhythmus-, Motiv-,
  Phrasen-, Kombinations- und Entwicklungsabschnitte sowie die gemeinsamen
  Umharmonisierungs-, Stimmführungs-, XYZ-, Korrektur- und Unsicherheitsabschnitte.
- [README der Forschungsbibliothek](../README.md).

`archive/` dokumentiert die Vorgeschichte, zählt aber **nicht zusätzlich als
Vokabular**. JB-H33 ist ein Alias von JB-H18; JB-R16 und JB-R23 werden ebenfalls
nicht als zusätzliche unabhängige Formen gezählt. Das neue Gegenspielermotiv ist
JB-M26, nicht die bereits anderweitig belegte ID JB-M21.

Für diesen Abgleich ergeben sich 46 kanonische JB-H, 25 JB-R, 26 JB-M, 20
Barry-Phrasen (P/L/A/F), sechs JB-RC und sechs JB-D. Gemeinsame B/H-Vorlagen werden
nur einmal gezählt. Die Gesamtfassung enthält darüber hinaus Herrmann-Material;
„BH“ in ihren IDs bedeutet **Bernard Herrmann**, nicht *The Black Hole*.

Die Unterlagen sind musikalische Forschung, keine Anweisung zur automatischen
Implementierung aller dort skizzierten Module. Die konkrete Aufgabenstellung
begrenzt diese Phase auf Dokumentation.

### Evidenzgrenzen

[N] bezeichnet laut Sammlung ein belegtes Verfahren, [I] eine Interpretation,
[H] eine Hypothese, [E] eine eigene Konstruktion. Auch eine mit [N] verbundene
Vorlage ist keine Transkription: Die konkreten Töne und Raster bleiben [E].
Die Quellen und Zitate wurden hier nicht durch ein neues Partiturstudium oder
externe Recherche unabhängig verifiziert. Phrasenstatistiken der Sammlung messen
32 eigene Entwürfe und keine repräsentative Stichprobe von Barry-Kompositionen.

Die charakteristische Kombination ist wichtiger als ein einzelnes Akkordsymbol:
wenige lange Farbakkorde, ein begrenztes Ostinato, Pedal/Fundament, sparsame obere
Gedanken und Schichtwechsel bei unverändertem Hosttempo. Warme, lyrische,
melancholische und actionorientierte Bereiche gehören ausdrücklich dazu.

## 2. Was heute tatsächlich vorhanden ist

### Gemeinsamer Datenpfad

Der aktuelle produktive Katalog enthält **87**, nicht mehr 84 Wendungen:
48 Score und 39 Pop/Rock, darunter WC-H01/H11/H19 als 2037/2038/2039.
Die drei zuletzt importierten WC-Vorlagen stehen ausschließlich im Pop/Rock-Pool.

Authoring-Dateien: `data/harmony/catalog.json`, `chord_types.json`,
`arrangements.json`, `profiles.json`, `notes.json`. Der Generator
`scripts/generate_harmony_catalog.py::_validate()` prüft IDs, Typen, Tonklassen,
Basstöne, Dauer, XYZ, Genre-, Quellen- und Profilreferenzen sowie potenzielle
harmonische Dubletten. Er erzeugt statische Header. `HarmonyRuntime.h` verbindet
Harmoniedaten mit getrennten Standard-Spielrezepten; keine JSON-Datei wird im
Audiothread geladen.

Die **acht musikalischen Slots** tragen weiterhin ganzzahlige Dauern von 1–8
Takten; die Summe ist exakt acht. Die 16 Plätze in
`CompositionCore.h::HarmonicRequest` sind acht Akkorde plus mögliche
Zwischendominanten, keine Freigabe für 16 frei notierte Akkordwechsel.
Die gemeinsame 64-Bit-Zeitbasis mit 960 PPQ und der Dispatcher sind bereits
vorhanden. Das allein erlaubt noch keine halbtaktigen Katalogdauern.

### Bereits auswählbares Barry-Profil

`data/harmony/profiles.json` definiert Barry als `harmony_selection_only=true`.
`CompositionPolicy.h::compositionProfiles` weist **allen drei Profilen dieselbe
`neutralFreePolicy`** zu. `PluginProcessor.cpp::currentSettings()` übernimmt sowohl
Profilidentität als auch Policy bereits in den Generator. Die Verbindung muss
nicht neu erfunden werden; eine eigene Barry-Policy existiert aber noch nicht.

`Generator::pick()` gewichtet aktuell die nach XYZ/Variety zulässigen Wendungen
mit den positiven Barry-Faktoren. Beispiele: 1005, 1006, 1007, 1017, 1034 und
1038 jeweils 1,8. Das sind vorläufige Auswahlpräferenzen, keine vollständigen
Stilregeln. 1006 enthält etwa **Min7**, nicht MinMaj7: Name oder bisheriger Faktor
beweisen daher keine Übereinstimmung mit dem neuen Forschungsschwerpunkt.

## 3. Harmonische Vorlagen und Akkordtypen

### Ergebnis der technischen Einzelprüfung

Alle **46** kanonischen Barry-Harmonievorlagen wurden aus den tatsächlichen
Tabellen gelesen. Geprüft wurden Symbole, relative Grundtöne, ausgeschriebene
Tonklassen einschließlich Slash-Bass, Dauer und Slot-Anzahl gegen den aktuellen
Datenpfad. Ergebnis:

- Alle 46 summieren sich auf acht **ganze** Takte.
- Slot-Verteilung: neun Ein-Akkord-, 21 Zwei-Akkord-, drei Drei-Akkord-, zwölf
  Vier-Akkord- und eine Acht-Akkord-Vorlage (JB-H46).
- Alle benötigten 15 Akkordtypen sind bereits unter den **27 internen Typen**
  definiert. Keine neue Akkorddefinition und keine Erweiterung des Zeitmodells
  ist für diese 46 Harmoniegerüste erforderlich.
- Ein Datenimport benötigt trotzdem stabile neue produktive IDs, Quellenreferenz,
  feste einzeln geprüfte XYZ-Anker, Genre-Eignung und ein gültiges Spielrezept.
  Forschungs-IDs wie JB-H01 sind Quellenidentitäten, keine bestehenden
  `WendungId`-Werte.
- Sprachliche Angaben wie „C-Moll“, „phrygisch“, „lydisch“ oder wechselnde Zentren
  sind nicht automatisch eine gültige `Mode`-Vorgabe. Das muss separat geprüft
  werden; `automatic` darf die harmonischen Daten unverändert bereitstellen,
  ohne eine eindeutige modale Melodieregel zu behaupten.

Benötigte Typen: `Maj`, `Min`, `Maj7`, `Min7`, `Dom7`, `MinMaj7`, `MinMaj9`,
`Min6`, `Add9`, `Sus2`, `Sus4`, `Fifth`, `DiminishedTriad`, `Dominant7Sus4`,
`Major7Sharp11`. `Dim7` darf nicht stellvertretend für den verminderten
**Dreiklang** importiert werden. Moll-add2/add9 ist ebenfalls bereits als
`MinorAdd9` vorhanden. `Major7Sharp5` ist vorhanden, obwohl es für die 46 JB-H
nicht benötigt wird. Der m6/9-Klang aus dem Stilprofil besitzt noch keinen eigenen
Typ; er ist ein möglicher späterer Datenzusatz innerhalb der heutigen
Fünf-Ton-Grenze, keine Voraussetzung dieser ersten Auswahl. Freie Polychords und
gezielt festgelegte obere Quartenlagen sind nicht dasselbe wie ein vorhandenes
Akkordsymbol `Quartal`.

Der benutzerseitige Custom-Akkordselektor enthält weiterhin 18 Typen. Die internen
27 Typen dürfen deshalb nicht als 27 bereits auswählbare GUI-Akkordtypen
beschrieben werden.

### Vergleichsmaßstab

Verglichen wurde in Bezugstonart C über alle 87 produktiven Einträge: geordnete
acht Takte mit Grundton, **definierter oberer Akkordtonklassenmenge** und
explizitem/equivalentem Grundtonbass. Dauern und Reihenfolge bleiben relevant;
Namen, Instrumentierung und XYZ zählen nicht als harmonische Identität.
Automatische spätere Färbung zählt nicht als fest vorhandenes Vorlagenmaterial.
Transposition auf eine andere Bezugsstufe, andere Schleifenphase oder anderes
Wechseltempo wurde nicht stillschweigend zur exakten Dublette erklärt.

Nur **JB-H40 = 1003** ist nach diesem Maßstab vollständig vorhanden. Das bedeutet
nicht, dass 45 musikalisch völlig neue Erfindungen vorliegen: Viele verwenden
bekannte Klänge und Fortschreitungsfamilien, aber in anderer Zeit-, Bass- oder
Farbkonstellation. Die folgende vollständige Liste nennt solche Nachbarn bewusst
als **Teilmaterial**, nicht als Ersatzvorlagen. `D` bedeutet: Harmoniegerüst als
Daten importierbar; die beschriebenen Linien, Rhythmen und Entwicklungen sind
nicht automatisch mit implementiert.

| Forschung | Harmonie und Takte | Bestand / benötigte Anpassung |
| --- | --- | --- |
| JB-H01 | `CmM7×8` | D; 1005/1007: mM-Farben nur innerhalb bewegter Folgen; statisches mM7 fehlt. |
| JB-H02 | `Cm6×8` | D; 1019/1011/1015: m6 vorhanden, acht Takte auf einem Klang fehlen. |
| JB-H03 | `Cadd9×8` | D; 1035: add9 vorhanden, aber kein statisches Acht-Takt-Feld. |
| JB-H04 | `Cmaj7×8` | D; 1038: Maj7-Farbe vorhanden, dort F–C im Zwei-Takt-Wechsel. |
| JB-H05 | `CmM7×4 → EmM7×4` | D; 1005: andere Grundtonbeziehung und andere Dauern; kein mM7-Großterzpendel. |
| JB-H06 | `Cmaj7×4 → Gmaj7×4` | D; 1038: verwandtes Maj7-Pendel, aber andere Stufen und Wechselrate. |
| JB-H07 | `Cm×4 → Abmaj7×4` | D; 1020: dieselben beiden Klänge, dort zweimal 2+2 statt 4+4. |
| JB-H08 | `Cm×4 → Bb/C×4` | D; 1022/2008: verwandte bVII-Farbe, aber kein identisches Slash-Pedal. |
| JB-H09 | `Cm×2 → Abmaj7×2 → Bb×2 → Cm×2` | D; 1020/1048: nur Teilklänge; die vollständige Folge fehlt. |
| JB-H10 | `Cm×4 → Fm×2 → Cm×2` | D; 1007/1017: Moll-Plagal als Teilmaterial; andere Folge. |
| JB-H11 | `Cadd9×4 → Fmaj7/C×4` | D; 1035: warme add9/Maj7-Klänge, Slash-Pedalfolge fehlt. |
| JB-H12 | `Csus2×4 → Csus4×4` | D; 1029/1035: Sus/add-Material; konkretes terzoffenes Pendel fehlt. |
| JB-H13 | `CmM7×4 → C#mM7×4` | D; 1001: Halbton und mM7, aber nicht dieses mM7-Pendel. |
| JB-H14 | `Cm×4 → F#m×4` | D; 1014: Moll-Tritonus als Teilfolge; keine langsame reine Zweiklangform. |
| JB-H15 | `Cmaj7×4 → Ebmaj7×4` | D; 1038/1042: Maj7 bzw. Medianten, nicht das konkrete Maj7-Paar. |
| JB-H16 | `Cmaj7×4 → D/C×4` | D; 1039: lydisch verwandtes Obermaterial, explizites D/C fehlt; Modus offenlassen. |
| JB-H17 | `C×4 → Bb/C×2 → F/C×2` | D; 1047/2037: I–bVII–IV-Familie, andere Dauern/Bässe und Genrebindung. |
| JB-H18 | `C5×8` | D; 1032/2039: Quintklänge, aber jeweils bewegte Grundtöne. |
| JB-H19 | `Cm×4 → Dbmaj7×4` | D; 1002/2001: gleiche Wurzeln und 4+4, jedoch Db statt Dbmaj7. |
| JB-H20 | `Cm×2 → Db×2 → Cm×2 → Db×2` | D; 1002: gleiche Klangfamilie, andere Wiederholung und Dauern. |
| JB-H21 | `Cmaj7×4 → Cm6×4` | D; 1034: Dur/Moll-Eintrübung, aber nicht Maj7–m6. |
| JB-H22 | `Fmaj7×4 → Fm6×4` | D; 1034: F–Fm als Teilmaterial, nicht Fmaj7–Fm6. |
| JB-H23 | `Cm×2 → Cdim×2 → Cm×2 → Cdim×2` | D; 1011: vermindertes Material, aber Dim7 statt vermindertem Dreiklang und andere Folge. |
| JB-H24 | `Cm×2 → C#m×2 → Dm×2 → D#m×2` | D; 1014: Chromatik vorhanden, keine identische Halbton-Mollreihe. |
| JB-H25 | `CmM9×8` | D; 1005: mM9, aber nur 4+2 Takte mit anderem Mittelklang. |
| JB-H26 | `Cm7×4 → Fm7×4` | D; 1006: exakt dieselben Klänge, dort viermal zwei Takte statt 4+4. |
| JB-H27 | `C×2 → G×2 → D×2 → A×2` | D; 1042: Dur-Rückungen, andere Intervalle. |
| JB-H28 | `F×2 → C×2 → F×2 → C×2` | D; 1038: gleiche Wurzeln/Dauern, aber Maj7 statt Dur-Dreiklängen. |
| JB-H29 | `Cm×2 → Bb×2 → Ab×2 → G×2` | D; 2010: nahe Andalusienform, Schluss G7 statt G; Pop/Rock-Pool. |
| JB-H30 | `Cm×2 → Cm/Bb×2 → Abmaj7×2 → G×2` | D; 2011/1004: Lamento-/Mollmaterial, andere Bässe und Farben. |
| JB-H31 | `G7sus4×4 → G7×4` | D; 1035/1041: Sus bzw. Dominantmaterial, kein G7sus4–G7-Pedal. |
| JB-H32 | `CmM7×4 → Cmaj7×4` | D; 1007/1034: Dur/Moll-Farben, konkrete mM7–Maj7-Folge fehlt. |
| JB-H34 | `Cm×2 → Abmaj7×2 → Fm×2 → Dbmaj7×2` | D; 1004: verwandte Mollfolge, andere Farben und Schlussstufe. |
| JB-H35 | `Cmaj7×4 → F#maj7×4` | D; 1042/1012: Dur-Rückungen, konkrete Tritonus-Maj7-Folge fehlt. |
| JB-H36 | `Cm×4 → Fm×2 → C×2` | D; 1034/1007: Plagal-/Dur-Moll-Material, andere Dauern und Schlussbildung. |
| JB-H37 | `C×2 → Bb/C×2 → Ab/C×2 → G/C×2` | D; 2010/1047: absteigende/bVII-Klänge, kein konstantes C-Slashfundament. |
| JB-H38 | `CmM7×4 → Cdim×4` | D; 1001/1011: mM7 und Verminderung nur in anderen Folgen. |
| JB-H39 | `Cm×2 → Cm/B×2 → Cm×2 → Cm/B×2` | D; 1003: oberer Cm bleibt; bewegter B-Bass fehlt. |
| JB-H40 | `Cm×8` | EXAKT 1003 (Harmoniedaten); dessen XYZ und Ausgestaltung sind anders. |
| JB-H41 | `Cm×4 → Fm×4` | D; 1007/1017: Cm–Fm als Teilfolge, nicht reines 4+4. |
| JB-H42 | `Cmaj7#11×8` | D; 1039: lyrisch/lydisches Umfeld, kein statischer maj7#11-Klang. |
| JB-H43 | `Cmaj7×4 → Dmaj7×4` | D; 1039: C/D-Klangfamilie, andere Typen und Dauern. |
| JB-H44 | `C×8` | D; 1043/1047: C-Dur als Teilklang; acht Takte rein statisch fehlen. |
| JB-H45 | `C×4 → F/C×4` | D; 1036/1034: I–IV-Material, kein explizites F/C und kein 4+4. |
| JB-H46 | `C×1 → G×1 → D×1 → A×1 → E×1 → B×1 → F#×1 → C#×1` | D; 1042/1032: Rückungen, keine identische Acht-Akkord-Quintenreihe. |
| JB-H47 | `Cmaj7×2 → F#maj7×2 → Cmaj7×2 → F#maj7×2` | D; 1042/1012: Dur-Rückungen, nicht dieses Tritonus-Maj7-Pendel. |

### Färbung, Modi und Bass sind getrennte Entscheidungen

Alle heutigen 48 Score-Vorlagen verwenden flexible Färbung. In
`HarmonyTypes.h::coloredChordType()` wird Moll ab Z=0,45 zu mM7 und ab Z=0,75
zu mM9; Dur wird ab Z=0,45 zu Maj7. Deshalb ist beispielsweise 1003 bei mittlerem
Z in der Fläche ein mM7-Feld, aber **keine geschützte mM7-Vorlage**.
`counterLadder()` und die Arp-Tonleiter verwenden weiterhin die notierte
Akkorddefinition; eine gefärbte Fläche bedeutet also nicht automatisch denselben
erweiterten Tonvorrat für alle Stimmen. Das ist eine nützliche vorhandene
Klangmöglichkeit, kein vollständiger Ersatz für JB-H01.

Ein späterer Import bewusst definierter Barry-Klänge sollte die vorhandene
Strategie `protected` nutzen. `allowsPassingHarmony()` unterbindet dabei auch
ungeplante Zwischendominanten; `authoredPitch()` verhindert bestimmte automatische
Begleitverzierungen außerhalb des definierten Materials. Umkehrung,
Oktavierung, Dynamik und rhythmische Gestaltung bleiben möglich. Ein geschütztes
CmM7 muss nicht jederzeit mit allen vier Tonklassen gleichzeitig erklingen.

Das Modusmodell kennt **Ionisch, Mixolydisch, Dorisch, Äolisch**, aber kein Lydisch,
Phrygisch, harmonisches Moll oder chromatisches Pedalfeld als Melodiestrategie.
Eine mM7-Folge passt gewöhnlich in keinen der vier vollständigen Tonvorräte;
`modalContext()` meldet dann incompatible statt einen falschen Modus zu erfinden.
Das verhindert nicht die Akkordausgabe, sondern nur die entsprechende modale
Durchgangstonanwendung. JB-H16/H42 dürfen nicht als Ionisch deklariert werden,
um eine Validierung zu umgehen.

`Chord.bass`, `bassRoot()`, `pedalRoot()` und `chordFor()` unterstützen explizite
Slash-Bässe und Pedale. „Folgt Akkorden“ AUS ist jedoch **keine beliebige
Pedaltonwahl aus der Forschung**: Bei produktiven Vorlagen wird auf das
Grundfundament der gewählten Tonart zurückgegangen, Slash-Bass wird dabei
zurückgesetzt. `BassPedal` verwendet dagegen den Bass des ersten Akkords.
Ein vorgeschlagenes F-Pedal bei JB-H22 oder G-Pedal bei JB-H31 ist deshalb
nicht automatisch die Ausgabe beider Follow-Zustände. Diese absichtliche
Benutzereinstellung bleibt erhalten; Quellenempfehlungen überschreiben sie nicht.

## 4. Rhythmus, Ostinati, Bass und Pedale

| Forschung | Heute nutzbarer Mechanismus | Was für die konkrete Vorlage noch fehlt |
| --- | --- | --- |
| JB-R01, R02, R12 | `BassHalf`, `BassQuarter`, `BassHeld`, `PadHeld`, `sustained()` | Exakte Dauern/Akzente sind nicht immer gleich: BassHalf endet nach sieben statt acht Sechzehnteln. Keine importierbaren R-Datensätze. |
| JB-R03, R04, R13, R21, R25 | Auto-/manuelle Arp-Raten, Auf/Ab/Kreisen, Achtel-/Sechzehntelbass | Einsatzdichte ist vorhanden, aber noch kein stabiles profilgewähltes R-Raster samt eigener Akzentfolge. R21/R25 sind zudem ausdrücklich schwach belegte Randbereichsentwürfe. |
| JB-R05, R26 | Einzelausgabe in Vierteln/Achteln/Sechzehnteln; vorhandene Motivaugmentation | Geplante Diminution einer Oberzelle bei **unverändertem** unteren Ostinato. Globale Intensitätserhöhung oder `rhythm`-Variation verkürzt nicht diesen ganzen Zusammenhang. |
| JB-R06 | Tatsächlicher Motivspeicher, Wiederkehr, Fragment/Sequenz | Kein A–A–B-Plan und kein bewusstes A′ mit nachfolgender B-Phrase. |
| JB-R07, R19 | Szenenbeginn, Aufbau, EndHard/EndFade/EndOpen, Dichtemaske | Kein frei platzierter planbarer Schlag–Stille-Abschnitt und kein frei wählbarer achtstufiger R19-Ablauf. |
| JB-R08, R09, R22, R24 | BassPulse/Quarter/Held, PadPulse, Akzente | Mehrstimmig geplante Zeitlupen-/Paukenmarschvorlage mit genauem Akzentraster fehlt. Stich ist nicht automatisch eine gestimmte Pauke. |
| JB-R10, R14, R18, R20 | Funk-/Gallop-/Heartbeat- und andere vorhandene Synkopen; einige Pop-Hooks | Kein beliebiger Score-Synkopenrasterimport. Ähnliche Einsatzpositionen sind kein Nachweis derselben Bass-/Oberstimmenfunktion. |
| JB-R11, R17 | `Meter::from()`, 6/8-Gruppierung, 3/4, metergerechte Arpeggios | Exakte zwei Hauptschläge bzw. die konkrete Bassfolge auf 1 und 2 sind nicht durch jede vorhandene Bassspielweise garantiert. |
| JB-R27 | Deterministische sparsame Tupfer | Nicht das notierte Vier-Takt-Muster; automatische Zusatzfarbtöne und Aktivierungslogik sind weiterhin eigenständig. |
| JB-RC01–RC06 | Bestehende Rollenpläne, Ein-/Ausblenden, Motiv-/Auto-Arp-Reservierungen | Keine sechs gespeicherten gemeinsamen Mehrstimmen-Einsatzpläne. Ein passender Bass plus passender Arp ist noch keine RC-Realisierung. |

`chooseArp()` wählt im Auto-Modus eines von zwei Rezeptmustern der aktuellen
Wendung, nicht aus profilabhängigen Ostinatopräferenzen. `playArpeggio()` führt
sie innerhalb der harmonischen Region aus; bei Follow EIN beginnt die Figur
relativ zum Akkordanfang und erhält einen deterministischen Hashversatz. Das
ist kein szenenlang unverändertes, gehörtes Ostinatomaterial mit eigener Identität.

`autoArpeggioDuration()` wählt neutral bei Intensität <0,15 Viertel, <0,50 Achtel,
sonst Sechzehntel. Einige Figuren (`arpeggioPeriod()`) erzwingen zusätzlich
Sechzehntel. Eine alleinige Änderung der beiden Schwellwerte löst also nicht jede
Tempoentscheidung. Ein zukünftiges bewusstes Achtellimit muss auch Y=1 korrekt
behandeln; `eighthBelow=1` allein tut das wegen des strikten Vergleichs nicht.

Besonders für *The Black Hole* relevant: `BassPendulum` spielt tatsächlich kleine
Terzen, schaltet aber ab Z=0,5 auf einen Halbton und bei Y>0,6 von Vierteln auf
Achtel. `rawBassPattern()` erzwingt bei Y>0,92 Achtel und ersetzt schon ab Y>0,8
Held/Half/Quarter/Pedal durch Achtel. Ein konstanter dunkler Motor ist deshalb
vorhanden, aber seine Intervall- und Daueridentität ist nicht frei von XYZ.
Diese Entscheidungen stehen noch im Adapter und nicht in einer Barry-Policy.

`BassPedal`/`BassHeld` können ein ruhiges Fundament erzeugen. Es existiert weder
für jedes Pedal automatisch ein extrem tiefes Register noch ein eigenständiger
Barry-Lamentobassplan. Die neuere melodische Bassphrasenplanung in
`BassPhrase.h::planBassPhrase()` wird in `melodicBassAllowed()` ausschließlich
für geeignete automatische Pop/Rock-Situationen in 4/4 aktiviert. Sie ist ein
wiederverwendbarer Baustein, keine bereits aktive Score-Basskomposition.

## 5. Motive, lange Phrasen und musikalische Identität

### Bereits vorhanden

`CompositionCore.h` enthält einen gemeinsamen unveränderlichen Motivkatalog mit
zwei Materialien pro Szene. `RememberedMotif` speichert bis zu acht tatsächlich
verwendete Noten mit Intervallen, Einsätzen, Dauern und ursprünglicher Velocity;
Melodie und Gegenstimme besitzen getrennte `MotifUse`-/Linienzustände.

`motifFor()` verwendet gegenwärtig sieben Anfangsrhythmen und sechs Konturformen
mit drei bis fünf Tönen. Die Folge wird durch `planMotifNote()` harmonisch
realisiert und erst anhand der tatsächlich gespielten Noten zu Gedächtnismaterial.
Die 26 Forschungs-Motive sind deshalb **nicht schon deshalb verfügbar**, weil ein
„Motivkatalog“ existiert. Dieser ist ein Laufzeitgedächtnis, kein Importkatalog
musikalischer Anfangsgesten.

`deriveMotif()` unterstützt unveränderte Rückkehr, Verkürzung einer ausgewählten
Notendauer, eine Schlussfragmentierung, eine kurze Sequenz und Augmentation ×2.
Die Sequenz kopiert konkret eine Zweitonfigur transponiert; sie ist keine
allgemeine Durchführung eines vollständigen langen Themas. Diminution aller
Zeitwerte, Umkehrung, Krebs und beliebige A–A′–B-Entwicklung sind nicht vorhanden.

`motifOccurrence()` plant Wiederkehr in einem achtaktigen Horizont an geeigneten
harmonischen Einsatzstellen. Die neutralen Policy-Abstände sind konfigurierbar,
der Horizont selbst ist derzeit `static constexpr windowBars=8`.
`realizeScoreMotif()` erhält Einsatzzeiten und das stärkste Intervall, begrenzt
andere Intervalländerungen und kann Gates höchstens auf die halbe Länge kürzen.
Ein geeigneter Suffix kann ersatzweise erklingen. Das verhindert die früheren
unbeabsichtigten Blockaden, ist aber keine vollständige Umharmonisierung nach
allen Invarianten der Forschung.

### Eignung der 26 kurzen Grundformen

| Material | Einstufung |
| --- | --- |
| JB-M01, M02, M07, M08, M12, M15, M22, M23, M24 | In passendem konkretem Akkordkontext überwiegend/rein akkordtonbasiert und in der Acht-Noten-Grenze. Gute spätere Initialgesten als Daten; noch kein entsprechender Initialgesten-Datenpfad. Die Kontextliste darf nicht pauschal als für jeden Folgetakt gültig gelten. |
| JB-M03, M04, M09, M10, M13, M14, M16, M17, M19, M20, M21, M26 | Verlangen teils diatonische oder chromatische Neben-, Wechsel-, Vorhalts- oder Zieltöne. Nur die Akkordtonauswahl deckt das nicht. Manche Varianten werden auf anderem Farbakkord vollständig akkordtonfähig; das ist einzeln zu prüfen. |
| JB-M05, M06 | Chromatische Linien über terzoffenem Pedal; durch das vorhandene viermodige Durchgangstonverfahren nicht abgedeckt. Keine beliebigen Nicht-Akkordtöne einfach „freischalten“. |
| JB-M11 | Unaufgelöster Tritonus als eigener Spannungsmarker; kein bereits kontrolliert aufgelöster Durchgang. Nur schwach belegte konkrete Tonfolge. |
| JB-M18, M25 | Je zehn Originalnoten, überschreiten den achtstelligen Speicher und den heutigen Anfangsgestengenerator; zusätzlich Harmonie-/Nebenstimmenprüfung nötig. Nicht still auf acht Töne kürzen. |

`ModalContext.h::planPassingTone()` ist auf einen diatonischen, schrittweise
auflösenden Durchgang zwischen Akkordtönen beschränkt. Der tatsächliche Aufruf
in `addPassingTone()` gilt nur für geeignete phrasenbezogene Pop-Gegenstimmen,
nicht Score und nicht die neue Pop-Hauptmelodie. Score besitzt daneben einzelne
lokale Vorhalts-/Nachbarnentscheidungen; daraus folgt keine allgemeine
Score-Nicht-Akkordtonplanung.

### Lange Phrasen

Alle **20 Barry-P/L/A/F-Entwürfe** wurden in ihren Takttabellen gelesen und die
Summen unabhängig nachgezählt: jeweils 16 Sechzehntel pro 4/4-Takt.
JB-P01–P08 enthalten **11–15**, JB-L01–L08 **19–29**, die A/F-Formen **19–27
Noten**. Bereits der kürzeste Vier-Takt-Entwurf überschreitet somit das heutige
Gedächtnis. Ein größeres Array allein würde weder Gipfel, Zielton, Atemstelle noch
Harmonieverlauf planen.

`freeLinePhrase()`/`planLinePhrase()` planen bereits einen kleinen Gedanken aus
zwei bis vier Kernnoten, gegebenenfalls plus Nachbar, mit Zielton und Atempause.
Dieser Pfad ist auf die freie **Score-Gegenstimme bei Motiv AUS** begrenzt und
orientiert sich an einer konkreten harmonischen Region. Die Hauptmelodie nutzt
diesen Phrasenplan nicht automatisch. Es fehlen ein geplanter Vier-/Acht-Takt-Bogen
über mehrere Akkorde, ein einmaliger Gipfel und ein explizites offenes Frageende
mit verändertem Antwortschluss.

Die H-Verweise der Phrasen sind oft nur Kontextfamilien, keine exakt identischen
Zeitleisten: JB-P01 enthält Fmaj7 im dritten Takt und Cadd9 im vierten, während
JB-H04 rein statisch ist. Beim späteren Import muss die **tatsächliche
Phrasenharmonik** validiert werden; ein Querverweis genügt nicht.

## 6. Stimmführung, Rollen und Dramaturgie

- `buildAnchor()`, `planHarmony()`, `voiceleading::lead()` und die zyklische
  Harmoniefolge können Umkehrungen, Registergrenzen und gemeinsame Töne
  berücksichtigen. `leadEntry()` nutzt an Score-Wendungsgrenzen zuletzt gehörte
  Akkordlage/Bass. Die akzeptierte Einschränkung fehlender Vorgeschichte bei
  kaltem Seek bleibt bestehen.
- Die besondere offene/reduzierte Akkordbesetzung aus `ChordDisposition.h`
  schützt charakteristische Farben und berücksichtigt einen tatsächlich stabilen
  Bass. Ihr Adapteraufruf in `padVoicing()` ist aber derzeit **Pop/Rock-only**.
  Eine nicht enge Lage kann Score schon mit dem bisherigen Anchor/Voice-Leading
  erzeugen; das ist noch keine profilspezifische Score-Besetzungsstrategie.
- `melodicRoleWindow()` und `dialogueMayLead()` binden Melodievorrang an spielbare
  Zeitfenster. `planMelodyHandoff()` kann ein tatsächlich gehörtes Schlussfragment
  von Melodie an Dialog übergeben. Das ist weder eine vollständig komponierte
  JB-F01/JB-F02-Form noch ein allgemeines Reinstrumentierungsverfahren.
- Die vorhandene Dialog–Arp-Antwort und die Melodie–Dialog-Übergabe bleiben
  begrenzt: unter anderem Score, 4/4, Aufbau AUS und ausreichend lange Phrase.
  Ein 3/4-Black-Hole-Kontext hat zwar Arp und Motive, aber nicht automatisch
  dieselbe explizite Übergabefunktion.
- `motifWindow()` lässt automatisches Arp tatsächlichen motivischen Fenstern
  Platz; manuelle Figuren werden respektiert. Für Barry muss dieser Schutz
  erhalten bleiben. Ein dauerndes Ostinato unter einer gleichzeitig führenden
  Melodie ist noch keine frei konfigurierbare Strategie dieser Reservierung.
- Die neue Pop-Rollenatmung aus Schritt C ist vorhanden, wird aber nicht zur
  Score-Barry-Formgrammatik umgedeutet. Der gemeinsame Rollen-/Fähigkeitskern ist
  wiederverwendbar; die genrespezifischen Entscheidungen sind verschieden.

`TexturePolicy` steuert Aktivierung, Hysterese, Mindestaktivzeit, Ruhezone und
Arp-Auto-Temposchwellen. Der Szenenaufbau staffelt Rollen, Endmechanismen dünnen
optionale Ereignisse aus oder lösen sie; `EventDensity` reduziert Ereignisse
getrennt von der ursprünglichen Intensität. Es gibt deshalb bereits hohe Energie
bei geringer Begleitdichte. `EndOpen` besitzt weiterhin eine absichtliche
Energiewirkung. Es gibt keinen 16/32/64/128-Takt-JB-D-Ablauf, keine Analyse echter
Sprecherpausen und keinen musikgesteuerten Patchwechsel. „Dialogstimme“ im
Generator bedeutet eine musikalische Rolle, keine erkannte Hörspiel-Sprechspur.

JB-D01–D06 sind daher überwiegend **Planungsverfahren**, keine sechs importierbaren
Datenpresets. Aufbau/Ausklang und gemeinsame Motivwiederkehr liefern Teile davon.
Insbesondere „wiederholtes Thema wird reichhaltiger instrumentiert“ erfordert eine
bewusste Kopplung von Wiederkehr und Schichtentscheidung, die bisher fehlt.

### Spielweise, Instrument und MIDI-Ziel

`PlayingTrack`, `RoleNeed`, `InstrumentCapabilities`, `suitable()` und
`outputCatalog()` unterscheiden Rolle, Spielweise, Tonhöhenverhalten, Range,
Polyphonie, Dauer und Ziel. Neun vorhandene Ziele genügen für den ersten
Barry-Ausschnitt: Harmonie/Bass lang und kurz, Bewegung, Tupfer, Stich, Dialog,
Hauptmelodie. Eigene Synth- und Orchester-Engines oder neue Ausgänge sind unnötig.

Die meisten Fähigkeiten sind Generatorannahmen; `externalPatchKnown=false`.
Ein fester Stich-Trigger liefert keine Information über gestimmte Pauken oder
Geräuschsamples und darf nicht als frei transponierbarer Melodieträger behandelt
werden. Reinstrumentierung benötigt später eine ausdrücklich geeignete
Zielzuordnung; keine automatische Programmwechsel-/Keyswitch-Engine in Phase 1.
Register und Oktaven sind bereits benutzerseitig steuerbar, aber die automatische
Defaultlage trennt hohe Melodie und tiefe Harmonie noch nicht als durchgängige
Barry-Regel. Ein anderes Samplepreset allein wäre kein Komponistenprofil.

## 7. Vorhandene Policy-Steuerstellen und tatsächliche Lücken

| Entscheidung | Gemeinsame Steuerstelle heute | Barry-Anschluss / Lücke |
| --- | --- | --- |
| Harmonische Auswahlpräferenz | `profiles.json`, `harmonicPreference()`, `Generator::pick()` | Bereits aktiv, ID-basiert; Forschungsneubewertung fehlt. Kein Stilnachweis durch einen Faktor. |
| Rollenaktivität, Ein-/Ausschalthysterese | `TexturePolicy`, `levelOn/Off()`, `stepOn()` | Bereits gelesen; derzeit dieselben Daten für alle Profile. Keine Zeitfensterregel „nur eine Oberschicht unter Dialog“. |
| Arp-Auto-Rate | `TexturePolicy::arpeggio`, `autoArpeggioDuration()` | Bereits aktiv; kein explizites Maximaltempo/keine profilabhängige Figurenpräferenz. Figuren-Override beachten. |
| Automatischer Bass / Pad / Arp | Wendungsrezept, `rawBassPattern()`, `choosePad/Arp()` | Daten von Harmonik getrennt, aber pro Wendung global. Mehrere profilbezogene Auto-Rezepte und Bass-Dichteentscheidungen fehlen. |
| Motivrückkehr und Variante | `MotifRecurrencePolicy` | Wiederverwendbar und tatsächlich ausgewertet; noch keine Barry-spezifischen Werte. Kein fortlaufendes A–A–B. |
| Pop-Hook-Strategie / Atmung | `HookPolicy`, `PopRolePolicy` | Pop-Anwendung, keine bereits anschließbare vollständige Barry-Score-Strategie. |
| Kontrollierte Durchgänge | `PassingPolicy` | Core vorhanden, tatsächlicher Adapteraufruf stark begrenzt; chromatische Wechselnoten und Score-Anbindung fehlen. |
| Melodischer Bass | `BassPhrasePolicy` | Tatsächlich genutzt, aktuell geeignete Pop-Auto-Kontexte. Score-Transfer muss musikalisch begrenzt werden. |
| Bass–Arp-Verzahnung | `RhythmCoordinationPolicy`, `planRhythmicInterlock()` | Kleine Pop-4/4-Strategie; weder allgemeine RC-Engine noch Black-Hole-3/4-Plan. |
| Akkordweite und Stimmenzahl | `ChordDispositionPolicy` | Core trennt beides, aktueller Adapter Pop-only. Harmoniecharakter nicht zur bloßen Dichte reduzieren. |
| Aufbau, Dichte, Szenenende | Bestehende Szenenparameter und `EventDensity` | Gemeinsame Ausführung vorhanden; feste JB-D-Verläufe und motivabhängige Schichtentscheidungen fehlen. |

Kein Profil benötigt eine eigene Engine. Neue Parameter sollen an wenige
musikalische Entscheidungen angeschlossen werden, die tatsächlich ausgeführt
werden. Keine leeren allgemeinen Regelobjekte und keine `if (id==JB-Hxx)`-
Sonderfälle im Generator. Ebenso wenig sollte der Kern von archivierten
Forschungsdateien oder Künstlernamen zur Laufzeit abhängen.

## 8. Abdeckung des gesamten XYZ-Feldes

### Reproduzierbare Prüfung des aktuellen kompilierten Katalogs

Ein temporärer C++-Analyseprozess wurde gegen die **unveränderten aktuellen
Header** kompiliert. Er verwendete `Generator::weight()`, `bestWeight()`,
`keepRatio()` und `candidates()` in einem Raster von **21 × 21 × 21 = 9261
Positionen**, einschließlich aller Flächen, Kanten und Ecken. Variety wurde mit
0, 0,5 und 1 geprüft: insgesamt **27.783 Punkte**. Die Zulässigkeit wurde
zusätzlich nach dem tatsächlichen Grenzvergleich in `pick()` nachgezählt; die
Kandidatenzahlen stimmten auf diesem Raster überein.

Der aktuelle Algorithmus bleibt die Referenz:

```
d² = (X−AnkerX)² + 0,49·(Y−AnkerY)² + 0,64·(Z−AnkerZ)²
XYZ-Gewicht = exp(−d² / 0,05)
zulässig: Gewicht >= (1 − 0,85·Variety) · bestes XYZ-Gewicht
Auswahlgewicht danach: XYZ-Gewicht · positive Profilpräferenz
```

Alle 48 Score-Wendungen haben unterschiedliche geordnete harmonische
Acht-Takt-Signaturen nach dem oben definierten Maßstab. Die Kandidatenzahl zählt
also keine exakten Score-Dubletten. Sie sagt dennoch nichts über ausreichende
Barry-Stilvielfalt oder passende Motorik aus. Die Zulässigkeit ist wegen positiver
Profilfaktoren für Neutral, Barry und Herrmann identisch.

| Variety | Kandidaten Minimum / Mittel / Maximum | Rasterpunkte mit nur einem Kandidaten |
| --- | --- | --- |
| 0 | 1 / 1,007 / 2 | 99,30 % |
| 0,5 | 1 / 3,149 / 14 | 26,02 % (2410/9261) |
| 1 | 1 / 10,288 / 31 | 0,25 % |

Ein Kandidat bedeutet lediglich „bestes verfügbares Material“, nicht gute
absolute Nähe. Der Algorithmus besitzt keine absolute Distanz-Abbruchschwelle.
Die mittlere Entfernung zum nächsten Anker beträgt 0,208 in der Auswahlmetrik,
die größte 0,673. Ungewichtet euklidisch sind es 0,248 bzw. 0,802.
933 Rasterpunkte haben eine metrische Entfernung >0,4, 333 >0,5.
Diese Grenzen sind Diagnosewerte, keine neu eingeführten Auswahlregeln.

Für die acht Randregionen wurden jeweils 512 Rasterpunkte betrachtet: niedrige
Achse <0,4, hohe Achse >0,6. Die mittleren Bereiche gehören zur obigen vollständigen
Gesamtprüfung, aber nicht zu diesen acht Teilregionen. Daten bei Variety 0,5:

| Region | Kandidaten Min / Mittel / Max | Nur einer | Kandidaten exakt in der 0/1-Ecke | Nächster Anker dort | Metrische Distanz dort |
| --- | --- | ---: | ---: | --- | ---: |
| DRS: dunkel/ruhig/stabil | 1 / 2,62 / 9 | 43,4 % | 1 | 1004 Trauer | 0,306 |
| DRU: dunkel/ruhig/unruhig | 1 / 1,77 / 10 | 50,6 % | 2 | 1001 Halbton-Nachbarn | 0,314 |
| DIS: dunkel/intensiv/stabil | 1 / 2,22 / 12 | 43,4 % | 1 | 1017 Moll-Marsch | 0,398 |
| DIU: dunkel/intensiv/unruhig | 1 / 2,61 / 6 | 19,9 % | 1 | 1013 Tritonus-Schock | 0,151 |
| HRS: hell/ruhig/stabil | 1 / 4,66 / 14 | 3,3 % | 1 | 1038 Wärme | 0,236 |
| HRU: hell/ruhig/unruhig | 1 / 1,41 / 3 | 60,5 % | 1 | 1028 Quarten-Weite | 0,673 |
| HIS: hell/intensiv/stabil | 1 / 3,85 / 9 | 12,3 % | 1 | 1048 Triumph | 0,138 |
| HIU: hell/intensiv/unruhig | 1 / 1,92 / 6 | 38,5 % | 1 | 1042 Terzverwandtschaft | 0,665 |

Insbesondere HRU/HIU sind nicht allein durch größere Barry-Faktoren zu reparieren:
Die jeweils besten Eckgewichte liegen nur bei etwa 0,000117/0,000144. Ein
willkürlich starkes Gewicht für einen weit entfernten dunklen Barry-Klang würde
an der vorgelagerten Zulässigkeit scheitern oder bei einer Strategieänderung
XYZ-Treue beschädigen. **Keine Änderung des Auswahlalgorithmus empfohlen.**
Eine eigenständige rhythmische Strategie kann dagegen auch bei nur einem
harmonischen Kandidaten einen hörbaren Profilunterschied erzeugen.

### Forschungsangebot ist keine schon implementierte Abdeckung

Abschnitt 13.1 der Forschung meldet für die acht Regionen folgende Anzahl
Harmonie-/Rhythmus-/Motivvorlagen: DRS 6/3/5, DRU 2/2/1, DIS 2/1/1, DIU 6/4/4,
HRS 8/2/4, HRU 2/1/1, HIS 3/1/1, HIU 3/1/1. Das ist eine grobe
Regionenzählung, kein Test mit dem Plugin-Algorithmus. Einträge in den mittleren
Regionen erklären, warum diese Zahlen nicht alle 46 JB-H aufsummieren.

Die schwächsten musikalischen Nachweise liegen gerade in DRU, DIS, HRU und den
hell-intensiven Extremen. JB-H38–H47 und mehrere M/R-Ergänzungen sind dort
explizit Extrapolationen. Sie dürfen die Software später funktional ergänzen,
aber nicht als erforschte Originalsprache Barrys oder bereits gelöste
XYZ-Abdeckung ausgegeben werden.

Einige gemeinsame Vorlagen besitzen im Text mehrere profilbezogene XYZ-Werte
oder Wertebereiche. Das aktuelle Datenmodell hat **einen statischen Anker pro
harmonischer Vorlage**. Dafür muss ein gemeinsamer musikalisch geprüfter Wert
gewählt werden. Unterschiedliche Ausgestaltung bleibt Profil-/Strategiedaten;
keine automatische Verdoppelung desselben Materials nur für einen anderen
Künstler-Anker. Erweiterungen des Koordinatenmodells sind keine Voraussetzung
für den ersten hörbaren Schritt.

## 9. The Black Hole und A View to a Kill

### The Black Hole

Am unmittelbarsten nutzbar sind ein dunkles stehendes Farbakkordfeld, langsamer
Bass/Pedal und ein kreisendes Arp im **vom Host vorgegebenen 3/4**. 960 PPQ und
2880 Ticks pro 3/4-Takt stellen die sechs Achtel aus JB-R04 exakt dar.
Dafür ist keine weitere Scheduler-Baustelle erforderlich. Es gibt aber noch
keinen gespeicherten spezifischen JB-R04-/JB-R26-Notenplan; `ArpCircle` ist ein
vorhandener verwandter Figurtyp, keine Rekonstruktion des Film-Ostinatos.

Relevante Forschungsbausteine: JB-H01/H02/H18/H25, JB-R04/R08/R26,
JB-RC04, JB-M01/M02/M17, JB-D01. Eine fortlaufend fallende Bassbewegung gegen
aufsteigende Oberstimme, eine beständige kleine Terz bei hoher Unruhe und
geplante Diminution einer Oberschicht sind noch nicht als solche Strategie
realisiert. Der Blaster-Beam-Klang gehört zur Instrumentierung, nicht in die
harmonische Engine. Die Originalakkorde, genaue Instrumentenrollen und manche
Takt-/Intervallangaben bleiben laut Quellenlage ungeprüft.

### A View to a Kill

Die brauchbare musikalische Fragestellung ist **dasselbe Material in anderem
Kontext**, mit dunklem Motor, kurzen Gegenspielerzeichen und einer warmen
lyrischen Seite. Die Gesamtfassung verweist dafür auf JB-M11, JB-M26, JB-D03
sowie die längeren A/F-Phrasen und die Umharmonisierungsbeispiele. Das heutige
Gedächtnis und die flexible Realisierung liefern Teile der technischen Basis.

Nicht vorhanden sind ein authentisches Zorin-Motiv, eine Transkription der
Film-Harmonik oder eine genaue Original-Taktart. JB-M11 und JB-M26 sind
unterschiedliche eigene Entwürfe mit unterschiedlicher Intervallik, nicht zwei
verifizierte Fassungen desselben Originalmotivs. M26 benötigt chromatische
Nebennoten, die der heutige Score-Akkordtonpfad nicht pauschal erzeugt.

Ein erster Barry-Grundmodus darf daher diese atmosphärische Motorik und das
Kontrastprinzip anstreben, aber nicht als Nachbildung des Songs, des
Originalscores oder als fertig implementierte AVTAK-Grammatik bezeichnet werden.
Die gemeinsame Engine muss auch mit Klavier dieselben kompositorischen
Unterschiede liefern; ein Orchester-/Synth-Patchtausch ist keine Stilstrategie.

## 10. Korrekturbedarf vor einem späteren Import

Die Originaldokumente bleiben unverändert. Folgende Punkte sind als
Import-/Interpretationshinweise zu beachten:

1. **Zeitbeschreibung JB-M01:** Die vier pausierenden Schritte 12–15 sind im
   angegebenen 4/4-Sechzehntelraster **eine** Viertelpause, nicht „zwei Viertel
   Luft“. Das Raster/Notenende ist maßgeblich.
2. **Gemeinsame Töne JB-H05:** CmM7 und EmM7 teilen als Tonklassen Eb/D#, G und B.
   Die Anweisung „ohne Verbindungston“ widerspricht einer pauschalen Behauptung
   fehlender Gemeinsamkeit; klären, ob ein absichtlich abgesetzter Übergang oder
   eine Bindung gewünscht ist. Keine harte Sonderregel aus diesem Satz ableiten.
3. **Durchgang vs. Nebenton:** Nicht jeder in der Sammlung so bezeichnete Ton
   erfüllt `planPassingTone()`. Beispielsweise führt D5 in JB-M09 direkt nach B4
   (kleine Terz), also nicht in zwei schrittweisen Bewegungen. Chromatische
   Umspielungen, Vorhalte, unaufgelöste Spannungen und zyklische Auflösungen müssen
   getrennt spezifiziert werden.
4. **Identität in JB-D03:** Die genannten M09/M16/M12 sind nicht einfach dieselbe
   Tonfolge in anderer Besetzung. Rhythmus, Schluss und teils Kontur wechseln.
   Für „ein Thema, zwei Gesichter“ muss später ein konkreter gemeinsamer Kern
   festgelegt werden, statt unterschiedliche Daten nur mit gleichem Namen zu
   versehen.
5. **Forschungsinvarianten vs. heutiger Fallback:** Abschnitt 9 fordert unter
   anderem erhaltene Tonzahl und langen Zielton; bestehende Fragmentierung und
   Gateverkürzung erfüllen das nicht in jeder Variante. Eine gemeinsame
   Herkunfts-ID beweist keine unveränderte Wahrnehmungsidentität. Ein zukünftiger
   Langphrasenplan benötigt eigene verbindliche Ziel-/Kernangaben; die aktuellen
   Score-Verbesserungen werden hier nicht zurückgebaut.
6. **Metrum, Bass und Harmonie:** Phrasen-Kontextlisten sind keine exakten
   Akkordzeitleisten. Pedalvorschläge überschreiben Follow nicht. Neue R-Daten
   müssen Halten/Pause/Akzent in reale Dauern umsetzen, nicht nur X zählen.
7. **XYZ und Herkunft:** Bereiche/mehrere Werte nicht als Array in den statischen
   Anker kopieren. Vermutete Stilhinweise, [E]-Konstruktionen und verifizierte
   Verfahren bleiben unterscheidbar; Archive liefern keine zusätzlichen IDs.

## 11. Empfehlung: kleinster zusammenhängender hörbarer Schritt

**Ein begrenzter Barry-Grundmodus „Farbakkordfeld + ruhiger Motor“ im Score-Modus.**
Er verbindet zwei prägende Merkmale, statt nur vorhandene Parameter leiser zu
stellen oder noch einmal Harmoniegewichte zu verändern.

Vorgeschlagener Umfang des nächsten Auftrags:

1. **Nur zwei kanonische Harmoniegerüste** über den vorhandenen validierten
   Datenpfad bereitstellen: JB-H01 (acht Takte mM7) und JB-H03 (acht Takte add9).
   Beide mit geschützter Färbung, eigener stabiler produktiver ID, Quellenreferenz
   und jeweils einem geprüften statischen XYZ-Anker. Keine R/M/P/D-Massenimporte.
   Die beiden unterschiedlichen Felder sichern einen dunklen und einen warmen
   ersten Hörfall, statt Barry auf Bedrohung zu reduzieren.
2. **Eine kleine profilabhängige Auto-Begleitstrategie** an die vorhandene
   `FreeCompositionPolicy` anschließen: bevorzugt gehaltenes Fundament/Pedal,
   gehaltene Harmonie und die vorhandenen kreisenden bzw. schlichten Arp-Figuren.
   Ein explizites Auto-Ratenlimit soll im begrenzten Kontext Viertel/Achtel
   ermöglichen, ohne bei Y=1 oder Figuren-Overrides versehentlich wieder in einen
   Sechzehntelmotor zu fallen. Energie darf trotzdem Velocity/Ausdruck verändern.
   Die bisher harten Bass-Hochintensitätsentscheidungen müssen diesen tatsächlich
   ausgewählten Auto-Plan respektieren. Vorhandene Motiv-/Antwortfenster behalten
   Vorrang. Keine neue Notenquote oder allgemeine Ebenenplanung.
3. **Wirkung nur im Score-Barry-Kontext** auflösen. Heute ist `policyForProfile()`
   genreunabhängig; eine neue Barry-Policy darf nicht versehentlich die weiterhin
   auswählbare Pop-Konfiguration verändern. Das lässt sich an der vorhandenen
   Settings-/Policy-Auflösung begrenzen, ohne jetzt eine neue Künstler-GUI oder
   allgemeines Profilregister zu bauen. `harmony_selection_only` wäre erst mit
   tatsächlich angeschlossener musikalischer Policy auf false zu setzen.
4. Manuelle Figur/Rate/Bassspielweise, Follow, Mute/Solo, Range, bereits aktive
   Motive und deren Rückkehr bleiben Benutzervorgabe. Hauptmelodie bleibt
   standardmäßig AUS. Kein automatischer Hosttempo-/Taktartwechsel und keine
   festgelegte Besetzung.

Warum dieser Umfang: Nur Daten importieren würde weiterhin die bisherigen
neutralen Begleitentscheidungen erhalten; nur Aktivitätsschwellen verschieben
würde eher eine ausgedünnte neutrale Engine liefern. Zwei unverwechselbar
angelegte Farbakkordfelder plus eine tatsächlich andere motorische Ausgestaltung
bilden einen kleinen vertikalen Hörfall ohne neue Melodie- oder Formgrammatik.
Die zwei Datenvorlagen können zuerst separat validiert werden, anschließend wird
der kleine Policy-Anschluss integriert. Das ist ein abgegrenztes erstes Ziel,
nicht die vollständige Barry-Implementierung.

**Wichtige Katalogfolge:** Werden neue gemeinsam nutzbare Vorlagen in den
Score-Pool aufgenommen, können auch Neutral und Herrmann andere Wendungen
wählen. Die bisherige weiche Profilgewichtung besitzt keine Ausschlussliste.
Bytegleichheit der gesamten automatischen Auswahl darf deshalb nach einem
Katalogzuwachs nicht behauptet werden. Bestehende Wendungen sollen bei
festgehaltener ID und gleicher neutraler Policy bytegleich bleiben; die neue
Auswahlverteilung ist separat zu dokumentieren. Falls stattdessen ausdrücklich
absolut unveränderte automatische Neutral-Auswahl verlangt wird, wäre ein
zusätzlicher, gesondert zu entscheidender Katalog-/Verfügbarkeitsumfang nötig.
Das gehört nicht stillschweigend in diesen kleinen Schritt.

### Konkrete Prüfkriterien für diesen nächsten Auftrag

- Vorlagendaten: acht Takte, korrekte Intervalle und geschützte Farben, keine
  versehentliche Septime auf add9 und keine automatische mM9-Erweiterung auf mM7;
  alle zwölf Transpositionen, beide Follow-Zustände.
- Echte Profileffektprüfung bei **gleicher** festgehaltener Harmonie und demselben
  Instrument: Barry- und Neutral-Auto-Ausführung müssen sich hörbar/testbar im
  Einsatz-/Dauerraster unterscheiden. Unterschiedliche Parameterwerte allein
  reichen nicht als Nachweis.
- In 3/4 ein sechsachteliges geeignetes Bewegungsraster über stehendem mM7, in
  4/4 eine warme add9-Fläche mit sparsamem Puls. Keine Behauptung, dass dies ein
  Original-Cue oder schon die genaue JB-R04-Tonfolge sei.
- Niedrige, mittlere, maximale Intensität sowie Unruhe, statische und bewegte XYZ;
  verbleibende Noten behalten ihren Energieausdruck. Kein erzwungenes Maximum an
  Bass-/Arp- oder Melodieanschlägen.
- Manuelle Einstellungen sowie Mute/Solo identisch zum jeweiligen Referenzpfad;
  keine zusätzliche Melodie durch Profilwahl; Motive, Antworten und automatische
  Arp-Reservierungen bleiben gültig.
- Neutral/Herrmann bei bestehenden expliziten IDs sowie Pop/Rock musikalisch
  unverändert; automatische Katalogverteilung gesondert vor/nach vergleichen.
- Mindestens 128 Takte, Notenledger, Gate-/Pausenmessung, Seek, Loop, Neustart,
  Blockgrößen, tatsächliche Live-/Exportgleichheit und kein Heap im Audiopfad.
- Hörabnahme mit gleichem Klavierpatch, danach optional Synth/Orchester. Erst
  danach eine Aussage über stilistische Überzeugungskraft treffen.

## 12. Danach priorisierte kleine Folgeaufgaben

| Reihenfolge | Aufgabe | Konkretes Abnahmekriterium |
| --- | --- | --- |
| 1 | Erster Grundmodus aus Abschnitt 11 | Dunkler und warmer A/B-Hörfall mit tatsächlicher Policywirkung, ohne neue Form-/Motivengine. |
| 2 | Kleiner Ergänzungsimport JB-H02, H05, H06 nach Einzelprüfung | m6-Stasis, mM7-Großterzpendel und langsames Maj7-Pendel korrekt, Profilvielfalt/XYZ-Nähe gemessen statt alle 46 auf einmal. |
| 3 | Begrenzte datenbasierte Initialgesten aus geeigneten JB-M, z. B. M01/M08 | Vorlage wird wirklich ausgegeben und genau dieses Material aufgezeichnet; keine zweite Motivverwaltung. Register und Akkordkontext vollständig geprüft. |
| 4 | Gezielte Score-Nebenton-/Auflösungsabsicht für chromatische Umspielung | Ein einziger kontrollierter Typ mit Zielauflösung, etwa die M26-artige Umspielung. Kein generelles Freischalten aller zwölf Tonklassen; Originalmaterial unverändert. |
| 5 | Vier-Takt-Linie mit einem Ziel und einem Gipfel | Ein vollständiger zusammenhängender Gedanke samt Atemstelle über tatsächliche Akkordgrenzen; keine bloße Erhöhung der Speicherkapazität. |
| 6 | Eine gekoppelte Oberzellen-Diminution über unverändertem Fundament | Originales unteres Material bleibt in Tonfolge und Rhythmus unverändert, nur eine definierte obere Zelle entwickelt sich; exakte Konflikt-/Fensterprüfung. |
| 7 | Eine bewusste A–A′–B-/Wiederkehr-Schichtentscheidung | Tatsächlich identischer Kern in A/A′, eigenständiger B-Schluss und nachvollziehbare Ruhe; keine freie komplette Formgrammatik. |
| Später | Score-Besetzungsstrategie, explizite Reinstrumentierung und weitere Randbereichsforschung | Charakteristische Farben erhalten, nur geeignete Ziele, keine ungeprüften Patchannahmen; evidenzarme XYZ-Regionen musikalisch nachprüfen. |

Nicht jede spätere Aufgabe muss vor einer erneuten Hörabnahme fertig sein.
Gerade die ruhigen Motor-/Farbakkord-Kombinationen lassen sich vorher als
begrenztes Profil testen. Die Chromatik- und Langphrasenlücken dürfen dabei nicht
als bereits gelöst erscheinen.

## 13. Relevante Codeverweise

Die Zeilen beziehen sich auf `f04b96d`; Funktionsnamen bleiben die primäre Referenz.

| Bereich | Datei / Funktion |
| --- | --- |
| Profil-/Policy-Daten und neutrale Defaults | [CompositionPolicy.h](../../../Source/CompositionPolicy.h): `TexturePolicy`, `MotifRecurrencePolicy`, `FreeCompositionPolicy`, `compositionProfiles`, `policyForProfile()` |
| Profil an die Produktengine anschließen | [PluginProcessor.cpp](../../../Source/PluginProcessor.cpp#L291): `currentSettings()` |
| Katalogvalidierung, statische Bereitstellung | [generate_harmony_catalog.py](../../../scripts/generate_harmony_catalog.py#L33): `_validate()`; [HarmonyRuntime.h](../../../Source/HarmonyRuntime.h): `playbackTemplate()` |
| Akkordfarben, Slots und Bassdaten | [HarmonyTypes.h](../../../Source/HarmonyTypes.h): `Chord`, `HarmonyTemplate`, `coloredChordType()`; `data/harmony/chord_types.json` |
| XYZ und gewichtete Auswahl | [ScoreEngine.h](../../../Source/ScoreEngine.h#L409): `keepRatio()`, `candidates()`, `weight()`, `pick()`; `maybeSwitch()` ab 1650 |
| Tatsächliche Anfangsgesten | `ScoreEngine.h::motifFor()` ab 1003, `counterLadder()`, `planMotifNote()`, `motifStep()` |
| Gespeicherte Motive / Ableitung / Realisierung | [CompositionCore.h](../../../Source/CompositionCore.h#L37): `RememberedMotif`, `deriveMotif()`, `realizeScoreMotif()`, `MotifCatalog`, `planRecurrence()` |
| Rollen, Übergaben und Arp-Platz | `ScoreEngine.h::melodicRoleWindow()`, `dialogueMayLead()`, `motifWindow()` ab 1460; `playableMelodyHandoff()`; `CompositionCore.h::planMelodyHandoff()` |
| Freie kurze Phrasen | `ScoreEngine.h::freeLinePhrase()` ab 3320; `CompositionCore.h::planLinePhrase()` ab 472 |
| Bass/Arp/Pad-Auswahl | `ScoreEngine.h::chooseArp()`, `rawBassPattern()`, `melodicBassAllowed()` ab 1722, `choosePad()` ab 1797, `arpeggioPeriod()` ab 2342 |
| Tatsächliche Bewegungs- und Bassnoten | `ScoreEngine.h::playArpeggio()` ab 2821, `render()` ab 2915, insbesondere BassPendulum/BassPedal und Hochintensitätsentscheidungen |
| Harmonie-Stimmführung und gehörte Übergänge | `CompositionCore.h::planHarmony()`, `leadEntry()`, `buildAnchor()`; `ScoreEngine.h::rememberHarmonicEntry()`, `prepareVoicingPlan()` ab 1980 |
| Offene/reduzierte Akkordlagen | [ChordDisposition.h](../../../Source/ChordDisposition.h): `realizeChord()`; `ScoreEngine.h::padVoicing()` ab 2094 |
| Instrumentenfähigkeiten | `CompositionCore.h::InstrumentCapabilities`, `RoleNeed`, `suitable()`; `ScoreEngine.h::outputCatalog()` ab 144 |
| Modalität und Durchgang | [ModalContext.h](../../../Source/ModalContext.h): `modalContext()`, `planPassingTone()`; `ScoreEngine.h::addPassingTone()` ab 1121 |
| Gemeinsame Zeit und Ausführung | [MusicalTime.h](../../../Source/MusicalTime.h), [MusicalExecution.h](../../../Source/MusicalExecution.h), `ScoreEngine.h::Meter::from()` |
| Bisherige letzte musikalische Änderungen | [ROLE_COORDINATION_A.md](../../development/ROLE_COORDINATION_A.md), [POP_MELODIC_ROLES.md](../../development/POP_MELODIC_ROLES.md) und die vorhandenen Score-Realisierungsberichte |

## 14. Prüfungen in dieser Analysephase

Durchgeführt: ZIP-Sicherheits-/Pfadprüfung, bytegleiche Übernahme einschließlich
Git-Blobs, vollständige Prüfung der 46 JB-H-Akkordtabellen gegen aktuelle
Tonklassen/Typen/Bässe/Dauern, Einzelvergleich mit allen 87 Katalogeinträgen,
Notenzählung/Taktsummen der 20 Barry-Phrasen, das oben beschriebene C++-XYZ-Raster
und `python scripts/generate_harmony_catalog.py --check` (erfolgreich).

Keine neuen musikalischen Regeln, keine Produktquellen oder GUI-Dateien geändert.
Keine erneute vollständige Render-/Sanitizer-Suite für reine Forschungsablage
behauptet oder benötigt. Die erfolgreichen Build-/Testnachweise des unveränderten
`f04b96d` bleiben davon getrennt. Keine neue Hörprüfung vorgenommen.

Die Bibliothek ist bei späteren Recherchen zu erweitern: neue Originaldokumente
mit Herkunft ablegen, die maßgebliche Fassung im README benennen, Aliasse und
Evidenz erhalten, Überschneidungen mit dem gemeinsamen Material prüfen und dann
nur kleine freigegebene Importschritte planen. Kein automatischer Import allein
aufgrund eines neu abgelegten Forschungsdokuments.

Kein Push, kein Release. Die Profilimplementierung wurde nicht begonnen.
