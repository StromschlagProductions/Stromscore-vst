#include "ScoreEngine.h"
#include "WendungInfo.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
using namespace stromscore;
int main(int argc,char** argv)
{
 if(argc==2)
 {
  std::cout<<std::setprecision(9);
  for(int t=0;t<kNumChordTypes;++t){auto sh=kShapes[t];std::cout<<"S,"<<t<<','<<sh.n<<','<<sh.suffix<<','<<sh.minor;for(int j=0;j<sh.n;++j)std::cout<<','<<sh.iv[j];std::cout<<'\n';}
  for(int genre=0;genre<2;++genre)for(int i=0;i<wendungCount(genre);++i)
  {
   const auto& w=wendungAt(genre,i);const auto& info=genre?kPopInfo[i]:kScoreInfo[i];std::cout<<"W,"<<genre<<','<<i<<','<<static_cast<unsigned>(w.id)<<','<<w.name<<','<<w.x<<','<<w.y<<','<<w.z<<','<<w.n;
   for(int j=0;j<w.n;++j){auto c=w.ch[j];std::cout<<','<<c.root<<','<<c.type<<','<<c.bars<<','<<c.bass;}
   for(int j=0;j<2;++j)std::cout<<','<<w.arp[j]<<','<<w.bass[j];
   std::cout<<','<<w.pad<<','<<popHookPattern(w.id);
   for(auto p:{composition::ProfileId::neutral,composition::ProfileId::johnBarry,composition::ProfileId::bernardHerrmann})std::cout<<','<<composition::harmonicPreference(p,w.id);
   std::cout<<'\n'<<info.idea<<'\n'<<info.instruments<<'\n'<<info.source<<'\n';
  }return 0;
 }
 if(argc!=6)return 2;
 Settings s;s.genre=std::atoi(argv[1]);const int index=std::atoi(argv[2]),profile=std::atoi(argv[3]),block=std::atoi(argv[4]),route=std::atoi(argv[5]);
 const auto w=wendungAt(s.genre,index);s.x=w.x;s.y=w.y;s.z=w.z;s.variety=0;s.profile=static_cast<composition::ProfileId>(profile);s.melody=true;s.swing=index%2?.3f:0.f;s.dynamics=true;
 bool found=false;for(int v=1;v<=16;++v){s.variation=v;if(Generator::pick(s,0)==index){found=true;break;}}if(!found)return 3;
 Generator g;EventList es;const double bpm=index%3==0?90:index%3==1?120:173;
 const double samplesPerQuarter=48000.*60./bpm;
 auto emit=[&](long long at){for(int i=0;i<es.size;++i){auto e=es.events[i];std::cout<<at+e.offset<<','<<int(e.channel)<<','<<int(e.note)<<','<<int(e.velocity)<<','<<int(e.type)<<','<<int(e.out)<<'\n';}};
 const long long segment=static_cast<long long>(16*4*samplesPerQuarter),renderEnd=4*segment;
 for(long long at=0;at<renderEnd;)
 {
  const int part=static_cast<int>(at/segment);Transport t;t.playing=true;t.bpm=bpm;
  const long long local=at%segment;const double origin=route?(part==0?0:part==1?96:part==2?32:0):part*64.;
  if(route&&part==3&&local==0){Transport stop;es.clear();g.process(stop,s,1,es);emit(at);}
  t.ppq=origin+local/samplesPerQuarter;const auto nextBar=static_cast<long long>(std::ceil((std::floor(local/(samplesPerQuarter*4))+1)*samplesPerQuarter*4-1e-7));const int n=static_cast<int>(std::min<long long>({block,renderEnd-at,segment-local,std::max(1LL,nextBar-local)}));es.clear();g.process(t,s,n,es);if(es.overflow)return 4;emit(at);at+=n;
 }
 Transport stop;es.clear();g.process(stop,s,block,es);emit(renderEnd);

}
