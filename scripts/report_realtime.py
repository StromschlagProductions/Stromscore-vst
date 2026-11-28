"""Summarize paired realtime observations without pooling unrelated quantiles."""
from pathlib import Path
import json,statistics,collections,os
root=Path(__file__).resolve().parents[1];folder=root/'docs/development/realtime-performance'
rows=[json.loads(line)for name in ('ENGINE_PAIRED.jsonl','PROCESSOR_PAIRED.jsonl')for line in (folder/name).read_text().splitlines()]
names={(p,0):n for p,n in enumerate(['Neutral SCORE','John Barry','Bernard Herrmann','John Williams','Ennio Morricone','Dark Synth'])};names[0,1]='Neutral POP/ROCK'
def key(r):return tuple(r.get(k,0)for k in ['kind','profile','genre','block','scenario','bars','instances','parallel','gui','instance','repetition'])
groups=collections.defaultdict(dict)
for r in rows:groups[key(r)][r['variant']]=r
assert all(set(g)=={'before','after'}and g['before']['digest']==g['after']['digest']for g in groups.values())
main=[g for g in groups.values()if g['before']['kind']=='processor'and g['before']['instances']==1 and not g['before']['gui']]
lines=['# Abschließende Echtzeit-Messergebnisse','','Einheiten: Mikrosekunden. p999 bezeichnet p99.9. Jede Rohzeile enthält Durchschnitt, Median, p95, p99, p999, Maximum und Budgetüberschreitungen für CPU und Wandzeit. Die folgenden Einzelwerte sind Wiederholung 0; die zweite Wiederholung ist vollständig in den JSONL-Dateien enthalten. Keine gepoolten Quantile.','','## Gesamtprozessor: schnelle XYZ-Fahrt, 128 Samples','','| Profil / Stand | Mittel | Median | p95 | p99 | p99.9 | Maximum | CPU-Budgetüberschreitungen |','|---|---:|---:|---:|---:|---:|---:|---:|']
for context,name in names.items():
 for variant in ('before','after'):
  r=next(r for r in rows if(r['profile'],r['genre'])==context and r['kind']=='processor'and r['block']==128 and r['scenario']==3 and r['instances']==1 and not r['gui']and r['repetition']==0 and r['variant']==variant);v=r['cpu_us']
  lines.append('| '+name+' / '+variant+' | '+' | '.join(f'{v[k]:.3f}'for k in ['mean','median','p95','p99','p999','max'])+f" | {v['over_budget']} |")
