"""Offline source projection. Originals are immutable; no parsing in the processor."""
from pathlib import Path
import re,json,hashlib,sys,collections,math,csv
ROOT=Path(__file__).resolve().parents[1];F=ROOT/'docs/research/dark-synth';TEXT=(F/'STROMSCORE_Dark_Synth_Vokabular_Erweiterung.md').read_text(encoding='utf-8')
def load(p):return json.loads((ROOT/p).read_text(encoding='utf-8'))
def degree(s):
 s=s.strip().replace('♯4/♭5','#4').replace('♭','b').replace('♯','#');m=re.fullmatch(r'([b#]?)([1-7])([+-]\d+Okt)?',s);assert m,s
 return [0,2,4,5,7,9,11][int(m[2])-1]+({'b':-1,'#':1,'':0}[m[1]])+(int(m[3][:-3])*12 if m[3] else 0)
def dec(s):return float(s.replace(',','.'))
def fields(body):return {m[1]:m[2].strip() for m in re.finditer(r'^- \*\*([^*]+):\*\* (.*)$',body,re.M)}
def domains(body):
 ds=re.findall(r'[XYZ] (\d,\d+)–(\d,\d+)',body);assert len(ds)>=3,body[:120]
 return [[dec(a),dec(b)]for a,b in ds[:3]]
rows=[]
for m in re.finditer(r'^#### (DS-(?:H|B|Q|TU|E)\d+) (.+)\n([\s\S]*?)(?=^###|^##|\Z)',TEXT,re.M):
 id,name,body=m.groups();kind=re.search(r'DS-([A-Z]+)',id)[1];f=fields(body);rows.append(dict(id=id,kind=kind,name=name,source_line=TEXT[:m.start()].count('\n')+1,fields=f,text=body.strip()))
# Inline HM and tabular R/TO/K, plus study/modulation headings have different source formats.
for m in re.finditer(r'^- \*\*(DS-HM\d+) (.+?)\*\* (.+)$',TEXT,re.M):rows.append(dict(id=m[1],kind='HM',name=m[2],text=m[3],source_line=TEXT[:m.start()].count('\n')+1))
for m in re.finditer(r'^\| (DS-(R|TO|K)\d+) \| (.+)$',TEXT,re.M):rows.append(dict(id=m[1],kind=m[2],name=m[3].split('|')[0].strip(),text=m[0],source_line=TEXT[:m.start()].count('\n')+1))
for m in re.finditer(r'^#### (DS-S\d+) (.+)\n([\s\S]*?)(?=^#### |\Z)',TEXT,re.M):rows.append(dict(id=m[1],kind='S',name=m[2],text=m[3].strip(),source_line=TEXT[:m.start()].count('\n')+1))
for m in re.finditer(r'^- \*\*(DS-MS\d+) (.+?)\*\*(.+)$',TEXT,re.M):rows.append(dict(id=m[1],kind='MS',name=m[2],text=m[3],source_line=TEXT[:m.start()].count('\n')+1))
assert len(rows)==236 and len({r['id']for r in rows})==236,(len(rows),collections.Counter(r['kind']for r in rows))
by={r['id']:r for r in rows};jc={r['id']:r for r in load('docs/research/john-carpenter/TECHNICAL_INVENTORY.json')['templates']}
# Rhythm x gates are documented constructions: source studies use 55% of a cell;
# explicit '_' sustain cells extend to the last tied cell (R02/R03).
rhythms={}
for r in rows:
 if r['kind']!='R':continue
 cols=[x.strip()for x in r['text'].split('|')][1:-1];grid=int(cols[3]);pattern=cols[4].strip('`');period=int(cols[5])*240;unit=3840//grid
 hits=[i for i,c in enumerate(pattern)if c in 'xXo'];events=[]
 for i in hits:
  tied=1
  while i+tied<len(pattern)and pattern[i+tied]=='_':tied+=1
  gate={1:.4,2:.95,3:.95,10:.4,13:.6}.get(int(r['id'][-2:]),.35)
  duration=int(tied*unit*gate)
  events.append(dict(at=i*unit,duration=duration,velocity={'X':112,'x':88,'o':62}[pattern[i]]))
 # R03 printed grid has 31 cells, declared period32; final rest is implicit.
 assert all(e['at']+e['duration']<=period for e in events)
 rhythms[r['id']]=dict(period=period,events=events)
 r.update(rhythms[r['id']]);r['timing_origin']='Printed onset grid; Detached gate factors follow matching CSV examples (.35/.4/.6); sustained R02/R03 use .95. Unstudied matching gates are explicit runtime constructions.'
