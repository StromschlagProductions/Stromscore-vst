#include "TestSupport.h"
#include "ScoreEngine.h"
#include <map>
#include <set>
#include <tuple>
#include <vector>
using namespace stromscore;
using Row=std::tuple<int64_t,int,int,int,int,int>;
struct Render {std::vector<Row> rows;std::map<int,int> ons;std::set<int> bassPitches;};
Settings settings(float y,float z)
{
    Settings s;s.profile=composition::ProfileId::johnBarry;s.policy=composition::policyForContext(s.profile,true);
    s.key=2;s.x=.85f;s.y=y;s.z=z;s.custom=true;s.customChords[0]={0,MinMaj7,8};
    s.mute[kGegenstimme]=true;s.melody=false;return s;
}
Render render(Settings s,int block=512,double bpm=100,int route=0,int bars=16)
{
    Generator g;Transport t;t.playing=true;t.bpm=bpm;EventList e;Render result;std::map<int,int> gates;
    const double spq=48000*60/bpm;const auto barQ=s.meterNum*4./s.meterDen;
    const auto total=std::llround(bars*barQ*spq),segment=total/4;int64_t at=0;
    auto collect=[&]{CHECK(!e.overflow);for(int i=0;i<e.size;++i){const auto n=e.events[i];
        result.rows.emplace_back(at+n.offset,n.out,n.channel,n.note,n.velocity,n.type);if(n.type)continue;
        const int k=n.channel*128+n.note;if(n.velocity){CHECK(!gates[k]);gates[k]=1;++result.ons[n.out];
            if(n.out==OutBassLong||n.out==OutBassShort)result.bassPitches.insert(n.note%12);}
        else{CHECK(gates[k]);gates[k]=0;}}};
    while(at<total)
    {
        const auto part=at/segment,local=at%segment;
        if(route==2&&part==3&&local==0){t.playing=false;e.clear();g.process(t,s,1,e);collect();t.playing=true;}
        t.ppq=route?(part==0?0:part==1?32:part==2?8:0)+local/spq:at/spq;
        const int n=static_cast<int>(std::min<int64_t>({block,total-at,segment-local}));e.clear();{NoAllocations guard;g.process(t,s,n,e);}collect();at+=n;
    }
    t.playing=false;e.clear();g.process(t,s,1,e);collect();for(auto x:gates)CHECK(!x.second);return result;
}
int main()
{
    auto quiet=render(settings(.25f,.15f)),medium=render(settings(.65f,.5f)),driven=render(settings(.95f,.85f)),peak=render(settings(.95f,1));
    CHECK(quiet.ons[OutPadLong]>0&&quiet.ons[OutPadShort]==0&&quiet.ons[OutBassLong]>0&&quiet.ons[OutBassShort]==0);
    CHECK(medium.ons[OutPadShort]>0&&medium.ons[OutBassShort]>0);
    CHECK(driven.ons[OutArp]>medium.ons[OutArp]&&driven.ons[OutBassShort]>medium.ons[OutBassShort]);
    CHECK(peak.ons[OutPadShort]>driven.ons[OutPadShort]&&peak.bassPitches.size()>1);
    auto lowUnrest=render(settings(.95f,0));CHECK(lowUnrest.ons[OutArp]<driven.ons[OutArp]);
    // R26's actual pitch sequence must circle, not merely emit eighteen rising notes.
    for(int variation:{1,3,7})
    {
        auto c=settings(.65f,.55f);c.x=.3f;c.meterNum=3;c.meterDen=4;c.variation=variation;
        c.customChords[0]={0,MinMaj9,8};c.solo[kArp]=true;
        const auto r=render(c,512,100,0,2);std::vector<int> pitches;
        for(auto n:r.rows)if(std::get<1>(n)==OutArp&&std::get<4>(n)>0&&!std::get<5>(n))pitches.push_back(std::get<3>(n));
        CHECK(pitches.size()==18);for(int i=1;i<9;++i)CHECK(pitches[i]==pitches[18-i]);
    }
    // A held patch must not continue behind a newly selected short Auto articulation.
    auto s=settings(.25f,.15f);Generator g;Transport t;t.playing=true;EventList e;std::set<int> longGates;
    for(int step=0;step<32;++step){if(step==4){s.y=.95f;s.z=1;}t.ppq=step*.25;e.clear();g.process(t,s,7200,e);
        for(int i=0;i<e.size;++i){const auto n=e.events[i];if(n.type)continue;
            if(n.out==OutPadLong||n.out==OutBassLong){const int k=n.channel*128+n.note;if(n.velocity)longGates.insert(k);else longGates.erase(k);}}
        if(step>=8)CHECK(longGates.empty());}
    // Canonical bass cells at their real XYZ, without the old artificial layer boost.
    for(int id:{1,2,10,11,17,22,24})
    {
        const auto& r=*std::find_if(std::begin(composition::barry::rhythms),std::end(composition::barry::rhythms),[&](const auto& r){return r.id==id;});
        auto c=settings(r.y,r.z);c.x=r.x;c.meterNum=r.num;c.meterDen=r.den;c.solo[kBass]=true;
        auto played=render(c,512,120,0,r.bars);std::vector<int> actual,expected;
        for(auto row:played.rows)if(std::get<4>(row)>0&&!std::get<5>(row))actual.push_back(static_cast<int>(std::get<0>(row)/6000));
        for(int i=0;i<r.num*16/r.den*r.bars;++i)if(r.bass[i]=='X'||r.bass[i]=='x')expected.push_back(i);
        CHECK(actual==expected);
    }
    // Deterministic musical output, including chase/loop and all supported odd eighth meters.
    for(auto meter:{std::pair<int,int>{4,4},{3,4},{6,8},{3,8},{5,8},{7,8}})
    for(int route:{0,1,2})
    {
        auto c=settings(.95f,1);c.meterNum=meter.first;c.meterDen=meter.second;c.swing=.3f;
        const auto a=render(c,512,100,route);CHECK(render(c,127,100,route).rows==a.rows);CHECK(render(c,8192,100,route).rows==a.rows);
    }
    // Non-integral samples/quarter retain the existing <=1 sample rounding tolerance;
    // event data and 960-PPQ positions must still agree (no scheduler change here).
    for(double bpm:{90.,173.})
    {
        const auto a=render(settings(.95f,.85f),512,bpm),b=render(settings(.95f,.85f),127,bpm);CHECK(a.rows.size()==b.rows.size());
        for(size_t i=0;i<a.rows.size();++i){auto x=a.rows[i],y=b.rows[i];CHECK(std::abs(std::get<0>(x)-std::get<0>(y))<=1);
            CHECK(std::llround(std::get<0>(x)*bpm/(48000*60)*960)==std::llround(std::get<0>(y)*bpm/(48000*60)*960));
            std::get<0>(x)=std::get<0>(y);CHECK(x==y);}
    }
    std::cout<<"Barry accompaniment: long/short balance, energy/unrest, exact real-XYZ bass cells, patch transitions, transport, swing and block sizes passed\n";
}
