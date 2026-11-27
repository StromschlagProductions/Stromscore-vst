# Bernard Herrmann – kanonischer Bestandsabgleich und Implementierungsplan

27.11.2026 · Branch `develop/composition-core-prototype` · Engine `023b0a6`.
Williams P2/P3 sind technisch vorhanden, musikalisch noch nicht abgenommen.
Dieser Auftrag archiviert und analysiert ausschließlich; keine HE-Vorlage wurde
aktiviert, kein musikalischer Parameter und keine GUI geändert.

## 1. Ergebnis und Bewertungsmaßstab

Die bestehende gemeinsame Engine ist ein brauchbarer Ausgangspunkt für ein früh
hörbares Herrmann-Profil. Sie ist noch kein Interpret der gesamten Bibliothek.
Besonders Pedallebensdauer, exakte chromatische Basslinien, Komponentenbeziehungen
und Modulprozesse fehlen. Diese Lücken sind auch für Williams und SYNTH relevant.

| Bereich | Gesamt | D: direkt darstellbar | A: begrenzte Anbindung | E: gemeinsame Fähigkeit fehlt | K: klären |
|---|---:|---:|---:|---:|---:|
| Harmonik | 101 | 34 | 4 | 61 | 2 |
| Rhythmik | 66 | 0 | 27 | 38 | 1 |
| Bass | 45 | 0 | 7 | 35 | 3 |
| Motive | 57 | 0 | 31 | 25 | 1 |
| Phrasen | 21 | 0 | 0 | 21 | 0 |
| Studien | 40 | 0 | 3 | 37 | 0 |
| Transformationen | 13 | 0 | 0 | 13 | 0 |
| **Summe** | **343** | **34** | **72** | **230** | **7** |

D heißt: bestehende musikalische Mechanismen stellen die Grundform korrekt dar;
validierter Import, Quellenidentität und Profilanbindung fehlen trotzdem. A heißt:
keine neue kompositorische Grundfähigkeit, aber ein begrenzter Datenverbraucher,
Kontext-/Registerprüfung oder Rollenanschluss ist nötig. E betrifft mindestens
eine wesentliche zusätzliche Fähigkeit, nicht automatisch einen großen Umbau.
K verlangt zuerst eine konkrete inhaltliche Entscheidung.

Die Einstufung bewertet Grundform und zwingende Eigenschaften, nicht sämtliche
optionalen Varianten. Beispiel HE-H13: Caug selbst ist darstellbar; eine frei
melodisch verwendbare Ganztonskala folgt daraus nicht. Eine achtaktige Akkordliste
mit extra Oberpedal ist ebenfalls nicht als Gesamtvorlage fertig, nur weil ihre
Tabellenzeilen passen. **62 H-Tabellen** passen rein strukturell in die heutigen
Akkorddaten; nur 38 H-Grundformen sind D/A. Diese Zahlen nicht verwechseln.

Alle 343 Einzelentscheidungen einschließlich Originalfiguren, Funktionen,
Kontextangaben, Quellzeilen und Abhängigkeiten stehen im
[JSON-Inventar](TECHNICAL_INVENTORY.json); die
[Einzeltabelle](TECHNICAL_INVENTORY.md) enthält jede ID mit Begründung.
`assessment.json` ist die redigierte Bewertungsquelle. Keine Einstufung ist eine
musikalische Hörabnahme oder eine Importfreigabe.

## 2. Unabhängige technische Prüfung

Die vier Originaldateien bleiben unverändert. Die eigene Offline-Prüfung bestätigt:

- 343 eindeutige Vorlagenköpfe; alle erfassten HE-ID-Verweise existieren.
- Alle 101 H-Tabellen ergeben acht Takte, höchstens acht Slots, ganze Taktdauern.
  Akkordsymbol, aufgeführte Tonklassen inklusive Slash-Bass und Bassspalte stimmen
  überein. Exakte Typunterstützung wird separat geprüft.
- R-/B-Raster: korrekte Takt-/Schrittsummen, keine führenden Haltestriche nach
  Pausen. M-/P-Notentokens: korrekte Taktsummen einschließlich 4/4T.
