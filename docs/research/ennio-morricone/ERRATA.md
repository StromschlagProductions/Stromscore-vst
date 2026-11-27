# Fehler, Klärungen und Grenzen der Morricone-Quellen

Ausgang `4c43bd2`. **Keine Originaldatei wurde korrigiert.** Befunde betreffen die
Vorlagen/Referenzstudien, nicht einen bereits laufenden Morricone-Produktionspfad:
dieser existiert nicht. Klangbezeichnungen, musikalische Absicht und konkrete
Noten werden getrennt geprüft. Eine technisch gültige MIDI-Datei bestätigt nicht
automatisch Titel, Identität oder musikalische Qualität.

## Angefragte harmonische Unstimmigkeiten

| ID | Tatsächliche Daten | Entscheidung vor Import |
|---|---|---|
| EM-H018 | Bass `-12,-13,-15,-13,-19,-20,-22,-12`; Bewegungen `-1,-2,+2,-6,-1,-2,+10`. | Stufenweise Abschnitte vorhanden, aber auch Tritonus und kleine Septime. Klären, ob Titel nur Füllschritte oder eine durchgehend schrittweise Linie meint. Nicht automatisch glätten. |
| EM-H025 | Schlussoberstimmen `[-8,0,9,19]`, Bass `-15`: PC `{0,4,7,9}`. | Tatsächlich Dur-Sexte mit Sextbass, keine None. `6/9` ist offenbar als `6` mit Slash-Bass `9` verarbeitet. Autor muss zwischen echter 6/9-Farbe und Umbenennung entscheiden. |
| EM-H026 | Derselbe Sextklang über acht Takte; Tonklasse `2` fehlt. | Kein Dur-6/9-Klang. Bestehender Typ `Major6` beschreibt die Daten, erfüllt aber nicht den angekündigten 6/9-Titel. |
| EM-H046 | `0:add9 → 8:maj → 0:add9 → 5:min`. | Kein gleichwurzeliger Dur-Moll-Doppelklang. Titel oder Progression klären; weder Zusammenlegen noch Hinzufügen einer Mollterz. |
| EM-H052 | Oberste Töne sämtlich `12`; über alle Klänge liegen `0` und `12`. | Gehaltener Grundton, nicht Quinte. Ein Umbenennen wäre eine Quellenentscheidung, keine technische Korrektur im Kern. |
| EM-H053 | Höchste Töne `15,15,15,14`; gemeinsam bleibt `12`. | Ein innerer Gemeinsamton bleibt, die höchste Stimme sinkt am Schluss. „Feste Oberstimme“ präzisieren oder Material berichtigen lassen. |
| EM-H058 | Tonikaoberstimmen `[-3,0,7,15]`, Bass `-15`: `{0,3,7,9}`. | Min6/Sextbass, keine Tonika-None `2`. Der folgende F9-Klang hat hingegen seine eigene None `7`. Nicht pauschal behaupten, überall fehlten Nonen. |
| EM-H063 | Alle vier Qualitäten sind Dur-add9. | Die Moll-add9-Antwort des Titels fehlt. Keine eigenmächtige Terzerniedrigung. |
| EM-H074 | Beide Zustände besitzen identische Oberstimmen `[-3,0,4,6,7,15]` und PC `{0,3,4,6,7,9}`. | Weder `2` noch `11` wird ausgetauscht; „Kern+2/Kern+11“ ist nicht realisiert. Kern, Austauschton und gewünschte Stimmenzahl festlegen lassen. |

Diese neun H-Vorlagen sind im vollständigen Inventar **K**, nicht importfähig
freigegeben. Auch eine intern konsistente Akkordtypenprüfung kann einen falschen
Titel bzw. die fehlende kompositorische Wirkung übersehen.

## Weitere Quellenklärungen

- **EM-R013/R035/R036/R037:** Bei vollständiger Wiederholung aller Schichten
  stimmen Dichte/VK nicht. R013:16/Takt und VK0 statt8/1,94;
  R035:8/Takt und0,408 statt1,33/0; R036:6,4/Takt und0,447 statt0,8/0;
  R037:2/Takt und0,5 statt0,14/0. Gezählt werden eindeutige Einsatzzeitpunkte
  über das vollständige kgV (gleichzeitige Schichten nicht doppelt). Die Schichten
  selbst sind eindeutig notiert; Metadaten und davon abgeleiteter Unruhe-Typ
  müssen geklärt werden. Keine rhythmische Änderung am Original. K.
- **EM-R040:** „Zweiunddreißigstel-Zittern“ enthält 16 Anschläge im Abstand von
  240 Ticks: Sechzehntel. Nicht Tempo verdoppeln oder heimlich Zwischenanschläge
  ergänzen. K bis Titel/Raster entschieden sind.
