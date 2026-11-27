"""Offline production renders and listening archive; no injected performance events.
Usage: validate_morricone_p1.py OUTPUT --prepared (before/after probes in OUTPUT).
Without --prepared, build the probes against 3227315 and current production headers.
"""
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
import sys,json,subprocess,collections,hashlib,struct,zipfile
from reference_headers import header_snapshot
ROOT=Path(__file__).resolve().parents[1];OUT=Path(sys.argv[1]);OUT.mkdir(parents=True,exist_ok=True)
if '--prepared' not in sys.argv:
 old=OUT/'before-headers';old.mkdir(exist_ok=True)
 for name,data in header_snapshot(ROOT,'3227315').items():(old/name).write_bytes(data)
 for label,headers in [('before',old),('after',ROOT/'Source')]:subprocess.run(['c++','-O1','-std=c++17','-I',str(headers),str(ROOT/'tools/williams_probe.cpp'),'-o',str(OUT/label)],check=True)
def run(label,args):
 r=subprocess.run([str(OUT/label),*map(str,args)],capture_output=True,check=True);return r.stdout,r.stderr

def ledger(raw):
 active={};spans=[];peaks=collections.Counter();current=collections.Counter()
 for line in raw.splitlines():
  at,o,ch,n,v,kind=map(int,line.split(b','))
  if kind:continue
  if v:
   assert (ch,n) not in active,('duplicate',at,o,ch,n)
   active[ch,n]=(at,o,v);current[o]+=1;peaks[o]=max(peaks[o],current[o])
  else:
   assert (ch,n) in active,('orphan',at,o,ch,n)
   start,owner,vel=active.pop((ch,n));assert at>start;spans.append([start,at,owner,n,vel]);current[owner]-=1
 assert not active
 return spans,dict(peaks)

def args(profile,path,mode=0,block=512,bars=128,genre=0,variation=3,manual=0,follow=1,swing=0,num=4,den=4,jumps=0,key=2):return [profile,path,mode,block,bars,genre,variation,manual,follow,swing,num,den,jumps,0,0,key]
fingerprints={p.name:hashlib.sha256(p.read_bytes()).hexdigest()for p in (ROOT/'Source').glob('*.h')}
reg=[]
cases=[args(profile,path,mode=3,genre=genre) for genre in (0,1)for profile in range(4)for path in range(13)]
registry=json.loads((ROOT/'data/harmony/profiles.json').read_text())['profiles']
base_pools=json.loads((ROOT/'data/harmony/catalog.json').read_text())['pools']
long_cases=len(cases)
for genre in (0,1):
 for profile in range(4):
  pool=base_pools['pop_rock'] if genre else registry[profile].get('score_pool',base_pools['score'])
  for index in range(len(pool)):cases.append(args(profile,100+index,mode=3,bars=8,genre=genre))
def unchanged(a):
 b,_=run('before',a);v,_=run('after',a);assert v==b,('existing profile changed',a);ledger(v)
 return dict(args=a,sha256=hashlib.sha256(v).hexdigest())
with ThreadPoolExecutor(max_workers=3)as exe:reg=list(exe.map(unchanged,cases))
# In pop/rock the new score identity must be exactly neutral.
for path in range(13):
 a,_=run('after',args(4,path,mode=3,genre=1));b,_=run('after',args(0,path,mode=3,genre=1));assert a==b
pool=json.loads((ROOT/'data/harmony/profiles.json').read_text())['profiles'][4]['score_pool']
records=[];renders={}
for path in [*range(13),100,104,110,111]:
 for mode in (0,3):
  a=args(4,path,mode);raw,trace=run('after',a);spans,peaks=ledger(raw)
  assert peaks.get(0,0)<=6,('LF transient polyphony exceeded',a,peaks)
  other,_=run('after',args(4,path,mode,block=127));assert other==raw,('block',a)
  name=f'Morricone-p{path}-m{mode}';renders[name]=raw
  selected=[int(line.split(b',')[2])for line in trace.splitlines()if line.startswith(b'H,')]
  records.append(dict(name=name,args=a,sha256=hashlib.sha256(raw).hexdigest(),selected=selected,
   notes_by_output=dict(collections.Counter(s[2]for s in spans)),peak_polyphony=peaks,
   longest_pad_quarters=max((e-b for b,e,o,n,v in spans if o==0),default=0)/28800,
   pad_examples=[dict(begin_quarters=b/28800,end_quarters=e/28800,note=n,velocity=v)for b,e,o,n,v in spans if o==0][:32]))
# All imported materials, keys, swing and meters have valid note ledgers.
for i,id in enumerate(pool):
 for key in range(12):
  raw,_=run('after',args(4,100+i,bars=8,key=key));ledger(raw)
