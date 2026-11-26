# Williams P2 – erster gemeinsamer Oktatonik-Kontext

Basis: musikalisch abgenommenes `2c6f366`, siehe
[Anwenderabnahme](../../development/ACCEPTED_REFERENCE_2c6f366.md).
Nur der freigegebene erste Tonvorratsschritt. Die Arp-Phrasierung bleibt unverändert.

## Gemeinsames Modell und vorhandene Daten

`ModalContext.h::Mode::octatonic` erweitert den vorhandenen transponierbaren
Kontext um den Halbton-Ganzton-Vorrat {0,1,3,4,6,7,9,10}. In Bezugstonart C:
C–D♭–E♭–E–F♯–G–A–B♭. Die zwölf Transpositionen ergeben wegen der Kleinterzsymmetrie
drei verschiedene Tonklassenmengen; der Bezugston ist eine Transpositionsreferenz,
keine behauptete funktionale Tonika. `ModalContext` enthält weiterhin Status,
Vorratsmaske und Bezugston; kein zweites Skalen-/Tonhöhensystem.

Oktatonik wird **explizit** angegeben. Die automatische Erkennung der vier bisher
unterstützten diatonischen Modi bleibt unverändert. Aus einem einzelnen Dreiklang
wird keine Oktatonik abgeleitet. Unbekannte, gemischte oder inkompatible Kontexte
liefern keinen gültigen Vorrat; dann gilt der vorhandene Akkordtonpfad.

Der gemeinsame Harmonievalidator prüft die gesamte Wendung einschließlich
expliziter Bässe gegen den angegebenen Vorrat. Acht bereits importierte kanonische
Okt-A-Vorlagen erhalten ausschließlich neue Tonvorratsmetadaten:
**H12/H14/H15/H16/H17/H19/H46/H54** (IDs 40012/40014/40015/40016/40017/40019/40046/40054).
Akkorde, Farben, Bassvorgaben, Dauern, XYZ-Anker, Reihenfolge, Auswahlgewichte und
Begleitrezepte bleiben erhalten. Alle acht sind weiterhin farbgeschützt.
Die Offline-Williams-Prüfung gleicht die Zuordnung mit dem kanonischen Inventar ab;
keine IDs oder Künstlerfälle im Tonvorratskern fest verdrahtet.

`membership(context,chordMask,pitch)` unterscheidet Akkordton, weiteren zulässigen
Vorratston und ausgeschlossenen Ton. Ein gemeinsamer Kontext bedeutet nicht, dass
alle Rollen sämtliche acht Töne spielen müssen. Harmonie/Bass behalten ihre
komponierten Tonklassen; deren Zugehörigkeit ist vorab validiert. Die vorhandenen dekorativen Bassansätze werden in diesem ersten Schritt nicht
neu geplant; chromatische Annäherungen oder Pendelnoten können weiterhin außerhalb
des Vorrats liegen. Eine Bindung sämtlicher erzeugter Basstöne ist eine eigene
spätere Bass-Anbindung. Melodie und Dialog
nutzen denselben Kontext für die nachstehende erste zusätzliche Funktion. Arp und
Akzente erhalten keine neuen Skalenfiguren; feste Stich-Trigger bleiben unabhängig
von der harmonischen Tonhöhensteuerung. Kein Anspruch auf eine vollständige
oktatonische Grammatik sämtlicher neun Ausgänge.

## Erster tatsächlicher Verbraucher: kontrollierter Motivdurchgang

Die vorhandene `planPassingTone`-Funktion wird für passende Score-Motivwiederkehren
mit explizitem oktatonischem Kontext wiederverwendet. Sie war bisher nur in
geeigneten Pop-Figuren wirksam. Kein neuer Motivgenerator, keine Williams-Motivimporte.

