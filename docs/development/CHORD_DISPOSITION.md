# Sparsame und offene Akkordlagen

Ausgangspunkt: `2a7e55d`, Branch `develop/composition-core-prototype`.

## Tatsächlicher Ausgangsstand

- Die 18 `kShapes` in `Source/ScoreEngine.h` beschreiben Dreiklänge, Sept-/erweiterte Akkorde, Sus/Add, Quartschichtung und ausdrücklich terzoffene Quintakkorde. `padType()` kann bei hoher Unruhe vorhandene Akkordfarben verändern; dieser Mechanismus wurde nicht geändert.
- `composition::buildAnchor()` (`Source/CompositionCore.h`) verteilt Grundton/Quinte und Farbtöne bereits auf unterschiedliche Oktaven. Eigene Folgen wählen über `ChordIntent::voicing` eine von drei Ankeranordnungen. Oberhalb Intensität 0,6 kommt normalerweise eine zusätzliche Grundtonoktave hinzu. Die vorhandene Stimmenzahl ist also bereits intensitätsabhängig, ohne dass Akkordfarbe und Besetzung explizit getrennt wären.
- `Generator::prepareVoicingPlan()` baut einen zyklischen harmonischen Plan. `planHarmony()` nutzt `voiceleading::lead()` für gemeinsame Töne, Inversionen, Register und Auflösungen. Basslagen werden getrennt mit unveränderlicher Basstonklasse geplant; explizite Slash-Bässe bleiben erhalten.
- `padChord()` realisiert die Anker als lange oder kurze Akkorde. Zusätzliche Grundtonverdopplungen werden schon bisher etwas leiser gespielt; bei gehaltenen Akkorden werden übrig gebliebene alte Farbtöne entfernt. Die tatsächlich gehörte Score-Stimmführung zwischen Wendungen bleibt ein eigener, unveränderter Mechanismus.

## Gemeinsame Strategie

`Source/ChordDisposition.h` ergänzt eine gemeinsame, MIDI- und genreunabhängige Realisierung hinter dem bestehenden harmonischen Plan. Keine zweite Harmonie- oder Pop/Rock-Engine. `ChordDispositionRequest` enthält Originalbesetzung, vorherige Lage, Akkord-/Pflichttonmaske, gegebenenfalls stabile Bassstütze, Tonumfang, Polyphonie und Auflösungsabsicht. `ChordDispositionResult` dokumentiert tatsächliche Lage, ausgelassene Tonklassen und Annahme/Fallback.

Drei getrennte Begriffe:

1. **Harmonische Farbe:** Pflichttonklassen aus dem effektiven vorhandenen Akkord; werden nicht neu gewählt oder ersetzt.
2. **Stimmenzahl/Besetzung:** vollständig oder reduziert.
3. **Weite/Register:** natürliche Ausgangslage oder offene Anordnung.

`FreeCompositionPolicy::chords` enthält `enabled`, vier typisierte Kombinationen und die Grenzen für offene Lagen. Neutraler Zyklus über bestehende achtaktige Phrasen: vollständig/natürlich, vollständig/offen, reduziert/natürlich, reduziert/offen. Startphase folgt dem vorhandenen Variation-Parameter. Diese Entscheidung verwendet keine Intensitätsschwelle. Vollständige Besetzungen bleiben die Hälfte der Phasen; die bisherige Intensitätswirkung auf Anker und Ausdruck bleibt bestehen.

### Auswahl der Töne

- Vollständig/natürlich liefert exakt den bisherigen harmonischen Plan einschließlich seiner vorgesehenen Verdopplungen.
- Vollständig/offen behält Stimmenzahl und vollständigen Tonklassenbestand.
- Reduziert entfernt innerhalb der Fläche zunächst Tonklassenverdopplungen. Bei mindestens vier verschiedenen Akkordtönen darf die reine Quinte entfallen. Bei Dreiklängen bleibt sie erhalten, sofern keine passende Bassstütze eine Grundtonauslassung ermöglicht.
- Ein Grundton darf nur entfallen, wenn eine aktive, unveränderte gehaltene Bass-/Pedalfunktion dieselbe Grundtonklasse tatsächlich planmäßig vertritt und sie innerhalb der Bassgrenzen darstellbar ist. Kurze Funk-/Tanz-/Achtelfiguren reichen dafür ausdrücklich nicht. Bei Bass AUS oder abweichendem Follow-/Slash-Basston bleibt der Flächengrundton erhalten.
- Terzen, Septimen, Sexte, Add-/Nonentöne, Sus-Töne, verminderte und übermäßige Quinten bleiben Pflichtfarben. Quartschichtungen und Quintakkorde behalten ihren kompletten Tonklassenbestand. Quintakkorde erhalten niemals eine Terz.
- Mindestens zwei Flächentöne. Reicht das Material nicht für eine sinnvolle Reduktion, bleibt die volle Tonklassenauswahl.

