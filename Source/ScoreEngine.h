#pragma once
// Stromscore: regelbasierter Noten-Generator (kein JUCE, echtzeitfest, ohne Speicheranforderung im Audiopfad).
// Die Ausgabe ist eine reine Funktion der Projektposition und der Einstellungen: gleiche Einstellungen, gleiche Noten.
//
// Stimmungsfeld: Faerbung (x, dunkel -> hell), Intensitaet (y, ruhig -> aufgewuehlt), Unruhe (z, sauber -> kratzig).
// Aus dem Feld wird je Phrase (8 Takte) eine Wendung aus dem Vokabular gezogen (siehe kWendungen, Grundlage:
// Stilmittel-Katalog). Die Muster der Ebenen folgen der Wendung, solange sie auf Auto stehen.
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>

namespace stromscore
{
constexpr int kNumLayers = 5;
enum Layer { kFlaeche = 0, kBass = 1, kArp = 2, kFarbe = 3, kAkzente = 4 };
constexpr int kNumKeys = 12;
constexpr double kStep = 0.25;          // Raster: Sechzehntel (in Viertelnoten)
constexpr int kPhraseBars = 8;          // eine Phrase = 8 Takte
constexpr int kMaxChords = 8;

// Ab welcher Intensitaet eine Ebene im Modus Auto einsetzt (Farbe zusaetzlich ab Unruhe 0,4)
constexpr float kLayerStart[kNumLayers] = { 0.0f, 0.0f, 0.25f, 0.4f, 0.7f };

// ------------------------------------------------------------------ Akkorde
enum ChordType { Maj, Min, Maj7, Min7, Dom7, MinMaj7, MinMaj9, Dim7, HalfDim, Sus4, Quartal, Add9, Min9, kNumChordTypes };
struct ChordShape { int n; int iv[5]; const char* suffix; bool minor; };
constexpr ChordShape kShapes[kNumChordTypes] = {
    { 3, { 0, 4, 7 }, "", false },
    { 3, { 0, 3, 7 }, "m", true },
    { 4, { 0, 4, 7, 11 }, "maj7", false },
    { 4, { 0, 3, 7, 10 }, "m7", true },
    { 4, { 0, 4, 7, 10 }, "7", false },
    { 4, { 0, 3, 7, 11 }, "m(maj7)", true },
    { 5, { 0, 3, 7, 11, 14 }, "m(maj9)", true },
    { 4, { 0, 3, 6, 9 }, "dim7", true },
    { 4, { 0, 3, 6, 10 }, "m7b5", true },
    { 3, { 0, 5, 7 }, "sus4", false },
    { 4, { 0, 5, 10, 15 }, " Quarten", false },
    { 4, { 0, 4, 7, 14 }, "add9", false },
    { 5, { 0, 3, 7, 10, 14 }, "m9", true } };

// ------------------------------------------------------------------ Muster
enum PadPattern { PadAuto = 0, PadHeld, PadStabs, PadPulse, kNumPadPatterns };
enum BassPattern { BassAuto = 0, BassHeld, BassHalf, BassQuarter, BassEighth, BassPulse, BassOctaves, BassFunk, BassPendulum, kNumBassPatterns };
enum ArpFigure { ArpAuto = 0, ArpUp, ArpDown, ArpCircle, ArpCell, ArpRiff, ArpGlitter, kNumArpFigures };
enum ArpRate { RateAuto = 0, RateQuarter, RateEighth, RateSixteenth, kNumArpRates };

// ------------------------------------------------------------------ Vokabular (Wendungen)
struct Chord { int root; int type; int bars; };
struct Wendung
{
    const char* name;
    float x, y, z;              // Platz im Stimmungsfeld
    int n; Chord ch[kMaxChords];
    int arp[2], bass[2], pad;   // bevorzugte Muster (Auto waehlt per VARIATION eines der beiden)
};

// Grundlage: Stilmittel-Katalog (Williams, Goldsmith, Herrmann, Barry, Silvestri, Carpenter, Europa-Hoerspielmusik).
// Wurzeln in Halbtoenen ueber dem Grundton der Tonart, Laengen in Takten (Summe je Wendung = 8).
constexpr Wendung kWendungen[] = {
    { "Halbton-Nachbarn",   0.12f, 0.30f, 0.75f, 4, { { 0, Min, 2 }, { 11, Min, 2 }, { 0, Min, 2 }, { 0, MinMaj7, 2 } }, { ArpCircle, ArpCell }, { BassPendulum, BassHeld }, PadHeld },
    { "Grundton-Teppich",   0.10f, 0.45f, 0.50f, 2, { { 0, Min, 4 }, { 1, Maj, 4 } }, { ArpCircle, ArpDown }, { BassPulse, BassEighth }, PadHeld },
    { "Lauern",             0.08f, 0.10f, 0.60f, 1, { { 0, Min, 8 } }, { ArpCircle, ArpCell }, { BassHeld, BassPendulum }, PadHeld },
    { "Trauer",             0.28f, 0.15f, 0.08f, 4, { { 0, Min, 2 }, { 8, Maj, 2 }, { 5, Min, 2 }, { 7, Maj, 2 } }, { ArpDown, ArpCircle }, { BassHeld, BassHalf }, PadHeld },
    { "Agentenfarbe",       0.30f, 0.45f, 0.45f, 3, { { 0, MinMaj9, 4 }, { 5, MinMaj7, 2 }, { 0, MinMaj9, 2 } }, { ArpCell, ArpCircle }, { BassQuarter, BassPendulum }, PadHeld },
    { "Septakkord-Paare",   0.22f, 0.55f, 0.55f, 4, { { 0, MinMaj7, 2 }, { 5, MinMaj7, 2 }, { 0, MinMaj7, 2 }, { 5, MinMaj7, 2 } }, { ArpCell, ArpUp }, { BassEighth, BassPendulum }, PadHeld },
    { "Schiefer Walzer",    0.20f, 0.55f, 0.35f, 4, { { 0, Min, 2 }, { 0, MinMaj7, 2 }, { 5, Min7, 2 }, { 7, Dom7, 2 } }, { ArpCircle, ArpDown }, { BassQuarter, BassHalf }, PadHeld },
    { "Grusel-Orchester",   0.15f, 0.50f, 0.50f, 4, { { 0, Min, 2 }, { 2, HalfDim, 2 }, { 0, Min, 2 }, { 1, Maj, 2 } }, { ArpDown, ArpCircle }, { BassQuarter, BassPendulum }, PadHeld },
    { "Terz-Treppe",        0.20f, 0.80f, 0.60f, 4, { { 0, Min, 2 }, { 3, Min, 2 }, { 6, Min, 2 }, { 9, Min, 2 } }, { ArpCell, ArpUp }, { BassPulse, BassOctaves }, PadPulse },
    { "Tritonus-Schock",    0.08f, 0.88f, 0.88f, 4, { { 0, Min, 2 }, { 6, Maj, 2 }, { 0, Min, 2 }, { 11, Dim7, 2 } }, { ArpCell, ArpCircle }, { BassPulse, BassPendulum }, PadStabs },
    { "Moll-Marsch",        0.32f, 0.75f, 0.20f, 4, { { 0, Min, 2 }, { 5, Min, 2 }, { 8, Maj, 2 }, { 7, Maj, 2 } }, { ArpUp, ArpDown }, { BassOctaves, BassEighth }, PadPulse },
    { "Epische Spannung",   0.45f, 0.60f, 0.15f, 4, { { 0, Min, 2 }, { 8, Maj, 2 }, { 3, Maj, 2 }, { 10, Maj, 2 } }, { ArpUp, ArpCircle }, { BassEighth, BassOctaves }, PadHeld },
    { "Funk-Spannung",      0.50f, 0.65f, 0.25f, 4, { { 0, Min9, 2 }, { 5, Dom7, 2 }, { 0, Min9, 2 }, { 10, Dom7, 2 } }, { ArpRiff, ArpRiff }, { BassFunk, BassFunk }, PadStabs },
    { "Quarten-Weite",      0.60f, 0.45f, 0.45f, 4, { { 0, Quartal, 2 }, { 10, Quartal, 2 }, { 0, Quartal, 2 }, { 6, Maj, 2 } }, { ArpGlitter, ArpCircle }, { BassHeld, BassHalf }, PadHeld },
    { "Bewegter Abschied",  0.60f, 0.35f, 0.15f, 4, { { 0, Maj, 2 }, { 7, Maj, 2 }, { 9, Min, 2 }, { 5, Maj, 2 } }, { ArpUp, ArpDown }, { BassQuarter, BassHalf }, PadHeld },
    { "Weite",              0.65f, 0.15f, 0.05f, 4, { { 0, Add9, 2 }, { 9, Min7, 2 }, { 5, Maj7, 2 }, { 7, Sus4, 2 } }, { ArpUp, ArpCircle }, { BassHeld, BassHalf }, PadHeld },
    { "Abenteuer",          0.70f, 0.55f, 0.10f, 4, { { 0, Maj7, 2 }, { 2, Min7, 2 }, { 4, Min7, 2 }, { 7, Dom7, 2 } }, { ArpRiff, ArpUp }, { BassFunk, BassEighth }, PadStabs },
    { "Terzverwandtschaft", 0.72f, 0.68f, 0.30f, 4, { { 0, Maj, 2 }, { 4, Maj, 2 }, { 8, Maj, 2 }, { 0, Maj, 2 } }, { ArpUp, ArpCircle }, { BassQuarter, BassEighth }, PadHeld },
    { "Heldisch",           0.80f, 0.75f, 0.10f, 4, { { 0, Maj, 2 }, { 10, Maj, 2 }, { 5, Maj, 2 }, { 0, Maj, 2 } }, { ArpUp, ArpRiff }, { BassOctaves, BassEighth }, PadPulse },
    { "W\xc3\xa4rme",       0.80f, 0.18f, 0.00f, 4, { { 5, Maj7, 2 }, { 0, Maj7, 2 }, { 5, Maj7, 2 }, { 0, Maj7, 2 } }, { ArpCircle, ArpUp }, { BassHeld, BassHalf }, PadHeld },
    { "Lydisches Staunen",  0.85f, 0.35f, 0.10f, 4, { { 0, Maj, 2 }, { 2, Maj, 2 }, { 0, Maj7, 2 }, { 2, Maj, 2 } }, { ArpGlitter, ArpUp }, { BassHeld, BassHalf }, PadHeld },
    { "Triumph",            0.88f, 0.92f, 0.05f, 4, { { 0, Maj, 2 }, { 8, Maj, 2 }, { 10, Maj, 2 }, { 0, Maj, 2 } }, { ArpUp, ArpUp }, { BassOctaves, BassEighth }, PadPulse } };
constexpr int kNumWendungen = (int) (sizeof (kWendungen) / sizeof (kWendungen[0]));

// ------------------------------------------------------------------ Ein- und Ausgabe
struct Settings
{
    int key = 9;                // 0 = C ... 9 = A ... 11 = H
    float x = 0.3f;             // Faerbung: 0 dunkel ... 1 hell
    float y = 0.3f;             // Intensitaet: 0 ruhig ... 1 aufgewuehlt
    float z = 0.0f;             // Unruhe: 0 sauber ... 1 kratzig
    int meterNum = 4, meterDen = 4;
    float swing = 0.0f;         // 0 ... 1 (1 = Triolen-Feeling)
    int variation = 1;          // 1 ... 16
    int layerMode[kNumLayers] = { 1, 1, 1, 1, 1 };            // 0 aus, 1 Auto, 2 an
    bool follow[3] = { true, true, true };                    // Flaeche, Bass, Arp: false = bleibt auf dem Grundakkord
    int padPattern = PadAuto, bassPattern = BassAuto, arpFigure = ArpAuto, arpRate = RateAuto;
};

struct Transport
{
    bool playing = false;
    double ppq = 0.0;           // Position am Blockanfang in Viertelnoten
    double bpm = 120.0;
    double sampleRate = 48000.0;
};

// velocity 0 = Note aus
struct Event { int offset; uint8_t channel; uint8_t note; uint8_t velocity; };

struct EventList
{
    static constexpr int kCapacity = 2048;
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

inline uint32_t hash3 (uint32_t a, uint32_t b, uint32_t c)
{
    uint32_t h = a * 0x9E3779B1u ^ (b + 0x7F4A7C15u) * 0x85EBCA6Bu ^ (c + 0x165667B1u) * 0xC2B2AE35u;
    h ^= h >> 16; h *= 0x7FEB352Du; h ^= h >> 15; h *= 0x846CA68Bu; h ^= h >> 16;
    return h;
}

// Akkordname (deutsche Notennamen mit H): "Am", "Fmaj7", "C#m(maj7)"
inline void chordName (int key, int root, int type, char* out, int maxLen)
{
    static const char* major[12] = { "C", "Des", "D", "Es", "E", "F", "Fis", "G", "As", "A", "B", "H" };
    static const char* minor[12] = { "C", "Cis", "D", "Es", "E", "F", "Fis", "G", "Gis", "A", "B", "H" };
    const int pc = ((key + root) % 12 + 12) % 12;
    const bool isMinor = kShapes[std::clamp (type, 0, kNumChordTypes - 1)].minor;
    int p = 0;
    for (const char* s = (isMinor ? minor : major)[pc]; *s && p < maxLen - 1; ++s) out[p++] = *s;
    for (const char* s = kShapes[std::clamp (type, 0, kNumChordTypes - 1)].suffix; *s && p < maxLen - 1; ++s) out[p++] = *s;
    out[p] = 0;
}

// Taktlaenge in Sechzehnteln und Betonungsgruppen (z. B. 5/4: 3+3+2+2 Achtel, 7/8: 2+2+3 Achtel)
struct Meter
{
    int len = 16;
    int numGroups = 4;
    int groupStart[16] {};

