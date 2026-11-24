# Verbindliche Folgeaufgabe: genreabhängige Komponistenprofile

Nutzervorgabe vom 24. November 2026, ergänzt zum ersten harmonischen Vokabularimport. Diese Aufgabe ist verbindlicher Projektumfang für folgende Entwicklungsschritte, **kein Bestandteil des Imports WC-H01/WC-H11/WC-H19**.

## Gefordertes Ergebnis

- Wang Chung wird ein tatsächlich auswählbares Künstlerprofil im Pop/Rock-Modus.
- Die Künstlerauswahl bietet die für das gewählte Genre geeigneten Profile an: zunächst Score = Neutral, John Barry, Bernard Herrmann; Pop/Rock = Neutral, Wang Chung.
- Neutral bleibt in beiden Genres verfügbar.
- Ein Profilwechsel muss die tatsächlichen musikalischen Entscheidungen erreichen und im Zustand eindeutig abgebildet werden. Sichtbare Menüreihenfolge und stabile interne Profilidentität dürfen nicht verwechselt werden.
- Wang Chung erhält schrittweise eigene musikalische Präferenzen für Harmonik, Rhythmik, Bassführung, Motivik, Stimmführung und musikalische Entwicklung. Eine bloße harmonische Gewichtstabelle oder ein Instrumentenpreset erfüllt das langfristige Ziel nicht.
- Sämtliche Profile verwenden dieselbe gemeinsame Kompositions-Engine. Keine Wang-Chung-Sonderengine und keine duplizierten Motiv-, Bass-, Modus- oder Rhythmusverfahren.
- Kompositionsprofil und Instrumentierung bleiben unabhängig; das Profil soll auch mit Klavier oder orchestralen Instrumenten sinnvoll arbeiten können. Das DAW-Tempo bleibt maßgeblich.
- Profile müssen über das XYZ-Feld unterschiedliche musikalische Situationen bedienen können; keine Reduktion auf eine feste Stimmung oder einen einzelnen Anker.

## Vorhandene Anschlussstellen

`data/harmony/profiles.json` / generierte Profilidentitäten und ID-basierte Harmoniepräferenzen; `Settings.profile`; `CompositionPolicy.h` mit gemeinsamer `FreeCompositionPolicy` und den Bereichen Texture, MotifRecurrence, Hook, Passing, BassPhrase, RhythmCoordination und ChordDisposition. Diese Mechanismen bilden die technische Grundlage. Eine profilabhängige Auswahl vollständiger, tatsächlich verwendeter Policies ist gesondert anzuschließen; aktuell teilen die drei bestehenden Profile die neutrale Kompositionspolicy.

Wendungsinventar und Profile sind getrennte Datenbestände. Die neuen harmonischen IDs 2037–2039 stehen zunächst allen geeigneten Pop/Rock-Profilen ohne Künstlergewichte zur Verfügung; sie werden nicht exklusiv Wang Chung zugeordnet.

## Kleine Folgeaufgaben mit Abnahmekriterien

1. **Genre-Eignung von Profilidentitäten modellieren und validieren.** Neutral für beide Genres, Barry/Herrmann für Score und später Wang Chung für Pop/Rock. Keine Änderung musikalischer Regeln. Tests für eindeutige IDs, ungültige Referenzen, Verfügbarkeit und erhaltene neutrale Policies.
2. **Genreabhängige GUI-Auswahl und Zustandszuordnung anschließen.** Das Menü bildet gefilterte Einträge auf stabile Profilidentitäten ab. Tests für beide Genrewechselrichtungen, sichtbare Auswahl, State/Automation und nicht verfügbare Kombinationen. Ob beim Genrewechsel die letzte genrebezogene Auswahl erinnert oder auf Neutral gewechselt wird, ist vor der Umsetzung ausdrücklich festzulegen. Neutral muss immer erreichbar bleiben.
3. **Wang-Chung-Identität und begrenzte musikalische Präferenzen anschließen.** Nur überprüfte Forschungsergebnisse und geeignetes gemeinsames Vokabular verwenden. Künstlernamen allein gelten nicht als Beleg. Getrennte Tests für Auswahlverteilung/XYZ-Nähe und für tatsächlich unterschiedliche musikalische Ergebnisse.
4. **Weitere Präferenzbereiche einzeln entwickeln.** Rhythmik, Bass, Motivverhalten, Stimmführung und Entwicklung jeweils als kleiner gemeinsamer Policy-Schritt mit messbaren Regeln, Regression, Transport-/Exportgleichheit und anschließender Hörprüfung. Keine pauschale Erhöhung von Dichte oder Motivhäufigkeit als Stilnachweis.

Der aktuelle Import implementiert keinen dieser Folgeschritte und setzt keine Wang-Chung-Profilgewichte. Die bestehende GUI bleibt in diesem Auftrag unverändert.
