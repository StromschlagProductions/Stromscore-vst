#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "realtime_probe.h"
#include <atomic>
#include <cmath>
#include <memory>
struct ProbeHost final:juce::AudioPlayHead {bool playing=true;double ppq=0;juce::Optional<PositionInfo>getPosition()const override{PositionInfo p;p.setIsPlaying(playing);p.setPpqPosition(ppq);p.setBpm(100.);p.setTimeSignature(TimeSignature{4,4});return p;}};
static void parameter(StromscoreProcessor& p,const char* id,float value){auto* a=p.apvts.getParameter(id);if(!a)std::abort();a->setValueNotifyingHost(a->convertTo0to1(value));}
struct ProbeStopTimer:juce::Timer {std::atomic<int>& done;int count;ProbeStopTimer(std::atomic<int>& d,int c):done(d),count(c){startTimer(10);}void timerCallback()override{if(done>=count){stopTimer();juce::MessageManager::getInstance()->stopDispatchLoop();}}};
int main(int argc,char**argv){juce::ScopedJuceInitialiser_GUI init;
 const int profile=argc>1?std::atoi(argv[1]):5,genre=argc>2?std::atoi(argv[2]):0,block=argc>3?std::atoi(argv[3]):128,scenario=argc>4?std::atoi(argv[4]):3,bars=argc>5?std::atoi(argv[5]):64,instances=argc>6?std::atoi(argv[6]):1,parallel=argc>7?std::atoi(argv[7]):0,gui=argc>8?std::atoi(argv[8]):0;
 struct Part{StromscoreProcessor p;ProbeHost host;juce::AudioBuffer<float> audio;juce::MidiBuffer midi;rtprobe::Hash hash;rtprobe::Series cpu,wall;std::unique_ptr<juce::AudioProcessorEditor> editor;Part(int n):audio(2,n){midi.ensureSize(65536);}};
 std::vector<std::unique_ptr<Part>> parts;for(int i=0;i<instances;++i){parts.emplace_back(new Part(block));auto& q=*parts.back();q.p.setPlayHead(&q.host);q.p.prepareToPlay(48000,block);parameter(q.p,"komponist",static_cast<float>(profile));parameter(q.p,"genre",static_cast<float>(genre));parameter(q.p,"key",2);parameter(q.p,"variation",3);parameter(q.p,"melodie",1);parameter(q.p,"motiv",1);parameter(q.p,"melodieMotiv",1);parameter(q.p,"aufbau",0);parameter(q.p,"fahrt",0);parameter(q.p,"szenenLaenge",0);if(gui){q.editor.reset(q.p.createEditor());q.editor->addToDesktop(0);q.editor->setVisible(true);}}
 const int64_t total=static_cast<int64_t>(bars)*115200;const size_t count=(total+block-1)/block;rtprobe::Series batchCpu,batchWall;batchCpu.values.reserve(count);batchWall.values.reserve(count);
 for(auto& q:parts){q->cpu.values.reserve(count);q->wall.values.reserve(count);}
 auto update=[&](Part& q,int64_t at){const double u=at/28800.;float x=scenario==0?0:scenario==1?.2f:.8f,y=scenario==0?0:.8f,z=scenario==0?0:scenario==1?.9f:.8f;
  if(scenario==3){x=.5f+.48f*std::sin(u*.71);y=.6f+.39f*std::sin(u*.53);z=.5f+.48f*std::cos(u*.91);}q.host.playing=true;q.host.ppq=u;
  if(scenario==4){int phase=static_cast<int>(u/16)%4;q.host.playing=phase!=1;if(phase==2)q.host.ppq=std::fmod(u,16.);if(phase==3)q.host.ppq=u+8.125;}
  if(scenario==5)parameter(q.p,"komponist",static_cast<float>((profile+static_cast<int>(u/16))%6));
  if(scenario==6){x=.5f+.48f*std::sin(u*.3);y=.5f+.48f*std::cos(u*.4);z=.5f+.48f*std::sin(u*.7);parameter(q.p,"dynamikCc",static_cast<int>(u/8)%2?0.f:1.f);}
  parameter(q.p,"faerbung",x);parameter(q.p,"intensitaet",y);parameter(q.p,"unruhe",z);q.midi.clear();};
 auto collect=[&](Part&q,int64_t at){for(const auto e:q.midi){q.hash.add(at+e.samplePosition);q.hash.add(e.numBytes);for(int j=0;j<e.numBytes;++j)q.hash.add(e.data[j]);}};
 auto process=[&](Part&q){const double w=rtprobe::wallUs(),c=rtprobe::cpuUs();q.p.processBlock(q.audio,q.midi);q.cpu.values.push_back(rtprobe::cpuUs()-c);q.wall.values.push_back(rtprobe::wallUs()-w);};
 std::atomic<int> ready{0},done{0};std::atomic<bool> start{false};std::vector<std::thread> workers;
 if(parallel){for(auto& q:parts)workers.emplace_back([&,ptr=q.get()]{++ready;while(!start.load())std::this_thread::yield();const auto pacing=std::chrono::steady_clock::now();for(int64_t at=0;at<total;at+=block){update(*ptr,at);process(*ptr);collect(*ptr,at);if(gui)std::this_thread::sleep_until(pacing+std::chrono::microseconds((at+block)*1000000/48000));}++done;});while(ready<instances)std::this_thread::yield();start=true;
  if(gui){ProbeStopTimer timer(done,instances);juce::MessageManager::getInstance()->runDispatchLoop();}else while(done<instances)std::this_thread::sleep_for(std::chrono::milliseconds(1));for(auto& thread:workers)thread.join();
 }else{for(int64_t at=0;at<total;at+=block){for(auto& q:parts)update(*q,at);const double w=rtprobe::wallUs(),c=rtprobe::cpuUs();for(auto& q:parts)process(*q);batchCpu.values.push_back(rtprobe::cpuUs()-c);batchWall.values.push_back(rtprobe::wallUs()-w);for(auto& q:parts)collect(*q,at);}}
 const double budget=block*1e6/48000.;for(int i=0;i<instances;++i){auto& q=*parts[i];q.host.playing=false;q.midi.clear();q.p.processBlock(q.audio,q.midi);collect(q,total);
  std::cout<<"{\"profile\":"<<profile<<",\"genre\":"<<genre<<",\"block\":"<<block<<",\"scenario\":"<<scenario<<",\"bars\":"<<bars<<",\"instances\":"<<instances<<",\"instance\":"<<i<<",\"parallel\":"<<parallel<<",\"gui\":"<<gui<<",\"digest\":\""<<q.hash.value<<"\",\"budget_us\":"<<budget<<",\"cpu_us\":";q.cpu.print(budget);std::cout<<",\"wall_us\":";q.wall.print(budget);if(!parallel&&i==0){std::cout<<",\"batch_cpu_us\":";batchCpu.print(budget);std::cout<<",\"batch_wall_us\":";batchWall.print(budget);}std::cout<<"}\n";}
}
