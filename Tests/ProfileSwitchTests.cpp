#include "TestSupport.h"
#include "ScoreEngine.h"
#include <array>
#include <map>
#include <set>
#include <tuple>
#include <vector>
using namespace stromscore;
using composition::ProfileId;
struct Result {std::vector<std::tuple<int64_t,int,int,int,int>> events;std::set<unsigned> harmonies;std::set<int> bass;};
Result scenario(int genre,int from,bool stopped,int block,float swing,bool moving)
{
 Settings s;s.key=2;s.genre=genre;s.profile=static_cast<ProfileId>(from);s.policy=composition::policyForContext(s.profile,genre==GenreScore);
 s.y=.05f;s.x=.2f;s.z=.5f;s.variation=3;s.seed=3;s.melody=true;s.motif=true;s.inertia=true;s.swing=swing;
 Generator g;Transport t;t.playing=true;t.bpm=100;EventList e;Result result;std::map<int,int> ledger;int64_t sample=0;
 auto render=[&](int steps,bool collect){
  for(int step=0;step<steps;++step){
   if(moving&&collect){s.x=.5f+.45f*std::sin(step*.017);s.y=.7f+.25f*std::sin(step*.013);s.z=.5f+.45f*std::sin(step*.019);s.variation=1+(step/64)%16;}
   for(int offset=0;offset<7200;){int n=std::min(block,7200-offset);t.ppq=sample/28800.;e.clear();{NoAllocations guard;g.process(t,s,n,e);}CHECK(!e.overflow);
    CHECK(g.wendung()>=0&&(g.wendung()==kCustomWendung||g.wendung()<wendungCount(s.genre,s.profile)));
    for(int i=0;i<e.size;++i){const auto a=e.events[i];if(a.type)continue;int k=a.channel*128+a.note;
     if(a.velocity){CHECK(!ledger[k]);ledger[k]=1;if(collect&&(a.out==OutBassLong||a.out==OutBassShort))result.bass.insert(a.note%12);}else{CHECK(ledger[k]);ledger[k]=0;}
     if(collect)result.events.emplace_back(sample+a.offset,a.out,a.channel,a.note,a.velocity);}
    if(collect)result.harmonies.insert((g.chordRoot()+12)%12*100+g.chordType());sample+=n;offset+=n;}
  }};
 auto stop=[&]{t.playing=false;e.clear();g.process(t,s,1,e);for(int i=0;i<e.size;++i)if(!e.events[i].type&&!e.events[i].velocity)ledger[e.events[i].channel*128+e.events[i].note]=0;for(auto v:ledger)CHECK(!v.second);};
 render(16,false);if(stopped)stop();s.profile=static_cast<ProfileId>(1-from);s.policy=composition::policyForContext(s.profile,s.genre==GenreScore);
 if(stopped){e.clear();g.process(t,s,1,e);}t.playing=true;render(16,false); // Stay quiet after switching, too.
 s.x=.85f;s.y=.95f;s.z=1;render(128*16,true);CHECK(result.harmonies.size()>1);CHECK(result.bass.size()>1);
 // Restart and a loop/seek return must keep a real selection, never a fabricated fallback.
 stop();t.playing=true;sample=32*28800;render(32,true);sample=16*28800;render(32,true);sample=16*28800;render(32,true);stop();
 return result;
}
int main()
{
 for(int genre:{GenreScore,GenrePopRock})for(int from:{0,1})for(bool stopped:{false,true})for(bool moving:{false,true})
 {
  const auto a=scenario(genre,from,stopped,512,0,moving),b=scenario(genre,from,stopped,127,0,moving);
  CHECK(a.events==b.events&&a.harmonies==b.harmonies);const auto c=scenario(genre,from,stopped,512,.35f,moving),d=scenario(genre,from,stopped,8192,.35f,moving);CHECK(c.events==d.events);
 }
 std::cout<<"Profile switches: 64 long renders with valid selection, harmonic development, transport, swing and exact block equality passed\n";
}
