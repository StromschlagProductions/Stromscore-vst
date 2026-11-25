import argparse,bisect,collections,json,pathlib,statistics
parser=argparse.ArgumentParser();parser.add_argument('--repo',type=pathlib.Path,required=True);parser.add_argument('--output',type=pathlib.Path,required=True);args=parser.parse_args();root=args.repo;out=args.output
data=json.loads((out/'results.json').read_text());rs=data['results'];sh={c['value']:c for c in json.loads((root/'data/harmony/chord_types.json').read_text())['types']}
for c in rs:
 cfg=c['config'];frames=[json.loads(l) for l in (out/(cfg['name']+'.jsonl')).read_text().splitlines()];times=[f['sample'] for f in frames]
 def context(sample):return frames[max(0,bisect.bisect_right(times,sample)-1)]
 for v in c['roles']:
  for m in v['materials']:
   m['gate_mismatch_count']=sum(n['actual_length']!=n['stored_length'] for n in m['actual_introduction'])
  for p in v['returns']:
   bad=[]
   for n in p['notes']:
    f=context(n['sample']);mask={(cfg['key']+f['root']+iv)%12 for iv in sh[f['type']]['intervals']}
    if n['pitch']%12 not in mask:bad.append(dict(note=n,context={k:f[k] for k in ('w','ci','root','type')},harmony_now=f.get('harmony_now')))
   p['off_chord_onsets']=bad
  valid=[p for p in v['returns'] if p['actual_count']]
  sources=v['materials'];intro=min((m['origin_time']+min(n[0] for n in m['memory']['notes']) for m in sources),default=None)
  v['first_return_gap_bars']=None if intro is None or not valid else round((valid[0]['first_actual']-intro)/((3 if cfg['path']==11 else 4)*960),4)
  v['off_chord_return_onsets']=sum(len(p['off_chord_onsets']) for p in valid)
  v['non_exact_original_returns']=sum(p['variation']==0 and not p['original_intervals'] for p in valid)
  v['replacement_count']=max(0,v['identities']-1)
for ctx in ['neutral','barry','pop']:
 print('\n',ctx)
 for paths,label in [([0,1,2,3,4,5],'static'),([6],'slow'),([7],'fast')]:
  cs=[c for c in rs if c['config']['context']==ctx and c['config']['label']=='main' and c['config']['path'] in paths]
  for o in [8,7]:
   vs=[next(v for v in c['roles'] if v['out']==o) for c in cs]
   print(label,o,'n=',len(cs),'ons median/range',statistics.median(v['note_ons'] for v in vs),(min(v['note_ons'] for v in vs),max(v['note_ons'] for v in vs)),
         'returns/full/fragment',sum(v['realized_returns'] for v in vs),sum(v['full_returns'] for v in vs),sum(v['variation_counts'].get('2',0) for v in vs),
         'off-chord',sum(v['off_chord_return_onsets'] for v in vs),'maxsilence',round(max(v['max_silence_seconds'] for v in vs),2),
         'gapintro',max((v['first_return_gap_bars'] or 0 for v in vs),default=0))
 print('answers',sum(len(v['answers']) for c in rs if c['config']['context']==ctx and c['config']['label']=='main' for v in c['roles'] if v['out']==7))
 print('long',[(c['config']['path'],[(v['out'],v['note_ons'],v['identities'],v['realized_returns'],v['max_silence_seconds']) for v in c['roles']]) for c in rs if c['config']['context']==ctx and c['config']['label']=='long'])
# Small comparable table.
for ctx in ['neutral','barry','pop']:
 for path in [0,1,3,6,7,9]:
  cs=[c for c in rs if c['config']['context']==ctx and c['config']['path']==path and c['config']['variation']==1 and c['config']['roles']==0 and c['config']['motifs']==3 and c['config']['custom']==0 and c['config']['sceneBars']==0 and c['config']['buildup']==0 and c['config']['bars']==128 and c['config']['key']==2]
  if cs:
   c=cs[0];print('CASE',c['config']['name'],[(v['out'],v['note_ons'],[(m['memory']['count'],m['distinct_pitches'],m['memory']['vocab']) for m in v['materials']],v['realized_returns'],v['first_return_gap_bars'],v['return_gaps_bars'],v['off_chord_return_onsets']) for v in c['roles']])
# Select a proven onset conflict with both actual and forecast harmony captured.
for c in rs:
 if c['config']['genre']!=0 or c['config']['path'] not in [6,7] or c['config']['roles']!=0 or c['config']['bars']!=128 or c['config']['custom']:continue
 found=False
 for v in c['roles']:
  for p in v['returns']:
   for bad in p['off_chord_onsets']:
    h=bad['harmony_now']
    if h and (h['actual_root'],h['actual_type'])!=(h['forecast_root'],h['forecast_type']):
     print('CONFLICT',c['config']['name'],v['out'],p['begin'],p['seen_at'],p['w'],bad);found=True;break
   if found:break
  if found:break
 if found:break
(out/'enriched.json').write_text(json.dumps({**data,'results':rs},indent=2)+'\n')
