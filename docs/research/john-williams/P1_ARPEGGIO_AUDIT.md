# Williams P1 – Hörabnahme und Arpeggio-Untersuchung

Stand: 26.11.2026. Gemessen: `7c20afa`, musikalischer Stand `ddad94b`.
Keine Engine-, GUI-, Policy- oder Vokabularänderung in diesem Auftrag.

## 1. Anwender-Hörabnahme

Praktischer DAW-Test mit orchestraler Instrumentierung: allgemeine Qualität gut,
Bass und Flächen überzeugend, kraftvolle Wirkung und hörbare Eigenständigkeit
gegenüber Barry; einzelne Passagen bereits für Hörspiele verwendbar.
Williams P1 ist damit als **brauchbare Entwicklungsgrundlage akzeptiert**, ausdrücklich
noch nicht als fertig ausgearbeitetes Künstlerprofil.

Verbesserungsbedarf: Arpeggio dominant und gefühlt nahezu permanent; entscheidend
ist Präsenz, nicht primär Tempo. Melodie/Dialog treten vergleichsweise wenig hervor.
Eindeutige Williams-Assoziationen zu Star Wars/Indiana Jones sowie fanfarenartige
und monumentale Gesten fehlen noch weitgehend. Das ist Anwenderfeedback, keine
von MIDI-Kennzahlen abgeleitete musikalische Qualitätsbewertung.

## 2. Reproduzierbare Messung und Begriffe

`scripts/analyze_williams_arpeggio.py /tmp/williams-arp-audit` kompiliert den
vorhandenen `tools/williams_probe.cpp` direkt gegen Produktionsheader. Ergebnis:
[P1_ARPEGGIO_MEASUREMENTS.json](P1_ARPEGGIO_MEASUREMENTS.json).
168 echte Renderings über je 128 Takte: drei Profile × 13 XYZ-Verläufe × vier
Melodiekonfigurationen, plus zwölf Variationskontrollen (1/7 statt 3 an zwei Punkten).
4/4, D, 100 BPM, 48 kHz, Auto, Follow EIN, Motivschalter EIN, Aufbau AUS,
unbegrenzt ohne interne Fahrt. Externe Fahrten werden zu festen Samplezeitpunkten
aktualisiert. Alle Einstellungen stammen aus dem verlinkten Probe; keine Injektion
von Akkorden oder Plänen. Andere Tempi, Swing, manuelle Muster, Patches und die
konkreten Einstellungen des Anwenderprojekts wurden hier nicht nachgestellt.

- Aktiver Takt: mindestens ein Arp-Notengate berührt den Takt; kein Aktivierungsflag.
- Klingende Zeit: Vereinigung tatsächlicher MIDI-Note-on/off-Intervalle / Gesamtdauer.
  Patch-Release, Hall, Lautheit und Maskierung sind damit nicht gemessen.
- Exakt ununterbrochen: keine positive MIDI-Gatelücke. Zusätzlich musikalischer
  Aktivitätsabschnitt: erst eine Pause von mindestens einer Viertelnote trennt ihn.
  Jede längere Pause mit Start/Dauer steht im JSON; auch Randstille ist ausgewiesen.
- Dichte: Note-ons; Geschwindigkeit: Abstand benachbarter Onsets. Beides ist von
  der Präsenz zu unterscheiden. Bei 100 BPM sind 128 Takte 307,2 Sekunden.
- Rhythmik: Sechzehntel-Onsetmaske je Takt (Swing 0); gleiche Maske bedeutet nicht
  gleiche Tonfolge oder gleiche Akkorde. Die längste Maskenfolge kann auch Stille sein.
- Bewegter Bass: getrennt mehr als ein Anschlag bzw. mehr als eine MIDI-Tonhöhe
  im Takt. Letzteres zählt auch Oktaven; keine Behauptung einer freien Bassphrase.

## 3. Tatsächliche Ausgabe

Tabelle: beide Melodierollen EIN, Variation 3. Aktiv = Takte von 128,
Gate = klingender Zeitanteil, Lauf = längster Abschnitt ohne Viertelpause.

