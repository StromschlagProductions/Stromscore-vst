#!/usr/bin/env python3
"""Build/run the independent v1.9 versus development MIDI comparison. No network needed."""
import argparse,subprocess
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--output',type=Path,required=True);a=p.parse_args()
root=Path(__file__).resolve().parents[1];out=a.output.resolve();out.mkdir(parents=True,exist_ok=True)
# Pinned released source, not the potentially changed main branch.
source=subprocess.check_output(['git','show','22be37ee755391f3651d7f5718c2e3d302c722ea:Source/ScoreEngine.h'],cwd=root)
(out/'ScoreEngine19.h').write_bytes(source)
cmd=['c++','-std=c++17','-O2','-I'+str(root/'Source'),'-I'+str(root/'Tests'),'-DREFERENCE_ENGINE_HEADER="'+str(out/'ScoreEngine19.h')+'"',str(root/'Tests/VoiceLeadingTests.cpp'),'-o',str(out/'VoiceLeadingTests')]
subprocess.run(cmd,check=True)
subprocess.run([str(out/'VoiceLeadingTests'),str(out)],check=True)
(out/'README.md').write_bytes((root/'docs/development/VOICE_LEADING.md').read_bytes())
