"""Actual 128-bar MIDI comparisons against 11abda9; no musical decisions mocked."""
import argparse, collections, hashlib, json, math, pathlib, statistics, struct, subprocess, zipfile
from reference_headers import header_snapshot

root = pathlib.Path(__file__).resolve().parents[1]
p = argparse.ArgumentParser(); p.add_argument('--output', required=True); a = p.parse_args()
out = pathlib.Path(a.output); out.mkdir(parents=True, exist_ok=True)
cases = []
rhythm_roles={int(r['id'][-2:]):set(r['roles']) for r in json.loads((root/'data/barry/vocabulary.json').read_text())['rhythms'] if r['enabled']}
def case(name, x, y, z, profile=1, genre=0, path=0, num=4, den=4, variation=3, manual=0, follow=1, swing=0, bpm=100):
    cases.append(dict(name=name, profile=profile, genre=genre, x=x, y=y, z=z, path=path, num=num, den=den,
                      variation=variation, manual=manual, follow=follow, swing=swing, bpm=bpm))
for x in (0, .3, .85, 1):
    for y in (.2, .6, 1):
        for z in (0, .5, 1): case(f'grid-{x}-{y}-{z}', x, y, z)
for name,x,y,z,num,den in [('warm',.8,.3,.1,4,4),('mystery',.2,.45,.4,4,4),('R05',.3,.75,.7,4,4),
        ('R04',.3,.55,.5,3,4),('R26',.3,.65,.55,3,4),('R14',.35,.6,.5,4,4),('R01',.45,.15,.1,4,4),('R11',.6,.15,.1,6,8),('R17',.65,.2,.1,3,4),
        ('unrest-94',.85,.95,.94,4,4),('unrest-95',.85,.95,.95,4,4),('unrest-100',.85,.95,1,4,4)]:
    case(name,x,y,z,num=num,den=den)
for path in (1,2,3):
    for variation in (1,3,7):case(f'drive-{path}-v{variation}',.5,.7,.5,path=path,variation=variation)
for follow in (0,1):
    for num,den in ((4,4),(3,4)):
        case(f'follow-{follow}-{num}',.85,.95,1,follow=follow,num=num,den=den,swing=.3)
for manual in (1,2):case(f'barry-manual-{manual}',.5,.7,.5,path=2,manual=manual)
# Exact unchanged contexts: Neutral/Herrmann Score, all Pop/Rock profile parameter values.
for genre, profile in ((0,0),(0,2),(1,0),(1,1),(1,2)):
    for path in (0,1,2):
        case(f'regression-{genre}-{profile}-{path}',.85,.95,1,profile=profile,genre=genre,path=path)
# Establish the inherited non-integral-tempo rounding separately on both revisions.
for bpm in (90,173):case(f'tempo-{bpm}',.85,.95,.85,manual=2,bpm=bpm)

def args(c, block=512):
    return [str(c[k]) for k in ('profile','genre','x','y','z','path','num','den','variation','manual','follow','swing')] + [str(block),str(c['bpm'])]
def rows(raw): return [tuple(map(int,line.split(b','))) for line in raw.splitlines()]
def music(rr): return [r[:6] for r in rr]
def digest(rr): return hashlib.sha256(json.dumps(music(rr),separators=(',',':')).encode()).hexdigest()
def stats(rr,c):
    active={}; ons=collections.Counter(); lengths=collections.defaultdict(list); rhythms=collections.Counter(); grids=collections.defaultdict(list)
    attacks=collections.defaultdict(set)
    spq=48000*60/c['bpm']; window=4*c['num']*4/c['den']*spq
    for at,o,ch,n,v,kind,r in rr:
        if kind: continue
        k=(ch,n)
        if v:
            assert k not in active,('double note',at,k)
            active[k]=(at,o);ons[o]+=1
            attacks[o].add(at)
            role='bass' if o in (2,3) else 'movement' if o==4 else ''
            if r and not c['manual'] and role in rhythm_roles.get(r,set()):rhythms[r]+=1
            if o<=4 and at<window:grids[o].append(round(at/spq,5))
        else:
            assert k in active,('orphan note-off',at,k)
            begin,owner=active.pop(k);lengths[owner].append((at-begin)/48000)
    assert not active,'hanging notes'
    return dict(sha256=digest(rr),note_ons=dict(ons),attack_positions={k:len(v) for k,v in attacks.items()},median_seconds={k:statistics.median(v) for k,v in lengths.items()},
                max_seconds={k:max(v) for k,v in lengths.items()},rhythm_ids_with_bass_or_arp_attacks=dict(rhythms),
                first_four_bar_onsets_quarters={k:sorted(set(v)) for k,v in grids.items()})
def vlq(n):
    b=[n&127];n>>=7
    while n:b.insert(0,(n&127)|128);n>>=7
    return bytes(b)
