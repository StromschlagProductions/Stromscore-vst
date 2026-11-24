#include "TestSupport.h"
#include "ScoreEngine.h"
#include <type_traits>
#include <vector>
#include <tuple>
#include <map>
using namespace stromscore;
using namespace stromscore::composition;
using namespace stromscore::musicaltime;
using EventRow=std::tuple<int64_t,int,int,int,int,int>;
std::vector<EventRow> render(Settings s,int block)
{
 Generator g;EventList events;std::vector<EventRow> result;
 const int64_t total=16LL*s.meterNum*12000; // 120 BPM, /8; integral sample bar lengths.
 auto append=[&](int64_t at){for(int i=0;i<events.size;++i){auto e=events.events[i];result.emplace_back(at+e.offset,e.out,e.channel,e.note,e.velocity,e.type);}};
 for(int64_t at=0;at<total;)
 {
  const int size=static_cast<int>(std::min<int64_t>(block,total-at));Transport host;host.playing=true;host.ppq=at/24000.;
  events.clear();{NoAllocations guard;g.process(host,s,size,events);}CHECK(!events.overflow);append(at);at+=size;
 }
 Transport stop;events.clear();{NoAllocations guard;g.process(stop,s,512,events);}append(total);
 std::map<std::pair<int,int>,bool> held;
 for(const auto& row:result)
 {
  auto [at,o,ch,n,v,type]=row;if(type)continue;const auto key=std::make_pair(ch,n);
  if(v){CHECK(!held[key]);held[key]=true;}else{CHECK(held[key]);held[key]=false;}
 }
 for(const auto& item:held)CHECK(!item.second);
 return result;
}
int main()
{
 static_assert(std::is_same<decltype(BassPhrasePlan{}.notes[0].at),Tick>::value);
 static_assert(std::is_same<decltype(BassAttack{}.duration),Tick>::value);
 static_assert(std::is_same<decltype(LinePhrasePlan{}.breath),Tick>::value);
 static_assert(std::is_same<decltype(RhythmPlan::Onset{}.length),Tick>::value);
 static_assert(std::is_same<decltype(InstrumentCapabilities{}.maxDuration),Tick>::value);
 const Tick origin{960000000037LL}; // Deliberately not on the execution grid.
 BassPhraseRequest bass;bass.begin=origin;bass.middle=origin+8*quarter;bass.end=origin+16*quarter;
 bass.bass={48,53};bass.root={0,5};bass.chords={pitchBit(0)|pitchBit(3)|pitchBit(7),pitchBit(5)|pitchBit(9)|pitchBit(0)};
 bass.range={36,72};bass.modal=modalContext(modalMask(Mode::dorian,0),0,true);
 auto phrase=planBassPhrase(bass);CHECK(phrase.valid&&phrase.notes[0].at==origin);
 bool second=false;
 for(int i=0;i<phrase.count;++i)
 {
  const auto& n=phrase.notes[i];CHECK(n.at>=bass.begin&&n.at+n.length<=bass.end);
  CHECK((n.at-origin)%sixteenth==Tick{});if(n.at==bass.middle){second=true;CHECK(n.pitch==53);}
  if(i+1<phrase.count)CHECK(n.at+n.length<=phrase.notes[i+1].at);
  if(!n.passing)CHECK(bass.chords[n.at>=bass.middle?1:0]&pitchBit(n.pitch));
 }
 CHECK(second);auto bounded=bass;bounded.maxDuration=2*sixteenth;CHECK(planBassPhrase(bounded).valid);bounded.maxDuration-=Tick{1};CHECK(!planBassPhrase(bounded).valid);
 auto tooShort=bass;tooShort.maxDuration=sixteenth-Tick{1};CHECK(!planBassPhrase(tooShort).valid);
 // Instrument assumptions are independent PPQ bounds, with no implicit 240x conversion.
 Settings settings;const auto catalog=outputCatalog(settings);CHECK(validOutputs(catalog.data(),kNumOutputs));
 CHECK(catalog[OutPadLong].track.instrument.maxDuration==sixteenth*(1<<24));
 CHECK(catalog[OutBassShort].track.instrument.maxDuration==quarter);
 PlayingTrack track;track.id={5};track.roles=roleBit(MusicalRole::lead);track.style=PlayingStyle::sustained;
 track.instrument.pitch=PitchBehaviour::pitched;track.instrument.articulations=1;
 track.instrument.minDuration=Tick{37};track.instrument.maxDuration=Tick{721};
 RoleNeed need;need.minDuration=Tick{37};need.maxDuration=Tick{721};CHECK(suitable(track,need));
 need.minDuration=Tick{36};CHECK(!suitable(track,need));need.minDuration=Tick{37};need.maxDuration=Tick{722};CHECK(!suitable(track,need));
 for(int num:{3,5,7})
 {
  const auto bar=barLength(num,8);
  LinePhraseRequest line;line.begin=origin+bar/4;line.end=line.begin+4*bar;line.pulse=bar/4;
  line.pitches={60,64,67,71,72,76};line.count=6;line.goalPitchClass=0;line.notes=4;
  auto thought=planLinePhrase(line);CHECK(thought.valid&&thought.begin==line.begin&&thought.notes[0].begin==line.begin);
  CHECK(thought.breath==line.end-line.pulse&&thought.arrival==thought.breath-line.pulse);
  CHECK(thought.notes[thought.count-1].pitch==thought.goal&&thought.notes[thought.count-1].end==thought.breath);
  for(int i=0;i<thought.count;++i){auto n=thought.notes[i];CHECK(n.end>n.begin&&n.end<=thought.breath);}
  // Pattern masks/slot ordinals stay dimensionless; realised events use explicit PPQ subdivision.
  RhythmPlanRequest rhythm;rhythm.reference=0x5555;rhythm.movement=0x5555;rhythm.bar=1;
  rhythm.subdivision=bar/16;rhythm.minDuration=rhythm.subdivision;rhythm.maxDuration=2*rhythm.subdivision;
  auto plan=planRhythmicInterlock(rhythm,{});CHECK(plan.active&&plan.count==8);
  for(int i=0;i<plan.count;++i){auto n=plan.notes[i];CHECK(n.at>=Tick{}&&n.at+n.length<=bar);CHECK(plan.at(n.at)==&plan.notes[i]);if(i+1<plan.count)CHECK(n.at+n.length<=plan.notes[i+1].at);}
  rhythm.minDuration=rhythm.subdivision+Tick{1};CHECK(!planRhythmicInterlock(rhythm,{}).active);
  auto unsupported=bass;unsupported.barDuration=bar;CHECK(!planBassPhrase(unsupported).valid); // Existing 4/4-only musical strategy remains protected.
  // Actual odd-meter playback: fallback bass patterns, free lines, scenes, shared claims,
  // swing and both follow states; rendering must never introduce dangling physical notes.
  for(int genre:{GenreScore,GenrePopRock})for(bool follow:{false,true})
  {
   Settings s;s.genre=genre;s.meterNum=num;s.meterDen=8;s.custom=true;s.customChords[0]={0,Maj7,2};s.customChords[1]={5,Maj,1};s.customChords[2]={7,Dom7,1};
   s.key=0;s.y=.7f;s.z=.6f;s.motif=false;s.swing=.3f;s.follow[kBass]=follow;s.dynamics=true;
   s.scene=true;s.sceneBars=12;s.buildBars=4;s.entry=EntryAll;s.ending=EndFade;
   s.channel[OutArp]=s.channel[OutPadLong];
   const auto reference=render(s,512);
   for(int block:{127,8192})
   {
    const auto other=render(s,block);CHECK(other.size()==reference.size());
    for(size_t i=0;i<reference.size();++i){auto a=reference[i],b=other[i];CHECK(std::abs(std::get<0>(a)-std::get<0>(b))<=1);std::get<0>(a)=std::get<0>(b);CHECK(a==b);}
   }
  }
 }
 std::cout<<"PPQ bass/line plans, duration bounds, rhythmic windows and odd-meter shared MIDI claims passed\n";
}
