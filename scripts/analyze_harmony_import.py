"""Pinned-catalog MIDI regression and real-selection before/after diagnostics. No production edits."""
import argparse,collections,csv,hashlib,importlib.util,itertools,json,math,pathlib,struct,subprocess,sys,tempfile
root=pathlib.Path(__file__).resolve().parents[1];sys.path.insert(0,str(root/'Tests'))
from HarmonyImportFixtures import prepare
from transport_regression import assert_chase_delta
from role_regression import assert_score_role_delta
p=argparse.ArgumentParser();p.add_argument('--probe',required=True);p.add_argument('--compiler',default='c++');p.add_argument('--output',required=True);a=p.parse_args();out=pathlib.Path(a.output);out.mkdir(parents=True,exist_ok=True)
cat=json.loads((root/'data/harmony/catalog.json').read_text());entries={t['id']:t for t in cat['templates']};shapes={t['id']:t['intervals'] for t in json.loads((root/'data/harmony/chord_types.json').read_text())['types']}
def run(exe,id,key=0,x=None,y=None,z=None,follow=1,manual=0,melody=0,dialog=0,bars=8,block=512,bpm=120,route=0,profile=0,swing=0,genre=1):
 t=entries.get(id,entries[2037]);xyz=t['xyz'];args=[id,key,xyz[0] if x is None else x,xyz[1] if y is None else y,xyz[2] if z is None else z,follow,manual,melody,dialog,bars,block,bpm,route,profile,swing,genre]
 return subprocess.check_output([str(exe)]+list(map(str,args)))
def events(raw):return [tuple(map(int,r.split(b','))) for r in raw.splitlines()]
def balance(es):
 held={}
 for at,o,ch,n,v,t in es:
  if t:continue
  k=(ch,n)
  if v:assert k not in held,('double',at,k);held[k]=o
  else:assert k in held,('orphan',at,k);del held[k]
 assert not held

