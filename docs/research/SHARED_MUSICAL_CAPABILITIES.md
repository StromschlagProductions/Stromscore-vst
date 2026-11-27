# Gemeinsame musikalische Fähigkeiten – Williams, Herrmann und später SYNTH

Stand: 27.11.2026 · Engine `023b0a6` · `develop/composition-core-prototype`.
Fortschreibung des früheren Abgleichs bei `ddad94b`: Williams P2-Oktatonik und
P3-Motive sind jetzt berücksichtigt; deren musikalische Hörabnahme steht aus.
Die positiv gehörte Arpeggio-Phrasierung `2c6f366` bleibt unverändert.
Dieser Bericht plant ausschließlich. Keine Engine-/GUI-/Laufzeitdatenänderung.

Maßgebliche Quellen: [Williams-Plan](john-williams/IMPLEMENTATION_PLAN.md),
[P2](john-williams/P2_OCTATONIC.md), [P3](john-williams/P3_MOTIFS.md), die neue
[Herrmann-Bibliothek](bernard-herrmann/README.md) mit
[343 Einzelbewertungen](bernard-herrmann/TECHNICAL_INVENTORY.json) sowie die separate
[Tiefenrecherche](bernard-herrmann/Spannungsgrammatik_Tiefenrecherche.md).
Konstruktions-/Evidenzangaben bleiben Angaben der Autoren, keine hier neu bestätigten
Filmtranskriptionen. Archivfassungen, BH-/HE-Überdeckungen und CSV/MIDI nicht doppelt
als Material zählen. Forschungsrezepte sind keine Implementierungsaufträge.

## Gemeinsamer Bestand und Lücken

