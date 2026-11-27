"""Offline source and SMF audit. No runtime import; originals are immutable.
Run from any directory: python docs/research/ennio-morricone/audit.py
"""
from pathlib import Path
import re,json,csv,collections,zipfile,struct,math,hashlib,itertools,statistics
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[2]
TEXT=(HERE/'STROMSCORE_Ennio_Morricone_Vokabular_Kanonisch.md').read_text()
def dump(name,data):(HERE/name).write_text(json.dumps(data,ensure_ascii=False,indent=2)+'\n')
def fields(body):return {m[1].strip():m[2].strip().strip(' ·') for m in re.finditer(r'\*\*([^*\n]+):\*\*\s*([^\n]*?)(?=\s*·\s*\*\*|\n|$)',body)}
def nums(s):return [int(n) for n in re.findall(r'[+-]?\d+',s)]
def bracket(s):
 m=re.search(r'\[([^]]*)\]',s);return nums(m[1])if m else []
def degree(s):
 m=re.fullmatch(r'([♭♯]?)([1-7])',s.strip().split('/')[0]);assert m,s
 return ([0,2,4,5,7,9,11][int(m[2])-1]+(-1 if m[1]=='♭' else 1 if m[1]=='♯' else 0))%12
def bar_ticks(f):
 n,d=map(int,re.search(r'(\d+)/(\d+)',f.get('Takt','4/4')).groups());return 960*4*n//d
def table(body):
 header=None;rows=[]
 for line in body.splitlines():
  if not line.startswith('|'):continue
  cols=[s.strip()for s in line.strip('|').split('|')]
  if all(re.fullmatch(r'[-: ]+',s)for s in cols):continue
  if header is None:header=cols
  else:assert len(header)==len(cols),(header,cols);rows.append(dict(zip(header,cols)))
 return rows
occ=collections.defaultdict(list)
for m in re.finditer(r'^### (EM-(?:EF\d{2}|[HURBCMPKS]\d{3})) – ([^\n]+)\n(.*?)(?=^#{1,3} |\Z)',TEXT,re.M|re.S):
 occ[m[1]].append(dict(name=m[2],line=TEXT[:m.start()].count('\n')+1,body=m[3]))
