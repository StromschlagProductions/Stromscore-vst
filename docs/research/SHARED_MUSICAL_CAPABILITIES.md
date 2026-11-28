# Gemeinsame musikalische Fähigkeiten – Williams, Herrmann, Carpenter, Morricone und SYNTH

Stand: 27.11.2026 · `develop/composition-core-prototype` · musikalisch abgenommene
Grundlage `023b0a6`, aktueller Analyse-Ausgang `4c43bd2`.
Williams P2-Oktatonik und P3-Motive wurden vom Anwender in Studio One ausdrücklich
positiv gehört; [Reichweite der Abnahme](../development/ACCEPTED_REFERENCE_023b0a6.md).
Die positiv gehörte Arpeggio-Phrasierung `2c6f366` bleibt unverändert.
Der Planungsabgleich wurde nach dem ersten begrenzten [unabhängigen Einzelpedal](john-williams/INDEPENDENT_PEDALS.md)
fortgeschrieben. Dieses neue Pedal benötigt seine eigene Hörabnahme. Die übrigen
unten beschriebenen Erweiterungen sind weiterhin Planung, keine aktivierten Funktionen.

Maßgebliche Quellen: [Williams-Plan](john-williams/IMPLEMENTATION_PLAN.md),
[P2](john-williams/P2_OCTATONIC.md), [P3](john-williams/P3_MOTIFS.md), die neue
[Herrmann-Bibliothek](bernard-herrmann/README.md) mit
[343 Einzelbewertungen](bernard-herrmann/TECHNICAL_INVENTORY.json) sowie die separate
[Tiefenrecherche](bernard-herrmann/Spannungsgrammatik_Tiefenrecherche.md).
Die [Carpenter-Recherche einschließlich maßgeblicher Vertiefung](john-carpenter/README.md)
ergänzt diese Grundlage. Die inzwischen archivierte
[kanonische405-ID-Bibliothek](john-carpenter/IMPLEMENTATION_PLAN.md) ist vollständig
geprüft; aktuelle Konkretisierungen stehen im neuen Abschnitt am Ende.
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
| Pedale | Gemeinsamer `PedalPlan` mit eigener 960-PPQ-Lebensdauer, kontextgebundener Dissonanzautorisierung und geschütztem Notenbesitz. Begrenzte Williams-Anbindung an JW-H03/H50/H61; bestehende andere Basspfade bleiben erhalten. | Hohe/innere und mehrfache Pedale, frei notierte Lebensdauern und weitere datenbasierte Künstleranbindungen bleiben offen. Der erste Schritt ist unter [INDEPENDENT_PEDALS.md](john-williams/INDEPENDENT_PEDALS.md) dokumentiert. |
| Stimmführung / Planing | [VoiceLeading.h](../../Source/VoiceLeading.h), `CompositionCore::planHarmony/buildAnchor/leadEntry`: Register, Anker, gemeinsame Töne und kleine Wege. | Exakte chromatische Strukturverschiebung als eigene Absicht; normale Optimierung darf Umkehrungen ändern. Feste Parallelintervalle, Komponenten und Bassbeziehungen sonst nicht garantiert. |
| Motive | [CompositionCore.h](../../Source/CompositionCore.h): unveränderliches tatsächlich gespieltes Material, Identität aus Intervallen/Rhythmus/Dauern, unabhängige Verwendung. Frühe Reprise, Fragment/Sequenz/Augmentation/Rhythmusvariation. P3 registriert 32 Williams-Quellen, 20 im dortigen Produktionsnachweis. | acht Noten, zwei Materialien/Szene und kurze Einführungsfenster sind Grenzen. Quellenregistrierung ist kein Klangnachweis. Kontrollierte modulare Bearbeitung statt willkürlicher Kombination vieler Varianten. |
| Repetitive Module | Motivwiederkehr, Pop-Hook/Ostinato-Unterscheidung, [ArpeggioPhrase.h](../../Source/ArpeggioPhrase.h) und Rollenfenster liefern Teilverfahren. | Kurzes Modul mit eigener Wiederholungsfunktion, Pause/Unterbrechung und identischer Rückkehr; danach Kürzung/Verlängerung. Kontinuierliche Sequenz bleibt gültig, keine verpflichtende Score-Mindestpause für SYNTH. |
| Gemeinsame Rhythmik | [RoleRhythm.h](../../Source/RoleRhythm.h)::`RoleRhythmSource/planRoleRhythm`, Williams-KF/Bass: zwei Takte4/4; [BarryVocabulary.h](../../Source/BarryVocabulary.h)::`planBar`; Pop-Bass/AR-Verzahnung; Motiv-/AR-Reservierungen. | Kleine Datenverbraucher für exakte Triolen und2/3-Gruppierung; getrennt davon eigene Perioden/Phasen, später mehrrollige Entwicklung. Endliches abweichendes Raster ist nicht automatisch eine neue Rhythmusengine. |
| Zeit / Ausführung | [MusicalTime.h](../../Source/MusicalTime.h), [MusicalExecution.h](../../Source/MusicalExecution.h):64 Bit960 PPQ, Harmonie unabhängig vom Swing, deterministische Ausführung. | Die Zeitbasis ist fertig. Achteltriolen320 Ticks sind darstellbar; heutige Vorlageneingänge zählen vielfach240 Tick-Sechzehntel. Verbraucher erweitern, keinen neuen Scheduler auf Vorrat bauen. |
| Polychorde | Ein Akkordobjekt pro Slot, Intervalle pro Typ maximal 5; keine Komponentenidentität. Eine Vereinigung von Tonklassen kann als Maske berechenbar sein. | Getrennte Komponenten mit Register, Zeit und Artikulation; Verschmelzung verändert diese Beziehungen. Weder PC-Vereinigung noch Weglassen einer Hälfte ist eine vollständige Umsetzung. |
| Rollen / Instrumente | `CompositionCore::MusicalRole/RoleNeed/PlayingTrack/suitable`, `ScoreEngine::outputCatalog`:9 Ziele, getrennte LF/KF/LB/KB, Rollenfähigkeiten und MIDI-Adresse getrennt. Unabhängige HM-/GS-Zustände; enge HM→GS- und GS→AR-Antworten. | Explizite Rollenwanderung/Kanon und Komponenten-Synchronität erst bei konkreter Vorlage. Keine beliebige Begleitlinie automatisch in GS verschieben. Kein zusätzlicher Ausgang ohne Bedarf und Forschung. |
| Register und Synchronität | Konfigurierbare Tonumfänge, Artikulations-/Polyphonie-/Dauerprüfung; bestehende Vordergrundkoordination. | Gemeinsamer Registerabstand, definierter Versatz und synchroner Eintritt als unabhängige Parameter. Keine pauschale Rollenabschaltung, wenn Bass oder Kurzfläche aktiv sind. |
| Langzeitentwicklung | Phrasen-/Szenenplanung, Ereignisdichte getrennt von Intensität, Aufbau/Ende, freie kurze Zieltonlinien, frühe Reprise. | Kurze Module und kontrollierte Gestaltwechsel bei statischem XYZ zuerst. Später längere Bögen, Verschachtelung, Liquidation und gerichtete Entwicklung. XYZ-Fahrt und autonome Entwicklung sind verschiedene Fälle. |

Der heutige Herrmann-Eintrag bleibt `harmonySelectionOnly` mit neutraler Policy.
`roleRhythm` prüft Williams/4/4, `authoredMotifs` Barry/Williams und
`williamsMaterial` nur Williams. Die gemeinsamen Daten-/Planungsfunktionen sind
damit vorhanden, ihre HE-Quellenanbindung aber nicht. Quellenauflösung bei Bedarf
begrenzt gemeinsam nutzen, keine parallelen HE- oder SYNTH-Kopien anlegen.

