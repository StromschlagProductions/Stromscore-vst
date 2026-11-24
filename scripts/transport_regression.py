"""Narrow allowance for reconstructed claims at explicit test transport boundaries.

Linear renders stay byte-exact. Existing attacks cannot disappear or move. Extra
attacks must start exactly at a declared seek, with balanced matching releases.
This is an offline assertion, not a compatibility path in the generator.
"""
from collections import Counter


def assert_chase_delta(before, after, cuts, *, layout='legacy', samples_per_quarter=24000):
    def canonical(data):
        if isinstance(data, bytes):
            data = [tuple(map(int, line.split(b','))) for line in data.splitlines()]
        if layout == 'legacy':
            return Counter((s, o, c, n, v, k) for s, c, n, v, k, o in data)
        assert layout == 'import'
        return Counter(data)

    old, new = canonical(before), canonical(after)
    removed, added = list((old-new).elements()), list((new-old).elements())
    cuts = set(cuts)
    assert all(e[5] or e[4] == 0 for e in removed), ('ordinary attack removed', removed)
    assert all((e[0] in cuts if e[5] else e[4] == 0 or e[0] in cuts) for e in added), ('non-chase addition', added)
    for e in removed:
        if e[5]:
            assert any(n[1:] == e[1:] and n[0] in cuts and 0 <= e[0]-n[0] <= samples_per_quarter for n in added), ('unrelated CC removal', e)
    balance = Counter()
    for sign, events in ((1, added), (-1, removed)):
        for _, _, channel, note, velocity, kind in events:
            if not kind:
                balance[channel, note] += sign * (1 if velocity else -1)
    assert not any(balance.values()), ('unbalanced reconstructed claims', balance)
    return {'added_events': len(added), 'removed_events': len(removed)}