seq=[];events=[]
for r in rows:
 k=r['kind'];f=r.get('fields',{})
 if k in ('B','Q'):
  tokens=f['Tonfolge'].split();pitches=[degree(x)for x in tokens];function_line=re.search(r'^- \*\*Tonfunktionen[^\n]+',r['text'],re.M)[0]
  funcs=re.findall(r'=([ATVFU])',function_line);assert len(funcs)==len(pitches),r['id']
  rhythm=re.search(r'(?:JC|DS)-R\d+',f['Rhythmus'])[0]
  if rhythm.startswith('JC'):
   rr=jc[rhythm];assert rr['gate_mapping_known'],rhythm
   rhythmdata=dict(period=rr['period_ticks'],events=[dict(at=e['at'],duration=e['duration'],velocity={'X':112,'x':88,'o':62}.get(e['accent'],88))for e in rr['events']])
  else:rhythmdata=rhythms[rhythm]
  # Independent figures retain original A-relative pitch phase; block transposition
  # is selected only when the reference triad/root is musically compatible.
  context=function_line
  major='Durdreiklang' in context;mode='dorian' if 'Dorisch' in context else 'ionian' if major else 'aeolian'
  entry=dict(id=r['id'],number=(4100 if k=='B'else 4000)+int(r['id'][-2:]),bass=k=='B',chord_bound='**akkordgebunden**' in f.get('Typ / Bindung',''),pitches=pitches,functions=funcs,domains=domains(r['text']),rhythm= rhythm,major=major,mode=mode,**rhythmdata)
  entry['block_transpose']='JC-T001' in r['text'];seq.append(entry);r['runtime']=entry
 if k=='TU':
  line=f['Noten'];ns=[]
  for token,at,dur,vel in re.findall(r'([^;]+?) @ (\d+), Dauer (\d+), v(\d+)',line):ns.append(dict(pitch=degree(token.strip()),at=int(at),duration=int(dur),velocity=int(vel)))
  assert ns,r['id'];fl=f.get('Tonfunktionen','');funcs=re.findall(r'=([ATVFU])',fl);assert len(funcs)==len(ns),(r['id'],fl)
  major='Durdreiklang' in fl;mode='dorian' if 'Dorisch' in fl else 'ionian' if major else 'aeolian'
  entry=dict(id=r['id'],number=4200+int(r['id'][-2:]),bass=False,chord_bound=False,pitches=[n['pitch']for n in ns],functions=funcs,domains=domains(r['text']),major=major,mode=mode,period=max(n['at']+n['duration']for n in ns),events=[{k:v for k,v in n.items()if k!='pitch'}for n in ns])
  events.append(entry);r['runtime']=entry
# Harmony import. Fixed-upper definitions take precedence over broad chord suffixes.
notes={'A':0,'H':2,'B':2,'C':3,'D':5,'E':7,'F':8,'G':10}
def note(s):
 m=re.match(r'^([A-H])([♯♭#b]?)',s);assert m,s
 return (notes[m[1]]+({'♯':1,'#':1,'♭':-1,'b':-1,'':0}[m[2]]))%12,m.end()
suffixes={'': [0,4,7],'m':[0,3,7],'maj7':[0,4,7,11],'m7':[0,3,7,10],'m9':[0,3,7,10,14],'maj9':[0,4,7,11,14],'(add9)':[0,4,7,14],'m(add9)':[0,3,7,14],'m6':[0,3,7,9],'6':[0,4,7,9],'sus2':[0,2,7],'sus4':[0,5,7],'5':[0,7],'dim':[0,3,6]}
def ordinary(label):
 root,end=note(label);suffix=label[end:];bass=root
 if '/' in suffix:suffix,b=suffix.split('/');bass,_=note(b)
 assert suffix in suffixes,(label,suffix)
 return root,suffixes[suffix],bass
