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

// Zeigt die Akkordfolge (vier Akkorde, der aktuelle leuchtet) und den VERLAUF mit den Einsatzpunkten der Ebenen
class ChordDisplay : public juce::Component, public juce::SettableTooltipClient
{
public:
    juce::Colour panel, line, accent, text, dim;
    juce::String chords[stromscore::kChordsPerCycle];
    int current = -1;
    bool playing = false;
    float verlauf = 0.0f;
    void paint (juce::Graphics& g) override;
};

// Ein Kasten pro Ebene: Name, MIDI-Kanal, Einsatzpunkt, Lampe fuer gespielte Noten
class LayerView : public juce::Component, public juce::SettableTooltipClient
{
public:
    juce::Colour panel, line, accent, text, dim;
    juce::String title, lines;
    int channel = 1;
    float start = 0.0f, verlauf = 0.0f, activity = 0.0f;
    void paint (juce::Graphics& g) override;
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
    void updateChordNames();

    static constexpr int kBaseW = StromscoreProcessor::kUiWidth, kBaseH = StromscoreProcessor::kUiHeight;

    StromscoreProcessor& processor;
    juce::LookAndFeel_V4 look;
    juce::Component content;
    float uiScale = 1.0f;
    Theme theme;
    bool sizeReady = false;
    juce::Image logo;

    juce::Label keyLabel, modeLabel, variationLabel, verlaufLabel, chordLabel;
    juce::ComboBox keyBox, modeBox;
    std::unique_ptr<APVTS::ComboBoxAttachment> keyAttachment, modeAttachment;
    juce::Slider verlauf, variation;
    std::unique_ptr<APVTS::SliderAttachment> verlaufAttachment, variationAttachment;
    juce::TextButton previewButton;
    std::unique_ptr<APVTS::ButtonAttachment> previewAttachment;
    ChordDisplay chordDisplay;
    LayerView layers[stromscore::kNumLayers];
    juce::TextButton themeButton, helpButton;
    HelpPanel helpScroll;
    HelpView helpText;
    juce::TooltipWindow tooltipWindow { this, 400 };
    int lastKey = -1, lastMode = -1;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StromscoreEditor)
};
