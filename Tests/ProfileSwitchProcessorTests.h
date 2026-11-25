#pragma once
// Real processor and editor, including the normal message-loop timer, not a GUI-only mock.
static int testProfileSwitchProcessor()
{
    struct State
    {
        std::unique_ptr<StromscoreProcessor> processor;FakeHost host;
        std::unique_ptr<juce::AudioProcessorEditor> editor;ChordDisplay* display=nullptr;
        Counts ledger;int64_t sample=0;std::set<std::pair<int,int>> harmonies;
    };
    std::atomic<bool> finished{false};int completed=0;
    std::function<void(int,int,std::shared_ptr<State>)> run;
    run=[&](int index,int stage,std::shared_ptr<State> state)
    {
        const int genre=index/4,from=(index/2)%2;const bool stopped=(index%2)!=0;
        if(!state)
        {
            state=std::make_shared<State>();state->processor=std::make_unique<StromscoreProcessor>();auto& p=*state->processor;
            state->host.bpm=100;state->host.numerator=4;state->host.denominator=4;p.setPlayHead(&state->host);
            setParam(p,"genre",genre);setParam(p,"komponist",from);setParam(p,"key",2);setParam(p,"aufbau",0);
            setParam(p,"faerbung",.2f);setParam(p,"intensitaet",.05f);setParam(p,"unruhe",.5f);setParam(p,"melodie",1);setParam(p,"preview",0);
            p.prepareToPlay(48000,512);state->editor.reset(p.createEditor());
            std::function<void(juce::Component&)> find=[&](juce::Component& c){if(auto* d=dynamic_cast<ChordDisplay*>(&c))state->display=d;for(auto* child:c.getChildren())find(*child);};
            find(*state->editor);CHECK(state->display);
        }
        auto& p=*state->processor;juce::AudioBuffer<float> audio(2,512);juce::MidiBuffer midi;midi.ensureSize(65536);
        auto process=[&](int n){midi.clear();{NoCHeap heap;NoAllocations allocations;p.processBlock(audio,midi);}collect(midi,state->ledger);
            if(state->host.playing){const auto settings=p.currentSettings();CHECK(p.wendung.load()>=0&&p.wendung.load()<stromscore::wendungCount(genre,settings.profile));
                state->harmonies.emplace(p.chordRoot.load(),p.chordType.load());}
            state->sample+=n;};
        if(stage==1)
        {
            if(stopped){state->host.playing=false;process(512);}
            setParam(p,"komponist",1-from); // Switch while still quiet, also when transport is stopped.
            if(stopped)process(512);
            state->host.playing=true;
        }
        if(stage==2){setParam(p,"faerbung",.85f);setParam(p,"intensitaet",.95f);setParam(p,"unruhe",1);state->harmonies.clear();}
        if(stage==3)setParam(p,"preview",1); // Host remains the display source while playing.
        if(stage==4)state->host.playing=false; // The independent preview is now the display source.
        if(stage==5){state->host.playing=true;setParam(p,"preview",0);state->sample=32*28800;}
        if(stage==6)state->sample=16*28800; // Seek / loop back.
        const int blocks=stage==2?static_cast<int>(24*4*28800/512):stage==6?1024:128;
        const int before=state->ledger.ons;
        for(int b=0;b<blocks;++b)
        {
            if(stage==6){setParam(p,"faerbung",.5f+.45f*std::sin(b*.013));setParam(p,"intensitaet",.75f);setParam(p,"variation",1+(b/128)%16);if(b==512)state->sample=16*28800;}
            state->host.ppq=state->sample/28800.;process(512);
        }
        if(stage==2){CHECK(state->harmonies.size()>1);CHECK(state->ledger.ons>before);}
        CHECK(!state->ledger.broken);
        juce::Timer::callAfterDelay(100,[&,index,stage,state,genre,from]
        {
            auto& p=*state->processor;auto* d=state->display;const auto s=p.currentSettings();
            CHECK(d->playing);CHECK(p.wendung.load()>=0&&p.wendung.load()<stromscore::wendungCount(genre,s.profile));
            char name[64];stromscore::chordName(s.key,p.chordRoot.load(),p.chordType.load(),name,64);
            CHECK(d->chord==juce::String::fromUTF8(name));CHECK(d->current==p.chordIndex.load());
            CHECK(d->wendung==juce::String::fromUTF8(stromscore::wendungAt(genre,p.wendung.load(),s.profile).name));
            CHECK(s.profile==static_cast<stromscore::composition::ProfileId>(stage?1-from:from));
            if(stage<6)run(index,stage+1,state);
            else
            {
                state->host.playing=false;setParam(p,"preview",0);juce::AudioBuffer<float> audio(2,512);juce::MidiBuffer midi;
                p.processBlock(audio,midi);collect(midi,state->ledger);CHECK(!state->ledger.broken);
                for(auto n:state->ledger.open)CHECK(n.second==0);
                state->editor.reset();p.setPlayHead(nullptr);p.releaseResources();++completed;
                if(index<7)run(index+1,0,{});else{finished=true;juce::MessageManager::getInstance()->stopDispatchLoop();}
            }
        });
    };
    std::thread watchdog([&]{for(int i=0;i<600&&!finished;++i)std::this_thread::sleep_for(std::chrono::milliseconds(100));if(!finished)juce::MessageManager::getInstance()->stopDispatchLoop();});
    juce::MessageManager::callAsync([&]{run(0,0,{});});juce::MessageManager::getInstance()->runDispatchLoop();finished=true;watchdog.join();CHECK(completed==8);
    std::cout<<"Real processor/editor: 8 live/stopped profile scenarios, 56 GUI states, harmony progression, preview and transport passed\n";return 0;
}
