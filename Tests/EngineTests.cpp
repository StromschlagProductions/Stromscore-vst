// Regressionstests fuer den Notengenerator (ohne JUCE)
#include "TestSupport.h"
#include "ScoreEngine.h"
#include <vector>
#include <map>
#include <set>
#include <string>
#include <tuple>

using namespace stromscore;

// channel: Ebene 1 ... 5 (aus dem Ausgang), midi: tatsaechlicher MIDI-Kanal, range: Index des Tonumfangs, out: Ausgang
struct Abs { long long sample; int channel, note, velocity, midi = 0, range = 0, out = 0; };
static Abs mk (long long t, const Event& e, int vel) { return { t, kOutputLayer[e.out] + 1, e.note, vel, e.channel, kOutputRange[e.out], e.out }; }

// Spielt 'seconds' Sekunden ab 'startPpq' mit fester Blockgroesse und sammelt alle Ereignisse
static std::vector<Abs> run (const Settings& s, int block, double seconds, double bpm = 120.0, double sr = 48000.0, double startPpq = 0.0)
{
    Generator g; g.reset();
    EventList list;
    std::vector<Abs> all;
    const long long total = (long long) (seconds * sr);
    for (long long pos = 0; pos < total; pos += block)
    {
        const int n = (int) std::min<long long> (block, total - pos);
        Transport t; t.playing = true; t.bpm = bpm; t.sampleRate = sr; t.ppq = startPpq + (double) pos / (sr * 60.0 / bpm);
        list.clear();
        g.process (t, s, n, list);
        CHECK (! list.overflow);
        for (int i = 0; i < list.size; ++i)
        {
            const auto& e = list.events[(size_t) i];
            CHECK (e.offset >= 0 && e.offset < n);
            if (e.type != 0) continue;   // Controller zaehlen hier nicht als Noten
            all.push_back (mk (pos + e.offset, e, e.velocity));
        }
    }
    Transport stop; stop.playing = false;
    list.clear();
    g.process (stop, s, block, list);
    for (int i = 0; i < list.size; ++i)
        all.push_back (mk (total, list.events[(size_t) i], 0));
    return all;
}

static std::set<int> channelsUsed (const std::vector<Abs>& ev)
{
    std::set<int> c;
    for (const auto& e : ev) if (e.velocity > 0) c.insert (e.channel);
    return c;
}

// Jede Note endet genau einmal, nie doppelt an, nie Ende ohne Anfang
static void checkBalanced (const std::vector<Abs>& ev)
{
    std::map<std::pair<int, int>, int> open;
    for (const auto& e : ev)
    {
        CHECK (e.midi >= 1 && e.midi <= 16);
        CHECK (e.note >= 0 && e.note <= 127);
        auto& o = open[std::make_pair (e.midi, e.note)];
        if (e.velocity > 0) { CHECK (o == 0); ++o; }
        else { CHECK (o == 1); --o; }
    }
    for (const auto& o : open) CHECK (o.second == 0);
}

static int countOns (const std::vector<Abs>& ev, int channel = 0)
{
    int n = 0;
    for (const auto& e : ev) if (e.velocity > 0 && (channel == 0 || e.channel == channel)) ++n;
    return n;
}

