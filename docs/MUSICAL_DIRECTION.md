# Musikalische Ausrichtung von STROMSCORE

Verbindliche Produktentscheidung des Anwenders vom 26. November 2026.
STROMSCORE bleibt ein spezialisiertes Hörspiel-Underscoring-Werkzeug, kein
universeller Songgenerator oder Orchesterarranger. Ausgangspunkt dieser Phase
ist die positive Hörabnahme von `8d4086c`.

Fortschreibung vom 26. November 2026: Die Williams-Arp-Phrasierung `2c6f366` wurde
vom Anwender positiv gehört und musikalisch abgenommen; siehe
[Referenzabnahme](development/ACCEPTED_REFERENCE_2c6f366.md). Sie bleibt für Williams P2
unverändert. Der freigegebene nächste Schritt ist ein erster gemeinsamer
Oktatonik-Kontext, keine weitere Arpeggio-Optimierung.

## Prioritäten für Forschung und Entwicklung

Höchste Priorität: Mystik, Geheimnis, subtile Spannung, psychologisches Unbehagen,
Lauern/Schleichen, unterschwellige Bedrohung, Angst/Horror, dramatische Spannung,
unheilvolle Erwartung, Nervosität, bedrohliche Stille und dramatische Eskalation.
Hohe Priorität: Action/Verfolgung, Fremdartigkeit, surreale/übernatürliche Atmosphäre,
Melancholie/Tragik, Einsamkeit/Verlorenheit, dunkle Monumentalität, unheimliche epische
Weite und mysteriöses Staunen. Wärme, Romantik, Humor, Verspieltheit, Freude,
unbeschwertes Abenteuer und strahlender Triumph bleiben musikalisch überzeugend
verfügbar, erhalten aber eine geringere Priorität für zusätzliche Entwicklung.

Dies gilt projektweit, auch für zukünftige Künstlerprofile. Differenzierte Formen
leiser Bedrohung sind für den tatsächlichen Einsatz besonders wertvoll. Die
Priorisierung ist **keine Laufzeitquote**, keine neue GUI-Einstellung und kein Grund,
bestehende warme Vorlagen zu löschen oder fremde XYZ-Anker umzusetzen.

## Verbindliche Stilarchitektur: ein Kern, individuelle Profile

Fortgeschriebene Anwenderentscheidung vom 27.11.2026: **Variante C** der
[Architekturanalyse](research/OPERATING_MODES_AND_STYLE_ARCHITECTURE.md).
Ein gemeinsamer Kompositionskern trägt individuelle musikalische Stilprofile
und flexibel verwendete MIDI-Rollen. SCORE, SYNTH und POP/ROCK dürfen der
Oberflächenorganisation dienen; sie sind keine drei separaten Engines und
keine vorgeschriebenen Instrumentierungen. ORCHESTRAL/ELECTRONIC wird nicht
als starre technische Trennung eingeführt.

Das bisherige POP/ROCK mit seinen 39 Wendungen, Hooks, Bass- und Rhythmusverfahren
bleibt vollständig erhalten. Seine spätere Darstellung als „Pop/Rock Mix“ in
einer Filmmusik-/Score-Sammlung ist möglich, aber kein bloßes Umschalten auf die
heutigen Score-Regeln. Carpenter P1 benötigt keinen vollständigen Genre-Umbau;
vorerst bleibt es ein Profil im vorhandenen SCORE-Auswahlpfad.

Geplante SYNTH-Profile:

- Neutral Electronic.
- John Carpenter.
- Harold Faltermeyer.
- Jan Hammer.
- Vangelis.
- Tangerine Dream.
- Jean-Michel Jarre.

Weitere Künstler können später hinzukommen. **John Carpenter besitzt für das
geplante Horrorhörspiel KADAITCHA besonders hohe Priorität.** Musikalischer
Referenzschwerpunkt der kommenden Forschung sind klassische elektronische
Horror-Soundtracks wie *The Fog*, *Christine* und die elektronischen Passagen aus
*The Thing*. Diese Priorität ist noch keine ausgearbeitete Stilgrammatik oder
Freigabe zur Profilimplementierung.

Bei zukünftigen gemeinsamen Erweiterungen sind insbesondere zu berücksichtigen:

- Eigenständige Sequencer-Figuren und harmonisch unabhängige Basssequenzen.
- Mehrere ineinandergreifende rhythmische Schichten mit unabhängigen
  Wiederholungszyklen und rhythmischen Phasenverschiebungen.
