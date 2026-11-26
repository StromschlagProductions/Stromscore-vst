"""P2 production A/B, explicit context diagnostics and real MIDI hearing examples."""
from pathlib import Path
import sys,subprocess,json,hashlib,collections,struct,zipfile
from reference_headers import header_snapshot
root=Path(__file__).resolve().parents[1];out=Path(sys.argv[1]);out.mkdir(exist_ok=True,parents=True)
if '--prepared' not in sys.argv:
 old=out/'before-headers';old.mkdir(exist_ok=True)
 for n,b in header_snapshot(root,'2c6f366').items():(old/n).write_bytes(b)
 subprocess.run([sys.executable,str(root/'Tests/ExecutionFixtures.py'),str(out/'headers')],check=True)
 for label,headers,flags in [('before',old,[]),('after',root/'Source',[]),('diagnostic',out/'headers',['-DOCTATONIC_DIAGNOSTICS'])]:
  subprocess.run(['c++','-std=c++17','-O1',*flags,'-I',str(headers),str(root/'tools/williams_probe.cpp'),'-o',str(out/label)],check=True)
finger={p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in (root/'Source').glob('*.h')}
def run(label,args):
 r=subprocess.run([str(out/label),*map(str,args)],capture_output=True,check=True);return r.stdout,r.stderr

def events(raw):return [tuple(map(int,l.split(b',')))for l in raw.splitlines()]
def ledger(raw):
 active={};onsets=set()
 for t,o,ch,n,v,k in events(raw):
  if k:continue
  key=ch,n
  if v:assert key not in active,('double',t,key);active[key]=t;onsets.add((t,o,n))
  else:assert key in active and t>active[key],('orphan/duration',t,key);active.pop(key)
 assert not active
 return onsets

def vlq(n):
 b=[n&127];n>>=7
 while n:b.insert(0,(n&127)|128);n>>=7
 return bytes(b)
def smf(raw):
 tracks=[b'\0\xff\x51\x03\x09\x27\xc0\0\xff\x58\x04\x04\x02\x18\x08']
 for output in range(9):
  b=bytearray();previous=0
  for t,o,ch,n,v,k in events(raw):
   if o!=output:continue
   tick=round(t/30);b+=vlq(tick-previous)+bytes([(0xb0 if k else 0x90)+ch-1,n,v]);previous=tick
  tracks.append(bytes(b))
 return b'MThd'+struct.pack('>IHHH',6,1,10,960)+b''.join(b'MTrk'+struct.pack('>I',len(b)+4)+b+b'\0\xff\x2f\0'for b in tracks)

def compare(args):
 before,_=run('before',args);after,trace=run('diagnostic',args);plain,_=run('after',args);assert after==plain,'inspection altered production'
 onsets=ledger(after);stable={0,1,2,3,5,6}
 assert collections.Counter(e for e in events(before)if e[1] in stable)==collections.Counter(e for e in events(after)if e[1] in stable),('accompaniment changed',args)
 new=[];unresolved=[]
 for line in trace.splitlines():
  if not line.startswith(b'O,'):continue
  _,t,o,n,mask,chord,targetAt,target,identity=line.decode().split(',');t,o,n,mask,chord,targetAt,target,identity=map(int,(t,o,n,mask,chord,targetAt,target,identity))
  assert mask&(1<<(n%12)),('outside octatonic context',args,t,o,n)
  if targetAt>=0:
   row=dict(at_quarters=t/28800,output=o,pitch=n,chord_mask=chord,context_mask=mask,target_quarters=targetAt/28800,target_pitch=target,material_identity=identity,resolved=(targetAt,o,target)in onsets)
   new.append(row)
   if not row['resolved']:unresolved.append(row)
 arpb=collections.Counter(e for e in events(before)if e[1]==4);arpa=collections.Counter(e for e in events(after)if e[1]==4)
 return before,after,dict(args=list(args),byte_equal=before==after,arp_events_equal=arpb==arpa,passing=new,unresolved=unresolved,sha256=hashlib.sha256(after).hexdigest())
