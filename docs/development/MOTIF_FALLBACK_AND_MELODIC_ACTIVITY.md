# Motiv-Fallback und melodische Aktivität

Ausgangspunkt: `9a3cbad`, Branch `develop/composition-core-prototype`.
Umfang: ausschließlich den belegten Score-Fallbackfehler korrigieren; weitere musikalische Ursachen untersuchen, nicht verändern. Kein Push, kein Release.

## 1. Korrigierter Fehler

`Generator::motifStep()` gibt bei nicht abgeschlossenem Material außerhalb der Einführung `false` zurück. `counterLine()` verwendet dann bereits seit vor der Scheduler-Migration seine lokale Linienführung. `nextOnset()` behandelte dagegen allein den eingeschalteten Motivschalter als Zuständigkeit des Motivpfads und meldete die Einsätze dieses Fallbacks nicht an.

Die Einsatzabfrage berücksichtigt jetzt denselben Material-/Einführungszustand wie der Erzeuger. Ein lokales Materialexemplar wird gegebenenfalls so abgeschlossen wie in `motifStep()`/`motifOccurrence()`; die Abfrage verändert weder Katalog noch Stimmenzustand. Ohne abgeschlossenes Material außerhalb der Einführung wird der schon vorhandene Linienzweig abgefragt. Seine Zielnoten, Periode, Artikulation und Zufallsschlüssel bleiben unverändert. Die Rückkehrplanung abgeschlossener Motive und die Pop/Rock-Strategie werden nicht ersetzt.

Produktiver Eingriff: nur `Source/ScoreEngine.h`, `Generator::nextOnset()`.

### Wiederholte Startmessungen

48 kHz, 120 BPM; Score, Färbung .5, Intensität .7, Motiv EIN, jeweils alleinige Gegenstimme oder Hauptmelodie. Zeiten ab dem ersten laufenden Hostblock. PPQ bezeichnet Viertelnoten ab Projektbeginn.

| Start | `9a3cbad` | Korrektur | vor Scheduler (`17b15a4`) |
|---|---:|---:|---:|
| PPQ 0 | 0 ms | 0 ms | 0 ms |
| PPQ .125 | 937,5 ms | 937,5 ms | 937,5 ms |
| PPQ 8.125 | 11.937,5 ms | 937,5 ms | 937,5 ms |
| PPQ 12 / Takt 4 | 10.000 ms | 0 ms | 0 ms |
| PPQ 16.5 | 7.750 ms | 750 ms | 750 ms |

Die 204 Messfälle umfassen 4/4, 3/8, 5/8 und 7/8, motivische und nichtmotivische Gegenstimme sowie Gegenstimmen-Einstieg mit Aufbau. Alle 80 zuvor verspäteten Fälle erreichen wieder den früheren ersten Einsatz; keiner bleibt gegenüber `17b15a4` verspätet. Beabsichtigte Pausen innerhalb einer begonnenen Motivfigur bleiben bestehen.

Regressionen in `Tests/ExecutionTests.cpp`: beide melodischen Ausgänge, kalte Starts auf und zwischen Taktgrenzen, Swing 0/.5, Blockgrößen 64/512/1024, physische Notenbilanzen, leeres Motivgedächtnis, exakte chordrelative Perioden in 3/8, 5/8 und 7/8, Rückwärtssprung/Loop und Szenenneustart. Der neue Kaltstarttest scheitert mit dem unveränderten Header aus `9a3cbad` und besteht mit der Korrektur. Bestehende Tests für eingeführtes Material, Wiederkehr und Antworten bleiben aktiv.

Einzeldaten: `MOTIF_FALLBACK_STARTS.json`.

## 2. Aktivitätsmessung

336 deterministische Langläufe zu jeweils 128 Takten / 256 Sekunden, 48 kHz, 120 BPM, 4/4, 512 Samples, Swing AUS, eindeutige Standardkanäle. Verglichen werden `9a3cbad`, korrigierter Arbeitsstand, `17b15a4` und Tag `v2.1`. Externe Patches und Studio One werden nicht simuliert; gezählt wird tatsächlich ausgegebenes Generator-MIDI. Kein gespeicherter Studio-One-Song lag vor.