| XYZ / Verlauf | Profil | Note-ons | Aktiv | Gate % | Lauf Takte |
|---|---|---:|---:|---:|---:|
| 0,15/0,20/0,20 | Neutral | 0 | 0 | 0.0 | 0.0 |
| 0,15/0,20/0,20 | Barry | 0 | 0 | 0.0 | 0.0 |
| 0,15/0,20/0,20 | Williams | 0 | 0 | 0.0 | 0.0 |
| 0,15/0,25/0,80 | Neutral | 830 | 105 | 81.055 | 14.0 |
| 0,15/0,25/0,80 | Barry | 0 | 0 | 0.0 | 0.0 |
| 0,15/0,25/0,80 | Williams | 814 | 103 | 79.492 | 14.5 |
| 0,15/0,85/0,20 | Neutral | 1660 | 105 | 81.055 | 16.0 |
| 0,15/0,85/0,20 | Barry | 890 | 115 | 86.914 | 10.0 |
| 0,15/0,85/0,20 | Williams | 1856 | 116 | 90.625 | 38.0 |
| 0,15/0,85/0,85 | Neutral | 1864 | 117 | 91.016 | 82.0 |
| 0,15/0,85/0,85 | Barry | 1780 | 115 | 86.914 | 11.0 |
| 0,15/0,85/0,85 | Williams | 1672 | 105 | 81.641 | 18.0 |
| 0,85/0,20/0,20 | Neutral | 0 | 0 | 0.0 | 0.0 |
| 0,85/0,20/0,20 | Barry | 0 | 0 | 0.0 | 0.0 |
| 0,85/0,20/0,20 | Williams | 0 | 0 | 0.0 | 0.0 |
| 0,85/0,25/0,80 | Neutral | 1252 | 104 | 79.883 | 14.0 |
| 0,85/0,25/0,80 | Barry | 0 | 0 | 0.0 | 0.0 |
| 0,85/0,25/0,80 | Williams | 905 | 114 | 88.379 | 22.625 |
| 0,85/0,85/0,20 | Neutral | 1620 | 102 | 79.102 | 16.0 |
| 0,85/0,85/0,20 | Barry | 890 | 115 | 86.914 | 10.0 |
| 0,85/0,85/0,20 | Williams | 1700 | 108 | 83.008 | 14.5 |
| 0,85/0,85/0,85 | Neutral | 1644 | 103 | 80.273 | 14.0 |
| 0,85/0,85/0,85 | Barry | 1816 | 114 | 88.672 | 15.0 |
| 0,85/0,85/0,85 | Williams | 1692 | 107 | 82.617 | 14.5 |
| 0,50/0,50/0,50 | Neutral | 1777 | 112 | 86.768 | 22.0 |
| 0,50/0,50/0,50 | Barry | 392 | 100 | 19.141 | 9.812 |
| 0,50/0,50/0,50 | Williams | 1824 | 116 | 89.062 | 13.0 |
| 0,20/0,30/1 | Neutral | 828 | 105 | 80.859 | 14.0 |
| 0,20/0,30/1 | Barry | 478 | 124 | 93.359 | 23.25 |
| 0,20/0,30/1 | Williams | 828 | 105 | 80.859 | 14.0 |
| 0,20/0,90/1 | Neutral | 1632 | 102 | 79.688 | 14.0 |
| 0,20/0,90/1 | Barry | 1780 | 115 | 86.914 | 11.0 |
| 0,20/0,90/1 | Williams | 1628 | 103 | 79.492 | 14.0 |
| langsame Fahrt | Neutral | 1548 | 106 | 82.373 | 18.0 |
| langsame Fahrt | Barry | 1025 | 122 | 79.443 | 72.0 |
| langsame Fahrt | Williams | 1392 | 106 | 81.396 | 14.0 |
| schnelle Fahrt | Neutral | 1574 | 110 | 85.645 | 22.0 |
| schnelle Fahrt | Barry | 1055 | 125 | 80.713 | 25.062 |
| schnelle Fahrt | Williams | 1466 | 108 | 82.91 | 15.75 |

### Präsenz ist nicht Geschwindigkeit

