"""Build and test tasks for uz_cli, identical on Linux, Windows and in CI.

Standard library only. Run from anywhere:

    python uz_cli/tasks.py install          build this checkout's CLI and install it as the ultrazohm_cli command
    python uz_cli/tasks.py check            formatting, clippy, Rust tests, integration tests
    python uz_cli/tasks.py debug-wheel      unoptimized wheel for tests into target/wheels-debug
    python uz_cli/tasks.py wheel            optimized wheel for this machine into target/wheels
    (with uv: uv run uz_cli/tasks.py TASK; on Linux: make -C uz_cli TASK)
    python uz_cli/tasks.py release-wheel    portable release wheel into target/wheels-release
    python uz_cli/tasks.py release-check    install that wheel in a fresh environment and run the integration tests
    python uz_cli/tasks.py version          release version for a CI run (GITHUB_* variables)
    python uz_cli/tasks.py stamp VERSION    write VERSION into pyproject.toml (wheel metadata)

The Python version comes from the repository's .python-version, which uv reads.
Set UZ_CLI_RELEASE_VERSION while building so the binary reports the same version.
"""
import argparse
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent
TARGET = HERE / "target"
WINDOWS = os.name == "nt"
# Oldest glibc supported by published Linux wheels; zig links against it from any host.
MANYLINUX = "manylinux_2_28"
STABLE_BRANCH = "main"
PRERELEASE_BRANCHES = ("develop", "feature/uz_cli_dataviewer_testing")


def run(*command, cwd=HERE, env=None):
    command = [str(part) for part in command]
    print("+", " ".join(command), flush=True)
    subprocess.run(command, cwd=cwd, env=env, check=True)


def maturin():
    """The installed maturin, or a uv-managed one (with zig for portable Linux wheels)."""
    if shutil.which("maturin"):
        return ["maturin"]
    return ["uv", "tool", "run", "--from", "maturin[zig]>=1.9,<2" if not WINDOWS else "maturin>=1.9,<2", "maturin"]


def venv_bin(venv, name):
    scripts = venv / ("Scripts" if WINDOWS else "bin")
    return scripts / (name + (".exe" if WINDOWS else ""))


def fresh_venv(venv, *packages):
    shutil.rmtree(venv, ignore_errors=True)
    run("uv", "venv", "--quiet", venv)
    python = venv_bin(venv, "python")
    run("uv", "pip", "install", "--quiet", "--python", python, *packages)
    return python


def single_wheel(directory):
    wheels = sorted(Path(directory).glob("ultrazohm_cli-*.whl"))
    if len(wheels) != 1:
        raise SystemExit(f"Expected exactly one wheel in {directory}, found {len(wheels)}")
    return wheels[0]


def integration(python, command=None):
    """The unittest suite, against the cargo binary or an installed console command."""
    env = os.environ.copy()
    if command is not None:
        env["UZ_CLI_BIN"] = str(command)
    run(python, "-m", "unittest", "discover", "-s", "uz_cli/tests", "-v", cwd=ROOT, env=env)


def debug_wheel(_args):
    """Unoptimized wheel for tests; reuses the debug build of cargo test."""
    wheels = TARGET / "wheels-debug"
    shutil.rmtree(wheels, ignore_errors=True)
    run(*maturin(), "build", "--locked", "--out", wheels)


def install(_args):
    """Build this checkout's CLI and install it as the ultrazohm_cli command (uv tool)."""
    out = TARGET / "wheels-install"
    shutil.rmtree(out, ignore_errors=True)
    run(*maturin(), "build", "--release", "--locked", "--out", out)
    python = (ROOT / ".python-version").read_text(encoding="utf-8").strip()
    run("uv", "tool", "install", "--force", "--python", python, single_wheel(out))


def check(args):
    run("cargo", "fmt", "--check")
    run("cargo", "clippy", "--all-targets", "--features", "python", "--locked", "--", "-D", "warnings")
    run("cargo", "test", "--locked")
    run("cargo", "build", "--locked")
    debug_wheel(args)
    python = fresh_venv(TARGET / "ci-venv", single_wheel(TARGET / "wheels-debug"), "polars", "packaging")
    # Once against the cargo-built executable, once against the wheel's console command.
    integration(python)
    integration(python, venv_bin(TARGET / "ci-venv", "ultrazohm_cli"))


