"""Production A/B, immutable research check, actual note ledgers and SMF listening.
Run: python scripts/validate_carpenter_p1.py OUTPUT. Base: accepted 44d2404.
"""
from pathlib import Path
import sys,json,subprocess,hashlib,collections,struct,zipfile,concurrent.futures,math,time
from reference_headers import header_snapshot
ROOT=Path(__file__).resolve().parents[1];OUT=Path(sys.argv[1]);OUT.mkdir(parents=True,exist_ok=True)
def call(cmd):subprocess.run(list(map(str,cmd)),check=True,cwd=ROOT)
base=OUT/'base';base.mkdir(exist_ok=True)
for n,b in header_snapshot(ROOT,'44d2404').items():(base/n).write_bytes(b)
for label,headers in [('before',base),('after',ROOT/'Source')]:
 cmd=['c++','-O1','-std=c++17','-I',headers,ROOT/'tools/williams_probe.cpp','-o',OUT/label]
 if label=='after':cmd.insert(1,'-DSEQUENCE_DIAGNOSTICS=1')
 call(cmd)
call(['c++','-O1','-std=c++17','-I',ROOT/'Source',ROOT/'tools/carpenter_coverage.cpp','-o',OUT/'coverage'])
with (ROOT/'docs/research/john-carpenter/P1_XYZ_COVERAGE.csv').open('wb') as f:subprocess.run([str(OUT/'coverage')],stdout=f,check=True)
def args(profile,path,mode=3,block=512,bars=128,genre=0,variation=3,manual=0,follow=1,swing=0,num=4,den=4,jumps=0,key=2,bpm=100,mask=0):return [profile,path,mode,block,bars,genre,variation,manual,follow,swing,num,den,jumps,0,0,key,0,bpm,mask,int(profile==5)]
def run(label,a):
 p=subprocess.run([str(OUT/label),*map(str,a)],capture_output=True,check=True)
 return p.stdout,p.stderr

def ledger(raw):
 active={};spans=[];peak=collections.Counter();current=collections.Counter()
 for line in raw.splitlines():
  at,o,ch,n,v,kind=map(int,line.split(b','))
  if kind:continue
  if v:
   assert (ch,n) not in active,('duplicate',at,o,ch,n)
   active[ch,n]=(at,o,v);current[o]+=1;peak[o]=max(peak[o],current[o])
  else:
   assert (ch,n) in active,('orphan',at,o,ch,n)
   start,owner,velocity=active.pop((ch,n));assert at>start,('zero',at,o,ch,n)
   spans.append([start,at,owner,n,velocity]);current[owner]-=1
 assert not active,active
 return spans,dict(peak)

def regression(a):
 old,_=run('before',a);new,_=run('after',a)
 assert old==new,('accepted profile regression',a)
 ledger(new);return dict(args=a,sha256=hashlib.sha256(new).hexdigest())
registry=json.loads((ROOT/'data/harmony/profiles.json').read_text(encoding="utf-8"))['profiles'];pools=json.loads((ROOT/'data/harmony/catalog.json').read_text(encoding="utf-8"))['pools']
cases=[args(p,path,genre=g)for p in range(5)for g in range(2)for path in range(13)]
for p in range(5):
 for g in range(2):
  pool=pools['pop_rock'] if g else registry[p].get('score_pool',pools['score'])
  for i in range(len(pool)):cases.append(args(p,100+i,bars=8,genre=g))
with concurrent.futures.ThreadPoolExecutor(max_workers=2)as ex:reg=list(ex.map(regression,cases))
print('Accepted-profile byte regressions',len(reg),flush=True)
# Hearing cases use real engine output and actual muting, never synthetic notes.
studies=[('01-pulsfreier-Drone-Echo',13,0,0,(1<<1)|(1<<2)|(1<<4)),('02-Drone-Bassfigur',100,0,0,1<<2),('03-Bass-Sequencer1',106,0,0,0),('04-zwei-Sequencer',106,2,0,0),('05-melancholisch',120,2,0,0),('06-intensive-Spannung',10,2,0,0),('07-hohe-Unruhe',9,2,0,0),('08-Reduktion-Wiederaufnahme',8,2,0,0),('09-optionale-Hauptmelodie',106,3,0,0),('10-langsam-XYZ',11,3,0,0),('11-schnell-XYZ',12,3,0,0)]
records=[];renders={};used=collections.Counter();identities=collections.defaultdict(set)
for name,path,mode,jump,mask in studies:
 a=args(5,path,mode=mode,jumps=jump,mask=mask)
 if path==13:a.extend([.4,.15,.1])
 start=time.perf_counter();raw,trace=run('after',a);elapsed=time.perf_counter()-start;spans,peak=ledger(raw)
 b=a.copy();b[3]=127;other,_=run('after',b);assert other==raw,('block size',name)
 assert peak.get(0,0)<=6 and all(peak.get(o,0)<=1 for o in [2,3,4,7,8]),(name,peak)
 local=collections.Counter()
 for line in trace.splitlines():
  if line.startswith(b'Q,'):
   fields=line.decode().split(',');used[fields[3]]+=1;local[fields[3]]+=1;identities[fields[3]].add(fields[4])
 for output,id in [(2,'JC-B001'),(5,'JC-M004')]:
  count=sum(s[2]==output for s in spans)
  if count:local[id]=count;used[id]+=count
 record=dict(name=name,args=a,elapsed_seconds=elapsed,notes_by_output=dict(collections.Counter(s[2]for s in spans)),peak_polyphony=peak,source_note_counts=dict(local),longest_notes_quarters={o:max((e-b for b,e,p,n,v in spans if p==o),default=0)/28800 for o in range(9)},examples=spans[:36],sha256=hashlib.sha256(raw).hexdigest())
 records.append(record);renders[name]=raw
 # Same field/settings with accepted neutral core, for honest profile contrast.
 if path in [8,106,120]:
  b=a.copy();b[0]=0
  if path>=100:
   h=json.loads((ROOT/'data/harmony/catalog.json').read_text(encoding="utf-8"))['templates'];pool=registry[5]['score_pool'];source=next(t for t in h if t['id']==pool[path-100]);xyz=source['xyz'];
   b[1]=13;b.extend(xyz);renders[name+'-Neutral-AB']=run('before',b)[0]
  else:renders[name+'-Neutral-AB']=run('before',b)[0]
