# John Barry – Phase 2: erstes hörbares Profil

Ausgangspunkt: `228425b`, Entwicklungsbranch `develop/composition-core-prototype`. Stand: 25. November 2026. Diese Umsetzung ersetzt die in Phase 1 vorgeschlagene Beschränkung auf zwei Farbakkorde durch alle 46 kanonischen Harmoniestudien. Sie ist ein erster Hörstand, keine abgeschlossene Barry-Grammatik.

## Bedienung und tatsächlich wirksame Unterschiede

Im vorhandenen Menü **KOMPONIST** unter **Score** „John Barry“ auswählen. „Neutral“ bleibt die freie Komposition und der Standard. Menü, Parameter-ID `komponist`, State und Layout bleiben erhalten; die bisher bereits vorhandene Barry-Auswahl aktiviert jetzt zusätzlich das neue Vokabular und die Begleitpolicy. „Bernard Herrmann“ behält seine bisherige Auswahl. Pop/Rock bleibt bei allen drei bestehenden Parameterwerten musikalisch unverändert; dies ist noch kein Pop-Barry-Profil.

Für einen ersten Vergleich: Aufbau AUS, Begleitspielweisen Auto, Arp-Figur und Tempo Auto, Variety 0,5, 4/4, 120 BPM. Neutral und Barry jeweils mindestens 64, besser 128 Takte vergleichen. Dunkel/motorisch: XYZ 0,20 / 0,80 / 0,40. Warm/lyrisch: 0,80 / 0,30 / 0,10. Anschließend langsame XYZ-Fahrt. Die Hauptmelodie bleibt standardmäßig deaktiviert; für den Motivvergleich Melodie aktivieren und beide Motivschalter einschalten. Externe Patches und deren Lautstärken beeinflussen den Höreindruck erheblich.

Hörbar wirksam sind:

- Ein eigener XYZ-ausgewählter Bestand von 46 geschützten Barry-Harmoniestudien: statische Farbfelder, Moll-Major-Färbungen, Sus-/Add-Klänge, Pedale, ruhigere lyrische und stärker bewegte Kontexte.
- Automatisch gehaltene harmonische Felder statt selbsttätiger Stabs/Gates. Die definierten Akkordfarben bleiben geschützt; Umkehrung, Stimmführung und Registerverteilung arbeiten weiter.
- Lange/Pedal- und langsamere Bassfiguren statt der neutralen automatischen Hochintensitäts-Achtelregel. Ein niedriger Bass-Intensitätswert unter 0,30 bevorzugt gehaltenen Bass. Die Benutzereinstellung „Folgt Akkorden“ und die notierten Bassvorgaben behalten ihre vorhandene Bedeutung.
- Kreisende, auf- oder absteigende vorhandene Arp-Figuren, bei vollständig automatischer Auswahl höchstens Achtel. Unter 0,40 Arp-Intensität werden Viertel bevorzugt; Arp-Aktivität beginnt bei 0,30.
- Bei automatischem Szeneneinstieg in dunkleren intensiveren Kontexten ein geeigneter Arp-Einstieg, ansonsten bevorzugt Fläche. Mute/Solo und die tatsächliche Verfügbarkeit gelten weiterhin.
- Etwas spätere Akzente (Aktivität ab 0,45, Unruhe ab 0,65), längere Mindesthaltezeit der Textur (vier Takte). Die melodischen Rollen verwenden dieselbe bestehende Motiv- und Rollenplanung, mit Aktivitätsschwellen von 0,25. Keine neuen Motiv- oder Antwortverfahren.

Manuell gewählte Spielweisen bleiben maßgeblich. Insbesondere wird ein manuell gewähltes Arp-Muster oder Arp-Tempo nicht durch die automatische Barry-Begrenzung verändert. Ein Profilwechsel beendet alte Notengates und verwirft alte Material-/Planreferenzen, damit kein Index aus dem vorherigen Auswahlbestand weiterverwendet wird. Das ist ein bewusster musikalischer Neustart, kein weicher Crossfade.

## Datenpfad und Katalogtreue

Kanonische Quelle ist ausschließlich `shared/Musikalisches_Vokabular_Gesamtfassung_2026-11-24.txt`. Archivfassungen wurden nicht zusätzlich ausgewertet. Die Forschungsoriginale sind unverändert.

