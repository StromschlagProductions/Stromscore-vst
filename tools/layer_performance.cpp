#include "ScoreEngine.h"
#include <chrono>
#include <ctime>
#include <vector>
#include <iostream>
using namespace stromscore;
int main(){Settings s;s.profile=composition::ProfileId::bernardHerrmann;s.policy=composition::policyForContext(s.profile,true);s.scene=false;s.sceneBars=0;s.melody=true;s.motif=true;s.melodyMotif=true;Generator g;Transport t;t.playing=true;t.bpm=100;EventList events;std::vector<double> cpu,wall;cpu.reserve(20000);wall.reserve(20000);
 for(int i=0;i<20000;++i){if(i%225==0){double u=i/225.;s.x=.5f+.45f*std::sin(u*.3);s.y=.6f+.3f*std::sin(u*.21);s.z=.5f+.45f*std::cos(u*.17);}t.ppq=i*128./28800.;events.clear();const auto begin=std::chrono::steady_clock::now();const auto c=std::clock();g.process(t,s,128,events);cpu.push_back(1e6*(std::clock()-c)/CLOCKS_PER_SEC);wall.push_back(std::chrono::duration<double,std::micro>(std::chrono::steady_clock::now()-begin).count());if(events.overflow)return 1;}
 auto print=[](std::vector<double> v){std::sort(v.begin(),v.end());double sum=0;for(double n:v)sum+=n;std::cout<<"{\"mean_us\":"<<sum/v.size()<<",\"p99_us\":"<<v[v.size()*99/100]<<",\"max_us\":"<<v.back()<<'}';};std::cout<<"{\"blocks\":20000,\"block_samples\":128,\"block_budget_us\":2666.67,\"generator_bytes\":"<<sizeof(Generator)<<",\"cpu\":";print(cpu);std::cout<<",\"wall_contended_host\":";print(wall);std::cout<<"}\n";
}
