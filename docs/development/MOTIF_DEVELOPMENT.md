# Motivische Weiterentwicklung

Basis: `0b9281a`, `develop/composition-core-prototype`.

## Bestandsaufnahme

Der gemeinsame `MotifCatalog` speichert zwei unveränderliche tatsächlich aufgenommene
Motive. `MotifUse` hält getrennte Materialreferenzen und Zeitursprünge pro Stimme.
Die Identität umfasst Intervalle, relative Einsätze und aufgenommene Dauern. Der
Generator passt vollständige Wiederkehren durch eine gemeinsame Transposition an
Harmonie und Register an; er erzeugt sie nicht aus einer neuen Zufallszahl.

Bisher vorhanden: `RememberedMotif::recalledLength()` kürzt die längste Note auf die
Hälfte und begrenzt Überhänge vor dem nächsten Anschlag. Das ist eine rhythmische
Artikulationsvariation, keine neue Einsatzrhythmik. Die bisherige harmonische
Transposition ist noch keine Sequenzierung innerhalb einer Figur. Eine kurze
Schlussfigur existiert in der expliziten Melodie–Dialog-Antwort; eine solche Figur
als eigenständige Wiederkehr sowie Augmentation fehlten.

## Kleine, getrennte Ableitungen

`composition::MotifFigure` enthält ausschließlich eine abgeleitete Spielfigur:
Quellidentität, typisiertes Verfahren, Noten, Anzahl und tatsächlichen Zeitbedarf.
`deriveMotif()` nimmt immer das unveränderte Original entgegen. Kein Katalogmaterial
wird überschrieben und keine Variante zum Ausgangspunkt der nächsten gemacht.

- **Unverändert:** ursprüngliche Intervallfolge, Einsätze und gespeicherte Dauern.
- **Rhythmus:** die vorhandene Kürzung der längsten Note; Einsatzfolge und Intervalle
  bleiben erhalten. Vorhandene Legatoüberhänge werden wie bisher begrenzt.
- **Fragment:** die letzten zwei bis drei Töne (höchstens Originalanzahl minus eins),
  relativ zum ersten Fragmentton zeitlich auf null gesetzt. Ein zweitöniges Original
  liefert kein eintöniges Ersatzfragment; die Variante wird dann verworfen.
- **Sequenz:** die ersten zwei Töne mit ihrem Rhythmus, danach dieselbe Zweitonfigur
  sieben Halbtöne höher. Die Wiederholung beginnt beim ursprünglichen dritten Einsatz,
  bei zweitönigem Material nach dem Ende der zweiten Note. Erst eine gemeinsame
  Transposition platziert die vollständige Figur in Harmonie und Register.
- **Augmentation:** alle relativen Einsätze und Dauern werden verdoppelt. Bestehende
  Artikulationsüberhänge werden auf den nächsten Einsatz begrenzt; keine zusätzlichen
  Gegenstimmen oder Kombinationen verschiedener Verfahren.

Eine Variante, die exakt dem Original entspräche, ist kein neues Ergebnis und wird
verworfen. Ungültiges/unvollständiges Material wird ebenso abgelehnt. Die kleine
Spielfigur hat Platz für maximal zehn Noten; die aktuelle Sequenz benötigt vier.

## Policy und zurückhaltende Auswahl

`MotifRecurrencePolicy::variations` ist eine achtteilige deterministische Folge:
Unverändert – Rhythmus – Unverändert – Fragment – Unverändert – Sequenz – Unverändert –
Augmentation. `sequenceSemitones` beträgt neutral 7. Beide Daten werden tatsächlich
von der Engine verwendet und validiert. Alle drei Profile nutzen dieselbe Vorgabe.
Die Wiederkehrabstände und deren Kontextentscheidung bleiben erhalten. Die Folge
zählt geplante Gelegenheiten, keine nachträglich gezählten erfolgreichen Aufführungen.

Kann das gewünschte Verfahren nicht vollständig platziert werden, wird es verworfen;
danach wird das Original eigenständig geprüft. Passt auch dieses nicht, bleibt die
Gelegenheit still. So erzwingt die Policy weder eine Variation noch maximal viele Noten.
Es gibt keine neuen GUI-Parameter und keine zusätzliche Motivengine.

## Vollständige Vorprüfung und zeitliche Koordination

`Generator::motifOccurrence()` prüft jetzt die gesamte abgeleitete Figur: relative
Einsätze, zulässige Notendauern, Register, MIDI-Grenzen und Akkordtonklassen während
jedes klingenden Tons. Die ganze Figur muss mit einer gemeinsamen Transposition passen.
Instrumentenfähigkeiten beruhen weiterhin auf den deklarierten Generatorannahmen,
nicht auf einer automatischen Erkennung externer Patches.

