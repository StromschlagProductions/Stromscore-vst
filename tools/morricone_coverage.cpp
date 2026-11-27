#include "ScoreEngine.h"
#include <iostream>
#include <set>
using namespace stromscore;
int main(){
 std::cout<<"x,y,z,variety,candidates,selected_ids\n";
 Settings s;s.profile=composition::ProfileId::ennioMorricone;
 for(int x=0;x<=10;++x)for(int y=0;y<=10;++y)for(int z=0;z<=10;++z)for(float variety:{0.f,.5f,1.f}){
  s.x=x/10.f;s.y=y/10.f;s.z=z/10.f;s.variety=variety;int candidates[kMaxWendungen];
  const int n=Generator::candidates(s,candidates,kMaxWendungen);if(n<=0)return 1;
  std::set<unsigned> selected;for(int seed=0;seed<64;++seed){const auto index=Generator::pick(s,seed);if(index<0||index>=wendungCount(GenreScore,s.profile))return 2;selected.insert(static_cast<unsigned>(wendungAt(GenreScore,index,s.profile).id));}
  std::cout<<s.x<<','<<s.y<<','<<s.z<<','<<variety<<','<<n<<',';bool first=true;for(auto id:selected){if(!first)std::cout<<';';first=false;std::cout<<id;}std::cout<<'\n';
 }
}
