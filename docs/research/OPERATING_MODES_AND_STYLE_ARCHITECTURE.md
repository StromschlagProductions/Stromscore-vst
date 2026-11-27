# Betriebsmodi und zukünftige Stilarchitektur

Stand: 27.11.2026 · `develop/composition-core-prototype`, Quellcode `44d2404`.
Ausschließlich Bestandsaufnahme und Empfehlung. Keine Änderung an Engine, GUI,
Katalogen oder musikalischem Verhalten. Keine erneute musikalische Hörabnahme.

## 1. Empfehlung

**Ein gemeinsamer Kompositionskern mit individuellen Stilprofilen; Stilfamilien
nur als Orientierung in der Oberfläche (Variante C).** Die musikalischen
Strategien gehören zum ausgewählten Profil, nicht zur Instrumentenfamilie.

POP/ROCK sollte als eigenständige, weiterhin auswählbare musikalische Persönlichkeit
etwa „80er Pop/Rock – Mix“ erhalten bleiben: mit seinem gesamten geeigneten
Vokabular und seinen heutigen Hook-, Bass- und Begleitverfahren. Es kann in einer
Filmmusik-Sammlung erscheinen, darf dafür aber nicht einfach den heutigen
`GenreScore`-Ausführungspfad erhalten. Dabei gingen musikalische Eigenschaften verloren.

Für Carpenter sind weder eine zweite Engine noch zuerst ein vollständiger
Genre-Umbau erforderlich. Benötigt werden gezielte gemeinsame Fähigkeiten für
lang lebendes Material und eigenständig fortlaufende Figuren. Eine zusätzliche
SYNTH-Schaltfläche allein liefert diese Fähigkeiten nicht. Umgekehrt sollte die
erste Carpenter-Implementierung nicht auf eine vollständige Umstellung aller
vorhandenen Genre-Abfragen warten müssen.

Die frühere Entscheidung für SCORE/SYNTH/POP/ROCK ist damit Gegenstand einer
begründeten Änderungsempfehlung, noch keine bereits umgesetzte Projektentscheidung.
Die Begriffe können als Sammlungen erhalten bleiben, ohne drei technische
Kompositionswelten festzuschreiben. **ORCHESTRAL/ELECTRONIC als verbindliche
musikalische Einteilung wird nicht empfohlen.** Sie vermischt Instrumentierung
mit Arbeitsweise und passt gerade zum ausdrücklich orchestral verwendeten
Pop/Rock-Material schlecht.

## 2. Was tatsächlich vorhanden ist

### Ein Kern, zwei stark wirksame Genre-Kontexte

Es gibt einen `Generator`, eine gemeinsame Tick-Zeitbasis mit 960 PPQ, einen
Dispatcher und eine MIDI-Notenverwaltung. `Genre` hat derzeit nur `GenreScore`
und `GenrePopRock`; SYNTH ist dokumentierte Zukunft, kein dritter Laufzeitmodus.

Gemeinsam sind unter anderem Harmonie-Datenpfad, stabile IDs, Transposition,
XYZ-Auswahlformel, Grund-Stimmführung, Instrumenten-Fähigkeitsmodell, sechs
Bediengruppen, neun Ausgabeziele, Transport, Swing-Ausführung, Mute/Solo,
Ereignisdichte, Szenenaufbau/-ende sowie wesentliche Motivdaten und Transformationen.

Der Genre-Wert bestimmt dennoch erheblich mehr als einen Katalogfilter:
Auswahlpool, verfügbare Strategie-Verbraucher, Hook-Verhalten, Linienplanung,
Antwortplanung und einzelne Register-/Akzent-/Dynamikentscheidungen. Es gibt
**keine zwei vollständig separaten Engines**, aber auch **keinen bereits
vollständig profilgesteuerten musikalischen Ablauf**.

Aktuelle Daten: 195 eindeutige Harmonievorlagen. Neutral SCORE verwendet 48,
POP/ROCK **39 statt der ursprünglichen 36**. Barry besitzt eine Auswahlansicht mit
46, Williams mit 49 und Morricone mit 14 Vorlagen; Ansichten sind nicht mit
zusätzlichen eindeutigen Datenkopien gleichzusetzen. Herrmann nutzt derzeit den
neutralen Score-Bestand mit seinen Auswahlpräferenzen. Carpenter und Wang Chung
sind noch keine auswählbaren Profile.

### Konkrete musikalische Unterschiede

| Bereich | SCORE heute | POP/ROCK heute | Bewertung |
|---|---|---|---|
| Harmonieauswahl | Profilabhängige Auswahlansicht; Barry-/Williams-/Morricone-Material erreichbar | Gemeinsamer Pool 2001–2039, unabhängig von der gewählten Profilidentität | Getrennte Vokabulare sinnvoll; Genre als alleinige Zuständigkeit historisch |
| Policy-Anschluss | `policyForContext` übernimmt die jeweilige Profil-Policy | Derselbe Aufruf liefert immer `neutralFreePolicy` | Hindert ein künftiges eigenständiges Wang-/Carpenter-Profil; kein musikalisches Naturgesetz |
| XYZ/Variety | Gemeinsame Distanz, Kandidatenschwelle, deterministische Ziehung | Derselbe Algorithmus | Beibehalten; unterschiedliche Daten/Strategien genügen, kein neues XYZ-Feld nötig |
| Bassmuster | Gemeinsame Muster plus profilabhängige Autorenrhythmen und Williams-Pedal | Gemeinsame Muster; zusätzliche melodische Bassphrasen über geeignete Akkordpaare | Pop-Verfahren auch für Filmmusik und Synth brauchbar; nicht auf Instrumente beschränkt |
| Rhythmische Verzahnung | Motiv-/Auto-Arp-Reservierung, Score-Antwortfenster; Autorenrhythmen | Zusätzlich Bass als Referenz für komplementäres Auto-Arp | Gemeinsam nutzbare Fähigkeit mit kontextbezogener Eignung, keine notwendige Genre-Grenze |
| Akkordbesetzung | Grund-Stimmführung, Score-Übergangsgeschichte; inzwischen explizite Quelllagen/Gemeinsamtöne | Zusätzlich automatische volle/offene/reduzierte Besetzung mit Bassberücksichtigung | Unterschiedliche Verfahren, nicht „Orchester dicht, Pop dünn“; mittelfristig nach musikalischem Bedarf freigeben |
| GS-Material | Motiv-/freie Linie, Zielton-/Atempausenplanung | Neun explizite Hook-Typen bzw. ältere kurze Gradfiguren, Aufnahme tatsächlicher MIDI-Ausgabe | Verschiedene musikalische Strategien sind sinnvoll; nicht zwei Motivspeicher-Implementierungen |
| Hauptmelodie | Optional, eigener Motiv-/Legatozustand | Heute ebenfalls optional funktionsfähig, mit Pop-Einsatzfenstern | Die frühere Aussage „Pop kann keine Hauptmelodie“ ist überholt |
| Wiederkehr | Gemeinsamer Motivkern, frühe Reprise und harmonisch flexible Score-Realisierung | Gemeinsamer Kern; eigene Hook-Policy unterscheidet motorische/phrasiert-melodische Figuren | Gleiche Materialarchitektur, absichtlich unterschiedliche Verwendungsregeln |
| Frage–Antwort | HM→GS-Schlussfigur und GS→AR in begrenzten geeigneten Kontexten | Rollenwechsel/Überlappungsschutz, aber keine gleichwertig aktivierte HM→GS-Zitatübergabe | Gemeinsame Koordination ist noch nicht überall derselbe Verbraucher |
| Auto-Arp-Phrasierung | Aktuell nur Williams, Auto/Auto und 4/4 | Nicht aktiviert | Bereits gemeinsame Funktion; spätere kontinuierliche Sequenz darf nicht automatisch deren Pausenpflicht erben |
| Einstieg, Register, Akzente, CC | Score-Präferenzen | Andere Eintrittspräferenzen, höherer TU-Bereich, zusätzliche ST-Offbeats, etwas andere CC-Modulation | Musikalische Präferenzen; historisch am Genre festgemacht, nicht an zwingende Instrumentenfähigkeiten |

