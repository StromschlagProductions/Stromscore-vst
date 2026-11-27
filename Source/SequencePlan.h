#pragma once
#include "MusicalTime.h"
#include <array>
#include <numeric>
#include <cstdint>
#include <algorithm>
namespace stromscore::composition {
using musicaltime::Tick;
// A finite ordered pitch cycle and a rhythm period are independent musical data.
// No channels, patches, transport clock, RNG or allocation belongs to this plan.
struct FigureHarmonyBinding { int id;bool independentPedal; };
struct SequenceSource {
 int id=0;const char* reference=nullptr;bool bass=false,chordBound=false,major=false,dorian=false;
 int tones=0;std::array<int,32> pitches{};std::array<char,32> functions{};
 struct Attack { Tick at{},duration{};int velocity=88; };
 int count=0;std::array<Attack,64> attacks{};Tick period{};
 std::array<std::array<float,2>,3> domains{},rhythmDomains{};int complement=0;bool blockTranspose=false;
 Tick cycle()const {return count>0?period*(tones/std::gcd(tones,count)):Tick{};}
};
inline bool valid(const SequenceSource& s) {
 if(!s.reference||s.id<=0||s.tones<1||s.tones>32||s.count<1||s.count>64||s.period<Tick{1})return false;
 for(int i=0;i<s.tones;++i)if(s.functions[i]!='A'&&s.functions[i]!='T'&&s.functions[i]!='U'&&s.functions[i]!='F')return false;
 for(int i=0;i<s.count;++i){const auto& a=s.attacks[i];if(a.at<Tick{}||a.at>=s.period||a.duration<Tick{1}||a.duration>s.period||a.velocity<1||a.velocity>127||
  (i&&a.at<=s.attacks[i-1].at)||a.at+a.duration>(i+1<s.count?s.attacks[i+1].at:s.period+s.attacks[0].at))return false;}
 return true;
}
inline uint64_t sequenceIdentity(const SequenceSource& s) {
 uint64_t h=1469598103934665603ull;
 auto add=[&](int64_t v){h^=static_cast<uint64_t>(v);h*=1099511628211ull;};
 add(s.cycle().value);for(int i=0;i<s.tones;++i)add(s.pitches[i]-s.pitches[0]);
 for(int i=0;i<s.count;++i){add(s.attacks[i].at.value);add(s.attacks[i].duration.value);add(s.attacks[i].velocity);}return h;
}
struct SequenceUse {
 const SequenceSource* source=nullptr;Tick origin{};int base=0,tonic=0,revision=0;
 Tick next(Tick at)const {
  if(!source)return Tick{INT64_MAX/4};
  const auto rel=std::max(Tick{},at-origin);const auto turn=rel/source->period;
  for(int i=0;i<source->count;++i){auto time=origin+source->period*turn+source->attacks[i].at;if(time>=at)return time;}
  return origin+source->period*(turn+1)+source->attacks[0].at;
 }
 int index(Tick at)const {if(!source||at<origin)return -1;auto local=(at-origin)%source->period;for(int i=0;i<source->count;++i)if(source->attacks[i].at==local)return i;return -1;}
 int tone(Tick at,int index)const {return static_cast<int>(((at-origin)/source->period*source->count+index)%source->tones);}
};
struct LayerCycle {
 // Contextual options, including unbroken stasis, not a compulsory rest quota.
 static bool active(int slot,Tick at,Tick origin,Tick cycle,float energy,float unrest,uint32_t seed) {
  if(cycle<Tick{1})return false;
  const auto ordinal=std::max<int64_t>(0,(at-origin)/cycle);
  const auto section=ordinal/8;const unsigned choice=static_cast<unsigned>((seed+section*13)%5);
  if(choice==0||(energy>.85f&&unrest>.7f))return true;
  if(choice==1)return (ordinal%8!=7)||slot==0;
  if(choice==2)return slot==0?ordinal%8<5:ordinal%8>=3;
  if(choice==3)return ordinal%8<(energy<.4f?2:6);
  return slot==0||ordinal%8>=4;
 }
};
}