- Hypnotische Ostinati, mechanische rhythmische Präzision und minimale
  musikalische Variation.
- Bewusst statische harmonische Strukturen und langfristige Entwicklung durch
  wechselnde Schichtung.

Diese Verfahren sind musikalische Möglichkeiten und Profilpräferenzen, keine
generellen Pflichten für alle SYNTH-Profile. Kontinuierliche Sequenzen dürfen
nicht allein wegen einer für andere Kontexte vorgesehenen Wiederkehrpause
unterbrochen werden. Die gemeinsame Engine soll geeignete Strategien ermöglichen;
es entsteht keine separate elektronische Kompositionsengine.

**Komposition und Instrumentierung bleiben unabhängig.** SYNTH bestimmt die
musikalische Arbeitsweise, nicht die Instrumente. Elektronische Kompositionsstile
sollen auch orchestral spielbar sein; SCORE-Strategien sollen ebenso mit
Synthesizern funktionieren. Kein Profil schreibt eine Instrumentierung vor.
Tatsächliche Spielweisen, Tonumfänge, Polyphonie und Instrumentenfähigkeiten
bleiben bei der Ausgabe zu berücksichtigen.

Optionale elektronische Percussion, optionale MIDI-CC-Klangbewegungen und eventuell
erforderliche zusätzliche musikalische MIDI-Rollen sind spätere Forschungsfragen.
Die vorhandenen neun MIDI-Ausgabeziele sollen möglichst erhalten bleiben.
Über notwendige Rollen-/Ausgangserweiterungen wird erst nach der
musikwissenschaftlichen Recherche entschieden; aus dieser Ausrichtung folgt
keine jetzige Routing- oder Artikulationserweiterung.

Die Entscheidung wird schrittweise umgesetzt; kein vorsorglicher Gesamtumbau.
Neue musikalische Fähigkeiten werden nur gezielt angeschlossen. Die erste Williams-P1-Grundlage und ihre Arp-Phrasierung sind inzwischen
positiv gehört; das vollständige Stilprofil bleibt weiter auszuarbeiten. Gemeinsame Anknüpfungspunkte stehen im
[musikalischen Fähigkeitsbericht](research/SHARED_MUSICAL_CAPABILITIES.md).

## Bedeutung der drei Achsen

X bleibt dunkel–hell, Y zurückhaltend–kraftvoll, Z stabil–unruhig. Hell bedeutet
nicht automatisch positiv: lydische Schwebe, hexatonische Durbeziehungen,
chromatische Medianten, dissonante Durklänge und hohe Pedale können entrückt,
kalt, gläsern, trügerisch idyllisch, fremdartig oder übernatürlich wirken.
Dunkel bedeutet weder automatisch laut noch nervös. Leise hohe Unruhe und
kraftvolle Stabilität müssen genauso sinnvoll bleiben wie intensive Action.

Intensität kann aus Dynamik, Register, Gewicht, Schichtung und Akzenten entstehen.
Unruhe kann aus Akzentverschiebung, Gruppierung, Synkope, Reibung, Dissonanzbass,
Pausen und harmonischer Bewegung entstehen. Beide dürfen sich beeinflussen,
sollen aber nicht auf dieselbe Notendichte- oder Arp-Temposkala reduziert werden.
Das ganze XYZ-Feld bleibt nutzbar; keine erzwungene Bevorzugung dunkler Klänge
unabhängig von der tatsächlich gewählten Position.

## Gestaltungs- und Abnahmeregeln

Stilmittel sind Präferenzen, keine generellen Rollensperren. Keine Pflicht auf
lange/kurze Flächen, Pedalbass, schnelle Arpeggien, hohe Dichte, Vorlagenwechsel,
Rollenzahlgrenzen oder Zeitlimits für Zuspitzungen. Manuelle Einstellungen haben
Vorrang. Instrumentenfähigkeiten und MIDI-Ziele bleiben von musikalischen Rollen
getrennt. Alle Profile verwenden dieselbe Engine.

Die akzeptierten organischen XYZ-Übergänge, erkennbare Motivwiederkehr und Variation,
Melodie/Dialog-Zusammenspiel und Entwicklung bei statischem XYZ sind zu schützen.
Neue Profile müssen auch ohne beide Melodierollen charakteristisch funktionieren.
Studien sind musikalische Referenzen und Prüfgrundlagen, keine statischen MIDI-
Clips für die Produktwiedergabe. Musikalische Qualität wird nach technischen
Prüfungen vom Anwender gehört; Auswahlstatistiken allein genügen nicht.
