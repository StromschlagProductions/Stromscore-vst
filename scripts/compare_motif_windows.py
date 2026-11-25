"""Protect accompaniment; explain every changed Arp attack by actual reservation decisions.

The two offline header copies log the existing motifWindow condition verbatim.
No selection seam, disabled engine feature or alternative performance is used.
"""
import argparse,collections,hashlib,json,pathlib,subprocess,tempfile
from reference_headers import header_snapshot
root=pathlib.Path(__file__).resolve().parents[1]
p=argparse.ArgumentParser();p.add_argument('--output',required=True);p.add_argument('--reference',default='9a8d01c');p.add_argument('--compiler',default='c++');p.add_argument('--current-headers',type=pathlib.Path);a=p.parse_args();out=pathlib.Path(a.output);out.mkdir(parents=True,exist_ok=True)
source=root/'docs/development/motif-audit/probe.cpp'
cases=[(genre,profile,path,var) for genre,profile in ((0,0),(0,1),(1,0)) for path in (0,1,3,6,7) for var in (1,)] + [(0,0,3,3)]
def decode(raw):return [tuple(map(int,l.split(b','))) for l in raw.splitlines()]
def balanced(events):
 active={};voices=collections.Counter();previous=0
 for sample,o,ch,n,v,kind in events:
  assert not(voices[7] and voices[8] and sample>previous),('competing melodic roles',previous,sample)
  previous=sample
  if kind:continue
  k=ch,n
  if v:assert k not in active,('double',k,sample);active[k]=(o,sample);voices[o]+=1
  else:
   assert k in active,('orphan',k,sample)
   owner,begin=active.pop(k);assert sample>begin,('empty gate',k,sample);voices[owner]-=1
 assert not active,('hanging',active)
with tempfile.TemporaryDirectory() as tmp:
 tmp=pathlib.Path(tmp);executables=[]
 for label,rev in [('before',a.reference),('after',None)]:
  d=tmp/label;d.mkdir();headers={p.name:p.read_bytes() for p in a.current_headers.glob('*.h')} if rev is None and a.current_headers else header_snapshot(root,rev)
  for name,data in headers.items():
   if name=='ScoreEngine.h':
    data=data.replace(b'#pragma once',b'#pragma once\n#include <cstdio>',1)
    needle=b'!motifWindow(p,s).contains(time)';assert data.count(needle)==1
    data=data.replace(needle,b'!([&]{const auto auditWindow=motifWindow(p,s);const bool reserved=auditWindow.contains(time);std::fprintf(stderr,"R,%lld,%d\\n",static_cast<long long>(time.value),int(reserved));return reserved;}())',1)
   (d/name).write_bytes(data)
  exe=d/'probe';subprocess.run([a.compiler,'-std=c++17','-O2','-I',str(d),str(source),'-o',str(exe)],check=True);executables.append(exe)
 results=[]
 for genre,profile,path,var in cases:
  name=f'g{genre}-p{profile}-xyz{path}-v{var}';versions=[]
  for label,exe in zip(('before','after'),executables):
   prefix=out/f'{name}-{label}';r=subprocess.run([str(exe),str(genre),str(profile),str(path),str(var),'0','3','0','0','0','128','512','0',str(prefix),'2'],capture_output=True,check=True)
   raw=prefix.with_suffix('.csv').read_bytes();events=decode(raw);balanced(events)
   reservations={int(t):bool(int(b)) for tag,t,b in (l.split(b',') for l in r.stderr.splitlines())}
   versions.append((events,reservations,hashlib.sha256(raw).hexdigest()))
  (old,ro,ho),(new,rn,hn)=versions
  protect=lambda events:collections.Counter(e for e in events if e[1] not in (4,7,8))
  assert protect(old)==protect(new),('pad/bass/accents/CC changed',name,list((protect(old)-protect(new)).elements())[:4],list((protect(new)-protect(old)).elements())[:4])
  attacks=lambda es:collections.Counter(e for e in es if e[1]==4 and e[4] and e[5]==0)
  oa,na=attacks(old),attacks(new);removed=list((oa-na).elements());added=list((na-oa).elements())
  for e in removed:
   t=round(e[0]/30);assert ro.get(t) is False and rn.get(t) is True,('removed Arp attack is not reservation-only',name,e,ro.get(t),rn.get(t))
  for e in added:
   t=round(e[0]/30);assert ro.get(t) is True and rn.get(t) is False,('added Arp attack is not reservation-only',name,e,ro.get(t),rn.get(t))
  results.append(dict(case=name,reference_sha256=ho,after_sha256=hn,removed_arpeggio_attacks=len(removed),added_arpeggio_attacks=len(added),removed=removed,added=added,protected_events=sum(protect(new).values())))
  print(name,'Arp -',len(removed),'+',len(added),'protected',sum(protect(new).values()),flush=True)
 (out/'comparison.json').write_text(json.dumps(dict(reference=a.reference,cases=results),indent=2)+'\n')
print('Every changed Arp attack explained by the actual existing reservation condition; pad/bass/accents/CC unchanged.')