| Bereich | Im tatsächlichen Code vorhanden | Nächste gemeinsame Fähigkeit / präzise Grenze |
|---|---|---|
| Harmonie-Datenpfad | [HarmonyTypes.h](../../Source/HarmonyTypes.h): `HarmonyTemplate`, stabile ID, Herkunft, XYZ, expliziter Bass, geschützte Farben. Validierte Quelldaten → statische Kataloge,181 Vorlagen/27 Typen. | Weitere exakte Typen bedarfsgerecht ergänzen. AchtSlots und ganze Taktdauern bleiben reale Grenzen. Niemals einen ähnlich benannten Typ als Ersatz verwenden. |
| Tonvorräte | [ModalContext.h](../../Source/ModalContext.h): Ionisch/Mixolydisch/Dorisch/Äolisch; P2 explizite transponierbare Oktatonik, `PitchMembership` chord/collection. Aktive Verbraucher sind begrenzt. | Ganzton, danach Hexatonik; ggf. Lydisch/weitere konkrete Systeme. Gemeinsame Rollenreferenz und Gültigkeit bei Wechseln. Herrmanns Okt-A/B sind lokale Vorräte, keine allgemeine Oktatonikpflicht. |
| Zusatztöne und Funktionen | `planPassingTone` prüft diatonische/oktatonische Durchgänge mit Ziel, Register und Zeit. [AuthoredMotifSource.h](../../Source/AuthoredMotifSource.h)::`authoredPitchMask` erlaubt zusätzliche Quelltöne bei exakt passendem Harmonie-/Basskontext. | A/T/V/F/U als unterscheidbare musikalische Absichten bei flexibler Realisierung; V-Ziel/Frist prüfen, F/U erhalten. Die bestehende lokale Maskenfreigabe ermöglicht bereits unveränderte kurze Quellen; sie ist keine allgemeine dissonante Liniengrammatik. |
| Bass | `Chord.bass`/Slash-Bass, Bassspielweisen und Pedalanker; [BassPhrase.h](../../Source/BassPhrase.h) mit begrenztem Pop-Verbraucher. Williams-P1 besitzt einige relative B-Quellen. | Gemeinsame notierte fixe/relative Bassfolge mit Kontur, Rhythmus und eigener Ziel-/Funktionsabsicht. Score hat keinen allgemeinen Bass-Quelllinienplan. Follow AUS ist kein Ersatz; beide Benutzereinstellungen ausdrücklich respektieren. |
| Pedale | `ScoreEngine::pedalRoot/BassPedal` und kontextgeprüfte Williams-Pedalfigur; wiederholte explizite Slash-Bässe können dissonant sein. | Unabhängige Lebensdauer und expliziter Ton, zunächst ein tiefes/inneres Pedal, dann hohes/Doppelpedal. Beginn/Ende über Akkord-/Wendungsgrenzen. Keine ungeprüfte Bindung an das Ende der aktuellen Harmonie. |
| Stimmführung / Planing | [VoiceLeading.h](../../Source/VoiceLeading.h), `CompositionCore::planHarmony/buildAnchor/leadEntry`: Register, Anker, gemeinsame Töne und kleine Wege. | Exakte chromatische Strukturverschiebung als eigene Absicht; normale Optimierung darf Umkehrungen ändern. Feste Parallelintervalle, Komponenten und Bassbeziehungen sonst nicht garantiert. |
| Motive | [CompositionCore.h](../../Source/CompositionCore.h): unveränderliches tatsächlich gespieltes Material, Identität aus Intervallen/Rhythmus/Dauern, unabhängige Verwendung. Frühe Reprise, Fragment/Sequenz/Augmentation/Rhythmusvariation. P3 registriert 32 Williams-Quellen, 20 im dortigen Produktionsnachweis. | acht Noten, zwei Materialien/Szene und kurze Einführungsfenster sind Grenzen. Quellenregistrierung ist kein Klangnachweis. Kontrollierte modulare Bearbeitung statt willkürlicher Kombination vieler Varianten. |
| Repetitive Module | Motivwiederkehr, Pop-Hook/Ostinato-Unterscheidung, [ArpeggioPhrase.h](../../Source/ArpeggioPhrase.h) und Rollenfenster liefern Teilverfahren. | Kurzes Modul mit eigener Wiederholungsfunktion, Pause/Unterbrechung und identischer Rückkehr; danach Kürzung/Verlängerung. Kontinuierliche Sequenz bleibt gültig, keine verpflichtende Score-Mindestpause für SYNTH. |
| Gemeinsame Rhythmik | [RoleRhythm.h](../../Source/RoleRhythm.h)::`RoleRhythmSource/planRoleRhythm`, Williams-KF/Bass: zwei Takte4/4; [BarryVocabulary.h](../../Source/BarryVocabulary.h)::`planBar`; Pop-Bass/AR-Verzahnung; Motiv-/AR-Reservierungen. | Kleine Datenverbraucher für exakte Triolen und2/3-Gruppierung; getrennt davon eigene Perioden/Phasen, später mehrrollige Entwicklung. Endliches abweichendes Raster ist nicht automatisch eine neue Rhythmusengine. |
| Zeit / Ausführung | [MusicalTime.h](../../Source/MusicalTime.h), [MusicalExecution.h](../../Source/MusicalExecution.h):64 Bit960 PPQ, Harmonie unabhängig vom Swing, deterministische Ausführung. | Die Zeitbasis ist fertig. Achteltriolen320 Ticks sind darstellbar; heutige Vorlageneingänge zählen vielfach240 Tick-Sechzehntel. Verbraucher erweitern, keinen neuen Scheduler auf Vorrat bauen. |
| Polychorde | Ein Akkordobjekt pro Slot, Intervalle pro Typ maximal5; keine Komponentenidentität. Eine Vereinigung von Tonklassen kann als Maske berechenbar sein. | Getrennte Komponenten mit Register, Zeit und Artikulation; Verschmelzung verändert diese Beziehungen. Weder PC-Vereinigung noch Weglassen einer Hälfte ist eine vollständige Umsetzung. |
| Rollen / Instrumente | `CompositionCore::MusicalRole/RoleNeed/PlayingTrack/suitable`, `ScoreEngine::outputCatalog`:9 Ziele, getrennte LF/KF/LB/KB, Rollenfähigkeiten und MIDI-Adresse getrennt. Unabhängige HM-/GS-Zustände; enge HM→GS- und GS→AR-Antworten. | Explizite Rollenwanderung/Kanon und Komponenten-Synchronität erst bei konkreter Vorlage. Keine beliebige Begleitlinie automatisch in GS verschieben. Kein zusätzlicher Ausgang ohne Bedarf und Forschung. |
| Register und Synchronität | Konfigurierbare Tonumfänge, Artikulations-/Polyphonie-/Dauerprüfung; bestehende Vordergrundkoordination. | Gemeinsamer Registerabstand, definierter Versatz und synchroner Eintritt als unabhängige Parameter. Keine pauschale Rollenabschaltung, wenn Bass oder Kurzfläche aktiv sind. |
| Langzeitentwicklung | Phrasen-/Szenenplanung, Ereignisdichte getrennt von Intensität, Aufbau/Ende, freie kurze Zieltonlinien, frühe Reprise. | Kurze Module und kontrollierte Gestaltwechsel bei statischem XYZ zuerst. Später längere Bögen, Verschachtelung, Liquidation und gerichtete Entwicklung. XYZ-Fahrt und autonome Entwicklung sind verschiedene Fälle. |