records={}
chtypes=json.loads((ROOT/'data/harmony/chord_types.json').read_text())['types']
for id,os in occ.items():
 b=os[0]['body'];f=fields(b);kind=re.sub(r'\d','',id[3:]);r=dict(id=id,kind=kind,name=os[0]['name'],source_line=os[0]['line'],occurrences=[o['line']for o in os],fields=f,refs=sorted(set(re.findall(r'EM-(?:EF\d{2}|[HURBCMPKTS]\d{3})',b))),production_active=False)
 xyz=re.search(r'\*\*XYZ-Anker:\*\* ([^·\n]+)',b)
 def number(s):return None if 'beliebig' in s else float(s.strip().replace(',','.'))
 r['xyz']=[number(s) for s in xyz[1].split('/')]if xyz else None
 rg=re.search(r'\*\*Gültigkeit:\*\* X ([\d,]+)–([\d,]+) · Y ([\d,]+)–([\d,]+) · Z ([\d,]+)–([\d,]+)',b)
 r['xyz_ranges']=[[float(n.replace(',','.'))for n in rg.groups()[j:j+2]]for j in (0,2,4)]if rg else [[max(0,v-.2),min(1,v+.2)]if v is not None else [0,1]for v in r['xyz']]if r['xyz'] else None
 if kind in ('H','U'):
  r['states']=table(b)
  for row in r['states']:
   row['pitches']=bracket(row.get('Oberstimmen (rel)','[]'));row['bass']=int(row.get('Bass (rel)',row.get('Bass','0')))if row.get('Bass (rel)',row.get('Bass','0'))not in ('–','—')else None;row['tick']=int(row['Tick']);row['duration']=int(row.get('Dauer','3840'))
   mask={p%12 for p in row['pitches']}|({row['bass']%12}if row['bass']is not None else set())
   row['pc_set']=sorted(mask);row['matching_types_any_root']=[{'root':root,'type':t['id']}for root in range(12)for t in chtypes if {(root+n)%12 for n in t['intervals']}==mask]
  for st in r['states']:
   label=st.get('Klang',st.get('Harmonie',''));root=re.match(r'\[([^]]+)\]',label)
   st['root']=degree(root[1])if root else None
   upper={n%12 for n in st['pitches']};full=set(upper)
   if st['bass']is not None:full.add(st['bass']%12)
   st['types_at_declared_root']=[t['id']for t in chtypes if st['root']is not None and {(st['root']+n)%12 for n in t['intervals']} in (upper,full)]
   st['unrooted_object']=st['root']is None
  r['voices']=sorted(set(len(s['pitches'])for s in r['states']));r['state_count']=len(r['states']);r['pc_data_fit']=all(s['types_at_declared_root']for s in r['states'])
  if kind=='H':r['progression']=re.search(r'\*\*Progression \(Notation\):\*\* `([^`]+)`',b)[1]
  else:
   r['held_requests']=re.findall(r'tatsächlich gehalten: ([^\n]*?)(?= · bewegt:|\n|$)',b)
   r['required_held_pitches']=[[int(v)for v in re.findall(r'([+-]\d+) \(Rolle',line)]for line in r['held_requests']]
   r['literal_common_pitches']=[sorted(set(a['pitches'])&set(z['pitches'])) for a,z in zip(r['states'],r['states'][1:])]
   r['fixed_index_holds']=[[a['pitches'][i]for i in range(min(len(a['pitches']),len(z['pitches']))) if a['pitches'][i]==z['pitches'][i]]for a,z in zip(r['states'],r['states'][1:])]
 elif kind=='R':
  layers=[]
  for line in b.splitlines():
   ff=fields(line)
   if any('Muster' in key for key in ff) or 'Einsätze (Ticks)'in ff:
    period=int(re.match(r'\d+',ff['Periode'])[0]);onsets=nums(ff['Einsätze (Ticks)']);pattern=next((v.strip('`')for k,v in ff.items()if 'Muster'in k),'')
    unit=int(re.search(r'(\d+) Ticks',f['Raster'])[1])if re.search(r'(\d+) Ticks',f['Raster'])else None
    if unit is None:pattern=''
    positions=[i*unit for i,c in enumerate(pattern)if c in 'Xxo']if pattern else None
    layers.append(dict(name=next((k for k in ff if 'Muster'in k),'ametrisch'),period=period,onsets=onsets,pattern=pattern,unit=unit,accents=nums(ff.get('Akzente','')),source_fields=ff,onsets_match_pattern=positions==onsets if positions is not None else None))
  assert layers,id
  r['layers']=layers;r.update({k:v for k,v in layers[0].items()if k!='name'});r['bar_ticks']=bar_ticks(f);r['joint_bar_ticks']=math.lcm(r['bar_ticks'],*[l['period']for l in layers]);r['off_old_grid']=any(t%240 for l in layers for t in l['onsets'])
 elif kind=='B':
  r['pitches']=bracket(f['Töne (rel)']);r['rhythm_refs']=[i for i in r['refs']if i.startswith('EM-R')]
  r['cycle_declared']=f['Gesamtzyklus'];r['intervals_actual']=[z-a for a,z in zip(r['pitches'],r['pitches'][1:])]
 elif kind=='C':
  r['pitches']=[degree(s)for s in re.search(r'\{([^}]+)\}',f['Tonhöhenmenge (Stufen)'])[1].split(',')];r['prime_declared']=bracket(f['Primform']);r['iv_declared']=list(map(int,re.search(r'<([0-9]{6})>',f['Intervallvektor'])[1]))
  exchange=re.search(r'Austauschtöne: ([^·\n]+)',f['Tonhöhenmenge (Stufen)'])
  r['exchange_tones']=[degree(n.strip())for n in exchange[1].split('|')]if exchange else []
  r['permitted_pc_variants']=[sorted(set(r['pitches'])|{n})for n in r['exchange_tones']]if exchange else [sorted(r['pitches'])]
 elif kind=='M':
  r['notes']=[];r['rests']=[];at=0
  for m in re.finditer(r'(Pause|[+-]?\d+)/(\d+)',f['Töne/Dauern']):
   duration=int(m[2])
   if m[1]=='Pause':r['rests'].append(dict(at=at,duration=duration))
   else:r['notes'].append(dict(pitch=int(m[1]),at=at,duration=duration))
   at+=duration
  r['duration']=at;r['note_count']=len(r['notes']);r['declared_duration']=int(re.match(r'\d+',f['Länge'])[0])*bar_ticks(f);r['length_matches']=at==r['declared_duration'];r['intervals_actual']=[z['pitch']-a['pitch']for a,z in zip(r['notes'],r['notes'][1:])];r['off_old_grid']=any(n['at']%240 or n['duration']%240 for n in r['notes'])
 if kind in ('S','EF'):
  study=os[-1];r['study_fields']=fields(study['body']);r['study_line']=study['line'];r['midi_file']=r['study_fields'].get('Datei');r['study_refs']=sorted(set(re.findall(r'EM-(?:EF\d{2}|[HURBCMPKTS]\d{3})',study['body'])))
 records[id]=r
