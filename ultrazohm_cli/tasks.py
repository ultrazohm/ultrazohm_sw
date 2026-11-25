"""Build, test and install ultrazohm_cli; the same tasks on Linux, Windows and in CI.

Standard library only. `./uz_developer task cli help` lists the tasks;
`./uz_developer task cli TASK --help` explains one. The Python version comes from the
repository's .python-version. Set UZ_CLI_RELEASE_VERSION while building so the
binary reports the same version as the wheel.
"""

import argparse
import os
import re
import shutil
import subprocess
import sys
import tempfile
from contextlib import nullcontext
from functools import partial
from pathlib import Path

import tomllib

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent
TARGET = HERE / "target"
sys.path.insert(0, str(ROOT))
from uz_build import build_lock, single_wheel, venv_bin  # noqa: E402
from uz_build import run as build_run  # noqa: E402

WINDOWS = os.name == "nt"
# Oldest glibc supported by published Linux wheels; zig links against it from any host.
MANYLINUX = "manylinux_2_28"
STABLE_BRANCH = "main"
PRERELEASE_BRANCHES = ("develop", "feature/uz_cli_dataviewer_testing")


run = partial(build_run, cwd=HERE)


def maturin():
    """Keep maturin and zig in the same tool environment, independent of the caller's Python."""
    python = (ROOT / ".python-version").read_text(encoding="utf-8").strip()
    return [
        "uv",
        "tool",
        "run",
        "--python",
        python,
        "--from",
        tomllib.loads((HERE / "pyproject.toml").read_text())["build-system"][
            "requires"
        ][0],
        "--with-requirements",
        ROOT / ".devcontainer" / "build-tools.txt",
        "maturin",
    ]


def fresh_venv(venv, *packages):
    run(
        "uv",
        "venv",
        "--quiet",
        "--python",
        (ROOT / ".python-version").read_text().strip(),
        venv,
    )
    python = venv_bin(venv, "python")
    run("uv", "pip", "install", "--quiet", "--python", python, *packages)
    return python


def integration(python, command=None):
    """The unittest suite, against the cargo binary or an installed console command."""
    env = os.environ.copy()
    if command is not None:
        env["UZ_CLI_BIN"] = str(command)
    run(
        python,
        "-m",
        "unittest",
        "discover",
        "-s",
        "ultrazohm_cli/tests",
        "-v",
        cwd=ROOT,
        env=env,
    )


def debug_wheel(args):
    """Unoptimized wheel for tests; reuses the debug build of cargo test."""
    wheels = (
        args.out.resolve() if getattr(args, "out", None) else TARGET / "wheels-debug"
    )
    if not getattr(args, "out", None):
        shutil.rmtree(wheels, ignore_errors=True)
    run(*maturin(), "build", "--locked", "--out", wheels)


def local_wheel():
    """Build a fresh optimized wheel, reusing Cargo build artifacts."""
    out = TARGET / "wheels-install"
    shutil.rmtree(out, ignore_errors=True)
    run(*maturin(), "build", "--release", "--locked", "--out", out)
    return single_wheel(out)


def install(_args):
    """Build this checkout's CLI and install it as the ultrazohm-cli command (uv tool)."""
    built = local_wheel()
    python = (ROOT / ".python-version").read_text(encoding="utf-8").strip()
    run("uv", "tool", "install", "--force", "--python", python, built)


def ruff(*arguments):
    """Run this project's pinned Ruff without installing application dependencies."""
    config = HERE / "pyproject.toml"
    settings = tomllib.loads(config.read_text(encoding="utf-8"))["tool"]["ruff"]
    run(
        "uv",
        "tool",
        "run",
        "--from",
        "ruff" + settings["required-version"],
        "ruff",
        *arguments,
        "--config",
        config,
        ".",
    )


def lint(_args):
    """Check this project's Python code without changing files."""
    ruff("check")


def format_code(_args):
    """Format this project's Python code in place (no lint fixes)."""
    ruff("format")


def format_check(_args):
    """Check this project's Python formatting without changing files."""
    ruff("format", "--check")


def check(args):
    lint(args)
    format_check(args)
    run("cargo", "fmt", "--check")
    run(
        "cargo",
        "clippy",
        "--all-targets",
        "--features",
        "python",
        "--locked",
        "--",
        "-D",
        "warnings",
    )
    run("cargo", "test", "--locked")
    run("cargo", "build", "--locked")
    debug_wheel(args)
    with tempfile.TemporaryDirectory(prefix="uz-cli-test-") as directory:
        venv = Path(directory) / "environment"
        python = fresh_venv(
            venv, single_wheel(TARGET / "wheels-debug"), "polars", "packaging"
        )
        # Once against cargo's executable, once against the installed wheel.
        integration(python)
        integration(python, venv_bin(venv, "ultrazohm-cli"))


def wheel(args):
    # run() builds from HERE; resolve user paths before changing directory.
    output = args.out.resolve() if args.out is not None else TARGET / "wheels"
    run(*maturin(), "build", "--release", "--locked", "--out", output)


