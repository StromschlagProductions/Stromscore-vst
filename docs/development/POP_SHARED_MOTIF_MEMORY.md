# Gemeinsames Motivgedächtnis für Pop/Rock

Basis `912d04c`, Entwicklungsbranch `develop/composition-core-prototype`.

## Vorhandener Pfad und begrenzte Anbindung

`Generator::leadHook()` besitzt neun explizite zweitäktige Hook-Studien mit bis zu
acht Anschlägen, darunter Figuren mit Anfangs- und Binnenpausen. Die übrigen Hooks
benutzen eine achtstellige Kontur mit Viertel-/Achtelgeschwindigkeit. Ihre musikalische
Periode ist damit je nach Intensität zwei oder ein Takt in 4/4. Akkordwechsel und
bestimmte Studien verändern die konkreten Tonhöhen weiterhin während der Wiedergabe.

Der bestehende Generator erzeugt weiterhin dieselben MIDI-Ereignisse. Es wurde weder
seine Tonwahl noch seine Wiederholungslogik durch ein starres Abspielen des ersten
Zyklus ersetzt. Das würde harmonische Anpassungen, alternierende Konturen und dynamische
Änderungen verlieren. Die Anbindung ist in diesem Schritt eine Aufnahme plus explizite
unveränderte Wiedergabemöglichkeit, keine neu aktivierte Wiederkehrstrategie.

## Gemeinsame Daten und Aufnahme

`composition::RememberedMotif` fasst jetzt maximal acht statt fünf Noten. Die bisherigen
Score-Motive bleiben gleich groß und behalten ihre bisherigen Identitäten. Zwei neue
Materialangaben beschreiben Zeiteinheit (`timeScale`, Einheiten pro Generator-Sechzehntel)
und ursprüngliche Figurenlänge (`cycleLength`). Bei Score bleibt `timeScale=1`; die
bestehenden Score-Ableitungen nehmen kein Material mit abweichender Zeitskala entgegen.

Der neue allgemeine `composition::MotifCapture` schreibt in den vorhandenen Aufnahmeentwurf
von `MotifUse`. Er ist weder an Pop/Rock noch an eine MIDI-Spur gebunden. `MotifCatalog`,
Materialidentität, Veröffentlichung und unabhängige Stimmenreferenzen bleiben dieselben.
Es gibt keinen zusätzlichen Pop-Motivkatalog und keine zweite Motivimplementierung.

`armHookCapture()` meldet einen tatsächlich beginnenden Hook-Zyklus an. Die nachgelagerte
Methode `capturePerformance()` beobachtet die ausgegebenen Note-on/off-Ereignisse in der
EventList. Deshalb werden klingende, bereits in den Tonumfang gefaltete MIDI-Tonhöhen und
tatsächliche Velocity gespeichert. Die Dauer entsteht erst beim tatsächlichen Note-off:
Legatoüberhänge, vorzeitige Abschlüsse und Wiederanschläge derselben Note werden erfasst,
nicht aus der ursprünglichen Generatorabsicht geschätzt.

Ein vollständiger Aufnahmezyklus wird erst veröffentlicht, wenn sämtliche aufgenommenen
Noten beendet wurden. Der Ton nach der Zyklusgrenze gehört nicht mehr zur Aufnahme; sein
Wiederanschlag kann aber den tatsächlichen Schluss der letzten aufgenommenen Note bestimmen.
Anfangs- und Binnenpausen bleiben als relative Einsätze erhalten, die Figurenlänge erhält
auch die Information über eine abschließende Pause. Weniger als zwei Noten oder eine
überlaufende Aufnahme werden nicht als vollständiges Motiv veröffentlicht.

