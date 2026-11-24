#include "TestSupport.h"
#include "ScoreEngine.h"
#include <memory>
#include <vector>
#include <tuple>
using namespace stromscore;using namespace stromscore::composition;
int main()
{
 ChordDispositionPolicy policy;CHECK(valid(policy));auto bad=policy;bad.maximumOpenSpan=12;CHECK(!valid(bad));
 int opens=0,reductions=0,expanded=0;
 for(int key=0;key<12;++key)for(int type=0;type<kNumChordTypes;++type)for(float y:{.2f,.8f})
 {
  const auto shape=kShapes[type];ChordIntent intent;intent.root=key;intent.bassPitchClass=key;intent.padLow=62;intent.bassLow=45;intent.intensity=y;intent.count=shape.n;
  for(int i=0;i<shape.n;++i)intent.intervals[i]=shape.iv[i];
  auto source=buildAnchor(intent,{36,100},true).pad;auto copy=source;
  for(auto mode:policy.cycle)
  {
   ChordDispositionRequest r;r.original=source;r.previous=source;r.root=key;r.bass=48+key;r.low=36;r.high=100;r.disposition=mode;
   for(int i=0;i<shape.n;++i){auto bit=static_cast<uint16_t>(1u<<((key+shape.iv[i])%12));r.chordMask|=bit;if(shape.iv[i]%12!=0&&shape.iv[i]%12!=7)r.required|=bit;}
   if(type==Fifth||type==Quartal)r.required=r.chordMask;
   ChordDispositionResult result;{NoAllocations guard;result=realizeChord(r,policy);}
   CHECK(source.n==copy.n);for(int i=0;i<source.n;++i)CHECK(source.notes[i]==copy.notes[i]);
   auto mask=dispositionMask(result.notes);CHECK(!(mask&~r.chordMask));CHECK((mask&r.required)==r.required);
   if(result.applied)
   {
    for(int i=0;i<result.notes.n;++i)CHECK(result.notes.notes[i]>=r.low&&result.notes.notes[i]<=r.high);
    if(mode.spacing==ChordSpacing::open){++opens;auto span=result.notes.notes[result.notes.n-1]-result.notes.notes[0];CHECK(span>=policy.minimumOpenSpan&&span<=policy.maximumOpenSpan);expanded+=span>source.notes[source.n-1]-source.notes[0];}
    if(mode.population==ChordPopulation::lean){CHECK(result.notes.n<=source.n);reductions+=result.notes.n<source.n;}
    if(type==Fifth)CHECK(mask==r.chordMask&&!(mask&(1u<<((key+3)%12)))&&!(mask&(1u<<((key+4)%12))));
   }
   r.bass=-1;auto noBass=realizeChord(r,policy);CHECK(dispositionMask(noBass.notes)&(1u<<key));
   r.low=60;r.high=60;r.previous={};auto impossible=realizeChord(r,policy);CHECK(!impossible.applied);
  }
 }
 CHECK(opens>0&&reductions>0&&expanded>0);
 // Sparse/full selection depends on the musical policy, not on an intensity threshold.
 Settings s;auto w=kPopWendungen[34];s.genre=GenrePopRock;s.x=w.x;s.y=w.y;s.z=w.z;s.variety=0;s.mute[kGegenstimme]=s.mute[kAkzent]=true;
 for(auto& d:s.policy.chords.cycle)d={ChordPopulation::lean,ChordSpacing::open};
 auto g=std::make_unique<Generator>();Transport t;t.playing=true;EventList es;std::vector<std::tuple<int,int,int>> first;
 for(int repetition=0;repetition<3;++repetition)
 {
  std::vector<std::tuple<int,int,int>> notes;
  for(int tick=0;tick<128;++tick){t.ppq=tick*.25;es.clear();{NoAllocations guard;g->process(t,s,6000,es);}for(int i=0;i<es.size;++i)if(es.events[i].out<2&&es.events[i].velocity)notes.emplace_back(tick,es.events[i].note,es.events[i].velocity);}
  if(!repetition)first=notes;else CHECK(first==notes);
 }
 CHECK(!first.empty());g->reset();t.ppq=0;es.clear();g->process(t,s,6000,es);CHECK(g->inspectChordDisposition().applied);
 // Held output reconstructs the same realized colour set at a cold seek.
 s.y=.2f;s.custom=true;s.customChords[0]={0,MinMaj9,8};s.padPattern=PadAuto;s.bassPattern=BassHeld;
 auto warm=std::make_unique<Generator>(),cold=std::make_unique<Generator>();t.ppq=0;es.clear();warm->process(t,s,6000,es);auto expected=warm->inspectChordDisposition();CHECK(expected.applied);
 t.ppq=1.125;es.clear();cold->process(t,s,1000,es);auto actual=cold->inspectChordDisposition();CHECK(actual.applied&&actual.notes.n==expected.notes.n);
 for(int i=0;i<actual.notes.n;++i)CHECK(actual.notes.notes[i]==expected.notes.notes[i]);
 std::cout<<"Chord disposition tests passed; "<<opens<<" open cases, "<<reductions<<" reductions, "<<expanded<<" wider cases\n";
}
