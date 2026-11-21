"""Published-tool dispatch and offline uv integration tests."""

import contextlib
import io
import json
import os
import shutil
import subprocess
import sys
import tempfile
import unittest
import zipfile
from pathlib import Path
from unittest.mock import patch

import uz


def wheel(directory, name, version, dependencies=()):
    normalized = name.replace("-", "_")
    info = f"{normalized}-{version}.dist-info"
    content = {
        f"{normalized}/__init__.py": f'def main():\n    print("{name} {version}")\n',
        f"{info}/METADATA": (
            f"Metadata-Version: 2.1\nName: {name}\nVersion: {version}\n"
            + "".join(f"Requires-Dist: {d}\n" for d in dependencies)
        ),
        f"{info}/WHEEL": "Wheel-Version: 1.0\nGenerator: test\nRoot-Is-Purelib: true\nTag: py3-none-any\n",
        f"{info}/entry_points.txt": f"[console_scripts]\n{name} = {normalized}:main\n",
    }
    content[f"{info}/RECORD"] = "".join(
        f"{path},,\n" for path in [*content, f"{info}/RECORD"]
    )
    with zipfile.ZipFile(
        directory / f"{normalized}-{version}-py3-none-any.whl", "w"
    ) as archive:
        for entry, value in content.items():
            archive.writestr(entry, value)


