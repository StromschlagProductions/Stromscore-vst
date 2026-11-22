# STROMSCORE 2.1 – Prüfmethodik und Grenzen

Automatisierte Prüfungen umfassen Bahn-Endpunkte, alle vier Wegpunkte, Kurvenbegrenzung, reproduzierbare Auswertung, Blockgrößen, freie Taktzahlen, einmaliges automatisiertes Ende mit allen Endarten einschließlich Seek und Neustart sowie vorgemerkte Würfe. Prozessorprüfungen umfassen direkte Taktparameter, State-Roundtrip, Alt-Bedienung und die bisherigen MIDI-/CC-/Export-/Legato-/Speicherregressionen.

Vor Release müssen Windows- und Linux-Regressionen sowie Windows pluginval Strictness 8 und die Installations-ZIP-Prüfung erfolgreich sein. Eine tatsächliche musikalische Hörbewertung mit den Zielinstrumenten ist durch diese objektiven Tests nicht ersetzt.

Bedienung, zeitliches Raster und Exportgrenzen: [Release-Hinweise](releases/2.1.md).

Lokal erfolgreich: Engine/VoiceLeading/Processor 3/3; ASan/UBSan 2/2 (lokal ohne LeakSanitizer wegen Sandbox); 7 Tests des Release-/ZIP-Prüfers. Der vollständige Quellstand wird zusätzlich im Windows- und Linux-Release-Lauf geprüft.
