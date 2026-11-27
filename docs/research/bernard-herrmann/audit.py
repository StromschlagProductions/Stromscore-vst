"""Reproduzierbare Forschungsanalyse. Keine Laufzeitdaten, Engine-Imports oder Source-Änderungen.
Klassifikationen sind fachlich redigierte Aussagen in assessment.json, keine Stil-Erkennung.
Aufruf aus beliebigem Verzeichnis: python docs/research/bernard-herrmann/audit.py
"""
from pathlib import Path
import re, json, csv, io, zipfile, struct, collections, hashlib, math
HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[2]
CANON=HERE/'STROMSCORE_Bernard_Herrmann_Vokabular_Kanonisch.md'
text=CANON.read_text()
blocks={m[1]:dict(name=m[2],body=m[3],line=text[:m.start()].count('\n')+1) for m in re.finditer(r'^#{3,4} (HE-[HRBMPST]\d+) · ([^\n]+)\n(.*?)(?=^#{2,4} |\Z)',text,re.M|re.S)}
assert len(blocks)==343
assert collections.Counter(i[3] for i in blocks)==dict(H=101,R=66,B=45,M=57,P=21,S=40,T=13)
def write(name,obj): (HERE/name).write_text(json.dumps(obj,ensure_ascii=False,indent=2)+'\n')
def field(b,name):
 m=re.search(r'\*\*'+re.escape(name)+r':\*\* (.*?)(?= · \*\*|\n|$)',b)
 return m[1].strip() if m else None
pc0=dict(C=0,D=2,E=4,F=5,G=7,A=9,B=11)
def pc(s):
 s=s.replace('♭','b').replace('♯','#');return (pc0[s[0]]+s[1:].count('#')-s[1:].count('b'))%12
pitch_re=r'[A-G](?:[b#♭♯])?'
def pcs(s):return [pc(p) for p in re.findall(pitch_re,s)]
ctypes=json.loads((ROOT/'data/harmony/chord_types.json').read_text())['types']
shapes={c['id']:c['intervals'] for c in ctypes}
suffix={'':[0,4,7],'m':[0,3,7],'maj7':[0,4,7,11],'m7':[0,3,7,10],'7':[0,4,7,10],'mM7':[0,3,7,11],'mM9':[0,3,7,11,2],'dim':[0,3,6],'dim7':[0,3,6,9],'dimM7':[0,3,6,11],'m7b5':[0,3,6,10],'sus4':[0,5,7],'sus2':[0,2,7],'add9':[0,4,7,2],'madd9':[0,3,7,2],'maj9':[0,4,7,11,2],'m9':[0,3,7,10,2],'6':[0,4,7,9],'m6':[0,3,7,9],'aug':[0,4,8],'augM7':[0,4,8,11],'maj7#11':[0,4,7,11,6],'7b9':[0,4,7,10,1],'7b5':[0,4,6,10],'it6':[0,4,10],'9#5':[0,4,8,10,2],'mM7b6':[0,3,7,11,8],'add#4':[0,4,6,7],'m(addb9)':[0,3,7,1]}
def symbol(s):
 s=s.replace('\\|','|')
 if '|' in s:
  a,b=map(symbol,s.split('|'));return dict(pcs=sorted(set(a['pcs'])|set(b['pcs'])),root=b['root'],bass=b['bass'],type=None,components=[a,b])
 if s.startswith('{'):
  p=pcs(s);return dict(pcs=sorted(set(p)),root=p[0],bass=p[0],type=None,components=[])
 bass=None
 if re.search(r'/'+pitch_re+'$',s):s,bs=s.rsplit('/',1);bass=pc(bs)
 m=re.fullmatch('('+pitch_re+')(.*)',s);r=pc(m[1]);iv=suffix[m[2]]
 typ=next((c['id'] for c in ctypes if {i%12 for i in c['intervals']}==set(iv)),None)
 return dict(pcs=sorted({(r+i)%12 for i in iv}),root=r,bass=r if bass is None else bass,type=typ,components=[])