for line in TEXT.splitlines():
 if not re.match(r'^\| EM-T\d{3} \|',line):continue
 c=[s.strip()for s in line.strip('|').split('|')];id=c[0];assert id not in records
 records[id]=dict(id=id,kind='T',name=c[1],source_line=TEXT[:TEXT.index(line)].count('\n')+1,fields=dict(zip(['Verfahren','Parameter','Invariante','Risiko','Evidenz'],c[2:])),refs=[],production_active=False,xyz=None,xyz_ranges=None)
assert len(records)==534,len(records)
assert collections.Counter(r['kind']for r in records.values())==dict(H=119,U=50,R=64,B=52,C=46,M=50,P=22,K=38,EF=16,T=20,S=57)
assert all(ref in records for r in records.values() for ref in r['refs']+r.get('study_refs',[]))
# Canonical PC-set prime form, independent of order, transposition and inversion.
def normal_form(ps):
 ps=sorted(set(n%12 for n in ps));rots=[]
 for i in range(len(ps)):
  a=ps[i:]+[n+12 for n in ps[:i]];a=[n-a[0]for n in a];rots.append(a)
 return min(rots,key=lambda a:tuple(reversed(a[1:])))
def prime(ps):return min(normal_form(ps),normal_form([-n for n in ps]))
for r in records.values():
 if r['kind']=='C':
  ps=sorted(set(r['pitches']));iv=[0]*6
  for a,b in itertools.combinations(ps,2):iv[min((b-a)%12,(a-b)%12)-1]+=1
  r['variant_analysis']=[]
  for variant in r['permitted_pc_variants']:
   vv=[0]*6
   for a,b in itertools.combinations(variant,2):vv[min((b-a)%12,(a-b)%12)-1]+=1
   r['variant_analysis'].append(dict(pcs=variant,prime=prime(variant),iv=vv))
  r['prime_actual']=prime(ps);r['iv_actual']=iv;r['prime_matches']=r['prime_actual']==r['prime_declared'];r['prime_tni_equivalent']=any({(sign*n+t)%12 for n in ps}==set(r['prime_declared'])for sign in(-1,1)for t in range(12));r['iv_matches']=iv==r['iv_declared']
 if r['kind']=='B':
  own=re.search(r'eigene Dauern: (.*)',r['fields']['Rhythmus'])
  if own:
   ds=nums(own[1]);ds=ds*len(r['pitches'])if len(ds)==1 and len(r['pitches'])>1 else ds;r['cycle_actual']=dict(attacks=len(r['pitches']),period=sum(ds),joint_bar=math.lcm(sum(ds),bar_ticks(r['fields'])),durations=ds)
  elif r['rhythm_refs']:
   rh=records[r['rhythm_refs'][0]];n=len(r['pitches']);a=len(rh['onsets']);rep=n//math.gcd(n,a)if n else 1;r['cycle_actual']=dict(attacks=rep*a,period=rep*rh['period'],rhythm_repeats=rep,joint_bar=math.lcm(rep*rh['period'],bar_ticks(r['fields'])))
for r in records.values():
 if r['kind']=='M':
  cell_refs=[id for id in r['refs']if id.startswith('EM-C')]
  r['declared_cell_fit']={id:any({n['pitch']%12 for n in r['notes']}<=set(v)for v in records[id]['permitted_pc_variants'])for id in cell_refs}
