# Flexible, materialgebundene Motivwiederkehr

Ausgangspunkt: `920d388`, Branch `develop/composition-core-prototype`.

## Befund

`MotifUse::recall()` ließ nach der Einführung nur jede zweite native Phrase zu;
`varied()` benutzte deren Modulo-4-Position. `motifStep()` beschränkte die Figur auf den
Phrasenanfang. Bei achtaktigen Score-Wendungen bedeutete das typischerweise zwei Takte
Motiv und vierzehn Takte ohne dieses Motiv. Hohe Intensität verkürzte diese Pause nicht.
Bei eigenen ein-, vier- oder sechzehntaktigen Akkordzyklen entstanden dagegen Abstände
von zwei, acht oder zweiunddreißig Takten. Die Tabellenlänge bestimmte somit unbeabsichtigt
auch die motivische Präsenz. Arp-Reservierung und Dialogantworten hatten eigene Kopien
beziehungsweise Ableitungen dieses Rasters.

Diese festen `recall`-/`varied`-Entscheidungen sind entfernt. Katalog, Motivaufnahme,
Intervall-/Rhythmusrepräsentation und die vorhandene Dauervariation bleiben gemeinsam.

## Daten und Policy

`FreeCompositionPolicy::motif` enthält eine typisierte `MotifRecurrencePolicy`:

| Parameter | Neutrale Vorgabe | Wirkung |
|---|---|---|
| `minimumSilentBars` | 2 | Mindestpause nach einer vollständigen Figur |
| `sparseBelow` | 0,4 | Grenze zur zurückhaltenden Strategie, mit Ebenenintensität |
| `unrestEngages` | 0,5 | Unruhe kann auch bei niedriger Intensität die bewegtere Strategie wählen |
| `sparseSteps` | 2, 2, 2 | Große, gleichmäßige Abstände in konstant ruhigen Kontexten |
| `normalSteps` | 1, 2, 1 | Wechselnde kürzere/längere Abstände in bewegteren Kontexten |

Die Schritte beziehen sich auf begrenzte **achtaktige Planungshorizonte**, nicht auf die
Länge der Akkordtabelle. Diese technische Horizontgröße ist in diesem Schritt konstant;
sie ist keine neue GUI-/Profil-Einstellung. Innerhalb eines Horizonts kann der Einsatz an
einer anderen harmonisch passenden Stelle liegen. Ein Horizont erzwingt keine Wiederkehr.

Neutral, John Barry und Bernard Herrmann verweisen auf dieselbe neutrale Policy.
`StromscoreProcessor::currentSettings()` übernimmt jetzt die Policy der bestehenden
Profilregistry, sodass spätere unterschiedliche Daten auch den realen Live-/Exportpfad
erreichen. Es gibt weder neue Künstlergewichte noch eine zusätzliche Engine.

## Zeitliche und harmonische Planung

`recurrenceSlot()` erzeugt begrenzte Gelegenheiten aus Kontext und Policy. `planRecurrence()`
wählt daraus eine vollständige spielbare Platzierung. `MotifOccurrence` beschreibt Beginn,
Ende, Transposition, Einführungs-/Wiederkehrstatus und die bestehende Variationsphase.

- Kandidaten liegen an harmonischen Grenzen oder im Inneren eines länger gehaltenen
  Akkordfelds. Nach einer ausgelassenen Gelegenheit wird eine frühe Rückkehr bevorzugt.
  Ein späterer Einsatz ist am Ende einer Folge aufeinanderfolgender Gelegenheiten möglich.
- Jeder Kandidat prüft das **tatsächlich gespeicherte** Material. Eine gemeinsame
  Transposition muss alle Intervalle erhalten und in die aktuelle Harmonie sowie das
  zulässige Register passen. Notendauern und vorhandene Instrumentenannahmen werden geprüft.
  Legato-Überhänge der Gegenstimme bis zum nächsten Anschlag dürfen wie bisher kurz binden.
- Wenn keine vollständige passende Platzierung existiert, entfällt die Wiederkehr.
  Es werden keine Intervalle auf einen einzigen verfügbaren Ton zusammengefaltet und
  keine neue Harmonie erzwungen. Die Hinzufügung eines anderen Motivgenerators entfällt.
