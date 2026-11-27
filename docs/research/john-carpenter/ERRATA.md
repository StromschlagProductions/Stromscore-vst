# JC – Fehlerliste und offene Zuordnungen

27.11.2026 · Analyse gegen `4937722` / unveränderte Engine `023b0a6`.
Originale bleiben bytegleich. Vorschläge unten sind keine stillen Datenkorrekturen
und keine Implementierungsfreigabe. Die vier kanonischen Dateien haben Vorrang
als Quellen, Anwenderentscheidungen aber Vorrang vor darin enthaltenen Rezepten.

## Eindeutig dokumentierbare Befunde

| Stelle | Tatsächliche Daten | Konsequenz / separat vorgeschlagene Präzisierung |
|---|---|---|
| JC-R046 | 480 Ticks nach Taktbeginn in 4/4 = Eins-und. | „Zwei-und“ im Charaktertext korrigieren; diese wäre1440 Ticks. Muster `.x......` und Tick480 stimmen miteinander überein. Keine Verschiebung der Noten als vermeintliche Fehlerkorrektur. |
| JC-R022 | Tick2880 = Zählzeit4; letzter Achtelbeginn wäre3360. | Text „letzte Achtel“ passt nicht. Datenautorität von Muster und Einsatzticks beibehalten; ggf. explizit „Zählzeit4 mit verlängertem Gate“ benennen. |
| JC-R038 | Acht Anschläge; nur die zwei Gatewerte96/432 dokumentiert, kein expliziter Index. | Lang–kurz-Startphase festlegen. Wenn der erste Ton lang sein soll:432,96,432,96,432,96,432,96. Das ist ein Vorschlag, nicht die aus der Datei bewiesene Zuordnung. |
| JC-R039/R040 | Beide32 Anschläge, gleiche verkürzte Liste72/168/288/432. | Taktspezifisch festlegen: für wachsend z.B. je acht Anschläge mit 72, dann 168,288,432; für schrumpfend die umgekehrte Reihenfolge. Nicht beide aus der identischen sortierten Liste abwechselnd abspielen. JC-B049 erbt die R038-Klärung. |
| JC-H067 | Fünf gedruckte Stimmen0,3,7,10,17; Fähigkeitszeile nur „≥4“. | Mindestanforderung≥5 präzisieren. „≥4“ ist nicht mathematisch falsch, reicht aber als Eignungstest nicht. LF-Standard6 Stimmen genügt; neuer Ausgang unnötig. Exaktes Klang-/A/T-Modell separat prüfen. |
| JC-H025/H085 | Perioden10 bzw.6 Takte. | Gerade, aber keine Zweierpotenzen. Fähigkeitsbezeichnung „ungerade Harmonieperiode“ präzisieren. Diese Fälle benötigen kein gebrochenes Taktmodell; sie benötigen ihre eigene harmonische Zykluslänge. |
| JC-S35 | KB1–32, AR1–16/33–64, GS17–32/49–64. | T33–48 nurAR aus dem Pool, widerspricht „immerzwei“. Keine neue KB-Phase erfinden. Autor muss entscheiden: Beschreibung ändern oder tatsächlichen zweiten Partner festlegen. |
| JC-S35 / JC-T007 | 16-Takt-Blöcke haben 256,192,128,192 Anschläge im PoolKB/AR/GS. | Gleiche Zahl aktiver Rollen ist nicht automatisch gleiche Anschlags-/Klangdichte. Gemeinte Dichte bzw. musikalischen Gewichtsausgleich benennen, keine starre globale Quote einführen. |
| JC-S04/S33 SMF | Ende jeweils3048 Ticks vor der beschriebenen16/32-Takt-Grenze. | LetzteStille ist nicht als vollständiges Clip-Ende gespeichert. Beim A/B-Hören Clip auf formale Länge ziehen; später ggf. End-of-Track passend setzen. CSV/MIDI-Noten sind trotzdem identisch und korrekt geschlossen. |
| JC-S29 „Merkmale“ | Text nennt Gegenstimme; Spuren sindLF/KB/AR/HM. | Metadaten präzisieren: Hauptmelodie statt GS. Noten nicht verändern, um das Etikett zu erfüllen. |
| JC-EF06 | KB JC-B014 ist ein wiederholter Herzschlag. | „Ereignisfeld“ bedeutet hier nicht automatisch „pulslos“. Die Qualitätszahl23pulsloseStudien nicht allein aus EF-Zugehörigkeit als akustischen Nachweis übernehmen. |

