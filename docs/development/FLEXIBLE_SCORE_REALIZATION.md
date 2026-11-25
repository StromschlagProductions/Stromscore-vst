# Flexible harmonische Score-Motivrealisierung – Schritt B

Ausgangspunkt: `c835747`, Branch `develop/composition-core-prototype`. Die Rollenkoordination aus Schritt A bleibt erhalten. Kein Push, kein Release, keine Pop/Rock-, Profil-, GUI- oder Harmonieauswahländerung.

## Bestehende Möglichkeiten und Ursache

`CompositionCore.h::deriveMotif()` leitet bereits rhythmische Variation, Schlussfragmente, Sequenzen und Augmentation aus unverändertem, tatsächlich eingeführtem Material ab. `ScoreEngine.h::motifOccurrence()` sucht anschließend konkrete Einsatzorte und eine Transposition. Bisher verlangte Score dabei die Übereinstimmung jeder gespeicherten Tonhöhe über nahezu das ganze Notengate mit allen berührten Harmonien. Die Pop/Rock-Anpassung war davon unabhängig und wird nicht übernommen: Ihre unbeschränkte akkordweise Tonanpassung garantiert keine hinreichende Score-Motivkontur.

Der bestehende Wiederkehrplan prüft achtaktige Epochen, variable Wiederkehrabstände und eine Mindestpause. Er wird nicht häufiger aufgerufen, seine Auswahlwahrscheinlichkeiten werden nicht erhöht. Ein verworfenes Motiv bleibt innerhalb derselben Epoche verworfen. Dieser Schritt verbessert die Realisierung vorhandener Gelegenheiten.

## Kleine gemeinsame Erweiterung

Die Reihenfolge in `motifOccurrence()` ist jetzt:

1. Bisher vorgesehene Variante exakt realisieren.
2. Falls nötig das vollständige Original exakt realisieren.
3. Erst wenn beides scheitert: vollständiges Original mit begrenzter harmonischer Anpassung prüfen.
4. Falls weiterhin ungeeignet: die letzten drei, danach gegebenenfalls die letzten zwei Originaltöne prüfen. Es wird jeweils neu vom unveränderten Katalogmaterial abgeleitet.
5. Ohne geeignete Realisierung pausieren. Es wurde kein zusätzlicher freier Fallback und kein neuer Motivgenerator eingeführt.

`CompositionCore.h::realizeScoreMotif()` ist eine begrenzte, allokationsfreie Suche. Sie hält Einsatzpositionen und ihre Abstände vollständig fest. Gegenüber einer gemeinsamen Transposition dürfen einzelne Töne höchstens zwei Halbtöne abweichen; die Bewegungsrichtung jeder Verbindung bleibt erhalten, Wiederholungstöne bleiben Wiederholungstöne und die Intervalländerung jeder Verbindung beträgt höchstens zwei Halbtöne. Der betragsmäßig größte Intervallsprung bleibt exakt erhalten; bei Gleichstand der erste. Auch ein Fragment muss diese Bedingungen erfüllen. Bevorzugt werden geringe Tonhöhenkorrekturen und eine Lage nahe dem Originalregister.

`motifOccurrence()` stellt dazu die gültigen Akkordtonklassen und die nächste bereits geplante Harmoniegrenze pro Note bereit. Gates dürfen bis zu dieser Grenze oder dem nächsten Figureneinsatz verkürzt werden, jedoch höchstens auf die Hälfte ihrer Ausgangslänge und niemals unter die Instrumentenmindestdauer. Instrumentenmaximum und Tonumfang gelten ebenfalls. Die Begrenzung an einer Harmoniegrenze berücksichtigt die tatsächliche Ausführungszeit: `execution::nominalAt()` bestimmt das passende Tick-Ende im bestehenden Groove-Zeitbereich. Dadurch klingt eine gekürzte Note auch in geswingtem 3/8, 5/8 und 7/8 nicht über die nominale Akkordgrenze hinaus. Scheduler und Swing-Abbildung selbst bleiben unverändert. Die Anpassung ergänzt keine neuen Akkordfarben und verwendet keine ungeprüften Nicht-Akkordtöne. Ein auch über der nächsten Harmonie verträglicher langer Ton kann im konservativen Anpassungszweig trotzdem an der Grenze enden; bereits exakt spielbare Figuren durchlaufen diesen Zweig nicht.

