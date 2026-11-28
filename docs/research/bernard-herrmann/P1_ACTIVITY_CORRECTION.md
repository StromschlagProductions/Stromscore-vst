# Herrmann P1 – Rollenaktivität und gezielte Korrektur

28.11.2026 · Vergleichsbasis `0874b02` · Entwicklungsbranch `develop/composition-core-prototype`.

## Musikalische Referenz und Umfang

Die vom Anwender positiv gehörte Herrmann-Handschrift bleibt die Grundlage: bedrohliche hohe Streicher, basslose Klangfelder und Mehrdeutigkeit im Bereich „Lauern“. Siehe [dokumentiertes Hörfeedback](../../development/ACCEPTED_REFERENCE_0874b02.md). Das Feedback ist keine exhaustive Abnahme aller Parameterkombinationen. Die Hörabnahme dieses Korrekturpakets steht noch aus.

Keine neuen Quellen, Profile, Ausgänge oder kreativen Parameter. Die 54 H-, 28 R-, 18 B- und 22 M-Quellen bleiben dieselben. Kanonische Forschungsdateien und generierte Vokabulardaten sind unverändert. Die zusätzlich beauftragten CC-Änderungen gelten dagegen ausdrücklich für alle Profile/Betriebsarten.

## Tatsächliche Ursachen und Korrekturen

### 1. Der gemeldete Bassausfall: Tonumfang vor Oktavplatzierung geprüft

Reproduktion mit **getrennten Kanälen 3/4**, Bass −2 Oktaven, Umfang C0–G3 (in STROMSCORE MIDI **24–67**), Follow EIN, AUTO, D/100 BPM/4/4, unbegrenzter Betrieb ohne Aufbau/Fahrt. Andere Host-Notennamen können abweichen. Der Umfang begrenzt den klingenden Ton nach der Oktavverschiebung.

`LayerAdapter.h::layerPlayable` prüfte die rohen Quellentöne nach Benutzeroktave, ohne die vorhandene Oktavplatzierung in den Benutzerumfang zu berücksichtigen. Beispielsweise liegt ein Quellbass um MIDI36 nach −24 zunächst bei12. Der normale Generator platziert ihn in den zugelassenen Bereich; der neue Schichtpfad lehnte ihn vorher ab. Weil dieser Pfad den Bass musikalisch besitzt, kam anschließend auch keine reguläre Ersatzbegleitung. Das erklärt den Unterschied zu Neutral/Barry/Williams bei unverändertem Routing.

Die Korrektur verwendet `layerRangeShift`, `layerBoundBassShift`, `layerFits` und `LayerUse::placement`: Ein vollständiger Figuren-/Bassverlauf erhält einen gemeinsamen gültigen Oktavversatz. Keine einzelnen Töne werden ausgelassen, harmonisch ersetzt oder unabhängig über die Registerkante gefaltet. Bei bewegten notierten Bassvorgaben gilt der gesamte Bassverlauf auch für kürzere Figuren und den anschließenden harmonischen Verbraucher als gemeinsamer Registervertrag. Sonst könnte ein absteigender Halbton beim Verbraucherwechsel zum aufsteigenden großen Septimsprung werden.

Konkreter Regressionstest HE-H07, D, −2 Oktaven, MIDI24–67: der zusammenhängende Bassverlauf ist **38–37–36–35**, sowohl ohne gewählte Zusatzfigur als auch mit normaler automatischer Figurenauswahl. Eine zu enge Spanne, in die das vollständige Material nicht passt, wird weiterhin abgelehnt. A/T/V/F/U, explizite Slash-Bässe, Dauergrenzen und instrumentelle Eignung bleiben verbindlich.

### 2. Zusätzlicher Routingfehler – getrennt von der Anwenderursache

`layerRoute` sperrte Lang- und Kurz-Ausgänge derselben Rolle gegenseitig, sobald beide denselben MIDI-Kanal benutzten. Das widersprach der vorhandenen Bedienmöglichkeit, beide Spielweisen auf demselben Instrument zu verwenden. Jetzt sind solche Geschwisterzuordnungen möglich. Verschiedene aktive Rollen auf einem unbekannten gemeinsamen Patch bleiben vorsichtig ausgeschlossen.

