#include "ScoreEngine.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
using namespace stromscore;
int main(int argc,char** argv)
{
    const int scenario=argc>1?std::atoi(argv[1]):0,profile=argc>2?std::atoi(argv[2]):0;
    const int block=argc>3?std::atoi(argv[3]):512;
    Settings s;s.profile=static_cast<composition::ProfileId>(profile);s.key=0;s.variation=17;
    s.scene=false;s.padPattern=PadHeld;s.bassPattern=BassHeld;s.melody=true;s.melodyMotif=true;
    s.passing=false;s.variety=.8f;s.x=.3f;s.y=.65f;s.z=.2f;
    if(scenario==1)s.x=.8f,s.y=.5f;
    if(scenario==2)s.x=.15f,s.y=.8f,s.z=.85f;
    if(scenario==3)s.x=.75f,s.y=.3f,s.z=.3f;
    if(scenario==7)s.genre=GenrePopRock;
    if(scenario==8){s.custom=true;s.customChords[0]={0,Maj7,4};s.customChords[1]={6,MinMaj7,4};}
    if(scenario==9)s.mute[kFlaeche]=true;
    if(scenario==10)s.padPattern=PadGated,s.bassPattern=BassWalking;
    if(scenario==11)s.bassPattern=BassPedal;
    if(scenario==12){s.drive=true;s.driveX=.9f;s.driveY=.8f;s.driveFrom=0;s.driveBars=64;}
#if defined(ENTRY_DIAGNOSTICS) && !defined(VARIATION_DIAGNOSTICS)
    // Pin the pre-development rhythm-only policy for this historical regression fixture.
    for(size_t i=0;i<s.policy.motif.variations.size();++i)s.policy.motif.variations[i]=i%2?composition::MotifVariation::rhythm:composition::MotifVariation::original;
#endif

#ifdef POP_HOOK_REGRESSION
 s.policy.popHooks.enabled=false;
#endif

#ifdef BASS_REGRESSION_CONTROL
 s.policy.bass.enabled=false;
 s.policy.rhythm.enabled=false;
#endif
 Generator g;EventList events;constexpr long long bar=96000,total=128*bar;
    int last=-1000,previousRoot=0,previousType=0;long long lastTick=-1;
    auto emit=[&](long long at){for(int i=0;i<events.size;++i){const auto& e=events.events[static_cast<size_t>(i)];
        std::cout<<at+e.offset<<','<<int(e.channel)<<','<<int(e.note)<<','<<int(e.velocity)<<','<<int(e.type)<<','<<int(e.out)<<'\n';}};
    for(long long at=0;at<total;)
    {
        const int b=static_cast<int>(at/bar),segment=b/8;
        if(scenario==4){s.x=(segment%2)? .9f:.1f;s.y=.55f;s.z=(segment%3)*.35f;}
        if(scenario==5){s.x=static_cast<float>(segment%5)/4;s.y=.75f;s.z=.8f;}
        if(scenario==6){s.x=(segment%3)*.5f;s.y=(segment%2)? .85f:.3f;s.z=.4f;}
        const int n=static_cast<int>(std::min<long long>({block,total-at,6000-at%6000}));
        Transport t;t.playing=true;t.ppq=static_cast<double>(at)/24000.;events.clear();g.process(t,s,n,events);
        if(events.overflow)return 3;emit(at);
        if(last!=g.wendung())
        {
            const long long tick=(at/6000)*6000;
            std::cerr<<tick<<','<<g.wendung()<<','<<g.chordRoot()<<','<<g.chordType()<<','<<previousRoot<<','<<previousType<<','<<(s.custom?s.customChords[0].bars:wendungAt(s.genre,g.wendung()).ch[0].bars)<<'\n';last=g.wendung();lastTick=tick;
        }
        previousRoot=g.chordRoot();previousType=g.chordType();at+=n;
    }
    Transport stop;events.clear();g.process(stop,s,block,events);emit(total);return lastTick<0;
}
