# Aktueller Hörschritt: John Carpenter P1

Im bestehenden **SCORE → KOMPONIST → John Carpenter** wählen. Zunächst 4/4,
D, 100 BPM, Aufbau/Fahrt AUS, unbegrenzte Wiedergabe, Auto-Spielweisen und Follow
EIN; Hauptmelodie zunächst AUS. GS arbeitet hier als zweiter Sequencer.
Standardkanäle: LF1/KF2/LB3/KB4/AR5/TU6/ST7/GS8/HM9. Geeignete Lang-/Kurz-Patches
in der DAW verwenden; ST im festen Modus mit Standardtaste36.

- Drone/Bassfigur: X/Y/Z = 0,25/0,30/0,20; zunächst AR/GS muten.
- Zwei Sequencer: 0,30/0,55/0,30; AR/GS einschalten, Variation3 testen.
- Pulsfreies Klangfeld mit Echo: 0,40/0,15/0,10; Bass/AR/GS muten, LF/TU hören.
- Melancholisch: 0,70/0,35/0,20.
- Intensive Spannung: 0,20/0,90/1,00; leise abhören und passende kurze Patches wählen.
- Anschließend HM mit Motiv einschalten und freie XYZ-Fahrten vergleichen.

Pro Position 64, besser 128 Takte (rund 2:34/5:07 bei 100 BPM). Die neue Figurenstrategie
ist zunächst 4/4-spezifisch; andere unterstützte Taktarten verwenden die sichere
bisherige Ausgestaltung des Carpenter-Harmoniematerials. ST wird im neuen Pfad
nicht als tonale Ersatzstimme ausgeführt. Bei geteilter Kanalbelegung können
unabhängige Figuren entfallen. Noch keine musikalische Abnahme von Carpenter P1.

Vollständige Anleitung und echte MIDI-Hörstudien liegen im Repository unter
`docs/research/john-carpenter/P1_STUDIO_ONE.md` und `P1_MIDI_LISTENING.zip`.
Die folgenden allgemeinen Installations-/Transporthinweise gelten weiter.

---

# STROMSCORE 2.2 DEV – Morricone P1: Hörtest in Studio One Pro 8

Dieser Entwicklungsbuild ergänzt die gemeinsame Oberstimmenbindung und einen
begrenzten Morricone-SCORE-Prototyp. Die genaue Commit-ID steht in `BUILD.txt`
und im Plugin als `v2.2 DEV <Commit>`. Kein offizielles Release.

## Installation

Das GitHub-Actions-Artefakt herunterladen und das äußere ZIP entpacken, danach
`Stromscore-2.2-DEV-<Commit>-Windows-x64-VST3.zip` entpacken. Studio One schließen,
die bisherige Installation außerhalb der Suchpfade sichern und den **gesamten
Ordner** `Stromscore.vst3` nach `C:\Program Files\Common Files\VST3\` kopieren.
Neu scannen und DEV-Kennung prüfen. Stabile und DEV-Version haben dieselbe
Plugin-ID: nicht gleichzeitig installieren. Bestehende Songs für den Test kopieren.

## Grundeinstellung

- 4/4, D, 100 BPM; SCORE, KOMPONIST **Ennio Morricone**.
- Aufbau AUS, Fahrt AUS, unbegrenzte Wiedergabe; Fläche/Bass Auto,
  „Folgt Akkorden“ für beide EIN. Vorhören AUS, Host-Wiedergabe verwenden.
- Zunächst Arpeggio, Akzente, Hauptmelodie und Gegenstimme muten. Die vorhandenen
  Lang-Ausgänge der Fläche und des Basses mit geeigneten gehaltenen Klängen belegen.
  Keine neue Kanalzuordnung: Fläche lang Kanal 1, Bass lang Kanal 3.
- Ein Sustain-fähiger Patch ist notwendig, um MIDI-Bindungen auch akustisch zu hören.
  Ein ausklingendes Klaviersample verhält sich anders als gehaltene Streicher.

## Vier kurze Durchläufe

| Situation | Färbung X | Intensität Y | Unruhe Z | Worum es geht |
|---|---:|---:|---:|---|
| Wehmütige Kreisbewegung | 0,40 | 0,35 | 0,20 | Moll-add9, ♭VI-maj7, Mollsubdominante; gemeinsame Töne bleiben liegen. |
| Helle plagale Terzkette | 0,75 | 0,30 | 0,15 | Dur-add9, vi-m7, IV-maj7; emotionale Umfärbung ohne Pflichtmelodie. |
| Dur/Moll-Umfärbung | 0,60 | 0,30 | 0,25 | Dur-add9 gegen Moll-6-Subdominante; liegende None über wechselnder Funktion. |
| Gemeinsamton-Kette | 0,45 | 0,30 | 0,20 | H051: Moll-add9 → ♭VII-add9 → ♭III-maj7 → ♭VI-maj7. |

Für einen gezielten Quellentest „Abwechslung“ zunächst auf 0 stellen. Die Anzeige
kontrollieren; in der unmittelbaren Nähe kann bei anderer Variation eine andere
passende Folge erscheinen. Danach Abwechslung erhöhen, mehrere Variationen und
langsame XYZ-Fahrten probieren. Pro Durchlauf mindestens **32 Takte** hören
(bei 100 BPM etwa 1:17 Minuten), für Entwicklung bei konstantem XYZ **128 Takte**
(etwa 5:07 Minuten). Die Harmonie darf sich auch bei unbewegtem Feld weiterentwickeln.

Anschließend Melodie und Dialog einzeln sowie gemeinsam aktivieren und deren
Motivschalter testen. Sie nutzen die bisherigen gemeinsamen Funktionen; neue
Morricone-Motivvorlagen sind in P1 noch nicht enthalten. Arpeggio und Akzente sind
optional. Manuelle rhythmische Flächenspielweisen dürfen ausdrücklich neu anschlagen;
die kontinuierliche Oberstimmenbindung gilt für die geeignete Langfläche.

## Vergleich und Rückmeldung

Neutral, Barry und Williams bei identischen Einstellungen und **denselben Patches**
gegenhören. Bestehende Profile sollen ihre bisherige musikalische Funktion behalten.
Nach Profilwechsel im Lauf, Stop/Neustart, Seek und einem Loop auf hängende Noten
achten. Rückmeldung besonders zu gehaltenen Farbtönen, Bassbewegung, harmonischen
Übergängen, Variation bei konstantem XYZ und zur Eignung ohne Vordergrundstimmen.

P1 ist lyrisch ausgerichtet. Sehr intensive/unruhige Randbereiche sind harmonisch
noch schwach besetzt; sie besitzen noch keine vollständige Morricone-Dramaturgie.
EM-S052 dient nur als musikalische Orientierung: keine Lolita-Transkription,
kein vollständiger Nachbau der Studie und kein Import ihrer ungeklärten H053.
