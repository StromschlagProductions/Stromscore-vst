"""Small regression fixtures for the release gate; no native code is executed."""
import importlib.util
import json
import struct
import tempfile
import unittest
import warnings
import zipfile
from pathlib import Path

spec = importlib.util.spec_from_file_location('release_gate', Path(__file__).resolve().parents[1] / 'scripts/validate_release.py')
gate = importlib.util.module_from_spec(spec)
spec.loader.exec_module(gate)


class ReleaseTests(unittest.TestCase):
    def entries(self):
        pe = bytearray(256)
        pe[:2] = b'MZ'
        struct.pack_into('<I', pe, 0x3c, 128)
        pe[128:132] = b'PE\0\0'
        struct.pack_into('<H', pe, 132, 0x8664)
        return [
            ('Stromscore.vst3/Contents/x86_64-win/Stromscore.vst3', pe),
            ('Stromscore.vst3/Contents/Resources/moduleinfo.json', json.dumps({'Version': '1.9.0'}).encode()),
        ]

    def check(self, entries, valid=False):
        with tempfile.TemporaryDirectory() as directory:
            archive = Path(directory) / 'plugin.zip'
            with warnings.catch_warnings():
                warnings.simplefilter('ignore', UserWarning)
                with zipfile.ZipFile(archive, 'w') as output:
                    for name, data in entries:
                        output.writestr(name, data)
            if valid:
                self.assertTrue(gate.validate(archive, '1.9').endswith('  plugin.zip\n'))
            else:
                with self.assertRaises((ValueError, KeyError)):
                    gate.validate(archive, '1.9')

    def test_installable_bundle(self):
        self.check(self.entries(), True)

    def test_wrapper_directory(self):
        self.check([('Downloads/' + name, data) for name, data in self.entries()])

    def test_case_insensitive_duplicate(self):
        entries = self.entries()
        self.check(entries + [(entries[0][0].upper(), entries[0][1])])

    def test_nested_zip(self):
        self.check(self.entries() + [('Stromscore.vst3/extra.zip', b'bad')])

    def test_traversal(self):
        self.check(self.entries() + [('Stromscore.vst3/../outside.txt', b'bad')])

    def test_wrong_architecture(self):
        entries = self.entries()
        struct.pack_into('<H', entries[0][1], 132, 0x14c)
        self.check(entries)

    def test_wrong_version(self):
        entries = self.entries()
        entries[1] = (entries[1][0], b'{"Version":"1.8"}')
        self.check(entries)


if __name__ == '__main__':
    unittest.main()
