#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace
{
juce::String u8 (const char* s) { return juce::String (juce::CharPointer_UTF8 (s)); }

juce::AudioParameterFloatAttributes percent()
{
    return juce::AudioParameterFloatAttributes()
        .withStringFromValueFunction ([] (float v, int) { return juce::String (juce::roundToInt (v * 100.0f)) + " %"; })
        .withValueFromStringFunction ([] (const juce::String& t) { return juce::jlimit (0.0f, 1.0f, t.retainCharacters ("0123456789.,").replaceCharacter (',', '.').getFloatValue() / 100.0f); });
}
}

juce::StringArray StromscoreProcessor::keyNames()
{
    return { "C", "Cis / Des", "D", "Dis / Es", "E", "F", "Fis / Ges", "G", "Gis / As", "A", "Ais / B", "H" };
}
juce::StringArray StromscoreProcessor::meterNames()  { return { "Vom Projekt", "4/4", "3/4", "6/8", "5/4", "7/8", "5/8", "12/8" }; }
juce::StringArray StromscoreProcessor::layerNames()  { return { u8 ("Fläche"), "Bass", "Arp", "Farbe", "Akzente" }; }
juce::StringArray StromscoreProcessor::padPatternNames()  { return { "Auto", "Gehalten", u8 ("Schläge"), "Puls" }; }
juce::StringArray StromscoreProcessor::bassPatternNames() { return { "Auto", "Gehalten", "Halbe", "Viertel", "Achtel", "Puls", "Oktaven", "Funk", "Pendel" }; }
juce::StringArray StromscoreProcessor::arpFigureNames()   { return { "Auto", u8 ("Aufwärts"), u8 ("Abwärts"), "Kreisend", "Zelle", "Riff", "Glitzern" }; }
juce::StringArray StromscoreProcessor::arpRateNames()     { return { "Auto", "Viertel", "Achtel", "Sechzehntel" }; }

juce::AudioProcessorValueTreeState::ParameterLayout StromscoreProcessor::createLayout()
{
    using namespace juce;
    AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "key", 1 }, "Tonart", keyNames(), 9));
    layout.add (std::make_unique<AudioParameterFloat> (ParameterID { "faerbung", 1 }, u8 ("Färbung"), NormalisableRange<float> (0.0f, 1.0f), 0.3f, percent()));
    layout.add (std::make_unique<AudioParameterFloat> (ParameterID { "intensitaet", 1 }, u8 ("Intensität"), NormalisableRange<float> (0.0f, 1.0f), 0.3f, percent()));
    layout.add (std::make_unique<AudioParameterFloat> (ParameterID { "unruhe", 1 }, "Unruhe", NormalisableRange<float> (0.0f, 1.0f), 0.0f, percent()));
    layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "takt", 1 }, "Takt", meterNames(), 0));
    layout.add (std::make_unique<AudioParameterFloat> (ParameterID { "swing", 1 }, "Swing", NormalisableRange<float> (0.0f, 1.0f), 0.0f, percent()));
    layout.add (std::make_unique<AudioParameterInt> (ParameterID { "variation", 1 }, "Variation", 1, 16, 1));
    for (int i = 0; i < stromscore::kNumLayers; ++i)
        layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "layer" + String (i + 1), 1 },
            layerNames()[i] + " Ebene", StringArray { "Aus", "Auto", "An" }, 1));
    for (int i = 0; i < 3; ++i)
        layout.add (std::make_unique<AudioParameterBool> (ParameterID { "follow" + String (i + 1), 1 },
            layerNames()[i] + " folgt den Akkorden", true));
    layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "padPattern", 1 }, u8 ("Fläche Muster"), padPatternNames(), 0));
    layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "bassPattern", 1 }, "Bass Muster", bassPatternNames(), 0));
    layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "arpFigure", 1 }, "Arp Figur", arpFigureNames(), 0));
    layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "arpRate", 1 }, "Arp Tempo", arpRateNames(), 0));
    layout.add (std::make_unique<AudioParameterBool> (ParameterID { "preview", 1 }, u8 ("Vorhören"), false));
    return layout;
}

