"""Offline measurement matrix; musical digests include every note/CC event.
Usage: python scripts/measure_realtime.py BINARY OUTPUT.jsonl [engine|processor]
Run before/after with identical compiler, arguments and machine conditions.
"""
import json,subprocess,sys,time
try:import resource
except ImportError:resource=None
from pathlib import Path
binary=Path(sys.argv[1]).resolve();out=Path(sys.argv[2]);kind=sys.argv[3]if len(sys.argv)>3 else 'engine'
reference=Path(sys.argv[4]).resolve()if len(sys.argv)>4 else None
contexts=[(p,0)for p in range(6)]+[(0,1)]
cases=[(p,g,b,s,32,1,0,0)for p,g in contexts for b in (64,128,256,512,1024)for s in range(7)]
cases +=[(p,g,128,3,8 if gui else 128,n,parallel,gui)for p,g in contexts for n,parallel,gui in ([(4,0,0)]if kind=='engine'else [(4,0,0),(4,1,0),(1,1,1)])]
with out.open('w')as f:
 for repetition in range(2):
  for i,args in enumerate(cases):
   used=args[:6]if kind=='engine'else args
   results=[]
   variants=[('before',reference),('after',binary)]if reference else [('single',binary)]
   if repetition%2:variants.reverse()
   for label,executable in variants:
    c0=resource.getrusage(resource.RUSAGE_CHILDREN)if resource else None
    w0=time.perf_counter()
    r=subprocess.run([str(executable),*map(str,used)],capture_output=True,text=True,check=True)
    elapsed=time.perf_counter()-w0
    c1=resource.getrusage(resource.RUSAGE_CHILDREN)if resource else None
    rows=[json.loads(line)for line in r.stdout.splitlines()]
    assert len({row['digest']for row in rows})==1,('instance state leakage',used)
    results.append([(row.get('instance',0),row['digest'])for row in rows])
    for row in rows:
     row.update(repetition=repetition,kind=kind,variant=label,process_wall_seconds=elapsed,process_cpu_seconds=(c1.ru_utime+c1.ru_stime-c0.ru_utime-c0.ru_stime)if c0 else None);f.write(json.dumps(row,separators=(',',':'))+'\n');f.flush()
   assert len(results)<2 or results[0]==results[1],('MIDI regression',args,results)
   if i%35==0:print(repetition,i,len(cases),flush=True)
