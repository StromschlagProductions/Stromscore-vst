"""P3 actual production A/B and source occurrence diagnostics; no injected engine plans."""
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
import subprocess,sys,json,collections,zipfile,struct,hashlib
ROOT=Path(__file__).resolve().parents[1];OUT=Path(sys.argv[1]);OUT.mkdir(parents=True,exist_ok=True)
if '--prepared' not in sys.argv:
 from reference_headers import header_snapshot
 old=OUT/'before-headers';old.mkdir(exist_ok=True)
 for name,data in header_snapshot(ROOT,'a8efd75').items():(old/name).write_bytes(data)
 subprocess.run([sys.executable,str(ROOT/'Tests/ExecutionFixtures.py'),str(OUT/'headers')],check=True)
 for label,headers,flags in [('before',old,[]),('after',ROOT/'Source',[]),('diagnostic',OUT/'headers',['-DWILLIAMS_MOTIF_DIAGNOSTICS'])]:
  subprocess.run(['c++','-O1','-std=c++17',*flags,'-I',str(headers),str(ROOT/'tools/williams_probe.cpp'),'-o',str(OUT/label)],check=True)
def run(label,args):
 r=subprocess.run([str(OUT/label),*map(str,args)],capture_output=True,check=True);return r.stdout,r.stderr
def events(raw):return [tuple(map(int,l.split(b',')))for l in raw.splitlines()]
def ledger(es):
 active={}
 for t,o,ch,n,v,k in es:
  if k:continue
  if v:assert (ch,n)not in active,('overlap',t,o,ch,n);active[ch,n]=t
  else:assert(ch,n)in active and t>active.pop((ch,n)),('release',t,o,ch,n)
 assert not active
pool=json.loads((ROOT/'data/harmony/profiles.json').read_text(encoding="utf-8"))['profiles'][3]['score_pool']
def anchor(identifier,key=2,bars=128,seed=0,voices=3):return [3,100+pool.index(identifier),voices,512,bars,0,3,0,1,0,4,4,0,0,0,key,seed]
def compare(args):
 b,_=run('before',args);a,trace=run('diagnostic',args);p,_=run('after',args);assert a==p,'diagnostics changed output'
 be,ae=events(b),events(a);ledger(ae)
 stable={0,1,2,3,5,6};assert collections.Counter(e for e in be if e[1]in stable)==collections.Counter(e for e in ae if e[1]in stable),('nonmelodic change',args)
 rows=[]
 for line in trace.splitlines():
  if not line.startswith(b'M,'):continue
  t,o,source,identity,complete,count,intro,variation,begin,end,notes,pitch,mask,planned=map(int,line.split(b',')[1:])
  if source>=50000 and planned:
   assert mask&(1<<(pitch%12)),('harmonic violation',args,line)
   rows.append(dict(sample=t,quarter=t/28800,output=o,source=f'JW-M{source-50000:02}',identity=identity,complete=bool(complete),introduction=bool(intro),variation=variation,begin_tick=begin,end_tick=end,pitch=pitch,allowed_mask=mask,material_notes=count,figure_notes=notes))
 result=dict(args=args,sha256=hashlib.sha256(a).hexdigest(),byte_equal=a==b,arp_changed=[e for e in be if e[1]==4]!=[e for e in ae if e[1]==4],authored_notes=rows,
  notes_before=dict(collections.Counter(str(e[1])for e in be if e[4]and not e[5])),notes_after=dict(collections.Counter(str(e[1])for e in ae if e[4]and not e[5])))
 key=hashlib.sha256(json.dumps(args).encode()).hexdigest()[:16];(OUT/(key+'-before.csv')).write_bytes(b);(OUT/(key+'-after.csv')).write_bytes(a);result['render_key']=key
 return result
cases=[]
for path in range(13):cases.append([3,path,3,512,128,0,3])
for identifier in pool:cases.append(anchor(identifier,bars=64))
for identifier in (40002,40003,40012,40014,40050,40059):
 for key in range(12):cases.append(anchor(identifier,key))
for identifier in (40002,40003,40012,40014,40050,40059):
 for seed in (1,7,19):cases.append(anchor(identifier,bars=64,seed=seed))
for identifier in (40010,40059):
 for voices in (2,3):
  args=anchor(identifier,bars=128,voices=voices);args[10:12]=[6,8];cases.append(args)
with ThreadPoolExecutor(max_workers=4)as executor:
 rows=[]
 for i,row in enumerate(executor.map(compare,cases)):
  rows.append(row)
  if i%10==0:print('production',i+1,'/',len(cases),flush=True)
