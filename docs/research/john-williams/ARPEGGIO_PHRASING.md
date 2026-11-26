# Williams – musikalische Auto-Arp-Phrasierung

Basis: `14ece80`, musikalischer Vergleich gegen `ddad94b`. Ausschließlich die
freigegebene Arp-Phrasierung, keine neuen Motive, Tonvorräte, Harmonievorlagen oder GUI.

## Umsetzung

`Source/ArpeggioPhrase.h` enthält eine kleine gemeinsame `ArpeggioPhrasePolicy`
und einen begrenzten Plan aus höchstens zwei zusammenhängenden Figurenfenstern.
`CompositionPolicy.h::williamsPolicy` aktiviert diese Fähigkeit ausschließlich für
Williams. Die neutralen, Barry- und Herrmann-Policies bleiben inaktiv; Pop/Rock
verwendet weiterhin seine neutrale Policy. Im Adapter ist der erste Anwendungsfall
zusätzlich auf Williams Score, 4/4 und automatische Figur **und** automatisches
Tempo begrenzt. Manuell gewählte Figur oder Rate bleibt vollständig vorrangig.

Bei der ersten regulären Arp-Auswertung eines Harmonieabschnitts wird eine
reproduzierbare Lesart für dessen Zeitfenster gewählt:

- Durchgehende Bewegung ohne neue Pause.
- Ein zusammenhängender Gedanke mit abschließender Atempause.
- Bei ausreichend langer Harmonie zwei Figuren mit einer Zwischenpause und einem
  atmenden Ende; die zweite Figur verwendet die vorhandene Ton-/Rhythmusfortsetzung.

Die Auswahl berücksichtigt ursprüngliche Energie, Unruhe und einen bereits
validierten Williams-Kurzflächen-/Bassplan als möglichen Begleitpartner. Sie
bevorzugt bei passendem Kontext eine Übergabe der Bewegung, sperrt das Arp aber
nicht aufgrund eines eingeschalteten Bass-/Flächen-Schalters. Auch ohne solchen
Partner ist eine Atempause möglich. Das sind musikalische Auswahlgewichte, keine
zu erreichenden Aktivitätsprozente. Hohe Energie/Unruhe erhöht zugleich das Gewicht
fortlaufender Bewegung; kein festes Laufzeitlimit und keine Pause nach N Takten.
Die Gewichte sind editorielle erste Setzungen für die kommende Hörabnahme.

Pausen orientieren sich am Ende des vorliegenden Harmonieabschnitts: letzter Schlag
bei kurzer Harmonie, halber oder ganzer Takt bei längeren Gedanken. Zwischenfiguren
verwenden halbtaktige Gruppengrenzen. Das ist eine begrenzte metrische Phrasierung,
noch keine Analyse der melodischen Schlussnote jeder Arp-Kontur. Nicht jeder
Harmonieabschnitt muss pausieren; aufeinanderfolgende kontinuierliche Pläne können
beliebig lange Bewegung ergeben. Die neu entstehenden Onsetmasken erlauben
Wiederholung und rhythmische Veränderung ohne einzelne Zufallsnoten auszustanzen.

`ScoreEngine::arpeggioFigureEnd` hält den Plan im aktuellen Harmonieabschnitt fest.
XYZ-Bewegung berechnet ihn dort nicht ständig neu; die vorhandene expressive und
harmonische XYZ-Steuerung läuft weiter. Der nächste Abschnitt kann eine neue Lesart
wählen. Variation/Seed und musikalischer Anfang bestimmen die reproduzierbare Wahl.
Szenenneustart und Profilwechsel löschen diesen kleinen Zustand; Seek rekonstruiert
am Ziel. Die akzeptierte Einschränkung fehlender Vorgeschichte bei kaltem Seek mit
veränderten Parametern bleibt bestehen; keine neue Historienarchitektur.

## Bestehende musikalische Funktionen

Motivfenster und Dialog-/Arp-Antworten behalten ihre bestehende Priorität.
Die neue Planung wird erst im regulären `playArpeggio` angewendet. Sie verändert
weder gespeichertes Motivmaterial noch Bass-/Flächenplanung. Notenanfänge, Tonwahl,
Geschwindigkeit, Velocity und Zufallsindizes der erhaltenen Arp-Anschläge bleiben
bestehen. Gates dürfen am geplanten Figurenende enden. Kein neues Einsatzraster,
keine zusätzliche Uhr und keine Dateioperation/Allokation im Audiothread.

