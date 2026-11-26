"""Offline XYZ simulation using the actual Generator::weight and keepRatio functions."""
from pathlib import Path
import json,tempfile,subprocess
p=Path(__file__).resolve().parent;root=p.parents[2];r=json.loads((p/'TECHNICAL_INVENTORY.json').read_text());h=[x for x in r['inventory'] if x['id'][3]=='H'];cat=json.loads((root/'data/harmony/catalog.json').read_text());by={t['id']:t for t in cat['templates']}
pools={'free_score':[dict(id=str(i),xyz=by[i]['xyz']) for i in cat['pools']['score']], 'williams_all':h,'williams_data_fit':[x for x in h if x['harmonic_data_fit']]}
code=r'''#include "ScoreEngine.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace stromscore;
int main(){int n;std::cin>>n;std::vector<Wendung> ws(n,wendungAt(GenreScore,0));for(auto& w:ws)std::cin>>w.x>>w.y>>w.z;for(float variety:{0.f,.5f,1.f})for(int i=0;i<=20;++i)for(int j=0;j<=20;++j)for(int k=0;k<=20;++k){Settings s;s.x=i/20.f;s.y=j/20.f;s.z=k/20.f;s.variety=variety;float best=0;std::vector<float>w(n);for(int a=0;a<n;++a){w[a]=Generator::weight(ws[a],s);best=std::max(best,w[a]);}int count=0;std::cout<<variety<<' '<<i<<' '<<j<<' '<<k;for(int a=0;a<n;++a)if(w[a]>=Generator::keepRatio(s)*best){++count;std::cout<<' '<<a;}std::cout<<'\n';}}
'''
with tempfile.TemporaryDirectory() as t:
 t=Path(t);(t/'p.cpp').write_text(code);subprocess.run(['c++','-std=c++17','-O0','-I',str(root/'Source'),str(t/'p.cpp'),'-o',str(t/'probe')],check=True)
 results={}
 for name,items in pools.items():
  raw=subprocess.check_output([str(t/'probe')],input=(str(len(items))+'\n'+'\n'.join(' '.join(map(str,x['xyz'])) for x in items)).encode()).decode().splitlines();rows=[]
  for v in (0,.5,1):
   group=[l.split() for l in raw if float(l.split()[0])==v];counts=[];distances=[];reachable=set();corners={};worst=[]
   for l in group:
    xyz=[int(x)/20 for x in l[1:4]];idx=list(map(int,l[4:]));counts.append(len(idx));reachable.update(idx)
    d=min(sum(a*(x-y)**2 for a,x,y in zip((1,.49,.64),xyz,it['xyz']))**.5 for it in items);distances.append(d)
    if all(x in (0,1) for x in xyz):corners['/'.join(map(str,xyz))]=dict(candidates=len(idx),nearest_weighted_distance=d,ids=[items[i]['id'] for i in idx])
    worst.append((d,xyz,len(idx)))
   rows.append(dict(variety=v,points=len(group),min_candidates=min(counts),mean_candidates=sum(counts)/len(counts),max_candidates=max(counts),single_candidate_points=counts.count(1),nearest_distance_max=max(distances),distance_over_035=sum(d>.35 for d in distances),reachable=len(reachable),unreached=[items[i]['id'] for i in range(len(items)) if i not in reachable],corners=corners,worst=sorted(worst,reverse=True)[:8]))
  results[name]=rows
 (p/'XYZ_COVERAGE.json').write_text(json.dumps(results,ensure_ascii=False,indent=2)+'\n')
 print(json.dumps({k:[{a:b for a,b in x.items() if a not in ('corners','worst','unreached')} for x in v] for k,v in results.items()},indent=2))
