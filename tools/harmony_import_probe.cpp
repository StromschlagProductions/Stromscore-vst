// Compiled only against an isolated test header snapshot with a selection seam.
#include "ScoreEngine.h"
#include "../Tests/TestSupport.h"
#include <iomanip>
#include <iostream>
#include <cstdlib>
using namespace stromscore;
int main(int argc,char** argv)
{
 if(argc==2)
 {
  std::cout<<std::setprecision(9);Settings s;s.genre=GenrePopRock;
  for(int x=0;x<=20;++x)for(int y=0;y<=20;++y)for(int z=0;z<=20;++z)for(float v:{0.f,.25f,.5f,.75f,1.f})
  {
   s.x=x/20.f;s.y=y/20.f;s.z=z/20.f;s.variety=v;int ids[kMaxWendungen];const int n=Generator::candidates(s,ids,kMaxWendungen);
   double nearest=100,euclidean=100;const float best=Generator::bestWeight(s);int exact=0;
   for(int i=0;i<kNumPopWendungen;++i){auto w=wendungAt(GenrePopRock,i);const double dx=w.x-s.x,dy=w.y-s.y,dz=w.z-s.z;
    nearest=std::min(nearest,std::sqrt(dx*dx+.49*dy*dy+.64*dz*dz));euclidean=std::min(euclidean,std::sqrt(dx*dx+dy*dy+dz*dz));
    exact+=Generator::weight(w,s)>=Generator::keepRatio(s)*best;}
   std::cout<<x<<','<<y<<','<<z<<','<<v<<','<<n<<','<<exact<<','<<nearest<<','<<euclidean<<','<<static_cast<unsigned>(wendungAt(s.genre,Generator::pick(s,0)).id);
   for(int i=0;i<n;++i)std::cout<<','<<static_cast<unsigned>(wendungAt(s.genre,ids[i]).id);std::cout<<'\n';
  }return 0;
 }
 if(argc!=16&&argc!=17&&argc!=19&&argc!=20)return 2;
 importTestId=static_cast<WendungId>(std::atoi(argv[1]));Settings s;s.genre=GenrePopRock;s.key=std::atoi(argv[2]);s.x=std::atof(argv[3]);s.y=std::atof(argv[4]);s.z=std::atof(argv[5]);
 s.follow[0]=s.follow[1]=s.follow[2]=std::atoi(argv[6])!=0;
 if(std::atoi(argv[7])){s.padPattern=PadHeld;s.bassPattern=BassHeld;s.arpFigure=ArpCircle;s.arpRate=RateEighth;}
 s.melody=std::atoi(argv[8])!=0;s.mute[kGegenstimme]=std::atoi(argv[9])==0;
 const int bars=std::atoi(argv[10]),block=std::atoi(argv[11]);const double bpm=std::atof(argv[12]);const bool route=std::atoi(argv[13])!=0;
 s.profile=static_cast<composition::ProfileId>(std::atoi(argv[14]));s.swing=std::atof(argv[15]);s.variety=0;s.passing=true;s.motif=true;if(argc>=17)s.genre=std::atoi(argv[16]);
 if(argc>=19){s.meterNum=std::atoi(argv[17]);s.meterDen=std::atoi(argv[18]);}
 // Dedicated time-planning regression controls, only in this offline probe.
 if(argc==20)
 {
  const int scenario=std::atoi(argv[19]);s.motif=false;s.melody=false;s.passing=false;
  if(scenario==1){s.scene=true;s.inertia=true;s.sceneBars=24;s.buildBars=4;s.entry=EntryAuto;s.ending=EndFade;s.hardness=.25f;}
  if(scenario==2){s.bassPattern=BassFunk;s.arpFigure=ArpCircle;s.arpRate=RateEighth;s.channel[OutArp]=s.channel[OutPadLong];}
 }
 const double barQuarters=Meter::from(s.meterNum,s.meterDen).len*kStep;
 Generator g;Transport t;t.bpm=bpm;t.playing=true;EventList events;const double spq=48000.*60./bpm;
 const long long end=std::llround(bars*barQuarters*spq),segment=end/4;
 auto emit=[&](long long at){if(events.overflow)std::exit(4);for(int i=0;i<events.size;++i){auto e=events.events[i];std::cout<<at+e.offset<<','<<int(e.out)<<','<<int(e.channel)<<','<<int(e.note)<<','<<int(e.velocity)<<','<<int(e.type)<<'\n';}};
 for(long long at=0;at<end;)
 {
  const int part=static_cast<int>(at/segment);const long long local=at%segment;
  if(route&&part==3&&local==0){Transport stop;events.clear();g.process(stop,s,1,events);emit(at);}
  t.ppq=route?(part==0?0.:part==1?128.125:part==2?16.:0.)+local/spq:at/spq;
  const auto nextBar=static_cast<long long>(std::ceil((std::floor(local/(spq*barQuarters))+1)*spq*barQuarters-1e-7));
  const int n=static_cast<int>(std::min<long long>({block,end-at,segment-local,std::max(1LL,nextBar-local)}));
  events.clear();{NoAllocations guard;g.process(t,s,n,events);}if(importTestId!=WendungId::invalid&&wendungAt(s.genre,g.wendung()).id!=importTestId)return 5;emit(at);at+=n;
 }
 Transport stop;events.clear();g.process(stop,s,block,events);emit(end);
}
