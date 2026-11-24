#!/usr/bin/env python3
"""Audit realized colour, population and spacing against the pinned MIDI generator."""
from reference_headers import header_snapshot
import argparse,collections,hashlib,json,pathlib,struct,subprocess,tempfile
p=argparse.ArgumentParser();p.add_argument('--probe',required=True);p.add_argument('--compiler',default='c++');p.add_argument('--output',required=True);a=p.parse_args();root=pathlib.Path(__file__).resolve().parents[1];out=pathlib.Path(a.output);out.mkdir(parents=True,exist_ok=True)
names=[str(2001+i)+'-auto' for i in range(36)]+['custom-'+str(i) for i in range(18)]+['manual-held','manual-stabs','pad-follow-off','bass-follow-off','both-follow-off','bass-muted','shared-pad-channel','narrow','buildup','scene-end','protected-line','score-neutral','score-barry','score-herrmann','high','low','full-natural','full-open','lean-natural','lean-open','stable-root','stable-bass-follow-off','slash-bass','unavailable-bass-root','manual-gated','manual-pulse','manual-staccato']
def run(exe,case,bpm,block=512,key=0,enabled=True):
 r=subprocess.run([str(exe),str(case),str(block),str(bpm),str(key),str(int(enabled))],capture_output=True,check=True)
 return r.stdout,[tuple(map(int,l.split(b','))) for l in r.stdout.splitlines()],[list(map(int,l[2:].split(b','))) for l in r.stderr.splitlines() if l.startswith(b'D,')]
def tick(e,bpm):return round(e[0]*bpm/(48000*60)*4)
def spans(es):
 active={}
 for e in es:
  if e[4]:continue
  k=e[1:3]
  if e[3]:assert k not in active,('double',e);active[k]=e
  else:assert k in active,('orphan',e);active.pop(k)
 assert not active

def pad_states(es,bpm):
 active=set();bytick={};bytime={}
 for e in es:
  if e[4] or e[5]>1:continue
  k=(e[5],e[2]);active.add(k) if e[3] else active.discard(k)
  bytick[tick(e,bpm)]=sorted(n for _,n in active);bytime[e[0]]=sorted(n for _,n in active)
 return bytick,bytime

def statistics(es,bpm):
 _,bytime=pad_states(es,bpm);counts=collections.Counter();widths=collections.Counter();dups=collections.Counter();previous=[];movements=[];last=0;current=[]
 for at,ns in sorted(bytime.items()):
  duration=at-last;counts[len(current)]+=duration
  if current:widths[current[-1]-current[0]]+=duration;dups[len(current)-len({n%12 for n in current})]+=duration
  if ns and ns!=current:
   if previous:movements += [min(abs(n-m) for m in previous) for n in ns]
   previous=ns
  current=ns;last=at
 total=sum(counts.values()) or 1;sounding=sum(widths.values()) or 1
 return {'pad_attacks':sum(e[5]<2 and not e[4] and bool(e[3]) for e in es),'maximum_polyphony':max(counts,default=0),'time_fraction_by_polyphony':{str(n):v/total for n,v in sorted(counts.items())},'mean_sounding_span':sum(n*v for n,v in widths.items())/sounding,'time_fraction_by_span':{str(n):v/sounding for n,v in sorted(widths.items())},'mean_pitch_class_duplicates':sum(n*v for n,v in dups.items())/sounding,'nearest_motion_mean':sum(movements)/max(1,len(movements)),'max_nearest_motion':max(movements,default=0)}

def midi(path,es,bpm):
 def vlq(n):
  v=[n&127];n>>=7
  while n:v.insert(0,(n&127)|128);n>>=7
  return bytes(v)
 tr=bytearray(b'\0\xff\x51\x03'+round(60000000/bpm).to_bytes(3,'big'));previous=0
 for at,ch,n,v,typ,o in es:
  at=round(at*bpm/(48000*60)*960);tr+=vlq(at-previous)+bytes([(0xb0 if typ else 0x90 if v else 0x80)+ch-1,n,v]);previous=at
 tr+=b'\0\xff\x2f\0';path.write_bytes(b'MThd'+struct.pack('>IHHH',6,0,1,960)+b'MTrk'+struct.pack('>I',len(tr))+tr)
