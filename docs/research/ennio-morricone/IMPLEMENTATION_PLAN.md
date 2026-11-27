# Ennio Morricone – Bestandsabgleich und gemeinsamer Implementierungsfahrplan

27.11.2026 · Ausgang **`4c43bd2`** · `develop/composition-core-prototype`.
**Nur Archivierung, Prüfung und Planung.** Morricone ist nicht aktiviert; keine
Engine-, GUI-, Parameter-, Routing- oder Klangänderung. Die laufende Hörabnahme
der unabhängigen Pedale bleibt unberührt. Die positive Williams-P2/P3-Abnahme
von `023b0a6` bleibt die musikalisch akzeptierte Grundlage.

## Maßgebliche Quellen und musikalische Priorität

Die sieben Originale sind bytegleich archiviert, siehe [README](README.md) und
[Prüfsummenmanifest](ARCHIVE_MANIFEST.json). Kanonisches Vokabular, Ereignis-CSV,
MIDI-ZIP und Qualitätsbericht bilden die Vorlagenbibliothek. Hauptrecherche,
Lolita-Nachtrag und Vertiefung bleiben getrennte wissenschaftliche Grundlagen;
der umbenannte Lolita-Nachtrag liegt **einmal** vor. Originale werden nicht repariert.
Empfehlungen und Aussagen über angeblich bestehende Engine-Funktionen sind
Forschungsinhalt, keine weiteren Implementierungsaufträge oder technischen Belege.

**Lolita / Love in the Morning und The Untouchables haben persönliche Priorität.**
Der früheste musikalische Schritt soll deshalb lyrische Harmonik und emotionale
Akkordübergänge hörbar machen. Das steht nicht im Gegensatz zur projektweiten
Horror-/Thriller-/Mystery-Priorität: gebundene Nonen, verzögerte Auflösung und
harmonische Umdeutung tragen auch leise Spannung. Ein gemeinsames Morricone-Profil,
kein Lyrik-/Experiment-Schalter. Weder HM/GS noch AR, Puls, Pedal oder ein Anker
werden obligatorisch. Kompositionsweise und Instrumentierung bleiben unabhängig.

Konkrete Akkorde oder Themen aus Love in the Morning sind **nicht nachgewiesen**.
Die Studien sind eigene Konstruktionen, keine Transkriptionen. Die ältere
Lolita-Fortsetzungstabelle ist nicht die verbindliche Notendefinition; insbesondere
Am(add9) ist nicht Am9. Evidenzkennungen bleiben Angaben der Forschung, nicht
hier erneut extern verifizierte Quellenbelege.

## Vollständigkeit und Einstufung

534 eindeutige IDs; 16 EF-Definitionen mit zweiter Studienfundstelle werden nicht
doppelt gezählt. Alle 20 T-Tabellenzeilen sind enthalten. Jede ID besitzt eigene
Quelldaten, Begründung, Abhängigkeiten und Codebezüge in
[TECHNICAL_INVENTORY.json](TECHNICAL_INVENTORY.json) und
[TECHNICAL_INVENTORY.md](TECHNICAL_INVENTORY.md).

| Bereich | Gesamt | D | A | E | K |
|---|---:|---:|---:|---:|---:|
| H Harmonik |119|0|0|110|9|
| U Übergänge |50|0|0|50|0|
| R Rhythmik |64|0|31|28|5|
| B Bass |52|1|4|44|3|
| C Zellen |46|0|0|46|0|
| M Motive |50|0|29|21|0|
| P Phrasen |22|0|0|21|1|
| K Module |38|0|0|34|4|
| EF Ereignisfelder |16|0|0|16|0|
| T Transformationen |20|0|0|20|0|
| S Modellstudien |57|0|0|49|8|
| **Summe** |**534**|**1**|**64**|**439**|**30**|

- **D:** definiertes Grundverhalten unmittelbar darstellbar. Hier ist B023s
  ausdrücklicher Bassverzicht bereits vorhanden. Keine Quelle wird dadurch importiert.
