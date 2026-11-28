# Herrmann P1 – Zweite Hörabnahme, AR und hörbare Ruhe

28.11.2026 · Referenz `2170807` · Entwicklungsbranch `develop/composition-core-prototype`.

## Bestätigte Referenz

Der Anwender bestätigt in Studio One Pro8 die orange CC-Anzeige, den Ausschalt-Reset127, Stich/Akzente, lange und kurze Bässe und die charakteristische Herrmann-Klangsprache. Diese [Abnahme](../../development/ACCEPTED_REFERENCE_2170807.md) bleibt die Grundlage. Die musikalische Hörabnahme der folgenden Korrektur steht aus.

Der genaue AR-Abgleich verwendet MIDI-Kanal5, Oktave0, relativen Intensitätsregler0, C3–D5 **=MIDI60–86**, Auto-Figur/Auto-Tempo und Follow EIN. Der Umfang betrifft die klingenden Noten nach Benutzeroktave. Der relative Regler0 lässt die globale XYZ-Intensität unverändert; er deaktiviert die Rolle nicht. Zusätzlich werden andere Kanäle, Oktaven, eingeschränkte Register, Variationen und Abwechslung geprüft.

## Ursache1 – Eine fremde Gruppe sperrt eine unbeanspruchte Rolle

`Source/LayerAdapter.h::prepareLayers` wählt weiterhin eine primäre koordinierte Rhythmusgruppe. Bisher wurden anschließend **sämtliche** Quellen anderer Gruppen ausgeschlossen. Sobald ein passender Bass wieder spielbar war, gewann häufiger eine Bassgruppe; selbst eine vollständig passende autonome AR-Figur wurde damit verworfen. Eine Bassgruppe wurde unbeabsichtigt als globale Reservierung auch der unbeteiligten AR-Rolle interpretiert.

Normale Produktion bei XYZ(.50/.85/.80), Variation3, Abwechslung50%, ohne Melodie/Dialog: HE-R11/R30/R37/R63 bestehen an den vier16-Takt-Schnappschüssen über64Takte die Eignungsprüfung und werden ausschließlich als `other_rhythm_group` abgelehnt. Insbesondere in den nicht verschmolzenen H93-Abschnitten blockiert damit eine fremde Gruppe die passende AR-Figur. Die H57-Abschnitte tragen beide harmonischen Komponenten bereits auf LF; deren gesonderte AR-Zurückhaltung bleibt erhalten. Die Diagnose unterscheidet diese musikalische Zuständigkeit von ungeeignetem Patch, zu niedrigem AR-Pegel oder melodischem Vordergrund.

Die kleine gemeinsame Funktion `layerGroupAllows` unterscheidet nun tatsächliche Rollenbelegung von einer bloßen Gruppennummer:

- Quellen der gewählten Gruppe behalten ihre gemeinsame Zuständigkeit.
- Belegt die gewählte Gruppe AR, darf keine fremde AR-Gruppe darübergelegt werden.
- Belegt sie AR nicht, dürfen **eigenständige** AR-Gruppen nach denselben bisherigen Eignungs- und Auswahlregeln teilnehmen.
- Ein AR-Mitglied einer Mehrrollengruppe wird dafür nicht aus seiner Gruppe herausgelöst. HE-R11 und R37 bleiben gekoppelt; die vorhandenen autonomen R30 und R63 können begleiten.

Die Auswahl der primären Gruppe und der anderen Rollen bleibt unverändert. Kein neuer Zufallsprozess, keine neue Dichtequote oder Rhythmusfigur. Perioden, Einsatzzeiten, Tonwahl, Notendauern, ganze Figurenpausen und vorhandene Variationsentscheidungen werden aus denselben Quellen übernommen. Gültige Motiv-/Antwortfenster behalten Vorrang.

## Ursache2 – Der obere Klang hatte einen separaten strikten Registerpfad

Normale Rollenfiguren besitzen bereits die gemeinsame Ganzfiguren-Oktavplatzierung aus2170807. Die direkt ausgegebene obere Polychord-Komponente verwendete sie nicht. `renderLayers` verlangte, dass alle drei rohen Quellentöne einschließlich Benutzeroktave bereits in den Umfang passen; andernfalls entfiel die gesamte Komponente.

Beispiel HE-H51 in D: **80–83–87**, bei Benutzerumfang60–86. Ein Ton liegt einen Halbton außerhalb, daher bisher keinerlei Ausgabe dieser Komponente. `layerUpperShift` findet nun einen gemeinsamen Oktavversatz: **68–71–75**. Beide Intervalle3/4Halbtöne und sämtliche Tonklassen bleiben exakt erhalten. Kein Abschneiden des höchsten Tons, individuelles Oktavfalten oder harmonisches Ersetzen.

