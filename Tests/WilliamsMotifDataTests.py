"""Canonical P3 registration, provenance and unmodified source-note checks."""
import unittest,sys,pathlib,json,copy
from unittest.mock import patch
root=pathlib.Path(__file__).resolve().parents[1];sys.path.insert(0,str(root/'scripts'))
from build_williams_motifs import outputs,DEFER
class DataTests(unittest.TestCase):
 def test_generated(self):
  for name,text in outputs().items():self.assertEqual((root/name).read_text(encoding="utf-8"),text)
 def test_complete_inventory(self):
  rows=json.loads(outputs()['data/williams/motifs.json'])['motifs']
  self.assertEqual({x['id'] for x in rows},{f'JW-M{n:02}' for n in range(1,49)})
  self.assertEqual(len({x['runtime_id'] for x in rows}),48)
  self.assertEqual(sum(x['enabled'] for x in rows),32)
  for x in rows:
   self.assertEqual(x['runtime_id'],50000+int(x['id'][-2:]))
   self.assertEqual(x['enabled'],int(x['id'][-2:])not in DEFER)
   self.assertTrue(x['enabled'] or x['reason'])
 def test_reject_manifest_drift(self):
  path=root/'docs/research/john-williams/TECHNICAL_INVENTORY.json';original=json.loads(path.read_text(encoding="utf-8"));read_text=pathlib.Path.read_text
  for field,value in [('sequence','C4/32'),('xyz',[1.4,.7,.6]),('name','Unreviewed replacement')]:
   data=copy.deepcopy(original);next(x for x in data['inventory']if x['id']=='JW-M40')[field]=value
   def read(current,*args,**kwargs):return json.dumps(data)if current==path else read_text(current,*args,**kwargs)
   with patch.object(pathlib.Path,'read_text',new=read):
    with self.assertRaises(AssertionError):outputs()
 def test_exact_source_material(self):
  canonical=json.loads((root/'docs/research/john-williams/TECHNICAL_INVENTORY.json').read_text(encoding="utf-8"))['inventory'];by={x['id']:x for x in canonical}
  for x in json.loads(outputs()['data/williams/motifs.json'])['motifs']:
   self.assertEqual(x['sequence'],by[x['id']]['sequence']);self.assertEqual(x['xyz'],by[x['id']]['xyz'])
   self.assertEqual(len(x['notes']),by[x['id']]['note_count'])
   for a,b in zip(x['notes'],x['notes'][1:]):self.assertLessEqual(a['at_ticks']+a['length_ticks'],b['at_ticks'])
   self.assertLessEqual(x['notes'][-1]['at_ticks']+x['notes'][-1]['length_ticks'],2*x['meter'][0]*3840//x['meter'][1])
if __name__=='__main__':unittest.main()