# Actual profile/genre byte regression and muted optional melodic roles.
regressions=[]
for genre in (0,1):
 for profile in (0,1,2,3):
  if genre==0 and profile==3:continue
  for path in (0,3,7,11,12):
   args=[profile,path,3,512,64,genre,3];assert run('before',args)[0]==run('after',args)[0],('profile regression',args);regressions.append(args)
for path in (0,3,7,11,12):
 args=[3,path,0,512,128,0,3];assert run('before',args)[0]==run('after',args)[0];regressions.append(args)
controls=[]
for follow in (0,1):
 for num,den in ((4,4),(3,8),(5,8),(6,8),(7,8)):
  args=anchor(40012,bars=64);args[9:13]=[.3,num,den,1];args[8]=follow
  a=run('after',args)[0];ledger(events(a));assert a==run('after',args)[0];args[3]=127;assert a==run('after',args)[0],('block',args);controls.append(args)
for identifier in (40002,40012,40050,40059):
 args=anchor(identifier,bars=128);a=run('after',args)[0];args[3]=127;assert a==run('after',args)[0];controls.append(args)
# Actual 100 BPM, 960 PPQ hearing files, identical instruments/routing.
def vlq(n):
 b=[n&127];n>>=7
 while n:b.insert(0,(n&127)|128);n>>=7
 return bytes(b)
def smf(raw):
 tracks=[b'\0\xff\x51\x03\x09\x27\xc0\0\xff\x58\x04\x04\x02\x18\x08']
 for output in range(9):
  data=bytearray();previous=0
  for t,o,ch,n,v,k in events(raw):
   if o!=output:continue
   tick=round(t/30);data+=vlq(tick-previous)+bytes([(0xb0 if k else 0x90)+ch-1,n,v]);previous=tick
  tracks.append(bytes(data))
 return b'MThd'+struct.pack('>IHHH',6,1,10,960)+b''.join(b'MTrk'+struct.pack('>I',len(b)+4)+b+b'\0\xff\x2f\0'for b in tracks)
dest=ROOT/'docs/research/john-williams';chosen=[]
# Prefer examples where source material and actual recurrences are both heard.
for row in rows:
 ids={x['source']for x in row['authored_notes']};returns=any(not x['introduction']for x in row['authored_notes'])
 if row['args'][4]==128 and returns and ids and (not chosen or ids-set.union(*(set(x['sources'])for x in chosen))):
  chosen.append(dict(render_key=row['render_key'],args=row['args'],sources=sorted(ids)))
 if len(chosen)==5:break
# Include both slow and fast continuous XYZ drives even if an exact source fails.
for path in (11,12):
 row=rows[path];chosen.append(dict(render_key=row['render_key'],args=row['args'],sources=sorted({x['source']for x in row['authored_notes']})))
for wanted in ('JW-M08','JW-M40'):
 row=next(x for x in rows if x['args'][4]==128 and x['args'][1]not in(11,12)and any(n['source']==wanted for n in x['authored_notes']))
 if not any(x['render_key']==row['render_key']for x in chosen):chosen.append(dict(render_key=row['render_key'],args=row['args'],sources=sorted({x['source']for x in row['authored_notes']})))
with zipfile.ZipFile(dest/'P3_MOTIFS_AB.zip','w',zipfile.ZIP_DEFLATED)as z:
 for i,item in enumerate(chosen):
  for label in ('before','after'):z.writestr(f'{i+1:02}-{label}.mid',smf((OUT/(item['render_key']+'-'+label+'.csv')).read_bytes()))
 z.writestr('README.txt','Actual engine output: before a8efd75 / after Williams P3. 128 bars, 100 BPM, 4/4, 960 PPQ, nine existing MIDI destinations. Same external patches for A/B. Main melody optional; these examples use both roles. Canonical constructed studies; no film-theme transcriptions. Detailed settings and actual source IDs in P3_MOTIFS_RESULTS.json.')
result=dict(reference='a8efd75',variation_codes={0:'original',1:'rhythm',2:'fragment',3:'sequence',4:'augmentation'},source_sha256={p.name:hashlib.sha256(p.read_bytes()).hexdigest()for p in(ROOT/'Source').glob('*.h')},pairs=len(rows),regressions=regressions,transport_block_controls=controls,hearing_examples=chosen,rows=rows)
(dest/'P3_MOTIFS_RESULTS.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
print('pairs',len(rows),'regressions',len(regressions),'source IDs',sorted({x['source']for r in rows for x in r['authored_notes']}),'planned notes',sum(len(r['authored_notes'])for r in rows),flush=True)
