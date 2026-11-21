#include "PluginEditor.h"
#include <BinaryData.h>

namespace
{
juce::String u8 (const char* s) { return juce::String (juce::CharPointer_UTF8 (s)); }

const char* kLayerTitle[stromscore::kNumLayers] = { "FLÄCHE", "BASS", "ARP", "FARBE", "AKZENTE" };
const char* kLayerTip[stromscore::kNumLayers] = {
    "Akkorde: gehalten, als kurze Schläge oder im Puls.",
    "Grundton der Akkorde in verschiedenen Mustern, von gehalten bis Funk.",
    "Gebrochene Akkorde und Figuren, auch als Ostinato.",
    "Einzelne hohe Töne über dem Akkord. Bei Unruhe auch Töne außerhalb der Tonart.",
    "Tiefe Schläge bei Akkordwechseln, bei hoher Intensität auch auf den Betonungen." };
const char* kLayerLines[stromscore::kNumLayers] = {
    "", "", "",
    "Hoher Ton über dem Akkord, bei Unruhe ein fremder, reibender Ton in der Mitte des Akkords",
    "Tiefer Schlag bei jedem Akkordwechsel, sehr aufgewühlt auch auf den Betonungen" };
const char* kAutoLabel[stromscore::kNumLayers] = { "Auto: immer", "Auto: immer", "Auto: ab 25 %", "Auto: ab 40 %", "Auto: ab 70 %" };
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
    g.setColour (accent);
    g.setFont (juce::FontOptions (13.0f, juce::Font::bold));
    g.drawText (playing ? u8 ("Wendung: ") + wendung : u8 ("Wiedergabe starten, dann spielt es"), 14, 48, w - 28, 18, juce::Justification::centredLeft);

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
    g.drawText (title, 12, 8, (int) r.getWidth() - 40, 16, juce::Justification::centredLeft);

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
    g.drawText (u8 ("MIDI-Kanal ") + juce::String (channel), 12, 28, (int) r.getWidth() - 24, 14, juce::Justification::centredLeft);
    if (lines.isNotEmpty())
    {
        g.setColour (active ? text : dim);
        g.setFont (juce::FontOptions (11.5f));
        g.drawFittedText (lines, 12, 50, (int) r.getWidth() - 24, 80, juce::Justification::topLeft, 6, 1.0f);
    }
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
    body ("Es erzeugt Musik für Untermalung und gibt sie als MIDI auf fünf Kanälen aus: Fläche, Bass, Arp, Farbe und Akzente. Die Klänge kommen aus deinen eigenen Instrumenten. Die Noten sind als Ausgangspunkt gedacht, den du weiter bearbeitest. Es läuft im Takt des Projekts: Wiedergabe starten, springen oder loopen, und es spielt an der richtigen Stelle weiter. Gleiche Einstellungen ergeben immer dieselben Noten.");

    head ("Woher die Musik kommt");
    bold ("Es verwendet keine KI. ");
    body ("STROMSCORE arbeitet mit festen Regeln, nicht mit trainierten Modellen und nicht mit fremdem Material. Die Grundlage ist der Stil, den Lars Eickstädt über Jahre für seine Hörspiele entwickelt hat, geprägt von großen Filmkomponisten und der Musik klassischer Hörspiele. Daraus ist ein Vorrat an Wendungen entstanden: Akkordfolgen, Figuren und Rhythmen. Je nach Stimmung zieht das Plugin daraus. Melodien bekannter Stücke werden nicht nachgebaut.");

    head ("Einrichten in Studio One");
    body ("1. Lege eine Instrumentenspur mit Stromscore an. 2. Lege für jede Ebene, die du hören willst, eine Instrumentenspur mit deinem Instrument an. 3. Stelle bei jeder dieser Spuren als Eingang Stromscore ein und wähle den MIDI-Kanal (Fläche 1, Bass 2, Arp 3, Farbe 4, Akzente 5). 4. Schalte die Spuren auf Monitor. Zum Weiterarbeiten nimmst du die Ausgabe einfach auf diesen Spuren auf.");
    note ("Ohne eigene Instrumente hörst du mit VORHÖREN einen einfachen Testklang direkt aus dem Plugin.");