    static Meter from (int num, int den)
    {
        Meter m;
        num = std::clamp (num, 1, 16);
        den = (den == 2 || den == 4 || den == 8 || den == 16) ? den : 4;
        m.len = std::clamp (num * 16 / den, 4, 32);
        int sizes[16] {}; int n = 0;
        if (den == 8 && num % 3 == 0)            { for (int i = 0; i < num / 3; ++i) sizes[n++] = 6; }
        else if (den == 8 && num >= 5)           { int rest = m.len; while (rest > 6) { sizes[n++] = 4; rest -= 4; } sizes[n++] = rest; }
        else if (num == 5 && den == 4)           { sizes[n++] = 6; sizes[n++] = 6; sizes[n++] = 4; sizes[n++] = 4; }
        else { int rest = m.len; while (rest > 0 && n < 16) { const int g = std::min (4, rest); sizes[n++] = g; rest -= g; } }
        int pos = 0;
        m.numGroups = 0;
        for (int i = 0; i < n && pos < m.len; ++i) { m.groupStart[m.numGroups++] = pos; pos += sizes[i]; }
        return m;
    }
    bool isGroupStart (int pos) const
    {
        for (int i = 0; i < numGroups; ++i) if (groupStart[i] == pos) return true;
        return false;
    }
};

// ------------------------------------------------------------------ Generator
class Generator
{
public:
    void reset() { chaseStep = -1; numActive = 0; running = false; lastPpqEnd = 0.0; phraseIndex = -1; current = -1; curRoot = 0; curType = Min; curChord = -1; }