Die tatsächliche Figurenlänge geht in `planRecurrence()` ein. Mindestpause, Szenenende,
Antwortreserve und begrenzter Planungshorizont werden damit vor der Ausgabe berücksichtigt.
`planMotifNote()`, `primaryMotifWindow()`, Ausgabe und Seek verwenden dieselbe Figur.
Auto-Arp-Anschläge werden im tatsächlichen aktiven Figurenfenster unterdrückt.
Bereits klingende Arp-Nachklänge und die bestehende Ausnahme für geteilte Kanäle bleiben.

`planDialogue()` legt den Beginn der vorhandenen Dialog–Arp-Antwort frühestens hinter
das Ende der Frage. Eine vieraktige Augmentation kann deshalb nicht mit einer schon
nach zwei Takten einsetzenden Antwort konkurrieren. Die Antwort selbst bleibt beim
vorhandenen Originalmaterial. Die sparsame Melodie–Dialog-Schlussfigur bezieht sich
weiterhin ausdrücklich auf das Original und liegt in einem nichtführenden Horizont.
Keine zusätzliche Antwortform wird eingeführt.

## Konkrete tatsächlich ausgegebene MIDI-Figuren

Gehaltener Cmaj7-Kontext, Gegenstimme, Seed 3, Intensität 0,7. Relative Zeiten in
Sechzehntel-Ticks (4 Ticks = Viertel). MIDI 60 = mittleres C.

| Figur | MIDI-Noten | Einsätze | Dauern | Bedarf |
|---|---|---|---|---|
| Original / unverändert | 67, 71, 64, 67 | 0, 12, 16, 24 | 13, 5, 9, 8 | 32 Ticks / 2 Takte |
| Rhythmisch | 67, 71, 64, 67 | 0, 12, 16, 24 | 6, 4, 8, 8 | 32 Ticks / 2 Takte |
| Schlussfragment | 71, 64, 67 | 0, 4, 12 | 4, 8, 8 | 20 Ticks / 1¼ Takte |
| Sequenz | 72, 76, 79, 83 | 0, 12, 16, 28 | 12, 4, 12, 5 | 33 Ticks / 2¹⁄₁₆ Takte |
| Augmentation | 67, 71, 64, 67 | 0, 24, 32, 48 | 24, 8, 16, 16 | 64 Ticks / 4 Takte |

Die kurzen Überhänge des Originals gehören zur bestehenden gebundenen Artikulation;
die neu abgeleiteten Figuren erzeugen keine Notenüberschneidungen. Die rhythmische
Variante verändert deshalb neben der gezielten Halbierung auch diese Überhänge. Die
Sequenz übernimmt die große Terz der eingeführten Anfangsfigur und deren 12-Tick-Abstand:
C–E wird zu G–B fortgesetzt. Das Fragment bewahrt die Schlussintervalle −7/+3 und den
Einsatzabstand 4/8. Die Augmentation bewahrt alle Intervalle und verdoppelt die Einsätze;
Gate-Begrenzungen verhindern die Verdopplung kurzer Legatoüberschneidungen.

Im gehaltenen 128-Takt-Fall liegen die Wiedereinsätze bei Takt 8, 24, 32, 43, 56, 64,
72, 88, 96, 107 und 120. Davon sechs unverändert, zwei rhythmisch, einmal Fragment,
einmal Sequenz und einmal Augmentation. Die Sequenz liegt bei Takt 64, die Augmentation
bei 88–92. Die folgenden Einsätze halten weiterhin mindestens zwei Takte Abstand nach
dem vollständigen Figurenende. Im wechselnden Cmaj7–Am7–Dm7–G7-Kontext ist die Sequenz
nicht vollständig harmonisch spielbar und wird in diesem Fall durch das Original ersetzt.
Das ist ein zulässiger Verzicht, kein fehlendes Variationsereignis.

## Reproduzierbare Prüfung und Artefakte

`MotifDevelopmentTests` prüft die reinen Ableitungen, Unveränderlichkeit, Quellidentität,
Ungültigkeitsfälle, Notendauern und Antwortfenster. Ein echter 128-Takt-Engine-Durchlauf
sammelt alle fünf tatsächlich realisierten Verfahren und prüft wiederholten Seek/Loop
mitten in deren Noten, ohne eine neue Materialaufnahme zuzulassen.

