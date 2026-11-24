"""Offline-only friend access to validate actual claim execution between pattern cells."""
import pathlib,sys
root=pathlib.Path(__file__).resolve().parents[1]
dest=pathlib.Path(sys.argv[1]);dest.mkdir(parents=True,exist_ok=True)
for path in (root/'Source').glob('*.h'):
 data=path.read_text(encoding="utf-8")
 if path.name=='ScoreEngine.h':
  needle='class Generator\n{\npublic:';assert needle in data
  data=data.replace(needle,'class Generator\n{\n    friend struct ExecutionTestAccess;\npublic:',1)
 (dest/path.name).write_text(data,encoding="utf-8")
