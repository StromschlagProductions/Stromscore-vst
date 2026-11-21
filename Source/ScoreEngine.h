#pragma once
// Stromscore: regelbasierter Noten-Generator (kein JUCE, echtzeitfest, ohne Speicheranforderung im Audiopfad).
// Die Ausgabe ist eine reine Funktion der Projektposition und der Einstellungen: gleiche Einstellungen, gleiche Noten.
//
// Stimmungsfeld: Faerbung (x, dunkel -> hell), Intensitaet (y, ruhig -> aufgewuehlt), Unruhe (z, sauber -> kratzig).
// Aus dem Feld wird je Phrase eine Wendung aus dem Vokabular gezogen (kWendungen, Grundlage: Stilmittel-Katalog).
// Bewegt sich der Punkt merklich, wechselt die Wendung am naechsten Wechselpunkt (Schlag, Takt, 2 oder 4 Takte)
// und beginnt dort mit ihrem ersten Akkord. Alternativ spielt eine eigene Akkordfolge.
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>

namespace stromscore
{
constexpr int kNumLayers = 5;
enum Layer { kFlaeche = 0, kBass = 1, kArp = 2, kFarbe = 3, kGegenstimme = 4 };
constexpr int kNumKeys = 12;
constexpr double kStep = 0.25;          // Raster: Sechzehntel (in Viertelnoten)
constexpr int kPhraseBars = 8;          // eine Wendung = 8 Takte
constexpr int kMaxChords = 8;

// Ab welcher Intensitaet eine Ebene im Modus Auto einsetzt (Farbe zusaetzlich ab Unruhe 0,4)
constexpr float kLayerStart[kNumLayers] = { 0.0f, 0.0f, 0.25f, 0.4f, 0.15f };

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
constexpr int kCustomTypes[] = { Maj, Min, Maj7, Min7, Dom7, Sus4, Sus2, Add9, Min6, MinMaj7, HalfDim, Dim7, Aug };
constexpr int kNumCustomTypes = (int) (sizeof (kCustomTypes) / sizeof (kCustomTypes[0]));

// ------------------------------------------------------------------ Muster
enum PadPattern { PadAuto = 0, PadHeld, PadStabs, PadPulse, PadStaccato, kNumPadPatterns };
enum BassPattern { BassAuto = 0, BassHeld, BassHalf, BassQuarter, BassEighth, BassPulse, BassFunk, BassPendulum,
                   BassWalking, BassAlternating, BassHeartbeat, BassArpeggio, BassPedal, kNumBassPatterns };
enum ArpFigure { ArpAuto = 0, ArpUp, ArpDown, ArpCircle, ArpCell, ArpRiff, ArpGlitter, ArpLeaps, ArpCascade, ArpOctatonic, ArpQuartal, kNumArpFigures };
enum ArpRate { RateAuto = 0, RateQuarter, RateEighth, RateSixteenth, kNumArpRates };
enum ChangeGrid { ChangeBeat = 0, ChangeBar, Change2Bars, Change4Bars, kNumChangeGrids };

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
    { "Septakkord-Paare",   0.22f, 0.55f, 0.55f, 4, { { 0, MinMaj7, 2 }, { 5, MinMaj7, 2 }, { 0, MinMaj7, 2 }, { 5, MinMaj7, 2 } }, { ArpCell, ArpUp }, { BassEighth, BassPendulum }, PadHeld },
    { "Schiefer Walzer",    0.20f, 0.55f, 0.35f, 4, { { 0, Min, 2 }, { 0, MinMaj7, 2 }, { 5, Min7, 2 }, { 7, Dom7, 2 } }, { ArpCircle, ArpDown }, { BassQuarter, BassHalf }, PadHeld },
    { "Unruhiger Schlaf",   0.25f, 0.35f, 0.40f, 8, { { 0, Min, 1 }, { 8, Maj, 1 }, { 9, Dim7, 1 }, { 8, Maj, 1 }, { 0, Min, 1 }, { 8, Maj, 1 }, { 9, Dim7, 1 }, { 8, Maj, 1 } }, { ArpCircle, ArpCell }, { BassHeld, BassPendulum }, PadHeld },
    { "Moll-Inseln",        0.30f, 0.45f, 0.30f, 4, { { 0, Min, 2 }, { 8, Min, 2 }, { 3, Min, 2 }, { 0, Min, 2 } }, { ArpDown, ArpCircle }, { BassHalf, BassHeld }, PadHeld },
    { "Grusel-Orchester",   0.15f, 0.50f, 0.50f, 4, { { 0, Min, 2 }, { 2, HalfDim, 2 }, { 0, Min, 2 }, { 1, Maj, 2 } }, { ArpDown, ArpCircle }, { BassQuarter, BassPendulum }, PadHeld },
    { "Geisterball",        0.15f, 0.55f, 0.55f, 4, { { 0, Min, 2 }, { 11, Dim7, 2 }, { 0, Min, 2 }, { 5, Min6, 2 } }, { ArpCircle, ArpDown }, { BassAlternating, BassQuarter }, PadStaccato },
    // dunkel und aufgewuehlt: Angst, Panik, Verfolgung
    { "Terz-Treppe",        0.20f, 0.80f, 0.60f, 4, { { 0, Min, 2 }, { 3, Min, 2 }, { 6, Min, 2 }, { 9, Min, 2 } }, { ArpCell, ArpUp }, { BassPulse, BassEighth }, PadPulse },
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
    { "Offene Quinten",     0.65f, 0.30f, 0.05f, 4, { { 0, Maj7, 2 }, { 2, Min7, 2 }, { 4, Min7, 2 }, { 5, Maj7, 2 } }, { ArpCascade, ArpUp }, { BassHalf, BassArpeggio }, PadHeld },
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
constexpr int kCustomWendung = kNumWendungen;   // Index fuer die eigene Folge

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
    bool passing = false;       // Durchgangsakkorde: bei viel Intensitaet die Dominante des naechsten Akkords auf dem letzten Schlag       // Abwechslung: 0 = nur die passendste Wendung, 1 = auch entferntere Nachbarn
    int octave[kNumLayers] = { 0, 0, 0, 0, 0 };               // -2 ... +2
    bool follow[3] = { true, true, true };                    // Flaeche, Bass, Arp: false = bleibt auf dem Grundakkord
    int padPattern = PadAuto, bassPattern = BassAuto, arpFigure = ArpAuto, arpRate = RateAuto;
    bool custom = false;        // eigene Akkordfolge statt Wendungen
    CustomChord customChords[kMaxChords];
};

