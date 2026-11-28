#pragma once
#include "SequencePlan.h"
namespace stromscore::composition {
// Musical target kinds, never channel numbers or external patch identities.
enum class FigurePart { harmonyLong,harmonyShort,bassLong,bassShort,movement,impulse,effect,dialog,melody };
enum class PitchReference { fixed,root,bass,fifth,octave,chord,brokenChord };
struct ToneIntent { char function='A'; int resolution=-1; };
struct LayerAttack { Tick at{},duration{};int pitch=0,velocity=72;PitchReference reference=PitchReference::fixed;ToneIntent intent; };
struct LayerFigure {
 int id=0;const char* reference=nullptr;FigurePart part=FigurePart::movement;
 Tick period{};int count=0;std::array<LayerAttack,64> attacks{};
 float y=.4f,z=.4f,xLow=0,xHigh=1;bool sparse=false;
 // F/U are valid only in one of these authored harmonic objects, not globally.
 unsigned context[2]{};int group=0;bool heldCycle=false;std::array<int,4> harmonicReferences{};
};
inline bool valid(const LayerFigure& s) {
 if(!s.reference||s.id<=0||s.count<1||s.count>64||s.period<Tick{1}||s.xLow<0||s.xHigh>1||s.xLow>s.xHigh)return false;
 for(int i=0;i<s.count;++i){const auto& a=s.attacks[i];if(a.at<Tick{}||a.duration<Tick{1}||(i&&a.at<s.attacks[i-1].at)||a.velocity<1||a.velocity>127)return false;
  if(a.intent.function!='A'&&a.intent.function!='T'&&a.intent.function!='V'&&a.intent.function!='F'&&a.intent.function!='U')return false;
  if(a.intent.function=='V'){
   bool target=false;for(int j=i+1;j<s.count;++j)if(s.attacks[j].pitch==a.intent.resolution&&s.attacks[j].at>a.at&&s.attacks[j].at<=a.at+a.duration+musicaltime::quarter)target=true;
   if(!target)return false;
  }
 }
 return true;
}
struct HarmonicLayerBinding {
 int harmonyId=0,sourceId=0,pedal=-1,highPedal=-1;
 // An independent second harmonic object, not a union masquerading as one chord.
 int upperRoot=-1,upperType=0;std::array<int,3> upperNotes{};
 bool fused=false;
 struct Stage { Tick at{};int shift=0;bool fused=false; };int stages=0;std::array<Stage,3> evolution{};int bassRegister=36;std::array<int,8> bassNotes{};int bassMode=0; // 0 held/figures, 1 absent, 2 entry impulse
};
inline bool permittedTone(const ToneIntent& intent,int pitch,unsigned chord,unsigned collection,unsigned authored,bool targetChord=false) {
 const unsigned bit=1u<<((pitch%12+12)%12);
 if(intent.function=='A')return (chord&bit)!=0;
 if(intent.function=='T')return ((chord|collection)&bit)!=0;
 if(intent.function=='V')return (authored&bit)&&intent.resolution>=0&&targetChord;
 return (intent.function=='F'||intent.function=='U')&&(authored&bit);
}
struct LayerUse {
 const LayerFigure* source=nullptr;Tick origin{};int harmony=0;int placement=0; // Whole-figure octave placement after the user octave, never pitch folding.
 Tick next(Tick at)const {
  if(!source)return Tick{INT64_MAX/4};
  const auto turn=std::max(Tick{},at-origin)/source->period;
  for(int i=0;i<source->count;++i){auto t=origin+source->period*turn+source->attacks[i].at;if(t>=at)return t;}
  return origin+source->period*(turn+1)+source->attacks[0].at;
 }
};
struct LayerPolicy {
 bool enabled=false;const LayerFigure* figures=nullptr;int count=0;
 const HarmonicLayerBinding* harmonies=nullptr;int harmonyCount=0;
};
}