def wheel(args):
    run(*maturin(), "build", "--release", "--locked", "--out", args.out or TARGET / "wheels")


def release_wheel(_args):
    output = TARGET / "wheels-release"
    shutil.rmtree(output, ignore_errors=True)
    portable = [] if WINDOWS else ["--zig", "--compatibility", MANYLINUX]
    run(*maturin(), "build", "--release", "--locked", *portable, "--out", output)


def release_check(args):
    built = single_wheel(args.wheel_dir or TARGET / "wheels-release")
    venv = TARGET / "release-venv"
    python = fresh_venv(venv, built, "polars", "packaging")
    integration(python, venv_bin(venv, "ultrazohm_cli"))


def release_version(base, branch, run_number):
    """One version per CI run: MAJOR.MINOR.<run>, with .dev0 outside main."""
    match = re.fullmatch(r"(\d+)\.(\d+)\.\d+", base)
    if not match:
        raise ValueError("pyproject.toml must contain a three-part base version")
    if run_number < 1:
        raise ValueError("invalid workflow run number")
    version = f"{match[1]}.{match[2]}.{run_number}"
    return version if branch == STABLE_BRANCH else version + ".dev0"


def version(_args):
    found = re.search(r'^version = "([^"]+)"$', (HERE / "pyproject.toml").read_text(encoding="utf-8"),
                      flags=re.MULTILINE)
    base = found[1] if found else ""
    branch = os.environ.get("GITHUB_REF_NAME", "")
    pushed = os.environ.get("GITHUB_EVENT_NAME") == "push"
    value = release_version(base, branch, int(os.environ["GITHUB_RUN_NUMBER"]))
    outputs = {"version": value, "tag": f"ultrazohm-v{value}",
               "publish": str(pushed and branch in (STABLE_BRANCH, *PRERELEASE_BRANCHES)).lower(),
               "prerelease": str(branch != STABLE_BRANCH).lower()}
    for key, item in outputs.items():
        print(f"{key}={item}")
    if path := os.environ.get("GITHUB_OUTPUT"):
        with open(path, "a", encoding="utf-8") as output:
            output.writelines(f"{key}={item}\n" for key, item in outputs.items())


def stamp(args):
    if not re.fullmatch(r"\d+\.\d+\.\d+(\.dev0)?", args.version):
        raise SystemExit(f"Invalid release version {args.version!r}")
    # Wheel metadata uses [project].version. Cargo.toml stays unchanged so
    # --locked builds still validate the checked-in lockfile.
    path = HERE / "pyproject.toml"
    text, count = re.subn(r'^version = "[^"]+"$', f'version = "{args.version}"',
                          path.read_text(encoding="utf-8"), count=1, flags=re.MULTILINE)
    if count != 1:
        raise SystemExit("pyproject.toml has no project version")
    path.write_text(text, encoding="utf-8")


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    tasks = parser.add_subparsers(dest="task", required=True)
    tasks.add_parser("install", help=install.__doc__).set_defaults(function=install)
    tasks.add_parser("check", help="Formatting, clippy, Rust tests and integration tests, as CI.").set_defaults(function=check)
    tasks.add_parser("debug-wheel", help="Unoptimized wheel for tests in target/wheels-debug.").set_defaults(function=debug_wheel)
    built = tasks.add_parser("wheel", help="Optimized wheel for this machine in target/wheels.")
    built.add_argument("--out", type=Path, help="output directory (default: target/wheels)")
    built.set_defaults(function=wheel)
    tasks.add_parser("release-wheel", help="Portable release wheel in target/wheels-release.").set_defaults(function=release_wheel)
    checked = tasks.add_parser("release-check", help="Integration tests against the installed release wheel.")
    checked.add_argument("--wheel-dir", type=Path, help="directory holding the wheel (default: target/wheels-release)")
    checked.set_defaults(function=release_check)
    tasks.add_parser("version", help="Release version for a CI run (GITHUB_* variables).").set_defaults(function=version)
    stamped = tasks.add_parser("stamp", help="Write VERSION into pyproject.toml.")
    stamped.add_argument("version")
    stamped.set_defaults(function=stamp)
    args = parser.parse_args()
    try:
        args.function(args)
    except subprocess.CalledProcessError as error:
        raise SystemExit(error.returncode or 1)


if __name__ == "__main__":
    main()
