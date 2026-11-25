# Musikalische Rollenkoordination – Schritt A

Ausgangspunkt: `edeb8e0`, `develop/composition-core-prototype`. Ausschließlich Score-Rollenkoordination; keine neuen Motivtransformationen, Profile, GUI oder Pop/Rock-Regeln.

## Entscheidung und Umsetzung

Die eingeschaltete Melodie ist nicht mehr während sämtlicher Pausen alleiniger Vordergrund. `ScoreEngine.h::melodicRoleWindow()` ermittelt aus vorhandenen Motiv-, Wiederkehr- und Linienplänen ein spielbares Fenster. `dialogueMayLead()` prüft dieses Fenster, tatsächlich klingende Melodienoten und die vorhandene, spielbare Melodie–Dialog-Antwort. Erst danach darf die reguläre Gegenstimme ihren eigenen bestehenden Plan ausführen. Die Entscheidung gilt für `render()`, `nextOnset()`, Chase und die Offline-Inspektion gleichermaßen.

Ein Motivfenster umfasst die tatsächlich spielbaren Noten einschließlich innerer Pausen. Bei der Hauptmelodie wird die schon vorhandene Mindestpause aus `policy.motif.minimumSilentBars` als Atemraum geschützt. Eine unabhängige Gegenstimmenfigur darf weder dieses Fenster noch die explizite Antwort überlappen. Sie darf auch nicht über die nächste noch ungeplante Wiederkehr-Epoche der Hauptmelodie reichen. Ein fehlender Gegenstimmenplan erzeugt keine Ersatzfigur. Bei nichtmotivischer Hauptmelodie bleibt deren vorhandene lokale Linienführung maßgeblich; die Phrasenplanung der Gegenstimme wird nicht auf die Hauptmelodie übertragen.

Die beiden Stimmen behalten ihr eigenes Material, Cursor und Wiederkehrzustände. Die neue Fensterabfrage verwendet die bestehende reine Vorschau; sie schreibt keine künftige Wiederkehrentscheidung vorzeitig fest. Die vorhandenen sparsamen Schlussfiguren-Antworten haben Vorrang. Die alte Dialog–Arp-Übergabe wird bei aktiver Hauptmelodie weiterhin nicht zusätzlich aktiviert.

Mute, Solo und Schwellen wirken über die bereits ausgewerteten `on[]`-Zustände. Ist die Hauptmelodie effektiv ausgeschaltet, gilt die bisherige alleinige Gegenstimmenlogik. Ist sie eingeschaltet, aber ihr Material im aktuellen Register unspielbar, darf die Gegenstimme unabhängig spielen. Neue unabhängige Einsätze werden konservativ unterlassen, wenn ihr MIDI-Kanal mit einem Begleitausgang geteilt wird: Neue physische Notenansprüche dürfen die geschützte Begleitung nicht verändern.

Die bisherigen Arpeggio-Reservierungen bleiben unverändert. Insbesondere erweitert dieser Schritt die Reservierung nicht um die neuen unabhängigen Dialogfiguren. Der Begleitgenerator, Harmonieauswahl, Motivmaterial und Transformationslogik sind unverändert; es gibt keine neue Laufzeitzustandsstruktur oder Speicherallokation.

## Reproduzierbare Aktivitätsmessung

`python scripts/analyze_role_coordination.py --output /tmp/stromscore-role-study --bars 128`

103 Konfigurationen gegen `edeb8e0` und Arbeitsstand, insgesamt 206 Läufe mit je 128 Takten / 256 Sekunden, 48 kHz, 120 BPM, 4/4, Blockgröße 512. Aufbau AUS außer expliziten Aufbaukontrollen; Motivschalter EIN außer den freien Linienkontrollen. XYZ-Fahrten werden pro Audioblock aktualisiert: X=.5+.4·sin(2πq/P), Y=.85+.1·sin(2πq/(1.3P)+.3), Z=.4+.35·sin(2πq/(1.7P)+.7), q in Viertelnoten, P=64 langsam beziehungsweise P=8 schnell. Die Maximalwertkontrolle fixiert Y=Z=1. Sämtliche Einstellungen stehen in `tools/melodic_activity_probe.cpp`; Einzeldaten und Header-Prüfsumme in `ROLE_COORDINATION_A_MEASUREMENTS.json`.

