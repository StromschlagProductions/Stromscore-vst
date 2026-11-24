# Erweiterbare Akkorddefinitionen

Ausgangspunkt `e4cb881`, Entwicklungsbranch `develop/composition-core-prototype`.
Keine neuen produktiven Wendungen, Künstlerprofile, GUI-Auswahleinträge, XYZ-Regeln oder Zeitmodelle.

## Umsetzung

Die 18 vorhandenen Definitionen bleiben in Identität, Zahlenwert und Intervallen unverändert. An die Datenregistrierung `data/harmony/chord_types.json` sind angehängt:

| ID | Definition | Intervalle |
|---|---|---|
| 18 | Major6 | 0,4,7,9 |
| 19 | MinorAdd9 | 0,3,7,14 |
| 20 | Major9 | 0,4,7,11,14 |
| 21 | Dominant9 | 0,4,7,10,14 |
| 22 | Dominant7Sus4 | 0,5,7,10 |
| 23 | DiminishedTriad | 0,3,6 |
| 24 | Major7Sharp5 | 0,4,8,11 |
| 25 | Major7Sharp11 | 0,4,7,11,18 |
| 26 | Major7Sus2 | 0,2,7,11 |

MinorAdd9 enthält keine Septime und unterscheidet sich von Min9. DiminishedTriad enthält keine verminderte Septime und unterscheidet sich von Dim7. Sus-Strukturen erhalten keine ergänzte Terz. Major7Sharp5 behält die übermäßige Quinte als Pflichtfarbe, Major7Sharp11 die große Septime und erhöhte Undezime.

Der Generator akzeptiert weitere eindeutig benannte registrierte Definitionen mit fortlaufenden stabilen Werten. Es gibt keine neue Tabelle von Akkordnamen im Kompositionskern: Namen, Suffixe, exakte Intervalle und Mollklassifizierung werden aus derselben Quelle generiert. Ein Semantikfingerabdruck schützt weiterhin die ersten 18 Definitionen. Unbekannte Typreferenzen, doppelte Identitäten, unzulässige Intervalle und falsche Zahlenwerte werden offline zurückgewiesen. Der Inventarexporter verwendet jetzt ebenfalls die generierten Typnamen.

Die GUI-Auswahl eigener Akkorde bleibt bei den bisherigen 18 Einträgen. Die neuen Definitionen sind für validierte Katalogvorlagen und synthetische Tests verfügbar. Ein direkter freier Intervallvektor je Akkordslot wurde nicht hinzugefügt. Registrierung in der gemeinsamen Typquelle reicht für unterstützte neue Strukturen aus; diese können anschließend in beliebig vielen Vorlagen referenziert werden.

## Bestandsaufnahme und Grenzen der gemeinsamen Ausgestaltung