def release_wheel(_args):
    sys.path.insert(0, str(HERE / "tools"))
    from release_build import staged_project

    output = TARGET / "wheels-release"
    shutil.rmtree(output, ignore_errors=True)
    portable = [] if WINDOWS else ["--zig", "--compatibility", MANYLINUX]
    with staged_project(HERE, os.environ.get("UZ_CLI_RELEASE_VERSION")) as (
        stage,
        version,
    ):
        env = {
            **os.environ,
            "UZ_CLI_RELEASE_VERSION": version,
            "CARGO_TARGET_DIR": str(TARGET),
        }
        run(
            *maturin(),
            "build",
            "--release",
            "--locked",
            *portable,
            "--out",
            output,
            cwd=stage,
            env=env,
        )


def standalone(_args):
    """Build the Windows native CLI with the same version as its wheel."""
    if not WINDOWS:
        raise SystemExit(
            "Standalone downloads are Windows-only; use the Python wheel on Linux."
        )
    run("cargo", "build", "--release", "--locked", "--bin", "ultrazohm-cli")


def release_check(args):
    built = single_wheel(args.wheel_dir or TARGET / "wheels-release")
    with tempfile.TemporaryDirectory(prefix="uz-cli-release-test-") as directory:
        venv = Path(directory) / "environment"
        python = fresh_venv(venv, built, "polars", "packaging")
        integration(python, venv_bin(venv, "ultrazohm-cli"))
        if args.standalone:
            integration(python, TARGET / "release" / "ultrazohm-cli.exe")


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
    found = re.search(
        r'^version = "([^"]+)"$',
        (HERE / "pyproject.toml").read_text(encoding="utf-8"),
        flags=re.MULTILINE,
    )
    base = found[1] if found else ""
    branch = os.environ.get("GITHUB_REF_NAME", "")
    event = os.environ.get("GITHUB_EVENT_NAME")
    pushed = event == "push"
    manual = (
        event == "workflow_dispatch"
        and os.environ.get("UZ_PUBLISH_PRERELEASE") == "true"
    )
    if manual and branch not in PRERELEASE_BRANCHES:
        raise ValueError("Manual publication is restricted to prerelease branches")
    value = release_version(
        base, branch if pushed else "validation", int(os.environ["GITHUB_RUN_NUMBER"])
    )
    outputs = {
        "version": value,
        "tag": f"ultrazohm-v{value}",
        "publish": str(
            (pushed and branch in (STABLE_BRANCH, "develop")) or manual
        ).lower(),
        "prerelease": str(not (pushed and branch == STABLE_BRANCH)).lower(),
    }
    for key, item in outputs.items():
        print(f"{key}={item}")
    if path := os.environ.get("GITHUB_OUTPUT"):
        with open(path, "a", encoding="utf-8") as output:
            output.writelines(f"{key}={item}\n" for key, item in outputs.items())


def _invocation():
    prefix = ".\\uz_developer.ps1" if WINDOWS else "./uz_developer"
    return lambda task, args="": (
        f"{prefix} task cli {task}" + (f" {args}" if args else "")
    )


def overview():
    print(
        "CLI build tasks: lint, format, format-check, check, wheel, debug-wheel, release-wheel, release-check, version, standalone, install"
    )
    print(
        "Use ./uz venv dev to run both applications; ./uz_developer task cli TASK --help for details."
    )


DESCRIPTIONS = {
    "lint": lint.__doc__,
    "format": format_code.__doc__,
    "format-check": format_check.__doc__,
    "standalone": "Build the Windows native CLI executable.",
    "install": "Build an optimized wheel of this checkout for this machine and install it with "
    "'uv tool install --force', replacing an ultrazohm-cli installed from PyPI until you "
    "reinstall that.",
    "check": "Formatting, clippy, Rust tests, then a debug wheel installed into a temporary environment and "
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
    add("lint", lint)
    add("format", format_code)
    add("format-check", format_check)
    add("check", check)
    add("debug-wheel", debug_wheel).add_argument("--out", type=Path)
    add("wheel", wheel).add_argument(
        "--out", type=Path, help="output directory (default: target/wheels)"
    )
    add("release-wheel", release_wheel)
    add("standalone", standalone)
    release_parser = add("release-check", release_check)
    release_parser.add_argument(
        "--standalone",
        action="store_true",
        help="also test the Windows executable built by the standalone task",
    )
    release_parser.add_argument(
        "--wheel-dir",
        type=Path,
        help="directory holding the wheel (default: target/wheels-release)",
    )
    add("version", version)
    argv = list(sys.argv[1:] if argv is None else argv)
    if not argv or argv[0] in ("-h", "--help", "help"):
        overview()
        return
    args = parser.parse_args(argv)
    try:
        lock = (
            build_lock(ROOT, "cli")
            if args.task
            in (
                "check",
                "wheel",
                "debug-wheel",
                "release-wheel",
                "release-check",
                "install",
                "standalone",
            )
            else nullcontext()
        )
        with lock:
            args.function(args)
    except RuntimeError as error:
        raise SystemExit(str(error)) from None
    except subprocess.CalledProcessError as error:
        raise SystemExit(error.returncode or 1) from None


if __name__ == "__main__":
    main()
