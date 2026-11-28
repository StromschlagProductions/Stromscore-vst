"""Reproducible normal production audit; binaries must use unmodified selection.
Build tools/williams_probe.cpp with LAYER_DIAGNOSTICS and ACTIVITY_DIAGNOSTICS; after additionally ACTIVITY_PLACEMENT.
Before uses0874b02 headers plus the existing test-only friend seam. No forced picks.
"""
from pathlib import Path
import sys,json,subprocess,collections,concurrent.futures,hashlib,zipfile,struct,ast,time,gzip
ROOT=Path(__file__).resolve().parents[1];OUT=Path(sys.argv[1]);DOC=ROOT/'docs/research/bernard-herrmann';HARMONIES={int(h['harmony']):h['source']for h in json.loads((ROOT/'data/herrmann/vocabulary.json').read_text())['harmonies']};BIN_SHA={name:hashlib.sha256((OUT/name).read_bytes()).hexdigest()for name in ['before','after']}
def args(x=.5,y=.7,z=.5,route=0,variety=.5,variation=3,seed=0,path=13,bars=64,mode=3,manual=0,follow=1,profile=2,genre=0,block=512,jump=0,key=2):
 return [profile,path,mode,block,bars,genre,variation,manual,follow,0,4,4,jump,0,0,key,seed,100,0,0,x,y,z,route,variety]
def execute(binary,a):
 cache=OUT/'activity-cache';cache.mkdir(exist_ok=True);key=hashlib.sha256((BIN_SHA[binary]+json.dumps(a)).encode()).hexdigest();path=cache/(key+'.gz')
 if path.exists():
  value=json.loads(gzip.decompress(path.read_bytes()));return value[0].encode(),value[1]
 r=subprocess.run([str(OUT/binary),*map(str,a)],capture_output=True,check=True);path.write_bytes(gzip.compress(json.dumps([r.stdout.decode(),r.stderr.decode()]).encode()));return r.stdout,r.stderr.decode()

