"""Validate release artifacts and write their manifest and SHA256SUMS."""
import argparse
from email.parser import BytesParser
import hashlib
import json
from pathlib import Path
import zipfile


def manifest(directory, version):
    directory = Path(directory)
    files = sorted([*directory.glob('*.whl'), *directory.glob('*.zip')])
    expected = {'ultrazohm-cli': 2, 'ultrazohm-dataviewer': 1}
    entries = []
    platforms = set()
    for path in files:
        if path.suffix == '.whl':
            with zipfile.ZipFile(path) as archive:
                metadata, = [n for n in archive.namelist() if n.endswith('.dist-info/METADATA')]
                package = BytesParser().parsebytes(archive.read(metadata))
                name = package['Name'].replace('_', '-').lower()
                if package['Version'] != version or name not in expected:
                    raise ValueError(f'Unexpected wheel metadata: {path.name}')
                wheel_info, = [n for n in archive.namelist() if n.endswith('.dist-info/WHEEL')]
                tags = BytesParser().parsebytes(archive.read(wheel_info)).get_all('Tag', [])
                if name == 'ultrazohm-cli':
                    platform = ('windows' if any(t.endswith('-win_amd64') for t in tags)
                                else 'linux' if any(t.endswith('-manylinux_2_28_x86_64') for t in tags)
                                else None)
                    if platform is None or platform in platforms:
                        raise ValueError('Expected one Windows and one manylinux_2_28 CLI wheel')
                    platforms.add(platform)
                elif tags != ['py3-none-any']:
                    raise ValueError('Expected a platform-independent viewer wheel')
                expected[name] -= 1
                if name == 'ultrazohm-dataviewer' and f'ultrazohm-cli=={version}' not in package.get_all('Requires-Dist', []):
                    raise ValueError('Viewer wheel does not require the matching CLI')
        with path.open('rb') as stream:
            digest = hashlib.file_digest(stream, 'sha256').hexdigest()
        entries.append({'file': path.name, 'size': path.stat().st_size, 'sha256': digest})
    if any(expected.values()):
        raise ValueError(f'Missing or extra wheels: {expected}')
    expected_zips = {f'{name}-{version}-windows-x86_64.zip' for name in expected}
    if {p.name for p in files if p.suffix == '.zip'} != expected_zips:
        raise ValueError('Expected CLI and viewer Windows archives')
    if list(directory.glob('*.tar.gz')):
        raise ValueError('Linux standalone archives are not release artifacts')
    (directory / 'manifest.json').write_text(json.dumps({'version': version, 'artifacts': entries}, indent=2) + '\n')
    (directory / 'SHA256SUMS').write_text(''.join(f"{e['sha256']}  {e['file']}\n" for e in entries))


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory')
    parser.add_argument('version')
    args = parser.parse_args()
    manifest(args.directory, args.version)