Konfigurationen: statische XYZ-Positionen, langsame und schnelle kontinuierliche Fahrten mit Intensität .75–.95, maximale Intensität/Unruhe, Übergang vom eingeführten Motiv zu maximalen Y/Z-Werten, Aufbau, eigene gehaltene Cmaj7-Harmonik, Motiv AUS, Melodie AUS, späte Aktivierung, Mute und Solo sowie laufende Genrewechsel. Die XYZ-Werte werden pro Audioblock aktualisiert. Varianten mit Barry/Herrmann verwenden nur deren bereits vorhandene Harmoniepräferenzen.

**Auslastung** ist die Vereinigungsdauer der MIDI-Notengates einer Rolle geteilt durch 256 s; Legatoüberlappungen zählen nicht doppelt. Es ist keine Messung akustischer Energie oder externer Patch-Releases. **Aktiviert** bezeichnet den internen Ebenenzustand, nicht tatsächlich klingende Noten. `template_changes` zählt Wendungswechsel, nicht einzelne Akkordwechsel.

### Nur Melodie und Gegenstimme offen, Aufbau AUS, beide Motive EIN

Alle vier Begleitrollen sind gemutet; die melodischen Schwellen sind während der gesamten Wiedergabe überschritten. Korrigierter Stand; die hier aufgeführten durchlaufenden Ergebnisse sind gegenüber `9a3cbad` unverändert.

| Verlauf | Melodie: Note-ons / Auslastung | Dialog: Note-ons / Auslastung | längste Melodiepause |
|---|---:|---:|---:|
| Score statisch .25/.85/.1 | 58 / 18,95 % | 0 / 0 % | 28 s |
| Score statisch .5/.9/.75 | 30 / 8,59 % | 0 / 0 % | 76 s |
| Score langsame XYZ-Fahrt | 20 / 6,25 % | 0 / 0 % | 76 s |
| Score schnelle XYZ-Fahrt | 8 / 2,54 % | 0 / 0 % | 169,5 s |
| Score: erst Einführung, dann X-Fahrt bei Y=Z=1 | 5 / 1,56 % | 0 / 0 % | 252 s |
| Pop/Rock statisch .25/.85/.1 | nicht verfügbar | 976 / 98,10 % | – |
| Pop/Rock statisch .75/.85/.2 | nicht verfügbar | 548 / 59,91 % | – |
| Pop/Rock langsame XYZ-Fahrt | nicht verfügbar | 970 / 98,97 % | – |
| Pop/Rock schnelle XYZ-Fahrt | nicht verfügbar | 908 / 92,48 % | – |
| Pop/Rock X-Fahrt bei Y=Z=1 | nicht verfügbar | 1.024 / 100 % | – |

Die vollständige Stille ab dem ersten Projektblock wird damit nicht pauschal reproduziert: Die Einführung erklingt. **Eine anschließende vollständige Stille beider Rollen über mehr als zwei Minuten ist jedoch reproduziert.** Maximalwerte allein erzwingen diese Stille nicht: Wird das Motiv bereits bei Y=Z=1 eingeführt, entstehen in einem anderen Kontrolllauf 60 Melodienoten / 17,97 %. Entscheidend ist die Vereinbarkeit des tatsächlich gespeicherten Materials mit dem späteren harmonischen Kontext.

### Aktivierung bei laufendem Transport – Rückmeldung aus dem Praxistest

Aufbau AUS, beide Motivschalter EIN; Begleitung gemutet. Bei Sekunde 8 wird die Hauptmelodie zusätzlich zur zuvor allein aktiven Gegenstimme freigegeben. Die Melodie übernimmt deren Motiv nicht automatisch.

| Verlauf | `9a3cbad`: erster Melodieeinsatz / Note-ons insgesamt | Korrektur: erster Melodieeinsatz / Note-ons insgesamt |
|---|---:|---:|
| langsame XYZ-Fahrt | 16 s / 12 | 8,5 s / 20 |
| schnelle XYZ-Fahrt | 16 s / 5 | 8 s / 16 |

