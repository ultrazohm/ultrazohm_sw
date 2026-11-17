"""Shared developer launcher; the shell wrappers only bootstrap uv/Python."""
import os
from pathlib import Path
import shutil
import subprocess
import sys


def options(argv):
    launch, live, wheel, viewer = 'gui', False, None, []
    args = iter(argv)
    for arg in args:
        if arg == '--use-live':
            live = True
        elif arg in ('--launch', '--live-wheel'):
            value = next(args, None)
            if arg == '--launch':
                if value not in ('gui', 'shell'):
                    raise ValueError('--launch requires gui or shell.')
                launch = value
            else:
                if value is None or not Path(value).is_file():
                    raise ValueError('--live-wheel requires a compatible ultrazohm_cli wheel path.')
                live, wheel = True, str(Path(value).resolve())
        else:
            viewer.append(arg)
    if launch == 'shell' and viewer:
        raise ValueError('Viewer arguments cannot be used with --launch shell.')
    return launch, live, wheel, viewer


def main(argv=None):
    launch, live, wheel, viewer = options(sys.argv[1:] if argv is None else argv)
    project = Path(__file__).resolve().parent
    uv = shutil.which('uv')
    if uv is None:
        raise ValueError('uv is required')
    # The repository's single Python pin (uv reads it only inside a project directory).
    python_version = (project.parent / '.python-version').read_text(encoding='utf-8').strip()
    common = ['--project', str(project), '--python', python_version, '--no-build-package', 'imgui-bundle']
    if not live and launch == 'gui':
        return subprocess.call([uv, 'run', *common, 'uz-dataviewer', *viewer])
    # Live mode installs the CLI version locked in uv.lock (the "live" extra).
    subprocess.run([uv, 'sync', *common, *(['--extra', 'live'] if live else []), '--inexact'], check=True)
    scripts = project / '.venv' / ('Scripts' if os.name == 'nt' else 'bin')
    python = scripts / ('python.exe' if os.name == 'nt' else 'python')
    if wheel:
        # An exact wheel, for example from a branch build, replaces the locked CLI.
        subprocess.run([uv, 'pip', 'install', '--python', str(python), '--no-deps', '--reinstall', wheel],
                       check=True)
    if live:
        subprocess.run([str(python), '-m', 'uz_dataviewer.check_live'], check=True)
    if launch == 'shell':
        return subprocess.call([str(python), '-m', 'uz_dataviewer.env_shell'])
    executable = scripts / ('uz-dataviewer.exe' if os.name == 'nt' else 'uz-dataviewer')
    return subprocess.call([str(executable), '--use-live', '--live-repo', str(project.parent), *viewer])


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (ValueError, OSError, subprocess.CalledProcessError) as exc:
        print(str(exc), file=sys.stderr)
        raise SystemExit(1)
