# Pop/Rock: melodische Rollen, Schritt C

Ausgangspunkt: `a6affa0`, Entwicklungsbranch `develop/composition-core-prototype`.
Keine Künstlerprofile, neuen Bedienelemente oder neuen harmonischen Vorlagen.

## Umsetzung

Die vorhandene Hauptmelodie ist nun auch in Pop/Rock verfügbar. Sie bleibt
standardmäßig ausgeschaltet. `melodyAvailable()` vereinheitlicht ihre Freigabe
für Aktivierung, Solo, Fähigkeitskatalog und MIDI-Export. Der vorhandene
Statushinweis „nur Score“ entfällt; Parameter und GUI-Aufbau bleiben erhalten.

Die Hauptmelodie verwendet `counterLine()`/`motifStep()`, den gemeinsamen
Motivkatalog, ihre eigenen Stimmenzustände und die vorhandene
`policy.motif`-Wiederkehrplanung. Die harmonisch flexible Realisierung aus Schritt B
kann bei Bedarf dieselben gespeicherten Intervalle anpassen, Dauern begrenzen oder
eine geeignete Schlussfigur verwenden. Keine neue Motivimplementierung wurde
angelegt. Der gespeicherte Ursprung bleibt unverändert. Mit Motiv AUS entstehen
freie harmonische Linien in begrenzten Vordergrundfenstern; es wird kein
Hauptmelodie-Motiv aufgenommen. Der eigene Legatoschalter bleibt wirksam.

Die Gegenstimme behält ihre bisherigen Pop-Hooks und die Unterscheidung zwischen
motorischen und phrasenbezogenen Figuren. Mit Motiv EIN verwenden phrasenbezogene
Hooks weiterhin `popHooks.recurrence` samt ihrer bisherigen Varianten und
harmonischen Anpassung. Mit Motiv AUS spielt die Gegenstimme aktuelle Hookfiguren
ohne gezielte gespeicherte Wiederkehr. Ihr Material kann weiterhin als unveränderte
Referenz der bestehenden Begleitkoordination erfasst werden. Das überträgt kein
Material der Hauptmelodie und löscht deren Gedächtnis nicht.

### Tatsächliche Vordergrundfenster

`popLeadWindow()` prüft die effektive Aktivität einschließlich Schwelle, Mute und
Solo, die Instrumenten-/Registereignung und einen tatsächlich spielbaren Plan.
Ein eingeschalteter, aber unspielbarer Melodiepart blockiert die Gegenstimme nicht.
`popDialogueMayLead()` prüft das tatsächliche Fenster und bereits klingende
Melodienoten. Ein neuer Dialoggedanke darf nicht in das geplante Melodiefenster
oder in eine noch ungeplante nächste Phrase hineinreichen. Die Melodie startet
ihrerseits nicht über noch klingenden Dialognoten.

Beide Stimmen behalten unabhängige Aufnahme-, Wiederkehr-, Varianten- und
Linienzustände. Es gibt in diesem Schritt **keine explizite Motivübergabe zwischen
den Pop-Stimmen**. Die bestehende Score-Übergabe bleibt unverändert und wird unter
Pop/Rock nicht zusätzlich aktiviert.

### Musikalisches Atmen statt einzelner Notenausfälle

`composition::planHookTurn()` plant vollständige vorhandene Hookzyklen und
dazwischen Atemzyklen. In 4/4 umfasst ein Zyklus zwei Takte. Die kleine
`PopRolePolicy` steuert die Auswahl mit der effektiven Gegenstimmen-Intensität und
Unruhe:

| Kontext | Ganze Spielzyklen | Ganze Atemzyklen |
| --- | ---: | ---: |
| Intensität < 0,40 und Unruhe < 0,50 | 1 | 2 |
| Intensität >= 0,75 und Unruhe >= 0,50 | 2 | 1 |
| Übrige Bereiche | 1 | 1 |

Die Entscheidung wird am Beginn des Zyklus gespeichert. XYZ-Bewegungen schalten
keine laufende Figur fortwährend ein und aus. Dies ist keine Note-on-Quote und kein
zufälliges Entfernen einzelner Hooktöne. Bereits vollständig geplante motivische
Phrasen behalten ihre vorhandene Wiederkehrplanung. Bei anderen Taktarten dient
konservativ die bestehende ganze Phrase als Atemeinheit, damit native Pop-Muster
nicht durch einen anders skalierten Zwei-Takt-Schnitt zerstückelt werden.

