"""Exact complete-event regression against b969932 (including CC and ordering).
Usage: python scripts/compare_realtime_midi.py BEFORE AFTER OUTPUT.json
Build tools/williams_probe.cpp with each version's Source headers first.
"""
from pathlib import Path
import json,subprocess,sys,hashlib
root=Path(__file__).resolve().parents[1];before,after=map(Path,sys.argv[1:3]);out=Path(sys.argv[3]);catalog=json.loads((root/'data/harmony/catalog.json').read_text());profiles=json.loads((root/'data/harmony/profiles.json').read_text())['profiles'];cases=[]
contexts=[(p,0)for p in range(6)]+[(0,1)]
def args(p,g,path=13,block=128,bars=16,key=2,meter=(4,4),xyz=(.8,.8,.8),cc=1,jumps=0,manual=0,follow=1,routing=0,mode=3,swing=.6):
 return [p,path,mode,block,bars,g,3,manual,follow,swing,*meter,jumps,0,0,key,0,100,0,0,*xyz,routing,.5,0,-1,127,follow,cc]
for p,g in contexts:
 pool=catalog['pools']['pop_rock']if g else profiles[p].get('score_pool',catalog['pools']['score'])
 for index in range(len(pool)):cases.append([p,100+index,3,512,8,g])
 for key in range(12):
  for meter in ((4,4),(3,8),(5,8),(7,8)):cases.append(args(p,g,key=key,meter=meter,jumps=1))
 for x,y,z in [(0,0,0),(.2,.2,.2),(.8,.2,.8),(.2,.8,.8),(.8,.8,.2),(.8,.8,.8),(.5,.5,.5)]:
  for mode in (0,1,2,3):cases.append(args(p,g,xyz=(x,y,z),mode=mode))
 for path in (11,12):
  for routing in (0,5,6):cases.append(args(p,g,path=path,routing=routing,bars=32))
 for manual,follow in ((1,1),(0,0)):cases.append(args(p,g,manual=manual,follow=follow))
 cases.append(args(p,g,path=12,bars=128,swing=0))
records=[];unselectable=[]
for i,a in enumerate(cases):
 old=subprocess.run([str(before.resolve()),*map(str,a)],capture_output=True);new=subprocess.run([str(after.resolve()),*map(str,a)],capture_output=True)
 if old.returncode==new.returncode==4:unselectable.append(a);continue
 assert old.returncode==new.returncode==0,(a,old.stderr[-400:],new.stderr[-400:])
 assert old.stdout==new.stdout,('musical regression',a)
 records.append(dict(args=a,events=len(old.stdout.splitlines()),sha256=hashlib.sha256(old.stdout).hexdigest()))
 if i%100==0:print(i,len(cases),flush=True)
out.write_text(json.dumps(dict(reference='b969932',passed=len(records),not_selectable_by_native_picker=unselectable,cases=records),indent=2)+'\n');print('Exact complete MIDI comparisons:',len(records),'native unselectable:',len(unselectable),flush=True)
