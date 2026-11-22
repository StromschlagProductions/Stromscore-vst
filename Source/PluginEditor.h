#pragma once
#include "PluginProcessor.h"

// Onboard-Hilfe: formatierter Text, scrollbar in einem Viewport (wie bei den anderen Stromschlag-Plugins)
class HelpView : public juce::Component
{
public:
    void setAttributed (const juce::AttributedString& s) { text = s; relayout(); }
    void setWidth (int w) { if (w != laidOutW) { laidOutW = w; relayout(); } }
    void paint (juce::Graphics& g) override { tl.draw (g, getLocalBounds().toFloat().reduced (14.0f, 10.0f)); }
private:
    void relayout()
    {
        const int w = juce::jmax (120, laidOutW);
        tl.createLayout (text, (float) (w - 28));
        setSize (w, (int) std::ceil (tl.getHeight()) + 24);
        repaint();
    }
    juce::AttributedString text;
    juce::TextLayout tl;
    int laidOutW = 0;
};

class HelpPanel : public juce::Viewport
{
public:
    juce::Colour fill, edge;
    void paint (juce::Graphics& g) override
    {
        auto r = getLocalBounds().toFloat();
        g.setColour (fill); g.fillRoundedRectangle (r, 8.0f);
        g.setColour (edge); g.drawRoundedRectangle (r.reduced (0.5f), 8.0f, 1.0f);
    }
};

// Das Stimmungsfeld: ziehen = Faerbung (waagerecht) und Intensitaet (senkrecht), Mausrad = Unruhe (Ring um den Punkt).
// Mit Fahrt: ein zweiter Punkt B (Ziel), links wird A, rechts wird B gezogen; waehrend der Wiedergabe zeigt ein
// kleiner Punkt, wo die Musik gerade ist, und die Unruhe zappelt dort. Dazu (ab 1.4): Farbzonen in den Ecken, eine
// verblassende Spur des klingenden Punkts und ein Licht je Ebene am Punkt.
class MoodPad : public juce::Component, public juce::SettableTooltipClient
{
public:
    juce::Colour panel, line, accent, text, dim;
    float x = 0.3f, y = 0.3f, z = 0.0f;
    bool showB = false, showNow = false;
    stromscore::DrivePath route;
    bool altHeld=false, routeEditable=true;
    int selectedBend=-1; juce::Point<float> handleDragOffset;
    std::function<void(const stromscore::DrivePath&)> onRoute;
    std::function<bool()> mayEditRoute;
    bool routeMouseDown(const juce::MouseEvent&);
    void routeMouseDrag(const juce::MouseEvent&);
    void modifierKeysChanged(const juce::ModifierKeys& m) override {altHeld=m.isAltDown();repaint();}
    bool targetPending = false;                   // Ziel B per Rechtsklick gesetzt, die Fahrt laeuft noch nicht
    std::function<void()> onSetTarget;
    std::function<bool (float, float)> onHideTarget;
    float bx = 0.8f, by = 0.85f, nowX = 0.0f, nowY = 0.0f;
    std::function<void (float, float)> onDrag, onDragB;
    std::function<void()> onDragStart, onDragEnd, onDragStartB, onDragEndB;
    std::function<void (float)> onWheel;
    std::function<void (float, float)> onHover;   // Maus ueber dem Feld (ohne Klick): Feld-Karte
    struct HoverItem { juce::String name; float x = 0, y = 0; };
    HoverItem hover[3];
    int numHover = 0;
    void paint (juce::Graphics& g) override;
    void mouseDown (const juce::MouseEvent& e) override
    {
        numHover = 0;
        if(e.mods.isAltDown()) {previousRightClick=false;routeMouseDown(e);return;}
        if (previousRightClick && e.mods.isRightButtonDown() && e.getNumberOfClicks() == 2
            && onHideTarget && onHideTarget (beforeClickBX, beforeClickBY))
        {
            dragging = draggingB = false; previousRightClick=false; showB = targetPending = false; repaint(); return;
        }
        previousRightClick=e.mods.isRightButtonDown();
        dragging = true;
        if (e.mods.isRightButtonDown())   // rechte Taste: nur das Ziel B setzen, ohne die Fahrt zu starten
        {
            beforeClickBX = bx; beforeClickBY = by;
            draggingB = true;
            if (onSetTarget) onSetTarget();
        }
        else draggingB = false;
        if (draggingB) { if (onDragStartB) onDragStartB(); } else if (onDragStart) onDragStart();
        move (e);
    }
    void mouseDrag (const juce::MouseEvent& e) override { if(routeDrag>=0){routeMouseDrag(e);return;} if (dragging) move (e); }
    void mouseUp (const juce::MouseEvent&) override
    {
        if(routeDrag>=0){routeDrag=-1;selectedBend=-1;return;}
        if (! dragging) return;
        dragging = false;
        if (draggingB) { if (onDragEndB) onDragEndB(); } else if (onDragEnd) onDragEnd();
        draggingB = false;
    }
    void mouseMove (const juce::MouseEvent& e) override
    {
        altHeld=e.mods.isAltDown(); repaint();
        if (dragging || ! onHover || altHeld) return;
        const auto a = area();
        onHover (juce::jlimit (0.0f, 1.0f, (e.position.x - a.getX()) / a.getWidth()), juce::jlimit (0.0f, 1.0f, 1.0f - (e.position.y - a.getY()) / a.getHeight()));
    }
    void mouseExit (const juce::MouseEvent&) override { numHover = 0; repaint(); }
    bool dragging = false, draggingB = false;
    void mouseWheelMove (const juce::MouseEvent&, const juce::MouseWheelDetails& w) override { if (onWheel) onWheel (w.deltaY * 0.25f); }
private:
    int routeDrag=-1; bool bendDrag=false, previousRightClick=false;
    juce::Point<float> routeDown; stromscore::DrivePoint controlDown;
    float beforeClickBX = 0.8f, beforeClickBY = 0.85f;
    juce::Rectangle<float> area() const { return getLocalBounds().toFloat().reduced (10.0f); }
    void move (const juce::MouseEvent& e)
    {
        const auto a = area();
        const float nx = juce::jlimit (0.0f, 1.0f, (e.position.x - a.getX()) / a.getWidth());
        const float ny = juce::jlimit (0.0f, 1.0f, 1.0f - (e.position.y - a.getY()) / a.getHeight());
        if (draggingB) { if (onDragB) onDragB (nx, ny); }
        else if (onDrag) onDrag (nx, ny);
    }
};

