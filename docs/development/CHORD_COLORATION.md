# Vorlagentreue Akkordfärbung

Ausgangspunkt: `1a58273`, Branch `develop/composition-core-prototype`.
Keine neuen produktiven Wendungen, Akkordtypen, Profile, Parameter oder GUI-Elemente.

## Bestandsaufnahme: Material und Ausgestaltung

| Stelle | Bisherige Wirkung | Einordnung / geschützte Strategie |
|---|---|---|
| `Generator::padType()` | Ab Z=.45 Maj→Maj7 und Min→MinMaj7; ab Z=.75 Min/MinMaj7→MinMaj9. | Änderung der Akkorddefinition; unter Schutz ausgeschlossen. |
| `freeTransition()` / `locate()` / `prepareVoicingPlan()` / `motifHarmonyAt()` / `nextBassPlacement()` | Bei eingeschalteten Durchgängen und Y≥.6 eine Dominante zum Folgeakkord auf dem letzten metrischen Schlag; eigene Lage/Bassanker und kürzere Harmoniefenster. | Eigenständige zusätzliche Harmonie; unter Schutz durch eine gemeinsame Zulassungsentscheidung ausgeschlossen. |
| `riss()` | Ab Z=.8 Halbtoncluster auf dem kurzen Harmonieausgang, unabhängig vom definierten Akkordvorrat. | Zusätzliche harmonische Reibungsfarben; unter Schutz keine Cluster. |
| `tupfer()` / `foreignTone()` | Optionale große None bzw. kleine None/Tritonus und gegebenenfalls weiterer Reibungston. | Tonale Akzentzusätze ohne geplante Auflösung: zusätzliche None nur, wenn definiert; fremde Reibungsfigur entfällt unter Schutz. Feste Stich-Trigger bleiben unverändert. |
| `playArpeggio()` | Akkordbrechung, aber auch freie Riff-/Quart-/oktatonische Figuren, Halbtonnachbarn und chromatische Abschlüsse. | Unter Schutz fällt ein nicht definierter Ton auf das vorhandene Akkordtonraster zurück. Einsatz, Dauer, Dynamik und Figurentakt bleiben erhalten. Keine neue automatische Durchgangstonregel. |
| `buildAnchor()` | Intensität kann eine Grundtonoktave ergänzen; Umkehrung/Registerverteilung; bisher notfalls Tonersatz beim Einpassen in sehr enge Bereiche. | Grundtonverdopplung und Registerausgestaltung bleiben erlaubt; unter Schutz entfällt ein nicht im Register darstellbarer Ton, statt durch eine andere Tonklasse ersetzt zu werden. |
| `planHarmony()` / `voiceleading::lead()` / `leadEntry()` | Lagen verbinden und gemeinsame Töne halten; Bass oktavieren. | Verändern keine Tonklassen eines korrekt gebildeten Ankers. Weiterhin aktiv. |
| `padVoicing()` / `realizeChord()` | Vollständig/reduziert, natürlich/offen; gegebenenfalls Weglassen eines durch den stabilen Bass vertretenen Grundtons oder einer entbehrlichen reinen Quinte. | Ausgestaltung des definierten Materials. Pflichtfarben wie Terz, Septime, Zusatztöne und Sus-Töne bleiben Pflicht; Quint- und Quartstrukturen behalten ihre Struktur. Weiterhin aktiv. |
| `render()` / `BassPhrase` | Bassannäherungen, Durchgänge, motivische Bassfiguren, Orgelpunkte und Slash-Bass-Anker. | Eigenständige Bassausgestaltung, keine Umdefinition der harmonischen Vorlage. Bestehende Zulassungs-/Follow-Regeln bleiben erhalten; Registerersatz wird unter Schutz auch hier nicht erzwungen. |
| `modalContextFor()` / `addPassingTone()` / `planPassingTone()` | Wendungsweiter Modus, geprüfter diatonischer Durchgang mit Akkordtonziel und zeitlich festgelegter Auflösung. | Melodischer Nicht-Akkordton, keine neue Akkordfarbe. Bleibt möglich; das gespeicherte Originalmotiv wird nicht verändert. |
| Linien, Hooks, Motivwiederkehr, Antworten | Melodisches Material und dessen harmonische Anpassung, Phrasierung und Rollenkoordination. | Kein globaler Akkordtonfilter für Melodie/Dialog. Bestehende Verfahren bleiben erhalten. Die Eigenschaft ist keine allgemeine Garantie, dass jeder bestehende melodische Nicht-Akkordton nach der neuen diatonischen Durchgangsregel validiert wurde. |