catalog=load('data/harmony/catalog.json');shapes=load('data/harmony/chord_types.json');arr=load('data/harmony/arrangements.json');prof=load('data/harmony/profiles.json');nt=load('data/harmony/notes.json')
# Idempotent: eliminate only our own projection before rebuilding.
catalog['templates']=[t for t in catalog['templates']if t.get('source_ref')!='dark_synth_p2'];catalog['sources']=[t for t in catalog['sources']if t['id']!='dark_synth_p2']
arr['bindings']=[t for t in arr['bindings']if not 61000<t['template_id']<61100];arr['recipes']=[t for t in arr['recipes']if not t['id'].startswith('dark_synth_')];nt['entries']=[t for t in nt['entries']if not 61000<t['template_id']<61100]
catalog['sources'].append(dict(id='dark_synth_p2',text='docs/research/dark-synth/STROMSCORE_Dark_Synth_Vokabular_Erweiterung.md; DS source constructions, not soundtrack transcriptions',verification='canonical_constructions_with_runtime_errata'))
harmonies=[]
for r in rows:
 if r['kind']!='H':continue
 f=r['fields'];num=int(r['id'][-2:]);
 if num==49:
  r['reserved_template_id']=61049;r['clarification']='Scope of the high #4/#11 is ambiguous across Amaj7 to Dmaj7; no H49 MIDI study resolves tonic-relative held tone versus chord-relative #11. No silent transposition or omission.';continue
 segments=re.findall(r'T(\d+)–(\d+) (.*?)(?= · |$)',f['Klangfolge (in A)']);assert segments,r['id']
 period=int(re.match(r'\d+',f['Periode'])[0]);assert sum(int(b)-int(a)+1 for a,b,_ in segments)==period
 fixed=f.get('Fester Oberbau');upper=None;basses=None
 if fixed:
  u,b=re.match(r'(.*?); nur der Bass wandert \((.*?)\)',fixed).groups();upper=[degree(t)for t in u.split()];basses=[degree(t.strip())%12 for t in b.split(',')];assert len(basses)==len(segments)
 independent='unabhängig' in f['Modus / Bass'];chords=[];voicings=[];pcall=set()
 for index,(start,end,label) in enumerate(segments):
  if upper is not None:
   bass=basses[index];root,_=note(label);pcs={p%12 for p in upper}|{root};intervals=sorted((p-root)%12 for p in pcs);assert 0 in intervals
   ns=[p-12 for p in upper]
  elif num==59:root=0;intervals=[0,2,3,5];bass=0;ns=[-12+i for i in intervals]
  else:
   root,intervals,bass=ordinary(label)
   if independent:bass=0
   if num==49:intervals=sorted(set(intervals+[18])) # source's explicit #11, not automatic coloration
   ns=[root+i-12 for i in intervals]
  match=next((t for t in shapes['types']if {i%12 for i in t['intervals']}=={i%12 for i in intervals}),None)
  if match is None:
   match=dict(id='DSShape'+str(num)+'_'+str(index),value=len(shapes['types']),suffix='['+','.join(map(str,intervals))+']',minor=3 in intervals and 4 not in intervals,intervals=intervals);shapes['types'].append(match)
  pcs={(root+i)%12 for i in intervals};pcall|=pcs|{bass}
  chords.append(dict(root=root,type=match['id'],bars=int(end)-int(start)+1,bass=bass))
  voicings.append(dict(notes=sorted(ns),held=sorted(ns) if upper is not None else [],bass=bass-36))
 # Exact common-pitch ties for melodic-link templates H24..27, not a blanket tie of all shared tones.
 hold={24:7,25:0,26:3,27:10}.get(num)
 if hold is not None:
  target=hold-12
  for v in voicings:
   assert hold in {n%12 for n in v['notes']}
   v['notes']=sorted(set(target if n%12==hold else n for n in v['notes']));v['held']=[target]
 modes={'Äolisch (natürliches Moll)':'aeolian','Dorisch':'dorian','Ionisch (Dur)':'ionian','Mixolydisch':'mixolydian'}
 mode=modes.get(f['Modus / Bass'].split(' / ')[0],'automatic');scales={'aeolian':{0,2,3,5,7,8,10},'dorian':{0,2,3,5,7,9,10},'ionian':{0,2,4,5,7,9,11},'mixolydian':{0,2,4,5,7,9,10}}
 if mode!='automatic' and not pcall<=scales[mode]:r['mode_correction']='Source mode contains borrowed/chromatic chord or bass tones; runtime automatic rather than false global scale.';mode='automatic'
 xyz=[dec(t.strip())for t in re.search(r'Anker \((.*?)\)',f['XYZ'])[1].split('/')]
 template=dict(id=61000+num,symbol=f'darkSynthH{num:02}',name=r['id']+' – '+r['name'],xyz=xyz,genres=['score'],tonality=dict(center_pc=0,mode=mode),source_ref='dark_synth_p2',chords=chords,coloration='protected',voicings=voicings,period_bars=period)
 catalog['templates'].append(template);harmonies.append(dict(id=61000+num,independent=independent,bassless=num==59,retain_bound=upper is not None));r['runtime']=dict(template_id=61000+num,period_bars=period,slots=len(chords),pcs=sorted(pcall));r['xyz']=xyz
 arr['recipes'].append(dict(id=f'dark_synth_{num}',arp=['ArpCircle','ArpCell'],bass=['BassHeld','BassHeld'],pad='PadHeld',hook=None));arr['bindings'].append(dict(template_id=61000+num,recipe=f'dark_synth_{num}'));nt['entries'].append(dict(template_id=61000+num,idea=f['Charakter'],instruments='Frei wählbare Instrumente; quelltreue harmonische Konstruktion, kein Filmzitat.'))
