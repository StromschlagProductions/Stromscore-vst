# Technische Prüfung Stromscore 1.9

Ausgangspunkt: v1.8, Commit `bda8c32e98a346f81628cc4f1ed215ebf4e8d29f`. Umsetzung und Prüfung am 22. November 2026. Die Hersteller-/Plugin-Codes `Strm` / `Stsc` und der Ordnername `Stromscore.vst3` bleiben erhalten.

## Regressionen und Zuordnung zum Audit

| Befund | Änderung | Nachweis im Test |
|---|---|---|
| S01 Controller-Zeitposition | MIDI-Eingang wird an seinen Samplegrenzen verarbeitet. GUI-/Host-Publikation erfolgt anschließend über den Nachrichtenthread. | Gleiche zeitgestempelte Notenströme bei 64, 512 und 8192 Samples; CC innerhalb eines Blocks. |
| S02 Fahrt-Abbruch | Erreichten Punkt beim Ausschalten atomar festhalten und bis zur Übergabe verwenden. | Abschalten aus separatem Automationsthread, nächster Audioblock vor GUI-Nachführung. |
| S03 Export-Schluss | Harten Szenenendpunkt und Ausklang mitrendern; keine Null-Längen-Schlussnoten. | Schluss-Note-ons bei MIDI-Tick 30720 und Note-offs danach im Acht-Takt-Export. |
| S04 Notenbesitz | Getrennte Ansprüche je Ausgang; physisches Note-off erst nach Ende des letzten Anspruchs. | Fläche/Bass auf Kanal 1 teilen C; Fläche muten, C bleibt bis Bassende erhalten. Gesamte Notenbilanz und gemeinsame Kanäle. |
| S05 CC-Wechsel | Controller-ID-Wechsel und Aus-/Einschalten setzen den Sendecache zurück. | Ausdruck von 11 auf 21 umstellen, neuer Controller wird unmittelbar am nächsten Musikraster gesendet. |
| S06 Echtzeit-Heap | MIDI-Arbeitspuffer vorbereiten und wiederverwenden; lange Nicht-Noten-/Nicht-CC-Nachrichten werden nicht kopiert. MIDI-CC-Eingang ruft keine Host-Listener im Audiopfad mehr auf. | Linux überwacht zusätzlich `malloc/realloc/calloc`, nicht nur `operator new`; wiederholte Durchleitung, Einzelton-Vorhören und MIDI-Controller ohne Allokation in den vorbereiteten Testblöcken. |
| S07 Host-Takt | Alte Begrenzung auf 4–32 Sechzehntel entfernt. | Unter anderem 9/4, 1/8, 1/16, 16/2 und 16/1. |
| S08 Legato | Vorige Gegenstimmen-Note endet tatsächlich eine Sechzehntelnote nach dem nächsten Anschlag. | Positive Überlappung von 6000 Samples bei 48 kHz/120 BPM, statt nur Note-on vor Note-off am selben Sample. |
| S09 Vorhördauer | Ersten Block mitzählen, Note-off am exakten Sample. | 19200 Samples bei 48 kHz für Blockgrößen 512, 8192, 32768. |
| S10 Notenparser | Studio-One-Oktavkonvention und internationale Notennamen rückwärts einlesen. | Alle 128 formatierten Notennamen rundlaufen; zusätzliche Db3/B3-Eingaben. |
| S11 Ereigniskapazität | Große Host-Blöcke in höchstens 512 Samples teilen; zusätzliche Notabschaltung bei internem Überlauf. | 65536 Samples, 8 kHz, 300 BPM, dichte Muster und CCs: vollständige Notenbilanz. |
| R01 Threadzugriffe | Tempo atomar, Takt als gemeinsames atomares Zahlenpaar; atomare Übergabe-/Reset-Anforderungen, Generator-/Preview-Reset im Audiopfad. | Funktionaler Automationsthread-Test und State-Roundtrip. Kein allgemeiner ThreadSanitizer-/Host-Race-Freiheitsnachweis. |

## Musikalische und Bedienungsregressionen

