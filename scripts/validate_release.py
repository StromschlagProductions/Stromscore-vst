"""Validate the distributable, without executing the downloaded native plugin."""
import hashlib
import json
import re
import struct
import sys
import zipfile
from pathlib import Path


def validate(path, version):
    with zipfile.ZipFile(path) as archive:
        names = [info.filename.replace('\\', '/') for info in archive.infolist()]
        if not names or any(not name.startswith('Stromscore.vst3/') for name in names):
            raise ValueError('ZIP must directly contain Stromscore.vst3 only')
        if len({name.casefold() for name in names}) != len(names):
            raise ValueError('Duplicate case-insensitive archive paths')
        if any('..' in name.split('/') or name.startswith('/') or ':' in name or name.lower().endswith('.zip') for name in names):
            raise ValueError('Unsafe path or nested ZIP')
        if archive.testzip() is not None:
            raise ValueError('ZIP CRC failure')
        native = archive.read('Stromscore.vst3/Contents/x86_64-win/Stromscore.vst3')
        pe = struct.unpack_from('<I', native, 0x3c)[0]
        if native[:2] != b'MZ' or native[pe:pe + 4] != b'PE\0\0' or struct.unpack_from('<H', native, pe + 4)[0] != 0x8664:
            raise ValueError('Native plugin is not Windows AMD64')
        raw = archive.read('Stromscore.vst3/Contents/Resources/moduleinfo.json').decode('utf-8-sig')
        metadata = json.loads(re.sub(r',\s*([}\]])', r'\1', raw))  # Steinberg JSON allows trailing commas.
        if not re.fullmatch(re.escape(version) + r'(\.0){0,2}', metadata['Version']):
            raise ValueError('VST3 metadata version mismatch')
    digest = hashlib.sha256(Path(path).read_bytes()).hexdigest()
    return f'{digest}  {Path(path).name}\n'


if __name__ == '__main__':
    target, expected = sys.argv[1:]
    checksum = validate(target, expected)
    Path(target + '.sha256').write_text(checksum, encoding='ascii')
    print('ZIP structure, CRC, Windows x64 identity and version verified.')
    print(checksum, end='')
