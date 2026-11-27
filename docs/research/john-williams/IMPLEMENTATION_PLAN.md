# John Williams – Bestandsabgleich und Implementierungsplan

Stand: 26.11.2026. Untersuchte Engine: `8d4086c`, Branch
`develop/composition-core-prototype`. Positive Anwender-Hörabnahme siehe
[ACCEPTED_REFERENCE_8d4086c](../../development/ACCEPTED_REFERENCE_8d4086c.md).
Keine Engine-/GUI-Änderung, kein Vorlagenimport in den Laufzeitkatalog.

## P1-Fortschreibung vom 26.11.2026

Die anschließende P1-Umsetzung erweitert den ursprünglich vorgeschlagenen 16er-Pool
auf sämtliche 49 direkt darstellbaren H-Grundvorlagen. Die zwölf angebundenen
R-Quellen und B01/B04/B18 nutzen eine gemeinsame rollenbezogene Begleitplanung;
Musik, Messungen, Teilübernahmen und Grenzen stehen in [P1.md](P1.md).
Die projektweit verbindliche [Ausrichtung](../../MUSICAL_DIRECTION.md) priorisiert
Horror/Thriller/Mystery, ohne helle oder warme Bereiche zu unterdrücken und ohne
XYZ-Anker/Quoten zu verändern. Der folgende Bestandsbericht bleibt die historische
Analyse vor P1; sein 16er-Vorschlag ist durch den freigegebenen 49er-Umfang ersetzt.

Nach der P1-Hörabnahme werden weitere Aufgaben gemeinsam festgelegt, mit hoher
Priorität für gemeinsame Okt-/Hex-/Lydisch-Kontexte, funktionale Nicht-Akkordtöne
und eigenständigere Bassführung. Klang-/Zeit-/Rhythmuserweiterungen, Williams-Motive
und danach Langphrasen/Rollenübergaben bleiben abgegrenzte Folgephasen. Sämtliche
76 Harmonien, 48 R-, 40 B-, 48 M-, 24 P- und 40 S/T-Referenzen bleiben im Ausbauplan;
nicht implementierte Studien sind keine statisch abzuspielenden Produktsequenzen.

### Gemeinsame Fortschreibung mit Herrmann, 26.11.2026

Williams P1 (`ddad94b`) ist technisch vorläufig freigegeben; die musikalische
Hörabnahme akzeptiert P1 als brauchbare Grundlage, nicht als fertiges Profil; siehe
[Arpeggio-Untersuchung und Motivfolgeaufgaben](P1_ARPEGGIO_AUDIT.md). Der neue [gemeinsame Fähigkeitsbericht](../SHARED_MUSICAL_CAPABILITIES.md)
empfiehlt danach einen tatsächlich ausgewerteten Tonvorratskontext, unabhängige
Pedal-/Bassabsichten sowie kleine repetitive Module und begrenzte Einsatz-/Register-
koordination vor umfangreicher Langphrasenplanung. Fehlende einfache Klangtypen
können bei konkretem Bedarf unabhängig folgen; Polychorde benötigen zusätzlich
eine getrennte Komponenten-/Registerbedeutung. Herrmanns neue Recherche begründet
keine allgemeine Oktatonikpflicht. Die historischen P2–P7 unten bleiben als
Bestandsplanung erhalten; die neue Reihenfolge ist ein Vorschlag, kein neuer
Implementierungsauftrag. Keine Änderung an P1 oder Freigabe einer Folgephase.

### Williams P2: erster gemeinsamer Oktatonik-Kontext

`2c6f366` ist musikalisch abgenommen; die Arp-Phrasierung wird nicht weiter
optimiert. Die freigegebene erste Kontextanbindung ist in [P2_OCTATONIC.md](P2_OCTATONIC.md)
dokumentiert: explizite Oktatonik-Metadaten für acht vorhandene Harmonien,
gemeinsame Zugehörigkeitsprüfung und kontrollierte Durchgänge im bestehenden
Score-Motivkern. Keine neue Motivbibliothek, keine vollständige Systemgrammatik.
Die folgenden Tabellen bleiben der historische Bestandsabgleich vor P1/P2;
neue musikalische P2-Ergebnisse benötigen die anschließende Anwender-Hörabnahme.

### Williams P3: kurze charakteristische Motivvorlagen

[P3_MOTIFS.md](P3_MOTIFS.md) prüft sämtliche 48 M-Grundvorlagen. 32 sind ohne
Tonverlust im gemeinsamen Vorlagen-/Motivpfad angebunden; 16 bleiben konkret
begründet zurückgestellt. Registrierung und tatsächliche Produktionsverwendung
werden im P3-Bericht getrennt ausgewiesen. Keine neue Langphrasen-, Kanon- oder
Parallelstimmenengine. P2/P3 benötigen weiterhin die musikalische Hörabnahme.

### Gemeinsame Fortschreibung mit kanonischem Herrmann, 27.11.2026

Abgleich bei `023b0a6` einschließlich P2/P3 und `.as_posix()`-Build-Fix:
Die [343 HE-Einzelbewertungen](../bernard-herrmann/TECHNICAL_INVENTORY.json) ergänzen
die bisherige Tiefenrecherche. [Gemeinsamer Fähigkeitsbericht](../SHARED_MUSICAL_CAPABILITIES.md)
und [HE-Fahrplan](../bernard-herrmann/IMPLEMENTATION_PLAN.md) priorisieren jetzt
unabhängiges Einzelpedal/Bassfolge, lokale A/T/V/F/U-Absicht, Ganzton/Hexatonik und
kurze Module vor langen Phrasensystemen. P3 hat bereits kurze Quellmotive angebunden;
weitere kontextkompatible Zellen müssen nicht auf alle Erweiterungen warten.
Lokale Quellmasken sind dafür vorhanden, eine flexible Funktions-/Auflösungssemantik
fehlt noch. Polychorde benötigen Komponenten-/Register-/Synchronitätspläne und
geeignete Instrumentendauern; keine Komponente entfernen. Triolen sind in 960 PPQ
darstellbar, erfordern aber exakte Vorlagen-Verbraucher. Kein neuer Scheduler.
Diese Anpassung betrifft ausschließlich die Planung. P2/P3 bleiben musikalisch
unabgenommen; keine Implementierung und keine weitere Arp-Optimierung.

## 1. Ergebnis und Bedeutung der Einstufungen

Die Forschung ist wesentlich breiter als ein Akkord-Preset. Die Engine bietet dafür
bereits eine leistungsfähige Grundlage: geschützte Akkordfarben, Slash-Bässe,
Übergangsstimmführung, exakte Tick-Zeit, echte Motivaufnahme, frühe Reprise,
Varianten und koordinierte melodische Vordergrundfenster. Die 40 Studien sind
jedoch **keine direkt ladbaren Engine-Presets**. Ihr Ereignisstrom darf nicht mit
bereits vorhandener generativer Fähigkeit verwechselt werden. Insbesondere die
vorläufige Umsetzbarkeitstabelle L der Forschung überschätzt die direkte Nutzbarkeit.

Das vollständige Inventar unten umfasst alle **276 IDs**. Die Einstufung bezieht
sich auf die Grundvorlage, nicht auf jede im Text vorgeschlagene Variation:

* **D / Direkt umsetzbar:** Datenimport mit vorhandenen musikalischen Typen; noch
  nicht implementiert. Bei H bedeutet das die definierte Akkord-/Bass-/Dauerfolge,
  keine automatische Übertragung ihres Systems auf sämtliche Rollen.
* **E / Musikalisch gleichwertig:** vorhandenes Verfahren unter genanntem Kontext;
  exakte Forschungsnoten und Auswahlanker sind damit nicht garantiert.
* **K / Kleine Erweiterung:** begrenzter neuer Datenverbraucher oder gezielte Fähigkeit;
  keine Aussage, dass alle K gemeinsam ein kleiner Auftrag wären.
* **G / Größere Erweiterung:** zusammenhängende Planung über mehrere Rollen/Abschnitte
  oder längere Melodiebögen. Nicht durch Verkürzen als implementiert ausgeben.
* **U / Unklar:** für eine verbindliche Umsetzung zuerst zu klären. Einzelne offene
  Varianten-/Routingfragen stehen separat; sie machen nicht jede Grundvorlage unklar.

54/76 Harmonievorlagen passen **strukturell** in bestehende Akkordtypen, acht Slots
und ganzzahlige Takte. Bei fünf davon verlangt das charakteristische Verfahren
zusätzlich Systemwechsel oder parallele Lagenführung: H20/H21/H58/H60/H70.
Die restlichen 49 erhalten D für den Akkorddatenanteil. Gesamtbewertung der
276 Grundvorlagen: 49 D, 3 E, 160 K und 64 G; keine gesamte Grundvorlage muss wegen
unlesbarer Daten als U eingestuft werden. Offene semantische Teilfragen bleiben
davon unabhängig ausdrücklich aufgeführt. 16 Vorlagen benötigen
fehlende exakte Klangdefinitionen; sechs weitere überschreiten Zeit-/Slotgrenzen.
Alle 76 sind über Anker geometrisch erreichbar, aber noch keine ist als Williams-
Vorlage im Plugin registriert. Kein neues Profil ist in dieser Phase auswählbar.

## 2. Tatsächlicher Produktionspfad und wiederverwendbare Fähigkeiten

Codeverweise beziehen sich auf den Repository-Stamm.

| Bereich | Vorhanden und tatsächlich benutzt | Grenze für Williams |
|---|---|---|
| Harmonie | `Source/HarmonyTypes.h::HarmonyTemplate`, `Chord`, `coloredChordType`; `data/harmony/catalog.json`; `scripts/generate_harmony_catalog.py` validiert und erzeugt statische Laufzeitdaten | `Chord.bars` ist **int**, `kMaxChords=8`, Summe acht ganze Takte. Die Zeitbasis-Migration hat dieses Datenformat nicht erweitert. |
| Farben | `ChordTypes.generated.h::kShapes`: 27 Typen; `ChordColoration::protectedColor` verhindert zusätzliche Farben/Zwischenharmonik; `ScoreEngine.h::chordFor` | Kein automatisches Ersetzen fehlender Typen. H27 `Cq` hat C–F–B♭, Tonklassen {0,5,10}; vorhandenes `Quartal` hat zusätzlich Es {0,5,10,3}. Daher **nicht** gleichsetzen. |
| Bass | `Chord.bass`, `rawBassPattern`, `chooseBass`, BassPedal, BassAlternating, BassPendulum, BassWalking; Slash-Bässe vorhanden | `BassPhrase.h::planBassPhrase` ist über `melodicBassAllowed` auf passende Pop/Rock-4/4-Fälle begrenzt. Kein allgemeiner Score-Cantus oder frei autorisierter Dissonanzbass. `Folgt Akkorden AUS` ist kein beliebiger Basslinien-Sequencer. |
| Stimmführung | `VoiceLeading.h`; `ScoreEngine.h::clearHarmonicEntries`, harmonische Eintrittshistorie und Akkordanker | Gemeinsame Töne/geringe Wege sind nicht dasselbe wie parallele Dreiklangsführung. Planing benötigt explizite Priorität für dieselbe Umkehrung/Stimmenzuordnung. Kaltes Seek ohne Vorgeschichte bleibt akzeptierte Grenze. |
| Besetzung | `ChordDisposition.h` trennt Stimmenzahl und Weite, erhält charakteristische Farben | Adapter `ScoreEngine.h` aktiviert diese besondere Automatik derzeit nur für geeignete Pop/Rock-Flächen. Nicht als allgemein aktiven Score-Mechanismus ausgeben. |
| Zeit | `MusicalTime.h`, `MusicalExecution.h::{Candidate,first,quarters}`: 64-Bit, 960 PPQ, Harmonie nominal, Rhythmus groove, Releases vor Planung vor Rhythmus | 320-Tick-Triolen sind exakt darstellbar, aber vorhandene Barry-Zellen werden in `sixteenth` erzeugt. Neue Tick-Daten müssen echte Onsets anmelden; kein Rundungsadapter und keine erneute Scheduler-Migration nötig. |
| Rhythmik | `RhythmPlan.h::planRhythmicInterlock`: gemeinsamer Bass/Arp-Plan; `BarryVocabulary.h::planBar`, `ScoreEngine.h::authoredRhythmBar` | Interlock ist bewusst eng und Pop/Rock-begrenzt. Barry-Raster speichert Bass und Bewegung; Bewegung geht zum Arp. Nicht automatisch KF, TU, ST oder mehrere beliebige Rollen. 16 Onsets pro `RhythmPlan`, `uint16_t`-Masken; 5/4 mit vielen Einsätzen nicht blind hineinkopieren. |
| Tonvorrat | `ModalContext.h::Mode`, `modalContext`, `PassingPolicy` unterstützt Ionisch/Mixolydisch/Dorisch/Äolisch und eindeutigen Kontext; kontrollierte Pop-Durchgänge | Kein Lydisch, Phrygisch, Okt-/Hexatonik, harmonisches Moll oder gemeinsamer variabler Rollen-Tonvorrat. `ArpOctatonic` ist eine Figurenwahl, kein solcher Systemkontext. |
| Motiv | `CompositionCore.h::{RememberedMotif,MotifCatalog,MotifUse,deriveMotif,realizeScoreMotif,MotifRepriseProgress}`; `motifOccurrence`, `continueMotif`, `motifStep` | Original maximal **8 Noten**, Ableitungsfigur maximal 10, Katalog zwei Materialien/Szene. Sechs kurze Williams-Motive überschreiten schon acht Noten; lange Phrasen sind kein Datenimport in diesen Speicher. |
| Vorlagenmotiv | `ScoreEngine.h::authoredMotif` und `BarryVocabulary.generated.h` liefern Barry-Material | Durchsucht ausdrücklich Barry-Daten. Tonmasken werden über die Gate-Dauer mit Akkordtönen geschnitten. Eine oktatonische Linie über einem statischen Dreiklang wird verworfen oder musikalisch verfälscht, selbst wenn alle Töne zum gewünschten System gehören. |
| Rollen | `CompositionCore.h::{RoleNeed,InstrumentCapabilities,PlayingTrack,OutputDescription}`; `planForeground`, `playableMelodyHandoff`, `motifVoiceWindow` | Gezielte Melodie→Dialog-Suffixantwort und Dialog→Arp-Antwort vorhanden; kein Kanon, keine automatische Gegenstimme→Melodie-Übergabe und keine allgemeine Studien-Orchestrierung. |
| Stilpolitik | `CompositionPolicy.h::{TexturePolicy,FreeCompositionPolicy,CompositionProfile,policyForContext}` | Aktivität/Hysterese, Arp-Tempo, Wiederkehr und einige Begleitentscheidungen steuerbar. `authoredCells` greift derzeit Barry-spezifisch zu; für Williams klein auf gemeinsame Datenzugriffe ausrichten, keine zweite Engine und kein universelles Regelwerk. |
| XYZ | `Generator::{weight,keepRatio,candidates,pick}`, ID-basierte `harmonicPreference` | Bestehende gewichtete Distanz und relative Variety-Schwelle erhalten. Profilgewichte wirken erst **nach** XYZ-Zulässigkeit; sie beheben keine entfernten Anker. Y beeinflusst weiterhin Aktivität/Velocity/Muster; gewünschte vollständige Y/Z-Unabhängigkeit ist keine vorhandene Garantie. |

