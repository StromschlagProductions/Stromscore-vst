"""Offline canonical projection checks; no plugin/runtime file loading."""
import unittest,json,pathlib,subprocess,sys,hashlib
ROOT=pathlib.Path(__file__).resolve().parents[1]
def read(p):return json.loads((ROOT/p).read_text(encoding='utf-8'))
class HerrmannDataTests(unittest.TestCase):
 @classmethod
 def setUpClass(cls):
  cls.v=read('data/herrmann/vocabulary.json');cls.c={t['id']:t for t in read('docs/research/bernard-herrmann/TECHNICAL_INVENTORY.json')['templates']};cls.h={t['id']:t for t in read('data/harmony/catalog.json')['templates']}
 def test_registered_harmony_and_components(self):
  self.assertEqual(len(self.v['harmonies']),54)
  profile=read('data/harmony/profiles.json')['profiles'][2];self.assertEqual(set(profile['score_pool']),{b['harmony'] for b in self.v['harmonies']})
  for b in self.v['harmonies']:
   source=self.c[b['source']];h=self.h[b['harmony']];self.assertEqual(len(h['chords']),len(source['chords']))
   for actual,expected in zip(h['chords'],source['chords']):
    parsed=expected['parsed'];parsed=parsed['components'][-1]if parsed['components']else parsed
    self.assertEqual((actual['root'],actual['type'],actual['bars'],actual['bass'] if actual['bass'] is not None else actual['root']),(parsed['root'],parsed['type'],expected['bars'],expected['bass']))
   if b['upper_root']>=0:self.assertEqual({n%12 for n in b['upper_notes']},set(source['chords'][0]['parsed']['components'][0]['pcs']))
 def test_exact_rhythm_roles_and_gates(self):
  for f in self.v['figures']:
   if not f['source'].startswith('HE-R'):continue
   source=self.c[f['source']];parts=source['grid_events'];role={'harmonyLong':'LF','harmonyShort':'KF','bassLong':'LB','bassShort':'KB','movement':'AR','impulse':'TU'}[f['part']]
   expected=next(g['events']for g in parts if g['role']==role)
   self.assertEqual([(e['at'],e['duration'])for e in f['events']],[(e['at_ticks'],e['duration_ticks'])for e in expected])
 def test_full_bass_cycle(self):
  b=next(f for f in self.v['figures']if f['source']=='HE-B24');self.assertEqual(b['period'],9*3840);self.assertEqual(len(b['events']),48)
  for i,e in enumerate(b['events']):self.assertEqual(e['reference'],['root','octave','root'][i%3])
 def test_motifs_and_resolution_metadata(self):
  self.assertEqual(len(self.v['motifs']),22)
  for m in self.v['motifs']:
   source=self.c[m['source']];self.assertEqual(m['notes'],source['notes']);self.assertEqual(len(m['functions']),len(m['notes']))
   for i,(p,f,target)in enumerate(m['functions']):
    if f=='V':self.assertTrue(any(q==target for q,_,_ in m['functions'][i+1:]))
 def test_component_evolution_and_high_pedals(self):
  b={r['source']:r for r in self.v['harmonies']};self.assertEqual(b['HE-H60']['stages'],[[0,0,False],[7680,-12,False],[15360,-36,True]])
  self.assertEqual(b['HE-H64']['high'],79);self.assertEqual(b['HE-H68']['high'],90)
  self.assertEqual(b['HE-H10']['bass_mode'],1);self.assertEqual(b['HE-H57']['bass_mode'],2)
  self.assertEqual(b['HE-H07']['bass_notes'],[36,35,34,33])
 def test_not_silently_simplified(self):
  self.assertNotIn('HE-H54',{r['source']for r in self.v['harmonies']});self.assertIn('HE-H54',self.v['deferred'])
  self.assertFalse(read('data/harmony/profiles.json')['profiles'][2]['harmony_selection_only'])
 def test_drift_and_immutable_canon(self):
  subprocess.run([sys.executable,str(ROOT/'scripts/build_herrmann_vocabulary.py'),'--check'],cwd=ROOT,check=True,capture_output=True)
  folder='docs/research/bernard-herrmann/'
  for name in ['STROMSCORE_Bernard_Herrmann_Vokabular_Kanonisch.md','HE_Studien_Ereignisse.csv','HE_Studien_MIDI.zip','HE_Qualitaetspruefung.md']:
   old=subprocess.check_output(['git','show','58ea29d:'+folder+name],cwd=ROOT);self.assertEqual(hashlib.sha256(old).digest(),hashlib.sha256((ROOT/folder/name).read_bytes()).digest())
if __name__=='__main__':unittest.main()
