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
// Prepared musical anchors, independent of Wendung tables and MIDI scheduling.
// Pitches/ranges are before the user's octave offset; negative pitches are valid here.
struct HarmonicSlot
{
    voiceleading::ChordVoicing pad;
    int bass = 48;
    int resolvingSeventh = -1, resolvingThird = -1;
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
            || slot.resolvingSeventh < -1 || slot.resolvingSeventh > 11
            || slot.resolvingThird < -1 || slot.resolvingThird > 11) return result;
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
                r.padRange.low, r.padRange.high, in.resolvingSeventh, in.resolvingThird);
            previousBass = voiceleading::bass(in.bass, previousBass, r.bassRange.low, r.bassRange.high);
            result.slots[static_cast<size_t> (i)] = { previous, previousBass, in.unavailable };
        }
    result.count = r.count; result.valid = true;
    return result;
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
