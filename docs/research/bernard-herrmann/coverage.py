"""Offline selection diagnostics. Compiles the unchanged Generator weight/Variety functions.
No generated runtime catalog and no HE template activation. Compiler required.
"""
from pathlib import Path
import json, tempfile, subprocess, math, collections, re
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[2]
items=json.loads((HERE/'TECHNICAL_INVENTORY.json').read_text())['templates'];hs=[r for r in items if r['id'][3]=='H'];catalog=json.loads((ROOT/'data/harmony/catalog.json').read_text());by={r['id']:r for r in catalog['templates']}
pools={'current_score_geometry':[dict(id=str(i),xyz=by[i]['xyz']) for i in catalog['pools']['score']],'he_all_geometry':hs,'he_chord_data_fit':[h for h in hs if h['harmonic_data_fit']],'he_complete_D_A':[h for h in hs if h['classification'] in ('D','A')]}
code=r'''#include "ScoreEngine.h"
#include <iostream>
#include <vector>
using namespace stromscore;
int main(){int n;std::cin>>n;std::vector<Wendung> ws(n,wendungAt(GenreScore,0));for(auto& w:ws)std::cin>>w.x>>w.y>>w.z;
for(float v:{0.f,.5f,1.f})for(int i=0;i<=20;++i)for(int j=0;j<=20;++j)for(int k=0;k<=20;++k){Settings s;s.x=i/20.f;s.y=j/20.f;s.z=k/20.f;s.variety=v;float best=0,wd=9,ed=9;std::vector<float>w(n);
for(int a=0;a<n;++a){w[a]=Generator::weight(ws[a],s);best=std::max(best,w[a]);float dx=ws[a].x-s.x,dy=ws[a].y-s.y,dz=ws[a].z-s.z;wd=std::min(wd,std::sqrt(dx*dx+.49f*dy*dy+.64f*dz*dz));ed=std::min(ed,std::sqrt(dx*dx+dy*dy+dz*dz));}
std::cout<<v<<' '<<i<<' '<<j<<' '<<k<<' '<<wd<<' '<<ed;for(int a=0;a<n;++a)if(w[a]>=Generator::keepRatio(s)*best)std::cout<<' '<<a;std::cout<<'\n';}}
'''
results={}
with tempfile.TemporaryDirectory() as tmp:
 t=Path(tmp);(t/'probe.cpp').write_text(code);subprocess.run(['c++','-std=c++17','-O2','-I',str(ROOT/'Source'),str(t/'probe.cpp'),'-o',str(t/'probe')],check=True)
 for name,pool in pools.items():
  payload=str(len(pool))+'\n'+'\n'.join(' '.join(map(str,r['xyz'])) for r in pool)
  out=subprocess.check_output([str(t/'probe')],input=payload.encode()).decode();groups=collections.defaultdict(list)
  for line in out.splitlines():
   cols=line.split();groups[float(cols[0])].append(dict(xyz=[int(n)/20 for n in cols[1:4]],weighted_distance=float(cols[4]),absolute_distance=float(cols[5]),indices=list(map(int,cols[6:]))))
  rows=[]
  for variety,ps in groups.items():
   counts=[len(p['indices']) for p in ps];reachable={a for p in ps for a in p['indices']};corners={}
   for p in ps:
    if all(x in (0,1) for x in p['xyz']):corners['/'.join(str(x) for x in p['xyz'])]=dict(candidates=len(p['indices']),ids=[pool[i]['id'] for i in p['indices']],weighted_distance=p['weighted_distance'],absolute_distance=p['absolute_distance'])
   rows.append(dict(variety=variety,points=len(ps),min_candidates=min(counts),mean_candidates=sum(counts)/len(ps),max_candidates=max(counts),single_candidate_points=counts.count(1),fewer_than_three=sum(n<3 for n in counts),weighted_distance_max=max(p['weighted_distance'] for p in ps),absolute_distance_max=max(p['absolute_distance'] for p in ps),distance_over_035=sum(p['weighted_distance']>.35 for p in ps),reachable=len(reachable),unreached=[p['id'] for i,p in enumerate(pool) if i not in reachable],corners=corners,worst=sorted([dict(xyz=p['xyz'],weighted_distance=p['weighted_distance'],absolute_distance=p['absolute_distance'],candidates=len(p['indices'])) for p in ps],key=lambda p:p['weighted_distance'],reverse=True)[:8]))
  results[name]=dict(pool_size=len(pool),summary=rows)
# Explicit source semantics. No silent numeric conversion of soft or conditional colour text.
colour=[]
for r in items:
 if r['id'][3] not in 'RBMP':continue
 raw=r['colour_scope_raw'] or ''
 if 'färbungsunabhängig' in raw or re.search(r'alle X',raw,re.I):kind='independent'
 elif any(x in raw.lower() for x in ['bevorzug','eher','für dunkle','in hellen','in dunklen']):kind='soft_or_conditional'
 else:kind='restricted_or_clarify'
 colour.append(dict(id=r['id'],kind=kind,raw=raw,anchor_x=r['xyz'][0]))
# Importing every source anchor into the current spherical role selection is an upper bound:
# no capability, harmonic, register, active-role or material-lock rejection included.
role_reach=[]
for kind,radius2 in [('R',.16),('B',.16),('M',.0625)]:
 sources=[r for r in items if r['id'][3]==kind and next(c['kind'] for c in colour if c['id']==r['id'])=='independent']
 for x in (0,.25,.5,.75,1):
  blocked=[r['id'] for r in sources if (x-r['xyz'][0])**2>radius2]
  role_reach.append(dict(kind=kind,x=x,independent_sources=len(sources),excluded_even_at_own_yz=len(blocked),excluded_ids=blocked,radius_squared=radius2))
report=dict(engine_commit='023b0a6',method='21³ points per pool and Variety0/.5/1; actual Generator::weight/keepRatio; pick cutoff without candidates-display epsilon; neutral source preferences (no invented HE weights). Pools separate, not a simulated active combined catalog.',scope='Geometry only: several candidates may be same chord material or require unavailable musical facilities. No production selection or hearing proof.',harmonic_pools=results,colour_scopes=colour,colour_summary={k:dict(collections.Counter(c['kind'] for c in colour if c['id'][3]==k)) for k in 'RBMP'},role_anchor_diagnostics=role_reach)
(HERE/'XYZ_COVERAGE.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n')
for n,v in results.items():print(n,v['pool_size'],[(r['variety'],round(r['mean_candidates'],2),r['single_candidate_points'],round(r['weighted_distance_max'],3)) for r in v['summary']])
print(report['colour_summary'])
