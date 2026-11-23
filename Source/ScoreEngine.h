#pragma once
// Stromscore: regelbasierter Noten-Generator (kein JUCE, echtzeitfest, ohne Speicheranforderung im Audiopfad).
// Deterministisch bei gleichem Szenenstart, Wurf, Einstellungen und Steuerungsverlauf; erzeugtes MIDI kann festgehalten werden.
//
// Stimmungsfeld: Faerbung (x, dunkel -> hell), Intensitaet (y, ruhig -> aufgewuehlt), Unruhe (z, sauber -> kratzig).
// Aus dem Feld wird je Phrase eine Wendung aus dem Vokabular gezogen (kWendungen, Grundlage: Stilmittel-Katalog).
// Bewegt sich der Punkt merklich, wechselt die Wendung am naechsten Wechselpunkt (Schlag, Takt, 2 oder 4 Takte)
// und beginnt dort mit ihrem ersten Akkord. Alternativ spielt eine eigene Akkordfolge.
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include "CompositionCore.h"
#include "DrivePath.h"

namespace stromscore
{
constexpr int kNumLayers = 5;
enum Layer { kFlaeche = 0, kBass = 1, kArp = 2, kAkzent = 3, kGegenstimme = 4 };
// Ausgaenge: jede Ebene schickt auf einen oder zwei frei waehlbare MIDI-Kanaele
// (Flaeche und Bass: lang und kurz, Akzent: Tupfer und Stich)
constexpr int kNumOutputs = 8;
enum Output { OutPadLong = 0, OutPadShort, OutBassLong, OutBassShort, OutArp, OutTupfer, OutStich, OutCounter };
constexpr int kOutputLayer[kNumOutputs] = { kFlaeche, kFlaeche, kBass, kBass, kArp, kAkzent, kAkzent, kGegenstimme };
// Tonumfang: je Ebene, der Akzent hat zwei (Tupfer und Stich spielen oft auf verschiedenen Instrumenten)
constexpr int kNumRanges = 6;
constexpr int kOutputRange[kNumOutputs] = { 0, 0, 1, 1, 2, 3, 5, 4 };
constexpr int kNumKeys = 12;
constexpr double kStep = 0.25;          // Raster: Sechzehntel (in Viertelnoten)
constexpr int kPhraseBars = 8;          // eine Wendung = 8 Takte
constexpr int kMaxChords = 8;

// Ab welcher Intensitaet eine Ebene im Modus Auto einsetzt (Akzent zusaetzlich bei Unruhe ab 0,35)
constexpr float kLayerStart[kNumLayers] = { 0.0f, 0.0f, 0.25f, 0.25f, 0.15f };
constexpr float kStichStart = 0.5f;     // der zweite Akzent (Stich) kommt erst bei mehr Intensitaet dazu
constexpr float kAkzentUnruhe = 0.35f;
constexpr float kRissStart = 0.8f;     // ab hier reisst die Unruhe: kurze Halbton-Stoesse hoch ueber dem Satz (ab 1.4)

// ------------------------------------------------------------------ Akkorde
enum ChordType { Maj, Min, Maj7, Min7, Dom7, MinMaj7, MinMaj9, Dim7, HalfDim, Sus4, Quartal, Add9, Min9, Aug, Min6, Dom7b9, Sus2, Fifth, kNumChordTypes };
struct ChordShape { int n; int iv[5]; const char* suffix; bool minor; };
constexpr ChordShape kShapes[kNumChordTypes] = {
    { 3, { 0, 4, 7 }, "", false },
    { 3, { 0, 3, 7 }, "m", true },
    { 4, { 0, 4, 7, 11 }, "maj7", false },
    { 4, { 0, 3, 7, 10 }, "m7", true },
    { 4, { 0, 4, 7, 10 }, "7", false },
    { 4, { 0, 3, 7, 11 }, "m(maj7)", true },
    { 5, { 0, 3, 7, 11, 14 }, "m(maj9)", true },
    { 4, { 0, 3, 6, 9 }, "dim7", true },
    { 4, { 0, 3, 6, 10 }, "m7b5", true },
    { 3, { 0, 5, 7 }, "sus4", false },
    { 4, { 0, 5, 10, 15 }, " Quarten", false },
    { 4, { 0, 4, 7, 14 }, "add9", false },
    { 5, { 0, 3, 7, 10, 14 }, "m9", true },
    { 3, { 0, 4, 8 }, "+", false },
    { 4, { 0, 3, 7, 9 }, "m6", true },
    { 5, { 0, 4, 7, 10, 13 }, "7b9", false },
    { 3, { 0, 2, 7 }, "sus2", false },
    { 3, { 0, 7, 12 }, "5", false } };

// Akkordarten fuer die eigene Folge (Reihenfolge = Auswahlliste in der Oberflaeche)
constexpr int kCustomTypes[] = { Maj, Min, Maj7, Min7, Dom7, Sus4, Sus2, Add9, Min6, MinMaj7, HalfDim, Dim7, Aug, MinMaj9, Quartal, Min9, Dom7b9, Fifth };
constexpr int kNumCustomTypes = (int) (sizeof (kCustomTypes) / sizeof (kCustomTypes[0]));

// ------------------------------------------------------------------ Muster
enum PadPattern { PadAuto = 0, PadHeld, PadStabs, PadPulse, PadStaccato, PadGated, kNumPadPatterns };
enum BassPattern { BassAuto = 0, BassHeld, BassHalf, BassQuarter, BassEighth, BassPulse, BassFunk, BassPendulum,
                   BassWalking, BassAlternating, BassHeartbeat, BassArpeggio, BassPedal, BassHiNrg, BassGallop, kNumBassPatterns };
enum ArpFigure { ArpAuto = 0, ArpUp, ArpDown, ArpCircle, ArpCell, ArpRiff, ArpGlitter, ArpLeaps, ArpCascade, ArpOctatonic, ArpQuartal, ArpSid, kNumArpFigures };
enum ArpRate { RateAuto = 0, RateQuarter, RateEighth, RateSixteenth, kNumArpRates };
enum Genre { GenreScore = 0, GenrePopRock, kNumGenres };
enum ChangeGrid { ChangeBeat = 0, ChangeBar, Change2Bars, Change4Bars, kNumChangeGrids };

// ------------------------------------------------------------------ Dramaturgie (ab 1.3)
// Szenenstart ist der Wiedergabebeginn (beim Herausziehen der Anfang der Datei). Von dort an laufen Einstieg und
// Aufbau, die Fahrt von A nach B und das Ende der Szene. Alles ist eine Funktion von Szenenstart, Position und
// Einstellungen; nur die Traegheit merkt sich, welche Ebenen gerade spielen.
enum Entry { EntryAuto = 0, EntryPad, EntryBass, EntryPulse, EntryArp, EntryAkzent, EntryCounter, EntryAll, kNumEntries };
enum Ending { EndHard = 0, EndFade, EndOpen, kNumEndings };
enum Curve { CurveEven = 0, CurveSlow, CurveSteps, CurveWave, kNumCurves };
// Reihenfolge der Ebenen nach dem Einstieg: verwandte Ebenen folgen zuerst (Bass -> Puls/Arp -> Flaeche ...)
constexpr int kEntryOrder[kNumEntries][kNumLayers] = {
    { kFlaeche, kBass, kArp, kGegenstimme, kAkzent },   // Auto (wird vorher aufgeloest)
    { kFlaeche, kBass, kArp, kGegenstimme, kAkzent },   // Flaeche, schuechtern
    { kBass, kArp, kFlaeche, kAkzent, kGegenstimme },   // Bass-Schlag
    { kBass, kFlaeche, kArp, kAkzent, kGegenstimme },   // Puls
    { kArp, kBass, kFlaeche, kGegenstimme, kAkzent },   // Arpeggio
    { kAkzent, kFlaeche, kBass, kArp, kGegenstimme },   // Akzent
    { kGegenstimme, kFlaeche, kBass, kArp, kAkzent },   // Gegenstimme
    { kFlaeche, kBass, kArp, kGegenstimme, kAkzent } }; // Alles zugleich (Reihenfolge nur fuers Ausduennen)
constexpr int kEntryLayer[kNumEntries] = { -1, kFlaeche, kBass, kBass, kArp, kAkzent, kGegenstimme, -1 };
constexpr float kStillIn = 0.10f;       // ganz unten im Feld (Intensitaet) steht der Akkord
constexpr float kStillOut = 0.14f;      // erst darueber laeuft die Akkordfolge wieder
constexpr float kHysteresis = 0.06f;   // Traegheit: so weit unter der Schwelle geht eine Ebene erst wieder aus

// ------------------------------------------------------------------ Vokabular (Wendungen)
struct Chord { int root; int type; int bars; int bass = -1; };   // bass: eigener Basston (Halbtoene ueber dem Grundton der Tonart), -1 = Grundton des Akkords
struct Wendung
{
    const char* name;
    float x, y, z;              // Platz im Stimmungsfeld
    int n; Chord ch[kMaxChords];
    int arp[2], bass[2], pad;   // bevorzugte Muster (Auto waehlt per VARIATION eines der beiden)
};

// Grundlage: Stilmittel-Katalog. Wurzeln in Halbtoenen ueber dem Grundton, Laengen in Takten (Summe je Wendung = 8).
constexpr Wendung kWendungen[] = {
    // dunkel und ruhig: Lauern, Trauer, Unheil
    { "Halbton-Nachbarn",   0.12f, 0.30f, 0.75f, 4, { { 0, Min, 2 }, { 11, Min, 2 }, { 0, Min, 2 }, { 0, MinMaj7, 2 } }, { ArpCircle, ArpCell }, { BassPendulum, BassHeld }, PadHeld },
    { "Grundton-Teppich",   0.10f, 0.45f, 0.50f, 2, { { 0, Min, 4 }, { 1, Maj, 4 } }, { ArpCircle, ArpDown }, { BassPulse, BassEighth }, PadHeld },
    { "Lauern",             0.08f, 0.10f, 0.60f, 1, { { 0, Min, 8 } }, { ArpCircle, ArpCell }, { BassHeld, BassPendulum }, PadHeld },
    { "Trauer",             0.28f, 0.15f, 0.08f, 4, { { 0, Min, 2 }, { 8, Maj, 2 }, { 5, Min, 2 }, { 7, Maj, 2 } }, { ArpDown, ArpCircle }, { BassHeld, BassHalf }, PadHeld },
    { "Agentenfarbe",       0.30f, 0.45f, 0.45f, 3, { { 0, MinMaj9, 4 }, { 5, MinMaj7, 2 }, { 0, MinMaj9, 2 } }, { ArpCell, ArpCircle }, { BassQuarter, BassPendulum }, PadHeld },
    { "Septakkord-Paare",   0.22f, 0.55f, 0.55f, 4, { { 0, Min7, 2 }, { 5, Min7, 2 }, { 0, Min7, 2 }, { 5, Min7, 2 } }, { ArpCell, ArpUp }, { BassEighth, BassPendulum }, PadHeld },
    { "Schiefer Walzer",    0.20f, 0.55f, 0.35f, 4, { { 0, Min, 2 }, { 0, MinMaj7, 2 }, { 5, Min7, 2 }, { 7, Dom7, 2 } }, { ArpCircle, ArpDown }, { BassQuarter, BassHalf }, PadHeld },
    { "Unruhiger Schlaf",   0.25f, 0.35f, 0.40f, 8, { { 0, Min, 1 }, { 8, Maj, 1 }, { 9, Dim7, 1 }, { 8, Maj, 1 }, { 0, Min, 1 }, { 8, Maj, 1 }, { 9, Dim7, 1 }, { 8, Maj, 1 } }, { ArpCircle, ArpCell }, { BassHeld, BassPendulum }, PadHeld },
    { "Moll-Inseln",        0.30f, 0.45f, 0.30f, 4, { { 0, Min, 2 }, { 8, Min, 2 }, { 3, Min, 2 }, { 0, Min, 2 } }, { ArpDown, ArpCircle }, { BassHalf, BassHeld }, PadHeld },
    { "Grusel-Orchester",   0.15f, 0.50f, 0.50f, 4, { { 0, Min, 2 }, { 2, HalfDim, 2 }, { 0, Min, 2 }, { 1, Maj, 2 } }, { ArpDown, ArpCircle }, { BassQuarter, BassPendulum }, PadHeld },
    { "Geisterball",        0.15f, 0.55f, 0.55f, 4, { { 0, Min, 2 }, { 11, Dim7, 2 }, { 0, Min, 2 }, { 5, Min6, 2 } }, { ArpCircle, ArpDown }, { BassAlternating, BassQuarter }, PadStaccato },
    // dunkel und aufgewuehlt: Angst, Panik, Verfolgung
    { "Terz-Treppe",        0.20f, 0.80f, 0.60f, 4, { { 0, Maj, 2 }, { 3, Maj, 2 }, { 6, Maj, 2 }, { 9, Maj, 2 } }, { ArpCell, ArpUp }, { BassPulse, BassEighth }, PadPulse },
    { "Tritonus-Schock",    0.08f, 0.88f, 0.88f, 4, { { 0, Min, 2 }, { 6, Maj, 2 }, { 0, Min, 2 }, { 11, Dim7, 2 } }, { ArpCell, ArpCircle }, { BassPulse, BassPendulum }, PadStabs },
    { "Verfolgung",         0.25f, 0.95f, 0.80f, 8, { { 0, Min, 1 }, { 6, Min, 1 }, { 0, Min, 1 }, { 1, Maj, 1 }, { 0, Min, 1 }, { 6, Maj, 1 }, { 3, Min, 1 }, { 11, Dim7, 1 } }, { ArpCell, ArpUp }, { BassPulse, BassEighth }, PadStabs },
    { "Achse",              0.15f, 0.70f, 0.75f, 4, { { 0, Min6, 2 }, { 6, Min6, 2 }, { 0, Min6, 2 }, { 9, Min7, 2 } }, { ArpOctatonic, ArpCell }, { BassPulse, BassPendulum }, PadStabs },
    { "Sog",                0.30f, 0.70f, 0.70f, 8, { { 0, Aug, 1 }, { 11, Aug, 1 }, { 10, Aug, 1 }, { 9, Aug, 1 }, { 8, Aug, 1 }, { 7, Aug, 1 }, { 6, Aug, 1 }, { 5, Aug, 1 } }, { ArpCell, ArpDown }, { BassPulse, BassEighth }, PadPulse },
    { "Moll-Marsch",        0.32f, 0.75f, 0.20f, 4, { { 0, Min, 2 }, { 5, Min, 2 }, { 8, Maj, 2 }, { 7, Maj, 2 } }, { ArpUp, ArpDown }, { BassEighth, BassQuarter }, PadPulse },
    // Mitte: Spannung, Ermittlung, Synth-Nacht, Fremde Orte, Geheimnis
    { "Epische Spannung",   0.45f, 0.60f, 0.15f, 4, { { 0, Min, 2 }, { 8, Maj, 2 }, { 3, Maj, 2 }, { 10, Maj, 2 } }, { ArpUp, ArpCircle }, { BassEighth, BassQuarter }, PadHeld },
    { "Ermittlung",         0.40f, 0.50f, 0.20f, 4, { { 0, Min6, 2 }, { 5, Min7, 2 }, { 2, HalfDim, 2 }, { 7, Dom7, 2 } }, { ArpDown, ArpRiff }, { BassWalking, BassWalking }, PadStabs },
    { "Sequenzer-Nacht",    0.30f, 0.50f, 0.20f, 4, { { 0, Min, 2 }, { 8, Maj7, 2 }, { 0, Min, 2 }, { 8, Maj7, 2 } }, { ArpUp, ArpCircle }, { BassHeartbeat, BassHeartbeat }, PadHeld },
    { "Nacht-Fl\xc3\xa4" "chen", 0.45f, 0.30f, 0.10f, 4, { { 8, Maj7, 2 }, { 5, Min7, 2 }, { 7, Min7, 2 }, { 0, Min7, 2 } }, { ArpCircle, ArpUp }, { BassArpeggio, BassHalf }, PadHeld },
    { "Synth-Groove",       0.55f, 0.70f, 0.15f, 4, { { 0, Min, 2 }, { 10, Maj, 2 }, { 8, Maj, 2 }, { 10, Maj, 2 } }, { ArpUp, ArpRiff }, { BassFunk, BassArpeggio }, PadStabs },
    { "Funk-Spannung",      0.50f, 0.65f, 0.25f, 4, { { 0, Min9, 2 }, { 5, Dom7, 2 }, { 0, Min9, 2 }, { 10, Dom7, 2 } }, { ArpRiff, ArpRiff }, { BassFunk, BassFunk }, PadStabs },
    { "Fremde Orte",        0.30f, 0.50f, 0.45f, 4, { { 0, Dom7b9, 2 }, { 1, Maj, 2 }, { 0, Dom7b9, 2 }, { 5, Min, 2 } }, { ArpRiff, ArpCircle }, { BassPendulum, BassQuarter }, PadHeld },
    { "Wurmloch",           0.40f, 0.55f, 0.55f, 4, { { 7, Aug, 2 }, { 0, Min, 2 }, { 8, Aug, 2 }, { 1, Min, 2 } }, { ArpCircle, ArpGlitter }, { BassPendulum, BassHeld }, PadHeld },
    { "Quarten-Ruf",        0.55f, 0.60f, 0.30f, 4, { { 0, Quartal, 2 }, { 10, Add9, 2 }, { 0, Quartal, 2 }, { 5, Sus4, 2 } }, { ArpQuartal, ArpUp }, { BassPedal, BassAlternating }, PadPulse },
    { "Geheimnis",          0.45f, 0.30f, 0.50f, 4, { { 0, Aug, 2 }, { 2, Aug, 2 }, { 0, Aug, 2 }, { 10, Aug, 2 } }, { ArpCircle, ArpGlitter }, { BassHeld, BassPendulum }, PadHeld },
    { "Quarten-Weite",      0.60f, 0.45f, 0.45f, 4, { { 0, Quartal, 2 }, { 10, Quartal, 2 }, { 0, Quartal, 2 }, { 6, Maj, 2 } }, { ArpGlitter, ArpCircle }, { BassHeld, BassHalf }, PadHeld },
    // hell und ruhig: Waerme, Staunen, Sehnsucht, Romantik
    { "Schneelinien",       0.55f, 0.30f, 0.10f, 4, { { 0, Sus2, 2 }, { 10, Add9, 2 }, { 5, Add9, 2 }, { 0, Min7, 2 } }, { ArpCascade, ArpCircle }, { BassPedal, BassHeld }, PadHeld },
    { "Dorischer Schimmer", 0.60f, 0.45f, 0.05f, 4, { { 0, Min7, 2 }, { 2, Min7, 2 }, { 3, Maj7, 2 }, { 5, Maj, 2 } }, { ArpCascade, ArpUp }, { BassQuarter, BassArpeggio }, PadHeld },
    { "Gleiten",            0.60f, 0.35f, 0.25f, 4, { { 0, Maj7, 2 }, { 11, Maj7, 2 }, { 10, Maj7, 2 }, { 9, Maj7, 2 } }, { ArpCircle, ArpDown }, { BassHalf, BassHeld }, PadHeld },
    { "Offene Quinten",     0.65f, 0.30f, 0.05f, 4, { { 0, Fifth, 2 }, { 2, Fifth, 2 }, { 4, Fifth, 2 }, { 5, Fifth, 2 } }, { ArpCascade, ArpUp }, { BassHalf, BassArpeggio }, PadHeld },
    { "Bewegter Abschied",  0.60f, 0.35f, 0.15f, 4, { { 0, Maj, 2 }, { 7, Maj, 2 }, { 9, Min, 2 }, { 5, Maj, 2 } }, { ArpUp, ArpDown }, { BassQuarter, BassHalf }, PadHeld },
    { "Sehnsucht",          0.62f, 0.20f, 0.00f, 4, { { 0, Maj, 2 }, { 5, Maj, 2 }, { 5, Min, 2 }, { 0, Maj, 2 } }, { ArpDown, ArpCircle }, { BassHeld, BassHalf }, PadHeld },
    { "Weite",              0.65f, 0.15f, 0.05f, 4, { { 0, Add9, 2 }, { 9, Min7, 2 }, { 5, Maj7, 2 }, { 7, Sus4, 2 } }, { ArpUp, ArpCircle }, { BassHeld, BassHalf }, PadHeld },
    { "Erhaben",            0.70f, 0.30f, 0.00f, 5, { { 0, Maj, 2 }, { 5, Maj, 2 }, { 9, Min, 2 }, { 5, Maj, 1 }, { 0, Maj, 1 } }, { ArpUp, ArpCircle }, { BassHalf, BassHeld }, PadHeld },
    { "Romantik",           0.75f, 0.30f, 0.00f, 4, { { 0, Maj, 2 }, { 9, Min, 2 }, { 4, Min, 2 }, { 5, Maj, 2 } }, { ArpUp, ArpCircle }, { BassHalf, BassQuarter }, PadHeld },
    { "W\xc3\xa4rme",       0.80f, 0.18f, 0.00f, 4, { { 5, Maj7, 2 }, { 0, Maj7, 2 }, { 5, Maj7, 2 }, { 0, Maj7, 2 } }, { ArpCircle, ArpUp }, { BassHeld, BassHalf }, PadHeld },
    { "Lydisches Staunen",  0.85f, 0.35f, 0.10f, 4, { { 0, Maj, 2 }, { 2, Maj, 2 }, { 0, Maj7, 2 }, { 2, Maj, 2 } }, { ArpGlitter, ArpUp }, { BassHeld, BassHalf }, PadHeld },
    // hell und aufgewuehlt: Aufbruch, Abenteuer, Heiterkeit, Triumph
    { "Terrassen",          0.80f, 0.40f, 0.10f, 7, { { 0, Maj, 1 }, { 2, Maj, 1, 0 }, { 10, Maj, 1 }, { 0, Maj, 1, 10 }, { 5, Maj, 1 }, { 7, Maj, 1, 5 }, { 0, Maj, 2 } }, { ArpCascade, ArpUp }, { BassHeld, BassHalf }, PadHeld },
    { "Abenteuer",          0.70f, 0.55f, 0.10f, 4, { { 0, Maj7, 2 }, { 2, Min7, 2 }, { 4, Min7, 2 }, { 7, Dom7, 2 } }, { ArpRiff, ArpUp }, { BassFunk, BassEighth }, PadStabs },
    { "Terzverwandtschaft", 0.72f, 0.68f, 0.30f, 4, { { 0, Maj, 2 }, { 4, Maj, 2 }, { 8, Maj, 2 }, { 0, Maj, 2 } }, { ArpUp, ArpCircle }, { BassQuarter, BassEighth }, PadHeld },
    { "Heiter",             0.82f, 0.50f, 0.05f, 4, { { 0, Maj, 2 }, { 5, Maj, 2 }, { 7, Dom7, 2 }, { 0, Maj, 2 } }, { ArpLeaps, ArpUp }, { BassAlternating, BassAlternating }, PadStaccato },
    { "Western",            0.85f, 0.55f, 0.05f, 4, { { 0, Maj, 2 }, { 5, Maj, 2 }, { 0, Maj, 2 }, { 10, Maj, 2 } }, { ArpLeaps, ArpUp }, { BassAlternating, BassQuarter }, PadHeld },
    { "Erhebung",           0.75f, 0.70f, 0.15f, 8, { { 0, Maj, 1 }, { 0, Dom7, 1 }, { 10, Maj, 1 }, { 10, Dom7, 1 }, { 8, Maj, 1 }, { 8, Dom7, 1 }, { 1, Maj, 1 }, { 1, Maj, 1 } }, { ArpUp, ArpLeaps }, { BassQuarter, BassEighth }, PadPulse },
    { "Fanfare",            0.70f, 0.85f, 0.20f, 4, { { 7, Dim7, 2 }, { 0, Fifth, 2 }, { 5, Dim7, 2 }, { 10, Fifth, 2 } }, { ArpLeaps, ArpUp }, { BassEighth, BassPulse }, PadStabs },
    { "Heldisch",           0.80f, 0.75f, 0.10f, 4, { { 0, Maj, 2 }, { 10, Maj, 2 }, { 5, Maj, 2 }, { 0, Maj, 2 } }, { ArpUp, ArpLeaps }, { BassEighth, BassQuarter }, PadPulse },
    { "Triumph",            0.88f, 0.92f, 0.05f, 4, { { 0, Maj, 2 }, { 8, Maj, 2 }, { 10, Maj, 2 }, { 0, Maj, 2 } }, { ArpUp, ArpLeaps }, { BassEighth, BassEighth }, PadPulse } };
constexpr int kNumWendungen = (int) (sizeof (kWendungen) / sizeof (kWendungen[0]));

// 80er Pop-Rock (Genre-Schalter): Grundlage ist der Abschnitt "80er Pop-Rock" im Stilmittel-Katalog.
constexpr Wendung kPopWendungen[] = {
    // dunkel und ruhig: Nacht, Neon, kalte Welle
    { "Kalte Welle",        0.12f, 0.45f, 0.45f, 2, { { 0, Min, 4 }, { 1, Maj, 4 } }, { ArpSid, ArpCell }, { BassPulse, BassHiNrg }, PadHeld },
    { "Neonregen",          0.35f, 0.25f, 0.10f, 4, { { 0, Min, 2 }, { 5, Min, 2 }, { 8, Maj, 2 }, { 10, Maj, 2 } }, { ArpCircle, ArpDown }, { BassHalf, BassEighth }, PadHeld },
    { "Nachtfahrt",         0.30f, 0.40f, 0.15f, 4, { { 0, Min, 2 }, { 8, Maj, 2 }, { 3, Maj, 2 }, { 10, Maj, 2 } }, { ArpUp, ArpCircle }, { BassEighth, BassPulse }, PadHeld },
    { "Sequenzer-Fieber",   0.30f, 0.55f, 0.25f, 4, { { 0, Min, 2 }, { 8, Maj7, 2 }, { 0, Min, 2 }, { 8, Maj7, 2 } }, { ArpUp, ArpSid }, { BassHiNrg, BassHeartbeat }, PadHeld },
    { "Miami-Nacht",        0.45f, 0.35f, 0.10f, 4, { { 8, Maj7, 2 }, { 5, Min7, 2 }, { 7, Min7, 2 }, { 0, Min7, 2 } }, { ArpCircle, ArpSid }, { BassArpeggio, BassHalf }, PadHeld },
    // dunkel und aufgewuehlt: Rebellion, Bombast, Jagd
    { "Kalter Krieg",       0.10f, 0.75f, 0.85f, 4, { { 0, Min, 2 }, { 6, Maj, 2 }, { 0, Min, 2 }, { 11, Dim7, 2 } }, { ArpSid, ArpOctatonic }, { BassHiNrg, BassPulse }, PadStabs },
    { "Jagd durch L.A.",    0.15f, 0.95f, 0.70f, 8, { { 0, Min, 1 }, { 8, Maj, 1 }, { 10, Maj, 1 }, { 0, Min, 1 }, { 6, Maj, 1 }, { 8, Maj, 1 }, { 10, Maj, 1 }, { 11, Dim7, 1 } }, { ArpSid, ArpCell }, { BassHiNrg, BassPulse }, PadStabs },
    { "Bombast",            0.20f, 0.90f, 0.55f, 3, { { 0, Min, 4 }, { 8, Maj, 2 }, { 10, Maj, 2 } }, { ArpSid, ArpUp }, { BassHiNrg, BassHiNrg }, PadGated },
    { "Rebellenschrei",     0.25f, 0.85f, 0.40f, 4, { { 0, Fifth, 2 }, { 10, Fifth, 2 }, { 8, Fifth, 2 }, { 10, Fifth, 2 } }, { ArpRiff, ArpSid }, { BassEighth, BassGallop }, PadStabs },
    { "Kommando",           0.30f, 0.80f, 0.30f, 4, { { 0, Min, 2 }, { 10, Maj, 2 }, { 8, Maj, 2 }, { 7, Dom7, 2 } }, { ArpSid, ArpUp }, { BassGallop, BassEighth }, PadGated },
    { "Galopp",             0.40f, 0.85f, 0.35f, 5, { { 0, Min, 2 }, { 7, Dom7, 1 }, { 0, Min, 1 }, { 8, Maj, 2 }, { 7, Dom7, 2 } }, { ArpSid, ArpRiff }, { BassGallop, BassGallop }, PadStabs },
    // Mitte: Groove, Glanz
    { "Dunkler Glanz",      0.45f, 0.65f, 0.25f, 4, { { 0, Min, 2 }, { 5, Maj, 2 }, { 0, Min, 2 }, { 5, Maj, 2 } }, { ArpUp, ArpRiff }, { BassEighth, BassGallop }, PadPulse },
    { "Synth-Funk",         0.55f, 0.70f, 0.15f, 4, { { 0, Min, 2 }, { 10, Maj, 2 }, { 8, Maj, 2 }, { 10, Maj, 2 } }, { ArpRiff, ArpUp }, { BassFunk, BassGallop }, PadStabs },
    { "Mosaik",             0.60f, 0.55f, 0.10f, 4, { { 0, Maj, 2 }, { 7, Maj, 2 }, { 9, Min, 2 }, { 5, Maj, 2 } }, { ArpUp, ArpSid }, { BassEighth, BassHiNrg }, PadGated },
    // hell: Tanzsaal, Ballade, Hymne
    { "Tanzsaal",           0.65f, 0.65f, 0.15f, 4, { { 0, Maj, 2 }, { 10, Maj, 2 }, { 5, Maj, 2 }, { 0, Maj, 2 } }, { ArpRiff, ArpUp }, { BassHiNrg, BassEighth }, PadGated },
    { "Powerballade",       0.70f, 0.30f, 0.05f, 4, { { 0, Maj, 2 }, { 4, Min, 2 }, { 5, Maj, 2 }, { 7, Maj, 2 } }, { ArpCircle, ArpUp }, { BassHalf, BassQuarter }, PadHeld },
    { "Machtakkorde",       0.70f, 0.80f, 0.30f, 4, { { 0, Fifth, 2 }, { 10, Fifth, 2 }, { 5, Fifth, 2 }, { 0, Fifth, 2 } }, { ArpRiff, ArpLeaps }, { BassEighth, BassGallop }, PadStabs },
    { "Sunset Strip",       0.80f, 0.45f, 0.05f, 4, { { 0, Add9, 2 }, { 5, Maj, 2, 0 }, { 0, Add9, 2 }, { 7, Sus4, 2 } }, { ArpSid, ArpCascade }, { BassPedal, BassEighth }, PadHeld },
    { "Sonnenseite",        0.80f, 0.65f, 0.10f, 3, { { 10, Maj, 2 }, { 5, Maj, 2 }, { 0, Maj, 4 } }, { ArpRiff, ArpUp }, { BassEighth, BassAlternating }, PadGated },
    { "Stadionhymne",       0.85f, 0.90f, 0.10f, 6, { { 0, Maj, 2 }, { 8, Maj, 1 }, { 10, Maj, 1 }, { 0, Maj, 2 }, { 8, Maj, 1 }, { 10, Maj, 1 } }, { ArpUp, ArpLeaps }, { BassEighth, BassHiNrg }, PadPulse },
    // Fernseh-Disco-Funk um 1980 (Abschnitt "Weltraum-Disco und Teufelsgeiger" im Katalog)
    { "Feindkontakt",       0.18f, 0.80f, 0.55f, 4, { { 0, Min7, 2 }, { 1, Maj7, 2 }, { 0, Min7, 2 }, { 6, Dom7, 2 } }, { ArpCell, ArpOctatonic }, { BassFunk, BassPulse }, PadStabs },
    { "Teufelsgeiger",      0.32f, 0.70f, 0.25f, 8, { { 0, Min, 1 }, { 5, Min, 1 }, { 10, Maj, 1 }, { 3, Maj, 1 }, { 8, Maj, 1 }, { 2, HalfDim, 1 }, { 7, Dom7, 1 }, { 0, Min, 1 } }, { ArpLeaps, ArpCircle }, { BassHiNrg, BassEighth }, PadPulse },
    { "Vorahnung",          0.38f, 0.45f, 0.45f, 4, { { 0, Min, 2 }, { 1, Maj, 2 }, { 7, Dom7b9, 2 }, { 0, Min, 2 } }, { ArpCircle, ArpCascade }, { BassHeartbeat, BassPulse }, PadHeld },
    { "Einsamer Planet",    0.40f, 0.20f, 0.10f, 5, { { 0, Min9, 2 }, { 8, Maj7, 2 }, { 10, Sus4, 1 }, { 10, Maj, 1 }, { 0, Min9, 2 } }, { ArpCircle, ArpCascade }, { BassHeld, BassHalf }, PadHeld },
    { "Weltraum-Disco",     0.48f, 0.62f, 0.20f, 5, { { 0, Min9, 2 }, { 5, Dom7, 2 }, { 0, Min9, 2 }, { 3, Maj7, 1 }, { 5, Dom7, 1 } }, { ArpRiff, ArpSid }, { BassHiNrg, BassFunk }, PadGated },
    { "Serenade",           0.72f, 0.45f, 0.05f, 4, { { 0, Maj, 2 }, { 9, Min, 2 }, { 2, Min7, 2 }, { 7, Dom7, 2 } }, { ArpLeaps, ArpUp }, { BassAlternating, BassEighth }, PadStaccato },
    { "Startfreigabe",      0.78f, 0.75f, 0.15f, 4, { { 0, Maj7, 2 }, { 2, Dom7, 2 }, { 2, Min7, 2 }, { 7, Sus4, 2 } }, { ArpRiff, ArpUp }, { BassHiNrg, BassFunk }, PadStabs },
    // Original 80s-inspired studies: album-pop language, not transcriptions of songs.
    { "Tanzflächenlicht", 0.76f, 0.69f, 0.08f, 5, { {0,Maj,2}, {2,Min7,2}, {5,Maj,2}, {7,Sus4,1}, {7,Maj,1} }, {ArpRiff,ArpUp}, {BassFunk,BassArpeggio}, PadStabs },
    { "Gegenlicht", 0.52f, 0.38f, 0.12f, 4, { {0,Maj7,2}, {10,Maj7,2}, {2,Min7,2}, {7,Sus4,2} }, {ArpCircle,ArpCascade}, {BassFunk,BassHalf}, PadHeld },
    { "Rückspiegel", 0.36f, 0.18f, 0.06f, 4, { {9,Min9,2}, {9,Min9,2,7}, {2,Dom7,2,6}, {5,Maj7,2} }, {ArpDown,ArpCircle}, {BassHeld,BassHalf}, PadHeld },
    { "Stahlpuls", 0.34f, 0.83f, 0.22f, 4, { {9,Fifth,2,9}, {5,Fifth,2,9}, {7,Fifth,2,9}, {9,Fifth,2,9} }, {ArpRiff,ArpCell}, {BassEighth,BassPedal}, PadGated },
    { "Drahtseil", 0.20f, 0.57f, 0.42f, 4, { {9,Min,2,9}, {9,MinMaj7,2,9}, {9,Min7,2,9}, {9,Min6,2,9} }, {ArpDown,ArpCell}, {BassEighth,BassPedal}, PadHeld },
    { "Sequenzmotor", 0.46f, 0.78f, 0.17f, 4, { {9,Min9,2}, {2,Dom7,2}, {7,Maj7,2}, {0,Maj7,2} }, {ArpSid,ArpRiff}, {BassHiNrg,BassFunk}, PadGated },
    { "Spiegelpalast", 0.70f, 0.71f, 0.26f, 7, { {0,Maj7,1}, {4,Dom7,1}, {9,Min7,2}, {2,Dom7,1}, {2,Min7,1}, {7,Dom7,1}, {0,Maj7,1} }, {ArpCascade,ArpUp}, {BassArpeggio,BassQuarter}, PadStabs },
    { "Sonntagmorgen", 0.88f, 0.48f, 0.03f, 4, { {0,Maj,2}, {5,Maj,2}, {9,Min7,2}, {7,Maj,2} }, {ArpRiff,ArpCircle}, {BassFunk,BassAlternating}, PadStabs },
    { "Licht im Fenster", 0.57f, 0.23f, 0.04f, 4, { {9,Min,2}, {0,Maj,2,7}, {5,Maj7,2}, {4,Dom7,2} }, {ArpCircle,ArpDown}, {BassHeld,BassHalf}, PadHeld } };
constexpr int kNumPopWendungen = (int) (sizeof (kPopWendungen) / sizeof (kPopWendungen[0]));
constexpr int kMaxWendungen = 64;
static_assert (kNumWendungen <= kMaxWendungen && kNumPopWendungen <= kMaxWendungen, "Vorrat zu gross");
constexpr int kCustomWendung = 1000;   // Index fuer die eigene Folge

inline const Wendung* wendungTable (int genre) { return genre == GenrePopRock ? kPopWendungen : kWendungen; }
inline int wendungCount (int genre) { return genre == GenrePopRock ? kNumPopWendungen : kNumWendungen; }
inline const Wendung& wendungAt (int genre, int i) { return wendungTable (genre)[std::clamp (i, 0, wendungCount (genre) - 1)]; }

// ------------------------------------------------------------------ Ein- und Ausgabe
struct CustomChord { int rootAbs = 0; int type = Maj; int bars = 0; };   // bars 0 = Platz leer

struct Settings
{
    int key = 9;                // 0 = C ... 9 = A ... 11 = H
    float x = 0.3f;             // Faerbung: 0 dunkel ... 1 hell
    float y = 0.3f;             // Intensitaet: 0 ruhig ... 1 aufgewuehlt
    float z = 0.0f;             // Unruhe: 0 sauber ... 1 kratzig
    int meterNum = 4, meterDen = 4;
    float swing = 0.0f;         // 0 ... 1 (1 = Triolen-Feeling)
    int variation = 1;          // 1 ... 16
    int change = ChangeBeat;    // Wechselpunkt fuer neue Wendungen
    bool mute[kNumLayers] = {};                               // Ebene stumm
    bool solo[kNumLayers] = {};                               // ist eine Ebene solo, spielen nur die Solo-Ebenen
    float layerIntensity[kNumLayers] = {};                    // -1 ... +1 zur Intensitaet des Feldes (0 = wie das Feld)
    float variety = 0.5f;
    int genre = GenreScore;     // Vokabular: Score oder 80er Pop-Rock
    bool dynamics = false;      // Dynamik als CC an die Spuren senden
    int ccDynamics = 1, ccExpression = 11;   // 0 = diesen CC nicht senden
    int ccLo[2][16] = {}, ccHi[2][16] = {};
    bool ccRange = false; // false preserves legacy projects; processor supplies explicit channel ranges
    bool passing = false;       // Durchgangsakkorde: bei viel Intensitaet die Dominante des naechsten Akkords auf dem letzten Schlag       // Abwechslung: 0 = nur die passendste Wendung, 1 = auch entferntere Nachbarn
    int octave[kNumLayers] = { 0, 0, 0, 0, 0 };               // -2 ... +2
    bool rangeOn[kNumRanges] = {};                            // Tonumfang begrenzen (fuer Orchesterinstrumente); [3] Tupfer, [5] Stich
    int rangeLo[kNumRanges] = { 0, 0, 0, 0, 0, 0 };           // tiefster spielbarer Ton (MIDI-Nummer)
    int rangeHi[kNumRanges] = { 127, 127, 127, 127, 127, 127 };   // hoechster spielbarer Ton
    int channel[kNumOutputs] = { 1, 2, 3, 4, 5, 6, 7, 8 };    // MIDI-Kanal je Ausgang (1 ... 16), doppelte Belegung erlaubt
    bool legato = true;         // Gegenstimme: Toene binden (minimale Ueberlappung bis zum naechsten Ton)
    bool follow[3] = { true, true, true };                    // Flaeche, Bass, Arp: false = bleibt auf dem Grundakkord
    int padPattern = PadAuto, bassPattern = BassAuto, arpFigure = ArpAuto, arpRate = RateAuto;
    bool custom = false;        // eigene Akkordfolge statt Wendungen
    CustomChord customChords[kMaxChords];

