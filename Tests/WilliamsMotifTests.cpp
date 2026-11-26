#include "TestSupport.h"
#include "ScoreEngine.h"
#include <set>
using namespace stromscore;using namespace stromscore::composition;using namespace stromscore::musicaltime;
namespace stromscore {struct ExecutionTestAccess {
 static int selected(Generator& g,const Settings& s,int output){g.cur=&s;auto m=g.authoredMotif(g.locate(Tick{}),s,output);g.cur=nullptr;return m.source?m.source->id:0;}
 static auto occurrence(Generator& original,const Settings& s,Tick at,int output){auto g=original;g.cur=&s;return g.motifOccurrence(at,g.locate(at),s,output,true);}
 static void sourceHarmony(Generator& g,const AuthoredMotifSource& source){
  g.current=kCustomWendung;g.custom={};g.custom.n=2;g.custom.coloration=ChordColoration::protectedColor;
  for(int bar=0;bar<2;++bar){bool found=false;
   for(int root=0;root<12&&!found;++root)for(int type=0;type<(int)(sizeof(kShapes)/sizeof(*kShapes))&&!found;++type){unsigned mask=0;
    for(int i=0;i<kShapes[type].n;++i)mask|=pitchBit(root+kShapes[type].iv[i]);
    if(mask==source.harmony[bar]){g.custom.ch[bar]={root,type,1,source.bass[bar]};found=true;}}
   CHECK(found);
  }
 }
 static void freePrefix(Generator& g){g.voice(OutCounter).motif.draft.vocabularyId=0;}
 static void foreignHarmony(Generator& g){for(int i=0;i<2;++i){g.custom.ch[i].root=(g.custom.ch[i].root+1)%12;g.custom.ch[i].bass=(g.custom.ch[i].bass+1)%12;}}
 static void markComplete(Generator& g,const AuthoredMotifSource& source,int key,int shift){auto& m=g.voice(OutCounter).motif.draft;m.clear();m.vocabularyId=source.id;for(int i=0;i<source.count;++i)m.observe(source.pitches[i]+key+shift,sixteenth*source.at[i],sixteenth*source.lengths[i]);m.cycleLength=sixteenth*source.steps;m.finish();}
 static void pin(Generator& g,const AuthoredMotifSource& source,int key,int shift){auto& m=g.voice(OutCounter).motif.draft;m.vocabularyId=source.id;m.count=1;m.origin=source.pitches[0]+key+shift;m.notes[0].at=sixteenth*source.at[0];}
 static auto note(Generator& g,const Settings& s,int i,int output){g.cur=&s;auto n=g.planMotifNote(i,g.locate(Tick{}),s,output,nullptr,false);g.cur=nullptr;return n;}
};}
int main(){
 CHECK(sizeof(williamsMotifs)/sizeof(*williamsMotifs)==32);std::set<int> ids;
 for(const auto& source:williamsMotifs){CHECK(ids.insert(source.id).second);CHECK(source.count>=2&&source.count<=8);
  for(int key=0;key<12;++key){
   Settings s;s.profile=ProfileId::johnWilliams;s.policy=policyForContext(s.profile,true);s.key=key;s.melody=true;s.scene=false;s.sceneBars=0;s.meterNum=source.num;s.meterDen=source.den;s.x=source.x;s.y=source.y;s.z=source.z;
   Generator g;Transport t;t.playing=true;EventList es;g.process(t,s,1,es);ExecutionTestAccess::sourceHarmony(g,source);
   // Full source pitches/gates are representable without dropping notes, clipping
   // peaks or introducing a different interval sequence, in every transposition.
   const auto catalog=outputCatalog(s);bool fits=false;int octave=0;
   for(int shift=-48;shift<=48;shift+=12){bool ok=true;
    for(int i=0;i<source.count;++i){const int pitch=key+source.pitches[i]+shift;
     ok&=pitch>=catalog[OutCounter].track.instrument.range.low&&pitch<=catalog[OutCounter].track.instrument.range.high;}
    if(ok&&!fits)octave=shift;fits|=ok;
   }CHECK(fits);
   ExecutionTestAccess::pin(g,source,key,octave);
   CHECK(ExecutionTestAccess::selected(g,s,OutCounter)==source.id);
   for(int i=0;i<source.count;++i){const auto n=ExecutionTestAccess::note(g,s,i,OutCounter);CHECK(n.valid);CHECK(n.at==sixteenth*source.at[i]);CHECK(n.length==sixteenth*source.lengths[i]);CHECK(n.pitch==source.pitches[i]+key+octave);}
   CHECK(!ExecutionTestAccess::note(g,s,source.count,OutCounter).valid);
   if(source.singleIntroduction){ExecutionTestAccess::markComplete(g,source,key,octave);CHECK(!ExecutionTestAccess::occurrence(g,s,16*quarter,OutCounter).active);}
   if(source.dialogOnly)CHECK(ExecutionTestAccess::selected(g,s,OutMelody)!=source.id);
   ExecutionTestAccess::freePrefix(g);CHECK(ExecutionTestAccess::selected(g,s,OutCounter)==0);
   ExecutionTestAccess::pin(g,source,key,octave);
   ExecutionTestAccess::foreignHarmony(g);CHECK(ExecutionTestAccess::selected(g,s,OutCounter)==0);

   for(int b=0;b<2;++b){const auto chord=transposePitchMask(source.harmony[b],key);
    const auto mask=authoredPitchMask(source,chord,source.bass[b]+key,key,{});
    CHECK((mask&transposePitchMask(source.melodic[b],key))==transposePitchMask(source.melodic[b],key));
    CHECK(authoredPitchMask(source,0,source.bass[b]+key,key,{})==0);
    CHECK(authoredPitchMask(source,chord,source.bass[b]+key+1,key,{})==0);
   }
  }
 }
 int authored=0,returns=0,variants=0;std::set<int> used;bool established[2]{};uint64_t original[2]{};
 for(int path=0;path<8;++path){
  Settings s;s.profile=ProfileId::johnWilliams;s.policy=policyForContext(s.profile,true);s.melody=true;s.scene=false;s.sceneBars=0;s.x=path<3?.2f:.75f;s.y=path%3==0?.35f:.75f;s.z=path%3==2?.8f:.35f;
  Generator g;Transport t;t.playing=true;EventList es;original[0]=original[1]=0;established[0]=established[1]=false;
  for(int step=0;step<128*16;++step){t.ppq=step*.25;
   if(path>=6){const double phase=t.ppq/(path==6?64.:8.);s.x=static_cast<float>(.5+.4*std::sin(phase));s.y=static_cast<float>(.65+.25*std::sin(phase*.7));s.z=static_cast<float>(.5+.45*std::cos(phase*.8));}
   es.clear();{NoAllocations guard;g.process(t,s,6000,es);}CHECK(!es.overflow);
   for(int output:{OutCounter,OutMelody}){const auto& m=g.rememberedMotif(output);int v=output==OutMelody;
    if(m.vocabularyId>=50000){
     const AuthoredMotifSource* source=nullptr;for(const auto& candidate:williamsMotifs)if(static_cast<uint32_t>(candidate.id)==m.vocabularyId)source=&candidate;CHECK(source);
     int octave=10000;
     for(int j=0;j<m.count;++j){int index=-1;for(int i=0;i<source->count;++i)if(m.notes[j].at==sixteenth*source->at[i])index=i;CHECK(index>=0);
      const int shift=m.origin+m.notes[j].interval-source->pitches[index]-s.key;CHECK(shift%12==0);if(j==0)octave=shift;CHECK(shift==octave);}
     ++authored;used.insert(m.vocabularyId);if(m.complete){if(!original[v])original[v]=m.identity;CHECK(original[v]==m.identity);}
     const auto p=ExecutionTestAccess::occurrence(g,s,step*sixteenth,output);
     for(int i=0;i<es.size;++i)if(!es.events[i].type&&es.events[i].velocity&&es.events[i].out==output&&!p.introduction&&p.active){++returns;variants+=p.figure.variation!=MotifVariation::original;established[v]=true;}
    }
   }
  }
  t.playing=false;g.process(t,s,512,es);
 }

 for(int mode=0;mode<4;++mode){
  Settings s;s.profile=ProfileId::johnWilliams;s.policy=policyForContext(s.profile,true);s.scene=false;s.sceneBars=0;s.x=.2f;s.y=.45f;s.z=.6f;
  s.melody=mode==1||mode==3;s.mute[kGegenstimme]=mode==1;s.melodyMotif=mode!=3;s.motif=mode!=2;
  Generator g;Transport t;t.playing=true;EventList es;int melody=0,dialog=0;
  for(int step=0;step<32*16;++step){t.ppq=step*.25;es.clear();{NoAllocations guard;g.process(t,s,6000,es);}
   for(int i=0;i<es.size;++i)if(!es.events[i].type&&es.events[i].velocity){melody+=es.events[i].out==OutMelody;dialog+=es.events[i].out==OutCounter;}
  }
  if(!s.melody)CHECK(melody==0);
  if(s.mute[kGegenstimme])CHECK(dialog==0);
  if(!s.motif)CHECK(g.rememberedMotif(OutCounter).vocabularyId==0);
  if(!s.melodyMotif)CHECK(g.rememberedMotif(OutMelody).vocabularyId==0);
  if(mode==0)CHECK(g.rememberedMotif(OutCounter).vocabularyId>=50000&&dialog>0);
 }
 CHECK(authored>0&&returns>0);std::cout<<"Williams authored source use="<<authored<<" returns="<<returns<<" variant notes="<<variants<<" distinct="<<used.size()<<"; 32 sources x 12 transpositions, immutable material, no allocations\n";
}
