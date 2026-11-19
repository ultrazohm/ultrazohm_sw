"""Project environment setup regressions; no network or native builds."""

import importlib.util
import shutil
import subprocess
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

REPO = Path(__file__).resolve().parents[2]
spec = importlib.util.spec_from_file_location(
    "repository_tasks", REPO / "ultrazohm_dataviewer/tools/setup_env.py"
)
tasks = importlib.util.module_from_spec(spec)
spec.loader.exec_module(tasks)


class SetupTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix="uz setup ")
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        for name in (
            ".python-version",
            "ultrazohm_dataviewer/tasks.py",
            "ultrazohm_dataviewer/tools/setup_env.py",
            "ultrazohm_dataviewer/pyproject.toml",
            "ultrazohm_dataviewer/uv.lock",
        ):
            target = self.root / name
            target.parent.mkdir(parents=True, exist_ok=True)
            shutil.copyfile(REPO / name, target)
        self.calls = []
        for patcher in (
            patch.object(tasks, "ROOT", self.root),
            patch.object(tasks, "run", side_effect=self.record),
            patch.object(tasks.subprocess, "check_output", return_value="{}"),
        ):
            patcher.start()
            self.addCleanup(patcher.stop)

    def record(self, *command, **kwargs):
        self.calls.append(command)
        if "--out" in command:
            Path(
                command[command.index("--out") + 1], "ultrazohm_cli-0.1.0-test.whl"
            ).touch()
        if command[:2] == ("uv", "venv"):
            tasks.scripts().mkdir(parents=True, exist_ok=True)
        if command[:3] == ("uv", "pip", "install"):
            for name in ("python", "ultrazohm-cli", "ultrazohm-dataviewer"):
                tasks.executable(name).touch()

    def test_all_installation_sources(self):
        for source in tasks.SOURCES:
            for app in ("viewer",):
                with self.subTest(source=source, app=app):
                    self.calls.clear()
                    tasks.setup(source)
                    install = next(
                        c for c in self.calls if c[:3] == ("uv", "pip", "install")
                    )
                    if source == "local":
                        self.assertTrue(any(str(c).endswith(".whl") for c in install))
                        self.assertEqual("--editable" in install, app == "viewer")
                        self.assertIn("--no-sources", install)
                        self.assertNotIn("--no-build-package", install)
                    else:
                        self.assertEqual(
                            install[-1],
                            "ultrazohm-cli" if app == "cli" else "ultrazohm-dataviewer",
                        )
                        self.assertNotIn("--editable", install)
                        self.assertEqual(
                            install[install.index("--prerelease") + 1],
                            "allow" if source == "prerelease" else "disallow",
                        )
                    self.assertTrue(
                        any(c[:3] == ("uv", "pip", "check") for c in self.calls)
                    )
                    state = tasks.saved_setup()
                    self.assertEqual((state["source"], state["app"]), (source, app))
                    self.assertIn("fingerprint", state)

    def test_shell_reuses_completed_setup_and_refreshes_missing_command(self):
        tasks.setup("stable")
        self.calls.clear()
        tasks.setup(reuse=True)
        self.assertEqual(self.calls, [])
        tasks.executable("ultrazohm-cli").unlink()
        tasks.setup(reuse=True)
        self.assertTrue(self.calls)

    def test_switch_recreates_environment(self):
        tasks.setup("local")
        self.calls.clear()
        tasks.setup("stable")
        self.assertTrue(any(c[:3] == ("uv", "venv", "--clear") for c in self.calls))
        self.assertEqual(tasks.saved_setup()["app"], "viewer")

    def test_failure_is_not_marked_ready(self):
        tasks.setup("stable")
        original = self.record

        def failing(*command, **kwargs):
            if command[:3] == ("uv", "pip", "install"):
                raise subprocess.CalledProcessError(1, command)
            original(*command, **kwargs)

        with patch.object(tasks, "run", side_effect=failing):
            with self.assertRaises(subprocess.CalledProcessError):
                tasks.setup("prerelease")
        self.assertNotIn("fingerprint", tasks.saved_setup())
