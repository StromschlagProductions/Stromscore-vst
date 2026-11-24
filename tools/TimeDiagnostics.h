#pragma once
#include <cstdint>
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