`harmonicPreference` ist selbst nicht grundsätzlich auf SCORE beschränkt. Im
aktuellen Datenbestand existieren aber keine wirksamen Barry-/Herrmann-/Williams-
Sondergewichte für den Pop-Pool. Die Kombination aus gleichem Pop-Pool und neutraler
Kontext-Policy macht eine dort gewählte Künstleridentität derzeit nicht zu einem
entsprechenden Pop-Künstlerprofil. Eine sichtbare Identität garantiert noch keinen
angeschlossenen musikalischen Strategiepfad.

### XYZ, Phrasen und musikalische Entwicklung

Die aktuelle harmonische Auswahl benutzt
`exp(-(dx² + (0,7·dy)² + (0,8·dz)²)/0,05)` und eine Variety-abhängige relative
Kandidatenschwelle `1−0,85·Variety`. Künstlerpräferenzen wirken innerhalb der
zulässigen Auswahl. Ein anderes Profil braucht dafür keinen anderen Koordinatenraum.

Die Harmonieprojektion arbeitet weiterhin mit acht Takten und höchstens acht
Slots, deren Dauern ganze Takte sind. Fein aufgelöste Tick-Zeit bedeutet nicht,
dass beliebige Harmonieperioden oder halb-/untertaktige Vorlagen bereits importierbar
sind. Phrase, Auswahlzeitpunkt, Motivverwendung und rhythmische Phase sind
unterschiedliche Sachverhalte, heute aber stellenweise noch miteinander verbunden.

X/Y/Z sind keine bloßen Stimmungsetiketten: Sie beeinflussen auch Lage,
Intensitätsausdruck, Muster, Aktivität, Unruhe und bei flexibler Harmonik deren
Färbung. Beispielsweise erzwingt `rawBassPattern` bei sehr hoher Intensität
gewöhnlich Achtel, und `playArpeggio` bezieht seinen Figurenanker auf Akkord- oder
Phrasenanfang. Das passt zu bisherigen Strategien, aber nicht ungeprüft zu einem
unabhängig weiterlaufenden Drone bzw. einer eigenen Sequencer-Tonfolge.

Für Carpenter muss daher eine Strategie bei hoher Intensität auch Stasis oder
Reduktion wählen können. Das ist keine globale Abschaffung der bisherigen
Intensitätswirkung und erfordert keine Veränderung der akzeptierten Profile.

## 3. Was POP/ROCK musikalisch enthält

### Harmonik und nachweisbare Künstlerbezüge

Der aktive Pool umfasst 2001–2036 sowie die geschützten Wang-Chung-Konstruktionen
2037/WC-H01, 2038/WC-H11 und 2039/WC-H19. Alle aktuellen Pop-Vorlagen umfassen acht
Takte. Sie enthalten Moll-/Durfolgen, bVII–IV-Beziehungen, Power-/Quintklänge,
Sus-/Add-Farben, Sept-/Nonenakkorde, Slash-Bässe, chromatische Nachbarn und
Binnenlinien; also deutlich mehr als eine Rockband-Grundharmonik.

Im Pool kommen 15 Akkordtypen vor: `Maj`, `Min`, `Maj7`, `Min7`, `Dom7`, `Fifth`,
`Min9`, `Sus4`, `Dim7`, `Add9`, `HalfDim`, `Dom7b9`, `MinMaj7`, `Min6`, `Sus2`.
36 Vorlagen behalten flexible Färbung; nur die drei späteren Wang-Importe haben
hier ausdrücklich geschützte Färbung. Explizite Basstonvorgaben stehen in 2018,
2030–2032, 2036–2039. 2032 besitzt außerdem einen speziellen Erhalt seiner
charakteristischen chromatischen Akkordlage; es ist trotzdem kein pauschal
färbungsgeschützter neuer Datensatz.

| Vorlagen | Tatsächlich dokumentierter Bezug, keine exklusive Künstlerzuordnung |
|---|---|
| 2001 | Carpenter / kalte New Wave als älterer Hinweis, keine implementierte Carpenter-Grammatik |
| 2002, 2003, 2007, 2014, 2015; 2028–2030 | Wang Chung, New Wave, *To Live and Die in L.A.*, Album-/Tanz- und untersuchte Hook-Konstruktionen |
| 2004 | Dixon/Stein, Sequencer-Pop |
| 2005 | Jan Hammer |
| 2006, 2008; 2033, 2034 | Frankie Goes to Hollywood / Trevor Horn |
| 2009, 2010, 2012, 2017; 2031, 2032 | Billy Idol / Steve Stevens |
| 2011, 2013, 2016, 2018–2020 | Allgemeine Galopp-, Funk-, Powerballaden-, Gitarren-, helle Pop- und Stadionideen |
| 2021–2027 | Christian Bruhn / Fernseh- und Space-Disco-Bezüge |
| 2035, 2036 | Men at Work / Colin Hay, Greg Ham als Klang-/Spielhinweise |
| 2037–2039 | Kanonische Wang-inspirierte Konstruktionen; keine Originaltranskriptionen |

Die Belege haben verschiedene Qualität: alte redaktionelle Stilhinweise,
später referenzierte Konstruktionen und kanonisch geprüfte Vorlagen. Namen und
Interviewverweise allein beweisen keine konkrete Original-Akkordfolge und keine
vollständige Künstlergrammatik. Der ausführliche aktuelle Bestand steht im Anhang.

### Rhythmik, Bass und Hooks

Die 39 Standardrezepte enthalten 16× `PadHeld`, 11× `PadStabs`, 8× `PadGated`,
3× `PadPulse`, 1× `PadStaccato`. Das sind **Rezeptzählungen, keine gemessenen
Höranteile**. Auto-Auswahl, Intensität, Szene und manuelle Einstellungen können
das tatsächlich Ausgeführte verändern.

Zwölf konkrete Bassmuster kommen als Rezeptpräferenz vor, darunter gehalten,
Halbe/Viertel/Achtel, Puls, Funk, Herzschlag, Akkordzerlegung, Pedal, Hi-NRG,
Galopp und Wechselbass. Hinzu kommt die gemeinsame melodische Bassphrasenplanung,
deren aktueller Verbraucher nur in geeigneten automatischen 4/4-Pop-Kontexten
mit Follow EIN arbeitet. Das ist noch keine beliebige eigenständige Bass-Tonfolge.

