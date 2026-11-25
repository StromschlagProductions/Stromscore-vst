"""Prove that the explicit Score-role allowance cannot hide protected MIDI changes."""
import pathlib,sys,unittest,tempfile
sys.path.insert(0,str(pathlib.Path(__file__).resolve().parents[1]/'scripts'))
from role_regression import assert_score_role_delta
class RoleRegressionTests(unittest.TestCase):
 def setUp(self):
  self.old=[(0,8,9,72,90,0),(100,8,9,72,0,0),(200,7,8,67,80,0),(240,7,8,67,0,0)]
  self.new=self.old+[(400,7,8,65,70,0),(450,7,8,65,0,0)]
 def verify(self,new):return assert_score_role_delta(self.old,sorted(new),layout='import')
 def test_independent_dialogue_allowed(self):self.assertEqual(self.verify(self.new)['added_dialogue_attacks'],1)
 def test_melody_bass_cc_and_old_answers_protected(self):
  for before,after in [((0,8,9,72,90,0),(0,8,9,73,90,0)),((200,7,8,67,80,0),(200,7,8,68,80,0))]:
   changed=self.new.copy();changed[changed.index(before)]=after
   with self.assertRaises(AssertionError):self.verify(changed)
  for event in [(10,2,3,45,88,0),(10,7,8,11,99,1)]:
   with self.assertRaises(AssertionError):self.verify(self.new+[event])
 def test_overlap_and_hanging_notes_rejected(self):
  with self.assertRaises(AssertionError):self.verify(self.old+[(50,7,8,65,70,0),(80,7,8,65,0,0)])
  with self.assertRaises(AssertionError):self.verify(self.new[:-1])
 def test_historical_fixture_only_freezes_role_assignment(self):
  sys.path.insert(0,str(pathlib.Path(__file__).resolve().parent));import HarmonyImportFixtures as fixtures
  source=(fixtures.root/'Source/ScoreEngine.h').read_bytes()
  with tempfile.TemporaryDirectory() as tmp:
   fixtures.prepare(tmp,historical=True);header=(pathlib.Path(tmp)/'ScoreEngine.h').read_text()
   self.assertIn('return s.genre!=GenreScore||!on[kMelodie];',header)
   self.assertIn('composition::MotifWindow melodicRoleWindow',header)
   self.assertEqual((fixtures.root/'Source/ScoreEngine.h').read_bytes(),source)
if __name__=='__main__':unittest.main()
