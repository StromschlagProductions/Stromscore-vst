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
#include "BassPhrase.h"
#include "WendungId.h"
#include "HarmonicPreferences.h"
#include "DrivePath.h"
#include "HarmonyRuntime.h"

namespace stromscore
{
constexpr int kNumLayers = 6;
enum Layer { kFlaeche = 0, kBass = 1, kArp = 2, kAkzent = 3, kGegenstimme = 4, kMelodie = 5 };
// Ausgaenge: jede Ebene schickt auf einen oder zwei frei waehlbare MIDI-Kanaele
// (Flaeche und Bass: lang und kurz, Akzent: Tupfer und Stich)
constexpr int kNumOutputs = 9;
enum Output { OutPadLong = 0, OutPadShort, OutBassLong, OutBassShort, OutArp, OutTupfer, OutStich, OutCounter, OutMelody };
constexpr int kOutputLayer[kNumOutputs] = { kFlaeche, kFlaeche, kBass, kBass, kArp, kAkzent, kAkzent, kGegenstimme, kMelodie };
// Tonumfang: je Ebene, der Akzent hat zwei (Tupfer und Stich spielen oft auf verschiedenen Instrumenten)
constexpr int kNumRanges = 7;
constexpr int kOutputRange[kNumOutputs] = { 0, 0, 1, 1, 2, 3, 5, 4, 6 };
constexpr int kNumKeys = 12;
constexpr double kStep = musicaltime::quartersPerGridStep;          // Raster: Sechzehntel (in Viertelnoten)
constexpr int kPhraseBars = 8;          // eine Wendung = 8 Takte

// Ab welcher Intensitaet eine Ebene im Modus Auto einsetzt (Akzent zusaetzlich bei Unruhe ab 0,35)
// Neutral UI threshold projections; all engine decisions read Settings::policy.
inline constexpr auto& kLayerStart = composition::neutralFreePolicy.texture.activityStart;
static_assert(kNumLayers==static_cast<int>(composition::TexturePart::count));
constexpr float kStichStart = composition::neutralFreePolicy.texture.stichStart;     // der zweite Akzent (Stich) kommt erst bei mehr Intensitaet dazu

constexpr float kRissStart = 0.8f;     // ab hier reisst die Unruhe: kurze Halbton-Stoesse hoch ueber dem Satz (ab 1.4)

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
    { kFlaeche, kBass, kArp, kGegenstimme, kAkzent , kMelodie },   // Auto (wird vorher aufgeloest)
    { kFlaeche, kBass, kArp, kGegenstimme, kAkzent , kMelodie },   // Flaeche, schuechtern
    { kBass, kArp, kFlaeche, kAkzent, kGegenstimme , kMelodie },   // Bass-Schlag
    { kBass, kFlaeche, kArp, kAkzent, kGegenstimme , kMelodie },   // Puls
    { kArp, kBass, kFlaeche, kGegenstimme, kAkzent , kMelodie },   // Arpeggio
    { kAkzent, kFlaeche, kBass, kArp, kGegenstimme , kMelodie },   // Akzent
    { kGegenstimme, kFlaeche, kBass, kArp, kAkzent , kMelodie },   // Gegenstimme
    { kFlaeche, kBass, kArp, kGegenstimme, kAkzent , kMelodie } }; // Alles zugleich (Reihenfolge nur fuers Ausduennen)
constexpr int kEntryLayer[kNumEntries] = { -1, kFlaeche, kBass, kBass, kArp, kAkzent, kGegenstimme, -1 };

// ------------------------------------------------------------------ Ein- und Ausgabe
struct CustomChord { int rootAbs = 0; int type = Maj; int bars = 0; };   // bars 0 = Platz leer

struct Settings
{
    composition::ProfileId profile=composition::ProfileId::neutral; // Internal selection, no GUI/host parameter.
    composition::FreeCompositionPolicy policy = *composition::policyForProfile(composition::ProfileId::neutral); // Internal scene policy; no host parameter or preset switch.
    bool melodyLegato = true, melodyMotif = true;
    bool melody = false; // Explicit foreground opt-in; background is the default.
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
    bool rangeOn[kNumRanges] = {false,false,false,false,false,false,true};                            // Tonumfang begrenzen (fuer Orchesterinstrumente); [3] Tupfer, [5] Stich
    int rangeLo[kNumRanges] = { 0, 0, 0, 0, 0, 0, 60 };           // tiefster spielbarer Ton (MIDI-Nummer)
    int rangeHi[kNumRanges] = { 127, 127, 127, 127, 127, 127, 84 };   // hoechster spielbarer Ton
    int channel[kNumOutputs] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };    // MIDI-Kanal je Ausgang (1 ... 16), doppelte Belegung erlaubt
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

inline bool hasSolo(const Settings& s)
{
    for(int layer=0;layer<kNumLayers;++layer)
        if(s.solo[layer]&&(layer!=kMelodie||(s.melody&&s.genre==GenreScore)))return true;
    return false;
}

// The only standard capability definitions for the current generator outputs.
// These describe emitted MIDI, never verified external patch capabilities.
inline std::array<composition::OutputDescription,kNumOutputs> outputCatalog(const Settings& s)
{
    using namespace composition;
    struct Standard { PlayingStyle style; int voices; int64_t maxDuration; unsigned roles; };
    const auto accompaniment=roleBit(MusicalRole::accompaniment);
    const Standard standards[kNumOutputs]={
        {PlayingStyle::sustained,6,1<<24,accompaniment},
        {PlayingStyle::detached,9,3,accompaniment},
        {PlayingStyle::sustained,1,1<<24,accompaniment},
        {PlayingStyle::detached,1,4,accompaniment},
        {PlayingStyle::detached,1,32,accompaniment|roleBit(MusicalRole::answer)},
        {PlayingStyle::detached,4,3,accompaniment},
        {PlayingStyle::detached,1,2,accompaniment},
        {PlayingStyle::sustained,2,1<<24,roleBit(MusicalRole::lead)|roleBit(MusicalRole::answer)},
        {PlayingStyle::sustained,1,1<<24,roleBit(MusicalRole::lead)} };
    const char* uses[kNumOutputs]={"Gehaltene Harmonie","Akkordimpulse und Riss","Bassfundament und Pedal",
        "Rhythmische Bassfigur","Arpeggio, Figur und Antwort","Farbiger Einwurf","Akzentschlag","Melodielinie, Motiv und Frage","Optionale Vordergrundmelodie"};
    std::array<OutputDescription,kNumOutputs> result {};
    const bool anySolo=hasSolo(s);
    for(int o=0;o<kNumOutputs;++o)
    {
        auto& entry=result[static_cast<size_t>(o)];auto& track=entry.track;
        const auto& standard=standards[o];const int layer=kOutputLayer[o],range=kOutputRange[o];
        entry.standardUse=uses[o];entry.target={o,s.channel[o],s.stichNote};track.id={1000+o};
        track.style=standard.style;track.roles=standard.roles;
        track.available=(layer!=kMelodie||(s.melody&&s.genre==GenreScore))&&!s.mute[layer]&&(!anySolo||s.solo[layer]);
        auto& c=track.instrument;c.pitch=PitchBehaviour::pitched;
        c.articulations=1u<<static_cast<unsigned>(standard.style);
        c.polyphony=standard.voices;c.maxDuration=standard.maxDuration;
        c.range=s.rangeOn[range]?Range{s.rangeLo[range],s.rangeHi[range]}:Range{0,127};
        if(o==OutStich&&s.stichFixed)
        {
            track.addressing=NoteAddressing::fixedTrigger;
            c.pitch=PitchBehaviour::unknown; // A fixed key says nothing about the sample's sound.
            c.range={s.stichNote,s.stichNote};
        }
    }
    return result;
}

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
    void reset() { bassPhrase={};bassPairStart=-1;harmonicChase=false; clearHarmonicEntries(); motifCatalog.clear(); voices={}; style = -1; chaseStep = -1; lastGenre = -1; resetCc(); resetVoicing(); numActive = 0; running = false; lastPpqEnd = 0.0; phraseIndex = -1; current = -1; wendungStart = 0; still = false; chordBase = 0; drivePrev = driveSeen = driveLatched = driveArrivedNow = false; driveTrajectory = false; driveProgressNow = 0; driveGenerationSeen = 0; curRoot = 0; curType = Min; curChord = -1;
                   sceneStep = 0; manualEndStep = -1; manualFinished = manualHitSent = false; endWasRequested = false; sceneSeed = 0; autoSeed = -1; sceneBarNow = -1; sceneEnded = false; for (int l = 0; l < kNumLayers; ++l) { on[l] = prevOn[l] = hOn[l] = false; } }

    uint32_t unavailablePadPitchClasses() const { return unavailablePad; }

    // Fuer die Anzeige: Szene
    int sceneBar() const { return sceneBarNow; }              // Takte seit Szenenstart (-1: steht)
    int sceneEntry() const { return entryInUse; }             // aufgeloester Einstieg
    bool sceneOver() const { return sceneEnded; }
    int activeSeed() const { return sceneSeed; }
    const composition::RememberedMotif& rememberedMotif(int output=OutCounter) const { return voice(output).motif.material(motifCatalog); }
    const composition::MotifUse& motifUse(int output)const { return voice(output).motif; }
    const composition::MotifUse& answerUse()const { return voice(OutCounter).answer; }
    // Offline/read-only inspection: reconstruct the same plan without changing performance state.
    composition::LinePhrasePlan inspectFreePhrase(long long tick,Settings settings)const
    {auto snapshot=*this;snapshot.cur=&settings;return snapshot.freeLinePhrase(snapshot.locate(tick),settings);}
    composition::MotifOccurrence inspectMotifOccurrence(long long tick,Settings settings,int output=OutCounter)const
    {
        auto snapshot=*this;snapshot.cur=&settings;
        if((settings.genre!=GenreScore&&!snapshot.phrasedHook(settings))||!on[kOutputLayer[output]]||(settings.genre==GenreScore&&!(output==OutMelody?settings.melodyMotif:settings.motif))
            ||(output==OutCounter&&on[kMelodie]))return {};
        return snapshot.motifOccurrence(tick,snapshot.locate(tick),settings,output);
    }
    composition::BassPhrasePlan inspectBassPhrase()const{return bassPhrase;}
    composition::RhythmPlan inspectMovementRhythm(long long tick,const Settings& s)const
    {auto snapshot=*this;snapshot.cur=&s;return snapshot.movementRhythm(snapshot.locate(tick),s);}
    composition::ChordDispositionResult inspectChordDisposition()const{return lastDisposition;}
    long long inspectChordDispositionStep()const{return dispositionAt;}
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
        if(layer==kMelodie&&(!s.melody||s.genre!=GenreScore))return false;
        const bool anySolo=hasSolo(s);
        return anySolo ? s.solo[layer] : ! s.mute[layer];
    }
    // Schwelle erreicht (ohne Mute/Solo); levelOff: weit genug darunter, dass die Traegheit loslaesst
    static bool levelOn (const Settings& s, int layer)
    {
        const float y = layerY (s, layer);
        if (layer == kAkzent) return y >= s.policy.texture.start(composition::TexturePart::accents) || s.z >= s.policy.texture.accentUnrest;
        return y >= s.policy.texture.start(static_cast<composition::TexturePart>(layer));
    }
    static bool levelOff (const Settings& s, int layer)
    {
        const float y = layerY (s, layer);
        if (layer == kAkzent) return y < s.policy.texture.start(composition::TexturePart::accents) - s.policy.texture.activityHysteresis && s.z < s.policy.texture.accentUnrest - s.policy.texture.activityHysteresis;
        return y < s.policy.texture.start(static_cast<composition::TexturePart>(layer)) - s.policy.texture.activityHysteresis;
    }

    // Einstieg bei Auto: gewuerfelt aus dem Wurf, gewichtet nach Genre und Stimmungsfeld (nur Ebenen, die spielen koennen)
    static int autoEntry (const Settings& s)
    {
        const bool pop = s.genre == GenrePopRock;
        auto ok = [&s] (int l) { return muteSoloOk (s, l) && levelOn (s, l); };
        float w[kNumEntries] {};
        if (ok (kFlaeche)) w[EntryPad] = pop ? 1.0f : 3.0f + (s.z >= s.policy.texture.accentUnrest ? 1.0f : 0.0f) + (s.y < 0.3f ? 1.0f : 0.0f);
        if (ok (kBass)) { w[EntryBass] = 2.0f; w[EntryPulse] = 1.0f + (s.z >= s.policy.texture.accentUnrest ? 2.0f : 0.0f); }
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
        float w[kMaxWendungen],xyz[kMaxWendungen]; float best = 0.0f;
        for (int i = 0; i < count; ++i) { xyz[i] = weight (tbl[i], s); best = std::max (best, xyz[i]);
            w[i]=xyz[i]*composition::harmonicPreference(s.profile,tbl[i].id); }
        const float r = keepRatio (s);
        int n = 0;
        if (maxOut <= 0) return 0;
        for (int i = 0; i < count; ++i)
        {
            if (xyz[i] < r * best - 1e-9f) continue;
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
        for (int i = 0; i < count; ++i) { if (w[i] < ratio * best) w[i] = 0.0f;
            else w[i] *= composition::harmonicPreference(s.profile,tbl[i].id);
            total += w[i]; }
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
        captureRead=0;
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
        if(!composition::findProfile(s.profile))s.profile=composition::ProfileId::neutral;
        if(!composition::valid(s.policy.texture)||!composition::valid(s.policy.motif)||!composition::valid(s.policy.popHooks.recurrence)||!composition::valid(s.policy.passing)||!composition::valid(s.policy.bass)||!composition::valid(s.policy.rhythm)||!composition::valid(s.policy.chords))s.policy=composition::neutralFreePolicy;
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
            if(s.genre!=lastGenre){motifCatalog.clear();for(auto& state:voices){state.motif.clear();state.answer.clear();state.capture.clear();state.recurrenceEpoch=-1;}}
            phraseIndex = -1; wasCustom = s.custom; phraseBars = bars; style = -1;
            genre = s.genre; lastGenre = s.genre;
            if (running) releaseHeld (0, out);
        }

        if (! t.playing || ! std::isfinite (t.bpm) || ! std::isfinite (t.sampleRate) || ! std::isfinite (t.ppq) || std::abs (t.ppq) > 1.0e9 || t.bpm <= 0.0 || t.sampleRate <= 0.0 || numSamples <= 0)
        {
            if (running) allNotesOff (out, 0);
            for(auto& state:voices){state.capture.clear();if(!state.motif.material(motifCatalog).complete)state.motif.clear();}
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
            for(auto& state:voices)if(!state.motif.material(motifCatalog).complete)state.motif.clear();
            for(auto& state:voices)state.capture.clear();
            resetVoicing();
            heardHarmony={}; harmonicChase=true;
            driveTrajectory = false; // A seek reconstructs the curve at the destination, without old segment history.
            // Szenenstart: Wiedergabebeginn, auf den Taktanfang gerundet. Ein Sprung nach vorn (oder ein Loop, der nicht
            // vor den Start zurueckspringt) laeuft in derselben Szene weiter, ein Sprung davor beginnt eine neue.
            const long long k0 = (long long) std::floor (t.ppq / kStep + 1e-9);
            if (! running) { manualEndStep = -1; manualFinished = manualHitSent = false; endWasRequested = false; }
            if (! running || k0 < sceneStep) { bassPhrase={};bassPairStart=-1;clearHarmonicEntries(); motifCatalog.clear(); voices={}; sceneStep = floorDiv (k0, meter.len) * meter.len; driveLatched = false; drivePrev = false; driveSeen = false; }
            running = true;
            phraseIndex = -1;
            for(auto& state:voices){state.note=-1;state.pendingAt=-1;} resetCc();
            applyDrive (k0, s, ax, ay);
            chase (t.ppq, s, out);
            harmonicChase=false;
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
            capturePerformance(t.ppq,when,samplesPerQuarter,s,out);
            stepOn (k, offset, s, out);
            releaseDue (k, offset, out);
        }
        capturePerformance(t.ppq,ppqEnd,samplesPerQuarter,s,out);
        lastPpqEnd = ppqEnd;
        cur = nullptr;
    }

