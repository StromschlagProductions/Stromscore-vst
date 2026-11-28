# MIDI-/CC-Ausgabe – Anzeige und sicherer Ausschalt-Reset

Stand:28.11.2026. Ergänzung des Herrmann-P1-Korrekturpakets, profil- und betriebsartenübergreifend.

## Bedienung und Zuordnung

Der bestehende „MIDI / CC“-Menübutton zeigt den tatsächlichen APVTS-Parameter `dynamikCc` als Toggle-Zustand. Die vorhandene orange On-Farbe und On-Textfarbe des jeweiligen Themes werden verwendet. Der Button öffnet weiterhin das Menü; er ist kein zusätzlicher Ein-/Ausschalter. Die30-Hz-Anzeigesynchronisation übernimmt auch Automation, Preset- und Projektladung. Beim Öffnen eines Editors wird der aktuelle Zustand sofort gelesen.

Eingangs- und Ausgangscontroller sind verschieden: Die XYZ-Eingänge liegen standardmäßig auf11/1/74. Die **Ausgabe** verwendet `ccOut[0]` für Dynamik (Vorgabe1) und `ccOut[1]` für Ausdruck (Vorgabe11). Diese bestehende Ausgangszuordnung ist umstellbar;0 bedeutet abgeschaltet.

## EIN → AUS

`StromscoreProcessor::processSlice` erkennt den globalen Wechsel auf dem Audio-Pfad. Einmalig werden die zuletzt aktiven Dynamik-/Ausdruckscontroller auf127 gesetzt. In der Standardzuordnung sind das genau CC1=127 und CC11=127. Bei ausdrücklich umbelegten Ausgangscontrollern werden deren Nummern verwendet; keine pauschale Rücksetzung fremder Controller und kein CC121.

Jeder konfigurierte MIDI-Ausgangskanal wird einmal bedient, unabhängig von Mute/Solo und Tonrollen. Mehrfach belegte Kanäle werden dedupliziert. Bei einer gleichzeitig geladenen neuen Kanalzuordnung werden außerdem die zuletzt aktiven eigenen Zielkanäle erreicht, damit die bisher angesteuerten Instrumente nicht auf einem abgesenkten Wert stehenbleiben. Eine identische Controllerzuordnung erzeugt keinen doppelten Reset; deaktivierte Zuordnungen(0) werden nicht gesendet.

Der Reset umgeht die CC-Minimum-/Maximum-Abbildung. Die Parameter und gespeicherten Bereiche werden **nicht** verändert. Solange global AUS bleibt, folgen keine weiteren automatischen Dynamik-/Ausdruckswerte. Bei erneutem EIN beginnt die vorhandene musikalische CC-Steuerung wieder mit den gespeicherten Bereichen und ihrem bisherigen musikalischen Abtastraster.

Der Zustand gehört jeder Prozessorinstanz separat. Er bleibt unabhängig von Generator-Neustart, Vorschau-Generator, Transport und Preset-Flush. Der Reset erfolgt auch bei gestoppter Wiedergabe im nächsten verarbeiteten Audioblock. Host-Bypass oder ein vollständig ruhender Audio-Graph können die Übertragung bis zum nächsten regulären Prozessoraufruf verzögern; außerhalb eines solchen Aufrufs kann das Plugin keine MIDI-Daten an den Host ausgeben. Wechsel, die vollständig zwischen zwei Host-Aufrufen liegen und von der Verarbeitung nie beobachtet werden, erzeugen auch keine zwischenzeitliche automatische CC-Ausgabe.

Bestehende Note-off-/CC123-Sicherungen bei Stop/Bypass bleiben unverändert; sie sind kein neu hinzugefügter Controller-Reset. Das statische MIDI-Exportformat erfindet keine zuvor erfolgten GUI-Umschaltungen.

## Nachweis

`ProcessorCcOutput`:24 Kombinationen aus sechs Profilen, zwei Vokabularmodi und laufendem/gestopptem Transport. Jeweils mehrmaliges EIN/AUS, geteilte Kanäle, Reset127 trotz eingeschränkter Bereiche, Wiederaufnahme der Bereichssteuerung, OFF-Presetladung, unveränderte Bereiche und unabhängige Instanzen. Zusätzlich geänderte Ausgangszuordnung sowie echter Buttonzustand in beiden Themes bei offenem Editor und beim Wiederöffnen. Der Test wartet auf die asynchrone Timer-Synchronisation, statt eine sofortige GUI-Aktualisierung im selben Parameteraufruf vorauszusetzen.
