# Harmonische Übergänge zwischen Score-Wendungen

Ausgangspunkt `be09fea`, Entwicklungsbranch `develop/composition-core-prototype`.
Keine Änderung an Katalog, XYZ-Auswahl, Profilgewichten oder GUI.

## Befund aus dem Code und der MIDI-Ausgabe

`Generator::prepareVoicingPlan()` baut bisher einen begrenzten zyklischen Plan pro
Wendung. `composition::planHarmony()` verwendet einen vorbereitenden und einen
abschließenden Umlauf. Dadurch ist eine Wendung in sich verbunden, ihre Anfangslage
bezieht sich jedoch auf ihren eigenen Schluss, nicht auf die zuvor tatsächlich gespielte
andere Wendung. `ensurePhrase()` und `maybeSwitch()` wechseln den harmonischen Vorrat,
übergeben aber keinen klingenden Kontext.

Bereits verwendbar sind `voiceleading::lead()`, `bass()`, `distance()` und `shapeCost()`:
begrenzte Kandidatensuche, vollständige Tonklassen, weiche Register-/Weitenkosten und
geordnete Stimmen. Der Bass erhält nur Oktavalternativen des vorgegebenen Basstons.
`padChord()` und die MIDI-Notenverwaltung halten gleiche Töne der langen Fläche bereits
über eine Akkordgrenze. Ein solcher Ton bleibt jedoch nur erhalten, wenn die neue Lage
auch dieselbe absolute Tonhöhe enthält.

Konkrete Referenzbeispiele (MIDI-Notennummern, Zeit ab Szenenbeginn, Takt 0 = Anfang):

| Neutraler Fall | Letzte tatsächliche Fläche | Bisheriger Eintritt | Neuer Eintritt |
|---|---|---|---|
| Hell, Takt 40, G7 → C | 62 65 79 83 | 55 72 76 | 60 64 79 |
| Hell, Takt 112, C → Cmaj7 | 60 67 76 | 59 64 72 79 | 60 67 71 76 |
| Lyrisch, Takt 88, F♯ → C | 66 73 82 | 60 67 76 | 64 72 79 |
| Unruhig, Takt 8, Bdim7 → Cmaj7 | 59 71 74 77 80 | 60 64 72 79 83 | unverändert |

Im ersten Beispiel bleibt G5 (79) erhalten, statt in einer anderen Oktave erneut
aufzutreten. Beim zweiten bleiben 60/67/76 erhalten; der Bass bleibt auf 48 statt einen
Oktavsprung 48→60 zu machen. Beim Tritonusbeispiel bewegen sich die drei geordneten
Stimmen statt −6/−6/−6 um −2/−1/−3 Halbtöne. Die Basstonbewegung −6 bleibt ausdrücklich
erhalten: der harmonische Kontrast wird nicht durch eine andere Basstonklasse ersetzt.
Der chromatische dim7-Kontrast wird nicht um jeden Preis geglättet.

Diese Beispiele zeigen vermeidbare Registerwechsel; sie belegen keine allgemeine
Stimmkreuzungsproblematik. Die Engine hat keine dauerhaften orchestralen Einzelstimmen.
Geordnete Tonlisten erlauben eine kreuzungsfreie Zuordnung; eine instrumentenspezifische
Stimmenidentität wird dadurch nicht erfunden. Bei unterschiedlicher Stimmenzahl gibt es
keine eindeutige Eins-zu-eins-Bewegung.

## Kleine gemeinsame Implementierung

- `composition::HarmonicEntry` enthält gespielte Flächenlage, optional gespielten Bass
  und die vorhandene Auflösungsabsicht. `leadEntry()` realisiert daraus einen Zielakkord
  mit den vorhandenen Voice-Leading-Funktionen. Keine eigene Profilengine.
- `Generator::HeardHarmony` wird aus akzeptierten Bassansprüchen in `noteOn()` und den
  tatsächlich vorhandenen Flächenansprüchen nach `padChord()` aktualisiert. Ein gemuteter
  oder nicht aktiver Ausgang liefert keinen erfundenen Satz. Kurze Artikulationen dürfen
  eine zuletzt gespielte Lage auch nach einer echten Pause als Bezug verwenden.
- Nur beim Wechsel zu einer **anderen vorhandenen Score-Wendung** wird dieser Kontext
  als Eintrittsbezug registriert. Wiederholungen derselben Wendung, eigene Folgen und
  Pop/Rock behalten ihren bisherigen Mechanismus.