R021/R022/R066 benötigen **keine** zusätzliche Gate-Klärung: Anders als die
expliziten Gate-Listen R038–040 lassen sich ihre Werte pro Anschlag aus dem Muster,
Unterstrich-Halten und dem einheitlichen Gatefaktor eindeutig zuordnen. Diese
Zuordnung ist im Inventar als `events` enthalten; eine bloße Liste verschiedener
Dauern wäre unzureichend.

## Vollständige Tonhöhen-/Rhythmuszyklen

Für N Quelltöne, A Anschläge je Rhythmusperiode P gilt bei fortlaufendem Tonindex:

`Rhythmuswiederholungen = N/gcd(N,A)`;
`Gesamtzyklus = P·N/gcd(N,A)`.

Tonindex `globalerAnschlagsordinal % N`, Rhythmusposition separat. Gate-/Akzentphase
gehört ebenfalls dazu; bei R038–040 erst nach Klärung vollständig definiert.
Dauerwerte sind keine Tonhöhenindizes. Kein Zurücksetzen pro Takt.

| Quelle | N / A | P inTicks | vollständiger Zyklus | Bedeutung |
|---|---:|---:|---:|---|
|JC-Q028|24 /12|3840|7680 =2 Takte|ganze24 Töne, keine Halbierung auf erstenTriolentakt|
|JC-Q054|4 /2|3840|7680 =2 Takte|vierHalbe, nicht zweiTöne wiederholen|
|JC-Q055|4 /1|3840|15360 =4 Takte|Abstieg über vierTakte|
|JC-Q063|32 /16|3840|7680 =2 Takte|zweiteHälfte muss tatsächlich erklingen|
|JC-B029/B030/B032|4 /1|3840|15360 =4 Takte|jede Basstonstufe einTakt|
|JC-B031/B052|16 /8|3840|7680 =2 Takte|zweiteAchtel-Tonfolge erhalten|
|JC-B033|8 /2|3840|15360 =4 Takte|ganzeAbwärts-/Rückkehrfigur|
|JC-B034/B035|4 /1|3840|15360 =4 Takte|keine Rücksetzung je Ganznote|
|JC-Q043|5 /16|3840|19200 =5 Takte,80 Anschläge|echtes Fortlaufen gegen Taktgrenze|
|JC-Q044|3 /8|3840|11520 =3 Takte,24 Anschläge|Dreier-Tonfolge gegen Achtel|

Die ersten zwölf angefragten Fälle sind kommensurable Mehrtaktfolgen; sie sind
nicht allein deshalb ein Beleg für Carpenter-Phasenmusik. Alle67 Q- und52 B-Quellen
sind im [Zyklusbericht](CYCLE_ANALYSIS.json) enthalten, einschließlich neun
gehaltener/reartikuliert gehaltener bzw. bewusst stummer Bassquellen. Alle67R
besitzen zusätzlich eine eigene Perioden-/Hosttakt-Ausrichtungsanalyse. Für R062
(720 Ticks) und R063(1200 Ticks) treffen Phase und4/4-Takt erst nach 3bzw.5 Takten
wieder gemeinsam auf ihren Anfang.

## Tonfunktionen und Kontext

Alle237 V-Noten der Studien erreichen den nächsten Ton derselben Rolle im Halb-
oder Ganztonschritt als A-Ton der dort geltenden Harmonie. Alle332 F/U-Noten haben
eine nachvollziehbare Quellenfreigabe (Klangton, Quellannotation, Dissonanzpedal
oder explizites U-Einzelereignis). Das beweist keine subjektive Klangqualität.
Ziele und Zeitpunkte stehen einzeln in `VALIDATION_RESULTS.json`.

