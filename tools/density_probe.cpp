// Complete MIDI/CC events plus bar-end harmonic/material diagnostics, at a fixed 48 kHz/120 BPM.
#include "ScoreEngine.h"
#include <cstdlib>
#include <iostream>
using namespace stromscore;
int main(int argc,char** argv)
{
    if(argc!=4)return 2;
    const int scenario=std::atoi(argv[1]),profile=std::atoi(argv[2]),block=std::atoi(argv[3]);
    Settings s;s.profile=static_cast<composition::ProfileId>(profile);s.key=0;s.x=.3f;s.y=.9f;s.z=.4f;
    s.seed=3;s.motif=true;s.dynamics=true;s.custom=true;
    s.customChords[0]={0,MinMaj9,4};s.customChords[1]={5,MinMaj7,2};s.customChords[2]={0,MinMaj9,2};
    s.hardness=.5f;if(scenario==17||scenario==18)s.custom=false;
    const bool build=scenario==18||scenario==1||scenario==2||scenario==3||scenario==9||scenario==11||scenario==12;
    s.scene=build;s.entry=EntryCounter;s.buildBars=8;
    if(scenario==2||scenario==16)s.y=.3f;
    if(scenario==3||scenario==5||scenario==13||scenario==14||scenario==19||scenario==20)
    {s.padPattern=PadGated;s.bassPattern=BassPulse;s.arpFigure=ArpUp;s.arpRate=RateSixteenth;}
    if(scenario==4||scenario==5||scenario==10||scenario==13||scenario==14||scenario==19||scenario==20)s.sceneBars=16;
    if(scenario==19)s.passing=true;
    if(scenario==20)s.dynamics=false;
    if(scenario==6||scenario==7){s.sceneBars=16;s.ending=scenario==6?EndOpen:EndHard;}
    if(scenario==8||scenario==9||scenario==10)s.genre=GenrePopRock;
    if(scenario==11){s.mute[kFlaeche]=s.mute[kBass]=s.mute[kArp]=s.mute[kAkzent]=true;}
    if(scenario==12)s.melody=true;
    if(scenario==15)s.hardness=0;
    Generator g;EventList events;constexpr long long sr=48000,total=48*sr,bar=96000;
    auto emit=[&](long long at){for(int i=0;i<events.size;++i){auto e=events.events[static_cast<size_t>(i)];
        std::cout<<at+e.offset<<','<<int(e.channel)<<','<<int(e.note)<<','<<int(e.velocity)<<','<<int(e.type)<<','<<int(e.out)<<'\n';}};
    for(long long pos=0;pos<total;)
    {
        long long segment=0,boundary=total;double origin=0;
        if(scenario==13||scenario==14)
        {
            if(pos<4*sr)boundary=4*sr;
            else if(pos<24*sr){segment=4*sr;origin=32;boundary=24*sr;}
            else{segment=24*sr;origin=0;}
        }
        if(scenario==15&&pos>=16*sr)s.endRequested=true;
        if(scenario==14&&pos==24*sr){Transport stop;events.clear();g.process(stop,s,block,events);emit(pos);}
        const int n=static_cast<int>(std::min<long long>({block,total-pos,boundary-pos,bar-pos%bar}));
        Transport t;t.playing=true;t.ppq=origin+static_cast<double>(pos-segment)/24000.;
        events.clear();g.process(t,s,n,events);if(events.overflow)return 3;emit(pos);pos+=n;
        if(pos%bar==0)
        {
            std::cerr<<pos<<','<<g.wendung()<<','<<g.chordRoot()<<','<<g.chordType();
            for(int o:{OutCounter,OutMelody}){const auto& m=g.rememberedMotif(o);std::cerr<<','<<m.identity<<','<<m.count;}
            std::cerr<<'\n';
        }
    }
    Transport stop;events.clear();g.process(stop,s,block,events);emit(total);
}
