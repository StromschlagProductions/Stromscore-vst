#include "ScoreEngine.h"
#include <iostream>
#include <chrono>
using namespace stromscore;
int main()
{
 std::cout<<"variety,num,den,x,y,z,motif,notes,complete,microseconds,rhythm_candidate\n";
 for(float variety:{0.f,.5f,1.f})for(auto m:{std::pair<int,int>{4,4},{3,4},{6,8}})
 for(int x=0;x<=6;++x)for(int y=0;y<=6;++y)for(int z=0;z<=6;++z)
 {
  Settings s;s.profile=composition::ProfileId::johnBarry;s.policy=composition::policyForContext(s.profile,true);s.x=x/6.f;s.y=y/6.f;s.z=z/6.f;s.variety=variety;s.melody=true;s.solo[kMelodie]=true;s.meterNum=m.first;s.meterDen=m.second;
  Generator g;Transport t;t.playing=true;EventList e;int64_t total=9*m.first*4LL/m.second*24000;
  const auto start=std::chrono::steady_clock::now();
  for(int64_t at=0;at<total;at+=6000){t.ppq=at/24000.;e.clear();g.process(t,s,6000,e);}
  const auto elapsed=std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now()-start).count();const auto& memory=g.rememberedMotif(OutMelody);
  std::cout<<variety<<','<<m.first<<','<<m.second<<','<<s.x<<','<<s.y<<','<<s.z<<','<<memory.vocabularyId<<','<<memory.count<<','<<memory.complete<<','<<elapsed<<',';
  const auto& w=wendungAt(GenreScore,g.wendung(),s.profile);int stable=8;for(int i=0;i<w.n;++i)stable=std::gcd(stable,w.ch[i].bars);
  const auto* rhythm=composition::barry::chooseRhythm(s.x,s.y,s.z,s.meterNum,s.meterDen,stable);std::cout<<(rhythm?rhythm->id:0)<<'\n';
 }
}
