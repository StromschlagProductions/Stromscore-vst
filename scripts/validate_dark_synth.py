"""Reproducible real-generator production atlas, byte regressions and listening SMFs.
Usage: python scripts/validate_dark_synth.py /tmp/ds-p2
Binaries 'before' (eb32983 headers) and diagnostic 'current' are built externally.
"""
from pathlib import Path
import subprocess,json,hashlib,collections,concurrent.futures,csv,zipfile,struct,sys,time
ROOT=Path(__file__).resolve().parents[1];OUT=Path(sys.argv[1]);F=ROOT/'docs/research/dark-synth';CACHE=OUT/'render-cache';CACHE.mkdir(exist_ok=True)
sha={x:hashlib.sha256((OUT/x).read_bytes()).hexdigest()for x in ('before','current')}
def args(p=5,path=13,mode=3,block=512,bars=64,genre=0,v=3,manual=0,follow=1,swing=0,num=4,den=4,jumps=0,key=2,seed=0,bpm=100,mask=0,xyz=(.5,.5,.5),routing=0,variety=.5):
 return [p,path,mode,block,bars,genre,v,manual,follow,swing,num,den,jumps,0,0,key,seed,bpm,mask,0,*xyz,routing,variety]
def run(label,a):
 key=hashlib.sha256(json.dumps([sha[label],a]).encode()).hexdigest();p=CACHE/key
 if not p.with_suffix('.csv').exists():
  begin=time.perf_counter();r=subprocess.run([str(OUT/label),*map(str,a)],capture_output=True,check=True);p.with_suffix('.csv').write_bytes(r.stdout);p.with_suffix('.trace').write_bytes(r.stderr);p.with_suffix('.time').write_text(str(time.perf_counter()-begin))
 return p.with_suffix('.csv').read_bytes(),p.with_suffix('.trace').read_bytes(),float(p.with_suffix('.time').read_text())
def ledger(raw):
 active={};spans=[]
 for line in raw.splitlines():
  at,o,ch,n,v,kind=map(int,line.split(b','))
  if kind:continue
  if v:assert (ch,n)not in active,('duplicate',at,o,ch,n);active[ch,n]=(at,o,v)
  else:
   assert(ch,n)in active,('orphan',at,o,ch,n);begin,output,vel=active.pop((ch,n));assert at>begin,('zero',at,o,ch,n);spans.append((begin,at,output,ch,n,vel))
 assert not active,active
 return spans