Der heutige Herrmann-Eintrag bleibt `harmonySelectionOnly` mit neutraler Policy.
`roleRhythm` prüft Williams/4/4, `authoredMotifs` Barry/Williams und
`williamsMaterial` nur Williams. Die gemeinsamen Daten-/Planungsfunktionen sind
damit vorhanden, ihre HE-Quellenanbindung aber nicht. Quellenauflösung bei Bedarf
begrenzt gemeinsam nutzen, keine parallelen HE- oder SYNTH-Kopien anlegen.

### Wichtige Daten- und Instrumentenbefunde

Die HE-Prüfung bestätigt343 IDs und53 SMF/5.328 Noten mit CSV-Gleichheit,960 PPQ und
ST36. Sie bestätigt nicht die Eignung der heutigen Ziele:22 Studien-/Transformations-
IDs enthalten28 Dauer-/Polyphonieabweichungen gegenüber den Generatorannahmen.
KF/TU sind derzeit auf 720 Ticks, KB auf 960 Ticks begrenzt; LB und KB je monophon.
Ein reales externes Instrument kann mehr oder weniger leisten, ist aber unbekannt.
Lange Kurzrollen-Noten und Bassdyaden daher weder kürzen noch still umrouten.
LB+KB mit je einer Stimme ist physisch etwas anderes als zwei Stimmen auf LB.

`stichFixed/stichNote` erlauben eine feste Triggeradresse (Standard36). Deren
Tonhöhen-/Geräuschcharakter ist unbekannt. HE-ST36 bleibt fest und untransponiert;
keine Motiv-, Modus- oder Harmonieregel darauf anwenden.

Geschützte Akkordfärbung verhindert automatische harmonische Erweiterung; sie
schützt nicht automatisch fremde Pedaltöne, Basslinien oder Schlussdissonanzen.
„Chromatisch“ bezeichnet ein begrenztes Klangobjekt mit autorisierten Ausnahmen,
keine allgemeine Zwölftonfreigabe.

## Musikalische Unterschiede auf derselben Grundlage

| Gemeinsames Verfahren | Williams | Herrmann | Später SYNTH |
|---|---|---|---|
| Vorrat / Klangobjekt | Oktatonische Action/Mystery, später Hexatonik; nicht nur heroische Fanfare. | mMaj7/Aug/ø7, Ganzton und lokale Hexatonik; nichtfunktionale Objekte und helle Kälte. | Statische Felder und modal/tonal gewählte Sequenzen; Forschung entscheidet. |
| Bass / Pedal | Gerichtete Ziel-/Spannungslinie, beweglicher Systembass, Pedal als Option. | Innen-/Hoch-/Tritonus-/Halbtonpedale, Pendel und chromatische Gegenbewegung. | Harmonisch unabhängige Basssequenz und langes Pedal ohne erzwungene Pausen. |
| Repetition | Erkennbare Reprise und Weiterführung; spätere längere Zielbögen. | Identische kurze Zellen, Interpunktion, Kürzung/Verlängerung, Verweilen. | Hypnotischer Zyklus, minimale Variation, motorische Präzision. |
| Schichten | Dialog, später koordinierte Action und Komponenten. | Register-/Zeittrennung und Verschmelzung bei unverändertem Material. | Ineinandergreifende Perioden, Schichtung und ggf. Phasenverschiebung. |
| Statische XYZ-Position | Zusammenhalt und Entwicklung ohne Dauer-Lead. | Gestaltwechsel ohne obligatorische Eskalation/Entspannung. | Lange Entwicklung durch Schichtung, keine Pflichtrotation pro Phrase. |

Das sind flexible Präferenzen, keine Künstlerverbote oder neue getrennte Engines.
Die neun Ausgänge bleiben zunächst erhalten. Komposition und Instrumentierung sind
unabhängig: elektronische Verfahren müssen auch orchestral spielbar sein und umgekehrt.
Für SYNTH haben Carpenter/KADAITCHA und klassische elektronische Horrorverfahren
besondere Priorität; Percussion/CC/zusätzliche Rollen bleiben Forschungsfragen.
Siehe [Projektentscheidung](../MUSICAL_DIRECTION.md).

## XYZ und Auswahl

