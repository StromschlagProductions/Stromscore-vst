// Offline investigation: the optional friend reads state without altering the running generator.
#include "ScoreEngine.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace stromscore;
using musicaltime::Tick;
#ifdef MOTIF_AUDIT_TRACE
namespace stromscore {
struct MotifAuditAccess
{
    static void material(std::ostream& o,const composition::RememberedMotif& m)
    {
        o<<"{\"id\":\""<<m.identity<<"\",\"complete\":"<<m.complete<<",\"count\":"<<m.count<<",\"origin\":"<<m.origin
         <<",\"vocab\":"<<m.vocabularyId<<",\"cycle\":"<<m.cycleLength.value<<",\"performed\":"<<m.performedTiming<<",\"notes\":[";
        for(int i=0;i<m.count;++i){if(i)o<<',';const auto& n=m.notes[i];o<<'['<<n.at.value<<','<<n.length.value<<','<<n.interval<<','<<n.velocity<<']';}o<<"]}";
    }
    static void plan(std::ostream& o,const Generator::VoiceState::RecurrenceCache& c)
    {
        const auto& p=c.plan;const auto& f=p.figure;
        o<<"{\"epoch\":"<<c.epoch<<",\"identity\":\""<<c.identity<<"\",\"origin\":"<<c.origin.value
         <<",\"active\":"<<p.active<<",\"intro\":"<<p.introduction<<",\"begin\":"<<p.begin.value<<",\"end\":"<<p.end.value
         <<",\"ordinal\":"<<p.ordinal<<",\"base\":"<<p.base<<",\"source\":\""<<f.sourceIdentity<<"\",\"variation\":"<<static_cast<int>(f.variation)
         <<",\"adapted\":"<<f.harmonicallyAdapted<<",\"clipped\":"<<f.durationAdjusted<<",\"realization\":"<<f.harmonicRealization
         <<",\"passing\":"<<f.passingIndex<<",\"span\":"<<f.span.value<<",\"notes\":[";
        for(int i=0;i<f.count;++i){if(i)o<<',';const auto& n=f.notes[i];o<<'['<<n.at.value<<','<<n.length.value<<','<<n.interval<<','<<n.velocity<<']';}o<<"]}";
    }
    static std::string frame(const Generator& g,const Settings& s,int64_t sample,int64_t end,bool detail)
    {
        std::ostringstream o;o<<std::setprecision(9);const auto& w=g.W();
        o<<"{\"sample\":"<<sample<<",\"observed_end\":"<<end<<",\"x\":"<<s.x<<",\"y\":"<<s.y<<",\"z\":"<<s.z
         <<",\"w\":"<<static_cast<uint32_t>(w.id)<<",\"wi\":"<<g.wendung()<<",\"ci\":"<<g.chordInWendung()
         <<",\"root\":"<<g.chordRoot()<<",\"type\":"<<g.chordType()<<",\"still\":"<<g.still<<",\"scene_end\":";
        if(g.sceneEndTime)o<<g.sceneEndTime->value;else o<<"null";
        o<<",\"phrased\":"<<g.phrasedHook(s)<<",\"roles\":[";
        for(int out:{OutMelody,OutCounter})
        {
            if(out==OutCounter)o<<',';const auto& v=g.voice(out);const auto& u=v.motif;const auto& m=u.material(g.motifCatalog);
            o<<"{\"out\":"<<out<<",\"on\":"<<g.on[kOutputLayer[out]]<<",\"ref\":"<<u.reference.value<<",\"intro\":"<<u.introduction
             <<",\"origin_time\":"<<u.originTime.value<<",\"material\":";material(o,m);o<<",\"plan\":";plan(o,v.recurrence);
#ifdef MOTIF_ESTABLISHMENT_DIAGNOSTICS
            o<<",\"reprise\":{\"identity\":\""<<v.reprise.identity<<"\",\"completed\":"<<v.reprise.completed<<",\"begin\":"<<v.reprise.begin.value<<",\"end\":"<<v.reprise.end.value<<",\"established\":";
            if(v.reprise.establishedAt)o<<v.reprise.establishedAt->value;else o<<"null";o<<'}';
#endif
            o<<",\"reservation\":";plan(o,v.reservationRecurrence);
            o<<",\"answer_ref\":"<<v.answer.reference.value<<",\"answer_intro\":"<<v.answer.introduction<<",\"answer_origin\":"<<v.answer.originTime.value
             <<",\"answer_id\":\""<<v.answer.material(g.motifCatalog).identity<<"\",\"capture\":"<<v.capture.active<<'}';
        }
        o<<']';
        if(detail)
        {
            auto copy=g;copy.cur=&s;const auto tick=musicaltime::fromQuarters(sample/28800.);const auto p=copy.locate(tick);
            const auto actual=copy.chordFor(p,kMelodie,s);const auto forecast=copy.motifHarmonyAt(tick,s);
            o<<",\"harmony_now\":{\"actual_root\":"<<actual.root<<",\"actual_type\":"<<actual.type
             <<",\"forecast_root\":"<<forecast.chord.root<<",\"forecast_type\":"<<forecast.chord.type<<",\"forecast_end\":"<<forecast.end.value<<'}';
            const auto source=copy.motifFor(s,p.phrase);
            o<<",\"candidate\":{\"n\":"<<source.n<<",\"at\":[";
            for(int i=0;i<source.n;++i){if(i)o<<',';o<<copy.motifTemplatePosition(source.on[i]).value;}o<<"],\"degrees\":[";
            for(int i=0;i<source.n;++i){if(i)o<<',';o<<source.deg[i];}o<<"]}";
            const auto handoff=copy.playableMelodyHandoff(tick,p,s,true);
            o<<",\"handoff\":{\"active\":"<<handoff.plan.active<<",\"origin\":"<<handoff.origin.value<<",\"begin\":"<<handoff.plan.begin.value
             <<",\"end\":"<<handoff.plan.end.value<<",\"base\":"<<handoff.base<<",\"first\":"<<handoff.plan.first<<",\"count\":"<<handoff.plan.count<<'}';
        }
        o<<'}';return o.str();
    }
    static uint64_t key(const Generator& g)
    {
        uint64_t h=1469598103934665603ull;auto add=[&](int64_t x){h^=static_cast<uint64_t>(x);h*=1099511628211ull;};
        add(g.current);add(g.curChord);add(g.still);
        for(int out:{OutMelody,OutCounter}){const auto& v=g.voice(out);const auto& m=v.motif.material(g.motifCatalog);
            for(int64_t x:{int64_t(m.count),int64_t(m.identity),int64_t(m.complete),v.motif.originTime.value,v.motif.introduction,
                v.recurrence.epoch,int64_t(v.recurrence.plan.active),v.recurrence.plan.begin.value,v.recurrence.plan.end.value,
                v.reservationRecurrence.epoch,int64_t(g.on[kOutputLayer[out]]),int64_t(v.answer.reference.value),v.answer.introduction,int64_t(v.capture.active)})add(x);}
        return h;
    }
};}
#endif
int main(int argc,char** argv)
{
    if(argc!=14&&argc!=15)return 2;
    Settings s;s.genre=std::atoi(argv[1]);s.profile=static_cast<composition::ProfileId>(std::atoi(argv[2]));s.policy=composition::policyForContext(s.profile,s.genre==GenreScore);
    const int path=std::atoi(argv[3]);s.variation=std::atoi(argv[4]);const int roles=std::atoi(argv[5]),motifs=std::atoi(argv[6]),custom=std::atoi(argv[7]);
    s.sceneBars=std::atoi(argv[8]);s.scene=std::atoi(argv[9])!=0;const int bars=std::atoi(argv[10]),block=std::atoi(argv[11]);const bool trace=std::atoi(argv[12])!=0;
    std::string prefix=argv[13];s.key=argc==15?std::atoi(argv[14]):2;s.seed=0;s.inertia=true;s.melody=roles!=2;s.mute[kGegenstimme]=roles==1;s.motif=motifs&1;s.melodyMotif=motifs&2;
    if(roles==3){s.rangeLo[6]=60;s.rangeHi[6]=96;}
    s.legato=s.melodyLegato=true;s.entry=EntryAll;
    const float points[][3]={{.2f,.45f,.4f},{.25f,.85f,.65f},{.8f,.3f,.1f},{.85f,.85f,.3f},{.5f,.9f,.9f},{1,1,1},
        {.5f,.85f,.5f},{.5f,.85f,.5f},{.76f,.69f,.08f},{.88f,.48f,.03f},{.36f,.18f,.06f},{.3f,.65f,.55f}};
    if(path<0||path>=12)return 3;s.x=points[path][0];s.y=points[path][1];s.z=points[path][2];if(path==11)s.meterNum=3;
    if(custom){s.custom=true;s.customChords[0]={s.key,MinMaj7,custom==1?8:4};if(custom==2)s.customChords[1]={(s.key+4)%12,MinMaj7,4};}
    Generator g;Transport t;t.playing=true;t.bpm=100;EventList events;std::ofstream midi(prefix+".csv"),frames;if(trace)frames.open(prefix+".jsonl");
    const int steps=Meter::from(s.meterNum,s.meterDen).len;int64_t at=0;uint64_t old=0;
    for(int step=0;step<bars*steps;++step)
    {
        const double q=step*.25;
        if(path==6||path==7){const double period=path==6?64.:8.;s.x=.5f+.4f*std::sin(q*6.283185307179586/period);
            s.y=.85f+.1f*std::sin(q*6.283185307179586/(period*1.3)+.3);s.z=.4f+.35f*std::sin(q*6.283185307179586/(period*1.7)+.7);}
        for(int offset=0;offset<7200;)
        {
            const int n=std::min(block,7200-offset);t.ppq=at/28800.;events.clear();g.process(t,s,n,events);if(events.overflow)return 4;
            bool melodic=false;for(int i=0;i<events.size;++i){const auto e=events.events[i];midi<<at+e.offset<<','<<int(e.out)<<','<<int(e.channel)<<','<<int(e.note)<<','<<int(e.velocity)<<','<<int(e.type)<<'\n';melodic|=!e.type&&e.out>=OutCounter;}
#ifdef MOTIF_AUDIT_TRACE
            if(trace&&g.wendung()>=0){const auto key=MotifAuditAccess::key(g);const bool detail=melodic||(step%steps==0&&offset==0);
                if(key!=old||detail)frames<<MotifAuditAccess::frame(g,s,at,at+n,detail)<<'\n';old=key;}
#else
            (void)old;(void)melodic;
#endif
            offset+=n;at+=n;
        }
    }
    t.playing=false;events.clear();g.process(t,s,1,events);for(int i=0;i<events.size;++i){const auto e=events.events[i];midi<<at+e.offset<<','<<int(e.out)<<','<<int(e.channel)<<','<<int(e.note)<<','<<int(e.velocity)<<','<<int(e.type)<<'\n';}
}
