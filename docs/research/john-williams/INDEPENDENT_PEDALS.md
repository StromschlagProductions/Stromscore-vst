# Gemeinsames unabhängiges Einzelpedal – erster musikalischer Schritt

## Ausgangspunkt und Abnahme

Lokaler Ausgangspunkt: `1d3c1d5` auf `develop/composition-core-prototype`, einschließlich der kanonischen Forschungsarchive und Bestandsaufnahmen. Die Engine entspricht musikalisch dem Windows-Stand `023b0a6`. Williams P2/P3 ist vom Anwender als musikalische Entwicklungsgrundlage positiv gehört: [Abnahme](../../development/ACCEPTED_REFERENCE_023b0a6.md). Die folgende Erweiterung ist technisch geprüft; ihre musikalische Hörabnahme steht separat aus.

## Musikalische Anbindung

Nur Williams Score, automatischer Bass und „Folgt Akkorden EIN“ erhalten zunächst eine neue Anbindung:

| Bestehende Vorlage | Stabile ID | Klangfolge in C | Explizites Pedal |
|---|---|---|---|
| JW-H03 | 40003 | C (2), D/C (2), C (2), D/C (1), Cmaj7 (1) | C; lydische Schwebe |
| JW-H50 | 40050 | Cmaj7 (2), Ab/C (1), E/C (1), Ab/C (1), E/C (1), Cmaj7 (2) | C; pantriadische Wanderung |
| JW-H61 | 40061 | Csus2, Dsus2/C, Fsus2/C, Ebsus2/C, Csus2, Absus2/C, Bbsus2/C, Csus2; je 1 Takt | C; Sus-Farbwechsel |

Die Vorlagen bleiben unverändert, einschließlich ihrer XYZ-Anker und Auswahlgewichte. Die Bassbindung jeder Vorlage ist bereits ausdrücklich notiert. JW-B01 belegt das lange Tonikapedal als musikalisches Verfahren, unter anderem in Verbindung mit H03. Die hier gewählte **16-taktige Lebensdauer** ist eine begrenzte kompositorische Implementierungsentscheidung, keine Behauptung, B01 oder die Modellstudien würden bereits vollständig und notengetreu abgespielt. H50/H61 werden aufgrund ihrer eigenen expliziten Pedalvorgaben angebunden.

So wird der bisher mehrfach angeschlagene Basston tatsächlich zu einem gehaltenen Fundament unter wechselnden Farben. H03s D/C und H50s E/C dürfen die absichtlich gesetzten Spannungen behalten. H17 und H46 haben dagegen **bewegte** Slash-/Dissonanzbässe und erhalten diese Bindung ausdrücklich nicht.

Es werden keine neuen Wendungen, Tonklassen, Melodien oder Rhythmuszellen eingeführt. Weder die Arpeggio-Phrasierung noch die Motivplanung werden umgestaltet. Andere Profile und POP/ROCK erhalten keine Anbindung.

## Gemeinsames Modell und Ausführung

