"""Shared source/frozen worker entry points; no GUI imports in workers."""
import os
import sys


def command(task, *args):
    if task not in ('cli', 'script'):
        raise ValueError(f'Unknown worker task: {task}')
    prefix = ([sys.executable, '--internal-worker'] if getattr(sys, 'frozen', False)
              else [sys.executable, '-u', '-m', 'uz_dataviewer.process_launcher'])
    return [*prefix, task, *map(str, args)]


def main(argv=None):
    args = list(sys.argv[1:] if argv is None else argv)
    task = args.pop(0)
    # Windowed Windows executables do not initialize Python standard streams.
    # Explicit redirected handles from the parent are used when available.
    for name, fd, mode in [('stdin', 0, 'r'), ('stdout', 1, 'w'), ('stderr', 2, 'w')]:
        if getattr(sys, name) is None:
            try:
                stream = os.fdopen(os.dup(fd), mode, encoding='utf-8', buffering=1)
            except OSError:
                stream = open(os.devnull, mode, encoding='utf-8')
            setattr(sys, name, stream)
    if task == 'cli':
        # External tools must not inherit frozen-library search paths.
        if getattr(sys, 'frozen', False):
            from pathlib import Path
            os.environ['UZ_CLI_TCL_DIR'] = str(Path(sys._MEIPASS) / 'tcl_scripts')
            if os.name == 'nt':
                import ctypes
                ctypes.windll.kernel32.SetDllDirectoryW(None)
            elif 'LD_LIBRARY_PATH_ORIG' in os.environ:
                os.environ['LD_LIBRARY_PATH'] = os.environ['LD_LIBRARY_PATH_ORIG']
            else:
                os.environ.pop('LD_LIBRARY_PATH', None)
        from ultrazohm.cli import main as cli_main
        sys.argv = ['ultrazohm', *args]
        return cli_main()
    if task == 'script':
        from .script_worker import main as script_main
        sys.argv = ['script_worker', *args]
        return script_main()
    raise ValueError(f'Unknown worker task: {task}')


if __name__ == '__main__':
    raise SystemExit(main())
