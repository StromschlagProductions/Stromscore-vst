# Erste musikalische Phrasenplanung der freien Gegenstimme

Ausgangspunkt: `0cc30c2`, Branch `develop/composition-core-prototype`.

## Bestandsaufnahme und Begrenzung

Die bisherige freie Score-Gegenstimme wird in `counterLine()` pro Akkordwechsel und
gegebenenfalls innerhalb des Akkords lokal weitergeführt. Unter Ebenenintensität 0,4
entsteht regulär nur am Akkordwechsel ein neuer Zielton; bis 0,7 alle zwei Takte, darüber
alle halben Takte (mindestens eine Viertel). `counterTarget()` bevorzugt Nähe, vermeidet
teilweise Wiederholung/Grundton und berücksichtigt leicht die Färbungsrichtung. Die
Kommentare versprechen Terz-/Septimpräferenz, die alte Kostenfunktion bewertet sie nicht
explizit. Bei Unruhe kommen obere Vorhalte mit einer Viertel bis zur Auflösung hinzu.

Mit Legato schließen die Gates nahezu lückenlos aneinander an bzw. überlappen kurz.
Damit kann ein tatsächlicher zusammenhängender Spielabschnitt den ganzen Akkordraum
belegen, etwa acht Takte auf einem einzelnen Akkord; eine generelle Atempause fehlt.
Akkordwechsel, Wendungs-/Phrasengrenzen sowie Szenenbeginn und geplante Ebenen-Ausgänge
sind schon vorhanden. Das Acht-Takt-Wendungsraster ist keine eigenständige melodische
Phrasierung. Motive und Antworten haben dagegen eigene eng definierte Zeitfenster.

Verwendbar sind `Pos` mit Akkord-/Phrasenbeginn und -ende, `sceneStep`, `wendungStart`,
`Meter`, Range/Oktave, der Fähigkeitskatalog sowie die vorhandene Szenen-Ein-/Ausstiegs-
Reihenfolge. `VoiceState.note` und `pendingAt` sind für lokale Linie/Vorhalt vorhanden,
werden aber nicht benötigt, um die neue Kontur zu bestimmen.

Der neue Pfad gilt nur für **Score, Gegenstimme aktiv, Gegenstimme Motiv AUS und keine
aktive führende Hauptmelodie**. Die Hauptmelodie, gespeicherte Motive einschließlich
Einführung/Wiederkehr/Variation und beide Antwortverfahren werden nicht umgestaltet.
Bei nicht geeigneten Regionen bleibt die bisherige lokale Gegenstimme erhalten.

## Planung und Ausgabe

`LinePhraseRequest`, `LinePhrasePlan`, `PhraseEnding` und `planLinePhrase()` in
`CompositionCore.h` beschreiben einen kleinen musikalischen Gedanken ohne MIDI-Kanal.
`Generator::freeLinePhrase()` liefert dafür die aktuellen harmonischen Daten.

- Ein Gedanke belegt eine tatsächliche harmonische Region, begrenzt durch Akkordwechsel,
  Wendungs-/Phrasenwechsel, Szenenstart und geplanten Szenen-/Ebenenausstieg. Der Aufbau
  berücksichtigt den bereits vorgesehenen Einsatz der Gegenstimme. Es wird kein neues
  Zwei-/Vier-Takt-Raster eingeführt und kein neuer Formzustand aufgebaut.
- Der Zielton wird vor Ausgabe aus passenden Akkordtönen im Register bestimmt. Ein Ende
  auf dem Grundakkord am Phrasenende kann Grundton oder bei heller Färbung Terz ansteuern.
  Offene Regionen bevorzugen je nach Färbung und Unruhe Terz, Quinte oder Septime.
  Die Kennzeichnung offen/gefestigt ist eine kompositorische Absicht, kein Beweis für
  eine subjektiv geschlossene Wirkung.
- Aus Richtung und verfügbaren Akkordtönen entsteht eine kurze monotone Kontur zum Ziel.
  Dunkle Färbung bevorzugt Abwärts-, helle Aufwärtsbewegung. Wenn dafür der Platz fehlt,
  wird die andere Richtung gewählt. Der vorletzte harmonische Ton liegt auf der
  benachbarten Stufe der Akkordtonleiter zum Ziel; er wird nicht erneut lokal ausgewürfelt.
- Es gibt höchstens vier harmonische Stationen, bei hoher Unruhe optional einen
  vorgeschalteten oberen Nachbarton mit Auflösung. Niedrige Intensität bevorzugt drei,
  hohe bis zu vier Stationen; Register und Länge können die Zahl weiter begrenzen.
- Die Einsätze verteilen sich im metrischen Puls über die verfügbare Region. Die Zielnote
  erreicht den Schluss vor der letzten Pulsgruppe; diese letzte Gruppe ist Atempause.
  In 4/4 ist das eine Viertel. Die Pause liegt nach dem Ziel und vor dem nächsten Abschnitt.
