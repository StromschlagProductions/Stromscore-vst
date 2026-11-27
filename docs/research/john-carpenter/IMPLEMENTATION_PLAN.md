# John Carpenter – kanonischer technischer Bestandsabgleich

27.11.2026 · Ausgang `4937722`, Branch `develop/composition-core-prototype`.
Musikalische Engine unverändert `023b0a6` einschließlich Williams P2/P3 und Build-Fix.
Ausschließlich Dokumentation/Analyse. Weder SYNTH-Modus noch Carpenter sind aktiviert.
Williams P2/P3 warten weiter auf die Anwender-Hörabnahme.

## Ergebnis und Vollständigkeit

Die Bibliothek ist formal konsistent als MIDI/CSV-Paket, aber keine unmittelbar
ladbare Engine-Grammatik. Der echte Gewinn liegt in klar unterscheidbaren
musikalischen Objekten: gehaltenes Feld, unabhängiger Bass, konkrete Tonfolge,
Rhythmus, Einzelereignis und deren kontrollierte Entwicklung. Die gemeinsame
Engine besitzt viele Bausteine; ihre heutigen Verbraucher interpretieren diese
Objekte noch nicht vollständig.

| Bereich | Gesamt | D | A | E | K |
|---|---:|---:|---:|---:|---:|
|Harmonik|88|20|0|68|0|
|Rhythmik|67|0|51|13|3|
|Sequencer|67|0|0|67|0|
|Bass|52|1|0|50|1|
|Motive|45|0|34|11|0|
|Phrasen|16|0|0|16|0|
|Transformationen|16|0|2|14|0|
|Ereignisfelder|12|0|0|11|1|
|Modellstudien|42|0|0|38|4|
|**Summe**|**405**|**21**|**87**|**288**|**9**|

D: musikalische Grundform direkt darstellbar, trotzdem noch nicht importiert.
A: begrenzte Anbindung vorhandener Fähigkeiten mit exakter Kontext-/Instrumenten-
prüfung. E: mindestens eine zusätzliche gemeinsame musikalische Datenbedeutung
oder Fähigkeit; das kann ein kleiner Verbraucher sein, kein großer Architekturumbau.
K: konkrete fehlende Zuordnung oder widersprüchliche Quelle vor vollständiger
Umsetzung klären. Optionale Transformationen machen nicht jede Grundform zu E;
volle Verfahren werden aber nicht nur wegen eines ähnlichen Teilverfahrens als
fertig bezeichnet. Eine PC-gleiche Harmonie ist noch keine exakt gleiche Besetzung.

Alle405 IDs stehen einzeln mit Grund, Quellzeile, konkreten Ton-/Zeitdaten,
Perioden und Fähigkeiten in [TECHNICAL_INVENTORY.json](TECHNICAL_INVENTORY.json)
und [TECHNICAL_INVENTORY.md](TECHNICAL_INVENTORY.md). `assessment.json` enthält die
redigierten Einstufungen, `audit.py` ergänzt prüfbare Quelldaten. Die67 Q-Quellen
sind nicht pauschal unspielbar: Teile passen in bestehende Motivbausteine. Es fehlt
aber ihr vollständiger eigenständiger Sequencer-Gebrauch; daraus wird kein
Akkordarpeggio und keine künstlich gekürzte Acht-Noten-Fassung gemacht.

## Eigene technische Prüfung

- ZIP fehlerfrei,405eindeutige IDs, erfasste JC-Verweise vorhanden.
-54 SMF-Dateien mit 16.046 Noten,960 PPQ. Jede Note einschließlich Spur/Rolle,
  Kanal, Einsatz, Dauer, Tonhöhe und Velocity stimmt mit der CSV überein.
- Keine offenen/verwaisten oder gleichzeitig identischen Kanal-/Tonpaare in einer
  Spur. Alle15ST-Ereignisse sind MIDI36. Keine stille Transposition.