- **EM-K009:** Modul nennt Quint-Drone und Polyphonie 2; Quelle EM-B003 notiert
  zwei *aufeinanderfolgende* Töne mit je 15360 Ticks und Gesamtzyklus 30720.
  „Polyphonie 2“ könnte ein Höchstwert oder ein gleichzeitig gewünschter Klang
  sein. Diese Bedeutung und die Periodenbindung müssen vor Umsetzung klar sein.
  Keine der beiden Quintkomponenten entfernen oder ungefragt übereinanderlegen.
- **EM-C035:** Unter der im Audit verwendeten packed-right/Forte-Konvention ergibt
  sich `[0,1,2,5,6,7,9]`; angegeben ist `[0,1,2,4,7,8,9]`. Letztere ist durch
  Inversion plus Transposition `T1` aus der ursprünglichen Menge erreichbar.
  **Keine falsche Tonmenge:** dies ist die bekannte Normalform-Konventionsfrage
  bei dieser Klasse. Alle 46 angegebenen Intervallvektoren stimmen. Vor Verwendung
  von Primformstrings als Identität eine einheitliche, benannte Konvention wählen.
- **EM-C025/C026:** sechs feste Kerntöne plus *ein* Austauschton ergeben sieben
  Töne. Die gedruckte Primform/der IV beziehen sich auf den Kern. Ein über eine
  ganze Studie größerer beobachteter Vorrat ist hier kein Identitätsfehler.
  `SOURCE_RECORDS.json` enthält die beiden vollständigen Varianten samt Primform/IV.

## Basszyklen: Materialperiode und Hostphasengleichheit getrennt halten

- **EM-B010/B011:** 5Tonhöhen und4Anschläge je1200Ticks. Dieselbe Pitch-/Rhythmus-
  Phase kehrt nach20Anschlägen/6000Ticks wieder. Zusammen mit4/4 ergibt das
  96000Ticks (25Takte), dann aber **320** Anschläge. „20Ereignisse/96000Ticks“
  vermischt die Zyklen. K; Material und autonome Phasen nicht verändern.
- **EM-B033:** 4Tonhöhen und9Anschläge je5280Ticks ergeben36Anschläge/21120Ticks.
  Hostphasengleichheit nach42240Ticks enthält72, nicht36Anschläge. K.
- **EM-B022/B047:** „Ereignisse“ umfasst hier auch notierte Pausen. B022 hat zwei
  Zeitelemente, aber einen klingenden Anschlag; B047 vier Elemente, aber zwei
  Anschläge. Das ist kein Notenbilanzfehler. Die abgeleiteten Daten trennen beide
  Bedeutungen ausdrücklich.

## Nachgewiesener Identitätsverlust durch Akkordtonanpassung

Die Original-Qualitätsprüfung nennt die Anpassung an den nächsten Akkordton als
Mittel gegen undeklarierte Fremdtöne. Die Implementierung dieser Referenzroutine
wurde nicht mitgeliefert; wir führen keinen angehängten Programmcode aus. Ihr
musikalisches Ergebnis ist aber anhand der CSV und identischen MIDI-Noten prüfbar:

**EM-S016, AR, EM-C010:** ursprüngliche Menge `{0,2,3,7}`. In den ersten vier
Ereignissen unter B♭-add9 ab Tick 7680 erklingt relativ `22,12,12,17`, also
`{10,0,5}` statt vier Tonklassen. Unter A♭-add9 ab Tick 15360 erklingt
`20,22,12,15`, also `{8,10,0,3}`; eine reine T8-Transposition wäre
`{8,10,11,3}`. Anzahl bzw. Intervallstruktur ändern sich. Unter G-m7 folgt eine
weitere Dreiklassen-Kollabierung.

**EM-S044, AR, EM-C010:** unter `5:m6` erklingt relativ `17,20,20,12` statt einer
vierklassigen Transposition: erneut Zusammenfall zweier Zelltöne. Die Definition
der Zelle bleibt sinnvoll, aber diese Realisierungen sind keine unveränderten
Wiederholungen derselben MENGE. S016/S044 sind deshalb **K**. Mögliche spätere
Entscheidungen: andere kompatible Harmonie, ausdrücklicher lokaler Tonkontext,
zulässige ganze Transposition oder benannte neue Variante; keine stumme Reparatur.

[Zellaudit](CELL_IDENTITY_AUDIT.json) unterscheidet Ganzstudien-Aggregate, einzelne
harmonische Kontexte und zulässige KERN-Austauschtöne. Ein Aggregat allein wäre
kein ausreichender Beweis: Transpositionen, unvollständige Figuren und ausdrücklich
erlaubte Farbtöne müssen zuerst berücksichtigt werden. Die gedruckten M-Grundformen
wurden zusätzlich gegen ihre deklarierten Zellen geprüft; das ersetzt keine
Prüfung ihrer veränderten Studienrealisierungen.

## Grenzen der unabhängigen Wiederprüfung