- **A:** konkrete Grundfigur mit bestehenden Bausteinen und begrenzter Quellen-,
  Rollen- und Kontextanbindung möglich. Das bestätigt nicht alle optionalen
  Transformationen, jede Kombination oder jeden externen Patch.
- **E:** mindestens eine zusätzliche gemeinsame musikalische Datenbedeutung oder
  Fähigkeit fehlt. Das kann eine kleine harte Haltebedingung sein; **keine Forderung
  nach einer neuen Engine**. Eine raw MIDI-Datei abspielen zu können ist kein
  Ersatz für die definierte kompositorische Fähigkeit.
- **K:** widersprüchliche oder wesentlich unklare Quellenentscheidung zuerst klären.
  Quellenfehler werden nicht als Entwicklung des Kerns kaschiert. Zwingend abhängige Vorlagen erhalten ebenfalls K, behalten aber ihre zusätzlichen Fähigkeitslücken.

Die strenge H-Einstufung ist bewusst: **87/119 H-Vorlagen** besitzen an ihren
angegebenen Wurzeln vollständig passende bestehende Akkordqualitäten (einschließlich
acht H-Klärfällen). Das harmonische *Material* ist also weitgehend vorhanden.
Der vollständige Vorlagenvertrag verlangt zusätzlich Quelllage, Reibungsverteilung,
teils eine feste Oberstimme oder gehaltene Töne. Diese Eigenschaften sind heute
nicht als harte Eingabe im gemeinsamen Pfad garantiert. Eine PC-gleiche, anders
besetzte Version wird nicht als vollständiger Import derselben Vorlage gezählt.

Ein zusätzlicher Materialabgleich findet vier bestehende Entsprechungen bei
Tonklassen, Bass und Dauern über acht Takte: **H041 → 1018/2003, H050 → 30025,
H075 → 30001 und H079 → 30020**. Dabei werden benachbarte identische Zustände
zusammengefasst und kürzere vollständige Zyklen wiederholt. Das ist ausdrücklich
keine Gleichheit der Quelllagen, Halteabsichten oder vollständigen Vorlagen.
Bestehende Katalog-IDs und sämtliche EM-Quellidentitäten bleiben erhalten; vor
einem Import ist Wiederverwendung statt eines unnötigen Materialduplikats zu prüfen.

## Tatsächlich vorhandene Basis

