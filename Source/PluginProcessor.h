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

    static constexpr int kUiWidth = 1000, kUiHeight = 656;
    static juce::StringArray keyNames();
    static juce::StringArray meterNames();
    static juce::StringArray layerNames();
    static juce::StringArray outputNames();   // die acht Ausgaenge (Flaeche lang / kurz, ...)
    static juce::String rangeName (int rangeIndex);   // Tonumfang 0 ... 5 (3 = Akzent Tupfer, 5 = Akzent Stich)
    static juce::StringArray channelNames();
    static juce::StringArray padPatternNames();
    static juce::StringArray bassPatternNames();
    static juce::StringArray arpFigureNames();
    static juce::StringArray arpRateNames();
    static juce::StringArray changeNames();
    static juce::StringArray octaveNames();
    static juce::StringArray slotRootNames();
    static juce::StringArray slotTypeNames();
    static juce::StringArray slotBarNames();
    // Szene (ab 1.3)
    static juce::StringArray entryNames();
    static juce::StringArray buildNames();         static constexpr int kBuildBars[3] = { 4, 8, 16 };
    static juce::StringArray sceneLengthNames();   static constexpr int kSceneBars[7] = { 0, 8, 16, 24, 32, 48, 64 };
    static juce::StringArray endingNames();
    static juce::StringArray driveStartNames();    static constexpr int kDriveFrom[5] = { 0, 4, 8, 16, 32 };
    static juce::StringArray driveBarsNames();     static constexpr int kDriveBars[4] = { 4, 8, 16, 32 };
    static juce::StringArray curveNames();
    // Tonumfang: Notenname wie in Studio One (mittleres C = C3), deutsche Namen; Vorlagen fuer Orchesterinstrumente
    static juce::String noteName (int midiNote);
    struct RangeTemplate { const char* name; int lo, hi; };
    static const std::vector<RangeTemplate>& rangeTemplates();

    // Die drei Achsen des Stimmungsfeldes: Faerbung, Intensitaet, Unruhe
    static constexpr const char* kAxisIds[3] = { "faerbung", "intensitaet", "unruhe" };

    juce::AudioProcessorValueTreeState apvts;
    stromscore::Settings currentSettings() const;
    std::atomic<int> uiTheme { 0 }, uiWidth { kUiWidth };
    // MIDI-CC-Nummern fuer Faerbung, Intensitaet, Unruhe (0 = aus); Vorgabe: Nuances-Fader 11, 1, 74
    std::atomic<int> ccNumber[3] { { 11 }, { 1 }, { 74 } };

    // Fuer die Anzeige
    std::atomic<float> activity[stromscore::kNumOutputs] {};   // je Ausgang, fuer die Lampen
    std::atomic<int> styleIndex { -1 }, genreInUse { 0 }, nextRoot { 0 }, nextType { 0 };
    std::atomic<float> chordProgress { 0.0f };
    std::atomic<int> ccOut[2] { { 1 }, { 11 } };   // Dynamik, Ausdruck (0 = nicht senden)
    std::atomic<int> exportBars { 8 };
    static juce::StringArray genreNames();
    // Die naechsten Takte als MIDI-Datei (eine Spur je benutztem MIDI-Kanal) fuer Drag & Drop; laeuft auf dem Nachrichten-Thread
    juce::File renderMidiFile (int bars) const;
    std::atomic<int> wendung { -1 }, chordIndex { -1 }, chordRoot { 0 }, chordType { 0 };
    std::atomic<int> meterNum { 4 }, meterDen { 4 };
    std::atomic<bool> hostPlaying { false };
    // Szene: Takte seit Szenenstart (-1 = steht), aufgeloester Einstieg, Ende erreicht, klingender Punkt im Feld (mit Fahrt)
    std::atomic<int> sceneBar { -1 }, sceneEntry { 0 };
    std::atomic<bool> sceneOver { false };
    std::atomic<float> pointX { 0.5f }, pointY { 0.1f };
    // Anlernen des Tonumfangs: die naechsten zwei Tasten am MIDI-Eingang (tiefste und hoechste) werden gemerkt
    std::atomic<int> learnLayer { -1 }, learnFirst { -1 }, learnSecond { -1 };

private:
    static juce::AudioProcessorValueTreeState::ParameterLayout createLayout();
    void handleControllers (const juce::MidiBuffer& incoming);
    void flushSounding (juce::MidiBuffer&, bool forceAllNotesOff);
    void emit (const stromscore::EventList&, juce::MidiBuffer&, juce::AudioBuffer<float>&, bool preview, bool toMidi = true);
    void publish (const stromscore::Generator&, bool playing);

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
    std::bitset<128> sounding[16];   // je MIDI-Kanal
    bool flushPending = false, wasPlaying = false;

    std::atomic<float>* pKey = nullptr; std::atomic<float>* pAxis[3] {}; std::atomic<float>* pMeter = nullptr;
    std::atomic<float>* pSwing = nullptr; std::atomic<float>* pVariation = nullptr; std::atomic<float>* pPreview = nullptr;
    std::atomic<float>* pMute[stromscore::kNumLayers] {}; std::atomic<float>* pSolo[stromscore::kNumLayers] {};
    std::atomic<float>* pLayerIntensity[stromscore::kNumLayers] {}; std::atomic<float>* pVariety = nullptr; std::atomic<float>* pPassing = nullptr; std::atomic<float>* pGenre = nullptr; std::atomic<float>* pDynamics = nullptr; std::atomic<float>* pFollow[3] {};
    std::atomic<float>* pPad = nullptr; std::atomic<float>* pBass = nullptr; std::atomic<float>* pArp = nullptr; std::atomic<float>* pRate = nullptr;
    std::atomic<float>* pChange = nullptr; std::atomic<float>* pOctave[stromscore::kNumLayers] {};
    std::atomic<float>* pRangeOn[stromscore::kNumRanges] {}; std::atomic<float>* pRangeLo[stromscore::kNumRanges] {}; std::atomic<float>* pRangeHi[stromscore::kNumRanges] {};
    std::atomic<float>* pChannel[stromscore::kNumOutputs] {}; std::atomic<float>* pLegato = nullptr; std::atomic<float>* pCustom = nullptr;
    std::atomic<float>* pScene = nullptr; std::atomic<float>* pEntry = nullptr; std::atomic<float>* pSeed = nullptr; std::atomic<float>* pBuild = nullptr;
    std::atomic<float>* pHardness = nullptr; std::atomic<float>* pSceneLen = nullptr; std::atomic<float>* pEnding = nullptr; std::atomic<float>* pMotif = nullptr;
    std::atomic<float>* pDrive = nullptr; std::atomic<float>* pDriveX = nullptr; std::atomic<float>* pDriveY = nullptr; std::atomic<float>* pDriveFrom = nullptr;
    std::atomic<float>* pDriveBars = nullptr; std::atomic<float>* pCurve = nullptr;
    std::atomic<float>* pSlotRoot[stromscore::kMaxChords] {}; std::atomic<float>* pSlotType[stromscore::kMaxChords] {}; std::atomic<float>* pSlotBars[stromscore::kMaxChords] {};
    juce::RangedAudioParameter* axisParam[3] {};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StromscoreProcessor)
};