Die erste tatsächlich spielbare Hookeinführung wird vor optionaler Hauptmelodie
geschützt (`popHookIntroductionPending()`). Der Anfang der ersten vier Takte und
die vollständige Aufnahme bleiben erhalten. Bei den gemessenen gemeinsamen
Startfällen folgt die Hauptmelodie im nächsten geeigneten Phrasenfenster ab
Taktindex 8 (16 Sekunden bei 120 BPM); ihre Einführung ist bei 20 Sekunden als
tatsächlich gespieltes Material abgeschlossen. Solo-Hauptmelodie beginnt in den
geeigneten Testfällen sofort. Aufbau und ungeeignete Harmonik können den Einsatz
weiter verzögern. Dies sind musikalische Einsatzentscheidungen, keine zusätzliche
Plugin-Latenz.

## Schutz der Begleitung und des Score-Modus

Die neue Pop-Melodie fügt keine zusätzlichen Aufbau-/End-Slots für die Begleitung
hinzu und deaktiviert nicht deren vorhandene Bass-/Arpeggio-Verzahnung.
Die bestehende Pop-Auto-Arp-Reservierung behält ihre Dialog-Referenz; sie wird nicht
auf die neue Hauptmelodie umgeschaltet und nicht von den neuen Dialogpausen
aufgehoben. Damit bleiben die vier Begleitrollen bei denselben Einstellungen
ereignisgleich, einschließlich ihrer Controller.

Das bedeutet bewusst auch: Ein vorhandenes Arp-Referenzfenster kann bestehen
bleiben, obwohl die Gegenstimme in diesem Durchlauf nicht spielt. Es gibt keine
zusätzliche Arp-Ausdünnung für die Hauptmelodie. Das ist eine Grenze dieses
Auftrags, keine allgemeine Neuplanung sämtlicher Stimmen.

Bei gemeinsamem physischem MIDI-Kanal von melodischer Stimme und Begleitung
verhindert `popLeadRoute()` die neue Hauptmelodie. Bei geteilter Dialog-/Begleitrouting-
Belegung erhält `popDialogRoute()` das bisherige Dialogverhalten. Solche Belegungen
sind kein sinnvoller Test der neuen getrennten Rollenkoordination; sie werden
konservativ behandelt, statt bestehende physische Notenansprüche zu verändern.

Beim echten Live-/Exportvergleich wurde zusätzlich gefunden, dass der SMF-Schreiber
die Melodiespur noch ausschließlich für Score anlegte. Er verwendet jetzt dieselbe
Verfügbarkeitsentscheidung wie der Generator. Dadurch erreicht die neue Pop-Melodie
auch die exportierte MIDI-Datei.

## Reproduzierbare Aktivitätsmessung

Maschinenlesbare Ergebnisse einschließlich Quellcode-Prüfsummen:
[POP_MELODIC_ROLES_MEASUREMENTS.json](POP_MELODIC_ROLES_MEASUREMENTS.json).

105 Einstellungen jeweils vor/nach der Änderung: **210 Renderings à 128 Takte**,
48 kHz, 120 BPM, 4/4, 512 Samples pro Block, Seed 0, Neutral, Aufbau normalerweise
AUS. Darunter neun XYZ-Verläufe, individuelle Stimmen, Motiv AUS, Mute/Solo,
Unterschreitung der Melodieschwelle, späte Deaktivierung sowie Aufbaukontrollen.
Vier Einstellungen schützen zusätzlich das vollständige Score-MIDI.

Gate-Auslastung ist die Vereinigung der MIDI-Notengates einer Rolle im gesamten
256-Sekunden-Durchlauf. Sie misst weder Lautheit noch den Nachklang eines Patches.
Gemeinsame Stille bedeutet: keine gehaltene Note einer der beiden melodischen
Rollen. Statisches XYZ bedeutet wegen Variety nicht zwingend eine statische Wendung.

Beide melodischen Rollen aktiv, alle Begleitrollen verfügbar:

