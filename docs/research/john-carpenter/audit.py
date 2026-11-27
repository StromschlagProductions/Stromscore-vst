"""Offline JC source/MIDI analysis; never creates runtime data or changes the engine.
Run python docs/research/john-carpenter/audit.py. Curated judgments: assessment.json.
"""
from pathlib import Path
import re,json,csv,collections,zipfile,struct,math,hashlib
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[2]
text=(HERE/'STROMSCORE_John_Carpenter_Vokabular_Kanonisch.md').read_text(encoding='utf-8')
blocks={m[1]:dict(name=m[2],body=m[3],line=text[:m.start()].count('\n')+1) for m in re.finditer(r'^#### (JC-(?:EF|[HRQBMPST])\d+) ([^\n]+)\n(.*?)(?=^#{2,4} |\Z)',text,re.M|re.S)}
assert len(blocks)==405
assert len(list(re.finditer(r'^#### (JC-(?:EF|[HRQBMPST])\d+) ',text,re.M)))==405
kind=lambda id:re.sub(r'\d','',id[3:])
assert collections.Counter(kind(i) for i in blocks)==dict(H=88,R=67,Q=67,B=52,M=45,P=16,T=16,EF=12,S=42)
def dump(name,x):(HERE/name).write_text(json.dumps(x,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
def field(b,name):
 m=re.search(r'\*\*'+re.escape(name)+r':\*\* ([^\n]+)',b);return m[1] if m else None
def degree(s):
 # 4/flat5 is one enharmonic degree, never a polyphonic dyad.
 s=s.strip();m=re.fullmatch(r'([♭♯]?)([1-7])(?:/[♭♯]?[1-7])?([+-]\d+Okt)?',s);assert m,s
 return [0,2,4,5,7,9,11][int(m[2])-1]+(-1 if m[1]=='♭' else 1 if m[1]=='♯' else 0)+(12*int(m[3].replace('Okt','')) if m[3] else 0)
chtypes=json.loads((ROOT/'data/harmony/chord_types.json').read_text(encoding='utf-8'))['types'];records={};findings=[]
for id,v in blocks.items():
 b=v['body'];k=kind(id);xyz=re.search(r'(?:Anker |XYZ:\*\* |XYZ-Anker:\*\* )\(([\d,]+) / ([\d,]+) / ([\d,]+)\)',b)
 ranges=re.search(r'X: ([\d,]+)–([\d,]+) · Y: ([\d,]+)–([\d,]+) · Z: ([\d,]+)–([\d,]+)',b)
 r=dict(id=id,kind=k,name=v['name'],source_line=v['line'],xyz=[float(n.replace(',','.')) for n in xyz.groups()] if xyz else None,xyz_ranges=[[float(n.replace(',','.')) for n in ranges.groups()[j:j+2]] for j in (0,2,4)] if ranges else None,source_fields={m[1]:m[2] for m in re.finditer(r'\*\*([^*]+):\*\* ([^\n]+)',b)},refs=sorted(set(re.findall(r'JC-(?:EF|[HRQBMPST])\d+',b))),production_active=False)
 if k=='H':
  r['period_bars']=int(re.match(r'\d+',field(b,'Periode'))[0]);r['mode']=field(b,'Modus (Tonvorrat)');r['segments']=[]
  for m in re.finditer(r'^  - T(\d+)(?:–(\d+))?: Grundton ([^ ]+) – ([^:]+): (.*)',b,re.M):
   tones=[dict(degree=z[1],pitch=degree(z[1]),function=z[2]) for z in re.finditer(r'([^, ]+) \([^)]*, ([ATVFU])\)',m[5])];assert tones,(id,m[0]);root=degree(m[3]);intervals={(t['pitch']-root)%12 for t in tones};types=[c['id'] for c in chtypes if {i%12 for i in c['intervals']}==intervals]
   r['segments'].append(dict(start_bar=int(m[1]),end_bar=int(m[2] or m[1]),root=root,quality=m[4],tones=tones,exact_pc_types=types))
  assert r['segments'] and r['segments'][0]['start_bar']==1,(id,r['segments'])
  assert r['segments'][-1]['end_bar']==r['period_bars'],id
  assert all(a['end_bar']+1==z['start_bar'] for a,z in zip(r['segments'],r['segments'][1:])),id
  r['max_voices']=max(len(s['tones']) for s in r['segments']);r['chord_pc_data_fit']=all(s['exact_pc_types'] for s in r['segments']);r['strategies']=field(b,'Entwicklungsstrategien')
 elif k=='R':
  m=re.search(r'\*\*Taktart / Raster / Periode:\*\* ([\d/]+) · ([^·]+) · (\d+) Ticks',b);assert m,id
  r.update(meter=m[1],grid=m[2].strip(),period_ticks=int(m[3]));r['pattern']=re.search(r'\*\*Muster:\*\* `([^`]+)`',b)[1]
  on=re.search(r'\*\*Einsätze \((\d+)\):\*\* (.*?) \(!',b);r['onsets']=[dict(at=int(z[1]),accent=z[2]) for z in re.finditer(r'(\d+)([!°]?)',on[2])];assert len(r['onsets'])==int(on[1]),id
  r['duration_values']=list(map(int,re.findall(r'\d+',re.search(r'\*\*Notendauern:\*\* (.*?) Ticks',b)[1])));r['gate_mapping_known']=len(r['duration_values'])==1;r['independent_period']='**unabhängige Periode**' in b
  symbols=[(j,c) for j,c in enumerate(r['pattern']) if c in 'Xxo'];assert len(symbols)==len(r['onsets']),id
  r['grid_unit_ticks']=r['period_ticks']//len(r['pattern']);assert r['grid_unit_ticks']*len(r['pattern'])==r['period_ticks'],id
  assert [j*r['grid_unit_ticks'] for j,c in symbols]==[e['at'] for e in r['onsets']],id
  assert all(e['at']<r['period_ticks'] for e in r['onsets']),id
  assert [c for j,c in symbols]==['X' if e['accent']=='!' else 'o' if e['accent']=='°' else 'x' for e in r['onsets']],id
  gate_match=re.search(r'\(Gate (\d+(?:,\d+)?)',b);gate=float(gate_match[1].replace(',','.')) if gate_match else None
  if gate is not None and 'Gate-Liste' not in b:
   ev=[]
   for j,c in symbols:
    hold=1
    while hold<len(r['pattern']) and r['pattern'][(j+hold)%len(r['pattern'])]=='_':hold+=1
    ev.append(dict(at=j*r['grid_unit_ticks'],duration=round(r['grid_unit_ticks']*hold*gate),accent=c))
   if sorted({e['duration'] for e in ev})==sorted(r['duration_values']):r['gate_mapping_known']=True;r['events']=ev

 elif k in ('Q','B'):
  tones=re.search(r'\*\*Tonfolge \((\d+) Töne\):\*\* (.*?) →',b)
  if tones:r['pitches']=list(map(int,tones[2].split()));assert len(r['pitches'])==int(tones[1]),id
  else:
   raw=field(b,'Tonfolge');r['pitches']=[] if 'keine' in raw else [degree(re.match(r'[^ ]+',raw)[0])];r['held_or_absent']=raw
  rh=re.search(r'\*\*Rhythmus:\*\* (JC-R\d+)',b);r['rhythm_id']=rh[1] if rh else None;r['binding']=field(b,'Typ / Bindung') if k=='B' else None
  r['function_annotations']=re.findall(r'([^, =]+)=([ATVFU])',field(b,'Tonfunktionen') or '')
 elif k=='M':
  m=re.search(r'\*\*Noten \((\d+)\):\*\* (.*)',b);ns=[dict(degree=z[1],pitch=degree(z[1]),at=int(z[2]),duration=int(z[3]),velocity_override=int(z[4]) if z[4] else None) for z in re.finditer(r'([^; ]+) @ (\d+) Ticks, (\d+) Ticks(?:, v(\d+))?',m[2])];assert len(ns)==int(m[1]),id
  r['notes']=ns;r['length_ticks']=int(re.match(r'\d+',field(b,'Länge'))[0]);r['declared_roles']=field(b,'Rollen').split(';')[0].split();r['function_annotations']=re.findall(r'([^, =]+)=([ATVFU])',next(l for l in b.splitlines() if '**Tonfunktionen**' in l))
 elif k in ('S','EF'):
  file=re.search(r'\*\*MIDI:\*\* `([^`]+)`',b);r['midi_file']=file[1]
  meter=re.search(r'(\d+) Takte ([\d/]+)',b);r['bars']=int(meter[1]) if meter else int(re.search(r'(\d+) Takte',b)[1]);r['meter']=meter[2] if meter else '4/4';n,d=map(int,r['meter'].split('/'));r['bar_ticks']=960*4*n//d
  key=re.search(r'Tonart ([^, ]+)',b)[1];r['key_name']=key;r['key']={'C':0,'C♯':1,'D♭':1,'D':2,'E♭':3,'E':4,'F':5,'F♯':6,'G♭':6,'G':7,'G♯':8,'A♭':8,'A':9,'B♭':10,'H':11,'B':11}[key]
  harmony=field(b,'Harmonie') or field(b,'Harmonisches Grundfeld');r['harmonic_entries']=[]
  for z in re.finditer(r'ab T(\d+) (JC-H\d+)([^,]*)',harmony):
   block=re.search(r'Block ([+-]\d+)',z[3]);r['harmonic_entries'].append(dict(start_bar=int(z[1]),id=z[2],transpose=int(block[1]) if block else 0))
 records[id]=r
assert all(ref in records for r in records.values() for ref in r['refs'])
for r in records.values():
 if r['kind'] in ('Q','B') and r['rhythm_id']:
  rh=records[r['rhythm_id']];n=len(r['pitches']);a=len(rh['onsets']);cycles=n//math.gcd(n,a);r['cycle']=dict(pitch_count=n,attacks_per_rhythm=a,rhythm_ticks=rh['period_ticks'],rhythm_repetitions=cycles,total_ticks=cycles*rh['period_ticks'],total_attacks=cycles*a,rule='pitchIndex=globalAttackOrdinal%N; rhythm repeats with its own period; no bar reset',gate_phase_known=rh['gate_mapping_known'],joint_with_host_bar_ticks=math.lcm(cycles*rh['period_ticks'],960*4*int(rh['meter'].split('/')[0])//int(rh['meter'].split('/')[1])))
  r['duration_values']=rh['duration_values'];r['meter']=rh['meter']
  if 'gekoppelt' in r['source_fields'].get('Zyklus','') and n%a:findings.append(dict(id=r['id'],kind='cycle_clarification',detail='gekoppelt bedeutet gemeinsamer Gesamtzyklus, nicht eine einzelne Rhythmusperiode',cycle=r['cycle']))
# Independent SMF reader including running status and same-note overlap protection.
def vlq(b,p):
 n=0
 while True:
  c=b[p];p+=1;n=(n<<7)+(c&127)
  if c<128:return n,p
csvrows=list(csv.DictReader((HERE/'JC_Studien_Ereignisse.csv').open(newline='',encoding='utf-8-sig'),delimiter=';'))
expected=collections.Counter((r['datei'],r['rolle'],int(r['kanal']),*[int(r[f]) for f in ('tick_on','dauer','note','velocity')]) for r in csvrows)
actual=collections.Counter();studies={};notes=[];errors=[]
z=zipfile.ZipFile(HERE/'JC_Studien_MIDI.zip');assert z.testzip() is None
for entry in z.namelist():
 if not entry.lower().endswith('.mid'):continue
 data=z.read(entry);assert data[:4]==b'MThd';fmt,tracks,ppq=struct.unpack('>HHH',data[8:14]);assert ppq==960
 p0=8+int.from_bytes(data[4:8],'big');ns=[];end=0
 for tr in range(tracks):
  assert data[p0:p0+4]==b'MTrk';length=int.from_bytes(data[p0+4:p0+8],'big');b=data[p0+8:p0+8+length];p0+=8+length;p=0;t=0;running=None;role='';active={}
  while p<len(b):
   dt,p=vlq(b,p);t+=dt;status=b[p]
   if status>=128:p+=1
   else:assert running is not None;status=running
   if status==255:
    typ=b[p];p+=1;n,p=vlq(b,p);payload=b[p:p+n];p+=n
    if typ==3:role=payload.decode('latin1').split()[0]
    continue
   if status in (240,247):n,p=vlq(b,p);p+=n;continue
   running=status;kind0=status>>4;ch=(status&15)+1;pitch=b[p];p+=1;vel=b[p] if kind0 not in (12,13) else 0
   if kind0 not in (12,13):p+=1
   if kind0==9 and vel:
    assert (ch,pitch) not in active,(entry,'overlap',role,t,pitch);active[ch,pitch]=(t,vel)
   elif kind0==8 or kind0==9 and vel==0:
    assert (ch,pitch) in active,(entry,'orphan',role,t,pitch);at,v=active.pop((ch,pitch));assert t>at
    n=dict(file=Path(entry).name,role=role,channel=ch,at=at,duration=t-at,pitch=pitch,velocity=v);ns.append(n);actual[Path(entry).name,role,ch,at,t-at,pitch,v]+=1
  assert not active,(entry,'hanging',role);end=max(end,t)
 sid=next(r['id'] for r in records.values() if r.get('midi_file')==Path(entry).name);sr=records[sid];assert end<=sr['bars']*sr['bar_ticks'],(sid,end,sr)
 notes+=ns;roles={}
 for role in sorted({n['role'] for n in ns}):
  rn=[n for n in ns if n['role']==role];cur=mx=0
  for at,d in sorted([(n['at'],1) for n in rn]+[(n['at']+n['duration'],-1) for n in rn]):cur+=d;mx=max(mx,cur)
  roles[role]=dict(notes=len(rn),polyphony=mx,min_duration=min(n['duration'] for n in rn),max_duration=max(n['duration'] for n in rn),pitch_min=min(n['pitch'] for n in rn),pitch_max=max(n['pitch'] for n in rn))
 studies[sid]=dict(file=Path(entry).name,notes=len(ns),end_tick=end,nominal_end_tick=sr['bars']*sr['bar_ticks'],trailing_silence_ticks=sr['bars']*sr['bar_ticks']-end,roles=roles)
assert expected==actual,('CSV/MIDI mismatch',list((expected-actual).items())[:3],list((actual-expected).items())[:3])
assert len(notes)==16046 and len(studies)==54
assert all(n['pitch']==36 for n in notes if n['role']=='ST')
assert all(int(r['tick_off'])-int(r['tick_on'])==int(r['dauer']) for r in csvrows)
# Role ranges from the research, distinct from configurable engine/patch ranges.
ranges=dict(LF=(33,91),KF=(40,84),LB=(21,52),KB=(28,64),AR=(45,100),TU=(48,108),ST=(36,36),GS=(36,96),HM=(48,96))
limits=dict(LF=(6,4026531840),KF=(9,720),LB=(1,4026531840),KB=(1,960),AR=(1,7680),TU=(4,720),ST=(1,480),GS=(2,4026531840),HM=(1,4026531840))
constraint=[]
for sid,st in studies.items():
 for role,v in st['roles'].items():
  if role not in ranges:raise AssertionError(role)
  lo,hi=ranges[role];assert lo<=v['pitch_min']<=v['pitch_max']<=hi,(sid,role,v)
  violations=[]
  if v['polyphony']>limits[role][0]:violations.append('polyphony')
  if v['min_duration']<240:violations.append('minimum_duration')
  if v['max_duration']>limits[role][1]:violations.append('maximum_duration')
  if violations:constraint.append(dict(id=sid,role=role,violations=violations,actual=v,default_polyphony=limits[role][0],default_min_duration=240,default_max_duration=limits[role][1]))
# All twelve transpositions, no automatic register folding; fixed trigger stays put.
transpositions=[]
for shift in range(12):
 bad=collections.Counter();midi_bad=collections.Counter()
 for n in notes:
  sid=next(i for i,st in studies.items() if st['file']==n['file']);p=n['pitch']+(0 if n['role']=='ST' else shift-records[sid]['key']);lo,hi=ranges[n['role']]
  if not lo<=p<=hi:bad[n['role']]+=1
  if not 0<=p<=127:midi_bad[n['role']]+=1
 transpositions.append(dict(target_key_pc=shift,research_range_violations=dict(bad),midi_range_violations=dict(midi_bad)))
# Store notes only as CSV references; no duplicate 16k-event JSON rendering.
for sid,st in studies.items():records[sid]['reference_midi']=st
analysis=dict(base='4937722',engine='023b0a6',counts=dict(collections.Counter(r['kind'] for r in records.values())),midi=dict(files=len(studies),notes=len(notes),ppq=960,csv_equal=True,same_note_overlaps=0,note_pair_errors=0,stich_notes=sum(n['role']=='ST' for n in notes),stich_fixed_36=True,functions=dict(collections.Counter(r['tonfunktion'] for r in csvrows)),studies=studies),default_instrument_conflicts=constraint,transpositions=transpositions,findings=findings,scope='Source/SMF/CSV analysis only. Instrument assumptions are not actual external patches; no engine renderings.')
# Analytic harmonies: exact printed voices, no inferred tonic harmony.
def context_at(sr,t):
 entries=sr['harmonic_entries'];entry=next((e for e in reversed(entries) if t>=(e['start_bar']-1)*sr['bar_ticks']),entries[0]);h=records[entry['id']];bar=(t//sr['bar_ticks']-(entry['start_bar']-1))%h['period_bars']+1;s=next(s for s in h['segments'] if s['start_bar']<=bar<=s['end_bar']);shift=sr['key']+entry['transpose'];return h,s,shift
mode_steps={'Äolisch':{0,2,3,5,7,8,10},'Ionisch':{0,2,4,5,7,9,11},'Dorisch':{0,2,3,5,7,9,10},'Phrygisch':{0,1,3,5,7,8,10},'Lokrisch':{0,1,3,5,6,8,10},'Lydisch':{0,2,4,6,7,9,11},'Harmonisch':{0,2,3,5,7,8,11},'Chromatisch':set()}
def collection(mode):return next(v for k,v in mode_steps.items() if mode.startswith(k))
# Function labels are tested at attack and at every harmonic change under held notes.
semantic=[];held_changes=[];v_targets=[]
byrole=collections.defaultdict(list)
for row in csvrows:byrole[row['studie'],row['rolle']].append(row)
for rows in byrole.values():rows.sort(key=lambda r:(int(r['tick_on']),int(r['note'])))
for row in csvrows:
 sid=row['studie'];sr=records[sid];at=int(row['tick_on']);end=int(row['tick_off']);pitch=int(row['note']);fn=row['tonfunktion'];source=[records[x] for x in re.findall(r'JC-(?:EF|[HRQBMPST])\d+',row['quelle'])]
 if row['rolle']=='ST':continue
 h,s,shift=context_at(sr,at);relative=(pitch-shift)%12;defined={p['pitch']%12:p['function'] for p in s['tones']};basepc={p['pitch']%12 for p in s['tones'] if p['function']=='A'}
 if fn=='A' and relative not in basepc:semantic.append(dict(id=sid,role=row['rolle'],at=at,pitch=pitch,kind='A_not_in_declared_A',context=h['id'],source=row['quelle']))
 if fn=='T' and relative not in collection(h['mode']) and relative not in defined:semantic.append(dict(id=sid,role=row['rolle'],at=at,pitch=pitch,kind='T_outside_H_mode',context=h['id'],source=row['quelle']))
 if fn=='V':
  later=[r for r in byrole[sid,row['rolle']] if int(r['tick_on'])>at];target=later[0] if later else None;ok=False
  if target:
   th,ts,tshift=context_at(sr,int(target['tick_on']));ok=abs(int(target['note'])-pitch) in (1,2) and (int(target['note'])-tshift)%12 in {p['pitch']%12 for p in ts['tones'] if p['function']=='A'}
  v_targets.append(dict(id=sid,role=row['rolle'],at=at,pitch=pitch,target_at=int(target['tick_on']) if target else None,target_pitch=int(target['note']) if target else None,gap_ticks=int(target['tick_on'])-end if target else None,valid_step_to_A=ok))
 # Check true context changes, not every bar; include full held-note span.
 initial=(h['id'],s['start_bar'],shift)
 for tick in range((at//sr['bar_ticks']+1)*sr['bar_ticks'],end,sr['bar_ticks']):
  hh,ss,sh=context_at(sr,tick);key=(hh['id'],ss['start_bar'],sh)
  if key==initial:continue
  initial=key;pc=(pitch-sh)%12;legal=pc in {p['pitch']%12 for p in ss['tones']} or pc in collection(hh['mode'])
  if not legal:
   pedal=any('Dissonanzpedal' in (r.get('binding') or '') for r in source);authorized=fn in ('F','U') or pedal or 'Blockverschiebung' in sr['source_fields'].get('Entwicklungsstrategie','')
   held_changes.append(dict(id=sid,role=row['rolle'],note_on=at,change_tick=tick,pitch=pitch,new_harmony=hh['id'],source=row['quelle'],attack_function=fn,explicit_pedal_or_FU_or_block=authorized))
analysis['semantic_checks']=dict(attack_label_findings=semantic,v_targets=v_targets,v_bad_targets=[r for r in v_targets if not r['valid_step_to_A']],held_foreign_at_changes=held_changes,scope='Reconstructed printed H timeline, key and explicit block changes. T-check uses H mode; 62 discrepancies need explicit resolution of local Q/B/M vs H context scope, not necessarily different notes. Findings require source review, not automatic note correction; F/U authorizations must additionally be semantically checked.')
# Compare layer-activation descriptions to observed note-on windows.
window_findings=[]
for id,sr in records.items():
 if sr['kind'] not in ('S','EF'):continue
 grouped=collections.defaultdict(list)
 for match in re.finditer(r'^  - (AR|GS|HM|KB|TU|LB):[^\n]*?\(T([\d,–-]+)\)',blocks[id]['body'],re.M):
  for item in match[2].split(','):
   q=re.split('[–-]',item);grouped[match[1]].append((int(q[0]),int(q[-1])))
 for role,windows in grouped.items():
  for row in byrole[id,role]:
   bar=int(row['tick_on'])//sr['bar_ticks']+1
   if not any(a<=bar<=z for a,z in windows):window_findings.append(dict(id=id,role=role,at=int(row['tick_on']),bar=bar,declared_windows=windows));break
analysis['study_window_findings']=window_findings
# Full pitch/rhythm periods of all Q/B figures, including those not used in a study.
cycles=[dict(id=r['id'],**r['cycle']) for r in records.values() if 'cycle' in r]
nonperiodic=[dict(id=r['id'],kind='silence' if not r['pitches'] else 'held_or_rearticulated',source_instruction=r['held_or_absent'],rearticulation_ticks=int(re.search(r'alle (\d+) Takte',r['held_or_absent'])[1])*3840 if re.search(r'alle (\d+) Takte',r['held_or_absent']) else None) for r in records.values() if r['kind']=='B' and not r.get('rhythm_id')]
rhythms=[dict(id=r['id'],own_period_ticks=r['period_ticks'],bar_ticks=960*4*int(r['meter'].split('/')[0])//int(r['meter'].split('/')[1]),joint_with_host_bar_ticks=math.lcm(r['period_ticks'],960*4*int(r['meter'].split('/')[0])//int(r['meter'].split('/')[1])),gate_mapping_known=r['gate_mapping_known']) for r in records.values() if r['kind']=='R']
assert len(cycles)+len(nonperiodic)==119 and len(rhythms)==67
dump('CYCLE_ANALYSIS.json',dict(rule='N/gcd(N,A) rhythm repetitions; joint pitch/rhythm cycle. Additional gate phases unresolved unless their event mapping is explicit.',cycles=cycles,nonperiodic_bass=nonperiodic,rhythms=rhythms))
# Base registration limits at all twelve target keys; no hidden octave-folding.
for r in records.values():
 if r['kind'] not in ('Q','B','M'):continue
 pitches=r.get('pitches') or [n['pitch'] for n in r.get('notes',[])]
 roles0=r.get('declared_roles') or (['LB','KB'] if r['kind']=='B' else ['AR','GS'])
 bases=dict(LF=48,KF=48,LB=24,KB=36,AR=60,TU=60,ST=36,GS=60,HM=48)
 r['register_projection']={role:dict(valid_target_keys=[key for key in range(12) if all(ranges[role][0]<=bases[role]+key+p<=ranges[role][1] for p in pitches)],pitch_min_C=bases[role]+min(pitches) if pitches else None,pitch_max_C=bases[role]+max(pitches) if pitches else None) for role in roles0}

# Specific measurable source observations, without changing canonical inputs.
analysis['rotation_S35']=[dict(bars=[a,a+15],pulse_roles=sorted({row['rolle'] for row in csvrows if row['studie']=='JC-S35' and row['rolle'] in ('KB','AR','GS') and a<=int(row['takt'])<=a+15})) for a in (1,17,33,49)]
analysis['min_duration_ticks']=min(n['duration'] for n in notes)
analysis['study_description_counts']=[dict(id=id,declared=int(__import__('re').search(r' · (\d+) Noten',records[id]['source_fields']['MIDI'])[1]),actual=st['notes']) for id,st in studies.items() if __import__('re').search(r' · (\d+) Noten',records[id]['source_fields']['MIDI'])]
assert all(r['declared']==r['actual'] for r in analysis['study_description_counts'])
analysis['declared_source_mode_scope']='H-mode validity and local Q/B/M-mode validity are distinct; do not silently union them.'
# Explicit next-note targets also for every M and Q/B source labeled V.
source_resolutions=[]
for r in records.values():
 if r['kind'] not in ('M','Q','B'):continue
 if r['kind']=='M':ps=[n['pitch'] for n in r['notes']]
 else:ps=r.get('pitches',[])
 ann=r.get('function_annotations',[])
 for j,(dg,fn) in enumerate(ann[:len(ps)]):
  if fn!='V':continue
  target=j+1 if j+1<len(ps) else 0 if r['kind'] in ('Q','B') else None
  source_resolutions.append(dict(id=r['id'],index=j,pitch=ps[j],target_index=target,target_pitch=ps[target] if target is not None else None,step_valid=target is not None and abs(ps[target]-ps[j]) in (1,2)))
analysis['source_V_targets']=source_resolutions

# Per-role actual pitch-cycle evidence, including tests that distinguish a bar reset.
pitch_evidence=[]
for (sid,role),rows in byrole.items():
 sources=collections.defaultdict(list)
 for row in rows:
  ids=[x for x in re.findall(r'JC-[QB]\d+',row['quelle']) if records[x].get('rhythm_id')]
  if ids:sources[ids[0]].append(row)
 for srcid,events in sources.items():
  src=records[srcid];seq=src['pitches'];sr=records[sid];actual_pc=[int(r['note'])%12 for r in events];models=[]
  for follows in (False,True):
   expect=[];barreset=[];ordinal=0;perbar=collections.Counter()
   for row in events:
    at=int(row['tick_on']);hh,ss,sh=context_at(sr,at);root=(ss['root'] if follows else 0)+(sh-sr['key']);expect.append((sr['key']+root+seq[ordinal%len(seq)])%12);bar=at//sr['bar_ticks'];barreset.append((sr['key']+root+seq[perbar[bar]%len(seq)])%12);perbar[bar]+=1;ordinal+=1
   # Octaves do not change PC. Do not fit an arbitrary per-note offset.
   mismatches=sum(a!=b for a,b in zip(expect,actual_pc));resets=sum(a!=b for a,b in zip(barreset,actual_pc));models.append(dict(follows_harmonic_root=follows,continuous_mismatches=mismatches,bar_reset_mismatches=resets))
  pitch_evidence.append(dict(id=sid,role=role,source=srcid,notes=len(events),models=models))
analysis['pitch_cycle_evidence']=pitch_evidence
# The literal requirements of every template are distinct from the 54 study arrangements.
for r in records.values():
 if r['kind']=='H':
  ps=[t['pitch'] for z in r['segments'] for t in z['tones']];r['register_projection']={'LF':dict(valid_target_keys=[key for key in range(12) if all(33<=48+key+p<=91 for p in ps)],pitch_min_C=48+min(ps),pitch_max_C=48+max(ps))};r['target_requirements']=dict(role='LF',polyphony=r['max_voices'],default_polyphony_compatible=r['max_voices']<=6)
 elif r['kind'] in ('Q','B','M'):
  durations=[n['duration'] for n in r['notes']] if r['kind']=='M' else r.get('duration_values',[]);roles0=r.get('declared_roles') or (['LB','KB'] if r['kind']=='B' else ['AR','GS'])
  r['target_requirements']={role:dict(min_duration=min(durations) if durations else None,max_duration=max(durations) if durations else None,default_duration_compatible=bool(durations) and min(durations)>=240 and max(durations)<=limits[role][1],scope='Not a statement about an externally loaded patch. Held drone has separately unbounded intended lifetime.') for role in roles0}
 elif r['kind']=='R':r['default_duration_compatible_targets']=[role for role in limits if role!='ST' and min(r['duration_values'])>=240 and max(r['duration_values'])<=limits[role][1]]

# Explicit, inspectable authorization reasons for every F/U note, no global bypass.
authorizations=[]
for row in csvrows:
 if row['tonfunktion'] not in ('F','U'):continue
 sid=row['studie'];sr=records[sid];at=int(row['tick_on']);pitch=int(row['note']);hh,ss,sh=context_at(sr,at);reasons=[]
 if any((t['pitch']+sh)%12==pitch%12 and t['function'] in ('F','U') for t in ss['tones']):reasons.append('explicit_H_tone')
 for srcid in re.findall(r'JC-(?:EF|[HRQBMPST])\d+',row['quelle']):
  src=records[srcid]
  if 'Dissonanzpedal' in (src.get('binding') or ''):reasons.append('dissonance_pedal')
  for dg,fn in src.get('function_annotations',[]):
   if fn in ('F','U') and any((degree(dg)+sr['key']+root)%12==pitch%12 for root in (0,ss['root'])):reasons.append('explicit_source_FU')
 if row['quelle']=='Feldton' and any((int(n)+sr['key'])%12==pitch%12 for n in re.findall(r'N:([+-]?\d+):\d+:U',sr['source_fields'].get('Zulässige Einzelereignisse',''))):reasons.append('explicit_field_event_U')
 authorizations.append(dict(id=sid,role=row['rolle'],at=at,pitch=pitch,function=row['tonfunktion'],source=row['quelle'],reasons=sorted(set(reasons))))
analysis['FU_authorizations']=authorizations
analysis['FU_missing_authorizations']=[r for r in authorizations if not r['reasons']]
# Note-ons by every 16-bar band distinguish the promised S35 rotation from density slogans.
analysis['rotation_S35_attacks']=[dict(bars=[a,a+15],counts=dict(collections.Counter(row['rolle'] for row in csvrows if row['studie']=='JC-S35' and row['rolle'] in ('KB','AR','GS') and a<=int(row['takt'])<=a+15))) for a in (1,17,33,49)]
# Curated assessments and source-specific structured evidence produce the final inventory.
assessment=json.loads((HERE/'assessment.json').read_text(encoding='utf-8'));assert set(assessment['entries'])==set(records)
for id,r in records.items():
 r.update(assessment['entries'][id]);assert r['classification'] in assessment['classes'];assert set(r['required_capabilities'])<=assessment['capabilities'].keys()
analysis['classification_counts']=dict(collections.Counter(r['classification'] for r in records.values()))
analysis['classification_by_kind']={k:dict(collections.Counter(r['classification'] for r in records.values() if r['kind']==k)) for k in ('H','R','Q','B','M','P','T','EF','S')}
dump('TECHNICAL_INVENTORY.json',dict(base='4937722',engine='023b0a6',scope=assessment['scope'],classes=assessment['classes'],capabilities=assessment['capabilities'],templates=list(records.values())))
lines=['# JC – vollständige technische Einzelbewertung','','Ausgang `4937722`, Engine unverändert `023b0a6`. 405 IDs. D = direkt darstellbare Grundform, A = begrenzte Anbindung, E = gemeinsame Fähigkeit fehlt, K = konkrete Klärung. Keine Vorlage ist aktiviert. Optionale Transformationen sind keine automatisch freigegebenen Varianten. Exakte Quellfelder und Zeit-/Register-/Periodendaten: [TECHNICAL_INVENTORY.json](TECHNICAL_INVENTORY.json).','']
for k in ('H','R','Q','B','M','P','T','EF','S'):
 lines+=['## '+k,'','| ID / Name | Klasse | Konkreter Grund / Voraussetzung |','|---|---|---|']
 for r in records.values():
  if r['kind']!=k:continue
  reason=r['reason']+' Benötigt: '+', '.join(r['required_capabilities'])+'.';lines.append('| [%s](STROMSCORE_John_Carpenter_Vokabular_Kanonisch.md) (Z.%s) %s | %s | %s |'%(r['id'],r['source_line'],r['name'],r['classification'],reason.replace('|','/').replace('\n',' ')))
(HERE/'TECHNICAL_INVENTORY.md').write_text('\n'.join(lines)+'\n',encoding='utf-8')

dump('VALIDATION_RESULTS.json',analysis)
print('Parsed',len(records),'MIDI',len(studies),len(notes),'role constraints',len(constraint))
