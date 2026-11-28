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
namespace stromscore {struct ExecutionTestAccess {
 static bool bassPlacement(Generator& g,const Settings& s,const LayerFigure& source,int& placement){g.current=wendungIndex(GenreScore,static_cast<WendungId>(30001),s.profile);g.cur=&s;const bool result=g.layerFits(source,Tick{},s,OutBassLong,&placement);g.cur=nullptr;return result;}
 static int motifInSourceContext(Generator& g,Settings s,const AuthoredMotifSource& source,int output){
  g.voices={};g.current=kCustomWendung;g.custom={};g.custom.n=2;g.custom.coloration=ChordColoration::protectedColor;
  for(int bar=0;bar<2;++bar){bool found=false;for(int root=0;root<12&&!found;++root)for(int type=0;type<(int)(sizeof(kShapes)/sizeof(*kShapes))&&!found;++type){unsigned mask=0;for(int n=0;n<kShapes[type].n;++n)mask|=pitchBit(root+kShapes[type].iv[n]);if(mask==source.harmony[bar]){g.custom.ch[bar]={root,type,4,source.bass[bar]};found=true;}}CHECK(found);}
  s.policy.authoredSources=&source;s.policy.authoredCount=1;g.cur=&s;const auto result=g.authoredMotif(g.locate(Tick{}),s,output);g.cur=nullptr;return result.source?result.source->id:0;
 }
};}
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


 // An explicitly shared long/short destination is one bass performer, not two
 // conflicting roles. Physical notes remain monophonic and Stop balances them.
 for(int shared=1;shared<=2;++shared)for(int path=0;path<3;++path){auto s=settings(.15f,path==0?.25f:.85f,path==1?.85f:.2f);s.channel[OutBassShort]=s.channel[OutBassLong];if(shared==2)s.channel[OutPadShort]=s.channel[OutPadLong];
  const auto rows=render(s,127,32);CHECK(rows==render(s,2048,32));int bass=0,open=0,peak=0;
  for(auto r:rows){auto [at,o,ch,n,v]=r;if(ch!=s.channel[OutBassLong])continue;if(v){++bass;++open;peak=std::max(peak,open);}else --open;}
  CHECK(bass>0&&peak<=1&&open==0);
 }
 // No registered effect figure may steal the existing fixed ST trigger path.
 {auto s=settings(.5f,.85f,.9f);int st=0;for(auto r:render(s,512,64))if(std::get<1>(r)==OutStich&&std::get<4>(r)){CHECK(std::get<3>(r)==36);++st;}CHECK(st>0);}
 // Source anchors below a role threshold remain preferences, not an impossible
 // admission requirement once the role is active. Exact harmony is still required.
 for(const auto& source:herrmann::motifs)for(int key=0;key<12;++key){auto s=settings(source.x,.85f,source.z);s.key=key;s.melody=true;s.scene=false;
  Generator g;Transport t;t.playing=true;EventList e;g.process(t,s,1,e);
  CHECK(ExecutionTestAccess::motifInSourceContext(g,s,source,OutCounter)==source.id);
  CHECK(ExecutionTestAccess::motifInSourceContext(g,s,source,OutMelody)==source.id);
 }
 // Actual hearing-test setup: separate channels3/4, minus two octaves,
 // C0..G3 in this GUI's naming convention = MIDI24..67, AFTER the octave.
 for(int key=0;key<12;++key){auto s=settings(.5f,.85f,.8f);s.key=key;s.octave[kBass]=-2;s.rangeOn[1]=true;s.rangeLo[1]=24;s.rangeHi[1]=67;
  auto rows=render(s,127,32);CHECK(rows==render(s,2048,32));int count=0;for(auto r:rows){auto [at,o,ch,n,v]=r;if(v&&(o==OutBassLong||o==OutBassShort)){CHECK(n>=24&&n<=67);++count;}}CHECK(count>0);
 }
 // The C/B neighbour figure crosses the lower range boundary: a single
 // common octave shift must retain the semitone, not fold each note separately.
 {auto s=settings();s.key=0;s.octave[kBass]=-2;s.rangeOn[1]=true;s.rangeLo[1]=24;s.rangeHi[1]=67;Generator g;Transport t;t.playing=true;EventList e;g.process(t,s,1,e);
  const LayerFigure* source=nullptr;for(const auto& f:herrmann::figures)if(f.id==81030)source=&f;CHECK(source);int placement=0;CHECK(ExecutionTestAccess::bassPlacement(g,s,*source,placement));CHECK(placement==24);s.rangeHi[1]=24;CHECK(!ExecutionTestAccess::bassPlacement(g,s,*source,placement));
 }
 // An authored entry impulse must not bypass a manual held-bass choice.
 {auto s=settings();auto index=wendungIndex(GenreScore,static_cast<WendungId>(70057),s.profile);const auto w=wendungAt(GenreScore,index,s.profile);s.x=w.x;s.y=w.y;s.z=w.z;s.bassPattern=BassHeld;s.follow[kBass]=false;for(int v=1;v<=16;++v){s.variation=v;if(Generator::pick(s,0)==index)break;}int shortBass=0;for(auto r:render(s,512,8))if(std::get<1>(r)==OutBassShort&&std::get<4>(r))++shortBass;CHECK(shortBass==0);}
 // Authored harmonic bass lanes also retain their chromatic contour when a
 // whole phrase crosses the user's lower range edge. No scalar octave zigzag.
 {auto s=settings();auto index=wendungIndex(GenreScore,static_cast<WendungId>(70007),s.profile);const auto w=wendungAt(GenreScore,index,s.profile);s.x=w.x;s.y=w.y;s.z=w.z;s.key=2;s.octave[kBass]=-2;s.rangeOn[1]=true;s.rangeLo[1]=24;s.rangeHi[1]=67;s.policy.layers.count=0;
  for(int v=1;v<=16;++v){s.variation=v;if(Generator::pick(s,0)==index)break;}std::vector<int> pitches;for(auto r:render(s,127,8))if(std::get<1>(r)==OutBassLong&&std::get<4>(r))pitches.push_back(std::get<3>(r));CHECK((pitches==std::vector<int>{38,37,36,35}));
  s.policy=policyForContext(s.profile,true);std::vector<int> actual;for(auto r:render(s,127,8))if(std::get<1>(r)==OutBassLong&&std::get<4>(r)){const int n=std::get<3>(r);if(actual.empty()||actual.back()!=n)actual.push_back(n);}CHECK((actual==std::vector<int>{38,37,36,35}));
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
 // Low XYZ is harmonic stillness, not exclusive ownership of a silent pad.
 for(float x:{0.f,.02f,.05f,.08f,.1f,.12f,.15f,.2f})for(float y:{0.f,.02f,.05f,.08f,.1f,.12f,.15f,.2f})for(float z:{0.f,.02f,.05f,.08f,.1f,.12f,.15f,.2f}){
  auto s=settings(x,y,z);int pad=0;for(auto r:render(s,512,4))if(std::get<1>(r)==OutPadLong&&std::get<4>(r))++pad;CHECK(pad>0);
 }
 for(int key=0;key<12;++key){auto s=settings(0,0,0);s.key=key;s.octave[kFlaeche]=-1;s.rangeOn[0]=true;s.rangeLo[0]=48;s.rangeHi[0]=84;
  auto rows=render(s,127,32,1);CHECK(rows==render(s,2048,32,1));int pad=0;for(auto r:rows)if(std::get<4>(r)){CHECK(std::get<1>(r)==OutPadLong);CHECK(std::get<3>(r)>=48&&std::get<3>(r)<=84);++pad;}CHECK(pad>0);
 }
 {auto s=settings(0,0,0);int pad=0;for(auto r:render(s,512,64))if(std::get<4>(r)){CHECK(std::get<1>(r)==OutPadLong);++pad;}CHECK(pad>0&&pad<=6);s.mute[kFlaeche]=true;CHECK(render(s,512,8).empty());}
 // Normal automatic choices, including the user's C3..D5 = MIDI60..86.
 // No forced catalog entry and no autonomous member detached from a paired group.
 for(int key=0;key<12;++key){auto s=settings(.5f,.85f,.8f);s.key=key;s.variation=3;s.variety=.5f;s.rangeOn[2]=true;s.rangeLo[2]=60;s.rangeHi[2]=86;
  int arp=0;auto rows=render(s,127,64);CHECK(rows==render(s,2048,64));for(auto r:rows)if(std::get<1>(r)==OutArp&&std::get<4>(r)){CHECK(std::get<3>(r)>=60&&std::get<3>(r)<=86);++arp;}CHECK(arp>0);
 }
 // Independent second harmonic component is transposed as a whole into the
 // instrument range, without changing any component tone class or interval.
 for(int key=0;key<12;++key){auto s=settings();const auto index=wendungIndex(GenreScore,static_cast<WendungId>(70051),s.profile);const auto w=wendungAt(GenreScore,index,s.profile);s.x=w.x;s.y=w.y;s.z=w.z;s.key=key;s.variety=0;s.rangeOn[2]=true;s.rangeLo[2]=60;s.rangeHi[2]=86;
  for(int v=1;v<=16;++v){s.variation=v;if(Generator::pick(s,0)==index)break;}int arp=0;for(auto r:render(s,512,8))if(std::get<1>(r)==OutArp&&std::get<4>(r)){const int n=std::get<3>(r);CHECK(n>=60&&n<=86);CHECK(pitchBit(n)&transposePitchMask(pitchBit(78)|pitchBit(81)|pitchBit(85),key));++arp;}CHECK(arp>0);
 }
 std::cout<<"Herrmann shared layers: sources, 12 keys, independent cycles, explicit functions, transport, ownership, manual/Follow and block sizes passed\n";
}
