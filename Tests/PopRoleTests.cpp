#include "TestSupport.h"
#include "ScoreEngine.h"
#include <vector>
#include <tuple>
#include <map>
using namespace stromscore;
using Row=std::tuple<int64_t,int,int,int,int>;
struct Render {std::vector<Row> rows;double overlap=0;bool dialogMaterial=false;int adaptations=0;int64_t leadPublished=-1;composition::RememberedMotif leadMemory,dialogMemory;};
Render render(Settings s,int block=512,int route=0,int changedHarmony=0)
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
  const auto segment=total/3;auto boundary=std::min(total,(at/segment+1)*segment);
  if(changedHarmony==2&&at<segment/4)boundary=std::min(boundary,segment/4);
  auto n=static_cast<int>(std::min<int64_t>(block,boundary-at));host.ppq=at/24000.;
  if(route==1)host.ppq=(at%segment)/24000.; // Repeated host loop with warm history.
  if(route==2)host.ppq+=at<segment?0:at<2*segment?12:-12; // Forward then backward seek.
  if(route==3&&at>0&&at%segment==0){Transport stop;events.clear();g.process(stop,s,1,events);collect(at);}
  if(route==3)host.ppq=(at%segment)/24000.; // Scene restart, not just a warm loop.
  if(changedHarmony&&at>=(changedHarmony==2?segment/4:segment)){s.customChords[0]={0,Min,2};s.customChords[1]={6,Min,2};s.customChords[2]={1,Min,2};s.customChords[3]={7,Min,2};}
  events.clear();
  {NoAllocations guard;g.process(host,s,n,events);}CHECK(!events.overflow);collect(at);if(result.leadPublished<0&&g.rememberedMotif(OutMelody).complete)result.leadPublished=at;
  if(changedHarmony&&at%segment==0){const auto plan=g.inspectMotifOccurrence(static_cast<long long>(host.ppq*4),s,OutMelody);result.adaptations+=plan.figure.harmonicRealization;}
  at+=n;}
 result.dialogMaterial=g.rememberedMotif(OutCounter).complete;result.leadMemory=g.rememberedMotif(OutMelody);result.dialogMemory=g.rememberedMotif(OutCounter);
 Transport stop;events.clear();g.process(stop,s,512,events);collect(total);
 for(auto value:physical)CHECK(value.second==0);CHECK(active[0]==0&&active[1]==0);return result;
}
std::vector<Row> part(const Render& r,int output){std::vector<Row> v;for(auto row:r.rows)if(std::get<1>(row)==output)v.push_back(row);return v;}
int ons(const Render& r,int output){int n=0;for(auto row:r.rows)n+=std::get<1>(row)==output&&std::get<3>(row)>0;return n;}
Settings settings(){Settings s;s.custom=true;s.customChords[0]={0,Maj7,8};s.key=0;s.x=.5f;s.y=.85f;s.motif=true;s.melody=true;for(int i=0;i<4;++i)s.mute[i]=true;return s;}
int main()
{
 auto s=settings();s.genre=GenrePopRock;s.z=.4f;auto both=render(s);
 CHECK(ons(both,OutMelody)>0&&ons(both,OutCounter)>0&&both.overlap==0);
 CHECK(std::abs(both.leadPublished-20*48000)<512);
 CHECK(both.leadMemory.complete&&both.dialogMemory.complete&&both.leadMemory.identity!=both.dialogMemory.identity);
 auto alone=s;alone.melody=false;auto dialog=render(alone);CHECK(ons(dialog,OutMelody)==0&&ons(dialog,OutCounter)>0);
 auto impossible=s;impossible.rangeLo[6]=impossible.rangeHi[6]=61;auto noPlan=render(impossible);CHECK(ons(noPlan,OutMelody)==0);CHECK(part(noPlan,OutCounter)==part(dialog,OutCounter));
 auto muted=s;muted.mute[kMelodie]=true;CHECK(part(render(muted),OutCounter)==part(dialog,OutCounter));
 auto solo=s;solo.solo[kGegenstimme]=true;CHECK(part(render(solo),OutCounter)==part(dialog,OutCounter));
 solo=s;solo.solo[kMelodie]=true;auto lead=render(solo);CHECK(ons(lead,OutMelody)>0&&ons(lead,OutCounter)==0);solo.mute[kMelodie]=true;CHECK(ons(render(solo),OutMelody)>0);
 auto all=s;for(int i=0;i<4;++i)all.mute[i]=false;all.solo[kMelodie]=true;
 auto foregroundOnly=render(all);CHECK(ons(foregroundOnly,OutMelody)>0&&ons(foregroundOnly,OutCounter)==0);
 for(const auto& row:foregroundOnly.rows)CHECK(std::get<1>(row)==OutMelody);
 all.melody=false;auto inactiveSolo=render(all);CHECK(ons(inactiveSolo,OutMelody)==0&&ons(inactiveSolo,OutCounter)>0);
 bool accompaniment=false;for(const auto& row:inactiveSolo.rows)accompaniment|=std::get<1>(row)<7&&std::get<3>(row)>0;CHECK(accompaniment);
 auto below=s;below.layerIntensity[kMelodie]=-1;CHECK(part(render(below),OutCounter)==part(dialog,OutCounter));
 auto free=s;free.melodyMotif=false;free.motif=false;auto lines=render(free);
 CHECK(ons(lines,OutMelody)>0&&ons(lines,OutCounter)>0&&lines.overlap==0&&!lines.leadMemory.complete);
 auto quiet=alone;quiet.y=.55f;quiet.z=.1f;auto standard=render(quiet);quiet.policy.popRoles.sparseBelow=.6f;
 auto sparse=render(quiet);CHECK(ons(sparse,OutCounter)<ons(standard,OutCounter));
 for(int route:{0,1,2,3}){auto reference=render(s,512,route);CHECK(reference.overlap==0);
  for(int block:{127,8192}){auto other=render(s,block,route);CHECK(other.rows==reference.rows);CHECK(other.overlap==0);}}
 for(int numerator:{3,5,7})for(float swing:{0.f,.5f}){auto odd=s;odd.meterNum=numerator;odd.meterDen=8;odd.swing=swing;
  auto reference=render(odd,512);auto other=render(odd,127);CHECK(reference.overlap==0&&other.overlap==0);CHECK(reference.rows.size()==other.rows.size());
  for(size_t i=0;i<reference.rows.size();++i){auto a=reference.rows[i],b=other.rows[i];CHECK(std::abs(std::get<0>(a)-std::get<0>(b))<=1);std::get<0>(a)=std::get<0>(b);CHECK(a==b);}}
 std::cout<<"Pop roles: independent melody, cycle breathing, motif controls, policy, transport, Swing and physical ledger passed\n";
}