| XYZ/Verlauf | Dialog vorher: Note-ons / Gate | Melodie nachher: Note-ons / Gate | Dialog nachher: Note-ons / Gate | Längste gemeinsame Stille vorher → nachher |
| --- | ---: | ---: | ---: | ---: |
| 0,25 / 0,85 / 0,10 | 976 / 98,10 % | 52 / 15,43 % | 356 / 35,45 % | 0,875 → 5,5 s |
| 0,75 / 0,85 / 0,20 | 548 / 59,91 % | 50 / 16,80 % | 224 / 24,22 % | 30 → 14 s |
| 0,50 / 0,90 / 0,75 | 1024 / 100 % | 55 / 16,80 % | 560 / 54,69 % | 0 → 5 s |
| Langsame XYZ-Fahrt | 970 / 98,97 % | 44 / 13,28 % | 452 / 44,92 % | 0,875 → 5 s |
| Schnelle XYZ-Fahrt | 908 / 92,48 % | 53 / 17,38 % | 389 / 39,01 % | 2,125 → 12 s |
| X-Fahrt, Intensität/Unruhe maximal | 1024 / 100 % | 53 / 15,82 % | 576 / 56,25 % | 0 → 5 s |
| Einführung, danach Intensität/Unruhe maximal | 1024 / 100 % | 53 / 15,82 % | 576 / 56,25 % | 0 → 5 s |
| 0,25 / 0,30 / 0,15 | 256 / 50,10 % | 25 / 9,91 % | 120 / 23,44 % | 28 → 13,125 s |
| 0,60 / 0,55 / 0,40 | 960 / 93,80 % | 53 / 15,82 % | 352 / 34,38 % | 15,875 → 12 s |

Die Hauptmelodie war vorher in allen Pop-Fällen gesperrt. Nachher wurden in keinem
der 105 aktuellen Langläufe positive konkurrierende Vordergrund-Gatezeiten oder
fehlerhafte Note-on/off-Paare gemessen. Das ist zeitliche Rollenkoordination, kein
Beweis einer allgemein gelungenen Instrumentierung.

Zum Vergleich bei nur einer melodischen Rolle, Begleitung gemutet:

| Verlauf | Nur Dialog: Note-ons / Gate | Nur Melodie: Note-ons / Gate |
| --- | ---: | ---: |
| Erstes statisches XYZ | 504 / 50,59 % | 48 / 14,45 % |
| Langsame XYZ-Fahrt | 571 / 58,69 % | 49 / 15,04 % |
| Schnelle XYZ-Fahrt | 540 / 53,91 % | 57 / 18,55 % |
| Niedrige Intensität | 128 / 25 % | 31 / 11,67 % |
| Mittlere Intensität | 496 / 48,44 % | 58 / 17,38 % |

Die jeweils längsten eigenen Pausen sind im JSON enthalten. Beispielsweise hat
die Melodie in der langsamen Fahrt weiterhin bis zu 44 Sekunden Pause, während
die längste gemeinsame Pause beider Stimmen fünf Sekunden beträgt. Eine einzelne
melodische Rolle muss also weiterhin nicht ständig präsent sein.

### Tatsächliche Wiederkehr und konkrete Noten

In der langsamen XYZ-Fahrt stellt die Hauptmelodie bei 16 Sekunden dieses Motiv
vor; bei 32 Sekunden erklingt die erste Wiederkehr:

| | MIDI-Tonhöhen | Relative Einsätze in Vierteln | Notendauern in Vierteln |
| --- | --- | --- | --- |
| Einführung | 81, 76, 72, 81, 84 | 0, 2, 3, 3,5, 4 | 2, 1, 0,5, 0,5, 4 |
| Wiederkehr | 78, 73, 69, 78, 81 | 0, 2, 3, 3,5, 4 | 2, 1, 0,5, 0,5, 4 |

Das ist eine Transposition um drei Halbtöne bei identischem Rhythmus und
Intervallprofil, keine neue Zufallsfigur. Quell-/Figuridentität:
`2033947017052208538`. In diesem Lauf wurden acht aktive Wiederkehrpläne und 39
tatsächlich gespielte Wiederkehrnoten gemessen, zusätzlich fünf Einführungstöne.
Beim ersten statischen XYZ sind es zehn Pläne und 47 Wiederkehrnoten.

Über die gespeicherten Beispiele wurden **50 flexible Hauptmelodie-Realisierungen
mit 203 tatsächlichen Note-ons** am MIDI-Strom geprüft; keines dieser Beispiele
blieb vollständig unausgeführt. In **83 Pop-Vergleichsfällen** mit abgeschlossener Dialogaufnahme
blieb außerdem dessen tatsächlicher MIDI-Präfix bis zur ursprünglichen Einführung
unverändert. In den übrigen 18 Pop-Fällen war die Gegenstimme stummgeschaltet.

## Tests und Reproduktion

- Reguläre Core-Suite: 48 Tests ausgeführt. Vier zunächst fehlschlagende historische
  Tests wurden eng auf ihre ursprünglichen Voraussetzungen berichtigt und mit
  Erfolg wiederholt; damit sind sämtliche 48 Testfälle abgedeckt. Die abschließenden
  drei Pop-Ziele wurden erneut erfolgreich geprüft. Nach dem vollständigen
  abschließenden Neuaufbau bestanden außerdem alle 25 kompilierten Core-Testfälle
  erneut (20,76 Sekunden).
