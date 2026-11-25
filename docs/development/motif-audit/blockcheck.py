import argparse,concurrent.futures,hashlib,json,pathlib,subprocess
parser=argparse.ArgumentParser();parser.add_argument('--output',type=pathlib.Path,required=True);out=parser.parse_args().output.resolve()
cases=[('neutral',0,0,1),('neutral',0,0,6),('barry',0,1,1),('barry',0,1,6),('pop',1,0,1),('pop',1,0,7)]
def check(item):
 name,genre,profile,path=item;ref=out/f'{name}-p{path}-v1-r0-m3-c0-e0-b0-n128-k2-reference.csv';expected=ref.read_bytes();res=[]
 for block in (127,8192):
  dest=out/f'block-{name}-{path}-{block}'
  subprocess.run([str(out/'probe-production'),str(genre),str(profile),str(path),'1','0','3','0','0','0','128',str(block),'0',str(dest),'2'],check=True)
  actual=dest.with_suffix('.csv').read_bytes();assert actual==expected,(name,path,block)
  res.append(dict(context=name,path=path,block=block,sha256=hashlib.sha256(actual).hexdigest()))
 return res
results=[]
with concurrent.futures.ThreadPoolExecutor(max_workers=2) as pool:
 for rows in pool.map(check,cases):results+=rows;print(rows,flush=True)
(out/'blockcheck.json').write_text(json.dumps(results,indent=2)+'\n')
