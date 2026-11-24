#!/usr/bin/env python3
"""Byte-exact complete MIDI and catalog facts against the pre-migration revision."""
from reference_headers import header_snapshot
from transport_regression import assert_chase_delta
import argparse,pathlib,subprocess,tempfile,json,hashlib
p=argparse.ArgumentParser();p.add_argument('--with-passing',action='store_true');p.add_argument('--baseline',default='2322d6b');p.add_argument('--probe',required=True);p.add_argument('--compiler',default='c++');p.add_argument('--output',required=True);a=p.parse_args();root=pathlib.Path(__file__).resolve().parents[1];out=pathlib.Path(a.output);out.mkdir(parents=True,exist_ok=True);results=[]
with tempfile.TemporaryDirectory() as tmp:
 tmp=pathlib.Path(tmp)
 for name,data in header_snapshot(root,a.baseline).items():(tmp/name).write_bytes(data)
 old=tmp/'before';subprocess.run([a.compiler,'-std=c++17','-O2','-I',str(tmp),str(root/'tools/harmony_catalog_probe.cpp'),'-o',str(old)],check=True)
 facts=subprocess.check_output([a.probe,'--facts']);assert facts==subprocess.check_output([str(old),'--facts']),'catalog/shapes/recipes/profiles/descriptions changed'
 for genre,count in [(0,48),(1,36)]:
  for index in range(count):
   for profile in range(3):
    for route in range(2):
     for passing in ((0,1) if a.with_passing else (0,)):
      args=list(map(str,[genre,index,profile,512,route,passing]));before=subprocess.check_output([str(old)]+args);after=subprocess.check_output([a.probe]+args)
      if route:
       spq=48000*60/(90 if index%3==0 else 120 if index%3==1 else 173);segment=int(64*spq)
       assert_chase_delta(before,after,(segment,segment*2,segment*3),samples_per_quarter=spq)
      else:assert before==after,(genre,index,profile,route,'MIDI changed')
      for block in (127,8192):
       raw=subprocess.check_output([a.probe]+list(map(str,[genre,index,profile,block,route,passing])));assert raw==after,(genre,index,profile,route,block,'block difference')
      results.append({'genre':genre,'index':index,'profile':profile,'seek_loop_restart':bool(route),'passing':bool(passing),'byte_identical':before==after,'before_sha256':hashlib.sha256(before).hexdigest(),'sha256':hashlib.sha256(after).hexdigest(),'bytes':len(after)})
(out/'summary.json').write_text(json.dumps({'baseline':a.baseline,'bars_per_render':64,'comparisons':len(results),'alternate_block_comparisons':2*len(results),'facts_sha256':hashlib.sha256(facts).hexdigest(),'results':results},indent=2)+'\n');print(len(results),'complete 64-bar MIDI regressions;',2*len(results),'alternate-block comparisons; full catalog facts equal')