Die Platzierung berücksichtigt sämtliche noch auf AR liegenden, nicht verschmolzenen Entwicklungsstufen gemeinsam. Passt kein gemeinsamer Oktavversatz, entfällt diese AR-Komponente. Bei H60 umfasst der AR-Teil19Halbtöne; die abschließende tiefe Verschmelzung wird auf LF gespielt und verlangt deshalb keinen entsprechenden Tiefumfang des AR-Instruments. In D/C3–D5 ergibt sich für den oberen Grundton **73 → 61 auf AR, dann49 auf LF**, gegenüber85 → 73 → 49 ohne Umfangsanpassung. Die Bewegung bleibt abwärts und innerhalb des AR-Teils intervalltreu; der Übergang zwischen den unterschiedlich registrierten Instrumenten wird dabei kleiner. Es wird keine identische absolute Registerentwicklung über alle MIDI-Ziele behauptet. Die LF-Verschmelzung, ihre Tonklassen und ihre eigene Registerprüfung bleiben unverändert.

## Ursache3 – Ruhemodus wurde im Schichtpfad zum Totalausfall

Die bestehende gemeinsame Ruhe-Hysterese bedeutet: unter10% Intensität wird die Harmonie gehalten, ab14% kann sie wieder fortschreiten. LF und Bass besitzen bereits Aktivierungsschwelle0; AR startet regulär bei25%, soweit kein relativer Regler das effektive Niveau verändert. Diese Policy-Werte werden **nicht** geändert.

`renderLayerHarmony` kehrte jedoch bei `still` sofort zurück. Gleichzeitig unterband `layerOwns` den regulären Flächenrenderer, weil die automatische Follow-Fläche dem Schichtpfad gehörte. Ergebnis: gültige ausgewählte Harmonie und aktive LF-Rolle, aber keine MIDI-Note. Beim kalten Start bis unter10% vollständig stumm; nach einer vorherigen Absenkung kann die Ruhezone wegen Hysterese bis14% bestehen. Das erklärt die ungefähr10–15% aus dem Hörbericht.

Der vorhandene harmonische LF-Renderer darf jetzt auch in harmonischer Ruhe arbeiten. Er verwendet die **tatsächlich ausgewählte Vorlage**, ihre zulässige Lage und bestehende Instrumentengrenzen. Rhythmische Figuren bleiben im Ruhemodus aus; die vorher pausierende automatische Bassbegleitung wird nicht zusätzlich eingeschaltet. Mute/Solo, manuelle Zuständigkeiten, Follow, Transport und ungeeignete Instrumentengrenzen behalten Vorrang. Keine Rückleitung auf den ersten Katalogeintrag und kein allgemeiner Mindestakkord für alle Situationen.

Konkreter Start D/100BPM, XYZ0/0/0: ausgewählt bleibt HE-H46; nun MIDI **62–65–69**, Velocity40, Beginn **Sample0**, ausgehalten bis Stop. Über64Takte nur drei Anschläge, keine Neuanstöße pro Takt/Phrase und kein zusätzlich erzwungener Bass. Andere gewählte Harmonien können andere zulässige Liegeklänge ergeben. Ein explizites LF-Mute oder ungeeigneter Umfang kann weiterhin Stille bedeuten; bewusst basslose Felder bleiben basslos.

## Tatsächlicher Plugin-Prozessor

`Tests/HerrmannArQuietProcessorTests.h` verwendet normale APVTS-Parameter, echten Host-Transport und `renderMidiFile`, keine erzwungenen Katalogindizes und keine injizierten Pläne.

**176 statische Fälle:**128 untere Feldpunkte mit den Stufen0/2/5/8/10/12/15/20% sowie48 längere AR-Kontexte, jeweils Live-/SMF-Vergleich, Notenbilanz und bewachter Audiopfad ohne C++-/C-Heap-Allokation. Der untere Prozessorraster kombiniert acht X- mit acht Y-Stufen, Z=X, in zwei Registerkonfigurationen. Der zusätzliche Core-Raster prüft alle512 unabhängigen XYZ-Kombinationen dieser acht Stufen.

| Reale Prozessorbedingung | Referenz2170807 | Korrektur |
|---|---:|---:|
| 64 Fälle unter10% Intensität | alle ohne LF | alle mit LF |
| XYZ0/0/0,8Takte, Standardregister | 0 LF-Anschläge | 3 gehaltene LF-Anschläge |
| XYZ(.50/.85/.80), V3,50% Abwechslung,64Takte, AR5/C3–D5 | 0 AR-Anschläge | 160 AR-Anschläge |
| Alle176 Fälle, einschließlich AR-Kanal5/12 | 1830 AR-Anschläge | 9941 AR-Anschläge |