- Das gesamte aufgenommene Zeitmaterial wird verwendet; seine Länge wird bei der
  Wiederkehr nicht aus der nativen Tabellen-/Phrasenlänge neu abgeleitet.
- Das Fenster wird so begrenzt, dass zwischen vollständigen Figuren mindestens zwei
  Takte frei bleiben. Geplante Szenen-/Ebenenausstiege werden berücksichtigt.
- Die zweite geplante Wiederkehr nutzt die schon vorhandene Dauervariation, danach
  alterniert diese Phase weiter. Es entsteht keine zusätzliche Variationsform.

`MotifUse::originTick` verankert den aufgenommenen Materialzeitursprung in absoluter
musikalischer Zeit. Der relative Einsatz der tatsächlich beobachteten Noten bleibt im
Material gespeichert. `motifHarmonyAt()` betrachtet die vorhandene harmonische Zeitlinie
auch über Grenzen wiederholter eigener Akkordzyklen hinweg, ohne vom aktuellen
Generatorcursor abhängig zu sein.

Jede Spielspur besitzt ihren eigenen kleinen Cache für den aktuellen Planungshorizont,
gebunden an Materialidentität, Materialzeitursprung und musikalische Fensterlänge. Der
Plan bleibt innerhalb dieses Horizonts gelatcht; keine gemeinsame Wiederkehrzählung oder
geteilte Linienposition wird eingeführt. Motive werden weiterhin nur nach tatsächlich
emittierten Einführungsnoten veröffentlicht, nicht aus einer neuen Zufallszahl erfunden.

## Antworten und Arpeggio

`primaryMotifWindow()` und `motifStep()` verwenden denselben Wiederkehrplan und dieselbe
Notenberechnung. Der automatische Arp unterdrückt neue Anschläge im tatsächlich geplanten
Motivfenster. Bereits klingende Arp-Noten werden wie bisher nicht abgeschnitten; die
bestehende Ausnahme für geteilte Arp-MIDI-Kanäle bleibt erhalten.

Die Dialog–Arp-Funktion richtet ihr Frage-/Antwortfenster nach dem geplanten Frageeinsatz
aus. Für eine anschließende Antwort wird zusätzlicher Raum reserviert. Ohne geplante
Frage wird kein leeres Antwortfenster erzwungen. Eine unbekannte/unvollständige Frage
kann nach einem Seek keine erfundene Antwort auslösen.

Die Melodie–Dialog-Übergabe erhält weiterhin nur eine kurze Schlussfigur desselben
Katalogmaterials. Sie liegt in einer geeigneten nichtführenden Gelegenheit und bleibt
auf höchstens eine Antwort pro vier Planungshorizonte begrenzt. Mit der neutralen
bewegteren Strategie verschieben sich die Antwortfenster: die frühere Antwortgelegenheit
nach der Einführung kann nun selbst eine führende Wiederkehr enthalten. Beide werden
nicht übereinandergelegt.

Bei bekannten Motiven rekonstruiert `chaseMotif()` nach Seek die laut Plan bereits
klingenden Noten; auch beide bestehenden Antwortformen können ihre laufenden Töne
wiederaufnehmen. Die ursprünglichen Notenendpunkte bleiben bestehen. Ohne abgeschlossene
Aufnahme wird keine Vergangenheit erfunden. Neustart löscht weiterhin Szenenkatalog und
Stimmenzustände; Loop verwendet den bekannten musikalischen Zeitplan.

## Reproduzierbare Prüfung

`tools/recurrence_probe.cpp` und `scripts/compare_recurrence.py` vergleichen gegen den
wirklichen Ausgangsstand `920d388`, der temporär gebaut wird. Kein Referenzgenerator wird
in das Plugin eingebaut. Die Matrix umfasst **26 Situationen × 3 Profile**, jeweils
**128 Takte**, 4/4, 120 BPM, 48 kHz. Unterschiedliche XYZ-Punkte, wechselnde Harmonik,
Katalogauswahl, kurze/lange eigene Zyklen, Antwortkontexte, Instrumenten-Unverfügbarkeit,
Aufbau/Ende, unabhängige Stimmen, Seek/Loop und Neustart sind enthalten.

