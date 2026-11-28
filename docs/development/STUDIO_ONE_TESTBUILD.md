# Aktueller DEV-Test – Echtzeit-Performance

Musikalische Referenz bleibt **b969932**. Dieser Build verändert weder das Dark-Synth-Vokabular noch die übrigen musikalischen Profile. Die Dark-Synth-Hörabnahme bleibt offen. Details und vollständige Messdaten stehen in `PERFORMANCE.md` und `realtime-performance/` im Paket.

Studio One schließen, bisherigen VST3-Ordner sichern und durch die Fassung aus dem inneren DEV-VST3-ZIP ersetzen. Gleiche Plugin-ID: beide Versionen nicht parallel installieren. Danach bei Bedarf neu scannen.

Für den technischen Vergleich dieselbe Szene und Instrumentierung verwenden, zunächst 48 kHz, 4/4, D, 100 BPM, Aufbau/Fahrt AUS und unbegrenzte Wiedergabe. Beide motivischen Stimmen für den Belastungstest aktivieren. Alle Profile sowie POP/ROCK prüfen; für eine musikalische Abnahme sind andere Rollenbesetzungen weiterhin sinnvoll.

1. Gerätepuffer nacheinander 64, 128, 256, 512 und 1024 Samples. Einstellungen des Studio-One-Dropoutschutzes beim Vergleich gleich halten und notieren: Gerätepuffer und tatsächlicher Plugin-Verarbeitungsblock können voneinander abweichen.
2. Statisches XYZ (ruhig und intensiv), schnelle XYZ-Bewegungen und längere Wiedergabe. Nicht nur den durchschnittlichen CPU-Balken, sondern Aussetzer und Spitzen beachten.
3. Profilwechsel, Stop/Neustart, Seek und Loop testen; auf hängende Noten achten. CC mehrfach ein-/ausschalten, auch gestoppt, und den bestehenden Reset gegenprüfen.
4. Eine, danach zwei beziehungsweise vier Instanzen gleichzeitig starten. GUI offen/geschlossen vergleichen. Externe Instrumente selbst können einen erheblichen Teil der Gesamtlast verursachen; deren Konfiguration im A/B unverändert lassen.

Die Messumgebung liefert keine Garantie für jeden 64-/128-Sample-Betrieb. Es wurden keine Noten, Controllerwerte oder musikalischen Entscheidungen zur Entlastung entfernt. Die folgenden Dark-Synth-MIDI-Hörbeispiele sind die unveränderten bisherigen P1/P2-Studien, keine musikalisch unterschiedlichen Performance-A/B-Versionen.

---

# Aktueller Hörtest – Dark Synth P2

Im bestehenden Komponistenmenü **Dark Synth** wählen (ersetzt John Carpenter). 4/4, D, 100 BPM, Aufbau/Fahrt AUS, unbegrenzte Wiedergabe, automatische Spielweisen und Follow EIN. Zunächst 512 Samples als Vergleichspuffer. Vorhandene neun MIDI-Ziele unverändert auf geeignete externe Instrumente routen; Kanalnummern, klingende Tonumfänge und Benutzeroktaven kontrollieren. Die Patchfähigkeiten werden nicht automatisch erkannt.

1. Ohne HM/GS bei XYZ 0/0/0 starten: eine minimale ruhige Stimmung soll unmittelbar möglich sein. Anschließend nostalgisch **.85/.20/.15**, Schatten/Bassrotation **.50/.35/.25**, ritualisch **.15/.85/.15** prüfen. LF und Bass zunächst zusammen hören, dann einzeln.
2. Bewegung **.40/.65/.45**, hohe Unruhe **.20/.80/.90**, helle Unheimlichkeit **.85/.20/.80**. Jeweils 64–128 Takte stehen lassen, dann langsam fahren und Variation/Abwechslung wechseln. Nicht jede Quelle verlangt AR/GS oder einen Bass. Lange Harmonieperioden und ruhende Klangfelder sind beabsichtigt.
3. TU separat hören: Akzente/Tupfer aktiv, AR/GS/HM aus; **.55/.40/.30**, mindestens 64 Takte. Keime, Pausen und Wiederkehr beachten. Danach AR/GS dazunehmen und echoartige Antworten vergleichen. TU benötigt einen tonhöhensteuerbaren Patch; ST bleibt fester Trigger 36.
4. Optional HM und deren Motivschalter aktivieren. Die belegten TU-Expositionen sind kontextabhängig und werden nicht erzwungen; HM soll ohne Aktivierung stumm bleiben. Bei Q13-Gefrieren bleibt die Note auf AR, kein Klangwechsel nach LF. Dafür einen gehaltene Noten unterstützenden AR-Patch wählen.
5. Neutral, Barry, Williams, Morricone, Herrmann sowie POP/ROCK gegenprüfen. Bestehende CC-Anzeige und Abschaltreset sollen unverändert funktionieren; keine neue CC16–19-Klangmodulation. Stop/Neustart/Loop und Projektladen testen.