Ohne Melodierollen spielen Williams und Neutral in allen neun statischen Fällen
mit aktivem Arp dieser Matrix **128/128 Takte mit 100 % Gate**, ohne eine einzige
Viertelpause. In den beiden leisen stabilen Fällen schweigen sie vollständig.
Williams hat bei Y=0,25/Z=0,80 nur 1024 statt 2048 Anschläge: Achtel statt
Sechzehntel, aber dieselben 100 % klingende Zeit. Eine Tempobremse allein löst
also die Dauerpräsenz nicht.
Barry schweigt bei Y=0,25 in diesen Beispielen wegen seiner höheren Einsatzschwelle.
Bei Y=0,85/Z=0,20 spielt er Achtel, aber ebenfalls ohne Pause über 128 Takte.
Im mittleren Fall hat Barry nur 25 % Gate ohne Melodierollen, ist trotzdem in
jedem Takt präsent (512 Anschläge): kurze Viertelimpulse mit kleinen Lücken sind
keine musikalisch längeren Atempausen. Die beiden Fahrten liefern bei Williams ohne
Melodierollen etwa 99,95/99,85 % Gate und 128 Takte ohne Viertelpause; Barry
82,76/83,64 % mit längeren Unterbrechungen. Dies ist kein ausschließliches
Williams-Problem und kein Nachweis eines defekten Schedulers.

### Koexistenz und konkrete musikalische Zeitfolge

Dunkle Action (0,15/0,85/0,85), Williams, ohne Melodierollen:
2048 Arp-Onsets, alle 0,25 Viertel = Sechzehntel, Gate lückenlos 307,2 s.
Kurzfläche in 128 Takten aktiv, Bass in 128 Takten mit mehreren Anschlägen,
in 70 Takten mit verschiedenen Tonhöhen. Arp läuft in allen diesen Takten mit.
Die Maske `0xffff` wiederholt sich **128 Takte**, obwohl Akkorde/Töne wechseln.
Bei heller Action ist diese Maske ohne Melodierollen ebenfalls 128 Takte identisch.
Neue Williams-Begleitzellen erzeugen somit noch keinen gemeinsamen Arp-Phrasenverlauf.

Derselbe dunkle Fall mit beiden Melodierollen: 1672 Arp-Anschläge, 105 aktive Takte,
81,641 % Gate = 250,8 s. Zwölf Viertelpausen: elf von zwei Takten, eine von
1,5 Takten. Beispiel ab Taktposition 0 (nullbasiert): Pause [0,2), Arp [2,4),
Pause [4,6), dann Arp [6,24) **18 Takte / 43,2 s**. Weitere Pausen beginnen bei
24,32,44,56,64,72,88,96,108 und 120. 104 volle Onsetmasken `0xffff`,
23 leere Masken und ein halber Takt `0xff00`; Rhythmusvariation besteht hier
hauptsächlich aus reservierungsbedingten Unterbrechungen.

Nur Hauptmelodie oder nur Dialog ergibt hier jeweils 1640 Arp-Noten, 103 aktive
Takte und 80,078 % Gate; längster Lauf 14 Takte. Beide Stimmen zusammen führen
nicht automatisch zu weniger Arp, weil ihre Rollenfenster anders koordiniert sind.
Mit beiden Stimmen entstehen 60 Melodie- und 63 Dialog-Noten. Arp überlappt die
Melodie in diesem Fall zeitlich nicht, den Dialog aber während **18,555 % der
Gesamtlaufzeit**. Das ist ein beobachtetes Verhältnis, kein neu festgestellter Bug:
Der bestehende Reservierungspfad wählt bei aktiver Hauptmelodie zunächst deren
Motivfenster; er reserviert nicht sämtliche unabhängigen Dialogeinsätze.

Auch bei beiden Melodierollen besteht keine globale Rangfolge „Williams am meisten“:
Neutral läuft im dunklen Actionfall bis zu 82 Takte ohne Viertelpause, Williams 18,
Barry 11. Bei dunkler kraftvoller Stabilität Williams 38 Takte, Neutral 16, Barry 10.
Die Dominanz hängt von Harmonie, spielbaren Motivfenstern, Parametern und Klang ab.
Die zusätzlichen Variationen 1/7 stehen vollständig im JSON; sie verändern
Unterbrechungen, beseitigen das strukturelle Fehlen eines eigenen Arp-Atemplans nicht.

