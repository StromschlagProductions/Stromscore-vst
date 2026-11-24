# Rhythmische Verzahnung von Bass und Bewegung

Basis `b0170ee`, Branch `develop/composition-core-prototype`.

## Bestandsaufnahme

`Generator::rawBassPattern()` wählt vorhandene Bassmuster abhängig von Wendung, Variation und Ebenenintensität. Gehaltene, halbe, Viertel-, Achtel-, Sechzehntel-, Funk-, Pedal-, Pendel-, Tanz- und weitere Figuren besitzen eigene Regeln. Funk verwendet bereits `composition::funkBassAttack()`. Hohe Intensität kann weiterhin einfache Achtel oder einen durchgehenden Sechzehntelmotor ergeben.

`chooseArp()` wählt eine der zwei Wendungsfiguren; `TexturePolicy` bestimmt das automatische Anschlagraster. Bisher entstehen Bass und Arpeggio überwiegend unabhängig. Beide verwenden metrische Gruppenakzente. `EventDensity` lässt optionale Ereignisse gruppenweise entfallen, verändert jedoch keine Figur gezielt relativ zu einer anderen Stimme.

`motifWindow()` reserviert spielbare melodische Figuren für automatische Arpeggios. `dialogueArp()` behandelt den bisherigen Score-Dialog. Pop/Rock-Hooks nutzen gemeinsamen Motivkatalog, Wiederkehr und Varianten; kontinuierliche und phrasierte Hooks sind getrennt. `prepareBassPhrase()` plant geeignete automatische Funkbasslinien über zwei Akkordregionen und hält deren Spielweise stabil. Diese Verfahren bleiben erhalten.

## Kleinster gemeinsamer Plan

`Source/RhythmPlan.h` enthält einen MIDI- und genreunabhängigen, allokationsfreien `planRhythmicInterlock()`. Eingaben sind das rhythmische Referenzraster, das vorhandene Bewegungsraster, der absolute Takt und zulässige Notendauern. `RhythmPlan` enthält Referenz, Original- und Zielraster sowie für jeden Einsatz seine ursprüngliche Position, neue Position und Dauer.

Erste Strategie:

- Achtelraster als Träger, Viertelpositionen 0/4/8/12 bleiben unverändert.
- Schwache Achtel 2/6/10/14 werden um eine Sechzehntel nach hinten gelegt, sofern dort kein Bassanschlag vorgesehen ist.
- Die Entscheidung gilt auch dann, wenn die ursprüngliche Achtelposition keinen Bassanschlag hatte: Es entsteht eine bewusst synkopierte Figur, kein bloßes Entfernen gleichzeitiger Ereignisse.
- Kein Anschlag entfällt und keiner kommt hinzu. Ein verschobener Ton kann verkürzt werden, damit nächste Note und Taktgrenze frei bleiben. Es entstehen kurze Artikulationspausen, keine Überlappungen.
- Standardmäßig wird jeder zweite geeignete Takt koordiniert; dazwischen bleibt die ursprüngliche parallele Rhythmik. Diese zweitäktige Pulsorganisation läuft über Akkordgrenzen weiter, statt an jedem Akkord neu anzufangen.

`FreeCompositionPolicy::rhythm` enthält `enabled` und das validierte `everyBars` (1–8). Alle Profile verwenden dieselbe neutrale Strategie. Es gibt keine neue Profilidentität, GUI oder Instrumentierungsvorgabe.

## Anbindung und Schutz

`Generator::movementRhythm()` übersetzt vorhandene automatische Bassfiguren in die Referenz und prüft die Eignung. `funkBassAttack()` wird wiederverwendet; bei einer melodisch geplanten Funklinie bleiben die identischen Funk-Einsätze die Referenz. `playArpeggio()` verwendet den Plan tatsächlich: Tonfolge und Velocity-Zufallsanteil beziehen sich weiterhin auf die Originalposition; Swing und Ausgabezeit beziehen sich auf die neue Position. Der Basspfad wird nicht verändert.

