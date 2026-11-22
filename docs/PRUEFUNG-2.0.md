# STROMSCORE 2.0 – Prüfstand des Entwicklungsbuilds

Basis: veröffentlichte 1.9 (`22be37ee755391f3651d7f5718c2e3d302c722ea`). 2.0 ist zunächst ein Testbuild im Entwicklungsbranch, ohne öffentliche Freigabe. Plugin-Kennung und bestehende Parameter-IDs bleiben gleich.

## Lokal objektiv geprüft

- Release-Build: Engine-, VoiceLeading- und Processor-Tests erfolgreich (3/3).
- AddressSanitizer/UndefinedBehaviorSanitizer: Engine und VoiceLeading erfolgreich (2/2; lokal LeakSanitizer wegen der Sandbox deaktiviert).
- Linux-VST3: pluginval Strictness 8 mit abschließendem `SUCCESS`.
- ZIP-/Release-Prüfer: 7 Python-Tests erfolgreich.
- Stimmführung: alle Akkordqualitäten, Tonarten und Register sowie Vergleich mit dem unveränderten 1.9-Quellcode; gemeinsame Töne, Bass, kurze Artikulationen, CCs, Transport und Export.
- Fahrt: alle vier Kurven; Hinfahrt mit geändertem B ohne Positionssprung am Änderungsrasterpunkt; Rückkehr zum ursprünglichen A; Neustart zwischen Rasterpunkten ohne alte Ankunft; Stopp und DAW-Sprünge/Loops.
- Bedienung: links stets A, rechts stets B; manuelle Übernahme beendet Fahrt; B bleibt nach Editor-Neuöffnung und Projektwiederherstellung sichtbar, auch bei unverändertem Standardziel. CC-Zuordnungsnamen einschließlich geteilter Kanäle geprüft.

Die vollständigen Regressionen laufen zusätzlich im Windows- und Linux-Workflow. Der Windows-Workflow prüft VST3-/Binärversion, führt pluginval Stufe 8 aus und validiert das Installationsarchiv auf direkte `Stromscore.vst3`-Struktur, CRC, Windows AMD64 und Versionsangabe. Erst ein vollständig grüner Lauf gilt als geprüfter Windows-Testbuild. Die ZIP samt SHA-256 liegt dann im Artefakt **Stromscore-2.0-Testbuild-Windows** des [Windows-Workflows](https://github.com/StromschlagProductions/Stromscore-vst/actions/workflows/build.yml). Ein Artefakt ist kein öffentliches Release.

## Musikalische Beurteilung

Die fünf MIDI-A/B-Paare zu 1.9 stehen im Vergleichsartefakt. Es wurde hier keine tatsächliche Hörbewertung mit den angeschlossenen Orchesterinstrumenten vorgenommen. Daher keine Aussage, dass die musikalischen Ergebnisse bereits abgenommen oder klanglich überlegen seien. Die musikalische Beurteilung erfolgt vor Merge und Veröffentlichung.

## Grenzen

Die Fahrt bleibt auf dem bisherigen Sechzehntelraster. Große späte Zieländerungen haben weniger Restzeit. Auf der Rückfahrt verändert B nicht das Ziel A. Nach einem DAW-Sprung gilt die kanonische Kurve der aktuellen Parameter; historische manuelle Änderungen werden nicht als versteckte Timeline gespeichert. Für wiederholbare Zielwechsel DAW-Automation verwenden. MIDI-Export beginnt wie bisher eine neue Szene. Phrasierung und Motiventwicklung wurden nicht erweitert.

Details zur Analyse und den Tests: [Stimmführung und Bedienkorrekturen](development/VOICE_LEADING.md).
