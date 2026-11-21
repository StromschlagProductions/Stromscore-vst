#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace
{
juce::String u8 (const char* s) { return juce::String (juce::CharPointer_UTF8 (s)); }

juce::AudioParameterFloatAttributes percent()
{
    return juce::AudioParameterFloatAttributes()
        .withStringFromValueFunction ([] (float v, int) { return juce::String (juce::roundToInt (v * 100.0f)) + " %"; })
        .withValueFromStringFunction ([] (const juce::String& t) { return juce::jlimit (0.0f, 1.0f, t.retainCharacters ("0123456789.,").replaceCharacter (',', '.').getFloatValue() / 100.0f); });
}
}

juce::StringArray StromscoreProcessor::keyNames()
{
    return { "C", "Cis / Des", "D", "Dis / Es", "E", "F", "Fis / Ges", "G", "Gis / As", "A", "Ais / B", "H" };
}
juce::StringArray StromscoreProcessor::meterNames()  { return { "Vom Projekt", "4/4", "3/4", "6/8", "5/4", "7/8", "5/8", "12/8" }; }
juce::StringArray StromscoreProcessor::layerNames()  { return { u8 ("Fläche"), "Bass", "Arp", "Akzent", "Gegenstimme" }; }
juce::StringArray StromscoreProcessor::outputNames() { return { u8 ("Fläche lang"), u8 ("Fläche kurz"), "Bass lang", "Bass kurz", "Arp", "Akzent Tupfer", "Akzent Stich", "Gegenstimme" }; }
juce::String StromscoreProcessor::rangeName (int r) { return r == 3 ? juce::String ("Akzent Tupfer") : r == 5 ? juce::String ("Akzent Stich") : layerNames()[juce::jlimit (0, 4, r)]; }
juce::StringArray StromscoreProcessor::channelNames() { juce::StringArray a; for (int i = 1; i <= 16; ++i) a.add ("Kanal " + juce::String (i)); return a; }
juce::StringArray StromscoreProcessor::padPatternNames()  { return { "Auto", "Gehalten", u8 ("Schläge"), "Puls", "Staccato", "Gated" }; }
juce::StringArray StromscoreProcessor::genreNames()       { return { "Score", "80er Pop-Rock" }; }
juce::StringArray StromscoreProcessor::bassPatternNames() { return { "Auto", "Gehalten", "Halbe", "Viertel", "Achtel", "Puls", "Funk", "Pendel",
                                                                     "Walking", "Wechselbass", "Herzschlag", "Arpeggio", "Orgelpunkt", "Hi-NRG", "Galopp" }; }
juce::StringArray StromscoreProcessor::arpFigureNames()   { return { "Auto", u8 ("Aufwärts"), u8 ("Abwärts"), "Kreisend", "Zelle", "Riff", "Glitzern", u8 ("Sprünge"), "Kaskade", "Oktatonisch", "Quarten", "SID" }; }
juce::StringArray StromscoreProcessor::changeNames()      { return { u8 ("Nächster Schlag"), u8 ("Nächster Takt"), "Alle 2 Takte", "Alle 4 Takte" }; }
juce::StringArray StromscoreProcessor::octaveNames()      { return { u8 ("−2 Okt."), u8 ("−1 Okt."), "Normal", "+1 Okt.", "+2 Okt." }; }
juce::StringArray StromscoreProcessor::slotRootNames()    { return { "C", "Cis", "D", "Es", "E", "F", "Fis", "G", "As", "A", "B", "H" }; }
juce::StringArray StromscoreProcessor::slotTypeNames()    { return { "Dur", "Moll", "maj7", "m7", "7", "sus4", "sus2", "add9", "m6", "m(maj7)", "m7b5", "dim7", "+" }; }
juce::StringArray StromscoreProcessor::slotBarNames()     { return { u8 ("–"), "1 Takt", "2 Takte", "3 Takte", "4 Takte" }; }
juce::StringArray StromscoreProcessor::arpRateNames()     { return { "Auto", "Viertel", "Achtel", "16tel" }; }
juce::StringArray StromscoreProcessor::entryNames()       { return { "Auto", u8 ("Fläche, schüchtern"), "Bass-Schlag", "Puls", "Arpeggio", "Akzent", "Gegenstimme", "Alles zugleich" }; }
juce::StringArray StromscoreProcessor::buildNames()       { return { "4 Takte", "8 Takte", "16 Takte" }; }
juce::StringArray StromscoreProcessor::sceneLengthNames() { return { "unbegrenzt", "8 Takte", "16 Takte", "24 Takte", "32 Takte", "48 Takte", "64 Takte" }; }
juce::StringArray StromscoreProcessor::endingNames()      { return { "Hart", "Ausklingend", "Offen" }; }
juce::StringArray StromscoreProcessor::driveStartNames()  { return { "sofort", "ab Takt 5", "ab Takt 9", "ab Takt 17", "ab Takt 33" }; }
juce::StringArray StromscoreProcessor::driveBarsNames()   { return { "4 Takte", "8 Takte", "16 Takte", "32 Takte" }; }
juce::StringArray StromscoreProcessor::curveNames()       { return { u8 ("Gleichmäßig"), "Erst langsam", "In Stufen", u8 ("Hin und zurück") }; }

