"""Offline research audit only. No engine imports, generated runtime data or source edits."""
from pathlib import Path
import re,json,csv,io,zipfile,struct,collections,hashlib,subprocess,tempfile
here=Path(__file__).resolve().parent;root=here.parents[2];text=(here/'STROMSCORE_John_Williams_Profil_Kanonisch.md').read_text()
blocks={m[1]:(m[2],m[3]) for m in re.finditer(r'^#{3,4} (JW-[HRBM PST]\d\d) · ([^\n]+)\n(.*?)(?=^#{2,4} |\Z)',text,re.M|re.S)}
counts={k:sum(i[3]==k for i in blocks) for k in 'HRBM PST' if k!=' '};assert counts==dict(H=76,R=48,B=40,M=48,P=24,S=30,T=10),counts
pc0=dict(C=0,D=2,E=4,F=5,G=7,A=9,B=11)
def pc(s):
 s=s.replace('♭','b').replace('♯','#');return (pc0[s[0]]+s[1:].count('#')-s[1:].count('b'))%12
def pitches(s):return [pc(x) for x in s.split()]
chtypes=json.loads((root/'data/harmony/chord_types.json').read_text())['types'];shapes={c['id']:c['intervals'] for c in chtypes}
suffix={'':[0,4,7],'m':[0,3,7],'q':[0,5,10],'5':[0,7],'maj7':[0,4,7,11],'m7':[0,3,7,10],'7':[0,4,7,10],'mM7':[0,3,7,11],'dim7':[0,3,6,9],'dim':[0,3,6],'m7b5':[0,3,6,10],'sus4':[0,5,7],'sus2':[0,2,7],'7sus4':[0,5,7,10],'add9':[0,4,7,2],'maj9':[0,4,7,11,2],'m9':[0,3,7,10,2],'6':[0,4,7,9],'m6':[0,3,7,9],'6/9':[0,4,7,9,2],'aug':[0,4,8],'augM7':[0,4,8,11],'augM7#9':[0,4,8,11,3],'maj7#11':[0,4,7,11,6],'7#5':[0,4,8,10],'m(add#4)':[0,3,6,7],'(addb3)':[0,3,4,7],'m(b6)':[0,3,7,8],'mM7b6':[0,3,7,11,8],'m(addb9)':[0,3,7,1]}
def chord(s):
 s=s.replace('\\|','|')
 if '|' in s:
  a,b=map(chord,s.split('|'));return a[0]|b[0],b[1],b[2],None
 if s.startswith('{'):
  ps=pitches(s[1:-1]);return set(ps),ps[0],ps[0],None
 bass=None
 if re.search(r'/[A-G][b#]?$',s):s,b=s.rsplit('/',1);bass=pc(b)
 m=re.fullmatch(r'([A-G][b#]?)(.*)',s);r=pc(m[1]);iv=suffix[m[2]]
 typ=next((c['id'] for c in chtypes if {n%12 for n in c['intervals']}==set(iv)),None)
 return {(r+n)%12 for n in iv}|({bass} if bass is not None else set()),r,r if bass is None else bass,typ
