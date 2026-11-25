"""Flexible Score motif realization study; compares actual MIDI with the preceding committed engine."""
import argparse,collections,hashlib,json,pathlib,subprocess,sys
root=pathlib.Path(__file__).resolve().parents[1];sys.path.insert(0,str(root/'scripts'))
from reference_headers import header_snapshot
from score_realization_validation import validate_examples
p=argparse.ArgumentParser();p.add_argument('--output',required=True);p.add_argument('--compiler',default='c++');p.add_argument('--bars',type=int,default=128);p.add_argument('--quick',action='store_true');a=p.parse_args()
if a.bars<1:p.error('--bars must be positive')
out=pathlib.Path(a.output);out.mkdir(parents=True,exist_ok=True)
# Base/isolated/individual/Solo/threshold/late activation, plus free-line and build controls.
cases=[(0,path,mode) for path in (0,1,2,3,4,9,13) for mode in (0,1,3,4,5,6,7,8,9,10,11,12,13)]
cases += [(0,path,mode) for path,mode in ((7,0),(7,3),(8,3),(12,3),(1,2),(3,2))]
cases += [(0,path,14) for path in (3,4,13)]
cases += [(1,path,mode) for path in (0,3,4) for mode in (0,3)]
if a.quick:cases=[(0,path,mode) for path in (3,4,13) for mode in (0,4,8,14)]+[(1,3,0)]
results=[];streams={}
def analyze(path,bars):
 rows=[tuple(map(int,line.split(','))) for line in path.read_text().splitlines()[1:]]
 def digest(events):return hashlib.sha256(repr(sorted(events)).encode()).hexdigest()
 active=[set(),set()];last=0;overlap=0;united=[];begin=None;broken=0
 for sample,output,channel,note,velocity,kind in rows:
  if active[0] and active[1]:overlap+=sample-last
  last=sample
  if kind or output not in (7,8):continue
  role=output-7;was=bool(active[0] or active[1]);key=(channel,note)
  if velocity:
   if key in active[role]:broken+=1
   active[role].add(key)
  else:
   if key not in active[role]:broken+=1
   active[role].discard(key)
  now=bool(active[0] or active[1])
  if now and not was:begin=sample
  if was and not now:united.append((begin,sample));begin=None
 broken+=sum(map(len,active));cursor=0;gap=0
 for begin,end in united:gap=max(gap,begin-cursor);cursor=end
 gap=max(gap,bars*96000-cursor)
 return {'controllers_sha256':digest([x for x in rows if x[5]]),'all_events_sha256':digest(rows),'accompaniment_canonical_sha256':digest([x for x in rows if x[1] in (0,1,2,3,5,6)]),'melody_sha256':digest([x for x in rows if x[1]==8]),'overlap_seconds':overlap/48000,'joint_max_silence_seconds':gap/48000,'note_ledger_errors':broken}
for revision in ('c835747','working'):
 d=out/revision;d.mkdir(exist_ok=True)
 for name,content in header_snapshot(root,None if revision=='working' else revision).items():
  if name=='ScoreEngine.h':
   content=content.replace(b'inline bool popMelodicRoles(const Settings& s){return s.genre==GenrePopRock;}',b'inline bool popMelodicRoles(const Settings&){return false;}')
   content=content.replace(b'\r\n',b'\n');needle=b'class Generator\n{\npublic:';assert needle in content
   content=content.replace(needle,b'class Generator\n{\nfriend struct ActivityAccess;\npublic:',1)
  (d/name).write_bytes(content)
 exe=d/'probe';subprocess.run([a.compiler,'-std=c++17','-O3','-DNDEBUG']+(['-DSCORE_REALIZATION_MEASUREMENTS'] if revision=='working' else [])+['-I',str(d),str(root/'tools/melodic_activity_probe.cpp'),'-o',str(exe)],check=True)
 for genre,path,mode in cases:
  name=f'g{genre}-p{path}-m{mode}';csv=d/(name+'.csv');r=json.loads(subprocess.check_output([str(exe),str(genre),str(path),str(mode),'0','0',str(a.bars),str(csv)]));r.update(revision=revision,**analyze(csv,a.bars));results.append(r);streams[revision,genre,path,mode]=r
  if revision=='working':
   if genre==0:r['example_validation']=validate_examples(csv,r)
   before=streams['c835747',genre,path,mode]
   assert r['accompaniment_canonical_sha256']==before['accompaniment_canonical_sha256'],('accompaniment',name)
   assert r['controllers_sha256']==before['controllers_sha256'],('CC',name)
   r['melodic_or_reservation_delta']=r['all_events_sha256']!=before['all_events_sha256']
   assert r['overlap_seconds']==0 and r['note_ledger_errors']==0,('overlap/notes',name,r)
  (out/'results.json').write_text(json.dumps(results,indent=2)+'\n');print(revision,name,[x['note_ons'] for x in r['roles']],r['joint_max_silence_seconds'],flush=True)
