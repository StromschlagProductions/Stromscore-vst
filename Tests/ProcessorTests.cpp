#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "TestSupport.h"
#include <map>
#include <set>
#include <memory>
#include <thread>
#include <tuple>
#include <vector>

namespace
{
struct FakeHost final : juce::AudioPlayHead
{
    bool playing = true;
    double ppq = 0.0, bpm = 120.0;
    int numerator=0,denominator=8;
    juce::Optional<PositionInfo> getPosition() const override
    {
        PositionInfo info;
        info.setIsPlaying (playing);
        info.setPpqPosition (ppq);
        info.setBpm (bpm);
        if(numerator>0)info.setTimeSignature(juce::AudioPlayHead::TimeSignature{numerator,denominator});
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

// Run explicitly against an isolated synthetic all-protected catalog build.
static int testProtectedCatalogExport()
{
    using namespace stromscore;
    for(const auto& h:harmonyTemplates)CHECK(h.coloration==ChordColoration::protectedColor);
    int cases=0;
    for(int genre=0;genre<2;++genre)for(int profile=0;profile<4;++profile)
    for(float unrest:{.1f,.6f,.95f})for(bool follow:{false,true})
    {
        StromscoreProcessor q;FakeHost host;q.setPlayHead(&host);q.prepareToPlay(48000,512);
        setParam(q,"genre",static_cast<float>(genre));setParam(q,"komponist",static_cast<float>(profile));
        setParam(q,"faerbung",.65f);setParam(q,"intensitaet",.8f);setParam(q,"unruhe",unrest);setParam(q,"durchgaenge",1);
        for(int i=1;i<=3;++i)setParam(q,("follow"+std::to_string(i)).c_str(),follow?1.f:0.f);
        using Timed=std::tuple<long long,int,int,int,int>;
        std::vector<Timed> live,exported;
        auto add=[](std::vector<Timed>& target,const juce::MidiMessage& m,long long tick)
        {if(m.isNoteOnOrOff())target.emplace_back(tick,m.isNoteOn()?1:0,m.getChannel(),m.getNoteNumber(),m.isNoteOn()?m.getVelocity():0);
         else if(m.isController()&&!m.isAllNotesOff())target.emplace_back(tick,2,m.getChannel(),m.getControllerNumber(),m.getControllerValue());};
        auto file=q.renderMidiFile(8);auto stream=file.createInputStream();juce::MidiFile midi;CHECK(stream&&midi.readFrom(*stream));
        for(int tr=0;tr<midi.getNumTracks();++tr)for(int i=0;i<midi.getTrack(tr)->getNumEvents();++i)
        {const auto& m=midi.getTrack(tr)->getEventPointer(i)->message;add(exported,m,std::llround(m.getTimeStamp()));}
        juce::AudioBuffer<float> audio(2,512);juce::MidiBuffer messages;messages.ensureSize(65536);Counts ledger;
        for(int at=0;at<8*96000;at+=512)
        {
            host.ppq=at/24000.;messages.clear();{NoCHeap cHeap;NoAllocations cppHeap;q.processBlock(audio,messages);}
            collect(messages,ledger);for(auto m:messages)add(live,m.getMessage(),std::llround((at+m.samplePosition)/25.));
        }
        host.playing=false;messages.clear();q.processBlock(audio,messages);collect(messages,ledger);
        for(auto m:messages)add(live,m.getMessage(),8*3840);
        std::sort(live.begin(),live.end());std::sort(exported.begin(),exported.end());
        CHECK(!live.empty()&&live==exported);CHECK(!ledger.broken&&ledger.ons==ledger.offs);
        file.deleteFile();++cases;
    }
    std::cout<<"Protected actual processor live/export: "<<cases<<" cases passed\n";return 0;
}

// Real 39-entry plugin path: the exact new anchors select each imported template.
static void testImportedCatalogExport(bool extended=false,int meter=0)
{
    using namespace stromscore;int cases=0;
    for(unsigned id:extended?std::vector<unsigned>{2001,2002,2003,2004,2005,2006,2007,2008,2009}:std::vector<unsigned>{2037,2038,2039})for(int key:{0,5,11})for(bool follow:{false,true})for(int profile=0;profile<3;++profile)
    {
        const auto* h=findHarmonyTemplate(static_cast<WendungId>(id));CHECK(h);
        if(extended)CHECK(h->chords[0].type==18+static_cast<int>(id)-2001);
        StromscoreProcessor q;FakeHost host;q.setPlayHead(&host);q.prepareToPlay(48000,512);
        if(meter){host.numerator=meter;host.playing=false;juce::AudioBuffer<float> prime(2,512);juce::MidiBuffer midi;q.processBlock(prime,midi);host.playing=true;}
        setParam(q,"genre",1);setParam(q,"komponist",static_cast<float>(profile));setParam(q,"key",static_cast<float>(key));
        setParam(q,"faerbung",h->x);setParam(q,"intensitaet",h->y);setParam(q,"unruhe",h->z);setParam(q,"abwechslung",0);
        setParam(q,"durchgaenge",1);for(int i=1;i<=3;++i)setParam(q,("follow"+std::to_string(i)).c_str(),follow?1.f:0.f);
        using Timed=std::tuple<long long,int,int,int,int>;std::vector<Timed> live,exported;
        auto add=[](std::vector<Timed>& target,const juce::MidiMessage& m,long long tick)
        {if(m.isNoteOnOrOff())target.emplace_back(tick,m.isNoteOn()?1:0,m.getChannel(),m.getNoteNumber(),m.isNoteOn()?m.getVelocity():0);
         else if(m.isController()&&!m.isAllNotesOff())target.emplace_back(tick,2,m.getChannel(),m.getControllerNumber(),m.getControllerValue());};
        auto file=q.renderMidiFile(8);auto stream=file.createInputStream();juce::MidiFile midi;CHECK(stream&&midi.readFrom(*stream));
        for(int tr=0;tr<midi.getNumTracks();++tr)for(int i=0;i<midi.getTrack(tr)->getNumEvents();++i)
        {const auto& m=midi.getTrack(tr)->getEventPointer(i)->message;add(exported,m,std::llround(m.getTimeStamp()));}
        juce::AudioBuffer<float> audio(2,512);juce::MidiBuffer messages;messages.ensureSize(65536);Counts ledger;
        const int total=8*(meter?12000*meter:96000);
        for(int at=0;at<total;at+=512)
        {
            audio.setSize(2,std::min(512,total-at));host.ppq=at/24000.;messages.clear();{NoCHeap cHeap;NoAllocations cppHeap;q.processBlock(audio,messages);}collect(messages,ledger);
            CHECK(q.wendung.load()==wendungIndex(GenrePopRock,static_cast<WendungId>(id)));
            for(auto m:messages)add(live,m.getMessage(),std::llround((at+m.samplePosition)/25.));
        }
        host.playing=false;messages.clear();q.processBlock(audio,messages);collect(messages,ledger);for(auto m:messages)add(live,m.getMessage(),total/25);
        std::sort(live.begin(),live.end());std::sort(exported.begin(),exported.end());CHECK(!live.empty()&&live==exported);CHECK(!ledger.broken&&ledger.ons==ledger.offs);
        file.deleteFile();++cases;
    }
    std::cout<<"Imported catalog real processor live/export: "<<cases<<" cases passed\n";
}

#include "ProfileSwitchProcessorTests.h"

// P3: actual processor/SMF path, including both melodic channels and their real note ledger.
static int testWilliamsMotifsExport()
{
 using namespace stromscore;int cases=0;
 for(unsigned id:{40002u,40014u})for(int key:{0,11})for(float swing:{0.f,.3f}){
  const auto* h=findHarmonyTemplate(static_cast<WendungId>(id));CHECK(h);
  StromscoreProcessor q;FakeHost host;q.setPlayHead(&host);q.prepareToPlay(48000,512);
  setParam(q,"komponist",3);setParam(q,"genre",0);setParam(q,"key",static_cast<float>(key));setParam(q,"aufbau",0);
  setParam(q,"faerbung",h->x);setParam(q,"intensitaet",h->y);setParam(q,"unruhe",h->z);setParam(q,"abwechslung",0);
  setParam(q,"durchgaenge",1);setParam(q,"melodie",1);setParam(q,"motiv",1);setParam(q,"melodieMotiv",1);setParam(q,"swing",swing);
  using Timed=std::tuple<long long,int,int,int,int>;std::vector<Timed> live,exported;
  auto add=[](std::vector<Timed>& target,const juce::MidiMessage& m,long long tick){
   if(m.isNoteOnOrOff())target.emplace_back(tick,m.isNoteOn()?1:0,m.getChannel(),m.getNoteNumber(),m.isNoteOn()?m.getVelocity():0);
   else if(m.isController()&&!m.isAllNotesOff())target.emplace_back(tick,2,m.getChannel(),m.getControllerNumber(),m.getControllerValue());};
  auto file=q.renderMidiFile(64);auto stream=file.createInputStream();juce::MidiFile midi;CHECK(stream&&midi.readFrom(*stream));
  for(int tr=0;tr<midi.getNumTracks();++tr)for(int i=0;i<midi.getTrack(tr)->getNumEvents();++i){const auto& m=midi.getTrack(tr)->getEventPointer(i)->message;add(exported,m,std::llround(m.getTimeStamp()));}
  juce::AudioBuffer<float> audio(2,512);juce::MidiBuffer messages;messages.ensureSize(65536);Counts ledger;
  const int total=64*96000;
  for(int at=0;at<total;at+=512){audio.setSize(2,std::min(512,total-at));host.ppq=at/24000.;messages.clear();
   {NoCHeap c;NoAllocations n;q.processBlock(audio,messages);}collect(messages,ledger);
   for(auto m:messages)add(live,m.getMessage(),std::llround((at+m.samplePosition)/25.));}
  host.playing=false;messages.clear();q.processBlock(audio,messages);collect(messages,ledger);for(auto m:messages)add(live,m.getMessage(),total/25);
  std::sort(live.begin(),live.end());std::sort(exported.begin(),exported.end());CHECK(live==exported&&!live.empty());CHECK(!ledger.broken&&ledger.ons==ledger.offs);
  int melodic=0;for(auto e:live)if(std::get<1>(e)==1&&(std::get<2>(e)==q.currentSettings().channel[OutMelody]||std::get<2>(e)==q.currentSettings().channel[OutCounter]))++melodic;CHECK(melodic>10);
  file.deleteFile();++cases;
 }
 std::cout<<"Williams P3 real processor live/export: "<<cases<<" cases, no hanging notes or process allocations\n";return 0;
}

int main(int argc,char** argv)
{
    juce::ScopedJuceInitialiser_GUI init;
    if(argc==2&&std::string(argv[1])=="--williams-motifs")return testWilliamsMotifsExport();
    if(argc==2&&std::string(argv[1])=="--profile-switch")return testProfileSwitchProcessor();
    if(argc==2&&std::string(argv[1])=="--protected-catalog")return testProtectedCatalogExport();
    if(argc==2&&std::string(argv[1])=="--extended-chords"){testImportedCatalogExport(true);return 0;}
    testImportedCatalogExport();
    for(int numerator:{3,5,7})testImportedCatalogExport(false,numerator);
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
        p->serviceDrive(); // publish MIDI-controlled axes on the message thread
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
        CHECK (StromscoreProcessor::noteName (60) == "C3" && StromscoreProcessor::noteName (0) == "C-2" && StromscoreProcessor::noteName (71) == "B3");
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
        setParam (*p, "szenenLaenge", 8.0f);
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

    // Stich-Ton und Durchleiten (ab 1.4)
    {
        auto st = p->currentSettings();
        CHECK (st.stichFixed && st.stichNote == 36);                           // Vorgabe: fest auf C1
        setParam (*p, "stichModus", 1.0f); setParam (*p, "stichTon", 40.0f);
        st = p->currentSettings();
        CHECK (! st.stichFixed && st.stichNote == 40);
        setParam (*p, "stichModus", 0.0f); setParam (*p, "stichTon", 36.0f);
        CHECK (p->channelMaskForRange (5) == (1 << 6));                         // Stich: Kanal 7
        CHECK (p->channelMaskForRange (0) == ((1 << 0) | (1 << 1)));            // Flaeche: Kanaele 1 und 2

        FakeHost stopped; stopped.playing = false;
        p->setPlayHead (&stopped);
        p->prepareToPlay (48000, 512);
        juce::AudioBuffer<float> audio (2, 512);
        auto block = [&] (juce::MidiBuffer& m) { p->processBlock (audio, m); };
        auto onsOn = [] (const juce::MidiBuffer& m, int ch, int note, bool on)
        {
            int n = 0;
            for (const auto meta : m)
            {
                const auto x = meta.getMessage();
                if (x.getChannel() == ch && x.isNoteOnOrOff() && x.getNoteNumber() == note && x.isNoteOn() == on) ++n;
            }
            return n;
        };
        // ohne offenes Fenster: nichts wird durchgereicht
        juce::MidiBuffer m; m.addEvent (juce::MidiMessage::noteOn (1, 50, (juce::uint8) 90), 10);
        block (m);
        CHECK (onsOn (m, 7, 50, true) == 0 && onsOn (m, 1, 50, true) == 0);
        // Fenster offen: die Taste geht auf den Kanal des Stichs, auch bei stehender DAW, und klingt weiter
        p->thruMask.store (1 << 6);
        m.clear(); m.addEvent (juce::MidiMessage::noteOn (1, 50, (juce::uint8) 90), 10);
        block (m);
        CHECK (onsOn (m, 7, 50, true) == 1);
        m.clear(); block (m);
        CHECK (onsOn (m, 7, 50, false) == 0);
        // Fenster zu: der gehaltene Ton endet
        p->thruMask.store (0);
        m.clear(); block (m);
        CHECK (onsOn (m, 7, 50, false) == 1);
        // Vorhoeren: ein Ton auf dem Kanal, nach etwa 0,4 Sekunden wieder aus
        p->audition (36, 1 << 6);
        m.clear(); block (m);
        CHECK (onsOn (m, 7, 36, true) == 1);
        int offs = 0;
        for (int i = 0; i < 60; ++i) { m.clear(); block (m); offs += onsOn (m, 7, 36, false); }
        CHECK (offs == 1);
        // Anlernen des Stich-Tons
        p->learnToneNote.store (-1); p->learnTone.store (true);
        m.clear(); m.addEvent (juce::MidiMessage::noteOn (1, 43, (juce::uint8) 90), 0);
        block (m);
        CHECK (p->learnToneNote.load() == 43);
        p->learnTone.store (false);
        p->setPlayHead (&host);
    }

    // Fahrt: bei der Ankunft wird B zu A und die Fahrt schaltet sich aus; bei Abbruch unterwegs die aktuelle Position
    {
        juce::AudioBuffer<float> audio (2, 512); juce::MidiBuffer midi;
        auto param = [&] (const char* id) { return p->apvts.getRawParameterValue (id)->load(); };
        for (int pass = 0; pass < 2; ++pass)
        {
            setParam (*p, "faerbung", 0.2f); setParam (*p, "intensitaet", 0.2f);
            setParam (*p, "fahrtX", 0.8f); setParam (*p, "fahrtY", 0.9f);
            setParam (*p, "fahrtTakte", 4.0f);   // 4 Takte
            setParam (*p, "fahrtStart", 1.0f);
            setParam (*p, "fahrt", 1.0f);
            p->reset();
            host.playing = true; host.ppq = 0.0;
            const int blocks = pass == 0 ? 8 * 188 : 2 * 188 + 100;   // 188 Bloecke = ein Takt bei 120 bpm
            for (int i = 0; i < blocks; ++i)
            {
                audio.clear(); midi.clear(); p->processBlock (audio, midi);
                host.ppq += 512.0 / 24000.0;
                p->serviceDrive();
            }
            if (pass == 0)
            {
                CHECK (param ("fahrt") < 0.5f);                          // angekommen: Fahrt aus
                CHECK (std::abs (param ("faerbung") - 0.8f) < 0.02f);    // B ist zum neuen A geworden
                CHECK (std::abs (param ("intensitaet") - 0.9f) < 0.02f);
            }
            else
            {
                setParam (*p, "fahrt", 0.0f);                           // unterwegs abgebrochen
                CHECK (param ("faerbung") > 0.3f && param ("faerbung") < 0.75f);
                CHECK (param ("intensitaet") > 0.3f && param ("intensitaet") < 0.85f);
            }
        }
        setParam (*p, "intensitaet", 0.0f);
    }

    // Rechtsklick im Stimmungsfeld setzt nur das Ziel B (die Fahrt startet nicht); Linksklick bewegt A
    {
        setParam (*p, "fahrt", 0.0f);
        setParam (*p, "faerbung", 0.3f); setParam (*p, "intensitaet", 0.3f);
        std::unique_ptr<juce::AudioProcessorEditor> editor (p->createEditor());
        editor->setSize (StromscoreProcessor::kUiWidth, StromscoreProcessor::kUiHeight);
        MoodPad* pad = nullptr;
        std::function<void (juce::Component&)> find = [&] (juce::Component& c)
        {
            if (auto* m = dynamic_cast<MoodPad*> (&c)) pad = m;
            for (auto* ch : c.getChildren()) find (*ch);
        };
        find (*editor);
        CHECK (pad != nullptr);
        if (pad != nullptr)
        {
            auto press = [&] (bool right, int clicks = 1, float x = 0.8f)
            {
                const auto mods = right ? juce::ModifierKeys (juce::ModifierKeys::rightButtonModifier) : juce::ModifierKeys (juce::ModifierKeys::leftButtonModifier);
                const juce::MouseEvent e (juce::Desktop::getInstance().getMainMouseSource(), juce::Point<float> (pad->getWidth() * x, pad->getHeight() * 0.2f), mods,
                                          1.0f, 0.0f, 0.0f, 0.0f, 0.0f, pad, pad, juce::Time::getCurrentTime(), juce::Point<float> (pad->getWidth() * x, pad->getHeight() * 0.2f), juce::Time::getCurrentTime(), clicks, false);
                pad->mouseDown (e);
                pad->mouseUp (e);
            };
            press (true);
            CHECK (pad->targetPending);
            CHECK (std::abs (p->apvts.getRawParameterValue ("faerbung")->load() - 0.3f) < 1e-3f);   // A bleibt stehen
            CHECK (p->apvts.getRawParameterValue ("fahrtX")->load() > 0.6f);                         // B ist gesetzt
            CHECK (p->apvts.getRawParameterValue ("fahrt")->load() < 0.5f);                          // keine Fahrt
            const auto original = p->currentSettings();
            // A real right-double-click consists of two downs/ups; the first must not lose old B.
            press (true, 1, 0.15f); press (true, 2, 0.15f);
            CHECK (! p->targetSet.load() && ! pad->targetPending && ! pad->showB);
            CHECK (std::abs (p->currentSettings().driveX - original.driveX) < 1e-6f);
            CHECK (std::abs (p->currentSettings().driveY - original.driveY) < 1e-6f);
            CHECK (std::abs (p->currentSettings().x - original.x) < 1e-6f);
            juce::MemoryBlock hiddenState; p->getStateInformation (hiddenState);
            // Processors contain large fixed MIDI buffers: keep the extra restore instance off Windows' small main stack.
            auto hidden = std::make_unique<StromscoreProcessor>();
            hidden->setStateInformation (hiddenState.getData(), (int) hiddenState.getSize());
            CHECK (! hidden->targetSet.load());
            CHECK (std::abs (hidden->currentSettings().driveX - original.driveX) < 1e-6f);
            setParam (*p, "fahrt", 1); CHECK (p->targetSet.load());
            press (true, 1, 0.25f); press (true, 2, 0.25f);
            CHECK (p->targetSet.load() && p->currentSettings().drive); // no hiding during a drive
            setParam (*p, "fahrt", 0);
            press (true, 1, 0.4f); press (true, 2, 0.4f); CHECK (! p->targetSet.load());
            press (true); CHECK (p->targetSet.load() && pad->targetPending);
            pad->showB = true; // left must still select A even when B is closer
            setParam (*p, "fahrt", 1);
            press (false);
            CHECK (p->apvts.getRawParameterValue ("fahrt")->load() < 0.5f);
            CHECK (p->targetSet.load());
            CHECK (p->apvts.getRawParameterValue ("faerbung")->load() > 0.6f);                       // Linksklick: A springt
        }
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

    // 1.9: MIDI controller positions are independent of host block size.
    {
        using Message = std::tuple<long long, int, int, int>;
        auto render = [] (int block)
        {
            StromscoreProcessor q; FakeHost h; q.setPlayHead (&h); q.prepareToPlay (48000, block);
            setParam (q, "aufbau", 0); setParam (q, "intensitaet", 0.1f);
            juce::AudioBuffer<float> a (2, block); juce::MidiBuffer m; m.ensureSize (65536);
            std::vector<Message> messages;
            const int total = 48000;
            for (int at = 0; at < total; at += block)
            {
                const int n = std::min (block, total - at); a.setSize (2, n, false, false, true); m.clear();
                if (at <= 6400 && at + n > 6400) m.addEvent (juce::MidiMessage::controllerEvent (1, 1, 127), 6400 - at);
                h.ppq = at / 24000.0; q.processBlock (a, m);
                for (const auto meta : m)
                {
                    const auto msg = meta.getMessage();
                    if (msg.isNoteOnOrOff()) messages.emplace_back (at + meta.samplePosition, msg.getChannel(), msg.getNoteNumber(), msg.isNoteOn() ? msg.getVelocity() : 0);
                }
            }
            q.setPlayHead (nullptr); return messages;
        };
        CHECK (render (64) == render (512)); CHECK (render (512) == render (8192));
    }
    // GUI timer latency must not replace the stopped drive position by old A.
    {
        StromscoreProcessor q; FakeHost h; q.setPlayHead (&h); q.prepareToPlay (48000, 512);
        setParam (q, "faerbung", 0.2f); setParam (q, "intensitaet", 0.2f);
        setParam (q, "fahrtX", 0.8f); setParam (q, "fahrtY", 0.8f); setParam (q, "fahrt", 1);
        juce::AudioBuffer<float> a (2, 512); juce::MidiBuffer m; m.ensureSize (65536);
        for (int i = 0; i < 187; ++i) { h.ppq = i * 512 / 24000.0; m.clear(); q.processBlock (a, m); }
        const float x = q.pointX.load();
        std::thread automation ([&] { setParam (q, "fahrt", 0); }); automation.join();
        h.ppq = 187 * 512 / 24000.0; m.clear(); q.processBlock (a, m); q.serviceDrive();
        CHECK (std::abs (q.currentSettings().x - x) < 1.0e-6f); q.setPlayHead (nullptr);
    }
    // Audition lasts exactly 0.4 seconds, including its first block, for small and large blocks.
    for (int block : { 512, 8192, 32768 })
    {
        StromscoreProcessor q; FakeHost h; h.playing = false; q.setPlayHead (&h); q.prepareToPlay (48000, block);
        juce::AudioBuffer<float> a (2, block); juce::MidiBuffer m; m.ensureSize (65536); q.audition (60, 1);
        int ended = -1;
        for (int at = 0; at < 48000; at += block)
        { m.clear(); q.processBlock (a, m); for (const auto meta : m) if (meta.getMessage().isNoteOff() && meta.getMessage().getNoteNumber() == 60) ended = at + meta.samplePosition; }
        CHECK (ended == 19200); q.setPlayHead (nullptr);
    }
    // New range parameters survive state roundtrip; note names roundtrip through host text entry.
    {
        StromscoreProcessor q, restored; setParam (q, "cc0Lo1", 100); setParam (q, "cc0Hi1", 127); setParam (q, "cc1Lo8", 70);
        juce::MemoryBlock state; q.getStateInformation (state); restored.setStateInformation (state.getData(), (int) state.getSize());
        CHECK (restored.currentSettings().ccLo[0][0] == 100); CHECK (restored.currentSettings().ccLo[1][7] == 70);
        auto* parameter = q.apvts.getParameter ("tief1");
        for (int note = 0; note < 128; ++note) CHECK (juce::roundToInt (parameter->convertFrom0to1 (parameter->getValueForText (StromscoreProcessor::noteName (note)))) == note);
        CHECK (juce::roundToInt (parameter->convertFrom0to1 (parameter->getValueForText ("Db3"))) == 61);
        CHECK (juce::roundToInt (parameter->convertFrom0to1 (parameter->getValueForText ("B3"))) == 71);
    }
    // The hard scene ending is present in the file with positive duration at the selected endpoint.
    {
        StromscoreProcessor q; setParam (q, "szenenLaenge", 8); setParam (q, "ende", 0);
        auto file = q.renderMidiFile (8); auto stream = file.createInputStream(); juce::MidiFile midiFile;
        CHECK (stream != nullptr && midiFile.readFrom (*stream)); int ons = 0, offs = 0;
        for (int track = 0; track < midiFile.getNumTracks(); ++track)
        { const auto* seq = midiFile.getTrack (track); for (int e = 0; e < seq->getNumEvents(); ++e)
          { const auto& msg = seq->getEventPointer (e)->message; if (msg.isNoteOn() && msg.getTimeStamp() == 30720.0) ++ons; if (msg.isNoteOff() && msg.getTimeStamp() > 30720.0) ++offs; } }
        CHECK (ons > 0 && offs >= ons);
    }
    // Large offline host blocks do not overflow or lose note-offs.
    {
        StromscoreProcessor q; FakeHost h; h.bpm = 300; q.setPlayHead (&h); q.prepareToPlay (8000, 65536);
        setParam (q, "aufbau", 0); setParam (q, "intensitaet", 1); setParam (q, "unruhe", 1);
        setParam (q, "dynamikCc", 1); setParam (q, "padPattern", stromscore::PadGated); setParam (q, "bassPattern", stromscore::BassPulse);
        juce::AudioBuffer<float> a (2, 65536); juce::MidiBuffer m; m.ensureSize (1000000); Counts counts;
        q.processBlock (a, m); collect (m, counts); h.playing = false; m.clear(); q.processBlock (a, m); collect (m, counts);
        std::cout << "Large block: " << counts.ons << " on, " << counts.offs << " off, broken=" << counts.broken << std::endl;
        CHECK (! counts.broken && counts.ons > 500 && counts.ons == counts.offs); q.setPlayHead (nullptr);
    }

    // C allocator tracking catches JUCE MidiBuffer malloc/realloc too, beyond operator new.
    {
        StromscoreProcessor q; FakeHost h; h.playing = false; q.setPlayHead (&h); q.prepareToPlay (48000, 512);
        q.thruMask.store (0xffff); juce::AudioBuffer<float> a (2, 512); juce::MidiBuffer m; m.ensureSize (65536);
        for (int pass = 0; pass < 8; ++pass)
        {
            m.clear();
            for (int note = 48; note < 72; ++note)
                m.addEvent (pass % 2 == 0 ? juce::MidiMessage::noteOn (1, note, (juce::uint8) 100) : juce::MidiMessage::noteOff (1, note), note);
            if (pass == 2) q.audition (84, 1);
            m.addEvent (juce::MidiMessage::controllerEvent (1, 11, pass * 16), 400);
            { NoCHeap heap; NoAllocations cppHeap; q.processBlock (a, m); }
        }
        q.setPlayHead (nullptr);
    }
    // Bypass stops keyboard/audition on channel 16 even when generators use only channels 1-8.
    {
        StromscoreProcessor q; FakeHost h; h.playing = false; q.setPlayHead (&h); q.prepareToPlay (48000, 512);
        juce::AudioBuffer<float> a (2, 512); juce::MidiBuffer m; m.ensureSize (65536); Counts c;
        q.thruMask.store (1 << 15); q.audition (84, 1 << 15);
        m.addEvent (juce::MidiMessage::noteOn (1, 60, (juce::uint8) 100), 0); q.processBlock (a, m); collect (m, c);
        CHECK (c.ons == 2); m.clear(); q.processBlockBypassed (a, m); collect (m, c);
        CHECK (! c.broken && c.ons == c.offs); q.setPlayHead (nullptr);
    }
    // Voice-leading export equals live DAW playback, including channel CCs and held common notes.
    for(float intensity : {.4f,.7f,.8f,.9f,1.f,.99f,.97f,.96f,.95f,.94f,.93f,.92f,.91f,.89f,.88f,.87f,.86f,.85f,.84f,.83f,.82f,.81f,.79f,.78f,.77f,.76f,.75f,.74f,.73f,.72f})
    {
        StromscoreProcessor q; FakeHost h; q.setPlayHead (&h); q.prepareToPlay (48000, 512);
        if(intensity==.89f||intensity==.88f||intensity==.87f||intensity==.86f||intensity==.85f||intensity==.84f||intensity==.83f)setParam(q,"genre",1);
        setParam (q, "aufbau", 0); setParam (q, "key", 0); setParam (q, "intensitaet", intensity);
        setParam(q,"durchgaenge",intensity>=.6f?1.f:0.f);
        setParam (q, "eigeneFolge", 1); setParam (q, "padPattern", stromscore::PadHeld); setParam (q, "dynamikCc", 1);
        setParam (q, "cc0Lo1", 100); setParam (q, "cc0Hi1", 127);
        const int roots[4] = { 0, 9, 2, 7 }, types[4] = { 2, 3, 15, 4 };
        for (int i = 0; i < 4; ++i)
        {
            setParam (q, ("slotRoot" + std::to_string (i + 1)).c_str(), (float) roots[i]);
            setParam (q, ("slotType" + std::to_string (i + 1)).c_str(), (float) types[i]);
        }
        if(intensity==.88f)setParam(q,"eigeneFolge",0);
        // Nonuniform harmonic durations must agree between live MIDI and file export.
        const int durations[4]={1,3,2,2};
        for(int i=0;i<4;++i)setParam(q,("slotBars"+std::to_string(i+1)).c_str(),static_cast<float>(durations[i]));
        for (int i = 2; i <= 5; ++i) setParam (q, ("mute" + std::to_string (i)).c_str(), 1);
        if(intensity==.8f||intensity==.9f)
        {setParam(q,"komponist",intensity==.8f?1.f:2.f);setParam(q,"eigeneFolge",0);}
        const bool recurrence=intensity>.75f;
        if(recurrence){setParam(q,"mute1",1);setParam(q,"mute5",0);setParam(q,"motiv",1);}
        if(intensity>.85f){setParam(q,"mute3",0);setParam(q,"arpFigure",stromscore::ArpCell);}
        if(intensity>.95f){setParam(q,"melodie",1);setParam(q,"mute6",0);}
        if(intensity>.98f&&intensity<1.f){setParam(q,"melodieMotiv",0);setParam(q,"melodieLegato",0);}
        // Exercise auto-arpeggio reservations for dialog and foreground melody, too.
        if(intensity==.95f||intensity==.96f){setParam(q,"mute3",0);setParam(q,"arpFigure",stromscore::ArpAuto);}
        if(intensity==.87f)
        {setParam(q,"eigeneFolge",0);setParam(q,"faerbung",.70f);setParam(q,"intensitaet",.71f);setParam(q,"unruhe",.26f);setParam(q,"abwechslung",0);setParam(q,"durchgaenge",0);setParam(q,"arpFigure",stromscore::ArpAuto);}
        if(intensity==.86f)
        {setParam(q,"eigeneFolge",0);setParam(q,"faerbung",.88f);setParam(q,"intensitaet",.48f);setParam(q,"unruhe",.03f);setParam(q,"abwechslung",0);setParam(q,"durchgaenge",0);setParam(q,"arpFigure",stromscore::ArpAuto);}
        // Automatic Pop/Rock bass phrases: actual plugin live/export path.
        if(intensity==.85f)
        {
            setParam(q,"eigeneFolge",0);setParam(q,"faerbung",.48f);setParam(q,"intensitaet",.62f);
            setParam(q,"unruhe",.2f);setParam(q,"abwechslung",0);setParam(q,"durchgaenge",0);
            setParam(q,"bassPattern",stromscore::BassAuto);setParam(q,"mute2",0);setParam(q,"mute5",1);
        }
        // Real auto bass/arp interlock, including a shifted onset and its export timing.
        if(intensity==.84f)
        {
            setParam(q,"eigeneFolge",0);setParam(q,"faerbung",.88f);setParam(q,"intensitaet",.48f);
            setParam(q,"unruhe",.03f);setParam(q,"abwechslung",0);setParam(q,"durchgaenge",0);
            setParam(q,"bassPattern",stromscore::BassAuto);setParam(q,"arpFigure",stromscore::ArpAuto);
            setParam(q,"arpRate",stromscore::RateAuto);setParam(q,"mute2",0);setParam(q,"mute3",0);setParam(q,"mute5",1);
            for(int v=1;v<=16;++v)if((stromscore::hash3(v,0,31)&1)==1&&(stromscore::hash3(v,0,47)&1)==0)
                {setParam(q,"variation",static_cast<float>(v));break;}
        }
        // Automatic held pad disposition; lean Maj7 retains E/B with a stable C bass.
        if(intensity==.83f)
        {
            setParam(q,"faerbung",.52f);setParam(q,"intensitaet",.38f);setParam(q,"unruhe",.12f);
            setParam(q,"abwechslung",0);setParam(q,"durchgaenge",0);setParam(q,"padPattern",stromscore::PadAuto);
            setParam(q,"bassPattern",stromscore::BassHeld);setParam(q,"arpFigure",stromscore::ArpAuto);
            setParam(q,"mute1",0);setParam(q,"mute2",0);setParam(q,"mute3",0);setParam(q,"mute5",1);
            const int chordRoots[]={0,5,0,7},chordTypes[]={stromscore::Maj7,stromscore::Min9,stromscore::Sus4,stromscore::Add9};
            for(int i=0;i<4;++i)
            {
                setParam(q,("slotRoot"+std::to_string(i+1)).c_str(),static_cast<float>(chordRoots[i]));
                setParam(q,("slotType"+std::to_string(i+1)).c_str(),static_cast<float>(chordTypes[i]));
                setParam(q,("slotBars"+std::to_string(i+1)).c_str(),2);
            }
        }
        const bool handoff=intensity>.96f&&intensity<.98f;
        if(handoff)
        {
            setParam(q,"arpFigure",stromscore::ArpAuto);
            setParam(q,"wurf",3);setParam(q,"durchgaenge",0);
            for(int i=1;i<=stromscore::kMaxChords;++i)
            {setParam(q,("slotRoot"+std::to_string(i)).c_str(),0);setParam(q,("slotType"+std::to_string(i)).c_str(),2);
                setParam(q,("slotBars"+std::to_string(i)).c_str(),i<=2?4.f:0.f);}
        }
        if(intensity==.94f||intensity==.93f)
        {
            setParam(q,"mute1",0);setParam(q,"mute2",0);setParam(q,"mute3",0);setParam(q,"mute4",0);
            setParam(q,"arpFigure",stromscore::ArpAuto);setParam(q,"szenenLaenge",16);
            if(intensity==.94f){setParam(q,"aufbau",1);setParam(q,"einstieg",stromscore::EntryCounter);}
        }
        if(intensity==.92f||intensity==.91f)
        {
            setParam(q,"motiv",0);setParam(q,"melodie",0);setParam(q,"mute3",0);setParam(q,"arpFigure",stromscore::ArpAuto);
            if(intensity==.91f){setParam(q,"aufbau",1);setParam(q,"einstieg",stromscore::EntryCounter);setParam(q,"szenenLaenge",16);}
        }
        const bool barryAccompaniment=intensity==.73f||intensity==.72f;
        const bool barryLead=barryAccompaniment||intensity==.77f||intensity==.76f||intensity==.75f||intensity==.74f;
        if(barryLead)
        {
            setParam(q,"komponist",1);setParam(q,"genre",0);setParam(q,"aufbau",0);setParam(q,"melodie",1);setParam(q,"mute6",0);
            setParam(q,"faerbung",intensity==.77f||intensity==.75f?.2f:.8f);setParam(q,"unruhe",.3f);
            setParam(q,"melodieMotiv",intensity==.75f||intensity==.74f?0.f:1.f);setParam(q,"motiv",intensity==.76f||intensity==.74f?0.f:1.f);
            CHECK(q.currentSettings().policy.accompaniment.fieldAndOstinato);
        }
        if(barryAccompaniment)
        {
            setParam(q,"faerbung",.85f);setParam(q,"intensitaet",.95f);setParam(q,"unruhe",intensity==.73f?.85f:1.f);
            setParam(q,"eigeneFolge",0);setParam(q,"padPattern",stromscore::PadAuto);setParam(q,"bassPattern",stromscore::BassAuto);
            setParam(q,"arpFigure",stromscore::ArpAuto);setParam(q,"arpRate",stromscore::RateAuto);
            for(int i=1;i<=6;++i)setParam(q,("mute"+std::to_string(i)).c_str(),0);
        }
        const bool popLead=intensity==.82f||intensity==.81f||intensity==.79f||intensity==.78f;
        if(popLead)
        {
            setParam(q,"genre",1);setParam(q,"melodie",1);setParam(q,"mute6",0);setParam(q,"unruhe",.4f);
            setParam(q,"melodieMotiv",intensity==.81f||intensity==.78f?0.f:1.f);
            setParam(q,"motiv",intensity==.79f||intensity==.78f?0.f:1.f);
            setParam(q,"melodieLegato",intensity==.78f?0.f:1.f);
        }
        // The existing plugin export is capped at 64 bars; the core comparison covers 128.
        const int bars=(barryLead||popLead||intensity==.8f||intensity==.9f||intensity==.87f||intensity==.86f||intensity==.85f||intensity==.84f||intensity==.83f||handoff)?64:recurrence?40:8;
        using Timed = std::tuple<long long, int, int, int, int>;
        std::vector<Timed> live, exported;
        auto add = [] (std::vector<Timed>& target, const juce::MidiMessage& m, long long tick)
        {
            if (m.isNoteOnOrOff()) target.emplace_back (tick, m.isNoteOn() ? 1 : 0, m.getChannel(), m.getNoteNumber(), m.isNoteOn() ? m.getVelocity() : 0);
            else if (m.isController() && ! m.isAllNotesOff()) target.emplace_back (tick, 2, m.getChannel(), m.getControllerNumber(), m.getControllerValue());
        };
        auto file = q.renderMidiFile (bars); auto stream = file.createInputStream(); juce::MidiFile mf;
        CHECK (stream != nullptr && mf.readFrom (*stream));
        for (int tr = 0; tr < mf.getNumTracks(); ++tr)
            for (int i = 0; i < mf.getTrack (tr)->getNumEvents(); ++i)
            { const auto& m = mf.getTrack (tr)->getEventPointer (i)->message; add (exported, m, (long long) std::llround (m.getTimeStamp())); }
        juce::AudioBuffer<float> a (2, 512); juce::MidiBuffer m; m.ensureSize (65536);
        for (int at = 0; at < bars*96000; at += 512)
        {
            h.ppq = at / 24000.0; m.clear(); q.processBlock (a, m);
            for (const auto meta : m) add (live, meta.getMessage(), (long long) std::llround ((at + meta.samplePosition) / 25.0));
        }
        h.playing = false; m.clear(); q.processBlock (a, m);
        for (const auto meta : m) add (live, meta.getMessage(), bars*3840);
        std::sort (live.begin(), live.end()); std::sort (exported.begin(), exported.end());
        CHECK (! live.empty() && live == exported);
        if(barryAccompaniment)
            for(int output:{stromscore::OutPadShort,stromscore::OutBassShort,stromscore::OutArp})
                CHECK(std::any_of(live.begin(),live.end(),[&](const Timed& n){return std::get<1>(n)==1&&std::get<2>(n)==q.currentSettings().channel[output];}));
        if(popLead)
        {
            int melody=0,dialog=0,ons=0;long long previous=-1;
            for(const auto& e:live){const auto at=std::get<0>(e);CHECK(!(melody&&dialog&&at>previous));previous=at;
                if(std::get<1>(e)==2)continue;const auto delta=std::get<1>(e)==1?1:-1;
                if(std::get<2>(e)==9){melody+=delta;ons+=delta>0;CHECK(melody>=0&&melody<=1);}
                if(std::get<2>(e)==8){dialog+=delta;CHECK(dialog>=0&&dialog<=2);}}
            CHECK(ons>0&&melody==0&&dialog==0);
        }
        if(intensity==.83f)
        {
            bool active[128] {};
            for(const auto& e:live)if(std::get<0>(e)<=16*3840+1&&std::get<2>(e)==1&&std::get<1>(e)!=2)
                active[std::get<3>(e)]=std::get<1>(e)==1;
            unsigned mask=0;for(int n=0;n<128;++n)if(active[n])mask|=1u<<(n%12);
            CHECK(mask==((1u<<4)|(1u<<11)));
        }
        if(intensity==.84f)
        {
            bool shifted=false,oldSlot=false;
            for(const auto& e:live)if(std::get<1>(e)==1&&std::get<2>(e)==5)
                {shifted|=std::get<0>(e)==23*240;oldSlot|=std::get<0>(e)==22*240;}
            CHECK(shifted&&!oldSlot);
        }
        if(handoff)
        {
            std::vector<Timed> introduction,answers;long long end=0;
            for(const auto& e:live)if(std::get<2>(e)==9&&std::get<0>(e)<=4*1920)
            {if(std::get<1>(e)==1&&std::get<0>(e)<4*1920)introduction.push_back(e);else if(std::get<1>(e)==0)end=std::max(end,std::get<0>(e));}
            CHECK(introduction.size()>=4);const auto source=introduction.size()-3;
            const auto span=end-std::get<0>(introduction[source]);
            for(const auto& e:live)if(std::get<1>(e)==1&&std::get<2>(e)==8)
            {const auto at=std::get<0>(e);if((at>=34*1920&&at<34*1920+span)||(at>=98*1920&&at<98*1920+span))answers.push_back(e);}
            CHECK(answers.size()==6);
            for(int group=0;group<2;++group)for(int i=0;i<3;++i)
            {
                CHECK(std::get<0>(answers[group*3+i])-std::get<0>(answers[group*3])==std::get<0>(introduction[source+i])-std::get<0>(introduction[source]));
                CHECK(std::get<3>(answers[group*3+i])-std::get<3>(answers[group*3])==std::get<3>(introduction[source+i])-std::get<3>(introduction[source]));
            }
        }
        q.setPlayHead (nullptr);
    }

    p->setPlayHead (nullptr);
    // 2.0: target visibility survives an editor reopen and project state roundtrip.
    {
        StromscoreProcessor q; q.markTargetSet(); // even the unchanged default B is an explicit target
        juce::MemoryBlock state; q.getStateInformation (state);
        StromscoreProcessor restored; restored.setStateInformation (state.getData(), (int) state.getSize());
        CHECK (restored.targetSet.load()); CHECK (! restored.currentSettings().drive);
        for (int reopen = 0; reopen < 2; ++reopen)
        {
            std::unique_ptr<juce::AudioProcessorEditor> ed (restored.createEditor());
            int found = 0;
            std::function<void (juce::Component&)> visit = [&] (juce::Component& c)
            {
                if (auto* pad = dynamic_cast<MoodPad*> (&c)) { CHECK (pad->targetPending); ++found; }
                CHECK (! c.getName().startsWith ("CCBereich"));
                for (auto* child : c.getChildren()) visit (*child);
            };
            visit (*ed); CHECK (found == 1);
        }
        CHECK (restored.ccChannelDescription (1).contains (juce::String::fromUTF8 ("Fläche lang")));
        CHECK (restored.ccChannelDescription (2).contains (juce::String::fromUTF8 ("Fläche kurz")));
        CHECK (restored.ccChannelDescription (7).contains ("Akzent Stich"));
        setParam (restored, "kanal2", 0);
        CHECK (restored.ccChannelDescription (1).contains (juce::String::fromUTF8 ("Fläche kurz")));
    }
    // A completed drive must not turn off a fresh activation before the next musical tick.
    {
        StromscoreProcessor q; FakeHost h; q.setPlayHead (&h); q.prepareToPlay (48000, 512);
        setParam (q, "fahrtTakte", 4); setParam (q, "fahrt", 1);
        juce::AudioBuffer<float> a (2, 512); juce::MidiBuffer m; m.ensureSize (65536);
        for (int i = 0; i < 760 && ! q.driveArrived.load(); ++i)
        { h.ppq = i * 512 / 24000.0; m.clear(); q.processBlock (a, m); }
        CHECK (q.driveArrived.load()); q.serviceDrive(); CHECK (! q.currentSettings().drive);
        setParam (q, "fahrt", 1); q.serviceDrive(); CHECK (q.currentSettings().drive);
        h.ppq += 512.0 / 24000.0; m.clear(); q.processBlock (a, m); q.serviceDrive();
        CHECK (q.currentSettings().drive && ! q.driveArrived.load());
        q.beginManualPosition(); setParam (q, "faerbung", 0.37f); setParam (q, "intensitaet", 0.42f); q.serviceDrive();
        CHECK (! q.currentSettings().drive && std::abs (q.currentSettings().x - 0.37f) < 1e-6f);
        q.setPlayHead (nullptr);
    }
    // 2.1 direct bar parameters, route state and end automation survive project restore.
    {
        auto q=std::make_unique<StromscoreProcessor>();auto restored=std::make_unique<StromscoreProcessor>();
        setParam(*q,"aufbauTakte",5);setParam(*q,"szenenLaenge",21);setParam(*q,"fahrtStart",7);setParam(*q,"fahrtTakte",13);
        setParam(*q,"wegpunkte",4);setParam(*q,"weg2X",.73f);setParam(*q,"bogen1Y",-.2f);setParam(*q,"szeneBeenden",1);
        auto s=q->currentSettings();CHECK(s.buildBars==5&&s.sceneBars==21&&s.driveFrom==6&&s.driveBars==13&&s.endRequested);
        juce::MemoryBlock state;q->getStateInformation(state);restored->setStateInformation(state.getData(),(int)state.getSize());s=restored->currentSettings();CHECK(s.route.count==4&&std::abs(s.route.points[2].x-.73f)<1e-6f&&std::abs(s.route.bends[1].y+.2f)<1e-6f&&s.endRequested);
        auto file=q->renderMidiFile(8);juce::FileInputStream input(file);juce::MidiFile midiFile;CHECK(midiFile.readFrom(input));int ons=0;for(int tr=0;tr<midiFile.getNumTracks();++tr)for(int n=0;n<midiFile.getTrack(tr)->getNumEvents();++n)if(midiFile.getTrack(tr)->getEventPointer(n)->message.isNoteOn())++ons;CHECK(ons>1);
        std::unique_ptr<juce::AudioProcessorEditor> ed(q->createEditor());juce::ComboBox* field=nullptr;
        std::function<void(juce::Component&)> findNumber=[&](juce::Component& c){if(c.getComponentID()=="aufbauTakte")field=dynamic_cast<juce::ComboBox*>(&c);for(auto* child:c.getChildren())findNumber(*child);};findNumber(*ed);CHECK(field!=nullptr);
        field->setText("7",juce::sendNotificationSync);CHECK(q->currentSettings().buildBars==7);
        field->setText("ungültig",juce::sendNotificationSync);CHECK(q->currentSettings().buildBars==7);
        field->setSelectedId(17,juce::sendNotificationSync);CHECK(q->currentSettings().buildBars==16);
        // Alt edits never move A/B; inserting and dragging is independent of normal conducting.
        MoodPad pad;pad.setSize(300,300);pad.x=.1f;pad.y=.1f;pad.bx=.9f;pad.by=.9f;pad.showB=true;
        auto mouse=[&](juce::Point<float> pos,bool drag){juce::MouseEvent ev(juce::Desktop::getInstance().getMainMouseSource(),pos,juce::ModifierKeys(juce::ModifierKeys::altModifier|juce::ModifierKeys::leftButtonModifier),1,0,0,0,0,&pad,&pad,juce::Time::getCurrentTime(),pos,juce::Time::getCurrentTime(),1,false);if(drag)pad.mouseDrag(ev);else pad.mouseDown(ev);};
        mouse({150,150},false);CHECK(pad.route.count==1);CHECK(pad.x==.1f&&pad.bx==.9f);
        mouse({150,150},false);mouse({100,120},true);CHECK(pad.route.points[0].x<.5f);
        pad.routeEditable=false;int count=pad.route.count;mouse({200,100},false);CHECK(pad.route.count==count);
    }
    // 2.2 free-mode -> shared harmony plan -> processor MIDI on a shared channel.
    {
        auto q=std::make_unique<StromscoreProcessor>();FakeHost h;q->setPlayHead(&h);
        setParam(*q,"aufbau",0);setParam(*q,"intensitaet",.55f);setParam(*q,"eigeneFolge",1);
        setParam(*q,"padPattern",stromscore::PadHeld);setParam(*q,"bassPattern",stromscore::BassHeld);
        for(int i=3;i<=5;++i)setParam(*q,("mute"+std::to_string(i)).c_str(),1);
        for(int i=1;i<=8;++i)setParam(*q,("kanal"+std::to_string(i)).c_str(),0);
        setParam(*q,"umfang1",1);setParam(*q,"tief1",60);setParam(*q,"hoch1",83);
        setParam(*q,"umfang2",1);setParam(*q,"tief2",36);setParam(*q,"hoch2",59);
        q->prepareToPlay(48000,512);juce::AudioBuffer<float> a(2,512);juce::MidiBuffer m;m.ensureSize(65536);
        Counts ledger;std::map<int,int> initial;
        for(double ppq:{0.,4.,12.5,0.,12.5})
        {
            h.ppq=ppq;m.clear();{NoAllocations guard;q->processBlock(a,m);}collect(m,ledger);
            CHECK(!ledger.broken);
            std::map<int,int> now;
            for(const auto& n:ledger.open)if(n.second){CHECK(n.first.first==1);now[n.first.second]=n.second;}
            CHECK(!now.empty());
            if(ppq<.01){if(initial.empty())initial=now;else CHECK(now==initial);}
            for(const auto& n:now)CHECK((n.first>=36&&n.first<=59)||(n.first>=60&&n.first<=83));
        }
        h.playing=false;m.clear();q->processBlock(a,m);collect(m,ledger);
        CHECK(!ledger.broken&&ledger.ons==ledger.offs);
        for(const auto& n:ledger.open)CHECK(n.second==0);
        q->setPlayHead(nullptr);
    }
    {
        auto q=std::make_unique<StromscoreProcessor>();CHECK(!q->currentSettings().melody);
        setParam(*q,"melodie",1);setParam(*q,"melodieLegato",0);setParam(*q,"melodieMotiv",0);setParam(*q,"kanal9",14);setParam(*q,"tief7",65);setParam(*q,"hoch7",81);
        juce::MemoryBlock state;q->getStateInformation(state);
        auto restored=std::make_unique<StromscoreProcessor>();restored->setStateInformation(state.getData(),static_cast<int>(state.getSize()));
        auto s=restored->currentSettings();CHECK(s.melody&&!s.melodyLegato&&!s.melodyMotif&&s.legato&&s.motif&&s.channel[stromscore::OutMelody]==15&&s.rangeLo[6]==65&&s.rangeHi[6]==81);
        setParam(*restored,"aufbau",0);setParam(*restored,"intensitaet",.7f);setParam(*restored,"solo6",1);
        FakeHost melodyHost;restored->setPlayHead(&melodyHost);
        const auto notes=play(*restored,melodyHost,4,512);CHECK(notes.channels.count(15)&&!notes.broken&&notes.ons==notes.offs);
        restored->setPlayHead(nullptr);
        std::unique_ptr<juce::AudioProcessorEditor> editor(restored->createEditor());CHECK(editor!=nullptr);
        int switches=0;std::function<void(juce::Component&)> find=[&](juce::Component& c)
        {if(c.getComponentID()=="melodieLegato"||c.getComponentID()=="melodieMotiv")
            {auto* b=dynamic_cast<juce::Button*>(&c);CHECK(b&&!b->getToggleState());++switches;}
            for(auto* child:c.getChildren())find(*child);};find(*editor);CHECK(switches==2);

    }
    // Composer choice uses APVTS, persists, and leaves the square mood pad/genre controls untouched.
    {
        using stromscore::composition::ProfileId;
        StromscoreProcessor q;CHECK(q.currentSettings().profile==ProfileId::neutral);
        CHECK(q.apvts.getParameter("komponist")!=nullptr);
        std::unique_ptr<juce::AudioProcessorEditor> editor(q.createEditor());
        juce::ComboBox* profile=nullptr;MoodPad* mood=nullptr;juce::Label* label=nullptr;
        juce::TextButton *score=nullptr,*pop=nullptr;
        std::function<void(juce::Component&)> find=[&](juce::Component& c)
        {
            if(c.getComponentID()=="komponist")profile=dynamic_cast<juce::ComboBox*>(&c);
            if(c.getComponentID()=="komponistLabel")label=dynamic_cast<juce::Label*>(&c);
            if(auto* m=dynamic_cast<MoodPad*>(&c))mood=m;
            if(auto* b=dynamic_cast<juce::TextButton*>(&c))
            {if(b->getButtonText()=="Score")score=b;if(b->getButtonText()=="Pop-Rock")pop=b;}
            for(auto* child:c.getChildren())find(*child);
        };find(*editor);
        CHECK(profile&&mood&&label&&score&&pop);
        CHECK(profile->getNumItems()==4&&profile->getSelectedId()==1&&profile->getText()=="Neutral");
        CHECK(label->getText()=="KOMPONIST"&&label->getBounds()==juce::Rectangle<int>(256,82,142,18));
        CHECK(profile->getBounds()==juce::Rectangle<int>(256,102,142,24));
        CHECK(score->getBounds()==juce::Rectangle<int>(118,80,52,20)&&pop->getBounds()==juce::Rectangle<int>(172,80,60,20));
        for(int width:{600,900,1200,1800})
        {editor->setSize(width,width*656/1200);CHECK(mood->getBounds()==juce::Rectangle<int>(24,102,208,208));
            const auto visible=editor->getLocalArea(mood,mood->getLocalBounds().toFloat());CHECK(std::abs(visible.getWidth()-visible.getHeight())<.0001f);}
        editor->setSize(1200,656);
        std::vector<juce::Rectangle<int>> column;
        for(auto* c:profile->getParentComponent()->getChildren())
            if(c->isVisible()&&c->getX()>=252&&c->getRight()<=404&&c->getY()>=82&&c->getBottom()<=310)
                column.push_back(c->getBounds());
        CHECK(column.size()==10);
        for(size_t i=0;i<column.size();++i)for(size_t j=0;j<i;++j)CHECK(!column[i].intersects(column[j]));
        setParam(q,"aufbau",0);setParam(q,"faerbung",.2f);setParam(q,"intensitaet",.45f);setParam(q,"unruhe",.45f);
        q.prepareToPlay(48000,512);FakeHost host;q.setPlayHead(&host);juce::AudioBuffer<float> audio(2,512);juce::MidiBuffer midi;
        int phrase=0;
        for(int item:{2,3,4,1})
        {
            profile->setSelectedId(item,juce::sendNotificationSync);
            const auto settings=q.currentSettings();CHECK(static_cast<int>(settings.profile)==item-1);
            CHECK(profile->getText()==StromscoreProcessor::profileNames()[item-1]);
            host.ppq=phrase*32.;midi.clear();q.processBlock(audio,midi);
            CHECK(q.wendung.load()==stromscore::Generator::pick(settings,phrase));++phrase;
        }
        setParam(q,"komponist",1);CHECK(q.currentSettings().policy.accompaniment.fieldAndOstinato);
        setParam(q,"genre",1);CHECK(!q.currentSettings().policy.accompaniment.fieldAndOstinato);setParam(q,"genre",0);
        setParam(q,"komponist",2);CHECK(profile->getSelectedId()==3&&q.currentSettings().profile==ProfileId::bernardHerrmann);
        juce::MemoryBlock state;q.getStateInformation(state);editor.reset();
        auto restored=std::make_unique<StromscoreProcessor>();restored->setStateInformation(state.getData(),static_cast<int>(state.getSize()));
        CHECK(restored->currentSettings().profile==ProfileId::bernardHerrmann);
        std::unique_ptr<juce::AudioProcessorEditor> reopened(restored->createEditor());profile=nullptr;find(*reopened);
        CHECK(profile&&profile->getSelectedId()==3&&profile->getText()=="Bernard Herrmann");
        if(const auto* path=std::getenv("STROMSCORE_GUI_SNAPSHOT"))
        {
            reopened->setVisible(true);
            auto stream=juce::File(juce::String::fromUTF8(path)).createOutputStream();
            CHECK(stream&&juce::PNGImageFormat().writeImageToStream(
                reopened->createComponentSnapshot(reopened->getLocalBounds(),true,2.f),*stream));
        }
        host.playing=false;midi.clear();q.processBlock(audio,midi);q.setPlayHead(nullptr);
    }
    return 0;
}
