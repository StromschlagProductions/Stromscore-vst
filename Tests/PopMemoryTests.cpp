#include "TestSupport.h"
#include "ScoreEngine.h"
#include <map>
#include <tuple>
#include <vector>
#include <iostream>
using namespace stromscore;
using E=std::tuple<long long,int,int,int>;
struct Result{std::vector<E> events;composition::RememberedMotif material;long long origin=0;};
Result render(Settings s,int block)
{
    Generator g;EventList list;Result r;
    for(int at=0;at<96000*4;)
    {
        int n=std::min(block,96000*4-at);Transport t;t.playing=true;t.ppq=at/24000.;list.clear();
        {NoAllocations guard;g.process(t,s,n,list);}CHECK(!list.overflow);
        for(int i=0;i<list.size;++i){auto e=list.events[i];if(!e.type&&e.out==OutCounter)r.events.emplace_back(at+e.offset,e.note,e.velocity,e.channel);}
        if(g.rememberedMotif().complete&&!r.material.complete){r.material=g.rememberedMotif();r.origin=g.motifUse(OutCounter).originTick;}
        CHECK(!g.rememberedMotif(OutMelody).complete);at+=n;
    }
    return r;
}
int main()
{
    for(int index=0;index<kNumPopWendungen;++index)for(float y:{kPopWendungen[index].y,.3f,.8f})for(bool legato:{false,true})
    {
        auto w=kPopWendungen[index];Settings s;s.genre=GenrePopRock;s.key=0;s.x=w.x;s.y=y;s.z=w.z;s.legato=legato;s.variety=0;s.solo[kGegenstimme]=true;
        auto a=render(s,512),b=render(s,127),c=render(s,8192);CHECK(a.events==b.events&&a.events==c.events);
        CHECK(a.material.complete&&a.material.count>=2&&a.material.count<=8&&a.material.timeScale==240);
        CHECK(a.material.identity==b.material.identity&&a.material.identity==c.material.identity);
        std::vector<E> replay;
        for(int i=0;i<a.material.count;++i)
        {
            const auto n=composition::replayMotifNote(a.material,i);CHECK(n.valid&&n.length>0);
            long long on=(a.origin+n.at)*25,off=on+n.length*25;
            auto first=std::find_if(a.events.begin(),a.events.end(),[&](const E& e){return std::get<0>(e)==on&&std::get<1>(e)==n.pitch&&std::get<2>(e)==n.velocity;});CHECK(first!=a.events.end());
            auto release=std::find_if(std::next(first),a.events.end(),[&](const E& e){return std::get<1>(e)==n.pitch&&std::get<2>(e)==0;});CHECK(release!=a.events.end()&&std::get<0>(*release)==off);
            replay.emplace_back(on,n.pitch,n.velocity,8);replay.emplace_back(off,n.pitch,0,8);
        }
        // All attacks in the captured cycle are present; interrupted patterns retain initial rests.
        int attacks=0;for(auto e:a.events)if(std::get<2>(e)>0&&std::get<0>(e)>=(a.origin*25)&&std::get<0>(e)<(a.origin+a.material.cycleLength)*25)++attacks;
        CHECK(attacks==a.material.count);
    }
    {
        Settings s;s.genre=GenrePopRock;s.solo[kGegenstimme]=true;s.channel[OutArp]=s.channel[OutCounter];CHECK(!render(s,512).material.complete);
        s.channel[OutArp]=5;s.mute[kGegenstimme]=true;s.solo[kGegenstimme]=false;CHECK(!render(s,512).material.complete);
    }
    {
        Settings s;s.genre=GenrePopRock;s.solo[kGegenstimme]=true;Generator g;EventList es;Transport t;t.playing=true;
        for(int tick=0;tick<70;++tick){t.ppq=tick*.25;es.clear();g.process(t,s,6000,es);}
        auto id=g.rememberedMotif().identity;CHECK(id!=0);
        for(double at:{0.,12.25,0.,9.5}){t.ppq=at;es.clear();g.process(t,s,6000,es);CHECK(g.rememberedMotif().identity==id);CHECK(!g.rememberedMotif(OutMelody).complete);}
        Transport stop;es.clear();g.process(stop,s,512,es);t.ppq=0;g.process(t,s,6000,es);CHECK(!g.rememberedMotif().complete);
        s.genre=GenreScore;g.process(t,s,6000,es);CHECK(g.rememberedMotif().timeScale==1);
    }
    {
        Settings s;s.genre=GenrePopRock;s.solo[kGegenstimme]=true;s.swing=.3f;
        auto r=render(s,127);CHECK(r.material.complete);
        for(int i=0;i<r.material.count;++i)
        {
            auto n=composition::replayMotifNote(r.material,i);
            auto start=std::find_if(r.events.begin(),r.events.end(),[&](const E& e){return std::get<1>(e)==n.pitch&&std::get<2>(e)==n.velocity&&std::llround(std::get<0>(e)/25.)==r.origin+n.at;});CHECK(start!=r.events.end());
            auto off=std::find_if(std::next(start),r.events.end(),[&](const E& e){return std::get<1>(e)==n.pitch&&std::get<2>(e)==0;});CHECK(off!=r.events.end());CHECK(std::llround(std::get<0>(*off)/25.)==r.origin+n.at+n.length);
        }
    }
    std::cout<<"Pop shared memory tests passed\n";
}