Neun konkrete Arp-Figuren sind in den Rezepten vertreten: Auf, Ab, Kreis, Zelle,
Riff, Sprünge, Kaskade, Oktatonik und SID. Dazu kommen manuell wählbare Varianten.
Die zusätzliche Bass-/Arp-Verzahnung verschiebt geeignete schwache Arp-Einsätze
komplementär zu einem geplanten Bassraster, erhält metrische Hauptakzente und
schützt geplante Bassphrasen/Hooks. Sie ist keine pauschale Kollisionstilgung.

2028–2036 besitzen neun explizite Hook-Muster mit eigenen Einsätzen und
Akkordgradfolgen. Die neutrale Hook-Policy behandelt die Muster zu 2029, 2030,
2034–2036 phrasenbezogen; 2028 und 2031–2033 dienen motorischeren Lesarten.
Die übrigen 30 Wendungen verwenden keine eigene dieser neun Hook-Zuordnungen;
der GS-Pfad hat ältere kurze Gradfiguren als Ausgangsmaterial.

Tatsächlich ausgegebene Pop-Hook-Noten werden samt Einsatz und Dauer über
`capturePerformance`/`armHookCapture` in denselben Motivkern übernommen. GS und
HM haben getrennte Verwendungszustände. Phrasierte Hooks können gemeinsame
Wiederkehr, zurückhaltende Sequenzierung und geeignete modale Durchgangstöne
verwenden. Kontinuierliche Figuren und phrasierte Wiederkehr sind musikalisch
verschiedene Anforderungen, keine austauschbaren Schalterstellungen.

### Keine Rockband-Simulation

Im untersuchten Produktionspfad gibt es kein Griffbrett, keine Saitenbelegung,
keine Gitarrenstimmung, keinen erzwungenen Gitarrenpatch und keinen Rockband-
Instrumentensatz. Riff-/Quint-/Galoppmuster sind MIDI-Tonfolgen und Rhythmen.
Auch die dunklen/hellen Riff-Tonleitern sind kein Gitarren-Spielbarkeitsmodell.
Gitarren-, Palm-Mute- oder Synthesizerhinweise in Beschreibungen sind Klangideen.
Sie machen die Konstruktion nicht technisch gitarrenspezifisch.

Instrumentennahe Einschränkungen existieren sehr wohl: Tonumfang, Polyphonie,
Artikulation, Notendauer, feste Trigger, teils genreabhängige Register und gemeinsame
Kanalansprüche. Sie müssen bei orchestraler Nutzung geprüft werden. Das Plugin
weiß nicht, welche externen Patches der Anwender geladen hat. Ein kurzer MIDI-
Impuls garantiert beispielsweise keinen geeigneten Orchester-Staccato-Patch.

**Fazit zur Zusammenlegung:** Das komplette Pop-Vokabular ist grundsätzlich
instrumentierungsunabhängig erhaltbar. Eine Umbenennung ist klein; eine verlustfreie
Verlagerung muss zusätzlich seine Strategie-Anschlüsse erhalten. Nur die 39
Harmonien in den Score-Pool zu kopieren würde dafür nicht ausreichen.

## 4. Neun MIDI-Ziele: Möglichkeiten und reale Kopplungen

Die sechs Gruppen heißen im aktuellen Code Fläche, Bass, Arpeggio, Akzente,
Gegenstimme und Melodie. Die neun Ziele sind Spielweisen/Ausgaben, nicht neun
frei organisierte musikalische Agenten. Standardkanäle sind 1–9, aber umstellbar;
Kanalgleichheit kann zusätzliche Konflikte und Schutzregeln auslösen.

| Ziel / Standardkanal | Heutige Aufgabe und Fähigkeitsannahme | Elektronisch nutzbare Aufgabe / erforderliche Abgrenzung |
|---|---|---|
| LF / 1 | Langfläche, tonal, 6 Stimmen, sustained | Akkordfeld/Drone; explizite Lebensdauer unabhängig von Auswahl-/Phrasenwechseln nötig |
| KF / 2 | Kurzfläche, tonal, 9 Stimmen, detached, maximal 720 Ticks | Akkordpulse/kurze rhythmische Schicht; kein neuer Ausgang nötig |
| LB / 3 | Bassfundament/Pedal, tonal, mono, sustained | Langer eigenständiger Grund-/Dissonanzton mit bewusstem Harmoniebezug |
| KB / 4 | Kurzbass, tonal, mono, detached, maximal 960 Ticks | Bass-Sequencer; komplette Tonfolge, Phase und geeignete Gatewerte fehlen als allgemeiner Verbraucher |
| AR / 5 | Tonale Monofigur, detached, maximal 7680 Ticks; Begleitung oder Antwort | Erster eigenständiger Sequencer; heutige Akkord-/Phrasen-Neuverankerung nicht mit eigener Zyklusphase verwechseln |
| TU / 6 | Tonaler Einwurf, 4 Stimmen, detached, maximal 720 Ticks | Pluck, einzelner musikalischer Impuls, kurze passende Zelle; kein fester Effekttrigger |
| ST / 7 | Effekt-/Akzenttrigger, mono, detached, maximal 480 Ticks | Im Standardmodus feste MIDI-Note 36, ohne Transposition; keine tonale Ersatzspur |
| GS / 8 | Linie/Motiv/Frage/Antwort, sustained, 2 Stimmen zugelassen | Optional zweiter Sequencer; dafür Begleitfunktion, passende kurze Spielweise und eigener Ablauf nötig |
| HM / 9 | Optionale Hauptmelodie, tonal, mono, sustained | Melodischer Vordergrund; muss auch bei elektronischen Strategien abschaltbar bleiben |

Das Modell setzt momentan mindestens 240 Ticks für alle Ziel-Spielweisen voraus;
LF/LB/GS/HM haben eine sehr große endliche Maximaldauer (`240·2²⁴` Ticks).
Das sind **Generatorannahmen, keine bestätigten Eigenschaften externer Patches**.
Manche Emissionspfade können kürzere Ereignisse erzeugen; daraus folgt keine
bereits konsistente Freigabe solcher Dauern im Fähigkeitsmodell. Kanonische
Carpenter-Gates von 84 oder 216 Ticks passen beispielsweise nicht ohne Prüfung
zu dessen aktuellem Minimum. Keine stillschweigende Verlängerung der Quelle.

ST besitzt im heutigen Plugin neben „Fest“ auch die Einstellung „Akkord“.
Die Aussage „ST ist ausnahmslos fest“ wäre deshalb als Bestandsbeschreibung falsch.
Standard ist aber „Fest“; dort meldet das Modell bewusst unbekanntes
Tonhöhenverhalten des Samples und feste Adressierung. Eine feste Taste sagt nicht,
ob ihr Sample geräuschhaft oder gestimmt ist. Carpenter-Quellen mit ST=36 dürfen
nicht über den tonalen Alternativmodus harmonisch transponiert werden.