Die Pop-Aufnahme verwendet **960 PPQ**, also `timeScale=240`. Das ist dieselbe musikalische
Auflösung wie beim Plugin-Dateiexport. Swing-Zeitpunkte werden aus den tatsächlichen
Ereignispositionen auf dieses Raster gerundet. Das erhält die MIDI-rhythmische Identität
auf Exportauflösung, verspricht aber keine samplegenaue Darstellung beliebiger Swing-
Zeitpunkte oder Tempi. Die unveränderte Live-Ausgabe selbst wird dabei nicht quantisiert.
Velocity gehört zum gespeicherten Material; wie bisher beruht die musikalische Identität
auf Intervallen, Einsätzen und Dauern, ergänzt um abweichende Zeitskala und Zykluslänge.

## Wiedergabe und unabhängige Zustände

`composition::replayMotifNote()` liefert für jede veröffentlichte Originalnote unverändert
klingende MIDI-Tonhöhe, tatsächliche Velocity, relativen Einsatz und Dauer. Der Aufrufer
ordnet diese musikalischen Ereignisse einem geeigneten Ziel zu; die Funktion enthält keine
Instrumenten- oder Kanalentscheidung. Tests gleichen alle so wiedergegebenen Noten und
Endpunkte mit der tatsächlich aufgezeichneten Performance ab.

Dieser Replay-Zugriff ist explizit verfügbar, übernimmt aber noch nicht den laufenden
Pop-Hook-Pfad. Es gibt in diesem Auftrag keine neue Wiederkehr, Transposition des aufgenommenen
Materials, Variation, automatische Übergabe oder Orchestrierung. Der erste veröffentlichte
Zyklus bleibt unverändert, auch wenn spätere Hooks anders gespielt werden.

Aufnahmezustand und Referenz liegen im vorhandenen `VoiceState`. Die Melodiestimme erhält
keinen Hook durch gemeinsamen Speicherzugriff und bleibt in Pop/Rock weiterhin deaktiviert.
Die vorhandenen Pop-Hooks spielen unabhängig vom Score-Motivschalter; die passive technische
Aufnahme ändert daran nichts. Ein Genrewechsel löscht Materialreferenzen und Aufnahmen,
damit Pop-Zeiteinheiten nicht versehentlich als Score-Sechzehntel interpretiert werden.
Die bisherigen Linien-/Vorhaltszustände werden dabei nicht pauschal ersetzt.

Seek/Loop behalten ein bereits veröffentlichtes Motiv innerhalb derselben Szene. Eine
unterbrochene unvollständige Aufnahme wird verworfen; die nächste vollständige Zyklusgrenze
kann eine neue Aufnahme beginnen. Neustart beginnt eine neue Szene und leert den Katalog.
Geteilte MIDI-Kanäle werden für die Aufnahme bewusst abgelehnt, auch wenn die andere Ebene
aktuell stumm ist: physische Noten besitzen dort keine eindeutige Stimmenidentität. Wird
während der Aufnahme der Kanal gewechselt oder mehrdeutig, wird die Aufnahme verworfen.
Die tatsächliche MIDI-Ausgabe bleibt auch in diesen Fällen unverändert.

## Konkrete MIDI-Beispiele

Bezugstonart C, jeweiliger Kataloganker, Variety 0, Dialog solo, Legato EIN. Zeiten und
Dauern in 960-PPQ-Ticks; die Werte wurden aus einer tatsächlichen Generatorperformance
aufgenommen. Schreibweise: `Tonhöhe @ Einsatz / Dauer`.

- **2001, kontinuierlicher generischer Hook, Periode 3840:**
  `72@0/480, 72@480/720, 79@960/720, 72@1440/720, 84@1920/720,
  72@2400/720, 79@2880/720, 75@3360/720`.
  Die erste Dauer beträgt tatsächlich 480: der erneute Anschlag desselben Tons beendet
  ihn früher als seine ursprünglich angeforderte Legatodauer.
- **2028, acht Anschläge, Periode 7680:**
  `72@0/960, 76@720/960, 79@1440/1200, 76@2400/1680,
  72@3840/960, 76@4560/1200, 84@5520/1440, 79@6720/1200`.
  Bestehende Legatoüberhänge bleiben als tatsächlich gespielte Dauern erhalten.