    // Dramaturgie (ab 1.3). Vorgaben hier: alles aus, wie vor 1.3; das Plugin schaltet Aufbau, Motiv und Traegheit ein.
    bool endRequested = false;
    DrivePath route;
    bool scene = false;         // Aufbau: Ebenen setzen nach dem Einstieg gestaffelt ein
    int entry = EntryAuto;      // womit die Szene beginnt
    int seed = 0;               // Wurf ("Neu wuerfeln"): Einstieg bei Auto und Motiv
    int buildBars = 8;          // Laenge des Aufbaus: 4, 8 oder 16 Takte
    float hardness = 0.5f;      // Einsatz: 0 weich eingeblendet (zwei Takte) ... 0,5 neutral ... 1 hart gesetzt
    int sceneBars = 0;          // Laenge der Szene in Takten, 0 = unbegrenzt
    int ending = EndFade;       // Ende der Szene: hart, ausklingend, offen
    bool motif = false;         // Szenenmotiv in der Gegenstimme
    bool inertia = false;       // Traegheit: Ebenen schalten nur auf Taktgrenzen, mit Abstand zur Schwelle, mindestens 2 Takte
    uint32_t driveGeneration = 0; // Rising-edge identity, transient (not a host parameter)
    bool drive = false;         // Fahrt von A (x, y) nach B
    float driveX = 0.8f, driveY = 0.85f;
    int driveFrom = 0;          // Takte nach Szenenstart
    int driveBars = 8;
    int driveCurve = CurveEven;

