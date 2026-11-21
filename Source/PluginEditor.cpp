#include "PluginEditor.h"
#include <BinaryData.h>

namespace
{
juce::String u8 (const char* s) { return juce::String (juce::CharPointer_UTF8 (s)); }

const char* kLayerTitle[stromscore::kNumLayers] = { "FLÄCHE", "BASS", "ARP", "FARBE", "GEGENSTIMME" };
const char* kLayerTip[stromscore::kNumLayers] = {
    "Akkorde: gehalten, als kurze Schläge oder im Puls.",
    "Grundton der Akkorde in verschiedenen Mustern, von gehalten bis Funk.",
    "Gebrochene Akkorde und Figuren, auch als Ostinato.",
    "Einzelne hohe Töne über dem Akkord. Bei Unruhe auch Töne außerhalb der Tonart.",
    "Ruhige Linie aus langen Tönen, die schrittweise von Akkord zu Akkord geht, zum Beispiel für Horn, Cello oder Oboe." };
const char* kLayerLines[stromscore::kNumLayers] = {
    "", "", "",
    "Hoher Ton über dem Akkord, bei Unruhe ein fremder, reibender Ton in der Mitte des Akkords",
    "Ruhige Linie aus langen Tönen, bewegter mit mehr Intensität, bei Unruhe mit Vorhalten" };
}

// ---------------------------------------------------------------- Stimmungsfeld

void MoodPad::paint (juce::Graphics& g)
{
    auto r = getLocalBounds().toFloat();
    g.setColour (panel);
    g.fillRoundedRectangle (r, 8.0f);
    g.setColour (line);
    g.drawRoundedRectangle (r.reduced (0.5f), 8.0f, 1.0f);

    const auto a = r.reduced (10.0f);
    g.setColour (line.withAlpha (0.6f));
    for (int i = 1; i < 4; ++i)
    {
        g.fillRect (a.getX() + a.getWidth() * (float) i / 4.0f - 0.5f, a.getY(), 1.0f, a.getHeight());
        g.fillRect (a.getX(), a.getY() + a.getHeight() * (float) i / 4.0f - 0.5f, a.getWidth(), 1.0f);
    }

    // Ecken: die vier Grundstimmungen
    g.setColour (dim);
    g.setFont (juce::FontOptions (11.0f));
    const int pad = 6;
    const auto ai = a.toNearestInt().reduced (pad);
    g.drawText (u8 ("Angst"), ai, juce::Justification::topLeft);
    g.drawText (u8 ("Triumph"), ai, juce::Justification::topRight);
    g.drawText (u8 ("Lauern"), ai, juce::Justification::bottomLeft);
    g.drawText (u8 ("Ruhe"), ai, juce::Justification::centredBottom);
    g.drawText (u8 ("Wärme"), ai, juce::Justification::bottomRight);

    // Punkt mit Unruhe-Ring: groesser und zittriger mit mehr Unruhe
    const float px = a.getX() + x * a.getWidth();
    const float py = a.getBottom() - y * a.getHeight();
    const float radius = 9.0f + z * 24.0f;
    const float amp = z * 0.22f;
    const float phase = (float) (juce::Time::getMillisecondCounter() % 100000) * 0.004f * (0.3f + z);
    juce::Path ring;
    for (int i = 0; i <= 64; ++i)
    {
        const float t = juce::MathConstants<float>::twoPi * (float) i / 64.0f;
        const float rr = radius * (1.0f + amp * std::sin (7.0f * t + phase) + amp * 0.5f * std::sin (13.0f * t - 1.7f * phase));
        const juce::Point<float> p (px + rr * std::cos (t), py + rr * std::sin (t));
        if (i == 0) ring.startNewSubPath (p); else ring.lineTo (p);
    }
    ring.closeSubPath();
    g.setColour (accent.withAlpha (0.12f + 0.18f * z));
    g.fillPath (ring);
    g.setColour (accent.withAlpha (0.85f));
    g.strokePath (ring, juce::PathStrokeType (1.5f));
    g.setColour (accent);
    g.fillEllipse (px - 6.0f, py - 6.0f, 12.0f, 12.0f);

    // Feld-Karte: beim Ueberfahren die naechstgelegenen Wendungen, klein und blass
    if (numHover > 0 && ! dragging)
    {
        g.setFont (juce::FontOptions (10.0f));
        for (int i = 0; i < numHover; ++i)
        {
            const float hx = a.getX() + hover[i].x * a.getWidth(), hy = a.getY() + (1.0f - hover[i].y) * a.getHeight();
            g.setColour (text.withAlpha (i == 0 ? 0.75f : 0.45f));
            g.fillEllipse (hx - 2.0f, hy - 2.0f, 4.0f, 4.0f);
            const float tw = 96.0f;
            const float tx = juce::jlimit (a.getX(), a.getRight() - tw, hx - tw * 0.5f);
            g.drawText (hover[i].name, juce::Rectangle<float> (tx, hy + 3.0f, tw, 12.0f), juce::Justification::centred);
        }
    }
}

// ---------------------------------------------------------------- Akkord-Anzeige

void ChordDisplay::paint (juce::Graphics& g)
{
    auto r = getLocalBounds().toFloat();
    g.setColour (panel);
    g.fillRoundedRectangle (r, 6.0f);
    g.setColour (line);
    g.drawRoundedRectangle (r.reduced (0.5f), 6.0f, 1.0f);

    const int w = getWidth();
    g.setColour (playing ? text : dim);
    g.setFont (juce::FontOptions (30.0f, juce::Font::bold));
    g.drawText (playing ? chord : u8 ("–"), 14, 8, w - 28, 38, juce::Justification::centredLeft);
    g.setColour (dim);
    g.setFont (juce::FontOptions (11.0f));
    g.drawText (meter, 14, 12, w - 28, 16, juce::Justification::centredRight);
    if (playing && nextChord.isNotEmpty())
    {
        g.setFont (juce::FontOptions (13.0f));
        g.drawText (u8 ("dann ") + nextChord, 14, 28, w - 28, 16, juce::Justification::centredRight);
        g.setColour (line);
        g.fillRoundedRectangle (14.0f, 46.0f, (float) w - 28.0f, 2.0f, 1.0f);
        g.setColour (accent.withAlpha (0.8f));
        g.fillRoundedRectangle (14.0f, 46.0f, ((float) w - 28.0f) * juce::jlimit (0.0f, 1.0f, progress), 2.0f, 1.0f);
    }
    g.setColour (accent);
    g.setFont (juce::FontOptions (13.0f, juce::Font::bold));
    g.drawText (playing ? (custom ? wendung : u8 ("Wendung: ") + wendung) : u8 ("Wiedergabe starten oder VORHÖREN einschalten"), 14, 52, w - 28, 18, juce::Justification::centredLeft);

    // Woraus VARIATION an dieser Stelle waehlt
    if (candidates.isNotEmpty())
    {
        g.setColour (dim);
        g.setFont (juce::FontOptions (11.0f));
        g.drawFittedText (u8 ("Hier: ") + candidates, 14, getHeight() - 80, w - 28, 16, juce::Justification::centredLeft, 1, 0.85f);
    }

    // Stimmung live: Faerbung, Intensitaet, Unruhe in Prozent mit schmalem Balken
    {
        const char* names[3] = { "Färbung", "Intensität", "Unruhe" };
        const float top = (float) getHeight() - 62.0f, labelW = 74.0f, valueW = 42.0f;
        for (int i = 0; i < 3; ++i)
        {
            const float yy = top + (float) i * 18.0f;
            g.setColour (dim);
            g.setFont (juce::FontOptions (11.0f));
            g.drawText (u8 (names[i]), juce::Rectangle<float> (14.0f, yy, labelW, 16.0f), juce::Justification::centredLeft);
            const juce::Rectangle<float> bar (14.0f + labelW, yy + 6.0f, (float) w - 28.0f - labelW - valueW - 6.0f, 4.0f);
            g.setColour (line);
            g.fillRoundedRectangle (bar, 2.0f);
            g.setColour (accent);
            g.fillRoundedRectangle (bar.withWidth (juce::jmax (4.0f, bar.getWidth() * juce::jlimit (0.0f, 1.0f, mood[i]))), 2.0f);
            g.setColour (text);
            g.drawText (juce::String (juce::roundToInt (mood[i] * 100.0f)) + " %", juce::Rectangle<float> ((float) w - 14.0f - valueW, yy, valueW, 16.0f),
                        juce::Justification::centredRight);
        }
    }

    // Akkorde der Wendung als Chips
    if (playing && numChips > 0)
    {
        const float gap = 6.0f;
        const float cw = ((float) w - 28.0f - gap * 3.0f) / 4.0f;
        for (int i = 0; i < numChips; ++i)
        {
            const juce::Rectangle<float> c (14.0f + (float) (i % 4) * (cw + gap), 76.0f + (float) (i / 4) * 28.0f, cw, 24.0f);
            const bool on = i == current;
            g.setColour (on ? accent : line);
            if (on) g.fillRoundedRectangle (c, 5.0f); else g.drawRoundedRectangle (c.reduced (0.5f), 5.0f, 1.0f);
            g.setColour (on ? juce::Colours::black : text);
            g.setFont (juce::FontOptions (12.0f, juce::Font::bold));
            g.drawFittedText (chips[i], c.toNearestInt().reduced (2, 0), juce::Justification::centred, 1, 0.8f);
        }
    }
}

