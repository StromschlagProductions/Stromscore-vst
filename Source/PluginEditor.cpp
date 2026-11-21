#include "PluginEditor.h"
#include <BinaryData.h>

namespace
{
juce::String u8 (const char* s) { return juce::String (juce::CharPointer_UTF8 (s)); }

const char* kLayerTitle[stromscore::kNumLayers] = { "FL\xc3\x84" "CHE", "BASS", "ARP", "FARBE", "AKZENTE" };
const char* kLayerNote[stromscore::kNumLayers] = {
    "Gehaltene Akkorde, mit steigendem VERLAUF dichter und lauter",
    "Grundton: erst gehalten, dann als Puls, ab 60 % in Achteln",
    "Gebrochener Akkord in Achteln, ab 60 % in Sechzehnteln",
    "Ein hoher Ton \xc3\xbc" "ber dem Akkord",
    "Tiefer Schlag bei jedem Akkordwechsel" };
}

// ---------------------------------------------------------------- Anzeigen

void ChordDisplay::paint (juce::Graphics& g)
{
    auto r = getLocalBounds().toFloat();
    g.setColour (panel);
    g.fillRoundedRectangle (r, 6.0f);
    g.setColour (line);
    g.drawRoundedRectangle (r.reduced (0.5f), 6.0f, 1.0f);

    const float cw = (r.getWidth() - 24.0f) * 0.5f;
    for (int i = 0; i < stromscore::kChordsPerCycle; ++i)
    {
        const juce::Rectangle<float> c (8.0f + (float) (i % 2) * (cw + 8.0f), 8.0f + (float) (i / 2) * 30.0f, cw, 26.0f);
        const bool on = playing && i == current;
        g.setColour (on ? accent : line);
        if (on) g.fillRoundedRectangle (c, 5.0f); else g.drawRoundedRectangle (c.reduced (0.5f), 5.0f, 1.0f);
        g.setColour (on ? juce::Colours::black : text);
        g.setFont (juce::FontOptions (12.5f, juce::Font::bold));
        g.drawText (chords[i], c.toNearestInt(), juce::Justification::centred);
    }

    // VERLAUF als Leiste mit den Einsatzpunkten der Ebenen
    const juce::Rectangle<float> bar (8.0f, r.getHeight() - 16.0f, r.getWidth() - 16.0f, 6.0f);
    g.setColour (line);
    g.fillRoundedRectangle (bar, 3.0f);
    g.setColour (accent);
    g.fillRoundedRectangle (bar.withWidth (bar.getWidth() * juce::jlimit (0.0f, 1.0f, verlauf)), 3.0f);
    g.setColour (dim);
    for (int i = 2; i < stromscore::kNumLayers; ++i)
        g.fillRect (bar.getX() + bar.getWidth() * stromscore::kLayerStart[i] - 0.5f, bar.getY() - 2.0f, 1.0f, bar.getHeight() + 4.0f);
}