64 Takte bei 100 BPM dauern 2:34 Minuten, 128 Takte 5:07 Minuten. Die beigefügte **DARK_SYNTH_P2_MIDI.zip** enthält neun 128-taktige A/B-Paare mit getrennten Rollen. MIDI in Studio One importieren und beiden Fassungen dieselben Instrumente zuweisen. Harmonisch identische Auswahl ist bei erweitertem Profil nicht zu erwarten; die A/Bs vergleichen die komplette tatsächliche Produktion bei gleichen Parametern.

DEV-Build mit gleicher Plugin-ID: Studio One beenden, bisheriges STROMSCORE-VST3 sichern und durch den entpackten `Stromscore.vst3`-Ordner im üblichen Windows-VST3-Verzeichnis ersetzen (normalerweise `C:\Program Files\Common Files\VST3`). Nicht beide Versionen parallel installieren. Studio One starten und gegebenenfalls Plugins neu einlesen. Kein offizielles Release. Musikalische Abnahme steht aus.

---

# Aktueller Hörtest – Herrmann: AR und Ruhebereich

Referenz2170807 ist hinsichtlich CC-Anzeige/-Reset, Stich/Akzenten, Bass und Herrmann-Klangsprache positiv bestätigt. Dieses Paket korrigiert gezielt die AR-Auswahl und den stummen Start im Ruhebereich.

SCORE / Bernard Herrmann, 4/4, D,100BPM, Aufbau/Fahrt AUS, unbegrenzte Wiedergabe. AR: Kanal5, relative Intensität0, Oktave0, C3–D5 (=MIDI60–86), Figur/Tempo AUTO, Folgt Akkorden EIN. Bass wie bisher getrennt3/4, −2Oktaven, MIDI24–67. Geeignete vorhandene Instrumente unverändert verwenden.

1. Kalt mit XYZ0/0/0 starten: die ausgewählte ruhende Flächenharmonie soll sofort hörbar sein. Danach0/2/5/8/10/12/15/20% prüfen. Auch von höherer Intensität herunterregeln; die bestehende Ruhe-Hysterese10/14% bleibt erhalten. Fläche muten/Solo anderer Rollen respektiert weiterhin die Bedienung.
2. XYZ(.50/.85/.80), Variation3, Abwechslung50%, zunächst Melodie/Gegenstimme aus:64Takte hören. Anschließend(.15/.45/.80) und(.50/.50/.75) sowie XYZ-Fahrten vergleichen. AR ist quell- und kontextabhängig, mit vollständigen Figurenpausen. Nicht jede Harmonie verlangt AR; verschmolzene Polychorde können die zweite Komponente bereits auf LF enthalten.
3. Melodie/Gegenstimme aktivieren: AR soll deren gültigen Fenstern weiterhin Platz lassen. Mute/Solo, manuelle Figur, manuelles Tempo und Follow AUS testen. Neutral/Barry/Williams und zurück wechseln, Stop/Neustart/Seek/Loop prüfen.
4. Die bestätigten CC-Funktionen sowie lange/kurze Bässe, Stich und Akzente gegenhören. Einzelne CPU-Spitzen bei128Samples waren bereits in der Referenz dokumentiert; für den ersten Hörvergleich512Samples verwenden.

64Takte dauern bei100BPM2:34Minuten,128Takte5:07Minuten. Die neue Version bleibt ein DEV-Testbuild mit gleicher Plugin-ID; Installationshinweise weiter unten. Die folgenden früheren Anleitungen bleiben als musikalische Orientierung erhalten.

---

# Aktuelles Korrekturpaket – Herrmann und MIDI/CC

Bernard Herrmann behält die positiv gehörten hohen Streicher, basslosen Felder und unabhängigen harmonischen Komponenten. Bitte besonders LB/KB mit der bisherigen Instrumentierung prüfen: getrennte Kanäle3/4, Bass−2Oktaven, Tonumfang C0–G3. In STROMSCORE entspricht dieser Bereich MIDI24–67 und begrenzt die **klingenden Töne nach** der Oktavverschiebung. Andere Instrumente/DAWs können dieselben MIDI-Nummern anders benennen. Der Patch wird nicht automatisch erkannt.

