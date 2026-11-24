#include "TimeDiagnostics.h"
#include "ScoreEngine.h"
#include <cstdlib>
#include <iostream>
#include <set>
using namespace stromscore;
int main(int argc,char** argv)
{
 if(argc<5)return 2;const int scenario=std::atoi(argv[1]),block=std::atoi(argv[2]),key=std::atoi(argv[4]);const double bpm=std::atof(argv[3]);
 int index=scenario<36?scenario:34;if(scenario==64)index=31;if(scenario==76)index=29;
 const auto& w=kPopWendungen[index];Settings s;s.genre=GenrePopRock;s.x=w.x;s.y=w.y;s.z=w.z;s.variety=0;s.key=key;s.swing=scenario%2?.3f:0;
 if(scenario>=36&&scenario<54)
 {s.custom=true;s.z=.1f;s.customChords[0]={0,scenario-36,2};s.customChords[1]={5,scenario-36,1};s.customChords[2]={0,scenario-36,3};s.customChords[3]={7,scenario-36,2};}
 if(scenario==54)s.padPattern=PadHeld;
 if(scenario==55)s.padPattern=PadStabs;
 if(scenario==56||scenario==58)s.follow[kFlaeche]=false;
 if(scenario==57||scenario==58)s.follow[kBass]=false;
 if(scenario==59)s.mute[kBass]=true;
 if(scenario==60)s.channel[OutBassShort]=s.channel[OutPadShort];
 if(scenario==61){s.rangeOn[0]=true;s.rangeLo[0]=60;s.rangeHi[0]=62;}
 if(scenario==62)s.scene=true;
 if(scenario==63)s.sceneBars=32;
 if(scenario>=65&&scenario<=67){s.genre=GenreScore;s.profile=static_cast<composition::ProfileId>(scenario-65);s.melody=true;}
 if(scenario==68)s.y=.97f;
 if(scenario==69)s.y=.18f;
 if(scenario>=74&&scenario<=77&&scenario!=76)
 {s.custom=true;s.customChords[0]={0,Maj7,2};s.customChords[1]={5,Min9,2};s.customChords[2]={0,Sus4,2};s.customChords[3]={7,Add9,2};s.bassPattern=BassHeld;}
 if(scenario==75)s.follow[kBass]=false;
 if(scenario==76)s.bassPattern=BassHeld;
 if(scenario==77){s.rangeOn[1]=true;s.rangeLo[1]=49;s.rangeHi[1]=50;}
 if(scenario==78)s.padPattern=PadGated;
 if(scenario==79)s.padPattern=PadPulse;
 if(scenario==80)s.padPattern=PadStaccato;
#ifdef DISPOSITION_DIAGNOSTICS
 if(scenario>=70&&scenario<=73)for(auto& d:s.policy.chords.cycle)d={static_cast<composition::ChordPopulation>((scenario-70)/2),static_cast<composition::ChordSpacing>((scenario-70)%2)};
 if(scenario>=74&&scenario<=77)for(auto& d:s.policy.chords.cycle)d={composition::ChordPopulation::lean,composition::ChordSpacing::natural};
 if(argc>5)s.policy.chords.enabled=std::atoi(argv[5])!=0;
#endif
 Generator g;Transport t;t.playing=true;t.bpm=bpm;EventList es;std::set<long long> seen;
 const double bar=48000*60/bpm*4;const long long total=static_cast<long long>(128*bar);
 auto emit=[&](long long at){for(int i=0;i<es.size;++i){auto e=es.events[i];std::cout<<at+e.offset<<','<<int(e.channel)<<','<<int(e.note)<<','<<int(e.velocity)<<','<<int(e.type)<<','<<int(e.out)<<'\n';}};
 for(long long at=0;at<total;)
 {
  t.ppq=at*bpm/(48000.*60);const auto next=static_cast<long long>(std::ceil((std::floor(t.ppq/4)+1)*bar-1e-7));const int n=static_cast<int>(std::min<long long>({block,total-at,std::max(1LL,next-at)}));es.clear();g.process(t,s,n,es);if(es.overflow)return 3;emit(at);
#ifdef DISPOSITION_DIAGNOSTICS
  const auto d=g.inspectChordDisposition();const auto tick=diagnosticDispositionStep(g,0);
  bool played=false;for(int i=0;i<es.size;++i)if(es.events[i].out<2&&es.events[i].velocity&&!es.events[i].type)
      played|=static_cast<long long>(std::llround((t.ppq+es.events[i].offset*bpm/(48000.*60))*4))==tick;
  if(played&&d.applied&&seen.insert(tick).second)
  {
   std::cerr<<"D,"<<tick<<','<<static_cast<int>(d.disposition.population)<<','<<static_cast<int>(d.disposition.spacing)<<','<<d.chordMask<<','<<d.required<<','<<d.omitted<<','<<d.bassCoversRoot<<','<<d.notes.n;
   for(int i=0;i<d.notes.n;++i)std::cerr<<','<<d.notes.notes[i];std::cerr<<'\n';
  }
#endif
  at+=n;
 }
 Transport stop;es.clear();g.process(stop,s,block,es);emit(total);
}