- `Source/PedalPlan.h`: eigenständiger `PedalPlan` mit nominalem Beginn/Ende in 64-Bit-Ticks bei 960 PPQ, absoluter Tonklasse und `BassRelation`. Die Zustände `chordBound`, `independentPedal` und `authorizedDissonancePedal` sind ausdrücklich getrennt. Der akkordgebundene Bass bleibt der normale Ausgabepfad, solange kein unabhängiger Plan besteht.
- `permits()` unterscheidet einen gemeinsamen Akkordton von einem absichtlich fremden Pedal. Für Letzteres müssen **zugleich** Planart, lokale Autorisierung und der exakt übereinstimmende explizite Basston passen. Eine Autorisierung gilt nicht für beliebige andere Töne oder andere Harmonievorlagen. Widersprechende Slash-Bässe werden abgelehnt.
- `CompositionPolicy.h`: kleine, tatsächlich verwendete `PedalPolicy` mit Aktivierung und Lebensdauer. Standard aus; nur Williams aktiviert sie. Keine neuen Benutzerparameter und keine persistierte zusätzliche GUI-Einstellung.
- `Generator::preparePedal()`: begrenzte Williams-Quellbindung, Prüfung der gesamten aktuell verfügbaren Wendungs-Zeitleiste und Validierung gegen den bestehenden gemeinsamen Ausgangs-/Instrumentenfähigkeitskatalog. Der Plan wird bei XYZ-bedingten Harmoniewechseln erneut geprüft. Eine weitere Wendung darf ihn nur tragen, wenn ihre tatsächlichen Akkorde/Bassvorgaben dies zulassen. Andernfalls endet er, statt den Fremdton zu korrigieren oder eine unzulässige Bassvorgabe zu übergehen.
- MIDI auf dem bestehenden **Bass-Lang-Ausgang**. Tonklasse bleibt erhalten; Oktavfaltung darf den Ton in den zulässigen Umfang bringen. Die tatsächlich klingende Lage bleibt bei XYZ-bedingten Registervorschlägen innerhalb eines Pedalplans erhalten; bewusste Oktav-, Tonart- und Kanaländerungen werden dagegen übernommen. Ein zu enger/unpassender Umfang führt zur Ablehnung des Pedals, nicht zum Ersatz durch einen anderen Akkordton. Tonhöhensteuerung, Sustained-Spielweise, Verfügbarkeit, monophone Eignung und Dauergrenzen werden über `suitable()` geprüft. Das sind Generatorannahmen, keine Erkennung eines externen Patches.
- Die bestehende `Active`-Notenliste erhält eine explizite Besitzmarkierung. Es gibt keine zweite Notenverwaltung. Harmonie-/Phrasenfreigaben übergehen diesen Besitzer; der normale Basspfad erzeugt während des Pedals keine konkurrierenden Bassnoten. Das nominale Enddatum wird durch den bestehenden Dispatcher freigegeben und nicht geswingt.
- Bei einer physisch identischen Note auf einem gemeinsam genutzten MIDI-Kanal verhindert der Pedalbesitz den Neuanschlag. Jeder Ausgang behält seinen Anspruch; erst der letzte Anspruch erzeugt das physische Note-off. Andere Tonhöhen/Kanäle folgen weiterhin der vorhandenen Verwaltung.

Die 16-taktigen Lebensfenster beziehen sich auf den Szenenursprung. Eine neue autorisierte Lebensperiode darf bewusst neu angeschlagen werden; Akkord- und achtaktige Phrasengrenzen innerhalb der Lebensperiode tun dies nicht. Ein späterer Einstieg kann ein bereits angebrochenes Fenster nutzen. Das ist keine neue Formgrammatik und kein generelles Aktivitätsraster für andere Rollen.

## Benutzerkontrolle, Ende und Transport

Manuelle Bassspielweisen, Follow AUS, Stummschaltung/Solo, ungeeignete Instrumentenfähigkeiten, Ruhe- und szenische Basspausen haben Vorrang. Geplante Szenenenden begrenzen die Lebensdauer. Der bisherige Basspfad bleibt nach einer Ablehnung verfügbar. Ein erlaubter Durchgangsakkord würde zusätzliche Harmonieprüfung benötigen; der erste Pedalverbraucher setzt deshalb nur auf Harmoniekontexte ohne automatische Zwischenakkorde. Die drei geschützten Williams-Vorlagen erfüllen das auch bei eingeschaltetem Durchgangsschalter.

Stop, Profil-/Genrewechsel und Reset geben den Notenbesitz sicher frei. Beim Seek/Loop werden physische Noten zunächst freigegeben und am Ziel gechast. Ein bekanntes, zeitlich noch gültiges Pedalintent bleibt bei einem warmen Sprung erhalten, muss aber erneut zur Zielharmonik und den Benutzer-/Instrumentenbedingungen passen. Bei kaltem Start wird nur aus einer explizit angebundenen Zielvorlage ein Pedal rekonstruiert; unbekannte musikalische Vorgeschichte wird nicht erfunden. Die bereits akzeptierte Einschränkung der Übergangsstimmführung bei kaltem Seek wird nicht verändert.

