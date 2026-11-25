#!/usr/bin/env python3
from reference_headers import header_snapshot
import argparse,collections,hashlib,json,pathlib,struct,subprocess,tempfile,sys
p=argparse.ArgumentParser();p.add_argument('--probe',required=True);p.add_argument('--compiler',default='c++');p.add_argument('--output',required=True);a=p.parse_args();root=pathlib.Path(__file__).resolve().parents[1];out=pathlib.Path(a.output);out.mkdir(parents=True,exist_ok=True)
def run(exe,case,bpm,block=512,control=False):
 cmd=[str(exe),str(case),str(block),str(bpm)]+(['1','0'] if control else [])
 r=subprocess.run(cmd,capture_output=True,check=True);es=[tuple(map(int,l.split(b','))) for l in r.stdout.splitlines()];tr=collections.defaultdict(list,{k:[] for k in ['M','P','D']})
 for l in r.stderr.splitlines():tr[l[:1].decode()].append(list(map(int,l[2:].split(b','))))
 return r.stdout,es,tr

def write_midi(path,es,bpm):
 def vlq(n):
  v=[n&127];n>>=7
  while n:v.insert(0,(n&127)|128);n>>=7
  return bytes(v)
 track=bytearray(b'\x00\xff\x51\x03'+round(60000000/bpm).to_bytes(3,'big'));prev=0
 for at,ch,n,v,kind,o in es:
  tick=round(at*bpm/(48000*60)*960);track+=vlq(tick-prev)+bytes([(0xb0 if kind else 0x90 if v else 0x80)+ch-1,n,v]);prev=tick
 track+=b'\x00\xff\x2f\x00';path.write_bytes(b'MThd'+struct.pack('>IHHH',6,0,1,960)+b'MTrk'+struct.pack('>I',len(track))+track)
