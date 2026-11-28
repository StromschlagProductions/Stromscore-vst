#include "TestSupport.h"
#include "ScoreEngine.h"
#include <memory>
using namespace stromscore;
int main()
{
 CHECK(harmonyTemplates.size()==340&&kNumPopWendungen==39&&kNumWendungen==48);
 const int roots[3][5]={{0,10,5,0,0},{0,5,0,5,10},{0,8,10}};
 const int types[3][5]={{Maj,Maj,Maj,Sus2,Maj},{Min7,Maj,Min7,Maj,Maj},{Fifth,Fifth,Fifth}};
 const int durations[3][5]={{2,2,2,1,1},{2,2,2,1,1},{6,1,1}};
 const int basses[3][5]={{0,10,9,0,0},{0,0,0,9,10},{0,8,10}};
 const float xyz[3][3]={{.75f,.5f,.3f},{.4f,.5f,.3f},{.15f,.9f,.2f}};
 for(int i=0;i<3;++i)
 {
  const auto id=static_cast<WendungId>(2037+i);const auto* h=findHarmonyTemplate(id);CHECK(h&&h->coloration==ChordColoration::protectedColor);
  CHECK(wendungAt(GenrePopRock,36+i).id==id&&wendungIndex(GenreScore,id)==-1);CHECK(h->x==xyz[i][0]&&h->y==xyz[i][1]&&h->z==xyz[i][2]);
  CHECK(h->count==(i==2?3:5));int length=0;
  for(int j=0;j<h->count;++j){auto c=h->chords[j];CHECK(c.root==roots[i][j]&&c.type==types[i][j]&&c.bars==durations[i][j]&&c.bass==basses[i][j]);length+=c.bars;}
  CHECK(length==8);CHECK(h->tonality.mode==(i==0?composition::Mode::mixolydian:i==1?composition::Mode::dorian:composition::Mode::automatic));
  for(int key=0;key<12;++key)
  {
   unsigned vocabulary=0;for(int j=0;j<h->count;++j){auto c=h->chords[j];for(int n=0;n<kShapes[c.type].n;++n)vocabulary|=composition::pitchBit(key+c.root+kShapes[c.type].iv[n]);vocabulary|=composition::pitchBit(key+c.bass);}
   auto context=composition::modalContext(vocabulary,key,true,h->tonality.mode);
   if(i<2){CHECK(context.status==composition::ModalStatus::unique&&context.mode==h->tonality.mode);CHECK(context.mask&composition::pitchBit(key+(i==0?10:9)));}
   else{CHECK(context.mode==composition::Mode::aeolian);/* Inference within the current four-mode set only, not an explicit modal claim. */}
  }
  for(const auto& profile:composition::compositionProfiles)CHECK(composition::harmonicPreference(profile.id,id)==1.f);
  for(int bars:{8,32,128})
  {
   auto g=std::make_unique<Generator>();Settings s;s.genre=GenrePopRock;s.x=h->x;s.y=h->y;s.z=h->z;s.variety=0;
   Transport t;t.playing=true;EventList es;int held[16][128]{};
   auto consume=[&]{CHECK(!es.overflow);for(int k=0;k<es.size;++k){auto e=es.events[k];if(e.type)continue;int& n=held[e.channel-1][e.note];if(e.velocity){CHECK(n==0);++n;}else{CHECK(n==1);--n;}}};
   for(long long at=0;at<bars*96000;at+=512){t.ppq=at/24000.;es.clear();{NoAllocations guard;g->process(t,s,512,es);}consume();CHECK(wendungAt(s.genre,g->wendung()).id==id);}
   Transport stop;es.clear();g->process(stop,s,512,es);consume();for(const auto& ch:held)for(int n:ch)CHECK(n==0);
  }
 }
 std::cout<<"Import definitions, 12-key modal facts, real automatic selection and no-allocation transport passed\n";
}
