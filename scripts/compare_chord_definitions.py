"""All 87 existing templates explicitly pinned against e4cb881; full MIDI bytes."""
import argparse,pathlib,sys,tempfile,subprocess,json,hashlib
root=pathlib.Path(__file__).resolve().parents[1];sys.path.insert(0,str(root/'Tests'))
from HarmonyImportFixtures import prepare
from transport_regression import assert_chase_delta
from role_regression import assert_score_role_delta
p=argparse.ArgumentParser();p.add_argument('--probe',required=True);p.add_argument('--compiler',default='c++');p.add_argument('--output',required=True);a=p.parse_args();out=pathlib.Path(a.output);out.mkdir(parents=True,exist_ok=True);cat=json.loads((root/'data/harmony/catalog.json').read_text());rows=[]
with tempfile.TemporaryDirectory() as tmp:
 tmp=pathlib.Path(tmp);prepare(tmp/'headers',revision='e4cb881',explicit=True);exe=tmp/'baseline';subprocess.run([a.compiler,'-std=c++17','-O2','-I',str(tmp/'headers'),str(root/'tools/harmony_import_probe.cpp'),'-o',str(exe)],check=True)
 for t in cat['templates']:
  for profile in range(3):
   for route in range(2):
    args=list(map(str,[t['id'],0,*t['xyz'],1,0,1,1,32,512,120,route,profile,.2,0 if t['id']<2000 else 1]))
    old=subprocess.check_output([str(exe)]+args);new=subprocess.check_output([a.probe]+args)
    if t['id']<2000:assert_score_role_delta(old,new,(768000,1536000,2304000) if route else (),layout='import')
    elif route:assert_chase_delta(old,new,(768000,1536000,2304000),layout='import')
    else:assert old==new,(t['id'],profile,route)
    rows.append({'id':t['id'],'profile':profile,'route':route,'byte_identical':old==new,'before_sha256':hashlib.sha256(old).hexdigest(),'sha256':hashlib.sha256(new).hexdigest()})
(out/'regression.json').write_text(json.dumps({'baseline':'e4cb881','comparisons':len(rows),'bars':32,'results':rows},indent=2)+'\n');print(len(rows),'existing-template comparisons; linear renders byte-exact, explicit chase claims validated')
