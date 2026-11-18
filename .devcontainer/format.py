"""Run the pinned C formatter locally in the devcontainer or enter it from the host."""

import argparse
import os
from pathlib import Path
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
VERSION = "19.1.7"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("mode", choices=("format", "check"))
    parser.add_argument("path", help="repository-relative directory or file")
    args = parser.parse_args()
    scope = (ROOT / args.path).resolve()
    if not scope.is_relative_to(ROOT) or not scope.exists():
        parser.error("path must exist inside the repository")
    relative = scope.relative_to(ROOT).as_posix()

    inside = (os.environ.get("UZ_DEVCONTAINER") == "1" or Path("/.dockerenv").exists()
              or Path("/run/.containerenv").exists())
    if not inside:
        cli = shutil.which("devcontainer")
        command = [cli] if cli else ["npx", "--yes", "@devcontainers/cli@0.90.0"]
        if not cli and not shutil.which("npx"):
            parser.error("install the Dev Container CLI or Node.js/npx; Docker must also be running")
        # Keep a reusable tooling container separate from editor containers, whose
        # display/socket mounts may be unavailable in a native terminal or CI.
        workspace = ["--workspace-folder", str(ROOT),
                     "--id-label", f"devcontainer.local_folder={ROOT}",
                     "--id-label", "ultrazohm.tooling=format"]
        subprocess.run([*command, "up", *workspace, "--skip-post-create"], check=True)
        subprocess.run([*command, "exec", *workspace,
                        "python3", ".devcontainer/format.py", args.mode, relative], check=True)
        return

    formatter = shutil.which("clang-format")
    if not formatter:
        parser.error("clang-format is missing; rebuild the devcontainer to install the pinned formatter")
    version = subprocess.check_output([formatter, "--version"], text=True)
    if f"version {VERSION}" not in version:
        parser.error(f"expected clang-format {VERSION}; rebuild the devcontainer (found {version.strip()})")
    output = subprocess.check_output(
        ["git", "-c", f"safe.directory={ROOT}", "ls-files", "-z", "--cached", "--others",
         "--exclude-standard", "--", relative], cwd=ROOT)
    files = sorted({os.fsdecode(name) for name in output.split(b"\0") if name
                    and Path(os.fsdecode(name)).suffix in (".c", ".h")
                    and (ROOT / os.fsdecode(name)).is_file()})
    if not files:
        parser.error("no C/H files found in the selected scope")
    options = ["-i"] if args.mode == "format" else ["--dry-run", "--Werror"]
    # Root containers should create replacement files as the mounted repo owner.
    identity = {"user": ROOT.stat().st_uid, "group": ROOT.stat().st_gid} if os.geteuid() == 0 else {}
    # clang-format applies .clang-format-ignore to the selected files.
    for offset in range(0, len(files), 100):
        subprocess.run([formatter, "--style=file", *options, *files[offset:offset + 100]],
                       cwd=ROOT, check=True, **identity)
    print(f"Formatting {'applied' if args.mode == 'format' else 'checked'}: {relative} "
          f"(clang-format {VERSION}; generated/vendor exclusions apply)", flush=True)


if __name__ == "__main__":
    try:
        main()
    except subprocess.CalledProcessError as error:
        sys.exit(error.returncode or 1)
