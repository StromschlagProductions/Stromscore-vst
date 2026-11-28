#include "ScoreEngine.h"
#include <iostream>
using namespace stromscore;
int main(){Settings s;s.profile=composition::ProfileId::bernardHerrmann;s.policy=composition::policyForContext(s.profile,true);int ids[kMaxWendungen];
 std::cout<<"x,y,z,variety,candidates,nearest_xyz_distance\n";
 for(int x=0;x<=12;++x)for(int y=0;y<=12;++y)for(int z=0;z<=12;++z)for(float variety:{0.f,.5f,1.f}){
  s.x=x/12.f;s.y=y/12.f;s.z=z/12.f;s.variety=variety;float distance=100;
  for(int i=0;i<wendungCount(s.genre,s.profile);++i){const auto& w=wendungAt(s.genre,i,s.profile);distance=std::min(distance,std::sqrt((s.x-w.x)*(s.x-w.x)+(s.y-w.y)*(s.y-w.y)+(s.z-w.z)*(s.z-w.z)));}
  std::cout<<s.x<<','<<s.y<<','<<s.z<<','<<variety<<','<<Generator::candidates(s,ids,kMaxWendungen)<<','<<distance<<'\n';
 }
}
