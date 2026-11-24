#!/usr/bin/env python3
"""Actual MIDI and preplanned target/breath evidence against 0cc30c2."""
from reference_headers import header_snapshot
import argparse,collections,hashlib,json,pathlib,subprocess,tempfile
p=argparse.ArgumentParser();p.add_argument('--probe',required=True);p.add_argument('--compiler',default='c++');p.add_argument('--output',required=True);a=p.parse_args()
root=pathlib.Path(__file__).resolve().parents[1];out=pathlib.Path(a.output);out.mkdir(parents=True,exist_ok=True)
names=['held-low','held-high','bright','dark-minor','changes-high','changes-low','unrest-high','unrest-medium','single-pitch-fallback','passing','motif-protected','melody-protected','handoff-protected','dialogue-arp-protected','pop-protected','seek-loop','restart','still','one-bar','narrow-fallback','octave-range','buildup-fade','catalog','muted','below-threshold','short-meter-fallback','scene-boundary','detached','unequal-durations']
def run(exe,case,profile,block=512):
    r=subprocess.run([str(exe),str(case),str(profile),str(block)],capture_output=True,check=True)
    es=[tuple(map(int,line.split(b','))) for line in r.stdout.splitlines()]
    h=[line for line in r.stderr.splitlines() if line.startswith(b'H,')]
    plans=[list(map(int,line[2:].split(b','))) for line in r.stderr.splitlines() if line.startswith(b'P,')]
    return r.stdout,es,h,plans

def ons(es):return [e for e in es if e[4]==0 and e[3]>0 and e[5]==7]
def spans(es):
    active={};spans=[]
    for e in es:
        if e[4]!=0:continue
        key=e[1],e[2]
        if e[3]>0:assert key not in active;active[key]=e
        else:
            assert key in active,('unowned release',e)
            n=active.pop(key)
            if n[5]==7:spans.append((n[0],e[0],n[2]))
    assert not active
    return spans

def sounding(es):
    events=[]
    for begin,end,_ in spans(es):events.extend([(begin,1),(end,-1)])
    count=0;last=0;total=0
    for tick,delta in sorted(events):
        if count:total+=tick-last
        count+=delta;last=tick
    return round(total/(48*48000),6)
summary=[];closings=set()
with tempfile.TemporaryDirectory(prefix='stromscore-phrases-') as temp:
    temp=pathlib.Path(temp)
    for name,data in header_snapshot(root,'0cc30c2').items():(temp/name).write_bytes(data)
    before=temp/'before'
    subprocess.run([a.compiler,'-std=c++17','-O1','-I',str(temp),str(root/'tools/phrase_probe.cpp'),'-o',str(before)],check=True)
    for profile in range(3):
        for case,name in enumerate(names):
            br,b,bh,_=run(before,case,profile)
            ar,after,ah,plans=run(a.probe,case,profile)
            # Internal identity hashes changed with PPQ storage; compare musical data and note counts.
            assert ([h.split(b',')[:5] for h in bh]==[h.split(b',')[:5] for h in ah] if case==14 else [h.split(b',')[:5]+h.split(b',')[6:7]+h.split(b',')[8:9] for h in bh]==[h.split(b',')[:5]+h.split(b',')[6:7]+h.split(b',')[8:9] for h in ah]),(name,'harmonic plan or motif count changed')
            thematic=case in [10,12,13]
            protected={4,7,8} if thematic else {7}
            assert sorted(e for e in b if e[5] not in protected)==sorted(e for e in after if e[5] not in protected),(name,'other layer/coordination/density changed')
            if thematic:assert [e for e in b if e[0]<16*48000]==[e for e in after if e[0]<16*48000],(name,'motif introduction changed')
            if case in [8,11,14,19,23,24,25]:assert ar==br,(name,'protected context changed')
            old,new=ons(b),ons(after)
            if old:assert new,(name,'counter voice vanished')
            note_spans=spans(after)
            if case not in [15,16]:
                for plan in plans:
                    begin,end,goal,arrival,breath,ending,count=plan[:7]
                    ns=[plan[7+i*3:10+i*3] for i in range(count)]
                    octave=12 if case==20 else 0
                    assert ns[-1][0]==arrival and ns[-1][2]==goal
                    expected=[(n[0]*6000,n[2]+octave) for n in ns]
                    actual=[(e[0],e[2]) for e in new if begin*6000<=e[0]<end*6000]
                    assert actual==expected,(name,plan,actual,'MIDI diverged from declared plan')
                    assert not any(lo<end*6000 and hi>breath*6000 for lo,hi,_ in note_spans),(name,'missing breath')
                    assert any(e[0]==arrival*6000 and e[2]==goal+octave for e in new),(name,'goal not reached')
                    closings.add(ns[-1][2]-ns[-2][2])
            for block in [127,8192]:
                raw,_,h,ps=run(a.probe,case,profile,block)
                assert raw==ar and h==ah and ps==plans,(name,profile,block,'block-dependent plan or MIDI')
            if case in [0,1,2,3,4,5,6,7,17,18,20,21,22,26,27,28]:assert plans,(name,'no planned phrase')
            row=dict(profile=profile,case=name,before_ons=len(old),after_ons=len(new),before_sounding=sounding(b),after_sounding=sounding(after),plans=plans[:4],before_notes=[(round(e[0]/6000,3),e[2]) for e in old[:20]],after_notes=[(round(e[0]/6000,3),e[2]) for e in new[:20]],before_sha256=hashlib.sha256(br).hexdigest(),after_sha256=hashlib.sha256(ar).hexdigest())
            summary.append(row)
            if profile==0:
                for suffix,raw in [('before',br),('after',ar)]:
                    (out/f'{name}-{suffix}.csv').write_bytes(b'sample,channel,note,velocity,type,output\n'+raw)
assert len(closings)>=3,('insufficient closing diversity',closings)
(out/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
print(f'{len(summary)} pinned comparisons and {len(summary)*2} alternate-block comparisons passed; closing intervals: {sorted(closings)}')
for r in summary[:len(names)]:print(r['case'],r['before_ons'],r['after_ons'],r['before_sounding'],r['after_sounding'])
