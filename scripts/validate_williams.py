"""Actual production MIDI, original-profile byte regression and P1 listening examples."""
from pathlib import Path
import sys,json,subprocess,collections,hashlib,struct,zipfile,io,csv
from reference_headers import header_snapshot
root=Path(__file__).resolve().parents[1];out=Path(sys.argv[1]).resolve();out.mkdir(parents=True,exist_ok=True)
old=out/'reference';old.mkdir(exist_ok=True)
for n,b in header_snapshot(root,'8d4086c').items():(old/n).write_bytes(b)
subprocess.run(['c++','-std=c++17','-O1','-I',str(old),str(root/'tools/williams_probe.cpp'),'-o',str(out/'before')],check=True)
# Compile directly against production headers as well as read-only friend diagnostics.
subprocess.run(['c++','-std=c++17','-O1','-I',str(root/'Source'),str(root/'tools/williams_probe.cpp'),'-o',str(out/'production')],check=True)
subprocess.run([sys.executable,str(root/'Tests/ExecutionFixtures.py'),str(out/'headers')],check=True)
subprocess.run(['c++','-std=c++17','-O1','-DWILLIAMS_DIAGNOSTICS','-I',str(out/'headers'),str(root/'tools/williams_probe.cpp'),'-o',str(out/'current')],check=True)
def run(exe,args):
 r=subprocess.run([str(out/exe),*map(str,args)],capture_output=True,check=True);return r.stdout,r.stderr
fingerprint={p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in (root/'Source').glob('*.h')}
rows=[];regressions=0
for genre in (0,1):
 for profile in (0,1,2):
  for path in (0,3,7,11,12):
   args=[profile,path,3,512,128,genre,3];b,_=run('before',args);a,_=run('production',args);assert a==b,('old profile changed',args);regressions+=1
for path in (0,3,7,11,12):
 a,_=run('production',[3,path,3,512,128,1,3]);b,_=run('production',[0,path,3,512,128,1,3]);assert a==b,('Williams affected Pop/Rock',path)
for path in range(13):
 for mode in (0,1,2,3):
  args=[3,path,mode,512,128,0,3];raw,trace=run('current',args);production,_=run('production',args);assert raw==production,('diagnostic altered output',args)
  es=[tuple(map(int,l.split(b','))) for l in raw.splitlines()];notes=[];active={};peak=collections.Counter();vactive=collections.Counter();overlap=0;last=0
  for at,o,ch,n,v,kind in es:
   if vactive[7] and vactive[8]:overlap+=at-last
   last=at
   if kind:continue
   key=ch,n
   if v:assert key not in active,('double',args,at,key);active[key]=(at,o,v);vactive[o]+=1
   else:
    assert key in active,('orphan',args,at,key);start,owner,vel=active.pop(key);assert at>start;notes.append((start,at,owner,n,vel));vactive[owner]-=1
  assert not active and overlap==0,('ledger/foreground overlap',args,overlap)
  assert all(n==36 for at,o,ch,n,v,kind in es if o==6 and not kind and v),'fixed trigger changed'
  counts=collections.Counter(o for at,o,ch,n,v,kind in es if not kind and v);events=[l.decode().split(',') for l in trace.splitlines()];harm=sorted({int(e[2]) for e in events if e[0]=='A' and int(e[2])>=0});rhythms=collections.Counter(int(e[2]) for e in events if e[0]=='R');bass=collections.Counter(int(e[3]) for e in events if e[0]=='R')
  gates={str(o):round(sum(end-at for at,end,owner,n,v in notes if owner==o)/(128*4*28800)*100,3) for o in (7,8)}
  row=dict(path=path,mode=mode,note_ons=dict(counts),gate_percent=gates,harmonies=harm,rhythm_events=dict(rhythms),bass_events=dict(bass),sha256=hashlib.sha256(raw).hexdigest());rows.append(row)
  (out/f'williams-p{path}-m{mode}.csv').write_bytes(raw)
  if mode in (0,3) and path in (0,3,7,11,12):
   for block in (127,8192):
    other,_=run('production',[3,path,mode,block,128,0,3]);assert other==raw,('block drift',args,block)
# Both Follow states and manual patterns; meter mismatch falls back to the existing generator.
for follow in (0,1):
 for manual in (0,1):
  for num,den in ((4,4),(3,8),(5,8),(7,8)):
   args=[3,12,3,512,32,0,3,manual,follow,.3,num,den];a,_=run('production',args);b,_=run('production',[*args[:3],127,*args[4:]]);assert a==b,('control block drift',args)
