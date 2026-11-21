# STROMSCORE – Audio Drama Underscore Inspirator

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="docs/logo-dunkel.png">
  <img src="docs/logo-hell.png" alt="Stromschlag Audio" height="64">
</picture>

VST3-Instrument für Hörspiel-Produktion. STROMSCORE ist als Inspiration gedacht: Es liefert einen Ausgangspunkt, den du auf deinen
eigenen Instrumenten weiter bearbeitest und veredelst. Dafür erzeugt es nach festen Regeln Musik zur Untermalung und gibt sie als **MIDI** aus:
ruhige Akkordflächen, Bass, gebrochene Akkorde, einzelne Farbtöne und Akzente. Du wählst Tonart und Modus und regelst mit **VERLAUF**,
wie viel gleichzeitig passiert. Jede der fünf Ebenen hat ihren eigenen MIDI-Kanal und lässt sich so von einem eigenen Instrument
spielen. Die Klänge kommen aus deinen eigenen Instrumenten, das Plugin liefert nur die Noten.

Es läuft im Takt des Projekts. Gleiche Einstellungen ergeben immer dieselben Noten, auch nach einem Sprung oder bei einem Loop.

**Es verwendet keine KI.** STROMSCORE arbeitet mit festen Regeln, nicht mit trainierten Modellen und nicht mit fremdem Material. Die
Grundlage ist der Stil, den ich über Jahre für meine Hörspiele entwickelt habe, geprägt von dem, was ich an großen Filmkomponisten
schätze. Das Ziel: Szenen so zu untermalen, wie ich es selbst tun würde, und das einfacher zu machen. Mit jeder Version fließt
mehr davon hinein, 0.3 ist noch ein früher Stand.

**Stand 0.3:** früher Test, ob die Noten sauber auf eigene Instrumentenspuren ankommen. Stimmungsverläufe, Stilvorlagen und
Ostinato-Muster folgen.

**⬇ Download (Windows · VST3):** https://github.com/StromschlagProductions/Stromscore-vst/releases/latest

## Warum es dieses Plugin gibt

Für die Musik zu meinen Hörspielen schreibe ich viel selbst. Was dabei oft Zeit kostet, sind nicht die Einfälle, sondern das
Ausprobieren: eine Fläche, ein Bass, ein Puls darüber, und dann das Ganze noch einmal in einer anderen Spannung. STROMSCORE
nimmt mir diesen Grundaufbau ab, damit ich mich auf Szene, Stimmung und Feinarbeit konzentrieren kann. Es ist mein Versuch, die
Art, wie ich selbst untermale, zu automatisieren, ohne dass es nach Baukasten klingt. Die Noten landen auf
meinen eigenen Instrumenten, so klingt es nach meinem Projekt und nicht nach einem Plugin.

*STROMSCORE soll das eigene Komponieren nicht ersetzen. Es macht Spaß und ist lehrreich, Flächen, Bässe und Figuren selbst zu
schreiben und zu hören, wie Harmonie, Rhythmus und Dichte zusammenwirken. Ich bin dankbar, dass ich diesen Weg selbst gegangen
bin, auch wenn er manchmal umständlich war. STROMSCORE soll nur die technische Umsetzung im Alltag einfacher machen.*

– Lars Eickstädt, Stromschlag Audio

## Oberfläche

| Dunkel (Standard) | Hell |
|---|---|
| ![Dunkle Oberfläche](docs/oberflaeche-dunkel.png) | ![Helle Oberfläche](docs/oberflaeche-hell.png) |

Der Umschalter oben rechts wechselt den Look, die Wahl wird mit dem Projekt gespeichert. Der **?**-Knopf öffnet die Hilfe, über
jedem Regler erscheint beim Darüberfahren ein kurzer Hinweis. Die Oberfläche lässt sich am rechten unteren Fensterrand stufenlos
von 50 % bis 300 % vergrößern oder verkleinern.

## Einrichten in Studio One

1. Eine Instrumentenspur mit **Stromscore** anlegen.
2. Für jede Ebene, die du hören willst, eine eigene Instrumentenspur mit deinem Instrument anlegen.
3. Bei jeder dieser Spuren als Eingang Stromscore wählen und den passenden MIDI-Kanal einstellen: Fläche 1, Bass 2, Arp 3, Farbe 4, Akzente 5.
4. Spuren auf Monitor schalten, Wiedergabe starten.