juce::String StromscoreProcessor::noteName (int n)
{
    static const char* names[12] = { "C", "Cis", "D", "Dis", "E", "F", "Fis", "G", "Gis", "A", "B", "H" };
    n = juce::jlimit (0, 127, n);
    return juce::String (names[n % 12]) + juce::String (n / 12 - 2);
}

// Richtwerte fuer den klingenden Tonumfang (MIDI-Nummern); genauer geht es mit "Anlernen" am eigenen Patch
const std::vector<StromscoreProcessor::RangeTemplate>& StromscoreProcessor::rangeTemplates()
{
    static const std::vector<RangeTemplate> t = {
        { "Violine", 55, 100 },          { "Viola", 48, 88 },             { "Cello", 36, 81 },
        { "Kontrabass", 28, 62 },        { "Streicher-Ensemble", 28, 100 },
        { "Fl\xc3\xb6te", 60, 96 },
        { "Piccolo", 74, 105 },          { "Oboe", 58, 91 },              { "Klarinette", 50, 91 },
        { "Fagott", 34, 75 },            { "Horn", 41, 77 },              { "Trompete", 54, 82 },
        { "Posaune", 40, 72 },           { "Tuba", 28, 58 },              { "Harfe", 24, 103 },
        { "Celesta", 60, 108 },          { "Glockenspiel", 79, 108 },     { "Klavier", 21, 108 } };
    return t;
}