Harmonische Anker und Akkordfarben bleiben gleich. Der bestehende Dispatcher
führt zusätzliche Notenenden deterministisch aus. Dadurch kann sich die Reihenfolge
anderer Ereignisse am **gleichen** Sample ändern, ohne dass deren Zeitpunkte,
Tonhöhen, Velocity oder Dauern verändert werden. Die A/B-Prüfung vergleicht deshalb
andere Rollen als vollständige Ereignismengen mit Samplezeit und Kanal; getrennte
Notenbilanzen sichern das zulässige Note-on/off-Verhalten.

Die gemeinsame Fähigkeit erlaubt ausdrücklich eine kontinuierliche Strategie
(`enabled=false` oder beide Pausengewichte null). Zukünftige SYNTH-Strategien müssen
keine Williams-Atempause übernehmen. Es wurde kein SYNTH-Modus implementiert.

## Reproduktion und A/B-Hörpaket

`python scripts/validate_arpeggio_phrasing.py /tmp/arp-phrasing` baut Produktions-
kompilate gegen `ddad94b` und den aktuellen Quellstand. 52 Williams-A/B-Paare über
je 128 Takte: elf feste XYZ-Positionen und langsame/schnelle externe Fahrten,
jeweils ohne beide Melodierollen, nur Melodie, nur Dialog und mit beiden.
D, 100 BPM, 4/4, Auto, Follow EIN, Motiv EIN, Aufbau AUS, unbegrenzt ohne interne
Fahrt; gleiche Variation 3. Zusätzlich manuelle Figur/Rate, Wiederholung und
Blockgrößenkontrollen. Kein Vergleich eigener nachkomponierter Sequenzen.

[ARPEGGIO_PHRASING_AB.zip](ARPEGGIO_PHRASING_AB.zip) enthält 24 tatsächliche
Vorher-/Nachher-MIDIs: dunkle/helle Unruhe und Action sowie langsame/schnelle Fahrten,
mit ausgeschalteten oder beiden aktiven Melodierollen. Gleiche Instrumente und
Pegel benutzen; besonders Bewegungsübergaben, Stille, Wiedererkennbarkeit und
Zusammenhang hören. Weniger Aktivität ist ausdrücklich kein Qualitätsbeweis.

[ARPEGGIO_PHRASING_RESULTS.json](ARPEGGIO_PHRASING_RESULTS.json) enthält alle
Einzelfälle, Source-Prüfsummen, klingende Zeit, aktive Takte, längste Läufe und
Pausebeginn/-dauer. Gate misst MIDI, nicht Release/Hall externer Patches.
Ein Aktivitätslauf endet in dieser Auswertung erst bei mindestens einer Viertelpause;
kurze Artikulationslücken sind keine musikalische Atempause.

## Grenzen und Hörabnahme

Die Strategie verwendet bisher den vorhandenen begrenzten Begleitplan und kein
vollständiges Vorauswissen aller manuellen/automatischen Bassfiguren. Es gibt
keine neu erfundene zweite Texturplanung. Normale Arp-Tonwahl bleibt auch dann
bestehen, wenn ein anderes Schlussziel später musikalisch besser wäre. Konturziel,
komplexe Rollentransfers und neue Motivvorlagen sind nicht Bestandteil dieses Schritts.
Unpassende Hostmetren verwenden den bestehenden Pfad statt eines abgeschnittenen
4/4-Plans. Manuelle Arps und andere Profile erhalten keine neue Phrasierung.

Die Anwender-Hörabnahme entscheidet über die musikalische Eignung. Messbare Pausen
und unveränderte Begleitnoten belegen Funktion und Abgrenzung, keine endgültige
Williams-Handschrift. Keine weitere Entwicklungsphase, kein Push und kein Release.

## Tatsächliche Vergleichsergebnisse (128 Takte)

Gate = klingende MIDI-Zeit, Lauf = längster Abschnitt ohne Viertelpause.

