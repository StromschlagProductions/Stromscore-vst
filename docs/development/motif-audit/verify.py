import argparse,hashlib,json,pathlib,struct,zipfile
parser=argparse.ArgumentParser();parser.add_argument('--repo',type=pathlib.Path,required=True);parser.add_argument('--output',type=pathlib.Path,required=True);args=parser.parse_args();root=args.repo.resolve();out=args.output.resolve()
d=json.loads((out/'enriched.json').read_text())
assert all(hashlib.sha256((root/'Source'/name).read_bytes()).hexdigest()==h for name,h in d['source_headers_sha256'].items())
for c in d['results']:
 name=c['config']['name'];assert (out/(name+'.csv')).read_bytes()==(out/(name+'-reference.csv')).read_bytes()
def decode(raw):
 assert raw[:4]==b'MThd';size,fmt,nt,ppq=struct.unpack('>IHHH',raw[4:14]);assert (size,fmt,nt,ppq)==(6,1,10,960)
 pos=14;events=[]
 for tr in range(nt):
  assert raw[pos:pos+4]==b'MTrk';n=int.from_bytes(raw[pos+4:pos+8],'big');p=pos+8;end=p+n;tick=0
  def vlq():
   nonlocal p
   value=0
   while True:
    b=raw[p];p+=1;value=(value<<7)|(b&127)
    if b<128:return value
  while p<end:
   tick+=vlq();status=raw[p];p+=1
   if status==255:
    meta=raw[p];p+=1;length=vlq();p+=length
   else:
    assert status>>4 in (9,11);note,vel=raw[p:p+2];p+=2
    events.append((tick,tr-1,(status&15)+1,note,vel,0 if status>>4==9 else 1))
  assert p==end;pos=end
 assert pos==len(raw);return events
z=zipfile.ZipFile(root/'docs/development/MOTIF_MUSICAL_AUDIT_MIDI.zip');assert z.testzip() is None
examples=json.loads(z.read('STROMSCORE_Motiv_Hoertest/Beispiele.json'))
for c in examples:
 source=[tuple(map(int,l.split(','))) for l in (out/(c['config']['name']+'.csv')).read_text().splitlines()]
 for voices,suffix in [(False,'gesamt'),(True,'melodische_Stimmen')]:
  raw=z.read(f'STROMSCORE_Motiv_Hoertest/{c["file"]}_{suffix}.mid');actual=decode(raw)
  expected=[(round(s/30),o,ch,p,v,k) for s,o,ch,p,v,k in source if not voices or o in (7,8)]
  assert sorted(actual)==sorted(expected),c['file']
print('Verified: source SHA-256 unchanged; 126 paired streams byte-identical; 16 MIDI files decoded and every event matched; ZIP CRC valid.')