- Die bisherige zyklische Planung bleibt Grundlage. Eine getrennte Eintrittslage ersetzt
  ausschließlich den ersten regulären Akkord ab `chordBase`, nicht die folgenden Akkorde,
  Durchgangsakkorde oder deren Walking-Anlaufziele.
- Eine begrenzte Gegenprüfung betrachtet den bereits geplanten Folgeakkord. Bewertet
  werden beide Anschlüsse, die ursprüngliche Lage/Weite und gemeinsame Töne. Eine neue
  Eintrittslage wird nur bei günstigerer Gesamtbewertung übernommen. Bassoktaven werden
  ebenso gegen den folgenden Basston geprüft. Der Folgeakkord selbst bleibt unverändert.
- Gemeinsame lange Töne werden über die vorhandene Notenbesitzverwaltung verlängert.
  Kurze Flächen artikulieren weiterhin neu; ein Orgelpunkt wird nicht umgedeutet.
  Tonarten, Oktavregler, Registergrenzen und vorhandene Farbakkorde gelten weiter.

Die Gegenprüfung ist nötig: ein zunächst ausschließlich rückwärts gerichteter Kandidat
konnte den Registersprung an die nächste Akkordgrenze verschieben. Der endgültige Test
protokolliert deshalb Eintritt **und** Anschluss. Die verwendete gewichtete Satzkostenmetrik
ist keine Garantie, dass jede andere Abstandsmetrik an jeder einzelnen Grenze sinkt.

## Transport und Grenzen des Gedächtnisses

Ein kleiner szenenlokaler Ring speichert die Quellkontexte der letzten **64 unterschiedlichen
Wendungsgrenzen**, jeweils mit Zeitpunkt und Zielwendung. Beim erneuten Besuch einer
bekannten Grenze wird deren Kontext verwendet, statt den vor dem Seek beliebig gehörten
Akkord als Vorgänger zu missbrauchen. Ein Seek leert den aktuellen Hörzustand; Neustart
und eine neue Szene leeren auch den Ring. Die Planung und der Ring benötigen keine
Speicherallokation im Audiothread.

Bei einem kalten Einstieg ohne bekannte Vorgeschichte oder einer aus dem Ring verdrängten
Grenze gilt der vorhandene zyklische Zielplan. Es wird keine vermeintlich tatsächlich
gehörte Vergangenheit rekonstruiert. Ein solcher Einstieg kann daher von einer zuvor
vollständig durchgespielten Szene abweichen. Die 64 Grenzen entsprechen nicht pauschal
512 Takten: Stimmungswechsel innerhalb einer Phrase können den Ring schneller füllen.
Es gibt weder eine unbegrenzte DAW-Automationshistorie noch einen neuen Szenen-Replayer.

Ein erneuter Besuch bekannter Grenzen verwendet die gespeicherte Ausgangslage; aktuelle
Zielharmonie und Registervorgaben werden weiterhin ausgewertet. Der Ring ist Performance-
Zustand und wird nicht als Plugin-Preset gespeichert. Live und Export stimmen bei identischem
Startzustand und denselben Einstellungen überein; Export startet wie bisher eine neue Szene.

## Reproduzierbare Vergleiche

`tools/transition_probe.cpp` rendert jeweils 128 Takte bei 120 BPM, 4/4 und 48 kHz.
`scripts/compare_transitions.py` baut temporär die tatsächlichen Header aus `be09fea`
und vergleicht 13 Fälle für alle drei Profile: stationäre dunkle, helle, unruhige und
lyrische XYZ-Punkte; dunkle/helle, chromatische und tritonusbezogene Feldwechsel;
eine XY-Fahrt; kurze Fläche/Walking-Bass; stummer Flächenausgang; Orgelpunkt sowie
Pop/Rock und eigene Folgen als vollständige Regressionen.

```sh
python3 scripts/compare_transitions.py --probe /pfad/TransitionProbe \
  --compiler c++ --output /tmp/stromscore-transitions
```