    // Stich (ab 1.4): immer ein einzelner Ton. Fest: eine frei gewaehlte Taste (perkussives Sample), unabhaengig von
    // Akkord, Oktave und Tonumfang. Sonst der Grundton des Akkords in der Lage des Stichs.
    bool stichFixed = false;
    int stichNote = 36;
};

struct Transport
{
    bool playing = false;
    double ppq = 0.0;           // Position am Blockanfang in Viertelnoten
    double bpm = 120.0;
    double sampleRate = 48000.0;
};

// velocity 0 = Note aus
// type 0: Note (velocity 0 = aus), type 1: Controller (note = CC-Nummer, velocity = Wert)
struct Event { int offset; uint8_t channel; uint8_t note; uint8_t velocity; uint8_t type = 0; uint8_t out = 0; };

struct EventList
{
    static constexpr int kCapacity = 2048;
    std::array<Event, kCapacity> events {};
    int size = 0;
    bool overflow = false;
    void clear() { size = 0; overflow = false; }
    void add (int offset, int channel, int note, int velocity, int out = 0)
    {
        if (size >= kCapacity) { overflow = true; return; }
        events[(size_t) size++] = { offset, (uint8_t) channel, (uint8_t) note, (uint8_t) velocity, 0, (uint8_t) out };
    }
    void addCc (int offset, int channel, int controller, int value, int out = 0)
    {
        if (size >= kCapacity) { overflow = true; return; }
        events[(size_t) size++] = { offset, (uint8_t) channel, (uint8_t) controller, (uint8_t) std::clamp (value, 0, 127), 1, (uint8_t) out };
    }
};

inline uint32_t hash3 (uint32_t a, uint32_t b, uint32_t c)
{
    uint32_t h = a * 0x9E3779B1u ^ (b + 0x7F4A7C15u) * 0x85EBCA6Bu ^ (c + 0x165667B1u) * 0xC2B2AE35u;
    h ^= h >> 16; h *= 0x7FEB352Du; h ^= h >> 15; h *= 0x846CA68Bu; h ^= h >> 16;
    return h;
}

// Akkordname (internationale Schreibweise, UTF-8 mit \u266d / \u266f): "Am", "Fmaj7", "G\u266fm(maj7)"
inline void chordName (int key, int root, int type, char* out, int maxLen)
{
    static const char* major[12] = { "C", "D\xe2\x99\xad", "D", "E\xe2\x99\xad", "E", "F", "F\xe2\x99\xaf", "G", "A\xe2\x99\xad", "A", "B\xe2\x99\xad", "B" };
    static const char* minor[12] = { "C", "C\xe2\x99\xaf", "D", "E\xe2\x99\xad", "E", "F", "F\xe2\x99\xaf", "G", "G\xe2\x99\xaf", "A", "B\xe2\x99\xad", "B" };
    const int pc = ((key + root) % 12 + 12) % 12;
    const bool isMinor = kShapes[std::clamp (type, 0, kNumChordTypes - 1)].minor;
    int p = 0;
    for (const char* s = (isMinor ? minor : major)[pc]; *s && p < maxLen - 1; ++s) out[p++] = *s;
    for (const char* s = kShapes[std::clamp (type, 0, kNumChordTypes - 1)].suffix; *s && p < maxLen - 1; ++s) out[p++] = *s;
    out[p] = 0;
}

// Die eigene Folge als Wendung (Wurzeln relativ zur Tonart, leere Plaetze uebersprungen)
inline Wendung customWendung (const Settings& s)
{
    Wendung w { "Eigene Folge", 0.5f, 0.5f, 0.0f, 0, {}, { ArpAuto, ArpAuto }, { BassAuto, BassAuto }, PadHeld };
    for (const auto& c : s.customChords)
        if (c.bars > 0 && w.n < kMaxChords)
            w.ch[w.n++] = { ((c.rootAbs - s.key) % 12 + 12) % 12, std::clamp (c.type, 0, kNumChordTypes - 1), std::clamp (c.bars, 1, 8) };
    if (w.n == 0) w.ch[w.n++] = { 0, Maj, 2 };
    return w;
}

inline int wendungBars (const Wendung& w)
{
    int b = 0;
    for (int i = 0; i < w.n; ++i) b += w.ch[i].bars;
    return std::max (1, b);
}

// Taktlaenge in Sechzehnteln und Betonungsgruppen (z. B. 5/4: 3+3+2+2 Achtel, 7/8: 2+2+3 Achtel)
struct Meter
{
    int len = 16;
    int numGroups = 4;
    int groupStart[128] {};

    static Meter from (int num, int den)
    {
        Meter m;
        num = std::clamp (num, 1, 16);
        den = (den == 1 || den == 2 || den == 4 || den == 8 || den == 16) ? den : 4;
        m.len = std::clamp (num * 16 / den, 1, 256);
        int sizes[128] {}; int n = 0;
        if (den == 8 && num % 3 == 0)            { for (int i = 0; i < num / 3; ++i) sizes[n++] = 6; }
        else if (den == 8 && num >= 5)           { int rest = m.len; while (rest > 6) { sizes[n++] = 4; rest -= 4; } sizes[n++] = rest; }
        else if (num == 5 && den == 4)           { sizes[n++] = 6; sizes[n++] = 6; sizes[n++] = 4; sizes[n++] = 4; }
        else { int rest = m.len; while (rest > 0 && n < 128) { const int g = std::min (4, rest); sizes[n++] = g; rest -= g; } }
        int pos = 0;
        m.numGroups = 0;
        for (int i = 0; i < n && pos < m.len; ++i) { m.groupStart[m.numGroups++] = pos; pos += sizes[i]; }
        return m;
    }
    bool isGroupStart (int pos) const
    {
        for (int i = 0; i < numGroups; ++i) if (groupStart[i] == pos) return true;
        return false;
    }
};

// ------------------------------------------------------------------ Generator
class Generator
{
public:
    void reset() { motifMemory.clear(); style = -1; csNote = -1; csPendingAt = -1; chaseStep = -1; lastGenre = -1; resetCc(); resetVoicing(); numActive = 0; running = false; lastPpqEnd = 0.0; phraseIndex = -1; current = -1; wendungStart = 0; still = false; chordBase = 0; drivePrev = driveSeen = driveLatched = driveArrivedNow = false; driveTrajectory = false; driveProgressNow = 0; driveGenerationSeen = 0; curRoot = 0; curType = Min; curChord = -1;
                   sceneStep = 0; manualEndStep = -1; manualFinished = manualHitSent = false; endWasRequested = false; sceneSeed = 0; autoSeed = -1; sceneBarNow = -1; sceneEnded = false; for (int l = 0; l < kNumLayers; ++l) { on[l] = prevOn[l] = hOn[l] = false; } }

    uint32_t unavailablePadPitchClasses() const { return unavailablePad; }

    // Fuer die Anzeige: Szene
    int sceneBar() const { return sceneBarNow; }              // Takte seit Szenenstart (-1: steht)
    int sceneEntry() const { return entryInUse; }             // aufgeloester Einstieg
    bool sceneOver() const { return sceneEnded; }
    int activeSeed() const { return sceneSeed; }
    const composition::RememberedMotif& rememberedMotif() const { return motifMemory; }
    int plannedHarmonySlots() const { return planValid ? harmonicPlan.count : 0; }
    bool driveArrived() const { return driveArrivedNow; }     // die Fahrt ist bei B angekommen (das Plugin macht B dann zu A)
    uint32_t driveGenerationNow() const { return driveGenerationSeen; }
    float driveProgress() const { return driveProgressNow; }
    int driveFromNow() const { return driveLatched ? driveFromLatched : -1; }   // Fahrt, die waehrend der Wiedergabe eingeschaltet wurde: Startbar
    float pointX() const { return curX; }                     // Punkt im Feld, wie er gerade klingt (mit Fahrt)
    float pointY() const { return curY; }
    bool layerPlaying (int l) const { return on[std::clamp (l, 0, kNumLayers - 1)]; }

    // Ebene nicht stumm (Mute) und nicht durch Solo einer anderen Ebene ausgeschlossen
    static bool muteSoloOk (const Settings& s, int layer)
    {
        bool anySolo = false;
        for (bool b : s.solo) anySolo = anySolo || b;
        return anySolo ? s.solo[layer] : ! s.mute[layer];
    }
    // Schwelle erreicht (ohne Mute/Solo); levelOff: weit genug darunter, dass die Traegheit loslaesst
    static bool levelOn (const Settings& s, int layer)
    {
        const float y = layerY (s, layer);
        if (layer == kAkzent) return y >= kLayerStart[kAkzent] || s.z >= kAkzentUnruhe;
        return y >= kLayerStart[layer];
    }
    static bool levelOff (const Settings& s, int layer)
    {
        const float y = layerY (s, layer);
        if (layer == kAkzent) return y < kLayerStart[kAkzent] - kHysteresis && s.z < kAkzentUnruhe - kHysteresis;
        return y < kLayerStart[layer] - kHysteresis;
    }

    // Einstieg bei Auto: gewuerfelt aus dem Wurf, gewichtet nach Genre und Stimmungsfeld (nur Ebenen, die spielen koennen)
    static int autoEntry (const Settings& s)
    {
        const bool pop = s.genre == GenrePopRock;
        auto ok = [&s] (int l) { return muteSoloOk (s, l) && levelOn (s, l); };
        float w[kNumEntries] {};
        if (ok (kFlaeche)) w[EntryPad] = pop ? 1.0f : 3.0f + (s.z >= kAkzentUnruhe ? 1.0f : 0.0f) + (s.y < 0.3f ? 1.0f : 0.0f);
        if (ok (kBass)) { w[EntryBass] = 2.0f; w[EntryPulse] = 1.0f + (s.z >= kAkzentUnruhe ? 2.0f : 0.0f); }
        if (ok (kArp)) w[EntryArp] = pop ? 3.0f : 1.0f;
        if (ok (kAkzent)) w[EntryAkzent] = pop ? 0.5f : 1.0f;
        if (ok (kGegenstimme)) w[EntryCounter] = pop ? 0.5f : 1.0f;
        if (s.y >= (pop ? 0.6f : 0.7f)) w[EntryAll] = pop ? 1.5f : 0.75f;
        float total = 0.0f;
        for (float v : w) total += v;
        if (total <= 0.0f) return EntryAll;
        const float r = (float) (hash3 ((uint32_t) s.seed, (uint32_t) s.variation, 1301u) % 100000u) / 100000.0f * total;
        float acc = 0.0f;
        for (int e = 1; e < kNumEntries; ++e) { acc += w[e]; if (r < acc) return e; }
        return EntryPad;
    }

    // Fahrt: Anteil des Weges von A nach B (0 ... 1) nach Takten seit Szenenstart, mit Kurve
    static float driveAmount (const Settings& s, double barsSinceStart)
    {
        if (! s.drive || s.driveBars <= 0) return 0.0f;
        const double t = std::clamp ((barsSinceStart - (double) s.driveFrom) / (double) s.driveBars, 0.0, 1.0);
        switch (s.driveCurve)
        {
            case CurveSlow:  return (float) (t * t);
            case CurveSteps: return (float) (std::floor (t * 4.0 + 1e-9) / 4.0);
            case CurveWave:  return (float) (0.5 - 0.5 * std::cos (2.0 * 3.14159265358979 * t));
            default:         return (float) t;
        }
    }

    // Fuer die Anzeige (kCustomWendung = eigene Folge)
    int wendung() const { return current; }
    int chordInWendung() const { return curChord; }
    int chordRoot() const { return curRoot; }
    int chordType() const { return curType; }
    int styleWendung() const { return current == kCustomWendung ? style : -1; }   // eigene Folge: Wendung, deren Stil geliehen wird
    int genreInUse() const { return genre; }
    int nextRoot() const { return curNextRoot; }
    int nextType() const { return curNextType; }
    float chordProgress() const { return curProgress; }   // 0 ... 1 bis zum naechsten Akkordwechsel

    // Intensitaet einer Ebene: Feld plus eigener Regler
    static float layerY (const Settings& s, int layer)
    {
        return std::clamp (s.y + s.layerIntensity[layer], 0.0f, 1.0f);
    }

    static bool layerActive (const Settings& s, int layer) { return muteSoloOk (s, layer) && levelOn (s, layer); }

    // Ab welchem Anteil der besten Passung eine Wendung in Frage kommt (Abwechslung 0 = nur die beste)
    static float keepRatio (const Settings& s) { return 1.0f - 0.85f * std::clamp (s.variety, 0.0f, 1.0f); }

    // Wendungen, die an der aktuellen Stelle in Frage kommen, nach Passung sortiert
    static int candidates (const Settings& s, int* out, int maxOut)
    {
        const Wendung* tbl = wendungTable (s.genre); const int count = wendungCount (s.genre);
        float w[kMaxWendungen]; float best = 0.0f;
        for (int i = 0; i < count; ++i) { w[i] = weight (tbl[i], s); best = std::max (best, w[i]); }
        const float r = keepRatio (s);
        int n = 0;
        if (maxOut <= 0) return 0;
        for (int i = 0; i < count; ++i)
        {
            if (w[i] < r * best - 1e-9f) continue;
            int j;
            if (n < maxOut) j = n++;
            else if (w[out[maxOut - 1]] < w[i]) j = maxOut - 1;   // ersetzt den schwaechsten
            else continue;
            out[j] = i;
            while (j > 0 && w[out[j - 1]] < w[out[j]]) { std::swap (out[j - 1], out[j]); --j; }
        }
        return n;
    }

    // Gewicht einer Wendung fuer die aktuelle Lage im Feld
    static float weight (const Wendung& w, const Settings& s)
    {
        const float dx = w.x - s.x, dy = (w.y - s.y) * 0.7f, dz = (w.z - s.z) * 0.8f;
        return std::exp (-(dx * dx + dy * dy + dz * dz) / 0.05f);
    }

    static float bestWeight (const Settings& s)
    {
        float best = 0.0f;
        for (int i = 0; i < wendungCount (s.genre); ++i) best = std::max (best, weight (wendungTable (s.genre)[i], s));
        return best;
    }

    // Deterministische Wahl unter den Wendungen, die gut zur Lage passen (mindestens halb so gut wie die beste)
    static int pick (const Settings& s, long long salt)
    {
        const Wendung* tbl = wendungTable (s.genre); const int count = wendungCount (s.genre);
        float w[kMaxWendungen]; float total = 0.0f, best = 0.0f; int bestIdx = 0;
        for (int i = 0; i < count; ++i)
        {
            w[i] = weight (tbl[i], s);
            if (w[i] > best) { best = w[i]; bestIdx = i; }
        }
        const float ratio = keepRatio (s);
        for (int i = 0; i < count; ++i) { if (w[i] < ratio * best) w[i] = 0.0f; total += w[i]; }
        if (total <= 0.0f) return bestIdx;
        const float r = (float) (hash3 ((uint32_t) s.variation, (uint32_t) salt, 911u) % 100000u) / 100000.0f * total;
        float acc = 0.0f;
        for (int i = 0; i < count; ++i) { acc += w[i]; if (r < acc) return i; }
        return bestIdx;
    }

    void allNotesOff (EventList& out, int offset)
    {
        while (numActive > 0) removeActive (numActive - 1, offset, out);
    }