- Alle 18 Akkordqualitäten behalten bei 5 % Intensität ihre vollständigen Tonklassen, jeweils normal und beim schüchternen Einstieg, mit niedriger und hoher Unruhe. Dieser Test läuft ausdrücklich **ohne CC-Ausgabe**.
- Explizite Mollsept-/Nonenqualitäten bleiben auch bei Unruhe erhalten; einfache Dreiklänge können weiterhin um Spannungstöne erweitert werden.
- CC-Arbeitsbereiche werden relativ abgebildet. Test für Dynamik 100–127 und getrennten Ausdruck; der weiche Einstieg kann Ausdruck 0 senden, ohne den Dynamikbereich abzusenken.
- Drahtseil enthält die tatsächlich in einem Register fallende A–G♯–G–F♯-Stimme über festem Bass (in C als Bezugstonart).
- Alle neun neuen Pop-Rock-Wendungen sind an ihrer Feldposition erreichbar, haben acht Takte, verschiedene Gegenfiguren, ausgeglichene Note-on/off-Bilanzen und identische Notenzeitpunkte bei unterschiedlichen Blockgrößen.
- Alle Wendungen besitzen Info-Daten; die Anzahl wird beim Kompilieren geprüft. Eigener Akkordeditor bietet sämtliche 18 internen Akkordqualitäten an.
- Neue CC-Bereiche überstehen den State-Roundtrip. Beim Laden/Reset werden klingende Noten im folgenden Audioblock aufgeräumt.
- Keyboard-Durchleitung und Einzelton-Vorhören werden bei Bypass auch auf Kanal 16 beendet, wenn dieser nicht zu den Generator-Kanälen gehört. Reset räumt alte Ansprüche vor neuen Keyboard-Noten auf.
- Exportdateien überschreiben einander nicht; Schreibfehler führen zu keinem vorgetäuschten erfolgreichen Drag-and-drop.

## Prüfläufe

Die vollständigen Prüfläufe werden vor der Veröffentlichung ausgeführt. Der Windows-Releaseworkflow veröffentlicht nur nach erfolgreichen Regressionen, pluginval Strictness 8, Versionsprüfung und ZIP-Prüfung. Die zugehörigen Actions-Protokolle sind über den Release-Commit aufrufbar.

Lokal bestanden: vollständige Engine-/Prozessortests unter Linux/Xvfb (CTest 2/2), C-Heap-Überwachung, Engine mit AddressSanitizer/UndefinedBehaviorSanitizer und pluginval Stufe 8 (Exitcode 0, Abschluss SUCCESS). Zusätzlich bestanden sieben Release-Prüfer-Tests für ein gültiges Paket und die Ablehnung von Wrapper-Verzeichnis, doppelten Pfaden, verschachtelter ZIP, Pfadtraversierung, falscher Architektur und falscher Version. Die Bilder werden mit dem echten JUCE-Editor erzeugt. Der lokale Sanitizerlauf verwendet `detect_leaks=0`, weil LeakSanitizer in dieser Ausführungsumgebung nicht zuverlässig unterstützt wird; ASan/UBSan bleiben aktiv. Der GitHub-Linux-Sanitizerlauf verwendet diese lokale Ausnahme nicht.

## Praktische Grenzen

Die Tests belegen MIDI-/Steuerungsfunktionen und technische Stabilität der geprüften Fälle. Es hat **keine subjektive Hörbewertung mit den externen Orchester-, Gitarren- oder Synth-Patches des Auftraggebers** stattgefunden. Der einfache Vorhörklang ist dafür kein Ersatz. Die neue musikalische Umsetzung ist deshalb nicht als klanglich abgenommen zu verstehen.

Tonumfang, Artikulation, Polyphonie, Dynamikbelegung und Klangbalance der externen Instrumente bleiben Aufgaben der DAW-Vorlage. Besonders Flächen benötigen polyphone Patches. [Praktische Routing-Vorlagen](ORCHESTRIERUNG.md).

Der Host-Takt arbeitet mit Zählern 1–16 und Nennern 1, 2, 4, 8, 16 auf dem Sechzehntelraster. Andere Nenner werden auf 4 zurückgeführt; für solche Projekte einen unterstützten festen Takt wählen. Walzer benötigen eine passende 3/4-Einstellung. Dreiergruppen in bestehenden Kaskaden sind keine zusätzlichen echten 3:2-Tuplets. Durchkomponierte Taktwechselpläne, eigenständige Shepard-Schichten, automatische Filterfahrten externer Instrumente sowie eigene Echo-/Wolken-/Ganzfolgen-Rückungsalgorithmen sind weiterhin Forschungs-/Ausbauideen aus dem Katalog und werden in dieser Version nicht als vorhandene Spezialverfahren ausgegeben.

Szenenstart und Export folgen der dokumentierten bisherigen Entscheidung: neuer Wiedergabestart = neue Szene; Fahrt-Ankunft/Abbruch = neuer Punkt A. Ausschnittexporte sind dadurch nicht automatisch identisch mit einem früheren Gesamtdurchlauf. Für festgeschriebene Musik MIDI aufnehmen.

Homepage und Plugin-Gesamtbundle werden nicht erweitert.