lines+=['','## Gepaarte Gesamtprozessor-Zusammenfassung','','Die Verhältniswerte sind der Median der einzelnen Nachher/Vorher-Verhältnisse über die Hauptmatrix einschließlich beider Wiederholungen. Sie sind keine gepoolten Blockquantile und keine Garantie für jedes Szenario. Maxima und Überschreitungen bleiben ungekürzt ausgewiesen.','','| Profil | Fälle inkl. Wiederholungen | Median Mittelwertverhältnis | Median p99.9-Verhältnis | größtes CPU-Maximum vorher / nachher (µs) | CPU-Überschreitungen vorher / nachher | Wandzeit-Überschreitungen vorher / nachher |','|---|---:|---:|---:|---|---|---|']
summary=[]
for context,name in names.items():
 pairs=[g for g in main if(g['before']['profile'],g['before']['genre'])==context]
 d={'profile':name,'cases':len(pairs)}
 for variant in ('before','after'):
  d[variant+'_cpu_seconds']=sum(g[variant]['cpu_us']['mean']*(g[variant]['bars']*115200//g[variant]['block'])for g in pairs)/1e6
 d['total_cpu_ratio']=d['after_cpu_seconds']/d['before_cpu_seconds']
 for metric in ('mean','p999'):d[metric+'_ratio']=statistics.median(g['after']['cpu_us'][metric]/g['before']['cpu_us'][metric]for g in pairs)
 for variant in ('before','after'):
  d[variant+'_cpu_max']=max(g[variant]['cpu_us']['max']for g in pairs)
  for what in ('cpu','wall'):d[variant+'_'+what+'_overruns']=sum(g[variant][what+'_us']['over_budget']for g in pairs)
 lines.append(f"| {name} | {d['cases']} | {d['mean_ratio']:.3f} | {d['p999_ratio']:.3f} | {d['before_cpu_max']:.3f} / {d['after_cpu_max']:.3f} | {d['before_cpu_overruns']} / {d['after_cpu_overruns']} | {d['before_wall_overruns']} / {d['after_wall_overruns']} |")
 summary.append(d)
# Full selected tables: all five block sizes, both timing clocks, exact run values.
for clock,label in [('cpu_us','Thread-CPU'),('wall_us','Wandzeit')]:
 lines+=['','## Alle Puffergrößen – '+label+', schnelle XYZ-Fahrt, Wiederholung 0','','| Profil | Samples | Stand | Mittel | Median | p95 | p99 | p99.9 | Maximum | Überschreitungen |','|---|---:|---|---:|---:|---:|---:|---:|---:|---:|']
 for context,name in names.items():
  for block in (64,128,256,512,1024):
   for variant in ('before','after'):
    r=next(r for r in rows if(r['profile'],r['genre'])==context and r['kind']=='processor'and r['block']==block and r['scenario']==3 and r['instances']==1 and not r['gui']and r['repetition']==0 and r['variant']==variant);v=r[clock]
    lines.append(f"| {name} | {block} | {variant} | "+' | '.join(f'{v[k]:.3f}'for k in ['mean','median','p95','p99','p999','max'])+f" | {v['over_budget']} |")
lines+=['','## Vier Instanzen und tatsächliche GUI','','Alle Eingaben identisch; Instanzen müssen unabhängige, identische musikalische Ergebnisse erzeugen. Serielle Gesamtsummen enthalten die verschachtelten Messhüllen. Bei parallel4 zeigt jede Spalte den größten Einzelinstanzwert; dies ist weder ein gepooltes Quantil noch die Summe der Überschreitungen. Parallele Worker bilden den kritischen DAW-Threadpfad nicht nach. GUI läuft zeitlich getaktet. Hier Wiederholung 0.','','| Profil | Modus | Stand | CPU Mittel | CPU p99.9 | CPU Maximum | CPU Überschreitungen | Wand Maximum | Wand Überschreitungen |','|---|---|---|---:|---:|---:|---:|---:|---:|']
for context,name in names.items():
 for mode in ('serial4','parallel4','gui'):
  for variant in ('before','after'):
   rs=[r for r in rows if(r['profile'],r['genre'])==context and r['kind']=='processor'and r['repetition']==0 and r['variant']==variant and ((mode=='serial4'and r['instances']==4 and not r['parallel'])or(mode=='parallel4'and r['instances']==4 and r['parallel'])or(mode=='gui'and r['gui']))]
   if mode=='serial4':c=rs[0]['batch_cpu_us'];w=rs[0]['batch_wall_us']
   else:
    c={k:max(r['cpu_us'][k]for r in rs)for k in rs[0]['cpu_us']};w={k:max(r['wall_us'][k]for r in rs)for k in rs[0]['wall_us']}
   lines.append(f"| {name} | {mode} | {variant} | {c['mean']:.3f} | {c['p999']:.3f} | {c['max']:.3f} | {c['over_budget']} | {w['max']:.3f} | {w['over_budget']} |")
recheck=folder/'PEAK_RECHECK.jsonl'
if recheck.exists():
 rr=[json.loads(line)for line in recheck.read_text().splitlines()]
 lines+=['','## Wiederholungsprüfung der drei größten Nachher-Maxima','','Die drei Fälle mit den größten CPU-Maxima der vollständigen Nachher-Hauptmatrix wurden anschließend jeweils fünfmal zusätzlich gepaart wiederholt. Die ursprünglichen Ausreißer bleiben oben und in den Rohdaten erhalten. Werte: Minimum / Median / Maximum der fünf Laufmaxima, keine gepoolten Blockquantile. Alle Wiederholungen müssen dieselben MIDI-Prüfsummen vor/nach liefern.','','| Profil | Samples / Szenario | Stand | CPU-Maxima (µs) | Wandzeit-Maxima (µs) |','|---|---|---|---|---|']
 for case in dict.fromkeys((r['profile'],r['genre'],r['block'],r['scenario'])for r in rr):
  for variant in ('before','after'):
   selected=[r for r in rr if(r['profile'],r['genre'],r['block'],r['scenario'])==case and r['variant']==variant]
   assert len(selected)==5
   cells=[]
   for clock in ('cpu_us','wall_us'):
    values=[r[clock]['max']for r in selected];cells.append(' / '.join(f'{v:.3f}'for v in (min(values),statistics.median(values),max(values))))
   lines.append(f'| {names[case[:2]]} | {case[2]} / {case[3]} | {variant} | '+ ' | '.join(cells)+' |')
(folder/'RESULTS.md').write_text('\n'.join(lines)+'\n')
payload=dict(paired_observations=len(groups),rows=len(rows),contexts=summary,main_processor_blocks=sum(g[v]['bars']*115200//g[v]['block']for g in main for v in ('before','after')))
(folder/'SUMMARY.json').write_text(json.dumps(payload,indent=2,ensure_ascii=False)+'\n')
os.environ.setdefault('MPLCONFIGDIR','/tmp/stromscore-perf/mpl-cache')
import matplotlib;matplotlib.use('Agg')
import matplotlib.pyplot as plt
fig,axes=plt.subplots(1,3,figsize=(15,5))
for ax,(clock,metric,title)in zip(axes,[('cpu_us','p999','CPU p99.9'),('cpu_us','max','CPU-Maximum'),('wall_us','max','Wandzeit-Maximum')]):
 for j,variant in enumerate(('before','after')):
  values=[];lower=[];upper=[]
  for context in names:
   vs=[r[clock][metric]/1000 for r in rows if(r['profile'],r['genre'])==context and r['kind']=='processor'and r['block']==128 and r['scenario']==3 and r['instances']==1 and not r['gui']and r['variant']==variant]
   m=statistics.median(vs);values.append(m);lower.append(m-min(vs));upper.append(max(vs)-m)
  ax.errorbar([i+(.12 if j else -.12)for i in range(7)],values,yerr=[lower,upper],fmt='o',capsize=3,label=variant)
 ax.axhline(128/48,color='red',linestyle='--',linewidth=1,label='Blockbudget');ax.set_yscale('log');ax.set_title(title);ax.set_ylabel('ms, logarithmisch');ax.set_xticks(range(7),list(names.values()),rotation=65,ha='right');ax.grid(axis='y',alpha=.25)
axes[0].legend();fig.suptitle('Gesamtprozessor – 128 Samples, schnelle XYZ-Fahrt\nPunkte: Median der zwei Einzelmesswerte; Fehlerbalken: deren Spannweite (keine gepoolten Quantile)');fig.tight_layout();fig.savefig(folder/'TAIL_COMPARISON.svg');plt.close(fig)
print(json.dumps(payload,indent=2,ensure_ascii=False))
