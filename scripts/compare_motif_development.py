#!/usr/bin/env python3
"""128-bar actual-material variations; no reference implementation in the plugin."""
import argparse,collections,hashlib,json,pathlib,struct,subprocess
p=argparse.ArgumentParser();p.add_argument('--probe',required=True);p.add_argument('--output',required=True);a=p.parse_args();out=pathlib.Path(a.output);out.mkdir(parents=True,exist_ok=True)
BAR=96000;TICK=6000;TOTAL=128*BAR
names={1:'held',3:'minor-colour',4:'changing',7:'one-bar',8:'four-bar',9:'melody-answer',11:'dialogue-arp',12:'pop',13:'range',14:'seek-loop',18:'long-cycle',22:'restart'}
def run(case,profile,block=512,kind=None):
 cmd=[a.probe,str(case),str(profile),str(block)]+([] if kind is None else [str(kind)])
 r=subprocess.run(cmd,capture_output=True,check=True);es=[tuple(map(int,l.split(b','))) for l in r.stdout.splitlines()];trace=collections.defaultdict(list,{key:[] for key in ("H","M","O","V")})
 for l in r.stderr.splitlines():trace[l[:1].decode()].append(list(map(int,l[2:].split(b','))))
 return r.stdout,es,trace

def spans(es):
 active={};result=[]
 for e in es:
  if e[4]:continue
  key=e[1:3]
  if e[3]:assert key not in active,('double',e);active[key]=e
  else:
   assert key in active,('orphan',e);n=active.pop(key);result.append((n,e[0]))
 assert not active
 return result

def derive(m,kind):
 count=m[2];ns=[m[4+3*i:7+3*i] for i in range(count)]
 if kind==1:
  longest=max(range(count),key=lambda i:ns[i][1]);ns=[n.copy() for n in ns];ns[longest][1]=max(1,ns[longest][1]//2)
 if kind==2:
  ns=ns[-min(3,count-1):];origin=ns[0][0];ns=[[at-origin,length,iv] for at,length,iv in ns]
 if kind==3:
  period=ns[2][0] if count>2 else ns[1][0]+ns[1][1];ns=ns[:2]+[[at+period,length,iv+7] for at,length,iv in ns[:2]]
 if kind==4:ns=[[at*2,length*2,iv] for at,length,iv in ns]
 if kind:
  for i in range(len(ns)-1):ns[i][1]=min(ns[i][1],ns[i+1][0]-ns[i][0])
 return ns

def midi(path,es):
 def vlq(n):
  v=[n&127];n>>=7
  while n:v.insert(0,(n&127)|128);n>>=7
  return bytes(v)
 data=bytearray(b'\x00\xff\x51\x03\x07\xa1\x20');previous=0
 for sample,ch,n,v,kind,o in es:
  t=round(sample/25);data+=vlq(t-previous)+bytes([(0xb0 if kind else 0x90 if v else 0x80)+ch-1,n,v]);previous=t
 data+=vlq(TOTAL//25-previous)+b'\xff\x2f\x00';path.write_bytes(b'MThd'+struct.pack('>IHHH',6,0,1,960)+b'MTrk'+struct.pack('>I',len(data))+data)
summary=[];examples=[];distribution=collections.Counter()
for profile in range(3):
 for case,name in names.items():
  raw,es,tr=run(case,profile);raw0,es0,tr0=run(case,profile,kind=0);ss=spans(es);spans(es0)
  assert tr['H']==tr0['H'] and tr['M']==tr0['M'],('original/harmony changed',name,profile)
  if case==12:assert raw==raw0,('Pop changed',profile)
  for block in (127,8192):
   rb,eb,tb=run(case,profile,block);assert rb==raw and tb==tr,('block drift',name,profile,block)
  counts=collections.Counter();last={};fallbacks=0
  for v in tr['V']:
   output,begin,end,ordinal,intro,base,kind,source,count=v[:9]
   if intro or not count:continue
   m=next(m for m in tr['M'] if m[0]==output and m[1]==source)
   ns=[v[9+3*i:12+3*i] for i in range(count)];assert ns==derive(m,kind),('not direct source derivation',v,m)
   assert end==begin+max(at+length for at,length,iv in ns)
   if case not in (14,22):
    played=[e for e in es if e[5]==output and e[3]>0 and e[4]==0 and begin*TICK<=e[0]<end*TICK]
    assert [(e[0]//TICK,e[2]) for e in played]==[(begin+at,base+iv) for at,length,iv in ns],('played figure mismatch',name,v,played)
    for e,(at,length,iv) in zip(played,ns):
     off=next(t for n,t in ss if n==e);expected=min(length,ns[played.index(e)+1][0]-at) if output==8 and played.index(e)+1<count else length
     assert off-e[0]==expected*TICK,('duration',name,v,e,off,expected)
     assert 0<=e[2]<=127
     if case not in (12,14,22):
      start=begin+at;finish=start+length
      # The pre-existing one-tick dialogue legato may overlap the next attack.
      if output==7 and played.index(e)+1<count:finish=min(finish,begin+ns[played.index(e)+1][0])
      for tick in range(start,finish):
       b=tick//16
       root,types=0,(0,4,7,11)
       if case==3:types=(0,3,7,11,2)
       if case in (4,13):
        local=b%8
        root,types=(0,(0,4,7,11)) if local<1 else (9,(0,3,7,10)) if local<4 else (2,(0,3,7,10)) if local<6 else (7,(0,4,7,10))
       if case==18 and (b//8)%2:root,types=9,(0,3,7,10)
       assert e[2]%12 in {(root+x)%12 for x in types},('harmonic mismatch',name,v,e,tick)
     if case==13 and 8*16<=begin<64*16:assert False,('unplayable register forced',v)
    if output in last:assert begin-last[output]>=32,('minimum rest',v,last)
    last[output]=end
    if output==8:assert not any(n[5]==7 and n[0]<end*TICK and t>begin*TICK for n,t in ss),('lead/answer',v)
    if case!=11:
     actual_end=max(t for n,t in ss if n in played)
     assert not any(e[5]==4 and e[3]>0 and e[4]==0 and played[0][0]<=e[0]<actual_end for e in es),('arp window',v)
   fallbacks+=kind!=[0,1,0,2,0,3,0,4][(ordinal-1)%8]
   counts[kind]+=1;distribution[kind]+=case not in (14,22)
   if profile==0 and case in (1,4,9) and not any(x['variation']==kind for x in examples):examples.append({'case':name,'variation':kind,'source_identity':source,'source_origin':m[3],'original':derive(m,0),'begin_tick':begin,'base':base,'notes':ns})
  summary.append({'profile':profile,'case':name,'counts':dict(counts),'fallbacks':fallbacks,'sha256':hashlib.sha256(raw).hexdigest(),'original_only_sha256':hashlib.sha256(raw0).hexdigest()})
  if profile==0:
   midi(out/f'{name}-original.mid',es0);midi(out/f'{name}-variants.mid',es)
   (out/f'{name}-plans.json').write_text(json.dumps(dict(tr),indent=2)+'\n')
assert all(distribution[k]>0 for k in (0,1,2,3,4)),distribution
(out/'summary.json').write_text(json.dumps({'bars':128,'distribution':dict(distribution),'results':summary,'examples':examples},indent=2)+'\n')
print(len(summary),'128-bar cases;',len(summary)*2,'block comparisons;',dict(distribution))
