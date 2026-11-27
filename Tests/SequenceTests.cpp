#include "TestSupport.h"
#include "ScoreEngine.h"
#include <vector>
#include <tuple>
#include <map>
using namespace stromscore;
using namespace stromscore::composition;
using namespace stromscore::musicaltime;
namespace stromscore {struct ExecutionTestAccess {
 static auto uses(const Generator& g){return g.sequences;}
 static PedalPlan pedal(const Generator& g){return g.independentPedal;}
};}
using Row=std::tuple<int64_t,int,int,int,int>;
static Settings settings(float x=.3f,float y=.7f,float z=.5f){Settings s;s.profile=ProfileId::johnCarpenter;s.policy=policyForContext(s.profile,true);s.x=x;s.y=y;s.z=z;s.scene=false;s.sceneBars=0;s.variety=0;s.stichFixed=true;s.motif=true;s.melody=false;return s;}
static std::vector<Row> render(Settings s,int block,int bars=16,int jump=0,double bpm=100){
 Generator g;Transport t;t.playing=true;t.bpm=bpm;const double samplesPerQuarter=48000.*60/bpm;EventList e;std::vector<Row> result;std::map<std::pair<int,int>,int> held;
 const int64_t total=static_cast<int64_t>(bars)*s.meterNum*4/s.meterDen*samplesPerQuarter;
 auto collect=[&](int64_t at){CHECK(!e.overflow);for(int i=0;i<e.size;++i){const auto n=e.events[i];if(n.type)continue;int& count=held[{n.channel,n.note}];if(n.velocity){CHECK(count==0);++count;}else{CHECK(count==1);--count;}
  CHECK(n.note<=127);if(n.out==OutStich&&n.velocity)CHECK(n.note==36);
  result.emplace_back(at+n.offset,n.out,n.channel,n.note,n.velocity);}e.clear();};
 for(int64_t at=0;at<total;){int n=static_cast<int>(std::min<int64_t>({block,total-at,7200-at%7200}));t.ppq=at/samplesPerQuarter;
  if(jump){if(at>=total/2)t.ppq-=total/2/samplesPerQuarter;if(at>=total*3/4)t.ppq+=8.125;}
  {NoAllocations guard;g.process(t,s,n,e);}collect(at);at+=n;
 }
 t.playing=false;{NoAllocations guard;g.process(t,s,block,e);}collect(total);for(auto [key,n]:held)CHECK(n==0);return result;
}
int main(){
 CHECK(valid(carpenterPolicy.sequences));
 for(const auto& s:carpenter::sources)CHECK(valid(s));
 // Complete source cycles, not first-bar reconstructions. Different voices share
 // immutable data but never a cursor. A five-tone/sixteenth cycle is five bars.
 auto source=carpenter::sources[0];source.tones=5;source.count=16;source.period=4*quarter;
 for(int i=0;i<5;++i)source.functions[i]='A';
 for(int i=0;i<16;++i)source.attacks[i]={i*sixteenth,Tick{84},88};
 CHECK(source.cycle()==20*quarter);CHECK(valid(source));SequenceUse a{&source,Tick{},60},b{&source,quarter,72};
 CHECK(a.tone(4*quarter,0)==1);CHECK(a.tone(20*quarter,0)==0);CHECK(b.next(Tick{})==quarter);CHECK(a.next(Tick{})==Tick{});
 auto broken=source;broken.attacks[1].at=Tick{};CHECK(!valid(broken));broken=source;broken.attacks[0].duration=2*quarter;CHECK(!valid(broken));
 // All production tonalities, both Follow settings, manual override, swing and odd meters.
 for(int key=0;key<12;++key){auto s=settings();s.key=key;CHECK(render(s,127)==render(s,1024));}
 for(int num:{3,4,5,7})for(float swing:{0.f,.6f}){auto s=settings();s.meterNum=num;s.meterDen=num==4?4:8;s.swing=swing;CHECK(render(s,127,8,1)==render(s,2048,8,1));}
 for(int mode=0;mode<5;++mode){auto s=settings();if(mode==0)s.follow[kBass]=false;if(mode==1)s.bassPattern=BassQuarter;if(mode==2)s.arpFigure=ArpDown;if(mode==3)s.mute[kBass]=true;if(mode==4)s.solo[kArp]=true;CHECK(render(s,127)==render(s,1024));}
 for(double bpm:{60.,137.,180.}){auto s=settings();auto a=render(s,127,8,0,bpm),b=render(s,2048,8,0,bpm);CHECK(a.size()==b.size());
  for(size_t i=0;i<a.size();++i){auto x=a[i],y=b[i];auto ta=std::get<0>(x),tb=std::get<0>(y);
   // Audio offsets are integer samples; non-integral PPQ/sample mappings may
   // differ by one sample, never by a musical tick or an event/voice decision.
   CHECK(std::abs(ta-tb)<=1);CHECK(std::llround(ta*960./(48000.*60/bpm))==std::llround(tb*960./(48000.*60/bpm)));
   std::get<0>(x)=std::get<0>(y)=0;CHECK(x==y);}}

 for(int pair=0;pair<3;++pair){auto s=settings();if(pair==0)s.channel[OutArp]=s.channel[OutCounter];if(pair==1)s.channel[OutBassShort]=s.channel[OutBassLong];if(pair==2)s.channel[OutCounter]=s.channel[OutPadLong];CHECK(render(s,127)==render(s,1024));}
 // A foreground melody must not consume a background sequencer's progress.
 {auto s=settings();auto original=render(s,512);s.melody=true;s.melodyMotif=true;auto lead=render(s,512);
  auto figures=[](const auto& rows){std::vector<Row> r;for(auto n:rows)if(std::get<1>(n)==OutArp||std::get<1>(n)==OutCounter)r.push_back(n);std::sort(r.begin(),r.end());return r;};
  CHECK(figures(original)==figures(lead));}
 // Real MIDI must reach the second bar/complete four-bar bass cycle, not
 // merely repeat a two-tone prefix. Policy data is consumed by the same emitter.
 for(const char* id:{"JC-Q054","JC-Q063","JC-B033"}){
  const SequenceSource* selected=nullptr;for(const auto& source:carpenter::sources)if(std::strcmp(source.reference,id)==0)selected=&source;CHECK(selected);
  auto s=settings(.3f,.55f,.3f);s.variety=0;if(std::strcmp(id,"JC-Q063")==0)s.z=.4f;s.policy.sequences.sources=selected;s.policy.sequences.count=1;
  const auto identity=sequenceIdentity(*selected);auto rows=render(s,512,8);std::vector<int> notes;
  for(auto r:rows)if(std::get<1>(r)==(selected->bass?OutBassShort:OutArp)&&std::get<4>(r))notes.push_back(std::get<3>(r));
  CHECK(notes.size()>=static_cast<size_t>(selected->tones));
  for(int i=0;i<selected->tones;++i)CHECK(notes[i]-notes[0]==selected->pitches[i]-selected->pitches[0]);
  CHECK(sequenceIdentity(*selected)==identity);
 }
 // Profile/genre changes out of a low-intensity rest must not block the next plan.
 {Generator g;auto s=settings();Transport t;t.playing=true;t.bpm=100;EventList e;std::map<std::pair<int,int>,int> open;
  for(int block=0;block<2000;++block){if(block%200==0){s.profile=block%400==0?ProfileId::neutral:ProfileId::johnCarpenter;if(block>=1200&&block<1800)s.profile=ProfileId::johnCarpenter;s.genre=block>=1200&&block<1600?GenrePopRock:GenreScore;s.policy=policyForContext(s.profile,s.genre==GenreScore);s.y=.01f;}
   if(block%200==20)s.y=.8f;t.ppq=block*512/28800.;e.clear();{NoAllocations n;g.process(t,s,512,e);}
   if(block%200>20)CHECK(g.wendung()>=0);
   for(int i=0;i<e.size;++i){auto r=e.events[i];if(!r.type){auto& n=open[{r.channel,r.note}];n+=r.velocity?1:-1;CHECK(n==0||n==1);}}}
  t.playing=false;e.clear();g.process(t,s,512,e);for(int i=0;i<e.size;++i)if(!e.events[i].type)open[{e.events[i].channel,e.events[i].note}]+=e.events[i].velocity?1:-1;
  for(auto n:open)CHECK(n.second==0);}
 // Production: an eligible fixed field has independently sounding LB and KB.
 {auto s=settings(.25f,.3f,.2f);s.variety=0;
  Generator g;Transport t;t.playing=true;t.bpm=100;EventList e;int lb=0,kb=0,ar=0,gs=0;
  for(int64_t at=0;at<32LL*4*28800;at+=512){t.ppq=at/28800.;e.clear();g.process(t,s,512,e);for(int i=0;i<e.size;++i)if(e.events[i].velocity){lb+=e.events[i].out==OutBassLong;kb+=e.events[i].out==OutBassShort;ar+=e.events[i].out==OutArp;gs+=e.events[i].out==OutCounter;}}
  std::cout<<"Production LB/KB/AR/GS "<<lb<<'/'<<kb<<'/'<<ar<<'/'<<gs<<'\n';CHECK(lb>0);CHECK(kb>0);CHECK(ar>0);CHECK(gs>0);
 }
 std::cout<<"Shared independent figures: full cycles, 12 keys, transport, ownership, manual/Follow, meters and block sizes passed\n";
}
