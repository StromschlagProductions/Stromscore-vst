#include "ScoreEngine.h"
#include <cstdlib>
#include <iostream>
#include <set>
#include <string>
#define CHECK(x) do{if(!(x)){std::cerr<<__LINE__<<": "<<#x<<'\n';return 1;}}while(false)
int main()
{
    using namespace stromscore;
    struct Expected { WendungId id;unsigned number;const char* name; };
    // Frozen ID/name contract, independent of future table order.
    const Expected expected[]={
        {WendungId::scoreHalbtonNachbarn,1001,"Halbton-Nachbarn"},
        {WendungId::scoreGrundtonTeppich,1002,"Grundton-Teppich"},
        {WendungId::scoreLauern,1003,"Lauern"},
        {WendungId::scoreTrauer,1004,"Trauer"},
        {WendungId::scoreAgentenfarbe,1005,"Agentenfarbe"},
        {WendungId::scoreSeptakkordPaare,1006,"Septakkord-Paare"},
        {WendungId::scoreSchieferWalzer,1007,"Schiefer Walzer"},
        {WendungId::scoreUnruhigerSchlaf,1008,"Unruhiger Schlaf"},
        {WendungId::scoreMollInseln,1009,"Moll-Inseln"},
        {WendungId::scoreGruselOrchester,1010,"Grusel-Orchester"},
        {WendungId::scoreGeisterball,1011,"Geisterball"},
        {WendungId::scoreTerzTreppe,1012,"Terz-Treppe"},
        {WendungId::scoreTritonusSchock,1013,"Tritonus-Schock"},
        {WendungId::scoreVerfolgung,1014,"Verfolgung"},
        {WendungId::scoreAchse,1015,"Achse"},
        {WendungId::scoreSog,1016,"Sog"},
        {WendungId::scoreMollMarsch,1017,"Moll-Marsch"},
        {WendungId::scoreEpischeSpannung,1018,"Epische Spannung"},
        {WendungId::scoreErmittlung,1019,"Ermittlung"},
        {WendungId::scoreSequenzerNacht,1020,"Sequenzer-Nacht"},
        {WendungId::scoreNachtFlachen,1021,"Nacht-Flächen"},
        {WendungId::scoreSynthGroove,1022,"Synth-Groove"},
        {WendungId::scoreFunkSpannung,1023,"Funk-Spannung"},
        {WendungId::scoreFremdeOrte,1024,"Fremde Orte"},
        {WendungId::scoreWurmloch,1025,"Wurmloch"},
        {WendungId::scoreQuartenRuf,1026,"Quarten-Ruf"},
        {WendungId::scoreGeheimnis,1027,"Geheimnis"},
        {WendungId::scoreQuartenWeite,1028,"Quarten-Weite"},
        {WendungId::scoreSchneelinien,1029,"Schneelinien"},
        {WendungId::scoreDorischerSchimmer,1030,"Dorischer Schimmer"},
        {WendungId::scoreGleiten,1031,"Gleiten"},
        {WendungId::scoreOffeneQuinten,1032,"Offene Quinten"},
        {WendungId::scoreBewegterAbschied,1033,"Bewegter Abschied"},
        {WendungId::scoreSehnsucht,1034,"Sehnsucht"},
        {WendungId::scoreWeite,1035,"Weite"},
        {WendungId::scoreErhaben,1036,"Erhaben"},
        {WendungId::scoreRomantik,1037,"Romantik"},
        {WendungId::scoreWarme,1038,"Wärme"},
        {WendungId::scoreLydischesStaunen,1039,"Lydisches Staunen"},
        {WendungId::scoreTerrassen,1040,"Terrassen"},
        {WendungId::scoreAbenteuer,1041,"Abenteuer"},
        {WendungId::scoreTerzverwandtschaft,1042,"Terzverwandtschaft"},
        {WendungId::scoreHeiter,1043,"Heiter"},
        {WendungId::scoreWestern,1044,"Western"},
        {WendungId::scoreErhebung,1045,"Erhebung"},
        {WendungId::scoreFanfare,1046,"Fanfare"},
        {WendungId::scoreHeldisch,1047,"Heldisch"},
        {WendungId::scoreTriumph,1048,"Triumph"},
        {WendungId::popKalteWelle,2001,"Kalte Welle"},
        {WendungId::popNeonregen,2002,"Neonregen"},
        {WendungId::popNachtfahrt,2003,"Nachtfahrt"},
        {WendungId::popSequenzerFieber,2004,"Sequenzer-Fieber"},
        {WendungId::popMiamiNacht,2005,"Miami-Nacht"},
        {WendungId::popKalterKrieg,2006,"Kalter Krieg"},
        {WendungId::popJagdDurchLA,2007,"Jagd durch L.A."},
        {WendungId::popBombast,2008,"Bombast"},
        {WendungId::popRebellenschrei,2009,"Rebellenschrei"},
        {WendungId::popKommando,2010,"Kommando"},
        {WendungId::popGalopp,2011,"Galopp"},
        {WendungId::popDunklerGlanz,2012,"Dunkler Glanz"},
        {WendungId::popSynthFunk,2013,"Synth-Funk"},
        {WendungId::popMosaik,2014,"Mosaik"},
        {WendungId::popTanzsaal,2015,"Tanzsaal"},
        {WendungId::popPowerballade,2016,"Powerballade"},
        {WendungId::popMachtakkorde,2017,"Machtakkorde"},
        {WendungId::popSunsetStrip,2018,"Sunset Strip"},
        {WendungId::popSonnenseite,2019,"Sonnenseite"},
        {WendungId::popStadionhymne,2020,"Stadionhymne"},
        {WendungId::popFeindkontakt,2021,"Feindkontakt"},
        {WendungId::popTeufelsgeiger,2022,"Teufelsgeiger"},
        {WendungId::popVorahnung,2023,"Vorahnung"},
        {WendungId::popEinsamerPlanet,2024,"Einsamer Planet"},
        {WendungId::popWeltraumDisco,2025,"Weltraum-Disco"},
        {WendungId::popSerenade,2026,"Serenade"},
        {WendungId::popStartfreigabe,2027,"Startfreigabe"},
        {WendungId::popTanzflachenlicht,2028,"Tanzflächenlicht"},
        {WendungId::popGegenlicht,2029,"Gegenlicht"},
        {WendungId::popRuckspiegel,2030,"Rückspiegel"},
        {WendungId::popStahlpuls,2031,"Stahlpuls"},
        {WendungId::popDrahtseil,2032,"Drahtseil"},
        {WendungId::popSequenzmotor,2033,"Sequenzmotor"},
        {WendungId::popSpiegelpalast,2034,"Spiegelpalast"},
        {WendungId::popSonntagmorgen,2035,"Sonntagmorgen"},
        {WendungId::popLichtImFenster,2036,"Licht im Fenster"},
        {WendungId::popWcH01,2037,"WC-H01 – Mixolydischer Kreis mit Sus-Auflösung"},
        {WendungId::popWcH11,2038,"WC-H11 – Dorische Wendung"},
        {WendungId::popWcH19,2039,"WC-H19 – Dunkle Quint-Maschine"},
    };
    CHECK(std::size(expected)==87);std::set<unsigned> seen;
    for(const auto& entry:expected)
    {
        CHECK(static_cast<unsigned>(entry.id)==entry.number);
        CHECK(seen.insert(static_cast<unsigned>(entry.id)).second);
        const auto* w=findWendung(entry.id);CHECK(w&&std::string(w->name)==entry.name);
    }
    for(int genre=0;genre<kNumGenres;++genre)for(int index=0;index<wendungCount(genre);++index)
    {
        const auto& w=wendungAt(genre,index);CHECK(seen.count(static_cast<unsigned>(w.id))==1);
        CHECK(wendungIndex(genre,w.id)==index&&findWendung(w.id)==&w);
        CHECK(wendungIndex(1-genre,w.id)==-1);CHECK(wendungBars(w)==8);
    }
    CHECK(!findWendung(WendungId::invalid)&&!findWendung(WendungId::custom));
    CHECK(!findWendung(static_cast<WendungId>(9999)));
    CHECK(popHookPattern(WendungId::scoreTrauer)==-1);
    const Wendung reordered[]={*findWendung(WendungId::popDrahtseil),*findWendung(WendungId::popTanzflachenlicht)};
    CHECK(popHookPattern(reordered[0].id)==4&&popHookPattern(reordered[1].id)==0);
    const WendungId hooks[]={WendungId::popTanzflachenlicht,WendungId::popGegenlicht,WendungId::popRuckspiegel,WendungId::popStahlpuls,WendungId::popDrahtseil,WendungId::popSequenzmotor,WendungId::popSpiegelpalast,WendungId::popSonntagmorgen,WendungId::popLichtImFenster};
    for(int i=0;i<9;++i)CHECK(popHookPattern(hooks[i])==i);
    Settings custom;CHECK(customWendung(custom).id==WendungId::custom);
    return 0;
}