Ein gemeinsamer Basskanal bleibt physisch monophon: ein unabhängiges Pedal hat Vorrang; eine bewegte Kurzfigur ersetzt die lange Fallback-Stimme; alte Ansprüche werden beim Wechsel freigegeben. Getrennte Kanäle behalten ihre getrennten Spielweisen. Für LF/KF wird keine automatische externe Artikulationserkennung behauptet. Ein Patch muss selbst zur gewählten Ausgabe passen.

### 3. Stich war unbeabsichtigt komplett im Besitz eines leeren Schichtpfads

`layerOwns(OutStich)` reservierte ST, obwohl keine einzige `FigurePart::effect` registriert ist. Dadurch wurde die vorhandene feste Stich-Funktion unterdrückt. Besitz wird nun nur bei einer tatsächlich vorhandenen Effektfigur übernommen. Der bestehende ST-Pfad arbeitet wieder; Im geprüften Festnotenmodus bleibt **MIDI36 der feste, nicht transponierte Standardtrigger**; die bestehende ausdrückliche Stich-Modus-/Notenwahl wird nicht verändert. Keine neue Effektgrammatik oder Häufigkeitsregel.

### 4. Manueller Bass bei H57

Der kurze H57-Eintrittsimpuls umging bisher die AUTO-/Follow-Zuständigkeit. Er verlangt jetzt wie die übrigen Figuren `layerOwns(OutBassShort)`. Manuell gehaltene Spielweise und Follow AUS erzeugen dadurch keinen unbestellten Kurzimpuls. Die autorisierte H57-Automatik bleibt erhalten.

### 5. Zu harte zusätzliche XYZ-Grenze bei Herrmann-Motiven

`ScoreEngine.h::authoredMotif` verwendete neben der weichen Auswahlgewichtung eine harte Nähegrenze von `.25²`, auch wenn eine Herrmann-Quelle harmonisch vollständig geeignet war. Nur für den vorhandenen Herrmann-Schichtpfad entfällt diese zusätzliche harte Grenze. Weiche XYZ-Gewichtung, Quellharmonie, vollständiges Zeitfenster, Register, Auflösung von V-Tönen und die Bindung eines bereits gespielten Präfixes bleiben bestehen. Keine zufällige Materialübernahme und keine pauschale Aufhebung harmonischer Schutzprüfungen.

Die frühere Aussage „nur M07“ beschrieb einen begrenzten Produktionsausschnitt, keine globale technische Beschränkung auf eine Vorlage. Im erweiterten Vergleich sind bereits vor der Korrektur **10**, danach **13** verschiedene Quellen an tatsächlich ausgegebenen Motivnoten nachweisbar. Alle22 Quellen bestehen zusätzlich ihren ausdrücklichen harmonischen Kontexttest in zwölf Tonarten und beiden melodischen Stimmen. Dies ist nicht mit natürlicher Auswahl aller22 in einem Durchlauf gleichzusetzen.

## Tatsächlicher Plugin-Prozessor: exakte Anwenderkonfiguration

64 Takte, D, XYZ(.50/.85/.80), Variation3, alle Rollen an, Live und exportiertes SMF verglichen. Zahlen sind Note-ons auf den physischen Kanälen; kein erzwungener Katalogindex.

| Konfiguration | Vorher LB/KB | Nachher LB/KB |
|---|---:|---:|
| Getrennt3/4, ohne Benutzerumfang | 40 / 142 | 40 / 142 |
| Getrennt3/4, −2 Oktaven, MIDI24–67 | **0 / 0** | **40 / 142** |
| Gleicher Basskanal, ohne Benutzerumfang | 0 / 0 | 142 auf gemeinsamem Kanal |
| Gleicher Basskanal, −2 Oktaven, MIDI24–67 | 0 / 0 | 142 auf gemeinsamem Kanal |

60 reale APVTS-Fälle decken zwölf Tonarten und fünf Routing-/Registerkonfigurationen ab. Dazu fünf tatsächliche Profilübergaben Herrmann→Williams→Barry→Neutral→Herrmann mit Stop/Neustart/Seek und aktivem Benutzerumfang. Keine Heap-Allokationen im geprüften Audiopfad, ausgeglichene Notenbilanzen und exakte Live-/SMF-Übereinstimmung für die statischen64-Takt-Fälle.

## Breite normale Produktion: alle neun Rollen