    // Fuer die Anzeige
    int wendung() const { return current; }
    int chordInWendung() const { return curChord; }
    int chordRoot() const { return curRoot; }
    int chordType() const { return curType; }

    static bool layerActive (const Settings& s, int layer)
    {
        const int m = s.layerMode[layer];
        if (m == 2) return true;
        if (m == 0) return false;
        if (layer == kFarbe) return s.y >= kLayerStart[kFarbe] || s.z >= 0.4f;
        return s.y >= kLayerStart[layer];
    }

    // Gewicht einer Wendung fuer die aktuelle Lage im Feld
    static float weight (const Wendung& w, const Settings& s)
    {
        const float dx = w.x - s.x, dy = (w.y - s.y) * 0.7f, dz = (w.z - s.z) * 0.8f;
        return std::exp (-(dx * dx + dy * dy + dz * dz) / 0.05f);
    }

    // Deterministische Wahl einer Wendung fuer eine Phrase
    static int pick (const Settings& s, long long phrase)
    {
        float w[kNumWendungen]; float total = 0.0f, best = 0.0f; int bestIdx = 0;
        for (int i = 0; i < kNumWendungen; ++i)
        {
            w[i] = weight (kWendungen[i], s);
            if (w[i] > best) { best = w[i]; bestIdx = i; }
        }
        for (int i = 0; i < kNumWendungen; ++i) { if (w[i] < 0.25f * best) w[i] = 0.0f; total += w[i]; }
        if (total <= 0.0f) return bestIdx;
        const float r = (float) (hash3 ((uint32_t) s.variation, (uint32_t) phrase, 911u) % 100000u) / 100000.0f * total;
        float acc = 0.0f;
        for (int i = 0; i < kNumWendungen; ++i) { acc += w[i]; if (r < acc) return i; }
        return bestIdx;
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
        s.x = std::clamp (s.x, 0.0f, 1.0f); s.y = std::clamp (s.y, 0.0f, 1.0f); s.z = std::clamp (s.z, 0.0f, 1.0f);
        s.swing = std::clamp (s.swing, 0.0f, 1.0f);
        s.variation = std::clamp (s.variation, 1, 16);
        for (auto& m : s.layerMode) m = std::clamp (m, 0, 2);
        s.padPattern = std::clamp (s.padPattern, 0, kNumPadPatterns - 1);
        s.bassPattern = std::clamp (s.bassPattern, 0, kNumBassPatterns - 1);
        s.arpFigure = std::clamp (s.arpFigure, 0, kNumArpFigures - 1);
        s.arpRate = std::clamp (s.arpRate, 0, kNumArpRates - 1);
        cur = &s;
        meter = Meter::from (s.meterNum, s.meterDen);

        if (! t.playing || t.bpm <= 0.0 || t.sampleRate <= 0.0 || numSamples <= 0)
        {
            if (running) allNotesOff (out, 0);
            running = false; curChord = -1; cur = nullptr;
            return;
        }
        releaseSilencedLayers (s, out);

        const double samplesPerQuarter = t.sampleRate * 60.0 / t.bpm;
        const double ppqEnd = t.ppq + (double) numSamples / samplesPerQuarter;
        const bool jumped = running && std::fabs (t.ppq - lastPpqEnd) > 0.05;
        if (! running || jumped)
        {
            allNotesOff (out, 0);
            running = true;
            phraseIndex = -1;
            chase (t.ppq, s, out);
        }

        const long long firstStep = (long long) std::floor (t.ppq / kStep) - 1;
        for (long long k = std::max (0LL, firstStep); ; ++k)
        {
            const double when = ((double) k + swingDelay (k, s)) * kStep;
            if (when >= ppqEnd - 1e-12) break;
            if (when < t.ppq - 1e-12) continue;
            const int offset = std::clamp ((int) std::llround ((when - t.ppq) * samplesPerQuarter), 0, numSamples - 1);
            releaseDue (k, offset, out);
            stepOn (k, offset, s, out);
        }
        lastPpqEnd = ppqEnd;
        cur = nullptr;
    }

private:
    struct Active { uint8_t channel, note; long long endStep; };

