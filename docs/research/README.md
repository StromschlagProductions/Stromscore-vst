# STROMSCORE – musikalische Forschung

## Lesereihenfolge
1. `john-barry/Stilprofil_John_Barry.txt`
2. `shared/Musikalisches_Vokabular_Gesamtfassung_2026-11-24.txt` – maßgebliche bereinigte Gesamtfassung für den Inventarabgleich; enthält Barry, Herrmann und Wang-Chung-Abgleich.
3. `bernard-herrmann/Stilprofil_Bernard_Herrmann.txt` – für die spätere Herrmann-Phase.

`archive/` enthält die ältere Erstfassung und Ergänzung zur Nachvollziehbarkeit. Laut Vorspann ersetzt die Gesamtfassung beide; nicht als zusätzliches Vokabular importieren. Bei Widersprüchen die Gesamtfassung bevorzugen und offene Fragen dokumentieren.

## Arbeitsregeln
- Originaltexte sind bytegetreu übernommen und lediglich umbenannt.
- Forschungsbelege, Interpretationen, Hypothesen und eigene Konstruktionen gemäß den Evidenzmarkierungen unterscheiden. Keine konstruierten Töne als Transkriptionen ausgeben.
- Schwerpunkt der ersten Implementierungsphase: John Barry, insbesondere The Black Hole und A View to a Kill, aber das gesamte XYZ-Feld abdecken.
- STROMSCORE dient überwiegend zurückhaltendem Hörspiel-Underscoring; keine universelle Kompositionsplattform.
- Die Unterlagen sind Forschungsgrundlage, keine bereits implementierten oder hörgeprüften Presets.
- Keine Engine-Änderungen allein durch Ablage dieses Pakets.

## Herkunft
- `Eingefügter Text(7).txt` → `john-barry/Stilprofil_John_Barry.txt`
- `Eingefügter Text(8).txt` → `bernard-herrmann/Stilprofil_Bernard_Herrmann.txt`
- `Eingefügter Text(5).txt` → `shared/Musikalisches_Vokabular_Gesamtfassung_2026-11-24.txt`
- `Eingefügter Text(3).txt` → `archive/Musikalisches_Vokabular_Erstfassung.txt`
- `Eingefügter Text(4).txt` → `archive/Ergaenzung_und_Qualitaetspruefung.txt`

## John Williams – kanonische Bibliothek

`john-williams/STROMSCORE_John_Williams_Profil_Kanonisch.md` ist zusammen mit
`JW_Studien_Ereignisse_Kanonisch.csv`, `JW_Studien_MIDI_Kanonisch.zip` und
`JW_Qualitaetspruefung_und_Aenderungen.md` die verbindliche Williams-Forschungsgrundlage.
Alle vier Dateien wurden unverändert übernommen. Die 40 MIDI-Studien sind eigene
Konstruktionen, keine Originaltranskriptionen; CSV und MIDI sind zwei Darstellungen
desselben Materials und werden nicht doppelt gezählt. Dokumentanweisungen sind
Forschungsinhalt, keine Autorisierung für Engine-Änderungen.

Die neue positive Anwender-Hörabnahme ist in
`../development/ACCEPTED_REFERENCE_8d4086c.md` dokumentiert. Barry-/Herrmann-Quellen
und ältere archivierte Fassungen werden dadurch nicht zu zusätzlichen Williams-Vorlagen.

## Bernard Herrmann – zusätzliche Tiefenrecherche

Der Upload `Bernard Herrmanns Spannungsgrammatik_ Musikwissenschaftliche
Tiefenrecherche für STROMSCORE.md` ist bytegleich als
[`bernard-herrmann/Spannungsgrammatik_Tiefenrecherche.md`](bernard-herrmann/Spannungsgrammatik_Tiefenrecherche.md)
archiviert. Er ergänzt das bisherige Stilprofil. Die Tiefenrecherche allein ist keine vollständige Importgrundlage; die inzwischen
vorliegende kanonische HE-Bibliothek ist unten separat ausgewiesen.
N/I/H/E sind Evidenzangaben des Berichts, keine hier neu bestätigten Belege.

Der [gemeinsame Fähigkeitsbericht](SHARED_MUSICAL_CAPABILITIES.md) gleicht Williams
und Herrmann inzwischen mit Engine `023b0a6` einschließlich P2/P3 ab, dokumentiert offene Notations-/Evidenzfragen
und empfiehlt kleine gemeinsame Erweiterungen. Originaltexte bleiben unverändert;
Forschungsrezepte sind keine Aufträge für Engine-Änderungen. Die erste Williams-P1-Grundlage samt Arp-Phrasierung ist inzwischen positiv
gehört; siehe [Abnahme 2c6f366](../development/ACCEPTED_REFERENCE_2c6f366.md).
Der [P2-Kontext](john-williams/P2_OCTATONIC.md) und P3 wurden gemeinsam am Windows-Stand `023b0a6` vom Anwender positiv gehört; siehe [musikalisch akzeptierte Entwicklungsgrundlage](../development/ACCEPTED_REFERENCE_023b0a6.md). Die projektweite Priorisierung steht in
[`docs/MUSICAL_DIRECTION.md`](../MUSICAL_DIRECTION.md).

