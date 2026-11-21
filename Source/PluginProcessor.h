#pragma once
#include <juce_audio_utils/juce_audio_utils.h>
#include "ScoreEngine.h"

class StromscoreProcessor : public juce::AudioProcessor
{
public:
    StromscoreProcessor();
    ~StromscoreProcessor() override = default;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override {}
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void processBlockBypassed (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void reset() override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return "Stromscore"; }
    bool acceptsMidi() const override { return true; }
    bool producesMidi() const override { return true; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.3; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram (int) override {}
    const juce::String getProgramName (int) override { return {}; }
    void changeProgramName (int, const juce::String&) override {}

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    static constexpr int kUiWidth = 820, kUiHeight = 420;
    static juce::StringArray keyNames();
    static juce::StringArray modeNames();

    juce::AudioProcessorValueTreeState apvts;
    std::atomic<int> uiTheme { 0 }, uiWidth { kUiWidth };

    // Fuer die Anzeige: Aktivitaet je Ebene (wird bei jedem Anschlag auf 1 gesetzt) und aktueller Akkord
    std::atomic<float> activity[stromscore::kNumLayers] {};
    std::atomic<int> chordIndex { -1 };
    std::atomic<bool> hostPlaying { false };

private:
    static juce::AudioProcessorValueTreeState::ParameterLayout createLayout();
    stromscore::Settings currentSettings() const;
    void emit (const stromscore::EventList&, juce::MidiBuffer&, juce::AudioBuffer<float>&, bool preview);

    stromscore::Generator generator;
    stromscore::Preview preview;
    stromscore::EventList events;
    bool wasBypassed = false;
    double currentRate = 48000.0;

    std::atomic<float>* pKey = nullptr; std::atomic<float>* pMode = nullptr; std::atomic<float>* pVerlauf = nullptr;
    std::atomic<float>* pVariation = nullptr; std::atomic<float>* pPreview = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StromscoreProcessor)
};