    void process (const Transport& t, const Settings& sIn, int numSamples, EventList& out)
    {
        Settings s = sIn;
        if (! running) sceneSeed = s.seed;
        s.seed = sceneSeed;
        if (s.dynamics != ccWasEnabled) { resetCc(); ccWasEnabled = s.dynamics; }
        s.route.count=std::clamp(s.route.count,0,4);
        for(auto& p:s.route.points){p.x=std::isfinite(p.x)?std::clamp(p.x,0.f,1.f):.5f;p.y=std::isfinite(p.y)?std::clamp(p.y,0.f,1.f):.5f;}
        for(auto& p:s.route.bends){p.x=std::isfinite(p.x)?std::clamp(p.x,-1.f,1.f):0;p.y=std::isfinite(p.y)?std::clamp(p.y,-1.f,1.f):0;}
        s.key = std::clamp (s.key, 0, kNumKeys - 1);
        s.x = std::clamp (s.x, 0.0f, 1.0f); s.y = std::clamp (s.y, 0.0f, 1.0f); s.z = std::clamp (s.z, 0.0f, 1.0f);
        s.swing = std::clamp (s.swing, 0.0f, 1.0f);
        s.variation = std::clamp (s.variation, 1, 16);
        s.change = std::clamp (s.change, 0, kNumChangeGrids - 1);
        for (auto& v : s.layerIntensity) v = std::clamp (v, -1.0f, 1.0f);
        s.variety = std::clamp (s.variety, 0.0f, 1.0f);
        for (auto& o : s.octave) o = std::clamp (o, -2, 2);
        for (auto& c : s.channel) c = std::clamp (c, 1, 16);
        for (int i = 0; i < kNumRanges; ++i)
        {
            int lo = std::clamp (s.rangeLo[i], 0, 127), hi = std::clamp (s.rangeHi[i], 0, 127);
            if (lo > hi) std::swap (lo, hi);
            s.rangeLo[i] = lo; s.rangeHi[i] = hi;
        }
        s.padPattern = std::clamp (s.padPattern, 0, kNumPadPatterns - 1);
        s.bassPattern = std::clamp (s.bassPattern, 0, kNumBassPatterns - 1);
        s.arpFigure = std::clamp (s.arpFigure, 0, kNumArpFigures - 1);
        s.arpRate = std::clamp (s.arpRate, 0, kNumArpRates - 1);
        s.entry = std::clamp (s.entry, 0, kNumEntries - 1);
        s.buildBars = std::clamp (s.buildBars, 1, 4096);
        s.hardness = std::clamp (s.hardness, 0.0f, 1.0f);
        s.sceneBars = std::clamp (s.sceneBars, 0, 4096);
        s.ending = std::clamp (s.ending, 0, kNumEndings - 1);
        s.driveX = std::clamp (s.driveX, 0.0f, 1.0f); s.driveY = std::clamp (s.driveY, 0.0f, 1.0f);
        s.driveFrom = std::clamp (s.driveFrom, 0, 4096); s.driveBars = std::clamp (s.driveBars, 1, 4096);
        s.driveCurve = std::clamp (s.driveCurve, 0, kNumCurves - 1);
        // Observe off/restart on every audio block, even between sixteenth-note ticks.
        if (! s.drive || s.driveGeneration != driveGenerationSeen)
        {
            drivePrev = driveLatched = driveArrivedNow = driveTrajectory = false;
            driveProgressNow = 0.0f;
        }
        driveGenerationSeen = s.driveGeneration;
        cur = &s;
        meter = Meter::from (s.meterNum, s.meterDen);
        custom = customWendung (s);
        const int bars = s.custom ? wendungBars (custom) : kPhraseBars;
        s.genre = std::clamp (s.genre, 0, kNumGenres - 1);
        if (s.custom != wasCustom || bars != phraseBars || s.genre != lastGenre)   // Umschalten, neue Laenge oder anderes Genre: neue Phrase
        {
            phraseIndex = -1; wasCustom = s.custom; phraseBars = bars; style = -1;
            genre = s.genre; lastGenre = s.genre;
            if (running) releaseHeld (0, out);
        }

        if (! t.playing || ! std::isfinite (t.bpm) || ! std::isfinite (t.sampleRate) || ! std::isfinite (t.ppq) || std::abs (t.ppq) > 1.0e9 || t.bpm <= 0.0 || t.sampleRate <= 0.0 || numSamples <= 0)
        {
            if (running) allNotesOff (out, 0);
            running = false; curChord = -1; cur = nullptr; sceneBarNow = -1;
            return;
        }
        releaseSilencedLayers (s, out);

        const double samplesPerQuarter = t.sampleRate * 60.0 / t.bpm;
        const double ppqEnd = t.ppq + (double) numSamples / samplesPerQuarter;
        const bool jumped = running && std::fabs (t.ppq - lastPpqEnd) > 0.05;
        const float ax = s.x, ay = s.y;   // Punkt A im Feld (die Fahrt bewegt den klingenden Punkt von hier nach B)
        if (! running || jumped)
        {
            allNotesOff (out, 0);
            if(!motifMemory.complete)motifMemory.clear();
            resetVoicing();
            driveTrajectory = false; // A seek reconstructs the curve at the destination, without old segment history.
            // Szenenstart: Wiedergabebeginn, auf den Taktanfang gerundet. Ein Sprung nach vorn (oder ein Loop, der nicht
            // vor den Start zurueckspringt) laeuft in derselben Szene weiter, ein Sprung davor beginnt eine neue.
            const long long k0 = (long long) std::floor (t.ppq / kStep + 1e-9);
            if (! running) { manualEndStep = -1; manualFinished = manualHitSent = false; endWasRequested = false; }
            if (! running || k0 < sceneStep) { motifMemory.clear(); sceneStep = floorDiv (k0, meter.len) * meter.len; driveLatched = false; drivePrev = false; driveSeen = false; }
            running = true;
            phraseIndex = -1;
            csNote = -1; csPendingAt = -1; resetCc();
            applyDrive (k0, s, ax, ay);
            chase (t.ppq, s, out);
        }

        const long long firstStep = (long long) std::floor (t.ppq / kStep) - 1;
        for (long long k = std::max (0LL, firstStep); ; ++k)
        {
            const double when = ((double) k + swingDelay (k, s)) * kStep;
            if (when >= ppqEnd - 1e-12) break;
            if (when < t.ppq - 1e-12) continue;
            const int offset = std::clamp ((int) std::llround ((when - t.ppq) * samplesPerQuarter), 0, numSamples - 1);
            applyDrive (k, s, ax, ay);
            releaseDue (k, offset, out, true);
            stepOn (k, offset, s, out);
            releaseDue (k, offset, out);
        }
        lastPpqEnd = ppqEnd;
        cur = nullptr;
    }

private:
    static constexpr float kKeepRatio = 0.5f;   // so gut muss die laufende Wendung mindestens passen, sonst wird gewechselt

    struct Active { uint8_t channel, note, out; long long endStep, startStep; };

    // Wo im Takt / in der Phrase / in der Wendung ein Schritt liegt
    struct Pos
    {
        long long k, bar, phrase; int pos, barInPhrase;
        int chordIdx; long long chordStart, chordEnd, phraseStart, phraseEnd;
        bool passing = false;   // Durchgangsakkord am Ende des Akkords
    };

    static long long floorDiv (long long a, long long b) { return a >= 0 ? a / b : -((-a + b - 1) / b); }

    const Wendung& W() const { return current == kCustomWendung ? custom : wendungAt (genre, current); }

    // ---------------------------------------------------------------- Dramaturgie
    static constexpr int kPulseTick = 100;   // Bass-Muster nur fuer den Puls-Einstieg: kurze Viertel auf dem Orgelpunkt

    long long barsSince (long long k) const { return floorDiv (k - sceneStep, meter.len); }

    // Fahrt: der klingende Punkt wandert von A (Punkt im Feld) nach B
    void applyDrive (long long k, Settings& s, float ax, float ay)
    {
        driveAY = ay;
        const double barsNow = (double) (k - sceneStep) / (double) meter.len;
        if (s.drive && ! drivePrev && driveSeen)   // waehrend der Wiedergabe eingeschaltet: ab dem naechsten Takt, vom Punkt aus
        {
            driveLatched = true;
            driveFromLatched = (int) std::ceil (barsNow - 1e-9);
        }
        if (! s.drive) { driveLatched = false; driveArrivedNow = false; }
        drivePrev = s.drive; driveSeen = true;
        if (s.drive)
        {
            if (driveLatched) s.driveFrom = driveFromLatched;
            driveArrivedNow = s.driveBars > 0 && barsNow - (double) s.driveFrom >= (double) s.driveBars;
            const bool routeFresh = ! driveTrajectory;
            const float amount = driveAmount (s, barsNow);
            const float progress = (float) std::clamp ((barsNow - s.driveFrom) / s.driveBars, 0.0, 1.0);
            driveProgressNow = (float) ((barsNow - s.driveFrom) / s.driveBars);
            const bool returning = s.driveCurve == CurveWave && progress > 0.5f;
            const float q = returning ? 1.0f - amount : amount;
            if (! driveTrajectory)
            {
                originX = ax; originY = ay;
                segmentX = returning ? s.driveX : ax; segmentY = returning ? s.driveY : ay;
                segmentQ = 0; segmentReturn = returning;
                observedBX = s.driveX; observedBY = s.driveY;
                segmentTargetX = returning ? originX : s.driveX; segmentTargetY = returning ? originY : s.driveY;
                driveTrajectory = true;
            }
            if (returning != segmentReturn)
            {
                segmentX = segmentQ >= 1.0f ? segmentX : segmentTargetX;
                segmentY = segmentQ >= 1.0f ? segmentY : segmentTargetY; segmentQ = 0;
                segmentTargetX = originX; segmentTargetY = originY; segmentReturn = returning;
            }
            auto fraction = [&] { return std::clamp ((q - segmentQ) / std::max (1.0e-6f, 1.0f - segmentQ), 0.0f, 1.0f); };
            if (s.driveX != observedBX || s.driveY != observedBY)
            {
                if (! returning)
                {
                    const float f = fraction();
                    segmentX += (segmentTargetX - segmentX) * f; segmentY += (segmentTargetY - segmentY) * f;
                    segmentQ = q; segmentTargetX = s.driveX; segmentTargetY = s.driveY;
                }
                observedBX = s.driveX; observedBY = s.driveY;
            }
            const float f = fraction();
            s.x = segmentX + (segmentTargetX - segmentX) * f;
            s.y = segmentY + (segmentTargetY - segmentY) * f;
            if (driveArrivedNow) { s.x = returning ? originX : s.driveX; s.y = returning ? originY : s.driveY; }
            if (s.route.active())
            {
                if(routeFresh){routeBX=s.driveX;routeBY=s.driveY;routeCorrection={};routeCorrectionStart=0;}
                if(returning)routeCorrection={};
                if(!returning && (routeBX!=s.driveX || routeBY!=s.driveY)){
                    auto old=s.route.at(amount,{originX,originY},{routeBX,routeBY});
                    auto next=s.route.at(amount,{originX,originY},{s.driveX,s.driveY});
                    float fade=std::clamp((1-amount)/std::max(1e-6f,1-routeCorrectionStart),0.f,1.f);
                    routeCorrection={old.x+routeCorrection.x*fade-next.x,old.y+routeCorrection.y*fade-next.y};
                    routeCorrectionStart=amount;routeBX=s.driveX;routeBY=s.driveY;
                }
                auto p = s.route.at (amount, {originX,originY}, {routeBX,routeBY});
                float fade=std::clamp((1-amount)/std::max(1e-6f,1-routeCorrectionStart),0.f,1.f);
                s.x=std::clamp(p.x+routeCorrection.x*fade,0.f,1.f);s.y=std::clamp(p.y+routeCorrection.y*fade,0.f,1.f);
            }
        }
        else { s.x = ax; s.y = ay; }
        curX = s.x; curY = s.y;
    }

    // Platz einer Ebene in der Reihenfolge des Einstiegs (stumme Ebenen zaehlen nicht mit); m = Anzahl der Plaetze
    static int orderIndex (const Settings& s, int e, int layer, int& m)
    {
        const int row = e == EntryAuto ? EntryPad : e;
        int idx = -1; m = 0;
        for (int i = 0; i < kNumLayers; ++i)
        {
            const int l = kEntryOrder[row][i];
            if (! muteSoloOk (s, l)) continue;
            if (l == layer) idx = m;
            ++m;
        }
        return idx;
    }
    // Takt, an dem Platz i von m einsetzt (verteilt auf span Takte; der letzte im letzten Takt des Aufbaus)
    static long long slotBar (int i, int m, int span)
    {
        return (m <= 1 || span <= 1 || i <= 0) ? 0 : (long long) std::lround ((double) i * (double) (span - 1) / (double) (m - 1));
    }

    // Was klingt jetzt: Traegheit, Aufbau, Ausduennen, Ende. Setzt on[], gain[], boost[] und die Sonderfaelle des Einstiegs.
    void updateScene (long long k, const Pos& p, const Settings& s, bool fresh, int offset, EventList& out)
    {
        const long long bs = barsSince (k);
        const bool barStart = p.pos == 0;
        sceneBarNow = (int) std::clamp (bs, 0LL, 1LL << 30);
        const long long autoKey = ((long long) s.seed << 12) ^ ((long long) s.variation << 2) ^ (long long) s.genre;
        if (fresh || autoKey != autoSeed) { autoValue = autoEntry (s); autoSeed = autoKey; }
        const int e = s.entry == EntryAuto ? autoValue : s.entry;
        entryInUse = e;
        const int L = s.buildBars;
        const bool building = s.scene && e != EntryAll && bs < L;
        const int first = building ? kEntryLayer[e] : -1;

        if (s.endRequested && ! endWasRequested && manualEndStep < 0)
            manualEndStep = k + (s.ending == EndFade ? 2LL * meter.len : 0);
        endWasRequested = s.endRequested;
        const bool hasEnd = s.sceneBars > 0 || manualEndStep >= 0;
        sceneEndStep = s.sceneBars > 0 ? sceneStep + (long long) s.sceneBars * meter.len : (1LL << 60);
        if (manualEndStep >= 0) sceneEndStep = std::min (sceneEndStep, manualEndStep);
        const int T = manualEndStep >= 0 ? 2 : std::clamp (std::min (L, s.sceneBars / 2), 1, 64);   // Takte zum Ausduennen / Steigern vor dem Ende
        const long long left = hasEnd ? (sceneEndStep - k + meter.len - 1) / meter.len : (1LL << 30);   // Takte bis zum Ende, der laufende mitgezaehlt
        if (manualEndStep >= 0 && k >= sceneEndStep) manualFinished=true;
        sceneEnded = manualFinished || (hasEnd && k >= sceneEndStep);

        // Traegheit: ein nur auf Taktanfaengen, aus erst deutlich unter der Schwelle und nach mindestens zwei Takten
        for (int l = 0; l < kNumLayers; ++l)
        {
            if (fresh) { hOn[l] = levelOn (s, l); hSince[l] = k; prevOn[l] = false; continue; }
            if (! s.inertia || ! barStart) continue;
            if (! hOn[l] && levelOn (s, l)) { hOn[l] = true; hSince[l] = k; }
            else if (hOn[l] && levelOff (s, l) && k - hSince[l] >= 2LL * meter.len) hOn[l] = false;
        }

        int m = 0;
        orderIndex (s, e, kFlaeche, m);
        for (int l = 0; l < kNumLayers; ++l)
        {
            const bool level = s.inertia ? hOn[l] : levelOn (s, l);
            bool v = muteSoloOk (s, l) && (level || l == first);
            int mm = 0;
            const int idx = orderIndex (s, e, l, mm);
            if (v && s.scene && e != EntryAll && idx >= 0 && bs < slotBar (idx, m, L)) v = false;              // Aufbau: noch nicht dran
            thinned[l] = v && hasEnd && s.ending == EndFade && idx > 0 && left <= slotBar (idx, m, T);       // was zuletzt kam, geht zuerst
            if (thinned[l] || sceneEnded) v = false;
            on[l] = v;
        }

        // Einsatz: weich eingeblendet oder hart gesetzt; beim Ausklingen leiser werdend
        const bool special = s.scene || s.inertia || hasEnd;
        for (int l = 0; l < kNumLayers; ++l)
        {
            enterNow[l] = false;
            if (on[l] && ! prevOn[l])
            {
                enterNow[l] = ! fresh && special;
                entryStep[l] = (s.scene || (s.inertia && ! fresh)) ? k : -(1LL << 50);
            }
            if (! on[l] && prevOn[l] && ! fresh && special) cut (l, k, thinned[l] ? k + meter.len : k, offset, out);
            prevOn[l] = on[l];

            // Haerte: unter der Mitte eingeblendet (ganz weich ueber zwei Takte), ueber der Mitte ein kraeftiger erster Anschlag
            const long long fadeLen = s.hardness < 0.5f ? (long long) std::lround ((0.5f - s.hardness) * 4.0f * (float) meter.len) : 0;
            const long long t = k - entryStep[l];
            gain[l] = (fadeLen > 0 && t >= 0 && t < fadeLen) ? (float) t / (float) fadeLen : 1.0f;
            if (! on[l] && exitUntil[l] > exitStep[l])
                gain[l] *= std::clamp ((float) (exitUntil[l] - k) / (float) (exitUntil[l] - exitStep[l]), 0.0f, 1.0f);
            boost[l] = (t == 0 && s.hardness > 0.5f) ? (int) std::lround ((s.hardness - 0.5f) * 28.0f) : 0;
            if (t == 0 && l == kBass && e == EntryBass && building) boost[l] += 14;   // Bass-Schlag: ein fetter Ton
        }

        // Dichte waechst im Aufbau; zum Ende hin duennt sie aus (ausklingend) oder steigt weiter (offen)
        dens = building ? 0.45f + 0.55f * std::clamp ((float) bs / (float) L, 0.0f, 1.0f) : 1.0f;
        yAdd = 0.0f;
        if (hasEnd && left > 0 && left <= T)
        {
            const float r = (float) (left - 1) / (float) T;   // knapp 1 ... 0 im letzten Takt
            if (s.ending == EndFade) { dens *= 0.45f + 0.55f * r; for (float& g : gain) g *= std::clamp ((float) (sceneEndStep - k) / (float) (T * meter.len), 0.0f, 1.0f); }
            if (s.ending == EndOpen) yAdd = 0.3f * (1.0f - r);
        }

        // Sonderfaelle des Einstiegs, solange die erste Ebene allein spielt (bzw. beim Puls: den ganzen Aufbau lang)
        const long long stage1 = slotBar (1, m, L);
        const bool stage0 = building && bs < stage1;
        padShy = stage0 && e == EntryPad;
        padGrow = s.scene && e == EntryPad && stage1 > 0 && bs == stage1 && barStart && on[kFlaeche];
        bassOverride = (building && e == EntryPulse) ? kPulseTick : (stage0 && e == EntryBass) ? (int) BassHeld : -1;
        akzentForced = stage0 && e == EntryAkzent;

        // Vorbereiten: vor dem harten Ende und vor dem Ziel einer Fahrt nach oben zieht sich der Bass zurueck,
        // ein Stich kuendigt an; am Ziel selbst setzen alle Ebenen kraeftig neu ein
        bool prep = hasEnd && s.ending == EndHard && bs == (long long) s.sceneBars - 1;
        peak = false;
        if (s.drive && s.driveY - driveAY >= 0.2f)
        {
            const long long arrive = s.driveFrom + (s.driveCurve == CurveWave ? s.driveBars / 2 : s.driveBars);
            if (arrive > 0 && bs == arrive - 1) prep = true;
            if (bs == arrive && barStart) { peak = true; for (int& b : boost) b += 10; }
        }
        const int lastGroup = meter.groupStart[std::max (0, meter.numGroups - 1)];
        bassRest = prep && p.pos >= meter.len / 2;
        prepStich = prep && lastGroup > 0 && p.pos == lastGroup;
        if (prep && ! fresh && p.pos == meter.len / 2) cut (kBass, k, k, offset, out);
    }

