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
#include <cstring>
#include <optional>
#include <cassert>
#include <numeric>
#include "CompositionCore.h"
#include "BarryVocabulary.h"
#include "MusicalExecution.h"
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

// Genre strategy seam, also frozen only in historical offline feature probes.
inline bool popMelodicRoles(const Settings& s){return s.genre==GenrePopRock;}
inline bool melodyAvailable(const Settings& s){return s.melody&&(s.genre==GenreScore||popMelodicRoles(s));}
inline bool hasSolo(const Settings& s)
{
    for(int layer=0;layer<kNumLayers;++layer)
        if(s.solo[layer]&&(layer!=kMelodie||melodyAvailable(s)))return true;
    return false;
}

// The only standard capability definitions for the current generator outputs.
// These describe emitted MIDI, never verified external patch capabilities.
inline std::array<composition::OutputDescription,kNumOutputs> outputCatalog(const Settings& s)
{
    using namespace composition;
    struct Standard { PlayingStyle style; int voices; musicaltime::Tick maxDuration; unsigned roles; };
    const auto accompaniment=roleBit(MusicalRole::accompaniment);
    const Standard standards[kNumOutputs]={
        {PlayingStyle::sustained,6,musicaltime::sixteenth*(1<<24),accompaniment},
        {PlayingStyle::detached,9,musicaltime::sixteenth*(3),accompaniment},
        {PlayingStyle::sustained,1,musicaltime::sixteenth*(1<<24),accompaniment},
        {PlayingStyle::detached,1,musicaltime::sixteenth*(4),accompaniment},
        {PlayingStyle::detached,1,musicaltime::sixteenth*(32),accompaniment|roleBit(MusicalRole::answer)},
        {PlayingStyle::detached,4,musicaltime::sixteenth*(3),accompaniment},
        {PlayingStyle::detached,1,musicaltime::sixteenth*(2),accompaniment},
        {PlayingStyle::sustained,2,musicaltime::sixteenth*(1<<24),roleBit(MusicalRole::lead)|roleBit(MusicalRole::answer)},
        {PlayingStyle::sustained,1,musicaltime::sixteenth*(1<<24),roleBit(MusicalRole::lead)} };
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
        track.available=(layer!=kMelodie||melodyAvailable(s))
            &&(layer==kMelodie&&popMelodicRoles(s)?(anySolo?s.solo[layer]:!s.mute[layer]):!s.mute[layer]&&(!anySolo||s.solo[layer]));
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
    void reset() { previousSettings.reset();preparedTime.reset();dispatchIdentity=0;nowTime={};currentPerformanceQuarter=0;currentTiming=execution::Timing::nominal;bassPhrase={};bassPairStart.reset();harmonicChase=false; clearHarmonicEntries(); motifCatalog.clear(); voices={};authoredRhythmCache={}; style = -1; restartAt.reset(); lastGenre = -1; resetCc(); resetVoicing(); numActive = 0; running = false; lastPpqEnd = 0.0; phraseIndex = -1; current = -1; wendungTime = musicaltime::fromGridStep(0); still = false; chordBase = 0; drivePrev = driveSeen = driveLatched = driveArrivedNow = false; driveTrajectory = false; driveProgressNow = 0; driveGenerationSeen = 0; curRoot = 0; curType = Min; curChord = -1;
                   sceneTime=musicaltime::fromGridStep(0); manualEndTime.reset(); manualFinished = manualHitSent = false; endWasRequested = false; sceneSeed = 0; autoSeed = -1; sceneBarNow = -1; sceneEnded = false; for (int l = 0; l < kNumLayers; ++l) { on[l] = prevOn[l] = hOn[l] = false; } }

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
    {auto snapshot=*this;snapshot.cur=&settings;const auto p=snapshot.locate(tick);return snapshot.dialogueMayLead(p,settings)?snapshot.freeLinePhrase(p,settings):composition::LinePhrasePlan{};}
    composition::MotifOccurrence inspectMotifOccurrence(long long tick,Settings settings,int output=OutCounter)const
    {
        auto snapshot=*this;snapshot.cur=&settings;
        if((settings.genre!=GenreScore&&!snapshot.phrasedHook(settings)&&!(popMelodicRoles(settings)&&output==OutMelody))||!on[kOutputLayer[output]]||(settings.genre==GenreScore&&!(output==OutMelody?settings.melodyMotif:settings.motif))
            ||(output==OutCounter&&!snapshot.dialogueMayLead(snapshot.locate(tick),settings)))return {};
        return snapshot.motifOccurrence(musicaltime::fromGridStep(tick),snapshot.locate(tick),settings,output);
    }
    composition::BassPhrasePlan inspectBassPhrase()const{return bassPhrase;}
    composition::RhythmPlan inspectMovementRhythm(long long tick,const Settings& s)const
    {auto snapshot=*this;snapshot.cur=&s;return snapshot.movementRhythm(snapshot.locate(tick),s);}
    composition::ChordDispositionResult inspectChordDisposition()const{return lastDisposition;}
    std::optional<musicaltime::Tick> inspectChordDispositionTime()const{return dispositionAt;}
    struct TimingSnapshot
    {
        musicaltime::Tick scene,section,phraseBegin,phraseEnd,chordBegin,chordEnd;
        std::optional<musicaltime::Tick> sceneEnd,manualEnd;
    };
    TimingSnapshot inspectTiming(long long gridStep,const Settings& settings)const
    {
        auto copy=*this;copy.cur=&settings;const auto p=copy.locate(gridStep);
        return {sceneTime,wendungTime,p.phraseStartTime,p.phraseEndTime,p.chordStartTime,p.chordEndTime,sceneEndTime,manualEndTime};
    }
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
        if(layer==kMelodie&&(!melodyAvailable(s)))return false;
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
        if(!pop&&s.policy.accompaniment.fieldAndOstinato)
        {
            if(s.x<.5f&&s.y>=.5f&&ok(kArp))return EntryArp;
            if(ok(kFlaeche))return EntryPad;
        }
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
    int accompanimentRhythmId() const { return authoredRhythmCache.source?authoredRhythmCache.source->id:0; }
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
        const Wendung* tbl = wendungTable (s.genre,s.profile); const int count = wendungCount (s.genre,s.profile);
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
        for (int i = 0; i < wendungCount (s.genre,s.profile); ++i) best = std::max (best, weight (wendungTable (s.genre,s.profile)[i], s));
        return best;
    }

    // Deterministische Wahl unter den Wendungen, die gut zur Lage passen (mindestens halb so gut wie die beste)
    static int pick (const Settings& s, long long salt)
    {
        const Wendung* tbl = wendungTable (s.genre,s.profile); const int count = wendungCount (s.genre,s.profile);
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
        if(!composition::valid(s.policy.accompaniment)||!composition::valid(s.policy.popRoles)||!composition::valid(s.policy.texture)||!composition::valid(s.policy.motif)||!composition::valid(s.policy.popHooks.recurrence)||!composition::valid(s.policy.passing)||!composition::valid(s.policy.bass)||!composition::valid(s.policy.rhythm)||!composition::valid(s.policy.chords))s.policy=composition::neutralFreePolicy;
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
        if (s.custom != wasCustom || bars != phraseBars || s.genre != lastGenre || s.profile != lastProfile)   // Umschalten, neue Laenge oder anderes Genre: neue Phrase
        {
            if(s.genre!=lastGenre||s.profile!=lastProfile){authoredRhythmCache={};if(s.profile!=lastProfile){allNotesOff(out,0);current=-1;voices={};authoredRhythmCache={};bassPhrase={};bassPairStart.reset();clearHarmonicEntries();resetVoicing();}motifCatalog.clear();for(auto& state:voices){state.motif.clear();state.answer.clear();state.capture.clear();state.recurrence={};state.reservationRecurrence={};state.popTurnValid=false;}}
            preparedTime.reset();
            phraseIndex = -1; wasCustom = s.custom; phraseBars = bars; style = -1;
            genre = s.genre; lastGenre = s.genre;lastProfile=s.profile;
            if (running) releaseHeld (0, out);
        }

        if (! t.playing || ! std::isfinite (t.bpm) || ! std::isfinite (t.sampleRate) || ! std::isfinite (t.ppq) || std::abs (t.ppq) > 1.0e9 || t.bpm <= 0.0 || t.sampleRate <= 0.0 || numSamples <= 0)
        {
            if (running) allNotesOff (out, 0);
            for(auto& state:voices){state.capture.clear();if(!state.motif.material(motifCatalog).complete)state.motif.clear();}
            running = false; curChord = -1; cur = nullptr; sceneBarNow = -1;
            return;
        }
        const bool configurationChanged=!previousSettings||!sameSettings(*previousSettings,s);
        previousSettings=s;
        releaseSilencedLayers (s, out);

        const double samplesPerQuarter = t.sampleRate * 60.0 / t.bpm;
        const double ppqEnd = t.ppq + (double) numSamples / samplesPerQuarter;
        const double transportTolerance=std::max(1./samplesPerQuarter,
            8*std::numeric_limits<double>::epsilon()*std::max(1.,std::abs(t.ppq)));
        const bool jumped = running && std::fabs (t.ppq - lastPpqEnd) > transportTolerance;
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
            const auto destination=execution::floorTime(t.ppq);
            const auto barDuration=musicaltime::sixteenth*meter.len;
            if (! running) { manualEndTime.reset(); manualFinished = manualHitSent = false; endWasRequested = false; }
            if (! running || destination<sceneTime) { bassPhrase={};bassPairStart.reset();clearHarmonicEntries(); motifCatalog.clear(); voices={};authoredRhythmCache={}; sceneTime=barDuration*floorDiv(destination.value,barDuration.value); driveLatched = false; drivePrev = false; driveSeen = false; }
            running = true;
            phraseIndex = -1;
            for(auto& state:voices){state.note=-1;state.pendingAt.reset();} resetCc();
            preparedTime.reset();currentPerformanceQuarter=t.ppq;++dispatchIdentity;
            nowTime=execution::floorTime(t.ppq);currentTiming=execution::Timing::nominal;
            applyDrive (execution::floorTime(t.ppq), s, ax, ay);
            chase (t.ppq, s, out);
            harmonicChase=false;
        }

        // The local Settings starts from the host parameters each block. Onset queries
        // must see the last evaluated trajectory point, not the raw point A, until
        // the next controller event evaluates the curve. No second clock/state copy.
        if(s.drive){s.x=curX;s.y=curY;}

        // Independent nominal controls, concrete musical onsets and note deadlines.
        // A stock pattern may use sixteenths; neither a plan nor the dispatcher must.
        auto nominalCursor=std::max(musicaltime::Tick{},execution::floorTime(t.ppq));
        while(musicaltime::toQuarters(nominalCursor)<t.ppq-1e-12)nominalCursor+=musicaltime::Tick{1};
        auto rhythmCursor=std::max(musicaltime::Tick{},execution::nominalAt(t.ppq,execution::Timing::groove,s.swing));
        while(execution::quarters(rhythmCursor,execution::Timing::groove,s.swing)<t.ppq-1e-12)rhythmCursor+=musicaltime::Tick{1};
        if(!hasWendung())ensurePhrase(phraseOf(nominalCursor),s);
        if(!hasWendung()){allNotesOff(out,0);curChord=-1;cur=nullptr;return;}
        bool inputEvent=configurationChanged;
        for(;;)
        {
            auto nominal=std::min(nextBoundary(nominalCursor,s),nextOnset(nominalCursor,s));
            if(s.drive)nominal=std::min(nominal,execution::atOrAfter(nominalCursor,musicaltime::sixteenth));
            if(inputEvent)nominal=std::min(nominal,execution::floorTime(t.ppq));
            auto pulse=nextOnset(rhythmCursor,s);
            const auto event=execution::first({nominal,execution::Timing::nominal,execution::Kind::planning,true},
                {pulse,execution::Timing::groove,execution::Kind::rhythm,true},s.swing);
            const auto release=nextRelease();
            const double when=std::max(t.ppq,std::min(execution::when(event,s.swing),execution::when(release,s.swing)));
            if(when>=ppqEnd-1e-12)break;
            const bool planning=execution::coincides(std::max(t.ppq,musicaltime::toQuarters(nominal)),when);
            bool rhythm=execution::coincides(execution::quarters(pulse,execution::Timing::groove,s.swing),when);
            const int offset=std::clamp(static_cast<int>(std::llround((when-t.ppq)*samplesPerQuarter)),0,numSamples-1);
            beginDispatch(when);
            capturePerformance(t.ppq,when,samplesPerQuarter,s,out);
            releaseAt(when,offset,out,planning);
            capturePerformance(t.ppq,when,samplesPerQuarter,s,out);
            if(planning)
            {
                currentTiming=execution::Timing::nominal;nowTime=nominal;
                applyDrive(nominal,s,ax,ay);
                prepareAt(nominal,offset,s,out);preparedTime=nominal;
                nominalCursor=nominal+musicaltime::Tick{1};inputEvent=false;
                // A newly enabled voice or a completed capture can register a coincident
                // onset. Re-query before releasing shared pad claims.
                auto earliest=execution::nominalAt(when,execution::Timing::groove,s.swing);
                while(execution::quarters(earliest,execution::Timing::groove,s.swing)<when-1e-12)earliest+=musicaltime::Tick{1};
                rhythmCursor=std::max(rhythmCursor,earliest);
                pulse=nextOnset(rhythmCursor,s);
                rhythm=execution::coincides(execution::quarters(pulse,execution::Timing::groove,s.swing),when);
            }
            if(!rhythm)releaseAt(when,offset,out);
            capturePerformance(t.ppq,when,samplesPerQuarter,s,out);
            if(rhythm)
            {
                currentTiming=execution::Timing::groove;nowTime=pulse;
                applyDrive(pulse,s,ax,ay);
                // Envelope/context evaluation is lazy at a concrete onset; structural
                // boundaries have their own nominal events and are never shifted here.
                if(!preparedTime||*preparedTime<pulse)
                {const auto saved=currentTiming;currentTiming=execution::Timing::nominal;prepareAt(pulse,offset,s,out);currentTiming=saved;preparedTime=pulse;}
                if(!sceneEnded)renderRhythmAt(pulse,offset,s,out);
                rhythmCursor=pulse+musicaltime::Tick{1};
            }
            releaseAt(when,offset,out);
            capturePerformance(t.ppq,when,samplesPerQuarter,s,out);
            // State changes may register future sources, never retroactive ones.
            auto nominalFloor=execution::floorTime(when);
            while(musicaltime::toQuarters(nominalFloor)<=when+1e-12)nominalFloor+=musicaltime::Tick{1};
            nominalCursor=std::max(nominalCursor,nominalFloor);
            auto grooveFloor=execution::nominalAt(when,execution::Timing::groove,s.swing);
            while(execution::quarters(grooveFloor,execution::Timing::groove,s.swing)<=when+1e-12)grooveFloor+=musicaltime::Tick{1};
            rhythmCursor=std::max(rhythmCursor,grooveFloor);
        }
        capturePerformance(t.ppq,ppqEnd,samplesPerQuarter,s,out);
        lastPpqEnd = ppqEnd;
        cur = nullptr;
    }

