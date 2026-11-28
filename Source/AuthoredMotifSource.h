#pragma once
#include "ModalContext.h"
#include <algorithm>
#include <cstdlib>
namespace stromscore::composition {
// Source notation uses dimensionless sixteenth-note counts. All runtime motif
// positions/durations are Tick; these values are converted only at authoring entry.
struct AuthoredMotifSource {
 int id,num,den,steps,count;float x,y,z;int pitches[8],at[8],lengths[8];
 // Optional explicit source harmony, one mask/bass per notated bar. Zero retains
 // the established chord-tone-only authoring behavior (Barry).
 unsigned harmony[2]{}, melodic[2]{};int bass[2]{};
 bool dialogOnly=false,octatonic=false,singleIntroduction=false;
 char functions[8]{};int targets[8]{};float xLow=0.f,xHigh=1.f;bool registerByColor=false; // Optional explicit A/T/V/F/U source intent.
};
struct AuthoredPlacement { int base=-1,cost=10000; };
// Exact placement of an unchanged cell. Intersect permissible root pitch classes
// and register bounds once; enumerate the same ascending feasible bases as before.
inline AuthoredPlacement placeAuthoredMotif(const AuthoredMotifSource& source,
    const unsigned* masks,int rangeLow,int rangeHigh,int preferred,bool octaveOnly,int fixed=-1)
{
 unsigned allowed=0xfffu;int low=0,high=127;
 for(int i=0;i<source.count;++i){
  const int relative=source.pitches[i]-source.pitches[0];
  const int shift=(relative%12+12)%12;
  const unsigned mask=masks[i]&0xfffu;
  allowed&=((mask>>shift)|(mask<<(12-shift)))&0xfffu;
  low=std::max(low,std::max(0,rangeLow)-relative);
  high=std::min(high,std::min(127,rangeHigh)-relative);
 }
 AuthoredPlacement result;if(!allowed||low>high)return result;
 if(fixed>=0){low=std::max(low,fixed);high=std::min(high,fixed);}
 const int step=octaveOnly?12:1;
 if(octaveOnly)low+=(preferred-low)%12<0?(preferred-low)%12+12:(preferred-low)%12;
 for(int base=low;base<=high;base+=step){
  if(!(allowed&(1u<<(base%12))))continue;
  const int cost=std::abs(base-preferred);
  if(cost<result.cost)result={base,cost};
 }
 return result;
}
inline unsigned transposePitchMask(unsigned mask,int key) {
 unsigned result=0;for(int pc=0;pc<12;++pc)if(mask&(1u<<pc))result|=pitchBit(pc+key);return result;
}
// Additional tones are authorized by their authored harmonic relationship, not
// by turning the motif's aggregate pitch set into a scale for unrelated chords.
inline unsigned authoredPitchMask(const AuthoredMotifSource& source,unsigned chord,int bass,int key,const ModalContext& context) {
 if(!source.harmony[0])return chord;
 if(context.status==ModalStatus::unique&&context.mode==Mode::octatonic) {
  unsigned vocabulary=source.harmony[0]|source.harmony[1]|source.melodic[0]|source.melodic[1];
  if(transposePitchMask(vocabulary,key)&~context.mask)return 0;
  if(source.octatonic)return context.mask;
 }
 unsigned result=0;
 for(int bar=0;bar<2;++bar)if(chord==transposePitchMask(source.harmony[bar],key)&&pitchBit(bass)==pitchBit(source.bass[bar]+key))
  result|=transposePitchMask(source.melodic[bar],key)|chord;
 return result;
}
}
