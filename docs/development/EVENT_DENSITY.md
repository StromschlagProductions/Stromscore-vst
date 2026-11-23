# Intensität und Ereignisdichte

Ausgangspunkt: `2f4dd47`, `develop/composition-core-prototype`.

## Befund der bisherigen Kopplung

`stepOn()` setzte für den gesamten `render()`-Aufruf `Settings.y` auf
`clamp(y * dens + yAdd)`. `dens` stammt aus Aufbau und ausklingendem Szenenende;
`yAdd` ist dagegen die ausdrücklich vorgesehene Energiesteigerung eines offenen Endes.

| Stelle in ScoreEngine.h | Wirkung der bisherigen Intensitätsreduktion |
|---|---|
| `choosePad`, `chooseBass` | Andere automatische Muster, gehalten statt bewegt, andere Bassraten |
| `render`, `autoArpeggioTicks` | Arp-Tempo, Bassbewegung, Pedalpuls, Anschlagsstärken |
| `planMotifNote` | Zahl der Einführungstöne, deren Velocity und damit die gespeicherte Wiederkehr-Velocity |
| `counterLine`, `leadHook` | Linienbewegung und Rate; Anschlagsstärke; Pop-Hook-Tempo |
| `tupferAt`, `accents`, `foreignTone`, `stich` | Einwurfwahrscheinlichkeiten, Stichschwellen, Dauer und Stärke; einzelne Reibungsentscheidungen |
| `prepareVoicingPlan` / `buildAnchor` | Intensitätsabhängige Oktavverdopplung und Freigabe von Durchgangsdominanten |
| `sustained` | Velocity von Harmonie und Bass |
| `dynamicsCc` | CC-Grundwerte, Bogenamplitude und Expression |
| `motifWindow` | Indirekt Spielbarkeit und Zeitfenster der Motivfigur über deren Notenberechnung |

Wendungsauswahl, Stillstand und Ebenenaktivierung liegen vor dieser Kopie und verwenden
bereits das unverringerte Feld. Färbung und Unruhe selbst wurden nicht multipliziert.
`riss()` verwendet überwiegend Unruhe; trotzdem lief die Ausgabe im gemeinsamen,
reduzierten Ausdruckskontext. Tonumfang, Routing und Notenbesitzverwaltung sind getrennt.

## Kleine gemeinsame Lösung

`composition::EventDensity` ist eine zustandslose Maske für optionale metrische Gruppen.
Der Adapter verwendet die unverändert vorhandene `dens`-Kurve. Die Zahl zugelassener
Gruppen ist `ceil(dens * Gruppenanzahl)`. Gerade Gruppen werden vor ungeraden zugelassen;
in 4/4 lautet die Rangfolge 1, 3, 2, 4. Die Masken sind geschachtelt und benötigen weder
Zufallszahl noch zusätzlichen GUI-/Profilparameter. Bei voller Dichte werden alle Gruppen
zugelassen. Positive Dichte behält stets die erste Gruppe.

`render()` erhält keine durch Ausdünnung reduzierte Intensität mehr. Auto-Muster,
Bewegungsraten, Velocity, Akkordlage und CC-Ausdruck sehen wieder die Feldintensität mit
bestehenden Ebenen-Offsets. Ausschließlich die schon vorhandene bewusste Energiesteigerung
`yAdd` des offenen Endes wird weiterhin addiert. Sie ist keine Ausdünnung.

Gefiltert werden neue optionale Flächenimpulse, rhythmische Basswiederholungen, gewöhnliche
Arp-Anschläge, Einwürfe und Risse. Der Filter lässt laufende Noten regulär ausklingen.
Bass-/Arp-Anschläge an Akkordgrenzen bleiben zugelassen, sofern das jeweilige bestehende
Muster dort einen Anschlag vorsieht; es werden keine zusätzlichen Anschläge erzeugt.
Gehaltene Harmonie, gehaltenes Bassfundament, Aufbau-Reihenfolge, Hysterese, Ausblendung,
Basspause vor Zielen, Vorbereitungsstich und harter Schluss bleiben erhalten.

Die Motivausgabe und die speziellen Antwortfunktionen umgehen die Ereignismaske. Auch die
Motivfenster-/Arp-Koordination aus `2f4dd47` wird unverändert vor dem optionalen Arp-Filter
geprüft. Motive werden weder zufällig noch gruppenweise zerschnitten.