struct Transport
{
    bool playing = false;
    double ppq = 0.0;           // Position am Blockanfang in Viertelnoten
    double bpm = 120.0;
    double sampleRate = 48000.0;
};

// velocity 0 = Note aus
struct Event { int offset; uint8_t channel; uint8_t note; uint8_t velocity; };

struct EventList
{
    static constexpr int kCapacity = 2048;
    std::array<Event, kCapacity> events {};
    int size = 0;
    bool overflow = false;
    void clear() { size = 0; overflow = false; }
    void add (int offset, int channel, int note, int velocity)
    {
        if (size >= kCapacity) { overflow = true; return; }
        events[(size_t) size++] = { offset, (uint8_t) channel, (uint8_t) note, (uint8_t) velocity };
    }
};

inline uint32_t hash3 (uint32_t a, uint32_t b, uint32_t c)
{
    uint32_t h = a * 0x9E3779B1u ^ (b + 0x7F4A7C15u) * 0x85EBCA6Bu ^ (c + 0x165667B1u) * 0xC2B2AE35u;
    h ^= h >> 16; h *= 0x7FEB352Du; h ^= h >> 15; h *= 0x846CA68Bu; h ^= h >> 16;
    return h;
}

// Akkordname (deutsche Notennamen mit H): "Am", "Fmaj7", "Gism(maj7)"
inline void chordName (int key, int root, int type, char* out, int maxLen)
{
    static const char* major[12] = { "C", "Des", "D", "Es", "E", "F", "Fis", "G", "As", "A", "B", "H" };
    static const char* minor[12] = { "C", "Cis", "D", "Es", "E", "F", "Fis", "G", "Gis", "A", "B", "H" };
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
    int groupStart[16] {};

    static Meter from (int num, int den)
    {
        Meter m;
        num = std::clamp (num, 1, 16);
        den = (den == 2 || den == 4 || den == 8 || den == 16) ? den : 4;
        m.len = std::clamp (num * 16 / den, 4, 32);
        int sizes[16] {}; int n = 0;
        if (den == 8 && num % 3 == 0)            { for (int i = 0; i < num / 3; ++i) sizes[n++] = 6; }
        else if (den == 8 && num >= 5)           { int rest = m.len; while (rest > 6) { sizes[n++] = 4; rest -= 4; } sizes[n++] = rest; }
        else if (num == 5 && den == 4)           { sizes[n++] = 6; sizes[n++] = 6; sizes[n++] = 4; sizes[n++] = 4; }
        else { int rest = m.len; while (rest > 0 && n < 16) { const int g = std::min (4, rest); sizes[n++] = g; rest -= g; } }
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
    void reset() { style = -1; csNote = -1; csPendingAt = -1; chaseStep = -1; numActive = 0; running = false; lastPpqEnd = 0.0; phraseIndex = -1; current = -1; wendungStart = 0; curRoot = 0; curType = Min; curChord = -1; }

    // Fuer die Anzeige (kCustomWendung = eigene Folge)
    int wendung() const { return current; }
    int chordInWendung() const { return curChord; }
    int chordRoot() const { return curRoot; }
    int chordType() const { return curType; }
    int styleWendung() const { return current == kCustomWendung ? style : -1; }   // eigene Folge: Wendung, deren Stil geliehen wird

    // Intensitaet einer Ebene: Feld plus eigener Regler
    static float layerY (const Settings& s, int layer)
    {
        return std::clamp (s.y + s.layerIntensity[layer], 0.0f, 1.0f);
    }

    static bool layerActive (const Settings& s, int layer)
    {
        bool anySolo = false;
        for (bool b : s.solo) anySolo = anySolo || b;
        if (anySolo ? ! s.solo[layer] : s.mute[layer]) return false;
        const float y = layerY (s, layer);
        if (layer == kFarbe) return y >= kLayerStart[kFarbe] || s.z >= 0.4f;
        return y >= kLayerStart[layer];
    }

    // Ab welchem Anteil der besten Passung eine Wendung in Frage kommt (Abwechslung 0 = nur die beste)
    static float keepRatio (const Settings& s) { return 1.0f - 0.85f * std::clamp (s.variety, 0.0f, 1.0f); }

    // Wendungen, die an der aktuellen Stelle in Frage kommen, nach Passung sortiert
    static int candidates (const Settings& s, int* out, int maxOut)
    {
        float w[kNumWendungen]; float best = 0.0f;
        for (int i = 0; i < kNumWendungen; ++i) { w[i] = weight (kWendungen[i], s); best = std::max (best, w[i]); }
        const float r = keepRatio (s);
        int n = 0;
        if (maxOut <= 0) return 0;
        for (int i = 0; i < kNumWendungen; ++i)
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
        for (const auto& w : kWendungen) best = std::max (best, weight (w, s));
        return best;
    }

    // Deterministische Wahl unter den Wendungen, die gut zur Lage passen (mindestens halb so gut wie die beste)
    static int pick (const Settings& s, long long salt)
    {
        float w[kNumWendungen]; float total = 0.0f, best = 0.0f; int bestIdx = 0;
        for (int i = 0; i < kNumWendungen; ++i)
        {
            w[i] = weight (kWendungen[i], s);
            if (w[i] > best) { best = w[i]; bestIdx = i; }
        }
        const float ratio = keepRatio (s);
        for (int i = 0; i < kNumWendungen; ++i) { if (w[i] < ratio * best) w[i] = 0.0f; total += w[i]; }
        if (total <= 0.0f) return bestIdx;
        const float r = (float) (hash3 ((uint32_t) s.variation, (uint32_t) salt, 911u) % 100000u) / 100000.0f * total;
        float acc = 0.0f;
        for (int i = 0; i < kNumWendungen; ++i) { acc += w[i]; if (r < acc) return i; }
        return bestIdx;
    }

    void allNotesOff (EventList& out, int offset)
    {
        for (int i = 0; i < numActive; ++i)
            out.add (offset, active[(size_t) i].channel, active[(size_t) i].note, 0);
        numActive = 0;
    }

    void process (const Transport& t, const Settings& sIn, int numSamples, EventList& out)
    {
        Settings s = sIn;
        s.key = std::clamp (s.key, 0, kNumKeys - 1);
        s.x = std::clamp (s.x, 0.0f, 1.0f); s.y = std::clamp (s.y, 0.0f, 1.0f); s.z = std::clamp (s.z, 0.0f, 1.0f);
        s.swing = std::clamp (s.swing, 0.0f, 1.0f);
        s.variation = std::clamp (s.variation, 1, 16);
        s.change = std::clamp (s.change, 0, kNumChangeGrids - 1);
        for (auto& v : s.layerIntensity) v = std::clamp (v, -1.0f, 1.0f);
        s.variety = std::clamp (s.variety, 0.0f, 1.0f);
        for (auto& o : s.octave) o = std::clamp (o, -2, 2);
        s.padPattern = std::clamp (s.padPattern, 0, kNumPadPatterns - 1);
        s.bassPattern = std::clamp (s.bassPattern, 0, kNumBassPatterns - 1);
        s.arpFigure = std::clamp (s.arpFigure, 0, kNumArpFigures - 1);
        s.arpRate = std::clamp (s.arpRate, 0, kNumArpRates - 1);
        cur = &s;
        meter = Meter::from (s.meterNum, s.meterDen);
        custom = customWendung (s);
        const int bars = s.custom ? wendungBars (custom) : kPhraseBars;
        if (s.custom != wasCustom || bars != phraseBars)       // Umschalten oder neue Laenge: neue Phrase
        {
            phraseIndex = -1; wasCustom = s.custom; phraseBars = bars;
            if (running) releaseHeld (0, out);
        }

        if (! t.playing || t.bpm <= 0.0 || t.sampleRate <= 0.0 || numSamples <= 0)
        {
            if (running) allNotesOff (out, 0);
            running = false; curChord = -1; cur = nullptr;
            return;
        }
        releaseSilencedLayers (s, out);

        const double samplesPerQuarter = t.sampleRate * 60.0 / t.bpm;
        const double ppqEnd = t.ppq + (double) numSamples / samplesPerQuarter;
        const bool jumped = running && std::fabs (t.ppq - lastPpqEnd) > 0.05;
        if (! running || jumped)
        {
            allNotesOff (out, 0);
            running = true;
            phraseIndex = -1;
            csNote = -1; csPendingAt = -1;
            chase (t.ppq, s, out);
        }

        const long long firstStep = (long long) std::floor (t.ppq / kStep) - 1;
        for (long long k = std::max (0LL, firstStep); ; ++k)
        {
            const double when = ((double) k + swingDelay (k, s)) * kStep;
            if (when >= ppqEnd - 1e-12) break;
            if (when < t.ppq - 1e-12) continue;
            const int offset = std::clamp ((int) std::llround ((when - t.ppq) * samplesPerQuarter), 0, numSamples - 1);
            releaseDue (k, offset, out);
            stepOn (k, offset, s, out);
        }
        lastPpqEnd = ppqEnd;
        cur = nullptr;
    }

private:
    static constexpr float kKeepRatio = 0.5f;   // so gut muss die laufende Wendung mindestens passen, sonst wird gewechselt

    struct Active { uint8_t channel, note; long long endStep; };

    // Wo im Takt / in der Phrase / in der Wendung ein Schritt liegt
    struct Pos
    {
        long long k, bar, phrase; int pos, barInPhrase;
        int chordIdx; long long chordStart, chordEnd, phraseStart, phraseEnd;
        bool passing = false;   // Durchgangsakkord am Ende des Akkords
    };

    static long long floorDiv (long long a, long long b) { return a >= 0 ? a / b : -((-a + b - 1) / b); }

    const Wendung& W() const { return current == kCustomWendung ? custom : kWendungen[std::clamp (current, 0, kNumWendungen - 1)]; }

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
        long long cs = std::max (wendungStart, p.phraseStart);
        p.chordIdx = w.n - 1;
        for (int i = 0; i < w.n; ++i)
        {
            const long long ce = cs + (long long) w.ch[i].bars * meter.len;
            if (k < ce || i == w.n - 1) { p.chordIdx = i; break; }
            cs = ce;
        }
        p.chordStart = cs;
        p.chordEnd = std::min (p.phraseEnd, cs + (long long) w.ch[p.chordIdx].bars * meter.len);
        if (p.chordIdx == w.n - 1) p.chordEnd = p.phraseEnd;   // letzter Akkord haelt bis zur Phrasengrenze
        if (cur != nullptr && cur->passing && cur->y >= 0.6f && p.chordEnd - p.chordStart >= meter.len)
        {
            const long long ps = p.chordEnd - (meter.len - meter.groupStart[std::max (0, meter.numGroups - 1)]);   // letzte Betonungsgruppe
            if (k >= ps) { p.chordStart = ps; p.passing = true; }
            else p.chordEnd = ps;
        }
        return p;
    }

    void ensurePhrase (long long phrase, const Settings& s)
    {
        if (phrase == phraseIndex) return;
        current = s.custom ? kCustomWendung : pick (s, phrase);
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
    bool maybeSwitch (long long k, const Pos& p, const Settings& s)
    {
        if (k == p.phraseStart || ! isChangePoint (p, s)) return false;
        if (current == kCustomWendung)   // eigene Folge: nur der geliehene Stil wechselt, die Akkorde bleiben
        {
            if (style < 0 || weight (kWendungen[style], s) < std::min (kKeepRatio, keepRatio (s)) * bestWeight (s)) style = pick (s, k * 7 + 3);
            return false;
        }
        if (s.custom) return false;
        if (weight (kWendungen[current], s) >= std::min (kKeepRatio, keepRatio (s)) * bestWeight (s)) return false;
        current = pick (s, k * 7 + 3);
        wendungStart = k;
        return true;
    }

    const Wendung& SW() const { return current == kCustomWendung ? kWendungen[std::clamp (style, 0, kNumWendungen - 1)] : W(); }

    int nextChordRoot (const Pos& p) const
    {
        const Wendung& w = W();
        return (p.chordIdx + 1 < w.n ? w.ch[p.chordIdx + 1] : w.ch[0]).root;
    }

    Chord chordFor (const Pos& p, int layer, const Settings& s) const
    {
        const Wendung& w = W();
        if (p.passing && (layer > kArp || s.follow[layer]))
            return Chord { (nextChordRoot (p) + 7) % 12, Dom7, 1 };
        if (layer <= kArp && ! s.follow[layer])
        {
            Chord tonic = w.ch[0]; tonic.root = current == kCustomWendung ? w.ch[0].root : 0;
            tonic.bass = -1;
            tonic.type = kShapes[w.ch[0].type].minor ? Min : Maj;
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

    // Unruhe faerbt die Flaeche: Reibung durch grosse Septime, bei viel Unruhe zusaetzlich die None
    static int padType (int type, float z)
    {
        if (z >= 0.75f && (type == Min || type == Min7 || type == MinMaj7 || type == Min9)) return MinMaj9;
        if (z >= 0.45f)
        {
            if (type == Min || type == Min7) return MinMaj7;
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
        if (s.padPattern != PadAuto) return s.padPattern;
        const float y = layerY (s, kFlaeche);
        return y < 0.3f ? PadHeld : SW().pad;
    }

    void releaseDue (long long step, int offset, EventList& out)
    {
        for (int i = 0; i < numActive;)
        {
            if (active[(size_t) i].endStep <= step)
            {
                out.add (offset, active[(size_t) i].channel, active[(size_t) i].note, 0);
                active[(size_t) i] = active[(size_t) --numActive];
            }
            else ++i;
        }
    }

    void releaseSilencedLayers (const Settings& s, EventList& out)
    {
        for (int i = 0; i < numActive;)
        {
            if (! layerActive (s, active[(size_t) i].channel - 1))
            {
                out.add (0, active[(size_t) i].channel, active[(size_t) i].note, 0);
                active[(size_t) i] = active[(size_t) --numActive];
            }
            else ++i;
        }
    }

    // Beim Wechsel der Wendung: gehaltene Toene der alten Stimmung sofort beenden
    void releaseHeld (int offset, EventList& out)
    {
        for (int i = 0; i < numActive;)
        {
            const int layer = active[(size_t) i].channel - 1;
            if (layer == kFlaeche || layer == kBass || layer == kFarbe)
            {
                out.add (offset, active[(size_t) i].channel, active[(size_t) i].note, 0);
                active[(size_t) i] = active[(size_t) --numActive];
            }
            else ++i;
        }
    }

    void noteOn (int layer, int note, int velocity, long long endStep, int offset, EventList& out)
    {
        if (cur != nullptr && ! layerActive (*cur, layer)) return;
        const int channel = layer + 1;
        if (cur != nullptr) note += 12 * cur->octave[layer];
        note = std::clamp (note, 0, 127);
        velocity = std::clamp (velocity, 1, 127);
        for (int i = 0; i < numActive; ++i)
            if (active[(size_t) i].channel == channel && active[(size_t) i].note == note)
            {
                out.add (offset, channel, note, 0);
                active[(size_t) i] = active[(size_t) --numActive];
                break;
            }
        if (numActive >= kMaxActive) return;
        out.add (offset, channel, note, velocity);
        active[(size_t) numActive++] = { (uint8_t) channel, (uint8_t) note, endStep };
    }

    int jitter (long long k, int layer, int range) const
    {
        return (int) (hash3 ((uint32_t) cur->variation, (uint32_t) k, (uint32_t) layer) % (uint32_t) (2 * range + 1)) - range;
    }

    static int padLow (const Settings& s)  { return 62 + (int) std::lround (s.x * 6.0f); }   // Flaeche: mittlere Lage
    static int bassLow (const Settings& s) { return 45 + (int) std::lround (s.x * 4.0f); }   // Bass: A2 bis Cis3

    // --- Flaeche
    void padChord (const Pos& p, const Settings& s, int offset, long long endStep, int velocity, EventList& out)
    {
        // Weiter Satz wie im Orchester: Grundton und Quinte unten, Terz und Farbtoene eine Oktave hoeher
        const Chord c = chordFor (p, kFlaeche, s);
        const ChordShape& sh = kShapes[padType (c.type, s.z)];
        const float y = layerY (s, kFlaeche);
        // VARIATION bei eigener Folge: weit, eng oder weit ohne tiefen Grundton
        const int voicing = current == kCustomWendung ? hashInt (91u, p.chordStart) % 3 : 0;
        const int root = voicing == 1 ? place (s.key + c.root, padLow (s) - 5) : place (s.key + c.root, padLow (s) - 12);
        int voices = sh.n;
        if (y < 0.2f) voices = std::min (voices, 3);
        for (int i = 0; i < voices; ++i)
        {
            const int iv = sh.iv[i];
            bool low = iv == 0 || iv == 7 || (iv == 5 && c.type == Quartal) || iv >= 12;
            if (voicing == 1) low = true;
            if (voicing == 2 && iv == 0) low = false;
            noteOn (kFlaeche, root + iv + (low ? 0 : 12), velocity - (i == 0 ? 0 : 4), endStep, offset, out);
        }
        if (y > 0.6f) noteOn (kFlaeche, root + 24, velocity - 10, endStep, offset, out);   // Verdopplung oben
    }

    // --- Farbe: Grundfarbe (None) und bei Unruhe ein fremder Ton
    void colour (const Pos& p, const Settings& s, int offset, EventList& out)
    {
        const Chord c = chordFor (p, kFarbe, s);
        if (layerY (s, kFarbe) >= kLayerStart[kFarbe])
        {
            const int ninth = place (s.key + c.root + 14, 74 + (int) std::lround (s.x * 4.0f));
            noteOn (kFarbe, ninth, (int) (35 + 40 * layerY (s, kFarbe)), p.chordEnd, offset, out);
        }
    }

    void foreignTone (const Pos& p, const Settings& s, int offset, EventList& out)
    {
        const Chord c = chordFor (p, kFarbe, s);
        const int interval = s.x < 0.5f ? 1 : 6;                          // dunkel: kleine None, hell: uebermaessige Quarte
        const int note = place (s.key + c.root + interval, 79);
        noteOn (kFarbe, note, (int) (30 + 45 * s.z), p.chordEnd, offset, out);
        if (s.z >= 0.8f && layerY (s, kFarbe) < 0.5f)                                      // Halbton-Reibung ganz oben
            noteOn (kFarbe, note + 11, (int) (25 + 30 * s.z), p.chordEnd, offset, out);
    }

    // Liegetoene einer Akkordposition (Flaeche gehalten, Bass gehalten, Farbe)
    void sustained (const Pos& p, const Settings& s, int offset, EventList& out, bool restart)
    {
        const int pad = choosePad (s);
        const bool padFollow = s.follow[kFlaeche];
        const bool phraseStart = p.k == p.phraseStart;
        if (pad == PadHeld && (padFollow || phraseStart || restart))
            padChord (p, s, offset, padFollow ? p.chordEnd : p.phraseEnd, (int) (40 + 45 * layerY (s, kFlaeche)), out);

        const int bp = chooseBass (s, p.phrase);
        if ((bp == BassHeld && (s.follow[kBass] || phraseStart || restart)) || bp == BassPedal)
        {
            const bool pedal = bp == BassPedal;
            noteOn (kBass, place (s.key + (pedal ? pedalRoot() : bassRoot (chordFor (p, kBass, s))), bassLow (s)),
                    (int) (60 + 35 * layerY (s, kBass)), (s.follow[kBass] && ! pedal) ? p.chordEnd : (pedal ? p.chordEnd : p.phraseEnd), offset, out);
        }
        colour (p, s, offset, out);
    }

    void chase (double ppq, const Settings& s, EventList& out)
    {
        if (ppq < 0.0) return;
        const long long k = (long long) std::floor (ppq / kStep + 1e-9);
        ensurePhrase (phraseOf (k), s);
        const Pos p = locate (k);
        curChord = p.chordIdx;
        curRoot = W().ch[p.chordIdx].root; curType = W().ch[p.chordIdx].type;
        if (ppq > (double) p.chordStart * kStep + 1e-9)
            sustained (p, s, 0, out, true);
        else
            chaseStep = k;   // genau am Akkordanfang: der normale Schritt schlaegt an, auch die stehenden Ebenen
    }

    void stepOn (long long k, int offset, const Settings& s, EventList& out)
    {
        const long long phrase = phraseOf (k);
        ensurePhrase (phrase, s);
        Pos p = locate (k);
        bool restart = k == chaseStep;
        if (maybeSwitch (k, p, s))
        {
            releaseHeld (offset, out);        // alte Stimmung sauber beenden
            p = locate (k);
            restart = true;
        }
        chaseStep = -1;
        const Wendung& w = W();
        curChord = p.chordIdx; curRoot = w.ch[p.chordIdx].root; curType = w.ch[p.chordIdx].type;
        if (p.passing && s.follow[kFlaeche]) { curRoot = (nextChordRoot (p) + 7) % 12; curType = Dom7; }
        const bool chordStart = k == p.chordStart;
        const bool beat = p.pos % 4 == 0;
        const bool group = meter.isGroupStart (p.pos);
        const float z = s.z;
        const float yPad = layerY (s, kFlaeche), yBass = layerY (s, kBass), yArp = layerY (s, kArp);

        if (chordStart)
            sustained (p, s, offset, out, restart);

        // Unruhe: fremder Ton in der Mitte des Akkords (das "quietschende" Element)
        if (z >= 0.35f && layerActive (s, kFarbe) && k == p.chordStart + (p.chordEnd - p.chordStart) / 2)
            foreignTone (p, s, offset, out);

        // --- Flaeche: Schlaege, Puls oder Staccato
        const int pad = choosePad (s);
        if (pad == PadStabs && p.pos % 4 == 2)
            padChord (p, s, offset, k + 1, (int) (55 + 40 * yPad) + jitter (k, kFlaeche, 4), out);
        else if (pad == PadPulse && beat)
            padChord (p, s, offset, k + 3, (int) (50 + 40 * yPad) + (group ? 8 : 0), out);
        else if (pad == PadStaccato && beat)
            padChord (p, s, offset, k + 1, (int) (48 + 40 * yPad) + (group ? 6 : 0), out);

        // --- Bass
        {
            const Chord c = chordFor (p, kBass, s);
            const ChordShape& sh = kShapes[c.type];
            const int low = bassLow (s);
            int root = place (s.key + (pattern0 (s, phrase) == BassPedal ? pedalRoot() : bassRoot (c)), low);
            const int vel = (int) (58 + 38 * yBass) + (group ? 8 : 0) + jitter (k, kBass, 3);
            const int pattern = pattern0 (s, phrase);
            const bool lastEighth = k == p.chordEnd - 2;
            // Chromatische Annaeherung an den naechsten Grundton im letzten Achtel des Akkords
            const bool approach = s.follow[kBass] && (z >= 0.3f || pattern == BassFunk) && lastEighth
                                  && pattern != BassHeld && pattern != BassWalking && pattern != BassHeartbeat;
            if (approach)
            {
                const int target = place (s.key + nextRoot (p), low);
                root = target - 1 >= low ? target - 1 : target + 1;
            }
            switch (pattern)
            {
                case BassHalf:     if (p.pos % 8 == 0 || approach) noteOn (kBass, root, vel, k + (approach ? 2 : 7), offset, out); break;
                case BassQuarter:  if (beat || approach) noteOn (kBass, root, vel, k + (approach ? 2 : 3), offset, out); break;
                case BassEighth:   if (p.pos % 2 == 0) noteOn (kBass, root, vel, k + 2, offset, out); break;
                case BassPulse:    noteOn (kBass, root, vel - (group ? 0 : 10), k + 1, offset, out); break;
                case BassFunk:
                {
                    const int q = p.pos % 8;
                    if (approach) noteOn (kBass, root, vel, k + 1, offset, out);
                    else if (q == 0) noteOn (kBass, root, vel + 6, k + 2, offset, out);
                    else if (q == 3) noteOn (kBass, root, vel - 6, k + 1, offset, out);
                    else if (q == 5) noteOn (kBass, root + 7, vel - 8, k + 1, offset, out);
                    else if (q == 6 && p.pos % 16 == 14) noteOn (kBass, root + 12, vel - 4, k + 1, offset, out);   // kurzer Sprung nur am Taktende
                    break;
                }
                case BassPendulum:
                {
                    const int rate = yBass > 0.6f ? 2 : 4;
                    if (p.pos % rate == 0)
                    {
                        const int other = z >= 0.5f ? 1 : 3;                 // Halbton (Unruhe) oder kleine Terz
                        const int n = (p.pos / rate) % 2 == 0 ? root : root + other;
                        noteOn (kBass, n, vel, k + rate - 1, offset, out);
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
                            const int target = place (s.key + nextRoot (p), low);
                            n = (b % 2 == 0) ? target - 1 : target + 1;
                        }
                        else
                        {
                            const int steps[4] = { 0, sh.iv[1], sh.iv[2], sh.n > 3 ? sh.iv[3] : 12 };
                            n = root + steps[b % 4];
                        }
                        noteOn (kBass, n, vel, k + 3, offset, out);
                    }
                    break;
                case BassAlternating:
                    if (beat || approach)
                    {
                        const bool odd = ((p.pos / 4) % 2) == 1;
                        noteOn (kBass, approach ? root : (odd ? root - 5 : root), vel - (odd ? 6 : 0), k + 2, offset, out);   // Grundton, Quinte darunter
                    }
                    break;
                case BassPedal:   // Orgelpunkt: liegt (in sustained), bei viel Intensitaet zusaetzlich ein Puls auf den Schlaegen
                    if (yBass > 0.6f && beat && k != p.chordStart) noteOn (kBass, root, vel - 12, k + 1, offset, out);
                    break;
                case BassHeartbeat:
                    if (p.pos % 8 == 0) noteOn (kBass, root, vel + 4, k + 1, offset, out);
                    else if (p.pos % 8 == 2) noteOn (kBass, root, vel - 10, k + 4, offset, out);
                    break;
                case BassArpeggio:
                    if (p.pos % 2 == 0)
                    {
                        const int startIdx = (int) (((p.bar % sh.n) + sh.n) % sh.n);                // Startton wechselt je Takt
                        const int i = (p.pos / 2 + startIdx) % sh.n;
                        noteOn (kBass, root + sh.iv[i] - (sh.iv[i] > 7 ? 12 : 0), vel, k + 2, offset, out);
                    }
                    break;
                default: break;
            }
        }

        // --- Arp / Figur
        if (layerActive (s, kArp))
        {
            const int fig = chooseArp (s, phrase);
            int rate = s.arpRate == RateQuarter ? 4 : s.arpRate == RateEighth ? 2 : s.arpRate == RateSixteenth ? 1
                     : (yArp < 0.15f ? 4 : yArp < 0.5f ? 2 : 1);
            if (fig == ArpGlitter) rate = 1;
            const long long rel = k - (s.follow[kArp] ? p.chordStart : p.phraseStart);
            if (rel % rate == 0)
            {
                const Chord c = chordFor (p, kArp, s);
                const ChordShape& sh = kShapes[c.type];
                const int base = place (s.key + c.root, 55 + (int) std::lround (s.x * 7.0f)) + (fig == ArpGlitter ? 12 : 0);
                int tones[10]; const int n = std::min (sh.n, 5), count = 2 * n;
                for (int i = 0; i < count; ++i) tones[i] = base + sh.iv[i % n] + 12 * (i / n);
                const long long c0 = rel / rate + (long long) (hashInt (77u, s.follow[kArp] ? p.chordStart : phrase) % 4);
                int note = base;
                switch (fig)
                {
                    case ArpDown:    note = tones[count - 1 - (int) (c0 % count)]; break;
                    case ArpCircle:  { const int period = 2 * count - 2; const int q = (int) (c0 % period); note = tones[q < count ? q : period - q]; break; }
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
                const long long len = (fig == ArpGlitter || rate == 1) ? 1 : rate;
                noteOn (kArp, note, vel, k + len, offset, out);
            }
        }

        // --- Gegenstimme: ruhige Linie aus Akkordtoenen, schrittweise gefuehrt
        counterLine (k, p, s, offset, chordStart, out);
    }

    // Zielton der Gegenstimme: Akkordton nahe am vorigen Ton, Terz und Septime bevorzugt, nicht der Ton der Farbe
    int counterTarget (const Chord& c, const Settings& s, bool chordStart, long long k) const
    {
        const ChordShape& sh = kShapes[c.type];
        const int lo = 60 + (int) std::lround (s.x * 4.0f);
        const int rootPc = (s.key + c.root) % 12, colourPc = (rootPc + 2) % 12;
        const int prev = csNote >= 0 ? csNote : lo + 7;
        int best = -1; float bestScore = 1e9f;
        for (int n = lo; n <= lo + 14; ++n)
        {
            const int pc = n % 12;
            bool inChord = false;
            for (int i = 0; i < sh.n; ++i) inChord = inChord || (rootPc + sh.iv[i]) % 12 == pc;
            if (! inChord || (pc == colourPc && sh.n > 1)) continue;
            const int d = n - prev;
            float score = (float) std::abs (d);
            if (d == 0 && ! chordStart) score += 3.0f;            // innerhalb des Akkords: weitergehen
            if (pc == rootPc) score += 1.5f;                       // Grundton hat der Bass
            if (s.x < 0.4f && d > 0) score += 0.5f;                // dunkel: eher abwaerts
            if (s.x > 0.6f && d < 0) score += 0.5f;                // hell: eher aufwaerts
            score += (float) (hash3 ((uint32_t) s.variation, (uint32_t) (k * 16 + n), 401u) % 100u) / 250.0f;
            if (score < bestScore) { bestScore = score; best = n; }
        }
        return best >= 0 ? best : place (s.key + c.root + sh.iv[std::min (1, sh.n - 1)], lo);
    }

    void counterLine (long long k, const Pos& p, const Settings& s, int offset, bool chordStart, EventList& out)
    {
        if (! layerActive (s, kGegenstimme)) { csNote = -1; csPendingAt = -1; return; }
        const float yc = layerY (s, kGegenstimme);
        const int vel = (int) (50 + 35 * yc);
        if (k == csPendingAt && csPending >= 0)                    // Vorhalt loest sich auf
        {
            noteOn (kGegenstimme, csPending, vel, csPendingEnd, offset, out);
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
            noteOn (kGegenstimme, sus, vel + 6, k + 4, offset, out);
            csPending = target; csPendingAt = k + 4; csPendingEnd = end;
            csNote = sus;
            return;
        }
        noteOn (kGegenstimme, target, vel, end, offset, out);
        csNote = target;
    }

    static constexpr int kMaxActive = 96;
    std::array<Active, kMaxActive> active {};
    int numActive = 0;
    bool running = false, wasCustom = false;
    double lastPpqEnd = 0.0;
    long long phraseIndex = -1, wendungStart = 0, chaseStep = -1;
    int current = -1, curChord = -1, curRoot = 0, curType = Min, style = -1;
    int csNote = -1, csPending = -1;                 // Gegenstimme: letzter Ton, aufzuloesender Vorhalt
    long long csPendingAt = -1, csPendingEnd = 0;
    int phraseBars = kPhraseBars;
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
        if (e.velocity == 0)
        {
            for (auto& v : voices)
                if (v.on && ! v.releasing && v.channel == e.channel && v.note == e.note) v.releasing = true;
            return;
        }
        Voice* slot = &voices[0];
        for (auto& v : voices) if (! v.on) { slot = &v; break; }
        static constexpr float layerGain[kNumLayers] = { 0.04f, 0.07f, 0.04f, 0.03f, 0.06f };
        const float freq = 440.0f * std::pow (2.0f, ((float) e.note - 69.0f) / 12.0f);
        *slot = {};
        slot->on = true; slot->channel = e.channel; slot->note = e.note;
        slot->inc = (float) (2.0 * 3.14159265358979 * freq / sampleRate);
        slot->gain = layerGain[std::clamp ((int) e.channel - 1, 0, kNumLayers - 1)] * (float) e.velocity / 127.0f;
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