| Bereich | Tatsächlicher Mechanismus | Grenze für diese Bibliothek |
|---|---|---|
| Harmonik | `HarmonyTypes.h::HarmonyTemplate/Chord`, validierte Quelldaten und generierte statische Kataloge; stabile IDs, Grundton/Bass getrennt, geschützte Akkordfärbung. | Aktueller Laufzeitvertrag: acht Slots, ganze Akkordtakte und acht Takte pro Vorlage; keine freien lokalen Klangobjekte/Schichten. Bestehende IDs unverändert lassen. |
| Akkordtypen | `ChordTypes.generated.h`: 27 Typen, darunter MinorAdd9, Major6, Min6, MinMaj7/9, Min9, Dominant9, HalfDim, Sus2/4, Major7Sharp11. | `add#11` ohne Septime und Moll7add11 fehlen; echte 6/9-Typen wären nach Quellenklärung eigene Definitionen. Nicht durch Major9/Maj7Sharp11 oder ähnlich benannte Typen ersetzen. |
| Stimmführung | `CompositionCore.h::buildAnchor/planHarmony/leadEntry`, `VoiceLeading.h::lead`: begrenzte Beam-Suche, PC-Schutz, Bewegungs-/Abstands- und Gemeinsamtonkosten, dominante Leittonpräferenzen; Vorgeschichte tatsächlich gehörter Lage. | Keine harten gehaltenen Tonhöhen, keine allgemeine Garantie exakter Quelllage oder aller Parallelverbote. `ChordIntent` hat fünf Intervalle, realisierte Padlagen sechs Stimmen. |
| Notenbesitz | `ScoreEngine.h::Active/noteOn/removeActive`, physische Freigabe erst nach letztem Ausgangsanspruch; `padChord` verlängert gemeinsame reale Langflächentöne über `extendOnly`. | Kein per-Stimme gespeicherter Halte-/Funktion-/Auflösungsplan; gemeinsamer PC ist nicht dieselbe gehaltene MIDI-Tonhöhe. Peak, Register und Neubelegung bleiben Kontextbedingungen. |
| Pedal | `PedalPlan.h::PedalPlan/permits`, `Generator::preparePedal`: eigener Tick-Lebensbereich, lokale Dissonanzberechtigung, explizite Bassprüfung, Williams-H03/H50/H61. | Ein tiefes Einzelpedal, zunächst begrenzte Lebensfenster und Quellbindung. Kein allgemeines hohes/inneres Pedal, keine Doppelpedale oder beliebigen Bass-Tonfolgen. Ein U-Oberstimmenton ist nicht durch Bassrouting gelöst. |
| Zeit | 64-Bit `musicaltime::Tick`, 960 PPQ und gemeinsamer Dispatcher. Harmoniegrenzen nominal, rhythmischer Swing getrennt. | Zeitdarstellbarkeit ist keine vorhandene beliebige Autorenrhythmus-/Periodenausführung. `RoleRhythmSource` arbeitet mit zwei 4/4-Texttakten; `AuthoredMotifSource` mit Sechzehntelzählwerten, acht Noten und zwei Harmonie-/Tonmasken. |
| Tonvorrat/Funktionen | `ModalContext.h`: Ionisch, Mixolydisch, Dorisch, Äolisch, explizite HG-Oktatonik; Akkord-/Vorratsmitgliedschaft und kontrollierter Durchgang. Quellmasken bei Motiven, neue explizite Pedal-Dissonanz. | Kein allgemeiner A/T/V/F/U-Vertrag pro Note und Harmoniezeitraum. Lydisch, Phrygisch, harmonisch/melodisch Moll, Ganzton und Hexatonik sind keine regulären Mode-Varianten. GH-Oktatonik ist als PC-Familie transponiert erreichbar, ihre Zentren-/Phasenbedeutung darf dabei nicht falsch beschriftet werden. |
| Motive | `RememberedMotif`, gemeinsamer `MotifCatalog`, getrennte `MotifUse`-Zustände, Originalaufnahme aus tatsächlichen Ereignissen, Wiederkehr, Konturschutz, rhythmische Variation, Fragment, Zweitonsequenz, Augmentation×2. | Keine ungeordnete Zelle, keine Klassen-/Kernidentität. Originalquelle acht Noten; zehn Variantenplätze heben die Acht-Noten-Originalgrenze nicht auf. Fragmentierung ist derzeit ein kurzes Schlussfragment, keine beliebige Kopfverkürzung. |
| Rollen/Koordination | `RoleNeed/PlayingTrack/suitable`, begrenzte Melodie→Dialog- und Dialog→Arp-Fenster; Auto-Arp-Phrasierung und motivische Reservierungen. | Kein allgemeiner Modulpool, keine frei simultanen Themen/Gegenmotive, keine beliebige Rollenwanderung. Bewusst unterstützende Gegenstimme ist von zweitem konkurrierendem Vordergrund zu unterscheiden. |
| Entwicklung | Gemeinsame `FreeCompositionPolicy`, Motiv-/Arp-/Texturpolitik, Szene und freie Wiederkehr; bereits musikalisch positive Entwicklung bei festem XYZ. | Keine Umsetzung der notierten P-, K-, EF- und T-Langverfahren. Statisches XYZ bedeutet nicht Stillstand und soll keinen automatischen Eskalationszyklus erzwingen. |

Die Aussage der Quellen „A/T/V/F/U bestehen bereits“ ist somit zu weitgehend.
Umgekehrt sind Pedale nicht mehr nur geplant: der erste gemeinsame Pfad existiert
bereits. Geschützte Akkordfärbung allein schützt weder eine Zelle vor Neurundung
noch eine selbständige Schicht vor globaler harmonischer Korrektur.

## Übergangsgrammatik: wichtiger kleiner Ausbau, kein Neubau