Voraussetzungen sind eine bereits geplante Originalwiederkehr nach der musikalischen
Etablierung, zwei geeignete Akkordzielnoten, genügend Zeit, gemeinsamer Harmonieabschnitt
und passende Instrumentenfähigkeiten. Ein kurzer Vorratston verbindet beide Ziele
schrittweise und erreicht zeitlich geplant den folgenden Akkordton. Die erste
vollständige Reprise bleibt geschützt. Rhythmische/andere Varianten werden nicht
zusätzlich gleichzeitig verändert. Der bestehende `PassingPolicy`-Abstand wird
weiterverwendet; keine neue Quote und keine höhere Einsatzwahrscheinlichkeit.

Im expliziten Oktatonik-Kontext darf der Durchgang eine bewusste kleine Sekunde
zum Quell- oder Zielton bilden, etwa C–D♭–E♭ über Cm. Andere Halbtonkonflikte zu
nicht beteiligten Akkord-/Basstönen bleiben ausgeschlossen. Das ist eine eng
begrenzte musikalische Autorisierung, kein Freibrief für beliebige Vorratstöne.
Register, Dauer, verfügbare Notenplätze und geplante Auflösung werden vor der
Ausgabe geprüft. Ungeeignete Verbindungen bleiben unverändert oder entfallen.

Das gespeicherte Originalmotiv bleibt unverändert. Die zusätzliche Note gehört
zur abgeleiteten Wiedergabefigur; Aufnahmeidentität, frühe Reprise, unabhängige
Stimmenzustände und Rollenkoordination werden weiterverwendet. Die Quellnote darf
für den kurzen Durchgang früher enden; Zielposition und Phrasenende bleiben bestehen.
Tatsächlich erklungene Motive werden nicht aus einer neuen Zufallszahl rekonstruiert.

Der gemeinsame Kontext wird außerdem bei bestehenden chromatischen Nachbarn des
Score-Linien-Fallbacks beachtet: Ein unzulässiger Vorhalt wird im neuen Kontext
nicht ausgegeben; der vorhandene Akkordzielton bleibt. Bei freier Linienplanung
kann der optionale Nachbar entfallen. Ohne expliziten Kontext bleibt das bisherige
Verhalten bestehen. Diese kleine notwendige Anbindung verhindert, dass die
Fallback-Stimme den eigenen gemeinsamen Vorrat sofort wieder verlässt.

## Harmonie, XYZ und Zeit

`motifHarmonyAt` bleibt die harmonische Referenz. Der Motiv-Cache berücksichtigt
nun auch Modus/Vorratsmaske; ein alter Plan darf nicht unter einem neuen Kontext
als weiterhin gültig gelten. Die verbleibenden Noten eines begonnenen Plans werden
gegen die aktuelle Harmonie geprüft, bei einem vorgesehenen Durchgang einschließlich
seiner Quell-/Zielbeziehung. Eine aufgegebene Auflösung darf nicht als weiterhin
gültiger Durchgang ausgegeben werden. Fremde oder ungeklärte Kontexte erzwingen
keine neue Skala.

Der erste Schritt ist bewusst auf die bestehende geplante Harmonie und kleine
Durchgänge begrenzt. Zukünftige unbekannte XYZ-Fahrten werden nicht vorausgesagt.
Wechsel zwischen mehreren symmetrischen Vorräten, langfristige Systemmodulation,
unabhängige Bass-Tonfolgen und längere melodische Bögen sind nicht implementiert.
Die bekannte Grenze fehlender Vorgeschichte bei kaltem Seek bleibt bestehen.

Alle Daten sind statisch vorbereitet; keine Dateioperationen, Validierungen oder
Heap-Allokationen im Audiothread. Die vorhandene 64-Bit-Zeitbasis mit 960 PPQ und
der Scheduler bleiben erhalten. Hexatonik, Ganzton und weitere Modi können später
am selben Kontextmodell ergänzt werden; in P2 wurden diese nicht implementiert.

## Prüfungen und A/B-Hörbeispiele