    // Wo im Takt / in der Phrase ein Schritt liegt
    struct Pos
    {
        long long k, bar, phrase; int pos, barInPhrase;
        int chordIdx; long long chordStart, chordEnd, phraseStart, phraseEnd;
    };

    static long long floorDiv (long long a, long long b) { return a >= 0 ? a / b : -((-a + b - 1) / b); }

    double swingDelay (long long k, const Settings& s) const
    {
        if (s.swing <= 0.0f) return 0.0;
        const int p = (int) (((k % 4) + 4) % 4);
        if (p == 2) return 0.667 * s.swing;
        if (p == 1 || p == 3) return 0.333 * s.swing;
        return 0.0;
    }

    Pos locate (long long k) const
    {
        Pos p;
        p.k = k;
        p.bar = floorDiv (k, meter.len);
        p.pos = (int) (k - p.bar * meter.len);
        p.phrase = floorDiv (p.bar, kPhraseBars);
        p.barInPhrase = (int) (p.bar - p.phrase * kPhraseBars);
        p.phraseStart = p.phrase * kPhraseBars * meter.len;
        p.phraseEnd = p.phraseStart + (long long) kPhraseBars * meter.len;
        const Wendung& w = kWendungen[std::max (0, current)];
        int startBar = 0; p.chordIdx = 0;
        for (int i = 0; i < w.n; ++i)
        {
            if (p.barInPhrase < startBar + w.ch[i].bars) { p.chordIdx = i; break; }
            startBar += w.ch[i].bars;
            p.chordIdx = i;
        }
        startBar = 0;
        for (int i = 0; i < p.chordIdx; ++i) startBar += w.ch[i].bars;
        p.chordStart = p.phraseStart + (long long) startBar * meter.len;
        p.chordEnd = std::min (p.phraseEnd, p.chordStart + (long long) w.ch[p.chordIdx].bars * meter.len);
        return p;
    }

