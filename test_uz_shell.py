"""Private extension shells must preserve runtime settings and private history."""
import os
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

import uz_shell


@unittest.skipIf(os.name == "nt", "Bash private-mode contract")
class PrivateShellTest(unittest.TestCase):
    def exercise(self, private):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            observed = {}

            def spawn(command, env):
                observed["command"] = command
                observed["env"] = env
                observed["rc"] = Path(command[command.index("--rcfile") + 1])
                observed["text"] = observed["rc"].read_text()
                class Process:
                    def wait(self):
                        return 0
                return Process()

            env = {"PATH": "/bundle/bin:/usr/bin", "UV_CACHE_DIR": str(root / "cache")}
            if private:
                env["UZ_PRIVATE_SHELL_DIR"] = str(root / "shell")
            with (
                patch.dict(os.environ, env, clear=True),
                patch.object(uz_shell.sys, "prefix", str(root / "environment")),
                patch.object(uz_shell.sys, "base_prefix", "/bundle/python"),
                patch.object(uz_shell.shutil, "which", return_value="/bin/bash"),
                patch.object(uz_shell.subprocess, "Popen", side_effect=spawn),
            ):
                self.assertEqual(uz_shell.shell(), 0)
            self.assertFalse(observed["rc"].exists())
            self.assertEqual(observed["env"]["PATH"], env["PATH"])
            self.assertEqual(observed["env"]["UV_CACHE_DIR"], env["UV_CACHE_DIR"])
            self.assertIn("activate", observed["text"])
            if private:
                self.assertNotIn("$HOME/.bashrc", observed["text"])
                self.assertEqual(observed["rc"].parent, root / "shell")
                self.assertEqual(observed["env"]["HISTFILE"], str(root / "shell/bash_history"))
            else:
                self.assertIn("$HOME/.bashrc", observed["text"])
                self.assertNotIn("HISTFILE", observed["env"])

    def test_extension_private_shell(self):
        self.exercise(True)

    def test_manual_shell_keeps_user_profile(self):
        self.exercise(False)
