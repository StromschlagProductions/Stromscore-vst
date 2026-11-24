#include "ScoreEngine.h"
#include <cstdlib>
#include <iostream>
using namespace stromscore;
int main(int argc,char** argv)
{
 if(argc!=5)return 2;Settings s;s.genre=std::atoi(argv[1]);const auto& w=wendungAt(s.genre,std::atoi(argv[2]));
 s.x=w.x;s.y=w.y;s.z=w.z;s.variety=0;s.profile=static_cast<composition::ProfileId>(std::atoi(argv[3]));s.motif=true;s.melody=true;s.melodyMotif=true;s.swing=.3f;

#ifdef POP_HOOK_REGRESSION
 s.policy.popHooks.enabled=false;
#endif

#ifdef BASS_REGRESSION_CONTROL
 s.policy.bass.enabled=false;
#endif
 Generator g;EventList es;const int block=std::atoi(argv[4]);constexpr int total=16*96000;
 auto emit=[&](int at){for(int i=0;i<es.size;++i){auto e=es.events[i];std::cout<<at+e.offset<<','<<int(e.channel)<<','<<int(e.note)<<','<<int(e.velocity)<<','<<int(e.type)<<','<<int(e.out)<<'\n';}};
 for(int at=0;at<total;){Transport t;t.playing=true;t.ppq=at/24000.;int n=std::min(block,total-at);es.clear();g.process(t,s,n,es);emit(at);at+=n;}
 Transport stop;es.clear();g.process(stop,s,block,es);emit(total);
}
