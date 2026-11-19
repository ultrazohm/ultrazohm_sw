"""Test the extracted Windows downloads from paths containing spaces."""

import argparse
import subprocess
import sys
import tempfile
import zipfile
from pathlib import Path


def smoke(directory, version):
    if sys.platform != "win32":
        raise RuntimeError("Windows archives must be tested on Windows")
    archives = Path(directory).resolve()
    for name in ("ultrazohm-cli",):
        archive = archives / f"{name}-{version}-windows-x86_64.zip"
        with tempfile.TemporaryDirectory(
            prefix="UltraZohm extracted release "
        ) as directory:
            with zipfile.ZipFile(archive) as package:
                package.extractall(directory)
            application = Path(directory) / name
            cli = application / "ultrazohm-cli.exe"
            output = subprocess.check_output(
                [str(cli), "--version"], cwd=directory, text=True, timeout=30
            )
            if output.strip() != f"ultrazohm-cli {version}":
                raise RuntimeError(f"Unexpected standalone CLI version: {output!r}")
    print("Extracted CLI Windows archive passed.")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("directory")
    parser.add_argument("version")
    args = parser.parse_args()
    smoke(args.directory, args.version)