juce::AudioProcessorValueTreeState::ParameterLayout StromscoreProcessor::createLayout()
{
    using namespace juce;
    AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "key", 1 }, "Tonart", keyNames(), 9));
    layout.add (std::make_unique<AudioParameterFloat> (ParameterID { "faerbung", 1 }, u8 ("Färbung"), NormalisableRange<float> (0.0f, 1.0f), 0.5f, percent()));
    layout.add (std::make_unique<AudioParameterFloat> (ParameterID { "intensitaet", 1 }, u8 ("Intensität"), NormalisableRange<float> (0.0f, 1.0f), 0.1f, percent()));
    layout.add (std::make_unique<AudioParameterFloat> (ParameterID { "unruhe", 1 }, "Unruhe", NormalisableRange<float> (0.0f, 1.0f), 0.0f, percent()));
    layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "takt", 1 }, "Takt", meterNames(), 0));
    layout.add (std::make_unique<AudioParameterFloat> (ParameterID { "swing", 1 }, "Swing", NormalisableRange<float> (0.0f, 1.0f), 0.0f, percent()));
    layout.add (std::make_unique<AudioParameterInt> (ParameterID { "variation", 1 }, "Variation", 1, 16, 1));
    const auto signedPercent = AudioParameterFloatAttributes()
        .withStringFromValueFunction ([] (float v, int) { const int p = roundToInt (v * 100.0f); return (p > 0 ? "+" : p < 0 ? String (CharPointer_UTF8 ("\xe2\x88\x92")) : String (CharPointer_UTF8 ("\xc2\xb1"))) + String (std::abs (p)) + " %"; })
        .withValueFromStringFunction ([] (const String& t) { const auto c = t.replace (CharPointer_UTF8 ("\xe2\x88\x92"), "-").retainCharacters ("-0123456789.,").replaceCharacter (',', '.'); return jlimit (-1.0f, 1.0f, c.getFloatValue() / 100.0f); });
    for (int i = 0; i < stromscore::kNumLayers; ++i)
    {
        const String n (i + 1);
        layout.add (std::make_unique<AudioParameterBool> (ParameterID { "mute" + n, 1 }, layerNames()[i] + " Mute", false));
        layout.add (std::make_unique<AudioParameterBool> (ParameterID { "solo" + n, 1 }, layerNames()[i] + " Solo", false));
        layout.add (std::make_unique<AudioParameterFloat> (ParameterID { "intensitaet" + n, 1 }, layerNames()[i] + u8 (" Intensität"),
            NormalisableRange<float> (-1.0f, 1.0f), 0.0f, signedPercent));
    }
    layout.add (std::make_unique<AudioParameterBool> (ParameterID { "durchgaenge", 1 }, u8 ("Durchgänge"), false));
    layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "genre", 1 }, "Genre", genreNames(), 0));
    layout.add (std::make_unique<AudioParameterBool> (ParameterID { "dynamikCc", 1 }, "Dynamik per CC", false));
    layout.add (std::make_unique<AudioParameterFloat> (ParameterID { "abwechslung", 1 }, "Abwechslung", NormalisableRange<float> (0.0f, 1.0f), 0.5f, percent()));
    for (int i = 0; i < 3; ++i)
        layout.add (std::make_unique<AudioParameterBool> (ParameterID { "follow" + String (i + 1), 1 },
            layerNames()[i] + " folgt den Akkorden", true));
    layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "padPattern", 1 }, u8 ("Fläche Muster"), padPatternNames(), 0));
    layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "bassPattern", 1 }, "Bass Muster", bassPatternNames(), 0));
    layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "arpFigure", 1 }, "Arp Figur", arpFigureNames(), 0));
    layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "arpRate", 1 }, "Arp Tempo", arpRateNames(), 0));
    layout.add (std::make_unique<AudioParameterBool> (ParameterID { "preview", 1 }, u8 ("Vorhören"), false));
    layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "wechsel", 1 }, "Wechsel", changeNames(), 0));
    for (int i = 0; i < stromscore::kNumLayers; ++i)
        layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "oct" + String (i + 1), 1 },
            layerNames()[i] + " Oktave", octaveNames(), 2));
    const auto noteAttr = AudioParameterIntAttributes()
        .withStringFromValueFunction ([] (int v, int) { return noteName (v); });
    for (int i = 0; i < stromscore::kNumRanges; ++i)
    {
        const String n (i + 1);
        layout.add (std::make_unique<AudioParameterBool> (ParameterID { "umfang" + n, 1 }, rangeName (i) + " Tonumfang", false));
        layout.add (std::make_unique<AudioParameterInt> (ParameterID { "tief" + n, 1 }, rangeName (i) + u8 (" tiefster Ton"), 0, 127, 0, noteAttr));
        layout.add (std::make_unique<AudioParameterInt> (ParameterID { "hoch" + n, 1 }, rangeName (i) + u8 (" höchster Ton"), 0, 127, 127, noteAttr));
    }
    // MIDI-Kanal je Ausgang; Vorgabe 1 ... 8, mehrere Ausgaenge duerfen sich einen Kanal teilen
    for (int i = 0; i < stromscore::kNumOutputs; ++i)
        layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "kanal" + String (i + 1), 1 }, outputNames()[i] + " MIDI-Kanal", channelNames(), i));
    layout.add (std::make_unique<AudioParameterBool> (ParameterID { "legato", 1 }, "Gegenstimme Legato", true));
    layout.add (std::make_unique<AudioParameterBool> (ParameterID { "eigeneFolge", 1 }, "Eigene Folge", false));
    // Szene (ab 1.3): Einstieg und Aufbau ab Wiedergabebeginn, Ende, Fahrt von A nach B, Motiv
    layout.add (std::make_unique<AudioParameterBool> (ParameterID { "aufbau", 1 }, "Aufbau", true));
    layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "einstieg", 1 }, "Einstieg", entryNames(), 0));
    layout.add (std::make_unique<AudioParameterInt> (ParameterID { "wurf", 1 }, "Wurf", 0, 9999, 0));
    layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "aufbauTakte", 1 }, u8 ("Aufbau Länge"), buildNames(), 1));
    layout.add (std::make_unique<AudioParameterFloat> (ParameterID { "haerte", 1 }, u8 ("Härte"), NormalisableRange<float> (0.0f, 1.0f), 0.5f, percent()));
    layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "szenenLaenge", 1 }, u8 ("Szenenlänge"), sceneLengthNames(), 0));
    layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "ende", 1 }, "Ende", endingNames(), 1));
    layout.add (std::make_unique<AudioParameterBool> (ParameterID { "motiv", 1 }, "Gegenstimme Motiv", true));
    layout.add (std::make_unique<AudioParameterBool> (ParameterID { "fahrt", 1 }, "Fahrt", false));
    layout.add (std::make_unique<AudioParameterFloat> (ParameterID { "fahrtX", 1 }, u8 ("Fahrt Ziel Färbung"), NormalisableRange<float> (0.0f, 1.0f), 0.8f, percent()));
    layout.add (std::make_unique<AudioParameterFloat> (ParameterID { "fahrtY", 1 }, u8 ("Fahrt Ziel Intensität"), NormalisableRange<float> (0.0f, 1.0f), 0.85f, percent()));
    layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "fahrtStart", 1 }, "Fahrt Start", driveStartNames(), 0));
    layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "fahrtTakte", 1 }, "Fahrt Dauer", driveBarsNames(), 1));
    layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "fahrtKurve", 1 }, "Fahrt Kurve", curveNames(), 0));
    static constexpr int defRoot[stromscore::kMaxChords] = { 5, 0, 10, 7, 9, 2, 4, 0 };   // F - C - B - G
    for (int i = 0; i < stromscore::kMaxChords; ++i)
    {
        const String n (i + 1);
        layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "slotRoot" + n, 1 }, "Akkord " + n + " Grundton", slotRootNames(), defRoot[i]));
        layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "slotType" + n, 1 }, "Akkord " + n + " Art", slotTypeNames(), 0));
        layout.add (std::make_unique<AudioParameterChoice> (ParameterID { "slotBars" + n, 1 }, "Akkord " + n + u8 (" Länge"), slotBarNames(), i < 4 ? 2 : 0));
    }
    return layout;
}

