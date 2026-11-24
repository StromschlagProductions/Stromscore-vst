#include "TestSupport.h"
#include "ScoreEngine.h"
#include <iostream>
using namespace stromscore;using namespace stromscore::composition;
ModalContext contextFor(const Wendung& w,int key){unsigned mask=0;bool tonic=false;for(int i=0;i<w.n;++i){auto c=w.ch[i];tonic|=c.root==0;for(int j=0;j<kShapes[c.type].n;++j)mask|=pitchBit(key+c.root+kShapes[c.type].iv[j]);if(c.bass>=0)mask|=pitchBit(key+c.bass);}return modalContext(mask,key,tonic);}
int main()
{
 for(int key=0;key<12;++key)
 {
  for(int mode=1;mode<=4;++mode){auto m=static_cast<Mode>(mode);auto mask=modalMask(m,key);auto c=modalContext(mask,key,true);CHECK(c.status==ModalStatus::unique&&c.mode==m);int bits=0;for(int n=0;n<12;++n)bits+=(mask>>n)&1u;CHECK(bits==7);PassingRequest passing;passing.context=c;passing.root=key;passing.source=60+key;passing.target=60+key+(mode<=2?4:3);passing.chordMask=pitchBit(key)|pitchBit(passing.target)|pitchBit(key+7);passing.targetAt=8;passing.harmonyEnd=16;auto note=planPassingTone(passing);CHECK(note.valid&&note.pitch==62+key);}
  CHECK(contextFor(kPopWendungen[14],key).mode==Mode::mixolydian);CHECK(contextFor(kPopWendungen[18],key).mode==Mode::mixolydian);
  CHECK(contextFor(kPopWendungen[11],key).mode==Mode::dorian);CHECK(contextFor(kPopWendungen[24],key).mode==Mode::dorian);
  CHECK(contextFor(kPopWendungen[16],key).status==ModalStatus::ambiguous);
  CHECK(contextFor(kPopWendungen[0],key).status==ModalStatus::incompatible);
  CHECK(contextFor(kPopWendungen[28],key).status==ModalStatus::incompatible);
  CHECK(modalContext(modalMask(Mode::ionian,key),key,true,Mode::mixolydian).status==ModalStatus::incompatible);
  CHECK(modalContext(pitchBit(key)|pitchBit(key+4)|pitchBit(key+7),key,true).status==ModalStatus::ambiguous);
  CHECK(modalContext(pitchBit(key)|pitchBit(key+4)|pitchBit(key+7),key,false,Mode::ionian).status==ModalStatus::unique);
  PassingRequest r;r.context=modalContext(modalMask(Mode::ionian,key),key,true);r.root=key;r.chordMask=pitchBit(key)|pitchBit(key+4)|pitchBit(key+7);
  r.source=60+key;r.target=64+key;r.sourceAt=0;r.targetAt=8;r.harmonyEnd=16;
  auto p=planPassingTone(r);CHECK(p.valid&&p.pitch==62+key&&p.end==8&&p.begin==6);
  r.source=67+key;r.target=64+key;p=planPassingTone(r);CHECK(p.valid&&p.pitch==65+key);
  r.bassPitchClass=key+4;CHECK(!planPassingTone(r).valid);r.bassPitchClass=-1;
  r.source=64+key;r.target=67+key;CHECK(!planPassingTone(r).valid); // F would conflict with the non-resolving E.
  r.source=60+key;r.target=64+key;r.high=61+key;CHECK(!planPassingTone(r).valid);r.high=127;r.harmonyEnd=8;CHECK(!planPassingTone(r).valid);
  r.harmonyEnd=16;r.targetAt=1;CHECK(!planPassingTone(r).valid);
  r.targetAt=8;r.source=69+key;r.target=72+key;r.chordMask=pitchBit(key)|pitchBit(key+4)|pitchBit(key+7)|pitchBit(key+9);CHECK(!planPassingTone(r).valid);
  r.context=modalContext(modalMask(Mode::aeolian,key),key,true);r.source=62+key;r.target=65+key;r.chordMask=pitchBit(key)|pitchBit(key+2)|pitchBit(key+5)|pitchBit(key+7);CHECK(!planPassingTone(r).valid);
  r.source=r.target;CHECK(!planPassingTone(r).valid);
  r.source=71+key;r.target=74+key;r.chordMask=pitchBit(r.source)|pitchBit(r.target);CHECK(!planPassingTone(r).valid);
 }
 Settings s;s.genre=GenrePopRock;auto w=kPopWendungen[34];s.x=w.x;s.y=w.y;s.z=w.z;s.variety=0;s.key=0;s.solo[kGegenstimme]=true;
 Generator g;EventList es;Transport t;t.playing=true;MotifOccurrence example;uint64_t id=0;int count=0;
 for(int tick=0;tick<128*16;++tick){t.ppq=tick*.25;es.clear();{NoAllocations guard;g.process(t,s,6000,es);}auto m=g.rememberedMotif();if(m.complete){if(!id)id=m.identity;CHECK(id==m.identity);}auto p=g.inspectMotifOccurrence(tick,s);if(p.figure.passingIndex>=0){example=p;for(int i=0;i<es.size;++i)if(es.events[i].out==OutCounter&&es.events[i].velocity&&tick==p.begin+p.figure.notes[p.figure.passingIndex].at)++count;}}
 CHECK(count>0&&example.active);auto n=example.figure.notes[example.figure.passingIndex];
 for(int repeat=0;repeat<2;++repeat)
 {
  const double start=(example.begin+n.at+.25)*.25;t.ppq=start;es.clear();g.process(t,s,1000,es);bool chased=false,resolved=false;
  for(int i=0;i<es.size;++i)chased|=es.events[i].out==OutCounter&&es.events[i].velocity&&es.events[i].note==example.base+n.interval;
  CHECK(chased&&id==g.rememberedMotif().identity);
  for(int at=1000;at<5500;){t.ppq=start+at/24000.;int size=std::min(512,5500-at);es.clear();g.process(t,s,size,es);for(int i=0;i<es.size;++i)resolved|=es.events[i].out==OutCounter&&es.events[i].velocity&&es.events[i].note==example.base+example.figure.notes[example.figure.passingIndex+1].interval;at+=size;}
  CHECK(resolved);t.ppq=0;es.clear();g.process(t,s,6000,es);
 }
 std::cout<<"Modal and passing tests passed\n";
}