void LayerView::paint (juce::Graphics& g)
{
    const bool active = verlauf + 1.0e-4f >= start;
    auto r = getLocalBounds().toFloat();
    g.setColour (panel);
    g.fillRoundedRectangle (r, 8.0f);
    g.setColour (line);
    g.drawRoundedRectangle (r.reduced (0.5f), 8.0f, 1.0f);

    g.setColour (active ? accent : dim);
    g.setFont (juce::FontOptions (12.0f, juce::Font::bold));
    g.drawText (title, 12, 8, (int) r.getWidth() - 40, 16, juce::Justification::centredLeft);

    // Lampe: leuchtet bei jedem gespielten Ton
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
    g.setColour (active ? text : dim);
    g.setFont (juce::FontOptions (11.5f));
    g.drawFittedText (lines, 12, 52, (int) r.getWidth() - 24, 66, juce::Justification::topLeft, 5, 1.0f);

    g.setColour (active ? text : dim);
    g.setFont (juce::FontOptions (12.0f, juce::Font::bold));
    g.drawText (start <= 0.0f ? u8 ("immer dabei") : u8 ("ab ") + juce::String (juce::roundToInt (start * 100.0f)) + " %",
                12, (int) r.getHeight() - 30, (int) r.getWidth() - 24, 18, juce::Justification::centredLeft);
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
    auto note = [&] (const char* t) { s.append (u8 (t) + "\n\n", juce::Font (juce::FontOptions (12.0f)), dim); };

    s.append (u8 ("Hilfe \xc2\xb7 v") + juce::String (PLUGIN_VERSION_TEXT) + "\n\n",
              juce::Font (juce::FontOptions (17.0f, juce::Font::bold)), accent);

    head ("Was das Plugin macht");
    body ("Es erzeugt nach festen Regeln Musik f\xc3\xbcr Untermalung und gibt sie als MIDI aus: Akkorde, Bass, gebrochene Akkorde und einzelne Akzente. Es l\xc3\xa4uft im Takt des Projekts: Wiedergabe starten, Position springen oder loopen, und es spielt an der richtigen Stelle weiter. Gleiche Einstellungen ergeben immer dieselben Noten. Es verwendet keine KI und keine Zufallswerte, die sich beim n\xc3\xa4" "chsten Abspielen \xc3\xa4ndern.");
    note ("Version 0.1 ist ein erster Test: Sie soll zeigen, dass die Noten sauber auf deine eigenen Instrumentenspuren ankommen. Weitere Stimmungen und Stilvorlagen folgen.");

    head ("Einrichten in Studio One");
    body ("1. Lege eine Instrumentenspur mit Stromscore an. 2. Lege f\xc3\xbcr jede Ebene, die du h\xc3\xb6ren willst, eine eigene Instrumentenspur mit deinem Instrument an. 3. Stelle bei jeder dieser Spuren als Eingang Stromscore ein und w\xc3\xa4hle dort den passenden MIDI-Kanal (Fl\xc3\xa4" "che 1, Bass 2, Arp 3, Farbe 4, Akzente 5). 4. Schalte die Spuren auf Monitor, dann spielen sie beim Abspielen mit.");
    note ("Ohne eigene Instrumente kannst du mit VOR\xc3\x96REN einen einfachen Testklang direkt aus dem Plugin h\xc3\xb6ren.");

    head ("TONART und MODUS");
    body ("Grundton und Tonleiter. Moll, Dur, Dorisch, Phrygisch und Lydisch. Alle Noten bleiben in der gew\xc3\xa4hlten Tonleiter. Pro Modus l\xc3\xa4uft eine Folge aus vier Akkorden, jeder Akkord dauert zwei Takte. Der gerade klingende Akkord leuchtet in der Anzeige.");

    head ("VERLAUF");
    body ("Wie viel gleichzeitig passiert, von ruhig (0 %) bis dicht (100 %). Die Ebenen setzen nacheinander ein: Fl\xc3\xa4" "che und Bass sind immer dabei, der Arp kommt ab 25 %, die Farbe ab 50 %, die Akzente ab 75 %. Zus\xc3\xa4tzlich wird der Bass lebendiger und der Arp schneller. Die Leiste unter den Akkorden zeigt die Einsatzpunkte. Der Regler l\xc3\xa4sst sich automatisieren, so baust du Spannung \xc3\xbc" "ber die Szene auf.");

    head ("VARIATION");
    body ("Sechzehn Varianten (1 bis 16) derselben Einstellung. Sie ver\xc3\xa4ndern kleine Details wie Anschlagst\xc3\xa4rken und den Einstieg des Arps. Gleiche Nummer ergibt immer das gleiche Ergebnis.");

    head ("Die f\xc3\xbcnf Ebenen");
    body ("Jede Ebene hat ihren eigenen MIDI-Kanal und eine Lampe, die bei jedem gespielten Ton leuchtet. Fl\xc3\xa4" "che (Kanal 1), Bass (2), Arp (3), Farbe (4) und Akzente (5). So kannst du jede Ebene mit einem anderen Instrument spielen.");

    head ("VOR\xc3\x96REN");
    body ("Schaltet einen einfachen Testklang im Plugin ein, damit du auch ohne eigene Instrumente h\xc3\xb6rst, was erzeugt wird. F\xc3\xbcr die fertige Musik schaltest du ihn aus.");

    head ("Allgemein");
    body ("Doppelklick auf einen Drehregler oder Strg-Klick setzt ihn auf den Standardwert zur\xc3\xbck. Look: Dunkel / Hell umschalten, die Wahl wird mit dem Projekt gespeichert. Das Fenster ist am rechten unteren Rand skalierbar (50\xe2\x80\x93" "300 %).");
    note ("Alle Regler sind automatisierbar. Bei Stopp, Sprung oder Bypass werden alle Noten sauber beendet. Das Ergebnis h\xc3\xa4ngt nur von der Projektposition ab, nicht von der Puffergr\xc3\xb6\xc3\x9f" "e.");

    head ("Idee und Konzept");
    body ("Lars Eickst\xc3\xa4" "dt, Stromschlag Audio");
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

    auto setupLabel = [this] (juce::Label& l, const juce::String& t)
    {
        l.setText (t, juce::dontSendNotification);
        l.setJustificationType (juce::Justification::centredLeft);
        content.addAndMakeVisible (l);
    };
    setupLabel (keyLabel, "TONART");
    setupLabel (modeLabel, "MODUS");
    setupLabel (chordLabel, "AKKORDE");
    verlaufLabel.setText ("VERLAUF", juce::dontSendNotification);
    verlaufLabel.setJustificationType (juce::Justification::centred);
    content.addAndMakeVisible (verlaufLabel);
    variationLabel.setText ("VARIATION", juce::dontSendNotification);
    variationLabel.setJustificationType (juce::Justification::centred);
    content.addAndMakeVisible (variationLabel);

    keyBox.addItemList (StromscoreProcessor::keyNames(), 1);
    modeBox.addItemList (StromscoreProcessor::modeNames(), 1);
    content.addAndMakeVisible (keyBox);
    content.addAndMakeVisible (modeBox);
    keyAttachment = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, "key", keyBox);
    modeAttachment = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, "mode", modeBox);

    for (auto* s : { &verlauf, &variation })
    {
        s->setSliderStyle (juce::Slider::RotaryVerticalDrag);
        s->setMouseDragSensitivity (180);
        s->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 18);
        content.addAndMakeVisible (*s);
    }
    verlaufAttachment = std::make_unique<APVTS::SliderAttachment> (processor.apvts, "verlauf", verlauf);
    variationAttachment = std::make_unique<APVTS::SliderAttachment> (processor.apvts, "variation", variation);

    previewButton.setButtonText (u8 ("Vorh\xc3\xb6ren"));
    previewButton.setClickingTogglesState (true);
    content.addAndMakeVisible (previewButton);
    previewAttachment = std::make_unique<APVTS::ButtonAttachment> (processor.apvts, "preview", previewButton);

    content.addAndMakeVisible (chordDisplay);
    for (int i = 0; i < stromscore::kNumLayers; ++i)
    {
        layers[i].title = u8 (kLayerTitle[i]);
        layers[i].lines = u8 (kLayerNote[i]);
        layers[i].channel = i + 1;
        layers[i].start = stromscore::kLayerStart[i];
        layers[i].setTooltip (u8 ("MIDI-Kanal ") + juce::String (i + 1) + ": " + u8 (kLayerNote[i]));
        content.addAndMakeVisible (layers[i]);
    }

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

    keyBox.setTooltip (u8 ("Grundton der Tonart. Alle erzeugten Noten bleiben in der gew\xc3\xa4hlten Tonleiter."));
    modeBox.setTooltip (u8 ("Tonleiter und Akkordfolge: Moll, Dur, Dorisch, Phrygisch oder Lydisch. Jeder Akkord dauert zwei Takte."));
    verlauf.setTooltip (u8 ("Wie viel gleichzeitig passiert: Fl\xc3\xa4" "che und Bass immer, Arp ab 25 %, Farbe ab 50 %, Akzente ab 75 %. Automatisierbar."));
    variation.setTooltip (u8 ("Sechzehn Varianten derselben Einstellung. Gleiche Nummer ergibt immer dieselben Noten."));
    previewButton.setTooltip (u8 ("Einfacher Testklang im Plugin, damit du auch ohne eigene Instrumente h\xc3\xb6rst, was erzeugt wird."));
    chordDisplay.setTooltip (u8 ("Die vier Akkorde der Folge (je zwei Takte). Der klingende Akkord leuchtet. Unten: VERLAUF mit den Einsatzpunkten der Ebenen."));

    applyTheme();
    updateChordNames();
    const int savedW = processor.uiWidth.load();
    const int restoredW = juce::jlimit (kBaseW / 2, kBaseW * 3, savedW);
    setSize (restoredW, juce::roundToInt ((float) restoredW * (float) kBaseH / (float) kBaseW));
    sizeReady = true;
    startTimerHz (30);
}

