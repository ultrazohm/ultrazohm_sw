"""Build, test and install ultrazohm_cli; the same tasks on Linux, Windows and in CI.

Standard library only. Run as ``./uz_developer cli TASK`` (``--help`` lists the
tasks). The Python version comes from the repository's .python-version. Set
UZ_CLI_RELEASE_VERSION while building so the binary reports the same version as
the wheel.
"""

import os
import re
import shutil
import sys
import tempfile
from functools import partial
from pathlib import Path

import tomllib

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent
TARGET = HERE / "target"
sys.path.insert(0, str(ROOT))
from uz_build import Task, single_wheel, venv_bin  # noqa: E402
from uz_build import run as build_run  # noqa: E402

WINDOWS = os.name == "nt"
# Oldest glibc supported by published Linux wheels; zig links against it from any host.
MANYLINUX = "manylinux_2_28"
STABLE_BRANCH = "main"
PRERELEASE_BRANCHES = ("develop", "feature/uz_cli_dataviewer_testing")
# Release patch numbers are GITHUB_RUN_NUMBER + this offset. Run numbers restart
# when the workflow file is renamed: raise the offset above the last published
# patch number in that case so versions keep increasing.
RUN_NUMBER_OFFSET = 0


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
    debug_wheel(args)
    with tempfile.TemporaryDirectory(prefix="uz-cli-test-") as directory:
        venv = Path(directory) / "environment"
        python = fresh_venv(
            venv, single_wheel(TARGET / "wheels-debug"), "polars", "packaging"
        )
        # The installed console command runs the same debug build as cargo test.
        integration(python, venv_bin(venv, "ultrazohm-cli"))


def release_wheel(args):
    sys.path.insert(0, str(HERE / "tools"))
    from release_build import staged_project

    if getattr(args, "out", None):
        output = args.out.resolve()
    else:
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
        raise ValueError("Cargo.toml must contain a three-part base version")
    if run_number < 1:
        raise ValueError("invalid workflow run number")
    version = f"{match[1]}.{match[2]}.{run_number + RUN_NUMBER_OFFSET}"
    return version if branch == STABLE_BRANCH else version + ".dev0"


def base_version():
    """The single source of the release base version: the crate version."""
    return tomllib.loads((HERE / "Cargo.toml").read_text(encoding="utf-8"))["package"][
        "version"
    ]


def version(_args):
    base = base_version()
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


ALWAYS = lambda args: True  # noqa: E731
LOCK = "cli"
TASKS = {
    "install": Task(
        install,
        "Build an optimized wheel of this checkout for this machine and install it with "
        "'uv tool install --force', replacing an ultrazohm-cli installed from PyPI until "
        "you reinstall that.",
        locked=ALWAYS,
    ),
    "lint": Task(lint, lint.__doc__),
    "format": Task(format_code, format_code.__doc__),
    "format-check": Task(format_check, format_check.__doc__),
    "check": Task(
        check,
        "Formatting, clippy, Rust tests, then a debug wheel installed into a temporary "
        "environment and the integration tests against the wheel's command.",
        locked=ALWAYS,
    ),
    "debug-wheel": Task(
        debug_wheel,
        "Unoptimized wheel for tests in target/wheels-debug.",
        lambda parser: parser.add_argument("--out", type=Path),
        locked=ALWAYS,
    ),
    "release-wheel": Task(
        release_wheel,
        "Portable release wheel in target/wheels-release: manylinux_2_28 on Linux "
        "(linked with zig), native on Windows.",
        lambda parser: parser.add_argument("--out", type=Path),
        locked=ALWAYS,
    ),
    "standalone": Task(
        standalone,
        "Build the Windows native CLI executable.",
        locked=ALWAYS,
    ),
    "release-check": Task(
        release_check,
        "Install the release wheel into a fresh environment and run the integration "
        "tests.",
        lambda parser: (
            parser.add_argument(
                "--standalone",
                action="store_true",
                help="also test the Windows executable built by the standalone task",
            ),
            parser.add_argument(
                "--wheel-dir",
                type=Path,
                help="directory holding the wheel (default: target/wheels-release)",
            ),
        ),
        locked=ALWAYS,
    ),
    "version": Task(
        version, "Print the release version for a CI run from the GITHUB_* variables."
    ),
}
