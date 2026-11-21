// Regressionstests fuer den Notengenerator (ohne JUCE)
#include "TestSupport.h"
#include "ScoreEngine.h"
#include <vector>
#include <map>
#include <set>
#include <string>

using namespace stromscore;

struct Abs { long long sample; int channel, note, velocity; };

// Spielt 'seconds' Sekunden ab Position 0 mit fester Blockgroesse und sammelt alle Ereignisse mit absoluter Sampleposition
static std::vector<Abs> run (const Settings& s, int block, double seconds, double bpm = 120.0, double sr = 48000.0)
{
    Generator g; g.reset();
    EventList list;
    std::vector<Abs> all;
    const long long total = (long long) (seconds * sr);
    for (long long pos = 0; pos < total; pos += block)
    {
        const int n = (int) std::min<long long> (block, total - pos);
        Transport t; t.playing = true; t.bpm = bpm; t.sampleRate = sr; t.ppq = (double) pos / (sr * 60.0 / bpm);
        list.clear();
        g.process (t, s, n, list);
        CHECK (! list.overflow);
        for (int i = 0; i < list.size; ++i)
        {
            const auto& e = list.events[(size_t) i];
            CHECK (e.offset >= 0 && e.offset < n);
            all.push_back ({ pos + e.offset, e.channel, e.note, e.velocity });
        }
    }
    Transport stop; stop.playing = false;
    list.clear();
    g.process (stop, s, block, list);
    for (int i = 0; i < list.size; ++i)
        all.push_back ({ total, list.events[(size_t) i].channel, list.events[(size_t) i].note, 0 });
    return all;
}

static std::set<int> channelsUsed (const std::vector<Abs>& ev)
{
    std::set<int> c;
    for (const auto& e : ev) if (e.velocity > 0) c.insert (e.channel);
    return c;
}

