#pragma once
#include <array>
#include "MusicalTime.h"
#include <cstdint>
namespace stromscore::composition
{
struct RhythmCoordinationPolicy
{
    bool enabled=true;
    int everyBars=2; // Leave the intervening bars in their original parallel rhythm.
};
inline bool valid(const RhythmCoordinationPolicy& p){return p.everyBars>=1&&p.everyBars<=8;}
struct RhythmPlanRequest
{
    uint16_t reference=0,movement=0;
    int64_t bar=0; // Dimensionless ordinal; masks below describe pattern slots.
    musicaltime::Tick subdivision=musicaltime::sixteenth;
    musicaltime::Tick minDuration=musicaltime::sixteenth,maxDuration=2*musicaltime::sixteenth;
};
struct RhythmPlan
{
    struct Onset { musicaltime::Tick at{},source{},length{}; };
    uint16_t reference=0,original=0,coordinated=0;
    std::array<Onset,16> notes {};int count=0;bool active=false;
    const Onset* at(musicaltime::Tick position)const
    {for(int i=0;i<count;++i)if(notes[i].at==position)return &notes[i];return nullptr;}
};
inline RhythmPlan planRhythmicInterlock(const RhythmPlanRequest& r,const RhythmCoordinationPolicy& policy)
{
    RhythmPlan p;p.reference=r.reference;p.original=r.movement;
    // First strategy: an eighth-note carrier, quarter-note anchors, weak eighth delays.
    // Full sixteenth-note motors have no vacant subdivision and keep their rhythm.
    if(!valid(policy)||!policy.enabled||r.bar<0||r.bar%policy.everyBars!=policy.everyBars-1
        ||r.movement!=0x5555||!r.reference||r.reference==0xffff||r.subdivision<musicaltime::Tick{1}||r.minDuration<musicaltime::Tick{1}||r.maxDuration<2*r.subdivision)return p;
    for(int source=0;source<16;source+=2)
    {
        int at=source;
        if(source%4==2&&!(r.reference&(1u<<(source+1))))at=source+1;
        p.notes[p.count++]={r.subdivision*at,r.subdivision*source,2*r.subdivision};p.coordinated|=static_cast<uint16_t>(1u<<at);
        p.active|=at!=source;
    }
    for(int i=0;i<p.count;++i)
    {
        auto& n=p.notes[i];const auto next=i+1<p.count?p.notes[i+1].at:16*r.subdivision;
        n.length=next-n.at<2*r.subdivision?r.subdivision:2*r.subdivision;
        if(n.length<r.minDuration||n.length>r.maxDuration)return {};
    }
    return p;
}
}
