#!/usr/bin/env python3
"""128-bar actual-material recurrence and coordinated MIDI regression against 920d388."""
import argparse,collections,hashlib,json,pathlib,struct,subprocess,tempfile
p=argparse.ArgumentParser();p.add_argument('--probe',required=True);p.add_argument('--compiler',default='c++');p.add_argument('--output',required=True);a=p.parse_args()
root=pathlib.Path(__file__).resolve().parents[1];out=pathlib.Path(a.output);out.mkdir(parents=True,exist_ok=True)
names=['quiet','active','bright','dark-unrest','changes','changes-quiet','catalog','one-bar-cycle','four-bar-cycle','melody-handoff','melody-manual-arp','dialogue-arp','pop','range-unavailable','seek-loop','XYZ-trajectory','buildup','motif-off','long-cycle','policy-sparse','policy-more-rest','independent-voices','restart','scene-ending','quiet-unrest','layer-emphasis']
BAR=96000;TICK=6000;TOTAL=128*BAR

def run(exe,case,profile,block=512):
    r=subprocess.run([str(exe),str(case),str(profile),str(block)],capture_output=True,check=True)
    events=[tuple(map(int,line.split(b','))) for line in r.stdout.splitlines()]
    trace=collections.defaultdict(list,{k:[] for k in ["H","M","O"]})
    for line in r.stderr.splitlines():
        trace[line[:1].decode()].append(list(map(int,line[2:].split(b','))))
    return r.stdout,events,trace

def noteons(es,o):return [e for e in es if e[4]==0 and e[3]>0 and e[5]==o]
def spans(es):
    active={};result=[]
    for e in es:
        if e[4]:continue
        k=e[1],e[2]
        if e[3]>0:assert k not in active;active[k]=e
        else:
            assert k in active,('unowned release',e)
            n=active.pop(k);result.append((n,e[0]))
    assert not active
    return result

def groups(es,o):
    ns=noteons(es,o);result=[]
    for e in ns:
        if not result or e[0]-result[-1][-1][0]>2*BAR:result.append([])
        result[-1].append(e)
    return result

def material(records,o):
    return next((m for m in records if m[0]==o),None)