Die Matrix enthält 507 Wendungswechsel, davon 462 Score-Wechsel. Reale Halbton- und
Tritonus-Grundtonbeziehungen werden aus dem Verlauf nachgewiesen, nicht nur aus Fallnamen.
Auswahlzeitpunkte/-indizes und harmonische Diagnosen müssen identisch bleiben. Zu jedem
harmonischen MIDI-Ereignis werden die Tonklassen aller vier Harmonie-/Bassausgänge verglichen.
Sämtliche übrigen Ebenen und CC-Ereignisse müssen vollständig identisch sein. Gehaltene
gemeinsame Flächentöne dürfen nicht neu angeschlagen werden. Folgeakkorde bleiben
in ihrer konkreten Lage unverändert. Note-on/off-Besitz muss vollständig ausgeglichen sein.

| Profil (Score-Fälle) | Geänderte Flächeneintritte | Bewegung vorher → nachher | Gemeinsame Töne vorher → nachher |
|---|---:|---:|---:|
| Neutral | 29 | 2914 → 2466 | 97 → 148 |
| John Barry | 31 | 2743 → 2288 | 112 → 162 |
| Bernard Herrmann | 33 | 2801 → 2334 | 114 → 164 |

Die Bewegungsmetrik summiert den nächsten Abstand je Ton in beide Richtungen; sie ist
keine vollständige Zuordnung orchestraler Einzelstimmen. Einschließlich Anschluss an
den Folgeakkord beträgt sie für Neutral 4654→4399, Barry 4467→4185, Herrmann 4502→4226.
Einzelne Anschlüsse können größere Bewegung behalten; ein harmonisch gewollter Sprung
ist zulässig. Insgesamt ändern sich 23 Bass-Eintritte durch eine andere Oktavlage,
nicht durch andere Basstonklassen. Die beobachteten Flächenweiten reichen vorher von
12 bis 28, nachher von 12 bis 31 Halbtönen; die Palette wird nicht auf enge Lagen reduziert.
Das ist ein begrenzter Messbefund, keine allgemeine Garantie gegen musikalische Monotonie.

Die kompakte Auswertung und vier vollständige Beispiele stehen in
`WENDUNG_TRANSITIONS_COMPARISON.json`. Die vollständigen 507 Einzelmessungen mit
Lagen, gemeinsamen Tönen, geordneten Halbtonbewegungen (nur bei gleicher Stimmenzahl),
Bassschritten und Folgeakkordkosten werden als `entries.json` erzeugt. CSV und importierbare
Vorher-/Nachher-MIDI-Dateien liegen lokal unter `/workspace/work/transition-comparison`.
Die beiden Dateien eines Falls mit denselben Patches und Lautstärken vergleichen,
zuerst Fläche/Bass isoliert, dann das Arrangement. Ein 128-Takt-Vergleich dauert 4:16 Minuten.

## Tests und musikalische Einordnung

Die separaten `TransitionTests` prüfen Akkordfarben, Basstonklassen, Register,
geordnete Stimmen, negative interne Register bei Oktavversatz, Vermeidung bloß
verschobener Sprünge, Mute ohne fiktive Quelle, wiederholte Seeks/Loops auf bekannte
Grenzen, kalten Einstieg, Reset und Allokationsfreiheit. Die Vergleichsmatrix prüft
512 gegen 127 und 8192 Samples. Die bestehenden Motiv-, Phrasen-, Dichte-, Begleit-,
Voice-Leading- und Profiltests bleiben Bestandteil der Gesamtsuite. Der echte
Processor-Test prüft Live-/SMF-Gleichheit einschließlich beider Künstlerprofile bis
zur bestehenden Exportgrenze von 64 Takten.

Die neue Logik ist eine begrenzte Übergangsstimmführung, keine Orchestrierungsengine.
Sie plant keine Übergangsakkorde, ändert keine Auflösungsregeln und verspricht keine
vollständige instrumentenspezifische Stimmverteilung. Bereits bestehende Einschränkungen
extrem enger Tonumfänge, unbekannter externer Patches und geteilter MIDI-Kanäle bleiben.
**Eine musikalische Qualitätsbewertung ist ohne Hörtest ausdrücklich vorläufig.**


Abschließend bestanden: 13/13 Kern-/Vergleichstests, 1/1 Processor-Test,
3/3 ASan-/UBSan-Läufe (TransitionTests, CompositionCoreTests, EngineTests) und
7/7 Release-/Paketprüfungen. Darin enthalten sind 39 Vorher-/Nachher-Paare über je
128 Takte und 78 zusätzliche Blockgrößenvergleiche dieses Übergangsschritts.
Es wurde weder ein Release erzeugt noch gepusht.
