#pragma once
// STROMSCORE – Notengenerator (reines C++ ohne JUCE, echtzeitsicher: keine Speicheranforderung im process()).
// Version 0.1: erzeugt synchron zum Host auf fuenf MIDI-Kanaelen einfache, zur Tonart passende Noten.
// Kanal 1 Flaeche, 2 Bass, 3 Arp/Ostinato, 4 Farbe, 5 Akzente. VERLAUF (0..1) bestimmt Dichte und welche Ebenen mitspielen.
// Alles haengt nur von der Taktposition ab: gleiche Einstellung = gleiche Noten, unabhaengig von der Puffergroesse.
#include <array>
#include <cmath>
#include <cstdint>
#include <algorithm>

namespace stromscore
{
constexpr int kNumLayers = 5;
enum Layer { kFlaeche = 0, kBass = 1, kArp = 2, kFarbe = 3, kAkzente = 4 };
constexpr int kNumModes = 5;
constexpr int kNumKeys = 12;
constexpr double kStep = 0.25;             // ein Rasterschritt = 1/16 (in Viertelnoten)
constexpr int kStepsPerBar = 16;           // 0.1 rechnet in 4/4
constexpr int kStepsPerChord = 2 * kStepsPerBar;   // ein Akkord dauert zwei Takte
constexpr int kChordsPerCycle = 4;
constexpr int kMaxActive = 64;

// Ab welchem VERLAUF eine Ebene mitspielt
constexpr float kLayerStart[kNumLayers] = { 0.0f, 0.0f, 0.25f, 0.5f, 0.75f };

// Tonleitern (Halbtonschritte vom Grundton)
constexpr int kScales[kNumModes][7] = {
    { 0, 2, 3, 5, 7, 8, 10 },   // Moll (aeolisch)
    { 0, 2, 4, 5, 7, 9, 11 },   // Dur
    { 0, 2, 3, 5, 7, 9, 10 },   // Dorisch
    { 0, 1, 3, 5, 7, 8, 10 },   // Phrygisch
    { 0, 2, 4, 6, 7, 9, 11 } }; // Lydisch

// Einfache Akkordfolge je Modus (Stufen 0..6), je zwei Takte
constexpr int kProgressions[kNumModes][kChordsPerCycle] = {
    { 0, 5, 3, 4 },   // Moll: i  VI  iv  v
    { 0, 5, 3, 4 },   // Dur:  I  vi  IV  V
    { 0, 3, 0, 6 },   // Dorisch: i  IV  i  VII
    { 0, 1, 0, 6 },   // Phrygisch: i  II  i  vii
    { 0, 1, 0, 4 } }; // Lydisch: I  II  I  V

struct Settings
{
    int key = 9;          // 0 = C ... 9 = A ... 11 = H
    int mode = 0;         // Index in kScales
    float verlauf = 0.3f; // 0..1
    int variation = 1;    // 1..16
    int layerMode[kNumLayers] = { 1, 1, 1, 1, 1 };            // je Ebene: 0 aus, 1 Auto (VERLAUF entscheidet), 2 immer an
    bool follow[kNumLayers] = { true, true, true, true, true }; // false: bleibt auf dem Grundakkord statt den Akkorden zu folgen
};

struct Transport
{
    bool playing = false;
    double ppq = 0.0;        // Position am Blockanfang in Viertelnoten
    double bpm = 120.0;
    double sampleRate = 48000.0;
};

// velocity 0 = Note aus
struct Event { int offset; uint8_t channel; uint8_t note; uint8_t velocity; };

struct EventList
{
    static constexpr int kCapacity = 1024;
    std::array<Event, kCapacity> events {};
    int size = 0;
    bool overflow = false;
    void clear() { size = 0; overflow = false; }
    void add (int offset, int channel, int note, int velocity)
    {
        if (size >= kCapacity) { overflow = true; return; }
        events[(size_t) size++] = { offset, (uint8_t) channel, (uint8_t) note, (uint8_t) velocity };
    }
};

// Halbtonabstand des n-ten Akkordtons (0 Grundton, 1 Terz, 2 Quinte, 3 Septime, 4 None) ueber dem Tonartgrundton
inline int chordTone (int mode, int degree, int index)
{
    const int i = degree + 2 * index;
    return kScales[mode][i % 7] + 12 * (i / 7);
}

// Name des Akkords (deutsche Schreibweise): Dur gross ("F-Dur"), Moll klein ("a-Moll")
inline void chordName (int key, int mode, int degree, char* out, int maxLen)
{
    static const char* names[12] = { "C", "Cis", "D", "Es", "E", "F", "Fis", "G", "As", "A", "B", "H" };
    static const char* lower[12] = { "c", "cis", "d", "es", "e", "f", "fis", "g", "as", "a", "b", "h" };
    const int root = (key + kScales[mode][degree % 7]) % 12;
    const int third = chordTone (mode, degree, 1) - chordTone (mode, degree, 0);
    const int fifth = chordTone (mode, degree, 2) - chordTone (mode, degree, 0);
    const char* quality = third == 4 ? "-Dur" : (fifth == 6 ? "-vermindert" : "-Moll");
    const char* n = third == 4 ? names[root] : lower[root];
    int p = 0;
    for (const char* s = n; *s && p < maxLen - 1; ++s) out[p++] = *s;
    for (const char* s = quality; *s && p < maxLen - 1; ++s) out[p++] = *s;
    out[p] = 0;
}

inline uint32_t hash3 (uint32_t a, uint32_t b, uint32_t c)
{
    uint32_t h = a * 0x9E3779B1u ^ (b + 0x7F4A7C15u) * 0x85EBCA6Bu ^ (c + 0x165667B1u) * 0xC2B2AE35u;
    h ^= h >> 16; h *= 0x7FEB352Du; h ^= h >> 15; h *= 0x846CA68Bu; h ^= h >> 16;
    return h;
}

class Generator
{
public:
    void reset() { numActive = 0; running = false; lastPpqEnd = 0.0; currentChord = -1; }

