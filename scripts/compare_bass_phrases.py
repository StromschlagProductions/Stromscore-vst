#!/usr/bin/env python3
from reference_headers import header_snapshot
import argparse,collections,hashlib,json,math,pathlib,struct,subprocess,tempfile
p=argparse.ArgumentParser();p.add_argument('--probe',required=True);p.add_argument('--compiler',default='c++');p.add_argument('--output',required=True);a=p.parse_args();root=pathlib.Path(__file__).resolve().parents[1];out=pathlib.Path(a.output);out.mkdir(parents=True,exist_ok=True)
ids=[2015,2019,2012,2025,2030,2031,2032,2035,2013,2028,2021]
names=[str(i)+'-auto-follow' for i in ids]+[str(i)+'-follow-off' for i in ids[:7]]+['manual-funk','pedal','high-simple','manual-eighth','narrow','buildup','shared-channel','manual-held','passing-chords','live-intensity-latch','manual-pulse','score-control']
def run(exe,case,bpm,block=512,key=0,disable=False):
 r=subprocess.run([str(exe),str(case),str(block),str(bpm),str(key)]+(['0'] if disable else []),capture_output=True,check=True)
 es=[tuple(map(int,l.split(b','))) for l in r.stdout.splitlines()];plans=[list(map(int,l[2:].split(b','))) for l in r.stderr.splitlines() if l.startswith(b'P,')];return r.stdout,es,plans

def spans(es):
 active={};ss=[]
 for e in es:
  if e[4]:continue
  key=e[1:3]
  if e[3]:assert key not in active,('double',e);active[key]=e
  else:assert key in active,('orphan',e);ss.append((active.pop(key),e[0]))
 assert not active
 return ss

def midi(path,es,bpm):
 def vlq(n):
  d=[n&127];n>>=7
  while n:d.insert(0,(n&127)|128);n>>=7
  return bytes(d)
 tr=bytearray(b'\x00\xff\x51\x03'+round(60000000/bpm).to_bytes(3,'big'));prev=0
 for at,ch,n,v,t,o in es:
  tick=round(at*bpm/(48000*60)*960);tr+=vlq(tick-prev)+bytes([(0xb0 if t else 0x90 if v else 0x80)+ch-1,n,v]);prev=tick
 tr+=b'\x00\xff\x2f\x00';path.write_bytes(b'MThd'+struct.pack('>IHHH',6,0,1,960)+b'MTrk'+struct.pack('>I',len(tr))+tr)
def bassons(es):return [e for e in es if not e[4] and e[3]>0 and e[5] in (2,3)]
def distribution(es):
 ns=bassons(es);return dict(collections.Counter(abs(b[2]-c[2]) for b,c in zip(ns,ns[1:])))
rows=[];examples=[];passings=0;line_count=0
with tempfile.TemporaryDirectory() as tmp:
 tmp=pathlib.Path(tmp)
 for name,data in header_snapshot(root,'888ff82').items():(tmp/name).write_bytes(data)
 old=tmp/'before';subprocess.run([a.compiler,'-std=c++17','-O2','-I',str(tmp),str(root/'tools/bass_phrase_probe.cpp'),'-o',str(old)],check=True)
 for case,name in enumerate(names):
  for bpm in (90,120,173):
   br,b,_=run(old,case,bpm);cr,c,_=run(a.probe,case,bpm,disable=True);ar,es,plans=run(a.probe,case,bpm)
   assert cr==br,('baseline changed',name,bpm);oldspans=spans(b);ss=spans(es)
   assert [e for e in es if e[5] not in (2,3)]==[e for e in b if e[5] not in (2,3)],('unrelated output',name,bpm)
   protected=case not in (3,7,8,9,27)
   if protected:assert ar==br and not plans,('protected bass changed',name,bpm)
   if case!=27:assert [(e[0],e[3],e[5]) for e in bassons(es)]==[(e[0],e[3],e[5]) for e in bassons(b)],('density/rhythm/expression changed',name,bpm)
   if case!=27:
    assert [(n[0],end-n[0],n[3],n[5]) for n,end in ss if n[5] in (2,3)]==[(n[0],end-n[0],n[3],n[5]) for n,end in oldspans if n[5] in (2,3)],('bass durations changed',name,bpm)
   for block in (127,8192):
    raw,ee,pp=run(a.probe,case,bpm,block);assert pp==plans and len(ee)==len(es) and all(x[1:]==y[1:] and abs(x[0]-y[0])<=(1 if bpm==173 else 0) for x,y in zip(ee,es)),('block drift',name,bpm,block)
   resolved=0
   for plan in plans:
    begin,middle,end,count=plan[:4];notes=[plan[4+i*7:11+i*7] for i in range(count)];line_count+=1
    ns=[e for e in bassons(es) if begin-.001<=e[0]*bpm/(48000*60)*4<end-.001]
    assert len(ns)==count,(name,bpm,'missing attacks',plan,ns)
    for i,(event,note) in enumerate(zip(ns,notes)):
     at,pitch,length,accent,passing,anchor,target=note;step=event[0]*bpm/(48000*60)*4
     assert abs(step-at)<.21 and event[2]==pitch
     release=next(t for n,t in ss if n==event);assert release>event[0]
     if i+1<count:assert release<=ns[i+1][0]+1,('bass not monophonic',name,note,event,release)
     if anchor:
      oldon=next(e for e in bassons(b) if abs(e[0]-event[0])<=1);assert oldon[2]%12==pitch%12,('bass class/slash changed',name,note,oldon)
     if passing:
      resolved+=1;passings+=1;assert target==i+1 and 1<=abs(pitch-notes[i-1][1])<=2 and 1<=abs(notes[target][1]-pitch)<=2
      assert (pitch-notes[i-1][1])*(notes[target][1]-pitch)>0
      assert notes[target][0]-at<=2 and release<=ns[target][0]+1
    if bpm==120 and len([e for e in examples if e['case']==name])<1:examples.append({'case':name,'plan':plan,'actual_ons':ns})
   rows.append({'case':name,'bpm':bpm,'plans':len(plans),'planned_attacks':sum(p[3] for p in plans),'melodic_attack_fraction':sum(p[3] for p in plans)/len(bassons(es)),'passing_tones':resolved,'note_ons_before':len(bassons(b)),'note_ons_after':len(bassons(es)),'intervals_before':distribution(b),'intervals_after':distribution(es),'register_before':[min(e[2] for e in bassons(b)),max(e[2] for e in bassons(b))],'register_after':[min(e[2] for e in bassons(es)),max(e[2] for e in bassons(es))],'before_sha256':hashlib.sha256(br).hexdigest(),'after_sha256':hashlib.sha256(ar).hexdigest()})
   if bpm==120:midi(out/f'{name}-before.mid',b,bpm);midi(out/f'{name}-after.mid',es,bpm)
 # Real adapter transposition controls, not just abstract modal masks.
 for key in range(12):
  for case in (3,7):
   raw,es,plans=run(a.probe,case,120,key=key);spans(es);assert plans,(case,key,'no real transposed phrase')
assert line_count>0 and passings>0
(out/'summary.json').write_text(json.dumps({'baseline':'888ff82','bars':128,'plans':line_count,'passing_tones':passings,'results':rows,'examples':examples},indent=2)+'\n');print(len(rows),'128-bar A/B cases;',len(rows)*2,'block comparisons; 24 transposed adapter renders;',line_count,'phrases;',passings,'resolved passing tones')
