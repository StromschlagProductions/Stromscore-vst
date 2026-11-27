#pragma once
#include "CompositionCore.h"
namespace stromscore::composition
{
// Harmonic intent, independent of MIDI channel, octave and note ownership.
enum class BassRelation { chordBound, independentPedal, authorizedDissonancePedal };
struct PedalPlan
{
    musicaltime::Tick begin{},end{};
    int pitchClass=-1;
    BassRelation relation=BassRelation::chordBound;
    bool contains(musicaltime::Tick at)const
    {return relation!=BassRelation::chordBound&&pitchClass>=0&&pitchClass<12&&begin<=at&&at<end;}
};
// Authorization belongs to this harmonic context, NOT to a voice or pitch class globally.
struct PedalHarmony { unsigned chordTones=0; int explicitBass=-1; bool authorizesDissonance=false; };
inline bool permits(const PedalPlan& p,const PedalHarmony& h)
{
    if(p.pitchClass<0||p.pitchClass>11||p.relation==BassRelation::chordBound
        ||h.explicitBass< -1||h.explicitBass>11||(h.chordTones&~0xfffu))return false;
    if(h.explicitBass>=0&&h.explicitBass!=p.pitchClass)return false;
    if(h.chordTones&(1u<<p.pitchClass))return true;
    return p.relation==BassRelation::authorizedDissonancePedal&&h.authorizesDissonance&&h.explicitBass==p.pitchClass;
}
}