### Wichtige Daten- und Instrumentenbefunde

Die HE-Prüfung bestätigt 343 IDs und53 SMF/5.328 Noten mit CSV-Gleichheit,960 PPQ und
ST 36. Sie bestätigt nicht die Eignung der heutigen Ziele:22 Studien-/Transformations-
IDs enthalten 28 Dauer-/Polyphonieabweichungen gegenüber den Generatorannahmen.
KF/TU sind derzeit auf 720 Ticks, KB auf 960 Ticks begrenzt; LB und KB je monophon.
Ein reales externes Instrument kann mehr oder weniger leisten, ist aber unbekannt.
Lange Kurzrollen-Noten und Bassdyaden daher weder kürzen noch still umrouten.
LB+KB mit je einer Stimme ist physisch etwas anderes als zwei Stimmen auf LB.

`stichFixed/stichNote` erlauben eine feste Triggeradresse (Standard36). Deren
Tonhöhen-/Geräuschcharakter ist unbekannt. HE-ST 36 bleibt fest und untransponiert;
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
sind 57 Rhythmus-,24 Bass-,45 Motiv- und18 Phrasenquellen ausdrücklich X-unabhängig.
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
5. **Identifizierbare kurze Zelle und Modul mit Wiederholung/Unterbrechung/Rückkehr**,
   danach Kürzung und Verlängerung. Kontinuierliches Ostinato und phrasierte Wiederkehr
   unterscheiden. Ein begrenzter Plan für pulslose Einzelereignisse kann parallel
   nach dem Einzelpedal folgen; er braucht weder Polychorde noch vollständige Langform.
   Für alle drei künftigen Genres nutzbar, ohne universelle Formengine.
6. **Exakte Strukturverschiebung; danach zwei Komponenten mit Register-/Zeitplan.**
   Die Verschiebung einer einzelnen Zelle braucht keine Polychorde. Zunächst zwei
   geprüfte Komponentenzustände, kein umfassendes Orchestrierungsmodell. Instrumenten-
   Dauer-/Polyphoniegrenzen vor Polychord-Hörabnahme lösen.
7. **Triolen-/Hemiolen-Verbraucher** können als kleiner separater Daten-Schritt früher
   erfolgen. **Unabhängige Perioden** benötigen fortgeführte Phasen; nicht taktweise
   zurücksetzen. **Einfache Rollenwanderung** benötigt Materialidentität, geeignete
   Ziele und einen expliziten Übergabeplan; sie muss nicht auf Polychorde oder
   unabhängige Perioden warten. Details der Carpenter-Fortschreibung stehen unten.
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

## Carpenter: Quellenrang und musikalische Korrekturen

Die [erste Recherche](john-carpenter/STROMSCORE_John_Carpenter_Tiefenrecherche.md)
und die [Vertiefung](john-carpenter/STROMSCORE_John_Carpenter_Tiefenrecherche_Vertiefung.md)
sind vollständig archiviert. **Bei Widersprüchen hat die Vertiefung Vorrang.**
Ihre §§2/4/6/8 ersetzen insbesondere die frühen pauschalen Regeln:

- Harmonik umfasst nicht nur Quintleere und Halbtonreibung, sondern auch
  Mollakkordfolgen, diatonische Zirkulation, gehaltene Mehrklänge, schreitende tiefe
  Akkorde und Umfärbung einer gleichbleibenden Figur. Reiche Akkordfarben sind
  durch die Recherche nicht als Kern belegt; daraus folgt kein technisches Verbot.
- Kurze Zwei- bis Viertonzellen sind eine Sequencer-Präferenz, keine maximale
  Motivlänge. Längere Figuren, lyrische Linien und Drei-Linien-Satz bleiben zulässig.
- Pulslose Texturen und lange Leerräume sind für Hörspiel-Underscoring ebenso
  wichtig wie motorische Sequenzen. Keine obligatorischen LF/LB/AR/ST-Rollen.
- C♯–F♯ und C–F sind reine Quarten (fünf Halbtöne), keine Tritoni. Die bekannte
  Herzschlagfigur des *The Thing*-Hauptthemas stammt von Morricone; Carpenter/Howarth-
  Zusatzcues begründen vor allem Drones und Stinger. Zuschreibungen nicht vermischen.
- Die festen 8/16/32/64-Takt-Veränderungen der ersten Recherche sind durch
  alternative Entwicklungsstrategien ersetzt. Null Veränderungen bleiben möglich;
  ein gekoppelter Schichttausch darf zwei zusammengehörige Änderungen enthalten.

Diese Gewichtungen und Entwicklungsstrategien sind Forschungsableitungen, keine
neuen Laufzeitregeln. Die damalige korrigierte Recherche war noch keine kanonische Vorlagenbibliothek.
Die inzwischen vorliegenden405 IDs sind separat geprüft; offene Kontextfragen
bleiben ausdrücklich dokumentiert. Keine neuen
Profile, Template-IDs, Katalogeinträge oder Gewichte aus diesem Bericht ableiten.

## Carpenter: gemeinsamer Fähigkeitsabgleich