dump('SOURCE_RECORDS.json',list(records.values()))
# MIDI reader, including running status and explicit active-note balance.
def vlq(b,p):
 n=0
 while True:
  c=b[p];p+=1;n=(n<<7)|(c&127)
  if c<128:return n,p
rows=list(csv.DictReader((HERE/'EM_Studien_Ereignisse.csv').open(newline='',encoding='utf-8-sig'),delimiter=';'))
expected=collections.Counter((r['datei'],r['rolle'],*[int(r[f])for f in ('tick','dauer_ticks','midi','velocity')])for r in rows)
actual=collections.Counter();channels=collections.defaultdict(set);midi_notes=[];studies={}
z=zipfile.ZipFile(HERE/'EM_Studien_MIDI.zip');assert z.testzip()is None
for filename in z.namelist():
 if not filename.lower().endswith('.mid'):continue
 data=z.read(filename);assert data[:4]==b'MThd';fmt,tracks,ppq=struct.unpack('>HHH',data[8:14]);assert ppq==960
 pos=8+int.from_bytes(data[4:8],'big');ns=[];end=0
 for tr in range(tracks):
  assert data[pos:pos+4]==b'MTrk';ln=int.from_bytes(data[pos+4:pos+8],'big');b=data[pos+8:pos+8+ln];pos+=8+ln;t=0;p=0;running=None;role='';active={}
  while p<len(b):
   dt,p=vlq(b,p);t+=dt;status=b[p]
   if status>=128:p+=1
   else:assert running is not None;status=running
   if status==255:
    typ=b[p];p+=1;n,p=vlq(b,p);payload=b[p:p+n];p+=n
    if typ==3:role=payload.decode('utf-8',errors='replace').split()[0]
    continue
   if status in (240,247):n,p=vlq(b,p);p+=n;continue
   running=status;k=status>>4;ch=(status&15)+1;pitch=b[p];p+=1;v=b[p]if k not in(12,13)else 0
   if k not in(12,13):p+=1
   if k==9 and v:
    assert(ch,pitch)not in active,(filename,'same key overlap',role,t,pitch)
    active[ch,pitch]=(t,v)
   elif k==8 or k==9 and v==0:
    assert(ch,pitch)in active,(filename,'orphan',role,t,pitch)
    at,vel=active.pop((ch,pitch));assert t>at
    actual[Path(filename).name,role,at,t-at,pitch,vel]+=1;ns.append(dict(file=Path(filename).name,role=role,channel=ch,at=at,duration=t-at,pitch=pitch,velocity=vel));channels[role].add(ch)
  assert not active,(filename,'hanging',role);end=max(end,t)
 sid=next(r['id']for r in records.values()if r.get('midi_file')==Path(filename).name);studies[sid]=dict(file=Path(filename).name,end_tick=end,notes=len(ns),roles={})
 for role in sorted({n['role']for n in ns}):
  rn=[n for n in ns if n['role']==role];cur=mx=0
  for t,d in sorted([(n['at'],1)for n in rn]+[(n['at']+n['duration'],-1)for n in rn]):cur+=d;mx=max(mx,cur)
  studies[sid]['roles'][role]=dict(notes=len(rn),polyphony=mx,low=min(n['pitch']for n in rn),high=max(n['pitch']for n in rn),min_duration=min(n['duration']for n in rn),max_duration=max(n['duration']for n in rn))
 midi_notes+=ns
assert actual==expected,('CSV mismatch',len(actual-expected),len(expected-actual))
assert len(studies)==73 and len(rows)==9752
assert all(n['pitch']==36 for n in midi_notes if n['role']=='ST')
# Physical collisions across tracks as well as inside a track.
for sid,st in studies.items():
 seen={}
 for t,off,n in sorted([(n['at'],1,n)for n in midi_notes if n['file']==st['file']]+[(n['at']+n['duration'],0,n)for n in midi_notes if n['file']==st['file']],key=lambda a:(a[0],a[1])):
  key=(n['channel'],n['pitch'])
  if off:assert key not in seen,(sid,'cross-track overlap',key,t);seen[key]=1
  else:assert key in seen;del seen[key]
 assert not seen
