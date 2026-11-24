#!/usr/bin/env python3
"""Actual 128-bar MIDI comparison of Score Wendung entries against be09fea."""
from reference_headers import header_snapshot
import argparse, collections, hashlib, json, pathlib, struct, subprocess, tempfile
p=argparse.ArgumentParser();p.add_argument('--probe',required=True);p.add_argument('--compiler',default='c++');p.add_argument('--output',required=True);a=p.parse_args()
root=pathlib.Path(__file__).resolve().parents[1];out=pathlib.Path(a.output);out.mkdir(parents=True,exist_ok=True)
names=['stationary-dark','stationary-bright','stationary-restless','stationary-lyrical','dark-bright','chromatic-field','tritone-field','pop','custom','muted-pad','short-pad-walking-bass','pedal','XY-drive']
BAR=96000;TOTAL=128*BAR

def run(exe,case,profile,block=512):
 r=subprocess.run([str(exe),str(case),str(profile),str(block)],capture_output=True,check=True)
 return r.stdout,[tuple(map(int,l.split(b','))) for l in r.stdout.splitlines()],[tuple(map(int,l.split(b','))) for l in r.stderr.splitlines()]
def spans(events):
 active={};result=[]
 for e in events:
  if e[4]:continue
  k=e[1:3]
  if e[3]:assert k not in active,('double',e);active[k]=e
  else:
   assert k in active,('orphan',e)
   n=active.pop(k);result.append((n,e[0]))
 assert not active
 return result

def state(events,t,outputs,latest=False):
 notes=set();sounding=[];previous_time=-1
 for e in events:
  if e[0]>t:break
  if e[4] or e[5] not in outputs:continue
  if e[0]!=previous_time:
   if notes:sounding=sorted(notes)
   previous_time=e[0]
  if e[3]:notes.add(e[2])
  else:notes.discard(e[2])
 if notes:sounding=sorted(notes)
 return sounding if latest else sorted(notes)
def pcs(notes):return sorted({n%12 for n in notes})
def motion(a,b):
 if not a or not b:return 0
 return sum(min(abs(n-m) for m in b) for n in a)+sum(min(abs(n-m) for m in a) for n in b)
