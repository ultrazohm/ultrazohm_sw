"""Shared developer launcher; the shell wrappers only bootstrap uv/Python."""
import os
from pathlib import Path
import shutil
import subprocess
import sys


def options(argv):
    launch, live, backend, viewer = 'gui', False, [], []
    args = iter(argv)
    for arg in args:
        if arg == '--use-live':
            live = True
        elif arg in ('--launch', '--live-channel', '--live-wheel'):
            value = next(args, None)
            if arg == '--launch':
                if value not in ('gui', 'shell'):
                    raise ValueError('--launch requires gui or shell.')
                launch = value
            elif arg == '--live-channel':
                if value not in ('stable', 'testing'):
                    raise ValueError('--live-channel requires stable or testing.')
                live = True
                backend += ['--channel', value]
            else:
                if value is None or not Path(value).is_file():
                    raise ValueError('--live-wheel requires a compatible ultrazohm wheel path.')
                live = True
                backend += ['--wheel', str(Path(value).resolve())]
        else:
            viewer.append(arg)
    if launch == 'shell' and viewer:
        raise ValueError('Viewer arguments cannot be used with --launch shell.')
    return launch, live, backend, viewer


def main(argv=None):
    launch, live, backend, viewer = options(sys.argv[1:] if argv is None else argv)
    project = Path(__file__).resolve().parent
    uv = shutil.which('uv')
    if uv is None:
        raise ValueError('uv is required')
    common = ['--project', str(project), '--python', '3.12', '--no-build-package', 'imgui-bundle']
    if not live and launch == 'gui':
        return subprocess.call([uv, 'run', *common, 'uz-dataviewer', *viewer])
    subprocess.run([uv, 'sync', *common, '--inexact'], check=True)
    scripts = project / '.venv' / ('Scripts' if os.name == 'nt' else 'bin')
    python = scripts / ('python.exe' if os.name == 'nt' else 'python')
    if live:
        # Reuse wheel selection/setup; do not sync again after the optional install.
        subprocess.run([sys.executable, str(project.parent / 'uz_cli' / 'setup_uv.py'),
                        '--python', '3.12', '--venv', str(project / '.venv'),
                        '--launch', 'none', '--no-examples', *backend], check=True)
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