## Vergleich und Hörmaterial

Reproduzierbar mit `python3 scripts/validate_pedals.py <Arbeitsverzeichnis>`. Das Skript baut den tatsächlichen Produktionsprobe gegen `1d3c1d5` und den aktuellen Quellstand. Es vergleicht reale MIDI-Ereignisse und Harmonieübernahmen, nicht nur geplante Daten.

- [Messdaten](INDEPENDENT_PEDALS_RESULTS.json): statische Positionen, langsame/schnelle XYZ-Fahrten, sämtliche bestehenden Williams-Wendungen, zwölf Transpositionen der drei Anbindungen sowie Kontrollfälle für andere Profile/Genres und manuelle Einstellungen.
- [A/B-MIDI-Hörpaket](INDEPENDENT_PEDALS_AB.zip): je 128 Takte H03/H50/H61, vorher/nachher, 100 BPM, D, 4/4, unveränderte Instrumenten-/Kanalzuordnung. A und B mit denselben Patches hören. Enthalten sind vollständige Engine-Renderings einschließlich anderer Rollen.

Außerhalb der gezielten Anbindung wird die vollständige Ereignisfolge bytegenau verglichen. Innerhalb der Anbindung bleiben die Ereignisfolgen der Nicht-Bass-Rollen je Ausgang, Kanal und Ton/Controller exakt gleich. Durch andere Laufzeiten der Bass-Claims kann die Reihenfolge **gleichzeitiger Note-offs verschiedener Töne auf demselben oder auf verschiedenen Ausgängen** variieren; dies verändert weder Tonhöhe noch Anschlag, Gate oder Zeitpunkt der anderen Rollen. Diese Änderung wird nicht als musikalische Regression verschleiert.

Bei freier Auswahl über 128 Takte bleiben die kontrastreichen mittleren und intensiven Testpositionen vollständig bytegleich. Zwei helle ruhige Positionen enthalten tatsächlich Pedale: XYZ 0,85/0,20/0,20 liefert 79 → 46 Bassanschläge, XYZ 0,85/0,25/0,80 liefert 231 → 183. Dazwischen bleiben die normalen Bassfiguren anderer ausgewählter Wendungen erhalten. Die schnelle XYZ-Fahrt liefert 647 → 643 Bassanschläge, mit einem längsten Bass-Gate von 10 Vierteln; inkompatible Folgeharmonik verhindert hier bewusst das volle 16-Takt-Pedal. Die langsame Fahrt trifft keine wirksame Pedalanbindung und bleibt bytegleich. Die tatsächlichen Wendungsübernahmen sind in sämtlichen Fällen identisch mit vorher.

### Konkrete tatsächliche MIDI-Folge: JW-H03 in D

64 Takte, 100 BPM, 4/4, XYZ 0,85 / 0,30 / 0,25, Variation vom Probe am Anker gewählt, beide Motivrollen verfügbar. Vorher **36 Bass-Note-ons**, nachher **4**. Das ist eine Prüfung dieser gezielten Pedalstelle, kein Zielwert für das allgemeine Bassverhalten.

- Vorher: MIDI-Note **50 (D)**, Note-on bei Viertelposition 0; erneute Anschläge unter anderem bei 8, 16, 24, 28 und 32. Die ersten Velocitywerte sind 70; bei späteren rhythmischen Zellen auch 75.
- Nachher: dieselbe Note 50 bei Viertelposition **0**, Note-off erst bei **64**, dort Beginn der nächsten eigenen Lebensperiode. Weitere Perioden beginnen bei 128 und 192; Stop bei 256 gibt die letzte Note frei. Die erste Note hat weiterhin Velocity 70. Kein Neuanschlag bei den dazwischenliegenden Akkord- oder achtaktigen Phrasengrenzen.
- Oberstimmenkontext der ersten acht Takte: **D (2 Takte), E/D (2), D (2), E/D (1), Dmaj7 (1)**. Die ausdrücklich notierte Spannung D unter E-Dur bleibt bestehen. Das Pedal hält über den erneuten Wendungsbeginn in Takt 9 hinweg; die oberen Akkorde entwickeln sich wie zuvor.