def activebars(ss,o):
    bars=set()
    for n,end in ss:
        if n[5]!=o:continue
        bars.update(range(n[0]//BAR,(max(n[0]+1,end)-1)//BAR+1))
    return len(bars)
def write_midi(path,events):
    def vlq(value):
        data=[value&127];value>>=7
        while value:data.insert(0,(value&127)|128);value>>=7
        return bytes(data)
    track=bytearray(b'\x00\xff\x51\x03\x07\xa1\x20\x00\xff\x58\x04\x04\x02\x18\x08')
    previous=0
    for sample,channel,note,velocity,kind,output in events:
        tick=round(sample/25);assert tick>=previous
        status=0xb0 if kind else 0x90 if velocity else 0x80
        track.extend(vlq(tick-previous)+bytes([status+channel-1,note,velocity]));previous=tick
    track.extend(vlq(TOTAL//25-previous)+b'\xff\x2f\x00')
    path.write_bytes(b'MThd'+struct.pack('>IHHH',6,0,1,960)+b'MTrk'+struct.pack('>I',len(track))+track)

summary=[];default_intervals=set();all_records={}
with tempfile.TemporaryDirectory(prefix='stromscore-recurrence-') as temp:
    temp=pathlib.Path(temp)
    for path in (root/'Source').glob('*.h'):
        (temp/path.name).write_bytes(subprocess.check_output(['git','show',f'920d388:Source/{path.name}'],cwd=root))
    before=temp/'before'
    subprocess.run([a.compiler,'-std=c++17','-O1','-I',str(temp),str(root/'tools/recurrence_probe.cpp'),'-o',str(before)],check=True)
    for profile in range(3):
        for case,name in enumerate(names):
            br,b,bh=run(before,case,profile)
            ar,after,ah=run(a.probe,case,profile)
            assert ([h[:4] for h in bh['H']]==[h[:4] for h in ah['H']] if case==12 else bh['H']==ah['H']),(name,profile,'harmony or recorded identity changed')
            assert case==12 or bh['M']==ah['M'],(name,profile,'actual introduced intervals/rhythm/durations changed')
            if case in [0,12,17,19]:assert ar==br,(name,'protected full-output regression')
            assert sorted(e for e in b if e[5] not in [4,7,8])==sorted(e for e in after if e[5] not in [4,7,8]),(name,'unrelated output changed')
            ns=spans(after);oldspans=spans(b)
            for block in [127,8192]:
                raw,_,trace=run(a.probe,case,profile,block)
                assert raw==ar and trace==ah,(name,profile,block,'block or transport nondeterminism')
            # Independent of implementation: group events in each declared complete occurrence,
            # compare every onset and relative interval to the actual introduced material.
            verified=0;starts=[]
            if case not in [14,22]:
                for occurrence in ah['O']:
                    output,begin,end,ordinal,varied,intro,base=occurrence
                    m=material(ah['M'],output)
                    if not m:continue
                    count=m[2];notes=[m[4+3*i:7+3*i] for i in range(count)]
                    played=[e for e in noteons(after,output) if begin*TICK<=e[0]<end*TICK]
                    if intro:
                        # Intros are logged while the actual recording is still in progress.
                        assert len(played)==count,(name,'incomplete introduction')
                    else:
                        assert len(played)==count,(name,occurrence,played,'fragmented return')
                        expected=[(begin+n[0],base+n[2]) for n in notes]
                        assert [(e[0]//TICK,e[2]) for e in played]==expected,(name,'identity/interval/rhythm drift')
                        # Exact intervals and onset identity, unchanged allowed duration variation only.
                        longest=max(range(count),key=lambda i:notes[i][1])
                        for i,e in enumerate(played):
                            off=next(t for n,t in ns if n==e)
                            length=notes[i][1]
                            if varied and i==longest:length=max(1,length//2)
                            if varied and i+1<count:length=min(length,notes[i+1][0]-notes[i][0])
                            if output==8:
                                available=notes[i+1][0]-notes[i][0] if i+1<count else end-begin-notes[i][0]
                                length=max(1,min(length,max(1,available))) # melodyLegato default ON
                            assert off-e[0]==length*TICK,(name,ordinal,i,'new/incorrect variation')
                        verified+=1
                    if output==(8 if case in [9,10] else 7):starts.append((begin,end,intro))
                    if output==8:
                        assert not any(n[5]==7 and n[0]<end*TICK and t>begin*TICK for n,t in ns),(name,'lead/answer overlap')
                    if case not in [10,11] and output in [7,8]:
                        actual_end=max((t for n,t in ns if n in played),default=begin*TICK)
                        assert not any(played[0][0]<=e[0]<actual_end for e in noteons(after,4)),(name,occurrence,'automatic arp competes with planned motif')
                starts=sorted(set(starts));gaps=[]
                for previous,current in zip(starts,starts[1:]):
                    if current[2]:continue
                    assert current[0]-previous[1]>=(4 if case==20 else 2)*16,(name,'missing minimum silence')
                    gaps.append((current[0]-previous[0])/16)
                if profile==0 and case in [1,2,3,4,8,9,18]:default_intervals.update(gaps)
            else:gaps=[]
            if case in [0,1,2,3,4,5,7,8,9,10,11,18,19,20,24,25]:assert verified>0,(name,'no valid return across 128 bars')
            oldgroups=groups(b,8 if case in [9,10] else 7)
            primary=8 if case in [9,10] else 7
            row=dict(profile=profile,case=name,before_starts_bars=[round(g[0][0]/BAR,3) for g in oldgroups],after_starts_bars=[round(g[0][0]/BAR,3) for g in groups(after,primary)],intervals_bars=gaps,before_active_bars=activebars(oldspans,primary),after_active_bars=activebars(ns,primary),verified_returns=verified,arp_ons_before=len(noteons(b,4)),arp_ons_after=len(noteons(after,4)),answer_ons=len(noteons(after,7)) if primary==8 else 0,material_ids=[m[1] for m in ah['M']],before_sha256=hashlib.sha256(br).hexdigest(),after_sha256=hashlib.sha256(ar).hexdigest())
            summary.append(row);all_records[(profile,case)]=ah
            if profile==0:
                for suffix,raw in [('before',br),('after',ar)]:
                    (out/f'{name}-{suffix}.csv').write_bytes(b'sample,channel,note,velocity,type,output\n'+raw)
                write_midi(out/f'{name}-before.mid',b);write_midi(out/f'{name}-after.mid',after)
                (out/f'{name}-plans.json').write_text(json.dumps(ah,indent=2)+'\n')
assert len(default_intervals)>=3,('fixed recurrence spacing',default_intervals)
assert summary[19]['after_starts_bars']!=summary[1]['after_starts_bars'],'policy is not connected'
(out/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
print(f'{len(summary)} 128-bar A/B comparisons, {len(summary)*2} alternate-block comparisons passed; intervals {sorted(default_intervals)}')
for r in summary[:len(names)]:print(r['case'],r['after_starts_bars'],r['after_active_bars'],r['verified_returns'])