class UserCommandsTest(unittest.TestCase):
    @unittest.skipIf(os.name == "nt", "Bash bootstrap contract")
    def test_bootstrap_preserves_arguments_cwd_and_exit_status(self):
        with tempfile.TemporaryDirectory(prefix="uz bootstrap ") as directory:
            root = Path(directory)
            executable = root / "uv"
            executable.write_text('#!/bin/sh\npwd\nprintf "%s\\n" "$@"\nexit 7\n')
            executable.chmod(0o755)
            for launcher in ("uz", "uz_developer"):
                result = subprocess.run(
                    ["bash", str(uz.ROOT / launcher), "one argument", "--flag"],
                    cwd=root,
                    env={
                        **os.environ,
                        "PATH": str(root) + os.pathsep + os.environ["PATH"],
                    },
                    capture_output=True,
                    text=True,
                )
                self.assertEqual(result.returncode, 7, result.stderr)
                lines = result.stdout.splitlines()
                self.assertEqual(lines[0], str(root))
                self.assertEqual(
                    lines[-3:],
                    [str(uz.ROOT / (launcher + ".py")), "one argument", "--flag"],
                )

    def test_default_channel_forwards_application_arguments(self):
        for arguments in (["status"], ["--", "status"], ["--version"]):
            for app in uz.PACKAGES:
                with (
                    self.subTest(app=app, arguments=arguments),
                    patch.object(uz, "run") as run,
                ):
                    uz.main([app, *arguments])
                    command = run.call_args.args[0]
                    self.assertIn("disallow", command)
                    self.assertEqual(command[-2:], [uz.PACKAGES[app], arguments[-1]])

    def test_launch_channel_and_arguments(self):
        for app in uz.PACKAGES:
            for channel, policy in (("stable", "disallow"), ("prerelease", "allow")):
                with (
                    self.subTest(app=app, channel=channel),
                    patch.object(uz, "run") as run,
                ):
                    uz.main([app, channel, "--", "--example", "a path"])
                    command = run.call_args.args[0]
                    self.assertEqual(command[:4], ["uv", "tool", "run", "--isolated"])
                    self.assertEqual(command[command.index("--prerelease") + 1], policy)
                    self.assertEqual(
                        command[-3:], [uz.PACKAGES[app], "--example", "a path"]
                    )

    def test_default_and_install(self):
        with patch.object(uz, "run") as run:
            uz.main(["cli"])
            self.assertIn("disallow", run.call_args.args[0])
            uz.main(["install", "dataviewer", "prerelease"])
            self.assertEqual(run.call_args.args[0][:3], ["uv", "tool", "install"])
            self.assertEqual(run.call_args.args[0][-1], "ultrazohm-dataviewer")

    def test_venv_is_a_published_shell(self):
        with patch.object(uz, "run") as run:
            uz.main(["venv", "prerelease"])
            command = run.call_args.args[0]
            self.assertEqual(
                command[-4:],
                ["--from", "ultrazohm-dataviewer", "python", uz.ROOT / "uz_shell.py"],
            )
            self.assertNotIn(str(uz.ROOT / ".venv"), list(map(str, command)))

    def test_failures_propagate(self):
        with patch.object(
            uz, "run", side_effect=subprocess.CalledProcessError(7, "uv")
        ):
            with (
                contextlib.redirect_stderr(io.StringIO()),
                self.assertRaises(SystemExit) as error,
            ):
                uz.main(["cli"])
            self.assertEqual(error.exception.code, 7)

    def test_rejects_old_development_commands(self):
        for arguments in (["setup"], ["cli", "local"], ["install", "invalid"]):
            with (
                contextlib.redirect_stderr(io.StringIO()),
                self.assertRaises(SystemExit),
            ):
                uz.main(arguments)

    @unittest.skipUnless(shutil.which("uv"), "uv needed for offline tool integration")
    def test_real_uv_channels_shell_and_install_are_isolated(self):
        with tempfile.TemporaryDirectory(prefix="uz published ") as directory:
            root = Path(directory)
            wheels = root / "wheels"
            wheels.mkdir()
            for version in ("1.0.0", "2.0.0.dev0"):
                wheel(wheels, "ultrazohm-cli", version)
                wheel(
                    wheels,
                    "ultrazohm-dataviewer",
                    version,
                    [f"ultrazohm-cli=={version}"],
                )
            (root / ".python-version").write_text(sys.executable)
            (root / "requirements.txt").write_text("shell-extra==1.0.0\n")
            wheel(wheels, "shell-extra", "1.0.0")
            (root / ".venv").mkdir()
            sentinel = root / ".venv/host-environment"
            sentinel.write_text("untouched")
            # Exercise the actual Python selection for venv without opening a TTY.
            report = root / "report.json"
            (root / "uz_shell.py").write_text(
                "import sys,json,importlib.metadata as m; from pathlib import Path; "
                f"Path({str(report)!r}).write_text(json.dumps([sys.prefix, "
                "m.version('ultrazohm-cli'),m.version('ultrazohm-dataviewer'),m.version('shell-extra')]))"
            )
            config = root / "uv.toml"
            config.write_text(
                "no-index = true\nfind-links = " + json.dumps([str(wheels)]) + "\n"
            )
            env = {
                "UV_CONFIG_FILE": str(config),
                "UV_NO_INDEX": "1",
                "UV_FIND_LINKS": str(wheels),
                "UV_CACHE_DIR": str(root / "cache"),
                "UV_TOOL_DIR": str(root / "tools"),
                "UV_TOOL_BIN_DIR": str(root / "bin"),
                "UV_PYTHON_DOWNLOADS": "never",
            }
            with patch.object(uz, "ROOT", root), patch.dict(os.environ, env):
                for channel, version in (
                    ("stable", "1.0.0"),
                    ("prerelease", "2.0.0.dev0"),
                ):
                    uz.main(["cli", channel])
                    uz.main(["dataviewer", channel])
                    uz.main(["venv", channel])
                    prefix, cli, viewer, extra = json.loads(report.read_text())
                    self.assertEqual(extra, "1.0.0")
                    self.assertEqual((cli, viewer), (version, version))
                    self.assertNotEqual(Path(prefix), root / ".venv")
                uz.main(["install", "cli", "prerelease"])
                executable = (
                    root
                    / "bin"
                    / ("ultrazohm-cli.exe" if os.name == "nt" else "ultrazohm-cli")
                )
                self.assertIn(
                    "2.0.0.dev0", subprocess.check_output([str(executable)], text=True)
                )
                # Explicit installation can also switch back from prerelease to stable.
                uz.main(["install", "cli", "stable"])
                self.assertIn(
                    "1.0.0", subprocess.check_output([str(executable)], text=True)
                )
            self.assertEqual(sentinel.read_text(), "untouched")


if __name__ == "__main__":
    unittest.main()
