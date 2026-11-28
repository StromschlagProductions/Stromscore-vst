"""Actual production regression and hearing studies for bounded Herrmann P1."""
from pathlib import Path
import sys,json,subprocess,collections,hashlib,concurrent.futures,zipfile,struct,time
ROOT=Path(__file__).resolve().parents[1];OUT=Path(sys.argv[1]);OUT.mkdir(parents=True,exist_ok=True)
def args(p,path,mode=3,block=512,bars=128,genre=0,variation=3,key=2,swing=0,num=4,den=4,jumps=0,mask=0,bpm=100,manual=0,follow=1):return [p,path,mode,block,bars,genre,variation,manual,follow,swing,num,den,jumps,0,0,key,0,bpm,mask,0]
def run(label,a):
 p=subprocess.run([str(OUT/label),*map(str,a)],capture_output=True,check=True);return p.stdout,p.stderr

def ledger(raw):
 held={};notes=[];peaks=collections.Counter();counts=collections.Counter()
 for line in raw.splitlines():
  at,o,ch,n,v,k=map(int,line.split(b','))
  if k:continue
  if v:
   assert (ch,n)not in held,('duplicate',at,o,ch,n);held[ch,n]=(at,o,v);counts[o]+=1;peaks[o]=max(peaks[o],counts[o])
  else:
   assert(ch,n)in held,('orphan',at,o,ch,n)
   begin,owner,velocity=held.pop((ch,n));assert at>begin,('zero note',at,o,n);notes.append([begin,at,owner,n,velocity]);counts[owner]-=1
 assert not held,held
 return notes,dict(peaks)

def regression(a):
 before,_=run('before-verified',a);after,_=run('after',a);assert before==after,('regression',a);ledger(after);return dict(args=a,sha256=hashlib.sha256(after).hexdigest())
registry=json.loads((ROOT/'data/harmony/profiles.json').read_text(encoding='utf-8'))['profiles'];pools=json.loads((ROOT/'data/harmony/catalog.json').read_text(encoding='utf-8'))['pools']
cases=[args(p,path,genre=g)for p in range(6)for g in range(2)if not(p==2 and g==0)for path in range(13)]
for p in range(6):
 for g in range(2):
  if p==2 and g==0:continue
  pool=pools['pop_rock']if g else registry[p].get('score_pool',pools['score'])
  cases.extend(args(p,100+i,bars=8,genre=g)for i in range(len(pool)))
cache=OUT/'regressions.json'
if '--reuse-regressions' in sys.argv:
 reg=json.loads(cache.read_text());assert len(reg)==len(cases)
else:
 with concurrent.futures.ThreadPoolExecutor(max_workers=2)as ex:reg=list(ex.map(regression,cases))
 cache.write_text(json.dumps(reg))
print('Unchanged profile byte regressions',len(reg),flush=True)
pool=registry[2]['score_pool'];trans=[]
for i,id in enumerate(pool):
 for key in range(12):
  a=args(2,100+i,bars=8,key=key);raw,_=run('after',a);
  try:notes,peak=ledger(raw)
  except AssertionError as e:raise AssertionError(('ledger',id,key,a)) from e
  assert notes,('silent source',id,key)
  if i%11==0:
   other,_=run('after',args(2,100+i,bars=8,key=key,block=127));assert raw==other,('blocks',id,key)
  trans.append(dict(id=id,key=key,notes=len(notes),peak=peak,sha256=hashlib.sha256(raw).hexdigest()))
print('Harmonic source transpositions',len(trans),flush=True)
transport=[]
for num,den in [(4,4),(3,8),(5,8),(7,8),(3,4),(6,8)]:
 for swing in [0,.6]:
  for manual,follow in [(0,1),(1,1),(0,0)]:
   a=args(2,11,bars=16,num=num,den=den,swing=swing,jumps=1,manual=manual,follow=follow)
   raw,_=run('after',a);other,_=run('after',args(2,11,bars=16,num=num,den=den,swing=swing,jumps=1,manual=manual,follow=follow,block=127));assert raw==other,('transport blocks',a);ledger(raw);transport.append(a)
