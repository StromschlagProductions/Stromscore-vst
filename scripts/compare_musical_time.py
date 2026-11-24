"""Before/after complete MIDI bytes; grid timing, meter, swing, transport and block tests."""
import argparse,pathlib,sys,tempfile,subprocess,json,hashlib,itertools
root=pathlib.Path(__file__).resolve().parents[1];sys.path.insert(0,str(root/'Tests'))
from HarmonyImportFixtures import prepare
p=argparse.ArgumentParser();p.add_argument('--probe',required=True);p.add_argument('--compiler',default='c++');p.add_argument('--output',required=True);a=p.parse_args();out=pathlib.Path(a.output);out.mkdir(parents=True,exist_ok=True);cat=json.loads((root/'data/harmony/catalog.json').read_text());byid={t['id']:t for t in cat['templates']};rows=[];blockchecks=0
meters=[(4,4),(3,4),(6,8),(3,8)];cases=[]
for t in cat['templates']:
 for profile in range(3):
  for route in range(2):cases.append((t['id'],profile,route,meters[(t['id']+profile)%4],(90,120,173)[profile],(0,.2,.5)[(t['id']+route)%3],32,False))
for id,meter,bpm,swing in itertools.product((1005,1008,1034,2015,2035,2037,2038,2039),meters,(90,120,173),(0,.2,.5)):
 cases.append((id,id%3,id%2,meter,bpm,swing,32,True))
for id,num,den in itertools.product((1005,2035),range(1,17),(1,2,4,8,16)):cases.append((id,0,0,(num,den),120,.3,32,True))
for id in (1005,2035,2037):cases.append((id,0,0,(3,8),173,.3,4096,True))
with tempfile.TemporaryDirectory() as tmp:
 tmp=pathlib.Path(tmp);prepare(tmp/'headers',revision='427a068',explicit=True);exe=tmp/'baseline';subprocess.run([a.compiler,'-std=c++17','-O2','-I',str(tmp/'headers'),str(root/'tools/harmony_import_probe.cpp'),'-o',str(exe)],check=True)
 for id,profile,route,meter,bpm,swing,bars,blocks in cases:
  t=byid[id];args=list(map(str,[id,0,*t['xyz'],1,0,1,1,bars,512,bpm,route,profile,swing,0 if id<2000 else 1,*meter]))
  before=subprocess.check_output([str(exe)]+args);after=subprocess.check_output([a.probe]+args);assert before==after,(id,profile,route,meter,bpm,swing,'MIDI changed')
  if blocks:
   reference=[tuple(map(int,l.split(b','))) for l in after.splitlines()]
   for block in (127,480,8192):
    args[10]=str(block);other=[tuple(map(int,l.split(b','))) for l in subprocess.check_output([a.probe]+args).splitlines()]
    assert len(other)==len(reference) and all(x[1:]==y[1:] and abs(x[0]-y[0])<=1 for x,y in zip(other,reference)),(id,meter,bpm,block,'block')
    blockchecks+=1
  rows.append({'id':id,'profile':profile,'route':route,'meter':meter,'bpm':bpm,'swing':swing,'bars':bars,'sha256':hashlib.sha256(after).hexdigest()})
(out/'regression.json').write_text(json.dumps({'baseline':'427a068','comparisons':len(rows),'block_comparisons':blockchecks,'results':rows},indent=2)+'\n');print(len(rows),'byte-identical before/after renders;',blockchecks,'alternate-block comparisons')
