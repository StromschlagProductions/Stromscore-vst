"""Actual current engine vs a6affa0: protect complete Score MIDI, accompaniment including CC, and physical gates."""
import argparse,collections,json,pathlib,subprocess,sys,tempfile
root=pathlib.Path(__file__).resolve().parents[1];sys.path.insert(0,str(root/'Tests'))
from HarmonyImportFixtures import prepare
p=argparse.ArgumentParser();p.add_argument('--output',required=True);p.add_argument('--compiler',default='c++');a=p.parse_args();out=pathlib.Path(a.output);out.mkdir(parents=True,exist_ok=True)
rows=[]
def events(raw):return [tuple(map(int,l.split(b','))) for l in raw.splitlines()]
def verify(before,after,score):
 b,n=events(before),events(after)
 protected=lambda es:collections.Counter(e for e in es if e[1]<7)
 assert protected(b)==protected(n),'accompaniment/CC changed'
 if score:assert before==after,'Score MIDI changed'
 active={};roles=collections.Counter();last=0
 for at,o,ch,note,v,kind in n:
  assert not(roles[7] and roles[8] and at>last),'competing foreground';last=at
  if kind:continue
  key=ch,note
  if v:assert key not in active;active[key]=o;roles[o]+=1
  else:assert key in active;roles[active.pop(key)]-=1
 assert not active,'hanging notes'
 return sum(e[4]>0 and not e[5] and e[1]>=7 for e in b),sum(e[4]>0 and not e[5] and e[1]>=7 for e in n)
with tempfile.TemporaryDirectory() as tmp:
 tmp=pathlib.Path(tmp);executables=[]
 for rev in ('a6affa0',None):
  d=tmp/(rev or 'working');prepare(d,revision=rev,explicit=True,currentMotifs=True,currentPop=True);exe=d/'probe'
  subprocess.run([a.compiler,'-std=c++17','-O2','-I',str(d),str(root/'tools/harmony_import_probe.cpp'),'-o',str(exe)],check=True);executables.append(exe)
 for t in json.loads((root/'data/harmony/catalog.json').read_text())['templates']:
  for profile in range(3):
   for route in (0,1):
    args=list(map(str,[t['id'],0,*t['xyz'],1,0,1,1,32,512,120,route,profile,.2,0 if t['id']<2000 else 1]))
    old,new=[subprocess.check_output([str(exe)]+args) for exe in executables]
    before,after=verify(old,new,t['id']<2000)
    rows.append(dict(id=t['id'],profile=profile,route=route,old_attacks=before,new_attacks=after,byte_identical=old==new))
    print(t['id'],profile,route,before,after,flush=True)
(out/'regression.json').write_text(json.dumps({'baseline':'a6affa0','comparisons':len(rows),'results':rows},indent=2)+'\n')