- `PopRoles`: unabhängige Materialzustände, Veröffentlichung der Einführung,
  unspielbarer Melodieplan ohne Dialogsperre, unabhängige Motivschalter, Mute/Solo
  einschließlich Solo bei gesetztem Mute und ausgeschalteter Melodie, wirksame
  Policy-Werte, Register-/Notenledger, Szenenneustart, Seek, Loop, Blockgrößen
  127/512/8192, Swing und 3/8, 5/8, 7/8. Audioprozessaufrufe stehen unter
  `NoAllocations`.
- `PopRoleCatalog`: **522 Vergleiche**, alle 87 produktiven Wendungen, alle drei
  Profile, zwei Transportverläufe. **288 Score-Vergleiche vollständig bytegleich**;
  bei allen 234 Pop-Vergleichen bleiben sämtliche Begleitereignisse unverändert.
  Neue melodische Ereignisse unterscheiden die Pop-Dateien erwartungsgemäß.
- `PopRoleActivity`: zusätzlich 32 schnelle Vorher-/Nachher-Renderings mit aktiven
  Dynamik-Controllern; Begleitnoten und Begleit-CCs unverändert. Die vollständigen
  210 Langläufe schützen die Begleitung separat und prüfen tatsächliche Beispiele.
- Echter JUCE-Prozessor: bestehende **216 importierte Live-/Exportfälle** und vier
  neue 64-Takt-Pop-Melodie-Vergleiche für beide Motivschalter und Legato bestanden,
  zusätzlich die übrigen bisherigen Prozessortests. Der große Block liefert 872
  Note-ons und 872 Note-offs ohne Ledgerfehler.
- ASan/UBSan: `Execution`, `ScoreRealization`, `RoleCoordination`, `PopRoles`
  bestanden. `PopRoles` nach den abschließenden Änderungen erneut bestanden.
  LeakSanitizer war mit `detect_leaks=0` deaktiviert.
- Paketprüfungen: 7/7 bestanden. `git diff --check` ohne Fehler.

Historische Prüfungen für frühere Einzelschritte frieren die neue Pop-Rollenstrategie
nur in ihren isolierten Offline-Headerkopien ein. Die bestehenden Durchgangston-
Fixtures schalten Motiv jetzt ausdrücklich ein. Der alte Voice-Leading-Vergleich
schützt die Begleitstimmen, nicht die hier bewusst geänderte Pop-Gegenstimme.
Der Dichtetest verwendet für Messung und Kontrollrendering dieselben historischen
Voraussetzungen. Die neuen Katalog-, Aktivitäts- und Prozessortests prüfen dagegen
den tatsächlichen aktuellen Produktcode einschließlich beider Pop-Stimmen.

Reproduktion ab Repositorywurzel (bestehendes konfiguriertes Buildverzeichnis
entsprechend ersetzen):

```sh
cmake --build ../stromscore-core-build -j2
ctest --test-dir ../stromscore-core-build --output-on-failure
python scripts/analyze_pop_roles.py --output /tmp/stromscore-pop-roles --bars 128
python scripts/analyze_pop_roles.py --output /tmp/stromscore-pop-roles-cc --quick --dynamics
python scripts/compare_pop_roles.py --output /tmp/stromscore-pop-catalog
python Tests/ReleaseTests.py
```

Die Analyse schreibt pro Fall vor/nachher CSV-Dateien mit samplegenauen MIDI-
Ereignissen und die Messdaten. Reproduzierbare Basisrevision ist immer `a6affa0`.

## Verbleibende Grenzen

Die Zyklusentscheidung ist klein und bewusst deterministisch; eine vollständige
Pop-Dramaturgie oder stilistische Formgrammatik ist damit nicht entstanden.
Andere Taktarten erhalten die bestehende native Musterbedeutung mit konservativen
Phrasenpausen. Die Modus-/Durchgangstonstrategie bleibt bei der bisherigen
Dialogstimme; sie wurde nicht zusätzlich für die Hauptmelodie verändert.

Der Generator kennt weiterhin nur beschriebene Instrumentenfähigkeiten und keine
tatsächlichen externen Patch-Eigenschaften. Kalter Seek besitzt die bereits
akzeptierte begrenzte musikalische Vorgeschichte. Die Messwerte belegen Funktion,
Zurückhaltung und zeitliche Trennung; ob die Musik besser wirkt, bleibt bis zum
Hörtest vorläufig.

Kein Push und kein Release. Keine weiteren Entwicklungsschritte Bestandteil
dieses Auftrags.
