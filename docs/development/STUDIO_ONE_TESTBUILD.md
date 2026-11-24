# STROMSCORE 2.2 DEV – Hörtest in Studio One Pro 8 (Windows x64)

Zeitbasis-/Scheduler-Abschluss: musikalischer Quellstand `bd119bc`, Branch
`develop/composition-core-prototype`. Der genaue gebaute Stand steht in BUILD.txt.
Die beiliegende MUSICAL_TIME_BASE.md dokumentiert die Migration und ihre Grenzen.
Dies ist ein privater Entwicklungsbuild, kein Release. Den exakten Paket-Commit nennt BUILD.txt;
im Plugin steht `v2.2 DEV <Commit>`. Numerische VST3-Version: 2.2.

## Herunterladen und installieren

Im zugehörigen erfolgreichen GitHub-Actions-Lauf **STROMSCORE 2.2 DEV Windows x64** unter
**Artifacts** das Paket `Stromscore-2.2-DEV-<Commit>-Windows-x64` herunterladen.
Das private Repository erfordert eine Anmeldung mit Repository-Zugriff. Das Artefakt bleibt
30 Tage verfügbar. Das äußere Actions-ZIP entpacken; darin liegen Installations-ZIP,
SHA-256-Datei, BUILD.txt und diese Anleitung. Auch das Installations-ZIP entpacken.

1. Studio One schließen. Eine vorhandene stabile `Stromscore.vst3` außerhalb aller
   VST3-Suchpfade sichern. Der Testbuild hat dieselbe Plugin-ID: stabile und DEV-Version
   nicht gleichzeitig in Suchpfaden installieren. Bestehende Songs für diesen Test kopieren.
2. Den **gesamten Ordner** `Stromscore.vst3` nach
   `C:\Program Files\Common Files\VST3\Stromscore.vst3` kopieren (gegebenenfalls Administratorrechte).
   Die innere Datei unter `Contents\x86_64-win` nicht einzeln herauskopieren.
3. Studio One Pro 8 starten und Plugins neu scannen. Falls Stromscore zuvor blockiert wurde,
   in der Plug-in-Verwaltung die Blockierung zurücksetzen und erneut scannen.
4. Einen neuen Test-Song öffnen, Stromscore als Instrument einsetzen und im Fenster die
   Kennung `2.2 DEV <Commit>` kontrollieren. Fehlt DEV, wurde die falsche Installation geladen.
5. Zum Zurückwechseln Studio One schließen, DEV-Ordner entfernen, gesicherte stabile Version
   wieder einsetzen und erneut scannen. Es gibt keinen Installer und keine Änderung am stabilen Download.

## Neun MIDI-Ziele anschließen

Stromscore erzeugt MIDI; externe Instrumente erzeugen den Klang. Für jedes benötigte Ziel
eine Instrumentenspur anlegen, deren Eingang auf Stromscore und den jeweiligen MIDI-Kanal
setzen und Monitoring einschalten. Nicht „Alle Kanäle“ auf sämtlichen Zielspuren verwenden.

| Ziel | Standardkanal |
| --- | ---: |
| Harmonie/Fläche lang | 1 |
| Harmonie/Fläche kurz | 2 |
| Bass lang | 3 |
| Bass kurz | 4 |
| Arpeggio | 5 |
| Tupfer | 6 |
| Stich | 7 |
| Dialog/Gegenstimme | 8 |
| Hauptmelodie | 9 |

Die Kanalwahl ist im Plugin je Ausgang änderbar. Zum Gegenprüfen Kanal 9 vorübergehend auf
15 setzen, die Melodie-Zielspur ebenfalls auf 15 stellen und anschließend beide zurücksetzen.
Ein Speichern/Schließen/Öffnen des Test-Songs muss Aktiv, Legato, Motiv und Kanalzuordnung erhalten.
Lang und kurz können verschiedene Patches benötigen. Für Melodie und Dialog zunächst klare,
tonhöhensteuerbare Sustain-Patches ohne Keyswitch-Zwang wählen, z. B. zwei unterscheidbare
Synthesizerklänge. Stich kann eine feste Triggernote (Vorgabe C1/MIDI 36) an ein Sample senden;
das ist kein Nachweis eines frei transponierbaren Instruments. Externe Patch-Fähigkeiten
werden nicht automatisch erkannt. Zunächst keine CC-Lautstärkesteuerung zuschalten.

## Gemeinsame reproduzierbare Grundeinstellung

- Song: **120 BPM, 4/4**, Beginn Takt 1; mindestens 48 Takte Platz.
- Plugin: **Score**, **Aufbau AUS**, **Fahrt AUS**, Szenenlänge **0/unbegrenzt**,
  „Szene beenden“ AUS, Unruhe **0 %**, Färbung **50 %**, Intensität **70 %**, Wurf **3**.
- **Wurf 3** nötigenfalls über die Plugin-Parameter-/Automationsliste von Studio One einstellen;
  „Neu würfeln“ wählt keinen bestimmten Wurf. Danach vor dem Test stoppen und neu starten.
- Tonart **C**, Akkorde **Eigene Folge**: Slot 1 **Cmaj7, 4 Takte**, Slot 2 **Cmaj7, 4 Takte**,
  übrige Slots leer. Das ergibt eine achttaktige Phrase; einzelne GUI-Slots sind auf vier Takte begrenzt.
- Abwechslung **0 %**, Durchgänge AUS. Oktaven Normal; Melodieumfang zunächst MIDI **60–84**.
- Für jeden Vergleich stoppen, zum Songbeginn zurückkehren und neu starten. Nicht während
  einer laufenden Einführung umschalten: Ein Szenenneustart leert das Motivgedächtnis.
