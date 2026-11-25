#include "ScoreEngine.h"
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace stromscore;
int main(){Settings s;s.profile=composition::ProfileId::johnBarry;int ids[kMaxWendungen];std::cout<<std::setprecision(9)<<"variety,x,y,z,count,distance,selected\n";
for(float v:{0.f,.5f,1.f})for(int x=0;x<=20;++x)for(int y=0;y<=20;++y)for(int z=0;z<=20;++z){s.variety=v;s.x=x/20.f;s.y=y/20.f;s.z=z/20.f;
 double distance=100;for(int i=0;i<wendungCount(s.genre,s.profile);++i){auto w=wendungAt(s.genre,i,s.profile);double a=w.x-s.x,b=w.y-s.y,c=w.z-s.z;distance=std::min(distance,std::sqrt(a*a+.49*b*b+.64*c*c));}
 int n=Generator::candidates(s,ids,kMaxWendungen);std::cout<<v<<','<<s.x<<','<<s.y<<','<<s.z<<','<<n<<','<<distance<<','<<static_cast<unsigned>(wendungAt(s.genre,Generator::pick(s,0),s.profile).id)<<'\n';}}
