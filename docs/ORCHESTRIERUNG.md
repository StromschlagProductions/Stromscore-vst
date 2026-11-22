# Praktische Routing-Vorlagen

Stromscore gibt MIDI aus. Speichere die folgenden Rollen als DAW-Vorlage mit deinen konkreten Instrumenten. Die Vorschläge sind Startpunkte, keine automatisch geprüfte Library-Erkennung. Eine echte Klangbalance ist erst mit den geladenen Patches beurteilbar.

## Orchester

| Kanal | Ausgang | Geeigneter Startpunkt | Darauf achten |
|---|---|---|---|
| 1 | Fläche lang | Polyphones Streicher-Ensemble / weiche Orchesterfläche | Alle Akkordtöne müssen gleichzeitig spielbar sein. Ein monophones Solo-Legato-Patch verschluckt Akkordstimmen trotz korrekter MIDI-Ausgabe. |
| 2 | Fläche kurz | Ensemble-Spiccato/Staccato oder kurze Blechakkorde | Eigenes Kurz-Patch statt langer Artikulation mit kurzen MIDI-Noten. |
| 3 | Bass lang | Tiefe Streicher / Kontrabass, lange Artikulation | Tonumfang, reale klingende Oktave und CC-Belegung prüfen. |
| 4 | Bass kurz | Kurze tiefe Streicher oder Klavier | Auf genügend kurze Freigabe der Töne achten. |
| 5 | Arp | Harfe, Celesta, Pizzicato, artikulierte Holzbläser | Grenzen auf spielbaren Patchbereich setzen; sehr enge Grenzen können Töne zusammenfalten. |
| 6 | Tupfer | Celesta, Glockenspiel, kurze Holzbläser | Eigenständige hohe Einwürfe, genügend Abstand zur Gegenstimme. |
| 7 | Stich | Pauke / tiefes perkussives Sample | Modus Fest und passende MIDI-Taste; bei tonalem Instrument Modus Akkord. |
| 8 | Gegenstimme | Solo-Horn, Cello, Oboe | Legato überlappt um eine Sechzehntelnote; passend zum Patch ein-/ausschalten. |

Für gehaltene, CC-gesteuerte Orchesterinstrumente kann Dynamik 100–127 bei Ausdruck 60–127 ein sinnvoller persönlicher Arbeitsbereich sein. Für einen leiseren Klangcharakter darf der Dynamikbereich tiefer liegen. CC1 steuert nicht in jeder Library Dynamik. Ausdruck muss einem Lautstärkeregler entsprechen, damit Ein-/Ausblendungen funktionieren. Anschlaginstrumente brauchen oft gar keine CC-Steuerung.

## 80er Band / Synth

| Rolle | Startpunkt |
|---|---|
| Fläche lang | Polyphoner analoger Synth / weicher Gitarrenteppich |
| Fläche kurz | Clean-Offbeat-Gitarre, Palm-Mute-Patch, kurze Synth-Brass-Akkorde |
| Bass lang/kurz | E-Bass oder Sequencer-Bass mit passender Artikulation |
| Arp | Saubere E-/Akustikgitarre oder Sequencer-Synth |
| Tupfer/Stich | Kurze Brass-/Synth-Antworten; gezieltes Sample über Stich Fest |
| Gegenstimme | Lead-Synth, Lead-Gitarre oder Sax-/Flöten-Patch |

Schlagzeug kommt separat dazu. Der Notengenerator steuert keine Amp-Effekte, Filter, Fairlight-Samples oder Gitarrentechniken im geladenen Instrument automatisch an. Diese Klangentscheidungen liegen in der DAW-Vorlage. Erst die tatsächlichen Patches machen aus der Notenrolle die gewünschte Instrumentierung.

## Reproduzierbare Cues

Einen festen Szenenstart verwenden, Einstellungen im Projekt speichern und die erzeugten MIDI-Spuren aufnehmen. Der MIDI-Dateiexport startet aus den aktuellen Einstellungen eine neue Szene ab Takt 1; er rekonstruiert keine vorherige Live-Fahrt oder zukünftige Host-Automation. Nach einer Fahrt wird der erreichte Punkt zu A. Für eine unveränderte Wiederholung das Projekt/die Ausgangseinstellungen wiederherstellen oder das aufgenommene MIDI verwenden.