    void ensurePhrase (long long phrase, const Settings& s)
    {
        if (phrase != phraseIndex) { current = pick (s, phrase); phraseIndex = phrase; }
    }

    // An einem Akkordwechsel mitten in der Phrase: nur wechseln, wenn die Wendung nicht mehr zur Lage passt
    void maybeSwitch (long long phrase, const Settings& s)
    {
        float best = 0.0f;
        for (const auto& w : kWendungen) best = std::max (best, weight (w, s));
        if (current >= 0 && weight (kWendungen[current], s) < 0.35f * best)
            current = pick (s, phrase);
    }

    Chord chordFor (const Pos& p, int layer, const Settings& s) const
    {
        const Wendung& w = kWendungen[current];
        if (layer <= kArp && ! s.follow[layer])
        {
            Chord tonic = w.ch[0]; tonic.root = 0;
            tonic.type = kShapes[w.ch[0].type].minor ? Min : Maj;
            return tonic;
        }
        return w.ch[p.chordIdx];
    }

    int nextRoot (const Pos& p) const
    {
        const Wendung& w = kWendungen[current];
        return p.chordIdx + 1 < w.n ? w.ch[p.chordIdx + 1].root : w.ch[0].root;
    }

    // Unruhe faerbt die Flaeche: Reibung durch grosse Septime, bei viel Unruhe zusaetzlich die kleine None
    static int padType (int type, float z)
    {
        if (z >= 0.75f && kShapes[type].minor && type != Dim7 && type != HalfDim) return MinMaj9;
        if (z >= 0.45f)
        {
            if (type == Min || type == Min7) return MinMaj7;
            if (type == Maj) return Maj7;
        }
        return type;
    }

