#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>

namespace stromscore::voiceleading
{
// Sounding pitches before the layer octave offset. No heap, RNG or host calls.
struct ChordVoicing { int n = 0; int notes[6] {}; };
inline int motion (int a, int b)
{
    const int d = std::abs (a - b);
    return 4 * d + 3 * std::max (0, d - 7) * std::max (0, d - 7);
}
inline int distance (const ChordVoicing& a, const ChordVoicing& b)
{
    int dp[7][7] {};
    for (int i = 1; i <= a.n; ++i) dp[i][0] = i * 28;
    for (int j = 1; j <= b.n; ++j) dp[0][j] = j * 28;
    for (int i = 1; i <= a.n; ++i)
        for (int j = 1; j <= b.n; ++j)
            dp[i][j] = std::min ({ dp[i - 1][j - 1] + motion (a.notes[i - 1], b.notes[j - 1]),
                                  dp[i - 1][j] + 28, dp[i][j - 1] + 28 });
    return dp[a.n][b.n];
}
inline bool contains (const ChordVoicing& v, int note)
{
    for (int i = 0; i < v.n; ++i) if (v.notes[i] == note) return true;
    return false;
}
inline void sort (ChordVoicing& v) { std::sort (v.notes, v.notes + v.n); }
inline int nearest (const ChordVoicing& v, int note)
{
    int d = 127;
    for (int i = 0; i < v.n; ++i) d = std::min (d, std::abs (note - v.notes[i]));
    return v.n ? d : 0;
}
inline int shapeCost (const ChordVoicing& v, const ChordVoicing& anchor)
{
    int cost = 0;
    for (int i = 1; i < v.n; ++i)
    {
        const int gap = v.notes[i] - v.notes[i - 1];
        if (v.notes[i - 1] < 60 && gap < 3) cost += (v.notes[i - 1] < 55 ? 64 : 24) * (3 - gap);
        cost += std::max (0, gap - 16) * 3;
    }
    if (v.n == anchor.n)
    {
        int centre = 0, target = 0;
        for (int i = 0; i < v.n; ++i) { cost += std::abs (v.notes[i] - anchor.notes[i]); centre += v.notes[i]; target += anchor.notes[i]; }
        cost += 4 * std::abs (centre - target) / std::max (1, v.n);
        cost += 2 * std::abs ((v.notes[v.n-1] - v.notes[0]) - (anchor.notes[anchor.n-1] - anchor.notes[0]));
    }
    return cost;
}
// Bounded beam search, at most 6 * 24 * 4 expansions and 24 final alignments.
// Complete pitch-class membership is a hard constraint. Register, spacing and outer voices
// are soft costs: this allows inversions without turning every chord into a close-position stack.
inline ChordVoicing lead (ChordVoicing anchor, ChordVoicing previous, int lo, int hi,
                          int resolvingSeventh = -1, int resolvingThird = -1)
{
    sort (anchor); sort (previous);
    if (anchor.n == 0 || previous.n == 0) return anchor;
    struct Node { ChordVoicing v; int score = 0; };
    std::array<Node, 24> beam {}, next {};
    int count = 1;
    for (int role = 0; role < anchor.n; ++role)
    {
        int options[4] {}, scores[4] {}; int numOptions = 0;
        const int pc = (anchor.notes[role] % 12 + 12) % 12;
        for (int note = lo; note <= hi; ++note)
        {
            if ((note % 12 + 12) % 12 != pc) continue;
            const int score = std::abs (note - anchor.notes[role]) + 2 * nearest (previous, note)
                            - (contains (previous, note) ? 36 : 0);
            int at = numOptions;
            if (at < 4) ++numOptions;
            else if (score < scores[3]) at = 3;
            else continue;
            while (at > 0 && score < scores[at - 1])
            { options[at] = options[at - 1]; scores[at] = scores[at - 1]; --at; }
            options[at] = note; scores[at] = score;
        }
        if (numOptions == 0) return anchor; // range folding was already performed by the caller
        int nextCount = 0;
        for (int b = 0; b < count; ++b)
            for (int q = 0; q < numOptions; ++q)
            {
                Node node = beam[(size_t) b];
                if (contains (node.v, options[q])) continue;
                node.v.notes[node.v.n++] = options[q];
                node.score += scores[q];
                int at = nextCount;
                if (at < (int) next.size()) ++nextCount;
                else if (node.score < next.back().score) at = (int) next.size() - 1;
                else continue;
                while (at > 0 && node.score < next[(size_t) at - 1].score)
                { next[(size_t) at] = next[(size_t) at - 1]; --at; }
                next[(size_t) at] = node;
            }
        if (nextCount == 0) return anchor;
        beam = next; count = nextCount;
    }
    ChordVoicing best = anchor;
    auto cost = [&] (ChordVoicing v)
    {
        sort (v);
        int score = distance (previous, v) + shapeCost (v, anchor);
        score += 2 * std::abs (v.notes[v.n - 1] - previous.notes[previous.n - 1]);
        for (int i = 0; i < v.n; ++i) if (contains (previous, v.notes[i])) score -= 48;
        // Contextual dominant resolution, never a global ban on held sevenths/colour notes.
        for (int i = 0; i < previous.n; ++i)
        {
            const int note = previous.notes[i], pc = (note % 12 + 12) % 12;
            if (pc == resolvingSeventh && ! contains (v, note - 1) && ! contains (v, note - 2)) score += 12;
            if (pc == resolvingThird && ! contains (v, note + 1)) score += 12;
        }
        return score;
    };
    int bestCost = cost (best);
    for (int b = 0; b < count; ++b)
    {
        auto v = beam[(size_t) b].v; sort (v);
        const int score = cost (v);
        if (score < bestCost) { bestCost = score; best = v; }
    }
    return best;
}
// Bass keeps the harmonic bass pitch class; no substitution by a nearby third or seventh.
inline int bass (int anchor, int previous, int lo, int hi)
{
    int best = anchor, bestCost = 100000;
    for (int note = lo; note <= hi; ++note)
    {
        if ((note % 12 + 12) % 12 != (anchor % 12 + 12) % 12) continue;
        const int cost = (previous >= 0 ? motion (previous, note) : 0) + 2 * std::abs (note - anchor);
        if (cost < bestCost) { bestCost = cost; best = note; }
    }
    return best;
}
}
