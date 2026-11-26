"""Williams-only phrasing A/B against ddad94b; run with an output directory."""
from pathlib import Path
import sys,subprocess,json,hashlib,collections,struct,zipfile
from reference_headers import header_snapshot
root=Path(__file__).resolve().parents[1];out=Path(sys.argv[1]);out.mkdir(exist_ok=True,parents=True)
finger={p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in (root/'Source').glob('*.h')}
# --prepared is for binaries just compiled by the same validation session.
if '--prepared' not in sys.argv:
 old=out/'baseline';old.mkdir(exist_ok=True)
 for n,b in header_snapshot(root,'ddad94b').items():(old/n).write_bytes(b)
 for label,headers in [('before',old),('after',root/'Source')]:subprocess.run(['c++','-std=c++17','-O1','-I',str(headers),str(root/'tools/williams_probe.cpp'),'-o',str(out/label)],check=True)
def render(label,args):return subprocess.check_output([str(out/label),*map(str,args)],stderr=subprocess.DEVNULL)
def events(raw):return [tuple(map(int,l.split(b','))) for l in raw.splitlines()]
def measures(raw):
 active={};gates=[];ons=[]
 for t,o,ch,p,v,k in events(raw):
  if k:continue
  key=ch,p
  if v:assert key not in active;active[key]=(t,o);ons.append((t,o))
  else:
   a,owner=active.pop(key)
   if owner==4:gates.append((a,t))
 assert not active
 runs=[];merged=[]
 for a,b in sorted(gates):
  if merged and a<=merged[-1][1]:merged[-1]=(merged[-1][0],max(b,merged[-1][1]))
  else:merged.append((a,b))
 for a,b in merged:
  if runs and a-runs[-1][1]<28800:runs[-1]=(runs[-1][0],b)
  else:runs.append((a,b))
 last=0;pauses=[]
 for a,b in merged:
  if a-last>=28800:pauses.append([round(last/115200,3),round((a-last)/115200,3)])
  last=b
 if 128*115200-last>=28800:pauses.append([round(last/115200,3),round((128*115200-last)/115200,3)])
 return dict(ons=sum(o==4 for t,o in ons),gate_percent=round(sum(b-a for a,b in merged)/(128*115200)*100,3),longest_run_bars=round(max([b-a for a,b in runs]or[0])/115200,3),active_bars=len({bar for a,b in merged for bar in range(a//115200,(b-1)//115200+1)}),pauses=pauses)
def vlq(n):
 b=[n&127];n>>=7
 while n:b.insert(0,(n&127)|128);n>>=7
 return bytes(b)
def smf(raw):
 tracks=[b'\0\xff\x51\x03\x09\x27\xc0\0\xff\x58\x04\x04\x02\x18\x08']
 for output in range(9):
  b=bytearray();prev=0
  for t,o,ch,n,v,k in events(raw):
   if o!=output:continue
   tick=round(t/30);b+=vlq(tick-prev)+bytes([(0xb0 if k else 0x90)+ch-1,n,v]);prev=tick
  tracks.append(bytes(b))
 return b'MThd'+struct.pack('>IHHH',6,1,10,960)+b''.join(b'MTrk'+struct.pack('>I',len(b)+4)+b+b'\0\xff\x2f\0' for b in tracks)
rows=[];dest=root/'docs/research/john-williams'
with zipfile.ZipFile(dest/'ARPEGGIO_PHRASING_AB.zip','w',zipfile.ZIP_DEFLATED) as z:
 for path in range(13):
  for mode in range(4):
   args=[3,path,mode,512,128,0,3];before=render('before',args);after=render('after',args)
   assert collections.Counter(e for e in events(before) if e[1]!=4)==collections.Counter(e for e in events(after) if e[1]!=4),('other role changed',args)
   # Retained attacks retain exact pitch, onset and velocity; only complete windows are withheld.
   assert not (collections.Counter(e for e in events(after) if e[1]==4 and e[4] and not e[5])-collections.Counter(e for e in events(before) if e[1]==4 and e[4] and not e[5]))
   rows.append(dict(path=path,mode=mode,before=measures(before),after=measures(after)))
   if path in (1,3,5,7,11,12) and mode in (0,3):
    for label,raw in [('before',before),('after',after)]:z.writestr(f'{label}-path{path}-mode{mode}.mid',smf(raw))
 for path in (3,12):
  args=[3,path,3,512,128,0,3];a=render('after',args);assert a==render('after',args);args[3]=127;assert a==render('after',args)
 # Manual figure OR manual rate has priority, including moving XYZ.
 for path in (3,7,12):
  for figure,rate in ((1,0),(0,2),(1,2)):
   args=[3,path,3,512,128,0,3,0,1,0,4,4,0,figure,rate]
   assert render('before',args)==render('after',args)
 z.writestr('README.txt','Actual Williams engine MIDI, ddad94b before / phrasing after. 128 bars, D, 100 BPM, 960 PPQ. path1 dark quiet unrest;3 dark action;5 bright quiet unrest;7 bright action;11 slow XYZ;12 fast XYZ. mode0 melody/dialog OFF;mode3 both ON. Same patches/routing required for A/B. All other-role events identical.')
for genre in (0,1):
 for profile in (0,1,2):
  for path in (3,11,12):
   args=[profile,path,3,512,128,genre,3]
   assert render('before',args)==render('after',args),('other profile changed',args)
assert finger=={p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in (root/'Source').glob('*.h')}
(dest/'ARPEGGIO_PHRASING_RESULTS.json').write_text(json.dumps(dict(reference='ddad94b',source_sha256=finger,rows=rows,manual_cases=9,repeat_block_cases=2,other_roles_unchanged=True,ddad_other_profile_cases=18),indent=2)+'\n')
print('52 A/B pairs: other roles and retained attacks identical; ledgers valid; 9 manual cases and repeated/block renders passed; 24 SMFs.')