private:
    static constexpr float kKeepRatio = 0.5f;   // so gut muss die laufende Wendung mindestens passen, sonst wird gewechselt

    struct Active { uint8_t channel, note, out; musicaltime::Tick endTime, startTime; };

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
            else if (hOn[l] && levelOff (s, l) && k - hSince[l] >= static_cast<long long>(s.policy.texture.minimumActiveBars) * meter.len) hOn[l] = false;
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
            a.endTime = std::min (a.endTime, musicaltime::fromGridStep(until));
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
    int counterLadder (const Chord& c, const Settings& s, int* out, int output=OutCounter) const
    {
        const ChordShape& sh = kShapes[c.type];
        int a = 62 + (int) std::lround (s.x * 3.0f), b = a + 24;
        const int ri = kOutputRange[output];
        if (s.rangeOn[ri])
        {
            const int rlo = s.rangeLo[ri] - 12 * s.octave[kOutputLayer[output]], rhi = s.rangeHi[ri] - 12 * s.octave[kOutputLayer[output]];
            a = std::max (a, rlo); b = std::min (b, rhi);
            if (b - a < 7) { a = rlo; b = rhi; }
        }
        const int rootPc = (s.key + c.root) % 12;
        int n = 0;
        for (int m = a; m <= b && n < 16; ++m)
            for (int i = 0; i < sh.n; ++i)
                if ((rootPc + sh.iv[i]) % 12 == ((m % 12) + 12) % 12) { out[n++] = m; break; }
        if(n==0&&output==OutMelody)return 0;
        if (n == 0) out[n++] = place (s.key + c.root, a);
        return n;
    }

    struct PlannedMotifNote
    {
        long long at=0,length=0;int pitch=0,velocity=0;
        bool valid=false;
    };
    struct PlayableHandoff { composition::MotifHandoffPlan plan; int base=-1;int64_t origin=0; };
    int64_t motifAvailableUntil(const Settings& s,int layer)const
    {
        int64_t end=sceneEndStep;
        if(s.ending==EndFade&&(s.sceneBars>0||manualEndStep>=0))
        {
            int slots=0;const int index=orderIndex(s,entryInUse,layer,slots);
            const int tailBars=manualEndStep>=0?2:std::clamp(std::min(s.buildBars,s.sceneBars/2),1,64);
            if(index>0)end-=slotBar(index,slots,tailBars)*meter.len;
        }
        return end;
    }
    struct MotifHarmony { Chord chord;long long end=0; };
    // Canonical harmonic lookup across repeated custom cycles, independent of the live cursor.
    MotifHarmony motifHarmonyAt(long long at,const Settings& s)const
    {
        const auto& w=W();const long long length=static_cast<long long>(phraseBars)*meter.len;
        const long long begin=floorDiv(at,length)*length;
        composition::ChordTimeline timeline;timeline.count=w.n;timeline.begin=begin;timeline.end=begin+length;
        timeline.first=still?chordBase:0;timeline.held=still;
        for(int i=0;i<w.n;++i)timeline.durations[static_cast<size_t>(i)]=static_cast<int64_t>(w.ch[i].bars)*meter.len;
        const auto position=composition::locateChord(timeline,at);
        const auto& chord=w.ch[position.index];
        const int next=position.index+1<w.n?w.ch[position.index+1].root:w.ch[0].root;
        const auto intent=composition::freeTransition(next,allowsPassingHarmony(s),s.y,still);
        const auto placement=composition::placeTransition(intent,position.begin,position.end,meter.len,meter.groupStart[std::max(0,meter.numGroups-1)]);
        if(placement.present&&at>=placement.begin)return {{intent.approachRoot,Dom7,1},placement.end};
        return {chord,placement.present?placement.begin:position.end};
    }
    bool phrasedHook(const Settings& s)const
    {
        const int index=popHookPattern(W().id);
        if(s.genre!=GenrePopRock||!s.policy.popHooks.enabled)return false;
        if(s.custom?!s.policy.popHooks.phrasedCustom:(index<0||!s.policy.popHooks.phrased[static_cast<size_t>(index)]))return false;
        for(int o=0;o<kNumOutputs;++o)if(o!=OutCounter&&s.channel[o]==s.channel[OutCounter])return false;
        return true;
    }
    composition::RememberedMotif performanceMaterial(int output,const Settings& s)const
    {
        auto material=voice(output).motif.material(motifCatalog);
        if(s.genre!=GenrePopRock||material.timeScale==1)return material;
        const auto origin=voice(output).motif.originTick/material.timeScale;
        Settings recorded=s;recorded.swing=voice(output).captureSwing;
        auto stepAt=[&](int64_t at)
        {
            const auto estimate=static_cast<long long>(std::llround(static_cast<double>(at)/material.timeScale));
            auto best=estimate;double distance=1e20;
            for(auto n=estimate-2;n<=estimate+2;++n){const double d=std::abs((n+swingDelay(origin+n,recorded))*material.timeScale-at);if(d<distance){best=n;distance=d;}}
            return best;
        };
        for(int i=0;i<material.count;++i){auto& n=material.notes[i];const auto start=stepAt(n.at),end=stepAt(n.at+n.length);n.at=start;n.length=std::max<int64_t>(1,end-start);}
        material.cycleLength/=material.timeScale;material.timeScale=1;
        for(int i=0;i<material.count;++i)material.notes[i].length=std::max<int64_t>(1,std::min(material.notes[i].length,material.cycleLength-material.notes[i].at));
        return material;
    }
    composition::ModalContext modalContextFor(const Settings& s)const
    {
        const auto* metadata=s.custom?nullptr:findHarmonyTemplate(W().id);
        const auto mode=s.policy.passing.mode==composition::Mode::automatic&&metadata?metadata->tonality.mode:s.policy.passing.mode;
        const int centre=s.policy.passing.tonicOffset==0&&metadata?metadata->tonality.center:s.policy.passing.tonicOffset;
        unsigned vocabulary=0;bool tonic=false;
        for(int i=0;i<W().n;++i){const auto& c=W().ch[i];tonic|=c.root==centre;
            for(int j=0;j<kShapes[c.type].n;++j)vocabulary|=composition::pitchBit(s.key+c.root+kShapes[c.type].iv[j]);
            if(c.bass>=0)vocabulary|=composition::pitchBit(s.key+c.bass);}
        return composition::modalContext(vocabulary,s.key+centre,tonic,mode);
    }
    void addPassingTone(composition::MotifOccurrence& occurrence,const Settings& s,int output)const
    {
        const auto& policy=s.policy.passing;
        if(s.genre!=GenrePopRock||!phrasedHook(s)||!policy.enabled||!occurrence.active||occurrence.introduction
            ||occurrence.figure.variation!=composition::MotifVariation::original||occurrence.ordinal%policy.opportunityStride)return;
        auto& figure=occurrence.figure;if(figure.count>=10)return;
        const auto context=modalContextFor(s);if(context.status!=composition::ModalStatus::unique)return;
        const auto capabilities=outputCatalog(s)[output].track.instrument;
        for(int i=0;i+1<figure.count;++i)
        {
            const auto source=figure.notes[i],target=figure.notes[i+1];if(target.at-source.at<policy.minGap)continue;
            const auto sourceAt=occurrence.begin+source.at,targetAt=occurrence.begin+target.at;
            const auto h=motifHarmonyAt(sourceAt,s);if(targetAt>=h.end)continue;
            unsigned mask=0;for(int j=0;j<kShapes[h.chord.type].n;++j)mask|=composition::pitchBit(s.key+h.chord.root+kShapes[h.chord.type].iv[j]);
            composition::PassingRequest request;request.context=context;request.chordMask=mask;request.root=s.key+h.chord.root;request.bassPitchClass=s.key+bassRoot(h.chord);
            request.source=occurrence.base+source.interval;request.target=occurrence.base+target.interval;
            request.low=capabilities.range.low;request.high=capabilities.range.high;request.sourceAt=sourceAt;request.targetAt=targetAt;
            request.harmonyBegin=sourceAt;request.harmonyEnd=h.end;request.minDuration=static_cast<int>(capabilities.minDuration);
            request.maxDuration=static_cast<int>(std::min<int64_t>(policy.maxDuration,capabilities.maxDuration));
            const auto passing=composition::planPassingTone(request);if(!passing.valid)continue;
            for(int j=figure.count;j>i+1;--j)figure.notes[j]=figure.notes[j-1];
            figure.notes[i].length=std::min(figure.notes[i].length,passing.begin-sourceAt);
            figure.notes[i+1]={passing.begin-occurrence.begin,passing.end-passing.begin,passing.pitch-occurrence.base,std::max(1,target.velocity-6)};
            ++figure.count;figure.passingIndex=i+1;return;
        }
    }
    composition::MotifOccurrence motifOccurrence(long long k,const Pos& p,const Settings& s,int output)
    {
        auto& state=voice(output);const auto& use=state.motif;auto memory=performanceMaterial(output,s);
        const auto& policy=s.genre==GenrePopRock?s.policy.popHooks.recurrence:s.policy.motif;
        const auto origin=s.genre==GenrePopRock?use.originTick/musicaltime::ticksPerGridStep:use.originTick;
        const auto section=p.phrase-phraseOf(sceneStep);
        if(memory.count&&(k-p.phraseStart>=std::min(2LL*meter.len,p.phraseEnd-p.phraseStart)||section!=use.introduction))memory.finish();
        if(!memory.complete)return {true,true,false,p.phraseStart,p.phraseStart+std::min(2LL*meter.len,p.phraseEnd-p.phraseStart),0,0};
        const int64_t window=static_cast<int64_t>(policy.windowBars)*meter.len;
        if(k<origin)return {};
        const auto epoch=(k-origin)/window;
        int64_t span=0;for(int i=0;i<memory.count;++i)span=std::max(span,memory.notes[static_cast<size_t>(i)].at+memory.notes[static_cast<size_t>(i)].length);
        if(epoch==0)return {true,true,false,origin,origin+span,0,0};
        if(state.recurrenceEpoch==epoch&&state.recurrenceIdentity==memory.identity&&state.recurrenceOrigin==origin&&state.recurrenceWindow==window)return state.recurrencePlan.end<=motifAvailableUntil(s,kOutputLayer[output])?state.recurrencePlan:composition::MotifOccurrence{};
        state.recurrenceEpoch=epoch;state.recurrenceIdentity=memory.identity;state.recurrenceOrigin=origin;state.recurrenceWindow=window;state.recurrencePlan={};
        const auto slot=composition::recurrenceSlot(policy,epoch,layerY(s,kOutputLayer[output]),s.z);
        if(!slot.eligible)return {};
        const int64_t begin=origin+epoch*window,end=std::min(begin+window,motifAvailableUntil(s,kOutputLayer[output]));
        const bool dialogue=output==OutCounter&&!on[kMelodie]&&s.genre==GenreScore&&s.arpFigure==ArpCell&&!s.scene
            &&s.meterNum==4&&s.meterDen==4&&on[kArp]&&on[kGegenstimme]&&phraseBars>=4;
        const int64_t response=dialogue?2LL*meter.len:0;
        const auto catalog=outputCatalog(s);const auto& capability=catalog[output].track.instrument;
        auto attempt=[&](composition::MotifVariation variation)
        {
        const auto figure=composition::deriveMotif(memory,variation,policy.sequenceSemitones);
        if(!figure.count)return composition::MotifOccurrence{};
        const int64_t last=end-figure.span-static_cast<int64_t>(policy.minimumSilentBars)*meter.len-response;
        std::array<composition::MotifPlacement,32> candidates {};
        std::array<composition::MotifFigure,32> realizations {};int count=0;
        auto add=[&](int64_t at)
        {
            if(at<begin||at>last||count==32)return;
            for(int i=0;i<count;++i)if(candidates[static_cast<size_t>(i)].begin==at)return;
            unsigned allowed[10] {};
            for(int i=0;i<figure.count;++i)
            {
                const auto& n=figure.notes[static_cast<size_t>(i)];allowed[i]=0xfffu;
                auto tick=at+n.at;
                const auto harmonicLength=output==OutCounter&&i+1<figure.count
                    ?std::min(n.length,figure.notes[static_cast<size_t>(i+1)].at-n.at):n.length;
                const auto finish=tick+harmonicLength;
                if(n.length<capability.minDuration||n.length>capability.maxDuration)return;
                for(int step=0;tick<finish&&step<32;++step)
                {
                    const auto h=motifHarmonyAt(tick,s);unsigned mask=0;const auto& shape=kShapes[h.chord.type];
                    for(int j=0;j<shape.n;++j)mask|=1u<<((s.key+h.chord.root+shape.iv[j])%12);
                    allowed[i]&=mask;if(h.end<=tick)return;tick=std::min<int64_t>(finish,h.end);
                }
                if(tick<finish||!allowed[i])return;
            }
            int base=-1,cost=10000;auto realization=figure;
            for(int candidate=0;candidate<128;++candidate)
            {
                bool fits=true;auto adjusted=figure;int adjustment=0;
                for(int i=0;i<figure.count;++i)
                {
                    int pitch=candidate+figure.notes[static_cast<size_t>(i)].interval;
                    if(pitch<capability.range.low||pitch>capability.range.high||pitch<0||pitch>127){fits=false;break;}
                    if(!(allowed[i]&(1u<<((pitch%12+12)%12))))
                    {
                        int adapted=-1;
                        if(policy.adaptChordTones&&variation==composition::MotifVariation::original)
                            for(int d=1;d<=12&&adapted<0;++d)for(int q:{pitch-d,pitch+d})
                                if(adapted<0&&q>=capability.range.low&&q<=capability.range.high&&q>=0&&q<=127&&(allowed[i]&(1u<<(q%12))))adapted=q;
                        if(adapted<0){fits=false;break;}
                        adjustment+=std::abs(adapted-pitch);pitch=adapted;
                    }
                    adjusted.notes[static_cast<size_t>(i)].interval=pitch-candidate;
                }
                const int distance=std::abs(candidate-memory.origin)+adjustment;
                if(fits&&distance<cost){base=candidate;cost=distance;realization=adjusted;}
            }
            if(base>=0){
                if(policy.adaptChordTones&&variation==composition::MotifVariation::original)
                    for(int i=0;i+1<realization.count;++i)if(realization.notes[i].interval==realization.notes[i+1].interval)
                        realization.notes[i].length=std::min(realization.notes[i].length,realization.notes[i+1].at-realization.notes[i].at);
                realizations[static_cast<size_t>(count)]=realization;candidates[static_cast<size_t>(count++)]={at,base,cost};}
        };
        for(int64_t at=begin;at<=last;)
        {
            const auto h=motifHarmonyAt(at,s);add(at);
            const auto middle=at+std::max<int64_t>(0,(std::min<int64_t>(h.end,end)-at-figure.span)/2/meter.len)*meter.len;
            add(middle);if(h.end<=at)break;at=h.end;
        }
        auto result=composition::planRecurrence(policy,slot,begin,end,figure.span,meter.len,candidates.data(),count,response);
        if(result.active){for(int i=0;i<count;++i)if(candidates[i].begin==result.begin&&candidates[i].base==result.base){result.figure=realizations[i];break;}result.varied=variation==composition::MotifVariation::rhythm;}
        return result;
        };
        const auto variation=composition::motifVariation(policy,slot.ordinal);
        state.recurrencePlan=attempt(variation);
        if(!state.recurrencePlan.active&&variation!=composition::MotifVariation::original)
            state.recurrencePlan=attempt(composition::MotifVariation::original);
        addPassingTone(state.recurrencePlan,s,output);
        return state.recurrencePlan;
    }

    // One note calculation shared by the existing performance and accompaniment preflight.
    // The caller supplies the harmony at that note's onset; no memory or MIDI is modified.
    PlannedMotifNote planMotifNote(int i,const Pos& p,const Settings& s,int output,
        const composition::RememberedMotif* memory,bool varied,const composition::MotifOccurrence* occurrence=nullptr)const
    {
        PlannedMotifNote n;
        const long long span=memory?p.phraseEnd-p.phraseStart:std::min(2LL*meter.len,p.phraseEnd-p.phraseStart);
        const auto yc=layerY(s,kOutputLayer[output]);
        const Motif mo=motifFor(s,p.phrase);
        // Preserve the existing introduced material (tone count/rhythm), independently of restored expression.
        const float materialBase=(dens<.999f||yAdd>.001f)?std::clamp(curY*dens+yAdd,0.f,1.f):curY;
        const float materialY=std::clamp(materialBase+s.layerIntensity[kOutputLayer[output]],0.f,1.f);
        const auto* figure=occurrence&&occurrence->figure.count?&occurrence->figure:nullptr;
        const int count=figure?figure->count:memory?memory->count:materialY>=.55f?mo.n:materialY>=.3f?std::max(2,mo.n-1):std::max(2,mo.n-2);
        if(i>=count)return n;
        n.at=figure?figure->notes[static_cast<size_t>(i)].at:memory?memory->notes[static_cast<size_t>(i)].at:static_cast<long long>(mo.on[i])*meter.len/16;
        if(n.at<0||n.at>=span)return n;
        int ladder[16] {};const bool exact=memory&&occurrence&&!occurrence->introduction;
        const int nl=exact?1:counterLadder(chordFor(p,kOutputLayer[output],s),s,ladder,output);
        if(!nl)return n;
        if(memory)
        {
            const auto& recorded=figure?figure->notes[static_cast<size_t>(i)]:memory->notes[static_cast<size_t>(i)];
            const int base=composition::adaptMotifPitch(memory->origin-12*octaveOf(output),ladder,nl);
            n.pitch=occurrence&&!occurrence->introduction?occurrence->base+recorded.interval-12*octaveOf(output)
                :composition::adaptMotifPitch(base+recorded.interval,ladder,nl);
            n.velocity=recorded.velocity;
            n.length=std::min<int64_t>(figure?recorded.length:memory->recalledLength(i,varied,span),span-n.at);
            if(output==OutMelody)n.length=composition::articulatedLength(n.length,
                std::min<int64_t>(exact?span-n.at:p.chordEnd-(p.phraseStart+n.at),i+1<count?(figure?figure->notes[static_cast<size_t>(i+1)].at:memory->notes[static_cast<size_t>(i+1)].at)-n.at:span-n.at),s.melodyLegato);
        }
        else
        {
            auto end=i+1<count?static_cast<long long>(mo.on[i+1])*meter.len/16:span;
            end=std::min(end,p.phraseEnd-p.phraseStart);
            n.pitch=ladder[std::clamp(mo.deg[i],0,nl-1)];n.velocity=static_cast<int>(56+35*yc)+(i==0?6:0);
            n.length=std::min(span,end+(output==OutMelody?0:tail(end-n.at)))-n.at;
            if(output==OutMelody)n.length=composition::articulatedLength(n.length,
                std::min(n.length,p.chordEnd-(p.phraseStart+n.at)),s.melodyLegato);
        }
        if(exact)
        {
            const int actual=n.pitch+12*octaveOf(output),ri=kOutputRange[output];
            if(actual<0||actual>127||(s.rangeOn[ri]&&(actual<s.rangeLo[ri]||actual>s.rangeHi[ri])))return {};
        }
        n.valid=true;return n;
    }

    // A short phrase reservation exists only for the selected, active motif voice.
    // Preview current settings, not hypothetical future automation or a fabricated past performance.
    composition::MotifWindow primaryMotifWindow(const Pos& p,const Settings& s)
    {
        const int output=on[kMelodie]?OutMelody:OutCounter;
        if(!on[kOutputLayer[output]]||(s.genre==GenreScore&&!(output==OutMelody?s.melodyMotif:s.motif)))return {};
        if(s.genre==GenrePopRock&&(!phrasedHook(s)||!voice(output).motif.material(motifCatalog).complete))return {};
        const auto catalog=outputCatalog(s);composition::RoleNeed need;need.range=catalog[output].track.instrument.range;
        if(!composition::suitable(catalog[output].track,need))return {};
        const auto occurrence=motifOccurrence(p.k,p,s,output);if(!occurrence.active)return {};
        auto memory=performanceMaterial(output,s);
        if(memory.count&&p.phrase-phraseOf(sceneStep)!=voice(output).motif.introduction)memory.finish();
        const bool complete=memory.complete;const auto mo=motifFor(s,p.phrase);
        int count=0,future=0;int64_t begin=occurrence.end,end=occurrence.begin;
        for(int i=0;i<(occurrence.figure.count?occurrence.figure.count:complete?memory.count:mo.n);++i)
        {
            const auto at=occurrence.figure.count?occurrence.figure.notes[static_cast<size_t>(i)].at:complete?memory.notes[static_cast<size_t>(i)].at:static_cast<long long>(mo.on[i])*meter.len/16;
            auto local=locate(occurrence.begin+at);local.phraseStart=occurrence.begin;local.phraseEnd=occurrence.end;
            const auto note=planMotifNote(i,local,s,output,complete?&memory:nullptr,occurrence.varied,&occurrence);
            if(!note.valid)continue;
            const auto& c=catalog[output].track.instrument;if(note.length<c.minDuration||note.length>c.maxDuration)continue;
            ++count;if(occurrence.begin+note.at>=p.k)++future;
            begin=std::min<int64_t>(begin,occurrence.begin+note.at);end=std::max<int64_t>(end,occurrence.begin+note.at+note.length);
        }
        if(!future&&!outputSounding(output))return {};
        return composition::reserveMotifWindow(catalog[output].track.id,count,begin,end);
    }

    composition::MotifWindow motifWindow(const Pos& p,const Settings& s)
    {
        if((s.genre!=GenreScore&&!phrasedHook(s))||s.arpFigure!=ArpAuto)return {};
        // Shared physical notes can alter motif recording/retriggers. Preserve that routing verbatim.
        for(int o=0;o<kNumOutputs;++o)if(o!=OutArp&&s.channel[o]==s.channel[OutArp])return {};
        const auto primary=primaryMotifWindow(p,s);
        if(primary.contains(p.k))return primary;
        const auto response=playableMelodyHandoff(p.k,p,s);
        if(response.plan.active)
        {
            const auto& material=*motifCatalog.find(response.plan.reference.material);
            const auto& last=material.notes[static_cast<size_t>(material.count-1)];
            const auto end=response.plan.end-(!s.legato&&last.length>1?1:0);
            return composition::reserveMotifWindow(outputCatalog(s)[OutCounter].track.id,response.plan.count,
                response.origin+response.plan.begin,response.origin+end);
        }
        return {};
    }

    // Material recording/rendering is shared; complete returns follow the coordinated occurrence plan.
    bool motifStep (long long k, const Pos& p, const Settings& s, int offset, EventList& out, int output=OutCounter)
    {
        auto& state=voice(output);auto& use=state.motif;
        const long long span=std::min(2LL*meter.len,p.phraseEnd-p.phraseStart),rel=k-p.phraseStart;
        const long long section=p.phrase-phraseOf(sceneStep);
        if(rel>=span||(use.material(motifCatalog).count&&section!=use.introduction))use.finish(motifCatalog);
        const auto memory=performanceMaterial(output,s);const bool complete=memory.complete;
        if(complete)
        {
            const auto occurrence=motifOccurrence(k,p,s,output);
            if(!occurrence.active||k<occurrence.begin||k>=occurrence.end)return true;
        }
        else
        {
            if(rel<0||rel>=span)return false;
            if(memory.count&&use.introduction!=section)use.clear();
        }
        const auto occurrence=motifOccurrence(k,p,s,output);
        auto local=p;if(complete){local.phraseStart=occurrence.begin;local.phraseEnd=occurrence.end;}
        for(int i=0;i<(occurrence.figure.count?occurrence.figure.count:5);++i)
        {
            const auto note=planMotifNote(i,local,s,output,complete?&memory:nullptr,occurrence.varied,&occurrence);
            if(!note.valid||note.at!=k-local.phraseStart)continue;
            const int before=out.size;
            const bool savedForce=forceOn;if(s.genre==GenrePopRock)forceOn=true;
            noteOn(output,note.pitch,note.velocity,local.phraseStart+note.at+note.length,offset,out);forceOn=savedForce;
            if(!complete)for(int e=before;e<out.size;++e)
            {
                const auto& emitted=out.events[static_cast<size_t>(e)];
                if(emitted.out==output&&emitted.type==0&&emitted.velocity>0)
                    use.observe(emitted.note,note.at,note.length,section,note.velocity,p.phraseStart);
            }
            if(output==OutCounter)releaseOthers(output,note.pitch,offset,out);
            state.note=note.pitch;state.pendingAt=-1;
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
            const auto intent=composition::freeTransition(nextChordRoot(p),allowsPassingHarmony(*cur),cur->y);
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
        const int previous=current;
        if (! still) { current = s.custom ? kCustomWendung : pick (s, phrase); chordBase = 0; }
        rememberHarmonicEntry(phrase * phraseBars * meter.len,previous,s);
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
        const bool want = still ? s.y < s.policy.texture.stillExit : s.y < s.policy.texture.stillEnter;
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
        const int previous=current;
        current = pick (s, k * 7 + 3);
        rememberHarmonicEntry(k,previous,s);
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
            if (layer != kFlaeche && !(layer==kArp&&protectedColoration())) tonic.type = kShapes[w.ch[0].type].minor ? Min : Maj; // keep pad colour even when harmony following is disabled
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

    bool protectedColoration()const {return W().coloration==ChordColoration::protectedColor;}
    bool allowsPassingHarmony(const Settings& s)const {return s.passing&&!protectedColoration();}
    // Tonal decorations without a planned resolution must not change a protected accompaniment.
    bool authoredPitch(const Chord& c,int pitch,const Settings& s)const
    {for(int i=0;i<kShapes[c.type].n;++i)if(composition::pitchBit(pitch)==composition::pitchBit(s.key+c.root+kShapes[c.type].iv[i]))return true;return false;}
    // Unruhe faerbt einfache Dreiklaenge; explizite Sept-/Nonenqualitaeten bleiben erhalten.
    int padType (int type, float z) const
    {
        return coloredChordType(type,z,W().coloration);
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
    int rawBassPattern (const Settings& s, long long phrase) const
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
    bool melodicBassAllowed(const Settings& s)const
    {
        if(s.genre!=GenrePopRock||!on[kBass]||s.scene||s.sceneBars>0||manualEndStep>=0||!s.policy.bass.enabled||!s.follow[kBass]||s.bassPattern!=BassAuto||bassOverride>=0||s.passing||still||s.meterNum!=4||s.meterDen!=4)return false;
        for(int o=0;o<kNumOutputs;++o)if(o!=OutBassShort&&s.channel[o]==s.channel[OutBassShort])return false;
        return true;
    }
    int chooseBass(const Settings& s,long long phrase)const
    {return melodicBassAllowed(s)&&bassPhrase.valid&&nowStep>=bassPhrase.begin&&nowStep<bassPhrase.end?BassFunk:rawBassPattern(s,phrase);}
    void prepareBassPhrase(const Pos& p,const Settings& s)
    {
        if(!melodicBassAllowed(s)){bassPhrase.valid=false;bassPairStart=-1;return;}
        const auto& w=W();const int first=(p.chordIdx/2)*2;
        if(first+1>=w.n||wendungStart>p.phraseStart){bassPhrase.valid=false;bassPairStart=-1;return;}
        long long begin=p.phraseStart;for(int i=0;i<first;++i)begin+=static_cast<long long>(w.ch[i].bars)*meter.len;
        auto signature=static_cast<uint64_t>(current+2)*1000003u+static_cast<unsigned>(s.key+12*s.octave[kBass]+32)
            +static_cast<uint64_t>(s.rangeOn[kBass]?s.rangeLo[kBass]+256*s.rangeHi[kBass]+1:0)*65537u;
        for(int value:{s.policy.bass.opportunityEvery,s.policy.bass.maxLeap,static_cast<int>(s.policy.passing.mode),s.policy.passing.tonicOffset}){signature^=static_cast<uint32_t>(value);signature*=1099511628211ull;}
        for(int i=0;i<w.n;++i)for(int value:{w.ch[i].root,w.ch[i].type,w.ch[i].bass,w.ch[i].bars}){signature^=static_cast<uint32_t>(value);signature*=1099511628211ull;}
        if(bassPairStart==begin&&bassPhraseKey==signature)return;
        bassPairStart=begin;bassPhraseKey=signature;bassPhrase={};
        if(rawBassPattern(s,p.phrase)!=BassFunk||(p.phrase+first/2)%s.policy.bass.opportunityEvery!=(s.policy.bass.opportunityEvery>1?1:0))return;
        prepareVoicingPlan(p,s);composition::BassPhraseRequest r;r.begin=begin;r.middle=begin+static_cast<long long>(w.ch[first].bars)*meter.len;
        r.end=r.middle+static_cast<long long>(w.ch[first+1].bars)*meter.len;r.modal=modalContextFor(s);r.maxLeap=s.policy.bass.maxLeap;
        for(int j=0;j<2;++j){const auto c=w.ch[first+j];r.bass[j]=harmonicPlan.slots[(first+j)*2].bass+12*s.octave[kBass];r.root[j]=(s.key+c.root)%12;for(int n=0;n<kShapes[c.type].n;++n)r.chords[j]|=composition::pitchBit(s.key+c.root+kShapes[c.type].iv[n]);}
        r.range=s.rangeOn[kBass]?composition::Range{s.rangeLo[kBass],s.rangeHi[kBass]}:composition::Range{std::max(0,std::min(r.bass[0],r.bass[1])-7),std::min(127,std::max(r.bass[0],r.bass[1])+12)};
        const auto c=outputCatalog(s)[OutBassShort].track.instrument;r.minDuration=static_cast<int>(c.minDuration);r.maxDuration=static_cast<int>(c.maxDuration);
        bassPhrase=composition::planBassPhrase(r);
    }
    int pattern0 (const Settings& s, long long phrase) const { return chooseBass (s, phrase); }

    composition::RhythmPlan movementRhythm(const Pos& p,const Settings& s)const
    {
        // Explicitly protect manual patterns, thematic contexts, scene density and shared routing.
        if(s.genre!=GenrePopRock||!s.policy.rhythm.enabled||s.bassPattern!=BassAuto||s.arpFigure!=ArpAuto
            ||s.arpRate!=RateAuto||!on[kBass]||!on[kArp]||s.scene||s.sceneBars>0||manualEndStep>=0||s.endRequested
            ||still||bassRest||bassOverride>=0||dens<1.f||s.meterNum!=4||s.meterDen!=4||s.passing
            ||on[kMelodie]||(on[kGegenstimme]&&phrasedHook(s)))return {};
        for(int o=0;o<kNumOutputs;++o)
            if((o!=OutArp&&s.channel[o]==s.channel[OutArp])
                ||(o!=OutBassShort&&s.channel[o]==s.channel[OutBassShort]))return {};
        const int fig=chooseArp(s,p.phrase);
        if(fig!=ArpUp&&fig!=ArpDown&&fig!=ArpCircle&&fig!=ArpCascade)return {};
        if(composition::autoArpeggioTicks(s.policy.texture,layerY(s,kArp))!=2)return {};
        const int pattern=chooseBass(s,p.phrase);
        composition::RhythmPlanRequest request;request.bar=p.bar;request.movement=0x5555;
        for(int pos=0;pos<16;++pos)
        {
            bool attack=false;
            if(pattern==BassEighth)attack=pos%2==0;
            else if(pattern==BassHiNrg)attack=pos%(layerY(s,kBass)>.75f?1:2)==0;
            else if(pattern==BassFunk)attack=composition::funkBassAttack(pos,false).active;
            else return {};
            if(attack)request.reference|=static_cast<uint16_t>(1u<<pos);
        }
        const auto cap=outputCatalog(s)[OutArp].track.instrument;
        request.minDuration=static_cast<int>(cap.minDuration);request.maxDuration=static_cast<int>(cap.maxDuration);
        return composition::planRhythmicInterlock(request,s.policy.rhythm);
    }

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
            if (claim.endTime <= musicaltime::fromGridStep(step) && ! (deferPadBoundary && claim.endTime == musicaltime::fromGridStep(step) && claim.out == OutPadLong))
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
            if (keepPad && active[(size_t) i].out == OutPadLong) active[(size_t) i].endTime = std::min (active[(size_t) i].endTime, musicaltime::fromGridStep(nowStep));
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
        if(protectedColoration())return note; // Unavailable pitch classes are omitted, never substituted.
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
        if(protectedColoration()&&cur!=nullptr&&!(o==OutStich&&cur->stichFixed))
        {
            const int physical=fitRange(o,note+12*octaveOf(o));
            if(physical<0||physical>127||(rangeOn(o)&&(physical<cur->rangeLo[kOutputRange[o]]||physical>cur->rangeHi[kOutputRange[o]])))return;
        }
        note = (o == OutStich && cur != nullptr && cur->stichFixed) ? std::clamp (note, 0, 127) : sounding (o, note);
        if (! forceOn) velocity = (int) std::lround ((float) velocity * (cur != nullptr && cur->dynamics && cur->ccExpression > 0 ? 1.0f : (0.6f + 0.4f * gain[layer]))) + boost[layer];
        velocity = std::clamp (velocity, 1, 127);
        int own = -1; bool existing = false, sameStep = false;
        for (int i = 0; i < numActive; ++i)
        {
            const auto& a = active[(size_t) i];
            if (a.channel != channel || a.note != note) continue;
            existing = true; sameStep = sameStep || a.startTime == musicaltime::fromGridStep(nowStep);
            if (a.out == o) own = i;
        }
        if (own < 0 && numActive >= kMaxActive) return;
        if (! existing || (! sameStep && ! extendOnly))
        {
            if (existing) out.add (offset, channel, note, 0, o);
            out.add (offset, channel, note, velocity, o);
            // One physical attack for all claims at this time.
            for (int i = 0; i < numActive; ++i)
                if (active[(size_t) i].channel == channel && active[(size_t) i].note == note) active[(size_t) i].startTime = musicaltime::fromGridStep(nowStep);
        }
        if (own >= 0)
        {
            auto& a = active[(size_t) own];
            a.endTime = (sameStep || extendOnly) ? std::max (a.endTime, musicaltime::fromGridStep(endStep)) : musicaltime::fromGridStep(endStep);
            a.startTime = musicaltime::fromGridStep(nowStep);
        }
        else active[(size_t) numActive++] = { (uint8_t) channel, (uint8_t) note, (uint8_t) o, musicaltime::fromGridStep(endStep), musicaltime::fromGridStep(nowStep) };
        if(o==OutBassLong||o==OutBassShort)heardHarmony.bass=note;
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
    void resetVoicing() { dispositionValid=false; planValid = false; entryVoicingValid=false; unavailablePad = 0; }

    struct HeardHarmony
    {
        voiceleading::ChordVoicing pad;
        int bass=-1,root=0,type=Min;
    } heardHarmony;
    // Small scene-local ledger for revisiting the last 64 performed boundaries.
    struct HarmonicEntryRecord { long long begin=-1;int target=-1;HeardHarmony heard; };
    std::array<HarmonicEntryRecord,64> harmonicEntries {};
    unsigned harmonicEntryNext=0;
    bool harmonicChase=false;
    void clearHarmonicEntries()
    {heardHarmony={};harmonicEntries={};harmonicEntryNext=0;}
    void rememberHarmonicEntry(long long begin,int previous,const Settings& s)
    {
        if(harmonicChase||s.genre!=GenreScore||s.custom||previous<0||previous==current)return;
        for(const auto& entry:harmonicEntries)if(entry.begin==begin&&entry.target==current)return;
        harmonicEntries[harmonicEntryNext++%harmonicEntries.size()]={begin,current,heardHarmony};
        planValid=false;
    }
    const HarmonicEntryRecord* harmonicEntryAt(const Pos& p,const Settings& s)const
    {
        if(s.genre!=GenreScore||s.custom)return nullptr;
        const auto begin=std::max(p.phraseStart,wendungStart);
        for(const auto& entry:harmonicEntries)if(entry.begin==begin&&entry.target==current)return &entry;
        return nullptr;
    }
    // The ordinary cyclic plan is unchanged. Only the entry chord can use performed context.
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
        const auto* entry=harmonicEntryAt(p,s);
        if(entry){mix(static_cast<int>(entry->begin));mix(static_cast<int>(entry->begin>>32));
            mix(entry->heard.pad.n);for(int i=0;i<entry->heard.pad.n;++i)mix(entry->heard.pad.notes[i]);
            mix(entry->heard.bass);mix(entry->heard.root);mix(entry->heard.type);}

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
                intent.quartal=pad.type==Quartal;intent.preservePitchClasses=protectedColoration();
                intent.protectedLine=s.genre==GenrePopRock&&W().id==WendungId::popDrahtseil;
                intent.voicing=current==kCustomWendung?hashInt(91u,start)%3:0;
                intent.padLow=padLow(s);intent.bassLow=bassLow(s);intent.intensity=layerY(s,kFlaeche);
                slot=composition::buildAnchor(intent,{lo,hi},rangeOn(o));
                mix(slot.pad.n);for(int n=0;n<slot.pad.n;++n)mix(slot.pad.notes[n]);
                mix(slot.bass);mix(static_cast<int>(slot.unavailable));
                slot.enabled = ! pass || (composition::freeTransition(0,allowsPassingHarmony(s),s.y,still).kind==composition::TransitionKind::passingDominant);
                slot.preservePad = s.genre == GenrePopRock && W().id == WendungId::popDrahtseil && ! s.custom;
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
        entryVoicingValid=false;
        if(entry&&harmonicPlan.valid)
        {
            composition::HarmonicEntry previous;
            previous.pad=entry->heard.pad;
            for(int i=0;i<previous.pad.n;++i)previous.pad.notes[i]-=oct;
            previous.hasBass=entry->heard.bass>=0;
            previous.bass=entry->heard.bass-12*s.octave[kBass];
            const int index=chordBase*2;
            const auto chord=chords[index];
            previous.resolution=composition::dominantResolution(entry->heard.root,
                entry->heard.type==Dom7||entry->heard.type==Dom7b9,s.key+chord.root,0);
            const composition::HarmonicPlan::Slot* following=nullptr;
            for(int next=index+1;next<request.count;++next)if(request.slots[static_cast<size_t>(next)].enabled)
                {following=&harmonicPlan.slots[static_cast<size_t>(next)];break;}
            entryVoicing=composition::leadEntry(
                harmonicPlan.slots[static_cast<size_t>(index)],previous,{lo,hi},{blo,bhi},following);
            entryVoicingValid=true;
        }
        planValid = harmonicPlan.valid; planKey = key;
    }

    voiceleading::ChordVoicing padVoicing (const Pos& p, const Settings& s, int output)
    {
        prepareVoicingPlan (p, s);
        dispositionAt=nowStep;
        const int index = p.chordIdx * 2 + (p.passing ? 1 : 0);
        unavailablePad = harmonicPlan.slots[static_cast<size_t> (index)].unavailable;
        const auto original=entryVoicingValid&&index==chordBase*2?entryVoicing.pad:harmonicPlan.slots[static_cast<size_t> (index)].pad;
        lastDisposition={};lastDisposition.notes=original;
        if(s.genre!=GenrePopRock||!s.policy.chords.enabled||s.padPattern!=PadAuto||!on[kFlaeche]||s.scene||s.sceneBars>0
            ||manualEndStep>=0||s.endRequested||s.passing||still||padShy||peak||padGrow||W().id==WendungId::popDrahtseil)return original;
        for(int o=0;o<kNumOutputs;++o)if(o!=output&&s.channel[o]==s.channel[output])return original;
        const auto cap=outputCatalog(s)[output].track.instrument;
        const int oct=12*s.octave[kFlaeche];
        const int lo=s.rangeOn[0]?s.rangeLo[0]-oct:std::max(-oct,padLow(s)-18);
        const int hi=s.rangeOn[0]?s.rangeHi[0]-oct:std::min(127-oct,padLow(s)+24);
        const auto mode=s.policy.chords.cycle[static_cast<size_t>((p.phrase+s.variation-1)%s.policy.chords.cycle.size())];
        uint64_t signature=planKey;auto mix=[&](int n){signature^=static_cast<uint32_t>(n);signature*=1099511628211ull;};
        mix(static_cast<int>(mode.population));mix(static_cast<int>(mode.spacing));mix(s.policy.chords.minimumOpenSpan);mix(s.policy.chords.maximumOpenSpan);mix(cap.polyphony);
        // Root support is admitted only for an unchanged, sustained bass tone.
        const int bp=chooseBass(s,p.phrase);const bool stableBass=on[kBass]&&(bp==BassHeld||bp==BassPedal)&&!bassRest;
        mix(stableBass);mix(s.follow[kBass]);mix(bp);mix(s.key);
        if(!dispositionValid||dispositionKey!=signature)
        {
            auto previous=harmonicPlan.slots[static_cast<size_t>((W().n-1)*2)].pad;
            for(int cycle=0;cycle<2;++cycle)for(int i=0;i<W().n;++i)
            {
                composition::ChordDispositionRequest request;request.original=harmonicPlan.slots[static_cast<size_t>(i*2)].pad;
                request.previous=previous;request.low=lo;request.high=hi;request.polyphony=cap.polyphony;request.disposition=mode;
                auto chord=W().ch[i];if(!s.follow[kFlaeche]){chord=W().ch[0];chord.root=s.custom?chord.root:0;}
                const auto& shape=kShapes[padType(chord.type,s.z)];request.root=(s.key+chord.root)%12;
                for(int n=0;n<shape.n;++n){const int iv=shape.iv[n]%12;const auto bit=static_cast<uint16_t>(1u<<((request.root+iv)%12));request.chordMask|=bit;
                    if(iv!=0&&iv!=7)request.required|=bit;}
                if(chord.type==Quartal||chord.type==Fifth)request.required=request.chordMask;
                if(stableBass)request.bass=bp==BassPedal?place(s.key+pedalRoot(),bassLow(s))
                    :harmonicPlan.slots[static_cast<size_t>(i*2)].bass;
                if(request.bass>=0)
                {
                    const int physical=request.bass+12*s.octave[kBass];
                    if(physical<0||physical>127||(s.rangeOn[1]&&(physical<s.rangeLo[1]||physical>s.rangeHi[1])))request.bass=-1;
                }
                const int previousIndex=(i+W().n-1)%W().n;
                auto prior=W().ch[previousIndex];if(!s.follow[kFlaeche]){prior=W().ch[0];prior.root=s.custom?prior.root:0;}
                const auto resolution=composition::dominantResolution(prior.root,prior.type==Dom7||prior.type==Dom7b9,chord.root,s.key);
                request.descendingSeventh=resolution.descendingSeventh;request.ascendingThird=resolution.ascendingThird;
                dispositionSlots[static_cast<size_t>(i)]=composition::realizeChord(request,s.policy.chords);
                previous=dispositionSlots[static_cast<size_t>(i)].notes;
            }
            dispositionKey=signature;dispositionValid=true;
        }
        lastDisposition=dispositionSlots[static_cast<size_t>(p.chordIdx)];return lastDisposition.notes;
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
        if(on[kFlaeche])
        {
            voiceleading::ChordVoicing played;
            for(int i=0;i<numActive&&played.n<6;++i)if(active[static_cast<size_t>(i)].out==o)
                played.notes[played.n++]=active[static_cast<size_t>(i)].note;
            if(played.n){voiceleading::sort(played);heardHarmony.pad=played;
                heardHarmony.root=(s.key+chord.root)%12;heardHarmony.type=chord.type;}
        }
    }

    int bassPlacement (const Pos& p, const Settings& s, int anchor, bool pedal)
    {
        if (pedal) return anchor;
        prepareVoicingPlan (p, s);
        const int index=p.chordIdx*2+(p.passing?1:0);
        return entryVoicingValid&&index==chordBase*2?entryVoicing.bass:harmonicPlan.slots[static_cast<size_t>(index)].bass;
    }

    int nextBassPlacement (const Pos& p, const Settings& s)
    {
        prepareVoicingPlan (p, s);
        const int index = !p.passing && composition::freeTransition(0,allowsPassingHarmony(s),s.y,still).kind==composition::TransitionKind::passingDominant
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
        if (ya < s.policy.texture.start(composition::TexturePart::accents) && ! akzentForced) return false;
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
        if (s.x >= 0.35f && s.z < 0.6f && (!protectedColoration()||authoredPitch(c,s.key+c.root+14,s))) pick[n++] = 14;   // None, im Hellen
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
        if(protectedColoration())return; // No resolution is planned for this foreign-tone accent.
        noteOn (OutTupfer, note, (int) (30 + 45 * s.z), p.k + 3, offset, out);
        if (s.z >= 0.8f && layerY (s, kAkzent) < 0.5f)                    // Halbton-Reibung ganz oben
            noteOn (OutTupfer, note + 11, (int) (25 + 30 * s.z), p.k + 3, offset, out);
    }

    // Stich: ein einzelner Schlag. Fest: die gewaehlte Taste. Akkord: der Grundton (MIDI 50 bis 61, unter der Gegenstimme).
    static int stichTone (const Settings& s, int pitch) { return composition::addressedPitch(outputCatalog(s)[OutStich], place(pitch,stichLow(s))); }
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
        if (protectedColoration() || s.z < kRissStart || ! muteSoloOk (s, kFlaeche)) return;
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

        if (s.z >= s.policy.texture.accentUnrest && k == p.chordStart + (p.chordEnd - p.chordStart) / 2)
            foreignTone (p, s, offset, out);
        else if (both || tupferAt (k, s))
            tupfer (p, s, offset, ya > 0.7f ? 1 : 2, both ? 10 : 0, out);

        if (ya < s.policy.texture.stichStart) return;
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
        prepareBassPhrase(p,s);
        if (ppq > (double) p.chordStart * kStep + 1e-9)
            sustained (p, s, 0, out, true);
        else
            chaseStep = k;   // genau am Akkordanfang: der normale Schritt schlaegt an, auch die stehenden Ebenen
        if(on[kBass]&&bassPhrase.valid)
            for(int i=0;i<bassPhrase.count;++i){const auto& note=bassPhrase.notes[i];if(note.at*kStep<ppq&&ppq<(note.at+note.length)*kStep)
                {const int position=static_cast<int>(note.at%meter.len);const int velocity=static_cast<int>(58+38*layerY(s,kBass))+(meter.isGroupStart(position)?8:0)+jitter(note.at,kBass,3)+note.accent;
                 noteOn(OutBassShort,note.pitch-12*s.octave[kBass],velocity,note.at+note.length,0,out);}}
        const auto rhythm=movementRhythm(p,s);
        if(rhythm.active)for(int i=0;i<rhythm.count;++i)
        {
            const auto& n=rhythm.notes[i];const auto begin=k-p.pos+n.at;
            if((begin+swingDelay(begin,s))*kStep<ppq&&ppq<(begin+n.length+swingDelay(begin+n.length,s))*kStep)
                playArpeggio(begin,0,locate(begin),p.phrase,s,out);
        }
        const bool inclusive=ppq>static_cast<double>(k)*kStep+1e-9;
        freePhraseStep(k,p,s,0,out,true,inclusive);
        chaseMotif(k,p,s,out,inclusive);
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
        // Density is a separate optional-event mask. EndOpen's explicit energy rise is retained.
        if (yAdd > 0.001f)
        {
            Settings sb = s;
            sb.y = std::clamp (s.y + yAdd, 0.0f, 1.0f);
            const Settings* saved = cur;
            cur = &sb;
            render (k, offset, p, restart, phrase, sb, out);
            cur = saved;
        }
        else render (k, offset, p, restart, phrase, s, out);
    }

    void chaseMotif(long long k,const Pos& p,const Settings& s,EventList& out,bool inclusive)
    {
        if(s.genre!=GenreScore&&!phrasedHook(s))return;
        const int output=on[kMelodie]?OutMelody:OutCounter;
        const auto memory=performanceMaterial(output,s);
        if(on[kOutputLayer[output]]&&(s.genre==GenrePopRock||(output==OutMelody?s.melodyMotif:s.motif))&&memory.complete)
        {
            const auto occurrence=motifOccurrence(k,p,s,output);
            if(occurrence.active&&k>=occurrence.begin&&k<occurrence.end)
            {
                auto local=p;local.phraseStart=occurrence.begin;local.phraseEnd=occurrence.end;
                for(int i=0;i<(occurrence.figure.count?occurrence.figure.count:memory.count);++i)
                {
                    const auto n=planMotifNote(i,local,s,output,&memory,occurrence.varied,&occurrence);
                    const auto begin=occurrence.begin+n.at,end=begin+n.length;
                    if(n.valid&&(begin<k||(inclusive&&begin==k))&&k<end)
                    {const bool saved=forceOn;if(s.genre==GenrePopRock)forceOn=true;noteOn(output,n.pitch,n.velocity,end,0,out);forceOn=saved;voice(output).note=n.pitch;}
                }
            }
        }
        if(on[kMelodie])melodyHandoff(k,p,s,0,out,true,inclusive);
        else if(on[kArp])dialogueArp(k,p,s,0,out,true,inclusive);
    }

    PlayableHandoff playableMelodyHandoff(long long k,const Pos& p,const Settings& s)
    {
        const auto catalog=outputCatalog(s);
        const auto& source=voice(OutMelody).motif;
        const auto window=static_cast<int64_t>(s.policy.motif.windowBars)*meter.len;
        const auto epoch=k>=source.originTick?(k-source.originTick)/window:-1;
        const auto origin=source.originTick+epoch*window;
        const auto leading=motifOccurrence(k,p,s,OutMelody);
        const auto plan=composition::planMelodyHandoff(
            s.genre==GenreScore&&s.melody&&s.melodyMotif&&s.motif&&!s.scene
                &&s.meterNum==4&&s.meterDen==4&&on[kMelodie]&&on[kGegenstimme]&&phraseBars>=4,
            source,motifCatalog,catalog[OutCounter].track,epoch,meter.len,window,s.policy.motif,
            layerY(s,kMelodie),s.z,leading.active);
        if(!plan.active||origin+plan.end>motifAvailableUntil(s,kGegenstimme))return {};
        const auto relative=k-origin;
        if(relative<plan.begin||relative>=plan.end||outputSounding(OutMelody))return {};
        // Preflight the whole response: exact suffix intervals, one harmonic region, no fallback pitches.
        const auto start=origin+plan.begin;
        const auto region=motifHarmonyAt(start,s);
        if(start+plan.end-plan.begin>region.end)return {};
        const auto& material=*motifCatalog.find(plan.reference.material);
        const auto& capability=catalog[OutCounter].track.instrument;
        const auto chord=region.chord;const auto& shape=kShapes[chord.type];
        int base=-1;int best=10000;
        for(int candidate=0;candidate<128;++candidate)
        {
            bool valid=true;
            for(int i=0;i<plan.count;++i)
            {
                const int pitch=candidate+material.notes[static_cast<size_t>(plan.first+i)].interval;
                bool harmonic=false;for(int j=0;j<shape.n;++j)harmonic|=(pitch%12+12)%12==(s.key+chord.root+shape.iv[j])%12;
                valid&=harmonic&&pitch>=capability.range.low&&pitch<=capability.range.high&&pitch>=0&&pitch<=127;
            }
            const int distance=std::abs(candidate-std::clamp(material.origin,62,77));
            if(valid&&distance<best){best=distance;base=candidate;}
        }
        if(base<0)return {};
        for(auto tick=start;tick<start+plan.end-plan.begin;++tick)
        {
            const auto soundingChord=motifHarmonyAt(tick,s).chord;
            if(soundingChord.root!=chord.root||soundingChord.type!=chord.type)return {};
        }
        return {plan,base,origin};
    }

    bool melodyHandoff(long long k,const Pos& p,const Settings& s,int offset,EventList& out,bool chase=false,bool inclusive=false)
    {
        const auto playable=playableMelodyHandoff(k,p,s);
        const auto& plan=playable.plan;if(!plan.active)return false;
        const int base=playable.base,oct=12*octaveOf(OutCounter);
        const auto relative=k-playable.origin;
        const auto capability=outputCatalog(s)[OutCounter].track.instrument;
        auto& answer=voice(OutCounter).answer;
        if(answer.reference.value!=plan.reference.material.value||answer.introduction!=plan.reference.introduction)
            if(!answer.adopt(plan.reference,motifCatalog))return false;
        const auto& source=answer.material(motifCatalog);
        const auto origin=source.notes[static_cast<size_t>(plan.first)].at;
        for(int i=0;i<plan.count;++i)
        {
            const auto& note=source.notes[static_cast<size_t>(plan.first+i)];
            const auto at=plan.begin+note.at-origin;
            auto length=std::min<int64_t>(note.length,plan.end-at);
            if(i+1<plan.count)length=std::min(length,source.notes[static_cast<size_t>(plan.first+i+1)].at-note.at);
            length=composition::articulatedLength(length,length,s.legato);
            if(length<capability.minDuration||length>capability.maxDuration)return false;
            if(chase?!((at<relative||(inclusive&&at==relative))&&relative<at+length):relative!=at)continue;
            // Renderer accepts prevalidated sounding pitches, compensating the adapter octave.
            cut(kGegenstimme,k,k,offset,out);
            noteOn(OutCounter,base+note.interval-oct,note.velocity,playable.origin+at+length,offset,out);
        }
        return true;
    }

    bool dialogueArp(long long k,const Pos& p,const Settings& s,int offset,EventList& out,bool chase=false,bool inclusive=false)
    {
        // Explicit cell + motif, no buildup, four-bar-or-longer 4/4 phrases only.
        if(on[kMelodie]||s.genre!=GenreScore||!s.motif||s.arpFigure!=ArpCell||s.scene||s.meterNum!=4||s.meterDen!=4
            ||phraseBars<4||!on[kArp]||!on[kGegenstimme])return false;
        const auto catalog=outputCatalog(s);
        if(!composition::validOutputs(catalog.data(),kNumOutputs))return true;
        const composition::PlayingTrack tracks[2]={catalog[OutCounter].track,catalog[OutArp].track};
        composition::RoleNeed question;question.polyphony=2;question.range=tracks[0].instrument.range;
        composition::RoleNeed answer;answer.role=composition::MusicalRole::answer;
        answer.style=composition::PlayingStyle::detached;answer.range=tracks[1].instrument.range;
        const auto assignment=composition::assignDialogue(tracks,2,question,answer);
        if(!assignment.valid)return true; // Reserved context, no incompatible fallback.
        int responseOutput=-1;
        for(const auto& entry:catalog)if(entry.track.id.value==assignment.response.value)responseOutput=entry.target.output;
        if(responseOutput<0)return true;
        const long long window=2LL*meter.len;
        auto& use=voice(OutCounter).motif;
        auto occurrence=motifOccurrence(k,p,s,OutCounter);
        if(k>=occurrence.begin+window)use.finish(motifCatalog);
        occurrence=motifOccurrence(k,p,s,OutCounter);
        const auto& motifMemory=use.material(motifCatalog);
        if(!motifMemory.complete&&k>=occurrence.begin+window)return false;
        const auto plan=composition::planDialogue(use,motifCatalog,occurrence,k,window);
        if(!plan.reserveResponse)return false;
        if(!plan.answer)return true;
        const auto chord=chordFor(p,kArp,s);const auto& shape=kShapes[chord.type];
        const int oct=12*octaveOf(responseOutput);
        const int lo=rangeOn(responseOutput)?s.rangeLo[kArp]-oct:60;
        const int hi=rangeOn(responseOutput)?s.rangeHi[kArp]-oct:84;
        int ladder[128],count=0;
        for(int pitch=lo;pitch<=hi;++pitch)for(int j=0;j<shape.n;++j)
            if((pitch%12+12)%12==(s.key+chord.root+shape.iv[j])%12){ladder[count++]=pitch;break;}
        if(!count)return true; // No harmonic answer possible within the user's range.
        const int base=composition::adaptMotifPitch(motifMemory.origin-oct,ladder,count);
        const int notes=plan.answerNotes;
        for(int i=0;i<notes;++i)
        {
            const auto& n=motifMemory.notes[static_cast<size_t>(i)];
            auto length=std::min<int64_t>(n.length,window-n.at);
            if(i+1<notes)length=std::min(length,motifMemory.notes[static_cast<size_t>(i+1)].at-n.at);
            if(length<=0)continue;
            const auto begin=plan.answerBegin+n.at;
            if(chase?!((begin<k||(inclusive&&begin==k))&&k<begin+length):k!=begin)continue;
            const int pitch=composition::adaptMotifPitch(base+n.interval,ladder,count);
            noteOn(responseOutput,pitch,n.velocity,begin+length,offset,out);
        }
        return true;
    }

    void playArpeggio(long long k,int offset,const Pos& p,long long phrase,const Settings& s,EventList& out)
    {
        const bool group=meter.isGroupStart(p.pos);const float z=s.z,yArp=layerY(s,kArp);
        const int fig = chooseArp (s, phrase);
        int rate = s.arpRate == RateQuarter ? 4 : s.arpRate == RateEighth ? 2 : s.arpRate == RateSixteenth ? 1
                 : composition::autoArpeggioTicks(s.policy.texture,yArp);
        if (fig == ArpGlitter || fig == ArpSid) rate = 1;
        const long long rel = k - (s.follow[kArp] ? p.chordStart : p.phraseStart);
        const auto rhythm=movementRhythm(p,s);
        const auto* onset=rhythm.active?rhythm.at(p.pos):nullptr;
        const auto sourceStep=onset?k+onset->source-p.pos:k;
        const auto sourceRel=rel+(sourceStep-k);
        if (rhythm.active?onset!=nullptr:rel%rate==0)
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
            const long long c0 = sourceRel / rate + (long long) (hashInt (77u, s.follow[kArp] ? p.chordStart : phrase) % 4);
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
            if(protectedColoration()&&!authoredPitch(c,note,s))note=tones[c0%count];
            const int vel = (int) ((fig == ArpGlitter ? 40 : 52) + 35 * yArp) + (group ? 6 : 0) + jitter (sourceStep, kArp, 6);
            const long long len = onset?onset->length:(fig == ArpGlitter || fig == ArpSid || rate == 1) ? 1 : rate;
            noteOn (OutArp, note, vel, k + len, offset, out);
        }
    }

    bool densityAllows(const Pos& p)const
    {
        int group=0;for(int i=1;i<meter.numGroups;++i)if(p.pos>=meter.groupStart[i])group=i;
        return composition::EventDensity{dens}.allows(group,meter.numGroups);
    }

    void render (long long k, int offset, const Pos& p, bool restart, long long phrase, const Settings& s, EventList& out)
    {
        prepareBassPhrase(p,s);
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
        const float yPad = layerY (s, kFlaeche), yBass = layerY (s, kBass);

        if (chordStart)
            sustained (p, s, offset, out, restart, bassRest ? 1u : 3u);
        else if (padGrow || peak || enterNow[kFlaeche] || enterNow[kBass])   // Ebene setzt mitten im Akkord ein
        {
            unsigned mask = (enterNow[kFlaeche] || peak ? 1u : 0u) | (enterNow[kBass] || peak ? 2u : 0u);
            if (padGrow && ! peak) { extendOnly = true; sustained (p, s, offset, out, true, 1u); extendOnly = false; }
            if (mask != 0) sustained (p, s, offset, out, true, mask);
        }

        // Akzente: Tupfer und Stich, bei Unruhe der fremde Ton in der Mitte des Akkords; ganz oben in der Unruhe der Riss
        const bool optional=densityAllows(p);
        // Structural cues and complete thematic/answer figures bypass the density mask.
        if(optional||prepStich||akzentForced)accents(k,p,s,offset,out);
        if(optional)riss(k,p,s,offset,out);

        // --- Flaeche: Schlaege, Puls oder Staccato
        const int pad = choosePad (s);
        if (optional && pad == PadStabs && p.pos % 4 == 2)
            padChord (p, s, OutPadShort, offset, k + 1, (int) (55 + 40 * yPad) + jitter (k, kFlaeche, 4), out);
        else if (optional && pad == PadPulse && beat)
            padChord (p, s, OutPadShort, offset, k + 3, (int) (50 + 40 * yPad) + (group ? 8 : 0), out);
        else if (optional && pad == PadStaccato && beat)
            padChord (p, s, OutPadShort, offset, k + 1, (int) (48 + 40 * yPad) + (group ? 6 : 0), out);
        else if (optional && pad == PadGated && p.pos % 2 == 0)                 // gehackte Achtel wie ein Gate
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
            switch (bassRest || (!optional && !chordStart) ? -1 : pattern)   // Vorbereiten: in der zweiten Takthaelfte schweigt der Bass
            {
                case kPulseTick:   if (beat) noteOn (bo, root, vel - (group ? 0 : 8), k + 1, offset, out); break;   // Ticken in Vierteln
                case BassHalf:     if (p.pos % 8 == 0 || approach) noteOn (bo, root, vel, k + (approach ? 2 : 7), offset, out); break;
                case BassQuarter:  if (beat || approach) noteOn (bo, root, vel, k + (approach ? 2 : 3), offset, out); break;
                case BassEighth:   if (p.pos % 2 == 0) noteOn (bo, root, vel, k + 2, offset, out); break;
                case BassPulse:    noteOn (bo, root, vel - (group ? 0 : 10), k + 1, offset, out); break;
                case BassFunk:
                {
                    auto hit=composition::funkBassAttack(p.pos,approach);
                    if(hit.active)
                    {
                        int pitch=root+hit.interval,length=hit.duration;
                        if(melodicBassAllowed(s)&&bassPhrase.valid)for(int i=0;i<bassPhrase.count;++i)if(bassPhrase.notes[i].at==k)
                            {pitch=bassPhrase.notes[i].pitch-12*s.octave[kBass];length=bassPhrase.notes[i].length;break;}
                        noteOn(bo,pitch,vel+hit.accent,k+length,offset,out);
                    }
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

        // --- Arp / Figur: motif/answer reservations retain priority over accompaniment.
        if (on[kArp] && !dialogueArp(k,p,s,offset,out) && !motifWindow(p,s).contains(k) && (optional||chordStart))
            playArpeggio(k,offset,p,phrase,s,out);

        // --- Gegenstimme: ruhige Linie aus Akkordtoenen, schrittweise gefuehrt
        if(on[kMelodie])
        {
            const auto catalog=outputCatalog(s);
            const auto foreground=composition::planForeground(s.melody,catalog[OutMelody].track);
            if(foreground.foreground)
            {
                if(!melodyHandoff(k,p,s,offset,out))cut(kGegenstimme,k,k,offset,out);
                int leadOutput=-1;
                for(const auto& entry:catalog)if(entry.track.id.value==foreground.lead.value)leadOutput=entry.target.output;
                if(leadOutput>=0)counterLine(k,p,s,offset,chordStart||enterNow[kMelodie],out,leadOutput);
            }
            else counterLine(k,p,s,offset,chordStart||enterNow[kGegenstimme],out);
        }
        else counterLine (k, p, s, offset, chordStart || enterNow[kGegenstimme], out);
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
    int counterTarget (const Chord& c, const Settings& s, bool chordStart, long long k, int output=OutCounter) const
    {
        const ChordShape& sh = kShapes[c.type];
        const int lo = 62 + (int) std::lround (s.x * 3.0f);
        const int rootPc = (s.key + c.root) % 12;
        const int ri = kOutputRange[output];
        int a = lo, b = lo + 13;
        if (s.rangeOn[ri])
        {
            // Tonumfang: nur Toene im spielbaren Bereich (Oktav-Einstellung eingerechnet); liegt die uebliche Lage
            // ausserhalb, sucht die Linie im ganzen Bereich
            const int rlo = s.rangeLo[ri] - 12 * s.octave[kOutputLayer[output]], rhi = s.rangeHi[ri] - 12 * s.octave[kOutputLayer[output]];
            a = std::max (lo, rlo); b = std::min (lo + 13, rhi);
            int found = 0;
            for (int n = a; n <= b; ++n)
                for (int i = 0; i < sh.n; ++i) found += (rootPc + sh.iv[i]) % 12 == n % 12 ? 1 : 0;
            if (found < 2) { a = rlo; b = rhi; }
        }
        const int prev = voice(output).note >= 0 ? voice(output).note : (a + b) / 2;
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

    void capturePerformance(double ppq,double end,double samplesPerQuarter,const Settings& s,const EventList& out)
    {
        if(s.genre!=GenrePopRock)return;
        auto& state=voice(OutCounter);
        if(!state.capture.active){captureRead=out.size;return;}
        bool ambiguous=state.captureChannel!=s.channel[OutCounter];
        for(int o=0;o<kNumOutputs;++o)if(o!=OutCounter&&s.channel[o]==s.channel[OutCounter])ambiguous=true;
        if(ambiguous){state.capture.clear();state.motif.clear();return;}
        for(int i=captureRead;i<out.size;++i)
        {
            const auto& e=out.events[static_cast<size_t>(i)];
            if(e.type==0&&e.channel==s.channel[OutCounter])
                state.capture.event(state.motif,e.note,e.velocity,musicaltime::fromQuarters(ppq+e.offset/samplesPerQuarter).value);
        }
        captureRead=out.size;
        state.capture.finish(state.motif,motifCatalog,musicaltime::fromQuarters(end).value);
    }
    void armHookCapture(long long k,const Pos& p,const Settings& s)
    {
        auto& state=voice(OutCounter);
        if(state.motif.material(motifCatalog).complete||state.capture.active)return;
        // Shared physical notes do not identify an independent melodic performance.
        for(int o=0;o<kNumOutputs;++o)if(o!=OutCounter&&s.channel[o]==s.channel[OutCounter])return;
        const bool special=popHookPattern(W().id)>=0&&!s.custom;
        const auto cycle=special?2LL*meter.len:8LL*(layerY(s,kGegenstimme)<.45f?4:2);
        if((k-p.phraseStart)%cycle==0){state.captureSwing=s.swing;state.captureChannel=s.channel[OutCounter];state.capture.start(state.motif,musicaltime::fromGridStep(k).value,musicaltime::fromGridStep(cycle).value,musicaltime::ticksPerGridStep);}
    }
    // Pop-Rock: durchgehende, gleichbleibende Hook-Linie aus Akkordtoenen (eine Figur je VARIATION)
    void leadHook (long long k, const Pos& p, const Settings& s, int offset, EventList& out)
    {
        armHookCapture(k,p,s);
        const int hook=popHookPattern(W().id);
        if (hook>=0 && ! s.custom)
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
            const int id = hook;
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
                releaseOthers (OutCounter, note, offset, out); voice(OutCounter).note = note;
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
                a.endTime = std::min (a.endTime, musicaltime::fromGridStep(nowStep + (cur != nullptr && cur->legato ? 1 : 0)));
        }
        if (cur == nullptr || ! cur->legato) releaseDue (nowStep, offset, out);
    }

    // Ende eines Tons der Gegenstimme relativ zum naechsten: Legato eine Sechzehntel darueber, sonst kurz davor abgesetzt
    long long tail (long long len) const { return cur != nullptr && cur->legato ? 1 : (len >= 4 ? -1 : 0); }

    composition::LinePhrasePlan freeLinePhrase(const Pos& p,const Settings& s)const
    {
        if(s.genre!=GenreScore||s.motif||on[kMelodie]||!on[kGegenstimme])return {};
        composition::LinePhraseRequest request;
        request.begin=std::max({p.chordStart,p.phraseStart,sceneStep,wendungStart});
        request.end=std::min({p.chordEnd,p.phraseEnd,sceneEndStep});
        if(s.ending==EndFade&&(s.sceneBars>0||manualEndStep>=0))
        {
            int slots=0;const int index=orderIndex(s,entryInUse,kGegenstimme,slots);
            const int tailBars=manualEndStep>=0?2:std::clamp(std::min(s.buildBars,s.sceneBars/2),1,64);
            if(index>0)request.end=std::min<int64_t>(request.end,sceneEndStep-slotBar(index,slots,tailBars)*meter.len);
        }
        if(s.scene&&entryInUse!=EntryAll)
        {
            int slots=0;const int index=orderIndex(s,entryInUse,kGegenstimme,slots);
            if(index>=0)request.begin=std::max<int64_t>(request.begin,sceneStep+slotBar(index,slots,s.buildBars)*meter.len);
        }
        request.pulse=meter.numGroups>1?meter.groupStart[1]:std::min(4,meter.len);
        const auto catalog=outputCatalog(s);composition::RoleNeed need;
        need.range=catalog[OutCounter].track.instrument.range;
        if(!composition::suitable(catalog[OutCounter].track,need))return {};
        const auto chord=chordFor(p,kGegenstimme,s);const auto& shape=kShapes[chord.type];
        int ladder[16];const int count=counterLadder(chord,s,ladder);
        const int low=62+static_cast<int>(std::lround(s.x*3.f));
        for(int i=0;i<count;++i)if(ladder[i]>=low&&ladder[i]<=low+13)
            request.pitches[static_cast<size_t>(request.count++)]=ladder[i];
        if(request.count<3){request.count=count;for(int i=0;i<count;++i)request.pitches[static_cast<size_t>(i)]=ladder[i];}
        const int oct=12*octaveOf(OutCounter);
        request.range={std::max(-oct,catalog[OutCounter].track.instrument.range.low-oct),
            std::min(127-oct,catalog[OutCounter].track.instrument.range.high-oct)};
        request.ending=request.end==p.phraseEnd&&chord.root==0
            ?composition::PhraseEnding::settled:composition::PhraseEnding::open;
        int interval=request.ending==composition::PhraseEnding::settled?(s.x>.6f?shape.iv[1]:0)
            :s.z>=.5f&&shape.n>3?shape.iv[3]:shape.iv[std::min(s.x>.6f?2:1,shape.n-1)];
        request.goalPitchClass=(s.key+chord.root+interval)%12;
        request.descending=s.x<.5f;request.notes=layerY(s,kGegenstimme)>=.7f?4:3;
        request.legato=s.legato;request.initialNeighbour=s.z>=.75f?1:s.z>=.5f?2:0;
        return composition::planLinePhrase(request);
    }

    bool freePhraseStep(long long k,const Pos& p,const Settings& s,int offset,EventList& out,
        bool chase=false,bool inclusive=false)
    {
        const auto plan=freeLinePhrase(p,s);if(!plan.valid)return false;
        voice(OutCounter).pendingAt=-1;
        if(k>=plan.breath){cut(kGegenstimme,k,k,offset,out);return true;}
        for(int i=0;i<plan.count;++i)
        {
            const auto& n=plan.notes[static_cast<size_t>(i)];
            if(chase? !((n.begin<k||(inclusive&&n.begin==k))&&k<n.end):n.begin!=k)continue;
            noteOn(OutCounter,n.pitch,static_cast<int>(50+35*layerY(s,kGegenstimme))+(i==0&&s.z>=.5f?6:0),n.end,offset,out);
            if(!chase)releaseOthers(OutCounter,n.pitch,offset,out);
            voice(OutCounter).note=n.pitch;
        }
        return true;
    }

    void counterLine (long long k, const Pos& p, const Settings& s, int offset, bool chordStart, EventList& out, int output=OutCounter)
    {
        if (! on[kOutputLayer[output]]) { voice(output).note = -1; voice(output).pendingAt = -1; return; }
        if (output==OutCounter && s.genre == GenrePopRock)
        {
            if(phrasedHook(s)&&voice(output).motif.material(motifCatalog).complete){motifStep(k,p,s,offset,out,output);return;}
            leadHook(k,p,s,offset,out);return;
        }
        if ((output==OutMelody?s.melodyMotif:s.motif) && motifStep (k, p, s, offset, out,output)) return;
        if(output==OutCounter&&freePhraseStep(k,p,s,offset,out))return;
        const float yc = layerY (s, kOutputLayer[output]);
        const int vel = (int) (50 + 35 * yc);
        if (output==OutCounter && k == voice(output).pendingAt && voice(output).pending >= 0)                    // Vorhalt loest sich auf
        {
            noteOn (OutCounter, voice(output).pending, vel, voice(output).pendingEnd + tail (voice(output).pendingEnd - k), offset, out);
            releaseOthers (OutCounter, voice(output).pending, offset, out);
            voice(output).note = voice(output).pending; voice(output).pendingAt = -1;
        }
        // Bewegung: ruhig nur bei Akkordwechseln, mittel alle zwei Takte, aufgewuehlt in Halben
        const long long rate = yc < 0.4f ? 0 : yc < 0.7f ? 2LL * meter.len : std::max (4LL, (long long) meter.len / 2);
        const bool move = chordStart || (rate > 0 && k > p.chordStart && (k - p.chordStart) % rate == 0 && p.chordEnd - k >= 4);
        if (! move) return;
        const Chord c = chordFor (p, kOutputLayer[output], s);
        const long long end = rate > 0 ? std::min (p.chordEnd, k + rate) : p.chordEnd;
        const int target = counterTarget (c, s, chordStart, k,output);
        if (output==OutCounter && s.z >= 0.5f && chordStart && end - k >= 8)               // Unruhe: Vorhalt von oben, loest auf den Zielton auf
        {
            const int sus = target + (s.z >= 0.75f ? 1 : 2);
            noteOn (OutCounter, sus, vel + 6, k + 4 + (s.legato ? 1 : 0), offset, out);
            releaseOthers (OutCounter, sus, offset, out);
            voice(output).pending = target; voice(output).pendingAt = k + 4; voice(output).pendingEnd = end;
            voice(output).note = sus;
            return;
        }
        if(output==OutMelody)
        {
            int ladder[16];if(counterLadder(c,s,ladder,output)==0)return;
            const auto duration=composition::articulatedLength(end-k,end-k,s.melodyLegato);
            noteOn(output,target,vel,k+duration,offset,out);voice(output).note=target;voice(output).pendingAt=-1;return;
        }
        noteOn (OutCounter, target, vel, end + tail (end - k), offset, out);   // Legato: eine Sechzehntel laenger, bindet zum naechsten Ton
        releaseOthers (OutCounter, target, offset, out);
        voice(output).note = target;
    }

    struct VoiceState
    {
        composition::MotifUse motif,answer;
        composition::MotifCapture capture; int captureChannel=0;float captureSwing=0;
        int64_t recurrenceEpoch=-1,recurrenceOrigin=0,recurrenceWindow=0;uint64_t recurrenceIdentity=0;
        composition::MotifOccurrence recurrencePlan;
        int note=-1,pending=-1;
        long long pendingAt=-1,pendingEnd=0;
    };
    std::array<VoiceState,2> voices {};
    int captureRead=0;
    composition::MotifCatalog motifCatalog;
    VoiceState& voice(int output){return voices[output==OutMelody?1u:0u];}
    const VoiceState& voice(int output)const{return voices[output==OutMelody?1u:0u];}
    composition::BassPhrasePlan bassPhrase;long long bassPairStart=-1;uint64_t bassPhraseKey=0;
    std::array<composition::ChordDispositionResult,8> dispositionSlots {};
    composition::ChordDispositionResult lastDisposition;
    uint64_t dispositionKey=0;bool dispositionValid=false;long long dispositionAt=-1;
    composition::HarmonicPlan harmonicPlan;
    composition::HarmonicPlan::Slot entryVoicing; bool entryVoicingValid=false;
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
        static constexpr float outGain[kNumOutputs] = { 0.04f, 0.04f, 0.07f, 0.07f, 0.04f, 0.035f, 0.03f, 0.06f, 0.05f };
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
