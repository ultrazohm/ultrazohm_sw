"""Isolated packaging entry point, shared by containers and CI."""
import argparse
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import release

ROOT = Path(__file__).resolve().parents[2]

def build(target, output, test=False):
    output.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='uz-extension-build-') as temporary:
        repo = Path(temporary) / 'source'
        repo.mkdir()
        shutil.copytree(ROOT / 'ultrazohm-extension', repo / 'ultrazohm-extension', ignore=shutil.ignore_patterns('node_modules', 'runtime', 'launcher', 'dist', '.runtime-downloads', '.package-test', '.archive-test', '.vscode-test', '.build-cache', '__pycache__', '*.vsix'))
        for source in list(ROOT.glob('uz*')) + list(ROOT.glob('test_uz*.py')) + [ROOT / name for name in ['requirements.txt', '.python-version', '.uv-version']]:
            if source.is_file():
                shutil.copy2(source, repo / source.name)
        for relative in ['vitis/software/Baremetal/src/include/javascope.h', 'vitis/software/Baremetal/src/include/javascope_status.h', 'vitis/software/shared/APU_RPU_shared.h', 'vitis/software/FreeRTOS/main.h', 'vitis/software/FreeRTOS/defines.h']:
            source = ROOT / relative
            if source.exists():
                destination = repo / relative
                destination.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(source, destination)
        extension = repo / 'ultrazohm-extension'
        env = dict(os.environ)
        cache = Path(env['UZ_BUILD_CACHE']) if env.get('UZ_BUILD_CACHE') else None
        if cache:
            env['npm_config_cache'] = str(cache / 'npm')
        if not env.get('GITHUB_SHA'):
            # A mounted worktree may reference a Git directory outside the mount.
            try:
                env['GITHUB_SHA'] = subprocess.check_output(['git', 'rev-parse', 'HEAD'], cwd=ROOT, text=True, stderr=subprocess.DEVNULL).strip()
            except (OSError, subprocess.CalledProcessError):
                env['GITHUB_SHA'] = 'local-unresolved'

        def run(*args):
            try:
                subprocess.run(args, cwd=extension, env=env, check=True)
            except Exception:
                diagnostics = output / 'diagnostics' / target
                diagnostics.mkdir(parents=True, exist_ok=True)
                (diagnostics / 'failed-command.json').write_text(json.dumps(list(args), indent=2))
                # Preserve VS Code profiles, including extension-host logs.
                for profile in Path(tempfile.gettempdir()).glob('ultrazohm-extension-test-*'):
                    shutil.copytree(profile, diagnostics / profile.name, dirs_exist_ok=True)
                raise
        run(sys.executable, 'tools/release.py', 'metadata', '--stamp')
        info = release.metadata()
        version = info['version']
        run('npm', 'ci')
        run('npm', 'run', 'check')
        run('npm', 'test')
        run(sys.executable, '-m', 'unittest', 'discover', '-s', 'tools', '-p', 'test_*.py')
        run(sys.executable, '-m', 'unittest', 'discover', '-s', '..', '-p', 'test_uz_shell.py')
        run(sys.executable, 'tools/bundle.py', '--target', target, *(['--cache', str(cache / target)] if cache else []))
        run(sys.executable, '-m', 'unittest', 'discover', '-s', 'tools', '-p', 'test_serial.py')
        vsix = extension / f'ultrazohm-extension-{target}-{version}.vsix'
        flags = ['--pre-release'] if info['prerelease'] else []
        run('npm', 'run', 'package', '--', '--target', target, '--out', str(vsix), *flags)
        run(sys.executable, 'tools/release.py', 'inspect', '--target', target, '--vsix', str(vsix), '--extract', '.archive-test')
        if test:
            if target != 'linux-x64':
                raise ValueError('Windows runtime verification requires a Windows host')
            run(sys.executable, 'tools/release.py', 'verify', '--target', target, '--vsix', str(vsix), '--extract', '.package-test', '--smoke-channel', 'prerelease' if flags else 'stable')
            run(sys.executable, 'tools/debug-integration.py')
            env['UZ_EXTENSION_TEST_PATH'] = '.package-test/extension'
            env['UZ_TEST_RECEIPT'] = str(vsix.with_suffix('.json'))
            for version in ['1.93.0', 'stable']:
                env['VSCODE_TEST_VERSION'] = version
                run('xvfb-run', '-a', 'npm', 'run', 'test:host')
        # An unverified rebuild must never retain a previous verification receipt.
        (output / vsix.with_suffix('.json').name).unlink(missing_ok=True)
        shutil.copy2(vsix, output / vsix.name)
        receipt = vsix.with_suffix('.json')
        if receipt.exists():
            shutil.copy2(receipt, output / receipt.name)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--target', choices=['linux-x64', 'win32-x64', 'all'], default='all')
    parser.add_argument('--output', type=Path, default=ROOT / 'ultrazohm-extension/dist')
    parser.add_argument('--test', action='store_true')
    args = parser.parse_args()
    for target in ['linux-x64', 'win32-x64'] if args.target == 'all' else [args.target]:
        build(target, args.output.resolve(), args.test)
