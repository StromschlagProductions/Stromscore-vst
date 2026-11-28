#include "TestSupport.h"
#include "ScoreEngine.h"
namespace stromscore { struct ExecutionTestAccess {
 static composition::MotifOccurrence plan(Generator& g,Settings& s,musicaltime::Tick bar) {
  auto& use=g.voice(OutMelody).motif;use.clear();
  use.observe(64,{},musicaltime::quarter/2,0,90,{});use.observe(67,musicaltime::quarter/2,bar,0,90,{});use.finish(g.motifCatalog);
  g.cur=&s;g.nowTime=8*bar;return g.motifOccurrence(8*bar,g.locate(8*bar),s,OutMelody);
 }
}; }
using namespace stromscore::composition;
using stromscore::musicaltime::quarter;
int main()
{
 RememberedMotif memory;memory.observe(60,{},quarter*2);memory.observe(64,quarter*2,quarter*2);memory.observe(67,quarter*4,quarter*2);memory.finish();
 const auto identity=memory.identity;const auto original=deriveMotif(memory,MotifVariation::original);
 unsigned masks[10]{};stromscore::musicaltime::Tick limits[10]{};
 for(int i=0;i<3;++i){masks[i]=1u<<((60+original.notes[i].interval)%12);limits[i]=quarter*2;}
 auto exact=realizeScoreMotif(original,masks,limits,{48,84},quarter/4,quarter*8,60);
 CHECK(exact.base==60&&!exact.figure.harmonicallyAdapted&&!exact.figure.durationAdjusted);
 // Keep the characteristic major third; adjust the weaker ascending third by one semitone.
 masks[2]=1u<<8;limits[1]=quarter;
 auto adapted=realizeScoreMotif(original,masks,limits,{60,72},quarter/4,quarter*8,60);
 CHECK(adapted.base>=0&&adapted.figure.harmonicallyAdapted&&adapted.figure.durationAdjusted);
 CHECK(adapted.figure.notes[1].interval-adapted.figure.notes[0].interval==4);
 CHECK(adapted.figure.notes[2].interval>adapted.figure.notes[1].interval);
 CHECK(adapted.figure.notes[1].length==quarter);
 for(int i=0;i<3;++i){CHECK(adapted.figure.notes[i].at==original.notes[i].at);CHECK(masks[i]&(1u<<((adapted.base+adapted.figure.notes[i].interval)%12)));}
 CHECK(memory.identity==identity&&memory.notes[1].length==quarter*2);
 CHECK(adapted.figure.sourceIdentity==identity);
 auto suffix=suffixFigure(memory,2);CHECK(suffix.count==2&&suffix.sourceIdentity==identity);
 CHECK(suffix.notes[0].at==stromscore::musicaltime::Tick{}&&suffix.notes[1].at==quarter*2);
 CHECK(suffix.notes[1].interval-suffix.notes[0].interval==3);
 limits[1]=quarter/4;CHECK(realizeScoreMotif(original,masks,limits,{60,72},quarter/4,quarter*8,60).base<0);
 limits[1]=quarter*2;masks[1]=1u<<3; // Strongest third cannot be changed to a minor third.
 CHECK(realizeScoreMotif(original,masks,limits,{60,72},quarter/4,quarter*8,60).base<0);
 for(int key=0;key<12;++key){for(int i=0;i<3;++i){masks[i]=1u<<((key+original.notes[i].interval)%12);limits[i]=quarter*2;}
  CHECK(realizeScoreMotif(original,masks,limits,{48,95},quarter/4,quarter*8,60+key).base>=0);}
 // A fragment's first interval need not be zero. A fixed physical first note
 // must constrain the base relative to that interval, including register edges.
 {auto fragment=suffix;unsigned allowed[10]{};stromscore::musicaltime::Tick durations[10]{};int fixed[10];std::fill(std::begin(fixed),std::end(fixed),-1);
  for(int i=0;i<fragment.count;++i){allowed[i]=0xfff;durations[i]=quarter*2;}
  fixed[0]=64;const auto held=realizeScoreMotif(fragment,allowed,durations,{60,84},quarter/4,quarter*8,60,fixed);CHECK(held.base>=0);CHECK(held.base+held.figure.notes[0].interval==64);CHECK(held.figure.notes[1].interval-held.figure.notes[0].interval==3);
  fixed[0]=0;CHECK(realizeScoreMotif(fragment,allowed,durations,{60,84},quarter/4,quarter*8,60,fixed).base<0);
 }
 for(int numerator:{3,5,7})for(float swing:{0.f,.5f,1.f})
 {
  using namespace stromscore;Settings s;s.custom=true;s.key=0;for(int i=0;i<8;++i)s.customChords[i]={i%2?6:0,Maj7,1};
  s.y=.85f;s.melody=true;s.solo[kMelodie]=true;s.meterNum=numerator;s.meterDen=8;s.swing=swing;
  Generator g;Transport host;host.playing=true;EventList events;g.process(host,s,1,events);
  const auto bar=musicaltime::barLength(numerator,8);const auto occurrence=ExecutionTestAccess::plan(g,s,bar);
  CHECK(occurrence.active&&occurrence.figure.harmonicRealization&&occurrence.figure.durationAdjusted);
  const auto& last=occurrence.figure.notes[occurrence.figure.count-1];
  CHECK(execution::quarters(occurrence.begin+last.at+last.length,execution::Timing::groove,swing)<=musicaltime::toQuarters(9*bar)+1e-12);
 }
 std::cout<<"Bounded Score motif realization: exact anchor, contour, timing, duration limits and immutable source passed\n";
}
