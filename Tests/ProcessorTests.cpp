#include "PluginProcessor.h"
#include "TestSupport.h"
#include <map>
#include <memory>

namespace
{
struct FakeHost final : juce::AudioPlayHead
{
    bool playing = true;
    double ppq = 0.0, bpm = 120.0;
    juce::Optional<PositionInfo> getPosition() const override
    {
        PositionInfo info;
        info.setIsPlaying (playing);
        info.setPpqPosition (ppq);
        info.setBpm (bpm);
        return info;
    }
};

struct Counts { int ons = 0, offs = 0; std::map<int, int> channels; std::map<std::pair<int, int>, int> open; bool broken = false; };

void collect (const juce::MidiBuffer& midi, Counts& c)
{
    for (const auto meta : midi)
    {
        const auto m = meta.getMessage();
        const int ch = m.getChannel();
        if (m.isNoteOn())
        {
            ++c.ons; ++c.channels[ch];
            if (++c.open[std::make_pair (ch, m.getNoteNumber())] > 1) c.broken = true;   // doppelter Anschlag ohne Ende
        }
        else if (m.isNoteOff())
        {
            ++c.offs;
            if (--c.open[std::make_pair (ch, m.getNoteNumber())] < 0) c.broken = true;   // Ende ohne Anschlag
        }
    }
}

void setParam (StromscoreProcessor& p, const char* id, float value)
{
    auto* prm = p.apvts.getParameter (id);
    CHECK (prm != nullptr);
    prm->setValueNotifyingHost (prm->convertTo0to1 (value));
}

// spielt 'bars' Takte (4/4) in Bloecken ab ppq 0 und sammelt das MIDI
Counts play (StromscoreProcessor& p, FakeHost& host, int bars, int blockSize)
{
    Counts c;
    p.prepareToPlay (48000, blockSize);
    juce::AudioBuffer<float> audio (2, blockSize);
    juce::MidiBuffer midi;
    host.ppq = 0.0; host.playing = true;
    const double samplesPerQuarter = 48000.0 * 60.0 / host.bpm;
    const int blocks = (int) (bars * 4 * samplesPerQuarter / blockSize);
    for (int i = 0; i < blocks; ++i)
    {
        audio.clear(); midi.clear();
        { NoAllocations guard; p.processBlock (audio, midi); }
        collect (midi, c);
        host.ppq += blockSize / samplesPerQuarter;
    }
    host.playing = false;   // Stopp: alle offenen Noten muessen enden
    audio.clear(); midi.clear();
    p.processBlock (audio, midi);
    collect (midi, c);
    return c;
}
}

