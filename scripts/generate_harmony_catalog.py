#!/usr/bin/env python3
"""Validate editable harmony sources offline; emit immutable C++17 catalog views."""
import argparse, collections, hashlib, json, math, pathlib, re, struct, sys
ROOT=pathlib.Path(__file__).resolve().parents[1]
FILES=('chord_types.json','catalog.json','arrangements.json','profiles.json','notes.json')
ENGINE_TYPES='Maj Min Maj7 Min7 Dom7 MinMaj7 MinMaj9 Dim7 HalfDim Sus4 Quartal Add9 Min9 Aug Min6 Dom7b9 Sus2 Fifth'.split()
ARP='ArpAuto ArpUp ArpDown ArpCircle ArpCell ArpRiff ArpGlitter ArpLeaps ArpCascade ArpOctatonic ArpQuartal ArpSid'.split()
BASS='BassAuto BassHeld BassHalf BassQuarter BassEighth BassPulse BassFunk BassPendulum BassWalking BassAlternating BassHeartbeat BassArpeggio BassPedal BassHiNrg BassGallop'.split()
PAD='PadAuto PadHeld PadStabs PadPulse PadStaccato PadGated'.split()
ENGINE_VOCABULARY_SIGNATURE='b9358ee8884a096c609ef792ca9ad2cc065650a3ec805c2aa6c13dcf38c67c68' # existing engine contract, not a second chord dictionary
MODES={'automatic':None,'ionian':{0,2,4,5,7,9,11},'mixolydian':{0,2,4,5,7,9,10},'dorian':{0,2,3,5,7,9,10},'aeolian':{0,2,3,5,7,8,10}}
KEYWORDS=set('alignas alignof and asm auto bool break case catch char char16_t char32_t class const const_cast constexpr continue decltype default delete do double dynamic_cast else enum explicit export extern false float for friend goto if inline int long mutable namespace new noexcept not nullptr operator or private protected public register reinterpret_cast return short signed sizeof static static_assert static_cast struct switch template this thread_local throw true try typedef typeid typename union unsigned using virtual void volatile wchar_t while xor xor_eq and_eq bitand bitor compl not_eq or_eq template'.split())
class ValidationError(ValueError):pass
def require(ok,path,message):
 if not ok:raise ValidationError(path+': '+message)
def obj(v,keys,path):require(type(v)is dict,path,'object required');require(set(v)==set(keys),path,'missing/unknown fields: '+str(set(v)^set(keys)))
def integer(v,lo,hi,path):require(type(v)is int and lo<=v<=hi,path,f'integer {lo}..{hi} required')
def text(v,path,empty=False):require(type(v)is str and (empty or bool(v.strip())) and '\0' not in v,path,'nonempty text without NUL required')
def identifier(v,path):text(v,path);require(bool(re.fullmatch('[A-Za-z_][A-Za-z0-9_]*',v)) and v not in KEYWORDS and not v.startswith('__') and not re.match('_[A-Z]',v),path,'nonreserved C++ identifier required')
def sequence(v,path):require(type(v)is list,path,'array required')
def number(v,path):require(type(v)in(int,float) and math.isfinite(v),path,'finite number required')
def load(directory):
 def pairs(xs):
  result={}
  for k,v in xs:require(k not in result,k,'duplicate JSON key');result[k]=v
  return result
 result={}
 for f in FILES:
  try:result[f]=json.loads((directory/f).read_text(encoding='utf-8'),object_pairs_hook=pairs)
  except (OSError,json.JSONDecodeError) as e:raise ValidationError(f+': '+str(e)) from e
 return result

