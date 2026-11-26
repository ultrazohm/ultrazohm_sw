"""Package the standalone Windows CLI from a tested executable."""

import argparse
import zipfile
from pathlib import Path

from release_build import VERSION


def package(version, cli, output):
    if not VERSION.fullmatch(version):
        raise ValueError("Invalid release version")
    cli, output = Path(cli), Path(output)
    if not cli.is_file():
        raise FileNotFoundError(cli)
    output.mkdir(parents=True, exist_ok=True)
    with zipfile.ZipFile(
        output / f"ultrazohm-cli-{version}-windows-x86_64.zip",
        "w",
        zipfile.ZIP_DEFLATED,
    ) as archive:
        archive.write(cli, "ultrazohm-cli/ultrazohm-cli.exe")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    for name in ("version", "cli", "output"):
        parser.add_argument("--" + name, required=True)
    package(**vars(parser.parse_args()))