- **2031, unterbrochener Hook, Periode 7680:**
  `69@1440/720, 76@2400/2640, 76@5280/720, 81@6240/1200`.
  Die Anfangspause von 1440 und die Schlussstille bis zur Zyklusgrenze gehen nicht verloren.
- **2030, nur drei Anschläge, Periode 7680:**
  `69@0/3120, 67@2880/2880, 67@5760/1920`.
  Auch hier ist der tatsächliche Wiederanschlag maßgeblich für den vorherigen Ton.

Das gespeicherte Material beschreibt diese konkrete Ausführung, nicht alle zukünftigen
harmonieabhängigen Ausführungen einer abstrakten Hook-Tabelle.

## Nachweise und Grenzen

`PopMemoryTests` prüft alle 36 Anker sowie niedrige/hohe Intensität, beide Legatostellungen,
kontinuierliche und unterbrochene Muster, Tonhöhen, tatsächliche Dauern, vollständige
Anschlagsanzahl, unveränderten Replay-Zugriff, getrennte Stimmen, Swing, Mute, gemeinsame
Kanäle, Seek/Loop und Neustart. Die Verarbeitung wird auf Allokationsfreiheit geprüft.

`PopMemoryProbe` und `compare_pop_memory.py` vergleichen den vollständigen MIDI-Strom
gegen die wirklichen Header aus `912d04c`: alle 84 Kataloganker, jeweils Neutral/Barry/
Herrmann, je 16 Takte, einschließlich Swing. 252 bytegenaue Regressionen plus Vergleiche
512/8192 Samples. Die Aufnahmetests vergleichen zusätzlich 127/512/8192 Samples.

Historische Diagnosevergleiche ignorieren bei Pop nur die neu hinzugekommene Motivmetadaten-
Spalte; ihre Harmonie- und MIDI-Vergleiche bleiben erhalten. Die neuen Aufnahmetests prüfen
diese Metadaten ausdrücklich. Der Processor-Test umfasst zusätzlich Pop mit eigener und
Stock-Akkordfolge für echte Live-/SMF-Gleichheit.

Bekannte Grenzen: höchstens acht Noten und zwei veröffentlichte Materialien pro Szene,
keine Aufnahme auf geteilten Kanälen, keine automatische Materialaktualisierung späterer
Hook-Zyklen. Material mit anderer Zeitskala kann noch nicht durch die Score-Variations-
planung geschickt werden. Eine nächste Integration muss die Zeitbasis ausdrücklich
berücksichtigen, statt neue Pop-Variationsfunktionen zu duplizieren. Die harmonische
Einschränkung bei kaltem Seek aus `COLD_SEEK_HARMONIC_TRANSITIONS.md` bleibt unverändert.


Abschließende Prüfung: alle 17 Kern-/Vergleichstests erfolgreich (der angepasste historische
Dichte-Metadatenvergleich wurde abschließend gezielt erneut ausgeführt), 1/1 Processor-Test
mit zusätzlichen Pop-Live-/Exportfällen, 3/3 ASan-/UBSan-Prüfungen und 7/7 Paketprüfungen.
Die erweiterten Pop-Aufnahmetests einschließlich Swing wurden zusätzlich erneut mit
ASan/UBSan geprüft. Keine musikalischen MIDI-Abweichungen in den 252 Referenzfällen.

Importierbare 16-Takt-MIDI-Beispiele mit Swing sowie CSV und Regression-Prüfsummen
liegen unter `/workspace/work/pop-memory-comparison`, unter anderem `2028-swing.mid`
und `2031-swing.mid`. Diese Dateien enthalten das ganze Arrangement, Dialog auf Kanal 8;
die obigen Tabellen isolieren dagegen die ohne Swing aufgenommenen Hook-Noten.
Die Beispiele sind technische Wiedergaben, kein neuer Hörtest oder Qualitätsurteil.
