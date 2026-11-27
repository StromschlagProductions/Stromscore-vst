"""Offline conservative JC combination/XYZ diagnostics, not an engine/profile implementation.
Run audit.py first. Formal pitch/intent/range compatibility is not an auditory approval.
"""
from pathlib import Path
import json,math,itertools,collections,tempfile,subprocess
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[2]
items=json.loads((HERE/'TECHNICAL_INVENTORY.json').read_text(encoding='utf-8'))['templates'];by={r['id']:r for r in items};hs=[r for r in items if r['kind']=='H'];sources=[r for r in items if r['kind'] in ('Q','B','M')]
mode_steps={'Äolisch':{0,2,3,5,7,8,10},'Ionisch':{0,2,4,5,7,9,11},'Dorisch':{0,2,3,5,7,9,10},'Phrygisch':{0,1,3,5,7,8,10},'Lokrisch':{0,1,3,5,6,8,10},'Lydisch':{0,2,4,6,7,9,11},'Harmonisch':{0,2,3,5,7,8,11},'Chromatisch':set()}
def coll(h):return next(v for k,v in mode_steps.items() if h['mode'].startswith(k))
def seg(h,t,bar):
 n=int(t//bar)%h['period_bars']+1;return next(s for s in h['segments'] if s['start_bar']<=n<=s['end_bar'])
def allowed(h,s,p,fu):return p%12 in {t['pitch']%12 for t in s['tones']} or p%12 in coll(h) or p%12 in fu
# Authorization comes from the source's explicit printed F/U annotation; no arbitrary chromatic permission.
def auth(r):
 ps=r.get('pitches') or [n['pitch'] for n in r.get('notes',[])];return {p%12 for p,(_,f) in zip(ps,r.get('function_annotations',[])) if f in ('F','U')}
def pair(h,r,follows):
 if r['kind']=='B' and not r['pitches']:return dict(status='compatible_silence',h=h['id'],source=r['id'],follows=False)
 if r['kind']=='M':
  bar=3840;valid=[]
  for start in range(h['period_bars']):
   good=True
   for j,n in enumerate(r['notes']):
    at=start*bar+n['at'];a=seg(h,at,bar);root=a['root'] if follows else 0;p=n['pitch']+root;fu={(x+root)%12 for x in auth(r)}
    for tick in [at]+list(range((at//bar+1)*bar,at+n['duration'],bar)):
     if not allowed(h,seg(h,tick,bar),p,fu):good=False;break
    fn=r['function_annotations'][j][1] if j<len(r['function_annotations']) else None
    if fn=='V':
     if j+1>=len(r['notes']):good=False
     else:
      target=r['notes'][j+1];ts=seg(h,start*bar+target['at'],bar);tp=target['pitch']+(ts['root'] if follows else 0)
      if abs(tp-p) not in (1,2) or tp%12 not in {t['pitch']%12 for t in ts['tones'] if t['function']=='A'}:good=False
    if not good:break
   if good:valid.append(start+1)
  return dict(status='compatible_M_windows' if valid else 'rejected_M_windows',h=h['id'],source=r['id'],follows=follows,admissible_start_bars=valid,scope='Bar-aligned starts within harmonic cycle, entire note spans and V targets checked; no forced continuous repetition.')
 elif r.get('rhythm_id'):
  rh=by[r['rhythm_id']]
  if not rh['gate_mapping_known']:return dict(status='unresolved_gate_mapping',h=h['id'],source=r['id'],follows=follows)
  bar=960*4*int(rh['meter'].split('/')[0])//int(rh['meter'].split('/')[1]);period=r['cycle']['total_ticks'];horizon=math.lcm(period,h['period_bars']*bar)
  events=[(rep*rh['period_ticks']+hit['at'],hit['duration'],r['pitches'][(rep*len(rh['events'])+j)%len(r['pitches'])]) for rep in range(r['cycle']['rhythm_repetitions']) for j,hit in enumerate(rh['events'])]
 else:bar=3840;period=h['period_bars']*bar;horizon=period;events=[(0,period,r['pitches'][0])]
 if r['kind']=='B' and 'Dissonanzpedal' in (r.get('binding') or ''):return dict(status='compatible_authorized_pedal',h=h['id'],source=r['id'],follows=False,joint_ticks=horizon)
 for base in range(0,horizon,period):
  for at,length,p0 in events:
   at+=base;s=seg(h,at,bar);root=s['root'] if follows else 0;p=p0+root;fu={(a+root)%12 for a in auth(r)}
   checks=[at]+list(range((at//bar+1)*bar,at+length,bar))
   for t in checks:
    ss=seg(h,t,bar)
    if not allowed(h,ss,p,fu):return dict(status='rejected_under_H_context',h=h['id'],source=r['id'],follows=follows,counterexample=dict(at=t,pitch=p,harmonic_root=ss['root'],defined=sorted({n['pitch']%12 for n in ss['tones']}),collection=sorted(coll(h))),joint_ticks=horizon)
 # A local source V must remain stepwise to a chord A in the resulting context.
 if r['kind']=='M':
  for j,(degree,fn) in enumerate(r.get('function_annotations',[])):
   if fn!='V':continue
   if j+1>=len(events):return dict(status='unresolved_V_target',h=h['id'],source=r['id'],follows=follows)
   for base in range(0,horizon,period):
    at,du,p=events[j];ta,td,tp=events[j+1];a=seg(h,base+at,bar);b=seg(h,base+ta,bar);p+=a['root'] if follows else 0;tp+=b['root'] if follows else 0
    if abs(tp-p) not in (1,2) or tp%12 not in {n['pitch']%12 for n in b['tones'] if n['function']=='A'}:return dict(status='rejected_V_target',h=h['id'],source=r['id'],follows=follows)
 return dict(status='compatible_under_H_context',h=h['id'],source=r['id'],follows=follows,joint_ticks=horizon)
pairs=[]
for h in hs:
 for r in sources:
  opts=(False,True) if r['kind']=='Q' else (bool('akkordgebunden' in (r.get('binding') or '')),)
  for follow in opts:pairs.append(pair(h,r,follow))
# All IDs and formal counterexamples are inspectable; do not materialize all H/R/Q/B products.
def inside(r,point):return r['xyz_ranges'] is not None and all(lo-1e-9<=v<=hi+1e-9 for (lo,hi),v in zip(r['xyz_ranges'],point))
accepted=collections.defaultdict(set)
for p in pairs:
 if p['status'].startswith('compatible'):accepted[p['h']].add(p['source'])
points=list(itertools.product((1/6,.5,5/6),repeat=3))+list(itertools.product((.05,.95),repeat=3))
cells=[]
for point in points:
 active={k:[r for r in items if r['kind']==k and inside(r,point)] for k in ('H','R','Q','B','M')};domain_ids={r['id'] for rs in active.values() for r in rs};plans=[]
 for h in active['H']:
  good={r['id'] for k in ('Q','B','M') for r in active[k] if r['id'] in accepted[h['id']] and (not r.get('rhythm_id') or r['rhythm_id'] in domain_ids)}
  bs=sorted(i for i in good if by[i]['kind']=='B');qs=sorted(i for i in good if by[i]['kind']=='Q');ms=sorted(i for i in good if by[i]['kind']=='M')
  plans.append(dict(harmony=h['id'],bass_options=bs,sequencer_options=qs,motif_options=ms,may_be_pulseless=True,may_omit_melody=True,note='Pairwise compatibility under one H-context, not proven multi-role interaction or instrument readiness.'))
 studies=[r['id'] for r in items if r['kind'] in ('S','EF') and r['xyz'] and all(min(range(3),key=lambda j:abs(r['xyz'][k]-(1/6,.5,5/6)[j]))==min(range(3),key=lambda j:abs(point[k]-(1/6,.5,5/6)[j])) for k in range(3))]
 cells.append(dict(xyz=point,kind='cell' if len(cells)<27 else 'corner',formal_counts={k:len(v) for k,v in active.items()},compatible_harmony_bass_pairs=sum(len(p['bass_options']) for p in plans),compatible_harmony_sequence_pairs=sum(len(p['sequencer_options']) for p in plans),compatible_harmony_motif_pairs=sum(len(p['motif_options']) for p in plans),compatible_harmony_sequence_pairs_without_R_domain=sum(r['id'] in accepted[h['id']] for h in active['H'] for r in active['Q']),plans=plans,nearest_cell_studies=studies))
# Actual existing weight/Variety routines; JC validity rectangles are not implemented there.
code=r'''#include "ScoreEngine.h"
#include <iostream>
#include <vector>
using namespace stromscore;
int main(){int n,m;std::cin>>n>>m;std::vector<Wendung>w(n,wendungAt(GenreScore,0));for(auto&a:w)std::cin>>a.x>>a.y>>a.z;for(int p=0;p<m;++p){Settings s;std::cin>>s.x>>s.y>>s.z;for(float v:{0.f,.5f,1.f}){s.variety=v;float best=0;std::vector<float>a(n);for(int i=0;i<n;++i){a[i]=Generator::weight(w[i],s);best=std::max(best,a[i]);}std::cout<<p<<' '<<v;for(int i=0;i<n;++i)if(a[i]>=Generator::keepRatio(s)*best)std::cout<<' '<<i;std::cout<<'\n';}}}
'''
with tempfile.TemporaryDirectory() as tmp:
 t=Path(tmp);(t/'p.cpp').write_text(code);subprocess.run(['c++','-O2','-std=c++17','-I',str(ROOT/'Source'),str(t/'p.cpp'),'-o',str(t/'p')],check=True)
 payload=f'{len(hs)} {len(points)}\n'+'\n'.join(' '.join(map(str,h['xyz'])) for h in hs)+'\n'+'\n'.join(' '.join(map(str,p)) for p in points)
 out=subprocess.check_output([str(t/'p')],input=payload.encode()).decode()
 for line in out.splitlines():
  row=line.split();idx=int(row[0]);cells[idx].setdefault('existing_anchor_filter',[]).append(dict(variety=float(row[1]),harmony_ids=[hs[int(i)]['id'] for i in row[2:]],scope='Unchanged engine weight/pick cutoff on all88JCanchors; source validity rectangles NOT applied, no runtime import.'))
# Reproduce the supplied formal counts independently from its Markdown table.
quality=(HERE/'JC_Qualitaetspruefung.md').read_text(encoding='utf-8');quality_cells=[];quality_corners=[]
for line in quality.splitlines():
 if not line.startswith('|'):continue
 cols=[v.strip() for v in line.strip('|').split('|')]
 if len(cols)==9 and all(c in ('0,17','0,50','0,83') for c in cols[:3]):quality_cells.append(cols)
 if len(cols)==6 and '/' in cols[0] and all(c.strip() in ('0,05','0,95') for c in cols[0].split('/')):quality_corners.append(cols)
assert len(quality_cells)==27 and len(quality_corners)==8
for source,c in zip(quality_cells,cells[:27]):
 assert list(c['formal_counts'].values())==list(map(int,source[3:8]))
 assert len(c['nearest_cell_studies'])==int(source[8])
for source,c in zip(quality_corners,cells[27:]):assert list(c['formal_counts'].values())==list(map(int,source[1:]))
report=dict(base='4937722',formal_counts_match_quality_report=True,method='All H×Q/B/M pairs, entire printed harmonic/pitch/rhythm joint cycles; V-target checks; then XYZ rectangles and referenced R rectangles at27cells+8corners. Actual existing C++ weight/Variety separately evaluated.',limitations=['Formal under printed H context, not aesthetic hearing proof.','Local source collections beyond H are not silently unioned; rejected pairs may need explicit alternative scoped authorization.','No automatic transposition/voicing/role allocation to repair incompatibility.','Pairwise compatibility does not prove simultaneous Q+B+M or independent-pedal implementation.','Pulse-/melody-free output is valid; no requirement to populate Q/M in every cell.','No JC sources are active in the current engine.'],pair_summary=dict(collections.Counter(p['status'] for p in pairs)),pair_results_file='PAIR_COMPATIBILITY.jsonl',cells=cells)
(HERE/'PAIR_COMPATIBILITY.jsonl').write_text(''.join(json.dumps(p,ensure_ascii=False,separators=(',',':'))+'\n' for p in pairs))
(HERE/'XYZ_COMPATIBILITY.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n')
print('Pairs',report['pair_summary']);print('cells without Q',[c['xyz'] for c in cells[:27] if c['compatible_harmony_sequence_pairs']==0]);print('cells without study',sum(not c['nearest_cell_studies'] for c in cells[:27]))