Intensität verändert weiterhin Stimmenverdopplungen, Anschlag, Aktivität und Bewegung. Sie erzwingt unter Schutz keinen zusätzlichen Akkordtyp. XYZ-Auswahl, Variety, Profilpräferenzen, harmonische Dauer und die rhythmische Koordination bleiben unverändert.

## Datenpfad

Die harmonische Quelle `data/harmony/catalog.json` besitzt ein erforderliches Feld:

```json
"coloration": "flexible"
```

Zugelassen sind ausschließlich `flexible` und `protected`. Unbekannte Werte, fehlende Felder, boolesche Ersatzwerte sowie eine widersprüchliche Definition im Begleitrezept werden abgewiesen. Der frühere, noch nicht wirksame Rezeptplatzhalter `coloration: free` entfällt. Keine doppelte Datenhoheit und keine Kompatibilitätsschicht.

Alle bestehenden 84 Einträge sind ausdrücklich **flexible**. Der Generator schreibt daraus `ChordColoration` in `HarmonyTemplate` und in die zur Compilezeit gebildete `Wendung`-Wiedergabeansicht. Eigene GUI-Akkordfolgen bleiben ohne neue Einstellung flexibel.

`coloredChordType()` enthält exakt die bisherigen Schwellen für die flexible Strategie und liefert bei Schutz den definierten Typ unverändert. `allowsPassingHarmony()` verbindet den vorhandenen Durchgangsschalter mit der Vorlagenvorgabe. Zeitliche Harmoniesuche, Ankerplanung und Bass-Zielsuche verwenden dieselbe Entscheidung; dadurch entstehen auch in Motivfenstern keine nur vermeintlichen Zwischenharmonien.

Der gemeinsame Kern erhält über `ChordIntent::preservePitchClasses` eine harte Tonklassenvorgabe für die Registereinpassung. Nicht darstellbare Klassen werden in `unavailablePadPitchClasses()` weiterhin gemeldet. Der Notenausgang verhindert auch bei anderen geschützten, tonhöhensteuerbaren Figuren einen erzwungenen Registerersatz. Ein fest adressierter Stich-Trigger wird davon nicht harmonisch transponiert.

„Folgt Akkorden“ behält seine Bedeutung: EIN folgt der laufenden Folge einschließlich expliziter Slash-Bass-Anker; AUS verwendet weiterhin den tonalen Bezug am Anfang statt der laufenden Akkorde. Der geschützte Arpeggio-Bezug bewahrt dabei die definierte Anfangsqualität, statt einen Quint-/Sus-Klang zu einem Dur-/Molldreiklang zu vereinfachen. Der Bass behält seine bisherigen unabhängigen Spiel- und Follow-Regeln.

Keine ID-/Künstlersonderfälle, keine Änderungen an Instrumentenfähigkeiten. Alle Daten sind statisch und unveränderlich. Keine zusätzlichen Dateioperationen, Datenvalidierungen oder Heap-Allokationen im Audiothread. Der Farbschutz benötigt konstante Abfragen und höchstens die vorhandenen fünf Akkordintervalle je Tonprüfung.

## Konkrete MIDI-Beispiele

Internationale MIDI-Nummern, deutsche Tonbezeichnungen: H entspricht international B. Synthetische C-Vorlagen, X=.8/Y=.8, Folge C–F/A–B–C (B hier deutsches B = Bb), je zwei Takte. Der Durchgangsschalter ist absichtlich EIN.

| Definierte Farbe | Z | Flexible erste Akkordlage | Geschützte erste Akkordlage |
|---|---:|---|---|
| C-Dur (C/E/G) | .60 | 60,67,76,83,84 = C/G/E/H/C: Maj7-Färbung | 60,67,76,84 = C/G/E/C |
| C-Moll (C/Es/G) | .95 | 60,63,74,79,83,84 = C/Es/D/G/H/C: MinMaj9 | 60,67,75,84 = C/G/Es/C |
| C-MinMaj7 (C/Es/G/H) | .95 | Ergänzung zur Nonenfarbe möglich | 63,67,72,83,84 = Es/G/C/H/C: große Septime erhalten |
| C-Add9 (C/D/E/G) | .95 | Definierter Add9-Typ bleibt erhalten | 62,72,76,79,84 = D/C/E/G/C |
| C5 (C/G) | .95 | Freie Reibungsfiguren können zusätzlich erklingen | 60,67,72,84 = C/G/C/C, ohne ergänzte Terz |