inventory=[];errors=[];harm=[];unknown=[]
for id,(name,b) in blocks.items():
 xyz=re.search(r'\*\*XYZ(?:-Anker)?:\*\* ([\d,]+) / ([\d,]+) / ([\d,]+)',b)
 xyz=[float(x.replace(',','.')) for x in xyz.groups()] if xyz else None
 record=dict(id=id,name=name,xyz=xyz,line=text[:text.index(id+' ·')].count('\n')+1,refs=sorted(set(re.findall(r'JW-[HRBMPST]\d\d',b))))
 if xyz and not all(0<=x<=1 for x in xyz):errors.append((id,'XYZ'))
 if id[3]=='H':
  rows=[]
  for row in re.findall(r'^\| \d+ \|.*',b,re.M):
   cells=[c.strip() for c in re.split(r'(?<!\\)\|',row)[1:-1]];symbol=cells[1].strip('`');dur=float(cells[2].replace('½','.5'));declared=set(pitches(cells[4]));bass=pc(cells[5]);typ=None
   try:
    actual,r,ba,typ=chord(symbol)
    if actual!=declared or ba!=bass:errors.append((id,'symbol/table mismatch',symbol,sorted(actual),sorted(declared),ba,bass))
   except (KeyError,TypeError,AttributeError) as e:unknown.append((id,symbol));r=pc(re.match(r'[A-G][b#]?',symbol)[0]) if not symbol.startswith('{') else bass
   rows.append(dict(symbol=symbol,bars=dur,root=r,bass=bass,pcs=sorted(declared),type=typ,system=cells[6]))
  record['chords']=rows;record['system']=re.search(r'\*\*Tonvorrat:\*\* (.*?) ·',b)[1]
  gaps=[]
  if any(c['type'] is None for c in rows):gaps.append('fehlende exakte Akkorddefinition/Polychord- oder Mengenbedeutung')
  if len(rows)>8 or any(c['bars']%1 for c in rows):gaps.append('Harmoniedauer/Slot-Modell erweitern')
  record['harmonic_data_fit']=not gaps
  if sum(c['bars'] for c in rows)!=8:errors.append((id,'duration'))
  record['classification']='Kleine Erweiterung erforderlich' if gaps else 'Direkt umsetzbar';record['reason']='; '.join(gaps) or 'geschützter Datenimport mit bestehenden Typen, explizitem Bass, ganzen Takten und höchstens acht Slots'
  if 'Planing' in name:record['reason']+='; exakte parallele Lagenführung zusätzlich planen (nicht durch Standard-Voice-Leading garantiert)';record['classification']='Kleine Erweiterung erforderlich'
  harm.append(record)
 elif id[3] in 'RB':
  grid=re.search(r'```(.*?)```',b,re.S)[1];record['grid']=grid.strip();record['meter']=re.search(r'\*\*Taktart:\*\* ([\d/T]+)',b)[1]
  record['classification']='Kleine Erweiterung erforderlich';record['reason']='vorhandene Tick-Ereignisse nutzbar; Vorlagenwahl und rollenbezogene Rasteranbindung fehlen'
  if id[3]=='B':
   tone=re.search(r'^Töne\s+(.*?)\s+\(je Einsatz',grid,re.M);record['tones']=tone[1] if tone else None
   if any(x in (record['tones'] or '') for x in ['P(', '+1',' n',' d']):record['reason']='explizite Bass-Tonfolge/relative Tonregel und harmonische Freigabe fehlen; Rhythmus ist nicht die Tonplanung'
  if record['meter']=='4/4T':record['reason']+='; Triolenzeit ist 320 Ticks, Einsatzproduktion noch Sechzehntel'
  if len(re.findall(r'^(?:KF|KB|LB|LF|AR|GS|HM|ST|TU)\s',grid,re.M))>1:record['reason']+='; gemeinsames Mehrrollen-Akzentgerüst erforderlich'
 elif id[3] in 'MP':
  seq=re.search(r'\*\*Töne/Dauern:\*\* `([^`]+)`',b)[1];record['sequence']=seq
  notes=re.findall(r'([A-G][b#]?\d|r)/(\d+)',seq);n=sum(p!='r' for p,d in notes);record['note_count']=n
  record['classification']='Größere Erweiterung erforderlich' if id[3]=='P' else 'Kleine Erweiterung erforderlich'
  record['reason']=('zusammenhängende 4–8/6-Takt-Ziel- und Spannungsplanung fehlt; kein Abschneiden auf acht Noten' if id[3]=='P' else 'Quelltonhöhen statt Akkordtonleiter erfassen; erlaubte Nicht-Akkordtöne mit Funktion erhalten')
  if n>8:record['reason']+='; überschreitet Acht-Noten-Materialgrenze'
  if id=='JW-M36':record['reason']+='; G–D über C ist nicht vollständig akkordtongebunden'
 else:
  record['meter']=re.search(r'\*\*Taktart:\*\* ([\d/T]+)',b)[1]
  record['classification']='Größere Erweiterung erforderlich';record['reason']='koordinierter mehrrolliger Verlauf einschließlich Eintritt/Pause/Dynamik; keine generische Studienwiedergabe vorhanden'
  if id[3]=='T':record['reason']='expliziter System-/Rollenübergang nicht durch vorhandene Übergangsstimmführung allein garantiert'
 inventory.append(record)
for r in inventory:
 if r['id'] in ('JW-B01','JW-B03','JW-B04'):
  r['classification']='Mit vorhandenen Fähigkeiten musikalisch gleichwertig umsetzbar';r['reason']='vorhandener Pedal-/Oktav-/Alternating-Bass unter passender Harmonie; exakte Vorlagenrhythmik und XYZ-Zuordnung bleiben Importarbeit'
