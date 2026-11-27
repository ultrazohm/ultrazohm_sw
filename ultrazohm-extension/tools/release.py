"""Verify platform VSIXs and assemble GitHub Release assets; never publish applications."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import tempfile
import zipfile
import xml.etree.ElementTree as ET

ROOT = Path(__file__).resolve().parents[1]
TARGETS = ['linux-x64', 'win32-x64']


def digest(file):
    with file.open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def metadata(stamp=False):
    package_path = ROOT / 'package.json'
    package = json.loads(package_path.read_text())
    base = package['version']
    match = re.fullmatch(r'(\d+)\.(\d+)\.\d+', base)
    if package['name'] != 'ultrazohm-extension' or not match:
        raise ValueError('Expected ultrazohm-extension and numeric extension version')
    run = os.environ.get('GITHUB_RUN_NUMBER')
    if run is not None and (not run.isdecimal() or int(run) < 1):
        raise ValueError('Invalid workflow run number')
    version = f'{match[1]}.{match[2]}.{int(run)}' if run else base
    ref = os.environ.get('GITHUB_REF', '')
    branch_run = (os.environ.get('GITHUB_EVENT_NAME') == 'push'
                  and ref in {'refs/heads/main', 'refs/heads/develop'})
    manual = (os.environ.get('GITHUB_EVENT_NAME') == 'workflow_dispatch'
              and os.environ.get('UZ_EXTENSION_PUBLISH_PRERELEASE') == 'true')
    if manual and ref not in {'refs/heads/develop', 'refs/heads/feature/vscode-extension'}:
        raise ValueError('Manual publication is restricted to develop and feature/vscode-extension')
    prerelease = not (branch_run and ref == 'refs/heads/main')
    publish = bool(run and (branch_run or manual) and os.environ.get('GITHUB_REPOSITORY') == 'ultrazohm/ultrazohm_sw')
    if stamp:
        package['version'] = version
        package_path.write_text(json.dumps(package, indent=2) + '\n')
        lock_path = ROOT / 'package-lock.json'
        lock = json.loads(lock_path.read_text())
        lock['version'] = lock['packages']['']['version'] = version
        lock_path.write_text(json.dumps(lock, indent=2) + '\n')
    return {'version': version, 'tag': 'ultrazohm-extension-v' + version,
            'prerelease': prerelease, 'publish': publish}


def inspect_archive(target, vsix, unpack):
    info = metadata()
    if vsix.name != f'ultrazohm-extension-{target}-{info["version"]}.vsix':
        raise ValueError('VSIX filename does not match version/target')
    if unpack.exists():
        raise ValueError('Use a fresh extraction directory')
    with zipfile.ZipFile(vsix) as archive:
        if archive.testzip():
            raise ValueError('Corrupt VSIX')
        names = archive.namelist()
        manifest = archive.read('extension.vsixmanifest').decode()
        if f'TargetPlatform="{target}"' not in manifest:
            raise ValueError('Incorrect VSIX target')
        document = ET.fromstring(manifest)
        properties = {element.get('Id'): element.get('Value') for element in document.iter() if element.tag.split('}')[-1] == 'Property'}
        if (properties.get('Microsoft.VisualStudio.Code.PreRelease') == 'true') != info['prerelease']:
            raise ValueError('VSIX release channel does not match intended release')
        package = json.loads(archive.read('extension/package.json'))
        if package['name'] != 'ultrazohm-extension' or package['publisher'] != 'ZohmControlGmbH' or package['version'] != info['version']:
            raise ValueError('Incorrect extension identity/version')
        if any(name.startswith(('extension/test/', 'extension/node_modules/', 'extension/tools/')) for name in names):
            raise ValueError('Development-only files leaked into VSIX')
        required = ['extension/serial-terminal.py', 'extension/serial-controller.js', 'extension/serial-tools.js', 'extension/runtime/serial/serial/__init__.py', 'extension/runtime/licenses/pyserial-LICENSE.txt', 'extension/debug-adapter.py', 'extension/debug-controller.js', 'extension/debug-tools.js', 'extension/debug-rsp.js', 'extension/debug-main.tcl', 'extension/debug-xsct.py', 'extension/debug-server.py', 'extension/flash.py', 'extension/update-packages.py', 'extension/cpld-check.py', 'extension/launcher/uz.py', 'extension/launcher/requirements.txt', 'extension/runtime/licenses/LICENSE.cpython.txt', 'extension/runtime/licenses/uv-LICENSE-MIT.txt']
        if any(name not in names for name in required):
            raise ValueError('Runtime, launcher or license files missing')
        for member in archive.infolist():
            output = (unpack / member.filename).resolve()
            if not output.is_relative_to(unpack.resolve()):
                raise ValueError('Invalid archive path')
            archive.extract(member, unpack)
            if os.name != 'nt' and member.external_attr >> 16:
                output.chmod((member.external_attr >> 16) & 0o777)
    extension = unpack / 'extension'
    runtime = extension / 'runtime'
    bundled = json.loads((runtime / 'manifest.json').read_text())
    lock = json.loads((ROOT / 'runtime-lock.json').read_text())
    if bundled['target'] != target or bundled['sources'] != lock['targets'][target] or bundled.get('pyserial') != lock['pyserial']:
        raise ValueError('Runtime does not match lock')
    return extension, bundled


def verify(target, vsix, unpack, channel):
    extension, bundled = inspect_archive(target, vsix, unpack)
    runtime = extension / 'runtime'
    info = metadata()
    windows = target == 'win32-x64'
    if windows != (os.name == 'nt'):
        raise ValueError('Runtime smoke tests must run on the native OS')
    with tempfile.TemporaryDirectory(prefix='uz-package-smoke-') as directory:
        storage = Path(directory)
        env = {k: v for k, v in os.environ.items() if not re.match(r'UV_|PYTHON|VIRTUAL_ENV$|CONDA_PREFIX$', k)}
        path_key = next((key for key in env if key.lower() == 'path'), 'PATH')
        env[path_key] = str(runtime / 'bin') + os.pathsep + env.get(path_key, '')
        python = runtime / bundled['python']
        env.update(UZ_BUNDLED_RUNTIME=str(runtime), UZ_BUNDLED_PYTHON=str(python),
            UV_PYTHON_INSTALL_DIR=str(runtime / 'python'), UV_PYTHON_PREFERENCE='only-managed',
            UV_PYTHON_DOWNLOADS='never', UV_NO_CONFIG='1', UV_PYTHON_NO_REGISTRY='1',
            UV_PYTHON_INSTALL_REGISTRY='0', UV_PYTHON_INSTALL_BIN='0',
            UV_CACHE_DIR=str(storage / 'cache'), UV_TOOL_DIR=str(storage / 'tools'), UV_TOOL_BIN_DIR=str(storage / 'bin'),
            PYTHONDONTWRITEBYTECODE='1', PYTHONNOUSERSITE='1', TMPDIR=str(storage), TEMP=str(storage), TMP=str(storage))
        def run(args):
            try:
                return subprocess.check_output([str(a) for a in args], cwd=storage, env=env, text=True, timeout=300).strip()
            except subprocess.CalledProcessError as error:
                print(error.output, file=sys.stderr)
                raise
        assert run([python, '-c', 'import sys,ssl,sqlite3,ctypes; print(sys.version.split()[0])']) == bundled['python_version']
        assert run([python, '-I', '-B', extension / 'serial-terminal.py', 'self-test']) == 'Bundled pySerial loopback passed'
        uv = runtime / 'bin' / ('uv.exe' if windows else 'uv')
        assert run([uv, '--version']).split()[1] == bundled['uv_version']
        launcher = extension / 'launcher'
        command = [Path(os.environ['SystemRoot']) / 'System32/WindowsPowerShell/v1.0/powershell.exe', '-NoProfile', '-ExecutionPolicy', 'Bypass', '-File', launcher / 'uz.ps1'] if windows else ['/bin/bash', launcher / 'uz']
        run([*command, '--help'])
        # Validate refresh/cache behavior using local fixture wheels, without PyPI.
        subprocess.run([str(python), '-B', str(ROOT / 'tools/test_update_packages.py')],
            cwd=storage, env={**env, 'UZ_TEST_UV': str(uv), 'UZ_TEST_UPDATE_SCRIPT': str(extension / 'update-packages.py')}, check=True, timeout=180)
        resolved = {}
        if channel:
            for application in ['cli', 'dataviewer']:
                run([*command, application, channel, '--', '--help'])
            viewer_help = run([*command, 'dataviewer', channel, '--', 'gui', '--help'])
            if '--live-repo' not in viewer_help:
                raise ValueError('Published DataViewer no longer supports --live-repo')
            print(run([uv, 'tool', 'run', '--isolated', '--python', '3.12', '--prerelease', 'allow' if channel == 'prerelease' else 'disallow',
                '--from', 'ultrazohm-cli', 'python', ROOT / 'tools/published-contract.py', '--extension', extension, '--repository', ROOT.parent]))
            result = run([uv, 'tool', 'run', '--isolated', '--python', '3.12', '--prerelease', 'allow' if channel == 'prerelease' else 'disallow',
                '--with-requirements', launcher / 'requirements.txt', '--from', 'ultrazohm-dataviewer', 'python', '-c',
                'import json,matplotlib; from importlib.metadata import version; print(json.dumps({p:version(p) for p in ["ultrazohm-cli","ultrazohm-dataviewer","matplotlib"]}))'])
            resolved = json.loads(result)
    receipt = {**info, 'target': target, 'file': vsix.name, 'sha256': digest(vsix), 'bytes': vsix.stat().st_size,
        'commit': os.environ.get('GITHUB_SHA') or subprocess.check_output(['git', 'rev-parse', 'HEAD'], cwd=ROOT, text=True).strip(),
        'builder_image': os.environ.get('UZ_BUILD_IMAGE'), 'runtime': bundled, 'tested_channel': channel, 'tested_packages': resolved}
    vsix.with_suffix('.json').write_text(json.dumps(receipt, indent=2) + '\n')
    print(f'Verified {vsix.name}; extracted to {extension}')


def aggregate(directory):
    info = metadata()
    receipts = [json.loads(p.read_text()) for p in directory.glob('*.json') if p.name != 'release-manifest.json']
    if sorted(r['target'] for r in receipts) != sorted(TARGETS):
        raise ValueError('Both tested platform receipts are required')
    for receipt in receipts:
        if receipt['version'] != info['version'] or receipt['sha256'] != digest(directory / receipt['file']):
            raise ValueError('Artifact changed after verification')
        expected_commit = os.environ.get('GITHUB_SHA')
        if expected_commit and receipt['commit'] != expected_commit:
            raise ValueError('Artifact does not match the current commit')
        channel = 'prerelease' if info['prerelease'] else 'stable'
        if receipt.get('prerelease') != info['prerelease'] or receipt.get('tested_channel') != channel:
            raise ValueError('Artifact release channel mismatch')
        if not all(receipt.get('host_checks', {}).get(label) for label in ('1.93.0', 'stable')):
            raise ValueError('Both VS Code host checks are required')
        if not receipt['tested_packages'] or not receipt['tested_channel']:
            raise ValueError('Published-package smoke tests required for release')
    if len({r['commit'] for r in receipts}) != 1:
        raise ValueError('Both packages must come from the same commit')
    manifest = {**info, 'artifacts': sorted(receipts, key=lambda r: r['target'])}
    (directory / 'release-manifest.json').write_text(json.dumps(manifest, indent=2) + '\n')
    (directory / 'SHA256SUMS').write_text(''.join(f'{r["sha256"]}  {r["file"]}\n' for r in manifest['artifacts']))
    (directory / 'release-notes.md').write_text(f'''ultrazohm-extension {info['version']}

Download the VSIX for Linux x64 or Windows x64. In VS Code, use **Extensions: Install from VSIX…**, then reload the window.

This extension bundles uv, Python and launcher scripts. Application packages download from PyPI on first use. Runtime and tested application versions are recorded in `release-manifest.json`.

Setup, Software build and Control sections provide the UltraZohm tools. Vitis remains an external prerequisite. Flash UZ uses the CLI service to finalize recordings, program via JTAG and reconnect when a device target is known. It opens an interactive CLI if needed and verifies the selected checkout.

Uninstall either local prototype (`ultrazohm-local.ultrazohm` or `ultrazohm-local.ultrazohm-extension`) before installing this extension to avoid duplicate controls. The extension ID is `ZohmControlGmbH.ultrazohm-extension`; Marketplace publication follows the GitHub Release for successful main/develop branch runs. Existing `ultrazohm.*` settings are retained, but the renamed extension uses a fresh private cache.

GitHub VSIX updates are installed manually. Neither real hardware programming nor a real Vitis installation is exercised by CI.
''')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    commands = parser.add_subparsers(dest='command', required=True)
    commands.add_parser('metadata').add_argument('--stamp', action='store_true')
    check = commands.add_parser('verify')
    check.add_argument('--target', choices=TARGETS, required=True)
    check.add_argument('--vsix', type=Path, required=True)
    check.add_argument('--extract', type=Path, required=True)
    check.add_argument('--smoke-channel', choices=['stable', 'prerelease'])
    inspect = commands.add_parser('inspect')
    inspect.add_argument('--target', choices=TARGETS, required=True)
    inspect.add_argument('--vsix', type=Path, required=True)
    inspect.add_argument('--extract', type=Path, required=True)
    manifest = commands.add_parser('manifest')
    manifest.add_argument('directory', type=Path)
    args = parser.parse_args()
    if args.command == 'metadata':
        for key, value in metadata(args.stamp).items():
            print(f'{key}={str(value).lower() if isinstance(value, bool) else value}')
    elif args.command == 'inspect':
        inspect_archive(args.target, args.vsix.resolve(), args.extract.resolve())
    elif args.command == 'verify':
        verify(args.target, args.vsix.resolve(), args.extract.resolve(), args.smoke_channel)
    else:
        aggregate(args.directory.resolve())
