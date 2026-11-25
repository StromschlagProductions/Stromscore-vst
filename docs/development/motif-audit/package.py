"""Package actual (not recomposed) engine MIDI with provenance and listening markers."""
import argparse,bisect,csv,hashlib,io,json,pathlib,struct,zipfile
from analyze import read_case
parser=argparse.ArgumentParser();parser.add_argument('--repo',type=pathlib.Path,required=True);parser.add_argument('--output',type=pathlib.Path,required=True);args=parser.parse_args();HERE=args.output.resolve();REPO=args.repo.resolve()
d=json.loads((HERE/'enriched.json').read_text());results=d['results']
selection=[('01_Neutral_Tonfolge','neutral',1,1),('02_Neutral_107_Takte_Pause','neutral',3,3),('03_Neutral_XYZ_langsam','neutral',6,1),('04_Barry_M22_Antwort','barry',1,1),('05_Barry_M15_Bogen','barry',0,1),('06_Barry_M07_XYZ','barry',6,1),('07_Pop_motorisch','pop',1,1),('08_Pop_Phrasenwechsel','pop',9,1)]
OUT=HERE/'hearing';OUT.mkdir(exist_ok=True)
variation=['Original','Rhythmus','Fragment','Sequenz','Augmentation']
tracks=['Harmonie lang','Harmonie kurz','Bass lang','Bass kurz','Arpeggio','Tupfer','Stich','Dialog','Melodie']
def vlq(n):
 assert n>=0
 b=[n&127];n>>=7
 while n:b.insert(0,(n&127)|128);n>>=7
 return bytes(b)
def meta(kind,text):
 b=text.encode('utf-8');return bytes([255,kind])+vlq(len(b))+b
def midi(events,markers,voices,total):
 conductor=[(0,meta(3,'STROMSCORE 9a8d01c - actual engine output')),(0,bytes.fromhex('ff51030927c0')),(0,bytes.fromhex('ff580404021808'))]+[(t,meta(6,m)) for t,m in markers]
 alltracks=[conductor]
 for out in range(9):
  ev=[(0,meta(3,tracks[out]))]
  if not voices or out in (7,8):
   for sample,o,ch,pitch,vel,kind in events:
    if o!=out:continue
    tick=round(sample/30)
    if kind==0:payload=bytes([0x90|(ch-1),pitch,vel])
    elif kind==1:payload=bytes([0xb0|(ch-1),pitch,vel])
    else:raise ValueError(kind)
    ev.append((tick,payload))
  alltracks.append(ev)
 data=b'MThd'+struct.pack('>IHHH',6,1,len(alltracks),960)
 for ev in alltracks:
  previous=0;raw=b''
  for tick,payload in sorted(ev,key=lambda e:e[0]):raw+=vlq(tick-previous)+payload;previous=tick
  raw+=vlq(max(0,total-previous))+b'\xff\x2f\x00';data+=b'MTrk'+struct.pack('>I',len(raw))+raw
 return data