Die zusätzliche Aktivität ist ausschließlich der wieder erreichbare lokale Fallback bis zur anschließenden Motiveinführung. Danach bleibt im schnellen Lauf eine Pause von 236 s bestehen. Der Fallbackfix ist somit nötig, aber keine Lösung der grundsätzlichen Motiv-/Rollenrestriktionen. Dasselbe gilt, wenn beide Rollen bis Sekunde 8 gemutet und dann gleichzeitig freigegeben werden.

## 3. Ursachen anhand der Implementierung

### Score: Vorrang gilt für Aktivierung, nicht nur für eine klingende Phrase

`ScoreEngine.h::render()` fragt bei `on[kMelodie]` den `ForegroundPlan` ab. Ist dieser geeignet, wird die gewöhnliche Gegenstimme nicht aufgerufen. Ohne aktuell spielbare `melodyHandoff()` wird sie stattdessen beendet. **Auch in einer motivfreien Melodiephase bleibt dieser Vorrang bestehen.** Hohe Intensität und ein eingeschalteter Dialog überstimmen ihn nicht.

`CompositionCore.h::planMelodyHandoff()` erlaubt nur sparsame Antwortfenster; `ScoreEngine.h::playableMelodyHandoff()` prüft unter anderem dieselbe Harmonie über die ganze Schlussfigur, Tonumfang und Spielweise. Deshalb ist ein eingeschalteter Dialog kein unabhängiger zweiter Melodiegenerator. Im gehaltenen Cmaj7-Kontrolllauf gelingen 12 Dialognoten / 3,91 %, während die katalogbasierten Beispiele keine geeignete Antwort finden.

Zusätzliche, für die bestätigte Anwenderkonfiguration **nicht zutreffende** Einschränkung: `!s.scene` sperrt die Melodie–Dialog-Übergabe bei eingeschaltetem Aufbau auch nach Ende der eigentlichen Aufbauphase. Das wurde nur dokumentiert, nicht verändert.

### Score: Die meisten vorgesehenen Wiederkehrfenster scheitern vor dem Dispatcher

`CompositionPolicy.h::MotifRecurrencePolicy` verwendet achtaktige Prüfungsfenster und mindestens zwei stille Takte. Hohe Intensität öffnet in diesen Beispielen 11 der 15 nachfolgenden Epochen; sie garantiert keine harmonisch spielbare Realisierung.

`ScoreEngine.h::motifOccurrence()` verlangt bei Score ohne Tonanpassung eine gemeinsame Transposition der gespeicherten Intervalle, passende Tonklassen während der vollständigen Notengates, zulässigen Umfang und genügend Zeit. Nicht geeignete Varianten fallen auf das Original zurück; scheitert auch dieses, bleibt der Plan leer.

| Score-Beispiel | zugelassene Wiederkehrfenster | spielbare Wiederkehrpläne | geplante / ausgegebene Wiederkehrnoten |
|---|---:|---:|---:|
| statisch .25/.85/.1 | 11 | 11 | 53 / 53 |
| statisch .5/.9/.75 | 11 | 5 | 25 / 25 |
| langsame Fahrt | 11 | 3 | 15 / 15 |
| schnelle Fahrt | 11 | 1 | 3 / 3 |
| Einführung, danach maximale Y/Z-Werte | 11 | 0 | 0 / 0 |

Die übrigen fünf Noten sind jeweils die tatsächlich gespielte Einführung. Für alle 54 durchgehend im Score-Modus laufenden korrigierten Messkonfigurationen stimmen gezählte geplante und ausgegebene Wiederkehrnoten überein. Hier werden keine bereits vorhandenen gültigen Pläne vom Dispatcher verschluckt.

Konkrete Harmoniediagnose bei Sekunde 16 im letzten Beispiel: Original-MIDI 76,72,69,76,81, Intervalle 0,-4,-7,0,+5. Die inzwischen ausgewählte Wendung **1014 „Verfolgung“** wechselt im Ein-Takt-Abstand unter anderem zwischen Mollakkorden im Tritonusabstand. Fünf geprüfte Platzierungen des Originals ergeben **null harmonisch gültige Transpositionen auch ohne Registerbegrenzung**. Der Umfang 60–84 ist dort nicht die Ursache. Das Modell lehnt die gesamte Figur einschließlich ihrer über Harmoniewechsel reichenden Notengates ab.