StromscoreProcessor::StromscoreProcessor()
    : AudioProcessor (BusesProperties().withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      apvts (*this, nullptr, "STROMSCORE", createLayout())
{
    pKey = apvts.getRawParameterValue ("key");
    for (int i = 0; i < 3; ++i) { pAxis[i] = apvts.getRawParameterValue (kAxisIds[i]); axisParam[i] = apvts.getParameter (kAxisIds[i]); }
    pMeter = apvts.getRawParameterValue ("takt");
    pSwing = apvts.getRawParameterValue ("swing");
    pVariation = apvts.getRawParameterValue ("variation");
    pPreview = apvts.getRawParameterValue ("preview");
    for (int i = 0; i < stromscore::kNumLayers; ++i)
    {
        const juce::String n (i + 1);
        pMute[i] = apvts.getRawParameterValue ("mute" + n);
        pSolo[i] = apvts.getRawParameterValue ("solo" + n);
        pLayerIntensity[i] = apvts.getRawParameterValue ("intensitaet" + n);
    }
    pVariety = apvts.getRawParameterValue ("abwechslung");
    pPassing = apvts.getRawParameterValue ("durchgaenge");
    pGenre = apvts.getRawParameterValue ("genre");
    pDynamics = apvts.getRawParameterValue ("dynamikCc");
    for (int i = 0; i < 3; ++i) pFollow[i] = apvts.getRawParameterValue ("follow" + juce::String (i + 1));
    pPad = apvts.getRawParameterValue ("padPattern");
    pBass = apvts.getRawParameterValue ("bassPattern");
    pArp = apvts.getRawParameterValue ("arpFigure");
    pRate = apvts.getRawParameterValue ("arpRate");
    pChange = apvts.getRawParameterValue ("wechsel");
    for (int i = 0; i < stromscore::kNumLayers; ++i)
        pOctave[i] = apvts.getRawParameterValue ("oct" + juce::String (i + 1));
    for (int i = 0; i < stromscore::kNumRanges; ++i)
    {
        const juce::String n (i + 1);
        pRangeOn[i] = apvts.getRawParameterValue ("umfang" + n);
        pRangeLo[i] = apvts.getRawParameterValue ("tief" + n);
        pRangeHi[i] = apvts.getRawParameterValue ("hoch" + n);
    }
    for (int i = 0; i < stromscore::kNumOutputs; ++i) pChannel[i] = apvts.getRawParameterValue ("kanal" + juce::String (i + 1));
    pLegato = apvts.getRawParameterValue ("legato");
    pCustom = apvts.getRawParameterValue ("eigeneFolge");
    pScene = apvts.getRawParameterValue ("aufbau");
    pEntry = apvts.getRawParameterValue ("einstieg");
    pSeed = apvts.getRawParameterValue ("wurf");
    pBuild = apvts.getRawParameterValue ("aufbauTakte");
    pHardness = apvts.getRawParameterValue ("haerte");
    pSceneLen = apvts.getRawParameterValue ("szenenLaenge");
    pEnding = apvts.getRawParameterValue ("ende");
    pMotif = apvts.getRawParameterValue ("motiv");
    pDrive = apvts.getRawParameterValue ("fahrt");
    pDriveX = apvts.getRawParameterValue ("fahrtX");
    pDriveY = apvts.getRawParameterValue ("fahrtY");
    pDriveFrom = apvts.getRawParameterValue ("fahrtStart");
    pDriveBars = apvts.getRawParameterValue ("fahrtTakte");
    pCurve = apvts.getRawParameterValue ("fahrtKurve");
    for (int i = 0; i < stromscore::kMaxChords; ++i)
    {
        const juce::String n (i + 1);
        pSlotRoot[i] = apvts.getRawParameterValue ("slotRoot" + n);
        pSlotType[i] = apvts.getRawParameterValue ("slotType" + n);
        pSlotBars[i] = apvts.getRawParameterValue ("slotBars" + n);
    }
}

bool StromscoreProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    const auto out = layouts.getMainOutputChannelSet();
    return out == juce::AudioChannelSet::stereo() || out == juce::AudioChannelSet::mono();
}

void StromscoreProcessor::prepareToPlay (double sampleRate, int)
{
    currentRate = sampleRate;
    flushPending = true;
    generator.reset();
    previewGenerator.reset(); previewRunning = false;
    preview.prepare (sampleRate);
}