Zum Weiterarbeiten kannst du die Ausgabe in Studio One direkt als MIDI mitschneiden: Instrumentenspur auf Aufnahme, Eingang Stromscore (Kanal wählen), Wiedergabe starten. Gleiche Einstellungen ergeben immer dieselben Noten.

Ohne eigene Instrumente hilft **VORHÖREN**: ein einfacher Testklang direkt aus dem Plugin.

## Regler (alle automatisierbar)

| Regler | Was er macht |
|---|---|
| TONART | Grundton. Alle Noten bleiben in der gewählten Tonleiter. |
| MODUS | Moll, Dur, Dorisch, Phrygisch oder Lydisch, mit je einer Folge aus vier Akkorden (jeder Akkord zwei Takte). |
| VERLAUF | Von ruhig (0 %) bis dicht (100 %). Ebenen im Modus Auto setzen nacheinander ein (Arp ab 25 %, Farbe ab 50 %, Akzente ab 75 %). Der Bass wird lebendiger, der Arp schneller. |
| VARIATION | 1 bis 16: kleine Abweichungen derselben Einstellung, reproduzierbar. |
| VORHÖREN | Einfacher Testklang im Plugin. |

## Die fünf Ebenen

Jede Ebene hat einen Schalter mit drei Stufen: **Aus** (schweigt), **Auto** (setzt bei ihrer VERLAUF-Stufe ein) und **An** (spielt immer).
Bei Fläche, Bass und Arp bestimmt ein zweiter Schalter, ob die Ebene **den Akkorden folgt** oder **auf dem Grundakkord bleibt**.
So lassen sich zum Beispiel ein durchlaufender Arpeggio-Ostinato über wechselnden Flächen oder ein Bass auf dem Grundton unter
wechselnden Akkorden einstellen. Die Ebenen lassen sich frei mischen.

| Ebene | Kanal | Was sie spielt |
|---|---|---|
| Fläche | 1 | Gehaltene Akkorde, mit steigendem VERLAUF dichter und lauter |
| Bass | 2 | Grundton: erst gehalten, dann als Puls, ab 60 % in Achteln |
| Arp | 3 | Gebrochener Akkord in Achteln, ab 60 % in Sechzehnteln |
| Farbe | 4 | Ein hoher Ton über dem Akkord |
| Akzente | 5 | Tiefer Schlag bei jedem Akkordwechsel |

## Installation (Windows)

ZIP entpacken, DAW schließen und den vollständigen Ordner `Stromscore.vst3` nach `C:\Program Files\Common Files\VST3` kopieren.
Danach in der DAW die Plugins neu einlesen.

## Versionen

- **0.1** – erster Test: Noten-Generator mit fünf MIDI-Kanälen, TONART, MODUS, VERLAUF, VARIATION und VORHÖREN.
- **0.3** – Ebenen einzeln ein- und ausschaltbar (Aus / Auto / An), Fläche, Bass und Arp wahlweise den Akkorden folgend oder auf dem Grundakkord bleibend. Hängende Töne nach Stopp behoben. Neuer Untertitel „Underscore Inspirator“.
- **0.2** – Hinweis zur Herkunft der Musik (keine KI, feste Regeln, Grundlage ist mein eigener Stil) in Hilfe und README.

Alle Release-Hinweise: `docs/releases/`.

## Aufbau

- `Source/ScoreEngine.h`: Noten-Generator, reines C++ ohne JUCE. Die Ausgabe hängt nur von der Projektposition und den Einstellungen ab.
- `Source/PluginProcessor.*`: Plugin-Hülle, MIDI-Ausgabe, Parameter.
- `Source/PluginEditor.*`: Oberfläche und Hilfe.
- `Tests/`: Tests für Engine und Plugin. `tools/screenshot.cpp`: erzeugt die Oberflächenbilder aus der echten Oberfläche.

## Qualität und Prüfung

Bei jeder Änderung baut GitHub das Plugin unter Windows, führt die Regressionstests aus und prüft es mit pluginval (Strictness 8).
Die Noten-Engine läuft zusätzlich unter Linux mit Speicher- und Fehlerprüfern. Siehe `docs/CI.md`.

## Hinweis

Stromscore wird ohne Gewähr bereitgestellt. Es ist ein Werkzeug für meine eigene Hörspielproduktion unter Windows mit Studio One. Das
MIDI-Routing hängt vom Host ab; andere Hosts sind nicht getestet. Bei Problemen hilft ein Issue mit kurzer Beschreibung.
