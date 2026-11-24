"""Execution-clock regression: strict unchanged cases and enumerated swing corrections."""
import argparse,pathlib,sys,tempfile,subprocess,json,hashlib,itertools,collections,struct
root=pathlib.Path(__file__).resolve().parents[1];sys.path.insert(0,str(root/'Tests'))
from HarmonyImportFixtures import prepare
p=argparse.ArgumentParser();p.add_argument('--probe',required=True);p.add_argument('--compiler',default='c++');p.add_argument('--output',required=True);a=p.parse_args();out=pathlib.Path(a.output);out.mkdir(parents=True,exist_ok=True);cat=json.loads((root/'data/harmony/catalog.json').read_text());byid={t['id']:t for t in cat['templates']};rows=[];blockchecks=0
meters=[(4,4),(3,4),(6,8),(3,8),(5,8),(7,8)];cases=[]
for t in cat['templates']:
 for profile in range(3):
  for route in range(2):cases.append((t['id'],profile,route,meters[(t['id']+profile)%4],(90,120,173)[profile],(0,.2,.5)[(t['id']+route)%3],32,False))
for id,meter,bpm,swing in itertools.product((1005,1008,1034,2015,2035,2037,2038,2039),meters,(90,120,173),(0,.2,.5)):
 cases.append((id,id%3,id%2,meter,bpm,swing,32,True))
