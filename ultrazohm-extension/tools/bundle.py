"""Build platform runtimes from checksum-pinned upstream distributions.

Use Python 3.14+, or Python 3.12+ with zstd on PATH for license extraction.
"""
import argparse
from contextlib import contextmanager
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import tarfile
import tempfile
import urllib.request
import uuid
import zipfile

ROOT = Path(__file__).resolve().parents[1]


def sha256(file):
    with file.open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def download(spec, cache):
    destination = cache / spec['sha256']
    if destination.exists() and sha256(destination) == spec['sha256']:
        return destination
    request = urllib.request.Request(spec['url'], headers={'User-Agent': 'ultrazohm-extension-build'})
    temporary = destination.with_suffix('.' + uuid.uuid4().hex + '.part')
    with urllib.request.urlopen(request, timeout=120) as response, temporary.open('wb') as stream:
        shutil.copyfileobj(response, stream)
    if sha256(temporary) != spec['sha256']:
        temporary.unlink()
        raise ValueError(f"Checksum mismatch: {spec['url']}")
    temporary.replace(destination)
    return destination


@contextmanager
def full_archive(file):
    try:
        import compression.zstd  # Python 3.14+
    except ImportError:
        with subprocess.Popen(['zstd', '-qdc', str(file)], stdout=subprocess.PIPE) as process:
            with tarfile.open(fileobj=process.stdout, mode='r|') as archive:
                yield archive
            if process.wait() != 0:
                raise RuntimeError('Could not decompress Python notices archive')
    else:
        with tarfile.open(file, mode='r:zst') as archive:
            yield archive


def bundle_serial(runtime, cache, spec):
    cache.mkdir(parents=True, exist_ok=True)
    wheel = download(spec, cache)
    destination = runtime / 'serial'
    destination.mkdir(parents=True, exist_ok=True)
    with zipfile.ZipFile(wheel) as archive:
        for name in archive.namelist():
            if name.startswith('serial/') and not name.endswith('/'):
                file = destination / name
                file.parent.mkdir(parents=True, exist_ok=True)
                file.write_bytes(archive.read(name))
        notices = runtime / 'licenses'
        notices.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(download(spec['license'], cache), notices / 'pyserial-LICENSE.txt')


def build(target, cache, replace=False):
    lock = json.loads((ROOT / 'runtime-lock.json').read_text())
    if (ROOT.parent / '.uv-version').read_text().strip() != lock['uv_version']:
        raise ValueError('Launcher uv version differs from runtime-lock.json')
    if not lock['python_version'].startswith((ROOT.parent / '.python-version').read_text().strip() + '.'):
        raise ValueError('Launcher Python version differs from runtime-lock.json')
    spec = lock['targets'][target]
    cache.mkdir(parents=True, exist_ok=True)
    files = {key: download(value, cache) for key, value in spec.items()}
    licenses = {name: download(value, cache) for name, value in lock['uv_licenses'].items()}
    destination = ROOT / 'runtime'
    if destination.exists() and not replace:
        raise ValueError('runtime/ exists; pass --replace to rebuild generated runtime files')
    with tempfile.TemporaryDirectory(prefix='uz-runtime-') as directory:
        stage = Path(directory)
        unpacked = stage / 'unpacked'
        unpacked.mkdir()
        if target == 'win32-x64':
            with zipfile.ZipFile(files['uv']) as archive:
                archive.extractall(unpacked)
            uv = unpacked / 'uv.exe'
        else:
            with tarfile.open(files['uv']) as archive:
                archive.extractall(unpacked, filter='data')
            uv = unpacked / 'uv-x86_64-unknown-linux-gnu' / 'uv'
        with tarfile.open(files['python']) as archive:
            archive.extractall(unpacked, filter='data')
        runtime = stage / 'runtime'
        (runtime / 'bin').mkdir(parents=True)
        shutil.copy2(uv, runtime / 'bin' / uv.name)
        system = 'windows-x86_64-none' if target == 'win32-x64' else 'linux-x86_64-gnu'
        python_dir = runtime / 'python' / f"cpython-{lock['python_version']}-{system}"
        shutil.copytree(unpacked / 'python', python_dir, symlinks=False)
        executable = python_dir / ('python.exe' if target == 'win32-x64' else 'bin/python3.12')
        if not executable.is_file():
            raise ValueError('Python executable missing in upstream archive')
        notices = runtime / 'licenses'
        notices.mkdir()
        for name, file in licenses.items():
            shutil.copyfile(file, notices / ('uv-' + name + '.txt'))
        with full_archive(files['python_notices']) as archive:
            for member in archive:
                if member.isfile() and (member.name.startswith('python/licenses/') or member.name == 'python/PYTHON.json'):
                    output = notices / Path(member.name).name
                    with archive.extractfile(member) as source, output.open('wb') as sink:
                        shutil.copyfileobj(source, sink)
        if not (notices / 'LICENSE.cpython.txt').is_file():
            raise ValueError('Upstream Python license notices missing')
        bundle_serial(runtime, cache, lock['pyserial'])
        manifest = {
            'platform': 'win32' if target == 'win32-x64' else 'linux', 'arch': 'x64', 'target': target,
            'python': executable.relative_to(runtime).as_posix(), 'uv_version': lock['uv_version'],
            'python_version': lock['python_version'], 'python_build': lock['python_build'],
            'sources': spec, 'uv_licenses': lock['uv_licenses'], 'pyserial': lock['pyserial'],
        }
        (runtime / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n')
        if destination.exists():
            shutil.rmtree(destination)
        shutil.copytree(runtime, destination)
    print(f'Bundled {target}: uv {lock["uv_version"]}, Python {lock["python_version"]}')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--target', choices=['linux-x64', 'win32-x64'], required=True)
    parser.add_argument('--cache', type=Path, default=ROOT / '.runtime-downloads')
    parser.add_argument('--replace', action='store_true')
    args = parser.parse_args()
    build(args.target, args.cache.resolve(), args.replace)