| Geforderte Fähigkeit | Tatsächlicher Ausgangspunkt im Code | Gemeinsame Lücke / Abhängigkeit und Nutzbarkeit |
|---|---|---|
| Unabhängige Pedaltöne | `ScoreEngine::pedalRoot()` nimmt den ersten Bassanker. `sustained()` setzt auch `BassPedal` bis `chordEndTime`; bei hoher Intensität kann `BassPedal` einen KB-Puls ergänzen. Explizite Slash-Bässe und lange Ziele sind vorhanden. | Kein vom Harmonieslot unabhängiger Lebensplan eines tiefen/hohen/inneren Tons. Für Carpenter lange Drones; für Herrmann Reibungs-/Innenpedale; für Williams Pedal unter beweglichem Material. Zunächst ein expliziter Ton mit Beginn/Ende, dann mehrere geeignete Ziele. Langes Halten muss nicht automatisch einen Puls aktivieren. |
| Eigenständige Basssequenzen | `RoleRhythmSource::intervals[3]` und `roleBassInterval` bieten begrenzte akkordrelative Folgen. `BassPhrase::planBassPhrase` erzeugt gezielte Linien in engem 4/4-Pop-Kontext; `ScoreEngine::melodicBassAllowed` begrenzt den Verbraucher. | Feste/relative Tonfolgen mit eigener Identität, Kontur, Register, Zeit und autorisierter Dissonanz fehlen als gemeinsame Quelle. Carpenter-Riff und Herrmann-Chromatik dürfen nicht ungefragt auf Akkordtöne korrigiert werden; Williams profitiert ebenso. Beide Follow-Zustände sind eine explizite fachliche Frage, kein Pedalersatz durch Follow AUS. |
| Repetitive Tonzelle mit Identität | `RememberedMotif`, `MotifCatalog` und `MotifUse`: tatsächlich ausgegebenes Material, unverändertes Original, unabhängige Verwendung. P3 und Pop-Hooks nutzen diesen Kern. | Kein frei beliebigen Begleitrollen zuweisbarer Zellplan. Acht Originalnoten und zwei Materialien/Szene sind bestehende Grenzen. Eine sechsnotige Zelle ist deshalb nicht grundsätzlich zu lang; Periode, Pausen und Rollenverbraucher separat prüfen. Kontinuierliches Ostinato darf keine aufgezwungene Score-Wiederkehrpause bekommen. Keine zweite Zellen-/Motivimplementierung. |
| Blocktransposition | `deriveMotif(...sequence...)` arbeitet mit den ersten zwei Noten und einer versetzten Zweitonwiederholung; normale Harmonierealisierung kann Tonhöhen anpassen. `VoiceLeading` minimiert Bewegungen. | Beides ist keine garantierte Transposition einer vollständigen Zelle oder eines Klangblocks. Benötigt werden expliziter Umfang der Verschiebung und Erhalt von Intervallen, Rhythmus, Akzenten, Gate und Materialreferenz. Bass/Pedal nur mitverschieben, wenn angefordert; sonst beabsichtigte Reibung prüfen. Für Carpenter und Herrmann zentral, auch für Williams nutzbar. Keine Polychorde als Voraussetzung für eine einzelne Zelle. |
| Schichtrotation | `TexturePolicy` bietet Aktivitätsschwellen/Hysterese, `ArpeggioPhrasePlan` begrenzte Figuren-/Pausenfenster; bestehende Rollenkoordination kann tatsächlichen Vordergrund schützen. | Kein geplanter Austausch zweier Begleitfunktionen bei weiterlaufendem Kernmaterial. Schichtanzahl ist nicht automatisch Dichte: mono KB und poly KF sind kein gleichwertiger Tausch. Gekoppelte Ein-/Austritte, Register, klingende Restnoten und geeignete Artikulation gemeinsam planen. Alle drei Künstler und spätere SYNTH-Profile profitieren. |
| Rollenwanderung | `MotifReferencePlan::adopt` erlaubt explizite Referenzübernahme mit unabhängigem Zustand. `planMelodyHandoff` bedient den engen HM→GS-Fall; GS→AR-Antwort ist ebenfalls vorhanden. | Ganze tatsächlich verwendete Zelle an ein anderes geeignetes Ziel übergeben, ohne Zufallsübernahme oder Fortschrittskopplung. Ein einzelner kontrollierter Rollenwechsel benötigt keine unabhängigen Perioden und keine Polychorde. Wiedererkennung vor/nach Übergabe, erlaubte Register und nicht konkurrierende Fenster nachweisen. |
| Pulslose Ereignisfelder | Gehaltene Flächen, sparsame Akzente sowie `tupfer`, `foreignTone`, `stich` existieren. Sie sind über metrische Fenster und Aktivität gesteuert; manche fremden Akzente entfallen bei geschützter Harmonik. `MusicalExecution` kann exakte Tick-Zeit ausführen. | Eine gehaltene Grundlage plus vorher festgelegte seltene Einzelereignisse/Leere ist nicht bloß ein abgeschaltetes Arpeggio oder globale Ausdünnung. Kleiner musikalischer Ereignisplan mit Identität, Typ, Zeitpunkt, Abstand und Tonabsicht; auch lange ohne neues Ereignis gültig. Für Herrmann, Carpenter und später Ambient/Vangelis nutzbar; kein neuer technischer Scheduler. |
| Mechanische / psychologische Unruhe | XYZ steuert heute Tempoauswahl, Figuren, Akzente und Fremdtöne; Ereignisdichte und Intensität sind bereits getrennt. Die geschützte harmonische Definition ist vorhanden, eine allgemeine F/U-Semantik noch nicht. | Mechanisch: regelmäßige prägnante Figur, stabile Referenz, ggf. Akzentasymmetrie. Psychologisch: lange Leere, Reibung, unerwarteter einzelner Einsatz, keine Pflicht auf hohe Dichte. Kontextabhängige musikalische Präferenzen statt zusätzlichem GUI-Regler oder pauschaler Z→Tempo-Kopplung. Keine freie Dissonanzquote. |
| Unabhängige rhythmische Perioden | Gemeinsame 64-Bit-Zeit mit 960 PPQ; `planRoleRhythm` ist zweitaktig/4/4, `BarryVocabulary::planBar` liest taktsynchrone Quellen. Separate Stimmenzustände sind kein Nachweis unabhängiger Phasen. | Eigene Periodenlänge/Phase im selben Host-Zeitbezug über Takt-/Akkordgrenzen erhalten, ohne neue Uhren oder Tempi. Für konkrete Herrmann-Vorlagen bereits begründet, für spätere SYNTH-Recherche relevant. Als Carpenter-Stilmerkmal weiterhin unbelegt, nicht aktivieren oder gewichten, bevor die kanonische Grundlage dies trägt. |
| Langfristige Entwicklung bei statischem XYZ | Motivwiederkehr, Szenenaufbau/-ende, wechselnde Quellwahl und Williams-Arp-Phrasierung sind vorhanden. | Kein allgemeiner musikalischer Strategieplan für Stasis, Schichtwechsel, Reharmonisierung oder Rückkehr derselben Textur. Fortschritt darf nicht nur von einer XYZ-Fahrt oder begrenzten Szene abhängen. Strategien gezielt und schrittweise erweitern; keine universelle Langform-/Orchestrierungsplattform. |

Der gemeinsame Kern bleibt instrumentenunabhängig. Neun vorhandene MIDI-Ziele sind
die derzeitige Ausgangsbasis, keine neun zwingend gleichzeitig aktiven Funktionen.
TU bleibt tonal nutzbar und wird nicht pauschal zur Rhythmusmaschine umgewidmet.
ST bleibt im festen Modus Trigger (Standard36), keine transponierbare Clusterstimme.
Tonale Stinger dürfen nur an dafür geeignete TU/KF-Spielweisen gehen; deren aktuelle
Dauer-/Polyphonieannahmen gelten weiterhin. Ein Klang, der Minuten hält, verlangt
auch einen tatsächlich dazu geeigneten Patch. Neue CC-Verläufe, Percussion oder
Ausgänge sind weder Voraussetzung dieser Analyse noch hiermit beschlossen.

### Gemeinsame Uhr ist nicht gemeinsame Periodenlänge

Die Vertiefung §5.2 beschreibt einen gemeinsamen Linn-/ARP-Takt und hält den
Nachweis von Phasenverschiebung offen. Diese Aussagen widersprechen sich technisch
nicht: Zwei Figuren können dieselbe Uhr und verschieden lange Perioden besitzen.
Aber weder ein 5/4-Thema noch Triolen beweisen eine unabhängige Periode. Triolen
können vollständig taktsynchron sein; 3+3+2+2 ist zunächst eine Akzentgruppierung.
Die Empfehlung der Recherche, daraus eine schwache Carpenter-Präferenz abzuleiten,
wird deshalb **nicht als gesicherte Regel oder neuer Default übernommen**.

Die bestehende Tick-Basis bildet bei 960 PPQ etwa Achteltriolen mit 320 Ticks exakt
ab. Das beseitigt nicht die Grenzen aktueller Sechzehntel-Vorlagenverbraucher.
Diese Verbraucher, eine unabhängige musikalische Phase und eine Humanisierung
relativ zum Referenzpuls sind drei getrennte Fragen. Der Host bleibt Tempoautorität;
keine neue Sequencer-Uhr, keine Swing- oder Scheduler-Überarbeitung auf Vorrat.

## Carpenter: acht Entwicklungsstrategien

Quelle: Vertiefung §7.2. **S1–S8 sind lokale Strategiebezeichnungen der Recherche,
keine Vorlagen-IDs, Laufzeittypen oder acht implementierte Betriebsarten.**
Alle sind dort E-Ableitungen aus unterschiedlich belastbaren N/I-Bezügen, keine
hier unabhängig nachgewiesene vollständige Kompositionsgrammatik.

