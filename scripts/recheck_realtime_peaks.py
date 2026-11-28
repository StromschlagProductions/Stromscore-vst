"""Repeat the three largest after-maxima to distinguish repeatable work from isolated tails.
Run only after the complete matrix, without builds/tests running concurrently.
Usage: python scripts/recheck_realtime_peaks.py BEFORE AFTER
"""
import json,subprocess,sys
from pathlib import Path
folder=Path(__file__).resolve().parents[1]/'docs/development/realtime-performance'
rows=[json.loads(s)for s in (folder/'PROCESSOR_PAIRED.jsonl').read_text().splitlines()]
ranked=sorted((r for r in rows if r['variant']=='after'and r['instances']==1 and not r['gui']),key=lambda r:r['cpu_us']['max'],reverse=True)
cases=[]
for row in ranked:
 case=tuple(row[k]for k in ('profile','genre','block','scenario','bars','instances','parallel','gui'))
 if case not in cases:cases.append(case)
 if len(cases)==3:break
with (folder/'PEAK_RECHECK.jsonl').open('w')as f:
 for case in cases:
  for repeat in range(5):
   variants=[('before',sys.argv[1]),('after',sys.argv[2])]
   if repeat%2:variants.reverse()
   digests=[]
   for variant,binary in variants:
    result=subprocess.run([binary,*map(str,case)],check=True,capture_output=True,text=True)
    row=json.loads(result.stdout);row.update(variant=variant,repetition=repeat)
    digests.append(row['digest']);f.write(json.dumps(row,separators=(',',':'))+'\n');f.flush()
   assert digests[0]==digests[1],('MIDI regression',case)
  print(case,flush=True)
