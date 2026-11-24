#pragma once
#include "VoiceLeading.h"
#include <array>
#include <cstdint>
namespace stromscore::composition
{
enum class ChordPopulation { complete,lean };
enum class ChordSpacing { natural,open };
struct ChordDisposition { ChordPopulation population=ChordPopulation::complete;ChordSpacing spacing=ChordSpacing::natural; };
struct ChordDispositionPolicy
{
    bool enabled=true;
    std::array<ChordDisposition,4> cycle {{{},{ChordPopulation::complete,ChordSpacing::open},
        {ChordPopulation::lean,ChordSpacing::natural},{ChordPopulation::lean,ChordSpacing::open}}};
    int minimumOpenSpan=19,maximumOpenSpan=30;
};
inline bool valid(const ChordDispositionPolicy& p)
{
    if(p.minimumOpenSpan<12||p.maximumOpenSpan<p.minimumOpenSpan||p.maximumOpenSpan>36)return false;
    for(auto d:p.cycle)if(static_cast<int>(d.population)<0||static_cast<int>(d.population)>1||static_cast<int>(d.spacing)<0||static_cast<int>(d.spacing)>1)return false;
    return true;
}
inline int dispositionCount(uint16_t mask)
{int n=0;for(;mask;mask&=mask-1)++n;return n;}
inline uint16_t dispositionMask(const voiceleading::ChordVoicing& v)
{uint16_t mask=0;for(int i=0;i<v.n;++i)mask|=static_cast<uint16_t>(1u<<((v.notes[i]%12+12)%12));return mask;}
struct ChordDispositionRequest
{
    voiceleading::ChordVoicing original,previous;
    uint16_t chordMask=0;int root=0,bass=-1,low=0,high=127,polyphony=6;
    // Exact interval structures (quartal/altered fifths) are supplied as mandatory facts.
    uint16_t required=0;
    ChordDisposition disposition;
    int descendingSeventh=-1,ascendingThird=-1;
};
struct ChordDispositionResult
{
    voiceleading::ChordVoicing notes;
    uint16_t chordMask=0,required=0,omitted=0;
    ChordDisposition disposition;
    bool applied=false,bassCoversRoot=false;
};
inline ChordDispositionResult realizeChord(const ChordDispositionRequest& r,const ChordDispositionPolicy& policy)
{
    ChordDispositionResult result;result.notes=r.original;result.chordMask=r.chordMask;result.required=r.required;result.disposition=r.disposition;
    if(!policy.enabled||!valid(policy)||r.original.n<2||r.original.n>6||r.polyphony<2||r.low>r.high||r.low< -128||r.high>255||r.root<0||r.root>11)return result;
    if(dispositionMask(r.original)!=r.chordMask)return result; // No repairing an unavailable harmonic colour with a substitute pitch.
    auto anchor=r.original;voiceleading::sort(anchor);
    const auto root=static_cast<uint16_t>(1u<<r.root),fifth=static_cast<uint16_t>(1u<<((r.root+7)%12));
    uint16_t needed=r.chordMask;
    if(r.disposition.population==ChordPopulation::lean)
    {
        // Only a genuinely represented stable bass root may replace the pad's root.
        result.bassCoversRoot=r.bass>=0&&(r.bass%12+12)%12==r.root;
        if(result.bassCoversRoot&&!(r.required&root))needed&=~root;
        if(dispositionCount(r.chordMask)>=4&&!(r.required&fifth))needed&=~fifth;
        if(dispositionCount(needed)<2)needed=r.chordMask;
        voiceleading::ChordVoicing reduced;uint16_t seen=0;
        for(int i=0;i<anchor.n;++i){const auto bit=static_cast<uint16_t>(1u<<((anchor.notes[i]%12+12)%12));
            if((needed&bit)&&!(seen&bit)){reduced.notes[reduced.n++]=anchor.notes[i];seen|=bit;}}
        anchor=reduced;
    }
    if(anchor.n>r.polyphony)return result;
    auto acceptable=[&](const voiceleading::ChordVoicing& v)
    {
        if(v.n!=anchor.n||dispositionMask(v)!=needed||(dispositionMask(v)&r.required)!=r.required)return false;
        for(int i=0;i<v.n;++i)if(v.notes[i]<r.low||v.notes[i]>r.high||(i&&v.notes[i]<=v.notes[i-1]))return false;
        const int span=v.notes[v.n-1]-v.notes[0];
        return r.disposition.spacing!=ChordSpacing::open||(span>=policy.minimumOpenSpan&&span<=policy.maximumOpenSpan);
    };
    if(r.disposition.population==ChordPopulation::complete&&r.disposition.spacing==ChordSpacing::natural)
    {result.applied=acceptable(anchor);return result;}
    voiceleading::ChordVoicing best;int cost=1000000;
    auto consider=[&](voiceleading::ChordVoicing candidate)
    {
        voiceleading::sort(candidate);if(!acceptable(candidate))return;
        int value=voiceleading::distance(r.previous,candidate)+voiceleading::shapeCost(candidate,anchor);
        // Retain contextual resolution guidance and existing voice-leading machinery.
        auto led=voiceleading::lead(candidate,r.previous,r.low,r.high,r.descendingSeventh,r.ascendingThird);
        if(acceptable(led))
        {
            const int ledCost=voiceleading::distance(r.previous,led)+voiceleading::shapeCost(led,anchor);
            if(ledCost<value){candidate=led;value=ledCost;}
        }
        if(value<cost){best=candidate;cost=value;}
    };
    consider(anchor);
    // Drop/lift one voice by an octave; never invent a new pitch class or transpose the chord.
    for(int i=0;i<anchor.n;++i)for(int shift:{-12,12}){auto candidate=anchor;candidate.notes[i]+=shift;consider(candidate);}
    if(!best.n)return result;
    result.notes=best;result.omitted=r.chordMask&~needed;result.applied=true;return result;
}
}
