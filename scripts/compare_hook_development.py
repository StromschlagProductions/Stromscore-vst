#!/usr/bin/env python3
import argparse,collections,hashlib,json,math,pathlib,struct,subprocess,tempfile
p=argparse.ArgumentParser();p.add_argument('--probe',required=True);p.add_argument('--compiler',default='c++');p.add_argument('--output',required=True);a=p.parse_args();root=pathlib.Path(__file__).resolve().parents[1];out=pathlib.Path(a.output);out.mkdir(parents=True,exist_ok=True)
names=['pedal-ostinato','intense-melodic','quiet-melodic','lyrical','syncopated-melodic','dance-ostinato','XY-changes','held-harmony']
def run(exe,case,bpm,block=512,control=False):
 cmd=[str(exe),str(case),str(block),str(bpm)]+(['0'] if control else [])
 r=subprocess.run(cmd,capture_output=True,check=True);events=[tuple(map(int,l.split(b','))) for l in r.stdout.splitlines()];tr=collections.defaultdict(list,{k:[] for k in ('M','P')})
 for l in r.stderr.splitlines():tr[l[:1].decode()].append(list(map(int,l[2:].split(b','))))
 return r.stdout,events,tr

def midi(path,es,bpm):
 def vlq(n):
  d=[n&127];n>>=7
  while n:d.insert(0,(n&127)|128);n>>=7
  return bytes(d)
 track=bytearray(b'\x00\xff\x51\x03'+round(60000000/bpm).to_bytes(3,'big'));prev=0
 for sample,ch,n,v,kind,o in es:
  tick=round(sample*bpm/(48000*60)*960);track+=vlq(tick-prev)+bytes([(0xb0 if kind else 0x90 if v else 0x80)+ch-1,n,v]);prev=tick
 track+=b'\x00\xff\x2f\x00';path.write_bytes(b'MThd'+struct.pack('>IHHH',6,0,1,960)+b'MTrk'+struct.pack('>I',len(track))+track)
