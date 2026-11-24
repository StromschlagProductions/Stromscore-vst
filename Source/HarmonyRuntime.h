#pragma once
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
// Stack scratch space scales with validated generated pools, without an arbitrary fixed 64 cap.
inline constexpr int kMaxWendungen=kNumWendungen>kNumPopWendungen?kNumWendungen:kNumPopWendungen;
// Preserve existing diagnostic value, but never collide with a larger generated pool index.
inline constexpr int kCustomWendung=kMaxWendungen<1000?1000:kMaxWendungen;
inline const Wendung* wendungTable(int genre){return genre==GenrePopRock?kPopWendungen.data():kWendungen.data();}
inline int wendungCount(int genre){return genre==GenrePopRock?kNumPopWendungen:kNumWendungen;}
inline const Wendung& wendungAt(int genre,int index){return wendungTable(genre)[std::clamp(index,0,wendungCount(genre)-1)];}
inline int wendungIndex(int genre,WendungId id)
{for(int i=0;i<wendungCount(genre);++i)if(wendungAt(genre,i).id==id)return i;return -1;}
inline const Wendung* findWendung(WendungId id)
{for(int g=0;g<kNumGenres;++g){int index=wendungIndex(g,id);if(index>=0)return &wendungAt(g,index);}return nullptr;}
}