StromscoreProcessor::StromscoreProcessor()
    : AudioProcessor (BusesProperties().withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      apvts (*this, nullptr, "STROMSCORE", createLayout())
{
    pKey = apvts.getRawParameterValue ("key");
    for (int i = 0; i < 3; ++i) { pAxis[i] = apvts.getRawParameterValue (kAxisIds[i]); axisParam[i] = apvts.getParameter (kAxisIds[i]); }
    pMeter = apvts.getRawParameterValue ("takt");
    pSwing = apvts.getRawParameterValue ("swing");
    pVariation = apvts.getRawParameterValue ("variation");
    pPreview = apvts.getRawParameterValue ("preview");
    for (int i = 0; i < stromscore::kNumLayers; ++i) pLayer[i] = apvts.getRawParameterValue ("layer" + juce::String (i + 1));
    for (int i = 0; i < 3; ++i) pFollow[i] = apvts.getRawParameterValue ("follow" + juce::String (i + 1));
    pPad = apvts.getRawParameterValue ("padPattern");
    pBass = apvts.getRawParameterValue ("bassPattern");
    pArp = apvts.getRawParameterValue ("arpFigure");
    pRate = apvts.getRawParameterValue ("arpRate");
}

bool StromscoreProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    const auto out = layouts.getMainOutputChannelSet();
    return out == juce::AudioChannelSet::stereo() || out == juce::AudioChannelSet::mono();
}

void StromscoreProcessor::prepareToPlay (double sampleRate, int)
{
    currentRate = sampleRate;
    flushPending = true;
    generator.reset();
    preview.prepare (sampleRate);
}

void StromscoreProcessor::reset()
{
    flushPending = true;   // klingende Noten beim naechsten Block beenden (die Engine vergisst sie hier)
    generator.reset();
    preview.reset();
}

stromscore::Settings StromscoreProcessor::currentSettings() const
{
    stromscore::Settings s;
    s.key = juce::roundToInt (pKey->load());
    s.x = pAxis[0]->load(); s.y = pAxis[1]->load(); s.z = pAxis[2]->load();
    static constexpr int nums[] = { 0, 4, 3, 6, 5, 7, 5, 12 };
    static constexpr int dens[] = { 0, 4, 4, 8, 4, 8, 8, 8 };
    const int m = juce::jlimit (0, 7, juce::roundToInt (pMeter->load()));
    s.meterNum = m == 0 ? hostNum : nums[m];
    s.meterDen = m == 0 ? hostDen : dens[m];
    s.swing = pSwing->load();
    s.variation = juce::roundToInt (pVariation->load());
    for (int i = 0; i < stromscore::kNumLayers; ++i) s.layerMode[i] = juce::jlimit (0, 2, juce::roundToInt (pLayer[i]->load()));
    for (int i = 0; i < 3; ++i) s.follow[i] = pFollow[i]->load() >= 0.5f;
    s.padPattern = juce::roundToInt (pPad->load());
    s.bassPattern = juce::roundToInt (pBass->load());
    s.arpFigure = juce::roundToInt (pArp->load());
    s.arpRate = juce::roundToInt (pRate->load());
    return s;
}

// Controller am MIDI-Eingang (z. B. Nuances-Fader) bewegen Faerbung, Intensitaet und Unruhe
void StromscoreProcessor::handleControllers (const juce::MidiBuffer& incoming)
{
    float last[3] = { -1.0f, -1.0f, -1.0f };
    for (const auto meta : incoming)
    {
        const auto msg = meta.getMessage();
        if (! msg.isController()) continue;
        for (int a = 0; a < 3; ++a)
        {
            const int cc = ccNumber[a].load();
            if (cc > 0 && msg.getControllerNumber() == cc)
                last[a] = (float) msg.getControllerValue() / 127.0f;
        }
    }
    for (int a = 0; a < 3; ++a)
        if (last[a] >= 0.0f && axisParam[a] != nullptr && std::abs (axisParam[a]->getValue() - last[a]) > 1.0e-4f)
            axisParam[a]->setValueNotifyingHost (last[a]);
}

// Beendet alles, was noch klingt, und schickt zur Sicherheit "Alle Noten aus" (CC 123) auf den fuenf Kanaelen
void StromscoreProcessor::flushSounding (juce::MidiBuffer& midi, bool forceAllNotesOff)
{
    for (int layer = 0; layer < stromscore::kNumLayers; ++layer)
    {
        bool any = forceAllNotesOff;
        for (int note = 0; note < 128; ++note)
            if (sounding[layer].test ((size_t) note))
            {
                midi.addEvent (juce::MidiMessage::noteOff (layer + 1, note), 0);
                any = true;
            }
        sounding[layer].reset();
        if (any) midi.addEvent (juce::MidiMessage::allNotesOff (layer + 1), 0);
    }
}