print('Hearing studies',len(records), 'used source cells',len(used),flush=True)
# Every imported H in all keys; all retained sources have their complete pitches/gates.
transpositions=[]
for i,id in enumerate(registry[5]['score_pool']):
 for key in range(12):
  a=args(5,100+i,bars=8,key=key);raw,_=run('after',a);ledger(raw);transpositions.append([id,key,hashlib.sha256(raw).hexdigest()])
# Tempo, swing, manual/Follow, host meters, stop/loop/seek, and block sizes.
transport=[]
for num,den in [(3,8),(5,8),(7,8),(3,4),(6,8),(5,4),(12,8),(4,4)]:
 for swing in [0,.6]:
  for manual,follow in [(0,1),(1,1),(0,0)]:
   a=args(5,106,bars=16,num=num,den=den,swing=swing,manual=manual,follow=follow,jumps=1)
   raw,_=run('after',a);ledger(raw);b=a.copy();b[3]=2048;other,_=run('after',b);assert other==raw,('transport',a);transport.append(a)
tempo_timing=[]
for bpm in [60,137,180]:
 a=args(5,106,bars=16,bpm=bpm);raw,_=run('after',a);ledger(raw);b=a.copy();b[3]=127;other=run('after',b)[0]
 def positioned(data):
  rows=[tuple(map(int,l.split(b','))) for l in data.splitlines()]
  return sorted(rows,key=lambda r:(round(r[0]*960/(48000*60/bpm)),*r[1:]))
 left,right=positioned(raw),positioned(other);assert len(left)==len(right)
 max_difference=0
 for l,r in zip(left,right):
  assert l[1:]==r[1:] and round(l[0]*960/(48000*60/bpm))==round(r[0]*960/(48000*60/bpm)),('musical tempo block',a,l,r)
  max_difference=max(max_difference,abs(l[0]-r[0]))
 assert max_difference<=1,('sample rounding',a,max_difference)
 tempo_timing.append(dict(bpm=bpm,max_sample_difference=max_difference,musical_ticks_equal=True))
# Verify immutable original research bytes.
manifest=json.loads((ROOT/'docs/research/john-carpenter/CANONICAL_MANIFEST.json').read_text(encoding="utf-8"))
for f in manifest['files']:
 p=ROOT/'docs/research/john-carpenter'/f['name'];assert hashlib.sha256(p.read_bytes()).hexdigest()==f['sha256']

def vlq(n):
 b=[n&127];n>>=7
 while n:b.insert(0,(n&127)|128);n>>=7
 return bytes(b)
def midi(raw):
 tracks=[];events=collections.defaultdict(list)
 for line in raw.splitlines():
  at,o,ch,n,v,kind=map(int,line.split(b','));tick=round(at/30)
  events[o].append((tick,bytes([(0xb0 if kind else 0x90 if v else 0x80)|(ch-1),n,v])))
 meta=b'\0\xff\x51\x03'+(600000).to_bytes(3,'big')+b'\0\xff\x58\x04\x04\x02\x18\x08\0\xff\x2f\0'
 tracks.append(b'MTrk'+struct.pack('>I',len(meta))+meta)
 for o,ev in sorted(events.items()):
  name=['LF','KF','LB','KB','AR','TU','ST','GS','HM'][o].encode();data=b'\0\xff\x03'+bytes([len(name)])+name;last=0
  for tick,msg in ev:data+=vlq(tick-last)+msg;last=tick
  data+=vlq(max(0,128*3840-last))+b'\xff\x2f\0';tracks.append(b'MTrk'+struct.pack('>I',len(data))+data)
 return b'MThd'+struct.pack('>IHHH',6,1,len(tracks),960)+b''.join(tracks)
listening=ROOT/'docs/research/john-carpenter/P1_MIDI_LISTENING.zip'
with zipfile.ZipFile(listening,'w',zipfile.ZIP_DEFLATED)as z:
 for name,raw in renders.items():z.writestr(name+'.mid',midi(raw))
 z.writestr('LESEN.txt','Tatsaechliche STROMSCORE-Ausgabe. 4/4, D, 100 BPM, 128 Takte, 960 PPQ.\nGetrennte Spuren der aktiven Rollen, Kanaele1-9; Instrumente in der DAW zuweisen.\nDateien 01/02 muten gezielt andere Rollen; keine nachtraeglich erfundenen Noten.\nKlangliche Qualitaet und Mischung vom Anwender abnehmen.\n')
report=dict(base='44d2404',regressions=reg,studies=records,source_note_counts=dict(used),source_identities={k:sorted(v) for k,v in identities.items()},transpositions=transpositions,transport_cases=transport,tempo_cases=tempo_timing,source_sha256={p.name:hashlib.sha256(p.read_bytes()).hexdigest()for p in (ROOT/'Source').glob('*.h')})
(ROOT/'docs/research/john-carpenter/P1_RENDER_RESULTS.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print('Carpenter production A/B, transpositions, transport and hearing archive passed',flush=True)
