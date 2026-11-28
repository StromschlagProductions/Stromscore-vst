// Automatic APVTS production: no forced source index and no injected layer plans.
static int testHerrmannArQuietProcessor(const char* report)
{
 using namespace stromscore;
 struct Case {float x,y,z;int reg,bars,voices,variation;float variety;};std::vector<Case> cases;
 const float low[]={0,.02f,.05f,.08f,.1f,.12f,.15f,.2f};
 for(float x:low)for(float y:low)for(int reg:{0,2})cases.push_back({x,y,x,reg,8,0,3,.5f});
 const float positions[][3]={{.5f,.85f,.8f},{.15f,.45f,.8f},{.85f,.85f,.85f},{.5f,.5f,.75f},{.15f,.25f,.8f},{.85f,.25f,.8f},{.5f,1,1},{.5f,.7f,.4f}};
 for(const auto& xyz:positions)for(int reg=0;reg<3;++reg)for(int voices=0;voices<2;++voices)
  cases.push_back({xyz[0],xyz[1],xyz[2],reg,64,voices,voices?9:3,reg*.5f});
 std::ofstream log;if(report)log.open(report);int id=0,totalArp=0;
 for(const auto& c:cases){StromscoreProcessor q;FakeHost host;host.bpm=100;host.numerator=4;host.denominator=4;q.setPlayHead(&host);q.prepareToPlay(48000,512);
  setParam(q,"komponist",2);setParam(q,"aufbau",0);setParam(q,"szenenLaenge",0);setParam(q,"fahrt",0);setParam(q,"key",2);
  setParam(q,"faerbung",c.x);setParam(q,"intensitaet",c.y);setParam(q,"unruhe",c.z);setParam(q,"variation",static_cast<float>(c.variation));setParam(q,"abwechslung",c.variety);
  setParam(q,"melodie",static_cast<float>(c.voices));setParam(q,"mute5",c.voices?0.f:1.f);
  const int channel=id%2?12:5;setParam(q,"kanal5",static_cast<float>(channel-1));
  if(c.reg){setParam(q,"umfang3",1);setParam(q,"tief3",60);setParam(q,"hoch3",86);setParam(q,"oct3",c.reg==2?1.f:2.f);
   setParam(q,"oct2",0);setParam(q,"umfang2",1);setParam(q,"tief2",24);setParam(q,"hoch2",67);}
  if(c.reg==2){setParam(q,"oct1",1);setParam(q,"umfang1",1);setParam(q,"tief1",48);setParam(q,"hoch1",84);}
  using Row=std::tuple<long long,int,int,int,int>;std::vector<Row> live,exported;
  auto add=[](std::vector<Row>& rows,const juce::MidiMessage& m,long long tick){if(m.isNoteOnOrOff())rows.emplace_back(tick,m.isNoteOn()?1:0,m.getChannel(),m.getNoteNumber(),m.isNoteOn()?m.getVelocity():0);};
  auto file=q.renderMidiFile(c.bars);auto stream=file.createInputStream();juce::MidiFile smf;CHECK(stream&&smf.readFrom(*stream));
  for(int tr=0;tr<smf.getNumTracks();++tr)for(int i=0;i<smf.getTrack(tr)->getNumEvents();++i){const auto& m=smf.getTrack(tr)->getEventPointer(i)->message;add(exported,m,std::llround(m.getTimeStamp()));}
  juce::AudioBuffer<float> audio(2,512);juce::MidiBuffer midi;midi.ensureSize(65536);Counts ledger;std::map<int,int> counts;const int end=c.bars*115200;
  for(int at=0;at<end;at+=512){host.ppq=at/28800.;midi.clear();{NoAllocations cpp;NoCHeap heap;q.processBlock(audio,midi);}collect(midi,ledger);
   for(auto e:midi){const auto m=e.getMessage();add(live,m,std::llround((at+e.samplePosition)/30.));if(m.isNoteOn()){++counts[m.getChannel()];if(c.reg&&m.getChannel()==channel)CHECK(m.getNoteNumber()>=60&&m.getNoteNumber()<=86);}}}
  host.playing=false;midi.clear();q.processBlock(audio,midi);collect(midi,ledger);for(auto e:midi)add(live,e.getMessage(),c.bars*3840);
  std::sort(live.begin(),live.end());std::sort(exported.begin(),exported.end());CHECK(live==exported);CHECK(!ledger.broken&&ledger.ons==ledger.offs);
#ifndef STROMSCORE_HE2_BASELINE
  if(c.y<.1f)CHECK(counts[1]>0);
#endif
  totalArp+=counts[channel];if(log){log<<id<<','<<c.x<<','<<c.y<<','<<c.z<<','<<c.reg<<','<<c.bars<<','<<channel;for(int ch=1;ch<=16;++ch)log<<','<<counts[ch];log<<'\n';}file.deleteFile();++id;
 }
#ifndef STROMSCORE_HE2_BASELINE
 CHECK(totalArp>0);
#endif
 // Real running-host transitions, including the user's register, descending
 // intensity, profile changes, mute/solo, manual control, seeks and restart.
 {StromscoreProcessor q;FakeHost host;host.bpm=100;host.numerator=4;host.denominator=4;q.setPlayHead(&host);q.prepareToPlay(48000,512);
  setParam(q,"aufbau",0);setParam(q,"szenenLaenge",0);setParam(q,"fahrt",0);setParam(q,"key",2);setParam(q,"variation",3);setParam(q,"abwechslung",.5f);
  setParam(q,"umfang3",1);setParam(q,"tief3",60);setParam(q,"hoch3",86);setParam(q,"oct2",0);setParam(q,"umfang2",1);setParam(q,"tief2",24);setParam(q,"hoch2",67);
  const int profiles[]={2,2,0,1,3,2,2,2,2,2,2,2};Counts ledger;double base=0;int heardArp=0;
  juce::AudioBuffer<float> audio(2,512);juce::MidiBuffer midi;midi.ensureSize(65536);
  for(int phase=0;phase<12;++phase){const bool quiet=phase==0||(phase>=2&&phase<=5);setParam(q,"komponist",static_cast<float>(profiles[phase]));setParam(q,"faerbung",quiet?0.f:.5f);setParam(q,"intensitaet",quiet?0.f:.85f);setParam(q,"unruhe",quiet?0.f:.8f);
   setParam(q,"mute3",phase==8?1.f:0.f);setParam(q,"solo2",phase==9?1.f:0.f);setParam(q,"arpFigure",phase==10?1.f:0.f);setParam(q,"arpRate",phase==10?3.f:0.f);setParam(q,"follow3",phase==10?0.f:1.f);
   int arp=0,soundingPad=0;const int end=64*115200;
   for(int at=0;at<end;at+=512){host.ppq=base+at/28800.;if(phase==6&&at>=end/2)host.ppq-=16.125;if(phase==7)setParam(q,"intensitaet",.2f*std::max(0.f,1.f-at/460800.f));
    midi.clear();{NoAllocations cpp;NoCHeap heap;q.processBlock(audio,midi);}collect(midi,ledger);for(auto e:midi)if(e.getMessage().isNoteOn()&&e.getMessage().getChannel()==5){CHECK(e.getMessage().getNoteNumber()>=60&&e.getMessage().getNoteNumber()<=86);++arp;}
    for(const auto& n:ledger.open)if(n.first.first==1&&n.second>0)++soundingPad;
   }
#ifndef STROMSCORE_HE2_BASELINE
   if(quiet&&profiles[phase]==2)CHECK(soundingPad>0);
#endif
   if(phase==8||phase==9)CHECK(arp==0);heardArp+=arp;CHECK(!ledger.broken);base+=256;
   if(phase==5){host.playing=false;midi.clear();q.processBlock(audio,midi);collect(midi,ledger);CHECK(ledger.ons==ledger.offs);host.playing=true;}
  }
  host.playing=false;midi.clear();q.processBlock(audio,midi);collect(midi,ledger);CHECK(!ledger.broken&&ledger.ons==ledger.offs);CHECK(heardArp>0);
 }
 std::cout<<"Herrmann AR/quiet real processor: "<<id<<" automatic cases, balanced live/export; AR note-ons "<<totalArp<<"\n";return 0;
}
