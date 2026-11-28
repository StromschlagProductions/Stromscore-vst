#pragma once
#include "ModalContext.h"
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
