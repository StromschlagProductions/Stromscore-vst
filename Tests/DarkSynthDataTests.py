"""Independent archive/SMF/CSV audit and generated source validation."""
from pathlib import Path
import collections,csv,hashlib,json,struct,subprocess,sys,unittest,zipfile
ROOT=Path(__file__).resolve().parents[1];F=ROOT/'docs/research/dark-synth'
def midi(data):
 assert data[:4]==b'MThd';length,fmt,tracks,ppq=struct.unpack('>IHHH',data[4:14]);assert ppq==960;pos=8+length;notes=[];cc=[]
 for track in range(tracks):
  assert data[pos:pos+4]==b'MTrk';size=struct.unpack('>I',data[pos+4:pos+8])[0];b=data[pos+8:pos+8+size];pos+=8+size;i=0;at=0;running=0;active={}
  def vlq():
   nonlocal i
   value=0
   while True:
    v=b[i];i+=1;value=value*128+(v&127)
    if v<128:return value
  while i<len(b):
   at+=vlq();status=b[i]
   if status>=128:i+=1
   else:status=running
   if status==255:
    i+=1;n=vlq();i+=n;continue
   if status in (240,247):n=vlq();i+=n;continue
   running=status;kind=status&240;channel=(status&15)+1;n=1 if kind in (192,208)else 2;payload=b[i:i+n];i+=n
   if kind in (128,144):
    pitch,velocity=payload;key=(channel,pitch)
    if kind==144 and velocity:
     assert key not in active;active[key]=(at,velocity)
    else:
     begin,vel=active.pop(key);assert at>begin;notes.append((begin,at,channel,pitch,vel))
   elif kind==176:cc.append((at,channel,*payload))
  assert not active
 return sorted(notes),sorted(cc)
class DarkSynthDataTests(unittest.TestCase):
 def test_originals(self):
  for file,sha in json.loads((F/'ORIGINAL_SHA256.json').read_text()).items():self.assertEqual(hashlib.sha256((F/file).read_bytes()).hexdigest(),sha)
 def test_all_ids_and_runtime(self):
  d=json.loads((F/'TECHNICAL_INVENTORY.json').read_text(encoding='utf-8'));self.assertEqual(len(d['templates']),236);self.assertEqual(len({r['id']for r in d['templates']}),236);self.assertEqual(d['counts'],dict(H=65,B=21,Q=22,TU=28,E=18,HM=18,R=13,TO=7,K=10,S=30,MS=4))
  subprocess.run([sys.executable,str(ROOT/'scripts/build_dark_synth.py'),'--check'],check=True)
  catalog=json.loads((ROOT/'data/harmony/catalog.json').read_text(encoding='utf-8'));new=[t for t in catalog['templates']if t['source_ref']=='dark_synth_p2'];self.assertEqual(len(new),64);self.assertNotIn(61049,{t['id']for t in new})
  rotation=next(t for t in new if t['id']==61061);self.assertEqual([c['type']for c in rotation['chords']],['Min','Min']);self.assertEqual([c['bass']for c in rotation['chords']],[0,6])
  self.assertTrue({3,12,14,16,20,24,32}<={t['period_bars']for t in new})
  for t in new:self.assertEqual(sum(c['bars']for c in t['chords']),t['period_bars']);self.assertEqual(t['coloration'],'protected')
  for t in new:
   if t['id']in [61007,61008,61009,61010,61011,61012,61013,61014,61061]:
    self.assertTrue(all(v['notes']==t['voicings'][0]['notes']and v['held']==v['notes']for v in t['voicings']))
 def test_midi_csv_exact(self):
  with (F/'DS_Studien_Ereignisse.csv').open(encoding='utf-8-sig',newline='')as f:rows=list(csv.DictReader(f,delimiter=';'))
  groups=collections.defaultdict(list)
  for r in rows:groups[r['datei']].append(r)
  total=controllers=0;files=0
  with zipfile.ZipFile(F/'DS_Studien_MIDI.zip')as z:
   for name in z.namelist():
    if not name.lower().endswith('.mid'):continue
    files+=1;ns,cs=midi(z.read(name));source=groups.get(name,groups[Path(name).name])
    expected=sorted((int(r['tick_on']),int(r['tick_off']),int(r['kanal']),int(r['note']),int(r['velocity']))for r in source if r['typ']=='note')
    self.assertEqual(ns,expected,name)
    expected_cc=sorted((int(r['tick_on']),int(r['kanal']),int(r['note']),int(r['velocity']))for r in source if r['typ']=='cc')
    self.assertEqual(cs,expected_cc,name);total+=len(ns);controllers+=len(cs)
    self.assertTrue(all(p==36 for a,b,ch,p,v in ns if ch==7))
  self.assertEqual((files,total,controllers),(34,15035,1463))
if __name__=='__main__':unittest.main()