`scripts/import_barry_research.py` reproduziert die geprüfte Übernahme. `data/harmony/catalog.json` enthält nun **132** verschiedene harmonische Datensätze: die bisherigen 87 plus **45** neue. **JB-H40** ist harmonisch bereits durch **1003** (Cm über acht Takte) vertreten und erhält keinen zweiten Harmonieeintrag. JB-H33 ist bereits in der Forschung ein Verweis auf JB-H18 und kein 47. Motiv.

Die neuen stabilen IDs sind 30001–30047, ohne 30033 und 30040. Grundtöne, Akkordtypen, explizite Bassvorgaben, ganze Akkorddauern und insgesamt acht Takte werden aus den Einzelvorlagen übernommen. Die in zusammengeführten Vorlagen angegebene Barry-Zeile liefert den Barry-Anker; andernfalls gilt der konkrete XYZ-Wert der Einzelvorlage. Die Anker sind weiterhin vorläufige musikalische Einschätzungen.

Alle konkreten Tonfolgen sind Forschungs-Konstruktionen **[E]**, keine Filmtranskriptionen. Die dokumentierte Verfahren-Evidenz [N]/[I]/[H] bleibt als Herkunftsmetadatum erhalten: sechs Verfahren [N], 19 [I], 21 [H]. Die positiven Startgewichte der neuen Vorlagen betragen 1,8 / 1,3 / 0,75 für diese Evidenzstufen. Dies ist eine zurückhaltende redaktionelle Gewichtung, keine gemessene stilistische Wahrscheinlichkeit. Für den wiederverwendeten alten Eintrag 1003 bleibt das bestehende Barry-Gewicht 1,3 erhalten.

Das Profil besitzt eine statisch erzeugte Auswahlansicht desselben gemeinsamen Katalogs (`HarmonyProfilePools.generated.h`), keine eigene Engine und keinen zweiten harmonischen Quelldatenbestand. Die freie Score-Ansicht bleibt exakt bei ihren 48 bisherigen Einträgen; Pop/Rock bei 39. Barry verwendet seine 46 Studien. Neue Barry-Daten sind damit nicht automatisch zusätzliche Zufallskandidaten der freien Komposition. Spätere gemeinsame Nutzung derselben IDs durch weitere Profile bleibt möglich.

Bei JB-H40 überschreibt ausschließlich die Barry-Ansicht Name, Quellenbezug, Anker (0,15 / 0,85 / 0,25) und Färbungsschutz. Der alte Eintrag 1003 behält für Neutral/Herrmann seinen bisherigen Anker und die flexible Färbung. Seine Harmoniedaten werden nicht dupliziert oder umgeschrieben.

Die Auswahlformel, XYZ-Metrik, Variety und Halteschwellen des Wendungswechsels bleiben unverändert. Profilgewichte wirken erst innerhalb der bisherigen XYZ-Eignung. Es gibt keinen erzwungenen Wechsel zu entfernten Barry-Kandidaten. Dichtestellung, Motivlogik, Scheduler und Swing werden nicht verändert.

## Konkrete ausgewählte Harmonien

Aus dem tatsächlichen Auswahlraster bei Variety 0,5 und Salt 0, transponiert auf C als Projekttonart:

| XYZ | Auswahl | Harmonie | passende Kandidaten |
|---|---|---|---|
| 0,20 / 0,80 / 0,40 | JB-H40 / 1003 | Cm, acht Takte | 2 |
| 0,80 / 0,30 / 0,10 | JB-H04 / 30004 | Cmaj7, acht Takte | 6 |
| 0,15 / 0,20 / 0,80 | JB-H38 / 30038 | CmMaj7 (vier Takte), Cdim (vier Takte), C-Pedal | 2 |
| 0,85 / 0,90 / 0,90 | JB-H46 / 30046 | C–G–D–A–E–B–F#–C#, je ein Takt | 2 |

Diese Beispiele zeigen Stasis, lyrische Farbe, dunkle Farbänderung und bewusst stärkere harmonische Bewegung. Die Auswahl ist nicht auf langsame oder dunkle Bereiche reduziert. Die letzte, hypothetische Randbereichsstudie ist ausdrücklich kein Beleg für einen typischen Barry-Filmausschnitt.

## Architektur und Grenzen der Begleitung

