"""Normal automatic-production A/B audit against2170807; never forces a catalog ID.
Usage: python scripts/audit_herrmann_ar_quiet.py DIRECTORY_WITH_BEFORE_AND_AFTER
Build tools/williams_probe.cpp with LAYER_DIAGNOSTICS and each source revision.
"""
import collections,concurrent.futures,gzip,hashlib,itertools,json,struct,subprocess,sys,zipfile
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1];OUT=Path(sys.argv[1]);DOC=ROOT/'docs/research/bernard-herrmann'
SHA={p:hashlib.sha256((OUT/p).read_bytes()).hexdigest()for p in ['before','after']}
LOW=[0,.02,.05,.08,.1,.12,.15,.2]
def args(x,y,z,reg=1,voices=0,variation=3,variety=.5,seed=0,bars=64,path=13,block=512,jump=0,manual=0,follow=1,key=2):
 a=[2,path,voices,block,bars,0,variation,0,1,0,4,4,jump,manual,0,key,seed,100,0,0,x,y,z,5,variety]
 return a+([0 if reg==1 else -1,60,86,follow]if reg else [0,-1,127,follow])
def execute(phase,a):
 cache=OUT/'ar-quiet-cache';cache.mkdir(exist_ok=True);path=cache/(hashlib.sha256((SHA[phase]+json.dumps(a)).encode()).hexdigest()+'.gz')
 if path.exists():return json.loads(gzip.decompress(path.read_bytes()))
 r=subprocess.run([str(OUT/phase),*map(str,a)],capture_output=True,check=True);value=[r.stdout.decode(),r.stderr.decode()];path.write_bytes(gzip.compress(json.dumps(value).encode()));return value

