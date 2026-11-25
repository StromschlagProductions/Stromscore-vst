# STROMSCORE 2.2 DEV – John Barry: Hörtest in Studio One Pro 8

Musikalischer Stand: `24f3c13` (Barry Phase 2 und 3), Branch
`develop/composition-core-prototype`. Der Paket-Commit einschließlich dieser Anleitung
steht in `BUILD.txt` und im Plugin als `v2.2 DEV <Commit>`. Kein offizielles Release.

## Installation und MIDI

Das Actions-Artefakt `Stromscore-2.2-DEV-<Commit>-Windows-x64` herunterladen.
Äußeres ZIP entpacken, danach das darin enthaltene Windows-VST3-ZIP entpacken.
Studio One schließen und eine vorhandene Installation außerhalb der VST3-Suchpfade sichern.
Den **gesamten Ordner** `Stromscore.vst3` nach
`C:\Program Files\Common Files\VST3\Stromscore.vst3` kopieren, dann in Studio One
neu scannen und die DEV-Kennung kontrollieren. Stabile und DEV-Version haben dieselbe
Plugin-ID und sollen nicht gleichzeitig installiert sein. Zum Zurückwechseln den
gesicherten Ordner wieder einsetzen. Bestehende Songs für den Hörtest kopieren.

Externe Instrumentenspuren mit Stromscore als MIDI-Eingang und dem jeweiligen Kanal
verbinden; Monitoring einschalten. Nicht auf allen Zielspuren „Alle Kanäle“ verwenden.

| MIDI-Ziel | Standardkanal |
|---|---:|
| Harmonie/Fläche lang / kurz | 1 / 2 |
| Bass lang / kurz | 3 / 4 |
| Arpeggio | 5 |
| Tupfer / Stich | 6 / 7 |
| Dialog/Gegenstimme | 8 |
| Hauptmelodie | 9 |

Zunächst gut hörbare, tonhöhensteuerbare Sustain-Klänge für Dialog/Melodie und passende
Kurz-Patches für kurze Begleitung verwenden. Legato steuert Notengates, keine Keyswitches.
Stich kann eine feste Sample-Triggernote senden; externe Patch-Fähigkeiten werden nicht erkannt.

## Gemeinsame Grundeinstellung

- **Score**, **KOMPONIST: John Barry**, Tonart **C**, automatische Wendungsauswahl:
  **keine eigene Akkordfolge** einstellen, damit das Barry-Harmoniematerial verwendet wird.
- **Aufbau AUS**, Fahrt AUS, Szenenlänge 0/unbegrenzt, Szene beenden AUS.
- Bass **Auto**, Arp-Figur **Auto**, Arp-Tempo **Auto**, „Folgt Akkorden“ für Harmonie/Bass EIN.
- Abwechslung zunächst **0 %**, Swing **0 %**, Oktaven Normal, unveränderte Tonumfänge.
  Für A/B denselben Wurf verwenden, etwa Wurf 3 über die DAW-Parameterliste.
- Alle Mute-/Solo-Schalter lösen. Dialog **Motiv EIN**, **Legato EIN**.
  Hauptmelodie zunächst **Aktiv AUS**. Keine zusätzliche CC-Lautstärkesteuerung zuschalten.
- Hosttempo **120 BPM** als Vergleich; der Host bleibt maßgeblich. Taktart gemäß Tabelle.
  XYZ bedeutet hier **Färbung / Intensität / Unruhe**, jeweils 0–1 (0,30 = 30 %).

## Empfohlene Hörkontexte

Die Angaben sind Startpunkte, keine zugesagten Original-Cues oder exakten Motivfolgen.
Harmonie, Register und Instrumentenfähigkeiten entscheiden, welche Vorlage spielbar ist.

