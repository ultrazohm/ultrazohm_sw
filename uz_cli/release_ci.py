"""Small cross-platform helpers for the CLI release workflow."""
import argparse
import hashlib
import os
from pathlib import Path
import re
import subprocess
import sys

from wheel_releases import TAG_PREFIXES, TESTING_BRANCH


def release_metadata(branch, base, run, attempt):
    if branch not in ("main", TESTING_BRANCH):
        raise ValueError(f"CLI publishing is not allowed from {branch}")
    if not re.fullmatch(r"\d+\.\d+\.\d+", base):
        raise ValueError("pyproject.toml must contain a three-part base release version")
    if run < 1 or not 1 <= attempt < 1000:
        raise ValueError("Invalid workflow run number/attempt")
    channel = "stable" if branch == "main" else "testing"
    suffix = "post" if channel == "stable" else "dev"
    version = f"{base}.{suffix}{run * 1000 + attempt}"
    return {"version": version, "channel": channel, "tag": TAG_PREFIXES[channel] + version}


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("action", choices=["metadata", "version", "install", "checksums"])
    parser.add_argument("value", nargs="?")
    args = parser.parse_args()
    root = Path(__file__).resolve().parent
    if args.action == "metadata":
        import tomllib
        base = tomllib.loads((root / "pyproject.toml").read_text())["project"]["version"]
        metadata = release_metadata(os.environ["GITHUB_REF_NAME"], base,
                                    int(os.environ["GITHUB_RUN_NUMBER"]), int(os.environ["GITHUB_RUN_ATTEMPT"]))
        with open(os.environ["GITHUB_OUTPUT"], "a") as output:
            for key, value in metadata.items():
                print(f"{key}={value}", file=output)
    elif args.action == "version":
        if not args.value or not re.fullmatch(r"\d+\.\d+\.\d+\.(post|dev)\d+", args.value):
            raise ValueError("Invalid release wheel version")
        # Wheel metadata uses [project].version. Leave Cargo.toml/Cargo.lock
        # unchanged so --locked builds still validate the checked-in lockfile.
        path = root / "pyproject.toml"
        text, count = re.subn(r'^version = "[^"]+"$', f'version = "{args.value}"',
                             path.read_text(), count=1, flags=re.MULTILINE)
        if count != 1:
            raise ValueError("Missing project version")
        path.write_text(text)
    elif args.action == "install":
        wheels = list(Path(args.value).glob("ultrazohm-*.whl"))
        if len(wheels) != 1:
            raise ValueError("Expected exactly one platform wheel")
        subprocess.run([sys.executable, "-m", "pip", "install", "--only-binary", ":all:",
                        "--force-reinstall", str(wheels[0]), "polars", "packaging"], check=True)
    else:
        directory = Path(args.value)
        wheels = sorted(directory.glob("ultrazohm-*.whl"))
        if len(wheels) != 2 or not any("win_amd64" in p.name for p in wheels) or not any("manylinux_2_28_x86_64" in p.name for p in wheels):
            raise ValueError("Release requires both Windows x86-64 and manylinux_2_28 x86-64 wheels")
        with (directory / "SHA256SUMS").open("w", newline="\n") as output:
            for wheel in wheels:
                print(f"{hashlib.sha256(wheel.read_bytes()).hexdigest()}  {wheel.name}", file=output)


if __name__ == "__main__":
    main()