- Legato darf intern eine Sechzehntel überlappen (höchstens zwei gleichzeitige Töne),
  getrennte Artikulation lässt Abstand. Das Schlussgate endet in beiden Fällen exakt
  vor der Atempause. Laufende andere MIDI-Ansprüche werden weiterhin aggregiert.

Weniger als drei verfügbare Akkordtöne oder weniger als vier Pulse Länge führen zum
lokalen bisherigen Verfahren, nicht zum Verstummen. Kurze Durchgangsregionen bleiben
so erhalten. `freePhraseStep()` erzeugt die MIDI-Noten mit der bestehenden Energie und
Notenverwaltung. Dichtemaske und Motiv-/Arp-Koordination bleiben unberührt.

Es gibt keinen zusätzlichen musikalischen Zufallszustand oder geteilten Phrasencursor.
Der Plan wird aus Region und aktuellen Einstellungen rekonstruiert. Seek innerhalb einer
laufenden Szene kann die im Plan bereits klingenden Töne übernehmen; in der Atempause
wird keine neue Note erfunden. Ein expliziter Neustart folgt weiter den Szenenregeln.
`inspectFreePhrase()` ist eine schreibfreie Offline-Diagnose auf einer Momentaufnahme des
vorbereiteten Generators und wird nicht im Audiopfad zur Diagnose aufgerufen.

## Reproduzierbarer Nachweis

`tools/phrase_probe.cpp` rendert die vollständigen MIDI-/CC-Ereignisse und protokolliert
harmonische Zustände, Motividentitäten und die tatsächlich berechneten Phrasenpläne.
`scripts/compare_phrases.py` baut den Ausgangsstand `0cc30c2` temporär zum Vergleich.
Kein zweiter Generator wird in das Plugin eingebaut.

```sh
python3 scripts/compare_phrases.py --probe /pfad/zum/Build/PhraseProbe \
  --compiler c++ --output /tmp/stromscore-phrases
```

Die Matrix umfasst 29 Situationen für jeweils Neutral, Barry und Herrmann: gehaltene und
wechselnde Harmonik, dunkle/helle Färbung, niedrige/hohe Intensität und Unruhe, enge Register,
Oktave, Stillstand, kurze/ungleiche Regionen, Szenenaufbau/-ausstieg, Legato AUS sowie die
unveränderten Motiv-, Antwort-, Hauptmelodie- und Pop/Rock-Kontexte. Je 48 Sekunden bei
48 kHz und 120 BPM; zusätzlich 127 und 8192 statt 512 Samples pro Block.

Gegen den Ausgangsstand müssen Harmonie-/Wendungsdiagnosen, Motividentitäten und alle
Ereignisse anderer Ausgänge übereinstimmen. Geschützte Kontexte werden vollständig
bytegleich verglichen. Für jede protokollierte freie Phrase stimmen tatsächliche
Anschläge mit ihrem vorab berechneten Plan überein, die Zielnote wird erreicht und in der
Atempause klingt keine Gegenstimmennote weiter. Sinkende Anschlagszahl und tatsächliche
klingende Zeit werden getrennt gezählt. Die Prüfung weist außerdem mehrere verschiedene
Schlussintervalle nach und darf keine zuvor aktive Stimme vollständig verlieren.

Der historische Stimmführungstest gegen v1.9 hält weiterhin Arpeggio und Akzente fest;
die jetzt bewusst veränderte freie Score-Gegenstimme wird dort nicht mehr als identischer
v1.9-Ausgang vorausgesetzt. Pop/Rock bleibt im Vergleich enthalten. Gleichzeitige
Ereignisse anderer Kanäle werden für diesen historischen Vergleich sortiert, weil weniger
Gegenstimmen-Ansprüche die Freigabereihenfolge im kompakten Notenarray ändern können.
Die exakte Blockdeterministik wird unabhängig weiterhin unsortiert geprüft.

## Bewertung und Grenzen

Es gibt jetzt ein nachweisbares gemeinsames Ziel, eine dazu passende Kontur und eine echte
Schlusspause. Das ist mehr als eine weitere lokale Bewertungszahl. Ob die Ergebnisse
musikalisch überzeugender sind, erfordert einen Hörvergleich.

Die Logik bleibt bewusst schematisch: wenige Stationen und eine letzte Pulsgruppe Pause,
je harmonischer Region. Bei einer immer gleichen kurzen Akkordfolge kann dieselbe
Schlussfigur wiederkehren. Sie besitzt weder ein Gedächtnis für freie Phrasen noch eine
Langzeitentwicklung, keine Melodieplanung über mehrere Akkorde und keine stilabhängigen
Phrasenregeln. Bei kurzen Regionen ist der Pausenanteil deutlich größer. Die vorhandenen
Musikprofile verwenden dieselbe Regel, nicht eigene Engines.

Für lange gehaltene Harmonik sinkt insbesondere bei hoher Intensität die Zahl neuer
Anschläge deutlich. Das ist keine pauschale Stummschaltung: die Töne werden überwiegend
länger gehalten. Bei niedriger Intensität können zusätzliche Töne entstehen, um erstmals
einen Gedanken zum Ziel zu führen. Beides ist eine bewusste hörbare Änderung der freien
Gegenstimme und sollte praktisch abgenommen werden.