// ---------------------------------------------------------------- Ebene

void LayerView::paint (juce::Graphics& g)
{
    auto r = getLocalBounds().toFloat();
    g.setColour (panel);
    g.fillRoundedRectangle (r, 8.0f);
    g.setColour (line);
    g.drawRoundedRectangle (r.reduced (0.5f), 8.0f, 1.0f);

    g.setColour (active ? accent : dim);
    g.setFont (juce::FontOptions (12.0f, juce::Font::bold));
    g.drawFittedText (title, 12, 8, (int) r.getWidth() - 92, 16, juce::Justification::centredLeft, 1, 0.75f);

    const juce::Rectangle<float> lamp (r.getWidth() - 26.0f, 10.0f, 12.0f, 12.0f);
    g.setColour (line);
    g.fillEllipse (lamp);
    if (activity > 0.02f)
    {
        g.setColour (accent.withAlpha (juce::jlimit (0.0f, 1.0f, activity)));
        g.fillEllipse (lamp);
    }

    g.setColour (dim);
    g.setFont (juce::FontOptions (11.0f));
    g.drawText (u8 ("MIDI-Kanal ") + juce::String (channel) + (entry.isNotEmpty() ? u8 (" · ") + entry : juce::String()),
                12, 28, (int) r.getWidth() - 24, 14, juce::Justification::centredLeft);
    if (lines.isNotEmpty())
    {
        g.setColour (active ? text : dim);
        g.setFont (juce::FontOptions (11.5f));
        g.drawFittedText (lines, 12, 50, (int) r.getWidth() - 24, (int) r.getHeight() - 116, juce::Justification::topLeft, 4, 1.0f);
    }
}

// ---------------------------------------------------------------- Eigene Akkordfolge

void SlotPanel::paint (juce::Graphics& g)
{
    auto r = getLocalBounds().toFloat();
    g.setColour (panel);
    g.fillRoundedRectangle (r, 8.0f);
    g.setColour (accent);
    g.drawRoundedRectangle (r.reduced (0.5f), 8.0f, 1.5f);

    g.setColour (accent);
    g.setFont (juce::FontOptions (13.0f, juce::Font::bold));
    g.drawText (u8 ("EIGENE AKKORDFOLGE"), 16, 12, 300, 18, juce::Justification::centredLeft);
    g.setColour (dim);
    g.setFont (juce::FontOptions (12.0f));
    g.drawText (u8 ("Bis zu acht Akkorde mit Grundton, Art und Länge. Plätze mit „–“ werden übersprungen, danach beginnt die Folge von vorn."),
                16, 32, getWidth() - 32, 18, juce::Justification::centredLeft);
    const int cw = (getWidth() - 32 - 7 * 8) / stromscore::kMaxChords;
    g.setFont (juce::FontOptions (11.0f, juce::Font::bold));
    for (int i = 0; i < stromscore::kMaxChords; ++i)
        g.drawText (juce::String (i + 1), 16 + i * (cw + 8), 66, cw, 16, juce::Justification::centred);
    g.setColour (text);
    g.setFont (juce::FontOptions (12.0f));
    g.drawText (totalText, 16, getHeight() - 42, getWidth() - 170, 28, juce::Justification::centredLeft);
}

// ---------------------------------------------------------------- Farben

StromscoreEditor::Theme StromscoreEditor::darkTheme()
{
    return { juce::Colour (0xff182326), juce::Colour (0xff233539), juce::Colour (0xfff5781a),
             juce::Colour (0xffe8ecec), juce::Colour (0xff8fa1a5), juce::Colour (0xff35494e), true };
}
StromscoreEditor::Theme StromscoreEditor::lightTheme()
{
    return { juce::Colour (0xffd5dbda), juce::Colour (0xffe8eae9), juce::Colour (0xfff5781a),
             juce::Colour (0xff233539), juce::Colour (0xff5d6e72), juce::Colour (0xffb5bfbe), false };
}

// ---------------------------------------------------------------- Hilfe

