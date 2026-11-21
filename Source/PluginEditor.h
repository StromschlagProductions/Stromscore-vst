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

// Das Stimmungsfeld: ziehen = Faerbung (waagerecht) und Intensitaet (senkrecht), Mausrad = Unruhe (Ring um den Punkt)
class MoodPad : public juce::Component, public juce::SettableTooltipClient
{
public:
    juce::Colour panel, line, accent, text, dim;
    float x = 0.3f, y = 0.3f, z = 0.0f;
    std::function<void (float, float)> onDrag;
    std::function<void()> onDragStart, onDragEnd;
    std::function<void (float)> onWheel;
    std::function<void (float, float)> onHover;   // Maus ueber dem Feld (ohne Klick): Feld-Karte
    struct HoverItem { juce::String name; float x = 0, y = 0; };
    HoverItem hover[3];
    int numHover = 0;
    void paint (juce::Graphics& g) override;
    void mouseDown (const juce::MouseEvent& e) override { dragging = true; numHover = 0; if (onDragStart) onDragStart(); move (e); }
    void mouseDrag (const juce::MouseEvent& e) override { move (e); }
    void mouseUp (const juce::MouseEvent&) override { dragging = false; if (onDragEnd) onDragEnd(); }
    void mouseMove (const juce::MouseEvent& e) override
    {
        if (dragging || ! onHover) return;
        const auto a = area();
        onHover (juce::jlimit (0.0f, 1.0f, (e.position.x - a.getX()) / a.getWidth()), juce::jlimit (0.0f, 1.0f, 1.0f - (e.position.y - a.getY()) / a.getHeight()));
    }
    void mouseExit (const juce::MouseEvent&) override { numHover = 0; repaint(); }
    bool dragging = false;
    void mouseWheelMove (const juce::MouseEvent&, const juce::MouseWheelDetails& w) override { if (onWheel) onWheel (w.deltaY * 0.25f); }
private:
    juce::Rectangle<float> area() const { return getLocalBounds().toFloat().reduced (10.0f); }
    void move (const juce::MouseEvent& e)
    {
        const auto a = area();
        const float nx = juce::jlimit (0.0f, 1.0f, (e.position.x - a.getX()) / a.getWidth());
        const float ny = juce::jlimit (0.0f, 1.0f, 1.0f - (e.position.y - a.getY()) / a.getHeight());
        if (onDrag) onDrag (nx, ny);
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
    void paint (juce::Graphics& g) override;
};

// Ein Kasten pro Ebene: Name, MIDI-Kanal, Muster, Oktave, "folgt / bleibt", Aus / Auto / An, Lampe fuer gespielte Noten
class LayerView : public juce::Component, public juce::SettableTooltipClient
{
public:
    LayerView()
    {
        for (auto* c : std::initializer_list<juce::Component*> { &soloButton, &muteButton, &intensity, &octBox }) addAndMakeVisible (c);
        addChildComponent (followButton); addChildComponent (combo1); addChildComponent (combo2);
    }
    juce::Colour panel, line, accent, text, dim;
    juce::String title, lines, entry;   // entry: ab wann die Ebene einsetzt
    int index = 0, channel = 1;
    bool active = true;
    float activity = 0.0f;
    juce::TextButton soloButton, muteButton, followButton;
    juce::Slider intensity;
    juce::ComboBox combo1, combo2, octBox;
    void paint (juce::Graphics& g) override;
    void resized() override
    {
        const int w = getWidth() - 24;
        combo1.setBounds (12, 50, w, 24);
        if (index == kArpIndex) { combo2.setBounds (12, 80, w / 2 - 3, 24); octBox.setBounds (12 + w / 2 + 3, 80, w - w / 2 - 3, 24); }
        else if (index < kArpIndex) octBox.setBounds (12, 80, w, 24);
        else octBox.setBounds (12, getHeight() - 60, w, 24);
        followButton.setBounds (12, getHeight() - 60, w, 24);
        intensity.setBounds (12, getHeight() - 32, w, 24);
        soloButton.setBounds (getWidth() - 76, 6, 21, 20);
        muteButton.setBounds (getWidth() - 52, 6, 21, 20);
    }
    static constexpr int kArpIndex = 2;
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
    void updateMidiLabel();
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
    juce::TextButton ccButton, previewButton, customButton, editButton, passingButton, genreScore, genrePop;
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
    std::unique_ptr<APVTS::ComboBoxAttachment> patternAttachment[4], octaveAttachment[stromscore::kNumLayers];

    juce::TextButton themeButton, helpButton;
    HelpPanel helpScroll;
    HelpView helpText;
    juce::TooltipWindow tooltipWindow { this, 400 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StromscoreEditor)
};
