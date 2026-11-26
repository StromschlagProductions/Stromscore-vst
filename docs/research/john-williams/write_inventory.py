"""Render the reviewed ID inventory into the analysis document; original research stays intact."""
from pathlib import Path
import json,collections
p=Path(__file__).resolve().parent;r=json.loads((p/'TECHNICAL_INVENTORY.json').read_text());target=p/'IMPLEMENTATION_PLAN.md';s=target.read_text().split('<!-- generated inventory -->')[0].rstrip()+'\n\n<!-- generated inventory -->\n'
keys={'Direkt umsetzbar':'D','Mit vorhandenen Fähigkeiten musikalisch gleichwertig umsetzbar':'E','Kleine Erweiterung erforderlich':'K','Größere Erweiterung erforderlich':'G','Musikalisch oder technisch unklar':'U'}
for group,title in [('H','Harmonie'),('R','Rhythmus'),('B','Bass'),('M','Kurze Motive'),('P','Längere Phrasen'),('S','Modellstudien'),('T','Übergangsstudien')]:
 s+=f'\n### {title}\n\n| ID | Grundvorlage / konkrete Daten | Status | Technische Zuordnung / Grenze |\n|---|---|---|---|\n'
 for x in r['inventory']:
  if x['id'][3]!=group:continue
  desc=x['name'];reason=x['reason']
  if group=='H':desc+=': '+' → '.join(c['symbol']+' ('+str(c['bars']).removesuffix('.0')+')' for c in x['chords'])
  elif group=='R':desc+='; '+x['meter']+'; '+x['grid'].replace('\n',' / ')
  elif group=='B':desc+='; '+x['meter']+'; '+str(x['tones'])
  elif group in 'MP':desc+='; '+str(x['note_count'])+' Noten'
  else:
   v=r['role_observations'][x['id']];desc+='; '+x['meter']+'; '+str(v['model_notes'])+' Noten; '+', '.join(x['refs'])
   if v['stich_max_polyphony']>1:reason+='; ST zweistimmig/tonal, kein fester Trigger'
   if v['short_pad_over_720'] or v['short_bass_over_960']:reason+=f"; zu lange Kurznoten KF={v['short_pad_over_720']}, KB={v['short_bass_over_960']}"
  if x['xyz']:desc+='; XYZ '+ '/'.join(str(v) for v in x['xyz'])
  s+='| '+x['id']+' | '+desc.replace('|','¦')+' | '+keys[x['classification']]+' | '+reason.replace('|','¦')+' |\n'
s+='\n## 10. Reproduktion und Abgrenzung der Prüfung\n\n'
s+='`python docs/research/john-williams/audit.py` rekonstruiert das JSON-Inventar und prüft Forschungsdaten.\n`python docs/research/john-williams/coverage.py` kompiliert die Offline-Abfrage mit einem C++17-Compiler und schreibt die XYZ-Simulation.\n`python docs/research/john-williams/write_inventory.py` aktualisiert ausschließlich den markierten Tabellenteil dieses Berichts.\n\n'
s+='Keine zusätzliche Engine-Regression erforderlich: `Source/`, Laufzeitdaten, GUI, Build- und Testkonfiguration wurden nicht verändert. Geprüft wurden die neuen Dokumentationsartefakte und Forschungsdaten, nicht eine noch nicht existierende Williams-Implementierung. Die vollständige letzte Engine-/Plugin-Prüfung bleibt die zu `8d4086c` dokumentierte.\n'
target.write_text(s)