static juce::AttributedString buildHelp (juce::Colour text, juce::Colour accent, juce::Colour dim)
{
    juce::AttributedString s;
    s.setWordWrap (juce::AttributedString::byWord);
    s.setJustification (juce::Justification::topLeft);

    auto head = [&] (const char* t) { s.append (u8 (t) + "\n", juce::Font (juce::FontOptions (14.0f, juce::Font::bold)), accent); };
    auto body = [&] (const char* t) { s.append (u8 (t) + "\n\n", juce::Font (juce::FontOptions (13.0f)), text); };
    auto bold = [&] (const char* t) { s.append (u8 (t), juce::Font (juce::FontOptions (13.0f, juce::Font::bold)), text); };
    auto note = [&] (const char* t) { s.append (u8 (t) + "\n\n", juce::Font (juce::FontOptions (12.0f)), dim); };

    s.append (u8 ("Hilfe · v") + juce::String (PLUGIN_VERSION_TEXT) + "\n\n", juce::Font (juce::FontOptions (17.0f, juce::Font::bold)), accent);

    head ("Was das Plugin macht");
    body ("Es erzeugt Musik für Untermalung und gibt sie als MIDI auf fünf Kanälen aus: Fläche, Bass, Arp, Farbe und Gegenstimme. Alle Ebenen sind tonal gedacht, für tongebende Instrumente; Schlagwerk gehört nicht dazu. Die Klänge kommen aus deinen eigenen Instrumenten. Die Noten sind als Ausgangspunkt gedacht, den du weiter bearbeitest. Es läuft im Takt des Projekts: Wiedergabe starten, springen oder loopen, und es spielt an der richtigen Stelle weiter. Gleiche Einstellungen ergeben immer dieselben Noten.");

    head ("Woher die Musik kommt");
    bold ("Es verwendet keine KI. ");
    body ("STROMSCORE arbeitet mit festen Regeln, nicht mit trainierten Modellen und nicht mit fremdem Material. Die Grundlage ist der Stil, den Lars Eickstädt über Jahre für seine Hörspiele entwickelt hat, geprägt von großen Filmkomponisten und der Musik klassischer Hörspiele. Daraus ist ein Vorrat an Wendungen entstanden: Akkordfolgen, Figuren und Rhythmen. Je nach Stimmung zieht das Plugin daraus. Melodien bekannter Stücke werden nicht nachgebaut.");

    head ("Einrichten in Studio One");
    body ("1. Lege eine Instrumentenspur mit Stromscore an. 2. Lege für jede Ebene, die du hören willst, eine Instrumentenspur mit deinem Instrument an. 3. Stelle bei jeder dieser Spuren als Eingang Stromscore ein und wähle den MIDI-Kanal (Fläche 1, Bass 2, Arp 3, Farbe 4, Gegenstimme 5). 4. Schalte die Spuren auf Monitor. Zum Weiterarbeiten nimmst du die Ausgabe einfach auf diesen Spuren auf.");
    note ("Ohne eigene Instrumente hörst du mit VORHÖREN einen einfachen Testklang direkt aus dem Plugin.");

    head ("Das Stimmungsfeld");
    body ("Ziehe den Punkt durch das Feld. Waagerecht ist die FÄRBUNG: links dunkel (Bedrohung, Trauer, Lauern), rechts hell (Wärme, Staunen, Triumph). Senkrecht ist die INTENSITÄT: unten ruhig und dünn, oben aufgewühlt und dicht. Unten in der Mitte liegt RUHE, der neutrale Ausgangspunkt. Färbung, Intensität und Unruhe stehen rechts in der Akkord-Anzeige laufend in Prozent.");
    body ("Mit dem Mausrad über dem Feld (oder per Controller) änderst du die dritte Achse, die UNRUHE. Sie zeigt sich als Ring um den Punkt: Je größer und zittriger, desto mehr Reibung, Dissonanz, Halbtöne und verschobene Betonungen. Bei wenig Intensität sind es einzelne fremde Töne, bei viel Intensität kratzt der ganze Satz.");
    body ("Alle drei Achsen lassen sich automatisieren. So fährst du durch eine Szene: langsam vom Lauern in die Panik und am Ende in die Erlösung.");

    head ("Genre: Score oder 80er Pop-Rock");
    body ("Die beiden Knöpfe neben STIMMUNG wählen das Vokabular. Score enthält die Wendungen für Filmmusik, von Lauern bis Triumph, orchestral und mit 80er-Synth-Farben. 80er Pop-Rock enthält Powerchord-Riffs, Hi-NRG- und Galopp-Bass, SID-Arpeggios, gehackte Flächen und Hymnen-Wendungen wie ♭VI – ♭VII – I. Das Stimmungsfeld funktioniert in beiden gleich: links dunkel, rechts hell, oben aufgewühlt. Alle anderen Funktionen bleiben, auch die eigene Folge, die dann den Pop-Rock-Stil leiht.");
    body ("Im Pop-Rock spielt die Gegenstimme eine durchgehende, gleichbleibende Hook-Linie in Achteln, bei wenig Intensität in Vierteln. Welche Figur, bestimmt VARIATION.");

    head ("WECHSEL");
    body ("Bewegst du den Punkt deutlich, wechselt die Wendung am nächsten Wechselpunkt: am nächsten Schlag (Vorgabe), am nächsten Takt, alle 2 oder alle 4 Takte. Die neue Wendung beginnt dort mit ihrem ersten Akkord. Gehaltene Töne der alten Stimmung enden genau am Wechselpunkt, der Arp läuft im Takt weiter und spielt gleich die neuen Akkordtöne. Kleine Bewegungen lösen keinen Wechsel aus, solange die laufende Wendung noch gut zur Lage passt; die Ebenen reagieren trotzdem sofort auf Intensität und Unruhe.");

    head ("Controller (CC)");
    body ("Stromscore hört auf seinem MIDI-Eingang auf drei Controller: CC 11 für die Färbung, CC 1 für die Intensität und CC 74 für die Unruhe. Das passt zu einem Fader-Controller, wie er für Orchester-Instrumente üblich ist. Gib der Stromscore-Spur den Controller als Eingang und nimm die Fader-Bewegungen als MIDI-Part auf. Über den Knopf mit den CC-Nummern kannst du die Zuordnung ändern oder einzelne Achsen abschalten.");

    head ("Wendungen und Akkorde");
    body ("Rechts oben steht der klingende Akkord, darunter die Wendung und ihre Akkorde. Eine Wendung dauert acht Takte. Welche Wendung kommt, hängt vom Punkt im Feld ab: An jeder Stelle kommen die Wendungen in Frage, die dort gut passen. Sie stehen in der Akkord-Anzeige unter „Hier“, die passendste zuerst. Die Akkorde stehen mit deutschen Notennamen (H statt B); ein Schrägstrich zeigt einen eigenen Basston, etwa D/C.");
    body ("VARIATION bestimmt, welcher dieser Kandidaten in welcher Phrase drankommt und welche der bevorzugten Figuren und Bass-Muster er spielt. Die Stimmung bleibt dabei gleich, nur das Arrangement ändert sich; gleiche Nummer, gleiches Ergebnis. ABWECHSLUNG legt fest, wie viele Kandidaten es gibt: ganz links spielt immer nur die passendste Wendung, weiter rechts mischen sich auch entferntere Nachbarn hinein.");
    body ("Der Vorrat umfasst 48 Wendungen: von Lauern, Trauer, Unruhigem Schlaf und Grusel über Verfolgung, Sog, Achse, Ermittlung, Geheimnis, Wurmloch, Fremde Orte, Synth-Nächte und Funk bis zu Schneelinien, Gleiten, Offenen Quinten, Sehnsucht, Romantik, Terrassen, Erhabenem, Heiterkeit, Western, Abenteuer, Erhebung, Fanfare und Triumph.");

    head ("Eigene Folge");
    body ("Mit EIGENE FOLGE spielt Stromscore deine Akkorde statt der Wendungen. Über „Bearbeiten“ legst du bis zu acht Akkorde fest, jeweils mit Grundton, Art (Dur, Moll, maj7, m7, 7, sus4, sus2, add9, m6, m(maj7), m7b5, dim7, +) und Länge in Takten. Die Grundtöne gelten unabhängig von TONART. Vorgabe ist F – C – B – G mit je 2 Takten. Die Akkorde bleiben fest, alles andere bestimmt weiter das Stimmungsfeld: Die Färbung leiht den Stil der Wendung, die am Punkt im Feld liegt, also ihre Figuren, Bass-Muster und den Rhythmus der Fläche. So spielt deine Folge zum Beispiel mit Funk-Bass und Riff oder mit Walking Bass, je nachdem, wohin du den Punkt ziehst. Welcher Stil gerade gilt, steht in der Akkord-Anzeige. Intensität und Unruhe wirken wie sonst. VARIATION wählt bei eigener Folge außerdem die Lage der Fläche: weit, eng oder ohne tiefen Grundton.");

    head ("TONART, TAKT, VARIATION, SWING");
    body ("TONART legt den Grundton fest. TAKT übernimmt die Taktart aus dem Projekt oder legt sie fest (4/4, 3/4, 6/8, 5/4, 7/8, 5/8, 12/8); ungerade Takte bekommen eigene Betonungsgruppen, etwa 3+3+2+2 im 5/4. VARIATION wählt eine von sechzehn Kombinationen aus Wendungen und Figuren; gleiche Nummer, gleiches Ergebnis. SWING verschiebt die Zwischen-Achtel nach hinten, bis zum Triolen-Gefühl.");

    head ("Die fünf Ebenen");
    body ("Jede Ebene hat ihren MIDI-Kanal und eine Lampe, die bei jedem Ton leuchtet. Daneben liegen S (Solo) und M (Mute): Mute lässt die Ebene schweigen, Solo lässt nur die Solo-Ebenen spielen, auch mehrere gleichzeitig. So kannst du zum Beispiel nur mit dem Bass oder nur mit einer Fläche beginnen.");
    body ("Fläche und Bass spielen immer, die anderen Ebenen setzen mit der Intensität ein: Arp ab 25 %, Farbe ab 40 % oder bei Unruhe, Gegenstimme ab 15 %. Ab wann eine Ebene gerade einsetzt, steht neben ihrem MIDI-Kanal, etwa „ab 25 %“ oder „immer“. Der Regler INTENSITÄT unten in jedem Kasten verschiebt die Intensität nur für diese Ebene. In der Mitte folgt sie dem Feld. Weniger macht sie dünner, beim Bass bis zu langen Tönen. Mehr macht sie dichter, beim Bass bis zu durchgehenden Achteln auf einem Ton; die Ebene setzt dann auch bei ruhiger Stimmung ein. Die übrigen Ebenen bleiben dabei, wie das Feld sie vorgibt. Doppelklick setzt den Regler auf die Mitte.");

    head ("Muster");
    body ("Fläche: Gehalten, Schläge (kurze Akkorde auf der Zwischenzeit), Puls (auf jedem Schlag), Staccato (kurz auf jedem Schlag) oder Gated (gehackte Achtel). Bass: Gehalten, Halbe, Viertel, Achtel, Puls (durchgehende Sechzehntel auf einem Ton), Funk (synkopiert, mit kurzem Sprung nach oben am Taktende), Pendel (Grundton und kleine Terz, bei Unruhe Halbton), Walking (Akkordtöne in Vierteln, chromatisch zum nächsten Grundton), Wechselbass (Grundton und Quinte im Wechsel), Herzschlag (doppelter Schlag, wie ein Puls), Arpeggio (Akkordtöne in Achteln), Orgelpunkt (liegt auf dem Grundton der Wendung, während die Akkorde darüber wandern), Hi-NRG (Grundton und Oberoktave im Wechsel) oder Galopp (Achtel und zwei Sechzehntel). Arp: Aufwärts, Abwärts, Kreisend (auf und ab), Zelle (kurze, obsessive Figur), Riff, Glitzern (schnell und hoch), Sprünge (weite Dreiklangs-Sprünge), Kaskade (Harfen-Wellen in Dreiergruppen), Oktatonisch (Läufe auf der Halbton-Ganzton-Leiter), Quarten (gestapelte Quarten als Ostinato) oder SID (Dreiklang in Sechzehnteln wie auf dem C64); das Tempo wählst du darunter. Auf Auto folgt das Muster der Wendung.");

    head ("Nächster Akkord und Feld-Karte");
    body ("Rechts oben in der Akkord-Anzeige steht der nächste Akkord, darunter läuft eine dünne Leiste bis zum Wechsel. Fährst du mit der Maus über das Stimmungsfeld, ohne zu klicken, erscheinen klein die Wendungen, die dort am nächsten liegen.");

    head ("MIDI herausziehen");
    body ("Das Feld MIDI neben VORHÖREN ziehst du auf deine DAW: Es entsteht eine MIDI-Datei mit den nächsten Takten, eine Spur je Ebene, mit allen aktuellen Einstellungen. Stumme Ebenen bleiben leer, mit Solo ziehst du also auch einzelne Ebenen heraus. Ein Klick auf das Feld wechselt die Länge zwischen 8, 16 und 32 Takten. Ist die Dynamik eingeschaltet, sind die Dynamikkurven mit in der Datei.");

    head ("Dynamik per CC");
    body ("Im Menü des CC-Knopfs schaltest du unter „Ausgabe an die Spuren“ die Dynamik ein. Dann bekommt jede Ebene CC 1 (Dynamik) und CC 11 (Ausdruck), wie es Orchester-Libraries erwarten; beide Nummern lassen sich dort ändern oder abschalten. Der Grundwert folgt der Intensität, darauf liegen atmende Bögen von einem bis vier Vierteln, im Score weiter und bei Unruhe mit einem Akzent beim Akkordwechsel, im Pop-Rock fast flach. Das ist getrennt von den Controllern am Eingang: Dein Controller bewegt das Stimmungsfeld, die Ausgabe geht an deine Instrumente. Für Synth-Klänge lässt du die Dynamik besser aus, weil CC 1 dort oft ein Vibrato steuert.");

    head ("Gegenstimme");
    body ("Die fünfte Ebene ist eine ruhige Linie aus langen Tönen, gedacht für Horn, Cello, Oboe oder ein Lead-Instrument. Sie geht schrittweise auf Akkordtönen von Akkord zu Akkord, bevorzugt Terz und Septime und meidet den Ton der Farbe, damit sich nichts doppelt. In dunkler Färbung neigt sie nach unten, in heller nach oben. Bei wenig Intensität wechselt sie nur mit den Akkorden, bei mehr alle zwei Takte, aufgewühlt in Halben. Bei Unruhe kommt sie mit einem Vorhalt von oben in den Akkord. Die Töne überlappen minimal, damit Legato-Instrumente sie gebunden spielen. Sie ist keine fertige Melodie, sondern ein roter Faden für deine eigene.");

    head ("Durchgänge");
    body ("Mit DURCHGÄNGE erklingt bei viel Intensität (ab 60 %) auf dem letzten Schlag eines Akkords kurz die Dominante des nächsten Akkords. Das zieht in den Wechsel hinein. Es gilt für Wendungen und eigene Folge und lässt sich jederzeit abschalten.");

    head ("Satz der Fläche");
    body ("Die Fläche ist weit gesetzt wie im Orchester: Grundton und Quinte unten, Terz und Farbtöne eine Oktave höher, bei viel Intensität mit Verdopplung oben.");

    head ("Oktave");
    body ("Jede Ebene hat ihre eigene Oktavlage: Normal, eine oder zwei Oktaven höher oder tiefer. So passt du die Lage an deine Instrumente an, ohne die Noten zu verändern.");

    head ("Folgt den Akkorden / bleibt");
    body ("Bei Fläche, Bass und Arp bestimmt dieser Schalter, ob die Ebene den Akkordwechseln folgt oder auf dem Grundakkord der Tonart bleibt. Ein Arp, der bleibt, läuft unverändert durch, während sich Fläche und Bass bewegen. Ein Bass, der bleibt, hält den Grundton unter wechselnden Akkorden.");

    head ("VORHÖREN");
    body ("Ein einfacher Testklang im Plugin, damit du ohne eigene Instrumente hörst, was entsteht. Das geht auch bei stehender DAW: Ist VORHÖREN an und die Wiedergabe gestoppt, läuft Stromscore mit eigener Uhr im Projekttempo. Dabei klingt nur der Testklang, an deine Instrumentenspuren geht kein MIDI. Startest du die Wiedergabe, übernimmt der Takt des Projekts. Für die fertige Musik schaltest du VORHÖREN aus.");

    head ("Allgemein");
    body ("Doppelklick auf einen Drehregler oder Strg-Klick setzt ihn auf den Standardwert zurück. Look: Dunkel / Hell umschalten, die Wahl wird mit dem Projekt gespeichert. Das Fenster ist am rechten unteren Rand skalierbar (50–300 %).");
    note ("Bei Stopp, Sprung, Reset oder Bypass werden alle klingenden Noten beendet, zusätzlich geht auf jedem Kanal ein „Alle Noten aus“ hinaus. Das Ergebnis hängt nur von der Projektposition ab, nicht von der Puffergröße.");

    head ("Idee und Konzept");
    body ("Lars Eickstädt, Stromschlag Audio");
    note ("Gebaut mit JUCE.");
    return s;
}

