#!/usr/bin/env python3
"""Pinned, complete MIDI regression and onset-plan audit over 128 bars."""
from reference_headers import header_snapshot
import argparse,collections,hashlib,json,pathlib,struct,subprocess,tempfile
p=argparse.ArgumentParser();p.add_argument('--probe',required=True);p.add_argument('--compiler',default='c++');p.add_argument('--output',required=True);a=p.parse_args()
root=pathlib.Path(__file__).resolve().parents[1];out=pathlib.Path(a.output);out.mkdir(parents=True,exist_ok=True)
names=[str(2001+i)+'-auto' for i in range(36)]+['bass-follow-off','arp-follow-off','both-follow-off','manual-bass','manual-arp','manual-rate','quiet','high-root-eighths','pedal','sixteenth-pulse','manual-dance','shared-channel','buildup','scene-end','phrased-motif','continuous-hook','score-neutral','score-barry','score-herrmann','static-harmony','independent-bass-energy','dense-sixteenths','policy-every-bar','bass-muted','arp-muted','bass-solo','three-four','passing-harmony','quiet-arp']
def run(exe,case,bpm,block=512,enabled=True):
 r=subprocess.run([str(exe),str(case),str(block),str(bpm),str(int(enabled))],capture_output=True,check=True)
 return r.stdout,[tuple(map(int,l.split(b','))) for l in r.stdout.splitlines()],[list(map(int,l[2:].split(b','))) for l in r.stderr.splitlines() if l.startswith(b'R,')]
def ons(es,output):return [e for e in es if not e[4] and e[3] and e[5]==output]
def tick(e,bpm):return round(e[0]*bpm/(48000*60)*4)
def owned_spans(es):
 active={};spans=[]
 for e in es:
  if e[4]:continue
  key=e[1:3]
  if e[3]:assert key not in active,('double',e);active[key]=e
  else:assert key in active,('orphan',e);spans.append((active.pop(key),e[0]))
 assert not active
 return spans