void StromscoreProcessor::reset()
{
    flushPending = true;   // klingende Noten beim naechsten Block beenden (die Engine vergisst sie hier)
    generator.reset();
    previewGenerator.reset(); previewRunning = false;
    preview.reset();
}

stromscore::Settings StromscoreProcessor::currentSettings() const
{
    stromscore::Settings s;
    s.key = juce::roundToInt (pKey->load());
    s.x = pAxis[0]->load(); s.y = pAxis[1]->load(); s.z = pAxis[2]->load();
    static constexpr int nums[] = { 0, 4, 3, 6, 5, 7, 5, 12 };
    static constexpr int dens[] = { 0, 4, 4, 8, 4, 8, 8, 8 };
    const int m = juce::jlimit (0, 7, juce::roundToInt (pMeter->load()));
    s.meterNum = m == 0 ? hostNum : nums[m];
    s.meterDen = m == 0 ? hostDen : dens[m];
    s.swing = pSwing->load();
    s.variation = juce::roundToInt (pVariation->load());
    for (int i = 0; i < stromscore::kNumLayers; ++i)
    {
        s.mute[i] = pMute[i]->load() >= 0.5f;
        s.solo[i] = pSolo[i]->load() >= 0.5f;
        s.layerIntensity[i] = pLayerIntensity[i]->load();
    }
    s.variety = pVariety->load();
    s.passing = pPassing->load() >= 0.5f;
    s.genre = juce::roundToInt (pGenre->load());
    s.dynamics = pDynamics->load() >= 0.5f;
    s.ccDynamics = ccOut[0].load();
    s.ccExpression = ccOut[1].load();
    for (int i = 0; i < 3; ++i) s.follow[i] = pFollow[i]->load() >= 0.5f;
    s.padPattern = juce::roundToInt (pPad->load());
    s.bassPattern = juce::roundToInt (pBass->load());
    s.arpFigure = juce::roundToInt (pArp->load());
    s.arpRate = juce::roundToInt (pRate->load());
    s.change = juce::roundToInt (pChange->load());
    for (int i = 0; i < stromscore::kNumLayers; ++i)
        s.octave[i] = juce::roundToInt (pOctave[i]->load()) - 2;
    for (int i = 0; i < stromscore::kNumOutputs; ++i)
        s.channel[i] = juce::jlimit (1, 16, juce::roundToInt (pChannel[i]->load()) + 1);
    s.legato = pLegato->load() >= 0.5f;
    for (int i = 0; i < stromscore::kNumRanges; ++i)
    {
        s.rangeOn[i] = pRangeOn[i]->load() >= 0.5f;
        s.rangeLo[i] = juce::roundToInt (pRangeLo[i]->load());
        s.rangeHi[i] = juce::roundToInt (pRangeHi[i]->load());
    }
    s.custom = pCustom->load() >= 0.5f;
    for (int i = 0; i < stromscore::kMaxChords; ++i)
    {
        s.customChords[i].rootAbs = juce::roundToInt (pSlotRoot[i]->load());
        s.customChords[i].type = stromscore::kCustomTypes[juce::jlimit (0, stromscore::kNumCustomTypes - 1, juce::roundToInt (pSlotType[i]->load()))];
        s.customChords[i].bars = juce::roundToInt (pSlotBars[i]->load());
    }
    auto pick = [] (std::atomic<float>* p, const int* table, int n) { return table[juce::jlimit (0, n - 1, juce::roundToInt (p->load()))]; };
    s.scene = pScene->load() >= 0.5f;
    s.entry = juce::jlimit (0, stromscore::kNumEntries - 1, juce::roundToInt (pEntry->load()));
    s.seed = juce::roundToInt (pSeed->load());
    s.buildBars = pick (pBuild, kBuildBars, 3);
    s.hardness = pHardness->load();
    s.sceneBars = pick (pSceneLen, kSceneBars, 7);
    s.ending = juce::jlimit (0, stromscore::kNumEndings - 1, juce::roundToInt (pEnding->load()));
    s.motif = pMotif->load() >= 0.5f;
    s.inertia = true;   // Traegheit ist im Plugin immer an
    s.drive = pDrive->load() >= 0.5f;
    s.driveX = pDriveX->load(); s.driveY = pDriveY->load();
    s.driveFrom = pick (pDriveFrom, kDriveFrom, 5);
    s.driveBars = pick (pDriveBars, kDriveBars, 4);
    s.driveCurve = juce::jlimit (0, stromscore::kNumCurves - 1, juce::roundToInt (pCurve->load()));
    return s;
}

