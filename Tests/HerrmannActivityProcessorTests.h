// Normal APVTS/host production, not forced individual catalog slots.
static int testHerrmannActivityProcessor(const char* report)
{
 using namespace stromscore;std::ofstream log;if(report)log.open(report);int cases=0;
 for(int key=0;key<12;++key)for(int routing=0;routing<5;++routing){
  StromscoreProcessor q;FakeHost host;host.bpm=100;host.numerator=4;host.denominator=4;q.setPlayHead(&host);q.prepareToPlay(48000,512);
  setParam(q,"komponist",2);setParam(q,"aufbau",0);setParam(q,"szenenLaenge",0);setParam(q,"fahrt",0);setParam(q,"key",static_cast<float>(key));
  setParam(q,"faerbung",.5f);setParam(q,"intensitaet",.85f);setParam(q,"unruhe",.8f);setParam(q,"variation",3);setParam(q,"motiv",1);setParam(q,"melodie",1);
  if(routing==1||routing==2){setParam(q,"kanal4",2);if(routing==2)setParam(q,"kanal2",0);}
  if(routing==3||routing==4){setParam(q,"oct2",0);setParam(q,"umfang2",1);setParam(q,"tief2",24);setParam(q,"hoch2",67);if(routing==4)setParam(q,"kanal4",2);}
  using Row=std::tuple<long long,int,int,int,int>;std::vector<Row> live,exported;
  auto add=[](std::vector<Row>& rows,const juce::MidiMessage& m,long long tick){if(m.isNoteOnOrOff())rows.emplace_back(tick,m.isNoteOn()?1:0,m.getChannel(),m.getNoteNumber(),m.isNoteOn()?m.getVelocity():0);};
  auto file=q.renderMidiFile(64);auto stream=file.createInputStream();juce::MidiFile midi;CHECK(stream&&midi.readFrom(*stream));
  for(int tr=0;tr<midi.getNumTracks();++tr)for(int i=0;i<midi.getTrack(tr)->getNumEvents();++i){const auto& m=midi.getTrack(tr)->getEventPointer(i)->message;add(exported,m,std::llround(m.getTimeStamp()));}
  juce::AudioBuffer<float> audio(2,512);juce::MidiBuffer messages;messages.ensureSize(65536);Counts ledger;std::map<int,int> counts;
  const int total=64*4*28800;
  for(int at=0;at<total;at+=512){const int n=std::min(512,total-at);audio.setSize(2,n);host.ppq=at/28800.;messages.clear();{NoAllocations cpp;NoCHeap c;q.processBlock(audio,messages);}collect(messages,ledger);
   for(auto m:messages){add(live,m.getMessage(),std::llround((at+m.samplePosition)/30.));if(m.getMessage().isNoteOn())++counts[m.getMessage().getChannel()];}}
  host.playing=false;messages.clear();q.processBlock(audio,messages);collect(messages,ledger);for(auto m:messages)add(live,m.getMessage(),64*4*960);
  CHECK(!ledger.broken&&ledger.ons==ledger.offs);std::sort(live.begin(),live.end());std::sort(exported.begin(),exported.end());CHECK(live==exported);
  // Positive bass, not an artificial minimum density. Baseline shared routing
  // fails this despite normal bass in the identical distinct-channel case.
#ifndef STROMSCORE_ACTIVITY_BASELINE
  CHECK(counts[3]+counts[4]>0);
#endif
  if(log){log<<key<<','<<routing;for(int ch=1;ch<=9;++ch)log<<','<<counts[ch];log<<'\n';}
  file.deleteFile();++cases;
 }
 // The hearing-test register also survives real APVTS profile handovers and
 // host Stop/restart/seek. Future automation is not invented for the SMF export.
 {StromscoreProcessor q;FakeHost host;host.bpm=100;host.numerator=4;host.denominator=4;q.setPlayHead(&host);q.prepareToPlay(48000,512);
  setParam(q,"aufbau",0);setParam(q,"key",2);setParam(q,"faerbung",.5f);setParam(q,"intensitaet",.85f);setParam(q,"unruhe",.8f);setParam(q,"variation",3);
  setParam(q,"oct2",0);setParam(q,"umfang2",1);setParam(q,"tief2",24);setParam(q,"hoch2",67);
  juce::AudioBuffer<float> audio(2,512);juce::MidiBuffer midi;midi.ensureSize(65536);Counts ledger;int phase=0;
  for(int profile:{2,3,1,0,2}){setParam(q,"komponist",static_cast<float>(profile));int bass=0;host.playing=true;
   for(int at=0;at<8*115200;at+=512){host.ppq=phase*32+at/28800.;if(at>=4*115200)host.ppq-=8.125;midi.clear();{NoAllocations cpp;NoCHeap c;q.processBlock(audio,midi);}collect(midi,ledger);for(auto e:midi){const auto m=e.getMessage();if(m.isNoteOn()&&(m.getChannel()==3||m.getChannel()==4)){CHECK(m.getNoteNumber()>=24&&m.getNoteNumber()<=67);++bass;}}}
#ifndef STROMSCORE_ACTIVITY_BASELINE
   CHECK(bass>0);
#endif
   host.playing=false;midi.clear();q.processBlock(audio,midi);collect(midi,ledger);CHECK(!ledger.broken&&ledger.ons==ledger.offs);++phase;
  }
 }
 std::cout<<"Herrmann normal processor activity/live-export: "<<cases<<" cases passed\n";return 0;
}