# Independent MIDI parsing including track names, running status and held notes.
z=zipfile.ZipFile(here/'JW_Studien_MIDI_Kanonisch.zip');assert z.testzip() is None
csvrows=list(csv.DictReader(io.StringIO((here/'JW_Studien_Ereignisse_Kanonisch.csv').read_text()),delimiter=';'))
expected=collections.Counter((r['studie'],r['rolle'],*[int(r[k]) for k in ('start_ticks_960ppq','dauer_ticks','midi_ton','velocity')]) for r in csvrows)
actual=collections.Counter();studies={};miderrors=[]
def vlq(b,p):
 n=0
 while True:
  c=b[p];p+=1;n=n*128+(c&127)
  if c<128:return n,p
for entry in z.namelist():
 if not entry.endswith('.mid'):continue
 data=z.read(entry);fmt,tracks,ppq=struct.unpack('>HHH',data[8:14]);assert ppq==960
 pos=14;stats=collections.Counter();end=0;roles={}
 for tr in range(tracks):
  length=int.from_bytes(data[pos+4:pos+8],'big');b=data[pos+8:pos+8+length];pos+=8+length;p=0;tick=0;running=None;name='';active={}
  while p<len(b):
   dt,p=vlq(b,p);tick+=dt;status=b[p]
   if status>=128:p+=1
   else:status=running
   if status==255:
    typ=b[p];p+=1;n,p=vlq(b,p);payload=b[p:p+n];p+=n
    if typ==3:name=payload.decode('latin1').split()[0]
    continue
   if status in (240,247):n,p=vlq(b,p);p+=n;continue
   running=status;kind=status>>4;ch=status&15;n=b[p];p+=1;v=b[p] if kind not in (12,13) else 0
   if kind not in (12,13):p+=1
   if kind==9 and v:
    if (ch,n) in active:miderrors.append((entry,'double',name,tick,n))
    active[ch,n]=(tick,v)
   elif kind==8 or kind==9 and not v:
    if (ch,n) not in active:miderrors.append((entry,'orphan',tick,n));continue
    at,vel=active.pop((ch,n));actual[Path(entry).stem,name,at,tick-at,n,vel]+=1;stats[name]+=1
    if not 21<=n<=108 or tick<=at:miderrors.append((entry,'pitch/duration',n,at,tick))
  if active:miderrors.append((entry,'hanging',name))
  end=max(end,tick)
 studies[Path(entry).stem]=dict(end_tick=end,roles=dict(stats),notes=sum(stats.values()))
assert actual==expected,(list((actual-expected).items())[:2],list((expected-actual).items())[:2])
refs=sorted({x for r in inventory for x in r['refs'] if x not in blocks})
# Strict sequence comparisons against existing catalog, merging adjacent identical harmony.
cat=json.loads((root/'data/harmony/catalog.json').read_text())['templates']
def signature(chords,shift=0):
 out=[]
 for c in chords:
  key=(tuple(sorted((n-shift)%12 for n in c['pcs'])),(c['bass']-shift)%12)
  if out and out[-1][:2]==key:out[-1]=(key[0],key[1],out[-1][2]+c['bars'])
  else:out.append((*key,c['bars']))
 return out
for h in harm:
 h['existing_equivalents']=[]
 for t in cat:
  cs=[dict(pcs=list({(c['root']+n)%12 for n in shapes[c['type']]}|({c['bass']} if c['bass'] is not None else set())),bass=c['root'] if c['bass'] is None else c['bass'],bars=c['bars']) for c in t['chords']]
  for shift in range(12):
   if signature(h['chords'])==signature(cs,shift):h['existing_equivalents'].append(dict(id=t['id'],transpose=-shift));break
# Pattern legality checks and melody bar sums.
pattern_errors=[]
for id,(name,b) in blocks.items():
 if id[3] in 'RB':
  meter=re.search(r'\*\*Taktart:\*\* ([\d/T]+)',b)[1];num,den=map(int,meter.replace('T','').split('/'));steps=12 if 'T' in meter else num*16//den
  grid=re.search(r'```(.*?)```',b,re.S)[1]
  for role,pat in re.findall(r'^([A-Z][A-Za-z]*)\s+([Xx.\-|]+)\s*$',grid,re.M):
   if any(len(bar)!=steps for bar in pat.split('|')):pattern_errors.append((id,role,'bar length'))
   held=False
   for c in pat.replace('|',''):
    if c=='-' and not held:pattern_errors.append((id,role,'hold after rest'))
    if c in 'Xx':held=True
    elif c=='.':held=False
 if id[3] in 'MP':
  seq=next(r['sequence'] for r in inventory if r['id']==id);meter=re.search(r'(?:Taktart:?\*?\*?\s*|Taktart )([\d/T]+)',b)
  meter=meter[1] if meter else '4/4';num,den=map(int,meter.replace('T','').split('/'));steps=12 if 'T' in meter else num*16//den
  for j,bar in enumerate(seq.split('|')):
   if sum(int(d) for d in re.findall(r'/(\d+)',bar))!=steps:pattern_errors.append((id,'melody bar',j+1,meter))