// Controller am MIDI-Eingang (z. B. Nuances-Fader) bewegen Faerbung, Intensitaet und Unruhe
void StromscoreProcessor::handleControllers (const juce::MidiBuffer& incoming)
{
    float last[3] = { -1.0f, -1.0f, -1.0f };
    for (const auto meta : incoming)
    {
        const auto msg = meta.getMessage();
        if (msg.isNoteOn() && learnLayer.load() >= 0)   // Anlernen: erste und zweite gedrueckte Taste
        {
            if (learnFirst.load() < 0) learnFirst.store (msg.getNoteNumber());
            else if (learnSecond.load() < 0 && msg.getNoteNumber() != learnFirst.load()) learnSecond.store (msg.getNoteNumber());
        }
        if (! msg.isController()) continue;
        for (int a = 0; a < 3; ++a)
        {
            const int cc = ccNumber[a].load();
            if (cc > 0 && msg.getControllerNumber() == cc)
                last[a] = (float) msg.getControllerValue() / 127.0f;
        }
    }
    for (int a = 0; a < 3; ++a)
        if (last[a] >= 0.0f && axisParam[a] != nullptr && std::abs (axisParam[a]->getValue() - last[a]) > 1.0e-4f)
            axisParam[a]->setValueNotifyingHost (last[a]);
}

// Beendet alles, was noch klingt, und schickt zur Sicherheit "Alle Noten aus" (CC 123) auf den benutzten Kanaelen
void StromscoreProcessor::flushSounding (juce::MidiBuffer& midi, bool forceAllNotesOff)
{
    uint32_t configured = 0;
    for (auto* c : pChannel) configured |= 1u << juce::jlimit (0, 15, juce::roundToInt (c->load()));
    for (int ch = 0; ch < 16; ++ch)
    {
        bool any = forceAllNotesOff && ((configured >> ch) & 1u) != 0;
        for (int note = 0; note < 128; ++note)
            if (sounding[ch].test ((size_t) note))
            {
                midi.addEvent (juce::MidiMessage::noteOff (ch + 1, note), 0);
                any = true;
            }
        sounding[ch].reset();
        if (any) midi.addEvent (juce::MidiMessage::allNotesOff (ch + 1), 0);
    }
}

void StromscoreProcessor::emit (const stromscore::EventList& list, juce::MidiBuffer& midi, juce::AudioBuffer<float>& audio, bool withPreview, bool toMidi)
{
    const int n = audio.getNumSamples();
    withPreview = withPreview && audio.getNumChannels() > 1;   // Vorhoeren nur in Stereo
    float* l = audio.getWritePointer (0);
    float* r = audio.getNumChannels() > 1 ? audio.getWritePointer (1) : nullptr;
    int rendered = 0;
    for (int i = 0; i < list.size; ++i)
    {
        const auto& e = list.events[(size_t) i];
        if (e.type == 1)   // Dynamik-Controller: nur an die Spuren, nicht in den Testklang
        {
            if (toMidi) midi.addEvent (juce::MidiMessage::controllerEvent (e.channel, e.note, e.velocity), e.offset);
            continue;
        }
        if (! toMidi)
        {
            if (e.velocity > 0) activity[e.out % stromscore::kNumOutputs].store (1.0f);
        }
        else if (e.velocity > 0)
        {
            midi.addEvent (juce::MidiMessage::noteOn (e.channel, e.note, (juce::uint8) e.velocity), e.offset);
            sounding[(e.channel - 1) & 15].set ((size_t) e.note);
            activity[e.out % stromscore::kNumOutputs].store (1.0f);
        }
        else
        {
            midi.addEvent (juce::MidiMessage::noteOff (e.channel, e.note), e.offset);
            sounding[(e.channel - 1) & 15].reset ((size_t) e.note);
        }

        if (withPreview)
        {
            const int upTo = juce::jlimit (rendered, n, e.offset);
            if (upTo > rendered) preview.render (l + rendered, r + rendered, upTo - rendered);
            rendered = upTo;
            preview.handle (e);
        }
    }
    if (withPreview && rendered < n)
        preview.render (l + rendered, r + rendered, n - rendered);
}