def mask(c,key):return sum(1<<n for n in {(key+c['root']+i)%12 for i in shapes[c['type']]})
def at_chord(t,tick):
 b=(tick//16)%8
 for c in t['chords']:
  if b<c['bars']:return c
  b-=c['bars']
 raise AssertionError('timeline')
def audit(raw,id,key,follow,manual,bpm=120):
 es=events(raw);balance(es);t=entries[id];spq=48000*60/bpm;classes=collections.defaultdict(set);nct=collections.Counter();slots=[];start=0
 for c in t['chords']:slots.append({'bar':start,'root':c['root'],'type':c['type'],'bass':c['bass'],'expected_mask':mask(c,key)});start+=c['bars']
 for at,o,ch,n,v,typ in es:
  if typ or not v:continue
  tick=round(at/spq*4);c=at_chord(t,tick) if follow else t['chords'][0];pc=n%12;classes[str(o)].add(pc)
  if o in (0,1,4):assert mask(c,key)&(1<<pc),('extra harmony',id,key,at,o,n,c)
  elif o in (2,3) and manual:assert pc==(key+(c['bass'] if follow else 0))%12,('bass',id,at,n,c)
  elif o in (7,8) and not(mask(at_chord(t,tick),key)&(1<<pc)):nct[str(o)]+=1
 # Held pad (with all voices disabled) must switch exactly at every authored slot boundary.
 if manual:
  starts={round(e[0]/spq*4) for e in es if e[1]==0 and e[4]>0 and e[5]==0}
  if follow:
   for slot in slots:assert slot['bar']*16 in starts,('missing boundary',id,slot,sorted(starts))
 # First-cycle sounding classes include notes held across a slot boundary, not just attacks.
 sounding=[{'pad':set(),'arp':set(),'bass':set(),'dialog':set(),'melody':set()} for _ in slots];held={}
 for at,o,ch,n,v,typ in es:
  if typ:continue
  token=(ch,n)
  if v:held[token]=(at,o)
  else:
   begin,owner=held.pop(token);group='pad' if owner in (0,1) else 'bass' if owner in (2,3) else 'arp' if owner==4 else 'dialog' if owner==7 else 'melody' if owner==8 else None
   if group:
    for j,slot in enumerate(slots):
     endbar=slots[j+1]['bar'] if j+1<len(slots) else 8
     if begin<endbar*4*spq and at>slot['bar']*4*spq:sounding[j][group].add(n%12)
 for j,slot in enumerate(slots):slot['actual_sounding_classes']={k:sorted(v) for k,v in sounding[j].items()};slot['expected_sounding_mask']=slot['expected_mask'] if follow else mask(t['chords'][0],key)
 return {'outputs_pitch_classes':{k:sorted(v) for k,v in classes.items()},'melodic_nonchord_attacks':dict(nct),'slot_boundaries':slots,'events':len(es)}
def midi(path,es,bpm=120):
 def vlq(n):
  assert n>=0
  v=[n&127];n>>=7
  while n:v.insert(0,(n&127)|128);n>>=7
  return bytes(v)
 tracks=[]
 for output in range(9):
  track=bytearray(b'\0\xff\x51\x03'+round(60000000/bpm).to_bytes(3,'big'));last=0
  for at,o,ch,n,v,t in es:
   if o!=output:continue
   tick=round(at*bpm/(48000*60)*960);track+=vlq(tick-last)+bytes([(0xb0 if t else 0x90 if v else 0x80)+ch-1,n,v]);last=tick
  track+=b'\0\xff\x2f\0';tracks.append(b'MTrk'+len(track).to_bytes(4,'big')+track)
 path.write_bytes(b'MThd'+struct.pack('>IHHH',6,1,len(tracks),960)+b''.join(tracks))

with tempfile.TemporaryDirectory() as tmp:
 tmp=pathlib.Path(tmp);prepare(tmp/'before',revision='e1b1de4',explicit=True);old=tmp/'before-probe'
 subprocess.run([a.compiler,'-std=c++17','-O2','-I',str(tmp/'before'),str(root/'tools/harmony_import_probe.cpp'),'-o',str(old)],check=True)
 regression=[]
 for id in list(range(1001,1049))+list(range(2001,2037)):
  for profile in range(3):
   for route in range(2):
    kw=dict(profile=profile,route=route,bars=32,melody=1,dialog=1,swing=.2,genre=0 if id<2000 else 1)
    before=run(old,id,**kw);after=run(a.probe,id,**kw)
    if id<2000:assert_score_role_delta(before,after,(768000,1536000,2304000) if route else (),layout='import')
    elif route:assert_chase_delta(before,after,(768000,1536000,2304000),layout='import')
    else:assert before==after,('explicit old MIDI changed',id,profile,route)
    regression.append({'id':id,'profile':profile,'route':route,'byte_identical':before==after,'before_sha256':hashlib.sha256(before).hexdigest(),'sha256':hashlib.sha256(after).hexdigest(),'bytes':len(after)})
 samples=[];matrix=0
 for id in (2037,2038,2039):
  for key,z,y,follow,manual in itertools.product(range(12),(.1,.6,.95),(.25,.65,.95),(0,1),(0,1)):
   raw=run(a.probe,id,key=key,z=z,y=y,follow=follow,manual=manual)
   data=audit(raw,id,key,follow,manual);matrix+=1
   if key==0 and z==.95 and y==.65 and follow:samples.append({'id':id,'z':z,'y':y,'manual':manual,**data})
  for bars,melody,dialog in itertools.product((8,32,128),(0,1),(0,1)):
   kw=dict(bars=bars,melody=melody,dialog=dialog,manual=0)
   raw=run(a.probe,id,**kw);data=audit(raw,id,0,1,0);assert raw==run(a.probe,id,**kw)
   if bars==128:samples.append({'id':id,'bars':bars,'melody':melody,'dialog':dialog,**data})
  high=run(a.probe,id,z=.95,y=.8,bars=32,melody=1,dialog=1);samples.append({'id':id,'bars':32,'z':.95,'y':.8,'melody':1,'dialog':1,**audit(high,id,0,1,0)})
  assert run(a.probe,id,bars=32,melody=0,dialog=1)==run(a.probe,id,bars=32,melody=1,dialog=1),'Pop melody exclusion changed'
  for route,bpm,swing in itertools.product((0,1),(90,120,173),(0,.3)):
   kw=dict(bars=32,melody=1,dialog=1,bpm=bpm,route=route,swing=swing)
   raw=run(a.probe,id,**kw);reference=events(raw);balance(reference)
   for block in (127,480,8192):
    other=events(run(a.probe,id,block=block,**kw));assert len(other)==len(reference),(id,route,bpm,block,'size')
    assert all(x[1:]==y[1:] and abs(x[0]-y[0])<=1 for x,y in zip(other,reference)),(id,route,bpm,block,'blocks')
  for label,exe,forced in [('old-auto',old,0),('new-auto',a.probe,0),('new-explicit',a.probe,id)]:
   t=entries[id];raw=run(exe,forced,x=t['xyz'][0],y=t['xyz'][1],z=t['xyz'][2],bars=128,dialog=1)
   midi(out/(str(id)+'-'+label+'.mid'),events(raw))
 for label,exe in [('before',old),('after',a.probe)]:midi(out/('2015-regression-'+label+'.mid'),events(run(exe,2015,bars=32,dialog=1)))
 # Geometry is evaluated by the actual compiled candidates()/pick() functions in each version.
 before=subprocess.check_output([str(old),'--geometry']).decode().splitlines();after=subprocess.check_output([a.probe,'--geometry']).decode().splitlines();assert len(before)==len(after)==21**3*5
 def fingerprint(t):
  frames=[]
  for c in t['chords']:frames += [(c['root'],tuple(sorted((c['root']+i)%12 for i in shapes[c['type']])),c['root'] if c['bass'] is None else c['bass'])]*c['bars']
  return min(tuple(frames[i:]+frames[:i]) for i in range(8))
 families={id:fingerprint(t) for id,t in entries.items()};summary={};corners=[];displaced=collections.Counter()
 for name,lines in [('before',before),('after',after)]:
  acc=collections.defaultdict(list)
  for line in lines:
   row=line.split(',');ix,iy,iz=map(int,row[:3]);var=float(row[3]);ids=list(map(int,row[9:]));n,pickn=int(row[4]),int(row[5]);d,e=float(row[6]),float(row[7]);chosen=int(row[8]);f=len({families[i] for i in ids})
   absolute=math.sqrt(sum((entries[chosen]['xyz'][axis]-value/20)**2 for axis,value in enumerate((ix,iy,iz))))
   acc[var].append((n,pickn,d,e,f,chosen,absolute))
   if ix in (0,20) and iy in (0,20) and iz in (0,20):corners.append({'catalog':name,'xyz':[ix/20,iy/20,iz/20],'variety':var,'candidates':n,'pick_candidates':pickn,'families':f,'distance':d,'euclidean':e,'selected':chosen,'ids':ids,'selected_absolute_distance':absolute})
  summary[name]={str(v):{'points':len(rows),'mean_candidates':sum(r[0] for r in rows)/len(rows),'min_candidates':min(r[0] for r in rows),'single_candidate_points':sum(r[0]==1 for r in rows),'mean_families':sum(r[4] for r in rows)/len(rows),'mean_nearest_weighted_distance':sum(r[2] for r in rows)/len(rows),'max_nearest_weighted_distance':max(r[2] for r in rows),'mean_nearest_absolute_distance':sum(r[3] for r in rows)/len(rows),'max_nearest_absolute_distance':max(r[3] for r in rows),'mean_selected_absolute_distance':sum(r[6] for r in rows)/len(rows),'max_selected_absolute_distance':max(r[6] for r in rows)} for v,rows in acc.items()}
 for x,y in zip(before,after):
  b=x.split(',');c=y.split(',');v=b[3];removed=set(b[9:])-set(c[9:]);displaced[v]+=bool(removed)
 (out/'coverage.json').write_text(json.dumps({'grid':[21]*3,'variety':[0,.25,.5,.75,1],'sizes':[36,39],'summary':summary,'points_with_displaced_old_candidates':dict(displaced),'corners':corners},indent=2)+'\n')
 (out/'regression.json').write_text(json.dumps({'baseline':'e1b1de4','selection':'explicit ID; test-only seam in an otherwise unchanged header snapshot','renders':len(regression),'results':regression},indent=2)+'\n')
 (out/'musical-results.json').write_text(json.dumps({'matrix_renders':matrix,'samples':samples},indent=2)+'\n')
 print(len(regression),'byte-exact explicit regressions;',matrix,'8-bar new-template renders; 8/32/128-bar voices and transport tests passed')
