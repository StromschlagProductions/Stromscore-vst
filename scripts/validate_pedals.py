"""Production MIDI A/B for independent pedals. No injected harmony or note plans."""
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
import subprocess,sys,json,collections,hashlib,zipfile,struct
from reference_headers import header_snapshot
ROOT=Path(__file__).resolve().parents[1]
OUT=Path(sys.argv[1]);OUT.mkdir(parents=True,exist_ok=True)
if '--prepared' not in sys.argv:
 old=OUT/'before-headers';old.mkdir(exist_ok=True)
 for name,data in header_snapshot(ROOT,'1d3c1d5').items():(old/name).write_bytes(data)
 for label,headers in [('before',old),('after',ROOT/'Source')]:
  subprocess.run(['c++','-O2','-std=c++17','-I',str(headers),str(ROOT/'tools/williams_probe.cpp'),'-o',str(OUT/label)],check=True)
def run(label,args):
 r=subprocess.run([str(OUT/label),*map(str,args)],check=True,capture_output=True);return r.stdout,r.stderr
def events(raw):return [tuple(map(int,line.split(b',')))for line in raw.splitlines()]
def ledger(rows):
 active={};spans=[]
 for t,o,ch,n,v,k in rows:
  if k:continue
  if v:assert(ch,n)not in active,('duplicate',t,o,ch,n);active[ch,n]=(t,o)
  else:
   assert(ch,n)in active,('orphan',t,o,ch,n)
   start,owner=active.pop((ch,n));assert t>=start;spans.append((start,t,owner,n))
 assert not active
 return spans
pool=json.loads((ROOT/'data/harmony/profiles.json').read_text())['profiles'][3]['score_pool']
def anchor(id,key=2,bars=128):return [3,100+pool.index(id),3,512,bars,0,3,0,1,0,4,4,0,0,0,key,0]
cases=[]
for genre,profile in [(0,0),(0,1),(0,2),(1,0),(1,1),(1,2),(1,3)]:
 for path in range(13):cases.append(('unchanged',[profile,path,3,512,128,genre,3]))
for id in pool:cases.append(('williams',anchor(id,bars=64)))
for id in (40003,40050,40061):
 for key in range(12):cases.append(('williams',anchor(id,key,bars=32)))
 for manual,follow in ((1,1),(1,0),(0,0)):
  a=anchor(id,bars=32);a[7]=manual;a[8]=follow;cases.append(('unchanged',a))
for path in range(13):cases.append(('williams',[3,path,3,512,128,0,3]))
def compare(case):
 kind,args=case;b,bh=run('before',args);a,ah=run('after',args);be,ae=events(b),events(a);spans=ledger(ae)
 assert bh==ah,('harmony selection changed',args)
 if kind=='unchanged':assert b==a,('regression',args)
 else:
  def streams(rows):
   result=collections.defaultdict(list)
   for t,o,ch,n,v,k in rows:
    if o not in (2,3):result[o,ch,n,k].append((t,v))
   return dict(result)
  assert streams(be)==streams(ae),('nonbass note/control stream changed',args)
 result=dict(args=args,byte_equal=b==a,hash_before=hashlib.sha256(b).hexdigest(),hash_after=hashlib.sha256(a).hexdigest(),
  bass_on_before=sum(e[1]in (2,3)and e[4]>0 and e[5]==0 for e in be),bass_on_after=sum(e[1]in (2,3)and e[4]>0 and e[5]==0 for e in ae),
  bass_span_examples_quarters=[[(start/28800),end/28800,n]for start,end,o,n in spans if o in (2,3)][:12],
  bass_longest_quarters=max([(end-start)/28800 for start,end,o,n in spans if o in (2,3)],default=0))
 key=hashlib.sha256(json.dumps(args).encode()).hexdigest()[:16];result['render']=key
 (OUT/(key+'-before.csv')).write_bytes(b);(OUT/(key+'-after.csv')).write_bytes(a)
 return result
with ThreadPoolExecutor(max_workers=3)as exe:
 results=[]
 for i,r in enumerate(exe.map(compare,cases)):
  results.append(r)
  if i%20==0:print('A/B',i+1,'/',len(cases),flush=True)
controls=[]
for id in (40003,40050,40061):
 for num,den in ((4,4),(3,8),(5,8),(7,8)):
  for swing in (0,.35):
   a=anchor(id,bars=32);a[9:13]=[swing,num,den,1];base=run('after',a)[0];ledger(events(base))
   assert base==run('after',a)[0];a[3]=127;assert base==run('after',a)[0],('blocks',a)
   controls.append(a)
for path in (11,12):
 a=[3,path,3,512,128,0,3];base=run('after',a)[0];ledger(events(base));assert base==run('after',a)[0];a[3]=127;assert base==run('after',a)[0],('dynamic blocks',a);controls.append(a)
# Host 100 BPM, 960 PPQ, original channel routing, one SMF track per output.
def vlq(n):
 b=[n&127];n>>=7
 while n:b.insert(0,(n&127)|128);n>>=7
 return bytes(b)
def midi(raw):
 tracks=[b'\0\xff\x51\x03\x09\x27\xc0\0\xff\x58\x04\x04\x02\x18\x08']
 for output in range(9):
  data=bytearray();last=0
  for sample,o,ch,n,v,k in events(raw):
   if o!=output:continue
   tick=round(sample/30);data+=vlq(tick-last)+bytes([(0xb0 if k else 0x90)+ch-1,n,v]);last=tick
  tracks.append(bytes(data))
 return b'MThd'+struct.pack('>IHHH',6,1,10,960)+b''.join(b'MTrk'+struct.pack('>I',len(t)+4)+t+b'\0\xff\x2f\0'for t in tracks)
dest=ROOT/'docs/research/john-williams'
with zipfile.ZipFile(dest/'INDEPENDENT_PEDALS_AB.zip','w',zipfile.ZIP_DEFLATED)as z:
 z.writestr('README.txt','A/B aus tatsächlicher Engine-Ausgabe, 100 BPM, D, 4/4, 960 PPQ. A = 1d3c1d5, B = unabhängiges Einzelpedal. Gleiche Instrumente/Kanäle verwenden. Keine Quantisierung. Je 128 Takte.\nStandardkanäle: 1 Harmonie lang, 2 Harmonie kurz, 3 Bass lang, 4 Bass kurz, 5 Arpeggio, 6 Tupfer, 7 Stich, 8 Dialog, 9 Melodie.\nZunächst Bass-Lang allein vergleichen, danach das vollständige Arrangement. Ein 16-Takt-Pedal dauert bei 100 BPM 38,4 Sekunden; keine kurzen Acht-Takt-Ausschnitte beurteilen.\n')
 for id in (40003,40050,40061):
  args=anchor(id)
  for label,name in [('before','A'),('after','B')]:z.writestr(f'JW-H{id-40000:02}_{name}.mid',midi(run(label,args)[0]))
summary=dict(source_sha256={name:hashlib.sha256((ROOT/'Source'/name).read_bytes()).hexdigest() for name in ('ScoreEngine.h','CompositionPolicy.h','PedalPlan.h')},baseline='1d3c1d5',cases=len(results),byte_equal=sum(r['byte_equal']for r in results),changed=sum(not r['byte_equal']for r in results),transport_controls=len(controls),results=results)
(dest/'INDEPENDENT_PEDALS_RESULTS.json').write_text(json.dumps(summary,indent=2)+'\n')
print('PASS',summary['cases'],'A/B,',summary['changed'],'intentional bass changes;',len(controls),'transport/block cases',flush=True)
