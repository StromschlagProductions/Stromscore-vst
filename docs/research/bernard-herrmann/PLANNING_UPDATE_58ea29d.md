# Herrmann – Ergebnis der Planaktualisierung

28.11.2026 · Quellstand `58ea29d` · ausschließlich Analyse/Dokumentation.
Carpenter P1 wartet auf die musikalische Hörabnahme. Kein Build und keine
Veränderung des musikalischen Verhaltens.

Die technische Ausgangslage ist deutlich besser als beim ersten343-ID-Inventar:
Pedalbesitz, gehaltene Oberstimmen, vollständige unabhängige Figurenzyklen,
Basssequenz neben Drone und GS als Begleiter sind vorhanden. Das aktuelle
Herrmann-Profil nutzt davon jedoch noch nichts gezielt: es ist weiterhin ein
Harmoniegewichtungsprofil mit neutraler Policy und ohne HE-Laufzeitpool.

**16 alte Fähigkeitsblockaden sind auf begrenzte Datenanbindung zurückführbar:**
neun fest notierte Parallel-Akkordfolgen, zwei tiefe Pedal-Grundfälle, vier
unabhängige Rhythmuszyklen und ein sparsamer Bassimpuls. Der konservative
Abgleich ergibt34 D-,88 A-,214 E- und7 K-Grundformen. E-Vorlagen haben häufig
bereits nutzbare Teile; ihre entscheidende Restanforderung darf trotzdem nicht
als implementiert gelten. D/A bedeutet nicht bereits spielende Runtime-Vorlage.

Wichtige konkrete Befunde:

- H03 kann über notierte Lagen und verbindliches C ohne MIDI-Neuanschlag verbunden
  werden. H15/H32 brauchen für ihre feste Parallelstruktur keinen neuen Solver.
- B14/B15 sind vollständig speicherbar, ihre7680-Tick-Noten passen aber nicht zum
  Kurz-Bass-Verbraucher. Passenden LB-Linienverbraucher anbinden, keine Gates kürzen.
- B24 benötigt bei3 Tonpositionen gegen16 Einsätze über3Takte einen9-Takt-
  Gesamtzyklus. Die vorhandene Zyklusrechnung kann das; Akkordbezug und Phase
  müssen im HE-Verbraucher korrekt zusammengeführt werden.
- Vorhandene F/U-Freigaben sind keine allgemeine Dissonanzgrammatik. Für Herrmann
  fehlen eine begrenzte quellenbezogene Tonabsicht und der Nachweis von V-Ziel/Frist.
- H64/H68 brauchen ein eigenständiges hohes Pedal mit autorisiertem Fremdton.
  Ein gemeinsamer Akkordton oder der vorhandene tiefe Tonikapedalplan genügt nicht.
- Zwei Sequencer sind keine zwei harmonischen Schichten. Komponentenidentität,
  getrennte Tonbezüge und geplante Verschmelzung fehlen weiterhin. S06 ist mit
  monophoner AR-Brechung grundsätzlich passend; S07 scheitert zusätzlich an der
  notierten KF-Halbe außerhalb der aktuellen Dauerannahme.

**Empfehlung:** ein zusammenhängendes, substanzielles Paket „Herrmann-Klangobjekte,
Pedale und Module“ mit einem geprüften Kandidatenrahmen von47 H-,28 R-,18 B- und
22 M-Grundformen. Das ist eine fachliche Auswahl, keine Importquote oder Zusage
von115 neuen Katalogeinträgen. Vollständige ID-Listen, Voraussetzungen und interne
Prüfgates stehen im [aktualisierten Plan](IMPLEMENTATION_PLAN.md).

Harmonie, Bass, kurze Pulse, hohe Einwürfe, leere Fenster und begrenzte
Wiederaufnahme sollen gemeinsam funktionieren – auch ohne HM/GS und ohne
XYZ-Bewegung. Quellenansichten/Verbraucher im gemeinsamen Kern ergänzen, keine
Herrmann-Kopie des Carpenter-Adapters. Variante C bleibt verbindlich;
Instrumentierung bleibt beim Anwender, die neun Ziele reichen zunächst aus.

Als anschließender eigener Zusammenhang folgen zwei harmonische Komponenten mit
geprüften Register-/Synchronitätszuständen. Ganzton/Hexatonik, hohe/mehrfache
Pedale, konkrete Moduloperationen, pulslose Ereignisfelder, Rollenwanderung und
lange Phrasen bleiben bedarfsgerechte gemeinsame Erweiterungen. Keine Komponente
entfernen, keine beabsichtigte Reibung korrigieren, keine instrumentell ungeeignete
Quelle still umrouten.

Der [maschinenlesbare343-ID-Abgleich](CAPABILITY_REVIEW_58ea29d.json) ergänzt das
unveränderte historische Inventar. Die frühere XYZ-Auswertung wurde nicht als
neuer47er-Pool-Nachweis umetikettiert. Neue Produktions-MIDI-Vergleiche und eine
musikalische Qualitätsaussage gehören erst zur später freigegebenen Umsetzung.