# Explicit non-chord slash bass stays outside the chord-tone vocabulary (H61).
used_types={c['type']for t in catalog['templates']for c in t['chords']}
shapes['types']=[t for t in shapes['types']if not t['id'].startswith('DSShape')or t['id']in used_types]
for value,t in enumerate(shapes['types']):t['value']=value
for p in prof['profiles']:
 if p['symbol']=='johnCarpenter':p['name']='Dark Synth';p['score_pool']=[i for i in p['score_pool']if not 61000<i<61100]+[h['id']for h in harmonies]
# Retain JC material in the same finite runtime collection. No second sequencer engine.
base=load('data/carpenter/vocabulary.json');allseq=[]
for s in base['sequences']:
 allseq.append(dict(id=s['id'],number=(2000 if s['kind']=='B'else 1000)+s['number'],bass=s['kind']=='B',chord_bound=s['chord_bound'],major=s['major'],pitches=s['pitches'],functions=s['functions'],domains=s['domains'],period=s['period'],events=[dict(at=e['at'],duration=e['duration'],velocity={'X':112,'x':88,'o':62}.get(e['accent'],88))for e in s['events']],rhythm_domains=s['rhythm_domains'],block_transpose=s['block_transpose'],complement=1025 if s['id']=='JC-Q024'else 1024 if s['id']=='JC-Q025'else 0))