| Strategie | Musikalische Absicht | Wiederverwendbarer Bestand / verbleibende Voraussetzung | Gemeinsame Nutzung und künftiger Nachweis |
|---|---|---|---|
| S1 **Stasis** | Material und Schichtung dürfen über lange Zeit gleich bleiben; keine erzwungene Entwicklung. | Gehaltene Klänge, Originalreprise und konstante Muster sind Teilbausteine. Wirklich unabhängige Haltelebensdauer und Schutz vor ungefragtem Materialwechsel fehlen. Velocity-Mikrovariation ist keine Pflicht und wirkt nur bei neuen Anschlägen. | Carpenter: Drone/Zelle; Herrmann: Klangobjekt; Williams: Spannungsfeld. Bei statischem XYZ auch 128 Takte ohne vorgeschriebene Steigerung, zusätzlichen Puls oder Wechsel prüfen; technische Note-offs bleiben korrekt. |
| S2 **Rotation** | Eine Schicht gegen eine andere tauschen, tragendes Material und ungefähres Aktivitätsniveau erhalten. | Schwellen/Hysterese und Rollenfenster reichen nicht für den gekoppelten Tausch. Zwei Änderungen können ein einziger musikalischer Entschluss sein; keine starre „nur eine Änderung“-Sperre. | Gemeinsamer Texturwechsel für alle Profile. Laufende Kernfigur, tatsächlich klingende Überlagerung, Artikulation und Energie vor/nach Tausch prüfen; nicht gleiche Rollenzahl als gleiche Dichte ausgeben. |
| S3 **Atmung** | Langsames Auftauchen/Zurücknehmen einzelner Schichten ohne obligatorischen Höhepunkt; langfristig im gleichen Bereich bleiben. | Szenenaufbau und End-Fade sind endliche Verläufe, keine autonome Texturatmung. Einsätze, Register und Gate können musikalische Annäherung/Entfernung tragen; sie ersetzen kein echtes stufenloses Fade eines gehaltenen Tons. | Alle drei Künstler, später Vangelis/Ambient. Notenbezogene Lesart gesondert hörprüfen. Ein echtes gehaltenes Fade ist ohne geeignete Klangsteuerung nicht zugesagt. Bestehende optionale Dynamics/Expression-CC sind kein neuer S3- oder Filterplan. |
| S4 **Wanderung** | Ein identischer Gedanke wechselt Rolle und/oder Register. | Gemeinsames Material und getrennte `MotifUse`-Zustände vorhanden; heutige Übergabe nur enger Spezialfall. Ganzen Gedanken explizit weiterreichen, geeignetes Ziel prüfen, Phase/Neuanfang begründet festlegen. | Carpenter-Motivtransfer, Herrmann-Zelle, Williams-Dialog. Intervalle/Rhythmus/Dauern und erkennbare Herkunft erhalten; keine unabsichtliche zweite Vordergrundstimme. Kein bloßer Instrumentenprogrammwechsel. |
| S5 **Umfärbung** | Figur bleibt erkennbar, der harmonische Unterbau ändert sich. | Harmonieplanung, lokale Quellmasken und adaptive Wiederkehr vorhanden. Gemeinsame Gültigkeitsintervalle und Schutz der Tonabsichten nötig, damit identische Figur nicht widersprüchlich korrigiert wird. | Besonders Verbindung zu Williams-Motivik und Herrmann-Pedalen. Figur vor/nach Unterbauwechsel und beabsichtigte A/T/V/F/U-Bezüge prüfen. Wenn eine echte unveränderte Figur nicht passt, den Wechsel ablehnen statt ihre Töne heimlich umzubauen. |
| S6 **Ereignisfeld** | Lange gehaltene Grundlage, seltene klar umrissene Ereignisse; auch gar kein neues Ereignis. | Bestehende Akzenterzeugung nur Teilbaustein. Eigene geplante Ereigniszeit/-art, Mindestabstand und autorisierte Tonbeziehung fehlen als zusammenhängendes Verfahren. | Carpenter/Fog/Thing-Zusatzcues, Herrmann-Spannung, spätere Ambient-Stile. Lange Leerräume und tatsächliche Ereignisfolgen messen, ohne Mindestquote; Stop/Seek/Loop dürfen keine Zusatzschläge oder hängenden Töne erzeugen. |
| S7 **Blockverschiebung** | Ganze ausgewählte Zelle oder Fläche exakt verschieben und ggf. zurückführen. | Sequenzvariation ist keine Ganzzellen-Blocktransposition. Umfang, Transpositionsvektor, Register und Beziehung zum verbleibenden Pedal planen. Quelle unverändert lassen. | Carpenter und Herrmann unmittelbar, Williams ebenfalls. Alle Intervalle, Einsatzabstände, Akzente und Dauern vergleichen; Grenzfall verwerfen statt Tonleiterkorrektur. Keine Oktav-/Stimmführungsänderung als exakte Transposition ausgeben. |
| S8 **Reduktion und Wiederaufnahme** | Zeitweise nur ein Element oder Leere, dann Rückkehr des vorherigen musikalischen Zusammenhangs. | Motivgedächtnis und Arp-Pausen vorhanden; keine vollständige Textur-/Modulreferenz für koordinierten Rückzug/Rückkehr. Bewusste Pause darf nicht das Material löschen. | Für alle drei Künstler und SYNTH. Rückkehr derselben Identität, bestimmter Wiedereinstieg (Neubeginn oder Fortsetzung), Rollenfenster und Schutz der Kernstimme nachweisen; keine zwangsläufige anschließende Eskalation. |

S1/S6 dürfen lange null Änderungen haben. S2 und ggf. S5 dürfen gekoppelte
Änderungen enthalten. Die Recherche nennt keine Verpflichtung, alle Strategien
rotierend abzuarbeiten. Eine Strategie kann dauerhaft passend bleiben; Mittelwert
und Ereignisarmut sind musikalische Ziele, keine festgelegten Aktivitätsquoten.
Profil- und vorlagenspezifische Präferenzen erst anhand kanonischer Daten bestimmen.

## Carpenter: begründete Fortschreibung des gemeinsamen Fahrplans

Die bisherige Reihenfolge bleibt im Kern sinnvoll. Die Ergänzung verschiebt den
Fokus von ausschließlich motorischen Modulen zu **zwei gleichwertigen Anwendungen**:
kontinuierliche Zelle und pulslose gehaltene Grundlage mit wenigen Ereignissen.
Keine neue Freigabe, kein eigenständiger Carpenter-Vorlagenplan.

1. **Williams P2/P3 hören; bestehende Abnahmen schützen.** Herrmann-Klärungen und
   begrenzter kompatibler HE-Import bleiben getrennte nächste Entscheidungen.
   Carpenter-Kanon ist nun archiviert: Gate-, Kontext- und Kombinationsfragen
   klären, bevor die entsprechenden Vorlagen importiert werden.
2. **Einzelpedal und autorisierte Bass-/Tonabsicht.** Eigene Lebensdauer und
   unabhängige Tonfolge bringen frühen gemeinsamen Nutzen. Kontinuierlich halten
   und periodisch neu anschlagen unterscheiden; neue Harmonie muss nicht das Pedal
   beenden. Erweiterte Akkordtypen/Skalen nur bei konkretem Bedarf, nicht als
   Voraussetzung eines reinen Einzeltonfelds.
