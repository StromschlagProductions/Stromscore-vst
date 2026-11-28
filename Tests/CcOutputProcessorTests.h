static int testCcOutputProcessor()
{
 using namespace stromscore;int cases=0;
 auto controls=[](const juce::MidiBuffer& midi){std::map<std::pair<int,int>,int> result;for(auto e:midi){const auto m=e.getMessage();if(m.isController()&&!m.isAllNotesOff()){CHECK(!result.count({m.getChannel(),m.getControllerNumber()}));result[{m.getChannel(),m.getControllerNumber()}]=m.getControllerValue();}}return result;};
 for(int profile=0;profile<6;++profile)for(int genre=0;genre<2;++genre)for(bool playing:{false,true}){
  StromscoreProcessor q,independent;FakeHost host;host.playing=playing;q.setPlayHead(&host);q.prepareToPlay(48000,128);independent.prepareToPlay(48000,128);
  setParam(q,"aufbau",0);setParam(q,"intensitaet",.8f);setParam(q,"komponist",static_cast<float>(profile));setParam(q,"genre",static_cast<float>(genre));
  // Three destinations, shared by the nine outputs; mute does not remove a
  // configured controller destination from the global reset.
  for(int o=0;o<kNumOutputs;++o)setParam(q,("kanal"+std::to_string(o+1)).c_str(),static_cast<float>(o%3));
  for(int ch=1;ch<=16;++ch){setParam(q,("cc0Lo"+std::to_string(ch)).c_str(),92);setParam(q,("cc0Hi"+std::to_string(ch)).c_str(),98);setParam(q,("cc1Lo"+std::to_string(ch)).c_str(),30);setParam(q,("cc1Hi"+std::to_string(ch)).c_str(),40);}
  const auto saved=q.currentSettings();juce::AudioBuffer<float> audio(2,128);juce::MidiBuffer midi;midi.ensureSize(65536);
  auto block=[&](){midi.clear();{NoAllocations cpp;NoCHeap c;q.processBlock(audio,midi);}host.ppq+=128/24000.;};
  block();CHECK(controls(midi).empty());
  for(int toggle=0;toggle<3;++toggle){setParam(q,"dynamikCc",1);block();if(playing){auto values=controls(midi);for(int wait=0;values.empty()&&wait<256;++wait){block();values=controls(midi);}CHECK(!values.empty());for(auto item:values){CHECK(item.first.second==1||item.first.second==11);CHECK(item.second<=98);}}
   setParam(q,"dynamikCc",0);block();auto reset=controls(midi);CHECK(reset.size()==6);for(int ch=1;ch<=3;++ch){CHECK(reset[std::make_pair(ch,1)]==127);CHECK(reset[std::make_pair(ch,11)]==127);}block();CHECK(controls(midi).empty());}
  // Loading OFF over an active state has the same one-shot edge, even if the
  // preset flushes/reset the musical generator in this slice.
  juce::MemoryBlock offState;q.getStateInformation(offState);setParam(q,"dynamikCc",1);block();q.setStateInformation(offState.getData(),static_cast<int>(offState.getSize()));block();CHECK(controls(midi).size()==6);block();CHECK(controls(midi).empty());
  const auto after=q.currentSettings();for(int kind=0;kind<2;++kind)for(int ch=0;ch<16;++ch){CHECK(saved.ccLo[kind][ch]==after.ccLo[kind][ch]);CHECK(saved.ccHi[kind][ch]==after.ccHi[kind][ch]);}
  midi.clear();independent.processBlock(audio,midi);CHECK(controls(midi).empty());++cases;
 }
 // Last active assignments are restored if an OFF preset also changes mapping.
 {StromscoreProcessor q;FakeHost host;host.playing=false;q.setPlayHead(&host);q.prepareToPlay(48000,128);q.ccOut[0]=21;q.ccOut[1]=22;
  juce::AudioBuffer<float> audio(2,128);juce::MidiBuffer midi;setParam(q,"dynamikCc",1);q.processBlock(audio,midi);q.ccOut[0]=1;q.ccOut[1]=11;setParam(q,"dynamikCc",0);midi.clear();q.processBlock(audio,midi);auto reset=controls(midi);CHECK(reset.size()==18);for(auto item:reset){CHECK(item.first.second==21||item.first.second==22);CHECK(item.second==127);}}
 // Real button state and existing themed colours, including an already-open
 // editor observing APVTS/preset changes rather than a click-local flag.
 for(int theme=0;theme<2;++theme){StromscoreProcessor q;q.uiTheme=theme;std::unique_ptr<juce::AudioProcessorEditor> editor(q.createEditor());juce::TextButton* button=nullptr;
  std::function<void(juce::Component&)> find=[&](juce::Component& c){if(auto* b=dynamic_cast<juce::TextButton*>(&c);b&&b->getButtonText()=="MIDI / CC")button=b;for(auto* child:c.getChildren())find(*child);};find(*editor);CHECK(button&&!button->getToggleState());
  const auto off=button->findColour(juce::TextButton::buttonColourId),on=button->findColour(juce::TextButton::buttonOnColourId);CHECK(on!=off&&on.getRed()>on.getBlue());
  juce::MemoryBlock offState;q.getStateInformation(offState);setParam(q,"dynamikCc",1);for(int wait=0;!button->getToggleState()&&wait<100;++wait){juce::Thread::sleep(10);juce::Timer::callPendingTimersSynchronously();}CHECK(button->getToggleState());
  q.setStateInformation(offState.getData(),static_cast<int>(offState.getSize()));for(int wait=0;button->getToggleState()&&wait<100;++wait){juce::Thread::sleep(10);juce::Timer::callPendingTimersSynchronously();}CHECK(!button->getToggleState());
  setParam(q,"dynamikCc",1);editor.reset();editor.reset(q.createEditor());button=nullptr;find(*editor);CHECK(button&&button->getToggleState());
 }
 std::cout<<"CC output: "<<cases<<" profile/genre/transport cases, one-shot reset, ranges, presets, mapping, instances and both themes passed\n";return 0;
}