Die Summen sind eine technische Vergleichsmenge, kein musikalisches Dichteziel. Zusätzlich12 zusammenhängende reale Prozessorphasen über je64Takte: Herrmann/Neutral/Barry/Williams, Start im Ruhebereich, Übergang zu höherer Intensität, erneute Absenkung, Profilwechsel im Lauf, Stop/Neustart, Positionssprung, AR-Mute, Bass-Solo, manuelle AR-Figur/-Geschwindigkeit/Follow und Rückkehr zur Automatik. Keine konkurrierende AR-Ausgabe bei Mute/Solo und keine hängenden Noten.

## Breite normale Produktion und Bezug zum letzten Bericht

[P1_AR_QUIET_RESULTS.json](P1_AR_QUIET_RESULTS.json) enthält2286 A/B-Fälle:

- 512 untere XYZ-Kombinationen, je8Takte, keine Rollenaufzwängung.
- 1440 Rasterfälle über das gesamte Feld: vier X-, fünf Y- und vier Z-Stufen einschließlich Randwerten; drei Register/Oktavkonfigurationen, Melodie/Dialog aus oder beide an, drei Kombinationen aus Variation/Seed/Abwechslung; je64Takte.
- 18 langsame/schnelle XYZ-Fahrten beziehungsweise Absenkungsverläufe, je128Takte.
- Drei manuelle/Follow-Vergleiche und48 Transport-/Blockgrößen-/Tonartfälle.
- Sechs konkrete Hörpaare und die **exakt gleichen259 Fälle** des vorherigen Aktivitätsberichts, jetzt2170807 gegen diese Korrektur.

Direkter Vergleich der alten259er-Matrix: **1629 → 50643 AR-Anschläge**, aktive Fälle **69 → 169**. Damit ist der frühere Rückgang2710→1629 durch die wieder geeigneten Bassgruppen anhand derselben Bedingungen eingeordnet. Die Bassaktivität wird dafür nicht wieder eingeschränkt.

Die Dateien enthalten je Rolle Note-ons, aktive Takte, klingenden Zeitanteil, längsten aktiven Abschnitt, längste Pause, Tonumfang, erste konkrete Noten, tatsächlich ausgegebene AR-Quellen und ausgewählte Harmonien. Auch Fälle ohne AR sind enthalten. Es wird kein Kandidat technisch hörbar gemacht, wenn Harmonie, Zeitfenster, Register, Spielweise, Route oder Kontext nicht passen.

| Vergleich | AR-Anschläge vorher → nachher | Aktive Takte vorher → nachher | Klingender Anteil vorher → nachher | Längste Folge aktiver Takte nachher | Längste vollständige AR-Pause nachher |
|---|---:|---:|---:|---:|---:|
| Dramatisch,64Takte | 0 → 160 | 0 → 25 | 0.00% → 15.62% | 15 | 20.00Takte |
| Zellen,64Takte | 163 → 217 | 31 → 40 | 16.11% → 21.58% | 22 | 9.12Takte |
| Langsame Fahrt,128Takte | 43 → 466 | 6 → 60 | 2.10% → 22.75% | 31 | 28.50Takte |
| Schnelle Fahrt,128Takte, Stimmen an | 41 → 595 | 7 → 81 | 2.00% → 29.05% | 25 | 6.44Takte |

Aktive Takte und klingende Zeit sind verschiedene Größen: kurze Noten können viele aufeinanderfolgende Takte markieren, ohne lückenlos zu klingen. Die längsten Pausen schließen zulässige Anfangspausen ein. Im dramatischen Beispiel beginnt AR nach20Takten, weil zuerst eine verschmolzene H57-Textur und anschließend eine Quellenpause gelten; deshalb mindestens64Takte hören.

Die wieder zugängliche Auswahl verwendet in der259er-Matrix vor allem R63(40380Anschläge) und R30(8999); die gekoppelten R11-Anschläge bleiben808. R37 ist in diesem Vergleich weiterhin nicht nachgewiesen. Das Paket stellt Erreichbarkeit her und garantiert keine gleichmäßige Nutzung aller Vorlagen. Die hörbare Verteilung dieser begrenzten Quellenfamilien gehört ausdrücklich zur nächsten Abnahme.