# Explicit stop/restart, warm backward loop and non-boundary forward seek.
for mode in range(4):
 args=[3,3,mode,512,32,0,3,0,1,.3,4,4,1]
 raw,_=run('production',args);other,_=run('production',[*args[:3],127,*args[4:]]);assert raw==other,('transport block drift',mode)
 active={}
 for line in raw.splitlines():
  at,o,ch,n,v,kind=map(int,line.split(b','))
  if kind:continue
  key=ch,n
  if v:assert key not in active,('transport double',mode,at,key);active[key]=at
  else:assert key in active,('transport orphan',mode,at,key);active.pop(key)
 assert not active,('transport hanging',mode)
# Seven unvisited harmonies in the broad matrix: real eight-bar anchor renders,
# never an injected template index or custom-chord substitute.
pool=json.loads((root/'data/harmony/profiles.json').read_text(encoding='utf-8'))['profiles'][3]['score_pool'];visited={i for r in rows for i in r['harmonies']};catalog_smoke=[]
for index,identifier in enumerate(pool):
 if identifier in visited:continue
 args=[3,100+index,0,512,8,0,3];raw,trace=run('production',args);repeat,_=run('production',[*args[:3],127,*args[4:]]);assert raw==repeat,('catalog block drift',identifier)
 first=next(int(l.split(b',')[2]) for l in trace.splitlines() if l.startswith(b'H,'));assert first==identifier
 ons=[l for l in raw.splitlines() if int(l.split(b',')[4])>0 and int(l.split(b',')[5])==0];assert ons
 catalog_smoke.append(dict(id=identifier,note_ons=len(ons),sha256=hashlib.sha256(raw).hexdigest()))
# Store real-engine SMF excerpts, no constructed substitute notes.
def vlq(n):
 b=[n&127];n>>=7
 while n:b.insert(0,(n&127)|128);n>>=7
 return bytes(b)
def smf(raw):
 tracks=[b'\0\xff\x51\x03\x09\x27\xc0\0\xff\x58\x04\x04\x02\x18\x08'];es=[tuple(map(int,l.split(b','))) for l in raw.splitlines()]
 for output in range(9):
  body=bytearray();prev=0
  for at,o,ch,n,v,kind in es:
   if o!=output:continue
   tick=round(at/30);body+=vlq(tick-prev)+bytes([(0xb0 if kind else 0x90)+ch-1,n,v]);prev=tick
  tracks.append(bytes(body))
 return b'MThd'+struct.pack('>IHHH',6,1,len(tracks),960)+b''.join(b'MTrk'+struct.pack('>I',len(t)+4)+t+b'\0\xff\x2f\0' for t in tracks)
dest=root/'docs/research/john-williams';result=dict(reference='8d4086c',pop_profile_passthrough_cases=5,source_headers_sha256=fingerprint,regression_cases=regressions,bars=128,bpm=100,key='D',additional_catalog_smoke=catalog_smoke,results=rows)
assert fingerprint=={p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in (root/'Source').glob('*.h')},'production headers changed during rendering'
(dest/'P1_RENDER_RESULTS.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
with zipfile.ZipFile(dest/'P1_MIDI_LISTENING.zip','w',zipfile.ZIP_DEFLATED) as z:
 for path in (0,1,3,4,5,7,11,12):
  for mode in (0,3):z.writestr(f'Williams-p{path}-melodicRoles{mode}.mid',smf((out/f'williams-p{path}-m{mode}.csv').read_bytes()))
 comparisons=[]
 for path in (0,3,5,7):
  for profile,label in ((0,'Neutral'),(1,'Barry')):
   raw,_=run('production',[profile,path,0,512,128,0,3]);z.writestr(f'{label}-p{path}-melodicRoles0.mid',smf(raw))
   current=(out/f'williams-p{path}-m0.csv').read_bytes();assert raw!=current,('cosmetic-only profile',profile,path)
   comparisons.append(dict(profile=label,path=path,sha256=hashlib.sha256(raw).hexdigest(),williams_sha256=hashlib.sha256(current).hexdigest()))
 z.writestr('README.txt','Actual engine MIDI. 128 bars, 100 BPM, D, 960 PPQ. p0 dark calm; p1 dark nervous; p3 dark action; p4 bright quiet; p5 bright nervous; p7 bright action; p11 slow XY; p12 fast XY. Mode0: melody/dialog off; mode3: both on. Channels1..9 existing destinations. No program changes; route to your own patches. These are constructed style outputs, not Williams transcriptions.')
print(regressions,'byte-identical old-profile cases; 52 Williams 128-bar renders; ledger, fixed trigger, no competing foreground; 20 block and 16 controls passed')
print('actual rhythm IDs',sorted({int(i) for r in rows for i in r['rhythm_events']}));print('actual bass IDs',sorted({int(i) for r in rows for i in r['bass_events']}))

result['listening_comparisons']=comparisons
(dest/'P1_RENDER_RESULTS.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