// Akkord-Anzeige: aktueller Akkord gross, darunter die Wendung und ihre Akkorde
class ChordDisplay : public juce::Component, public juce::SettableTooltipClient
{
public:
    juce::Colour panel, line, accent, text, dim;
    juce::String chord, wendung, meter;
    juce::String chips[stromscore::kMaxChords];
    int numChips = 0, current = -1;
    bool playing = false, custom = false;
    juce::String nextChord;    // naechster Akkord
    float progress = 0.0f;     // bis zum naechsten Akkordwechsel
    juce::String candidates;   // Wendungen, die an der aktuellen Stelle in Frage kommen
    float mood[3] {};   // Faerbung, Intensitaet, Unruhe (0..1), live angezeigt
    // Die drei Balken lassen sich ziehen (ab 1.4): Faerbung, Intensitaet, Unruhe
    std::function<void (int)> onBarStart, onBarEnd;
    std::function<void (int, float)> onBar;
    void paint (juce::Graphics& g) override;
    void mouseDown (const juce::MouseEvent& e) override
    {
        dragAxis = -1;
        for (int i = 0; i < 3; ++i)
            if (barHit (i).contains (e.position)) dragAxis = i;
        if (dragAxis < 0) return;
        if (onBarStart) onBarStart (dragAxis);
        mouseDrag (e);
    }
    void mouseDrag (const juce::MouseEvent& e) override
    {
        if (dragAxis < 0 || ! onBar) return;
        const auto b = bar (dragAxis);
        onBar (dragAxis, juce::jlimit (0.0f, 1.0f, (e.position.x - b.getX()) / b.getWidth()));
    }
    void mouseUp (const juce::MouseEvent&) override { if (dragAxis >= 0 && onBarEnd) onBarEnd (dragAxis); dragAxis = -1; }
    void mouseMove (const juce::MouseEvent& e) override
    {
        bool over = false;
        for (int i = 0; i < 3; ++i) over = over || barHit (i).contains (e.position);
        setMouseCursor (over ? juce::MouseCursor::LeftRightResizeCursor : juce::MouseCursor::NormalCursor);
    }
    juce::Rectangle<float> bar (int i) const
    {
        const float top = (float) getHeight() - 62.0f + (float) i * 18.0f;
        return { 14.0f + kBarLabelW, top + 5.0f, (float) getWidth() - 28.0f - kBarLabelW - kBarValueW - 10.0f, 6.0f };
    }
private:
    static constexpr float kBarLabelW = 74.0f, kBarValueW = 42.0f;
    juce::Rectangle<float> barHit (int i) const { return bar (i).expanded (8.0f, 6.0f); }
    int dragAxis = -1;
};