Die Harmonieauswahl ist im gesamten Korpus unverändert. Außerhalb der korrigierten Ruhezone sind die übrigen Rollenereignisse mit ihren Samplezeiten, Noten, Velocitys und Notenenden identisch. Zusätzliche AR-Ansprüche können die interne Reihenfolge gleichzeitig endender **verschiedener** Noten verändern; der Vergleich normalisiert ausschließlich diese gleichzeitige Reihenfolge. Keine Verschiebung von Anschlägen/Notenenden und keine künstliche Produktänderung zur Erzwingung gleicher Bytefolge. Andere Profile werden zusätzlich vollständig bytegenau verglichen.

## Schutzregeln und verbleibende Grenzen

- Die Instrumentenprüfung und A/T/V/F/U-/Slash-/Harmonieprüfungen in `layerFits` und `permittedTone` bleiben unverändert. Die obere Komponente bleibt quellenbezogen autorisiert; ihre Tonklassen werden nicht global für andere Stimmen freigegeben.
- AR-Figur/Tempo AUTO und Follow EIN bleiben Voraussetzung des Schichtpfads. Manuelle AR-Spielweisen/Tempi und Follow AUS behalten ihre bisherige Ausgabe.
- AR kann unterhalb seiner Aktivierungsschwelle, in Motiv-/Antwortfenstern, in ganzen Quellenpausen oder bei ungeeigneter Harmonie/Instrumentierung bewusst schweigen. Verschmolzene Polychorde können die zweite Komponente auf LF tragen; sie erzwingen keine weitere AR-Stimme.
- C3–D5 genügt für viele Figuren und obere Komponenten. Die vollständige AR-Teilfigur muss in einem einzigen Oktavversatz passen; andernfalls entfällt sie. Bei Rollenübergaben wie H60 kann die unterschiedliche Instrumentenlage die Größe des Registersprungs verändern, ohne die Bewegungsrichtung oder die harmonischen Komponenten zu ersetzen. Keine automatische Patch-Erkennung oder Artikulationsumschaltung.
- Die Herrmann-Schichtstrategie bleibt wie P1 zunächst4/4; keine Erweiterung von Zeitmodell oder Scheduler.
- Keine zusätzlichen Tonvorlagen, Profile, GUI-Elemente oder kreativen Parameter. Runtime-Änderungen ausschließlich in `Source/LayerAdapter.h`; Editor, Prozessor-/CC-Code, Policies und Vokabulardaten bleiben gegenüber2170807 unverändert.
- Die vorhandenen CPU-Grenzen der Referenz bei sehr kleinen Puffern werden durch diesen Auftrag nicht als behoben ausgegeben. Für die Hörabnahme zunächst512Samples.

## Prüfungen und Hörabnahme

[Prüfnachweis](P1_AR_QUIET_VALIDATION.json): vollständige Core-/Prozessorregression, ASan/UBSan, zwölf Tonarten, Blockgrößen127/2048, Transport/Stop/Seek/Loop, Live-/SMF-Gleichheit, Datenvalidierung und Paketprüfungen. **564 unveränderte vollständige Notenrenderings anderer Profile/Pop-Rock** plus27 unveränderte Carpenter-TU-Kontexte. Die bereits abgenommenen CC-Funktionen werden durch die bestehende Prozessorprüfung erneut gesichert. Keine neuen Heap-Allokationen, Dateioperationen oder Datenvalidierungen im Audiothread.

Windows-VST3, Windows-Tests, Paketprüfung und pluginval Strictness8 werden im vorhandenen Entwicklungsworkflow desselben Commits geprüft; dessen Ergebnis wird mit dem Artefaktlink berichtet. Keine Änderung am Workflow und kein offizielles Release/Tag.

[Sechs MIDI-A/B-Paare](P1_AR_QUIET_AB_MIDI.zip): kalter ruhiger Start, zwei AR-Kontexte mit Benutzerumfang, langsame/schnelle Fahrt und Absenkung der Intensität. Echte Engine-Ausgabe, D/100BPM/4/4/960PPQ; ein Track je physischem MIDI-Kanal. Der Vorher-Clip des kalten ruhigen Starts enthält absichtlich nur die8Takte Stille des reproduzierten Fehlers.

[Hörtestanleitung](../../development/STUDIO_ONE_TESTBUILD.md) liegt auch im Windows-Artefakt. Technisch nachgewiesen sind passende Ausgabe, unverändertes Quellenmaterial und erhaltene Pausen. Ob die neue Balance musikalisch überzeugt, entscheidet die erneute Anwender-Hörabnahme. Danach Entwicklungsstopp; keine weiteren musikalischen Schritte eigenständig anschließen.