int main()
{
    // 1) Ohne Wiedergabe entstehen keine Noten
    {
        Generator g; g.reset(); EventList l; Settings s;
        Transport t; t.playing = false;
        g.process (t, s, 512, l);
        CHECK (l.size == 0);
        CHECK (g.chordIndex() == -1);
    }

    // 2) Alle Noten gehoeren zur Tonleiter, in jeder Tonart und jedem Modus; alle Noten werden wieder beendet
    for (int key = 0; key < kNumKeys; ++key)
        for (int mode = 0; mode < kNumModes; ++mode)
        {
            Settings s; s.key = key; s.mode = mode; s.verlauf = 1.0f;
            const auto ev = run (s, 512, 20.0);
            std::map<std::pair<int, int>, int> open;
            int ons = 0;
            for (const auto& e : ev)
            {
                CHECK (e.channel >= 1 && e.channel <= kNumLayers);
                CHECK (e.note >= 0 && e.note <= 127);
                if (e.velocity > 0)
                {
                    ++ons;
                    const int pc = ((e.note - key) % 12 + 12) % 12;
                    bool inScale = false;
                    for (int d = 0; d < 7; ++d) inScale |= kScales[mode][d] == pc;
                    CHECK (inScale);
                    CHECK (open[std::make_pair (e.channel, e.note)] == 0);   // keine doppelt angeschlagene Note
                    open[std::make_pair (e.channel, e.note)] = 1;
                }
                else open[std::make_pair (e.channel, e.note)] = 0;
            }
            CHECK (ons > 100);
            for (const auto& o : open) CHECK (o.second == 0);   // nichts haengt
        }

    // 3) Unabhaengig von der Puffergroesse (bis auf Rundung um ein Sample)
    {
        Settings s; s.verlauf = 0.8f; s.variation = 5;
        const auto a = run (s, 64, 12.0), b = run (s, 512, 12.0), c = run (s, 1000, 12.0);
        auto same = [] (const std::vector<Abs>& x, const std::vector<Abs>& y)
        {
            if (x.size() != y.size()) return false;
            for (size_t i = 0; i < x.size(); ++i)
                if (x[i].channel != y[i].channel || x[i].note != y[i].note || x[i].velocity != y[i].velocity
                    || std::llabs (x[i].sample - y[i].sample) > 1) return false;
            return true;
        };
        CHECK (same (a, b));
        CHECK (same (a, c));
    }

    // 4) VERLAUF bestimmt die Ebenen: 0 % nur Flaeche und Bass, 100 % alle fuenf
    {
        Settings s; s.verlauf = 0.0f;
        CHECK (channelsUsed (run (s, 512, 10.0)) == (std::set<int> { 1, 2 }));
        s.verlauf = 0.3f;
        CHECK (channelsUsed (run (s, 512, 10.0)) == (std::set<int> { 1, 2, 3 }));
        s.verlauf = 0.55f;
        CHECK (channelsUsed (run (s, 512, 10.0)) == (std::set<int> { 1, 2, 3, 4 }));
        s.verlauf = 1.0f;
        CHECK (channelsUsed (run (s, 512, 10.0)) == (std::set<int> { 1, 2, 3, 4, 5 }));
    }

    // 5) Mehr VERLAUF = mehr Noten
    {
        Settings s; s.verlauf = 0.1f;
        const auto lo = run (s, 512, 16.0);
        s.verlauf = 0.9f;
        const auto hi = run (s, 512, 16.0);
        CHECK (hi.size() > 3 * lo.size());
    }

    // 6) Gleiche VARIATION = gleiche Noten, andere VARIATION = andere Fassung
    {
        Settings s; s.verlauf = 0.8f; s.variation = 3;
        const auto a = run (s, 512, 8.0), b = run (s, 512, 8.0);
        CHECK (a.size() == b.size());
        for (size_t i = 0; i < a.size(); ++i) CHECK (a[i].note == b[i].note && a[i].velocity == b[i].velocity && a[i].sample == b[i].sample);
        s.variation = 4;
        const auto c = run (s, 512, 8.0);
        bool differs = c.size() != a.size();
        for (size_t i = 0; ! differs && i < a.size(); ++i) differs = a[i].note != c[i].note || a[i].velocity != c[i].velocity;
        CHECK (differs);
    }

    // 7) Sprung zurueck (Loop): alles wird beendet, die Flaeche wird mitten im Akkord sofort nachgeholt
    {
        Generator g; g.reset(); EventList l; Settings s; s.verlauf = 0.5f;
        Transport t; t.playing = true; t.bpm = 120; t.sampleRate = 48000;
        const double spq = 48000.0 * 60.0 / 120.0;
        double ppq = 0.0;
        for (int i = 0; i < 200; ++i) { t.ppq = ppq; l.clear(); g.process (t, s, 512, l); ppq += 512.0 / spq; }
        t.ppq = 3.0;   // zurueck in Takt 1, mitten im ersten Akkord
        l.clear();
        { NoAllocations guard; g.process (t, s, 512, l); }
        int offs = 0, padOns = 0;
        for (int i = 0; i < l.size; ++i)
        {
            const auto& e = l.events[(size_t) i];
            if (e.velocity == 0) ++offs;
            if (e.velocity > 0 && e.channel == 1 && e.offset == 0) ++padOns;
        }
        CHECK (offs > 0);
        CHECK (padOns >= 3);
        CHECK (g.chordIndex() == 0);
    }

    // 8) Start mitten im Akkord: Flaeche sofort da; Stopp beendet alles
    {
        Generator g; g.reset(); EventList l; Settings s;
        Transport t; t.playing = true; t.bpm = 90; t.sampleRate = 44100; t.ppq = 9.5;   // Takt 3, zweiter Akkord
        g.process (t, s, 256, l);
        int padOns = 0;
        for (int i = 0; i < l.size; ++i) if (l.events[(size_t) i].channel == 1 && l.events[(size_t) i].velocity > 0) ++padOns;
        CHECK (padOns >= 3);
        CHECK (g.chordIndex() == 1);
        l.clear(); t.playing = false;
        g.process (t, s, 256, l);
        CHECK (l.size == padOns + 1);   // Flaeche + der Arp-Ton auf der Startposition
        for (int i = 0; i < l.size; ++i) CHECK (l.events[(size_t) i].velocity == 0);
    }

    // 9) Kein Speicher im Audio-Pfad, auch bei hohem Tempo und kleinen Bloecken
    {
        Generator g; g.reset(); EventList l; Settings s; s.verlauf = 1.0f;
        Preview p; p.prepare (48000);
        std::vector<float> L (64), R (64);
        Transport t; t.playing = true; t.bpm = 240; t.sampleRate = 48000;
        NoAllocations guard;
        for (int i = 0; i < 4000; ++i)
        {
            t.ppq = i * 64.0 / (48000.0 * 60.0 / 240.0);
            l.clear(); g.process (t, s, 64, l);
            std::fill (L.begin(), L.end(), 0.0f); std::fill (R.begin(), R.end(), 0.0f);
            for (int e = 0; e < l.size; ++e) p.handle (l.events[(size_t) e]);
            p.render (L.data(), R.data(), 64);
            for (float x : L) CHECK (std::isfinite (x) && std::fabs (x) < 2.0f);
        }
    }

    // 10) Negative Position (Vorzaehler) erzeugt keine Noten
    {
        Generator g; g.reset(); EventList l; Settings s;
        Transport t; t.playing = true; t.bpm = 120; t.sampleRate = 48000; t.ppq = -2.0;
        g.process (t, s, 512, l);
        CHECK (l.size == 0);
    }

    // 11) Akkordnamen
    {
        char buf[32];
        chordName (9, 0, 0, buf, 32); CHECK (std::string (buf) == "a-Moll");
        chordName (9, 0, 5, buf, 32); CHECK (std::string (buf) == "F-Dur");
        chordName (0, 1, 6, buf, 32); CHECK (std::string (buf) == "h-vermindert");
    }
    return 0;
}