- 53 SMF-Dateien, alle 960 PPQ; jede der 5.328 Noten stimmt in Studie, Rolle,
  Beginn, Dauer, Tonhöhe und Velocity mit der CSV überein.
- Keine verwaisten Note-offs, doppelt geöffneten gleichen Kanal-/Tonpaare oder
  hängenden Noten; alle Studiotöne 21–108. ST ausschließlich MIDI36.

Das bestätigt technische Integrität, **nicht** alle musikwissenschaftlichen
Behauptungen, Funktionslabels oder die Eignung aktueller Runtime-Verbraucher.
Die Ergebnisse sind in [VALIDATION_RESULTS.json](VALIDATION_RESULTS.json) enthalten.
Es wurden keine Engine-Renderings oder neuen Hörbeispiele produziert; die gelieferten
Studien sind Forschungsreferenzen, keine Ausgabe der aktuellen Engine.

### Konkrete Abweichung von den aktuellen Instrumentenannahmen

`ScoreEngine::outputCatalog` beschreibt Generatorannahmen, keine erkannten externen
Patches. Die separaten Lang-/Kurz-Ausgänge sind unterschiedliche Spielweisen.

| Ziel | Stimmen | Mindestdauer | Maximaldauer in Ticks | Konsequenz |
|---|---:|---:|---:|---|
| LF | 6 | 240 | 4.026.531.840 | Langfläche, nicht automatisch derselbe Patch wie KF |
| KF | 9 | 240 | 720 | Viertel-/Halbnoten sind bereits außerhalb der Annahme |
| LB | 1 | 240 | 4.026.531.840 | keine Dyade/Oktavverdopplung auf einem Ziel |
| KB | 1 | 240 | 960 | kein lang gehaltener Kaskadenton |
| AR | 1 | 240 | 7.680 | Brechung möglich, simultaner Dreiklang nicht |
| TU | 4 | 240 | 720 | lange Glockentöne nicht automatisch geeignet |
| ST | 1 | 240 | 480 | fixer Trigger, nicht tonale Stimme |
| GS | 2 | 240 | 4.026.531.840 | Fähigkeiten und Rollenfreigabe getrennt beachten |
| HM | 1 | 240 | 4.026.531.840 | optionaler Vordergrund, kein Ersatz für Polyfläche |

Die hohe Long-Grenze ist ein technischer Standardwert, keine musikalisch empfohlene
Notenlänge. Register kommen aus den Benutzereinstellungen; ohne Range-Begrenzung
0–127. Ein externer Patch ist damit weder als lang spielfähig noch als tonal
bekannt. `stichFixed/stichNote` sind bestehende Einstellungen; HE fordert den festen
Trigger36. Keine Akkordtransposition darauf anwenden, keine anderen Noten aus
Akkord-/Tonvorratsregeln ableiten.

16 R-/Ziel-Kombinationen überschreiten die aktuellen Dauerannahmen; etwa R32:
KF-Viertel = 960 statt maximal720. R51 verlangt TU5.760/KF4.800/KB4.320 Ticks.
In den tatsächlichen SMF-Daten gibt es 28 Grenzüberschreitungen über 22 S-/T-IDs:
26 Dauerkonflikte und zweimal LB-Polyphonie2 (S09/S37). S02 benötigt sogar für KF,
KB und TU jeweils1.920 Ticks. Keine der Dateien ist dadurch formal ungültig.

Ein möglicher späterer Schritt ist eine ausdrücklich bestätigte Instrumenten- und
Spielweisenbeschreibung für diese Fälle. Nicht pauschal Grenzen hochsetzen, nicht
Noten verkürzen und nicht auf einen vermeintlich passenden anderen Patch umleiten.
LB+KB können grundsätzlich gleichzeitig je eine Stimme adressieren (B04); dies
verlangt zwei unabhängige Pläne. Es ist etwas anderes als zwei Stimmen auf LB (B43).
Zusätzliche MIDI-Ausgänge sind dafür jetzt weder beschlossen noch begründet.

## 3. Harmonik, Tonvorräte und Herkunft

