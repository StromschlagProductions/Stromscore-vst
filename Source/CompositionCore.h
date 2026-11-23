#pragma once
#include "VoiceLeading.h"
#include <array>
#include <cstdint>
#include <limits>

namespace stromscore::composition
{
// First shared-core slice, not an artist grammar. Musical time is in quarter notes.
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
// One actually emitted motif per scene. No RNG reconstruction or dynamic storage.
struct RememberedMotif
{
    struct Note { int64_t at=0, length=1; int interval=0, velocity=64; };
    std::array<Note,5> notes {};
    int count=0, origin=0;
    uint64_t identity=0;
    int64_t introduction=-1;
    bool complete=false;
    void clear(){*this={};}
    void observe(int pitch,int64_t at,int64_t length,int64_t section,int velocity=64)
    {
        if(complete||count==5)return;
        if(count==0){origin=pitch;introduction=section;}
        notes[static_cast<size_t>(count++)]={at,length,pitch-origin,velocity};
    }
    void finish()
    {
        if(complete||count<2)return;
        identity=1469598103934665603ull;
        for(int i=0;i<count;++i)for(auto value:{notes[static_cast<size_t>(i)].at,notes[static_cast<size_t>(i)].length,static_cast<int64_t>(notes[static_cast<size_t>(i)].interval)})
        {identity^=static_cast<uint64_t>(value);identity*=1099511628211ull;}
        complete=true;
    }
    bool varied(int64_t section)const
    {return recall(section)&&(section-introduction)%4==0;}
    int64_t recalledLength(int index,int64_t section,int64_t phraseEnd)const
    {
        if(index<0||index>=count)return 0;
        const auto& n=notes[static_cast<size_t>(index)];
        auto length=std::max<int64_t>(1,std::min(n.length,phraseEnd-n.at));
        if(!varied(section))return length;
        int chosen=0;
        for(int i=1;i<count;++i)if(notes[static_cast<size_t>(i)].length>notes[static_cast<size_t>(chosen)].length)chosen=i;
        if(index==chosen)length=std::max<int64_t>(1,length/2);
        // The articulated variant has no legato overlaps, even for recorded legato.
        if(index+1<count)length=std::max<int64_t>(1,std::min(length,notes[static_cast<size_t>(index+1)].at-n.at));
        return length;
    }
    bool recall(int64_t section)const
    {return complete&&section>=introduction+2&&(section-introduction)%2==0;}
};
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
    int64_t minDuration=1,maxDuration=32; // Musical ticks, not patch release time.
};
struct PlayingTrack
{
    TrackId id; InstrumentCapabilities instrument;
    PlayingStyle style=PlayingStyle::detached;
    NoteAddressing addressing=NoteAddressing::pitchedNotes;
    unsigned roles=0; bool available=true;
};
inline unsigned roleBit(MusicalRole r){return 1u<<static_cast<unsigned>(r);}
struct RoleNeed
{
    MusicalRole role=MusicalRole::lead; PlayingStyle style=PlayingStyle::sustained;
    PitchBehaviour pitch=PitchBehaviour::pitched; NoteAddressing addressing=NoteAddressing::pitchedNotes; Range range {0,127};
    int polyphony=1; int64_t minDuration=1,maxDuration=32;
};
inline bool suitable(const PlayingTrack& t,const RoleNeed& n)
{
    const auto& c=t.instrument;
    if(static_cast<unsigned>(n.role)>2||static_cast<unsigned>(n.style)>1)return false;
    if(c.range.low<0||c.range.high>127||c.range.low>c.range.high||c.polyphony<1
        ||c.minDuration<1||c.maxDuration<c.minDuration)return false;
    return t.available&&t.id.value>=0&&(t.roles&roleBit(n.role))&&t.style==n.style&&n.pitch!=PitchBehaviour::unknown&&c.pitch==n.pitch&&t.addressing==n.addressing
        &&(c.articulations&(1u<<static_cast<unsigned>(n.style)))
        &&n.range.low>=0&&n.range.high<=127&&n.range.low<=n.range.high
        &&c.range.low<=n.range.low&&c.range.high>=n.range.high
        &&n.polyphony>0&&c.polyphony>=n.polyphony&&n.minDuration>0&&n.maxDuration>=n.minDuration
        &&c.minDuration<=n.minDuration&&c.maxDuration>=n.maxDuration;
}
struct DialogueRoles { TrackId question, response; bool valid=false; };
inline DialogueRoles assignDialogue(const PlayingTrack* tracks,int count,const RoleNeed& question,const RoleNeed& answer)
{
    if(count<0||count>16)return {}; // Bounded candidate batch, not an output-layout definition.
    for(int q=0;q<count;++q)if(suitable(tracks[q],question))
        for(int a=0;a<count;++a)if(tracks[a].id.value!=tracks[q].id.value&&suitable(tracks[a],answer))
            return {tracks[q].id,tracks[a].id,true};
    return {}; // No silent fallback to a patch with incompatible capabilities.
}
// Role scheduling only; MIDI rendering and catalog rules remain outside this data.
struct DialoguePlan { bool reserveResponse=false, answer=false; int answerNotes=0; uint64_t sourceMotif=0; int64_t answerBegin=0, answerEnd=0; };
inline DialoguePlan planDialogue(const RememberedMotif& memory,int64_t section,int64_t relative,int64_t window)
{
    DialoguePlan p;p.sourceMotif=memory.identity;p.reserveResponse=relative<2*window;p.answerBegin=window;p.answerEnd=2*window;
    p.answer=memory.complete&&(section==memory.introduction||memory.recall(section))
        &&relative>=window&&relative<2*window;
    p.answerNotes=p.answer?std::min(3,memory.count):0;
    return p;
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
struct TransitionPlacement { bool present = false; int64_t begin = 0, end = 0; };
inline TransitionPlacement placeTransition (const TransitionIntent& intent, int64_t begin,
                                           int64_t end, int ticksPerBar, int lastGroup)
{
    if(intent.kind!=TransitionKind::passingDominant || ticksPerBar<=0 || lastGroup<0
        || lastGroup>=ticksPerBar || end-begin<ticksPerBar)return {};
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
};
struct HarmonicRequest
{
    static constexpr int capacity = 16;
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
            previous = in.preservePad ? in.pad : voiceleading::lead(in.pad, previous,
                r.padRange.low, r.padRange.high, in.resolution.descendingSeventh, in.resolution.ascendingThird);
            previousBass = voiceleading::bass(in.bass, previousBass, r.bassRange.low, r.bassRange.high);
            result.slots[static_cast<size_t> (i)] = { previous, previousBass, in.unavailable };
        }
    result.count = r.count; result.valid = true;
    return result;
}
// Harmonic intent contains pitch material, not a catalog quality/index.
struct ChordIntent
{
    int root = 0, bassPitchClass = 0, count = 0;
    std::array<int, 5> intervals {};
    bool quartal = false, protectedLine = false;
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
        for(int i=0;i<out.pad.n;++i)
        {
            const int original=out.pad.notes[i]+shift;
            int n=original;while(n<range.low)n+=12;while(n>range.high)n-=12;
            if(n<range.low)
            {
                int chosen=-1000,distance=1000;
                for(int m=range.low;m<=range.high;++m)if((mask>>((m%12+12)%12))&1u)
                {
                    const int d=std::min(std::abs(m-n),std::abs(m-(n+12)));
                    if(d<distance){distance=d;chosen=m;}
                }
                n=chosen!=-1000?chosen:std::clamp(original,range.low,range.high);
            }
            out.pad.notes[i]=n;
        }
        voiceleading::sort(out.pad);
        out.pad.n=static_cast<int>(std::unique(out.pad.notes,out.pad.notes+out.pad.n)-out.pad.notes);
    }
    out.bass=placePitch(in.bassPitchClass,in.bassLow);
    return out;
}
// Integer musical ticks, independent of audio sample rate. An adapter defines ticks/bar.
struct ChordTimeline
{
    std::array<int64_t,8> durations {};
    int count=0, first=0;
    int64_t begin=0,end=0;
    bool held=false;
};
struct ChordPosition { int index=0; int64_t begin=0,end=0; };
inline ChordPosition locateChord (const ChordTimeline& t,int64_t at)
{
    ChordPosition p;
    if(t.count<1||t.count>8)return p;
    p.index=std::clamp(t.first,0,t.count-1);p.begin=t.begin;p.end=t.end;
    if(t.held)return p;
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