rows=[];examples=[];changed=0;openings=0;reductions=0
with tempfile.TemporaryDirectory() as tmp:
 tmp=pathlib.Path(tmp)
 for name,data in header_snapshot(root,'2a7e55d').items():(tmp/name).write_bytes(data)
 old=tmp/'before';subprocess.run([a.compiler,'-std=c++17','-O2','-I',str(tmp),str(root/'tools/chord_disposition_probe.cpp'),'-o',str(old)],check=True)
 for case,name in enumerate(names):
  for bpm in (90,120,173):
   br,b,_=run(old,case,bpm);control,_,_=run(a.probe,case,bpm,enabled=False);raw,es,ds=run(a.probe,case,bpm)
   assert control==br,('disabled regression',name,bpm);spans(b);spans(es)
   assert sorted(e for e in es if e[5]>1)==sorted(e for e in b if e[5]>1),('other voices changed',name,bpm)
   assert [e for e in es if e[5] in (2,3)]==[e for e in b if e[5] in (2,3)],('bass changed',name,bpm)
   assert [e for e in es if e[5]>1 and (e[3] or e[4])]==[e for e in b if e[5]>1 and (e[3] or e[4])],('other attacks changed',name,bpm)
   protected=case in [54,55,60,61,62,63,64,65,66,67,70,78,79,80]
   if protected:assert raw==br,('protected regression',name,bpm)
   old_states,_=pad_states(b,bpm);states,_=pad_states(es,bpm)
   for d in ds:
    at,pop,spacing,mask,required,omitted,bass,count=d[:8];ns=d[8:];assert len(ns)==count
    actual=0
    for n in ns:actual|=1<<(n%12)
    assert actual==mask&~omitted and actual&required==required,('colour lost',name,d)
    if spacing:assert 19<=ns[-1]-ns[0]<=30;openings+=1
    if omitted:reductions+=1
    assert set(ns)<=set(states[at]),('planned vs played',name,bpm,d,states.get(at))
    if bpm==120 and case in [36,38,42,45,47,48,53,71,73,74,75,76] and len([e for e in examples if e['case']==name])<8:
     previous=next((old_states[t] for t in sorted(old_states,reverse=True) if t<=at),[])
     if not any(e['case']==name and e['population']==pop and e['spacing']==spacing and e['before']==previous and e['after']==ns for e in examples):
      examples.append({'case':name,'tick':at,'population':pop,'spacing':spacing,'chord_mask':mask,'required':required,'omitted':omitted,'bass_covers_root':bool(bass),'before':previous,'after':ns})
   for block in (127,8192):
    rr,ee,dd=run(a.probe,case,bpm,block);assert dd==ds and len(ee)==len(es),('block shape',name,bpm,block)
    assert all(x[1:]==y[1:] and abs(x[0]-y[0])<=1 for x,y in zip(ee,es)),('block dependence',name,bpm,block)
   if bpm==120:
    repeat,_,dd=run(a.probe,case,bpm);assert repeat==raw and dd==ds,('nondeterminism',name)
    midi(out/(name+'-before.mid'),b,bpm);midi(out/(name+'-after.mid'),es,bpm)
   changed+=raw!=br
   rows.append({'case':name,'bpm':bpm,'changed':raw!=br,'accepted_realizations':len(ds),'modes':dict(collections.Counter(str(d[1])+','+str(d[2]) for d in ds)),'omissions':sum(d[5]!=0 for d in ds),'bass_root_substitutions':sum(d[6] and d[5]!=0 for d in ds),'before':statistics(b,bpm),'after':statistics(es,bpm),'before_sha256':hashlib.sha256(br).hexdigest(),'after_sha256':hashlib.sha256(raw).hexdigest()})
 # Actual adapter MIDI in twelve transpositions, beyond the all-shape unit test.
 for key in range(12):
  for case in (36,38,41,46,53,76):
   _,es,ds=run(a.probe,case,120,key=key);spans(es);assert ds,(key,case,'no realization')
   _,baseline,_=run(old,case,120,key=key)
   assert sorted(e for e in es if e[5]>1)==sorted(e for e in baseline if e[5]>1),('transposed other voices',key,case)
   assert [e for e in es if e[5] in (2,3)]==[e for e in baseline if e[5] in (2,3)],('transposed bass',key,case)
   for d in ds:
    mask=0
    for n in d[8:]:mask|=1<<(n%12)
    assert mask==d[3]&~d[5] and mask&d[4]==d[4]
assert changed and openings and reductions
(out/'summary.json').write_text(json.dumps({'baseline':'2a7e55d','bars':128,'cases':len(rows),'changed_cases':changed,'accepted_open_realizations':openings,'realizations_with_omissions':reductions,'results':rows,'examples':examples},indent=2)+'\n')
print(len(rows),'128-bar A/B cases;',2*len(rows),'block comparisons; 72 transposed adapter renderings;',changed,'changed cases;',openings,'open realizations;',reductions,'realizations with omissions')
