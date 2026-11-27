#include "TestSupport.h"
#include "ScoreEngine.h"
#include <vector>
#include <tuple>
#include <map>
using namespace stromscore;
using namespace stromscore::musicaltime;
using namespace stromscore::composition;
namespace stromscore { struct ExecutionTestAccess {
 static PedalPlan plan(const Generator& g){return g.independentPedal;}
 static void release(Generator& g,const Settings& s,double at,EventList& e){g.cur=&s;g.releaseAt(at,0,e);g.cur=nullptr;}
 static int pitch(const Generator& g){for(int i=0;i<g.numActive;++i)if(g.active[i].pedalOwner)return g.active[i].note;return -1;}
 static int owners(const Generator& g){int n=0;for(int i=0;i<g.numActive;++i)n+=g.active[i].pedalOwner;return n;}
 static void shared(Generator& g,const Settings& s,EventList& e){g.cur=&s;g.on[kArp]=true;g.nowTime=quarter;g.dispatchIdentity+=1;g.noteOn(OutArp,g.active[0].note,70,2*quarter,0,e);g.cur=nullptr;}
};}
using Row=std::tuple<long long,int,int,int,int,int>;
static Settings settings(int id=40003,int key=0){Settings s;s.profile=ProfileId::johnWilliams;s.policy=policyForContext(s.profile,true);s.key=key;s.scene=false;s.sceneBars=0;s.drive=false;s.melody=false;s.mute[kGegenstimme]=true;s.variety=0;
 const auto* h=findHarmonyTemplate(static_cast<WendungId>(id));CHECK(h);s.x=h->x;s.y=h->y;s.z=h->z;
 bool found=false;for(int v=1;v<=16;++v){s.variation=v;if(static_cast<int>(wendungAt(s.genre,Generator::pick(s,0),s.profile).id)==id){found=true;break;}}CHECK(found);return s;}
static std::vector<Row> render(Settings s,int block,int bars=32){Generator g;Transport t;t.playing=true;t.bpm=100;EventList e;std::vector<Row> rows;std::map<std::pair<int,int>,int> held;
 const long long total=bars*4*28800LL;
 auto collect=[&](long long at){CHECK(!e.overflow);for(int i=0;i<e.size;++i){auto n=e.events[i];if(n.type)continue;auto& count=held[{n.channel,n.note}];if(n.velocity){CHECK(count==0);++count;}else {CHECK(count==1);--count;}rows.emplace_back(at+n.offset,n.out,n.channel,n.note,n.velocity,n.type);}e.clear();};
 for(long long at=0;at<total;){int n=static_cast<int>(std::min<long long>(block,total-at));t.ppq=at/28800.;{NoAllocations guard;g.process(t,s,n,e);}collect(at);at+=n;}
 t.playing=false;{NoAllocations guard;g.process(t,s,block,e);}collect(total);for(auto [key,count]:held)CHECK(count==0);return rows;}
