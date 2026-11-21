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
    void paint (juce::Graphics& g) override;
    void mouseDown (const juce::MouseEvent& e) override { if (onDragStart) onDragStart(); move (e); }
    void mouseDrag (const juce::MouseEvent& e) override { move (e); }
    void mouseUp (const juce::MouseEvent&) override { if (onDragEnd) onDragEnd(); }
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
    bool playing = false;
    void paint (juce::Graphics& g) override;
};

// Ein Kasten pro Ebene: Name, MIDI-Kanal, Muster, "folgt / bleibt", Aus / Auto / An, Lampe fuer gespielte Noten
class LayerView : public juce::Component, public juce::SettableTooltipClient
{
public:
    LayerView() { addAndMakeVisible (modeButton); addChildComponent (followButton); addChildComponent (combo1); addChildComponent (combo2); }
    juce::Colour panel, line, accent, text, dim;
    juce::String title, lines;
    int channel = 1, mode = 1;
    bool active = true;
    float activity = 0.0f;
    juce::TextButton modeButton, followButton;
    juce::ComboBox combo1, combo2;
    void paint (juce::Graphics& g) override;
    void resized() override
    {
        const int w = getWidth() - 24;
        combo1.setBounds (12, 50, w, 24);
        combo2.setBounds (12, 80, w, 24);
        followButton.setBounds (12, getHeight() - 60, w, 24);
        modeButton.setBounds (12, getHeight() - 32, w, 24);
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
    void updateModeButton (int layer, int mode);
    void updateCcButton();
    void showCcMenu();

    static constexpr int kBaseW = StromscoreProcessor::kUiWidth, kBaseH = StromscoreProcessor::kUiHeight;

    StromscoreProcessor& processor;
    juce::LookAndFeel_V4 look;
    juce::Component content;
    float uiScale = 1.0f;
    Theme theme;
    bool sizeReady = false;
    juce::Image logo;

    MoodPad pad;
    std::unique_ptr<juce::ParameterAttachment> axisAttachment[3];

    juce::Label padLabel, padValues, unruheLabel, keyLabel, meterLabel, variationLabel, swingLabel, chordLabel;
    juce::Slider unruhe, variation, swing;
    std::unique_ptr<APVTS::SliderAttachment> unruheAttachment, variationAttachment, swingAttachment;
    juce::ComboBox keyBox, meterBox;
    std::unique_ptr<APVTS::ComboBoxAttachment> keyAttachment, meterAttachment;
    juce::TextButton ccButton, previewButton;
    std::unique_ptr<APVTS::ButtonAttachment> previewAttachment;
    ChordDisplay chordDisplay;

    LayerView layers[stromscore::kNumLayers];
    std::unique_ptr<juce::ParameterAttachment> modeAttachment[stromscore::kNumLayers];
    std::unique_ptr<APVTS::ButtonAttachment> followAttachment[3];
    std::unique_ptr<APVTS::ComboBoxAttachment> patternAttachment[4];

    juce::TextButton themeButton, helpButton;
    HelpPanel helpScroll;
    HelpView helpText;
    juce::TooltipWindow tooltipWindow { this, 400 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StromscoreEditor)
};