    head ("Das Stimmungsfeld");
    body ("Ziehe den Punkt durch das Feld. Waagerecht ist die FÄRBUNG: links dunkel (Bedrohung, Trauer, Lauern), rechts hell (Wärme, Staunen, Triumph). Senkrecht ist die INTENSITÄT: unten ruhig und dünn, oben aufgewühlt und dicht. Mit dem Mausrad über dem Feld oder dem Regler UNRUHE änderst du die dritte Achse. Sie zeigt sich als Ring um den Punkt: Je größer und zittriger, desto mehr Reibung, Dissonanz, Halbtöne und verschobene Betonungen. Bei wenig Intensität sind es einzelne fremde Töne, bei viel Intensität kratzt der ganze Satz.");
    body ("Alle drei Achsen lassen sich automatisieren. So fährst du durch eine Szene: langsam vom Lauern in die Panik und am Ende in die Erlösung. Wechsel greifen am nächsten Akkordwechsel, damit nichts mitten im Ton umspringt.");

    head ("Controller (CC)");
    body ("Stromscore hört auf seinem MIDI-Eingang auf drei Controller: CC 11 für die Färbung, CC 1 für die Intensität und CC 74 für die Unruhe. Das passt zu einem Fader-Controller, wie er für Orchester-Instrumente üblich ist. Gib der Stromscore-Spur den Controller als Eingang und nimm die Fader-Bewegungen als MIDI-Part auf. Über den Knopf mit den CC-Nummern kannst du die Zuordnung ändern oder einzelne Achsen abschalten.");

    head ("Wendungen und Akkorde");
    body ("Rechts oben steht der klingende Akkord, darunter die Wendung und ihre Akkorde. Eine Wendung dauert acht Takte. Welche Wendung kommt, hängt vom Punkt im Feld und von VARIATION ab. Bleibst du an einer Stelle, wechseln sich passende Wendungen ab. Die Akkorde stehen mit deutschen Notennamen (H statt B).");

    head ("TONART, TAKT, VARIATION, SWING");
    body ("TONART legt den Grundton fest. TAKT übernimmt die Taktart aus dem Projekt oder legt sie fest (4/4, 3/4, 6/8, 5/4, 7/8, 5/8, 12/8); ungerade Takte bekommen eigene Betonungsgruppen, etwa 3+3+2+2 im 5/4. VARIATION wählt eine von sechzehn Kombinationen aus Wendungen und Figuren; gleiche Nummer, gleiches Ergebnis. SWING verschiebt die Zwischen-Achtel nach hinten, bis zum Triolen-Gefühl.");

    head ("Die fünf Ebenen");
    body ("Jede Ebene hat ihren MIDI-Kanal und eine Lampe, die bei jedem Ton leuchtet. Der untere Schalter hat drei Stufen: Aus (die Ebene schweigt), Auto (sie setzt bei ihrer Intensitäts-Stufe ein: Arp ab 25 %, Farbe ab 40 % oder bei Unruhe, Akzente ab 70 %) und An (sie spielt immer). So kannst du auch nur mit dem Bass oder nur mit einer Fläche beginnen.");

    head ("Muster");
    body ("Fläche: Gehalten, Schläge (kurze Akkorde auf der Zwischenzeit) oder Puls (auf jedem Schlag). Bass: Gehalten, Halbe, Viertel, Achtel, Puls (durchgehende Sechzehntel auf einem Ton), Oktaven, Funk (synkopiert) oder Pendel (Grundton und kleine Terz, bei Unruhe Halbton). Arp: Aufwärts, Abwärts, Kreisend (auf und ab), Zelle (kurze, obsessive Figur), Riff oder Glitzern (schnell und hoch); das Tempo wählst du daneben. Auf Auto folgt das Muster der Wendung.");

    head ("Folgt den Akkorden / bleibt");
    body ("Bei Fläche, Bass und Arp bestimmt dieser Schalter, ob die Ebene den Akkordwechseln folgt oder auf dem Grundakkord der Tonart bleibt. Ein Arp, der bleibt, läuft unverändert durch, während sich Fläche und Bass bewegen. Ein Bass, der bleibt, hält den Grundton unter wechselnden Akkorden.");