[Maschinenlesbare Ergebnisse](P1_ACTIVITY_RESULTS.json): **259 A/B-Fälle**, jeweils64 oder128Takte. 3×3×3-Feldraster, acht echte Randbereiche, Variety0/.5/1, gepaarte Variationen/Seeds1/0 und9/37, zusätzliche Variante16/Seed13, langsame/schnelle XYZ-Fahrten, Melodie/Dialog einzeln/gemeinsam/aus, manuelle und Follow-Einstellungen, sieben Routing-/Registerkonfigurationen. Zusätzlich54 Rasterfälle und zwei128-Takt-Fahrten im tatsächlichen Anwenderregister. Keine Aufbau-/Fahrt-Szene, kein erzwungener Quellindex. Das Core-Messwerkzeug deaktiviert Parameterträgheit; die ergänzenden echten Prozessortests verwenden die normale Parameterverwaltung.

Aggregierte Note-ons und Anzahl Fälle mit mindestens einem Anschlag:

| Rolle | Note-ons vorher → nachher | Aktive Fälle vorher → nachher | Befund |
|---|---:|---:|---|
| LF | 31516 → 30641 | 251 → 253 | Harmonik, hohe Felder und Bindungen erhalten; Gruppenauswahl reagiert auf wieder spielbaren Bass. |
| KF | 113577 → 112655 | 122 → 116 | Keine globale Sperre; gemeinsame Rhythmusgruppen können ihre Auswahl ändern. |
| LB | 6232 → 8282 | 197 → 243 | Wieder mögliche Registerplatzierung und Geschwisterrouting. |
| KB | 13263 → 17017 | 93 → 125 | Kurze Figuren wieder im Benutzerregister erreichbar. |
| AR | 2710 → 1629 | 69 → 69 | Keine neue AR-Regel; gemeinsame Gruppen dürfen mit wieder geeigneten Basspartnern andere Figuren wählen. |
| TU | 4940 → 4928 | 46 → 46 | Quellen-/Kontextabhängigkeit, kein gemeinsamer technischer Totalausfall. |
| ST | 0 → 8806 | 0 → 179 | Bestehende feste Triggerfunktion aus leerer Reservierung befreit. |
| GS | 2946 → 2724 | 136 → 136 | Mehr Quellen erreichbar; keine Aktivitätsquote. |
| HM | 2345 → 1978 | 136 → 136 | Weiter optional; eigene Motivzustände und Rollenkoordination erhalten. |

Die Aggregate mischen bewusst unterschiedliche Testbedingungen und sind **keine erwartete musikalische Auslastung eines normalen Songs**. Gespielte Dauer, aktive Takte, längste Stille und erste konkrete Noten stehen je Fall/Rolle im JSON. Bei gemeinsamem Kanal wird ein physischer Anschlag nur seinem tatsächlich sendenden Anspruch zugerechnet.

Beispiel `routing-5-roles-3`,128Takte, statisch(.5/.7/.5), Benutzerregister: vorher LB2/KB0, danach LB64/KB34; LB-Gate3.1→87.5%, KB0→1.7%, längste Bassrollenstille LB108→8Takte, KB128→40.2Takte. Im identischen Kontext ohne Umfang sind LB64/KB34 bereits vorher möglich. Das ist eine Fehlerkorrektur der Erreichbarkeit, kein allgemeines Ziel für Bassdichte. H10 bleibt ausdrücklich basslos, H57 bleibt kurzer Eintritt statt Dauerbass.

## Registrierung, Zulassung und wirkliche Quellenverwendung

[CSV mit allen122 eindeutigen integrierten Quellen](P1_ACTIVITY_SOURCE_USE.csv) trennt:

1. Registrierung und validierte Definition (54 Harmoniequellen,36 Rollenfiguren aus28 Rhythmusquellen,18 Bassquellen,22 Motivquellen).
2. Zulassung/Selektion an16-taktigen Diagnoseschnappschüssen.
3. Tatsächliche Note-ons mit Herkunft im normalen Lauf.

Alle54 H-Kontexte erzeugen im Korpus MIDI; nach der Korrektur sind **17/28 R**, **14/18 B** und **13/22 M** an ausgegebenen Quellenereignissen belegt. Vorher waren es insgesamt36 verschiedene R/B-Quellen, nachher31: gültigere gemeinsame Gruppen müssen nicht jede zuvor konkurrierende Quelle häufiger wählen. Es gibt kein Gleichverteilungsziel.