def analyze(a):
 raw,trace,elapsed=run('current',a);spans=ledger(raw);used=collections.Counter();admitted=set();h=[];memory=[];operations=collections.Counter();operation_events=set();physical=collections.defaultdict(collections.Counter);precise=b'C,'in trace
 for l in trace.decode().splitlines():
  row=l.split(',')
  if row[0]=='H':h.append([int(row[1]),int(row[2])])
  if row[0]=='Q' and not precise:used[row[3]]+=1
  if row[0]=='C':physical[row[2]][row[4]]+=1
  if row[0]=='C'and int(row[3]):
   n=int(row[3]);prefix,number=('JC-Q',n-1000)if 1000<n<2000 else('JC-B',n-2000)if 2000<n<3000 else('JC-M',n-3000)if 3000<n<4000 else('DS-Q',n-4000)if 4000<n<4100 else('DS-B',n-4100)if 4100<n<4200 else('DS-TU',n-4200)if 4200<n<4300 else('DS-TO',n-4300)if 4300<n<4400 else('DS-HM',n-4400)
   used[prefix+str(number).zfill(3 if prefix.startswith('JC')else 2)]+=1
  if row[0]=='E':
   n=int(row[3]);id='JC-M004'if n==3004 else('DS-TU'+str(n-4200).zfill(2))if 4200<n<4300 else('DS-TO'+str(n-4300).zfill(2))if 4300<n<4400 else('DS-HM'+str(n-4400).zfill(2));
   if not precise:used[id]+=1
   memory.append(row[1:])
   if len(row)>11:operations[row[9]]+=1;operation_events.add((row[9],row[10],row[3]))
  if row[0]=='J':admitted.add(row[3])
 counts=collections.Counter(s[2]for s in spans);gates={};activebars={};longest={}
 total=a[4]*a[10]*4/a[11]*(48000*60/a[17]);bar=(a[10]*4/a[11])*(48000*60/a[17])
 for output in range(9):
  intervals=sorted((b,e)for b,e,o,ch,n,v in spans if o==output);merged=[]
  for b,e in intervals:
   if merged and b<=merged[-1][1]:merged[-1][1]=max(e,merged[-1][1])
   else:merged.append([b,e])
  gates[output]=sum(e-b for b,e in merged)/total;activebars[output]=len({i for b,e in merged for i in range(int(b//bar),int((e-1)//bar)+1)});longest[output]=max((e-b for b,e in merged),default=0)/bar
 return dict(args=a,sha256=hashlib.sha256(raw).hexdigest(),render_seconds=elapsed,note_ons=dict(counts),gate_fraction=gates,active_bars=activebars,longest_sounding_bars=longest,harmonies=h,source_note_ons=dict(used),harmony_note_ons={k:dict(v)for k,v in physical.items()},admitted=sorted(admitted),tu_examples=[list(s)for s in spans if s[2]==5][:24],motif_trace=memory[:32],operation_note_ons=dict(operations),operation_events=[list(x)for x in sorted(operation_events)])

def regression(a):
 before=run('before',a)[0];after=run('current',a)[0];assert before==after,('outside-profile regression',a);ledger(after);return dict(args=a,sha256=hashlib.sha256(after).hexdigest())
oldprof=json.loads(subprocess.check_output(['git','show','eb32983:data/harmony/profiles.json'],cwd=ROOT))['profiles'];oldcatalog=json.loads(subprocess.check_output(['git','show','eb32983:data/harmony/catalog.json'],cwd=ROOT))
cases=[]
for p in range(6):
 for g in range(2):
  if p==5 and g==0:continue
  for path in range(13):cases.append(args(p=p,path=path,genre=g,bars=16))
  pool=oldcatalog['pools']['pop_rock']if g else oldprof[p].get('score_pool',oldcatalog['pools']['score'])
  for i in range(len(pool)):cases.append(args(p=p,path=100+i,genre=g,bars=8))
with concurrent.futures.ThreadPoolExecutor(max_workers=2)as ex:reg=list(ex.map(regression,cases))
print('Outside-profile byte regressions',len(reg),flush=True)
# Actual musical generation on a 7^3 field, three variety/seed combinations.
coords=[0,.1,.25,.5,.75,.9,1];atlas=[args(xyz=(x,y,z),variety=variety,v=v,seed=v*13)for x in coords for y in coords for z in coords for variety,v in [(0,1),(.5,7),(1,13)]]
with concurrent.futures.ThreadPoolExecutor(max_workers=2)as ex:
 records=[]
 for i,r in enumerate(ex.map(analyze,atlas)):
  records.append(r)
  if i%100==0:print('Production atlas',i,'/',len(atlas),flush=True)
# Longer static/path studies, solos and manual controls; generated without catalog forcing.
named=[('01-warm-pulseless',(.85,.2,.15),0,(1<<2)|(1<<4),13),('02-shadow-rotation',(.5,.35,.25),0,(1<<2)|(1<<4),13),('03-two-periods',(.4,.65,.45),3,0,13),('04-ritual',(.15,.85,.15),0,0,13),('05-high-unrest',(.2,.8,.9),3,0,13),('06-bright-unease',(.85,.2,.8),0,(1<<2)|(1<<4),13),('07-slow-xyz',(.5,.5,.5),3,0,11),('08-fast-xyz',(.5,.5,.5),3,0,12),('09-TU-alone',(.55,.4,.3),0,(1<<0)|(1<<1)|(1<<2)|(1<<4),13)]
hearing=[];midi_files={}
def vlq(n):
 b=[n&127];n>>=7
 while n:b.insert(0,(n&127)|128);n>>=7
 return bytes(b)
def smf(raw,bars=128,bpm=100):
 tracks=[];es=collections.defaultdict(list)
 for line in raw.splitlines():
  at,o,ch,n,v,k=map(int,line.split(b','));tick=round(at*960/(48000*60/bpm));es[o].append((tick,bytes([(176 if k else 144 if v else 128)+ch-1,n,v])))
 for o,name in enumerate(['LF','KF','LB','KB','AR','TU','ST','GS','HM']):
  tr=bytearray(b'\x00\xff\x03'+bytes([len(name)])+name.encode());last=0
  if o==0:tr+=b'\x00\xff\x51\x03'+int(60e6/bpm).to_bytes(3,'big')
  for tick,message in es[o]:tr+=vlq(tick-last)+message;last=tick
  tr+=vlq(max(0,bars*3840-last))+b'\xff\x2f\x00';tracks.append(bytes(tr))
 return b'MThd'+struct.pack('>IHHH',6,1,9,960)+b''.join(b'MTrk'+struct.pack('>I',len(t))+t for t in tracks)
for name,xyz,mode,mask,path in named:
 a=args(xyz=xyz,mode=mode,mask=mask,path=path,bars=128);r=analyze(a);r['name']=name;hearing.append(r)
 raw=run('current',a)[0];other=a.copy();other[3]=127;assert raw==run('current',other)[0],('block',name)
 for label in ['before','current']:midi_files[name+'-'+('P1-Carpenter'if label=='before'else'P2-Dark-Synth')+'.mid']=smf(run(label,a)[0])
# Real ranges/transpose/full transport, including odd meters and shared bass channels.
transport=[]
for key in range(12):
 for num,den in [(4,4),(3,8),(5,8),(7,8)]:
  a=args(key=key,num=num,den=den,swing=.6,jumps=1,bars=16,routing=5);raw=run('current',a)[0];ledger(raw);b=a.copy();b[3]=2048;assert raw==run('current',b)[0],('transport',a);transport.append(a)
for manual,follow in [(1,1),(0,0)]:
 a=args(manual=manual,follow=follow,bars=32);ledger(run('current',a)[0]);transport.append(a)
used=collections.Counter();admitted=set();selected=set()
for r in records+hearing:used.update(r['source_note_ons']);admitted.update(r['admitted']);selected.update(id for at,id in r['harmonies'])
result=dict(base='eb32983',regression_count=len(reg),byte_regressions=reg,atlas=records,hearing=hearing,transport=transport,source_note_counts=dict(used),selected_harmony_ids=sorted(selected),admitted_sources=sorted(admitted),note='Sources counted only from automatic production; selection/admission is distinct from physical note-on provenance. One-sample host rounding at non-integral tempos is tested separately.')
(F/'P2_RENDER_RESULTS.json').write_text(json.dumps(result,ensure_ascii=False,separators=(',',':'))+'\n',encoding='utf-8')
with zipfile.ZipFile(F/'P2_MIDI_LISTENING.zip','w',zipfile.ZIP_DEFLATED)as z:
 for name,content in midi_files.items():z.writestr(name,content)
 z.writestr('README.txt','Tatsaechliche Generator-Ausgabe, 128 Takte, D, 100 BPM, neun getrennte MIDI-Spuren. P1-Carpenter = eb32983; P2-Dark-Synth = neuer Produktionspfad. Keine Forschungstranskriptionen. TU-alone: AR/GS/HM und Harmonie/Bass gemutet. Klang und Balance in Studio One frei waehlen. Musikalische Qualitaet braucht Hoerabnahme.\n')
print('Done:',len(records),'atlas cases,',len(selected),'selected harmonies,',len(used),'played source figures; 18 MIDI comparisons',flush=True)
