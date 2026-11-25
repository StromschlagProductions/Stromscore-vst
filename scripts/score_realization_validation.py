"""Verify provenance, recognisable intervals/rhythm and actual MIDI realization."""
from collections import defaultdict

def validate_examples(path,result):
 rows=[tuple(map(int,l.split(','))) for l in path.read_text().splitlines()[1:]]
 attacks=defaultdict(list);ons=set();pending={};gates={}
 for sample,out,ch,note,vel,kind in rows:
  if kind:continue
  key=ch,note
  if vel:pending[key]=(sample,out,note);ons.add((sample,out,note));attacks[out].append((sample,note))
  else:
   start= pending.pop(key);gates[start]=sample-start[0]
 verified=performed=blocked=0
 for role in result['roles']:
  output=8 if role['role']=='melody' else 7
  for e in role['examples']:
   if not e['flexible']:continue
   source=e['source'];figure=e['figure'];assert e['source_identity']==e['figure_identity']
   h=1469598103934665603;mask=(1<<64)-1
   for pitch,at,length in source:
    for value in (at,length,pitch-source[0][0]):h=((h^(value&mask))*1099511628211)&mask
   h=(h*1099511628211)&mask;assert str(h)==e['source_identity']
   introduced=any(all((begin-at0*25+at*25,output,pitch) in ons for pitch,at,length in source)
                  for begin,pitch0 in attacks[output] for at0 in [source[0][1]] if pitch0==source[0][0])
   assert introduced,'material not found in performed introduction'
   suffix=e['variation']==2;selected=source[-len(figure):] if suffix else source
   assert len(selected)==len(figure)
   for i,((pitch,at,length),(old,oldAt,oldLength)) in enumerate(zip(figure,selected)):
    assert at==oldAt-(selected[0][1] if suffix else 0),'onset rhythm changed'
    assert 0<length<=oldLength and length*2>=oldLength,'excessive gate change'
    if i:
     oldStep=old-selected[i-1][0];step=pitch-figure[i-1][0]
     assert (oldStep>0)-(oldStep<0)==(step>0)-(step<0) and abs(step-oldStep)<=2
   anchor=max(range(1,len(selected)),key=lambda i:abs(selected[i][0]-selected[i-1][0]))
   assert figure[anchor][0]-figure[anchor-1][0]==selected[anchor][0]-selected[anchor-1][0]
   played=0
   for pitch,at,length in figure:
    key=(25*(e['begin_tick']+at),output,pitch)
    if key in ons:
     played+=1;assert gates[key]<=25*length,'actual gate exceeds harmonic preflight'
   e['performed_notes']=played;e['introduced_material_verified']=True
   verified+=1;performed+=played;blocked+=played==0
 return dict(verified_flexible_examples=verified,performed_example_notes=performed,unperformed_examples=blocked)
