#include "TestSupport.h"
#include "ScoreEngine.h"
#ifdef REFERENCE_ENGINE_HEADER
#define stromscore stromscore19
#include REFERENCE_ENGINE_HEADER
#undef stromscore
#endif
#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <string>
#include <numeric>
#include <chrono>

struct E { long long sample; int channel,note,velocity,type; };
using Events = std::vector<E>;
template<class G, class S, class L, class T>
Events render (S s, int blocks, int total, double start = 0)
{
    G g; L l; Events all;
    for (int at = 0; at < total; at += blocks)
    {
        T t; t.playing = true; t.ppq = start + at / 24000.0;
        l.clear(); const int n = std::min (blocks,total-at);
        { NoAllocations guard; g.process (t,s,n,l); }
        CHECK (! l.overflow);
        for (int i=0;i<l.size;++i) {auto e=l.events[(size_t)i];all.push_back({at+e.offset,e.channel,e.note,e.velocity,e.type});}
    }
    T stop; l.clear(); g.process(stop,s,512,l);
    for(int i=0;i<l.size;++i){auto e=l.events[(size_t)i];all.push_back({total,e.channel,e.note,e.velocity,e.type});}
    return all;
}
Events current (stromscore::Settings s,int block,int total,double start=0)
{return render<stromscore::Generator,stromscore::Settings,stromscore::EventList,stromscore::Transport>(s,block,total,start);}
std::set<int> pitches (const Events& events,long long at,int channel=1)
{
    std::set<int> held;
    for(auto e:events) if(e.sample<=at&&e.channel==channel&&e.type==0) {if(e.velocity) held.insert(e.note);else held.erase(e.note);}
    return held;
}
std::set<int> pcs (const std::set<int>& notes) {std::set<int> v;for(int n:notes)v.insert(n%12);return v;}
void balanced (const Events& events)
{
    std::map<std::pair<int,int>,bool> held;
    for(auto e:events)if(e.type==0){auto& h=held[{e.channel,e.note}];CHECK(h != (e.velocity>0));h=e.velocity>0;}
    for(auto h:held)CHECK(!h.second);
}
int displacement (const std::set<int>& a,const std::set<int>& b)
{
    int total=0;for(int n:a){int best=128;for(int m:b)best=std::min(best,std::abs(n-m));total+=best;}
    for(int n:b){int best=128;for(int m:a)best=std::min(best,std::abs(n-m));total+=best;}return total;
}
int retriggers (const Events& ev,long long at,const std::set<int>& common)
{int n=0;for(auto e:ev)if(e.sample==at&&e.channel==1&&e.type==0&&e.velocity&&common.count(e.note))++n;return n;}
void same (const Events& a,const Events& b)
{
    CHECK(a.size()==b.size());for(size_t i=0;i<a.size();++i){CHECK(a[i].sample==b[i].sample);CHECK(a[i].channel==b[i].channel);CHECK(a[i].note==b[i].note);CHECK(a[i].velocity==b[i].velocity);CHECK(a[i].type==b[i].type);}
}
void vlq (std::vector<unsigned char>& out,unsigned int v)
{unsigned char b[4];int n=0;b[n++]=(unsigned char)(v&127);while((v>>=7)!=0)b[n++]=(unsigned char)((v&127)|128);while(n)out.push_back(b[--n]);}
void word (std::ofstream& f,unsigned int v,int n){for(int i=n-1;i>=0;--i)f.put((char)(v>>(8*i)));}
void midi (const std::string& path,const Events& events)
{
    std::ofstream f(path,std::ios::binary);f.write("MThd",4);word(f,6,4);word(f,0,2);word(f,1,2);word(f,960,2);
    std::vector<unsigned char> track={0,255,81,3,7,161,32,0,255,88,4,4,2,24,8};int tick=0;
    for(auto e:events){int next=(int)(e.sample/25);vlq(track,(unsigned)(next-tick));tick=next;track.push_back((unsigned char)((e.type?0xb0:e.velocity?0x90:0x80)+(e.channel-1)));track.push_back((unsigned char)e.note);track.push_back((unsigned char)e.velocity);}
    track.insert(track.end(),{0,255,47,0});f.write("MTrk",4);word(f,(unsigned int)track.size(),4);f.write((char*)track.data(),(std::streamsize)track.size());
}
int main(int argc,char**argv)
{
    using namespace stromscore;
    // Standalone optimizer: complete tensions, genuine inversions, and register-aware spacing.
    voiceleading::ChordVoicing a{4,{60,64,67,71}},b{4,{57,60,64,67}};
    auto v=voiceleading::lead(b,a,48,88);CHECK(v.n==4);
    for(int pc:{9,0,4,7}){bool found=false;for(int i=0;i<v.n;++i)found|=v.notes[i]%12==pc;CHECK(found);}
    int common=0;for(int i=0;i<v.n;++i)common+=voiceleading::contains(a,v.notes[i]);CHECK(common>=3);
    // All qualities, in every key and representative register bounds. No colour can disappear if playable.
    for(int key=0;key<12;++key)for(int type=0;type<kNumChordTypes;++type)for(int low:{36,55,72})for(int width:{11,23})
    {
        Settings s;s.key=key;s.y=.35f;s.custom=true;s.solo[kFlaeche]=true;s.padPattern=PadHeld;
        s.customChords[0]={key,Maj7,1};s.customChords[1]={key,type,1};s.rangeOn[0]=true;s.rangeLo[0]=low;s.rangeHi[0]=low+width;
        auto ev=current(s,512,192000);balanced(ev);auto actual=pcs(pitches(ev,96000));
        for(int i=0;i<kShapes[type].n;++i)CHECK(actual.count((key+kShapes[type].iv[i])%12));
        for(auto e:ev)if(e.type==0&&e.velocity)CHECK(e.note>=low&&e.note<=low+width);
    }
    // Holding the initial pad harmony must not silently simplify a seventh/ninth to a triad.
    for(int type=0;type<kNumChordTypes;++type)
    {
        Settings s;s.key=0;s.y=.35f;s.custom=true;s.follow[kFlaeche]=false;s.padPattern=PadHeld;s.solo[kFlaeche]=true;
        s.customChords[0]={0,type,1};s.customChords[1]={5,Maj,1};auto events=current(s,512,192000);
        std::set<int> wanted;for(int i=0;i<kShapes[type].n;++i)wanted.insert(kShapes[type].iv[i]%12);
        CHECK(pcs(pitches(events,120000))==wanted);balanced(events);
    }
    // Repeated short articulations keep their voicing and remain repeated attacks.
    {
        Settings s;s.custom=true;s.customChords[0]={0,Min9,8};s.padPattern=PadGated;s.y=.7f;s.solo[kFlaeche]=true;
        auto e=current(s,64,48000);balanced(e);std::map<long long,std::set<int>> attacks;
        for(auto x:e)if(x.velocity&&x.type==0)attacks[x.sample].insert(x.note);
        CHECK(attacks.size()>=4);for(auto group:attacks)CHECK(group.second==attacks.begin()->second);
    }
    // Narrow impossible range: stay legal, expose exactly the unavailable pitch classes.
    {
        Generator g;EventList e;Transport t;t.playing=true;Settings s;s.key=0;s.y=.3f;s.custom=true;s.customChords[0]={0,Maj7,8};s.rangeOn[0]=true;s.rangeLo[0]=60;s.rangeHi[0]=64;
        g.process(t,s,512,e);CHECK(g.unavailablePadPitchClasses()==((1u<<7)|(1u<<11)));
    }
    // Stable processing across block sizes, warm resets, loops, and non-chord-boundary chase.
    {
        Settings s;s.custom=true;s.dynamics=true;s.y=.65f;s.z=.3f;s.customChords[0]={0,Maj7,2};s.customChords[1]={9,Min7,2};s.customChords[2]={2,Min9,2};s.customChords[3]={7,Dom7,2};
        auto a1=current(s,64,768000),b1=current(s,4096,768000);same(a1,b1);balanced(a1);
        same(current(s,64,96000,10.3),current(s,777,96000,10.3));
    }
    {
        Settings s;s.key=0;s.custom=true;s.padPattern=PadHeld;s.y=.4f;
        s.customChords[0]={0,Maj7,2};s.customChords[1]={9,Min7,2};s.customChords[2]={2,Min9,2};s.customChords[3]={7,Dom7,2};
        auto full=current(s,512,1800000);
        for(double at:{1.3,10.3,31.3,40.3,65.3})
        {
            auto chased=current(s,512,512,at);
            CHECK(pitches(full,(long long)std::llround(at*24000))==pitches(chased,0));
            CHECK(pitches(full,(long long)std::llround(at*24000),3)==pitches(chased,0,3));
        }
    }
    // Walking approaches the planned next bass octave, not a stale root-position octave.
    {
        Settings s;s.key=0;s.custom=true;s.y=.5f;s.bassPattern=BassWalking;s.solo[kBass]=true;
        s.customChords[0]={0,Maj7,2};s.customChords[1]={9,Min7,2};
        auto ev=current(s,512,384000);auto before=pitches(ev,168000,4),after=pitches(ev,192000,4);
        CHECK(before.size()==1&&after.size()==1);CHECK(std::abs(*before.begin()-*after.begin())==1);
    }
    // Mood switches retain balanced notes and target harmony; timestamped changes are block-size independent.
    {
        auto runMood=[](int block)
        {
            Generator g;EventList list;Events out;Settings s;s.padPattern=PadHeld;s.solo[kFlaeche]=true;s.y=.45f;s.x=.15f;s.z=0;
            for(int at=0;at<384000;)
            {
                int n=std::min(block,384000-at);if(at<192000)n=std::min(n,192000-at);else s.x=.85f;
                Transport t;t.playing=true;t.ppq=at/24000.0;list.clear();g.process(t,s,n,list);
                for(int i=0;i<list.size;++i){auto e=list.events[(size_t)i];out.push_back({at+e.offset,e.channel,e.note,e.velocity,e.type});}
                if(at==192000)
                {
                    std::set<int> expected;auto shape=kShapes[g.chordType()];for(int j=0;j<shape.n;++j)expected.insert((s.key+g.chordRoot()+shape.iv[j])%12);
                    CHECK(pcs(pitches(out,at))==expected);
                }
                at+=n;
            }
            Transport stop;list.clear();g.process(stop,s,512,list);for(int i=0;i<list.size;++i){auto e=list.events[(size_t)i];out.push_back({384000,e.channel,e.note,e.velocity,e.type});}return out;
        };
        auto a=runMood(64),b=runMood(4096);balanced(a);same(a,b);
    }
    // The entire stock vocabulary keeps its complete notes and balanced ownership.
    for(int genre=0;genre<kNumGenres;++genre)for(int index=0;index<wendungCount(genre);++index)
    {
        const auto& w=wendungAt(genre,index);Settings s;s.genre=genre;s.x=w.x;s.y=w.y;s.z=w.z;s.variety=0;s.dynamics=true;
        CHECK(Generator::pick(s,0)==index);
        balanced(current(s,777,768000));
    }
    // Controller values/timestamps are independent of voicing.
#ifdef REFERENCE_ENGINE_HEADER
    {
        Settings s;stromscore19::Settings old;s.custom=old.custom=true;s.y=old.y=.7f;s.dynamics=old.dynamics=true;
        for(int i=0;i<4;++i){s.customChords[i]={i*2,Maj7,2};old.customChords[i]={i*2,Maj7,2};}
        auto aa=current(s,512,768000);auto bb=render<stromscore19::Generator,stromscore19::Settings,stromscore19::EventList,stromscore19::Transport>(old,512,768000);
        Events ca,cb;for(auto e:aa)if(e.type==1)ca.push_back(e);for(auto e:bb)if(e.type==1)cb.push_back(e);
        CHECK(!ca.empty());same(ca,cb);
    }
#endif
    // No history drift: cold chase agrees with continuous playback, including passing dominants.
    for(bool passing:{false,true})
    {
        Settings s;s.key=0;s.custom=true;s.padPattern=PadHeld;s.y=.7f;s.passing=passing;
        s.customChords[0]={0,Maj7,2};s.customChords[1]={9,Min7,2};s.customChords[2]={2,Min9,2};s.customChords[3]={7,Dom7,2};
        auto full=current(s,512,1800000);
        for(double at:{1.3,7.3,10.3,31.3,40.3,65.3})
        {
            auto chased=current(s,512,512,at);
            CHECK(pitches(full,(long long)std::llround(at*24000))==pitches(chased,0));
            CHECK(pitches(full,(long long)std::llround(at*24000),3)==pitches(chased,0,3));
        }
    }
#ifdef REFERENCE_ENGINE_HEADER
    CHECK(argc==2);std::string dir=argv[1];std::ofstream csv(dir+"/comparison.csv");
    csv<<"scenario,engine,chord,pitches,common_pitch_classes,held_common_notes,retriggered_common_notes,bidirectional_movement_semitones\n";
    const char* names[]={"maj7_ii9_V7","minor_line","quartal_sus","chromatic_mediants","slash_bass"};
    const int roots[5][4]={{0,9,2,7},{9,9,9,9},{0,5,10,0},{0,4,8,0},{9,0,5,4}};
    const int types[5][4]={{Maj7,Min7,Min9,Dom7},{Min,MinMaj7,Min7,Min6},{Quartal,Sus4,Add9,Quartal},{Maj,Maj,Maj,Maj},{Min,Maj,Maj7,Dom7}};
    int oldRetriggers=0,newRetriggers=0,oldMove=0,newMove=0;
    for(int scenario=0;scenario<5;++scenario)
    {
        Settings s;stromscore19::Settings old;s.key=old.key=0;s.y=old.y=.4f;s.custom=old.custom=true;s.padPattern=old.padPattern=PadHeld;
        for(int i=0;i<4;++i){s.customChords[i]={roots[scenario][i],types[scenario][i],2};old.customChords[i]={roots[scenario][i],types[scenario][i],2};}
        if(scenario==4){ // explicit bass roots are represented by the stock cue in separate stock tests
            s.genre=old.genre=GenrePopRock;s.custom=old.custom=false;
            s.x=old.x=kPopWendungen[35].x;s.y=old.y=kPopWendungen[35].y;s.z=old.z=kPopWendungen[35].z;
            s.variety=old.variety=0;
        }
        auto dev=current(s,512,768000);auto ref=render<stromscore19::Generator,stromscore19::Settings,stromscore19::EventList,stromscore19::Transport>(old,512,768000);balanced(dev);balanced(ref);
        midi(dir+"/"+names[scenario]+"-v1.9.mid",ref);midi(dir+"/"+names[scenario]+"-development.mid",dev);
        for(int c=0;c<4;++c)
        {
            const long long at=c*192000LL;auto aa=pitches(ref,at),bb=pitches(dev,at);CHECK(pcs(aa)==pcs(bb));
            std::set<int> wanted;for(int i=0;i<kShapes[types[scenario][c]].n;++i)wanted.insert((roots[scenario][c]+kShapes[types[scenario][c]].iv[i])%12);CHECK(pcs(bb)==wanted);
            for(int engine=0;engine<2;++engine)
            {
                const auto& ev=engine?dev:ref;auto now=pitches(ev,at);auto before=c?pitches(ev,at-1):std::set<int>{};std::set<int> commonNotes,commonPcs;
                for(int note:before)if(now.count(note))commonNotes.insert(note);
                for(int pc:pcs(before))if(pcs(now).count(pc))commonPcs.insert(pc);
                int triggers=retriggers(ev,at,commonNotes),held=(int)commonNotes.size()-triggers,movement=c?displacement(before,now):0;
                if(engine){newRetriggers+=triggers;newMove+=movement;}else{oldRetriggers+=triggers;oldMove+=movement;}
                csv<<names[scenario]<<','<<(engine?"development":"v1.9")<<','<<c+1<<",\"";for(int note:now)csv<<note<<' ';csv<<"\","<<commonPcs.size()<<','<<held<<','<<triggers<<','<<movement<<'\n';
            }
        }
        if(scenario==4)
        {
            const int bassPcs[4]={9,7,5,4};
            for(int c=0;c<4;++c) { const auto notes=pitches(dev,c*192000LL,3); CHECK(notes.size()==1); CHECK(*notes.begin()%12==bassPcs[c]); }
        }
        // Arp/accent/counter streams remain byte-for-byte identical for static comparisons.
        Events otherA,otherB;for(auto e:dev)if(e.channel!=1&&e.channel!=2&&e.channel!=3&&e.channel!=4)otherA.push_back(e);
        for(auto e:ref)if(e.channel!=1&&e.channel!=2&&e.channel!=3&&e.channel!=4)otherB.push_back(e);same(otherA,otherB);
    }
    CHECK(newRetriggers<oldRetriggers);CHECK(newMove<=oldMove);
    std::cout<<"Common-note reattacks: "<<oldRetriggers<<" -> "<<newRetriggers<<"; bidirectional displacement: "<<oldMove<<" -> "<<newMove<<" semitones\n";
#else
    (void)argc;(void)argv;
#endif
    {
        std::vector<double> times;
        for(int trial=0;trial<100;++trial)
        {
            Generator g;EventList list;Transport t;t.playing=true;Settings s;s.custom=true;s.y=.8f;s.passing=true;
            for(int i=0;i<8;++i)s.customChords[i]={i,MinMaj9,1};
            auto begin=std::chrono::steady_clock::now();g.process(t,s,64,list);auto finish=std::chrono::steady_clock::now();
            times.push_back(std::chrono::duration<double,std::micro>(finish-begin).count());
        }
        std::sort(times.begin(),times.end());std::cout<<"Cold worst-case plan (16 slots, 64-sample block): p95="<<times[94]<<" us; max="<<times.back()<<" us\n";
    }
    std::cout<<"Voice-leading tests passed\n";
}