# Cross-file semantic observations, without treating deliberate dissonance as an error.
systems={'Dur':{0,2,4,5,7,9,11},'Lydisch':{0,2,4,6,7,9,11},'Mixolydisch':{0,2,4,5,7,9,10},'Dorisch':{0,2,3,5,7,9,10},'Phrygisch':{0,1,3,5,7,8,10},'Äolisch':{0,2,3,5,7,8,10},'Moll harm.':{0,2,3,5,7,8,11},'Moll gesamt':{0,2,3,5,7,8,9,10,11},'Okt-A':{0,1,3,4,6,7,9,10},'Okt-B':{1,2,4,5,7,8,10,11},'Okt-C':{0,2,3,5,6,8,9,11},'Hex-C':{0,3,4,7,8,11},'Ganzton-0':{0,2,4,6,8,10},'Ungarisch-Moll':{0,2,3,6,7,8,11}}
system_errors=[]
for h in harm:
 for c in h['chords']:
  if c['system'] in systems and set(c['pcs'])-systems[c['system']]:system_errors.append((h['id'],c['symbol'],c['system']))
 if h['id'] in ('JW-H20','JW-H21','JW-H60'):
  h['classification']='Kleine Erweiterung erforderlich';h['reason']+='; expliziter Systemwechsel bzw. Parallelführung nicht durch Akkordliste garantiert'
role_observations={}
for study in studies:
 rs=[k for k in actual for _ in range(actual[k]) if k[0]==study];st=[k for k in rs if k[1]=='ST']
 events=[]
 for _,role,at,dur,n,v in st:events.extend([(at,1),(at+dur,-1)])
 active=0;maximum=0
 for at,d in sorted(events):active+=d;maximum=max(maximum,active)
 role_observations[study]=dict(stich_pitches=sorted({k[4] for k in st}),stich_max_polyphony=maximum,
  short_pad_over_720=sum(k[1]=='KF' and k[3]>720 for k in rs),short_bass_over_960=sum(k[1]=='KB' and k[3]>960 for k in rs),
  accompaniment_without_melody=sum(k[1] not in ('HM','GS') for k in rs),model_notes=len(rs))
interval_errors=[];jw_duplicates=[]
for r in inventory:
 if r['id'][3]=='M':
  b=blocks[r['id']][1];seq=r['sequence'];ns=re.findall(r'([A-G][b#]?)([0-9])/\d+',seq);midi=[12*(int(o)+1)+pc(n) for n,o in ns];actual_iv=[b-a for a,b in zip(midi,midi[1:])]
  line=re.search(r'\*\*Intervalle \(Halbtöne\):\*\* (.*?) ·',b)
  declared=[int(n) for n in re.findall(r'[+-]?\d+',line[1])] if line else []
  if declared!=actual_iv:interval_errors.append((r['id'],declared,actual_iv))
for i,h in enumerate(harm):
 for other in harm[:i]:
  for shift in range(12):
   if signature(h['chords'])==signature(other['chords'],shift):jw_duplicates.append((h['id'],other['id'],shift));break
results=dict(engine='8d4086c',counts=counts,interval_errors=interval_errors,jw_duplicates=jw_duplicates,system_errors=system_errors,role_observations=role_observations,harmonic_chords=sum(len(h['chords']) for h in harm),errors=errors,unparsed_symbols=unknown,pattern_errors=pattern_errors,missing_references=refs,midi_files=len(studies),csv_notes=sum(expected.values()),midi_notes=sum(actual.values()),midi_errors=miderrors,csv_midi_equal=actual==expected,studies=studies,inventory=inventory)
(here/'TECHNICAL_INVENTORY.json').write_text(json.dumps(results,ensure_ascii=False,indent=2)+'\n')
print(json.dumps({k:v for k,v in results.items() if k not in ('inventory','studies')},ensure_ascii=False,indent=2))
