"""Source-specific judgments and mechanical constraints. Does not import runtime vocabulary."""
from pathlib import Path
import json,csv,re,collections,itertools,math,hashlib
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[2]
rs=json.loads((HERE/'SOURCE_RECORDS.json').read_text());by={r['id']:r for r in rs}
rows=list(csv.DictReader((HERE/'EM_Studien_Ereignisse.csv').open(newline='',encoding='utf-8-sig'),delimiter=';'))
validation=json.loads((HERE/'VALIDATION_RESULTS.json').read_text())
def dump(n,d):(HERE/n).write_text(json.dumps(d,ensure_ascii=False,indent=2)+'\n')
def nums(s):return [int(v)for v in re.findall(r'[+-]?\d+',s)]
def prime(ps):
 # Documented packed-right/Forte-style normal order; set-class equivalence is checked independently.
 def normal(ps):
  ps=sorted(set(n%12 for n in ps));a=[]
  for i in range(len(ps)):
   v=ps[i:]+[n+12 for n in ps[:i]];a.append([n-v[0]for n in v])
  return min(a,key=lambda x:tuple(reversed(x[1:])))
 return min(normal(ps),normal([-n for n in ps]))
def iv(ps):
 a=[0]*6
 for x,y in itertools.combinations(sorted(set(n%12 for n in ps)),2):a[min((y-x)%12,(x-y)%12)-1]+=1
 return a
# Link to the actual inspected implementation, rather than research claims of readiness.
caps={
 'HARMONY':'Source/HarmonyTypes.h:Chord/HarmonyTemplate; Source/HarmonyRuntime.h:Wendung; scripts/generate_harmony_catalog.py:validate',
 'VOICING':'Source/VoiceLeading.h:lead; Source/CompositionCore.h:buildAnchor/planHarmony/leadEntry',
 'HOLD':'Source/ScoreEngine.h:padChord/releaseAt/releaseHeld; Source/CompositionCore.h:ResolutionIntent/TransitionIntent',
 'PEDAL':'Source/PedalPlan.h:PedalPlan/permits; Source/ScoreEngine.h:preparePedal',
 'NOTES':'Source/ScoreEngine.h:Active/noteOn/removeActive/outputCatalog; Source/CompositionCore.h:suitable',
 'MOTIF':'Source/CompositionCore.h:RememberedMotif/MotifFigure/MotifUse/MotifCatalog/deriveMotif; Source/AuthoredMotifSource.h',
 'TIME':'Source/MusicalTime.h:Tick; Source/MusicalExecution.h; Source/ScoreEngine.h:nextOnset/templateOnset',
 'RHYTHM':'Source/RoleRhythm.h:RoleRhythmSource/planRoleRhythm; Source/RhythmPlan.h',
 'MODE':'Source/ModalContext.h:Mode/ModalContext; Source/AuthoredMotifSource.h:authoredPitchMask',
 'ROLES':'Source/CompositionCore.h:RoleNeed/PlayingTrack/MotifHandoffPlan; Source/ScoreEngine.h:foregroundWindow',
 'POLICY':'Source/CompositionPolicy.h:FreeCompositionPolicy/MotifRecurrencePolicy/ArpeggioPhrasePolicy/PedalPolicy'}