// Ein Kasten pro Ebene. Kopfzeile: Name, Mute, Solo (wie in Studio One), Lampe (bei zwei Ausgaengen zwei Punkte).
// Darunter Zeilen mit Beschriftung links: MIDI-Kanal (Flaeche und Bass: lang und kurz, Akzent: Tupfer und Stich,
// je mit eigenem Tonumfang), Muster, Tempo (Arp), Legato (Gegenstimme), "folgt / bleibt", Intensitaet, Oktave und Umfang.
class LayerView : public juce::Component, public juce::SettableTooltipClient
{
public:
    LayerView()
    {
        for (auto* c : std::initializer_list<juce::Component*> { &muteButton, &soloButton, &intensity, &octBox, &chanBox[0] }) addAndMakeVisible (c);
        for (auto* c : std::initializer_list<juce::Component*> { &chanBox[1], &rangeButton, &rangeButton2, &followButton, &legatoButton, &motifButton, &combo1, &combo2 })
            addChildComponent (c);
    }
    juce::Colour panel, line, accent, text, dim;
    juce::String title, entry;          // entry: ab wann die Ebene einsetzt
    juce::String rowLabel[4];           // Beschriftungen der Zeilen 1 ... 4
    int index = 0, numLamps = 1;
    bool active = true;
    float activity[2] {};
    juce::TextButton soloButton, muteButton, followButton, rangeButton, rangeButton2, legatoButton, motifButton;
    juce::Slider intensity;
    juce::ComboBox combo1, combo2, octBox, chanBox[2];
    void paint (juce::Graphics& g) override;
    void resized() override
    {
        const int w = getWidth();
        const int cx = kLabelW + 14, cw = w - cx - 12;   // Spalte der Bedienelemente
        auto row = [] (int i) { return 34 + i * 28; };
        muteButton.setBounds (w - 82, 6, 22, 20);
        soloButton.setBounds (w - 57, 6, 22, 20);
        const bool accent = index == stromscore::kAkzent;
        chanBox[0].setBounds (cx, row (0), cw, 24);
        chanBox[1].setBounds (cx, row (accent ? 2 : 1), cw, 24);
        if (accent)   // Akzent: Tupfer und Stich je mit eigener Zeile fuer den Tonumfang darunter
        {
            rangeButton.setBounds (cx, row (1), cw, 24);
            rangeButton2.setBounds (cx, row (3), cw, 24);
        }
        combo2.setBounds (cx, row (1), cw, 24);         // Arp: Tempo
        legatoButton.setBounds (cx, row (1), cw / 2 - 2, 24);                 // Gegenstimme: Legato und Motiv
        motifButton.setBounds (cx + cw / 2 + 2, row (1), cw - cw / 2 - 2, 24);
        combo1.setBounds (cx, row (2), cw, 24);         // Muster
        followButton.setBounds (12, row (3), w - 24, 24);
        intensity.setBounds (12, getHeight() - 64, w - 24, 24);
        const int okW = accent ? w - 24 : 78;
        octBox.setBounds (12, getHeight() - 34, okW, 24);
        if (! accent) rangeButton.setBounds (12 + okW + 6, getHeight() - 34, w - 24 - okW - 6, 24);
    }
    static constexpr int kLabelW = 46;
};

// Tonumfang einer Ebene: Ein/Aus, tiefster und hoechster Ton, Vorlagen, Anlernen ueber zwei Tasten am MIDI-Eingang.
// Beim Stich (ab 1.4) zuerst die Wahl: Fest (eine Taste, mit Anlernen und Hoeren) oder Akkord (Grundton, mit Tonumfang).
// Solange das Fenster offen ist, kann das Keyboard auf die Kanaele dieser Ebene durchgeleitet werden.
class RangePanel : public juce::Component, private juce::Timer
{
public:
    RangePanel (StromscoreProcessor& p, int rangeIndex, juce::Colour panel, juce::Colour accent, juce::Colour text, juce::Colour dim);
    ~RangePanel() override;
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    void timerCallback() override;
    void applyRange (int lo, int hi);
    void setParam (const juce::String& id, float value);
    bool isStich() const { return layer == 5; }
    bool fixedMode() const;
    void updateMode (bool fixed);
    void updateThru();
    int offset() const { return isStich() ? 30 : 0; }
    StromscoreProcessor& processor;
    int layer;
    juce::Colour panelColour, accentColour, textColour, dimColour;
    juce::TextButton onButton, learnButton, thruButton, modeFixed, modeChord, tonePlay, toneLearn;
    juce::ComboBox templateBox, loBox, hiBox, toneBox;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> onAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> loAttachment, hiAttachment, toneAttachment;
    std::unique_ptr<juce::ParameterAttachment> modeAttachment;
    juce::String status;
    bool shownFixed = false;
};