3. **Materialidentität und begrenzte Einsatzpläne gemeinsam weiterverwenden.**
   Zunächst eine Zelle bzw. eine gehaltene Grundlage plus einzelnes geplantes
   Ereignis. S1/S6 müssen ohne Lead und ohne laufendes Arpeggio funktionieren;
   Fortsetzung im unbegrenzten Modus bei statischem XYZ prüfen. Kein neuer
   Universalplaner oder Ersatz des technischen Dispatchers.
4. **Exakte Blocktransposition einer einzelnen Struktur** kann vor aufwendiger
   Polychord-/Verschmelzungsplanung kommen. Gemeinsame Intervall-/Rhythmusidentität
   und harmonische Legitimation sind Voraussetzung; zwei Komponenten noch nicht.
5. **Expliziter Schichttausch, begrenzte Rollenwanderung und Rückkehr** bauen auf
   Materialreferenz, passenden Instrumenten und kontrollierten Einsätzen auf.
   Ein kleiner monodischer Transfer muss nicht auf unabhängige Zyklen warten.
   Danach Kürzung/Verlängerung und Umfärbung gezielt, nicht alle S1–S8 gleichzeitig.
6. **Komponenten-/Register-/Synchronitätspläne** bleiben für konkrete Herrmann- und
   Williams-Polychorde nötig. **Triolen/Akzentgruppen** können bei Bedarf unabhängig
   als kleiner Vorlagen-Verbraucherschritt folgen. **Eigene Perioden/Phasen** erst
   bei belegter konkreter Vorlage mit Tests über Akkord-/Taktgrenzen; kein
   Carpenter-Default und kein Zurücksetzen je Takt.
7. **Längere Bögen und komplexe Entwicklung** später; keine feste
   Steigerungs-Abbau-Kurve bei unverändertem XYZ. Echter kontinuierlicher
   Klangwandel bleibt eine getrennte, noch nicht beschlossene Frage.

Für jeden später freigegebenen Schritt: Produktions-MIDI unter statischem XYZ und
Fahrten, tatsächlich verwendetes Material, Rollenfenster, Gate/Dauer und Stille
prüfen; 12 Transpositionen, manuelle Spielweisen, Follow, Mute/Solo, Instrumenten-
Eignung, Determinismus, Seek/Loop und Live/Export einschließen. Alle erhaltenen
Rollen und Profile gezielt regressieren. Kein Dateizugriff/keine neue Allokation im
Audiothread. Testkriterien sind keine Behauptung bereits bestandener Implementierung.

### XYZ, Instrumentierung und weiterhin offene Grenzen

X bleibt dunkel–hell, nicht negativ–positiv. Die erweiterte harmonische Bandbreite
spricht gegen die frühe Verengung auf „X nicht Dur/Moll“: Harmoniequalität, Lage und
Kontext können gemeinsam Farbe tragen; daraus folgt noch keine neue X-Zuordnung. Y ist Energie/Gewicht, nicht automatisch Schichtzahl oder Notendichte.
Z kann regelmäßige mechanische oder ereignisarme psychologische Unruhe bedeuten.
Das sind interne musikalische Strategien, kein zusätzlicher Regler und keine
Beschädigung der bestehenden XYZ-Auswahl. Aus dunklen Forschungsankern dürfen auch
hier keine versteckten Sperren für färbungsunabhängige Figuren entstehen.

Die klare Registertrennung der Recherche ist als Underscoring-Ziel nützlich, aber
kein Auftrag für einen Dialogdetektor oder eine dauerhafte Mittellagensperre.
Die DAW meldet STROMSCORE aktuell nicht, wann jemand spricht. Sprache und geeignete
Register müssen praktisch gehört werden; die Orchestrierung bleibt frei.
Tempo kommt aus dem Host. Maschinenpuls/Handspiel ist nicht gleich globales
Swing oder zufälliger Jitter aller Rollen. Kein Humanisierungsumbau in diesem Schritt.

Die Forschung berichtet fehlende eigene Audioanalyse, nicht verfügbare Primärtexte
und teils widersprüchliche Crowd-Tonartangaben. Der nun mögliche kanonische Abgleich von Harmonien, Akzentfolgen, Zellperioden
und Instrumentenanforderungen steht im folgenden Abschnitt. Er ersetzt keine
Hörabnahme oder Kenntnis externer Patches. Das gilt auch für untertaktige Wechsel oder zusätzliche
Tonvorräte: jetzt keine Vorlagen vereinfachen oder vermeintliche Anforderungen erfinden.
Filter-/CC74-Rampen, elektronische Percussion und weitere MIDI-Ziele bleiben offen.
Vorhandene optionale Dynamics-/Expression-CC in `ScoreEngine::dynamicsCc` beweisen
keine allgemeine rollenunabhängige Klangbewegung: der aktuelle Verlauf ist
musikalisch gekoppelt und geteilter MIDI-Kanal bedeutet geteilte CC-Wirkung.
Keine automatische Echo-/Hall-Notenerzeugung aus Produktionsbeschreibungen ableiten.

## Carpenter-Kanon: technischer Abgleich bei `4937722`

Die [vier Originale](john-carpenter/README.md) umfassen405 IDs:88H/67R/67Q/52B/45M/
16P/16T/12EF/42S. Alle54 SMF-Dateien enthalten 16.046 Noten bei 960 PPQ und stimmen
Note für Note mit der CSV überein.21 Grundformen sind direkt darstellbar,87 benötigen
begrenzte Anbindung,288 mindestens eine gemeinsame Fähigkeit und9 eine konkrete
Klärung. Keine JC-Vorlage, kein Carpenter-Profil und kein SYNTH-Modus ist aktiviert.
Vollständige Gründe: [Einzelinventar](john-carpenter/TECHNICAL_INVENTORY.json).

### Was dadurch konkret wird

- **Eigene Pitchfolgen:** Die67 Q-Quellen sind eigenständige Tonobjekte. Auch eine
  Folge aus Akkordtönen darf nicht zu einem beliebig sortierten Arpeggio werden.
  Bestehendes tatsächlich gespieltes Motivmaterial und unabhängige Verwendungszustände
  weiterverwenden; Langsequenzen/Ein-Noten-Zellen und neue Rollenverbraucher sind
  reale Grenzen der aktuellen Acht-Noten-/Zwei-Materialien-Struktur.
- **Perioden:** Q028/Q054/Q063 bzw.B031/B052 benötigen zwei Takte, Q055 und mehrere
  Kriech-/Schreitbässe vierTakte. Q043 hat fünfTakte Gesamtzyklus bei 16 Anschlägen/Takt.
  Nicht auf den ersten Rhythmustakt kürzen. Alle119Q/B-Quellen und67R sind
  [zeitlich abgeglichen](john-carpenter/CYCLE_ANALYSIS.json). 10/6-Takt-Harmonien
  sind gerade, aber keine Zweierpotenzen; das ist ein Zyklusmodellproblem, kein
  Anlass für einen neuen Scheduler oder ein untertaktiges Zeitmodell.
- **Funktionen:** Alle237 V-Studiennoten besitzen ein tatsächliches schrittweises
  A-Ziel; alle 332 F/U-Noten eine Freigabe.62 T-Kennzeichnungen passen dagegen nur
  unter einer präzisierten lokalen Q/B/M-Kontexthierarchie, nicht allein zum
  H-Vorrat. Keine versteckte Vereinigung aller Modi und keine Tonkorrektur zur
  Statistikglättung. Gemeinsame Tonabsicht bleibt früh nötig.