4/4, D,100BPM, Bass AUTO, Folgt Akkorden EIN, Aufbau/Fahrt AUS, unbegrenzte Wiedergabe. Zunächst bei(.5/.85/.8)64Takte hören; anschließend ruhige und basslose Bereiche sowie langsame XYZ-Fahrten vergleichen. Einzelne vollständige Figuren werden gemeinsam oktaviert, keine Tonklassen oder Intervalle ersetzt. Absichtlich basslose Quellen bleiben basslos. ST ist wieder über seine bestehende feste Triggerfunktion erreichbar.

Zusätzlich „CC-Ausgabe für alle Kanäle“ prüfen: MIDI/CC oben wird orange. Beim Ausschalten einmalig127 für Dynamik/Ausdruck auf den konfigurierten Kanälen, auch bei gestopptem Transport, sofern der Host Audioblöcke verarbeitet. Vorgabe ist CC1/CC11; umbelegte Ausgangszuordnungen werden entsprechend behandelt. Die gespeicherten Bereiche bleiben erhalten. Erneutes Einschalten nimmt ihre normale Steuerung wieder auf. Beide Themes und Projekt-Neuladen ausprobieren.

Die nachfolgende ursprüngliche P1-Anleitung bleibt als musikalische Orientierung erhalten. Die Hörabnahme dieses Korrekturpakets steht aus.

---

# Herrmann P1 – Hörtest in Studio One

Windows-DEV-Version, gleiche Plugin-ID wie bisher. Studio One schließen, bisheriges STROMSCORE-VST3 sichern und den entpackten VST3-Ordner nach `C:\Program Files\Common Files\VST3\` kopieren. Nicht beide Versionen gleichzeitig installieren. Danach Plugin-Scan und Projektkopie öffnen.

SCORE / Bernard Herrmann, 4/4, D, 100 BPM, Fläche/Bass/Arp AUTO, Folgt Akkorden EIN, Aufbau und Fahrt AUS, unbegrenzte Wiedergabe. Zunächst Hauptmelodie und Gegenstimme stummschalten: die Identität soll bereits durch Harmonik und Begleitung entstehen. LF benötigt bis sechs Stimmen; LB und KB getrennt routen. Keine Instrumentenerkennung: geeignete Sustain-/Kurz-Patches selbst wählen.

Mindestens64Takte pro Zustand hören (2:34Minuten bei100BPM), für Entwicklung128Takte (5:07Minuten). Unterschiedliche Variationen ausprobieren. XYZ-Werte sind Vorschläge, keine garantierte Einzelauswahl.

- HE-H01: XYZ [0.2, 0.3, 0.3] – eingefrorener Moll-Dur-Septakkord; identisches Material mit stabilem Katalogeintrag JB-H01 gemeinsam genutzt.
- HE-H03: XYZ [0.15, 0.45, 0.7] – HE-H03 – Halbtonpendel zweier Moll-Dur-Septakkorde.
- HE-H66: XYZ [0.55, 0.25, 0.6] – HE-H66 – Dur über Tritonusbass.
- HE-H51: XYZ [0.15, 0.25, 0.65] – HE-H51 – Moll über Moll im Tritonus, getrennt.
- HE-H60: XYZ [0.15, 0.55, 0.65] – HE-H60 – Polychord rückt zusammen.
- HE-H68: XYZ [0.45, 0.15, 0.55] – HE-H68 – Hochpedal über tiefem Moll.

Die getrennten Komponenten über LF und AR isoliert vergleichen. H60 zeigt eine hohe, mittlere und tiefe Komponente mit abschließender Verschmelzung. Die Verschmelzung ist zunächst ein gehaltenes sechsstimmiges Feld; keine allgemeine rhythmische LF/KF-Fusionsengine. H68 enthält tiefes und hohes Pedal. Bei gleichen MIDI-Kanälen oder ungeeigneten Registern kann eine Quelle bewusst entfallen.

Anschließend GS, optional HM und deren Motivschalter einschalten. Strenge Harmoniebedingungen dürfen Pausen erzeugen. Die14 breiten Produktionsstudien belegen M07, nicht die hörbare Nutzung aller22 registrierten Motivgrundformen. Keine permanente Lead-Stimme erwarten.

`P1_MIDI_LISTENING.zip` enthält14 vollständige128-Takt-Produktionsstudien und sieben passende Neutral-Vergleiche; die Dateien auf externe Instrumente mit unveränderter Kanalzuordnung routen. Klangliche Qualität und Balance durch den Anwender beurteilen. Andere Taktarten verwenden sichere bestehende Pfade; neue komplexe Schichtfiguren sind auf4/4 begrenzt. CC-Modulation ist nicht implementiert.

---

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