**Bewusst erhaltene Materialentscheidung:** Die vorhandene Tonzahlwahl bei einer neuen
Motivaufnahme verwendet weiterhin ihren bisherigen Materialkontext (`curY * dens + yAdd`
mit bisherigen Schwellen und Ebenen-Offset), getrennt von der wiederhergestellten Velocity.
So bleiben eingeführte Intervalle, Rhythmus, Dauern und Identität gegenüber `2f4dd47`
erhalten. Diese eng begrenzte Auswahl wurde nicht musikalisch umgestaltet. Der neue
Ausdünnungsfilter entfernt keine Einzelnoten aus solchen Figuren. Eine vollständig neue,
von diesem Kontext unabhängige Motiv-Tonzahlplanung wäre ein eigener musikalischer Schritt.

## Vergleichsverfahren

`tools/density_probe.cpp` rendert vollständige Note-/CC-Ereignisse sowie taktweise
Wendungs-/Akkord- und Motividentitätsdiagnosen. Es gibt 21 Situationen für jeweils Neutral,
Barry und Herrmann (48 Sekunden, 48 kHz, 120 BPM): stationäre hohe/niedrige Intensität,
Aufbau, automatische/manuelle Muster, Ausklang, offenes/hartes Ende, Pop/Rock, geschützte
Motive, Melodie, Seek/Loop, Neustart, manueller Schluss, Katalogharmonie, Durchgänge und
Ausblenden ohne CC-Ausgabe.

`scripts/compare_density.py` baut zwei temporäre Vergleichsprogramme:

1. den wirklichen Ausgangsstand `2f4dd47`;
2. den aktuellen Code mit ausschließlich auf 1 gesetzter Ereignismaske. Aufbau, Ausdruck,
   Motive und alle übrigen Mechanismen bleiben in dieser wissenschaftlichen Kontrolle aktiv.

Die zweite Kontrolle isoliert den Filter von der gleichzeitig korrigierten Energie.
Jede überlebende Notenspanne muss mit Tonhöhe, Velocity, Anschlag und Freigabe exakt in
der Kontrolle vorhanden sein. CC-Ereignisse und sämtliche Melodie-/Dialogereignisse müssen
mit dieser Kontrolle übereinstimmen. Gegen den Ausgangsstand werden harmonische Planung
und Motividentitäten verglichen; nicht ausgedünnte Fälle einschließlich Pop/Rock und
bewusster offener/harter Enden müssen vollständig bytegleich bleiben.

Alle Hauptfälle werden zusätzlich mit 127 und 8192 statt 512 Samples geprüft. Die
CSV-Dateien enthalten Vorher, Nachher, Kontrolle sowie einzeln entfallene/hinzugekommene
Note-ons gegenüber Ausgangsstand und Kontrolle. Die JSON-Zusammenfassung enthält SHA-256,
Anschlagszahlen und Velocity-Änderungen. Kein Referenzgenerator wird ins Plugin eingebaut.

```sh
python3 scripts/compare_density.py --probe /pfad/zum/Build/DensityProbe \
  --compiler c++ --output /tmp/stromscore-density
```

CTest registriert den Referenzvergleich bei vorhandenem Git-Ausgangspunkt, Python und
GCC-/Clang-kompatiblem Compiler. Plattformunabhängige Tests prüfen die Masken sowie direkt
an der Engine, dass bei niedriger und hoher Energie ein Basspuls von 16 auf 8 Anschläge
reduziert wird, ohne irgendeinen überlebenden Anschlag leiser zu machen.

Der historische Begleitvergleich gegen `237b415` prüft weiterhin alle unveränderten
Kontexte. Seine drei Aufbau-Vergleiche sind jetzt durch den gezielten Dichtevergleich
ersetzt, weil die Energiekorrektur dort ausdrücklich musikalische Unterschiede erzeugt.

## Grenzen

- Die Maske ist eine grobe metrische Ausdünnung, keine gewünschte exakte Note-on-Zahl.
  Bereits sehr sparse Musik kann unverändert bleiben. Geschützte Motive setzen eine Untergrenze.
- Gewöhnliche Begleitfiguren laufen phasenrichtig weiter; ihre metrischen Gruppen können
  pausieren. Eine allgemeine Erkennung/Schonung beliebiger längerer Ostinatogestalten fehlt.