def midi(path,rr,c):
    track=bytearray(b'\0\xff\x51\3'+round(60000000/c['bpm']).to_bytes(3,'big'))
    track+=b'\0\xff\x58\4'+bytes([c['num'],int(math.log2(c['den'])),24,8]);last=0
    for at,o,ch,n,v,kind,r in rr:
        tick=round(at*c['bpm']/(48000*60)*960)
        track+=vlq(tick-last)+bytes([(0xb0 if kind else 0x90 if v else 0x80)+ch-1,n,v]);last=tick
    track+=b'\0\xff\x2f\0';path.write_bytes(b'MThd'+struct.pack('>IHHH',6,0,1,960)+b'MTrk'+struct.pack('>I',len(track))+track)

result=[]; before={}; artifacts=[]
for revision in ('11abda9','working'):
    d=out/revision;d.mkdir(exist_ok=True)
    for name,raw in header_snapshot(root,None if revision=='working' else revision).items():
        target=d/name
        if not target.exists() or target.read_bytes()!=raw:target.write_bytes(raw)
    exe=d/'probe'; source=root/'tools/barry_accompaniment_probe.cpp'
    newest=max([source.stat().st_mtime]+[h.stat().st_mtime for h in d.glob('*.h')])
    if not exe.exists() or exe.stat().st_mtime<newest:
        subprocess.run(['c++','-std=c++17','-O2']+(['-DBARRY_ACCOMPANIMENT_CURRENT'] if revision=='working' else [])+
                       ['-I',str(d),str(source),'-o',str(exe)],check=True)
    for c in cases:
        cache=d/(c['name']+'.csv')
        if not cache.exists() or cache.stat().st_mtime<exe.stat().st_mtime:
            cache.write_bytes(subprocess.check_output([str(exe),*args(c)]))
        rr=rows(cache.read_bytes()); info=stats(rr,c); info.update(c,revision=revision,bars=128)
        if revision=='11abda9': before[c['name']]=rr
        else:
            old=before[c['name']];info['byte_identical_music']=music(old)==music(rr)
            unchanged=c['genre']==1 or c['profile']!=1 or c['manual']
            if unchanged:assert info['byte_identical_music'],('outside Auto Score-Barry changed',c)
            # A changed accompaniment can reorder distinct simultaneous MIDI events;
            # protect the exact timed melodic/accent events, not cross-part list order.
            assert sorted(r[:6] for r in old if r[1]>=5)==sorted(r[:6] for r in rr if r[1]>=5),('accents or melodic roles changed',c)
            if c['name'] in ('R05','R04','R26','unrest-100','drive-2-v3','follow-0-4'):
                for block in (127,8192):assert music(rows(subprocess.check_output([str(exe),*args(c,block)])))==music(rr),('block difference',c,block)
        if c['name'] in ('warm','R05','R04','R26','unrest-94','unrest-95','unrest-100','drive-2-v3'):
            target=d/(c['name']+'.mid');midi(target,rr,c);artifacts.append(target)
        if c['name'].startswith('tempo-'):
            other=rows(subprocess.check_output([str(exe),*args(c,127)]));assert len(rr)==len(other)
            delta=max((abs(x[0]-y[0]) for x,y in zip(rr,other)),default=0)
            assert delta<=1 and all(x[1:6]==y[1:6] for x,y in zip(rr,other)),('tempo event data changed',revision,c)
            info['block_sample_rounding_max']=delta
        result.append(info);print(revision,c['name'],info['note_ons'],flush=True)
    (out/'measurements.json').write_text(json.dumps(result,indent=2)+'\n')
with zipfile.ZipFile(out/'BARRY_BEGLEITUNG_MIDI_AB.zip','w',compression=zipfile.ZIP_DEFLATED) as z:
    for path in artifacts:z.write(path,path.relative_to(out))
    z.writestr('HOERHINWEISE.txt','STROMSCORE Barry-Begleitung, 128-Takte-MIDI-Vergleich\n'
        '11abda9 = vorher; working = nachher. Tempo 100 BPM, Tonart D.\n'
        'R04/R26: 3/4. Andere Beispiele: 4/4. DAW-Tempo/Taktart passend einstellen.\n'
        'Kanäle 1/2: Fläche lang/kurz; 3/4: Bass lang/kurz; 5: Arp; 6/7: Tupfer/Stich; 8: Dialog; 9: Melodie.\n'
        'Geeignete Lang-/Kurz-Patches verwenden; dieselben Instrumente für beide Fassungen.\n'
        'warm: ruhiger Vergleich. R05: 4-8-16-8-Verdichtung. R04/R26: Kreisfigur im Dreier.\n'
        'unrest-94/95/100: hohe Energie und letzte Unruhezone. drive-2-v3: schnelle XYZ-Fahrt.\n'
        'Die Beispiele sind eigene algorithmische Ausgaben, keine Transkriptionen von Barry-Cues.\n')
print(len(cases),'before/after pairs x 128 bars; unchanged profiles/manual modes, accents and melodic notes verified')