// ---------------------------------------------------------------- Editor

StromscoreEditor::StromscoreEditor (StromscoreProcessor& p) : AudioProcessorEditor (&p), processor (p)
{
    addAndMakeVisible (content);
    setResizable (true, true);
    setResizeLimits (kBaseW / 2, kBaseH / 2, kBaseW * 3, kBaseH * 3);
    if (auto* c = getConstrainer())
        c->setFixedAspectRatio ((double) kBaseW / (double) kBaseH);

    logo = juce::ImageCache::getFromMemory (BinaryData::logo_png, BinaryData::logo_pngSize);
    theme = processor.uiTheme.load() == 1 ? lightTheme() : darkTheme();
    setLookAndFeel (&look);

    auto label = [this] (juce::Label& l, const juce::String& t, juce::Justification j)
    {
        l.setText (t, juce::dontSendNotification);
        l.setJustificationType (j);
        content.addAndMakeVisible (l);
    };
    label (padLabel, u8 ("STIMMUNG"), juce::Justification::centredLeft);
    label (keyLabel, "TONART", juce::Justification::centredLeft);
    label (meterLabel, "TAKT", juce::Justification::centredLeft);
    label (variationLabel, "VARIATION", juce::Justification::centredLeft);
    label (swingLabel, "SWING", juce::Justification::centredLeft);
    label (chordLabel, "AKKORD", juce::Justification::centredLeft);
    label (changeLabel, "WECHSEL", juce::Justification::centredLeft);
    label (customLabel, "AKKORDE", juce::Justification::centredLeft);

    // Stimmungsfeld: Faerbung und Intensitaet als ein Zug, Unruhe per Mausrad
    for (int a = 0; a < 3; ++a)
        axisAttachment[a] = std::make_unique<juce::ParameterAttachment> (*processor.apvts.getParameter (StromscoreProcessor::kAxisIds[a]),
            [this, a] (float v)
            {
                (a == 0 ? pad.x : a == 1 ? pad.y : pad.z) = v;
                pad.repaint();
            }, nullptr);
    pad.onDragStart = [this] { axisAttachment[0]->beginGesture(); axisAttachment[1]->beginGesture(); };
    pad.onDrag = [this] (float nx, float ny) { axisAttachment[0]->setValueAsPartOfGesture (nx); axisAttachment[1]->setValueAsPartOfGesture (ny); };
    pad.onDragEnd = [this] { axisAttachment[0]->endGesture(); axisAttachment[1]->endGesture(); };
    pad.onWheel = [this] (float dz) { axisAttachment[2]->setValueAsCompleteGesture (juce::jlimit (0.0f, 1.0f, pad.z + dz)); };
    pad.onHover = [this] (float hx, float hy)
    {
        auto st = processor.currentSettings();
        st.x = hx; st.y = hy; st.variety = 1.0f;
        int c[3];
        const int n = stromscore::Generator::candidates (st, c, 3);
        pad.numHover = n;
        for (int i = 0; i < n; ++i)
        {
            const auto& wd = stromscore::wendungAt (st.genre, c[i]);
            pad.hover[i] = { juce::String (juce::CharPointer_UTF8 (wd.name)), wd.x, wd.y };
        }
        pad.repaint();
    };

    // Genre: Score oder 80er Pop-Rock
    genreScore.setButtonText ("Score");
    genrePop.setButtonText ("Pop-Rock");
    for (auto* b : { &genreScore, &genrePop }) { b->setRadioGroupId (77); content.addAndMakeVisible (b); }
    genreAttachment = std::make_unique<juce::ParameterAttachment> (*processor.apvts.getParameter ("genre"),
        [this] (float v)
        {
            const bool pop = juce::roundToInt (v) == 1;
            genreScore.setToggleState (! pop, juce::dontSendNotification);
            genrePop.setToggleState (pop, juce::dontSendNotification);
        }, nullptr);
    genreScore.onClick = [this] { genreAttachment->setValueAsCompleteGesture (0.0f); };
    genrePop.onClick = [this] { genreAttachment->setValueAsCompleteGesture (1.0f); };
    genreAttachment->sendInitialUpdate();
    genreScore.setTooltip (u8 ("Vokabular für Filmmusik: Wendungen von Lauern bis Triumph, orchestral und mit 80er-Synth-Farben."));
    genrePop.setTooltip (u8 ("Vokabular für 80er Pop-Rock: Powerchords, Hi-NRG- und Galopp-Bass, SID-Arpeggios, gehackte Flächen, eine durchgehende Hook-Linie. Alle anderen Funktionen bleiben gleich."));

    // MIDI herausziehen
    midiDrag.render = [this] { return processor.renderMidiFile (processor.exportBars.load()); };
    midiDrag.onClick = [this]
    {
        const int now = processor.exportBars.load();
        processor.exportBars.store (now == 8 ? 16 : now == 16 ? 32 : 8);
        processor.updateHostDisplay (juce::AudioProcessorListener::ChangeDetails{}.withNonParameterStateChanged (true));
        updateMidiLabel();
    };
    content.addAndMakeVisible (midiDrag);
    updateMidiLabel();
    for (auto& a : axisAttachment) a->sendInitialUpdate();
    content.addAndMakeVisible (pad);


    variation.setSliderStyle (juce::Slider::IncDecButtons);
    variation.setTextBoxStyle (juce::Slider::TextBoxLeft, false, 60, 24);
    content.addAndMakeVisible (variation);
    variationAttachment = std::make_unique<APVTS::SliderAttachment> (processor.apvts, "variation", variation);

    swing.setSliderStyle (juce::Slider::LinearHorizontal);
    swing.setTextBoxStyle (juce::Slider::TextBoxRight, false, 50, 20);
    content.addAndMakeVisible (swing);
    swingAttachment = std::make_unique<APVTS::SliderAttachment> (processor.apvts, "swing", swing);

    keyBox.addItemList (StromscoreProcessor::keyNames(), 1);
    meterBox.addItemList (StromscoreProcessor::meterNames(), 1);
    content.addAndMakeVisible (keyBox);
    content.addAndMakeVisible (meterBox);
    keyAttachment = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, "key", keyBox);
    meterAttachment = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, "takt", meterBox);

    label (varietyLabel, "ABWECHSLUNG", juce::Justification::centredLeft);
    variety.setSliderStyle (juce::Slider::LinearHorizontal);
    variety.setTextBoxStyle (juce::Slider::TextBoxRight, false, 50, 20);
    content.addAndMakeVisible (variety);
    varietyAttachment = std::make_unique<APVTS::SliderAttachment> (processor.apvts, "abwechslung", variety);
    variety.setTooltip (u8 ("Wie viele passende Wendungen sich abwechseln. Ganz links: immer nur die passendste. Weiter rechts: auch entferntere Nachbarn. Welche gerade in Frage kommen, steht in der Akkord-Anzeige unter „Hier“."));

    changeBox.addItemList (StromscoreProcessor::changeNames(), 1);
    content.addAndMakeVisible (changeBox);
    changeAttachment = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, "wechsel", changeBox);

    // Eigene Akkordfolge
    customButton.setClickingTogglesState (true);
    customButton.setButtonText ("Eigene Folge");
    content.addAndMakeVisible (customButton);
    customAttachment = std::make_unique<APVTS::ButtonAttachment> (processor.apvts, "eigeneFolge", customButton);
    editButton.setButtonText (u8 ("…"));
    editButton.setName ("Bearbeiten");
    passingButton.setButtonText (u8 ("Durchgänge"));
    passingButton.setClickingTogglesState (true);
    content.addAndMakeVisible (passingButton);
    passingAttachment = std::make_unique<APVTS::ButtonAttachment> (processor.apvts, "durchgaenge", passingButton);
    passingButton.setTooltip (u8 ("Bei viel Intensität (ab 60 %) erklingt auf dem letzten Schlag eines Akkords kurz die Dominante des nächsten Akkords, als Durchgang. Gilt für Wendungen und eigene Folge."));
    editButton.onClick = [this] { slots.setVisible (! slots.isVisible()); if (slots.isVisible()) slots.toFront (false); };
    content.addAndMakeVisible (editButton);
    for (int i = 0; i < stromscore::kMaxChords; ++i)
    {
        const juce::String n (i + 1);
        slots.root[i].addItemList (StromscoreProcessor::slotRootNames(), 1);
        slots.type[i].addItemList (StromscoreProcessor::slotTypeNames(), 1);
        slots.bars[i].addItemList (StromscoreProcessor::slotBarNames(), 1);
        slotAttachment[3 * i] = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, "slotRoot" + n, slots.root[i]);
        slotAttachment[3 * i + 1] = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, "slotType" + n, slots.type[i]);
        slotAttachment[3 * i + 2] = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, "slotBars" + n, slots.bars[i]);
        slots.root[i].setTooltip (u8 ("Grundton des Akkords (unabhängig von TONART)."));
        slots.type[i].setTooltip (u8 ("Art des Akkords."));
        slots.bars[i].setTooltip (u8 ("Länge in Takten. „–“ lässt den Platz aus."));
    }
    slots.doneButton.setButtonText ("Fertig");
    slots.doneButton.onClick = [this] { slots.setVisible (false); };
    slots.setVisible (false);
    content.addChildComponent (slots);

    ccButton.onClick = [this] { showCcMenu(); };
    content.addAndMakeVisible (ccButton);
    updateCcButton();

    previewButton.setButtonText (u8 ("Vorhören"));
    previewButton.setClickingTogglesState (true);
    content.addAndMakeVisible (previewButton);
    previewAttachment = std::make_unique<APVTS::ButtonAttachment> (processor.apvts, "preview", previewButton);
    content.addAndMakeVisible (chordDisplay);

    // Ebenen
    for (int i = 0; i < stromscore::kNumLayers; ++i)
    {
        auto& lv = layers[i];
        lv.title = u8 (kLayerTitle[i]);
        lv.lines = u8 (kLayerLines[i]);
        lv.channel = i + 1;
        lv.index = i;
        lv.octBox.addItemList (StromscoreProcessor::octaveNames(), 1);
        lv.octBox.setTooltip (u8 ("Oktavlage dieser Ebene."));
        octaveAttachment[i] = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, "oct" + juce::String (i + 1), lv.octBox);
        lv.resized();   // Lage des Oktav-Felds haengt von der Ebene ab
        lv.setTooltip (u8 ("MIDI-Kanal ") + juce::String (i + 1) + ": " + u8 (kLayerTip[i]));
        const juce::String n (i + 1);
        lv.soloButton.setButtonText ("S");
        lv.muteButton.setButtonText ("M");
        lv.soloButton.setClickingTogglesState (true);
        lv.muteButton.setClickingTogglesState (true);
        lv.soloButton.setTooltip (u8 ("Solo: nur diese Ebene spielt (mehrere Ebenen können gleichzeitig solo sein)."));
        lv.muteButton.setTooltip (u8 ("Mute: diese Ebene schweigt."));
        soloAttachment[i] = std::make_unique<APVTS::ButtonAttachment> (processor.apvts, "solo" + n, lv.soloButton);
        muteAttachment[i] = std::make_unique<APVTS::ButtonAttachment> (processor.apvts, "mute" + n, lv.muteButton);
        lv.intensity.setSliderStyle (juce::Slider::LinearBar);
        lv.intensity.setTextValueSuffix ("");
        intensityAttachment[i] = std::make_unique<APVTS::SliderAttachment> (processor.apvts, "intensitaet" + n, lv.intensity);
        lv.intensity.textFromValueFunction = [] (double v)
        {
            const int p = juce::roundToInt (v * 100.0);
            return u8 ("Intensität ") + (p > 0 ? juce::String ("+") : p < 0 ? u8 ("−") : u8 ("±")) + juce::String (std::abs (p)) + " %";
        };
        lv.intensity.updateText();
        lv.intensity.setDoubleClickReturnValue (true, 0.0);
        lv.intensity.setTooltip (u8 ("Intensität nur für diese Ebene, zusätzlich zum Stimmungsfeld. Mitte: wie das Feld. Weniger: dünner, bis zu langen Tönen. Mehr: dichter, bis zu durchgehenden Achteln; die Ebene setzt dann auch bei ruhiger Stimmung ein. Doppelklick: Mitte."));
        if (i < 3)
        {
            lv.followButton.setVisible (true);
            lv.followButton.setClickingTogglesState (true);
            lv.followButton.onStateChange = [this, i]
            { layers[i].followButton.setButtonText (layers[i].followButton.getToggleState() ? u8 ("folgt den Akkorden") : u8 ("bleibt auf Grundakkord")); };
            lv.followButton.setTooltip (u8 ("Ein: die Ebene folgt den Akkordwechseln. Aus: sie bleibt auf dem Grundakkord der Tonart, zum Beispiel ein durchlaufender Arp oder ein Bass auf dem Grundton."));
            followAttachment[i] = std::make_unique<APVTS::ButtonAttachment> (processor.apvts, "follow" + juce::String (i + 1), lv.followButton);
            lv.combo1.setVisible (true);
        }
        content.addAndMakeVisible (lv);
    }
    layers[0].combo1.addItemList (StromscoreProcessor::padPatternNames(), 1);
    layers[1].combo1.addItemList (StromscoreProcessor::bassPatternNames(), 1);
    layers[2].combo1.addItemList (StromscoreProcessor::arpFigureNames(), 1);
    layers[2].combo2.addItemList (StromscoreProcessor::arpRateNames(), 1);
    layers[2].combo2.setVisible (true);
    patternAttachment[0] = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, "padPattern", layers[0].combo1);
    patternAttachment[1] = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, "bassPattern", layers[1].combo1);
    patternAttachment[2] = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, "arpFigure", layers[2].combo1);
    patternAttachment[3] = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, "arpRate", layers[2].combo2);
    layers[0].combo1.setTooltip (u8 ("Muster der Fläche. Auto: wie es zur Wendung passt."));
    layers[1].combo1.setTooltip (u8 ("Muster des Basses. Auto: wie es zur Wendung passt, sehr ruhig gehalten, sehr aufgewühlt mindestens Achtel."));
    layers[2].combo1.setTooltip (u8 ("Figur des Arps. Auto: wie es zur Wendung passt."));
    layers[2].combo2.setTooltip (u8 ("Tempo des Arps. Auto: ruhig Viertel, mittel Achtel, aufgewühlt Sechzehntel."));

    themeButton.onClick = [this]
    {
        theme = theme.dark ? lightTheme() : darkTheme();
        processor.uiTheme.store (theme.dark ? 0 : 1);
        processor.updateHostDisplay (juce::AudioProcessorListener::ChangeDetails{}.withNonParameterStateChanged (true));
        applyTheme();
    };
    content.addAndMakeVisible (themeButton);

    helpButton.setButtonText ("?");
    helpButton.setTooltip (u8 ("Hilfe: Einrichten und was machen die Regler?"));
    helpButton.onClick = [this] { helpScroll.setVisible (! helpScroll.isVisible()); };
    content.addAndMakeVisible (helpButton);

    helpScroll.setViewedComponent (&helpText, false);
    helpScroll.setScrollBarsShown (true, false);
    helpScroll.setVisible (false);
    content.addChildComponent (helpScroll);

    pad.setTooltip (u8 ("Stimmungsfeld: waagerecht die Färbung (dunkel bis hell), senkrecht die Intensität (ruhig bis aufgewühlt), Mausrad: Unruhe (Ring um den Punkt). Automatisierbar, auch per CC."));
    changeBox.setTooltip (u8 ("Wann eine neue Wendung einsetzt, wenn du den Punkt deutlich bewegst: am nächsten Schlag, am nächsten Takt, alle 2 oder alle 4 Takte."));
    customButton.setTooltip (u8 ("An: deine eigene Akkordfolge statt der Wendungen. Die Akkorde bleiben fest, Figuren und Muster kommen von der Wendung, die am Punkt im Feld liegt."));
    editButton.setTooltip (u8 ("Eigene Akkordfolge bearbeiten: bis zu acht Akkorde mit Grundton, Art und Länge."));
    keyBox.setTooltip (u8 ("Grundton der Tonart."));
    meterBox.setTooltip (u8 ("Taktart: vom Projekt übernehmen oder fest einstellen. Ungerade Takte bekommen eigene Betonungen."));
    variation.setTooltip (u8 ("Sechzehn Kombinationen aus Wendungen und Figuren. Gleiche Nummer, gleiches Ergebnis."));
    swing.setTooltip (u8 ("Verschiebt die Zwischen-Achtel nach hinten, bis zum Triolen-Gefühl."));
    previewButton.setTooltip (u8 ("Einfacher Testklang im Plugin. Spielt auch ohne Wiedergabe mit eigener Uhr (nur der Testklang, kein MIDI)."));
    chordDisplay.setTooltip (u8 ("Der klingende Akkord, darunter die Wendung (acht Takte) oder deine eigene Folge und ihre Akkorde."));

    applyTheme();
    const int savedW = processor.uiWidth.load();
    const int restoredW = juce::jlimit (kBaseW / 2, kBaseW * 3, savedW);
    setSize (restoredW, juce::roundToInt ((float) restoredW * (float) kBaseH / (float) kBaseW));
    sizeReady = true;
    startTimerHz (30);
}