-42explizite S-Notenzahlen stimmen mit den tatsächlichen Dateien überein;
  beschriebene zeitliche Rollenfenster passen, wenn mehrere Fenster derselben
  Rolle gemeinsam ausgewertet werden. Der weitergehende S35-Rotationsanspruch
  ist dagegen nicht erfüllt.
- Alle237 V-Studiennoten erreichen einen schrittweisen passenden A-Zielton.
  Alle332 F/U-Noten besitzen eine ausdrückliche nachvollziehbare Freigabe.
  Kein neu fremder Ton bei tatsächlich durchgehaltenen Harmoniewechseln gefunden.
-62 T-Noten in vier Gesamtvorlagen benötigen eine eindeutige lokale Kontext-
  Hierarchie. Das ist kein Nachweis62falscher Tonhöhen. Keine Harmoniekorrektur
  durchführen, um die Labels passend zu machen.
- Forschungsregister in den gelieferten Tonarten erfüllt. In allen zwölf
  Zieltonarten bei unveränderter Lage geprüft: acht LB-Noten in S40 unterschreiten
  in C den ForschungsbodenA0; keine Note verlässt MIDI 0–127.
-64 Studien-/Ziel-Kombinationen in 38 IDs überschreiten mindestens eine aktuelle
  Standardannahme zu Dauer oder Polyphonie. Kürzeste Note48 Ticks, Modellminimum240.
  Das sind keine kaputten MIDI-Dateien und keine Garantie für unbekannte Patches.

Vollständige Messwerte,237 Zielverknüpfungen,332 Autorisierungsnachweise und
Studienstatistiken: [VALIDATION_RESULTS.json](VALIDATION_RESULTS.json).
Die Originalqualitätsprüfung bleibt unverändert; unsere Prüfung bestätigt nicht
ungeprüft sämtliche ästhetischen oder konzeptionellen Aussagen. Keine eigene
Hörabnahme. Forschungs-MIDI ist keine Ausgabe eines aktiven Carpenter-Profils.

## Konkreter Korrektur- und Klärungsbedarf

[ERRATA.md](ERRATA.md) behandelt alle ausdrücklich angefragten Fälle und die
zusätzlichen Befunde. Insbesondere:

- R022/R046: Beschreibung korrigieren, nicht die eindeutigen Einsatzticks verschieben.
- R038–040: Gate-Zuordnung und Startphase explizit machen; B049 hängt daran.
- H067: fünf Klangstimmen; LF 6 reicht. H025/H085: gerade10/6-Takt-Perioden, keine
  Zweierpotenzen, keine neuen untertaktigen Harmoniewechsel erforderlich.
- S35: tatsächliche Poolanschläge je 16 Takte256/192/128/192 und aktive Rollen 2/2/1/2.
  „Immerzwei“ und konstante Dichte sind nicht durch die Studie nachgewiesen.
- S04/S33: abschließende Stille fehlt im SMF-Clipende, jeweils3048 Ticks.
- Lokale T-Vorräte vs. H-Kontext in S18/S28/S40/EF12 klären.
- Die angenommene harte R-Domain-Vererbung auf fest eingebettete Rhythmen und die
  Alternative als reine Datenreferenz ausdrücklich entscheiden.

Originale werden nicht geändert. Eindeutig lösbare Textfehler, vorgeschlagene
Zuordnungen und noch offene musikalische Entscheidungen bleiben getrennt.

## Zeit, Zyklen, Gate und Identität

[CYCLE_ANALYSIS.json](CYCLE_ANALYSIS.json) deckt alle 67Q,52B und67R ab.
Für eine endliche Tonliste N und A Anschläge in einer Rhythmusperiode P beträgt
der gemeinsame Zyklus `N/gcd(N,A)·P`. Nicht mit einer einzelnen Rhythmusperiode
oder einem Acht-Takt-Phrasenfenster verwechseln.