Die tatsächlich benötigte Figurendauer wird neu berechnet. Rollenfenster, Dispatcher, Chase und Notenenden verwenden diese konkrete Realisierung über die vorhandenen Strukturen. Die unveränderte Motividentität bleibt als `sourceIdentity` erhalten; `harmonicRealization`, `harmonicallyAdapted` und `durationAdjusted` beschreiben ausschließlich die abgeleitete Figur. Keine Variante wird zurück in den Motivkatalog geschrieben.

## Begleitung und Rollen schützen

Die vier Begleitrollen sollen ausdrücklich unverändert bleiben. Deshalb erhält die bestehende Arpeggio-Reservierungsabfrage weiterhin nur die exakt realisierbaren Gelegenheiten. Ein kleiner eigener Reservierungscache hält diese Entscheidung innerhalb der Epoche stabil, während der Aufführungscache die zusätzlich realisierbare Figur enthält. Beide benutzen denselben Planer, dasselbe Original und dieselbe Harmoniezeitleiste; es existiert keine zweite Motivimplementation. Pop/Rock verwendet weiter seinen bisherigen Cache und seine Strategie.

Zusätzlich realisierbare Score-Figuren erzwingen keine neuen Arpeggio-Pausen. Eine noch ausstehende, spielbare erste Motivaufnahme der aktiven Dialogstimme wird nicht durch eine optionale angepasste Melodie-Wiederkehr verdrängt. Damit bleibt ihr tatsächlich eingeführtes Material als Grundlage späterer Reservierungen erhalten, auch wenn die Melodie nach ihrer Einführung gemutet wird. Unspielbare Dialogregister lösen diese Wartebedingung nicht aus. Bereits exakt spielbare Melodiepläne behalten ihren bisherigen Vorrang. Die bestehende explizite Dialog–Arp-Antwort mit manueller Arp-Zelle bleibt unverändert und erhält keine neue Anpassung. Bei gemeinsam mit Begleitausgängen genutzten physischen MIDI-Kanälen unterbleibt die zusätzliche Anpassung konservativ, damit keine neuen Notenansprüche die Begleitung verändern.

Schritt A prüft weiterhin die tatsächlichen Vordergrundfenster einschließlich Atemraum und expliziter Antworten. Ein harmonisch gültiger Gegenstimmenplan darf daher weiterhin zugunsten einer führenden Melodie entfallen. Mehr Realisierungsmöglichkeiten bedeuten keine Erlaubnis für parallele Vordergrundstimmen.

## Aktivität: jeweils 128 Takte / 256 Sekunden

48 kHz, 120 BPM, 4/4, 512 Samples, eindeutige Standardkanäle, beide Motivschalter EIN und Aufbau AUS außer expliziten Aufbaukontrollen. 106 Konfigurationen jeweils gegen Ausgangsstand und neuen Stand, insgesamt 212 Langläufe. Verläufe und Mute-/Solo-/Aktivierungsvarianten entsprechen Schritt A; exakte Funktionen stehen in `tools/melodic_activity_probe.cpp`. Gate-Auslastung misst die Vereinigungsdauer ausgegebener MIDI-Noten, keine akustischen Patch-Releases.

Beide melodischen Rollen eingeschaltet, Begleitung gemutet. Angaben vorher → nachher:

| Verlauf | Melodie: Note-ons / Gate | Dialog: Note-ons / Gate | längste gemeinsame Stille |
|---|---:|---:|---:|
| statisch .25/.85/.10 | 58 / 18,95 % → unverändert | 46 / 14,79 % → unverändert | 16 → 16 s |
| statisch .50/.90/.75 | 30 / 8,59 % → unverändert | 51 / 14,89 % → 56 / 16,46 % | 28 → 28 s |
| langsame XYZ-Fahrt | 20 / 6,25 % → 49 / 15,82 % | 20 / 6,54 % → 36 / 11,57 % | 76 → 20 s |
| schnelle XYZ-Fahrt | 8 / 2,54 % → 36 / 11,33 % | 20 / 4,54 % → 51 / 14,99 % | 169,5 → 17,5 s |
| X-Fahrt, Y=Z=1 ab Beginn | 60 / 17,97 % → unverändert | 61 / 17,09 % → unverändert | 13 → 13 s |
| Einführung, anschließend X-Fahrt mit Y=Z=1 | 5 / 1,56 % → 55 / 17,19 % | 68 / 19,38 % → 48 / 13,53 % | 28 → 12 s |

Die Funktion erhöht also nicht pauschal die Aktivität. Bei bereits geeigneten Maximalwert- und ruhigen statischen Motiven bleibt die Ausgabe vollständig erhalten. Die Gegenstimme kann zugunsten tatsächlich geplanter Melodiefiguren auch weniger spielen. In den drei zusätzlichen Kontrollen mit Stummschaltung der Melodie ab Sekunde 40 bleiben die Begleitereignisse ebenfalls unverändert.

Einzelstimmen im neuen Stand, jeweils Note-ons / Gate / längste eigene Stille:

| Verlauf | Melodie allein | Dialog allein |
|---|---:|---:|
| statisch .25/.85/.10 | 58 / 18,95 % / 28 s | 58 / 18,95 % / 28 s |
| statisch .50/.90/.75 | 30 / 8,59 % / 76 s | 30 / 8,59 % / 76 s |
| langsam | 54 / 17,38 % / 28 s | 54 / 17,38 % / 28 s |
| schnell | 41 / 12,89 % / 36 s | 41 / 12,89 % / 36 s |
| Einführung, danach maximale Y/Z-Werte | 60 / 18,75 % / 28 s | 60 / 18,75 % / 28 s |

Die verbleibenden 76 Sekunden Stille im dunklen statischen Einzelstimmenfall sind ausdrücklich kein gelöstes Problem. Die strengen Identitätsbedingungen finden dort weiterhin nicht genügend geeignete Realisierungen. Mit beiden Rollen beträgt die gemeinsame längste Stille dort 28 Sekunden.

### Realisierte und verworfene Gelegenheiten

Melodie bei gemeinsam aktiven Rollen, nach der Einführung:

| Verlauf | zugelassene Epochen | exakte Pläne vorher | Pläne nachher | davon neue flexible Pläne | nicht realisiert (einschließlich Einführungsschutz) |
|---|---:|---:|---:|---:|---:|
| statisch .25/.85/.10 | 11 | 11 | 11 | 0 | 0 |
| statisch .50/.90/.75 | 11 | 5 | 5 | 0 | 6 |
| langsam | 11 | 3 | 10 | 7 | 1 |
| schnell | 11 | 1 | 9 | 8 | 2 |
| Einführung, danach maximale Y/Z-Werte | 11 | 0 | 10 | 10 | 1 |

Einzeldaten enthalten zusätzlich Dialogpläne, Einzelstimmen, Aufbau, späte Aktivierung, Mute/Solo, Schwellen und Pop/Rock-Kontrollen. Die Zähler erfassen materialisierte Pläne, nicht jedes interne Suchkandidatenpaar. In den drei bewegten Beispielen wird je eine optionale Lead-Gelegenheit zugunsten der noch ausstehenden Dialogeinführung ausgelassen. Beim schnellen Verlauf scheitert eine weitere Gelegenheit an den Eignungsbedingungen. Es wird kein rhythmischer Dauereinsatz erzwungen.

Ein harmonisch gültiger Plan ist noch keine Garantie für eine Aufführung: Rollenfreigabe, Aktivierungszeitpunkt und Mute-Fenster werden weiterhin angewendet. Die Beispielprüfung weist deshalb auch geplante Figuren ohne tatsächlich ausgegebene Note ausdrücklich aus.

## Konkrete, tatsächlich ausgegebene Figuren