LF/KF teilen Fläche, LB/KB teilen Bass, TU/ST teilen Akzente samt wesentlichen
Bedieneinstellungen; sie sind keine vollständig unabhängig steuerbaren Rollen.
Ein unabhängiger Pedalplan unterdrückt heute den regulären Bass-Renderer komplett:
**LB-Pedal plus gleichzeitig unabhängige KB-Sequenz ist trotz zweier Ausgänge
noch nicht implementiert.** Das ist eine Frage von Rollenanspruch und Notenbesitz,
nicht zunächst von fehlenden MIDI-Buchsen.

### GS ist tatsächlich zu eng für den zweiten Sequencer

Das Grundmodell trennt bereits `MusicalRole` (lead/accompaniment/answer),
`PlayingStyle`, `InstrumentCapabilities` und `MidiTarget`. Seine konkrete
Standardbelegung weist GS jedoch nur lead/answer und sustained zu, nicht
accompaniment/detached. HM und GS besitzen zwei eigene `VoiceState`s; die
Ausgabezuordnung dieser Zustände ist kein allgemeiner Zustandsspeicher für AR,
KB und weitere Sequencer.

Der aktuelle Melodievorrang blockiert GS **nicht mehr pauschal, sobald HM aktiviert
ist**. Er prüft tatsächlich geplante Vordergrundfenster, klingende Noten,
Antworten und bewusst reservierte Ruhe. In Pop gibt es eigene Hook-/Turn-Fenster
und Überlappungsschutz. Das ist sinnvoll für zwei Vordergrundstimmen.

Eine diskrete Begleitsequenz darf jedoch gleichzeitig mit einer Hauptmelodie
musikalisch sinnvoll sein. Würde man sie einfach als heutige GS-Linie ausgeben,
würden `dialogueMayLead`/`popDialogueMayLead`, Phrasenbegrenzungen und gegebenenfalls
Arp-Antworten ihre Kontinuität unterbrechen. Korrekt wäre eine explizite musikalische
Nutzung **Begleitsequenz oder Dialog** mit geeigneter Spielweise und eigenem Zustand.
Dafür ist nicht automatisch eine neue GUI-Steuerung nötig. Der Patch muss die
benötigte Spielweise unterstützen; sustained allein autorisiert kein Staccato.

### Reichen neun Ziele?

**Für den ersten Carpenter-Ausbau ja, nach gezielter Lockerung der beschriebenen
musikalischen Kopplungen.** LF/LB als gehaltene Grundlage, AR und gegebenenfalls
GS/KB als Figuren, KF/TU als Pulse/Einwürfe und ST als Effekt bieten eine brauchbare
Palette. Nicht alle müssen gleichzeitig aktiv sein.

Eine Erweiterung wäre erst durch eine konkrete Studie zu begründen, etwa mehr
zeitgleich unabhängige monophone Figuren mit verschiedenen Patches, als geeignete
Ziele verbleiben, oder getrennte Instrumentenfähigkeiten/Notenbesitzer, die sich
nicht auf die verfügbaren Ziele verteilen lassen. Zusätzliche Ausgänge lösen
weder fehlende Tonfolgenpläne noch eine falsche Rollenklassifikation. Mehrere
Noten auf einem Kanal sind umgekehrt nicht automatisch mehrere unabhängig
steuerbare musikalische Schichten.

## 5. Carpenter: andere Grammatik, keine andere Engine

Maßgeblich sind die kanonische Bibliothek, ihre technische Bestandsaufnahme und
bei Forschungswidersprüchen die Vertiefung. Forschungsvorschläge sind hier
Beobachtungsgrundlage, keine automatisch übernommenen Implementierungsanweisungen.

Die Bibliothek enthält 405 IDs: 88 H, 67 R, 67 Q, 52 B, 45 M, 16 P, 16 T,
12 EF und 42 S. Sie ist archiviert, nicht in der Engine aktiv. Die 54 MIDI-Studien
sind Forschungsdaten, keine bereits erzeugte Carpenter-Plugin-Ausgabe.

| Anforderung | Heute verwendbar | Tatsächlich noch fehlend / begrenzt |
|---|---|---|
| Bewusst statische Harmonik | Geschützte Akkordfarbe, einfache Moll-/Quintklänge, gehaltene Fläche | Vorlagen-/Lebensdauerstrategie darf nicht zwangsläufig harmonisch wechseln oder neu anschlagen |
| Unabhängiges Pedal | Gemeinsamer `PedalPlan`, eigene Lebensdauer, Autorisierung von Dissonanz, sichere Freigabe | Aktueller Produktionsanschluss nur an bestimmte Williams-Vorlagen; unbegrenzte Carpenter-Stasis und paralleles KB sind damit nicht automatisch freigegeben |
| Eigenständige Basssequenz | Bassmuster und begrenzte Bassphrase | Geordnete Quelltonfolge mit eigenem Ursprung, kompletter Periode und harmonischer Bindung statt laufendem Akkordgrundton |
| Eigenständige AR-/GS-Figur | Gemeinsame Zeitbasis, Figuren-/Motivmaterial und Ausgabe | Stabile Tonfolgenphase, Quell-Gates/Akzente, keine automatische Akkord-/Takt-Neustartlogik oder unnötige Motiv-Mindestpause |
| Unterschiedliche Perioden | Tick-Auflösung und Dispatcher | Musikalischer Phasen-/Fortschrittszustand pro Figur; nicht eine weitere technische Clock |
| Hypnotische Schichtung | Mehrere Ausgänge, Aktivitätsschwellen, Dichte und einzelne koordinierte Pläne | Gemeinsamer Entschluss über Eintritt, Fortbestand, Ablösung und Wiederaufnahme einer Schicht; keine Pflicht zum stetigen Verdichten |
| Ineinandergreifende Figuren | Pop-Bass/Arp-Verzahnung als konkretes Vorbild | Beliebige Quellraster bzw. zwei eigene Figuren nicht durch dieselbe enge 4/4-Auto-Regel abgedeckt |
| Pulslose Ereignisfelder | Fläche und einzelne Akzente | Geplante seltene tonale Ereignisse mit eigenem Zeitfenster; kein Zwangspuls und kein automatisch zufälliges Dauer-Tupfen |
| Lange Entwicklung bei konstantem XYZ | Motivwiederkehr, Varianten, Auswahl und Williams-Arp-Phrasierung | Quellbezogene Stasis, Rotation, Reduktion/Rückkehr und Blocktransposition für autonome Schichten noch nicht vollständig |

Die ältere Carpenter-Bestandsaufnahme beruht auf dem Stand vor den unabhängigen
Pedalen und Morricone P1. Deren damaliges „Pedallebensdauer fehlt“ ist heute
**teilweise überholt**: Der gemeinsame Kern und ein Williams-Verbraucher existieren.
Auch explizite harmonische Quelllagen und tatsächlich gebundene Oberstimmen sind
inzwischen hinzugekommen. Beides ersetzt noch keine beliebige Drone-/Sequencer-
Organisation; die alten Klassifikationszahlen werden hier nicht als aktuelle
Neubewertung sämtlicher 405 IDs ausgegeben.

### Identität, Dauer und Quellen nicht zurechtbiegen