    head ("VORHÖREN");
    body ("Ein einfacher Testklang im Plugin, damit du ohne eigene Instrumente hörst, was entsteht. Für die fertige Musik schaltest du ihn aus.");

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
    label (padValues, "", juce::Justification::centredRight);
    padValues.setFont (juce::Font (juce::FontOptions (11.0f)));
    label (unruheLabel, "UNRUHE", juce::Justification::centred);
    label (keyLabel, "TONART", juce::Justification::centredLeft);
    label (meterLabel, "TAKT", juce::Justification::centredLeft);
    label (variationLabel, "VARIATION", juce::Justification::centredLeft);
    label (swingLabel, "SWING", juce::Justification::centredLeft);
    label (chordLabel, "AKKORD", juce::Justification::centredLeft);

    // Stimmungsfeld: Faerbung und Intensitaet als ein Zug, Unruhe per Mausrad
    for (int a = 0; a < 3; ++a)
        axisAttachment[a] = std::make_unique<juce::ParameterAttachment> (*processor.apvts.getParameter (StromscoreProcessor::kAxisIds[a]),
            [this, a] (float v)
            {
                (a == 0 ? pad.x : a == 1 ? pad.y : pad.z) = v;
                padValues.setText (u8 ("Färbung ") + juce::String (juce::roundToInt (pad.x * 100.0f)) + u8 (" % · Intensität ")
                                   + juce::String (juce::roundToInt (pad.y * 100.0f)) + " %", juce::dontSendNotification);
                pad.repaint();
            }, nullptr);
    pad.onDragStart = [this] { axisAttachment[0]->beginGesture(); axisAttachment[1]->beginGesture(); };
    pad.onDrag = [this] (float nx, float ny) { axisAttachment[0]->setValueAsPartOfGesture (nx); axisAttachment[1]->setValueAsPartOfGesture (ny); };
    pad.onDragEnd = [this] { axisAttachment[0]->endGesture(); axisAttachment[1]->endGesture(); };
    pad.onWheel = [this] (float dz) { axisAttachment[2]->setValueAsCompleteGesture (juce::jlimit (0.0f, 1.0f, pad.z + dz)); };
    for (auto& a : axisAttachment) a->sendInitialUpdate();
    content.addAndMakeVisible (pad);

    unruhe.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    unruhe.setMouseDragSensitivity (180);
    unruhe.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 18);
    content.addAndMakeVisible (unruhe);
    unruheAttachment = std::make_unique<APVTS::SliderAttachment> (processor.apvts, "unruhe", unruhe);

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
        lv.setTooltip (u8 ("MIDI-Kanal ") + juce::String (i + 1) + ": " + u8 (kLayerTip[i]));
        lv.modeButton.setTooltip (u8 ("Aus: die Ebene schweigt. Auto: sie setzt bei ihrer Intensitäts-Stufe ein. An: sie spielt immer. Klick schaltet weiter."));
        modeAttachment[i] = std::make_unique<juce::ParameterAttachment> (*processor.apvts.getParameter ("layer" + juce::String (i + 1)),
            [this, i] (float v) { updateModeButton (i, juce::roundToInt (v)); }, nullptr);
        lv.modeButton.onClick = [this, i] { modeAttachment[i]->setValueAsCompleteGesture ((float) ((layers[i].mode + 1) % 3)); };
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
    for (int i = 0; i < stromscore::kNumLayers; ++i) modeAttachment[i]->sendInitialUpdate();

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

    pad.setTooltip (u8 ("Stimmungsfeld: waagerecht die Färbung (dunkel bis hell), senkrecht die Intensität (ruhig bis aufgewühlt). Mausrad: Unruhe. Automatisierbar, auch per CC."));
    unruhe.setTooltip (u8 ("Unruhe: Reibung, Halbtöne, Dissonanz und verschobene Betonungen. Auch per Mausrad über dem Feld."));
    keyBox.setTooltip (u8 ("Grundton der Tonart."));
    meterBox.setTooltip (u8 ("Taktart: vom Projekt übernehmen oder fest einstellen. Ungerade Takte bekommen eigene Betonungen."));
    variation.setTooltip (u8 ("Sechzehn Kombinationen aus Wendungen und Figuren. Gleiche Nummer, gleiches Ergebnis."));
    swing.setTooltip (u8 ("Verschiebt die Zwischen-Achtel nach hinten, bis zum Triolen-Gefühl."));
    previewButton.setTooltip (u8 ("Einfacher Testklang im Plugin, damit du ohne eigene Instrumente hörst, was entsteht."));
    chordDisplay.setTooltip (u8 ("Der klingende Akkord, darunter die Wendung (acht Takte) und ihre Akkorde."));

    applyTheme();
    const int savedW = processor.uiWidth.load();
    const int restoredW = juce::jlimit (kBaseW / 2, kBaseW * 3, savedW);
    setSize (restoredW, juce::roundToInt ((float) restoredW * (float) kBaseH / (float) kBaseW));
    sizeReady = true;
    startTimerHz (30);
}

