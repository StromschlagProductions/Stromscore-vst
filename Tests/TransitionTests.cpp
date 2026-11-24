#include "TestSupport.h"
#include "ScoreEngine.h"
#include <algorithm>
#include <map>
#include <set>
#include <tuple>
#include <vector>
using namespace stromscore;
using Row=std::tuple<long long,int,int,int,int,int>;
struct Harness
{
    Generator g;EventList e;std::vector<Row> rows;long long at=0;
    void advance(long long end,Settings s,int block=512)
    {
        while(at<end)
        {
            const int n=static_cast<int>(std::min<long long>(block,end-at));Transport t;t.playing=true;t.ppq=static_cast<double>(at)/24000.;
            e.clear();{NoAllocations guard;g.process(t,s,n,e);}CHECK(!e.overflow);
            for(int i=0;i<e.size;++i){auto x=e.events[static_cast<size_t>(i)];rows.emplace_back(at+x.offset,x.out,x.note,x.velocity,x.type,x.channel);}at+=n;
        }
    }
    std::set<int> held(int output)const
    {
        std::set<int> ns;for(const auto& [time,o,n,v,type,ch]:rows)if(o==output&&type==0){if(v)ns.insert(n);else ns.erase(n);}return ns;
    }
    void seek(long long sample,Settings s)
    {
        at=sample;rows.clear();advance(sample+512,s);
    }
};
int main()
{
    using namespace composition;
    // Entry optimisation preserves every colour and bass class, also before high octave offsets.
    for(int root=0;root<12;++root)for(int type=0;type<kNumChordTypes;++type)
    {
        ChordIntent intent;intent.root=root;intent.bassPitchClass=(root+7)%12;intent.padLow=64;
        intent.count=kShapes[type].n;for(int i=0;i<intent.count;++i)intent.intervals[i]=kShapes[type].iv[i];
        const auto a=buildAnchor(intent,{48,90},false);
        HarmonicPlan::Slot target{a.pad,a.bass,a.unavailable};HarmonicEntry previous;
        previous.pad={4,{60,64,67,71}};previous.hasBass=true;previous.bass=31;
        HarmonicPlan::Slot r;{NoAllocations guard;r=leadEntry(target,previous,{48,90},{28,60});}
        CHECK(r.pad.n==a.pad.n);std::multiset<int> before,after;
        for(int i=0;i<r.pad.n;++i){before.insert(a.pad.notes[i]%12);after.insert(r.pad.notes[i]%12);CHECK(r.pad.notes[i]>=48&&r.pad.notes[i]<=90);if(i)CHECK(r.pad.notes[i]>r.pad.notes[i-1]);}
        CHECK(before==after);CHECK((r.bass-a.bass)%12==0);CHECK(r.bass>=28&&r.bass<=60);
        auto negative=target;negative.bass=-13;previous.bass=-14;
        auto nr=leadEntry(negative,previous,{-24,96},{-24,0});CHECK(nr.bass<0&&(nr.bass+13)%12==0);
    }
    // Do not move a jump to the unchanged following chord merely to improve the entry.
    {
        HarmonicPlan::Slot target{{3,{72,76,79}},48,0};
        HarmonicEntry previous;previous.pad={3,{60,64,67}};previous.hasBass=true;previous.bass=36;
        auto following=target;following.bass=60;
        const auto chosen=leadEntry(target,previous,{48,90},{24,60},&following);
        CHECK(chosen.pad.n==target.pad.n);
        for(int i=0;i<target.pad.n;++i)CHECK(chosen.pad.notes[i]==target.pad.notes[i]);
        CHECK(chosen.bass==target.bass);
    }
    // A known actually performed entry is restored on seek/loop, independent of the last heard chord.
    for(int profile=0;profile<3;++profile)
    {
        Settings s;s.scene=false;s.padPattern=PadHeld;s.bassPattern=BassHeld;s.x=.3f;s.y=.65f;s.z=.2f;s.variety=.8f;s.variation=17;
        s.profile=static_cast<ProfileId>(profile);s.mute[kArp]=s.mute[kAkzent]=s.mute[kGegenstimme]=true;
        Harness h;h.advance(8*96000+512,s);auto pad=h.held(OutPadLong),bass=h.held(OutBassLong);CHECK(!pad.empty()&&!bass.empty());
        h.advance(40*96000+512,s);
        for(int repeat=0;repeat<2;++repeat){h.seek(8*96000,s);CHECK(h.held(OutPadLong)==pad);CHECK(h.held(OutBassLong)==bass);h.advance(12*96000,s);}
        h.seek(8*96000+30000,s);CHECK(h.held(OutPadLong)==pad);CHECK(h.held(OutBassLong)==bass);
        h.g.reset();h.rows.clear();h.at=0;h.advance(8*96000+512,s,127);CHECK(h.held(OutPadLong)==pad);CHECK(h.held(OutBassLong)==bass);
    }
    // Muted layers do not contribute a fictional performed chord to the next entry.
    {
        Settings s;s.scene=false;s.padPattern=PadHeld;s.bassPattern=BassHeld;s.x=.3f;s.y=.65f;s.z=.2f;s.variety=.8f;s.variation=17;
        s.mute[kFlaeche]=true;s.mute[kBass]=true;
        Harness a;a.advance(8*96000,s);CHECK(a.held(OutPadLong).empty());
        s.mute[kFlaeche]=false;s.mute[kBass]=false;a.advance(8*96000+512,s);
        Harness b;b.seek(8*96000,s);CHECK(a.held(OutPadLong)==b.held(OutPadLong));CHECK(a.held(OutBassLong)==b.held(OutBassLong));
    }
    // No imagined seed at a cold seek; reset and block sizes are repeatable.
    {
        Settings s;s.scene=false;s.padPattern=PadHeld;s.bassPattern=BassHeld;
        Harness a,b;a.seek(33*96000+30000,s);b.seek(33*96000+30000,s);CHECK(a.rows==b.rows);
    }
    std::cout<<"Wendung entry tests passed\n";
}