Zunächst geeignet sind automatische Auf-/Ab-/Kreis-/Kaskadenfiguren mit automatischem Achteltempo und automatischem Achtel-, Funk- oder Hi-NRG-Bass im 4/4-Takt. Ein Hi-NRG-Sechzehntelmotor hat keinen freien Zwischenraum und fällt zurück. Pedal, andere Bassostinati und markante Arp-Riffs/Cells/SID-Figuren bleiben unverändert. Beide Follow-Schalter sind unabhängig möglich; sie behalten ihre bisherige harmonische Funktion.

Manuelle Bassfigur, Arpfigur oder Arprate, stumme/ausgeschlossene Referenzstimme, geteilte beteiligte MIDI-Kanäle, Aufbau, endliche Szenen, Endanforderung, Bass-Einstiegsoverride, Basspause, Ausdünnung, Stillstand und Zwischendominanten führen zum bisherigen Verhalten. Bei aktiver Hauptmelodie oder aktiven phrasierten Hooks bleibt der gesamte Kontext unverändert. Damit haben vorhandene Motivreservierungen und Varianten Vorrang, ohne ihre Fenster oder ihr Material neu zu planen. Kontinuierliche Hooks bleiben unverändert und können neben einer geeigneten Begleitkoordination laufen.

Die Funktion prüft die zulässigen Arp-Notendauern aus dem gemeinsamen Ausgangskatalog. Sie beansprucht keine Kenntnis tatsächlich extern geladener Patches. Eine bereits angenommene melodische Bassphrase wird weder gekürzt noch verschoben noch neu berechnet. Score einschließlich Neutral, Barry und Herrmann nutzt unverändert den bisherigen Pfad.

## Reproduktion

```sh
cmake -S . -B ../stromscore-core-build -DENGINE_ONLY=ON
cmake --build ../stromscore-core-build
ctest --test-dir ../stromscore-core-build --output-on-failure
python3 scripts/compare_rhythm.py --probe ../stromscore-core-build/RhythmProbe \
  --output ../rhythmic-interlock
```

Der Referenzgenerator wird aus den echten Headern von `b0170ee` kompiliert. Der Vergleich enthält alle 36 Pop/Rock-Wendungen sowie Follow-, manuelle, dichte, ruhige, statische, Hook-, Szenen-, Kanal-, Mute/Solo- und Score-Kontrollen. Jeder Fall dauert 128 Takte bei 90, 120 und 173 BPM, mit beziehungsweise ohne Swing. 127/8192-Sample-Blöcke werden gegen 512 verglichen. Geprüft werden zusätzlich tatsächliche Bassreferenz, unveränderte andere Ausgänge, Tonreihenfolge/Velocity/Anschlagszahl des Arpeggios, konkrete Verschiebung, metrische Anker und vollständige MIDI-Notenverwaltung.

Die bekannten Rundungsunterschiede verschiedener Blockgrößen dürfen höchstens ein Sample betragen; musikalische Einsätze und Ereignisdaten müssen identisch sein. Derselbe Vergleich misst diese Abweichung auch im alten Generator. Wiederholtes Rendering mit gleicher Blockgröße muss bytegleich sein.

`Tests/RhythmPlanTests.cpp` prüft Planregeln, Instrumentendauern, geeignete/ungeeignete Raster, allokationsfreien Audiopfad, warmen und kalten Seek, Swing vor einem verzögerten Einsatz, Loop und Reset/Neustart. `Tests/ProcessorTests.cpp` prüft die tatsächliche Plugin-Live-/Exportstrecke über 64 Takte und einen nachweislich verschobenen Einsatz; die bisherige Exportoberfläche bleibt auf 64 Takte begrenzt.

## Grenzen

Ein fester, überschaubarer zweitäktiger Rhythmuskontrast, keine allgemeine Groove-, Rollen- oder Orchestrierungsplanung. Voll besetzte Sechzehntelraster werden bewusst nicht verändert. Noch keine Koordination innerhalb phrasierter Motivfenster, kein freies Verschieben über Akkordgrenzen, keine Kenntnis zukünftiger Hostautomation. Live-Änderungen können die Eignung ändern und zum ursprünglichen Raster zurückführen. Die musikalische Qualität und das Zusammenspiel externer Patches müssen gehört werden; die Tests belegen technische Eigenschaften, keine abschließende ästhetische Bewertung.

### Konkrete Einsatzraster

