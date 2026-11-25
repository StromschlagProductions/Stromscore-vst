# Profilwechsel, Ruhemodus und ungültige Wendung

## Nachgewiesener Fehler

Ausgangsstand: `aaec260`, musikalischer Stand `24f3c13`. Reproduktion bei
laufendem Host: Intensität auf 0,05 absenken, Neutral ↔ John Barry umschalten,
anschließend Intensität auf 0,95 erhöhen. Ebenso bei einem Profilwechsel im
gestoppten Zustand nach vorherigem Eintritt in den Ruhemodus.

Der Profilwechsel setzte `current = -1`, ließ aber `still = true` bestehen.
`Generator::ensurePhrase()` wählte im Ruhemodus keine Wendung. Gleichzeitig
konnte `updateStill()` bei ungültiger Wendung den Ruhemodus nicht verlassen.
Der geklemmte Zugriff über `wendungAt()` interpretierte den ungültigen Index
beim Rendern als ersten Katalogeintrag. Deshalb konnten weiterhin MIDI-Noten
erklingen, ohne gültige Wendung und ohne harmonische Weiterentwicklung.

Die GUI erhielt während der Host-Wiedergabe den tatsächlich ungültigen
Wendungsindex und zeigte deshalb den Starttext. Internes Vorhören bei
gestopptem Host verwendete dagegen seinen eigenen, gültig initialisierten
Generator. Ein vollständiger Neustart beseitigte den blockierten Zustand.
Ein Absturz oder eine getrennte Studio-One-Verarbeitungsinstanz wurde damit
nicht nachgewiesen.

## Begrenzte Korrektur

- `Generator::hasWendung()` prüft den Index gegen den tatsächlichen
  Genre-/Profilkatalog; eine eigene Akkordfolge ist ein ausdrücklich gültiger Fall.
- `ensurePhrase()` initialisiert eine ungültige Auswahl auch im Ruhemodus
  und auch innerhalb derselben Phrase. Eine bereits gültige, gehaltene
  Harmonie bleibt von dieser Änderung unberührt.
- Vor der Ereignisausführung wird die gültige Auswahl sichergestellt. Falls
  sie wider Erwarten nicht hergestellt werden kann, werden Noten freigegeben
  und es wird kein Ersatzakkord erzeugt.
- Der interne harmonische Zugriff `W()` verwendet nur eine gültige Auswahl;
  er klemmt einen ungültigen Index nicht mehr auf Katalogeintrag 0.

Damit kann die bestehende `updateStill()`-Logik an ihren bisherigen
Wechselpunkten wieder regulär arbeiten. Es gibt weder neue Schwellen noch
einen erzwungenen sofortigen musikalischen Einsatz. Prozessor, GUI-Timer,
Auswahlalgorithmus und Barry-Policies benötigen keine Änderung.

## Automatisierter Nachweis

`Tests/ProfileSwitchTests.cpp` / CTest `ProfileSwitch`:

- Beide Profilrichtungen, Score und Pop/Rock, laufender und gestoppter
  Transport, statische Positionen und kontinuierliche XYZ-/Variationsänderungen.
- Nach dem Wechsel zunächst weiterhin niedrige Intensität, dann hohe
  Intensität; jeweils mindestens 128 Takte Weiterlauf.
- Gültige Auswahl in jedem laufenden Block sowie tatsächlich unterschiedliche
  Akkordidentitäten und Bass-Tonklassen nach Verlassen des Ruhemodus.
- Stop/Neustart, Seek und wiederholte Loop-Rückkehr; MIDI-Notenbilanz und
  Allokationsprüfung. Exakte Ereignisgleichheit zwischen Blockgrößen
  127/512 bzw. 512/8192 bei Swing 0,35; insgesamt 64 lange Renderings.
- Derselbe neue Test schlägt mit den unveränderten Headern von `aaec260`
  bereits an der Prüfung des gültigen Wendungsindex fehl.

`Tests/ProfileSwitchProcessorTests.h` / CTest `ProcessorProfileSwitch`:

