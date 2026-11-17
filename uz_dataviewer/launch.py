"""Shared developer launcher; the shell wrappers only bootstrap uv/Python."""
import os
from pathlib import Path
import shutil
import subprocess
import sys


def options(argv):
    launch, dev_cli, viewer = 'gui', False, []
    args = iter(argv)
    for arg in args:
        if arg == '--dev-cli':
            dev_cli = True
        elif arg == '--launch':
            value = next(args, None)
            if value not in ('gui', 'shell'):
                raise ValueError('--launch requires gui or shell.')
            launch = value
        else:
            viewer.append(arg)
    if launch == 'shell' and viewer:
        raise ValueError('Viewer arguments cannot be used with --launch shell.')
    return launch, dev_cli, viewer


def main(argv=None):
    launch, dev_cli, viewer = options(sys.argv[1:] if argv is None else argv)
    project = Path(__file__).resolve().parent
    root = project.parent
    uv = shutil.which('uv')
    if uv is None:
        raise ValueError('uv is required')
    # The repository's single Python pin (uv reads it only inside a project directory).
    python_version = (root / '.python-version').read_text(encoding='utf-8').strip()
    common = ['--project', str(project), '--python', python_version, '--no-build-package', 'imgui-bundle']
    gui = ['--live-repo', str(root), *viewer]
    if launch == 'gui' and not dev_cli:
        # The locked dependencies, including the published ultrazohm_cli.
        return subprocess.call([uv, 'run', *common, 'uz-dataviewer', *gui])
    subprocess.run([uv, 'sync', *common, '--inexact'], check=True)
    scripts = project / '.venv' / ('Scripts' if os.name == 'nt' else 'bin')
    python = scripts / ('python.exe' if os.name == 'nt' else 'python')
    if dev_cli:
        # Build ../uz_cli and install it over the locked CLI for this start; the
        # next ordinary start restores the locked version.
        wheels = root / 'uz_cli' / 'target' / 'wheels-dev'
        shutil.rmtree(wheels, ignore_errors=True)
        subprocess.run([sys.executable, str(root / 'uz_cli' / 'tasks.py'), 'wheel', '--out', str(wheels)], check=True)
        built = sorted(wheels.glob('ultrazohm_cli-*.whl'))
        if len(built) != 1:
            raise ValueError(f'Expected one built wheel in {wheels}, found {len(built)}')
        subprocess.run([uv, 'pip', 'install', '--python', str(python), '--no-deps', '--reinstall', str(built[0])],
                       check=True)
    if launch == 'shell':
        return subprocess.call([str(python), '-m', 'uz_dataviewer.env_shell'])
    executable = scripts / ('uz-dataviewer.exe' if os.name == 'nt' else 'uz-dataviewer')
    return subprocess.call([str(executable), *gui])


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (ValueError, OSError, subprocess.CalledProcessError) as exc:
        print(str(exc), file=sys.stderr)
        raise SystemExit(1)