stats=dict(base='4c43bd2',definitions=len(records),counts=dict(collections.Counter(r['kind']for r in records.values())),ef_counted_once=True,zip_crc_ok=True,studies=len(studies),csv_notes=len(rows),midi_notes=len(midi_notes),ppq=960,csv_midi_equal=True,physical_note_balance_ok=True,stich_notes=sum(n['role']=='ST'for n in midi_notes),stich_fixed36=True,reference_channels={k:sorted(v)for k,v in channels.items()},prime_mismatches=[r['id']for r in records.values()if r['kind']=='C'and not r['prime_matches']],iv_mismatches=[r['id']for r in records.values()if r['kind']=='C'and not r['iv_matches']],studies_detail=studies)
# Separate what we can independently verify from unprovided renderer semantics.
for r in records.values():
 if r['kind']=='R':
  assert all(l['onsets_match_pattern']is not False for l in r['layers']),r['id']
  assert all(not l['pattern']or len(l['pattern'])*l['unit']==l['period']for l in r['layers']),r['id']
  assert int(re.match(r'\d+',r['fields']['Gesamtzyklus'])[0])==r['joint_bar_ticks'],r['id']
  cycle=r['joint_bar_ticks'];on=sorted({base+t for l in r['layers']for base in range(0,cycle,l['period'])for t in l['onsets']})
  intervals=[b-a for a,b in zip(on,on[1:]+[cycle+on[0]])]
  density=len(on)*r['bar_ticks']/cycle;cv=statistics.pstdev(intervals)/statistics.mean(intervals)
  r['complete_cycle_metrics']=dict(ticks=cycle,onsets=on,unique_onsets=len(on),density=density,cv=cv,declared_density=float(r['fields']['Dichte'].split()[0].replace(',','.')),declared_cv=float(r['fields']['VK'].replace(',','.')))

 if r['kind']=='B'and r.get('cycle_actual'):
  declared=nums(r['fields']['Gesamtzyklus']);r['cycle_comparison']=dict(declared_event_count=declared[0],declared_ticks=declared[1],note_attacks=r['cycle_actual']['attacks'],material_ticks=r['cycle_actual']['period'],host_joint_ticks=r['cycle_actual']['joint_bar'],notes_at_host_joint=r['cycle_actual']['attacks']*(r['cycle_actual']['joint_bar']//r['cycle_actual']['period']),pause_count=len(re.findall(r'Pause',r['fields']['Rhythmus'])))
 if r['kind']=='M':assert r['length_matches']and all(r['declared_cell_fit'].values()),r['id']
 if r['kind']=='U':
  assert len(r['required_held_pitches'])==len(r['states'])-1,r['id']
  for i,required in enumerate(r['required_held_pitches']):assert set(required)<=set(r['literal_common_pitches'][i]),r['id']
for id,st in studies.items():
 f=records[id]['study_fields'];assert int(re.match(r'\d+',f['Ereignisse'])[0])==st['notes'],id
v_checks=[]
for v in [r for r in rows if r['tonfunktion']=='V']:
 end=int(v['tick'])+int(v['dauer_ticks']);relative_target=int(v['absicht'].split('→')[1]);target=int(v['midi'])-int(v['rel'])+relative_target
 matching=[r for r in rows if r['datei']==v['datei']and r['rolle']==v['rolle']and int(r['tick'])==end and int(r['midi'])==target]
 assert matching,(v,'V target missing')
 v_checks.append(dict(study=v['studie'],source=v['vorlage'],at=int(v['tick']),target_at=end,target_midi=target,target_functions=sorted({r['tonfunktion']for r in matching})))
stats['v_target_checks']=v_checks
stats['u_ids_referenced_in_csv']=sorted({id for row in rows for id in re.findall(r'EM-U\d{3}',row['vorlage'])})
stats['rhythm_all_layers_and_joint_cycles_match']=True;stats['motif_lengths_and_declared_cell_subsets_match']=True
stats['long_note_function_strings']=dict(collections.Counter(row['funktionsfolge']for row in rows if row['funktionsfolge']))
stats['full_function_timeline_limit']='CSV function chains have no segment timestamps. Do not count them as an independently reconstructed per-note local/global harmonic timeline. SOURCE_RECORDS has complete H/U states and explicit targets; formal pair checks cover their written spans. The unprovided renderer is not the engine.'
dump('SOURCE_RECORDS.json',list(records.values()))
dump('VALIDATION_RESULTS.json',stats)
print({k:v for k,v in stats.items()if k!='studies_detail'})