needed={
 'voicing_constraints':'Quelllagen, enge/offene Reibung und feste Stimmen als validierte Eingabe/harte Bedingungen der vorhandenen Stimmführung; kein neuer Solver neben ihr.',
 'held_upper':'Ausdrückliche Halteabsicht mit tatsächlicher MIDI-Tonhöhe und Gültigkeitsfenster im vorhandenen Pad-Notenbesitz; Gemeinsamtonbonus allein genügt nicht.',
 'transition_intent':'U-Quell-/Zielakkord, Zielzustände, erlaubte Fortsetzungen und offene/geschlossene Auflösungsabsicht im gemeinsamen Harmonieplan.',
 'timed_resolution':'Vorhaltston, Zielton und exakter Tick sowie bewusst ausbleibende Auflösung als Tonabsicht; vorhandene lokale Linienauflösung ist kein Oberstimmen-Vorhaltsplan.',
 'staggered':'Individuelle Einsätze der Akkordstimmen statt gleichzeitiger padChord-Schleife.',
 'tone_objects':'Grundtonfreie geschützte Tonmengen, von Skalenkontext und funktionalen Akkordtypen getrennt.',
 'layers':'Getrennte lokale/global harmonische Kontexte, Schutz konsonanter UND dissonanter Schichten.',
 'bass_sequence':'Explizite geordnete Bassfolge mit Einsätzen/Dauern/Funktionsfreigabe; aktuelle Pop-Funk-/Walking-Planer reichen nicht für jede Quellfolge.',
 'periods':'Quellgetreue eigenständige Perioden und Pitch-/Rhythmus-Cursor ohne Taktreset.',
 'tick_authoring':'Autoren-Einsätze und Dauern direkt als 960-PPQ-Ticks zuführen; bestehender Dispatcher kann diese Zeiten, heutige Autorenverbraucher aber noch nicht beliebig.',
 'cell_identity':'MENGE/KLASSE/ORD/RHY/KERN als verschiedene Invarianten; keine automatische Akkordtonanpassung geschützter Mengen.',
 'cell_operations':'Permutation/erlaubte Inversion/Rotation und Kern-Farbtonaustausch mit Identitätsprüfung.',
 'long_line':'Notierte Linien über mehr als acht Originalnoten/zwei Autoren-Takte; keine Zerschneidung zur Umgehung der Kapazität.',
 'phrase_plan':'Explizite Phrasen-/Abschnittsfolge, Thema/Gegenmotiv und Entwicklung auch bei konstantem XYZ, ohne obligatorische Besetzung.',
 'modules':'Gemeinsame Modulkompatibilität für komplette Mehrfachkombinationen, Grenzwechsel und Freigabe; paarweise Tabellen sind kein Arranger.',
 'event_field':'Unregelmäßige Ereignisfelder mit Mindestabständen, Antwortfenstern und legitimer Stille; Akzentzufall ist kein Feldplan.',
 'scoped_tones':'A/T/V/F/U je konkreter Tonverwendung und Harmoniezeitraum, einschließlich expliziter F/U-Autorisierung und Zielauflösung.',
 'instrument':'Pro Kombination tatsächliche Polyphonie, Tonumfang und Gate/Artikulation am vorhandenen Ziel prüfen; keine stumme Umleitung oder pauschale Grenzaufweitung.',
 'addiv':'Ein Original über mehrere Vorkommen gezielt enthüllen/kürzen, Varianten daraus neu ableiten statt Kette von Varianten.',
 'block':'Geschützte exakte Ganzobjekt-Transposition, Y-Ereignis bei T017; heutige Motivsequenzierung ist nur ein Zweitonverfahren.'}
# Harmonic material sharing candidates, not a claim of identical voicing or style.
chordtypes={t['id']:t['intervals']for t in json.loads((ROOT/'data/harmony/chord_types.json').read_text())['types']}
existing=json.loads((ROOT/'data/harmony/catalog.json').read_text())['templates']
def merge_material(events):
 out=[]
 for duration,mask,bass in events:
  if out and out[-1][1:]==(mask,bass):out[-1]=(out[-1][0]+duration,mask,bass)
  else:out.append((duration,mask,bass))
 return out
material_index=collections.defaultdict(list)
for h in existing:
 events=[(c['bars']*3840,tuple(sorted({(c['root']+n)%12 for n in chordtypes[c['type']]})),c['root']if c['bass']is None else c['bass'])for c in h['chords']]
 material_index[tuple(merge_material(events))].append(h['id'])
