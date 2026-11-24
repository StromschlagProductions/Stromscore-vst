#include "ScoreEngine.h"
#include <iostream>
#include <set>
#include <map>
#include <array>
#include <iomanip>
#define CHECK(x) do{if(!(x)){std::cerr<<__LINE__<<": "<<#x<<'\n';return 1;}}while(false)
using namespace stromscore;
using namespace stromscore::composition;
int main(int argc,char**)
{
    const bool report=argc>1;
    const std::array<std::array<float,3>,8> positions {{{.20f,.45f,.45f},{.15f,.78f,.75f},{.40f,.30f,.5f},
        {.65f,.23f,.05f},{.80f,.32f,.08f},{.5f,.6f,.2f},{.8f,.78f,.15f},{.30f,.70f,.25f}}};
    CHECK(templatePreferences.size()==84);std::set<WendungId> ids;
    for(const auto& p:templatePreferences){CHECK(ids.insert(p.id).second&&findWendung(p.id));for(float w:p.weights)CHECK(w>=1.f&&w<=1.8f);CHECK(p.weights[0]==1.f);}
    for(int i=0;i<48;++i)CHECK(ids.count(wendungAt(GenreScore,i).id));
    for(int i=0;i<36;++i)for(auto p:{ProfileId::neutral,ProfileId::johnBarry,ProfileId::bernardHerrmann})CHECK(harmonicPreference(p,wendungAt(GenrePopRock,i).id)==1.f);
    if(report)std::cout<<"# Auswahlhäufigkeiten – erste Harmonieprofile\n\n4096 tatsächliche `pick`-Aufrufe pro Profil und Position, Variation 1, Wurf 42, Salt 0–4095, Variety 0,5. Keine Hörqualitätsbewertung.\n\n";
    int totalDifferent=0;
    for(const auto& xyz:positions)
    {
        Settings s;s.x=xyz[0];s.y=xyz[1];s.z=xyz[2];s.variety=.5f;s.seed=42;
        std::array<std::map<int,int>,3> hist;int different=0;std::set<int> eligible;
        const float best=Generator::bestWeight(s),ratio=Generator::keepRatio(s);
        for(int i=0;i<48;++i)if(Generator::weight(wendungAt(GenreScore,i),s)>=ratio*best)eligible.insert(i);
        for(int salt=0;salt<4096;++salt)
        {
            int selected[3];int p=0;
            for(auto profile:{ProfileId::neutral,ProfileId::johnBarry,ProfileId::bernardHerrmann})
            {
                s.profile=profile;const int index=Generator::pick(s,salt);CHECK(index==Generator::pick(s,salt));CHECK(eligible.count(index));
                selected[p]=index;++hist[static_cast<size_t>(p++)][index];
            }
            different+=selected[1]!=selected[2];
        }
        for(const auto& h:hist)CHECK(h.size()==eligible.size()); // No silent exclusions with this draw batch.
        bool relativeDifference=false;float firstRatio=-1.f;
        for(int index:eligible){const auto id=wendungAt(GenreScore,index).id;
            const float r=harmonicPreference(ProfileId::johnBarry,id)/harmonicPreference(ProfileId::bernardHerrmann,id);
            if(firstRatio<0)firstRatio=r;else relativeDifference|=std::abs(firstRatio-r)>1.e-6f;}
        if(relativeDifference)CHECK(different>0&&hist[1]!=hist[2]);
        else CHECK(different==0&&hist[1]==hist[2]); // A common multiplier cannot change a draw.
        totalDifferent+=different;
        // Candidate presentation uses the same XYZ eligibility, ranking by weighted preference.
        int candidates[kMaxWendungen];s.profile=ProfileId::johnBarry;
        const int n=Generator::candidates(s,candidates,kMaxWendungen);CHECK(n==static_cast<int>(eligible.size()));
        for(int i=0;i<n;++i)CHECK(eligible.count(candidates[i]));
        if(report)
        {
            std::cout<<std::setprecision(3)<<"## XYZ "<<xyz[0]<<" / "<<xyz[1]<<" / "<<xyz[2]<<"\n\n";
            std::cout<<"Zugelassene Wendungen: "<<eligible.size()<<". Barry/Herrmann bei gleichem Salt verschieden: "<<different<<"/4096 ("<<std::fixed<<std::setprecision(1)<<100.*different/4096.<<" %).\n\n";
            std::cout<<"| ID | Wendung | Neutral | Barry | Herrmann |\n|---|---|---:|---:|---:|\n";
            for(int index:eligible){const auto& w=wendungAt(GenreScore,index);std::cout<<"| "<<static_cast<unsigned>(w.id)<<" | "<<w.name<<" | "<<hist[0][index]<<" | "<<hist[1][index]<<" | "<<hist[2][index]<<" |\n";}
            if(&xyz!=&positions.back())std::cout<<'\n';
            std::cout<<std::defaultfloat;
        }
    }
    CHECK(totalDifferent>1000);
    int actualDifferent=0;
    for(int variation=1;variation<=16;++variation)
    {
        auto actual=[&](ProfileId profile){Settings s;s.profile=profile;s.variation=variation;s.seed=42;s.x=.2f;s.y=.45f;s.z=.45f;
            Generator g;Transport t;t.playing=true;EventList e;g.process(t,s,6000,e);return g.wendung();};
        actualDifferent+=actual(ProfileId::johnBarry)!=actual(ProfileId::bernardHerrmann);
        CHECK(actual(ProfileId::johnBarry)==actual(ProfileId::johnBarry));
    }
    CHECK(actualDifferent>0);

    // Prove the identity reaches actual engine decisions, including borrowed style for custom chords.
    for(auto profile:{ProfileId::neutral,ProfileId::johnBarry,ProfileId::bernardHerrmann})
    {
        Settings s;s.profile=profile;s.x=.2f;s.y=.45f;s.z=.45f;
        Generator g;Transport transport;transport.playing=true;EventList events;int step=0;
        for(int genre:{GenreScore,GenrePopRock,GenreScore})
        {
            s.genre=genre;transport.ppq=step++*.25;events.clear();g.process(transport,s,6000,events);
            CHECK(g.wendung()==Generator::pick(s,0));
        }
        s.genre=GenreScore;s.custom=true;s.customChords[0]={0,Maj7,8};
        Generator custom;Transport t;t.playing=true;EventList e;custom.process(t,s,6000,e);
        CHECK(custom.wendung()==kCustomWendung&&custom.styleWendung()==Generator::pick(s,0));
    }

    // Variety zero / a single nearest candidate: never force an artist preference out of the XYZ pool.
    for(int i=0;i<48;++i)for(float variety:{0.f,.5f,1.f})
    {
        Settings s;const auto& w=wendungAt(GenreScore,i);s.x=w.x;s.y=w.y;s.z=w.z;s.variety=variety;
        for(auto profile:{ProfileId::johnBarry,ProfileId::bernardHerrmann})for(int salt=0;salt<64;++salt)
        {s.profile=profile;const int selected=Generator::pick(s,salt);CHECK(Generator::weight(wendungAt(GenreScore,selected),s)>=Generator::keepRatio(s)*Generator::bestWeight(s));}
    }
    // Genre switch: preference never affects any Pop/Rock selection, independent of variation/salt.
    for(int genre:{GenreScore,GenrePopRock})for(int i=0;i<wendungCount(genre);++i)
    {
        Settings s;const auto& w=wendungAt(genre,i);s.genre=genre;s.x=w.x;s.y=w.y;s.z=w.z;
        if(genre==GenrePopRock)for(int salt=0;salt<128;++salt)
        {s.profile=ProfileId::neutral;const auto neutral=Generator::pick(s,salt);
            for(auto profile:{ProfileId::johnBarry,ProfileId::bernardHerrmann}){s.profile=profile;CHECK(Generator::pick(s,salt)==neutral);}}
    }
    return 0;
}
