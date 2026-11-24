"""Developer command routing, persistence and build serialization."""

import contextlib
import io
import os
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

import uz_developer
import uz_venv
from uz_build import build_lock, venv_bin


class DeveloperTest(unittest.TestCase):
    def test_application_builds_refresh_pair(self):
        for name in ("cli", "dataviewer", "linux_wheels"):
            with (
                tempfile.TemporaryDirectory() as directory,
                patch.object(uz_developer, "ROOT", Path(directory)),
                patch.object(uz_developer, "build_development") as build,
                patch.object(sys, "platform", "linux"),
            ):
                uz_developer.main(["build", name])
                build.assert_called_once_with(Path(directory), uz_developer.run)

    def test_task_and_check_dispatch(self):
        with patch.object(uz_developer, "run") as run:
            uz_developer.main(["task", "cli", "wheel", "--out", "a path"])
            self.assertEqual(run.call_args.args[0][-3:], ["wheel", "--out", "a path"])
            uz_developer.main(["check", "dataviewer", "--gui-smoke"])
            self.assertEqual(run.call_args.args[0][-2:], ["check", "--gui-smoke"])
        for args in (
            ["build", "viewer"],
            ["check", "viewer"],
            ["task", "viewer", "wheel"],
        ):
            with (
                contextlib.redirect_stderr(io.StringIO()),
                self.assertRaises(SystemExit),
            ):
                uz_developer.main(args)

    def test_shell_reuses_environment_without_build_or_cleanup(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            environment = root / "environment"
            python = venv_bin(environment)
            python.parent.mkdir(parents=True)
            python.touch()
            with (
                patch.dict(
                    os.environ, {"UZ_DEVELOPMENT_ENVIRONMENT": str(environment)}
                ),
                patch.object(uz_developer, "run") as run,
            ):
                uz_venv.development_shell(root, run)
                uz_venv.development_shell(root, run)
                self.assertEqual(run.call_count, 2)
                run.assert_called_with([python.resolve(), root / "uz_shell.py"])
                self.assertTrue(python.exists())

    def test_shell_requires_build(self):
        with (
            tempfile.TemporaryDirectory() as directory,
            patch.dict(os.environ, {"UZ_DEVELOPMENT_ENVIRONMENT": directory}),
            self.assertRaisesRegex(RuntimeError, "Build first"),
        ):
            uz_venv.development_shell(
                Path(directory), lambda _: self.fail("must not build")
            )

    def test_build_installs_only_after_both_artifacts_succeed(self):
        with patch.object(uz_venv, "install_development") as install:
            calls = []
            uz_venv.build_development(Path("checkout"), calls.append)
            self.assertEqual([call[-1] for call in calls], ["release-wheel", "wheel"])
            install.assert_called_once()
            install.reset_mock()

            def fail(command):
                raise subprocess.CalledProcessError(1, command)

            with self.assertRaises(subprocess.CalledProcessError):
                uz_venv.build_development(Path("checkout"), fail)
            install.assert_not_called()

    def test_build_lock_is_shared_across_processes_and_released(self):
        with tempfile.TemporaryDirectory() as directory:
            code = "from uz_build import build_lock; import sys;\nwith build_lock(sys.argv[1], 'development'): print('acquired')"
            with build_lock(directory, "development"):
                result = subprocess.run(
                    [sys.executable, "-c", code, directory],
                    capture_output=True,
                    text=True,
                )
                self.assertNotEqual(result.returncode, 0)
                self.assertIn("Another development build", result.stderr)
            result = subprocess.run(
                [sys.executable, "-c", code, directory], capture_output=True, text=True
            )
            self.assertEqual(result.returncode, 0, result.stderr)


if __name__ == "__main__":
    unittest.main()
