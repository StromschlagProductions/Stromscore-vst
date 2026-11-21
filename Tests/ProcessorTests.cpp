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

struct Counts { int ons = 0, offs = 0, ccs = 0; std::map<int, int> channels; std::map<std::pair<int, int>, int> open; bool broken = false; };

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
        else if (m.isController()) { if (m.getControllerNumber() == 1 || m.getControllerNumber() == 11) ++c.ccs; }
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

    // Bei geringem Verlauf: nur Flaeche und Bass (gehalten, also die Kanaele fuer lang); bei vollem: alle Ebenen.
    // Vorgabe der Kanaele: Flaeche 1 und 2, Bass 3 und 4, Arp 5, Tupfer 6, Stich 7, Gegenstimme 8. Jede Note endet, nichts doppelt.
    setParam (*p, "intensitaet", 0.0f);
    {
        auto c = play (*p, host, 8, 512);
        CHECK (c.ons > 0 && c.ons == c.offs && ! c.broken);
        CHECK (c.channels.count (1) && c.channels.count (3));
        for (int ch = 5; ch <= 8; ++ch) CHECK (! c.channels.count (ch));
    }
    setParam (*p, "intensitaet", 1.0f);
    for (int block : { 64, 441, 512, 1024 })
    {
        auto c = play (*p, host, 8, block);
        CHECK (c.ons > 0 && c.ons == c.offs && ! c.broken);
        for (int ch : { 5, 6, 7, 8 }) CHECK (c.channels.count (ch) == 1);
        CHECK (c.channels.count (1) + c.channels.count (2) >= 1 && c.channels.count (3) + c.channels.count (4) >= 1);
        for (const auto& kv : c.channels) CHECK (kv.first >= 1 && kv.first <= 8);
    }

    // Freie Kanalwahl: alles auf Kanal 1 (ein einziges Instrument), Legato als Parameter
    {
        for (int i = 1; i <= 8; ++i) CHECK (p->apvts.getParameter ("kanal" + juce::String (i)) != nullptr);
        CHECK (p->apvts.getParameter ("legato") != nullptr && p->currentSettings().legato);
        CHECK (p->currentSettings().channel[7] == 8 && p->currentSettings().channel[0] == 1);
        for (int i = 1; i <= 8; ++i) setParam (*p, ("kanal" + juce::String (i)).toRawUTF8(), 0.0f);
        CHECK (p->currentSettings().channel[5] == 1);
        auto c = play (*p, host, 8, 441);
        CHECK (c.ons > 0 && c.ons == c.offs && ! c.broken && c.channels.size() == 1 && c.channels.count (1) == 1);
        const auto file = p->renderMidiFile (8);
        juce::MidiFile mf; juce::FileInputStream in (file);
        CHECK (in.openedOk() && mf.readFrom (in) && mf.getNumTracks() == 2);   // Takt-Spur und eine Spur fuer Kanal 1
        for (int i = 1; i <= 8; ++i) setParam (*p, ("kanal" + juce::String (i)).toRawUTF8(), (float) (i - 1));
        CHECK (p->currentSettings().channel[3] == 4);
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

    // Vorhoeren bei stehender DAW: eigene Uhr, hoerbar, aber keine Noten am MIDI-Ausgang
    {
        host.playing = false;
        p->prepareToPlay (48000, 512);
        auto runStopped = [&] (float on)
        {
            setParam (*p, "preview", on);
            juce::AudioBuffer<float> audio (2, 512); juce::MidiBuffer midi; double e = 0; int noteOns = 0;
            for (int i = 0; i < 200; ++i)
            {
                audio.clear(); midi.clear();
                { NoAllocations guard; p->processBlock (audio, midi); }
                for (const auto meta : midi) if (meta.getMessage().isNoteOn()) ++noteOns;
                for (int s = 0; s < 512; ++s) { const float x = audio.getSample (0, s); CHECK (std::isfinite (x) && std::abs (x) <= 1.0f); e += (double) x * x; }
            }
            CHECK (noteOns == 0);
            return e;
        };
        CHECK (runStopped (1.0f) > 1e-4);
        CHECK (p->wendung.load() >= 0);           // Anzeige laeuft mit
        CHECK (runStopped (0.0f) == 0.0);
        // DAW startet waehrend des Vorhoerens: ihr Takt uebernimmt, MIDI geht wieder raus
        setParam (*p, "preview", 1.0f);
        { juce::AudioBuffer<float> a (2, 512); juce::MidiBuffer m; p->processBlock (a, m); }
        setParam (*p, "intensitaet", 0.6f);
        auto c = play (*p, host, 4, 512);
        CHECK (c.ons > 0 && c.ons == c.offs && ! c.broken);
        setParam (*p, "preview", 0.0f);
        host.playing = true;
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

    // Solo, Mute, Intensitaet je Ebene und "folgt den Akkorden" als Parameter
    {
        for (int i = 1; i <= 5; ++i)
            for (auto* id : { "mute", "solo", "intensitaet" }) CHECK (p->apvts.getParameter (id + juce::String (i)) != nullptr);
        for (int i = 1; i <= 3; ++i) CHECK (p->apvts.getParameter ("follow" + juce::String (i)) != nullptr);
        CHECK (p->apvts.getParameter ("abwechslung") != nullptr);
        CHECK (p->apvts.getParameter ("durchgaenge") != nullptr);
        CHECK (StromscoreProcessor::layerNames()[4] == "Gegenstimme");
        setParam (*p, "solo3", 1.0f); setParam (*p, "intensitaet3", 0.5f);
        setParam (*p, "intensitaet", 0.0f);
        auto c = play (*p, host, 8, 512);
        CHECK (c.channels.size() == 1 && c.channels.count (5) == 1);   // nur der Arp, trotz ruhiger Stimmung
        setParam (*p, "solo3", 0.0f); setParam (*p, "intensitaet3", 0.0f); setParam (*p, "mute2", 1.0f);
        setParam (*p, "intensitaet", 1.0f);
        c = play (*p, host, 8, 512);
        CHECK (c.channels.count (3) == 0 && c.channels.count (4) == 0 && c.channels.count (5) == 1 && c.ons == c.offs);
        setParam (*p, "mute2", 0.0f);
        // Text des Intensitaets-Reglers
        auto* li = p->apvts.getParameter ("intensitaet2");
        CHECK (li->getText (li->convertTo0to1 (0.2f), 32) == "+20 %");
        CHECK (std::abs (li->convertFrom0to1 (li->getValueForText ("-30 %")) + 0.3f) < 1e-4f);
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

    // Auswahllisten passen zu den Mustern der Engine
    CHECK (StromscoreProcessor::padPatternNames().size() == stromscore::kNumPadPatterns);
    CHECK (StromscoreProcessor::bassPatternNames().size() == stromscore::kNumBassPatterns);
    CHECK (StromscoreProcessor::arpFigureNames().size() == stromscore::kNumArpFigures);
    CHECK (StromscoreProcessor::arpRateNames().size() == stromscore::kNumArpRates);
    CHECK (StromscoreProcessor::changeNames().size() == stromscore::kNumChangeGrids);
    CHECK (StromscoreProcessor::slotTypeNames().size() == stromscore::kNumCustomTypes);
    CHECK (! StromscoreProcessor::bassPatternNames().contains ("Oktaven"));

    // Wechsel, Oktaven und eigene Folge als Parameter; Vorgabe F - C - B - G je 2 Takte
    {
        CHECK (p->apvts.getParameter ("wechsel") != nullptr && p->apvts.getParameter ("eigeneFolge") != nullptr);
        for (int i = 1; i <= 5; ++i) CHECK ((int) p->apvts.getRawParameterValue ("oct" + juce::String (i))->load() == 2);
        auto st = p->currentSettings();
        CHECK (! st.custom && st.change == stromscore::ChangeBeat);
        CHECK (st.customChords[0].rootAbs == 5 && st.customChords[1].rootAbs == 0 && st.customChords[2].rootAbs == 10 && st.customChords[3].rootAbs == 7);
        for (int i = 0; i < 4; ++i) CHECK (st.customChords[i].bars == 2 && st.customChords[i].type == stromscore::Maj);
        for (int i = 4; i < 8; ++i) CHECK (st.customChords[i].bars == 0);
        setParam (*p, "oct2", 3.0f); setParam (*p, "slotType2", 1.0f); setParam (*p, "eigeneFolge", 1.0f); setParam (*p, "wechsel", 1.0f);
        st = p->currentSettings();
        CHECK (st.custom && st.change == stromscore::ChangeBar && st.octave[1] == 1 && st.customChords[1].type == stromscore::Min);

        // eigene Folge spielt und alles endet sauber
        setParam (*p, "intensitaet", 0.6f);
        auto c = play (*p, host, 8, 512);
        CHECK (c.ons > 0 && c.ons == c.offs && ! c.broken);
        CHECK (p->wendung.load() == stromscore::kCustomWendung || ! host.playing);

        juce::MemoryBlock state; p->getStateInformation (state);
        auto q = std::make_unique<StromscoreProcessor>();
        q->setStateInformation (state.getData(), (int) state.getSize());
        for (auto* id : { "eigeneFolge", "wechsel", "oct2", "slotType2", "slotRoot3", "slotBars4" })
            CHECK (q->apvts.getRawParameterValue (id)->load() == p->apvts.getRawParameterValue (id)->load());
        setParam (*p, "oct2", 2.0f); setParam (*p, "slotType2", 0.0f); setParam (*p, "eigeneFolge", 0.0f); setParam (*p, "wechsel", 0.0f);
    }

    // 80er Pop-Rock, Dynamik per CC und MIDI-Datei zum Herausziehen
    {
        CHECK (p->apvts.getParameter ("genre") != nullptr && p->apvts.getParameter ("dynamikCc") != nullptr);
        setParam (*p, "intensitaet", 0.6f);
        auto c = play (*p, host, 8, 512);
        CHECK (c.ccs == 0);                                   // Vorgabe: keine Dynamik-Controller
        setParam (*p, "dynamikCc", 1.0f);
        c = play (*p, host, 8, 512);
        CHECK (c.ccs > 10 && c.ons == c.offs && ! c.broken);
        setParam (*p, "genre", 1.0f);
        c = play (*p, host, 8, 512);
        CHECK (c.ons > 0 && c.ons == c.offs && ! c.broken);
        CHECK (StromscoreProcessor::bassPatternNames().contains ("Hi-NRG") && StromscoreProcessor::arpFigureNames().contains ("SID"));

        const auto file = p->renderMidiFile (8);
        CHECK (file.existsAsFile());
        juce::MidiFile mf;
        juce::FileInputStream in (file);
        CHECK (in.openedOk() && mf.readFrom (in));
        CHECK (mf.getNumTracks() == 9);   // Takt-Spur und eine Spur je Kanal (Vorgabe: acht)
        int notes = 0, ccs = 0; double last = 0.0;
        for (int t = 1; t < mf.getNumTracks(); ++t)
        {
            const auto* seq = mf.getTrack (t);
            int open = 0;
            for (int i = 0; i < seq->getNumEvents(); ++i)
            {
                const auto& m = seq->getEventPointer (i)->message;
                if (m.isNoteOn()) { ++notes; ++open; CHECK (m.getChannel() == t); }
                if (m.isNoteOff()) --open;
                if (m.isController()) ++ccs;
                last = std::max (last, m.getTimeStamp());
            }
            CHECK (open == 0);
        }
        CHECK (notes > 20 && ccs > 0);
        const auto st = p->currentSettings();
        const auto meter = stromscore::Meter::from (st.meterNum, st.meterDen);
        CHECK (last <= 8.0 * meter.len * stromscore::kStep * 960.0 + 1.0);   // genau 8 Takte im aktuellen Takt
        CHECK (last >= 7.0 * meter.len * stromscore::kStep * 960.0);
        setParam (*p, "genre", 0.0f); setParam (*p, "dynamikCc", 0.0f);
    }

    // Tonumfang: Parameter, Notennamen, Vorlagen, Anlernen per MIDI-Eingang und die herausgezogene Datei
    {
        CHECK (StromscoreProcessor::noteName (60) == "C3" && StromscoreProcessor::noteName (0) == "C-2" && StromscoreProcessor::noteName (71) == "H3");
        CHECK (StromscoreProcessor::rangeTemplates().size() >= 15);
        for (const auto& t : StromscoreProcessor::rangeTemplates()) CHECK (t.lo >= 0 && t.hi <= 127 && t.hi - t.lo >= 12);
        CHECK (p->apvts.getParameter ("tief1")->getCurrentValueAsText() == "C-2");
        setParam (*p, "umfang3", 1.0f); setParam (*p, "tief3", 60.0f); setParam (*p, "hoch3", 96.0f);
        setParam (*p, "umfang2", 1.0f); setParam (*p, "tief2", 36.0f); setParam (*p, "hoch2", 50.0f);
        setParam (*p, "intensitaet", 0.8f);
        auto st = p->currentSettings();
        CHECK (st.rangeOn[2] && st.rangeLo[2] == 60 && st.rangeHi[2] == 96 && ! st.rangeOn[0]);
        const auto c = play (*p, host, 8, 512);
        CHECK (c.ons > 0 && c.ons == c.offs && ! c.broken);

        const auto file = p->renderMidiFile (8);
        juce::MidiFile mf; juce::FileInputStream in (file);
        CHECK (in.openedOk() && mf.readFrom (in));
        int arpNotes = 0;
        for (int t = 1; t < mf.getNumTracks(); ++t)
            for (int i = 0; i < mf.getTrack (t)->getNumEvents(); ++i)
            {
                const auto& m = mf.getTrack (t)->getEventPointer (i)->message;
                if (! m.isNoteOn()) continue;
                if (m.getChannel() == 5) { CHECK (m.getNoteNumber() >= 60 && m.getNoteNumber() <= 96); ++arpNotes; }
                if (m.getChannel() == 3 || m.getChannel() == 4) CHECK (m.getNoteNumber() >= 36 && m.getNoteNumber() <= 50);
            }
        CHECK (arpNotes > 10 && mf.getNumTracks() == 9);   // Takt-Spur und acht Kanaele

        // Anlernen: zwei Tasten am Eingang, in beliebiger Reihenfolge; eingehende Noten gehen nicht hinaus
        p->learnFirst.store (-1); p->learnSecond.store (-1); p->learnLayer.store (4);
        juce::AudioBuffer<float> audio (2, 256); juce::MidiBuffer midi;
        host.playing = false;
        midi.addEvent (juce::MidiMessage::noteOn (1, 84, (juce::uint8) 100), 0);
        p->processBlock (audio, midi);
        for (const auto meta : midi) CHECK (! meta.getMessage().isNoteOn());
        midi.clear(); midi.addEvent (juce::MidiMessage::noteOn (1, 84, (juce::uint8) 100), 0);
        midi.addEvent (juce::MidiMessage::noteOn (1, 48, (juce::uint8) 100), 10);
        p->processBlock (audio, midi);
        CHECK (p->learnFirst.load() == 84 && p->learnSecond.load() == 48);
        p->learnLayer.store (-1);
        for (const char* id : { "umfang2", "umfang3" }) setParam (*p, id, 0.0f);
        setParam (*p, "tief2", 0.0f); setParam (*p, "hoch2", 127.0f); setParam (*p, "tief3", 0.0f); setParam (*p, "hoch3", 127.0f);
        setParam (*p, "intensitaet", 0.1f);
    }

    // Szene (ab 1.3): Vorgaben, Einstieg ab Wiedergabebeginn, Laenge und Ende, Zustand wird gespeichert
    {
        for (auto* id : { "aufbau", "einstieg", "wurf", "aufbauTakte", "haerte", "szenenLaenge", "ende", "motiv", "fahrt", "fahrtX", "fahrtY", "fahrtStart", "fahrtTakte", "fahrtKurve" })
            CHECK (p->apvts.getParameter (id) != nullptr);
        auto st = p->currentSettings();
        CHECK (st.scene && st.entry == stromscore::EntryAuto && st.motif && st.inertia && ! st.drive && st.sceneBars == 0 && st.buildBars == 8);

        // Bass-Schlag: im ersten Takt spielt nur der Bass, nach dem Aufbau alle Ebenen
        setParam (*p, "intensitaet", 1.0f);
        setParam (*p, "einstieg", (float) stromscore::EntryBass);
        setParam (*p, "takt", 1.0f);   // 4/4 fest (weiter oben wurden andere Taktarten probiert)
        p->prepareToPlay (48000, 512);
        juce::AudioBuffer<float> audio (2, 512); juce::MidiBuffer midi;
        host.ppq = 16.0; host.playing = true;   // Wiedergabe startet in Takt 5: dort beginnt die Szene
        std::map<int, int> firstBar, later;
        for (int i = 0; i < 94 * 19; ++i)       // gut 9 Takte zu 2 Sekunden (94 Bloecke je Sekunde)
        {
            audio.clear(); midi.clear();
            p->processBlock (audio, midi);
            for (const auto meta : midi) if (meta.getMessage().isNoteOn()) ++(host.ppq < 20.0 ? firstBar : later)[meta.getMessage().getChannel()];
            host.ppq += 512.0 / 24000.0;
        }
        CHECK (p->sceneBar.load() >= 8 && p->sceneEntry.load() == stromscore::EntryBass);
        CHECK (! firstBar.empty());
        for (const auto& kv : firstBar) CHECK (kv.first == 3 || kv.first == 4);
        for (int ch : { 5, 8 }) CHECK (later.count (ch) == 1);
        host.playing = false; audio.clear(); midi.clear(); p->processBlock (audio, midi);
        CHECK (p->sceneBar.load() == -1);

        // Laenge 8 Takte, hartes Ende: in der herausgezogenen Datei nach dem Schlusspunkt kein Ton mehr
        setParam (*p, "szenenLaenge", 1.0f);
        setParam (*p, "ende", (float) stromscore::EndHard);
        {
            const auto file = p->renderMidiFile (16);
            juce::MidiFile mf; juce::FileInputStream in (file);
            CHECK (in.openedOk() && mf.readFrom (in));
            int ons = 0, late = 0;
            for (int t = 1; t < mf.getNumTracks(); ++t)
                for (const auto* ev : *mf.getTrack (t))
                    if (ev->message.isNoteOn()) { ++ons; if (ev->message.getTimeStamp() > 8 * 4 * 960 + 1) ++late; }
            CHECK (ons > 20 && late == 0);
        }

        // Wurf, Fahrt und Ziel werden mit dem Projekt gespeichert
        setParam (*p, "wurf", 42.0f); setParam (*p, "fahrt", 1.0f); setParam (*p, "fahrtX", 0.3f);
        juce::MemoryBlock state;
        p->getStateInformation (state);
        StromscoreProcessor q;
        q.setStateInformation (state.getData(), (int) state.getSize());
        const auto qs = q.currentSettings();
        CHECK (qs.seed == 42 && qs.drive && std::abs (qs.driveX - 0.3f) < 1e-3f && qs.sceneBars == 8 && qs.ending == stromscore::EndHard && qs.entry == stromscore::EntryBass);
        for (auto [id, v] : { std::pair<const char*, float> { "wurf", 0.0f }, { "fahrt", 0.0f }, { "fahrtX", 0.8f }, { "szenenLaenge", 0.0f }, { "ende", 1.0f }, { "einstieg", 0.0f } })
            setParam (*p, id, v);
        setParam (*p, "intensitaet", 0.1f);
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
