# JC – Qualitätsprüfung der Carpenter-Vorlagenbibliothek

*Stand: 27. November 2026 · gilt für STROMSCORE_John_Carpenter_Vokabular_Kanonisch.md, JC_Studien_Ereignisse.csv, JC_Studien_MIDI.zip*

## 1. Verfahren

Alle vier Dateien entstehen aus einem gemeinsamen Python-Datenmodell. Die MIDI-Dateien werden von einem eigenen Schreiber erzeugt und mit einer **unabhängigen Bibliothek (mido)** zurückgelesen. Die zurückgelesenen Noten werden Note für Note mit der CSV verglichen. Die Tonfunktionen werden für jede einzelne Note gegen den in diesem Moment klingenden Klang berechnet.

## 2. Maschinelle Prüfungen

| # | Prüfung | Ergebnis | Details |
|---|---|---|---|
| 1 | MIDI-Rücklesung (mido) stimmt mit CSV überein | bestanden | 54 Dateien, 16046 Noten gelesen, 16046 CSV-Zeilen, Abweichungen in 0 Dateien |
| 2 | Note-on/off-Bilanz | bestanden | offene oder verwaiste Ereignisse: 0 |
| 3 | Spurnamen = Rollenkürzel | bestanden | fehlerhaft: [] |
| 4 | Auflösung 960 PPQ | bestanden | in allen Dateien ticks_per_beat = 960 (assert) |
| 5 | Keine unbeabsichtigten Notenüberlagerungen (gleicher Ton, gleiche Spur) | bestanden | Überlappungen: 0 [] |
| 6 | Stich immer MIDI-Note 36, nie transponiert | bestanden | 15 Stich-Ereignisse in 9 Studien |
| 7 | Rollenregister eingehalten | bestanden | Verstöße: [] |
| 8 | Keine unautorisierte Dissonanz (Funktion X) | bestanden | Verteilung: {'A': 13684, 'U': 324, 'ST': 15, 'T': 1778, 'V': 237, 'F': 8}; X: [] |
| 9 | Jede F/U-Note ist autorisiert (Vorlage, Klang, Dissonanzpedal oder Blocktransposition) | bestanden | F/U-Noten je Studie (Auszug): {'JC-S02': 1, 'JC-S15': 10, 'JC-S17': 67, 'JC-S18': 64, 'JC-S25': 3, 'JC-S29': 130, 'JC-S40': 25, 'JC-EF02': 8, 'JC-EF03': 8, 'JC-EF07': 7, 'JC-EF11': 9} |
| 10 | IDs eindeutig | bestanden | 405 IDs, Duplikate: [] |
| 11 | Querverweise gültig | bestanden | ungültig: [] |
| 12 | Intervallbenennung korrekt (Selbsttest) | bestanden | C♯→F♯ = 5 Halbtöne = Quarte (Korrektur der Vertiefung bestätigt); Tabelle 0–24 geprüft |
| 13 | Alle Klangqualitäten beginnen mit dem Bezugston als Akkordton | bestanden | 33 Qualitäten; Abweichungen: [] |
| 14 | Keine identischen Vorlagen (Inhalt, nicht Name) | bestanden | H:0 R:0 Q:0 B:0 M:0 identische Inhalte |
| 15 | Namen eindeutig je Bibliothek | bestanden | doppelt: [] |
| 16 | Mindestens 50 MIDI-Studien | bestanden | 54 Dateien |
| 17 | Mindestens vier 64-Takt-Studien | bestanden | 13 Studien mit 64 Takten |
| 18 | Erheblicher Teil ohne Arpeggio | bestanden | 33 von 54 ohne AR |
| 19 | Mehrheit ohne HM und GS | bestanden | 33 von 54 ohne HM und GS |
| 20 | Vielfalt ohne obligatorischen Maschinenpuls | bestanden | 23 pulslose Studien |
| 21 | XYZ: jede der 27 Zellen hat ≥ 3 Harmonik- und ≥ 3 Bassvorlagen | bestanden | Lücken: [] |
| 22 | XYZ: alle acht Ecken (0,05/0,95) versorgt (≥ 2 H, R, B) | bestanden | schwach: [] |
| 23 | Mindestdauer 30 Ticks | bestanden | zu kurz: [] |

**Ergebnis:** 23 von 23 Prüfungen bestanden.

**Während der Erstellung gefundene und musikalisch behobene Fehler** (nicht durch automatische Glättung):

