#include "CompositionCore.h"
#include "TestSupport.h"
#include <map>
#include <tuple>
#include <vector>
using namespace stromscore::composition;
using Event = std::tuple<int64_t, int, int, int>;
static std::vector<Event> render (const Plan& p, int block)
{
    Renderer r; CHECK (r.setNextScene (p)); CHECK (r.start().size == 0);
    std::vector<Event> result;
    auto collect = [&] (int64_t at, const Events& out)
    {
        CHECK (out.size <= Events::capacity);
        for (int i = 0; i < out.size; ++i)
        {
            const auto& e = out.items[i]; CHECK (e.offset >= 0 && e.offset < block);
            result.emplace_back (at + e.offset, e.channel, e.pitch, e.velocity);
        }
    };
    for (int64_t at = 0; at < p.duration() + 1; at += block)
    {
        Events out;
        { NoAllocations guard; out = r.process (at, block); }
        collect (at, out);
    }
    CHECK (r.stop().size == 0);
    std::map<std::pair<int,int>, int> notes;
    for (const auto& e : result)
    {
        auto& n = notes[{std::get<1>(e), std::get<2>(e)}];
        n += std::get<3>(e) ? 1 : -1; CHECK (n >= 0 && n <= 1);
    }
    for (const auto& n : notes) CHECK (n.second == 0);
    return result;
}
int main()
{
    Request request;
    CompileResult compiled;
    { NoAllocations guard; compiled = Compiler::compile (request); }
    CHECK (compiled.error == Error::none && compiled.plan.valid());
    CHECK (compiled.plan.size() == 9 && compiled.plan.duration() == 384000);
    const auto baseline = render (compiled.plan, 512);
    CHECK (baseline == render (compiled.plan, 1));
    CHECK (baseline == render (compiled.plan, 8192));
    CHECK (baseline == render (compiled.plan, 1000000));
    // Cmaj7 -> Fmaj7: C/E stay sounding through the boundary, including quiet B.
    int commonAttacks = 0; bool quietSeventh = false;
    for (const auto& e : baseline)
    {
        if (std::get<1>(e) == 1 && std::get<3>(e))
        {
            if (std::get<2>(e) % 12 == 0 || std::get<2>(e) % 12 == 4) ++commonAttacks;
            if (std::get<2>(e) % 12 == 11) quietSeventh = true;
        }
    }
    CHECK (commonAttacks == 2 && quietSeventh);
    // Every required pitch class survives compilation in both sections.
    for (int section = 0; section < 2; ++section)
        for (int degree = 0; degree < request.harmony[section].count; ++degree)
        {
            bool found = false;
            for (int i = 0; i < compiled.plan.size(); ++i)
            {
                const auto& n = compiled.plan.note(i);
                if (n.role == Role::pad && n.begin == section * compiled.plan.duration() / 2
                    && n.pitch % 12 == (request.harmony[section].root + request.harmony[section].intervals[degree]) % 12) found = true;
            }
            CHECK (found);
        }
    auto bad = request; bad.padRange = {60,65};
    auto failed = Compiler::compile(bad);
    CHECK (failed.error == Error::requiredToneUnavailable && ! failed.plan.valid() && failed.plan.size() == 0);
    bad = request; bad.harmony[1].count = 6; CHECK (Compiler::compile(bad).error == Error::invalidHarmony);
    bad = request; bad.harmony[0].intervals[1] = 12; CHECK (Compiler::compile(bad).error == Error::invalidHarmony);
    bad = request; bad.bpm = NAN; CHECK (Compiler::compile(bad).error == Error::invalidClock);
    bad = request; bad.intensity = NAN; CHECK (Compiler::compile(bad).error == Error::invalidIntensity);
    bad = request; bad.bassChannel = 17; CHECK (Compiler::compile(bad).error == Error::invalidChannel);
    bad = request; bad.padRange = {80,60}; CHECK (Compiler::compile(bad).error == Error::invalidRange);
    bad = request; bad.revision = 0; CHECK (Compiler::compile(bad).error == Error::invalidIdentity);
    // A muted part makes no demand for an impossible range.
    bad = request; bad.mutePad = true; bad.padRange = {60,60};
    CHECK (Compiler::compile(bad).plan.size() == 1);
    bad.muteBass = true; const auto empty = Compiler::compile(bad); CHECK (empty.plan.valid());
    CHECK (render(empty.plan,512).empty());
    // Shared ownership: pedal C60 and pad C60 share one physical note.
    auto shared = request; shared.bassRange = {60,60}; shared.bassChannel = 1;
    shared.harmony[1] = {2,4,{0,4,7,11,0}};
    const auto sharedPlan = Compiler::compile(shared); CHECK (sharedPlan.plan.valid());
    int attacks = 0, releases = 0;
    for (const auto& e : render(sharedPlan.plan,8192)) if (std::get<2>(e) == 60)
    {
        if (std::get<3>(e)) ++attacks;
        else { ++releases; CHECK (std::get<0>(e) == sharedPlan.plan.duration()); }
    }
    CHECK (attacks == 1 && releases == 1);
    // Seek and loop use canonical target state, not the last sounding chord.
    Renderer live; CHECK(live.setNextScene(compiled.plan)); live.start();
    live.process(0,512);
    auto second = request; second.configurationId = 2; second.harmony[0].root = 2;
    const auto next = Compiler::compile(second); CHECK(next.plan.valid()); CHECK(live.setNextScene(next.plan));
    CHECK(!live.setNextScene(Plan{}));
    auto seek = live.process(200000,512,true);
    CHECK(seek.size > 0 && live.activeConfiguration() == 1);
    Renderer fresh; fresh.setNextScene(compiled.plan); fresh.start();
    auto canonical = fresh.process(200000,512);
    int ons = 0;
    for(int i=0;i<seek.size;++i) if(seek.items[i].velocity)
    {
        CHECK(ons < canonical.size);
        CHECK(seek.items[i].pitch == canonical.items[ons].pitch);
        CHECK(seek.items[i].channel == canonical.items[ons].channel); ++ons;
    }
    CHECK(ons == canonical.size);
    auto loop = live.process(0,512,true); CHECK(loop.size > 0 && live.activeConfiguration() == 1);
    CHECK(live.start().size > 0 && live.activeConfiguration() == 2);
    CHECK(live.process(0,512).size > 0); CHECK(live.stop().size > 0);
    CHECK(live.stop().size == 0 && live.process(0,512).size == 0);
    // Domain-key calls are stateless: evaluating accents cannot advance harmony RNG.
    const auto key = randomKey(3,1,1,RandomDomain::harmony,9);
    for(uint32_t i=0;i<100;++i) (void)randomKey(3,1,1,RandomDomain::accent,i);
    CHECK(key == randomKey(3,1,1,RandomDomain::harmony,9));
    CHECK(key != randomKey(3,1,2,RandomDomain::harmony,9));
    // Unusual clock, endpoint rounding and maximum voice count.
    auto clock = request; clock.bpm = 137; clock.sampleRate = 44100;
    clock.harmony[0] = {0,5,{0,3,7,10,14}}; clock.harmony[1] = clock.harmony[0];
    auto p = Compiler::compile(clock); CHECK(p.plan.valid() && p.plan.size() == Plan::capacity);
    CHECK(render(p.plan,64) == render(p.plan,1000000));
    // Transposition/register matrix: compile and render with full required harmony.
    for (int root = 0; root < 12; ++root) for (int low : {36,60,84})
    {
        auto variant = request; variant.harmony[0].root = root;
        variant.harmony[1].root = (root + 5) % 12;
        variant.padRange = {low, low + 23};
        auto v = Compiler::compile(variant); CHECK(v.plan.valid());
        for(int i=0;i<v.plan.size();++i) if(v.plan.note(i).role == Role::pad)
            CHECK(v.plan.note(i).pitch >= low && v.plan.note(i).pitch <= low + 23);
        CHECK(render(v.plan,512) == render(v.plan,1000000));
    }
    // Complete transport ledger, including queued changes and invalid input cleanup.
    Renderer transport; transport.setNextScene(compiled.plan);
    int held[16][128] {};
    auto account = [&] (const Events& events)
    {
        for(int i=0;i<events.size;++i)
        {
            const auto& e=events.items[i]; auto& n=held[e.channel-1][e.pitch];
            n += e.velocity ? 1 : -1; CHECK(n >= 0 && n <= 1);
        }
    };
    {
        NoAllocations guard;
        account(transport.start()); account(transport.process(0,512));
        transport.setNextScene(next.plan);
        account(transport.process(200000,1000,true));
        account(transport.process(0,1000000,true));
        account(transport.start()); account(transport.process(0,512));
        account(transport.process(std::numeric_limits<int64_t>::max(),512));
        account(transport.process(0,512)); account(transport.process(-1,512));
        account(transport.stop());
    }
    for(const auto& channel : held) for(int n : channel) CHECK(n == 0);
    // Shared planner accepts prepared octave-relative anchors and explicit protected lines.
    HarmonicRequest hr; hr.count=3;hr.padRange={-12,60};hr.bassRange={-12,24};
    hr.slots[0].pad={3,{-12,-8,-5}};hr.slots[0].bass=0;
    hr.slots[1].enabled=false;
    hr.slots[2].pad={3,{-7,-3,0}};hr.slots[2].bass=5;
    hr.slots[2].preservePad=true;hr.slots[2].unavailable=1u<<11;
    HarmonicPlan hp;{NoAllocations guard;hp=planHarmony(hr);}
    CHECK(hp.valid&&hp.count==3&&hp.slots[1].pad.n==0);
    CHECK(hp.slots[2].pad.notes[0]==-7&&hp.slots[2].unavailable==(1u<<11));
    hr.count=17;CHECK(!planHarmony(hr).valid);hr.count=3;
    hr.slots[0].pad.n=7;CHECK(!planHarmony(hr).valid);
    // Intent -> anchor: colour tones, spread/close voicings and range folding.
    ChordIntent intent;intent.root=0;intent.count=4;intent.intervals={0,4,7,11,0};
    HarmonicSlot anchor;{NoAllocations guard;anchor=buildAnchor(intent,{0,127},false);}
    CHECK(anchor.pad.n==4&&anchor.pad.notes[0]==60&&anchor.pad.notes[3]==83);
    auto narrow=buildAnchor(intent,{60,65},true);CHECK(narrow.unavailable&(1u<<11));
    for(int i=0;i<narrow.pad.n;++i)CHECK(narrow.pad.notes[i]>=60&&narrow.pad.notes[i]<=65);
    intent.voicing=1;auto close=buildAnchor(intent,{0,127},false);
    CHECK(close.pad.notes[3]-close.pad.notes[0]==11);
    intent.count=3;intent.intervals={0,3,7,0,0};intent.protectedLine=true;
    CHECK(buildAnchor(intent,{0,127},false).pad.n==4);
    // Nonuniform durations, exact boundaries, truncated last chord and held harmony.
    for(int ticksPerBar:{10,12,14,16,24})
    {
        ChordTimeline timeline;timeline.count=4;timeline.begin=100;timeline.end=100+8*ticksPerBar;
        timeline.durations={ticksPerBar,3*ticksPerBar,2*ticksPerBar,2*ticksPerBar};
        int offset=0;
        for(int i=0;i<4;++i)
        {
            auto p=locateChord(timeline,100+offset);
            CHECK(p.index==i&&p.begin==100+offset);
            CHECK(locateChord(timeline,p.end-1).index==i);
            offset+=static_cast<int>(timeline.durations[static_cast<size_t>(i)]);
        }
        timeline.first=2;timeline.held=true;
        CHECK(locateChord(timeline,timeline.end-1).index==2);
    }
    // Existing transition strategy: threshold, held harmony and final beat group.
    CHECK(freeTransition(0,true,.599f).kind==TransitionKind::direct);
    CHECK(freeTransition(0,true,.6f,true).kind==TransitionKind::direct);
    CHECK(freeTransition(0,false,1.f).kind==TransitionKind::direct);
    for(int root=0;root<12;++root)
    {
        const auto intent=freeTransition(root,true,.6f);
        CHECK(intent.kind==TransitionKind::passingDominant&&intent.targetRoot==root);
        CHECK(intent.approachRoot==(root+7)%12);
        for(int bar:{10,12,14,16,24})
        {
            const auto placed=placeTransition(intent,100,100+3*bar,bar,bar-4);
            CHECK(placed.present&&placed.begin==100+3*bar-4&&placed.end==100+3*bar);
            CHECK(!placeTransition(intent,100,100+bar-1,bar,bar-4).present);
        }
        for(int key=0;key<12;++key)
        {
            const auto resolution=dominantResolution(intent.approachRoot,true,root,key);
            CHECK(resolution.descendingSeventh==(key+intent.approachRoot+10)%12);
            CHECK(resolution.ascendingThird==(key+intent.approachRoot+4)%12);
            CHECK(dominantResolution(intent.approachRoot,false,root,key).ascendingThird==-1);
            CHECK(dominantResolution(root,true,root,key).descendingSeventh==-1);
        }
    }
    RememberedMotif memory;
    CHECK(!memory.recall(2));memory.observe(60,0,4,0);memory.observe(64,6,8,0);memory.finish();
    CHECK(memory.complete&&memory.notes[1].interval==4&&!memory.recall(1)&&memory.recall(2));
    const auto id=memory.identity;memory.observe(90,4,1,3);memory.finish();CHECK(memory.identity==id);
    memory.clear();CHECK(!memory.complete&&!memory.recall(2));
    RememberedMotif variation;
    variation.observe(60,0,9,0);variation.observe(64,8,12,0);variation.finish();
    const auto originalIdentity=variation.identity;
    CHECK(!variation.varied(2)&&variation.varied(4)&&!variation.varied(6));
    CHECK(variation.recalledLength(1,2,32)==12);
    CHECK(variation.recalledLength(1,4,32)==6);
    CHECK(variation.recalledLength(0,4,32)<=8);
    CHECK(variation.identity==originalIdentity&&variation.notes[1].interval==4);
    for(int section:{4,8,12})for(int i=0;i<variation.count;++i)
    {
        auto length=variation.recalledLength(i,section,32);
        CHECK(length>=1&&variation.notes[static_cast<size_t>(i)].at+length<=32);
        if(i+1<variation.count)CHECK(variation.notes[static_cast<size_t>(i)].at+length<=variation.notes[static_cast<size_t>(i+1)].at);
    }
    std::cout << "Composition core tests passed\n";
}