Vorhanden: 181 Katalogeinträge, 27 Akkordtypen, geschützte Färbung, relative Wurzeln,
expliziter Slash-Bass, Herkunft, Profile/Genre und ein validierter statischer
Laufzeitpfad. Siehe [HarmonyTypes.h](../../../Source/HarmonyTypes.h),
[Typdefinitionen](../../../data/harmony/chord_types.json),
[Katalog](../../../data/harmony/catalog.json) und
[Generator](../../../Source/ScoreEngine.h) (`chordFor`, `coloredChordType`,
`CompositionCore::planHarmony/buildAnchor`, `roleRhythm`, `authoredRhythmBar`).

mMaj7/mMaj9, Aug/AugMaj7, halbvermindert, vermindert, Dom7b9, Sus/Add und einzelne
quartale Typen sind bereits vorhanden. Fehlend sind insbesondere exakte7b5-,
italienische-Sext-, mMaj7♭6-,9♯5-,dimMaj7-,add♯4-,m(add♭9)-Definitionen sowie
verschiedene explizite Tonmengen. `Cadd#4` ist kein `Cmaj7#11`: letzterer ergänzt
zusätzlich B. `{C F B}` ist nicht der vorhandene vierstimmige Quartaltyp.
Alle fehlenden Symbole mit IDs sind maschinenlesbar aufgeführt.

Acht HE-H-Grundtabellen besitzen eine streng gleiche vorhandene harmonische
Ton-/Bass-/Dauerstruktur: H01→30001, H10→30025, H32→1031, H41→1042,
H42→40025, H68→1003, H91→30042, H94→30001. Das sind **keine** acht komplett
identischen Arrangements: H68 fügt etwa ein hohes Pedal hinzu, H91/H94 verlangen
Oktavbass. Bestehende Laufzeit-IDs erhalten und zusätzliche Verfahren/Provenienz
separat anbinden. Die Auswahl der Repräsentanten ist noch keine Importliste.

Der [BH-/HE-Abgleich](BH_HE_CROSSWALK.md) erfasst 111 historische BH-Definitionen
inklusive JB-Aliase; bei neun alten H-IDs findet sich eine strikte harmonische
Überdeckung. Andere Fälle sind nur ähnlich. Zum Beispiel BH-H29 gegenüber HE-H07:
gleiche chromatische Bassidee, aber Cm gegenüber CmM7. Keine Zusammenführung nur
aufgrund eines Namens, einer vereinigten Tonmenge oder eines ähnlichen Verfahrens.

[ModalContext.h](../../../Source/ModalContext.h) bietet Ionisch, Mixolydisch,
Dorisch, Äolisch und explizite Oktatonik mit Akkord-/Vorratstonunterscheidung.
Ganzton und Hexatonik fehlen. Nicht jedes Caug benötigt sofort eine Ganzton-Engine;
H13 ist zunächst ein gültiges Akkordobjekt. Freie Linien und erlaubte zusätzliche
Töne mehrerer Rollen brauchen dagegen einen gemeinsamen Kontext. Okt-A/B sind
lokale Referenzvorräte, keine pauschale Herrmann-Oktatonik. „Chromatisch“ autorisiert
nur die definierte Struktur plus ausdrücklich legitimierte Zusatz-/Pedaltöne,
niemals zwölf beliebige Tonklassen.

## 4. Motive, Funktionen und Entwicklung

[AuthoredMotifSource.h](../../../Source/AuthoredMotifSource.h) ist wichtig: P3
kann bereits **zusätzliche notierte melodische Töne kontextgebunden erlauben**.
Deshalb werden nicht sämtliche HE-Nicht-Akkordtonzellen als unmöglich eingestuft.
31 kurze M-Grundformen sind mit begrenzter, strenger Anbindung möglich: vollständige
Quellfolge, geprüfter aktueller Kontext, passende Dauern/Register und vollständige
Zielauflösung. Das ist keine freie Übertragung jedes dissonanten Gedankens auf
beliebige neue Harmonik. Der Vorrat ist nicht aus der Summe der Motivtöne abzuleiten.

