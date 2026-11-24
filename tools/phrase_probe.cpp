#include "ScoreEngine.h"
#include <cstdlib>
#include <iostream>
using namespace stromscore;
int main(int argc,char** argv)
{
    if(argc!=4)return 2;
    const int scenario=std::atoi(argv[1]),profile=std::atoi(argv[2]),block=std::atoi(argv[3]);
    Settings s;s.profile=static_cast<composition::ProfileId>(profile);s.key=0;s.x=.2f;s.y=.8f;s.z=0;s.motif=false;s.seed=3;
    s.custom=true;s.customChords[0]={0,Maj7,8};s.dynamics=true;
    if(scenario==0)s.y=.2f;
    if(scenario==2)s.x=.8f;
    if(scenario==3){s.x=.15f;s.customChords[0]={0,MinMaj9,8};}
    if(scenario==4||scenario==5||scenario==9||scenario==15||scenario==16)
    {
        s.customChords[0]={0,Maj7,1};s.customChords[1]={9,Min7,3};
        s.customChords[2]={2,Min7,2};s.customChords[3]={7,Dom7,2};
    }
    if(scenario==5)s.y=.3f;
    if(scenario==6)s.z=.8f;
    if(scenario==7)s.z=.55f;
    if(scenario==8||scenario==19){s.rangeOn[4]=true;s.rangeLo[4]=65;s.rangeHi[4]=scenario==8?65:67;}
    if(scenario==9)s.passing=true;
    if(scenario==10||scenario==12||scenario==13)s.motif=true;
    if(scenario==11||scenario==12){s.melody=true;s.melodyMotif=scenario==12;}
    if(scenario==13)s.arpFigure=ArpCell;
    if(scenario==14)s.genre=GenrePopRock;
    if(scenario==17){s.y=.08f;s.layerIntensity[kGegenstimme]=.3f;}
    if(scenario==18)s.customChords[0].bars=1;
    if(scenario==20){s.rangeOn[4]=true;s.rangeLo[4]=72;s.rangeHi[4]=84;s.octave[kGegenstimme]=1;}
    if(scenario==21){s.scene=true;s.entry=EntryCounter;s.sceneBars=16;s.buildBars=8;}
    if(scenario==22)s.custom=false;
    if(scenario==23)s.mute[kGegenstimme]=true;
    if(scenario==24)s.y=.1f;
    if(scenario==25){s.meterNum=3;s.meterDen=8;s.customChords[0].bars=1;}
    if(scenario==26)s.sceneBars=6;
    if(scenario==27)s.legato=false;
    if(scenario==28){s.customChords[0].bars=1;s.customChords[1]={5,Min7,2};s.customChords[2]={0,Maj7,5};}
    Generator g;EventList events;constexpr long long total=48*48000,bar=96000;
    long long previousBegin=-1,previousEnd=-1;
    auto emit=[&](long long at){for(int i=0;i<events.size;++i){auto e=events.events[static_cast<size_t>(i)];
        std::cout<<at+e.offset<<','<<int(e.channel)<<','<<int(e.note)<<','<<int(e.velocity)<<','<<int(e.type)<<','<<int(e.out)<<'\n';}};
    for(long long pos=0;pos<total;)
    {
        long long segment=0,boundary=total;double origin=0;
        if(scenario==15||scenario==16)
        {
            if(pos<4*48000)boundary=4*48000;
            else if(pos<24*48000){segment=4*48000;origin=32;boundary=24*48000;}
            else {segment=24*48000;origin=0;}
        }
        if(scenario==16&&pos==24*48000){Transport stop;events.clear();g.process(stop,s,block,events);emit(pos);}
        const int n=static_cast<int>(std::min<long long>({block,total-pos,boundary-pos,bar-pos%bar}));
        Transport t;t.playing=true;t.ppq=origin+static_cast<double>(pos-segment)/24000.;
        events.clear();g.process(t,s,n,events);if(events.overflow)return 3;emit(pos);pos+=n;
        if(pos%bar==0)
        {
            std::cerr<<"H,"<<pos<<','<<g.wendung()<<','<<g.chordRoot()<<','<<g.chordType();
            for(int o:{OutCounter,OutMelody}){const auto& m=g.rememberedMotif(o);std::cerr<<','<<m.identity<<','<<m.count;}std::cerr<<'\n';
#ifdef PHRASE_DIAGNOSTICS
            const long long tick=static_cast<long long>((t.ppq+n/24000.)*4)-1;
            const auto plan=g.inspectFreePhrase(tick,s);
            if(plan.valid&&(plan.begin!=previousBegin||plan.end!=previousEnd))
            {
                std::cerr<<"P,"<<plan.begin<<','<<plan.end<<','<<plan.goal<<','<<plan.arrival<<','<<plan.breath<<','<<int(plan.ending)<<','<<plan.count;
                for(int i=0;i<plan.count;++i){const auto& note=plan.notes[static_cast<size_t>(i)];std::cerr<<','<<note.begin<<','<<note.end<<','<<note.pitch;}std::cerr<<'\n';
                previousBegin=plan.begin;previousEnd=plan.end;
            }
#endif
        }
    }
    Transport stop;events.clear();g.process(stop,s,block,events);emit(total);
}