- **Fähigkeiten:** Kürzeste Note48 Ticks gegen240 Ticks Modellminimum;64 Studien-/
  Ziel-Kombinationen in 38 IDs verletzen mindestens eine Dauer-/Polyphonieannahme.
  Der Emitter kann kurze Noten schon ausgeben, die Eignungsprüfung ist aber eine
  andere Frage. H067 hat fünf Stimmen, LF 6 reicht. Keine neuen Ausgänge nötig, nur
  weil ein beschreibender Mindestwert zu niedrig war. Keine stillen Kürzungen.
- **Stasis/Ereignisfeld:** Eigene Haltelebensdauer und geplante seltene Ereignisse
  bleiben frühe gemeinsame Aufgaben. Eine16-/64-Takt-Studie macht den derzeit
  akkordgebundenen Pedalverbraucher noch nicht unabhängig. Kein obligatorischer
  Puls/AR und kein Spannungsbogen bei unverändertem XYZ.
- **Rotation:** S35 spielt im PoolKB/AR/GS über vier 16-Takt-Blöcke2/2/1/2Rollen und
  256/192/128/192 Anschläge. Der beabsichtigte konstante Zwei-Schicht-Tausch wird
  nicht vollständig vorgeführt. Kein Algorithmus darf diesen Fehler als Stil
  übernehmen; Rollenzahl und musikalische Dichte auseinanderhalten.

### Gemeinsame Abhängigkeiten und nächste Reihenfolge

Die achtStrategien bleiben gemeinsam nutzbar, sind jetzt mit konkreten JC-Verfahren
verknüpft: S1→T012, S2→T007, S3→T016, S4→T006, S5→T008, S6→EF, S7→T001,
S8→T011/T014. Die [achtteilige Gegenüberstellung](john-carpenter/IMPLEMENTATION_PLAN.md)
dokumentiert die jeweilige Grenze. T016wirkt nur auf neue Anschläge; daraus folgt
kein CC-Fade. Schichtrotation, Materialwanderung und Umfärbung bleiben verschiedene
Entscheidungen. Perioden sind gemeinsame Fähigkeit, kein gesichertes Carpenter-Merkmal.

Nach Williams-Hörabnahme und den jeweils betroffenen Quellenklärungen:

1. Einzelpedal/Note-Lebensdauer und notwendige Tonabsicht für alle Profile.
2. Gehaltenes Feld plus einzelnes geplantes Ereignis als kleiner gemeinsamer Pfad;
   damit früh auch ohne HM/GS/AR eine musikalisch eigenständige spätereSYNTH-Probe.
3. Stabile vollständige Ton-/Bassfolge mit eigener Rhythmusphase und exakten Gates.
4. Nach konkret benötigtem Material harmonische Zykluslängen, Klangobjekte und
   lokale Vorräte ergänzen; nicht erst nach Import fehlende F/U-Bezüge reparieren.
5. Einzelne Blockverschiebung, Übergabe oder gekoppelte Rotation; danach komplexere
   Strategien, Polychordkomponenten und Langphrasen. Keine zweite Engine.

Die27XYZ-Zellen sind formal mit H/B versorgt, neun ohne eigeneStudie. Paarprüfungen
über ganze Harmonie-/Figurzyklen zeigen zusätzliche Engstellen: In vier Zellen
sind vorhandeneQ bei strikterVererbung ihres R-Gültigkeitsbereichs unerreichbar.
Diese Vererbungsfrage bleibt offen, Bereiche werden nicht ausgeweitet. Insgesamt
sechs Zellen haben unter dieser Lesart kein kompatiblesQ/H/R-Paar. Das ist kein
pauschaler Musikmangel: pulslose und melodielose Pläne sind gültig, aber ein
Bassverzicht oder Einzelkandidat beweist noch keine ausreichende musikalische Vielfalt.
[XYZ-/Kombinationsbericht](john-carpenter/XYZ_COMPATIBILITY.json) trennt formal
geeignete Paare, tatsächliche Referenzstudien, Instrumentenbereitschaft und Hörqualität.
Eine globale XYZ-Umstellung oder Gewichtung wird daraus nicht abgeleitet.

Korrekturen/Unsicherheiten, inklusive R022/R038–040/R046, S35und nicht vollständig
gespeicherter Schlussstille in S04/S33: [ERRATA.md](john-carpenter/ERRATA.md).
Registertrennung bleibt nach Anwenderentscheidung Präferenz, keine zwingende
Freihaltung der Mitte. Der User-Schalter Follow wird nicht aus einem Quellwort
„eigenständig“ automatisch überschrieben. TU bleibt tonal, ST fest 36. CC, elektronische
Percussion und zusätzliche Ausgänge sind weiter nicht beschlossen. Keine musikalische
Verhaltensänderung in diesem Dokumentationsstand.


## Morricone: Übergangsabsichten früh hörbar machen (27.11.2026)

Die [kanonische Morricone-Bibliothek](ennio-morricone/README.md) ergänzt534IDs und
73Studien/9752Noten. Die [vollständige Bestandsaufnahme](ennio-morricone/TECHNICAL_INVENTORY.md)
bezieht sich auf den unveränderten Kern `4c43bd2` einschließlich des ersten
unabhängigen Einzelpedals. Originale bleiben unverändert, Morricone ist nicht
aktiviert. Persönliche Priorität: **Lolita / Love in the Morning und The Untouchables**.
Ein Profil umfasst Lyrik, Spannung und Experiment; keine zusätzliche Betriebsart
oder Säulen-Auswahl und keine vorgeschriebenen Instrumente.

### Gemeinsam nötig, stilistisch unterschiedlich gewichtet

| Gemeinsame Fähigkeit | Vorhandener Anknüpfungspunkt | Fehlende Bedeutung / gemeinsamer Nutzen |
|---|---|---|
| Harmonieübergangsabsicht und Pflicht-Gemeinsamtöne | `ResolutionIntent/TransitionIntent`, `planHarmony/leadEntry`, Beam-Stimmführung mit Gemeinsamtonkosten | Konkrete klingende Oberstimme muss bleiben dürfen/müssen; Quell-/Zielharmonie und Rollenwechsel9→3→7 als Daten. Morricone lyrisch, Herrmann Spannung/Stasis, Williams warme/monumentale Felder, Carpenter ruhige Schichten. Keine neue Harmonieengine. |
| Gebundener Notenbesitz | `Active`-Ansprüche, `padChord::extendOnly`, neuer `PedalPlan` | Reale Tonhöhe, Stimme, Dauer und Funktion über mehrere Harmonien; Basspedal ist kein automatisch beliebiges hohes/inneres Pedal. Bestehende Claim-Liste erweitern, nicht duplizieren. |
| Vorhalt mit Zielzeit / bewusst ohne Ziel | Lokale Linien-Vorhalte und kontrollierter Durchgang, kein allgemeiner Pad-Vorhalt | Temporär klingender Ton, Zielton und Zielzeit getrennt vom neuen Akkord. Aufgeschobene Auflösung eignet sich unmittelbar für leise Mystery; nicht bloß Wahrscheinlichkeiten von V–I erhöhen. |
| Gestaffelte Akkordeinsätze | Bestehender Tick-Dispatcher, gleichzeitige `padChord`-Ausgabe | Einzelne Stimmen einsetzen/ablösen, Klangidentität erhalten. Morricone-Atmung, Williams-/Herrmann-Schichtaufbau und spätere SYNTH-Felder. Kein neuer Zeitscheduler. |
| Geschützte Zellen | Unveränderliche Motivmaterialien und Varianten, aber geordnete Motividentität | MENGE, KLASSE, ORD, RHY und KERN unterscheiden; Permutation, zulässige Inversion/Rotation und Farbtonaustausch sind verschiedene Operationen. Kein Akkordton-Snapping geschützter Mengen. Für Morricone, Herrmann und Carpenter gemeinsam. |
| Lokale/globale Tonabsichten | Akkord-/Vorratsmitgliedschaft, Quellenmasken, Pedalberechtigungen | Noch kein allgemeines A/T/V/F/U pro Ton und Zeitraum. Konsonante Schicht kann gegen andere Harmonik dissonant bleiben; D-Schicht wird nicht pauschal „korrigiert“. Polychordkomponenten dürfen nicht verschwinden. |
| Explizite Ton-/Rhythmuszyklen | 960PPQ, vorhandene Rhythmus-/Bassbausteine, begrenzte Autorenformate | Autonome Phasen, Triplet-/ametrische Daten und vollständiges kgV. Zeitauflösung allein führt keine beliebige Vorlage aus. Carpenter-Sequenzen, Herrmann-Module und Morricone-Polyperiodik benötigen denselben Verbraucher. |
| Module und längere Entwicklung | Motivwiederkehr, wenige Antwortfenster, Arp-Phrasierung | Mehrfachkompatibilität statt paarweiser Freigabe; eigene Perioden/Lifetimes, additive Enthüllung, gezielte Kopfverkürzung, Reduktion und Wiederaufnahme. Keine obligatorische Lead-, Puls- oder Ankerschicht. |
| Pulslose Antwortfelder | Vorhandene Pausen, Rollen-/Antwortfenster und Akzentgenerator | Unregelmäßige Ereignisse, Mindestabstände, explizite Imitation/Widerspruch/Schweigen; keine als Feld umbenannte Folge zufälliger Akzente. |

