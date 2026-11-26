#pragma once
#include <array>
#include "MusicalTime.h"
#include <cstdlib>
#include <cstdint>
namespace stromscore::composition
{
enum class Mode { automatic,ionian,mixolydian,dorian,aeolian,octatonic };
enum class ModalStatus { unspecified,unique,ambiguous,incompatible };
inline unsigned pitchBit(int pitch){return 1u<<((pitch%12+12)%12);}
inline unsigned modalMask(Mode mode,int tonic)
{
    if(mode==Mode::octatonic){unsigned result=0;for(int step:{0,1,3,4,6,7,9,10})result|=pitchBit(tonic+step);return result;}
    constexpr int steps[4][7]={{0,2,4,5,7,9,11},{0,2,4,5,7,9,10},{0,2,3,5,7,9,10},{0,2,3,5,7,8,10}};
    const int index=static_cast<int>(mode)-1;if(index<0||index>=4)return 0;
    unsigned result=0;for(int n:steps[index])result|=pitchBit(tonic+n);return result;
}
struct ModalContext { Mode mode=Mode::automatic;ModalStatus status=ModalStatus::unspecified;unsigned mask=0;int tonic=0; };
inline ModalContext modalContext(unsigned vocabulary,int tonic,bool tonicEvidence,Mode requested=Mode::automatic)
{
    ModalContext result;result.tonic=(tonic%12+12)%12;
    if(!vocabulary||(vocabulary&~0xfffu))return result;
    // Symmetric collections are explicit authoring contexts, never inferred from
    // a small subset or added to legacy diatonic auto-detection.
    if(requested==Mode::octatonic){
        const auto mask=modalMask(requested,tonic);
        if(vocabulary&~mask){result.status=ModalStatus::incompatible;return result;}
        result.mode=requested;result.mask=mask;result.status=ModalStatus::unique;return result;
    }
    int count=0;
    for(int m=1;m<=4;++m)
    {
        const auto mode=static_cast<Mode>(m);if(requested!=Mode::automatic&&requested!=mode)continue;
        const auto mask=modalMask(mode,tonic);
        if(!(vocabulary&~mask)){++count;result.mode=mode;result.mask=mask;}
    }
    result.status=count==0?ModalStatus::incompatible:count>1?ModalStatus::ambiguous:
        requested==Mode::automatic&&!tonicEvidence?ModalStatus::unspecified:ModalStatus::unique;
    if(result.status!=ModalStatus::unique){result.mode=Mode::automatic;result.mask=0;}
    return result;
}
enum class PitchMembership { excluded,chord,collection };
inline PitchMembership membership(const ModalContext& context,unsigned chordMask,int pitch)
{
    if(chordMask&pitchBit(pitch))return PitchMembership::chord;
    return context.status==ModalStatus::unique&&(context.mask&pitchBit(pitch))?PitchMembership::collection:PitchMembership::excluded;
}
struct PassingPolicy
{
    bool enabled=true;int opportunityStride=3;
    musicaltime::Tick minGap=musicaltime::fromGridStep(4),maxDuration=musicaltime::fromGridStep(2);
    Mode mode=Mode::automatic;int tonicOffset=0;
};
inline bool valid(const PassingPolicy& p)
{return p.opportunityStride>=1&&p.opportunityStride<=64&&p.minGap>=musicaltime::fromGridStep(3)&&p.minGap<=musicaltime::fromGridStep(32)&&p.maxDuration>=musicaltime::fromGridStep(1)&&p.maxDuration<=musicaltime::fromGridStep(4)&&static_cast<int>(p.mode)>=0&&static_cast<int>(p.mode)<=5&&p.tonicOffset>=0&&p.tonicOffset<12;}
struct PassingRequest
{
    ModalContext context;unsigned chordMask=0;int root=0,bassPitchClass=-1,source=0,target=0,low=0,high=127;
    musicaltime::Tick sourceAt{},targetAt{},harmonyBegin{},harmonyEnd{};musicaltime::Tick minDuration=musicaltime::fromGridStep(1),maxDuration=musicaltime::fromGridStep(2);
};
struct PassingTone { bool valid=false;int pitch=0;musicaltime::Tick begin{},end{}; };
inline PassingTone planPassingTone(const PassingRequest& r)
{
    if(r.context.status!=ModalStatus::unique||(r.chordMask&~r.context.mask)||!(r.chordMask&pitchBit(r.root))||!(r.context.mask&pitchBit(r.source))||!(r.context.mask&pitchBit(r.target))||!(r.chordMask&pitchBit(r.source))||!(r.chordMask&pitchBit(r.target)))return {};
    if(std::abs(r.target-r.source)<2||std::abs(r.target-r.source)>4||r.minDuration<musicaltime::fromGridStep(1)||r.maxDuration<r.minDuration||r.maxDuration>musicaltime::fromGridStep(4))return {};
    const int direction=r.target>r.source?1:-1;
    if(r.source<r.low||r.source>r.high||r.target<r.low||r.target>r.high)return {};
    for(int pitch=r.source+direction;pitch!=r.target;pitch+=direction)
    {
        const int a=(pitch-r.source)*direction,b=(r.target-pitch)*direction;
        if(a>2||b>2||a<1||b<1||membership(r.context,r.chordMask,pitch)!=PitchMembership::collection)continue;
        if(pitch<r.low||pitch>r.high)continue;
        // A diatonic semitone against the resolving target is intentional; other chord
        // neighbours, especially the bass/root, are outside this first controlled scope.
        const unsigned resolutionNeighbours=r.context.mode==Mode::octatonic?(pitchBit(r.source)|pitchBit(r.target)):0;
        if((pitchBit(pitch-1)|pitchBit(pitch+1))&((pitchBit(r.root)|pitchBit(r.bassPitchClass<0?r.root:r.bassPitchClass))&~resolutionNeighbours))continue;
        unsigned neighbours=pitchBit(pitch-1)|pitchBit(pitch+1);
        if((r.chordMask&neighbours)&~(pitchBit(r.target)|resolutionNeighbours))continue;
        for(auto duration=r.maxDuration;duration>=r.minDuration;duration-=musicaltime::fromGridStep(1))
        {
            const auto begin=r.targetAt-duration;
            if(duration<musicaltime::fromGridStep(1)||begin<=r.sourceAt||begin<r.harmonyBegin||r.targetAt>=r.harmonyEnd||begin.value%musicaltime::ticksPerQuarter==0)continue;
            return {true,pitch,begin,r.targetAt};
        }
    }
    return {};
}
}
