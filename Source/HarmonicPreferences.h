#pragma once
#include "CompositionPolicy.h"
#include "WendungId.h"
namespace stromscore::composition
{
// Initial, revisable musical hypotheses supplied by the user, not exclusive authorship claims.
// XYZ/Variety eligibility is evaluated BEFORE these bounded positive preferences.
struct HarmonicPreference { WendungId id;float barry,herrmann; };
inline constexpr std::array<HarmonicPreference,48> scorePreferences {{
    {WendungId::scoreHalbtonNachbarn,1.0f,1.8f}, // 1001: Halbton-Nachbarn
    {WendungId::scoreGrundtonTeppich,1.4f,1.3f}, // 1002: Grundton-Teppich
    {WendungId::scoreLauern,1.3f,1.8f}, // 1003: Lauern
    {WendungId::scoreTrauer,1.2f,1.2f}, // 1004: Trauer
    {WendungId::scoreAgentenfarbe,1.8f,1.3f}, // 1005: Agentenfarbe
    {WendungId::scoreSeptakkordPaare,1.8f,1.0f}, // 1006: Septakkord-Paare
    {WendungId::scoreSchieferWalzer,1.8f,1.2f}, // 1007: Schiefer Walzer
    {WendungId::scoreUnruhigerSchlaf,1.0f,1.8f}, // 1008: Unruhiger Schlaf
    {WendungId::scoreMollInseln,1.2f,1.3f}, // 1009: Moll-Inseln
    {WendungId::scoreGruselOrchester,1.0f,1.5f}, // 1010: Grusel-Orchester
    {WendungId::scoreGeisterball,1.0f,1.4f}, // 1011: Geisterball
    {WendungId::scoreTerzTreppe,1.0f,1.4f}, // 1012: Terz-Treppe
    {WendungId::scoreTritonusSchock,1.0f,1.8f}, // 1013: Tritonus-Schock
    {WendungId::scoreVerfolgung,1.0f,1.3f}, // 1014: Verfolgung
    {WendungId::scoreAchse,1.0f,1.8f}, // 1015: Achse
    {WendungId::scoreSog,1.0f,1.8f}, // 1016: Sog
    {WendungId::scoreMollMarsch,1.8f,1.0f}, // 1017: Moll-Marsch
    {WendungId::scoreEpischeSpannung,1.0f,1.0f}, // 1018: Epische Spannung
    {WendungId::scoreErmittlung,1.0f,1.0f}, // 1019: Ermittlung
    {WendungId::scoreSequenzerNacht,1.4f,1.0f}, // 1020: Sequenzer-Nacht
    {WendungId::scoreNachtFlachen,1.3f,1.0f}, // 1021: Nacht-Flächen
    {WendungId::scoreSynthGroove,1.0f,1.0f}, // 1022: Synth-Groove
    {WendungId::scoreFunkSpannung,1.0f,1.0f}, // 1023: Funk-Spannung
    {WendungId::scoreFremdeOrte,1.0f,1.0f}, // 1024: Fremde Orte
    {WendungId::scoreWurmloch,1.0f,1.5f}, // 1025: Wurmloch
    {WendungId::scoreQuartenRuf,1.0f,1.0f}, // 1026: Quarten-Ruf
    {WendungId::scoreGeheimnis,1.0f,1.8f}, // 1027: Geheimnis
    {WendungId::scoreQuartenWeite,1.0f,1.3f}, // 1028: Quarten-Weite
    {WendungId::scoreSchneelinien,1.2f,1.2f}, // 1029: Schneelinien
    {WendungId::scoreDorischerSchimmer,1.2f,1.0f}, // 1030: Dorischer Schimmer
    {WendungId::scoreGleiten,1.2f,1.8f}, // 1031: Gleiten
    {WendungId::scoreOffeneQuinten,1.0f,1.0f}, // 1032: Offene Quinten
    {WendungId::scoreBewegterAbschied,1.0f,1.0f}, // 1033: Bewegter Abschied
    {WendungId::scoreSehnsucht,1.8f,1.2f}, // 1034: Sehnsucht
    {WendungId::scoreWeite,1.4f,1.3f}, // 1035: Weite
    {WendungId::scoreErhaben,1.0f,1.0f}, // 1036: Erhaben
    {WendungId::scoreRomantik,1.3f,1.0f}, // 1037: Romantik
    {WendungId::scoreWarme,1.8f,1.2f}, // 1038: Wärme
    {WendungId::scoreLydischesStaunen,1.3f,1.0f}, // 1039: Lydisches Staunen
    {WendungId::scoreTerrassen,1.0f,1.0f}, // 1040: Terrassen
    {WendungId::scoreAbenteuer,1.0f,1.0f}, // 1041: Abenteuer
    {WendungId::scoreTerzverwandtschaft,1.0f,1.4f}, // 1042: Terzverwandtschaft
    {WendungId::scoreHeiter,1.0f,1.0f}, // 1043: Heiter
    {WendungId::scoreWestern,1.0f,1.0f}, // 1044: Western
    {WendungId::scoreErhebung,1.0f,1.0f}, // 1045: Erhebung
    {WendungId::scoreFanfare,1.0f,1.4f}, // 1046: Fanfare
    {WendungId::scoreHeldisch,1.0f,1.0f}, // 1047: Heldisch
    {WendungId::scoreTriumph,1.0f,1.0f}, // 1048: Triumph
}};
inline constexpr float harmonicPreference(ProfileId profile,WendungId id)
{
    if(profile==ProfileId::neutral)return 1.f;
    for(const auto& p:scorePreferences)if(p.id==id)
        return profile==ProfileId::johnBarry?p.barry:profile==ProfileId::bernardHerrmann?p.herrmann:1.f;
    return 1.f; // Pop/Rock and non-catalog harmony are deliberately unchanged.
}
}