Hörtest: Score, Melodie AUS, Gegenstimme hörbar, Gegenstimme Motiv AUS. Mindestens eine
vollständige Wendung hören, für Wiederholungsverhalten mehrere Wendungen. Kein neuer
GUI-Regler wurde ergänzt.

## Konkrete Beispiele und Zahlen

Alle folgenden Beispiele: Neutral, C als Tonart, 4/4, getrennte Standardkanäle.
Oktavbezeichnungen verwenden MIDI 60 = C4, deutsches H = MIDI 71. Die Zeiten sind
Viertel ab Beginn des Gedankens, keine zusätzlichen Formvorgaben.

| Kontext | Geplant und tatsächlich gespielt | Ziel / Pause |
|---|---|---|
| Cmaj7, acht Takte, niedrige Intensität | E4 bei 0, H4 bei 15, C5 bei 30 | C5; Pause Viertel 31–32 |
| Cmaj7, acht Takte, hohe Intensität | E4 bei 0, G4 bei 10, H4 bei 20, C5 bei 30 | C5; Pause 31–32 |
| Cmaj7, hell, hohe Intensität | G4 bei 0, H4 bei 10, C5 bei 20, E5 bei 30 | Terz E5; Pause 31–32 |
| Cm(maj9), dunkel | Es5 bei 0, D5 bei 15, C5 bei 30 | C5; Pause 31–32 |
| Erster Cmaj7 in Folge mit 1/3/2/2 Takten | C5 bei 0, G4 bei 1, E4 bei 2 | offenes E4; Pause 3–4 |
| Cmaj7, hohe Unruhe | F4 bei 0, E4 bei 1, G4 bei 10, H4 bei 20, C5 bei 30 | früher Vorhalt, C5; Pause 31–32 |

Die alte lokale Linie auf acht Takte Cmaj7 hielt bei niedriger Intensität nur G4. Bei
hoher Intensität wiederholte sie zunächst G4 und später E4 auf der bisherigen Halbtakt-
Rate, ohne gemeinsame Zielnote oder Schlusslücke. Hell oszillierte sie häufig H4/C5.
Die neue Kontur führt dagegen nachweislich zu dem bereits vor Ausgabe bestimmten Ziel.

Auswahl der Anschlagszahlen und klingenden Zeit über 48 Sekunden:

| Fall | Anschläge bisher → neu | Klingender Anteil bisher → neu |
|---|---:|---:|
| held-low | 3 → 9 | 100.0 % → 96.9 % |
| held-high | 48 → 12 | 100.0 % → 96.9 % |
| changes-high | 48 → 42 | 100.0 % → 87.5 % |
| changes-low | 12 → 36 | 100.0 % → 87.5 % |
| one-bar | 48 → 72 | 100.0 % → 75.0 % |
| buildup-fade | 32 → 8 | 66.7 % → 64.6 % |
| motif-protected | 8 → 8 | 16.7 % → 16.7 % |
| dialogue-arp-protected | 8 → 8 | 16.7 % → 16.7 % |
| pop-protected | 192 → 192 | 100.0 % → 100.0 % |

Kein zuvor klingender Testfall verstummt vollständig. Die eintaktige Ein-Akkord-Folge
zeigt mit 25 % Pause den stärksten regelmäßigen Atemanteil; hier ist die Gefahr eines
zusätzlichen Schemas besonders klar. Die geschützten Fälle bleiben unverändert.
`FREE_LINE_PHRASE_COMPARISON.json` enthält die kompakte Matrix einschließlich Prüfsummen
und neutralen Noten-/Planbeispielen; die vollständigen CSVs und ausführlichen Pläne werden
vom Vergleichsskript erzeugt.

## Abschließende Validierung

- 87 Vergleiche gegen `0cc30c2` und 174 zusätzliche Blockgrößenvergleiche bestanden.
- 10/10 Kern-CTest-Prüfungen bestanden, einschließlich Phrasen-, Dichte- und Begleitvergleich.
- Linux/Xvfb-Processor-Prüfung 1/1 bestanden; freie Gegenstimme mit Motiv AUS sowie
  Aufbau/Ausklang stimmen zwischen Live-Ausgabe und echtem MIDI-Dateiexport einschließlich CC überein.
- ASan/UBSan für CompositionCore, Policy und Engine: 3/3 bestanden.
- Python-Paketprüfer: 7/7 bestanden.
- Keine neue Windows-/pluginval-Prüfung und keine subjektive Hörabnahme.

Alle Fälle mit zuvor aktiver Gegenstimme behalten Gegenstimmenereignisse. Bei gleicher
Harmonie und gleicher Einstellung bleibt die Kontur deterministisch und kann sich wiederholen;
das Verfahren beweist keine allgemeine musikalische Qualitätssteigerung. Es ist ein kleiner
Ziel-/Kontur-/Atemplan, keine vollständige Melodie- oder Formgrammatik.

Kein Push, kein Release.
