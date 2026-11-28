#include "ScoreEngine.h"
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace stromscore;
int main(){std::cout<<"generator_bytes,"<<sizeof(Generator)<<"\n";
 const float xyz[][3]={{0,0,0},{.1,.1,.9},{.2,.8,.9},{.85,.2,.15},{.5,.5,.5},{.8,.8,.8}};
 for(const auto& p:xyz){Settings s;s.profile=composition::ProfileId::johnCarpenter;s.policy=composition::policyForContext(s.profile,true);s.x=p[0];s.y=p[1];s.z=p[2];s.melody=true;s.motif=s.melodyMotif=true;s.scene=false;s.sceneBars=0;s.key=2;s.stichFixed=true;
  Generator g;Transport t;t.playing=true;t.bpm=100;EventList e;std::vector<double> cpu;cpu.reserve(30000);double first=0,max=0;
  for(int at=0;at<64*115200;at+=512){t.ppq=at/28800.;e.clear();const auto before=std::clock();g.process(t,s,512,e);const double dt=1000.*(std::clock()-before)/CLOCKS_PER_SEC;if(at==0)first=dt;max=std::max(max,dt);cpu.push_back(dt);}
  std::sort(cpu.begin(),cpu.end());std::cout<<p[0]<<','<<p[1]<<','<<p[2]<<",first_cpu_ms,"<<first<<",p99_cpu_ms,"<<cpu[cpu.size()*99/100]<<",max_cpu_ms,"<<max<<"\n";
 }
}
