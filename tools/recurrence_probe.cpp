#include "ScoreEngine.h"
#include <cstdlib>
#include <iostream>
#include <set>
#include <tuple>
using namespace stromscore;
int main(int argc,char** argv)
{
    if(argc<4||argc>5)return 2;
    const int scenario=std::atoi(argv[1]),profile=std::atoi(argv[2]),block=std::atoi(argv[3]);
    Settings s;s.profile=static_cast<composition::ProfileId>(profile);s.key=0;s.x=.3f;s.y=.7f;s.z=0;s.motif=true;s.seed=3;
    s.custom=true;s.customChords[0]={0,Maj7,8};s.mute[kFlaeche]=s.mute[kBass]=s.mute[kAkzent]=true;
    if(scenario==0)s.y=.25f;
    if(scenario==2)s.x=.8f;
    if(scenario==3){s.x=.15f;s.z=.8f;s.customChords[0]={0,MinMaj9,8};}
    if(scenario==4||scenario==5||scenario==13||scenario==14)
    {s.customChords[0]={0,Maj7,1};s.customChords[1]={9,Min7,3};s.customChords[2]={2,Min7,2};s.customChords[3]={7,Dom7,2};}
    if(scenario==5){s.y=.3f;s.z=.3f;}
    if(scenario==6)s.custom=false;
    if(scenario==7)s.customChords[0].bars=1;
    if(scenario==8)s.customChords[0].bars=4;
    if(scenario==9||scenario==10){s.melody=true;s.melodyMotif=true;}
    if(scenario==10)s.arpFigure=ArpCell;
    if(scenario==11)s.arpFigure=ArpCell;
    if(scenario==12)s.genre=GenrePopRock;
    if(scenario==16)s.scene=true,s.entry=EntryCounter;
    if(scenario==17)s.motif=false;
    if(scenario==18){s.customChords[1]={9,Min7,8};}
#ifdef RECURRENCE_DIAGNOSTICS
    if(scenario==19)s.policy.motif.normalSteps={2,2,2};
    if(scenario==20)s.policy.motif.minimumSilentBars=4;
#endif
    if(scenario==23){s.scene=true;s.entry=EntryCounter;s.sceneBars=61;}
    if(scenario==24){s.y=.25f;s.z=.8f;}
    if(scenario==25){s.y=.25f;s.layerIntensity[kGegenstimme]=.5f;}
#if defined(RECURRENCE_DIAGNOSTICS) && !defined(VARIATION_DIAGNOSTICS)
    // Pin the pre-development rhythm-only policy for this historical regression fixture.
    for(size_t i=0;i<s.policy.motif.variations.size();++i)s.policy.motif.variations[i]=i%2?composition::MotifVariation::rhythm:composition::MotifVariation::original;
#endif
#ifdef VARIATION_DIAGNOSTICS
    if(argc==5){const int requested=std::atoi(argv[4]);if(requested>=0&&requested<=4)s.policy.motif.variations.fill(static_cast<composition::MotifVariation>(requested));}
#endif

#ifdef POP_HOOK_REGRESSION
 s.policy.popHooks.enabled=false;
#endif

#ifdef BASS_REGRESSION_CONTROL
 s.policy.bass.enabled=false;
 s.policy.rhythm.enabled=false;
 s.policy.chords.enabled=false;
#endif
 Generator g;EventList events;constexpr long long bar=96000,total=128*bar;
    std::set<std::pair<int,uint64_t>> published;
    std::set<std::tuple<int,int64_t,int64_t,int64_t>> occurrences;
    auto emit=[&](long long at){for(int i=0;i<events.size;++i){auto e=events.events[static_cast<size_t>(i)];
        std::cout<<at+e.offset<<','<<int(e.channel)<<','<<int(e.note)<<','<<int(e.velocity)<<','<<int(e.type)<<','<<int(e.out)<<'\n';}};
    for(long long pos=0;pos<total;)
    {
        const int wallBar=static_cast<int>(pos/bar);
        if(scenario==13&&wallBar>=8){s.rangeOn[4]=true;s.rangeLo[4]=61;s.rangeHi[4]=61;if(wallBar>=64)s.rangeOn[4]=false;}
        if(scenario==15){if(wallBar>=32){s.x=.8f;s.y=.25f;s.z=.3f;}if(wallBar>=64){s.x=.15f;s.y=.9f;s.z=.8f;}}
        if(scenario==21){s.melody=wallBar>=24&&wallBar<64;}
        long long segment=0,boundary=total;double origin=0;
        if(scenario==14||scenario==22)
        {
            if(pos<4*bar)boundary=4*bar;
            else if(pos<48*bar){segment=4*bar;origin=98;boundary=48*bar;}
            else{segment=48*bar;origin=0;}
        }
        if(scenario==22&&pos==48*bar){Transport stop;events.clear();g.process(stop,s,block,events);emit(pos);}
        const int n=static_cast<int>(std::min<long long>({block,total-pos,boundary-pos,bar-pos%bar}));
        Transport t;t.playing=true;t.ppq=origin+static_cast<double>(pos-segment)/24000.;
        events.clear();g.process(t,s,n,events);if(events.overflow)return 3;emit(pos);pos+=n;
        if(pos%bar==0)
        {
            std::cerr<<"H,"<<pos<<','<<g.wendung()<<','<<g.chordRoot()<<','<<g.chordType();
            for(int o:{OutCounter,OutMelody}){const auto& m=g.rememberedMotif(o);std::cerr<<','<<m.identity<<','<<m.count;}
            std::cerr<<'\n';
            for(int o:{OutCounter,OutMelody})
            {
                const auto& m=g.rememberedMotif(o);
                if(m.complete&&published.insert({o,m.identity}).second)
                {
                    std::cerr<<"M,"<<o<<','<<m.identity<<','<<m.count<<','<<m.origin;
                    for(int i=0;i<m.count;++i){const auto& note=m.notes[static_cast<size_t>(i)];std::cerr<<','<<note.at<<','<<note.length<<','<<note.interval;}
                    std::cerr<<'\n';
                }
#ifdef RECURRENCE_DIAGNOSTICS
                const long long tick=static_cast<long long>((t.ppq+n/24000.)*4)-1;
                const auto plan=g.inspectMotifOccurrence(tick,s,o);
                if(plan.active&&occurrences.insert({o,plan.begin,plan.end,plan.ordinal}).second)
                {
                    std::cerr<<"O,"<<o<<','<<plan.begin<<','<<plan.end<<','<<plan.ordinal<<','<<plan.varied<<','<<plan.introduction<<','<<plan.base<<'\n';
#ifdef VARIATION_DIAGNOSTICS
                    std::cerr<<"V,"<<o<<','<<plan.begin<<','<<plan.end<<','<<plan.ordinal<<','<<plan.introduction<<','<<plan.base<<','<<static_cast<int>(plan.figure.variation)<<','<<plan.figure.sourceIdentity<<','<<plan.figure.count;
                    for(int i=0;i<plan.figure.count;++i){const auto& n=plan.figure.notes[static_cast<size_t>(i)];std::cerr<<','<<n.at<<','<<n.length<<','<<n.interval;}
                    std::cerr<<'\n';
#endif
                }
#endif
            }
        }
    }
    Transport stop;events.clear();g.process(stop,s,block,events);emit(total);
}
