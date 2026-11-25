#pragma once
#include "ProfileIdentity.generated.h"
#include "HarmonyCatalog.generated.h"
#include "HarmonyStrategies.generated.h"
#include <algorithm>
namespace stromscore
{
// Read-only playback projection joining harmonic facts with an independent default strategy.
// Existing renderers keep this compact access shape; it is never a second authoring catalog.
struct Wendung
{
    const char* name;float x,y,z;int n;Chord ch[kMaxChords];
    int arp[2],bass[2],pad;WendungId id=WendungId::custom;
    ChordColoration coloration=ChordColoration::flexible;
};
inline constexpr Wendung playbackTemplate(int index)
{
    const auto& h=harmonyTemplates[index];const auto& recipe=defaultArrangements[index];
    Wendung w{};w.name=h.name;w.x=h.x;w.y=h.y;w.z=h.z;w.n=h.count;w.id=h.id;w.coloration=h.coloration;
    for(int i=0;i<h.count;++i)w.ch[i]=h.chords[static_cast<size_t>(i)];
    for(int i=0;i<2;++i){w.arp[i]=recipe.arp[i];w.bass[i]=recipe.bass[i];}w.pad=recipe.pad;return w;
}
template<size_t N> inline constexpr std::array<Wendung,N> playbackPool(const std::array<int,N>& indices)
{
    std::array<Wendung,N> result{};for(size_t i=0;i<N;++i)result[i]=playbackTemplate(indices[i]);return result;
}
inline constexpr auto kWendungen=playbackPool(kWendungenIndices);
inline constexpr auto kPopWendungen=playbackPool(kPopWendungenIndices);
inline constexpr int kNumWendungen=static_cast<int>(kWendungen.size());
inline constexpr int kNumPopWendungen=static_cast<int>(kPopWendungen.size());
}
#include "HarmonyProfilePools.generated.h"
namespace stromscore
{
// Bounded scratch follows the largest validated selection view.
inline constexpr int kMaxWendungen=std::max({kNumWendungen,kNumPopWendungen,profilePoolCapacity});
inline constexpr int kCustomWendung=kMaxWendungen<1000?1000:kMaxWendungen;
inline const Wendung* wendungTable(int genre,composition::ProfileId profile=composition::ProfileId::neutral)
{return genre==GenrePopRock?kPopWendungen.data():scoreProfileTable(profile);}
inline int wendungCount(int genre,composition::ProfileId profile=composition::ProfileId::neutral)
{return genre==GenrePopRock?kNumPopWendungen:scoreProfileCount(profile);}
inline const Wendung& wendungAt(int genre,int index,composition::ProfileId profile=composition::ProfileId::neutral)
{return wendungTable(genre,profile)[std::clamp(index,0,wendungCount(genre,profile)-1)];}
inline int wendungIndex(int genre,WendungId id,composition::ProfileId profile=composition::ProfileId::neutral)
{for(int i=0;i<wendungCount(genre,profile);++i)if(wendungAt(genre,i,profile).id==id)return i;return -1;}
inline const Wendung* findWendung(WendungId id)
{for(const auto& p:composition::profileIdentities)for(int g=0;g<kNumGenres;++g){int index=wendungIndex(g,id,p.id);if(index>=0)return &wendungAt(g,index,p.id);}return nullptr;}
}