Auslastung bezeichnet die Vereinigungsdauer der ausgegebenen MIDI-Gates je Stimme, keine akustischen Patch-Releases. Stille umfasst den ganzen Messlauf einschließlich Anfang und Ende. Die Tabelle zeigt beide melodischen Rollen bei gemuteter Begleitung. Die Hauptmelodie bleibt gegenüber dem Ausgangsstand vollständig unverändert.

| Verlauf | Melodie: Note-ons / Gate | Dialog vorher → nachher: Note-ons / Gate | längste Pause Melodie / Dialog nachher | längste gemeinsame Pause vorher → nachher |
|---|---:|---:|---:|---:|
| statisch .25/.85/.10 | 58 / 18,95 % | 0 / 0 % → 46 / 14,79 % | 28 / 60,875 s | 28 → 16 s |
| statisch .75/.85/.20 | 58 / 18,95 % | 0 / 0 % → 52 / 16,70 % | 32 / 44 s | 32 → 21,5 s |
| statisch .50/.90/.75 | 30 / 8,59 % | 0 / 0 % → 51 / 14,89 % | 76 / 68 s | 76 → 28 s |
| langsame XYZ-Fahrt | 20 / 6,25 % | 0 / 0 % → 20 / 6,54 % | 76 / 108,875 s | 76 → 76 s |
| schnelle XYZ-Fahrt | 8 / 2,54 % | 0 / 0 % → 20 / 4,54 % | 169,5 / 236 s | 169,5 → 169,5 s |
| X-Fahrt bei Y=Z=1 ab Start | 60 / 17,97 % | 0 / 0 % → 61 / 17,09 % | 28 / 44 s | 28 → 13 s |
| Einführung, danach X-Fahrt bei Y=Z=1 | 5 / 1,56 % | 0 / 0 % → 68 / 19,38 % | 252 / 28 s | 252 → 28 s |
| gehaltene eigene Amaj7-Harmonik | 58 / 18,95 % | 12 / 3,91 % → 63 / 23,14 % | 28 / 61,5 s | 18 → 14 s |

Langsame Fahrt als Kontrollgruppe, jeweils Note-ons / Gate / längste eigene Stille:

| Konfiguration | Melodie | Dialog | längste gemeinsame Stille |
|---|---:|---:|---:|
| Dialog allein | 0 / 0 % / 256 s | 20 / 6,25 % / 76 s | 76 s |
| Melodie allein | 20 / 6,25 % / 76 s | 0 / 0 % / 256 s | 76 s |
| beide ab Sekunde 8 entmutet | 20 / 6,64 % / 109 s | 28 / 8,84 % / 84 s | 84 s |
| Melodie ab Sekunde 8 zugeschaltet | 20 / 6,64 % / 109 s | 20 / 6,25 % / 76 s | 76 s |
| Melodie gemutet oder Dialog solo oder Melodie unter Schwelle | 0 / 0 % / 256 s | 20 / 6,25 % / 76 s | 76 s |
| Melodie solo | 20 / 6,25 % / 76 s | 0 / 0 % / 256 s | 76 s |

Alle 103 aktuellen Läufe haben **0 Sekunden konkurrierende Melodie-/Dialog-Gates** und eine fehlerfreie melodische Notenbilanz. Für jeden Lauf sind sämtliche Begleitereignisse und Melodieereignisse einschließlich Zeit, Kanal, Tonhöhe, Velocity und Ereignistyp identisch zum Ausgangsstand. Verglichen werden kanonische Ereignismengen: Zusätzliche Dialogansprüche können allein die Reihenfolge gleichzeitig ausgegebener Note-offs auf getrennten Ausgängen verändern, nicht deren Inhalt oder Zeitpunkt. Pop/Rock erhält keine neuen Einsätze.

## Tests und Abgrenzung historischer Vergleiche

`Tests/RoleCoordinationTests.cpp` prüft wirklich ausgegebenes MIDI, unspielbare Hauptmelodie, unabhängiges Dialogmaterial, unveränderte Hauptmelodie, Motiv AUS, Mute/Solo/Schwelle, Swing, Blockgrößen und allokationsfreie Verarbeitung. Der Unspielbarkeitsfall scheitert am alten Header und besteht mit der Korrektur. Bestehende Antworttests prüfen weiter die exakten ursprünglichen Antwortnoten innerhalb ihrer geplanten Zeitfenster; zusätzliche unabhängige Einsätze außerhalb sind nun zulässig.