def midi(path,events):
 def vlq(n):
  v=[n&127];n>>=7
  while n:v.insert(0,(n&127)|128);n>>=7
  return bytes(v)
 data=bytearray(b'\x00\xff\x51\x03\x07\xa1\x20');last=0
 for sample,ch,n,v,kind,o in events:
  t=round(sample/25);data+=vlq(t-last)+bytes([(0xb0 if kind else 0x90 if v else 0x80)+ch-1,n,v]);last=t
 data+=vlq(TOTAL//25-last)+b'\xff\x2f\x00'
 path.write_bytes(b'MThd'+struct.pack('>IHHH',6,0,1,960)+b'MTrk'+struct.pack('>I',len(data))+data)

results=[];details=[]
with tempfile.TemporaryDirectory(prefix='stromscore-entries-') as temp:
 temp=pathlib.Path(temp)
 for name,data in header_snapshot(root,'be09fea').items():(temp/name).write_bytes(data)
 before=temp/'before';subprocess.run([a.compiler,'-std=c++17','-O2','-I',str(temp),str(root/'tools/transition_probe.cpp'),'-o',str(before)],check=True)
 for profile in range(3):
  for case,name in enumerate(names):
   raw0,e0,t0=run(before,case,profile);raw,e,t=run(a.probe,case,profile)
   assert t0==t,('selection changed',case,profile)
   spans(e0);spans(e)
   assert [x for x in e0 if x[4] or x[5]>=4]==[x for x in e if x[4] or x[5]>=4],('unrelated output',case,profile)
   # Pitch-class vocabulary/bass identities at every event time, not merely the boundaries.
   def harmonic_states(es):
    states=[set() for _ in range(4)];states_at={}
    for row in es:
     at,ch,n,v,kind,o=row
     if kind or o>=4:continue
     if v:states[o].add(n)
     else:states[o].discard(n)
     states_at[at]=tuple(tuple(pcs(s)) for s in states)
    return states_at
   h0,h=harmonic_states(e0),harmonic_states(e)
   p0=p1=((),(),(),())
   for at in sorted(h0.keys()|h.keys()):
    p0=h0.get(at,p0);p1=h.get(at,p1);assert p0==p1,('colour/bass changed',name,profile,at,p0,p1)
   if case in (7,8):assert raw0==raw,('regression',name,profile)
   for block in (127,8192):
    rb,eb,tb=run(a.probe,case,profile,block);assert rb==raw and tb==t,('blocks',name,profile,block)
   measurements=[]
   for at,w,root_note,quality,source_root,source_quality,first_bars in t[1:]:
    pad_outputs=(1,) if case==10 else (0,)
    previous=state(e,at-1,pad_outputs,True);old_previous=state(e0,at-1,pad_outputs,True)
    old=state(e0,at+1,pad_outputs);new=state(e,at+1,pad_outputs)
    baseline_bass_before=state(e0,at-1,(2,3),True);bass_before=state(e,at-1,(2,3),True);old_bass=state(e0,at+1,(2,3));bass=state(e,at+1,(2,3))
    row={'profile':profile,'case':name,'bar':at/BAR,'target_index':w,'root':root_note,'quality':quality,'source_root':source_root,'source_quality':source_quality,'root_motion_class':(root_note-source_root)%12,'previous':previous,'baseline_previous':old_previous,'baseline':old,'new':new,'common_before':sorted(set(old_previous)&set(old)),'common_after':sorted(set(previous)&set(new)),'movement_before':motion(old_previous,old),'movement_after':motion(previous,new),'ordered_semitones_before':[b-a for a,b in zip(old_previous,old)] if len(old_previous)==len(old) else None,'ordered_semitones_after':[b-a for a,b in zip(previous,new)] if len(previous)==len(new) else None,'baseline_bass_previous':baseline_bass_before,'bass_previous':bass_before,'bass_baseline':old_bass,'bass_new':bass,'bass_semitones_before':old_bass[0]-baseline_bass_before[0] if baseline_bass_before and old_bass else None,'bass_semitones_after':bass[0]-bass_before[0] if bass_before and bass else None}
    common=set(previous)&set(new)
    row['common_rearticulated']=sum(x[0]==at and x[5] in pad_outputs and x[3]>0 and x[2] in common for x in e)
    if case!=10:assert row['common_rearticulated']==0,('lost held common note',name,profile,at)
    end=min(at+first_bars*BAR,((at//(8*BAR))+1)*8*BAR)
    row['entry_end_bar']=end/BAR
    if end<TOTAL and not any(record[0]==end for record in t):
     old_exit=state(e0,end+1,pad_outputs);new_exit=state(e,end+1,pad_outputs)
     assert old_exit==new_exit,('changed following chord',name,profile,end)
     row['exit_baseline']=old_exit;row['exit_new']=new_exit
     row['exit_movement_before']=motion(state(e0,end-1,pad_outputs,True),old_exit)
     row['exit_movement_after']=motion(state(e,end-1,pad_outputs,True),new_exit)
    details.append(row);measurements.append(row)
   results.append({'profile':profile,'case':name,'transitions':len(measurements),'changed_entries':sum(r['baseline']!=r['new'] for r in measurements),'movement_before':sum(r['movement_before'] for r in measurements),'movement_after':sum(r['movement_after'] for r in measurements),'common_before':sum(len(r['common_before']) for r in measurements),'common_after':sum(len(r['common_after']) for r in measurements),'widths_before':sorted({r['baseline'][-1]-r['baseline'][0] for r in measurements if r['baseline']}),'widths_after':sorted({r['new'][-1]-r['new'][0] for r in measurements if r['new']}),'before_sha256':hashlib.sha256(raw0).hexdigest(),'after_sha256':hashlib.sha256(raw).hexdigest()})
   if profile==0:
    (out/f'{name}-before.csv').write_bytes(raw0);(out/f'{name}-after.csv').write_bytes(raw)
    midi(out/f'{name}-before.mid',e0);midi(out/f'{name}-after.mid',e)
(out/'summary.json').write_text(json.dumps(results,indent=2)+'\n');(out/'entries.json').write_text(json.dumps(details,indent=2)+'\n')
assert any(r['root_motion_class']==6 for r in details) and any(r['root_motion_class'] in (1,11) for r in details)
print(f'{len(results)} 128-bar comparisons, {len(results)*2} block comparisons; {len(details)} Wendung changes verified')