**Kein Neubau der Stimmführung:** Im Offline-Probe708U-Grenztranspositionen bleiben
alle Ziel-PCs erhalten. U040 verliert aber in zwei Fällen den zwingend gehaltenen
konkreten C-Ton zugunsten eines anderen C-Registers. Soft-Präferenz ist keine
harte Bindung; hier liegt eine kleine präzise Ausbaustelle. Die existierende
Langflächen-Notenverlängerung kann weiterverwendet werden.

**Keine globale „harmonische Glättung“:** Die Referenzstudien S016/S044 verändern
C010s Zellklasse bzw. reduzieren vier auf drei Tonklassen. Das darf kein Vorbild
für einen geschützten Zellverbraucher sein. C026s erlaubter Farbtonaustausch und
C035s TnI-äquivalente Normalformkonvention sind andere Sachverhalte.

**Kompatibilität ist mehr als Zählen:** 16.280formale H/B/C/M-Paare und8436
Moduldreiergruppen wurden untersucht. Es gibt Instrumenten-/Gatekonflikte,
auseinanderfallende Quellbereiche und gerichtete Kompatibilitätsangaben.
644Dreiergruppen passieren einen strengen Vorfilter, keine ist damit vollständig
musikalisch/instrumental zertifiziert. Tonhöhen oder Zyklen werden nicht verändert,
um diese Zahl zu erhöhen. Die32H-Vorlagen ohne vollständigen
bestehenden Typvertrag werden nicht durch ähnlich benannte Akkorde ersetzt.

### Fortschreibung der gemeinsamen Reihenfolge

Die älteren Listen oben bleiben historische Planungsstände. Unter Berücksichtigung
der inzwischen positiven Williams-P2/P3-Abnahme und des implementierten, separat
in Hörabnahme befindlichen Pedalkerns gilt als neue Empfehlung:

1. Quellenklärungen gezielt erledigen; keine Änderung der laufenden Hörreferenz.
2. **Früh zwei klar begrenzte lyrische U-Übergänge (U001/U002)** mit harten
   Oberstimmenbindungen im bestehenden Solver/Pad-Claim-Pfad. Ohne HM/GS/AR
   hörbar; ungeeignete Startlage/Register ablehnen. Registerangepasste Ableitungen
   nicht als identische kanonische U-Lagen deklarieren.
3. Danach ein Vorhalt mit exaktem Zielzeitpunkt, anschließend ein gestaffelter
   Einsatz. Jeder Teil separat musikalisch und technisch prüfen.
4. Quellengetreue Einzelpedalbindungen, dann eine eigenständige Bassfolge und
   geschützte Zellidentität. Kein komplettes Formsystem als Voraussetzung.
5. Tickgenaue Autorenereignisse/Phasen, nötige Tonvorräte/Klangobjekte und lokale
   Schichten nach konkretem Material. Kein pauschaler Wunschlistenimport.
6. Kleine nachweislich kompatible Mehrfachmodule, danach Rollenwanderung,
   additive Enthüllung/Kopfverkürzung und pulslose Antwortlogik; lange Themen-
   /Gegenmotiventwicklung erst bei vollständig erhaltenem Material.

So verdrängt die experimentelle Bibliothek die lyrische Übergangsgrammatik nicht.
Die persönlichen Morricone-Referenzen liefern Präferenzen, keine starren Verbote.
Die bestehende globale XYZ-Steuerung bleibt: „beliebig“ bei R/B/C braucht später
passende dimensionenbezogene Auswahl, nicht einen erfundenen dunklen X-Anker.
An Grenzpositionen sind ein Kandidat oder eine leere M-Rolle weder Vielfaltbeweis
noch Funktionsfehler. Keine automatische Eskalation bei statischem XYZ.

[Morricone-Plan mit Tests und Unsicherheiten](ennio-morricone/IMPLEMENTATION_PLAN.md),
[Errata](ennio-morricone/ERRATA.md), [XYZ-Prüfung](ennio-morricone/XYZ_COMPATIBILITY.json).
Sämtliche vier Künstler und zukünftige SYNTH-Profile verwenden denselben Kern.
Keine GUI-/MIDI-Erweiterung, keine Engine-Änderung in diesem Archivierungsauftrag.

## Umgesetzt: gemeinsame Übergangsgrammatik P1 und Morricone-Prototyp

Nach dem Bestandsabgleich `3227315` wurde ein begrenzter erster Verbraucher
implementiert; Details und Hörgrenzen: [Morricone P1](ennio-morricone/P1.md).

- Gemeinsame typisierte Pflichtbindungen physischer Tonhöhen und optionale
  Gemeinsamton-Präferenzen im vorhandenen Stimmführungs-/Harmonieplan.
- Validierte geschützte Quelllagen mit expliziten Bindungen; keine automatische
  Tonklassenrundung und kein Ersatz einer gehaltenen Note durch ihre andere Oktave.
- Reale Durchbindung über den bestehenden Notenbesitz der Langfläche; bestehende
  unabhängige Basspedale behalten ihren gesonderten musikalischen Lebensbereich.
- Erster hörbarer Morricone-SCORE-Pool mit 14 achtaktigen lyrischen H-Folgen,
  einschließlich H051 als gültigem Teil der S052-Orientierung. Keine Aktivierung
  ungeklärter H053 oder pauschaler Import aller U-Vorlagen.

Die Fähigkeit ist gemeinsam nutzbar; die konkrete H-Auswahl ist eine Stilpräferenz.
Verzögerte Vorhaltsauflösungen, gestaffelte Einsätze und lokale Harmonieschichten
bleiben eigenständige Folgeaufgaben. Die frühere Bestandsaufnahme wird dadurch
nicht rückwirkend als bereits damals implementiert ausgegeben. Zunächst ist die
musikalische Studio-One-Hörabnahme dieses P1-Standes vorgesehen.

## Carpenter P1 – gemeinsame Figurenstrategie

