"""Local desktop bundles use a fresh optimized CLI wheel unless supplied one."""

import argparse
import importlib.util
import zipfile
from pathlib import Path


def tasks():
    path = Path(__file__).resolve().parents[1] / "tasks.py"
    spec = importlib.util.spec_from_file_location("viewer_build_tasks", path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def test_bundle_builds_release_wheel_in_isolated_directory(monkeypatch, tmp_path):
    module = tasks()
    builds, calls = [], []

    def build(*args):
        # Resolve while the directory exists: Windows may supply its 8.3 alias.
        builds.append(Path(args[2]).resolve())
        assert args[:2] == ("wheel", "--out")
        path = Path(args[2]) / "ultrazohm_cli-0.1.0-test.whl"
        with zipfile.ZipFile(path, "w") as archive:
            archive.writestr("test.dist-info/METADATA", "Version: 0.1.0\n")

    monkeypatch.setattr(module, "cli_tasks", build)
    monkeypatch.setattr(module, "run", lambda *args, **kwargs: calls.append(args))
    module.install_packages(
        tmp_path / "python",
        argparse.Namespace(cli_wheel=None, viewer_wheel=tmp_path / "viewer.whl"),
        release=True,
    )
    assert len(builds) == 1
    assert not builds[0].exists()
    install = next(c for c in calls if c[:3] == ("uv", "pip", "install"))
    assert Path(install[-2]).parent == builds[0]


def test_bundle_selects_release_install(monkeypatch):
    module = tasks()
    installs = []
    monkeypatch.setattr(module.shutil, "rmtree", lambda *args, **kwargs: None)
    monkeypatch.setattr(module.shutil, "copy2", lambda *args, **kwargs: None)
    monkeypatch.setattr(module, "WINDOWS", True)
    monkeypatch.setattr(module, "sync", lambda venv: Path("python"))
    monkeypatch.setattr(module, "run", lambda *args, **kwargs: None)
    monkeypatch.setattr(
        module,
        "install_packages",
        lambda python, args, **kwargs: installs.append(kwargs),
    )
    module.bundle(argparse.Namespace(cli_wheel=None, viewer_wheel=None))
    assert installs == [{"release": True}]
