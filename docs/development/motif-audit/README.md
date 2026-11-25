# Reproduktion der Motivuntersuchung

Stand 9a8d01c; reine Offline-Diagnose, keine produktiven Engineänderungen.
Python 3 und C++17-Compiler genügen; keine externen Python-Pakete.
Aus dem Repository-Stamm, Ausgabeverzeichnis außerhalb des Repositorys wählen:

```bash
python docs/development/motif-audit/run.py --repo "$PWD" --output /tmp/stromscore-motif-audit
python docs/development/motif-audit/summary.py --repo "$PWD" --output /tmp/stromscore-motif-audit
python docs/development/motif-audit/blockcheck.py --output /tmp/stromscore-motif-audit
python docs/development/motif-audit/package.py --repo "$PWD" --output /tmp/stromscore-motif-audit
python docs/development/motif-audit/verify.py --repo "$PWD" --output /tmp/stromscore-motif-audit
```

`run.py` erzeugt 126 Konfigurationen. Alle Läufe werden sowohl direkt gegen
`Source/` als auch mit einem nur lesenden Diagnosezugriff gebaut. Dafür entsteht
im Ausgabeverzeichnis eine Headerkopie mit genau einer zusätzlichen
`friend struct MotifAuditAccess`-Deklaration. Produktivdateien bleiben unberührt.
Jeder vollständige MIDI-Strom beider Programme muss bytegleich sein.
Diagnosevorhersagen werden auf einer Generatorkopie ausgeführt.

Der Harness verwendet den realen `Generator::process()` mit simuliertem Hosttransport;
es handelt sich weder um eine isolierte Transformation noch um einen Studio-One-Test.
Parameterfahrten werden bei festen Sechzehntelgrenzen gesetzt, unabhängig von der
Audioblockgröße. Interne Fahrt bleibt aus. Keine Samplezeit wird durch Diagnoseaufwand
in die Simulation eingerechnet. Die Variante ohne Diagnose gibt den Referenzstrom aus.

`analyze.py` prüft Notenpaare, erfasst eingeführtes Material und gleicht gespeicherte
Rückkehrpläne mit tatsächlichen Note-ons ab. `full_execution` bedeutet vollständige
Ausführung der gewählten Figur, auch wenn diese nur ein Fragment des Originals ist.
Ein als still markierter Plan ist eine geplante Gelegenheit ohne tatsächliche Noten;
beim Pop-Dialog ist insbesondere der Wechsel zwischen motorischer und phrasenbezogener
Verwendung zu beachten. Motorische Neu-Erzeugung zählt nicht als gespeicherte Wiederkehr.
`answers` sind reale Übernahmen einer Materialreferenz, keine aus Notenzahlen erratenen
Frage-Antwort-Beziehungen. Einzelbeispiele werden zusätzlich anhand ihrer Noten geprüft.

`forecast_disagreements` sind Diagnose-Schnappschüsse, keine Fehler pro Note oder
Zeitanteile. `off_chord_onsets` vergleicht mit dem definierten Grundakkord, nicht allen
zulässigen automatischen Färbungen. Diese Zahl allein beweist keine falsche Note.
Das konkrete harmonische Gegenbeispiel im Bericht wurde gesondert geprüft.
`bursts` gruppiert nach mehr als einer Viertel gatefreier Zeit; dies ist ausdrücklich
keine semantische Phrasenerkennung. Materialpublikation wird blockweise beobachtet;
Notenanfänge und -enden entstammen den samplegenauen tatsächlichen MIDI-Ereignissen.

`summary.py` erstellt `enriched.json`. `package.py` schreibt die dokumentierten
Messdaten und das MIDI-ZIP nach `docs/development/`; andere Schritte schreiben nur
in das angegebene Ausgabeverzeichnis. Keine Dateien werden hochgeladen.
Die MIDI-Zweifassungen sind Vollmix und nachträglich gefilterte Stimmen desselben Laufs.
Alle neun Ziele bleiben eigene Spuren und Kanäle; keine Solo-Neukomposition.

Grenzen: 100 BPM, 4/4 als Hauptmatrix, Legato EIN, voreingestellte Tonumfänge,
Seed 0, Variationen 1/3/7. Ergänzende 3/4-, Register-, Tonart-, Szenen- und Solo-
Kontrollen sind keine erschöpfende Prüfung aller Parametersätze. Keine neue
VST3-/Host-Abnahme, kein neuer Live-/Export-Integrationstest und kein Audiohörurteil.

## Wiederkehrprüfung A/B

Der Harness ist auch für den aktuellen Produktionsstand verwendbar. `run.py`
protokolliert dafür Commit, modifizierten Quellstand und SHA256 sämtlicher Header.
Mit `--source-headers /pfad/zum/snapshot` lässt sich dieselbe Messmatrix auf einer
vorherigen Fassung ausführen. Für alle drei Stände dieselbe aktuelle Auswertung
verwenden: Bei Kontextänderungen zählt die zuletzt mit tatsächlich ausgegebenen
Noten verbundene Planfassung, nicht der erste spekulative Cacheeintrag.

```bash
python docs/development/motif-audit/run.py --repo "$PWD" --output /tmp/motif-after
python docs/development/motif-audit/summary.py --repo "$PWD" --output /tmp/motif-after
python docs/development/motif-audit/blockcheck.py --output /tmp/motif-after
python scripts/package_motif_reprise.py --before /tmp/motif-before \
  --stage-a /tmp/motif-stage-a --after /tmp/motif-after --output docs/development
```

`before` = `9a8d01c`, `stage-a` = `b4a5184`; jeweils `run.py` und `summary.py`
ausführen. Das neue Paket enthält 16 MIDI-Dateien aus vier Produktions-A/B-Läufen.
Details, tatsächliche Prozessor-/Exportprüfungen und Grenzen stehen in
`../MOTIF_REPRISE_B.md`. Die ursprüngliche Audit-Anleitung oben beschreibt den
Untersuchungsauftrag vor der Fehlerkorrektur; dessen fehlende Integrationstests
sind keine Aussage über die anschließend separat geprüfte Implementierung.