- Bei geringer Intensität können gegenüber der alten Ausgabe mehr Noten entstehen, weil
  deren unbeabsichtigte zusätzliche Verlangsamung entfällt. Die neue Maske reduziert stets
  gegenüber der gleichen musikalischen Energie, nicht zwingend gegenüber der alten Kopplung.
- Die ausdrücklich vorhandenen Ein-/Ausblendungen dürfen weiterhin leiser werden. Nur der
  Ereignisfilter selbst reduziert keine Velocity oder CC-Werte.
- Neue Künstlerstrategien, Kataloge, Gewichte, GUI, Motivrepertoire und Formgrammatik sind
  nicht Bestandteil dieses Schritts. Die drei Profile verwenden denselben Mechanismus.

## Messergebnisse

63 Vergleiche (21 Situationen × 3 Profile) gegen Ausgangsstand und Kontrollausgabe sowie
126 zusätzliche Blockgrößenvergleiche bestanden. `EVENT_DENSITY_COMPARISON.json` enthält
alle Zahlen und Prüfsummen. Die nachfolgende Auswahl zählt sämtliche Note-ons über 48
Sekunden für Neutral; die Kontrolle hat dieselbe Energie, dieselben Ein-/Ausblendungen
und denselben Rollenplan, aber keine Ereignisfilterung.

| Fall | Ausgangsstand | Neu | Kontrolle gleicher Energie | Nur durch Maske entfallen |
|---|---:|---:|---:|---:|
| high-steady | 1126 | 1126 | 1126 | 0 |
| high-build | 973 | 962 | 981 | 19 |
| low-build | 199 | 204 | 205 | 1 |
| manual-build | 1661 | 1639 | 1677 | 38 |
| auto-fade | 575 | 565 | 583 | 18 |
| manual-fade | 1015 | 995 | 1031 | 36 |
| protected-motif | 6 | 6 | 6 | 0 |
| melody-build | 1023 | 1004 | 1035 | 31 |
| pop-steady | 1789 | 1789 | 1789 | 0 |
| pop-build | 1578 | 1570 | 1590 | 20 |
| pop-fade | 895 | 881 | 915 | 34 |

Beispiel `manual-build`: gegenüber dem Ausgangsstand entfallen 34 konkrete Anschläge und
12 kommen hinzu; netto ergeben sich 22 weniger. Gegen dieselbe Energie ohne Dichtemaske
entfallen ausschließlich 38 Anschläge, ohne Ersatzanschläge. 342 gemeinsame Anschläge
haben gegenüber dem Ausgangsstand eine höhere Velocity; keiner eine geringere.

Im isolierten portablen Bass-Test entstehen bei hoher wie niedriger Intensität 8 statt
16 Anschläge im ersten 4/4-Takt; jeder überlebende Anschlag stimmt einschließlich Velocity
und Notenende mit der ungedünnten Referenz überein. Das belegt die Entkopplung unabhängig
vom alten, ebenfalls musikalisch veränderten Ausgangsstand.

In allen drei Profilen stimmen die taktweisen Wendungs-/Akkorddiagnosen und Motividentitäten
mit dem Ausgangsstand überein. Stationäre Fälle ohne Ausdünnung sowie offene/harte Enden
sind vollständig bytegleich. Das gilt auch für die Pop/Rock-Regression ohne Ausdünnung.
Pop/Rock-Aufbau und -Ausklang erhalten wie Score die ausdrücklich gewünschte Korrektur.

Die identischen Motivintervalle, Rhythmen und Dauern können durch wiederhergestellte
Ausdruckswerte kräftiger erklingen. Motive werden von der Maske nicht zerteilt. Der Schutz
ist zusätzlich gegen die unverändert energiereiche Kontrollausgabe ereignisgenau geprüft.

## Validierung

- 9/9 Kern-CTest-Prüfungen bestanden, einschließlich Dichte- und Begleitvergleich.
- Linux/Xvfb-Processor-Prüfung 1/1 bestanden; zusätzliche Aufbau-/Ausklangfälle stimmen
  zwischen Live-Ausgabe und tatsächlichem MIDI-Dateiexport einschließlich CC überein.
- ASan/UBSan für CompositionCore, Policy und Engine: 3/3 bestanden.
- Python-Paketprüfer: 7/7 bestanden.
- Keine neue Windows-/pluginval-Prüfung und keine subjektive Hörabnahme.

Kein Push, kein Release.