`ModalTests` prüft alle zwölf Transpositionen, acht Töne, Kleinterzinvarianz,
Unterscheidung der drei Mengen, Akkord-/Vorratstonzugehörigkeit, explizite Wahl,
inkompatible Mengen und einen korrekt aufgelösten Durchgang. Die bisherigen
Diatonik-/Pop-Durchgangstests bleiben erhalten. `HarmonyDataTests` prüft die acht
Metadaten sowie unzulässige Bass-/Akkordtöne und falsche Bezugslagen.

`OctatonicTests` rendert H12 über jeweils 128 Takte in allen zwölf Tonarten mit
beiden melodischen Rollen. Er prüft echte ausgegebene Tonhöhen, unveränderliche
Originale, tatsächliche zusätzliche Durchgänge und tatsächliche Zielnoten.
Es wurden **43 Durchgangstöne und 43 tatsächlich gespielte Auflösungen** nachgewiesen.
Die bestehenden Register beeinflussen die erzeugten Originalmotive; nicht jede
Tonart erhält in dieser konkreten Stichprobe zusätzliche Durchgänge. Eine korrekte
Transposition des Vorrats ist keine Garantie derselben absoluten Registerlinie.

Reproduktion: `python scripts/validate_octatonic.py /tmp/oct-p2`.
[Ergebnisse](P2_OCTATONIC_RESULTS.json) und
[MIDI-A/B-Paket](P2_OCTATONIC_AB.zip) stammen aus dem tatsächlichen Produktionspfad,
vorher `2c6f366`, nachher P2. 128 Takte bei 100 BPM, feste XYZ-Positionen und
langsame/schnelle externe Fahrten; unbegrenzt ohne interne Fahrt. Die acht
Referenzharmonien werden zusätzlich in allen zwölf Tonarten geprüft.
Diagnose- und direkte Produktionskompilate müssen identische MIDI-Ereignisse liefern.

Die A/B-Dateien verwenden gleiche Einstellungen und benötigen gleiche externe
Patches. Es sind konstruierte Engine-Ausgaben, keine Filmthemen-Transkriptionen.
Ziel der Hörabnahme ist der begrenzte neue Tonraum innerhalb erkennbarer Motive,
kein Versprechen bereits ausgeprägter Star-Wars-/Indiana-Jones-Thematik.

## Tatsächliche Ergebnisse und musikalische Beispiele

148 Produktions-A/B-Paare über jeweils 128 Takte bestanden: 52 allgemeine XYZ-/
Stimmenfälle und 96 Referenz-/Transpositionsfälle. **409 tatsächlich ausgegebene
Durchgangstöne, 409 tatsächliche Zielauflösungen, keine ungeklärte Auflösung** in
dieser Matrix. 30 zusätzliche Neutral-/Barry-/Herrmann-Vergleiche in Score/Pop
blieben bytegleich zu `2c6f366`, ebenso fünf Williams-Pop-Vergleiche. Wiederholungs-
und 127/512-Blockkontrollen sowie Follow, Swing, 3/8, 5/8, 7/8, Neustart, Loop und
Positionssprünge bestanden mit geschlossenen Note-on/off-Bilanzen.

**Arpeggio-MIDI blieb in allen 148 A/B-Paaren identisch.** Die Implementierungen von
Arp-Phrasierung, Arp-Tempo und Arp-Tonwahl wurden nicht angefasst. Auch die Ereignisse
von Fläche, Bass, Tupfer und Stich sind in diesen Paaren identisch. Ohne beide
Melodierollen ist die vollständige Ausgabe der 13 XYZ-Fälle bytegleich. Der hier
abgenommene Begleitstand wird somit in der geprüften Matrix erhalten.

Beispiele aus den tatsächlichen C-Renderings, Viertelposition ab Szenenbeginn:

| Referenz / Rolle | Bestehende Bewegung | Neue Realisierung | Tatsächliche Auflösung |
|---|---|---|---|
| H12, Hauptmelodie, Cm | E♭5 → C5 | E♭5 → D♭5 → C5 | D♭5 (MIDI 73) bei 129,5 Vierteln, C5 (72) bei 130; identische Materialreferenz bei weiteren Wiederkehren. |
| H17, Dialog, C mit Dissonanzbass | E5 → G5 | E5 → F♯5 → G5 | F♯5 (78) bei 193,5 Vierteln, G5 (79) bei 194; die vorgesehene Bassfarbe bleibt unverändert. |