- Glocken-Kanonkopf enthielt ♭7 über lydischem/sus2-Klang (JC-S09) → ersetzt durch „Drei Glocken“.
- Herzschlag-Quinte folgte dem verminderten ii° und erzeugte eine reine Quinte außerhalb des Klangs (JC-S32) → bleibt auf dem Grundton.
- Komplementär-Sequenz B folgte einem Durklang mit Molltonfolge (JC-S35) → folgt nicht mehr.
- Zögernde Klavierfigur mit ♭3 über hellem Dur add9 (JC-EF04) → ersetzt durch Quintsprung-Signal.
- Bassregister unter A0 in zwei Studien → Oktave angehoben.
- Akkordpulse (KF) schlugen bei Oktavverdopplungen denselben Ton doppelt an → Tonhöhen je Anschlag eindeutig.
- Drei inhaltsgleiche Harmonievorlagen, je eine in Q und B, und ein doppelter Name → inhaltlich unterschieden bzw. umbenannt.
- XYZ-Lücken in hellen/kraftvollen/unruhigen Bereichen → sieben neue Harmonievorlagen (JC-H081–H087) und begründete Erweiterung einzelner Gültigkeitsbereiche.

## 3. Kennzahlen der Studien

- Studien gesamt (S + EF): **54**
- MIDI-Dateien: **54**
- Ohne Arpeggio (AR): **33**
- Ohne HM und GS: **33**
- Pulslos: **23**
- Repetitiv (mit Puls/Sequenz): **31**
- 64 Takte: **13**
- Melancholisch (X 0,35–0,65, Y ≤ 0,4, Z ≤ 0,3): **7**
- Kraftvoll (Y ≥ 0,7): **10**
- Tonfunktionen aller 16046 Noten: A 13684, T 1778, U 324, V 237, ST 15, F 8

## 4. XYZ-Abdeckung

Anzahl der Vorlagen, deren Gültigkeitsbereich die Zellmitte (0,17 / 0,50 / 0,83) enthält:

| X | Y | Z | H | R | Q | B | M | Studien (nächste Zelle) |
|---|---|---|---|---|---|---|---|---|
| 0,17 | 0,17 | 0,17 | 3 | 8 | 0 | 9 | 2 | 2 |
| 0,17 | 0,17 | 0,50 | 6 | 12 | 5 | 7 | 10 | 4 |
| 0,17 | 0,17 | 0,83 | 4 | 3 | 1 | 6 | 1 | 2 |
| 0,17 | 0,50 | 0,17 | 13 | 13 | 4 | 12 | 4 | 3 |
| 0,17 | 0,50 | 0,50 | 19 | 54 | 42 | 36 | 17 | 8 |
| 0,17 | 0,50 | 0,83 | 13 | 13 | 15 | 15 | 6 | 2 |
| 0,17 | 0,83 | 0,17 | 10 | 8 | 2 | 8 | 1 | 3 |
| 0,17 | 0,83 | 0,50 | 11 | 30 | 29 | 31 | 2 | 1 |
| 0,17 | 0,83 | 0,83 | 6 | 8 | 10 | 13 | 2 | 4 |
| 0,50 | 0,17 | 0,17 | 23 | 8 | 4 | 13 | 20 | 6 |
| 0,50 | 0,17 | 0,50 | 15 | 12 | 9 | 9 | 20 | 4 |
| 0,50 | 0,17 | 0,83 | 5 | 3 | 1 | 5 | 1 | 1 |
| 0,50 | 0,50 | 0,17 | 38 | 13 | 9 | 19 | 20 | 1 |
| 0,50 | 0,50 | 0,50 | 33 | 54 | 52 | 38 | 24 | 3 |
| 0,50 | 0,50 | 0,83 | 8 | 13 | 11 | 12 | 4 | 2 |
| 0,50 | 0,83 | 0,17 | 12 | 8 | 2 | 8 | 1 | 0 |
| 0,50 | 0,83 | 0,50 | 14 | 30 | 34 | 31 | 2 | 2 |
| 0,50 | 0,83 | 0,83 | 3 | 8 | 6 | 11 | 1 | 0 |
| 0,83 | 0,17 | 0,17 | 11 | 8 | 4 | 9 | 9 | 4 |
| 0,83 | 0,17 | 0,50 | 4 | 12 | 8 | 6 | 4 | 2 |
| 0,83 | 0,17 | 0,83 | 3 | 3 | 1 | 4 | 0 | 0 |
| 0,83 | 0,50 | 0,17 | 9 | 13 | 8 | 11 | 10 | 0 |
| 0,83 | 0,50 | 0,50 | 7 | 54 | 24 | 24 | 4 | 0 |
| 0,83 | 0,50 | 0,83 | 5 | 13 | 2 | 8 | 0 | 0 |
| 0,83 | 0,83 | 0,17 | 4 | 8 | 2 | 7 | 1 | 0 |
| 0,83 | 0,83 | 0,50 | 3 | 30 | 12 | 21 | 1 | 0 |
| 0,83 | 0,83 | 0,83 | 3 | 8 | 0 | 8 | 0 | 0 |

