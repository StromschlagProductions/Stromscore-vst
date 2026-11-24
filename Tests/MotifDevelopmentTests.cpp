#include "TestSupport.h"
#include "ScoreEngine.h"
#include <iostream>
using namespace stromscore::composition;
int main()
{
    RememberedMotif source;source.observe(60,0,4);source.observe(64,4,4);source.observe(67,8,8);source.finish();const auto saved=source;
    for(int kind=0;kind<5;++kind)
    {
        MotifFigure f;{NoAllocations guard;f=deriveMotif(source,static_cast<MotifVariation>(kind));}
        CHECK(f.sourceIdentity==source.identity&&f.count>=2&&f.span>0);
        for(int i=0;i<f.count;++i){CHECK(f.notes[i].length>0);if(i+1<f.count)CHECK(f.notes[i].at+f.notes[i].length<=f.notes[i+1].at);}
        auto repeated=deriveMotif(source,static_cast<MotifVariation>(kind));CHECK(f.span==repeated.span);
        CHECK(source.identity==saved.identity&&source.count==saved.count);
        for(int i=0;i<source.count;++i)CHECK(source.notes[i].at==saved.notes[i].at&&source.notes[i].length==saved.notes[i].length&&source.notes[i].interval==saved.notes[i].interval);
    }
    auto rhythm=deriveMotif(source,MotifVariation::rhythm);CHECK(rhythm.notes[2].length==4&&rhythm.span==12);
    auto fragment=deriveMotif(source,MotifVariation::fragment);CHECK(fragment.count==2&&fragment.notes[0].interval==4&&fragment.notes[1].at==4&&fragment.span==12);
    auto sequence=deriveMotif(source,MotifVariation::sequence);CHECK(sequence.count==4&&sequence.notes[2].interval==7&&sequence.notes[3].interval==11&&sequence.notes[2].at==8);
    auto augmented=deriveMotif(source,MotifVariation::augmentation);CHECK(augmented.span==32&&augmented.notes[1].at==8&&augmented.notes[2].length==16);
    source.count=2;CHECK(!deriveMotif(source,MotifVariation::fragment).count);
    CHECK(!deriveMotif(source,MotifVariation::sequence,0).count);
    source.complete=false;CHECK(!deriveMotif(source,MotifVariation::augmentation).count);
    MotifRecurrencePolicy policy;CHECK(valid(policy));policy.sequenceSemitones=0;CHECK(!valid(policy));policy.sequenceSemitones=7;policy.variations[0]=static_cast<MotifVariation>(50);CHECK(!valid(policy));
    // A longer question moves the existing answer window; it cannot answer over augmentation.
    MotifOccurrence q;q.active=true;q.begin=128;q.end=192;MotifUse use;MotifCatalog catalog;
    auto response=planDialogue(use,catalog,q,180,32);CHECK(!response.answer&&response.answerBegin==192&&response.answerEnd==224);
    // Real neutral performance: each realised variant has its own seekable timing,
    // and every return still references the unchanged actually introduced material.
    {
        using namespace stromscore;
        Settings s;s.motif=true;s.scene=false;s.custom=true;s.customChords[0]={0,Maj7,8};s.x=.3f;s.y=.7f;s.z=0;s.key=0;s.seed=3;s.solo[kGegenstimme]=true;
        Generator g;EventList events;Transport t;t.playing=true;
        std::array<MotifOccurrence,5> examples {};RememberedMotif original;
        for(int tick=0;tick<128*16;++tick)
        {
            t.ppq=tick*.25;events.clear();{NoAllocations guard;g.process(t,s,6000,events);}
            const auto& m=g.rememberedMotif();
            if(m.complete){if(!original.complete)original=m;CHECK(m.identity==original.identity);for(int i=0;i<m.count;++i)CHECK(m.notes[i].at==original.notes[i].at&&m.notes[i].length==original.notes[i].length&&m.notes[i].interval==original.notes[i].interval);}
            const auto plan=g.inspectMotifOccurrence(tick,s);
            if(plan.figure.count)examples[static_cast<size_t>(plan.figure.variation)]=plan;
        }
        for(const auto& plan:examples)
        {
            CHECK(plan.active&&plan.figure.sourceIdentity==original.identity);
            const auto& n=plan.figure.notes[0];CHECK(n.length>1);
            for(int repeat=0;repeat<2;++repeat)
            {
                t.ppq=(plan.begin+n.at+1)*.25;events.clear();g.process(t,s,6000,events);bool found=false;
                for(int i=0;i<events.size;++i){const auto e=events.events[i];if(e.out==OutCounter&&e.velocity>0){CHECK(e.note==plan.base+n.interval);found=true;}}
                CHECK(found);
                // Make the next visit a real discontinuity even when looping the same note.
                t.ppq=0;events.clear();g.process(t,s,6000,events);
            }
        }
    }
    std::cout<<"Motif development tests passed\n";
}
