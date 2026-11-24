#pragma once
#include "CompositionCore.h"
namespace stromscore::composition
{
enum class BassFunction { foundation,pedal,ostinato,melodicLine };
struct BassAttack { bool active=false;int interval=0;Tick duration=musicaltime::sixteenth;int accent=0; };
inline BassAttack funkBassAttack(int position,bool approach)
{
    if(approach)return {true,0,musicaltime::sixteenth,0};
    const int q=position%8;
    if(q==0)return {true,0,2*musicaltime::sixteenth,6};
    if(q==3)return {true,0,musicaltime::sixteenth,-6};
    if(q==5)return {true,7,musicaltime::sixteenth,-8};
    if(q==6&&position%16==14)return {true,12,musicaltime::sixteenth,-4};
    return {};
}
struct BassPhraseRequest
{
    Tick begin{},middle{},end{},barDuration=4*musicaltime::quarter;
    std::array<int,2> bass {},root {};std::array<unsigned,2> chords {};
    Range range;ModalContext modal;Tick minDuration=musicaltime::sixteenth,maxDuration=musicaltime::quarter;int maxLeap=7;
};
struct BassPhrasePlan
{
    struct Note { Tick at{};int pitch=0;Tick length=musicaltime::sixteenth;int accent=0;bool passing=false,anchor=false;int resolution=-1; };
    std::array<Note,64> notes {};int count=0;Tick begin{},middle{},end{};
    BassFunction function=BassFunction::melodicLine;bool valid=false;
};
inline BassPhrasePlan planBassPhrase(const BassPhraseRequest& r)
{
    BassPhrasePlan p;p.begin=r.begin;p.middle=r.middle;p.end=r.end;
    if(r.modal.status!=ModalStatus::unique||r.barDuration!=4*musicaltime::quarter||r.middle-r.begin<r.barDuration||r.end-r.middle<r.barDuration||r.end-r.begin>32*musicaltime::quarter
        ||r.range.low<0||r.range.high>127||r.range.low>r.range.high||r.minDuration<Tick{1}||r.maxDuration<r.minDuration)return p;
    for(int region=0;region<2;++region)
    {
        const auto begin=region?r.middle:r.begin,end=region?r.end:r.middle;
        const int bass=r.bass[region];if(bass<r.range.low||bass>r.range.high||!(r.chords[region]&pitchBit(bass))||(r.chords[region]&~r.modal.mask))return p;
        int third=bass;const int destination=region?r.bass[region]:r.bass[1];
        // A deliberate third provides a small thought; it need not replace repeated roots.
        for(int d:{3,4,-3,-4})if(bass+d>=r.range.low&&bass+d<=r.range.high&&(r.chords[region]&pitchBit(bass+d)))
            {third=bass+d;if(destination>=bass||d<0)break;}
        int previous=bass;
        for(auto at=begin;at<end;at+=musicaltime::sixteenth)
        {
            const bool approach=at==end-2*musicaltime::sixteenth;const auto hit=funkBassAttack(static_cast<int>((at%r.barDuration)/musicaltime::sixteenth),approach);if(!hit.active)continue;
            if(p.count==64)return {};
            int pitch=bass;
            if(at!=begin)
            {
                int ideal=static_cast<int>(bass+(destination-bass)*(at-begin)/(end-begin));
                if(at==begin+5*musicaltime::sixteenth)ideal=third;
                if(destination>=third&&third>bass&&at>begin+5*musicaltime::sixteenth)ideal=std::max(ideal,third);
                int best=100000;
                for(int note=std::max(r.range.low,bass-7);note<=std::min(r.range.high,bass+12);++note)
                {
                    if(!(r.chords[region]&pitchBit(note))||std::abs(note-previous)>r.maxLeap)continue;
                    const int cost=4*std::abs(note-ideal)+std::abs(note-previous);
                    if(cost<best){best=cost;pitch=note;}
                }
                if(best==100000)return {};
            }
            p.notes[p.count++]={at,pitch,hit.duration,hit.accent,false,at==begin,-1};previous=pitch;
        }
    }
    if(p.count<4)return p;
    // Reuse the same controlled diatonic bridge, at an existing syncopated attack.
    for(int i=1;i+1<p.count;++i)
    {
        auto& n=p.notes[i];const auto& before=p.notes[i-1];const auto& target=p.notes[i+1];
        if(n.anchor||before.at<r.middle&&target.at>=r.middle)continue;
        const int region=n.at>=r.middle?1:0;
        PassingRequest q;q.context=r.modal;q.chordMask=r.chords[region];q.root=r.root[region];q.bassPitchClass=r.bass[region]%12;
        q.source=before.pitch;q.target=target.pitch;q.low=r.range.low;q.high=r.range.high;q.sourceAt=before.at;q.targetAt=target.at;
        q.harmonyBegin=region?r.middle:r.begin;q.harmonyEnd=region?r.end:r.middle;q.minDuration=r.minDuration;q.maxDuration=2*musicaltime::sixteenth;
        const auto tone=planPassingTone(q);
        if(tone.valid&&tone.begin==n.at&&target.at-(n.at+n.length)<=musicaltime::sixteenth)
            {n.pitch=tone.pitch;n.passing=true;n.resolution=i+1;break;}
    }
    for(int i=0;i<p.count;++i)
    {
        auto& n=p.notes[i];if(i+1<p.count)n.length=std::min(n.length,p.notes[i+1].at-n.at);
        if(n.length<r.minDuration||n.length>r.maxDuration)return {};
    }
    p.valid=true;return p;
}
}