allseq+=seq
old=base['events'][0]
events.append(dict(id='JC-M004',number=3004,bass=False,chord_bound=False,major=False,pitches=[24,24,24],functions=['A','A','A'],domains=old['xyz_ranges'],period=old['length_ticks'],events=[dict(at=n['at'],duration=n['duration'],velocity=n['velocity_override'] if n['velocity_override']is not None else 88)for n in old['notes']]))
header='// Generated offline by scripts/build_dark_synth.py. Do not edit.\n#pragma once\n#include "SequencePlan.h"\nnamespace stromscore::composition::darkSynth {\n'
def cpp_source(r):
 dom=lambda ds:'{{'+','.join('{'+str(lo)+'f,'+str(hi)+'f}'for lo,hi in ds)+'}}'
 def floatds(ds):return [[float(a),float(b)]for a,b in ds]
 mask=sum(1<<i for i in {'ionian':[0,2,4,5,7,9,11],'dorian':[0,2,3,5,7,9,10],'aeolian':[0,2,3,5,7,8,10]}.get(r.get('mode'),[]))
 return '{'+str(r['number'])+','+json.dumps(r['id'])+','+','.join(str(r.get(k,False)).lower()for k in ['bass','chord_bound','major'])+','+str(r.get('mode')=='dorian').lower()+','+str(len(r['pitches']))+',{'+','.join(map(str,r['pitches']))+'},{'+','.join("'"+f+"'"for f in r['functions'])+'},'+str(len(r['events']))+',{{'+','.join('{Tick{'+str(e['at'])+'},Tick{'+str(e['duration'])+'},'+str(e['velocity'])+'}'for e in r['events'])+'}},Tick{'+str(r['period'])+'},'+dom(floatds(r['domains']))+','+dom(floatds(r.get('rhythm_domains',[[0,1]]*3)))+','+str(r.get('complement',0))+','+str(r.get('block_transpose',False)).lower()+','+str(mask)+'u,'+str(r['id'].startswith('DS-')).lower()+','+str(r['id'] in ('DS-Q19','DS-Q20')).lower()+','+str(7 if r['id']=='DS-Q20'else -1)+','+str(12 if r['id']=='DS-Q20'else 0)+','+str(32 if r['id']=='DS-Q20'else 0)+','+str(24 if r['id']=='DS-Q13'else 0)+','+str(8 if r['id']=='DS-Q13'else 0)+','+('1.35f'if r['id']in ('DS-TU15','DS-TU16','DS-TU18')else '1.f')+','+str(4401 if r['id']in ('DS-TU15','DS-TU16')else 4417 if r['id']=='DS-TU18'else 0)+','+str(r['id']in ('DS-HM01','DS-HM17')).lower()+'}'
# Four optional lead sources have exact individual timings and intent in CSV.
with (F/'DS_Studien_Ereignisse.csv').open(encoding='utf-8-sig',newline='')as f:csvrows=list(csv.DictReader(f,delimiter=';'))
leads=[]
for id in ('DS-HM01','DS-HM05','DS-HM10','DS-HM17'):
 rr=[n for n in csvrows if n['typ']=='note'and n['quelle']==id];first=rr[0]['studie'];rr=[n for n in rr if n['studie']==first];start=int(rr[0]['tick_on']);number=int(id[-2:]);count={1:8,5:5,10:6,17:6}[number];rr=rr[:count]
 entry=dict(id=id,number=4400+number,bass=False,chord_bound=False,pitches=[degree(n['stufe'])for n in rr],functions=[n['tonfunktion']for n in rr],major=number==10,mode='ionian'if number==10 else 'aeolian',domains=domains(by[id]['text']),events=[dict(at=int(n['tick_on'])-start,duration=int(n['dauer']),velocity=int(n['velocity']))for n in rr],period=max(int(n['tick_off'])for n in rr)-start)
 leads.append(entry);by[id]['runtime']=entry;by[id]['timing_origin']='CSV '+first+'; complete first occurrence, original event timings and note intentions.'
header+='inline constexpr SequenceSource leads[]={\n'+',\n'.join(cpp_source(r)for r in leads)+'\n};\n'
header+='inline constexpr SequenceSource sources[]={\n'+',\n'.join(cpp_source(r)for r in allseq)+'\n};\ninline constexpr SequenceSource events[]={\n'+',\n'.join(cpp_source(r)for r in events)+'\n};\ninline constexpr FigureHarmonyBinding harmonies[]={\n'+',\n'.join('{'+str(h['id'])+','+str(h['independentPedal']).lower()+',false}'for h in [dict(id=int(n[4:])+60000,independentPedal=next('unabhängig' in byjc['source_fields']['Rollen'] for byjc in [jc[n]]))for n in base['harmonies']])+',\n'+',\n'.join('{'+str(h['id'])+','+str(h['independent']).lower()+','+str(h['bassless']).lower()+','+str(h['retain_bound']).lower()+'}'for h in harmonies)+'\n};\n}\n'
for r in rows:
 r['registered']=True;r['executable']=bool(r.get('runtime')or r['kind']=='R');r['status']='ground_form' if r['executable'] else 'deferred'
 r['reason']=r.get('clarification')or('Exact source ground form; optional operations are not implicitly included.' if r['executable']else {'HM':'Individual onset/duration/intent data must be reconstructed from matching source study; no invented equal-note melody.','TO':'Requires actual performance reference and explicit role transfer; see P2 implementation report.','E':'Development operation; only explicitly documented partial operations enabled.','S':'Reference study, not a mandatory 32/128-bar production form.','K':'Electronic CC deliberately deferred by task.','MS':'CC16–19 are research placeholders, not plugin routing.'}.get(r['kind'],'Pending source-specific implementation.'))