StromscoreEditor::~StromscoreEditor() { stopTimer(); setLookAndFeel (nullptr); }

void StromscoreEditor::updateCcButton()
{
    auto txt = [this] (int a) { const int n = processor.ccNumber[a].load(); return n > 0 ? juce::String (n) : juce::String ("aus"); };
    ccButton.setButtonText ("CC " + txt (0) + u8 (" · ") + txt (1) + u8 (" · ") + txt (2));
    ccButton.setTooltip (u8 ("MIDI-Controller am Eingang: Färbung, Intensität, Unruhe. Klick zum Ändern."));
}

void StromscoreEditor::updateMidiLabel()
{
    const int bars = processor.exportBars.load();
    midiDrag.label = "MIDI " + juce::String (bars);
    midiDrag.setTooltip (u8 ("Auf die DAW ziehen: die nächsten ") + juce::String (bars) + u8 (" Takte als MIDI-Datei, eine Spur je Ebene, mit den aktuellen Einstellungen (stumme Ebenen bleiben leer). Klick wechselt die Länge: 8, 16 oder 32 Takte."));
    midiDrag.repaint();
}

void StromscoreEditor::showCcMenu()
{
    static const int common[] = { 1, 2, 4, 7, 11, 16, 17, 18, 19, 21, 71, 72, 73, 74, 75, 76, 77 };
    const char* axis[3] = { "Färbung", "Intensität", "Unruhe" };
    juce::PopupMenu menu;
    for (int a = 0; a < 3; ++a)
    {
        juce::PopupMenu sub;
        const int now = processor.ccNumber[a].load();
        sub.addItem (1000 * (a + 1), "aus", true, now == 0);
        for (int cc : common)
            sub.addItem (1000 * (a + 1) + cc, "CC " + juce::String (cc), true, now == cc);
        menu.addSubMenu (u8 (axis[a]) + " (" + (now > 0 ? "CC " + juce::String (now) : juce::String ("aus")) + ")", sub);
    }
    menu.addSeparator();
    menu.addItem (9999, u8 ("Vorgabe: 11 · 1 · 74"));
    menu.addSeparator();
    menu.addSectionHeader (u8 ("Ausgabe an die Spuren"));
    const bool dyn = processor.apvts.getRawParameterValue ("dynamikCc")->load() >= 0.5f;
    menu.addItem (8001, u8 ("Dynamik per CC senden"), true, dyn);
    const char* outName[2] = { "Dynamik", "Ausdruck" };
    static const int outCommon[] = { 1, 2, 7, 11, 21 };
    for (int o = 0; o < 2; ++o)
    {
        juce::PopupMenu sub;
        const int now = processor.ccOut[o].load();
        sub.addItem (5000 + 1000 * o, "aus", true, now == 0);
        for (int cc : outCommon) sub.addItem (5000 + 1000 * o + cc, "CC " + juce::String (cc), true, now == cc);
        menu.addSubMenu (u8 (outName[o]) + " (" + (now > 0 ? "CC " + juce::String (now) : juce::String ("aus")) + ")", sub, dyn);
    }
    menu.showMenuAsync (juce::PopupMenu::Options().withTargetComponent (&ccButton), [this] (int r)
    {
        if (r == 0) return;
        if (r == 9999) { processor.ccNumber[0].store (11); processor.ccNumber[1].store (1); processor.ccNumber[2].store (74); }
        else if (r == 8001)
        {
            auto* p = processor.apvts.getParameter ("dynamikCc");
            p->beginChangeGesture(); p->setValueNotifyingHost (p->getValue() >= 0.5f ? 0.0f : 1.0f); p->endChangeGesture();
        }
        else if (r >= 5000 && r < 7000) processor.ccOut[(r - 5000) / 1000].store ((r - 5000) % 1000);
        else { const int a = r / 1000 - 1; if (a >= 0 && a < 3) processor.ccNumber[a].store (r % 1000); }
        processor.updateHostDisplay (juce::AudioProcessorListener::ChangeDetails{}.withNonParameterStateChanged (true));
        updateCcButton();
    });
}

