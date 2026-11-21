#pragma once
#include <juce_audio_utils/juce_audio_utils.h>
#include "ScoreEngine.h"
#include <bitset>

class StromscoreProcessor : public juce::AudioProcessor
{
public:
    StromscoreProcessor();
    ~StromscoreProcessor() override = default;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override { flushPending = true; }
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

    static constexpr int kUiWidth = 900, kUiHeight = 520;
    static juce::StringArray keyNames();
    static juce::StringArray meterNames();
    static juce::StringArray layerNames();
    static juce::StringArray padPatternNames();
    static juce::StringArray bassPatternNames();
    static juce::StringArray arpFigureNames();
    static juce::StringArray arpRateNames();
    static juce::StringArray changeNames();
    static juce::StringArray octaveNames();
    static juce::StringArray slotRootNames();
    static juce::StringArray slotTypeNames();
    static juce::StringArray slotBarNames();

    // Die drei Achsen des Stimmungsfeldes: Faerbung, Intensitaet, Unruhe
    static constexpr const char* kAxisIds[3] = { "faerbung", "intensitaet", "unruhe" };

    juce::AudioProcessorValueTreeState apvts;
    stromscore::Settings currentSettings() const;
    std::atomic<int> uiTheme { 0 }, uiWidth { kUiWidth };
    // MIDI-CC-Nummern fuer Faerbung, Intensitaet, Unruhe (0 = aus); Vorgabe: Nuances-Fader 11, 1, 74
    std::atomic<int> ccNumber[3] { { 11 }, { 1 }, { 74 } };

    // Fuer die Anzeige
    std::atomic<float> activity[stromscore::kNumLayers] {};
    std::atomic<int> styleIndex { -1 };
    std::atomic<int> wendung { -1 }, chordIndex { -1 }, chordRoot { 0 }, chordType { 0 };
    std::atomic<int> meterNum { 4 }, meterDen { 4 };
    std::atomic<bool> hostPlaying { false };

private:
    static juce::AudioProcessorValueTreeState::ParameterLayout createLayout();
    void handleControllers (const juce::MidiBuffer& incoming);
    void flushSounding (juce::MidiBuffer&, bool forceAllNotesOff);
    void emit (const stromscore::EventList&, juce::MidiBuffer&, juce::AudioBuffer<float>&, bool preview, bool toMidi = true);

    stromscore::Generator generator;
    // Vorhoeren bei stehender DAW: eigene Uhr, nur Testklang, kein MIDI
    stromscore::Generator previewGenerator;
    stromscore::EventList previewEvents;
    double previewPpq = 0.0, hostBpm = 120.0;
    bool previewRunning = false;
    stromscore::Preview preview;
    stromscore::EventList events;
    bool wasBypassed = false;
    double currentRate = 48000.0;
    int hostNum = 4, hostDen = 4;
    // Was gerade klingt (unabhaengig von der Engine): damit nach Stopp, Reset oder Bypass nie eine Note haengen bleibt
    std::bitset<128> sounding[stromscore::kNumLayers];
    bool flushPending = false, wasPlaying = false;

    std::atomic<float>* pKey = nullptr; std::atomic<float>* pAxis[3] {}; std::atomic<float>* pMeter = nullptr;
    std::atomic<float>* pSwing = nullptr; std::atomic<float>* pVariation = nullptr; std::atomic<float>* pPreview = nullptr;
    std::atomic<float>* pMute[stromscore::kNumLayers] {}; std::atomic<float>* pSolo[stromscore::kNumLayers] {};
    std::atomic<float>* pLayerIntensity[stromscore::kNumLayers] {}; std::atomic<float>* pVariety = nullptr; std::atomic<float>* pPassing = nullptr; std::atomic<float>* pFollow[3] {};
    std::atomic<float>* pPad = nullptr; std::atomic<float>* pBass = nullptr; std::atomic<float>* pArp = nullptr; std::atomic<float>* pRate = nullptr;
    std::atomic<float>* pChange = nullptr; std::atomic<float>* pOctave[stromscore::kNumLayers] {}; std::atomic<float>* pCustom = nullptr;
    std::atomic<float>* pSlotRoot[stromscore::kMaxChords] {}; std::atomic<float>* pSlotType[stromscore::kMaxChords] {}; std::atomic<float>* pSlotBars[stromscore::kMaxChords] {};
    juce::RangedAudioParameter* axisParam[3] {};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StromscoreProcessor)
};