Die jeweiligen Zwischenintervalle sind 2+1 Halbtöne und gehören zum gemeinsamen
Okt-A-Vorrat, obwohl D♭ über Cm bzw. F♯ über C keine Akkordtöne sind. Die Quellnote
wird für den vorhandenen Durchgangsbaustein verkürzt; Rhythmusanker und Ziel bleiben.
Das Originalmaterial wird nicht umgeschrieben. Die Identitäten und weitere
Wiederkehrzeitpunkte stehen im Ergebnis-JSON.

Die Funktion ist zurückhaltend: Im H12-C-Lauf erklingen drei zusätzliche Durchgänge
in 128 Takten; der erste erst bei 129,5 Vierteln, rund **77,7 Sekunden** bei 100 BPM.
Die Hörbeispiele deshalb mindestens 40 Takte, besser vollständig hören. In schnellen
und langsamen allgemeinen XYZ-Fahrten dieser Matrix entstanden **keine zusätzlichen
Durchgänge**; ungeeignete Gelegenheiten wurden nicht erzwungen. Kontextverträglichkeit
wurde dort trotzdem an tatsächlich ausgegebenen melodischen Noten geprüft.
Diese Zahlen sind Funktionsbelege, keine musikalischen Aktivitätsziele.

Nach der P2-Hörabnahme wäre ein kleiner Import einer nachweislich passenden kurzen
Williams-Grundfigur sinnvoll, z. B. der fünfnotige oktatonische Kern von M42.
Dessen vorgesehene Parallelterzfassung und freie autorisierte Vorratstöne benötigen
zusätzliche explizite Planung; sie sind mit dem jetzigen einzelnen Durchgang noch
nicht vollständig umgesetzt. Kein stillschweigender Vorlagenimport in P2.

Ein zusätzlicher 128-Takt-Swing-Fall über H12 in C weist drei tatsächlich gespielte
Durchgänge mit drei tatsächlichen Auflösungen nach. Diagnose-/Produktionsausgabe
und Blockgrößen 127/512 sind dabei identisch; auch die Begleitung einschließlich
Arp bleibt gegenüber der Referenz unverändert. Ein gezielter warmer Seek in eine
klingende zusätzliche Score-Durchgangsnote rekonstruiert diese und erreicht
anschließend ihre Zielnote. Der Rücksprung auf Szenenanfang erhält die Motividentität;
diese Transportaufrufe sind ebenfalls unter Allokationswache geprüft.

## Abschließender technischer Prüfstand

- Reguläre Core-Suite: **58/58 bestanden**, 1005,88 Sekunden, einschließlich des
  neuen Oktatonik-Tests und der bisherigen musikalischen Regressionen.
- Echte JUCE-Prozessorsuite: **2/2 bestanden**, einschließlich Live-/Exportvergleich.
- Offline-Harmoniedaten: **10/10 bestanden**; beide Daten-/Driftprüfer erfolgreich.
- Paketprüfer: **7/7 bestanden**.
- Gezielter Oktatonik-Test unter **ASan/UBSan bestanden**, einschließlich warmer
  Durchgangsnoten-Rekonstruktion, Auflösung, Loop und Allokationswache.
- 148 Produktions-A/B-Paare, zusätzliche Profil-/Pop-, Block-, Transport- und
  Swing-Prüfungen wie oben dokumentiert. 24 gültige MIDI-Hördateien im A/B-Paket.

Alle Prüfungen unter Linux. Kein Windows-Build in diesem Auftrag. Kein Push,
kein Release und keine eigenständig begonnene Folgephase. Die neue P2-Musik ist
technisch geprüft, ihre endgültige musikalische Bewertung bleibt dem Anwender.