Die verbindliche Architekturentscheidung ist inzwischen Variante C: ein Kern,
individuelle Profile, optionale Oberflächensammlungen, Instrumentierung in der DAW.
Ein kompletter Genre-Umbau wurde nicht vorgezogen. POP/ROCK mit 39 Wendungen bleibt
unverändert. Details und Grenzen im [P1-Bericht](john-carpenter/P1.md).

Neu gemeinsam darstellbar sind vollständige geordnete Ton-/Rhythmuszyklen mit
unabhängigen Verwendungen, Bass-Sequenz neben gehaltenem Pedal, GS als geeignete
Begleitsequenz, quellautorisierte Blocktransposition sowie begrenzte zyklische
Schichtung. Datenansichten in der Profil-Policy aktivieren denselben Adapter;
keine eigene elektronische Engine und keine neue technische Clock.

Die neue musikalische Nutzung ist zunächst Carpenter/4/4 vorbehalten. Allgemeine
Rollenwanderung, Polychorde, beliebige Ereignisfelder und vollständige Langformen
bleiben separate gemeinsame Folgefähigkeiten. Die Herrmann-/Williams-/Morricone-
Originalrecherchen werden dadurch nicht pauschal als implementiert ausgegeben.
Morricone P1 und Williams P2/P3 sind positiv vom Anwender gehört; Carpenter P1
wartet nach der technischen Auslieferung auf die musikalische Abnahme.


## Herrmann-Planung nach Carpenter P1 (28.11.2026, `58ea29d`)

Der [aktualisierte Herrmann-Plan](bernard-herrmann/IMPLEMENTATION_PLAN.md) gleicht
alle343 historischen Einstufungen mit dem aktuellen Kern ab. Die frühen Tabellen
dieses Berichts sind historische Befunde; ihre pauschalen Lücken „keine geordneten
Basssequenzen/keine unabhängigen Perioden/keine verbindlichen Oberstimmen“ gelten
in dieser Form nicht mehr. Der aktuelle Katalog enthält225 Vorlagen/27 Typen.
Williams P2/P3 und Morricone P1 sind musikalisch positiv gehört; Carpenter P1
wartet auf die Anwenderabnahme.

Unmittelbar wiederverwenden: `PedalPlan` samt Notenbesitz, `HarmonyVoicing/held`,
notierte exakte Parallel-Lagen, `SequenceSource/SequenceUse`, unabhängige KB/AR/GS-
Verwendungen und gemeinsames Motivmaterial mit eigenem Stimmenzustand. Daraus
folgt noch kein fertiger Herrmann-Verbraucher: tiefe Pedalquellen sind tonikagebunden,
Sequenz-F/U-Freigaben eng, der neue Adapter4/4- und rollenbegrenzt. KF/TU besitzen
nicht automatisch lange Gates; GS-Begleitung ist keine Rollenwanderung.

Empfohlen wird ein gemeinsames umfangreiches Paket Klangobjekte/Pedale/kurze
Module statt vieler Zwischenprototypen. Sein Kandidatenrahmen umfasst47 H-,28 R-,
18 B- und22 M-Grundformen; Kontext-/Instrumentprüfung kann Quellen zurückstellen.
Ein kleiner quellenbezogener A/T/V/F/U-Vertrag und geeignete LB-Linien-/Mehrrollen-
Verbraucher gehören dazu. Bestehende Funktionen erweitern, keine Herrmann-Engine.

Danach zweikomponentige Harmonik mit eigener Identität, Tonbezug, Register und
Synchronität. Hohe/fremde/mehrfache Pedale, Ganzton/Hexatonik, echte pulslose
Ereignisfelder, vollständige Moduloperationen, Rollenwanderung und lange Formen
bleiben gemeinsame Aufgaben auch für Williams, Morricone und SYNTH. Die
Carpenter-Schichtung ist keine vollständige Herrmann-Modulgrammatik; zwei
Sequencer sind keine Polychorde. Keine neue Uhr und keine vorsorglichen Ausgänge.
Die globale XYZ-Auswahl bleibt erhalten; ausdrücklich X-unabhängige Figurendaten
werden lokal nach Y/Z geprüft. Diese Fortschreibung implementiert nichts.

## Implementierungsfortschritt Herrmann P1 – 28.11.2026

Gemeinsame quellenbezogene Tonabsichten und Rollenfiguren, getrennte harmonische Komponenten, begrenzte Verschmelzung sowie tiefe/hohe Pedale sind nun tatsächlich angebunden. [P1-Bericht](bernard-herrmann/P1.md) unterscheidet Datenregistrierung und Produktionsnachweise. Die neuen Verbraucher bleiben profilgesteuert; andere Profile sind bytegleich geprüft.

Keine allgemeine Polychord-/Ereignisfeld-Plattform: zwei Dreiklangskomponenten, gehaltene LF-Verschmelzung, geprüfte Registerstufen und ein tiefer/hoher Pedalfall bilden die begrenzte erste Teilmenge. Freie Ereignisfelder, beliebige Komponentenperioden, Ganzton/Hexatonik und lange P-/S-/T-Verläufe bleiben offen. Optionale rollenbezogene MIDI-CC-Klangmodulation ist als zukünftige gemeinsame Fähigkeit vorgemerkt, nicht implementiert. Die Herrmann-Hörabnahme steht aus.

## Dark Synth P2: gemeinsame Erweiterungen auf Basis eb32983

Das bisherige Carpenter-Profil wird als **Dark Synth** weitergeführt; es gibt kein zusätzliches Carpenter-Unterprofil. Die 405 JC-IDs bleiben Grundlage, die 236 DS-IDs sind in `dark-synth/` unverändert archiviert. Action Synth und Space Synth bleiben spätere Profile. Instrumentierung und bestehende neun MIDI-Ziele bleiben davon unabhängig.

Der gemeinsame Harmonie-Datenpfad unterstützt nun ausdrücklich deklarierte ganzzahlige Perioden statt der bisherigen impliziten Acht-Takt-Annahme. Die statische Slot-Kapazität folgt den validierten Katalogdaten; die acht manuellen Akkordplätze der Bedienung bleiben erhalten. Eine Harmonieperiode und eine melodische Phrase müssen nicht gleich lang sein. Ein Wiedereinstieg vom gehaltenen Akkord kann die vollständige geordnete Harmonieperiode rotieren, ohne den letzten Akkord auf die Restperiode zu dehnen.

Gemeinsame Figurenfähigkeiten: vollständige Ton-/Rhythmuszyklen, quellenbezogene Tonabsichten mit geprüfter V-Auflösung, Platzierung einer vollständigen Figur um ganze Oktaven, begrenzte Gate-Atmung und Einzel-Schritt-Mutation sowie ein autorisierter Halteton derselben Sequencer-Rolle. TU verwendet einen dritten unabhängigen Stimmenzustand im bestehenden unveränderlichen Motivkatalog. Explizite endliche Rollenpläne können reale AR-/GS-Noten beantworten und belegte TU-Keime in eine optionale HM-Endgestalt überführen. Ein unabhängiger Choral wird nicht als Ableitung eines fremden Keims ausgegeben.

Diese Fähigkeiten werden in diesem Paket ausschließlich im erweiterten Dark-Synth-Profil musikalisch aktiviert. Andere Profile werden durch MIDI-Regressionen abgesichert. Elektronische CC-Klangmodulation, Pitch-Bend und allgemeine Übergaben zwischen beliebigen Rollen sind nicht enthalten. Grenzen, tatsächlich gehörte Quellen und zurückgestellte Vorlagen: `dark-synth/P2.md` und `dark-synth/P2_IMPLEMENTED_IDS.md`.
