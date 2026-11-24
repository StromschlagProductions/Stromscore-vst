#pragma once
#include <array>
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
    int64_t bar=0;
    int minDuration=1,maxDuration=2;
};
struct RhythmPlan
{
    struct Onset { int at=0,source=0,length=0; };
    uint16_t reference=0,original=0,coordinated=0;
    std::array<Onset,16> notes {};int count=0;bool active=false;
    const Onset* at(int position)const
    {for(int i=0;i<count;++i)if(notes[i].at==position)return &notes[i];return nullptr;}
};
inline RhythmPlan planRhythmicInterlock(const RhythmPlanRequest& r,const RhythmCoordinationPolicy& policy)
{
    RhythmPlan p;p.reference=r.reference;p.original=r.movement;
    // First strategy: an eighth-note carrier, quarter-note anchors, weak eighth delays.
    // Full sixteenth-note motors have no vacant subdivision and keep their rhythm.
    if(!valid(policy)||!policy.enabled||r.bar<0||r.bar%policy.everyBars!=policy.everyBars-1
        ||r.movement!=0x5555||!r.reference||r.reference==0xffff||r.minDuration<1||r.maxDuration<2)return p;
    for(int source=0;source<16;source+=2)
    {
        int at=source;
        if(source%4==2&&!(r.reference&(1u<<(source+1))))at=source+1;
        p.notes[p.count++]={at,source,2};p.coordinated|=static_cast<uint16_t>(1u<<at);
        p.active|=at!=source;
    }
    for(int i=0;i<p.count;++i)
    {
        auto& n=p.notes[i];const int next=i+1<p.count?p.notes[i+1].at:16;
        n.length=next-n.at<2?1:2;
        if(n.length<r.minDuration||n.length>r.maxDuration)return {};
    }
    return p;
}
}
