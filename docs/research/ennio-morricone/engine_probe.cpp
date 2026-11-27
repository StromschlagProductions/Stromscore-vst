// Offline analysis only; no vocabulary registration or runtime/profile changes.
#include "ScoreEngine.h"
#include <iostream>
#include <vector>
#include <string>
using namespace stromscore;
int main(){
 Settings settings;auto outputs=outputCatalog(settings);
 for(int o=0;o<kNumOutputs;++o){auto c=outputs[o].track.instrument;std::cout<<"CAP "<<o<<' '<<c.polyphony<<' '<<c.minDuration.value<<' '<<c.maxDuration.value<<'\n';}
 int transitions;std::cin>>transitions;
 for(int t=0;t<transitions;++t){std::string id;int step,a,b;std::cin>>id>>step>>a>>b;voiceleading::ChordVoicing old,target;old.n=a;target.n=b;
  for(int i=0;i<a;++i)std::cin>>old.notes[i];for(int i=0;i<b;++i)std::cin>>target.notes[i];
  for(int key=0;key<12;++key){auto from=old,to=target;for(int i=0;i<a;++i)from.notes[i]+=60+key;for(int i=0;i<b;++i)to.notes[i]+=60+key;
   const auto actual=voiceleading::lead(to,from,0,127);
   std::cout<<"U "<<id<<' '<<step<<' '<<key<<' '<<actual.n;for(int i=0;i<actual.n;++i)std::cout<<' '<<actual.notes[i];std::cout<<'\n';}
 }
 int n,m;std::cin>>n>>m;std::vector<Wendung>w(n,wendungAt(GenreScore,0));for(auto& a:w)std::cin>>a.x>>a.y>>a.z;
 for(int p=0;p<m;++p){Settings s;std::cin>>s.x>>s.y>>s.z;for(float variety:{0.f,.5f,1.f}){s.variety=variety;float best=0;std::vector<float>weight(n);for(int i=0;i<n;++i){weight[i]=Generator::weight(w[i],s);best=std::max(best,weight[i]);}std::cout<<"XYZ "<<p<<' '<<variety;for(int i=0;i<n;++i)if(weight[i]>=Generator::keepRatio(s)*best)std::cout<<' '<<i;std::cout<<'\n';}}
}