Q028/Q054/Q063 und B031/B052 benötigen zwei Takte; Q055 sowie B029/B030/B032/
B033/B034/B035 vierTakte. Q043 braucht fünfTakte für 80 Anschläge, Q044 dreiTakte
für 24. Der globale Anschlagsordinal bestimmt die Tonfolge, die eigene Rhythmusphase
die Einsätze. Bei allen in den Studien verwendeten Q/B-Folgen passt ein
fortlaufendes Modell mit der angegebenen harmonischen Bindung; kein bloßer
Takt-Reset ist nötig. S22s ausdrückliche Halbton-Blockverschiebung wird dabei
mitgerechnet, nicht als Tonfehler gezählt. Die entsprechenden Vergleichszahlen
stehen in `pitch_cycle_evidence`.

Der heutige Materialhash bildet Intervalle, Einsatzzeiten, Dauern und gegebenenfalls
Zykluslänge ab, nicht Velocity. Die kanonischen Identitätsregeln unterscheiden aber
teils Tonhöhen-, teils Rhythmus-/Akzentidentität. Gespeicherte Velocity und ein
Intervall-/Zeithash sind deshalb nicht schon die vollständige Durchsetzung jeder
Quellinvariante. Diese Angaben sind im Inventar pro Quelle erhalten.

Die konkreten M-Noten speichern auch ausdrücklich notierte Velocity-Overrides
(etwa M004 v60/v40). Ein verkürztes Set möglicher Dauern ersetzt keine vollständige
Gatefolge. Vorlagenkataloge, tatsächlich eingeführtes Motiv und dessen Verwendung
sind unterschiedliche Zustände; Quelle und Original dürfen nicht gegenseitig
fortgeschrieben oder durch gemeinsam zugängliche Speicher zufällig übernommen werden.

## Gemeinsamer Kern: vorhanden und noch erforderlich

| Bereich | Konkrete Codebasis | Grenze / kleinste zusammenhängende Weiterentwicklung |
|---|---|---|
|Harmonie|[HarmonyTypes.h](../../../Source/HarmonyTypes.h), validierter statischer Katalog|27Typen, bis 8Slots; heutiger Importpfad8 Takte. Exakte weitere Klangobjekte/A-T-F-U-Stimmen und4/6/10/16-Takt-Zyklen getrennt prüfen. Bestehende stabile IDs erhalten. Kein ähnlicher Typ als Ersatz.|
|Gehaltene Noten/Pedale|`ScoreEngine::pedalRoot/sustained/BassPedal`|Pedal endet derzeit am Harmonieslot und kann zusätzlich KB-Puls erhalten. Eigener Lebensplan, kontrollierte Freigabe und explizite Dissonanzautorität fehlen. Follow AUS ist kein solcher Plan.|
|Bass|[BassPhrase.h](../../../Source/BassPhrase.h), `RoleRhythmSource::intervals[3]`|Gezielte4/4-Pop-Linie und begrenzte relative Zelle vorhanden. Keine vollständige fixe/relative Score-/SYNTH-Quellsequenz samt eigener Phase und Kontur.|
|Material|`RememberedMotif`, `MotifCatalog`, `MotifUse`, [AuthoredMotifSource.h](../../../Source/AuthoredMotifSource.h)|Gemeinsames tatsächliches Material, getrennte Verwendung, frühe Reprise/Variation. Maximal8 Noten, mindestens 2für Identität, zwei Katalogmaterialien/Szene; Quellenverbraucher Barry/Williams. Ein-Noten-Ruf und32 Noten-Q werden dadurch nicht automatisch korrekt.|
|Rhythmus|[RoleRhythm.h](../../../Source/RoleRhythm.h), `BarryVocabulary::planBar`|Ersterer2 Takte4/4, Sechzehntelzählung; letzterer andere taktsynchrone Muster. JC-Ticks, Unterstriche, Gate und Akzentwerte wörtlich konsumieren. Einstellbares Hostmeter ist keine Umsetzung aller Vorlagen.|
|Ausführung|[MusicalTime.h](../../../Source/MusicalTime.h), [MusicalExecution.h](../../../Source/MusicalExecution.h)|64 Bit960 PPQ und Dispatcher reichen für 320/640-Triolen. Zeitbasis nicht neu bauen. Pitch-/Rhythmusphase ist musikalischer Zustand, keine zweite Clock.|
|Instrumente|`ScoreEngine::outputCatalog`, `PlayingTrack/RoleNeed/suitable`|NeunZiele; LF 6 Stimmen, LB/KBmono, ARmono, TU4. Min240 Ticks, KF/TUmax720, KBmax960. Tatsächlicher Emitter kann kürzer, aber Modellprüfung muss zur realen Spielweise passen. Patchfähigkeiten unbekannt.|
|Tonabsicht|`ModalContext`, `authoredPitchMask`, kontrollierte Durchgänge|Ionisch/Mixolydisch/Dorisch/Äolisch/Oktatonik und lokale P3-Masken vorhanden. Keine allgemeine Funktions-/Gültigkeitssemantik für unabhängige Pedale, Bass- und Sequencerlinien. Lydisch/Phrygisch/Harmonisch-Moll/Lokrisch fehlen als gemeinsame Modi.|
|Block/Rollen|`deriveMotif(sequence)`, `planMelodyHandoff`, Rollenfenster|Sequenzvariante verarbeitet Zweitonzelle; keine ganzeBlocktransposition. HM→GS-Suffix/GS→AR sind kein allgemeiner Kanon oder Rollenwechsel. Sourceidentität und unabhängige Zustände weiterverwenden.|
|Feld/Langzeit|Akzente, Ereignisdichte, Szenenaufbau/-ende, Arp-Phrasierung|Keine allgemeine Ereignisabstandsreihe, gekoppelte Schichtrotation oder langfristige Stasis-/Wiederaufnahmeentscheidung. Gezielte kleine Verbraucher ergänzen; keine zweite Engine.|