`playArpeggio` gewinnt Tonmaterial aus aktueller Harmonie; sein Anker ist je nach
Follow Akkord- oder Phrasenbeginn. Das ist ein Arpeggiator, noch kein allgemeiner
Quellsequencer. Follow AUS hält einen anderen Harmoniebezug, autorisiert aber
weder eine eigene Tonliste noch absichtliche harmonische Fremdtöne.

Der gemeinsame Motivkatalog bewahrt tatsächlich gespieltes Material und getrennte
Verwendung von HM/GS. Seine derzeit zwei Materialplätze und bis acht Originalnoten
pro Motiv reichen nicht automatisch für alle längeren Q/B-Zyklen. Eine fortlaufende
Figur ist nicht zwingend eine Vordergrund-Motivwiederkehr. Ihre Pause darf daher
nicht blind aus der Score-Mindestpause abgeleitet werden.

Beispiele aus der geprüften Bibliothek:

- JC-Q054 hat vier Töne `0, 7, 8, 7` auf Halben: kompletter Zyklus zwei 4/4-Takte,
  Gates 1632 Ticks. Der b6-Ton hat eine ausdrücklich andere Tonfunktion als die
  Akkordtöne; nicht automatisch auf die Mollquinte runden.
- JC-Q043 verbindet fünf Töne mit 16 Anschlägen pro Takt: vollständige Wiederkehr
  erst nach fünf Takten/80 Anschlägen. JC-Q044 braucht drei Takte/24 Anschläge.
  Taktweises Zurücksetzen würde die Identität zerstören. Beide sind als gemeinsame
  SYNTH-Hypothesen, nicht gesicherte Carpenter-Kernmerkmale markiert.
- Eine Halben-Bassfolge kann KBs derzeitiges Dauermodell überschreiten. Ein
  H025-Zyklus von zehn oder H085 von sechs Takten passt nicht in den heutigen
  achtaktigen Harmonieimport. Weder abschneiden noch durch acht Takte ersetzen.

### Was die Forschung für den ersten Schritt wirklich verlangt

Die korrigierte Recherche belegt eine gemeinsame Uhr für die Howarth-Sequencer-
Phase. Unabhängige musikalische Ebenen bedeuten nicht unabhängige DAW-Tempi.
Verschiedene Perioden und Phasenverschiebung sind als Carpenter-Identität **nicht
belegt**; sie bleiben mögliche gemeinsame Fähigkeiten insbesondere auch für
Tangerine Dream/Jarre. Sie sind keine Voraussetzung für den ersten Carpenter-Hörtest.

Die acht Entwicklungsstrategien Stasis, Rotation, Atmung, Wanderung, Umfärbung,
Ereignisfeld, Blockverschiebung und Reduktion/Wiederaufnahme sind Alternativen,
kein obligatorischer Acht-Phasen-Ablauf. Atmung eines bereits gehaltenen externen
Patches lässt sich nicht allein über neue Note-on-Velocities realisieren; daraus
folgt hier keine Freigabe für CC-Automation. Auch ein immer frei gehaltenes
Sprachregister wäre ohne DAW-Kontext nur eine Präferenz, kein Dialogdetektor.

Die Recherche zu *The Thing* unterscheidet Morricones Musik und Carpenter/Howarth-
Zusatzcues. Nicht jede elektronische Passage ist damit Carpenter-Beleg.
Kanonische Zellen sind Konstruktionen mit verschieden gekennzeichneter Evidenz,
keine nachzubauenden Originalthemen.

## 6. Variantenvergleich

Aufwand ist relativ zum heutigen Code bewertet; keine belastbare Kalender- oder
Personentagsschätzung ohne eingegrenzten Implementierungsauftrag.

| Kriterium | A: SCORE / SYNTH / POP/ROCK | B: ORCHESTRAL / ELECTRONIC; Pop als Mischprofil | C: Profile; Familien nur GUI |
|---|---|---|---|
| Musikalische Flexibilität | Gut, wenn alle Verfahren geteilt werden; drei harte Zweige schränken Mischformen ein | Besser als reine Genre-Schubladen nur bei durchlässigen Strategien; Namen suggerieren falsche Instrumentenbindung | Am höchsten: gleiche Verfahren nach Profil und Eignung kombinierbar |
| Unmittelbarer Oberflächenaufwand | Zusätzlicher Modus, Parameter-/State-/Auswahlpfad; musikalisch noch leer | Neue Begriffe und Zuordnung; Pop muss vom Modusschalter zum Profil werden | Familien können zunächst unverändert bleiben; später schlanker Profil-/Filteranschluss |
| Verhaltensbewahrender Codeaufwand | Mittel: alle binären „Score sonst Pop“-Annahmen kontrollieren; Gefahr eines dritten Sonderpfads | Mittel bis hoch: heutige Pop-Ausführung muss im Profil erhalten werden | Mittel, bei sofortigem vollständigem Umbau hoch; schrittweise nur betroffene Strategie-Verbraucher anschließen |
| Carpenter-Voraussetzungen | Eigene Figuren-/Pedalzustände trotzdem nötig | Dieselben Fähigkeiten nötig; Electronic-Name implementiert sie nicht | Dieselben Fähigkeiten nötig, direkt gemeinsam nutzbar |
| Erweiterbarkeit | Weitere Grenzfälle erzeugen Genre-Ausnahmen | Mischkünstler und Orchester-Synth-Kombinationen bleiben begrifflich schwierig | Neue Profile/Vokabulare ohne weitere technische Betriebsart möglich |
| Bedienbarkeit | Einfacher Dreifachschalter, aber Künstler könnten sinnvoll mehrfach vorkommen | Zwei vertraute Wörter, hier musikalisch missverständlich | Einfacher Profilwähler; optionale Sammlungen, keine zusätzliche Strategiereglerwand |
| Pop-Vokabular erhalten | Einfach im bestehenden Pfad | Nur bei Übernahme seiner kompletten Strategiekombination | Als echtes Mixprofil mit seinem Katalog/Strategiebündel vollständig erhaltbar |
| Bestehende Profile schützen | Wenig Risiko bei isoliertem Zusatz, aber Zweierannahmen gefährlich | Höheres unmittelbares Umstellungsrisiko | Niedrig bei schrittweisem Anschluss; hoch bei pauschaler Ersetzung sämtlicher Zweige |

**Empfohlene Kombination:** C als fachliche Architektur; die Vertrautheit von A
höchstens als optionale Navigation bewahren. Keine neue Engine- oder Regelwerk-
Plattform auf Vorrat. Für die Oberfläche genügt später eine einfache Profilwahl
mit optionalen Sammlungen. Eine Sammlung darf nicht heimlich dieselbe ausgewählte
Persönlichkeit anders komponieren lassen. Unterschiedliche neutrale Strategien
müssen eindeutig benannt bleiben, etwa „Neutral Filmmusik“, „80er Pop/Rock – Mix“
und später „Neutral Electronic“, statt ein undefiniertes Neutral umzuschalten.

Ein Profil braucht fachlich eine Auswahlansicht, tatsächlich konsumierte
Strategie-Präferenzen und passende Rollenverwendungen. Es braucht weder einen
kompletten eigenen Generator noch ein frei programmierbares Regelwerk. Die
vorhandenen Policy-, Vorlagen- und Rollenstrukturen sind der Ausgangspunkt.

