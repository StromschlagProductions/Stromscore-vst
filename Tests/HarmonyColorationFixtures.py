"""Generate extra harmonic templates/profiles only into an isolated test include directory."""
import copy,importlib.util,json,pathlib,shutil,sys
root=pathlib.Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('harmony_generator',root/'scripts/generate_harmony_catalog.py');gen=importlib.util.module_from_spec(spec);spec.loader.exec_module(gen)
def create(destination):
 d=gen.load(root/'data/harmony');profileBase=len(d['profiles.json']['profiles']);cat=d['catalog.json'];arr=d['arrangements.json'];base=cat['templates'][0]
 # Equal distances permit the full real XYZ range while test profiles select a fixture explicitly.
 for t in cat['templates']:t['xyz']=[.5,.5,.5]
 for i,kind in enumerate(t['id'] for t in d['chord_types.json']['types']):
  for protected in (False,True):
   case=i*2+int(protected);id=3000+case;t=copy.deepcopy(base)
   t.update(id=id,symbol='colorationFixture'+str(case),name='Synthetic '+kind,xyz=[.5,.5,.5],genres=['score','pop_rock'],coloration='protected' if protected else 'flexible',tonality={'center_pc':0,'mode':'automatic'})
   t['chords']=[{'root':r,'type':kind,'bars':2,'bass':9 if r==5 else None} for r in (0,5,10,0)]
   cat['templates'].append(t)
   for pool in cat['pools'].values():pool.append(id)
   recipe=copy.deepcopy(arr['recipes'][0]);recipe.update(id='colorationRecipe'+str(case),hook=1,arp=['ArpCircle','ArpCell'],bass=['BassHeld','BassHeld'],pad='PadHeld');arr['recipes'].append(recipe);arr['bindings'].append({'template_id':id,'recipe':recipe['id']})
   d['notes.json']['entries'].append({'template_id':id,'idea':'Synthetic test only','instruments':'Independent'})
   d['profiles.json']['profiles'].append({'id':case+profileBase,'symbol':'colorationTest'+str(case),'name':'Synthetic '+str(case),'harmony_selection_only':True,'weights':[{'template_id':id,'factor':1e12}]})
 # A protected copy of the existing modal-hook study exercises checked melodic non-chord tones.
 modal=copy.deepcopy(next(t for t in cat['templates'] if t['id']==2035));modal.update(id=3100,symbol='protectedModalFixture',name='Synthetic protected modal hook',coloration='protected')
 cat['templates'].append(modal);cat['pools']['pop_rock'].append(3100)
 binding=next(b['recipe'] for b in arr['bindings'] if b['template_id']==2035);arr['bindings'].append({'template_id':3100,'recipe':binding})
 d['notes.json']['entries'].append({'template_id':3100,'idea':'Synthetic modal test only','instruments':'Independent'})
 d['profiles.json']['profiles'].append({'id':profileBase+2*len(d['chord_types.json']['types']),'symbol':'protectedModalTest','name':'Synthetic modal','harmony_selection_only':True,'weights':[{'template_id':3100,'factor':1e12}]})
 gen.validate(d);destination=pathlib.Path(destination);source=destination/'Source';source.mkdir(parents=True,exist_ok=True)
 for f in (root/'Source').glob('*.h'):shutil.copyfile(f,source/f.name)
 for name,content in gen.emit(d).items():target=destination/name;target.parent.mkdir(parents=True,exist_ok=True);target.write_text(content,encoding='utf-8')
 # Leave the exact validated sources available for the separate processor integration build.
 sources=destination/'data/harmony';sources.mkdir(parents=True,exist_ok=True)
 for name,value in d.items():(sources/name).write_text(json.dumps(value,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
if __name__=='__main__':create(sys.argv[1])
