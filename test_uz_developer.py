"""Local setup, non-mutating launch, rollback and concurrent usage tests."""

import contextlib
import io
import json
import os
import shutil
import subprocess
import sys
import tempfile
import time
import unittest
from pathlib import Path
from unittest.mock import patch

import uz_developer as developer
import uz_developer_environment as environment
from uz_environment import environment_lock


class DeveloperTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix="uz development ")
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        (self.root / ".python-version").write_text(sys.executable)
        for patcher in (
            patch.object(developer, "ROOT", self.root),
            patch.object(environment, "ROOT", self.root),
            patch.dict(os.environ, {"UZ_DEV_CONTAINER": "0"}),
        ):
            patcher.start()
            self.addCleanup(patcher.stop)

    def installed(self):
        for name in ("python", "ultrazohm-cli", "ultrazohm-dataviewer"):
            path = environment.executable(name)
            path.parent.mkdir(parents=True, exist_ok=True)
            path.touch()
        (self.root / ".venv/.uz-setup.json").write_text(
            json.dumps(
                {
                    "source": "local",
                    "app": "viewer",
                    "context": {"root": str(self.root), "platform": sys.platform},
                }
            )
        )

    def test_launches_never_install_and_forward_arguments(self):
        self.installed()
        with (
            patch.object(environment, "setup") as setup,
            patch.object(environment.subprocess, "run"),
            patch.object(environment, "run") as run,
        ):
            for app in ("cli", "dataviewer"):
                developer.main([app, "--", "--endpoint", "127.0.0.1:19742"])
                run.assert_called_with(
                    environment.executable(f"ultrazohm-{app}"),
                    "--endpoint",
                    "127.0.0.1:19742",
                )
            developer.main(["shell"])
            run.assert_called_with(
                environment.executable("python"), self.root / "uz_shell.py"
            )
            setup.assert_not_called()

    def test_missing_or_foreign_environment_never_rebuilds(self):
        for foreign in (False, True):
            if foreign:
                self.installed()
                marker = self.root / ".venv/.uz-setup.json"
                state = json.loads(marker.read_text())
                state["context"]["platform"] = "foreign"
                marker.write_text(json.dumps(state))
            with (
                patch.object(environment, "setup") as setup,
                patch.object(environment, "run") as run,
                contextlib.redirect_stderr(io.StringIO()),
                self.assertRaises(SystemExit),
            ):
                developer.main(["cli"])
            setup.assert_not_called()
            run.assert_not_called()

    def test_container_guard(self):
        with patch.dict(os.environ, {"UZ_DEV_CONTAINER": "1"}):
            for command in ("setup", "cli", "dataviewer", "shell", "clear_venv"):
                with (
                    contextlib.redirect_stderr(io.StringIO()),
                    self.assertRaises(SystemExit),
                ):
                    developer.main([command])
            self.assertFalse((self.root / ".venv").exists())

    def test_lock_checked_before_build(self):
        with (
            environment_lock(self.root, use=True),
            patch.object(environment, "run") as run,
        ):
            with self.assertRaisesRegex(RuntimeError, "in use"):
                environment.setup()
            run.assert_not_called()

    def test_clear_refuses_active_users(self):
        self.installed()
        with environment_lock(self.root, use=True):
            with (
                contextlib.redirect_stderr(io.StringIO()),
                self.assertRaises(SystemExit),
            ):
                developer.main(["clear_venv"])
        self.assertTrue((self.root / ".venv").exists())
        developer.main(["clear_venv"])
        self.assertFalse((self.root / ".venv").exists())

    def test_dispatch(self):
        for arguments, project, task in (
            (["build", "cli"], "cli", "wheel"),
            (["build", "viewer"], "viewer", "bundle"),
            (["check", "viewer"], "viewer", "check"),
            (["task", "cli", "release-wheel"], "cli", "release-wheel"),
        ):
            with patch.object(environment, "run") as run:
                developer.main(arguments)
                run.assert_called_once_with(
                    sys.executable,
                    self.root / developer.PROJECTS[project] / "tasks.py",
                    task,
                )

    def test_setup_and_failed_install_rollback(self):
        def run(*command):
            if "--out" in command:
                (command[-1] / "ultrazohm_cli-0.1.0-test.whl").touch()
            if command[:2] == ("uv", "venv"):
                environment.executable("python").parent.mkdir(parents=True)
            if command[:3] == ("uv", "pip", "install"):
                for name in ("python", "ultrazohm-cli", "ultrazohm-dataviewer"):
                    environment.executable(name).touch()

        with (
            patch.object(environment, "run", side_effect=run),
            patch.object(environment.subprocess, "check_output", return_value="{}"),
        ):
            environment.setup()
        self.assertEqual(environment.saved_setup()["source"], "local")
        sentinel = self.root / ".venv/preserve"
        sentinel.write_text("previous environment")

        def failure(*command):
            if command[:3] == ("uv", "pip", "install"):
                raise subprocess.CalledProcessError(7, command)
            run(*command)

        with patch.object(environment, "run", side_effect=failure):
            with self.assertRaises(subprocess.CalledProcessError):
                environment.setup()
        self.assertEqual(sentinel.read_text(), "previous environment")

    def test_environment_lease_blocks_replacement_across_processes(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            script = (
                "import sys; from uz_environment import environment_lock; "
                "lock=environment_lock(sys.argv[1], use=True); lock.__enter__(); "
                "print('ready', flush=True); sys.stdin.read(); lock.__exit__(None,None,None)"
            )
            with subprocess.Popen(
                [sys.executable, "-c", script, directory],
                stdin=subprocess.PIPE,
                stdout=subprocess.PIPE,
                text=True,
            ) as child:
                try:
                    self.assertEqual(child.stdout.readline().strip(), "ready")
                    with environment_lock(root, use=True):
                        pass  # Multiple applications can share an installation.
                    with self.assertRaisesRegex(RuntimeError, "in use"):
                        with environment_lock(root):
                            self.fail("replacement acquired an active environment")
                finally:
                    child.stdin.close()
                    child.wait(timeout=10)
            with environment_lock(root):
                pass

    def test_background_supervisor_holds_lease_until_application_exits(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            ready = root / "ready"
            script = (
                "import sys; from pathlib import Path; "
                "Path(sys.argv[1]).touch(); sys.stdin.read()"
            )
            with subprocess.Popen(
                [
                    sys.executable,
                    str(Path(__file__).resolve().parent / "uz_environment.py"),
                    directory,
                    sys.executable,
                    "-c",
                    script,
                    str(ready),
                ],
                stdin=subprocess.PIPE,
            ) as child:
                try:
                    deadline = time.monotonic() + 10
                    while not ready.exists() and time.monotonic() < deadline:
                        self.assertIsNone(child.poll())
                        time.sleep(0.01)
                    self.assertTrue(ready.exists())
                    with self.assertRaisesRegex(RuntimeError, "in use"):
                        with environment_lock(root):
                            self.fail("background application lost its lease")
                finally:
                    child.stdin.close()
                    child.wait(timeout=10)
            self.assertEqual(child.returncode, 0)
            with environment_lock(root):
                pass

    def test_failed_removal_retains_backup(self):
        venv = self.root / ".venv"
        venv.mkdir()
        (venv / "original").write_text("preserve me")
        remove = shutil.rmtree

        def locked(path, *args, **kwargs):
            if Path(path) == venv:
                raise PermissionError("new environment locked")
            return remove(path, *args, **kwargs)

        with patch.object(environment.shutil, "rmtree", side_effect=locked):
            with self.assertRaisesRegex(
                RuntimeError, "Previous environment retained at"
            ) as error:
                with environment.replace_environment():
                    venv.mkdir()
                    raise RuntimeError("installation failed")
        (backup,) = self.root.glob(".uz-backup-*/environment")
        self.assertEqual((backup / "original").read_text(), "preserve me")
        self.assertIn(str(backup), str(error.exception))

    def test_failed_restore_retains_backup(self):
        venv = self.root / ".venv"
        venv.mkdir()
        (venv / "original").write_text("preserve me")
        rename = Path.rename

        def locked(path, target):
            if path.name == "environment":
                raise PermissionError("restore denied")
            return rename(path, target)

        with patch.object(Path, "rename", locked):
            with self.assertRaisesRegex(
                RuntimeError, "Previous environment retained at"
            ):
                with environment.replace_environment():
                    venv.mkdir()
                    raise RuntimeError("installation failed")
        (backup,) = self.root.glob(".uz-backup-*/environment")
        self.assertEqual((backup / "original").read_text(), "preserve me")
