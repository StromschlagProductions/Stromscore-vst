#include "TestSupport.h"
#include "ScoreEngine.h"
#include <cstring>
using namespace stromscore;using namespace stromscore::composition;
#include "RealtimeReference.h"
static AuthoredPlacement original(const AuthoredMotifSource& source,const unsigned* masks,int lo,int hi,int preferred,bool octave,int fixed){
 AuthoredPlacement result;for(int base=0;base<128;++base){if(octave&&(base-preferred)%12!=0)continue;if(fixed>=0&&base!=fixed)continue;bool fits=true;
 for(int i=0;i<source.count;++i){int pitch=base+source.pitches[i]-source.pitches[0];if(pitch<lo||pitch>hi||pitch<0||pitch>127||!(masks[i]&pitchBit(pitch))){fits=false;break;}}
 if(fits&&std::abs(base-preferred)<result.cost)result={base,std::abs(base-preferred)};}return result;
}
int main(){uint32_t seed=7331;auto next=[&]{seed^=seed<<13;seed^=seed>>17;seed^=seed<<5;return seed;};
 for(int test=0;test<100000;++test){AuthoredMotifSource source{};source.count=next()%9;for(auto& p:source.pitches)p=static_cast<int>(next()%73)-36;unsigned masks[8];for(auto& mask:masks)mask=next();const int lo=static_cast<int>(next()%90)-12,hi=lo+next()%80,preferred=static_cast<int>(next()%200)-36,fixed=test%3==0?static_cast<int>(next()%128):-1;bool octave=test%2;
 const auto a=original(source,masks,lo,hi,preferred,octave,fixed),b=placeAuthoredMotif(source,masks,lo,hi,preferred,octave,fixed);CHECK(a.base==b.base&&a.cost==b.cost);}
 // Single-target lookup is exactly the corresponding full-catalog entry,
 // including availability, fixed triggers and all independent long/short limits.
 for(int profile=0;profile<6;++profile)for(int genre=0;genre<2;++genre)for(int variant=0;variant<32;++variant){Settings s;s.profile=static_cast<ProfileId>(profile);s.genre=genre;s.policy=policyForContext(s.profile,genre==0);s.melody=variant&1;s.stichFixed=variant&2;s.stichNote=36+variant;s.rangeOn[2]=variant&4;s.rangeLo[2]=60;s.rangeHi[2]=86;s.solo[variant%kNumLayers]=variant&8;s.mute[(variant+1)%kNumLayers]=variant&16;
  const auto all=referenceOutputCatalog(s);for(int o=0;o<kNumOutputs;++o){const auto one=outputDescription(s,o);const auto& a=all[o];CHECK(std::strcmp(a.standardUse,one.standardUse)==0);CHECK(a.target.output==one.target.output&&a.target.channel==one.target.channel&&a.target.fixedNote==one.target.fixedNote);CHECK(a.origin==one.origin&&a.externalPatchKnown==one.externalPatchKnown);const auto& x=a.track;const auto& y=one.track;CHECK(x.id.value==y.id.value&&x.style==y.style&&x.roles==y.roles&&x.available==y.available&&x.addressing==y.addressing);CHECK(x.instrument.pitch==y.instrument.pitch&&x.instrument.articulations==y.instrument.articulations&&x.instrument.polyphony==y.instrument.polyphony&&x.instrument.minDuration==y.instrument.minDuration&&x.instrument.maxDuration==y.instrument.maxDuration&&x.instrument.range.low==y.instrument.range.low&&x.instrument.range.high==y.instrument.range.high);}}
 std::cout<<"100000 exact placement comparisons and 3456 output capability comparisons passed\n";
}
