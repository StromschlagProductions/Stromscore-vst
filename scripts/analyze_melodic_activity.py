"""Offline long-run activity study; source snapshots and CSVs stay in --output."""
import argparse,pathlib,sys,subprocess,json
root=pathlib.Path(__file__).resolve().parents[1];sys.path.insert(0,str(root/'scripts'));from reference_headers import header_snapshot
p=argparse.ArgumentParser();p.add_argument('--output',required=True);p.add_argument('--compiler',default='c++');p.add_argument('--bars',type=int,default=128);p.add_argument('--supplement',action='store_true');a=p.parse_args();out=pathlib.Path(a.output);out.mkdir(parents=True,exist_ok=True)
cases=[(g,p,m,0,0) for g in range(2) for p in (0,1,2,3,4,6) for m in (0,1)]
cases += [(g,p,2,0,0) for g in range(2) for p in (1,3)]
cases += [(g,p,0,0,0) for g in range(2) for p in (7,8)]
cases += [(0,p,0,profile,0) for p in (1,3) for profile in (1,2)]
cases += [(g,p,m,0,0) for g in range(2) for p in (0,1,2,3,4,9) for m in (3,4,5,6,7)]
cases += [(0,p,m,0,0) for p,m in ((8,3),(12,3),(10,3),(10,4),(13,3),(13,4))]
if a.supplement:cases=[c for c in cases if c[0]==0 and (c[1],c[2]) in ((8,3),(12,3),(10,3),(10,4),(13,3),(13,4))]
if a.bars<1:p.error('--bars must be positive')
results=[]
for revision,macro in [('9a3cbad',None),('working',None),('17b15a4','ACTIVITY_PRE_SCHEDULER'),('v2.1','ACTIVITY_V21')]:
 d=out/revision;d.mkdir(exist_ok=True);headers=header_snapshot(root,None if revision=='working' else revision)
 for name,content in headers.items():
  if name=='ScoreEngine.h' and revision!='v2.1':
   content=content.replace(b'\r\n',b'\n');needle=b'class Generator\n{\npublic:';assert needle in content
   content=content.replace(needle,b'class Generator\n{\nfriend struct ActivityAccess;\npublic:',1)
  (d/name).write_bytes(content)
 exe=d/'probe';cmd=[a.compiler,'-std=c++17','-O3','-DNDEBUG','-I',str(d),str(root/'tools/melodic_activity_probe.cpp'),'-o',str(exe)]
 if macro:cmd.insert(1,'-D'+macro)
 subprocess.run(cmd,check=True)
 for genre,path,mode,profile,seed in cases:
  if revision=='v2.1' and (mode not in (1,2,4) or profile):continue
  name=f'g{genre}-p{path}-m{mode}-a{profile}-s{seed}';data=json.loads(subprocess.check_output([str(exe),*map(str,(genre,path,mode,profile,seed,a.bars)),str(d/(name+'.csv'))]));data['revision']=revision;results.append(data)
  (out/'results.json').write_text(json.dumps(results,indent=2)+'\n');print(revision,name,[r['note_ons'] for r in data['roles']],flush=True)