## Grenzen und Folgeaufgaben

Dieser Schritt bindet ein tiefes, monophones Einzelpedal an drei vorhandene Williams-Quellen. Er implementiert keine Basssequenzen, hohen/inneren Doppelpedale, freien Pedalvorlagenimport, Polychorde oder Ereignisfelder. Er garantiert nicht, dass ein externer Patch MIDI-Haltezeiten akustisch umsetzen kann. Weitere Künstler benötigen eigene begründete Quellbindungen; sie bekommen nicht automatisch Williams' Pedalregel.

Die Auswahl und harmonische Entwicklung bei statischem XYZ bleiben unverändert. Eine inkompatible Folgewendung darf ein Pedal beenden. Es wird weder harmonische Vielfalt zugunsten des Pedals eingeschränkt noch ein Pedal durch beliebige Harmonien erzwungen. Ein späterer kleiner Schritt könnte einzelne kanonische Herrmann-/Carpenter-Pedale mit ausdrücklich notierter Lebensdauer und Dissonanzberechtigung an denselben Kern anbinden. Das ist hier nicht implementiert.

## Abschließende Prüfergebnisse

- **198 Produktions-A/B-Fälle**: 156 vollständig bytegleich, 42 beabsichtigte Bassänderungen. Alle 100 ausdrücklich geschützten Profil-/Genre-/Bedienkontrollen sind vollständig bytegleich. Für Williams bleiben alle Nicht-Bass-Ton-/Controllerströme unverändert; Harmonieübernahmen ebenfalls.
- **26 Transport-/Determinismus-/Blockfälle** im Produktionsprobe: 3/8, 5/8, 7/8 und 4/4; Swing 0/0,35; Stop/Neustart, Loop und Seek; zusätzlich langsame/schnelle XYZ-Fahrten über 128 Takte bei 512/127 Samples. Die Ergebnisse sind bei Wiederholung identisch.
- **36 transponierte Quellfälle** im gezielten Pedaltest: drei Vorlagen × zwölf Tonarten, jeweils 32 Takte bei 512/2048 Samples. Zusätzlich Dissonanzberechtigungen, ungeeignete Bereiche, manuelle Spielweisen, Follow AUS, ausgeschaltete Policy, nicht angebundene bewegte Slash-Bässe, warmer Seek/Loop und sichere Freigabe gemeinsam besessener physischer Noten. XYZ verändert die klingende Lage nicht; bewusste Oktav-/Tonartänderungen werden übernommen.
- **4/4 echte JUCE-Prozessor-Prüfgruppen bestanden**, darunter **12 neue Pedal-Live-/SMF-Exportfälle** (drei Quellen, zwei Tonarten, Swing an/aus, je 64 Takte), mit identischen musikalischen Ergebnissen, korrekter Notenbilanz und C-/C++-Heap-Wachen im Audioaufruf.
- Gezielter finaler Pedaltest unter **ASan/UBSan ohne Befund**, einschließlich Allokationswache.
- **7/7 Paketprüf-Fixtures bestanden**; sechs A/B-MIDI-Dateien bei 960 PPQ, ZIP-CRC fehlerfrei.

**Reguläre Core-Suite: 61/61 bestanden**, 1127,09 Sekunden; einschließlich historischer Harmonie-, Zeitbasis-/Scheduler-, Rhythmus-, Akkordlagen-, Motiv-/Rollen- und Profilwechselregressionen sowie des neuen Pedaltests. Alle technischen Prüfungen lokal unter Linux; kein Windows-Build, kein Push und kein Release in diesem Auftrag.
