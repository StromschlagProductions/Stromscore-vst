#include "ScoreEngine.h"
#include <cstdlib>
#include <iostream>
#include <set>
using namespace stromscore;
int main(int argc,char** argv)
{
 if(argc<4)return 2;int scenario=std::atoi(argv[1]),block=std::atoi(argv[2]);double bpm=std::atof(argv[3]);
 const int indices[]={30,33,29,28,34,27,33,33};int index=indices[scenario];const auto& w=kPopWendungen[index];Settings s;
 s.genre=GenrePopRock;s.x=w.x;s.y=w.y;s.z=w.z;s.variety=0;s.key=0;s.swing=scenario%2?.3f:0;s.mute[kFlaeche]=s.mute[kBass]=s.mute[kAkzent]=true;
 if(scenario==7){s.custom=true;s.customChords[0]={0,Maj7,8};}
#ifdef HOOK_DIAGNOSTICS
#ifndef MODAL_DIAGNOSTICS
#ifdef PASSING_CONTROL
 s.policy.passing.enabled=false;
#endif
#else
 if(argc>5)s.policy.passing.enabled=std::atoi(argv[5])!=0;
#endif
 if(scenario==7)s.policy.popHooks.phrasedCustom=true;
 if(argc>4)s.policy.popHooks.enabled=std::atoi(argv[4])!=0;
#endif
 Generator g;EventList es;std::set<long long> seen;bool published=false;
 const long long bar=std::llround(48000*60/bpm*4),total=static_cast<long long>(128*48000*60/bpm*4);
 auto emit=[&](long long at){for(int i=0;i<es.size;++i){auto e=es.events[i];std::cout<<at+e.offset<<','<<int(e.channel)<<','<<int(e.note)<<','<<int(e.velocity)<<','<<int(e.type)<<','<<int(e.out)<<'\n';}};
 for(long long at=0;at<total;)
 {
  int b=static_cast<int>(at/bar);if(scenario==6){const auto& target=kPopWendungen[(b/8)%2?29:33];s.x=target.x;s.y=target.y;s.z=target.z;}
  Transport t;t.playing=true;t.bpm=bpm;t.ppq=at*bpm/(48000.*60);const int n=static_cast<int>(std::min<long long>({block,total-at,bar-at%bar}));es.clear();g.process(t,s,n,es);if(es.overflow)return 3;emit(at);
  const auto& m=g.rememberedMotif();
  if(m.complete&&!published){std::cerr<<"M,"<<m.identity<<','<<m.count<<','<<m.origin;for(int i=0;i<m.count;++i)std::cerr<<','<<m.notes[i].at<<','<<m.notes[i].length<<','<<m.notes[i].interval;std::cerr<<'\n';published=true;}
#ifdef HOOK_DIAGNOSTICS
  long long emittedTick=-1;
  for(int i=0;i<es.size;++i){const auto& e=es.events[i];if(e.out==OutCounter&&e.type==0&&e.velocity>0)emittedTick=static_cast<long long>(std::floor((t.ppq+e.offset*bpm/(48000.*60))*4+1e-4));}
  auto p=emittedTick>=0?g.inspectMotifOccurrence(emittedTick,s):composition::MotifOccurrence{};
  if(p.active&&!p.introduction&&p.begin<128*16&&seen.insert(p.begin).second){std::cerr<<"P,"<<p.begin<<','<<p.end<<','<<p.ordinal<<','<<static_cast<int>(p.figure.variation)<<','<<p.base<<','<<p.figure.sourceIdentity<<','<<p.figure.count;for(int i=0;i<p.figure.count;++i)std::cerr<<','<<p.figure.notes[i].at<<','<<p.figure.notes[i].length<<','<<p.figure.notes[i].interval;std::cerr<<'\n';
#ifdef MODAL_DIAGNOSTICS
   std::cerr<<"D,"<<p.begin<<','<<p.figure.passingIndex<<'\n';
#endif
  }
#endif
  at+=n;
 }
 Transport stop;es.clear();g.process(stop,s,block,es);emit(total);
}
