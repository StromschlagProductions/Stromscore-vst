#pragma once
#include "WendungId.h"
#include "ChordTypes.generated.h"
#include "ModalContext.h"
#include <array>
namespace stromscore
{
// Renderer limits, not catalog-size limits. Time remains whole bars in this first step.
inline constexpr int kMaxChords=8;
struct Chord {int root;int type;int bars;int bass=-1;};
enum class ChordColoration { flexible, protectedColor };
// Only the flexible strategy changes the authored chord vocabulary.
inline constexpr int coloredChordType(int type,float unrest,ChordColoration strategy)
{
    if(strategy==ChordColoration::protectedColor)return type;
    if(unrest>=.75f&&(type==Min||type==MinMaj7))return MinMaj9;
    if(unrest>=.45f){if(type==Min)return MinMaj7;if(type==Maj)return Maj7;}
    return type;
}
struct TemplateTonality {int center;composition::Mode mode;};
struct HarmonyTemplate
{
    WendungId id;const char* name;float x,y,z;int count;
    std::array<Chord,kMaxChords> chords;
    TemplateTonality tonality;unsigned genres;const char* sourceRef;
    ChordColoration coloration=ChordColoration::flexible;
};
}
