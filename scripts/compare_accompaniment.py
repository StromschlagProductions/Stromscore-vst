#!/usr/bin/env python3
"""Compare complete note/CC events against 237b415; emit reproducible CSV evidence."""
import argparse, collections, hashlib, json, pathlib, subprocess, tempfile
p=argparse.ArgumentParser();p.add_argument('--probe',required=True);p.add_argument('--compiler',default='c++');p.add_argument('--output',required=True);a=p.parse_args()
root=pathlib.Path(__file__).resolve().parents[1];out=pathlib.Path(a.output);out.mkdir(parents=True,exist_ok=True)
names=['dialog','melody','motifs-off','pop-rock','unplayable-melody','melody-motif-off','dialog-arp-answer','melody-dialog-answer','shared-channel','muted-dialog','solo-arp','buildup','chord-changes','three-four-swing','catalog-harmony','both-motifs-off','seek-loop','scene-restart','auto-melody-dialog-answer']
def run(exe,case,profile,block=512,seed=None):
    args=[str(exe),str(case),str(profile),str(block)]
    if seed is not None:args.append(str(seed))
    raw=subprocess.check_output(args)
    return raw,[tuple(map(int,line.split(b','))) for line in raw.splitlines()]
def attacks(events,output):return [e for e in events if e[4]==0 and e[3]>0 and e[5]==output]
def nonarp(events):return sorted(e for e in events if e[5]!=4)
def digest(raw):return hashlib.sha256(raw).hexdigest()
summary=[]
with tempfile.TemporaryDirectory(prefix='stromscore-coordination-') as temp:
    temp=pathlib.Path(temp)
    headers=subprocess.check_output(['git','ls-tree','-r','--name-only','237b415','Source'],cwd=root,text=True).splitlines()
    for name in headers:
        if name.endswith('.h'):
            (temp/pathlib.Path(name).name).write_bytes(subprocess.check_output(['git','show',f'237b415:{name}'],cwd=root))
    reference=temp/'before'
    subprocess.run([a.compiler,'-std=c++17','-O2','-I',str(temp),str(root/'tools/accompaniment_probe.cpp'),'-o',str(reference)],check=True)
    for profile in range(3):
        for case,name in enumerate(names):
            before_raw,before=run(reference,case,profile)
            after_raw,after=run(a.probe,case,profile)
            if nonarp(before)!=nonarp(after):
                (out/'failed-before.csv').write_bytes(before_raw);(out/'failed-after.csv').write_bytes(after_raw)
                diff=list((collections.Counter(nonarp(before))-collections.Counter(nonarp(after))).elements())
                raise AssertionError((name,profile,'motif/other output changed',diff[:8]))
            old=attacks(before,4);new=attacks(after,4)
            removed=list((collections.Counter(old)-collections.Counter(new)).elements())
            assert not collections.Counter(new)-collections.Counter(old),(name,'new arp attacks')
            unchanged=case in [2,3,4,5,6,7,8,9,10,15]
            if unchanged:assert before==after,(name,profile,'unrelated context changed')
            if case in [0,1,12,13,14,16,17]:assert removed,(name,profile,'no audible coordination')
            # With static 4/4 harmony, the exact envelope of actually emitted motif notes
            # independently predicts every deleted attack; pauses between phrases stay unchanged.
            if case in [0,1,12,14,18]:
                outputs=[7,8] if case in [1,18] else [7]
                by_phrase=collections.defaultdict(list)
                for e in before:
                    if e[4]==0 and e[5] in outputs:by_phrase[e[0]//768000].append(e)
                windows=[]
                for phrase,es in by_phrase.items():
                    ons=[e[0] for e in es if e[3]>0]
                    if not ons:continue
                    # Include phrase-end note-offs at the boundary in the preceding envelope.
                    start=min(ons);ends=[e[0] for e in before if e[4]==0 and e[5] in outputs and e[3]==0 and start<=e[0]<=phrase*768000+(288000 if case==18 else 192000)]
                    windows.append((start,max(ends)))
                expected=[e for e in old if any(lo<=e[0]<hi for lo,hi in windows)]
                assert sorted(removed)==sorted(expected),(name,profile,'reservation differs from actual motif envelope')
            # All MIDI events outside the bounded window plus any released deleted arp note
            # are covered by exact surviving note-span comparison below.
            def spans(es):
                active={};result=[]
                for e in es:
                    if e[4] or e[5]!=4:continue
                    key=e[1],e[2]
                    if e[3]>0:assert key not in active;active[key]=e
                    else:
                        assert key in active,(name,'unbalanced arp')
                        n=active.pop(key);result.append((n,e[0]))
                assert not active
                return collections.Counter(result)
            if case!=8:assert not spans(after)-spans(before),(name,'surviving arp span changed')
            for block in [127,8192]:
                raw,_=run(a.probe,case,profile,block)
                assert raw==after_raw,(name,profile,block,'block-dependent MIDI')
            row=dict(profile=profile,case=name,before_arp=len(old),after_arp=len(new),removed=len(removed),motif_attacks=len(attacks(after,7))+len(attacks(after,8)),before_sha256=digest(before_raw),after_sha256=digest(after_raw))
            summary.append(row)
            if profile==0 and case in [0,1,18]:
                for suffix,raw in [('before',before_raw),('after',after_raw)]:
                    (out/f'{name}-{suffix}.csv').write_bytes(b'sample,channel,note,velocity,type,output\n'+raw)
                (out/f'{name}-removed.csv').write_text('sample,channel,note,velocity,type,output\n'+''.join(','.join(map(str,e))+'\n' for e in sorted(removed)))
    # Additional motif templates/counts and variation values; no duplicated music engine in tests.
    for seed in range(16):
        for case in [0,1]:
            before_raw,before=run(reference,case,0,seed=seed)
            after_raw,after=run(a.probe,case,0,seed=seed)
            assert nonarp(before)==nonarp(after),(case,seed,'motif template regression')
            old=attacks(before,4);new=attacks(after,4)
            assert not collections.Counter(new)-collections.Counter(old)
            assert len(new)<len(old)
            summary.append(dict(profile=0,case=names[case],seed=seed,variation=seed%16+1,
                before_arp=len(old),after_arp=len(new),removed=len(old)-len(new),
                motif_attacks=len(attacks(after,7))+len(attacks(after,8)),
                before_sha256=digest(before_raw),after_sha256=digest(after_raw)))
(out/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
print(f'{len(summary)} baseline comparisons; {len(names)*6} alternate-block comparisons passed. Evidence: {out}')
for row in summary[:len(names)]:print(row['case'],row['before_arp'],row['after_arp'],row['removed'],row['motif_attacks'])