Die historischen Einzelverfahrens-Probes frieren neben ihrem bereits bestehenden 36er-Katalogpool ausschließlich in der kopierten Testdatei die alte Rollenentscheidung ein. Dadurch bleiben ihre alten musikalischen Vergleichsaussagen präzise. Produktiv gibt es keinen Legacy-Schalter. Die tatsächlichen aktuellen Rollen werden separat durch den vollständigen Katalog, Transportvergleiche, direkte Rollentests und die 206 Langläufe geprüft. `scripts/role_regression.py` erlaubt dort ausschließlich zusätzliche Score-Dialognoten; alle bisherigen Dialoganschläge, Melodie-, Begleit- und CC-Ereignisse bleiben geschützt. Seine Negativtests lehnen veränderte geschützte Ereignisse, verlorene Antworten, konkurrierende Stimmen und hängende Noten ab. Die unabhängige historische Prüfung der 98 Scheduler-Korrekturen bleibt unverändert.

## Verifikation

- Reguläre CTest-Suite: 42/42 Tests bestanden; der zunächst an einer veralteten vollständigen Dialogsperre scheiternde Engine-Test wurde gezielt auf Antwortfenster und unabhängige Einsätze angepasst und anschließend erfolgreich wiederholt.

- Reproduzierbare Aktivitätsstudie: 103 Konfigurationen × zwei Revisionen × 128 Takte; alle geschützten Ereignismengen identisch, keine konkurrierenden Melodiegates und keine fehlerhaften melodischen Notenbilanzen.
- Scheduler-/Transportvergleich: 1.313 Renderpaare, 2.177 zusätzliche Blockgrößenvergleiche; 408 bytegleich, 525 mit ausschließlich erlaubter Score-Rollenänderung, 380 mit weiterhin eng geprüfter Transport-/Chase-Abweichung gegenüber dem historischen Ausgangsstand. Die 98 früheren Zeitkorrekturen werden separat unverändert geprüft.
- Tatsächlicher Plugin-Prozessor: 216 Live-/SMF-Vergleiche, zusätzliche musikalische Antwort-/Rollenfälle und Großblocktest mit 872 Note-ons / 872 Note-offs bestanden; C-/C++-Heap-Prüfungen bleiben aktiv.
- ASan/UBSan: Execution, RoleCoordination und Engine bestanden (3/3 Programme, `ASAN_OPTIONS=detect_leaks=0`; keine LeakSanitizer-Aussage). Die neue Rollenprüfung schließt Loop, Vorwärts-/Rückwärtssprung und Szenenneustart in unterschiedlichen Blockgrößen ein.
- Paketvalidator: 7/7 Fixtures bestanden. Es wurde kein Paket veröffentlicht oder gepusht.

## Grenzen

Die Korrektur beseitigt die dauerhafte Checkbox-Sperre, garantiert aber keine Aktivität. Die streng geprüfte harmonische Eignung gespeicherter Motive bleibt unverändert. Bei schnellen Fahrten können deshalb beide Stimmen weiterhin lange pausieren. Es wird weder die Einsatzwahrscheinlichkeit erhöht noch Motivmaterial umgeschrieben. Die Schutzpause und das Verbot, unbekannte künftige Lead-Epochen zu überragen, können geeignete Dialoggelegenheiten zusätzlich auslassen.

Neue Dialogfiguren erhalten in diesem Auftrag keine zusätzlichen Auto-Arp-Pausen, damit die vier Begleitrollen musikalisch unverändert bleiben. Kalter Seek kennt weiterhin keine zuvor gespielte musikalische Vorgeschichte. Eine Aussage über die musikalische Qualität und Durchhörbarkeit erfordert einen Hörtest mit geeigneten Instrumenten; die Messungen belegen Rollenfreigabe und Kollisionsfreiheit, keine subjektive Qualitätssteigerung.

Ein möglicher separater Folgeschritt wäre die Diagnose harmonisch verworfener Motivfenster anhand konkreter Beispiele. In diesem Auftrag wird er nicht umgesetzt.