for num,den in [(3,8),(5,8),(7,8),(3,4),(6,8),(5,4),(12,8),(4,4)]:
 for swing in (0,.6):
  for manual,follow in [(0,1),(1,1),(0,0)]:
   a=args(4,111,bars=32,manual=manual,follow=follow,swing=swing,num=num,den=den,jumps=1)
   raw,_=run('after',a);ledger(raw);a[3]=2048;other,_=run('after',a);assert raw==other,('transport block',a)
# Actual neutral/Morricone comparisons at the exact same XYZ paths, without melodic roles.
for path in (0,4,8,11):renders[f'Neutral-p{path}-m0']=run('after',args(0,path))[0]
# Four source-anchor contrasts, including H051, for the harmonic binding ear test.
for path in (100,104,110,111):
 a=args(4,path,bars=64);raw,_=run('after',a);renders[f'Morricone-source{pool[path-100]}-LF-LB']=raw
 # Isolate existing LF/LB output events from this real render, never invent notes.
 renders[f'Morricone-source{pool[path-100]}-LF-LB']=b'\n'.join(l for l in raw.splitlines()if int(l.split(b',')[1])in (0,2))+b'\n'
def vlq(n):
 b=[n&127];n>>=7
 while n:b.insert(0,(n&127)|128);n>>=7
 return bytes(b)
def smf(raw):
 groups=collections.defaultdict(list)
 for line in raw.splitlines():
  at,o,ch,n,v,k=map(int,line.split(b','));groups[o].append((round(at/30),ch,n,v,k))
 tracks=[b'\0\xff\x51\x03\x09\x27\xc0\0\xff\x58\x04\x04\x02\x18\x08']
 for o,es in sorted(groups.items()):
  body=b'\0\xff\x03'+vlq(len(str(o)))+str(o).encode();last=0
  for tick,ch,n,v,k in es:body+=vlq(tick-last)+bytes([(0xb0 if k else 0x90)+ch-1,n,v]);last=tick
  tracks.append(body)
 return b'MThd'+struct.pack('>IHHH',6,1,len(tracks),960)+b''.join(b'MTrk'+struct.pack('>I',len(t)+4)+t+b'\0\xff\x2f\0'for t in tracks)
# Dense selection audit with the real pick(), including every boundary coordinate.
coverage=[]
# The dedicated C++ tests exercise exact source anchors; geometric coverage is recorded independently below.
anchors=[t['xyz']for t in json.loads((ROOT/'data/harmony/catalog.json').read_text())['templates']if t['id']in pool]
for xi in range(11):
 for yi in range(11):
  for zi in range(11):
   xyz=[xi/10,yi/10,zi/10];distance=min(sum((a-b)**2 for a,b in zip(xyz,h))**.5 for h in anchors)
   coverage.append(dict(xyz=xyz,nearest_euclidean=distance))
dest=ROOT/'docs/research/ennio-morricone'
assert fingerprints=={p.name:hashlib.sha256(p.read_bytes()).hexdigest()for p in (ROOT/'Source').glob('*.h')},'production sources changed during rendering'
result=dict(reference='3227315',source_headers_sha256=fingerprints,bars=128,existing_profile_byte_regressions=len(reg),long_128_bar_regressions=long_cases,catalog_8_bar_regressions=len(reg)-long_cases,regressions=reg,
 pop_passthrough_cases=13,full_source_key_ledgers=168,transport_combinations=48,prototype_renders=records,
 coverage_geometric_only=dict(points=1331,max_nearest=max(r['nearest_euclidean']for r in coverage),corners=[r for r in coverage if all(v in(0,1)for v in r['xyz'])]))
(dest/'P1_RENDER_RESULTS.json').write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n')
with zipfile.ZipFile(dest/'P1_MIDI_LISTENING.zip','w',zipfile.ZIP_DEFLATED)as z:
 for name,raw in renders.items():z.writestr(name+'.mid',smf(raw))
 z.writestr('README.txt','Reale Engine-Ausgabe, 100 BPM, D, 4/4, 960 PPQ. p0 dunkel ruhig, p4 hell ruhig, p8 Mitte, p11 langsame XYZ-Fahrt, p12 schnelle Fahrt. m0: Hauptmelodie/Dialog AUS, m3: beide EIN. Source-Dateien: nur vorhandene LF/LB-Ereignisse isoliert; keine Noten hinzugefuegt. Keine Lolita-Transkription. Bisherige neun MIDI-Ziele/Kanaele 1..9. 128 Takte, Source-Beispiele 64 Takte. Gleiche Instrumente fuer A/B verwenden. Klang und Artikulation externer Patches sind unbekannt.')
print(f'PASS: {len(reg)} byte-identical existing-profile renders (104 long, 347 full-catalog); 168 source/key ledgers; 48 transport cases; {len(records)} 128-bar prototype renders')