| XYZ / Verlauf | Melodierollen | Gate vorher → nachher % | Lauf vorher → nachher Takte | Arp-Onsets vorher → nachher |
|---|---|---:|---:|---:|
| dunkel/leise/unruhig | aus | 100.0 → 82.031 | 128.0 → 6.5 | 1024 → 840 |
| dunkel/leise/unruhig | beide ein | 79.492 → 64.258 | 14.5 → 5.5 | 814 → 658 |
| dunkel/kraftvoll/stabil | aus | 100.0 → 87.109 | 128.0 → 7.75 | 2048 → 1784 |
| dunkel/kraftvoll/stabil | beide ein | 90.625 → 78.906 | 38.0 → 7.75 | 1856 → 1616 |
| dunkle Action | aus | 100.0 → 87.695 | 128.0 → 19.0 | 2048 → 1796 |
| dunkle Action | beide ein | 81.641 → 70.898 | 18.0 → 10.0 | 1672 → 1452 |
| hell/leise/unruhig | aus | 100.0 → 82.422 | 128.0 → 3.75 | 1024 → 844 |
| hell/leise/unruhig | beide ein | 88.379 → 73.242 | 22.625 → 3.75 | 905 → 750 |
| helle Action | aus | 100.0 → 85.156 | 128.0 → 5.75 | 2048 → 1744 |
| helle Action | beide ein | 82.617 → 70.117 | 14.5 → 5.75 | 1692 → 1436 |
| langsame XYZ-Fahrt | aus | 99.951 → 87.061 | 128.0 → 11.75 | 1716 → 1508 |
| langsame XYZ-Fahrt | beide ein | 81.396 → 71.436 | 14.0 → 10.5 | 1392 → 1234 |
| schnelle XYZ-Fahrt | aus | 99.854 → 85.596 | 128.0 → 7.5 | 1751 → 1504 |
| schnelle XYZ-Fahrt | beide ein | 82.91 → 69.629 | 15.75 → 5.5 | 1466 → 1237 |

Die beiden leisen stabilen Punkte bleiben ohne Arp. Im dunklen Actionfall ohne
Melodierollen bleiben 1796 von 2048 Arp-Anschlägen; mit beiden 1452 von 1672.
Die übrigen Rollenereignisse stimmen in allen 52 Paaren einschließlich ihrer
Note-offs und CC-Werte überein. Alle erhaltenen Arp-Note-ons entsprechen exakt
vorherigen Anschlägen; nur geplante Fenster entfallen und Gates enden gegebenenfalls
am Fensterende. Keine pauschale Dynamikänderung und keine neue Tonwahl.

Die neu eingefügten Pausen reichen in diesen Fällen typischerweise vom letzten
Viertelschlag bis zum halben/ganzen Takt; vorhandene Motivfenster können längere
Pausen ergeben. Viele kurze Harmonieabschnitte können dadurch recht viele kurze
Atemstellen erzeugen. Ob das zu kleinteilig oder überzeugend phrasiert klingt,
ist eine ausdrückliche Frage für die Hörabnahme. Es wurde keine Aktivitätszielzahl
optimiert. Auch nach der Änderung bleiben längere durchgehende Läufe vorhanden.

30 zusätzliche vollständige Renderings von Neutral/Barry/Herrmann in Score und
Pop/Rock bleiben bytegleich zur Referenz `8d4086c` (musikalisch ebenfalls in
`ddad94b` unverändert). Fünf Williams-Pop-Durchläufe bleiben neutral. Die bestehende
Williams-Validierung bestand mit 20 Block- und 16 Follow/Manuell/Swing/Metrik-
Kontrollen sowie Stop/Neustart/Loop/Seek. Ihre neuen Prüfergebnisse stehen in
[ARPEGGIO_PHRASING_REGRESSION.json](ARPEGGIO_PHRASING_REGRESSION.json); die historischen
P1-Hördateien und P1-Messdaten wurden unverändert erhalten.

Zusätzlich wurden 18 direkte Bytevergleiche gegen `ddad94b` für Neutral, Barry und
Herrmann in Score/Pop bei statischem XYZ sowie langsamer/schneller Fahrt bestanden.
Die echte JUCE-Suite Processor/ProcessorProfileSwitch bestand 2/2 einschließlich
Williams-Live-/Export. Der gezielte Williams-Prüflauf unter ASan/UBSan und
Allokationswache bestand; die Paketprüfer bestanden 7/7. Die gezielten Williams-/
Policy-Tests bestanden 2/2. Der gemeinsame Plan ist in den Unit-Tests sowohl mit
kontinuierlichen Fenstern als auch mit Abschluss-/Zwischenpausen abgedeckt.

Der abschließende reguläre Core-Gesamtlauf bestand **57/57 Tests** (960,44 Sekunden),
einschließlich musikalischer Ereignisausführung, Harmonie-/Akkorddaten, Rhythmik,
Motivfenster, Wiederkehr, Übergangsstimmführung, Dichte und Begleitkoordination.
Alle Ergebnisse beziehen sich auf den unveränderten finalen Produktionsquellstand.
Es wurde nach bestandenen Prüfungen kein weiteres musikalisches Verhalten ergänzt.