### Kontinuierliche Parameteränderungen

Blockweise XYZ-Änderungen löschen das eingeführte Material nicht und setzen den Liniencursor nicht pauschal zurück. Der Wiederkehrcache ist nach Epoche, Materialidentität, Ursprung und Fenster indiziert, nicht nach jeder XYZ-Bewegung. Ein leerer Plan wird daher innerhalb seiner achtaktigen Epoche nicht bei jedem späteren Harmoniewechsel erneut geprüft. Das kann weitere geeignete Gelegenheiten ungenutzt lassen.

Kontrolle: Bei bewegtem XYZ und eigener, unveränderter Cmaj7-Harmonik bleiben 58 Melodie- und 12 Dialogeinsätze möglich. Die Parameteränderungen selbst verursachen also keine generelle Einsatzblockade. Sie verändern aber die ausgewählte harmonische Umgebung; diese kann zum gespeicherten Original nicht mehr passen.

### Pop/Rock: anderer vorhandener Rollen- und Hookpfad

`ScoreEngine.h::muteSoloOk()` lässt die neue Hauptmelodie ausdrücklich nur in Score zu. Deshalb bleibt sie in Pop/Rock unabhängig von ihrer Checkbox still. Das ist kein Aktivierungsschwellen- oder Schedulerfehler.

Die Gegenstimme erreicht dagegen `counterLine()` → `leadHook()`. Kontinuierliche motorische Hook-Muster laufen ohne Score-Mindestpausen. Phrasenbezogene Hooks können den gemeinsamen Katalog und Wiederkehrplan verwenden; die bestehende Pop-Policy erlaubt harmonische Tonanpassung. Ein Wendungswechsel kann zwischen diesen beiden Hookfunktionen umschalten. Deshalb sind bei solchen Wechseln Pop-Zähler für früher vorgesehene Wiederkehrnoten nicht als reine Dispatcher-Verlustbilanz interpretierbar; der kontinuierliche Hookpfad kann inzwischen musikalisch zuständig sein. Pop/Rock ist außerdem nicht in jedem XYZ-Bereich durchgehend: der warme Kontrollfall erreicht rund 60 % Auslastung.

Im laufenden Genrewechsel Score → Pop bei Sekunde 120 setzt der Dialog sowohl vorher als auch nachher ohne gemessene Verzögerung ein: 230 Note-ons in den folgenden 60 s. Hauptmelodie: 0. Beim Rückwechsel zu Score gelten wieder dessen Vordergrund-/Motivregeln.

### Mute und Solo

Muting der vier Begleitrollen beseitigt die seltenen Score-Einsätze nicht. Bei normal durchlaufender, schon eingeführter Motivik liefern Begleitung verfügbar, Begleitung gemutet und beide melodischen Rollen solo dieselben melodischen Anschlagszahlen in den verglichenen Kontrollen. Die Begleitung ist für diese gültigen Motivpläne kein notwendiger Hilfstaktgeber.

Solo hat weiterhin Vorrang vor Mute; bei Aufbau können Mute/Solo auch die Wahl der zuerst verfügbaren Ebene beeinflussen. Das ist von der bestätigten Konfiguration Aufbau AUS zu trennen. Kanalteilung und verifizierte externe Patchfähigkeiten wurden nicht erfunden; gemessen sind die eindeutigen Standardkanäle.

## 4. Historische Einordnung

Die Score-Zahlen für die normalen Fahrten stimmen mit `17b15a4` überein: 58 / 20 / 8 Anschläge für statisch / langsam / schnell, unabhängig davon, ob Melodie oder die alleinige Gegenstimme das Motiv führt. Die geringe fortlaufende Aktivität stammt daher nicht primär aus der Scheduler-Migration. Diese verschlechterte zusätzlich den Einstieg mit leerem Material; genau dieser Fehler wurde korrigiert.