[CompositionCore.h](../../../Source/CompositionCore.h) hält tatsächlich gespieltes
Material (Intervalle, Rhythmus, Dauern), maximal acht Noten pro Motiv, zwei Materialien
pro Szene und unabhängige Verwendungszustände. Einführung, frühe Reprise,
Fragmentierung, Sequenzierung, rhythmische Variation und Augmentation existieren.
Die Produktionsanbindung liegt in `authoredMotif`, `motifPitchMask`,
`planMotifNote`, `motifOccurrence` im Generator. Williams P3 registriert 32 von 48
Vorlagen; der P3-Bericht weist20 im dortigen Produktionsvergleich tatsächlich nach.

Noch nicht modelliert ist pro Note:

- **A:** Bezug auf den zu diesem Zeitpunkt geltenden Akkord/die Komponente.
- **T:** Bezug auf den expliziten lokalen Tonvorrat.
- **V:** gerichtete Spannung mit bestimmtem erreichbarem Ziel und Frist.
- **F:** absichtliche innere Reibung, nicht versehentlich zu „verbessern“.
- **U:** beabsichtigte unaufgelöste Schlussdissonanz, kein fehlgeschlagenes V.

Lokale Quellmasken sind ein vorhandener Teilbaustein, keine vollständige Semantik
für Transformation und Rollenwechsel. Geschützte Akkordfarben schützen die
harmonische Definition, nicht automatisch den fremden Bass oder eine U-Schlussnote.
Die derzeitigen Verbraucher haben konkrete Profilprüfungen: `roleRhythm` ist auf
Williams und 4/4 beschränkt, `authoredMotifs` bedient Barry/Williams und
`williamsMaterial` löst nur Williams-Provenienz auf. Der HE-Anschluss muss diese
Quellenzuordnung begrenzt gemeinsam nutzbar machen. Eine zusätzliche HE-Kopie
dieser Verbraucher wäre die falsche Lösung; das gemeinsame Masken-/Motivverfahren
ist bereits vorhanden. Der bestehende Herrmann-Eintrag nutzt weiterhin nur
Harmoniegewichte (`harmonySelectionOnly`) und neutrale Policies.

Eine adaptive Variante darf nicht mit einer ähnlichen Kontur als bestanden gelten,
wenn die konkrete Auflösung verlorengeht. Ungeeignete Varianten auslassen.

Die aktuellen Antwortpläne sind gezielt eng: HM→GS mit kurzer Schlussfigur und
GS→AR. Sie sind kein beliebiger Kanon, kein Fugato und keine freie Rollenwanderung.
Freie Zieltonlinien sind ebenfalls kurze Gedanken, keine13Takt-Bögen.
Phrasen-/Transformationsvorlagen deshalb nicht nur durch größere Arrays freischalten.

## 5. XYZ-Erreichbarkeit und musikalische Eigenständigkeit

Die [reproduzierbare Diagnose](XYZ_COVERAGE.json) verwendet die unveränderten
C++-Funktionen `Generator::weight/keepRatio` auf 21³ Positionen und Variety 0/0,5/1.
Für die Harmonie gilt weiterhin:

`w = exp(-(dx² + 0,49dy² + 0,64dz²)/0,05)`;
zulässig ab `(1−0,85·Variety)·best`. Erst danach wirken Profilpräferenzen.
Gemessen wird die tatsächliche Pick-Schwelle, nicht das leicht tolerantere
Kandidaten-Anzeigefilter. Keine neuen HE-Profilgewichte wurden erfunden.

| Pool, separat simuliert | Anzahl | Ø Kandidaten bei Variety 0,5 | Punkte mit nur1 Kandidat /9.261 | größte gewichtete Entfernung |
|---|---:|---:|---:|---:|
| Heutiger freier Score-Katalog | 48 | 3,15 | 2.410 | 0,673 |
| Alle HE-H-Anker, auch noch nicht realisierbare | 101 | 6,48 | 752 | 0,517 |
| Nur strukturell passende HE-H-Tabellen | 62 | 4,78 | 2.136 | 0,574 |
| Vollständige HE-H-Grundformen D/A | 38 | 3,69 | 3.565 | 0,657 |

