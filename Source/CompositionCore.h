#pragma once
#include "HarmonyLimits.generated.h"
#include "VoiceLeading.h"
#include "MusicalTime.h"
#include "CompositionPolicy.h"
#include <array>
#include <cstdint>
#include <limits>
#include <optional>

namespace stromscore::composition
{
// Motif positions, relative offsets and durations use the shared 960-PPQ Tick.
using musicaltime::Tick;
inline constexpr Tick motifQuantum=musicaltime::sixteenth; // Existing performance articulation/rhythm quantum.
// Whole existing hook/phrase cycles form a thought; breathing happens between cycles,
// never by randomly dropping notes of the characteristic rhythm.
struct HookTurn { bool active=false;Tick begin{},end{}; };
inline HookTurn planHookTurn(const PopRolePolicy& policy,Tick at,Tick cycle,float energy,float unrest)
{
    if(!valid(policy)||cycle<Tick{1}||at<Tick{})return {};
    const auto index=at/cycle;
    const int sounding=energy>=policy.drivenFrom&&unrest>=policy.unrestFrom?2:1;
    const int breath=energy<policy.sparseBelow&&unrest<policy.unrestFrom?2:1;
    return {index%(sounding+breath)<sounding,cycle*index,cycle*(index+1)};
}
enum class Role { pad, bass };
enum class RandomDomain : uint32_t { harmony = 1, motif, rhythm, accent };
inline uint32_t randomKey (uint32_t seed, uint32_t configuration, uint32_t revision,
                           RandomDomain domain, uint32_t event)
{
    uint32_t h = 2166136261u;
    for (auto v : { seed, configuration, revision, static_cast<uint32_t> (domain), event })
    { h ^= v; h *= 16777619u; h ^= h >> 16; }
    return h;
}
struct Range { int low = 0, high = 127; };
// Actually emitted musical material; no voice, timeline or MIDI destination.
struct RememberedMotif
{
    // at is an offset from the motif origin; length is a duration, never an event index.
    struct Note { Tick at{}, length{motifQuantum}; int interval=0, velocity=64; };
    std::array<Note,8> notes {};
    int count=0, origin=0;
    uint32_t vocabularyId=0; // Optional authoring provenance; identity still comes from actual emitted material.
    bool legatoAtCapture=true; // Performance metadata, not part of musical identity.
    Tick cycleLength{};
    bool performedTiming=false; // Captured swing, not a different time unit.
    uint64_t identity=0;
    bool complete=false;
    void clear(){*this={};}
    void observe(int pitch,Tick at,Tick length,int velocity=64)
    {
        if(complete||count==8)return;
        if(count==0)origin=pitch;
        notes[static_cast<size_t>(count++)]={at,length,pitch-origin,velocity};
    }
    void finish()
    {
        if(complete||count<2)return;
        identity=1469598103934665603ull;
        for(int i=0;i<count;++i)for(auto value:{notes[static_cast<size_t>(i)].at.value,notes[static_cast<size_t>(i)].length.value,static_cast<int64_t>(notes[static_cast<size_t>(i)].interval)})
        {identity^=static_cast<uint64_t>(value);identity*=1099511628211ull;}
        // An explicitly recorded cycle includes its trailing rest; neither capture
        // provenance nor a former storage scale contributes to musical identity.
        identity^=static_cast<uint64_t>(cycleLength.value);identity*=1099511628211ull;
        complete=true;
    }
    Tick recalledLength(int index,bool variation,Tick phraseEnd)const
    {
        if(index<0||index>=count)return {};
        const auto& n=notes[static_cast<size_t>(index)];
        auto length=std::max(motifQuantum,std::min(n.length,phraseEnd-n.at));
        if(!variation)return length;
        int chosen=0;
        for(int i=1;i<count;++i)if(notes[static_cast<size_t>(i)].length>notes[static_cast<size_t>(chosen)].length)chosen=i;
        if(index==chosen)length=std::max(motifQuantum,motifQuantum*((length/motifQuantum)/2));
        if(index+1<count)length=std::max(motifQuantum,std::min(length,notes[static_cast<size_t>(index+1)].at-n.at));
        return length;
    }
};
// A performance figure always derives from immutable published source material.
struct MotifFigure
{
    std::array<RememberedMotif::Note,10> notes {};
    uint64_t sourceIdentity=0;
    int count=0;
    int passingIndex=-1;
    bool harmonicallyAdapted=false,durationAdjusted=false,harmonicRealization=false;
    Tick span{};
    MotifVariation variation=MotifVariation::original;
};
inline MotifFigure deriveMotif(const RememberedMotif& source,MotifVariation variation,int sequenceSemitones=7)
{
    MotifFigure figure;figure.sourceIdentity=source.identity;figure.variation=variation;
    if(source.performedTiming||!source.complete||source.count<2||source.count>8||static_cast<int>(variation)<0||static_cast<int>(variation)>4)return figure;
    int first=0,count=source.count;
    if(variation==MotifVariation::fragment){count=std::min(3,count-1);if(count<2)return figure;first=source.count-count;}
    if(variation==MotifVariation::sequence){if(sequenceSemitones==0||std::abs(sequenceSemitones)>12)return figure;count=2;}
    const auto origin=first?source.notes[static_cast<size_t>(first)].at:Tick{};
    Tick originalSpan{};
    for(int i=0;i<source.count;++i)originalSpan=std::max(originalSpan,source.notes[i].at+source.notes[i].length);
    for(int i=0;i<count;++i)
    {
        auto n=source.notes[static_cast<size_t>(first+i)];n.at-=origin;
        if(n.at<Tick{}||n.length<Tick{1}||n.at>motifQuantum*4096||n.length>motifQuantum*4096)return {};
        if(variation==MotifVariation::rhythm)n.length=source.recalledLength(first+i,true,originalSpan);
        if(variation==MotifVariation::augmentation){n.at*=2;n.length*=2;}
        figure.notes[static_cast<size_t>(figure.count++)]=n;
    }
    if(variation==MotifVariation::sequence)
    {
        const auto period=source.count>2?source.notes[2].at:source.notes[1].at+source.notes[1].length;
        if(period<=source.notes[1].at)return {};
        for(int i=0;i<2;++i){auto n=figure.notes[static_cast<size_t>(i)];n.at+=period;n.interval+=sequenceSemitones;figure.notes[static_cast<size_t>(figure.count++)]=n;}
    }
    for(int i=0;i<figure.count;++i)
    {
        auto& n=figure.notes[static_cast<size_t>(i)];
        if(i+1<figure.count)
        {
            const auto gap=figure.notes[static_cast<size_t>(i+1)].at-n.at;
            if(gap<Tick{1})return {};
            if(variation!=MotifVariation::original)n.length=std::min(n.length,gap);
        }
        figure.span=std::max(figure.span,n.at+n.length);
    }
    if(variation!=MotifVariation::original&&figure.count==source.count)
    {
        bool unchanged=true;
        for(int i=0;i<figure.count;++i){const auto& a=figure.notes[i];const auto& b=source.notes[i];unchanged&=a.at==b.at&&a.length==b.length&&a.interval==b.interval;}
        if(unchanged)return {};
    }
    return figure;
}
// Bounded realization of immutable material. Onsets stay exact; fresh placements
// keep the strongest interval. Steps retain direction and move at most two semitones.
// A fixed, already heard prefix permits one semitone of anchor adaptation.
// Duration clipping may remove at most half of a source gate.
struct MotifRealization { MotifFigure figure;int base=-1,cost=10000; };
inline MotifRealization realizeScoreMotif(const MotifFigure& source,const unsigned* masks,
    const Tick* limits,Range range,Tick minimum,Tick maximum,int preferred,const int* fixedPitches=nullptr)
{
    MotifRealization result;
    if(source.count<2||source.count>10||!masks||!limits||minimum<Tick{1}||maximum<minimum)return result;
    auto figure=source;figure.span={};figure.harmonicRealization=true;int anchor=1;
    for(int i=1;i<source.count;++i)
        if(std::abs(source.notes[i].interval-source.notes[i-1].interval)>
           std::abs(source.notes[anchor].interval-source.notes[anchor-1].interval))anchor=i;
    int durationCost=0;
    for(int i=0;i<figure.count;++i)
    {
        auto& note=figure.notes[i];if(!masks[i]||note.at<Tick{}||(i&&note.at<=figure.notes[i-1].at))return result;
        const auto length=std::min({note.length,limits[i],maximum});
        if(length<minimum||length*2<note.length)return result;
        if(length!=note.length){figure.durationAdjusted=true;++durationCost;}
        note.length=length;figure.span=std::max(figure.span,note.at+note.length);
    }
    constexpr int inf=100000;
    // A fixed first pitch permits only these five bases (the existing +/-2
    // realization offsets). Skip mathematically impossible placements, preserving
    // the original ascending tie order and every musical decision.
    int firstBase=0,lastBase=127;
    if(fixedPitches&&fixedPitches[0]>=0){
        const int64_t center=static_cast<int64_t>(fixedPitches[0])-source.notes[0].interval;
        if(center < -2||center>129)return result;
        firstBase=static_cast<int>(std::max<int64_t>(0,center-2));lastBase=static_cast<int>(std::min<int64_t>(127,center+2));
    }
    for(int base=firstBase;base<=lastBase;++base)
    {
        int costs[10][5],previous[10][5];
        for(int i=0;i<figure.count;++i)for(int d=0;d<5;++d)
        {
            costs[i][d]=inf;previous[i][d]=-1;
            const int pitch=base+source.notes[i].interval+d-2;
            if(pitch<0||pitch>127||pitch<range.low||pitch>range.high||!(masks[i]&(1u<<(pitch%12)))
                ||(fixedPitches&&fixedPitches[i]>=0&&pitch!=fixedPitches[i]))continue;
            if(i==0){costs[i][d]=6*std::abs(d-2);continue;}
            const int original=source.notes[i].interval-source.notes[i-1].interval;
            for(int last=0;last<5;++last)
            {
                const int step=original+d-last;
                if((original==0&&step!=0)||(original>0&&step<=0)||(original<0&&step>=0)
                    ||std::abs(step-original)>2||(i==anchor&&std::abs(step-original)>(fixedPitches?1:0)))continue;
                const int cost=costs[i-1][last]+6*std::abs(d-2)+std::abs(step-original);
                if(cost<costs[i][d]){costs[i][d]=cost;previous[i][d]=last;}
            }
        }
        for(int d=0;d<5;++d)
        {
            if(costs[figure.count-1][d]>=inf)continue;
            const int cost=costs[figure.count-1][d]+std::abs(base-preferred)+durationCost*2;
            if(cost>=result.cost)continue;
            auto realized=figure;int choice=d;
            for(int i=figure.count-1;i>=0;--i)
            {realized.notes[i].interval+=choice-2;realized.harmonicallyAdapted|=choice!=2;choice=previous[i][choice];}
            result={realized,base,cost};
        }
    }
    return result;
}
inline MotifFigure suffixFigure(const RememberedMotif& source,int count)
{
    auto figure=deriveMotif(source,MotifVariation::original);
    if(count<2||count>=figure.count)return {};
    const auto first=figure.count-count;const auto at=figure.notes[first].at;
    for(int i=0;i<count;++i)figure.notes[i]=figure.notes[first+i];
    figure.count=count;figure.variation=MotifVariation::fragment;figure.span={};
    for(int i=0;i<count;++i){figure.notes[i].at-=at;figure.span=std::max(figure.span,figure.notes[i].at+figure.notes[i].length);}
    return figure;
}
inline MotifVariation motifVariation(const MotifRecurrencePolicy& policy,int64_t ordinal)
{return ordinal>0?policy.variations[static_cast<size_t>((ordinal-1)%policy.variations.size())]:MotifVariation::original;}
struct MotifRef { int value=-1; };
// Bounded scene catalog. Published material is immutable until the whole scene resets.
struct MotifCatalog
{
private:
    std::array<RememberedMotif,3> materials {};
    int count=0;
public:
    const RememberedMotif* find(MotifRef ref)const
    {return ref.value>=0&&ref.value<count?&materials[static_cast<size_t>(ref.value)]:nullptr;}
    MotifRef publish(const RememberedMotif& material)
    {
        if(!material.complete||count==static_cast<int>(materials.size()))return {};
        materials[static_cast<size_t>(count)]=material;return {count++};
    }
    void clear(){*this={};}
};
// A future role plan must explicitly request adoption; never inferred from catalog contents.
struct MotifReferencePlan
{
    MotifRef material;
    int64_t introduction=-1; // Dimensionless section ordinal.
    Tick originTime{}; // Absolute musical position.
};
struct MotifUse
{
    RememberedMotif draft;
    MotifRef reference;
    int64_t introduction=-1; // Dimensionless section ordinal.
    Tick originTime{}; // Absolute musical position.
    void clear(){*this={};}
    const RememberedMotif& material(const MotifCatalog& catalog)const
    {const auto* published=catalog.find(reference);return published?*published:draft;}
    void observe(int pitch,Tick at,Tick length,int64_t section,int velocity=64,Tick absoluteBegin={})
    {
        if(reference.value>=0)return;
        if(draft.count==0){introduction=section;originTime=absoluteBegin;}
        draft.observe(pitch,at,length,velocity);
    }
    void finish(MotifCatalog& catalog)
    {
        if(reference.value>=0)return;
        draft.finish();if(!draft.complete)return;
        reference=catalog.publish(draft);
        if(reference.value>=0)draft.clear();
    }
    bool adopt(const MotifReferencePlan& plan,const MotifCatalog& catalog)
    {
        if(plan.introduction<0||!catalog.find(plan.material))return false;
        clear();reference=plan.material;introduction=plan.introduction;originTime=plan.originTime;return true;
    }
};
// Common performance capture uses the same PPQ unit as score material.
struct MotifCapture
{
    Tick begin{},end{};
    bool active=false,invalid=false;
    std::array<bool,8> pending {};
    void clear(){*this={};}
    void start(MotifUse& use,Tick at,Tick length)
    {
        clear();use.clear();begin=at;end=at+length;active=true;
        use.originTime=at;use.introduction=0;use.draft.performedTiming=true;use.draft.cycleLength=length;
    }
    void event(MotifUse& use,int pitch,int velocity,Tick at)
    {
        if(!active||at<begin)return;
        auto& m=use.draft;
        for(int i=0;i<m.count;++i)if(pending[i]&&m.origin+m.notes[i].interval==pitch)
        {m.notes[i].length=at-begin-m.notes[i].at;pending[i]=false;if(m.notes[i].length<Tick{1})invalid=true;}
        if(velocity>0&&at<end)
        {
            if(m.count==8){invalid=true;return;}
            const int index=m.count;m.observe(pitch,at-begin,Tick{1},velocity);pending[index]=true;
        }
    }
    void finish(MotifUse& use,MotifCatalog& catalog,Tick at)
    {
        if(!active||at<end)return;
        for(bool open:pending)if(open)return;
        active=false;
        if(invalid||use.draft.count<2){use.clear();return;}
        use.finish(catalog);
    }
};
struct RecordedMotifNote { bool valid=false;int pitch=0,velocity=0;Tick at{},length{}; };
inline RecordedMotifNote replayMotifNote(const RememberedMotif& material,int index)
{
    if(!material.complete||index<0||index>=material.count)return {};
    const auto& n=material.notes[static_cast<size_t>(index)];
    return {true,material.origin+n.interval,n.velocity,n.at,n.length};
}
struct RecurrenceSlot { bool eligible=false;int64_t ordinal=0;int preceding=0;bool lateAllowed=false; };
inline RecurrenceSlot recurrenceSlot(const MotifRecurrencePolicy& policy,int64_t epoch,float energy,float unrest)
{
    if(!valid(policy)||epoch<1)return {};
    const auto& steps=energy<policy.sparseBelow&&unrest<policy.unrestEngages?policy.sparseSteps:policy.normalSteps;
    const int cycle=steps[0]+steps[1]+steps[2];const auto rounds=(epoch-1)/cycle;
    const int position=static_cast<int>((epoch-1)%cycle)+1;int total=0;
    auto eligible=[&](int64_t e)
    {
        if(e<1)return false;const int phase=static_cast<int>((e-1)%cycle)+1;int sum=0;
        for(int n:steps){sum+=n;if(sum==phase)return true;}return false;
    };
    for(int i=0;i<3;++i)
    {
        total+=steps[static_cast<size_t>(i)];
        if(total==position)return {true,rounds*3+i+1,steps[static_cast<size_t>(i)],eligible(epoch-1)&&eligible(epoch-2)};
    }
    return {};
}
struct MotifOccurrence
{
    bool active=false,introduction=false,varied=false;
    Tick begin{},end{}; // Absolute musical positions.
    int64_t ordinal=0;int base=0;
    MotifFigure figure;
};
// Per-use evidence of actually emitted recalls; never stored in the shared material.
struct MotifRepriseProgress
{
    uint64_t identity=0;
    Tick begin{INT64_MIN},end{};
    std::optional<Tick> establishedAt;
    unsigned played=0;int64_t completed=0;
    void observe(const MotifOccurrence& occurrence,int index,int originalCount)
    {
        const auto& figure=occurrence.figure;
        if(!occurrence.active||occurrence.introduction||index<0||index>=figure.count)return;
        if(identity!=figure.sourceIdentity){*this={};identity=figure.sourceIdentity;}
        if(begin!=occurrence.begin){begin=occurrence.begin;end=occurrence.end;played=0;}
        const auto bit=1u<<index;if(played&bit)return;played|=bit;
        if(played!=(1u<<figure.count)-1)return;
        ++completed;
        if(!establishedAt&&figure.variation==MotifVariation::original&&figure.count==originalCount&&figure.passingIndex<0)
            establishedAt=occurrence.end;
    }
};
// Fit the whole dimensionless contour, instead of independently clipping each step.
inline int fittedMotifDegree(const int* degrees,int count,int index,int ladderSize)
{
    if(!degrees||count<1||index<0||index>=count||ladderSize<2)return 0;
    int low=degrees[0],high=low;for(int i=1;i<count;++i){low=std::min(low,degrees[i]);high=std::max(high,degrees[i]);}
    if(high-low<ladderSize)
    {
        const int shift=std::clamp(0,-low,ladderSize-1-high);
        return degrees[index]+shift;
    }
    // A narrow instrument may need a compressed contour, preserving its extrema/order.
    return static_cast<int>(std::lround(double(degrees[index]-low)*(ladderSize-1)/(high-low)));
}
struct MotifPlacement { Tick begin{};int base=0,cost=0; };
inline MotifOccurrence planRecurrence(const MotifRecurrencePolicy& policy,const RecurrenceSlot& slot,
    Tick begin,Tick end,Tick span,Tick bar,
    const MotifPlacement* candidates,int count,Tick responseReserve={})
{
    if(!slot.eligible||!valid(policy)||bar<Tick{1}||span<Tick{1}||count<0||count>32||!candidates)return {};
    const auto last=end-span-policy.minimumSilentBars*bar-responseReserve;
    if(last<begin)return {};
    // Interior entries finish a run of opportunities; after a quiet slot prefer an early return.
    const auto preferred=slot.preceding>1||!slot.lateAllowed||slot.ordinal%2?begin:last;
    int best=-1;int64_t cost=std::numeric_limits<int64_t>::max();
    for(int i=0;i<count;++i)
    {
        const auto& c=candidates[i];if(c.begin<begin||c.begin>last)continue;
        const auto score=c.cost+std::abs((c.begin-preferred).value)*(slot.preceding>1?24:4)/bar.value;
        if(score<cost){best=i;cost=score;}
    }
    if(best<0)return {};
    const auto& c=candidates[best];
    return {true,false,slot.ordinal%2==0,c.begin,c.begin+span,slot.ordinal,c.base};
}
// A role, a playing style, an instrument and a destination are distinct concepts.
enum class MusicalRole { lead, accompaniment, answer };
enum class PlayingStyle { sustained, detached };
enum class PitchBehaviour { unknown, pitched, noise };
enum class NoteAddressing { pitchedNotes, fixedTrigger };
struct TrackId { int value=-1; };
struct MidiTarget { int output=-1, channel=1, fixedNote=36; }; // Not part of role selection.
struct InstrumentCapabilities
{
    PitchBehaviour pitch=PitchBehaviour::unknown;
    unsigned articulations=0; // Bit 0 sustained, bit 1 detached; unknown is not all-capable.
    Range range {0,127}; int polyphony=1;
    Tick minDuration=musicaltime::sixteenth,maxDuration=32*musicaltime::sixteenth;
};
struct PlayingTrack
{
    TrackId id; InstrumentCapabilities instrument;
    PlayingStyle style=PlayingStyle::detached;
    NoteAddressing addressing=NoteAddressing::pitchedNotes;
    unsigned roles=0; bool available=true;
};
inline constexpr unsigned roleBit(MusicalRole r){return 1u<<static_cast<unsigned>(r);}
struct RoleNeed
{
    MusicalRole role=MusicalRole::lead; PlayingStyle style=PlayingStyle::sustained;
    PitchBehaviour pitch=PitchBehaviour::pitched; NoteAddressing addressing=NoteAddressing::pitchedNotes; Range range {0,127};
    int polyphony=1; Tick minDuration=musicaltime::sixteenth,maxDuration=32*musicaltime::sixteenth;
};
inline bool suitable(const PlayingTrack& t,const RoleNeed& n)
{
    const auto& c=t.instrument;
    if(static_cast<unsigned>(n.role)>2||static_cast<unsigned>(n.style)>1)return false;
    if(c.range.low<0||c.range.high>127||c.range.low>c.range.high||c.polyphony<1
        ||c.minDuration<Tick{1}||c.maxDuration<c.minDuration)return false;
    return t.available&&t.id.value>=0&&(t.roles&roleBit(n.role))&&t.style==n.style&&n.pitch!=PitchBehaviour::unknown&&c.pitch==n.pitch&&t.addressing==n.addressing
        &&(c.articulations&(1u<<static_cast<unsigned>(n.style)))
        &&n.range.low>=0&&n.range.high<=127&&n.range.low<=n.range.high
        &&c.range.low<=n.range.low&&c.range.high>=n.range.high
        &&n.polyphony>0&&c.polyphony>=n.polyphony&&n.minDuration>Tick{}&&n.maxDuration>=n.minDuration
        &&c.minDuration<=n.minDuration&&c.maxDuration>=n.maxDuration;
}
enum class CapabilityOrigin { generatorAssumption };
struct OutputDescription
{
    PlayingTrack track; MidiTarget target;
    const char* standardUse=nullptr;
    CapabilityOrigin origin=CapabilityOrigin::generatorAssumption;
    bool externalPatchKnown=false;
};
inline bool validOutputs(const OutputDescription* entries,int count)
{
    if(!entries||count!=9)return false; // Current adapter layout, not a musical role limit.
    for(int i=0;i<count;++i)
    {
        const auto& e=entries[i];const auto& c=e.track.instrument;
        if(!e.standardUse||e.externalPatchKnown||static_cast<unsigned>(e.track.style)>1)return false;
        if(e.target.output<0||e.target.output>=count||e.target.channel<1||e.target.channel>16
            ||e.track.id.value<0||c.range.low<0||c.range.high>127||c.range.low>c.range.high
            ||c.polyphony<1||c.minDuration<Tick{1}||c.maxDuration<c.minDuration
            ||!(c.articulations&(1u<<static_cast<unsigned>(e.track.style))))return false;
        if(e.track.addressing==NoteAddressing::fixedTrigger
            &&(e.target.fixedNote<0||e.target.fixedNote>127))return false;
        for(int j=0;j<i;++j)if(entries[j].target.output==e.target.output||entries[j].track.id.value==e.track.id.value)return false;
    }
    return true;
}
inline int addressedPitch(const OutputDescription& output,int pitchedNote)
{return output.track.addressing==NoteAddressing::fixedTrigger?output.target.fixedNote:pitchedNote;}
struct DialogueRoles { TrackId question, response; bool valid=false; };
inline DialogueRoles assignDialogue(const PlayingTrack* tracks,int count,const RoleNeed& question,const RoleNeed& answer)
{
    if(count<0||count>16)return {}; // Bounded candidate batch, not an output-layout definition.
    for(int q=0;q<count;++q)if(suitable(tracks[q],question))
        for(int a=0;a<count;++a)if(tracks[a].id.value!=tracks[q].id.value&&suitable(tracks[a],answer))
            return {tracks[q].id,tracks[a].id,true};
    return {}; // No silent fallback to a patch with incompatible capabilities.
}
// Explicit foreground intent: default background leaves existing thematic roles untouched.
struct ForegroundPlan { bool foreground=false; TrackId lead; };
inline ForegroundPlan planForeground(bool requested,const PlayingTrack& candidate)
{
    RoleNeed need;need.range=candidate.instrument.range;
    return requested&&suitable(candidate,need)?ForegroundPlan{true,candidate.id}:ForegroundPlan{};
}
// Sparse melody-to-dialog handoff. Material selection and timing belong to the role plan.
struct MotifHandoffPlan
{
    bool active=false;
    MotifReferencePlan reference;
    int first=0,count=0;
    Tick begin{},end{}; // Relative to the role-plan handoff origin.
};
inline MotifHandoffPlan planMelodyHandoff(bool requested,const MotifUse& source,
    const MotifCatalog& catalog,const PlayingTrack& target,int64_t epoch,Tick bar,Tick window,
    const MotifRecurrencePolicy& policy,float energy,float unrest,bool leading)
{
    MotifHandoffPlan p;RoleNeed need;need.role=MusicalRole::answer;need.range=target.instrument.range;
    const auto* material=catalog.find(source.reference);
    if(!requested||leading||!suitable(target,need)||!material||material->count<3||bar<Tick{1}||window<4*bar||epoch<1)return p;
    const auto group=(epoch-1)/4;int64_t quiet=-1;
    for(int i=1;i<=4;++i)if(!recurrenceSlot(policy,group*4+i,energy,unrest).eligible){quiet=group*4+i;break;}
    if(epoch!=quiet)return p;
    p.count=std::min(3,material->count-1);p.first=material->count-p.count;p.begin=bar;
    const auto& last=material->notes[static_cast<size_t>(material->count-1)];
    p.end=p.begin+last.at-material->notes[static_cast<size_t>(p.first)].at+last.length;
    if(p.end>window||p.end-p.begin>2*bar)return {};
    p.reference={source.reference,source.introduction+epoch,source.originTime+epoch*window};p.active=true;return p;
}
struct DialoguePlan { bool reserveResponse=false,answer=false;int answerNotes=0;uint64_t sourceMotif=0;Tick answerBegin{},answerEnd{}; };
inline DialoguePlan planDialogue(const MotifUse& use,const MotifCatalog& catalog,const MotifOccurrence& question,Tick at,Tick window)
{
    const auto& memory=use.material(catalog);DialoguePlan p;p.sourceMotif=memory.identity;
    p.answerBegin=std::max(question.end,question.begin+window);p.answerEnd=p.answerBegin+window;
    p.reserveResponse=question.active&&at>=question.begin&&at<p.answerEnd;
    p.answer=memory.complete&&p.reserveResponse&&at>=p.answerBegin;
    p.answerNotes=p.answer?std::min(3,memory.count):0;return p;
}
// A bounded free-line thought over an actual harmonic region, not a fixed bar grammar.
enum class PhraseEnding { open, settled };
struct LinePhraseRequest
{
    Tick begin{},end{},pulse=musicaltime::quarter;
    std::array<int,16> pitches {};int count=0,goalPitchClass=0,notes=3;
    bool descending=true,legato=true;int initialNeighbour=0;
    Range range;PhraseEnding ending=PhraseEnding::open;
};
struct LinePhrasePlan
{
    struct Note { Tick begin{},end{};int pitch=0; };
    std::array<Note,5> notes {};int count=0,goal=0;
    Tick begin{},end{},arrival{},breath{};
    PhraseEnding ending=PhraseEnding::open;
    bool valid=false;
};
inline LinePhrasePlan planLinePhrase(const LinePhraseRequest& r)
{
    LinePhrasePlan p;
    if(r.count<3||r.count>16||r.pulse<Tick{1}||r.begin<Tick{}||r.end-r.begin<4*r.pulse
        ||r.notes<2||r.notes>4||r.goalPitchClass<0||r.goalPitchClass>11)return p;
    int goal=-1,best=10000;const int centre=(r.pitches[0]+r.pitches[static_cast<size_t>(r.count-1)])/2;
    for(int i=0;i<r.count;++i)
    {
        const int pitch=r.pitches[static_cast<size_t>(i)];
        if(pitch<r.range.low||pitch>r.range.high||(i&&pitch<=r.pitches[static_cast<size_t>(i-1)]))return {};
        if((pitch%12+12)%12==r.goalPitchClass&&(std::abs(pitch-centre)<best
            ||(!r.descending&&std::abs(pitch-centre)==best)))
        {goal=i;best=std::abs(pitch-centre);}
    }
    if(goal<0)return p;
    int start=std::clamp(goal+(r.descending?3:-3),0,r.count-1);
    if(std::abs(start-goal)<2)start=std::clamp(goal+(r.descending?-3:3),0,r.count-1);
    if(start==goal)return p;
    p.begin=r.begin;p.end=r.end;p.breath=r.end-r.pulse;p.arrival=p.breath-r.pulse;
    p.goal=r.pitches[static_cast<size_t>(goal)];p.ending=r.ending;
    auto begin=r.begin;
    const int neighbour=r.pitches[static_cast<size_t>(start)]+r.initialNeighbour;
    if(r.initialNeighbour>0&&p.arrival-begin>=3*r.pulse&&neighbour>=r.range.low&&neighbour<=r.range.high)
    {p.notes[static_cast<size_t>(p.count++)]={begin,begin+r.pulse+(r.legato?musicaltime::sixteenth:-1*musicaltime::sixteenth),neighbour};begin+=r.pulse;}
    p.arrival=begin+((p.arrival-begin)/r.pulse)*r.pulse;
    const int count=std::min({r.notes,std::abs(goal-start)+1,static_cast<int>(1+(p.arrival-begin)/r.pulse)});
    for(int i=0;i<count;++i)
    {
        const auto at=begin+((p.arrival-begin)*i/(count-1)/r.pulse)*r.pulse;
        const int index=i==count-2&&count>=3?goal+(start>goal?1:-1):start+(goal-start)*i/(count-1);
        p.notes[static_cast<size_t>(p.count++)]={at,{},r.pitches[static_cast<size_t>(index)]};
    }
    for(int i=(begin>r.begin?1:0);i<p.count;++i)
    {
        auto& n=p.notes[static_cast<size_t>(i)];
        const auto next=i+1<p.count?p.notes[static_cast<size_t>(i+1)].begin:p.breath;
        n.end=i+1==p.count?p.breath:std::max(n.begin+musicaltime::sixteenth,next+(r.legato?musicaltime::sixteenth:-1*musicaltime::sixteenth));
    }
    p.valid=true;return p;
}

// Density removes optional metrical groups, never changes expression or pitch material.
struct EventDensity
{
    float amount=1.f;
    bool allows(int group,int groups)const
    {
        if(groups<1||group<0||group>=groups)return false;
        const int keep=std::clamp(static_cast<int>(std::ceil(std::clamp(amount,0.f,1.f)*groups)),0,groups);
        // In 4/4: beats 1,3,2,4. Nested masks, no RNG, first group retained at any positive density.
        const int rank=group%2==0?group/2:(groups+1)/2+group/2;
        return rank<keep;
    }
};
// A bounded role-plan window, independent of MIDI channels and arpeggio figures.
struct MotifWindow
{
    TrackId owner;
    Tick begin{},end{};
    bool contains(Tick tick)const{return owner.value>=0&&tick>=begin&&tick<end;}
};
inline MotifWindow reserveMotifWindow(TrackId owner,int notes,Tick begin,Tick end)
{return owner.value>=0&&notes>=2&&begin>=Tick{}&&end>begin?MotifWindow{owner,begin,end}:MotifWindow{};}
// Bound phrasing for a monophonic target: touching gates, never overlapping claims.
inline Tick articulatedLength(Tick recorded,Tick available,bool legato)
{
    return std::max(motifQuantum,std::min(recorded,std::max(motifQuantum,available-(legato?Tick{}:motifQuantum))));
}
inline int adaptMotifPitch(int desired,const int* ladder,int count)
{
    if(count<=0)return desired;
    int best=ladder[0];
    for(int i=1;i<count;++i)if(std::abs(ladder[i]-desired)<std::abs(best-desired))best=ladder[i];
    return best;
}
// Musical transition data; neither MIDI channels nor concrete voice assignments.
enum class TransitionKind { direct, passingDominant };
struct ResolutionIntent
{
    int descendingSeventh = -1; // prefer a downward step from this pitch class
    int ascendingThird = -1;    // prefer an upward semitone from this pitch class
};
struct TransitionIntent
{
    TransitionKind kind = TransitionKind::direct;
    int targetRoot = 0, approachRoot = 0;
};
// Existing free-mode strategy. Other strategies may produce the same intent types.
inline TransitionIntent freeTransition (int targetRoot, bool enabled, float intensity, bool held = false)
{
    return { enabled && intensity >= .6f && !held ? TransitionKind::passingDominant : TransitionKind::direct,
             targetRoot, (targetRoot + 7) % 12 };
}
struct TransitionPlacement { bool present = false; musicaltime::Tick begin {}, end {}; };
inline TransitionPlacement placeTransition (const TransitionIntent& intent, musicaltime::Tick begin,
                                           musicaltime::Tick end, musicaltime::Tick ticksPerBar, musicaltime::Tick lastGroup)
{
    if(intent.kind!=TransitionKind::passingDominant || ticksPerBar<=musicaltime::Tick{} || lastGroup<musicaltime::Tick{}
        || !(lastGroup<ticksPerBar) || end-begin<ticksPerBar)return {};
    return {true,end-(ticksPerBar-lastGroup),end};
}
inline ResolutionIntent dominantResolution (int sourceRoot, bool sourceDominant, int targetRoot, int key)
{
    if(!sourceDominant || (targetRoot-sourceRoot+12)%12!=5)return {};
    return {(key+sourceRoot+10)%12,(key+sourceRoot+4)%12};
}
// Prepared musical anchors, independent of Wendung tables and MIDI scheduling.
// Pitches/ranges are before the user's octave offset; negative pitches are valid here.
struct HarmonicSlot
{
    voiceleading::ChordVoicing pad;
    int bass = 48;
    ResolutionIntent resolution;
    uint32_t unavailable = 0;
    bool enabled = true, preservePad = false;
    voiceleading::VoiceBinding binding;
};
struct HarmonicRequest
{
    static constexpr int capacity = 2*kCatalogChordSlots;
    std::array<HarmonicSlot, capacity> slots {};
    int count = 0;
    Range padRange { 0, 127 }, bassRange { 0, 127 };
    bool cyclic = true;
};
struct HarmonicPlan
{
    struct Slot { voiceleading::ChordVoicing pad; int bass = 0; uint32_t unavailable = 0; };
    std::array<Slot, HarmonicRequest::capacity> slots {};
    int count = 0;
    bool valid = false;
};
// Fixed two passes for cyclic plans; linear plans start without a preceding chord.
// Bounded and allocation-free, suitable for the free-mode audio-thread cache miss.
inline HarmonicPlan planHarmony (const HarmonicRequest& r)
{
    HarmonicPlan result;
    auto validRange = [] (Range v) { return v.low >= -128 && v.high <= 255 && v.low <= v.high; };
    if (r.count < 1 || r.count > HarmonicRequest::capacity
        || ! validRange(r.padRange) || ! validRange(r.bassRange)) return result;
    int last = -1;
    for (int i = 0; i < r.count; ++i)
    {
        const auto& slot = r.slots[static_cast<size_t> (i)];
        if (slot.pad.n < 0 || slot.pad.n > 6 || slot.bass < -128 || slot.bass > 255
            || slot.resolution.descendingSeventh < -1 || slot.resolution.descendingSeventh > 11
            || slot.resolution.ascendingThird < -1 || slot.resolution.ascendingThird > 11) return result;
        if(slot.binding.required.n<0||slot.binding.required.n>6||slot.binding.preferred.n<0||slot.binding.preferred.n>6)return result;
        for(const auto* tones:{&slot.binding.required,&slot.binding.preferred})
            for(int n=0;n<tones->n;++n)
            {
                const int note=tones->notes[n];
                if(note < -128 || note > 255 || (tones==&slot.binding.required&&(note<r.padRange.low||note>r.padRange.high)))return result;
                for(int j=0;j<n;++j)if(note==tones->notes[j])return result;
            }
        for (int n = 0; n < slot.pad.n; ++n)
            if (slot.pad.notes[static_cast<size_t> (n)] < -128 || slot.pad.notes[static_cast<size_t> (n)] > 255) return result;
        if (slot.enabled) last = i;
    }
    if (last < 0) return result;
    auto previous = r.cyclic ? r.slots[static_cast<size_t> (last)].pad : voiceleading::ChordVoicing{};
    int previousBass = r.cyclic ? r.slots[static_cast<size_t> (last)].bass : -1;
    for (int cycle = 0; cycle < (r.cyclic ? 2 : 1); ++cycle)
        for (int i = 0; i < r.count; ++i)
        {
            const auto& in = r.slots[static_cast<size_t> (i)];
            if (! in.enabled) continue;
            if(in.binding.required.n&&!voiceleading::satisfies(previous,in.binding.required))return HarmonicPlan{};
            previous = in.preservePad ? in.pad : voiceleading::lead(in.pad, previous,
                r.padRange.low, r.padRange.high, in.resolution.descendingSeventh, in.resolution.ascendingThird,
                in.binding.required.n||in.binding.preferred.n?&in.binding:nullptr);
            if(in.binding.required.n&&!voiceleading::satisfies(previous,in.binding.required))return HarmonicPlan{};
            previousBass = voiceleading::bass(in.bass, previousBass, r.bassRange.low, r.bassRange.high);
            result.slots[static_cast<size_t> (i)] = { previous, previousBass, in.unavailable };
        }
    result.count = r.count; result.valid = true;
    return result;
}
// An entry is realised once from the preceding performance, without replanning the vocabulary.
struct HarmonicEntry
{
    voiceleading::ChordVoicing pad;
    int bass = 0;
    bool hasBass = false;
    ResolutionIntent resolution;
};
inline HarmonicPlan::Slot leadEntry(HarmonicPlan::Slot target,const HarmonicEntry& previous,
                                    Range padRange,Range bassRange,const HarmonicPlan::Slot* following=nullptr)
{
    auto candidate=target;
    candidate.pad=voiceleading::lead(target.pad,previous.pad,padRange.low,padRange.high,
        previous.resolution.descendingSeventh,previous.resolution.ascendingThird);
    if(previous.hasBass)candidate.bass=voiceleading::bass(target.bass+128,previous.bass+128,
        bassRange.low+128,bassRange.high+128)-128;
    if(following)
    {
        auto cost=[&](const voiceleading::ChordVoicing& v)
        {
            int result=voiceleading::distance(previous.pad,v)+voiceleading::distance(v,following->pad)
                +voiceleading::shapeCost(v,target.pad);
            for(int i=0;i<v.n;++i)if(voiceleading::contains(previous.pad,v.notes[i]))result-=8;
            return result;
        };
        if(cost(candidate.pad)>=cost(target.pad))candidate.pad=target.pad;
        if(previous.hasBass&&voiceleading::motion(previous.bass,candidate.bass)+voiceleading::motion(candidate.bass,following->bass)
            +2*std::abs(candidate.bass-target.bass)>=voiceleading::motion(previous.bass,target.bass)
            +voiceleading::motion(target.bass,following->bass))candidate.bass=target.bass;
    }
    return candidate;
}
// Harmonic intent contains pitch material, not a catalog quality/index.
struct ChordIntent
{
    int root = 0, bassPitchClass = 0, count = 0;
    std::array<int, 5> intervals {};
    bool quartal = false, protectedLine = false, preservePitchClasses = false;
    int voicing = 0, padLow = 62, bassLow = 45;
    float intensity = 0;
};
inline int placePitch (int note, int low)
{ while(note<low)note+=12; while(note>=low+12)note-=12; return note; }
inline HarmonicSlot buildAnchor (const ChordIntent& in, Range range, bool constrain)
{
    HarmonicSlot out; out.preservePad=in.protectedLine;
    if(in.count<1||in.count>5||range.low < -128||range.high>255||range.low>range.high
        ||in.root<0||in.root>23||in.voicing<0||in.voicing>2)return out;
    const int root=placePitch(in.root,in.padLow-(in.voicing==1?5:12));
    for(int i=0;i<in.count;++i)
    {
        const int iv=in.intervals[static_cast<size_t>(i)];
        bool low=iv==0||iv==7||(iv==5&&in.quartal)||iv>=12;
        if(in.voicing==1)low=true;
        if(in.voicing==2&&iv==0)low=false;
        out.pad.notes[out.pad.n++]=root+iv+(low?0:12);
    }
    if((in.protectedLine&&in.count==3)||(!in.protectedLine&&in.intensity>.6f))out.pad.notes[out.pad.n++]=root+24;
    voiceleading::sort(out.pad);
    uint32_t mask=0;
    for(int i=0;i<out.pad.n;++i)
    {
        const int pc=(out.pad.notes[i]%12+12)%12;mask|=1u<<pc;
        bool found=false;
        for(int n=range.low;n<=range.high;++n)if((n%12+12)%12==pc)found=true;
        if(!found)out.unavailable|=1u<<pc;
    }
    if(constrain)
    {
        int shift=0,best=-1;
        for(int sh:{0,12,-12,24,-24,36,-36,48,-48})
        {
            int count=0;for(int i=0;i<out.pad.n;++i)count+=out.pad.notes[i]+sh>=range.low&&out.pad.notes[i]+sh<=range.high;
            if(count>best){best=count;shift=sh;}
        }
        int written=0;
        for(int i=0;i<out.pad.n;++i)
        {
            const int original=out.pad.notes[i]+shift;
            int n=original;while(n<range.low)n+=12;while(n>range.high)n-=12;
            if(n<range.low)
            {
                if(in.preservePitchClasses)continue; // Never repair an unavailable authored class with a substitute.
                int chosen=-1000,distance=1000;
                for(int m=range.low;m<=range.high;++m)if((mask>>((m%12+12)%12))&1u)
                {
                    const int d=std::min(std::abs(m-n),std::abs(m-(n+12)));
                    if(d<distance){distance=d;chosen=m;}
                }
                n=chosen!=-1000?chosen:std::clamp(original,range.low,range.high);
            }
            out.pad.notes[written++]=n;
        }
        out.pad.n=written;
        voiceleading::sort(out.pad);
        out.pad.n=static_cast<int>(std::unique(out.pad.notes,out.pad.notes+out.pad.n)-out.pad.notes);
    }
    out.bass=placePitch(in.bassPitchClass,in.bassLow);
    return out;
}
// Integer musical ticks, independent of audio sample rate. An adapter defines ticks/bar.
struct ChordTimeline
{
    std::array<musicaltime::Tick,kCatalogChordSlots> durations {};
    int count=0, first=0;
    musicaltime::Tick begin{},end{};
    bool held=false,cyclicFromFirst=false;
};
struct ChordPosition { int index=0; musicaltime::Tick begin{},end{}; };
inline ChordPosition locateChord (const ChordTimeline& t,musicaltime::Tick at)
{
    ChordPosition p;
    if(t.count<1||t.count>kCatalogChordSlots)return p;
    p.index=std::clamp(t.first,0,t.count-1);p.begin=t.begin;p.end=t.end;
    if(t.held)return p;
    if(t.cyclicFromFirst){
        const int first=p.index;
        for(int i=0;i<t.count;++i){p.index=(first+i)%t.count;
            if(at<p.begin+t.durations[static_cast<size_t>(p.index)]||i==t.count-1)break;
            p.begin+=t.durations[static_cast<size_t>(p.index)];
        }
        p.end=std::min(t.end,p.begin+t.durations[static_cast<size_t>(p.index)]);return p;
    }
    for(int i=p.index;i<t.count;++i)
    {
        p.index=i;
        if(at<p.begin+t.durations[static_cast<size_t>(i)]||i==t.count-1)break;
        p.begin+=t.durations[static_cast<size_t>(i)];
    }
    p.end=p.index==t.count-1?t.end:std::min(t.end,p.begin+t.durations[static_cast<size_t>(p.index)]);
    return p;
}
struct Harmony { int root = 0; int count = 4; std::array<int, 5> intervals { 0, 4, 7, 11, 0 }; };
struct Request
{
    uint32_t configurationId = 1, revision = 1;
    // Required user harmony: two two-bar spans in a four-bar 4/4 scene.
    std::array<Harmony, 2> harmony {{ {}, { 5, 4, { 0, 4, 7, 11, 0 } } }};
    int pedalPitchClass = 0;
    Range padRange { 60, 84 }, bassRange { 36, 48 };
    int padChannel = 1, bassChannel = 2;
    bool mutePad = false, muteBass = false;
    float intensity = 0.2f; // Velocity only: required colours never removed.
    double sampleRate = 48000, bpm = 120;
};
enum class Error { none, invalidIdentity, invalidClock, invalidHarmony, invalidRange,
                   invalidChannel, invalidIntensity, requiredToneUnavailable };
struct NoteSpan { int64_t begin = 0, end = 0; int channel = 1, pitch = 60, velocity = 64; Role role = Role::pad; };
class Plan
{
public:
    static constexpr int capacity = 11; // 2 * 5 pad voices + one pedal
    bool valid() const { return ready; }
    int size() const { return count; }
    const NoteSpan& note (int i) const { return notes[static_cast<size_t> (i)]; }
    int64_t duration() const { return length; }
    uint32_t configurationId() const { return id; }
    uint32_t revision() const { return rev; }
private:
    friend struct Compiler;
    std::array<NoteSpan, capacity> notes {};
    int count = 0;
    int64_t length = 0;
    uint32_t id = 0, rev = 0;
    bool ready = false;
};
struct CompileResult { Error error = Error::none; Plan plan; };
struct Compiler
{
    // Call outside the audio callback. Failure never exposes a partial playable plan.
    static CompileResult compile (const Request& r)
    {
        CompileResult result;
        auto fail = [&] (Error e) { result.error = e; result.plan = {}; return result; };
        if (! r.configurationId || ! r.revision) return fail (Error::invalidIdentity);
        if (! std::isfinite (r.sampleRate) || ! std::isfinite (r.bpm)
            || r.sampleRate < 8000 || r.sampleRate > 384000 || r.bpm < 10 || r.bpm > 400)
            return fail (Error::invalidClock);
        for (auto range : { r.padRange, r.bassRange })
            if (range.low < 0 || range.high > 127 || range.low > range.high) return fail (Error::invalidRange);
        if (r.padChannel < 1 || r.padChannel > 16 || r.bassChannel < 1 || r.bassChannel > 16)
            return fail (Error::invalidChannel);
        if (! std::isfinite (r.intensity) || r.intensity < 0 || r.intensity > 1)
            return fail (Error::invalidIntensity);
        if (r.pedalPitchClass < 0 || r.pedalPitchClass > 11) return fail (Error::invalidHarmony);
        for (const auto& h : r.harmony)
        {
            if (h.root < 0 || h.root > 11 || h.count < 1 || h.count > 5) return fail (Error::invalidHarmony);
            for (int i = 0; i < h.count; ++i)
            {
                if (h.intervals[static_cast<size_t> (i)] < 0 || h.intervals[static_cast<size_t> (i)] > 36) return fail (Error::invalidHarmony);
                for (int j = 0; j < i; ++j)
                    if (h.intervals[static_cast<size_t> (i)] % 12 == h.intervals[static_cast<size_t> (j)] % 12) return fail (Error::invalidHarmony);
            }
        }
        auto& p = result.plan;
        p.length = std::llround (16.0 * r.sampleRate * 60.0 / r.bpm);
        p.id = r.configurationId; p.rev = r.revision;
        const auto middle = std::llround (8.0 * r.sampleRate * 60.0 / r.bpm);
        const int velocity = 40 + static_cast<int> (std::lround (r.intensity * 50));
        HarmonicRequest harmonic; harmonic.count = 2; harmonic.cyclic = false;
        harmonic.padRange = r.padRange; harmonic.bassRange = r.bassRange;
        if (! r.mutePad) for (int section = 0; section < 2; ++section)
        {
            const auto& h = r.harmony[static_cast<size_t> (section)];
            voiceleading::ChordVoicing anchor;
            for (int i = 0; i < h.count; ++i)
            {
                const int pc = (h.root + h.intervals[static_cast<size_t> (i)]) % 12;
                const int pitch = r.padRange.low + (pc - r.padRange.low % 12 + 12) % 12;
                if (pitch > r.padRange.high) return fail (Error::requiredToneUnavailable);
                anchor.notes[anchor.n++] = pitch;
            }
            harmonic.slots[static_cast<size_t> (section)].pad = anchor;
        }
        const auto voicedPlan = planHarmony(harmonic);
        if (! voicedPlan.valid) return fail(Error::invalidHarmony);
        if (! r.mutePad) for (int section = 0; section < 2; ++section)
        {
            const auto& voiced = voicedPlan.slots[static_cast<size_t> (section)].pad;
            for (int i = 0; i < voiced.n; ++i)
                p.notes[static_cast<size_t> (p.count++)] = { section == 0 ? 0 : middle, section == 0 ? middle : p.length,
                                      r.padChannel, voiced.notes[static_cast<size_t> (i)], velocity, Role::pad };
        }
        if (! r.muteBass)
        {
            const int pitch = r.bassRange.low + (r.pedalPitchClass - r.bassRange.low % 12 + 12) % 12;
            if (pitch > r.bassRange.high) return fail (Error::requiredToneUnavailable);
            p.notes[static_cast<size_t> (p.count++)] = { 0, p.length, r.bassChannel, pitch, velocity, Role::bass };
        }
        p.ready = true;
        return result;
    }
};
struct MidiEvent { int offset = 0, channel = 1, pitch = 60, velocity = 0; };
struct Events
{
    // Each of 11 spans can start/end once, plus at most 11 old offs + 11 chase ons.
    static constexpr int capacity = 4 * Plan::capacity;
    std::array<MidiEvent, capacity> items {};
    int size = 0;
};
class Renderer
{
public:
    // Same-thread API. A processor adapter must publish plans safely outside this class.
    bool setNextScene (const Plan& p) { if (! p.valid()) return false; pending = p; return true; }
    // Explicit new scene only: queued configuration is latched here, never on seek/loop.
    Events start()
    {
        Events out; silence (out);
        activePlan = pending; running = activePlan.valid(); expected = -1;
        return out;
    }
    Events stop() { Events out; silence (out); running = false; expected = -1; return out; }
    uint32_t activeConfiguration() const { return activePlan.configurationId(); }
    // Half-open scene-local sample interval. Tempo/sample rate are fixed by the compiled plan.
    // A discontinuity (including loop) releases old notes and chases the canonical target state.
    Events process (int64_t position, int samples, bool discontinuity = false)
    {
        Events out;
        if (! running) return out;
        if (position < 0 || samples <= 0 || position > std::numeric_limits<int64_t>::max() - samples)
        { silence (out); expected = -1; return out; }
        if (discontinuity || position != expected) silence (out);
        reconcile (position, 0, out);
        const int64_t end = position + samples;
        int64_t cursor = position;
        // At most 2 * capacity distinct boundaries, independent of block length.
        for (;;)
        {
            int64_t next = end;
            for (int i = 0; i < activePlan.size(); ++i)
            {
                const auto& n = activePlan.note (i);
                if (n.begin > cursor && n.begin < next) next = n.begin;
                if (n.end > cursor && n.end < next) next = n.end;
            }
            if (next == end) break;
            reconcile (next, static_cast<int> (next - position), out); cursor = next;
        }
        expected = end;
        return out;
    }
private:
    struct Sounding { int channel = 1, pitch = 60, velocity = 64; };
    static bool same (const Sounding& a, const Sounding& b) { return a.channel == b.channel && a.pitch == b.pitch; }
    static bool contains (const std::array<Sounding, Plan::capacity>& a, int count, const Sounding& n)
    { for (int i = 0; i < count; ++i) if (same (a[static_cast<size_t> (i)], n)) return true; return false; }
    static void emit (Events& out, int offset, const Sounding& n, bool on)
    { out.items[static_cast<size_t> (out.size++)] = { offset, n.channel, n.pitch, on ? n.velocity : 0 }; }
    void silence (Events& out)
    { for (int i = 0; i < count; ++i) emit (out, 0, sounding[static_cast<size_t> (i)], false); count = 0; }
    void reconcile (int64_t at, int offset, Events& out)
    {
        std::array<Sounding, Plan::capacity> desired {}; int num = 0;
        for (int i = 0; i < activePlan.size(); ++i)
        {
            const auto& n = activePlan.note (i);
            if (n.begin <= at && at < n.end)
            {
                Sounding s { n.channel, n.pitch, n.velocity };
                if (! contains (desired, num, s)) desired[static_cast<size_t> (num++)] = s;
            }
        }
        // Ownership is aggregated before output: a shared/common note stays held.
        for (int i = 0; i < count; ++i)
            if (! contains (desired, num, sounding[static_cast<size_t> (i)])) emit (out, offset, sounding[static_cast<size_t> (i)], false);
        for (int i = 0; i < num; ++i)
            if (! contains (sounding, count, desired[static_cast<size_t> (i)])) emit (out, offset, desired[static_cast<size_t> (i)], true);
        sounding = desired; count = num;
    }
    Plan pending, activePlan;
    std::array<Sounding, Plan::capacity> sounding {};
    int count = 0;
    bool running = false;
    int64_t expected = -1;
};
}
