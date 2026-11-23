# Erste gemeinsame Begleitkoordination

Ausgangspunkt: `237b415`, Branch `develop/composition-core-prototype`.

## Umfang

Im Score-Modus unterdrückt der gemeinsame Mechanismus neue Anschläge des automatisch
gewählten Arpeggios innerhalb einer spielbaren Motivfigur. Die Profilidentität ist dafür
unerheblich: Neutral, Barry und Herrmann verwenden dieselbe Regel. Manuelle Arp-Figuren
und Pop/Rock bleiben unverändert. Eine manuelle Arp-Geschwindigkeit bei automatischer
Figur hebt die Koordination nicht auf.

`composition::MotifWindow` beschreibt Besitzer und halboffenes Zeitfenster in musikalischen
Ticks. Der Adapter prüft die aktive Vordergrund-/Dialogrolle, Motivschalter, vorhandenes
Material, Einführungs-/Wiederkehrphase, Register und Dauerfähigkeiten. Mindestens zwei
spielbare Noten sind erforderlich. Das Fenster reicht vom ersten vorgesehenen Anschlag
bis zum Ende der letzten vorgesehenen Note; Binnenpausen gehören zur Figur. Für reguläre
Motive bleibt es innerhalb der bisherigen ersten zwei Phrasentakte.

`planMotifNote()` wird von Preflight und bestehender Motivausgabe gemeinsam verwendet.
Der Preflight liest nur; er veröffentlicht keine Motive, übernimmt keine Referenzen und
verändert weder Cursor noch Wiederkehr-/Variationszustand. Bei einem Sprung hinter den
letzten Motivanschlag ohne klingende Motivnote wird kein vergangenes Spiel erfunden.

Die bestehende Melodie–Dialog-Schlussfigur nutzt ihre bisherige harmonische/Register-
Prüfung nun gemeinsam mit der Reservierung (`playableMelodyHandoff()`). Nur eine dort
zugelassene Antwort bekommt ihr bisheriges Antwortfenster freigehalten. Sie beginnt
weiterhin nach der vorgesehenen Pause und darf höchstens zwei Takte dauern. Die spezielle
Dialog–Arp-Antwort benötigt eine explizite manuelle Arp-Zelle und bleibt unverändert.

## Grenzen

- Nur Arp-Anschläge entfallen. Bereits klingende Arp-Noten werden nicht abgeschnitten;
  Bass, Harmonie, Akzente und normale nichtmotivische Linien werden nicht neu koordiniert.
- Bei einem mit irgendeinem anderen Ziel geteilten Arp-MIDI-Kanal bleibt die bisherige
  Ausgabe vollständig erhalten, auch wenn das andere Ziel stumm ist. Gemeinsame physische
  Noten können Anschläge, Aufnahme und Freigaben beeinflussen. Dieser konservative
  Ausnahmefall vermeidet eine Änderung der Notenbesitzverwaltung in diesem Schritt.
- Geprüft wird der bekannte Plan unter den aktuellen Einstellungen. Spätere Automation
  oder manuelle Eingriffe werden nicht vorhergesagt; die Prüfung wird am Raster erneuert.
- Instrumentenfähigkeiten bleiben die vorhandenen Generatorannahmen, keine Erkennung
  eines geladenen externen Patches.
- Bei geänderter aktiver Notenliste kann sich die Reihenfolge gleichzeitig fälliger
  Note-offs verschiedener anderer Ziele ändern. Ihre musikalischen Ereignisse (Zeit,
  Kanal, Ton, Anschlagswert) bleiben identisch. Tests vergleichen diese unabhängig von
  der Reihenfolge gleichzeitiger Ereignisse und separat die exakte Blockdeterministik.

## Reproduzierbare Vorher-/Nachher-Prüfung

`tools/accompaniment_probe.cpp` rendert dieselben Einstellungen gegen den alten und neuen
Generator. `scripts/compare_accompaniment.py` extrahiert die Header von `237b415` in ein
temporäres Verzeichnis und baut ausschließlich den Referenz-Probe damit. Keine zweite
Engine wird in das Plugin eingebaut. Der Referenzvergleich setzt einen verfügbaren
Git-Ausgangspunkt und einen GCC-/Clang-kompatiblen Compiler voraus; CTest registriert ihn
bei erfüllten Voraussetzungen. Plattformunabhängige Invarianten stehen außerdem in
`EngineTests.cpp`.

Beispiel nach einem Engine-Testbuild:

```sh
python3 scripts/compare_accompaniment.py \
  --probe /pfad/zum/build/AccompanimentProbe \
  --compiler c++ --output /tmp/stromscore-accompaniment
```

