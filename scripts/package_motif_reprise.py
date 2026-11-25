"""Measured motif reprise report and actual engine A/B MIDI, no recomposition."""
import argparse,bisect,collections,csv,io,json,pathlib,statistics,struct,sys,zipfile
root=pathlib.Path(__file__).resolve().parents[1];sys.path.insert(0,str(root/'docs/development/motif-audit'))
from analyze import read_case
p=argparse.ArgumentParser();p.add_argument('--before',type=pathlib.Path,required=True);p.add_argument('--stage-a',type=pathlib.Path,required=True);p.add_argument('--after',type=pathlib.Path,required=True);p.add_argument('--output',type=pathlib.Path,required=True);a=p.parse_args();a.output.mkdir(parents=True,exist_ok=True)
versions={name:json.loads((path/'enriched.json').read_text()) for name,path in [('before',a.before),('stage_a',a.stage_a),('after',a.after)]}
byname={name:{c['config']['name']:c for c in d['results']} for name,d in versions.items()}
# Complete protected MIDI; Arp note-on changes have their own reservation-condition regression.
protected=[]
for name,c in byname['after'].items():
 streams=[]
 for path in (a.before,a.stage_a,a.after):streams.append([tuple(map(int,l.split(','))) for l in (path/(name+'.csv')).read_text().splitlines()])
 # Compare exact sample/payload; canonicalize only interleaving of independent
 # physical notes. Stable sort preserves same-note on/off order at the same sample.
 protect=lambda es:sorted((e for e in es if e[1] not in (4,7,8)),key=lambda e:(e[0],e[1],e[2],e[3],e[5]))
 assert protect(streams[0])==protect(streams[1])==protect(streams[2]),name
 assert byname['before'][name]['harmonic_ids']==c['harmonic_ids'],('harmonic vocabulary changed',name)
 protected.append(dict(case=name,events=len(protect(streams[2]))))
def stats(c,v):
 bar=(3 if c['config']['path']==11 else 4)*960
 origin=min((m['origin_time']+m['memory']['notes'][0][0] for m in v['materials']),default=None)
 returns=[r for r in v['returns'] if r['actual_count']]
 first=next((r for r in returns if r['variation']==0 and r['full_execution'] and r['planned_count']==r['source_count']),None)
 cats=collections.Counter()
 for r in returns:
  cats['partial' if not r['full_execution'] else 'fragment' if r['variation']==2 else 'whole_original' if r['variation']==0 and r['planned_count']==r['source_count'] else 'variation']+=1
 return dict(out=v['out'],source_notes=[m['memory']['count'] for m in v['materials']],distinct_pitches=[m['distinct_pitches'] for m in v['materials']],first_any_gap_bars=v['first_return_gap_bars'],first_whole_original_gap_bars=None if first is None or origin is None else (first['first_actual']-origin)/bar,note_ons=v['note_ons'],active_percent=v['active_percent'],maximum_silence_seconds=v['max_silence_seconds'],categories=dict(cats),answers=len(v['answers']),first_whole_identity=None if first is None else first['source'],full_original_onsets_preserved=sum(r['full_execution'] and r['variation']==0 and r['original_onsets'] for r in returns),source_ids=[m['memory']['id'] for m in v['materials']])
rows=[]
for name in byname['after']:
 rows.append(dict(config=byname['after'][name]['config'],versions={label:[stats(data[name],v) for v in data[name]['roles']] for label,data in byname.items()}))
aggregates=[]
for ctx in ('neutral','barry','pop'):
 for pathgroup,paths in [('static',range(6)),('slow',[6]),('fast',[7])]:
  for output in (8,7):
   selection=[r for r in rows if r['config']['label']=='main' and r['config']['context']==ctx and r['config']['path'] in paths]
   values={}
   for version in byname:
    vs=[next(v for v in r['versions'][version] if v['out']==output) for r in selection];gaps=[v['first_whole_original_gap_bars'] for v in vs if v['first_whole_original_gap_bars'] is not None]
    cats=sum((collections.Counter(v['categories']) for v in vs),collections.Counter())
    values[version]=dict(cases=len(vs),cases_with_whole_reprise=len(gaps),first_whole_gap_median=statistics.median(gaps) if gaps else None,first_whole_gap_max=max(gaps,default=None),within_8_bars=sum(g<=8 for g in gaps),monotone_originals=sum(n==1 for v in vs for n in v['distinct_pitches']),categories=dict(cats),note_ons_median=statistics.median(v['note_ons'] for v in vs),gate_percent_median=statistics.median(v['active_percent'] for v in vs),maximum_silence_seconds=max(v['maximum_silence_seconds'] for v in vs),explicit_adoptions=sum(v['answers'] for v in vs))
   aggregates.append(dict(context=ctx,path=pathgroup,out=output,versions=values))