Die 50 U-IDs sind vollständige Zustands-/Absichtsdaten, keine 50 gewöhnlichen
zusätzlichen Wendungen für denselben Pool. Sie müssen zur tatsächlich gespielten
Ausgangsharmonie passen. Zwingende Haltetöne werden getrennt von bloß möglichen
Gemeinsamtönen gespeichert; ein Ton kann als None→Terz→Septime liegen bleiben.
Die MIDI-Tonhöhe und ihr Besitzer müssen dabei erhalten bleiben.

[TRANSITION_AUDIT.json](TRANSITION_AUDIT.json) enthält alle 50 Definitionen,
59 Grenzen, Pflicht-/Optionaltöne, mögliche monotone Stimmenzuordnungen und
hinzukommende/entfallende Stimmen. Bei 4→6 Stimmen werden keine Stimmen per
Index-`zip` erfunden. Vorhalte U014/U036 sind zusätzliche Ereignisse im Zielzustand,
nicht bloß ein anderer Akkordtyp an der Taktgrenze.

Der unveränderte kompilierte `voiceleading::lead` wurde mit diesen 59 Quellgrenzen
in zwölf Transpositionen geprüft: **708 Fälle**, jeweils mit erhaltenen Ziel-PCs.
Das ist eine erfreulich nutzbare Basis, aber keine harte Haltegarantie. Konkreter
Gegenbeleg: U040s letzte Grenze in C, Quelllage relativ `[-3,0,5,12]`, Ziel
`[-2,0,7,15]`. Mit Offset60 müsste Pflichtton **60** bleiben. Der heutige Solver
liefert **[58,63,67,72]**: gleiche Ziel-Tonklassen, aber statt des verlangten C60
bleibt C72. Derselbe Verlust tritt in Cis auf. Weder eine richtige Akkordmaske
noch `extendOnly` kann diesen bereits umgelegten Ton nachträglich binden.
[ENGINE_PROBE_RESULTS.json](ENGINE_PROBE_RESULTS.json) ist ein **Offline-Kerntest
mit Quelllagen**, kein Morricone-Livepfad und kein Test tatsächlicher Note-ons.

Der Bass-Pedalplan ist für stabile Lebensdauer, Berechtigungsprüfung und Freigabe
wiederverwendbares Vorbild. Für Langflächengemeinsamtöne zuerst deren vorhandene
Claim-/Verlängerungslogik verwenden. Nicht jeden Akkordton in einen Bass-Pedalplan
pressen und keine zweite Notenverwaltung eröffnen.

## Daten- und Artefaktprüfung

- Sieben Originale bytegleich; keine doppelte Lolita-Ablage.
- 534 eindeutige Definitionen, alle erkannten Querverweise auf vorhandene IDs.
- 73 ZIP-Dateien/9752 MIDI-Noten gleich mit CSV in Rolle, Einsatz, Dauer, Tonhöhe
  und Velocity; 960 PPQ, keine offenen/verwaisten Noten und keine physischen
  Gleichtonüberlagerungen innerhalb oder zwischen Spuren. ST stets36.
- Alle 46 IVs stimmen; C035s TnI-äquivalente Primformkonvention ist getrennt
  ausgewiesen. Kern- und Austauschvarianten C025/C026 werden getrennt betrachtet.
- Alle 64 R-Quellen vollständig mit ihren Schichten und kgV geprüft. Vier
  Dichte-/VK-Beschreibungen widersprechen dem Vollzyklus (R013/035/036/037).
- Alle 50 M-Längen stimmen unter Einrechnung von Pausen und tatsächlicher
  Taktart; gedruckte zellgebundene M-Töne liegen in ihren deklarierten Mengen.
- Beide tatsächlich exportierten V-Noten besitzen Zielton und Zielereignis am
  angegebenen Ende. Nicht alle 50 U-Definitionen sind in den gelieferten MIDI-
  Studien vertreten: 17 werden tatsächlich referenziert.
- Die CSV nennt Funktionsfolgen langer Noten, aber ohne deren Segmentzeitpunkte.
  Diese Angaben sind **kein unabhängig rekonstruierter lokaler/globaler
  Funktionstimeline-Nachweis für alle 9752 Noten**. Wir prüfen vollständige H/U-
  Zustände, explizite Ziele und ganze formale H/Figur-Horizonte separat; der
  unbereitgestellte Referenzrenderer wird nicht mit der Engine gleichgesetzt.