private:
    static bool sameSettings(const Settings& a,const Settings& b)
    {
        if(a.profile!=b.profile
            ||a.melodyLegato!=b.melodyLegato
            ||a.melodyMotif!=b.melodyMotif
            ||a.melody!=b.melody
            ||a.key!=b.key
            ||a.x!=b.x
            ||a.y!=b.y
            ||a.z!=b.z
            ||a.meterNum!=b.meterNum
            ||a.meterDen!=b.meterDen
            ||a.swing!=b.swing
            ||a.variation!=b.variation
            ||a.change!=b.change
            ||a.variety!=b.variety
            ||a.genre!=b.genre
            ||a.dynamics!=b.dynamics
            ||a.ccDynamics!=b.ccDynamics
            ||a.ccExpression!=b.ccExpression
            ||a.ccRange!=b.ccRange
            ||a.passing!=b.passing
            ||a.legato!=b.legato
            ||a.padPattern!=b.padPattern
            ||a.bassPattern!=b.bassPattern
            ||a.arpFigure!=b.arpFigure
            ||a.arpRate!=b.arpRate
            ||a.custom!=b.custom
            ||a.endRequested!=b.endRequested
            ||a.scene!=b.scene
            ||a.entry!=b.entry
            ||a.seed!=b.seed
            ||a.buildBars!=b.buildBars
            ||a.hardness!=b.hardness
            ||a.sceneBars!=b.sceneBars
            ||a.ending!=b.ending
            ||a.motif!=b.motif
            ||a.inertia!=b.inertia
            ||a.driveGeneration!=b.driveGeneration
            ||a.drive!=b.drive
            ||a.driveX!=b.driveX
            ||a.driveY!=b.driveY
            ||a.driveFrom!=b.driveFrom
            ||a.driveBars!=b.driveBars
            ||a.driveCurve!=b.driveCurve
            ||a.stichFixed!=b.stichFixed
            ||a.stichNote!=b.stichNote)return false;
        for(int i=0;i<kNumLayers;++i)if(a.mute[i]!=b.mute[i]||a.solo[i]!=b.solo[i]||a.layerIntensity[i]!=b.layerIntensity[i]||a.octave[i]!=b.octave[i])return false;
        for(int i=0;i<kNumRanges;++i)if(a.rangeOn[i]!=b.rangeOn[i]||a.rangeLo[i]!=b.rangeLo[i]||a.rangeHi[i]!=b.rangeHi[i])return false;
        for(int i=0;i<kNumOutputs;++i)if(a.channel[i]!=b.channel[i])return false;
        for(int i=0;i<3;++i)if(a.follow[i]!=b.follow[i])return false;
        for(int i=0;i<2;++i)for(int j=0;j<16;++j)if(a.ccLo[i][j]!=b.ccLo[i][j]||a.ccHi[i][j]!=b.ccHi[i][j])return false;
        for(int i=0;i<kMaxChords;++i)if(a.customChords[i].rootAbs!=b.customChords[i].rootAbs||a.customChords[i].type!=b.customChords[i].type||a.customChords[i].bars!=b.customChords[i].bars)return false;
        if(a.route.count!=b.route.count)return false;
        for(size_t i=0;i<a.route.points.size();++i)if(a.route.points[i].x!=b.route.points[i].x||a.route.points[i].y!=b.route.points[i].y)return false;
        for(size_t i=0;i<a.route.bends.size();++i)if(a.route.bends[i].x!=b.route.bends[i].x||a.route.bends[i].y!=b.route.bends[i].y)return false;
        const auto& x=a.policy;const auto& y=b.policy;
        if(x.accompaniment.authoredCells!=y.accompaniment.authoredCells||x.accompaniment.fieldAndOstinato!=y.accompaniment.fieldAndOstinato||x.accompaniment.fastestArp!=y.accompaniment.fastestArp
            ||x.popRoles.sparseBelow!=y.popRoles.sparseBelow||x.popRoles.drivenFrom!=y.popRoles.drivenFrom||x.popRoles.unrestFrom!=y.popRoles.unrestFrom
            ||x.texture.activityStart!=y.texture.activityStart
            ||x.texture.accentUnrest!=y.texture.accentUnrest
            ||x.texture.stichStart!=y.texture.stichStart
            ||x.texture.activityHysteresis!=y.texture.activityHysteresis
            ||x.texture.minimumActiveBars!=y.texture.minimumActiveBars
            ||x.texture.stillEnter!=y.texture.stillEnter
            ||x.texture.stillExit!=y.texture.stillExit
            ||x.texture.arpeggio.quarterBelow!=y.texture.arpeggio.quarterBelow
            ||x.texture.arpeggio.eighthBelow!=y.texture.arpeggio.eighthBelow
            ||x.popHooks.enabled!=y.popHooks.enabled
            ||x.popHooks.phrasedCustom!=y.popHooks.phrasedCustom
            ||x.popHooks.phrased!=y.popHooks.phrased
            ||x.passing.enabled!=y.passing.enabled
            ||x.passing.opportunityStride!=y.passing.opportunityStride
            ||x.passing.minGap!=y.passing.minGap
            ||x.passing.maxDuration!=y.passing.maxDuration
            ||x.passing.mode!=y.passing.mode
            ||x.passing.tonicOffset!=y.passing.tonicOffset
            ||x.bass.enabled!=y.bass.enabled
            ||x.bass.opportunityEvery!=y.bass.opportunityEvery
            ||x.bass.maxLeap!=y.bass.maxLeap
            ||x.rhythm.enabled!=y.rhythm.enabled
            ||x.rhythm.everyBars!=y.rhythm.everyBars
            ||x.chords.enabled!=y.chords.enabled
            ||x.chords.minimumOpenSpan!=y.chords.minimumOpenSpan
            ||x.chords.maximumOpenSpan!=y.chords.maximumOpenSpan)return false;
        auto recurrence=[](const composition::MotifRecurrencePolicy& x,const composition::MotifRecurrencePolicy& y)
        {return x.minimumSilentBars==y.minimumSilentBars&&x.adaptChordTones==y.adaptChordTones&&x.establishOriginal==y.establishOriginal&&x.preserveContour==y.preserveContour&&x.sparseBelow==y.sparseBelow&&x.unrestEngages==y.unrestEngages&&x.variations==y.variations&&x.sequenceSemitones==y.sequenceSemitones&&x.sparseSteps==y.sparseSteps&&x.normalSteps==y.normalSteps;};
        if(!recurrence(x.motif,y.motif)||!recurrence(x.popHooks.recurrence,y.popHooks.recurrence))return false;
        for(size_t i=0;i<x.chords.cycle.size();++i)if(x.chords.cycle[i].population!=y.chords.cycle[i].population||x.chords.cycle[i].spacing!=y.chords.cycle[i].spacing)return false;
        return true;
    }

    static constexpr float kKeepRatio = 0.5f;   // so gut muss die laufende Wendung mindestens passen, sonst wird gewechselt

    struct Active { uint8_t channel, note, out; musicaltime::Tick endTime;execution::Timing timing=execution::Timing::nominal;uint64_t attack=0; };

    // Wo im Takt / in der Phrase / in der Wendung ein Schritt liegt
    struct Pos
    {
        musicaltime::Tick time{};
        long long k, bar, phrase; int pos, barInPhrase; // Dimensionless pattern/metric ordinals.
        int chordIdx; musicaltime::Tick chordStartTime{},chordEndTime{},phraseStartTime{},phraseEndTime{};
        bool passing = false;   // Durchgangsakkord am Ende des Akkords
    };


    static long long floorDiv (long long a, long long b) { return a >= 0 ? a / b : -((-a + b - 1) / b); }

    composition::ProfileId lastProfile=composition::ProfileId::neutral;
    bool hasWendung() const
    {return current==kCustomWendung||(current>=0&&current<wendungCount(genre,lastProfile));}
    const Wendung& W() const
    {
        // Rendering requires an initialized selection; never clamp an invalid index to template 0.
        assert(hasWendung());
        return current==kCustomWendung?custom:wendungTable(genre,lastProfile)[current];
    }

    // ---------------------------------------------------------------- Dramaturgie
    static constexpr int kPulseTick = 100;   // Bass-Muster nur fuer den Puls-Einstieg: kurze Viertel auf dem Orgelpunkt

    long long barsSince (musicaltime::Tick time) const { return floorDiv((time-sceneTime).value,musicaltime::fromGridStep(meter.len).value); }

    // Fahrt: der klingende Punkt wandert von A (Punkt im Feld) nach B
    void applyDrive (musicaltime::Tick time, Settings& s, float ax, float ay)
    {
        driveAY = ay;
        // This trajectory intentionally retains its established sample-and-hold rate.
        // It is a local controller property, never the timebase of note planning.
        const auto evaluated=s.drive?musicaltime::sixteenth*floorDiv(time.value,musicaltime::sixteenth.value):time;
        const double barsNow=static_cast<double>((evaluated-sceneTime).value)/static_cast<double>(musicaltime::fromGridStep(meter.len).value);
        if (s.drive && ! drivePrev && driveSeen)   // waehrend der Wiedergabe eingeschaltet: ab dem naechsten Takt, vom Punkt aus
        {
            driveLatched = true;
            driveFromLatched = (int) std::ceil (static_cast<double>((time-sceneTime).value)/static_cast<double>((musicaltime::sixteenth*meter.len).value) - 1e-9);
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
            if(popMelodicRoles(s)&&l==kMelodie)continue; // keep accompaniment build/end slots unchanged
            if (! muteSoloOk (s, l)) continue;
            if (l == layer) idx = m;
            ++m;
        }
        if(popMelodicRoles(s)&&layer==kMelodie)idx=std::max(0,m-1);
        return idx;
    }
    // Takt, an dem Platz i von m einsetzt (verteilt auf span Takte; der letzte im letzten Takt des Aufbaus)
    static long long slotBar (int i, int m, int span)
    {
        return (m <= 1 || span <= 1 || i <= 0) ? 0 : (long long) std::lround ((double) i * (double) (span - 1) / (double) (m - 1));
    }

    // Was klingt jetzt: Traegheit, Aufbau, Ausduennen, Ende. Setzt on[], gain[], boost[] und die Sonderfaelle des Einstiegs.
    void updateScene (musicaltime::Tick time, const Pos& p, const Settings& s, bool fresh, int offset, EventList& out)
    {
        const auto barDuration=musicaltime::fromGridStep(meter.len);
        const long long bs = barsSince (time);
        const bool barStart = time % musicaltime::fromGridStep(meter.len) == musicaltime::Tick{};
        sceneBarNow = (int) std::clamp (bs, 0LL, 1LL << 30);
        const long long autoKey = ((long long) s.seed << 12) ^ ((long long) s.variation << 2) ^ (long long) s.genre;
        if (fresh || autoKey != autoSeed) { autoValue = autoEntry (s); autoSeed = autoKey; }
        const int e = s.entry == EntryAuto ? autoValue : s.entry;
        entryInUse = e;
        const int L = s.buildBars;
        const bool building = s.scene && e != EntryAll && bs < L;
        const int first = building ? kEntryLayer[e] : -1;

        if (s.endRequested && ! endWasRequested && !manualEndTime)
            manualEndTime=time+(s.ending==EndFade?2*barDuration:musicaltime::Tick{});
        endWasRequested = s.endRequested;
        const bool hasEnd = s.sceneBars > 0 || manualEndTime.has_value();
        sceneEndTime=s.sceneBars>0?std::optional<musicaltime::Tick>{sceneTime+barDuration*s.sceneBars}:std::nullopt;
        if (manualEndTime.has_value()) sceneEndTime=std::min(sceneEndTime.value_or(*manualEndTime),*manualEndTime);
        const int T = manualEndTime.has_value() ? 2 : std::clamp (std::min (L, s.sceneBars / 2), 1, 64);   // Takte zum Ausduennen / Steigern vor dem Ende
        const long long left = hasEnd ? (*sceneEndTime-time+barDuration-musicaltime::Tick{1})/barDuration : (1LL << 30);   // Takte bis zum Ende, der laufende mitgezaehlt
        if (manualEndTime.has_value() && time >= *sceneEndTime) manualFinished=true;
        sceneEnded = manualFinished || (hasEnd && time >= *sceneEndTime);

        // Traegheit: ein nur auf Taktanfaengen, aus erst deutlich unter der Schwelle und nach mindestens zwei Takten
        for (int l = 0; l < kNumLayers; ++l)
        {
            if (fresh) { hOn[l] = levelOn (s, l); hSince[l] = time; prevOn[l] = false; continue; }
            if (! s.inertia || ! barStart) continue;
            if (! hOn[l] && levelOn (s, l)) { hOn[l] = true; hSince[l] = time; }
            else if (hOn[l] && levelOff (s, l) && time - hSince[l] >= barDuration*s.policy.texture.minimumActiveBars) hOn[l] = false;
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
                entryTime[l] = (s.scene || (s.inertia && ! fresh)) ? std::optional<musicaltime::Tick>{time} : std::nullopt;
            }
            if (! on[l] && prevOn[l] && ! fresh && special) cut (l, time, thinned[l] ? time + barDuration : time, offset, out);
            prevOn[l] = on[l];

            // Haerte: unter der Mitte eingeblendet (ganz weich ueber zwei Takte), ueber der Mitte ein kraeftiger erster Anschlag
            const auto fadeLen=musicaltime::fromGridStep(s.hardness<.5f?static_cast<int64_t>(std::lround((.5f-s.hardness)*4.f*static_cast<float>(meter.len))):0);
            const auto t=entryTime[l]?time-*entryTime[l]:musicaltime::Tick{};
            gain[l] = (entryTime[l] && fadeLen > musicaltime::Tick{} && t >= musicaltime::Tick{} && t < fadeLen) ? static_cast<float>(t.value) / static_cast<float>(fadeLen.value) : 1.0f;
            if (! on[l] && exitUntil[l] > exitStep[l])
                gain[l] *= std::clamp (static_cast<float>((exitUntil[l]-time).value) / static_cast<float>((exitUntil[l]-exitStep[l]).value), 0.0f, 1.0f);
            boost[l] = (entryTime[l] && t == musicaltime::Tick{} && s.hardness > 0.5f) ? (int) std::lround ((s.hardness - 0.5f) * 28.0f) : 0;
            if (entryTime[l] && t == musicaltime::Tick{} && l == kBass && e == EntryBass && building) boost[l] += 14;   // Bass-Schlag: ein fetter Ton
        }

        // Dichte waechst im Aufbau; zum Ende hin duennt sie aus (ausklingend) oder steigt weiter (offen)
        dens = building ? 0.45f + 0.55f * std::clamp ((float) bs / (float) L, 0.0f, 1.0f) : 1.0f;
        yAdd = 0.0f;
        if (hasEnd && left > 0 && left <= T)
        {
            const float r = (float) (left - 1) / (float) T;   // knapp 1 ... 0 im letzten Takt
            if (s.ending == EndFade) { dens *= 0.45f + 0.55f * r; for (float& g : gain) g *= std::clamp (static_cast<float>((*sceneEndTime-time).value)/static_cast<float>((barDuration*T).value), 0.0f, 1.0f); }
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
        prepStich = prep && lastGroup > 0 && time==musicaltime::sixteenth*(p.bar*meter.len+lastGroup);
        if (prep && ! fresh && time==musicaltime::sixteenth*(p.bar*meter.len+meter.len/2)) cut (kBass, time, time, offset, out);
    }

    // Toene einer Ebene beenden: sofort (until <= k) oder spaetestens bei until
    void cut (int layer, musicaltime::Tick time, musicaltime::Tick until, int offset, EventList& out)
    {
        exitStep[layer] = time; exitUntil[layer] = until;
        for (int i = 0; i < numActive;)
        {
            auto& a = active[(size_t) i];
            if (kOutputLayer[a.out] != layer) { ++i; continue; }
            if (until <= time)
            {
                removeActive (i, offset, out);
                continue;
            }
            limitClaim(a,until,execution::Timing::nominal);
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
            for (int n : { r, r + 7, r + 12 + (minor ? 3 : 4), r + 19 }) noteOn (OutPadShort, n, v - 6, p.time + musicaltime::sixteenth*2, offset, out);
        }
        if (muteSoloOk (s, kBass)) noteOn (OutBassShort, place (s.key, bassLow (s)), v, p.time + musicaltime::sixteenth*2, offset, out);
        if (muteSoloOk (s, kAkzent)) noteOn (OutStich, stichTone (s, s.key), v, p.time + musicaltime::sixteenth*2, offset, out);
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
        const int q = (int) (((phrase - phraseOf(sceneTime)) % 4 + 4) % 4);
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
        musicaltime::Tick at{},length{};int pitch=0,velocity=0;
        bool valid=false;
    };
    struct PlayableHandoff { composition::MotifHandoffPlan plan; int base=-1;musicaltime::Tick origin{}; };
    musicaltime::Tick motifAvailableUntil(const Settings& s,int layer)const
    {
        auto end=sceneEndTime.value_or(musicaltime::Tick{INT64_MAX/4});
        if(s.ending==EndFade&&(s.sceneBars>0||manualEndTime))
        {
            int slots=0;const int index=orderIndex(s,entryInUse,layer,slots);
            const int tailBars=manualEndTime?2:std::clamp(std::min(s.buildBars,s.sceneBars/2),1,64);
            if(index>0)end-=musicaltime::fromGridStep(slotBar(index,slots,tailBars)*meter.len);
        }
        return end;
    }
    struct MotifHarmony { Chord chord;musicaltime::Tick end{}; };
    // The shared harmonic timeline is also the motif's harmonic reference.
    MotifHarmony motifHarmonyAt(musicaltime::Tick at,const Settings& s)const
    {
        const auto position=locate(at);
        return {chordFor(position,kMelodie,s),position.chordEndTime};
    }

    uint64_t motifHarmonyKey(const Settings& s,int output)const
    {
        uint64_t key=1469598103934665603ull;
        auto add=[&](int64_t value){key^=static_cast<uint64_t>(value);key*=1099511628211ull;};
        for(auto value:{int64_t(current),wendungTime.value,int64_t(chordBase),int64_t(still),int64_t(s.key),
            int64_t(meter.len),int64_t(phraseBars),int64_t(allowsPassingHarmony(s)&&s.y>=.6f)})add(value);
        const auto& w=W();for(int i=0;i<w.n;++i){add(w.ch[i].root);add(w.ch[i].type);add(w.ch[i].bars);}
        const auto c=outputCatalog(s)[output].track.instrument;
        add(c.range.low);add(c.range.high);add(c.minDuration.value);add(c.maxDuration.value);
        const auto& policy=s.genre==GenrePopRock&&output==OutCounter?s.policy.popHooks.recurrence:s.policy.motif;
        add(policy.establishOriginal);add(policy.preserveContour);
        uint32_t swing=0;std::memcpy(&swing,&s.swing,sizeof swing);add(swing);
        return key;
    }
    // Automation cannot rewrite an already heard prefix. A changed harmony may
    // keep a begun thought only if all its remaining attacks/gates still fit.
    bool remainingMotifFits(const composition::MotifOccurrence& plan,musicaltime::Tick time,const Settings& s,int output)const
    {
        const auto capability=outputCatalog(s)[output].track.instrument;
        for(int i=0;i<plan.figure.count;++i)
        {
            const auto& n=plan.figure.notes[i];auto at=plan.begin+n.at;
            if(at<time)continue;
            const int pitch=plan.base+n.interval;
            if(pitch<capability.range.low||pitch>capability.range.high)return false;
            const auto length=output==OutCounter&&i+1<plan.figure.count?std::min(n.length,plan.figure.notes[i+1].at-n.at):n.length;
            const auto end=at+length;
            for(int part=0;at<end&&part<32;++part)
            {
                const auto h=motifHarmonyAt(at,s);unsigned mask=0;
                for(int j=0;j<kShapes[h.chord.type].n;++j)mask|=composition::pitchBit(s.key+h.chord.root+kShapes[h.chord.type].iv[j]);
                if(!(mask&composition::pitchBit(pitch))||h.end<=at)return false;
                at=std::min(end,h.end);
            }
            if(at<end)return false;
        }
        return true;
    }
    composition::MotifOccurrence continueMotif(const composition::MotifOccurrence& previous,
        const composition::RememberedMotif& memory,musicaltime::Tick time,const Settings& s,int output)const
    {
        // Always derive from the immutable original; freeze the already heard prefix.
        // No accumulating transformations and no replacement of past MIDI notes.
        if(previous.figure.passingIndex>=0||previous.figure.variation!=composition::MotifVariation::original)return {};
        auto figure=composition::deriveMotif(memory,composition::MotifVariation::original);
        if(figure.count!=previous.figure.count)return {};
        const auto capability=outputCatalog(s)[output].track.instrument;
        unsigned masks[10]{};musicaltime::Tick limits[10]{};int fixed[10];int prefix=0;
        const auto& heard=voice(output).reprise;
        for(int i=0;i<figure.count;++i)
        {
            const auto& note=figure.notes[i];const auto at=previous.begin+note.at;fixed[i]=-1;
            if(at<time||(heard.identity==memory.identity&&heard.begin==previous.begin&&(heard.played&(1u<<i))))
            {
                ++prefix;fixed[i]=previous.base+previous.figure.notes[i].interval;
                masks[i]=composition::pitchBit(fixed[i]);limits[i]=previous.figure.notes[i].length;
            }
            else
            {
                const auto h=motifHarmonyAt(at,s);
                for(int j=0;j<kShapes[h.chord.type].n;++j)masks[i]|=composition::pitchBit(s.key+h.chord.root+kShapes[h.chord.type].iv[j]);
                const auto end=execution::nominalAt(musicaltime::toQuarters(h.end),execution::Timing::groove,s.swing);
                limits[i]=std::min(note.length,end-at);
                if(i+1<figure.count)limits[i]=std::min(limits[i],figure.notes[i+1].at-note.at);
            }
        }
        if(!prefix)return {};
        const auto realized=composition::realizeScoreMotif(figure,masks,limits,capability.range,
            capability.minDuration,capability.maxDuration,previous.base,fixed);
        if(realized.base<0)return {};
        auto result=previous;result.base=realized.base;result.figure=realized.figure;
        result.end=result.begin+result.figure.span;
        return result.end<=motifAvailableUntil(s,kOutputLayer[output])?result:composition::MotifOccurrence{};
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
        if(s.genre!=GenrePopRock||!material.performedTiming)return material;
        const auto origin=floorDiv(voice(output).motif.originTime.value,musicaltime::sixteenth.value);
        Settings recorded=s;recorded.swing=voice(output).captureSwing;
        // Invert the recorded performance swing to nominal positions. Both representations
        // are PPQ; this is a timing interpretation, never a change of storage units.
        auto nominalAt=[&](musicaltime::Tick at)
        {
            const auto estimate=static_cast<long long>(std::llround(static_cast<double>(at.value)/musicaltime::ticksPerGridStep));
            auto best=estimate;double distance=1e20;
            for(auto n=estimate-2;n<=estimate+2;++n){const double d=std::abs((execution::quarters(musicaltime::sixteenth*(origin+n),execution::Timing::groove,recorded.swing)-musicaltime::toQuarters(musicaltime::sixteenth*origin))*musicaltime::ticksPerQuarter-at.value);if(d<distance){best=n;distance=d;}}
            return musicaltime::fromGridStep(best);
        };
        const auto quantum=composition::motifQuantum;
        for(int i=0;i<material.count;++i){auto& n=material.notes[i];const auto start=nominalAt(n.at),end=nominalAt(n.at+n.length);n.at=start;n.length=std::max(quantum,end-start);}
        material.performedTiming=false;
        for(int i=0;i<material.count;++i)material.notes[i].length=std::max(quantum,std::min(material.notes[i].length,material.cycleLength-material.notes[i].at));
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
        if(popMelodicRoles(s)&&output==OutMelody)return;
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
            request.harmonyBegin=sourceAt;request.harmonyEnd=h.end;request.minDuration=capabilities.minDuration;
            request.maxDuration=std::min(policy.maxDuration,capabilities.maxDuration);
            const auto passing=composition::planPassingTone(request);if(!passing.valid)continue;
            for(int j=figure.count;j>i+1;--j)figure.notes[j]=figure.notes[j-1];
            figure.notes[i].length=std::min(figure.notes[i].length,passing.begin-sourceAt);
            figure.notes[i+1]={passing.begin-occurrence.begin,passing.end-passing.begin,passing.pitch-occurrence.base,std::max(1,target.velocity-6)};
            ++figure.count;figure.passingIndex=i+1;return;
        }
    }
    bool scoreMotifAdaptation(const Settings& s,int output)const
    {
        if(s.genre!=GenreScore)return false;
        // An optional adapted return must not displace the dialog's first actual
        // introduction: its published material also drives existing Arp reservations.
        if(output==OutMelody&&on[kGegenstimme]&&s.motif&&!voice(OutCounter).motif.material(motifCatalog).complete)
        {
            const auto p=locate(nowTime);const auto c=outputCatalog(s)[OutCounter].track.instrument;int playable=0;
            for(int i=0;i<initialMotifSlots(s);++i){const auto n=planMotifNote(i,p,s,OutCounter,nullptr,false);const int pitch=n.pitch+12*octaveOf(OutCounter);
                playable+=n.valid&&pitch>=c.range.low&&pitch<=c.range.high&&n.length>=c.minDuration&&n.length<=c.maxDuration;}
            if(playable>=2)return false;
        }
        // Shared physical claims and the existing explicit dialog/Arp response
        // retain their exact figures; no accompaniment behavior changes here.
        for(int o=0;o<OutCounter;++o)if(s.channel[o]==s.channel[output])return false;
        return !(output==OutCounter&&!on[kMelodie]&&s.arpFigure==ArpCell&&on[kArp]&&!s.scene
            &&s.meterNum==4&&s.meterDen==4&&phraseBars>=4);
    }
    composition::MotifOccurrence motifOccurrence(musicaltime::Tick time,const Pos& p,const Settings& s,int output,bool preview=false,bool reservation=false)
    {
        const auto bar=musicaltime::fromGridStep(meter.len);
        auto& state=voice(output);const auto& use=state.motif;auto memory=performanceMaterial(output,s);
        const auto& policy=s.genre==GenrePopRock&&!(popMelodicRoles(s)&&output==OutMelody)?s.policy.popHooks.recurrence:s.policy.motif;
        const auto origin=use.originTime;
        const auto section=p.phrase-phraseOf(sceneTime);
        if(memory.count&&(time-p.phraseStartTime>=std::min(2*bar,p.phraseEndTime-p.phraseStartTime)||section!=use.introduction))memory.finish();
        if(!memory.complete)return {true,true,false,p.phraseStartTime,p.phraseStartTime+std::min(2*bar,p.phraseEndTime-p.phraseStartTime),0,0};
        const auto window=bar*policy.windowBars;
        if(time<origin)return {};
        const auto epoch=(time-origin)/window;
        musicaltime::Tick span{};for(int i=0;i<memory.count;++i)span=std::max(span,memory.notes[static_cast<size_t>(i)].at+memory.notes[static_cast<size_t>(i)].length);
        const bool dialogue=output==OutCounter&&!on[kMelodie]&&s.genre==GenreScore&&s.arpFigure==ArpCell&&!s.scene
            &&s.meterNum==4&&s.meterDen==4&&on[kArp]&&on[kGegenstimme]&&phraseBars>=4;
        // The existing dialogue/Arp answer follows this introduction. Its reserved
        // response must not be replaced by a new epoch-zero reprise.
        if(epoch==0&&(!policy.establishOriginal||time<origin+span||dialogue))return {true,true,false,origin,origin+span,0,0};
        auto heard=state.reprise;if(heard.identity!=memory.identity)heard={};
        const bool establishing=policy.establishOriginal&&(!heard.establishedAt||time<*heard.establishedAt);
        // An onset lookup may precede nominal harmony preparation. Preview only the
        // bounded derived cache; never commit a future decision from the old context.
        auto& stored=reservation&&s.genre==GenreScore?state.reservationRecurrence:state.recurrence;
        auto cacheCopy=stored;
        auto& cached=preview?cacheCopy:stored;
        const auto harmony=motifHarmonyKey(s,output);
        const bool sameSlot=cached.epoch==epoch&&cached.identity==memory.identity&&cached.origin==origin&&cached.window==window;
        if(sameSlot&&cached.harmony==harmony)return cached.plan.end<=motifAvailableUntil(s,kOutputLayer[output])?cached.plan:composition::MotifOccurrence{};
        if(sameSlot&&cached.started)
        {
            cached.harmony=harmony;
            if(cached.plan.active&&!remainingMotifFits(cached.plan,time,s,output))
            {
                const bool adaptable=policy.establishOriginal&&(scoreMotifAdaptation(s,output)
                    ||(popMelodicRoles(s)&&((output==OutMelody&&popLeadRoute(s))||(output==OutCounter&&phrasedHook(s)&&popDialogRoute(s)))));
                cached.plan=adaptable?continueMotif(cached.plan,memory,time,s,output):composition::MotifOccurrence{};
            }
            return cached.plan.end<=motifAvailableUntil(s,kOutputLayer[output])?cached.plan:composition::MotifOccurrence{};
        }
        cached.harmony=harmony;cached.started=false;
        cached.epoch=epoch;cached.identity=memory.identity;cached.origin=origin;cached.window=window;cached.plan={};
        auto slot=composition::recurrenceSlot(policy,epoch,layerY(s,kOutputLayer[output]),s.z);
        if(epoch==0&&establishing)slot={true,1,1,false};
        if(!slot.eligible)return {};
        const auto horizon=origin+epoch*window,end=std::min(horizon+window,motifAvailableUntil(s,kOutputLayer[output]));
        auto begin=horizon;
        if(policy.establishOriginal)
        {
            // One actual thought per horizon. Neither failed opportunities nor
            // automation may manufacture extra reiterations. Chase reconstructs
            // an earlier performance, without consuming a future rest budget.
            if(!chasingPatterns&&!harmonicChase&&heard.begin>=horizon&&heard.begin<horizon+window)return {};
            // Articulation shortens gates, not the musical thought/cycle.
            const auto thought=std::max(memory.cycleLength,bar*((span.value+bar.value-1)/bar.value));
            begin=std::max(begin,origin+thought+policy.minimumSilentBars*bar);
            if(!chasingPatterns&&!harmonicChase&&heard.identity==memory.identity)begin=std::max(begin,heard.end+policy.minimumSilentBars*bar);
        }
        const auto response=dialogue?2*bar:musicaltime::Tick{};
        const auto catalog=outputCatalog(s);const auto& capability=catalog[output].track.instrument;
        auto attempt=[&](composition::MotifVariation variation,bool adaptive=false,int fragmentNotes=0)
        {
        const auto figure=fragmentNotes?composition::suffixFigure(memory,fragmentNotes):composition::deriveMotif(memory,variation,policy.sequenceSemitones);
        if(!figure.count)return composition::MotifOccurrence{};
        const auto last=end-figure.span-policy.minimumSilentBars*bar-response;
        std::array<composition::MotifPlacement,32> candidates {};
        std::array<composition::MotifFigure,32> realizations {};int count=0;
        auto add=[&](musicaltime::Tick at)
        {
            if(at<begin||(!chasingPatterns&&!harmonicChase&&(sameSlot||policy.establishOriginal)&&at<time)||at>last||count==32)return;
            for(int i=0;i<count;++i)if(candidates[static_cast<size_t>(i)].begin==at)return;
            unsigned allowed[10] {};musicaltime::Tick limits[10] {};
            for(int i=0;i<figure.count;++i)
            {
                const auto& n=figure.notes[static_cast<size_t>(i)];allowed[i]=0xfffu;
                auto tick=at+n.at;
                const auto harmonicLength=output==OutCounter&&i+1<figure.count
                    ?std::min(n.length,figure.notes[static_cast<size_t>(i+1)].at-n.at):n.length;
                const auto finish=tick+harmonicLength;
                limits[i]=n.length;
                if(adaptive)
                {
                    const auto h=motifHarmonyAt(tick,s);allowed[i]=0;const auto& shape=kShapes[h.chord.type];
                    for(int j=0;j<shape.n;++j)allowed[i]|=1u<<((s.key+h.chord.root+shape.iv[j])%12);
                    // A groove-domain gate must finish at the nominal harmony boundary,
                    // also when an odd-meter bar ends on a swung subdivision.
                    const auto releaseLimit=execution::nominalAt(musicaltime::toQuarters(h.end),execution::Timing::groove,s.swing);
                    limits[i]=std::min(n.length,releaseLimit-tick);
                    if(i+1<figure.count)limits[i]=std::min(limits[i],figure.notes[i+1].at-n.at);
                    continue;
                }
                if(n.length<capability.minDuration||n.length>capability.maxDuration)return;
                for(int step=0;tick<finish&&step<32;++step)
                {
                    const auto h=motifHarmonyAt(tick,s);unsigned mask=0;const auto& shape=kShapes[h.chord.type];
                    for(int j=0;j<shape.n;++j)mask|=1u<<((s.key+h.chord.root+shape.iv[j])%12);
                    allowed[i]&=mask;if(h.end<=tick)return;tick=std::min(finish,h.end);
                }
                if(tick<finish||!allowed[i])return;
            }
            int base=-1,cost=10000;auto realization=figure;
            if(adaptive)
            {
                const auto adapted=composition::realizeScoreMotif(figure,allowed,limits,capability.range,
                    capability.minDuration,capability.maxDuration,memory.origin);
                base=adapted.base;cost=adapted.cost;realization=adapted.figure;
            }
            for(int candidate=0;!adaptive&&candidate<128;++candidate)
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
                if(fits&&policy.preserveContour)
                    for(int i=1;i<adjusted.count;++i)
                    {
                        const int wanted=figure.notes[i].interval-figure.notes[i-1].interval;
                        const int actual=adjusted.notes[i].interval-adjusted.notes[i-1].interval;
                        if((wanted==0&&actual!=0)||(wanted>0&&actual<=0)||(wanted<0&&actual>=0))fits=false;
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
        for(auto at=begin;at<=last;)
        {
            const auto h=motifHarmonyAt(at,s);add(at);
            const auto middle=at+std::max<int64_t>(0,(std::min(h.end,end)-at-figure.span)/2/bar)*bar;
            add(middle);if(h.end<=at)break;at=h.end;
        }
        auto result=composition::planRecurrence(policy,slot,begin,end,figure.span,bar,candidates.data(),count,response);
        if(result.active){for(int i=0;i<count;++i)if(candidates[i].begin==result.begin&&candidates[i].base==result.base){result.figure=realizations[i];break;}result.varied=variation==composition::MotifVariation::rhythm;if(adaptive)result.end=result.begin+result.figure.span;}
        return result;
        };
        const auto variation=establishing?composition::MotifVariation::original:composition::motifVariation(policy,slot.ordinal);
        cached.plan=attempt(variation);
        if(!cached.plan.active&&variation!=composition::MotifVariation::original)
            cached.plan=attempt(composition::MotifVariation::original);
        if(!cached.plan.active&&(((!reservation||policy.establishOriginal)&&scoreMotifAdaptation(s,output))
            ||(popMelodicRoles(s)&&((output==OutMelody&&popLeadRoute(s))
                ||(policy.establishOriginal&&output==OutCounter&&phrasedHook(s)&&popDialogRoute(s))))))
        {
            cached.plan=attempt(composition::MotifVariation::original,true);
            for(int notes=std::min(3,memory.count-1);!establishing&&!cached.plan.active&&notes>=2;--notes)
                cached.plan=attempt(composition::MotifVariation::fragment,true,notes);
        }
        if(!establishing)addPassingTone(cached.plan,s,output);
        return cached.plan;
    }

    struct AuthoredMotif {const composition::barry::MotifSource* source=nullptr;int base=-1;};
    AuthoredMotif authoredMotif(const Pos& p,const Settings& s,int output)const
    {
        if(!authoredCells(s))return {};
        const auto& recorded=voice(output).motif.material(motifCatalog);
        const auto track=outputCatalog(s)[output].track;composition::RoleNeed need;need.range=track.instrument.range;
        if(!composition::suitable(track,need))return {};
        AuthoredMotif result;float best=1e9f;
        for(const auto& source:composition::barry::motifs)
        {
            if(source.num!=s.meterNum||source.den!=s.meterDen||(recorded.vocabularyId&&recorded.vocabularyId!=static_cast<uint32_t>(source.id)))continue;
            const auto span=musicaltime::sixteenth*source.steps;
            if(p.phraseStartTime+span>p.phraseEndTime||p.phraseStartTime+span>motifAvailableUntil(s,kOutputLayer[output]))continue;
            unsigned masks[8]{};bool valid=true;
            for(int i=0;i<source.count;++i)
            {
                const auto length=musicaltime::sixteenth*source.lengths[i];
                if(length<track.instrument.minDuration||length>track.instrument.maxDuration){valid=false;break;}
                auto at=p.phraseStartTime+musicaltime::sixteenth*source.at[i];const auto end=at+length;masks[i]=0xfffu;
                for(int part=0;at<end&&part<8;++part)
                {
                    const auto position=locate(at);const auto h=chordFor(position,kOutputLayer[output],s);unsigned chord=0;
                    for(int j=0;j<kShapes[h.type].n;++j)chord|=composition::pitchBit(s.key+h.root+kShapes[h.type].iv[j]);
                    // Unpredictable automation cannot rewrite an already heard prefix.
                    if(!recorded.vocabularyId||at>=p.time)masks[i]&=chord;
                    if(position.chordEndTime<=at){valid=false;break;}at=std::min(end,position.chordEndTime);
                }
                if(at<end||!masks[i])valid=false;
            }
            if(!valid)continue;
            const int preferred=s.key+source.pitches[0]+(output==OutMelody?12:0)+12*octaveOf(output);
            int chosen=-1,cost=10000;
            for(int base=0;base<128;++base)
            {
                if(recorded.vocabularyId)
                {
                    // A late activation can first hear the middle of a cell. Its
                    // recorded origin is that actual note, not the template's first pitch.
                    int first=-1;for(int j=0;j<source.count;++j)
                        if(recorded.notes[0].at==musicaltime::sixteenth*source.at[j])first=j;
                    if(first<0||base!=recorded.origin-source.pitches[first]+source.pitches[0])continue;
                }
                bool fits=true;
                for(int i=0;i<source.count;++i)
                {
                    const int pitch=base+source.pitches[i]-source.pitches[0];
                    if(pitch<track.instrument.range.low||pitch>track.instrument.range.high||pitch<0||pitch>127||!(masks[i]&composition::pitchBit(pitch))){fits=false;break;}
                }
                if(fits&&std::abs(base-preferred)<cost){cost=std::abs(base-preferred);chosen=base;}
            }
            if(chosen<0)continue;
            const float score=composition::barry::distance(s.x,s.y,s.z,source.x,source.y,source.z)+.0001f*cost;
            if(score<best){best=score;result={&source,chosen};}
        }
        return result;
    }
    int initialMotifSlots(const Settings& s)const {return authoredCells(s)?8:5;}
    musicaltime::Tick initialMotifAt(int i,const Pos& p,const Settings& s,int output)const
    {
        const auto authored=authoredMotif(p,s,output);
        if(authored.source)return i<authored.source->count?musicaltime::sixteenth*authored.source->at[i]:p.phraseEndTime-p.phraseStartTime;
        const auto legacy=motifFor(s,p.phrase);
        return i<legacy.n?motifTemplatePosition(legacy.on[i]):p.phraseEndTime-p.phraseStartTime;
    }

    // Template positions are dimensionless sixteenths OF A BAR, not fixed sixteenth notes.
    // Keep their existing floor-to-performance-grid realisation (including odd meters).
    // Stored material and derived variants never pass through this template conversion.
    musicaltime::Tick motifTemplatePosition(int subdivision)const
    {return musicaltime::fromGridStep(static_cast<int64_t>(subdivision)*meter.len/16);}

    // One note calculation shared by the existing performance and accompaniment preflight.
    // The caller supplies the harmony at that note's onset; no memory or MIDI is modified.
    PlannedMotifNote planMotifNote(int i,const Pos& p,const Settings& s,int output,
        const composition::RememberedMotif* memory,bool varied,const composition::MotifOccurrence* occurrence=nullptr)const
    {
        PlannedMotifNote n;
        if(!memory&&authoredCells(s))
        {
            const auto plan=authoredMotif(p,s,output);
            if(plan.source)
            {
                if(i>=plan.source->count)return n;
                n.at=musicaltime::sixteenth*plan.source->at[i];n.length=musicaltime::sixteenth*plan.source->lengths[i];
                n.pitch=plan.base+plan.source->pitches[i]-plan.source->pitches[0]-12*octaveOf(output);
                n.velocity=static_cast<int>(56+35*layerY(s,kOutputLayer[output]))+(i==0?6:0);
                const bool legato=output==OutMelody?s.melodyLegato:s.legato;
                n.length=composition::articulatedLength(n.length,n.length,legato);n.valid=true;return n;
            }
            if(voice(output).motif.material(motifCatalog).vocabularyId)return n; // Never splice a new cell into a begun gesture.
        }
        const auto span=memory?p.phraseEndTime-p.phraseStartTime:std::min(musicaltime::fromGridStep(2LL*meter.len),p.phraseEndTime-p.phraseStartTime);
        const auto yc=layerY(s,kOutputLayer[output]);
        const Motif mo=motifFor(s,p.phrase);
        // Preserve the existing introduced material (tone count/rhythm), independently of restored expression.
        const float materialBase=(dens<.999f||yAdd>.001f)?std::clamp(curY*dens+yAdd,0.f,1.f):curY;
        const float materialY=std::clamp(materialBase+s.layerIntensity[kOutputLayer[output]],0.f,1.f);
        const auto* figure=occurrence&&occurrence->figure.count?&occurrence->figure:nullptr;
        const int count=figure?figure->count:memory?memory->count:materialY>=.55f?mo.n:materialY>=.3f?std::max(2,mo.n-1):std::max(2,mo.n-2);
        if(i>=count)return n;
        n.at=figure?figure->notes[static_cast<size_t>(i)].at:memory?memory->notes[static_cast<size_t>(i)].at:motifTemplatePosition(mo.on[i]);
        if(n.at<musicaltime::Tick{}||n.at>=span)return n;
        const bool authoredReplay=memory&&occurrence&&occurrence->introduction&&authoredCells(s)&&memory->vocabularyId;
        int ladder[16] {};const bool exact=memory&&occurrence&&(!occurrence->introduction||authoredReplay);
        const int nl=exact?1:counterLadder(chordFor(p,kOutputLayer[output],s),s,ladder,output);
        if(!nl)return n;
        if(memory)
        {
            const auto& recorded=figure?figure->notes[static_cast<size_t>(i)]:memory->notes[static_cast<size_t>(i)];
            const int base=composition::adaptMotifPitch(memory->origin-12*octaveOf(output),ladder,nl);
            if(authoredReplay)
            {
                auto context=locate(p.time);context.phraseStartTime=p.phraseStartTime;
                if(!authoredMotif(context,s,output).source)return n;
                n.pitch=memory->origin+recorded.interval-12*octaveOf(output);
            }
            else n.pitch=occurrence&&!occurrence->introduction?occurrence->base+recorded.interval-12*octaveOf(output)
                :composition::adaptMotifPitch(base+recorded.interval,ladder,nl);
            n.velocity=recorded.velocity;
            n.length=std::min(figure?recorded.length:memory->recalledLength(i,varied,span),span-n.at);
            if(output==OutMelody&&(!memory->vocabularyId||memory->legatoAtCapture!=s.melodyLegato))n.length=composition::articulatedLength(n.length,
                std::min(exact?span-n.at:p.chordEndTime-(p.phraseStartTime+n.at),i+1<count?(figure?figure->notes[static_cast<size_t>(i+1)].at:memory->notes[static_cast<size_t>(i+1)].at)-n.at:span-n.at),s.melodyLegato);
        }
        else
        {
            auto end=i+1<count?motifTemplatePosition(mo.on[i+1]):span;
            end=std::min(end,p.phraseEndTime-p.phraseStartTime);
            const auto& policy=s.genre==GenrePopRock&&output==OutCounter?s.policy.popHooks.recurrence:s.policy.motif;
            n.pitch=ladder[policy.preserveContour?composition::fittedMotifDegree(mo.deg,count,i,nl):std::clamp(mo.deg[i],0,nl-1)];n.velocity=static_cast<int>(56+35*yc)+(i==0?6:0);
            const auto extension=cur!=nullptr&&cur->legato?composition::motifQuantum
                :end-n.at>=4*composition::motifQuantum?-1*composition::motifQuantum:musicaltime::Tick{};
            n.length=std::min(span,end+(output==OutMelody?musicaltime::Tick{}:extension))-n.at;
            if(output==OutMelody)n.length=composition::articulatedLength(n.length,
                std::min(n.length,p.chordEndTime-(p.phraseStartTime+n.at)),s.melodyLegato);
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
    composition::MotifWindow motifVoiceWindow(const Pos& p,const Settings& s,int output,bool preview=false,bool roleWindow=false)
    {
        if(!on[kOutputLayer[output]]||(s.genre==GenreScore&&!(output==OutMelody?s.melodyMotif:s.motif)))return {};
        if(s.genre==GenrePopRock&&!(popMelodicRoles(s)&&roleWindow&&output==OutMelody)&&(!phrasedHook(s)||!voice(output).motif.material(motifCatalog).complete))return {};
        const auto catalog=outputCatalog(s);composition::RoleNeed need;need.range=catalog[output].track.instrument.range;
        if(!composition::suitable(catalog[output].track,need))return {};
        const auto occurrence=motifOccurrence(p.time,p,s,output,preview,!roleWindow);if(!occurrence.active)return {};
        auto memory=performanceMaterial(output,s);
        if(memory.count&&p.phrase-phraseOf(sceneTime)!=voice(output).motif.introduction)memory.finish();
        const bool complete=memory.complete;const auto mo=motifFor(s,p.phrase);
        int count=0,future=0;auto begin=occurrence.end,end=occurrence.begin;
        for(int i=0;i<(occurrence.figure.count?occurrence.figure.count:complete?memory.count:authoredCells(s)?8:mo.n);++i)
        {
            const auto at=occurrence.figure.count?occurrence.figure.notes[static_cast<size_t>(i)].at:complete?memory.notes[static_cast<size_t>(i)].at:initialMotifAt(i,p,s,output);
            auto local=locate(occurrence.begin+at);local.phraseStartTime = occurrence.begin;local.phraseEndTime = occurrence.end;
            const auto note=planMotifNote(i,local,s,output,complete?&memory:nullptr,occurrence.varied,&occurrence);
            if(!note.valid)continue;
            const auto& c=catalog[output].track.instrument;if(note.length<c.minDuration||note.length>c.maxDuration)continue;
            ++count;if(occurrence.begin+note.at>=p.time)++future;
            begin=std::min(begin,occurrence.begin+note.at);end=std::max(end,occurrence.begin+note.at+note.length);
        }
        if(roleWindow)return count>0&&end>begin?composition::MotifWindow{catalog[output].track.id,begin,end}:composition::MotifWindow{};
        if(!future&&!outputSounding(output)&&!chasingPatterns&&!(popMelodicRoles(s)&&!roleWindow))return {};
        return composition::reserveMotifWindow(catalog[output].track.id,count,begin,end);
    }

    bool popLeadRoute(const Settings& s)const
    {
        for(int o=0;o<OutCounter;++o)if(s.channel[o]==s.channel[OutMelody]||s.channel[o]==s.channel[OutCounter])return false;
        return s.channel[OutMelody]!=s.channel[OutCounter];
    }
    bool popDialogRoute(const Settings& s)const
    {for(int o=0;o<OutCounter;++o)if(s.channel[o]==s.channel[OutCounter])return false;return true;}
    bool popHookIntroductionPending(const Pos& p,const Settings& s)
    {
        const auto& state=voice(OutCounter);
        if(!on[kGegenstimme]||state.motif.material(motifCatalog).complete)return false;
        if(state.capture.active)return true;
        const auto capability=outputCatalog(s)[OutCounter].track.instrument;int playable=0;
        const auto bar=musicaltime::sixteenth*meter.len;
        for(auto at=p.phraseStartTime;at<p.phraseStartTime+2*bar;at+=musicaltime::sixteenth)
        {const auto n=hookNote(at,locate(at),s);const int pitch=sounding(OutCounter,n.pitch);
            playable+=n.valid&&pitch>=capability.range.low&&pitch<=capability.range.high&&n.length>=capability.minDuration&&n.length<=capability.maxDuration;}
        return playable>=2;
    }
    composition::MotifWindow popLeadWindow(const Pos& p,const Settings& s,bool preview=true)
    {
        if(!on[kMelodie]||!popLeadRoute(s))return {};
        // Preserve the first actually captured hook, including boundary retriggers.
        if(on[kGegenstimme]&&p.time<sceneTime+4*musicaltime::sixteenth*meter.len)return {};
        const auto& leadState=voice(OutMelody);
        const bool inProgress=outputSounding(OutMelody)
            ||(leadState.recurrence.plan.active&&p.time>=leadState.recurrence.plan.begin&&p.time<leadState.recurrence.plan.end)
            ||(!leadState.motif.material(motifCatalog).complete&&leadState.motif.material(motifCatalog).count>0
                &&p.phrase-phraseOf(sceneTime)==leadState.motif.introduction);
        if(!inProgress&&popHookIntroductionPending(p,s))return {};
        const auto track=outputCatalog(s)[OutMelody].track;
        if(!composition::planForeground(s.melody,track).foreground)return {};
        const auto bar=musicaltime::sixteenth*meter.len;
        if(s.melodyMotif)
        {
            auto memory=performanceMaterial(OutMelody,s);
            if(memory.count&&(p.time>=p.phraseStartTime+2*bar||p.phrase!=voice(OutMelody).motif.introduction+phraseOf(sceneTime)))memory.finish();
            if(!memory.complete&&p.time>=p.phraseStartTime+std::min(2*bar,p.phraseEndTime-p.phraseStartTime))return {};
            return motifVoiceWindow(p,s,OutMelody,true,true);
        }
        int ladder[16];if(!counterLadder(chordFor(p,kMelodie,s),s,ladder,OutMelody))return {};
        const auto end=std::min(p.phraseEndTime,p.phraseStartTime+2*bar);
        auto& state=voice(OutMelody);
        if(state.popTurnValid&&state.popTurnKey==p.phraseStartTime&&state.popTurn.end==end)
            return state.popTurn.active?composition::MotifWindow{track.id,state.popTurn.begin,state.popTurn.end}:composition::MotifWindow{};
        const auto epoch=std::max<int64_t>(0,p.phrase-phraseOf(sceneTime));
        const bool active=(epoch==0||composition::recurrenceSlot(s.policy.motif,epoch,layerY(s,kMelodie),s.z).eligible);
        const composition::HookTurn turn{active,p.phraseStartTime,end};
        if(!preview){state.popTurn=turn;state.popTurnKey=p.phraseStartTime;state.popTurnValid=true;}
        return active?composition::MotifWindow{track.id,turn.begin,turn.end}:composition::MotifWindow{};
    }
    composition::HookTurn popDialogTurn(const Pos& p,const Settings& s,bool preview=true)
    {
        const auto bar=musicaltime::sixteenth*meter.len;
        const auto cycleBegin=2*bar*(p.time/(2*bar));
        if(!voice(OutCounter).motif.material(motifCatalog).complete||voice(OutCounter).capture.active)
            return {true,cycleBegin,cycleBegin+2*bar};
        if(p.time<sceneTime+4*bar)return {true,sceneTime,sceneTime+4*bar};
        // Stock Pop figures assume 4/4. Other meters breathe only at existing
        // phrase resets rather than interrupting a differently scaled hook cycle.
        const auto cycle=s.meterNum==4&&s.meterDen==4?2*bar:p.phraseEndTime-p.phraseStartTime;
        const auto key=cycle*(p.time/cycle);auto& state=voice(OutCounter);
        if(state.popTurnValid&&state.popTurnKey==key&&state.popTurn.end==key+cycle)return state.popTurn;
        const auto turn=composition::planHookTurn(s.policy.popRoles,p.time,cycle,layerY(s,kGegenstimme),s.z);
        if(!preview){state.popTurn=turn;state.popTurnKey=key;state.popTurnValid=true;}
        return turn;
    }
    bool popDialogueMayLead(const Pos& p,const Settings& s)
    {
        if(!on[kGegenstimme])return false;
        if(!popDialogRoute(s))return true; // physical accompaniment claims retain their behavior
        const bool recalled=s.motif&&phrasedHook(s)&&voice(OutCounter).motif.material(motifCatalog).complete;
        const auto turn=popDialogTurn(p,s);
        auto begin=turn.begin,end=turn.end;
        if(recalled){const auto plan=motifOccurrence(p.time,p,s,OutCounter,true);if(!plan.active)return false;begin=plan.begin;end=plan.end;}
        else if(!turn.active)return false;
        if(end>p.phraseEndTime)return false; // never overrun an as-yet unplanned lead epoch
        const auto lead=popLeadWindow(p,s);
        if(outputSounding(OutMelody)||lead.contains(p.time))return false;
        return lead.owner.value<0||end<=lead.begin||begin>=lead.end;
    }

    // Bounded Score role windows reuse the existing motif and line plans. They do
    // not change the accompaniment's established reservations or transformations.
    composition::MotifWindow melodicRoleWindow(int output,const Pos& p,const Settings& s)
    {
        if(popMelodicRoles(s))return output==OutMelody?popLeadWindow(p,s):composition::MotifWindow{};
        if(s.genre!=GenreScore||!on[kOutputLayer[output]])return {};
        const auto catalog=outputCatalog(s);
        if(output==OutMelody&&!composition::planForeground(s.melody,catalog[output].track).foreground)return {};
        const bool requested=output==OutMelody?s.melodyMotif:s.motif;
        auto memory=performanceMaterial(output,s);
        const auto span=std::min(2*musicaltime::sixteenth*meter.len,p.phraseEndTime-p.phraseStartTime);
        const bool introduction=p.time>=p.phraseStartTime&&p.time<p.phraseStartTime+span;
        if(memory.count&&(!introduction||p.phrase-phraseOf(sceneTime)!=voice(output).motif.introduction))memory.finish();
        if(requested&&(memory.complete||introduction))
        {
            auto window=motifVoiceWindow(p,s,output,true,true);
            // The existing minimum rest is part of the lead's musical thought.
            if(output==OutMelody&&window.owner.value>=0)
                window.end+=musicaltime::sixteenth*meter.len*s.policy.motif.minimumSilentBars;
            return window;
        }
        if(output==OutCounter)
        {
            const auto phrase=freeLinePhrase(p,s);
            if(phrase.valid)return {catalog[output].track.id,phrase.begin,phrase.breath};
        }
        int ladder[16];if(!counterLadder(chordFor(p,kOutputLayer[output],s),s,ladder,output))return {};
        const auto y=layerY(s,kOutputLayer[output]);
        const auto period=musicaltime::sixteenth*(y<.4f?0:y<.7f?2LL*meter.len:std::max(4LL,static_cast<long long>(meter.len)/2));
        const auto begin=period>musicaltime::Tick{}?p.chordStartTime+period*((p.time-p.chordStartTime)/period):p.chordStartTime;
        auto end=period>musicaltime::Tick{}?std::min(p.chordEndTime,begin+period):p.chordEndTime;
        if(output==OutCounter)end+=tail(end-begin);
        return {catalog[output].track.id,begin,end};
    }

    bool dialogueMayLead(const Pos& p,const Settings& s)
    {
        if(popMelodicRoles(s))return popDialogueMayLead(p,s);
        if(s.genre!=GenreScore||!on[kMelodie])return true;
        if(!on[kGegenstimme]||outputSounding(OutMelody))return false;
        // New dialogue must not alter physical claims of an accompaniment output.
        for(int o=0;o<OutCounter;++o)if(s.channel[o]==s.channel[OutCounter])return false;
        const auto lead=melodicRoleWindow(OutMelody,p,s);
        const auto answer=playableMelodyHandoff(p.time,p,s,true);
        if(lead.contains(p.time)||(answer.plan.active&&p.time>=answer.origin+answer.plan.begin&&p.time<answer.origin+answer.plan.end))return false;
        const auto candidate=melodicRoleWindow(OutCounter,p,s);
        auto overlaps=[&](musicaltime::Tick begin,musicaltime::Tick end)
        {return candidate.owner.value>=0&&candidate.begin<end&&candidate.end>begin;};
        if(lead.owner.value>=0&&overlaps(lead.begin,lead.end))return false;
        if(answer.plan.active&&overlaps(answer.origin+answer.plan.begin,answer.origin+answer.plan.end))return false;
        // Do not carry an independent thought across an as-yet unplanned lead epoch.
        const auto window=musicaltime::sixteenth*meter.len*s.policy.motif.windowBars;
        const auto origin=voice(OutMelody).motif.originTime;
        const auto epoch=std::max<int64_t>(0,(p.time-origin)/window);
        return candidate.owner.value<0||candidate.end<=origin+window*(epoch+1);
    }

    composition::MotifWindow motifWindow(const Pos& p,const Settings& s)
    {
        if((s.genre!=GenreScore&&!phrasedHook(s))||s.arpFigure!=ArpAuto)return {};
        // Shared physical notes can alter motif recording/retriggers. Preserve that routing verbatim.
        for(int o=0;o<kNumOutputs;++o)if(o!=OutArp&&s.channel[o]==s.channel[OutArp])return {};
        const auto primary=motifVoiceWindow(p,s,on[kMelodie]&&!popMelodicRoles(s)?OutMelody:OutCounter);
        if(primary.contains(p.time))return primary;
        const auto response=playableMelodyHandoff(p.time,p,s);
        if(response.plan.active)
        {
            const auto& material=*motifCatalog.find(response.plan.reference.material);
            const auto& last=material.notes[static_cast<size_t>(material.count-1)];
            const auto end=response.plan.end-(!s.legato&&last.length>composition::motifQuantum?composition::motifQuantum:musicaltime::Tick{});
            return composition::reserveMotifWindow(outputCatalog(s)[OutCounter].track.id,response.plan.count,
                response.origin+response.plan.begin,response.origin+end);
        }
        return {};
    }

    // Material recording/rendering is shared; complete returns follow the coordinated occurrence plan.
    bool motifStep (musicaltime::Tick time, const Pos& p, const Settings& s, int offset, EventList& out, int output=OutCounter)
    {
        auto& state=voice(output);auto& use=state.motif;

        const auto span=std::min(musicaltime::fromGridStep(2LL*meter.len),p.phraseEndTime-p.phraseStartTime),rel=time-p.phraseStartTime;
        const long long section=p.phrase-phraseOf(sceneTime);
        if(rel>=span||(use.material(motifCatalog).count&&section!=use.introduction))use.finish(motifCatalog);
        const auto memory=performanceMaterial(output,s);const bool complete=memory.complete;
        if(complete)
        {
            const auto occurrence=motifOccurrence(time,p,s,output);
            if(!occurrence.active||time<occurrence.begin||time>=occurrence.end)return true;
        }
        else
        {
            if(rel<musicaltime::Tick{}||rel>=span)return false;
            if(memory.count&&use.introduction!=section)use.clear();
        }
        const auto occurrence=motifOccurrence(time,p,s,output);
        auto local=p;if(complete){local.phraseStartTime = occurrence.begin;local.phraseEndTime = occurrence.end;}
        for(int i=0;i<(occurrence.figure.count?occurrence.figure.count:authoredCells(s)?(complete?memory.count:8):5);++i)
        {
            const auto note=planMotifNote(i,local,s,output,complete?&memory:nullptr,occurrence.varied,&occurrence);
            if(!note.valid||note.at!=time-local.phraseStartTime)continue;
            const int before=out.size;
            const bool savedForce=forceOn;if(s.genre==GenrePopRock)forceOn=true;
            noteOn(output,note.pitch,note.velocity,local.phraseStartTime+note.at+note.length,offset,out);forceOn=savedForce;
            for(int e=before;e<out.size;++e)
            {
                const auto& emitted=out.events[static_cast<size_t>(e)];
                if(emitted.out==output&&emitted.type==0&&emitted.velocity>0)
                {
                    if(complete)
                    {
                        state.reprise.observe(occurrence,i,memory.count);
                        state.recurrence.started=true;
                        if(state.reservationRecurrence.plan.begin==occurrence.begin)state.reservationRecurrence.started=true;
                        continue;
                    }
                    const auto authored=authoredMotif(local,s,output);
                    use.observe(emitted.note,note.at,note.length,section,note.velocity,p.phraseStartTime);
                    if(authored.source){use.draft.vocabularyId=authored.source->id;use.draft.legatoAtCapture=output==OutMelody?s.melodyLegato:s.legato;use.draft.cycleLength=musicaltime::sixteenth*authored.source->steps;}
                }
            }
            if(output==OutCounter)releaseOthers(output,note.pitch,offset,out);
            state.note=note.pitch;state.pendingAt.reset();
        }
        return true;
    }

    long long phraseOf(musicaltime::Tick time)const
    {return floorDiv(time.value,musicaltime::fromGridStep(static_cast<int64_t>(meter.len)*phraseBars).value);}

    Pos locate(long long patternOrdinal)const{return locate(musicaltime::fromGridStep(patternOrdinal));}
    Pos locate (musicaltime::Tick time) const
    {
        Pos p;p.time=time;
        const auto k=floorDiv(time.value,musicaltime::ticksPerGridStep);
        p.k = k;
        const auto barDuration=musicaltime::sixteenth*meter.len;
        p.bar = floorDiv(time.value,barDuration.value);
        p.pos = static_cast<int>((time-barDuration*p.bar)/musicaltime::sixteenth);
        p.phrase = floorDiv (p.bar, phraseBars);
        p.barInPhrase = (int) (p.bar - p.phrase * phraseBars);
        p.phraseStartTime = musicaltime::fromGridStep(p.phrase * phraseBars * meter.len);
        p.phraseEndTime = p.phraseStartTime + musicaltime::fromGridStep(static_cast<int64_t>(phraseBars)*meter.len);
        const Wendung& w = W();
        composition::ChordTimeline timeline;
        timeline.count=w.n;timeline.first=chordBase;timeline.held=still;
        timeline.begin=std::max(wendungTime,p.phraseStartTime);timeline.end=p.phraseEndTime;
        for(int i=0;i<w.n;++i)timeline.durations[static_cast<size_t>(i)]=musicaltime::fromGridStep(static_cast<int64_t>(w.ch[i].bars)*meter.len);
        const auto position=composition::locateChord(timeline,time);
        p.chordIdx=position.index;p.chordStartTime=position.begin;p.chordEndTime=position.end;
        if(still)return p;
        if (cur != nullptr)
        {
            const auto intent=composition::freeTransition(nextChordRoot(p),allowsPassingHarmony(*cur),cur->y);
            const auto transition=composition::placeTransition(intent,p.chordStartTime,p.chordEndTime,
                musicaltime::fromGridStep(meter.len),musicaltime::fromGridStep(meter.groupStart[std::max(0,meter.numGroups-1)]));
            if(transition.present)
            {
                if(time>=transition.begin){p.chordStartTime = transition.begin;p.passing=true;}
                else p.chordEndTime = transition.begin;
            }
        }
        return p;
    }

    void ensurePhrase (long long phrase, const Settings& s)
    {
        const bool initialise=!hasWendung();
        if (phrase == phraseIndex && ! initialise) return;
        const int previous=current;
        // Stillness holds a valid harmony; it must not block selection after a profile change.
        if (! still || initialise) { current = s.custom ? kCustomWendung : pick (s, phrase); chordBase = 0; }
        rememberHarmonicEntry(musicaltime::sixteenth*(phrase * phraseBars * meter.len),previous,s);
        if (s.custom) style = pick (s, phrase);
        phraseIndex = phrase;
        wendungTime = musicaltime::fromGridStep(phrase * phraseBars * meter.len);
    }

    bool metricGroup(const Pos& p)const
    {
        const auto local=p.time-musicaltime::sixteenth*(p.bar*meter.len);
        for(int i=0;i<meter.numGroups;++i)if(local==musicaltime::sixteenth*meter.groupStart[i])return true;
        return false;
    }

    bool isChangePoint (const Pos& p, const Settings& s) const
    {
        const auto local=p.time-musicaltime::sixteenth*(p.bar*meter.len);
        if(s.change==ChangeBeat)
        return metricGroup(p);
        if(local!=musicaltime::Tick{})return false;
        return s.change==ChangeBar||(s.change==Change2Bars?p.barInPhrase%2==0:p.barInPhrase%4==0);
    }

    // Wechsel auf eine neue Wendung, wenn die laufende nicht mehr zur Lage passt (Hysterese ueber kKeepRatio)
    // Ruhezone: ganz unten im Feld (Intensitaet) bleibt der Akkord stehen; gewechselt wird nur auf Wechselpunkten
    bool updateStill (musicaltime::Tick time, const Pos& p, const Settings& s)
    {
        if (current < 0 || ! isChangePoint (p, s)) return false;
        const bool want = still ? s.y < s.policy.texture.stillExit : s.y < s.policy.texture.stillEnter;
        if (want == still) return false;
        still = want;
        if (still) chordBase = p.chordIdx;   // der gerade klingende Akkord bleibt
        wendungTime = time;                    // beim Verlassen laeuft die Folge von diesem Akkord an weiter
        return true;
    }

    bool maybeSwitch (musicaltime::Tick time, const Pos& p, const Settings& s)
    {
        const auto k=p.k;
        if (still || time == p.phraseStartTime || ! isChangePoint (p, s)) return false;
        if (current == kCustomWendung)   // eigene Folge: nur der geliehene Stil wechselt, die Akkorde bleiben
        {
            if (style < 0 || weight (wendungAt (genre, style,lastProfile), s) < std::min (kKeepRatio, keepRatio (s)) * bestWeight (s)) style = pick (s, k * 7 + 3);
            return false;
        }
        if (s.custom) return false;
        if (weight (wendungAt (genre, current,lastProfile), s) >= std::min (kKeepRatio, keepRatio (s)) * bestWeight (s)) return false;
        const int previous=current;
        current = pick (s, k * 7 + 3);
        rememberHarmonicEntry(time,previous,s);
        wendungTime = time;
        return true;
    }

    const Wendung& SW() const { return current == kCustomWendung ? wendungAt (genre, style,lastProfile) : W(); }

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

    bool fieldAccompaniment(const Settings& s)const
    {return s.genre==GenreScore&&s.policy.accompaniment.fieldAndOstinato;}

    int chooseArp (const Settings& s, long long phrase) const
    {
        if (s.arpFigure != ArpAuto) return s.arpFigure;
        // Barry's three-quarter movement is a circling ostinato, not a new meter.
        if(fieldAccompaniment(s)&&s.meterNum==3&&s.meterDen==4&&s.z>=.4f)return ArpCircle;
        return SW().arp[hashInt (31u, phrase) % 2];
    }
    int rawBassPattern (const Settings& s, long long phrase) const
    {
        if (bassOverride >= 0) return bassOverride;   // Einstieg: Bass-Schlag (gehalten) oder Puls
        if (s.bassPattern != BassAuto) return s.bassPattern;
        const float y = layerY (s, kBass);
        if(fieldAccompaniment(s))
        {
            if(y<.3f)return BassHeld;
            // Keep the low register metrically clear; escalation is an eighth-note
            // pitch pendulum, not another simultaneous sixteenth-note motor.
            if(y>=.6f&&s.z>=.95f)return BassPendulum;
            if(y>=.55f&&y<=.8f&&s.z>=.5f)return BassQuarter;
        }
        if (y < 0.15f) return BassHeld;                       // ganz duenn: lange Toene
        if (y > 0.92f) return BassEighth;                     // ganz dicht: Achtel nageln
        int pref = SW().bass[hashInt (47u, phrase) % 2];
        if (y < 0.3f && pref != BassHeld && pref != BassPedal) pref = BassHalf;   // ausduennen
        if (y > 0.8f && (pref == BassHeld || pref == BassHalf || pref == BassQuarter || pref == BassPedal)) return BassEighth;
        return pref;
    }
    bool melodicBassAllowed(const Settings& s)const
    {
        if(s.genre!=GenrePopRock||!on[kBass]||s.scene||s.sceneBars>0||manualEndTime||!s.policy.bass.enabled||!s.follow[kBass]||s.bassPattern!=BassAuto||bassOverride>=0||s.passing||still||s.meterNum!=4||s.meterDen!=4)return false;
        for(int o=0;o<kNumOutputs;++o)if(o!=OutBassShort&&s.channel[o]==s.channel[OutBassShort])return false;
        return true;
    }
    int chooseBass(const Settings& s,long long phrase)const
    {return melodicBassAllowed(s)&&bassPhrase.valid&&nowTime>=bassPhrase.begin&&nowTime<bassPhrase.end?BassFunk:rawBassPattern(s,phrase);}
    void prepareBassPhrase(const Pos& p,const Settings& s)
    {
        if(!melodicBassAllowed(s)){bassPhrase.valid=false;bassPairStart.reset();return;}
        const auto& w=W();const int first=(p.chordIdx/2)*2;
        if(first+1>=w.n||wendungTime>p.phraseStartTime){bassPhrase.valid=false;bassPairStart.reset();return;}
        auto begin=p.phraseStartTime;for(int i=0;i<first;++i)begin+=musicaltime::fromGridStep(static_cast<int64_t>(w.ch[i].bars)*meter.len);
        auto signature=static_cast<uint64_t>(current+2)*1000003u+static_cast<unsigned>(s.key+12*s.octave[kBass]+32)
            +static_cast<uint64_t>(s.rangeOn[kBass]?s.rangeLo[kBass]+256*s.rangeHi[kBass]+1:0)*65537u;
        for(int value:{s.policy.bass.opportunityEvery,s.policy.bass.maxLeap,static_cast<int>(s.policy.passing.mode),s.policy.passing.tonicOffset}){signature^=static_cast<uint32_t>(value);signature*=1099511628211ull;}
        for(int i=0;i<w.n;++i)for(int value:{w.ch[i].root,w.ch[i].type,w.ch[i].bass,w.ch[i].bars}){signature^=static_cast<uint32_t>(value);signature*=1099511628211ull;}
        if(bassPairStart==begin&&bassPhraseKey==signature)return;
        bassPairStart=begin;bassPhraseKey=signature;bassPhrase={};
        if(rawBassPattern(s,p.phrase)!=BassFunk||(p.phrase+first/2)%s.policy.bass.opportunityEvery!=(s.policy.bass.opportunityEvery>1?1:0))return;
        prepareVoicingPlan(p,s);composition::BassPhraseRequest r;r.begin=begin;r.middle=begin+musicaltime::fromGridStep(static_cast<int64_t>(w.ch[first].bars)*meter.len);
        r.end=r.middle+musicaltime::fromGridStep(static_cast<int64_t>(w.ch[first+1].bars)*meter.len);r.barDuration=musicaltime::fromGridStep(meter.len);r.modal=modalContextFor(s);r.maxLeap=s.policy.bass.maxLeap;
        for(int j=0;j<2;++j){const auto c=w.ch[first+j];r.bass[j]=harmonicPlan.slots[(first+j)*2].bass+12*s.octave[kBass];r.root[j]=(s.key+c.root)%12;for(int n=0;n<kShapes[c.type].n;++n)r.chords[j]|=composition::pitchBit(s.key+c.root+kShapes[c.type].iv[n]);}
        r.range=s.rangeOn[kBass]?composition::Range{s.rangeLo[kBass],s.rangeHi[kBass]}:composition::Range{std::max(0,std::min(r.bass[0],r.bass[1])-7),std::min(127,std::max(r.bass[0],r.bass[1])+12)};
        const auto c=outputCatalog(s)[OutBassShort].track.instrument;r.minDuration=c.minDuration;r.maxDuration=c.maxDuration;
        bassPhrase=composition::planBassPhrase(r);
    }

    bool authoredCells(const Settings& s)const
    {return s.genre==GenreScore&&s.policy.accompaniment.authoredCells;}
    const composition::barry::RhythmSource* authoredRhythm(const Settings& s)const
    {
        if(!authoredCells(s))return nullptr;
        for(int o=0;o<kNumOutputs;++o)
            if((o!=OutArp&&s.channel[o]==s.channel[OutArp])||(o!=OutBassLong&&s.channel[o]==s.channel[OutBassLong])
                ||(o!=OutBassShort&&s.channel[o]==s.channel[OutBassShort]))return nullptr;
        const auto& w=W();int stableBars=8;
        if(!still)for(int i=0;i<w.n;++i)stableBars=std::gcd(stableBars,w.ch[i].bars);
        if(!still&&wendungTime%(musicaltime::sixteenth*meter.len)!=musicaltime::Tick{})stableBars=0;
        auto& c=authoredRhythmCache;
        if(c.entry!=wendungTime||c.scene!=sceneTime||c.harmony!=w.id||c.num!=s.meterNum||c.den!=s.meterDen||c.stableBars!=stableBars)
        {
            c.entry=wendungTime;c.scene=sceneTime;c.harmony=w.id;c.num=s.meterNum;c.den=s.meterDen;c.stableBars=stableBars;
            c.source=composition::barry::chooseRhythm(s.x,s.y,s.z,s.meterNum,s.meterDen,stableBars);
        }
        return c.source;
    }
    composition::RhythmPlan authoredRhythmBar(const Pos& p,const Settings& s,bool bass)const
    {
        if(bass?(s.bassPattern!=BassAuto||bassOverride>=0||bassRest||still):(s.arpFigure!=ArpAuto||s.arpRate!=RateAuto))return {};
        const auto* source=authoredRhythm(s);if(!source)return {};
        auto plan=composition::barry::planBar(*source,bass,p.bar-floorDiv((source->staticHarmony?wendungTime:sceneTime).value,(musicaltime::sixteenth*meter.len).value));
        // Chase has no authored cell before this scene/current harmonic entry.
        // Keep ownership of its part, but never invent a negative cell ordinal.
        if(p.time<std::max(sceneTime,source->staticHarmony?wendungTime:sceneTime)){plan.count=0;return plan;}
        const auto catalog=outputCatalog(s);
        for(int i=0;i<plan.count;++i)
        {
            auto& n=plan.notes[i];const auto at=musicaltime::sixteenth*(p.bar*meter.len)+n.at;
            n.length=std::min(n.length,locate(at).chordEndTime-at);
            const int output=bass?(n.length>4*musicaltime::sixteenth?OutBassLong:OutBassShort):OutArp;
            const auto& track=catalog[output].track;composition::RoleNeed need;need.role=composition::MusicalRole::accompaniment;
            need.style=track.style;need.range=track.instrument.range;need.minDuration=need.maxDuration=n.length;
            if(!composition::suitable(track,need))return {};
        }
        return plan;
    }

    composition::RhythmPlan movementRhythm(const Pos& p,const Settings& s)const
    {
        if(authoredCells(s))return authoredRhythmBar(p,s,false);
        // Explicitly protect manual patterns, thematic contexts, scene density and shared routing.
        if(s.genre!=GenrePopRock||!s.policy.rhythm.enabled||s.bassPattern!=BassAuto||s.arpFigure!=ArpAuto
            ||s.arpRate!=RateAuto||!on[kBass]||!on[kArp]||s.scene||s.sceneBars>0||manualEndTime.has_value()||s.endRequested
            ||still||bassRest||bassOverride>=0||dens<1.f||s.meterNum!=4||s.meterDen!=4||s.passing
            ||(on[kMelodie]&&!popMelodicRoles(s))||(on[kGegenstimme]&&phrasedHook(s)))return {};
        for(int o=0;o<kNumOutputs;++o)
            if((o!=OutArp&&s.channel[o]==s.channel[OutArp])
                ||(o!=OutBassShort&&s.channel[o]==s.channel[OutBassShort]))return {};
        const int fig=chooseArp(s,p.phrase);
        if(fig!=ArpUp&&fig!=ArpDown&&fig!=ArpCircle&&fig!=ArpCascade)return {};
        if(composition::autoArpeggioDuration(s.policy.texture,layerY(s,kArp))!=2*musicaltime::sixteenth)return {};
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
        request.minDuration=cap.minDuration;request.maxDuration=cap.maxDuration;
        return composition::planRhythmicInterlock(request,s.policy.rhythm);
    }

    int choosePad (const Settings& s) const
    {
        if (padShy) return PadHeld;                   // Einstieg: ein stehender Ton
        if (s.padPattern != PadAuto) return s.padPattern;
        const float y = layerY (s, kFlaeche);
        if(fieldAccompaniment(s))
        {
            if(y>=.6f&&s.z>=.95f)return PadGated;
            // Notated diminution cells retain their sustained harmonic foundation.
            if(const auto* cell=authoredRhythm(s);cell&&cell->staticHarmony)return PadHeld;
            if(y>=.8f)return s.z>=.6f?PadStaccato:PadPulse;
            if(y>=.55f&&s.z>=.4f)return PadStabs;
            return PadHeld;
        }
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

    double performed(musicaltime::Tick time,execution::Timing timing)const
    {return execution::quarters(time,timing,cur?cur->swing:0.f);}
    void limitClaim(Active& claim,musicaltime::Tick end,execution::Timing timing)
    {if(performed(end,timing)<performed(claim.endTime,claim.timing)){claim.endTime=end;claim.timing=timing;}}
    void releaseAt(double quarter,int offset,EventList& out,bool deferPadBoundary=false)
    {
        for(int i=0;i<numActive;)
        {
            const auto& claim=active[static_cast<size_t>(i)];const double due=performed(claim.endTime,claim.timing);
            if(due<=quarter+1e-12&&!(deferPadBoundary&&claim.out==OutPadLong&&execution::coincides(due,quarter)))removeActive(i,offset,out);
            else ++i;
        }
    }
    execution::Candidate nextRelease()const
    {
        execution::Candidate result;
        for(int i=0;i<numActive;++i){const auto& a=active[static_cast<size_t>(i)];
            result=execution::first(result,{a.endTime,a.timing,execution::Kind::release,true},cur?cur->swing:0.f);}
        return result;
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
            if (keepPad && active[(size_t) i].out == OutPadLong) limitClaim(active[static_cast<size_t>(i)],nowTime,execution::Timing::nominal);
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
    void noteOn (int o, int note, int velocity, musicaltime::Tick endTime, int offset, EventList& out)
    {
        if(chasingPatterns&&!execution::sounding(nowTime,endTime,currentTiming,cur?cur->swing:0.f,currentPerformanceQuarter))return;
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
        // A newly playable Auto articulation replaces the old long patch of the
        // same Barry part. Otherwise a held chord/bass can mask the new rhythm
        // for the rest of an eight-bar field. Manual and other profiles are untouched.
        if(cur&&fieldAccompaniment(*cur)&&((o==OutPadShort&&cur->padPattern==PadAuto)
            ||(o==OutBassShort&&cur->bassPattern==BassAuto)))
        {
            for(int i=0;i<numActive;)
                if(kOutputLayer[active[static_cast<size_t>(i)].out]==layer&&active[static_cast<size_t>(i)].out!=o)
                    removeActive(i,offset,out);
                else ++i;
        }
        int own = -1; bool existing = false, sameStep = false;
        for (int i = 0; i < numActive; ++i)
        {
            const auto& a = active[(size_t) i];
            if (a.channel != channel || a.note != note) continue;
            existing = true; sameStep = sameStep || a.attack == dispatchIdentity;
            if (a.out == o) own = i;
        }
        if (own < 0 && numActive >= kMaxActive) return;
        if (! existing || (! sameStep && ! extendOnly))
        {
            if (existing) out.add (offset, channel, note, 0, o);
            out.add (offset, channel, note, velocity, o);
            // One physical attack for all claims at this time.
            for (int i = 0; i < numActive; ++i)
                if (active[(size_t) i].channel == channel && active[(size_t) i].note == note) active[(size_t) i].attack = dispatchIdentity;
        }
        if (own >= 0)
        {
            auto& a = active[(size_t) own];
            if(!(sameStep||extendOnly)||performed(endTime,currentTiming)>performed(a.endTime,a.timing))
                {a.endTime=endTime;a.timing=currentTiming;}
            a.attack = dispatchIdentity;
        }
        else active[(size_t) numActive++] = { (uint8_t) channel, (uint8_t) note, (uint8_t) o, endTime, currentTiming, dispatchIdentity };
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
    struct HarmonicEntryRecord { musicaltime::Tick begin{};int target=-1;HeardHarmony heard; };
    std::array<HarmonicEntryRecord,64> harmonicEntries {};
    unsigned harmonicEntryNext=0;
    bool harmonicChase=false;
    void clearHarmonicEntries()
    {heardHarmony={};harmonicEntries={};harmonicEntryNext=0;}
    void rememberHarmonicEntry(musicaltime::Tick begin,int previous,const Settings& s)
    {
        if(harmonicChase||s.genre!=GenreScore||s.custom||previous<0||previous==current)return;
        for(const auto& entry:harmonicEntries)if(entry.begin==begin&&entry.target==current)return;
        harmonicEntries[harmonicEntryNext++%harmonicEntries.size()]={begin,current,heardHarmony};
        planValid=false;
    }
    const HarmonicEntryRecord* harmonicEntryAt(const Pos& p,const Settings& s)const
    {
        if(s.genre!=GenreScore||s.custom)return nullptr;
        const auto begin=std::max(p.phraseStartTime,wendungTime);
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
        if(entry){
            // This cache key retains the historical event ordinal, not a second stored clock.
            const auto eventIndex=floorDiv(entry->begin.value,musicaltime::sixteenth.value);
            mix(static_cast<int>(eventIndex));mix(static_cast<int>(eventIndex>>32));
            mix(entry->heard.pad.n);for(int i=0;i<entry->heard.pad.n;++i)mix(entry->heard.pad.notes[i]);
            mix(entry->heard.bass);mix(entry->heard.root);mix(entry->heard.type);}

        const auto& w = W(); auto start = std::max(p.phraseStartTime,wendungTime);
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
                intent.voicing=current==kCustomWendung?hashInt(91u,floorDiv(start.value,musicaltime::sixteenth.value))%3:0;
                intent.padLow=padLow(s);intent.bassLow=bassLow(s);intent.intensity=layerY(s,kFlaeche);
                slot=composition::buildAnchor(intent,{lo,hi},rangeOn(o));
                mix(slot.pad.n);for(int n=0;n<slot.pad.n;++n)mix(slot.pad.notes[n]);
                mix(slot.bass);mix(static_cast<int>(slot.unavailable));
                slot.enabled = ! pass || (composition::freeTransition(0,allowsPassingHarmony(s),s.y,still).kind==composition::TransitionKind::passingDominant);
                slot.preservePad = s.genre == GenrePopRock && W().id == WendungId::popDrahtseil && ! s.custom;
                mix(slot.preservePad);
                if (slot.enabled) order[count++] = index;
            }
            if (i >= chordBase) start += musicaltime::fromGridStep(static_cast<int64_t>(w.ch[i].bars)*meter.len);
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
        dispositionAt=nowTime;
        const int index = p.chordIdx * 2 + (p.passing ? 1 : 0);
        unavailablePad = harmonicPlan.slots[static_cast<size_t> (index)].unavailable;
        const auto original=entryVoicingValid&&index==chordBase*2?entryVoicing.pad:harmonicPlan.slots[static_cast<size_t> (index)].pad;
        lastDisposition={};lastDisposition.notes=original;
        if(s.genre!=GenrePopRock||!s.policy.chords.enabled||s.padPattern!=PadAuto||!on[kFlaeche]||s.scene||s.sceneBars>0
            ||manualEndTime.has_value()||s.endRequested||s.passing||still||padShy||peak||padGrow||W().id==WendungId::popDrahtseil)return original;
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

    void padChord (const Pos& p, const Settings& s, int o, int offset, musicaltime::Tick endTime, int velocity, EventList& out)
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
            noteOn (o, voiced.notes[i], velocity - reduction, endTime, offset, out);
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
        noteOn (OutTupfer, place (s.key + c.root + iv, tupferLow (s)), (int) (45 + 40 * ya) + boost, p.time + musicaltime::sixteenth*len, offset, out);
    }

    // Unruhe: ein fremder, reibender Ton als kurzer Stachel in der Mitte des Akkords
    void foreignTone (const Pos& p, const Settings& s, int offset, EventList& out)
    {
        const Chord c = chordFor (p, kAkzent, s);
        const int interval = s.x < 0.5f ? 1 : 6;                          // dunkel: kleine None, hell: uebermaessige Quarte
        const int note = place (s.key + c.root + interval, 79);
        if(protectedColoration())return; // No resolution is planned for this foreign-tone accent.
        noteOn (OutTupfer, note, (int) (30 + 45 * s.z), p.time + musicaltime::sixteenth*3, offset, out);
        if (s.z >= 0.8f && layerY (s, kAkzent) < 0.5f)                    // Halbton-Reibung ganz oben
            noteOn (OutTupfer, note + 11, (int) (25 + 30 * s.z), p.time + musicaltime::sixteenth*3, offset, out);
    }

    // Stich: ein einzelner Schlag. Fest: die gewaehlte Taste. Akkord: der Grundton (MIDI 50 bis 61, unter der Gegenstimme).
    static int stichTone (const Settings& s, int pitch) { return composition::addressedPitch(outputCatalog(s)[OutStich], place(pitch,stichLow(s))); }
    void stich (const Pos& p, const Settings& s, int offset, long long len, int boost, EventList& out)
    {
        const Chord c = chordFor (p, kAkzent, s);
        const float ya = layerY (s, kAkzent);
        noteOn (OutStich, stichTone (s, s.key + bassRoot (c)), (int) (68 + 40 * ya) + boost, p.time + musicaltime::sixteenth*len, offset, out);
    }

    // Riss (ab 1.4): ganz oben in der Unruhe kurze, harte Stoesse aus zwei Toenen im Halbtonabstand hoch ueber dem Satz,
    // auf dem Kanal der kurzen Flaeche (Staccato-Streicher), wie die Streicher in Herrmanns "Psycho". Er waechst mit der
    // Unruhe: bei 80 % selten und leiser, bei 100 % haeufig, laut und doppelt; ganz oben kommt ein dritter Reibungston dazu.
    void riss (musicaltime::Tick time, const Pos& p, const Settings& s, int offset, EventList& out)
    {
        const auto k=p.k;
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
        noteOn (OutPadShort, t, v, time + musicaltime::sixteenth, offset, out);
        noteOn (OutPadShort, t + 1, v, time + musicaltime::sixteenth, offset, out);
        if (r >= 0.75f) noteOn (OutPadShort, t + 13, v - 8, time + musicaltime::sixteenth, offset, out);
    }

    // Preserve the existing accent vocabulary's quantised middle symbol.
    static musicaltime::Tick accentMiddle(const Pos& p)
    {return p.chordStartTime+musicaltime::sixteenth*((p.chordEndTime-p.chordStartTime)/(2*musicaltime::sixteenth));}

    void accents (musicaltime::Tick time, const Pos& p, const Settings& s, int offset, EventList& out)
    {
        const auto k=p.k;const bool symbol=time%musicaltime::sixteenth==musicaltime::Tick{};
        if (prepStich && muteSoloOk (s, kAkzent))   // Vorbereiten: ein Stich kuendigt den Wechsel an
        {
            forceOn = true; stich (p, s, offset, 2, 10, out); forceOn = false;
            return;
        }
        if (! on[kAkzent]) return;
        if (akzentForced && entryTime[kAkzent] && time == *entryTime[kAkzent])   // Einstieg mit dem Akzent: ein Stich (hart) oder Tupfer (weich) in der Stille
        {
            if (cur->hardness >= 0.5f) stich (p, s, offset, 2, 8, out); else tupfer (p, s, offset, 2, 6, out);
            return;
        }
        const float ya = layerY (s, kAkzent);
        const bool lastBar = p.barInPhrase == phraseBars - 1;
        const int lastGroup = meter.groupStart[std::max (0, meter.numGroups - 1)];
        const bool phraseEnd = lastBar && time==musicaltime::sixteenth*(p.bar*meter.len+lastGroup) && lastGroup > 0;    // Schlusspunkt der Phrase
        const bool both = phraseEnd && ya >= 0.8f;

        if (s.z >= s.policy.texture.accentUnrest && time == accentMiddle(p))
            foreignTone (p, s, offset, out);
        else if (both || (symbol&&tupferAt (k, s)))
            tupfer (p, s, offset, ya > 0.7f ? 1 : 2, both ? 10 : 0, out);

        if (ya < s.policy.texture.stichStart) return;
        bool hit = both || (phraseEnd && ya >= 0.6f);
        if (! hit && time == p.chordStartTime)
            hit = (float) (hashInt (613u, k) % 1000) < (0.25f + 0.45f * ya) * 1000.0f;
        if (! hit && symbol && ya >= 0.55f && tupferAt (k - 3, s))                       // Antwort auf den Tupfer
            hit = hashInt (617u, k) % 2 == 0;
        if (! hit && symbol && s.genre == GenrePopRock && p.pos % 8 == 6)                 // Pop-Rock: Stab auf der Zwischenzeit
            hit = (float) (hashInt (619u, k) % 1000) < (0.05f + 0.2f * ya) * 1000.0f;
        if (hit) stich (p, s, offset, s.genre == GenrePopRock ? 1 : 2, phraseEnd ? 8 : 0, out);
    }

    // Liegetoene einer Akkordposition (Flaeche gehalten, Bass gehalten)
    void sustained (const Pos& p, const Settings& s, int offset, EventList& out, bool restart, unsigned mask = 3u)
    {
        const int pad = choosePad (s);
        const bool padFollow = s.follow[kFlaeche];
        const bool phraseStart = p.time == p.phraseStartTime;
        if ((mask & 1u) && pad == PadHeld && (padFollow || phraseStart || restart))
            padChord (p, s, OutPadLong, offset, padFollow ? p.chordEndTime : p.phraseEndTime, (int) (40 + 45 * layerY (s, kFlaeche)), out);

        const int bp = chooseBass (s, p.phrase);
        if (!authoredRhythmBar(p,s,true).active && (mask & 2u) && ((bp == BassHeld && (s.follow[kBass] || phraseStart || restart)) || bp == BassPedal))
        {
            const bool pedal = bp == BassPedal;
            noteOn (OutBassLong, bassPlacement (p, s, place (s.key + (pedal ? pedalRoot() : bassRoot (chordFor (p, kBass, s))), bassLow (s)), pedal),
                    (int) (60 + 35 * layerY (s, kBass)), (s.follow[kBass] && ! pedal) ? p.chordEndTime : (pedal ? p.chordEndTime : p.phraseEndTime), offset, out);
        }
    }

    musicaltime::Tick arpeggioPeriod(const Settings& s,long long phrase)const
    {
        const int figure=chooseArp(s,phrase);
        if(fieldAccompaniment(s)&&s.arpFigure==ArpAuto&&s.arpRate==RateAuto)
        {
            auto fastest=s.policy.accompaniment.fastestArp;
            if(layerY(s,kArp)<.65f||s.z<.6f)fastest=std::max(fastest,2*musicaltime::sixteenth);
            return std::max(fastest,composition::autoArpeggioDuration(s.policy.texture,layerY(s,kArp)));
        }
        if(figure==ArpGlitter||figure==ArpSid)return musicaltime::sixteenth;
        return s.arpRate==RateQuarter?musicaltime::quarter:s.arpRate==RateEighth?2*musicaltime::sixteenth:
            s.arpRate==RateSixteenth?musicaltime::sixteenth:composition::autoArpeggioDuration(s.policy.texture,layerY(s,kArp));
    }

    // Each stock template owns its musical slots. Searching this bounded symbol set
    // does not advance the generator clock, harmony, memory or random state.
    bool templateOnset(const Pos& p,const Settings& s)
    {
        if(p.time%musicaltime::sixteenth!=musicaltime::Tick{})return false;
        const int slot=p.pos;const auto k=p.k;
        if(s.dynamics)return true; // Existing expression curve sampling, not a note scheduler.
        const int pad=choosePad(s);
        if(on[kFlaeche]&&((pad==PadStabs&&slot%4==2)||((pad==PadPulse||pad==PadStaccato)&&slot%4==0)||(pad==PadGated&&slot%2==0)))return true;
        if(on[kBass])
        {
            const auto authored=authoredRhythmBar(p,s,true);if(authored.active&&authored.at(p.time-musicaltime::sixteenth*(p.bar*meter.len)))return true;
            const int bass=chooseBass(s,p.phrase);const bool approach=s.follow[kBass]&&(s.z>=.3f||bass==BassFunk)&&p.time==p.chordEndTime-2*musicaltime::sixteenth;
            switch(bass)
            {
                case BassPulse:return true;
                case kPulseTick:case BassWalking:if(slot%4==0)return true;break;
                case BassHalf:if(slot%8==0||approach)return true;break;
                case BassQuarter:case BassAlternating:if(slot%4==0||approach)return true;break;
                case BassEighth:case BassArpeggio:if(slot%2==0)return true;break;
                case BassFunk:if(composition::funkBassAttack(slot,approach).active)return true;break;
                case BassPendulum:if(slot%(layerY(s,kBass)>.6f?2:4)==0)return true;break;
                case BassPedal:if(layerY(s,kBass)>.6f&&slot%4==0)return true;break;
                case BassHiNrg:if(slot%(layerY(s,kBass)>.75f?1:2)==0)return true;break;
                case BassGallop:if(slot%4!=1)return true;break;
                case BassHeartbeat:if(slot%8==0||slot%8==2)return true;break;
                default:break;
            }
        }
        if(on[kArp])
        {
            const auto rhythm=movementRhythm(p,s);
            const auto local=p.time-musicaltime::sixteenth*(p.bar*meter.len);
            if(rhythm.active){if(rhythm.at(local))return true;}
            else
            {
                const auto rate=arpeggioPeriod(s,p.phrase);
                if((p.time-(s.follow[kArp]?p.chordStartTime:p.phraseStartTime))%rate==musicaltime::Tick{})return true;
            }
        }
        if(on[kAkzent]||prepStich||akzentForced)
        {
            // All candidates of the stateless accent vocabulary. Probability and pitch
            // are evaluated only by the existing renderer, with their original keys.
            if(tupferAt(k,s)||tupferAt(k-3,s)||p.time==p.chordStartTime||
                p.time==accentMiddle(p)||
                (p.barInPhrase==phraseBars-1&&slot==meter.groupStart[meter.numGroups-1])||
                (s.genre==GenrePopRock&&slot%8==6)||prepStich||
                (entryTime[kAkzent]&&p.time==*entryTime[kAkzent]))return true;
        }
        if(on[kFlaeche]&&!protectedColoration()&&s.z>=kRissStart)
        {
            const int half=std::max(2,meter.len/2);const auto window=floorDiv(k,half);
            const int in=static_cast<int>(k-window*half),target=2*(hashInt(701u,window)%std::max(1,half/2));
            if(in==target||(s.z>=.9f&&in==target+1))return true;
        }
        if(on[kGegenstimme]&&(!on[kMelodie]||popMelodicRoles(s))&&s.genre==GenrePopRock&&
            !(phrasedHook(s)&&voice(OutCounter).motif.material(motifCatalog).complete&&(!popMelodicRoles(s)||s.motif)))
        {
            const bool special=popHookPattern(W().id)>=0&&!s.custom;
            const auto cycle=musicaltime::sixteenth*(special?2LL*meter.len:8LL*(layerY(s,kGegenstimme)<.45f?4:2));
            if((p.time-p.phraseStartTime)%cycle==musicaltime::Tick{}||hookNote(p.time,p,s).valid)return true;
        }
        return false;
    }

    musicaltime::Tick nextOnset(musicaltime::Tick at,const Settings& s)
    {
        const auto p=locate(at);auto best=p.phraseEndTime;
        auto consider=[&](musicaltime::Tick time){if(time>=at&&time<best)best=time;};
        // Bounded template lookup within this bar; a bar boundary refreshes the context.
        const auto end=musicaltime::sixteenth*((p.bar+1)*meter.len);
        consider(end); // next bar refreshes a template even while its swung start is pending
        for(auto cell=execution::atOrAfter(at,musicaltime::sixteenth);cell<end;cell+=musicaltime::sixteenth)
            if(templateOnset(locate(cell),s)){consider(cell);break;}
        if(on[kBass]&&bassPhrase.valid)for(int i=0;i<bassPhrase.count;++i)consider(bassPhrase.notes[i].at);
        const auto rhythm=movementRhythm(p,s);
        if(on[kArp])
        {
            if(rhythm.active)for(int i=0;i<rhythm.count;++i)consider(musicaltime::sixteenth*(p.bar*meter.len)+rhythm.notes[i].at);
            else
            {
                const auto anchor=s.follow[kArp]?p.chordStartTime:p.phraseStartTime;
                consider(anchor+execution::atOrAfter(at-anchor,arpeggioPeriod(s,p.phrase)));
            }
        }
        if(on[kAkzent]){consider(p.chordStartTime);if(s.z>=s.policy.texture.accentUnrest)consider(accentMiddle(p));if(entryTime[kAkzent])consider(*entryTime[kAkzent]);}
        const int bass=chooseBass(s,p.phrase);
        if(on[kBass]&&s.follow[kBass]&&(s.z>=.3f||bass==BassFunk)&&
            (bass==BassHalf||bass==BassQuarter||bass==BassAlternating||bass==BassFunk))consider(p.chordEndTime-2*musicaltime::sixteenth);
        const auto leadWindow=melodicRoleWindow(OutMelody,p,s);
        if(leadWindow.owner.value>=0){consider(leadWindow.begin);consider(leadWindow.end);}
        for(int output:{OutMelody,OutCounter})
        if(on[kOutputLayer[output]]&&(output!=OutCounter||dialogueMayLead(p,s)))
        {
            auto memory=performanceMaterial(output,s);
            const auto span=std::min(2*musicaltime::sixteenth*meter.len,p.phraseEndTime-p.phraseStartTime);
            const bool introduction=at>=p.phraseStartTime&&at<p.phraseStartTime+span;
            // Match motifStep's existing fall-through: without completed material,
            // time outside the introduction belongs to the local line, not recurrence.
            if((s.genre==GenreScore||(popMelodicRoles(s)&&output==OutMelody))&&memory.count&&(!introduction||p.phrase-phraseOf(sceneTime)!=voice(output).motif.introduction))memory.finish();
            const bool motivic=(s.genre==GenreScore||(popMelodicRoles(s)&&output==OutMelody))?(output==OutMelody?s.melodyMotif:s.motif)&&(memory.complete||introduction):
                phrasedHook(s)&&memory.complete&&(!popMelodicRoles(s)||s.motif);
            if(motivic)
            {
                const auto occurrence=motifOccurrence(at,p,s,output,true);
                // A locally finished preview must still dispatch the existing
                // publication deadline for the real per-voice introduction.
                if(!voice(output).motif.material(motifCatalog).complete)consider(p.phraseStartTime+span);
                if(occurrence.active)
                {
                    consider(occurrence.begin);consider(occurrence.end);
                    for(int i=0;i<(occurrence.figure.count?occurrence.figure.count:memory.complete?memory.count:initialMotifSlots(s));++i)
                    {
                        auto local=p;local.phraseStartTime=occurrence.begin;local.phraseEndTime=occurrence.end;
                        const auto n=planMotifNote(i,local,s,output,memory.complete?&memory:nullptr,occurrence.varied,&occurrence);
                        if(n.valid)consider(occurrence.begin+n.at);
                    }
                }
                // Recurrence epochs are planning windows, not a playback subdivision.
                const auto window=musicaltime::sixteenth*meter.len*s.policy.motif.windowBars;
                const auto origin=voice(output).motif.originTime;
                const auto epoch=std::max<int64_t>(0,(at-origin)/window);
                consider(origin+window*epoch); // materialise the epoch even when its result is silence
                consider(origin+window*(epoch+1));
                if(!on[kMelodie]&&s.genre==GenreScore&&s.arpFigure==ArpCell)
                {
                    const auto plan=composition::planDialogue(voice(output).motif,motifCatalog,occurrence,at,2*musicaltime::sixteenth*meter.len);
                    if(plan.reserveResponse){consider(plan.answerBegin);for(int i=0;i<plan.answerNotes;++i)consider(plan.answerBegin+memory.notes[i].at);}
                }
            }
            else if(s.genre==GenreScore||(popMelodicRoles(s)&&output==OutMelody))
            {
                const auto plan=output==OutCounter?freeLinePhrase(p,s):composition::LinePhrasePlan{};
                if(plan.valid){for(int i=0;i<plan.count;++i)consider(plan.notes[i].begin);consider(plan.breath);}
                else
                {
                    consider(p.chordStartTime);
                    const auto y=layerY(s,kOutputLayer[output]);
                    const auto rate=musicaltime::sixteenth*(y<.4f?0:y<.7f?2LL*meter.len:std::max(4LL,static_cast<long long>(meter.len)/2));
                    if(rate>musicaltime::Tick{})consider(p.chordStartTime+execution::atOrAfter(at-p.chordStartTime,rate));
                }
            }
            if(voice(output).pendingAt)consider(*voice(output).pendingAt);
        }
        if(on[kMelodie])
        {
            const auto response=playableMelodyHandoff(at,p,s,true);
            if(response.plan.active)
            {
                const auto& material=*motifCatalog.find(response.plan.reference.material);
                const auto first=material.notes[response.plan.first].at;
                for(int i=0;i<response.plan.count;++i)consider(response.origin+response.plan.begin+material.notes[response.plan.first+i].at-first);
                consider(response.origin+response.plan.end);
            }
        }
        return best;
    }

    void beginDispatch(double quarter)
    {if(!execution::coincides(quarter,currentPerformanceQuarter))++dispatchIdentity;currentPerformanceQuarter=quarter;}
    // Harmonic/metric/scene boundaries are queried from musical time, not inferred from
    // the next rhythmic pulse. In particular odd-meter boundaries remain unswung.
    musicaltime::Tick nextBoundary(musicaltime::Tick at,const Settings&)const
    {
        const auto p=locate(at);const auto bar=musicaltime::fromGridStep(meter.len);
        auto best=p.phraseEndTime;
        auto consider=[&](musicaltime::Tick time){if(time>=at&&time<best)best=time;};
        consider(p.chordStartTime);consider(p.chordEndTime);consider(p.phraseStartTime);
        const auto barBegin=bar*floorDiv(at.value,bar.value);
        consider(barBegin);consider(barBegin+bar);
        consider(barBegin+musicaltime::sixteenth*(meter.len/2));
        for(int i=0;i<meter.numGroups;++i)consider(barBegin+musicaltime::fromGridStep(meter.groupStart[i]));
        if(sceneEndTime)consider(*sceneEndTime);if(manualEndTime)consider(*manualEndTime);
        return best;
    }
    void renderRhythmAt(musicaltime::Tick time,int offset,const Settings& s,EventList& out)
    {
        const auto p=locate(time);nowTime=time;
        if(yAdd>.001f){auto raised=s;raised.y=std::clamp(s.y+yAdd,0.f,1.f);const auto* saved=cur;cur=&raised;
            render(time,offset,p,false,p.phrase,raised,out,false);cur=saved;}
        else render(time,offset,p,false,p.phrase,s,out,false);
    }

    void chase (double ppq, const Settings& s, EventList& out)
    {
        if (ppq < 0.0) return;
        const auto actual=execution::floorTime(ppq);
        ensurePhrase(phraseOf(actual),s);
        const Pos structural=locate(actual);
        const auto source=execution::nominalAt(ppq,execution::Timing::groove,s.swing);
        const Pos p=locate(source);nowTime=actual;
        curChord = structural.chordIdx;
        curRoot = W().ch[structural.chordIdx].root; curType = W().ch[structural.chordIdx].type;
        updateMask (s);
        updateScene (actual, structural, s, true, 0, out);
        if (sceneEnded) return;
        prepareBassPhrase(p,s);
        if (ppq > musicaltime::toQuarters(structural.chordStartTime) + 1e-9)
            sustained (structural, s, 0, out, true);
        else
            restartAt = actual;   // genau am Akkordanfang: der normale Schritt schlaegt an, auch die stehenden Ebenen
        currentTiming=execution::Timing::groove;nowTime=source;
        // Reconstruct the stock accompaniment from the very same onset predicates and
        // emitters. This bounded lookback covers their maximum gate/cycle, not scene replay.
        const auto horizon=std::max(2*musicaltime::sixteenth*meter.len,8*musicaltime::quarter);
        const auto begin=std::max(p.phraseStartTime,source-horizon);
        chasingPatterns=true;
        for(auto at=nextOnset(begin,s);at<=source;at=nextOnset(at+musicaltime::Tick{1},s))
        {
            const auto position=locate(at);nowTime=at;
            if(execution::quarters(at,currentTiming,s.swing)<ppq-1e-9)
                render(at,0,position,false,position.phrase,s,out,false,true);
        }
        chasingPatterns=false;nowTime=source;
        if(on[kBass]&&bassPhrase.valid)
            for(int i=0;i<bassPhrase.count;++i){const auto& note=bassPhrase.notes[i];if(execution::sounding(note.at,note.at+note.length,currentTiming,s.swing,ppq))
                {const auto eventIndex=floorDiv(note.at.value,musicaltime::sixteenth.value);const int position=static_cast<int>(eventIndex%meter.len);const int velocity=static_cast<int>(58+38*layerY(s,kBass))+(meter.isGroupStart(position)?8:0)+jitter(eventIndex,kBass,3)+note.accent;
                 noteOn(OutBassShort,note.pitch-12*s.octave[kBass],velocity,note.at+note.length,0,out);}}
        if(on[kGegenstimme]&&(!on[kMelodie]||popMelodicRoles(s))&&s.genre==GenrePopRock&&
            !(phrasedHook(s)&&voice(OutCounter).motif.material(motifCatalog).complete&&(!popMelodicRoles(s)||s.motif)))
        {
            // At most the last hook note and its actual legato overlap are sounding.
            PlannedMotifNote last,previous;
            for(auto at=execution::atOrAfter(begin,musicaltime::sixteenth);at<=source;at+=musicaltime::sixteenth)
            {
                const auto n=hookNote(at,locate(at),s);
                if(n.valid&&(!popMelodicRoles(s)||popDialogueMayLead(locate(at),s))&&execution::quarters(at,currentTiming,s.swing)<ppq-1e-9){previous=last;last=n;}
            }
            if(popMelodicRoles(s)&&popDialogRoute(s)&&voice(OutCounter).motif.material(motifCatalog).complete)
                for(auto* n:{&last,&previous})if(n->valid)n->length=std::min(n->length,popDialogTurn(locate(n->at),s).end-n->at);
            const bool releases=(popHookPattern(W().id)>=0&&!s.custom)||s.legato;
            // A real attack exactly at the seek destination owns its articulation and
            // velocity. Do not pre-empt it with an overlapping chase of the same key.
            const auto upcoming=hookNote(source,p,s);
            auto replaced=[&](const PlannedMotifNote& n)
            {return upcoming.valid&&execution::coincides(execution::quarters(source,currentTiming,s.swing),ppq)
                &&sounding(OutCounter,n.pitch)==sounding(OutCounter,upcoming.pitch);};
            if(previous.valid&&last.valid&&releases)
            {
                const auto end=std::min(previous.at+previous.length,last.at+(s.legato?musicaltime::sixteenth:musicaltime::Tick{}));
                if(!replaced(previous)&&execution::sounding(previous.at,end,currentTiming,s.swing,ppq))noteOn(OutCounter,previous.pitch,previous.velocity,end,0,out);
            }
            if(last.valid&&!replaced(last)&&execution::sounding(last.at,last.at+last.length,currentTiming,s.swing,ppq))
            {noteOn(OutCounter,last.pitch,last.velocity,last.at+last.length,0,out);voice(OutCounter).note=last.pitch;}
        }
        freePhraseStep(source,p,s,0,out,true);
        chaseMotif(source,p,s,out);
        const int lineOutput=on[kMelodie]&&!dialogueMayLead(p,s)?OutMelody:OutCounter;
        if((s.genre==GenreScore||(popMelodicRoles(s)&&lineOutput==OutMelody))&&on[kOutputLayer[lineOutput]]&&
            !(lineOutput==OutMelody?s.melodyMotif:s.motif)&&(lineOutput!=OutCounter||!freeLinePhrase(p,s).valid))
        {
            const auto y=layerY(s,kOutputLayer[lineOutput]);
            const auto rate=musicaltime::sixteenth*(y<.4f?0:y<.7f?2LL*meter.len:std::max(4LL,static_cast<long long>(meter.len)/2));
            auto at=p.chordStartTime;
            if(rate>musicaltime::Tick{}&&source>at)at+=rate*((source-at)/rate);
            if(at!=p.chordStartTime&&p.chordEndTime-at<musicaltime::quarter)at-=rate;
            chasingPatterns=true;nowTime=at;
            counterLine(at,locate(at),s,0,at==p.chordStartTime,out,lineOutput);
            if(voice(lineOutput).pendingAt&&*voice(lineOutput).pendingAt<=source)
            {const auto resolve=*voice(lineOutput).pendingAt;nowTime=resolve;counterLine(resolve,locate(resolve),s,0,false,out,lineOutput);}
            chasingPatterns=false;
        }
        nowTime=source;curChord=structural.chordIdx;curRoot=W().ch[curChord].root;curType=W().ch[curChord].type;updateMask(s);
        if(s.dynamics)dynamicsCc(source,p,s,0,out);
    }

    void prepareAt (musicaltime::Tick time, int offset, const Settings& s, EventList& out)
    {
        nowTime=time;const long long phrase = phraseOf (time);
        ensurePhrase (phrase, s);
        Pos p = locate(time);
        bool restart = restartAt&&time==*restartAt;
        if (updateStill (time, p, s))
        {
            releaseHeld (offset, out, true);  // Flaeche wird zielharmonisch abgeglichen; andere gehaltene Toene neu setzen, auf demselben Akkord
            p = locate(time);
            restart = true;
        }
        if (maybeSwitch (time, p, s))
        {
            releaseHeld (offset, out, true);  // gemeinsame Flaechentoene am Stimmungswechsel halten
            p = locate(time);
            restart = true;
        }
        restartAt.reset();
        updateScene (time, p, s, false, offset, out);
        if (sceneEnded)
        {
            if (sceneEndTime && time==*sceneEndTime && (!manualEndTime || !manualHitSent))
            {
                if(manualEndTime.has_value())manualHitSent=true;
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
            render (time, offset, p, restart, phrase, sb, out, true);
            cur = saved;
        }
        else render (time, offset, p, restart, phrase, s, out, true);
    }

    void chaseMotif(musicaltime::Tick time,const Pos& p,const Settings& s,EventList& out)
    {

        if(s.genre!=GenreScore&&!phrasedHook(s)&&!popMelodicRoles(s))return;
        for(int output:{OutMelody,OutCounter})
        {
        if(popMelodicRoles(s)&&output==OutCounter&&(!s.motif||!phrasedHook(s)))continue;
        if(output==OutCounter&&!dialogueMayLead(p,s))continue;
        const auto memory=performanceMaterial(output,s);
        if(on[kOutputLayer[output]]&&(output!=OutMelody||!popMelodicRoles(s)||popLeadWindow(p,s).contains(time))
            &&(s.genre==GenrePopRock&&(!popMelodicRoles(s)||(output==OutCounter&&s.motif&&phrasedHook(s)))||(output==OutMelody?s.melodyMotif:s.motif))&&memory.complete)
        {
            const auto occurrence=motifOccurrence(time,p,s,output);
            if(occurrence.active&&time>=occurrence.begin&&time<occurrence.end)
            {
                auto local=p;local.phraseStartTime = occurrence.begin;local.phraseEndTime = occurrence.end;
                for(int i=0;i<(occurrence.figure.count?occurrence.figure.count:memory.count);++i)
                {
                    const auto n=planMotifNote(i,local,s,output,&memory,occurrence.varied,&occurrence);
                    const auto begin=occurrence.begin+n.at,end=begin+n.length;
                    if(n.valid&&execution::sounding(begin,end,execution::Timing::groove,s.swing,currentPerformanceQuarter))
                    {const bool saved=forceOn;if(s.genre==GenrePopRock)forceOn=true;noteOn(output,n.pitch,n.velocity,end,0,out);forceOn=saved;voice(output).note=n.pitch;}
                }
            }
        }
        }
        if(on[kMelodie])melodyHandoff(time,p,s,0,out,true);
        else if(on[kArp])dialogueArp(time,p,s,0,out,true);
    }

    PlayableHandoff playableMelodyHandoff(musicaltime::Tick time,const Pos& p,const Settings& s,bool preview=false)
    {
        if(popMelodicRoles(s))return {};

        const auto catalog=outputCatalog(s);
        const auto& source=voice(OutMelody).motif;
        const auto window=musicaltime::fromGridStep(meter.len)*s.policy.motif.windowBars;
        const auto epoch=time>=source.originTime?(time-source.originTime)/window:-1;
        const auto origin=source.originTime+epoch*window;
        const auto leading=motifOccurrence(time,p,s,OutMelody,preview);
        const auto plan=composition::planMelodyHandoff(
            s.genre==GenreScore&&s.melody&&s.melodyMotif&&s.motif&&!s.scene
                &&s.meterNum==4&&s.meterDen==4&&on[kMelodie]&&on[kGegenstimme]&&phraseBars>=4,
            source,motifCatalog,catalog[OutCounter].track,epoch,musicaltime::fromGridStep(meter.len),window,s.policy.motif,
            layerY(s,kMelodie),s.z,leading.active);
        if(!plan.active||origin+plan.end>motifAvailableUntil(s,kGegenstimme))return {};
        const auto relative=time-origin;
        if(!preview&&(relative<plan.begin||relative>=plan.end||outputSounding(OutMelody)))return {};
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
        for(auto tick=start;tick<start+plan.end-plan.begin;tick+=composition::motifQuantum)
        {
            const auto soundingChord=motifHarmonyAt(tick,s).chord;
            if(soundingChord.root!=chord.root||soundingChord.type!=chord.type)return {};
        }
        return {plan,base,origin};
    }

    bool melodyHandoff(musicaltime::Tick time,const Pos& p,const Settings& s,int offset,EventList& out,bool chase=false)
    {

        const auto playable=playableMelodyHandoff(time,p,s);
        const auto& plan=playable.plan;if(!plan.active)return false;
        const int base=playable.base,oct=12*octaveOf(OutCounter);
        const auto relative=time-playable.origin;
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
            auto length=std::min(note.length,plan.end-at);
            if(i+1<plan.count)length=std::min(length,source.notes[static_cast<size_t>(plan.first+i+1)].at-note.at);
            length=composition::articulatedLength(length,length,s.legato);
            if(length<capability.minDuration||length>capability.maxDuration)return false;
            if(chase?!execution::sounding(playable.origin+at,playable.origin+at+length,execution::Timing::groove,s.swing,currentPerformanceQuarter):relative!=at)continue;
            // Renderer accepts prevalidated sounding pitches, compensating the adapter octave.
            cut(kGegenstimme,time,time,offset,out);
            noteOn(OutCounter,base+note.interval-oct,note.velocity,playable.origin+at+length,offset,out);
        }
        return true;
    }

    bool dialogueReserved(const Pos& p,const Settings& s)
    {
        if(on[kMelodie]||s.genre!=GenreScore||!s.motif||s.arpFigure!=ArpCell||s.scene||s.meterNum!=4||s.meterDen!=4||phraseBars<4||!on[kGegenstimme])return false;
        const auto occurrence=motifOccurrence(p.time,p,s,OutCounter,false,true);
        return composition::planDialogue(voice(OutCounter).motif,motifCatalog,occurrence,p.time,2*musicaltime::sixteenth*meter.len).reserveResponse;
    }

    bool dialogueArp(musicaltime::Tick time,const Pos& p,const Settings& s,int offset,EventList& out,bool chase=false)
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
        const auto window=musicaltime::fromGridStep(2LL*meter.len);
        auto& use=voice(OutCounter).motif;
        auto occurrence=motifOccurrence(time,p,s,OutCounter);
        if(time>=occurrence.begin+window)use.finish(motifCatalog);
        occurrence=motifOccurrence(time,p,s,OutCounter);
        const auto& motifMemory=use.material(motifCatalog);
        if(!motifMemory.complete&&time>=occurrence.begin+window)return false;
        const auto plan=composition::planDialogue(use,motifCatalog,occurrence,time,window);
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
            auto length=std::min(n.length,window-n.at);
            if(i+1<notes)length=std::min(length,motifMemory.notes[static_cast<size_t>(i+1)].at-n.at);
            if(length<=musicaltime::Tick{})continue;
            const auto begin=plan.answerBegin+n.at;
            if(chase?!execution::sounding(begin,begin+length,execution::Timing::groove,s.swing,currentPerformanceQuarter):time!=begin)continue;
            const int pitch=composition::adaptMotifPitch(base+n.interval,ladder,count);
            noteOn(responseOutput,pitch,n.velocity,begin+length,offset,out);
        }
        return true;
    }

    void playArpeggio(musicaltime::Tick time,int offset,const Pos& p,long long phrase,const Settings& s,EventList& out)
    {
        const bool group=metricGroup(p);const float z=s.z,yArp=layerY(s,kArp);
        const int fig = chooseArp (s, phrase);
        const auto period=arpeggioPeriod(s,phrase);
        const auto anchor=s.follow[kArp]?p.chordStartTime:p.phraseStartTime;
        const auto rel=time-anchor;
        const auto rhythm=movementRhythm(p,s);
        const auto* onset=rhythm.active?rhythm.at(time-musicaltime::sixteenth*(p.bar*meter.len)):nullptr;
        const auto sourceTime=onset?musicaltime::sixteenth*(p.bar*meter.len)+onset->source:time;
        const auto sourceStep=floorDiv(sourceTime.value,musicaltime::sixteenth.value);
        const auto sourceRel=sourceTime-anchor;
        if (rhythm.active?onset!=nullptr:rel%period==musicaltime::Tick{})
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
            const auto* authored=onset?authoredRhythm(s):nullptr;
            const long long c0 = authored?composition::barry::movementOrdinal(*authored,p.bar-floorDiv((authored->staticHarmony?wendungTime:sceneTime).value,(musicaltime::sixteenth*meter.len).value),p.pos):sourceRel / period + (long long) (hashInt (77u, s.follow[kArp] ? floorDiv(anchor.value,musicaltime::sixteenth.value) : phrase) % 4);
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
            const int vel = (int) ((fig == ArpGlitter ? 40 : 52) + 35 * yArp) + (authored ? onset->accent : group ? 6 : 0) + jitter (sourceStep, kArp, 6);
            const auto len = onset?onset->length:period;
            noteOn (OutArp, note, vel, time + len, offset, out);
        }
    }

    bool densityAllows(const Pos& p)const
    {
        int group=0;for(int i=1;i<meter.numGroups;++i)if(p.pos>=meter.groupStart[i])group=i;
        return composition::EventDensity{dens}.allows(group,meter.numGroups);
    }

    void render (musicaltime::Tick time, int offset, const Pos& p, bool restart, long long phrase, const Settings& s, EventList& out, bool structural=false,bool accompanimentOnly=false)
    {
        const auto k=p.k;
        if(!chasingPatterns)prepareBassPhrase(p,s);
        const Wendung& w = W();
        curChord = p.chordIdx; curRoot = w.ch[p.chordIdx].root; curType = w.ch[p.chordIdx].type;
        if (p.passing && s.follow[kFlaeche]) { curRoot = composition::freeTransition(nextChordRoot(p),true,1.f).approachRoot; curType = Dom7; }
        updateMask (s);
        {
            const Chord& nc = p.chordIdx + 1 < w.n ? w.ch[p.chordIdx + 1] : w.ch[0];
            curNextRoot = nc.root; curNextType = nc.type;
            curProgress = p.chordEndTime > p.chordStartTime ? (float) (time-p.chordStartTime).value / (float) (p.chordEndTime-p.chordStartTime).value : 0.0f;
        }
        const bool chordStart = p.time == p.chordStartTime;
        if (!accompanimentOnly&&s.dynamics&&(!structural||chordStart||padGrow||peak||enterNow[kFlaeche]||enterNow[kBass])) dynamicsCc (time, p, s, offset, out);
        const bool beat = p.pos % 4 == 0;
        const bool group = metricGroup(p);
        const float z = s.z;
        const float yPad = layerY (s, kFlaeche), yBass = layerY (s, kBass);

        if (structural&&chordStart)
            sustained (p, s, offset, out, restart, bassRest ? 1u : 3u);
        else if (structural&&(padGrow || peak || enterNow[kFlaeche] || enterNow[kBass]))   // Ebene setzt mitten im Akkord ein
        {
            unsigned mask = (enterNow[kFlaeche] || peak ? 1u : 0u) | (enterNow[kBass] || peak ? 2u : 0u);
            if (padGrow && ! peak) { extendOnly = true; sustained (p, s, offset, out, true, 1u); extendOnly = false; }
            if (mask != 0) sustained (p, s, offset, out, true, mask);
        }

        if(structural)return;

        const bool templateSlot=time%musicaltime::sixteenth==musicaltime::Tick{};
        // Akzente: Tupfer und Stich, bei Unruhe der fremde Ton in der Mitte des Akkords; ganz oben in der Unruhe der Riss
        const bool optional=densityAllows(p);
        // Structural cues and complete thematic/answer figures bypass the density mask.
        if((templateSlot||time==p.chordStartTime||time==accentMiddle(p)||(entryTime[kAkzent]&&time==*entryTime[kAkzent]))&&(optional||prepStich||akzentForced))accents(time,p,s,offset,out);
        if(templateSlot&&optional)riss(time,p,s,offset,out);

        // --- Flaeche: Schlaege, Puls oder Staccato
        const int pad = choosePad (s);
        if (templateSlot && optional && pad == PadStabs && p.pos % 4 == 2)
            padChord (p, s, OutPadShort, offset, time + musicaltime::sixteenth*1, (int) (55 + 40 * yPad) + jitter (k, kFlaeche, 4), out);
        else if (templateSlot && optional && pad == PadPulse && beat)
            padChord (p, s, OutPadShort, offset, time + musicaltime::sixteenth*3, (int) (50 + 40 * yPad) + (group ? 8 : 0), out);
        else if (templateSlot && optional && pad == PadStaccato && beat)
            padChord (p, s, OutPadShort, offset, time + musicaltime::sixteenth*1, (int) (48 + 40 * yPad) + (group ? 6 : 0), out);
        else if (templateSlot && optional && pad == PadGated && p.pos % 2 == 0)                 // gehackte Achtel wie ein Gate
            padChord (p, s, OutPadShort, offset, time + musicaltime::sixteenth*1, (int) (46 + 40 * yPad) + (group ? 10 : 0), out);

        // --- Bass
        {
            const Chord c = chordFor (p, kBass, s);
            const ChordShape& sh = kShapes[c.type];
            const int low = bassLow (s);
            const int pat = chooseBass (s, phrase);
            int root = bassPlacement (p, s, place (s.key + ((pat == BassPedal || pat == kPulseTick) ? pedalRoot() : bassRoot (c)), low), pat == BassPedal || pat == kPulseTick);
            const int vel = (int) (58 + 38 * yBass) + (group ? 8 : 0) + jitter (k, kBass, 3);
            const int pattern = chooseBass (s, phrase);
            const int bo = bassOut (pattern);
            const bool lastEighth = time == p.chordEndTime - 2*musicaltime::sixteenth;
            // Chromatische Annaeherung an den naechsten Grundton im letzten Achtel des Akkords
            const bool approach = s.follow[kBass] && (z >= 0.3f || pattern == BassFunk) && lastEighth
                                  && pattern != BassHeld && pattern != BassWalking && pattern != BassHeartbeat && pattern != kPulseTick;
            if (approach)
            {
                const int target = nextBassPlacement (p, s);
                root = target - 1; // preserve the chromatic approach pitch class; sounding() applies the user range
            }
            const auto authored=authoredRhythmBar(p,s,true);
            if(authored.active&&!bassRest&&(optional||chordStart)&&on[kBass])
                if(const auto* hit=authored.at(time-musicaltime::sixteenth*(p.bar*meter.len)))
                {
                    const auto pitch=bassPlacement(p,s,place(s.key+bassRoot(c),low),false);
                    const int target=hit->length>4*musicaltime::sixteenth?OutBassLong:OutBassShort;
                    cut(kBass,time,time,offset,out);
                    noteOn(target,pitch,static_cast<int>(58+38*yBass)+hit->accent,time+hit->length,offset,out);
                }
            bool plannedBass=false;
            if(!chasingPatterns&&!bassRest&&(optional||chordStart)&&on[kBass]&&melodicBassAllowed(s)&&bassPhrase.valid)
                for(int i=0;i<bassPhrase.count;++i)if(bassPhrase.notes[i].at==time)
                {const auto& n=bassPhrase.notes[i];noteOn(bo,n.pitch-12*s.octave[kBass],vel+n.accent,time+n.length,offset,out);plannedBass=true;}
            switch (authored.active || (chasingPatterns&&melodicBassAllowed(s)&&bassPhrase.valid) || plannedBass || (!templateSlot&&!(approach&&(pattern==BassHalf||pattern==BassQuarter||pattern==BassAlternating||pattern==BassFunk))) || bassRest || (!optional && !chordStart) ? -1 : pattern)   // Vorbereiten: in der zweiten Takthaelfte schweigt der Bass
            {
                case kPulseTick:   if (beat) noteOn (bo, root, vel - (group ? 0 : 8), time + musicaltime::sixteenth, offset, out); break;   // Ticken in Vierteln
                case BassHalf:     if (p.pos % 8 == 0 || approach) noteOn (bo, root, vel, time + musicaltime::sixteenth*(approach ? 2 : 7), offset, out); break;
                case BassQuarter:  if (beat || approach) noteOn (bo, root, vel, time + musicaltime::sixteenth*(approach ? 2 : 3), offset, out); break;
                case BassEighth:   if (p.pos % 2 == 0) noteOn (bo, root, vel, time + musicaltime::sixteenth*2, offset, out); break;
                case BassPulse:    noteOn (bo, root, vel - (group ? 0 : 10), time + musicaltime::sixteenth, offset, out); break;
                case BassFunk:
                {
                    auto hit=composition::funkBassAttack(p.pos,approach);
                    if(hit.active)
                    {
                        int pitch=root+hit.interval;auto length=hit.duration;
                        if(melodicBassAllowed(s)&&bassPhrase.valid)for(int i=0;i<bassPhrase.count;++i)if(bassPhrase.notes[i].at==time)
                            {pitch=bassPhrase.notes[i].pitch-12*s.octave[kBass];length=bassPhrase.notes[i].length;break;}
                        noteOn(bo,pitch,vel+hit.accent,time+length,offset,out);
                    }
                    break;
                }
                case BassPendulum:
                {
                    const int rate = yBass > 0.6f ? 2 : 4;
                    if (p.pos % rate == 0)
                    {
                        const int other = fieldAccompaniment(s)&&s.bassPattern==BassAuto?3:z >= 0.5f ? 1 : 3;                 // Halbton (Unruhe) oder kleine Terz
                        const int n = (p.pos / rate) % 2 == 0 ? root : root + other;
                        noteOn (bo, n, vel, time + musicaltime::sixteenth*(rate - 1), offset, out);
                    }
                    break;
                }
                case BassWalking:
                    if (beat)
                    {
                        const int b = (int) ((time-p.chordStartTime) / musicaltime::quarter);
                        int n;
                        if (s.follow[kBass] && time + musicaltime::quarter >= p.chordEndTime)         // letzter Schlag: chromatisch zum naechsten Grundton
                        {
                            const int target = nextBassPlacement (p, s);
                            n = (b % 2 == 0) ? target - 1 : target + 1;
                        }
                        else
                        {
                            const int steps[4] = { 0, sh.iv[1], sh.iv[2], sh.n > 3 ? sh.iv[3] : 12 };
                            n = root + steps[b % 4];
                        }
                        noteOn (bo, n, vel, time + musicaltime::sixteenth*3, offset, out);
                    }
                    break;
                case BassAlternating:
                    if (beat || approach)
                    {
                        const bool odd = ((p.pos / 4) % 2) == 1;
                        noteOn (bo, approach ? root : (odd ? root - 5 : root), vel - (odd ? 6 : 0), time + musicaltime::sixteenth*2, offset, out);   // Grundton, Quinte darunter
                    }
                    break;
                case BassPedal:   // Orgelpunkt: liegt (in sustained), bei viel Intensitaet zusaetzlich ein Puls auf den Schlaegen
                    if (yBass > 0.6f && beat && time != p.chordStartTime) noteOn (OutBassShort, root, vel - 12, time + musicaltime::sixteenth, offset, out);
                    break;
                case BassHiNrg:   // Grundton und Oberoktave im Wechsel, sehr aufgewuehlt in Sechzehnteln
                {
                    const int rate = yBass > 0.75f ? 1 : 2;
                    if (p.pos % rate == 0)
                        noteOn (bo, ((p.pos / rate) % 2 == 0) ? root : root + 12, vel - ((p.pos / rate) % 2 == 0 ? 0 : 8), time + musicaltime::sixteenth*rate, offset, out);
                    break;
                }
                case BassGallop:  // Achtel und zwei Sechzehntel
                {
                    const int q = p.pos % 4;
                    if (q == 0) noteOn (bo, root, vel + 4, time + musicaltime::sixteenth*2, offset, out);
                    else if (q == 2 || q == 3) noteOn (bo, root, vel - 8, time + musicaltime::sixteenth, offset, out);
                    break;
                }
                case BassHeartbeat:
                    if (p.pos % 8 == 0) noteOn (bo, root, vel + 4, time + musicaltime::sixteenth, offset, out);
                    else if (p.pos % 8 == 2) noteOn (bo, root, vel - 10, time + musicaltime::quarter, offset, out);
                    break;
                case BassArpeggio:
                    if (p.pos % 2 == 0)
                    {
                        const int startIdx = (int) (((p.bar % sh.n) + sh.n) % sh.n);                // Startton wechselt je Takt
                        const int i = (p.pos / 2 + startIdx) % sh.n;
                        noteOn (bo, root + sh.iv[i] - (sh.iv[i] > 7 ? 12 : 0), vel, time + musicaltime::sixteenth*2, offset, out);
                    }
                    break;
                default: break;
            }
        }

        // --- Arp / Figur: motif/answer reservations retain priority over accompaniment.
        if (on[kArp] && !(chasingPatterns?dialogueReserved(p,s):dialogueArp(time,p,s,offset,out)) && !motifWindow(p,s).contains(time) && (optional||chordStart))
            playArpeggio(time,offset,p,phrase,s,out);

        if(accompanimentOnly)return;

        if(popMelodicRoles(s))
        {
            // Publish the completed, actually performed introduction even during
            // the subsequent breathing window (which deliberately has no emitter).
            auto& use=voice(OutMelody).motif;
            if(use.material(motifCatalog).count&&(time-p.phraseStartTime>=std::min(2*musicaltime::sixteenth*meter.len,p.phraseEndTime-p.phraseStartTime)
                ||p.phrase-phraseOf(sceneTime)!=use.introduction))use.finish(motifCatalog);
            popDialogTurn(p,s,false);
            const auto lead=popLeadWindow(p,s,false);
            if(lead.contains(time)&&!outputSounding(OutCounter))counterLine(time,p,s,offset,chordStart||enterNow[kMelodie],out,OutMelody);
            if(popDialogueMayLead(p,s))counterLine(time,p,s,offset,chordStart||enterNow[kGegenstimme],out);
            return;
        }
        // --- Gegenstimme: ruhige Linie aus Akkordtoenen, schrittweise gefuehrt
        if(on[kMelodie])
        {
            const auto catalog=outputCatalog(s);
            const auto foreground=composition::planForeground(s.melody,catalog[OutMelody].track);
            if(foreground.foreground)
            {
                if(!melodyHandoff(time,p,s,offset,out))
                {
                    if(dialogueMayLead(p,s))counterLine(time,p,s,offset,chordStart||enterNow[kGegenstimme],out);
                    else cut(kGegenstimme,time,time,offset,out);
                }
                int leadOutput=-1;
                for(const auto& entry:catalog)if(entry.track.id.value==foreground.lead.value)leadOutput=entry.target.output;
                if(leadOutput>=0)counterLine(time,p,s,offset,chordStart||enterNow[kMelodie],out,leadOutput);
            }
            else counterLine(time,p,s,offset,chordStart||enterNow[kGegenstimme],out);
        }
        else counterLine (time, p, s, offset, chordStart || enterNow[kGegenstimme], out);
    }

    // Dynamik als CC: Grundwert folgt der Intensitaet, darauf atmende Boegen (Grundlage: Dynamikkurven der eigenen Vorlagen,
    // meist zwischen 62 und 75 in Boegen von ein bis drei Vierteln). Pop-Rock fast flach, Score weiter, bei Unruhe mit Akzent.
    void resetCc() { lastDynamicsId = lastExpressionId = -1; for (auto& v : lastCc) v = -1; for (auto& v : lastExpr) v = -1; }

    bool outputSounding (int output) const
    {
        for (int i = 0; i < numActive; ++i) if (active[(size_t) i].out == output) return true;
        return false;
    }

    void dynamicsCc (musicaltime::Tick time, const Pos& p, const Settings& s, int offset, EventList& out)
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
            if (s.genre == GenrePopRock) value += 2.0f * std::sin (3.14159265f * ((float) ((time-p.chordStartTime) % (musicaltime::sixteenth*16)).value / musicaltime::sixteenth.value) / 16.0f);
            else
            {
                const bool slow = o == OutCounter || o == OutPadLong || o == OutBassLong;
                const int arc = slow ? 16 : 8;
                const float amp = 4.0f + 6.0f * yl + 4.0f * s.z;
                const float phase = (float) ((time-p.chordStartTime) % (musicaltime::sixteenth*arc)).value / (float) (arc*musicaltime::sixteenth.value);
                value += -0.5f * amp + amp * std::sin (3.14159265f * phase);
                const auto since = time-p.chordStartTime;
                if (s.z >= 0.6f && since < musicaltime::quarter) value += (amp + 6.0f) * (1.0f - (float) since.value / musicaltime::quarter.value);   // Sforzato beim Akkordwechsel
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
                state.capture.event(state.motif,e.note,e.velocity,musicaltime::fromQuarters(ppq+e.offset/samplesPerQuarter));
        }
        captureRead=out.size;
        state.capture.finish(state.motif,motifCatalog,musicaltime::fromQuarters(end));
    }
    void armHookCapture(musicaltime::Tick time,const Pos& p,const Settings& s)
    {
        auto& state=voice(OutCounter);
        if(state.motif.material(motifCatalog).complete||state.capture.active)return;
        // Shared physical notes do not identify an independent melodic performance.
        for(int o=0;o<kNumOutputs;++o)if(o!=OutCounter&&s.channel[o]==s.channel[OutCounter])return;
        const bool special=popHookPattern(W().id)>=0&&!s.custom;
        const auto cycle=special?2LL*meter.len:8LL*(layerY(s,kGegenstimme)<.45f?4:2);
        if((time-p.phraseStartTime)%(musicaltime::sixteenth*cycle)==musicaltime::Tick{}){state.captureSwing=s.swing;state.captureChannel=s.channel[OutCounter];state.capture.start(state.motif,time,musicaltime::fromGridStep(cycle));}
    }
    // Pop-Rock: durchgehende, gleichbleibende Hook-Linie aus Akkordtoenen (eine Figur je VARIATION)
    PlannedMotifNote hookNote (musicaltime::Tick time, const Pos& p, const Settings& s)
    {
        const auto k=p.k;
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
            const auto local = (time-p.phraseStartTime) % (musicaltime::sixteenth*cycle);
            const Chord c = chordFor (p, kGegenstimme, s);
            const auto& sh = kShapes[c.type];
            for (int i = 0; i < 8 && starts[id][i] >= 0; ++i)
            {
                const long long at = (long long) starts[id][i] * cycle / 32;
                if (local != musicaltime::sixteenth*at) continue;
                const int deg = degrees[id][i] + ((id == 0 && (time-p.phraseStartTime) / (musicaltime::sixteenth*cycle) % 2 && i == 7) ? 1 : 0);
                int note = place (s.key + c.root, 67) + sh.iv[deg % sh.n] + 12 * (deg / sh.n);
                if (id == 1 || id == 2 || id == 8) note = counterTarget (c, s, time == p.chordStartTime, k);
                long long next = i < 7 && starts[id][i + 1] >= 0 ? (long long) starts[id][i + 1] * cycle / 32 : cycle;
                const long long len = std::max (1LL, next - at - ((id == 3 || id == 7) ? 2 : 0));
                return {time,musicaltime::sixteenth*(len+(s.legato?1:0)),note,static_cast<int>(58+35*layerY(s,kGegenstimme)),true};
            }
            return {};
        }
        static constexpr int figures[6][8] = { { 0, 1, 2, 1, 0, 1, 2, 3 }, { 2, 1, 0, 1, 2, 3, 2, 1 }, { 0, 0, 2, 0, 3, 0, 2, 1 },
                                               { 3, 2, 1, 2, 3, 2, 1, 0 }, { 0, 2, 1, 2, 0, 3, 2, 1 }, { 1, 2, 3, 2, 1, 0, 1, 2 } };
        const float yc = layerY (s, kGegenstimme);
        const int rate = yc < 0.45f ? 4 : 2;
        if ((time-p.phraseStartTime) % (musicaltime::sixteenth*rate) != musicaltime::Tick{}) return {};
        const int slot = (int) (((time-p.phraseStartTime) / (musicaltime::sixteenth*rate)) % 8);
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
        return {time,musicaltime::sixteenth*(s.legato?rate+1:std::max(1,rate-1)),note,static_cast<int>(58+35*yc)+(slot%2==0?6:0),true};
    }

    void leadHook(musicaltime::Tick time,const Pos& p,const Settings& s,int offset,EventList& out)
    {
        armHookCapture(time,p,s);
        const auto n=hookNote(time,p,s);if(!n.valid)return;
        auto end=n.at+n.length;
        if(popMelodicRoles(s)&&popDialogRoute(s)&&voice(OutCounter).motif.material(motifCatalog).complete)
            end=std::min(end,popDialogTurn(p,s).end);
        noteOn(OutCounter,n.pitch,n.velocity,end,offset,out);
        if((popHookPattern(W().id)>=0&&!s.custom)||s.legato)releaseOthers(OutCounter,n.pitch,offset,out);
        voice(OutCounter).note=n.pitch;
    }

    // Legato: vorigen Ton desselben Ausgangs erst eine Sechzehntelnote nach dem neuen Anschlag loslassen.
    void releaseOthers (int o, int keep, int offset, EventList& out)
    {
        const int keepNote = sounding (o, keep);
        for (int i = 0; i < numActive; ++i)
        {
            auto& a = active[(size_t) i];
            if (a.out == o && a.note != keepNote)
                limitClaim(a,nowTime+(cur!=nullptr&&cur->legato?musicaltime::sixteenth:musicaltime::Tick{}),currentTiming);
        }
        if (cur == nullptr || ! cur->legato) releaseAt(currentPerformanceQuarter, offset, out);
    }

    // Ende eines Tons der Gegenstimme relativ zum naechsten: Legato eine Sechzehntel darueber, sonst kurz davor abgesetzt
    musicaltime::Tick tail(musicaltime::Tick len)const
    {return cur!=nullptr&&cur->legato?musicaltime::sixteenth:(len>=musicaltime::quarter?-1*musicaltime::sixteenth:musicaltime::Tick{});}

    composition::LinePhrasePlan freeLinePhrase(const Pos& p,const Settings& s)const
    {
        if(s.genre!=GenreScore||s.motif||!on[kGegenstimme])return {};
        composition::LinePhraseRequest request;
        request.begin=std::max({p.chordStartTime,p.phraseStartTime,sceneTime,wendungTime});
        request.end=std::min(p.chordEndTime,p.phraseEndTime);
        if(sceneEndTime)request.end=std::min(request.end,*sceneEndTime);
        if(s.ending==EndFade&&(s.sceneBars>0||manualEndTime))
        {
            int slots=0;const int index=orderIndex(s,entryInUse,kGegenstimme,slots);
            const int tailBars=manualEndTime?2:std::clamp(std::min(s.buildBars,s.sceneBars/2),1,64);
            if(index>0)request.end=std::min(request.end,*sceneEndTime-musicaltime::fromGridStep(slotBar(index,slots,tailBars)*meter.len));
        }
        if(s.scene&&entryInUse!=EntryAll)
        {
            int slots=0;const int index=orderIndex(s,entryInUse,kGegenstimme,slots);
            if(index>=0)request.begin=std::max(request.begin,sceneTime+musicaltime::fromGridStep(slotBar(index,slots,s.buildBars)*meter.len));
        }
        request.pulse=musicaltime::fromGridStep(meter.numGroups>1?meter.groupStart[1]:std::min(4,meter.len));
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
        request.ending=request.end==p.phraseEndTime&&chord.root==0
            ?composition::PhraseEnding::settled:composition::PhraseEnding::open;
        int interval=request.ending==composition::PhraseEnding::settled?(s.x>.6f?shape.iv[1]:0)
            :s.z>=.5f&&shape.n>3?shape.iv[3]:shape.iv[std::min(s.x>.6f?2:1,shape.n-1)];
        request.goalPitchClass=(s.key+chord.root+interval)%12;
        request.descending=s.x<.5f;request.notes=layerY(s,kGegenstimme)>=.7f?4:3;
        request.legato=s.legato;request.initialNeighbour=s.z>=.75f?1:s.z>=.5f?2:0;
        return composition::planLinePhrase(request);
    }

    bool freePhraseStep(musicaltime::Tick time,const Pos& p,const Settings& s,int offset,EventList& out,
        bool chase=false)
    {

        if(!dialogueMayLead(p,s))return true;
        const auto plan=freeLinePhrase(p,s);if(!plan.valid)return false;
        voice(OutCounter).pendingAt.reset();
        if(time>=plan.breath){cut(kGegenstimme,time,time,offset,out);return true;}
        for(int i=0;i<plan.count;++i)
        {
            const auto& n=plan.notes[static_cast<size_t>(i)];
            if(chase?!execution::sounding(n.begin,n.end,execution::Timing::groove,s.swing,currentPerformanceQuarter):n.begin!=time)continue;
            noteOn(OutCounter,n.pitch,static_cast<int>(50+35*layerY(s,kGegenstimme))+(i==0&&s.z>=.5f?6:0),n.end,offset,out);
            if(!chase)releaseOthers(OutCounter,n.pitch,offset,out);
            voice(OutCounter).note=n.pitch;
        }
        return true;
    }

    void counterLine (musicaltime::Tick time, const Pos& p, const Settings& s, int offset, bool chordStart, EventList& out, int output=OutCounter)
    {
        const auto k=p.k;

        if (! on[kOutputLayer[output]]) { voice(output).note = -1; voice(output).pendingAt.reset(); return; }
        if(output==OutCounter&&!dialogueMayLead(p,s))return;
        if (output==OutCounter && s.genre == GenrePopRock)
        {
            if(phrasedHook(s)&&voice(output).motif.material(motifCatalog).complete&&(!popMelodicRoles(s)||s.motif)){motifStep(time,p,s,offset,out,output);return;}
            leadHook(time,p,s,offset,out);return;
        }
        if(popMelodicRoles(s)&&output==OutMelody&&!popLeadWindow(p,s).contains(time))return;
        if ((output==OutMelody?s.melodyMotif:s.motif) && motifStep (time, p, s, offset, out,output)) return;
        if(output==OutCounter&&freePhraseStep(time,p,s,offset,out))return;
        const float yc = layerY (s, kOutputLayer[output]);
        const int vel = (int) (50 + 35 * yc);
        if (output==OutCounter && voice(output).pendingAt && time == *voice(output).pendingAt && voice(output).pending >= 0)                    // Vorhalt loest sich auf
        {
            noteOn (OutCounter, voice(output).pending, vel, voice(output).pendingEnd + tail (voice(output).pendingEnd - time), offset, out);
            releaseOthers (OutCounter, voice(output).pending, offset, out);
            voice(output).note = voice(output).pending; voice(output).pendingAt.reset();
        }
        // Bewegung: ruhig nur bei Akkordwechseln, mittel alle zwei Takte, aufgewuehlt in Halben
        const auto rate = musicaltime::fromGridStep(yc < 0.4f ? 0 : yc < 0.7f ? 2LL * meter.len : std::max (4LL, (long long) meter.len / 2));
        const bool move = chordStart || (rate > musicaltime::Tick{} && time > p.chordStartTime && (time - p.chordStartTime) % rate == musicaltime::Tick{} && p.chordEndTime - time >= musicaltime::quarter);
        if (! move) return;
        const Chord c = chordFor (p, kOutputLayer[output], s);
        const auto end = rate > musicaltime::Tick{} ? std::min (p.chordEndTime, time + rate) : p.chordEndTime;
        const int target = counterTarget (c, s, chordStart, k,output);
        if (output==OutCounter && s.z >= 0.5f && chordStart && end - time >= 2*musicaltime::quarter)               // Unruhe: Vorhalt von oben, loest auf den Zielton auf
        {
            const int sus = target + (s.z >= 0.75f ? 1 : 2);
            noteOn (OutCounter, sus, vel + 6, time + musicaltime::quarter + (s.legato ? musicaltime::sixteenth : musicaltime::Tick{}), offset, out);
            releaseOthers (OutCounter, sus, offset, out);
            voice(output).pending = target; voice(output).pendingAt = time + musicaltime::quarter; voice(output).pendingEnd = end;
            voice(output).note = sus;
            return;
        }
        if(output==OutMelody)
        {
            int ladder[16];if(counterLadder(c,s,ladder,output)==0)return;
            const auto bound=popMelodicRoles(s)?std::min(end,popLeadWindow(p,s).end):end;
            const auto duration=composition::articulatedLength(bound-time,bound-time,s.melodyLegato);
            noteOn(output,target,vel,time+duration,offset,out);voice(output).note=target;voice(output).pendingAt.reset();return;
        }
        noteOn (OutCounter, target, vel, end + tail(end-time), offset, out);   // Legato: eine Sechzehntel laenger, bindet zum naechsten Ton
        releaseOthers (OutCounter, target, offset, out);
        voice(output).note = target;
    }

    struct VoiceState
    {
        composition::MotifUse motif,answer;
        composition::MotifRepriseProgress reprise;
        composition::MotifCapture capture; int captureChannel=0;float captureSwing=0;
        struct RecurrenceCache
        {
            int64_t epoch=-1;musicaltime::Tick origin{},window{};uint64_t identity=0,harmony=0;bool started=false;
            composition::MotifOccurrence plan;
        } recurrence,reservationRecurrence;
        composition::HookTurn popTurn;musicaltime::Tick popTurnKey{};bool popTurnValid=false;
        int note=-1,pending=-1;
        std::optional<musicaltime::Tick> pendingAt;musicaltime::Tick pendingEnd{};
    };
    struct AuthoredRhythmCache
    {
        musicaltime::Tick entry{INT64_MIN},scene{};WendungId harmony=WendungId::invalid;
        int num=0,den=0,stableBars=-1;const composition::barry::RhythmSource* source=nullptr;
    };
    mutable AuthoredRhythmCache authoredRhythmCache;
    std::array<VoiceState,2> voices {};
    int captureRead=0;
    composition::MotifCatalog motifCatalog;
    VoiceState& voice(int output){return voices[output==OutMelody?1u:0u];}
    const VoiceState& voice(int output)const{return voices[output==OutMelody?1u:0u];}
    composition::BassPhrasePlan bassPhrase;std::optional<musicaltime::Tick> bassPairStart;uint64_t bassPhraseKey=0;
    std::array<composition::ChordDispositionResult,8> dispositionSlots {};
    composition::ChordDispositionResult lastDisposition;
    uint64_t dispositionKey=0;bool dispositionValid=false;std::optional<musicaltime::Tick> dispositionAt;
    composition::HarmonicPlan harmonicPlan;
    composition::HarmonicPlan::Slot entryVoicing; bool entryVoicingValid=false;
    uint64_t planKey = 0; bool planValid = false;
    uint32_t unavailablePad = 0;
    static constexpr int kMaxActive = 192;
    std::array<Active, kMaxActive> active {};
    int numActive = 0;
    bool running = false, wasCustom = false;
    double lastPpqEnd = 0.0;
    long long phraseIndex = -1;
    std::optional<musicaltime::Tick> restartAt;
    musicaltime::Tick wendungTime{};
    bool still = false;   // Ruhezone: Akkord steht
    bool drivePrev = false, driveSeen = false, driveLatched = false, driveArrivedNow = false;   // Fahrt: Einschalten waehrend der Wiedergabe, Ankunft
    uint32_t driveGenerationSeen = 0;
    float driveProgressNow = 0;
    bool driveTrajectory = false, segmentReturn = false;
    float originX = 0, originY = 0, segmentX = 0, segmentY = 0, segmentQ = 0;
    float segmentTargetX = 0, segmentTargetY = 0, observedBX = 0, observedBY = 0;
    std::optional<musicaltime::Tick> manualEndTime;
    bool endWasRequested = false, manualFinished=false, manualHitSent=false;
    int sceneSeed = 0;
    float routeBX=0,routeBY=0,routeCorrectionStart=0; DrivePoint routeCorrection;
    int driveFromLatched = 0;
    int chordBase = 0;    // Akkord, ab dem die Folge laeuft (nach der Ruhezone)
    int current = -1, curChord = -1, curRoot = 0, curType = Min, style = -1;
    int genre = GenreScore, lastGenre = -1, curNextRoot = 0, curNextType = Min;
    float curProgress = 0.0f;
    uint32_t chordMask = 0;          // Tonnamen des klingenden Akkords (Ersatz bei sehr engem Tonumfang)
    musicaltime::Tick nowTime{};
    execution::Timing currentTiming=execution::Timing::nominal;
    double currentPerformanceQuarter=0;
    uint64_t dispatchIdentity=0;
    std::optional<musicaltime::Tick> preparedTime;
    std::optional<Settings> previousSettings;
    musicaltime::Tick exitStep[kNumLayers] {}, exitUntil[kNumLayers] {};
    bool ccWasEnabled = false;
    int lastDynamicsId = -1, lastExpressionId = -1;
    int lastCc[17] {}, lastExpr[17] {};   // je MIDI-Kanal (1 ... 16)
    int phraseBars = kPhraseBars;
    // Szene
    musicaltime::Tick sceneTime{};
    std::optional<musicaltime::Tick> sceneEndTime;
    long long autoSeed = -1;
    int autoValue = EntryPad, entryInUse = EntryPad, sceneBarNow = -1, bassOverride = -1;
    bool sceneEnded = false, padShy = false, padGrow = false, akzentForced = false, bassRest = false, prepStich = false, peak = false;
    bool chasingPatterns=false;
    bool forceOn = false, extendOnly = false;
    bool on[kNumLayers] {}, prevOn[kNumLayers] {}, hOn[kNumLayers] {}, enterNow[kNumLayers] {}, thinned[kNumLayers] {};
    musicaltime::Tick hSince[kNumLayers] {};
    std::optional<musicaltime::Tick> entryTime[kNumLayers] {};
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
