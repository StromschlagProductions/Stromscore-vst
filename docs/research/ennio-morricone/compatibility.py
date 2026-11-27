"""Finite offline compatibility diagnostics; no import, no changed XYZ strategy."""
from pathlib import Path
import json,re,itertools,subprocess,tempfile,collections,math,csv
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[2]
items=json.loads((HERE/'TECHNICAL_INVENTORY.json').read_text())['records'];by={r['id']:r for r in items}
def dump(n,d):(HERE/n).write_text(json.dumps(d,ensure_ascii=False,indent=2)+'\n')
# Expose actual compiled instrument assumptions and unchanged engine weights.
trans=[]
for r in items:
 if r['kind']=='U':
  for i,(a,b)in enumerate(zip(r['states'],r['states'][1:])):trans.append((r['id'],i,a['pitches'],b['pitches']))
harmonies=[r for r in items if r['kind']=='H'];points=list(itertools.product([i/10 for i in range(11)],repeat=3));probe_rows=[]
payload=str(len(trans))+'\n'+'\n'.join(f'{id} {step} {len(a)} {len(b)} '+' '.join(map(str,a+b))for id,step,a,b in trans)+'\n'
payload+=f'{len(harmonies)} {len(points)}\n'+'\n'.join(' '.join(map(str,r['xyz']))for r in harmonies)+'\n'+'\n'.join(' '.join(map(str,p))for p in points)+'\n'
with tempfile.TemporaryDirectory()as tmp:
 exe=Path(tmp)/'probe';subprocess.run(['c++','-O0','-std=c++17','-I',str(ROOT/'Source'),str(HERE/'engine_probe.cpp'),'-o',str(exe)],check=True)
 result=subprocess.check_output([str(exe)],input=payload.encode()).decode()
compiled_caps={};voicings=[];selection={}
for line in result.splitlines():
 s=line.split()
 if s[0]=='CAP':compiled_caps[int(s[1])]=dict(polyphony=int(s[2]),minDuration=int(s[3]),maxDuration=int(s[4]))
 elif s[0]=='U':
  id,step,key,n=s[1],int(s[2]),int(s[3]),int(s[4]);actual=list(map(int,s[5:]));assert len(actual)==n
  a,b=next((a,b)for name,i,a,b in trans if name==id and i==step);common=set(a)&set(b);required=set(by[id]['required_held_pitches'][step]);kept={p for p in common if p+60+key in actual}
  voicings.append(dict(id=id,step=step,key=key,actual=actual,common_relative=sorted(common),retained=sorted(kept),lost=sorted(common-kept),required_held=sorted(required),lost_required=sorted(required-kept),pc_identity_preserved=sorted({(p-60-key)%12 for p in actual})==sorted({p%12 for p in b})))
 else:
  i,variety=int(s[1]),float(s[2]);ids=[harmonies[int(j)]['id']for j in s[3:]];selection[i,variety]=ids
role_to_output={'LF':0,'KF':1,'LB':2,'KB':3,'AR':4,'TU':5,'ST':6,'GS':7,'HM':8};limits=json.loads((HERE/'INSTRUMENT_CONSTRAINTS.json').read_text())['limits']
for role,output in role_to_output.items():
 cap=compiled_caps[output];assert [cap['polyphony'],cap['minDuration'],cap['maxDuration']]==limits[role]
dump('ENGINE_PROBE_RESULTS.json',dict(base='4c43bd2',compiled_caps=compiled_caps,voices=voicings,scope='Canonical raw upper voicings used as inputs to the existing lead function, twelve keys. This is not an active Morricone runtime path, not a hard-hold guarantee, not a MIDI continuity or aesthetic test.'))
# Strict local material comparison. Source pitches are tonic-relative; NEVER
# transpose each bass tone by the next chord root, or snap cells to chord tones.
def deg(s):
 m=re.fullmatch(r'([♭♯]?)([1-7])',s.strip().split('/')[0]);assert m,s
 return ([0,2,4,5,7,9,11][int(m[2])-1]+(-1 if m[1]=='♭'else 1 if m[1]=='♯'else 0))%12
