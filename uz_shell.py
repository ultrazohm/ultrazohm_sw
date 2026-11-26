"""Open an interactive shell in the launcher's virtual environment, without a GUI."""

import os
import shlex
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path


# Readline needs \[ / \] around ANSI sequences to keep cursor positioning correct.
# Set this before activation so the environment prefix and deactivate still work.
PRIVATE_BASH_STARTUP = r"""
PS1='\u@\h:\w\$ '
if [[ -t 1 && -n ${TERM:-} && ${TERM} != dumb && -z ${NO_COLOR:-} ]]; then
    PS1='\[\e[32m\]\u@\h\[\e[0m\]:\[\e[34m\]\w\[\e[0m\]\$ '
    alias ls='ls --color=auto'
fi
"""


def shell():
    venv = Path(sys.prefix)
    if sys.prefix == sys.base_prefix:
        raise RuntimeError("Launch this module using the target virtual environment")
    scripts = venv / ("Scripts" if os.name == "nt" else "bin")
    rc_path = None
    private_dir = os.environ.get("UZ_PRIVATE_SHELL_DIR")
    if private_dir:
        Path(private_dir).mkdir(parents=True, exist_ok=True)
    if os.name == "nt":
        shell = shutil.which("pwsh") or shutil.which("powershell")
        if not shell:
            raise RuntimeError("PowerShell is required to open the environment shell")
        activate = str(scripts / "Activate.ps1").replace("'", "''")
        if private_dir:
            history = str(Path(private_dir) / "powershell_history.txt").replace("'", "''")
            command = [
                shell, "-NoProfile", "-ExecutionPolicy", "Bypass", "-NoExit", "-Command",
                "if (Get-Module -ListAvailable PSReadLine) { "
                "Import-Module PSReadLine; "
                f"Set-PSReadLineOption -HistorySavePath '{history}' }}; . '{activate}'",
            ]
        else:
            command = [shell, "-NoExit", "-Command", f". '{activate}'"]
    else:
        shell = shutil.which("bash")
        if not shell:
            raise RuntimeError("Bash is required to open the environment shell")
        with tempfile.NamedTemporaryFile(
            mode="w", suffix=".bashrc", delete=False, dir=private_dir
        ) as rc:
            if private_dir:
                rc.write(PRIVATE_BASH_STARTUP)
            else:
                rc.write('if [ -f "$HOME/.bashrc" ]; then . "$HOME/.bashrc"; fi\n')
            rc.write("source " + shlex.quote(str(scripts / "activate")) + "\n")
            rc_path = Path(rc.name)
        command = [shell, "--noprofile", "--rcfile", str(rc_path), "-i"]
    # Activation sets PATH itself, allowing deactivate to restore the original.
    env = os.environ.copy()
    env.pop("VIRTUAL_ENV", None)
    if private_dir and os.name != "nt":
        env["HISTFILE"] = str(Path(private_dir) / "bash_history")
    print(
        "Opening activated environment shell. Use deactivate to deactivate; exit to return.",
        flush=True,
    )
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


if __name__ == "__main__":
    raise SystemExit(shell())
