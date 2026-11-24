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
struct TemplateTonality {int center;composition::Mode mode;};
struct HarmonyTemplate
{
    WendungId id;const char* name;float x,y,z;int count;
    std::array<Chord,kMaxChords> chords;
    TemplateTonality tonality;unsigned genres;const char* sourceRef;
};
}