Die erlaubten neun Ausgänge sind eine Ausgangsbasis, keine Pflichtbesetzung.
Keine obligatorische Melodie, Gegenstimme, AR oder Puls. Registertrennung ist eine
Präferenz; die kanonische Formulierung „zwingend für Hörspiel“ überstimmt nicht den
Anwenderauftrag. ST bleibt fest36, TU harmonisch nutzbar. Keine automatische
Percussion-Zuordnung, neuen CC-Verläufe oder zusätzlichen Ausgänge.

## XYZ: formale Abdeckung ist nicht musikalische Verfügbarkeit

[XYZ_COMPATIBILITY.json](XYZ_COMPATIBILITY.json) enthält27Zellmitten und8Ecken,
passende H/B/Q/M-Paare samt Quellen und einen getrennten Vergleich mit den
unveränderten C++-Funktionen `Generator::weight/keepRatio` bei Variety0/0,5/1.
Alle20.328H/Q/B/M-Paarvarianten sind mit Gegenbeispiel oder passenden Zeitfenstern
in [PAIR_COMPATIBILITY.jsonl](PAIR_COMPATIBILITY.jsonl) enthalten.

Verfahren: H-Gesamtzyklus und Pitch-/Rhythmuszyklus vollständig prüfen; ganze
gehaltene Noten berücksichtigen. Kontinuierliche Q/B und nur in geeigneten Fenstern
spielbare M unterscheiden. V-Ziele bleiben schrittweise zu A. Erlaubnis kommt aus
definierten H-Tönen/Vorrat oder ausdrücklicher F/U-/Pedalfreigabe. Keine heimliche
Vereinigung aller Quellenmodi. Danach XYZ-Domains sowie konservativ die referenzierte
R-Domain schneiden. Keine neue globale Auswahlregel im Produkt.