### Lage und Stimmführung

Offene Lagen verwenden in dieser ersten Strategie 19–30 Halbtöne Gesamtweite. Das ist eine technische Zielspanne, keine allgemeingültige Definition musikalischer Offenheit. Ein Ton kann um eine Oktave abgesenkt/angehoben werden; neue Tonklassen werden nicht erfunden. Eine Lage kann bereits ausreichend offen sein und unverändert bleiben.

Die Kandidaten nutzen vorhandene `voiceleading::lead()`, `distance()` und `shapeCost()` einschließlich der bestehenden Auflösungsabsichten. Zwei begrenzte zyklische Durchläufe verbinden die realisierten Lagen mehrerer Akkorde. Es gibt keine gespeicherte Aufführungshistorie oder neue Stimmenidentitätsverwaltung. Ein enger Farbtongrund kann trotz offener Gesamtweite erhalten bleiben; Offenheit bedeutet nicht zwingend gleiche Abstände zwischen allen Tönen.

## Schmale Integration

`Generator::padVoicing()` ergänzt die Realisierung nach `prepareVoicingPlan()`. Der kanonische `harmonicPlan` wird nicht verändert: Bass, Motive, Arpeggios und andere Stimmen verwenden weiterhin dieselben Daten. Ein begrenzter Cache enthält maximal acht Besetzungen. Cachefaktoren umfassen Ausgangsplan, Population/Weite, Policy-Grenzen, Polyphonie und zulässige Bassstütze. Reset/Seek invalidieren den Cache; identische Einstellungen rekonstruieren dieselben Lagen.

Zunächst nur Pop/Rock und **automatische Fläche**. Lange und kurze Ausgänge verwenden die vorhandenen Spielweisen und Dauern. Manuelle Flächenmuster, geteilte beteiligte MIDI-Kanäle, Aufbau, endliche Szenen/Ende, Einstiegsoverride, Wachstum/Peak, Stillstand, Zwischendominanten und die geschützte Drahtseil-Linie bleiben beim bisherigen Verhalten. Score einschließlich Neutral, Barry und Herrmann unverändert. Keine GUI, neuen Akkordtypen oder Instrumentierungsvorgaben.

Der gemeinsame Ausgangskatalog liefert Tonumfang und Polyphonie. Die Fähigkeiten externer Patches sind dadurch weiterhin nicht bekannt. Fehlende Farben im ursprünglichen, stark eingeengten Register werden nicht mit anderen Tonklassen „repariert“: der neue Schritt fällt zurück. Die neue Strategie reagiert an den bestehenden Flächenanschlägen; sie plant keine zukünftige Hostautomation voraus und führt keine zusätzlichen Zwischenanschläge ein.

## Reproduzierbare MIDI-Prüfung

```sh
cmake -S . -B ../stromscore-core-build -DENGINE_ONLY=ON
cmake --build ../stromscore-core-build
ctest --test-dir ../stromscore-core-build --output-on-failure
python3 scripts/compare_chord_disposition.py \
  --probe ../stromscore-core-build/ChordDispositionProbe --output ../chord-disposition
```

81 Szenarien, jeweils 128 Takte bei 90/120/173 BPM, mit/ohne Swing: alle 36 Pop/Rock-Wendungen, alle 18 Akkordtypen in eigenen Folgen mit Dauern 2/1/3/2, Follow AN/AUS, Bass AUS, Slash-Bässe, fehlende Bassregister, manuelle Muster, schmale Register, Szenen, vollständige/reduzierte/offene Kombinationen und drei Score-Profile. Referenz ist der tatsächlich kompilierte Stand `2a7e55d`.

243 A/B-Fälle, 486 Blockvergleiche (127/8192 gegen 512 Samples), 81 bytegleiche Wiederholungen bei 120 BPM und 72 zusätzliche Adapterfälle in allen zwölf Tonarten. Letztere vergleichen ebenfalls Bass und andere Ausgänge mit dem alten Generator. Gleichzeitige Note-offs verschiedener Ausgänge können durch die veränderte aktive Flächennotenliste anders sortiert werden; deren Noten/Zeitpunkte bleiben exakt gleich. Bassereignisse werden zusätzlich in ihrer Reihenfolge strikt verglichen, andere Anschläge und Ausdrucksdaten ebenfalls. Ausschalten der neuen Policy und vollständig/natürlich müssen vollständig bytegleich sein.