- `CompositionPolicy.h`: kleine `AutoAccompanimentPolicy`, echte Barry-TexturePolicy; `policyForContext()` schaltet sie nur für Score auf.
- `PluginProcessor::currentSettings()`: verbindet den vorhandenen GUI-/State-Parameter mit Auswahlidentität und tatsächlicher Policy. Die Engine erlaubt weiterhin explizite Policy-Injektion in Tests.
- `Generator::pick/candidates/bestWeight`, `HarmonyRuntime.h`: gemeinsame profilabhängige Auswahlansicht. `W()/SW()` und GUI-/Infotexte verwenden dieselbe Ansicht.
- `Generator::rawBassPattern/choosePad/arpeggioPeriod/autoEntry`: wertet die kleine Begleitpolicy aus; keine separaten Barry-Mustererzeuger.
- `generate_harmony_catalog.py`: validiert die profilbezogenen Referenzen, Metadaten und den gemeinsamen Harmoniepfad offline. Nur generierte statische Daten werden im Audio-Thread verwendet.

Die zwei neuen Besetzungsrezepte nutzen ausschließlich vorhandene Figuren: bei konstantem notierten Bass Pedal/Held plus Circle/Up; sonst Held/Half plus Circle/Down; jeweils gehaltene Fläche. Der wiederverwendete Eintrag 1003 behält sein bestehendes Rezept. Dessen automatisches Basspendel verwendet unter der neuen Feldstrategie die kleine Terz statt einer Z-abhängigen Halbtonverengung. Manuelle Basswahl bleibt unverändert.

Das ist keine automatische Instrumentenerkennung: MIDI-Ziele und ihre internen Fähigkeitsannahmen bleiben die vorhandenen. Externe Patch-Fähigkeiten werden nicht als bekannt behauptet. Es gibt keine neuen Keyswitches, Artikulationen oder Instrumentenzuweisungen. Die Rollenauswahl, Notenverwaltung und geprüften Motivrealisierungen bleiben gemeinsame Engine-Funktionen.

## XYZ-Abdeckung

Messung mit dem tatsächlichen Auswahlcode auf 21 × 21 × 21 Positionen einschließlich sämtlicher Flächen, Kanten und Ecken; jeweils Variety 0 / 0,5 / 1. Kein Ersatzalgorithmus.

| Variety | Kandidaten min / Mittel / max | Anteil mit nur einem Kandidaten | verschiedene tatsächlich gezogene IDs im Raster |
|---|---|---|---|
| 0 | 1 / 1.00 / 2 | 99.84 % | 46 |
| 0.5 | 1 / 3.59 / 16 | 8.69 % | 44 |
| 1 | 2 / 10.35 / 27 | 0.00 % | 43 |

Die größte Entfernung zum nächstliegenden Anker beträgt 0,4696 in der bestehenden gewichteten XYZ-Metrik (keine ungewichtete euklidische Messung). Alle 46 Vorlagen werden sowohl an ihrem eigenen Anker tatsächlich ausgewählt als auch insgesamt im Raster erreicht. Bei größerer Variety zieht ein einzelner deterministischer Versuch pro Punkt nicht zwingend jede ID; die vollständige Erreichbarkeit wurde separat geprüft.

Einzelkandidaten bei Variety 0 sind konstruktionsbedingt: Diese Einstellung beschränkt auf die beste XYZ-Passung und ist kein Vielfaltstest. Bei Variety 0,5 bestehen an 8,69 % der Positionen weiterhin Einzelkandidaten; Profile haben somit nicht überall gleich viel Auswahl. Die äußeren stark unruhigen/hellen Kombinationen enthalten auch hypothetische Studien [H]. Ihre Eignung für Barry ist hörend zu prüfen. Die vollständige Abdeckung ist kein Beleg für stilistische Authentizität.

## Reproduzierbare MIDI-Messungen

`scripts/analyze_barry.py --output <Ordner>` kompiliert einen echten Header-Snapshot von 228425b und den aktuellen Produktionscode. **Keine** historischen Fixture-Umschaltungen werden in diesem Vergleich benutzt. Pro Fall 128 Takte, 120 BPM, 48 kHz, beide melodischen Rollen und Motivschalter aktiv; Controller-Fahrten werden unabhängig von der Audio-Blockgröße zeitlich konstant aktualisiert. 32 Fälle × zwei Revisionen = 64 Renderings.

Die 25 Vergleichspaare für Neutral/Herrmann in Score und alle bisherigen Profilparameterwerte in Pop/Rock sind **bytegleich**, einschließlich manueller Begleitung und Positionssprüngen. Barry verändert bewusst sieben Fälle. Die Roh-MIDI-Hashes und Einzelwerte stehen in `PHASE_2_MEASUREMENTS.json`.