| Hörziel | Takt | XYZ | Worauf hören? |
|---|---|---|---|
| Dunkel und geheimnisvoll | 4/4 | **0,20 / 0,45 / 0,40**; danach Y auf 0,80 | Dunkle Farbakkorde, kurze Zeichen und Pausen; Unterschied zwischen ruhiger und energischer Ausgestaltung. |
| Romantisch / warm | 4/4 | **0,80 / 0,30 / 0,10** | Warme Akkordfarben und Raum zwischen den Stimmen; kein erzwungener dichter Motor. |
| Melancholisch | 4/4 | **0,35 / 0,40 / 0,15** | Mit dem warmen Kontext vergleichen: dunklere Färbung bei weiterhin ruhiger Bewegung. |
| Kreisend, Richtung The Black Hole | **3/4** | **0,30 / 0,65 / 0,55**; ergänzend **0,30 / 0,50 / 0,40** | Gehaltenes Fundament, kreisende Oberfigur und mögliche Achtel-/Sechzehntelverdichtung. Im passenden Klangfeld kann die kurze M17-Geste auftreten. |
| Dramatisch / bewegt, Richtung A View to a Kill | 4/4 | **0,35 / 0,60 / 0,50**; ergänzend **0,30 / 0,75 / 0,70** | Synkopierte Bewegung bzw. gestufte Verdichtung, koordinierter Bass und Freiräume für Motive. Keine Rekonstruktion des Zorin-Motivs. |

Pro Kontext zunächst **64, besser 128 Takte** laufen lassen. Bei 120 BPM entsprechen
64/128 Takten in 4/4 etwa **2:08 / 4:16 Minuten**, in 3/4 **1:36 / 3:12 Minuten**.
Die Einführung allein zeigt weder Wiederkehr noch Varianten und Antwortverhalten.

### Neutral gegen John Barry

Gleiche Patches, Kanäle, XYZ, Tonart, Hosttempo/-takt, Wurf, Abwechslung und Schalter verwenden.
Eine Passage mit **Neutral** aufnehmen, stoppen, zum Anfang zurückkehren, **John Barry**
wählen und neu starten. Ein Neustart beginnt eine frische Szene mit neuem Motivgedächtnis.
Die automatische harmonische Auswahl eingeschaltet lassen. Unterschiedliche Wendungen,
Begleitfiguren und Motivgestalten sind beabsichtigt; Klangwechsel sind kein Stilnachweis.

### Mit und ohne Hauptmelodie

Jeden Kontext zuerst ohne Hauptmelodie hören. Danach stoppen, zum Anfang zurückkehren,
Hauptmelodie **Aktiv EIN**, **Motiv EIN**, **Legato EIN** und neu starten; Dialog-Motiv bleibt EIN.
Beide Zielspuren auf Kanal 8/9 müssen hörbar sein. Die Stimmen sollen sich abwechseln,
nicht gleichzeitig dauerhaft führen. Geplante Motive können das automatische Arp kurz pausieren lassen.

Zum Isolieren beide melodischen Rollen gemeinsam solo schalten; für reine Begleitung beide
muten. Anschließend Solo/Mute wieder lösen. Motiv AUS liefert vorhandene freie Linien statt
gezielter Wiederkehr. Legato EIN/AUS je Stimme getrennt vergleichen, jeweils mit Neustart.
Die kurze Melodie–Dialog-Antwort ist nicht in jeder Phrase vorgesehen und kann bei ungeeigneter
Harmonie ausbleiben; zum gezielten Vergleich **4/4, Aufbau AUS, beide Motivschalter EIN** lassen.

## Rückmeldung und Grenzen

Notieren: DEV-Commit, Kontext/XYZ, Taktart/Tempo, Wurf, Patches, aktive Rollen sowie Takt einer
Auffälligkeit. Besonders auf Wiedererkennbarkeit, unnötige Dichte, lange Blockaden und Übergänge achten.
Lange Sample-Releases/Hall können MIDI-Pausen überdecken. Ein kalter Einstieg mitten im Song
besitzt keine zuvor gespielte musikalische Vorgeschichte; erste Vergleiche deshalb am Anfang starten.

Nicht jede Forschungsvorlage ist bereits umgesetzt: Phase 3 nutzt 16 Rhythmus- und 20 kurze
Motivvorlagen. Lange Melodiebögen, komplexe Chromatik und Formdramaturgie bleiben ausgenommen.
Die konkreten Noten-/Rhythmusstudien sind Konstruktionen, keine Originaltranskriptionen.
Automatisierte Tests belegen MIDI-Korrektheit; musikalische Qualität und Stilwirkung sind Gegenstand
dieser Hörabnahme. Bis zu deren Ergebnis bleibt die Entwicklung gestoppt.