void StromscoreProcessor::emit (const stromscore::EventList& list, juce::MidiBuffer& midi, juce::AudioBuffer<float>& audio, bool withPreview)
{
    const int n = audio.getNumSamples();
    withPreview = withPreview && audio.getNumChannels() > 1;   // Vorhoeren nur in Stereo
    float* l = audio.getWritePointer (0);
    float* r = audio.getNumChannels() > 1 ? audio.getWritePointer (1) : nullptr;
    int rendered = 0;
    for (int i = 0; i < list.size; ++i)
    {
        const auto& e = list.events[(size_t) i];
        if (e.velocity > 0)
        {
            midi.addEvent (juce::MidiMessage::noteOn (e.channel, e.note, (juce::uint8) e.velocity), e.offset);
            sounding[e.channel - 1].set ((size_t) e.note);
            activity[e.channel - 1].store (1.0f);
        }
        else
        {
            midi.addEvent (juce::MidiMessage::noteOff (e.channel, e.note), e.offset);
            sounding[e.channel - 1].reset ((size_t) e.note);
        }

        if (withPreview)
        {
            const int upTo = juce::jlimit (rendered, n, e.offset);
            if (upTo > rendered) preview.render (l + rendered, r + rendered, upTo - rendered);
            rendered = upTo;
            preview.handle (e);
        }
    }
    if (withPreview && rendered < n)
        preview.render (l + rendered, r + rendered, n - rendered);
}

void StromscoreProcessor::processBlock (juce::AudioBuffer<float>& audio, juce::MidiBuffer& midi)
{
    juce::ScopedNoDenormals noDenormals;
    audio.clear();
    handleControllers (midi);
    midi.clear();   // eingehende Noten werden nicht weitergereicht

    stromscore::Transport t;
    t.sampleRate = currentRate > 0.0 ? currentRate : 48000.0;
    if (auto* head = getPlayHead())
        if (auto pos = head->getPosition())
        {
            t.playing = pos->getIsPlaying();
            if (auto ppq = pos->getPpqPosition()) t.ppq = *ppq; else t.playing = false;
            if (auto bpm = pos->getBpm()) t.bpm = *bpm;
            if (auto sig = pos->getTimeSignature()) { hostNum = sig->numerator; hostDen = sig->denominator; }
        }
    hostPlaying.store (t.playing);

    events.clear();
    if (wasBypassed) { generator.reset(); wasBypassed = false; }
    if (flushPending) { flushSounding (midi, false); preview.reset(); flushPending = false; }
    const auto settings = currentSettings();
    meterNum.store (settings.meterNum); meterDen.store (settings.meterDen);
    generator.process (t, settings, audio.getNumSamples(), events);
    wendung.store (t.playing ? generator.wendung() : -1);
    chordIndex.store (t.playing ? generator.chordInWendung() : -1);
    chordRoot.store (generator.chordRoot());
    chordType.store (generator.chordType());

    const bool withPreview = pPreview->load() >= 0.5f;
    if (! withPreview) preview.reset();
    emit (events, midi, audio, withPreview);

    // Stopp: was noch klingt (z. B. weil der Host zwischendurch zurueckgesetzt hat) sicher beenden
    if (! t.playing)
        flushSounding (midi, wasPlaying);
    wasPlaying = t.playing;
}

void StromscoreProcessor::processBlockBypassed (juce::AudioBuffer<float>& audio, juce::MidiBuffer& midi)
{
    audio.clear();
    midi.clear();
    if (! wasBypassed)
    {
        generator.reset();
        flushSounding (midi, true);
        preview.reset();
        wasPlaying = false;
        wasBypassed = true;
    }
}

void StromscoreProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    state.setProperty ("theme", uiTheme.load(), nullptr);
    state.setProperty ("uiW", uiWidth.load(), nullptr);
    state.setProperty ("ccFaerbung", ccNumber[0].load(), nullptr);
    state.setProperty ("ccIntensitaet", ccNumber[1].load(), nullptr);
    state.setProperty ("ccUnruhe", ccNumber[2].load(), nullptr);
    if (auto xml = state.createXml())
        copyXmlToBinary (*xml, destData);
}

void StromscoreProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (auto xml = getXmlFromBinary (data, sizeInBytes))
    {
        auto state = juce::ValueTree::fromXml (*xml);
        if (state.isValid() && state.hasType (apvts.state.getType()))
        {
            uiTheme.store ((int) state.getProperty ("theme", 0) == 1 ? 1 : 0);
            uiWidth.store (juce::jlimit (kUiWidth / 2, kUiWidth * 3, (int) state.getProperty ("uiW", kUiWidth)));
            ccNumber[0].store (juce::jlimit (0, 127, (int) state.getProperty ("ccFaerbung", 11)));
            ccNumber[1].store (juce::jlimit (0, 127, (int) state.getProperty ("ccIntensitaet", 1)));
            ccNumber[2].store (juce::jlimit (0, 127, (int) state.getProperty ("ccUnruhe", 74)));
            apvts.replaceState (state);
        }
    }
}

juce::AudioProcessorEditor* StromscoreProcessor::createEditor() { return new StromscoreEditor (*this); }

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new StromscoreProcessor(); }
