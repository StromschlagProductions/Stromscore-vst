"""Read-only historical BH/HE material comparison; writes documentation, no catalog aliases."""
from pathlib import Path
import re,json
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[2]
old=(ROOT/'docs/research/shared/Musikalisches_Vokabular_Gesamtfassung_2026-11-24.txt').read_text()
blocks={m[1]:dict(name=m[2],body=m[3],line=old[:m.start()].count('\n')+1) for m in re.finditer(r'^#{3,4} ((?:BH|JB)-[A-Z]\d+) · ([^\n]+)\n(.*?)(?=^#{2,4} |\Z)',old,re.M|re.S)}
aliases={a:b for a,b in re.findall(r'^\| (BH-[A-Z]\d+) \| (JB-[A-Z]\d+) \|',old,re.M)}
ids=sorted(set(i for i in blocks if i.startswith('BH-'))|set(aliases))
new=json.loads((HERE/'TECHNICAL_INVENTORY.json').read_text())['templates']
base=dict(C=0,D=2,E=4,F=5,G=7,A=9,B=11)
def pc(s):s=s.replace('♭','b').replace('♯','#');return (base[s[0]]+s[1:].count('#')-s[1:].count('b'))%12
types=json.loads((ROOT/'data/harmony/chord_types.json').read_text())['types']
suffix={c['suffix']:c['intervals'] for c in types}
suffix.update({'mM7':[0,3,7,11],'mM9':[0,3,7,11,2],'aug':[0,4,8],'augM7':[0,4,8,11],'madd9':[0,3,7,2]})
def upper(symbol):
 s=re.sub(r'/[A-G][b#]?$', '',symbol);m=re.fullmatch(r'([A-G][b#]?)(.*)',s)
 if not m or m[2] not in suffix:return None
 return sorted({(pc(m[1])+i)%12 for i in suffix[m[2]]})
def chordrows(body):
 rows=[]
 for row in re.findall(r'^\| \d+ \|.*',body,re.M):
  c=[x.strip() for x in re.split(r'(?<!\\)\|',row)[1:-1]]
  try:rows.append(dict(pcs=sorted({pc(p) for p in re.findall(r'[A-G][b#♭♯]?',c[4])}),bass=pc(c[5]),bars=float(c[2]),symbol=c[1].strip('`'),upper_pcs=upper(c[1].strip('`'))))
  except (ValueError,KeyError,IndexError):return []
 return rows
def expanded(cs,tr=0,strict=False):
 return [(frozenset((p+tr)%12 for p in ((c.get('upper_pcs') if not c.get('parsed') else c['parsed']['pcs']) if strict else c['pcs'])),(c['bass']+tr)%12) for c in cs for _ in range(int(c['bars']*2))]
records=[]
for id in ids:
 source=aliases.get(id,id);v=blocks.get(source);rec=dict(bh_id=id,historical_canonical_id=source,name=v['name'] if v else None,historical_line=v['line'] if v else None,equivalents=[],related=[],disposition='Historisch erhalten, kein zusätzlicher Import. Kein vollständiges HE-Äquivalent durch den strikten Strukturvergleich nachgewiesen.')
 if v and id[3]=='H':
  cs=chordrows(v['body']);rec['historical_chords']=cs
  if cs:
   a=expanded(cs)
   candidates=[]
   for n in new:
    if n['id'][3]!='H':continue
    for tr in range(12):
     z=expanded(n['chords'],tr)
     if len(a)!=len(z):continue
     if all(c['upper_pcs'] is not None for c in cs) and expanded(cs,strict=True)==expanded(n['chords'],tr,strict=True):rec['equivalents'].append(dict(he_id=n['id'],transpose=tr,scope='Obere Akkordtonklassen separat von Bass und Halb­takt-Dauerfolge; keine Gleichheit von Register/Rollen/Verfahren.'));break
     score=sum((len(x[0]&y[0])/len(x[0]|y[0])+.25*(x[1]==y[1]))/1.25 for x,y in zip(a,z))/len(a)
     candidates.append((score,n['id'],tr))
   best={}
   for score,i,tr in sorted(candidates,reverse=True):
    if i not in best and score>=.7:best[i]=dict(he_id=i,transpose=tr,structural_similarity=round(score,4))
   rec['related']=list(best.values())[:3]
   if rec['equivalents']:rec['disposition']='Harmonische Überdeckung nachgewiesen. Nicht als zusätzliche Wendung importieren; Verfahren/optional andere Komponenten separat prüfen.'
 elif v and id[3]=='R':
  pats=re.findall(r'^\S+\s+([xX.\-|]+)\s*$',v['body'],re.M)
  for n in new:
   if n['id'][3]!='R':continue
   for row in n.get('grid_events',[]):
    # Original symbols retain accents and gates; matching lines are not matching multi-role plans.
    newpats=re.findall(r'^\S+\s+([xX.\-|]+)\s*$',n['grid'],re.M)
    if set(pats)&set(newpats):rec['related'].append(dict(he_id=n['id'],scope='Identische einzelne Rasterzeile; Meter, Rolle, Tonregel und weiterer Verlauf NICHT dadurch gleich.'));break
 elif v and id[3]=='M':
  rec['historical_note_tokens']=re.findall(r'([A-G][b#]?\d)@(\d+)\+(\d+)',v['body'])
  for n in new:
   if n['id'][3]!='M' or not rec['historical_note_tokens']:continue
   a=[(pc(p),int(at)*240,int(d)*240) for p,at,d in rec['historical_note_tokens']];z=[(pc(t['pitch']),t['at_ticks'],t['duration_ticks']) for t in n['notes']]
   if a==z:rec['related'].append(dict(he_id=n['id'],scope='Tonklassen/Einsatz/Dauer gleich; harmonische Funktion und Register separat prüfen.'))
 hints={'BH-H01':['HE-H01'],'BH-H02':['HE-H03'],'BH-H03':['HE-H79','HE-H11'],'BH-H04':['HE-H33'],'BH-H05':['HE-H32'],'BH-H06':['HE-H56','HE-H57','HE-H89'],'BH-H07':['HE-H43'],'BH-H10':['HE-H41'],'BH-H14':['HE-H19'],'BH-H18':['HE-H21'],'BH-H25':['HE-H38'],'BH-H26':['HE-H48'],'BH-H29':['HE-H07'],'BH-H31':['HE-H20']}
 rec['research_procedure_hints']=hints.get(id,[])
 rec['research_procedure_hint_scope']='Forschungsinterner Verfahrenshinweis, keine Gleichheit von Tonfolge/Bass/Dauer oder Arrangement.'
 records.append(rec)
