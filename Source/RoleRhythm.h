#pragma once
#include "RhythmPlan.h"
#include <cmath>
#include <limits>
namespace stromscore::composition {
// A bounded two-bar role decision. Pitches remain in the harmonic adapter.
struct RoleRhythmSource {
 int rhythm,bassId;float x,y,z;const char* harmony;const char* bass;
 int intervals[3];int intervalCount;bool pedal;
};
struct RoleRhythmPlan {
 RhythmPlan harmony,bass;const RoleRhythmSource* source=nullptr;
};
inline RoleRhythmPlan planRoleRhythm(const RoleRhythmSource& source,int64_t bar)
{
 RoleRhythmPlan result;result.source=&source;
 auto plan=[&](const char* pattern){RhythmPlan p;if(!*pattern)return p;p.active=true;
 const int begin=static_cast<int>((bar%2+2)%2)*16;
 for(int i=0;i<16;++i)if(pattern[begin+i]=='X'||pattern[begin+i]=='x'){
  int length=1;while(begin+i+length<32&&pattern[begin+i+length]=='-')++length;
  p.notes[p.count++]={musicaltime::sixteenth*i,musicaltime::sixteenth*i,musicaltime::sixteenth*length,pattern[begin+i]=='X'?6:0};}
 return p;};result.harmony=plan(source.harmony);result.bass=plan(source.bass);return result;
}
inline int roleBassInterval(const RoleRhythmSource& source,int64_t bar,int position)
{
 int attacks=0,total=0;const auto local=static_cast<int>((bar%2+2)%2)*16+position;
 for(int i=0;i<32;++i)if(source.bass[i]=='X'||source.bass[i]=='x'){++total;if(i<local)++attacks;}
 const auto ordinal=(bar/2)*total+attacks;return source.intervals[static_cast<size_t>((ordinal%source.intervalCount+source.intervalCount)%source.intervalCount)];
}
}
#include "WilliamsVocabulary.generated.h"