// Feld zum Herausziehen der naechsten Takte als MIDI-Datei; Klick wechselt die Laenge
class MidiDragBox : public juce::Component, public juce::SettableTooltipClient
{
public:
    juce::Colour panel, line, accent, text, dim;
    juce::String label;
    std::function<juce::File()> render;
    std::function<void()> onClick;
    void paint (juce::Graphics& g) override
    {
        auto r = getLocalBounds().toFloat().reduced (0.5f);
        g.setColour (over ? accent.withAlpha (0.18f) : panel);
        g.fillRoundedRectangle (r, 4.0f);
        g.setColour (accent);
        g.drawRoundedRectangle (r, 4.0f, 1.2f);
        g.setFont (juce::FontOptions (12.0f, juce::Font::bold));
        g.drawText (label, getLocalBounds(), juce::Justification::centred);
    }
    void mouseEnter (const juce::MouseEvent&) override { over = true; repaint(); }
    void mouseExit (const juce::MouseEvent&) override { over = false; repaint(); }
    void mouseDown (const juce::MouseEvent&) override { started = false; }
    void mouseDrag (const juce::MouseEvent& e) override
    {
        if (started || e.getDistanceFromDragStart() < 6 || ! render) return;
        started = true;
        const auto file = render();
        if (file.existsAsFile()) juce::DragAndDropContainer::performExternalDragDropOfFiles ({ file.getFullPathName() }, false, this);
    }
    void mouseUp (const juce::MouseEvent&) override { if (! started && onClick) onClick(); }
private:
    bool over = false, started = false;
};

// Eigene Akkordfolge: acht Plaetze mit Grundton, Art und Laenge (ueber der oberen Karte eingeblendet)
class SlotPanel : public juce::Component
{
public:
    SlotPanel()
    {
        for (int i = 0; i < stromscore::kMaxChords; ++i) { addAndMakeVisible (root[i]); addAndMakeVisible (type[i]); addAndMakeVisible (bars[i]); }
        addAndMakeVisible (doneButton);
    }
    juce::Colour panel, line, accent, text, dim;
    juce::ComboBox root[stromscore::kMaxChords], type[stromscore::kMaxChords], bars[stromscore::kMaxChords];
    juce::TextButton doneButton;
    juce::String totalText;
    void paint (juce::Graphics& g) override;
    void resized() override
    {
        const int cw = (getWidth() - 32 - 7 * 8) / stromscore::kMaxChords;
        for (int i = 0; i < stromscore::kMaxChords; ++i)
        {
            const int x = 16 + i * (cw + 8);
            root[i].setBounds (x, 88, cw, 26);
            type[i].setBounds (x, 120, cw, 26);
            bars[i].setBounds (x, 152, cw, 26);
        }
        doneButton.setBounds (getWidth() - 136, getHeight() - 42, 120, 28);
    }
};