Vorhandene Akkordtypen umfassen Dur/Moll, Septimen, mMaj7/mMaj9, verminderte
Dreiklänge/Septimen, halbvermindert, Sus2/Sus4/7sus4, Add9/mAdd9, Dur-/Mollnonen,
6/m6, Aug, Maj7#5, Maj7#11 und Maj7sus2. Es fehlen insbesondere 6/9,
Moll-add#4, 7#5, Dur-add♭3, Moll-♭6/mMaj7♭6, AugMaj7#9, Moll-add♭9 und der
**dreitönige** Quartstapel. Polychorde/Mengen brauchen zusätzlich eine Bedeutung
für Komponenten/Register, nicht bloß einen ähnlichen Namen.
`ChordShape.iv[5]` fasst fünf Intervalle: sechstönige Polychorde und siebentönige
Cluster passen auch speicherseitig nicht. Einfaches Zusammenwerfen oder Entfernen
charakteristischer Töne ist kein zulässiger Import.

## 3. Instrumentierung, Stich und Artikulation

Neun MIDI-Ziele bleiben von der Kompositionsstrategie getrennt. `outputCatalog`
setzt interne Generatorannahmen, **keine erkannte externe Patchfähigkeit**.
Lang-/Kurz-Ausgänge von Harmonie und Bass können unterschiedliche Instrumente
enthalten; gleiche Rolle bedeutet nicht gleiche Artikulation.

| Ziel | Interne Polyphonie | Maximale Dauer |
|---|---:|---|
| Harmonie lang / kurz | 6 / 9 | sehr lang / 720 Ticks |
| Bass lang / kurz | 1 / 1 | sehr lang / 960 Ticks |
| Arp | 1 | 7680 Ticks |
| Tupfer | 4 | 720 Ticks |
| Stich | 1 | 480 Ticks |
| Dialog / Melodie | 2 / 1 | sehr lang |

`Settings.stichFixed` ist im reinen Engine-Struct initial false; der echte
Plugin-Prozessor setzt ihn aus dem vorhandenen Modusparameter (`PluginProcessor.cpp`,
`pStichMode`, Wert 0 = fester Trigger). Entscheidend für diesen Auftrag:
**Den Stich nicht wegen der Studie auf tonal umschalten.** Bei fester Adressierung
ist nur die Triggernote bekannt, das Klangmaterial selbst unbekannt.
16 Studien liefern zweistimmige tonale ST-Schläge (Liste in JSON). Diese sind
entweder mit passender kurzer Harmonie musikalisch neu zuzuordnen oder müssen als
nicht exakt darstellbar ausgesetzt werden; Rhythmusakzent und harmonische Bedeutung
getrennt behandeln. Zwei MIDI-Töne einfach auf denselben Trigger abzubilden kann
Doppeltrigger/Notenverwaltung verfälschen und erhält die Tonhöhenfunktion nicht.

Zu lange Kurznoten betreffen S02/S07/S21/S22/S26/S29 und T01/T02/T06/T08.
Beispiele: S21 hat 27 KF-Noten über 720 Ticks; S07 hat zwölf KB-Noten über 960.
Nicht automatisch auf Lang-Ziele routen: deren Artikulation/Verfügbarkeit muss
passen; sonst Vorlage verwerfen oder musikalisch begründete Variante planen.
M41 reicht bis E6; die voreingestellte Melodielage 60–84 kann das nicht unverändert
spielen. Gemeinsame Oktavtransposition prüfen, nicht einzelne Gipfeltöne abschneiden.

## 4. Unabhängige Prüfung der Forschung

Reproduzierbar: `python docs/research/john-williams/audit.py` (nur Offline-Daten).
`TECHNICAL_INVENTORY.json` enthält jede Vorlage, Quellzeile, Abhängigkeiten,
Akkord-/Rhythmus-/Melodiedaten und die konkreten Studiendatenkonflikte.

Bestätigt: alle 276 IDs; 526 Akkordereignisse mit konsistenten Symbolen,
Tonklassen und explizitem Bass; alle 76 Summen acht Takte; gültige XYZ-Anker;
keine fehlenden JW-Querverweise; korrekte Rasterlängen und Haltezeichen;
korrekte Motiv-/Phrasentaktsummen; sämtliche angegebenen Kurzmotivintervalle
unabhängig aus Tonhöhen bestätigt; alle prüfbaren harmonischen Systemzugehörigkeiten;
40 MIDI-Dateien mit 960 PPQ; **7662 CSV-Noten = 7662 MIDI-Noten** einschließlich
Einsatz, Dauer, Tonhöhe, Velocity und Rolle; keine offenen/gleichen überlappenden
Noten innerhalb einer Spur, keine unzulässigen Dauern oder Töne außerhalb 21–108.
MIDI-Spurnamen verwenden teils Latin-1 statt UTF-8; Offline-Parser berücksichtigt das.
Die Originale bleiben unverändert.

Das bestätigt Datenkonsistenz, **keine akustische Qualitätsabnahme und keine unabhängig
verifizierten musikwissenschaftlichen Belege**. Quellen wurden in dieser Phase
nicht extern neu recherchiert. Symbole wurden unabhängig aus Intervalldefinitionen
abgeleitet, nicht durch bloßes Nachzählen der mitgelieferten Prüftabelle bestätigt.
Pantriadik/chromatische Systeme erlauben keine eindeutige Skalenmitgliedschaft.
Vorhalte/Skalentöne/Dissonanzbässe werden nicht pauschal als falsche Akkordtöne bewertet.
Die Behauptung „keine Haltetonkonflikte“ der gesamten Forschung ist hier nicht als
vollständige satztechnische Freigabe bestätigt; die automatische Prüfung validiert
Notenpaare und harmonische Tabellen, nicht jede ästhetische Absicht sämtlicher Stimmen.

Konkrete Korrektur-/Klärungsliste vor Import (Originale nicht bearbeiten):

1. Kopftext nennt vier lange Modellstudien; tatsächlich sind S25–S30 **sechs**
   Studien über 16/32 Takte. Die detaillierten Abschnitte sind maßgeblich.
2. H04-Variation „D durch D/F♯“ ergibt nicht die beschriebene Bassfolge C–D–E–F♯.
   Grundfassung ist valide; Varianten-Bassfolge zuerst eindeutig notieren.
3. `Cq` ist dreitönig; kein Alias für den bestehenden vierstimmigen Quartaltyp.
4. Festes Stich-Routing gegen tonale/mehrstimmige ST-Studien explizit entscheiden.
5. Kurz-Ausgangsdauern und Instrumentenregister prüfen; keine heimliche Umadressierung.
6. H48/H53/H62/H64/H65/H66 brauchen 12/15/14/16/12/12 Slots und Halbtakte.
   Kein Zusammenziehen verschiedener Klänge auf acht Slots und keine Aufrundung.
7. Systemwechsel H20/H21: Klangfolgen sind darstellbar, aber bisher kein gültiger
   mehrrolliger Kontextwechsel. Keine Behauptung, ein einziges Modusfeld reiche aus.
8. Ganzton H26/M31 bleibt stilistische Hypothese; konstruierte Studien bleiben E,
   auch wenn ein verwandtes Verfahren belegt ist. Keine Transkriptionsbehauptung.

Strenger Dublettenabgleich gegen sämtliche produktiven Katalogvorlagen (Tonklassen,
Bass, Dauern, Transpositionen, benachbarte gleiche Klänge zusammengefasst): keine
vollständige Sequenzgleichheit gefunden. Auch unter den 76 neuen Grundfolgen
finden sich bei dieser normalisierten Prüfung keine transpositionsgleichen Dubletten. Das heißt nicht, dass alle Akkordbausteine
neu wären: H01 teilt die mixolydische Achse mit 2015/2019, aber andere Dauern/
Sus-Abschluss; H14 ist nicht 1013 (dort F♯-Dur und verminderter Abschluss).
Polychord-Komponenten und Lagen bleiben zusätzliche Identitätsmerkmale; der
Tonklassenvergleich kann deren musikalische Gleichwertigkeit nicht beweisen.

## 5. XYZ-Abdeckung – tatsächliche Auswahlfunktion

`coverage.py` kompiliert eine **unveränderte** Offline-Abfrage von
`Generator::weight` und `keepRatio`. Raster 21³ = 9261 Punkte einschließlich aller
Flächen/Kanten/Ecken, Variety 0/0,5/1. Schwelle wie `pick`, ohne den zusätzlichen
1e-9-Anzeigetoleranzterm von `candidates`. Distanz:
`sqrt(dx² + 0,49 dy² + 0,64 dz²)`, Gewicht `exp(-d²/0,05)`.
Die Williams-Pools sind **Simulationen**, keine importierten Laufzeitpools.
Alle Profilgewichte 1: Es gibt noch keine fachlich festgelegten Williams-Gewichte.
Gemessen wird positive Auswahlzulässigkeit, nicht MIDI-Häufigkeit oder realer
Profil-Produktionsbetrieb. Alle Einzelresultate und Randpunkte: `XYZ_COVERAGE.json`.

| Pool | Variety | Kandidatenmittel | Punkte mit nur 1 Kandidaten |
|---|---:|---:|---:|
| bestehend Neutral Score, 48 | 0 / 0,5 / 1 | 1,01 / 3,15 / 10,29 | 9196 / 2410 / 23 |
| alle Williams, 76 | 0 / 0,5 / 1 | 1,01 / 4,63 / 16,38 | 9183 / 732 / 0 |
| nur strukturell passende Williams, 54 | 0 / 0,5 / 1 | 1,01 / 3,92 / 12,80 | 9198 / 1367 / 0 |

Variety 0,5: Kandidatenbereiche 1–14 / 1–17 / 1–16. Alle 76 bzw. 54 Anker sind
im Raster bei jeder geprüften Variety mindestens irgendwo zulässig. Das ist keine
Garantie gegen einen später durch Artikulation/Harmonie/Mute unspielbaren Plan.
Größte Entfernung zum nächsten Anker: bestehend 0,673; Williams gesamt 0,398;
struktureller Teilpool 0,470. Bei Entfernung >0,35 (diagnostische Setzung, kein
musikalischer Grenzwert) liegen 1369 / 23 / 174 Punkte. Relative Auswahl allein
kann also auch bei nur entfernten Klängen Kandidaten liefern.

