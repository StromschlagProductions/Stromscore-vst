#include "TestSupport.h"
#include "ScoreEngine.h"
#include <cstring>
using namespace stromscore;
int main()
{
 CHECK(harmonyTemplates.size()==276&&kNumWendungen==48&&kNumPopWendungen==39);
 CHECK(kMaxWendungen==54&&kCustomWendung>=kMaxWendungen);
 CHECK(!findHarmonyTemplate(WendungId::custom)&&!findHarmonyTemplate(WendungId::invalid));
 for(const auto& h:harmonyTemplates)
 {
  CHECK(findHarmonyTemplate(h.id)==&h);CHECK(h.tonality.center==0&&(static_cast<unsigned>(h.id)>=2037||h.tonality.mode==composition::Mode::automatic));
  CHECK(h.sourceRef&&*h.sourceRef);int bars=0;
  for(int i=0;i<h.count;++i)bars+=h.chords[i].bars;CHECK(bars==8);
  for(int genre=0;genre<kNumGenres;++genre)
  {
   const auto projected=playbackTemplate(static_cast<int>(&h-harmonyTemplates.data()));const auto* w=&projected;CHECK(w->id==h.id&&std::strcmp(h.name,w->name)==0);CHECK(h.count==w->n&&h.x==w->x&&h.y==w->y&&h.z==w->z);
   for(int i=0;i<h.count;++i){auto a=h.chords[i],b=w->ch[i];CHECK(a.root==b.root&&a.type==b.type&&a.bars==b.bars&&a.bass==b.bass);}
  }
 }
 // Lookup and selection are allocation-free with the generated pool-sized scratch space.
 Settings s;Generator g;Transport t;t.playing=true;EventList es;
 for(int genre=0;genre<2;++genre){s.genre=genre;for(int v=0;v<4;++v){s.variety=v/3.f;int ids[kMaxWendungen];{NoAllocations guard;CHECK(Generator::candidates(s,ids,kMaxWendungen)>0);CHECK(Generator::pick(s,v)>=0);g.process(t,s,512,es);}}}
}
