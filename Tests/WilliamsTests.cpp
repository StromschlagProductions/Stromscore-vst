#include "TestSupport.h"
#include "ScoreEngine.h"
#include <set>
using namespace stromscore;
using namespace stromscore::composition;
using namespace stromscore::musicaltime;
namespace stromscore {struct ExecutionTestAccess {
 static RoleRhythmPlan roles(Generator& g,const Settings& s,Tick at){g.cur=&s;auto p=g.roleRhythm(g.locate(at),s);g.cur=nullptr;return p;}
};}
int main()
{
 ArpeggioPhrasePolicy phrasing;phrasing.enabled=true;
 int continued=0,breathed=0,exchanged=0;
 for(unsigned choice=0;choice<100000;choice+=997){
  const auto plan=planArpeggioPhrase(phrasing,Tick{},16*quarter,4*quarter,.7f,.8f,true,choice);
  CHECK(plan.count>=1&&plan.count<=2);
  for(int i=0;i<plan.count;++i){CHECK(plan.figures[i].end>plan.figures[i].begin);CHECK(plan.figures[i].end<=plan.end);}
  if(plan.count==2){++exchanged;CHECK(plan.figures[0].end<plan.figures[1].begin);CHECK(plan.releaseAt(plan.figures[0].end)==plan.figures[0].end);}
  if(plan.figures[plan.count-1].end==plan.end)++continued;else ++breathed;
 }
 CHECK(continued&&breathed&&exchanged);
 phrasing.enabled=false;
 const auto continuous=planArpeggioPhrase(phrasing,Tick{},32*quarter,4*quarter,.2f,.8f,true,99999);
 CHECK(continuous.count==1&&continuous.releaseAt(31*quarter)==32*quarter);

 CHECK(wendungCount(GenreScore,ProfileId::johnWilliams)==49);
 std::set<int> selected;
 Settings s;s.profile=ProfileId::johnWilliams;s.policy=policyForContext(s.profile,true);s.y=.75f;s.x=.3f;s.z=.6f;s.melody=true;
 for(int xyz=0;xyz<49;++xyz){const auto& w=wendungAt(GenreScore,xyz,s.profile);CHECK(w.coloration==ChordColoration::protectedColor);s.x=w.x;s.y=w.y;s.z=w.z;
  for(int salt=0;salt<200;++salt)selected.insert(static_cast<int>(wendungAt(GenreScore,Generator::pick(s,salt),s.profile).id));}
 CHECK(selected.size()==49);
 for(const auto& c:williamsRhythms)for(int bar=0;bar<16;++bar)
 {NoAllocations guard;auto p=planRoleRhythm(c,bar);
  for(const auto* part:{&p.harmony,&p.bass})for(int i=0;i<part->count;++i){const auto& n=part->notes[i];CHECK(n.at>=Tick{}&&n.at<4*quarter&&n.length>Tick{});if(i+1<part->count)CHECK(n.at+n.length<=part->notes[i+1].at);}
 }
 s.x=.55f;s.y=.8f;s.z=.7f;Generator g;EventList es;Transport t;t.playing=true;g.process(t,s,1,es);
 bool harmony=false,bass=false,fallback=false;
 for(int i=0;i<128;++i){NoAllocations guard;auto p=ExecutionTestAccess::roles(g,s,i*4*quarter);harmony|=p.harmony.active;bass|=p.bass.active;fallback|=!p.source;
  Settings m=s;m.padPattern=PadHeld;m.bassPattern=BassHeld;auto manual=ExecutionTestAccess::roles(g,m,i*4*quarter);CHECK(!manual.harmony.active&&!manual.bass.active);
  m=s;m.meterNum=7;m.meterDen=8;CHECK(!ExecutionTestAccess::roles(g,m,i*4*quarter).source);
  m=s;m.genre=GenrePopRock;CHECK(!ExecutionTestAccess::roles(g,m,i*4*quarter).source);
  m=s;m.profile=ProfileId::johnBarry;CHECK(!ExecutionTestAccess::roles(g,m,i*4*quarter).source);
  m=s;m.rangeOn[kBass]=true;m.rangeLo[kBass]=m.rangeHi[kBass]=1;
  CHECK(!ExecutionTestAccess::roles(g,m,i*4*quarter).bass.active);
  m=s;m.rangeOn[kFlaeche]=true;m.rangeLo[kFlaeche]=m.rangeHi[kFlaeche]=1;
  CHECK(!ExecutionTestAccess::roles(g,m,i*4*quarter).harmony.active);
 }
 CHECK(harmony&&bass&&fallback);
 // The actual new-profile processor path is allocation-free, including density,
 // simultaneous note claims, scene restarts and non-boundary position jumps.
 for(int mode=0;mode<4;++mode){Settings x=s;x.melody=mode==1||mode==3;x.mute[kGegenstimme]=mode==0||mode==1;x.stichFixed=true;
  Generator engine;Transport host;host.playing=true;EventList midi;
  for(int i=0;i<512;++i){host.ppq=i*.25;if(i==256)host.ppq=12.125;{NoAllocations guard;engine.process(host,x,7200,midi);}CHECK(!midi.overflow);midi.clear();}
  host.playing=false;{NoAllocations guard;engine.process(host,x,512,midi);}
 }

 for(int layer=0;layer<kNumLayers;++layer)for(bool solo:{false,true}){
  Settings x=s;x.melody=true;x.y=.9f;if(solo)x.solo[layer]=true;else x.mute[layer]=true;
  Generator engine;Transport host;host.playing=true;EventList midi;
  for(int i=0;i<64;++i){midi.clear();host.ppq=i*.25;{NoAllocations guard;engine.process(host,x,7200,midi);}
   for(int e=0;e<midi.size;++e)if(!midi.events[e].type&&midi.events[e].velocity)
    CHECK(solo?kOutputLayer[midi.events[e].out]==layer:kOutputLayer[midi.events[e].out]!=layer);
  }
 }
 std::cout<<"49 protected harmonies reachable; typed roles, durations, manual/meter/profile fallback and allocation guard passed\n";
}