Nicht nachgewiesene R-Quellen: R02/R16/R17/R18/R20/R27/R28/R35/R45/R47/R60. Nicht nachgewiesene B-Quellen: B15/B27/B30/B42. B15/B27/B42 besitzen gleichwohl passende Zulassungsschnappschüsse; Konkurrenz und zyklische Bindung können Auswahl verhindern. Bei R-Gruppen bedeutet `other_rhythm_group` sowohl konkurrierende Auswahl als auch gemeinsame Eignung/noch gebundenen Zyklus; daraus lässt sich keine einzelne musikalische Ablehnungsursache ableiten. Keine Behauptung, diese Quellen seien außerhalb des Korpus unmöglich oder alle isoliert musikalisch abgenommen.

Motivherkunft wird konservativ anhand ausgegebener Tonhöhe/Einsatzzeit im aktiven Original-/Varianten-/Antwortplan gezählt. Reine Speichermetadaten werden separat ausgewiesen und gelten nicht als hörbare Verwendung. Nachgewiesen: M02/M07/M11/M13/M14/M16/M19/M27/M31/M34/M48/M56/M57. Die übrigen neun können an Schnappschüssen passen, werden aber nicht automatisch gegen ein bereits etabliertes Original ausgetauscht. Langfristige Materialrotation wurde nicht implementiert.

Wesentliche verbleibende Gründe: inaktive Rolle/Aktivitätsschwelle; manuelle Zuständigkeit; nicht passender Quellen-X-Bereich; unpassende vollständige Harmonie-/Slash-/Tonabsichts-/Dauer-/Register-/Polyphonieprüfung; andere koordinierte Gruppe; schon etabliertes Motiv. Die Diagnosen sind Momentaufnahmen, keine Aufrufzählung im Audiothread und keine vollständige Zerlegung kombinierter Prüfungen.

Carpenter-TU-Zusatzprüfung: in27 unveränderten128-Takt-Kontexten sind12 mit TU aktiv (je18–24Anschläge). Der bisherige P1-Pfad ist das sparsame JC-M004-Echo im Bereich X.4–1/Y0–.4/Z.1–.6 mit harmonischer Prüfung und16-Takt-Abstand. Das erklärt geringe Präsenz; es ist kein Nachweis eines global kaputten TU-Ausgangs. Carpenter wurde nicht erweitert.

## Rechenzeit und Sicherheit

In `layerFits` werden Routing, Instrumentkatalog und modaler Kontext außerhalb der Notenschleife ermittelt. Kein zusätzlicher Cache, Heap-Speicher oder Datei-/Validierungsaufruf im Audiothread. **32 bytegleiche MIDI-Vergleiche** gegen denselben korrigierten Code ohne diese Schleifenoptimierung sichern die unveränderte Entscheidung.

18 CPU-Messläufe, je20000Blöcke à128Samples/48kHz, bewegtes XYZ, Default-/Anwenderregister, drei Wiederholungen. Auf dem gleichzeitig belasteten Linux-Rechner beträgt der mittlere CPU-Aufwand vorher20.06/19.30µs, korrigiert21.81/23.24µs; gemittelte p99 vorher125.33/111.67µs, korrigiert140.67/141.00µs. Größte einzelne CPU-Zeit vorher4.845/4.749ms, korrigiert5.004/3.863ms. Das Blockbudget beträgt2.667ms. Viele Spitzen liegen beim ersten Aufbau; ein korrigierter Lauf hat seine Spitze erst inBlock6001.

Die reine Schleifenoptimierung zeigt unter dieser Messlast **keinen belastbaren Zeitgewinn** gegenüber dem korrigierten Vergleich ohne Hoisting. Wieder spielbare Figuren und deren vollständige Registerprüfung ändern zudem die Arbeitsmenge. Keine Garantie für128Samples und keine Aussage über die CPU des Anwenders. Für die musikalische Abnahme zunächst512Samples verwenden; die verbleibenden Spitzen ausdrücklich weiter beobachten. Keine vorsorgliche Performance-Architektur eingebaut.

## CC-Ergänzung