report=dict(source='shared/Musikalisches_Vokabular_Gesamtfassung_2026-11-24.txt',scope='Alle dort definierten BH-IDs einschließlich JB-Aliase. Keine Gleichsetzung mit numerischen Laufzeit-IDs. Exakte Harmonieüberdeckung unterscheidet obere Akkordtonmenge, Bass und Dauer; Verfahren bleiben eigenständig. Ähnlichkeit ist Suchhilfe, kein Importentscheid.',records=records)
(HERE/'BH_HE_CROSSWALK.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n')
lines=['# Historischer BH-/kanonischer HE-Abgleich','','Die neue HE-Bibliothek ist maßgeblich. BH-/JB-Originale bleiben historische Quellen. CSV und MIDI sind dieselben Studien in zwei Formaten, kein Zusatzmaterial. Stabile numerische Laufzeit-IDs werden weder aus BH noch aus HE neu abgeleitet oder überschrieben.','', 'Vollständiger maschinenlesbarer Vergleich: [BH_HE_CROSSWALK.json](BH_HE_CROSSWALK.json). Obere Akkordtonklassen, Bass und Dauerfolge werden getrennt und streng verglichen, auch transponiert; Gleichheit des Klangs bedeutet keine Gleichheit der Rollen-/Registeranweisung. Rastergleichheit ist lediglich ein Hinweis. Die grobe Ähnlichkeitszahl darf keine Zusammenlegung auslösen.','','| Historische ID | Historische kanonische ID | HE-Harmonieüberdeckung | Weitere Materialhinweise |','|---|---|---|---|']
for r in records:
 lines.append('| %s | %s | %s | %s |'%(r['bh_id'],r['historical_canonical_id'],', '.join(x['he_id']+' (+'+str(x['transpose'])+')' for x in r['equivalents']) or 'nicht nachgewiesen',', '.join(dict.fromkeys(x['he_id'] for x in r['related'])) or 'kein strikter Treffer; nicht zusätzlich importieren'))
lines+=['','Besonders wichtig: BH-H29 beschreibt Cm über C–B–B♭–A. HE-H07 benutzt stattdessen CmM7 über dieser Basslinie: verwandtes Verfahren, keine exakte Dublette. BH-H03/JB-H14 und HE-H79 betreffen das Moll-Tritonuspendel; HE-H11 verwendet dagegen mMaj7-Farben. HE-H79 verlangt zusätzlich Oktavbass. BH-H22 (Cm/F→Fm/C) bleibt von grundtönigen Plagalfällen getrennt. Die bestehenden früheren Merge-Korrekturen werden nicht rückgängig gemacht.','', 'Nicht harmonische BH-L/P-/weitere Form-IDs besitzen keine eins-zu-eins vergleichbare harmonische Ereignisliste; sie bleiben prozedurale historische Hinweise, keine neuen HE-Datenzeilen. Nicht gefundene Äquivalenz beweist kein neues musikalisches Material.']
(HERE/'BH_HE_CROSSWALK.md').write_text('\n'.join(lines)+'\n')
print('Historical BH IDs',len(records),'strict harmony overlaps',sum(bool(r['equivalents']) for r in records))
