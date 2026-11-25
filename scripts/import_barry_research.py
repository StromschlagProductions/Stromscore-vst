#!/usr/bin/env python3
"""Reproduce the reviewed phase-2 Barry import from the canonical, unchanged research.
Does not import archives, rhythm/melody examples or asserted original film notes.
"""
import json,pathlib,re
ROOT=pathlib.Path(__file__).resolve().parents[1]
RESEARCH='docs/research/shared/Musikalisches_Vokabular_Gesamtfassung_2026-11-24.txt'
TYPES={'':'Maj','m':'Min','maj7':'Maj7','m7':'Min7','7':'Dom7','mM7':'MinMaj7','mM9':'MinMaj9','m6':'Min6','add9':'Add9','sus2':'Sus2','sus4':'Sus4','5':'Fifth','dim':'DiminishedTriad','7sus4':'Dominant7Sus4','maj7#11':'Major7Sharp11'}
def pc(value):
 m=re.match(r'([CDEFGAB])([b#]?)',value);assert m,value
 return ({'C':0,'D':2,'E':4,'F':5,'G':7,'A':9,'B':11}[m[1]]+{'':0,'b':-1,'#':1}[m[2]])%12
def research():
 text=(ROOT/RESEARCH).read_text();result=[]
 for m in re.finditer(r'^#### (JB-H\d+) · ([^\n]+)\n(.*?)(?=^#### |^## |\Z)',text,re.M|re.S):
  ref,name,body=m.groups();number=int(ref[-2:]);chords=[]
  row=re.search(r'^\| '+re.escape(ref)+r' \| Barry \| ([^|]+)',body,re.M)
  xyz=row[1].strip() if row else re.search(r'\*\*XYZ:\*\* (.*?) →',body)[1]
  xyz=[float(v.strip().replace(',','.')) for v in xyz.split('/')];assert len(xyz)==3
  for line in body.splitlines():
   if not re.match(r'^\| \d+ \|',line):continue
   _,symbol,bars,start,notes,bass,stage=[v.strip() for v in line.strip('|').split('|')]
   symbol=symbol.strip('`').split('/')[0];root=pc(symbol);kind=TYPES[re.sub(r'^[A-G][b#]?','',symbol)]
   chords.append(dict(root=root,type=kind,bars=int(bars),bass=pc(bass)))
  assert sum(c['bars'] for c in chords)==8
  evidence=re.search(r'Verfahren \[([NIH])\]',body)[1]
  result.append(dict(ref=ref,number=number,name=name,xyz=xyz,chords=chords,evidence=evidence,text=body.strip()))
 assert len(result)==46 and all(r['number']!=33 for r in result)
 return result

def main():
 paths={name:ROOT/'data/harmony'/f'{name}.json' for name in ('catalog','arrangements','profiles','notes')}
 d={name:json.loads(p.read_text()) for name,p in paths.items()};cat=d['catalog'];arr=d['arrangements'];profile=d['profiles']['profiles'][1]
 owned={30000+n for n in range(1,48) if n not in (33,40)}
 imported=research();existing={t['id']:t for t in cat['templates'] if t['id'] not in owned};cat['templates']=[t for t in cat['templates'] if t['id'] not in owned]
 cat['sources']=[s for s in cat['sources'] if not s['id'].startswith('JB-H')]
 arr['bindings']=[b for b in arr['bindings'] if b['template_id'] not in owned];d['notes']['entries']=[n for n in d['notes']['entries'] if n['template_id'] not in owned]
 arr['recipes']=[r for r in arr['recipes'] if not r['id'].startswith('barry_')]
 for name,bass,arp in [('static',['BassPedal','BassHeld'],['ArpCircle','ArpUp']),('moving',['BassHeld','BassHalf'],['ArpCircle','ArpDown'])]:
  arr['recipes'].append(dict(id='barry_'+name,bass=bass,arp=arp,pad='PadHeld',hook=None))
 profile['score_pool']=[];profile['score_overrides']=[];profile['harmony_selection_only']=False
 profile['weights']=[w for w in profile['weights'] if w['template_id'] not in owned]
 for r in imported:
  i=1003 if r['number']==40 else 30000+r['number']
  cat['sources'].append(dict(id=r['ref'],text=RESEARCH+' · '+r['ref']+' · '+r['name']+' · Verfahren ['+r['evidence']+']; konkrete Vorlage [E], keine Transkription.\n'+r['text'],verification='research_constructed_'+r['evidence']))
  profile['score_pool'].append(i)
  if i==1003:
   # Reuse actual harmonic material. Only this profile's anchor/colour policy differs.
   assert existing[i]['chords']==[dict(root=0,type='Min',bars=8,bass=None)]
   profile['score_overrides'].append(dict(template_id=i,xyz=r['xyz'],coloration='protected',source_ref=r['ref'],name=r['ref']+' – '+r['name']))
   continue
  cat['templates'].append(dict(id=i,symbol='barryH'+str(r['number']).zfill(2),name=r['ref']+' – '+r['name'],xyz=r['xyz'],genres=['score'],tonality=dict(center_pc=0,mode='automatic'),source_ref=r['ref'],chords=r['chords'],coloration='protected'))
  arr['bindings'].append(dict(template_id=i,recipe='barry_static' if len({c['bass'] for c in r['chords']})==1 else 'barry_moving'))
  d['notes']['entries'].append(dict(template_id=i,idea=r['name']+'. Verfahren ['+r['evidence']+']; Tonfolge [E]. Bassvorgaben und Dauern laut kanonischer Forschung.',instruments='Besetzungsunabhängig; vorhandene geeignete MIDI-Ziele. Originalhinweise siehe Quelle.'))
  profile['weights'].append(dict(template_id=i,factor={'N':1.8,'I':1.3,'H':.75}[r['evidence']]))
 for name,path in paths.items():path.write_text(json.dumps(d[name],ensure_ascii=False,indent=2)+'\n')
if __name__=='__main__':main()