Im zweiten Abschnitt der geschützten Durvorlage F/A werden F/A/C als harmonische Klassen (Maske 545) und A als Bassklasse (Maske 512) geprüft. Mit „Folgt Akkorden“ AUS bleiben der C-Bezug der Harmonie (Maske 145) und der C-Bass (Maske 1) erhalten. Ein expliziter Nicht-Akkordton im Slash-Bass ist dabei bewusst von den Flächentönen getrennt.

Die Maschinenübersicht `CHORD_COLORATION_EXAMPLES.csv` enthält alle 18 Typen, beide Strategien und drei Z-Werte. Tonklassenmasken verwenden Bit 0=C bis Bit 11=H. `defined_mask` ist die unveränderte Quelldefinition, `effective_mask` der effektive Flächentyp; `pad_mask`, `arp_mask` und `bass_mask` sind die tatsächlich erklungenen Klassen des ersten Zweitaktabschnitts, einschließlich gehaltener Flächentöne. Die flexible Flächenmaske enthält dabei bewusst auch Zwischenakkorde und Reibungsakzente. Sie ist deshalb keine bloße Kopie des effektiven Akkordtyps. Die Bassmaske wird separat ausgewiesen; melodische Durchgangstöne sind kein Bestandteil dieser Harmoniemasken.

## Prüfaufbau und Reproduktion

`HarmonyColorationFixtures.py` erzeugt ausschließlich im Buildverzeichnis zusätzliche validierte synthetische Vorlagen und Auswahlprofile. Der produktive Katalog erhält keine zusätzlichen Einträge. Testgewichte wählen gezielt eine Vorlage; gleiche Testanker ermöglichen dabei unabhängige XYZ-Prüfungen. Ein weiterer geschützter Testeintrag übernimmt das bestehende modale Hook-Material 2035, um echte Durchgangstöne und ihre ausgeführte Zielauflösung über 128 Takte zu prüfen.

`HarmonyColorationTests.cpp` prüft 10.368 vollständige Acht-Takt-Matrixrenderings: 18 Typen × zwei Strategien × zwölf Transpositionen × drei Z-Werte × zwei X-Werte × zwei Y-Werte × beide Follow-Zustände. Zusätzlich werden sämtliche konkreten Arpeggiofiguren in Score und Pop/Rock, offene/reduzierte Besetzungen, enge Register, weiterhin wirksames Z, deterministischer Neustart, Seek-/Loop-Transportfolgen, Swing, drei Tempi sowie Blöcke 127/480/512/8192 geprüft. 480 entspricht der bestehenden Exportblockgröße. MIDI-Notenbilanzen werden auf offene bzw. doppelte Noten geprüft.

Für den tatsächlichen Processor-/SMF-Test steht `ProcessorTests --protected-catalog` zur Verfügung. Er verlangt einen vollständig geschützten Testkatalog und vergleicht 36 Fälle (zwei Genres × drei Profile × drei Z-Werte × beide Follow-Zustände), einschließlich Heap-Prüfung und Notenbilanz. Zum Reproduzieren in einer **separaten Repositorykopie** alle 84 `catalog.json`-Einträge auf `protected` setzen, den Katalog generieren, `ProcessorTests` neu bauen und mit diesem Argument ausführen. Der normale Produktionsbuild bleibt flexibel und führt den vorhandenen Processor-Gesamttest ohne Argument aus. Hier wurde der Testkatalog für den Build vorübergehend erzeugt und anschließend vollständig zurückgesetzt; die finale Quelle enthält ausschließlich die 84 flexiblen Einträge.

Die vollständige Regression gegen `1a58273` wird mit `compare_harmony_data.py --baseline 1a58273 --with-passing` ausgeführt. Sie umfasst jede bestehende Wendung in allen drei Profilen, mit Durchgangsschalter EIN/AUS sowie linearem und Seek-/Loop-/Neustart-Transport, jeweils 64 Takte. Somit 1008 Vorher-/Nachher-Vergleiche und 2016 weitere Blockgrößenvergleiche. Die zugehörige Zusammenfassung steht in `CHORD_COLORATION_REGRESSION.json`.

