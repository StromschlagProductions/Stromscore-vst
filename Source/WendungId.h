#pragma once
#include <cstdint>
namespace stromscore
{
// Permanent explicit identities: keep IDs with their material when reordering; never reuse retired IDs.
enum class WendungId : uint16_t
{
    invalid=0,
    scoreHalbtonNachbarn=1001, // Halbton-Nachbarn
    scoreGrundtonTeppich=1002, // Grundton-Teppich
    scoreLauern=1003, // Lauern
    scoreTrauer=1004, // Trauer
    scoreAgentenfarbe=1005, // Agentenfarbe
    scoreSeptakkordPaare=1006, // Septakkord-Paare
    scoreSchieferWalzer=1007, // Schiefer Walzer
    scoreUnruhigerSchlaf=1008, // Unruhiger Schlaf
    scoreMollInseln=1009, // Moll-Inseln
    scoreGruselOrchester=1010, // Grusel-Orchester
    scoreGeisterball=1011, // Geisterball
    scoreTerzTreppe=1012, // Terz-Treppe
    scoreTritonusSchock=1013, // Tritonus-Schock
    scoreVerfolgung=1014, // Verfolgung
    scoreAchse=1015, // Achse
    scoreSog=1016, // Sog
    scoreMollMarsch=1017, // Moll-Marsch
    scoreEpischeSpannung=1018, // Epische Spannung
    scoreErmittlung=1019, // Ermittlung
    scoreSequenzerNacht=1020, // Sequenzer-Nacht
    scoreNachtFlachen=1021, // Nacht-Flächen
    scoreSynthGroove=1022, // Synth-Groove
    scoreFunkSpannung=1023, // Funk-Spannung
    scoreFremdeOrte=1024, // Fremde Orte
    scoreWurmloch=1025, // Wurmloch
    scoreQuartenRuf=1026, // Quarten-Ruf
    scoreGeheimnis=1027, // Geheimnis
    scoreQuartenWeite=1028, // Quarten-Weite
    scoreSchneelinien=1029, // Schneelinien
    scoreDorischerSchimmer=1030, // Dorischer Schimmer
    scoreGleiten=1031, // Gleiten
    scoreOffeneQuinten=1032, // Offene Quinten
    scoreBewegterAbschied=1033, // Bewegter Abschied
    scoreSehnsucht=1034, // Sehnsucht
    scoreWeite=1035, // Weite
    scoreErhaben=1036, // Erhaben
    scoreRomantik=1037, // Romantik
    scoreWarme=1038, // Wärme
    scoreLydischesStaunen=1039, // Lydisches Staunen
    scoreTerrassen=1040, // Terrassen
    scoreAbenteuer=1041, // Abenteuer
    scoreTerzverwandtschaft=1042, // Terzverwandtschaft
    scoreHeiter=1043, // Heiter
    scoreWestern=1044, // Western
    scoreErhebung=1045, // Erhebung
    scoreFanfare=1046, // Fanfare
    scoreHeldisch=1047, // Heldisch
    scoreTriumph=1048, // Triumph
    popKalteWelle=2001, // Kalte Welle
    popNeonregen=2002, // Neonregen
    popNachtfahrt=2003, // Nachtfahrt
    popSequenzerFieber=2004, // Sequenzer-Fieber
    popMiamiNacht=2005, // Miami-Nacht
    popKalterKrieg=2006, // Kalter Krieg
    popJagdDurchLA=2007, // Jagd durch L.A.
    popBombast=2008, // Bombast
    popRebellenschrei=2009, // Rebellenschrei
    popKommando=2010, // Kommando
    popGalopp=2011, // Galopp
    popDunklerGlanz=2012, // Dunkler Glanz
    popSynthFunk=2013, // Synth-Funk
    popMosaik=2014, // Mosaik
    popTanzsaal=2015, // Tanzsaal
    popPowerballade=2016, // Powerballade
    popMachtakkorde=2017, // Machtakkorde
    popSunsetStrip=2018, // Sunset Strip
    popSonnenseite=2019, // Sonnenseite
    popStadionhymne=2020, // Stadionhymne
    popFeindkontakt=2021, // Feindkontakt
    popTeufelsgeiger=2022, // Teufelsgeiger
    popVorahnung=2023, // Vorahnung
    popEinsamerPlanet=2024, // Einsamer Planet
    popWeltraumDisco=2025, // Weltraum-Disco
    popSerenade=2026, // Serenade
    popStartfreigabe=2027, // Startfreigabe
    popTanzflachenlicht=2028, // Tanzflächenlicht
    popGegenlicht=2029, // Gegenlicht
    popRuckspiegel=2030, // Rückspiegel
    popStahlpuls=2031, // Stahlpuls
    popDrahtseil=2032, // Drahtseil
    popSequenzmotor=2033, // Sequenzmotor
    popSpiegelpalast=2034, // Spiegelpalast
    popSonntagmorgen=2035, // Sonntagmorgen
    popLichtImFenster=2036, // Licht im Fenster
    custom=65535
};
// Existing study hooks are addressed by material identity, not catalog position.
inline constexpr int popHookPattern(WendungId id)
{
    switch(id)
    {
        case WendungId::popTanzflachenlicht: return 0;
        case WendungId::popGegenlicht: return 1;
        case WendungId::popRuckspiegel: return 2;
        case WendungId::popStahlpuls: return 3;
        case WendungId::popDrahtseil: return 4;
        case WendungId::popSequenzmotor: return 5;
        case WendungId::popSpiegelpalast: return 6;
        case WendungId::popSonntagmorgen: return 7;
        case WendungId::popLichtImFenster: return 8;
        default: return -1;
    }
}
}