Details und Entscheidungen: [ERRATA.md](ERRATA.md). Besonders H074s fehlender
Farbtonwechsel und C010s tatsächliche Klangtonrundung dürfen nicht durch
„harmonisch gültig“ verdeckt werden. Die vier neuen R-Klärungen betreffen Metadaten,
nicht die Entscheidung, das notierte musikalische Material eigenmächtig zu ändern.

## XYZ und tatsächliche Kombinierbarkeit

[XYZ_COMPATIBILITY.json](XYZ_COMPATIBILITY.json) trennt vier Ebenen: deklarierte
Quellbereiche, unveränderten aktuellen Ankerfilter, formale Materialeignung und
noch fehlende musikalische/Instrumenten-Ausführung. **Aktive Morricone-Vorlagen:0.**

Das dichte Raster enthält **1331 Positionen (11³) einschließlich sämtlicher Ränder**
bei Variety0/0,5/1. Im unveränderten `Generator::weight/keepRatio`-Filter werden
hier nur hypothetisch alle119H-Anker ausgewertet. Keine neuen Profilgewichte,
keine U/H-Poolvermischung und keine globale XYZ-Änderung.

| Bereich | Minimum–Maximum deklarierte Vorlagen im dichten Raster | Positionen ohne Quelle |
|---|---|---:|
| H |0–51|13|
| U |0–28|915|
| R |0–45|154|
| B |0–32|400|
| C |1–36|0|
| M |0–32|652|

Der heutige weiche Filter findet zwar immer Kandidaten (Variety0:1–3,
Variety0,5:1–34, Variety1:1–74). Er kennt die neuen harten Quellrechtecke aber nicht:
bei 49/385/1284 Rasterpositionen liegt mindestens ein zulässiger Ankerkandidat
außerhalb des angegebenen Bereichs. Das ist keine Regression des bisherigen
XYZ-Algorithmus, sondern eine neue Quellenbedeutung, die beim späteren Import
explizit behandelt werden muss.

Alle acht exakten Ecken haben H-Material, aber nur ein bis drei Kandidaten und
**keine U** innerhalb der gedruckten Bereiche. Bei Y=1 fehlen in den Ecken B und M;
bei hohem Z fehlen dort auch R. Das beweist keine musikalische Leere – Stille,
Bass-/Melodieverzicht und vorhandene Begleitung sind gültig –, aber ebenso wenig
eine ausgearbeitete Kombinationsvielfalt. Die Bereiche sind musikalische
Einschätzungen; nicht eigenmächtig verbreitern oder durch künstliche Quoten füllen.

**16.280 formale H×B/C/M-Paare** wurden ohne Akkordtonrundung geprüft. Tonfolgen
bleiben tonikabezogen; „Folgt Akkorden“ wird nicht als zusätzliche Transposition
jeder notierten Bassnote missverstanden. M-Notenspannen werden über harmonische
Grenzen, Bassfiguren über vollständige Pitch-/Rhythmus-/HarmoniekgV geprüft:
B010 hat20 Anschläge/6000Ticks, gemeinsam mit4/4 erst nach96000Ticks (25Takte)
dieselbe Phase; mit einer achttaktigen Harmonie erst nach200Takten. Keine taktweise
Neustellung. Die H/D-Mehrschichtvorlagen benötigen zuerst lokale Kontexte und
werden nicht auf eine einzige flache Akkordfolge reduziert.

Negative Bass-Hüllprüfungen heißen bewusst „Gate-/Kontextentscheidung nötig“:
Rollen-Gates sind noch nicht vollständig quellgetreu definiert. Materialeignung
ist weder fertige Funktionserlaubnis noch Instrumenten- oder Hörfreigabe.