rows=[];examples=[];passing_count=0
with tempfile.TemporaryDirectory() as tmp:
 tmp=pathlib.Path(tmp)
 for name,data in header_snapshot(root,'1fa718f').items():(tmp/name).write_bytes(data)
 old=tmp/'before';subprocess.run([a.compiler,'-std=c++17','-O2','-DHOOK_DIAGNOSTICS=1','-I',str(tmp),str(root/'tools/hook_development_probe.cpp'),'-o',str(old)],check=True)
 # Reproduce the same historical pool/role fixture used by ModalProbe.
 sys.path.insert(0,str(root/'Tests'));from HarmonyImportFixtures import prepare
 corrected=tmp/'corrected';prepare(corrected,revision='b4a5184',historical=True)
 fixed=tmp/'step-a';subprocess.run([a.compiler,'-std=c++17','-O2','-DHOOK_DIAGNOSTICS=1','-DMODAL_DIAGNOSTICS=1','-DBASS_REGRESSION_CONTROL=1','-I',str(corrected),str(root/'tools/hook_development_probe.cpp'),'-o',str(fixed)],check=True)
 for case in range(8):
  for bpm in (90,120,173):
   br,b,bh=run(old,case,bpm);cr,c,ch=run(a.probe,case,bpm,control=True);ar,es,tr=run(a.probe,case,bpm)
   if case==6:
    fixed_control,_,_=run(fixed,case,bpm,control=True);fixed_active,_,_=run(fixed,case,bpm)
    assert cr==fixed_control and ar==fixed_active,('corrected dynamic regression',case,bpm)
   else:assert cr==br,('previous output changed',case,bpm)
   # Compare current identities strictly; historical storage used a different hash encoding.
   assert tr['M']==ch['M'],('source changed by passing strategy',case,bpm)
   assert [m[1:] for m in tr['M']]==[m[1:] for m in bh['M']],('source changed',case,bpm)
   assert [e for e in es if e[5]!=7]==[e for e in c if e[5]!=7],('unrelated output changed',case,bpm)
   for block in (127,8192):
    raw,ee,tt=run(a.probe,case,bpm,block);assert tt==tr and len(ee)==len(es) and all(x[1:]==y[1:] and abs(x[0]-y[0])<=(1 if bpm==173 else 0) for x,y in zip(ee,es)),('block drift',case,bpm,block)
   # Recurrence/sequence plan times, source identity and span remain exactly the same.
   assert [p[:6] for p in tr['P']]==[p[:6] for p in ch['P']],('recurrence changed',case,bpm)
   if case!=4:assert ar==cr,('ineligible context changed',case,bpm)
   count=0
   for plan,decoration,original in zip(tr['P'],tr['D'],ch['P']):
    begin,end,ordinal,kind,base,identity,n=plan[:7];index=decoration[1]
    if index<0:assert plan==original;continue
    count+=1;passing_count+=1
    notes=[plan[7+3*i:10+3*i] for i in range(n)];at,length,interval=notes[index];pitch=base+interval
    assert n==original[6]+1 and kind==0 and index>0 and index+1<n
    src,target=notes[index-1],notes[index+1]
    assert at+length==target[0] and 1<=abs(interval-src[2])<=2 and 1<=abs(target[2]-interval)<=2 and (interval-src[2])*(target[2]-interval)>0
    assert (begin+at)%4!=0 and (begin+src[0])//32==(begin+target[0])//32
    # This default eligible case is C-Ionian with C/F/Am7/G at two bars each.
    bar=((begin+at)//16)%8;root_note,chord=(0,{0,4,7}) if bar<2 else (5,{5,9,0}) if bar<4 else (9,{9,0,4,7}) if bar<6 else (7,{7,11,2})
    assert pitch%12 in {0,2,4,5,7,9,11} and pitch%12 not in chord and (base+target[2])%12 in chord
    assert (pitch-root_note)%12 not in (1,11)
    def onset(note):
     step=begin+note[0];delay=(.667 if step%4==2 else .333 if step%4 in (1,3) else 0)*(.3 if case%2 else 0)
     expected=(step+delay)*.25*48000*60/bpm
     matches=[e for e in es if e[5]==7 and e[4]==0 and e[3]>0 and e[2]==base+note[2] and abs(e[0]-expected)<=1.01];assert len(matches)==1;return matches[0]
    pn=onset(notes[index]);resolution=onset(target)
    release=next(e for e in es if e[5]==7 and e[4]==0 and not e[3] and e[2]==pn[2] and e[0]>pn[0]);assert abs(release[0]-resolution[0])<=1
    # Every old target remains, including onset, pitch, velocity and gate; only predecessor gate may shorten.
    old_notes=[original[7+3*i:10+3*i] for i in range(original[6])]
    retained=notes[:index]+notes[index+1:]
    for i,(new,old_note) in enumerate(zip(retained,old_notes)):
     assert new[0]==old_note[0] and new[2]==old_note[2] and (new[1]==old_note[1] or i==index-1 and new[1]<=old_note[1]);onset(new)
    if bpm==120:examples.append({'case':case,'begin_bar':begin/16,'source_pitch':base+src[2],'passing_pitch':pitch,'target_pitch':base+target[2],'passing_at':at,'length':length,'actual_passing':pn,'actual_resolution':resolution,'source_identity':identity})
   rows.append({'case':case,'bpm':bpm,'passing_tones':count,'returns':len(tr['P']),'before_sha256':hashlib.sha256(br).hexdigest(),'after_sha256':hashlib.sha256(ar).hexdigest()})
   if bpm==120:write_midi(out/f'case-{case}-without.mid',c,bpm);write_midi(out/f'case-{case}-with.mid',es,bpm)
assert passing_count>0
(out/'summary.json').write_text(json.dumps({'baseline':'1fa718f','dynamic_reference':'b4a5184','bars':128,'passing_tones':passing_count,'results':rows,'examples':examples},indent=2)+'\n');print('24 128-bar modal A/B cases, 48 block comparisons;',passing_count,'resolved passing tones')
