#include "TestSupport.h"
#include "ScoreEngine.h"
#include <iostream>
#include <set>
using namespace stromscore;
int main()
{
 Settings s;s.motif=true;s.genre=GenrePopRock;const auto& w=kPopWendungen[33];s.x=w.x;s.y=w.y;s.z=w.z;s.variety=0;s.key=0;s.solo[kGegenstimme]=true;
 // Controlled harmony makes both original and sequence musically eligible;
 // a mixed catalog template need not admit a complete original before sequencing.
 s.custom=true;s.customChords[0]={0,Maj7,8};s.policy.popHooks.phrasedCustom=true;
 Generator g;EventList es;Transport t;t.playing=true;std::array<composition::MotifOccurrence,2> examples {};uint64_t identity=0;
 for(int tick=0;tick<128*16;++tick)
 {
  t.ppq=tick*.25;es.clear();{NoAllocations guard;g.process(t,s,6000,es);}const auto& m=g.rememberedMotif();if(m.complete){if(!identity)identity=m.identity;CHECK(identity==m.identity);}
  auto plan=g.inspectMotifOccurrence(tick,s);if(plan.active&&!plan.introduction){CHECK(plan.figure.variation==composition::MotifVariation::original||plan.figure.variation==composition::MotifVariation::sequence);examples[plan.figure.variation==composition::MotifVariation::sequence?1:0]=plan;}
 }
 CHECK(identity&&examples[0].active&&examples[1].active);
 for(auto plan:examples)
 {
  auto note=plan.figure.notes[0];for(int repeat=0;repeat<2;++repeat){t.ppq=musicaltime::toQuarters(plan.begin+note.at+musicaltime::fromGridStep(1));es.clear();g.process(t,s,6000,es);bool found=false;for(int i=0;i<es.size;++i){auto e=es.events[i];if(e.out==OutCounter&&e.velocity){CHECK(e.note==plan.base+note.interval);found=true;}}CHECK(found);t.ppq=0;es.clear();g.process(t,s,6000,es);CHECK(g.rememberedMotif().identity==identity);}
 }
 std::cout<<"Hook development tests passed\n";
}