StromscoreEditor::~StromscoreEditor() { stopTimer(); setLookAndFeel (nullptr); }

void StromscoreEditor::updateChordNames()
{
    const int key = juce::jlimit (0, stromscore::kNumKeys - 1, juce::roundToInt (processor.apvts.getRawParameterValue ("key")->load()));
    const int mode = juce::jlimit (0, stromscore::kNumModes - 1, juce::roundToInt (processor.apvts.getRawParameterValue ("mode")->load()));
    lastKey = key; lastMode = mode;
    for (int i = 0; i < stromscore::kChordsPerCycle; ++i)
    {
        char buf[32];
        stromscore::chordName (key, mode, stromscore::kProgressions[mode][i], buf, (int) sizeof (buf));
        chordDisplay.chords[i] = juce::String (i + 1) + "  " + juce::String (juce::CharPointer_UTF8 (buf));
    }
}

void StromscoreEditor::timerCallback()
{
    const bool wantsDark = processor.uiTheme.load() != 1;
    if (theme.dark != wantsDark) { theme = wantsDark ? darkTheme() : lightTheme(); applyTheme(); }
    const int width = processor.uiWidth.load();
    if (getWidth() != width) setSize (width, juce::roundToInt ((float) width * kBaseH / kBaseW));

    const int key = juce::roundToInt (processor.apvts.getRawParameterValue ("key")->load());
    const int mode = juce::roundToInt (processor.apvts.getRawParameterValue ("mode")->load());
    if (key != lastKey || mode != lastMode) updateChordNames();

    const float v = processor.apvts.getRawParameterValue ("verlauf")->load();
    chordDisplay.verlauf = v;
    chordDisplay.current = processor.chordIndex.load();
    chordDisplay.playing = processor.hostPlaying.load();
    chordDisplay.repaint();
    for (int i = 0; i < stromscore::kNumLayers; ++i)
    {
        const float a = processor.activity[i].exchange (0.0f);
        layers[i].activity = std::max (a, layers[i].activity * 0.88f);
        layers[i].verlauf = v;
        layers[i].repaint();
    }
}