## 7. Kleinste sinnvolle Folgearbeiten – noch nicht umgesetzt

| Reihenfolge | Begrenzter Inhalt | Prüfkriterium / Aufwandseinordnung |
|---|---|---|
| 1 | Erster Carpenter-Hörkontext: geschütztes Klangfeld, unabhängiger gehaltener Basston und optional seltener tonaler Einwurf. Bestehenden Pedalkern nutzen; eigener Fortbestand ohne Pflicht-Neuanschlag. Kleine passende Quellenauswahl, nicht alle 405 IDs | Kleiner bis mittlerer zusammenhängender Schritt. Alle zwölf Tonarten, Gates/Patchannahmen, Dissonanzautorität, Transport und unbegrenzte Stasis; kein erzwungenes AR/HM/GS. Früh praktisch für Mystery/Horror nutzbar |
| 2 | Eine vollständige eigenständig fortlaufende AR-Tonfolge mit eigener Quellidentität, Ursprung, Rhythmusphase und Tonfortschritt; gemeinsame Tick-Ausführung nutzen | Mittlerer musikalischer Schritt. Keine Takt-/Akkord-Resets; vollständige Periode/Quell-Gates/Autorisierung; kontinuierliche und pausierte Lesart ausdrücklich unterscheiden |
| 3 | Eigenständige KB-Tonfolge; nur bei benötigter Quelle parallel zum LB-Pedal getrennte Ansprüche erlauben | Mittlerer Schritt. Bassmute/Follow/manuelle Wahl respektieren; Pedal nicht neu anschlagen, KB nicht pauschal unterdrücken; eindeutiger Notenbesitz |
| 4 | GS alternativ als geeignete Begleitsequenz nutzen, nicht als konkurrierende Vordergrundlinie; konkrete Zwei-Schichten-Studie | Begrenzter Anschluss nach Schritt 2. GS-Phase unabhängig; HM darf Hintergrundfigur nicht grundlos sperren; Register, Spielweise und Polyphonie prüfen |
| 5 | Beim jeweiligen Anschluss Genre-Grenze durch konkrete Profilstrategie ersetzen; Pop-Mix als vollständiges Strategiebündel erhalten | Keine einmalige Großmigration. Byte-/Ereignisregression der unangetasteten Profile; getrennte Tests für bewusst neue Kombinationen |
| 6 | Quellbelegte Rotation, Blocktransposition, Reduktion/Rückkehr; später tatsächlich benötigte verschiedene Perioden | Größer, einzeln zerlegbar. Keine fixen Veränderungsquoten, keine Phasensimulation durch wiederholten Takt-Reset, keine Pflichtdichte |

Konkreter Kandidat für Schritt 1 ist eine **geprüfte Schnittmenge** um JC-H017
(Mollgrundklang, acht Takte), JC-B001 (eigenständiger Grundton-Drone) und JC-M004
(drei Echoimpulse auf TU). H017 gilt für X 0,10–0,50/Y 0,20–0,90/Z 0–0,60;
M004 für X 0,40–1/Y 0–0,40/Z 0,10–0,60. Gemeinsam zulässig ist also nur ein
begrenzter Bereich, beispielsweise `(0,45 / 0,30 / 0,35)`. Ihre Anker dürfen
nicht ungeprüft als allgemeine XYZ-Abdeckung ausgegeben werden. M004 benötigt
480-Tick-Noten mit Einsätzen 0/1440/2880 und ausdrücklich leiserer Wiederholung;
der heutige TU-Zufallsakzent ist noch kein korrekter Verbraucher dafür. H017s
optionale KF-Pulse müssen im gewählten Kontext bewusst behandelt werden, nicht
als angeblich vollständig importierte Pflichtfigur ausgegeben werden.

Das ist ein früher **Klangfeld-/Suspense-Prototyp**, noch kein vollständiges
Carpenter-Profil. Für die hörbare Sequencer-Seite folgt Schritt 2. Geeignetes
Material ist dort erst nach Tonfunktions-/Gate-/Kontextprüfung auszuwählen;
Q054 zeigt die nötige vollständige Zweitakt-Lebensdauer, ist aber wegen b6 nicht
blind über jeden Mollklang zu legen. Offene Kombinationen und Errata bleiben
zurückgestellt. Zusätzliche Ausgänge oder ein kompletter SYNTH-Modus sind für
keinen dieser ersten beiden Hörschritte zwingend.

## 8. Nachweise und Grenzen der Untersuchung

| Quelle im aktuellen Repository | Konkret herangezogene Stellen |
|---|---|
| [ArrangementTypes.h](../../Source/ArrangementTypes.h), [HarmonyRuntime.h](../../Source/HarmonyRuntime.h) | `Genre`, Muster-Enums; `playbackTemplate`, `wendungTable`, `wendungCount`, Profil-/Genre-Auswahlansichten |
| [CompositionPolicy.h](../../Source/CompositionPolicy.h) | `TexturePolicy`, `HookPolicy`, `PopRolePolicy`, `FreeCompositionPolicy`, `policyForContext` |
| [ScoreEngine.h](../../Source/ScoreEngine.h), Z. 31–190, 4059–4084 | Gruppen/Ausgaben, `outputCatalog`, zwei `VoiceState`s und konkrete Zustandszuordnung |
| [CompositionCore.h](../../Source/CompositionCore.h) | `MotifCatalog`, `MotifUse`, `MusicalRole`, `PlayingTrack`, `RoleNeed`, `suitable` |
| [ScoreEngine.h](../../Source/ScoreEngine.h), Z. 422–480, 1193–1800 | `keepRatio`, `weight`, Auswahl; `phrasedHook`, `performanceMaterial`, `motifOccurrence`, `popLeadWindow`, `popDialogTurn`, `melodicRoleWindow`, `dialogueMayLead` |
| [ScoreEngine.h](../../Source/ScoreEngine.h), Z. 1966–2200, 2419–2600 | `chordFor`, `rawBassPattern`, `melodicBassAllowed`, `prepareBassPhrase`, `movementRhythm`, `prepareVoicingPlan`, `padVoicing` |
| [ScoreEngine.h](../../Source/ScoreEngine.h), Z. 2817–2870, 3261–3456, 3564–3572 | `preparePedal`, `playableMelodyHandoff`, `counterQuestion`, `playArpeggio`, Ausschluss regulärer Bassausgabe bei unabhängigem Pedal |
| [ScoreEngine.h](../../Source/ScoreEngine.h), Z. 3830–4040 | `capturePerformance`, `armHookCapture`, `hookNote`, `freeLinePhrase`, `counterLine` |
| [PedalPlan.h](../../Source/PedalPlan.h), [MusicalTime.h](../../Source/MusicalTime.h), [MusicalExecution.h](../../Source/MusicalExecution.h) | Bassrelation/Autorisierung, gemeinsame Zeit und Ausführung; eigene musikalische Phase ist kein neuer Scheduler |
| [ArpeggioPhrase.h](../../Source/ArpeggioPhrase.h), [RhythmPlan.h](../../Source/RhythmPlan.h), [ChordDisposition.h](../../Source/ChordDisposition.h), [BassPhrase.h](../../Source/BassPhrase.h) | Bereits gemeinsame, aber unterschiedlich aktivierte musikalische Planungsbausteine |
| [HarmonyTypes.h](../../Source/HarmonyTypes.h), [catalog.json](../../data/harmony/catalog.json), [arrangements.json](../../data/harmony/arrangements.json), [notes.json](../../data/harmony/notes.json) | Akkordzeit-/Slotmodell, aktuelle 195 Vorlagen, 39 Pop-Rezepte, explizite Farben/Bässe und redaktionelle Künstlerhinweise |
| [PluginProcessor.cpp](../../Source/PluginProcessor.cpp) | `profileNames`, Parameter `komponist`, `stichModus` und Übernahme der Profil-Policy in Settings; Instrumentierung bleibt extern |
| [Carpenter-Vertiefung](john-carpenter/STROMSCORE_John_Carpenter_Tiefenrecherche_Vertiefung.md), §§5.2/7.2/8 | Gemeinsame Uhr, Evidenzgrenzen, acht Entwicklungsstrategien, Präferenzen statt starre Verbote |
| [Carpenter-Bestandsaufnahme](john-carpenter/IMPLEMENTATION_PLAN.md), [Inventar](john-carpenter/TECHNICAL_INVENTORY.json), [Errata](john-carpenter/ERRATA.md), [Zyklen](john-carpenter/CYCLE_ANALYSIS.json) | Vollständige kanonische Struktur, konkrete Quellenzyklen, Dauer-/Rollenanforderungen und ungeklärte Fälle |
| [Gemeinsame Fähigkeiten](SHARED_MUSICAL_CAPABILITIES.md) | Williams/Herrmann/Carpenter/Morricone-Abhängigkeiten; historische Fehlstellen gegen heutigen Pedal-/Morricone-Code neu eingeordnet |

