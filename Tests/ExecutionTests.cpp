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
 static void material(Generator& g)
 {
  auto& use=g.voice(OutMelody).motif;use.clear();
  use.observe(64,Tick{37},Tick{240},0,87,Tick{});
  use.observe(67,Tick{517},Tick{240},0,89,Tick{});use.finish(g.motifCatalog);
 }
 static int64_t recurrenceEpoch(const Generator& g,int output){return g.voice(output).recurrence.epoch;}
 static void section(Generator& g,Tick begin){g.wendungTime=begin;g.preparedTime.reset();}
 static bool changeAt(Generator& g,Tick at,const Settings& s){return g.isChangePoint(g.locate(at),s);}
 static Tick onset(Generator& g,Tick at,const Settings& s){g.cur=&s;auto result=g.nextOnset(at,s);g.cur=nullptr;return result;}

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
// Actual note starts, not just note ends, must be dispatched between stock cells.
std::vector<Row> fineStarts(int block,int numerator,float swing)
{
 Settings s;s.custom=true;s.customChords[0]={0,Maj7,8};s.key=0;s.y=.7f;
 s.melody=true;s.melodyMotif=true;s.melodyLegato=false;s.solo[kMelodie]=true;
 s.meterNum=numerator;s.meterDen=8;s.swing=swing;
 Generator g;EventList events;Transport t;t.playing=true;
 g.process(t,s,1,events);events.clear();g.allNotesOff(events,0);events.clear();ExecutionTestAccess::material(g);
 std::vector<Row> result;
 for(int at=1;at<30000;)
 {
  int count=std::min(block,30000-at);t.ppq=at/24000.;events.clear();
  {NoAllocations guard;g.process(t,s,count,events);}CHECK(!events.overflow);
  for(int i=0;i<events.size;++i){auto e=events.events[i];if(e.out==OutMelody&&!e.type)result.emplace_back(at+e.offset,e.out,e.channel,e.note,e.velocity,e.type);}
  at+=count;
 }
 CHECK(result.size()==4);
 CHECK(std::get<0>(result[0])==std::llround(execution::quarters(Tick{37},execution::Timing::groove,swing)*24000));
 CHECK(std::get<0>(result[2])==std::llround(execution::quarters(Tick{517},execution::Timing::groove,swing)*24000));
 CHECK(std::get<4>(result[0])>0&&std::get<4>(result[1])==0&&std::get<4>(result[2])>0&&std::get<4>(result[3])==0);
 return result;
}

