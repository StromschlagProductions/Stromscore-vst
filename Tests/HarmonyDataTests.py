"""Offline validation, generation drift, sharing and real compiled large-pool tests."""
import copy,importlib.util,json,pathlib,shutil,subprocess,tempfile,unittest,os,re
root=pathlib.Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('harmony_generator',root/'scripts/generate_harmony_catalog.py');gen=importlib.util.module_from_spec(spec);spec.loader.exec_module(gen)
class HarmonyDataTests(unittest.TestCase):
 @classmethod
 def setUpClass(cls):cls.original=gen.load(root/'data/harmony')
 def rejected(self,mutate):
  data=copy.deepcopy(self.original);mutate(data)
  with self.assertRaises(gen.ValidationError):gen.validate(data)
 def test_existing_and_reproducible(self):
  m=gen.validate(self.original);self.assertEqual(len(m['templates']),181);self.assertEqual(len(m['profiles']),4)
  self.assertEqual(set(m['templates']),set(range(1001,1049))|set(range(2001,2040))|{30000+n for n in range(1,48) if n not in (33,40)}|set(self.original['profiles.json']['profiles'][3]['score_pool']))
  self.assertIn([1047,2015,2019],m['duplicate_groups'])
  for path,content in gen.emit(self.original).items():self.assertEqual((root/path).read_text(encoding='utf-8'),content)
 def test_explicit_octatonic_harmonic_and_bass_context(self):
  templates={t['id']:t for t in self.original['catalog.json']['templates']}
  expected={40012,40014,40015,40016,40017,40019,40046,40054}
  self.assertEqual({i for i,t in templates.items() if t['tonality']['mode']=='octatonic'},expected)
  for identifier in expected:self.assertEqual(templates[identifier]['tonality']['center_pc'],0)
  index=next(i for i,t in enumerate(self.original['catalog.json']['templates']) if t['id']==40012)
  self.rejected(lambda d:d['catalog.json']['templates'][index]['chords'][0].update(bass=2))
  self.rejected(lambda d:d['catalog.json']['templates'][index]['chords'][0].update(type='MinMaj7'))
  self.rejected(lambda d:d['catalog.json']['templates'][index]['tonality'].update(center_pc=1))
 def test_barry_research_material_and_shared_alias(self):
  spec=importlib.util.spec_from_file_location('barry_import',root/'scripts/import_barry_research.py');module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
  records=module.research();self.assertEqual(len(records),46)
  m=gen.validate(self.original);profile=m['profiles'][1];self.assertFalse(profile['harmony_selection_only']);self.assertEqual(len(profile['score_pool']),46)
  self.assertEqual(set(self.original['catalog.json']['pools']['score']),set(range(1001,1049)))
  for r,i in zip(records,profile['score_pool']):
   expected=1003 if r['number']==40 else 30000+r['number'];self.assertEqual(i,expected)
   t=m['templates'][i];self.assertIn(r['ref'],m['sources'])
   for a,b in zip(t['chords'],r['chords']):self.assertEqual((a['root'],a['type'],a['bars'],a['root'] if a['bass']is None else a['bass']),(b['root'],b['type'],b['bars'],b['bass']))
   self.assertEqual(len(t['chords']),len(r['chords']))
   # Independently check the source's explicit note column, not just the importer's symbol mapping.
   rows=[line for line in r['text'].splitlines() if re.match(r'^\| \d+ \|',line)]
   for chord,line in zip(t['chords'],rows):
    columns=[v.strip() for v in line.strip('|').split('|')]
    pitches={(chord['root']+n)%12 for n in m['definitions'][chord['type']]['intervals']}
    pitches.add(chord['root'] if chord['bass']is None else chord['bass'])
    self.assertEqual(pitches,{module.pc(note) for note in columns[4].split()},r['ref'])
   if i!=1003:self.assertEqual(t['xyz'],r['xyz']);self.assertEqual(t['source_ref'],r['ref']);self.assertEqual(t['coloration'],'protected')
  self.assertEqual(profile['score_overrides'][0]['template_id'],1003)
  self.assertEqual(m['templates'][1003]['xyz'],[.08,.1,.6]);self.assertEqual(m['templates'][1003]['coloration'],'flexible')
  # A membership reference cannot invent/redefine harmony, name a Pop-only entry, or carry invalid anchors.
  for mutate in [lambda d:d['profiles.json']['profiles'][1]['score_pool'].append(99999),
    lambda d:d['profiles.json']['profiles'][1]['score_pool'].append(2037),
    lambda d:d['profiles.json']['profiles'][1]['score_pool'].append(1003),
    lambda d:d['profiles.json']['profiles'][1]['score_overrides'][0].update(chords=[]),
    lambda d:d['profiles.json']['profiles'][1]['score_overrides'][0].update(xyz=[0,0,2]),
    lambda d:d['profiles.json']['profiles'][1]['score_overrides'][0].update(source_ref='missing')]:self.rejected(mutate)
 def test_import_fixture_accepts_windows_line_endings(self):
  from unittest.mock import patch
  import HarmonyImportFixtures as fixtures
  headers=fixtures.header_snapshot(root,None)
  engine=headers['ScoreEngine.h'].replace(b'\r\n',b'\n')
  with tempfile.TemporaryDirectory() as tmp:
   outputs=[]
   for ending in (b'\n',b'\r\n'):
    snapshot=dict(headers);snapshot['ScoreEngine.h']=engine.replace(b'\n',ending)
    with patch.object(fixtures,'header_snapshot',return_value=snapshot):
     dest=pathlib.Path(tmp)/str(len(outputs));fixtures.prepare(dest,explicit=True)
    result=(dest/'ScoreEngine.h').read_bytes();outputs.append(result)
    self.assertIn(b'inline WendungId importTestId=',result)
    self.assertIn(b'if(importTestId!=WendungId::invalid)return false;',result)
    self.assertEqual((root/'Source/ScoreEngine.h').read_bytes(),headers['ScoreEngine.h'])
   self.assertEqual(*outputs)
 def test_bad_definitions(self):
  mutations=[lambda d:d['catalog.json']['templates'].append(copy.deepcopy(d['catalog.json']['templates'][0])),
   lambda d:d['catalog.json']['templates'][0].update(id=65535),lambda d:d['catalog.json']['templates'][0].update(symbol='class'),
   lambda d:d['catalog.json']['templates'][0].update(name=''),lambda d:d['catalog.json']['templates'][0].update(xyz=[.1,[.2,.3],.4]),
   lambda d:d['catalog.json']['templates'][0].update(xyz=[float('nan'),.2,.3]),lambda d:d['catalog.json']['templates'][0].update(xyz=[1.1,.2,.3]),
   lambda d:d['catalog.json']['templates'][0]['chords'][0].update(root=-1),lambda d:d['catalog.json']['templates'][0]['chords'][0].update(root=True),
   lambda d:d['catalog.json']['templates'][0]['chords'][0].update(type='Maj6'),lambda d:d['catalog.json']['templates'][0]['chords'][0].update(type=[]),
   lambda d:d['catalog.json']['templates'][0]['chords'][0].update(bass=12),lambda d:d['catalog.json']['templates'][0]['chords'][0].update(bass=-1),
   lambda d:d['catalog.json']['templates'][0]['chords'][0].update(bars=.5),lambda d:d['catalog.json']['templates'][0]['chords'][0].update(bars=0),
   lambda d:d['catalog.json']['templates'][0]['chords'][0].update(bars=3),lambda d:d['catalog.json']['templates'][0].update(chords=[]),
   lambda d:d['catalog.json']['templates'][0].update(chords=[copy.deepcopy(d['catalog.json']['templates'][0]['chords'][0])]*9),
   lambda d:d['catalog.json']['templates'][0].update(instruments='not a harmonic field'),
   lambda d:d['catalog.json']['templates'][0].update(source_ref='unknown'),lambda d:d['catalog.json']['templates'][0]['tonality'].update(mode='phrygian'),
   lambda d:d['catalog.json']['templates'][0]['tonality'].update(mode='ionian'),lambda d:d['catalog.json']['pools']['score'].append(99999),
   lambda d:d['catalog.json']['pools']['pop_rock'].append(1001),lambda d:d['profiles.json']['profiles'][1]['weights'][0].update(template_id=99999),
   lambda d:d['profiles.json']['profiles'][1]['weights'][0].update(factor=0),lambda d:d['profiles.json']['profiles'][1]['weights'][0].update(factor=float('inf')),
   lambda d:d['profiles.json']['profiles'][1]['weights'].append(copy.deepcopy(d['profiles.json']['profiles'][1]['weights'][0])),
   lambda d:d['profiles.json']['profiles'][1].update(id=0),lambda d:d['arrangements.json']['recipes'][0].update(arp=['ArpUnknown','ArpUp']),
   lambda d:d['catalog.json']['templates'][0].update(coloration='literal'),lambda d:d['arrangements.json']['bindings'][0].update(recipe='unknown'),
   lambda d:d['chord_types.json']['types'][0].update(intervals=[0,4,99]),lambda d:d['chord_types.json']['types'][0].update(intervals=[0,4,4]),
   lambda d:d['chord_types.json']['types'][0].update(intervals=[0,2,4,5,7,9]),lambda d:d['chord_types.json']['types'][0].update(value=True),lambda d:d['chord_types.json']['types'][0].update(intervals=[0,3,7])]
  for i,mutation in enumerate(mutations):
   with self.subTest(case=i):self.rejected(mutation)
 def test_coloration_is_a_validated_harmonic_fact(self):
  self.assertTrue(all(t['coloration']==('flexible' if t['id']<=2036 else 'protected') for t in self.original['catalog.json']['templates']))
  d=copy.deepcopy(self.original);d['catalog.json']['templates'][0]['coloration']='protected'
  m=gen.validate(d);self.assertEqual(m['templates'][1001]['coloration'],'protected')
  outputs=gen.emit(d);self.assertIn('ChordColoration::protectedColor',outputs['Source/HarmonyCatalog.generated.h'])
  self.assertEqual(outputs['Source/HarmonyStrategies.generated.h'],gen.emit(self.original)['Source/HarmonyStrategies.generated.h'])
  self.rejected(lambda d:d['catalog.json']['templates'][0].pop('coloration'))
  self.rejected(lambda d:d['catalog.json']['templates'][0].update(coloration=True))
  self.rejected(lambda d:d['arrangements.json']['recipes'][0].update(coloration='protected'))
 def test_extensible_chord_registry(self):
  d=copy.deepcopy(self.original);types=d['chord_types.json']['types'];types.append({'id':'SyntheticStack','value':len(types),'suffix':'test','minor':False,'intervals':[0,7,14,21]})
  d['catalog.json']['templates'][0]['chords'][0]['type']='SyntheticStack';gen.validate(d)
  self.assertIn('SyntheticStack',gen.emit(d)['Source/ChordTypes.generated.h'])
  for iv in ([0],[0,1,2,3,4,5],[0,4,24]):
   bad=copy.deepcopy(d);bad['chord_types.json']['types'][-1]['intervals']=iv
   with self.assertRaises(gen.ValidationError):gen.validate(bad)
 def test_nonchord_slash_bass_is_valid(self):
  d=copy.deepcopy(self.original);t=d['catalog.json']['templates'][0];t['chords']=[{'root':10,'type':'Maj','bars':8,'bass':0}];t['tonality']={'center_pc':0,'mode':'mixolydian'}
  gen.validate(d)
 def test_duplicate_json_keys_and_drift(self):
  with tempfile.TemporaryDirectory() as tmp:
   p=pathlib.Path(tmp)
   for f in gen.FILES:(p/f).write_text(json.dumps(self.original[f]))
   (p/'catalog.json').write_text('{"schema_version":1,"schema_version":1}')
   with self.assertRaises(gen.ValidationError):gen.load(p)
   for f in gen.FILES:(p/f).write_text(json.dumps(self.original[f]))
   result=subprocess.run([os.sys.executable,str(root/'scripts/generate_harmony_catalog.py'),'--source',str(p),'--output-root',str(p/'missing'),'--check'],capture_output=True)
   self.assertNotEqual(result.returncode,0);self.assertFalse((p/'missing').exists())
 def test_large_shared_catalog_compiles_and_selects(self):
  compiler=shutil.which('c++') or shutil.which('g++')
  if not compiler:self.skipTest('C++17 compiler unavailable; offline validation still runs')
  d=copy.deepcopy(self.original);cat=d['catalog.json'];binding=d['arrangements.json']['bindings'][0]['recipe']
  for i in range(1200):
   t=copy.deepcopy(cat['templates'][0]);t.update(id=3000+i,symbol='synthetic'+str(i),name='Synthetic '+str(i),xyz=[.5,.5,.5],genres=['score'],chords=[{'root':0,'type':'Maj','bars':8,'bass':None}],tonality={'center_pc':0,'mode':'mixolydian'});cat['templates'].append(t);cat['pools']['score'].append(t['id']);d['arrangements.json']['bindings'].append({'template_id':t['id'],'recipe':binding});d['notes.json']['entries'].append({'template_id':t['id'],'idea':'Synthetic test only','instruments':'Independent'})
  cat['templates'][0]['genres'].append('pop_rock');cat['pools']['pop_rock'].append(1001)
  for i in range(len(d['profiles.json']['profiles']),40):d['profiles.json']['profiles'].append({'id':i,'symbol':'testProfile'+str(i),'name':'Test '+str(i),'harmony_selection_only':True,'weights':[{'template_id':3000,'factor':2}]})
  m=gen.validate(d);self.assertEqual(len(m['templates']),1381);self.assertEqual(len(m['profiles']),40);self.assertTrue(any(len(g)>=1200 for g in m['duplicate_groups']))
  with tempfile.TemporaryDirectory() as tmp:
   p=pathlib.Path(tmp);source=p/'Source';source.mkdir()
   for f in (root/'Source').glob('*.h'):shutil.copyfile(f,source/f.name)
   for name,content in gen.emit(d).items():target=p/name;target.parent.mkdir(parents=True,exist_ok=True);target.write_text(content)
   code=p/'test.cpp';code.write_text('''#include "ScoreEngine.h"
#include "TestSupport.h"
#include <memory>
using namespace stromscore;
int main(){static_assert(kMaxWendungen==1248);static_assert(kCustomWendung>=kMaxWendungen);
CHECK(harmonyTemplates.size()==1381);CHECK(composition::compositionProfiles.size()==40);
CHECK(findHarmonyTemplate(static_cast<WendungId>(3000))->tonality.mode==composition::Mode::mixolydian);
CHECK(wendungIndex(GenrePopRock,WendungId::scoreHalbtonNachbarn)>=0);
CHECK(composition::harmonicPreference(static_cast<composition::ProfileId>(39),static_cast<WendungId>(3000))==2.f);
CHECK(!findHarmonyTemplate(static_cast<WendungId>(0xfffffffe)));
Settings s;s.x=s.y=s.z=.5f;s.variety=0;int ids[kMaxWendungen];
{NoAllocations guard;CHECK(Generator::candidates(s,ids,kMaxWendungen)==1200);}
bool aboveOldSentinel=false;for(int salt=0;salt<128;++salt){int i=Generator::pick(s,salt);CHECK(i>=48&&i<1248);aboveOldSentinel|=i>=1000;}CHECK(aboveOldSentinel);
auto g=std::make_unique<Generator>();Transport t;t.playing=true;EventList events;
{NoAllocations guard;g->process(t,s,512,events);}CHECK(!events.overflow&&g->wendung()!=kCustomWendung);
}''')
   exe=p/'test';flags=['-g','-fsanitize=address,undefined','-fno-omit-frame-pointer'] if os.environ.get('HARMONY_TEST_SANITIZE') else [];build=subprocess.run([compiler,'-std=c++17','-O1']+flags+['-I',str(source),'-I',str(root/'Tests'),str(code),'-o',str(exe)],capture_output=True);self.assertEqual(build.returncode,0,build.stderr.decode());subprocess.run([str(exe)],check=True)
if __name__=='__main__':unittest.main()