| 128 Takte, Auto | Profil | Bass Note-ons gesamt | Arp Note-ons | Melodie Note-ons | Dialog Note-ons | Gate Melodie / Dialog | längste gemeinsame melodische Pause |
|---|---|---|---|---|---|---|---|
| dunkel/intensiv | Neutral | 1104 | 1692 | 58 | 47 | 18.95 / 15.43 % | 20 s |
| dunkel/intensiv | Barry | 310 | 790 | 58 | 64 | 18.95 / 23.24 % | 14 s |
| warm/ruhig | Neutral | 293 | 984 | 29 | 31 | 10.11 / 12.06 % | 14 s |
| warm/ruhig | Barry | 42 | 454 | 30 | 31 | 11.28 / 12.11 % | 20 s |
| XYZ-Fahrt | Neutral | 906 | 1836 | 53 | 41 | 16.60 / 14.60 % | 16 s |
| XYZ-Fahrt | Barry | 259 | 926 | 58 | 34 | 18.16 / 11.72 % | 20 s |

Die geringere Zahl von Anschlägen ist kein Qualitätsziel an sich. Der dunkle Barry-Test behält erkennbare Arp-Motorik, ohne den neutralen hochaktiven Bass zu übernehmen. In einem absichtlich sehr ruhigen Test (0,15 / 0,20 / 0,80) bleiben unterhalb ihrer Schwellen nur Fläche und Bass aktiv: 24 beziehungsweise 52 Note-ons über 128 Takte. Das ist erlaubte Zurückhaltung, kein Planungsfehler. In allen aktuellen Renderings: keine hängenden Noten, keine doppelten Note-ons und null zeitliche Überlagerung von Melodie und Dialog.

### Automatisierte Prüfungen

- `BarryTests`: je 1.104 tatsächliche Acht-Takte-Renderings für Harmoniestimmen und Bass, jeweils alle 46 Studien, zwölf Transpositionen und beide Follow-Zustände. Harmoniestimmen müssen zu den ausdrücklich definierten Pitch-Classes gehören; der separat gerenderte gehaltene Bass muss die notierte Basstonklasse beziehungsweise bei Follow AUS die bisherige Tonika treffen. Dazu Policy-Wirkung, manuelle Overrides, Mute/Solo, unmögliche Register, Motivschalter, Profilwechsel, Notengate-Bilanz, Seek/Loop/Neustart und Blockgrößen 127/512/8192.
- Taktarten 3/4, 6/8, 3/8, 5/8, 7/8; bei der blockübergreifenden Samplequantisierung wird höchstens ein Sample Abweichung zugelassen, Noten und Ereignisreihenfolge müssen gleich bleiben.
- `HarmonicProfileTests`: Auswahlidentität, gültige Referenzen, deterministische tatsächliche Auswahl, alle 46 Anker, unveränderte Pop-Auswahl und der gemeinsame 1003-Alias.
- `HarmonyDataTests`: 46 Originaldatensätze, Bass-/Akkord-/Dauerzuordnung, keine versehentliche Änderung des freien Pools, ungültige Profilreferenzen und Overrides; bestehende Skalierbarkeitsprüfungen bleiben erhalten.
- `ProcessorTests`: vorhandenes Auswahlmenü, State und reale Policy-Zuordnung; vier zusätzliche 64-Takte-Vergleiche von tatsächlicher Plugin-Liveausgabe und MIDI-Export mit allen Kombinationen der beiden Motivschalter.
- Frühere Feature-Vergleiche behalten ausdrücklich ihre historischen Kataloge. Diese eingefrorenen Untersuchungen sind nicht der Nachweis der aktuellen Neutral-Regression; dafür dient der obige unveränderte Produktionsvergleich.

Abschlussprüfung:

