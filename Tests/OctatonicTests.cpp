#include "TestSupport.h"
#include "ScoreEngine.h"
#include <iostream>
#include <map>
using namespace stromscore;using namespace stromscore::composition;using namespace stromscore::musicaltime;
namespace stromscore {struct ExecutionTestAccess {
 static ModalContext context(Generator& g,const Settings& s){return g.modalContextFor(s);}
 static MotifOccurrence occurrence(Generator& g,const Settings& s,Tick at,int output){auto copy=g;copy.cur=&s;return copy.motifOccurrence(at,copy.locate(at),s,output,true);}
};}
int main(){
 int passingCount=0,resolved=0;std::map<std::pair<int,int64_t>,int> targets;
 for(int key=0;key<12;++key){
  Settings s;s.profile=ProfileId::johnWilliams;s.policy=policyForContext(s.profile,true);s.key=key;s.melody=true;s.motif=s.melodyMotif=true;s.scene=false;s.sceneBars=0;
  const auto index=wendungIndex(GenreScore,WendungId::williamsH12,s.profile);const auto& w=wendungAt(GenreScore,index,s.profile);
  s.x=w.x;s.y=w.y;s.z=w.z;s.variety=0;
  bool selected=false;for(int v=1;v<=64;++v){s.variation=v;if(Generator::pick(s,0)==index){selected=true;break;}}CHECK(selected);
  Generator g;Transport t;t.playing=true;EventList es;uint64_t identities[2]{};int localPasses=0;targets.clear();MotifOccurrence firstBridge;int bridgeOutput=-1;
  for(int step=0;step<128*16;++step){
   t.ppq=step*.25;es.clear();{NoAllocations guard;g.process(t,s,6000,es);}CHECK(!es.overflow);
   const auto context=ExecutionTestAccess::context(g,s);CHECK(context.mode==Mode::octatonic&&context.status==ModalStatus::unique);
   for(int output:{OutCounter,OutMelody}){
    const auto& material=g.rememberedMotif(output);if(material.complete){auto& id=identities[output==OutMelody];if(!id)id=material.identity;CHECK(id==material.identity);}
    const auto plan=ExecutionTestAccess::occurrence(g,s,sixteenth*step,output);
    for(int e=0;e<es.size;++e){const auto& n=es.events[e];if(n.type||!n.velocity||n.out!=output)continue;
     if(!(context.mask&pitchBit(n.note)))std::cerr<<"outside key="<<key<<" step="<<step<<" output="<<output<<" note="<<int(n.note)<<" id="<<g.wendung()<<"\n";CHECK(context.mask&pitchBit(n.note));
     auto found=targets.find({output,step});if(found!=targets.end()){CHECK(n.note==found->second);++resolved;targets.erase(found);}
     if(plan.figure.passingIndex<0)continue;
     const auto i=plan.figure.passingIndex;const auto& bridge=plan.figure.notes[i];const auto& target=plan.figure.notes[i+1];
     if(plan.begin+bridge.at==step*sixteenth&&n.note==plan.base+bridge.interval){
      ++passingCount;++localPasses;if(bridgeOutput<0){firstBridge=plan;bridgeOutput=output;}const auto at=(plan.begin+target.at)/sixteenth;
      targets[{output,at}]=plan.base+target.interval;
     }
    }
   }
  }
  CHECK(targets.empty());
  if(key==0){
   CHECK(bridgeOutput>=0);const int i=firstBridge.figure.passingIndex;
   const auto& n=firstBridge.figure.notes[i];const int pitch=firstBridge.base+n.interval;
   const int target=firstBridge.base+firstBridge.figure.notes[i+1].interval;
   const double start=toQuarters(firstBridge.begin+n.at)+.0625;
   t.ppq=start;es.clear();{NoAllocations guard;g.process(t,s,1000,es);}bool chased=false,targetPlayed=false;
   for(int e=0;e<es.size;++e)chased|=!es.events[e].type&&es.events[e].velocity&&es.events[e].out==bridgeOutput&&es.events[e].note==pitch;
   CHECK(chased);
   for(int offset=1000;offset<13000;){t.ppq=start+offset/24000.;const int size=std::min(512,13000-offset);es.clear();{NoAllocations guard;g.process(t,s,size,es);}
    for(int e=0;e<es.size;++e)targetPlayed|=!es.events[e].type&&es.events[e].velocity&&es.events[e].out==bridgeOutput&&es.events[e].note==target;
    offset+=size;}
   CHECK(targetPlayed);
   t.ppq=0;es.clear();{NoAllocations guard;g.process(t,s,6000,es);}CHECK(g.rememberedMotif(bridgeOutput).identity==identities[bridgeOutput==OutMelody]);
  }
  t.playing=false;{NoAllocations guard;g.process(t,s,512,es);}
 }
 CHECK(passingCount>0&&resolved==passingCount);
 std::cout<<"Octatonic score: "<<passingCount<<" actual passing notes / "<<resolved<<" actual resolutions; twelve transpositions, immutable originals, both roles, warm passing-note chase/loop, no allocations\n";
}
