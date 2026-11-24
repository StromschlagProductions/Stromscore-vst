# Melodisch eigenständige Bassphrasen

Basis: `888ff82`, Entwicklungsbranch `develop/composition-core-prototype`.

## Befund und kleinster Eingriff

`Generator::rawBassPattern()` bewahrt die bisherige automatische Auswahl: unter 0,15 gehalten, unter 0,30 gegebenenfalls Halbe, oberhalb 0,92 einfache Achtel; dazwischen das vorhandene Wendungsinventar. Manuelle Muster haben Vorrang. `chordFor()` berücksichtigt die bisherige Follow-Einstellung; `prepareVoicingPlan()` liefert kanonische Basslagen und Slash-Basstöne. Orgelpunkt, Pendel, gehaltene und pulsierende Figuren bleiben eigene Optionen. Follow AUS bewahrt exakt die bisherige harmonische Referenz; einzelne Muster enthalten weiterhin ihre bisherigen Quinten/Oktaven. Das ist keine neue melodische Bewegung.

`BassFunction` unterscheidet Fundament, Orgelpunkt, Ostinato und melodische Linie. Motivischer Bass bleibt eine spätere Funktion, ohne Speicher oder neue Implementierung in diesem Schritt. Die Typen bewerten keine Funktion als höherwertig.

## Architektur

- `Source/BassPhrase.h`: gemeinsamer, allokationsfreier `planBassPhrase(BassPhraseRequest)` mit begrenztem `BassPhrasePlan`. Zwei echte Akkordregionen, harmonische Anker, Akkordmasken, modaler Kontext, Register und Dauern sind explizite Eingaben. Keine eigene Pop/Rock-Tonhöhenarchitektur.
- `FreeCompositionPolicy::bass`: aktiv, Gelegenheit alle drei Paarfenster, maximaler bevorzugter melodischer Sprung sieben Halbtöne. Alle Profile verwenden dieselben Werte.
- `Generator::prepareBassPhrase()`: schmaler Adapter, verbindet vorhandene harmonische Planung und `modalContextFor()` mit dem gemeinsamen Planer. Geeignete aufeinanderfolgende Regionen werden paarweise betrachtet. Ungerader Restakkord bleibt unverändert.
- `funkBassAttack()` ist die einzige Definition des bisherigen Funk-Rhythmus für Planung und Rendering. Es werden keine Anschläge ergänzt. Akzente, Synkopen und Dauern bleiben erhalten.
- Die erste Note jeder Region bleibt die vorhandene Basslage. Dazwischen bevorzugt die Linie kleine Bewegungen zu einer Akkordterz und zum nächsten Bassanker; Wiederholung ist ausdrücklich erlaubt. Größere harmonische Ankersprünge werden nicht durch Änderung der Basstonklasse versteckt.
- Höchstens ein geeigneter diatonischer Durchgangston ersetzt einen vorhandenen schwachen Anschlag. Gemeinsames `planPassingTone()`, eindeutiger Gesamtmodus, gerichtete Schritte, tatsächliche nächste Zielnote, keine Akkordgrenzüberschreitung. Eine vorhandene kurze Artikulationspause darf erhalten bleiben.
- Ein angenommener Plan hält seine Funk-Spielweise bis zum Paarende auch bei Intensitätsänderung fest. Velocity folgt weiterhin der aktuellen Intensität. Ausdrückliche Änderungen von Harmonie, Follow, Muster, Register oder Verfügbarkeit können ihn abbrechen. Kein Rekonstruieren unbekannter Automationshistorie bei kaltem Seek.
- Reset/Szenenneustart löschen den transienten Cache; Seek rekonstruiert den Plan aus absoluten Positionen und Einstellungen. Chase berücksichtigt gehaltene geplante Bassnoten.

## Bewusst begrenzte Aktivierung