def analyse(raw,trace,bars):
 held={};notes=[];count=collections.Counter();source=collections.Counter();harmonies=[]
 for line in trace.splitlines():
  f=line.split(',')
  if f[0]=='H':harmonies.append([int(f[1]),int(f[2])])
  if f[0]=='L'and f[2]=='4':source[f[3]]+=1
 for line in raw.splitlines():
  at,o,ch,n,v,k=map(int,line.split(','))
  if k:continue
  if v:assert(ch,n)not in held;held[ch,n]=(at,o,v);count[o]+=1
  else:
   assert(ch,n)in held;begin,owner,vel=held.pop((ch,n));assert at>begin;notes.append((begin,at,owner,n,vel))
 assert not held
 roles={};end=bars*115200
 for o in range(9):
  ns=[n for n in notes if n[2]==o];windows=[];active=set()
  for a,b,_,n,v in sorted(ns):
   active.update(range(a//115200,min(bars-1,(b-1)//115200)+1))
   if windows and a<=windows[-1][1]:windows[-1][1]=max(windows[-1][1],b)
   else:windows.append([a,b])
  gaps=[];last=0
  for a,b in windows:gaps.append(a-last);last=b
  gaps.append(end-last)
  run=longest=0;previous=-2
  for bar in sorted(active):run=run+1 if bar==previous+1 else 1;previous=bar;longest=max(longest,run)
  roles[o]=dict(longest_consecutive_active_bars=longest,note_ons=count[o],active_bars=len(active),gate_fraction=sum(b-a for a,b in windows)/end,longest_silence_bars=max(gaps)/115200,longest_active_bars=max((b-a for a,b in windows),default=0)/115200,first_sample=min((n[0]for n in ns),default=None),pitch_range=[min((n[3]for n in ns),default=None),max((n[3]for n in ns),default=None)],first_notes=ns[:9])
 return dict(roles=roles,arp_sources=dict(source),arp_direct_or_manual_note_ons=count[4]-sum(source.values()),harmonies=harmonies,sha256=hashlib.sha256(raw.encode()).hexdigest())
items=[]
for xyz in itertools.product(LOW,repeat=3):items.append(('quiet-'+str(xyz),args(*xyz,bars=8)))
for x,y,z,reg,voices,(v,variety,seed)in itertools.product([0,.33,.66,1],[0,.2,.5,.8,1],[0,.33,.66,1],range(3),[0,3],[(1,0,0),(3,.5,7),(9,1,37)]):
 items.append((f'field-{x}-{y}-{z}-reg{reg}-voices{voices}-v{v}',args(x,y,z,reg,voices,v,variety,seed)))
for path,reg,voices in itertools.product([11,12,14],range(3),[0,3]):items.append((f'path-{path}-reg{reg}-voices{voices}',args(0,.2,0,reg,voices,bars=128,path=path)))
for manual,follow in [(1,1),(2,1),(0,0)]:items.append((f'manual-{manual}-follow-{follow}',args(.5,.85,.8,manual=manual,follow=follow)))
for key,jump,block in itertools.product(range(12),[0,1],[127,2048]):items.append((f'transport-key{key}-jump{jump}-block{block}',args(.5,.85,.8,key=key,jump=jump,block=block,bars=32)))
# Concrete comparable hearing examples, still normal selection.
for name,a in [('cold-quiet',args(0,0,0,bars=8)),('user-arp-dramatic',args(.5,.85,.8)),('user-arp-cell',args(.15,.45,.8)),('slow-xyz',args(.5,.7,.5,path=11,bars=128)),('fast-xyz',args(.5,.7,.5,path=12,bars=128,voices=3)),('lowering-intensity',args(0,.2,0,path=14,bars=32))]:items.append(('listen-'+name,a))

for old in json.loads((DOC/'P1_ACTIVITY_RESULTS.json').read_text())['cases']:
 items.append(('legacy259-'+old['name'],old['args']+[0,-1,127,1]))

def one(item):
 name,a=item;data={};raw={}
 for phase in ['before','after']:
  text,trace=execute(phase,a);raw[phase]=text;data[phase]=analyse(text,trace,a[4])
  if a[26:28]==[60,86]:assert all(60<=int(l.split(',')[3])<=86 for l in text.splitlines()if l.split(',')[1]=='4'and int(l.split(',')[4])and l.split(',')[5]=='0')
 assert data['before']['harmonies']==data['after']['harmonies'],('harmonic selection changed',name)
 unchanged=lambda text:sorted(tuple(map(int,l.split(',')))for l in text.splitlines()if int(l.split(',')[1])not in [0,4])
 assert unchanged(raw['before'])==unchanged(raw['after']),('bass/accent/melodic event changed',name)
 # Other voices are byte-exact unless the corrected cold/descending stillness
 # intentionally permits the authored pad that used to be swallowed.
 if a[1]!=14 and a[21]>=.1:
  filt=lambda text:sorted(tuple(map(int,l.split(',')))for l in text.splitlines()if l.split(',')[1]!='4')
  assert filt(raw['before'])==filt(raw['after']),('other voice changed',name)
 if name.startswith('quiet-'):assert data['after']['roles'][0]['note_ons']>0
 if a[13]or not a[28]:
  filt=lambda text:'\n'.join(l for l in text.splitlines()if l.split(',')[1]=='4');assert filt(raw['before'])==filt(raw['after'])
 return dict(name=name,args=a,non_ar_raw_order_equal=[l for l in raw['before'].splitlines()if l.split(',')[1]!='4']==[l for l in raw['after'].splitlines()if l.split(',')[1]!='4'],**data),raw if name.startswith('listen-')else None
records=[];examples={}
with concurrent.futures.ThreadPoolExecutor(max_workers=2)as pool:
 for i,(record,raw)in enumerate(pool.map(one,items)):
  records.append(record)
  if raw:examples[record['name']]=(raw,record['args'][4])
  if i%100==0:print(i+1,'/',len(items),flush=True)
def vlq(n):
 b=[n&127];n>>=7
 while n:b.insert(0,(n&127)|128);n>>=7
 return bytes(b)
def midi(text,bars):
 tracks=[];meta=b'\0\xff\x51\x03'+(600000).to_bytes(3,'big')+b'\0\xff\x58\x04\x04\x02\x18\x08'+vlq(bars*3840)+b'\xff\x2f\0';tracks.append(meta);events=collections.defaultdict(list)
 for line in text.splitlines():
  at,o,ch,n,v,k=map(int,line.split(','));events[ch].append((round(at/30),bytes([(0xb0 if k else 0x90 if v else 0x80)|(ch-1),n,v])))
 for ch,ev in sorted(events.items()):
  label=('Channel '+str(ch)).encode();data=b'\0\xff\x03'+bytes([len(label)])+label;last=0
  for tick,message in ev:data+=vlq(tick-last)+message;last=tick
  data+=vlq(max(0,bars*3840-last))+b'\xff\x2f\0';tracks.append(data)
 return b'MThd'+struct.pack('>IHHH',6,1,len(tracks),960)+b''.join(b'MTrk'+struct.pack('>I',len(t))+t for t in tracks)
with zipfile.ZipFile(DOC/'P1_AR_QUIET_AB_MIDI.zip','w',zipfile.ZIP_DEFLATED)as z:
 for name,(raw,bars)in examples.items():
  for phase,text in raw.items():z.writestr(name+'-'+phase+'.mid',midi(text,bars))
 z.writestr('LESEN.txt','before=2170807; after=Korrektur. Normale automatische Engine, keine erzwungenen Quellen. D,100 BPM,4/4,960PPQ; AR auf MIDI5, Umfang60..86 (C3..D5); Bass -2Oktaven/24..67. Cold-quiet:8Takte; lowering:32; statische AR:64; XYZ-Fahrten:128. Ein Track je physischem MIDI-Kanal.\n')
(DOC/'P1_AR_QUIET_RESULTS.json').write_text(json.dumps(dict(base='2170807',executables=SHA,cases=records,source_sha256={p.name:hashlib.sha256(p.read_bytes()).hexdigest()for p in(ROOT/'Source').glob('*.h')}),separators=(',',':'))+'\n')
print('Completed',len(records),'normal A/B cases',flush=True)
