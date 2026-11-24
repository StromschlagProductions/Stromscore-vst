#include "TestSupport.h"
#include "ScoreEngine.h"
#include <type_traits>
#include <set>
#include <vector>
using namespace stromscore;
using namespace stromscore::composition;
using namespace stromscore::musicaltime;
int main()
{
 static_assert(std::is_same<decltype(RememberedMotif::Note{}.at),Tick>::value);
 static_assert(std::is_same<decltype(MotifOccurrence{}.begin),Tick>::value);
 static_assert(std::is_same<decltype(MotifCapture{}.end),Tick>::value);
 // Identical score-observed and performance-captured content has one identity/unit.
 // Deliberately off-grid positions expose accidental divide/multiply adapters.
 RememberedMotif score;score.observe(60,Tick{37},Tick{481});score.observe(64,Tick{721},Tick{479});score.cycleLength=Tick{1440};score.finish();
 MotifCatalog catalog;MotifUse captured;MotifCapture capture;
 const Tick origin{1000000000037LL};
 {NoAllocations guard;
  capture.start(captured,origin,Tick{1440});
  capture.event(captured,60,64,origin+Tick{37});capture.event(captured,60,0,origin+Tick{518});
  capture.event(captured,64,64,origin+Tick{721});capture.event(captured,64,0,origin+Tick{1200});
  capture.finish(captured,catalog,origin+Tick{1440});}
 const auto& material=captured.material(catalog);
 CHECK(material.complete&&material.identity==score.identity&&captured.originTime==origin);
 for(int i=0;i<2;++i){auto n=replayMotifNote(material,i);CHECK(n.at==score.notes[i].at&&n.length==score.notes[i].length);}
 auto augmented=deriveMotif(score,MotifVariation::augmentation);
 CHECK(augmented.count==2&&augmented.notes[0].at==Tick{74}&&augmented.notes[0].length==Tick{962});
 CHECK(score.notes[0].at==Tick{37}&&score.notes[0].length==Tick{481});
 RememberedMotif odd;odd.observe(60,Tick{},fromGridStep(3));odd.observe(64,fromGridStep(4),fromGridStep(1));odd.finish();
 CHECK(deriveMotif(odd,MotifVariation::rhythm).notes[0].length==fromGridStep(1));
 MotifUse other;CHECK(other.adopt({captured.reference,9,origin+Tick{1440}},catalog));
 CHECK(&other.material(catalog)==&material&&other.originTime!=captured.originTime&&captured.introduction==0);
 // Genuine PPQ-only placements/answers, not roundtrips through sixteenth-note positions.
 for(int num:{3,5,7})
 {
  const auto bar=barLength(num,8),begin=origin+bar/4,window=8*bar;
  MotifRecurrencePolicy policy;RecurrenceSlot slot{true,1,1,false};
  MotifPlacement places[2]={{begin,60,0},{begin+bar,60,1}};
  auto occurrence=planRecurrence(policy,slot,begin,begin+window,bar/2,bar,places,2);
  CHECK(occurrence.active&&occurrence.begin==begin&&occurrence.end==begin+bar/2);
  auto answer=planDialogue(captured,catalog,occurrence,begin+bar,bar);
  CHECK(answer.answer&&answer.answerBegin==begin+bar&&answer.answerEnd==begin+2*bar);
  MotifCatalog handed;MotifUse lead;
  for(int i=0;i<3;++i)lead.observe(60+i*4,bar*i/4,bar/4,0,64,origin);
  lead.finish(handed);PlayingTrack target;target.id={5};target.roles=roleBit(MusicalRole::answer);
  target.instrument.pitch=PitchBehaviour::pitched;target.instrument.articulations=1;target.style=PlayingStyle::sustained;
  auto handoff=planMelodyHandoff(true,lead,handed,target,2,bar,window,policy,.7f,0,false);
  CHECK(handoff.active&&handoff.begin==bar&&handoff.end==bar+bar/2&&handoff.reference.originTime==origin+2*window);
  auto reservation=reserveMotifWindow({5},2,begin,occurrence.end);
  CHECK(reservation.contains(begin)&&reservation.contains(occurrence.end-Tick{1})&&!reservation.contains(occurrence.end));
  // End-to-end existing pattern realisation, capture and recurrence in eighth meters.
  for(int genre:{GenreScore,GenrePopRock})
  {
   Settings s;s.genre=genre;s.custom=true;s.customChords[0]={0,Maj7,8};s.meterNum=num;s.meterDen=8;
   s.key=0;s.y=.7f;s.z=0;s.motif=true;if(genre==GenrePopRock)s.policy.popHooks.phrasedCustom=true;s.solo[kGegenstimme]=true;
   Generator gen;EventList events;Transport host;host.playing=true;
   uint64_t identity=0;int returns=0;std::set<int64_t> starts;
   struct Emitted {Tick at;int pitch,velocity;};std::vector<Emitted> played;
   for(int k=0;k<128*Meter::from(num,8).len;++k)
   {
    host.ppq=k*.25;events.clear();{NoAllocations guard;gen.process(host,s,6000,events);}
    CHECK(!events.overflow);
    for(int i=0;i<events.size;++i){const auto& e=events.events[i];if(!e.type&&e.out==OutCounter)played.push_back({fromQuarters(host.ppq+e.offset/24000.),e.note,e.velocity});}
    const auto& m=gen.rememberedMotif();
    if(m.complete){if(!identity)identity=m.identity;CHECK(identity==m.identity);}
    const auto plan=gen.inspectMotifOccurrence(k,s);
    if(plan.active&&!plan.introduction){CHECK(plan.begin<=plan.end);if(starts.insert(plan.begin.value).second)++returns;CHECK(plan.figure.sourceIdentity==identity);}
   }
   std::cout<<"meter="<<num<<"/8 genre="<<genre<<" identity="<<identity<<" returns="<<returns<<"\n";CHECK(identity&&returns>0);
   auto saved=gen.rememberedMotif();
   if(genre==GenrePopRock)for(int i=0;i<saved.count;++i)
   {
    const auto n=replayMotifNote(saved,i);const auto start=gen.motifUse(OutCounter).originTime+n.at;
    auto on=std::find_if(played.begin(),played.end(),[&](const auto& e){return e.at==start&&e.pitch==n.pitch&&e.velocity==n.velocity;});CHECK(on!=played.end());
    auto off=std::find_if(std::next(on),played.end(),[&](const auto& e){return e.pitch==n.pitch&&!e.velocity;});CHECK(off!=played.end()&&off->at==start+n.length);
   }
   for(double ppq:{0.,3.25,0.,17.5}){host.ppq=ppq;events.clear();gen.process(host,s,6000,events);CHECK(gen.rememberedMotif().identity==saved.identity);}
   Transport stop;events.clear();gen.process(stop,s,512,events);host.ppq=0;events.clear();gen.process(host,s,6000,events);CHECK(!gen.rememberedMotif().complete);
  }
 }
 std::cout<<"Common motif PPQ identity, capture, transformations, odd-meter recurrence and answer tests passed\n";
}
