#pragma once
#include <array>
#include <cmath>
#include <cstddef>

namespace stromscore::composition
{
// Musical parts, independent of MIDI destination numbers. The free adapter maps its six layers.
enum class TexturePart : size_t { harmony, bass, movement, accents, dialog, melody, count };
struct TexturePolicy
{
    std::array<float,static_cast<size_t>(TexturePart::count)> activityStart {{0.f,0.f,.25f,.25f,.15f,.15f}};
    float accentUnrest=.35f, stichStart=.5f;
    float activityHysteresis=.06f;
    int minimumActiveBars=2;
    float stillEnter=.10f, stillExit=.14f;
    struct ArpeggioTempo
    {
        float quarterBelow=.15f,eighthBelow=.5f;
    } arpeggio;
    float start(TexturePart part)const { return activityStart[static_cast<size_t>(part)]; }
};
struct FreeCompositionPolicy { TexturePolicy texture; };
inline constexpr FreeCompositionPolicy neutralFreePolicy {};
// Artist identities currently provide only initial harmonic preferences; all texture data stay neutral.
enum class ProfileId { neutral=0, johnBarry=1, bernardHerrmann=2 };
struct CompositionProfile
{
    ProfileId id;
    const char* name;
    const FreeCompositionPolicy* policy;
    bool harmonySelectionOnly=false;
};
inline constexpr std::array<CompositionProfile,3> compositionProfiles {{
    {ProfileId::neutral,"Neutral",&neutralFreePolicy},
    {ProfileId::johnBarry,"John Barry",&neutralFreePolicy,true},
    {ProfileId::bernardHerrmann,"Bernard Herrmann",&neutralFreePolicy,true}
}};
inline constexpr const CompositionProfile* findProfile(ProfileId id)
{
    for(const auto& p:compositionProfiles)if(p.id==id)return &p;
    return nullptr;
}
inline constexpr const FreeCompositionPolicy* policyForProfile(ProfileId id)
{const auto* p=findProfile(id);return p?p->policy:nullptr;}
inline bool valid(const TexturePolicy& p)
{
    auto unit=[](float v){return std::isfinite(v)&&v>=0.f&&v<=1.f;};
    for(auto value:p.activityStart)if(!unit(value))return false;
    return unit(p.accentUnrest)&&unit(p.stichStart)&&unit(p.activityHysteresis)
        &&p.minimumActiveBars>=0&&p.minimumActiveBars<=4096
        &&unit(p.stillEnter)&&unit(p.stillExit)&&p.stillEnter<=p.stillExit
        &&unit(p.arpeggio.quarterBelow)&&unit(p.arpeggio.eighthBelow)
        &&p.arpeggio.quarterBelow<=p.arpeggio.eighthBelow;
}
// Auto only: explicit rates and figure-specific sixteenth overrides remain in the adapter.
inline int autoArpeggioTicks(const TexturePolicy& p,float intensity)
{return intensity<p.arpeggio.quarterBelow?4:intensity<p.arpeggio.eighthBelow?2:1;}
}
