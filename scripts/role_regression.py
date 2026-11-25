"""Narrow musical delta for Score dialogue released by real foreground windows.

No melody/accompaniment/CC changes; previous dialogue attacks must survive.
The caller must explicitly opt in only for Score with the melody enabled.
"""
from collections import Counter
from transport_regression import assert_chase_delta

def canonical(data,layout='legacy'):
 if isinstance(data,bytes):data=[tuple(map(int,line.split(b','))) for line in data.splitlines()]
 if layout=='legacy':return [(s,o,c,n,v,k) for s,c,n,v,k,o in data]
 assert layout=='import';return list(data)

def assert_score_role_delta(before,after,cuts=(),*,layout='legacy',samples_per_quarter=24000):
 old,new=canonical(before,layout),canonical(after,layout)
 def protected(events):return [e for e in events if not(e[1]==7 and e[5]==0)]
 a,b=protected(old),protected(new)
 if cuts:assert_chase_delta(sorted(a),sorted(b),cuts,layout='import',samples_per_quarter=samples_per_quarter)
 else:assert Counter(a)==Counter(b),('protected melody/accompaniment/CC changed',list((Counter(a)-Counter(b)).elements())[:6],list((Counter(b)-Counter(a)).elements())[:6])
 attacks=lambda es:Counter(e for e in es if e[1]==7 and e[4]>0 and e[5]==0)
 assert not attacks(old)-attacks(new),('previous dialogue attack removed',list((attacks(old)-attacks(new)).elements())[:6])
 # Physical ownership, including shared-channel off events, is evaluated independently
 # of the output number attached to the final release.
 active={};roles=Counter();last=0
 for sample,output,channel,note,velocity,kind in new:
  assert not(roles[7] and roles[8] and sample>last),('competing melodic notes',last,sample)
  last=sample
  if kind:continue
  key=channel,note
  if velocity:
   assert key not in active,('duplicate note-on',sample,key)
   active[key]=output;roles[output]+=1
  else:
   assert key in active,('orphan note-off',sample,key)
   roles[active.pop(key)]-=1
 assert not active,('hanging notes',active)
 return {'added_dialogue_attacks':sum((attacks(new)-attacks(old)).values()),'protected_events':len(b)}
