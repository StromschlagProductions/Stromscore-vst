#include "TestSupport.h"
#include "ScoreEngine.h"
#include <set>
#include <map>
#include <vector>
#include <chrono>
using namespace stromscore;
using namespace stromscore::composition;
struct Played {int pitch;musicaltime::Tick at,length;};
struct Result {RememberedMotif memory;std::vector<Played> notes;std::vector<int> velocities;int events=0;};
Result renderCell(Settings s,int output,int bars=9,int block=512,double bpm=120)
{
 Generator g;Transport t;t.playing=true;t.bpm=bpm;const double spq=48000.*60./bpm;EventList e;Result result;std::map<int,int> ledger;std::map<int,int64_t> begins;
 const int64_t total=std::llround(bars*s.meterNum*4./s.meterDen*spq);
 for(int64_t at=0;at<total;){const int n=static_cast<int>(std::min<int64_t>(block,total-at));t.ppq=at/spq;e.clear();{NoAllocations guard;g.process(t,s,n,e);}CHECK(!e.overflow);
  for(int i=0;i<e.size;++i){auto a=e.events[i];if(a.type)continue;int key=a.channel*128+a.note;
   if(a.velocity){CHECK(!ledger[key]);ledger[key]=1;}else{CHECK(ledger[key]);ledger[key]=0;}
   if(a.out!=output)continue;if(a.velocity)result.velocities.push_back(a.velocity);++result.events;auto sample=at+a.offset;
   if(a.velocity)begins[a.note]=sample;else if(begins.count(a.note)){const auto begin=begins[a.note];if(begin<2*s.meterNum*4./s.meterDen*spq)result.notes.push_back({a.note,musicaltime::fromQuarters(begin/spq),musicaltime::fromQuarters((sample-begin)/spq)});begins.erase(a.note);}}
  at+=n;
 }
 result.memory=g.rememberedMotif(output);t.playing=false;e.clear();g.process(t,s,1,e);for(int i=0;i<e.size;++i)if(!e.events[i].type&&!e.events[i].velocity)ledger[e.events[i].channel*128+e.events[i].note]=0;for(auto n:ledger)CHECK(!n.second);
 return result;
}
Settings settings(){Settings s;s.key=0;s.profile=ProfileId::johnBarry;s.policy=policyForContext(s.profile,true);s.custom=true;s.customChords[0]={0,MinMaj9,8};s.variety=0;s.melody=true;s.legato=s.melodyLegato=true;return s;}
int main()
{
 CHECK(std::size(barry::rhythms)==16&&std::size(barry::motifs)==20);
 CHECK(barry::chooseRhythm(.8f,.3f,.1f,4,4,8)==nullptr);
 CHECK(barry::chooseRhythm(1.f,0.f,1.f,4,4,8)==nullptr);
 // Real automatic harmony selection must reach the characteristic cells, not only custom fixtures.
 for(int id:{5,14,26})
 {
  const auto& source=*std::find_if(std::begin(barry::rhythms),std::end(barry::rhythms),[&](const auto& r){return r.id==id;});
  auto s=settings();s.custom=false;s.x=source.x;s.y=source.y;s.z=source.z;s.meterNum=source.num;s.meterDen=source.den;
  s.melody=false;s.motif=false;s.mute[kGegenstimme]=true;s.solo[kBass]=s.solo[kArp]=true;s.layerIntensity[kBass]=s.layerIntensity[kArp]=1;
  Generator g;Transport t;t.playing=true;EventList e;std::vector<int> actual,expected;
  for(int i=0;i<source.num*16/source.den*source.bars;++i)
  {if(source.movement[i]=='X'||source.movement[i]=='x')expected.push_back(i);t.ppq=i*.25;e.clear();g.process(t,s,6000,e);
   for(int n=0;n<e.size;++n)if(!e.events[n].type&&e.events[n].velocity&&e.events[n].out==OutArp)actual.push_back(i);}
  CHECK(actual==expected);
  for(double destination:{7.25,194.5})
  {
   Generator cold;Transport h;h.playing=true;h.ppq=destination;std::map<int,int> ledger;int ons=0;
   for(int block=0;block<400;++block){e.clear();{NoAllocations guard;cold.process(h,s,512,e);}CHECK(!e.overflow);h.ppq+=512/24000.;
    for(int n=0;n<e.size;++n){auto a=e.events[n];if(a.type)continue;const int key=a.channel*128+a.note;
     if(a.velocity){CHECK(!ledger[key]);ledger[key]=1;++ons;}else{CHECK(ledger[key]);ledger[key]=0;}}}
   h.playing=false;e.clear();cold.process(h,s,512,e);for(int n=0;n<e.size;++n)if(!e.events[n].type&&!e.events[n].velocity)ledger[e.events[n].channel*128+e.events[n].note]=0;
   for(auto v:ledger)CHECK(!v.second);CHECK(ons>0);
  }
 }
 // All 16 canonical rhythms are real selection winners; literal attacks/holds/rests.
 for(const auto& source:barry::rhythms)
 {
  auto s=settings();s.x=source.x;s.y=source.y;s.z=source.z;s.meterNum=source.num;s.meterDen=source.den;
  CHECK(barry::chooseRhythm(s.x,s.y,s.z,source.num,source.den,8)->id==source.id);
  s.motif=s.melodyMotif=false;s.melody=false;s.mute[kGegenstimme]=true;s.solo[kBass]=s.solo[kArp]=true;
  s.layerIntensity[kArp]=s.layerIntensity[kBass]=1;
  for(bool bass:{true,false})if(*(bass?source.bass:source.movement))
  {
   // Bass MIDI destinations follow articulation; combine the two through direct event inspection below.
   Generator g;Transport t;t.playing=true;EventList e;std::vector<int> actual,expected;std::map<int,int64_t> starts;
   int steps=source.num*16/source.den,total=steps*source.bars;
   for(int i=0;i<total;++i)if((bass?source.bass:source.movement)[i]=='X'||(bass?source.bass:source.movement)[i]=='x')expected.push_back(i);
   for(int step=0;step<total;++step){t.ppq=step*.25;e.clear();{NoAllocations guard;g.process(t,s,6000,e);}for(int i=0;i<e.size;++i){auto a=e.events[i];if(!a.type&&a.velocity&&(bass?(a.out==OutBassLong||a.out==OutBassShort):a.out==OutArp))actual.push_back(step);}}
   CHECK(actual==expected);
  }
 }
 // Every supported short source can be played intact on a suitable existing harmonic field.
 std::set<int> used;int conditional=0;
 for(const auto& source:barry::motifs)
 {
  bool found=false;
  for(auto type:{MinMaj7,MinMaj9,Min6,Add9,Maj7,Min7,Major7Sharp11,Maj,DiminishedTriad})
  {
   auto s=settings();s.x=source.x;s.y=source.y;s.z=source.z;s.customChords[0]={0,type,8};s.meterNum=source.num;s.meterDen=source.den;s.solo[kMelodie]=true;s.layerIntensity[kMelodie]=1;
   auto r=renderCell(s,OutMelody);
   if(r.memory.vocabularyId!=static_cast<uint32_t>(source.id))continue;
   std::cout<<"M"<<source.id<<" type "<<type<<" captured "<<r.memory.count<<"/"<<source.count<<" cycle "<<r.memory.cycleLength.value<<" complete "<<r.memory.complete<<'\n';
   CHECK(r.memory.complete&&r.memory.count==source.count&&r.memory.cycleLength==musicaltime::sixteenth*source.steps);
   CHECK(static_cast<int>(r.notes.size())==source.count);
   for(int i=0;i<source.count;++i){const auto& n=r.memory.notes[i];CHECK(n.at==musicaltime::sixteenth*source.at[i]);CHECK(n.length==musicaltime::sixteenth*source.lengths[i]);CHECK(n.interval==source.pitches[i]-source.pitches[0]);
    CHECK(r.notes[i].pitch==r.memory.origin+n.interval&&r.notes[i].at==n.at&&r.notes[i].length==n.length);}
   auto other=renderCell(s,OutMelody,9,127);CHECK(other.memory.identity==r.memory.identity&&other.events==r.events);
   for(int key=0;key<12;++key)for(int output:{OutMelody,OutCounter})
   {
    auto transposed=s;transposed.key=key;transposed.customChords[0].rootAbs=key;transposed.motif=true;
    transposed.rangeOn[kOutputRange[OutMelody]]=false;
    transposed.solo[kMelodie]=output==OutMelody;transposed.solo[kGegenstimme]=output==OutCounter;
    transposed.layerIntensity[kGegenstimme]=1;
    auto played=renderCell(transposed,output);if(played.memory.vocabularyId!=static_cast<uint32_t>(source.id))std::cerr<<"source "<<source.id<<" key "<<key<<" output "<<output<<" actual "<<played.memory.vocabularyId<<" count "<<played.memory.count<<'\n';CHECK(played.memory.vocabularyId==static_cast<uint32_t>(source.id));
    CHECK(played.memory.identity==r.memory.identity&&played.memory.count==source.count);
    if(source.id==19&&key==9&&output==OutMelody)
    {auto narrow=transposed;narrow.rangeOn[kOutputRange[OutMelody]]=true;narrow.rangeLo[6]=60;narrow.rangeHi[6]=84;CHECK(renderCell(narrow,output).memory.vocabularyId!=19);}
   }
   used.insert(source.id);found=true;break;
  }
  if(!found){std::cout<<"Not selected at its anchor on tested fields: M"<<source.id<<'\n';++conditional;}
 }
 CHECK(used.count(1)&&used.count(2)&&used.count(7)&&used.count(8)&&used.count(17));CHECK(conditional==0);
 auto s=settings();s.x=.2f;s.y=.45f;s.z=.4f;s.solo[kMelodie]=true;
 auto original=renderCell(s,OutMelody,128);CHECK(original.memory.complete&&original.memory.vocabularyId);
 auto initial=renderCell(s,OutMelody);CHECK(initial.memory.identity==original.memory.identity&&initial.memory.count==original.memory.count);
 auto lowered=s;lowered.octave[kMelodie]=-1;lowered.rangeOn[kOutputRange[OutMelody]]=false;const auto low=renderCell(lowered,OutMelody);
 CHECK(low.memory.origin==initial.memory.origin-12&&low.memory.identity==initial.memory.identity);
 auto detached=s;detached.melodyLegato=false;const auto separated=renderCell(detached,OutMelody);bool shorter=false;
 CHECK(separated.memory.vocabularyId==initial.memory.vocabularyId&&separated.memory.count==initial.memory.count);
 for(int i=0;i<initial.memory.count;++i)
 {const auto& a=initial.memory.notes[i];const auto& b=separated.memory.notes[i];CHECK(a.at==b.at&&a.interval==b.interval&&b.length<=a.length);shorter|=b.length<a.length;}
 CHECK(shorter);
 for(double bpm:{90.,173.})for(float swing:{0.f,.35f})
 {auto varied=s;varied.swing=swing;auto a=renderCell(varied,OutMelody,16,512,bpm);auto b=renderCell(varied,OutMelody,16,127,bpm);
  CHECK(a.memory.identity==original.memory.identity&&a.memory.identity==b.memory.identity&&a.events==b.events);}

 auto velocityCase=s;velocityCase.dynamics=false;const auto energy=renderCell(velocityCase,OutMelody,32);
 CHECK(energy.velocities.size()>static_cast<size_t>(energy.memory.count)&&energy.velocities[0]==energy.velocities[energy.memory.count]);
 CHECK(original.events>initial.events); // The common recurrence path really reuses the stored original.
 // Rewinding a learned low-register source must preserve the heard figure and gates.
 for(int output:{OutMelody,OutCounter})for(bool legato:{false,true})
 {
  auto loop=settings();loop.customChords[0]={0,Add9,8};loop.motif=true;loop.x=.85f;loop.y=.5f;loop.z=.2f;
  loop.solo[kMelodie]=output==OutMelody;loop.solo[kGegenstimme]=output==OutCounter;
  loop.layerIntensity[kMelodie]=loop.layerIntensity[kGegenstimme]=1;loop.melodyLegato=loop.legato=legato;
  Generator g;Transport h;h.playing=true;EventList events;
  using Gate=std::tuple<int,int,int,int>;
  auto window=[&](int steps){std::vector<Gate> heard;std::map<int,std::pair<int,int>> active;
   for(int step=0;step<steps;++step){h.ppq=step*.25;events.clear();{NoAllocations guard;g.process(h,loop,6000,events);}CHECK(!events.overflow);
    for(int i=0;i<events.size;++i){const auto e=events.events[i];if(e.type||e.out!=output)continue;const int at=step*6000+e.offset;
     if(e.velocity)active[e.note]={at,e.velocity};else if(active.count(e.note)){const auto begin=active[e.note];if(begin.first<32*6000)heard.emplace_back(e.note,begin.first,at-begin.first,begin.second);active.erase(e.note);}}}
   return heard;};
  const auto first=window(144);CHECK(g.rememberedMotif(output).vocabularyId==19&&g.rememberedMotif(output).complete);
  const auto again=window(33);CHECK(first.size()==6&&first==again);
  h.playing=false;events.clear();g.process(h,loop,1,events);
 }
 // Late activation starts inside M01; the first heard G must not become a new C-origin.
 s.customChords[0]={0,MinMaj7,8};Generator late;Transport host;host.playing=true;EventList e;std::vector<int> suffix;
 for(int step=0;step<144;++step){host.ppq=step*.25;s.mute[kMelodie]=step<4;e.clear();late.process(host,s,6000,e);
  for(int i=0;i<e.size;++i)if(step<16&&!e.events[i].type&&e.events[i].velocity&&e.events[i].out==OutMelody)suffix.push_back(e.events[i].note%12);}
 CHECK((suffix==std::vector<int>{7,11,7,3}));CHECK(late.rememberedMotif(OutMelody).count==4);
 s.melodyMotif=false;CHECK(!renderCell(s,OutMelody).memory.vocabularyId);
 s.melodyMotif=true;s.mute[kMelodie]=true;CHECK(renderCell(s,OutMelody).events==0);
 std::cout<<used.size()<<" actual initial motif sources and 16 coordinated rhythm sources passed\n";
}