- Tatsächlicher Plugin-Prozessor, APVTS-Parameter, Fake-Host-Transport und
  echter Editor mit laufender Message-Loop und GUI-Timer.
- Acht Szenarien und 56 Anzeigeprüfungen: niedrige Intensität, Profilwechsel,
  erhöhte Intensität, Vorhören während Host-Wiedergabe, eigenes Vorhören bei
  gestopptem Host, Host-Neustart sowie Seek/Loop mit XYZ und Variation.
- Wendungsname, Akkordname, Akkordindex und Profil müssen dem tatsächlichen
  Prozessorzustand entsprechen; zusätzlich MIDI-Ausgabe, harmonische
  Weiterentwicklung, Notenbilanz und Heap-/Allokationsschutz im Prozessaufruf.

Die regulären Tests bleiben einschließlich tatsächlicher Live-/MIDI-Export-
Vergleiche aktiv. Zusätzliche bytegleiche Vergleiche gegen `aaec260` verwenden
`tools/barry_probe.cpp`, kompiliert mit `-DBARRY_PROFILE`: drei Profile, beide
Genres, fünf statische/bewegte XYZ-Verläufe sowie manuelle Begleitung und
Stop/Seek-Routen, jeweils 128 Takte. Die Einzelprüfsummen stehen in
`PROFILE_SWITCH_MIDI_COMPARISON.json`.

Ergebnis dieses Vorher-/Nachher-Vergleichs: **42/42 Renderings bytegleich**,
insgesamt **796.233 MIDI-Ereignisse**. Der Vergleich misst unveränderte, gültig
initialisierte Verläufe; für die vorher blockierten Abläufe ist eine Änderung
ausdrücklich beabsichtigt und wird durch die neuen Regressionstests geprüft.
Die JSON-Felder entsprechen den Argumenten des Probe-Werkzeugs
`profile path 128 512 route genre manual`; Profil 0/1/2 bedeutet
Neutral/Barry/Herrmann, Genre 0/1 bedeutet Score/Pop-Rock.

Lokale Abschlussprüfung:

- Vollständige Core-Suite: **52/52 bestanden**, einschließlich der historischen
  Zeitbasis-, Harmoniedaten-, Motiv-, Rhythmus- und Begleitvergleiche.
- Prozessor-Suite und neuer Prozessor-/Editor-Wechseltest: **2/2 bestanden**;
  tatsächliche Live-/Export-Vergleiche und 56 GUI-Zustände geprüft.
- ASan/UBSan: **2/2 bestanden** (`Barry`, `ProfileSwitch`; Leak-Erkennung in
  diesem Sanitizer-Lauf deaktiviert). Allokations- und C-Heap-Wächter bleiben
  in den entsprechenden normalen Prozessortests aktiv.
- Paketprüfer: **7/7 bestanden**; Linux-VST3 gebaut; `git diff --check` sauber.

Reproduktionsbefehle: `ctest --test-dir <core-build> --output-on-failure`,
`ctest --test-dir <plugin-build> -R '^Processor(ProfileSwitch)?$' --output-on-failure`
mit verfügbarer Desktop-/X11-Sitzung sowie `python Tests/ReleaseTests.py`.
Für den Sanitizer-Build werden AddressSanitizer und UndefinedBehaviorSanitizer
aktiviert und `ctest -R '^(ProfileSwitch|Barry)$'` ausgeführt.

## Grenzen und Hörabnahme

Die Einschränkungen der korrekt initialisierten Barry-Begleitstrategie bleiben
ausdrücklich erhalten: Diese Fehlerkorrektur erweitert weder ihre rhythmische
Vielfalt noch ihre musikalischen Vorlagen. Sie beseitigt den Zustand, in dem
überhaupt keine gültige Wendung mehr fortgeschrieben wurde. Der Neustart eines
alten Projekts ersetzt nicht den gezielten Wechseltest in der beiliegenden
Studio-One-Anleitung.

Die Host-Anbindung wird automatisiert simuliert; der abschließende Test im
konkreten Studio-One-Projekt bleibt eine praktische Hör- und Hostprüfung.
Kein offizielles Release und keine weiterführende Profilentwicklung in diesem
Auftrag.