def _validate(data):
 for f in FILES:require(f in data,f,'source missing');require(type(data[f].get('schema_version'))is int and data[f].get('schema_version')==1,f,'schema_version 1 required')
 shapes=data['chord_types.json'];obj(shapes,['schema_version','types','custom_choice_order'],'chord_types')
 sequence(shapes['types'],'types');require(len(shapes['types'])==len(ENGINE_TYPES),'types','this stage supports exactly the existing 18 engine types')
 definitions={}
 for i,t in enumerate(shapes['types']):
  p=f'types[{i}]';obj(t,['id','value','suffix','minor','intervals'],p);require(t['id']==ENGINE_TYPES[i] and type(t['value'])is int and t['value']==i,p,'unsupported/reordered chord type')
  text(t['suffix'],p+'.suffix',True);require(type(t['minor'])is bool,p,'minor must be boolean');ns=t['intervals'];sequence(ns,p);require(2<=len(ns)<=5,p,'2..5 intervals supported')
  for n in ns:integer(n,0,23,p+'.interval')
  require(ns[0]==0 and ns==sorted(set(ns)),p,'root 0 and strictly increasing intervals required');definitions[t['id']]=t
 require(hashlib.sha256(json.dumps([{k:t[k] for k in ['id','value','intervals','minor']} for t in shapes['types']],sort_keys=True).encode()).hexdigest()==ENGINE_VOCABULARY_SIGNATURE,'types','unsupported musical redefinition of existing engine chord vocabulary')
 require(shapes['custom_choice_order']==list(dict.fromkeys(shapes['custom_choice_order'])) and set(shapes['custom_choice_order'])==set(ENGINE_TYPES),'custom_choice_order','each existing type exactly once')
 cat=data['catalog.json'];obj(cat,['schema_version','sources','templates','pools'],'catalog');sources={}
 for i,s in enumerate(cat['sources']):
  p=f'sources[{i}]';obj(s,['id','text','verification'],p);text(s['id'],p);text(s['text'],p);text(s['verification'],p);require(s['id'] not in sources,p,'duplicate source');sources[s['id']]=s
 templates={};symbols=set();require(type(cat['templates'])is list and len(cat['templates'])>0,'templates','nonempty array required')
 for i,t in enumerate(cat['templates']):
  p=f'templates[{i}]';obj(t,['id','symbol','name','xyz','genres','tonality','source_ref','chords','coloration'],p)
  require(t['coloration'] in ('flexible','protected'),p+'.coloration','flexible or protected required')
  integer(t['id'],1,0xffffffff,p+'.id');require(t['id']!=65535,p,'reserved custom ID');require(t['id'] not in templates,p,'duplicate stable ID');identifier(t['symbol'],p+'.symbol');require(t['symbol'] not in symbols and t['symbol'] not in ('custom','invalid'),p,'duplicate/reserved symbol');symbols.add(t['symbol']);text(t['name'],p+'.name')
  sequence(t['xyz'],p+'.xyz');require(len(t['xyz'])==3,p,'three static coordinates required')
  for v in t['xyz']:number(v,p+'.xyz');require(0<=v<=1,p,'XYZ outside unit cube')
  require(type(t['genres'])is list and bool(t['genres']) and len(set(t['genres']))==len(t['genres']) and set(t['genres'])<=set(['score','pop_rock']),p,'invalid genre suitability')
  obj(t['tonality'],['center_pc','mode'],p+'.tonality');integer(t['tonality']['center_pc'],0,11,p+'.center');require(t['tonality']['mode'] in MODES,p,'unsupported mode')
  require(t['source_ref'] in sources,p,'unknown source reference');sequence(t['chords'],p+'.chords');require(1<=len(t['chords'])<=8,p,'current renderer supports 1..8 slots')
  duration=0;vocabulary=set()
  for j,c in enumerate(t['chords']):
   q=f'{p}.chords[{j}]';obj(c,['root','type','bars','bass'],q);integer(c['root'],0,11,q+'.root');require(c['type'] in definitions,q,'unknown chord type; no aliases/substitution');integer(c['bars'],1,8,q+'.bars');duration+=c['bars']
   if c['bass'] is not None:integer(c['bass'],0,11,q+'.bass')
   vocabulary|={(c['root']+n)%12 for n in definitions[c['type']]['intervals']};vocabulary.add(c['root'] if c['bass'] is None else c['bass'])
  require(duration==8,p,'total duration must be exactly eight integer bars')
  mode=MODES[t['tonality']['mode']]
  if mode is not None:require(vocabulary<={(n+t['tonality']['center_pc'])%12 for n in mode},p,'declared mode incompatible with complete chord/bass vocabulary')
  templates[t['id']]=t
 obj(cat['pools'],['score','pop_rock'],'pools')
 for genre,ids in cat['pools'].items():
  sequence(ids,'pool '+genre);require(len(ids)>0 and len(ids)<0x7ffffffd,'pool '+genre,'nonempty, representable runtime index count required');require(len(set(ids))==len(ids),'pool '+genre,'duplicate pool reference')
  for i in ids:require(type(i)is int and i in templates and genre in templates[i]['genres'],'pool '+genre,'invalid/ineligible template reference')
 for t in templates.values():require(all(t['id'] in cat['pools'][g] for g in t['genres']),t['symbol'],'genre suitability and published pools disagree')
 arr=data['arrangements.json'];obj(arr,['schema_version','recipes','bindings'],'arrangements');recipes={}
 for r in arr['recipes']:
  obj(r,['id','arp','bass','pad','hook'],'recipe');text(r['id'],'recipe.id');require(r['id'] not in recipes,'recipe','duplicate recipe')
  require(type(r['arp'])is list and len(r['arp'])==2 and all(v in ARP[1:] for v in r['arp']),'recipe','two concrete existing arp choices required')
  require(type(r['bass'])is list and len(r['bass'])==2 and all(v in BASS[1:] for v in r['bass']),'recipe','two concrete existing bass choices required');require(r['pad'] in PAD[1:],'recipe','concrete pad pattern required')
  if r['hook'] is not None:integer(r['hook'],0,8,'recipe.hook')
  recipes[r['id']]=r
 bindings={}
 for r in arr['bindings']:
  obj(r,['template_id','recipe'],'binding');require(type(r['template_id'])is int and r['template_id'] in templates,'binding','unknown template');require(r['template_id'] not in bindings,'binding','duplicate default binding');require(r['recipe'] in recipes,'binding','unknown recipe');bindings[r['template_id']]=r['recipe']
 require(set(bindings)==set(templates),'bindings','each template needs one independent default strategy')
 profiles=data['profiles.json'];obj(profiles,['schema_version','profiles'],'profiles');pids=set();pnames=set();prefs={}
 require(type(profiles['profiles'])is list and len(profiles['profiles'])>0,'profiles','nonempty registry required')
 for p in profiles['profiles']:
  obj(p,['id','symbol','name','harmony_selection_only','weights'],'profile');integer(p['id'],0,0x7fffffff,'profile.id');identifier(p['symbol'],'profile.symbol');text(p['name'],'profile.name');require(p['id'] not in pids and p['symbol'] not in pnames,'profile','duplicate profile identity');pids.add(p['id']);pnames.add(p['symbol']);require(type(p['harmony_selection_only'])is bool,'profile','boolean required');sequence(p['weights'],'profile.weights');weights={}
  for w in p['weights']:
   obj(w,['template_id','factor'],'weight');require(type(w['template_id'])is int and w['template_id'] in templates,'weight','unknown template reference');require(w['template_id'] not in weights,'weight','duplicate template/profile weight');number(w['factor'],'weight.factor');require(w['factor']>0,'weight.factor','positive weights only; no exclusion lists')
   try:f32=struct.unpack('<f',struct.pack('<f',w['factor']))[0]
   except OverflowError:raise ValidationError('weight.factor: not representable as float32')
   require(math.isfinite(f32) and f32>0,'weight.factor','finite positive float32 required');weights[w['template_id']]=w['factor']
  # Derived numeric safety, not a fixed artistic weight cap.
  require(sum(max(1.,weights.get(i,1.)) for i in templates)<3.4028234663852886e38/4,'profile.weights','unsafe floating-point accumulator total');prefs[p['symbol']]=weights
 require(pids==set(range(len(pids))) and profiles['profiles'][0]['id']==0 and profiles['profiles'][0]['symbol']=='neutral','profiles','contiguous stable runtime indices with neutral=0 required')
 notes=data['notes.json'];obj(notes,['schema_version','entries'],'notes');noteMap={}
 for n in notes['entries']:
  obj(n,['template_id','idea','instruments'],'notes.entry');require(type(n['template_id'])is int and n['template_id'] in templates and n['template_id'] not in noteMap,'notes','unknown/duplicate reference');text(n['idea'],'notes.idea');text(n['instruments'],'notes.instruments');noteMap[n['template_id']]=n
 require(set(noteMap)==set(templates),'notes','each existing template needs display notes')
 # Harmonic duplicate warnings preserve IDs and strategy differences. No automatic merge.
 groups=collections.defaultdict(list)
 for t in templates.values():
  frames=[]
  for c in t['chords']:
   frame=(c['root'],tuple(sorted({(c['root']+n)%12 for n in definitions[c['type']]['intervals']})),c['root'] if c['bass'] is None else c['bass']);frames += [frame]*c['bars']
  fingerprint=min(tuple(frames[j:]+frames[:j]) for j in range(8));groups[fingerprint].append(t['id'])
 duplicates=[sorted(ids) for ids in groups.values() if len(ids)>1]
 return {'templates':templates,'definitions':definitions,'recipes':recipes,'bindings':bindings,'profiles':sorted(profiles['profiles'],key=lambda p:p['id']),'prefs':prefs,'sources':sources,'notes':noteMap,'duplicate_groups':sorted(duplicates)}

