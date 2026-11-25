import argparse, concurrent.futures, hashlib, json, pathlib, subprocess, sys
from analyze import read_case
p=argparse.ArgumentParser();p.add_argument('--repo',type=pathlib.Path,required=True);p.add_argument('--output',type=pathlib.Path,required=True);p.add_argument('--source-headers',type=pathlib.Path);a=p.parse_args()
root=a.repo.resolve();out=a.output.resolve();out.mkdir(parents=True,exist_ok=True);here=pathlib.Path(__file__).resolve().parent
commit=subprocess.check_output(['git','rev-parse','HEAD'],cwd=root,text=True).strip()
source_root=(a.source_headers or root/'Source').resolve()
source_modified=a.source_headers is not None or bool(subprocess.check_output(['git','status','--porcelain','--','Source'],cwd=root))
headers=out/'headers';headers.mkdir(exist_ok=True)
original={x.name:x.read_bytes() for x in source_root.glob('*.h')}
fingerprint={name:hashlib.sha256(raw).hexdigest() for name,raw in original.items()}
for name,raw in original.items():
 if name=='ScoreEngine.h':
  needle=b'class Generator\n{\npublic:';assert raw.count(needle)==1
  raw=raw.replace(needle,b'class Generator\n{\nfriend struct MotifAuditAccess;\npublic:',1)
 path=headers/name
 if not path.exists() or path.read_bytes()!=raw:path.write_bytes(raw)
source=here/'probe.cpp'
for trace in (False,True):
 exe=out/('probe-trace' if trace else 'probe-production');inc=headers if trace else source_root
 newest=max([source.stat().st_mtime]+[p.stat().st_mtime for p in inc.glob('*.h')])
 if not exe.exists() or exe.stat().st_mtime<newest:
  subprocess.run(['c++','-std=c++17','-O2']+(['-DMOTIF_AUDIT_TRACE']+(['-DMOTIF_ESTABLISHMENT_DIAGNOSTICS'] if b'MotifRepriseProgress reprise' in original['ScoreEngine.h'] else []) if trace else [])+['-I',str(inc),str(source),'-o',str(exe)],check=True)
contexts=[('neutral',0,0),('barry',0,1),('pop',1,0)]
cases=[]
def add(context,genre,profile,path,variation=1,roles=0,motifs=3,custom=0,sceneBars=0,buildup=0,bars=128,key=2,label='main'):
 c=dict(context=context,genre=genre,profile=profile,path=path,variation=variation,roles=roles,motifs=motifs,custom=custom,sceneBars=sceneBars,buildup=buildup,bars=bars,key=key,label=label)
 c['name']=f'{context}-p{path}-v{variation}-r{roles}-m{motifs}-c{custom}-e{sceneBars}-b{buildup}-n{bars}-k{key}'
 cases.append(c)
for context,genre,profile in contexts:
 for path in range(8):
  for variation in (1,3,7):add(context,genre,profile,path,variation)
 for path in (1,6):
  for roles in (1,2):add(context,genre,profile,path,roles=roles,label='single-role')
  add(context,genre,profile,path,motifs=0,label='motifs-off')
 for custom in (1,2):add(context,genre,profile,1,custom=custom,label='controlled-harmony')
 add(context,genre,profile,1,sceneBars=64,label='finite-control')
 add(context,genre,profile,1,buildup=1,label='buildup-control')
 for path in (1,6):add(context,genre,profile,path,bars=512,label='long')
 for path in (0,1):add(context,genre,profile,path,roles=3,label='range-control')
for path in (8,9,10):
 for variation in (1,3):add('pop',1,0,path,variation,label='pop-anchor')
for variation in (1,3):
 add('barry',0,1,11,variation,label='barry-three-quarter')
 for key in (0,5):add('barry',0,1,0,variation,key=key,label='key-control')
assert len({c['name'] for c in cases})==len(cases)
def run(c):
 prefix=out/c['name'];reference=out/(c['name']+'-reference')
 base=[str(c[k]) for k in ('genre','profile','path','variation','roles','motifs','custom','sceneBars','buildup','bars')]
 for trace,target in ((True,prefix),(False,reference)):
  exe=out/('probe-trace' if trace else 'probe-production')
  dest=pathlib.Path(str(target)+'.csv')
  if not dest.exists() or dest.stat().st_mtime<exe.stat().st_mtime:
   subprocess.run([str(exe),*base,'512',str(int(trace)),str(target),str(c['key'])],check=True)
 assert pathlib.Path(str(prefix)+'.csv').read_bytes()==pathlib.Path(str(reference)+'.csv').read_bytes(),('observer changed MIDI',c)
 r,notes,frames=read_case(prefix,c)
 return r
results=[]
with concurrent.futures.ThreadPoolExecutor(max_workers=2) as pool:
 for r in pool.map(run,cases):
  results.append(r)
  print(len(results),r['config']['name'],[(v['out'],v['note_ons'],[m['memory']['count'] for m in v['materials']],v['realized_returns'],v['incomplete_returns']) for v in r['roles']],flush=True)
  (out/'results.json').write_text(json.dumps(dict(commit=commit,source_modified=source_modified,settings=dict(bpm=100,sample_rate=48000,internal_drive=False,default_sceneBars=0,default_buildup=False),source_headers_sha256=fingerprint,results=results),indent=2)+'\n')
assert all((source_root/name).read_bytes()==raw for name,raw in original.items()),'production Source changed'
print('Completed',len(results),'cases; all observer/reference MIDI streams byte-identical; production Source unchanged',flush=True)
