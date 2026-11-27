"""Check archive fidelity, full inventory, complete cycles and analysis boundaries."""
from pathlib import Path
import json,re,hashlib,subprocess,zipfile
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[2]
base='4c43bd2'
manifest=json.loads((HERE/'ARCHIVE_MANIFEST.json').read_text())
for entry in manifest['files']:
 path=HERE/entry['archived'];data=path.read_bytes()
 assert len(data)==entry['bytes']and hashlib.sha256(data).hexdigest()==entry['sha256'],path
assert len(manifest['files'])==7 and len(list(HERE.glob('*Lolita*')))==1
# Production code/GUI byte fidelity, not just a claim that no engine file was staged.
paths=subprocess.check_output(['git','ls-tree','-r','--name-only',base,'Source'],cwd=ROOT).decode().splitlines()
for name in paths:assert (ROOT/name).read_bytes()==subprocess.check_output(['git','show',base+':'+name],cwd=ROOT),name
inventory=json.loads((HERE/'TECHNICAL_INVENTORY.json').read_text());records=inventory['records'];by={r['id']:r for r in records}
assert len(records)==len(by)==534
human=(HERE/'TECHNICAL_INVENTORY.md').read_text();human_ids=re.findall(r'^\| (EM-(?:EF\d{2}|[HURBCMPKTS]\d{3})) ',human,re.M)
assert len(human_ids)==534 and set(human_ids)==set(by)
for r in records:
 a=r['assessment'];assert a['status']in'DAEK'and a['reason']and a['code_references']
 assert not r['production_active']
 for dep in a.get('source_dependencies',[]):
  assert dep['status']==by[dep['id']]['assessment']['status']
  if dep['status']=='K':assert a['status']=='K'
 assert all(i in by for i in r['refs'])
summary=json.loads((HERE/'AUDIT_SUMMARY.json').read_text());assert summary['classification']=={'D':1,'A':64,'E':439,'K':30}
assert summary['harmonic_pc_data_ready']==87 and summary['u_probe_total_boundaries']==59
assert not summary['canonical_m_cell_subset_failures']
for id in ('EM-H018','EM-H025','EM-H026','EM-H046','EM-H052','EM-H053','EM-H058','EM-H063','EM-H074','EM-B010','EM-B011','EM-B033','EM-R013','EM-R035','EM-R036','EM-R037','EM-R040','EM-K009','EM-S016','EM-S044'):assert by[id]['assessment']['status']=='K'
for r in records:
 if r['kind']=='R':
  assert all(l['onsets_match_pattern']is not False for l in r['layers'])
 if r['kind']=='M':assert r['length_matches']
 if r['kind']=='C':assert r['iv_matches']and r['prime_tni_equivalent']
assert by['EM-C025']['permitted_pc_variants']!=by['EM-C026']['permitted_pc_variants']
v=json.loads((HERE/'VALIDATION_RESULTS.json').read_text());assert v['csv_midi_equal']and v['physical_note_balance_ok']and v['csv_notes']==9752 and v['studies']==73 and v['stich_notes']==280
assert len(v['u_ids_referenced_in_csv'])==17 and len(v['v_target_checks'])==2
assert v['reference_channels']['ST']==[10]
probe=json.loads((HERE/'ENGINE_PROBE_RESULTS.json').read_text());assert len(probe['voices'])==708 and all(r['pc_identity_preserved']for r in probe['voices'])
assert [(r['id'],r['key'])for r in probe['voices']if r['lost_required']]==[('EM-U040',0),('EM-U040',1)]
x=json.loads((HERE/'XYZ_COMPATIBILITY.json').read_text());assert len(x['dense'])==1331 and len(x['cells'])==27 and x['engine_active_morricone_templates']==0
assert sum(all(v in(0,1)for v in c['xyz'])for c in x['cells'])==8
assert sum(1 for _ in(HERE/'PAIR_COMPATIBILITY.jsonl').open())==16280
assert sum(1 for _ in(HERE/'MODULE_TRIPLES.jsonl').open())==8436
m=json.loads((HERE/'MODULE_COMPATIBILITY.json').read_text());assert m['no_triple_certified_playable']and m['triples']==8436
# All derived JSON/JSONL is syntactically complete.
for path in HERE.glob('*.json'):json.loads(path.read_text())
for path in HERE.glob('*.jsonl'):
 for line in path.open():json.loads(line)
with zipfile.ZipFile(HERE/'EM_Studien_MIDI.zip')as z:assert z.testzip()is None
# Maintain the readable count table from the same final assessment.
plan=(HERE/'IMPLEMENTATION_PLAN.md').read_text()
for line in plan.splitlines():
 m=re.match(r'\| ([HURBCMPKTS]|EF) [^|]+\|(\d+)\|(\d+)\|(\d+)\|(\d+)\|(\d+)\|',line)
 if not m:continue
 k,n,d,a,e,c=m.groups();counts=inventory['counts'][k];assert [int(d),int(a),int(e),int(c)]==[counts.get(s,0)for s in'DAEK'];assert int(n)==sum(counts.values())
print('PASS: seven byte-exact originals; 534 complete assessments; CSV/MIDI/cycles/identities/708 core probes/1331XYZ/8436 triples; Source and GUI unchanged against4c43bd2')