void StromscoreEditor::timerCallback()
{
    const bool wantsDark = processor.uiTheme.load() != 1;
    if (theme.dark != wantsDark) { theme = wantsDark ? darkTheme() : lightTheme(); applyTheme(); }
    const int width = processor.uiWidth.load();
    if (getWidth() != width) setSize (width, juce::roundToInt ((float) width * kBaseH / kBaseW));

    // Akkord-Anzeige
    const int w = processor.wendung.load();
    const int key = juce::roundToInt (processor.apvts.getRawParameterValue ("key")->load());
    const int gen = processor.genreInUse.load();
    chordDisplay.playing = w >= 0 && (w == stromscore::kCustomWendung || w < stromscore::wendungCount (gen));
    chordDisplay.meter = u8 ("Takt ") + juce::String (processor.meterNum.load()) + "/" + juce::String (processor.meterDen.load());
    const auto settings = processor.currentSettings();
    {
        int total = 0;
        for (const auto& c : settings.customChords) total += c.bars;
        slots.totalText = total > 0 ? u8 ("Länge der Folge: ") + juce::String (total) + (total == 1 ? " Takt" : " Takte")
                                    : u8 ("Alle Plätze leer: es spielt der Grundakkord der Tonart.");
        if (slots.isVisible()) slots.repaint();
    }
    if (chordDisplay.playing)
    {
        const auto custom = stromscore::customWendung (settings);
        const auto& wd = w == stromscore::kCustomWendung ? custom : stromscore::wendungAt (gen, w);
        char buf[32];
        stromscore::chordName (key, processor.chordRoot.load(), processor.chordType.load(), buf, (int) sizeof (buf));
        chordDisplay.chord = juce::String (juce::CharPointer_UTF8 (buf));
        chordDisplay.wendung = juce::String (juce::CharPointer_UTF8 (wd.name));
        chordDisplay.custom = w == stromscore::kCustomWendung;
        const int st = processor.styleIndex.load();
        if (chordDisplay.custom && st >= 0 && st < stromscore::wendungCount (gen))
            chordDisplay.wendung << u8 (" · Stil: ") << juce::String (juce::CharPointer_UTF8 (stromscore::wendungAt (gen, st).name));
        stromscore::chordName (key, processor.nextRoot.load(), processor.nextType.load(), buf, (int) sizeof (buf));
        chordDisplay.nextChord = juce::String (juce::CharPointer_UTF8 (buf));
        chordDisplay.progress = processor.chordProgress.load();
        chordDisplay.numChips = wd.n;
        for (int i = 0; i < wd.n; ++i)
        {
            stromscore::chordName (key, wd.ch[i].root, wd.ch[i].type, buf, (int) sizeof (buf));
            chordDisplay.chips[i] = juce::String (juce::CharPointer_UTF8 (buf));
            if (wd.ch[i].bass >= 0)
            {
                stromscore::chordName (key, wd.ch[i].bass, stromscore::Maj, buf, (int) sizeof (buf));
                chordDisplay.chips[i] << "/" << juce::String (juce::CharPointer_UTF8 (buf));
            }
        }
        chordDisplay.current = processor.chordIndex.load();
    }
    chordDisplay.mood[0] = pad.x; chordDisplay.mood[1] = pad.y; chordDisplay.mood[2] = pad.z;
    chordDisplay.repaint();

    // Kandidaten an der aktuellen Stelle
    {
        int c[6];
        const int n = stromscore::Generator::candidates (settings, c, 6);
        juce::String t;
        for (int i = 0; i < n; ++i) t << (i > 0 ? u8 (" · ") : juce::String()) << juce::String (juce::CharPointer_UTF8 (stromscore::wendungAt (settings.genre, c[i]).name));
        chordDisplay.candidates = t;
    }

    // Ebenen
    const auto& s = settings;
    for (int i = 0; i < stromscore::kNumLayers; ++i)
    {
        const float a = processor.activity[i].exchange (0.0f);
        layers[i].activity = std::max (a, layers[i].activity * 0.88f);
        layers[i].active = stromscore::Generator::layerActive (s, i);
        bool anySolo = false;
        for (bool b : s.solo) anySolo = anySolo || b;
        juce::String entry;
        if (anySolo ? ! s.solo[i] : s.mute[i]) entry = "stumm";
        else
        {
            const float t = stromscore::kLayerStart[i] - s.layerIntensity[i];
            entry = t <= 0.0f ? juce::String ("immer") : t > 1.0f ? (i == stromscore::kFarbe ? juce::String ("bei Unruhe") : juce::String ("nie"))
                                                                   : "ab " + juce::String (juce::roundToInt (t * 100.0f)) + " %";
        }
        if (layers[i].entry != entry) { layers[i].entry = entry; }
        layers[i].repaint();
    }
    if (pad.z > 0.01f) pad.repaint();   // der Unruhe-Ring zittert
}