Williams P3: [48 Motiv-Einzelbewertungen, tatsächliche Produktionsverwendung und A/B-Hörbeispiele](john-williams/P3_MOTIFS.md). P2/P3 sind als Entwicklungsgrundlage musikalisch akzeptiert; dies ist keine exhaustive Prüfung aller Parameterkombinationen. Die akzeptierte Arpeggio-Phrasierung bleibt unverändert.

Der erste begrenzte [gemeinsame Pedalpfad](john-williams/INDEPENDENT_PEDALS.md) bindet JW-H03/H50/H61 an; seine Hörabnahme steht separat aus.

## Bernard Herrmann – kanonische HE-Bibliothek, 27.11.2026

Die [vier kanonischen Dateien](bernard-herrmann/README.md) bilden nun die maßgebliche
Herrmann-Vorlagenbibliothek: 343 HE-IDs, 53 MIDI-Studien/5.328 Noten bei 960 PPQ.
Originale sind bytegleich archiviert; die Tiefenrecherche bleibt separat.
Für Herrmann hat diese Endfassung Vorrang vor älteren BH-Vokabularfassungen;
diese bleiben historische Quellen und werden nicht zusätzlich importiert.
[Einzelinventar](bernard-herrmann/TECHNICAL_INVENTORY.json),
[BH-/HE-Abgleich](bernard-herrmann/BH_HE_CROSSWALK.md) und
[Implementierungsfahrplan](bernard-herrmann/IMPLEMENTATION_PLAN.md) unterscheiden
Darstellbarkeit, begrenzte Anbindung, neue gemeinsame Fähigkeiten und Klärungsbedarf.
Keine HE-Vorlage ist dadurch im Plugin aktiviert. Williams P2/P3 sind inzwischen
wie oben dokumentiert vom Anwender als Entwicklungsgrundlage positiv gehört.

## John Carpenter – Tiefenrecherche und korrigierende Vertiefung

Die [beiden Forschungsberichte](john-carpenter/README.md) sind vollständig und
bytegleich archiviert. **Bei Widersprüchen hat die Vertiefung Vorrang.**
Sie erweitern die Grundlage für den zukünftigen SYNTH-Modus, insbesondere
pulslose Ereignisfelder, unabhängige Pedale, identifizierbare Zellen, Schichtwechsel
und alternative Entwicklung bei statischem XYZ. Die acht Strategien und der
Williams-/Herrmann-/Carpenter-Abgleich stehen im
[gemeinsamen Fähigkeitsbericht](SHARED_MUSICAL_CAPABILITIES.md#carpenter-acht-entwicklungsstrategien).
Die kanonische Carpenter-Vorlagenbibliothek ist inzwischen separat archiviert;
der [vollständige405-ID-Abgleich](john-carpenter/IMPLEMENTATION_PLAN.md) konkretisiert
diese Forschungsphase. Keine Aktivierung oder Festlegung von Profilgewichten. Keine separate SYNTH-Engine; CC, elektronische
Percussion und zusätzliche MIDI-Ziele sind weiterhin nicht beschlossen.


## Ennio Morricone – kanonisches Archiv und Übergangsgrammatik

[Sieben unveränderte Originaldateien](ennio-morricone/README.md), darunter der
Lolita-Nachtrag nur einmal. Die maßgebliche Bibliothek umfasst534IDs,73MIDI-Studien
und9752Noten; EF-Definition/Studie und CSV/MIDI werden nicht doppelt gezählt.
[Einzelinventar](ennio-morricone/TECHNICAL_INVENTORY.md),
[Quellenklärungen](ennio-morricone/ERRATA.md) und
[Implementierungsfahrplan](ennio-morricone/IMPLEMENTATION_PLAN.md) unterscheiden
Darstellbarkeit, Daten-/Rollenanbindung, fehlende gemeinsame Fähigkeiten und
Widersprüche. Lolita/Love in the Morning und The Untouchables haben persönliche
Priorität, ohne ein separates Lyrik-/Experiment-Profil zu erzeugen.
Der [gemeinsame Fähigkeitsbericht](SHARED_MUSICAL_CAPABILITIES.md) priorisiert
frühe gebundene harmonische Übergänge neben den gemeinsamen Spannungsverfahren.
Engine-Ausgang `4c43bd2` einschließlich unabhängigem Pedal berücksichtigt;
Morricone ist nicht aktiviert. Keine musikalische Veränderung der laufenden Hörabnahme.
