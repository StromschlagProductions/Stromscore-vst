#pragma once
#include <cstdint>
#include <cmath>
#include <limits>
// Historical comparison reports use sixteenth-note display units. Production motif
// storage and calculation never use these reporting-only conversions.
inline int64_t diagnosticTime(int64_t value,int =1){return value;}
template<class Time> auto diagnosticTime(Time time,int scale=240)->decltype(time.value)
{return time.value/scale;}

// Compare historical reports across the disposition inspection API migration.
template<class Generator> auto diagnosticDispositionStep(const Generator& g,int)
    -> decltype(g.inspectChordDispositionTime(),int64_t{})
{const auto at=g.inspectChordDispositionTime();return at?diagnosticTime(*at):-1;}
template<class Generator> auto diagnosticDispositionStep(const Generator& g,long)
    -> decltype(g.inspectChordDispositionStep())
{return g.inspectChordDispositionStep();}

// Read-only reporting of a performed stock-grid onset. Do not floor a rounded
// sample at non-integral host tempos into the previous planning epoch.
inline int64_t diagnosticOnset(double quarter,float swing)
{
    const auto estimate=static_cast<int64_t>(std::llround(quarter*4));auto best=estimate;double cost=std::numeric_limits<double>::max();
    for(auto cell=estimate-2;cell<=estimate+2;++cell)
    {
        const auto mod=(cell%4+4)%4;const double delay=(mod==2?.667:mod==1||mod==3?.333:0)*swing;
        const auto distance=std::abs((cell+delay)*.25-quarter);if(distance<cost){cost=distance;best=cell;}
    }
    return best;
}
