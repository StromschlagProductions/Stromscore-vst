#include "TestSupport.h"
#include "ScoreEngine.h"
#include <tuple>
#include <vector>
#include <map>
#include <cstring>
using namespace stromscore;using namespace stromscore::composition;using namespace stromscore::musicaltime;
namespace stromscore {struct ExecutionTestAccess {
 static void harmony(Generator& g,int id,const Settings& s){g.cur=&s;g.meter=Meter::from(s.meterNum,s.meterDen);g.genre=s.genre;g.lastProfile=s.profile;g.current=wendungIndex(GenreScore,static_cast<WendungId>(id),s.profile);CHECK(g.current>=0);g.phraseIndex=0;g.wendungTime={};g.chordBase=0;g.still=false;g.planValid=false;}
 static void first(Generator& g,int first){g.chordBase=first;}
 static void independentLead(Generator& g,const Settings& s){g.cur=&s;std::fill(std::begin(g.on),std::end(g.on),false);g.on[kMelodie]=true;EventList e;g.prepareLeadEvent(40*musicaltime::quarter,s,0,e);CHECK(g.leadEvent.ready);CHECK(!g.voice(OutTupfer).motif.material(g.motifCatalog).complete);CHECK(!g.leadEvent.figure.expansionOnly);}
 static auto at(const Generator& g,Tick at){return g.locate(at);}
 static const auto& event(const Generator& g){return g.figureEvent;}
 static const auto& lead(const Generator& g){return g.leadEvent;}
 static const auto& history(const Generator& g){return g.figureHistory;}
 static void finiteOwnership(Settings s){
  Generator g;harmony(g,61061,s);std::fill(std::begin(g.on),std::end(g.on),false);g.on[kArp]=true;
  const SequenceSource* source=nullptr;for(const auto& candidate:darkSynth::sources)if(candidate.id==4013)source=&candidate;CHECK(source);
  const auto last=96*quarter-sixteenth,end=128*quarter;
  for(int v=1;v<=32;++v)if(LayerCycle::active(1,last,{},source->cycle(),s.y,s.z,v+17)&&LayerCycle::active(1,96*quarter,{},source->cycle(),s.y,s.z,v+17)){s.variation=v;break;}
  g.sequences[1]={source,{},60+s.key,s.key,s.variation};CHECK(g.sequenceFits(g.sequences[1],last,s,OutArp));
  EventList e;g.nowTime=last;g.renderSequences(last,s,0,e);int ons=0;for(int i=0;i<e.size;++i)ons+=e.events[i].out==OutArp&&e.events[i].velocity>0;CHECK(ons==1);
  CHECK(g.sequenceFreezeEnd[1]==end);CHECK(g.numActive==1&&g.active[0].endTime==end);
  e.clear();g.releaseAt(toQuarters(96*quarter),0,e);g.renderSequences(96*quarter,s,0,e);CHECK(e.size==0);
  g.releaseAt(toQuarters(end),0,e);CHECK(g.numActive==0);CHECK(e.size==1&&e.events[0].velocity==0);
  // The reply's source pause outlives its short sounding TU gate, until a whole
  // source cycle ends. Muting TU cancels that reservation immediately.
  g.on[kAkzent]=true;g.figureEvent={};g.figureEvent.replyTo=OutArp;g.figureEvent.replyEnd=32*quarter;g.figureEventSlot=-1;
  e.clear();g.prepareFigureEvent(20*quarter,s,0,e);CHECK(g.figureEventSlot==-1&&g.figureEvent.replyEnd==32*quarter);
  g.on[kAkzent]=false;g.prepareFigureEvent(20*quarter,s,0,e);CHECK(g.figureEvent.replyTo==-1);
 }
};}
using Row=std::tuple<int64_t,int,int,int,int>;
static Settings settings(float x=.5f,float y=.5f,float z=.5f){Settings s;s.profile=ProfileId::johnCarpenter;s.policy=policyForContext(s.profile,true);s.x=x;s.y=y;s.z=z;s.scene=false;s.sceneBars=0;s.motif=s.melodyMotif=true;s.melody=true;s.stichFixed=true;return s;}
static std::vector<Row> render(Settings s,int block,int bars=32,bool jumps=false,int fixed=0){
 Generator g;Transport t;t.playing=true;t.bpm=100;EventList e;std::vector<Row> rows;std::map<std::pair<int,int>,int> open;std::map<std::pair<int,int>,int64_t> began;
 const int64_t total=static_cast<int64_t>(bars)*s.meterNum*4/s.meterDen*28800;
 auto collect=[&](int64_t at){CHECK(!e.overflow);for(int i=0;i<e.size;++i){auto n=e.events[i];if(n.type)continue;auto& held=open[{n.channel,n.note}];CHECK(n.velocity?held==0:held==1);if(n.velocity)began[{n.channel,n.note}]=at+n.offset;else CHECK(at+n.offset>began[std::make_pair(n.channel,n.note)]);held+=n.velocity?1:-1;rows.emplace_back(at+n.offset,n.out,n.channel,n.note,n.velocity);}e.clear();};
 if(fixed){g.process(t,s,1,e);t.playing=false;g.process(t,s,1,e);g.reset();e.clear();g.process(t,s,0,e);ExecutionTestAccess::harmony(g,fixed,s);}
 for(int64_t at=0;at<total;){int n=static_cast<int>(std::min<int64_t>({block,total-at,7200-at%7200}));t.ppq=at/28800.;if(jumps){if(at>=total/2)t.ppq-=total/2/28800.;if(at>=total*3/4)t.ppq+=8.125;}
  {NoAllocations guard;g.process(t,s,n,e);}collect(at);at+=n;}
 t.playing=false;g.process(t,s,block,e);collect(total);for(auto [k,n]:open)CHECK(n==0);return rows;
}
int main(){
 CHECK(std::strcmp(findProfile(ProfileId::johnCarpenter)->name,"Dark Synth")==0);CHECK(valid(carpenterPolicy.sequences));
 for(const auto& source:darkSynth::sources)CHECK(valid(source));for(const auto& source:darkSynth::events)CHECK(valid(source));for(const auto& source:darkSynth::leads)CHECK(valid(source));
 {FigureHistory h;PerformedFigureTone a;a.output=OutArp;a.base=60;a.context=1453;h.observe(a);h.observe(a);CHECK(h.count==2);a.base=65;h.observe(a);CHECK(h.count==1);a.output=OutCounter;h.observe(a);CHECK(h.count==1);}
 CHECK(kMaxChords==8);CHECK(kCatalogChordSlots==12);
 ExecutionTestAccess::finiteOwnership(settings(.5f,.6f,.4f));
 // All declared independent harmonic periods, including 3/14/20/24/32 bars.
 for(int num:{3,4,5,7})for(int id=61001;id<=61065;++id){if(id==61049){CHECK(!findHarmonyTemplate(static_cast<WendungId>(id)));continue;}auto s=settings();s.meterNum=num;s.meterDen=num==4?4:8;const auto bar=musicaltime::barLength(s.meterNum,s.meterDen);Generator g;ExecutionTestAccess::harmony(g,id,s);const auto* h=findHarmonyTemplate(static_cast<WendungId>(id));Tick at{};
  for(int i=0;i<h->count;++i){const auto p=ExecutionTestAccess::at(g,at);CHECK(p.chordIdx==i);CHECK(p.chordStartTime==at);CHECK(p.chordEndTime==at+h->chords[i].bars*bar);at=p.chordEndTime;}
  CHECK(ExecutionTestAccess::at(g,at).chordIdx==0);CHECK(ExecutionTestAccess::at(g,at).chordStartTime==at);
 }
 // Leaving stillness resumes the authored order from the held chord, including
 // the wrap, instead of stretching the last slot to the entire long period.
 {auto s=settings();Generator g;ExecutionTestAccess::harmony(g,61023,s);ExecutionTestAccess::first(g,11);
  CHECK(ExecutionTestAccess::at(g,Tick{}).chordIdx==11);CHECK(ExecutionTestAccess::at(g,Tick{}).chordEndTime==8*quarter);
  CHECK(ExecutionTestAccess::at(g,8*quarter).chordIdx==0);CHECK(ExecutionTestAccess::at(g,96*quarter).chordIdx==11);
 }
 {auto s=settings();Generator g;ExecutionTestAccess::harmony(g,61034,s);ExecutionTestAccess::independentLead(g,s);}
 // Physical bass rotation in automatic production, not just a parsed data assertion.
 {auto s=settings(.5f,.35f,.25f);s.melody=false;s.mute[kArp]=s.mute[kGegenstimme]=s.mute[kAkzent]=true;s.bassPattern=BassHeld;s.variety=0;
  bool chosen=false;for(int v=1;v<=16;++v){s.variation=v;const int index=Generator::pick(s,0);if(static_cast<int>(wendungAt(s.genre,index,s.profile).id)==61007){chosen=true;break;}}CHECK(chosen);
  for(int key=0;key<12;++key){s.key=key;const auto rows=render(s,512,16);int attacks=0,releases=0;std::vector<int> bass;
   for(const auto& n:rows){if(std::get<1>(n)==OutPadLong){if(std::get<4>(n)){++attacks;CHECK(std::get<0>(n)==0);}else{++releases;CHECK(std::get<0>(n)==16LL*115200);}}
    if(std::get<1>(n)==OutBassLong&&std::get<4>(n))bass.push_back((std::get<3>(n)-key+120)%12);}
   CHECK(attacks==4&&releases==4);CHECK((bass==std::vector<int>{0,8,5,8,0,1,10,0}));
  }
 }
 // Actual registers, physical ownership, mode changes and musical-time determinism.
 int tu=0,ar=0,kb=0,lb=0,gs=0;
 for(int key=0;key<12;++key){auto s=settings();s.key=key;s.rangeOn[2]=true;s.rangeLo[2]=60;s.rangeHi[2]=86;s.octave[kBass]=-2;s.rangeOn[1]=true;s.rangeLo[1]=24;s.rangeHi[1]=67;
  const auto a=render(s,127,16),b=render(s,2048,16);CHECK(a==b);
  for(auto n:a)if(std::get<4>(n)){const int o=std::get<1>(n),p=std::get<3>(n);tu+=o==OutTupfer;ar+=o==OutArp;kb+=o==OutBassShort;lb+=o==OutBassLong;gs+=o==OutCounter;if(o==OutArp)CHECK(p>=60&&p<=86);if(o==OutBassLong||o==OutBassShort)CHECK(p>=24&&p<=67);if(o==OutStich)CHECK(p==36);}
 }
 CHECK(tu>0&&ar>0&&kb>0&&lb>0&&gs>0);
 for(int num:{3,4,5,7}){auto s=settings();s.meterNum=num;s.meterDen=num==4?4:8;s.swing=.6f;CHECK(render(s,127,8,true)==render(s,2048,8,true));}
 // Independent TU works with all sequencers and lead disabled. Catalog identity
 // comes only from MIDI that really escaped the emitter.
 {auto s=settings(.55f,.4f,.3f);s.melody=false;s.mute[kArp]=s.mute[kGegenstimme]=true;Generator g;Transport t;t.playing=true;t.bpm=100;EventList e;std::vector<int> played;uint64_t identity=0;
  for(int64_t at=0;at<128LL*4*28800;at+=512){t.ppq=at/28800.;e.clear();{NoAllocations guard;g.process(t,s,512,e);}for(int i=0;i<e.size;++i)if(!e.events[i].type&&e.events[i].out==OutTupfer&&e.events[i].velocity)played.push_back(e.events[i].note);
   const auto& m=g.inspectMotif(OutTupfer);if(m.complete){if(!identity){identity=m.identity;CHECK(m.count>=2);CHECK(played.size()>=static_cast<size_t>(m.count));for(int i=0;i<m.count;++i)CHECK(m.origin+m.notes[i].interval==played[played.size()-m.count+i]);}CHECK(m.identity==identity);}CHECK(!ExecutionTestAccess::lead(g).ready);
  }CHECK(played.size()>2);CHECK(identity!=0);
 }
 // A warm loop must not retain a future absolute TU window from before the seek.
 {auto s=settings(.55f,.4f,.3f);s.melody=false;s.mute[kArp]=s.mute[kGegenstimme]=true;Generator g;Transport t;t.playing=true;t.bpm=100;EventList e;
  for(int at=0;at<1216512;at+=512){t.ppq=at/28800.;e.clear();g.process(t,s,512,e);}
  const auto identity=g.inspectMotif(OutTupfer).identity;CHECK(identity!=0);
  t.ppq=0;e.clear();g.process(t,s,512,e);const auto& plan=ExecutionTestAccess::event(g);CHECK(plan.ready&&plan.begin==4*quarter);CHECK(g.inspectMotif(OutTupfer).identity==identity);
 }
 // New operations always derive from immutable material; cycles remain exact.
 for(const auto& source:darkSynth::sources)if(source.sourceIntents){if(source.gateBreathing)for(int i=0;i<source.count;++i){auto early=source.attack(i,{},{}),late=source.attack(i,source.cycle()*16,{});CHECK(early.duration>Tick{}&&late.duration>early.duration);}}
 {auto s=settings(0,0,0);s.melody=false;const auto rows=render(s,512,8);CHECK(std::any_of(rows.begin(),rows.end(),[](auto n){return std::get<1>(n)==OutPadLong&&std::get<4>(n)>0;}));}
 std::cout<<"Dark Synth production TU/AR/KB/LB/GS "<<tu<<'/'<<ar<<'/'<<kb<<'/'<<lb<<'/'<<gs<<"; independent periods, ranges, ownership and memory passed\n";
}
