# STROMSCORE – Musikwissenschaftliche Tiefenrecherche: John Carpenter

*Zieldatei: STROMSCORE_John_Carpenter_Tiefenrecherche.md · Phase 1 (Recherche) · Stand: 27. November 2026*

Carpenter wird musikalisch zu „Carpenter“ nicht durch bestimmte Synthesizer, sondern durch eine Grammatik der Verknappung: kurze, von Hand gespielte, rockmusikalisch geprägte Ostinato-Zellen über einem gleichmäßigen „Herzschlag“-Puls oder einem extrem lange gehaltenen Ton, in wenigen klar getrennten Registerschichten (hoch – mittel – tief), deren Veränderung vor allem durch Hinzufügen und Entfernen von Schichten sowie durch Blockverschiebungen der ganzen Zelle um einen Halbton entsteht, nicht durch neue Melodien oder funktionale Akkordfolgen.

## TL;DR

- **Kern der Grammatik (N/I):** Carpenters Identität liegt in Puls + Zelle + Halteton: ein mechanischer Grundpuls (Halloween: „metronome-like sound … so I could play along“), eine kurze Zelle aus Quinten/Oktaven mit Halbtonreibung, und extrem statische Bässe oder Drones („A hold note for like two minutes?“ – Alan Howarth). Das alles ist instrumentenunabhängig und damit direkt in MIDI übertragbar.
- **Entwicklung durch Schichtung, nicht durch Thematik (N/I):** Belegte Hauptstücke wachsen „only in texture, but not thematically“ (Burnand/Mera über *Assault on Precinct 13*, Sekundärzitat). Halloween fügt Schicht um Schicht hinzu und verschiebt die Zelle um Halbtöne. Für STROMSCORE heißt das: Ein Schicht-Ein/Aus-Automat und eine globale Halbton-Blockverschiebung sind wichtiger als ein Akkordfolgen-Generator.
- **Übertragung (E):** Die neun Rollen reichen weitgehend aus. Ohne HM/GS trägt die Kombination LB (Pedal) + KB (Puls-/Riffbass) + AR (Zelle) + LF (Drone) + TU/ST (Stinger) bereits eine glaubwürdige Carpenter-Identität. Konkreten Ergänzungsbedarf gibt es nur bei einer optionalen, nicht transponierbaren Rhythmusmaschinen-Spur und bei langsamen CC74-Rampen (Filterhelligkeit). Polyrhythmik und Phasenverschiebung sind für Carpenter nicht belegt und sollen nicht als Stilregel implementiert werden.

## Kernbefunde