for r in rs:
 if r['kind']!='H':continue
 r['existing_harmonic_material_ids']=[]
 if not r['pc_data_fit']or any(st.get('#')=='D'for st in r['states']):continue
 events=[]
 for st in r['states']:
  type=st['types_at_declared_root'][0];events.append((st['duration'],tuple(sorted({(st['root']+n)%12 for n in chordtypes[type]})),st['bass']%12 if st['bass']is not None else None))
 period=sum(e[0]for e in events)
 if period and 30720%period==0:r['existing_harmonic_material_ids']=material_index.get(tuple(merge_material(events*(30720//period))),[])
# Primary conflicts, not silent corrections.
clarify={
 'EM-H018':'Bass -12,-13,-15,-13,-19,-20,-22,-12; Bewegungen -1,-2,+2,-6,-1,-2,+10. Stufenanspruch vs Sext-/Septimsprung klären, nicht automatisch glätten.',
 'EM-H025':'Schlussklang Oberstimmen [-8,0,9,19], Bass -15 = Major6/A, keine None; 6/9-Notation wurde als Sextakkord mit Sextbass realisiert.',
 'EM-H026':'Oberstimmen [-8,0,9,19], Bass -15: {0,4,7,9}, keine 2/9; Titel 6/9 und tatsächlicher Major6/Sextbass widersprechen sich.',
 'EM-H046':'0:add9 → 8:maj → 0:add9 → 5:min; kein gleichwurzeliger Dur/Moll-Doppelklang. Titel oder Materialentscheidung offen.',
 'EM-H052':'Gemeinsam liegen 0 und 12 (Grundton), nicht Tonklasse 7 (Quinte). Titel und tatsächlicher Halt unterscheiden sich.',
 'EM-H053':'Höchste relative Töne 15,15,15,14; gemeinsam bleibt 12 innen liegen. Keine durchgehend feste höchste Stimme.',
 'EM-H058':'Tonika-Akkorde sind Min6 mit Bass9, nicht m6/9; None 2 fehlt. F9 im zweiten Segment besitzt dagegen seine richtige None 7.',
 'EM-H063':'Alle vier Akkorde sind Dur-add9; der Titel verspricht eine Moll-add9-Antwort.',
 'EM-H074':'Beide sechsnotigen Oberstimmen [-3,0,4,6,7,15] und PC-Mengen {0,3,4,6,7,9} sind identisch; kein angekündigter Austausch 2/11.',
 'EM-R013':'Vollzyklus zwei Takte: 32 eindeutige Einsätze =16/Takt, VK0; gedruckt8/Takt und VK1,94. Phasen beider Schichten auswerten.',
 'EM-R035':'Vollzyklus11520Ticks:24 eindeutige Einsätze =8/Takt, VK0,408; gedruckt1,33 und0. Kennzahlen/Unruhe-Typ vor Auswahl korrigieren lassen.',
 'EM-R036':'Vollzyklus19200Ticks:32 eindeutige Einsätze =6,4/Takt, VK0,447; gedruckt0,8 und0. Nicht nur eine Kopie je Schicht zählen.',
 'EM-R037':'Vollzyklus26880Ticks:14 eindeutige Einsätze =2/Takt, VK0,5; gedruckt0,14 und0. Vollständige Wiederholungen beider Perioden nötig.',
 'EM-R040':'Titel Zweiunddreißigstel, aber 16 Anschläge bei 0,240,...,3600: tatsächlich Sechzehntel. Nicht stillschweigend verdoppeln.',
 'EM-B010':'20 Ton-/Rhythmusanschläge dauern6000Ticks; erst die Ausrichtung zum4/4-Takt dauert96000Ticks und enthält320Anschläge. Angabe20/96000 vermischt zwei Zyklen.',
 'EM-B011':'WieB010:20Anschläge/6000Ticks, Hostphasengleichheit96000Ticks mit320Anschlägen; deklarierte20/96000 zuerst präzisieren.',
 'EM-B033':'36Anschläge/21120Ticks; Hostphasengleichheit42240Ticks umfasst72Anschläge. Gedruckte36/42240 vermischen Material- und Hostzyklus.',
 'EM-K009':'Modul behauptet Quint-Drone mit Polyphonie2; Quelle B003 notiert zwei NACHEINANDER je15360Ticks, Zyklus30720. Zugleich–nacheinander und Periodenbindung klären.'}
# Identity audit of actual C-source notes in the reference CSV. No repaired note is accepted as identity proof.
cell_observed=collections.defaultdict(list)
for row in rows:
 for ref in re.findall(r'EM-C\d{3}',row['vorlage']):cell_observed[ref].append(row)
cell_checks=[]
for id,r in by.items():
 if r['kind']!='C':continue
 observed=cell_observed[id];groups=collections.defaultdict(list)
 for row in observed:groups[row['studie']].append(row)
 examples=[]
 for sid,rr in groups.items():
  actual={int(z['rel'])%12 for z in rr};expected=set(r['pitches']);outside=actual-expected
  if outside and r['fields']['Typ']!='KERN':examples.append(dict(study=sid,expected_pcs=sorted(expected),actual_pcs=sorted(actual),outside=sorted(outside),expected_prime=r['prime_declared'],actual_prime=prime(actual),same_tni_class=len(actual)==len(expected)and any({(sign*n+t)%12 for n in actual}==expected for sign in(-1,1)for t in range(12))))
 cell_checks.append(dict(id=id,type=r['fields']['Typ'],pcs=r['pitches'],prime_source=r['prime_declared'],prime_packed_right=r['prime_actual'],prime_equivalent=r['prime_tni_equivalent'],iv_source=r['iv_declared'],iv_actual=r['iv_actual'],reference_events=len(observed),exchange_tones=r.get('exchange_tones',[]),permitted_pc_variants=r.get('permitted_pc_variants'),changed_aggregate_examples=examples,scope='CSV rel is relative to global tonic. Aggregate changes prove the literal global PC-set differs, not which unexported permutation event caused the change. Transposition is analyzed separately; local harmony is not silently unioned.'))
# Local harmonic contexts remove whole-study transposition ambiguity.
for c in cell_checks:
 r=by[c['id']];g=collections.defaultdict(list)
 for row in cell_observed[c['id']]:g[row['studie'],row['rolle'],row['kontext']].append(row)
 checks=[]
 for (study,role,context),rr in g.items():
  actual=sorted({int(z['rel'])%12 for z in rr});equiv=any({(sign*n+t)%12 for n in r['pitches']}==set(actual)for sign in(-1,1)for t in range(12))
  checks.append(dict(study=study,role=role,context=context,actual_pcs=actual,events=len(rr),same_tni_class=equiv,exchange_authorized=r['fields']['Typ']=='KERN',first_events=[dict(tick=int(z['tick']),pitch=int(z['rel']),duration=int(z['dauer_ticks']),function=z['tonfunktion'])for z in rr[:12]]))
 c['per_context_evidence']=checks
dump('CELL_IDENTITY_AUDIT.json',cell_checks)
# U: count changes require a real partial voice matching, not zip(old,new).
uchecks=[]
for r in rs:
 if r['kind']!='U':continue
 maps=[]
 for a,b in zip(r['states'],r['states'][1:]):
  ap,bp=a['pitches'],b['pitches'];solutions=[]
  if len(ap)<=len(bp):pairs=[list(zip(range(len(ap)),ix))for ix in itertools.combinations(range(len(bp)),len(ap))]
  else:pairs=[list(zip(ix,range(len(bp))))for ix in itertools.combinations(range(len(ap)),len(bp))]
  for mapping in pairs:
   held=[ap[i]for i,j in mapping if ap[i]==bp[j]];deltas=[bp[j]-ap[i]for i,j in mapping];parallel=[]
   for (i,j),(k,l)in itertools.combinations(mapping,2):
    old=(ap[k]-ap[i])%12;new=(bp[l]-bp[j])%12;da,db=bp[j]-ap[i],bp[l]-ap[k]
    if old==new and old in(0,7)and da*db>0:parallel.append([i,k])
   common=set(ap)&set(bp);required=set(r['required_held_pitches'][len(maps)]);cost=(len(required-set(held)),len(parallel),sum(abs(n)>7 for n in deltas),sum(map(abs,deltas)))
   solutions.append((cost,mapping,held,deltas,parallel))
  best=min(solutions,key=lambda x:x[0]);maps.append(dict(source_tick=a['tick'],target_tick=b['tick'],from_pitches=ap,to_pitches=bp,matching=best[1],held=best[2],movements=best[3],parallel_pairs=best[4],unheld_required=best[0][0],required_held=r['required_held_pitches'][len(maps)],large_leaps=best[0][2],new_voices=len(bp)-len(best[1]),removed_voices=len(ap)-len(best[1]),scope='Existence of a monotone partial assignment; no claim this is the unprovided author solver or current engine assignment.'))
 r['u_analysis']=maps
 rendered=[row for row in rows if r['id']in re.findall(r'EM-U\d{3}',row['vorlage'])]
 holds=0
 for row in rendered:
  if row['rolle']=='LF'and '→'in row['funktionsfolge']:holds+=1
 uchecks.append(dict(id=r['id'],states=r['states'],transitions=maps,rendered_csv_notes=len(rendered),csv_multicontext_lf_notes=holds,explicit_suspension=r['fields'].get('Vorhalt'),resolution_intent=r['fields'].get('Auflösungsabsicht')))
dump('TRANSITION_AUDIT.json',uchecks)
# Existing output assumptions, read against ScoreEngine::outputCatalog, not the study's looser limits.
limits={'LF':(6,240,240*(1<<24)),'KF':(9,240,720),'LB':(1,240,240*(1<<24)),'KB':(1,240,960),'AR':(1,240,7680),'TU':(4,240,720),'ST':(1,240,480),'GS':(2,240,240*(1<<24)),'HM':(1,240,240*(1<<24))}
violations=[]
for sid,st in validation['studies_detail'].items():
 for role,stats in st['roles'].items():
  poly,mn,mx=limits[role];issues=[]
  if stats['polyphony']>poly:issues.append('polyphony')
  if stats['min_duration']<mn:issues.append('minDuration')
  if stats['max_duration']>mx:issues.append('maxDuration')
  if issues:violations.append(dict(id=sid,role=role,issues=issues,actual=stats,engine_assumption=dict(polyphony=poly,minDuration=mn,maxDuration=mx)))
dump('INSTRUMENT_CONSTRAINTS.json',dict(base='4c43bd2',limits=limits,study_violations=violations,warning='Generator assumptions, not externally detected patches. Reassigning a role or changing an assumed articulation needs an explicit decision; do not drop or shorten notes to inflate compatibility.'))
# Per-ID assessment: core limitations, complete literal facts and specific choices.
for r in rs:
 id,k,f=r['id'],r['kind'],r['fields'];needs=[];cites=[];status='E';why=[]
 if k=='H':
  cites=['HARMONY','VOICING','HOLD','MODE'];layers=any(s.get('#')=='D'for s in r['states'])
  needs=['voicing_constraints'];why=[r['progression'],f"{r['state_count']} notierte Zustände, Oberstimmenzahl {r['voices']}; "+('alle Tonklassen an angegebener Wurzel als bestehende Typen möglich.'if r['pc_data_fit']else'kein vollständiger Typ-Match an den angegebenen Wurzeln; kein enharmonisches Umbenennen.')]
  if any(s['unrooted_object']for s in r['states']):needs+=['tone_objects']
  if layers:needs+=['layers'];why+=['Gleichzeitige K/D-Schichten sind keine zusätzliche Zeitfolge.']
  if 'Pedalrolle'in f.get('Algorithmische Voraussetzungen',''):needs+=['held_upper'];why+=['Basspedalkern vorhanden; Bindung und explizite Bass-/Halteabsicht der Vorlage fehlen.']
  if r['state_count']>1:needs+=['held_upper']
  r['harmonic_material_ready']=r['pc_data_fit'];r['template_import_ready']=False
 elif k=='U':
  cites=['VOICING','HOLD','PEDAL','NOTES'];needs=['transition_intent','held_upper'];why=[f"{r['state_count']} Zustände, zwingend deklarierte Haltemengen {r['required_held_pitches']} (weitere gemeinsame Tonhöhen nur mögliche Kandidaten); Absicht: {f.get('Auflösungsabsicht')}.",'Vorhandene Gemeinsamton-Boni und extendOnly bewirken mögliche Bindung, garantieren keine konkret verlangte Oberstimme.']
  if f.get('Vorhalt'):needs+=['timed_resolution'];why+=[f['Vorhalt']]
  if 'gestaffelt'in f.get('Algorithmische Voraussetzungen',''):needs+=['staggered']
  if id=='EM-U047':needs+=['tone_objects']
  if id=='EM-U048':needs+=['tone_objects','layers'];why+=['Vier→sechs Stimmen: neu hinzukommende Stimmen müssen eigene Identität/Einsätze erhalten.']
 elif k=='R':
  cites=['TIME','RHYTHM','NOTES'];why=[f"{len(r['layers'])} Schicht(en), Perioden {[s['period']for s in r['layers']]}, Gesamtzyklus mit Hosttakt {r['joint_bar_ticks']}Ticks; Rollen {f['Rollen']}."]
  if len(r['layers'])>1 or r['period']%r['bar_ticks'] or r['period']>7680 or r['off_old_grid'] or f['Takt']!='4/4':needs=['periods']if len(r['layers'])>1 or r['period']%r['bar_ticks']else[];needs+=['tick_authoring'];why+=['960 PPQ und Dispatcher reichen zeitlich aus; kein allgemeiner tickgenauer Autoren-/Mehrperiodenverbraucher vorhanden.']
  else:status='A';why+=['Ein-/Zweitaktiges Sechzehntelraster passt in die vorhandene Rhythmusplanung; Rollen-/Gate-Anbindung mit Instrumentenprüfung erforderlich.']
  if 'ST'in f['Rollen']:why+=['ST bleibt Trigger36; 120Ticks der Studie unterschreiten die heutige Standard-Mindestdauer240.']
 elif k=='B':
  cites=['PEDAL','NOTES','RHYTHM','HARMONY'];why=[f"{f['Typ']}, Töne {r['pitches']}, {f['Rhythmus']}; deklarierter Zyklus {f['Gesamtzyklus']}."]
  if not r['pitches']:status='D';why+=['Auslassen der Bassrolle ist bereits möglich; nicht durch verpflichtendes Fundament ersetzen.']
  elif len(r['pitches'])==1 and 'eigene Dauern: 15360' in f['Rhythmus'] and f['Rollen']=='LB':status='A';why+=['Einzelpedalkern kann die eigene Lebensdauer und explizite Dissonanzberechtigung tragen; benötigte Tonklasse/Quelle und genaue Start-/Endbindung ergänzen. Keine Aufhebung von Slash-Bass-Schutz.']
  else:needs=['bass_sequence','scoped_tones'];why+=['Explizite tonikabezogene Folge ist kein beliebiges bestehendes Auto-Bassmuster.']
  if r.get('rhythm_refs')and any(by[i]['period']%by[i]['bar_ticks']or len(by[i]['layers'])>1 for i in r['rhythm_refs']):needs+=['periods']
  if id=='EM-B031':needs+=['instrument'];why+=['Tatsächliche Oktavdopplung KB benötigt2 statt heutiger1 Stimme.']
  if id=='EM-B047':needs+=['transition_intent'];why+=['Antwort beginnt1920Ticks nach dem Ruf; Bezug zum Ruf muss explizit geplant sein.']
 elif k=='C':
  cites=['MOTIF','MODE'];needs=['cell_identity','cell_operations','scoped_tones'];why=[f"Identität {f['Typ']}, PC-Menge {r['pitches']}, IV {r['iv_actual']}; Menge/Klasse/Ordnung nicht als zufälliges Motiv uminterpretieren."]
  if f['Typ']=='KERN':why+=['Kerntöne und austauschbarer Farbton benötigen getrennte Gültigkeit.']
  if f['Typ']=='RHY':why+=['Zusätzlich feste Rhythmusbindung; Permutation ausdrücklich nicht zulässig.']
  if id=='EM-C035':why+=['Primform weicht unter packed-right/Forte ab, ist aber TnI-äquivalent (Rahn/Forte-Konventionsfrage), kein anderer Tonvorrat. Konvention vor Klassenschlüssel festlegen.']
 elif k=='M':
  cites=['MOTIF','MODE','ROLES','TIME'];why=[f"{r['note_count']} Noten, {r['duration']}Ticks, Intervalle {r['intervals_actual']}; Rollen {f['Rollen']}."]
  if 2<=r['note_count']<=8 and r['duration']<=2*(5760 if f['Takt']=='12/8'else 2880 if f['Takt']=='3/4'else 3840)and not r['off_old_grid']:
   status='A';why+=['Feste Grundfigur passt zur bestehenden Autorennotation und Motivspeicherung; harmonische Quellmasken vollständig annotieren und Originalkontur schützen, nicht akkordtonrunden. Optionale Zell-/Rollenoperationen sind damit nicht implementiert.']
  else:
   if r['note_count']>8 or r['duration']>7680:needs+=['long_line']
   if r['note_count']<2:needs+=['timed_resolution'];why+=['Ein einzelner offener Vorhalt ist kein zweitoniges Motiv; nicht durch erfundene zweite Note reparieren.']
   if r['off_old_grid']:needs+=['tick_authoring']
  if f['Typ']=='Additiv':why+=['Einzelfigur ist nicht die übergreifende Enthüllungsstrategie; diese fehlt bei P/T.']
 elif k=='P':
  cites=['MOTIF','ROLES','POLICY'];needs=['phrase_plan'];why=[f['Bauplan'],'Heutige Wiederkehr-/Vordergrundfenster sind keine Ausführung dieser vollständigen notierten Rollen-/Abschnittsfolge.']
  if any(i in r['refs']for i in('EM-T005','EM-T018'))or id=='EM-P002':needs+=['addiv']
  if any(i in r['refs']for i in('EM-T003',))or id in('EM-P005','EM-P006','EM-P020'):needs+=['modules']
  if 'EM-T017'in r['refs']:needs+=['block']
 elif k=='K':
  cites=['ROLES','NOTES','RHYTHM','MOTIF'];needs=['modules'];why=[f"{f.get('Art')}, Rolle {f.get('Rolle')}, Polyphonie {f.get('Polyphonie')}, Periode {f.get('Periode')}; Quelle {f.get('Quelle')}.",'Modulgrenzen, Mehrfachkompatibilität und lokale Tonabsicht fehlen; paarweise Freigaben nicht als Dreierfreigabe behandeln.']
  if f.get('harmonische Absicht')=='FSCHICHT':needs+=['layers','scoped_tones']
  if f.get('Rolle')in('KB','LB')and int(f.get('Polyphonie','1'))>1:needs+=['instrument']
 elif k=='EF':
  cites=['TIME','ROLES','POLICY'];needs=['event_field','scoped_tones'];why=[f"Zelle {f.get('Zelle')}, Dichte {f.get('Dichte')}, Mindestabstand {f.get('Mindestabstand')}, Antwort {f.get('Antwort (Imitation/Widerspruch/Schweigen)')}.",'Die zweite EF-Fundstelle ist dieselbe ID als Studie, keine zweite Vorlage.']
 elif k=='S':
  cites=['HARMONY','MOTIF','ROLES','NOTES','POLICY'];needs=['phrase_plan'];f=r['study_fields'];why=[f"{f.get('Länge')}, Rollen {f.get('Rollenspuren')}; Schichten {f.get('Schichten')}; Entwicklung {f.get('Entwicklung')}.",'Vollständiger Mehrrollenplan mit Quellen, lokalen Kontexten und Lifetimes fehlt; eine korrekte MIDI-Datei ist kein ausgeführtes Engine-Profil.']
 elif k=='T':
  cites=['MOTIF','POLICY','HOLD'];why=[f.get('Verfahren',''),f"Invariante: {f.get('Invariante')}; Risiko: {f.get('Risiko')}."]
  specific={'001':['cell_identity','cell_operations'],'002':['cell_identity','voicing_constraints'],'003':['modules'],'004':['addiv'],'005':['addiv'],'006':['tick_authoring'],'007':['tick_authoring'],'008':['periods'],'009':['held_upper','scoped_tones'],'010':['cell_identity','cell_operations'],'011':['modules'],'012':['staggered'],'013':['phrase_plan'],'014':['phrase_plan'],'015':['layers'],'016':['phrase_plan'],'017':['block'],'018':['addiv'],'019':['cell_identity','cell_operations'],'020':['cell_identity','cell_operations']}
  needs=specific[id[-3:]]
  if id=='EM-T004':why+=['Fragmentierung vorhanden, aber nur Schlussfigur max3 Noten; Quelle verlangt beliebige Kopf-n, daher nicht als vollständig vorhanden einstufen.']
  if id=='EM-T007':why+=['Augmentation×2 vorhanden; graduelle1,5-Extension und Mehrdurchlaufplanung fehlen.']
 if id in('EM-S016','EM-S044'):
  status='K';why+=['Referenz-AR C010 verliert in konstanten Harmonieabschnitten ihre Vierklassen-Identität durch Akkordtonanpassung (siehe CELL_IDENTITY_AUDIT); Quellidentität oder bewusste Variante zuerst festlegen.']
 if id in clarify:status='K';why.append(clarify[id])
 r['assessment']=dict(status=status,reason=' '.join(why),required_capabilities=sorted(set(needs)),code_references={key:caps[key]for key in cites},requires_import_even_if_D=True,optional_transformations_not_assumed_implemented=True)
# Propagate necessary source dependencies as explicit extra facts, without mistaking
# optional suitable/unsuitable references for mandatory sources.
for r in rs:
 if r['kind']in('K','P','S','EF'):
  fields=r.get('study_fields',r['fields'])if r['kind']=='S'else r['fields'];value=fields.get('Quelle',fields.get('Bauplan',fields.get('Schichten',fields.get('Zelle',''))))+' '+fields.get('Harmonie','')+' '+fields.get('Anker','')
  mandatory=sorted(set(re.findall(r'EM-(?:EF\d{2}|[HURBCMPKTS]\d{3})',value))-{r['id']})
  r['assessment']['source_dependencies']=[dict(id=i,status=by[i]['assessment']['status'],missing=by[i]['assessment']['required_capabilities'])for i in mandatory]
  if any(by[i]['assessment']['status']=='K'for i in mandatory):r['assessment']['clarification_dependency']=True
 # Runtime study constraints must not be hidden by permissive research thresholds.
 study_id=r['id']if r['kind']in('S','EF')else None
 if study_id:r['assessment']['reference_instrument_conflicts']=[v for v in violations if v['id']==study_id]
# Unresolved mandatory sources take precedence over a capability-only primary label.
changed=True
while changed:
 changed=False
 for r in rs:
  deps=r['assessment'].get('source_dependencies',[]);blocked=[d['id']for d in deps if by[d['id']]['assessment']['status']=='K']
  if blocked:
   r['assessment']['clarification_dependency']=True
   if r['assessment']['status']!='K':
    r['assessment']['status']='K';r['assessment']['reason']+=' Notwendige Quelle zuerst klären: '+', '.join(blocked)+'.';changed=True
for r in rs:
 for d in r['assessment'].get('source_dependencies',[]):d['status']=by[d['id']]['assessment']['status']
counts={k:dict(collections.Counter(r['assessment']['status']for r in rs if r['kind']==k))for k in ['H','U','R','B','C','M','P','K','EF','T','S']}
dump('TECHNICAL_INVENTORY.json',dict(base='4c43bd2',active=False,legend={'D':'Grundverhalten direkt darstellbar (noch nicht importiert)','A':'Vorhandene Fähigkeiten, begrenzte Daten-/Rollenanbindung','E':'Mindestens eine zusätzliche gemeinsame musikalische Fähigkeit nötig','K':'Widerspruch oder wesentliche Festlegung zuerst klären'},counts=counts,capabilities=needed,records=rs))
md=['# Vollständiges technisches Inventar – Ennio Morricone','', 'Ausgang `4c43bd2`. Keine Morricone-Vorlage aktiviert. D/A/E/K siehe IMPLEMENTATION_PLAN.md. Jede Zeile bewertet die definierte musikalische Grundform; optionale Transformationen und alle Kombinationen sind nicht automatisch mitfreigegeben. Die JSON-Datei enthält vollständige Ton-/Zeitdaten, Quellenfelder, Instrumentenkonflikte und konkrete Codebezüge.','']
for k in counts:
 codebases={v for r in rs if r['kind']==k for v in r['assessment']['code_references'].values()}
 md+=['## '+k,'','Codebasis: '+'; '.join('`'+v+'`'for v in sorted(codebases))+'.','', '| ID | Name | Status | Konkreter Grund | Erforderliche Fähigkeit |','|---|---|---|---|---|']
 for r in rs:
  if r['kind']!=k:continue
  a=r['assessment'];reason=a['reason'].replace('|',' / ').replace('\n',' ');needs=', '.join(a['required_capabilities'])or'Begrenzte Quellenbindung / vorhandenes Verhalten'
  md.append(f"| {r['id']} (Quelle Z.{r['source_line']}) | {r['name']} | {a['status']} | {reason} | {needs} |")
 md+=['']
(HERE/'TECHNICAL_INVENTORY.md').write_text('\n'.join(md).rstrip()+'\n')
summary=dict(base='4c43bd2',total=534,classification=dict(collections.Counter(r['assessment']['status']for r in rs)),by_kind=counts,harmonic_pc_data_ready=sum(r['kind']=='H'and r['pc_data_fit']for r in rs),u_referenced_in_exported_csv=sorted({id for row in rows for id in re.findall(r'EM-U\d{3}',row['vorlage'])}),u_probe_total_boundaries=sum(max(0,len(r.get('states',[]))-1)for r in rs if r['kind']=='U'),reference_functions=dict(collections.Counter(row['tonfunktion']for row in rows)),canonical_m_cell_subset_failures=[r['id']for r in rs if r['kind']=='M'and not all(r['declared_cell_fit'].values())],reference_studies_with_instrument_conflict=len({v['id']for v in violations}))
dump('AUDIT_SUMMARY.json',summary)
print('Assessment',counts);print('Instrument conflicts',len(violations),'studies',len({v['id']for v in violations}));print('Cell literal changes',[(c['id'],len(c['changed_aggregate_examples']))for c in cell_checks if c['changed_aggregate_examples']])