def active_bars(events,bpm):
 live={};bars=set()
 for e in events:
  if e[4] or e[5]!=7:continue
  key=e[1:3]
  if e[3]:live[key]=e[0]
  else:
   start=live.pop(key);first=int((start*bpm/(48000*60)*4+.001)//16);last=math.ceil((e[0]*bpm/(48000*60)*4-.001)/16)-1
   bars.update(range(first,last+1))
 return len(bars)
summary=[];examples=[];sequences=0
with tempfile.TemporaryDirectory() as tmp:
 tmp=pathlib.Path(tmp)
 for f in (root/'Source').glob('*.h'):(tmp/f.name).write_bytes(subprocess.check_output(['git','show','2566894:Source/'+f.name],cwd=root))
 old=tmp/'before';subprocess.run([a.compiler,'-std=c++17','-O2','-I',str(tmp),str(root/'tools/hook_development_probe.cpp'),'-o',str(old)],check=True)
 for case,name in enumerate(names):
  for bpm in (90,120,173):
   br,b,bh=run(old,case,bpm);ar,es,tr=run(a.probe,case,bpm);cr,c,ch=run(a.probe,case,bpm,control=True)
   assert cr==br,('disabled regression',name,bpm)
   assert tr['M']==bh['M'],('source altered',name,bpm)
   if case in (0,5):assert ar==br and not tr['P'],('groove interrupted',name,bpm)
   for block in (127,8192):
    rr,ee,tt=run(a.probe,case,bpm,block)
    assert tt==tr and len(ee)==len(es) and all(x[1:]==y[1:] and abs(x[0]-y[0])<=(1 if bpm==173 else 0) for x,y in zip(ee,es)),('block drift',name,bpm,block)
   live={};spans=[]
   for e in es:
    if e[4]:continue
    key=e[1:3]
    if e[3]:assert key not in live;live[key]=e
    else:assert key in live;spans.append((live.pop(key),e[0]))
   assert not live
   active=set();last_end=None;counts=collections.Counter();begins=[]
   for plan in tr['P']:
    begin,end,ordinal,kind,base,identity,count=plan[:7];assert kind in (0,3)
    notes=[plan[7+i*3:10+i*3] for i in range(count)]
    material=tr['M'][0];assert identity==material[0]
    cycle=16 if case==7 else 32
    original=[]
    for i in range(material[1]):
     at,length,interval=material[3+i*3:6+i*3];step=round(at/240);gate=max(1,min(round((at+length)/240)-step,cycle-step));original.append([step,gate,interval])
    expected=original
    if kind==3:
     period=original[2][0] if len(original)>2 else original[1][0]+original[1][1]
     expected=[n.copy() for n in original[:2]]+[[at+period,length,iv+7] for at,length,iv in original[:2]]
     for i in range(3):expected[i][1]=min(expected[i][1],expected[i+1][0]-expected[i][0])
    if kind==0:
     for i in range(len(notes)-1):
      if notes[i][2]==notes[i+1][2]:expected[i][1]=min(expected[i][1],expected[i+1][0]-expected[i][0])
    assert (notes==expected if kind==3 else len(notes)==len(expected) and all(n[:2]==e[:2] and abs(n[2]-e[2])<=12 for n,e in zip(notes,expected))),('source identity/rhythm changed',name,plan,expected)
    assert end==begin+max(at+length for at,length,iv in notes)
    counts[kind]+=1;begins.append(begin/16)
    if last_end is not None:assert begin-last_end>=32,('minimum silence',plan,last_end)
    last_end=end;ons=[e for e in es if e[5]==7 and e[3] and not e[4] and begin-.001<=e[0]*bpm/(48000*60)*4<end-.001]
    assert len(ons)==count,('missing figure',name,bpm,plan,ons)
    swing=.3 if case%2 else 0
    for e,(at,length,interval) in zip(ons,notes):
     step=begin+at;mod=step%4;delay=(.667 if mod==2 else .333 if mod in (1,3) else 0)*swing
     assert abs(e[0]-(step+delay)*.25*48000*60/bpm)<=1.01 and e[2]==base+interval,('rhythm/pitch',plan,e)
     off=next(t for n,t in spans if n==e);assert off>e[0]
     end_step=step+length;end_mod=end_step%4;end_delay=(.667 if end_mod==2 else .333 if end_mod in (1,3) else 0)*swing
     assert abs(off-(end_step+end_delay)*.25*48000*60/bpm)<=1.01,('gate length',name,plan,e,off)
     if case!=6:
      vocab={1:[(0,(0,4,7,11),1),(4,(0,4,7,10),1),(9,(0,3,7,10),2),(2,(0,4,7,10),1),(2,(0,3,7,10),1),(7,(0,4,7,10),1),(0,(0,4,7,11),1)],2:[(9,(0,3,7,10,2),4),(2,(0,4,7,10),2),(5,(0,4,7,11),2)],3:[(0,(0,4,7,11),2),(10,(0,4,7,11),2),(2,(0,3,7,10),2),(7,(0,5,7),2)],4:[(0,(0,4,7),2),(5,(0,4,7),2),(9,(0,3,7,10),2),(7,(0,4,7),2)],7:[(0,(0,4,7,11),8)]}[case]
      harmonic_end=min(end_step,begin+notes[notes.index([at,length,interval])+1][0]) if notes.index([at,length,interval])+1<count else end_step
      for tick in range(step,harmonic_end):
       bar=(tick//16)%8;acc=0
       for root,shape,bars in vocab:
        acc+=bars
        if bar<acc:assert e[2]%12 in {(root+iv)%12 for iv in shape},('harmonic mismatch',name,plan,e,tick);break
     active.update(range(int(e[0]*bpm/(48000*60)/4),int((off-1)*bpm/(48000*60)/4)+1))
    if kind==3:
     sequences+=1;assert count==4 and notes[1][2]-notes[0][2]==notes[3][2]-notes[2][2] and notes[2][2]-notes[0][2]==7
     if bpm==120:examples.append({'case':name,'plan':plan,'actual_ons':ons})
    actual_end=max((t for n,t in spans if n in ons),default=0)
    assert not any(e[5]==4 and e[3] and not e[4] and ons[0][0]<=e[0]<actual_end for e in es),('arp conflict',name,plan)
   summary.append({'case':name,'bpm':bpm,'counts':dict(counts),'starts_bars':begins,'active_return_bars':len(active),'before_active_bars':active_bars(b,bpm),'after_active_bars':active_bars(es,bpm),'before_hook_ons':sum(e[5]==7 and e[3]>0 and not e[4] for e in b),'after_hook_ons':sum(e[5]==7 and e[3]>0 and not e[4] for e in es),'before_sha256':hashlib.sha256(br).hexdigest(),'after_sha256':hashlib.sha256(ar).hexdigest()})
   if bpm==120:midi(out/f'{name}-before.mid',b,bpm);midi(out/f'{name}-after.mid',es,bpm)
assert sequences>0,'No actual sequence realised'
(out/'summary.json').write_text(json.dumps({'baseline':'2566894','bars':128,'results':summary,'sequence_examples':examples},indent=2)+'\n');print('24 128-bar A/B cases, 48 block comparisons passed;',sequences,'sequences')
