#!/usr/bin/env python3
import argparse,pathlib,subprocess,tempfile,json,hashlib
p=argparse.ArgumentParser();p.add_argument('--probe',required=True);p.add_argument('--compiler',default='c++');p.add_argument('--output',required=True);a=p.parse_args();root=pathlib.Path(__file__).resolve().parents[1];out=pathlib.Path(a.output);out.mkdir(parents=True,exist_ok=True)
results=[]
with tempfile.TemporaryDirectory() as tmp:
 tmp=pathlib.Path(tmp)
 for f in (root/'Source').glob('*.h'):(tmp/f.name).write_bytes(subprocess.check_output(['git','show','912d04c:Source/'+f.name],cwd=root))
 old=tmp/'prior';subprocess.run([a.compiler,'-std=c++17','-O2','-I',str(tmp),str(root/'tools/pop_memory_probe.cpp'),'-o',str(old)],check=True)
 for genre,count in [(0,48),(1,36)]:
  for index in range(count):
   for profile in range(3):
    args=list(map(str,[genre,index,profile,512]));before=subprocess.check_output([str(old)]+args);after=subprocess.check_output([a.probe]+args)
    assert before==after,(genre,index,profile,'MIDI regression')
    assert after==subprocess.check_output([a.probe]+list(map(str,[genre,index,profile,8192]))),(genre,index,profile,'block drift')
    results.append({'genre':genre,'index':index,'profile':profile,'sha256':hashlib.sha256(after).hexdigest()})
(out/'summary.json').write_text(json.dumps(results,indent=2)+'\n');print(len(results),'16-bar byte-exact Score/Pop regressions and block comparisons passed')