`VariationProbe` benutzt den realen neutralen Standard. Die Python-Auswertung
`compare_motif_development.py` umfasst 12 Situationen × 3 Profile, jeweils 128 Takte:
gehaltene und wechselnde Harmonik, Mollfarben, ein-/vier-/sechzehntaktige Akkordzyklen,
beide Antwortkontexte, unspielbarer Tonumfang, Seek/Loop, Neustart sowie Pop/Rock.
Sie vergleicht gegen eine echte Ausgabe mit expliziter Nur-Original-Policy und prüft:

- unveränderte Aufnahmeidentitäten, Intervalle, Einsätze, Dauern und Harmonie;
- direkte Ableitung aus dem Original und jede tatsächlich ausgegebene Variantennote;
- konkrete Notendauern, harmonische Eignung, Mindestpausen und Register;
- keine unzulässigen konkurrierenden Antworten oder Auto-Arp-Anschläge;
- ausgeglichene MIDI-Notenverwaltung;
- identische MIDI-Daten und Pläne bei 127, 512 und 8192 Samples;
- Pop/Rock bleibt unberührt.

Transportfälle werden wegen ihrer Sprünge nicht als normale Häufigkeitsstatistik gezählt.
Die übrigen Verteilungen sind Messwerte der realisierten Verfahren, keine Qualitätsziele.
Historische Wiederkehr-/Übergangsvergleichsprobes fixieren ausdrücklich die bisherige
Rhythmus-Policy, damit ihre bisherigen Invarianten weiter geprüft werden; der neue
Standard wird separat vollständig geprüft. Es existiert keine zweite Produktionsengine.

```sh
python3 scripts/compare_motif_development.py --probe /pfad/VariationProbe \
  --output /tmp/stromscore-motif-development
```

Die Auswertung erzeugt `summary.json`, detaillierte Pläne und importierbare Paare
`held-original.mid` / `held-variants.mid`, entsprechend auch für die anderen Situationen.
Lokal liegen sie unter `/workspace/work/motif-development`. Je Datei 128 Takte bei
120 BPM, also 4:16 Minuten. Dieselben Patches für den Vergleich verwenden; zunächst
Dialog (Kanal 8), anschließend mit Arp (Kanal 5) hören. Im Melodiefall führt Kanal 9.

## Grenzen

Der feste achtaktige Planungshorizont bleibt bestehen; Augmentation und Antwort müssen
vollständig darin Platz finden. Nur eine Transformation pro Wiederkehr, keine
rekursive Entwicklung und keine Formgrammatik. Die feste Sequenz um sieben Halbtöne
passt nicht zu jedem Motiv oder jedem Akkord – dann wird sie verworfen. Harmonieanpassung
bedeutet eine gemeinsame Transposition, keine frei diatonische Umformung der Intervalle.
Sehr kurze Originale können kein sinnvolles Schlussfragment liefern. Aktuelle Einstellungen
werden innerhalb eines Planungshorizonts wie bisher gelatcht; keine unbegrenzte Historie
beliebiger Live-Automation. Ein kalter Seek ohne tatsächlich aufgenommenes Motiv erfindet
keine frühere Einführung.

Die unabhängige Einschränkung harmonischer Eintrittslagen bei kaltem Seek bleibt
unverändert und ist separat in `COLD_SEEK_HARMONIC_TRANSITIONS.md` dokumentiert.
Die Messwerte belegen Erkennbarkeitsmerkmale und technische Konsistenz; ein musikalisches
Qualitätsurteil mit den vorgesehenen Instrumenten erfordert weiterhin einen Hörtest.


## Gemessene Verteilung

Über die kontinuierlichen Vergleichsfälle aller drei Profile (ohne Seek-/Neustartfälle)
werden 282 Wiederkehren realisiert: 165 unverändert, 51 rhythmisch, 21 Fragmente,
18 Sequenzen und 27 Augmentationen. Das entspricht rund 58,5 % unverändertem Material.
Die absolute Zahl ist eine Eigenschaft dieser Testmatrix, kein angestrebtes Dichteziel.
Die vollständigen Verteilungen pro Fall und Profil, Quellidentitäten, konkrete Beispiele
und MIDI-Prüfsummen stehen in `MOTIF_DEVELOPMENT_COMPARISON.json`.


Abschließende Prüfung: 15/15 Kern-/Vergleichstests, 1/1 Processor-Live-/Exporttest,
3/3 ASan-/UBSan-Läufe (MotifDevelopmentTests, CompositionCoreTests, EngineTests)
und 7/7 Release-/Paketprüfungen bestanden. Es wurde kein Release erzeugt.
Der vorhandene Plugin-Dateiexport bleibt auf 64 Takte begrenzt; die separaten
Engine-Vergleiche umfassen jeweils 128 Takte. Keine GUI-/Harmonieänderung, kein Push.