std::vector<Row> anchoredArpeggio(int block,int numerator,float swing)
{
 Settings s;s.custom=true;s.customChords[0]={0,Maj7,8};s.key=0;s.y=.7f;
 s.solo[kArp]=true;s.arpFigure=ArpUp;s.arpRate=RateEighth;s.swing=swing;s.meterNum=numerator;s.meterDen=8;
 Generator g;EventList events;Transport t;t.playing=true;g.process(t,s,1,events);events.clear();g.allNotesOff(events,0);events.clear();
 ExecutionTestAccess::section(g,Tick{37});std::vector<Row> result;
 for(int at=1;at<30000;){int count=std::min(block,30000-at);t.ppq=at/24000.;events.clear();
  {NoAllocations guard;g.process(t,s,count,events);}CHECK(!events.overflow);
  for(int i=0;i<events.size;++i){auto e=events.events[i];if(e.out==OutArp&&!e.type)result.emplace_back(at+e.offset,e.out,e.channel,e.note,e.velocity,e.type);}at+=count;}
 int index=0;for(auto row:result)if(std::get<4>(row)>0)
 {CHECK(std::get<0>(row)==std::llround(execution::quarters(Tick{37}+2*sixteenth*index,execution::Timing::groove,swing)*24000));++index;}
 CHECK(index==3);return result;
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

 for(int numerator:{3,5,7})for(float swing:{0.f,.5f,1.f})
 {auto a=fineStarts(127,numerator,swing);CHECK(a==fineStarts(512,numerator,swing));CHECK(a==fineStarts(8192,numerator,swing));
  auto arp=anchoredArpeggio(127,numerator,swing);CHECK(arp==anchoredArpeggio(512,numerator,swing));CHECK(arp==anchoredArpeggio(8192,numerator,swing));}
 // Future onset previews must not commit recurrence decisions before nominal
 // harmonic preparation (for example an XYZ-driven Wendung switch at an epoch).
 {
  Settings s;s.custom=true;s.customChords[0]={0,Maj7,8};s.key=0;s.y=.7f;s.melody=true;s.melodyMotif=true;s.solo[kMelodie]=true;
  Generator g;EventList events;Transport t;t.playing=true;g.process(t,s,1,events);ExecutionTestAccess::material(g);
  const auto identity=g.rememberedMotif(OutMelody).identity;
  CHECK(ExecutionTestAccess::recurrenceEpoch(g,OutMelody)==-1);
  for(auto at:{8*barLength(4,4),16*barLength(4,4),8*barLength(4,4)})
   {ExecutionTestAccess::onset(g,at,s);CHECK(ExecutionTestAccess::recurrenceEpoch(g,OutMelody)==-1);CHECK(g.rememberedMotif(OutMelody).identity==identity);}
 }
 // A silent recurrence window is still a planning decision. Materialise it at
 // its own milestone without relying on an accompaniment/CC sixteenth callback.
 {
  Settings s;s.custom=true;s.customChords[0]={0,Maj7,8};s.key=0;s.y=.2f;s.melody=true;s.melodyMotif=true;s.solo[kMelodie]=true;
  s.policy.motif.sparseBelow=.9f;
  Generator g;EventList events;Transport t;t.playing=true;g.process(t,s,1,events);events.clear();g.allNotesOff(events,0);events.clear();ExecutionTestAccess::material(g);
  t.ppq=1/24000.;{NoAllocations guard;g.process(t,s,768000,events);}CHECK(!events.overflow);
  CHECK(ExecutionTestAccess::recurrenceEpoch(g,OutMelody)==1);
 }
 // An idle held texture has no sixteenth clock. Its next concrete rhythm source
 // is a section milestone; independent structural events still update harmony.
 {
  Settings s;s.custom=true;s.customChords[0]={0,Maj,8};s.padPattern=PadHeld;s.bassPattern=BassHeld;
  s.solo[kFlaeche]=s.solo[kBass]=true;s.y=.7f;
  Generator g;EventList events;Transport t;t.playing=true;g.process(t,s,1,events);
  CHECK(ExecutionTestAccess::onset(g,Tick{1},s)>quarter);
  CHECK(ExecutionTestAccess::changeAt(g,Tick{},s));
  CHECK(!ExecutionTestAccess::changeAt(g,Tick{37},s));
 }
 // Empty Score motif memory outside its introduction must schedule the already
 // existing local-line fallback. Cold starts on bars and between beats must not
 // wait until the next eight-bar phrase merely because the motif switch is on.
 for(int output:{OutCounter,OutMelody})for(double start:{12.,16.,16.5,20.,24.,28.})
 for(int block:{64,512,1024})for(float swing:{0.f,.5f})
 {
  Settings s;s.x=.5f;s.y=.7f;s.inertia=true;s.motif=true;s.melody=output==OutMelody;s.swing=swing;
  s.solo[kOutputLayer[output]]=true;
  Generator g;EventList events;Transport t;t.playing=true;t.ppq=start;
  int64_t first=-1;std::map<std::pair<int,int>,int> held;
  for(int at=0;at<48000;at+=block)
  {
   t.ppq=start+at/24000.;events.clear();{NoAllocations guard;g.process(t,s,std::min(block,48000-at),events);}CHECK(!events.overflow);
   for(int j=0;j<events.size;++j){const auto e=events.events[j];if(!e.type){auto& n=held[{e.channel,e.note}];if(e.velocity){CHECK(n==0);n=1;if(first<0)first=at+e.offset;}else{CHECK(n==1);n=0;}}}
  }
  CHECK(first>=0);
  if(!swing)CHECK(first==static_cast<int64_t>(start==16.5?36000:0));
  Transport stop;events.clear();g.process(stop,s,512,events);
  for(int j=0;j<events.size;++j){const auto e=events.events[j];if(!e.type&&!e.velocity)--held[{e.channel,e.note}];}
  for(const auto& pair:held)CHECK(pair.second==0);
  CHECK(!g.rememberedMotif(output).complete); // A local fallback must not invent stored motif material.
 }
 // The same fallback period belongs to its chord anchor in eighth-note meters;
 // it is not forced to the next bar/phrase or to an absolute sixteenth callback.
 for(int num:{3,5,7})for(int output:{OutCounter,OutMelody})for(float swing:{0.f,.5f})
 {
  Settings s;s.custom=true;s.customChords[0]={0,Maj7,8};s.key=0;s.x=.5f;s.y=.7f;s.inertia=true;
  s.motif=true;s.melody=output==OutMelody;s.solo[kOutputLayer[output]]=true;s.meterNum=num;s.meterDen=8;s.swing=swing;
  const double start=3*num*.5+.125;const auto period=sixteenth*std::max(4,num);
  const auto expected=execution::atOrAfter(musicaltime::fromQuarters(start),period);
  const auto sample=std::llround((execution::quarters(expected,execution::Timing::groove,swing)-start)*24000);
  for(int block:{64,512,1024})
  {
   Generator g;EventList events;Transport t;t.playing=true;int64_t reference=-1;
   for(int pass=0;pass<3;++pass) // cold, backwards seek/loop, then explicit scene restart
   {
    if(pass==2){events.clear();g.allNotesOff(events,0);g.reset();}int64_t first=-1;
    for(int at=0;at<48000;at+=block){t.ppq=start+at/24000.;events.clear();{NoAllocations guard;g.process(t,s,std::min(block,48000-at),events);}
     for(int j=0;j<events.size;++j){const auto e=events.events[j];if(!e.type&&e.velocity&&first<0)first=at+e.offset;}}
    CHECK(first==sample);if(pass==0)reference=first;else CHECK(first==reference);
   }
  }
 }
 // A 0.01-quarter jump is a real transport discontinuity, not host rounding.
 // Sub-sample host rounding must not cut a running note.
 for(auto test:std::array<std::pair<double,bool>,5>{{{.01,true},{-.01,true},{.000001,false},{.75/24000.,false},{1.5/24000.,true}}})
 {
  Settings s;s.y=.7f;Generator g;EventList events;Transport t;t.playing=true;
  g.process(t,s,1,events);events.clear();ExecutionTestAccess::claim(g,s,events,OutCounter,8*quarter,execution::Timing::groove,true);
  events.clear();t.ppq=1/24000.+test.first;g.process(t,s,1,events);bool off=false;
  for(int i=0;i<events.size;++i){const auto& e=events.events[i];off|=e.note==1&&!e.type&&!e.velocity&&e.offset==0;}
  CHECK(off==test.second);
 }
 // Between two musical onsets, ending requests are control events at their actual
 // host position. They do not wait for a universal subdivision callback.
 {
  Settings s;s.custom=true;s.customChords[0]={0,Maj,8};s.padPattern=PadHeld;s.bassPattern=BassHeld;s.y=.7f;s.ending=EndHard;
  Generator g;EventList events;Transport t;t.playing=true;g.process(t,s,925,events);
  events.clear();ExecutionTestAccess::claim(g,s,events,OutCounter,8*quarter,execution::Timing::groove,true);
  s.endRequested=true;t.ppq=37./960;events.clear();g.process(t,s,1,events);bool off=false;
  for(int i=0;i<events.size;++i){const auto& e=events.events[i];off|=e.note==1&&!e.type&&!e.velocity&&e.offset==0;}
  CHECK(off);CHECK(g.sceneOver());
 }
 // Revision between nominal preparation and delayed performance: mute is immediate;
 // unmute may enable a still-future groove onset, never a past one.
 for(bool initiallyMuted:{false,true})
 {
  Settings s;s.custom=true;s.customChords[0]={0,Maj,8};for(auto& mute:s.mute)mute=true;s.mute[kArp]=initiallyMuted;
  s.y=.7f;s.swing=.5f;s.arpFigure=ArpUp;s.arpRate=RateSixteenth;
  Generator g;EventList events;Transport t;t.playing=true;g.process(t,s,6600,events);
  s.mute[kArp]=!initiallyMuted;t.ppq=6600/24000.;events.clear();g.process(t,s,5400,events);
  int attacks=0;for(int i=0;i<events.size;++i){auto e=events.events[i];if(e.out==OutArp&&!e.type&&e.velocity)
   {++attacks;CHECK(6600+e.offset==std::llround(execution::quarters(Tick{240},execution::Timing::groove,s.swing)*24000));}}
  CHECK(attacks==(initiallyMuted?1:0));
 }
 // Cold chase of a continuous Pop hook must reconstruct a note that actually
 // sounds at the destination; a genuine rest must stay silent.
 for(int numerator:{3,5,7,4})for(float swing:{0.f,.5f})for(bool legato:{false,true})
 {
  Settings s;s.genre=GenrePopRock;s.custom=true;s.customChords[0]={0,Maj,8};s.key=0;s.y=.7f;s.swing=swing;s.legato=legato;
  s.meterNum=numerator;s.meterDen=numerator==4?4:8;s.solo[kGegenstimme]=true;
  Generator linear;EventList events;Transport t;t.playing=true;std::map<int,bool> sounding;
  const int destination=10250; // inside the first offbeat hook's gate or articulation gap
  for(int at=0;at<destination;){int count=std::min(127,destination-at);t.ppq=at/24000.;events.clear();linear.process(t,s,count,events);
   for(int i=0;i<events.size;++i){auto e=events.events[i];if(e.out==OutCounter&&!e.type)sounding[e.note]=e.velocity>0;}at+=count;}
  Generator cold;t.ppq=destination/24000.;events.clear();cold.process(t,s,1,events);std::map<int,bool> restored;
  for(int i=0;i<events.size;++i){auto e=events.events[i];if(e.out==OutCounter&&!e.type)restored[e.note]=e.velocity>0;}
  for(int note=0;note<128;++note)CHECK(sounding[note]==restored[note]);
 }
 // At an exact hook onset, a chased legato tail of the same physical key must
 // not steal the real attack's accent/velocity through same-time claim coalescing.
 for(int variation=1;variation<=16;++variation)
 {
  Settings s;s.genre=GenrePopRock;s.custom=true;s.customChords[0]={0,Maj,8};s.key=0;s.y=.7f;
  s.legato=true;s.variation=variation;s.solo[kGegenstimme]=true;
  Generator live;EventList events;Transport t;t.playing=true;live.process(t,s,12000,events);
  t.ppq=.5;events.clear();live.process(t,s,1,events);std::map<int,int> attacks;
  for(int i=0;i<events.size;++i){auto e=events.events[i];if(e.out==OutCounter&&!e.type&&e.velocity)attacks[e.note]=e.velocity;}
  CHECK(!attacks.empty());Generator cold;events.clear();cold.process(t,s,1,events);std::map<int,int> restored;
  for(int i=0;i<events.size;++i){auto e=events.events[i];if(e.out==OutCounter&&!e.type&&e.velocity)restored[e.note]=e.velocity;}
  for(auto attack:attacks)CHECK(restored[attack.first]==attack.second);
 }
 // The same stock producers reconstruct their actual gates across harmonic/bar
 // boundaries; no separate bass/arp/pad chase vocabulary is allowed.
 for(int numerator:{3,5,7,4})for(float swing:{0.f,.5f})for(int family=0;family<3;++family)
 for(int pattern=1;pattern<(family==0?static_cast<int>(kNumBassPatterns):family==1?static_cast<int>(kNumArpFigures):static_cast<int>(kNumPadPatterns));++pattern)
 {
  Settings s;s.custom=true;s.customChords[0]={0,Maj,1};s.customChords[1]={5,Min,1};s.key=0;s.y=.7f;s.z=.4f;s.swing=swing;
  s.meterNum=numerator;s.meterDen=numerator==4?4:8;s.mute[kGegenstimme]=true;
  const int layer=family==0?kBass:family==1?kArp:kFlaeche;s.solo[layer]=true;
  if(family==0)s.bassPattern=pattern;else if(family==1){s.arpFigure=pattern;s.arpRate=RateEighth;}else s.padPattern=pattern;
  const int destination=static_cast<int>(barLength(s.meterNum,s.meterDen).value*25+3101);
  Generator linear;EventList events;Transport t;t.playing=true;std::map<std::pair<int,int>,bool> held;
  for(int at=0;at<destination;){int count=std::min(127,destination-at);t.ppq=at/24000.;events.clear();linear.process(t,s,count,events);
   for(int i=0;i<events.size;++i){auto e=events.events[i];if(!e.type)held[{e.channel,e.note}]=e.velocity>0;}at+=count;}
  Generator cold;t.ppq=destination/24000.;events.clear();cold.process(t,s,1,events);std::map<std::pair<int,int>,bool> restored;
  for(int i=0;i<events.size;++i){auto e=events.events[i];if(!e.type)restored[{e.channel,e.note}]=e.velocity>0;}
  for(int channel=1;channel<=16;++channel)for(int note=0;note<128;++note)
   if(held[{channel,note}]!=restored[{channel,note}])
   {std::cerr<<"chase "<<numerator<<" "<<swing<<" "<<family<<" "<<pattern<<" "<<channel<<" "<<note<<"\n";CHECK(false);}
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