Die27formalen H/R/Q/B/M-Zählungen und neun Zellen ohne Studie werden reproduziert.
Zusätzlich ergeben sich **sechs Zellen ohne konservativ nutzbares Q/H/R-Paar**.
Davon haben zwei bereits keine Q-Quelle; vier besitzen Q, verlieren diese aber
bei der eigenen R-Domain. Beispiel: dunkles leises hohesZ hat Q003, aber R013
schließt diese Intensität aus. Helle leise Bereiche betreffen Q053/R037 bzw.
Q018/Q033/Q034/Q036 mit ihren Rhythmen. Das muss durch präzise Gültigkeitssemantik
geklärt werden, nicht durch willkürlich größere Rechtecke.

Hochhell/kraftvoll/unruhig (0,83/0,83/0,83): dreiH, achtB, achtR, keineQ und keineM,
keine eigene Studie. Gehaltene Klangfelder, Bassfiguren und bewusst melodielose
Ergebnisse sind dort formal möglich. Das ist **kein** Nachweis einer schon
überzeugenden vielschichtigen Hörspielmusik in dieser Ecke. Bestehende Quellen
nicht vervielfachen, um die Tabelle aufzufüllen.

Der konservative Paarcheck beweist weder gleichzeitige Verträglichkeit aller
B/Q/M-Kombinationen noch Register-/Instrumentenbereitschaft oder hörbare Qualität.
Ein einzelner passender Bass oder B041(Silence) ist keine ausreichende Vielfalt.
Er prüft keine unvorhergesehenen XYZ-Sprünge. Der alternative Wert ohne vererbte
R-Domain ist nur eine diagnostische zweite Lesart. Aktuell ist keine JC-Kombination
im Plugin aktiv. Die kanonischen Anker/Bereiche bleiben unverändert.

## Acht Strategien und gemeinsamer Ausbau

| Strategie aus Vertiefung | Konkretisierung im JC-Paket | Gemeinsame Voraussetzung / Status |
|---|---|---|
|S1 Stasis|T012, B001, S01/S20|Eigene Lebensdauer und Materialbindung, keine obligatorische Acht-Takt-Neuauswahl.|
|S2 Rotation|T007, P009, S35|Gekoppelte Rollenentscheidung, tatsächliche Dichte/Gewicht prüfen; S35-Klärung zuerst.|
|S3 Atmung|T016, B004; S35 istlautDatenRotation|Notenbezogene Velocity bei neuen Anschlägen, keine Lautstärkefahrt gehaltenerTöne. Kein neuer CC-Auftrag.|
|S4 Wanderung|T006, P007, S27|Gemeinsame Referenz, unabhängige Verwendung, passende Rollen-/Dauergrenzen.|
|S5 Umfärbung|T008, P006, S29|Figur bleibt, neuer Kontext mit autorisierten Funktionswechseln; keine automatische Tonhöhenkorrektur.|
|S6 Ereignisfeld|EF01–EF12|Lange Grundlage, eigene Ereigniszeit/-abstände, auch Null Ereignisse zulassen; EF06 istnichtreinpulslos.|
|S7 Blockverschiebung|T001, P012, S22|Ganzer angeforderter Block, nicht bestehende Zweiton-Sequenzvariation; Pedalbeziehung explizit.|
|S8 Reduktion/Rückkehr|T011/T014, P001/P005, S36|Identisches Material erhalten, Restart oder fortlaufende Phase ausdrücklich entscheiden.|

Diese Verfahren sind für Williams/Herrmann/SYNTH gemeinsam nutzbar. Keine Pflicht,
alleStrategien regelmäßig abzuarbeiten; mechanische und psychologische Unruhe
sind unterschiedliche Wege und brauchen keine zusätzlichen GUI-Regler.
Unabhängige Perioden bleiben gemeinsame Fähigkeit und markierte Carpenter-Hypothese,
kein schon durchTriolen/5/4bewiesenes Stilmerkmal.

## Priorisierte kleine Schritte – Empfehlung, keine Umsetzung