Eine Spalte entspricht einer Sechzehntel; `x` ist ein Anschlag. Gruppen: vier Viertel im 4/4-Takt. Die Folge der Arp-Töne bleibt dieselbe.

```text
Position       0123 4567 89ab cdef
Achtelbass     x.x. x.x. x.x. x.x.
Arp vorher     x.x. x.x. x.x. x.x.
Arp koordiniert x..x x..x x..x x..x
```

Achtelreferenz: 8 → 8 Arpanschläge, 8 → 4 gemeinsame und 0 → 4 komplementäre Arpanschläge; alle vier gemeinsamen Viertel bleiben. Vier Sechzehntel Artikulationspause pro koordiniertem Takt statt durchgehend gehaltenen Achteln.

```text
Funkbass       x..x .x.. x..x .xx.
Arp vorher     x.x. x.x. x.x. x.x.
Arp koordiniert x.x. x..x x.x. x..x
```

Funkreferenz: 8 → 8 Arpanschläge, 3 → 2 gemeinsame und 5 → 6 komplementäre Arpanschläge; gemeinsame Viertel 0 und 8 bleiben. Zwei Sechzehntel Artikulationspause. Auch Position 6 wandert nach 7, obwohl bei 6 kein Bassanschlag entfernt werden müsste. Das folgende unveränderte Parallelraster bleibt Teil derselben zweitäktigen Struktur.

Die interne aktive Notenliste kann gleichzeitige Note-offs anderer Ausgänge in anderer Reihenfolge ausgeben. Im A/B-Vergleich bleiben deren Noten und Zeitpunkte exakt gleich; andere Anschläge und Ausdrucksdaten werden zusätzlich in ihrer Reihenfolge geprüft. Der Bassstrom bleibt auch in seiner Ereignisreihenfolge exakt unverändert. Ohne aktivierten Koordinationsplan muss der gesamte MIDI-Strom bytegleich sein.

Historische Probes mit `BASS_REGRESSION_CONTROL` schalten zusätzlich `policy.rhythm.enabled=false`, um ihre früheren musikalischen Funktionen isoliert zu prüfen. Der neue Standard wird in `RhythmComparison` separat gegen `b0170ee` geprüft, nicht von dieser Kontrolle ausgenommen.

## Hörvergleich

Die generierten Dateien `*-before.mid` / `*-after.mid` enthalten jeweils 128 Takte mit identischen Instrumentierungsvorgaben. Beide Dateien mit denselben Patches und derselben Kanalzuordnung vergleichen; Standard: Bass kurz MIDI-Kanal 4, Arpeggio MIDI-Kanal 5. Tempoangabe der MIDI-Dateien: 120 BPM. Die Dauer beträgt 4:16 Minuten. Die tonale Aussage des Vergleichs bleibt von den gewählten Patches abhängig.

Geeignete Paare:

- `2003-auto`: durchgehende Bassfiguren und erstmals komplementäres Arpeggio.
- `2029-auto`: synkopierte Funkreferenz.
- `2035-auto`: auch mit unverändert bestehenden melodischen Bassphrasen.
- `static-harmony`: statische Harmonik als Rhythmuskontrolle.
- `bass-follow-off` und `both-follow-off`: gleiche Koordination, ursprüngliche harmonische Follow-Funktion.
- `high-root-eighths`: hohe Bassenergie mit weiterhin einfachen Grundtonachteln.
- `pedal`, `dense-sixteenths`, `manual-bass`, `phrased-motif`: bewusst unveränderte Gegenbeispiele.

Für einen direkten Plugin-Test: Pop/Rock, 4/4, Aufbau AUS, keine endliche Szenenlänge, Bass/Arpeggio und Arprate jeweils Auto; Bass und Arp aktiv, Gegenstimme stumm, Melodie AUS, getrennte MIDI-Kanäle. Zunächst XYZ `(0,30 / 0,40 / 0,15)` für Nachtfahrt/2003 oder `(0,88 / 0,48 / 0,03)` für Sonntagmorgen/2035, Variety 0. Automatische Muster wechseln weiterhin wie bisher mit der Variation und Phrase; daher mindestens 128 Takte vergleichen, statt einen einzelnen Takt als Funktionsnachweis zu verwenden.

## Messwerte: 128 Takte bei 120 BPM

