"""Minimal checks for project dispatch and child exit codes."""

import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

import uz


class DispatchTest(unittest.TestCase):
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