ASan/UBSan: `HarmonyColorationTests --sanitizer` prüft die komplette Typ-/Strategie-/Transpositions-/Z-/Follow-Kombination bei einem X/Y-Paar sowie die zusätzlichen Rand-, Transport- und Modaltests. Die normale Matrix prüft zusätzlich alle X/Y-Kombinationen. Bestehende Engine- und Paketprüfungen ergänzen diese Tests.

## Grenzen und nächster Schritt

- Schutz ist keine neue Harmonie-, Melodie- oder Artikulationsengine. Er garantiert die vorgegebenen harmonischen Klassen, keine bestimmte Klangwirkung eines externen Patches.
- Fehlende Registertöne dürfen entfallen und werden gemeldet; Schutz macht ein ungeeignetes Instrument oder einen unmöglichen Tonumfang nicht spielbar. Eine absichtlich reduzierte Besetzung ist etwas anderes als eine wegen des Registers unvollständige Besetzung.
- Die freie chromatische Reibung der Begleitung wird unter Schutz eingeschränkt. Unruhe wirkt weiterhin über bestehende Muster-/Bewegungsentscheidungen, Bassausgestaltung, Artikulation und gegebenenfalls CCs. Es wurde keine neue Ersatzwirkung für weggefallene Cluster erfunden.
- Melodische Figuren und eigenständiger Bass sind von harmonischen Stimmen zu unterscheiden; ein Nicht-Akkordton dort ist nicht automatisch eine hinzugefügte Akkordfarbe. Eine allgemeine Nachvalidierung aller historischen melodischen Ornamente ist nicht Teil dieses Schritts.
- Die bekannte Beschränkung der Übergangsstimmführung bei kaltem Seek bleibt unverändert. Der deterministische Seek-Verlauf wird geprüft; eine kalte Einstiegslage muss nicht die vorher im linearen Lauf tatsächlich gehörte Lage rekonstruieren.
- Bestehende Eignungsprüfungen von Bassphrasen, rhythmischer Koordination und Akkordbesetzung können beim eingeschalteten Durchgangsschalter weiterhin konservativ auf das bisherige Grundverfahren zurückfallen, auch wenn der Farbschutz den Zwischenakkord verhindert. Diese Regeln wurden nicht zusätzlich verallgemeinert.
- Acht Slots und ganze Takte bleiben erhalten. Keine neuen Modi oder Akkordtypen.

Damit ist der nächste kleine Schritt der einzeln geprüfte Import von H01, H11 und H19 mit geschützter Farbe: H01 passt in fünf Slots (2+2+2+1+1), H11 ebenso, H19 in drei Slots (6+1+1). H01 kann mixolydisch, H11 dorisch validiert werden; bei der terzoffenen Quintfolge H19 darf keine eindeutige Dur-/Mollterz erfunden werden. Quellen-/Basskorrekturen, statische XYZ-Anker und beide Follow-Zustände bleiben separat zu prüfen. Rhythmus-, Motiv- und dramaturgische Gestaltungsanweisungen werden dabei nicht automatisch mitimportiert. Hier wurde keiner dieser Importe begonnen.

Eine musikalische Qualitätsbewertung benötigt weiterhin einen Hörtest.

## Abschlussprüfung

31/31 CTest-Gesamttests bestanden. Die 1008 vollständigen MIDI-Regressionen gegen `1a58273` sowie 2016 weitere Blockgrößenvergleiche waren bytegleich. Der normale Processor-Gesamttest und der separate geschützte Processor-/Export-Test (36 Fälle) sind bestanden. ASan/UBSan für den synthetischen Farbschutztest (2592 Matrixfälle plus Zusatzprüfungen) und den bestehenden Engine-Test ohne Befund; 7/7 Paketprüf-Fixtures bestanden. Linux-VST3 erfolgreich mit dem finalen flexiblen Produktionskatalog gebaut, ELF-/Bundle-/Versionsmetadaten geprüft. Kein Windows-Build, kein pluginval-Lauf und kein Releasepaket in diesem Auftrag.

Im Z-Vergleich entstehen jeweils 164 MIDI-Ereignisse, aber unterschiedliche musikalische Ergebnisse: Es geht hier um weiter wirksame Unruhe, nicht um erzwungene Dichte. Der geschützte modale 128-Takt-Test spielt drei geprüfte Durchgangstöne und alle drei geplanten Zielauflösungen. Zwölf offene Besetzungen werden angenommen, zehn davon reduzieren entbehrliche Bestandteile; ungeeignete Besetzungen fallen auf die vollständige Ausgangslage zurück.
