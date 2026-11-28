#include "TestSupport.h"
#include "ScoreEngine.h"
#include <vector>
#include <tuple>
#include <map>
using namespace stromscore;
using namespace stromscore::composition;
using namespace stromscore::musicaltime;
using Row=std::tuple<int64_t,int,int,int,int>;
static Settings settings(float x=.3f,float y=.7f,float z=.5f){Settings s;s.profile=ProfileId::bernardHerrmann;s.policy=policyForContext(s.profile,true);s.x=x;s.y=y;s.z=z;s.scene=false;s.sceneBars=0;s.variety=0;s.stichFixed=true;s.motif=true;s.melody=false;return s;}
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
 // Every admitted harmonic source, including all component/high-pedal cases.
 for(const auto& b:herrmann::harmonies){auto s=settings();const int index=wendungIndex(GenreScore,static_cast<WendungId>(b.harmonyId),s.profile);CHECK(index>=0);
  auto w=wendungAt(GenreScore,index,s.profile);s.x=w.x;s.y=w.y;s.z=w.z;bool found=false;
  for(int v=1;v<=16;++v){s.variation=v;if(Generator::pick(s,0)==index){found=true;break;}}CHECK(found);
  for(int key:{0,11}){s.key=key;std::cerr<<"CHECK SOURCE "<<b.sourceId<<" KEY "<<key<<"\n";auto rows=render(s,127,8);CHECK(rows==render(s,2048,8));
   std::map<std::pair<int,int>,std::pair<int64_t,int>> open;std::array<int,9> sounding{};
   for(auto row:rows){const auto [at,o,ch,n,velocity]=row;if(velocity){open[{ch,n}]={at,o};++sounding[o];if(o==OutPadLong)CHECK(sounding[o]<=6);if(o==OutBassLong||o==OutBassShort||o==OutArp)CHECK(sounding[o]<=1);}
    else{auto previous=open.at({ch,n});CHECK(at>previous.first);--sounding[previous.second];open.erase({ch,n});}}
   CHECK(open.empty());
  }
 }

 for(const auto& f:herrmann::figures)CHECK(valid(f));
 CHECK(herrmannPolicy.layers.enabled&&herrmannPolicy.authoredCount==22);
 CHECK(permittedTone({'A',-1},60,1,0,0));CHECK(!permittedTone({'F',-1},61,1,0,0));
 CHECK(permittedTone({'F',-1},61,1,0,2));CHECK(!permittedTone({'V',60},61,1,0,2,false));CHECK(permittedTone({'V',60},61,1,0,2,true));
 for(int key=0;key<12;++key){auto s=settings();s.key=key;CHECK(render(s,127,8)==render(s,1024,8));}
 for(double bpm:{60.,137.,180.}){auto s=settings();auto a=render(s,127,8,0,bpm),b=render(s,2048,8,0,bpm);CHECK(a.size()==b.size());for(size_t i=0;i<a.size();++i){auto x=a[i],y=b[i];auto ta=std::get<0>(x),tb=std::get<0>(y);CHECK(std::abs(ta-tb)<=1);CHECK(std::llround(ta*960./(48000.*60/bpm))==std::llround(tb*960./(48000.*60/bpm)));std::get<0>(x)=std::get<0>(y)=0;CHECK(x==y);}}
 for(int num:{3,4,5,7})for(float swing:{0.f,.6f}){auto s=settings();s.meterNum=num;s.meterDen=num==4?4:8;s.swing=swing;CHECK(render(s,127,8,1)==render(s,2048,8,1));}
 for(int mode=0;mode<8;++mode){auto s=settings();if(mode==0)s.follow[kBass]=false;if(mode==1)s.bassPattern=BassQuarter;if(mode==2)s.arpFigure=ArpDown;if(mode==3)s.mute[kBass]=true;if(mode==4)s.solo[kArp]=true;if(mode==5)s.channel[OutArp]=s.channel[OutPadLong];if(mode==6)s.melody=true;if(mode==7)s.padPattern=PadPulse;CHECK(render(s,127,8)==render(s,1024,8));}
 for(float x:{.1f,.5f,.9f})for(float y:{.2f,.8f})for(float z:{.2f,.8f}){auto s=settings(x,y,z);CHECK(render(s,127,16)==render(s,2048,16));}
 // Isolated production component plan: same six pitch classes, three exact
 // register/synchrony states. No synthetic post-render note construction.
 {auto s=settings();const int index=wendungIndex(GenreScore,static_cast<WendungId>(70060),s.profile);auto w=wendungAt(GenreScore,index,s.profile);s.x=w.x;s.y=w.y;s.z=w.z;s.key=0;s.policy.layers.count=0;
  s.mute[kBass]=s.mute[kAkzent]=s.mute[kGegenstimme]=true;
  for(int v=1;v<=16;++v){s.variation=v;if(Generator::pick(s,0)==index)break;}
  auto rows=render(s,127,16);std::vector<int> fused;bool high=false,middle=false;
  for(auto row:rows){auto [at,o,ch,n,vel]=row;if(!vel)continue;if(o==OutArp&&at==28800&&n==83)high=true;if(o==OutArp&&at==9*28800&&n==71)middle=true;if(o==OutPadLong&&at==16*28800)fused.push_back(n);}
  std::sort(fused.begin(),fused.end());CHECK(high&&middle);CHECK((fused==std::vector<int>{47,48,50,51,54,55}));
 }
 // Simultaneous low and high pedal: one attack each over16 bars, not repeated
 // on chord/phrase boundaries, both released by Stop.
 {auto s=settings();const int index=wendungIndex(GenreScore,static_cast<WendungId>(70068),s.profile);auto w=wendungAt(GenreScore,index,s.profile);s.x=w.x;s.y=w.y;s.z=w.z;s.key=0;s.policy.layers.count=0;
  for(int v=1;v<=16;++v){s.variation=v;if(Generator::pick(s,0)==index)break;}
  auto rows=render(s,512,16);int low=0,high=0;for(auto r:rows)if(std::get<4>(r)){low+=std::get<1>(r)==OutBassLong&&std::get<3>(r)==36;high+=std::get<1>(r)==OutPadLong&&std::get<3>(r)==90;}CHECK(low==1&&high==1);
 }
 // Static source geometry preserves all components, not a merged catalog chord.
 const HarmonicLayerBinding* split=nullptr;for(const auto& b:herrmann::harmonies)if(b.sourceId==53)split=&b;
 CHECK(split&&split->upperRoot==11&&!split->fused);
 CHECK(split->upperNotes[0]==71&&split->upperNotes[2]==78);
 // B24 is the complete nine-bar tone/rhythm cycle (not a three-bar reset).
 bool full=false;for(const auto& f:herrmann::figures)if(f.id==81024){CHECK(f.period==36*quarter&&f.count==48);full=true;}CHECK(full);
 // Common motif functions retain their explicit directed resolution metadata.
 for(const auto& m:herrmann::motifs)for(int i=0;i<m.count;++i)if(m.functions[i]=='V'){bool found=false;for(int j=i+1;j<m.count;++j)found|=m.pitches[j]==m.targets[i];CHECK(found);}
 {Generator g;auto s=settings();Transport t;t.playing=true;t.bpm=100;EventList e;std::map<std::pair<int,int>,int> open;
  for(int block=0;block<2000;++block){if(block%200==0){s.profile=block%400==0?ProfileId::neutral:ProfileId::bernardHerrmann;s.genre=block>=1200&&block<1600?GenrePopRock:GenreScore;s.policy=policyForContext(s.profile,s.genre==GenreScore);s.y=.01f;}if(block%200==20)s.y=.8f;
   t.ppq=block*512/28800.;e.clear();{NoAllocations n;g.process(t,s,512,e);}for(int i=0;i<e.size;++i){auto r=e.events[i];if(!r.type){auto& n=open[{r.channel,r.note}];n+=r.velocity?1:-1;CHECK(n==0||n==1);}}}
  t.playing=false;e.clear();g.process(t,s,512,e);for(int i=0;i<e.size;++i)if(!e.events[i].type)open[{e.events[i].channel,e.events[i].note}]+=e.events[i].velocity?1:-1;for(auto n:open)CHECK(n.second==0);
 }
 std::cout<<"Herrmann shared layers: sources, 12 keys, independent cycles, explicit functions, transport, ownership, manual/Follow and block sizes passed\n";
}
