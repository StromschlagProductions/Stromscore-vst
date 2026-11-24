#pragma once
#include "MusicalTime.h"
#include <algorithm>
#include <cmath>
#include <limits>
namespace stromscore::execution
{
using musicaltime::Tick;
enum class Timing { nominal, groove };
enum class Kind { release, planning, rhythm };
// Musical time is authoritative. Performance PPQ is derived only at dispatch/chase.
inline double quarters(Tick at,Timing timing,float swing)
{
    const double cells=static_cast<double>(at.value)/musicaltime::ticksPerGridStep;
    if(timing==Timing::nominal||swing<=0)return cells*musicaltime::quartersPerGridStep;
    const int64_t period=musicaltime::ticksPerQuarter;
    const int64_t phase=(at.value%period+period)%period;
    const int cell=static_cast<int>(phase/musicaltime::ticksPerGridStep);
    const double fraction=static_cast<double>(phase%musicaltime::ticksPerGridStep)/musicaltime::ticksPerGridStep;
    constexpr double delays[5]={0,.333,.667,.333,0};
    const double delay=(delays[cell]+(delays[cell+1]-delays[cell])*fraction)*swing;
    return (cells+delay)*musicaltime::quartersPerGridStep;
}
inline Tick floorTime(double ppq)
{return {static_cast<int64_t>(std::floor(ppq*musicaltime::ticksPerQuarter+1e-7))};}
inline Tick nominalAt(double performed,Timing timing,float swing)
{
    if(timing==Timing::nominal||swing<=0)return floorTime(performed);
    const double quarter=std::floor(performed),phase=(performed-quarter)*4;
    const double positions[5]={0,1+.333*swing,2+.667*swing,3+.333*swing,4};
    int cell=0;while(cell<3&&phase>=positions[cell+1])++cell;
    const double fraction=(phase-positions[cell])/(positions[cell+1]-positions[cell]);
    return floorTime(quarter+(cell+fraction)*musicaltime::quartersPerGridStep);
}
inline Tick atOrAfter(Tick at,Tick period)
{
    auto ordinal=at.value/period.value;const auto remainder=at.value%period.value;
    if(remainder>0)++ordinal;
    return period*ordinal;
}
struct Candidate
{
    Tick at{};Timing timing=Timing::nominal;Kind kind=Kind::planning;bool valid=false;
};
inline double when(const Candidate& e,float swing)
{return e.valid?quarters(e.at,e.timing,swing):std::numeric_limits<double>::infinity();}
inline Candidate first(Candidate a,Candidate b,float swing)
{
    const double x=when(a,swing),y=when(b,swing);
    return y<x-1e-12||(std::abs(x-y)<=1e-12&&static_cast<int>(b.kind)<static_cast<int>(a.kind))?b:a;
}
inline bool coincides(double a,double b){return std::abs(a-b)<=1e-12;}
inline bool sounding(Tick begin,Tick end,Timing timing,float swing,double cursor)
{return quarters(begin,timing,swing)<cursor-1e-9&&quarters(end,timing,swing)>cursor+1e-9;}
}