result=dict(reference='9a8d01c',stage_a='b4a5184',after_source_sha256=versions['after']['source_headers_sha256'],protected_events=sum(c['events'] for c in protected),protected_cases=len(protected),forecast_disagreements_after=sum(len(c['forecast_disagreements']) for c in byname['after'].values()),aggregates=aggregates,cases=rows)
(a.output/'MOTIF_REPRISE_RESULTS.json').write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n')
tracks=['Harmonie lang','Harmonie kurz','Bass lang','Bass kurz','Arpeggio','Tupfer','Stich','Dialog','Melodie']
def vlq(n):
 assert n>=0
 out=[n&127];n>>=7
 while n:out.insert(0,(n&127)|128);n>>=7
 return bytes(out)
def meta(kind,s):
 b=s.encode();return bytes([255,kind])+vlq(len(b))+b
def smf(events,markers,voices):
 ts=[[(0,meta(3,'STROMSCORE - actual engine A/B')),(0,bytes.fromhex('ff51030927c0')),(0,bytes.fromhex('ff580404021808'))]+[(t,meta(6,m)) for t,m in markers]]
 for output,name in enumerate(tracks):
  track=[(0,meta(3,name))]
  for sample,o,ch,n,v,kind in events:
   if o==output and (not voices or o in (7,8)):track.append((round(sample/30),bytes([(0xb0 if kind else 0x90)+ch-1,n,v])))
  ts.append(track)
 raw=b'MThd'+struct.pack('>IHHH',6,1,len(ts),960)
 for track in ts:
  prev=0;body=bytearray()
  for tick,data in sorted(track,key=lambda e:e[0]):body+=vlq(tick-prev)+data;prev=tick
  body+=vlq(max(0,128*3840-prev))+b'\xff\x2f\x00';raw+=b'MTrk'+struct.pack('>I',len(body))+body
 return raw
