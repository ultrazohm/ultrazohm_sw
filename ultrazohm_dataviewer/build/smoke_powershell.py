"""Exercise the shipped wrapper through both supported PowerShell hosts."""

import os
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path


def main():
    wrapper = Path(sys.argv[1]).resolve(strict=True)
    if sys.platform != "win32":
        raise SystemExit("PowerShell bundle smoke tests require Windows")
    for name in ("powershell", "pwsh"):
        shell = shutil.which(name)
        if not shell:
            raise RuntimeError(f"{name} is required for Windows release checks")
        # Use a parent script to verify return to the calling shell, rather
        # than only testing a new PowerShell process's exit status.
        with tempfile.TemporaryDirectory(prefix="viewer wrapper test ") as directory:
            script = Path(directory) / "parent.ps1"
            script.write_text(
                """$ErrorActionPreference = 'Continue'
& $env:VIEWER_WRAPPER @args
$result = $LASTEXITCODE
[Console]::Error.WriteLine("WRAPPER_RETURNED:$result")
exit $result
""",
                encoding="utf-8",
            )
            for args, success, expected in [
                (["--help"], True, "usage:"),
                (["--version"], True, "."),
                (["not a command with spaces"], False, ""),
            ]:
                result = subprocess.run(
                    [
                        shell,
                        "-NoProfile",
                        "-ExecutionPolicy",
                        "Bypass",
                        "-File",
                        str(script),
                        *args,
                    ],
                    cwd=directory,
                    stdin=subprocess.DEVNULL,
                    capture_output=True,
                    timeout=30,
                    env={**os.environ, "VIEWER_WRAPPER": str(wrapper)},
                )
                assert (result.returncode == 0) == success, (name, args, result)
                assert (
                    f"WRAPPER_RETURNED:{result.returncode}".encode() in result.stderr
                ), result
                assert expected.encode() in result.stdout, result
                if not success:
                    assert b"not a command with spaces" in result.stderr, result
    print(
        "PowerShell 5.1 and 7 wrapper output, arguments, waiting, and exit status passed."
    )


if __name__ == "__main__":
    main()