    // Toene einer Ebene beenden: sofort (until <= k) oder spaetestens bei until
    void cut (int layer, long long k, long long until, int offset, EventList& out)
    {
        exitStep[layer] = k; exitUntil[layer] = until;
        for (int i = 0; i < numActive;)
        {
            auto& a = active[(size_t) i];
            if (kOutputLayer[a.out] != layer) { ++i; continue; }
            if (until <= k)
            {
                removeActive (i, offset, out);
                continue;
            }
            a.endStep = std::min (a.endStep, until);
            ++i;
        }
    }

    // Hartes Ende: ein kurzer, kraeftiger Schlag auf dem Grundakkord der Tonart, dann Stille
    void finalHit (const Pos& p, const Settings& s, int offset, EventList& out)
    {
        forceOn = true;
        const bool minor = kShapes[std::clamp (W().ch[0].type, 0, kNumChordTypes - 1)].minor;
        const int v = (int) (96 + 20 * s.hardness);
        if (muteSoloOk (s, kFlaeche))
        {
            const int r = place (s.key, padLow (s) - 12);
            for (int n : { r, r + 7, r + 12 + (minor ? 3 : 4), r + 19 }) noteOn (OutPadShort, n, v - 6, p.k + 2, offset, out);
        }
        if (muteSoloOk (s, kBass)) noteOn (OutBassShort, place (s.key, bassLow (s)), v, p.k + 2, offset, out);
        if (muteSoloOk (s, kAkzent)) noteOn (OutStich, stichTone (s, s.key), v, p.k + 2, offset, out);
        forceOn = false;
    }

    // ---------------------------------------------------------------- Szenenmotiv
    // Candidate for the first actual introduction. Later returns use recorded MIDI material.
    struct Motif { int n = 0; int on[5] {}; int deg[5] {}; };
    Motif motifFor (const Settings& s, long long phrase) const
    {
        static constexpr int rhythms[7][6] = { { 4, 0, 6, 8, 16, 0 }, { 5, 0, 4, 8, 12, 16 }, { 4, 0, 2, 4, 16, 0 }, { 5, 0, 8, 12, 14, 16 },
                                               { 4, 0, 12, 16, 24, 0 }, { 5, 0, 3, 4, 8, 16 }, { 3, 0, 8, 16, 0, 0 } };
        static constexpr int contours[6][4] = { { 1, 1, -1, -1 }, { 2, -1, -1, 1 }, { -1, 2, 1, -1 }, { 1, 2, -1, -2 }, { 1, -2, 1, 2 }, { -1, -1, 2, 1 } };
        const uint32_t h = hash3 ((uint32_t) s.seed, (uint32_t) s.variation, 1409u);
        const int* r = rhythms[h % 7];
        const int* c = contours[(h / 7) % 6];
        const int q = (int) (((phrase - phraseOf (sceneStep)) % 4 + 4) % 4);
        Motif mo;
        mo.n = r[0];
        int d = 1 + (int) ((h / 42) % 3) + (q == 1 ? 1 : q == 2 ? 2 : 0);
        for (int i = 0; i < mo.n; ++i)
        {
            if (i > 0) d += (q == 2 ? -1 : 1) * c[i - 1];
            mo.on[i] = r[i + 1];
            mo.deg[i] = d;
        }
        if (q == 3) mo.deg[mo.n - 1] += 2;
        return mo;
    }

    // Leiter der Akkordtoene fuer die Gegenstimme (zwei Oktaven ab ihrer Lage, im Tonumfang)
    int counterLadder (const Chord& c, const Settings& s, int* out) const
    {
        const ChordShape& sh = kShapes[c.type];
        int a = 62 + (int) std::lround (s.x * 3.0f), b = a + 24;
        const int ri = kOutputRange[OutCounter];
        if (s.rangeOn[ri])
        {
            const int rlo = s.rangeLo[ri] - 12 * s.octave[kGegenstimme], rhi = s.rangeHi[ri] - 12 * s.octave[kGegenstimme];
            a = std::max (a, rlo); b = std::min (b, rhi);
            if (b - a < 7) { a = rlo; b = rhi; }
        }
        const int rootPc = (s.key + c.root) % 12;
        int n = 0;
        for (int m = a; m <= b && n < 16; ++m)
            for (int i = 0; i < sh.n; ++i)
                if ((rootPc + sh.iv[i]) % 12 == ((m % 12) + 12) % 12) { out[n++] = m; break; }
        if (n == 0) out[n++] = place (s.key + c.root, a);
        return n;
    }

    // Spielt das Motiv, solange der Schritt in seinen zwei Takten liegt (dann true: die normale Linie pausiert)
    bool motifStep (long long k, const Pos& p, const Settings& s, int offset, EventList& out)
    {
        const long long span = std::min ((long long) 2 * meter.len, p.phraseEnd - p.phraseStart);
        const long long rel = k - p.phraseStart;
        const long long section=p.phrase-phraseOf(sceneStep);
        if(rel>=span||(motifMemory.count&&section!=motifMemory.introduction))motifMemory.finish();
        // A complete intervening phrase contains no counter motif or fallback line.
        if(motifMemory.complete)
        {
            if((section!=motifMemory.introduction&&!motifMemory.recall(section))||rel<0||rel>=span)return true;
            const auto& memory=motifMemory;
            int ladder[16];const int nl=counterLadder(chordFor(p,kGegenstimme,s),s,ladder);
            // Retain original contour/intervals; nearest available chord tones adapt harmony.
            const int base=composition::adaptMotifPitch(memory.origin-12*octaveOf(OutCounter),ladder,nl);
            for(int i=0;i<memory.count;++i)
            {
                const auto& n=memory.notes[static_cast<size_t>(i)];if(n.at!=rel)continue;
                const int note=composition::adaptMotifPitch(base+n.interval,ladder,nl);
                noteOn(OutCounter,note,n.velocity,
                    p.phraseStart+n.at+memory.recalledLength(i,section,span),offset,out);
                releaseOthers(OutCounter,note,offset,out);csNote=note;csPendingAt=-1;
            }
            return true;
        }
        // Only an introduction can populate memory. A fresh seek into a later section
        // cannot fabricate a performance that never happened.
        if(rel<0||rel>=span)return false; // Before an introduction, retain the ordinary line.
        if(motifMemory.count&&motifMemory.introduction!=section)motifMemory.clear();

        const Motif mo = motifFor (s, p.phrase);
        const float yc = layerY (s, kGegenstimme);
        const int count = yc >= 0.55f ? mo.n : yc >= 0.3f ? std::max (2, mo.n - 1) : std::max (2, mo.n - 2);
        for (int i = 0; i < count; ++i)
        {
            const long long at = (long long) mo.on[i] * meter.len / 16;
            if (at != rel) continue;
            long long end = i + 1 < count ? (long long) mo.on[i + 1] * meter.len / 16 : span;
            end = std::min (end, p.phraseEnd - p.phraseStart);
            const Chord c = chordFor (p, kGegenstimme, s);
            int ladder[16];
            const int nl = counterLadder (c, s, ladder);
            const int note = ladder[std::clamp (mo.deg[i], 0, nl - 1)];
            const long long length=std::min(span,end+tail(end-at))-at;
            const int before=out.size;
            noteOn (OutCounter, note, (int) (56 + 35 * yc) + (i == 0 ? 6 : 0), p.phraseStart + at + length, offset, out);
            for(int e=before;e<out.size;++e)
            {
                const auto& emitted=out.events[static_cast<size_t>(e)];
                if(emitted.out==OutCounter&&emitted.type==0&&emitted.velocity>0)
                    motifMemory.observe(emitted.note,at,length,section,static_cast<int>(56+35*yc)+(i==0?6:0));
            }
            releaseOthers (OutCounter, note, offset, out);
            csNote = note; csPendingAt = -1;
        }
        return true;
    }

    double swingDelay (long long k, const Settings& s) const
    {
        if (s.swing <= 0.0f) return 0.0;
        const int p = (int) (((k % 4) + 4) % 4);
        if (p == 2) return 0.667 * s.swing;
        if (p == 1 || p == 3) return 0.333 * s.swing;
        return 0.0;
    }

    long long phraseOf (long long k) const { return floorDiv (floorDiv (k, meter.len), phraseBars); }

    Pos locate (long long k) const
    {
        Pos p;
        p.k = k;
        p.bar = floorDiv (k, meter.len);
        p.pos = (int) (k - p.bar * meter.len);
        p.phrase = floorDiv (p.bar, phraseBars);
        p.barInPhrase = (int) (p.bar - p.phrase * phraseBars);
        p.phraseStart = p.phrase * phraseBars * meter.len;
        p.phraseEnd = p.phraseStart + (long long) phraseBars * meter.len;
        const Wendung& w = W();
        composition::ChordTimeline timeline;
        timeline.count=w.n;timeline.first=chordBase;timeline.held=still;
        timeline.begin=std::max(wendungStart,p.phraseStart);timeline.end=p.phraseEnd;
        for(int i=0;i<w.n;++i)timeline.durations[static_cast<size_t>(i)]=static_cast<int64_t>(w.ch[i].bars)*meter.len;
        const auto position=composition::locateChord(timeline,k);
        p.chordIdx=position.index;p.chordStart=position.begin;p.chordEnd=position.end;
        if(still)return p;
        if (cur != nullptr)
        {
            const auto intent=composition::freeTransition(nextChordRoot(p),cur->passing,cur->y);
            const auto transition=composition::placeTransition(intent,p.chordStart,p.chordEnd,
                meter.len,meter.groupStart[std::max(0,meter.numGroups-1)]);
            if(transition.present)
            {
                if(k>=transition.begin){p.chordStart=transition.begin;p.passing=true;}
                else p.chordEnd=transition.begin;
            }
        }
        return p;
    }

    void ensurePhrase (long long phrase, const Settings& s)
    {
        if (phrase == phraseIndex) return;
        if (! still) { current = s.custom ? kCustomWendung : pick (s, phrase); chordBase = 0; }
        if (s.custom) style = pick (s, phrase);
        phraseIndex = phrase;
        wendungStart = phrase * phraseBars * meter.len;
    }

    bool isChangePoint (const Pos& p, const Settings& s) const
    {
        switch (s.change)
        {
            case ChangeBeat:  return meter.isGroupStart (p.pos);
            case ChangeBar:   return p.pos == 0;
            case Change2Bars: return p.pos == 0 && p.barInPhrase % 2 == 0;
            default:          return p.pos == 0 && p.barInPhrase % 4 == 0;
        }
    }

    // Wechsel auf eine neue Wendung, wenn die laufende nicht mehr zur Lage passt (Hysterese ueber kKeepRatio)
    // Ruhezone: ganz unten im Feld (Intensitaet) bleibt der Akkord stehen; gewechselt wird nur auf Wechselpunkten
    bool updateStill (long long k, const Pos& p, const Settings& s)
    {
        if (current < 0 || ! isChangePoint (p, s)) return false;
        const bool want = still ? s.y < kStillOut : s.y < kStillIn;
        if (want == still) return false;
        still = want;
        if (still) chordBase = p.chordIdx;   // der gerade klingende Akkord bleibt
        wendungStart = k;                    // beim Verlassen laeuft die Folge von diesem Akkord an weiter
        return true;
    }

    bool maybeSwitch (long long k, const Pos& p, const Settings& s)
    {
        if (still || k == p.phraseStart || ! isChangePoint (p, s)) return false;
        if (current == kCustomWendung)   // eigene Folge: nur der geliehene Stil wechselt, die Akkorde bleiben
        {
            if (style < 0 || weight (wendungAt (genre, style), s) < std::min (kKeepRatio, keepRatio (s)) * bestWeight (s)) style = pick (s, k * 7 + 3);
            return false;
        }
        if (s.custom) return false;
        if (weight (wendungAt (genre, current), s) >= std::min (kKeepRatio, keepRatio (s)) * bestWeight (s)) return false;
        current = pick (s, k * 7 + 3);
        wendungStart = k;
        return true;
    }

    const Wendung& SW() const { return current == kCustomWendung ? wendungAt (genre, style) : W(); }

    int nextChordRoot (const Pos& p) const
    {
        const Wendung& w = W();
        return (p.chordIdx + 1 < w.n ? w.ch[p.chordIdx + 1] : w.ch[0]).root;
    }

    Chord chordFor (const Pos& p, int layer, const Settings& s) const
    {
        const Wendung& w = W();
        if (p.passing && (layer > kArp || s.follow[layer]))
            return Chord { composition::freeTransition(nextChordRoot(p),true,1.f).approachRoot, Dom7, 1 };
        if (layer <= kArp && ! s.follow[layer])
        {
            Chord tonic = w.ch[0]; tonic.root = current == kCustomWendung ? w.ch[0].root : 0;
            tonic.bass = -1;
            if (layer != kFlaeche) tonic.type = kShapes[w.ch[0].type].minor ? Min : Maj; // keep pad colour even when harmony following is disabled
            return tonic;
        }
        return w.ch[p.chordIdx];
    }

    static int bassRoot (const Chord& c) { return c.bass >= 0 ? c.bass : c.root; }
    int pedalRoot() const { return bassRoot (W().ch[0]); }

    int nextRoot (const Pos& p) const
    {
        const Wendung& w = W();
        return bassRoot (p.chordIdx + 1 < w.n ? w.ch[p.chordIdx + 1] : w.ch[0]);
    }

    // Unruhe faerbt einfache Dreiklaenge; explizite Sept-/Nonenqualitaeten bleiben erhalten.
    static int padType (int type, float z)
    {
        if (z >= 0.75f && (type == Min || type == MinMaj7)) return MinMaj9;
        if (z >= 0.45f)
        {
            if (type == Min) return MinMaj7;
            if (type == Maj) return Maj7;
        }
        return type;
    }

    static int place (int note, int low)
    {
        while (note < low) note += 12;
        while (note >= low + 12) note -= 12;
        return note;
    }

    int hashInt (uint32_t salt, long long a) const { return (int) (hash3 ((uint32_t) cur->variation, (uint32_t) a, salt) & 0x7fffffff); }

    int chooseArp (const Settings& s, long long phrase) const
    {
        if (s.arpFigure != ArpAuto) return s.arpFigure;
        return SW().arp[hashInt (31u, phrase) % 2];
    }
    int chooseBass (const Settings& s, long long phrase) const
    {
        if (bassOverride >= 0) return bassOverride;   // Einstieg: Bass-Schlag (gehalten) oder Puls
        if (s.bassPattern != BassAuto) return s.bassPattern;
        const float y = layerY (s, kBass);
        if (y < 0.15f) return BassHeld;                       // ganz duenn: lange Toene
        if (y > 0.92f) return BassEighth;                     // ganz dicht: Achtel nageln
        int pref = SW().bass[hashInt (47u, phrase) % 2];
        if (y < 0.3f && pref != BassHeld && pref != BassPedal) pref = BassHalf;   // ausduennen
        if (y > 0.8f && (pref == BassHeld || pref == BassHalf || pref == BassQuarter || pref == BassPedal)) return BassEighth;
        return pref;
    }
    int pattern0 (const Settings& s, long long phrase) const { return chooseBass (s, phrase); }

    int choosePad (const Settings& s) const
    {
        if (padShy) return PadHeld;                   // Einstieg: ein stehender Ton
        if (s.padPattern != PadAuto) return s.padPattern;
        const float y = layerY (s, kFlaeche);
        return y < 0.3f ? PadHeld : SW().pad;
    }

    void removeActive (int i, int offset, EventList& out)
    {
        const auto a = active[(size_t) i];
        active[(size_t) i] = active[(size_t) --numActive];
        for (int j = 0; j < numActive; ++j)
            if (active[(size_t) j].channel == a.channel && active[(size_t) j].note == a.note) return;
        out.add (offset, a.channel, a.note, 0, a.out);
    }

    void releaseDue (long long step, int offset, EventList& out, bool deferPadBoundary = false)
    {
        for (int i = 0; i < numActive;)
        {
            const auto& claim = active[(size_t) i];
            if (claim.endStep <= step && ! (deferPadBoundary && claim.endStep == step && claim.out == OutPadLong))
            {
                removeActive (i, offset, out);
            }
            else ++i;
        }
    }

    void releaseSilencedLayers (const Settings& s, EventList& out)
    {
        for (int i = 0; i < numActive;)
        {
            const int l = kOutputLayer[active[(size_t) i].out];
            if (active[(size_t) i].channel != s.channel[active[(size_t) i].out] || ! muteSoloOk (s, l) || (! s.inertia && ! s.scene && s.sceneBars <= 0 && ! levelOn (s, l)))
            {
                removeActive (i, 0, out);
            }
            else ++i;
        }
    }

    // Beim Wechsel der Wendung: gehaltene Toene der alten Stimmung sofort beenden
    void releaseHeld (int offset, EventList& out, bool keepPad = false)
    {
        for (int i = 0; i < numActive;)
        {
            if (keepPad && active[(size_t) i].out == OutPadLong) active[(size_t) i].endStep = std::min (active[(size_t) i].endStep, nowStep);
            const int layer = kOutputLayer[active[(size_t) i].out];
            if ((layer == kFlaeche && ! (keepPad && active[(size_t) i].out == OutPadLong)) || layer == kBass || layer == kAkzent)
            {
                removeActive (i, offset, out);
            }
            else ++i;
        }
    }

