#include "TestSupport.h"
#include "ScoreEngine.h"
#include <vector>
#include <tuple>
#include <map>
using namespace stromscore;
using Row=std::tuple<int64_t,int,int,int,int>;
struct Render {std::vector<Row> rows;double overlap=0;bool dialogMaterial=false;};
Render render(Settings s,int block=512,int route=0)
{
 Generator g;EventList events;Transport host;host.playing=true;Render result;
 std::map<std::pair<int,int>,int> physical;int active[2]{};int64_t previous=0;
 auto collect=[&](int64_t base){for(int i=0;i<events.size;++i){auto e=events.events[i];if(e.type)continue;
  const int64_t at=base+e.offset;if(active[0]&&active[1])result.overlap+=at-previous;previous=at;
  const auto key=std::make_pair(e.channel,e.note);if(e.velocity){CHECK(!physical[key]);physical[key]=1;}else{CHECK(physical[key]);physical[key]=0;}
  if(e.out==OutMelody||e.out==OutCounter)active[e.out==OutMelody?0:1]+=e.velocity?1:-1;
  result.rows.emplace_back(at,e.out,e.note,e.velocity,e.channel);
 }};
 constexpr int64_t total=96LL*96000;
 for(int64_t at=0;at<total;){
  const auto segment=total/3;const auto boundary=std::min(total,(at/segment+1)*segment);
  auto n=static_cast<int>(std::min<int64_t>(block,boundary-at));host.ppq=at/24000.;
  if(route==1)host.ppq=(at%segment)/24000.; // Repeated host loop with warm history.
  if(route==2)host.ppq+=at<segment?0:at<2*segment?12:-12; // Forward then backward seek.
  if(route==3&&at>0&&at%segment==0){Transport stop;events.clear();g.process(stop,s,1,events);collect(at);}
  if(route==3)host.ppq=(at%segment)/24000.; // Scene restart, not just a warm loop.
  events.clear();
  {NoAllocations guard;g.process(host,s,n,events);}CHECK(!events.overflow);collect(at);at+=n;}
 result.dialogMaterial=g.rememberedMotif(OutCounter).complete;
 Transport stop;events.clear();g.process(stop,s,512,events);collect(total);
 for(auto value:physical)CHECK(value.second==0);CHECK(active[0]==0&&active[1]==0);return result;
}
std::vector<Row> part(const Render& r,int output){std::vector<Row> v;for(auto row:r.rows)if(std::get<1>(row)==output)v.push_back(row);return v;}
int ons(const Render& r,int output){int n=0;for(auto row:r.rows)n+=std::get<1>(row)==output&&std::get<3>(row)>0;return n;}
Settings settings(){Settings s;s.custom=true;s.customChords[0]={0,Maj7,8};s.key=0;s.x=.5f;s.y=.85f;s.motif=true;s.melody=true;for(int i=0;i<4;++i)s.mute[i]=true;return s;}
int main()
{
 auto s=settings();auto both=render(s);CHECK(ons(both,OutMelody)>0&&ons(both,OutCounter)>0);CHECK(both.overlap==0);
 auto lead=s;lead.mute[kGegenstimme]=true;auto onlyLead=render(lead);CHECK(part(both,OutMelody)==part(onlyLead,OutMelody));
 auto absent=s;absent.rangeLo[6]=absent.rangeHi[6]=61;auto noPlan=render(absent);
 CHECK(ons(noPlan,OutMelody)==0);CHECK(ons(noPlan,OutCounter)>0);CHECK(noPlan.dialogMaterial);
 auto dialog=s;dialog.melody=false;auto onlyDialog=render(dialog);CHECK(part(noPlan,OutCounter)==part(onlyDialog,OutCounter));
 auto free=s;free.melodyMotif=false;free.motif=false;auto freeBoth=render(free);free.mute[kGegenstimme]=true;auto freeLead=render(free);
 CHECK(part(freeBoth,OutMelody)==part(freeLead,OutMelody));CHECK(freeBoth.overlap==0);
 for(int mode=0;mode<3;++mode){auto control=s;if(mode==0)control.mute[kMelodie]=true;if(mode==1)control.solo[kGegenstimme]=true;if(mode==2)control.layerIntensity[kMelodie]=-1;
  auto r=render(control);CHECK(ons(r,OutMelody)==0);CHECK(part(r,OutCounter)==part(onlyDialog,OutCounter));}
 for(int block:{127,1024,8192}){auto other=render(s,block);CHECK(other.rows==both.rows);CHECK(other.overlap==0);}
 for(int route:{1,2,3}){auto reference=render(s,512,route);CHECK(reference.overlap==0);
  for(int block:{127,1024,8192}){auto other=render(s,block,route);CHECK(other.rows==reference.rows);CHECK(other.overlap==0);}}
 for(float swing:{.3f,.7f}){auto swung=s;swung.swing=swing;auto r=render(swung);CHECK(r.overlap==0);auto other=render(swung,127);CHECK(other.rows.size()==r.rows.size());
  for(size_t i=0;i<r.rows.size();++i){auto a=r.rows[i],b=other.rows[i];CHECK(std::abs(std::get<0>(a)-std::get<0>(b))<=1);std::get<0>(a)=std::get<0>(b);CHECK(a==b);}}
 std::cout<<"Playable Score foreground windows, independent dialogue, Mute/Solo/thresholds, no overlap and block determinism passed\n";
}
