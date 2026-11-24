// Reproducible note/CC probe shared by the current and pinned pre-coordination engine.
#include "ScoreEngine.h"
#include <cstdlib>
#include <iostream>
using namespace stromscore;
int main(int argc,char** argv)
{
    if(argc!=4&&argc!=5)return 2;
    const int scenario=std::atoi(argv[1]),profile=std::atoi(argv[2]),block=std::atoi(argv[3]);
    Settings s;s.profile=static_cast<composition::ProfileId>(profile);s.key=0;s.y=.7f;s.x=.3f;s.z=0;
    s.motif=true;s.seed=3;s.custom=true;s.customChords[0]={0,Maj7,8};
    s.melody=scenario==18||scenario==1||scenario==4||scenario==5||scenario==7||scenario==8||scenario==15;
    if(scenario==1)s.motif=false;
    if(scenario==2){s.motif=false;s.melodyMotif=false;}
    if(scenario==3)s.genre=GenrePopRock;
    if(scenario==4){s.rangeOn[6]=true;s.rangeLo[6]=61;s.rangeHi[6]=61;s.mute[kGegenstimme]=true;}
    if(scenario==5)s.melodyMotif=false;
    if(scenario==6||scenario==7)s.arpFigure=ArpCell;
    if(scenario==8)s.channel[OutArp]=s.channel[OutMelody];
    if(scenario==9)s.mute[kGegenstimme]=true;
    if(scenario==10){s.solo[kArp]=true;}
    if(scenario==11){s.scene=true;s.inertia=true;s.hardness=0;s.buildBars=8;}
    if(scenario==12){s.customChords[0]={0,Maj7,1};s.customChords[1]={5,Min7,3};s.customChords[2]={7,Dom7,4};s.passing=true;}
    if(scenario==13){s.meterNum=3;s.meterDen=4;s.swing=.5f;}
    if(scenario==14)s.custom=false;
    if(scenario==15){s.melodyMotif=false;s.motif=false;}
    if(argc==5){s.seed=std::atoi(argv[4]);s.variation=1+s.seed%16;}

#ifdef POP_HOOK_REGRESSION
 s.policy.popHooks.enabled=false;
#endif

#ifdef BASS_REGRESSION_CONTROL
 s.policy.bass.enabled=false;
 s.policy.rhythm.enabled=false;
#endif
 Generator g;EventList events;
    constexpr long long sr=48000,total=96*sr;
    auto emit=[&](long long at){for(int i=0;i<events.size;++i){auto e=events.events[static_cast<size_t>(i)];std::cout<<at+e.offset<<','<<int(e.channel)<<','<<int(e.note)<<','<<int(e.velocity)<<','<<int(e.type)<<','<<int(e.out)<<'\n';}};
    for(long long pos=0;pos<total;)
    {
        // Transport boundaries aligned independently of the block size.
        long long boundary=total;double origin=0;long long segment=0;
        if(scenario==16||scenario==17)
        {
            if(pos<4*sr)boundary=4*sr;
            else if(pos<36*sr){segment=4*sr;origin=64;boundary=36*sr;}
            else {segment=36*sr;origin=0;}
        }
        const int n=static_cast<int>(std::min<long long>(block,boundary-pos));
        Transport t;t.playing=true;t.ppq=origin+static_cast<double>(pos-segment)/24000.;
        if(scenario==17&&pos==36*sr){Transport stop;t.playing=false;events.clear();g.process(stop,s,n,events);emit(pos);t.playing=true;}
        events.clear();g.process(t,s,n,events);if(events.overflow)return 3;emit(pos);pos+=n;
    }
    Transport stop;events.clear();g.process(stop,s,block,events);emit(total);
}