    // Tonumfang: Ton um ganze Oktaven in den spielbaren Bereich holen (gleicher Tonname, kein Ton faellt weg).
    // Ist der Bereich enger als eine Oktave und der Tonname passt nicht hinein, nimmt ein Akkordton im Bereich seinen Platz ein.
    // Alles ist nach Ausgang geschluesselt: Oktave nach Ebene, Tonumfang nach Ebene (Akzent: Tupfer und Stich getrennt).
    bool rangeOn (int o) const { return cur != nullptr && cur->rangeOn[kOutputRange[o]]; }
    int octaveOf (int o) const { return cur != nullptr ? cur->octave[kOutputLayer[o]] : 0; }
    int fitRange (int o, int note) const
    {
        if (! rangeOn (o)) return note;
        const int lo = cur->rangeLo[kOutputRange[o]], hi = cur->rangeHi[kOutputRange[o]];
        int n = note;
        while (n < lo) n += 12;
        while (n > hi) n -= 12;
        if (n >= lo) return n;
        int best = -1, bestD = 1000;
        for (int m = lo; m <= hi; ++m)
            if ((chordMask >> (m % 12)) & 1)
            {
                const int d = std::min (std::abs (m - n), std::abs (m - (n + 12)));
                if (d < bestD) { bestD = d; best = m; }
            }
        return best >= 0 ? best : std::clamp (note, lo, hi);
    }
    // Klingender Ton eines Ausgangs: Oktav-Einstellung, dann Tonumfang
    int sounding (int o, int note) const
    {
        if (cur != nullptr) note = fitRange (o, note + 12 * octaveOf (o));
        return std::clamp (note, 0, 127);
    }
    // Eine Gruppe von Toenen (Akkord, Arpeggio) als Ganzes um Oktaven verschieben, so dass moeglichst viele in den Bereich passen
    int bestShift (int o, const int* notes, int n) const
    {
        if (! rangeOn (o) || n <= 0) return 0;
        const int lo = cur->rangeLo[kOutputRange[o]] - 12 * octaveOf (o), hi = cur->rangeHi[kOutputRange[o]] - 12 * octaveOf (o);
        int best = 0, bestCount = -1;
        for (int sh : { 0, 12, -12, 24, -24, 36, -36, 48, -48 })
        {
            int c = 0;
            for (int i = 0; i < n; ++i) c += (notes[i] + sh >= lo && notes[i] + sh <= hi) ? 1 : 0;
            if (c > bestCount) { bestCount = c; best = sh; }
        }
        return best;
    }
    // Verschieben, Ausreisser falten, sortieren, doppelte entfernen; liefert die neue Anzahl
    int fitGroup (int o, int* notes, int n) const
    {
        if (! rangeOn (o)) return n;
        const int sh = bestShift (o, notes, n);
        const int oct = 12 * octaveOf (o);
        for (int i = 0; i < n; ++i) notes[i] = fitRange (o, notes[i] + sh + oct) - oct;
        std::sort (notes, notes + n);
        return (int) (std::unique (notes, notes + n) - notes);
    }

    // Note anschlagen. Mehrere Ausgaenge duerfen auf demselben Kanal liegen: Trifft ein Ton auf einen schon klingenden
    // gleichen Ton desselben Kanals, wird er im selben Schritt nur verlaengert, sonst neu angeschlagen. Jeder Ausgang
    // behaelt seinen eigenen Anspruch; erst das Ende des letzten Anspruchs beendet die physische MIDI-Note.
    void noteOn (int o, int note, int velocity, long long endStep, int offset, EventList& out)
    {
        const int layer = kOutputLayer[o];
        if (cur != nullptr && ! forceOn && ! on[layer]) return;
        const int channel = cur != nullptr ? cur->channel[o] : o + 1;
        note = (o == OutStich && cur != nullptr && cur->stichFixed) ? std::clamp (note, 0, 127) : sounding (o, note);
        if (! forceOn) velocity = (int) std::lround ((float) velocity * (cur != nullptr && cur->dynamics && cur->ccExpression > 0 ? 1.0f : (0.6f + 0.4f * gain[layer]))) + boost[layer];
        velocity = std::clamp (velocity, 1, 127);
        int own = -1; bool existing = false, sameStep = false;
        for (int i = 0; i < numActive; ++i)
        {
            const auto& a = active[(size_t) i];
            if (a.channel != channel || a.note != note) continue;
            existing = true; sameStep = sameStep || a.startStep == nowStep;
            if (a.out == o) own = i;
        }
        if (own < 0 && numActive >= kMaxActive) return;
        if (! existing || (! sameStep && ! extendOnly))
        {
            if (existing) out.add (offset, channel, note, 0, o);
            out.add (offset, channel, note, velocity, o);
            // One physical attack for all claims at this time.
            for (int i = 0; i < numActive; ++i)
                if (active[(size_t) i].channel == channel && active[(size_t) i].note == note) active[(size_t) i].startStep = nowStep;
        }
        if (own >= 0)
        {
            auto& a = active[(size_t) own];
            a.endStep = (sameStep || extendOnly) ? std::max (a.endStep, endStep) : endStep;
            a.startStep = nowStep;
        }
        else active[(size_t) numActive++] = { (uint8_t) channel, (uint8_t) note, (uint8_t) o, endStep, nowStep };
    }

    void updateMask (const Settings& s)
    {
        const ChordShape& sh = kShapes[std::clamp (curType, 0, kNumChordTypes - 1)];
        chordMask = 0;
        for (int i = 0; i < sh.n; ++i) chordMask |= 1u << (unsigned) ((s.key + curRoot + sh.iv[i]) % 12);
    }

    int jitter (long long k, int layer, int range) const
    {
        return (int) (hash3 ((uint32_t) cur->variation, (uint32_t) k, (uint32_t) layer) % (uint32_t) (2 * range + 1)) - range;
    }

    static int padLow (const Settings& s)  { return 62 + (int) std::lround (s.x * 6.0f); }   // Flaeche: mittlere Lage
    static int bassLow (const Settings& s) { return 45 + (int) std::lround (s.x * 4.0f); }   // Bass: A2 bis Cis3

    // --- Flaeche (o: lang fuer gehaltene Akkorde, kurz fuer Schlaege, Puls, Staccato und Gated)
    void resetVoicing() { planValid = false; unavailablePad = 0; }

    // A bounded cyclic plan is a function of the harmonic vocabulary, register and variation.
    // It has no "last played notes" memory: seek, loop, offline export and block size agree.
    void prepareVoicingPlan (const Pos& p, const Settings& s)
    {
        const int o = OutPadLong, oct = 12 * octaveOf (o);
        const int lo = rangeOn (o) ? s.rangeLo[0] - oct : std::max (-oct, padLow (s) - 18);
        const int hi = rangeOn (o) ? s.rangeHi[0] - oct : std::min (127 - oct, padLow (s) + 24);
        const int blo = s.rangeOn[1] ? s.rangeLo[1] - 12 * s.octave[kBass] : bassLow (s) - 7;
        const int bhi = s.rangeOn[1] ? s.rangeHi[1] - 12 * s.octave[kBass] : bassLow (s) + 12;
        composition::HarmonicRequest request;
        request.padRange = { lo, hi }; request.bassRange = { blo, bhi };
        request.count = W().n * 2;
        Chord chords[16] {};
        int order[16] {}, count = 0;
        uint64_t key = 1469598103934665603ull;
        auto mix = [&] (int n) { key ^= (uint64_t) (uint32_t) n; key *= 1099511628211ull; };
        mix (lo); mix (hi); mix (blo); mix (bhi); mix (current); mix (genre);
        const auto& w = W(); long long start = std::max (p.phraseStart, wendungStart);
        for (int i = 0; i < w.n; ++i)
        {
            for (int pass = 0; pass < 2; ++pass)
            {
                const int index = i * 2 + pass;
                auto& slot = request.slots[static_cast<size_t> (index)];
                Chord c = w.ch[i];
                if (pass) c = { composition::freeTransition(i+1<w.n?w.ch[i+1].root:w.ch[0].root,true,1.f).approachRoot, Dom7, 1 };
                Chord pad = c, bass = c;
                if (! s.follow[kFlaeche]) { pad = w.ch[0]; pad.root = s.custom ? pad.root : 0; }
                if (! s.follow[kBass]) { bass = w.ch[0]; bass.root = s.custom ? bass.root : 0; bass.type = kShapes[bass.type].minor ? Min : Maj; bass.bass = -1; }
                chords[index] = pad; mix (pad.root); mix (pad.type);
                const auto& shape=kShapes[padType(pad.type,s.z)];
                composition::ChordIntent intent;
                intent.root=s.key+pad.root;intent.bassPitchClass=s.key+bassRoot(bass);
                intent.count=shape.n;for(int n=0;n<shape.n;++n)intent.intervals[static_cast<size_t>(n)]=shape.iv[n];
                intent.quartal=pad.type==Quartal;
                intent.protectedLine=s.genre==GenrePopRock&&current==31;
                intent.voicing=current==kCustomWendung?hashInt(91u,start)%3:0;
                intent.padLow=padLow(s);intent.bassLow=bassLow(s);intent.intensity=layerY(s,kFlaeche);
                slot=composition::buildAnchor(intent,{lo,hi},rangeOn(o));
                mix(slot.pad.n);for(int n=0;n<slot.pad.n;++n)mix(slot.pad.notes[n]);
                mix(slot.bass);mix(static_cast<int>(slot.unavailable));
                slot.enabled = ! pass || (composition::freeTransition(0,s.passing,s.y,still).kind==composition::TransitionKind::passingDominant);
                slot.preservePad = s.genre == GenrePopRock && current == 31 && ! s.custom;
                mix(slot.preservePad);
                if (slot.enabled) order[count++] = index;
            }
            if (i >= chordBase) start += (long long) w.ch[i].bars * meter.len;
        }
        mix (count); for (int i = 0; i < count; ++i) mix (order[i]);
        if (planValid && planKey == key) return;
        // Adapter supplies chord facts; core derives the existing resolution intent.
        for (int j = 0; j < count; ++j)
        {
            const int index = order[j], prev = order[(j + count - 1) % count];
            request.slots[static_cast<size_t>(index)].resolution=composition::dominantResolution(
                chords[prev].root,chords[prev].type==Dom7||chords[prev].type==Dom7b9,
                chords[index].root,s.key);
        }
        harmonicPlan = composition::planHarmony(request);
        planValid = harmonicPlan.valid; planKey = key;
    }

    voiceleading::ChordVoicing padVoicing (const Pos& p, const Settings& s, int)
    {
        prepareVoicingPlan (p, s);
        const int index = p.chordIdx * 2 + (p.passing ? 1 : 0);
        unavailablePad = harmonicPlan.slots[static_cast<size_t> (index)].unavailable; return harmonicPlan.slots[static_cast<size_t> (index)].pad;
    }

    void padChord (const Pos& p, const Settings& s, int o, int offset, long long endStep, int velocity, EventList& out)
    {
        const auto voiced = padVoicing (p, s, o);
        const bool saved = extendOnly;
        if (o == OutPadLong && ! peak) extendOnly = true;
        const auto chord = chordFor (p, kFlaeche, s);
        const auto& shape = kShapes[padType (chord.type, s.z)];
        const int rootPc = (s.key + chord.root) % 12;
        int roots = 0, authoredRoots = 0, lastRoot = -1;
        for (int i = 0; i < shape.n; ++i) authoredRoots += shape.iv[i] % 12 == 0;
        for (int i = 0; i < voiced.n; ++i) if ((voiced.notes[i] % 12 + 12) % 12 == rootPc) { ++roots; lastRoot = i; }
        bool mainRoot = true;
        for (int i = 0; i < voiced.n; ++i)
        {
            const bool root = (voiced.notes[i] % 12 + 12) % 12 == rootPc;
            const int reduction = roots > authoredRoots && i == lastRoot ? 10 : root && mainRoot ? 0 : 4;
            noteOn (o, voiced.notes[i], velocity - reduction, endStep, offset, out);
            if (root) mainRoot = false;
        }
        extendOnly = saved;
        // Harmonic changes may leave an old colour note whose nominal duration has not ended yet.
        if (o == OutPadLong)
            for (int i = 0; i < numActive;)
            {
                const auto& a = active[(size_t) i]; bool wanted = false;
                for (int j = 0; j < voiced.n; ++j) wanted = wanted || a.note == sounding (o, voiced.notes[j]);
                if (a.out == o && ! wanted) removeActive (i, offset, out); else ++i;
            }
    }

    int bassPlacement (const Pos& p, const Settings& s, int anchor, bool pedal)
    {
        if (pedal) return anchor;
        prepareVoicingPlan (p, s);
        return harmonicPlan.slots[static_cast<size_t> (p.chordIdx * 2 + (p.passing ? 1 : 0))].bass;
    }

    int nextBassPlacement (const Pos& p, const Settings& s)
    {
        prepareVoicingPlan (p, s);
        const int index = !p.passing && composition::freeTransition(0,s.passing,s.y,still).kind==composition::TransitionKind::passingDominant
                        ? p.chordIdx * 2 + 1 : ((p.chordIdx + 1) % W().n) * 2;
        return harmonicPlan.slots[static_cast<size_t> (index)].bass;
    }

    // Bass: lange Muster (Gehalten, Halbe, Orgelpunkt) gehen auf den Kanal fuer lang, alle anderen auf den fuer kurz
    static int bassOut (int pattern) { return (pattern == BassHeld || pattern == BassHalf || pattern == BassPedal) ? OutBassLong : OutBassShort; }

    // --- Akzent. Zwei Stimmen, die nur gelegentlich einwerfen und nie stehen bleiben:
    // Tupfer: einzelne kurze Toene hoch ueber dem Satz (Celesta, Glocken, Pizzicato), auf Zwischenzeiten.
    // Stich: ein einzelner kurzer Schlag (Pauke, Trommel, Klavier, Synth-Stab), an den Nahtstellen
    // der Musik: bei Akkordwechseln, am Ende der Phrase und als Antwort kurz nach einem Tupfer. Wenig Intensitaet:
    // nur Tupfer; mehr: der Stich kommt dazu und antwortet; viel Intensitaet am Phrasenende: beide zugleich.
    // Alles haengt nur von der Position ab (kein Zustand), daher nach Spruengen und beim Herausziehen identisch.
    static int tupferLow (const Settings& s) { return (s.genre == GenrePopRock ? 84 : 79) + (int) std::lround (s.x * 5.0f); }
    static int stichLow (const Settings&)  { return 50; }

    bool tupferAt (long long k, const Settings& s) const
    {
        const float ya = layerY (s, kAkzent);
        if (ya < kLayerStart[kAkzent] && ! akzentForced) return false;
        const long long bar = floorDiv (k, meter.len);
        const int pos = (int) (k - bar * meter.len);
        if (pos % 2 != 0 || pos % 8 == 0 || meter.isGroupStart (pos)) return false;   // nur Zwischenzeiten
        const long long window = bar * 4 + pos / 8;                                   // hoechstens ein Tupfer je halben Takt
        const int slot = 2 + 2 * (hashInt (601u, window) % 3);
        if (pos % 8 != slot) return false;
        const float prob = 0.12f + 0.5f * ya + 0.15f * s.z + (akzentForced ? 0.3f : 0.0f);
        return (float) (hashInt (607u, window) % 1000) < prob * 1000.0f;
    }

    void tupfer (const Pos& p, const Settings& s, int offset, long long len, int boost, EventList& out)
    {
        const Chord c = chordFor (p, kAkzent, s);
        const ChordShape& sh = kShapes[c.type];
        int pick[4]; int n = 0;
        pick[n++] = 12;                                   // Oktave
        if (sh.n > 1) pick[n++] = sh.iv[1];               // Terz
        if (sh.n > 2) pick[n++] = sh.iv[2];               // Quinte
        if (s.x >= 0.35f && s.z < 0.6f) pick[n++] = 14;   // None, im Hellen
        const int iv = pick[hashInt (611u, p.k) % n];
        const float ya = layerY (s, kAkzent);
        noteOn (OutTupfer, place (s.key + c.root + iv, tupferLow (s)), (int) (45 + 40 * ya) + boost, p.k + len, offset, out);
    }

    // Unruhe: ein fremder, reibender Ton als kurzer Stachel in der Mitte des Akkords
    void foreignTone (const Pos& p, const Settings& s, int offset, EventList& out)
    {
        const Chord c = chordFor (p, kAkzent, s);
        const int interval = s.x < 0.5f ? 1 : 6;                          // dunkel: kleine None, hell: uebermaessige Quarte
        const int note = place (s.key + c.root + interval, 79);
        noteOn (OutTupfer, note, (int) (30 + 45 * s.z), p.k + 3, offset, out);
        if (s.z >= 0.8f && layerY (s, kAkzent) < 0.5f)                    // Halbton-Reibung ganz oben
            noteOn (OutTupfer, note + 11, (int) (25 + 30 * s.z), p.k + 3, offset, out);
    }

    // Stich: ein einzelner Schlag. Fest: die gewaehlte Taste. Akkord: der Grundton (MIDI 50 bis 61, unter der Gegenstimme).
    static int stichTone (const Settings& s, int pitch) { return s.stichFixed ? std::clamp (s.stichNote, 0, 127) : place (pitch, stichLow (s)); }
    void stich (const Pos& p, const Settings& s, int offset, long long len, int boost, EventList& out)
    {
        const Chord c = chordFor (p, kAkzent, s);
        const float ya = layerY (s, kAkzent);
        noteOn (OutStich, stichTone (s, s.key + bassRoot (c)), (int) (68 + 40 * ya) + boost, p.k + len, offset, out);
    }

    // Riss (ab 1.4): ganz oben in der Unruhe kurze, harte Stoesse aus zwei Toenen im Halbtonabstand hoch ueber dem Satz,
    // auf dem Kanal der kurzen Flaeche (Staccato-Streicher), wie die Streicher in Herrmanns "Psycho". Er waechst mit der
    // Unruhe: bei 80 % selten und leiser, bei 100 % haeufig, laut und doppelt; ganz oben kommt ein dritter Reibungston dazu.
    void riss (long long k, const Pos& p, const Settings& s, int offset, EventList& out)
    {
        if (s.z < kRissStart || ! muteSoloOk (s, kFlaeche)) return;
        const float r = std::clamp ((s.z - kRissStart) / (1.0f - kRissStart), 0.0f, 1.0f);
        const int half = std::max (2, meter.len / 2);                     // je halben Takt hoechstens ein Riss
        const long long w = floorDiv (k, half);
        const int inW = (int) (k - w * half);
        const int slot = 2 * (hashInt (701u, w) % std::max (1, half / 2));
        if ((float) (hashInt (709u, w) % 1000) >= (0.2f + 0.6f * r) * 1000.0f) return;
        const bool second = r >= 0.5f && inW == slot + 1;
        if (inW != slot && ! second) return;
        const Chord c = chordFor (p, kFlaeche, s);
        const int t = place (s.key + c.root + (hashInt (719u, w) % 2 == 0 ? 0 : 7), 84);
        const int v = (int) (72 + 48 * r) - (second ? 10 : 0);
        noteOn (OutPadShort, t, v, k + 1, offset, out);
        noteOn (OutPadShort, t + 1, v, k + 1, offset, out);
        if (r >= 0.75f) noteOn (OutPadShort, t + 13, v - 8, k + 1, offset, out);
    }

