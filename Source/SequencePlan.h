#pragma once
#include "MusicalTime.h"
#include <array>
#include <numeric>
#include <cstdint>
#include <algorithm>
namespace stromscore::composition {
using musicaltime::Tick;
inline constexpr std::array<int,21> figureOctaves{{0,-12,12,-24,24,-36,36,-48,48,-60,60,-72,72,-84,84,-96,96,-108,108,-120,120}};
// A finite ordered pitch cycle and a rhythm period are independent musical data.
// No channels, patches, transport clock, RNG or allocation belongs to this plan.
struct FigureHarmonyBinding { int id;bool independentPedal;bool bassless=false,retainBoundBass=false; };
struct SequenceSource {
 int id=0;const char* reference=nullptr;bool bass=false,chordBound=false,major=false,dorian=false;
 int tones=0;std::array<int,32> pitches{};std::array<char,32> functions{};
 struct Attack { Tick at{},duration{};int velocity=88; };
 int count=0;std::array<Attack,64> attacks{};Tick period{};
 std::array<std::array<float,2>,3> domains{},rhythmDomains{};int complement=0;bool blockTranspose=false;
 unsigned contextMask=0;bool sourceIntents=false;
 bool gateBreathing=false;int mutationStep=-1,mutationInterval=0,mutationAfter=0,freezeAfter=0,freezeCycles=0;
 float preference=1.f;int exposition=0;bool expansionOnly=false;
 Attack attack(int index,Tick at,Tick origin)const {
  auto hit=attacks[index];if(gateBreathing){
   const int phase=static_cast<int>(std::max<int64_t>(0,(at-origin)/cycle())/8%4);
   const auto gap=index+1<count?attacks[index+1].at-hit.at:period+attacks[0].at-hit.at;
   const int factors[]={30,55,80,55};hit.duration=std::max(Tick{48},gap*factors[phase]/100);
  }return hit;
 }
 int pitch(int tone,Tick at,Tick origin)const {
  return pitches[tone]+((tone==mutationStep&&mutationAfter>0&&at-origin>=cycle()*mutationAfter)?mutationInterval:0);
 }
 bool frozen(Tick at,Tick origin)const {if(freezeAfter<1||freezeCycles<1)return false;const auto turn=std::max<int64_t>(0,(at-origin)/cycle());return turn%(freezeAfter+freezeCycles)>=freezeAfter;}

 Tick cycle()const {return count>0?period*(tones/std::gcd(tones,count)):Tick{};}
};
inline bool valid(const SequenceSource& s) {
 if(s.mutationStep>=s.tones||s.mutationAfter<0||s.freezeAfter<0||s.freezeCycles<0)return false;
 if(!s.reference||s.id<=0||s.tones<1||s.tones>32||s.count<1||s.count>64||s.period<Tick{1})return false;
 for(int i=0;i<s.tones;++i)if(s.functions[i]!='A'&&s.functions[i]!='T'&&s.functions[i]!='U'&&s.functions[i]!='F'&&s.functions[i]!='V')return false;
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
