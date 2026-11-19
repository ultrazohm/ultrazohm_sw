"""Build, test and install ultrazohm_cli; the same tasks on Linux, Windows and in CI.

Standard library only. `./uz task cli help` lists the tasks;
`./uz task cli TASK --help` explains one. The Python version comes from the
repository's .python-version. Set UZ_CLI_RELEASE_VERSION while building so the
binary reports the same version as the wheel.
"""
import argparse
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path

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
    """Keep maturin and zig in the same tool environment, independent of the caller's Python."""
    python = (ROOT / ".python-version").read_text(encoding="utf-8").strip()
    return ["uv", "tool", "run", "--python", python, "--from",
            "maturin[zig]>=1.9,<2" if not WINDOWS else "maturin>=1.9,<2", "maturin"]


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
    run(python, "-m", "unittest", "discover", "-s", "ultrazohm_cli/tests", "-v", cwd=ROOT, env=env)


def debug_wheel(_args):
    """Unoptimized wheel for tests; reuses the debug build of cargo test."""
    wheels = TARGET / "wheels-debug"
    shutil.rmtree(wheels, ignore_errors=True)
    run(*maturin(), "build", "--locked", "--out", wheels)


def local_wheel():
    """Build a fresh optimized wheel, reusing Cargo build artifacts."""
    out = TARGET / "wheels-install"
    shutil.rmtree(out, ignore_errors=True)
    run(*maturin(), "build", "--release", "--locked", "--out", out)
    return single_wheel(out)


def install(_args):
    """Build this checkout's CLI and install it as the ultrazohm_cli command (uv tool)."""
    built = local_wheel()
    python = (ROOT / ".python-version").read_text(encoding="utf-8").strip()
    run("uv", "tool", "install", "--force", "--python", python, built)


def check(args):
    run("cargo", "fmt", "--check")
    run("cargo", "clippy", "--all-targets", "--features", "python", "--locked", "--", "-D", "warnings")
    run("cargo", "test", "--locked")
    run("cargo", "build", "--locked")
    debug_wheel(args)
    python = fresh_venv(TARGET / "ci-venv", single_wheel(TARGET / "wheels-debug"), "polars", "packaging")
    # Once against the cargo-built executable, once against the wheel's console command.
    integration(python)
    integration(python, venv_bin(TARGET / "ci-venv", "ultrazohm-cli"))


def wheel(args):
    # run() builds from HERE; resolve user paths before changing directory.
    output = args.out.resolve() if args.out is not None else TARGET / "wheels"
    run(*maturin(), "build", "--release", "--locked", "--out", output)


def release_wheel(_args):
    sys.path.insert(0, str(ROOT / "scripts"))
    from release_build import staged_project
    output = TARGET / "wheels-release"
    shutil.rmtree(output, ignore_errors=True)
    portable = [] if WINDOWS else ["--zig", "--compatibility", MANYLINUX]
    with staged_project(HERE, os.environ.get("UZ_CLI_RELEASE_VERSION")) as (stage, version):
        env = {**os.environ, "UZ_CLI_RELEASE_VERSION": version, "CARGO_TARGET_DIR": str(TARGET)}
        run(*maturin(), "build", "--release", "--locked", *portable, "--out", output,
            cwd=stage, env=env)


def standalone(_args):
    """Build the Windows native CLI with the same version as its wheel."""
    if not WINDOWS:
        raise SystemExit("Standalone downloads are Windows-only; use the Python wheel on Linux.")
    run("cargo", "build", "--release", "--locked", "--bin", "ultrazohm-cli")


def release_check(args):
    built = single_wheel(args.wheel_dir or TARGET / "wheels-release")
    venv = TARGET / "release-venv"
    python = fresh_venv(venv, built, "polars", "packaging")
    integration(python, venv_bin(venv, "ultrazohm-cli"))


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


def _invocation():
    prefix = ".\\uz.ps1" if WINDOWS else "./uz"
    return lambda task, args="": f"{prefix} task cli {task}" + (f" {args}" if args else "")


def overview():
    print("CLI build tasks: check, wheel, debug-wheel, release-wheel, release-check, version, standalone, install")
    print("Use ./uz shell to run both applications; ./uz task cli TASK --help for details.")


DESCRIPTIONS = {
    "standalone": "Build the Windows native CLI executable.",
    "install": "Build an optimized wheel of this checkout for this machine and install it with "
               "'uv tool install --force', replacing an ultrazohm_cli installed from PyPI until you "
               "reinstall that.",
    "check": "Formatting, clippy, Rust tests, then a debug wheel installed into target/ci-venv and "
             "the integration tests twice: against the cargo binary and the wheel's command.",
    "wheel": "Optimized wheel for this machine (not portable to older Linux systems).",
    "release-wheel": "Portable release wheel: manylinux_2_28 on Linux (linked with zig), native on Windows.",
    "release-check": "Install the release wheel into a fresh environment and run the integration tests.",
    "debug-wheel": "Unoptimized wheel for tests in target/wheels-debug.",
    "version": "Print the release version for a CI run from the GITHUB_* variables.",
}


def main(argv=None):
    call = _invocation()
    parser = argparse.ArgumentParser(prog=call("").strip(), add_help=False)
    tasks = parser.add_subparsers(dest="task")

    def add(name, function):
        task = tasks.add_parser(name, prog=call(name), description=DESCRIPTIONS[name])
        task.set_defaults(function=function)
        return task
    add("install", install)
    add("check", check)
    add("debug-wheel", debug_wheel)
    add("wheel", wheel).add_argument("--out", type=Path, help="output directory (default: target/wheels)")
    add("release-wheel", release_wheel)
    add("standalone", standalone)
    add("release-check", release_check).add_argument(
        "--wheel-dir", type=Path, help="directory holding the wheel (default: target/wheels-release)")
    add("version", version)
    argv = list(sys.argv[1:] if argv is None else argv)
    if not argv or argv[0] in ("-h", "--help", "help"):
        overview()
        return
    args = parser.parse_args(argv)
    try:
        args.function(args)
    except subprocess.CalledProcessError as error:
        raise SystemExit(error.returncode or 1)


if __name__ == "__main__":
    main()