    void accents (long long k, const Pos& p, const Settings& s, int offset, EventList& out)
    {
        if (prepStich && muteSoloOk (s, kAkzent))   // Vorbereiten: ein Stich kuendigt den Wechsel an
        {
            forceOn = true; stich (p, s, offset, 2, 10, out); forceOn = false;
            return;
        }
        if (! on[kAkzent]) return;
        if (akzentForced && k == entryStep[kAkzent])   // Einstieg mit dem Akzent: ein Stich (hart) oder Tupfer (weich) in der Stille
        {
            if (cur->hardness >= 0.5f) stich (p, s, offset, 2, 8, out); else tupfer (p, s, offset, 2, 6, out);
            return;
        }
        const float ya = layerY (s, kAkzent);
        const bool lastBar = p.barInPhrase == phraseBars - 1;
        const int lastGroup = meter.groupStart[std::max (0, meter.numGroups - 1)];
        const bool phraseEnd = lastBar && p.pos == lastGroup && lastGroup > 0;    // Schlusspunkt der Phrase
        const bool both = phraseEnd && ya >= 0.8f;

        if (s.z >= kAkzentUnruhe && k == p.chordStart + (p.chordEnd - p.chordStart) / 2)
            foreignTone (p, s, offset, out);
        else if (both || tupferAt (k, s))
            tupfer (p, s, offset, ya > 0.7f ? 1 : 2, both ? 10 : 0, out);

        if (ya < kStichStart) return;
        bool hit = both || (phraseEnd && ya >= 0.6f);
        if (! hit && k == p.chordStart)
            hit = (float) (hashInt (613u, k) % 1000) < (0.25f + 0.45f * ya) * 1000.0f;
        if (! hit && ya >= 0.55f && tupferAt (k - 3, s))                       // Antwort auf den Tupfer
            hit = hashInt (617u, k) % 2 == 0;
        if (! hit && s.genre == GenrePopRock && p.pos % 8 == 6)                 // Pop-Rock: Stab auf der Zwischenzeit
            hit = (float) (hashInt (619u, k) % 1000) < (0.05f + 0.2f * ya) * 1000.0f;
        if (hit) stich (p, s, offset, s.genre == GenrePopRock ? 1 : 2, phraseEnd ? 8 : 0, out);
    }

    // Liegetoene einer Akkordposition (Flaeche gehalten, Bass gehalten)
    void sustained (const Pos& p, const Settings& s, int offset, EventList& out, bool restart, unsigned mask = 3u)
    {
        const int pad = choosePad (s);
        const bool padFollow = s.follow[kFlaeche];
        const bool phraseStart = p.k == p.phraseStart;
        if ((mask & 1u) && pad == PadHeld && (padFollow || phraseStart || restart))
            padChord (p, s, OutPadLong, offset, padFollow ? p.chordEnd : p.phraseEnd, (int) (40 + 45 * layerY (s, kFlaeche)), out);

        const int bp = chooseBass (s, p.phrase);
        if ((mask & 2u) && ((bp == BassHeld && (s.follow[kBass] || phraseStart || restart)) || bp == BassPedal))
        {
            const bool pedal = bp == BassPedal;
            noteOn (OutBassLong, bassPlacement (p, s, place (s.key + (pedal ? pedalRoot() : bassRoot (chordFor (p, kBass, s))), bassLow (s)), pedal),
                    (int) (60 + 35 * layerY (s, kBass)), (s.follow[kBass] && ! pedal) ? p.chordEnd : (pedal ? p.chordEnd : p.phraseEnd), offset, out);
        }
    }

    void chase (double ppq, const Settings& s, EventList& out)
    {
        if (ppq < 0.0) return;
        const long long k = (long long) std::floor (ppq / kStep + 1e-9);
        ensurePhrase (phraseOf (k), s);
        const Pos p = locate (k);
        curChord = p.chordIdx;
        curRoot = W().ch[p.chordIdx].root; curType = W().ch[p.chordIdx].type;
        nowStep = k; updateMask (s);
        updateScene (k, p, s, true, 0, out);
        if (sceneEnded) return;
        if (ppq > (double) p.chordStart * kStep + 1e-9)
            sustained (p, s, 0, out, true);
        else
            chaseStep = k;   // genau am Akkordanfang: der normale Schritt schlaegt an, auch die stehenden Ebenen
    }

    void stepOn (long long k, int offset, const Settings& s, EventList& out)
    {
        nowStep = k;
        const long long phrase = phraseOf (k);
        ensurePhrase (phrase, s);
        Pos p = locate (k);
        bool restart = k == chaseStep;
        if (updateStill (k, p, s))
        {
            releaseHeld (offset, out, true);  // Flaeche wird zielharmonisch abgeglichen; andere gehaltene Toene neu setzen, auf demselben Akkord
            p = locate (k);
            restart = true;
        }
        if (maybeSwitch (k, p, s))
        {
            releaseHeld (offset, out, true);  // gemeinsame Flaechentoene am Stimmungswechsel halten
            p = locate (k);
            restart = true;
        }
        chaseStep = -1;
        nowStep = k;
        updateScene (k, p, s, false, offset, out);
        if (sceneEnded)
        {
            if (k == sceneEndStep && (manualEndStep < 0 || !manualHitSent))
            {
                if(manualEndStep>=0)manualHitSent=true;
                allNotesOff (out, offset);
                if (s.ending == EndHard) finalHit (p, s, offset, out);
            }
            return;
        }
        // Dichte: im Aufbau duenner, zum Ende ausklingend duenner oder offen dichter (Schwellen bleiben beim Feld)
        if (dens < 0.999f || yAdd > 0.001f)
        {
            Settings sb = s;
            sb.y = std::clamp (s.y * dens + yAdd, 0.0f, 1.0f);
            const Settings* saved = cur;
            cur = &sb;
            render (k, offset, p, restart, phrase, sb, out);
            cur = saved;
        }
        else render (k, offset, p, restart, phrase, s, out);
    }

    void render (long long k, int offset, const Pos& p, bool restart, long long phrase, const Settings& s, EventList& out)
    {
        const Wendung& w = W();
        curChord = p.chordIdx; curRoot = w.ch[p.chordIdx].root; curType = w.ch[p.chordIdx].type;
        if (p.passing && s.follow[kFlaeche]) { curRoot = composition::freeTransition(nextChordRoot(p),true,1.f).approachRoot; curType = Dom7; }
        nowStep = k; updateMask (s);
        {
            const Chord& nc = p.chordIdx + 1 < w.n ? w.ch[p.chordIdx + 1] : w.ch[0];
            curNextRoot = nc.root; curNextType = nc.type;
            curProgress = p.chordEnd > p.chordStart ? (float) (k - p.chordStart) / (float) (p.chordEnd - p.chordStart) : 0.0f;
        }
        if (s.dynamics) dynamicsCc (k, p, s, offset, out);
        const bool chordStart = k == p.chordStart;
        const bool beat = p.pos % 4 == 0;
        const bool group = meter.isGroupStart (p.pos);
        const float z = s.z;
        const float yPad = layerY (s, kFlaeche), yBass = layerY (s, kBass), yArp = layerY (s, kArp);

        if (chordStart)
            sustained (p, s, offset, out, restart, bassRest ? 1u : 3u);
        else if (padGrow || peak || enterNow[kFlaeche] || enterNow[kBass])   // Ebene setzt mitten im Akkord ein
        {
            unsigned mask = (enterNow[kFlaeche] || peak ? 1u : 0u) | (enterNow[kBass] || peak ? 2u : 0u);
            if (padGrow && ! peak) { extendOnly = true; sustained (p, s, offset, out, true, 1u); extendOnly = false; }
            if (mask != 0) sustained (p, s, offset, out, true, mask);
        }

        // Akzente: Tupfer und Stich, bei Unruhe der fremde Ton in der Mitte des Akkords; ganz oben in der Unruhe der Riss
        accents (k, p, s, offset, out);
        riss (k, p, s, offset, out);

        // --- Flaeche: Schlaege, Puls oder Staccato
        const int pad = choosePad (s);
        if (pad == PadStabs && p.pos % 4 == 2)
            padChord (p, s, OutPadShort, offset, k + 1, (int) (55 + 40 * yPad) + jitter (k, kFlaeche, 4), out);
        else if (pad == PadPulse && beat)
            padChord (p, s, OutPadShort, offset, k + 3, (int) (50 + 40 * yPad) + (group ? 8 : 0), out);
        else if (pad == PadStaccato && beat)
            padChord (p, s, OutPadShort, offset, k + 1, (int) (48 + 40 * yPad) + (group ? 6 : 0), out);
        else if (pad == PadGated && p.pos % 2 == 0)                 // gehackte Achtel wie ein Gate
            padChord (p, s, OutPadShort, offset, k + 1, (int) (46 + 40 * yPad) + (group ? 10 : 0), out);

        // --- Bass
        {
            const Chord c = chordFor (p, kBass, s);
            const ChordShape& sh = kShapes[c.type];
            const int low = bassLow (s);
            const int pat = pattern0 (s, phrase);
            int root = bassPlacement (p, s, place (s.key + ((pat == BassPedal || pat == kPulseTick) ? pedalRoot() : bassRoot (c)), low), pat == BassPedal || pat == kPulseTick);
            const int vel = (int) (58 + 38 * yBass) + (group ? 8 : 0) + jitter (k, kBass, 3);
            const int pattern = pattern0 (s, phrase);
            const int bo = bassOut (pattern);
            const bool lastEighth = k == p.chordEnd - 2;
            // Chromatische Annaeherung an den naechsten Grundton im letzten Achtel des Akkords
            const bool approach = s.follow[kBass] && (z >= 0.3f || pattern == BassFunk) && lastEighth
                                  && pattern != BassHeld && pattern != BassWalking && pattern != BassHeartbeat && pattern != kPulseTick;
            if (approach)
            {
                const int target = nextBassPlacement (p, s);
                root = target - 1; // preserve the chromatic approach pitch class; sounding() applies the user range
            }
            switch (bassRest ? -1 : pattern)   // Vorbereiten: in der zweiten Takthaelfte schweigt der Bass
            {
                case kPulseTick:   if (beat) noteOn (bo, root, vel - (group ? 0 : 8), k + 1, offset, out); break;   // Ticken in Vierteln
                case BassHalf:     if (p.pos % 8 == 0 || approach) noteOn (bo, root, vel, k + (approach ? 2 : 7), offset, out); break;
                case BassQuarter:  if (beat || approach) noteOn (bo, root, vel, k + (approach ? 2 : 3), offset, out); break;
                case BassEighth:   if (p.pos % 2 == 0) noteOn (bo, root, vel, k + 2, offset, out); break;
                case BassPulse:    noteOn (bo, root, vel - (group ? 0 : 10), k + 1, offset, out); break;
                case BassFunk:
                {
                    const int q = p.pos % 8;
                    if (approach) noteOn (bo, root, vel, k + 1, offset, out);
                    else if (q == 0) noteOn (bo, root, vel + 6, k + 2, offset, out);
                    else if (q == 3) noteOn (bo, root, vel - 6, k + 1, offset, out);
                    else if (q == 5) noteOn (bo, root + 7, vel - 8, k + 1, offset, out);
                    else if (q == 6 && p.pos % 16 == 14) noteOn (bo, root + 12, vel - 4, k + 1, offset, out);   // kurzer Sprung nur am Taktende
                    break;
                }
                case BassPendulum:
                {
                    const int rate = yBass > 0.6f ? 2 : 4;
                    if (p.pos % rate == 0)
                    {
                        const int other = z >= 0.5f ? 1 : 3;                 // Halbton (Unruhe) oder kleine Terz
                        const int n = (p.pos / rate) % 2 == 0 ? root : root + other;
                        noteOn (bo, n, vel, k + rate - 1, offset, out);
                    }
                    break;
                }
                case BassWalking:
                    if (beat)
                    {
                        const int b = (int) ((k - p.chordStart) / 4);
                        int n;
                        if (s.follow[kBass] && k + 4 >= p.chordEnd)         // letzter Schlag: chromatisch zum naechsten Grundton
                        {
                            const int target = nextBassPlacement (p, s);
                            n = (b % 2 == 0) ? target - 1 : target + 1;
                        }
                        else
                        {
                            const int steps[4] = { 0, sh.iv[1], sh.iv[2], sh.n > 3 ? sh.iv[3] : 12 };
                            n = root + steps[b % 4];
                        }
                        noteOn (bo, n, vel, k + 3, offset, out);
                    }
                    break;
                case BassAlternating:
                    if (beat || approach)
                    {
                        const bool odd = ((p.pos / 4) % 2) == 1;
                        noteOn (bo, approach ? root : (odd ? root - 5 : root), vel - (odd ? 6 : 0), k + 2, offset, out);   // Grundton, Quinte darunter
                    }
                    break;
                case BassPedal:   // Orgelpunkt: liegt (in sustained), bei viel Intensitaet zusaetzlich ein Puls auf den Schlaegen
                    if (yBass > 0.6f && beat && k != p.chordStart) noteOn (OutBassShort, root, vel - 12, k + 1, offset, out);
                    break;
                case BassHiNrg:   // Grundton und Oberoktave im Wechsel, sehr aufgewuehlt in Sechzehnteln
                {
                    const int rate = yBass > 0.75f ? 1 : 2;
                    if (p.pos % rate == 0)
                        noteOn (bo, ((p.pos / rate) % 2 == 0) ? root : root + 12, vel - ((p.pos / rate) % 2 == 0 ? 0 : 8), k + rate, offset, out);
                    break;
                }
                case BassGallop:  // Achtel und zwei Sechzehntel
                {
                    const int q = p.pos % 4;
                    if (q == 0) noteOn (bo, root, vel + 4, k + 2, offset, out);
                    else if (q == 2 || q == 3) noteOn (bo, root, vel - 8, k + 1, offset, out);
                    break;
                }
                case BassHeartbeat:
                    if (p.pos % 8 == 0) noteOn (bo, root, vel + 4, k + 1, offset, out);
                    else if (p.pos % 8 == 2) noteOn (bo, root, vel - 10, k + 4, offset, out);
                    break;
                case BassArpeggio:
                    if (p.pos % 2 == 0)
                    {
                        const int startIdx = (int) (((p.bar % sh.n) + sh.n) % sh.n);                // Startton wechselt je Takt
                        const int i = (p.pos / 2 + startIdx) % sh.n;
                        noteOn (bo, root + sh.iv[i] - (sh.iv[i] > 7 ? 12 : 0), vel, k + 2, offset, out);
                    }
                    break;
                default: break;
            }
        }

        // --- Arp / Figur
        if (on[kArp])
        {
            const int fig = chooseArp (s, phrase);
            int rate = s.arpRate == RateQuarter ? 4 : s.arpRate == RateEighth ? 2 : s.arpRate == RateSixteenth ? 1
                     : (yArp < 0.15f ? 4 : yArp < 0.5f ? 2 : 1);
            if (fig == ArpGlitter || fig == ArpSid) rate = 1;
            const long long rel = k - (s.follow[kArp] ? p.chordStart : p.phraseStart);
            if (rel % rate == 0)
            {
                const Chord c = chordFor (p, kArp, s);
                const ChordShape& sh = kShapes[c.type];
                int base = place (s.key + c.root, 55 + (int) std::lround (s.x * 7.0f)) + (fig == ArpGlitter ? 12 : 0);
                int tones[10]; const int n = std::min (sh.n, 5); int count = 2 * n;
                for (int i = 0; i < count; ++i) tones[i] = base + sh.iv[i % n] + 12 * (i / n);
                if (rangeOn (OutArp))
                {
                    // Tonumfang: die Figur rueckt als Ganzes in den Bereich; die Tonleiter der Figur wird gefaltet und
                    // sortiert, so dass Auf, Ab und Kreisen an den Grenzen umkehren und kein Ton verschluckt wird
                    const int shift = bestShift (OutArp, tones, count);
                    base += shift;
                    count = fitGroup (OutArp, tones, count);
                }
                const long long c0 = rel / rate + (long long) (hashInt (77u, s.follow[kArp] ? p.chordStart : phrase) % 4);
                int note = base;
                switch (fig)
                {
                    case ArpDown:    note = tones[count - 1 - (int) (c0 % count)]; break;
                    case ArpCircle:  { const int period = std::max (1, 2 * count - 2); const int q = (int) (c0 % period); note = tones[q < count ? q : period - q]; break; }
                    case ArpCell:
                    {
                        static constexpr int cell[4] = { 0, 1, 0, 2 };
                        const int q = cell[c0 % 4];
                        note = (q == 1 && z >= 0.5f) ? base + 1 : tones[q];   // bei Unruhe: Halbton-Nachbar statt Terz
                        break;
                    }
                    case ArpRiff:
                    {
                        static constexpr int dark[8] = { 0, 3, 5, 7, 10, 7, 5, 3 };
                        static constexpr int bright[8] = { 0, 2, 4, 7, 9, 7, 4, 2 };
                        static constexpr int exotic[8] = { 0, 1, 4, 5, 7, 8, 5, 4 };   // phrygisch-dominant
                        const int* r = c.type == Dom7b9 ? exotic : sh.minor ? dark : bright;
                        note = base + r[c0 % 8];
                        break;
                    }
                    case ArpLeaps:
                    {
                        const int leaps[6] = { 0, 7, 12, sh.iv[1] + 12, 12, 7 };   // Dreiklangs-Spruenge
                        note = base + leaps[c0 % 6];
                        break;
                    }
                    case ArpCascade:   // Harfen-Kaskade: Dreiergruppen, die stufenweise steigen und von vorn beginnen
                    {
                        const int g = (int) ((c0 / 3) % n), j = (int) (c0 % 3);
                        note = tones[std::min (count - 1, g + j)];
                        break;
                    }
                    case ArpOctatonic: // Halbton-Ganzton-Leiter auf und ab
                    {
                        static constexpr int scale[8] = { 0, 1, 3, 4, 6, 7, 9, 10 };
                        const int q = (int) (c0 % 14);
                        const int idx = q < 8 ? q : 14 - q;
                        note = base + (idx < 8 ? scale[idx] : 12);
                        break;
                    }
                    case ArpSid:       // SID-Arpeggio: Dreiklang in Sechzehnteln, eine Oktave hoeher, wie ein Akkord auf einem Kanal
                    {
                        note = base + 12 + sh.iv[(int) (c0 % std::min (3, sh.n))];
                        break;
                    }
                    case ArpQuartal:   // gestapelte Quarten als Ostinato
                    {
                        static constexpr int fourths[6] = { 0, 5, 10, 15, 10, 5 };
                        note = base + fourths[c0 % 6];
                        break;
                    }
                    default:         note = tones[c0 % count]; break;       // Aufwaerts, Glitzern
                }
                if (z >= 0.6f && c0 % 8 == 7) note -= 1;                    // Unruhe: chromatischer Durchgang
                const int vel = (int) ((fig == ArpGlitter ? 40 : 52) + 35 * yArp) + (group ? 6 : 0) + jitter (k, kArp, 6);
                const long long len = (fig == ArpGlitter || fig == ArpSid || rate == 1) ? 1 : rate;
                noteOn (OutArp, note, vel, k + len, offset, out);
            }
        }

        // --- Gegenstimme: ruhige Linie aus Akkordtoenen, schrittweise gefuehrt
        counterLine (k, p, s, offset, chordStart || enterNow[kGegenstimme], out);
    }