[Details und Tests](../../development/MIDI_CC_OUTPUT_RESET.md): tatsächlicher globaler Zustand am bestehenden MIDI/CC-Button orange, in beiden Themes sowie nach Preset-/Projektladung. EIN→AUS sendet einmalig127 für die zuletzt aktiven Dynamik-/Ausdruckszuordnungen (VorgabeCC1/11) an deduplizierte konfigurierte Kanäle, unabhängig von den gespeicherten Bereichen. Kein CC121, keine Bereichsänderung. Stopp funktioniert, solange der Host Audioblöcke verarbeitet. Wieder EIN nimmt die normale Bereichssteuerung auf. Instanzen bleiben unabhängig.

## Reproduktion, Prüfungen und Hörvergleich

- `Tests/LayerTests.cpp`: alle54 H-Kontexte, zwölf Tonarten, Transport/Blockgrößen, Note-off-Bilanz, Shared-Bass-Monophonie, fester ST36, Benutzerregister, H07-Kontur und H57-Manuell; alle22 Motivquellen in ihren harmonischen Voraussetzungen ×zwölf Tonarten ×beide Stimmen.
- `ProcessorHerrmannActivity`:60 reale Prozessor-/Live-/Exportfälle plus Profilübergaben; keine C++-/C-Heap-Allokationen in den bewachten Audioblöcken.
- `ProcessorCcOutput`:24 Profil-/Genre-/Transportkombinationen, wiederholtes EIN/AUS, Presets, Zuordnung, Bereiche, unabhängige Instanzen; echter GUI-Button in beiden Themes.
- 564 bytegleiche Core-Notenrenderings außerhalb Herrmann-SCORE und27 unveränderte Carpenter-TU-Vergleiche. Die ausdrücklich beauftragte CC-Ausschaltfunktion ist davon getrennt.
- Vollständige lokale Core- und Prozessorregression, ASan/UBSan, Linux-VST3; Validierungsdetails und Ergebnisse im zugehörigen [Prüfnachweis](P1_ACTIVITY_VALIDATION.json). Windows-/Paket-/pluginval8-Nachweis gehört zum anschließenden GitHub-Workflow desselben Commits.

[Sieben zusammenhängende MIDI-A/B-Paare](P1_ACTIVITY_AB_MIDI.zip), jeweils128Takte, D/100BPM/4/4/960PPQ: Standardrouting, gemeinsamer Bass, gemeinsame Lang-/Kurz-Ziele, exaktes Anwenderregister, langsame Fahrt und zwei kontrastierende statische Positionen. Ein SMF-Track je physischem MIDI-Kanal; vollständige Notenbilanz bleibt auch bei geteiltem Kanal erhalten. Tatsächliche Engine-Ausgabe, keine nachträgliche Kompositionsbearbeitung oder Filmmusiktranskription.

Messwerkzeug: `tools/williams_probe.cpp`, optionale Offline-Diagnosen; `scripts/audit_herrmann_activity.py <Verzeichnis-mit-before-und-after>` erzeugt259Vergleiche, JSON, Quellen-CSV und MIDI-ZIP. Ausgangsheader `0874b02`, aktueller Headerstand; die vorhandene Test-Friend-Schnittstelle wird ausschließlich in Offline-Testkopien verwendet. Keine dauerhafte alte Engine im Produkt.

## Grenzen und nächster Abnahmeschritt

Die hörbare Herrmann-Schichtgrammatik bleibt wie P1 zunächst4/4; andere Taktarten/manuelle Zuständigkeiten erhalten ihre bisherigen Pfade. Keine Erkennung tatsächlicher externer Patchfähigkeiten, keine automatische Artikulationsumschaltung. Kein pauschaler Bass unter basslosen Klangobjekten, keine zusätzliche Dissonanzfreigabe und kein automatischer Ersatz ungeeigneten Materials.

Materialnutzung bleibt ungleich und manche Quellen sind im breiten Korpus nicht gehört. Die Korrektur beseitigt konkrete Blockaden; sie macht aus der Bibliothek keine Garantie aller musikalischen Möglichkeiten an jedem XYZ-Punkt. Als nächstes ausschließlich erneute Studio-One-Hörabnahme mit den vorhandenen Instrumenten, insbesondere Benutzerregister, basslose Kontraste, Stich und CC-Schaltverhalten. Keine weitere Entwicklung eigenständig anschließen.