chosen=[('01_Neutral_Tritonus','neutral',3,3),('02_Barry_M22','barry',1,1),('03_Barry_M07_XYZ','barry',6,1),('04_Pop_Hook_und_Melodie','pop',1,1)]
manifest=[]
with zipfile.ZipFile(a.output/'MOTIF_REPRISE_AB.zip','w',zipfile.ZIP_DEFLATED) as z:
 for label,ctx,path,var in chosen:
  case=f'{ctx}-p{path}-v{var}-r0-m3-c0-e0-b0-n128-k2'
  for version,folder in [('before',a.before),('after',a.after)]:
   c=byname[version][case];prefix=folder/case;events=[tuple(map(int,l.split(','))) for l in prefix.with_suffix('.csv').read_text().splitlines()]
   _,notes,frames=read_case(prefix,c['config']);ft=[f['sample'] for f in frames];markers=[]
   for v in c['roles']:
    voice=tracks[v['out']]
    for m in v['materials']:markers.append((m['origin_time'],f'{voice} INTRO {m["memory"]["id"]}'))
    for r in v['returns']:
     if r['actual_count']:markers.append((r['first_actual'],f'{voice} REPRISE kind={r["variation"]} played={r["actual_count"]}/{r["planned_count"]} source={r["source"]}'))
   for voices,suffix in [(False,'gesamt'),(True,'melodische_Stimmen')]:z.writestr(f'{label}_{"A_9a8d01c" if version=="before" else "B_neuer_Stand"}_{suffix}.mid',smf(events,markers,voices))
   buf=io.StringIO();w=csv.writer(buf);w.writerow(['bar_1_based','quarter_1_based','seconds','voice','pitch','length_quarters','velocity','wendung','slot','relative_root','chord_type'])
   for n in notes:
    if n['out'] not in (7,8):continue
    f=frames[max(0,bisect.bisect_right(ft,n['sample'])-1)];w.writerow([n['tick']//3840+1,1+(n['tick']%3840)/960,round(n['sample']/48000,6),tracks[n['out']],n['pitch'],(n['end_tick']-n['tick'])/960,n['velocity'],f['w'],f['ci'],f['root'],f['type']])
   z.writestr(f'{label}_{version}_Noten.csv',buf.getvalue())
   manifest.append(dict(example=label,version=version,config=c['config'],sha256=c['midi_sha256'],roles=[dict(out=v['out'],materials=v['materials'],returns=[{k:x for k,x in r.items() if k!='material'} for r in v['returns']],answers=v['answers']) for v in c['roles']]))
 z.writestr('Messdaten_Beispiele.json',json.dumps(manifest,ensure_ascii=False,indent=2))
 z.writestr('BITTE_LESEN.md','''# STROMSCORE – Motivik A/B

A = abgenommene Referenz 9a8d01c, B = neue harmonische Konsistenz und Motivwiederkehr.
Je Beispiel 128 Takte, 100 BPM, 4/4, D, 5:07,2 Minuten; Seed 0, Variation in den Messdaten.
Interne Fahrt AUS, Szenenlänge unbegrenzt, Aufbau AUS, beide Stimmen/Motiv-/Legatoschalter EIN.
Beispiel 03 enthält externe XYZ-Bewegung; die übrigen Positionen sind statisch.
Keine nachkomponierten Ersatznoten. `melodische_Stimmen` ist eine nachträgliche Filterung
desselben Gesamtlaufs, keine Solo-Neukomposition. Tempo beim Import auf 100 setzen,
keine Quantisierung/Time-Stretch anwenden. MIDI 960 PPQ. Keine Programmwechsel.

Kanäle: 1 Harmonie lang, 2 Harmonie kurz, 3 Bass lang, 4 Bass kurz, 5 Arp,
6 Tupfer, 7 Stich, 8 Dialog, 9 Melodie. Lang/Kurz auf geeignete Patches routen.
Melodie/Dialog zuerst mit demselben neutralen Klavier vergleichen, dann im eigenen Mix.
MIDI-Nummern in CSV sind eindeutig; Oktavbezeichnungen variieren je DAW.
Marker zeigen Einführung und tatsächlich gespielte Reprisen samt Quellen-ID.
Eine Quellen-ID bezeichnet die Herkunft, nicht automatisch unveränderte Intervalle.

## Hörstellen

01 Neutral: Hauptmelodie Takt 1 C–Es–A–C–Fis. A: nächste Reprise erst Takt 108.
B: vollständige transponierte Reprise bereits Takt 5, nach zwei stillen Takten.
Die spätere lange Lücke ist dadurch nicht generell abgeschafft.
02 Barry M22: D–D–A–D in Vierteln. A: erste Reprise Takt 9.
B: erste transponierte Reprise Takt 4. Die anschließenden Antwortfenster mit anhören.
03 Barry M07: Achtelzelle A–D–Cis–D zweimal. Bewusst ein Grenzfall bei wechselnder
Harmonik; eine frühe geeignete vollständige Reprise ist hier nicht immer möglich.
04 Pop: eigenständiger motorischer Dialoghook und sparsame Hauptmelodie.
Die frühe Reprise der Hauptmelodie vergleichen; der Motor darf kontinuierlich bleiben.

Fläche, Bass und Akzent-Noten bleiben identisch. Arp-Pausen folgen den korrigierten
Motivreservierungen. Keine Änderung von Arp-Muster, Tempo oder Tonwahl.
Bitte Wiedererkennung, Kontur, Atempausen und Zusammenhang beurteilen, nicht nur Lautstärke
oder Notenzahl. Eine akustische Qualitätsabnahme wird durch die MIDI-Messung nicht ersetzt.
''')
assert zipfile.ZipFile(a.output/'MOTIF_REPRISE_AB.zip').testzip() is None
print('Packaged',len(rows),'cases, protected events',result['protected_events'],'and 16 actual A/B MIDI files')
for row in aggregates:
 if row['out']==8:print(row['context'],row['path'],[(v,d['first_whole_gap_median'],d['first_whole_gap_max'],d['within_8_bars']) for v,d in row['versions'].items()])
