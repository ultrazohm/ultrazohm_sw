"""Minimal checks for project dispatch and child exit codes."""

import sys
import subprocess
import io
import tempfile
import time
import unittest
from pathlib import Path
from unittest.mock import patch

import uz
from uz_environment import environment_lock


class DispatchTest(unittest.TestCase):
    def test_application_shortcuts(self):
        for app in ("cli", "dataviewer"):
            for flag in (None, "--stable", "--prerelease", "--local"):
                source = flag[2:] if flag else "stable"
                for saved in ("stable", "local", "prerelease"):
                    with (
                        self.subTest(app=app, flag=flag, saved=saved),
                        patch.object(uz.importlib, "import_module") as load,
                    ):
                        setup = load.return_value
                        setup.saved_setup.return_value = {"source": saved}
                        uz.main([app] + ([flag] if flag else []))
                        project = uz.PROJECTS[
                            "viewer" if app == "dataviewer" else "cli"
                        ]
                        load.assert_called_once_with(f"{project}.tools.setup_env")
                        setup.setup.assert_called_once_with(
                            None if saved == source else source, reuse=True
                        )
                        setup.executable.assert_called_once_with(f"ultrazohm-{app}")
                        setup.run.assert_called_once_with(
                            setup.executable.return_value, interactive=True
                        )

    def test_interactive_viewer(self):
        with (
            patch.object(uz.importlib, "import_module") as load,
            patch.object(uz.subprocess, "Popen") as start,
            patch.object(uz.socket, "socket"),
            patch.object(uz, "wait_for_viewer") as ready,
        ):
            setup = load.return_value
            setup.saved_setup.return_value = {}
            setup.executable.side_effect = lambda name: Path("/environment") / name
            uz.main(["dataviewer", "--interactive", "--local"])
            setup.setup.assert_called_once_with("local", reuse=True)
            self.assertEqual(
                Path(start.call_args.args[0][-1]), Path("/environment/ultrazohm-dataviewer")
            )
            ready.assert_called_once_with(
                start.return_value, Path("/environment/python")
            )
            self.assertEqual(start.call_args.kwargs["stdin"], uz.subprocess.DEVNULL)
            setup.run.assert_called_once_with(
                Path("/environment/python"),
                uz.ROOT / "ultrazohm_dataviewer/tools/env_shell.py",
                interactive=True,
            )

    def test_cli_keeps_viewer_installation(self):
        with patch.object(uz.importlib, "import_module") as load:
            setup = load.return_value
            setup.saved_setup.return_value = {"app": "viewer", "source": "local"}
            uz.main(["cli", "--local"])
            self.assertEqual(
                load.call_args.args[0], "ultrazohm_dataviewer.tools.setup_env"
            )
            setup.setup.assert_called_once_with(None, reuse=True)

    def test_readiness_rejects_early_exit_and_timeout(self):
        from unittest.mock import Mock

        child = Mock()
        child.poll.return_value = 7
        with self.assertRaisesRegex(RuntimeError, "exit code 7"):
            uz.wait_for_viewer(child, "python")
        child.poll.return_value = None
        with self.assertRaisesRegex(RuntimeError, "not ready"):
            uz.wait_for_viewer(child, "python", timeout=0)

    def test_startup_failure_closes_child_without_opening_shell(self):
        with (
            patch.object(uz.importlib, "import_module") as load,
            patch.object(uz.socket, "socket"),
            patch.object(uz.subprocess, "Popen") as start,
            patch.object(
                uz, "wait_for_viewer", side_effect=RuntimeError("startup failed")
            ),
            patch.object(uz, "stop_background") as stop,
        ):
            load.return_value.saved_setup.return_value = {}
            load.return_value.executable.return_value = Path("python")
            with self.assertRaises(SystemExit):
                uz.main(["dataviewer", "--interactive", "--local"])
            stop.assert_called_once_with(start.return_value)
            load.return_value.run.assert_not_called()

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
                    str(uz.ROOT / "uz_environment.py"),
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

    def test_clear_refuses_active_environment(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / ".venv").mkdir()
            with patch.object(uz, "ROOT", root), environment_lock(root, use=True):
                with self.assertRaisesRegex(RuntimeError, "in use"):
                    uz.clear_venv()
                self.assertTrue((root / ".venv").exists())

    def test_shortcut_failure_does_not_launch(self):
        with (
            patch.object(uz.importlib, "import_module") as load,
            patch.object(sys, "stderr", new_callable=io.StringIO) as stderr,
        ):
            setup = load.return_value
            setup.setup.side_effect = uz.subprocess.CalledProcessError(7, "setup")
            with self.assertRaises(SystemExit) as error:
                uz.main(["cli"])
            self.assertEqual(error.exception.code, 7)
            self.assertIn(
                "./uz cli --prerelease"
                if uz.os.name != "nt"
                else "uz.ps1 cli --prerelease",
                stderr.getvalue(),
            )
            setup.run.assert_not_called()

    def test_shortcut_rejects_conflicting_flags(self):
        with patch.object(uz.importlib, "import_module") as load:
            for args in (["cli", "--local", "--stable"], ["cli", "--interactive"]):
                with self.assertRaises(SystemExit) as error:
                    uz.main(args)
                self.assertEqual(error.exception.code, 2)
            load.assert_not_called()

    def test_clear_venv_removes_only_managed_environment(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            venv = root / ".venv"
            venv.mkdir()
            (venv / ".uz-setup.json").write_text('{"app": "cli"}')
            other = root / "ultrazohm_cli" / "target"
            other.mkdir(parents=True)
            with (
                patch.object(uz, "ROOT", root),
                patch.object(uz.subprocess, "Popen") as run,
            ):
                uz.main(["clear_venv"])
                self.assertFalse(venv.exists())
                self.assertTrue(other.is_dir())
                uz.main(["clear_venv"])
                run.assert_not_called()

    def test_forwarding(self):
        cases = [
            (["check", "cli"], "cli", ["check"]),
            (["check", "viewer"], "viewer", ["check"]),
            (["build", "cli", "--out", "a path"], "cli", ["wheel", "--out", "a path"]),
            (["build", "viewer"], "viewer", ["bundle"]),
            (["task", "cli", "format"], "cli", ["format"]),
            (["task", "viewer", "lint"], "viewer", ["lint"]),
            (["setup", "local", "--app", "cli"], "cli", ["setup", "local"]),
            (["shell", "--app", "viewer"], "viewer", ["shell"]),
        ]
        for arguments, project, forwarded in cases:
            with (
                self.subTest(arguments=arguments),
                patch.object(uz.subprocess, "Popen") as run,
            ):
                run.return_value.__enter__.return_value.wait.return_value = 0
                uz.main(arguments)
                run.assert_called_once_with(
                    [
                        sys.executable,
                        str(uz.ROOT / uz.PROJECTS[project] / "tasks.py"),
                        *forwarded,
                    ],
                )

    def test_default_application_and_child_failure(self):
        with (
            patch.object(uz, "selected_app", return_value="cli"),
            patch.object(uz.subprocess, "Popen") as run,
        ):
            run.return_value.__enter__.return_value.wait.side_effect = [
                KeyboardInterrupt,
                7,
            ]
            with self.assertRaises(SystemExit) as error:
                uz.main(["shell"])
            self.assertEqual(error.exception.code, 7)
            self.assertEqual(
                run.call_args.args[0][1], str(uz.ROOT / "ultrazohm_cli/tasks.py")
            )


if __name__ == "__main__":
    unittest.main()