| # | Befund | Kennz. |
|---|---|---|
| 1 | Das Halloween-Thema beruht auf einer 5/4-Zelle, die Carpenter auf eine Bongo-Lektion seines Vaters zurückführt; auf dem Klavier „rocking octaves“, „octaves and went up a half-step“.\[1\]\[2\] | N |
| 2 | Die Akzentgruppierung des Halloween-Themas wird als 3+3+2+2 Achtel beschrieben (Berklee Online, Michele Darling); daraus folgt die verbreitete Lesart „10/8“.\[3\] | N (Sekundäranalyse) |
| 3 | Der tickende Grundpuls in Halloween stammt laut Dan Wyman aus einem Moog-Sequencer; die Klavierfigur spielte Carpenter von Hand darüber.\[4\] | N |
| 4 | Die Melodie- und Riffideen kamen von Carpenter; Klangpalette, Synchronisation und Drumcomputer lagen ab *Escape from New York* bei Howarth („The whole synthesizer synchronization and drum machine stuff was on me“).\[5\]\[6\] | N |
| 5 | Mit wachsender Zusammenarbeit (*Prince of Darkness*, *They Live*) übernahm Howarth eigenständig ganze Passagen; diese Partituren sind Gemeinschaftssprache.\[5\] | N |
| 6 | Musik zu *The Thing* stammt überwiegend von Ennio Morricone; genau vier elektronische Zusatzcues („Main Title“/„Main Theme“, „Burn It“, „Fuchs“, „To Mac's Shack“) sind Carpenter (in association with Alan Howarth) zugeordnet – so auf dem Howarth/Hopkins-Album von 2011 und, neu eingespielt von John und Cody Carpenter sowie Daniel Davies, auf der EP *Lost Cues: The Thing* (Mai 2020). | N |
| 7 | Carpenter beschreibt seine Funktion als „Teppich“ (carpet) unter der Szene und grenzt sich vom „Mickey-Mousing“ (Steiner, Williams) zugunsten Herrmann-artigen Underscorings ab. | N\[7\] |
| 8 | Eine Polyrhythmik oder Phasenverschiebung unabhängiger Sequencer-Zyklen ließ sich in keiner Quelle konkret nachweisen. | N (Negativbefund) |
| 9 | In *Halloween II* gab es keine Quantisierung: „you really had to play everything“ (Howarth).\[8\] Die „mechanische Präzision“ kommt aus Maschinenpuls + Handspiel, nicht aus Raster-Perfektion aller Schichten. | N/I |
| 10 | In *Big Trouble in Little China* arbeiteten Carpenter/Howarth mit MIDI und Arpeggiator-artigem Verfahren:\[5\] gehaltene Töne, die „randomly or in sequence“ abgetastet wurden, darauf reagierte Carpenter melodisch. | N (Sekundärzitat)\[7\] |

## 1. Methodik, Quellenlage und Kennzeichnung

**Kennzeichnung:** N = nachvollziehbar nachgewiesen · I = begründete musikalische Interpretation · H = plausible, nicht ausreichend belegte Hypothese · E = eigenständige Ableitung für STROMSCORE.

**Grundsatz:** Es wurden keine Transkriptionen urheberrechtlich geschützter Themen erstellt und keine Taktangaben erfunden. Wo Tonhöhen genannt werden, stammen sie aus benannten Sekundäranalysen und sind als solche markiert.

| Quelle | Art | Einsichtstiefe |
|---|---|---|
| Tomasz Adam Cundell, MRes-Arbeit „Patterns And Recurring Themes In The Music Of John Carpenter“ (University of Nottingham, Studienjahr 2022/23; auf Nottingham ePrints veröffentlicht am 20. Juli 2024; Betreuung u. a. Prof. Mervyn Cooke) | Wissenschaftliche Analyse, eigene Transkriptionen | Vollständig eingesehen bis ca. S. 46 (Kap. 1–3 teilweise); Rest abgeschnitten |
| Tim Greiving, „John Carpenter, Dark Lord of the Film Score“ (The Ringer, 2023) | Feature mit Interviews (Carpenter, Wyman, Howarth, Cody Carpenter) | Großteils vollständig |
| Alan Howarth-Interview, Dread Central (2023) | Interview | Großteils vollständig |
| Alan Howarth-Interview, Birth.Movies.Death. (2018) | Interview | Vollständig |
| John Carpenter, Composer Notes *The Fog* (theofficialjohncarpenter.com) | Primärquelle Komponist | Vollständig |
| K. J. Donnelly, „Hearing Deep Seated Fears: John Carpenter's The Fog (1980)“, in N. Lerner (Hg.), *Music in the Horror Film*, Routledge 2010, S. 152–167\[9\] | Musikwissenschaft | **Nicht eingesehen**; nur über Sekundärzitate (Nottingham-Arbeit, Randall D. Larson-Liner-Notes Silva Screen 2012, Blog) |
| D. Burnand / M. Mera, „Fast and Cheap? The Film Music of John Carpenter“, in Conrich/Woods (Hg.), *The Cinema of John Carpenter*, Wallflower 2004, S. 49–65\[10\] | Musikwissenschaft | **Nicht eingesehen**; nur über Sekundärzitate (Wikipedia-Fußnoten, Nottingham-Arbeit, filmexposure.ch) |
| Rolling Stone, Billboard, NPR, Dazed, Red Bull Music Academy, RogerEbert.com, The Skinny | Carpenter-Interviews | Snippets |
| Neil Lerner (Davidson College), Berklee Online, Hooktheory, Pianote, Splice | Kurzanalysen Halloween-Thema | Snippets |
| Filmtracks, maintitles.net, Electric Sheep, Wax Poetics, AllMusic | Rezensionen | Snippets |

**Bewertung der Quellenlage (I):** Die wissenschaftliche Literatur zu Carpenters Musik ist schmal; Cundells Nottingham-Arbeit stellt im Abstract selbst fest, „very little has been written about John Carpenter's work and even less about the scores that he wrote for his films“. Die beiden Fachaufsätze (Donnelly; Burnand/Mera) konnten nicht im Primärtext geprüft werden. Nach allem, was die Sekundärzitate zeigen, enthalten sie eher kategoriale und funktionale Aussagen als detaillierte Tonhöhenanalysen. Für Tonhöhen-, Metrik- und Schichtdetails sind daher Interviews der Beteiligten, Liner Notes und die Nottingham-Arbeit die belastbarsten Quellen.

## 2. Werke, Urheberschaft und Unterschiede

| Werk | Beteiligte | Dokumentierte Arbeitsweise / Charakter | Kennz. |
|---|---|---|---|
| *Dark Star* (1974) | Carpenter; Minimoog-Hilfe durch Dan Wyman\[4\] | Synthesizer-„beeps and boops“ zwischen Effekt und Musik; Kritik an fehlender Entwicklung | N\[7\] |
| *Assault on Precinct 13* (1976) | Carpenter; Programmierung Wyman (Sound Arts)\[11\] | Laut verbreiteten Angaben in drei Tagen komponiert, Carpenter selbst nennt jedoch 2015 für die Aufnahme nur einen Tag („Assault, which was one day“, Interview Magazine); Haupttitel: fetter Sägezahn-Bass über „ricky-tick rhythm-box“ mit großem Hall; Temp-Vorbild „Immigrant Song“ (Led Zeppelin). Laut Burnand/Mera (Sekundärzitat) baut der Haupttitel „only in texture, but not thematically“ auf; dazu ein Fender-Rhodes-Thema und ein hoher Haltetton als Gang-Motiv „with no other changes except inner frequency modulations“ | N |
| *Halloween* (1978) | Carpenter; Wyman | In drei Tagen aufgenommen („I had three days to record the score for Halloween, which was a big improvement from Assault, which was one day“, Carpenter, Interview Magazine 2015), ohne Bildsynchronisation, Cue-Längen per Stoppuhr („making yard goods, like cloth“, Wyman); Klavier + Synth; Maschinenpuls zuerst aufgenommen | N |
| *The Fog* (1980) | Carpenter; Wyman | Komplett neu vertont nach misslungener erster Fassung; Ziel: „a lightness of tone, a softer understated fear“; Drei-Linien-Satz, Glocken-/Cembalo-„round“, zehnminütiger Reel-9-Cue\[12\] | N\[13\] |
| *Escape from New York* (1981) | Carpenter + Howarth (erste Zusammenarbeit) | Vorbilder Tangerine Dream (*Sorcerer*) und The Police; Prophet-5, ARP, Linn LM-1; Themenschluss im Raum ausgearbeitet; Sync zunächst per gleichzeitigem Start von VHS und Band\[4\]\[5\]\[6\] | N\[4\] |
| *Halloween II* (1981) | Howarth (Carpenter-Material) | Howarth spielte Texturen über Carpenters Original-Mehrspur; „much darker … gothic“; keine Quantisierung\[8\] | N\[14\] |
| *The Thing* (1982) | **Morricone**; Zusatzcues Carpenter/Howarth | Zusatzcues: Drones, Stinger; „almost tones“ (Carpenter); Main Title mit gleicher aufsteigender Zwei-Ton-Formation wie Morricone (Filmtracks)\[15\]\[16\] | N\[7\] |
| *Halloween III* (1982) | Carpenter + Howarth | Linn-Drum, ARP-Sequencer, zwei Prophets; Howarth „dialed up a sequence“ für „Chariots of Pumpkins“;\[17\] „sweep-filtered arpeggiating Prophet synths“ (Electric Sheep)\[8\]\[17\] | N\[8\] |
| *Christine* (1983) | Carpenter + Howarth | Elektronischer Score neben 1950er-Rock-Songs; „Electronica for a killer car … I filled in where necessary“ (Carpenter)\[18\] | N |
| *Big Trouble in Little China* (1986) | Carpenter + Howarth | Erstmals MIDI und Samples;\[5\] Chinatown über Klangfarbe statt Melodik (Troy Howarth, Sekundärzitat) | N\[7\] |
| *Prince of Darkness* (1987) | Carpenter + Howarth | Gesampelte Chöre über eingängiger Basslinie; Howarth zunehmend eigenständig\[5\]\[19\] | N\[20\] |
| *They Live* (1988) | Carpenter + Howarth | Blues-Riff (Nottingham-Arbeit: E–E(8va)–E–G–E) | N\[7\] |
| *In the Mouth of Madness* (1994/95) | Carpenter + Jim Lang | Gitarren-Haupttitel (Temp: „Enter Sandman“); laut Nottingham-Arbeit fehlt dem übrigen Score der typische Puls | N\[7\] |
| *Village of the Damned* (1995) | Carpenter + Dave Davies | Keine belastbare Analysequelle gefunden | Lücke |
| *Vampires* (1998) | Carpenter mit Bluesband (u. a. Steve Cropper, Donald „Duck“ Dunn), Cody Carpenter, Daniel Davies\[21\] | Blues-Rock-Score\[21\] | N\[20\] |
| *Ghosts of Mars* (2001) | Carpenter mit Anthrax, Steve Vai, Buckethead u. a.\[22\] | Metal-Score; Synthklang nur punktuell\[23\]\[24\] | N\[20\] |
| *Lost Themes I–IV* (2015–2024) | John + Cody Carpenter, Daniel Davies\[25\] | Improvisiert in Logic Pro; Stücke beginnen „with a bassline or arpeggiator“; *IV: Noir* mit „heavy guitar riffs“\[25\]\[26\]\[27\] | N |

**Einordnung (I):** Für den SYNTH-Modus ist der Korpus 1976–1988 maßgeblich. Ab *In the Mouth of Madness* wandert die Identität in Gitarren-Riffs und Rock/Blues/Metal; das gehört eher in den künftigen POP/ROCK-Modus. Die *Lost Themes* zeigen, welche Bausteine Carpenter selbst als Keimzelle behandelt (Bassline, Arpeggiator), sind aber Studioproduktionen mit dichterer Instrumentierung.

## 3. Harmonische Grammatik

**3.1 Grundmaterial (N/I).** Belegt sind: Moll-Zentrierung (Hooktheory-TheoryTab „Halloween Theme“: Intro in F♯-Moll, 140 BPM, 5/4; Verse in F♯-Moll, 136 BPM; Chorus in „B Harmonic Minor“; crowd-sourced, mittlere Verlässlichkeit), Quint- und Oktavgerüste (Pianote: die rechte Hand ist „a series of 5ths with a half-step added“, Eröffnung mit C♯ und F♯, Halbtonschritt zu D), Tritoni und kleine Sexten (Berklee/Hypebot: „tritones and minor 6ths that then descend by a minor 2nd“) sowie Halbtonverschiebung des gesamten Materials (Neil Lerner: „mostly three pitches that he repeats several times, and then he shifts it all down a half step“).

**3.2 Konflikt in den Quellen (offen gelegt).** Cundell (Nottingham-Arbeit, Abstract) beschreibt, das Thema „works around a 5/4 quaver pattern that drops a semitone and then rises again as the bass slowly creeps up a minor third and then a semitone“. Dan Wyman spricht dagegen von einem Gang durch den Quintenzirkel.\[4\] Splice nennt eine Tonartenfolge C-Moll – A-Moll – F-Moll – D-Moll, die mit den anderen Analysen nicht vereinbar ist.\[28\] Konsistent über die Quellen hinweg ist nur: **die Zelle bleibt intervallisch identisch und wird als Block transponiert, vorrangig um Halbtöne** (N). Die genaue Transpositionsfolge bleibt H.

**3.3 Harmonische Statik und Pedal (N).** Howarth fasst die Lehre aus acht Jahren mit Carpenter zusammen: „the idea of the quarter-note pulse … A hold note for like two minutes? … But it worked for his movies. It created tension.“\[8\] Die Nottingham-Arbeit bemerkt, dass das Halloween-Thema nur einmal pro Takt den Akkord wechselt. Bei 136 BPM in 5/4 bedeutet das langsamen harmonischen Rhythmus bei schneller Oberflächenaktivität.\[7\]

**3.4 Akkordqualitäten (I/H).** Belegt sind Mollakkorde („a methodical series of minor chords on synths with strange tonalities used as unnerving accents throughout“ für das *Halloween III*-Hauptthema, Rezension im Blog Soundtrack Universe, 2016), Power-Chord-Harmonik (Grundton–Quinte–Oktave in *In the Mouth of Madness*, Nottingham-Arbeit) und Cluster („based on tone clusters“ für die *The Thing*-Zusatzcues, Dokumentationsaussage via Nottingham-Arbeit). Daraus folgt als Interpretation: Carpenters Harmonik ist **Zwei-Ebenen-Harmonik** – eine leere Quint/Oktav-Ebene (stabil, kalt) und eine Reibungsebene (Halbton, Tritonus, Cluster) für Bedrohung. Terzschichtung mit Septimen oder Optionstönen spielt kaum eine Rolle (I).

**3.5 Kadenzen und Funktionalität (I).** In keiner Quelle findet sich eine Dominant-Tonika-Kadenz als Strukturmittel. Musik beginnt und endet per Ein-/Ausblendung oder Schnitt; die Nottingham-Arbeit beschreibt das Halloween-Thema als „starting softly and adding layers until a final fade out“.\[7\] Dissonanzen bleiben stehen, statt aufgelöst zu werden („continuous, steady, and unresolving“, Berklee/Hypebot).\[2\] **Nichtfunktionale Harmonik ist Normalfall, nicht Effekt.**

**3.6 Bass gegen Fläche (I).** Larson (Liner Notes, Sekundärquelle) beschreibt die Fog-Themen als „a forceful contrast between high-end melody, mid-range counterpoint, and low, droning bass textures“.\[13\] Carpenter selbst schildert sein Lieblingsthema der *Fog* als „three lines, a high flute melody, a mid-range counterpoint and a low bass support“ (N).\[12\] Die harmonische Beziehung entsteht durch das Zusammenklingen der drei Linien, nicht durch geplante Akkordfolgen.

**3.7 Carpenter-spezifisch vs. allgemein elektronisch (I):**
- *Allgemein elektronisch:* lange Drones, Arpeggien über statischem Akkord, Filterbewegung.
- *Carpenter-spezifisch:* (a) Halbton-Blocktransposition einer intakten Zelle; (b) Oktav-„Wiegen“ (rocking octaves) als Melodieersatz; (c) Riff-Herkunft aus Rock/Blues (Immigrant Song, They Live); (d) Kombination aus Quintleere und einzelner Halbtonreibung statt üppiger Pads; (e) Verzicht auf Kadenz bei gleichzeitig hoher rhythmischer Prägnanz.

## 4. Sequencer-Grammatik und Ostinati (höchste Priorität)

**4.1 Hand vs. Maschine – geprüft, nicht vorausgesetzt (N).**
- *Halloween:* „The metronome-like sound on it is an electronic machine – almost like a drum machine … one of the first things that we put down, so I could play along to it“ (Carpenter, Dazed).\[29\] Wyman realisierte das Ticken laut Ringer mit einem Moog-Sequencer. Das Klavier-Ostinato spielte Carpenter selbst: „The stuff you hear on my early albums is all me playing … it has to be simple if I'm doing it.“\[4\]
- *Halloween II:* „because there were no computers involved, you really had to play everything. You couldn't just … quantize it and loop it“ (Howarth).\[8\]
- *Halloween III:* Howarth „dialed up a sequence on my analog gear“ für „Chariots of Pumpkins“ – hier ist der Sequencer tatsächlich Träger der Zelle.\[8\]
- *Big Trouble:* MIDI; „we'd create a pattern of notes that you hold down … the computer would pick through these notes on its own, randomly or in sequence … you respond to it with your own melody“ (Howarth, via Troy Howarth, *Assault on the System*, Sekundärzitat).\[7\]
- *Lost Themes:* „a song usually starts with Cody and I … with a bassline or arpeggiator“.\[27\]

**Folgerung (I):** Die „mechanische“ Wirkung entsteht aus einem **einzigen maschinellen Referenzpuls**, gegen den Menschen eng, aber nicht rastergenau spielen. Das ist wichtig für die MIDI-Humanisierung (siehe 4.6).

**4.2 Zellenbau (N/I).** Typische Zellen sind kurz: Lerner spricht von „mostly three pitches“;\[3\] die Cue-by-Cue-Analyse des Halloween-Scores (Blog, Snippet) nennt ein „3-note rising piano/synth motif“, ein „2-note piano ostinato“ (Laurie-Thema) und einen Teil „based on a rising 4-note figure“; AllMusic beschreibt für *Escape from New York* „simple, repetitive keyboard figures, generally two per sequence, set in a fast-slow counterpoint“ (Sekundärzitat).\[30\]\[31\] Intervallisch dominieren Oktave, Quinte, Halbton; der Tritonus erscheint als Reibung.

**4.3 Metrik und Akzent (N).** Halloween: 5/4 mit Akzentgruppen 3+3+2+2 Achtel (Darling/Berklee).\[2\]\[3\] Carpenter vokalisiert das Muster als „Ba-ba-ba ba-ba-ba ba-ba-ba-ba-ba“.\[32\] Das ist der einzige gut belegte Fall ungerader Metrik; die anderen Hauptthemen (*Assault*, *Escape*, *They Live*) stehen im geraden Metrum mit Rock-Groove (I). **Ungerade Metrik ist also ein markantes, aber singuläres Merkmal, keine Generalregel.**

**4.4 Polyrhythmik und Phasenverschiebung (N, Negativbefund).** Für keine der untersuchten Partituren fand sich ein Beleg für gegeneinander verschobene Sequencer-Zyklen unterschiedlicher Länge. Die belegte Mehrschichtigkeit ist **komplementär im selben Raster**: Puls + Zelle + Halteton, bzw. „fast-slow counterpoint“ (*Escape*). Phasenverschiebung bleibt als allgemeine Sequencer-Möglichkeit (Tangerine-Dream-Tradition) erlaubt, darf aber **nicht** als Carpenter-Regel markiert werden.

**4.5 Wann bleibt eine Sequenz unverändert? (N/I).** Belegt ist die extreme Konstanz: *Assault*-Haupttitel „builds only in texture“;\[33\] ein Musiker beschreibt ihn als Aufbau „to a few synth elements, and then gets stripped back down to just the drums“ (IMPOSE, Snippet).\[34\] Fog Reel 9: zehn Minuten „held together by … a bell/heartbeat driven by rising and falling synthesized tones“ (Carpenter).\[12\] Variiert werden (I): (1) Transpositionsstufe der gesamten Zelle; (2) Register/Oktavlage; (3) Klangfarbe/Instrument (*Halloween II*: Orgel statt Klavier); (4) Tempo/Dichte („fast and syncopated … or slow and creepy“, Ringer).\[4\]\[35\] **Identitätsstiftend und daher unveränderlich: Intervallfolge und Akzentmuster.**

**4.6 Notenlängen und Spielweise (I/E).** Staccato-Einzeltöne („stabbing staccato single-note strains“ in *Halloween III*, Rezension) stehen gegen Haltetöne über Minuten.\[36\] Mittlere Notenlängen sind selten. Für MIDI: Zellennoten 30–60 % Gate, Pedale 100 % über viele Takte; Timing-Humanisierung nur auf Hand-Schichten (KB/AR/HM), nicht auf der Puls-Referenz (E).

**4.7 Spannung mit wenigen Tönen (I).** Drei Mechanismen sind aus den Belegen ableitbar: (1) **Asymmetrie** (5/4, 3+3+2+2) verhindert Einrasten; (2) **Halbtonreibung** zwischen Zelle und Pedal bleibt ungelöst; (3) **Erwartung von Schichtzuwachs** – der Puls kündigt an, ohne einzulösen. Donnelly beschreibt die Partitur als „fragmentary and repetitious“ und Carpenters Musik als „primal“ und „inhuman“ (Sekundärzitate).\[13\]\[37\]

## 5. Bassführung

| Bassfunktion | Beleg | Wirkung (I) |
|---|---|---|
| Tiefer Drone / Haltetton | „hold note for like two minutes“ (Howarth);\[8\] „buzzing synth drone“ unter Fog-Prolog (Larson) | Ruhe mit latenter Bedrohung\[8\]\[13\] |
| Pulsierender Einzeltonbass („Herzschlag“) | Donnelly vergleicht Carpenters Basspuls mit Herzschlag (Fog); Carpenter selbst nennt „bell/heartbeat“\[7\]\[12\] | Latente bis akute Bedrohung, je nach Tempo\[7\] |
| Riffbass / melodische Basssequenz | *Assault*: „fat bass synth“, Temp „Immigrant Song“; Wyman sollte „a good, sick bass“ liefern (Halloween)\[4\]\[38\] | Verfolgung, Action |
| Oktavierender Bass | „rocking octaves“ (Halloween, rechte Hand); Blues-Riff E–E(8va)–E–G–E (*They Live*) | Antrieb ohne harmonische Bewegung\[7\]\[39\] |
| Kriechender Bass unter konstanter Zelle | Halloween: Bass „creeps up a minor third and then a semitone“ (Nottingham) | Eskalation ohne neue Melodie\[7\] |

**Harmonische Freiheit (I):** Der Bass darf sich gegen die Oberzelle bewegen (Kriechen um kleine Terz/Halbton), während die Zelle steht – oder stehen bleiben, während die Zelle blocktransponiert wird. Er ist **nicht** an Akkordgrundtöne einer Progression gebunden, sondern an das Pedal-Zentrum. Akuter Horror wird laut Diabolique (Rezension, Snippet) weniger durch Bassaktivität erzeugt: Die Musik geht bei Morden „to a single note“ und wird zurückgenommen.\[40\]

## 6. Motivik und Melodik

- **Motivlänge (N/I):** 2–4 Töne; Titel-Hooks bis etwa ein Takt. Längere Linien gibt es in den „lyrischen“ Themen (Fog-Flötenmelodie, Rhodes-Thema *Assault*).
- **Wiederholung (N):** Carpenter will „simple and repetitive and gets under your skin“; er bat Morricone um „fewer notes“.\[4\]\[7\]\[32\]
- **Rollenwechsel (N/I):** In Halloween trägt die Klavierzelle zugleich Puls, Harmonie und Melodie. In *Escape* übernimmt der Bass das Thema, Keyboards antworten. In Fog ist das Glocken-/Cembalo-„round“ ein Kanon – die einzige explizit belegte Imitationstechnik.\[12\]
- **Frage-Antwort (H):** Die Beschreibung eines „3-note rising … motif (with a shadowing 2-note falling line)“ deutet ein Ruf/Echo-Prinzip an; das ist nicht systematisch belegt.
- **Titelthemen vs. Fragmente (N):** Carpenter baut „three, four or five pieces of music that you put in various places“ und nutzt Klangkontinuität statt thematischer Durchführung.\[7\]\[33\] Im Underscoring erscheinen Fragmente, Haltetöne und Stinger; das Fog-Hauptthema sei im Film „only hinted at“ (Musikerkommentar, IMPOSE).\[34\]
- **Wiedererkennbarkeit (I):** Sie hängt am Rhythmus und an der Intervallkontur, nicht am Klang – siehe die Übertragung von Klavier auf Orgel in *Halloween II* und Dr. Dres 4/4-Sample, das trotz Metrumwechsel erkennbar bleibt.\[7\]\[14\]

## 7. Schichtung und zeitliche Entwicklung

**Belegte Schichtmodelle (N):**
1. *Puls + Hand-Zelle + Bass* (Halloween-Haupttitel).
2. *Drone + Stinger*: Für The Fog wurden die Stinger getrennt aufgenommen und über Drone-Spuren gelegt – „that was the drones plus the stingers“ (Howarth, via Larson-Liner-Notes).\[13\]
3. *Hohe Melodie + mittlerer Kontrapunkt + tiefer Bass* (Fog, Carpenter).\[12\]
4. *Rhythmusmaschine + Bassriff + Flächen* (*Assault*, *Escape*).
5. *Glocke/Herzschlag + steigende/fallende Töne* über zehn Minuten (Fog Reel 9).\[12\]
6. *Arpeggio + Antwortmelodie* (Big Trouble; Lost Themes).\[7\]

**Antwort auf die Kernfrage (I):** Veränderung entsteht **primär durch Hinzufügen und Entfernen bestehender Schichten**, sekundär durch Blocktransposition und Registerwechsel, kaum durch neue Noten. Das ist durch die Beschreibung „builds only in texture, but not thematically“ (*Assault*), das additive Halloween-Thema und die getrennt eingespielten Stinger gut gestützt. Die improvisatorische Arbeitsweise („electronic coloring book“, „It's all one big jam“) bestätigt das: Man spielt Schichten gegen das Bild ein, statt eine Form vorzukomponieren.\[41\]

## 8. Musik ohne Hauptmelodie und Gegenstimme (höchste Priorität)

**Befund (I):** Ein großer Teil von Carpenters Underscoring hat keine Melodie im engeren Sinne – Drones, Pulse, Stinger und „almost tones“ (*The Thing*-Cues).\[15\]\[16\] Laut Burnand/Mera ist das Gang-Motiv in *Assault* nur „a held, high synthesizer note“ (Sekundärzitat).\[33\] Melodielosigkeit ist bei Carpenter also **der Normalfall des Underscorings**.

**Identitätsträger ohne HM/GS (E):**
1. **Pedal-Zentrum (LB):** ein Ton, gegebenenfalls mit Oktave, über 16–64 Takte.
2. **Puls (KB oder Rhythmusspur):** Viertel- oder Achtelpuls; Herzschlag-Varianten (lang-kurz).
3. **Zelle (AR):** 2–4 Töne, Quinte/Oktave + ein Halbton; in seltenen, markierten Fällen asymmetrisch gruppiert.
4. **Kalte Fläche (LF):** Quint- oder Oktavklang, optional mit einem Reibungston (♭2 oder ♯4).
5. **Leerraum:** Bei Höhepunkten auf einen einzigen Ton reduzieren statt verdichten.
6. **Register:** Hoch (Glocke/Klavier), Mitte (Zelle), Tief (Pedal) mit deutlichen Lücken dazwischen – Platz für Sprache im Mittenbereich (E: Formantbereich der Stimme freihalten).
7. **Stinger (TU/ST):** einzelne Schläge oder Cluster, nicht synchron zum Puls.

## 9. XYZ-Steuerung: acht Eckbereiche

*X = dunkel→hell, Y = zurückhaltend→kraftvoll, Z = stabil→unruhig. Die Zuordnung zu Carpenter-Verfahren ist I, die Parametrisierung E.*

| X/Y/Z | Charakter | Carpenter-Verfahren | Beispielbezug |
|---|---|---|---|
| 0/0/0 | Dunkle, ruhige Bedrohung | Tiefes Pedal + sporadischer Herzschlag; keine Zelle | Fog-Prolog-Drone; Howarth „hold note“ |
| 0/0/1 | Paranoia (leise) | Pedal + unregelmäßige Einzeltöne/Cluster, Halbtonreibung | *The Thing*-Zusatzcues (Drones, Stinger)\[16\] |
| 0/1/0 | Kraftvoll ohne Hektik | Riffbass in Oktaven, langsamer Puls, Power-Quinten | *Assault*-Hauptthema |
| 0/1/1 | Akuter Horror / bedrohliche Action | Asymmetrische Zelle + Halbtonblockverschiebung + Stinger | Halloween-Haupttitel; „First Chase“ („missed-step“ rhythms)\[42\] |
| 1/0/0 | Kalte, helle Mystery | Hohe Glocke/Klavier über Quintfläche, Kanon („round“) | Fog: Glocken-/Cembalo-„round“\[12\] |
| 1/0/1 | Langsame, hypnotische Spannung (hell) | Hohes Arpeggio über statischem Akkord, Filter langsam | Fog-Hauptthema: „high-end keyboard arpeggios … above a low resonance“ (Larson)\[13\] |
| 1/1/0 | Melancholisch-kraftvoll, heroisch | Thema im Bass, Flächen in Quinten, gerader Groove | *Escape*-Hauptthema |
| 1/1/1 | Mechanische Unruhe | Sequencer-Arpeggio + Drumcomputer + Filterbewegung\[17\] | „Chariots of Pumpkins“ |

**Unabhängig veränderbare Dimensionen (E):** X steuert Registerlage und Reibungsintervall (♭2/Tritonus vs. reine Quinte), nicht Dur/Moll. Y steuert Schichtanzahl, Velocity und Oktavverdopplung, nicht Notendichte. Z steuert Akzentasymmetrie, Stinger-Wahrscheinlichkeit und Transpositionshäufigkeit, nicht Tempo. Melancholie (Laurie-Thema, Fog-Lighthouse) liegt bei mittlerem X, niedrigem Y und niedrigem Z.

## 10. Langfristige Entwicklung bei konstanter XYZ-Position

**Belegbasis (N):** Zehn-Minuten-Cue mit konstantem Grundmuster (Fog Reel 9); Haupttitel mit reiner Texturentwicklung (*Assault*); additiver Aufbau mit Ausblendung (Halloween); Haltetöne über Minuten (Howarth).\[8\]\[12\]

**Ableitung (E):**
- **8 Takte:** Zelle und Puls konstant; höchstens ein Stinger oder ein Velocity-Akzent.
- **16 Takte:** eine Schicht kommt oder geht (z. B. LF ein, TU aus); die Zelle bleibt unverändert.
- **32 Takte:** optionale Blocktransposition der Zelle um einen Halbton (oder Rückkehr); Bass bleibt oder kriecht um einen Schritt.
- **64+ Takte:** „Atemzyklus“ – Reduktion auf Pedal + Puls („stripped back down“), dann Neuaufbau in anderer Reihenfolge; Registerwechsel der Zelle (Oktave).

**Regel gegen Ermüdung (E):** Nie mehr als eine Veränderung pro Ereignispunkt; Zelle und Pedal sind die Anker, alle anderen Rollen rotieren. Keine erzwungene Eskalation: Hinzufügen und Entfernen sind gleich wahrscheinlich, gesteuert durch Y.

## 11. Klangbewegung vs. kompositorische Entwicklung (MIDI-Grenzen)

| Eigenschaft | Relevanz bei Carpenter | Übertragung |
|---|---|---|
| Filter (Cutoff) | Mittel-hoch: „sweep-filtered arpeggiating Prophet synths“ (*Halloween III*)\[17\] | Optional CC74 (Brightness) als langsame Rampe (E) |
| Resonanz | Gering belegt | CC71 optional, standardmäßig aus (E) |
| Hüllkurven | Hoch (Staccato vs. Halteton) | Über Notenlänge/Gate; Rest im Synth |
| LFO / „inner frequency modulations“ | Mittel (*Assault*-Gang-Motiv) | CC1 (Modulation) optional; keine Notentriller zur Simulation |
| Pulsbreitenmodulation | Nicht belegt | Synth-Aufgabe |
| Delay/Hall | Hoch für Produktionsästhetik („cavernous reverb“, *Assault*)\[38\] | Synth/DAW-Aufgabe; keine Echonoten generieren (E) |
| Pitch-Dive/Glide | Vereinzelt (Forumsbeobachtung *Assault*, unbelegt)\[43\] | Pitch-Bend nur als ST-Option (H) |
| Velocity | Hoch (Akzentmuster 3+3+2+2) | Kernparameter in MIDI |

**Grundsatz (E):** Klangbewegung bleibt CC-Aufgabe oder Synth-Aufgabe. Notenwiederholungen zur Simulation von Delay oder LFO sind ausgeschlossen.

## 12. Übertragung auf die neun MIDI-Rollen

| Rolle | Carpenter-Funktion (E) | Pflicht? |
|---|---|---|
| LF | Kalte Quint-/Oktavfläche, gelegentlich Reibungston; sehr lange Noten | Ja |
| KF | Selten: Power-Quint-Stabs, Mollakkord-Pulse (*Halloween III*-Hauptthema) | Optional |
| LB | Pedal/Drone, minutenlang | Ja |
| KB | Herzschlag- oder Riffbass; darf kriechen | Ja |
| AR | Die Zelle (2–4 Töne, Oktave/Quinte/Halbton) | Ja |
| TU | Glocken-/Klaviertupfer, hohe Einzeltöne, Kanon-Echo | Optional |
| ST | Stinger („screeching“, White-Noise-Hits in Fog) – nicht transponierbar | Ja |
| GS | Zweite Zelle im „fast-slow counterpoint“ oder Kanonstimme | Optional |
| HM | Kurze Hook oder lyrische Linie (Fog-Flöte) | Optional |

**Kritische Bewertung (E):** Die neun Rollen reichen. Zwei konkrete Lücken bestehen:
1. **Rhythmusmaschine:** Belegt in *Assault* (rhythm box), Halloween (Moog-Ticken), *Escape* und *Halloween III* (Linn).\[4\]\[17\]\[38\]\[44\] Vorschlag: zuerst prüfen, ob TU als feststehender, nicht transponierter Puls-Generator genügt; nur wenn nicht, eine optionale, nicht transponierbare Rolle „RP – Rhythmus-Puls“ (Drum-Map) ergänzen.
2. **Langsame CC-Rampen:** CC74/CC1 pro Rolle als gemeinsame Fähigkeit, nicht als Carpenter-Sonderfunktion.

**Gemeinsame Engine-Fähigkeiten statt Zweitengine (E):** (a) Zellen-Generator mit fester Intervallkontur und Blocktransposition; (b) Akzentgruppen-Muster (z. B. 3+3+2+2) unabhängig vom Taktmaß; (c) Schicht-Scheduler (Ein/Aus über Taktgrenzen); (d) Pedal-Halter über beliebig viele Takte; (e) Humanisierung pro Rolle, mit „Referenzpuls exakt“-Option.

## 13. Abgrenzung und gemeinsame SYNTH-Fähigkeiten

**Gegenüber Herrmann (I):** Carpenter nennt als Einflüsse „Bernard Herrmann, Bernard Herrmann and Bernard Herrmann. He got the most out of the least means.“\[2\]\[7\] Gemeinsam sind kurze Zellen, Ostinato und Underscoring statt Mickey-Mousing; der Halbtonabstieg im Halloween-Thema wurde von Burnand/Mera als „Herrmannesque“ bezeichnet (Sekundärzitat).\[7\] Der Unterschied: Herrmann arbeitet orchestral-farbig mit chromatischer Akkordik; Carpenter mit Rock-Puls, Maschinenreferenz und Quint/Oktav-Leere.
**Gegenüber Barry (I):** Barry baut auf weit ausgesponnene Melodik und satte Streicherharmonik; Carpenter vermeidet lange Linien und harmonische Wärme.
**Gegenüber Williams (I):** Leitmotivik, funktionale Harmonik und Bildsynchronität – Carpenter nennt Williams ausdrücklich als „mickey-mouse“-Gegenpol.\[7\]

**Universell für spätere SYNTH-Profile (E):** Sequencer-Zellen mit eigenen Periodenlängen (für Tangerine Dream, Jarre), Arpeggiator über gehaltenen Akkorden (Faltermeyer, Hammer), Drumcomputer-Spur, lange Pads mit CC-Bewegung (Vangelis), Velocity-Akzentmuster, Schicht-Scheduler. **Carpenter-spezifisch** bleiben: Halbton-Blocktransposition, Oktav-Wiegen, asymmetrische Akzentgruppen als markierte Ausnahme, Drei-Register-Trennung mit Mittenlücke, Stinger über Drone, Rock/Blues-Riffherkunft, Melodieverzicht.

## 14. Carpenter-spezifische Auswahl- und Verarbeitungsregeln (E, abgeleitet aus N/I)

1. Zelle = 2–4 Töne; erlaubte Intervalle: Oktave, Quinte, Quarte, kleine Sekunde; maximal ein Reibungston.
2. Die Zelle wird nie intervallisch umgebaut, sondern nur blocktransponiert (bevorzugt ±1 Halbton), oktaviert oder umgefärbt.
3. Pedal und Zelle teilen das Tonzentrum; Bass darf um kleine Terz oder Halbton kriechen.
4. Keine Dominant-Tonika-Kadenz; Abschlüsse per Schichtabbau.
5. Pro Ereignispunkt höchstens eine Veränderung.
6. Höchste Dramatik = Reduktion (ein Ton, Stille, Stinger), nicht Verdichtung.
7. Referenzpuls exakt; Handschichten leicht humanisiert.
8. Ungerade Akzentgruppen sparsam und als „Signatur“-Option; Standard ist gerades Metrum.
9. Register streng getrennt; Mittenbereich bei Dialog ausdünnen.
10. Stinger asynchron zum Puls und nie transponiert.

## 15. Priorisierte Empfehlungen für die Vorlagenbibliothek (Phase 2)

1. **Höchste Priorität:** Vorlagen „Pedal + Herzschlag“ und „Pedal + Zelle“ ohne HM/GS (KADAITCHA-Grundbedarf).
2. Zellenkatalog nach Intervallklassen (Oktav-Wiegen, Quint + Halbton, Tritonus-Reibung) mit Blocktranspositionsregeln.
3. Schicht-Scheduler-Profile für 16/32/64 Takte („Atemzyklus“).
4. Stinger-Bibliothek für ST (Cluster, Noise-Hits, hohe Haltetöne).
5. „Fast-slow counterpoint“-Vorlagen AR+GS.
6. Optionale Rhythmus-Puls-Vorlagen (Ticken, Rhythm-Box-Groove).
7. Lyrische Drei-Linien-Vorlagen (hoch/mittel/tief) für Melancholie.
8. Später: Riff-orientierte Vorlagen (*They Live*, *Vampires*) für den POP/ROCK-Modus.

## 16. Offene Fragen und Forschungslücken

- **Primärtexte Donnelly (2010) und Burnand/Mera (2004)** konnten nicht eingesehen werden; Beschaffung per Fernleihe oder über Donnellys Reprint (2023, Kap. 7) ist dringend empfohlen, bevor Tonhöhenregeln finalisiert werden.\[45\]
- **Transpositionsfolge des Halloween-Themas** ist zwischen den Quellen widersprüchlich (Halbtonschritte vs. Quintenzirkel vs. Tonartenliste).
- **Ursprung des „electronic coloring book“:** Electric Sheep datiert es auf *Halloween III*, Howarth beschreibt VHS-Sync bereits ab *Escape*.\[5\]\[17\] Das ist ungeklärt.
- **Zahl und Zuordnung der *The Thing*-Zusatzcues** variiert („four“ bei Filmtracks, „five or six“ bzw. „four or five“ in anderen Aussagen).\[16\]\[41\]
- *Village of the Damned*, *Dark Star* und *Christine* sind analytisch kaum erschlossen; eigene Höranalysen mit dokumentierten Zeitstempeln wären nötig.
- Ob Carpenter je unabhängige Zykluslängen nutzte, bleibt offen; bis zum Gegenbeweis gilt: nicht als Stilregel implementieren.
- Die Wirkung von Carpenter-Grammatik unter Sprache (Hörspiel) ist nicht erforscht; Phase 2 sollte Hörtests mit Dialog einplanen.

## Quellen

1. [John Carpenter's ‘Halloween’ Theme Is the Nightmare From Which You Can’t Wake Up](https://melmagazine.com/en-us/story/john-carpenter-halloween-theme)
2. [The 'Halloween' Theme: What Is It That Makes It So Scary? - Hypebot](https://www.hypebot.com/hypebot/2020/10/the-halloween-theme-what-is-it-that-makes-it-so-scary.html)
3. [Scary Chord Progressions: Why They Sound Wrong on Purpose](https://songcage.com/blog/scary-chord-progressions/)
4. [John Carpenter, Dark Lord of the Film Score](https://www.theringer.com/2023/10/31/music/john-carpenter-film-scores-musician-halloween)
5. [The Sound Lord Speaks: A Conversation with Alan Howarth](https://www.dreadcentral.com/interviews/463891/the-sound-lord-speaks-a-conversation-with-alan-howarth/)
6. [John Carpenter's Escape From New York](https://waxworkrecords.com/collections/all/products/escape-from-new-york)
7. [Patterns And Recurring Themes In The Music Of John Carpenter](https://eprints.nottingham.ac.uk/78100/1/20162496_MUSI4015_2223.pdf)
8. [EXCLUSIVE: And Now, An Interview With HALLOWEEN III Composer Alan Howarth](https://birthmoviesdeath.com/2018/08/29/exclusive-and-now-an-interview-with-halloween-iii-composer-alan-howarth)
9. [The Journal of Kitsch, Camp and Mas Culture](https://aaltodoc.aalto.fi/server/api/core/bitstreams/3f10ce3b-8449-4e5d-bd78-ed372299920d/content)
10. [Full Bibliography - Miguel Mera](http://www.miguelmera.com/bibliography-of-publications/)
11. [FSM Board: Synths used in Assault on Precinct 13?](https://filmscoremonthly.com/board/posts.cfm?threadID=10726&forumID=1&archive=1)
12. [The Fog Soundtrack – The Official John Carpenter](https://theofficialjohncarpenter.com/the-fog-soundtrack/)
13. <https://www.silvascreen.com/wp-content/uploads/TheFog-iTunes-new.pdf>
14. [Halloween II (1981 soundtrack)](<https://en.wikipedia.org/wiki/Halloween_II_(1981_soundtrack)>)
15. [The Thing (1982 soundtrack)](<https://en.wikipedia.org/wiki/The_Thing_(1982_soundtrack)>)
16. [Filmtracks: The Thing (Ennio Morricone)](https://www.filmtracks.com/titles/thing82.html)
17. [Halloween III: Chariots of Pumpkins - Electric Sheep Magazine](http://www.electricsheepmagazine.co.uk/2012/10/15/halloween-iii-chariots-of-pumpkins/)
18. [You Should Be Listening - Crate Digging for the Week of September 12th, 2021 — DJ Dain](https://djdain.com/blog/2021/9/16/you-should-be-listening-crate-digging-for-the-week-of-september-12th-2021)
19. [PRINCE OF DARKNESS \[VINYL\]: Amazon.co.uk: CDs & Vinyl](https://www.amazon.co.uk/PRINCE-DARKNESS-VINYL-JOHN-CARPENTER/dp/B07PFS7563)
20. [NIFFF 2016 – John Carpenter compositeur](https://filmexposure.ch/2016/06/30/nifff-2016-john-carpenter-compositeur/)
21. [Vampires (soundtrack)](<https://en.wikipedia.org/wiki/Vampires_(soundtrack)>)
22. [John Carpenter](https://craftrecordings.com/products/john-carpenter-ghosts-of-mars-original-soundtrack-red-black-vinyl)
23. [Ghosts of Mars (soundtrack)](<https://en.wikipedia.org/wiki/Ghosts_of_Mars_(soundtrack)>)
24. [John Carpenter - Ghost of Mars (2001) - MusicMeter.nl](https://www.musicmeter.nl/album/30449)
25. [John Carpenter Returns with New Album 'Lost Themes IV: Noir' │ Exclaim!](https://exclaim.ca/music/article/john-carpenter-new-album-lost-themes-iv-noir)
26. [John Carpenter Talks Debut Album 'Lost Themes' & Why Music Is Easier Than Directing](https://www.billboard.com/music/music-news/john-carpenter-lost-themes-debut-album-interview-6450980/)
27. [Unearthing Skeletons: John Carpenter on Lost Themes III and Scoring Halloween](https://www.rogerebert.com/interviews/unearthing-skeletons-john-carpenter-on-lost-themes-iii-and-scoring-halloween)
28. [9 Music Production Elements Common in Horror Themes - Blog](https://splice.com/blog/music-production-elements-horror-themes/)
29. [How John Carpenter made (and remade) his game-changing Halloween score](https://www.dazeddigital.com/music/article/41938/1/john-carpenter-halloween-soundtrack-sequel-interview)
30. [John Carpenter, Alan Howarth:... Tracks & Reviews](https://www.allmusic.com/album/escape-from-new-york-original-film-soundtrack-mw0000189820)
31. [Cue By Cue: Film Music Narratives: Halloween (Carpenter, 1978)](https://cuebycue.blogspot.com/2016/07/halloween-carpenter-1978.html?m=1)
32. [John Carpenter was just 13 when he created iconic Halloween score](https://kdhnews.com/living/ae/john-carpenter-was-just-13-when-he-created-iconic-halloween-score/article_d4e92c7b-f6b7-546e-ad16-f89c5d12044c.html)
33. [Assault on Precinct 13 (soundtrack)](<https://en.wikipedia.org/wiki/Assault_on_Precinct_13_(soundtrack)>)
34. [We Ask Musicians: What’s your favorite John Carpenter score? - IMPOSE Magazine](https://imposemagazine.com/bytes/chatter/your-favorite-john-carpenter-score)
35. [Ghosts Of Mars : John Carpenter: Digital Music](https://www.amazon.com/Dismemberment-Blues/dp/B00L8SYOMI)
36. [The Sludgelord: Choice Cuts : Halloween III : Season Of The Witch (Original Soundtrack)](https://thesludgelord.blogspot.com/2013/09/choice-cuts-recommendation-of-week.html)
37. [MOVIES MADE ME: MOVIES MADE ME #44: JOHN CARPENTER'S THE FOG](http://maddrey.blogspot.com/2012/05/movies-made-me-44-fog.html)
38. [John Carpenter: Assault On Precinct 13](https://magazine.waxpoetics.com/rediscovery/john-carpenter-assault-on-precinct-13/)
39. [Director and Composer John Carpenter on Minimalism, Collaboration and Unexpected Second Acts](https://daily.redbullmusicacademy.com/2019/02/john-carpenter-interview/)
40. [The Importance of Music in John Carpenter's Halloween (1978) - Diabolique Magazine](https://diaboliquemagazine.com/the-importance-of-music-in-john-carpenters-halloween-1978/)
41. [Alan Howarth Discusses Working on Film Scores with John Carpenter](https://theultimaterabbit.com/2016/11/16/alan-howarth-discusses-working-on-film-scores-with-john-carpenter/)
42. [John Carpenter: Halloween III: Season of The Witch - maintitles.net](https://www.maintitles.net/reviews/halloween-iii-season-of-the-witch/)
43. [John Carpenter: Assault on Precinct 13 sound - Sound Design Forum - KVR Audio](https://www.kvraudio.com/forum/viewtopic.php?t=361175)
44. [Filmtracks: Escape From New York (John Carpenter/Alan Howarth)](https://www.filmtracks.com/titles/escape_new_york.html)
45. [\[PDF\] The Synergy of Music and Image in Audiovisual Culture by K.J. Donnelly](https://www.perlego.com/book/4310856/the-synergy-of-music-and-image-in-audiovisual-culture-halfheard-sounds-and-peripheral-visions-pdf)