// Look: kleine Auswahlfelder (Ebenen) mit schmalerem Pfeil und etwas kleinerer Schrift, damit kurze Texte ganz passen
class StromLook : public juce::LookAndFeel_V4
{
public:
    static int arrowWidth (int height) { return height <= 24 ? 18 : 30; }
    juce::Font getComboBoxFont (juce::ComboBox& box) override
    { return juce::Font (juce::FontOptions (juce::jmin (16.0f, (float) box.getHeight() * (box.getHeight() <= 24 ? 0.58f : 0.62f)))); }
    void positionComboBoxText (juce::ComboBox& box, juce::Label& label) override
    {
        label.setBounds (1, 1, box.getWidth() - arrowWidth (box.getHeight()), box.getHeight() - 2);
        label.setFont (getComboBoxFont (box));
    }
    // Balken-Regler (Intensitaet je Ebene): Fuellung von der Mitte aus, Schrift bleibt lesbar
    void drawLinearSlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minPos, float maxPos,
                           juce::Slider::SliderStyle style, juce::Slider& slider) override
    {
        if (style != juce::Slider::LinearBar)
        {
            juce::LookAndFeel_V4::drawLinearSlider (g, x, y, width, height, sliderPos, minPos, maxPos, style, slider);
            return;
        }
        const juce::Rectangle<float> r ((float) x, (float) y, (float) width, (float) height);
        g.setColour (findColour (juce::ComboBox::backgroundColourId));
        g.fillRoundedRectangle (r, 3.0f);
        const double range = slider.getMaximum() - slider.getMinimum();
        const float centre = range > 0.0 ? (float) x + (float) width * (float) ((0.0 - slider.getMinimum()) / range) : r.getCentreX();
        const float a = std::min (centre, sliderPos), b = std::max (centre, sliderPos);
        g.setColour (slider.findColour (juce::Slider::trackColourId).withAlpha (0.45f));
        g.fillRect (juce::Rectangle<float> (a, r.getY() + 1.0f, std::max (1.0f, b - a), r.getHeight() - 2.0f));
        g.setColour (findColour (juce::ComboBox::outlineColourId));
        g.fillRect (centre - 0.5f, r.getY() + 3.0f, 1.0f, r.getHeight() - 6.0f);
        g.drawRoundedRectangle (r.reduced (0.5f), 3.0f, 1.0f);
    }

    // Tooltips: grosse Schrift (18 pt), links ausgerichtet, ausgewogene Zeilen bis 520 Punkte Breite
    static juce::TextLayout tipLayout (const juce::String& text, juce::Colour colour)
    {
        juce::AttributedString s;
        s.setJustification (juce::Justification::topLeft);
        s.setWordWrap (juce::AttributedString::byWord);
        s.append (text, juce::Font (juce::FontOptions (18.0f)), colour);
        s.setLineSpacing (2.0f);
        juce::TextLayout tl;
        tl.createLayoutWithBalancedLineLengths (s, 520.0f);
        return tl;
    }
    juce::Rectangle<int> getTooltipBounds (const juce::String& text, juce::Point<int> pos, juce::Rectangle<int> area) override
    {
        const auto tl = tipLayout (text, juce::Colours::black);
        const int w = (int) std::ceil (tl.getWidth()) + 28, h = (int) std::ceil (tl.getHeight()) + 20;
        return juce::Rectangle<int> (pos.x > area.getCentreX() ? pos.x - (w + 12) : pos.x + 24,
                                     pos.y > area.getCentreY() ? pos.y - (h + 6) : pos.y + 6, w, h).constrainedWithin (area);
    }
    void drawTooltip (juce::Graphics& g, const juce::String& text, int width, int height) override
    {
        const juce::Rectangle<float> r (0.0f, 0.0f, (float) width, (float) height);
        g.setColour (findColour (juce::TooltipWindow::backgroundColourId));
        g.fillRoundedRectangle (r, 5.0f);
        g.setColour (findColour (juce::TooltipWindow::outlineColourId));
        g.drawRoundedRectangle (r.reduced (0.5f), 5.0f, 1.0f);
        tipLayout (text, findColour (juce::TooltipWindow::textColourId)).draw (g, r.reduced (14.0f, 10.0f));
    }

    void drawComboBox (juce::Graphics& g, int width, int height, bool, int, int, int, int, juce::ComboBox& box) override
    {
        const juce::Rectangle<float> r (0.0f, 0.0f, (float) width, (float) height);
        g.setColour (box.findColour (juce::ComboBox::backgroundColourId));
        g.fillRoundedRectangle (r, 3.0f);
        g.setColour (box.findColour (juce::ComboBox::outlineColourId));
        g.drawRoundedRectangle (r.reduced (0.5f), 3.0f, 1.0f);
        const float aw = (float) arrowWidth (height);
        const float x0 = (float) width - aw + (aw > 20.0f ? 3.0f : 1.0f), x1 = (float) width - (aw > 20.0f ? 13.0f : 7.0f);
        const float cy = (float) height * 0.5f;
        juce::Path p;
        p.startNewSubPath (x0, cy - 2.0f);
        p.lineTo (0.5f * (x0 + x1), cy + 3.0f);
        p.lineTo (x1, cy - 2.0f);
        g.setColour (box.findColour (juce::ComboBox::arrowColourId).withAlpha (box.isEnabled() ? 0.9f : 0.2f));
        g.strokePath (p, juce::PathStrokeType (2.0f));
    }
};