for id,num,den in itertools.product((1005,2035),range(1,17),(1,2,4,8,16)):cases.append((id,0,0,(num,den),120,.3,32,True))
for id in (1005,2035,2037):cases.append((id,0,0,(3,8),173,.3,4096,True))
def group_positions(num,den):
 length=num*16//den
 if den==8 and num%3==0:sizes=[6]*(num//3)
 elif den==8 and num>=5:
  sizes=[];rest=length
  while rest>6:sizes.append(4);rest-=4
  sizes.append(rest)
 elif num==5 and den==4:sizes=[6,6,4,4]
 else:sizes=[min(4,length-i) for i in range(0,length,4)]
 total=0;starts=[]
 for size in sizes:starts.append(total);total+=size
 return length,starts

def comparison(before,after,meter,swing,route):
 same=before==after
 length,groups=group_positions(*meter)
 shifted=length%4!=0 or any(g%4 for g in groups)
 # An unshifted metric timeline without a seek retains complete historical output.
 assert same or swing>0 and (shifted or route),('unexpected output change',meter,swing,route)
 def notes(raw):return collections.Counter(tuple(map(int,l.split(b',')))[1:] for l in raw.splitlines())
 b,n=notes(before),notes(after)
 assert b==n,('musical event data changed',meter,swing,route)
 old,new=collections.defaultdict(list),collections.defaultdict(list)
 for raw,dest in ((before,old),(after,new)):
  for line in raw.splitlines():
   values=tuple(map(int,line.split(b',')));dest[values[1:]].append(values[0])
 changes=[(*key,a,b) for key in old for a,b in zip(old[key],new[key]) if a!=b]
 shifts=[r[-1]-r[-2] for r in changes]
 return {'byte_identical':same,'before_sha256':hashlib.sha256(before).hexdigest(),
  'after_sha256':hashlib.sha256(after).hexdigest(),'changed_note_data':b!=n,
  'removed_events':sum((b-n).values()),'added_events':sum((n-b).values()),'changed_timestamps':len(changes),'sample_shift_range':[min(shifts,default=0),max(shifts,default=0)],'examples':changes[:4],
  'correction':None if same else 'unswung_boundaries_or_performance_chase'}

def midi(path,raw,bpm):
 def vlq(n):
  value=[n&127];n>>=7
  while n:value.insert(0,(n&127)|128);n>>=7
  return bytes(value)
 track=bytearray(b'\x00\xff\x51\x03'+round(60000000/bpm).to_bytes(3,'big'));last=0
 for line in raw.splitlines():
  sample,output,ch,note,velocity,kind=map(int,line.split(b','));tick=round(sample*bpm/(48000*60)*960)
  track+=vlq(tick-last)+bytes([(0xb0 if kind else 0x90 if velocity else 0x80)+ch-1,note,velocity]);last=tick
 track+=b'\x00\xff\x2f\x00';path.write_bytes(b'MThd'+struct.pack('>IHHH',6,0,1,960)+b'MTrk'+struct.pack('>I',len(track))+track)

with tempfile.TemporaryDirectory() as tmp:
 tmp=pathlib.Path(tmp);prepare(tmp/'headers',revision='17b15a4',explicit=True);exe=tmp/'baseline';subprocess.run([a.compiler,'-std=c++17','-O2','-I',str(tmp/'headers'),str(root/'tools/harmony_import_probe.cpp'),'-o',str(exe)],check=True)
 for id,profile,route,meter,bpm,swing,bars,blocks in cases:
  t=byid[id];args=list(map(str,[id,0,*t['xyz'],1,0,1,1,bars,512,bpm,route,profile,swing,0 if id<2000 else 1,*meter]))
  before=subprocess.check_output([str(exe)]+args);after=subprocess.check_output([a.probe]+args);delta=comparison(before,after,meter,swing,route)
  if blocks:
   reference=[tuple(map(int,l.split(b','))) for l in after.splitlines()]
   for block in (127,480,8192):
    args[10]=str(block);other=[tuple(map(int,l.split(b','))) for l in subprocess.check_output([a.probe]+args).splitlines()]
    assert len(other)==len(reference) and all(x[1:]==y[1:] and abs(x[0]-y[0])<=1 for x,y in zip(other,reference)),(id,meter,bpm,block,'block')
    blockchecks+=1
  rows.append({'id':id,'profile':profile,'route':route,'meter':meter,'bpm':bpm,'swing':swing,'bars':bars,**delta})
 # Direct regression of the just-migrated free-line, scene and manual/shared-claim paths.
 for (num,den),genre,follow,swing,scenario in itertools.product(((4,4),(3,8),(5,8),(7,8)),range(2),range(2),(0,.3),range(3)):
  id=1005 if genre==0 else 2025;t=byid[id];profile=(num+scenario)%3;route=scenario%2
  args=list(map(str,[id,0,*t['xyz'],follow,0,0,1,32,512,120,route,profile,swing,genre,num,den,scenario]))
  before=subprocess.check_output([str(exe)]+args);after=subprocess.check_output([a.probe]+args)
  delta=comparison(before,after,(num,den),swing,route)
  reference=[tuple(map(int,l.split(b','))) for l in after.splitlines()]
  for block in (127,8192):
   args[10]=str(block);other=[tuple(map(int,l.split(b','))) for l in subprocess.check_output([a.probe]+args).splitlines()]
   assert len(other)==len(reference) and all(x[1:]==y[1:] and abs(x[0]-y[0])<=1 for x,y in zip(other,reference)),('planning',num,den,genre,block)
   blockchecks+=1
  rows.append({'id':id,'profile':profile,'route':route,'meter':[num,den],'bpm':120,'swing':swing,'bars':32,'planning_scenario':scenario,'follow':follow,**delta})
 # Direct audible/semantic examples: alternating existing custom chords, held voices.
 for num in (3,5,7,6):
  args=list(map(str,[1005,0,.5,.8,0,1,0,0,0,8,512,120,0,0,.5,0,num,8,3]))
  before=subprocess.check_output([str(exe)]+args);after=subprocess.check_output([a.probe]+args)
  delta=comparison(before,after,(num,8),.5,False);bar=num*12000
  actual=[tuple(map(int,l.split(b','))) for l in after.splitlines()]
  legacy=[tuple(map(int,l.split(b','))) for l in before.splitlines()]
  actual_bass=[e[0] for e in actual if e[1]==2 and e[4]>0 and not e[5]]
  legacy_bass=[e[0] for e in legacy if e[1]==2 and e[4]>0 and not e[5]]
  assert actual_bass==[b*bar for b in range(8)],('nominal chord boundary',num,actual_bass)
  expected=[]
  for b in range(8):
   cell=b*num*2;delay=(.667 if cell%4==2 else .333 if cell%4 in (1,3) else 0)*.5
   expected.append(round((cell+delay)*6000))
  assert legacy_bass==expected,('legacy reference boundary',num,legacy_bass,expected)
  for block in (127,8192):
   args[10]=str(block);assert subprocess.check_output([a.probe]+args)==after;blockchecks+=1
  midi(out/f'held-{num}-8-before.mid',before,120);midi(out/f'held-{num}-8-after.mid',after,120)
  rows.append({'id':'custom-C-Fm','profile':0,'route':0,'meter':[num,8],'bpm':120,'swing':.5,'bars':8,'legacy_bass_samples':legacy_bass,'bass_samples':actual_bass,**delta})
(out/'regression.json').write_text(json.dumps({'baseline':'17b15a4','comparisons':len(rows),'byte_identical':sum(r['byte_identical'] for r in rows),'corrected':sum(not r['byte_identical'] for r in rows),'block_comparisons':blockchecks,'results':rows},indent=2)+'\n');print(len(rows),'comparisons;',sum(r['byte_identical'] for r in rows),'byte-identical;',sum(not r['byte_identical'] for r in rows),'documented swing/chase corrections;',blockchecks,'block comparisons')
