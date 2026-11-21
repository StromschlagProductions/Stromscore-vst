// Regressionstests fuer den Notengenerator (ohne JUCE)
#include "TestSupport.h"
#include "ScoreEngine.h"
#include <vector>
#include <map>
#include <set>
#include <string>

using namespace stromscore;

struct Abs { long long sample; int channel, note, velocity; };

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

// Jede Note endet genau einmal, nie doppelt an, nie Ende ohne Anfang
static void checkBalanced (const std::vector<Abs>& ev)
{
    std::map<std::pair<int, int>, int> open;
    for (const auto& e : ev)
    {
        CHECK (e.channel >= 1 && e.channel <= kNumLayers);
        CHECK (e.note >= 0 && e.note <= 127);
        auto& o = open[std::make_pair (e.channel, e.note)];
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
        s.y = 0.3f; CHECK ((channelsUsed (run (s, 512, 20.0)) == std::set<int> { 1, 2, 3, 5 }));
        s.y = 0.5f; CHECK ((channelsUsed (run (s, 512, 20.0)) == std::set<int> { 1, 2, 3, 4, 5 }));
        s.y = 0.9f; CHECK ((channelsUsed (run (s, 512, 20.0)) == std::set<int> { 1, 2, 3, 4, 5 }));
        s.y = 0.1f; s.z = 0.6f;
        CHECK (channelsUsed (run (s, 512, 20.0)).count (4) == 1);   // Unruhe holt die Farbe auch bei wenig Intensitaet
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

    // 15) Akkordnamen mit deutschen Notennamen
    {
        char buf[32];
        chordName (9, 0, Min, buf, 32);      CHECK (std::string (buf) == "Am");
        chordName (9, 8, Maj7, buf, 32);     CHECK (std::string (buf) == "Fmaj7");
        chordName (0, 11, MinMaj7, buf, 32); CHECK (std::string (buf) == "Hm(maj7)");
        chordName (0, 10, Maj, buf, 32);     CHECK (std::string (buf) == "B");
        chordName (9, 11, Min, buf, 32);     CHECK (std::string (buf) == "Gism");
        chordName (9, 11, Maj, buf, 32);     CHECK (std::string (buf) == "As");
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
        CHECK (maxOpen == 1 && seq.size() >= 32);
        for (size_t i = 8; i < seq.size(); ++i) CHECK (seq[i] == seq[i - 8]);   // gleichbleibende Figur ueber gleichem Akkord
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
    return 0;
}
