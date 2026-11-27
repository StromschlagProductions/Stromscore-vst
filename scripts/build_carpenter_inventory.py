"""Documentation-only mapping of all canonical IDs to the bounded P1 integration."""
from pathlib import Path
import json,collections
root=Path(__file__).resolve().parents[1];folder=root/'docs/research/john-carpenter'
read=lambda p:json.loads(p.read_text(encoding='utf-8'))
canonical=read(folder/'TECHNICAL_INVENTORY.json')['templates'];vocab=read(root/'data/carpenter/vocabulary.json')
selected=set(vocab['harmonies'])|{s['id'] for s in vocab['sequences']}|{s['rhythm_id'] for s in vocab['sequences']}|{'JC-B001','JC-M004','JC-R001'}
results=read(folder/'P1_RENDER_RESULTS.json') if (folder/'P1_RENDER_RESULTS.json').exists() else {}
heard=results.get('source_note_counts',{});rows=[]
partial_transforms={'JC-T001':'Quellautorisierte Blocktransposition einer Figur; keine pauschale Transposition aller Schichten.',
 'JC-T003':'Registeranpassung als ganze Oktavverschiebung und bestehende manuelle Oktaven; keine freie Rollenwanderung.',
 'JC-T007':'Begrenzte zyklische Schichtablösung; keine Übernahme der widersprüchlichen S35-Konstantdichte.',
 'JC-T011':'Ganze Figuren können pausieren und wiederaufgenommen werden; keine vollständige kanonische Szenengrammatik.',
 'JC-T012':'Stabile Felder und unabhängige Pedallebensdauer; keine Vollimplementierung jedes zugehörigen Modells.'}
for r in canonical:
 id=r['id'];status='deferred';reason='Nicht Bestandteil der repräsentativen P1-Auswahl; keine Umdeutung der Originalquelle.';component=None
 if id in selected:
  status='integrated_ground_form'
  reason={'Q':'Vollständige geordnete Tonfolge mit sämtlichen Einsätzen, Gates und Akzenten; nur bei passender Harmonie, Domain, Route und Register zugelassen.',
   'B':'Vollständige Bassfigur bzw. eigener Pedalanspruch; akkordgebundene und unabhängige Bindung getrennt.',
   'R':'Vollständige referenzierte Ereignisfolge; kein globaler Ersatz für sämtliche rhythmischen Rollen.',
   'M':'Exakte TU-Echofigur, getrennt von ihrem sparsamen Wiederkehrfenster.'}.get(r['kind'],'Exakte harmonische Grundform und gedruckte Akkordlagen importiert; optionale Strategien nicht vollständig.')
  if r['kind']=='H':status='partially_integrated';component='harmonic_chords_and_voicings_complete'
 if id in partial_transforms:status='partially_integrated';reason=partial_transforms[id]
 if status=='deferred':
  if r['kind']=='H' and r.get('period_bars')!=8:reason='Die eigenständige Harmonieperiode passt nicht zum aktuellen achtaktigen Importmodell; nicht auf acht Takte umgeschrieben.'
  elif r['kind']=='H' and not r.get('chord_pc_data_fit',False):reason='Nicht als exakt darstellbarer vorhandener Akkordtyp freigegeben; kein ähnlicher Akkord als Ersatz.'
  elif id in ['JC-R038','JC-R039','JC-R040','JC-B049']:reason='Gatefolge/Startphase gemäß ERRATA noch nicht eindeutig; keine erfundene Zuordnung.'
  elif id in ['JC-S18','JC-S28','JC-S40','JC-EF12']:reason='Offene Hierarchie lokaler Tonvorräte gemäß ERRATA; Gesamtvorlage nicht aktiviert.'
  elif id=='JC-S35':reason='Rollen-/Dichtebeschreibung widerspricht der Studie; keine künstlich ergänzte zweite Schicht.'
  elif id in ['JC-Q043','JC-Q044']:reason='Optionale allgemeine SYNTH-Phasenhypothese, nicht gesicherter Carpenter-Default. Der gemeinsame Figurenplan kann eigene Perioden ausdrücken; diese Quelle ist nicht aktiviert.'
  elif r['kind'] in ['S','P','EF']:reason='Keine vollständige Quell-Szene/Phrase/Ereignisfeldplanung importiert; ähnliche P1-Hörstudien sind kein Ersatz für diese ID.'
  elif r['kind']=='T':reason='Keine vollständige Aktivierung dieses Transformationsverfahrens; konkrete Voraussetzungen separat prüfen.'
 rows.append(dict(id=id,kind=r['kind'],name=r['name'],status=status,reason=reason,component=component,observed_note_ons_in_hearing_studies=heard.get(id,0) if r['kind'] in ('Q','B') or id=='JC-M004' else None,source_line=r.get('source_line')))
assert len(rows)==405 and len({r['id'] for r in rows})==405
output=dict(base='44d2404',scope='P1 ground forms and explicit partial components, not the complete optional instructions of every canonical ID',counts=dict(collections.Counter(r['status'] for r in rows)),source_data='data/carpenter/vocabulary.json',hearing_counts_available=bool(results),ids=rows)
(folder/'P1_IMPLEMENTED_IDS.json').write_text(json.dumps(output,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(output['counts'])