def collection(h):return {deg(s)for s in re.search(r'\{([^}]+)\}',h['fields']['Modus/Tonvorrat'])[1].split(',')}
def segments(h):return [s for s in h['states']if s.get('#')!='D']
def end(h):return max(s['tick']+s['duration']for s in segments(h))
def seg(h,t):return next(s for s in segments(h)if s['tick']<=t%end(h)<s['tick']+s['duration'])
def may_sustain(h,at,length,pc,explicit_u=False):
 checks={at};period=end(h)
 for base in range(at//period*period,at+length,period):
  checks.update(base+s['tick']for s in segments(h)if at<base+s['tick']<at+length)
 for t in sorted(checks):
  c=seg(h,t);tones=set(c['pc_set'])
  # Chord bass is part of its printed local context; a replacement bass needs
  # a separate slash-bass/role decision even when this material check succeeds.
  if pc not in tones|collection(h)and not explicit_u:return False,t
 return True,None
pairs=[];hs=[h for h in harmonies if not any(s.get('#')=='D'for s in h['states'])]
for h in hs:
 for source in [r for r in items if r['kind']in('B','M','C')]:
  kind=source['kind'];result=dict(harmony=h['id'],source=source['id'],kind=kind,scope='Formal local material/timing only; not instrument, role, style or engine readiness.')
  if kind=='C':
   variants=source['permitted_pc_variants'];mode=collection(h);ok=[v for v in variants if set(v)<=mode]
   result.update(status='compatible_literal_cell'if ok else'needs_explicit_local_context_or_reject',admissible_pc_variants=ok,rule='No automatic chord-tone repair. No rotation/order/rhythm certification. For cells transposed at harmony roots an explicit transposition plan is still required.')
  elif kind=='M':
   starts=[]
   for start in range(0,end(h),3840):
    if all(may_sustain(h,start+n['at'],n['duration'],n['pitch']%12)[0]for n in source['notes']):starts.append(start)
   result.update(status='compatible_phrase_windows'if starts else'rejected_phrase_windows',start_ticks=starts,phrase_ticks=source['duration'],rests=source.get('rests',[]))
  else:
   pitches=source['pitches'];cycle=source.get('cycle_actual');events=[]
   if not pitches:result.update(status='compatible_silence');pairs.append(result);continue
   if source.get('rhythm_refs'):
    rhythm=by[source['rhythm_refs'][0]]
    if len(rhythm['layers'])>1:result.update(status='needs_layer_pitch_assignment');pairs.append(result);continue
    on=rhythm['onsets'];rep=cycle['rhythm_repeats']
    for r in range(rep):
     for j,t in enumerate(on):
      at=r*rhythm['period']+t;next_at=r*rhythm['period']+(on[j+1]if j+1<len(on)else rhythm['period']+on[0]);events.append((at,next_at-at,pitches[(r*len(on)+j)%len(pitches)]))
   else:
    duration_text=source['fields']['Rhythmus'];tokens=re.findall(r'(Pause\s+)?(\d+)',duration_text);times=[(bool(rest),int(n))for rest,n in tokens]
    if len(times)==1 and len(pitches)>1:times*=len(pitches)
    at=0;j=0
    for rest,duration in times:
     if not rest:events.append((at,duration,pitches[j%len(pitches)]));j+=1
     at+=duration
   period=cycle['period'];horizon=math.lcm(end(h),period);bad=None
   for base in range(0,horizon,period):
    for at,length,pitch in events:
     good,t=may_sustain(h,base+at,length,pitch%12,source['fields']['Typ']=='DIS')
     if not good:bad=dict(tick=t,pitch_class=pitch%12);break
    if bad:break
   result.update(status='compatible_explicit_U_material'if source['fields']['Typ']=='DIS'else'compatible_whole_cycle_material'if bad is None else'needs_gate_or_context_decision',joint_ticks=horizon,counterexample=bad,gate_scope='Full onset-to-next-onset envelope; actual per-role gates need independent checking. Explicit DIS is the source authorization, never global permission.')
  pairs.append(result)
(HERE/'PAIR_COMPATIBILITY.jsonl').write_text(''.join(json.dumps(p,ensure_ascii=False,separators=(',',':'))+'\n'for p in pairs))
accepted=collections.defaultdict(set)
for p in pairs:
 if p['status'].startswith('compatible'):accepted[p['harmony']].add(p['source'])
def inside(r,p):return r.get('xyz_ranges')is not None and all(lo<=v<=hi for (lo,hi),v in zip(r['xyz_ranges'],p))
cells=[]
for point in itertools.product((0,.5,1),repeat=3):
 active={k:[r for r in items if r['kind']==k and inside(r,point)]for k in('H','U','R','B','C','M')};plans=[]
 for h in active['H']:
  candidates=[r for k in('B','C','M')for r in active[k]if r['id']in accepted[h['id']]]
  # Keep source-R domain constraints distinct; do not widen them to force an answer.
  options=[r['id']for r in candidates if not r.get('rhythm_refs')or all(inside(by[i],point)for i in r['rhythm_refs'])]
  plans.append(dict(h=h['id'],material_options=options))
 i=points.index(point);filters=[]
 for variety in(0,.5,1):
  ids=selection[i,variety];filters.append(dict(variety=variety,candidates=len(ids),ids=ids,outside_declared_range=sum(not inside(by[id],point)for id in ids)))
 cells.append(dict(xyz=list(point),counts={k:len(v)for k,v in active.items()},strict_pair_options=sum(len(p['material_options'])for p in plans),plans=plans,existing_anchor_filter=filters))
# 1331-point coverage summary: source domains versus today's unchanged anchor cutoff.
dense=[]
for i,p in enumerate(points):
 counts={k:sum(r['kind']==k and inside(r,p)for r in items)for k in('H','U','R','B','C','M')}
 dense.append(dict(xyz=p,source_domain_counts=counts,selector=[dict(variety=v,candidates=len(selection[i,v]),outside_source_domain=sum(not inside(by[id],p)for id in selection[i,v]))for v in(0,.5,1)]))
dump('XYZ_COMPATIBILITY.json',dict(base='4c43bd2',engine_active_morricone_templates=0,grid='11³ including0/1 boundaries; three Variety settings; 27-cell detail includes all eight corners',pair_counts=dict(collections.Counter(p['status']for p in pairs)),source_pair_count=len(pairs),scope='H/U domains are NOT combined into one catalog. Selection simulation uses only all119H anchors with actual Generator::weight and keepRatio, not new profile weights. Domain/material compatibility is evaluated separately, no global XYZ change.',cells=cells,dense=dense))
# All 8436 triples: necessary compatibility, not a proof of temporal arrangement.
modules=[r for r in items if r['kind']=='K'];pairmatrix={}
for a,b in itertools.combinations(modules,2):
 def tag(a,b):
  f=a['fields'];id=b['id']
  if id in f.get('Ungeeignet',''):return 'reject'
  if id in f.get('Bedingt',''):return 'conditional'
  if id in f.get('Frei kombinierbar mit',''):return 'free'
  return 'unspecified'
 pairmatrix[a['id'],b['id']]=[tag(a,b),tag(b,a)]
triples=[]
for group in itertools.combinations(modules,3):
 flags=[];poly=collections.Counter();periods=[]
 for m in group:
  f=m['fields'];poly[f['Rolle']]+=int(f['Polyphonie']);period=re.match(r'\d+',f['Periode'])
  if period:periods.append(int(period[0]))
 for a,b in itertools.combinations(group,2):
  tags=pairmatrix[a['id'],b['id']]
  if 'reject'in tags:flags.append('pair_rejected')
  elif tags!=['free','free']:flags.append('conditional_or_unspecified_pair')
 for role,n in poly.items():
  if n>limits[role][0]:flags.append('summed_polyphony_needs_timeline_check')
 domains=[by[i]['xyz_ranges']for m in group for i in re.findall(r'EM-(?:[HURBCMPKTS]\d{3}|EF\d{2})',m['fields'].get('Quelle',''))if by[i].get('xyz_ranges')]
 intersection=[[max(r[d][0]for r in domains),min(r[d][1]for r in domains)]for d in range(3)]if domains else None
 if intersection and any(lo>hi for lo,hi in intersection):flags.append('source_domains_disjoint')
 triples.append(dict(ids=[m['id']for m in group],necessary_constraints_pass=not flags,flags=sorted(set(flags)),role_polyphony=dict(poly),period_lcm=math.lcm(*periods)if periods else None,source_domain_intersection=intersection,temporal_harmony_and_gate_proof=False))
(HERE/'MODULE_TRIPLES.jsonl').write_text(''.join(json.dumps(p,ensure_ascii=False,separators=(',',':'))+'\n'for p in triples))
asym=[dict(ids=list(k),tags=v)for k,v in pairmatrix.items()if v[0]!=v[1]]
dump('MODULE_COMPATIBILITY.json',dict(triples=len(triples),necessary_constraints_pass=sum(t['necessary_constraints_pass']for t in triples),no_triple_certified_playable=True,asymmetric_source_pairs=asym,flags=dict(collections.Counter(f for t in triples for f in t['flags'])),limits='Pairwise approvals and summed declared polyphony are preliminary filters. Sum above capacity does not prove simultaneous overflow; complementary timing could avoid it. No claim of simultaneous pitch/harmony/gate validity; module references are not playable runtime data. No resetting independent cycles at bar boundaries. Unperiodic modules remain lifecycle-bound, not forced into periodicity.'))
print('Probe',len(voicings),'transposed U boundaries;',len(pairs),'H/B/C/M pairs;',len(triples),'triples;',len(points),'XYZ points')