| XYZ-Ecke | Neutral Anzahl / Distanz | Williams gesamt | struktureller Teilpool |
|---|---|---|---|
| 0/0/0 | 1 / 0,306 | 1 / 0,364 | 1 / 0,364 |
| 0/0/1 | 2 / 0,314 | 1 / 0,363 | 2 / 0,461 |
| 0/1/0 | 1 / 0,398 | 2 / 0,243 | 2 / 0,243 |
| 0/1/1 | 1 / 0,151 | 1 / 0,229 | 2 / 0,356 |
| 1/0/0 | 1 / 0,236 | 1 / 0,243 | 2 / 0,297 |
| 1/0/1 | 1 / 0,673 | 1 / 0,388 | 1 / 0,388 |
| 1/1/0 | 1 / 0,138 | 2 / 0,330 | 2 / 0,330 |
| 1/1/1 | 1 / 0,665 | 1 / 0,329 | 2 / 0,470 |

Mehrzahl der Eckpunkte bleibt mit Standard-Variety **musikalisch eng**, trotz
zählbarer Besetzung aller Oktanten. Verschiedene Dauern derselben Dreiklänge sind
nicht automatisch verschiedene harmonische Verfahren. H47/H48 als einzige
Harmonieanker ≥0,9 Z sind beide zunächst technisch blockiert. Die Spitze kann
nicht allein durch Gewichtung eines direkt importierbaren Pools abgedeckt werden.
Kein Grund, XYZ-Treue abzuschaffen: Material und Begleitverfahren gezielt vervollständigen,
keine entfernten Vorlagen erzwingen und keine erfundenen Anker als Messwerte behandeln.

## 6. Host-Taktarten und Musik ohne Melodierollen

Harmonien sind acht **4/4**-Takte. Acht Host-Takte anderer Metrik sind zeitlich und
musikalisch nicht dieselbe Folge. Akkordwechsel auf Host-Taktgrenzen sind technisch
möglich; eine Proportionierung oder taktweise Übernahme verlangt aber eine explizite
Interpretation des harmonischen Rhythmus. Motive/Raster nicht automatisch dehnen,
abschneiden oder eine 4/4-Tonfolge zum 7/8-Pattern erklären. Hosttempo bleibt maßgeblich.

R-Vorlagen: 34×4/4, 3×4/4T, 1×7/8, 2×5/4, 4×6/8, 2×3/4, 1×3/2, 1×2/2.
Bass: 37×4/4, 1×2/2, 2×6/8. 4/4T ist eine Unterteilung des 4/4-Hosts,
**keine neue Taktart**. 3/4 und 6/8 haben gleiche Länge, aber andere Akzentordnung;
Hemiolen R19/R44 brauchen diese bewusst getrennten metrischen Sichtweisen.
Nicht passende Vorlagen auslassen und die abgenommene freie Musik fortsetzen;
niemals die DAW-Taktart umstellen. Für 3/8 und 5/8 fehlen eigene passende Raster;
7/8 hat nur R05 und keine gleich umfangreiche Bassfamilie. Kein Anspruch auf
Williams-spezifische Gleichabdeckung sämtlicher vorhandener Host-Taktarten.

Ohne HM/GS bleibt die eigentliche Profilkombination entscheidend: H03 + Pedal und
leise Achtel, H17 mit explizitem Dissonanzbass und komplementären kurzen Akkorden,
H16/H19 mit rhythmisch gemeinsam geführtem Bass/KF; nicht alles durch schnellen Arp
kompensieren. S20 (288 Noten), S30 (620), T09 (78) sind schon in den Forschungsdaten
rein begleitungsgetragen. Sie sind Prüfbeispiele, keine fertigen Presets; ihre
Notenzahlen sind ausdrücklich keine Zielquote. Ohne Melodierollen muss das Profil
auch in ruhigen Ecken funktionieren, während bei hoher Unruhe Bass/KF/TU den
Zusammenhang tragen. Keine generelle Pflicht auf Pedal, Lange Fläche oder Arp-Achtel.

## 7. Priorisierte Folgeaufgaben und erster hörbarer Schritt

**P0: Datenentscheidungen klären.** H04-Variante, ST-Übertragung, Kurznoten und
Cluster-/Polychordbedeutung festhalten. Kanonische Originale nicht überschreiben;
spätere validierte Importdaten referenzieren IDs und begründen Abweichungen.

**P1 – erster zusammenhängender Hörschritt, noch nicht umgesetzt:** Williams als
zusätzliches Score-Profil in vorhandener Auswahl; gemeinsame Engine, eigener
validierter Pool und eine kleine gemeinsame rhythmische Datenanbindung für
**kurze Harmonie plus Bass**. Ausgangsmenge H03/H06/H11/H12/H13/H14/H16/H17/H19/
H34/H41/H46/H49/H50/H63/H67: lydisches Pedal, leise Oktatonik, Dissonanzbass,
Medianten und warme Klänge, nicht nur zwei Farbakkorde. Das ist ein kuratierter
Startpool, kein Ersatz für die 76 Vorlagen; dessen eigene XYZ-Abdeckung muss vor
Implementierungsabnahme neu gemessen werden. Die 54er-Simulation beweist nicht die
Abdeckung dieser 16er-Auswahl.

Dazu R03/R24/R26/R37 mit passenden Bassbausteinen B01/B04/B18 als erste 4/4-
Kombinationen. R37 erfordert die neue Rollenadressierung für KF; Barry-Bewegung
bloß als Arp wiederzugeben reicht nicht. H17/H46 können ihre Dissonanzbässe bereits
über explizite Bassvorgaben erhalten, ohne jetzt einen freien Bassliniengenerator
zu entwickeln. Die Antwort auf hohe Unruhe ist Akzentwechsel/komplementäre Figuren,
nicht pauschales Tempo oder maximale Dichte. Keine festen Einzel-ID-Regeln im Renderer:
Vorlagenkombinationen/Anforderungen als kleine Datenzuordnung, manuelle Muster
haben Vorrang, Instrumentierung bleibt unabhängig.

Abnahme P1: derselbe Seed/XYZ Neutral gegen Williams, über alle acht Eckbereiche,
ruhige und intensive Fahrten, ohne HM/GS; Fläche/Bass müssen nachweisbar zwischen
langen und rhythmischen Funktionen wechseln, Harmonie wirklich fortschreiten.
Mute/Solo/Follow/Aktivierung/Instrumententauglichkeit, statische Farbe vs. Bewegung
und Szenen-/Endsteuerung bewahren. Neutral/Barry unverändert. Mit Melodierollen
zunächst ausschließlich die abgenommene gemeinsame Motivik nutzen; **noch keine
vollständige Williams-Motivik behaupten**. Stille und stationäre Harmonie dürfen
musikalisch sinnvoll bleiben; sie dürfen nicht global erzwungen werden.

**P2:** fehlende exakte kleine Akkorddefinitionen, insbesondere 3-Ton-Quartal,
Moll-add#4 und 6/9, über vorhandenen validierten Datenpfad. Transposition aller
zwölf Tonarten und charakteristische Tonklassen prüfen; keine automatische Färbung.
Polychordregister/Cluster als gesonderte Fähigkeit erst bei Bedarf, nicht als
Vorwand für eine universelle Symbolsprache.

**P3:** gemeinsame rhythmische Zeitpositionen der Vorlagen auf Tick-Onsets beziehen,
Triolen 320 Ticks und passende ungerade Hostmetren einführen; bestehende Dispatcher-
Schnittstellen verwenden. R02/R34/R45, R05/R06/R19/R44 als getrennte musikalische
Testgruppen. Swing nur ausdrücklich geeignete Ereignisse verschieben lassen.

**P4:** expliziter Tonvorratskontext für passende Rollen und begrenzte Bass-Tonregeln
(Pedal, relative Intervalle, feste transponierbare Tonfolge). Erst Okt-A/Hex-C und
Lydisch bedarfsgerecht, kein Systemkatalog auf Vorrat. Nicht-Akkordtöne funktional
zulassen, beabsichtigte Dissonanz nicht auflösen müssen. S12/P06 und B07/B33/B35
werden dadurch überhaupt erst charaktertreu möglich. Beide Follow-Einstellungen
bewusst festlegen; OFF nicht durch Profil übersteuern.

**P5:** harmonisches Zeitmodell (halbe Takte und ≥16 Slots) separat. Nominale
Harmonieereignisse bleiben swingfrei. H48/H53/H62/H64/H65/H66 unverändert als
Regression; nichts zusammenlegen, um bestehende Grenzen zu umgehen.

**P6:** kurze Williams-Motivdaten in den vorhandenen Kern integrieren, genaue
Quellintervalle und autorisierte Nicht-Akkordtöne, Register/Artikulation und tatsächliche
Aufnahme prüfen. Vorher Acht-Noten-Grenze gezielt für M10/M11/M12/M16/M32/M41
entscheiden; nicht als Fragmente importieren und anschließend Vollständigkeit behaupten.
Bestehende frühe Reprise, Pausen und Rollenreservierungen weiterverwenden.

**P7, später:** längere Phrasen, modale Systemübertragung, gerichtete Rollenübergaben,
Abschnittsentwicklung und exaktes Planing. Das sind reale musikalische Lücken;
aber keine Voraussetzungen für den ersten aussagekräftigen Hörschritt. Keine
Williams-Sonderengine und keine allgemeine 32-Takt-Orchestrierungsplattform.

## 8. Prüf- und Hörkriterien der späteren Implementierung

* Zuerst vorhandene Referenzrenderings einfrieren; Neutral/Barry für statisches XYZ,
  langsame/schnelle externe Fahrten und Variationswechsel über mindestens 128 Takte
  vergleichen. Unbegrenzter Modus ohne Fahrt ist ein eigener Pflichtfall.
* Tatsächlich ausgegebene Harmonie/Bass/Pattern-ID, Akkordwechsel, Gates, Register,
  Pausen und Rolle protokollieren; reine Auswahlstatistik reicht nicht.
* Williams-Raster zunächst exakt gegen Originaldaten prüfen; später semantisch
  begründete Varianten einzeln markieren. Gerade/Triolen, alle Transpositionen,
  passende und unpassende Hostmetren, unterschiedliche Tempi/Swing/Blockgrößen.
* Motive anhand realer Ton-/Einsatz-/Dauerfolgen und Konturrichtung prüfen, früheste
  vollständige Reprise und spätere Varianten getrennt zählen. Nicht-Akkordtonfunktion
  und Systemwechsel ausdrücklich prüfen, nicht pauschal an Akkordmasken scheitern lassen.
* Ohne HM/GS und mit jeder Stimme einzeln hören; kein Dauerschweigen zweier Rollen,
  keine pauschale Dauerführung, kein Arp als einzig bewegte Begleitung.
* Technisch: deterministische Wiederholung, Seek/Loop/Neustart/Chase, Note-on/off-
  Ledger, Kanalteilung, tatsächlicher Plugin-Live-/Exportvergleich, keine Allokation/
  Dateioperation im Audiothread, ASan/UBSan und reguläre Suite nach Codeänderungen.
* Hörabnahme: leise geheimnisvolle, warme, heroische und unruhige Bereiche bei
  gleicher Instrumentierung vergleichen, zusätzlich Klavier-/Synth-/Orchesterklang.
  Akzentordnung vs. Lautstärke/Dichte getrennt hören (S29/S30 als Zielvergleich).
  Die Forschungs-MIDIs sind konstruiert und kein Nachweis für Engine-Klangqualität.

## 9. Vollständiges ID-Inventar

Jede Zeile ist eine eigene Grundvorlage. Bei H: Akkordsymbol und Dauer in Takten;
bei M/P: Notenzahl und Referenzkontexte; bei R/B: Metrik und konkrete Raster-/Tonregel;
bei S/T: Querverweise und nachgewiesene Routingprobleme. Ausführliche Quellnoten,
XY-Anker und Referenzen stehen zusätzlich unverändert im kanonischen Dokument und
maschinenlesbar in `TECHNICAL_INVENTORY.json`. Folgende Tabelle wird aus dessen
Einzelbewertungen erstellt, nicht aus den Namen allein.

<!-- generated inventory -->

### Harmonie

