#pragma once
#include <cstdint>
#include <cmath>
#include <cassert>
namespace stromscore::musicaltime
{
inline constexpr int ticksPerQuarter=960;
inline constexpr int ticksPerGridStep=ticksPerQuarter/4;
inline constexpr double quartersPerGridStep=static_cast<double>(ticksPerGridStep)/ticksPerQuarter;
// Nominal musical position/duration. Samples and host PPQ are boundary representations.
struct Tick
{
    int64_t value=0;
    friend constexpr Tick operator+(Tick a,Tick b){return {a.value+b.value};}
    friend constexpr Tick operator-(Tick a,Tick b){return {a.value-b.value};}
    Tick& operator+=(Tick b){value+=b.value;return *this;}
    friend constexpr bool operator<(Tick a,Tick b){return a.value<b.value;}
    friend constexpr bool operator>=(Tick a,Tick b){return !(a<b);}
    friend constexpr bool operator<=(Tick a,Tick b){return a.value<=b.value;}
    friend constexpr bool operator==(Tick a,Tick b){return a.value==b.value;}
    friend constexpr bool operator!=(Tick a,Tick b){return !(a==b);}
};
// Caller bounds: |gridStep| <= 4e9 (existing host transport limit), comfortably within int64.
inline constexpr Tick fromGridStep(int64_t gridStep){return {gridStep*ticksPerGridStep};}
// Temporary, explicit boundary to the still grid-based planner/scheduler.
// Only exact old-grid positions may cross it; never silently quantize a finer time.
inline int64_t toExactGridStep(Tick time)
{assert(time.value%ticksPerGridStep==0);return time.value/ticksPerGridStep;}
inline constexpr double toQuarters(Tick time){return static_cast<double>(time.value)/ticksPerQuarter;}
// Host/capture/export boundary; callers supply finite PPQ within the existing transport limits.
inline Tick fromQuarters(double ppq){return {static_cast<int64_t>(std::llround(ppq*ticksPerQuarter))};}
inline constexpr Tick barLength(int numerator,int denominator)
{return {static_cast<int64_t>(numerator)*4*ticksPerQuarter/denominator};}
}