def bar_spec(meter):
 n,d=map(int,meter.replace('T','').split('/'))
 return (12,320) if meter=='4/4T' else (n*16//d,240)
errors=[];unparsed=[];inventory=[];pattern_checks=[];short_gate=[]
roles={'LF','KF','LB','KB','AR','TU','ST','GS','HM'}
limits={'KF':720,'KB':960,'AR':7680,'TU':720,'ST':480}
for id,v in blocks.items():
 b=v['body'];xyz=re.search(r'\*\*XYZ(?:-Anker)?:\*\* ([\d,]+) / ([\d,]+) / ([\d,]+)',b)
 r=dict(id=id,name=v['name'],source_line=v['line'],xyz=[float(x.replace(',','.')) for x in xyz.groups()] if xyz else None,refs=sorted(set(re.findall(r'HE-[HRBMPST]\d+',b))),evidence=field(b,'Evidenz'),technical_requirements=field(b,'Technische Anforderungen'))
 r['colour_scope_raw']=field(b,'Färbungsbereich')
 r['mentioned_roles']=sorted(set(re.findall(r'\b(?:LF|KF|LB|KB|AR|TU|ST|GS|HM)\b',b)))
 r['meter']=field(b,'Taktart')
 if r['meter']:r['meter']=re.match(r'[\d/T]+',r['meter'])[0]
 if r['xyz'] is None or not all(0<=n<=1 for n in r['xyz']):errors.append([id,'XYZ'])
 if id[3]=='H':
  rows=[]
  for row in re.findall(r'^\| \d+ \|.*',b,re.M):
   cs=[x.strip() for x in re.split(r'(?<!\\)\|',row)[1:-1]];s=cs[1].strip('`');d=float(cs[2]);declared=sorted(set(pcs(cs[4])));bass=pc(cs[5]);a=None
   try:
    a=symbol(s)
    if sorted(set(a['pcs'])|{a['bass']})!=declared or a['bass']!=bass:errors.append([id,'symbol/table',s,a['pcs'],declared,a['bass'],bass])
   except (KeyError,TypeError,AttributeError) as e:unparsed.append([id,s,str(e)])
   rows.append(dict(symbol=s,bars=d,at=cs[3],pcs=declared,bass=bass,system=cs[6],parsed=a))
  r['chords']=rows;r['harmonic_slots']=len(rows);r['total_bars']=sum(x['bars'] for x in rows)
  r['harmonic_data_fit']=all(c['parsed'] and c['parsed']['type'] for c in rows) and len(rows)<=8 and all(c['bars'].is_integer() for c in rows)
  if r['total_bars']!=8:errors.append([id,'total bars',r['total_bars']])
  r['bass_instruction']=field(b,'Bassführung');r['effect']=field(b,'Wirkung')
 elif id[3] in 'RB':
  grid=re.search(r'```(.*?)```',b,re.S)[1].strip();r['grid']=grid;r['bars']=int(re.match(r'\d+',field(b,'Länge'))[0]);steps,tick=bar_spec(r['meter']);r['source_unit_ticks']=tick
  rr=[]
  for role,pat in re.findall(r'^([A-Z][A-Za-z]*)\s+([Xx.\-|]+)\s*$',grid,re.M):
   if any(len(p)!=steps for p in pat.split('|')) or len(pat.split('|'))!=r['bars']:errors.append([id,'grid length',role])
   s=pat.replace('|','');events=[];held=False
   for j,c in enumerate(s):
    if c=='-' and not held:errors.append([id,'hold after rest',role,j])
    if c in 'Xx':
     held=True;n=1
     while j+n<len(s) and s[j+n]=='-':n+=1
     events.append(dict(at_ticks=j*tick,duration_ticks=n*tick,accent=c=='X'))
    elif c=='.':held=False
   rr.append(dict(role=role,events=events))
   if role in limits and any(e['duration_ticks']>limits[role] for e in events):short_gate.append(dict(id=id,role=role,max_ticks=max(e['duration_ticks'] for e in events),assumed_max=limits[role]))
  r['grid_events']=rr
  r['tones']=re.search(r'^Töne\s+(.*?)\s+\(je Einsatz',grid,re.M)[1] if id[3]=='B' else None
  r['harmonic_relationship']=field(b,'Beziehung zur Harmonie');r['functions_raw']=field(b,'Tonfunktionen')
 elif id[3] in 'MP':
  seq=re.search(r'\*\*Töne/Dauern:\*\* `([^`]+)`',b)[1];r['sequence']=seq;meter=re.search(r'\(Taktart ([\d/T]+)\)',b);r['meter']=meter[1] if meter else r['meter'] or '4/4';steps,tick=bar_spec(r['meter']);r['source_unit_ticks']=tick
  ns=[];at=0
  for j,bar in enumerate(seq.split('|')):
   tokens=re.findall(r'('+pitch_re+r'\d|r)/(\d+)',bar)
   if sum(int(n) for p,n in tokens)!=steps:errors.append([id,'melodic bar length',j+1,tokens])
   for p,n in tokens:
    n=int(n)
    if p!='r':ns.append(dict(pitch=p,at_ticks=at,duration_ticks=n*tick))
    at+=n*tick
  r.update(notes=ns,note_count=len(ns),duration_ticks=at,bars=len(seq.split('|')),functions_raw=field(b,'Tonfunktionen'),must_preserve=field(b,'Muss erhalten bleiben'),return_rule=field(b,'Wiederkehr'),context=field(b,'Kontext') or field(b,'Harmonik') or field(b,'Akkorde je Takt'))
 else:
  r['generator_rule']=field(b,'Generatorregel');r['musical_relationship']=field(b,'Zusammenhang der Rollen');r['bars']=int(re.match(r'\d+',field(b,'Länge'))[0])
 inventory.append(r)
assert not unparsed,unparsed
assert not errors,errors
# Compare harmonic material only: do not confuse a matching chord list with matching orchestration.
cat=json.loads((ROOT/'data/harmony/catalog.json').read_text())['templates']
def signature(cs,shift=0):
 out=[]
 for c in cs:
  key=(tuple(sorted((n+shift)%12 for n in (c['parsed']['pcs'] if c.get('parsed') else c['pcs']))),(c['bass']+shift)%12)
  if out and out[-1][:2]==key:out[-1]=(*key,out[-1][2]+c['bars'])
  else:out.append((*key,c['bars']))
 return out
for h in (r for r in inventory if r['id'][3]=='H'):
 h['existing_harmonic_equivalents']=[]
 for t in cat:
  cs=[dict(pcs=list({(c['root']+n)%12 for n in shapes[c['type']]}),bass=c['root'] if c['bass'] is None else c['bass'],bars=c['bars']) for c in t['chords']]
  for tr in range(12):
   if signature(h['chords'])==signature(cs,tr):h['existing_harmonic_equivalents'].append(dict(catalog_id=t['id'],transpose=tr));break
# Independent SMF parser: compare every matched note, not just counts.
def vlq(b,p):
 n=0
 while True:
  x=b[p];p+=1;n=(n<<7)+(x&127)
  if x<128:return n,p
z=zipfile.ZipFile(HERE/'HE_Studien_MIDI.zip');assert z.testzip() is None
csvrows=list(csv.DictReader(io.StringIO((HERE/'HE_Studien_Ereignisse.csv').read_text()),delimiter=';'))
expected=collections.Counter((r['studie'],r['rolle'],*[int(r[k]) for k in ('start_ticks_960ppq','dauer_ticks','midi_ton','velocity')]) for r in csvrows)
actual=collections.Counter();midi_errors=[];study_stats={};allnotes=[]
for name in z.namelist():
 if not name.lower().endswith('.mid'):continue
 data=z.read(name);assert data[:4]==b'MThd';fmt,tracks,ppq=struct.unpack('>HHH',data[8:14]);assert ppq==960
 pos=8+int.from_bytes(data[4:8],'big');study=Path(name).stem;notes=[];end=0
 for tr in range(tracks):
  assert data[pos:pos+4]==b'MTrk';length=int.from_bytes(data[pos+4:pos+8],'big');b=data[pos+8:pos+8+length];pos+=8+length;p=0;tick=0;running=None;role='';active={}
  while p<len(b):
   dt,p=vlq(b,p);tick+=dt;status=b[p]
   if status>=128:p+=1
   else:assert running is not None;status=running
   if status==255:
    typ=b[p];p+=1;n,p=vlq(b,p);payload=b[p:p+n];p+=n
    if typ==3:role=payload.decode('latin1').split()[0]
    continue
   if status in (240,247):n,p=vlq(b,p);p+=n;continue
   running=status;kind=status>>4;channel=status&15;pitch=b[p];p+=1;vel=b[p] if kind not in (12,13) else 0
   if kind not in (12,13):p+=1
   if kind==9 and vel:
    if (channel,pitch) in active:midi_errors.append([study,'double on',role,tick,pitch])
    active[channel,pitch]=(tick,vel)
   elif kind==8 or kind==9 and vel==0:
    if (channel,pitch) not in active:midi_errors.append([study,'orphan',role,tick,pitch]);continue
    at,v=active.pop((channel,pitch));n=dict(study=study,role=role,at=at,duration=tick-at,pitch=pitch,velocity=v,channel=channel+1);notes.append(n);actual[study,role,at,tick-at,pitch,v]+=1
    if tick<=at or not 21<=pitch<=108:midi_errors.append([study,'pitch/duration',n])
  if active:midi_errors.append([study,'hanging',role])
  end=max(end,tick)
 allnotes+=notes;rc={}
 for role in sorted({n['role'] for n in notes}):
  ns=[n for n in notes if n['role']==role];ev=sorted([(n['at'],1) for n in ns]+[(n['at']+n['duration'],-1) for n in ns]);poly=cur=0
  for t,d in ev:cur+=d;poly=max(poly,cur)
  rc[role]=dict(notes=len(ns),polyphony=poly,max_duration_ticks=max(n['duration'] for n in ns),pitch_min=min(n['pitch'] for n in ns),pitch_max=max(n['pitch'] for n in ns),channels=sorted({n['channel'] for n in ns}))
 study_stats[study]=dict(notes=len(notes),end_tick=end,roles=rc)
assert actual==expected,('CSV/MIDI mismatch',list((actual-expected).items())[:2],list((expected-actual).items())[:2])
assert not midi_errors,midi_errors
assert len(study_stats)==53 and len(allnotes)==5328
assert set(study_stats)=={i for i in blocks if i[3] in 'ST'}
assert all(n['pitch']==36 for n in allnotes if n['role']=='ST')
assert all(n['role'] in roles for n in allnotes)
refs_missing=sorted({i for r in inventory for i in r['refs'] if i not in blocks});assert not refs_missing
assessment=json.loads((HERE/'assessment.json').read_text());assert set(assessment['entries'])==set(blocks)
for r in inventory:
 r.update(assessment['entries'][r['id']]);assert r['classification'] in assessment['classes'];assert r['reason'] and isinstance(r['required_capabilities'],list)
 if r['id'][3]=='H':r['reason']='Grundform: '+', '.join(c['symbol']+'×'+str(int(c['bars']))+'T' for c in r['chords'])+'. '+r['reason']
 elif r['id'][3]=='M' and r['sequence'] not in r['reason']:r['reason']='Zelle '+r['sequence']+'; Kontext '+str(r['context'])+'. '+r['reason']
 elif r['id'][3]=='R' and r['classification']=='A':r['reason']=r['meter']+', '+str(r['bars'])+' Takte: '+', '.join(c['role']+' '+str(len(c['events']))+' Einsätze, max '+str(max((e['duration_ticks'] for e in c['events']),default=0))+' Ticks' for c in r['grid_events'])+'. '+r['reason']
 r['production_active']=False
 if r['id'] in study_stats:r['reference_midi']=study_stats[r['id']]
 r['functions_raw']=next((line.strip('- ') for line in blocks[r['id']]['body'].splitlines() if '**Tonfunktionen**' in line),r.get('functions_raw'))
# MIDI vs current default assumptions is deliberately a separate test from SMF validity.
violations=[];poly_limits=dict(LF=6,KF=9,LB=1,KB=1,AR=1,TU=4,ST=1,GS=2,HM=1)
for s,v in study_stats.items():
 for role,st in v['roles'].items():
  if st['polyphony']>poly_limits[role]:violations.append(dict(id=s,role=role,kind='polyphony',actual=st['polyphony'],assumed=poly_limits[role]))
  if role in limits and st['max_duration_ticks']>limits[role]:violations.append(dict(id=s,role=role,kind='duration',actual=st['max_duration_ticks'],assumed=limits[role]))
missing_types=collections.defaultdict(set)
for r in inventory:
 for c in r.get('chords',[]):
  if not c['parsed']['type']:missing_types[c['symbol']].add(r['id'])
files=['STROMSCORE_Bernard_Herrmann_Vokabular_Kanonisch.md','HE_Studien_Ereignisse.csv','HE_Studien_MIDI.zip','HE_Qualitaetspruefung.md']
manifest={n:dict(bytes=(HERE/n).stat().st_size,sha256=hashlib.sha256((HERE/n).read_bytes()).hexdigest()) for n in files}
validation=dict(engine_commit='023b0a61c08797d72a746a44f9bffaa58e31b048',archived_files=manifest,counts=dict(collections.Counter(i[3] for i in blocks)),classification_counts=dict(collections.Counter(r['classification'] for r in inventory)),catalog_templates=len(cat),chord_types=len(ctypes),missing_symbols={s:sorted(ids) for s,ids in sorted(missing_types.items())},source_structure_findings=errors,missing_references=refs_missing,midi=dict(files=len(study_stats),notes=len(allnotes),ppq=960,csv_equal=True,note_errors=midi_errors,fixed_stich_36=True,studies=study_stats),default_output_incompatibilities=violations,rhythm_duration_incompatibilities=short_gate,scope='Offline-Dokumentanalyse; kein Engine-Rendering, keine externen Patchfähigkeiten verifiziert.')
write('TECHNICAL_INVENTORY.json',dict(schema_version=1,engine_commit=validation['engine_commit'],classes=assessment['classes'],capabilities=assessment['capabilities'],scope=assessment['scope'],templates=inventory))
write('VALIDATION_RESULTS.json',validation)
# Human-readable per-ID companion, generated only from curated decisions and parsed facts.
lines=['# HE-Einzelinventar – 343 Vorlagen','', 'Stand: Engine `023b0a6`. Kategorien beziehen sich auf die musikalische Grundform einschließlich zwingender Eigenschaften; optionale Varianten werden gesondert genannt. Keine Vorlage ist aktiviert. D = direkt, A = begrenzte Anbindung, E = gemeinsame Fähigkeit fehlt, K = Klärung. Vollständige Quelldaten, Register-/Funktionsangaben und Referenzen: `TECHNICAL_INVENTORY.json`.','']
for kind in 'HRBMPST':
 lines+=['## '+kind,'','| ID / Name | Status | Begründung / fehlende Fähigkeit |','|---|---|---|']
 for r in inventory:
  if r['id'][3]!=kind:continue
  reason=r['reason']+' '+('Benötigt: '+', '.join(r['required_capabilities'])+'.' if r['required_capabilities'] else '')
  lines.append('| [%s](STROMSCORE_Bernard_Herrmann_Vokabular_Kanonisch.md) (Z.%s) · %s | %s | %s |'%(r['id'],r['source_line'],r['name'],r['classification'],reason.replace('|','/')))
(HERE/'TECHNICAL_INVENTORY.md').write_text('\n'.join(lines)+'\n')
print(json.dumps({k:validation[k] for k in ['counts','classification_counts','catalog_templates','chord_types','source_structure_findings']},ensure_ascii=False))
print('CSV/MIDI',len(study_stats),len(allnotes),'default output violations',len(violations),'rhythm gate mismatches',len(short_gate))
