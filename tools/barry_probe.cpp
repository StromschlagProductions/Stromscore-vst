// Offline actual-product rendering, also compiled against pinned pre-Barry headers.
#include "ScoreEngine.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace stromscore;
int main(int argc,char** argv)
{
 if(argc!=8)return 2;Settings s;s.profile=static_cast<composition::ProfileId>(std::atoi(argv[1]));int path=std::atoi(argv[2]),bars=std::atoi(argv[3]),block=std::atoi(argv[4]),route=std::atoi(argv[5]);s.genre=std::atoi(argv[6]);int manual=std::atoi(argv[7]);
#ifdef BARRY_PROFILE
 s.policy=composition::policyForContext(s.profile,s.genre==GenreScore);
#else
 s.policy=*composition::policyForProfile(s.profile);
#endif
 s.key=0;s.y=.8f;s.x=.2f;s.z=.4f;s.melody=true;s.motif=true;s.inertia=true;s.dynamics=true;
 if(manual){s.padPattern=PadHeld;s.bassPattern=BassQuarter;s.arpFigure=ArpCircle;s.arpRate=RateEighth;}
 Generator g;Transport t;t.playing=true;EventList events;const long long end=bars*96000LL,segment=end/4;
 auto emit=[&](long long at){if(events.overflow)std::exit(3);for(int i=0;i<events.size;++i){auto e=events.events[i];std::cout<<at+e.offset<<','<<int(e.out)<<','<<int(e.channel)<<','<<int(e.note)<<','<<int(e.velocity)<<','<<int(e.type)<<'\n';}};
 for(long long at=0;at<end;){const auto local=at%segment;const int part=at/segment;const double q=at/24000.;const double controlQ=(at/6000*6000)/24000.;
  if(path==1){s.x=.8f;s.y=.3f;s.z=.1f;}if(path==2){s.x=.5f+.45f*std::sin(controlQ*.2);s.y=.7f+.25f*std::sin(controlQ*.13);s.z=.5f+.45f*std::sin(controlQ*.17);}
  if(path==3){s.x=.85f;s.y=.9f;s.z=.9f;}if(path==4){s.x=.15f;s.y=.2f;s.z=.8f;}
  if(route&&part==3&&local==0){Transport stop;events.clear();g.process(stop,s,1,events);emit(at);}
  t.ppq=route?(part==0?0:part==1?96:part==2?16:0)+local/24000.:q;
  const int n=std::min<long long>({block,end-at,segment-local,6000-at%6000});events.clear();g.process(t,s,n,events);emit(at);at+=n;
 }
 Transport stop;events.clear();g.process(stop,s,block,events);emit(end);
}