**Ecken (0,05 / 0,95):**

| Ecke | H | R | Q | B | M |
|---|---|---|---|---|---|
| 0,05 / 0,05 / 0,05 | 3 | 5 | 0 | 7 | 0 |
| 0,05 / 0,05 / 0,95 | 3 | 3 | 0 | 5 | 0 |
| 0,05 / 0,95 / 0,05 | 4 | 4 | 0 | 4 | 1 |
| 0,05 / 0,95 / 0,95 | 4 | 4 | 5 | 5 | 1 |
| 0,95 / 0,05 / 0,05 | 3 | 5 | 0 | 7 | 3 |
| 0,95 / 0,05 / 0,95 | 2 | 3 | 1 | 3 | 0 |
| 0,95 / 0,95 / 0,05 | 2 | 4 | 0 | 4 | 1 |
| 0,95 / 0,95 / 0,95 | 2 | 4 | 0 | 4 | 0 |

**Zellen ohne eigene Studie:** 9 von 27. Diese werden durch Vorlagen versorgt, nicht durch Beispiel-MIDI. Studien wurden nicht vervielfacht, um die Statistik zu glätten.

## 5. Technische Voraussetzungen

Siehe Abschnitt 14 der Bibliothek. Kritisch für die Umsetzung: Halteton ohne Neuanschlag, mehrstimmige LF bis 5 Stimmen, unabhängiges Pedal mit Autorisierung, Tonfunktionsberechnung ohne Korrektur von F/U, Ereignisfelder mit Abstandsreihe, Schicht-Scheduler. Nicht vorausgesetzt: Percussion-Spur, CC-Daten, zusätzliche Ausgänge.

## 6. Verbleibende Unsicherheiten

- **Keine Höranalyse.** Die Bibliothek beruht auf schriftlichen Quellen. Wie die Studien klingen, wurde nicht gehört; die Prüfungen sind formal (Tonhöhen, Funktionen, Bilanz), nicht ästhetisch. Eine musikalische Abnahme durch Hören bleibt notwendig.
- **Harmonische Belege sind dünn.** Konkrete Akkordfolgen der Underscoring-Cues sind nicht belegt; H4–H6 stützen sich auf wenige Quellen (Crowd-Analyse Escape, Fog-Liner-Notes, Donnelly nur sekundär). Alle Folgen sind E-Konstruktionen.
- **V-Erkennung ist regelbasiert** (Nicht-Akkordton, Folgeton derselben Rolle im Halb-/Ganzton, Akkordton, kurze Dauer). Echte Vorhalte mit Auflösung in anderer Stimme werden als T geführt.
- **T-Töne sind großzügig:** Jeder Modus-Ton gilt als zulässig. In dichten Sequenzen über wechselnden Klängen kann das musikalisch härter klingen als die Kennzeichnung vermuten lässt (z. B. ♭6 über ♭VII).
- **Velocity-Humanisierung fehlt bewusst** in den Studien; das Handspiel-Moment ist Aufgabe der Engine (Regel 7).
- **Hypothesen (H)** wie Phasenzellen, Tritonus-Figuren und modale Farben sind spielbar, aber nicht als Carpenter-Merkmal belegt; sie sind gekennzeichnet und sollten niedrig gewichtet werden.
- **XYZ-Bereiche sind Einschätzungen.** Einige Bereiche wurden in der Prüfung erweitert, um Lücken zu schließen (jeweils musikalisch begründet, z. B. Drone gilt für jede Unruhe). Eine Feinkalibrierung beim Hören ist sinnvoll.
- **Wirkung unter Dialog** ist ungetestet. Testszenen aus KADAITCHA mit Sprache sind der nächste sinnvolle Schritt.
