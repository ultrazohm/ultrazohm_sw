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
    def test_build_refreshes_pair(self):
        with (
            tempfile.TemporaryDirectory() as directory,
            patch.object(uz_developer, "ROOT", Path(directory)),
            patch.object(uz_developer, "build_development") as build,
        ):
            uz_developer.main(["build"])
            build.assert_called_once_with(Path(directory), uz_developer.run)

    def test_project_tasks_dispatch_in_process(self):
        calls = []
        tasks = uz_developer.project_tasks("cli")
        with (
            patch.dict(
                tasks.TASKS,
                {"lint": tasks.TASKS["lint"].__class__(calls.append, "lint")},
            ),
            patch.object(uz_developer, "project_tasks", return_value=tasks),
        ):
            uz_developer.main(["cli", "lint"])
        self.assertEqual(len(calls), 1)
        self.assertEqual(calls[0].task, "lint")

    def test_every_project_task_parses(self):
        for project in uz_developer.PROJECTS:
            tasks = uz_developer.project_tasks(project)
            for name in tasks.TASKS:
                with (
                    contextlib.redirect_stdout(io.StringIO()),
                    self.assertRaises(SystemExit) as exit,
                ):
                    uz_developer.main([project, name, "--help"])
                self.assertEqual(exit.exception.code, 0)

    def test_invalid_commands_are_rejected(self):
        for args in (
            ["build", "viewer"],
            ["viewer", "check"],
            ["cli", "unknown"],
            ["task", "cli", "wheel"],
            ["verify", "macos"],
        ):
            with (
                contextlib.redirect_stderr(io.StringIO()),
                self.assertRaises(SystemExit),
            ):
                uz_developer.main(args)

    def test_tasks_run_in_child_processes(self):
        with patch.object(uz_developer, "run") as run:
            uz_developer.task("cli", "debug-wheel", "--out", "a path")
        self.assertEqual(
            run.call_args.args[0][1:],
            [uz_developer.ROOT / "uz_developer.py", "cli", "debug-wheel", "--out", "a path"],
        )

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
            self.assertEqual([call[-2] for call in calls], ["cli", "dataviewer"])
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
