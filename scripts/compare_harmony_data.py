#!/usr/bin/env python3
"""Byte-exact complete MIDI and catalog facts against the pre-migration revision."""
from reference_headers import header_snapshot
import argparse,pathlib,subprocess,tempfile,json,hashlib
p=argparse.ArgumentParser();p.add_argument('--probe',required=True);p.add_argument('--compiler',default='c++');p.add_argument('--output',required=True);a=p.parse_args();root=pathlib.Path(__file__).resolve().parents[1];out=pathlib.Path(a.output);out.mkdir(parents=True,exist_ok=True);results=[]
with tempfile.TemporaryDirectory() as tmp:
 tmp=pathlib.Path(tmp)
 for name,data in header_snapshot(root,'2322d6b').items():(tmp/name).write_bytes(data)
 old=tmp/'before';subprocess.run([a.compiler,'-std=c++17','-O2','-I',str(tmp),str(root/'tools/harmony_catalog_probe.cpp'),'-o',str(old)],check=True)
 facts=subprocess.check_output([a.probe,'--facts']);assert facts==subprocess.check_output([str(old),'--facts']),'catalog/shapes/recipes/profiles/descriptions changed'
 for genre,count in [(0,48),(1,36)]:
  for index in range(count):
   for profile in range(3):
    for route in range(2):
     args=list(map(str,[genre,index,profile,512,route]));before=subprocess.check_output([str(old)]+args);after=subprocess.check_output([a.probe]+args);assert before==after,(genre,index,profile,route,'MIDI changed')
     for block in (127,8192):
      raw=subprocess.check_output([a.probe]+list(map(str,[genre,index,profile,block,route])));assert raw==after,(genre,index,profile,route,block,'block difference')
     results.append({'genre':genre,'index':index,'profile':profile,'seek_loop_restart':bool(route),'sha256':hashlib.sha256(after).hexdigest(),'bytes':len(after)})
(out/'summary.json').write_text(json.dumps({'baseline':'2322d6b','bars_per_render':64,'comparisons':len(results),'alternate_block_comparisons':2*len(results),'facts_sha256':hashlib.sha256(facts).hexdigest(),'results':results},indent=2)+'\n');print(len(results),'complete 64-bar MIDI regressions;',2*len(results),'alternate-block comparisons; full catalog facts equal')