| ID | Grundvorlage / konkrete Daten | Status | Technische Zuordnung / Grenze |
|---|---|---|---|
| JW-H01 | Mixolydische Fanfarenachse: C (2) → Bb (1) → F (1) → C (2) → Gsus4 (1) → C (1); XYZ 0.8/0.75/0.3 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H02 | Subtonischer Halbschluss (♭VII–V): C (2) → F (1) → Bb (1) → C (2) → Bb (1) → G (1); XYZ 0.75/0.7/0.4 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H03 | Lydische Schwebe (II♯ über Tonikapedal): C (2) → D/C (2) → C (2) → D/C (1) → Cmaj7 (1); XYZ 0.85/0.3/0.25 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H04 | Lydischer Aufschwung: C (2) → D (1) → Em (1) → Am (1) → D (1) → C (1) → C (1); XYZ 0.9/0.65/0.35 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H05 | Lydisches Nachglühen: C (2) → Cmaj7#11 (2) → C6/9 (2) → Cmaj7 (1) → C (1); XYZ 0.85/0.15/0.2 | K | fehlende exakte Akkorddefinition/Polychord- oder Mengenbedeutung |
| JW-H06 | Tonikapedal mit Mischklängen: C (2) → F/C (1) → Fm/C (1) → C (2) → Ab/C (1) → C (1); XYZ 0.65/0.35/0.2 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H07 | Dominantpedal mit wechselnden Oberklängen: C/G (2) → F/G (2) → Eb/G (1) → F/G (1) → G (2); XYZ 0.6/0.6/0.45 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H08 | Chromatische Großterz-Rückung: C (2) → G (1) → C (1) → E (2) → B (1) → E (1); XYZ 0.8/0.65/0.4 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H09 | Chromatisch modulierende Kadenzauflösung: C (2) → F/A (1) → G (1) → E (2) → A/E (1) → E (1); XYZ 0.75/0.55/0.45 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H10 | Gemischte Plagalkadenz: C (2) → F (1) → Fm (1) → C (1) → Dm7b5 (1) → G7 (1) → C (1); XYZ 0.7/0.45/0.15 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H11 | Moll-Tonika zur Dur-Subdominante: Cm (2) → F (2) → Cm (2) → F/A (1) → Cm (1); XYZ 0.4/0.3/0.35 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H12 | Moll-Dreiklänge im Kleinterzzyklus: Cm (2) → Ebm (1) → Cm (1) → F#m (1) → Cm (1) → Am (1) → Cm (1); XYZ 0.15/0.35/0.55 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H13 | Moll-Pendel i–♭vi (hexatonisch): Cm (1) → Abm/C (1) → Cm (1) → Abm/C (1) → Cm (1) → Abm/C (1) → Em/B (1) → Cm (1); XYZ 0.15/0.75/0.4 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H14 | Tritonus-Mollwechsel: Cm (2) → F#m (2) → Cm (2) → F#m (1) → Cm (1); XYZ 0.2/0.45/0.6 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H15 | Dur-Tritonus-Schweben: C (2) → F# (2) → C (2) → F# (1) → C (1); XYZ 0.7/0.3/0.5 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H16 | Kleinterz-Durzyklus: C (1) → Eb (1) → F# (1) → A (1) → C (1) → Eb (1) → F# (1) → A (1); XYZ 0.55/0.7/0.75 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H17 | Durklang über Halbton-Bass: C/Db (2) → Eb/E (2) → F#/G (2) → A/Bb (2); XYZ 0.3/0.85/0.8 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H18 | Oktatonischer Liegeklang mit Repetition: Cm(add#4) (8); XYZ 0.25/0.6/0.65 | K | fehlende exakte Akkorddefinition/Polychord- oder Mengenbedeutung |
| JW-H19 | Oktatonischer Basslauf: Cm (1) → A/Db (1) → Eb (1) → C/E (1) → F#m (1) → Eb/G (1) → Am (1) → F#/Bb (1); XYZ 0.35/0.65/0.7 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H20 | Wechsel zwischen zwei oktatonischen Tonvorräten: Cm (1) → Ebm (1) → A/Db (1) → Cdim7 (1) → D (1) → F (1) → Ab (1) → B (1); XYZ 0.3/0.7/0.75 | K | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots; expliziter Systemwechsel bzw. Parallelführung nicht durch Akkordliste garantiert |
| JW-H21 | Vermindertes Gelenk zwischen Tonal und Oktatonik: C (2) → Am (1) → Cdim7 (1) → Eb (1) → F# (1) → Cdim7 (1) → C (1); XYZ 0.5/0.5/0.6 | K | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots; expliziter Systemwechsel bzw. Parallelführung nicht durch Akkordliste garantiert |
| JW-H22 | Polychord-Schläge („Holst-Akkorde“): F#\¦C (2) → Eb\¦A (2) → F#\¦C (2) → C5 (2); XYZ 0.2/0.9/0.7 | K | fehlende exakte Akkorddefinition/Polychord- oder Mengenbedeutung |
| JW-H23 | Moll-Polychord-Oszillation: Cm (1) → Abm\¦Cm (1) → Cm (1) → Abm\¦Cm (1) → Cm (1) → Abm\¦Cm (1) → Abm (1) → Cm (1); XYZ 0.1/0.4/0.55 | K | fehlende exakte Akkorddefinition/Polychord- oder Mengenbedeutung |
| JW-H24 | Hexatonischer Pol: C (2) → Abm (2) → C (2) → Abm (1) → C (1); XYZ 0.45/0.35/0.5 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H25 | Hexatonischer Zyklus: C (1) → Cm (1) → Ab (1) → Abm (1) → E (1) → Em (1) → C (2); XYZ 0.45/0.45/0.6 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H26 | Ganztonfläche: Caug (2) → D7#5/C (2) → C7#5 (2) → Caug (2); XYZ 0.6/0.25/0.6 | K | fehlende exakte Akkorddefinition/Polychord- oder Mengenbedeutung |
| JW-H27 | Quartenkette: Cq (1) → Dq (1) → Eq (1) → Dq (1) → Cq (1) → Aq (1) → Gq (1) → Cq (1); XYZ 0.7/0.75/0.5 | K | fehlende exakte Akkorddefinition/Polychord- oder Mengenbedeutung |
| JW-H28 | Sus-Pendel C2 – G7sus4: Csus2 (1) → G7sus4 (1) → Csus2 (1) → G7sus4 (1) → Am7 (1) → Fsus2 (1) → G7sus4 (1) → Csus2 (1); XYZ 0.8/0.45/0.35 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H29 | Großterzzyklus in Dur: C (1) → Ab (1) → C (1) → E (1) → Ab (1) → E (1) → C (2); XYZ 0.7/0.55/0.5 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H30 | Chromatischer Basslink: Am (1) → Fm/Ab (1) → Eb/G (1) → D/F# (1) → Dm/F (1) → C/E (1) → Fmaj7 (1) → G (1); XYZ 0.55/0.4/0.45 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H31 | Verminderter Septakkord statt Dominante: C (2) → F (1) → Am (1) → Dm7 (1) → Bdim7 (1) → C (2); XYZ 0.65/0.45/0.35 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H32 | Dur-Moll-Terz gleichzeitig: C (2) → F (1) → Ab (1) → C (2) → C(addb3) (2); XYZ 0.55/0.3/0.45 | K | fehlende exakte Akkorddefinition/Polychord- oder Mengenbedeutung |
| JW-H33 | Heroische Mischung ♭VI–♭VII–I: C (2) → Am (1) → F (1) → Ab (1) → Bb (1) → C (2); XYZ 0.8/0.85/0.3 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H34 | Moll-Trauer mit Sextakkord: Cm (2) → Abmaj7 (1) → Fm6 (1) → Cm/G (1) → G7sus4 (1) → G7 (1) → Cm (1); XYZ 0.25/0.3/0.2 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H35 | Undulation Tonika–Mediante: C (1) → Em/B (1) → C (1) → Em/B (1) → Am (1) → Em (1) → F (1) → C (1); XYZ 0.5/0.25/0.15 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H36 | Pandiatonische Add-Fläche: Cadd9 (2) → Fadd9/C (2) → Am7 (2) → Gsus4 (1) → Cadd9 (1); XYZ 0.75/0.2/0.1 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H37 | Quintfallsequenz mit Septimen und Zwischendominante: Cmaj7 (1) → Fmaj7 (1) → Bm7b5 (1) → E7 (1) → Am7 (1) → Dm7 (1) → G7sus4 (1) → Cmaj7 (1); XYZ 0.6/0.45/0.25 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H38 | Romantische Mischklänge über Pedal: Cmaj7 (1) → Fm6/C (1) → Cmaj7 (1) → Abmaj7/C (1) → Fmaj7 (1) → Fm6 (1) → Csus4 (1) → C (1); XYZ 0.6/0.35/0.3 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H39 | Chromatisch fallender Lamentobass: Cm (1) → G/B (1) → Gm/Bb (1) → F/A (1) → Fm/Ab (1) → Cm/G (1) → D7/F# (1) → G (1); XYZ 0.25/0.45/0.4 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H40 | Gemeinsamer-Ton-Wanderung über C: Cm (1) → Ab/C (1) → Am/C (1) → F/C (1) → Fm/C (1) → F#dim/C (1) → Ab/C (1) → Cm (1); XYZ 0.3/0.25/0.4 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H41 | Phrygische Lauer-Achse: Cm (2) → Db/C (1) → Cm (1) → Cm (2) → Db/C (1) → Cm (1); XYZ 0.15/0.25/0.45 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H42 | Dorisch-mystische Fläche: Cm7 (2) → Dm7 (2) → Cm7 (1) → Ebmaj7 (1) → Bbsus2 (1) → Cm (1); XYZ 0.35/0.3/0.25 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H43 | Ungarisch-Moll-Aktionsklang: CmM7 (2) → Ab (1) → B (1) → CmM7 (2) → Ebaug (1) → G (1); XYZ 0.2/0.75/0.65 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H44 | Moll mit kleiner Sexte, ausgehalten: Cm(b6) (4) → CmM7b6 (2) → Cm(b6) (2); XYZ 0.2/0.65/0.5 | K | fehlende exakte Akkorddefinition/Polychord- oder Mengenbedeutung |
| JW-H45 | Übermäßig mit großer Septime: CaugM7 (2) → CaugM7#9 (2) → Abm (2) → C (2); XYZ 0.45/0.6/0.7 | K | fehlende exakte Akkorddefinition/Polychord- oder Mengenbedeutung |
| JW-H46 | Dissonanzbass unter statischem Moll: Cm/F# (2) → Cm/Db (2) → Cm/F# (2) → Cm (2); XYZ 0.15/0.6/0.7 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H47 | Atonale (014)-Zellen im Kleinterzabstand: {C Db E} (1) → {F# G Bb} (1) → {Eb E G} (1) → {A Bb Db} (1) → {C Db E} (1) → {F# G Bb} (1) → {Eb E G} (1) → {A Bb Db} (1); XYZ 0.2/0.85/0.95 | K | fehlende exakte Akkorddefinition/Polychord- oder Mengenbedeutung |
| JW-H48 | Zwei oktatonische Vorräte im Halbtaktwechsel: C/Db (0.5) → Db/D (0.5) → C/Db (0.5) → Db/D (0.5) → C/Db (0.5) → Db/D (0.5) → C/Db (0.5) → Db/D (0.5) → C/Db (1) → Db/D (1) → C/Db (1) → Db/D (1); XYZ 0.3/0.95/1.0 | K | Harmoniedauer/Slot-Modell erweitern |
| JW-H49 | Heroische Medianten-Rückung: C (2) → E (2) → C (1) → Ab (1) → Bb (1) → C (1); XYZ 0.85/0.9/0.45 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H50 | Pantriadisches Staunen über Pedal: Cmaj7 (2) → Ab/C (1) → E/C (1) → Ab/C (1) → E/C (1) → Cmaj7 (2); XYZ 0.75/0.4/0.5 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H51 | Scherzando-Chromatik: C (1) → Eb (1) → C (1) → Ab (1) → F (1) → Db (1) → G7 (1) → C (1); XYZ 0.75/0.5/0.7 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H52 | Marsch mit einem chromatischen Moment: C (1) → F (1) → D7/F# (1) → G (1) → C (1) → F (1) → F#dim7 (1) → C/G (1); XYZ 0.8/0.45/0.45 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H53 | Aeolisch-phrygischer Action-Halbtaktwechsel: Cm (0.5) → Ab (0.5) → Bb (0.5) → Cm (0.5) → Cm (0.5) → Db (0.5) → Bb (0.5) → Cm (0.5) → Ab (0.5) → Bb (0.5) → Cm (0.5) → Eb (0.5) → Db (0.5) → Bb (0.5) → G (1); XYZ 0.3/0.8/0.6 | K | Harmoniedauer/Slot-Modell erweitern |
| JW-H54 | Oktatonische Moll-Parallelterzen über Pedal: Cm (2) → Ebm/C (2) → F#m/C (2) → Cm (2); XYZ 0.25/0.45/0.7 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H55 | Epische Breite mit langem harmonischem Rhythmus: C (4) → Ab (2) → Bb (2); XYZ 0.7/0.55/0.2 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H56 | Archaische Mollkadenz: Cm (2) → Bb (1) → Cm (1) → Fm (1) → Ab (1) → Gm (1) → Cm (1); XYZ 0.2/0.75/0.25 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H57 | Schweres Moll über Orgelpunkt: Cm (2) → Ab/C (2) → Fm/C (2) → Cm (2); XYZ 0.15/0.85/0.2 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H58 | Staccato-Planing über Pedal: C (1) → D/C (1) → E/C (1) → D/C (1) → C (1) → Bb/C (1) → Ab/C (1) → Bb/C (1); XYZ 0.75/0.25/0.7 | K | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots; exakte parallele Lagenführung zusätzlich planen (nicht durch Standard-Voice-Leading garantiert) |
| JW-H59 | Lydisch-♯2-Farbe: C (2) → Am/C (1) → C (1) → B/C (1) → C (1) → Em/C (1) → C (1); XYZ 0.7/0.3/0.65 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H60 | Maj7-Plagalpendel mit parallelem Abstieg: Cmaj7 (1) → Fmaj7 (1) → Cmaj7 (1) → Fmaj7 (1) → Eb (1) → D (1) → Db (1) → C (1); XYZ 0.75/0.35/0.55 | K | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots; expliziter Systemwechsel bzw. Parallelführung nicht durch Akkordliste garantiert |
| JW-H61 | Sus-Farbwechsel über Pedal: Csus2 (1) → Dsus2/C (1) → Fsus2/C (1) → Ebsus2/C (1) → Csus2 (1) → Absus2/C (1) → Bbsus2/C (1) → Csus2 (1); XYZ 0.7/0.2/0.6 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H62 | Lydische I↔II-Schleife: C (0.5) → D (0.5) → C (0.5) → D (0.5) → C (0.5) → D (0.5) → C (0.5) → D (0.5) → C (0.5) → D (0.5) → C (0.5) → D (0.5) → Em (1) → D (1); XYZ 0.9/0.8/0.65 | K | Harmoniedauer/Slot-Modell erweitern |
| JW-H63 | Mixolydische Maj7-Farbe ohne Dominante: Cmaj7 (2) → Fmaj7 (1) → Bbmaj7 (1) → Cmaj7 (1) → Dbmaj7 (1) → Bbmaj7 (1) → Cmaj7 (1); XYZ 0.8/0.6/0.5 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H64 | Dur-Planing über Pedal mit Großterzrückung: C (0.5) → Bb/C (0.5) → Ab/C (0.5) → Bb/C (0.5) → C (0.5) → D/C (0.5) → Eb/C (0.5) → F/C (0.5) → E (0.5) → D/E (0.5) → C/E (0.5) → D/E (0.5) → E (0.5) → F#/E (0.5) → G/E (0.5) → A/E (0.5); XYZ 0.85/0.85/0.6 | K | Harmoniedauer/Slot-Modell erweitern; exakte parallele Lagenführung zusätzlich planen (nicht durch Standard-Voice-Leading garantiert) |
| JW-H65 | Sus- und Quartenpuls: Csus4 (0.5) → Csus2 (0.5) → Bbsus2 (1) → Fsus2 (0.5) → Gsus4 (0.5) → Csus2 (1) → Csus4 (0.5) → Csus2 (0.5) → Bbsus2 (1) → Fsus2 (0.5) → Gsus4 (0.5) → Csus2 (1); XYZ 0.75/0.75/0.7 | K | Harmoniedauer/Slot-Modell erweitern |
| JW-H66 | Hexatonische Halbtonrutsche in Durklängen: C (0.5) → E/B (0.5) → C (1) → Ab (0.5) → E/G# (0.5) → Ab (1) → E (0.5) → Ab/Eb (0.5) → E (1) → C (0.5) → E/B (0.5) → C (1); XYZ 0.7/0.7/0.65 | K | Harmoniedauer/Slot-Modell erweitern |
| JW-H67 | Tritonusoszillation mit stufenweisem Abstieg: Cm (1) → F#m (1) → Cm (1) → F#m (1) → Bbm (1) → Abm (1) → Gm (1) → Cm (1); XYZ 0.15/0.75/0.35 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H68 | Chromatischer Mollchoral zum hexatonischen Polychord: Cm (2) → Bm (1) → Bbm (1) → Am (1) → Abm (1) → E\¦Cm (2); XYZ 0.1/0.65/0.4 | K | fehlende exakte Akkorddefinition/Polychord- oder Mengenbedeutung |
| JW-H69 | Dies-irae-Bass, choralartig (Typ 2): Cm (1) → G/B (1) → Cm (1) → Fm/Ab (1) → G/B (1) → Cm/G (1) → Fm/Ab (1) → Ab (1); XYZ 0.15/0.8/0.25 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |
| JW-H70 | Planing erster Umkehrungen in Moll: Cm/Eb (1) → C#m/E (1) → Dm/F (1) → C#m/E (1) → Cm/Eb (1) → Bm/D (1) → Bbm/Db (1) → Bm/D (1); XYZ 0.2/0.7/0.55 | K | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots; exakte parallele Lagenführung zusätzlich planen (nicht durch Standard-Voice-Leading garantiert) |
| JW-H71 | Halbton-Mollpaar (überlagert): Cm (1) → C#m\¦Cm (1) → Cm (2) → C#m\¦Cm (1) → Cm (1) → Bm\¦Cm (1) → Cm (1); XYZ 0.15/0.25/0.65 | K | fehlende exakte Akkorddefinition/Polychord- oder Mengenbedeutung |
| JW-H72 | Arpeggien mit Fremdton, stufenweise versetzt: Cm(b6) (1) → Dm(addb9) (1) → EbmM7 (1) → Dm(b6) (1) → Cm(addb9) (1) → BmM7 (1) → Cm(b6) (1) → Cm (1); XYZ 0.3/0.2/0.65 | K | fehlende exakte Akkorddefinition/Polychord- oder Mengenbedeutung |
| JW-H73 | Hohe Pedale, leise Reibungen: C5 (2) → {C D G} (1) → C5 (1) → {C Db G} (1) → C5 (1) → {B C G} (1) → Cmaj9 (1); XYZ 0.35/0.1/0.55 | K | fehlende exakte Akkorddefinition/Polychord- oder Mengenbedeutung |
| JW-H74 | Leise Oktatonik: Mollklänge im Kleinterzabstand: Cm (2) → Ebm\¦Cm (2) → Cm (1) → Am\¦F#m (1) → Ebm\¦Cm (1) → Cm (1); XYZ 0.2/0.2/0.6 | K | fehlende exakte Akkorddefinition/Polychord- oder Mengenbedeutung |
| JW-H75 | Cluster öffnet sich zu Dur: {B C Db} (1) → {Bb B C Db D} (1) → {A Bb B C Db D Eb} (2) → {G A B C D E} (1) → Cadd9 (1) → C (2); XYZ 0.55/0.45/0.6 | K | fehlende exakte Akkorddefinition/Polychord- oder Mengenbedeutung |
| JW-H76 | Pantriadische Kleinterzkette zur überhöhten Kadenz: Cm (2) → Ebm (1) → F#m (1) → Am (1) → Cm (1) → G#7 (1) → C#m (1); XYZ 0.3/0.55/0.55 | D | geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots |

### Rhythmus

| ID | Grundvorlage / konkrete Daten | Status | Technische Zuordnung / Grenze |
|---|---|---|---|
| JW-R01 | Marsch-Grundrhythmus; 4/4; KF  X..xX...X..xX.x.¦X..xX...X.x.X--- / ST  X...............¦X.......X.......; XYZ 0.55/0.7/0.4 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R02 | Repetitions-Triolen; 4/4T; KF  XxxXxxXxxXxx¦XxxXxxX--...; XYZ 0.4/0.75/0.6 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; Triolenzeit ist 320 Ticks, Einsatzproduktion noch Sechzehntel |
| JW-R03 | Achtelmotor mit 3+3+2-Akzent; 4/4; AR  X.x.x.X.x.x.X.x.¦X.x.x.X.x.x.X.x. / KB  X.....X.....X...¦X.....X.....X...; XYZ 0.55/0.6/0.6 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R04 | Synkopierte Militärfigur; 4/4; KF  X..X..X.X..X.X..¦X..X..X.X....... / ST  ..............X.¦................; XYZ 0.45/0.75/0.7 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R05 | Asymmetrisches 7/8-Ostinato (2+2+3); 7/8; KB  X...X...X.x.x.¦X...X...X.x.x. / ST  X.............¦X.......X.....; XYZ 0.35/0.7/0.7 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R06 | 5/4-Ostinato (3+2); 5/4; KF  X.x.x.x.x.x.X.x.x.x.¦X.x.x.x.x.x.X.x.x.x. / KB  X-----x.....X---x...¦X-----x.....X---x...; XYZ 0.35/0.7/0.65 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R07 | Tiefes Sechzehntel-Ostinato 3+3+2; 4/4; KB  X-xX-xX-X-xX-xX-¦X-xX-xX-X-xX-xX-; XYZ 0.25/0.7/0.75 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-R08 | Repetitionsakkord-Ostinato; 4/4; KF  X.xxX.xxX.xxX.xx¦X.xxX.xxX.x.X...; XYZ 0.3/0.65/0.7 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-R09 | Hetzende Sechzehntel mit Lücken; 4/4; AR  XxxxXxx.XxxxXx..¦XxxxXxx.XxXxXxXx; XYZ 0.5/0.8/0.85 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-R10 | Fanfaren-Auftakt; 4/4; HM  X-----------.xxx¦X--------------- / ST  ................¦X...............; XYZ 0.8/0.8/0.3 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R11 | Verstreute Tupfer; 4/4; TU  x.....x...x.....¦..x.....x.....x.; XYZ 0.4/0.25/0.55 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-R12 | Atmende Liegefläche; 4/4; LF  X---------------¦------------....; XYZ 0.5/0.2/0.2 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-R13 | Anschwellende Fläche (4 Takte); 4/4; LF  X---------------¦----------------¦X---------------¦---------------- / ST  ................¦................¦................¦............X...; XYZ 0.55/0.5/0.45 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R14 | Harfen-/Celesta-Achtel; 4/4; AR  X.x.x.x.x.x.x.x.¦x.x.x.x.x.x.x.x.; XYZ 0.75/0.3/0.35 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-R15 | Aufsteigendes Sechzehntel-Arpeggio; 4/4; AR  XxxxXxxxXxxxXxxx¦XxxxXxxxXxxx----; XYZ 0.6/0.45/0.6 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-R16 | 6/8-Wiegen; 6/8; AR  X.x.x.X.x.x.¦X.x.x.X.x.x. / KB  X-----x-----¦X-----......; XYZ 0.6/0.3/0.25 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R17 | 3/4-Scherzo; 3/4; KB  X...........¦X........... / KF  ....x...x...¦....x...x...; XYZ 0.75/0.45/0.5 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R18 | 3/2-Einschub; 3/2; KF  X-------x-------x------- / KB  X---------------x-------; XYZ 0.7/0.5/0.4 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R19 | Hemiole im 3/4; 3/4; KF  X.......X...¦....X....... / LB  X-----------¦X-----------; XYZ 0.6/0.5/0.55 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R20 | Drei gegen vier (punktierte Achtel); 4/4; AR  X..x..x..x..x..x¦..x..x..x..x..x. / KB  X...X...X...X...¦X...X...X...X...; XYZ 0.45/0.6/0.7 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R21 | Stich am Phrasenende; 4/4; ST  ................¦............X---; XYZ 0.4/0.7/0.5 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-R22 | Hämmernde 5/4-Schläge; 5/4; KF  X.X.X...X.X.X...X.X.¦X.X.X...X.X.X...X... / ST  X...................¦X...............X...; XYZ 0.2/0.9/0.7 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R23 | Punktierter Basso ostinato; 4/4; KB  X--xX---X--xX---¦X--xX---X--xX.x.; XYZ 0.4/0.65/0.45 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-R24 | Pendel-Viertel; 4/4; KB  X...x...X...x...¦X...x...X...x...; XYZ 0.65/0.45/0.3 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-R25 | Synkopierter Bass; 4/4; KB  X..X..X...X..X..¦X..X..X...X.X.X.; XYZ 0.35/0.75/0.75 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-R26 | Lauernder Herzschlag; 4/4; KB  X.......x.......¦X.......x....... / TU  ......x.........¦..........x.....; XYZ 0.2/0.25/0.45 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R27 | Kaskadeneinsätze; 4/4; GS  XxxxXxxx........¦....XxxxXxxx.... / HM  ........XxxxXxxx¦........XxxxX---; XYZ 0.75/0.8/0.6 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R28 | Ausdünnung (4 Takte); 4/4; KF  X.xxX.xxX.xxX.xx¦X.x.X.x.X.x.X.x.¦X...X...X...X...¦X-------........; XYZ 0.45/0.5/0.45 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-R29 | Verdichtung (4 Takte); 4/4; AR  X...X...X...X...¦X.x.X.x.X.x.X.x.¦X.xxX.xxX.xxX.xx¦XxxxXxxxXxxxXxxx; XYZ 0.45/0.65/0.6 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-R30 | Schlag und Stille; 4/4; ST  X...............¦................ / LF  ................¦........X-------; XYZ 0.3/0.6/0.5 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R31 | Heroisches Alla breve; 2/2; KF  X.......X...x.x.¦X.......X....... / KB  X.......X.......¦X.......X.......; XYZ 0.8/0.75/0.3 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R32 | 6/8-Abenteuergalopp; 6/8; KB  X-xX-xX-xX-x¦X-xX-xX----- / KF  ...x.....x..¦...x........; XYZ 0.65/0.7/0.55 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R33 | Staccato-Humor; 4/4; KF  x.x...x.x.x.....¦x...x.x.....x...; XYZ 0.75/0.4/0.6 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-R34 | Magische Triolen-Tupfer; 4/4T; TU  x..x..x.x...¦..x..x......; XYZ 0.75/0.25/0.55 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; Triolenzeit ist 320 Ticks, Einsatzproduktion noch Sechzehntel |
| JW-R35 | Gedämpfter Trauermarsch; 4/4; KF  X.......X.......¦X.......X...x... / ST  X...............¦................; XYZ 0.2/0.35/0.2 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R36 | Unregelmäßiges Klopfen; 4/4; TU  x.....x.....x...¦...x.......x.... / KB  X...............¦........x.......; XYZ 0.2/0.25/0.75 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R37 | Wechselnde Akzentgruppen 3+3+2 ¦ 2+3+3; 4/4; KF  X.x.x.X.x.x.X.x.¦X.x.X.x.x.X.x.x.; XYZ 0.75/0.7/0.7 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-R38 | Puls 2+2+2+2 ¦ 3+2+3; 4/4; KF  X.x.X.x.X.x.X.x.¦X.x.x.X.x.X.x.x. / KB  X.......X.......¦X.....X...X.....; XYZ 0.75/0.75/0.7 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R39 | Staccato-Duett; 4/4; TU  x.x...x.x.......¦....x.x...x.x... / GS  ........x...x.x.¦x.x.............; XYZ 0.75/0.25/0.65 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R40 | Isolierte Einwürfe mit Ausstieg (4 Takte); 4/4; TU  x...............¦........x.......¦................¦....x........... / GS  ........x.......¦................¦x...............¦................; XYZ 0.7/0.15/0.55 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R41 | Synkopierte 6/8-Figur; 6/8; KF  X..x.x..x...¦X..x.x...... / KB  X.....x.....¦X...........; XYZ 0.7/0.4/0.6 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R42 | Oom-pah mit verschobenen Nachschlägen; 4/4; KB  X.......X.......¦X.......X....... / KF  ....x.....x.x...¦....x...x.....x.; XYZ 0.75/0.3/0.6 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R43 | Lang-lang-kurz-kurz-lang; 4/4; KB  X---x---x-x-x---¦X---x---x-x-x---; XYZ 0.2/0.75/0.45 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-R44 | Hemiole 6/8 gegen 3/4; 6/8; KF  X.....x.....¦X.....x..... / KB  X...x...x...¦X...x...x...; XYZ 0.7/0.65/0.65 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R45 | Leise Triolenarpeggien abwärts; 4/4T; AR  Xxxxxxxxxxxx¦Xxxxxxxxxxxx; XYZ 0.35/0.2/0.5 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; Triolenzeit ist 320 Ticks, Einsatzproduktion noch Sechzehntel |
| JW-R46 | Choral in Halben mit sparsamem Akzent; 4/4; KF  X-------X-------¦X-------X------- / ST  X...............¦................; XYZ 0.15/0.75/0.25 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R47 | Hohes Pedal, tiefe Einzeltöne; 4/4; LF  X---------------¦---------------- / TU  ..........x.....¦...x............; XYZ 0.3/0.1/0.55 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |
| JW-R48 | Gemeinsames Akzentgerüst; 4/4; KB  X..x..x.X..x..x.¦X..x..x.X..x..x. / KF  X.....x.X.....x.¦X.....x.X.....x. / ST  X.......X.......¦X...............; XYZ 0.75/0.8/0.7 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen; gemeinsames Mehrrollen-Akzentgerüst erforderlich |

