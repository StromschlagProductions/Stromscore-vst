#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace
{
juce::String u8 (const char* s) { return juce::String (juce::CharPointer_UTF8 (s)); }
}

juce::StringArray StromscoreProcessor::keyNames()
{
    return { "C", "Cis / Des", "D", "Dis / Es", "E", "F", "Fis / Ges", "G", "Gis / As", "A", "Ais / B", "H" };
}

juce::StringArray StromscoreProcessor::modeNames()
{
    return { "Moll", "Dur", "Dorisch", "Phrygisch", "Lydisch" };
}

juce::AudioProcessorValueTreeState::ParameterLayout StromscoreProcessor::createLayout()
{
    using namespace juce;
    AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "key", 1 }, "Tonart", keyNames(), 9));
    layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "mode", 1 }, "Modus", modeNames(), 0));
    layout.add (std::make_unique<AudioParameterFloat> (ParameterID { "verlauf", 1 }, "Verlauf",
        NormalisableRange<float> (0.0f, 1.0f), 0.3f,
        AudioParameterFloatAttributes().withStringFromValueFunction ([] (float v, int) { return String (roundToInt (v * 100.0f)) + " %"; })
                                       .withValueFromStringFunction ([] (const String& t) { return jlimit (0.0f, 1.0f, t.getFloatValue() / 100.0f); })));
    layout.add (std::make_unique<AudioParameterInt> (ParameterID { "variation", 1 }, "Variation", 1, 16, 1));
    layout.add (std::make_unique<AudioParameterBool> (ParameterID { "preview", 1 }, u8 ("Vorhören"), false));
    return layout;
}

StromscoreProcessor::StromscoreProcessor()
    : AudioProcessor (BusesProperties().withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      apvts (*this, nullptr, "STROMSCORE", createLayout())
{
    pKey = apvts.getRawParameterValue ("key");
    pMode = apvts.getRawParameterValue ("mode");
    pVerlauf = apvts.getRawParameterValue ("verlauf");
    pVariation = apvts.getRawParameterValue ("variation");
    pPreview = apvts.getRawParameterValue ("preview");
}

bool StromscoreProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    const auto out = layouts.getMainOutputChannelSet();
    return out == juce::AudioChannelSet::stereo() || out == juce::AudioChannelSet::mono();
}

void StromscoreProcessor::prepareToPlay (double sampleRate, int)
{
    generator.reset();
    preview.prepare (sampleRate);
}

void StromscoreProcessor::reset()
{
    generator.reset();
    preview.reset();
}

stromscore::Settings StromscoreProcessor::currentSettings() const
{
    stromscore::Settings s;
    s.key = juce::roundToInt (pKey->load());
    s.mode = juce::roundToInt (pMode->load());
    s.verlauf = pVerlauf->load();
    s.variation = juce::roundToInt (pVariation->load());
    return s;
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
            activity[e.channel - 1].store (1.0f);
        }
        else
            midi.addEvent (juce::MidiMessage::noteOff (e.channel, e.note), e.offset);

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
    midi.clear();   // eingehende Noten werden in 0.1 nicht verwendet

    stromscore::Transport t;
    t.sampleRate = getSampleRate();
    if (auto* head = getPlayHead())
        if (auto pos = head->getPosition())
        {
            t.playing = pos->getIsPlaying();
            if (auto ppq = pos->getPpqPosition()) t.ppq = *ppq; else t.playing = false;
            if (auto bpm = pos->getBpm()) t.bpm = *bpm;
        }
    hostPlaying.store (t.playing);

    events.clear();
    if (wasBypassed) { generator.reset(); wasBypassed = false; }
    generator.process (t, currentSettings(), audio.getNumSamples(), events);
    chordIndex.store (generator.chordIndex());

    const bool withPreview = pPreview->load() >= 0.5f;
    if (! withPreview) preview.reset();
    emit (events, midi, audio, withPreview);
}

void StromscoreProcessor::processBlockBypassed (juce::AudioBuffer<float>& audio, juce::MidiBuffer& midi)
{
    audio.clear();
    midi.clear();
    if (! wasBypassed)
    {
        events.clear();
        generator.allNotesOff (events, 0);
        for (int i = 0; i < events.size; ++i)
            midi.addEvent (juce::MidiMessage::noteOff (events.events[(size_t) i].channel, events.events[(size_t) i].note), 0);
        preview.reset();
        wasBypassed = true;
    }
}

void StromscoreProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    state.setProperty ("theme", uiTheme.load(), nullptr);
    state.setProperty ("uiW", uiWidth.load(), nullptr);
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
            apvts.replaceState (state);
        }
    }
}

juce::AudioProcessorEditor* StromscoreProcessor::createEditor() { return new StromscoreEditor (*this); }

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new StromscoreProcessor(); }