Dauern und Einsätze in Viertelnoten, Tonhöhen als MIDI-Nummern. Das Original wird anhand der tatsächlichen Einführungs-Note-ons im gleichen Lauf nachgewiesen. Die jeweilige Katalogidentität bleibt erhalten.

1. **Einführung, danach maximale Y/Z-Werte; erste angepasste Wiederkehr ab Sekunde 48:** Original `76,72,69,76,81`; neue Realisierung `76,72,69,76,82`. Einsätze `0,2,3,3.5,4`, Dauern `2,1,.5,.5,4` bleiben vollständig erhalten. Nur der letzte Ton wird um einen Halbton korrigiert. Die Intervalle zum Anfang sind ursprünglich `0,-4,-7,0,+5`, anschließend `0,-4,-7,0,+6`. Der charakteristische Sprung von 69 nach 76 bleibt exakt. Identität `16850298472929787427` bezeichnet weiterhin das unveränderte Original.
2. **Schnelle Fahrt, Melodie ab Sekunde 48:** Das tatsächlich eingeführte Original `77,76,69,76,81` liefert die Schlussfigur `69,76,81`. Deren ursprüngliche Einsätze `3,3.5,4` werden relativ als `0,.5,1` übernommen. Die Dauern `.5,.5,4` werden zu `.5,.5,3`: Der Schluss endet an der nächsten Harmoniegrenze. Beide charakteristischen Sprünge bleiben exakt; es erklingt keine vollständige zweite Themenwiederholung.
3. **Schnelle Fahrt, Dialog ab Sekunde 32:** Das Original `79,81,73,81,84` liefert die letzten zwei Töne `81,84`, realisiert als `82,85`. Die kleine Terz und der Einsatzabstand `.5` bleiben exakt. Dauern `.75,4` werden zu `.5,4` begrenzt. Die gemeinsame Transposition und die kürzere erste Note ermöglichen eine klare, kurze Schlussfigur.

Die maschinelle Prüfung bestätigt für **428 flexible Beispielpläne** die Originalidentität, die tatsächlich gespielte Einführung, unveränderte Einsatzabstände, den exakten charakteristischen Sprung, erhaltene Bewegungsrichtungen und die Dauergrenzen. **1.733 Beispiel-Note-ons** werden im tatsächlichen MIDI wiedergefunden. **23 Beispielpläne ohne tatsächlich ausgegebene Note** werden gesondert ausgewiesen; ein gültiger harmonischer Plan überstimmt Rollen-, Aktivierungs- und Mute-Fenster nicht. Tatsächliche Gates überschreiten die vorgeprüften Grenzen nicht.

## Reproduktion und Tests

