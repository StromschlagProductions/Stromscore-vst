#include "TestSupport.h"
#include "ScoreEngine.h"
#include <map>
#include <vector>
#include <tuple>
#include <iostream>
using namespace stromscore;
using Row=std::tuple<int64_t,int,int,int,int,int>;
std::vector<Row> render(Settings s,int block=512,int route=0,int bars=32)
{
 Generator g;Transport t;t.playing=true;EventList es;std::vector<Row> result;std::map<std::pair<int,int>,int> ledger;int lead=0,dialog=0;int64_t previous=0;
 const int64_t bar=Meter::from(s.meterNum,s.meterDen).len*6000LL,total=bars*bar,segment=total/4;
 auto collect=[&](int64_t base){for(int i=0;i<es.size;++i){auto e=es.events[i];auto at=base+e.offset;CHECK(!(lead&&dialog&&at>previous));previous=at;
  result.emplace_back(at,e.out,e.channel,e.note,e.velocity,e.type);if(e.type)continue;auto key=std::make_pair(e.channel,e.note);
  if(e.velocity){CHECK(!ledger[key]);ledger[key]=1;}else{CHECK(ledger[key]);ledger[key]=0;}
  if(e.out==OutMelody)lead+=e.velocity?1:-1;if(e.out==OutCounter)dialog+=e.velocity?1:-1;CHECK(lead>=0&&lead<=1&&dialog>=0&&dialog<=2);
 }};
 for(int64_t at=0;at<total;){auto local=at%segment;int part=at/segment;
  if(route==2&&part==3&&local==0){Transport stop;es.clear();g.process(stop,s,1,es);collect(at);}
  t.ppq=(route?(part==0?0:part==1?96:part==2?16:0):part*segment/24000.)+local/24000.;
  auto n=std::min<int64_t>({block,total-at,segment-local});es.clear();{NoAllocations guard;g.process(t,s,n,es);}CHECK(!es.overflow);collect(at);at+=n;
 }
 Transport stop;es.clear();g.process(stop,s,512,es);collect(total);for(auto v:ledger)CHECK(v.second==0);CHECK(!lead&&!dialog);return result;
}
int ons(const std::vector<Row>& r,int out){int n=0;for(auto e:r)n+=std::get<1>(e)==out&&std::get<4>(e)>0&&!std::get<5>(e);return n;}
Settings barry(){Settings s;s.profile=composition::ProfileId::johnBarry;s.policy=composition::policyForContext(s.profile,true);s.variety=0;s.key=0;return s;}
int main()
{
 // Every canonical entry really renders; protect authored pad/Arp classes for 12 keys and both Follow states.
 int checks=0;
 for(int index=0;index<46;++index)for(int key=0;key<12;++key)for(bool follow:{false,true})
 {
  auto s=barry();auto w=wendungAt(s.genre,index,s.profile);s.x=w.x;s.y=w.y;s.z=w.z;s.key=key;s.follow[0]=s.follow[1]=s.follow[2]=follow;
  s.solo[kFlaeche]=s.solo[kArp]=true;s.layerIntensity[kArp]=1;s.padPattern=PadHeld;s.arpFigure=ArpCircle;s.arpRate=RateEighth;
  Generator g;Transport t;t.playing=true;EventList es;int heard=0;
  for(int step=0;step<128;++step){t.ppq=step*.25;es.clear();{NoAllocations guard;g.process(t,s,6000,es);}CHECK(!es.overflow&&g.wendung()==index);
   int slot=0,bar=step/16,end=w.ch[0].bars;while(bar>=end&&slot+1<w.n)end+=w.ch[++slot].bars;
   auto c=w.ch[follow?slot:0];if(!follow)c.root=0;unsigned mask=0;for(int i=0;i<kShapes[c.type].n;++i)mask|=composition::pitchBit(key+c.root+kShapes[c.type].iv[i]);
   for(int i=0;i<es.size;++i){auto e=es.events[i];if(!e.type&&e.velocity){CHECK(e.out==OutPadLong||e.out==OutArp);CHECK(mask&composition::pitchBit(e.note));++heard;}}
  }CHECK(heard>0);++checks;
  // Actual authored slash/pedal classes, separately from harmonic voices; Follow OFF retains the tonic.
  s.solo[kFlaeche]=s.solo[kArp]=false;s.solo[kBass]=true;s.bassPattern=BassHeld;
  Generator bass;heard=0;
  for(int step=0;step<128;++step){t.ppq=step*.25;es.clear();{NoAllocations guard;bass.process(t,s,6000,es);}CHECK(!es.overflow);
   int slot=0,bar=step/16,end=w.ch[0].bars;while(bar>=end&&slot+1<w.n)end+=w.ch[++slot].bars;
   const auto c=w.ch[slot];const auto pitch=(key+(follow?(c.bass>=0?c.bass:c.root):0))%12;
   for(int i=0;i<es.size;++i){auto e=es.events[i];if(!e.type&&e.velocity){CHECK(e.out==OutBassLong&&e.note%12==pitch);++heard;}}
  }CHECK(heard>0);
 }
 auto s=barry();s.custom=true;s.customChords[0]={0,MinMaj7,8};s.x=.2f;s.y=1;s.z=0;s.solo[kArp]=true;
 auto dark=s;dark.scene=true;CHECK(Generator::autoEntry(dark)==EntryArp);dark.y=.2f;dark.solo[kArp]=false;CHECK(Generator::autoEntry(dark)==EntryPad);
 auto limited=render(s);CHECK(ons(limited,OutArp)>0&&ons(limited,OutArp)<=32*8);
 auto faster=s;faster.z=1;CHECK(ons(render(faster),OutArp)>ons(limited,OutArp));
 // Explicit user figure/rate overrides the Auto policy. Same harmony, same expression, exact events.
 s.arpFigure=ArpCircle;s.arpRate=RateSixteenth;auto manual=render(s);s.policy=composition::neutralFreePolicy;CHECK(render(s)==manual);
 // Real profile voices, motivational switches, bounded register, Swing and transport.
 s=barry();s.x=.2f;s.y=.65f;s.z=.5f;s.melody=true;s.motif=true;s.swing=.3f;
 for(int route:{0,1,2}){auto a=render(s,512,route);CHECK(ons(a,OutMelody)>0||ons(a,OutCounter)>0);for(int block:{127,8192})CHECK(render(s,block,route)==a);}
 for(auto meter:{std::pair<int,int>{3,4},{6,8},{3,8},{5,8},{7,8}}){s.meterNum=meter.first;s.meterDen=meter.second;auto a=render(s);auto b=render(s,127);CHECK(a.size()==b.size());for(size_t i=0;i<a.size();++i){auto x=a[i],y=b[i];CHECK(std::abs(std::get<0>(x)-std::get<0>(y))<=1);std::get<0>(x)=std::get<0>(y);CHECK(x==y);}}
 s.meterNum=4;s.meterDen=4;s.melodyMotif=s.motif=false;CHECK(!render(s).empty());
 s.melody=false;CHECK(ons(render(s),OutMelody)==0);s.melody=true;s.mute[kMelodie]=true;CHECK(ons(render(s),OutMelody)==0);
 s.solo[kMelodie]=true;s.mute[kMelodie]=false;auto solo=render(s);CHECK(ons(solo,OutMelody)>0);for(auto e:solo)CHECK(std::get<1>(e)==OutMelody);
 s.rangeLo[6]=s.rangeHi[6]=61;s.custom=true;s.customChords[0]={0,MinMaj7,8};CHECK(ons(render(s),OutMelody)==0);
 // Switching material views cannot leave old gates or stale pool indices.
 Generator g;EventList es;Transport t;t.playing=true;std::map<std::pair<int,int>,int> held;
 for(int step=0;step<512;++step){Settings state;state.melody=true;state.motif=true;state.y=.8f;state.profile=step%128<64?composition::ProfileId::johnBarry:composition::ProfileId::neutral;state.policy=composition::policyForContext(state.profile,true);t.ppq=step*.25;es.clear();g.process(t,state,6000,es);
  CHECK(g.wendung()>=0&&g.wendung()<wendungCount(state.genre,state.profile));for(int i=0;i<es.size;++i){auto e=es.events[i];if(e.type)continue;auto k=std::make_pair(e.channel,e.note);if(e.velocity){CHECK(!held[k]);held[k]=1;}else{CHECK(held[k]);held[k]=0;}}}
 Transport stop;es.clear();g.process(stop,Settings{},512,es);for(int i=0;i<es.size;++i){auto e=es.events[i];if(!e.type&&!e.velocity)held[{e.channel,e.note}]=0;}for(auto v:held)CHECK(v.second==0);
 std::cout<<checks<<" authored-colour renders; policy, controls, independent roles, MIDI ledger and transport passed\n";
}