# Intrinsic implementation status is independent of production admission/counts.
operations={
'TO01':'Actual last two AR/GS notes, +12, 3/16 after the explicit reply request; whole-figure source pause.',
'TO02':'Actual last AR/GS note, +24, 1/8 after the reply request; whole-octave register fit.',
'TO03':'Actual last three compatible AR/GS notes, +12, 1/8 after the reply request.',
'TO04':'Actual last two compatible notes, -12, quarter-note reply delay.',
'TO05':'Shared contour-preserving realization of actual stored material: at most two semitones and half-gate clipping; unsuitable variants omitted.',
'TO06':'Whole transposition of the immutable actually played seed, only when the complete phrase fits.',
'TO07':'Two-note prefix of the actual seed, octave/register adaptation; independent progress.',
'E01':'Explicit seed/exposition relations TU15/16 to HM01 and TU18 to HM17; only after actual capture and only with enabled HM. No full scene grammar.',
'E02':'Complete independent pitch/rhythm periods in the shared figure core; no mandatory high-Z threshold.',
'E03':'Exact fixed upper pitches and tied physical notes, separately moving authored bass; H07-H14/H61.',
'E05':'Limited AR/GS to TU reply/transfer at complete figure boundaries. KB to LB and AR to LF transfers are not implemented.',
'E06':'Immutable actual TU material: transposition, bounded harmonic realization, fragment return.',
'E07':'Q13: last actually played AR pitch may be held on AR if the entire gate is harmonically and instrumentally valid. No automatic LF takeover.',
'E08':'Q19/Q20: deterministic .30/.55/.80/.55 gate phases, clamped before the next onset.',
'E09':'Q20: one octave mutation at step 8 after 32 complete cycles; persistent until scene restart, original unchanged.',
'E10':'Independent harmony, figure and sparse TU clocks. No mandatory 128-bar scene.',
'E11':'Existing context-weighted selection after complete harmony periods and independent layer options; no obligatory intensity rise.',
'E12':'Shared complete-figure reduction/return options, including continuous stasis. Not the full 8-16/16-32-bar source form.'}
for r in rows:
 code=r['id'][3:]
 if code in operations:r['status']='partially_integrated';r['executable']=True;r['reason']=operations[code]
 if r['kind']=='S':r['status']='reference_only';r['reason']='Reference study archived/independently MIDI-checked; no obligatory form sequence imported.'
 if r['id']in ('DS-TU20','DS-TU21','DS-TU22'):r['status']='partially_integrated';r['reason']='Exact note ground form; optional pitch-bend deliberately deferred.'
 if r['id']=='DS-H49':r['status']='clarification_required'
 if r['kind']=='E'and int(r['id'][-2:])>=13:r['reason']='Existing XYZ response remains; this particular composed transition/stillness/cadence scenario has not been activated.'
 if r['id']=='DS-E04':r['reason']='Electronic timbre/CC development deliberately deferred; placeholder modulation studies are not plugin mappings.'
outputs={ROOT/'Source/DarkSynthVocabulary.generated.h':header,F/'TECHNICAL_INVENTORY.json':json.dumps(dict(schema_version=1,base='eb32983',counts=dict(collections.Counter(r['kind']for r in rows)),templates=rows),ensure_ascii=False,indent=2)+'\n'}
if '--import' in sys.argv:
 for name,d in [('catalog',catalog),('chord_types',shapes),('arrangements',arr),('profiles',prof),('notes',nt)]:outputs[ROOT/'data/harmony'/f'{name}.json']=json.dumps(d,ensure_ascii=False,indent=2)+'\n'
for p,s in outputs.items():
 if '--check' in sys.argv:assert p.read_text(encoding='utf-8')==s,'Dark Synth data drift: '+str(p)
 else:p.parent.mkdir(parents=True,exist_ok=True);p.write_text(s,encoding='utf-8')
print('DS registered',len(rows),'harmony',len(harmonies),'sequences',len(seq),'TU',len(events))