```sh
python3 scripts/compare_recurrence.py --probe /pfad/zum/Build/RecurrenceProbe \
  --compiler c++ --output /tmp/stromscore-recurrence
```

Für jede vollständige Wiederkehr werden sämtliche tatsächlichen Anschläge gegen die
aufgenommenen relativen Einsätze und Intervalle geprüft. Nur die bisherige Dauervariation
ist erlaubt. Die tatsächlichen Aufnahmeidentitäten und die harmonischen Diagnosen müssen
mit dem Ausgangsstand übereinstimmen. Arp-Anschläge dürfen nicht in reservierte aktive
Motivfenster fallen; führende Melodie und Dialogantwort dürfen nicht konkurrieren.
Notenbesitz und vollständige Freigaben werden überprüft.

512 Samples werden mit 127 und 8192 Samples verglichen, einschließlich der diagnostizierten
Pläne. Pop/Rock und Motiv AUS bleiben vollständig bytegleich; auch eine ausdrücklich
konfigurierte gleichmäßige Strategie und der ruhige gehaltene Referenzkontext werden
bytegleich gegen den Ausgangsstand geprüft. Ein eigenständiger Engine-Test überprüft
Standardabstände, exakte Intervalle und Speicherallokationsfreiheit ohne Git-Referenz.

Zusätzliche Transporttests springen mitten in gehaltene Motive und beide Antwortformen.
Ein Motivschluss muss nach Seek zum ursprünglichen Endzeitpunkt loslassen, nicht erneut
seine volle Länge ab dem Seek spielen. Unabhängige Stimmen und gemeinsame Referenzen
werden weiterhin getrennt geprüft.

Historische Vergleichstests schützen weiterhin ihre jeweiligen unveränderten Mechanismen;
ihre früher fest angenommenen Wiederkehrzeitpunkte sind kein Sollwert mehr. Bestehende
Identitäts-/Variationsfixtures benutzen ausdrücklich eine konfigurierte gleichmäßige
Policy über denselben neuen Planer. Die neue neutrale Standardstrategie wird separat über
128 Takte geprüft, nicht durch ein eingefrorenes altes Raster ersetzt.

## Grenzen und musikalische Bewertung

Die Strategie ist ein kleiner Planer mit begrenzten Gelegenheiten, keine Formgrammatik.
Konstante Harmonie und gleichbleibender Kontext können weiterhin ähnliche Abstandsfolgen
ergeben. Die ruhige Strategie darf bewusst regelmäßig bleiben. Eine subjektive Aussage,
ob die neue Wiederkehr musikalisch überzeugender ist, benötigt einen Hörvergleich.

Die Mindestpause ist eine Untergrenze, kein garantiertes Wiederkehrdatum. Bei ungeeigneter
Harmonie, nicht verfügbarem Register oder deaktivierten Rollen kann es längere Pausen geben;
es werden keine ungeeigneten Noten erzwungen. Die Variationsphase zählt geplante Gelegenheiten,
nicht nachträglich rekonstruierte erfolgreiche Aufführungen.

Der Plan wird mit dem jeweils bekannten harmonischen Kontext gelatcht. Eine vollständige
historische Rekonstruktion beliebiger Live-Automation ist nicht Bestandteil dieses Schritts.
Die Tests decken feste Einstellungen, definierte Steuerverläufe und reproduzierbare
Transportsprünge ab. Externe Patchfähigkeiten werden weiterhin nicht automatisch erkannt.

Weniger Motive geben dem bisherigen Arp mehr freie Zeit; mehr Motive reservieren entsprechend
mehr Raum. Es gibt keinen zusätzlichen Ausgleich der Gesamtdichte. Besonders bei sehr kurzen
Akkordzyklen kann daher weniger motivische Schleife mit mehr gewöhnlicher Begleitung einhergehen.
Die vorhandene Ereignisdichte-Maske und die Instrumenten-/Routingstruktur bleiben erhalten.

Alle Testzeiten verstehen sich als **Takte seit Szenenbeginn**, mit 0 als Anfang. Ein Takt
zählt als motivisch aktiv, sobald ein Teil einer tatsächlich klingenden Motivnote hineinragt;
das ist keine Gleichsetzung mit durchgehender klingender Zeit oder Hook-Linien in Pop/Rock.


