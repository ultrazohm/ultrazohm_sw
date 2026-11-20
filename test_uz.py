"""Minimal checks for project dispatch and child exit codes."""

import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

import uz


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
                        project = uz.PROJECTS["viewer" if app == "dataviewer" else "cli"]
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
        ):
            setup = load.return_value
            setup.saved_setup.return_value = {}
            setup.executable.side_effect = lambda name: Path("/environment") / name
            uz.main(["dataviewer", "--interactive", "--local"])
            setup.setup.assert_called_once_with("local", reuse=True)
            self.assertEqual(start.call_args.args[0], ["/environment/ultrazohm-dataviewer"])
            self.assertEqual(start.call_args.kwargs["stdin"], uz.subprocess.DEVNULL)
            setup.run.assert_called_once_with(
                Path("/environment/python"),
                uz.ROOT / "ultrazohm_dataviewer/tools/env_shell.py",
                interactive=True,
            )

    def test_shortcut_failure_does_not_launch(self):
        with patch.object(uz.importlib, "import_module") as load:
            setup = load.return_value
            setup.setup.side_effect = uz.subprocess.CalledProcessError(7, "setup")
            with self.assertRaises(SystemExit) as error:
                uz.main(["cli"])
            self.assertEqual(error.exception.code, 7)
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