void StromscoreProcessor::processBlock (juce::AudioBuffer<float>& audio, juce::MidiBuffer& midi)
{
    juce::ScopedNoDenormals noDenormals;
    audio.clear();
    handleControllers (midi);
    midi.clear();   // eingehende Noten werden nicht weitergereicht

    stromscore::Transport t;
    t.sampleRate = currentRate > 0.0 ? currentRate : 48000.0;
    if (auto* head = getPlayHead())
        if (auto pos = head->getPosition())
        {
            t.playing = pos->getIsPlaying();
            if (auto ppq = pos->getPpqPosition()) t.ppq = *ppq; else t.playing = false;
            if (auto bpm = pos->getBpm()) { t.bpm = *bpm; hostBpm = *bpm; }
            if (auto sig = pos->getTimeSignature()) { hostNum = sig->numerator; hostDen = sig->denominator; }
        }
    hostPlaying.store (t.playing);

    events.clear();
    if (wasBypassed) { generator.reset(); wasBypassed = false; }
    if (flushPending) { flushSounding (midi, false); preview.reset(); flushPending = false; }
    const auto settings = currentSettings();
    meterNum.store (settings.meterNum); meterDen.store (settings.meterDen);
    generator.process (t, settings, audio.getNumSamples(), events);
    publish (generator, t.playing);
    wendung.store (t.playing ? generator.wendung() : -1);
    styleIndex.store (generator.styleWendung());
    genreInUse.store (generator.genreInUse());
    nextRoot.store (generator.nextRoot()); nextType.store (generator.nextType()); chordProgress.store (generator.chordProgress());
    chordIndex.store (t.playing ? generator.chordInWendung() : -1);
    chordRoot.store (generator.chordRoot());
    chordType.store (generator.chordType());

    const bool withPreview = pPreview->load() >= 0.5f;
    if (! withPreview) preview.reset();

    // Vorhoeren ohne Wiedergabe: eigene Uhr im Projekttempo, nur der Testklang, kein MIDI an die Spuren
    if (withPreview && ! t.playing)
    {
        if (! previewRunning) { previewGenerator.reset(); preview.reset(); previewPpq = 0.0; previewRunning = true; }
        stromscore::Transport own;
        own.playing = true; own.ppq = previewPpq; own.sampleRate = t.sampleRate;
        own.bpm = hostBpm > 1.0 ? hostBpm : 120.0;
        previewEvents.clear();
        previewGenerator.process (own, settings, audio.getNumSamples(), previewEvents);
        previewPpq += (double) audio.getNumSamples() / (own.sampleRate * 60.0 / own.bpm);
        publish (previewGenerator, true);
        wendung.store (previewGenerator.wendung());
        styleIndex.store (previewGenerator.styleWendung());
        genreInUse.store (previewGenerator.genreInUse());
        nextRoot.store (previewGenerator.nextRoot()); nextType.store (previewGenerator.nextType()); chordProgress.store (previewGenerator.chordProgress());
        chordIndex.store (previewGenerator.chordInWendung());
        chordRoot.store (previewGenerator.chordRoot());
        chordType.store (previewGenerator.chordType());
        emit (previewEvents, midi, audio, true, false);
    }
    else
    {
        if (previewRunning) { previewGenerator.reset(); preview.reset(); previewRunning = false; }   // DAW startet: ihr Takt uebernimmt
        emit (events, midi, audio, withPreview);
    }

    // Stopp: was noch klingt (z. B. weil der Host zwischendurch zurueckgesetzt hat) sicher beenden
    if (! t.playing)
        flushSounding (midi, wasPlaying);
    wasPlaying = t.playing;
}

void StromscoreProcessor::publish (const stromscore::Generator& g, bool playing)
{
    sceneBar.store (playing ? g.sceneBar() : -1);
    sceneEntry.store (g.sceneEntry());
    sceneOver.store (playing && g.sceneOver());
    if (playing) { pointX.store (g.pointX()); pointY.store (g.pointY()); }
}

void StromscoreProcessor::processBlockBypassed (juce::AudioBuffer<float>& audio, juce::MidiBuffer& midi)
{
    audio.clear();
    midi.clear();
    if (! wasBypassed)
    {
        generator.reset();
        previewGenerator.reset(); previewRunning = false;
        flushSounding (midi, true);
        preview.reset();
        wasPlaying = false;
        wasBypassed = true;
    }
}

void StromscoreProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    state.setProperty ("theme", uiTheme.load(), nullptr);
    state.setProperty ("uiW", uiWidth.load(), nullptr);
    state.setProperty ("ccFaerbung", ccNumber[0].load(), nullptr);
    state.setProperty ("ccIntensitaet", ccNumber[1].load(), nullptr);
    state.setProperty ("ccUnruhe", ccNumber[2].load(), nullptr);
    state.setProperty ("ccDynamik", ccOut[0].load(), nullptr);
    state.setProperty ("ccAusdruck", ccOut[1].load(), nullptr);
    state.setProperty ("exportTakte", exportBars.load(), nullptr);
    if (auto xml = state.createXml())
        copyXmlToBinary (*xml, destData);
}

void StromscoreProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (auto xml = getXmlFromBinary (data, sizeInBytes))
    {
        auto state = juce::ValueTree::fromXml (*xml);
        if (state.isValid() && state.hasType (apvts.state.getType()))
        {
            uiTheme.store ((int) state.getProperty ("theme", 0) == 1 ? 1 : 0);
            uiWidth.store (juce::jlimit (kUiWidth / 2, kUiWidth * 3, (int) state.getProperty ("uiW", kUiWidth)));
            ccNumber[0].store (juce::jlimit (0, 127, (int) state.getProperty ("ccFaerbung", 11)));
            ccNumber[1].store (juce::jlimit (0, 127, (int) state.getProperty ("ccIntensitaet", 1)));
            ccNumber[2].store (juce::jlimit (0, 127, (int) state.getProperty ("ccUnruhe", 74)));
            ccOut[0].store (juce::jlimit (0, 127, (int) state.getProperty ("ccDynamik", 1)));
            ccOut[1].store (juce::jlimit (0, 127, (int) state.getProperty ("ccAusdruck", 11)));
            exportBars.store (juce::jlimit (1, 64, (int) state.getProperty ("exportTakte", 8)));
            apvts.replaceState (state);
        }
    }
}

juce::AudioProcessorEditor* StromscoreProcessor::createEditor() { return new StromscoreEditor (*this); }

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new StromscoreProcessor(); }

// ---------------------------------------------------------------- MIDI-Datei zum Herausziehen
juce::File StromscoreProcessor::renderMidiFile (int bars) const
{
    auto settings = currentSettings();
    const double bpm = hostBpm > 1.0 ? hostBpm : 120.0;
    const double sr = 48000.0;
    const int block = 480;
    const auto meter = stromscore::Meter::from (settings.meterNum, settings.meterDen);
    const double quarters = (double) bars * meter.len * stromscore::kStep;
    const double samplesPerQuarter = sr * 60.0 / bpm;
    constexpr int tpq = 960;

    stromscore::Generator gen;
    gen.reset();
    auto events = std::make_unique<stromscore::EventList>();
    juce::MidiMessageSequence tracks[16];   // je MIDI-Kanal
    stromscore::Transport t;
    t.playing = true; t.bpm = bpm; t.sampleRate = sr;
    auto collect = [&] (double blockPpq)
    {
        for (int i = 0; i < events->size; ++i)
        {
            const auto& e = events->events[(size_t) i];
            const double tick = std::min (quarters, blockPpq + (double) e.offset / samplesPerQuarter) * tpq;
            const int ch = juce::jlimit (0, 15, (int) e.channel - 1);
            juce::MidiMessage m = e.type == 1 ? juce::MidiMessage::controllerEvent (e.channel, e.note, e.velocity)
                                : e.velocity > 0 ? juce::MidiMessage::noteOn (e.channel, e.note, (juce::uint8) e.velocity)
                                                 : juce::MidiMessage::noteOff (e.channel, e.note);
            m.setTimeStamp (std::round (tick));
            tracks[ch].addEvent (m);
        }
    };
    for (double ppq = 0.0; ppq < quarters - 1e-9; ppq += block / samplesPerQuarter)
    {
        t.ppq = ppq;
        const int n = (int) std::min ((double) block, std::ceil ((quarters - ppq) * samplesPerQuarter));
        events->clear();
        gen.process (t, settings, std::max (1, n), *events);
        collect (ppq);
    }
    stromscore::Transport stop;
    events->clear();
    gen.process (stop, settings, block, *events);   // alle Noten am Ende beenden
    collect (quarters);

    juce::MidiFile file;
    file.setTicksPerQuarterNote (tpq);
    juce::MidiMessageSequence conductor;
    conductor.addEvent (juce::MidiMessage::tempoMetaEvent (juce::roundToInt (60000000.0 / bpm)));
    conductor.addEvent (juce::MidiMessage::timeSignatureMetaEvent (juce::jlimit (1, 16, settings.meterNum), juce::jlimit (1, 16, settings.meterDen)));
    file.addTrack (conductor);
    // Eine Spur je eingestelltem Kanal, benannt nach den Ausgaengen darauf (z. B. "Fläche lang + Fläche kurz")
    for (int ch = 0; ch < 16; ++ch)
    {
        juce::StringArray names;
        for (int o = 0; o < stromscore::kNumOutputs; ++o)
            if (settings.channel[o] == ch + 1) names.add (outputNames()[o]);
        if (names.isEmpty()) continue;
        juce::MidiMessageSequence seq;
        seq.addEvent (juce::MidiMessage::textMetaEvent (3, names.joinIntoString (" + ") + " (Kanal " + juce::String (ch + 1) + ")"));
        seq.addSequence (tracks[ch], 0.0);
        seq.sort();
        seq.updateMatchedPairs();
        file.addTrack (seq);
    }
    const auto name = juce::String ("Stromscore ") + (settings.genre == stromscore::GenrePopRock ? "Pop-Rock" : "Score") + " " + juce::String (bars) + " Takte.mid";
    auto out = juce::File::getSpecialLocation (juce::File::tempDirectory).getChildFile ("Stromscore").getChildFile (name);
    out.getParentDirectory().createDirectory();
    out.deleteFile();
    if (auto stream = out.createOutputStream())
        file.writeTo (*stream);
    return out;
}