summaries=[]
for label,ctx,path,var in selection:
 c=next(c for c in results if c['config']['name']==f'{ctx}-p{path}-v{var}-r0-m3-c0-e0-b0-n128-k2')
 prefix=HERE/c['config']['name'];rows=[tuple(map(int,l.split(','))) for l in prefix.with_suffix('.csv').read_text().splitlines()]
 _,notes,frames=read_case(prefix,c['config']);ft=[f['sample'] for f in frames]
 markers=[]
 for v in c['roles']:
  voice='Melodie' if v['out']==8 else 'Dialog'
  for m in v['materials']:
   markers.append((m['origin_time'],f'{voice} INTRO id={m["memory"]["id"]} JB-M{m["memory"]["vocab"]:02}'))
  for p in v['returns']:
   if p['actual_count']:markers.append((p['first_actual'],f'{voice} RETURN {variation[p["variation"]]} {p["actual_count"]}/{p["planned_count"]} id={p["source"]}'))
  for a in v['answers']:markers.append((a['tick'],f'{voice} ANSWER adopted id={a["identity"]}'))
 old=None
 for f in frames:
  sig=(f['w'],f['ci'],f['root'],f['type'])
  if sig!=old:markers.append((round(f['sample']/30),f'HARMONY W{f["w"]} slot={f["ci"]} relative-root={f["root"]} type={f["type"]}'));old=sig
 for voices,suffix in [(False,'gesamt'),(True,'melodische_Stimmen')]:
  (OUT/f'{label}_{suffix}.mid').write_bytes(midi(rows,markers,voices,128*3840))
 buf=io.StringIO();writer=csv.writer(buf);writer.writerow(['bar_1_based','quarter_in_bar_1_based','seconds','voice','midi_pitch','duration_quarters','velocity','wendung_id','chord_slot_0_based','relative_root','type'])
 for n in notes:
  if n['out'] not in (7,8):continue
  f=frames[max(0,bisect.bisect_right(ft,n['sample'])-1)]
  writer.writerow([n['tick']//3840+1,1+(n['tick']%3840)/960,round(n['sample']/48000,6),tracks[n['out']],n['pitch'],(n['end_tick']-n['tick'])/960,n['velocity'],f['w'],f['ci'],f['root'],f['type']])
 (OUT/f'{label}_Noten.csv').write_text(buf.getvalue())
 summaries.append(dict(file=label,config=c['config'],sha256_source_csv=c['midi_sha256'],roles=[{k:v for k,v in v.items() if k in ['out','materials','answers','return_gaps_bars','note_ons','active_percent','max_silence_seconds','returns']} for v in c['roles']]))
(OUT/'Beispiele.json').write_text(json.dumps(summaries,ensure_ascii=False,indent=2)+'\n')
(OUT/'BITTE_LESEN.md').write_text('''# STROMSCORE – Motiv-Hörbeispiele, 9a8d01c

Tatsächliche Generatorausgabe, keine nachträglich komponierten Ersatzbeispiele.
100 BPM, 4/4, D, 128 Takte = 5:07,2 Minuten je Datei; Seed 0, Variation im Dateibeispiel hinterlegt.
Interne Fahrt AUS, Szenenlänge unbegrenzt, Aufbau AUS, beide Motivschalter/Legato EIN.

Je Beispiel zwei Dateien: `gesamt` enthält alle neun Ziele, `melodische_Stimmen`
enthält exakt dieselben Melodie-/Dialogereignisse aus diesem Gesamtlauf.
Die zweite Datei wurde nachträglich gefiltert, NICHT mit Solo neu komponiert.
Keine Time-Stretch-/Quantisierungsfunktion beim Import verwenden, Tempo 100 einstellen.
MIDI 960 PPQ. Kanäle 1/2 Harmonie lang/kurz, 3/4 Bass lang/kurz, 5 Arp,
6 Tupfer, 7 Stich, 8 Dialog, 9 Melodie. Studio One kann Oktavnamen anders anzeigen;
die CSV-Dateien verwenden eindeutige MIDI-Notennummern.

Für den Motivvergleich Dialog und Melodie zuerst auf denselben neutralen Klavierklang
routen, dann auf die eigenen Patches. Dies dient nur dem Hörvergleich; die tatsächlichen
Patch-Fähigkeiten und Lautstärken wurden nicht gemessen. Keine GM-Programwechsel.
Spur-/Markernamen enthalten Einführung, Wiederkehr, verwendetes Verfahren und Material-ID.
Eine Material-ID bezeichnet die Herkunft, nicht automatisch unveränderte hörbare Intervalle.
`ANSWER adopted` markiert eine reale Übernahme des Antwortplans; die tatsächlich gespielten
Antwortnoten sind in der CSV nachzulesen. Harmony-Marker geben Grundton relativ zu D und
internen Akkordtyp an; die vollständige Deutung steht im Untersuchungsbericht.

## Hörstellen (Takte ab 1)

- 01 Neutral: erster fünftöniger Gedanke Takt 1, erste Wiederkehr erst Takt 25 (0:57,6).
- 02 Neutral: Einführung Takt 1, anschließend lange Lücke der Hauptmelodie;
  erste Wiederkehr Takt 108 (4:16,8). Dialog bleibt unabhängig aktiv.
- 03 Neutral XYZ langsam: Takt 109 (4:19,2) zeigt den im Bericht belegten
  widersprüchlichen Harmoniebezug eines zwischengespeicherten Rückkehrplans.
- 04 Barry M22: D–D–A–D in Vierteln; Wiederkehr Takt 9, explizite Dialogantwort
  Takt 18, 50, 82 und 114. Die Antwort verwendet die dreitönige Schlussfigur D–A–D,
  in angepasster Lage. Ob daraus ein deutlicher Dialog entsteht, bitte hören.
- 05 Barry M15: D4–A4–D5–A4–D4 über zwei Takte; beide Stimmen können in derselben
  Lage auftreten. Erste Hauptmelodie-Wiederkehr Takt 9.
- 06 Barry M07: acht tatsächlich gespeicherte Töne; bei XYZ-Bewegung längere Lücken.
- 07 Pop: motorische Gegenstimme gegenüber erheblich sparsamerer Hauptmelodie.
- 08 Pop: Wechsel zwischen motorischer und phrasenbezogener Hook-Verwendung;
  gespeichertes Material und live erzeugte Hook-Noten sind nicht gleichzusetzen.

Begleitung ist unverändert. Für reale Instrumente die beiden Längen-Ausgänge separat
zuweisen. Keine Audioaufnahme, keine behauptete akustische Qualitätsabnahme.
Beispiele.json und *_Noten.csv enthalten Tonhöhen, Dauern, Akkordkontext und Wiederkehrdaten.
''')
archive=REPO/'docs/development/MOTIF_MUSICAL_AUDIT_MIDI.zip'
with zipfile.ZipFile(archive,'w',zipfile.ZIP_DEFLATED) as z:
 for f in sorted(OUT.iterdir()):z.write(f,'STROMSCORE_Motiv_Hoertest/'+f.name)
assert zipfile.ZipFile(archive).testzip() is None
# Reduce repeated state/notes; retain all source motifs, recurrence intervals and conflicts.
compact={k:v for k,v in d.items() if k!='results'};compact['results']=[]
if (HERE/'blockcheck.json').exists():compact['additional_blocksize_comparisons']=json.loads((HERE/'blockcheck.json').read_text())
for c in results:
 item={k:v for k,v in c.items() if k!='roles'};item['roles']=[]
 for v in c['roles']:
  vv={k:x for k,x in v.items() if k not in ['material_states','bursts','returns']}
  vv['returns']=[{k:x for k,x in p.items() if k!='material'} for p in v['returns']];item['roles'].append(vv)
 compact['results'].append(item)
(REPO/'docs/development/MOTIF_MUSICAL_AUDIT_MEASUREMENTS.json').write_text(json.dumps(compact,ensure_ascii=False,separators=(',',':'))+'\n')
print('archive',archive.stat().st_size,'bytes;',len(selection)*2,'MIDI files; measurements',(REPO/'docs/development/MOTIF_MUSICAL_AUDIT_MEASUREMENTS.json').stat().st_size)