Ausgabe: vollständige Vorher-/Nachher-Ereignisse für Dialog, Melodie und Melodie–Dialog-Antwort als CSV,
exakt entfallene Anschläge als eigene CSV und `summary.json` mit Ereigniszahlen und
SHA-256 der vollständigen Ereignislisten. Samplezeiten beziehen sich auf 48 kHz.

Die Hauptmatrix umfasst 19 Situationen für alle drei Profile, jeweils 96 Sekunden bei
120 BPM. Neben Motiv-Einführung, Wiederkehr und Variation werden ausgeschaltete Motive,
Pop/Rock, unspielbare Melodie, Mute/Solo, manuelle Antwortverfahren, Kanalteilung,
Aufbau, Akkordwechsel, 3/4 mit Swing, Katalogharmonie, Seek/Loop und Szenenneustart geprüft.
32 zusätzliche Vergleiche variieren Seed/Variation für beide Motivstimmen.

Für statische 4/4-Fälle bestimmen die tatsächlich ausgegebenen Motivanschläge und
Freigaben der Referenz unabhängig das erwartete Reservierungsfenster. Jeder entfallene
Arp-Anschlag muss darin liegen; alle erwarteten entfallen. Alle übrigen Ausgänge bleiben
ereignisgleich. Überlebende Arp-Notenspannen behalten Anschlag und Freigabe. Kontexte
außerhalb der neuen Funktion werden vollständig unverändert verglichen. Die Hauptmatrix
wird zusätzlich mit Blockgrößen 127 und 8192 gegen 512 Samples bytegleich verglichen.

Die Processor-Tests ergänzen Auto-Arp-Fälle für Dialog und Melodie und prüfen sie wie
bisher gegen den tatsächlichen MIDI-Dateiexport, einschließlich Controllerdaten.

## Ergebnis der MIDI-Auswertung

89 Vorher-/Nachher-Vergleiche (57 Hauptfälle und 32 zusätzliche Seed-/Variationsfälle)
und 114 zusätzliche Blockgrößenvergleiche bestanden. Die maschinenlesbaren Zahlen und
SHA-256 stehen in `ACCOMPANIMENT_COMPARISON.json`.

Auszug für Neutral, 96 Sekunden, 120 BPM, 4/4, Seed 3, Variation 1, Cmaj7,
achtaktige Phrase, Intensität 0,7, Aufbau AUS, getrennte Standardkanäle:

| Situation | Arp vorher | Arp nachher | Entfallen | Linienanschläge Melodie/Dialog vorher/nachher |
|---|---:|---:|---:|---:|
| dialog | 768 | 672 | 96 | 12/12 |
| melody | 768 | 672 | 96 | 12/12 |
| auto-melody-dialog-answer | 768 | 632 | 136 | 18/18 |
| motifs-off | 768 | 768 | 0 | 96/96 |
| pop-rock | 768 | 768 | 0 | 384/384 |
| unplayable-melody | 768 | 768 | 0 | 0/0 |
| dialog-arp-answer | 393 | 393 | 0 | 12/12 |
| melody-dialog-answer | 768 | 768 | 0 | 18/18 |
| shared-channel | 768 | 768 | 0 | 15/15 |

`melody` schaltet das eigene Dialogmotiv aus und zeigt nur die Hauptmelodie.
`auto-melody-dialog-answer` aktiviert beide Motivschalter und enthält die bestehenden
Antworten. Die beiden manuellen Antwortkontexte bleiben vollständig unverändert.
Die Tabelle zählt Note-ons; die zu entfallenen Anschlägen gehörenden Note-offs entfallen
ebenfalls. Überlebende Arp-Noten behalten ihre bisherige vollständige Notenspanne.

Die drei betroffenen Hauptfälle haben bei Barry und Herrmann dieselben Anschlagszahlen;
auch dort bleiben alle Motivereignisse unverändert. Katalogharmonie wird zusätzlich
profilabhängig geprüft. Eine subjektive Verbesserung ist damit noch nicht hörend abgenommen.

## Weitere Validierung

- Kern-CTest: 8/8 bestanden, einschließlich des neuen Referenzvergleichs.
- Linux/Xvfb-Processor-Test: 1/1 bestanden, einschließlich Live-/SMF-Exportgleichheit.
- Gezielte ASan-/UBSan-Prüfungen: CompositionCore, Policy und Engine, 3/3 bestanden.
- Python-Paketprüfer: 7/7 bestanden.
- Keine neue Windows-/pluginval- oder subjektive Hörprüfung.

Es wurden weder GUI noch Profilgewichte oder Motivrepertoire verändert. Kein Push und
kein Release.