void StromscoreEditor::applyTheme()
{
    look.setColour (juce::Slider::thumbColourId, theme.accent);
    look.setColour (juce::Slider::rotarySliderFillColourId, theme.accent);
    look.setColour (juce::Slider::rotarySliderOutlineColourId, theme.line);
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

    for (auto* l : { &keyLabel, &modeLabel, &chordLabel, &verlaufLabel, &variationLabel })
        l->setColour (juce::Label::textColourId, theme.dim);
    auto look2 = [this] (auto& c)
    {
        c.panel = theme.dark ? theme.bg : theme.bg.brighter (0.05f);
        c.line = theme.line; c.accent = theme.accent; c.text = theme.text; c.dim = theme.dim;
    };
    look2 (chordDisplay);
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
    const juce::String subtitle = u8 ("AUDIO DRAMA UNDERSCORE GENERATOR");
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

        juce::Path clef;   // Linie G liegt bei y = 22 in Pfadkoordinaten (Notenlinien bei 10 ... 26)
        clef.startNewSubPath (10.0f, 34.0f);
        clef.cubicTo (10.0f, 38.0f, 16.0f, 38.0f, 16.0f, 34.0f);
        clef.cubicTo (16.0f, 28.0f, 14.0f, 10.0f, 14.0f, 5.0f);
        clef.cubicTo (14.0f, 0.0f, 19.0f, 0.0f, 18.0f, 6.0f);
        clef.cubicTo (17.0f, 14.0f, 9.0f, 17.0f, 9.0f, 22.0f);
        clef.cubicTo (9.0f, 28.0f, 19.0f, 28.0f, 19.0f, 22.0f);
        clef.cubicTo (19.0f, 17.0f, 11.0f, 16.0f, 11.0f, 21.0f);
        g.strokePath (clef, juce::PathStrokeType (1.3f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded),
                      juce::AffineTransform::translation (x0 + 1.0f, y0 - 10.0f));

        // Noten: x, Hoehe in halben Linienabstaenden ueber der untersten Linie
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
        // Lautstaerke: p vor den Noten, f am Ende (kursiv)
        g.setFont (juce::Font (juce::FontOptions ("Times New Roman", 14.0f, juce::Font::bold | juce::Font::italic)));
        g.drawText ("p", (int) (x0 + 25.0f), (int) (y0 + 18.0f), 14, 18, juce::Justification::centred);
        g.drawText ("f", (int) (x0 + 90.0f), (int) (y0 + 18.0f), 12, 18, juce::Justification::centred);
    }

    // Obere Karte
    g.setColour (theme.panel);
    g.fillRoundedRectangle (12.0f, 76.0f, (float) W - 24.0f, 150.0f, 8.0f);
    g.setColour (theme.line);
    g.drawRoundedRectangle (12.5f, 76.5f, (float) W - 25.0f, 149.0f, 8.0f, 1.0f);
    for (float x : { 232.0f, 352.0f, 472.0f })
        g.fillRect (x, 88.0f, 1.0f, 126.0f);
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
    helpScroll.setBounds (12, 76, w - 24, 332);
    helpText.setWidth (helpScroll.getMaximumVisibleWidth());

    keyLabel.setBounds (24, 84, 200, 18);
    keyBox.setBounds (24, 106, 196, 28);
    modeLabel.setBounds (24, 148, 200, 18);
    modeBox.setBounds (24, 170, 196, 28);

    verlaufLabel.setBounds (240, 84, 104, 18);
    verlauf.setBounds (244, 104, 96, 118);
    variationLabel.setBounds (360, 84, 104, 18);
    variation.setBounds (364, 104, 96, 118);

    chordLabel.setBounds (484, 84, 312, 18);
    chordDisplay.setBounds (484, 104, w - 508, 82);
    previewButton.setBounds (484, 192, w - 508, 26);

    for (int i = 0; i < stromscore::kNumLayers; ++i)
        layers[i].setBounds (12 + i * 161, 236, 152, 172);
    helpScroll.toFront (false);
}
