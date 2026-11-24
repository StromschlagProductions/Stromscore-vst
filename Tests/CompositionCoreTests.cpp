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
static constexpr auto T(int64_t n){return stromscore::musicaltime::fromGridStep(n);}
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
        ChordTimeline timeline;timeline.count=4;timeline.begin={100};timeline.end={100+8*ticksPerBar};
        timeline.durations={stromscore::musicaltime::Tick{ticksPerBar},stromscore::musicaltime::Tick{3*ticksPerBar},stromscore::musicaltime::Tick{2*ticksPerBar},stromscore::musicaltime::Tick{2*ticksPerBar}};
        int offset=0;
        for(int i=0;i<4;++i)
        {
            auto p=locateChord(timeline,stromscore::musicaltime::Tick{100+offset});
            CHECK(p.index==i&&p.begin==stromscore::musicaltime::Tick{100+offset});
            CHECK(locateChord(timeline,p.end-stromscore::musicaltime::Tick{1}).index==i);
            offset+=static_cast<int>(timeline.durations[static_cast<size_t>(i)].value);
        }
        timeline.first=2;timeline.held=true;
        CHECK(locateChord(timeline,timeline.end-stromscore::musicaltime::Tick{1}).index==2);
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
            const auto placed=placeTransition(intent,{100},{100+3*bar},{bar},{bar-4});
            CHECK(placed.present&&placed.begin==stromscore::musicaltime::Tick{100+3*bar-4}&&placed.end==stromscore::musicaltime::Tick{100+3*bar});
            CHECK(!placeTransition(intent,{100},{100+bar-1},{bar},{bar-4}).present);
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
    MotifRecurrencePolicy policy;CHECK(valid(policy));
    CHECK(recurrenceSlot(policy,1,.7f,0).eligible&&!recurrenceSlot(policy,2,.7f,0).eligible);
    CHECK(recurrenceSlot(policy,3,.7f,0).ordinal==2&&recurrenceSlot(policy,4,.7f,0).eligible);
    CHECK(!recurrenceSlot(policy,1,.2f,0).eligible&&recurrenceSlot(policy,2,.2f,0).eligible);
    auto invalid=policy;invalid.minimumSilentBars=0;CHECK(!valid(invalid));
    MotifCatalog catalog;MotifUse use;use.observe(60,T(0),T(4),0);use.observe(64,T(6),T(8),0);use.finish(catalog);
    const auto& memory=use.material(catalog);CHECK(memory.complete&&memory.notes[1].interval==4);
    const auto id=memory.identity;use.observe(90,T(4),T(1),3);use.finish(catalog);CHECK(use.material(catalog).identity==id);
    use.clear();CHECK(!use.material(catalog).complete);
    MotifUse variationUse;variationUse.observe(60,T(0),T(9),0);variationUse.observe(64,T(8),T(12),0);variationUse.finish(catalog);
    const auto& variation=variationUse.material(catalog);const auto originalIdentity=variation.identity;
    CHECK(variation.recalledLength(1,false,T(32))==T(12)&&variation.recalledLength(1,true,T(32))==T(6));
    CHECK(variation.recalledLength(0,true,T(32))<=T(8)&&variation.identity==originalIdentity);
    MotifPlacement places[2]={{T(128),60,0},{T(192),60,0}};
    const auto plain=planRecurrence(policy,recurrenceSlot(policy,1,.7f,0),T(128),T(256),T(32),T(16),places,2);
    CHECK(plain.active&&!plain.varied&&plain.begin==T(128));
    const auto changed=planRecurrence(policy,recurrenceSlot(policy,3,.7f,0),T(128),T(256),T(32),T(16),places,2);
    CHECK(changed.active&&changed.varied&&changed.begin==T(128));
    const auto interior=planRecurrence(policy,recurrenceSlot(policy,5,.7f,0),T(128),T(256),T(32),T(16),places,2);
    CHECK(interior.active&&interior.begin==T(192)&&interior.end==T(224));
    auto moreRest=policy;moreRest.minimumSilentBars=4;
    CHECK(planRecurrence(moreRest,recurrenceSlot(moreRest,5,.7f,0),T(128),T(256),T(32),T(16),places,2).begin==T(128));
    auto restrained=policy;restrained.sparseBelow=.8f;
    CHECK(!recurrenceSlot(restrained,1,.7f,0).eligible);
    restrained.unrestEngages=.1f;CHECK(recurrenceSlot(restrained,1,.7f,.2f).eligible);

    CHECK(!planRecurrence(policy,{},T(128),T(256),T(32),T(16),places,2).active);
    MotifUse other;CHECK(other.adopt({variationUse.reference,1,T(128)},catalog));
    CHECK(&other.material(catalog)==&variationUse.material(catalog)&&other.originTime!=variationUse.originTime);
    other.clear();CHECK(variationUse.material(catalog).identity==originalIdentity);
    MotifCatalog questionCatalog;MotifUse question;question.observe(60,T(0),T(4),0);question.observe(64,T(8),T(4),0);question.finish(questionCatalog);
    MotifOccurrence questionOccurrence{true,true,false,T(0),T(32),0,0};
    CHECK(planDialogue(question,questionCatalog,questionOccurrence,T(0),T(32)).reserveResponse);
    CHECK(planDialogue(question,questionCatalog,questionOccurrence,T(32),T(32)).answer);
    CHECK(!planDialogue(question,questionCatalog,{},T(32),T(32)).answer);
    CHECK(!planDialogue(question,questionCatalog,questionOccurrence,T(64),T(32)).reserveResponse);
    {
        MotifCatalog motifs;MotifUse lead;for(int i=0;i<4;++i)lead.observe(60+4*i,T(i*4),T(4),0);
        lead.finish(motifs);PlayingTrack target;target.id={5};target.style=PlayingStyle::sustained;
        target.roles=roleBit(MusicalRole::answer);target.instrument.pitch=PitchBehaviour::pitched;target.instrument.articulations=1;
        auto handoff=[&](bool requested,int epoch,bool leading=false){return planMelodyHandoff(requested,lead,motifs,target,epoch,T(16),T(128),policy,.7f,0,leading);};
        CHECK(!handoff(false,2).active&&!handoff(true,0).active&&!handoff(true,2,true).active);
        const auto plan=handoff(true,2);CHECK(plan.active&&plan.first==1&&plan.count==3&&plan.begin==T(16));
        CHECK(plan.reference.material.value==lead.reference.value);
        CHECK(!handoff(true,3).active&&handoff(true,6).active);
        target.instrument.pitch=PitchBehaviour::noise;CHECK(!handoff(true,2).active);
        target.instrument.pitch=PitchBehaviour::pitched;target.addressing=NoteAddressing::fixedTrigger;CHECK(!handoff(true,2).active);
    }
    PlayingTrack tracks[2];tracks[0].id={71};tracks[0].roles=roleBit(MusicalRole::lead);
    tracks[0].style=PlayingStyle::sustained;tracks[0].instrument.polyphony=2;
    tracks[1].id={12};tracks[1].roles=roleBit(MusicalRole::answer);
    for(auto& track:tracks){track.instrument.pitch=PitchBehaviour::pitched;track.instrument.articulations=1u<<static_cast<unsigned>(track.style);}
    RoleNeed q;q.polyphony=2;RoleNeed a;a.role=MusicalRole::answer;a.style=PlayingStyle::detached;
    CHECK(assignDialogue(tracks,2,q,a).valid);
    CHECK(assignDialogue(tracks,2,q,a).response.value==12);
    std::swap(tracks[0],tracks[1]);CHECK(assignDialogue(tracks,2,q,a).question.value==71);
    for(auto pitch:{PitchBehaviour::noise,PitchBehaviour::unknown})
    {tracks[0].instrument.pitch=pitch;CHECK(!assignDialogue(tracks,2,q,a).valid);}
    tracks[0].instrument.pitch=PitchBehaviour::pitched;
    tracks[0].instrument.maxDuration=2;CHECK(!assignDialogue(tracks,2,q,a).valid);
    tracks[0].instrument.maxDuration=32;tracks[0].style=PlayingStyle::sustained;CHECK(!assignDialogue(tracks,2,q,a).valid);
    tracks[0].style=PlayingStyle::detached;tracks[0].instrument.range={60,72};CHECK(!assignDialogue(tracks,2,q,a).valid);
    a.range={60,72};CHECK(assignDialogue(tracks,2,q,a).valid);
    tracks[1].instrument.polyphony=1;CHECK(!assignDialogue(tracks,2,q,a).valid);
    tracks[1].instrument.polyphony=2;
    tracks[0].addressing=NoteAddressing::fixedTrigger;CHECK(!assignDialogue(tracks,2,q,a).valid);
    tracks[0].addressing=NoteAddressing::pitchedNotes;
    tracks[0].instrument.articulations=0;CHECK(!assignDialogue(tracks,2,q,a).valid);
    tracks[0].instrument.articulations=2;CHECK(assignDialogue(tracks,2,q,a).valid);
    // Two patches/styles for one musical task: a short-only patch cannot sustain.
    tracks[0].style=PlayingStyle::sustained;CHECK(!suitable(tracks[0],q));
    PlayingTrack longPatch;longPatch.id={501};longPatch.roles=roleBit(MusicalRole::accompaniment);
    longPatch.style=PlayingStyle::sustained;longPatch.instrument.pitch=PitchBehaviour::pitched;
    longPatch.instrument.articulations=1;longPatch.instrument.polyphony=6;longPatch.instrument.maxDuration=128;
    RoleNeed chord;chord.role=MusicalRole::accompaniment;chord.polyphony=4;chord.maxDuration=64;
    CHECK(suitable(longPatch,chord));
    auto shortPatch=longPatch;shortPatch.id={502};shortPatch.style=PlayingStyle::detached;
    shortPatch.instrument.articulations=2;shortPatch.instrument.maxDuration=4;
    CHECK(!suitable(shortPatch,chord));
    longPatch.available=false;CHECK(!suitable(longPatch,chord));
    CHECK(planForeground(true,tracks[1]).foreground);
    CHECK(!planForeground(false,tracks[1]).foreground);
    CHECK(!planForeground(true,longPatch).foreground);
    // Nested metrical masks preserve strong groups and never introduce random state.
    for(int groups:{1,3,4,7})
    {
        int previous=0;
        for(float amount:{0.f,.1f,.25f,.45f,.75f,1.f})
        {
            EventDensity density{amount};int count=0;
            for(int g=0;g<groups;++g)count+=density.allows(g,groups);
            CHECK(count>=previous);previous=count;
            CHECK(density.allows(0,groups)==(amount>0));
        }
        CHECK(previous==groups);
    }
    CHECK((EventDensity{.45f}.allows(2,4)&&!EventDensity{.45f}.allows(1,4)));
    // A target-directed free thought follows harmonic-region lengths, with an explicit rest.
    {
        LinePhraseRequest r;r.count=6;r.pitches={60,64,67,71,72,76};r.goalPitchClass=0;r.notes=4;
        for(int duration:{16,32,48,80,128})
        {
            r.end=duration;auto phrase=planLinePhrase(r);CHECK(phrase.valid&&phrase.goal==72);
            CHECK(phrase.arrival==duration-8&&phrase.breath==duration-4);
            CHECK(phrase.notes[static_cast<size_t>(phrase.count-1)].pitch==phrase.goal);
            CHECK(phrase.notes[static_cast<size_t>(phrase.count-1)].end==phrase.breath);
            for(int i=0;i<phrase.count;++i)
            {
                const auto& n=phrase.notes[static_cast<size_t>(i)];CHECK(n.end>n.begin&&n.end<=phrase.breath);
                if(i)CHECK(n.begin>phrase.notes[static_cast<size_t>(i-1)].begin);
            }
        }
        r.initialNeighbour=1;r.end=80;CHECK(planLinePhrase(r).count==5);
        r.legato=false;const auto detached=planLinePhrase(r);
        for(int i=1;i<detached.count;++i)CHECK(detached.notes[static_cast<size_t>(i-1)].end<detached.notes[static_cast<size_t>(i)].begin);
        r.goalPitchClass=9;CHECK(!planLinePhrase(r).valid);
        r.goalPitchClass=0;r.count=2;CHECK(!planLinePhrase(r).valid);
    }
    std::cout << "Composition core tests passed\n";
}
