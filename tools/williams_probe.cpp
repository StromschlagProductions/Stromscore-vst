#include "ScoreEngine.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#ifdef WILLIAMS_DIAGNOSTICS
namespace stromscore {struct ExecutionTestAccess {
 static void trace(Generator& g,const Settings& s,double ppq,int output,long long sample){
 const auto saved=g.cur;g.cur=&s;const auto at=execution::nominalAt(ppq,execution::Timing::groove,s.swing);const auto pos=g.locate(at);const auto plan=g.roleRhythm(pos,s);
 const auto& part=output==OutPadShort?plan.harmony:plan.bass;
 if(plan.source&&part.active&&part.at(at-pos.bar*16*musicaltime::sixteenth))std::cerr<<"R,"<<sample<<','<<plan.source->rhythm<<','<<plan.source->bassId<<','<<output<<'\n';g.cur=saved;
 }
};}
#endif
#ifdef OCTATONIC_DIAGNOSTICS
namespace stromscore {struct ExecutionTestAccess {
 static void traceOct(const Generator& original,const Settings& s,long long sample,int output,int pitch){
  auto g=original;g.cur=&s;
  const auto context=g.modalContextFor(s);if(context.mode!=composition::Mode::octatonic||context.status!=composition::ModalStatus::unique)return;
  const auto at=execution::nominalAt(sample/28800.,execution::Timing::groove,s.swing);const auto pos=g.locate(at);const auto h=g.motifHarmonyAt(at,s);
  unsigned mask=0;for(int i=0;i<kShapes[h.chord.type].n;++i)mask|=composition::pitchBit(s.key+h.chord.root+kShapes[h.chord.type].iv[i]);
  if(mask&composition::pitchBit(pitch))return;
  const auto plan=g.motifOccurrence(at,pos,s,output,true);const int i=plan.figure.passingIndex;
  long long targetAt=-1;int target=-1;
  if(i>=0&&i+1<plan.figure.count&&std::abs(std::llround(execution::quarters(plan.begin+plan.figure.notes[i].at,execution::Timing::groove,s.swing)*28800.)-sample)<=1&&plan.base+plan.figure.notes[i].interval==pitch){
   targetAt=std::llround(execution::quarters(plan.begin+plan.figure.notes[i+1].at,execution::Timing::groove,s.swing)*28800.);target=plan.base+plan.figure.notes[i+1].interval;
  }
  std::cerr<<"O,"<<sample<<','<<output<<','<<pitch<<','<<context.mask<<','<<mask<<','<<targetAt<<','<<target<<','<<g.voice(output).motif.material(g.motifCatalog).identity<<'\n';
 }
};}
#endif
#ifdef WILLIAMS_MOTIF_DIAGNOSTICS
namespace stromscore {struct ExecutionTestAccess {
 static void traceMotif(const Generator& original,const Settings& s,long long sample,int output,int pitch){
  auto g=original;g.cur=&s;const auto at=execution::nominalAt(sample/28800.,execution::Timing::groove,s.swing);const auto pos=g.locate(at);
  const auto& m=g.voice(output).motif.material(g.motifCatalog);const auto plan=g.motifOccurrence(at,pos,s,output,true);
  const auto h=g.motifHarmonyAt(at,s);const auto allowed=g.motifPitchMask(h.chord,s,output);
  bool planned=false;auto local=pos;if(m.complete){local.phraseStartTime=plan.begin;local.phraseEndTime=plan.end;}
  for(int i=0;i<(plan.figure.count?plan.figure.count:m.complete?m.count:8);++i){
   const auto note=g.planMotifNote(i,local,s,output,m.complete?&m:nullptr,plan.varied,&plan);
   if(note.valid&&note.pitch+12*g.octaveOf(output)==pitch&&std::abs(std::llround(execution::quarters(local.phraseStartTime+note.at,execution::Timing::groove,s.swing)*28800.)-sample)<=1)planned=true;
  }
  std::cerr<<"M,"<<sample<<','<<output<<','<<m.vocabularyId<<','<<m.identity<<','<<m.complete<<','<<m.count<<','<<plan.introduction<<','<<static_cast<int>(plan.figure.variation)<<','<<plan.begin.value<<','<<plan.end.value<<','<<plan.figure.count<<','<<pitch<<','<<allowed<<','<<planned<<'\n';
 }
};}
#endif
#ifdef ACTIVITY_DIAGNOSTICS
namespace stromscore {struct ExecutionTestAccess {
 static void admission(Generator& g,const Settings& s,long long sample){
  const auto saved=g.cur;g.cur=&s;const auto pos=g.locate(g.nowTime);const auto* binding=g.layerBinding(s);
  if(binding)for(int i=0;i<s.policy.layers.count;++i){const auto& source=s.policy.layers.figures[i];const int output=static_cast<int>(source.part);const char* reason="eligible";
   if(!g.on[kOutputLayer[output]])reason="inactive";
   else if(!g.layerOwns(output,s))reason="manual";
   else if(!g.layerRoute(output,s))reason="route";
   else if((output==OutBassLong||output==OutBassShort)&&binding->bassMode!=0)reason="source_bass_absent_or_entry";
   else if(s.x<source.xLow||s.x>source.xHigh)reason="source_x_domain";
   else {bool durations=true,range=true;const auto cap=outputCatalog(s)[output].track.instrument;
    const auto begin=g.sceneTime+source.period*std::max<int64_t>(0,(g.nowTime-g.sceneTime)/source.period);int placement=0;
#ifdef ACTIVITY_PLACEMENT
    const bool fits=g.layerFits(source,begin,s,output,&placement);
#else
    const bool fits=g.layerFits(source,begin,s,output);
#endif
    for(int j=0;j<source.count;++j){const auto& hit=source.attacks[j];durations&=hit.duration>=cap.minDuration&&hit.duration<=cap.maxDuration;
     if(hit.reference!=composition::PitchReference::chord){const auto at=begin+hit.at;const auto c=g.chordFor(g.locate(at),kOutputLayer[output],s);const int pitch=g.layerPitch(hit,c,s,output,at)+12*g.octaveOf(output)+placement;range&=pitch>=cap.range.low&&pitch<=cap.range.high;}}
    if(!durations)reason="duration";else if(!range)reason="register";
    else if(!fits)reason="whole_context_register_slash_intent_or_polyphony";
    else if(source.group&&source.group!=g.layerGroup)reason="other_rhythm_group";
   }
   const auto& use=g.layerUses[output];if(use.source==&source)reason="selected";
   std::cerr<<"D,"<<sample<<','<<output<<','<<source.reference<<','<<reason<<'\n';
  }
  if(layerStrategyForAudit(s))for(int output:{OutCounter,OutMelody})for(int i=0;i<s.policy.authoredCount;++i){auto local=s;const auto& source=s.policy.authoredSources[i];local.policy.authoredSources=&source;local.policy.authoredCount=1;
   const auto& m=g.voice(output).motif.material(g.motifCatalog);const char* reason="harmonic_register_window_or_proximity";
   if(!g.on[kOutputLayer[output]])reason="inactive";
   else if(m.count&&m.vocabularyId!=static_cast<unsigned>(source.id))reason="established_other_material";
   else if(g.authoredMotif(pos,local,output).source)reason="eligible";
   std::cerr<<"D,"<<sample<<','<<output<<",HE-M"<<(source.id%100<10?"0":"")<<source.id%100<<','<<reason<<'\n';
  }
  g.cur=saved;
 }
 static void matched(const Generator& original,const Settings& s,long long sample,int output,int pitch){
  auto g=original;g.cur=&s;const auto at=musicaltime::fromQuarters(sample/28800.);const auto pos=g.locate(at);
  const auto& memory=g.voice(output).motif.material(g.motifCatalog);auto occurrence=g.motifOccurrence(at,pos,s,output,true);auto local=pos;
  int id=0;uint64_t identity=0;
  if(memory.vocabularyId&&(!memory.complete||occurrence.active)){
   if(memory.complete){local.phraseStartTime=occurrence.begin;local.phraseEndTime=occurrence.end;}
   for(int i=0;i<8;++i){const auto n=g.planMotifNote(i,local,s,output,memory.complete?&memory:nullptr,occurrence.varied,&occurrence);
    if(n.valid&&local.phraseStartTime+n.at==at&&n.pitch+12*g.octaveOf(output)==pitch){id=static_cast<int>(memory.vocabularyId);identity=memory.identity;}}
  }
  if(output==OutCounter){const auto handoff=g.playableMelodyHandoff(at,pos,s,true);if(handoff.plan.active)if(const auto* source=g.motifCatalog.find(handoff.plan.reference.material)){
   const auto first=source->notes[handoff.plan.first].at;for(int i=0;i<handoff.plan.count;++i){const auto& n=source->notes[handoff.plan.first+i];
    if(handoff.origin+handoff.plan.begin+n.at-first==at&&handoff.base+n.interval==pitch){id=static_cast<int>(source->vocabularyId);identity=source->identity;}}
  }}
  if(id>=82001&&id<=82057)std::cerr<<"A,"<<sample<<','<<output<<','<<id<<','<<identity<<','<<pitch<<'\n';
 }
 static bool layerStrategyForAudit(const Settings& s){return s.policy.layers.enabled&&s.policy.authoredSources;}
};}
#endif
using namespace stromscore;
int main(int argc,char** argv){
 if(argc<7)return 2;Settings s;s.profile=static_cast<composition::ProfileId>(std::atoi(argv[1]));const int path=std::atoi(argv[2]),mode=std::atoi(argv[3]),block=std::atoi(argv[4]),bars=std::atoi(argv[5]);s.genre=std::atoi(argv[6]);
 s.policy=composition::policyForContext(s.profile,s.genre==GenreScore);s.key=2;s.variation=argc>7?std::atoi(argv[7]):1;s.scene=false;s.sceneBars=0;s.drive=false;s.melody=mode==1||mode==3;s.mute[kGegenstimme]=mode==0||mode==1;s.melodyMotif=s.motif=true;s.stichFixed=true;
 const float xyz[][3]={{.15f,.2f,.2f},{.15f,.25f,.8f},{.15f,.85f,.2f},{.15f,.85f,.85f},{.85f,.2f,.2f},{.85f,.25f,.8f},{.85f,.85f,.2f},{.85f,.85f,.85f},{.5f,.5f,.5f},{.2f,.3f,1.f},{.2f,.9f,1.f}};
 if(path<11){s.x=xyz[path][0];s.y=xyz[path][1];s.z=xyz[path][2];}
 if(path>=100){const int index=path-100;const auto& w=wendungAt(s.genre,index,s.profile);s.x=w.x;s.y=w.y;s.z=w.z;s.variety=0;bool found=argc>20&&std::atoi(argv[20])&&Generator::pick(s,0)==index;
  for(int v=1;v<=16&&!found;++v){s.variation=v;if(Generator::pick(s,0)==index){found=true;break;}}if(!found)return 4;}
 if(argc>23){s.x=std::atof(argv[21]);s.y=std::atof(argv[22]);s.z=std::atof(argv[23]);s.variety=0;}
 if(argc>8&&std::atoi(argv[8])){s.padPattern=PadPulse;s.bassPattern=BassQuarter;}
 if(argc>9)s.follow[kBass]=s.follow[kFlaeche]=std::atoi(argv[9])!=0;
 if(argc>10)s.swing=std::atof(argv[10]);if(argc>11){s.meterNum=std::atoi(argv[11]);s.meterDen=std::atoi(argv[12]);}
 if(argc>14)s.arpFigure=std::atoi(argv[14]);if(argc>15)s.arpRate=std::atoi(argv[15]);
 if(argc>16)s.key=std::atoi(argv[16]);if(argc>17)s.seed=std::atoi(argv[17]);
 if(argc>19){int mask=std::atoi(argv[19]);for(int l=0;l<kNumLayers;++l)s.mute[l]=s.mute[l]||((mask>>l)&1);}
 #ifdef LAYER_DIAGNOSTICS
 std::cerr<<"S,"<<s.variation<<','<<s.x<<','<<s.y<<','<<s.z<<'\n';
#endif
 // Optional offline audit controls; absent arguments preserve all existing probes.
 if(argc>24){const int routing=std::atoi(argv[24]);if(routing==1||routing==2)s.channel[OutBassShort]=s.channel[OutBassLong];if(routing==2)s.channel[OutPadShort]=s.channel[OutPadLong];if(routing==3){s.rangeOn[1]=true;s.rangeLo[1]=36;s.rangeHi[1]=60;}if(routing==4)s.channel[OutBassShort]=s.channel[OutBassLong]=s.channel[OutArp];if(routing==5||routing==6){s.rangeOn[1]=true;s.rangeLo[1]=24;s.rangeHi[1]=67;s.octave[kBass]=-2;if(routing==6)s.channel[OutBassShort]=s.channel[OutBassLong];}}
 if(argc>25)s.variety=std::atof(argv[25]);
 if(argc>26)s.octave[kArp]=std::atoi(argv[26]);
 if(argc>28){s.rangeOn[2]=std::atoi(argv[27])>=0;s.rangeLo[2]=std::atoi(argv[27]);s.rangeHi[2]=std::atoi(argv[28]);}
 if(argc>29)s.follow[kArp]=std::atoi(argv[29])!=0;
 Generator g;Transport t;t.playing=true;t.bpm=argc>18?std::atof(argv[18]):100;
 const double samplesPerQuarter=48000.*60/t.bpm;EventList es;long long total=static_cast<long long>(bars*4.*s.meterNum/s.meterDen*samplesPerQuarter);int last=-2;
 for(long long at=0;at<total;){
  if((path==11||path==12)&&at%7200==0){double phase=at/samplesPerQuarter/(path==11?64:8);s.x=.5+.4*std::sin(phase);s.y=.65+.25*std::sin(phase*.7);s.z=.5+.45*std::cos(phase*.8);}
  if(path==14&&at%7200==0)s.y=.2f*std::max(0.,1.-at/samplesPerQuarter/16.);
  const int n=static_cast<int>(std::min<long long>({block,total-at,7200-at%7200}));t.ppq=at/samplesPerQuarter;
  if(argc>13&&std::atoi(argv[13])){
   t.playing=!(at>=total/4&&at<total/4+7200);
   if(at>=total/2)t.ppq-=total/2/samplesPerQuarter;
   if(at>=total*3/4)t.ppq+=8.125;
  }
  es.clear();g.process(t,s,n,es);if(es.overflow)return 3;
#ifdef ACTIVITY_DIAGNOSTICS
  if(at%static_cast<long long>(16*4*samplesPerQuarter)==0)ExecutionTestAccess::admission(g,s,at);
#endif

#ifdef DARK_SYNTH_DIAGNOSTICS
  if(at%static_cast<long long>(4*samplesPerQuarter)==0){
   for(const auto& use:g.inspectSequences())if(use.source)std::cerr<<"J,"<<at<<",0,"<<use.source->reference<<'\n';
   for(int output:{OutTupfer,OutMelody}){const auto& plan=g.inspectFigureEvent(output);if(plan.ready)std::cerr<<"J,"<<at<<','<<output<<','<<plan.figure.id<<'\n';}
  }
#endif
  if(g.wendung()!=last){last=g.wendung();std::cerr<<"H,"<<at<<','<<(last<0?-1:static_cast<int>(wendungAt(s.genre,last,s.profile).id))<<'\n';}
  for(int i=0;i<es.size;++i){const auto& e=es.events[i];std::cout<<at+e.offset<<','<<int(e.out)<<','<<int(e.channel)<<','<<int(e.note)<<','<<int(e.velocity)<<','<<int(e.type)<<'\n';
#ifdef LAYER_DIAGNOSTICS
   if(!e.type&&e.velocity&&(e.out==OutMelody||e.out==OutCounter)){const auto& m=g.inspectMotif(e.out);std::cerr<<"P,"<<at+e.offset<<','<<int(e.out)<<','<<m.vocabularyId<<','<<m.identity<<','<<m.count<<','<<m.complete<<'\n';}
#ifdef ACTIVITY_DIAGNOSTICS
   if(!e.type&&e.velocity&&(e.out==OutMelody||e.out==OutCounter))ExecutionTestAccess::matched(g,s,at+e.offset,e.out,e.note);
#endif
   if(!e.type&&e.velocity){const auto& use=g.inspectLayers()[e.out];if(use.source)std::cerr<<"L,"<<at+e.offset<<','<<int(e.out)<<','<<use.source->reference<<','<<use.origin.value<<'\n';}
#endif
#ifdef DARK_SYNTH_DIAGNOSTICS
#ifdef STROMSCORE_DIAGNOSTIC_EVENTS
   if(!e.type&&e.velocity)std::cerr<<"C,"<<at+e.offset<<','<<e.diagnosticHarmony<<','<<e.diagnosticSource<<','<<int(e.out)<<','<<int(e.note)<<','<<int(e.velocity)<<'\n';
#endif
   if(!e.type&&e.velocity&&(e.out==OutTupfer||e.out==OutMelody)){
    const auto& event=g.inspectFigureEvent(e.out);const auto& m=g.inspectMotif(e.out);
    if(event.ready){auto use=event.use();const auto nominal=execution::nominalAt((at+e.offset)/samplesPerQuarter,execution::Timing::groove,s.swing);
     if(use.index(nominal)>=0){int operation=0;
      if(event.replyTo>=0)operation=event.figure.id-4300;
      else if(e.out==OutTupfer&&m.complete&&m.vocabularyId==static_cast<unsigned>(event.figure.id)){
       if(event.figure.count<m.count)operation=7;
       else{bool adapted=false;for(int n=0;n<m.count;++n)adapted|=event.figure.pitches[n]-event.figure.pitches[0]!=m.notes[n].interval||event.figure.attacks[n].duration!=m.notes[n].length;
        if(adapted)operation=5;else if((event.base+event.figure.pitches[0]+12*s.octave[kAkzent]-m.origin+120)%12)operation=6;}
      }
      std::cerr<<"E,"<<at+e.offset<<','<<int(e.out)<<','<<event.figure.id<<','<<m.identity<<','<<m.count<<','<<m.complete<<','<<event.base<<','<<event.replyTo<<','<<operation<<','<<event.begin.value<<','<<event.end().value<<'\n';}}
   }
   if(at+e.offset==at)for(int slot=0;slot<3;++slot){const auto& use=g.inspectSequences()[slot];if(use.source)std::cerr<<"J,"<<at<<','<<slot<<','<<use.source->reference<<'\n';}
#endif
#ifdef SEQUENCE_DIAGNOSTICS
   if(e.type==0&&e.velocity&&(e.out==OutBassShort||e.out==OutArp||e.out==OutCounter)){
    const auto& use=g.inspectSequences()[e.out==OutBassShort?0:e.out==OutArp?1:2];
    if(use.source)std::cerr<<"Q,"<<at+e.offset<<','<<int(e.out)<<','<<use.source->reference<<','<<composition::sequenceIdentity(*use.source)<<','<<use.origin.value<<','<<use.base<<'\n';}
#endif
#ifdef WILLIAMS_MOTIF_DIAGNOSTICS
   if(e.type==0&&e.velocity&&(e.out==OutCounter||e.out==OutMelody))ExecutionTestAccess::traceMotif(g,s,at+e.offset,e.out,e.note);
#endif
#ifdef OCTATONIC_DIAGNOSTICS
   if(e.type==0&&e.velocity&&(e.out==OutCounter||e.out==OutMelody))ExecutionTestAccess::traceOct(g,s,at+e.offset,e.out,e.note);
#endif
#ifdef WILLIAMS_DIAGNOSTICS
   if(e.type==0&&e.velocity&&e.out<=OutBassShort&&g.wendung()>=0)std::cerr<<"A,"<<at+e.offset<<','<<static_cast<int>(wendungAt(s.genre,g.wendung(),s.profile).id)<<','<<int(e.out)<<'\n';
   if(e.type==0&&e.velocity&&(e.out==OutPadShort||e.out==OutBassShort||e.out==OutBassLong))ExecutionTestAccess::trace(g,s,(at+e.offset)/28800.,e.out,at+e.offset);
#endif
  }at+=n;
 }
 t.playing=false;es.clear();g.process(t,s,block,es);for(int i=0;i<es.size;++i){auto e=es.events[i];std::cout<<total+e.offset<<','<<int(e.out)<<','<<int(e.channel)<<','<<int(e.note)<<','<<int(e.velocity)<<','<<int(e.type)<<'\n';}
}