**8436 Dreierkombinationen** der38Module wurden gegen beidseitige Tabellenangaben,
Quellbereichsschnitt und deklarierte Polyphonie-Obergrenzen geprüft. 644 passieren
diesen strengen Vorfilter; **keine** ist dadurch als vollständiger klingender
Plan zertifiziert. 81 Paare besitzen unterschiedliche gerichtete Angaben;
Träger-/Färbungsrichtung muss geklärt werden. Eine Polyphoniesumme über dem
Standardmaximum beweist ohne Zeitraster keine tatsächliche Überlastung – gerade
komplementäre Einsätze können sie vermeiden. Auch ein bestandener paarweiser Test
beweist keine gleichzeitig gültigen drei lokalen Harmonien, Gates und Register.
[MODULE_COMPATIBILITY.json](MODULE_COMPATIBILITY.json) und die vollständigen
JSONL-Dateien machen diese Grenzen statt einer falschen Freigabe sichtbar.

Färbungsunabhängige R/B/C-Quellen behalten `beliebig` als dimensionsfreie Angabe;
nicht pauschal X=0,5 einsetzen. Für einen späteren Verbraucher sind explizite
Voraussetzungen und dimensionenbezogene Gewichtung sinnvoll, während die
bestehende globale XYZ-Steuerung erhalten bleibt. U wird zusätzlich nach
passender Quell-/Zielharmonie und Haltebedingungen gewählt, nicht allein nach Nähe.

## Priorisierte kleine Folgeaufgaben mit Abnahmekriterien

**0. Quellenentscheidungen abschließen, Pedalhörabnahme respektieren.** Die20
direkten Klärfälle und zehn zwingend davon abhängigen Vorlagen separat entscheiden lassen. Normalformkonvention festlegen, lokale
Funktionszeiträume und Gate-Bedeutung präzisieren. Originale archiviert lassen;
künftige korrigierte Arbeitsdaten mit Herkunft versionieren. Keine Pflicht, erst
alle experimentellen Fragen zu lösen, bevor eindeutige lyrische Quellen folgen.

**1. Pflicht-Gemeinsamtöne im bestehenden Stimmführungs-/Langflächenpfad.**
Kleinster zusammenhängender hörbarer Schritt: eine ausdrückliche Halteabsicht
für **U001 und U002**, mit vollständigen Start-/Ziellagen, bestehenden
MinorAdd9/Add9/Maj7-Farben und LF/LB; HM/GS/AR bleiben optional bzw. können aus
sein. Den vorhandenen Solver um begrenzte harte Tonbindungen ergänzen und seine
Entscheidung an die vorhandene `padChord`-Claim-/Release-Logik durchreichen.
Keine neue Harmonieengine, kein neues MIDI-Ziel, kein Vollimport der50U.

Zunächst die kanonischen jeweils eintaktigen Vor-/Nachzustände als vollständige
Zwei-Takt-Fenster prüfen/hörbar ausgeben. Produktionsanbindung nur bei kompatibler
tatsächlich gespielter Startlage und passenden Zeitfenstern. Eine aus U001/U002
abgeleitete, registerangepasste Bindungsregel für H005/H004 muss ausdrücklich als
solche gekennzeichnet werden: diese H-Vorlagen haben eigene zweitäktige Akkorde
und andere notierte Lagen. Nicht behaupten, ihre unveränderten Voicings seien
bereits exakt die U-Studien; keine Akkorddauer heimlich ändern. Ungeeignete
Fenster entfallen zugunsten des bisherigen gültigen Verhaltens.

Abnahme: zwölf Tonarten; echte Zielakkord-PCs und Bassvorgaben; Pflichtton bleibt
als **dieselbe physische MIDI-Note ohne Note-off/Note-on** liegen; neue/entfallende
Stimmen eindeutig; ungeeignete Register/Artikulationen abgelehnt; Mute/Solo,
beide Follow-Einstellungen, XYZ-Fahrten, Seek/Loop/Stop, deterministisches Live-
/Exportverhalten. Nicht angebundene Profile müssen unverändert bleiben. Ein A/B
mit LF/LB allein muss hörbar gebundene Umfärbung zeigen. Noch keine allgemeine
Phrasenplanung und kein alle Akkordwechsel dominierender Gemeinsamtonzwang.