Die GUI-Hilfe enthält teilweise historische Angaben zu fünf Ebenen/acht Kanälen
und 48+36 Wendungen (`PluginEditor.cpp`). Maßgeblich für diesen Bericht sind die
aktuellen Strukturen und Daten, nicht diese Texte. Keine Korrektur daran im
Analyseauftrag.

Die Bestandszahlen und der Anhang wurden direkt aus den aktuellen Quelldaten
abgeleitet; die entscheidenden Genre-Verzweigungen und ihre Verbraucher wurden
im C++-Code geprüft. Keine neuen MIDI-Renderings oder subjektiven Klangurteile:
Dieser Auftrag untersucht Architektur und darstellbare Verfahren, nicht einen
bereits spielenden Carpenter-Prototyp. Vorhandene Forschungs-MIDI ist davon
getrennt. Kein Build-/Sanitizerlauf erforderlich, da ausschließlich dieser Bericht
neu erstellt wird; keine Behauptung einer erneuten technischen oder musikalischen
Abnahme. Verbleibende Unsicherheiten sind Patchfähigkeiten, offene kanonische
Kombinationen und die musikalische Qualität der erst vorgeschlagenen neuen Anschlüsse.

## Anhang: vollständiges aktuelles Pop/Rock-Inventar

Direkte Projektion von `catalog.json` und `arrangements.json`. Grundtöne/Bässe
sind Halbtonklassen relativ zur gewählten Tonart, **keine** fest vorgeschriebene
absolute Tonart. `@n` bedeutet n Takte; `/b` eine explizite relative Bassklasse.
Arp-/Basspaare sind Auto-Alternativen, keine gleichzeitig verpflichtenden Figuren.
Die Hooknummer bezeichnet den expliziten Mustereintrag 0–8, `–` den älteren Pfad.