Der Vergleich prüft die erforderlichen Farbtöne an tatsächlich gespielten MIDI-Zuständen, nicht nur an Planobjekten. Die JSON-Auswertung enthält zeitgewichtete Polyphonie-/Weitenverteilungen einschließlich Pausen, Tonklassenverdopplungen, nächste Tonabstände an Besetzungswechseln und konkrete Vorher-/Nachherlagen. Der Nächste-Ton-Abstand ist eine Diagnose, keine eindeutige Rekonstruktion individueller Stimmen. Bei identisch belegten MIDI-Kanälen dient die Kontrolle ausschließlich der unveränderten Ausgabe; eine akustische Trennung gemeinsamer Notenansprüche wird dadurch nicht behauptet.

Historische Probes mit `BASS_REGRESSION_CONTROL` schalten auch `policy.chords` aus; `RhythmProbe` isoliert ebenfalls seine bisherige Rhythmusfunktion. Die neue Vergleichssuite prüft die tatsächliche neue Standardbelegung separat gegen `2a7e55d`. Keine parallele Produktionsimplementierung.

## Vorläufige musikalische Einordnung und Grenzen

Die Tonauswahl ist konservativ und erlaubt Transparenz, ohne automatisch weniger Töne bei niedriger Intensität zu verlangen. Eine vollständige Akkordlage kann klanglich geeigneter sein als eine reduzierte. Offene Lagen können mehr Registerbewegung benötigen; die neue Strategie optimiert nicht alle Bewegungsmaße gleichzeitig. Insbesondere Slash-Folgen und Besetzungswechsel verdienen einen Hörtest. Es gibt keine allgemeine Instrumenten-/Orchestrierungs-, Jazz-Shell- oder Satzgrammatik, keine Echtzeiterkennung von Patches und keine voll ausgearbeitete profilabhängige Formplanung. Unspielbare Kandidaten bleiben beim bisherigen Verfahren.

Die musikalische Bewertung bleibt bis zum Hörtest vorläufig.

## Messwerte bei 120 BPM, jeweils 128 Takte

| Fall | Mittlere klingende Stimmenzahl vor/nach | Mittlere Akkordweite vor/nach | Maximale Stimmenzahl vor/nach |
|---|---:|---:|---:|
| 2025-auto | 5.50 / 4.50 | 28.50 / 25.62 | 6 / 6 |
| 2029-auto | 3.75 / 3.38 | 20.25 / 20.62 | 4 / 4 |
| 2030-auto | 4.50 / 3.84 | 20.75 / 20.17 | 5 / 5 |
| 2035-auto | 3.25 / 3.12 | 17.25 / 18.00 | 4 / 4 |
| full-natural | 3.25 / 3.25 | 17.25 / 17.25 | 4 / 4 |
| full-open | 3.25 / 3.25 | 17.25 / 20.25 | 4 / 4 |
| lean-natural | 3.25 / 3.00 | 17.25 / 14.25 | 4 / 3 |
| lean-open | 3.25 / 3.00 | 17.25 / 20.25 | 4 / 3 |
| stable-root | 4.00 / 2.25 | 14.44 / 9.05 | 5 / 3 |
| stable-bass-follow-off | 4.00 / 2.75 | 14.44 / 10.86 | 5 / 4 |
| slash-bass | 4.50 / 3.00 | 20.75 / 14.50 | 5 / 4 |
| unavailable-bass-root | 4.00 / 3.25 | 14.44 / 12.66 | 5 / 4 |
| high | 4.00 / 3.50 | 25.00 / 21.56 | 4 / 4 |
| low | 3.00 / 3.00 | 16.00 / 18.12 | 3 / 3 |

Die Werte umfassen die tatsächlich klingenden Flächenausgänge. Klangpausen sind in der JSON-Verteilung separat erfasst und im Mittel der klingenden Stimmen nicht als Nullstimmen eingerechnet. Die Zahlen sind keine Qualitätsrangfolge. Beispielsweise bleibt die Stimmenzahl bei vollständig/offen gleich, während die Weite zunimmt; bei reduziert/natürlich sinken Stimmenzahl und Weite. Reduziert/offen kann trotz weniger Stimmen eine größere Weite behalten.

Zusätzliche Grundtonverdopplungen: bei 2025 sinkt ihr zeitgewichtetes Mittel von 1,0 auf 0,5; der ursprüngliche volle Klang bleibt in den vollständigen Phasen erhalten.

Der Nächste-Ton-Abstand wächst im Slash-Kontrollfall von 1,32 auf 3,54 Halbtöne. Das ist ein messbarer Preis der veränderten Besetzung/Registerverteilung, kein Nachweis besserer Stimmführung. Gemeinsame Töne und bestehende Auflösungsabsichten werden weiterhin berücksichtigt; ein Hörtest muss diese Wechsel bewerten.

## Konkrete MIDI-Lagen

Ticks sind Sechzehntel ab Szenenbeginn. Notenzahlen sind eindeutige MIDI-Nummern; nicht alle Beispiele gehören zu derselben Phrase oder Policy-Kombination.