int main(){
 PedalPlan p{Tick{},64*quarter,0,BassRelation::independentPedal};CHECK(p.contains(63*quarter));CHECK(!p.contains(64*quarter));CHECK(permits(p,{1,0,false}));CHECK(!permits(p,{2,0,true}));p.relation=BassRelation::authorizedDissonancePedal;CHECK(permits(p,{2,0,true}));CHECK(!permits(p,{2,-1,true}));CHECK(!permits(p,{2,0,false}));CHECK(!permits(p,{1,1,true}));p.pitchClass=12;CHECK(!permits(p,{4095,0,true}));
 for(int id:{40003,40050,40061})for(int key=0;key<12;++key){auto s=settings(id,key);auto a=render(s,512);auto b=render(s,2048);CHECK(a==b);
  int bass=0;for(auto r:a)if(std::get<1>(r)==OutBassLong&&std::get<4>(r)>0){++bass;CHECK(std::get<3>(r)%12==key);}CHECK(bass==2);
 }
 for(int id:{40017,40046}){auto s=settings(id);Generator g;Transport t;t.playing=true;EventList e;g.process(t,s,512,e);CHECK(ExecutionTestAccess::owners(g)==0);}
 // Explicit user choices remain the original bass path.
 for(int mode=0;mode<5;++mode){auto s=settings();if(mode==0)s.bassPattern=BassQuarter;if(mode==1)s.follow[kBass]=false;if(mode==2)s.mute[kBass]=true;if(mode==4)s.policy.pedal.enabled=false;if(mode==3)s.rangeOn[kBass]=true,s.rangeLo[kBass]=s.rangeHi[kBass]=1;
  Generator g;Transport t;t.playing=true;EventList e;g.process(t,s,512,e);CHECK(ExecutionTestAccess::owners(g)==0);CHECK(!ExecutionTestAccess::plan(g).contains(Tick{}));}
 // Chase, loop, octave/channel/key changes, mute/solo and stop always own/release one note.
 for(int meter:{3,4,5,7}){auto s=settings();s.meterNum=meter;s.meterDen=meter==4?4:8;Generator g;Transport t;t.playing=true;EventList e;
  for(double pos:{0.,.5,8.125,33.,1.,0.}){t.ppq=pos;e.clear();{NoAllocations guard;g.process(t,s,512,e);}CHECK(ExecutionTestAccess::owners(g)==1);CHECK(ExecutionTestAccess::plan(g).contains(fromQuarters(pos)));}
  s.mute[kBass]=true;t.ppq+=512/24000.;e.clear();g.process(t,s,512,e);CHECK(ExecutionTestAccess::owners(g)==0);
  s.mute[kBass]=false;s.octave[kBass]=1;s.channel[OutBassLong]=12;t.ppq+=512/24000.;e.clear();g.process(t,s,512,e);CHECK(ExecutionTestAccess::owners(g)==1);
  t.playing=false;e.clear();g.process(t,s,512,e);CHECK(ExecutionTestAccess::owners(g)==0);
 }
 {auto s=settings();s.passing=true;Generator g;Transport t;t.playing=true;EventList e;g.process(t,s,512,e);CHECK(ExecutionTestAccess::owners(g)==1);}
 // Continuous XYZ must not octave-shift/retrigger an already sounding pedal.
 {auto s=settings();Generator g;Transport t;t.playing=true;EventList e;g.process(t,s,512,e);const int pitch=ExecutionTestAccess::pitch(g);CHECK(pitch>=0);
  s.x=.91f;t.ppq=512/24000.;e.clear();g.process(t,s,512,e);CHECK(ExecutionTestAccess::pitch(g)==pitch);for(int i=0;i<e.size;++i)CHECK(e.events[i].out!=OutBassLong&&e.events[i].out!=OutBassShort);
  s.octave[kBass]=1;t.ppq+=512/24000.;e.clear();g.process(t,s,512,e);CHECK(ExecutionTestAccess::pitch(g)>pitch);
  s.key=1;t.ppq+=512/24000.;e.clear();g.process(t,s,512,e);CHECK(ExecutionTestAccess::pitch(g)>=0&&ExecutionTestAccess::pitch(g)%12==1);
 }
 // A second output on the same physical key cannot interrupt a held pedal.
 {auto s=settings();for(int l=0;l<kNumLayers;++l)s.mute[l]=l!=kBass;s.channel[OutArp]=s.channel[OutBassLong];Generator g;Transport t;t.playing=true;EventList e;g.process(t,s,512,e);s.mute[kArp]=false;e.clear();ExecutionTestAccess::shared(g,s,e);CHECK(e.size==0);CHECK(ExecutionTestAccess::owners(g)==1);ExecutionTestAccess::release(g,s,2.,e);CHECK(e.size==0);ExecutionTestAccess::release(g,s,64.,e);CHECK(e.size==1&&e.events[0].velocity==0);CHECK(ExecutionTestAccess::owners(g)==0);}
 std::cout<<"Independent pedals: 36 transposed sources; ownership, lifetime, transport, capability and dissonance checks passed\n";
}
