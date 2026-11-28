#include "ScoreEngine.h"
#include "realtime_probe.h"
#include <memory>
#include <cmath>
#include <string>
using namespace stromscore;
int main(int argc,char**argv){
 const int profile=argc>1?std::atoi(argv[1]):2,genre=argc>2?std::atoi(argv[2]):0,block=argc>3?std::atoi(argv[3]):128,scenario=argc>4?std::atoi(argv[4]):2,bars=argc>5?std::atoi(argv[5]):64,instances=argc>6?std::atoi(argv[6]):1;
 std::vector<std::unique_ptr<Generator>> generators;for(int i=0;i<instances;++i)generators.emplace_back(new Generator);
 std::vector<std::unique_ptr<EventList>> lists;for(int i=0;i<instances;++i)lists.emplace_back(new EventList);
 Settings s;s.profile=static_cast<composition::ProfileId>(profile);s.genre=genre;s.policy=composition::policyForContext(s.profile,genre==0);s.scene=false;s.sceneBars=0;s.key=2;s.melody=s.motif=s.melodyMotif=true;s.stichFixed=true;s.variation=3;
 Transport t;t.playing=true;t.bpm=100;EventList events;rtprobe::Hash hash;rtprobe::Series cpu,wall;const int64_t total=static_cast<int64_t>(bars)*115200;const size_t count=(total+block-1)/block+1;cpu.values.reserve(count);wall.values.reserve(count);double peak=0;int64_t peakAt=0;int peakW=-1;int notes=0;bool overflow=false;
 for(int64_t at=0;at<total;at+=block){const int n=static_cast<int>(std::min<int64_t>(block,total-at));double u=at/28800.;
  s.x=scenario==0?0:scenario==1?.2f:.8f;s.y=scenario==0?0:.8f;s.z=scenario==0?0:scenario==1?.9f:.8f;
  if(scenario==3){s.x=.5f+.48f*std::sin(u*.71);s.y=.6f+.39f*std::sin(u*.53);s.z=.5f+.48f*std::cos(u*.91);}
  t.playing=true;t.ppq=u;if(scenario==4){const int p=static_cast<int>(u/16)%4;t.playing=p!=1;if(p==2)t.ppq=std::fmod(u,16.);if(p==3)t.ppq=u+8.125;}
  if(scenario==5){s.profile=static_cast<composition::ProfileId>((profile+static_cast<int>(u/16))%6);s.policy=composition::policyForContext(s.profile,genre==0);}
  s.dynamics=scenario==6;if(scenario==6){s.x=.5f+.48f*std::sin(u*.3);s.y=.5f+.48f*std::cos(u*.4);s.z=.5f+.48f*std::sin(u*.7);}
  const auto w0=rtprobe::wallUs(),c0=rtprobe::cpuUs();
  for(int i=0;i<instances;++i){lists[i]->clear();generators[i]->process(t,s,n,*lists[i]);}
  const auto c=rtprobe::cpuUs()-c0,w=rtprobe::wallUs()-w0;cpu.values.push_back(c);wall.values.push_back(w);if(c>peak){peak=c;peakAt=at;peakW=generators[0]->wendung();}
  for(int i=0;i<instances;++i){const auto& es=*lists[i];overflow|=es.overflow;for(int j=0;j<es.size;++j){const auto e=es.events[j];hash.add(i);hash.add(at+e.offset);hash.add(e.out);hash.add(e.channel);hash.add(e.note);hash.add(e.velocity);hash.add(e.type);notes+=!e.type&&e.velocity>0;}}
 }
 t.playing=false;for(int i=0;i<instances;++i){events.clear();generators[i]->process(t,s,block,events);for(int j=0;j<events.size;++j){auto e=events.events[j];hash.add(i);hash.add(total+e.offset);hash.add(e.out);hash.add(e.channel);hash.add(e.note);hash.add(e.velocity);hash.add(e.type);}}
 const double budget=block*1e6/48000.;std::cout<<"{\"profile\":"<<profile<<",\"genre\":"<<genre<<",\"block\":"<<block<<",\"scenario\":"<<scenario<<",\"bars\":"<<bars<<",\"instances\":"<<instances<<",\"budget_us\":"<<budget<<",\"blocks\":"<<cpu.values.size()<<",\"digest\":\""<<hash.value<<"\",\"note_ons\":"<<notes<<",\"peak_sample\":"<<peakAt<<",\"peak_wendung\":"<<peakW<<",\"cpu_us\":";cpu.print(budget);std::cout<<",\"wall_us\":";wall.print(budget);std::cout<<"}\n";return overflow?1:0;
}