    static int place (int note, int low)
    {
        while (note < low) note += 12;
        while (note >= low + 12) note -= 12;
        return note;
    }

    int hashInt (uint32_t salt, long long a) const { return (int) (hash3 ((uint32_t) cur->variation, (uint32_t) a, salt) & 0x7fffffff); }

    int chooseArp (const Settings& s, long long phrase) const
    {
        if (s.arpFigure != ArpAuto) return s.arpFigure;
        return kWendungen[current].arp[hashInt (31u, phrase) % 2];
    }
    int chooseBass (const Settings& s, long long phrase) const
    {
        if (s.bassPattern != BassAuto) return s.bassPattern;
        const int pref = kWendungen[current].bass[hashInt (47u, phrase) % 2];
        // ganz ruhig: Bass haelt; sehr aufgewuehlt: mindestens Achtel
        if (s.y < 0.15f) return BassHeld;
        if (s.y > 0.85f && (pref == BassHeld || pref == BassHalf || pref == BassQuarter)) return BassEighth;
        return pref;
    }
    int choosePad (const Settings& s) const
    {
        if (s.padPattern != PadAuto) return s.padPattern;
        const int pref = kWendungen[current].pad;
        return s.y < 0.3f ? PadHeld : pref;
    }

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
        for (int i = 0; i < numActive; ++i)
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

    int jitter (long long k, int layer, int range) const
    {
        return (int) (hash3 ((uint32_t) cur->variation, (uint32_t) k, (uint32_t) layer) % (uint32_t) (2 * range + 1)) - range;
    }

    // --- Flaeche
    void padChord (const Pos& p, const Settings& s, int offset, long long endStep, int velocity, EventList& out)
    {
        const Chord c = chordFor (p, kFlaeche, s);
        const ChordShape& sh = kShapes[padType (c.type, s.z)];
        const int low = 50 + (int) std::lround (s.x * 8.0f);               // dunkel tiefer, hell hoeher
        const int root = place (s.key + c.root, low);
        int voices = sh.n;
        if (s.y < 0.2f) voices = std::min (voices, 3);
        for (int i = 0; i < voices; ++i)
            noteOn (kFlaeche, root + sh.iv[i], velocity, endStep, offset, out);
        if (s.y > 0.6f) noteOn (kFlaeche, root + 12, velocity - 8, endStep, offset, out);   // Verdopplung oben
    }

    // --- Farbe: Grundfarbe (None) und bei Unruhe ein fremder Ton
    void colour (const Pos& p, const Settings& s, int offset, EventList& out)
    {
        const Chord c = chordFor (p, kFarbe, s);
        if (s.y >= kLayerStart[kFarbe] || s.layerMode[kFarbe] == 2)
        {
            const int ninth = place (s.key + c.root + 14, 74 + (int) std::lround (s.x * 4.0f));
            noteOn (kFarbe, ninth, (int) (35 + 40 * s.y), p.chordEnd, offset, out);
        }
    }

    void foreignTone (const Pos& p, const Settings& s, int offset, EventList& out)
    {
        const Chord c = chordFor (p, kFarbe, s);
        const int interval = s.x < 0.5f ? 1 : 6;                          // dunkel: kleine None, hell: uebermaessige Quarte
        const int note = place (s.key + c.root + interval, 79);
        noteOn (kFarbe, note, (int) (30 + 45 * s.z), p.chordEnd, offset, out);
        if (s.z >= 0.8f && s.y < 0.5f)                                      // Halbton-Pendel ganz oben
            noteOn (kFarbe, note + 11, (int) (25 + 30 * s.z), p.chordEnd, offset, out);
    }

    // Liegetoene einer Akkordposition (Flaeche gehalten, Bass gehalten, Farbe); mode 0 normal, 1 Nachholen
    void sustained (const Pos& p, const Settings& s, int offset, EventList& out, bool chasing)
    {
        const int pad = choosePad (s);
        const bool padFollow = s.follow[kFlaeche];
        const bool phraseStart = p.k == p.phraseStart;
        if (pad == PadHeld && (padFollow || phraseStart || chasing))
            padChord (p, s, offset, padFollow ? p.chordEnd : p.phraseEnd, (int) (40 + 45 * s.y), out);

        if (chooseBass (s, p.phrase) == BassHeld && (s.follow[kBass] || phraseStart || chasing))
        {
            const Chord c = chordFor (p, kBass, s);
            noteOn (kBass, place (s.key + c.root, 33 + (int) std::lround (s.x * 4.0f)), (int) (60 + 35 * s.y),
                    s.follow[kBass] ? p.chordEnd : p.phraseEnd, offset, out);
        }
        colour (p, s, offset, out);
    }

