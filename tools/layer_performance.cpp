#include "ScoreEngine.h"
#include <chrono>
#include <ctime>
#include <vector>
#include <iostream>
using namespace stromscore;
int main(int argc,char**){Settings s;s.profile=composition::ProfileId::bernardHerrmann;s.policy=composition::policyForContext(s.profile,true);s.scene=false;s.sceneBars=0;s.melody=true;s.motif=true;s.melodyMotif=true;if(argc>1){s.rangeOn[1]=true;s.rangeLo[1]=24;s.rangeHi[1]=67;s.octave[kBass]=-2;}double peak=0;int peakBlock=0,peakSource=-1;float peakX=0,peakY=0,peakZ=0;Generator g;Transport t;t.playing=true;t.bpm=100;EventList events;std::vector<double> cpu,wall;cpu.reserve(20000);wall.reserve(20000);
 for(int i=0;i<20000;++i){if(i%225==0){double u=i/225.;s.x=.5f+.45f*std::sin(u*.3);s.y=.6f+.3f*std::sin(u*.21);s.z=.5f+.45f*std::cos(u*.17);}t.ppq=i*128./28800.;events.clear();const auto begin=std::chrono::steady_clock::now();const auto c=std::clock();g.process(t,s,128,events);cpu.push_back(1e6*(std::clock()-c)/CLOCKS_PER_SEC);wall.push_back(std::chrono::duration<double,std::micro>(std::chrono::steady_clock::now()-begin).count());if(cpu.back()>peak){peak=cpu.back();peakBlock=i;peakSource=g.wendung()<0?-1:static_cast<int>(wendungAt(s.genre,g.wendung(),s.profile).id);peakX=s.x;peakY=s.y;peakZ=s.z;}if(events.overflow)return 1;}
 auto print=[](std::vector<double> v){std::sort(v.begin(),v.end());double sum=0;for(double n:v)sum+=n;std::cout<<"{\"mean_us\":"<<sum/v.size()<<",\"p99_us\":"<<v[v.size()*99/100]<<",\"max_us\":"<<v.back()<<'}';};std::cout<<"{\"blocks\":20000,\"block_samples\":128,\"block_budget_us\":2666.67,\"generator_bytes\":"<<sizeof(Generator)<<",\"user_register\":"<<(argc>1?"true":"false")<<",\"peak_block\":"<<peakBlock<<",\"peak_source\":"<<peakSource<<",\"peak_xyz\":["<<peakX<<','<<peakY<<','<<peakZ<<"],\"cpu\":";print(cpu);std::cout<<",\"wall_contended_host\":";print(wall);std::cout<<"}\n";
}