Nur Pop/Rock, Auto-Bass, tatsächlich aktive Bassstimme, Follow AN und vorhandene automatische Funk-Auswahl. Nur 4/4, zwei mindestens eintaktige Regionen, höchstens acht Takte insgesamt, eindeutiger gemeinsamer Modus und spielbarer Tonumfang. Keine Aktivierung bei Aufbau, endlicher Szenenlänge/Ende, Einstiegsoverride, Stillstand oder Zwischendominanten. Geteilter Bass-Kurz-MIDI-Kanal führt konservativ zum alten Verhalten. Keine Änderung an anderen Bassmustern, Score, Harmoniekatalog, Profilgewichtungen oder Motiven.

## Reproduzierbarer Nachweis

```sh
python3 scripts/compare_bass_phrases.py \
  --probe ../stromscore-core-build/BassPhraseProbe --output ../bass-phrases
```

Der Vergleich kompiliert den tatsächlichen Referenzstand `888ff82`. 30 Szenarien bei 90/120/173 BPM, jeweils 128 Takte, mit/ohne Swing. Dazu 180 Blockvergleiche (127/8192 gegen 512 Samples) und 24 reale Adapterrenderings in allen zwölf Tonarten. Bei 173 BPM wird die vorhandene Rundungsabweichung bis ein Sample toleriert, musikalische Ereignisse und Pläne bleiben gleich. Weitere Tests prüfen wiederholten Seek, Loop, kalten Seek, Neustart und Intensitätswechsel. Der JUCE-Prozessortest ergänzt einen 64-Takt-Fall für die tatsächliche Plugin-Live-/Exportstrecke; die Exportoberfläche bleibt auf 64 Takte begrenzt.

Historische Motiv-/Score-Probes setzen ausschließlich für ihre bisherigen Referenzvergleiche `policy.bass.enabled=false`. Das ist ein testseitiger Kontrollwert, keine parallele Produktionsengine. Der neue Vergleich testet die tatsächlichen Standardwerte und verlangt zusätzlich, dass ausgeschaltete Bassplanung exakt den alten Stand liefert.

Vollständige Messwerte, MIDI-Prüfsummen, Intervallverteilungen, Registerextrema und Planbeispiele: `BASS_PHRASE_COMPARISON.json`. Generierte MIDI-Dateien: Ausgabeordner `../bass-phrases`, jeweils `*-before.mid` und `*-after.mid` (alle MIDI-Kanäle erhalten).

### Ergebnisse bei 120 BPM über 128 Takte

| Wendung/Fall | Geplante Linien | Anteil Anschläge in Linien | Bass-Note-ons vorher/nachher |
|---|---:|---:|---:|
| 2015 | 0 | 0 % | 1024 / 1024 |
| 2019 | 0 | 0 % | 832 / 832 |
| 2012 | 0 | 0 % | 1216 / 1216 |
| 2025 | 5 | 12,9 % | 976 / 976 |
| 2030 (Slash) | 0 | 0 % | 136 / 136 |
| 2031 | 0 | 0 % | 1024 / 1024 |
| 2032 | 0 | 0 % | 664 / 664 |
| 2035 | 6 | 22,3 % | 752 / 752 |
| 2013 | 6 | 14,8 % | 1136 / 1136 |
| 2028 | 6 | 14,8 % | 944 / 944 |
| 2021 (chromatisch) | 0 | 0 % | 1328 / 1328 |

Der übrige Anteil ist bisherige Ausgabe, nicht ausschließlich Grundton: alte Figuren enthalten ebenfalls Quinten/Oktaven. 87 Linien und 87 tatsächlich aufgelöste Durchgangstöne über alle 90 A/B-Fälle; dies ist keine vorgeschriebene Durchgangstonquote. Bei 2025 sind fünf von 976 Anschlägen Durchgangstöne (0,51 %). Insgesamt unveränderte Registerextrema in den Tabellenfällen. Bei 2025 steigt die Anzahl direkter Tonwiederholungen von 96 auf 158, Zweihalbtonbewegungen von 0 auf 15; die Funktion erzeugt also nicht pauschal mehr Bewegung.