class StromscoreEditor : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    explicit StromscoreEditor (StromscoreProcessor&);
    ~StromscoreEditor() override;
    void showOutputCcRanges (int channel = 1);
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using APVTS = juce::AudioProcessorValueTreeState;
    struct Theme { juce::Colour bg, panel, accent, text, dim, line; bool dark; };
    static Theme darkTheme();
    static Theme lightTheme();
    void applyTheme();
    void timerCallback() override;
    void updateCcButton();
    void showCcMenu();
    void showCcRanges (int channel, juce::Component& anchor);
    void showWendungInfo();
    void updateMidiLabel();
    void showRangePanel (int rangeIndex);
    juce::TextButton& rangeButtonFor (int rangeIndex);
    void updateRangeButtons();
    void updateSceneStatus();
    float subtitleEnd() const;

    static constexpr int kBaseW = StromscoreProcessor::kUiWidth, kBaseH = StromscoreProcessor::kUiHeight;
    static constexpr float kSubtitleX = 244.0f, kSymbolW = 64.0f;

    StromscoreProcessor& processor;
    StromLook look;
    juce::Component content;
    float uiScale = 1.0f;
    Theme theme;
    bool sizeReady = false;
    juce::Image logo;

    MoodPad pad;
    std::unique_ptr<juce::ParameterAttachment> axisAttachment[3];

    juce::Label varietyLabel;
    juce::Slider variety;
    std::unique_ptr<APVTS::SliderAttachment> varietyAttachment;
    juce::Label padLabel, keyLabel, meterLabel, variationLabel, swingLabel, chordLabel, changeLabel, customLabel;
    juce::Slider variation, swing;
    std::unique_ptr<APVTS::SliderAttachment> variationAttachment, swingAttachment;
    juce::ComboBox keyBox, meterBox, changeBox;
    std::unique_ptr<APVTS::ComboBoxAttachment> keyAttachment, meterAttachment, changeAttachment;
    juce::TextButton infoButton, ccButton, previewButton, customButton, editButton, passingButton, genreScore, genrePop;
    std::unique_ptr<juce::ParameterAttachment> genreAttachment;
    MidiDragBox midiDrag;
    std::unique_ptr<APVTS::ButtonAttachment> previewAttachment, customAttachment, passingAttachment;
    SlotPanel slots;
    std::unique_ptr<APVTS::ComboBoxAttachment> slotAttachment[3 * stromscore::kMaxChords];
    ChordDisplay chordDisplay;

    LayerView layers[stromscore::kNumLayers];
    std::unique_ptr<APVTS::ButtonAttachment> soloAttachment[stromscore::kNumLayers], muteAttachment[stromscore::kNumLayers];
    std::unique_ptr<APVTS::SliderAttachment> intensityAttachment[stromscore::kNumLayers];
    std::unique_ptr<APVTS::ButtonAttachment> followAttachment[3];
    std::unique_ptr<APVTS::ComboBoxAttachment> patternAttachment[4], octaveAttachment[stromscore::kNumLayers], channelAttachment[stromscore::kNumOutputs];
    std::unique_ptr<APVTS::ButtonAttachment> legatoAttachment;

    // Szene und Fahrt (ab 1.3)
    juce::Label sceneLabel, driveLabel, entryLabel, lengthLabel, endLabel, startLabel, durLabel, curveLabel, sceneStatus;
    juce::TextButton sceneButton, diceButton, driveButton, finishButton;
    juce::ComboBox buildBox, entryBox, lengthBox, endBox, startBox, durBox, curveBox;
    juce::Slider hardness;
    std::unique_ptr<APVTS::ButtonAttachment> sceneAttachment, driveAttachment, motifAttachment, finishAttachment;
    std::unique_ptr<juce::ParameterAttachment> numberAttachment[4];
    std::unique_ptr<APVTS::ComboBoxAttachment> buildAttachment, entryAttachment, lengthAttachment, endAttachment, startAttachment, durAttachment, curveAttachment;
    std::unique_ptr<APVTS::SliderAttachment> hardnessAttachment;
    std::unique_ptr<juce::ParameterAttachment> targetAttachment[2];

    juce::TextButton themeButton, helpButton;
    HelpPanel helpScroll;
    HelpView helpText;
    juce::TooltipWindow tooltipWindow { this, 400 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StromscoreEditor)
};