Das ist keine Simulation eines aktivierten kombinierten Katalogs. Absolute
ungewichtete XYZ-Entfernung, Ecken, schlechter versorgte Punkte und alle weiteren
Variety-Werte stehen im JSON. Mehr Kandidaten bedeuten nicht automatisch mehr
musikalische Unterschiede: Inversionen, gemeinsame Klangfelder und noch fehlende
Komponenten-/Bassregeln separat zählen. Variety 0 liefert erwartbar meist einen
Kandidaten. Selbst bei allen101 Ankern bleibt an manchen Randpunkten die Auswahl
klein und die absolute Entfernung groß.

| Ecke X/Y/Z | alle HE: Kandidaten / gewichtete Nähe | D/A-Grundformen: Kandidaten / Nähe |
|---|---|---|
|0/0/0|3 /0,376|1 /0,376|
|0/0/1|1 /0,307|1 /0,307|
|0/1/0|3 /0,280|2 /0,569|
|0/1/1|1 /0,190|1 /0,356|
|1/0/0|1 /0,371|1 /0,486|
|1/0/1|1 /0,517|2 /0,579|
|1/1/0|1 /0,446|1 /0,490|
|1/1/1|2 /0,387|1 /0,657|

Nähe bedeutet hier Entfernung (kleiner ist näher). Die dunkle DRU-Häufung ist ein
bewusster Forschungsschwerpunkt. Sie darf nicht durch globale XYZ-Verzerrung auf
alle Rollen übertragen werden. Helle Herrmann-Bereiche sind kalt/surreal/bedrohlich,
nicht zwingend freundlich; hohe Intensität bei niedrigem Z kann aus Masse/Lage
statt schnellen Noten entstehen.

**Konkretes Erreichbarkeitsproblem:** 57 R-,24 B-,45 M- und18 P-Vorlagen deklarieren
„alleX“ oder Färbungsunabhängigkeit. Übertrüge man sie blind in die heutigen
Williams-nahen Filter (`roleRhythm`: Radius²0,16; Motiv-Neueinführung:0,0625), wären
bei X=1 selbst an ihrem eigenen Y/Z **57/57 R,24/24 B und45/45M** ausgeschlossen.
Das ist eine geometrische obere Schranke, noch ohne Harmonie-/Registerablehnung;
HE wird aktuell überhaupt nicht von diesen Filtern konsumiert.

Empfehlung für den späteren begrenzten Import, keine globale XYZ-Umstellung:

1. Harmonik weiter nach vollständigem XYZ auswählen.
2. Harmonische Voraussetzungen, Funktionen, Rollen, Mute/Solo und tatsächliche
   Instrumentenfähigkeiten prüfen.
3. Bei ausdrücklich X-unabhängigen R/B/M/P nur Y/Z für die Nähe verwenden;
   Register-/Farbwirkung bleibt musikalisch wirksam. Bei eingeschränkten Quellen
   deren ausdrücklich vorgegebenen Bereich prüfen.
4. „bevorzugt/eher“ als weiche Präferenz behandeln, nicht als Ausschluss;
   „für dunkle Kontexte tiefer“ als explizite Registervariante prüfen. M53 verlangt
   dagegen ausdrücklich Hochlage und verliert tiefer die gemeinte Farbe.
5. Danach begründete stilistische Gewichtung; keine dunklen Anker als heimliche
   Sperre und keine Gewichte zum Überwinden einer echten harmonischen Ungeeignetheit.

### Profil ohne Hauptmelodie und Gegenstimme

Früh hörbar durch mMaj7/Aug/ø7-Klangfelder, bewusst nichtfunktionale Pendel,
ungewöhnliche explizite Slash-Bässe, mechanische kurze Pulse, synkopierte
Interpunktion und große bewusst leere Fenster. H01/H03/H11/H19/H20/H25/H38/H45/H66/H67
liefern unterschiedliche Grundlagen; nur die jeweils vollständige D/A-Version
verwenden. R01/R02/R14/R15/R28/R33 bieten begrenzte frühe Rhythmusansätze.
R32 ist trotz einfacher Viertelstruktur wegen der KF-Dauer zunächst ausgeschlossen.