Variationskontrolle, dunkle Action mit beiden Melodierollen: Williams Gate bei
Variation 1/3/7 = 82,617/81,641/81,641 %, längster Lauf jeweils 18 Takte.
Neutral = 79,492/91,016/83,105 %, Barry = 86,914/86,914/86,914 %.
Gleicher Gate-Anteil schließt andere Tonfolgen oder Pausenpositionen nicht aus.

## 4. Ursachen und wiederverwendbare Planung

- `Source/CompositionPolicy.h::TexturePolicy`: Williams nutzt neutrale Schwellen
  (Arp ab Y≈0,25); Barry hat 0,30, andere Hysterese und Auto-Temposchwellen.
  Aktivierung und Tempo sind vorhanden, ein eigener Arp-Phrasen-/Pausenplan fehlt.
- `ScoreEngine::{chooseArp,arpeggioPeriod,playArpeggio}`: Figur aus zwei
  Wendungsvorschlägen, reproduzierbar pro Phrase; reguläre Anschlagsperiode und
  akkordbezogene Tonfolge. Das verändert Figur/Tonhöhe, erzwingt aber keine Pause.
- `ScoreEngine::render` ruft `playArpeggio` auf, sobald Rolle, Dichtemaske und
  Reservierungen erlauben. `EventDensity` entfernt optionale metrische Gruppen,
  ist kein musikalischer Plan für mehrere zusammenhängende Pausentakte.
- `roleRhythm` koordiniert Williams-Kurzfläche/Bass, besitzt aber keinen Arp-Anteil.
  `movementRhythm`/`RhythmPlan` und Barrys `authoredRhythmBar` können bereits
  konkrete Einsätze/Pausen abbilden; der Pop-Interlock ist bewusst genrebegrenzt.
- `motifWindow`, `dialogueArp`, `MotifOccurrence` und `playableMelodyHandoff`
  schützen tatsächlich spielbare melodische Fenster; deshalb existieren mit
  Motivstimmen schon längere Arp-Pausen. Aktiviert bedeutet nicht durchgehend spielend.
- 960-PPQ-Zeit, Plananfang/-ende, Register-/Instrumentenprüfung, unabhängige
  Motivverwendung und deterministische Varianten sind vorhanden. Kein neuer
  Scheduler, keine zweite Engine und keine pauschale Erhöhung der Leadwahrscheinlichkeit nötig.

## 5. Vorschlag: kleine musikalische Arp-Phrasierung

Als gesonderten nächsten Auftrag einen begrenzten Einsatzplan für **Auto-Arp im
Williams-Score-Kontext** prüfen: eine zusammenhängende Figur mit geplanter Fortsetzung
oder Atempause an einer echten Harmonie-/Modulgrenze. Rhythmische Kurzfläche und
bewegter Bass liefern Kontext, aber keine automatische Sperre. Gemeinsamer Puls
und bewusst parallele Bewegung bleiben erlaubt, insbesondere in Action.

Entscheidungsgrundlage: aktuelle spielbare Motiv-/Antwortfenster, bereits geplante
Begleitansätze, Figurabschluss, harmonische Dauer und bisheriger Bewegungsverlauf.
Pausen können auch ohne aktive Melodierollen sinnvoll sein. Fortgesetzte Bewegung
bleibt eine zulässige Entscheidung; keine Laufzeitquote, kein verpflichtender
Taktwechsel und kein starrer Höchstwert für Aktivitätsläufe. Keine globale Velocity-
Absenkung und keine zufällige Zerstückelung einzelner Arp-Noten. Explizit manuelle
Figuren bleiben vorrangig. Wenn Dialogfenster berücksichtigt werden, nur tatsächlich
spielbare Fenster und bewusste Rollenkoordination verwenden, keine Aktiv-Checkbox-Sperre.

