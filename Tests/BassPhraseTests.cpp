#include "TestSupport.h"
#include "ScoreEngine.h"
#include <iostream>
using namespace stromscore;using namespace stromscore::composition;
static constexpr auto T(int64_t n){return musicaltime::fromGridStep(n);}
int main()
{
 for(int key=0;key<12;++key)
 {
  BassPhraseRequest r;r.begin=T(0);r.middle=T(32);r.end=T(64);r.bass={48+key,53+key};r.root={key,(key+5)%12};r.chords={pitchBit(key)|pitchBit(key+3)|pitchBit(key+7),pitchBit(key+5)|pitchBit(key+9)|pitchBit(key)};r.range={36+key,72+key};r.modal=modalContext(modalMask(Mode::dorian,key),key,true);
  BassPhrasePlan p;{NoAllocations guard;p=planBassPhrase(r);}CHECK(p.valid&&p.count>10);int passing=0;
  for(int i=0;i<p.count;++i){auto n=p.notes[i];CHECK(n.pitch>=r.range.low&&n.pitch<=r.range.high);if(n.at==T(0))CHECK(n.pitch==r.bass[0]);if(n.at==T(32))CHECK(n.pitch==r.bass[1]);if(i+1<p.count)CHECK(n.at+n.length<=p.notes[i+1].at);if(n.passing){++passing;CHECK(n.resolution==i+1);CHECK(std::abs(n.pitch-p.notes[i-1].pitch)<=2&&std::abs(p.notes[i+1].pitch-n.pitch)<=2);}else CHECK(r.chords[n.at>=T(32)?1:0]&pitchBit(n.pitch));}
  CHECK(passing==1);r.modal={};CHECK(!planBassPhrase(r).valid);r.modal=modalContext(modalMask(Mode::dorian,key),key,true);r.range={40,41};CHECK(!planBassPhrase(r).valid);
 }
 Settings s;s.genre=GenrePopRock;auto w=kPopWendungen[24];s.x=w.x;s.y=w.y;s.z=w.z;s.variety=0;s.key=0;s.solo[kBass]=true;s.policy.bass.opportunityEvery=1;
 Generator g;EventList es;Transport t;t.playing=true;BassPhrasePlan found;int lastPatternNotes=0;
 for(int tick=0;tick<128*16;++tick){t.ppq=tick*.25;es.clear();{NoAllocations guard;g.process(t,s,6000,es);}auto p=g.inspectBassPhrase();if(p.valid)found=p;for(int i=0;i<es.size;++i)if(es.events[i].out==OutBassShort&&es.events[i].velocity)++lastPatternNotes;}
 CHECK(found.valid&&lastPatternNotes>0);auto note=found.notes[0];CHECK(note.length>=T(2));
 for(int repeat=0;repeat<2;++repeat){t.ppq=musicaltime::toQuarters(note.at)+.0625;es.clear();g.process(t,s,1000,es);bool held=false;for(int i=0;i<es.size;++i)held|=es.events[i].out==OutBassShort&&es.events[i].velocity&&es.events[i].note==note.pitch;CHECK(held);t.ppq=0;es.clear();g.process(t,s,6000,es);}
 s.follow[kBass]=false;t.ppq=musicaltime::toQuarters(note.at);es.clear();g.process(t,s,6000,es);CHECK(!g.inspectBassPhrase().valid);
 s.follow[kBass]=true;s.bassPattern=BassFunk;t.ppq=0;g.process(t,s,6000,es);CHECK(!g.inspectBassPhrase().valid);
 Settings plain=s;plain.bassPattern=BassAuto;plain.y=w.y;
 Generator cold;t.ppq=musicaltime::toQuarters(note.at)+.0625;es.clear();cold.process(t,plain,1000,es);bool coldHeld=false;
 for(int i=0;i<es.size;++i)coldHeld|=es.events[i].out==OutBassShort&&es.events[i].velocity&&es.events[i].note==note.pitch;CHECK(coldHeld);
 Transport stop;es.clear();g.process(stop,plain,1000,es);t.ppq=musicaltime::toQuarters(note.at);es.clear();g.process(t,plain,6000,es);CHECK(g.inspectBassPhrase().valid);
 plain.y=.97f;es.clear();g.process(stop,plain,1000,es);es.clear();g.process(t,plain,6000,es);CHECK(!g.inspectBassPhrase().valid);
 std::cout<<"Bass phrase tests passed\n";
}
