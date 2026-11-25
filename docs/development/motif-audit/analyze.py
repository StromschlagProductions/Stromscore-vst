import bisect, collections, hashlib, json, math, pathlib, statistics

SPQ=28800
TICK_SAMPLES=30
def read_case(prefix, cfg):
    rows=[tuple(map(int,l.split(','))) for l in pathlib.Path(str(prefix)+'.csv').read_text().splitlines()]
    frames=[json.loads(l) for l in pathlib.Path(str(prefix)+'.jsonl').read_text().splitlines()]
    active={};notes=[];zero=0
    for sample,out,ch,pitch,vel,kind in rows:
        if kind:continue
        key=ch,pitch
        if vel:
            assert key not in active,('double',prefix,sample,key)
            active[key]=(sample,out,vel)
        else:
            assert key in active,('orphan',prefix,sample,key)
            start,owner,velocity=active.pop(key)
            assert sample>=start
            if sample==start:zero+=1
            notes.append(dict(sample=start,end=sample,out=owner,pitch=pitch,velocity=velocity,tick=round(start/30),end_tick=round(sample/30)))
    assert not active,('hanging',prefix)
    notes.sort(key=lambda n:(n['sample'],n['out'],n['pitch']))
    frame_times=[f['sample'] for f in frames]
    def context(sample):
        i=bisect.bisect_right(frame_times,sample)-1
        return frames[max(0,i)]
    bar_ticks=(3 if cfg['path']==11 else 4)*960
    total=cfg['bars']*bar_ticks
    result=dict(config=cfg,midi_sha256=hashlib.sha256(pathlib.Path(str(prefix)+'.csv').read_bytes()).hexdigest(),
                harmonic_ids=sorted({f['w'] for f in frames}),zero_gates=zero,roles=[],forecast_disagreements=[])
    for f in frames:
        h=f.get('harmony_now')
        if h and (h['actual_root'],h['actual_type'])!=(h['forecast_root'],h['forecast_type']):
            result['forecast_disagreements'].append(dict(tick=round(f['sample']/30),w=f['w'],**h))
    for out in (8,7):
        actual=[n for n in notes if n['out']==out]
        materials={};stages=[];plans={};answers={};first_seen={}
        for f in frames:
            v=next(v for v in f['roles'] if v['out']==out);m=v['material'];p=v['plan']
            sig=(v['ref'],v['intro'],v['origin_time'],m['id'],m['count'],m['complete'],m['vocab'])
            if not stages or sig!=stages[-1]['signature']:
                stages.append(dict(signature=sig,tick=round(f['observed_end']/30),memory=m,origin_time=v['origin_time']))
            if m['complete'] and m['id'] not in materials:
                materials[m['id']]=dict(memory=m,origin_time=v['origin_time'],intro=v['intro'],published_by=round(f['observed_end']/30))
            if p['epoch']>=0 and not p['intro']:
                key=(p['identity'],p['origin'],p['epoch'])
                if key not in plans:
                    plans[key]=dict(plan=p,seen_at=round(f['observed_end']/30),w=f['w'],energy=f['y'],unrest=f['z'],material=m)
            if v['answer_ref']>=0:
                k=(v['answer_ref'],v['answer_intro'],v['answer_origin'])
                if k not in answers:answers[k]=dict(tick=round(f['sample']/30),identity=v['answer_id'],origin=v['answer_origin'],intro=v['answer_intro'])
        recalls=[];failed=[];ineligible=0
        for data in plans.values():
            p=data['plan'];m=data['material'];epoch=p['epoch']
            sparse=data['energy']<.4 and data['unrest']<.5
            if out==7 and cfg['genre']==1: sparse=data['energy']<.4 and data['unrest']<.5
            steps=(2,2,2) if sparse else (1,2,1)
            cycle=sum(steps);position=(epoch-1)%cycle+1
            eligible=epoch==0 or position in (steps[0],steps[0]+steps[1],sum(steps))
            ordinal=(epoch-1)//cycle*3+(0 if position==steps[0] else 1 if position==steps[0]+steps[1] else 2)+1 if eligible else 0
            desired=[0,1,0,2,0,3,0,4][(ordinal-1)%8] if ordinal>0 else 0
            if not p['active']:
                if eligible:failed.append(dict(epoch=epoch,seen_at=data['seen_at'],requested_variation=desired,w=data['w']))
                else:ineligible+=1
                continue
            ns=[n for n in actual if p['begin']<=n['tick']<p['end']]
            expected=[(p['begin']+n[0],p['base']+n[2]) for n in p['notes']]
            matched=[n for n in ns if any(abs(n['tick']-at)<=1 and n['pitch']==pitch for at,pitch in expected)]
            source=m['notes'];fig=p['notes']
            source_pitch=[n[2]-source[0][2] for n in source] if source else []
            fig_pitch=[n[2]-fig[0][2] for n in fig] if fig else []
            exact_contour=len(source)==len(fig) and source_pitch==fig_pitch
            onset_exact=len(source)==len(fig) and all(a[0]==b[0] for a,b in zip(source,fig))
            recalls.append(dict(epoch=epoch,begin=p['begin'],end=p['end'],source=p['source'],identity=m['id'],vocab=m['vocab'],
                planned_count=len(fig),source_count=m['count'],actual_count=len(ns),matched=len(matched),
                full_execution=len(matched)==len(fig) and len(ns)==len(fig),variation=p['variation'],requested_variation=desired,
                adapted=p['adapted'],clipped=p['clipped'],realization=p['realization'],passing=p['passing'],
                original_intervals=exact_contour,original_onsets=onset_exact,first_actual=ns[0]['tick'] if ns else None,
                material=m,figure=fig,base=p['base'],notes=ns,w=data['w'],seen_at=data['seen_at']))
        recalls.sort(key=lambda x:x['begin'])
        for item in materials.values():
            m=item['memory'];source=[]
            for at,length,interval,velocity in m['notes']:
                wanted=item['origin_time']+at
                match=next((n for n in actual if abs(n['tick']-wanted)<=1 and n['pitch']==m['origin']+interval),None)
                source.append(dict(pitch=m['origin']+interval,at=at,stored_length=length,
                                   actual_length=None if match is None else match['end_tick']-match['tick'],
                                   context=None if match is None else {k:context(match['sample'])[k] for k in ('w','ci','root','type')}))
            item['actual_introduction']=source
            item['distinct_pitches']=len({n['pitch'] for n in source})
            item['span_ticks']=max((n[0]+n[1] for n in m['notes']),default=0)-min((n[0] for n in m['notes']),default=0)
        # Audible MIDI-thought grouping: >one quarter of gate-free air separates groups.
        bursts=[]
        for n in actual:
            if not bursts or n['tick']-bursts[-1]['gate_end']>960:
                bursts.append(dict(begin=n['tick'],gate_end=n['end_tick'],notes=[n]))
            else:bursts[-1]['notes'].append(n);bursts[-1]['gate_end']=max(bursts[-1]['gate_end'],n['end_tick'])
        intervals=[]
        for n in actual:
            if not intervals or n['sample']>intervals[-1][1]:intervals.append([n['sample'],n['end']])
            else:intervals[-1][1]=max(intervals[-1][1],n['end'])
        end=cfg['bars']*bar_ticks*30;cursor=0;gap=0
        for a,b in intervals:gap=max(gap,a-cursor);cursor=max(cursor,b)
        gap=max(gap,end-cursor)
        successful=[p for p in recalls if p['actual_count']>0]
        starts=[p['first_actual'] for p in successful]
        role=dict(out=out,note_ons=len(actual),active_percent=100*sum(b-a for a,b in intervals)/end,max_silence_seconds=gap/48000,
                  materials=list(materials.values()),material_states=stages,identities=len(materials),plans_seen=len(plans),
                  active_plans=len(recalls),failed_eligible_epochs=failed,ineligible_epochs=ineligible,
                  realized_returns=len(successful),full_returns=sum(p['full_execution'] for p in successful),
                  incomplete_returns=sum(not p['full_execution'] for p in successful),planned_but_silent=sum(not p['actual_count'] for p in recalls),
                  variation_counts=dict(collections.Counter(p['variation'] for p in successful)),
                  fragment_counts=dict(collections.Counter((p['source_count'],p['planned_count']) for p in successful if p['variation']==2)),
                  adapted_returns=sum(bool(p['adapted']) for p in successful),clipped_returns=sum(bool(p['clipped']) for p in successful),
                  exact_interval_returns=sum(p['original_intervals'] for p in successful),answers=list(answers.values()),
                  return_gaps_bars=[round((b-a)/bar_ticks,4) for a,b in zip(starts,starts[1:])],
                  returns=recalls,burst_note_counts=dict(collections.Counter(len(b['notes']) for b in bursts)),
                  bursts=bursts)
        # JSON needs string keys.
        role['fragment_counts']={f'{a}->{b}':v for (a,b),v in role['fragment_counts'].items()}
        result['roles'].append(role)
    return result, notes, frames