| Fall | Tick | Vorher | Nachher | Bedeutung |
|---|---:|---|---|---|
| custom-0 | 130 | 64, 67, 72 | 52, 67, 72 | C-Dur: nur Registerverteilung |
| custom-2 | 258 | 67, 71, 72, 76 | 71, 72, 76 | Cmaj7: reine Quinte entfällt |
| custom-6 | 258 | 60, 67, 74, 75, 83 | 62, 72, 75, 83 | Cm(maj9): Nonenton und große Septime bleiben |
| custom-9 | 130 | 65, 67, 72 | 53, 67, 72 | Csus4: Sus-Ton bleibt, keine Terz |
| custom-11 | 258 | 64, 67, 72, 86 | 64, 72, 86 | Cadd9: Add-Ton bleibt |
| custom-17 | 258 | 60, 67, 72 | 67, 72 | C5: Oktavverdopplung entfällt, keine Terz |
| stable-root | 2 | 55, 64, 71, 72 | 64, 71 | Cmaj7 mit gehaltenem C-Bass |
| slash-bass | 32 | 55, 60, 69, 71, 76 | 55, 60, 69, 71 | Am9/G: A bleibt, G ist kein Ersatzgrundton |

Der vollständige Vergleich und die zeitgewichteten Register-/Stimmenverteilungen stehen in `CHORD_DISPOSITION_COMPARISON.json`.

## Hörvergleich

Die Ausgabe enthält 81 Vorher-/Nachher-MIDI-Paare mit je 128 Takten bei 120 BPM (4:16 Minuten). Für beide Dateien dieselben Patches und Kanalzuordnungen verwenden. Standard: Fläche lang Kanal 1, Fläche kurz Kanal 2, Bass lang/kurz Kanal 3/4, Arpeggio Kanal 5. Es gibt keine Program-Changes oder vorgegebene Klangbibliothek.

Empfohlene Paare: `custom-0`, `custom-2`, `custom-6`, `custom-9`, `custom-11`, `custom-17`, `full-open`, `lean-natural`, `lean-open`, `stable-root`, `slash-bass`. `full-natural`, die manuellen Fälle und `score-*` dienen als unveränderte Kontrollen. Die erzwungenen Kombinationen sind ausschließlich Test-Policy-Daten, keine neuen GUI-Schalter.

Für einen Plugin-Test: Pop/Rock, Fläche Auto, Aufbau AUS, keine endliche Szene/Zwischendominanten, getrennte MIDI-Kanäle. Beispielsweise XYZ (0,52 / 0,38 / 0,12) für Gegenlicht/2029 oder (0,88 / 0,48 / 0,03) für Sonntagmorgen/2035, Variety 0. Mindestens 32 Takte für den vierphasigen Besetzungszyklus, für den Vergleich 128 Takte. Bass und Follow-Einstellungen jeweils separat vergleichen; einfache Bassmuster bleiben unverändert.

## Tests und Abschluss

- Alle 27 CTest-Prüfungen erfolgreich: 26 im Gesamtlauf; die zunächst abweichende DensityComparison anschließend nach Angleichung ihres separat kompilierten Kontrollgenerators bestanden. Nur die Kontrollkonfiguration wurde korrigiert, keine Produktionsentscheidung geändert.
- 243 vollständige A/B-Renderings gegen `2a7e55d`, 486 Blockvergleiche und 81 bytegleiche Wiederholungen bestanden.
- 72 zusätzliche Adapterfälle über zwölf Tonarten mit unverändertem Bass/anderen Stimmen und Farberhalt bestanden. Der Kern prüft alle 18 Akkordtypen in zwölf Transpositionen bei zwei Intensitäten und vier Kombinationen.
- Die Kernprüfung umfasst unveränderliche Eingaben, Pflichtfarben, Quintakkorde ohne Terz, Register, unspielbare Kandidaten, allokationsfreien Audiopfad, warmen/kalten Seek, Loop und Reset/Neustart.
- ASan/UBSan-Prüfung des neuen Kerns und der Generatoranbindung bestanden.
- Vollständiger JUCE-ProcessorTests-Lauf einschließlich echter Plugin-Live-/Exportgleichheit und nachgewiesener E/H-Besetzung über C-Bass im Export bestanden. Die vorhandene Plugin-Exportoberfläche bleibt auf 64 Takte begrenzt.
- 7/7 vorhandene Release-Gate-Fixtures bestanden; kein Release erzeugt.

JUCE meldet in dieser Umgebung Fontconfig-Cachewarnungen; die Tests enden erfolgreich. Bestehende Compilerwarnungen bleiben bestehen. Kein Windows-Host-/Patch-Hörtest durchgeführt. Kein Push und kein Release.
