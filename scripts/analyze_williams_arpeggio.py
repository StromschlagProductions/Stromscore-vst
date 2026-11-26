"""Read-only production renders: arpeggio presence is distinct from speed/density."""
from pathlib import Path
import subprocess,json,collections,hashlib,sys
root=Path(__file__).resolve().parents[1]
out=Path(sys.argv[1]);out.mkdir(parents=True,exist_ok=True)
subprocess.run(['c++','-std=c++17','-O1','-I',str(root/'Source'),str(root/'tools/williams_probe.cpp'),'-o',str(out/'probe')],check=True)
finger={p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in (root/'Source').glob('*') if p.is_file()}
Q=28800;BAR=4*Q;END=128*BAR

def union(xs):
 r=[]
 for a,b in sorted(xs):
  if r and a<=r[-1][1]:r[-1]=(r[-1][0],max(b,r[-1][1]))
  else:r.append((a,b))
 return r

def metrics(raw):
 active={};notes=[[] for _ in range(9)];ons=[[] for _ in range(9)]
 for line in raw.decode().splitlines():
  t,o,ch,p,v,k=map(int,line.split(','))
  if k:continue
  key=ch,p
  if v:
   assert key not in active
   active[key]=(t,o,p);ons[o].append((t,p))
  else:
   a,owner,p=active.pop(key);notes[owner].append((a,min(t,END)))
 assert not active
 gates=[union(n) for n in notes];arp=gates[4];duration=sum(b-a for a,b in arp)
 gaps=[];prev=0
 for a,b in arp:
  if a>prev:gaps.append((prev,a))
  prev=b
 if prev<END:gaps.append((prev,END))
 runs=[]
 for a,b in arp:
  if runs and a-runs[-1][1]<Q:runs[-1]=(runs[-1][0],b)
  else:runs.append((a,b))
 masks=[];activebars=[];padbars=[];bassbars=[];moving=[]
 for bar in range(128):
  a,b=bar*BAR,(bar+1)*BAR
  activebars.append(any(x<b and y>a for x,y in arp))
  padbars.append(any(a<=t<b for t,p in ons[1]))
  bass=[p for o in (2,3) for t,p in ons[o] if a<=t<b];bassbars.append(len(bass)>1);moving.append(len(set(bass))>1)
  masks.append(sum(1<<i for i in {round((t-a)/(Q/4)) for t,p in ons[4] if a<=t<b}))
 count=collections.Counter(masks);pairs=sum(a and b for a,b in zip(activebars,padbars))
 def overlap(other):
  return round(sum(max(0,min(b,d)-max(a,c)) for a,b in arp for c,d in gates[other])/END*100,3)
 intervals=collections.Counter(round((b[0]-a[0])/Q,4) for a,b in zip(ons[4],ons[4][1:]))
 return dict(note_ons=len(ons[4]),active_bars=sum(activebars),gate_percent=round(duration/END*100,3),longest_exact_gate_bars=round(max([b-a for a,b in arp]or[0])/BAR,3),longest_activity_run_bars=round(max([b-a for a,b in runs]or[0])/BAR,3),run_break_min_quarters=1,pauses_at_least_quarter=[{'start_bar':round(a/BAR,3),'bars':round((b-a)/BAR,3)} for a,b in gaps if b-a>=Q],silent_whole_bars=128-sum(activebars),short_pad_bars=sum(padbars),arp_and_short_pad_bars=pairs,bass_multiple_onset_bars=sum(bassbars),arp_and_bass_multiple_onset_bars=sum(a and b for a,b in zip(activebars,bassbars)),bass_distinct_pitch_bars=sum(moving),arp_and_bass_distinct_pitch_bars=sum(a and b for a,b in zip(activebars,moving)),melody_ons=len(ons[8]),dialog_ons=len(ons[7]),melody_overlap_percent=overlap(8),dialog_overlap_percent=overlap(7),onset_interval_quarters=dict(intervals.most_common(6)),rhythm_masks=[{'mask':hex(m),'bars':n}for m,n in count.most_common()],longest_same_mask_bars=max((len(list(g)) for k,g in __import__('itertools').groupby(masks)),default=0))
rows=[]
for profile in (0,1,3):
 for path in range(13):
  for mode in range(4):
   args=[profile,path,mode,512,128,0,3]
   raw=subprocess.check_output([str(out/'probe'),*map(str,args)],stderr=subprocess.DEVNULL)
   row=dict(profile=profile,path=path,mode=mode,variation=3,**metrics(raw));rows.append(row)
   if path in (0,1,3,5,7,11,12) and mode in (0,3):(out/f'p{profile}-x{path}-m{mode}.csv').write_bytes(raw)
for profile in (0,1,3):
 for variation in (1,7):
  for path in (3,7):
   raw=subprocess.check_output([str(out/'probe'),*map(str,[profile,path,3,512,128,0,variation])],stderr=subprocess.DEVNULL)
   rows.append(dict(profile=profile,path=path,mode=3,variation=variation,**metrics(raw)))
assert finger=={p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in (root/'Source').glob('*') if p.is_file()}
result=dict(source_commit=subprocess.check_output(['git','rev-parse','HEAD'],cwd=root).decode().strip(),source_sha256=finger,bars=128,bpm=100,key='D',sample_rate=48000,quarter_samples=Q,settings='Score; Auto; Follow ON; build/drive/scene limit OFF; motifs ON; mode0 neither,1 melody,2 dialog,3 both; variation3 except explicit controls; probe XYZ paths',rows=rows)
(root/'docs/research/john-williams/P1_ARPEGGIO_MEASUREMENTS.json').write_text(json.dumps(result,indent=2)+'\n')
print('Completed',len(rows),'128-bar production renders; ledger and unchanged source fingerprints passed.')