- Instrumenten-Release zunächst kurz genug halten, um komponierte Gates und Pausen zu beurteilen.
  Lange Hallfahnen oder Sample-Releases sind keine zusätzlichen MIDI-Noten.

## Fünf Hörtests

| Test | Einstellungen gegenüber der Grundeinstellung | Laufzeit und Erwartung |
| --- | --- | --- |
| 1. Klassisches Underscoring | Melodie **Aktiv AUS**. Gegenstimme **Motiv AUS**. Alle Solo-Schalter aus; Fläche und Bass an, Arp nach Geschmack Auto. | 32 Takte / 64 s. Begleitung ohne neue Hauptmelodie oder Melodie–Dialog-Übergabe. |
| 2. Gegenstimmenmotiv | Melodie **Aktiv AUS**. Nur Gegenstimme solo; dort **Motiv EIN**, **Legato EIN**. | Mindestens 40 Takte / 80 s. Einführung zu Beginn; danach flexible, harmonisch geprüfte Wiederkehr mit Mindestpausen. Zeitpunkt und Variante hängen vom musikalischen Kontext ab. |
| 3. Hauptmelodie | Melodie **Aktiv EIN**, **Motiv EIN**, **Legato EIN**; nur Melodie solo. | Mindestens 40 Takte / 80 s. Auf Kanal 9: Einführung, Pause, flexible Wiederkehr und geeignete Varianten. Die reguläre Gegenstimme pausiert. |
| 4. Gezielte Motivantwort | Melodie **Aktiv EIN**; **beide Motivschalter EIN**. Melodie und Gegenstimme beide solo; beide Zielspuren monitoren. | 48 Takte / 96 s. Kurze Schlussfigur auf Kanal 8 in einem ausdrücklich reservierten, geeigneten Antwortfenster. Keine Antwort in jeder Phrase und keine führende Melodie gleichzeitig; ungeeignete Antworten entfallen. |
| 5. Schaltervergleich | Test 3 je einmal mit Melodie-Legato EIN/AUS neu starten, dann mit Melodie-Motiv EIN/AUS. Anschließend analog Test 2 für die Gegenstimme. | Je 40 Takte / 80 s für Motivvergleiche; Legato ist schon in der Einführung vergleichbar. Motiv AUS erzeugt weiterhin harmonische Linien, ohne geplante Wiederkehr. Die Schalter der anderen Stimme dürfen das Ergebnis nicht steuern. |

Zusatz zu Test 4: Beide Motivschalter müssen eingeschaltet sein. Die Antwort übernimmt die
letzten zwei bis drei tatsächlich eingeführten Töne, nicht das ganze Thema. Rhythmus und
Intervalle bleiben erhalten; das Register darf transponiert sein. Sie darf ausbleiben, wenn
die gesamte Figur nicht in eine unveränderte Harmonie, einen geeigneten Tonumfang oder die
Spielweise passt. Die Cmaj7-Einstellungen bieten einen harmonisch stabilen Testkontext; die konkreten
Antwortzeitpunkte sind seit der flexiblen Wiederkehrplanung nicht mehr fest zugesagt.

Die bisherige Gegenstimme–Arp-Frage–Antwort lässt sich separat prüfen: Melodie AUS,
Gegenstimme-Motiv EIN, Arp-Figur **Zelle**, Gegenstimme und Arp an, Aufbau AUS, 4/4.
Zu einer geeigneten Motivfrage wird ein nachfolgendes, getrenntes Arp-Antwortfenster reserviert. Bei aktiver
Hauptmelodie läuft dieser ältere Dialog nicht parallel zur neuen Motivübergabe.

## Legato, Transport und Grenzen

Melodie-Legato verbindet monophone Notengates, ohne zusätzliche Notenüberlappung.
Legato AUS lässt nach Möglichkeit eine Sechzehntel Abstand; sehr kurze Noten bleiben
mindestens eine Sechzehntel lang. Das schaltet keine bibliothekseigenen Legato-Samples
oder Keyswitches um. Aufgezeichnete Pausen und Variationskürzungen bleiben erhalten.
Die bisherige Gegenstimme kann im regulären Linienmodus überlappendes Legato verwenden;
die neue kurze Antwort bleibt monophon.

Zum Transporttest nach erfolgter Einführung auf Takt 17 springen und einen Loop Takt 17–25
mehrmals abspielen. Keine hängenden Noten; Wiederholungen sollen bei gleichen Einstellungen
gleich bleiben. Stoppen und am Songbeginn neu starten muss eine neue Einführung ergeben.
Ein frischer Einstieg mitten im Song kann kein zuvor niemals gespieltes Motiv rekonstruieren.
Für den ersten Hörtest deshalb immer am Anfang starten. Parameterautomation während des
Songs wird durch einen späteren Export nicht rückwirkend rekonstruiert.

Exportvergleich: mit unveränderten Einstellungen vom Anfang spielen/aufnehmen und eine
32-Takt-MIDI-Datei aus Stromscore exportieren. Gegenstimmenantwort und Wiederkehr müssen
zur Aufnahme passen. Die GUI bietet derzeit 8/16/32 Exporttakte; längere Verläufe
lassen sich über die Live-MIDI-Aufnahme überprüfen.

Bitte beim Hören notieren: DEV-Commit, Testnummer, Patch, Takt und Auffälligkeit (z. B.
„Takt 10 Antwort zu laut“, „Variante Takt 33 nicht erkennbar“). Automatisierte Prüfungen
belegen Struktur und MIDI-Korrektheit, nicht die künstlerische Qualität im Hörspielkontext.
Studio One Pro 8 und die eingesetzten Klangbibliotheken benötigen diese praktische Abnahme.
