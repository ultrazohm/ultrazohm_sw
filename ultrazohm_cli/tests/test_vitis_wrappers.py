"""Verify public firmware wrappers reject XSCT's false-success exits."""

import json
import os
import shlex
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


class FirmwareWrapperTest(unittest.TestCase):
    def test_completion_and_exit_status(self):
        with tempfile.TemporaryDirectory(prefix="uz wrapper ") as directory:
            root = Path(directory)
            stub = root / "fake.py"
            stub.write_text(
                "import json, os, sys\nfrom pathlib import Path\n"
                "args = sys.argv[1:]\n"
                "action = next(args[i+1] for i, a in enumerate(args) if a.endswith('.tcl'))\n"
                "receipt = Path(os.environ['UZ_VITIS_COMPLETION'])\n"
                "Path(os.environ['UZ_TEST_REPORT']).write_text(json.dumps([args, str(receipt)]))\n"
                "mode = os.environ['UZ_TEST_MODE']\n"
                "if mode != 'missing': receipt.write_text('wrong' if mode == 'wrong' else action)\n"
                "sys.exit(7 if mode == 'failed' else 0)\n"
            )
            launcher = root / ("xsct.bat" if os.name == "nt" else "xsct")
            if os.name == "nt":
                launcher.write_text(f'@echo off\n"{sys.executable}" "{stub}" %*\n')
                entries = [
                    (["cmd", "/c", str(ROOT / "vitis" / name)], action)
                    for name, action in (
                        ("build_and_flash.bat", "flash"),
                        ("open_workspace.bat", "open"),
                        ("run_generate_workspace.bat", "generate-open"),
                    )
                ]
            else:
                launcher.write_text(
                    f'#!/bin/sh\nexec {shlex.quote(sys.executable)} {shlex.quote(str(stub))} "$@"\n'
                )
                launcher.chmod(0o755)
                entries = [
                    (["bash", str(ROOT / "vitis/run_xsct_checked.sh"), action], action)
                    for action in (
                        "generate",
                        "generate-open",
                        "open",
                        "build",
                        "build-clean",
                        "flash",
                    )
                ]
            report = root / "report.json"
            stale = root / "stale"
            stale.write_text("flash")
            env = {
                **os.environ,
                "XSCT": str(launcher),
                "UZ_TEST_REPORT": str(report),
                "UZ_VITIS_COMPLETION": str(stale),
            }
            if shutil.which("make") and os.name != "nt":
                entries += [
                    (["make", "-C", str(ROOT / "vitis"), action], action)
                    for action in (
                        "generate",
                        "build",
                        "build-clean",
                        "flash",
                    )
                ]
            for command, action in entries:
                for mode in ("success", "missing", "wrong", "failed"):
                    with self.subTest(command=command, mode=mode):
                        result = subprocess.run(
                            command,
                            cwd=root,
                            env={**env, "UZ_TEST_MODE": mode},
                            capture_output=True,
                            text=True,
                            timeout=10,
                        )
                        self.assertEqual(
                            result.returncode == 0,
                            mode == "success",
                            result.stdout + result.stderr,
                        )
                        args, receipt = json.loads(report.read_text())
                        self.assertIn(action, args)
                        self.assertFalse(Path(receipt).parent.exists())
                        self.assertEqual(stale.read_text(), "flash")
                        if mode in ("missing", "wrong"):
                            self.assertIn("did not confirm completion", result.stderr)
                        if os.name != "nt":
                            self.assertEqual(
                                "-nodisp" in args, action in ("open", "generate-open")
                            )
                        else:
                            self.assertNotIn("-nodisp", args)
                            self.assertNotIn("-norlwrap", args)