rows=[];dest=root/'docs/research/john-williams'
with zipfile.ZipFile(dest/'P2_OCTATONIC_AB.zip','w',zipfile.ZIP_DEFLATED)as z:
 for path in range(13):
  for mode in range(4):
   args=[3,path,mode,512,128,0,3];before,after,row=compare(args);rows.append(row)
   if mode==0:assert before==after,'muted melodic roles changed output'
   if path in (3,11,12)and mode in (2,3):
    for label,raw in [('before',before),('after',after)]:z.writestr(f'{label}-XYZ{path}-voices{mode}-keyD.mid',smf(raw))
 # Reference harmonies, all twelve transpositions. Actual production anchors, no injected chord index.
 pool=json.loads((root/'data/harmony/profiles.json').read_text())['profiles'][3]['score_pool']
 for identifier in (40012,40014,40015,40016,40017,40019,40046,40054):
  for key in range(12):
   args=[3,100+pool.index(identifier),3,512,128,0,3,0,1,0,4,4,0,0,0,key]
   before,after,row=compare(args);row['reference_id']=identifier;row['key']=key;rows.append(row)
   if key==0 and identifier in (40012,40014,40017,40019,40046,40054):
    for label,raw in [('before',before),('after',after)]:z.writestr(f'{label}-H{identifier-40000:02}-keyC.mid',smf(raw))
 z.writestr('README.txt','Actual engine A/B: before 2c6f366 / after P2. 128 bars, 100 BPM, 960 PPQ. Harmonic reference anchors in C; XYZ3 dark action, XYZ11 slow and XYZ12 fast drives in D. voices2 dialog only;voices3 both. Nine original MIDI destinations; use identical patches. Constructed vocabulary, no film-theme transcriptions.')
regressions=0
for genre in (0,1):
 for profile in (0,1,2):
  for path in (0,3,7,11,12):
   args=[profile,path,3,512,128,genre,3];assert run('before',args)[0]==run('after',args)[0];regressions+=1
for path in (0,3,7,11,12):
 args=[3,path,3,512,128,1,3];assert run('before',args)[0]==run('after',args)[0]
for path in (3,11,12):
 for mode in (2,3):
  args=[3,path,mode,512,128,0,3];a=run('after',args)[0];assert a==run('after',args)[0];args[3]=127;assert a==run('after',args)[0]
# Both Follow states, odd meters, swing and deterministic warm loop/forward seek/restart.
for follow in (0,1):
 for num,den in ((4,4),(3,8),(5,8),(7,8)):
  args=[3,3,3,512,32,0,3,0,follow,.3,num,den,1];a=run('after',args)[0];ledger(a);args[3]=127;assert a==run('after',args)[0]
# Exercise new passing notes under Swing, beyond the first full-reprise window.
args=[3,100+pool.index(40012),3,512,128,0,3,0,1,.3,4,4,0,0,0,0]
swing_before,swing_after,swing_row=compare(args)
assert swing_row['passing'] and not swing_row['unresolved'] and swing_row['arp_events_equal']
swing_row['accompaniment_unchanged']=True
args[3]=127;assert run('after',args)[0]==swing_after
assert finger=={p.name:hashlib.sha256(p.read_bytes()).hexdigest()for p in(root/'Source').glob('*.h')}
result=dict(reference='2c6f366',source_sha256=finger,production_pairs=len(rows),old_profile_byte_cases=regressions,swing_reference=swing_row,rows=rows)
(dest/'P2_OCTATONIC_RESULTS.json').write_text(json.dumps(result,indent=2)+'\n')
print('Production pairs',len(rows),'old profiles byte-identical',regressions,'passing notes',sum(len(x['passing'])for x in rows),'unresolved',sum(len(x['unresolved'])for x in rows),'Arp differences',sum(not x['arp_events_equal']for x in rows))
