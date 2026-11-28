"""Offline Herrmann P1 projection; canonical inputs are never rewritten."""
from pathlib import Path
import json,re,sys,math,hashlib
ROOT=Path(__file__).resolve().parents[1]
def read(p):return json.loads((ROOT/p).read_text(encoding='utf-8'))
def dump(p,v):
 p=ROOT/p;p.parent.mkdir(parents=True,exist_ok=True);p.write_text(json.dumps(v,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
rows=read('docs/research/bernard-herrmann/TECHNICAL_INVENTORY.json')['templates'];by={t['id']:t for t in rows}
selection=read('docs/research/bernard-herrmann/CAPABILITY_REVIEW_58ea29d.json')['package_candidate_ids']
H=selection['H']+['HE-H51','HE-H53','HE-H57','HE-H58','HE-H60','HE-H64','HE-H68']
shapes=read('data/harmony/chord_types.json')['types'];types={t['id']:t for t in shapes}
P=lambda v:json.dumps(v,ensure_ascii=False,separators=(',',':'))
def pitch(s):
 s=s.replace('♭','b').replace('♯','#');m=re.fullmatch(r'([A-G])([#b]?)(-?\d+)',s);assert m,s
 return {'C':0,'D':2,'E':4,'F':5,'G':7,'A':9,'B':11}[m[1]]+({'#':1,'b':-1}.get(m[2],0))+12*(int(m[3])+1)
def functions(t):
 raw=(t.get('functions_raw') or '').replace('♭','b').replace('♯','#')
 return [(pitch(p),f,pitch(target) if target else -1)for p,f,target in re.findall(r'([A-G][#b]?\d+)\s+([ATVFU])(?:→([A-G][#b]?\d+))?',raw)]
# Exact same harmonic object can be shared. Distinct required voicings are real strategy differences.
reuse={'HE-H01':30001,'HE-H41':1042,'HE-H42':40025}
runtime={id:reuse.get(id,70000+int(id[4:]))for id in H}
components={};bindings=[]
for id in H:
 t=by[id];num=int(id[4:]);upper=None
 if t['chords'][0]['parsed']['components']:upper=t['chords'][0]['parsed']['components'][0]
 comps=upper is not None
 # Canonical H54/H57 are synchronized near-register objects; others separate.
 fused=id in ['HE-H54','HE-H57']
 upper_notes=([60+upper['root']+iv for iv in types[upper['type']]['intervals']]if upper else [0,0,0])
 if upper and (id in ['HE-H51','HE-H57','HE-H58','HE-H60']):upper_notes=[n+12 for n in upper_notes]
 base_register=24 if id in ['HE-H02','HE-H05','HE-H66','HE-H67'] else 36
 bass_notes=[]
 written=re.findall(r'[A-G][#b♭♯]?\d+',t['bass_instruction'])
 for c in t['chords']:
  n=base_register+c['bass']
  if bass_notes:
   while n-bass_notes[-1]>6:n-=12
   while n-bass_notes[-1]<-6:n+=12
  bass_notes.append(n)
 if len(written)==len(bass_notes):
  exact=[pitch(n) for n in written]
  if all(n%12==c['bass'] for n,c in zip(exact,t['chords'])):bass_notes=exact
 bindings.append(dict(bass_notes=bass_notes,harmony=runtime[id],source=id,pedal=0 if id in ['HE-H23','HE-H43','HE-H60','HE-H68'] else -1,high=79 if id=='HE-H64' else 90 if id=='HE-H68' else -1,
  upper_root=upper['root'] if upper else -1,upper_type=types[upper['type']]['value'] if upper else 0,upper_notes=upper_notes,fused=fused,stages=[(0,0,False),(7680,-12,False),(15360,-36,True)] if id=='HE-H60' else [],bass_register=24 if id in ['HE-H02','HE-H05','HE-H66','HE-H67'] else 36,bass_mode=1 if id=='HE-H10' else 2 if id=='HE-H57' else 0))
if '--import' in sys.argv:
 cat=read('data/harmony/catalog.json');arr=read('data/harmony/arrangements.json');prof=read('data/harmony/profiles.json');notes=read('data/harmony/notes.json')
 source='herrmann_canonical_p1'
 # Rebuild this projection only; all existing stable source rows remain untouched.
 owned={t['id'] for t in cat['templates'] if t['source_ref']==source}
 cat['templates']=[t for t in cat['templates'] if t['id'] not in owned]
 arr['bindings']=[b for b in arr['bindings'] if b['template_id'] not in owned]
 arr['recipes']=[r for r in arr['recipes'] if not r['id'].startswith('herrmann_')]
 notes['entries']=[n for n in notes['entries'] if n['template_id'] not in owned]
 if not any(s['id']==source for s in cat['sources']):cat['sources'].append(dict(id=source,text='docs/research/bernard-herrmann/STROMSCORE_Bernard_Herrmann_Vokabular_Kanonisch.md; canonical constructed material, not film transcriptions',verification='canonical_research_constructions'))
 for id in H:
  if id in reuse or any(v['id']==runtime[id] for v in cat['templates']):continue
  t=by[id];ch=[];voices=[];last=None
  for c in t['chords']:
   p=c['parsed'];p=p['components'][-1] if p['components'] else p;assert p['type'] in types,id
   root=p['root'];typ=p['type'];bass=c['bass'];dur=int(c['bars']);assert dur==c['bars']
   ch.append(dict(root=root,type=typ,bars=dur,bass=bass))
   ns=[root+i for i in types[typ]['intervals']]
   # Parallel structures use one shared root reference, never per-note octave folding.
   if id in ['HE-H15','HE-H22','HE-H32','HE-H33','HE-H76']:
    root2=root if root<=6 else root-12;ns=[root2+i for i in types[typ]['intervals']]
   if id=='HE-H10' or id=='HE-H57':ns=[n+12 for n in ns]
   if id in ['HE-H51','HE-H53','HE-H58','HE-H60']:ns=[n-12 for n in ns]
   if id=='HE-H17' and root==5:ns=[0,5,8]
   if id=='HE-H03':
    # Fixed C4 is root -> major seventh, not a rearticulated nearest pitch class.
    ns=[0,3,7,11] if root==0 else [0,1,4,8]
   bass_note=next(b for b in bindings if b['source']==id)['bass_notes'][len(voices)]
   voices.append(dict(notes=ns,held=[],bass=bass_note-60))
  for i,v in enumerate(voices):v['held']=sorted(set(v['notes'])&set(voices[i-1]['notes'])) if id in ['HE-H03','HE-H07','HE-H17'] else []
  cat['templates'].append(dict(id=runtime[id],symbol='herrmannH'+id[4:],name=id+' – '+t['name'],xyz=t['xyz'],genres=['score'],tonality=dict(center_pc=0,mode='automatic'),source_ref=source,chords=ch,coloration='protected',voicings=voices))
  recipe='herrmann_'+id[4:];arr['recipes'].append(dict(id=recipe,arp=['ArpCircle','ArpCell'],bass=['BassHeld','BassPedal'],pad='PadHeld',hook=None));arr['bindings'].append(dict(template_id=runtime[id],recipe=recipe))
  notes['entries'].append(dict(template_id=runtime[id],idea=t['effect']+' Kanonische Konstruktion; '+t['evidence'],instruments='Instrumentierung frei; geeignete Spielweisen und Register erforderlich.'))
 p=next(p for p in prof['profiles'] if p['symbol']=='bernardHerrmann');p['harmony_selection_only']=False;p['score_pool']=list(runtime.values());p['weights']=[]
 p['score_overrides']=[dict(template_id=runtime[id],xyz=by[id]['xyz'],name=id+' – '+by[id]['name'],coloration='protected',source_ref=source)for id in reuse]
 for file,d in [('catalog',cat),('arrangements',arr),('profiles',prof),('notes',notes)]:dump('data/harmony/'+file+'.json',d)
figures=[];deferred={}
roles={'LF':'harmonyLong','KF':'harmonyShort','LB':'bassLong','KB':'bassShort','AR':'movement','TU':'impulse','ST':'effect','GS':'dialog'}
for id in selection['R']:
 t=by[id]
 for part,g in enumerate(t['grid_events']):
  events=[]
  for i,e in enumerate(g['events']):
   ref='chord' if g['role'] in ['LF','KF'] else ('root' if id=='HE-R37' else 'brokenChord') if g['role']=='AR' else 'bass' if g['role'] in ['LB','KB'] else 'root'
   events.append(dict(at=e['at_ticks'],duration=e['duration_ticks'],pitch=(i%5 if id=='HE-R63' else i%4) if ref=='brokenChord' else 12 if id=='HE-R64' else 0,velocity=88 if e['accent'] else 66,reference=ref,function='A',target=-1))
  figures.append(dict(id=80000+int(id[4:])*10+part,source=id,part=roles[g['role']],period=t['bars']*3840,events=events,y=t['xyz'][1],z=t['xyz'][2],xlow=.5 if id=='HE-R64' else 0,xhigh=1,context=[0,0],refs=[],group=int(id[4:]),held=False,sparse=g['role']in['TU','AR']))
for id in selection['B']:
 t=by[id];tokens=re.findall(r'P\(([^)]+)\)|(?<![A-Za-z])(-8|R|b|3|5|8)(?![A-Za-z])',t['tones']);tones=[]
 for fixed,relative in tokens:
  if fixed:tones.append(('fixed',pitch(fixed)))
  else:tones.append(({'R':'root','b':'bass','3':'root','5':'fifth','8':'octave','-8':'octave'}[relative],-12 if relative=='-8' else 0))
 assert tones,id
 es=t['grid_events'][0]['events'];turns=len(tones)//math.gcd(len(tones),len(es));events=[];period=t['bars']*3840;func=functions(t)
 # B05 has explicit reattacks; an identity-preserving held pedal is a separate use.
 for turn in range(turns):
  for i,e in enumerate(es):
   ordinal=turn*len(es)+i;ref,n=tones[ordinal%len(tones)];f='A';target=-1
   if func:f,target=func[ordinal%len(func)][1:]
   events.append(dict(at=turn*period+e['at_ticks'],duration=e['duration_ticks'],pitch=n,velocity=65,reference=ref,function=f,target=target))
 assert len(events)<=64,id
 long=max(e['duration'] for e in events)>960
 figures.append(dict(id=81000+int(id[4:]),source=id,part='bassLong' if long else 'bassShort',period=period*turns,events=events,y=t['xyz'][1],z=t['xyz'][2],xlow=.4 if id=='HE-B42' else 0,xhigh=1,refs=[runtime[r] for r in t['refs'] if r in runtime][:4],context=list(dict.fromkeys(sum(1<<p for p in c['parsed']['pcs']) for ref in t['refs'] if ref in by for c in by[ref].get('chords',[]) if c['parsed'] and not c['parsed']['components']))[:2],group=0,held=id in ['HE-B01','HE-B02','HE-B03'],sparse=id in ['HE-B20']))
# Motifs: unchanged short originals, bound to exact declared harmonic objects.
# Four unambiguous source contexts only; ambiguous/new type entries are deferred.
deferred['HE-H54']='Full canonical bass requires C2+C1 simultaneously; no unverified bass-polyphony or silent omission.'
motifs=[]
def chord(symbol):
 symbol=symbol.replace('\\','').replace('♭','b').replace('♯','#')
 for t in rows:
  for c in t.get('chords',[]):
   if c['symbol'].replace('\\','')==symbol and c['parsed']['type']:
    p=c['parsed'];return sum(1<<n for n in p['pcs']),p['bass']
 return None
for id in selection['M']:
 t=by[id];ctx=[chord(c)for c in re.findall(r'`([^`]+)`',t['context'] or '')]
 if len(ctx)!=2 or not all(ctx):deferred[id]='Exact source harmony unavailable';continue
 ns=t['notes'];fs=functions(t)
 if len(fs)!=len(ns):deferred[id]='Function annotations not unambiguously mapped';continue
 valid=True
 for i,(p,f,target) in enumerate(fs):
  if p!=pitch(ns[i]['pitch']):valid=False
  if f=='V' and not any(pitch(n['pitch'])==target and n['at_ticks']>ns[i]['at_ticks'] for n in ns[i+1:]):valid=False
 if not valid:deferred[id]='Explicit function/target mismatch';continue
 motifs.append(dict(id=82000+int(id[4:]),source=id,xyz=t['xyz'],context=ctx,notes=ns,functions=fs,bars=t['bars'],scope=t.get('colour_scope_raw') or ''))
header='// Generated by scripts/build_herrmann_vocabulary.py. Canonical constructed sources.\n#pragma once\n#include "LayerPlan.h"\n#include "AuthoredMotifSource.h"\nnamespace stromscore::composition::herrmann {\ninline constexpr HarmonicLayerBinding harmonies[]={\n'
for b in bindings:header+='{'+','.join(map(str,[b['harmony'],int(b['source'][4:]),b['pedal'],b['high'],b['upper_root'],b['upper_type']]))+',{'+','.join(map(str,b['upper_notes']))+'},'+str(b['fused']).lower()+','+str(len(b['stages']))+',{{'+','.join('{Tick{'+str(a)+'},'+str(shift)+','+str(f).lower()+'}'for a,shift,f in b['stages'])+'}},'+str(b['bass_register'])+',{'+','.join(map(str,b['bass_notes']))+'},'+str(b['bass_mode'])+'},\n'
header+='};\ninline constexpr LayerFigure figures[]={\n'
for f in figures:
 attacks=','.join('{Tick{'+str(e['at'])+'},Tick{'+str(e['duration'])+'},'+str(e['pitch'])+','+str(e['velocity'])+',PitchReference::'+e['reference']+",{'"+e['function']+"',"+str(e['target'])+'}}'for e in f['events'])
 header+='{'+str(f['id'])+','+P(f['source'])+',FigurePart::'+f['part']+',Tick{'+str(f['period'])+'},'+str(len(f['events']))+',{{'+attacks+'}},'+str(f['y'])+'f,'+str(f['z'])+'f,'+str(float(f['xlow']))+'f,'+str(float(f['xhigh']))+'f,'+str(f['sparse']).lower()+',{'+','.join(map(str,(f['context']+[0,0])[:2]))+'},'+str(f['group'])+','+str(f['held']).lower()+',{'+','.join(map(str,f['refs']))+'}},\n'
header+='};\ninline constexpr AuthoredMotifSource motifs[]={\n'
for m in motifs:
 ns=m['notes'];n=len(ns);arr=lambda a:'{'+','.join(map(str,a))+'}'
 mel=[]
 for bar in range(2):mel.append(sum(1<<p for p in set(pitch(v['pitch'])%12 for v in ns if v['at_ticks']//3840==min(bar,m['bars']-1))))
 header+='{'+str(m['id'])+',4,4,'+str(m['bars']*16)+','+str(n)+','+','.join(str(x)+'f'for x in m['xyz'])+','+arr([pitch(v['pitch']) for v in ns])+','+arr([v['at_ticks']//240 for v in ns])+','+arr([v['duration_ticks']//240 for v in ns])+','+arr([c[0]for c in m['context']])+','+arr(mel)+','+arr([c[1]for c in m['context']])+',false,false,false,'+"{"+','.join("'"+f+"'" for p,f,t in m['functions'])+"},"+arr([t for p,f,t in m['functions']])+','+str(.5 if 'X ≥ 0,5' in m['scope'] and 'dunk' not in m['scope'].lower() else 0.)+'f,1.f,'+str('tief' in m['scope'].lower() or 'dunk' in m['scope'].lower()).lower()+'},\n'
header+='};\n}\n'
manifest=dict(schema_version=1,source_sha256=hashlib.sha256((ROOT/'docs/research/bernard-herrmann/TECHNICAL_INVENTORY.json').read_text(encoding='utf-8').encode()).hexdigest(),harmonies=bindings,figures=figures,motifs=motifs,deferred=deferred)
for path,content in [('Source/HerrmannVocabulary.generated.h',header),('data/herrmann/vocabulary.json',json.dumps(manifest,ensure_ascii=False,indent=2)+'\n')]:
 p=ROOT/path
 if '--check'in sys.argv:assert p.exists() and p.read_text(encoding='utf-8')==content,'Herrmann drift: '+path
 else:p.parent.mkdir(parents=True,exist_ok=True);p.write_text(content,encoding='utf-8')
print('Herrmann P1:',len(H),'harmonic sources,',len(figures),'role figures,',len(motifs),'motifs; deferred',deferred)