1. **C0 Quellen klären.** Eindeutige Textkorrekturen separat bestätigen; Gate-Mapping,
   S35, lokale T-Hierarchie und R-Domain-Vererbung festlegen. Diese Entscheidungen
   dürfen andere direkt passende Quellen nicht unnötig blockieren.
2. **C1 Gemeinsamer Einzelpedal-/Halteplan.** Eigener Ton, Beginn/Ende und Autorisierung
   über reale Harmonie-/Phrasenwechsel; exakter Note-off. Williams/Herrmann ebenfalls
   prüfen. Kein neues musikalisches Material erforderlich, keine zweite Zeitbasis.
3. **C2 Kleiner gehaltener Feld-/Einzelereignisplan.** Danach minimaler späterer
   SYNTH-Hörtest mit wenigen vollständig passenden Quellen, zunächst auch ohne
   AR/HM/GS. Kandidaten erst nach Eligibility-Prüfung, etwa vorhandene Moll-Grundform
   H017 plus langes B001 und kurze komponierte TU-Figur M004 im gemeinsamen
   gültigen Bereich. M004s480 Tick-Gates passen zu TU; M040s langeTöne dagegen nicht.
   Stille muss wirklich erhalten bleiben, kein Pflichtstich. Dafür nur tatsächlich
   benötigte Quellen anbinden, nicht gleich alle 405 oder eine universelle Plattform.
4. **C3 Gemeinsame stabile Tonfolge und Bassfolge.** Vollständiger Tonindex neben
   Rhythmusphase, zuerst einfacher Root-/Quint-Gedanke, dann mehrtaktiger Fall
   Q054/B033 und Phasenbeispiel. Originalkern wiederverwenden; alleTöne spielen,
   keine Rückrechnung ins Arpeggio. Instrumenten-Dauergrenzen ausdrücklich auflösen.
5. **C4 Präzise lokale Tonabsicht/Vorräte und harmonische Zyklusdauer.** Nach konkretem
   Bedarf mit C1–C3verbinden, nicht erst nach dem Import korrigieren. 4/6/10/16-Takte
   erhalten; benötigte Klangobjekte/Modi einzeln. Kontextwechsel und beabsichtigte
   Dissonanz schützen. Das erschließt auch Williams- und Herrmann-Vorlagen.
6. **C5 Blockverschiebung, Rollenwanderung und gekoppelte Rotation.** Jeweils ein
   begrenzter Fall, keine gesamte Formgrammatik. Block benötigt keine Polychorde;
   einfacher Materialtransfer keine unabhängige Periodik. S35 nicht blind nachbauen.
7. **C6 Weitere Strategien und komplexe Studien.** Kürzung/Verlängerung, Umfärbung,
   explizite Rhythmus-/Pitchphasen, Polychordkomponenten und längereBögen entsprechend
   den gemeinsamen Abhängigkeiten. Kein erzwungener Spannungsbogen bei konstantem XYZ.

Vor einer Genre-/GUI-Aktivierung kann ein tatsächlicher gemeinsamer Produktionspfad
bereits Offline-MIDI-Hörbeispiele liefern; dies ist von der später separat
freizugebenden auswählbaren SYNTH-Testversion zu unterscheiden. Dieser Auftrag
aktiviert weder Testprofil noch Genre. Williams-P2/P3-Hörabnahme bleibt offen.

Jeder freigegebene Schritt: tatsächliche Quellenverwendung, Original-/Varianten-
Identität, Pitch-/Rhythmuszyklus, Harmonie über ganze Gates, alle zwölf Tonarten,
manuelle Einstellungen/Follow/Mute/Solo und Instrumentenfähigkeiten prüfen. Dazu
statische Position und XYZ-Fahrten über 64/128 Takte, Determinismus, Seek/Loop,
Blockgrößen, Live/Export, erhaltene Profile/Rollen regressieren; Sanitizer/Build
passend zum Codeeingriff. Keine Allokationen, Validierung oder Dateioperationen im
Audiothread. Hörtests unter Sprache ergänzen, keine Statistik als Qualitätsersatz.