def mask(events,bpm,bar):
 return sum(1<<pos for pos in {tick(e,bpm)%16 for e in events if tick(e,bpm)//16==bar})
def grid(m):return ''.join('x' if m&(1<<i) else '.' for i in range(16))
def metrics(es,bpm):
 bass=ons(es,2)+ons(es,3);arp=ons(es,4);bs={tick(e,bpm) for e in bass};ars={tick(e,bpm) for e in arp}
 return {'bass_attacks':len(bass),'arp_attacks':len(arp),'common':len(bs&ars),'arp_complementary':len(ars-bs),'bass_complementary':len(bs-ars),'shared_quarters':sum(t%4==0 for t in bs&ars),'arp_patterns':dict(collections.Counter(grid(mask(arp,bpm,b)) for b in range(128)))}
def midi(path,es,bpm):
 def vlq(n):
  v=[n&127];n>>=7
  while n:v.insert(0,(n&127)|128);n>>=7
  return bytes(v)
 tr=bytearray(b'\0\xff\x51\x03'+round(60000000/bpm).to_bytes(3,'big'));previous=0
 for at,ch,n,v,typ,o in es:
  at=round(at*bpm/(48000*60)*960);tr+=vlq(at-previous)+bytes([(0xb0 if typ else 0x90 if v else 0x80)+ch-1,n,v]);previous=at
 tr+=b'\0\xff\x2f\0';path.write_bytes(b'MThd'+struct.pack('>IHHH',6,0,1,960)+b'MTrk'+struct.pack('>I',len(tr))+tr)
rows=[];examples=[];total_plans=0;changes=0
with tempfile.TemporaryDirectory() as tmp:
 tmp=pathlib.Path(tmp)
 for name,data in header_snapshot(root,'b0170ee').items():(tmp/name).write_bytes(data)
 old=tmp/'before';subprocess.run([a.compiler,'-std=c++17','-O2','-I',str(tmp),str(root/'tools/rhythm_probe.cpp'),'-o',str(old)],check=True)
 for case,name in enumerate(names):
  for bpm in (90,120,173):
   br,b,_=run(old,case,bpm);control,_,_=run(a.probe,case,bpm,enabled=False);raw,es,plans=run(a.probe,case,bpm)
   assert control==br,('disabled regression',name,bpm)
   if bpm==120:
    repeat,repeated,repeated_plans=run(a.probe,case,bpm);assert repeat==raw and repeated_plans==plans,('nondeterminism',name)
   before_spans=owned_spans(b);after_spans=owned_spans(es)
   assert sorted(e for e in es if e[5]!=4)==sorted(e for e in b if e[5]!=4),('non-arp change',name,bpm)
   assert [e for e in es if e[5] in (2,3)]==[e for e in b if e[5] in (2,3)],('bass changed',name,bpm)
   assert [e for e in es if e[5]!=4 and (e[3] or e[4])]==[e for e in b if e[5]!=4 and (e[3] or e[4])],('other attack/expression order changed',name,bpm)
   before=ons(b,4);after=ons(es,4);assert len(before)==len(after),('density changed',name,bpm)
   assert [e[1:] for e in before]==[e[1:] for e in after],('arp material/order/expression changed',name,bpm)
   protected=case in [39,40,41,42,44,45,46,47,48,49,50,52,53,54,57,59,60,61,62,63,64]
   if protected:assert raw==br and not plans,('protected',name,bpm)
   planned={p[0]//16:p for p in plans};total_plans+=len(plans);changed=sum(x[0]!=y[0] for x,y in zip(before,after));changes+=changed
   assert (raw!=br)==bool(plans),('unused plans/unplanned change',name,bpm)
   for prior,current in zip(before,after):
    original_at,actual_at=tick(prior,bpm),tick(current,bpm);bar=original_at//16
    if bar not in planned:assert current==prior,('outside plan changed',name,bpm,bar)
    else:
     plan=planned[bar];notes=[plan[5+3*i:8+3*i] for i in range(plan[4])];note=next(n for n in notes if n[1]==original_at%16)
     assert actual_at==bar*16+note[0],('wrong onset',name,bpm,note,current)
   for plan in plans:
    begin,reference,original,coordinated,count=plan[:5];bar=begin//16;notes=[plan[5+3*i:8+3*i] for i in range(count)]
    assert mask(ons(es,3),bpm,bar)==reference,('reference != actual bass',name,bpm,bar)
    assert mask(before,bpm,bar)==original and mask(after,bpm,bar)==coordinated
    assert original&0x1111==coordinated&0x1111==0x1111
    assert count==8 and sum(n[2] for n in notes)<=16
    for pos,source,length in notes:
     if pos!=source:assert source%4==2 and pos==source+1 and not(reference&(1<<pos))
     event=next(e for e in after if tick(e,bpm)==begin+pos);release=next(end for n,end in after_spans if n==event)
     assert release>event[0] and pos+length<=16
    if bpm==120 and not any(e['case']==name for e in examples):
     examples.append({'case':name,'bar_zero_based':bar,'bass':grid(reference),'arp_before':grid(original),'arp_after':grid(coordinated),'onsets':notes,'planned_rest_ticks':16-sum(n[2] for n in notes)})
   block_drift=0;baseline_drift=0
   for block in (127,8192):
    rr,ee,pp=run(a.probe,case,bpm,block);assert pp==plans and len(ee)==len(es)
    delta=max((abs(x[0]-y[0]) for x,y in zip(ee,es)),default=0);block_drift=max(block_drift,delta)
    assert all(x[1:]==y[1:] and abs(x[0]-y[0])<=1 for x,y in zip(ee,es)),('block dependence',name,bpm,block)
    _,old_events,_=run(old,case,bpm,block);assert len(old_events)==len(b)
    baseline_drift=max(baseline_drift,max((abs(x[0]-y[0]) for x,y in zip(old_events,b)),default=0))
   rows.append({'case':name,'bpm':bpm,'coordinated_bars':len(plans),'melodic_bass_bars':sum(p[5+3*p[4]] for p in plans),'block_max_sample_delta':block_drift,'baseline_block_max_sample_delta':baseline_drift,'shifted_attacks':changed,'before':metrics(b,bpm),'after':metrics(es,bpm),'before_sha256':hashlib.sha256(br).hexdigest(),'after_sha256':hashlib.sha256(raw).hexdigest()})
   if bpm==120:midi(out/(name+'-before.mid'),b,bpm);midi(out/(name+'-after.mid'),es,bpm)
assert total_plans>0 and changes>0
assert sum(r['melodic_bass_bars'] for r in rows)>0,'No coverage of already planned melodic bass'
for bpm in (90,120,173):
 neutral=next(r for r in rows if r['case']=='2035-auto' and r['bpm']==bpm)
 each=next(r for r in rows if r['case']=='policy-every-bar' and r['bpm']==bpm)
 assert each['coordinated_bars']==2*neutral['coordinated_bars']>0,('policy not used',bpm)
(out/'summary.json').write_text(json.dumps({'baseline':'b0170ee','bars':128,'cases':len(rows),'coordinated_bars':total_plans,'shifted_attacks':changes,'results':rows,'examples':examples},indent=2)+'\n')
print(len(rows),'128-bar A/B cases;',len(rows)*2,'block comparisons;',total_plans,'coordinated bars;',changes,'shifted arp attacks')