print('Transport cases',len(transport),flush=True)
studies=[('01-latente-Spannung',30001,0),('02-Halbton-Gelenk',70003,0),('03-chromatische-Bloecke',70015,0),('04-kalte-Helligkeit',70066,0),('05-getrennte-Komponenten',70051,0),('06-grosse-Septime-Schichten',70053,0),('07-helle-verschmolzene-Komponenten',70057,0),('08-geplante-Verschmelzung',70060,0),('09-oberes-Pedal',70064,0),('10-fremdes-Hochpedal',70068,0),('11-Motiv-Gegenstimme',8,2),('12-optionale-Hauptmelodie',8,3),('13-langsam-XYZ',11,3),('14-schnell-XYZ',12,3)]
records=[];renders={};used=collections.Counter()
for name,target,mode in studies:
 path=100+pool.index(target) if target>=1000 else target
 a=args(2,path,mode=mode);start=time.monotonic();raw,trace=run('after',a);elapsed=time.monotonic()-start;notes,peak=ledger(raw);renders[name]=raw
 counts=collections.Counter(n[2]for n in notes);uses=collections.Counter()
 for line in trace.splitlines():
  fields=line.decode().split(',')
  if fields[0]=='L':uses[fields[3]]+=1;used[fields[3]]+=1
 records.append(dict(name=name,args=a,motif_trace=[l.decode()for l in trace.splitlines()if l.startswith(b'P,')],notes_by_output=dict(counts),peak=peak,source_note_ons=dict(uses),first_notes=notes[:32],render_seconds=elapsed,harmonies=[l.decode()for l in trace.splitlines()if l.startswith(b'H,')]))
 if path<100 or name.startswith(('02','04','08')):
  actual=next(l.decode().split(',') for l in trace.splitlines()if l.startswith(b'S,'))
  neutral=args(0,path if path<100 else 13,mode=mode,variation=int(actual[1]))
  if path>=100:neutral.extend(map(float,actual[2:5]))
  renders[name+'-Neutral-AB']=run('after',neutral)[0]

def vlq(n):
 b=[n&127];n>>=7
 while n:b.insert(0,(n&127)|128);n>>=7
 return bytes(b)
def midi(raw):
 tracks=[];events=collections.defaultdict(list)
 for line in raw.splitlines():
  at,o,ch,n,v,kind=map(int,line.split(b','));tick=round(at/30);events[o].append((tick,bytes([(0xb0 if kind else 0x90 if v else 0x80)|(ch-1),n,v])))
 meta=b'\0\xff\x51\x03'+(600000).to_bytes(3,'big')+b'\0\xff\x58\x04\x04\x02\x18\x08\0\xff\x2f\0';tracks.append(b'MTrk'+struct.pack('>I',len(meta))+meta)
 for o,ev in sorted(events.items()):
  name=['LF','KF','LB','KB','AR','TU','ST','GS','HM'][o].encode();data=b'\0\xff\x03'+bytes([len(name)])+name;last=0
  for tick,msg in ev:data+=vlq(tick-last)+msg;last=tick
  data+=vlq(max(0,128*3840-last))+b'\xff\x2f\0';tracks.append(b'MTrk'+struct.pack('>I',len(data))+data)
 return b'MThd'+struct.pack('>IHHH',6,1,len(tracks),960)+b''.join(tracks)
folder=ROOT/'docs/research/bernard-herrmann'
with zipfile.ZipFile(folder/'P1_MIDI_LISTENING.zip','w',zipfile.ZIP_DEFLATED)as z:
 for name,raw in renders.items():z.writestr(name+'.mid',midi(raw))
 z.writestr('LESEN.txt','Tatsaechliche STROMSCORE-Ausgabe, keine Filmtranskriptionen. 128 Takte, D, 100 BPM, 4/4, 960 PPQ.\nGetrennte aktive MIDI-Rollen; Instrumentierung in der DAW zuweisen.\nA/B verwendet identische XYZ-Werte, siehe P1_RENDER_RESULTS.json. Musikalische Abnahme steht aus.\n')
report=dict(base='58ea29d',regressions=reg,transpositions=trans,transport_cases=transport,studies=records,source_note_ons=dict(used),source_sha256={p.name:hashlib.sha256(p.read_bytes()).hexdigest()for p in(ROOT/'Source').glob('*.h')})
(folder/'P1_RENDER_RESULTS.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print('Production hearing studies',len(records),'used R/B sources',len(used),flush=True)
