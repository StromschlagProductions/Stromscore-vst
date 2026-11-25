#include "TestSupport.h"
#include "ScoreEngine.h"
using namespace stromscore;
using namespace stromscore::musicaltime;
namespace stromscore { struct ExecutionTestAccess {
 static void timeline(Generator& g,Settings& s)
 {
  g.cur=&s;const auto bar=barLength(s.meterNum,s.meterDen);
  for(bool held:{false,true})for(int first:{0,1})for(bool passing:{false,true})
  {
   s.passing=passing;g.still=held;g.chordBase=first;g.wendungTime=bar+quarter/2;
   for(auto at=g.wendungTime;at<8*bar;at+=quarter/4)
   {
    const auto p=g.locate(at);const auto actual=g.chordFor(p,kMelodie,s);const auto forecast=g.motifHarmonyAt(at,s);
    CHECK(actual.root==forecast.chord.root&&actual.type==forecast.chord.type&&p.chordEndTime==forecast.end);
   }
  }
 }
 static void cache(Generator& g,Settings& s)
 {
  g.cur=&s;g.still=false;g.chordBase=0;g.wendungTime={};
  auto& use=g.voice(OutMelody).motif;use.clear();
  use.observe(60,{},quarter,0,90,{});use.observe(64,quarter,quarter,0,85,{});use.observe(67,2*quarter,quarter,0,85,{});use.finish(g.motifCatalog);
  const auto bar=barLength(s.meterNum,s.meterDen);const auto at=8*bar;
  auto plan=g.motifOccurrence(at,g.locate(at),s,OutMelody);CHECK(plan.active);
  const auto key=g.voice(OutMelody).recurrence.harmony;
  // A preflight is read-only, including after a mid-phrase restart of the same template.
  g.wendungTime=at+bar;
  auto preview=g.motifOccurrence(at+bar,g.locate(at+bar),s,OutMelody,true);
  CHECK(g.voice(OutMelody).recurrence.harmony==key);
  auto revised=g.motifOccurrence(at+bar,g.locate(at+bar),s,OutMelody);
  CHECK(g.voice(OutMelody).recurrence.harmony!=key);
  CHECK(!revised.active||revised.begin>=at+bar);
  if(revised.active){CHECK(revised.begin==preview.begin);CHECK(g.remainingMotifFits(revised,revised.begin,s,OutMelody));}
  // An already played prefix must not be replanned/retriggered in the same horizon.
  auto& cached=g.voice(OutMelody).recurrence;cached.plan=plan;cached.started=true;
  g.custom.ch[0].root=6;g.custom.ch[0].type=Maj;g.wendungTime=at+quarter/2;
  auto cancelled=g.motifOccurrence(at+quarter/2,g.locate(at+quarter/2),s,OutMelody);
  CHECK(!cancelled.active);
  CHECK(!g.motifOccurrence(at+quarter,g.locate(at+quarter),s,OutMelody).active);
 }
}; }
int main()
{
 for(int num:{3,4,5,7})for(int den:{4,8})
 {
  Settings s;s.custom=true;s.customChords[0]={0,Maj7,2};s.customChords[1]={5,Min7,2};s.customChords[2]={7,Dom7,4};
  s.key=0;s.y=.85f;s.melody=true;s.solo[kMelodie]=true;s.meterNum=num;s.meterDen=den;
  Generator g;EventList events;Transport host;host.playing=true;
  {NoAllocations guard;g.process(host,s,1,events);ExecutionTestAccess::timeline(g,s);}
 }
 Settings s;s.custom=true;s.customChords[0]={0,Maj7,8};s.key=0;s.y=.85f;s.melody=true;s.solo[kMelodie]=true;
 Generator g;EventList events;Transport host;host.playing=true;g.process(host,s,1,events);
 {NoAllocations guard;ExecutionTestAccess::cache(g,s);}
 std::cout<<"Motif harmony matches actual timeline; revised/failing/started caches and read-only preflight passed\n";
}