| ID / Name | Harmonie und Dauern | XYZ | Auto-Fläche / Bass / AR / Hook |
|---|---|---|---|
| 2001 Kalte Welle | 0:Min@4 → 1:Maj@4 | 0.12/0.45/0.45 | PadHeld / BassPulse,BassHiNrg / ArpSid,ArpCell / – |
| 2002 Neonregen | 0:Min@2 → 5:Min@2 → 8:Maj@2 → 10:Maj@2 | 0.35/0.25/0.1 | PadHeld / BassHalf,BassEighth / ArpCircle,ArpDown / – |
| 2003 Nachtfahrt | 0:Min@2 → 8:Maj@2 → 3:Maj@2 → 10:Maj@2 | 0.3/0.4/0.15 | PadHeld / BassEighth,BassPulse / ArpUp,ArpCircle / – |
| 2004 Sequenzer-Fieber | 0:Min@2 → 8:Maj7@2 → 0:Min@2 → 8:Maj7@2 | 0.3/0.55/0.25 | PadHeld / BassHiNrg,BassHeartbeat / ArpUp,ArpSid / – |
| 2005 Miami-Nacht | 8:Maj7@2 → 5:Min7@2 → 7:Min7@2 → 0:Min7@2 | 0.45/0.35/0.1 | PadHeld / BassArpeggio,BassHalf / ArpCircle,ArpSid / – |
| 2006 Kalter Krieg | 0:Min@2 → 6:Maj@2 → 0:Min@2 → 11:Dim7@2 | 0.1/0.75/0.85 | PadStabs / BassHiNrg,BassPulse / ArpSid,ArpOctatonic / – |
| 2007 Jagd durch L.A. | 0:Min@1 → 8:Maj@1 → 10:Maj@1 → 0:Min@1 → 6:Maj@1 → 8:Maj@1 → 10:Maj@1 → 11:Dim7@1 | 0.15/0.95/0.7 | PadStabs / BassHiNrg,BassPulse / ArpSid,ArpCell / – |
| 2008 Bombast | 0:Min@4 → 8:Maj@2 → 10:Maj@2 | 0.2/0.9/0.55 | PadGated / BassHiNrg,BassHiNrg / ArpSid,ArpUp / – |
| 2009 Rebellenschrei | 0:Fifth@2 → 10:Fifth@2 → 8:Fifth@2 → 10:Fifth@2 | 0.25/0.85/0.4 | PadStabs / BassEighth,BassGallop / ArpRiff,ArpSid / – |
| 2010 Kommando | 0:Min@2 → 10:Maj@2 → 8:Maj@2 → 7:Dom7@2 | 0.3/0.8/0.3 | PadGated / BassGallop,BassEighth / ArpSid,ArpUp / – |
| 2011 Galopp | 0:Min@2 → 7:Dom7@1 → 0:Min@1 → 8:Maj@2 → 7:Dom7@2 | 0.4/0.85/0.35 | PadStabs / BassGallop,BassGallop / ArpSid,ArpRiff / – |
| 2012 Dunkler Glanz | 0:Min@2 → 5:Maj@2 → 0:Min@2 → 5:Maj@2 | 0.45/0.65/0.25 | PadPulse / BassEighth,BassGallop / ArpUp,ArpRiff / – |
| 2013 Synth-Funk | 0:Min@2 → 10:Maj@2 → 8:Maj@2 → 10:Maj@2 | 0.55/0.7/0.15 | PadStabs / BassFunk,BassGallop / ArpRiff,ArpUp / – |
| 2014 Mosaik | 0:Maj@2 → 7:Maj@2 → 9:Min@2 → 5:Maj@2 | 0.6/0.55/0.1 | PadGated / BassEighth,BassHiNrg / ArpUp,ArpSid / – |
| 2015 Tanzsaal | 0:Maj@2 → 10:Maj@2 → 5:Maj@2 → 0:Maj@2 | 0.65/0.65/0.15 | PadGated / BassHiNrg,BassEighth / ArpRiff,ArpUp / – |
| 2016 Powerballade | 0:Maj@2 → 4:Min@2 → 5:Maj@2 → 7:Maj@2 | 0.7/0.3/0.05 | PadHeld / BassHalf,BassQuarter / ArpCircle,ArpUp / – |
| 2017 Machtakkorde | 0:Fifth@2 → 10:Fifth@2 → 5:Fifth@2 → 0:Fifth@2 | 0.7/0.8/0.3 | PadStabs / BassEighth,BassGallop / ArpRiff,ArpLeaps / – |
| 2018 Sunset Strip | 0:Add9@2 → 5:Maj/0@2 → 0:Add9@2 → 7:Sus4@2 | 0.8/0.45/0.05 | PadHeld / BassPedal,BassEighth / ArpSid,ArpCascade / – |
| 2019 Sonnenseite | 10:Maj@2 → 5:Maj@2 → 0:Maj@4 | 0.8/0.65/0.1 | PadGated / BassEighth,BassAlternating / ArpRiff,ArpUp / – |
| 2020 Stadionhymne | 0:Maj@2 → 8:Maj@1 → 10:Maj@1 → 0:Maj@2 → 8:Maj@1 → 10:Maj@1 | 0.85/0.9/0.1 | PadPulse / BassEighth,BassHiNrg / ArpUp,ArpLeaps / – |
| 2021 Feindkontakt | 0:Min7@2 → 1:Maj7@2 → 0:Min7@2 → 6:Dom7@2 | 0.18/0.8/0.55 | PadStabs / BassFunk,BassPulse / ArpCell,ArpOctatonic / – |
| 2022 Teufelsgeiger | 0:Min@1 → 5:Min@1 → 10:Maj@1 → 3:Maj@1 → 8:Maj@1 → 2:HalfDim@1 → 7:Dom7@1 → 0:Min@1 | 0.32/0.7/0.25 | PadPulse / BassHiNrg,BassEighth / ArpLeaps,ArpCircle / – |
| 2023 Vorahnung | 0:Min@2 → 1:Maj@2 → 7:Dom7b9@2 → 0:Min@2 | 0.38/0.45/0.45 | PadHeld / BassHeartbeat,BassPulse / ArpCircle,ArpCascade / – |
| 2024 Einsamer Planet | 0:Min9@2 → 8:Maj7@2 → 10:Sus4@1 → 10:Maj@1 → 0:Min9@2 | 0.4/0.2/0.1 | PadHeld / BassHeld,BassHalf / ArpCircle,ArpCascade / – |
| 2025 Weltraum-Disco | 0:Min9@2 → 5:Dom7@2 → 0:Min9@2 → 3:Maj7@1 → 5:Dom7@1 | 0.48/0.62/0.2 | PadGated / BassHiNrg,BassFunk / ArpRiff,ArpSid / – |
| 2026 Serenade | 0:Maj@2 → 9:Min@2 → 2:Min7@2 → 7:Dom7@2 | 0.72/0.45/0.05 | PadStaccato / BassAlternating,BassEighth / ArpLeaps,ArpUp / – |
| 2027 Startfreigabe | 0:Maj7@2 → 2:Dom7@2 → 2:Min7@2 → 7:Sus4@2 | 0.78/0.75/0.15 | PadStabs / BassHiNrg,BassFunk / ArpRiff,ArpUp / – |
| 2028 Tanzflächenlicht | 0:Maj@2 → 2:Min7@2 → 5:Maj@2 → 7:Sus4@1 → 7:Maj@1 | 0.76/0.69/0.08 | PadStabs / BassFunk,BassArpeggio / ArpRiff,ArpUp / 0 |
| 2029 Gegenlicht | 0:Maj7@2 → 10:Maj7@2 → 2:Min7@2 → 7:Sus4@2 | 0.52/0.38/0.12 | PadHeld / BassFunk,BassHalf / ArpCircle,ArpCascade / 1 |
| 2030 Rückspiegel | 9:Min9@2 → 9:Min9/7@2 → 2:Dom7/6@2 → 5:Maj7@2 | 0.36/0.18/0.06 | PadHeld / BassHeld,BassHalf / ArpDown,ArpCircle / 2 |
| 2031 Stahlpuls | 9:Fifth/9@2 → 5:Fifth/9@2 → 7:Fifth/9@2 → 9:Fifth/9@2 | 0.34/0.83/0.22 | PadGated / BassEighth,BassPedal / ArpRiff,ArpCell / 3 |
| 2032 Drahtseil | 9:Min/9@2 → 9:MinMaj7/9@2 → 9:Min7/9@2 → 9:Min6/9@2 | 0.2/0.57/0.42 | PadHeld / BassEighth,BassPedal / ArpDown,ArpCell / 4 |
| 2033 Sequenzmotor | 9:Min9@2 → 2:Dom7@2 → 7:Maj7@2 → 0:Maj7@2 | 0.46/0.78/0.17 | PadGated / BassHiNrg,BassFunk / ArpSid,ArpRiff / 5 |
| 2034 Spiegelpalast | 0:Maj7@1 → 4:Dom7@1 → 9:Min7@2 → 2:Dom7@1 → 2:Min7@1 → 7:Dom7@1 → 0:Maj7@1 | 0.7/0.71/0.26 | PadStabs / BassArpeggio,BassQuarter / ArpCascade,ArpUp / 6 |
| 2035 Sonntagmorgen | 0:Maj@2 → 5:Maj@2 → 9:Min7@2 → 7:Maj@2 | 0.88/0.48/0.03 | PadStabs / BassFunk,BassAlternating / ArpRiff,ArpCircle / 7 |
| 2036 Licht im Fenster | 9:Min@2 → 0:Maj/7@2 → 5:Maj7@2 → 4:Dom7@2 | 0.57/0.23/0.04 | PadHeld / BassHeld,BassHalf / ArpCircle,ArpDown / 8 |
| 2037 WC-H01 – Mixolydischer Kreis mit Sus-Auflösung | 0:Maj/0@2 → 10:Maj/10@2 → 5:Maj/9@2 → 0:Sus2/0@1 → 0:Maj/0@1 | 0.75/0.5/0.3 | PadHeld / BassHeld,BassQuarter / ArpUp,ArpCircle / – |
| 2038 WC-H11 – Dorische Wendung | 0:Min7/0@2 → 5:Maj/0@2 → 0:Min7/0@2 → 5:Maj/9@1 → 10:Maj/10@1 | 0.4/0.5/0.3 | PadHeld / BassHeld,BassQuarter / ArpUp,ArpCircle / – |
| 2039 WC-H19 – Dunkle Quint-Maschine | 0:Fifth/0@6 → 8:Fifth/8@1 → 10:Fifth/10@1 | 0.15/0.9/0.2 | PadHeld / BassHeld,BassQuarter / ArpUp,ArpCircle / – |
