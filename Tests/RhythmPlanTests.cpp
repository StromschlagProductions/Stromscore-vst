#include "TestSupport.h"
#include "ScoreEngine.h"
#include <iostream>
#include <memory>
#include <vector>
#include <tuple>
using namespace stromscore;using namespace stromscore::composition;
int main()
{
 RhythmCoordinationPolicy policy;CHECK(valid(policy));policy.everyBars=0;CHECK(!valid(policy));policy={};
 for(unsigned reference:{0x5555u,0x2929u,0x555fu})
 {
  RhythmPlanRequest r;r.reference=reference;r.movement=0x5555;r.bar=1;
  RhythmPlan p;{NoAllocations guard;p=planRhythmicInterlock(r,policy);}CHECK(p.active&&p.count==8);
  CHECK((p.coordinated&0x1111)==0x1111);
  for(int i=0;i<p.count;++i){auto n=p.notes[i];CHECK(n.at==n.source||n.at==n.source+1);if(n.at!=n.source)CHECK(n.source%4==2&&!(reference&(1u<<n.at)));CHECK(n.length>=1&&n.at+n.length<=16);if(i+1<p.count)CHECK(n.at+n.length<=p.notes[i+1].at);}
  r.bar=0;CHECK(!planRhythmicInterlock(r,policy).active);r.bar=1;r.minDuration=2;CHECK(!planRhythmicInterlock(r,policy).active);
 }
 RhythmPlanRequest r;r.reference=0xffff;r.movement=0x5555;r.bar=1;CHECK(!planRhythmicInterlock(r,policy).active);
 r.reference=0x5555;r.movement=0xffff;CHECK(!planRhythmicInterlock(r,policy).active);
 Settings s;const auto w=kPopWendungen[34];s.genre=GenrePopRock;s.x=w.x;s.y=w.y;s.z=w.z;s.variety=0;
 s.mute[kFlaeche]=s.mute[kGegenstimme]=s.mute[kAkzent]=true;
 for(int v=1;v<=16;++v)if((hash3(v,0,31)&1)==1&&(hash3(v,0,47)&1)==0){s.variation=v;break;}
 auto generator=std::make_unique<Generator>();auto& g=*generator;Transport t;t.playing=true;EventList es;int pitch=-1,velocity=-1;RhythmPlan observed;
 for(int k=0;k<32;++k){t.ppq=k*.25;es.clear();{NoAllocations guard;g.process(t,s,6000,es);}if(k==23){observed=g.inspectMovementRhythm(k,s);for(int i=0;i<es.size;++i)if(es.events[i].out==OutArp&&es.events[i].velocity){pitch=es.events[i].note;velocity=es.events[i].velocity;}}}
 CHECK(observed.active&&observed.at(23%16)&&pitch>=0);
 for(int pass=0;pass<3;++pass)
 {
  if(pass==2)g.reset();t.ppq=23.25*.25;es.clear();g.process(t,s,1000,es);bool held=false;
  for(int i=0;i<es.size;++i)held|=es.events[i].out==OutArp&&es.events[i].note==pitch&&es.events[i].velocity==velocity;CHECK(held);
  Transport stop;es.clear();g.process(stop,s,1000,es);
 }
 auto cold=std::make_unique<Generator>();t.ppq=23.25*.25;es.clear();cold->process(t,s,1000,es);bool held=false;
 for(int i=0;i<es.size;++i)held|=es.events[i].out==OutArp&&es.events[i].note==pitch&&es.events[i].velocity==velocity;CHECK(held);
 // A cold seek before a swung onset must wait for its real onset, not pre-trigger it.
 auto swung=s;swung.swing=.3f;auto swingGenerator=std::make_unique<Generator>();
 t.ppq=23.05*.25;es.clear();swingGenerator->process(t,swung,1000,es);bool delayed=false;
 for(int i=0;i<es.size;++i)if(es.events[i].out==OutArp&&es.events[i].velocity)
     {CHECK(es.events[i].offset>0);delayed=true;}
 CHECK(delayed);
 std::vector<std::tuple<int,int,int>> firstLoop;
 for(int repeat=0;repeat<3;++repeat)
 {
  std::vector<std::tuple<int,int,int>> notes;
  for(int tick=16;tick<32;++tick)
  {
   t.ppq=tick*.25;es.clear();g.process(t,s,6000,es);
   for(int i=0;i<es.size;++i)if(es.events[i].out==OutArp&&es.events[i].velocity)
       notes.emplace_back(tick,es.events[i].note,es.events[i].velocity);
  }
  if(repeat==0)firstLoop=notes;else CHECK(notes==firstLoop);
 }
 CHECK(firstLoop.size()==8);
 for(int test=0;test<5;++test)
 {
  auto control=s;if(test==0)control.arpFigure=ArpCircle;if(test==1)control.bassPattern=BassFunk;
  if(test==2)control.arpRate=RateEighth;if(test==3)control.mute[kBass]=true;if(test==4)control.policy.rhythm.enabled=false;
  auto q=std::make_unique<Generator>();t.ppq=4.;es.clear();q->process(t,control,6000,es);CHECK(!q->inspectMovementRhythm(23,control).active);
 }
 std::cout<<"Rhythmic interlock tests passed\n";
}
