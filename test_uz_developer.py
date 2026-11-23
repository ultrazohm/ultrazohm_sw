"""Fresh developer shells, task dispatch, cleanup and output concurrency."""

import contextlib
import inspect
import io
import json
import os
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

import uz
import uz_developer
import uz_venv
from test_uz import wheel
from uz_build import build_lock

ROOT = Path(__file__).resolve().parent


class DeveloperTest(unittest.TestCase):
    def test_dispatch_and_removed_commands(self):
        with patch.object(uz_developer, "run") as run:
            uz_developer.main(["build", "cli", "--out", "a path"])
            self.assertEqual(run.call_args.args[0][-3:], ["wheel", "--out", "a path"])
            uz_developer.main(["check", "viewer", "--gui-smoke"])
            self.assertEqual(run.call_args.args[0][-2:], ["check", "--gui-smoke"])
            for command in (
                "setup",
                "shell",
                "cli",
                "dataviewer",
                "status",
                "clear_venv",
            ):
                with (
                    contextlib.redirect_stderr(io.StringIO()),
                    self.assertRaises(SystemExit),
                ):
                    uz_developer.main([command])

    def test_build_lock_is_shared_across_processes_and_released(self):
        with tempfile.TemporaryDirectory() as directory:
            code = "from uz_build import build_lock; import sys;\nwith build_lock(sys.argv[1], 'cli'): print('acquired')"
            with build_lock(directory, "cli"):
                result = subprocess.run(
                    [sys.executable, "-c", code, directory],
                    capture_output=True,
                    text=True,
                )
                self.assertNotEqual(result.returncode, 0)
                self.assertIn("Another cli build", result.stderr)
                with build_lock(directory, "viewer"):
                    pass
            result = subprocess.run(
                [sys.executable, "-c", code, directory], capture_output=True, text=True
            )
            self.assertEqual(result.returncode, 0, result.stderr)

    def test_independent_shell_lifetimes_and_failure_cleanup(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / ".python-version").write_text(sys.executable)
            (root / ".venv").mkdir()
            sentinel = root / ".venv/preserve"
            sentinel.write_text("host")
            shells = []

            def run(command):
                if "--out" in command:
                    out = Path(command[-1])
                    out.mkdir()
                    (out / "ultrazohm_cli-0.1.0-test.whl").touch()
                if Path(command[-1]).name == "uz_shell.py":
                    location = Path(command[0]).parents[2]
                    shells.append(location)
                    if len(shells) == 1:
                        uz_venv.development_shell(root, run)
                        self.assertTrue(location.exists())
                    else:
                        self.assertNotEqual(shells[0], location)
                        self.assertTrue(shells[0].exists())

            uz_venv.development_shell(root, run)
            self.assertTrue(all(not p.exists() for p in shells))
            self.assertEqual(sentinel.read_text(), "host")
            touched = []

            def fail(command):
                touched.append(Path(command[-1]).parent)
                raise subprocess.CalledProcessError(7, command)

            with self.assertRaises(subprocess.CalledProcessError):
                uz_venv.development_shell(root, fail)
            self.assertFalse(touched[0].exists())

    @unittest.skipUnless(shutil.which("uv"), "uv needed")
    def test_real_local_install_and_cleanup_without_published_apps(self):
        with tempfile.TemporaryDirectory(prefix="uz local fixture ") as directory:
            root = Path(directory)
            (root / ".python-version").write_text(sys.executable)
            (root / "requirements.txt").write_text("shell-extra==1.0.0\n")
            packages = root / "packages"
            packages.mkdir()
            wheel(packages, "shell-extra", "1.0.0")
            # No published UltraZohm wheels exist in the index: local provenance is required.
            cli = root / "ultrazohm_cli"
            cli.mkdir()
            cli.joinpath("tasks.py").write_text(
                "import zipfile,sys\nfrom pathlib import Path\n"
                + inspect.getsource(wheel)
                + "\nout=Path(sys.argv[-1]); out.mkdir(); wheel(out,'ultrazohm-cli','0.1.0')\n"
            )
            viewer = root / "ultrazohm_dataviewer"
            viewer.mkdir()
            source = viewer / "src/ultrazohm_dataviewer"
            source.mkdir(parents=True)
            (source / "__init__.py").write_text('def main(): print("local viewer")\n')
            viewer.joinpath("pyproject.toml").write_text(
                '[build-system]\nrequires=[]\nbuild-backend="backend"\nbackend-path=["."]\n'
            )
            viewer.joinpath("backend.py").write_text(
                "import zipfile\nfrom pathlib import Path\n"
                + inspect.getsource(wheel)
                + """
def build_editable(wheel_directory, config_settings=None, metadata_directory=None):
    wheel(Path(wheel_directory), "ultrazohm-dataviewer", "0.1.0", ["ultrazohm-cli==0.1.0"])
    path = next(Path(wheel_directory).glob("*.whl"))
    with zipfile.ZipFile(path) as archive:
        entries = {n: archive.read(n) for n in archive.namelist() if not n.startswith("ultrazohm_dataviewer/")}
    entries["local-viewer.pth"] = str(Path(__file__).parent / "src").encode()
    with zipfile.ZipFile(path, "w") as archive:
        for n, data in entries.items(): archive.writestr(n, data)
    return path.name
"""
            )
            report = root / "report.json"
            (root / "uz_shell.py").write_text(
                "import json,sys,importlib.metadata as m,ultrazohm_dataviewer as v; from pathlib import Path; "
                f"Path({str(report)!r}).write_text(json.dumps([sys.prefix,v.__file__,"
                "m.version('ultrazohm-cli'),m.version('shell-extra')]))"
            )
            config = root / "uv.toml"
            config.write_text(
                "no-index = true\nfind-links = " + json.dumps([str(packages)]) + "\n"
            )
            env = {
                "UV_CONFIG_FILE": str(config),
                "UV_CACHE_DIR": str(root / "cache"),
                "UV_PYTHON_DOWNLOADS": "never",
            }
            real_run = uz.run

            def run(command):
                # Fixture has no lockfile. Exercise every actual build/install/shell step;
                # export itself is covered by the real project's locked build tasks.
                if command[:2] == ["uv", "export"]:
                    Path(command[-1]).write_text("")
                else:
                    real_run(command)

            with patch.dict(os.environ, env):
                uz_venv.development_shell(root, run)
            prefix, module, cli_version, extra = json.loads(report.read_text())
            self.assertFalse(Path(prefix).exists())
            self.assertEqual(Path(module).resolve(), (source / "__init__.py").resolve())
            self.assertEqual((cli_version, extra), ("0.1.0", "1.0.0"))
            self.assertFalse((root / ".venv").exists())


if __name__ == "__main__":
    unittest.main()
