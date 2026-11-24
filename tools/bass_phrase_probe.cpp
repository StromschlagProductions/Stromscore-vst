#include "ScoreEngine.h"
#include <cstdlib>
#include <iostream>
#include <set>
using namespace stromscore;
int main(int argc,char** argv)
{
 if(argc<5)return 2;int scenario=std::atoi(argv[1]),block=std::atoi(argv[2]),key=std::atoi(argv[4]);double bpm=std::atof(argv[3]);
 const int ids[]={14,18,11,24,29,30,31,34,12,27,20};int selected=ids[scenario%11];if(scenario>=18)selected=24;if(scenario==19)selected=30;if(scenario==20)selected=34;const auto& w=kPopWendungen[selected];
 Settings s;s.genre=scenario==29?GenreScore:GenrePopRock;s.x=w.x;s.y=w.y;s.z=w.z;s.variety=0;s.key=key;s.swing=scenario%2?.3f:0;
 s.mute[kArp]=s.mute[kAkzent]=s.mute[kGegenstimme]=true;s.padPattern=PadHeld;
 if(scenario>=11&&scenario<18)s.follow[kBass]=false;
 if(scenario==18)s.bassPattern=BassFunk;
 if(scenario==19)s.bassPattern=BassPedal;
 if(scenario==20)s.y=.97f;
 if(scenario==21)s.bassPattern=BassEighth;
 if(scenario==22){s.rangeOn[1]=true;s.rangeLo[1]=48;s.rangeHi[1]=49;}
 if(scenario==23)s.scene=true;
 if(scenario==24)s.channel[OutPadShort]=s.channel[OutBassShort];
 if(scenario==25){s.bassPattern=BassHeld;}
 if(scenario==26)s.passing=true;
 if(scenario==28)s.bassPattern=BassPulse;
 if(scenario==27)s.change=Change4Bars;
 if(scenario==27)for(int v=1;v<=16;++v)if((hash3(v,1,47u)&1u)==1u){s.variation=v;break;}
#ifdef BASS_DIAGNOSTICS
 if(argc>5)s.policy.bass.enabled=std::atoi(argv[5])!=0;
#endif
 Generator g;EventList es;std::set<long long> seen;
 const auto bar=std::llround(48000*60/bpm*4),total=static_cast<long long>(128*48000*60/bpm*4);
 auto emit=[&](long long at){for(int i=0;i<es.size;++i){auto e=es.events[i];std::cout<<at+e.offset<<','<<int(e.channel)<<','<<int(e.note)<<','<<int(e.velocity)<<','<<int(e.type)<<','<<int(e.out)<<'\n';}};
 for(long long at=0;at<total;)
 {
  const auto tbar=at/bar;if(scenario==27&&tbar>=9&&tbar<12)s.y=.97f;else if(scenario==27)s.y=w.y;
  Transport t;t.playing=true;t.bpm=bpm;t.ppq=at*bpm/(48000.*60);int n=static_cast<int>(std::min<long long>({block,total-at,bar-at%bar}));es.clear();g.process(t,s,n,es);if(es.overflow)return 3;emit(at);
#ifdef BASS_DIAGNOSTICS
  auto p=g.inspectBassPhrase();bool played=false;
  for(int i=0;i<es.size;++i){auto e=es.events[i];if(e.out==OutBassShort&&e.velocity&&!e.type){const auto tick=(t.ppq+e.offset*bpm/(48000.*60))*4;played|=p.valid&&tick>=p.begin-.001&&tick<p.end;}}
  if(played&&seen.insert(p.begin).second){std::cerr<<"P,"<<p.begin<<','<<p.middle<<','<<p.end<<','<<p.count;
    for(int i=0;i<p.count;++i){auto n=p.notes[i];std::cerr<<','<<n.at<<','<<n.pitch<<','<<n.length<<','<<n.accent<<','<<n.passing<<','<<n.anchor<<','<<n.resolution;}std::cerr<<'\n';}
#endif
  at+=n;
 }
 Transport stop;es.clear();g.process(stop,s,block,es);emit(total);
}