- `python scripts/analyze_score_realization.py --output /tmp/stromscore-realization --bars 128`: alle 212 Aktivitätsläufe, MIDI-CSVs und automatische Beispielvalidierung. Pop/Rock wird vollständig verglichen; für jeden Score-Lauf müssen alle Begleit- und CC-Ereignisse unverändert sein, melodische Notenbilanzen stimmen und konkurrierende Gates ausbleiben.
- Der CTest `ScoreRealizationActivity` führt mit `--quick` 26 gezielte 128-Takt-Läufe aus: langsame/schnelle/maximale Fahrten, Einzelstimmen, später Melodie-Mute und eine Pop-Kontrolle.
- `python scripts/compare_score_realization.py --output /tmp/stromscore-realization-catalog`: tatsächlicher aktueller Generator gegen `c835747`, alle 87 produktiven Wendungen × drei Profile × kontinuierlich/Sprünge, **522 Vergleiche**. 519 vollständig bytegleich; drei Score-Fälle enthalten bewusst andere melodische Ereignisse. Alle Begleit- und CC-Ereignisse sind identisch, Pop/Rock vollständig bytegleich, keine konkurrierenden Vordergrundgates oder fehlerhaften physischen Notenbilanzen.
- `Tests/ScoreRealizationTests.cpp`: exakte und angepasste Figuren, unveränderliches Original, charakteristischer Sprung, erhaltene Kontur, konkrete Tonklassen, Dauern, Ablehnung ungeeigneter Figuren und zwölf Transpositionen. Ein synthetischer, tatsächlich durch `Generator::motifOccurrence()` geplanter Wechsel zwischen Cmaj7 und Fismaj7 prüft zusätzlich die realen Gate-Endzeiten in 3/8, 5/8 und 7/8 bei Swing 0/.5/1. Dieser Test scheitert mit der zunächst rein nominalen Dauerkürzung an der tatsächlich überschrittenen Harmoniegrenze und besteht mit der endgültigen Begrenzung.
- `Tests/RoleCoordinationTests.cpp`: zusätzlich tatsächlich eingeführtes Motiv unter später wechselnder chromatischer Harmonik; real genutzte neue Anpassungen, Loop, Vorwärts-/Rückwärtssprung, Szenenneustart, unterschiedliche Blockgrößen und allokationsfreie Verarbeitung. Die bisherigen Rollen-, Mute-/Solo-/Schwellen- und Swing-Prüfungen bleiben erhalten.
- Historische musikalische Einzelverfahrens-Probes fixieren in ihren isolierten Testheadern die zuvor verwendete Score-Realisierungsstrategie. Die separate neue Katalogprüfung setzt `currentMotifs=True` und prüft ausdrücklich den tatsächlichen neuen Generator. Es gibt keinen produktiven Abschalt- oder Legacy-Pfad. Bereits bestehende historische Scheduler-Korrekturen werden unverändert geprüft.

Abschluss: 43 reguläre Basistests plus zwei neue Integrationsregressionen bestanden (45 Testnamen insgesamt). Nach der gezielten Swing-Grenzkorrektur wurden die sechs betroffenen Engine-/Ausführungs-/Integrationsprüfungen erneut erfolgreich ausgeführt. Alle 212 abschließenden 4/4-Vergleichsrenderings sind auch gegenüber dem Stand unmittelbar vor dieser zusätzlichen Grenzkorrektur ereignisidentisch. Die neuen Grenzfälle ändern damit ausschließlich zuvor unzulässig über die Harmoniegrenze reichende adaptive Gates in den entsprechenden Swing-Kontexten.

Der tatsächliche Plugin-Prozessor besteht einschließlich 216 Live-/SMF-Vergleichen und der Großblockbilanz 872 Note-ons / 872 Note-offs ohne Notenverwaltungsfehler. Die C-/C++-Heap-Prüfungen bleiben aktiv. Paketprüf-Fixtures: 7/7 bestanden. Gezielte ASan/UBSan-Prüfungen der endgültigen Implementierung: Execution, ScoreRealization und RoleCoordination bestanden (3/3 Programme, `-O1 -g -fsanitize=address,undefined`, `ASAN_OPTIONS=detect_leaks=0`; keine LeakSanitizer-Aussage).

## Grenzen und musikalische Einordnung

Die konservative Erhaltung des stärksten Sprungs kann sinnvolle andere Varianten ausschließen. Nur Schlussfragmente sind neu als harmonischer Fallback zugelassen; keine freie Fragmentauswahl, keine Modus-Neudeutung, keine automatische Vereinfachung des wichtigsten Intervalls. Der letzte Suchkandidat darf scheitern, und eine Stimme darf pausieren.

Es gibt keine zusätzliche Wiederkehrgelegenheit zwischen den bisherigen Epochen und keine Nachprüfung eines bereits verworfenen Plans bei jeder XYZ-Änderung. Kalter Seek besitzt weiterhin keine musikalische Vorgeschichte. Die Instrumentenfähigkeiten sind Generatorannahmen und keine Erkennung externer Patches.

Die Zahlen belegen mehr spielbare, überprüfbar verwandte Gedanken bei unveränderter Begleitung und zurückhaltender Auslastung. Ob die adaptierten Linien mit den konkreten Instrumenten musikalisch überzeugend und als Motiv erkennbar wirken, bleibt bis zum Hörtest vorläufig. Es wurde kein weiterer Entwicklungsschritt begonnen.
