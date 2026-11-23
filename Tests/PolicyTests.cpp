#include "TestSupport.h"
#include "ScoreEngine.h"
#include <vector>
#include <tuple>
#include <string>
using namespace stromscore;
using Notes=std::vector<std::tuple<long long,int,int,int,int,int>>;
static Notes render(Settings s)
{
    Generator g;Transport t;t.playing=true;EventList events;Notes result;
    for(int tick=0;tick<128;++tick)
    {
        t.ppq=tick*.25;events.clear();g.process(t,s,6000,events);CHECK(!events.overflow);
        for(int i=0;i<events.size;++i){auto e=events.events[static_cast<size_t>(i)];result.emplace_back(tick,e.channel,e.note,e.velocity,e.type,e.out);}
    }
    t.playing=false;events.clear();g.process(t,s,6000,events);
    for(int i=0;i<events.size;++i){auto e=events.events[static_cast<size_t>(i)];result.emplace_back(128,e.channel,e.note,e.velocity,e.type,e.out);}
    return result;
}
static int ons(const Notes& notes,int output)
{int count=0;for(auto e:notes)if(std::get<3>(e)>0&&std::get<4>(e)==0&&std::get<5>(e)==output)++count;return count;}
int main()
{
    using namespace composition;
    CHECK(compositionProfiles.size()==3);
    CHECK(findProfile(ProfileId::neutral)&&std::string(findProfile(ProfileId::neutral)->name)=="Neutral");
    CHECK(findProfile(ProfileId::johnBarry)&&std::string(findProfile(ProfileId::johnBarry)->name)=="John Barry");
    CHECK(findProfile(ProfileId::bernardHerrmann)&&std::string(findProfile(ProfileId::bernardHerrmann)->name)=="Bernard Herrmann");
    CHECK(policyForProfile(ProfileId::neutral)==&neutralFreePolicy);
    CHECK(policyForProfile(ProfileId::johnBarry)==&neutralFreePolicy&&policyForProfile(ProfileId::bernardHerrmann)==&neutralFreePolicy);
    CHECK(findProfile(ProfileId::johnBarry)->harmonySelectionOnly&&findProfile(ProfileId::bernardHerrmann)->harmonySelectionOnly);
    CHECK(!findProfile(static_cast<ProfileId>(99))&&!policyForProfile(static_cast<ProfileId>(99)));

    TexturePolicy p;CHECK(valid(p));CHECK(autoArpeggioTicks(p,0)==4);
    CHECK(autoArpeggioTicks(p,std::nextafter(.15f,0.f))==4&&autoArpeggioTicks(p,.15f)==2);
    CHECK(autoArpeggioTicks(p,std::nextafter(.5f,0.f))==2&&autoArpeggioTicks(p,.5f)==1);
    p.arpeggio.eighthBelow=.1f;CHECK(!valid(p));p={};p.minimumActiveBars=-1;CHECK(!valid(p));
    p={};p.activityStart[0]=NAN;CHECK(!valid(p));
    for(int part=0;part<kNumLayers;++part)
    {
        Settings s;s.melody=true;s.y=.4f;
        CHECK(Generator::levelOn(s,part));s.policy.texture.activityStart[static_cast<size_t>(part)]=.7f;
        CHECK(!Generator::levelOn(s,part));s.layerIntensity[part]=.3f;CHECK(Generator::levelOn(s,part));
    }
    for(int genre:{GenreScore,GenrePopRock})
    {
        Settings s;s.genre=genre;s.solo[kArp]=true;s.y=.6f;s.arpFigure=ArpUp;
        auto neutral=render(s);s.policy=*policyForProfile(ProfileId::neutral);CHECK(render(s)==neutral);
        s.policy.texture.arpeggio={.7f,.8f};CHECK(ons(neutral,OutArp)==4*ons(render(s),OutArp));
        for(int rate:{RateQuarter,RateEighth,RateSixteenth})
        {s.arpRate=rate;auto slow=render(s);s.policy={};CHECK(render(s)==slow);s.policy.texture.arpeggio={.7f,.8f};}
        s.arpRate=RateAuto;
        for(int figure:{ArpGlitter,ArpSid})
        {s.arpFigure=figure;auto forced=render(s);s.policy={};CHECK(render(s)==forced);s.policy.texture.arpeggio={.7f,.8f};}
        s.arpFigure=ArpUp;s.solo[kArp]=false;s.mute[kArp]=true;CHECK(ons(render(s),OutArp)==0);
        s.mute[kArp]=false;s.solo[kBass]=true;CHECK(ons(render(s),OutArp)==0);
        s.solo[kBass]=false;s.solo[kArp]=true;s.policy={};s.y=.2f;CHECK(ons(render(s),OutArp)==0);
        s.policy.texture.activityStart[static_cast<size_t>(TexturePart::movement)]=.1f;CHECK(ons(render(s),OutArp)>0);
    }
    // Actual bar-boundary deactivation, with independently configurable hysteresis and minimum hold.
    auto activeAfter=[&](int hold,float hysteresis,int tickEnd)
    {
        Settings s;s.inertia=true;s.y=.6f;s.solo[kArp]=true;
        s.policy.texture.minimumActiveBars=hold;s.policy.texture.activityHysteresis=hysteresis;
        Generator g;Transport t;t.playing=true;EventList e;
        for(int tick=0;tick<=tickEnd;++tick){if(tick)s.y=.1f;t.ppq=tick*.25;e.clear();g.process(t,s,6000,e);}
        return g.layerPlaying(kArp);
    };
    CHECK(activeAfter(2,.06f,16)&&!activeAfter(1,.06f,16));
    CHECK(!activeAfter(2,.06f,32)&&activeAfter(2,.2f,32));
    Settings accent;accent.solo[kAkzent]=true;accent.y=0;accent.z=.4f;
    CHECK(!render(accent).empty());accent.policy.texture.accentUnrest=.9f;CHECK(render(accent).empty());
    accent.y=.7f;accent.z=0;accent.policy={};CHECK(ons(render(accent),OutStich)>0);
    accent.policy.texture.stichStart=.9f;CHECK(ons(render(accent),OutStich)==0);
    Settings harmony;harmony.custom=true;harmony.customChords[0]={0,Maj,2};harmony.customChords[1]={5,Maj,2};
    harmony.y=.5f;harmony.solo[kBass]=true;harmony.bassPattern=BassHeld;
    auto moving=render(harmony);harmony.policy.texture.stillEnter=.8f;harmony.policy.texture.stillExit=.9f;
    CHECK(render(harmony)!=moving);
    for(auto e:render(harmony))if(std::get<3>(e)>0)CHECK(std::get<2>(e)%12==0);
    harmony.policy.texture.stillExit=.2f;CHECK(render(harmony)==moving); // Invalid policy falls back to neutral.
    auto resumes=[&](float exit)
    {
        Settings s;s.custom=true;s.customChords[0]={0,Maj,2};s.customChords[1]={5,Maj,2};
        s.solo[kBass]=true;s.bassPattern=BassHeld;s.policy.texture.stillExit=exit;
        Generator g;Transport t;t.playing=true;EventList e;bool fifth=false;
        for(int tick=0;tick<128;++tick){s.y=tick<16?.05f:.12f;t.ppq=tick*.25;e.clear();g.process(t,s,6000,e);
            for(int i=0;i<e.size;++i){auto n=e.events[static_cast<size_t>(i)];if(n.type==0&&n.velocity>0&&n.note%12==5)fifth=true;}}
        return fifth;
    };
    CHECK(!resumes(.14f)&&resumes(.11f));
    return 0;
}