- Alle **49 unterschiedlichen Kernprüfungen** erfolgreich. Der vollständige erste Lauf bestand 47/49; zwei alte Testannahmen wurden anschließend korrigiert und gezielt erneut erfolgreich geprüft: `HarmonyImport` erwartete noch insgesamt 87 statt 132 Datensätze; `MusicalExecutionRegression` versuchte neue Barry-IDs gegen einen historischen Katalog zu rendern. Sein ursprünglicher 87er-Korpus bleibt vollständig erhalten. Keine Produktionskorrektur war hierfür nötig.
- Der vollständige wiederholte Scheduler-Vergleich bestätigt 1.217 Vergleiche mit unverändert exakt 98 historischen Zeitkorrekturen und zusätzlich 1.313 Abschlussvergleiche mit 2.177 Blockgrößenvergleichen. Die dort dokumentierten Chase-/Rollenabweichungen stammen aus den früheren, eingefrorenen Entwicklungsständen und sind keine neuen Barry-Abweichungen.
- **3/3 ASan/UBSan-Testgruppen** (`Barry`, `HarmonicProfiles`, `Policy`) bestanden. Die anschließend ergänzten 1.104 separaten Bassrenderings wurden ebenfalls erneut unter ASan/UBSan erfolgreich ausgeführt. LeakSanitizer war in dieser Umgebung deaktiviert; die Allokationswächter der Engine bleiben aktiv.
- Tatsächlicher JUCE-`ProcessorTests`-Lauf erfolgreich, einschließlich 216 bestehender Import-Live-/Exportfälle und vier zusätzlicher 64-Takte-Barry-Fälle. Auswahlmenü, Profilwechsel, State und quadratisches XYZ-Layout bestanden die vorhandenen GUI-Prüfungen.
- **9/9** Datenprüfungen und **7/7** Paketvalidierungsprüfungen erfolgreich; Generator-Driftprüfung und `git diff --check` sauber.
- Linux-VST3 gebaut. Kein Windows-Build, Push, Tag oder Release in diesem Auftrag.

Die gemessenen Produktionsheader stimmen per SHA-256 mit dem abschließenden Quellstand überein. Die wissenschaftlich/musikalische Hörabnahme steht aus.

## Was noch fehlt

Die 25 Rhythmus-, 26 Melodie- sowie P/L/A/F-Studien der Barry-Forschung werden in diesem Schritt nicht als neue Vorlagen importiert. Bereits vorhandene Ostinati und Motive ersetzen keine spezifische Umsetzung aller dort beschriebenen Verfahren. Es gibt noch keine langen komponierten Barry-Melodiebögen, keine komplexe chromatische Stimmführungsgrammatik, kein motivabhängiges Schichtgedächtnis und keine neue Orchestrierungslogik.

The Black Hole beeinflusst die Auswahl der dunklen Stasis-/Pedal-/Ostinato-Facette; A View to a Kill wird über vorhandene rhythmischere, farbige und kontrastierende Studien berücksichtigt. Das sind begründete Annäherungen aus der Forschungsbibliothek, keine Rekonstruktionen der Original-Cues. Insbesondere das konkrete Zorin-Motiv bleibt unbekannt und wurde nicht erfunden. 3/4 wird über die bestehende Host-Taktart unterstützt; das Profil stellt den DAW-Takt nicht selbst um.

Ein sinnvoller nächster Schritt ist die musikalische Hörabnahme dieses Bestands mit protokollierten XYZ-/Variety-/Tempo-Einstellungen. Erst danach eine einzelne klar begrenzte Rhythmus- oder Motivpräferenz aus der kanonischen Forschung ergänzen. Keine solche Folgefunktion wurde vorweggenommen.

## Stabile Zuordnung der 46 Studien

