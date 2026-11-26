#include "ScoreEngine.h"
#include <iostream>
#include <cmath>
using namespace stromscore;
int main(){Settings s;s.profile=composition::ProfileId::johnWilliams;int indices[kMaxWendungen];
for(float variety:{0.f,.5f,1.f})for(int x=0;x<=20;++x)for(int y=0;y<=20;++y)for(int z=0;z<=20;++z){s.x=x/20.f;s.y=y/20.f;s.z=z/20.f;s.variety=variety;
 const auto* pool=wendungTable(GenreScore,s.profile);float best=Generator::bestWeight(s);int exact=0;float distance=10;
 for(int i=0;i<wendungCount(GenreScore,s.profile);++i){if(Generator::weight(pool[i],s)>=Generator::keepRatio(s)*best)++exact;const float dx=pool[i].x-s.x,dy=.7f*(pool[i].y-s.y),dz=.8f*(pool[i].z-s.z);distance=std::min(distance,std::sqrt(dx*dx+dy*dy+dz*dz));}
 std::cout<<variety<<','<<x<<','<<y<<','<<z<<','<<exact<<','<<Generator::candidates(s,indices,kMaxWendungen)<<','<<distance;
 for(int salt=0;salt<8;++salt)std::cout<<','<<static_cast<int>(pool[Generator::pick(s,salt)].id);std::cout<<'\n';}}
