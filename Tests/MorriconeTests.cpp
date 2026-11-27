#include "TestSupport.h"
#include "ScoreEngine.h"
#include <vector>
#include <tuple>
#include <map>
using namespace stromscore;
using namespace stromscore::composition;
namespace stromscore {struct ExecutionTestAccess {
 static bool planned(const Generator& g){return g.harmonicPlan.valid;}
 static int owners(const Generator& g){return g.numActive;}
};}
using Row=std::tuple<long long,int,int,int,int>;
static Settings settings(int id,int key=0){
 Settings s;s.profile=ProfileId::ennioMorricone;s.policy=policyForContext(s.profile,true);s.key=key;s.scene=false;s.sceneBars=0;s.drive=false;
 s.melody=false;s.mute[kGegenstimme]=true;s.mute[kArp]=s.mute[kAkzent]=true;s.variety=0;s.dynamics=false;
 const auto* h=findHarmonyTemplate(static_cast<WendungId>(id));CHECK(h);s.x=h->x;s.y=h->y;s.z=h->z;
 bool found=false;for(int v=1;v<=16;++v){s.variation=v;if(wendungAt(s.genre,Generator::pick(s,0),s.profile).id==h->id){found=true;break;}}CHECK(found);return s;
}
static std::vector<Row> render(Settings s,int block,int bars=8,bool jumps=false){
 Generator g;Transport t;t.playing=true;t.bpm=100;EventList e;std::vector<Row> rows;std::map<std::pair<int,int>,bool> active;
 const long long total=bars*4*28800LL;
 auto collect=[&](long long at){CHECK(!e.overflow);for(int i=0;i<e.size;++i){auto n=e.events[i];if(n.type)continue;auto& held=active[{n.channel,n.note}];if(n.velocity){CHECK(!held);held=true;}else{CHECK(held);held=false;}
 if(n.out==OutPadLong){int poly=0;for(auto [k,v]:active)if(k.first==s.channel[OutPadLong])poly+=v;if(s.channel[OutPadLong]!=s.channel[OutBassLong])CHECK(poly<=6);}rows.emplace_back(at+n.offset,n.out,n.channel,n.note,n.velocity);}e.clear();};
 for(long long at=0;at<total;){int n=static_cast<int>(std::min<long long>({block,total-at,7200-at%7200}));t.ppq=at/28800.;
  if(jumps){if(at>=total/2)t.ppq-=total/2/28800.;if(at>=total*3/4)t.ppq+=8.125;t.playing=!(at>=total/4&&at<total/4+7200);}
  {NoAllocations guard;g.process(t,s,n,e);}collect(at);at+=n;
 }
 t.playing=false;{NoAllocations guard;g.process(t,s,block,e);}collect(total);CHECK(ExecutionTestAccess::owners(g)==0);for(auto [k,v]:active)CHECK(!v);return rows;
}
int main(){
 // The U040 counterexample: retain physical C60, not merely pitch class C72.
 voiceleading::ChordVoicing a{4,{58,60,67,75}},p{4,{57,60,65,72}};
 voiceleading::VoiceBinding b;b.required={1,{60}};b.preferred={1,{67}};
 auto v=voiceleading::lead(a,p,40,90,-1,-1,&b);CHECK(v.n==4&&voiceleading::contains(v,60));
 b.required={1,{61}};CHECK(voiceleading::lead(a,p,40,90,-1,-1,&b).n==0);
 b.required={1,{60}};CHECK(voiceleading::lead(a,p,61,90,-1,-1,&b).n==0);
 CHECK(voiceleading::lead(a,{},40,90,-1,-1,&b).n==0);
 // Ordinary soft preferences do not license foreign tones or require an impossible hold.
 b.required={};b.preferred={1,{61}};v=voiceleading::lead(a,p,40,90,-1,-1,&b);CHECK(v.n==4);for(int i=0;i<v.n;++i)CHECK(v.notes[i]%12!=1);
 voiceleading::ChordVoicing six{6,{48,60,64,67,72,76}},four{4,{48,60,64,67}};
 b.required={2,{48,60}};b.preferred={};v=voiceleading::lead(six,four,40,90,-1,-1,&b);
 CHECK(v.n==6&&voiceleading::contains(v,48)&&voiceleading::contains(v,60));
 HarmonicRequest request;request.count=2;request.cyclic=false;request.padRange={40,90};request.bassRange={30,60};
 request.slots[0].pad=p;request.slots[0].bass=48;request.slots[0].preservePad=true;
 request.slots[1].pad=a;request.slots[1].bass=46;request.slots[1].binding.required={1,{60}};
 request.slots[1].binding.preferred={1,{100}};auto plan=planHarmony(request);CHECK(plan.valid&&voiceleading::contains(plan.slots[1].pad,60));
 request.slots[1].binding.required={1,{61}};CHECK(!planHarmony(request).valid);
 for(int id:{50004,50005,50009,50010,50011,50014,50016,50017,50019,50022,50023,50051,50056,50057})
  for(int key=0;key<12;++key){
   auto s=settings(id,key);const auto rows=render(s,512);CHECK(rows==render(s,2048));
   const auto* source=findHarmonyTemplate(static_cast<WendungId>(id));std::map<int,bool> sounding;
   size_t cursor=0;long long boundary=0;int base=60+key;
   for(int c=0;c<source->count;++c){const auto& chord=source->voicings[c];const long long end=boundary+source->chords[c].bars*4*28800LL;
    const auto start=cursor;
    while(cursor<rows.size()&&std::get<0>(rows[cursor])<end){const auto& r=rows[cursor++];if(std::get<1>(r)==OutPadLong)sounding[std::get<3>(r)]=std::get<4>(r)>0;}
    int count=0;for(auto [n,on]:sounding)count+=on;CHECK(count==chord.count);
    if(c==0){for(auto [pitch,on]:sounding)if(on){base=pitch-chord.notes[0];break;}CHECK((base-60-key)%12==0);}
    for(int n=0;n<chord.count;++n)CHECK(sounding[base+chord.notes[n]]);
    if(c>0)for(int n=0;n<chord.heldCount;++n)for(size_t j=start;j<cursor;++j){auto r=rows[j];CHECK(!(std::get<0>(r)==boundary&&std::get<1>(r)==OutPadLong&&std::get<3>(r)==base+chord.held[n]));}
    boundary=end;
   }
   int previousBass=-1;
   for(const auto& r:rows)if(std::get<1>(r)==OutBassLong&&std::get<4>(r)>0)
   {const int note=std::get<3>(r);if(previousBass>=0)CHECK(std::abs(note-previousBass)<=7);previousBass=note;}
   CHECK(!rows.empty());
  }
 // Transport/loop/seek and swing are block-independent; long harmony remains nominal.
 for(int meter:{3,4,5,7}){auto s=settings(50004);s.meterNum=meter;s.meterDen=meter==4?4:8;s.swing=.65f;CHECK(render(s,127,16,true)==render(s,2048,16,true));}
 for(int mode=0;mode<5;++mode){auto s=settings(50051);if(mode==0)s.follow[kFlaeche]=false;if(mode==1)s.padPattern=PadPulse;if(mode==2)s.mute[kFlaeche]=true;if(mode==3){s.rangeOn[0]=true;s.rangeLo[0]=48;s.rangeHi[0]=60;}if(mode==4){s.channel[OutBassLong]=s.channel[OutPadLong];s.octave[kBass]=1;}
  CHECK(render(s,127,16,true)==render(s,2048,16,true));}
 std::cout<<"Morricone: 14 sources x 12 keys, physical holds, colour, claims, transport, manual/capability fallbacks passed\n";
}
