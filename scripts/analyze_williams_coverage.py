"""Actual registered P1 pool: public candidate diagnostics and exact selection threshold."""
import csv,json,pathlib,subprocess,sys
root=pathlib.Path(__file__).resolve().parents[1];out=pathlib.Path(sys.argv[1]);out.mkdir(parents=True,exist_ok=True)
exe=out/'coverage';subprocess.run(['c++','-std=c++17','-O1','-I',str(root/'Source'),str(root/'tools/williams_coverage.cpp'),'-o',str(exe)],check=True)
raw=subprocess.check_output([str(exe)]);(out/'coverage.csv').write_bytes(raw);rows=[list(map(float,l)) for l in csv.reader(raw.decode().splitlines())];result=[]
for v in(0,.5,1):
 r=[x for x in rows if x[0]==v];counts=[int(x[4]) for x in r]
 result.append(dict(variety=v,points=len(r),minimum=min(counts),maximum=max(counts),mean=sum(counts)/len(counts),single_candidate=counts.count(1),max_nearest_distance=max(x[6] for x in r),sampled_selected_ids=sorted({int(n) for x in r for n in x[7:]}),display_tolerance_differences=sum(x[4]!=x[5] for x in r),corners=[dict(xyz=[n/20 for n in x[1:4]],candidates=int(x[4]),distance=x[6],selected=sorted({int(n) for n in x[7:]})) for x in r if all(c in(0,20) for c in x[1:4])]))
(root/'docs/research/john-williams/P1_XYZ_COVERAGE.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8');print('49-entry runtime pool; 9261 points x three Variety settings; eight actual selections/point')