int main()
{
    juce::ScopedJuceInitialiser_GUI init;
    auto p = std::make_unique<StromscoreProcessor>();
    FakeHost host;
    p->setPlayHead (&host);

    // Ausgang: Stereo und Mono sind erlaubt, Surround nicht
    auto layout = p->getBusesLayout();
    layout.outputBuses.set (0, juce::AudioChannelSet::mono());
    CHECK (p->setBusesLayout (layout));
    layout.outputBuses.set (0, juce::AudioChannelSet::create5point1());
    CHECK (! p->setBusesLayout (layout));
    layout.outputBuses.set (0, juce::AudioChannelSet::stereo());
    CHECK (p->setBusesLayout (layout));
    CHECK (p->acceptsMidi() && p->producesMidi());

    // Parameter-IDs
    for (auto* id : { "key", "faerbung", "intensitaet", "unruhe", "takt", "swing", "variation", "preview", "padPattern", "bassPattern", "arpFigure", "arpRate" })
        CHECK (p->apvts.getParameter (id) != nullptr);

    // Bei geringem Verlauf: nur Flaeche und Bass; bei vollem: alle fuenf Kanaele. Jede Note endet, nichts doppelt.
    setParam (*p, "intensitaet", 0.0f);
    {
        auto c = play (*p, host, 8, 512);
        CHECK (c.ons > 0 && c.ons == c.offs && ! c.broken);
        CHECK (c.channels.count (1) && c.channels.count (2));
        CHECK (! c.channels.count (3) && ! c.channels.count (4) && ! c.channels.count (5));
    }
    setParam (*p, "intensitaet", 1.0f);
    for (int block : { 64, 441, 512, 1024 })
    {
        auto c = play (*p, host, 8, block);
        CHECK (c.ons > 0 && c.ons == c.offs && ! c.broken);
        for (int ch = 1; ch <= 5; ++ch) CHECK (c.channels.count (ch) == 1);
        CHECK (c.channels.size() == 5);
    }

    // Gleiche Einstellungen, andere Blockgroesse: gleiche Anzahl Noten
    {
        auto a = play (*p, host, 8, 64), b = play (*p, host, 8, 1024);
        CHECK (a.ons == b.ons);
    }

    // Ohne Wiedergabe keine Noten
    {
        host.playing = false;
        p->prepareToPlay (48000, 512);
        juce::AudioBuffer<float> audio (2, 512); juce::MidiBuffer midi; Counts c;
        for (int i = 0; i < 50; ++i) { audio.clear(); midi.clear(); p->processBlock (audio, midi); collect (midi, c); }
        CHECK (c.ons == 0);
        host.playing = true;
    }

    // Vorhoeren: ohne Schalter Stille im Audio, mit Schalter hoerbar
    {
        auto energy = [&] (float on)
        {
            setParam (*p, "preview", on);
            p->prepareToPlay (48000, 512);
            host.ppq = 0.0; host.playing = true;
            juce::AudioBuffer<float> audio (2, 512); juce::MidiBuffer midi; double e = 0;
            for (int i = 0; i < 200; ++i)
            {
                audio.clear(); midi.clear();
                { NoAllocations guard; p->processBlock (audio, midi); }
                for (int ch = 0; ch < 2; ++ch)
                    for (int s = 0; s < 512; ++s) { const float x = audio.getSample (ch, s); CHECK (std::isfinite (x) && std::abs (x) <= 1.0f); e += (double) x * x; }
                host.ppq += 512.0 / (48000.0 * 60.0 / host.bpm);
            }
            return e;
        };
        CHECK (energy (0.0f) == 0.0);
        CHECK (energy (1.0f) > 1e-4);
        setParam (*p, "preview", 0.0f);
    }

    // Bypass beendet offene Noten genau einmal
    {
        {   // Reste des vorigen Tests (Wiedergabe lief weiter) zuerst sauber beenden
            host.playing = false;
            juce::AudioBuffer<float> a (2, 512); juce::MidiBuffer m;
            p->processBlock (a, m);
        }
        p->prepareToPlay (48000, 512);
        host.ppq = 0.0; host.playing = true;
        juce::AudioBuffer<float> audio (2, 512); juce::MidiBuffer midi; Counts c;
        for (int i = 0; i < 20; ++i) { audio.clear(); midi.clear(); p->processBlock (audio, midi); collect (midi, c); host.ppq += 0.1; }
        midi.clear(); p->processBlockBypassed (audio, midi); collect (midi, c);
        CHECK (c.ons == c.offs && ! c.broken);
        midi.clear(); p->processBlockBypassed (audio, midi);
        CHECK (midi.getNumEvents() == 0);
    }

    // Hängende Töne: Reset des Hosts mitten im Spiel, dann Stopp: alles muss enden (auch ohne Engine-Wissen)
    {
        setParam (*p, "intensitaet", 1.0f);
        p->prepareToPlay (48000, 512);
        host.ppq = 0.0; host.playing = true;
        juce::AudioBuffer<float> audio (2, 512); juce::MidiBuffer midi; Counts c;
        for (int i = 0; i < 30; ++i) { audio.clear(); midi.clear(); p->processBlock (audio, midi); collect (midi, c); host.ppq += 512.0 / 24000.0; }
        p->reset();                                  // wie ein Host, der beim Stopp zurücksetzt
        host.playing = false;
        audio.clear(); midi.clear(); p->processBlock (audio, midi); collect (midi, c);
        CHECK (c.ons == c.offs && ! c.broken);
        bool cc123 = false;
        for (const auto meta : midi) if (meta.getMessage().isAllNotesOff()) cc123 = true;
        (void) cc123;
        host.playing = true;
    }

    // Ebenen-Schalter und "folgt den Akkorden" als Parameter
    {
        for (int i = 1; i <= 5; ++i) CHECK (p->apvts.getParameter ("layer" + juce::String (i)) != nullptr);
        for (int i = 1; i <= 3; ++i) CHECK (p->apvts.getParameter ("follow" + juce::String (i)) != nullptr);
        setParam (*p, "layer1", 0.0f); setParam (*p, "layer2", 0.0f); setParam (*p, "layer3", 2.0f);
        setParam (*p, "intensitaet", 0.0f);
        auto c = play (*p, host, 8, 512);
        CHECK (c.channels.size() == 1 && c.channels.count (3) == 1);   // nur der Arp
        setParam (*p, "layer1", 1.0f); setParam (*p, "layer2", 1.0f); setParam (*p, "layer3", 1.0f);
        setParam (*p, "intensitaet", 1.0f);
    }

    // Zustand speichern und laden
    {
        setParam (*p, "key", 3.0f); setParam (*p, "faerbung", 0.8f); setParam (*p, "intensitaet", 0.62f); setParam (*p, "variation", 7.0f);
        setParam (*p, "takt", 4.0f); setParam (*p, "bassPattern", 7.0f);
        p->uiTheme.store (1); p->uiWidth.store (1000); p->ccNumber[1].store (2);
        juce::MemoryBlock state; p->getStateInformation (state);
        auto q = std::make_unique<StromscoreProcessor>();
        q->setStateInformation (state.getData(), (int) state.getSize());
        CHECK (q->uiTheme.load() == 1 && q->uiWidth.load() == 1000 && q->ccNumber[1].load() == 2 && q->ccNumber[0].load() == 11);
        for (auto* id : { "key", "faerbung", "intensitaet", "unruhe", "takt", "variation", "preview", "bassPattern" })
            CHECK (q->apvts.getRawParameterValue (id)->load() == p->apvts.getRawParameterValue (id)->load());
        const char junk[] = "not a state";
        q->setStateInformation (junk, (int) sizeof (junk));
        CHECK ((int) q->apvts.getRawParameterValue ("takt")->load() == 4);
    }

    // Controller am Eingang bewegen das Stimmungsfeld (Vorgabe CC 11, 1, 74)
    {
        p->ccNumber[1].store (1);
        p->prepareToPlay (48000, 512);
        juce::AudioBuffer<float> audio (2, 512); juce::MidiBuffer midi;
        midi.addEvent (juce::MidiMessage::controllerEvent (1, 11, 127), 0);
        midi.addEvent (juce::MidiMessage::controllerEvent (1, 1, 0), 10);
        midi.addEvent (juce::MidiMessage::controllerEvent (1, 74, 64), 20);
        p->processBlock (audio, midi);
        CHECK (std::abs (p->apvts.getRawParameterValue ("faerbung")->load() - 1.0f) < 1e-3f);
        CHECK (std::abs (p->apvts.getRawParameterValue ("intensitaet")->load() - 0.0f) < 1e-3f);
        CHECK (std::abs (p->apvts.getRawParameterValue ("unruhe")->load() - 64.0f / 127.0f) < 1e-3f);
        for (const auto meta : midi) CHECK (! meta.getMessage().isController() || meta.getMessage().isAllNotesOff());   // Eingang wird nicht weitergereicht
        p->ccNumber[0].store (0);   // aus
        midi.clear(); midi.addEvent (juce::MidiMessage::controllerEvent (1, 11, 0), 0);
        p->processBlock (audio, midi);
        CHECK (std::abs (p->apvts.getRawParameterValue ("faerbung")->load() - 1.0f) < 1e-3f);
        p->ccNumber[0].store (11);
        setParam (*p, "faerbung", 0.3f); setParam (*p, "unruhe", 0.0f);
    }

    // Texte: Prozent
    {
        auto* v = p->apvts.getParameter ("intensitaet");
        CHECK (std::abs (v->convertFrom0to1 (v->getValueForText ("70 %")) - 0.7f) < 1e-5f);
    }

    // Die Oberflaeche laesst sich anlegen und wieder abbauen (beide Looks)
    for (int theme = 0; theme < 2; ++theme)
    {
        p->uiTheme.store (theme);
        std::unique_ptr<juce::AudioProcessorEditor> editor (p->createEditor());
        CHECK (editor != nullptr);
        editor->setSize (StromscoreProcessor::kUiWidth, StromscoreProcessor::kUiHeight);
    }

    p->setPlayHead (nullptr);
    return 0;
}