| Fall | Koordinierte Takte | Bassanschläge vor/nach | Arpanschläge vor/nach | Gemeinsame vor/nach | Komplementäre Arp vor/nach | Gemeinsame Viertel vor/nach |
|---|---:|---:|---:|---:|---:|---:|
| 2003-auto | 40 | 1408 / 1408 | 1024 / 1024 | 1024 / 864 | 0 / 160 | 512 / 512 |
| 2029-auto | 40 | 656 / 656 | 1024 / 1024 | 336 / 296 | 688 / 728 | 256 / 256 |
| 2035-auto | 16 | 752 / 752 | 1024 / 1024 | 432 / 416 | 592 / 608 | 352 / 352 |
| bass-follow-off | 16 | 752 / 752 | 1024 / 1024 | 432 / 416 | 592 / 608 | 352 / 352 |
| high-root-eighths | 32 | 1024 / 1024 | 1024 / 1024 | 1024 / 896 | 0 / 128 | 512 / 512 |
| pedal | 0 | 512 / 512 | 2048 / 2048 | 512 / 512 | 1536 / 1536 | 512 / 512 |
| dense-sixteenths | 0 | 1472 / 1472 | 1536 / 1536 | 1088 / 1088 | 448 / 448 | 416 / 416 |
| phrased-motif | 0 | 752 / 752 | 939 / 939 | 396 / 396 | 543 / 543 | 322 / 322 |
| score-neutral | 0 | 512 / 512 | 828 / 828 | 414 / 414 | 414 / 414 | 414 / 414 |
| score-barry | 0 | 512 / 512 | 828 / 828 | 414 / 414 | 414 / 414 | 414 / 414 |
| score-herrmann | 0 | 512 / 512 | 828 / 828 | 414 / 414 | 414 / 414 | 414 / 414 |

Über alle 195 Fälle: 864 koordinierte Takte, 2.544 verschobene Arpanschläge. Gemeinsame Anschläge werden nicht minimiert; metrische Orientierung und der Trägerbass bleiben erhalten. Im endgültigen Taktgrenzen-synchronisierten Blockvergleich gab es tatsächlich keine Sampleabweichungen (auch nicht im Referenzgenerator). Die zulässige Ein-Sample-Rundungstoleranz musste nicht ausgeschöpft werden.

Bei 2035 liegen sechs der 16 koordinierten Takte innerhalb bereits geplanter melodischer Bassphrasen; deren vollständiger Bass-MIDI-Strom bleibt unverändert. Die zusätzliche Policy-Probe mit `everyBars=1` verdoppelt die koordinierten Takte von 16 auf 32, ohne Bass- oder Arpanschläge hinzuzufügen.

Die vollständige Häufigkeitsverteilung der Einsatzraster, Prüf-MIDI-Summen und Einzelwerte steht in `RHYTHMIC_INTERLOCK_COMPARISON.json`. In der MIDI-Ausgabe bleibt der charakteristische rhythmische Wechsel hörbar prüfbar, seine musikalische Überzeugungskraft ist ohne Hörabnahme vorläufig.

## Abschließende Tests

- 25/25 CTest-Kerntests bestanden, einschließlich aller bestehenden und der neuen MIDI-Vergleiche.
- 195 vollständige 128-Takt-A/B-Fälle gegen `b0170ee`, 390 Blockvergleiche und 65 zusätzliche bytegleiche Wiederholungsrenderings bei 120 BPM bestanden.
- Koordination während bereits geplanter melodischer Bassphrasen nachgewiesen; Bass-MIDI bleibt exakt unverändert.
- ASan/UBSan: RhythmPlanTests mit Echtzeit-Allokationsprüfung, Seek, Swing, Loop und Neustart bestanden.
- Vollständiger JUCE-ProcessorTests-Lauf einschließlich explizitem verzögertem Arpeggioeinsatz und Plugin-Live-/Exportgleichheit bestanden.
- 7/7 vorhandene Release-Gate-Fixtures bestanden; es wurde kein Release erstellt.
- JUCE meldet in dieser Umgebung Fontconfig-Cachewarnungen; die Tests enden erfolgreich. Bestehende Compilerwarnungen bleiben bestehen.

Kein Push und kein Release. Kein Windows-DAW- oder Patch-Hörtest durchgeführt.
