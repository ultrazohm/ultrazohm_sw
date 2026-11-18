"""Open an interactive shell in the launcher's virtual environment, without a GUI."""
import os
from pathlib import Path
import shlex
import shutil
import subprocess
import sys
import tempfile


def main():
    venv = Path(sys.prefix)
    if sys.prefix == sys.base_prefix:
        raise RuntimeError('Launch this module using the target virtual environment')
    scripts = venv / ('Scripts' if os.name == 'nt' else 'bin')
    rc_path = None
    if os.name == 'nt':
        shell = shutil.which('pwsh') or shutil.which('powershell')
        if not shell:
            raise RuntimeError('PowerShell is required to open the environment shell')
        activate = str(scripts / 'Activate.ps1').replace("'", "''")
        command = [shell, '-NoExit', '-Command', f". '{activate}'"]
    else:
        shell = shutil.which('bash')
        if not shell:
            raise RuntimeError('Bash is required to open the environment shell')
        with tempfile.NamedTemporaryFile(mode='w', suffix='.bashrc', delete=False) as rc:
            rc.write('if [ -f "$HOME/.bashrc" ]; then . "$HOME/.bashrc"; fi\n')
            rc.write('source ' + shlex.quote(str(scripts / 'activate')) + '\n')
            rc_path = Path(rc.name)
        command = [shell, '--noprofile', '--rcfile', str(rc_path), '-i']
    # Activation sets PATH itself, allowing deactivate to restore the original.
    env = os.environ.copy()
    env.pop('VIRTUAL_ENV', None)
    print('Opening activated environment shell. Use deactivate to deactivate; exit to return.', flush=True)
    try:
        child = subprocess.Popen(command, env=env)
        while True:
            try:
                return child.wait()
            except KeyboardInterrupt:
                continue  # The interactive shell handles Ctrl-C.
    finally:
        if rc_path is not None:
            rc_path.unlink(missing_ok=True)


if __name__ == '__main__':
    raise SystemExit(main())
