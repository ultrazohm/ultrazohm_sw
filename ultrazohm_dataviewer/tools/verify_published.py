"""Verify the published viewer in clean Python and uv tool environments."""

import argparse
import os
import subprocess
import tempfile
import time
from pathlib import Path


def verify_tools(root, version, index_args=None):
    """Check uvx and persistent tools without touching the runner's installed tools."""
    index_args = index_args or ["--default-index", "https://pypi.org/simple"]
    package = "ultrazohm-dataviewer"
    tool_root = root / f"tools-{package}"
    bin_dir = tool_root / "bin"
    env = {
        **os.environ,
        "UV_TOOL_DIR": str(tool_root / "environments"),
        "UV_TOOL_BIN_DIR": str(bin_dir),
    }
    options = ["--python", "3.12", "--no-build", *index_args]
    # uvx is the alias for `uv tool run`.
    output = subprocess.check_output(
        [
            "uv",
            "tool",
            "run",
            "--isolated",
            *options,
            f"{package}=={version}",
            "--version",
        ],
        cwd=root,
        env=env,
        text=True,
    )
    if version not in output.split():
        raise RuntimeError(f"uvx {package} reported {output!r}")
    names = ["ultrazohm-cli", package]
    extra = ["--with-executables-from", "ultrazohm-cli"]
    subprocess.run(
        ["uv", "tool", "install", *options, *extra, f"{package}=={version}"],
        cwd=root,
        env=env,
        check=True,
    )
    for name in names:
        command = bin_dir / (name + (".exe" if os.name == "nt" else ""))
        output = subprocess.check_output(
            [str(command), "--version"], cwd=root, env=env, text=True
        )
        if version not in output.split():
            raise RuntimeError(f"Installed tool {name} reported {output!r}")


def verify(version):
    from release_build import VERSION

    if not VERSION.fullmatch(version):
        raise ValueError("Invalid release version")
    with tempfile.TemporaryDirectory(prefix="ultrazohm-pypi-") as directory:
        root = Path(directory)
        package = "ultrazohm-dataviewer"
        venv = root / package
        subprocess.run(["uv", "venv", "--python", "3.12", str(venv)], check=True)
        scripts = venv / ("Scripts" if os.name == "nt" else "bin")
        python = scripts / ("python.exe" if os.name == "nt" else "python")
        command = [
            "uv",
            "pip",
            "install",
            "--python",
            str(python),
            "--index-url",
            "https://pypi.org/simple",
            "--only-binary",
            ":all:",
            "--refresh",
            f"{package}=={version}",
        ]
        for attempt in range(12):
            result = subprocess.run(command, cwd=root, check=False)
            if result.returncode == 0:
                break
            if attempt == 11:
                result.check_returncode()
            time.sleep(10)
        subprocess.run(["uv", "pip", "check", "--python", str(python)], check=True)
        names = ["ultrazohm-cli", "ultrazohm-dataviewer"]
        for name in names:
            exe = scripts / (name + (".exe" if os.name == "nt" else ""))
            reported = subprocess.check_output(
                [str(exe), "--version"], cwd=root, text=True
            )
            if version not in reported.split():
                raise RuntimeError(f"{name} reports {reported!r}, expected {version}")
        code = (
            "import importlib.metadata as m; from ultrazohm_cli import Acquisition, Client; "
            f'assert m.version("ultrazohm-cli") == {version!r}; '
        )
        code += f"from ultrazohm_dataviewer import Client, __version__; assert __version__ == {version!r}"
        subprocess.run([str(python), "-c", code], cwd=root, check=True)
        verify_tools(root, version)
    print(
        f"PyPI release {version}: clean Python, uvx, and persistent tool installations verified."
    )


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("version")
    verify(parser.parse_args().version)