Klein anfangen: bestehende Plan-/Fensterdaten und Tick-Onsets verwenden, zunächst
nur eine nachvollziehbare Bewegungs-/Atementscheidung am Figurenende. Noch keine
allgemeine Texturdramaturgie. Nicht dieselbe Pausenstrategie auf zukünftige
kontinuierliche SYNTH-Sequenzen übertragen.

Abnahme: gleiche Vergleichsmatrix, reale vollständige Pausen und Läufe zusätzlich
zu Tempo/Dichte, Schutz manueller Muster und Begleit-/Motividentität; keine Forderung
nach einer bestimmten Prozentzahl. Determinismus, Seek/Loop, Blockgrößen und echte
Live-/Exportgleichheit bei späterer Implementierung prüfen und anschließend hören.

## 6. Williams-Motive früh nach dem gemeinsamen Tonvorrat

P1 importierte bewusst keine der 48 Williams-Motivvorlagen. Mehr Arp-Pausen schaffen
Platz, erzeugen allein aber noch keine Williams-Handschrift. Nach dem ersten
**tatsächlich von Score-Motiven verwendeten** Tonvorratskontext kann eine kleine
Auswahl kurzer Vorlagen früh folgen, vor Langphrasen und der vollständigen Bibliothek.
Gemeinsamen Motivkatalog, tatsächliche Aufnahme, frühe Reprise, Variation und
Melodie/Dialog-Zustände weiterverwenden. Benötigt werden Quellintervalle, Rhythmus,
Kontext und erlaubte Nicht-Akkordtonfunktionen; Vorratszugehörigkeit allein garantiert
noch keine musikalisch sinnvolle Realisierung über allen Akkorden.

Geeignete getrennte Testgruppen aus der kanonischen Forschung:

- Dunkle Repetition **M05** (sechs Noten, kleine Terz und chromatischer Schluss):
  kurzer erster Horror-/Spannungskandidat. Seine tatsächlichen D/Db-Funktionen über
  `Cm | Db/C` prüfen; nicht allein aus dem Namen pauschal Oktatonik annehmen.
- **M08** (vier Noten, A–F♯–G | E über C): lydischer Doppelnachbar;
  #4→5 muss hörbar erhalten bleiben und darf nicht auf Akkordtöne kollabieren.
- **M01** (sieben Noten, Quintaufschwung/Doppelschlag) und **M02** (sieben Noten,
  auf–ab–höher): frühe Signal-/Fanfaren- bzw. Kampfkonturen für helle/kraftvolle
  Bereiche; vollständige Zweitaktgestalt, Register und Zielnoten erhalten.

M04 verlangt zusätzlich den fehlenden dreitönigen Quartaltyp und ist kein ebenso
kleiner Erstimport. M11/M12 überschreiten die Acht-Noten-Grenze, M16 benötigt
zusätzlich Triolen; diese nicht als gekürzte Vollvorlagen ausgeben. Ein erstes
Vorratsmodell für Oktatonik schaltet Lydisch/Diatonik oder chromatische Vorhalte
nicht automatisch frei. Imports in kleinen, zum jeweils geprüften Kontext passenden
Gruppen; keine separate Williams-Motivengine. Alle Vorlagentöne sind Konstruktionen
[E], keine Star-Wars-/Indiana-Jones-Transkriptionen und kein Versprechen einer
Themenimitation. Monumentalität verlangt außerdem Rhythmus, Register, Klang und
später längere Zielbewegung; die neue kurze Motivwahl allein garantiert sie nicht.

## 7. Prüfstand dieses Untersuchungsauftrags

168 Produktionsrenderings mit geschlossener Note-on/off-Bilanz und unveränderten
Quellprüfsummen. Zusätzliche Wiederholungs- und 127/512-Blockvergleiche für alle drei
Profile bei schneller externer Fahrt bestanden. Keine Änderung an ausführbarem
Enginecode; deshalb keine erneute vollständige Engine-/pluginval-Suite.
Das neue Skript ist eine Offline-Auswertung, keine Kompositionsfunktion.
Es misst den aktuellen MIDI-Produktionspfad, keine DAW-Audioaufnahme oder externen
Patchfähigkeiten. Vorschläge sind nicht implementiert. Kein Push und kein Release.