    // Akkord-Index in der Folge (0..3), -1 wenn gestoppt
    int chordIndex() const { return currentChord; }

    // Alle klingenden Noten beenden (z. B. bei Stopp, Sprung oder Bypass)
    static bool layerActive (const Settings& s, int layer)
    {
        const int m = s.layerMode[layer];
        return m == 2 || (m == 1 && s.verlauf >= kLayerStart[layer]);
    }

    void allNotesOff (EventList& out, int offset)
    {
        for (int i = 0; i < numActive; ++i)
            out.add (offset, active[(size_t) i].channel, active[(size_t) i].note, 0);
        numActive = 0;
    }

    void process (const Transport& t, const Settings& sIn, int numSamples, EventList& out)
    {
        Settings s = sIn;
        s.key = std::clamp (s.key, 0, kNumKeys - 1);
        s.mode = std::clamp (s.mode, 0, kNumModes - 1);
        s.verlauf = std::clamp (s.verlauf, 0.0f, 1.0f);
        s.variation = std::clamp (s.variation, 1, 16);
        for (auto& m : s.layerMode) m = std::clamp (m, 0, 2);
        cur = &s;

        if (! t.playing || t.bpm <= 0.0 || t.sampleRate <= 0.0 || numSamples <= 0)
        {
            if (running) allNotesOff (out, 0);
            running = false; currentChord = -1;
            cur = nullptr;
            return;
        }
        releaseSilencedLayers (s, out);
        const double samplesPerQuarter = t.sampleRate * 60.0 / t.bpm;
        const double ppqEnd = t.ppq + (double) numSamples / samplesPerQuarter;

        // Start oder Sprung (Loop, Klick in die Zeitleiste): alles aus, laufende Flaechen nachholen
        const bool jumped = running && std::fabs (t.ppq - lastPpqEnd) > 0.05;
        if (! running || jumped)
        {
            allNotesOff (out, 0);
            running = true;
            chase (t.ppq, s, out);
        }

        const long long firstStep = (long long) std::ceil (t.ppq / kStep - 1e-9);
        for (long long k = firstStep; (double) k * kStep < ppqEnd - 1e-12; ++k)
        {
            const int offset = std::clamp ((int) std::llround (((double) k * kStep - t.ppq) * samplesPerQuarter), 0, numSamples - 1);
            releaseDue (k, offset, out);
            if (k >= 0) stepOn (k, offset, s, out);
        }
        lastPpqEnd = ppqEnd;
        cur = nullptr;
    }

private:
    struct Active { uint8_t channel, note; long long endStep; };

    static long long floorDiv (long long a, long long b) { return a >= 0 ? a / b : -((-a + b - 1) / b); }

    void releaseDue (long long step, int offset, EventList& out)
    {
        for (int i = 0; i < numActive;)
        {
            if (active[(size_t) i].endStep <= step)
            {
                out.add (offset, active[(size_t) i].channel, active[(size_t) i].note, 0);
                active[(size_t) i] = active[(size_t) --numActive];
            }
            else ++i;
        }
    }

