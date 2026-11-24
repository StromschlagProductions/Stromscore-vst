"""Test-only selection seam and an explicitly frozen historical candidate pool.
Production source and compiled plugin selection are never changed.
"""
import pathlib,re,sys
sys.path.insert(0,str(pathlib.Path(__file__).resolve().parents[1]/'scripts'))
from reference_headers import header_snapshot
root=pathlib.Path(__file__).resolve().parents[1]
def prepare(destination,revision=None,historical=False,explicit=False):
 headers=header_snapshot(root,revision)
 if historical:
  name='HarmonyStrategies.generated.h';s=headers[name].decode();pattern=r'(inline constexpr std::array<int,)\d+(> kPopWendungenIndices \{\{)([^}]+)(\}\};)'
  def trim(m):return m[1]+'36'+m[2]+','.join(m[3].split(',')[:36])+m[4]
  s,count=re.subn(pattern,trim,s);assert count==1;headers[name]=s.encode()
 if explicit:
  name='ScoreEngine.h';s=headers[name].decode();s=s.replace('namespace stromscore\n{','namespace stromscore\n{\ninline WendungId importTestId=WendungId::invalid;',1)
  needle='static int pick (const Settings& s, long long salt)\n    {';assert needle in s
  s=s.replace(needle,needle+'\n        if(importTestId!=WendungId::invalid)return wendungIndex(s.genre,importTestId);',1)
  needle='bool maybeSwitch (long long k, const Pos& p, const Settings& s)\n    {'
  if needle not in s:needle='bool maybeSwitch (musicaltime::Tick time, const Pos& p, const Settings& s)\n    {'
  assert needle in s
  s=s.replace(needle,needle+'\n        if(importTestId!=WendungId::invalid)return false;',1);headers[name]=s.encode()
 p=pathlib.Path(destination);p.mkdir(parents=True,exist_ok=True)
 for n,v in headers.items():(p/n).write_bytes(v)
if __name__=='__main__':
 prepare(sys.argv[1]+'/import',explicit=True);prepare(sys.argv[1]+'/historical',historical=True)
