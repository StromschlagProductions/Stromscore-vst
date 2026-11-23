"""Generate/check factual inventory from the compiled catalog exporter. No artist assignment."""
import argparse
import json
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parent.parent
TARGET = ROOT / 'docs/development'


def inventory(exporter):
    entries = json.loads(subprocess.check_output([str(exporter)], encoding='utf-8'))
    assert len(entries) == 84 and len({e['id'] for e in entries}) == 84
    for entry in entries:
        chords = entry['chords']
        total = sum(c['bars'] for c in chords)
        assert total == 8
        def identity(c):
            bass = c['bass_pc_relative_to_key']
            return (c['root_pc_relative_to_key'], c['type'],
                    c['root_pc_relative_to_key'] if bass is None else bass)
        changes = sum(identity(a) != identity(b) for a, b in zip(chords, chords[1:]))
        cyclic_changes = sum(identity(a) != identity(b) for a, b in zip(chords, chords[1:] + chords[:1]))
        entry['harmonic_rhythm'] = {
            'total_bars': total, 'slot_count': len(chords),
            'mean_slot_bars': total / len(chords),
            'min_slot_bars': min(c['bars'] for c in chords),
            'max_slot_bars': max(c['bars'] for c in chords),
            'actual_changes_within_phrase': changes,
            'actual_changes_including_cycle': cyclic_changes,
            'actual_changes_including_cycle_per_bar': cyclic_changes / total,
            'actual_changes_within_phrase_per_bar': changes / total,
        }
        motions = []
        for i, a in enumerate(chords):
            b = chords[(i + 1) % len(chords)]
            up = (b['root_pc_relative_to_key'] - a['root_pc_relative_to_key']) % 12
            shortest = up if up <= 6 else up - 12
            motions.append({'from_slot': i, 'to_slot': (i + 1) % len(chords),
                            'cycle_boundary': i == len(chords) - 1,
                            'ascending_semitones_mod12': up,
                            'shortest_semitones': shortest,
                            'tritone_direction_ambiguous': up == 6})
        entry['root_movements'] = motions
        tags = []
        for value, tag in [(0, 'repeated_root'), (1, 'semitone'), (2, 'whole_tone'),
                           (3, 'minor_third'), (4, 'major_third'), (5, 'fourth_or_fifth'), (6, 'tritone')]:
            if any(abs(m['shortest_semitones']) == value for m in motions):
                tags.append(tag)
        entry['root_movement_features'] = tags
        description = entry.pop('description')
        source = entry.pop('description_source')
        marker = 'Stilistischer Bezug:'
        hint = description.split(marker, 1)[1].split('. Zuordnung', 1)[0].strip().rstrip('.') if marker in description else description
        entry['existing_style_hint'] = {'status': 'unverified', 'text': hint,
                                        'description': description, 'source': source}
        entry['confirmed_profile_assignments'] = []
    return {'schema_version': 1, 'root_unit': 'semitones_relative_to_selected_key',
            'duration_unit': 'bars', 'meter_and_bpm': 'host_settings_not_catalog_metadata',
            'notes': ['Slot boundaries with unchanged chords are not harmonic changes.',
                      'Root movement uses pitch classes, not played register or voice-leading.',
                      'The final root movement is the cyclic return; +6 also means -6.',
                      'Existing textual style hints are unverified and do not assign profiles.'],
            'entries': entries}


def readable(data):
    lines = ['# Wendungsinventar – 84 vorhandene Studien', '',
             'Generiert aus dem kompilierten Quellkatalog. IDs bleiben bei ihrem Material; Reihenfolge und Inhalte sind erhalten.', '',
             'Akkordbeispiele stehen in C; Wurzeln und optionale Basstöne sind relativ zur gewählten Tonart. Dauern sind Takte.',
             'Mittlere Slotdauer und echte Akkordwechsel sind getrennt: wiederholte gleiche Akkorde zählen nicht als Wechsel.',
             'Es ist kein BPM festgelegt. Grundtonbewegungen sind kürzeste Tonklassenwege, keine gespielten Stimmführungen.',
             'Der letzte Weg ist die zyklische Rückkehr; ±6 ist richtungsmehrdeutig. Künstlerhinweise sind unbestätigt.', '']
    features = {'repeated_root': 'gleicher Grundton', 'semitone': 'Halbtonschritt',
                'whole_tone': 'Ganztonschritt', 'minor_third': 'kleine Terz',
                'major_third': 'große Terz', 'fourth_or_fifth': 'Quart-/Quintbeziehung',
                'tritone': 'Tritonus'}
    for e in data['entries']:
        r = e['harmonic_rhythm']
        progression = ' → '.join(f"{c['example_in_c']} [{c['type']}; {c['bars']} T.]" +
                                 (f" (Bass-PC {c['bass_pc_relative_to_key']})" if c['bass_pc_relative_to_key'] is not None else '')
                                 for c in e['chords'])
        motion = ', '.join(('±6' if m['tritone_direction_ambiguous'] else f"{m['shortest_semitones']:+d}") +
                           (' (Rückkehr)' if m['cycle_boundary'] else '') for m in e['root_movements'])
        lines += [f"## {e['id']} – {e['name']}", '',
                  f"- Katalog: {'Score' if e['catalog'] == 'score' else 'Pop/Rock'}, Position {e['catalog_index'] + 1}; XYZ: {e['xyz']}.",
                  f'- Akkordfolge: {progression}.',
                  f"- Wechseltempo: {r['slot_count']} Slots / {r['total_bars']} Takte; mittlere Slotdauer {r['mean_slot_bars']:.3g} Takte; Dauerbereich {r['min_slot_bars']}–{r['max_slot_bars']} Takte. Echte Wechsel innerhalb der Phrase: {r['actual_changes_within_phrase']} ({r['actual_changes_within_phrase_per_bar']:.3g} pro Takt, ohne Rückkehr).",
                  f"- Grundtonbewegungen in Halbtönen: {motion}. Merkmale: {', '.join(features[f] for f in e['root_movement_features'])}.",
                  f"- **Unbestätigter bestehender Stilhinweis:** {e['existing_style_hint']['text']}. Keine bestätigte Profilzuordnung.", '']
    return '\n'.join(lines).rstrip() + '\n'


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--exporter', required=True, type=Path)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    data = inventory(args.exporter.resolve())
    files = {'WENDUNGEN_INVENTAR.json': json.dumps(data, ensure_ascii=False, indent=2) + '\n',
             'WENDUNGEN_INVENTAR.md': readable(data)}
    for name, content in files.items():
        path = TARGET / name
        if args.check:
            if path.read_text(encoding='utf-8') != content:
                raise SystemExit(f'{path}: inventory differs; regenerate with the compiled exporter')
        else:
            path.write_text(content, encoding='utf-8')
    print('84 unique entries; generated inventories agree with compiled catalog.' if args.check else 'Generated both inventories.')


if __name__ == '__main__':
    main()