    void chase (double ppq, const Settings& s, EventList& out)
    {
        if (ppq < 0.0) return;
        const long long k = (long long) std::floor (ppq / kStep + 1e-9);
        const long long phrase = floorDiv (floorDiv (k, meter.len), kPhraseBars);
        ensurePhrase (phrase, s);
        const Pos p = locate (k);
        curChord = p.chordIdx;
        const Chord c = kWendungen[current].ch[p.chordIdx];
        curRoot = c.root; curType = c.type;
        if (ppq > (double) p.chordStart * kStep + 1e-9)
            sustained (p, s, 0, out, true);
        else
            chaseStep = k;   // genau am Akkordanfang: der normale Schritt schlaegt an, auch die stehenden Ebenen
    }

    void stepOn (long long k, int offset, const Settings& s, EventList& out)
    {
        const long long phrase = floorDiv (floorDiv (k, meter.len), kPhraseBars);
        ensurePhrase (phrase, s);
        Pos p = locate (k);
        const bool chordStart = k == p.chordStart;
        if (chordStart && k != p.phraseStart)
        {
            const int before = current;
            maybeSwitch (phrase, s);
            if (current != before) p = locate (k);
        }
        const Wendung& w = kWendungen[current];
        curChord = p.chordIdx; curRoot = w.ch[p.chordIdx].root; curType = w.ch[p.chordIdx].type;
        const bool beat = p.pos % 4 == 0;
        const bool group = meter.isGroupStart (p.pos);
        const float y = s.y, z = s.z;

        if (chordStart)
        {
            sustained (p, s, offset, out, k == chaseStep);
            chaseStep = -1;
            if (layerActive (s, kAkzente))
            {
                const Chord c = chordFor (p, kAkzente, s);
                const int root = place (s.key + c.root, 36);
                noteOn (kAkzente, root, (int) (90 + 30 * y), k + 2, offset, out);
                noteOn (kAkzente, root + 7, (int) (82 + 30 * y), k + 2, offset, out);
                if (z >= 0.8f) { noteOn (kAkzente, root + 1, (int) (70 + 30 * z), k + 2, offset, out); noteOn (kAkzente, root + 6, (int) (70 + 30 * z), k + 2, offset, out); }
            }
        }

        // Unruhe: fremder Ton in der Mitte des Akkords (das \"quietschende\" Element)
        if (z >= 0.35f && layerActive (s, kFarbe) && k == p.chordStart + (p.chordEnd - p.chordStart) / 2)
            foreignTone (p, s, offset, out);

        // --- Flaeche: Schlaege oder Puls
        const int pad = choosePad (s);
        if (pad == PadStabs && p.pos % 4 == 2)
            padChord (p, s, offset, k + 1, (int) (55 + 40 * y) + jitter (k, kFlaeche, 4), out);
        else if (pad == PadPulse && beat)
            padChord (p, s, offset, k + 3, (int) (50 + 40 * y) + (group ? 8 : 0), out);

        // --- Bass
        {
            const Chord c = chordFor (p, kBass, s);
            const int low = 33 + (int) std::lround (s.x * 4.0f);
            int root = place (s.key + c.root, low);
            const int vel = (int) (58 + 38 * y) + (group ? 8 : 0) + jitter (k, kBass, 3);
            const int pattern = chooseBass (s, phrase);
            // Chromatische Annaeherung an den naechsten Grundton im letzten Achtel des Akkords
            const bool approach = s.follow[kBass] && (z >= 0.3f || pattern == BassFunk) && k == p.chordEnd - 2 && pattern != BassHeld;
            if (approach)
            {
                const int target = place (s.key + nextRoot (p), low);
                root = target - 1 >= low ? target - 1 : target + 1;
            }
            switch (pattern)
            {
                case BassHalf:     if (p.pos % 8 == 0 || approach) noteOn (kBass, root, vel, k + (approach ? 2 : 7), offset, out); break;
                case BassQuarter:  if (beat || approach) noteOn (kBass, root, vel, k + (approach ? 2 : 3), offset, out); break;
                case BassEighth:   if (p.pos % 2 == 0) noteOn (kBass, root, vel, k + 2, offset, out); break;
                case BassPulse:    noteOn (kBass, root, vel - (group ? 0 : 10), k + 1, offset, out); break;
                case BassOctaves:  if (p.pos % 2 == 0) noteOn (kBass, root + (approach ? 0 : ((p.pos / 2) % 2) * 12), vel, k + 1, offset, out); break;
                case BassFunk:
                {
                    const int q = p.pos % 8;
                    if (approach) noteOn (kBass, root, vel, k + 1, offset, out);
                    else if (q == 0) noteOn (kBass, root, vel + 6, k + 2, offset, out);
                    else if (q == 3) noteOn (kBass, root, vel - 6, k + 1, offset, out);
                    else if (q == 5) noteOn (kBass, root + 7, vel - 8, k + 1, offset, out);
                    else if (q == 6) noteOn (kBass, root + 12, vel - 4, k + 1, offset, out);
                    break;
                }
                case BassPendulum:
                {
                    const int rate = y > 0.6f ? 2 : 4;
                    if (p.pos % rate == 0)
                    {
                        const int other = z >= 0.5f ? 1 : 3;                 // Halbton (Unruhe) oder kleine Terz
                        const int n = (p.pos / rate) % 2 == 0 ? root : root + other;
                        noteOn (kBass, n, vel, k + rate - 1, offset, out);
                    }
                    break;
                }
                default: break;
            }
        }

        // --- Arp / Figur
        if (layerActive (s, kArp))
        {
            const int fig = chooseArp (s, phrase);
            int rate = s.arpRate == RateQuarter ? 4 : s.arpRate == RateEighth ? 2 : s.arpRate == RateSixteenth ? 1
                     : (y < 0.15f ? 4 : y < 0.5f ? 2 : 1);
            if (fig == ArpGlitter) rate = 1;
            const long long rel = k - (s.follow[kArp] ? p.chordStart : p.phraseStart);
            if (rel % rate == 0)
            {
                const Chord c = chordFor (p, kArp, s);
                const ChordShape& sh = kShapes[c.type];
                const int base = place (s.key + c.root, 55 + (int) std::lround (s.x * 7.0f)) + (fig == ArpGlitter ? 12 : 0);
                int tones[10]; const int n = std::min (sh.n, 5), count = 2 * n;
                for (int i = 0; i < count; ++i) tones[i] = base + sh.iv[i % n] + 12 * (i / n);
                const long long c0 = rel / rate + (long long) (hashInt (77u, s.follow[kArp] ? p.chordStart : phrase) % 4);
                int note = base;
                switch (fig)
                {
                    case ArpDown:    note = tones[count - 1 - (int) (c0 % count)]; break;
                    case ArpCircle:  { const int period = 2 * count - 2; const int q = (int) (c0 % period); note = tones[q < count ? q : period - q]; break; }
                    case ArpCell:
                    {
                        static constexpr int cell[4] = { 0, 1, 0, 2 };
                        const int q = cell[c0 % 4];
                        note = (q == 1 && z >= 0.5f) ? base + 1 : tones[q];   // bei Unruhe: Halbton-Nachbar statt Terz
                        break;
                    }
                    case ArpRiff:
                    {
                        static constexpr int dark[8] = { 0, 3, 5, 7, 10, 7, 5, 3 };
                        static constexpr int bright[8] = { 0, 2, 4, 7, 9, 7, 4, 2 };
                        note = base + (sh.minor ? dark : bright)[c0 % 8];
                        break;
                    }
                    default:         note = tones[c0 % count]; break;       // Aufwaerts, Glitzern
                }
                // Unruhe: jede achte Note ein chromatischer Durchgang
                if (z >= 0.6f && c0 % 8 == 7) note -= 1;
                const int vel = (int) ((fig == ArpGlitter ? 40 : 52) + 35 * y) + (group ? 6 : 0) + jitter (k, kArp, 6);
                const long long len = (fig == ArpGlitter || rate == 1) ? 1 : rate;
                noteOn (kArp, note, vel, k + len, offset, out);
            }
        }

        // --- Akzente auf den Betonungsgruppen (sehr aufgewuehlt), bei Unruhe vorgezogen
        if (layerActive (s, kAkzente) && y >= 0.85f && ! chordStart)
        {
            const int probe = z >= 0.5f ? (p.pos + 1) % meter.len : p.pos;
            if (meter.isGroupStart (probe) && probe != 0)
            {
                const Chord c = chordFor (p, kAkzente, s);
                noteOn (kAkzente, place (s.key + c.root, 36), (int) (70 + 30 * y), k + 1, offset, out);
            }
        }
    }

    static constexpr int kMaxActive = 96;
    std::array<Active, kMaxActive> active {};
    int numActive = 0;
    bool running = false;
    double lastPpqEnd = 0.0;
    long long phraseIndex = -1;
    int current = -1, curChord = -1, curRoot = 0, curType = Min;
    long long chaseStep = -1;
    Meter meter;
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
        static constexpr float layerGain[kNumLayers] = { 0.04f, 0.07f, 0.04f, 0.03f, 0.06f };
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
    std::array<Voice, 64> voices {};
    double sampleRate = 48000.0;
};
} // namespace stromscore