    // Ebenen, die ausgeschaltet wurden, beenden ihre klingenden Noten sofort
    void releaseSilencedLayers (const Settings& s, EventList& out)
    {
        for (int i = 0; i < numActive;)
        {
            if (! layerActive (s, active[(size_t) i].channel - 1))
            {
                out.add (0, active[(size_t) i].channel, active[(size_t) i].note, 0);
                active[(size_t) i] = active[(size_t) --numActive];
            }
            else ++i;
        }
    }

    void noteOn (int layer, int note, int velocity, long long endStep, int offset, EventList& out)
    {
        if (cur != nullptr && ! layerActive (*cur, layer)) return;
        const int channel = layer + 1;
        note = std::clamp (note, 0, 127);
        velocity = std::clamp (velocity, 1, 127);
        for (int i = 0; i < numActive; ++i)   // gleiche Note auf gleichem Kanal: erst beenden
            if (active[(size_t) i].channel == channel && active[(size_t) i].note == note)
            {
                out.add (offset, channel, note, 0);
                active[(size_t) i] = active[(size_t) --numActive];
                break;
            }
        if (numActive >= kMaxActive) return;
        out.add (offset, channel, note, velocity);
        active[(size_t) numActive++] = { (uint8_t) channel, (uint8_t) note, endStep };
    }

    static int degreeFor (const Settings& s, long long chord, int layer)
    {
        if (! s.follow[layer]) return kProgressions[s.mode][0];   // bleibt auf dem Grundakkord
        return kProgressions[s.mode][(int) (((chord % kChordsPerCycle) + kChordsPerCycle) % kChordsPerCycle)];
    }

    static int register_ (int note, int low)   // in die Oktave ab 'low' legen
    {
        while (note < low) note += 12;
        while (note >= low + 12) note -= 12;
        return note;
    }

    // Gehaltene Ebenen eines Akkords (Flaeche, Farbe, ruhiger Bass). Ebenen, die nicht den Akkorden folgen,
    // werden nur am Anfang der Folge angeschlagen und halten ueber alle vier Akkorde (beim Nachholen sofort).
    void sustained (long long chord, long long endStep, int offset, const Settings& s, EventList& out, int mode)   // mode 0 normal, 1 Nachholen, 2 nur nicht folgende Ebenen
    {
        const float v = s.verlauf;
        // liefert false, wenn die Ebene jetzt nichts anschlagen soll; setzt Akkordstufe und Ende
        auto plan = [&] (int layer, int& deg, long long& end)
        {
            deg = degreeFor (s, chord, layer);
            end = endStep;
            if (s.follow[layer]) return mode != 2;
            const long long inCycle = ((chord % kChordsPerCycle) + kChordsPerCycle) % kChordsPerCycle;
            end = (chord - inCycle + kChordsPerCycle) * kStepsPerChord;
            return mode != 0 || inCycle == 0;
        };
        int deg; long long end;
        if (plan (kFlaeche, deg, end))
        {
            const int padRoot = register_ (s.key, 52);
            const int tones = v > 0.6f ? 4 : 3;
            for (int i = 0; i < tones; ++i)
                noteOn (kFlaeche, padRoot + chordTone (s.mode, deg, i), (int) (40 + 50 * v), end, offset, out);
        }
        if (plan (kFarbe, deg, end))
            noteOn (kFarbe, register_ (s.key + chordTone (s.mode, deg, 4), 76), (int) (35 + 40 * v), end, offset, out);
        if (v < 0.3f && plan (kBass, deg, end))
            noteOn (kBass, register_ (s.key + chordTone (s.mode, deg, 0), 36), (int) (60 + 40 * v), end, offset, out);
    }

    void chase (double ppq, const Settings& s, EventList& out)
    {
        if (ppq < 0.0) return;
        const long long step = (long long) std::floor (ppq / kStep + 1e-9);
        const long long chord = floorDiv (step, kStepsPerChord);
        const double chordStartPpq = (double) (chord * kStepsPerChord) * kStep;
        currentChord = (int) (chord % kChordsPerCycle);
        // mitten im Akkord gestartet: Liegetöne sofort nachholen; genau am Akkordanfang nur die Ebenen,
        // die nicht den Akkorden folgen (die anderen schlägt der normale Schritt an)
        sustained (chord, (chord + 1) * kStepsPerChord, 0, s, out, ppq > chordStartPpq + 1e-9 ? 1 : 2);
    }