    // Dynamik als CC: Grundwert folgt der Intensitaet, darauf atmende Boegen (Grundlage: Dynamikkurven der eigenen Vorlagen,
    // meist zwischen 62 und 75 in Boegen von ein bis drei Vierteln). Pop-Rock fast flach, Score weiter, bei Unruhe mit Akzent.
    void resetCc() { lastDynamicsId = lastExpressionId = -1; for (auto& v : lastCc) v = -1; for (auto& v : lastExpr) v = -1; }

    bool outputSounding (int output) const
    {
        for (int i = 0; i < numActive; ++i) if (active[(size_t) i].out == output) return true;
        return false;
    }

    void dynamicsCc (long long k, const Pos& p, const Settings& s, int offset, EventList& out)
    {
        if (lastDynamicsId != s.ccDynamics || lastExpressionId != s.ccExpression)
        { resetCc(); lastDynamicsId = s.ccDynamics; lastExpressionId = s.ccExpression; }
        uint32_t sent = 0;   // teilen sich Ebenen einen Kanal, bestimmt die erste Ebene seinen Verlauf
        for (int o = 0; o < kNumOutputs; ++o)
        {
            const int layer = kOutputLayer[o];
            const int channel = s.channel[o];
            if ((sent >> channel) & 1u) continue;
            if (! on[layer] && ! outputSounding (o)) continue;
            sent |= 1u << channel;
            float yl = layerY (s, layer), envelope = gain[layer];
            for (int other = o + 1; other < kNumOutputs; ++other)
                if (s.channel[other] == channel && (on[kOutputLayer[other]] || outputSounding (other)))
                { yl = std::max (yl, layerY (s, kOutputLayer[other])); envelope = std::max (envelope, gain[kOutputLayer[other]]); }
            const float base = 50.0f + 40.0f * yl;
            float value = base;
            if (s.genre == GenrePopRock) value += 2.0f * std::sin (3.14159265f * (float) ((k - p.chordStart) % 16) / 16.0f);
            else
            {
                const bool slow = o == OutCounter || o == OutPadLong || o == OutBassLong;
                const int arc = slow ? 16 : 8;
                const float amp = 4.0f + 6.0f * yl + 4.0f * s.z;
                const float phase = (float) ((k - p.chordStart) % arc) / (float) arc;
                value += -0.5f * amp + amp * std::sin (3.14159265f * phase);
                const long long since = k - p.chordStart;
                if (s.z >= 0.6f && since < 4) value += (amp + 6.0f) * (1.0f - (float) since / 4.0f);   // Sforzato beim Akkordwechsel
            }
            auto mapped = [&] (int kind, float unit)
            {
                const int lo = std::clamp (std::min (s.ccLo[kind][channel - 1], s.ccHi[kind][channel - 1]), 0, 127);
                const int hi = std::clamp (std::max (s.ccLo[kind][channel - 1], s.ccHi[kind][channel - 1]), 0, 127);
                return (float) lo + (float) (hi - lo) * std::clamp (unit, 0.0f, 1.0f);
            };
            const int v = std::clamp ((int) std::lround (s.ccRange ? mapped (0, (value - 45.0f) / 45.0f) : value), 0, 127);
            const float expr = s.ccRange ? mapped (1, yl) : 70.0f + 50.0f * yl;
            const int e = std::clamp ((int) std::lround (expr * envelope), 0, 127);
            if (s.ccDynamics > 0 && (lastCc[channel] < 0 || v != lastCc[channel])) { out.addCc (offset, channel, s.ccDynamics, v, o); lastCc[channel] = v; }
            if (s.ccExpression > 0 && (lastExpr[channel] < 0 || e != lastExpr[channel])) { out.addCc (offset, channel, s.ccExpression, e, o); lastExpr[channel] = e; }
        }
    }

    // Zielton der Gegenstimme: Akkordton nahe am vorigen Ton, Terz und Septime bevorzugt.
    // Eigene Lage in der Mitte (D4 bis F#5), getrennt vom Tupfer darueber und vom Stich darunter.
    int counterTarget (const Chord& c, const Settings& s, bool chordStart, long long k) const
    {
        const ChordShape& sh = kShapes[c.type];
        const int lo = 62 + (int) std::lround (s.x * 3.0f);
        const int rootPc = (s.key + c.root) % 12;
        const int ri = kOutputRange[OutCounter];
        int a = lo, b = lo + 13;
        if (s.rangeOn[ri])
        {
            // Tonumfang: nur Toene im spielbaren Bereich (Oktav-Einstellung eingerechnet); liegt die uebliche Lage
            // ausserhalb, sucht die Linie im ganzen Bereich
            const int rlo = s.rangeLo[ri] - 12 * s.octave[kGegenstimme], rhi = s.rangeHi[ri] - 12 * s.octave[kGegenstimme];
            a = std::max (lo, rlo); b = std::min (lo + 13, rhi);
            int found = 0;
            for (int n = a; n <= b; ++n)
                for (int i = 0; i < sh.n; ++i) found += (rootPc + sh.iv[i]) % 12 == n % 12 ? 1 : 0;
            if (found < 2) { a = rlo; b = rhi; }
        }
        const int prev = csNote >= 0 ? csNote : (a + b) / 2;
        int best = -1; float bestScore = 1e9f;
        for (int n = a; n <= b; ++n)
        {
            const int pc = n % 12;
            bool inChord = false;
            for (int i = 0; i < sh.n; ++i) inChord = inChord || (rootPc + sh.iv[i]) % 12 == pc;
            if (! inChord) continue;
            const int d = n - prev;
            float score = (float) std::abs (d);
            if (d == 0 && ! chordStart) score += 3.0f;            // innerhalb des Akkords: weitergehen
            if (pc == rootPc) score += 1.5f;                       // Grundton hat der Bass
            if (s.x < 0.4f && d > 0) score += 0.5f;                // dunkel: eher abwaerts
            if (s.x > 0.6f && d < 0) score += 0.5f;                // hell: eher aufwaerts
            score += (float) (hash3 ((uint32_t) s.variation, (uint32_t) (k * 16 + n), 401u) % 100u) / 250.0f;
            if (score < bestScore) { bestScore = score; best = n; }
        }
        return best >= 0 ? best : place (s.key + c.root + sh.iv[std::min (1, sh.n - 1)], a);
    }

    // Pop-Rock: durchgehende, gleichbleibende Hook-Linie aus Akkordtoenen (eine Figur je VARIATION)
    void leadHook (long long k, const Pos& p, const Settings& s, int offset, EventList& out)
    {
        if (current >= 27 && current < 36 && ! s.custom)
        {
            // Each new study has its own two-bar rhythm and contour, with real rests.
            static constexpr int starts[9][8] = {
                {0,3,6,10,16,19,23,28}, {0,8,14,20,28,-1,-1,-1}, {0,12,24,-1,-1,-1,-1,-1},
                {6,10,22,26,-1,-1,-1,-1}, {0,6,12,16,22,28,-1,-1}, {2,6,12,18,22,28,-1,-1},
                {0,4,10,16,20,26,30,-1}, {2,6,18,22,28,-1,-1,-1}, {0,6,12,22,28,-1,-1,-1} };
            static constexpr int degrees[9][8] = {
                {0,1,2,1,0,1,3,2}, {2,2,1,2,1,0,0,0}, {2,1,0,0,0,0,0,0},
                {0,1,1,2,0,0,0,0}, {2,1,0,2,1,0,0,0}, {0,2,1,0,3,2,0,0},
                {0,1,2,1,2,3,2,0}, {0,2,1,2,1,0,0,0}, {2,1,0,1,0,0,0,0} };
            const int id = current - 27;
            const long long cycle = 2LL * meter.len;
            const auto local = (k - p.phraseStart) % cycle;
            const Chord c = chordFor (p, kGegenstimme, s);
            const auto& sh = kShapes[c.type];
            for (int i = 0; i < 8 && starts[id][i] >= 0; ++i)
            {
                const long long at = (long long) starts[id][i] * cycle / 32;
                if (local != at) continue;
                const int deg = degrees[id][i] + ((id == 0 && (k - p.phraseStart) / cycle % 2 && i == 7) ? 1 : 0);
                int note = place (s.key + c.root, 67) + sh.iv[deg % sh.n] + 12 * (deg / sh.n);
                if (id == 1 || id == 2 || id == 8) note = counterTarget (c, s, k == p.chordStart, k);
                long long next = i < 7 && starts[id][i + 1] >= 0 ? (long long) starts[id][i + 1] * cycle / 32 : cycle;
                const long long len = std::max (1LL, next - at - ((id == 3 || id == 7) ? 2 : 0));
                noteOn (OutCounter, note, (int) (58 + 35 * layerY (s, kGegenstimme)), k + len + (s.legato ? 1 : 0), offset, out);
                releaseOthers (OutCounter, note, offset, out); csNote = note;
                return;
            }
            return;
        }
        static constexpr int figures[6][8] = { { 0, 1, 2, 1, 0, 1, 2, 3 }, { 2, 1, 0, 1, 2, 3, 2, 1 }, { 0, 0, 2, 0, 3, 0, 2, 1 },
                                               { 3, 2, 1, 2, 3, 2, 1, 0 }, { 0, 2, 1, 2, 0, 3, 2, 1 }, { 1, 2, 3, 2, 1, 0, 1, 2 } };
        const float yc = layerY (s, kGegenstimme);
        const int rate = yc < 0.45f ? 4 : 2;
        if ((k - p.phraseStart) % rate != 0) return;
        const int slot = (int) (((k - p.phraseStart) / rate) % 8);
        const int* fig = figures[hash3 ((uint32_t) s.variation, 17u, 523u) % 6];
        const Chord c = chordFor (p, kGegenstimme, s);
        const ChordShape& sh = kShapes[c.type];
        const int base = place (s.key + c.root, 67 + (int) std::lround (s.x * 4.0f));
        const int idx = fig[slot];
        int note = idx >= 3 || idx >= sh.n ? base + 12 : base + sh.iv[idx];
        if (s.z >= 0.5f && slot == 7)                               // Unruhe: chromatischer Nachbar vor dem naechsten Ton
        {
            const int nx = fig[0] >= 3 || fig[0] >= sh.n ? base + 12 : base + sh.iv[fig[0]];
            note = nx - 1;
        }
        noteOn (OutCounter, note, (int) (58 + 35 * yc) + (slot % 2 == 0 ? 6 : 0), k + (s.legato ? rate + 1 : std::max (1, rate - 1)), offset, out);
        if (s.legato) releaseOthers (OutCounter, note, offset, out);
    }

    // Legato: vorigen Ton desselben Ausgangs erst eine Sechzehntelnote nach dem neuen Anschlag loslassen.
    void releaseOthers (int o, int keep, int offset, EventList& out)
    {
        const int keepNote = sounding (o, keep);
        for (int i = 0; i < numActive; ++i)
        {
            auto& a = active[(size_t) i];
            if (a.out == o && a.note != keepNote)
                a.endStep = std::min (a.endStep, nowStep + (cur != nullptr && cur->legato ? 1 : 0));
        }
        if (cur == nullptr || ! cur->legato) releaseDue (nowStep, offset, out);
    }

    // Ende eines Tons der Gegenstimme relativ zum naechsten: Legato eine Sechzehntel darueber, sonst kurz davor abgesetzt
    long long tail (long long len) const { return cur != nullptr && cur->legato ? 1 : (len >= 4 ? -1 : 0); }

    void counterLine (long long k, const Pos& p, const Settings& s, int offset, bool chordStart, EventList& out)
    {
        if (! on[kGegenstimme]) { csNote = -1; csPendingAt = -1; return; }
        if (s.genre == GenrePopRock) { leadHook (k, p, s, offset, out); return; }
        if (s.motif && motifStep (k, p, s, offset, out)) return;
        const float yc = layerY (s, kGegenstimme);
        const int vel = (int) (50 + 35 * yc);
        if (k == csPendingAt && csPending >= 0)                    // Vorhalt loest sich auf
        {
            noteOn (OutCounter, csPending, vel, csPendingEnd + tail (csPendingEnd - k), offset, out);
            releaseOthers (OutCounter, csPending, offset, out);
            csNote = csPending; csPendingAt = -1;
        }
        // Bewegung: ruhig nur bei Akkordwechseln, mittel alle zwei Takte, aufgewuehlt in Halben
        const long long rate = yc < 0.4f ? 0 : yc < 0.7f ? 2LL * meter.len : std::max (4LL, (long long) meter.len / 2);
        const bool move = chordStart || (rate > 0 && k > p.chordStart && (k - p.chordStart) % rate == 0 && p.chordEnd - k >= 4);
        if (! move) return;
        const Chord c = chordFor (p, kGegenstimme, s);
        const long long end = rate > 0 ? std::min (p.chordEnd, k + rate) : p.chordEnd;
        const int target = counterTarget (c, s, chordStart, k);
        if (s.z >= 0.5f && chordStart && end - k >= 8)               // Unruhe: Vorhalt von oben, loest auf den Zielton auf
        {
            const int sus = target + (s.z >= 0.75f ? 1 : 2);
            noteOn (OutCounter, sus, vel + 6, k + 4 + (s.legato ? 1 : 0), offset, out);
            releaseOthers (OutCounter, sus, offset, out);
            csPending = target; csPendingAt = k + 4; csPendingEnd = end;
            csNote = sus;
            return;
        }
        noteOn (OutCounter, target, vel, end + tail (end - k), offset, out);   // Legato: eine Sechzehntel laenger, bindet zum naechsten Ton
        releaseOthers (OutCounter, target, offset, out);
        csNote = target;
    }

    composition::RememberedMotif motifMemory;
    composition::HarmonicPlan harmonicPlan;
    uint64_t planKey = 0; bool planValid = false;
    uint32_t unavailablePad = 0;
    static constexpr int kMaxActive = 192;
    std::array<Active, kMaxActive> active {};
    int numActive = 0;
    bool running = false, wasCustom = false;
    double lastPpqEnd = 0.0;
    long long phraseIndex = -1, wendungStart = 0, chaseStep = -1;
    bool still = false;   // Ruhezone: Akkord steht
    bool drivePrev = false, driveSeen = false, driveLatched = false, driveArrivedNow = false;   // Fahrt: Einschalten waehrend der Wiedergabe, Ankunft
    uint32_t driveGenerationSeen = 0;
    float driveProgressNow = 0;
    bool driveTrajectory = false, segmentReturn = false;
    float originX = 0, originY = 0, segmentX = 0, segmentY = 0, segmentQ = 0;
    float segmentTargetX = 0, segmentTargetY = 0, observedBX = 0, observedBY = 0;
    long long manualEndStep = -1;
    bool endWasRequested = false, manualFinished=false, manualHitSent=false;
    int sceneSeed = 0;
    float routeBX=0,routeBY=0,routeCorrectionStart=0; DrivePoint routeCorrection;
    int driveFromLatched = 0;
    int chordBase = 0;    // Akkord, ab dem die Folge laeuft (nach der Ruhezone)
    int current = -1, curChord = -1, curRoot = 0, curType = Min, style = -1;
    int genre = GenreScore, lastGenre = -1, curNextRoot = 0, curNextType = Min;
    float curProgress = 0.0f;
    uint32_t chordMask = 0;          // Tonnamen des klingenden Akkords (Ersatz bei sehr engem Tonumfang)
    long long nowStep = -1;
    long long exitStep[kNumLayers] {}, exitUntil[kNumLayers] {};
    bool ccWasEnabled = false;
    int lastDynamicsId = -1, lastExpressionId = -1;
    int lastCc[17] {}, lastExpr[17] {};   // je MIDI-Kanal (1 ... 16)
    int csNote = -1, csPending = -1;                 // Gegenstimme: letzter Ton, aufzuloesender Vorhalt
    long long csPendingAt = -1, csPendingEnd = 0;
    int phraseBars = kPhraseBars;
    // Szene
    long long sceneStep = 0, sceneEndStep = 1LL << 60, autoSeed = -1;
    int autoValue = EntryPad, entryInUse = EntryPad, sceneBarNow = -1, bassOverride = -1;
    bool sceneEnded = false, padShy = false, padGrow = false, akzentForced = false, bassRest = false, prepStich = false, peak = false;
    bool forceOn = false, extendOnly = false;
    bool on[kNumLayers] {}, prevOn[kNumLayers] {}, hOn[kNumLayers] {}, enterNow[kNumLayers] {}, thinned[kNumLayers] {};
    long long hSince[kNumLayers] {}, entryStep[kNumLayers] { -(1LL << 50), -(1LL << 50), -(1LL << 50), -(1LL << 50), -(1LL << 50) };
    float gain[kNumLayers] { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
    int boost[kNumLayers] {};
    float dens = 1.0f, yAdd = 0.0f, curX = 0.0f, curY = 0.0f, driveAY = 0.0f;
    Meter meter;
    Wendung custom {};
    const Settings* cur = nullptr;   // nur waehrend process() gueltig
};

// Einfacher Vorhoer-Klang: weiche Sinus-Stimmen, damit man ohne eigene Instrumente etwas hoert
class Preview
{
public:
    void prepare (double sr) { sampleRate = sr; reset(); }
    void reset() { for (auto& v : voices) v = {}; }

    void handle (const Event& e)
    {
        if (e.type != 0) return;
        if (e.velocity == 0)
        {
            for (auto& v : voices)
                if (v.on && ! v.releasing && v.channel == e.channel && v.note == e.note) v.releasing = true;
            return;
        }
        Voice* slot = &voices[0];
        for (auto& v : voices) if (! v.on) { slot = &v; break; }
        static constexpr float outGain[kNumOutputs] = { 0.04f, 0.04f, 0.07f, 0.07f, 0.04f, 0.035f, 0.03f, 0.06f };
        const float freq = 440.0f * std::pow (2.0f, ((float) e.note - 69.0f) / 12.0f);
        *slot = {};
        slot->on = true; slot->channel = e.channel; slot->note = e.note;
        slot->inc = (float) (2.0 * 3.14159265358979 * freq / sampleRate);
        slot->gain = outGain[std::clamp ((int) e.out, 0, kNumOutputs - 1)] * (float) e.velocity / 127.0f;
    }

    void render (float* l, float* r, int n)
    {
        const float att = 1.0f / (0.02f * (float) sampleRate), rel = 1.0f / (0.25f * (float) sampleRate);
        for (auto& v : voices)
        {
            if (! v.on) continue;
            for (int i = 0; i < n; ++i)
            {
                if (v.releasing) { v.env -= rel; if (v.env <= 0.0f) { v.on = false; break; } }
                else if (v.env < 1.0f) v.env = std::min (1.0f, v.env + att);
                const float x = (std::sin (v.phase) + 0.25f * std::sin (2.0f * v.phase)) * v.env * v.gain;
                v.phase += v.inc; if (v.phase > 6.2831853f) v.phase -= 6.2831853f;
                l[i] += x; r[i] += x;
            }
        }
    }

private:
    struct Voice { bool on = false, releasing = false; uint8_t channel = 0, note = 0; float phase = 0, inc = 0, env = 0, gain = 0; };
    std::array<Voice, 64> voices {};
    double sampleRate = 48000.0;
};
} // namespace stromscore