Harmonieauswahl bleibt vollständig XYZ-geführt. In der kanonischen HE-Bibliothek
sind57 Rhythmus-,24 Bass-,45 Motiv- und18 Phrasenquellen ausdrücklich X-unabhängig.
Ihr dunkler Forschungsanker darf keine versteckte Helligkeitssperre werden.
[Diagnose](bernard-herrmann/XYZ_COVERAGE.json): In den heute für Williams verwendeten
3 D-Radien wäre am X=1-Rand jede dieser unabhängigen R/B/M-Quellen selbst an ihrem
eigenen Y/Z unerreichbar. HE wird derzeit noch nicht konsumiert.

Begrenzte spätere Lösung: nur bei als unabhängig deklarierten Quellen X aus deren
Nähebewertung nehmen; eingeschränkte/bedingte Registervarianten explizit prüfen.
„Eher/bevorzugt“ ist keine harte Ausschlussliste. Harmonische Voraussetzungen und
reale Rollen-/Instrumentenfähigkeit entscheiden weiter. Keine globale XYZ-Änderung,
keine Gewichte zum Überspielen ungültiger Dissonanzen. Klangliche Vielfalt und
Erreichbarkeit getrennt messen.

## Empfohlene Reihenfolge und Anpassung des Williams-Plans

1. **Williams P2/P3 hören.** Die bereits akzeptierte Arp-Phrasierung bleibt stehen.
2. **Kanonische Klärungen und kleiner hörbarer HE-Begleitimport:** passende bestehende
   Harmonien/Raster, validierte Provenienz/Dublettenbehandlung und lokale Farbdomäne.
   Ohne HM/GS testen. Keine Vollbibliothek auf einmal.
3. **Unabhängiges Einzelpedal, dann begrenzte Bassfolge.** Gemeinsame Ton-/Funktions-
   absicht von Anfang an berücksichtigen; Follow-Konflikte ausdrücklich klären.
   Williams-Bass/Pedal und Herrmann-Horror erhalten dadurch früh neue Möglichkeiten.
4. **Lokale A/T/V/F/U-Semantik und konkrete Ganzton-/Hexatonik-Kontexte** ergänzen,
   soweit die jeweilige Quelle sie braucht. Keine Pflichtskala für reine Aug-Akkorde.
   Bestehende P3-Quellmasken weiterverwenden, keine zweite Pitch-Architektur.
5. **Ein kurzes Modul mit Wiederholung/Unterbrechung/Rückkehr**, danach Kürzung und
   Verlängerung. Für alle drei künftigen Genres nutzbar, ohne universelle Formengine.
6. **Exakte Strukturverschiebung; zwei Komponenten mit Register-/Zeitplan.** Zunächst
   zwei geprüfte Zustände, kein umfassendes Orchestrierungsmodell. Instrumenten-
   Dauer-/Polyphoniegrenzen vor Polychord-Hörabnahme lösen.
7. **Triolen-/Hemiolen-Verbraucher** können als kleiner separater Daten-Schritt früher
   erfolgen; **unabhängige Perioden und Rollenwanderung** erst mit fortgeführter
   Phase und vorhandenen gemeinsamen Plänen. Nicht taktweise zurücksetzen.
8. **Längere Phrasen, Fugato und komplexe Szenarien** zuletzt gezielt, nicht durch
   bloßes Vergrößern des Motivarrays.

Diese Reihenfolge ersetzt die überholte Annahme, Williams-Motive müssten vollständig
bis nach allen harmonischen Erweiterungen warten: P3 ist bereits angebunden.
Weitere exakt kontextkompatible kurze Motive können begrenzt folgen; Modelle mit
F/U-Transformation, Polychordbezug oder langen Bögen bleiben von ihren tatsächlichen
Voraussetzungen abhängig. Ein allgemeines Langphrasensystem bleibt nachrangig.

Konkrete IDs, Testkriterien und Aufteilung:
[Herrmann-Implementierungsplan](bernard-herrmann/IMPLEMENTATION_PLAN.md).
Jeder Schritt braucht Produktionsnachweis, A/B-MIDI und Hörabnahme, 12 Transpositionen,
Mute/Solo/Follow/Artikulation, Determinismus, Seek/Loop, Blockgrößen und Live/Export;
unveränderte Profile/Rollen separat regressieren. Audiothread frei von Dateizugriff,
Validierung und neuen Allokationen halten. Kein Schritt ist hiermit implementiert
oder freigegeben.
