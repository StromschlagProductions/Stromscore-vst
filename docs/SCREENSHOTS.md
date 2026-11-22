# Reproduzierbare Screenshots

Die Aufnahmen ab 2.1 zeigen auch eine Beispielroute mit Wegpunkten und den Endschalter.

Die PNGs werden aus der echten JUCE-Oberfläche erzeugt, einschließlich der aus `VERSION`
kompilierten Versionsanzeige und einem gesetzten Wiedergabezustand (zweiter Akkord, einzelne
Ebenen leuchten). Keine nachträglich ersetzten Versionsziffern.

Am einfachsten über GitHub: Actions > **Screenshots erzeugen** > Run workflow. Der Lauf nimmt beide
Looks und die Dialoge auf: eigene Akkordfolge, Tonumfang, Stich, CC-Bereiche und Wendungsinfo (insgesamt sieben PNGs). Dazu kommt `docs/screenshots.json`.

Lokal:

```sh
cmake -S . -B build
cmake --build build --config Release --target StromscoreScreenshot
# Windows:
build/StromscoreScreenshot_artefacts/Release/StromscoreScreenshot.exe <absoluter-Pfad-zum-docs-Ordner>
```

Unter Linux benötigt das Werkzeug eine X11-Sitzung (z. B. Xvfb); der ausführbare Name
hat dort kein `.exe`. Es nutzt die echte Message-Loop und schreibt Aufnahmen mit
zweifacher Pixelauflösung. Theme und Beispielparameter betreffen ausschließlich die
lokale Screenshot-Instanz, keine Plugin-Defaults oder gespeicherten Nutzerprojekte.

`docs/screenshots.json` enthält die einkompilierte Version und die erzeugten PNG-Dateien.
Diesen Eintrag nicht manuell hochsetzen. Vor Veröffentlichung prüft der Workflow die
Übereinstimmung mit `VERSION` und das Vorhandensein aller aufgeführten Bilder. Das Manifest
wird zusammen mit den PNGs als Release-Asset angehängt. Stromscore erhält dadurch keine Homepage-Karte und bleibt vom Gesamtbundle ausgeschlossen.
