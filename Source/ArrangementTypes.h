#pragma once
namespace stromscore
{
enum PadPattern { PadAuto = 0, PadHeld, PadStabs, PadPulse, PadStaccato, PadGated, kNumPadPatterns };
enum BassPattern { BassAuto = 0, BassHeld, BassHalf, BassQuarter, BassEighth, BassPulse, BassFunk, BassPendulum,
                   BassWalking, BassAlternating, BassHeartbeat, BassArpeggio, BassPedal, BassHiNrg, BassGallop, kNumBassPatterns };
enum ArpFigure { ArpAuto = 0, ArpUp, ArpDown, ArpCircle, ArpCell, ArpRiff, ArpGlitter, ArpLeaps, ArpCascade, ArpOctatonic, ArpQuartal, ArpSid, kNumArpFigures };
enum ArpRate { RateAuto = 0, RateQuarter, RateEighth, RateSixteenth, kNumArpRates };
enum Genre { GenreScore = 0, GenrePopRock, kNumGenres };
struct ArrangementRecipe { int arp[2],bass[2],pad,hook; };
}