**2. Ein expliziter Vorhalt mit Zielzeit, danach gestaffelter Akkordeinsatz.**
U014 zuerst, anschließend U036/U033/U034. Zielharmonie und vorübergehend V-
klingender Ton sind verschieden. Nachweis1920/2880Ticks nach Zielbeginn,
korrekte Freigabe, explizites Nichtauflösen als alternative Absicht, später
kontrollierter Stimmenaufbau. Nicht alle Verfahren gleichzeitig beginnen.

**3. Quellengetreue Pedal-/Bassbindung auf bestehendem Kern.** B001/B002/B004/B005
nach passender Ton-/Slash-Autorisierung anbinden. Eigene notierte Lebensdauer
und Beginn von den aktuellen Lebensfenstern unterscheiden. Danach **eine** echte
Bassfolge mit vollständigem Rhythmus-/Pitch-Zyklus (z. B. eine eindeutige kurze
Folge), nicht gleichzeitig Polychorde einführen. Gesamtkontext statt nacktem
DIS-Schalter prüfen. Gemeinsamer Nutzen für Williams/Herrmann/Carpenter.

**4. Eine geschützte Zellidentität, dann kleine periodische Quelle.** Erst MENGE,
ORD und KERN klar trennen; eine unveränderte C010-Realisierung und ein zulässiger
C026-Austausch. S016/S044 nicht als korrekte Identitätsvorbilder übernehmen.
Danach ein gemeinsamer tickgenauer Autorenverbraucher für exakt benötigte
Rhythmuspositionen und autonome Zyklen; R035/R036/R037 erst nach Metadatenklärung.
Triplet320 ist darstellbar, wird nicht auf240gerundet. B01025Takt-Phasenprobe und
mögliche200Takt-Verbindungen vollständig testen, nicht nur acht Takte betrachten.

**5. Lokale Schichten, kleine Module, gezielte Entwicklung.** Ein klarer K/D-Fall
(H091 oder H092 nach vollständiger Tonobjekt-/Dissonanzdefinition), danach ein
nachweislich vollständiger Dreierplan mit Ruhe-/Austauschregeln. Erst dann
Rotation, additive Enthüllung, echte Kopfverkürzung und pulslose Antwortfelder.
Keine verpflichtende Ankerstimme, kein Taktreset unabhängiger Zyklen, keine
Stimmreduktion zur scheinbaren Instrumentenverträglichkeit.

**6. Längere Linien und bewusst koordinierte Gegenmotive.** M011–M018/M048 und
P006/P020 benötigen vollständige Quelllinien und eine unterstützende Gegenrolle,
keine zweite zwangsläufige Vordergrundmelodie. >8Originalnoten nicht in unabhängige
Minimotive zerlegen. Erst konkrete Materialanforderungen erweitern, keine
universelle Form- oder Orchestrierungsplattform auf Vorrat.

Diese Reihenfolge ergänzt den gemeinsamen Williams-/Herrmann-/Carpenter-/SYNTH-
Fahrplan: **lyrische Übergangsbedeutung früh**, nicht erst nach kompletter Modul-
oder Polychordimplementierung. Horror-/Mystery-Bausteine und Carpenter bleiben
hohe Priorität; sie profitieren von demselben Notenbesitz, Tonabsichten und Zyklen.
Keine vorgeschlagene Folgeaufgabe ist mit diesem Dokument autorisiert umgesetzt.

## Reproduktion und Grenzen

```
python3 docs/research/ennio-morricone/audit.py
python3 docs/research/ennio-morricone/assess.py
python3 docs/research/ennio-morricone/compatibility.py
python3 docs/research/ennio-morricone/verify.py
```

Nur Offline-Dateianalyse und temporärer C++-Probe gegen den unveränderten Kern.
Keine fremden Renderer ausgeführt und keine MIDI-Studie als Engine-Ausgabe
umetikettiert. Kein neuer VST3-/Audio-/Hörtest und keine erneute DSP-Gesamtsuite:
Produktionsquellen und GUI bleiben bytegleich mit `4c43bd2`. Die Bibliothek wird
nicht als vollständig musikalisch abgenommen bezeichnet. Die Rohbefunde,
Quellenklärungen und formalen Kompatibilitätsgrenzen bleiben nachprüfbar.