### Bass

| ID | Grundvorlage / konkrete Daten | Status | Technische Zuordnung / Grenze |
|---|---|---|---|
| JW-B01 | Tonikapedal, lang; 4/4; P(C2); XYZ 0.6/0.25/0.15 | E | vorhandener Pedal-/Oktav-/Alternating-Bass unter passender Harmonie; exakte Vorlagenrhythmik und XYZ-Zuordnung bleiben Importarbeit |
| JW-B02 | Dominantpedal mit Neuansatz; 4/4; P(G1); XYZ 0.6/0.55/0.45 | K | explizite Bass-Tonfolge/relative Tonregel und harmonische Freigabe fehlen; Rhythmus ist nicht die Tonplanung |
| JW-B03 | Oktavsprung-Pedal; 4/4; R 8; XYZ 0.7/0.45/0.35 | E | vorhandener Pedal-/Oktav-/Alternating-Bass unter passender Harmonie; exakte Vorlagenrhythmik und XYZ-Zuordnung bleiben Importarbeit |
| JW-B04 | Grundton–Quinte-Marsch; 4/4; R 5; XYZ 0.65/0.5/0.3 | E | vorhandener Pedal-/Oktav-/Alternating-Bass unter passender Harmonie; exakte Vorlagenrhythmik und XYZ-Zuordnung bleiben Importarbeit |
| JW-B05 | Chromatischer Lamentofall; 4/4; b; XYZ 0.25/0.4/0.4 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-B06 | Chromatisch steigender Spannungsbass; 4/4; R n; XYZ 0.4/0.6/0.55 | K | explizite Bass-Tonfolge/relative Tonregel und harmonische Freigabe fehlen; Rhythmus ist nicht die Tonplanung |
| JW-B07 | Oktatonischer Basslauf; 4/4; P(C2) P(Db2) P(Eb2) P(E2) P(F#2) P(G2) P(A2) P(Bb2); XYZ 0.3/0.65/0.75 | K | explizite Bass-Tonfolge/relative Tonregel und harmonische Freigabe fehlen; Rhythmus ist nicht die Tonplanung |
| JW-B08 | Kleinterz-Sprungbass; 4/4; P(C2) P(Eb2) P(F#2) P(A2); XYZ 0.25/0.6/0.7 | K | explizite Bass-Tonfolge/relative Tonregel und harmonische Freigabe fehlen; Rhythmus ist nicht die Tonplanung |
| JW-B09 | Halbton-Dissonanzbass; 4/4; +1; XYZ 0.25/0.8/0.75 | K | explizite Bass-Tonfolge/relative Tonregel und harmonische Freigabe fehlen; Rhythmus ist nicht die Tonplanung |
| JW-B10 | Tritonus-Pendel; 4/4; R P(F#1); XYZ 0.2/0.45/0.6 | K | explizite Bass-Tonfolge/relative Tonregel und harmonische Freigabe fehlen; Rhythmus ist nicht die Tonplanung |
| JW-B11 | Punktiertes Marschmotiv; 4/4; R 5 R R 5 R R 5 R R 5 R 5; XYZ 0.55/0.65/0.45 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-B12 | Synkopierte Basslinie; 4/4; R 8 R 5 R 8 R 5 R 3 5; XYZ 0.35/0.75/0.75 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-B13 | Gegenbewegung zur Oberstimme; 4/4; P(C2) P(Bb1) P(Ab1) P(Gb1); XYZ 0.45/0.55/0.55 | K | explizite Bass-Tonfolge/relative Tonregel und harmonische Freigabe fehlen; Rhythmus ist nicht die Tonplanung |
| JW-B14 | Staccato-Wanderbass; 4/4; R d d 5 R d d 5; XYZ 0.75/0.4/0.55 | K | explizite Bass-Tonfolge/relative Tonregel und harmonische Freigabe fehlen; Rhythmus ist nicht die Tonplanung |
| JW-B15 | Durchgangsbass zwischen Grundtönen; 4/4; R d d; XYZ 0.6/0.35/0.3 | K | explizite Bass-Tonfolge/relative Tonregel und harmonische Freigabe fehlen; Rhythmus ist nicht die Tonplanung |
| JW-B16 | Terzbass (Sextakkordlinie); 4/4; 3; XYZ 0.65/0.3/0.3 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-B17 | Bass nur auf Akzenten; 4/4; R R; XYZ 0.4/0.6/0.5 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-B18 | Ostinato 3+3+2; 4/4; R 5 8 R 5 8; XYZ 0.55/0.65/0.6 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-B19 | Tiefe Achtelrepetition mit Akzentversatz; 4/4; R; XYZ 0.35/0.55/0.6 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-B20 | Registersprung bei Abschnittswechsel; 4/4; R -8; XYZ 0.35/0.6/0.3 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-B21 | Dorische Stufenlinie; 4/4; P(C2) P(D2) P(Eb2) P(F2); XYZ 0.35/0.35/0.3 | K | explizite Bass-Tonfolge/relative Tonregel und harmonische Freigabe fehlen; Rhythmus ist nicht die Tonplanung |
| JW-B22 | Lydisches Nachbarton-Ostinato; 4/4; P(C2) P(D2) P(E2) P(F#2); XYZ 0.85/0.4/0.4 | K | explizite Bass-Tonfolge/relative Tonregel und harmonische Freigabe fehlen; Rhythmus ist nicht die Tonplanung |
| JW-B23 | Hexatonischer Stufenbass; 4/4; P(C2) P(B1) P(Ab1) P(G1); XYZ 0.4/0.4/0.55 | K | explizite Bass-Tonfolge/relative Tonregel und harmonische Freigabe fehlen; Rhythmus ist nicht die Tonplanung |
| JW-B24 | Lang–kurz-Wechsel; 4/4; R; XYZ 0.45/0.5/0.45 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-B25 | Bass als Motor (Sechzehntel); 4/4; R R 8 R; XYZ 0.45/0.85/0.8 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-B26 | Wiederkehrendes Bassmotiv (Vierton); 4/4; R P(Eb2) P(D2) P(G1); XYZ 0.3/0.45/0.45 | K | explizite Bass-Tonfolge/relative Tonregel und harmonische Freigabe fehlen; Rhythmus ist nicht die Tonplanung |
| JW-B27 | Heroischer Quintfall-Bass; 2/2; R 5 R; XYZ 0.8/0.75/0.3 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-B28 | Bewusste Basspause; 4/4; R; XYZ 0.55/0.3/0.4 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-B29 | Lydischer Oktav-Motor; 4/4; R 8 5 R 8 R 5 8 R 5; XYZ 0.8/0.8/0.7 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-B30 | Schwebender Hochbass; 4/4; R 5 8 5 R; XYZ 0.75/0.3/0.6 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-B31 | Oom-pah-Bass, beweglich; 4/4; R 5 +1 5; XYZ 0.75/0.3/0.6 | K | explizite Bass-Tonfolge/relative Tonregel und harmonische Freigabe fehlen; Rhythmus ist nicht die Tonplanung |
| JW-B32 | Bass auf Nicht-Akkordtönen; 4/4; +1 +1 n n; XYZ 0.7/0.75/0.75 | K | explizite Bass-Tonfolge/relative Tonregel und harmonische Freigabe fehlen; Rhythmus ist nicht die Tonplanung |
| JW-B33 | Tiefes oktatonisches Klavier-Ostinato; 4/4; P(C2) P(C2) P(Db2) P(Db2) P(Eb2) P(C2) P(C2) P(Gb1) P(Gb1) P(A1); XYZ 0.25/0.45/0.7 | K | explizite Bass-Tonfolge/relative Tonregel und harmonische Freigabe fehlen; Rhythmus ist nicht die Tonplanung |
| JW-B34 | Lang-lang-kurz-kurz-lang-Bass; 4/4; R 5 8 5 R; XYZ 0.2/0.75/0.45 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-B35 | Dies-irae-Cantus im Bass; 4/4; P(C2) P(B1) P(C2) P(Ab1) P(B1) P(G1) P(Ab1) P(Ab1); XYZ 0.15/0.8/0.25 | K | explizite Bass-Tonfolge/relative Tonregel und harmonische Freigabe fehlen; Rhythmus ist nicht die Tonplanung |
| JW-B36 | Chromatischer Gegenbass zu steigenden Klängen; 4/4; P(C2) P(B1) P(Bb1) P(A1); XYZ 0.65/0.6/0.6 | K | explizite Bass-Tonfolge/relative Tonregel und harmonische Freigabe fehlen; Rhythmus ist nicht die Tonplanung |
| JW-B37 | Tiefer Einwurf unter hohem Pedal; 4/4; P(C1); XYZ 0.3/0.1/0.55 | K | explizite Bass-Tonfolge/relative Tonregel und harmonische Freigabe fehlen; Rhythmus ist nicht die Tonplanung |
| JW-B38 | Synkopierter Quintpendel-Bass (6/8); 6/8; R 5 R R 5; XYZ 0.7/0.4/0.55 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-B39 | Galopp-Bass 6/8; 6/8; R R 5; XYZ 0.8/0.75/0.6 | K | vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen |
| JW-B40 | Kleinterz-Pedalwechsel (leise); 4/4; P(C2) P(Eb2) P(F#2) P(A1); XYZ 0.2/0.2/0.6 | K | explizite Bass-Tonfolge/relative Tonregel und harmonische Freigabe fehlen; Rhythmus ist nicht die Tonplanung |

### Kurze Motive

| ID | Grundvorlage / konkrete Daten | Status | Technische Zuordnung / Grenze |
|---|---|---|---|
| JW-M01 | Quintaufschwung mit Doppelschlag; 7 Noten; XYZ 0.75/0.45/0.35 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M02 | Kampfkontur; 7 Noten; XYZ 0.7/0.7/0.45 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M03 | Zielton mit Obersekund-Vorhalt; 6 Noten; XYZ 0.7/0.55/0.3 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M04 | Quartsignal; 6 Noten; XYZ 0.7/0.75/0.4 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M05 | Repetition und kleine Terz; 6 Noten; XYZ 0.2/0.45/0.5 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M06 | Sechsfache Repetition mit Halbtonfall; 7 Noten; XYZ 0.2/0.4/0.6 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M07 | Verminderte Terz (Gegenspieler); 4 Noten; XYZ 0.15/0.4/0.55 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M08 | Lydischer Doppelnachbar; 4 Noten; XYZ 0.85/0.25/0.3 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M09 | ♭6–5–♯4-Zelle; 4 Noten; XYZ 0.2/0.45/0.55 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M10 | Pentatonischer Hüpfer; 9 Noten; XYZ 0.8/0.45/0.5 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten; überschreitet Acht-Noten-Materialgrenze |
| JW-M11 | Oktatonische Synkope in Unterterzen; 10 Noten; XYZ 0.3/0.65/0.8 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten; überschreitet Acht-Noten-Materialgrenze |
| JW-M12 | Nervöses vermindertes Arpeggio; 13 Noten; XYZ 0.3/0.6/0.8 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten; überschreitet Acht-Noten-Materialgrenze |
| JW-M13 | Chromatische Glockenfigur; 5 Noten; XYZ 0.3/0.35/0.45 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M14 | Zitternder chromatischer Doppelnachbar; 4 Noten; XYZ 0.3/0.25/0.65 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M15 | Seufzerkette; 6 Noten; XYZ 0.25/0.3/0.35 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M16 | Triolensequenz (fallend, steigend gekettet); 11 Noten; XYZ 0.75/0.5/0.45 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten; überschreitet Acht-Noten-Materialgrenze |
| JW-M17 | Heroische Tetrachorde; 8 Noten; XYZ 0.75/0.75/0.4 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M18 | Steigende Quartenkette; 5 Noten; XYZ 0.65/0.7/0.55 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M19 | Synkopierte Militärzelle; 6 Noten; XYZ 0.55/0.7/0.55 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M20 | Romantischer Sextaufschwung; 5 Noten; XYZ 0.6/0.4/0.25 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M21 | Wiegenterzen; 6 Noten; XYZ 0.7/0.2/0.2 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M22 | Staunen: Nonensprung; 5 Noten; XYZ 0.8/0.3/0.4 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M23 | Quarte–Tritonus-Rätsel; 4 Noten; XYZ 0.3/0.25/0.5 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M24 | Tiefe Lauerzelle; 3 Noten; XYZ 0.15/0.2/0.45 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M25 | Chromatischer Stolperer; 7 Noten; XYZ 0.75/0.4/0.6 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M26 | Mechanischer Marschgruß; 6 Noten; XYZ 0.8/0.45/0.45 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M27 | Abenteueraufruf; 7 Noten; XYZ 0.8/0.7/0.4 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M28 | Moll-Klagezelle i–♭6–5; 4 Noten; XYZ 0.2/0.4/0.35 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M29 | Phrygischer Abstieg; 5 Noten; XYZ 0.2/0.55/0.45 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M30 | Hexatonische Linie; 6 Noten; XYZ 0.45/0.35/0.55 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M31 | Ganztonschwebe; 6 Noten; XYZ 0.6/0.2/0.55 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M32 | Oktatonischer Verbindungslauf; 9 Noten; XYZ 0.35/0.75/0.75 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten; überschreitet Acht-Noten-Materialgrenze |
| JW-M33 | Kurze Antwortfigur; 3 Noten; XYZ 0.7/0.3/0.3 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M34 | Schwere Quint-Oktav-Zelle; 6 Noten; XYZ 0.15/0.8/0.25 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M35 | Synkopiertes Quintpendel (6/8); 5 Noten; XYZ 0.7/0.4/0.6 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M36 | Isolierter Quinteinwurf; 2 Noten; XYZ 0.7/0.15/0.5 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten; G–D über C ist nicht vollständig akkordtongebunden |
| JW-M37 | Lydisch-♯2-Hüpfer; 7 Noten; XYZ 0.7/0.3/0.65 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M38 | Wrong-note-Punktierung; 5 Noten; XYZ 0.75/0.35/0.65 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M39 | Hexatonische Abwärtszelle, synkopiert; 5 Noten; XYZ 0.7/0.35/0.6 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M40 | Galoppzelle; 8 Noten; XYZ 0.75/0.7/0.6 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M41 | Sechzehntel-Fanfarenkopf mit Staccato-Achtel; 10 Noten; XYZ 0.85/0.8/0.6 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten; überschreitet Acht-Noten-Materialgrenze |
| JW-M42 | Leiser Kleinterz-Kreisel (oktatonisch); 5 Noten; XYZ 0.2/0.2/0.6 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M43 | Choralabstieg 5→3 mit ♭6-Reibung; 5 Noten; XYZ 0.15/0.65/0.3 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M44 | Dies-irae-Kopf (Typ 1); 4 Noten; XYZ 0.15/0.55/0.35 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M45 | Dies-irae-Umkehrung (Typ 5); 4 Noten; XYZ 0.15/0.7/0.55 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M46 | Spannungszelle 1–3–2–x–1, synkopiert; 5 Noten; XYZ 0.2/0.4/0.6 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M47 | Arpeggio mit Fremdton (♭6); 7 Noten; XYZ 0.3/0.2/0.6 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |
| JW-M48 | Halbton-Mollpaar in hoher Lage; 5 Noten; XYZ 0.15/0.2/0.65 | K | Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten |

### Längere Phrasen

| ID | Grundvorlage / konkrete Daten | Status | Technische Zuordnung / Grenze |
|---|---|---|---|
| JW-P01 | Heroische Kampfphrase (4 Takte); 15 Noten; XYZ 0.8/0.75/0.35 | G | zusammenhängende 4–8/6-Takt-Ziel- und Spannungsplanung fehlt; kein Abschneiden auf acht Noten; überschreitet Acht-Noten-Materialgrenze |
| JW-P02 | Lyrische Frage–Antwort (8 Takte); 19 Noten; XYZ 0.6/0.4/0.25 | G | zusammenhängende 4–8/6-Takt-Ziel- und Spannungsplanung fehlt; kein Abschneiden auf acht Noten; überschreitet Acht-Noten-Materialgrenze |
| JW-P03 | Lydischer Aufbruch (4 Takte); 14 Noten; XYZ 0.9/0.6/0.4 | G | zusammenhängende 4–8/6-Takt-Ziel- und Spannungsplanung fehlt; kein Abschneiden auf acht Noten; überschreitet Acht-Noten-Materialgrenze |
| JW-P04 | Lauernde Gegenstimme (4 Takte); 8 Noten; XYZ 0.15/0.2/0.45 | G | zusammenhängende 4–8/6-Takt-Ziel- und Spannungsplanung fehlt; kein Abschneiden auf acht Noten |
| JW-P05 | Kleinterzsequenz der Bedrohung (4 Takte); 16 Noten; XYZ 0.2/0.55/0.65 | G | zusammenhängende 4–8/6-Takt-Ziel- und Spannungsplanung fehlt; kein Abschneiden auf acht Noten; überschreitet Acht-Noten-Materialgrenze |
| JW-P06 | Oktatonische Actionlinie (4 Takte); 24 Noten; XYZ 0.3/0.75/0.75 | G | zusammenhängende 4–8/6-Takt-Ziel- und Spannungsplanung fehlt; kein Abschneiden auf acht Noten; überschreitet Acht-Noten-Materialgrenze |
| JW-P07 | Staunen über Pedal (8 Takte); 20 Noten; XYZ 0.75/0.4/0.45 | G | zusammenhängende 4–8/6-Takt-Ziel- und Spannungsplanung fehlt; kein Abschneiden auf acht Noten; überschreitet Acht-Noten-Materialgrenze |
| JW-P08 | Trauerphrase (8 Takte); 18 Noten; XYZ 0.25/0.3/0.2 | G | zusammenhängende 4–8/6-Takt-Ziel- und Spannungsplanung fehlt; kein Abschneiden auf acht Noten; überschreitet Acht-Noten-Materialgrenze |
| JW-P09 | Verspielte Staccatophrase (4 Takte); 17 Noten; XYZ 0.75/0.4/0.6 | G | zusammenhängende 4–8/6-Takt-Ziel- und Spannungsplanung fehlt; kein Abschneiden auf acht Noten; überschreitet Acht-Noten-Materialgrenze |
| JW-P10 | Heroischer Mollmarsch (4 Takte); 15 Noten; XYZ 0.3/0.8/0.6 | G | zusammenhängende 4–8/6-Takt-Ziel- und Spannungsplanung fehlt; kein Abschneiden auf acht Noten; überschreitet Acht-Noten-Materialgrenze |
| JW-P11 | Dorische Mystik (8 Takte); 16 Noten; XYZ 0.35/0.3/0.3 | G | zusammenhängende 4–8/6-Takt-Ziel- und Spannungsplanung fehlt; kein Abschneiden auf acht Noten; überschreitet Acht-Noten-Materialgrenze |
| JW-P12 | Romantischer Bogen (8 Takte); 19 Noten; XYZ 0.6/0.4/0.3 | G | zusammenhängende 4–8/6-Takt-Ziel- und Spannungsplanung fehlt; kein Abschneiden auf acht Noten; überschreitet Acht-Noten-Materialgrenze |
| JW-P13 | Kleinterz-Durzyklus (8 Takte); 42 Noten; XYZ 0.55/0.75/0.75 | G | zusammenhängende 4–8/6-Takt-Ziel- und Spannungsplanung fehlt; kein Abschneiden auf acht Noten; überschreitet Acht-Noten-Materialgrenze |
| JW-P14 | Triumphphrase (8 Takte); 19 Noten; XYZ 0.85/0.85/0.35 | G | zusammenhängende 4–8/6-Takt-Ziel- und Spannungsplanung fehlt; kein Abschneiden auf acht Noten; überschreitet Acht-Noten-Materialgrenze |
| JW-P15 | Lydisches Rätsel (4 Takte); 8 Noten; XYZ 0.85/0.25/0.35 | G | zusammenhängende 4–8/6-Takt-Ziel- und Spannungsplanung fehlt; kein Abschneiden auf acht Noten |
| JW-P16 | Hexatonischer Bogen (8 Takte); 18 Noten; XYZ 0.45/0.4/0.55 | G | zusammenhängende 4–8/6-Takt-Ziel- und Spannungsplanung fehlt; kein Abschneiden auf acht Noten; überschreitet Acht-Noten-Materialgrenze |
| JW-P17 | Walzer-Scherzo (8 Takte); 20 Noten; XYZ 0.75/0.45/0.5 | G | zusammenhängende 4–8/6-Takt-Ziel- und Spannungsplanung fehlt; kein Abschneiden auf acht Noten; überschreitet Acht-Noten-Materialgrenze |
| JW-P18 | Archaische Mollhymne (4 Takte); 9 Noten; XYZ 0.2/0.75/0.25 | G | zusammenhängende 4–8/6-Takt-Ziel- und Spannungsplanung fehlt; kein Abschneiden auf acht Noten; überschreitet Acht-Noten-Materialgrenze |
| JW-P19 | Neugieriges Staccato-Planing (4 Takte); 19 Noten; XYZ 0.75/0.25/0.7 | G | zusammenhängende 4–8/6-Takt-Ziel- und Spannungsplanung fehlt; kein Abschneiden auf acht Noten; überschreitet Acht-Noten-Materialgrenze |
| JW-P20 | Lydische Schleifenphrase (8 Takte); 27 Noten; XYZ 0.9/0.8/0.65 | G | zusammenhängende 4–8/6-Takt-Ziel- und Spannungsplanung fehlt; kein Abschneiden auf acht Noten; überschreitet Acht-Noten-Materialgrenze |
| JW-P21 | Archaischer Choral über Dies-irae-Bass (8 Takte); 12 Noten; XYZ 0.15/0.75/0.25 | G | zusammenhängende 4–8/6-Takt-Ziel- und Spannungsplanung fehlt; kein Abschneiden auf acht Noten; überschreitet Acht-Noten-Materialgrenze |
| JW-P22 | Spannungsphrase mit Atempausen (4 Takte); 12 Noten; XYZ 0.3/0.2/0.65 | G | zusammenhängende 4–8/6-Takt-Ziel- und Spannungsplanung fehlt; kein Abschneiden auf acht Noten; überschreitet Acht-Noten-Materialgrenze |
| JW-P23 | Frage hoch – Antwort tief (8 Takte); 24 Noten; XYZ 0.75/0.35/0.55 | G | zusammenhängende 4–8/6-Takt-Ziel- und Spannungsplanung fehlt; kein Abschneiden auf acht Noten; überschreitet Acht-Noten-Materialgrenze |
| JW-P24 | Asymmetrische 6-Takt-Phrase (3 + 3); 11 Noten; XYZ 0.15/0.7/0.35 | G | zusammenhängende 4–8/6-Takt-Ziel- und Spannungsplanung fehlt; kein Abschneiden auf acht Noten; überschreitet Acht-Noten-Materialgrenze |

### Modellstudien

| ID | Grundvorlage / konkrete Daten | Status | Technische Zuordnung / Grenze |
|---|---|---|---|
| JW-S01 | Lauern im Dunkeln; 4/4; 40 Noten; JW-B01, JW-H41, JW-P04, JW-R26, JW-S01, JW-T01; XYZ 0.15/0.2/0.45 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden |
| JW-S02 | Marschierende Bedrohung; 4/4; 220 Noten; JW-B11, JW-H13, JW-H22, JW-M28, JW-R01, JW-S02, JW-T02; XYZ 0.15/0.8/0.35 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden; ST zweistimmig/tonal, kein fester Trigger; zu lange Kurznoten KF=12, KB=0 |
| JW-S03 | Geheimnis; 4/4; 74 Noten; JW-H40, JW-M23, JW-R11, JW-R14, JW-R34, JW-S03, JW-T03; XYZ 0.3/0.25/0.4 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden |
| JW-S04 | Psychologisches Unbehagen; 4/4; 80 Noten; JW-B09, JW-H14, JW-H46, JW-M14, JW-R20, JW-S04, JW-T07; XYZ 0.2/0.25/0.75 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden |
| JW-S05 | Trauer; 4/4; 64 Noten; JW-B05, JW-H34, JW-H35, JW-P08, JW-S05, JW-T05; XYZ 0.25/0.25/0.15 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden |
| JW-S06 | Wärme und Geborgenheit; 4/4; 102 Noten; JW-H36, JW-M33, JW-R14, JW-S06, JW-T05; XYZ 0.75/0.2/0.1 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden |
| JW-S07 | Romantik; 6/8; 97 Noten; JW-H38, JW-P12, JW-R16, JW-S07, JW-T06; XYZ 0.6/0.4/0.25 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden; zu lange Kurznoten KF=0, KB=12 |
| JW-S08 | Staunen und Entdeckung; 4/4; 117 Noten; JW-B28, JW-H50, JW-P07, JW-R15, JW-S08, JW-T04; XYZ 0.8/0.35/0.5 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden |
| JW-S09 | Magie und Fremdartigkeit; 4/4; 120 Noten; JW-H24, JW-H25, JW-M30, JW-R20, JW-S08, JW-S09; XYZ 0.7/0.25/0.7 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden |
| JW-S10 | Verspieltheit; 4/4; 207 Noten; JW-B14, JW-H51, JW-H52, JW-P09, JW-R33, JW-S10; XYZ 0.75/0.4/0.6 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden; ST zweistimmig/tonal, kein fester Trigger |
| JW-S11 | Helle Verfolgungsjagd; 4/4; 278 Noten; JW-B18, JW-H04, JW-P03, JW-R04, JW-R09, JW-S11, JW-S14, JW-T08; XYZ 0.8/0.75/0.7 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden |
| JW-S12 | Dramatische Spannung; 4/4; 300 Noten; JW-B07, JW-H19, JW-P06, JW-R08, JW-R29, JW-S12, JW-S13, JW-T07; XYZ 0.35/0.6/0.65 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden; ST zweistimmig/tonal, kein fester Trigger |
| JW-S13 | Dunkle Action; 4/4; 292 Noten; JW-B25, JW-H17, JW-M11, JW-R04, JW-S13, JW-S16, JW-T08; XYZ 0.3/0.85/0.8 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden; ST zweistimmig/tonal, kein fester Trigger |
| JW-S14 | Triumph; 4/4; 167 Noten; JW-H33, JW-H49, JW-P14, JW-R31, JW-S14; XYZ 0.85/0.85/0.3 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden; ST zweistimmig/tonal, kein fester Trigger |
| JW-S15 | Epische Weite; 4/4; 70 Noten; JW-B20, JW-H33, JW-H55, JW-R14, JW-S15; XYZ 0.7/0.55/0.2 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden |
| JW-S16 | Zuspitzung (Unruhe > 0,9); 4/4; 478 Noten; JW-H19, JW-H48, JW-M32, JW-R07, JW-R08, JW-R09, JW-S13, JW-S16, JW-T08; XYZ 0.3/0.95/0.98 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden; ST zweistimmig/tonal, kein fester Trigger |
| JW-S17 | Neugierige Werkstatt; 4/4; 155 Noten; JW-B31, JW-H58, JW-P19, JW-R39, JW-R42, JW-S10, JW-S17, JW-S25; XYZ 0.75/0.25/0.7 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden |
| JW-S18 | Lydisch-♯2-Rätsel; 4/4; 61 Noten; JW-H58, JW-H59, JW-M37, JW-M38, JW-R40, JW-S17, JW-S18; XYZ 0.7/0.3/0.65 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden |
| JW-S19 | Lydische Schleife mit wechselnden Akzenten; 4/4; 371 Noten; JW-B32, JW-H62, JW-P20, JW-R37, JW-S14, JW-S19, JW-S20; XYZ 0.9/0.8/0.65 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden; ST zweistimmig/tonal, kein fester Trigger |
| JW-S20 | Planing-Jagd mit Großterzrückung; 4/4; 288 Noten; JW-H64, JW-R09, JW-R48, JW-S14, JW-S20; XYZ 0.85/0.85/0.6 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden; ST zweistimmig/tonal, kein fester Trigger |
| JW-S21 | Dies-irae-Choral; 4/4; 88 Noten; JW-B35, JW-H69, JW-P21, JW-R43, JW-S21, JW-S26; XYZ 0.15/0.8/0.25 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden; ST zweistimmig/tonal, kein fester Trigger; zu lange Kurznoten KF=27, KB=0 |
| JW-S22 | Tritonus-Oszillation in Triolen; 4/4T; 170 Noten; JW-H67, JW-H76, JW-P24, JW-R45, JW-R46, JW-S22; XYZ 0.15/0.75/0.35 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden; ST zweistimmig/tonal, kein fester Trigger; zu lange Kurznoten KF=24, KB=0 |
| JW-S23 | Leise Oktatonik; 4/4; 58 Noten; JW-B40, JW-H74, JW-M42, JW-R47, JW-S04, JW-S23, JW-S28; XYZ 0.2/0.2/0.6 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden |
| JW-S24 | Rätselhafte Arpeggien; 4/4; 58 Noten; JW-H72, JW-M47, JW-P22, JW-S03, JW-S23, JW-S24; XYZ 0.3/0.2/0.65 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden |
| JW-S25 | 32 Takte gleiche Stimmung: Planing-Scherzo; 4/4; 368 Noten; JW-H58, JW-H60, JW-P23, JW-R39, JW-R42, JW-S25; XYZ 0.75/0.35/0.55 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden |
| JW-S26 | 16 Takte dunkle Größe; 4/4; 165 Noten; JW-B35, JW-H69, JW-M45, JW-P21, JW-R43, JW-S22, JW-S26, JW-T02; XYZ 0.15/0.8/0.25 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden; ST zweistimmig/tonal, kein fester Trigger; zu lange Kurznoten KF=57, KB=0 |
| JW-S27 | 16 Takte heller Abenteuerbogen; 4/4; 551 Noten; JW-H66, JW-R09, JW-R37, JW-R38, JW-S20, JW-S27; XYZ 0.7/0.7/0.65 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden; ST zweistimmig/tonal, kein fester Trigger |
| JW-S28 | 32 Takte Lauern: Bewegung und Stille; 4/4; 262 Noten; JW-B33, JW-H71, JW-M48, JW-R47, JW-S28, JW-T01; XYZ 0.15/0.25/0.65 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden |
| JW-S29 | Intensität ohne Unruhe (16 Takte); 4/4; 183 Noten; JW-H12, JW-M05, JW-R46, JW-S29, JW-S30; XYZ 0.15/0.25/0.55 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden; ST zweistimmig/tonal, kein fester Trigger; zu lange Kurznoten KF=48, KB=0 |
| JW-S30 | Unruhe ohne Intensität (16 Takte); 4/4; 620 Noten; JW-B32, JW-H01, JW-R20, JW-R37, JW-S11, JW-S19, JW-S30; XYZ 0.75/0.5/0.25 | G | koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden |

### Übergangsstudien

| ID | Grundvorlage / konkrete Daten | Status | Technische Zuordnung / Grenze |
|---|---|---|---|
| JW-T01 | Lauern → Angst; 4/4; 144 Noten; JW-M05, JW-S01, JW-S02, JW-T01; XYZ 0.15/0.2/0.45 | G | expliziter System-/Rollenübergang nicht durch vorhandene Übergangsstimmführung allein garantiert; zu lange Kurznoten KF=6, KB=0 |
| JW-T02 | Angst → Action; 4/4; 262 Noten; JW-S02, JW-S13, JW-T02; XYZ 0.15/0.8/0.35 | G | expliziter System-/Rollenübergang nicht durch vorhandene Übergangsstimmführung allein garantiert; ST zweistimmig/tonal, kein fester Trigger; zu lange Kurznoten KF=6, KB=0 |
| JW-T03 | Geheimnis → Staunen; 4/4; 108 Noten; JW-S03, JW-S08, JW-T03; XYZ 0.3/0.25/0.4 | G | expliziter System-/Rollenübergang nicht durch vorhandene Übergangsstimmführung allein garantiert |
| JW-T04 | Staunen → Triumph; 4/4; 185 Noten; JW-M01, JW-S08, JW-S14, JW-T04; XYZ 0.8/0.35/0.5 | G | expliziter System-/Rollenübergang nicht durch vorhandene Übergangsstimmführung allein garantiert; ST zweistimmig/tonal, kein fester Trigger |
| JW-T05 | Wärme → Melancholie; 4/4; 85 Noten; JW-S05, JW-S06, JW-T05; XYZ 0.75/0.2/0.1 | G | expliziter System-/Rollenübergang nicht durch vorhandene Übergangsstimmführung allein garantiert |
| JW-T06 | Romantik → Bedrohung; 4/4; 85 Noten; JW-H14, JW-M20, JW-S07, JW-T06; XYZ 0.6/0.4/0.25 | G | expliziter System-/Rollenübergang nicht durch vorhandene Übergangsstimmführung allein garantiert; zu lange Kurznoten KF=0, KB=8 |
| JW-T07 | Ruhige Spannung → hochgradige Unruhe; 4/4; 342 Noten; JW-H18, JW-S16, JW-T07; XYZ 0.25/0.45/0.5 | G | expliziter System-/Rollenübergang nicht durch vorhandene Übergangsstimmführung allein garantiert; ST zweistimmig/tonal, kein fester Trigger |
| JW-T08 | Action → ruhige Entspannung; 4/4; 192 Noten; JW-H05, JW-M02, JW-S11, JW-T08; XYZ 0.55/0.8/0.75 | G | expliziter System-/Rollenübergang nicht durch vorhandene Übergangsstimmführung allein garantiert; zu lange Kurznoten KF=3, KB=0 |
| JW-T09 | Cluster → Dur (atonal → tonal); 4/4; 78 Noten; JW-S08, JW-S24, JW-T09; XYZ 0.4/0.4/0.7 | G | expliziter System-/Rollenübergang nicht durch vorhandene Übergangsstimmführung allein garantiert |
| JW-T10 | Tonal → leise Oktatonik; 4/4; 77 Noten; JW-H34, JW-S23, JW-T10; XYZ 0.25/0.25/0.2 | G | expliziter System-/Rollenübergang nicht durch vorhandene Übergangsstimmführung allein garantiert |

## 10. Reproduktion und Abgrenzung der Prüfung

`python docs/research/john-williams/audit.py` rekonstruiert das JSON-Inventar und prüft Forschungsdaten.
`python docs/research/john-williams/coverage.py` kompiliert die Offline-Abfrage mit einem C++17-Compiler und schreibt die XYZ-Simulation.
`python docs/research/john-williams/write_inventory.py` aktualisiert ausschließlich den markierten Tabellenteil dieses Berichts.

Keine zusätzliche Engine-Regression erforderlich: `Source/`, Laufzeitdaten, GUI, Build- und Testkonfiguration wurden nicht verändert. Geprüft wurden die neuen Dokumentationsartefakte und Forschungsdaten, nicht eine noch nicht existierende Williams-Implementierung. Die vollständige letzte Engine-/Plugin-Prüfung bleibt die zu `8d4086c` dokumentierte.

## Fortschreibung: unabhängiges Einzelpedal

Der erste begrenzte gemeinsame Pedalpfad ist mit JW-H03/H50/H61 verbunden. Modell, Autorisierungsgrenzen, tatsächliche MIDI-Vergleiche und noch offene Bass-/Pedalfähigkeiten stehen in [INDEPENDENT_PEDALS.md](INDEPENDENT_PEDALS.md). Dies ersetzt keine vollständige Implementierung des übrigen Bassvokabulars oder der Modellstudien. Williams P2/P3 wurde separat am Windows-Stand 023b0a6 musikalisch positiv gehört.
