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
        argparse.Namespace(cli_wheel=None, dataviewer_wheel=tmp_path / "viewer.whl"),
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
    module.bundle(argparse.Namespace(cli_wheel=None, dataviewer_wheel=None))
    assert installs == [{"release": True}]


def test_test_environment_is_private_and_lives_through_gui_smoke(monkeypatch):
    module = tasks()
    environments, calls = [], []

    def sync(venv):
        assert venv.parent.is_dir()
        environments.append(venv)
        return venv / "python"

    def run(*command, **kwargs):
        assert environments[-1].parent.is_dir()
        calls.append(command)

    monkeypatch.setattr(module, "sync", sync)
    monkeypatch.setattr(module, "install_packages", lambda *args: None)
    monkeypatch.setattr(module, "run", run)
    for _ in range(2):
        module.test(argparse.Namespace(gui_smoke=True))
        assert not environments[-1].parent.exists()
    assert environments[0] != environments[1]
    assert calls[1][-1] == module.HERE / "build/smoke_gui.py"
    assert calls[0][0] in calls[1]
    if module.sys.platform == "linux" and not module.os.environ.get("DISPLAY"):
        assert calls[1][:2] == ("xvfb-run", "-a")