Version 2.1 besitzt keine eigenständige Hauptmelodie. Ihre Gegenstimme erzeugt in den Vergleichsfällen 272 / 302 / 422 Note-ons und etwa 100 % / 99,71 % / 99,85 % MIDI-Gate-Auslastung. Das ist ein Funktionsvergleich, keine Byte-Regression: Motivverfahren und Pop-Katalog unterscheiden sich. Der damalige lokale Linienanteil ist erheblich kontinuierlicher als die heutige vollständige Motivzuständigkeit mit Pausen und Eignungsprüfung.

## 5. Folgeschritte – nur Vorschläge

1. Musikalische Rollenpriorität an tatsächlich geplante Vordergrund-/Antwortfenster binden; eine aktive, aber auf lange Zeit unspielbare Melodie sollte die Gegenstimme nicht dauerhaft exklusiv sperren. Keine pauschale Notendichteerhöhung.
2. Die harmonische Realisierung gespeicherten Score-Materials gezielt untersuchen: Notengates an Akkordgrenzen, geeignete kurze vorhandene Figuren und begrenzte harmonische Anpassung. Originalmaterial unverändert erhalten; Ablehnungsgründe und Qualität getrennt prüfen. Die Pop-Anpassung nicht ungeprüft einschalten.
3. Leere Wiederkehrpläne bei tatsächlichen relevanten Harmoniewechseln begrenzt neu prüfen; gültige Pläne, Mindestpausen und Determinismus schützen. Reine Erhöhung der Auswahlwahrscheinlichkeiten löst die gezeigte Unvereinbarkeit nicht.
4. Genreabhängige Verfügbarkeit der Hauptmelodie und die fortdauernde Aufbau-Antwortsperre separat spezifizieren. Keine dieser Änderungen ist Bestandteil des Fixes.

## 6. Reproduktion und Prüfstand

`python scripts/analyze_melodic_activity.py --output <Verzeichnis>` erzeugt alle Langläufe und Note-event-CSVs. `--supplement` beschränkt auf Aufbau-, Genrewechsel- und Maximalwert-Diagnosen. Der Skriptpfad erstellt reine Offline-Headerkopien mit Freundzugriff für Messzustände; keine Produktionsschnittstelle und keine zweite Kompositions-Engine. `v2.1` kennzeichnet die fehlende Hauptmelodie als nicht verfügbare Rolle.

Die komplette Übersicht einschließlich Parameterkonfigurationen und Source-Prüfsumme liegt in `MELODIC_ACTIVITY_MEASUREMENTS.json`. Für alle 102 Vorher-/Nachher-Konfigurationen sind die vollständigen Begleit-MIDI-Prüfsummen identisch: Fläche, Bass, Tupfer/Stich und Arpeggio unverändert.

Abschlussprüfungen bestanden:

- 40/40 reguläre CTests; die vollständige Scheduler-Matrix mit 1.313 Vergleichsrenderings und 2.177 Blockgrößenvergleichen bleibt erfolgreich, einschließlich der unabhängigen 98 historischen Zeitkorrekturen.
- `Execution` nach Ergänzung der gesamten Fallback-/Achteltakt-/Loop-Testfälle nochmals bestanden. Der unveränderte `9a3cbad`-Header scheitert am neuen Kaltstarttest.
- Gezielter `ExecutionTests`-Lauf mit ASan/UBSan (`-O1 -g -fno-omit-frame-pointer -fsanitize=address,undefined`, `detect_leaks=0`) ohne Befund. Keine LeakSanitizer-Aussage.
- Echter, neu gebauter Processor-Test: 216 Live-/SMF-Vergleiche in 4/4, 3/8, 5/8 und 7/8; Großblockbilanz 872 Note-ons / 872 Note-offs, keine Verwaltungsfehler. Die Fallback-spezifischen kalten Sprünge werden separat in `ExecutionTests` geprüft; der SMF-Exporter bildet keine historische Hostautomation nach.
- 7/7 Paketprüf-Fixtures.
- 204 wiederholte Startmessungen, 336 Langläufe, 102 identische Begleit-MIDI-Vergleiche.
- Reproduktionsskript zusätzlich mit kurzem Supplementlauf gegen alle vier Source-Stände geprüft; Python-Syntaxprüfung und `git diff --check` bestanden.

Kein Windows-Neubuild, kein Push, kein Release. Keine GUI-, Profil-, Begleit- oder weiteren musikalischen Regeländerungen.
