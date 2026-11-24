#include "TestSupport.h"
#include "ScoreEngine.h"
#include <fstream>
#include <map>
#include <memory>
#include <tuple>
#include <vector>
using namespace stromscore;
using Timed=std::tuple<long long,int,int,int,int,int>;
static unsigned mask(const Chord& c,int key)
{unsigned m=0;for(int i=0;i<kShapes[c.type].n;++i)m|=composition::pitchBit(key+c.root+kShapes[c.type].iv[i]);return m;}
static Settings settingsFor(int type,bool protect,int genre=GenrePopRock)
{
 Settings s;s.genre=genre;s.profile=static_cast<composition::ProfileId>(3+type*2+protect);s.variety=0;
 s.mute[kGegenstimme]=s.mute[kAkzent]=true;s.melody=false;s.padPattern=PadHeld;s.bassPattern=BassHeld;
 s.arpFigure=ArpCircle;s.arpRate=RateEighth;s.x=.8f;s.y=.8f;s.z=.9f;s.passing=true;
 s.rangeOn[0]=true;s.rangeLo[0]=36;s.rangeHi[0]=108;
 for(int v=1;v<=16;++v){s.variation=v;if(wendungAt(s.genre,Generator::pick(s,0)).id==static_cast<WendungId>(3000+type*2+protect))return s;}
 CHECK(false);return s;
}
static std::vector<Timed> render(Settings s,int bars,int block=512,double bpm=120,double start=0,bool route=false)
{
 auto g=std::make_unique<Generator>();EventList es;Transport t;t.playing=true;t.bpm=bpm;
 std::vector<Timed> result;const double spq=48000.*60./bpm;const long long end=std::llround(bars*4*spq);
 auto collect=[&](long long at){CHECK(!es.overflow);for(int i=0;i<es.size;++i){auto e=es.events[i];result.emplace_back(at+e.offset,e.out,e.channel,e.note,e.velocity,e.type);}};
 for(long long at=0;at<end;){
  const auto segment=end/4;const int part=static_cast<int>(at/segment);const long long local=at%segment;
  if(route&&part==3&&local==0){Transport stop;es.clear();g->process(stop,s,1,es);collect(at);}
  t.ppq=route?(part==0?0.:part==1?24.125:part==2?8.:0.)+local/spq:start+at/spq;int n=static_cast<int>(std::min<long long>(block,route?segment-local:end-at));es.clear();{NoAllocations guard;g->process(t,s,n,es);}collect(at);at+=n;}
 Transport stop;es.clear();g->process(stop,s,block,es);collect(end);return result;
}
static void balanced(const std::vector<Timed>& events)
{std::map<std::pair<int,int>,int> held;for(auto [at,o,ch,n,v,t]:events){if(t)continue;auto& count=held[{ch,n}];if(v){CHECK(count==0);++count;}else{CHECK(count==1);--count;}}for(auto p:held)CHECK(p.second==0);}
int main(int argc,char** argv)
{
 int matrix=0,flexChanges=0;const bool quick=argc>1&&std::string(argv[1])=="--sanitizer";std::ofstream report;if(argc>1&&!quick){report.open(argv[1]);CHECK(report.good());report<<"type,strategy,z,defined_mask,effective_mask,pad_mask,arp_mask,bass_mask,first_pad_notes\n";}
 for(int type=0;type<kNumChordTypes;++type)for(bool protect:{false,true})for(int key=0;key<12;++key)
 for(float z:{.1f,.6f,.95f})for(float x:{.2f,.8f})for(float y:{.2f,.8f})for(bool follow:{false,true})
 {
  if(quick&&(x==.2f||y==.2f))continue;
  auto s=settingsFor(type,protect);s.key=key;s.x=x;s.y=y;s.z=z;s.follow[kFlaeche]=s.follow[kBass]=s.follow[kArp]=follow;
  auto g=std::make_unique<Generator>();Transport t;t.playing=true;EventList es;unsigned pads[4]{},arps[4]{},basses[4]{};std::vector<int> first;std::map<std::pair<int,int>,bool> held;
  const auto& w=wendungAt(s.genre,Generator::pick(s,0));CHECK(w.coloration==(protect?ChordColoration::protectedColor:ChordColoration::flexible));
  for(int tick=0;tick<128;++tick)
  {
   t.ppq=tick*.25;es.clear();{NoAllocations guard;g->process(t,s,6000,es);}CHECK(wendungAt(s.genre,g->wendung()).id==w.id);CHECK(!es.overflow);
   const int slot=tick/32;const auto c=follow?w.ch[slot]:w.ch[0];auto effective=c;effective.type=coloredChordType(c.type,z,w.coloration);
   for(int i=0;i<es.size;++i)
   {
    auto e=es.events[i];if(!e.type)held[{e.out,e.note}]=e.velocity>0;if(e.type||!e.velocity)continue;auto bit=composition::pitchBit(e.note);
    if(e.out==OutPadLong||e.out==OutPadShort){pads[slot]|=bit;if(protect)CHECK(bit&mask(c,key));if(!tick)first.push_back(e.note);}
    if(e.out==OutArp){arps[slot]|=bit;if(protect)CHECK(bit&mask(c,key));}
    if(e.out==OutBassLong||e.out==OutBassShort){basses[slot]|=bit;if(protect||y<.6f||!follow)CHECK(bit==composition::pitchBit(key+(follow?(c.bass>=0?c.bass:c.root):0)));}
   }
   for(auto [voice,active]:held)if(active&&(voice.first==OutPadLong||voice.first==OutPadShort))pads[slot]|=composition::pitchBit(voice.second);
  }
  for(int i=0;i<4;++i){auto c=follow?w.ch[i]:w.ch[0];if(protect&&pads[i]!=mask(c,key)){std::cerr<<"type="<<type<<" key="<<key<<" z="<<z<<" x="<<x<<" y="<<y<<" follow="<<follow<<" slot="<<i<<" heard="<<pads[i]<<" expected="<<mask(c,key)<<"\n";CHECK(false);}}
  auto effective=w.ch[0];effective.type=coloredChordType(type,z,w.coloration);
  if(!protect&&effective.type!=type)++flexChanges;
  if(report&&key==0&&x==.8f&&y==.8f&&follow){report<<type<<','<<(protect?"protected":"flexible")<<','<<z<<','<<mask(w.ch[0],key)<<','<<mask(effective,key)<<','<<pads[0]<<','<<arps[0]<<','<<basses[0]<<',';for(int n:first)report<<n<<' ';report<<'\n';}
  ++matrix;
 }
 CHECK(flexChanges>0);
 // Explicit harmonic protection does not switch off time/rhythm or register decisions driven by Z.
 auto s=settingsFor(Min,true);s.arpFigure=ArpAuto;s.padPattern=PadAuto;s.bassPattern=BassAuto;s.passing=false;
 s.z=.1f;auto quiet=render(s,8);s.z=.95f;auto restless=render(s,8);CHECK(quiet!=restless);balanced(quiet);balanced(restless);
 std::cout<<"Protected Z: "<<quiet.size()<<" events at .1, "<<restless.size()<<" at .95\n";
 // Open/reduced dispositions keep every required colour and remain a distinct realization option.
 int applied=0,reduced=0;
 for(int type=0;type<kNumChordTypes;++type)
 {
  auto a=settingsFor(type,true);a.passing=false;a.padPattern=PadAuto;
  for(auto& mode:a.policy.chords.cycle)mode={composition::ChordPopulation::lean,composition::ChordSpacing::open};
  auto g=std::make_unique<Generator>();Transport t;t.playing=true;EventList es;g->process(t,a,6000,es);auto d=g->inspectChordDisposition();
  if(d.applied){++applied;CHECK(!(composition::dispositionMask(d.notes)&~d.chordMask));CHECK((composition::dispositionMask(d.notes)&d.required)==d.required);reduced+=d.omitted!=0;}
 }
 CHECK(applied>0&&reduced>0);
 // Every movement figure and sustained pad playing style obeys the same protected harmonic vocabulary.
 for(int genre:{GenreScore,GenrePopRock})for(int type:{Maj,Min,Fifth,Sus2,Sus4,Add9,MinMaj7})for(int fig=1;fig<kNumArpFigures;++fig)
 {
  auto a=settingsFor(type,true,genre);a.arpFigure=fig;a.mute[kAkzent]=false;auto events=render(a,8);balanced(events);
  const auto w=wendungAt(genre,Generator::pick(a,0));for(auto [at,o,ch,n,v,t]:events)if(!t&&v&&(o==OutPadLong||o==OutPadShort||o==OutArp||o==OutTupfer)){int slot=std::min(3,static_cast<int>(std::llround(at/6000.)/32));CHECK(mask(w.ch[slot],a.key)&composition::pitchBit(n));}
 }
 // Fresh replay, scene restart, loop-to-start, cold seek and export-sized blocks.
 for(bool protect:{false,true})for(int genre:{GenreScore,GenrePopRock})for(double bpm:{90.,120.,173.})
 {
  auto a=settingsFor(MinMaj7,protect,genre);a.swing=.3f;a.dynamics=true;
  auto reference=render(a,8,512,bpm);CHECK(reference==render(a,8,512,bpm));balanced(reference);
  for(int block:{127,480,8192}){auto other=render(a,8,block,bpm);CHECK(other.size()==reference.size());for(size_t i=0;i<other.size();++i){auto lhs=other[i],rhs=reference[i];CHECK(std::abs(std::get<0>(lhs)-std::get<0>(rhs))<=1);std::get<0>(lhs)=std::get<0>(rhs);CHECK(lhs==rhs);}}
  auto transport=render(a,16,512,bpm,0,true);balanced(transport);CHECK(transport==render(a,16,512,bpm,0,true));
  CHECK(render(a,2,127,bpm,8.125)==render(a,2,127,bpm,8.125));
 }
 // A very narrow range must omit an unavailable class instead of substituting a neighbouring pitch.
 for(int type:{Fifth,Sus4,MinMaj7})
 {
  auto a=settingsFor(type,true);a.passing=false;a.follow[kFlaeche]=a.follow[kBass]=a.follow[kArp]=false;a.arpFigure=ArpRiff;a.rangeOn[0]=a.rangeOn[2]=true;
  a.rangeLo[0]=a.rangeHi[0]=a.rangeLo[2]=a.rangeHi[2]=61;
  auto events=render(a,8);balanced(events);for(auto [at,o,ch,n,v,t]:events)if(!t&&v&&(o==OutPadLong||o==OutPadShort||o==OutArp)){std::cerr<<"narrow type="<<type<<" at="<<at<<" out="<<o<<" note="<<n<<"\n";CHECK(false);}
 }
 // Checked modal passing tones remain possible and resolve; the stored original stays immutable.
 {
  Settings a;a.genre=GenrePopRock;a.profile=static_cast<composition::ProfileId>(3+2*kNumChordTypes);a.x=.85f;a.y=.75f;a.z=.35f;a.variety=0;a.solo[kGegenstimme]=true;
  auto g=std::make_unique<Generator>();Transport t;t.playing=true;EventList es;int passes=0,resolutions=0;uint64_t identity=0;long long targetAt=-1;int target=-1;
  for(int tick=0;tick<128*16;++tick)
  {
   t.ppq=tick*.25;es.clear();g->process(t,a,6000,es);CHECK(wendungAt(a.genre,g->wendung()).id==static_cast<WendungId>(3100));
   auto m=g->rememberedMotif();if(m.complete){if(!identity)identity=m.identity;CHECK(identity==m.identity);}
   auto occurrence=g->inspectMotifOccurrence(tick,a);const int index=occurrence.figure.passingIndex;
   for(int i=0;i<es.size;++i){auto e=es.events[i];if(e.type||!e.velocity||e.out!=OutCounter)continue;
    if(tick==targetAt&&e.note==target){++resolutions;targetAt=-1;}
    if(index>=0&&musicaltime::fromGridStep(tick)==occurrence.begin+occurrence.figure.notes[index].at&&e.note==occurrence.base+occurrence.figure.notes[index].interval)
    {++passes;targetAt=musicaltime::toExactGridStep(occurrence.begin+occurrence.figure.notes[index+1].at);target=occurrence.base+occurrence.figure.notes[index+1].interval;}
   }
  }
  CHECK(identity&&passes>0&&passes==resolutions);std::cout<<"Protected modal hook: "<<passes<<" checked passing tones, "<<resolutions<<" actual resolutions in 128 bars\n";
 }
 // The production presets remain flexible; every protected fixture comes through generated validated data.
 for(const auto& h:harmonyTemplates)if(static_cast<uint32_t>(h.id)<=2036)CHECK(h.coloration==ChordColoration::flexible);
 std::cout<<"Coloration tests passed: "<<matrix<<" full 8-bar matrix renders; "<<applied<<" open realizations, "<<reduced<<" reductions\n";
}
