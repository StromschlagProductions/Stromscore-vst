#include "TestSupport.h"
#include "ScoreEngine.h"
#include <set>
#include <iostream>
using namespace stromscore;
using namespace stromscore::composition;
int main()
{
 CHECK(templatePreferences.size()==225);std::set<WendungId> ids;
 for(const auto& p:templatePreferences){CHECK(ids.insert(p.id).second&&findWendung(p.id));for(float w:p.weights)CHECK(w>0&&std::isfinite(w));CHECK(p.weights[0]==1.f);}
 CHECK(wendungCount(GenreScore)==48&&wendungCount(GenreScore,ProfileId::johnBarry)==46);
 int different=0;
 for(auto profile:{ProfileId::neutral,ProfileId::johnBarry,ProfileId::bernardHerrmann})
 for(int x=0;x<=10;++x)for(int y=0;y<=10;++y)for(int z=0;z<=10;++z)for(float variety:{0.f,.5f,1.f})
 {
  Settings s;s.profile=profile;s.x=x/10.f;s.y=y/10.f;s.z=z/10.f;s.variety=variety;
  const float best=Generator::bestWeight(s);int candidates[kMaxWendungen];const int n=Generator::candidates(s,candidates,kMaxWendungen);CHECK(n>0);
  for(int salt=0;salt<8;++salt){const auto index=Generator::pick(s,salt);CHECK(index==Generator::pick(s,salt));CHECK(index>=0&&index<wendungCount(s.genre,profile));
   const auto& w=wendungAt(s.genre,index,profile);CHECK(Generator::weight(w,s)>=Generator::keepRatio(s)*best-1.e-8f);
   if(profile==ProfileId::johnBarry){s.profile=ProfileId::neutral;different+=w.id!=wendungAt(GenreScore,Generator::pick(s,salt)).id;s.profile=profile;}}
 }
 CHECK(different>1000);
 for(int i=0;i<46;++i){Settings s;s.profile=ProfileId::johnBarry;auto w=wendungAt(GenreScore,i,s.profile);CHECK(w.coloration==ChordColoration::protectedColor);s.x=w.x;s.y=w.y;s.z=w.z;s.variety=0;
  Generator g;Transport t;t.playing=true;EventList events;{NoAllocations guard;g.process(t,s,512,events);}CHECK(g.wendung()==i);CHECK(w.id==wendungAt(s.genre,Generator::pick(s,0),s.profile).id);}
 for(int i=0;i<kNumPopWendungen;++i)for(float variety:{0.f,.5f,1.f})for(int salt=0;salt<64;++salt){Settings s;s.genre=GenrePopRock;auto w=wendungAt(s.genre,i);s.x=w.x;s.y=w.y;s.z=w.z;s.variety=variety;const auto free=Generator::pick(s,salt);
  for(auto profile:{ProfileId::johnBarry,ProfileId::bernardHerrmann}){s.profile=profile;CHECK(Generator::pick(s,salt)==free);CHECK(&policyForContext(profile,false)==&neutralFreePolicy);}}
 // Shared material has one harmonic identity, independent score anchor/colour views.
 const auto* raw=findHarmonyTemplate(WendungId::scoreLauern);auto reused=wendungAt(GenreScore,wendungIndex(GenreScore,raw->id,ProfileId::johnBarry),ProfileId::johnBarry);
 CHECK(raw->coloration==ChordColoration::flexible&&reused.coloration==ChordColoration::protectedColor);
 CHECK(reused.ch[0].root==raw->chords[0].root&&reused.ch[0].type==raw->chords[0].type&&reused.ch[0].bars==8);
 std::cout<<"Profiles: actual catalog selection, XYZ eligibility, shared material and unchanged Pop pools passed\n";
}
