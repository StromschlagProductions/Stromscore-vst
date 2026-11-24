#pragma once
#include <cstdint>
#include <cmath>
namespace stromscore::musicaltime
{
inline constexpr int ticksPerQuarter=960;
inline constexpr int ticksPerGridStep=ticksPerQuarter/4;
inline constexpr double quartersPerGridStep=static_cast<double>(ticksPerGridStep)/ticksPerQuarter;
// Nominal musical position/duration. Samples and host PPQ are boundary representations.
struct Tick
{
    int64_t value=0;
    friend constexpr bool operator<(Tick a,Tick b){return a.value<b.value;}
    friend constexpr bool operator<=(Tick a,Tick b){return a.value<=b.value;}
    friend constexpr bool operator==(Tick a,Tick b){return a.value==b.value;}
    friend constexpr bool operator!=(Tick a,Tick b){return !(a==b);}
};
// Caller bounds: |gridStep| <= 4e9 (existing host transport limit), comfortably within int64.
inline constexpr Tick fromGridStep(int64_t gridStep){return {gridStep*ticksPerGridStep};}
inline constexpr double toQuarters(Tick time){return static_cast<double>(time.value)/ticksPerQuarter;}
// Host/capture/export boundary; callers supply finite PPQ within the existing transport limits.
inline Tick fromQuarters(double ppq){return {static_cast<int64_t>(std::llround(ppq*ticksPerQuarter))};}
inline constexpr Tick barLength(int numerator,int denominator)
{return {static_cast<int64_t>(numerator)*4*ticksPerQuarter/denominator};}
}