Kein genereller Held-/Warmklangverzicht, keine Pedalpflicht, keine Dauersperren
anderer geeigneter Spielweisen und kein permanent laufendes AR. Die Erfahrung mit
Barry spricht gegen solche Einschränkungen. Ohne GS/HM muss die Persönlichkeit
aus Harmonik, Bass, Registern, Pulse/Leerräumen und später Komponenten kommen.

## 6. Kleine aufeinander aufbauende Folgeaufgaben

Die Reihenfolge ist ein Vorschlag, keine Freigabe; vor Musikänderungen Williams
P2/P3 hören. Jeder Schritt nutzt denselben Kern. Keine separate Herrmann-Engine.

| Schritt | Begrenzter hörbarer Umfang | Voraussetzung / konkrete Abnahme |
|---|---|---|
| H0: Quellenentscheidungen | Sieben K-Fälle klären, Import-/Bestands-ID-Tabelle verbindlich machen. | Klare Bassdefinition H71; H04-Innenstimme; R12-Akzentvariante/Phase; Funktionsbezug B08/B28/B39; Harmoniezeit M08. Originale nicht still überschreiben. |
| H1: erstes vollständiges Begleitprofil | Kleine repräsentative Auswahl aus D-H und wirklich passenden A-R; bestehendes Herrmann-Profil anbinden, ohne GS/HM bereits erkennbar. | Geschützte exakte Akkorde, keine Dubletten; X-unabhängige Quellen lokal erreichen; tatsächliche LF/KF/LB/KB-Ausgabe und Pausen in Produktionsfahrten nachweisen. Ganze XYZ-Ränder mit Rückfall auf freie Strategie; keine künstliche8-Takt-Stasis. Manuelle Spielweisen/Follow/Mute/Solo erhalten. |
| H2a: unabhängiges Einzelpedal | Erst tiefer oder innerer Einzelton mit eigenem Beginn/Ende, etwa B01/B02/B05. | A/T/F/U-Legitimation für konkreten Ton, 12 Transpositionen; über mindestens zwei Akkord-/Wendungswechsel halten, exakt freigeben; Follow-Konflikte ausdrücklich entscheiden. Kein Duo-/Polybass erzwingen. Williams-Pedaltests mitnutzen. |
| H2b: eigenständige Bassfolge | Wenige konkrete Linien, z.B.B14/B15 und nach Klärung B08. | Eigenes Pitch-/Register-/Gate-Ziel, nicht globale Korrektur; beide Follow-Zustände, keine Halbton-Autokorrektur beabsichtigter Reibung; Pedal und bewegte zweite Bassstimme erst bei nachgewiesener Eignung. |
| H3a: lokale Tonabsicht und Vorräte | A/T/V/F/U für konkrete kurze Quellen; Ganzton zuerst, Hexatonik danach. | Gemeinsamer Kontext aller beteiligten Rollen, 12 Transpositionen, fremder Ton ohne Absicht abgelehnt, V erreicht Ziel, F/U bleiben erhalten. P3-Masken weiterverwenden. Exakte neue Akkordtypen bedarfsgerecht einzeln, nicht als Vorbedingung jedes R-Imports. |
| H3b: kurze Module | Eine wiedererkennbare Zelle mit begrenzter Wiederholung/Unterbrechung und identischer Rückkehr, dann Kürzung/Verlängerung. | Original unverändert, tatsächlich genutztes Material; Pausen/Mindestabstände passend zur Funktion. Statisches XYZ über 128 Takte ohne Pflichtsteigerung. Ton-/Rhythmusparameter einzeln ändern. Keine starre Szene oder universelle Formgrammatik. |
| H4a: exakte Strukturverschiebung | Ein Klangobjekt einen Halbton versetzen und zurück; danach zwei Komponenten. | Intervalle und Stimme-/Registerbezug exakt; normale Voice-Leading-Optimierung als andere Option behalten. Kein Rücksetzen von Zufallsindizes. |
| H4b: Polychord und Verschmelzung | Zwei vollständige Komponenten, zuerst feste, dann zwei geprüfte Register-/Synchronitätszustände. | S06/S07-Relation: gleiche Tonklassen/Notenzahl/Velocity; nur Lage/Zeit/Dauer ändern. Kurz-Zieldauern vorab geeignet beschreiben; AR mono bleibt mono. Bassdyaden nicht auf einen Ton reduzieren. Keine neue Ausgangszahl vor belastbarer Instrumentenprüfung. |
| H5a: exakte triolische/metrische Vorlagen | 4/4T und3/4↔6/8-Akzente über vorhandene Tick-Zeit konsumieren. |320 Tick-Triolen, Gruppierung2/3 nachvollziehbar; kein Schedulerumbau und keine Rundung auf 240 Ticks. Diesen kleinen Datenverbraucher bei Bedarf vor H4 vorziehen. |
| H5b: unabhängige Perioden | Ein3 gegen 4- oder5 gegen 8-Fall, dann Rollenwanderung einer Zelle. | Phase über Takt-/Harmonie-/Loopgrenzen exakt; gleiche Zellidentität, passende Polyphonie/Artikulation, keine unkoordinierten Vordergründe. Carpenter/Tangerine-Dream-Anwendungsfall mitprüfen. |
| H6: längere Entwicklung | Einzelne P-/S-Zielbögen, Kanon und Langzeitbeziehungen. | Nicht nur Speicher vergrößern: gemeinsame Ziele und Gelenke prüfen; dynamische Fahrt von Entwicklung bei statischer Position unterscheiden. Kein Erzwungensein von Eskalation/Entspannung. |

