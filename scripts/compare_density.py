#!/usr/bin/env python3
"""Pinned A/B MIDI comparison plus same-energy, density-mask-disabled scientific control."""
from reference_headers import header_snapshot
import argparse, collections, hashlib, json, pathlib, subprocess, tempfile
p=argparse.ArgumentParser();p.add_argument('--probe',required=True);p.add_argument('--compiler',default='c++');p.add_argument('--output',required=True);a=p.parse_args()
root=pathlib.Path(__file__).resolve().parents[1];out=pathlib.Path(a.output);out.mkdir(parents=True,exist_ok=True)
names=['high-steady','high-build','low-build','manual-build','auto-fade','manual-fade','open-end','hard-end','pop-steady','pop-build','pop-fade','protected-motif','melody-build','seek-loop','restart','manual-fade-request','low-steady','catalog-steady','catalog-build','passing-fade','velocity-fade']
def run(exe,case,profile,block=512):
    r=subprocess.run([str(exe),str(case),str(profile),str(block)],capture_output=True,check=True)
    return r.stdout,[tuple(map(int,line.split(b','))) for line in r.stdout.splitlines()],r.stderr

def ons(events):return [e for e in events if e[4]==0 and e[3]>0]
def key(e):return e[0],e[1],e[2],e[5]
def cc(es):return sorted(e for e in es if e[4]!=0)
def motif(es):return sorted(e for e in es if e[5] in [7,8])
def digest(raw):return hashlib.sha256(raw).hexdigest()
def spans(es):
    active={};result=[]
    for e in es:
        if e[4]:continue
        k=e[1],e[2]
        if e[3]>0:assert k not in active;active[k]=e
        else:
            assert k in active,('unowned note-off',e)
            on=active.pop(k);result.append((on,e[0]))
    assert not active
    return collections.Counter(result)
summary=[]
with tempfile.TemporaryDirectory(prefix='stromscore-density-') as temp:
    temp=pathlib.Path(temp)
    for folder,revision in [('before','2f4dd47'),('control',None)]:
        dest=temp/folder;dest.mkdir()
        for name,data in header_snapshot(root,revision).items():
            if not revision and name=='ScoreEngine.h':
                assert b'composition::EventDensity{dens}' in data
                data=data.replace(b'composition::EventDensity{dens}',b'composition::EventDensity{1.f}')
            (dest/name).write_bytes(data)
        # The scientific control changes only density, keeping the probe's feature controls identical.
        flags=['-DBASS_REGRESSION_CONTROL=1'] if revision is None else []
        subprocess.run([a.compiler,'-std=c++17','-O1',*flags,'-I',str(dest),str(root/'tools/density_probe.cpp'),'-o',str(temp/f'{folder}-probe')],check=True)
    for profile in range(3):
        for case,name in enumerate(names):
            br,b,bh=run(temp/'before-probe',case,profile)
            ar,after,ah=run(a.probe,case,profile)
            cr,control,ch=run(temp/'control-probe',case,profile)
            if case in (8,9,10):
                checked=[b'\n'.join(b','.join(line.split(b',')[:4]) for line in h.splitlines()) for h in (ah,bh,ch)]
                assert checked[0]==checked[1]==checked[2],(name,profile,'harmonic selection changed')
            else:
                # Internal identity hashes changed with PPQ storage; compare musical data and note counts.
                stable=lambda h:[v[:4]+v[5:6]+v[7:8] for v in (line.split(b',') for line in h.splitlines())]
                assert stable(ah)==stable(bh)==stable(ch),(name,profile,'harmonic selection/material count changed')
            assert cc(after)==cc(control),(name,'density changed expression CC')
            assert motif(after)==motif(control),(name,'density fragmented thematic material')
            assert not spans(after)-spans(control),(name,'remaining note pitch/velocity/duration changed by density')
            old=ons(b);new=ons(after);full=ons(control)
            # No density at all: complete MIDI must remain byte-identical, including intentional open-end energy.
            if case in [0,6,7,8,16,17]:
                assert ar==cr,(name,'undiluted density control')
                if case==8:assert ar==br,(name,'Pop regression')
                else:assert [e for e in b if e[0]<16*48000]==[e for e in after if e[0]<16*48000],(name,'undiluted introduction changed')
            if case in [1,3,4,5,9,10,13,14,18]:assert len(new)<len(full),(name,'density mask unused')
            oldkeys={key(e):e for e in old};newkeys={key(e):e for e in new}
            removed=[e for e in old if key(e) not in newkeys]
            added=[e for e in new if key(e) not in oldkeys]
            vel=[(e,oldkeys[key(e)][3]) for e in new if key(e) in oldkeys and e[3]!=oldkeys[key(e)][3]]
            for block in [127,8192]:
                raw,_,h=run(a.probe,case,profile,block)
                assert raw==ar and h==ah,(name,profile,block,'nondeterministic blocks/transport')
            summary.append(dict(profile=profile,case=name,before_ons=len(old),after_ons=len(new),same_energy_unthinned_ons=len(full),density_removed=len(full)-len(new),before_only=len(removed),after_only=len(added),changed_velocity=len(vel),velocity_increases=sum(e[3]>old for e,old in vel),velocity_decreases=sum(e[3]<old for e,old in vel),before_sha256=digest(br),after_sha256=digest(ar),harmonic_material_sha256=digest(ah)))
            if profile==0:
                for suffix,raw in [('before',br),('after',ar),('unthinned-control',cr)]:
                    (out/f'{name}-{suffix}.csv').write_bytes(b'sample,channel,note,velocity,type,output\n'+raw)
                for suffix,es in [('removed',removed),('added',added),('density-removed',[e for e in full if key(e) not in newkeys])]:
                    (out/f'{name}-{suffix}.csv').write_text('sample,channel,note,velocity,type,output\n'+''.join(','.join(map(str,e))+'\n' for e in es))
(out/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
print(f'{len(summary)} baseline/control comparisons and {len(summary)*2} alternate-block comparisons passed.')
for r in summary[:len(names)]:print(r['case'],r['before_ons'],r['after_ons'],r['same_energy_unthinned_ons'],r['density_removed'],r['changed_velocity'])