## Messergebnisse (128 Takte)

| Neutraler Testfall | Aktive Motivtakte vorher | Nachher | Anteil nachher |
|---|---:|---:|---:|
| quiet | 16 | 16 | 12.500 % |
| active | 16 | 24 | 18.750 % |
| changes | 16 | 24 | 18.750 % |
| catalog | 16 | 24 | 18.750 % |
| one-bar-cycle | 64 | 12 | 9.375 % |
| four-bar-cycle | 32 | 24 | 18.750 % |
| long-cycle | 8 | 24 | 18.750 % |
| melody-handoff | 16 | 24 | 18.750 % |
| range-unavailable | 16 | 14 | 10.938 % |

Im bewegteren gehaltenen Referenzfall liegt die Einführung bei Takt 0, die Wiederkehr bei
8, 24, 32, 43, 56, 64, 72, 88, 96, 107 und 120. Die Abstände sind damit 8/16/8/11/13/8/8/16/8/11/13
Takte. Bei wechselnder Harmonie verschieben sich die inneren Einsätze auf 44 und 108;
im ruhigen Referenzfall bleiben die Einsätze bei 0/16/32/48/64/80/96/112 vollständig erhalten.
Die Materialidentitäten, aufgenommenen Intervalle und relativen Einsätze bleiben geprüft.

Bei Melodie–Dialog entstehen vier kurze Antworten (insgesamt zwölf Dialog-Anschläge),
keine zusätzliche vollständige Themenwiederholung. Der Auto-Arp hat im bewegteren
Referenzfall 1664 statt 1792 Anschläge, im ruhigen unverändert 911. Im Dialog–Arp-Kontext
sind es dagegen 1316 statt 1048: bisher reservierte leere Fragehorizonte stehen wieder
für gewöhnliche Begleitung zur Verfügung. Das ist keine pauschale Verdichtung oder
Ausdünnung aller Ausgänge.

Die vollständigen Messwerte einschließlich aller drei Profile, Einführungs-/Wiederkehrzeiten,
Abstände, Material-IDs und MIDI-Prüfsummen stehen in `MOTIF_RECURRENCE_COMPARISON.json`.
Pop/Rock und Motiv AUS enthalten freie beziehungsweise Hook-Linien; deren aktive Takte
sind ausdrücklich keine Kennzahl gespeicherter Motivwiederkehr. Transportfälle enthalten
Zeitversetzungen und dürfen ebenfalls nicht als normale Abstandsstatistik gelesen werden.

Die erzeugten CSV-Dateien, Plan-Diagnosen und importierbaren Vorher-/Nachher-MIDI-Dateien
liegen außerhalb des Repositorys in `/workspace/work/recurrence-comparison`. Jeder
Referenzfall enthält 128 Takte bei 120 BPM (4 Minuten 16 Sekunden). Kanal 5 ist Arp,
Kanal 8 Dialog, Kanal 9 Melodie. Die Datei `active-before.mid` lässt sich unmittelbar
gegen `active-after.mid` mit identischen Instrumenten vergleichen.

Der vorhandene Plugin-Dateiexport bleibt auf 64 Takte begrenzt. Der echte Processor-Test
vergleicht deshalb Live-Ausgabe und SMF über bis zu 64 Takte, einschließlich zwei
Melodie–Dialog-Antworten (sechs Anschläge). Die separaten Kern-/Referenzrenderings laufen
über die geforderten 128 Takte; die Exportbegrenzung wurde nicht als zusätzliche Funktion
verändert.


## Abschließende Tests

- 11/11 Kern-/Vergleichstests, darunter 78 Vorher-/Nachher-Paare über je 128 Takte und
  156 zusätzliche Vergleiche mit anderen Blockgrößen.
- ASan/UBSan: CompositionCoreTests, PolicyTests und EngineTests erfolgreich (3/3).
- Release-/Paketprüfungen: 7/7 erfolgreich. Es wurde kein Release erzeugt.
- Processor-Live-/SMF-Prüfung: 1/1 erfolgreich; maximale Vergleichslänge ist die
  bestehende Exportgrenze von 64 Takten.