Für jeden freigegebenen Musikschritt: echte Produktions-MIDI-A/B-Beispiele,
Determinismus, Seek/Loop/Neustart, Blockgrößen und Live-/Exportgleichheit;
Regression unveränderter Profile/Rollen, geeignete Sanitizer-/Buildprüfungen,
kein Dateizugriff oder neue Allokation im Audiothread. Pro Schritt eine klar
benannte musikalische Frage für die Hörabnahme. Vorlagenregistrierung allein
ist kein Erfolgskriterium.

## 7. Offene Fragen und verbindliche Nicht-Vereinfachungen

Die sieben K-Fälle stehen einzeln im Inventar. Zusätzlich:

- Sind die zwei Kontextklänge einer kurzen M-Zelle zeitlich nacheinander oder
  alternative erlaubte Umgebungen? Wo Akkordtonlabels davon abhängen, einen
  eindeutigen Zeit-/Gültigkeitsbezug hinzufügen, nicht beide Masken blind vereinen.
  Bei M08 könnte ein Wechsel auf Zählzeit3 nötig sein: dann fehlt zusätzlich die
  untertaktige Dauerdefinition in `Chord.bars` (int), obwohl die Tick-Zeitleiste
  den Zeitpunkt bereits abbilden kann. Nicht den Scheduler wieder öffnen.
- „Moll gesamt“ und „Chromatisch“ sind keine vorhandenen universellen Modi. Für
  eine konkrete unveränderte Zelle kann lokale P3-Autorisierung genügen; für freie
  Weiterentwicklung muss der Vorrat explizit und begrenzt definiert werden.
- Welche tatsächlichen externen Patches erlauben die langen Noten auf KF/KB/TU
  und die Bassdyaden? Die MIDI-Studie beantwortet diese Instrumentenfrage nicht.
- Exakte Parallelführung am Übergang/Loop muss Bassvorgaben respektieren: bei H15
  stehen vier chromatisch fallende Aug-Wurzeln, am Rücksprung wieder C. Die
  enharmonische Aug-Symmetrie ersetzt keinen präzisen Bass-/Stimmenplan.
- Dynamische XYZ-Vorschläge sind keine statischen H-Anker. Vorlagenanker und
  Entwicklungsregeln getrennt belassen. Geometrische Erreichbarkeit beweist weder
  musikalische Vielfalt noch passende Besetzung.

Nicht übernehmen: eine Polychordhälfte entfernen; polyphonen Bass auf den tiefsten
Ton kürzen; lange Noten auf Kurz-Zielen abschneiden oder unangekündigt umrouten;
eigene Perioden taktweise neu starten; Begleitlinien einfach der GS zuweisen;
F/U auf nahe Akkordtöne korrigieren; für jedes Stück eine Künstler-Sonderengine
schreiben. Nicht korrekt umsetzbare Quellen bleiben zurückgestellt.