Follow AUS (alle sieben geforderten IDs), manuelle Funk-/Achtel-/Puls-/Halte-/Pedalfiguren, enge Register, Aufbau, geteilter Kanal, Zwischendominanten und hohe Intensität mit einfachen Achteln bleiben bytegleich. Beispiel hohe Intensität: 1024/1024 Anschläge, keine neue Linie. Beim isolierten Live-Intensitätsanstieg bleibt der geplante Funk statt eines sofortigen Achtelwechsels bestehen: 955 → 952 Anschläge, keine Verdichtung. Die Wendung wird in diesem Test bis zur bestehenden Vier-Takt-Wechselgrenze gehalten, um reine Intensitätsänderung von harmonischem Wechsel zu trennen.

### Konkrete Linie: 2025, C-Moll9 → Esmaj7

Positionen in Sechzehnteln ab Szenenbeginn, MIDI-Notennummern; Paar 64–112, Akkordwechsel bei 96. Ausgangston C48, Zielanker Es51 bleiben an 64/96 erhalten.

| Position | Bisheriger Funk | Geplant | Dauer |
|---:|---|---|---:|
| 64 | C48 | C48 | 2 |
| 67 | C48 | C48 | 1 |
| 69 | G55 | Es51 | 1 |
| 72 | C48 | Es51 | 2 |
| 96 | Es51 | Es51 | 2 |
| 99 | Es51 | F53 (Durchgang) | 1 |
| 101 | B58 | G55 (Auflösung) | 1 |
| 104 | Es51 | Es51 | 2 |

Dazwischen bleiben vorhandene rhythmische Einsätze bestehen. Es wird als gemeinsamer Ton vorbereitet; Es–F–G ist im gemeinsamen dorischen Tonvorrat schrittweise, F kein Esmaj7-Akkordton. Vor G bleibt die ursprüngliche kurze Artikulationspause. Die vollständige Linie enthält 21 Anschläge, keinen zusätzlichen Ton.

## Hörvergleich und Grenzen

Für den ersten Hörtest Pop/Rock, 4/4, Aufbau AUS, keine endliche Szene/Zwischendominanten, Bass Auto, Follow AN, getrenntes Bass-Kurz-Ziel; 128 Takte abspielen. Direkte A/B-MIDI-Dateien `2025-auto-follow`, `2035-auto-follow`, `high-simple`, `pedal`, `2025-follow-off` und `manual-funk` demonstrieren sowohl neue Linien als auch bewahrte einfache Figuren. MIDI-B58 ist deutsches B, nicht H.

Das Verfahren ist eine kleine Konturplanung über zwei Regionen, keine allgemeine Basskompositions- oder Motivengine. Mehrdeutige Modi, kurze Regionen und ungeeignete Varianten fallen zurück. Es gibt noch keine explizite stilistische Auswahl zwischen Bassrollen und keine größeren Langformbögen. Live-Harmonieänderungen können einen Plan beenden; ein kalter Seek kennt keine vorherigen Automationen. Externe Patchfähigkeiten bleiben Generatorannahmen, keine automatische Erkennung. Eine endgültige Bewertung von Groove und musikalischer Qualität erfordert einen Hörtest.

## Abschließende technische Prüfung

- 23/23 CTest-Kerntests einschließlich aller bestehenden MIDI-Regressionen erfolgreich.
- Zusätzlicher vollständiger JUCE-`ProcessorTests`-Lauf einschließlich Bass-Live/Export erfolgreich (Linux, Xvfb).
- 3/3 native ASan/UBSan-Läufe: BassPhraseTests, ModalTests, EngineTests erfolgreich.
- 7/7 bestehende Release-Gate-Fixtures erfolgreich; kein Release erzeugt.
- Vollständiger Bass-A/B-Lauf einschließlich Dauergleichheit der statischen Fälle erfolgreich.
- Die JUCE-Ausführung meldet in dieser Umgebung Fontconfig-Cachewarnungen; die Tests enden erfolgreich. Vorhandene Compilerwarnungen bleiben bestehen.

Kein Push, kein Release. Ein Windows-Host-/Patch-Hörtest ist damit noch nicht ersetzt.
