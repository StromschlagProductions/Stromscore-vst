"""Actual phase-2 engine vs 228425b: preserve free/Herrmann and Pop, measure Barry."""
import argparse,collections,csv,hashlib,json,pathlib,subprocess,sys
from reference_headers import header_snapshot
root=pathlib.Path(__file__).resolve().parents[1]
p=argparse.ArgumentParser();p.add_argument('--output',required=True);p.add_argument('--quick',action='store_true');a=p.parse_args();out=pathlib.Path(a.output);out.mkdir(parents=True,exist_ok=True)
results=[];raws={}
def stats(data):
 rows=[tuple(map(int,l.split(b','))) for l in data.splitlines()];active={};held=[set(),set()];busy=[0,0];ons=collections.Counter();last=0;overlap=0;common=[];start=None;broken=0
 for at,o,ch,n,v,t in rows:
  for i in range(2):busy[i]+=(at-last)*bool(held[i])
  overlap+=(at-last)*bool(held[0] and held[1]);last=at
  if t:continue
  key=ch,n;before=bool(held[0] or held[1])
  if v:
   assert key not in active,('double on',key,at)
   active[key]=o;ons[o]+=1
  else:assert key in active,('orphan off',key,at);active.pop(key)
  if o>=7:
   if v:held[o-7].add(key)
   else:held[o-7].remove(key)
  after=bool(held[0] or held[1])
  if after and not before:start=at
  if before and not after:common.append((start,at));start=None
 assert not active,'hanging notes'
 end=128*96000;cursor=0;silence=0
 for begin,finish in common:silence=max(silence,begin-cursor);cursor=finish
 silence=max(silence,end-cursor)
 return dict(sha256=hashlib.sha256(data).hexdigest(),ons=dict(ons),dialog_gate=100*busy[0]/end,melody_gate=100*busy[1]/end,overlap_seconds=overlap/48000,joint_silence_seconds=silence/48000)
contexts=[(0,0),(0,2),(1,0),(1,1),(1,2)]
cases=[(g,p,path,0,0) for g,p in contexts for path in (0,1,2)]
cases += [(g,p,2,1,0) for g,p in contexts]+[(g,p,0,0,1) for g,p in contexts]
cases += [(0,1,path,0,0) for path in range(5)]+[(0,1,2,1,0),(0,1,0,0,1)]
if a.quick:cases=[(g,p,path,0,0) for g,p in [(0,0),(0,1),(0,2),(1,1)] for path in (0,1,2)]
for revision in ('228425b','working'):
 d=out/revision;d.mkdir(exist_ok=True)
 for name,content in header_snapshot(root,None if revision=='working' else revision).items():(d/name).write_bytes(content)
 exe=d/'probe';subprocess.run(['c++','-std=c++17','-O3']+(['-DBARRY_PROFILE'] if revision=='working' else [])+['-I',str(d),str(root/'tools/barry_probe.cpp'),'-o',str(exe)],check=True)
 for genre,profile,path,route,manual in cases:
  key=genre,profile,path,route,manual;data=subprocess.check_output([str(exe),*map(str,[profile,path,128,512,route,genre,manual])]);r=stats(data);r.update(revision=revision,genre=genre,profile=profile,path=path,route=route,manual=manual);results.append(r)
  if revision=='working':
   old=raws[key]
   if genre==1 or profile!=1:assert old==data,('free/Pop changed',key)
   assert r['overlap_seconds']==0,('competing foreground',key)
   if profile==1 and genre==0 and not route:(d/f'g{genre}-p{profile}-path{path}-m{manual}.csv').write_bytes(data)
  else:raws[key]=data
  print(revision,key,r['ons'],flush=True)
 (out/'midi_results.json').write_text(json.dumps(results,indent=2)+'\n')
if not a.quick:
 exe=out/'selection';subprocess.run(['c++','-std=c++17','-O3','-I',str(root/'Source'),str(root/'tools/barry_selection_probe.cpp'),'-o',str(exe)],check=True)
 data=subprocess.check_output([str(exe)]);(out/'selection.csv').write_bytes(data)
 rows=[{k:float(v) for k,v in r.items()} for r in csv.DictReader(data.decode().splitlines())];summary=[]
 for v in (0,.5,1):
  selected=[r for r in rows if r['variety']==v];ns=[r['count'] for r in selected];summary.append(dict(variety=v,points=len(ns),minimum=min(ns),maximum=max(ns),mean=sum(ns)/len(ns),single_percent=100*ns.count(1)/len(ns),max_distance=max(r['distance'] for r in selected),selected_ids=sorted(set(int(r['selected']) for r in selected))))
 (out/'coverage.json').write_text(json.dumps(summary,indent=2)+'\n')
print('Actual MIDI comparison and note ledgers passed. No historical feature seams used.')