int main()
{
    // 1) Gestoppt: keine Noten
    {
        Generator g; g.reset(); EventList l; Settings s;
        Transport t; t.playing = false;
        g.process (t, s, 512, l);
        CHECK (l.size == 0);
    }

    // 2) Ueber das ganze Feld, alle Taktarten und Muster: nichts haengt, nichts doppelt, kein Ueberlauf
    for (float x : { 0.0f, 0.3f, 0.6f, 1.0f })
        for (float y : { 0.0f, 0.5f, 1.0f })
            for (float z : { 0.0f, 0.5f, 1.0f })
            {
                Settings s; s.x = x; s.y = y; s.z = z; s.key = (int) (x * 11);
                s.swing = y * 0.5f;
                for (auto& v : s.layerIntensity) v = 1.0f;
                checkBalanced (run (s, 333, 20.0));
            }
    for (int num : { 3, 4, 5, 6, 7 })
        for (int den : { 4, 8 })
        {
            Settings s; s.y = 0.9f; s.meterNum = num; s.meterDen = den;
            for (auto& v : s.layerIntensity) v = 1.0f;
            checkBalanced (run (s, 256, 16.0));
        }
    for (int bp = 0; bp < kNumBassPatterns; ++bp)
        for (int af = 0; af < kNumArpFigures; ++af)
        {
            Settings s; s.y = 0.6f; s.z = 0.7f; s.bassPattern = bp; s.arpFigure = af; s.padPattern = (bp + af) % kNumPadPatterns;
            s.arpRate = af % kNumArpRates;
            for (auto& v : s.layerIntensity) v = 1.0f;
            checkBalanced (run (s, 512, 12.0));
        }

    // 3) Unabhaengig von der Blockgroesse (gleiche Einstellungen, gleiche Noten zur gleichen Zeit)
    {
        Settings s; s.y = 0.8f; s.z = 0.6f; s.swing = 0.4f; s.variation = 5;
        for (auto& v : s.layerIntensity) v = 1.0f;
        auto a = run (s, 64, 30.0), b = run (s, 1000, 30.0), c = run (s, 4096, 30.0);
        CHECK (a.size() == b.size() && b.size() == c.size());
        for (size_t i = 0; i < a.size(); ++i)
        {
            CHECK (a[i].channel == b[i].channel && a[i].note == b[i].note && a[i].velocity == b[i].velocity);
            CHECK (std::llabs (a[i].sample - b[i].sample) <= 1 && std::llabs (a[i].sample - c[i].sample) <= 1);
        }
    }

    // 4) Ebenen im Modus Auto setzen mit der Intensitaet ein
    {
        Settings s; s.z = 0.0f;
        s.y = 0.0f; CHECK ((channelsUsed (run (s, 512, 20.0)) == std::set<int> { 1, 2 }));
        s.y = 0.2f; CHECK ((channelsUsed (run (s, 512, 20.0)) == std::set<int> { 1, 2, 5 }));   // Gegenstimme ab 15 %
        s.y = 0.3f; CHECK ((channelsUsed (run (s, 512, 20.0)) == std::set<int> { 1, 2, 3, 4, 5 }));   // Akzent (Tupfer) ab 25 %
        s.y = 0.5f; CHECK ((channelsUsed (run (s, 512, 20.0)) == std::set<int> { 1, 2, 3, 4, 5 }));
        s.y = 0.9f; CHECK ((channelsUsed (run (s, 512, 20.0)) == std::set<int> { 1, 2, 3, 4, 5 }));
        s.y = 0.1f; s.z = 0.6f;
        CHECK (channelsUsed (run (s, 512, 20.0)).count (4) == 1);   // Unruhe holt den Akzent auch bei wenig Intensitaet
    }

    // 5) Mehr Intensitaet = mehr Noten
    {
        Settings a; a.y = 0.1f; Settings b; b.y = 0.9f;
        CHECK (countOns (run (b, 512, 20.0)) > 2 * countOns (run (a, 512, 20.0)));
    }

    // 6) Faerbung waehlt passende Wendungen: dunkel ueberwiegend Moll, hell ueberwiegend Dur
    {
        int darkMinor = 0, brightMajor = 0;
        for (int v = 1; v <= 16; ++v)
            for (long long phrase = 0; phrase < 8; ++phrase)
            {
                Settings d; d.x = 0.1f; d.y = 0.4f; d.variation = v;
                Settings h; h.x = 0.9f; h.y = 0.4f; h.variation = v;
                if (kShapes[kWendungen[Generator::pick (d, phrase)].ch[0].type].minor) ++darkMinor;
                if (! kShapes[kWendungen[Generator::pick (h, phrase)].ch[0].type].minor) ++brightMajor;
            }
        CHECK (darkMinor >= 120 && brightMajor >= 120);
    }

    // 7) VARIATION ist reproduzierbar und veraendert spuerbar
    {
        Settings s; s.y = 0.7f; s.z = 0.3f; s.x = 0.5f; s.variation = 3;
        auto a = run (s, 512, 30.0), b = run (s, 512, 30.0);
        CHECK (a.size() == b.size());
        for (size_t i = 0; i < a.size(); ++i) CHECK (a[i].note == b[i].note && a[i].sample == b[i].sample);
        int differ = 0;
        for (int v = 1; v <= 16; ++v)
        {
            Settings o = s; o.variation = v;
            auto c = run (o, 512, 30.0);
            if (c.size() != a.size()) { ++differ; continue; }
            for (size_t i = 0; i < a.size(); ++i) if (c[i].note != a[i].note) { ++differ; break; }
        }
        CHECK (differ >= 8);
    }

    // 8) Sprung (Loop), Start mitten in der Phrase, Stopp: nichts haengt, keine Speicheranforderung
    {
        Generator g; g.reset(); EventList l; Settings s; s.y = 0.5f; s.padPattern = PadHeld;
        std::map<std::pair<int, int>, int> open;
        auto feed = [&] (double ppq, bool playing, int n)
        {
            Transport t; t.playing = playing; t.bpm = 120; t.sampleRate = 48000; t.ppq = ppq;
            l.clear();
            { NoAllocations guard; g.process (t, s, n, l); }
            for (int i = 0; i < l.size; ++i)
            {
                const auto& e = l.events[(size_t) i];
                open[std::make_pair ((int) e.channel, (int) e.note)] += e.velocity > 0 ? 1 : -1;
            }
        };
        feed (13.3, true, 512);           // mitten in einem Akkord: Flaeche wird nachgeholt
        int pads = 0;
        for (const auto& o : open) if (o.first.first == 1 && o.second > 0) ++pads;
        CHECK (pads >= 3);
        for (int i = 1; i < 40; ++i) feed (13.3 + i * 512.0 / 24000.0, true, 512);
        feed (0.0, true, 512);            // Loop-Sprung
        feed (8.0, true, 512);            // Sprung genau auf einen Akkordanfang
        feed (9.0, false, 512);           // Stopp
        for (const auto& o : open) CHECK (o.second == 0);
    }

    // 9) Ebenen-Schalter: aus = still, an = auch bei wenig Intensitaet; Ausschalten waehrend des Spielens beendet Noten
    {
        Settings s; s.y = 0.0f; s.layerIntensity[kArp] = 0.5f; s.mute[kFlaeche] = true;
        const auto used = channelsUsed (run (s, 512, 20.0));
        CHECK (used.count (3) == 1 && used.count (1) == 0 && used.count (2) == 1);

        Generator g; g.reset(); EventList l; Settings a; a.y = 0.5f;
        std::map<std::pair<int, int>, int> open;
        for (int i = 0; i < 40; ++i)
        {
            if (i == 20) a.mute[kFlaeche] = true;
            Transport t; t.playing = true; t.bpm = 120; t.sampleRate = 48000; t.ppq = i * 512.0 / 24000.0;
            l.clear(); g.process (t, a, 512, l);
            for (int e = 0; e < l.size; ++e)
                open[std::make_pair ((int) l.events[(size_t) e].channel, (int) l.events[(size_t) e].note)] += l.events[(size_t) e].velocity > 0 ? 1 : -1;
        }
        for (const auto& o : open) if (o.first.first == 1) CHECK (o.second == 0);
    }

    // 10) "bleibt": Bass bleibt auf dem Grundton, auch wenn die Wendung wechselt
    {
        Settings s; s.key = 0; s.x = 0.85f; s.y = 0.7f; s.z = 0.0f; s.follow[kBass] = false; s.bassPattern = BassEighth;
        std::set<int> pcs;
        for (const auto& e : run (s, 512, 60.0)) if (e.velocity > 0 && e.channel == 2) pcs.insert (e.note % 12);
        CHECK (pcs.size() == 1 && *pcs.begin() == 0);
        s.follow[kBass] = true;
        pcs.clear();
        for (const auto& e : run (s, 512, 60.0)) if (e.velocity > 0 && e.channel == 2) pcs.insert (e.note % 12);
        CHECK (pcs.size() > 1);
    }

    // 11) Unruhe bringt Toene ausserhalb der Akkorde: mehr verschiedene Tonhoehen
    {
        Settings a; a.x = 0.2f; a.y = 0.5f; a.z = 0.0f; a.variation = 2;
        Settings b = a; b.z = 1.0f;
        std::set<int> pa, pb;
        for (const auto& e : run (a, 512, 40.0)) if (e.velocity > 0) pa.insert (e.note % 12);
        for (const auto& e : run (b, 512, 40.0)) if (e.velocity > 0) pb.insert (e.note % 12);
        CHECK (pb.size() > pa.size());
    }

    // 12) Taktarten: Laenge und Betonungsgruppen
    {
        auto m = Meter::from (5, 4); CHECK (m.len == 20 && m.numGroups == 4 && m.groupStart[2] == 12);
        m = Meter::from (7, 8);      CHECK (m.len == 14 && m.numGroups == 3 && m.groupStart[2] == 8);
        m = Meter::from (6, 8);      CHECK (m.len == 12 && m.numGroups == 2);
        m = Meter::from (3, 4);      CHECK (m.len == 12 && m.numGroups == 3);
    }

    // 13) Swing verschiebt die Zwischen-Achtel nach hinten
    {
        Settings s; s.y = 0.4f; s.arpRate = RateEighth; s.arpFigure = ArpUp; s.solo[kArp] = true;
        auto straight = run (s, 512, 4.0);
        s.swing = 1.0f;
        auto swung = run (s, 512, 4.0);
        long long sumA = 0, sumB = 0;
        for (const auto& e : straight) if (e.velocity > 0) sumA += e.sample;
        for (const auto& e : swung) if (e.velocity > 0) sumB += e.sample;
        CHECK (sumB > sumA);
    }

    // 14) Vorhoeren ohne Speicheranforderung, Negative Position (Vorzaehler) ohne Noten
    {
        Generator g; g.reset(); Preview p; p.prepare (48000); EventList l; Settings s; s.y = 1.0f;
        std::vector<float> L (64), R (64);
        for (int b = 0; b < 600; ++b)
        {
            Transport t; t.playing = true; t.bpm = 140; t.sampleRate = 48000; t.ppq = b * 64.0 / (48000.0 * 60.0 / 140.0);
            NoAllocations guard;
            l.clear(); g.process (t, s, 64, l);
            std::fill (L.begin(), L.end(), 0.0f); std::fill (R.begin(), R.end(), 0.0f);
            for (int e = 0; e < l.size; ++e) p.handle (l.events[(size_t) e]);
            p.render (L.data(), R.data(), 64);
            for (float x : L) CHECK (std::isfinite (x) && std::fabs (x) < 2.0f);
        }
        Generator h; h.reset(); EventList m;
        Transport t; t.playing = true; t.bpm = 120; t.sampleRate = 48000; t.ppq = -2.0;
        h.process (t, s, 512, m);
        CHECK (m.size == 0);
    }

    // 15) Akkordnamen, international (B = H, B\u266d, \u266f)
    {
        char buf[32];
        chordName (9, 0, Min, buf, 32);      CHECK (std::string (buf) == "Am");
        chordName (9, 8, Maj7, buf, 32);     CHECK (std::string (buf) == "Fmaj7");
        chordName (0, 11, MinMaj7, buf, 32); CHECK (std::string (buf) == "Bm(maj7)");
        chordName (0, 10, Maj, buf, 32);     CHECK (std::string (buf) == "B\xe2\x99\xad");
        chordName (9, 11, Min, buf, 32);     CHECK (std::string (buf) == "G\xe2\x99\xafm");
        chordName (9, 11, Maj, buf, 32);     CHECK (std::string (buf) == "A\xe2\x99\xad");
    }

    // 16) Jede Wendung fuellt genau eine Phrase
    for (const auto& w : kWendungen)
    {
        int bars = 0;
        for (int i = 0; i < w.n; ++i) bars += w.ch[i].bars;
        CHECK (bars == kPhraseBars);
    }

    // 17) Wechsel: bewegt sich der Punkt deutlich, kommt die neue Wendung am naechsten Wechselpunkt (Schlag / 4 Takte)
    {
        auto wendungAt = [] (int change, double moveAt, double until, std::vector<int>& seen, bool& balanced)
        {
            Generator g; g.reset(); EventList l; Settings s; s.x = 0.08f; s.y = 0.15f; s.z = 0.6f; s.change = change;
            for (auto& v : s.layerIntensity) v = 1.0f;
            std::map<std::pair<int, int>, int> open;
            const double blockQ = 256.0 / 24000.0;
            for (int b = 0; b * blockQ < until; ++b)
            {
                const double ppq = b * blockQ;
                if (ppq >= moveAt) { s.x = 0.85f; s.y = 0.55f; s.z = 0.05f; }
                Transport t; t.playing = true; t.bpm = 120; t.sampleRate = 48000; t.ppq = ppq;
                l.clear();
                { NoAllocations guard; g.process (t, s, 256, l); }
                for (int e = 0; e < l.size; ++e)
                {
                    const auto& ev = l.events[(size_t) e];
                    int& o = open[std::make_pair ((int) ev.channel, (int) ev.note)];
                    if (ev.velocity > 0) { if (o != 0) balanced = false; ++o; } else { if (o != 1) balanced = false; --o; }
                }
                seen.push_back (g.wendung());
            }
            Transport stop; l.clear(); g.process (stop, s, 256, l);
            for (int e = 0; e < l.size; ++e) open[std::make_pair ((int) l.events[(size_t) e].channel, (int) l.events[(size_t) e].note)] -= 1;
            for (const auto& o : open) if (o.second != 0) balanced = false;
        };
        const double blockQ = 256.0 / 24000.0;
        std::vector<int> beat, four; bool okA = true, okB = true;
        wendungAt (ChangeBeat, 9.3, 20.0, beat, okA);
        wendungAt (Change4Bars, 9.3, 20.0, four, okB);
        CHECK (okA && okB);
        const int dark = beat[0];
        CHECK (kShapes[kWendungen[dark].ch[0].type].minor);
        CHECK (beat[(size_t) (10.05 / blockQ)] != dark);                                   // naechster Schlag (10.0)
        CHECK (! kShapes[kWendungen[beat[(size_t) (10.05 / blockQ)]].ch[0].type].minor);
        CHECK (four[(size_t) (15.9 / blockQ)] == dark);                                    // bei "4 Takte" erst ab Takt 5 (16.0)
        CHECK (four[(size_t) (16.05 / blockQ)] != dark);
    }

    // 18) Hysterese: eine kleine Bewegung wechselt die Wendung nicht
    {
        Generator g; g.reset(); EventList l; Settings s; s.x = 0.30f; s.y = 0.45f; s.z = 0.45f;
        int first = -1; bool same = true;
        for (int b = 0; b < 600; ++b)
        {
            const double ppq = b * 256.0 / 24000.0;
            if (ppq > 31.0) break;                 // innerhalb der ersten Phrase bleiben
            s.x = 0.30f + 0.03f * (float) std::sin (ppq);
            Transport t; t.playing = true; t.bpm = 120; t.sampleRate = 48000; t.ppq = ppq;
            l.clear(); g.process (t, s, 256, l);
            if (first < 0) first = g.wendung(); else if (g.wendung() != first) same = false;
        }
        CHECK (same);
    }

    // 19) Oktavlage je Ebene
    {
        Settings a; a.y = 0.5f; a.solo[kFlaeche] = true; a.padPattern = PadHeld;
        Settings b = a; b.octave[kFlaeche] = 1;
        Settings c = a; c.octave[kFlaeche] = -2;
        auto ea = run (a, 512, 10.0), eb = run (b, 512, 10.0), ec = run (c, 512, 10.0);
        CHECK (ea.size() == eb.size() && ea.size() == ec.size() && ! ea.empty());
        for (size_t i = 0; i < ea.size(); ++i) { CHECK (eb[i].note == ea[i].note + 12); CHECK (ec[i].note == ea[i].note - 24); }
    }

    // 20) Eigene Akkordfolge: F - C - B - G je 2 Takte (Tonart egal), danach von vorn
    {
        Settings s; s.key = 9; s.y = 0.5f; s.custom = true; s.bassPattern = BassQuarter;
        s.customChords[0] = { 5, Maj, 2 }; s.customChords[1] = { 0, Maj, 2 }; s.customChords[2] = { 10, Maj, 2 }; s.customChords[3] = { 7, Maj, 2 };
        std::vector<int> roots;
        for (const auto& e : run (s, 512, 32.0)) if (e.velocity > 0 && e.channel == 2) roots.push_back (e.note % 12);
        // 120 BPM: 2 Takte = 4 s = 8 Viertel, also Bass-Viertel 0..7 = F, 8..15 = C, 16..23 = B, 24..31 = G, 32.. = F
        CHECK (roots.size() >= 40);
        CHECK (roots[0] == 5 && roots[7] == 5 && roots[8] == 0 && roots[16] == 10 && roots[24] == 7 && roots[32] == 5);
        checkBalanced (run (s, 333, 30.0));
        Generator g; g.reset(); EventList l; Transport t; t.playing = true; t.ppq = 0.0;
        g.process (t, s, 512, l);
        CHECK (g.wendung() == kCustomWendung);
        // ungerade Laenge (3 Takte) und alle Ebenen
        Settings o = s; o.customChords[1].bars = 1; o.customChords[2].bars = 0; o.customChords[3].bars = 0; o.bassPattern = BassWalking;
        for (auto& v : o.layerIntensity) v = 1.0f;
        checkBalanced (run (o, 256, 30.0));
        // Umschalten waehrend des Spielens: nichts haengt
        Generator h; h.reset(); EventList m; std::map<std::pair<int, int>, int> open;
        Settings u = s; u.custom = false;
        for (int b = 0; b < 300; ++b)
        {
            if (b == 100) u.custom = true;
            if (b == 200) u.custom = false;
            Transport tt; tt.playing = b < 299; tt.bpm = 120; tt.sampleRate = 48000; tt.ppq = b * 512.0 / 24000.0;
            m.clear(); h.process (tt, u, 512, m);
            for (int e = 0; e < m.size; ++e) open[std::make_pair ((int) m.events[(size_t) e].channel, (int) m.events[(size_t) e].note)] += m.events[(size_t) e].velocity > 0 ? 1 : -1;
        }
        for (const auto& op : open) CHECK (op.second == 0);
    }

    // 21) Solo und Mute
    {
        Settings s; s.y = 0.9f;
        s.solo[kBass] = true;
        CHECK ((channelsUsed (run (s, 512, 10.0)) == std::set<int> { 2 }));
        s.solo[kBass] = false; s.mute[kBass] = true;
        const auto used = channelsUsed (run (s, 512, 10.0));
        CHECK (used.count (2) == 0 && used.count (1) == 1 && used.count (3) == 1);
        s.solo[kArp] = true; s.solo[kFlaeche] = true;     // mehrere Solo-Ebenen
        CHECK ((channelsUsed (run (s, 512, 10.0)) == std::set<int> { 1, 3 }));
    }

    // 22) Intensitaet nur fuer den Bass: duenner oder dichter, die anderen Ebenen bleiben gleich
    {
        Settings a; a.y = 0.5f; a.variation = 3;
        Settings thin = a; thin.layerIntensity[kBass] = -1.0f;
        Settings dense = a; dense.layerIntensity[kBass] = 1.0f;
        const auto ea = run (a, 512, 30.0), et = run (thin, 512, 30.0), ed = run (dense, 512, 30.0);
        CHECK (countOns (ed, 2) > 2 * countOns (et, 2));
        CHECK (countOns (ea, 1) == countOns (ed, 1) && countOns (ea, 3) == countOns (ed, 3));
        CHECK (countOns (ea, 1) == countOns (et, 1) && countOns (ea, 3) == countOns (et, 3));
        checkBalanced (ed); checkBalanced (et);
        // hochgedrehter Arp spielt auch bei ruhiger Stimmung
        Settings calm; calm.y = 0.05f; calm.layerIntensity[kArp] = 0.6f;
        CHECK (channelsUsed (run (calm, 512, 10.0)).count (3) == 1);
    }

    // 23) Abwechslung: 0 = immer die passendste Wendung, 1 = mehrere Nachbarn; Kandidaten nach Passung sortiert
    {
        int c[16];
        Settings s; s.x = 0.3f; s.y = 0.45f; s.z = 0.45f;
        s.variety = 0.0f;
        CHECK (Generator::candidates (s, c, 16) == 1);
        std::set<int> picks;
        for (int v = 1; v <= 16; ++v) for (long long ph = 0; ph < 8; ++ph) { Settings o = s; o.variation = v; picks.insert (Generator::pick (o, ph)); }
        CHECK (picks.size() == 1 && *picks.begin() == c[0]);
        s.variety = 1.0f;
        const int n = Generator::candidates (s, c, 16);
        CHECK (n >= 3);
        for (int i = 1; i < n; ++i) CHECK (Generator::weight (kWendungen[c[i - 1]], s) >= Generator::weight (kWendungen[c[i]], s));
        int few[2];                                     // begrenzte Liste: die besten zuerst
        CHECK (Generator::candidates (s, few, 2) == 2 && few[0] == c[0] && few[1] == c[1]);
        picks.clear();
        for (int v = 1; v <= 16; ++v) for (long long ph = 0; ph < 8; ++ph) { Settings o = s; o.variation = v; picks.insert (Generator::pick (o, ph)); }
        CHECK (picks.size() >= 3);
        // ueber das ganze Feld mit viel Abwechslung und Wechsel am Schlag: nichts haengt
        Settings w; w.variety = 1.0f; w.y = 0.7f; w.z = 0.5f; for (auto& v : w.layerIntensity) v = 0.5f;
        checkBalanced (run (w, 300, 40.0));
    }

    // 24) Eigener Basston (Terrassen: D-Dur ueber C) und Orgelpunkt
    {
        int terr = -1;
        for (int i = 0; i < kNumWendungen; ++i) if (std::string (kWendungen[i].name) == "Terrassen") terr = i;
        CHECK (terr >= 0 && kWendungen[terr].ch[1].bass == 0);
        char buf[16];
        chordName (0, 2, Maj, buf, 16); CHECK (std::string (buf) == "D");
        Settings s; s.x = 0.8f; s.y = 0.4f; s.z = 0.1f; s.variety = 0.0f; s.key = 0; s.bassPattern = BassQuarter; s.solo[kBass] = true;
        std::set<int> pcs;
        for (const auto& e : run (s, 512, 16.0)) if (e.velocity > 0) pcs.insert (e.note % 12);
        CHECK (pcs.count (2) == 0);                  // unter D-Dur liegt C, kein D im Bass
        s.bassPattern = BassPedal; pcs.clear();
        for (const auto& e : run (s, 512, 16.0)) if (e.velocity > 0) pcs.insert (e.note % 12);
        CHECK (pcs.size() == 1 && *pcs.begin() == 0);
    }

    // 25) Gegenstimme: immer nur ein Ton, in ihrer Lage, ueberwiegend Akkordtoene, bei Unruhe mit Vorhalten
    for (float z : { 0.0f, 0.8f })
        for (float y : { 0.3f, 0.6f, 0.9f })
        {
            Settings s; s.y = y; s.z = z; s.x = 0.5f; s.variation = 4; s.solo[kGegenstimme] = true;
            const auto ev = run (s, 333, 30.0);
            checkBalanced (ev);
            int open = 0, maxOpen = 0, ons = 0;
            for (const auto& e : ev)
            {
                if (e.channel != 5) continue;
                open += e.velocity > 0 ? 1 : -1; maxOpen = std::max (maxOpen, open);
                if (e.velocity > 0) { ++ons; CHECK (e.note >= 58 && e.note <= 80); }
            }
            CHECK (maxOpen <= 2 && ons >= 4);   // hoechstens kurz zwei Toene: Legato-Ueberlappung
        }
    {   // mehr Intensitaet = bewegter
        Settings a; a.y = 0.3f; a.solo[kGegenstimme] = true;
        Settings b = a; b.y = 0.9f;
        CHECK (countOns (run (b, 512, 30.0), 5) > countOns (run (a, 512, 30.0), 5));
    }

    // 26) Eigene Folge leiht den Stil der Wendung am Punkt im Feld; die Akkorde bleiben
    {
        Settings s; s.key = 0; s.custom = true; s.variety = 0.0f;
        s.customChords[0] = { 5, Maj, 2 }; s.customChords[1] = { 0, Maj, 2 }; s.customChords[2] = { 10, Maj, 2 }; s.customChords[3] = { 7, Maj, 2 };
        Settings a = s; a.x = 0.55f; a.y = 0.70f; a.z = 0.15f;     // Synth-Groove: Funk-Bass
        Settings b = s; b.x = 0.40f; b.y = 0.50f; b.z = 0.20f;     // Ermittlung: Walking Bass
        Generator g; g.reset(); EventList l; Transport t; t.playing = true;
        g.process (t, a, 512, l);
        CHECK (g.wendung() == kCustomWendung && std::string (kWendungen[g.styleWendung()].name) == "Synth-Groove");
        g.reset(); l.clear(); g.process (t, b, 512, l);
        CHECK (std::string (kWendungen[g.styleWendung()].name) == "Ermittlung");
        std::vector<int> ra, rb;
        for (const auto& e : run (a, 512, 16.0)) if (e.velocity > 0 && e.channel == 2) ra.push_back (e.note);
        for (const auto& e : run (b, 512, 16.0)) if (e.velocity > 0 && e.channel == 2) rb.push_back (e.note);
        CHECK (ra != rb);
        // Flaeche spielt in beiden Faellen die eigenen Akkorde (Grundtoene F, C, B, G kommen vor)
        std::set<int> pcs;
        for (const auto& e : run (a, 512, 16.0)) if (e.velocity > 0 && e.channel == 1) pcs.insert (e.note % 12);
        CHECK (pcs.count (5) && pcs.count (0) && pcs.count (10) && pcs.count (7));
        // VARIATION aendert bei eigener Folge die Lage der Flaeche
        std::set<std::vector<int>> voicings;
        for (int v = 1; v <= 6; ++v)
        {
            Settings o = s; o.y = 0.4f; o.variation = v; o.solo[kFlaeche] = true; o.padPattern = PadHeld;
            std::vector<int> first;
            for (const auto& e : run (o, 512, 2.0)) if (e.velocity > 0 && e.channel == 1) first.push_back (e.note);
            voicings.insert (first);
        }
        CHECK (voicings.size() >= 2);
    }

    // 27) Durchgaenge: bei viel Intensitaet erklingt vor dem naechsten Akkord dessen Dominante
    {
        Settings s; s.key = 0; s.custom = true; s.y = 0.7f; s.padPattern = PadHeld; s.solo[kFlaeche] = true;
        s.customChords[0] = { 0, Maj, 2 }; s.customChords[1] = { 5, Maj, 2 };   // C - F: Dominante von F ist C7 (B kommt dazu)
        auto has = [] (const std::vector<Abs>& ev, int pc) { for (const auto& e : ev) if (e.velocity > 0 && e.channel == 1 && e.note % 12 == pc) return true; return false; };
        const auto off = run (s, 512, 8.0);
        s.passing = true;
        const auto on = run (s, 512, 8.0);
        CHECK (! has (off, 10) && has (on, 10));
        checkBalanced (on);
        Settings calm = s; calm.y = 0.3f;                                         // bei wenig Intensitaet keine Durchgaenge
        CHECK (! has (run (calm, 512, 8.0), 10));
        Settings all; all.passing = true; all.y = 0.8f; for (auto& v : all.layerIntensity) v = 0.5f;
        checkBalanced (run (all, 300, 30.0));
    }

    // 28) 80er Pop-Rock: eigener Vorrat, alle Muster und das ganze Feld sauber, Lead-Hook einstimmig und gleichbleibend
    {
        CHECK (kNumPopWendungen >= 16);
        for (int i = 0; i < kNumPopWendungen; ++i)
        {
            int bars = 0;
            for (int c = 0; c < kPopWendungen[i].n; ++c) bars += kPopWendungen[i].ch[c].bars;
            CHECK (bars == kPhraseBars);
        }
        int c[8];
        Settings pop; pop.genre = GenrePopRock; pop.x = 0.25f; pop.y = 0.85f; pop.z = 0.4f; pop.variety = 0.0f;
        CHECK (Generator::candidates (pop, c, 8) == 1 && std::string (kPopWendungen[c[0]].name) == "Rebellenschrei");
        for (float x : { 0.1f, 0.5f, 0.9f })
            for (float y : { 0.2f, 0.6f, 0.95f })
                for (float z : { 0.0f, 0.8f })
                {
                    Settings s = pop; s.x = x; s.y = y; s.z = z; s.variety = 0.7f;
                    checkBalanced (run (s, 333, 20.0));
                }
        for (int bp : { (int) BassHiNrg, (int) BassGallop })
        {
            Settings s = pop; s.bassPattern = bp; s.padPattern = PadGated; s.arpFigure = ArpSid;
            const auto ev = run (s, 256, 10.0);
            checkBalanced (ev);
            CHECK (countOns (ev, 2) > 20 && countOns (ev, 3) > 40);
        }
        Settings h = pop; h.bassPattern = BassHiNrg; h.y = 0.5f; h.solo[kBass] = true;   // Hi-NRG: Grundton und Oberoktave
        std::set<int> notes;
        for (const auto& e : run (h, 512, 2.0)) if (e.velocity > 0) notes.insert (e.note);
        CHECK (notes.size() >= 2 && (*notes.rbegin() - *notes.begin()) % 12 == 0);
        Settings l = pop; l.y = 0.6f; l.z = 0.0f; l.solo[kGegenstimme] = true; l.custom = true;   // Lead-Hook
        l.customChords[0] = { 9, Min, 4 }; l.customChords[1] = { 9, Min, 4 };
        const auto ev = run (l, 512, 32.0);
        checkBalanced (ev);
        std::vector<int> seq;
        int open = 0, maxOpen = 0;
        for (const auto& e : ev) { open += e.velocity > 0 ? 1 : -1; maxOpen = std::max (maxOpen, open); if (e.velocity > 0) seq.push_back (e.note); }
        CHECK (maxOpen <= 2 && seq.size() >= 32);                                // Legato: der neue Ton kommt kurz vor dem Ende des alten
        for (size_t i = 8; i < seq.size(); ++i) CHECK (seq[i] == seq[i - 8]);   // gleichbleibende Figur ueber gleichem Akkord
        Settings nl = l; nl.legato = false;                                     // ohne Legato: Toene abgesetzt, nie zwei zugleich
        open = 0; maxOpen = 0;
        for (const auto& e : run (nl, 512, 16.0)) { open += e.velocity > 0 ? 1 : -1; maxOpen = std::max (maxOpen, open); }
        CHECK (maxOpen == 1);
    }

    // 29) Dynamik als CC: nur wenn eingeschaltet, Werte im Bereich, sparsam, Pop flacher als Score
    {
        auto collect = [] (Settings s, int& count, int& lo, int& hi)
        {
            Generator g; g.reset(); EventList l; count = 0; lo = 127; hi = 0;
            for (int b = 0; b < 2000; ++b)   // gut 40 Viertel
            {
                Transport t; t.playing = true; t.bpm = 120; t.sampleRate = 48000; t.ppq = b * 512.0 / 24000.0;
                l.clear();
                { NoAllocations guard; g.process (t, s, 512, l); }
                for (int i = 0; i < l.size; ++i)
                {
                    const auto& e = l.events[(size_t) i];
                    if (e.type == 1 && e.note == 1 && e.channel == 1) { ++count; lo = std::min (lo, (int) e.velocity); hi = std::max (hi, (int) e.velocity); }
                    if (e.type == 1) CHECK (e.velocity >= 1 && e.velocity <= 127 && (e.note == 1 || e.note == 11));
                }
            }
        };
        Settings s; s.y = 0.5f; s.z = 0.3f;
        int n, lo, hi;
        collect (s, n, lo, hi); CHECK (n == 0);
        s.dynamics = true;
        collect (s, n, lo, hi);
        CHECK (n > 40 && n < 2000);
        CHECK (hi - lo >= 4 && lo >= 40 && hi <= 110);
        Settings p = s; p.genre = GenrePopRock;
        int pn, plo, phi;
        collect (p, pn, plo, phi);
        CHECK (phi - plo < hi - lo);
        Settings off = s; off.ccDynamics = 0; off.ccExpression = 0;
        collect (off, n, lo, hi); CHECK (n == 0);
        checkBalanced (run (s, 300, 20.0));
    }

    // 30) Legato der Gegenstimme: der neue Ton kommt vor dem Loslassen des alten
    {
        Settings s; s.y = 0.8f; s.solo[kGegenstimme] = true; s.x = 0.5f;
        const auto ev = run (s, 512, 20.0);
        checkBalanced (ev);
        int overlaps = 0, open = 0;
        for (const auto& e : ev) { open += e.velocity > 0 ? 1 : -1; if (open == 2) ++overlaps; CHECK (open <= 2); }
        CHECK (overlaps >= 4);
    }

    // 31) Naechster Akkord und Fortschritt fuer die Anzeige
    {
        Settings s; s.custom = true; s.key = 0;
        s.customChords[0] = { 0, Maj, 2 }; s.customChords[1] = { 7, Min, 2 };
        Generator g; g.reset(); EventList l;
        Transport t; t.playing = true; t.bpm = 120; t.sampleRate = 48000; t.ppq = 0.0;
        g.process (t, s, 512, l);
        CHECK (g.nextRoot() == 7 && g.nextType() == Min && g.chordProgress() < 0.1f);
        for (int b = 1; b < 300 && t.ppq < 6.0; ++b) { t.ppq = b * 512.0 / 24000.0; l.clear(); g.process (t, s, 512, l); }
        CHECK (g.chordProgress() > 0.6f && g.nextRoot() == 7);
    }
    // 32) Tonumfang: alle Ebenen bleiben in ihrem Bereich, auch mit Oktav-Einstellung, in beiden Genres
    {
        const int lo[kNumRanges] = { 48, 36, 60, 72, 48, 40 }, hi[kNumRanges] = { 84, 81, 96, 100, 88, 64 };
        int checked = 0;
        for (int genre = 0; genre < kNumGenres; ++genre)
            for (float x : { 0.1f, 0.5f, 0.9f })
                for (float y : { 0.2f, 0.6f, 0.95f })
                    for (float z : { 0.0f, 0.7f })
                    {
                        Settings s; s.genre = genre; s.x = x; s.y = y; s.z = z; s.variation = 1 + (int) (x * 10 + y * 5);
                        s.passing = true;
                        for (int i = 0; i < kNumRanges; ++i) { s.rangeOn[i] = true; s.rangeLo[i] = lo[i]; s.rangeHi[i] = hi[i]; }
                        s.octave[kArp] = (int) (z * 3) - 1;   // -1 oder +1
                        s.octave[kBass] = -2;
                        const auto ev = run (s, 480, 12.0);
                        checkBalanced (ev);
                        for (const auto& e : ev)
                            if (e.velocity > 0)
                            {
                                CHECK (e.note >= lo[e.range] && e.note <= hi[e.range]);
                                ++checked;
                            }
                    }
        CHECK (checked > 2000);
    }

    // 33) Tonumfang ab einer Oktave: Flaeche, Bass und Akzent behalten zu jedem Zeitpunkt dieselben Tonnamen, das Arp verschluckt keinen Ton
    {
        for (float x : { 0.2f, 0.7f })
            for (float y : { 0.3f, 0.8f })
            {
                Settings free; free.x = x; free.y = y; free.z = 0.5f;
                Settings lim = free;
                const int lo[kNumRanges] = { 55, 40, 72, 76, 50, 42 }, hi[kNumRanges] = { 70, 52, 86, 90, 70, 60 };
                for (int i = 0; i < kNumRanges; ++i) { lim.rangeOn[i] = true; lim.rangeLo[i] = lo[i]; lim.rangeHi[i] = hi[i]; }
                const auto a = run (free, 512, 16.0), b = run (lim, 512, 16.0);
                checkBalanced (b);
                for (int ch : { 1, 2, 4 })
                {
                    std::set<std::pair<long long, int>> pa, pb;
                    for (const auto& e : a) if (e.velocity > 0 && e.channel == ch) pa.insert ({ e.sample, e.note % 12 });
                    for (const auto& e : b) if (e.velocity > 0 && e.channel == ch) pb.insert ({ e.sample, e.note % 12 });
                    if (ch != 1) CHECK (pa == pb);
                    else
                    {
                        // Held common tones intentionally have no new attack. Compare sounding harmony, not attacks.
                        std::set<long long> times;
                        for (const auto& e : a) times.insert (e.sample);
                        for (const auto& e : b) times.insert (e.sample);
                        std::map<std::pair<int,int>, bool> aa, bb; size_t ia = 0, ib = 0;
                        for (auto t : times)
                        {
                            while (ia < a.size() && a[ia].sample <= t) { const auto& e = a[ia++]; if (e.channel == 1) aa[{e.midi,e.note}] = e.velocity > 0; }
                            while (ib < b.size() && b[ib].sample <= t) { const auto& e = b[ib++]; if (e.channel == 1) bb[{e.midi,e.note}] = e.velocity > 0; }
                            std::set<int> ca, cb;
                            for (auto e : aa) if (e.second) ca.insert (e.first.second % 12);
                            for (auto e : bb) if (e.second) cb.insert (e.first.second % 12);
                            CHECK (ca == cb);
                        }
                    }
                }
                CHECK (countOns (a, 3) == countOns (b, 3));
                CHECK (countOns (b, 3) > 20);
            }
    }

    // 34) Sehr enger Tonumfang (unter einer Oktave): bleibt im Bereich, spielt weiter, Akkordtoene ersetzen fehlende Tonnamen
    {
        Settings s; s.y = 0.8f; s.x = 0.4f;
        for (int i = 0; i < kNumRanges; ++i) { s.rangeOn[i] = true; s.rangeLo[i] = 64; s.rangeHi[i] = 70; }
        Settings free = s; for (auto& r : free.rangeOn) r = false;
        const auto ev = run (s, 512, 16.0), fr = run (free, 512, 16.0);
        checkBalanced (ev);
        for (const auto& e : ev) if (e.velocity > 0) CHECK (e.note >= 64 && e.note <= 70);
        CHECK (countOns (ev, 3) == countOns (fr, 3));
        CHECK (countOns (ev, 1) > 0 && countOns (ev, 2) > 0 && countOns (ev, 5) > 0);
    }

    // 35) Gegenstimme mit Tonumfang: bleibt im Bereich und bewegt sich weiter
    {
        Settings s; s.y = 0.8f; s.solo[kGegenstimme] = true;
        s.rangeOn[kGegenstimme] = true; s.rangeLo[kGegenstimme] = 36; s.rangeHi[kGegenstimme] = 55;   // tiefe Lage, unter der ueblichen
        const auto ev = run (s, 512, 30.0);
        checkBalanced (ev);
        std::set<int> notes;
        for (const auto& e : ev) if (e.velocity > 0) { CHECK (e.note >= 36 && e.note <= 55); notes.insert (e.note); }
        CHECK (notes.size() >= 3);
    }

    // 37) Freie Kanalwahl: alle Ausgaenge auf einem Kanal (z. B. ein Klavier) - nichts haengt, nichts doppelt
    for (int genre = 0; genre < kNumGenres; ++genre)
        for (float y : { 0.3f, 0.7f, 1.0f })
            for (float z : { 0.0f, 0.6f })
            {
                Settings s; s.genre = genre; s.y = y; s.z = z; s.x = 0.4f + 0.2f * z;
                for (auto& c : s.channel) c = 1;
                for (auto& v : s.layerIntensity) v = 0.5f;
                const auto ev = run (s, 300, 20.0);
                checkBalanced (ev);
                for (const auto& e : ev) CHECK (e.midi == 1);
                CHECK (countOns (ev) > 50);
            }
    {
        Settings s; s.y = 0.8f;
        s.channel[OutPadLong] = 9; s.channel[OutPadShort] = 9; s.channel[OutBassLong] = 16;
        for (const auto& e : run (s, 512, 10.0))
        {
            if (e.out == OutPadLong || e.out == OutPadShort) CHECK (e.midi == 9);
            if (e.out == OutBassLong) CHECK (e.midi == 16);
        }
    }

    // 38) Lang und kurz: gehaltene Muster auf dem Kanal fuer lang, kurze auf dem fuer kurz
    {
        auto outs = [] (Settings s, int layer)
        {
            std::set<int> o;
            for (const auto& e : run (s, 512, 12.0)) if (e.velocity > 0 && e.channel == layer + 1) o.insert (e.out);
            return o;
        };
        Settings s; s.y = 0.5f;
        s.padPattern = PadHeld;     CHECK ((outs (s, kFlaeche) == std::set<int> { OutPadLong }));
        s.padPattern = PadStaccato; CHECK ((outs (s, kFlaeche) == std::set<int> { OutPadShort }));
        s.padPattern = PadGated;    CHECK ((outs (s, kFlaeche) == std::set<int> { OutPadShort }));
        s.bassPattern = BassHalf;   CHECK ((outs (s, kBass) == std::set<int> { OutBassLong }));
        s.bassPattern = BassHeld;   CHECK ((outs (s, kBass) == std::set<int> { OutBassLong }));
        s.bassPattern = BassEighth; CHECK ((outs (s, kBass) == std::set<int> { OutBassShort }));
        s.bassPattern = BassFunk;   CHECK ((outs (s, kBass) == std::set<int> { OutBassShort }));
        s.bassPattern = BassPedal; s.y = 0.8f;   // Orgelpunkt liegt, bei viel Intensitaet pulsiert er zusaetzlich kurz
        CHECK ((outs (s, kBass) == std::set<int> { OutBassLong, OutBassShort }));
        // Lang und kurz auf demselben Kanal: wie ein einziger Kanal, nichts haengt
        Settings one = s; one.padPattern = PadAuto; one.bassPattern = BassAuto; one.channel[OutPadShort] = 1; one.channel[OutBassShort] = 3;
        for (float x : { 0.2f, 0.5f, 0.8f }) { one.x = x; checkBalanced (run (one, 333, 20.0)); }
    }

    // 39) Akzent: Tupfer hoch und kurz, Stich tief und kurz, erst ab mehr Intensitaet; Gegenstimme in eigener Lage dazwischen
    {
        auto collect = [] (const Settings& s, std::map<int, std::vector<long long>>& len, std::map<int, std::set<int>>& notes)
        {
            std::map<std::pair<int, int>, long long> start;
            for (const auto& e : run (s, 512, 40.0))
            {
                const auto key = std::make_pair (e.midi, e.note);
                if (e.velocity > 0) { start[key] = e.sample; notes[e.out].insert (e.note); }
                else len[e.out].push_back (e.sample - start[key]);
            }
        };
        const long long sixteenth = 6000;   // 120 BPM, 48 kHz
        for (int genre = 0; genre < kNumGenres; ++genre)
            for (float x : { 0.0f, 0.5f, 1.0f })
            {
                Settings low; low.genre = genre; low.x = x; low.y = 0.35f;
                std::map<int, std::vector<long long>> len; std::map<int, std::set<int>> notes;
                collect (low, len, notes);
                CHECK (notes[OutTupfer].size() >= 1 && notes[OutStich].empty());          // wenig Intensitaet: nur Tupfer
                Settings high = low; high.y = 0.9f;
                len.clear(); notes.clear();
                collect (high, len, notes);
                CHECK (! notes[OutTupfer].empty() && ! notes[OutStich].empty());
                for (int n : notes[OutTupfer]) CHECK (n >= 79);
                for (int n : notes[OutStich]) CHECK (n <= 61);
                if (genre == GenreScore) for (int n : notes[OutCounter]) CHECK (n >= 62 && n <= 78);
                for (int o : { (int) OutTupfer, (int) OutStich })
                    for (long long l : len[o]) CHECK (l <= 3 * sixteenth + 1);                // nie ein stehender Ton
            }
        // Selten: deutlich weniger Akzente als Arp-Toene, mehr bei mehr Intensitaet
        Settings a; a.y = 0.4f; Settings b; b.y = 0.95f;
        int ta = 0, tb = 0, arp = 0;
        for (const auto& e : run (a, 512, 40.0)) if (e.velocity > 0) { ta += e.out == OutTupfer ? 1 : 0; arp += e.out == OutArp ? 1 : 0; }
        for (const auto& e : run (b, 512, 40.0)) if (e.velocity > 0) tb += (e.out == OutTupfer || e.out == OutStich) ? 1 : 0;
        CHECK (ta > 0 && ta * 4 < arp && tb > ta);
        // Nur von der Position abhaengig: ab Takt 9 gestartet wie durchgespielt
        Settings j; j.y = 0.85f; j.z = 0.2f; j.solo[kAkzent] = true;
        const auto whole = run (j, 512, 32.0), late = run (j, 512, 16.0, 120.0, 48000.0, 32.0);
        std::vector<std::pair<long long, int>> wa, wb;
        for (const auto& e : whole) if (e.velocity > 0 && e.sample >= 16 * 48000) wa.push_back ({ e.sample - 16 * 48000, e.note });
        for (const auto& e : late) if (e.velocity > 0) wb.push_back ({ e.sample, e.note });
        CHECK (! wb.empty() && wa == wb);
    }

    // 36) Neue Wendungen im Pop-Rock-Vorrat: alle Akkordlaengen ergeben acht Takte
    {
        for (int i = 0; i < kNumPopWendungen; ++i) CHECK (wendungBars (kPopWendungen[i]) == 8);
        for (int i = 0; i < kNumWendungen; ++i) CHECK (wendungBars (kWendungen[i]) == 8);
    }
    // 40) Einstieg und Aufbau: zuerst nur die Einstiegs-Ebene, die anderen folgen auf Taktgrenzen in fester Reihenfolge
    {
        const long long bar = 96000;   // 4/4, 120 bpm
        for (int e = EntryPad; e < kNumEntries; ++e)
        {
            Settings s; s.scene = true; s.entry = e; s.buildBars = 8; s.y = 0.8f; s.x = 0.5f;
            const auto ev = run (s, 512, 40.0);
            checkBalanced (ev);
            long long firstOn[kNumLayers]; for (auto& f : firstOn) f = -1;
            for (const auto& x : ev) if (x.velocity > 0 && firstOn[x.channel - 1] < 0) firstOn[x.channel - 1] = x.sample;
            if (e == EntryAll)
            {
                for (int l : { kFlaeche, kBass, kArp, kGegenstimme }) CHECK (firstOn[l] >= 0 && firstOn[l] < bar);
                continue;
            }
            const int lead = kEntryLayer[e];
            CHECK (firstOn[lead] >= 0 && firstOn[lead] < bar);
            for (int i = 1; i < kNumLayers; ++i)
            {
                const int l = kEntryOrder[e][i];
                const long long due = (long long) std::lround (i * 7.0 / 4.0) * bar;   // Platz i von 5, ueber 8 Takte verteilt
                CHECK (firstOn[l] < 0 || firstOn[l] >= due);
                if (l != kAkzent) CHECK (firstOn[l] >= 0 && firstOn[l] < due + bar);
            }
            for (const auto& x : ev)   // im ersten Takt nur die Einstiegs-Ebene
                if (x.velocity > 0 && x.sample < bar) CHECK (x.channel - 1 == lead);
            if (e == EntryPad)   // schuechtern: ein einzelner stehender Ton
            {
                int n = 0;
                for (const auto& x : ev) if (x.velocity > 0 && x.sample < bar) ++n;
                CHECK (n >= 3); // even a quiet entry retains the complete harmony
            }
            if (e == EntryPulse)   // Puls: kurze Viertel im ganzen Aufbau
                for (const auto& x : ev)
                    if (x.velocity > 0 && x.channel - 1 == kBass && x.sample < 8 * bar) CHECK (x.sample % 24000 == 0);
        }
        // Ohne Aufbau setzt alles zugleich ein (wie vor 1.3)
        Settings off; off.y = 0.8f;
        long long first[kNumLayers]; for (auto& f : first) f = -1;
        for (const auto& x : run (off, 512, 4.0)) if (x.velocity > 0 && first[x.channel - 1] < 0) first[x.channel - 1] = x.sample;
        for (int l : { kFlaeche, kBass, kArp, kGegenstimme }) CHECK (first[l] >= 0 && first[l] < bar);
        // Szenenstart ist der Wiedergabebeginn: ab Takt 9 gestartet beginnt der Aufbau dort
        Settings late; late.scene = true; late.entry = EntryArp; late.y = 0.8f;
        for (const auto& x : run (late, 512, 2.0, 120.0, 48000.0, 32.0)) if (x.velocity > 0) CHECK (x.channel - 1 == kArp);
    }

    // 41) Auto-Einstieg: gleicher Wurf, gleicher Einstieg; verschiedene Wuerfe ergeben verschiedene Einstiege;
    //     es kommen nur Ebenen in Frage, die bei dieser Intensitaet spielen
    {
        std::set<int> seen;
        for (int w = 0; w < 40; ++w)
        {
            Settings s; s.seed = w; s.y = 0.8f;
            const int e = Generator::autoEntry (s);
            CHECK (e == Generator::autoEntry (s));
            CHECK (e > EntryAuto && e < kNumEntries);
            seen.insert (e);
            Settings q = s; q.y = 0.05f;
            const int eq = Generator::autoEntry (q);
            CHECK (eq == EntryPad || eq == EntryBass || eq == EntryPulse);
            Settings m = s; m.mute[kFlaeche] = true; m.mute[kBass] = true;
            const int em = Generator::autoEntry (m);
            CHECK (em != EntryPad && em != EntryBass && em != EntryPulse);
        }
        CHECK (seen.size() >= 4);
    }

    // 42) Traegheit: wackelt die Intensitaet an der Schwelle, flackert der Arp nicht; er setzt nur auf Taktanfaengen ein
    {
        for (int inertia = 0; inertia < 2; ++inertia)
        {
            Generator g; g.reset(); EventList list;
            Settings s; s.inertia = inertia == 1; s.solo[kArp] = true; s.x = 0.5f;
            std::vector<long long> ons;
            int switches = 0; bool was = false;
            for (long long pos = 0; pos < 48000LL * 32; pos += 512)
            {
                s.y = ((pos / 512) % 7 < 3) ? 0.22f : 0.27f;
                Transport t; t.playing = true; t.bpm = 120.0; t.sampleRate = 48000.0; t.ppq = (double) pos / 24000.0;
                list.clear();
                g.process (t, s, 512, list);
                for (int i = 0; i < list.size; ++i) if (list.events[(size_t) i].velocity > 0 && list.events[(size_t) i].type == 0) ons.push_back (pos + list.events[(size_t) i].offset);
                const bool now = g.layerPlaying (kArp);
                if (now != was) ++switches;
                was = now;
            }
            CHECK (! ons.empty());
            if (inertia == 1)
            {
                CHECK (switches == 1);
                CHECK (ons.front() % 96000 == 0);
            }
            else CHECK (switches > 10);
        }
    }

    // 43) Ende der Szene: hart (ein Schlag, dann Stille), ausklingend (Ebenen gehen nacheinander), offen (dichter bis zum Abbruch)
    {
        const long long bar = 96000;
        for (int end = 0; end < kNumEndings; ++end)
        {
            Settings s; s.sceneBars = 8; s.ending = end; s.y = 0.7f; s.x = 0.4f;
            const auto ev = run (s, 512, 24.0);
            checkBalanced (ev);
            int after = 0, hit = 0, lastBar = 0, early = 0;
            std::set<int> lastLayers;
            for (const auto& x : ev)
            {
                if (x.velocity == 0) continue;
                if (x.sample == 8 * bar) { ++hit; CHECK (x.velocity >= 90); }
                else if (x.sample >= 8 * bar) ++after;
                if (x.sample >= 7 * bar && x.sample < 8 * bar) { ++lastBar; lastLayers.insert (x.channel - 1); }
                if (x.sample >= 2 * bar && x.sample < 3 * bar) ++early;
            }
            CHECK (after == 0);
            for (const auto& x : ev) if (x.velocity == 0) CHECK (x.sample <= 8 * bar + 12000);   // alles ist kurz nach dem Ende aus
            if (end == EndHard)
            {
                CHECK (hit >= 5);
                for (const auto& x : ev)   // Vorbereiten: in der zweiten Haelfte des letzten Takts schweigt der Bass
                    if (x.velocity > 0 && x.channel - 1 == kBass && x.sample >= 7 * bar + bar / 2 && x.sample < 8 * bar) CHECK (false);
            }
            else CHECK (hit == 0);
            if (end == EndFade)   // am laengsten bleibt die Ebene, mit der die Szene begonnen hat
            {
                const int e = Generator::autoEntry (s);
                CHECK (lastLayers.size() <= 1 && (lastLayers.empty() || lastLayers.count (kEntryOrder[e][0]) == 1));
                CHECK (lastBar < early);
            }
            if (end == EndOpen) CHECK (lastBar > early);
        }
    }

    // 44) Fahrt von A nach B: der klingende Punkt wandert in 8 Takten nach oben, Ebenen kommen dazu; Hin und zurueck endet bei A
    {
        for (int curve = 0; curve < kNumCurves; ++curve)
        {
            Generator g; g.reset(); EventList list;
            Settings s; s.drive = true; s.driveCurve = curve; s.driveBars = 8; s.x = 0.3f; s.y = 0.1f; s.driveX = 0.8f; s.driveY = 0.9f;
            float lastY = 0.0f, maxY = 0.0f;
            bool arpEarly = false, arpLate = false;
            for (long long pos = 0; pos < 48000LL * 20; pos += 512)
            {
                Transport t; t.playing = true; t.bpm = 120.0; t.sampleRate = 48000.0; t.ppq = (double) pos / 24000.0;
                list.clear();
                g.process (t, s, 512, list);
                for (int i = 0; i < list.size; ++i)
                    if (list.events[(size_t) i].velocity > 0 && list.events[(size_t) i].out == OutArp) (pos < 96000 ? arpEarly : arpLate) = true;
                if (curve != CurveWave) CHECK (g.pointY() >= lastY - 1e-6f);
                lastY = g.pointY(); maxY = std::max (maxY, lastY);
            }
            CHECK (! arpEarly && arpLate && maxY > 0.85f);
            CHECK (curve == CurveWave ? lastY < 0.15f : lastY > 0.85f);
        }
    }

    // 45) Recorded motif returns after a complete intervening phrase.
    {
        auto onsets = [] (int seed, long long fromBar)
        {
            Settings s; s.motif = true; s.seed = seed; s.solo[kGegenstimme] = true; s.y = 0.6f; s.x = 0.3f;
            std::vector<std::pair<long long, int>> o;
            for (const auto& x : run (s, 512, 40.0))
                if (x.velocity > 0 && x.sample >= fromBar * 96000 && x.sample < (fromBar + 2) * 96000) o.push_back ({ x.sample - fromBar * 96000, x.note });
            return o;
        };
        const auto a = onsets (3, 0), a2 = onsets (3, 16);
        CHECK(onsets(3,8).empty());
        CHECK (a.size() >= 3 && a.size() == a2.size());
        for (size_t i = 0; i < a.size(); ++i) CHECK (a[i].first == a2[i].first);
        bool differs = false;
        for (int w = 4; w < 10 && ! differs; ++w) differs = onsets (w, 0) != a;
        CHECK (differs);
    }

    // 46) Mit allem eingeschaltet: unabhaengig von der Blockgroesse, keine Speicheranforderung, nichts haengt
    {
        Settings s; s.scene = true; s.inertia = true; s.motif = true; s.sceneBars = 12; s.ending = EndHard; s.drive = true;
        s.driveFrom = 2; s.driveBars = 4; s.x = 0.2f; s.y = 0.2f; s.driveY = 0.9f; s.z = 0.4f; s.dynamics = true;
        const auto a = run (s, 64, 30.0), b = run (s, 512, 30.0);
        checkBalanced (a);
        CHECK (a.size() == b.size());
        for (size_t i = 0; i < a.size(); ++i) CHECK (a[i].sample == b[i].sample && a[i].note == b[i].note && a[i].velocity == b[i].velocity);
        Generator g; g.reset(); EventList list;
        Transport t; t.playing = true; t.bpm = 120.0; t.sampleRate = 48000.0;
        list.clear(); g.process (t, s, 512, list);
        NoAllocations na;
        for (long long pos = 512; pos < 48000LL * 30; pos += 512)
        {
            t.ppq = (double) pos / 24000.0;
            list.clear();
            g.process (t, s, 512, list);
        }
    }
    // 47) Stich (ab 1.4): immer nur ein Ton je Schlag. Akkord: Grundton in fester Lage; Fest: immer die gewaehlte Taste,
    // auch beim harten Schlussschlag, unabhaengig von Oktave und Tonumfang
    {
        auto stichHits = [] (const Settings& s)
        {
            std::map<long long, std::set<int>> hits;
            for (const auto& e : run (s, 512, 40.0)) if (e.velocity > 0 && e.out == OutStich) hits[e.sample].insert (e.note);
            return hits;
        };
        for (int genre = 0; genre < kNumGenres; ++genre)
        {
            Settings a; a.genre = genre; a.y = 0.9f; a.z = 0.7f;
            const auto chord = stichHits (a);
            CHECK (! chord.empty());
            std::set<int> pcs;
            for (const auto& h : chord) { CHECK (h.second.size() == 1); for (int n : h.second) { CHECK (n >= 50 && n <= 61); pcs.insert (n % 12); } }
            CHECK (pcs.size() >= 2);   // folgt den Akkorden
            Settings f = a; f.stichFixed = true; f.stichNote = 37; f.octave[kAkzent] = 2;
            f.rangeOn[5] = true; f.rangeLo[5] = 60; f.rangeHi[5] = 72;
            const auto fixed = stichHits (f);
            CHECK (fixed.size() == chord.size());
            for (const auto& h : fixed) CHECK (h.second.size() == 1 && *h.second.begin() == 37);
        }
        Settings e; e.scene = true; e.sceneBars = 8; e.ending = EndHard; e.y = 0.9f; e.stichFixed = true; e.stichNote = 41;
        std::set<int> last;
        for (const auto& x : run (e, 512, 18.0)) if (x.velocity > 0 && x.out == OutStich) { if (x.sample >= 8 * 96000) last.insert (x.note); }
        CHECK (last.size() == 1 && *last.begin() == 41);   // Schlussschlag: ein Ton, die gewaehlte Taste
    }

    // 48) Riss (ab 1.4): erst ab 80 % Unruhe, hoch, kurz, im Halbtonabstand, auf dem Kanal der kurzen Flaeche; waechst mit der Unruhe
    {
        auto riss = [] (float z, int& dyads, int& triples, int& ons)
        {
            Settings s; s.y = 0.2f; s.x = 0.3f; s.z = z; s.padPattern = PadHeld; s.solo[kFlaeche] = true;
            std::map<long long, std::set<int>> hits;
            for (const auto& e : run (s, 512, 40.0)) if (e.velocity > 0 && e.out == OutPadShort) hits[e.sample].insert (e.note);
            dyads = triples = ons = 0;
            for (const auto& h : hits)
            {
                ons += (int) h.second.size();
                const int lo = *h.second.begin();
                CHECK (lo >= 84 && lo <= 95);
                CHECK (h.second.count (lo + 1) == 1);
                ++dyads;
                triples += h.second.size() == 3 ? 1 : 0;
            }
        };
        int d0, t0, o0, d1, t1, o1, d2, t2, o2;
        riss (0.75f, d0, t0, o0);
        riss (0.82f, d1, t1, o1);
        riss (1.0f, d2, t2, o2);
        CHECK (d0 == 0 && d1 > 0 && d2 > d1 && t1 == 0 && t2 > 0);
        Settings m; m.z = 1.0f; m.padPattern = PadHeld; m.mute[kFlaeche] = true;
        for (const auto& e : run (m, 512, 20.0)) CHECK (e.out != OutPadShort);   // stumme Flaeche: kein Riss
        Settings b; b.z = 0.95f; b.y = 0.5f;
        const auto ra = run (b, 64, 20.0), rb = run (b, 777, 20.0);
        checkBalanced (ra);
        CHECK (ra.size() == rb.size());
    }

    // 49) Ruhezone (ab 1.5): ganz unten im Feld bleibt der Akkord stehen, auch bei Unruhe; darueber laeuft die Folge
    {
        auto chords = [] (float y, float z, float y2 = -1.0f)
        {
            Settings s; s.y = y; s.x = 0.4f; s.z = z; s.padPattern = PadHeld; s.solo[kFlaeche] = true; s.follow[kFlaeche] = true;
            std::set<std::set<int>> sets;
            std::map<long long, std::set<int>> onsets;
            for (const auto& e : run (s, 512, 60.0)) if (e.velocity > 0 && e.out == OutPadLong) onsets[e.sample].insert (e.note % 12);
            for (const auto& o : onsets) sets.insert (o.second);
            (void) y2;
            return (int) sets.size();
        };
        CHECK (chords (0.0f, 0.0f) == 1);
        CHECK (chords (0.05f, 0.6f) <= 2);   // Unruhe faerbt die Flaeche (Septime), der Akkord bleibt
        CHECK (chords (0.5f, 0.0f) > 1);
        // Auf demselben Wendungsplatz, ohne Sprung: jede Note endet genau einmal
        Settings s; s.y = 0.0f; s.x = 0.4f; s.padPattern = PadHeld; s.follow[kFlaeche] = true;
        checkBalanced (run (s, 512, 40.0));
    }

    // 50) Fahrt (ab 1.7): mitten im Spiel eingeschaltet startet sie am naechsten Takt vom Punkt aus; Ankunft wird gemeldet
    {
        Generator g; g.reset();
        EventList list;
        Settings s; s.x = 0.2f; s.y = 0.2f; s.driveX = 0.8f; s.driveY = 0.9f; s.driveBars = 4; s.driveFrom = 0; s.drive = false;
        const double sr = 48000.0, bpm = 120.0, barSec = 2.0;
        double x4 = -1.0, xEnd = -1.0; bool arrivedEarly = false, arrived = false; int arrivedBar = -1;
        for (long long pos = 0; pos < (long long) (20.0 * barSec * sr); pos += 512)
        {
            const double sec = (double) pos / sr;
            const int bar = (int) (sec / barSec);
            s.drive = bar >= 3;   // in Takt 4 eingeschaltet
            Transport t; t.playing = true; t.bpm = bpm; t.sampleRate = sr; t.ppq = sec * bpm / 60.0;
            list.clear();
            g.process (t, s, 512, list);
            if (bar == 3 && x4 < 0.0) x4 = g.pointX();
            if (bar <= 3) arrivedEarly = arrivedEarly || g.driveArrived();
            if (g.driveArrived() && ! arrived) { arrived = true; arrivedBar = bar; }
            xEnd = g.pointX();
        }
        CHECK (std::fabs (x4 - 0.2f) < 0.01f);     // bis zum Einschalten und noch im selben Takt steht der Punkt auf A
        CHECK (! arrivedEarly);
        CHECK (arrived && arrivedBar >= 7 && arrivedBar <= 9);   // vier Takte nach dem Start im Takt 5
        CHECK (std::fabs (xEnd - 0.8f) < 0.01f);
    }
    // 1.9: every explicitly requested chord colour survives quiet and shy entries.
    for (int type = 0; type < kNumChordTypes; ++type)
        for (bool shy : { false, true })
        for (float unrest : { 0.0f, 0.9f })
    {
        Settings s; s.key = 0; s.y = 0.05f; s.z = unrest; s.custom = true;
        s.customChords[0] = { 0, type, 8 }; s.padPattern = PadHeld; s.solo[kFlaeche] = true;
        s.scene = shy; s.entry = EntryPad;
        std::set<int> pcs;
        for (const auto& e : run (s, 512, 0.5)) if (e.velocity > 0) pcs.insert (e.note % 12);
        for (int i = 0; i < kShapes[type].n; ++i) CHECK (pcs.count (kShapes[type].iv[i] % 12) == 1);
    }
    // Shared channel: muting one owner must not end another owner's held C.
    {
        Settings s; s.key = 0; s.x = 0.7f; s.y = 0.6f; s.custom = true;
        s.customChords[0] = { 0, Maj, 4 }; s.padPattern = PadHeld; s.bassPattern = BassHeld;
        for (int l = 2; l < kNumLayers; ++l) s.mute[l] = true;
        for (auto& c : s.channel) c = 1; s.octave[kBass] = 1;
        Generator g; EventList e; Transport t; t.playing = true;
        g.process (t, s, 480, e);
        s.mute[kFlaeche] = true; t.ppq = 0.02; e.clear(); g.process (t, s, 480, e);
        for (int i = 0; i < e.size; ++i) CHECK (! (e.events[i].note == 60 && e.events[i].velocity == 0));
        t.playing = false; e.clear(); g.process (t, s, 480, e);
        int offs = 0; for (int i = 0; i < e.size; ++i) offs += e.events[i].note == 60 && e.events[i].velocity == 0;
        CHECK (offs == 1);
    }
    // Exact positive legato overlap, not merely event ordering at one sample.
    {
        Settings s; s.y = 0.8f; s.solo[kGegenstimme] = true; s.legato = true;
        std::map<int, long long> held, changed; int transitions = 0;
        for (const auto& e : run (s, 512, 20.0))
        {
            if (e.velocity > 0)
            { for (auto old : held) if (old.first != e.note) changed[old.first] = e.sample; held[e.note] = e.sample; }
            else
            { if (changed.count (e.note)) { CHECK (e.sample - changed[e.note] == 6000); ++transitions; changed.erase (e.note); } held.erase (e.note); }
        }
        CHECK (transitions > 0);
    }
    CHECK (Meter::from (9, 4).len == 36); CHECK (Meter::from (1, 8).len == 2);
    CHECK (Meter::from (16, 1).len == 256); CHECK (Meter::from (16, 2).len == 128); CHECK (Meter::from (1, 16).len == 1);
    // CC remapping immediately sends the newly selected controller; high ranges retain their floor.
    {
        Generator g; EventList e; Settings s; s.dynamics = true; s.ccRange = true;
        for (int k = 0; k < 2; ++k) for (int c = 0; c < 16; ++c) { s.ccLo[k][c] = 100; s.ccHi[k][c] = 127; }
        Transport t; t.playing = true; g.process (t, s, 6000, e);
        s.ccExpression = 21; t.ppq = 0.25; e.clear(); g.process (t, s, 6000, e);
        int found = 0;
        for (int i = 0; i < e.size; ++i) if (e.events[i].type == 1)
        { CHECK (e.events[i].velocity >= 100); found += e.events[i].note == 21; }
        CHECK (found > 0);
        s.scene = true; s.hardness = 0; s.entry = EntryAll; g.reset(); t.ppq = 0; e.clear(); g.process (t, s, 6000, e);
        int silent = 0;
        for (int i = 0; i < e.size; ++i) if (e.events[i].type == 1)
        { if (e.events[i].note == 1) CHECK (e.events[i].velocity >= 100); if (e.events[i].note == 21 && e.events[i].velocity == 0) ++silent; }
        CHECK (silent > 0);
    }
    // A one-value range change must not be swallowed by a two-point CC deadband.
    {
        Settings s; s.dynamics = true; s.ccRange = true; s.y = 1;
        for (int kind = 0; kind < 2; ++kind) for (int c = 0; c < 16; ++c) s.ccLo[kind][c] = s.ccHi[kind][c] = 100;
        Generator g; Transport t; t.playing = true; EventList e; g.process (t, s, 6000, e);
        for (int kind = 0; kind < 2; ++kind) for (int c = 0; c < 16; ++c) s.ccLo[kind][c] = s.ccHi[kind][c] = 101;
        t.ppq = 0.25; e.clear(); g.process (t, s, 6000, e);
        int updates = 0; for (int i = 0; i < e.size; ++i) if (e.events[i].type == 1) { CHECK (e.events[i].velocity == 101); ++updates; }
        CHECK (updates > 0);
    }
    // Every new cue is reachable at its own anchor, has eight bars, and generates a balanced distinct hook.
    CHECK (kNumWendungen == 48 && kNumPopWendungen == 36);
    std::set<std::vector<long long>> signatures;
    for (int i = 27; i < 36; ++i)
    {
        const auto& w = kPopWendungen[i]; CHECK (wendungBars (w) == 8);
        Settings s; s.genre = GenrePopRock; s.x = w.x; s.y = w.y; s.z = w.z; s.variety = 0;
        CHECK (Generator::pick (s, 0) == i);
        s.layerIntensity[kGegenstimme] = 0.5f; s.solo[kGegenstimme] = true;
        const auto notes = run (s, 64, 16.0); checkBalanced (notes);
        std::vector<long long> signature;
        for (const auto& e : notes) if (e.velocity > 0) signature.push_back (e.sample * 128 + e.note);
        CHECK (! signature.empty()); signatures.insert (signature);
        const auto larger = run (s, 777, 16.0); CHECK (notes.size() == larger.size());
        for (size_t j = 0; j < notes.size(); ++j) { CHECK (notes[j].sample == larger[j].sample); CHECK (notes[j].note == larger[j].note); CHECK (notes[j].velocity == larger[j].velocity); }
    }
    CHECK (signatures.size() == 9);
    // Drahtseil's chromatic line is actually voiced A-G#-G-F# above its fixed bass.
    {
        const auto& w = kPopWendungen[31]; Settings s; s.genre = GenrePopRock; s.key = 0;
        s.x = w.x; s.y = w.y; s.z = w.z; s.variety = 0; s.padPattern = PadHeld; s.solo[kFlaeche] = true;
        std::map<long long, int> top;
        for (const auto& e : run (s, 512, 16.0)) if (e.velocity > 0) top[e.sample] = std::max (top[e.sample], e.note);
        CHECK (top.size() == 4); int expected = 81;
        for (const auto& voice : top) { CHECK (voice.second == expected); --expected; }
    }
    // 2.0: retargeting follows the old position at the edit tick, then reaches the new B.
    // All four curves, including an edit on the return leg; restart between ticks and seeks.
    for (int curve = 0; curve < kNumCurves; ++curve)
    {
        Generator g, reference; Settings s; EventList e, ref;
        s.drive = true; s.driveBars = 4; s.driveCurve = curve;
        s.x = 0.2f; s.y = 0.2f; s.driveX = 0.8f; s.driveY = 0.9f;
        Transport t; t.playing = true; t.bpm = 120; t.sampleRate = 48000;
        for (int tick = 0; tick <= 64; ++tick)
        {
            t.ppq = tick * 0.25; e.clear(); ref.clear();
            auto old = s;
            if (tick == 12) { s.driveX = 0.55f; s.driveY = 0.65f; }
            if (tick == 44 && curve == CurveWave) { s.driveX = 0.95f; s.driveY = 0.95f; }
            reference.process (t, old, 6000, ref); g.process (t, s, 6000, e);
            if (tick == 12 || (tick == 44 && curve == CurveWave))
            {
                CHECK (std::abs (g.pointX() - reference.pointX()) < 1e-5f);
                CHECK (std::abs (g.pointY() - reference.pointY()) < 1e-5f);
            }
            reference = g;
            if (tick == 64)
            {
                CHECK (g.driveArrived());
                CHECK (std::abs (g.pointX() - (curve == CurveWave ? 0.2f : 0.55f)) < 1e-5f);
                CHECK (std::abs (g.pointY() - (curve == CurveWave ? 0.2f : 0.65f)) < 1e-5f);
            }
        }
        // No sixteenth occurs in this small block: the completed generation must still be cleared.
        s.drive = false; t.ppq = 16.25; e.clear(); g.process (t, s, 64, e);
        CHECK (! g.driveArrived());
        s.drive = true; ++s.driveGeneration; t.ppq += 64.0 / 24000; e.clear(); g.process (t, s, 64, e);
        CHECK (! g.driveArrived() && g.driveGenerationNow() == s.driveGeneration);
        // DAW jump/loop reconstructs the canonical curve rather than replaying stale retarget history.
        t.ppq = 0; e.clear(); g.process (t, s, 6000, e);
        CHECK (! g.driveArrived()); CHECK (std::abs (g.pointX() - s.x) < 1e-5f);
        t.playing = false; e.clear(); g.process (t, s, 6000, e);
        CHECK (g.sceneBar() == -1);
    }
    // 2.1 routes: endpoints, ordered waypoints, bounded curves and deterministic evaluation.
    {
        DrivePath p;p.count=4;p.points={DrivePoint{.1f,.8f},DrivePoint{.7f,.9f},DrivePoint{.3f,.2f},DrivePoint{.8f,.4f}};
        p.bends[1]={.2f,-.3f};DrivePoint a{.2f,.1f},b{.9f,.9f};
        CHECK(std::abs(p.at(0,a,b).x-a.x)<1e-6f);CHECK(std::abs(p.at(1,a,b).y-b.y)<1e-5f);
        float total=0;for(int j=0;j<=p.count;++j)total+=p.length(j,a,b);
        float distance=0;for(int j=0;j<p.count;++j){distance+=p.length(j,a,b);auto q=p.at(distance/total,a,b);CHECK(std::hypot(q.x-p.points[(size_t)j].x,q.y-p.points[(size_t)j].y)<1e-4f);}
        for(int j=0;j<=1000;++j){auto q=p.at(j/1000.f,a,b);CHECK(q.x>=0&&q.x<=1&&q.y>=0&&q.y<=1);CHECK(q.x==p.at(j/1000.f,a,b).x);}
        Settings route;route.drive=true;route.route=p;route.driveBars=5;route.y=.7f;
        auto small=run(route,64,14),large=run(route,777,14);CHECK(small.size()==large.size());
        for(size_t j=0;j<small.size();++j)CHECK(small[j].sample==large[j].sample&&small[j].note==large[j].note&&small[j].velocity==large[j].velocity);
        checkBalanced(small);
    }
    // 2.1 arbitrary whole-bar lengths end; manual ending is one-shot and survives a seek.
    for(int mode=0;mode<3;++mode)
    {
        for(int length:{5,7,11,17,21}){Settings s;s.sceneBars=length;s.ending=mode;s.y=.7f;auto ev=run(s,512,length*2.+3);for(auto n:ev)if(n.velocity>0)CHECK(n.sample<=(length*2LL)*48000);checkBalanced(ev);}
        Generator g;Settings s;s.y=.7f;s.ending=mode;EventList e;Transport t;t.playing=true;t.bpm=120;t.sampleRate=48000;
        for(int tick=0;tick<96;++tick){t.ppq=tick*.25;s.endRequested=tick==16;e.clear();g.process(t,s,6000,e);if(tick>48){CHECK(g.sceneOver());for(int n=0;n<e.size;++n)CHECK(e.events[(size_t)n].type!=0||e.events[(size_t)n].velocity==0);}}
        t.ppq=0;e.clear();g.process(t,s,6000,e);CHECK(g.sceneOver());for(int n=0;n<e.size;++n)CHECK(e.events[(size_t)n].type!=0||e.events[(size_t)n].velocity==0);
        t.playing=false;e.clear();g.process(t,s,6000,e);t.playing=true;t.ppq=0;e.clear();g.process(t,s,6000,e);CHECK(!g.sceneOver());
    }
    // New dice rolls are pending until a genuine stop/start; they cannot replace the ongoing opening.
    {
        Generator g;Settings s;s.seed=17;EventList e;Transport t;t.playing=true;t.sampleRate=48000;t.bpm=120;
        g.process(t,s,6000,e);CHECK(g.activeSeed()==17);s.seed=99;t.ppq=.25;e.clear();g.process(t,s,6000,e);CHECK(g.activeSeed()==17);
        t.playing=false;e.clear();g.process(t,s,6000,e);t.playing=true;t.ppq=0;e.clear();g.process(t,s,6000,e);CHECK(g.activeSeed()==99);
    }
    // A fixed deadline can shorten a manually requested fade; that completed manual ending stays latched.
    {
        Generator g;Settings s;s.sceneBars=2;s.ending=EndFade;s.y=.7f;Transport t;t.playing=true;t.bpm=120;t.sampleRate=48000;EventList e;
        for(int tick=0;tick<=40;++tick){t.ppq=tick*.25;s.endRequested=tick==16;e.clear();g.process(t,s,6000,e);}CHECK(g.sceneOver());t.ppq=0;e.clear();g.process(t,s,6000,e);CHECK(g.sceneOver());
    }
    // 2.2: every catalog anchor enters the shared harmonic planner, then physical MIDI.
    for (int genre : {GenreScore, GenrePopRock})
        for (int index = 0; index < wendungCount(genre); ++index)
        {
            const auto& w = wendungAt(genre,index);
            Settings s; s.genre=genre; s.x=w.x; s.y=w.y; s.z=w.z; s.variety=0;
            s.padPattern=PadHeld; s.bassPattern=BassHeld;
            Generator g; Transport t; t.playing=true; EventList e;
            { NoAllocations guard; g.process(t,s,512,e); }
            CHECK(!e.overflow && g.plannedHarmonySlots() == 2 * w.n);
            const auto small=run(s,512,16.1), large=run(s,8192,16.1);
            checkBalanced(small); checkBalanced(large); CHECK(small.size()==large.size());
            for(size_t i=0;i<small.size();++i)
            {
                CHECK(small[i].sample==large[i].sample && small[i].midi==large[i].midi);
                CHECK(small[i].note==large[i].note && small[i].velocity==large[i].velocity);
            }
        }
    // Shared core plan invalidation, canonical seek/loop and scene restart; one MIDI channel.
    for(bool passing:{false,true})
    {
        Settings s; s.custom=true; s.customChords[0]={0,Maj7,2};s.customChords[1]={5,Min9,2};
        s.y=passing?.75f:.55f;s.passing=passing;s.padPattern=PadHeld;s.bassPattern=BassHeld;
        s.mute[kArp]=s.mute[kAkzent]=s.mute[kGegenstimme]=true;
        for(auto& ch:s.channel)ch=1;
        s.rangeOn[0]=s.rangeOn[1]=true;s.rangeLo[0]=60;s.rangeHi[0]=83;s.rangeLo[1]=36;s.rangeHi[1]=59;
        Generator g;EventList e;Transport t;t.playing=true;
        std::set<int> sounding;
        auto block=[&](double ppq)
        {
            t.ppq=ppq;e.clear();{NoAllocations guard;g.process(t,s,512,e);}CHECK(!e.overflow);
            for(int i=0;i<e.size;++i)
            {
                const auto& n=e.events[(size_t)i];if(n.type!=0)continue;
                CHECK(n.channel==1);
                if(n.velocity){CHECK(sounding.insert(n.note).second);CHECK((n.note>=s.rangeLo[0]&&n.note<=s.rangeHi[0])||(n.note>=s.rangeLo[1]&&n.note<=s.rangeHi[1]));}
                else CHECK(sounding.erase(n.note)==1);
            }
            return sounding;
        };
        const auto initial=block(0);CHECK(!initial.empty()&&g.plannedHarmonySlots()==4);
        const auto seek=block(12.5);CHECK(!seek.empty());
        CHECK(block(0)==initial);CHECK(block(12.5)==seek);
        const auto approach=block(15.5);CHECK(block(0)==initial);CHECK(block(15.5)==approach);
        // Changed harmonic/register inputs must not reuse the previous cached plan.
        s.customChords[1]={2,Dom7b9,2};s.rangeLo[0]=72;s.rangeHi[0]=95;
        block(0); // Re-enter through a real seek so held notes are reconstructed.
        const auto changed=block(12.5);CHECK(changed!=seek);
        for(int note:changed)CHECK(note<60||note>=72);
        t.playing=false;block(12.5);CHECK(sounding.empty());
        s.seed=93;t.playing=true;block(0);CHECK(g.activeSeed()==93);
        t.playing=false;block(0);CHECK(sounding.empty());
    }
    // Actual MIDI attacks, stored identity and recall, not a seed-derived surrogate.
    {
        Settings s;s.motif=true;s.y=.7f;s.custom=true;s.customChords[0]={0,Maj7,8};
        s.solo[kGegenstimme]=true;s.seed=3;
        auto events=run(s,512,50.);checkBalanced(events);
        const auto large=run(s,8192,50.);CHECK(events.size()==large.size());
        for(size_t i=0;i<events.size();++i)CHECK(events[i].sample==large[i].sample&&events[i].note==large[i].note&&events[i].velocity==large[i].velocity);
        std::vector<std::pair<long long,int>> first,reprise;
        int gap=0;
        for(auto e:events)if(e.velocity>0)
        {
            if(e.sample<2*96000)first.push_back({e.sample,e.note});
            if(e.sample>=8*96000&&e.sample<16*96000)++gap;
            if(e.sample>=16*96000&&e.sample<18*96000)reprise.push_back({e.sample-16*96000,e.note});
        }
        CHECK(first.size()>=2&&first==reprise&&gap==0);
        Generator g;EventList e;Transport t;t.playing=true;
        for(int tick=0;tick<140;++tick){t.ppq=tick*.25;e.clear();g.process(t,s,6000,e);}
        const auto memory=g.rememberedMotif();CHECK(memory.complete&&memory.count==static_cast<int>(first.size()));
        for(int i=0;i<memory.count;++i)CHECK(memory.origin+memory.notes[static_cast<size_t>(i)].interval==first[static_cast<size_t>(i)].second);
        // Changing variation after capture cannot replace the remembered material.
        s.variation=16;t.ppq=64;e.clear();g.process(t,s,6000,e);CHECK(g.rememberedMotif().identity==memory.identity);
        t.ppq=0;e.clear();g.process(t,s,6000,e);CHECK(g.rememberedMotif().identity==memory.identity);
        t.playing=false;e.clear();g.process(t,s,6000,e);t.playing=true;t.ppq=0;e.clear();g.process(t,s,6000,e);
        CHECK(!g.rememberedMotif().complete);
        s.customChords[0].bars=1;
        std::vector<std::pair<long long,int>> shortA,shortReturn;int shortGap=0;
        for(const auto& n:run(s,512,8.))if(n.velocity>0)
        {
            if(n.sample<96000)shortA.push_back({n.sample,n.note});
            if(n.sample>=96000&&n.sample<192000)++shortGap;
            if(n.sample>=192000&&n.sample<288000)shortReturn.push_back({n.sample-192000,n.note});
        }
        CHECK(shortA.size()>=2&&shortA==shortReturn&&shortGap==0);
    }
    // Physical MIDI durations differ on the second return, while attacks/pitches agree.
    {
        Settings s;s.motif=true;s.y=.7f;s.custom=true;s.customChords[0]={0,Maj7,8};s.solo[kGegenstimme]=true;
        const auto events=run(s,512,80.);checkBalanced(events);
        std::map<int,long long> active;
        std::vector<std::tuple<long long,int,long long>> plain,variant;
        for(const auto& e:events)
        {
            if(e.velocity>0)active[e.note]=e.sample;
            else
            {
                auto at=active.at(e.note);active.erase(e.note);
                if(at>=16*96000&&at<18*96000)plain.emplace_back(at-16*96000,e.note,e.sample-at);
                if(at>=32*96000&&at<34*96000)variant.emplace_back(at-32*96000,e.note,e.sample-at);
            }
        }
        CHECK(plain.size()>=2&&plain.size()==variant.size());bool changed=false;
        for(size_t i=0;i<plain.size();++i)
        {
            CHECK(std::get<0>(plain[i])==std::get<0>(variant[i])&&std::get<1>(plain[i])==std::get<1>(variant[i]));
            changed|=std::get<2>(plain[i])!=std::get<2>(variant[i]);
        }
        CHECK(changed);
    }
    // Dialogue uses the actual first question, with disjoint role windows and shared MIDI.
    {
        Settings s;s.motif=true;s.y=.7f;s.custom=true;s.customChords[0]={0,Maj7,8};s.arpFigure=ArpCell;
        s.solo[kArp]=s.solo[kGegenstimme]=true;
        s.rangeOn[kArp]=s.rangeOn[kGegenstimme]=true;
        s.rangeLo[kArp]=s.rangeLo[kGegenstimme]=60;s.rangeHi[kArp]=s.rangeHi[kGegenstimme]=83;
        s.channel[OutArp]=s.channel[OutCounter]=1;
        auto events=run(s,512,20.);checkBalanced(events);
        std::vector<std::pair<long long,int>> question,answer;
        for(auto e:events)if(e.velocity>0)
        {
            CHECK(e.note>=60&&e.note<=83);
            if(e.sample<192000){CHECK(e.out==OutCounter);question.push_back({e.sample,e.note});}
            if(e.sample>=192000&&e.sample<384000){CHECK(e.out==OutArp);answer.push_back({e.sample-192000,e.note});}
        }
        CHECK(question.size()>=3&&answer.size()==3);
        for(size_t i=0;i<answer.size();++i)CHECK(answer[i]==question[i]);
        Generator g;EventList list;Transport t;t.playing=true;
        for(int step=0;step<32;++step){t.ppq=step*.25;list.clear();g.process(t,s,6000,list);}
        auto answerAt=[&](double ppq){t.ppq=ppq;list.clear();g.process(t,s,6000,list);std::vector<int> pitches;
            for(int i=0;i<list.size;++i)if(list.events[static_cast<size_t>(i)].velocity&&list.events[static_cast<size_t>(i)].out==OutArp)pitches.push_back(list.events[static_cast<size_t>(i)].note);return pitches;};
        const auto firstAnswer=answerAt(8);CHECK(!firstAnswer.empty());
        answerAt(0);CHECK(answerAt(8)==firstAnswer);
        t.playing=false;answerAt(8);t.playing=true;answerAt(0);CHECK(!g.rememberedMotif().complete);

        const auto large=run(s,8192,20.);CHECK(events.size()==large.size());
        for(size_t i=0;i<events.size();++i)CHECK(events[i].sample==large[i].sample&&events[i].note==large[i].note&&events[i].velocity==large[i].velocity);
    }
    // Complete adapter catalog, independent articulation targets and fixed-key safety.
    {
        Settings s;auto catalog=outputCatalog(s);CHECK(composition::validOutputs(catalog.data(),kNumOutputs));
        for(int i=0;i<kNumOutputs;++i){CHECK(catalog[static_cast<size_t>(i)].target.output==i);CHECK(!catalog[static_cast<size_t>(i)].externalPatchKnown);}
        CHECK(catalog[OutPadLong].track.style!=catalog[OutPadShort].track.style);
        CHECK(catalog[OutBassLong].track.style!=catalog[OutBassShort].track.style);
        composition::RoleNeed held;held.role=composition::MusicalRole::accompaniment;held.maxDuration=64;
        CHECK(composition::suitable(catalog[OutPadLong].track,held));
        CHECK(!composition::suitable(catalog[OutPadShort].track,held));
        s.stichFixed=true;s.stichNote=41;s.octave[kAkzent]=2;s.rangeOn[5]=true;s.rangeLo[5]=80;s.rangeHi[5]=90;
        catalog=outputCatalog(s);CHECK(composition::validOutputs(catalog.data(),kNumOutputs));
        CHECK(catalog[OutStich].track.instrument.pitch==composition::PitchBehaviour::unknown);
        CHECK(catalog[OutStich].track.addressing==composition::NoteAddressing::fixedTrigger);
        for(int root=0;root<12;++root)CHECK(composition::addressedPitch(catalog[OutStich],root+72)==41);
        composition::RoleNeed melody;CHECK(!composition::suitable(catalog[OutStich].track,melody));
        auto invalid=catalog;invalid[1].target.output=0;CHECK(!composition::validOutputs(invalid.data(),kNumOutputs));
        invalid=catalog;invalid[1].track.id=invalid[0].track.id;CHECK(!composition::validOutputs(invalid.data(),kNumOutputs));
        s.mute[kAkzent]=true;catalog=outputCatalog(s);CHECK(!catalog[OutStich].track.available&&!catalog[OutTupfer].track.available);
        s.mute[kAkzent]=false;s.solo[kBass]=true;catalog=outputCatalog(s);CHECK(catalog[OutBassLong].track.available&&!catalog[OutCounter].track.available);
    }
    return 0;
}