void StromscoreEditor::applyTheme()
{
    look.setColour (juce::Slider::thumbColourId, theme.accent);
    look.setColour (juce::Slider::rotarySliderFillColourId, theme.accent);
    look.setColour (juce::Slider::rotarySliderOutlineColourId, theme.line);
    look.setColour (juce::Slider::trackColourId, theme.accent.withAlpha (0.75f));
    look.setColour (juce::Slider::backgroundColourId, theme.line);
    look.setColour (juce::Slider::textBoxTextColourId, theme.text);
    look.setColour (juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    look.setColour (juce::ComboBox::backgroundColourId, theme.bg);
    look.setColour (juce::ComboBox::textColourId, theme.text);
    look.setColour (juce::ComboBox::arrowColourId, theme.text);
    look.setColour (juce::ComboBox::outlineColourId, theme.line);
    look.setColour (juce::PopupMenu::backgroundColourId, theme.panel);
    look.setColour (juce::PopupMenu::textColourId, theme.text);
    look.setColour (juce::PopupMenu::highlightedBackgroundColourId, theme.accent);
    look.setColour (juce::PopupMenu::highlightedTextColourId, juce::Colours::black);
    look.setColour (juce::Label::textColourId, theme.text);
    look.setColour (juce::TextButton::buttonColourId, theme.dark ? theme.panel : theme.bg);
    look.setColour (juce::TextButton::buttonOnColourId, theme.accent);
    look.setColour (juce::TextButton::textColourOffId, theme.text);
    look.setColour (juce::TextButton::textColourOnId, juce::Colours::black);

    for (auto* l : { &padLabel, &varietyLabel, &keyLabel, &meterLabel, &variationLabel, &swingLabel, &chordLabel, &changeLabel, &customLabel })
        l->setColour (juce::Label::textColourId, theme.dim);
    const auto inner = theme.dark ? theme.bg : theme.bg.brighter (0.05f);
    pad.panel = inner; pad.line = theme.line; pad.accent = theme.accent; pad.text = theme.text; pad.dim = theme.dim;
    chordDisplay.panel = inner; chordDisplay.line = theme.line; chordDisplay.accent = theme.accent; chordDisplay.text = theme.text; chordDisplay.dim = theme.dim;
    midiDrag.panel = theme.panel; midiDrag.line = theme.line; midiDrag.accent = theme.accent; midiDrag.text = theme.text; midiDrag.dim = theme.dim;
    slots.panel = theme.panel; slots.line = theme.line; slots.accent = theme.accent; slots.text = theme.text; slots.dim = theme.dim;
    for (auto& l : layers) { l.panel = theme.panel; l.line = theme.line; l.accent = theme.accent; l.text = theme.text; l.dim = theme.dim; }
    themeButton.setButtonText (theme.dark ? "Look: Dunkel" : "Look: Hell");
    helpText.setAttributed (buildHelp (theme.text, theme.accent, theme.dim));
    helpScroll.fill = theme.panel;
    helpScroll.edge = theme.line;
    sendLookAndFeelChange();
    repaint();
}

float StromscoreEditor::subtitleEnd() const
{
    juce::GlyphArrangement ga;
    ga.addLineOfText (juce::Font (juce::FontOptions (12.0f, juce::Font::bold)), u8 ("AUDIO DRAMA UNDERSCORE INSPIRATOR"), 0.0f, 0.0f);
    return kSubtitleX + ga.getBoundingBox (0, -1, true).getWidth();
}

void StromscoreEditor::paint (juce::Graphics& g)
{
    g.fillAll (theme.bg);
    g.addTransform (juce::AffineTransform::scale (uiScale));
    const int W = kBaseW;

    g.setColour (theme.panel);
    g.fillRect (0, 0, W, 64);
    g.setColour (theme.line);
    g.fillRect (0, 63, W, 1);
    g.setColour (theme.accent);
    g.fillRect (0, 0, 5, 64);

    if (logo.isValid())
    {
        g.setColour (theme.text);
        g.drawImage (logo, juce::Rectangle<float> (14.0f, 4.0f, 56.0f, 56.0f), juce::RectanglePlacement::centred, true);
    }

    const float subX = kSubtitleX;
    g.setColour (theme.text);
    g.setFont (juce::FontOptions (24.0f, juce::Font::bold));
    g.drawText ("STROMSCORE", 80, 8, 210, 30, juce::Justification::centredLeft);
    g.setColour (theme.accent);
    g.setFont (juce::FontOptions (12.0f, juce::Font::bold));
    const juce::String subtitle = u8 ("AUDIO DRAMA UNDERSCORE INSPIRATOR");
    g.drawText (subtitle, (int) subX, 15, 320, 22, juce::Justification::centredLeft);
    g.setColour (theme.dim);
    g.setFont (juce::FontOptions (11.0f));
    g.drawText (juce::String (juce::CharPointer_UTF8 ("STROMSCHLAG AUDIO  \xc2\xb7  v" PLUGIN_VERSION_TEXT)), 80, 36, 300, 16, juce::Justification::centredLeft);

    // Symbol: Violinschluessel, Notenlinien, drei Noten mit p und f (kompakt direkt hinter dem Untertitel, folgt dem Look)
    {
        const float x0 = subtitleEnd() + 12.0f, x1 = x0 + kSymbolW, y0 = 22.0f, gap = 4.0f;
        g.setColour (theme.panel.interpolatedWith (theme.text, 0.34f));
        for (int i = 0; i < 5; ++i)
            g.fillRect (x0, y0 + (float) i * gap, x1 - x0, 1.0f);

        juce::Path clef;
        clef.startNewSubPath (10.0f, 34.0f);
        clef.cubicTo (10.0f, 38.0f, 16.0f, 38.0f, 16.0f, 34.0f);
        clef.cubicTo (16.0f, 28.0f, 14.0f, 10.0f, 14.0f, 5.0f);
        clef.cubicTo (14.0f, 0.0f, 19.0f, 0.0f, 18.0f, 6.0f);
        clef.cubicTo (17.0f, 14.0f, 9.0f, 17.0f, 9.0f, 22.0f);
        clef.cubicTo (9.0f, 28.0f, 19.0f, 28.0f, 19.0f, 22.0f);
        clef.cubicTo (19.0f, 17.0f, 11.0f, 16.0f, 11.0f, 21.0f);
        g.strokePath (clef, juce::PathStrokeType (1.2f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded),
                      juce::AffineTransform::translation (-9.0f, -1.0f).scaled (0.9f).translated (x0 + 2.0f, y0 - 8.0f));

        const float notes[][2] = { { 28, 1 }, { 40, 4 }, { 52, 3 } };
        for (const auto& n : notes)
        {
            const float cx = x0 + n[0];
            const float cy = y0 + 4.0f * gap - n[1] * gap * 0.5f;
            juce::Path head;
            head.addEllipse (-2.6f, -1.9f, 5.2f, 3.8f);
            g.fillPath (head, juce::AffineTransform::rotation (-0.4f).translated (cx, cy));
            g.fillRect (cx + 2.0f, cy - 10.0f, 1.0f, 10.0f);
        }
        g.setFont (juce::Font (juce::FontOptions ("Times New Roman", 13.0f, juce::Font::bold | juce::Font::italic)));
        g.drawText ("p", (int) (x0 + 21.0f), (int) (y0 + 18.0f), 12, 16, juce::Justification::centred);
        g.drawText ("f", (int) (x0 + 49.0f), (int) (y0 + 18.0f), 12, 16, juce::Justification::centred);
    }

    // Obere Karte
    g.setColour (theme.panel);
    g.fillRoundedRectangle (12.0f, 76.0f, (float) W - 24.0f, 244.0f, 8.0f);
    g.setColour (theme.line);
    g.drawRoundedRectangle (12.5f, 76.5f, (float) W - 25.0f, 243.0f, 8.0f, 1.0f);
    for (float x : { 244.0f, 410.0f, 586.0f })
        g.fillRect (x, 88.0f, 1.0f, 220.0f);
}

void StromscoreEditor::resized()
{
    if (sizeReady)
        processor.uiWidth.store (getWidth());
    uiScale = std::min ((float) getWidth() / kBaseW, (float) getHeight() / kBaseH);
    content.setTransform (juce::AffineTransform::scale (uiScale));
    content.setBounds (0, 0, kBaseW, kBaseH);
    repaint();

    const int w = kBaseW;
    // Kopfzeile: CC-Knopf klein links neben dem Look-Schalter
    helpButton.setBounds (w - 44, 18, 30, 28);
    themeButton.setBounds (w - 150, 18, 100, 28);
    const int ccX = std::max (juce::roundToInt (subtitleEnd() + 12.0f + kSymbolW + 14.0f), w - 150 - 8 - 150);
    ccButton.setBounds (ccX, 18, w - 150 - 8 - ccX, 28);
    helpScroll.setBounds (12, 76, w - 24, kBaseH - 88);
    helpText.setWidth (helpScroll.getMaximumVisibleWidth());

    // Stimmungsfeld, darunter Unruhe
    padLabel.setBounds (24, 82, 90, 18);
    genreScore.setBounds (118, 80, 52, 20);
    genrePop.setBounds (172, 80, 60, 20);
    pad.setBounds (24, 102, 208, 208);

    // Tonart, Takt, Variation, Swing
    keyLabel.setBounds (256, 82, 140, 18);
    keyBox.setBounds (256, 102, 142, 26);
    meterLabel.setBounds (256, 136, 140, 18);
    meterBox.setBounds (256, 156, 142, 26);
    variationLabel.setBounds (256, 190, 140, 18);
    variation.setBounds (256, 210, 142, 26);
    swingLabel.setBounds (256, 244, 140, 18);
    swing.setBounds (252, 264, 150, 24);

    // Wechsel, eigene Folge, Vorhoeren
    changeLabel.setBounds (422, 82, 150, 18);
    changeBox.setBounds (422, 102, 152, 26);
    customLabel.setBounds (422, 136, 150, 18);
    customButton.setBounds (422, 156, 116, 26);
    editButton.setBounds (542, 156, 32, 26);
    passingButton.setBounds (422, 188, 152, 26);
    varietyLabel.setBounds (422, 222, 150, 18);
    variety.setBounds (418, 240, 160, 24);
    previewButton.setBounds (422, 280, 94, 26);
    midiDrag.setBounds (520, 280, 54, 26);

    // Akkord-Anzeige
    chordLabel.setBounds (598, 82, 200, 18);
    chordDisplay.setBounds (598, 102, w - 622, 208);
    slots.setBounds (12, 76, w - 24, 244);

    // Ebenen
    for (int i = 0; i < stromscore::kNumLayers; ++i)
        layers[i].setBounds (12 + i * 177, 330, 168, kBaseH - 342);
    if (slots.isVisible()) slots.toFront (false);
    helpScroll.toFront (false);
}
