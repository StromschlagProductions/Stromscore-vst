#include "TestSupport.h"
#include "ScoreEngine.h"
#include <map>
#include <vector>
using namespace stromscore;
using namespace stromscore::composition;
using namespace stromscore::musicaltime;
namespace stromscore {struct ExecutionTestAccess {
 static void debug(Generator& g,const Settings& s,Tick at){g.cur=&s;g.chasingPatterns=true;const auto plan=g.motifOccurrence(at,g.locate(at),s,OutMelody);std::cerr<<"plan "<<plan.active<<" intro "<<plan.introduction<<" begin "<<plan.begin.value<<" end "<<plan.end.value<<" fig "<<plan.figure.count<<" epoch "<<g.voice(OutMelody).recurrence.epoch<<" source "<<g.rememberedMotif(OutMelody).count<<" on "<<g.on[kMelodie]<<"\n";g.chasingPatterns=false;g.cur=nullptr;}
 static void continuation(Generator& g,Settings& s)
 {
  g.cur=&s;auto& use=g.voice(OutMelody).motif;use.clear();
  use.observe(60,{},quarter,0,90,{});use.observe(64,quarter,quarter,0,85,{});use.observe(67,2*quarter,quarter,0,85,{});use.finish(g.motifCatalog);
  const auto source=use.material(g.motifCatalog);const auto at=32*quarter;EventList out;
  g.allNotesOff(out,0);out.clear();g.nowTime=at;
  const auto first=g.motifOccurrence(at,g.locate(at),s,OutMelody);CHECK(first.active);
  g.motifStep(at,g.locate(at),s,0,out,OutMelody);CHECK(out.size>0&&out.events[out.size-1].note==60);
  g.custom.ch[0].root=5;g.custom.ch[0].type=Maj;
  const auto next=g.motifOccurrence(at+quarter/2,g.locate(at+quarter/2),s,OutMelody);
  CHECK(next.active&&next.begin==first.begin&&next.figure.sourceIdentity==source.identity);
  CHECK(next.base+next.figure.notes[0].interval==60);
  CHECK(next.base+next.figure.notes[1].interval==65&&next.base+next.figure.notes[2].interval==69);
  CHECK(use.material(g.motifCatalog).identity==source.identity&&use.material(g.motifCatalog).notes[1].interval==4);
  g.cur=nullptr;
 }
 static MotifRepriseProgress progress(const Generator& g,int output){return g.voice(output).reprise;}
};}
static void progressTests()
{
 RememberedMotif m;m.observe(60,{},quarter);m.observe(64,quarter,quarter);m.observe(67,2*quarter,quarter);m.finish();
 MotifOccurrence p;p.active=true;p.begin=16*quarter;p.end=p.begin+3*quarter;p.figure=deriveMotif(m,MotifVariation::original);
 MotifRepriseProgress first,second;
 first.observe(p,1,m.count);first.observe(p,2,m.count);CHECK(!first.establishedAt&&first.completed==0);
 first.observe(p,0,m.count);CHECK(first.establishedAt&&*first.establishedAt==p.end&&first.completed==1);
 first.observe(p,0,m.count);CHECK(first.completed==1&&!second.establishedAt);
 auto fragment=p;fragment.begin+=16*quarter;fragment.figure=deriveMotif(m,MotifVariation::fragment);
 for(int i=0;i<fragment.figure.count;++i)second.observe(fragment,i,m.count);
 CHECK(second.completed==1&&!second.establishedAt);
 CHECK(m.complete&&m.count==3&&m.notes[1].interval==4);
 // Continue the same immutable C-E-G thought over changed harmony: heard C stays
 // exactly C, while the unheard ending may become F-A. No accumulated re-variation.
 auto source=deriveMotif(m,MotifVariation::original);
 unsigned masks[10]={pitchBit(0),pitchBit(5),pitchBit(9)};Tick limits[10]={quarter,quarter,quarter};int fixed[10]={60,-1,-1};
 auto continuation=realizeScoreMotif(source,masks,limits,{60,84},quarter/4,8*quarter,60,fixed);
 CHECK(continuation.base>=0&&continuation.figure.harmonicallyAdapted);
 CHECK(continuation.base+continuation.figure.notes[0].interval==60);
 CHECK(continuation.base+continuation.figure.notes[1].interval==65);
 CHECK(continuation.base+continuation.figure.notes[2].interval==69);
 CHECK(m.notes[1].interval==4&&m.notes[2].interval==7);
 fixed[0]=72;CHECK(realizeScoreMotif(source,masks,limits,{60,69},quarter/4,8*quarter,60,fixed).base<0);
 const int contour[]={7,6,4,5,7};
 for(int size:{2,3,5,8})
 {
  int low=128,high=-1;
  for(int i=0;i<5;++i){auto d=fittedMotifDegree(contour,5,i,size);CHECK(d>=0&&d<size);low=std::min(low,d);high=std::max(high,d);}
  CHECK(low<high);
  if(size>=4)for(int i=1;i<5;++i)CHECK(fittedMotifDegree(contour,5,i,size)-fittedMotifDegree(contour,5,i-1,size)==contour[i]-contour[i-1]);
 }
 CHECK(fittedMotifDegree(contour,5,2,1)==0);
}
static void earlyReprise(int genre,ProfileId profile)
{
 Settings s;s.genre=genre;s.profile=profile;s.policy=policyForContext(profile,genre==GenreScore);
 s.custom=true;s.customChords[0]={0,Maj7,8};s.key=0;s.y=.85f;s.z=.4f;s.melody=true;s.solo[kMelodie]=true;
 s.scene=false;s.sceneBars=0;s.drive=false;
 Generator g;EventList events;Transport host;host.playing=true;
 RememberedMotif original;MotifRepriseProgress heard;const auto bar=4*quarter;
 std::map<std::pair<int,int>,bool> ledger;
 for(int k=0;k<32*16;++k)
 {
  host.ppq=k*.25;events.clear();{NoAllocations guard;g.process(host,s,6000,events);}CHECK(!events.overflow);
  for(int i=0;i<events.size;++i)
  {auto e=events.events[i];if(e.type)continue;auto key=std::make_pair(e.channel,e.note);if(e.velocity){CHECK(!ledger[key]);ledger[key]=true;}else{CHECK(ledger[key]);ledger[key]=false;}}
  auto memory=g.rememberedMotif(OutMelody);if(memory.complete){if(!original.complete)original=memory;CHECK(original.identity==memory.identity);}
  if(k==36)CHECK(original.complete); // Published at the introduction boundary, even before a later reprise.
  auto p=ExecutionTestAccess::progress(g,OutMelody);
  if(!heard.establishedAt&&p.establishedAt)heard=p;
  auto plan=g.inspectMotifOccurrence(k,s,OutMelody);
  if(plan.active&&plan.figure.count&&plan.figure.variation!=MotifVariation::original)
  {CHECK(p.establishedAt&&musicaltime::fromGridStep(k)>=*p.establishedAt);}
 }
 CHECK(original.complete&&heard.establishedAt&&heard.completed>0);
 Tick span{};for(int i=0;i<original.count;++i)span=std::max(span,original.notes[i].at+original.notes[i].length);
 CHECK(heard.begin>=span+2*bar&&heard.begin<8*bar);
 CHECK(heard.end-heard.begin==span);
 // Warm seek/loop must reconstruct a past established figure, not move it ahead of the cursor.
 for(int visit=0;visit<2;++visit)
 {
  host.ppq=musicaltime::toQuarters(heard.begin+quarter/4);events.clear();
  {NoAllocations guard;g.process(host,s,512,events);}
  bool found=false;for(int i=0;i<events.size;++i){auto e=events.events[i];if(e.out==OutMelody&&e.type==0&&e.velocity)found=true;}
  if(!found)ExecutionTestAccess::debug(g,s,heard.begin+quarter/4);
  if(!found)std::cerr<<"seek failure genre="<<genre<<" profile="<<int(profile)<<" begin="<<heard.begin.value<<" end="<<heard.end.value<<" count="<<original.count<<" on="<<g.rememberedMotif(OutMelody).complete<<" events="<<events.size<<"\n";
  CHECK(found);
  host.ppq=0;events.clear();g.process(host,s,512,events);
 }
 host.playing=false;events.clear();g.process(host,s,512,events);
 for(int i=0;i<events.size;++i){auto e=events.events[i];if(!e.type)ledger[{e.channel,e.note}]=false;}
 for(auto x:ledger)CHECK(!x.second);
 // Restart creates a fresh per-voice use, not a remembered future establishment.
 host.playing=true;host.ppq=0;events.clear();g.process(host,s,6000,events);
 CHECK(!ExecutionTestAccess::progress(g,OutMelody).establishedAt);
}
int main()
{
 {NoAllocations guard;progressTests();}
 {
  Settings s;s.custom=true;s.customChords[0]={0,Maj7,8};s.key=0;s.y=.85f;s.melody=true;s.solo[kMelodie]=true;
  Generator g;EventList events;Transport host;host.playing=true;g.process(host,s,1,events);
  {NoAllocations guard;ExecutionTestAccess::continuation(g,s);}
 }
 earlyReprise(GenreScore,ProfileId::neutral);earlyReprise(GenreScore,ProfileId::johnBarry);earlyReprise(GenrePopRock,ProfileId::neutral);
 std::cout<<"Actual complete reprise before variations; independent evidence, whole contours and unlimited restart passed\n";
}
