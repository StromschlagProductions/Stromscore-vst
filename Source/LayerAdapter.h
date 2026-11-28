int layerStage(const composition::HarmonicLayerBinding& b)const
{const auto phase=std::max(musicaltime::Tick{},nowTime-wendungTime)%(32*musicaltime::quarter);int result=-1;for(int i=0;i<b.stages;++i)if(phase>=b.evolution[i].at)result=i;return result;}
bool layerFused(const composition::HarmonicLayerBinding& b,const Settings&)const
{const int stage=layerStage(b);return stage>=0?b.evolution[stage].fused:b.fused;}
int layerUpper(const composition::HarmonicLayerBinding& b,int index,const Settings& s)const
{const int stage=layerStage(b);return b.upperNotes[index]+(stage>=0?b.evolution[stage].shift:0)+s.key;}
bool layerStrategy(const Settings& s)const
{return s.policy.layers.enabled&&s.policy.layers.figures&&s.genre==GenreScore&&!s.custom&&s.meterNum==4&&s.meterDen==4;}
const composition::HarmonicLayerBinding* layerBinding(const Settings& s)const
{
 if(!layerStrategy(s)||current<0)return nullptr;
 for(int i=0;i<s.policy.layers.harmonyCount;++i)if(s.policy.layers.harmonies[i].harmonyId==static_cast<int>(W().id))return &s.policy.layers.harmonies[i];return nullptr;
}
bool layerOwns(int output,const Settings& s)const
{
 if(!layerBinding(s))return false;
 if(output==OutPadLong||output==OutPadShort)return s.padPattern==PadAuto&&s.follow[kFlaeche];
 if(output==OutBassLong||output==OutBassShort)return s.bassPattern==BassAuto&&s.follow[kBass]&&bassOverride<0;
 if(output==OutArp)return s.arpFigure==ArpAuto&&s.arpRate==RateAuto&&s.follow[kArp];
 return output==OutTupfer||output==OutStich;
}
bool layerRoute(int output,const Settings& s)const
{
 for(int other=0;other<kNumOutputs;++other)if(other!=output&&on[kOutputLayer[other]]&&s.channel[other]==s.channel[output])return false;return true;
}
unsigned layerChordMask(const Chord& chord,const Settings& s,bool includeBass=false)const
{
 unsigned mask=0;for(int i=0;i<kShapes[chord.type].n;++i)mask|=composition::pitchBit(s.key+chord.root+kShapes[chord.type].iv[i]);
 if(includeBass)mask|=composition::pitchBit(s.key+bassRoot(chord));return mask;
}
int layerPitch(const composition::LayerAttack& hit,const Chord& c,const Settings& s,int output,musicaltime::Tick at)const
{
 using R=composition::PitchReference;const auto& shape=kShapes[c.type];
 if(hit.reference==R::fixed)return hit.pitch+s.key;
 int root=(output==OutBassLong||output==OutBassShort?36:output==OutTupfer?72:60)+s.key+c.root;
 if(output==OutBassLong||output==OutBassShort)if(const auto* b=layerBinding(s)){const auto pos=locate(at);const int wanted=b->bassNotes[pos.chordIdx]+s.key;while(root-wanted>6)root-=12;while(root-wanted< -6)root+=12;}
 if(hit.reference==R::bass){if(const auto* b=layerBinding(s);b&&(output==OutBassLong||output==OutBassShort))return b->bassNotes[locate(at).chordIdx]+s.key;return 60+s.key+bassRoot(c);}
 if(hit.reference==R::fifth)return root+7;
 if(hit.reference==R::octave)return root+(hit.pitch<0?-12:12);
 if(hit.reference==R::brokenChord)return 60+s.key+c.root+shape.iv[hit.pitch%shape.n]+12*(hit.pitch/shape.n);
 return root+hit.pitch;
}
bool layerPlayable(int output,int pitch,musicaltime::Tick duration,const Settings& s)const
{
 const auto c=outputCatalog(s)[output].track.instrument;pitch+=12*octaveOf(output);
 return pitch>=c.range.low&&pitch<=c.range.high&&pitch>=0&&pitch<=127&&duration>=c.minDuration&&duration<=c.maxDuration&&layerRoute(output,s);
}
bool layerPolyphony(const composition::LayerFigure& source,musicaltime::Tick begin,const Settings& s,int output)const
{
 if(output!=OutPadLong)return true;const auto* h=findHarmonyTemplate(W().id);if(!h||!h->voicings[0].count)return true;
 const auto cap=outputCatalog(s)[output].track.instrument;int shift=0;bool available=false;
 for(int oct:{0,-12,12,-24,24}){bool fits=true;for(int i=0;i<h->count;++i)for(int n=0;n<h->voicings[i].count;++n){const int pitch=60+s.key+oct+h->voicings[i].notes[n]+12*octaveOf(output);fits&=pitch>=cap.range.low&&pitch<=cap.range.high;}
  if(fits){shift=oct;available=true;break;}}
 if(!available)return false;
 for(int i=0;i<source.count;++i){bool heard[128]{};int voices=0;auto add=[&](int pitch){if(pitch>=0&&pitch<128&&!heard[pitch]){heard[pitch]=true;++voices;}};
  const auto at=begin+source.attacks[i].at;const auto now=locate(at);const auto& current=h->voicings[now.chordIdx];
  for(int n=0;n<current.heldCount;++n)add(60+s.key+shift+current.held[n]+12*octaveOf(output));
  if(const auto* b=layerBinding(s);b&&b->highPedal>=0)add(b->highPedal+s.key+12*octaveOf(output));
  for(int turn=-1;turn<=0;++turn)for(int j=0;j<source.count;++j){const auto start=begin+source.period*turn+source.attacks[j].at;
   if(start>at||start+source.attacks[j].duration<=at||start<sceneTime)continue;
   const auto p=locate(start);const auto& v=h->voicings[p.chordIdx];for(int n=0;n<v.count;++n)add(60+s.key+shift+v.notes[n]+12*octaveOf(output));}
  if(voices>cap.polyphony)return false;
 }
 return true;
}
bool layerFits(const composition::LayerFigure& source,musicaltime::Tick begin,const Settings& s,int output)const
{
 using namespace composition;
 if(!layerPolyphony(source,begin,s,output))return false;
 for(int i=0;i<source.count;++i){const auto& hit=source.attacks[i];const auto at=begin+hit.at;auto cursor=at;const auto until=at+hit.duration;
  const auto reference=chordFor(locate(at),kOutputLayer[output],s);const int note=layerPitch(hit,reference,s,output,at);
  if(hit.reference==PitchReference::chord){
   const auto cap=outputCatalog(s)[output].track.instrument;if(hit.duration<cap.minDuration||hit.duration>cap.maxDuration)return false;
   auto cursor=at;const auto required=layerChordMask(reference,s);
   while(cursor<until){const auto pos=locate(cursor);const auto c=chordFor(pos,kOutputLayer[output],s);if(required&~layerChordMask(c,s))return false;if(pos.chordEndTime<=cursor)return false;cursor=std::min(until,pos.chordEndTime);}continue;
  }
  if(!layerPlayable(output,note,hit.duration,s))return false;
  while(cursor<until){const auto pos=locate(cursor);const auto c=chordFor(pos,kOutputLayer[output],s);const unsigned mask=layerChordMask(c,s,output==OutBassLong||output==OutBassShort);
   unsigned authorized=0;for(unsigned context:source.context)if(context&&transposePitchMask(context,s.key)==layerChordMask(c,s))authorized|=pitchBit(note);
   bool target=false;if(hit.intent.function=='V')for(int j=i+1;j<source.count;++j)if(source.attacks[j].pitch==hit.intent.resolution){const auto targetChord=chordFor(locate(begin+source.attacks[j].at),kOutputLayer[output],s);target=(layerChordMask(targetChord,s,true)&pitchBit(hit.intent.resolution+s.key))!=0;break;}
   if((output==OutBassLong||output==OutBassShort)&&c.bass>=0&&(note%12+12)%12!=(s.key+c.bass)%12){
    bool explicitVariant=false;for(int id:source.harmonicReferences)explicitVariant|=id==static_cast<int>(W().id);if(!explicitVariant)return false;
   }
   const auto modal=modalContextFor(s);if(!permittedTone(hit.intent,note,mask,modal.mask,authorized,target))return false;
   if(pos.chordEndTime<=cursor)return false;cursor=std::min(until,pos.chordEndTime);
  }
 }
 return true;
}
void prepareLayers(musicaltime::Tick time,const Settings& s,int offset,EventList& out)
{
 const auto* binding=layerBinding(s);const int id=binding?binding->harmonyId:0;
 // Clear old owned claims on handover, but keep identical harmonic notes until
 // the new complete voicing is reconciled below. No unknown-history replay.
 for(int i=0;i<numActive;){auto& a=active[i];if(a.layerOwner&&(!binding||!layerOwns(a.out,s)||!layerRoute(a.out,s)))removeActive(i,offset,out);else ++i;}
 if(!binding){layerUses={};layerHarmony=0;layerGroup=0;layerGroupEnd={};return;}
 if(layerHarmony!=id){layerUses={};layerHarmony=id;layerGroup=0;layerGroupEnd={};
  for(int i=0;i<numActive;)if(active[i].layerOwner&&active[i].out!=OutPadLong&&active[i].out!=OutBassLong)removeActive(i,offset,out);else ++i;}
 int group=layerGroup;float groupBest=-1;
 if(!layerGroup||time>=layerGroupEnd)for(int i=0;i<s.policy.layers.count;++i){const auto& candidate=s.policy.layers.figures[i];if(!candidate.group||(i>0&&s.policy.layers.figures[i-1].group==candidate.group))continue;
  const float dy=s.y-candidate.y,dz=s.z-candidate.z;float rank=std::exp(-(dy*dy+.64f*dz*dz)/.06f);
  bool fits=s.x>=candidate.xLow&&s.x<=candidate.xHigh;
  for(int j=0;j<s.policy.layers.count;++j){const auto& part=s.policy.layers.figures[j];if(part.group!=candidate.group)continue;
   const int output=static_cast<int>(part.part);if(!on[kOutputLayer[output]]||!layerOwns(output,s))continue;
   const auto begin=sceneTime+part.period*std::max<int64_t>(0,(time-sceneTime)/part.period);fits&=layerFits(part,begin,s,output);}
  rank*=1.f+.2f*(hashInt(candidate.group,(time-sceneTime)/candidate.period/4)%100)/100.f;
  if(fits&&rank>groupBest){groupBest=rank;group=candidate.group;}
 }
 if(layerGroup&&time<layerGroupEnd)group=layerGroup;
 else{layerGroup=group;for(int i=0;i<s.policy.layers.count;++i)if(s.policy.layers.figures[i].group==group){auto period=s.policy.layers.figures[i].period;layerGroupEnd=sceneTime+period*((time-sceneTime)/period+1);break;}}
 for(int output=0;output<kNumOutputs;++output){auto& use=layerUses[output];if((output==OutBassLong&&(binding->pedal>=0||binding->bassMode!=0))||(output==OutBassShort&&binding->bassMode!=0)){use={};continue;}if(!layerOwns(output,s)||!on[kOutputLayer[output]]||!layerRoute(output,s)||still||sceneEnded){use={};continue;}
  if(use.source){const auto begin=use.origin+use.source->period*std::max<int64_t>(0,(time-use.origin)/use.source->period);
   if((!use.source->group||use.source->group==group)&&layerFits(*use.source,begin,s,output)&&s.x>=use.source->xLow&&s.x<=use.source->xHigh){if((time-use.origin)%use.source->period!=musicaltime::Tick{}||hashInt(1901+output,(time-sceneTime)/use.source->period)%4!=0)continue;}}
  float best=-1;composition::LayerUse chosen;
  for(int i=0;i<s.policy.layers.count;++i){const auto& source=s.policy.layers.figures[i];if((source.group&&source.group!=group)||static_cast<int>(source.part)!=output||s.x<source.xLow||s.x>source.xHigh)continue;
   const auto begin=sceneTime+source.period*std::max<int64_t>(0,(time-sceneTime)/source.period);
   if(!layerFits(source,begin,s,output))continue;
   const float dy=layerY(s,kOutputLayer[output])-source.y,dz=s.z-source.z;const float distance=dy*dy+.64f*dz*dz;
   const auto cycle=(time-sceneTime)/source.period;const float rank=std::exp(-distance/.06f)*(1.f+.25f*(hashInt(source.id+output,cycle/4)%100)/100.f);
   if(rank>best){best=rank;chosen={&source,sceneTime,id};}
  }
  if(use.source!=chosen.source)for(int a=0;a<numActive;)if(active[a].layerOwner&&!active[a].layerAnchor&&active[a].out==output)removeActive(a,offset,out);else ++a;
  use=chosen;
 }
 // The long and short bass are alternative figure contracts. A short figure can
 // coexist with a separately authorized held pedal, not a second moving LB line.
 if(binding->upperRoot>=0){layerUses[OutArp]={};if(layerFused(*binding,s)){layerUses[OutPadLong]={};layerUses[OutPadShort]={};}}
 if(layerUses[OutBassLong].source&&layerUses[OutBassShort].source)
  {if(s.z>.55f&&s.y>.4f)layerUses[OutBassLong]={};else layerUses[OutBassShort]={};} for(int a=0;a<numActive;){const auto& n=active[a];
  const bool obsolete=n.layerOwner&&n.layerAnchor&&(n.out==OutBassLong&&layerUses[OutBassLong].source&&!layerUses[OutBassLong].source->heldCycle);
  if(obsolete)removeActive(a,offset,out);else ++a;}

}
void layerEmit(int output,int pitch,int velocity,musicaltime::Tick end,int offset,const Settings& s,EventList& out,bool tie=false)
{
 if(sceneEndTime)end=std::min(end,*sceneEndTime);
 if(!layerPlayable(output,pitch,end-nowTime,s))return;
 const bool saved=layerEmission,held=extendOnly;layerEmission=true;extendOnly=tie;
 noteOn(output,pitch,velocity,end,offset,out,false,tie);layerEmission=saved;extendOnly=held;
}
void renderLayerHarmony(musicaltime::Tick time,const Pos& p,const Settings& s,int offset,EventList& out)
{
 const auto* b=layerBinding(s);if(!b||still||sceneEnded)return;
 if(layerOwns(OutPadLong,s)&&on[kFlaeche]){
  auto v=padVoicing(p,s,OutPadLong);
  if(layerUses[OutPadLong].source){auto required=v;required.n=0;
   if(const auto* h=findHarmonyTemplate(W().id)){const auto& authored=h->voicings[p.chordIdx];for(int i=0;i<v.n;++i)for(int n=0;n<authored.heldCount;++n)
    if((v.notes[i]%12+12)%12==(s.key+authored.held[n]+120)%12)required.notes[required.n++]=v.notes[i];}
   v=required;}
if(layerFused(*b,s))for(int i=0;i<3;++i)if(v.n<6)v.notes[v.n++]=layerUpper(*b,i,s);
  if(b->highPedal>=0&&v.n<6)v.notes[v.n++]=b->highPedal+s.key;
  bool fits=true;for(int i=0;i<v.n;++i)fits&=layerPlayable(OutPadLong,v.notes[i],p.chordEndTime-time,s);
  if(fits){for(int i=0;i<numActive;){auto& a=active[i];bool wanted=false;for(int n=0;n<v.n;++n)wanted|=a.note==v.notes[n]+12*octaveOf(OutPadLong);
    if(a.layerOwner&&a.out==OutPadLong&&!wanted&&(!layerUses[OutPadLong].source||a.layerAnchor))removeActive(i,offset,out);else ++i;}
   for(int i=0;i<v.n;++i)layerEmit(OutPadLong,v.notes[i],static_cast<int>(40+45*layerY(s,kFlaeche)),p.chordEndTime,offset,s,out,true);}
  else for(int i=0;i<numActive;)if(active[i].layerOwner&&active[i].out==OutPadLong)removeActive(i,offset,out);else ++i;
 }
 if(layerOwns(OutPadLong,s)&&on[kFlaeche]&&b->highPedal>=0)
  layerEmit(OutPadLong,b->highPedal+s.key,56,time+32*musicaltime::quarter,offset,s,out,true);
 if(layerOwns(OutBassLong,s)&&on[kBass]&&b->bassMode==0&&!layerUses[OutBassLong].source){
  const auto c=chordFor(p,kBass,s);const int pitch=(b->pedal>=0?b->bassRegister+b->pedal:b->bassNotes[p.chordIdx])+s.key;
  // Every independent pedal must be explicitly licensed by this source context.
  const auto end=b->pedal>=0?time+32*musicaltime::quarter:p.chordEndTime;
  for(int i=0;i<numActive;)if(active[i].layerOwner&&active[i].out==OutBassLong&&active[i].note!=pitch+12*octaveOf(OutBassLong))removeActive(i,offset,out);else ++i;
  layerEmit(OutBassLong,pitch,static_cast<int>(48+35*layerY(s,kBass)),sceneEndTime?std::min(end,*sceneEndTime):end,offset,s,out,true);
 }
}
void renderLayers(musicaltime::Tick time,const Pos& p,const Settings& s,int offset,EventList& out,bool structural)
{
 const auto* b=layerBinding(s);if(!b)return;
 if(structural||layerStage(*b)!=lastLayerStage){
  const bool entering=layerHarmony!=b->harmonyId,changing=layerStage(*b)!=lastLayerStage;
  if((entering||changing)&&layerFused(*b,s))for(int i=0;i<numActive;)if(active[i].layerOwner&&active[i].out==OutPadLong&&active[i].note!=b->highPedal+s.key+12*octaveOf(OutPadLong))removeActive(i,offset,out);else ++i;
  lastLayerStage=layerStage(*b);prepareLayers(time,s,offset,out);renderLayerHarmony(time,p,s,offset,out);
  if(b->bassMode==1||b->bassMode==2)for(int i=0;i<numActive;)if(active[i].layerOwner&&active[i].out==OutBassLong)removeActive(i,offset,out);else ++i;
  if(b->bassMode==2&&on[kBass]&&(entering||changing))layerEmit(OutBassShort,b->bassRegister+s.key+bassRoot(chordFor(p,kBass,s)),68,time+musicaltime::sixteenth,offset,s,out);
  if(const auto* source=layerUses[OutBassLong].source;source&&source->heldCycle&&on[kBass]){const auto& hit=source->attacks[0];const auto c=chordFor(p,kBass,s);const int wanted=layerPitch(hit,c,s,OutBassLong,time)+12*octaveOf(OutBassLong);
   for(int i=0;i<numActive;)if(active[i].layerOwner&&active[i].out==OutBassLong&&active[i].note!=wanted)removeActive(i,offset,out);else ++i;
   layerEmit(OutBassLong,layerPitch(hit,c,s,OutBassLong,time),hit.velocity,time+source->period+32*musicaltime::quarter,offset,s,out,true);}return;}
 if(still||sceneEnded)return;
 for(int output=0;output<kNumOutputs;++output){const auto& use=layerUses[output];if(!use.source||(bassRest&&(output==OutBassLong||output==OutBassShort))||!on[kOutputLayer[output]]||!layerOwns(output,s))continue;
  const auto& source=*use.source;const auto rel=(time-use.origin)%source.period;
  const auto turn=(time-use.origin)/source.period;
  if(source.sparse&&hashInt(source.id,turn)%3==0)continue; // rest is a whole source figure
  if(output==OutArp&&motifWindow(p,s).contains(time))continue;
  for(int i=0;i<source.count;++i){const auto& hit=source.attacks[i];if(hit.at!=rel)continue;const auto c=chordFor(p,kOutputLayer[output],s);
   const auto end=source.heldCycle?time+source.period+32*musicaltime::quarter:time+hit.duration;
   if(hit.reference==composition::PitchReference::chord){auto v=padVoicing(p,s,output);
    for(int a=0;a<numActive;)if(active[a].layerOwner&&!active[a].layerAnchor&&active[a].out==output&&active[a].endTime<=time)removeActive(a,offset,out);else ++a;
    for(int n=0;n<v.n;++n)layerEmit(output,v.notes[n],hit.velocity,end,offset,s,out);}
   else layerEmit(output,layerPitch(hit,c,s,output,time),hit.velocity,end,offset,s,out,source.heldCycle);
  }
 }
 if(b->upperRoot>=0&&!layerFused(*b,s)&&layerOwns(OutArp,s)&&on[kArp]&&!motifWindow(p,s).contains(time)){
  bool fits=true;for(int i=0;i<3;++i)fits&=layerPlayable(OutArp,layerUpper(*b,i,s),musicaltime::quarter,s);if(!fits)return;
  const auto local=(time-sceneTime)%(8*musicaltime::quarter);for(int i=0;i<3;++i)if(local==(i+1)*musicaltime::quarter)
   layerEmit(OutArp,layerUpper(*b,i,s),66,time+musicaltime::quarter,offset,s,out);
 }
}
