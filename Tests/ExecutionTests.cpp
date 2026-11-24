#include "TestSupport.h"
#include "ScoreEngine.h"
#include <vector>
#include <tuple>
#include <map>
using namespace stromscore;
using namespace stromscore::musicaltime;
namespace stromscore
{
// Only the copied offline test header grants access; not part of the plugin API.
struct ExecutionTestAccess
{
 static void claim(Generator& g,const Settings& s,EventList& out,int output,Tick end,execution::Timing domain,bool first)
 {
  g.cur=&s;g.forceOn=true;g.currentTiming=domain;g.nowTime={};g.currentPerformanceQuarter=0;
  if(first)++g.dispatchIdentity;
  g.noteOn(output,1,91,end,0,out);g.forceOn=false;g.cur=nullptr;
 }
 static void endScene(Generator& g,Tick end){g.manualEndTime=end;g.sceneEndTime=end;}
};
}
using Row=std::tuple<int64_t,int,int,int,int,int>;
std::vector<Row> deadline(int block,float swing,bool shared,bool scene)
{
 Settings s;s.y=.7f;s.swing=swing;s.melody=false;s.scene=false;s.ending=EndFade;
 s.channel[OutCounter]=s.channel[OutPadLong];
 Generator g;EventList events;Transport t;t.playing=true;
 std::vector<Row> result;
 auto emit=[&](int64_t at){for(int i=0;i<events.size;++i){auto e=events.events[i];if(e.type==0&&e.note==1)result.emplace_back(at+e.offset,e.out,e.channel,e.note,e.velocity,e.type);}};
 g.process(t,s,1,events);events.clear();
 ExecutionTestAccess::claim(g,s,events,OutCounter,Tick{53},execution::Timing::groove,true);
 if(shared)ExecutionTestAccess::claim(g,s,events,OutPadLong,Tick{37},execution::Timing::nominal,false);
 if(scene)ExecutionTestAccess::endScene(g,Tick{37});emit(0);
 for(int at=1;at<12000;)
 {
  const int size=std::min(block,12000-at);t.ppq=at/24000.;events.clear();
  {NoAllocations guard;g.process(t,s,size,events);}CHECK(!events.overflow);emit(at);at+=size;
 }
 CHECK(result.size()==2&&std::get<4>(result[0])>0&&std::get<4>(result[1])==0);
 const auto expected=scene?925:std::llround(execution::quarters(Tick{53},execution::Timing::groove,swing)*24000);
 CHECK(std::get<0>(result[1])==expected);
 return result;
}
int main()
{
 for(float swing:{0.f,.3f,1.f})for(int num=1;num<=16;++num)for(int den:{1,2,4,8,16})
 {
  const auto bar=barLength(num,den);
  CHECK(execution::quarters(bar,execution::Timing::nominal,swing)==toQuarters(bar));
  // Old supported rhythmic cells keep their exact floating-point mapping.
  for(int k=0;k<64;++k)
  {
   const double delay=(k%4==2?.667:k%4==1||k%4==3?.333:0)*swing;
   CHECK(execution::quarters(sixteenth*k,execution::Timing::groove,swing)==(k+delay)*.25);
  }
 }
 for(float swing:{0.f,.3f,1.f})
 {
  double previous=-1e10;
  for(int64_t at=-960;at<=1920;++at)
  {
   const auto q=execution::quarters(Tick{at},execution::Timing::groove,swing);CHECK(q>previous);previous=q;
   auto inverse=execution::nominalAt(q,execution::Timing::groove,swing);CHECK(std::abs(inverse.value-at)<=1);
  }
  auto release=execution::Candidate{Tick{37},execution::Timing::nominal,execution::Kind::release,true};
  auto boundary=execution::Candidate{Tick{37},execution::Timing::nominal,execution::Kind::planning,true};
  CHECK(execution::first(boundary,release,swing).kind==execution::Kind::release);
  for(bool shared:{false,true})for(bool scene:{false,true})
  {auto a=deadline(127,swing,shared,scene);CHECK(a==deadline(512,swing,shared,scene));CHECK(a==deadline(8192,swing,shared,scene));}
 }
 // Real held harmony must enter on odd-meter boundaries even when the coincident
 // rhythmic pulse has a delayed performance time.
 for(int num=1;num<=16;++num)for(int den:{1,2,4,8,16})for(float swing:{.3f,1.f})
 {
  Settings s;s.custom=true;s.customChords[0]={0,Maj,1};s.customChords[1]={5,Min,1};s.padPattern=PadHeld;
  s.bassPattern=BassHeld;s.meterNum=num;s.meterDen=den;s.swing=swing;s.y=.8f;s.z=0;s.solo[kFlaeche]=s.solo[kBass]=true;
  Generator g;EventList events;Transport t;t.playing=true;const int64_t bar=barLength(num,den).value*25;
  std::map<std::pair<int,int>,bool> held;int bass=0;
  for(int64_t at=0;at<4*bar;)
  {
   const int size=static_cast<int>(std::min<int64_t>(512,4*bar-at));t.ppq=at/24000.;events.clear();{NoAllocations guard;g.process(t,s,size,events);}
   for(int i=0;i<events.size;++i){auto e=events.events[i];if(e.type)continue;auto key=std::make_pair(e.channel,e.note);
    if(e.velocity){CHECK(!held[key]);held[key]=true;}else{CHECK(held[key]);held[key]=false;}
    if(e.out==OutBassLong&&e.velocity){CHECK((at+e.offset)%bar==0);++bass;}}
   at+=size;
  }
  CHECK(bass==4);Transport stop;events.clear();g.process(stop,s,127,events);
  for(int i=0;i<events.size;++i){auto e=events.events[i];if(!e.type&&!e.velocity)held[std::make_pair(e.channel,e.note)]=false;}
  for(auto item:held)CHECK(!item.second);
 }
 // Chase uses the inverse performance mapping: before a delayed onset the previous
 // motif note remains sounding; afterwards the actual new motif note is reconstructed.
 {
  Settings s;s.custom=true;s.customChords[0]={0,Maj7,8};s.key=0;s.y=.7f;s.seed=3;s.swing=.5f;
  s.melody=true;s.melodyMotif=true;s.melodyLegato=true;s.solo[kMelodie]=true;
  Generator g;EventList events;Transport host;host.playing=true;
  composition::RememberedMotif material;int chosen=-1;
  for(int seed=1;seed<=64&&chosen<0;++seed)
  {
   g.reset();s.seed=seed;
   for(int k=0;k<40;++k){host.ppq=k*.25;events.clear();g.process(host,s,6000,events);}
   material=g.rememberedMotif(OutMelody);CHECK(material.complete);
   for(int i=1;i<material.count;++i)if(material.notes[i].at%quarter!=Tick{}&&material.notes[i].interval!=material.notes[i-1].interval){chosen=i;break;}
  }
  CHECK(chosen>0);const auto note=material.notes[chosen];
  const double nominal=toQuarters(note.at),performed=execution::quarters(note.at,execution::Timing::groove,s.swing);
  CHECK(performed>nominal);
  for(int repeat=0;repeat<2;++repeat)
  {
   host.ppq=(nominal+performed)/2;events.clear();g.process(host,s,1,events);bool previous=false;
   for(int i=0;i<events.size;++i){auto e=events.events[i];if(e.out==OutMelody&&e.velocity){CHECK(e.note!=material.origin+note.interval);previous|=e.note==material.origin+material.notes[chosen-1].interval;}}
   CHECK(previous);
   host.ppq=performed+.05;events.clear();g.process(host,s,1,events);bool found=false;
   for(int i=0;i<events.size;++i){auto e=events.events[i];found|=e.out==OutMelody&&e.velocity&&e.note==material.origin+note.interval;}
   CHECK(found);CHECK(g.rememberedMotif(OutMelody).identity==material.identity);
   host.ppq=0;events.clear();g.process(host,s,1,events);
  }
 }
 std::cout<<"Independent nominal/groove/deadline execution, fine releases and shared claims passed\n";
}