def validate(data):
 try:return _validate(data)
 except ValidationError:raise
 except (TypeError,KeyError,AttributeError,OverflowError,IndexError) as e:raise ValidationError('malformed typed source: '+str(e)) from e

def string(s):return json.dumps(s,ensure_ascii=False)
def flt(v):
 s=format(v,'.9g');return s+('' if '.' in s or 'e' in s.lower() else '.0')+'f'
def emit(data):
 m=validate(data);ts=sorted(m['templates'].values(),key=lambda t:t['id']);ps=m['profiles'];sh=data['chord_types.json'];out={}
 banner='// Generated by scripts/generate_harmony_catalog.py; edit data/harmony/*.json.\n#pragma once\n'
 ids=banner+'#include <cstdint>\nnamespace stromscore {\nenum class WendungId : uint32_t { invalid=0,\n'+''.join(f"    {t['symbol']}={t['id']}u,\n" for t in ts)+'    custom=65535u\n};\n}\n';out['Source/WendungId.h']=ids
 prof=banner+'#include <array>\nnamespace stromscore::composition {\nenum class ProfileId { '+','.join(p['symbol']+'='+str(p['id']) for p in ps)+' };\nstruct ProfileIdentity {ProfileId id;const char* name;bool harmonySelectionOnly;};\ninline constexpr std::array<ProfileIdentity,'+str(len(ps))+'> profileIdentities {{\n'+''.join('{ProfileId::'+p['symbol']+','+string(p['name'])+','+str(p['harmony_selection_only']).lower()+'},\n' for p in ps)+'}};\n}\n';out['Source/ProfileIdentity.generated.h']=prof
 shapes=banner+'namespace stromscore {\nenum ChordType {'+','.join(t['id']+'='+str(t['value']) for t in sh['types'])+',kNumChordTypes};\nstruct ChordShape {int n;int iv[5];const char* suffix;bool minor;};\ninline constexpr ChordShape kShapes[kNumChordTypes]={\n'+''.join('{'+str(len(t['intervals']))+',{'+','.join(map(str,t['intervals']))+'},'+string(t['suffix'])+','+str(t['minor']).lower()+'},\n' for t in sh['types'])+'};\ninline constexpr int kCustomTypes[]={'+','.join(sh['custom_choice_order'])+'};\ninline constexpr int kNumCustomTypes=sizeof(kCustomTypes)/sizeof(kCustomTypes[0]);\n}\n';out['Source/ChordTypes.generated.h']=shapes
 pure=banner+'#include "HarmonyTypes.h"\nnamespace stromscore {\ninline constexpr std::array<HarmonyTemplate,'+str(len(ts))+'> harmonyTemplates {{\n'
 for t in ts:
  chords=','.join('{'+','.join([str(c['root']),c['type'],str(c['bars']),'-1' if c['bass']is None else str(c['bass'])])+'}' for c in t['chords'])
  pure+='{WendungId::'+t['symbol']+','+string(t['name'])+','+','.join(flt(v) for v in t['xyz'])+','+str(len(t['chords']))+',{{'+chords+'}},{'+str(t['tonality']['center_pc'])+',composition::Mode::'+t['tonality']['mode']+'},'+str(sum(1 if g=='score' else 2 for g in t['genres']))+','+string(t['source_ref'])+',ChordColoration::'+('flexible' if t['coloration']=='flexible' else 'protectedColor')+'},\n'
 pure+='}};\ninline constexpr int harmonyIndex(WendungId id){\n int lo=0,hi=static_cast<int>(harmonyTemplates.size());while(lo<hi){int mid=lo+(hi-lo)/2;if(static_cast<uint32_t>(harmonyTemplates[mid].id)<static_cast<uint32_t>(id))lo=mid+1;else hi=mid;}return lo<static_cast<int>(harmonyTemplates.size())&&harmonyTemplates[lo].id==id?lo:-1;\n}\ninline constexpr const HarmonyTemplate* findHarmonyTemplate(WendungId id){int i=harmonyIndex(id);return i<0?nullptr:&harmonyTemplates[i];}\n}\n';out['Source/HarmonyCatalog.generated.h']=pure
 arr=banner+'#include "ArrangementTypes.h"\n#include "HarmonyCatalog.generated.h"\nnamespace stromscore {\ninline constexpr std::array<ArrangementRecipe,'+str(len(ts))+'> defaultArrangements {{\n'
 for t in ts:
  r=m['recipes'][m['bindings'][t['id']]];arr+='{{'+','.join(r['arp'])+'},{'+','.join(r['bass'])+'},'+r['pad']+','+str(-1 if r['hook']is None else r['hook'])+'},\n'
 arr+='}};\ninline constexpr int popHookPattern(WendungId id){int i=harmonyIndex(id);return i<0?-1:defaultArrangements[i].hook;}\n'
 for genre,variable in [('score','kWendungen'),('pop_rock','kPopWendungen')]:
  indices=[next(i for i,t in enumerate(ts) if t['id']==id) for id in data['catalog.json']['pools'][genre]]
  arr+='inline constexpr std::array<int,'+str(len(indices))+'> '+variable+'Indices {{'+','.join(map(str,indices))+'}};\n'
 arr+='}\n';out['Source/HarmonyStrategies.generated.h']=arr
 pref=banner+'#include "WendungId.h"\n#include "ProfileIdentity.generated.h"\n#include <array>\nnamespace stromscore::composition {\nstruct TemplatePreference {WendungId id;std::array<float,'+str(len(ps))+'> weights;};\ninline constexpr std::array<TemplatePreference,'+str(len(ts))+'> templatePreferences {{\n'
 for t in ts:pref+='{WendungId::'+t['symbol']+',{{'+','.join(flt(m['prefs'][p['symbol']].get(t['id'],1.)) for p in ps)+'}}},\n'
 pref+='}};\ninline constexpr float harmonicPreference(ProfileId p,WendungId id){int index=static_cast<int>(p);if(index<0||index>=static_cast<int>(profileIdentities.size()))return 1.f;int lo=0,hi=static_cast<int>(templatePreferences.size());while(lo<hi){int mid=lo+(hi-lo)/2;if(static_cast<uint32_t>(templatePreferences[mid].id)<static_cast<uint32_t>(id))lo=mid+1;else hi=mid;}return lo<static_cast<int>(templatePreferences.size())&&templatePreferences[lo].id==id?templatePreferences[lo].weights[index]:1.f;}\n}\n';out['Source/HarmonyPreferences.generated.h']=pref
 notes=banner+'// Editorial descriptions, independent of playback and instrument assignment.\nstruct WendungInfo {const char* idea;const char* instruments;const char* source;};\n'
 for genre,var in [('score','kScoreInfo'),('pop_rock','kPopInfo')]:
  notes+='inline constexpr WendungInfo '+var+'[]={\n'
  for id in data['catalog.json']['pools'][genre]:
   n=m['notes'][id];t=m['templates'][id];notes+='{'+','.join(string(v) for v in [n['idea'],n['instruments'],m['sources'][t['source_ref']]['text']])+'},\n'
  notes+='};\n'
 out['Source/WendungInfo.h']=notes
 out['docs/development/HARMONY_DATA_VALIDATION.json']=json.dumps({'schema_version':1,'templates':len(ts),'chord_types':len(sh['types']),'profiles':len(ps),'pools':{g:len(v) for g,v in data['catalog.json']['pools'].items()},'potential_harmonic_duplicate_groups':m['duplicate_groups'],'duplicate_policy':'warning only; preserve IDs, entry phase and independent strategies','source_sha256':{f:hashlib.sha256((json.dumps(data[f],sort_keys=True,ensure_ascii=False)).encode()).hexdigest() for f in FILES}},ensure_ascii=False,indent=2)+'\n'
 return out

def main():
 p=argparse.ArgumentParser();p.add_argument('--source',type=pathlib.Path,default=ROOT/'data/harmony');p.add_argument('--output-root',type=pathlib.Path,default=ROOT);p.add_argument('--check',action='store_true');a=p.parse_args()
 try:
  outputs=emit(load(a.source));stale=[]
  for name,content in outputs.items():
   target=a.output_root/name
   if a.check:
    if not target.exists() or target.read_text(encoding='utf-8')!=content:stale.append(name)
   else:target.parent.mkdir(parents=True,exist_ok=True);target.write_text(content,encoding='utf-8')
  if stale:raise ValidationError('generated files stale/missing: '+', '.join(stale)+'; run scripts/generate_harmony_catalog.py')
 except ValidationError as e:print(e,file=sys.stderr);return 1
 print('Harmony sources valid; generated static catalog '+('up to date' if a.check else 'written'));return 0
if __name__=='__main__':sys.exit(main())
