#pragma once
#include "MusicalTime.h"
#include <array>
#include <algorithm>
#include <cstdint>
namespace stromscore::composition {
struct ArpeggioPhrasePolicy { bool enabled=false;float breathWeight=1.f,exchangeWeight=1.f; };
inline bool valid(const ArpeggioPhrasePolicy& p)
{return p.breathWeight>=0&&p.breathWeight<=4&&p.exchangeWeight>=0&&p.exchangeWeight<=4;}
struct ArpeggioPhrasePlan {
 using Tick=musicaltime::Tick;
 struct Figure { Tick begin{},end{}; };
 std::array<Figure,2> figures{};int count=0;
 Tick begin{},end{};
 Tick releaseAt(Tick at)const {for(int i=0;i<count;++i)if(at>=figures[i].begin&&at<figures[i].end)return figures[i].end;return at;}
};
// Whole figures, not independent note thinning. A continuous reading always remains possible.
inline ArpeggioPhrasePlan planArpeggioPhrase(const ArpeggioPhrasePolicy& policy,
 musicaltime::Tick begin,musicaltime::Tick end,musicaltime::Tick bar,
 float energy,float unrest,bool companion,uint32_t choice)
{
 using musicaltime::Tick;ArpeggioPhrasePlan p;p.begin=begin;p.end=end;
 if(end<=begin||bar<4*musicaltime::quarter)return p;
 p.figures[0]={begin,end};p.count=1;
 if(!policy.enabled||!valid(policy))return p;
 const float continuation=1.f+2.f*energy*unrest;
 const float breath=policy.breathWeight*(1.2f-.5f*energy+.8f*(companion?1.f:0.f));
 const float exchange=policy.exchangeWeight*(companion?1.5f:.35f)*(.5f+unrest);
 const float draw=(choice%100000)/100000.f*(continuation+breath+exchange);
 if(draw<continuation)return p;
 const auto duration=end-begin,unit=bar/2;
 // A short harmonic thought breathes on its last beat; longer thoughts finish a half/bar figure.
 const auto pause=duration<=bar?musicaltime::quarter:duration>=4*bar?bar:unit;
 p.figures[0].end=end-pause;
 if(draw>=continuation+breath&&duration>=2*bar){
  const auto split=begin+unit*((duration/unit)/2);
  p.figures[0].end=split;
  if(split+unit<end-pause){p.figures[1]={split+unit,end-pause};p.count=2;}
 }
 return p;
}
}