| Forschung | Katalog-ID | Verfahren-Evidenz | XYZ | Name |
|---|---|---|---|---|
| JB-H01 | 30001 | [N] | 0.20 / 0.30 / 0.30 | Ein-Akkord-Ostinato: Moll-Dur7 |
| JB-H02 | 30002 | [N] | 0.25 / 0.30 / 0.25 | Ein-Akkord: Moll mit Sexte |
| JB-H03 | 30003 | [N] | 0.80 / 0.20 / 0.10 | Ein-Akkord: Dur mit None (add9) |
| JB-H04 | 30004 | [I] | 0.75 / 0.15 / 0.05 | Ein-Akkord: Dur-Septime weit |
| JB-H05 | 30005 | [N] | 0.30 / 0.50 / 0.45 | Terzverschiebung mM7 |
| JB-H06 | 30006 | [N] | 0.70 / 0.35 / 0.25 | Dur-Pendel Grund–Quinte |
| JB-H07 | 30007 | [I] | 0.35 / 0.45 / 0.30 | Moll mit tiefer Terzfarbe |
| JB-H08 | 30008 | [I] | 0.45 / 0.40 / 0.30 | Pedal c mit bVII |
| JB-H09 | 30009 | [I] | 0.35 / 0.50 / 0.35 | Absteigende Moll-Kadenz Cm–Ab–Bb |
| JB-H10 | 30010 | [I] | 0.30 / 0.35 / 0.25 | Moll-Plagal Cm–Fm–Cm |
| JB-H11 | 30011 | [I] | 0.80 / 0.30 / 0.10 | Dur-Ostinato mit Pedal c |
| JB-H12 | 30012 | [H] | 0.60 / 0.25 / 0.25 | Schwebende Sus-Folge |
| JB-H13 | 30013 | [H] | 0.30 / 0.60 / 0.70 | Halbton-Pendel mM7 |
| JB-H14 | 30014 | [H] | 0.20 / 0.65 / 0.65 | Tritonus-Pendel Moll |
| JB-H15 | 30015 | [I] | 0.65 / 0.35 / 0.20 | Mediantenpaar hell |
| JB-H16 | 30016 | [H] | 0.85 / 0.30 / 0.20 | Lydische Färbung über Pedal |
| JB-H17 | 30017 | [I] | 0.65 / 0.50 / 0.30 | Bright Pedal mit bVII–IV |
| JB-H18 | 30018 | [N] | 0.25 / 0.55 / 0.60 | Quint-Pedal c–g (mit Linie oder als leerer Klang) |
| JB-H19 | 30019 | [I] | 0.15 / 0.55 / 0.55 | Phrygisches Pendel |
| JB-H20 | 30020 | [I] | 0.15 / 0.75 / 0.70 | Schnelles Phrygisch-Pendel |
| JB-H21 | 30021 | [I] | 0.50 / 0.30 / 0.30 | Bittersüßes Dur-Moll-Pendel |
| JB-H22 | 30022 | [I] | 0.45 / 0.30 / 0.25 | Mollsubdominante hell |
| JB-H23 | 30023 | [H] | 0.15 / 0.80 / 0.85 | Moll-Diminished-Wechsel |
| JB-H24 | 30024 | [H] | 0.20 / 0.90 / 0.90 | Chromatische Mollreihe aufwärts |
| JB-H25 | 30025 | [I] | 0.30 / 0.35 / 0.35 | Ein-Akkord: Moll-None |
| JB-H26 | 30026 | [H] | 0.45 / 0.25 / 0.20 | Moll-Septakkord-Kette |
| JB-H27 | 30027 | [H] | 0.90 / 0.65 / 0.40 | Quintaufstieg hell |
| JB-H28 | 30028 | [H] | 0.75 / 0.40 / 0.15 | Hymnisches Plagal |
| JB-H29 | 30029 | [I] | 0.25 / 0.50 / 0.40 | Absteigende Moll-Kadenz i–♭VII–♭VI–V (Zentrum c oder a) |
| JB-H30 | 30030 | [I] | 0.25 / 0.40 / 0.35 | Lamento-Kadenz |
| JB-H31 | 30031 | [H] | 0.30 / 0.70 / 0.65 | Dominantpedal |
| JB-H32 | 30032 | [I] | 0.50 / 0.40 / 0.40 | Moll-Dur-Wechsel mit Septime |
| JB-H34 | 30034 | [I] | 0.30 / 0.50 / 0.40 | Terzkette abwärts |
| JB-H35 | 30035 | [H] | 0.60 / 0.70 / 0.80 | Tritonus-Dur |
| JB-H36 | 30036 | [I] | 0.40 / 0.30 / 0.20 | Moll-Schluss mit Aufhellung |
| JB-H37 | 30037 | [I] | 0.50 / 0.60 / 0.50 | Pedal c mit absteigenden Dreiklängen |
| JB-H38 | 30038 | [H] | 0.15 / 0.30 / 0.65 | Leises Flirren (Moll-Verminderung) |
| JB-H39 | 30039 | [H] | 0.20 / 0.25 / 0.60 | Wackelnder Bass unter Moll |
| JB-H40 | 1003 | [H] | 0.15 / 0.85 / 0.25 | Wuchtiges Moll-Pedal |
| JB-H41 | 30041 | [H] | 0.20 / 0.80 / 0.30 | Schwerer Plagalschritt |
| JB-H42 | 30042 | [H] | 0.85 / 0.20 / 0.65 | Heller Schimmer |
| JB-H43 | 30043 | [H] | 0.85 / 0.25 / 0.65 | Helles Flirren-Pendel |
| JB-H44 | 30044 | [H] | 0.90 / 0.85 / 0.20 | Fanfare statisch |
| JB-H45 | 30045 | [H] | 0.90 / 0.80 / 0.25 | Triumph über Pedal |
| JB-H46 | 30046 | [H] | 0.90 / 0.90 / 0.80 | Heller Quintaufstieg beschleunigt |
| JB-H47 | 30047 | [H] | 0.80 / 0.85 / 0.85 | Heller Tritonus-Wechsel |