StromscoreEditor::~StromscoreEditor() { stopTimer(); setLookAndFeel (nullptr); }

void StromscoreEditor::updateModeButton (int layer, int mode)
{
    auto& lv = layers[layer];
    mode = juce::jlimit (0, 2, mode);
    lv.mode = mode;
    lv.modeButton.setButtonText (mode == 0 ? juce::String ("Aus") : mode == 2 ? juce::String ("An") : u8 (kAutoLabel[layer]));
    lv.modeButton.setToggleState (mode == 2, juce::dontSendNotification);
    lv.repaint();
}

void StromscoreEditor::updateCcButton()
{
    auto txt = [this] (int a) { const int n = processor.ccNumber[a].load(); return n > 0 ? juce::String (n) : juce::String ("aus"); };
    ccButton.setButtonText ("CC " + txt (0) + u8 (" · ") + txt (1) + u8 (" · ") + txt (2));
    ccButton.setTooltip (u8 ("MIDI-Controller am Eingang: Färbung, Intensität, Unruhe. Klick zum Ändern."));
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
    menu.showMenuAsync (juce::PopupMenu::Options().withTargetComponent (&ccButton), [this] (int r)
    {
        if (r == 0) return;
        if (r == 9999) { processor.ccNumber[0].store (11); processor.ccNumber[1].store (1); processor.ccNumber[2].store (74); }
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
    chordDisplay.playing = w >= 0 && w < stromscore::kNumWendungen;
    chordDisplay.meter = u8 ("Takt ") + juce::String (processor.meterNum.load()) + "/" + juce::String (processor.meterDen.load());
    if (chordDisplay.playing)
    {
        const auto& wd = stromscore::kWendungen[w];
        char buf[32];
        stromscore::chordName (key, processor.chordRoot.load(), processor.chordType.load(), buf, (int) sizeof (buf));
        chordDisplay.chord = juce::String (juce::CharPointer_UTF8 (buf));
        chordDisplay.wendung = juce::String (juce::CharPointer_UTF8 (wd.name));
        chordDisplay.numChips = wd.n;
        for (int i = 0; i < wd.n; ++i)
        {
            stromscore::chordName (key, wd.ch[i].root, wd.ch[i].type, buf, (int) sizeof (buf));
            chordDisplay.chips[i] = juce::String (juce::CharPointer_UTF8 (buf));
        }
        chordDisplay.current = processor.chordIndex.load();
    }
    chordDisplay.repaint();

    // Ebenen
    stromscore::Settings s;
    s.y = processor.apvts.getRawParameterValue ("intensitaet")->load();
    s.z = processor.apvts.getRawParameterValue ("unruhe")->load();
    for (int i = 0; i < stromscore::kNumLayers; ++i) s.layerMode[i] = layers[i].mode;
    for (int i = 0; i < stromscore::kNumLayers; ++i)
    {
        const float a = processor.activity[i].exchange (0.0f);
        layers[i].activity = std::max (a, layers[i].activity * 0.88f);
        layers[i].active = stromscore::Generator::layerActive (s, i);
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

    for (auto* l : { &padLabel, &padValues, &unruheLabel, &keyLabel, &meterLabel, &variationLabel, &swingLabel, &chordLabel })
        l->setColour (juce::Label::textColourId, theme.dim);
    const auto inner = theme.dark ? theme.bg : theme.bg.brighter (0.05f);
    pad.panel = inner; pad.line = theme.line; pad.accent = theme.accent; pad.text = theme.text; pad.dim = theme.dim;
    chordDisplay.panel = inner; chordDisplay.line = theme.line; chordDisplay.accent = theme.accent; chordDisplay.text = theme.text; chordDisplay.dim = theme.dim;
    for (auto& l : layers) { l.panel = theme.panel; l.line = theme.line; l.accent = theme.accent; l.text = theme.text; l.dim = theme.dim; }
    themeButton.setButtonText (theme.dark ? "Look: Dunkel" : "Look: Hell");
    helpText.setAttributed (buildHelp (theme.text, theme.accent, theme.dim));
    helpScroll.fill = theme.panel;
    helpScroll.edge = theme.line;
    sendLookAndFeelChange();
    repaint();
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

    const float subX = 244.0f;
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

    // Symbol: Violinschluessel, Notenlinien, ein paar Noten mit p und f (einfarbig, folgt dem Look)
    {
        juce::GlyphArrangement ga;
        ga.addLineOfText (juce::Font (juce::FontOptions (12.0f, juce::Font::bold)), subtitle, 0.0f, 0.0f);
        const float subEnd = subX + ga.getBoundingBox (0, -1, true).getWidth();
        const float helpX = (float) (kBaseW - 170);
        const float mid = 0.5f * (subEnd + helpX);
        g.setColour (theme.panel.interpolatedWith (theme.text, 0.34f));
        const float x0 = mid - 50.0f, x1 = mid + 50.0f, y0 = 24.0f, gap = 4.0f;
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
        g.strokePath (clef, juce::PathStrokeType (1.3f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded),
                      juce::AffineTransform::translation (x0 + 1.0f, y0 - 10.0f));

        const float notes[][2] = { { 44, 1 }, { 58, 3 }, { 72, 5 }, { 84, 4 } };
        for (const auto& n : notes)
        {
            const float cx = x0 + n[0];
            const float cy = y0 + 4.0f * gap - n[1] * gap * 0.5f;
            juce::Path head;
            head.addEllipse (-2.8f, -2.0f, 5.6f, 4.0f);
            g.fillPath (head, juce::AffineTransform::rotation (-0.4f).translated (cx, cy));
            g.fillRect (cx + 2.2f, cy - 11.0f, 1.0f, 11.0f);
        }
        g.setFont (juce::Font (juce::FontOptions ("Times New Roman", 14.0f, juce::Font::bold | juce::Font::italic)));
        g.drawText ("p", (int) (x0 + 25.0f), (int) (y0 + 18.0f), 14, 18, juce::Justification::centred);
        g.drawText ("f", (int) (x0 + 90.0f), (int) (y0 + 18.0f), 12, 18, juce::Justification::centred);
    }

    // Obere Karte
    g.setColour (theme.panel);
    g.fillRoundedRectangle (12.0f, 76.0f, (float) W - 24.0f, 244.0f, 8.0f);
    g.setColour (theme.line);
    g.drawRoundedRectangle (12.5f, 76.5f, (float) W - 25.0f, 243.0f, 8.0f, 1.0f);
    for (float x : { 404.0f, 584.0f })
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
    themeButton.setBounds (w - 170, 18, 112, 28);
    helpButton.setBounds (w - 48, 18, 32, 28);
    helpScroll.setBounds (12, 76, w - 24, kBaseH - 88);
    helpText.setWidth (helpScroll.getMaximumVisibleWidth());

    // Stimmungsfeld und Unruhe
    padLabel.setBounds (24, 82, 100, 18);
    padValues.setBounds (84, 82, 150, 18);
    pad.setBounds (24, 102, 210, 210);
    unruheLabel.setBounds (246, 82, 146, 18);
    unruhe.setBounds (252, 102, 134, 126);
    ccButton.setBounds (250, 280, 142, 26);

    // Tonart, Takt, Variation, Swing
    keyLabel.setBounds (418, 82, 150, 18);
    keyBox.setBounds (418, 102, 154, 26);
    meterLabel.setBounds (418, 136, 150, 18);
    meterBox.setBounds (418, 156, 154, 26);
    variationLabel.setBounds (418, 190, 150, 18);
    variation.setBounds (418, 210, 154, 26);
    swingLabel.setBounds (418, 244, 150, 18);
    swing.setBounds (414, 264, 162, 24);

    // Akkord-Anzeige
    chordLabel.setBounds (598, 82, 200, 18);
    chordDisplay.setBounds (598, 102, w - 622, 172);
    previewButton.setBounds (598, 282, w - 622, 26);

    // Ebenen
    for (int i = 0; i < stromscore::kNumLayers; ++i)
        layers[i].setBounds (12 + i * 177, 330, 168, kBaseH - 342);
    helpScroll.toFront (false);
}