    void stepOn (long long k, int offset, const Settings& s, EventList& out)
    {
        const long long chord = floorDiv (k, kStepsPerChord);
        const int pos = (int) (k - chord * kStepsPerChord);
        const float v = s.verlauf;
        const long long chordEnd = (chord + 1) * kStepsPerChord;
        const uint32_t var = (uint32_t) s.variation;
        auto jitter = [&] (int layer, int range) { return (int) (hash3 (var, (uint32_t) k, (uint32_t) layer) % (uint32_t) (2 * range + 1)) - range; };

        if (pos == 0)
        {
            currentChord = (int) (chord % kChordsPerCycle);
            sustained (chord, chordEnd, offset, s, out, 0);
            {
                const int root = register_ (s.key + chordTone (s.mode, degreeFor (s, chord, kAkzente), 0), 36);
                noteOn (kAkzente, root, (int) (90 + 30 * v), k + 2, offset, out);
                noteOn (kAkzente, root + 7, (int) (85 + 30 * v), k + 2, offset, out);
            }
        }

        // Bass: ruhig gehalten (< 30 %), Viertel-Puls (< 60 %), Oktav-Achtel (ab 60 %)
        const int bassRoot = register_ (s.key + chordTone (s.mode, degreeFor (s, chord, kBass), 0), 36);
        if (v >= 0.6f && pos % 2 == 0)
            noteOn (kBass, bassRoot + ((pos / 2) % 2) * 12, 62 + (int) (35 * v) + ((pos % 4) == 0 ? 8 : 0) + jitter (kBass, 3), k + 1, offset, out);
        else if (v >= 0.3f && v < 0.6f && pos % 4 == 0)
            noteOn (kBass, bassRoot, 60 + (int) (35 * v) + jitter (kBass, 3), k + 3, offset, out);

        // Arp: Achtel, ab 60 % Sechzehntel; steigt ueber zwei Oktaven durch die Akkordtoene
        {
            const int degArp = degreeFor (s, chord, kArp);
            const int rate = v >= 0.6f ? 1 : 2;
            if (pos % rate == 0)
            {
                const int start = (int) (hash3 (var, (uint32_t) (s.follow[kArp] ? chord : 0), 77u) % 4u);
                const int i = (pos / rate + start) % 8;
                const int note = register_ (s.key, 57) + chordTone (s.mode, degArp, i % 4) + 12 * (i / 4);
                noteOn (kArp, note, 55 + (int) (35 * v) + jitter (kArp, 6), k + 1, offset, out);
            }
        }
    }

    std::array<Active, kMaxActive> active {};
    int numActive = 0;
    bool running = false;
    double lastPpqEnd = 0.0;
    int currentChord = -1;
    const Settings* cur = nullptr;   // nur waehrend process() gueltig
};

// Einfacher Vorhoer-Klang: weiche Sinus-Stimmen, damit man ohne eigene Instrumente etwas hoert
class Preview
{
public:
    void prepare (double sr) { sampleRate = sr; reset(); }
    void reset() { for (auto& v : voices) v = {}; }

    void handle (const Event& e)
    {
        if (e.velocity == 0)
        {
            for (auto& v : voices)
                if (v.on && ! v.releasing && v.channel == e.channel && v.note == e.note) v.releasing = true;
            return;
        }
        Voice* slot = &voices[0];
        for (auto& v : voices) if (! v.on) { slot = &v; break; }
        static constexpr float layerGain[kNumLayers] = { 0.045f, 0.07f, 0.04f, 0.03f, 0.06f };
        const float freq = 440.0f * std::pow (2.0f, ((float) e.note - 69.0f) / 12.0f);
        *slot = {};
        slot->on = true; slot->channel = e.channel; slot->note = e.note;
        slot->inc = (float) (2.0 * 3.14159265358979 * freq / sampleRate);
        slot->gain = layerGain[std::clamp ((int) e.channel - 1, 0, kNumLayers - 1)] * (float) e.velocity / 127.0f;
    }

    void render (float* l, float* r, int n)
    {
        const float att = 1.0f / (0.02f * (float) sampleRate), rel = 1.0f / (0.25f * (float) sampleRate);
        for (auto& v : voices)
        {
            if (! v.on) continue;
            for (int i = 0; i < n; ++i)
            {
                if (v.releasing) { v.env -= rel; if (v.env <= 0.0f) { v.on = false; break; } }
                else if (v.env < 1.0f) v.env = std::min (1.0f, v.env + att);
                const float x = (std::sin (v.phase) + 0.25f * std::sin (2.0f * v.phase)) * v.env * v.gain;
                v.phase += v.inc; if (v.phase > 6.2831853f) v.phase -= 6.2831853f;
                l[i] += x; r[i] += x;
            }
        }
    }

private:
    struct Voice { bool on = false, releasing = false; uint8_t channel = 0, note = 0; float phase = 0, inc = 0, env = 0, gain = 0; };
    std::array<Voice, 48> voices {};
    double sampleRate = 48000.0;
};
} // namespace stromscore
