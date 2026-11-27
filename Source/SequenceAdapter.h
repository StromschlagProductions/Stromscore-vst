// Generator adapter for shared ordered figures. Included inside Generator;
// harmonic sources, figure data and the physical MIDI emitter remain separate.
bool sequenceOwns(int output,const Settings& s)const
{
 if(!sequenceStrategy(s))return false;
 if(output==OutBassShort)return s.bassPattern==BassAuto&&s.follow[kBass]&&bassOverride<0;
 if(output==OutArp)return s.arpFigure==ArpAuto&&s.arpRate==RateAuto&&s.follow[kArp];
 if(output==OutCounter||output==OutTupfer)return true;
 if(output==OutPadShort)return s.padPattern==PadAuto;
 return false;
}
bool sequenceRoute(int output,const Settings& s)const
{
 // A pitched independent mono figure cannot claim the same patch as another
 // active part whose polyphony/articulation contract is unknown.
 for(int other=0;other<kNumOutputs;++other)
  if(other!=output&&on[kOutputLayer[other]]&&s.channel[other]==s.channel[output])return false;
 return true;
}
void releaseSequence(int output,int offset,EventList& out)
{for(int i=0;i<numActive;)if(active[i].out==output)removeActive(i,offset,out);else ++i;}
void prepareSequencePedal(musicaltime::Tick time,const Settings& s,int offset,EventList& out)
{
 using namespace composition;
 PedalPlan plan;plan.begin=sceneTime;plan.end=time+64*musicaltime::sixteenth*meter.len;plan.pitchClass=s.key;
 plan.relation=BassRelation::independentPedal;
 bool eligible=on[kBass]&&s.bassPattern==BassAuto&&s.follow[kBass]&&bassOverride<0&&!bassRest&&!still&&!sceneEnded;
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
 int physical=24+s.key+12*s.octave[kBass];auto track=outputCatalog(s)[OutBassLong].track;
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
 if(function=='T'){
  const auto* h=findHarmonyTemplate(W().id);if(!h)return false;
  const unsigned context=composition::modalMask(h->tonality.mode,s.key+h->tonality.center);
  return (context&composition::pitchBit(pc))!=0;
 }
 return (function=='U'||function=='F')&&base%12==(s.key+c.root)%12&&(source.major?c.type==Maj:c.type==Min);
}
bool sequenceFits(const composition::SequenceUse& use,musicaltime::Tick begin,const Settings& s,int output)const
{
 using namespace composition;const auto& source=*use.source;auto track=outputCatalog(s)[output].track;
 RoleNeed need;need.role=MusicalRole::accompaniment;need.style=PlayingStyle::detached;
 int lo=127,hi=0;auto min=source.attacks[0].duration,max=min;
 for(int n=0;n<source.tones;++n){const int pitch=use.base+source.pitches[n]+12*octaveOf(output);lo=std::min(lo,pitch);hi=std::max(hi,pitch);}
 for(int i=0;i<source.count;++i){min=std::min(min,source.attacks[i].duration);max=std::max(max,source.attacks[i].duration);}
 need.range={lo,hi};need.minDuration=min;need.maxDuration=max;if(!suitable(track,need))return false;
 const auto end=begin+source.cycle();
 for(auto at=use.next(begin);at<end;at=use.next(at+musicaltime::Tick{1})){
  const int i=use.index(at),tone=use.tone(at,i);auto until=at+source.attacks[i].duration;
  auto cursor=at;
  while(cursor<until){const auto p=locate(cursor);const auto c=chordFor(p,kOutputLayer[output],s);
   if(!sequencePitch(source,tone,c,s,use.base))return false;
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
  if(!sequenceOwns(output,s)||!sequenceRoute(output,s)||!on[kOutputLayer[output]]||still||sceneEnded){if(use.source)releaseSequence(output,offset,out);use={};continue;}
  const auto c=chordFor(locate(time),kOutputLayer[output],s);
  if(use.source&&use.tonic==s.key&&use.revision==s.variation){
   const float xyz[]={s.x,layerY(s,kOutputLayer[output]),s.z};bool domain=true;
   for(int d=0;d<3;++d)domain&=xyz[d]>=use.source->domains[d][0]&&xyz[d]<=use.source->domains[d][1]
      &&(d==0||(xyz[d]>=use.source->rhythmDomains[d][0]&&xyz[d]<=use.source->rhythmDomains[d][1]));
   const auto cycle=use.source->cycle();const auto start=use.origin+cycle*std::max<int64_t>(0,(time-use.origin)/cycle);
   if(sequenceFits(use,start,s,output)&&(domain||(time-use.origin)%cycle!=musicaltime::Tick{}))continue;
   releaseSequence(output,offset,out);use={};
  }
  if(use.source){releaseSequence(output,offset,out);use={};}
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
   for(int shift:{0,-12,12,-24,24}){candidate.base=anchor+shift;if(sequenceFits(candidate,start,s,output)){fits=true;break;}}
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
void renderSequences(musicaltime::Tick time,const Settings& s,int offset,EventList& out)
{
 using namespace composition;const int outputs[]={OutBassShort,OutArp,OutCounter};
 const bool saved=sequenceEmission;sequenceEmission=true;
 for(int slot=0;slot<3;++slot){auto& use=sequences[slot];if(!use.source)continue;const int i=use.index(time);if(i<0)continue;
  const auto cycle=use.source->cycle();
  if(!LayerCycle::active(slot,time,use.origin,cycle,layerY(s,kOutputLayer[outputs[slot]]),s.z,static_cast<uint32_t>(s.variation+17*slot)))continue;
  const auto& hit=use.source->attacks[i];const int note=use.base+use.source->pitches[use.tone(time,i)];
  noteOn(outputs[slot],note,static_cast<int>(hit.velocity*(.6f+.4f*layerY(s,kOutputLayer[outputs[slot]]))),time+hit.duration,offset,out);
 }
 // JC-R001 quarter pulse (480-tick gates), only as an eligible short harmony layer.
 if(s.policy.sequences.chordPulse&&on[kFlaeche]&&s.padPattern==PadAuto&&s.y>=.55f&&s.z<=.4f&&s.channel[OutPadShort]!=s.channel[OutPadLong]&&time%musicaltime::quarter==musicaltime::Tick{}
   &&LayerCycle::active(1,time,sceneTime,16*musicaltime::sixteenth,s.y,s.z,s.variation+3))
  padChord(locate(time),s,OutPadShort,offset,time+musicaltime::Tick{480},static_cast<int>(48+35*s.y),out);
 // A source figure and its sparse occurrence window are distinct data.
 const auto window=s.policy.sequences.eventSpacing;
 const auto origin=sceneTime+window*std::max<int64_t>(0,(time-sceneTime)/window);
 const auto* source=s.policy.sequences.event;
 const SequenceUse echo{source,origin,60+s.key,s.key,s.variation};
 const auto relative=time-origin;
 if(source&&on[kAkzent]&&relative>=musicaltime::Tick{}&&relative<source->period
   &&s.x>=source->domains[0][0]&&s.x<=source->domains[0][1]
   &&s.y>=source->domains[1][0]&&s.y<=source->domains[1][1]
   &&s.z>=source->domains[2][0]&&s.z<=source->domains[2][1]&&sequenceFits(echo,origin,s,OutTupfer))
 {const int index=echo.index(time);if(index>=0){const auto& hit=source->attacks[index];
   noteOn(OutTupfer,echo.base+source->pitches[index],hit.velocity,time+hit.duration,offset,out);}}
 sequenceEmission=saved;
}
