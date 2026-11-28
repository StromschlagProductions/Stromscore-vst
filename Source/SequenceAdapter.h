void prepareLeadEvent(musicaltime::Tick time,const Settings& s,int offset,EventList& out)
{
 using namespace composition;
 if(leadEvent.ready&&(time>=leadEvent.end()||!on[kMelodie]||!s.melodyMotif||!sequenceRoute(OutMelody,s))){releaseSequence(OutMelody,offset,out);leadEvent.ready=false;}
 if(!sequenceStrategy(s)||!s.policy.sequences.leads||!s.melodyMotif||!on[kMelodie]||!sequenceRoute(OutMelody,s))return;
 const auto slot=std::max<int64_t>(0,(time-sceneTime)/s.policy.sequences.eventSpacing);
 if(slot==leadEventSlot)return;leadEventSlot=slot;
 const auto& memory=voice(OutTupfer).motif;const auto& material=memory.material(motifCatalog);
 if(slot%4!=2)return;
 const auto begin=sceneTime+slot*s.policy.sequences.eventSpacing+4*musicaltime::quarter;
 if(time>begin)return;
 int exposition=0;for(int i=0;i<s.policy.sequences.eventCount;++i)if(static_cast<unsigned>(s.policy.sequences.events[i].id)==material.vocabularyId)exposition=s.policy.sequences.events[i].exposition;
 const auto chord=chordFor(locate(begin),kMelodie,s);float best=-1;FigureEventPlan chosen;
 for(int i=0;i<s.policy.sequences.leadCount;++i){const auto& source=s.policy.sequences.leads[i];
  // Explicit seed-to-full-figure relation. This does not activate a disabled HM.
  if(source.expansionOnly&&(!material.complete||memory.reference.value<0||source.id!=exposition))continue;
  const float xyz[]={s.x,layerY(s,kMelodie),s.z};float distance=0;for(int d=0;d<3;++d){const float delta=xyz[d]-(source.domains[d][0]+source.domains[d][1])*.5f;distance+=delta*delta;}
  for(int root:{0,chord.root})for(int shift:composition::figureOctaves){SequenceUse use{&source,begin,48+s.key+root+shift};if(!sequenceFits(use,begin,s,OutMelody))continue;
   const float score=(source.expansionOnly?1.3f:1.f)/(.12f+distance);if(score>best){best=score;chosen={source,begin,use.base,-1,true,false};}break;}
 }
 if(chosen.ready){releaseSequence(OutMelody,offset,out);leadEvent=chosen;
  if(chosen.figure.expansionOnly)voice(OutMelody).answer.adopt({memory.reference,slot,begin},motifCatalog);
  else voice(OutMelody).answer.clear(); // An independent chorale is not a derivative of an unrelated seed.
  if(figureEvent.ready&&figureEvent.begin>=begin&&!figureEvent.record)figureEvent.ready=false;
 }
}
void renderLeadEvent(musicaltime::Tick time,const Settings& s,int offset,EventList& out)
{
 if(!leadEvent.ready||!on[kMelodie]||!s.melodyMotif||time>=leadEvent.end())return;
 const auto use=leadEvent.use();const int i=use.index(time);if(i<0)return;
 if(!sequenceFits(use,leadEvent.begin,s,OutMelody)){leadEvent.ready=false;releaseSequence(OutMelody,offset,out);return;}
 const auto& hit=leadEvent.figure.attacks[i];const auto duration=composition::articulatedLength(hit.duration,hit.duration,s.melodyLegato);
 noteOn(OutMelody,leadEvent.base+leadEvent.figure.pitches[i],hit.velocity,time+duration,offset,out);
}
// Sparse tonal events share the scene's immutable motif catalog. The role plan
// explicitly chooses introduction, material recall or a reply to heard notes.
void prepareFigureEvent(musicaltime::Tick time,const Settings& s,int offset,EventList& out)
{
 using namespace composition;
 if(!sequenceStrategy(s)||!s.policy.sequences.events)return;
 auto& memory=voice(OutTupfer).motif;
 if(figureEvent.ready&&time>=figureEvent.end()){
  if(figureEvent.record){if(memory.draft.count==figureEvent.figure.count){memory.draft.vocabularyId=figureEvent.figure.id;memory.finish(motifCatalog);}else memory.clear();}
  figureEvent.ready=false;
 }
 if(!on[kAkzent]||sceneEnded||!sequenceRoute(OutTupfer,s)){
  if(figureEvent.ready){releaseSequence(OutTupfer,offset,out);if(figureEvent.record)memory.clear();}figureEvent={};return;
 }
 const auto window=s.policy.sequences.eventSpacing;
 const auto ordinal=std::max<int64_t>(0,(time-sceneTime)/window);
 if(figureEventSlot==ordinal)return;
 if(figureEvent.replyTo>=0&&time<figureEvent.replyEnd)return;
 if(figureEvent.ready&&time<figureEvent.end())return;
 figureEventSlot=ordinal;
 auto begin=sceneTime+window*ordinal+4*musicaltime::quarter;
 if(time>begin)return; // A cold seek has no invented played prefix.
 const auto chord=chordFor(locate(begin),kAkzent,s);
 float best=-1;FigureEventPlan chosen;
 auto admit=[&](const SequenceSource& source,int anchor,int reply,bool record,float preference){
  for(int shift:composition::figureOctaves){
   SequenceUse use{&source,begin,anchor+shift};if(!sequenceFits(use,begin,s,OutTupfer))continue;
   float score=preference;
   for(int i=0;i<numActive;++i)if(active[i].out==OutArp||active[i].out==OutCounter)
    if(std::abs(anchor+shift+source.pitches[0]+12*octaveOf(OutTupfer)-active[i].note)<5)score*=.75f;
   if(score>best){best=score;chosen={source,begin,anchor+shift,reply,true,record};}break;
  }
 };
 const auto& material=memory.material(motifCatalog);
 if(material.complete){
  // Reprise comes from the actual stored notes, not a fresh random seed.
  for(int i=0;i<s.policy.sequences.eventCount;++i){const auto& original=s.policy.sequences.events[i];if(static_cast<unsigned>(original.id)!=material.vocabularyId)continue;
   auto source=original;source.count=source.tones=material.count;
   for(int n=0;n<material.count;++n){const auto& note=material.notes[n];source.pitches[n]=original.pitches[0]+note.interval;source.attacks[n]={note.at,note.length,note.velocity};}
   source.period=material.cycleLength;
   // Whole transposition preserves rhythm and contour. A return can be silent if
   // this harmony does not support the remembered source-specific intent.
   for(int root:{0,chord.root})admit(source,48+s.key+root,-1,false,10.f);
   if(best<0){
    // Reuse the shared contour-preserving realization, with per-note intent
    // masks. F/U retain their recorded class; no arbitrary dissonance repair.
    const auto cap=outputDescription(s,OutTupfer).track.instrument;
    for(int root:{0,chord.root})for(int shift:composition::figureOctaves){
     if(best>=8.5f)break; // Maximum score: later equal placements cannot replace it.
     const int anchor=48+s.key+root+shift,oct=12*octaveOf(OutTupfer);
     const int preferred=anchor+source.pitches[0]+oct;
     if(preferred<0||preferred>127||preferred<cap.range.low||preferred>cap.range.high)continue;
     unsigned masks[10]{};musicaltime::Tick limits[10]{};int fixed[10];std::fill(std::begin(fixed),std::end(fixed),-1);
     auto figure=deriveMotif(material,MotifVariation::original);bool compatible=true;
     for(int n=0;n<material.count;++n){const auto pos=locate(begin+source.attacks[n].at);const auto c=chordFor(pos,kAkzent,s);
      limits[n]=std::min(source.attacks[n].duration,pos.chordEndTime-(begin+source.attacks[n].at));
      for(int pc=0;pc<12;++pc){auto trial=source;trial.pitches[n]=(pc-anchor-oct+120)%12;
       if((source.functions[n]=='F'||source.functions[n]=='U')&&composition::pitchBit(pc)!=composition::pitchBit(anchor+source.pitches[n]+oct))continue;
       if(sequencePitch(trial,n,c,s,anchor))masks[n]|=composition::pitchBit(pc);}
      compatible&=masks[n]!=0;
     }
     if(!compatible)continue;
     fixed[0]=preferred;
     const auto realized=realizeScoreMotif(figure,masks,limits,cap.range,cap.minDuration,cap.maxDuration,preferred,fixed);
     if(realized.base<0)continue;
     auto adapted=source;adapted.period={};
     for(int n=0;n<material.count;++n){adapted.pitches[n]=realized.base+realized.figure.notes[n].interval-anchor-oct;adapted.attacks[n].duration=realized.figure.notes[n].length;adapted.period=std::max(adapted.period,adapted.attacks[n].at+adapted.attacks[n].duration);}
     admit(adapted,anchor,-1,false,8.5f);
    }
   }
   if(ordinal>1&&ordinal%3==2&&source.count>2){source.count=source.tones=2;source.period=source.attacks[1].at+source.attacks[1].duration;
    for(int root:{0,chord.root})admit(source,60+s.key+root,-1,false,11.f);}
  }
 }
 // A real echo is an explicit request, never an accidental catalog lookup.
 if(ordinal%4==3&&figureHistory.count&&time-figureHistory.tones[figureHistory.count-1].at<4*musicaltime::quarter){
  const int operation=static_cast<int>((ordinal/4+s.variation)%4),wanted=operation==1?1:operation==2?3:2;
  if(figureHistory.count>=wanted){const int first=figureHistory.count-wanted;const auto& initial=figureHistory.tones[first];
   SequenceSource echo=s.policy.sequences.events[0];echo.id=4301+operation;echo.reference="DS-TO echo";echo.count=echo.tones=wanted;echo.contextMask=initial.context;echo.major=initial.major;echo.sourceIntents=true;
   echo.period={};for(int n=0;n<wanted;++n){const auto& heard=figureHistory.tones[first+n];echo.pitches[n]=heard.pitch-initial.base;echo.functions[n]=heard.intent;
    const auto at=heard.at-initial.at;echo.attacks[n]={at,std::min(heard.length,2*musicaltime::sixteenth),std::max(1,static_cast<int>(heard.velocity*(operation==0?.7f:operation==2?.65f:.6f)))};
    if(n+1<wanted)echo.attacks[n].duration=std::min(echo.attacks[n].duration,figureHistory.tones[first+n+1].at-heard.at);
    echo.period=std::max(echo.period,at+echo.attacks[n].duration);}
   const auto& performer=sequences[initial.output==OutArp?1:2];
   if(performer.source){const auto cycle=performer.source->cycle();
    const auto rest=performer.origin+cycle*std::max<int64_t>(0,((time-performer.origin).value+cycle.value-1)/cycle.value);
    begin=rest+musicaltime::sixteenth*(operation==0?3:operation==3?4:2);
    if(valid(echo)&&begin+echo.period<=sceneTime+window*(ordinal+1)){
     admit(echo,initial.base+(operation==1?24:operation==3?-12:12),initial.output,false,12.f);
     if(chosen.ready&&chosen.figure.id==echo.id){chosen.replyBegin=rest;chosen.replyEnd=rest+cycle*(((chosen.end()-rest).value+cycle.value-1)/cycle.value);}
    }
   }
  }
 }
 begin=sceneTime+window*ordinal+4*musicaltime::quarter;
 if(best<0){
  for(int i=0;i<s.policy.sequences.eventCount;++i){const auto& source=s.policy.sequences.events[i];const float xyz[]={s.x,layerY(s,kAkzent),s.z};float distance=0;
   for(int d=0;d<3;++d){const float delta=xyz[d]-(source.domains[d][0]+source.domains[d][1])*.5f;distance+=delta*delta;}
   const float score=source.preference*(1.f+.65f*(hashInt(1601+static_cast<unsigned>(ordinal),source.id)%100)/100.f)/(.12f+distance);
   // Once a seed exists, isolated bells/questions may complement it without
   // replacing or taking ownership of its immutable memory.
   if(material.complete&&source.count>1)continue;
   admit(source,48+s.key,-1,!material.complete&&source.count>1,score);
   if(chord.root)admit(source,48+s.key+chord.root,-1,!material.complete&&source.count>1,score*.95f);
  }
 }
 figureEvent=chosen;
 if(figureEvent.ready&&figureEvent.record){memory.clear();memory.originTime=figureEvent.begin;memory.introduction=ordinal;memory.draft.cycleLength=figureEvent.figure.period;}
}
void renderFigureEvent(musicaltime::Tick time,const Settings& s,int offset,EventList& out)
{
 if(!figureEvent.ready||!on[kAkzent])return;
 auto use=figureEvent.use();const int i=use.index(time);
 if(i<0||time>=figureEvent.end())return;
 // Revalidate an already planned event against the currently sounding timeline.
 if(!sequenceFits(use,figureEvent.begin,s,OutTupfer)){if(figureEvent.record)voice(OutTupfer).motif.clear();figureEvent={};return;}
 const auto& hit=figureEvent.figure.attacks[i];const int pitch=figureEvent.base+figureEvent.figure.pitches[i];
 const auto& memory=voice(OutTupfer).motif.material(motifCatalog);
 const bool replay=figureEvent.replyTo>=0||(memory.complete&&memory.vocabularyId==static_cast<unsigned>(figureEvent.figure.id));
 const bool savedForce=forceOn;if(replay)forceOn=true;
 const int before=out.size;noteOn(OutTupfer,pitch,hit.velocity,time+hit.duration,offset,out);forceOn=savedForce;
 if(figureEvent.record)for(int e=before;e<out.size;++e){const auto& n=out.events[e];if(!n.type&&n.out==OutTupfer&&n.velocity)
  voice(OutTupfer).motif.observe(n.note,time-figureEvent.begin,hit.duration,figureEventSlot,n.velocity,figureEvent.begin);}
}
// Generator adapter for shared ordered figures. Included inside Generator;
// harmonic sources, figure data and the physical MIDI emitter remain separate.
bool sequenceEligible(int output,const Settings& s)const
{
 if(!sequenceStrategy(s))return false;
 if(output==OutBassShort)return s.bassPattern==BassAuto&&s.follow[kBass]&&bassOverride<0;
 if(output==OutArp)return s.arpFigure==ArpAuto&&s.arpRate==RateAuto&&s.follow[kArp];
 if(output==OutCounter||output==OutTupfer)return true;
 if(output==OutPadShort)return s.padPattern==PadAuto;
 return false;
}
bool sequenceOwns(int output,const Settings& s)const
{
 if(!sequenceEligible(output,s))return false;
 if(output==OutBassShort)return sequences[0].source!=nullptr;
 if(output==OutArp)return sequences[1].source!=nullptr;
 return true;
}
bool sequenceBassless(const Settings& s)const
{
 if(!sourceHarmonyStrategy(s)||s.bassPattern!=BassAuto||!s.follow[kBass])return false;
 for(int i=0;i<s.policy.sequences.harmonyCount;++i)if(s.policy.sequences.harmonies[i].id==static_cast<int>(W().id))return s.policy.sequences.harmonies[i].bassless;
 return false;
}
bool sequenceRetainsBass(const Settings& s)const
{
 if(!sourceHarmonyStrategy(s)||s.bassPattern!=BassAuto||!s.follow[kBass])return false;
 for(int i=0;i<s.policy.sequences.harmonyCount;++i)if(s.policy.sequences.harmonies[i].id==static_cast<int>(W().id))return s.policy.sequences.harmonies[i].retainBoundBass;
 return false;
}
bool sequenceRoute(int output,const Settings& s)const
{
 if(output==OutBassShort&&s.channel[OutBassLong]==s.channel[OutBassShort]&&(sequenceRetainsBass(s)||independentPedal.contains(nowTime)))return false;
 // A pitched independent mono figure cannot claim the same patch as another
 // active part whose polyphony/articulation contract is unknown.
 for(int other=0;other<kNumOutputs;++other)
  if(other!=output&&!(kOutputLayer[other]==kBass&&kOutputLayer[output]==kBass)&&on[kOutputLayer[other]]&&s.channel[other]==s.channel[output])return false;
 return true;
}
void releaseSequence(int output,int offset,EventList& out)
{for(int i=0;i<numActive;)if(active[i].out==output)removeActive(i,offset,out);else ++i;}
void prepareSequencePedal(musicaltime::Tick time,const Settings& s,int offset,EventList& out)
{
 using namespace composition;
 PedalPlan plan;plan.begin=sceneTime;plan.end=time+64*musicaltime::sixteenth*meter.len;plan.pitchClass=s.key;
 plan.relation=BassRelation::independentPedal;
 bool eligible=!sequenceBassless(s)&&on[kBass]&&s.bassPattern==BassAuto&&s.follow[kBass]&&bassOverride<0&&!bassRest&&!sceneEnded;
 for(int i=0;i<W().n;++i){const auto& c=W().ch[i];unsigned tones=0;for(int n=0;n<kShapes[c.type].n;++n)tones|=pitchBit(s.key+c.root+kShapes[c.type].iv[n]);
  const int bass=c.bass<0?-1:(s.key+c.bass)%12;
  // Only an explicitly authored tonic pedal authorizes a dissonance here.
  bool sourcePedal=false;
  for(int h=0;h<s.policy.sequences.harmonyCount;++h){const auto& binding=s.policy.sequences.harmonies[h];if(binding.id==static_cast<int>(W().id))sourcePedal=binding.independentPedal;}
  const bool authorized=c.bass==0&&sourcePedal;
  if(authorized)plan.relation=BassRelation::authorizedDissonancePedal;
  eligible&=permits(plan,{tones,bass,authorized});
 }
 if(sceneEndTime)plan.end=std::min(plan.end,*sceneEndTime);
 int physical=24+s.key+12*s.octave[kBass];auto track=outputDescription(s,OutBassLong).track;
 while(physical<track.instrument.range.low)physical+=12;
 while(physical>track.instrument.range.high)physical-=12;
 bool continuing=false;for(int i=0;i<numActive;++i)continuing|=active[i].pedalOwner&&active[i].note==physical&&active[i].channel==s.channel[OutBassLong];
 RoleNeed need;need.role=MusicalRole::accompaniment;need.range={physical,physical};need.minDuration=need.maxDuration=std::max(track.instrument.minDuration,plan.end-time);
 eligible&=continuing||plan.end-time>=track.instrument.minDuration;
 eligible&=suitable(track,need)&&plan.contains(time);
 bool owned=false;
 for(int i=0;i<numActive;){auto& a=active[i];if(!a.pedalOwner){++i;continue;}
  if(!eligible||a.note!=physical||a.channel!=s.channel[OutBassLong])removeActive(i,offset,out);
  else{a.endTime=plan.end;owned=true;++i;}}
 independentPedal=eligible?plan:PedalPlan{};
 if(eligible&&!owned){
  // Promote an identical held bass without an attack; retire a different old
  // long-bass claim without touching the independent short-bass performer.
  for(int i=0;i<numActive;)if(active[i].out==OutBassLong&&(active[i].note!=physical||active[i].channel!=s.channel[OutBassLong]))removeActive(i,offset,out);else ++i;
  const auto saved=currentTiming;currentTiming=execution::Timing::nominal;
  noteOn(OutBassLong,physical-12*s.octave[kBass],static_cast<int>(54+35*layerY(s,kBass)),plan.end,offset,out,true);currentTiming=saved;}
}
// A is tested against the sounding chord; T against the declared harmonic context.
// U/F is permission attached to this exact source and matching reference chord only.
bool sequencePitch(const composition::SequenceSource& source,int tone,const Chord& c,const Settings& s,int base)const
{
 // Chord-bound degrees retain their reference root. An independent cell may
 // reinterpret a shared tone's function; a root-bass recipe must not do so.
 if(source.chordBound&&(base%12+12)%12!=(s.key+c.root)%12)return false;
 const int pc=(base+source.pitches[tone]+120)%12;unsigned mask=0;
 for(int i=0;i<kShapes[c.type].n;++i)mask|=composition::pitchBit(s.key+c.root+kShapes[c.type].iv[i]);
 const char function=source.functions[tone];if(mask&composition::pitchBit(pc))return true;
 if(source.chordBound)return false;
 if(source.sourceIntents){
  unsigned context=0;for(int pc=0;pc<12;++pc)if(source.contextMask&(1u<<pc))context|=composition::pitchBit(base+pc);
  if(function=='T'||function=='V')return (context&composition::pitchBit(pc))&&(mask&~context)==0;
  // Intent permission belongs to this exact source and reference triad/root.
  const unsigned reference=composition::pitchBit(base)|composition::pitchBit(base+(source.major?4:3))|composition::pitchBit(base+7);
  return (function=='U'||function=='F')&&(mask&reference)==reference&&(base%12+12)%12==(s.key+c.root)%12;
 }
 if(function=='T'){
  const auto* h=findHarmonyTemplate(W().id);if(!h)return false;
  const unsigned context=composition::modalMask(h->tonality.mode,s.key+h->tonality.center);
  return (context&composition::pitchBit(pc))!=0;
 }
 return (function=='U'||function=='F')&&base%12==(s.key+c.root)%12&&(source.major?c.type==Maj:c.type==Min);
}
bool sequenceFits(const composition::SequenceUse& use,musicaltime::Tick begin,const Settings& s,int output)const
{
 using namespace composition;const auto& source=*use.source;auto track=outputDescription(s,output).track;
 RoleNeed need;need.role=output==OutMelody?MusicalRole::lead:MusicalRole::accompaniment;need.style=track.style;
 int lo=127,hi=0;auto min=source.attacks[0].duration,max=min;
 for(int n=0;n<source.tones;++n){const int pitch=use.base+source.pitch(n,begin,use.origin)+12*octaveOf(output);lo=std::min(lo,pitch);hi=std::max(hi,pitch);}
 for(int i=0;i<source.count;++i){min=std::min(min,source.attack(i,begin,use.origin).duration);max=std::max(max,source.attack(i,begin,use.origin).duration);}
 need.range={lo,hi};need.minDuration=min;need.maxDuration=max;if(!suitable(track,need))return false;
 const auto end=begin+source.cycle();
 for(auto at=use.next(begin);at<end;at=use.next(at+musicaltime::Tick{1})){
  const int i=use.index(at),tone=use.tone(at,i);auto until=at+source.attack(i,at,use.origin).duration;
  auto realized=source;realized.pitches[tone]=source.pitch(tone,at,use.origin);
  if(source.functions[tone]=='V'){
   const auto next=use.next(at+musicaltime::Tick{1});const int index=use.index(next);if(index<0)return false;
   const int target=use.tone(next,index);if(std::abs(source.pitch(target,next,use.origin)-realized.pitches[tone])>2||source.functions[target]!='A')return false;
   if(!sequencePitch(source,target,chordFor(locate(next),kOutputLayer[output],s),s,use.base))return false;
  }
  auto cursor=at;
  while(cursor<until){const auto p=locate(cursor);const auto c=chordFor(p,kOutputLayer[output],s);
   if(!sequencePitch(realized,tone,c,s,use.base))return false;
   if(output==OutBassShort&&c.bass>=0&&!independentPedal.contains(at)&&(use.base+source.pitches[tone]+120)%12!=(s.key+c.bass)%12)return false;
   cursor=std::min(until,p.chordEndTime);if(cursor<=p.time)return false;
  }
 }
 return true;
}
void prepareSequences(musicaltime::Tick time,const Settings& s,int offset,EventList& out)
{
 using namespace composition;
 const int outputs[]={OutBassShort,OutArp,OutCounter};
 if(!sequenceStrategy(s)){for(int slot=0;slot<3;++slot)if(sequences[slot].source)releaseSequence(outputs[slot],offset,out);sequences={};return;}
 for(int slot=0;slot<3;++slot){auto& use=sequences[slot];const int output=outputs[slot];
  if(!sequenceEligible(output,s)||!sequenceRoute(output,s)||!on[kOutputLayer[output]]||still||sceneEnded||(slot==0&&sequenceBassless(s))){if(use.source)releaseSequence(output,offset,out);sequenceFreezeEnd[slot]={};use={};continue;}
  const auto c=chordFor(locate(time),kOutputLayer[output],s);
  if(sequenceFreezeEnd[slot]>time&&!sequenceCanHold(sequenceLast[slot],output,time,sequenceFreezeEnd[slot],s)){releaseSequence(output,offset,out);sequenceFreezeEnd[slot]={};}
  if(use.source&&use.tonic==s.key&&use.revision==s.variation){
   const float xyz[]={s.x,layerY(s,kOutputLayer[output]),s.z};bool domain=true;
   for(int d=0;d<3;++d)domain&=xyz[d]>=use.source->domains[d][0]&&xyz[d]<=use.source->domains[d][1]
      &&(d==0||(xyz[d]>=use.source->rhythmDomains[d][0]&&xyz[d]<=use.source->rhythmDomains[d][1]));
   const auto cycle=use.source->cycle();const auto start=use.origin+cycle*std::max<int64_t>(0,(time-use.origin)/cycle);
   if(sequenceFits(use,start,s,output)&&(domain||(time-use.origin)%cycle!=musicaltime::Tick{}))continue;
   releaseSequence(output,offset,out);sequenceFreezeEnd[slot]={};use={};
  }
  if(use.source){releaseSequence(output,offset,out);sequenceFreezeEnd[slot]={};use={};}
  // Admission is checked on whole source cycles. XYZ never truncates an eligible cell.
  float best=-1;SequenceUse chosen;
  for(int material=0;material<s.policy.sequences.count;++material){const auto& source=s.policy.sequences.sources[material];
   if(source.bass!=(slot==0))continue;
   const float coords[]={s.x,layerY(s,kOutputLayer[output]),s.z};bool domain=true;
   float distance=0;
   for(int d=0;d<3;++d){if(coords[d]<source.domains[d][0]||coords[d]>source.domains[d][1])domain=false;
    if(d>0&&(coords[d]<source.rhythmDomains[d][0]||coords[d]>source.rhythmDomains[d][1]))domain=false;
    float delta=coords[d]-(source.domains[d][0]+source.domains[d][1])*.5f;distance+=delta*delta;}
   if(!domain)continue;
   const auto cycle=source.cycle();SequenceUse candidate{&source,sceneTime,0,s.key,s.variation};
   const auto start=sceneTime+cycle*std::max<int64_t>(0,(time-sceneTime)/cycle);
   // Source pitch phase belongs to the scene, not the currently selected chord.
   const int anchor=(slot==0?36:slot==1?60:72)+s.key+((source.chordBound||source.blockTranspose)?c.root:0);
   bool fits=false;
   for(int shift:composition::figureOctaves){candidate.base=anchor+shift;if(sequenceFits(candidate,start,s,output)){fits=true;break;}}
   if(!fits)continue;
   float score=1.f/(.1f+distance)*(1.f+.3f*(hashInt(1201+slot,source.id)%100)/100.f);
   // Joint admission of the documented onbeat/offbeat pair; not a collision-removal mask.
   if(on[kArp]&&on[kGegenstimme]&&s.variation%3==0&&source.complement>0
     &&((slot==1&&source.id<source.complement)||(slot==2&&sequences[1].source&&sequences[1].source->complement==source.id)))score*=4.f;
   if(score>best){best=score;chosen=candidate;}
  }
  if(chosen.source)releaseSequence(output,offset,out); // acquire this output without an older stock claim
  use=chosen;
 }
}
bool sequenceCanHold(int physical,int output,musicaltime::Tick at,musicaltime::Tick end,const Settings& s)const
{
 if(physical<0||end-at>outputDescription(s,output).track.instrument.maxDuration)return false;
 while(at<end){const auto p=locate(at);const auto chord=chordFor(p,kOutputLayer[output],s);unsigned mask=0;
  for(int n=0;n<kShapes[chord.type].n;++n)mask|=composition::pitchBit(s.key+chord.root+kShapes[chord.type].iv[n]);
  if(!(mask&composition::pitchBit(physical))||p.chordEndTime<=at)return false;at=std::min(end,p.chordEndTime);
 }return true;
}
void renderSequences(musicaltime::Tick time,const Settings& s,int offset,EventList& out)
{
 using namespace composition;const int outputs[]={OutBassShort,OutArp,OutCounter};
 const bool saved=sequenceEmission;sequenceEmission=true;
 for(int slot=0;slot<3;++slot){auto& use=sequences[slot];if(!use.source)continue;const int i=use.index(time);if(i<0)continue;
  const auto cycle=use.source->cycle();
  if(!LayerCycle::active(slot,time,use.origin,cycle,layerY(s,kOutputLayer[outputs[slot]]),s.z,static_cast<uint32_t>(s.variation+17*slot)))continue;
  if(figureEvent.replyTo==outputs[slot]&&time>=figureEvent.replyBegin&&time<figureEvent.replyEnd)continue;
  auto hit=use.source->attack(i,time,use.origin);const int note=use.base+use.source->pitch(use.tone(time,i),time,use.origin);
  if(use.source->frozen(time,use.origin)){
   const auto turn=(time-use.origin)/cycle;const auto start=use.origin+cycle*(turn-turn%(use.source->freezeAfter+use.source->freezeCycles)+use.source->freezeAfter);
   if(time==start&&sequenceFreezeEnd[slot]<=time&&sequenceCanHold(sequenceLast[slot],outputs[slot],time,start+cycle*use.source->freezeCycles,s)){
    const auto end=start+cycle*use.source->freezeCycles;
    noteOn(outputs[slot],sequenceLast[slot]-12*octaveOf(outputs[slot]),hit.velocity,end,offset,out);sequenceFreezeEnd[slot]=end;
   }
   continue; // A cold seek into a frozen span cannot invent its missing played prefix.
  }
  const auto following=use.next(time+musicaltime::Tick{1});
  if(use.source->frozen(following,use.origin)){
   const auto end=following+cycle*use.source->freezeCycles;
   if(sequenceCanHold(note+12*octaveOf(outputs[slot]),outputs[slot],time,end,s)){hit.duration=end-time;sequenceFreezeEnd[slot]=end;}
  }
  noteOn(outputs[slot],note,static_cast<int>(hit.velocity*(.6f+.4f*layerY(s,kOutputLayer[outputs[slot]]))),time+hit.duration,offset,out);
 }
 // JC-R001 quarter pulse (480-tick gates), only as an eligible short harmony layer.
 if(s.policy.sequences.chordPulse&&on[kFlaeche]&&s.padPattern==PadAuto&&s.y>=.55f&&s.z<=.4f&&s.channel[OutPadShort]!=s.channel[OutPadLong]&&time%musicaltime::quarter==musicaltime::Tick{}
   &&LayerCycle::active(1,time,sceneTime,16*musicaltime::sixteenth,s.y,s.z,s.variation+3))
  padChord(locate(time),s,OutPadShort,offset,time+musicaltime::Tick{480},static_cast<int>(48+35*s.y),out);
 renderFigureEvent(time,s,offset,out);renderLeadEvent(time,s,offset,out);
 sequenceEmission=saved;
}