def stats(raw,trace,bars):
 held={};notes=[];ons=collections.Counter();source=collections.Counter();motif=collections.Counter();matched=collections.Counter();examples=[];admit=collections.defaultdict(collections.Counter);h=[];episodes=collections.Counter();last_source={};channels=collections.Counter();peaks=collections.Counter()
 for line in raw.splitlines():
  at,o,ch,n,v,k=map(int,line.split(b','))
  if k:continue
  if v:assert(ch,n)not in held;held[ch,n]=(at,o,v);ons[o]+=1;channels[ch]+=1;peaks[ch]=max(peaks[ch],channels[ch])
  else:
   assert(ch,n)in held,(at,o,ch,n);begin,owner,velocity=held.pop((ch,n));channels[ch]-=1;assert at>begin;notes.append((begin,at,owner,n,velocity))
 assert not held
 end=bars*4*28800;activity={}
 for o in range(9):
  ns=sorted((a,b)for a,b,owner,n,v in notes if owner==o);segments=[];activebars=set()
  for a,b in ns:
   activebars.update(range(a//115200,min(bars-1,(b-1)//115200)+1))
   if segments and a<=segments[-1][1]:segments[-1][1]=max(b,segments[-1][1])
   else:segments.append([a,b])
  last=0;longest=0
  for a,b in segments:longest=max(longest,a-last);last=b
  longest=max(longest,end-last);activity[o]=dict(note_ons=ons[o],active_bars=len(activebars),gate_fraction=sum(b-a for a,b in segments)/end,longest_silence_bars=longest/115200,first_notes=[n for n in notes if n[2]==o][:6])
 for line in trace.splitlines():
  f=line.split(',')
  if f[0]=='L':source[f[3]]+=1
  if f[0]=='P' and 82000<int(f[3])<82100:motif['HE-M%02d'%(int(f[3])%100)]+=1
  if f[0]=='P':
   voice=int(f[2]);id=int(f[3]);
   if id and id!=last_source.get(voice):episodes['HE-M%02d'%(id%100)]+=1
   last_source[voice]=id
  if f[0]=='A':
   matched['HE-M%02d'%(int(f[3])%100)]+=1
   if len(examples)<12:examples.append(dict(sample=int(f[1]),output=int(f[2]),source=f[3],identity=f[4],pitch=int(f[5])))
  if f[0]=='D':admit[f[3]][f[4]]+=1
  if f[0]=='H':h.append([int(f[1]),int(f[2])])
 harmony_ons=collections.defaultdict(collections.Counter)
 for begin,until,owner,pitch,velocity in notes:
  harmony_source=None
  for time,id in h:
   if time>begin:break
   harmony_source=HARMONIES.get(id)
  if harmony_source:harmony_ons[harmony_source][owner]+=1
 return dict(roles=activity,peak_physical_notes_by_channel=dict(peaks),source_note_ons=dict(source),motif_trace_events=dict(motif),motif_selection_episodes=dict(episodes),harmony_context_note_ons={k:dict(v)for k,v in harmony_ons.items()},matched_motif_note_ons=dict(matched),matched_examples=examples,admission_snapshots={k:dict(v)for k,v in admit.items()},harmonies=h,sha256=hashlib.sha256(raw).hexdigest())
cases=[]
for x in [.15,.5,.85]:
 for y in [.2,.55,.9]:
  for z in [.1,.5,.9]:
   for variety in [0,.5,1]:
    for variant,(variation,seed)in enumerate([(1,0),(9,37)]):cases.append((f'grid-{x}-{y}-{z}-{variety}-{variant}',args(x,y,z,variety=variety,variation=variation,seed=seed,mode=3 if variant else 0)))
for path in [11,12]:
 for mode in [0,1,2,3]:cases.append((f'path-{path}-roles-{mode}',args(path=path,mode=mode,bars=128)))
for route in [0,1,2,3,4,5,6]:
 for mode in [0,3]:cases.append((f'routing-{route}-roles-{mode}',args(route=route,mode=mode,bars=128)))
for manual,follow in [(1,1),(0,0),(1,0)]:cases.append((f'manual-{manual}-follow-{follow}',args(manual=manual,follow=follow,bars=128)))
# Eight corners also have128-bar static counterparts, independent of the grid64.
for x in [.15,.85]:
 for y in [.2,.9]:
  for z in [.1,.9]:cases.append((f'long-{x}-{y}-{z}',args(x,y,z,bars=128)))
for x in [0,1]:
 for y in [.05,1]:
  for z in [0,1]:cases.append((f'edge-{x}-{y}-{z}',args(x,y,z,bars=128,variation=16,seed=13)))
# The exact user register across the field, not just an isolated central example.
for x in [.15,.5,.85]:
 for y in [.2,.55,.9]:
  for z in [.1,.5,.9]:
   for variant,(variation,seed)in enumerate([(1,0),(9,37)]):cases.append((f'user-register-{x}-{y}-{z}-{variant}',args(x,y,z,route=5,variation=variation,seed=seed,mode=3 if variant else 0)))
for path in [11,12]:cases.append((f'user-register-path-{path}',args(route=5,path=path,bars=128)))
def one(item):
 name,a=item;record=dict(name=name,args=a,before={},after={});renders={}
 for binary in ['before','after']:
  raw,trace=execute(binary,a);record[binary]=stats(raw,trace,a[4]);
  if a[23] in [1,2,6]:assert record[binary]['peak_physical_notes_by_channel'].get(3,0)<=1,(name,binary,'shared bass polyphony')
  if name in ['routing-0-roles-3','routing-1-roles-3','routing-2-roles-3','routing-5-roles-3','path-11-roles-3','long-0.15-0.9-0.9','long-0.85-0.2-0.1']:renders[name+'-'+binary]=raw
 return record,renders
records=[];renders={};start=time.monotonic()
with concurrent.futures.ThreadPoolExecutor(max_workers=2)as ex:
 for index,(r,m)in enumerate(ex.map(one,cases)):
  records.append(r);renders.update(m)
  if index%20==0:print('Activity cases',index+1,'/',len(cases),flush=True)
# One track per physical MIDI channel, including explicitly shared destinations.
def vlq(n):
 b=[n&127];n>>=7
 while n:b.insert(0,(n&127)|128);n>>=7
 return bytes(b)
def midi(raw):
 events=collections.defaultdict(list);outputs=collections.defaultdict(set);tracks=[]
 meta=b'\0\xff\x51\x03'+(600000).to_bytes(3,'big')+b'\0\xff\x58\x04\x04\x02\x18\x08\0\xff\x2f\0';tracks.append(b'MTrk'+struct.pack('>I',len(meta))+meta)
 for line in raw.splitlines():
  at,o,ch,n,v,kind=map(int,line.split(b','));events[ch].append((round(at/30),bytes([(0xb0 if kind else 0x90 if v else 0x80)|(ch-1),n,v])));outputs[ch].add(o)
 for ch,ev in sorted(events.items()):
  label=('Ch'+str(ch)+' '+ '/'.join(['LF','KF','LB','KB','AR','TU','ST','GS','HM'][o]for o in sorted(outputs[ch]))).encode();data=b'\0\xff\x03'+bytes([len(label)])+label;last=0
  for tick,message in ev:data+=vlq(tick-last)+message;last=tick
  data+=vlq(max(0,128*3840-last))+b'\xff\x2f\0';tracks.append(b'MTrk'+struct.pack('>I',len(data))+data)
 return b'MThd'+struct.pack('>IHHH',6,1,len(tracks),960)+b''.join(tracks)
with zipfile.ZipFile(DOC/'P1_ACTIVITY_AB_MIDI.zip','w',zipfile.ZIP_DEFLATED)as z:
 for name,raw in renders.items():z.writestr(name+'.mid',midi(raw))
 z.writestr('LESEN.txt','Normale Engine-Produktion, kein erzwungener Katalogeintrag.128 Takte,D,100BPM,4/4. before=0874b02. after=Korrektur. Routing1 teiltLB/KB; Routing2 zusaetzlichLF/KF. Bei gemeinsamem Kanal zeigt die physische MIDI-Spur beide Ansprueche. Keine Filmmusiktranskription.\n')
result=dict(executable_sha256=BIN_SHA,base='0874b02',cases=records,elapsed_seconds=time.monotonic()-start,source_sha256={p.name:hashlib.sha256(p.read_bytes()).hexdigest()for p in(ROOT/'Source').glob('*.h')},note='D=16-Takt-Schnappschuss der Zulassung; keine kumulierte Echtzeit-Aufrufzahl. M-Provenienzereignisse sind keine neue Motiveinführung pro Note. Bei geteiltem Kanal zählt die physische Attacke zum tatsächlich ausgebenden Anspruch, nicht zu beiden Rollen.')
(DOC/'P1_ACTIVITY_RESULTS.json').write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n',encoding='utf-8');print('Completed',len(records),'normal production A/B cases',flush=True)

# One row per unique integrated source (not per duplicate role consumer).
import csv
vocabulary=json.loads((ROOT/'data/herrmann/vocabulary.json').read_text())
registered={entry['source']:kind for kind,key in [('harmonic','harmonies'),('rhythmic','figures'),('motivic','motifs')]for entry in vocabulary[key]}
with (DOC/'P1_ACTIVITY_SOURCE_USE.csv').open('w',newline='',encoding='utf-8')as file:
 writer=csv.writer(file,lineterminator="\n");writer.writerow(['source','kind','registered','definition_validation','before_eligible_snapshots','after_eligible_snapshots','before_actual_note_ons','after_actual_note_ons','after_cases_with_actual_notes','after_selection_episodes','evidence_scope','after_admission_reasons'])
 for source,kind in sorted(registered.items()):
  totals={};reasons=collections.Counter();episodes=0
  for phase in ['before','after']:
   eligible=notes=heard=0
   for case in records:
    data=case[phase];admission=data['admission_snapshots'].get(source,{});eligible+=sum(admission.get(k,0)for k in ['eligible','selected'])
    count=(sum(data['harmony_context_note_ons'].get(source,{}).values())if kind=='harmonic'else data['matched_motif_note_ons'].get(source,0)if kind=='motivic'else data['source_note_ons'].get(source,0))
    notes+=count;heard+=bool(count)
    if phase=='after':reasons.update(admission);episodes+=data['motif_selection_episodes'].get(source,0)
   totals[phase]=(eligible,notes,heard)
  scope=('note-ons while primary harmonic context active; not a complete model study'if kind=='harmonic'else 'emitted pitch/onset matched to active motif plan; conservative provenance'if kind=='motivic'else 'emitted layer-source attacks, all registered role consumers combined')
  writer.writerow([source,kind,True,'validated source and common consumer; not a guarantee of isolated audible use',totals['before'][0]if kind!='harmonic'else '',totals['after'][0]if kind!='harmonic'else '',totals['before'][1],totals['after'][1],totals['after'][2],episodes if kind=='motivic'else '',scope,json.dumps(reasons,sort_keys=True)])