- `ChordShape` und `ChordIntent` halten maximal fünf definierte Intervalle. `buildAnchor()` kann eine Grundtonoktave ergänzen; der Voicing-/MIDI-Pfad hat maximal sechs gleichzeitig geplante Harmoniestimmen. Es wurde keine dieser Kapazitäten erhöht.
- Ganze Halbtonintervalle bleiben erhalten, nicht lediglich ihre Tonklassen. 14 und 2 sowie 18 und 6 bleiben verschiedene Quelldaten. Modusprüfung und harmonische Mitgliedschaft verwenden dagegen bewusst Modulo 12. Register und Umkehrungen sind Ausgestaltung; die Stimmführung darf Töne oktavieren. Eine None wird nicht als garantiert mindestens 14 Halbtöne über dem Grundton ausgegeben. Auch Sus2 kann im oberen Register liegen. Ein differenziertes obligatorisches Register-/Funktionsmodell ist noch nicht vorhanden.
- `coloredChordType()` verändert weiterhin nur die bisherigen einfachen Maj-/Min-/MinMaj7-Typen nach den bisherigen Z-Schwellen. Die neuen expliziten Farben werden unter flexibler und geschützter Strategie nicht automatisch umgedeutet.
- `prepareVoicingPlan()`, `buildAnchor()`, `planHarmony()` und `voiceleading::lead()` verwenden die angegebenen Intervalle bzw. Tonklassen. Verbindungen zwischen alten und neuen Typen benötigen keinen Namenssonderfall. Bassanker und Slash-Vorgaben sind hiervon getrennt.
- `realizeChord()` markiert alle definierten Klassen außer Grundton und reiner Quinte als Pflichtfarben. Reduktion darf einen vom stabilen Bass vertretenen Grundton und eine entbehrliche reine Quinte weglassen, nicht aber Terz, Septime, Sexte, None, Sus-Ton, veränderte Quinte oder #11. Die vorhandene Quint-/Quartal-Sonderbehandlung bleibt unverändert.
- Bei zu kleiner angeforderter Polyphonie konnte die bisherige Funktion auf die zu große ursprüngliche Besetzung zurückfallen. Für diese Fälle liefert sie jetzt leere Noten und `insufficientVoices=true`. Auch eine wegen der geforderten offenen Lage erfolglose Suche darf nicht auf eine zu große Besetzung zurückfallen. Es wird keine charakteristische Farbe durch einen bequemeren Ersatzton ersetzt. Mit normaler Standardpolyphonie sechs bleibt das bisherige Verhalten erhalten.
- Dies ist keine automatische Erkennung externer Patches: Die Harmonieausgänge nehmen weiterhin sechs Stimmen an. Die explizite Polyphonie wird in der vorhandenen automatischen Pop/Rock-Besetzungsplanung berücksichtigt; manuelle und andere historische Pfade besitzen nicht schon dadurch eine allgemeine Instrumentenverteilungsengine. Kleinere tatsächlich geladene Patches sind erst bekannt, wenn ihre Fähigkeiten ausdrücklich konfiguriert werden können.
- Die zusätzliche kontextuelle Dominant-Auflösungshilfe erkennt bisher ausdrücklich Dom7/Dom7b9. Neue Dominant9-/7Sus4-Klänge erhalten die normale tonklassentreue Stimmführung, aber noch keine neue automatische Funktionserkennung. Eine spätere generische Ableitung aus Akkordmerkmalen ist gesondert zu testen; sie wurde nicht als neue musikalische Übergangsregel vorgezogen.
- Bass, Arp, Linien und Motive verwenden größtenteils `shape.n` und `iv[]`. Einzelne bestehende Figuren bevorzugen weiterhin die ersten drei oder vier Töne: SID-Arp erste drei, Walking-Bass bis vier, generische Pop-Linien kurze Figuren. Das begrenzt die melodische Vorstellung aller Zusatztöne, verändert aber nicht ihre Definition oder die Pflichtfarben der Fläche. Manche freien Figuren enthalten historische Nicht-Akkordtöne; bei geschützter Begleitung greift weiterhin deren bereits vorhandener Farbschutz.
- `minor` ist eine grobe vorhandene Ausdrucksklassifikation, keine vollständige Funktionstheorie. Modusprüfung betrachtet den gesamten Tonvorrat einer Wendung; chromatische oder mehrdeutige neue Farben führen kontrolliert zum vorhandenen Rückfall ohne zusätzliche modale Durchgangsstrategie.
- MIDI-Notenverwaltung und tatsächliche Live-/Exportwege verwenden denselben Generator. Zusätzliche Definitionen bedeuten keine neuen MIDI-Ziele oder Kanäle. Alle Definitionen sind statische Daten; keine Ladeoperation, Validierung oder Heap-Allokation im Audiothread.

## Sichere Erweiterungsgrenze

Aktuell validiert: zwei bis fünf aufsteigende, unterschiedliche ganze Intervalle im Bereich 0–23, beginnend mit 0. Unterschiedliche Oktavlagen derselben Tonklasse sind als Intervalle zulässig; der vorhandene Fifth-Typ enthält beispielsweise 0/7/12. Mehr als fünf Intervalle, Einzeltondefinitionen und Intervalle ab 24 werden ausdrücklich abgewiesen.

Ein zusätzlicher registrierter Quintstapel 0/7/14/21 wird im Datenpfad getestet. Ähnlich lassen sich begrenzte Quartenstapel oder Cluster darstellen, ohne neue Typnamenbedingungen im Kern. Das garantiert aber noch keine passende musikalische Ausgestaltung: die bisherigen Verdopplungs-/Reduktionsregeln unterscheiden nicht jede denkbare Struktur. Vor einem produktiven Import solcher Klänge sind strukturelle Pflichttonrollen und Verdopplungsregeln gesondert zu spezifizieren und zu prüfen. Die bestehende Quartal-Definition bleibt unverändert.

Eine flache gemeinsame Tonklassenmenge wäre kein echter Polychord: getrennte Teilakkorde, unabhängige Register, funktionale Beziehungen und Instrumentenzuweisung werden nicht modelliert. Keine Polychord-Engine implementiert.

## Prüfungen

