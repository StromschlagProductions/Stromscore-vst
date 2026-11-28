// Test-only immutable reference from b969932; never linked into the plugin.
inline std::array<composition::OutputDescription,kNumOutputs> referenceOutputCatalog(const Settings& s)
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
        if(sequenceStrategy(s)&&(o==OutArp||o==OutCounter||o==OutBassShort))
        { track.style=PlayingStyle::detached;track.roles=accompaniment;c.articulations=2;c.polyphony=1;
          c.minDuration=musicaltime::Tick{48};c.maxDuration=4*musicaltime::quarter; }
        if(sequenceStrategy(s)&&s.policy.sequences.development&&o==OutArp)c.maxDuration=36*musicaltime::quarter;
        if(sequenceStrategy(s)&&o==OutTupfer){c.minDuration=musicaltime::Tick{48};c.maxDuration=8*musicaltime::quarter;c.polyphony=1;}
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