- Alle 73 exportierten Studien/9752 Noten stimmen mit der CSV überein; ZIP, 960 PPQ,
  Notenbilanz und physische Gleichtonhygiene auch über Spuren hinweg sind korrekt.
  Alle 280 ST-Noten sind 36. Dies bestätigt **Dateikonsistenz**, keine Hörqualität.
- In den gelieferten CSV/MIDI-Studien werden **17 der 50 U-IDs** tatsächlich
  referenziert. Die Angabe „50/50 im MIDI geprüft“ kann sich auf zusätzliche interne
  Tests des Erstellers beziehen; sie ist mit den gelieferten Dateien nicht für
  alle 50 wiederholbar. Alle 50 Definitionen wurden hier strukturell bewertet.
- U014 beschreibt eine zusätzliche Vorhaltsphase nach Eintritt des Zielakkords:
  Auflösung erst `3840+1920`. Die Tabelle allein ist nicht die vollständige
  klingende Zeitleiste. Zwei V-Noten in EM-S034 enden am korrekten Zielereignis.
  U036 verlangt entsprechend `3840+2880`; sie ist in den exportierten Studien
  nicht separat nachgewiesen. Ziel-Tonhöhe und Zielzeit aus dem relativen Material
  übernehmen; absolute Tonbeispiele ohne explizite Tonika nicht als globale Noten
  lesen.
- Bei U048 steigt die Stimmenzahl 4→6. Ein `zip` der sortierten Tonlisten ist keine
  verlässliche Stimmenidentität. Der Audit zeigt mögliche monotone Teilzuordnungen
  einschließlich neuer/entfallender Stimmen; er bestätigt damit nicht den nicht
  mitgelieferten Solver und garantiert keine neue Engine-Fähigkeit.
- R-Mehrschichten besitzen verschiedene Perioden: z. B. R035 `720/960`, R036
  `1200/960`, R037 `3360/3840`. Nur das letzte gedruckte Periodenfeld zu lesen wäre
  falsch. Beide Schichten und ihr gemeinsamer Zyklus werden gespeichert.
- Bei dünnen Rhythmusmustern ist die Beschreibung „bis zum nächsten Einsatz“ keine
  hinreichende Gate-Spezifikation für alle Rollen: kurze TU-Trigger in den Studien
  sind z. B. 216 Ticks lang. Eine vollständig lange IOI-Hülle wird in unserer
  formalen Paarprüfung ausdrücklich als konservative Hülle geprüft. Ein negatives
  Ergebnis bedeutet deshalb **Gate-/Kontextentscheidung nötig**, nicht zwangsläufig
  musikalisch unmöglich. Originale werden nicht auf bestehende Gate-Grenzen gekürzt.

## Instrumente und Routing

Die Studie verwendet andere Annahmen als `Generator::outputCatalog()`. **50 von 73
Studien** haben mindestens einen Konflikt mit dessen heutigen Standardgrenzen,
73 Rollen-/Studienbefunde insgesamt. Beispiele: KB tatsächlich zweistimmig, KF bis
15360 Ticks gegenüber Standardmaximum 720, TU bis 3648 gegenüber 720; ST 120
gegenüber Standardminimum 240. Das sind keine universellen MIDI-Grenzen und keine
erkannten Fähigkeiten eines externen Patches. Details: [INSTRUMENT_CONSTRAINTS.json](INSTRUMENT_CONSTRAINTS.json).

Referenzkanäle LF1/KF2/LB3/KB4/AR5/TU6/**GS7/HM8/ST10**. Bestehende
STROMSCORE-Standardziele bleiben LF1/KF2/LB3/KB4/AR5/TU6/**ST7/GS8/HM9**.
Die Rolle, nicht die Zahl des Referenzkanals, ist die Zuordnungsgrundlage eines
späteren Imports. Kein zehnter Ausgang; ST bleibt nicht transponierter Trigger36.

Fehlende Akkordqualitäten werden nicht durch ähnlich benannte ersetzt. Insbesondere
ist `add#11` ohne Septime nicht `Major7Sharp11`, und Moll7add11 nicht Min9. Rootlose
Klangobjekte benötigen ihre eigene harmonische Bedeutung; PC-Gleichheit mit einem
funktionalen Akkord ist allein kein Identitätsbeweis.

## Abhängige Klärfälle

Neben20 direkten K-Befunden hängen P007, K004, K013, K021, S015, S018, S023, S025,
S039 und S052 zwingend von ungeklärten Quellen ab. Sie werden ebenfalls als K geführt,
mit weiter dokumentierten Fähigkeitslücken. **S052s „kein Lolita-Zitat“ bleibt
unverändert**; die Quellenklärung verhindert keine frühe Umsetzung eindeutiger
lyrischer Übergänge U001/U002. Es werden keine neuen Klärfälle allein aus
optionalen „geeignet“-Verweisen erzeugt.
