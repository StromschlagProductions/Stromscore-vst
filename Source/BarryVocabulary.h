#pragma once
#include "BarryVocabulary.generated.h"
#include "RhythmPlan.h"
#include <algorithm>
#include <cmath>
namespace stromscore::composition::barry
{
inline float distance(float x,float y,float z,float a,float b,float c)
{return (x-a)*(x-a)+.49f*(y-b)*(y-b)+.64f*(z-c)*(z-c);}
inline const RhythmSource* chooseRhythm(float x,float y,float z,int num,int den,int stableBars)
{
    const RhythmSource* best=nullptr;float score=1e9f;
    for(const auto& r:rhythms)if(r.num==num&&r.den==den&&(!r.staticHarmony||r.bars<=stableBars))
    {const auto d=distance(x,y,z,r.x,r.y,r.z);if(d<score){score=d;best=&r;}}
    // Do not force a remote motor into a lyrical/quiet corner with no fitting R study.
    // Editorial radius in the existing weighted XYZ metric, not a research measurement.
    return score<=.25f*.25f?best:nullptr;
}
// Interpret the canonical X/x attack, '-' continuation and '.' release/rest literally.
// The existing RhythmPlan is a per-bar performance plan, not another clock or scheduler.
inline RhythmPlan planBar(const RhythmSource& r,bool bass,int64_t bar)
{
    RhythmPlan p;const char* pattern=bass?r.bass:r.movement;if(!*pattern)return p;
    const int steps=r.num*16/r.den,cycle=steps*r.bars,begin=static_cast<int>((bar%r.bars+r.bars)%r.bars)*steps;
    p.active=true;
    for(int pos=0;pos<steps;++pos)if(pattern[begin+pos]=='X'||pattern[begin+pos]=='x')
    {
        int duration=1;while(begin+pos+duration<cycle&&pattern[begin+pos+duration]=='-')++duration;
        p.notes[p.count++]={musicaltime::sixteenth*pos,musicaltime::sixteenth*pos,musicaltime::sixteenth*duration,pattern[begin+pos]=='X'?6:0};
    }
    return p;
}
inline int64_t movementOrdinal(const RhythmSource& r,int64_t bar,int position)
{
    const int steps=r.num*16/r.den,cycle=steps*r.bars;int count=0,prefix=0;
    const auto local=(bar%r.bars+r.bars)%r.bars*steps+position;
    for(int i=0;i<cycle;++i)if(r.movement[i]=='X'||r.movement[i]=='x'){++count;if(i<local)++prefix;}
    return (bar/r.bars)*count+prefix;
}
}