Der rekonstruierte H-Zeitverlauf findet **62 T-Noten außerhalb des dort deklarierten
H-Vorrats**, verteilt auf S18(48), S40(10), S28(3), EF12(1). Diese Noten können
unter lokalen Q-/B-/M-Vorräten zulässig sein. Damit sind nicht62falsche Noten
nachgewiesen, sondern eine entscheidende **offene Kontext-Hierarchie**: welcher
lokale Vorrat gilt wann, in welcher Rolle, und relativ zu welcher Wurzel?
„Chromatisch, nur Akkordtöne + autorisierte Töne“ allein legitimiert sie nicht als
T. Keine automatische Änderung zu Akkordtönen; gemeinsame Gültigkeitsdaten oder
explizite alternative Autorisierung nachreichen. Diese vier Gesamtvorlagen sind K.

Während tatsächlich gehaltener Noten wurden sämtliche harmonischen Taktwechsel
rekonstruiert: kein dabei neu fremder Ton außerhalb definierter Klänge/Vorräte
gefunden. Das ist eine Prüfung dieser54konkreten Referenzen, keine generelle
Freigabe aller Querverweiskombinationen oder neuer XYZ-Fahrten.

## Register, Spielweisen und Kombinationen

Die54 Studien liegen in ihrer jeweiligen gelieferten Tonart innerhalb der
Forschungsregister. Bei unveränderter Registerlage auf alle zwölf Zieltonarten
transponiert unterschreiten **acht LB-Noten aus S40 in C** den ForschungsbodenA0:
MIDI 20 statt mindestens 21. Alle bleiben im MIDI-Zahlenbereich0–127. Nicht pro Note
ungefragt oktavieren; passende globale Lage oder Auslassung vorher musikalisch
planen. Für B020/B023/B033/B035/B045/B050 ist die tiefe LB-Zuordnung in einigen
Tonarten ebenfalls außerhalb des angegebenen Forschungsregisters; KB kann andere
Möglichkeiten haben. Pro Vorlage/Rolle sind alle zwölf Schlüssel geprüft.

64 Studien-/Ziel-Kombinationen in 38 IDs verletzen mindestens eine aktuelle
Generatorannahme zu Mindestdauer, Maximaldauer oder Polyphonie. Kürzeste gelieferte
Note48 Ticks; Default-Mindestdauer im Instrumentenmodell240. Der Dispatcher und
Notenemitter können kurze Dauern bereits ausgeben; dies ist keine neue Zeitauflösung,
sondern eine echte Fähigkeits-/Validierungsfrage. TUmax720 und KBmax960 begrenzen
lange Figuren. Externe Patches unbekannt. Weder einfach kürzen noch auf HM
umleiten oder Fähigkeitspass pauschal als passend deklarieren.

R/Gültigkeitsvererbung ist offen: Müssen fest in Q/B eingebettete R-Vorlagen ihren
eigenen XYZ-Bereich mitbringen, oder ist ihre Rhythmik dort ausdrücklich als
Datenreferenz mit neuer Gültigkeit autorisiert? Der konservative Abgleich nimmt
die Schnittmenge. Der alternative Wert ohne R-Domain ist diagnostisch ausgewiesen,
keine Erweiterung. Q003/R013, Q053/R037 sowie mehrere helle/ruhige Q/R-Paare zeigen
die Konsequenz. Einzelne vorhandene IDs beweisen keinen zulässigen Gesamtplan.

Verbindlich bleibt der Anwenderauftrag: Registertrennung ist **Präferenz**, keine
zwingende leere Mittellage; STROMSCORE erkennt Dialog nicht. „Eigenständig“ darf
keine automatische Änderung des Benutzerschalters Follow auslösen. ST bleibt
fester Trigger36, TU tonal. M004 enthält ausdrücklich komponierte Wiederholungen
mit v60/v40; diese sind zulässiges Motivmaterial, kein Auftrag für automatische
Hall-/Delay-Echonoten. Neue CC-, Percussion- oder Ausgangsfunktionen sind offen.
