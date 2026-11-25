#include "TimeDiagnostics.h"
#include "ScoreEngine.h"
#include "../Tests/MotifExperiment.h"
#include <cstdlib>
#include <iostream>
#include <set>
using namespace stromscore;
int main(int argc,char** argv)
{
 if(argc<4)return 2;const int scenario=std::atoi(argv[1]),block=std::atoi(argv[2]);const double bpm=std::atof(argv[3]);
 int index=scenario<36?scenario:34;
 if(scenario==44)index=30;if(scenario==46)index=3;if(scenario==51)index=30;if(scenario==57)index=3;
 const auto& w=kPopWendungen[index];Settings s;pinMotifExperiment(s);s.genre=GenrePopRock;s.x=w.x;s.y=w.y;s.z=w.z;s.variety=0;
 s.mute[kGegenstimme]=s.mute[kAkzent]=true;s.swing=scenario%2?.3f:0;
 if(scenario==36||scenario==38)s.follow[kBass]=false;
 if(scenario==37||scenario==38)s.follow[kArp]=false;
 if(scenario==39)s.bassPattern=BassFunk;
 if(scenario==40)s.arpFigure=ArpCircle;
 if(scenario==41)s.arpRate=RateEighth;
 if(scenario==42)s.y=.1f;
 if(scenario==43){s.y=.97f;s.layerIntensity[kArp]=-.5f;}
 if(scenario==44)s.bassPattern=BassPedal;
 if(scenario==45)s.bassPattern=BassPulse;
 if(scenario==46)s.bassPattern=BassHiNrg;
 if(scenario==47)s.channel[OutPadLong]=s.channel[OutArp];
 if(scenario==48)s.scene=true;
 if(scenario==49)s.sceneBars=32;
 if(scenario==50||scenario==51)s.mute[kGegenstimme]=false;
 if(scenario==50){s.custom=true;s.customChords[0]={0,Maj,4};s.customChords[1]={7,Maj,4};s.policy.popHooks.phrasedCustom=true;}
 if(scenario>=52&&scenario<=54){s.genre=GenreScore;s.profile=static_cast<composition::ProfileId>(scenario-52);s.mute[kGegenstimme]=false;s.melody=true;}
 if(scenario==55){s.custom=true;s.customChords[0]={0,Maj,4};s.customChords[1]={0,Maj,4};}
 if(scenario==56)s.layerIntensity[kBass]=.49f;
 if(scenario==57){s.layerIntensity[kBass]=.3f;s.layerIntensity[kArp]=-.1f;}
 if(scenario==58)s.policy.texture.arpeggio.eighthBelow=.8f;
 if(scenario==59)s.mute[kBass]=true;
 if(scenario==60)s.mute[kArp]=true;
 if(scenario==61)s.solo[kBass]=true;
 if(scenario==62){s.meterNum=3;s.meterDen=4;}
 if(scenario==63)s.passing=true;
 if(scenario==64){s.layerIntensity[kArp]=-.3f;}
#ifdef RHYTHM_DIAGNOSTICS
 s.policy.chords.enabled=false;
 if(scenario==58)s.policy.rhythm.everyBars=1;
 if(argc>4)s.policy.rhythm.enabled=std::atoi(argv[4])!=0;
#endif
 Generator g;Transport t;t.playing=true;t.bpm=bpm;EventList es;std::set<long long> seen;
 const double bar=48000*60/bpm*4;const long long total=static_cast<long long>(128*bar);
 auto emit=[&](long long at){for(int i=0;i<es.size;++i){auto e=es.events[i];std::cout<<at+e.offset<<','<<int(e.channel)<<','<<int(e.note)<<','<<int(e.velocity)<<','<<int(e.type)<<','<<int(e.out)<<'\n';}};
 for(long long at=0;at<total;)
 {
  t.ppq=at*bpm/(48000.*60);const auto nextBar=static_cast<long long>(std::ceil((std::floor(t.ppq/4)+1)*bar-1e-7));int n=static_cast<int>(std::min<long long>({block,total-at,std::max(1LL,nextBar-at)}));es.clear();g.process(t,s,n,es);if(es.overflow)return 3;emit(at);
#ifdef RHYTHM_DIAGNOSTICS
  for(int i=0;i<es.size;++i)if(es.events[i].out==OutArp&&es.events[i].velocity&&!es.events[i].type)
  {
   const auto tick=static_cast<long long>(std::floor((t.ppq+es.events[i].offset*bpm/(48000.*60))*4+1e-4));
   const auto begin=(tick/16)*16;if(!seen.insert(begin).second)continue;const auto plan=g.inspectMovementRhythm(tick,s);
   if(plan.active){std::cerr<<"R,"<<begin<<','<<plan.reference<<','<<plan.original<<','<<plan.coordinated<<','<<plan.count;for(int j=0;j<plan.count;++j){auto p=plan.notes[j];std::cerr<<','<<diagnosticTime(p.at)<<','<<diagnosticTime(p.source)<<','<<diagnosticTime(p.length);}const auto bass=g.inspectBassPhrase();std::cerr<<','<<int(bass.valid&&diagnosticTime(bass.begin)<=begin&&diagnosticTime(bass.end)>=begin+16)<<'\n';}
  }
#endif
  at+=n;
 }
 Transport stop;es.clear();g.process(stop,s,block,es);emit(total);
}