`ChordDefinitionTests.cpp` prüft die neun Definitionen unabhängig gegen die vorgegebenen Intervalllisten: zwölf Transpositionen, zwei Register, alle vier bestehenden Besetzungsstrategien und Polyphonie 1–6. Geprüft werden Pflichtfarben, Bassklassen, flexible/geschützte Strategie, alle Z-Bereiche, Stimmführung und kontrollierte Moduserkennung. 2472 Kombinationen liefern zulässige Besetzungen; 2712 lehnen eine nicht realisierbare Stimmenzuteilung kontrolliert ab. Diese Zahlen sind technische Abdeckung, kein musikalisches Optimierungsziel.

Die synthetischen Katalogfixtures der vorhandenen `HarmonyColorationTests` werden aus allen 27 registrierten Definitionen erzeugt. Sie prüfen 15552 vollständige Acht-Takt-Renderings über zwölf Transpositionen, XYZ und beide Follow-Zustände, beide Färbungsstrategien, tatsächliche Harmonie-/Arp-Klassen, explizite Slash-Bässe, offene/reduzierte Lagen, enge Register sowie Transport-/Block-/Tempo-/Swing-Verhalten. Produktive Vorlagen bleiben dabei unverändert.

`compare_chord_definitions.py` vergleicht alle 87 produktiven IDs × drei Profile × linear/Seek-Loop-Neustart explizit gegen `e4cb881` (522 vollständige 32-Takt-MIDI-Vergleiche). Die vorhandenen historischen Vergleichssuiten bleiben zusätzlich aktiv. Deren Faktenprobe beschränkt den Vergleich der Akkordregistrierung bewusst auf die alten 18 Definitionen; die neuen Definitionen werden unabhängig durch Daten- und Renderprüfungen geprüft, nicht aus dem Vergleich verborgen.

## Kleine Folgeaufgaben

1. Strukturelle Pflichtton- und Verdopplungsmetadaten für registrierte Cluster/Stapel vor deren produktivem Import ergänzen; vorhandene Standardwerte als Regression erhalten.
2. Polyphoniebeschränkungen bei Bedarf vorlagenübergreifend durch alle manuellen und Genrepfade koordinieren, sobald tatsächliche Patchfähigkeiten konfigurierbar sind. Keine stumme Annahme über externe Instrumente.
3. Erst danach entscheiden, ob Einzeltonflächen bzw. mehr als fünf definierte Intervalle ein erweitertes Voicing-Modell oder zeitliche Verteilung benötigen. Keine bloße Vergrößerung aller Arrays.
4. Mehrschichtige Polychords als eigenständigen späteren Planungsauftrag behandeln.

Die verbindliche Profil-Roadmap bleibt bestehen; keine Barry-/Herrmann-/Williams-/Wang-Chung-Sonderlogik wurde eingeführt. Eine musikalische Qualitätsbewertung erfordert weiterhin einen Hörtest.

## Ergebnisse

35/35 Gesamttests bestanden. 522 vollständige 32-Takt-Regressionen aller 87 produktiven Wendungen in drei Profilen bytegleich zu `e4cb881`; Prüfsummen in `CHORD_DEFINITION_REGRESSION.json`. Die synthetische Katalogmatrix besteht 15552 Acht-Takt-Renderings über alle 27 Definitionen. Konkrete erste MIDI-Lagen und tatsächliche Klassen je Ausgang für beide Strategien und drei Z-Werte stehen in `CHORD_DEFINITION_MIDI_EXAMPLES.csv` (Typwerte 18–26 sind die neuen Definitionen; die flexible Maske umfasst absichtlich auch bestehende Zwischenharmonien/Reibungen).

Der echte Processor-/SMF-Test mit temporären synthetischen Vorlagen verwendet die neuen Typen auf den ersten neun Pop/Rock-Ankern und besteht 162 Fälle (neun Typen × drei Transpositionen × zwei Follow-Zustände × drei Profile), einschließlich C-/C++-Heap- und Notenbilanzprüfungen. Aufruf für einen entsprechend vorbereiteten isolierten Testkatalog: `ProcessorTests --extended-chords`. Die produktiven Vorlagen wurden nach dem Test wiederhergestellt.

ASan/UBSan für `ChordDefinitionTests` und bestehende `EngineTests` ohne Befund; 7/7 Paketprüf-Fixtures bestanden. Keine neuen produktiven Wendungen oder GUI-Auswahleinträge. Weitere Ergebnisse des abschließenden Produktionsbuilds sind unten festgehalten.

Abschließender Produktionsstand: Linux-VST3 erfolgreich gebaut, Bundle-/ELF-/Versionsmetadaten geprüft. Der unveränderte produktive 87er-Katalog besteht den tatsächlichen Processor-Gesamttest einschließlich der bestehenden 54 Import-Live-/SMF-Fälle. Kein Windows-/pluginval-Lauf, kein Push und kein Release in diesem Auftrag.
