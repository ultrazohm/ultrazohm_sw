"""Exercise Vitis dispatch using a fake XSCT launcher; never touch hardware."""

import json
import os
import shlex
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
BIN = Path(
    os.environ.get(
        "UZ_CLI_BIN",
        ROOT
        / "ultrazohm_cli/target/debug"
        / ("ultrazohm-cli.exe" if os.name == "nt" else "ultrazohm-cli"),
    )
)


@unittest.skipUnless(BIN.exists(), "build Rust CLI first")
class VitisCommandTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.base = Path(self.tmp.name)
        self.repo = self.base / "checkout with spaces"
        (self.repo / "tcl_scripts").mkdir(parents=True)
        (self.repo / "vitis/software").mkdir(parents=True)
        header = self.repo / "vitis/software/Baremetal/src/include/javascope.h"
        header.parent.mkdir(parents=True, exist_ok=True)
        header.touch()
        self.script = self.repo / "tcl_scripts/vitis_headless.tcl"
        self.script.write_text("# Fixture, never executed\n")
        self.bin = self.base / "tools with spaces"
        self.bin.mkdir()
        self.result = self.base / "invocation.json"
        self.env = {
            **os.environ,
            "PATH": str(self.bin),
            "UZ_TEST_INVOCATION": str(self.result),
        }
        stub = self.bin / "fake.py"
        stub.write_text(
            "import json, os, sys\nfrom pathlib import Path\n"
            "Path(os.environ['UZ_TEST_INVOCATION']).write_text(json.dumps({'args':sys.argv[1:], 'cwd':os.getcwd()}))\n"
            "sys.exit(int(os.environ.get('UZ_TEST_EXIT', '0')))\n"
        )
        if os.name == "nt":
            (self.bin / "xsct.bat").write_text(
                f'@echo off\n"{sys.executable}" "{stub}" %*\n'
            )
        else:
            launcher = self.bin / "xsct"
            launcher.write_text(
                f'#!/bin/sh\nexec {shlex.quote(sys.executable)} {shlex.quote(str(stub))} "$@"\n'
            )
            launcher.chmod(0o755)

    def cli(self, *args, cwd=None, env=None):
        return subprocess.run(
            [str(BIN), *args],
            cwd=cwd or self.base,
            env=env or self.env,
            text=True,
            capture_output=True,
            timeout=10,
        )

    def test_service_commands_never_fall_back_to_local_tools(self):
        result = self.cli("--endpoint", "127.0.0.1:1", "build")
        self.assertNotEqual(result.returncode, 0)
        self.assertFalse(self.result.exists())

    def test_actions_and_paths_with_spaces(self):
        for command, action, tail in [
            ("generate", "generate", []),
            ("build", "build", []),
            ("build-clean", "build-clean", []),
        ]:
            with self.subTest(command=command):
                result = self.cli(command, "--local", "--repo", str(self.repo))
                self.assertEqual(result.returncode, 0, result.stderr)
                call = json.loads(self.result.read_text())
                self.assertEqual(Path(call["cwd"]).resolve(), self.repo.resolve())
                self.assertEqual(call["args"][0], "-nodisp")
                script = Path(call["args"][1]).resolve()
                self.assertTrue(
                    script.is_relative_to(self.repo / "artifacts/cli-tools")
                )
                self.assertEqual(
                    script.read_bytes(),
                    (ROOT / "tcl_scripts/vitis_headless.tcl").read_bytes(),
                )
                self.assertTrue(
                    (script.parent / "launch/Run_UltraZohm.launch").is_file()
                )
                self.assertEqual(call["args"][2:], [action, *tail])
        result = self.cli("generate", "--local", "--open", "--repo", str(self.repo))
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(
            json.loads(self.result.read_text())["args"][2:], ["generate-open"]
        )

    def test_embedded_scripts_work_without_checkout_scripts_and_preserve_timestamps(
        self,
    ):
        self.script.unlink()
        first = self.cli("build", "--local", "--repo", str(self.repo))
        self.assertEqual(first.returncode, 0, first.stderr)
        script = Path(json.loads(self.result.read_text())["args"][1])
        stamp = script.stat().st_mtime_ns
        second = self.cli("build", "--local", "--repo", str(self.repo))
        self.assertEqual(second.returncode, 0, second.stderr)
        self.assertEqual(script.stat().st_mtime_ns, stamp)

    def test_discovery_from_subdirectory(self):
        result = self.cli("build", "--local", cwd=self.repo / "vitis/software")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(
            Path(json.loads(self.result.read_text())["cwd"]).resolve(),
            self.repo.resolve(),
        )

    def test_missing_repository_and_tool(self):
        result = self.cli("build", "--local")
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("--repo", result.stderr)
        result = self.cli("build", "--local", "--repo", str(self.base))
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("not an UltraZohm repository", result.stderr)
        empty = self.base / "empty"
        empty.mkdir()
        result = self.cli(
            "build",
            "--local",
            "--repo",
            str(self.repo),
            env={**self.env, "PATH": str(empty)},
        )
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("not found on PATH", result.stderr)
        self.assertFalse(self.result.exists())

    def test_child_failure_and_invalid_profile(self):
        result = self.cli(
            "build",
            "--local",
            "--repo",
            str(self.repo),
            env={**self.env, "UZ_TEST_EXIT": "7"},
        )
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("Vitis build failed", result.stderr)
        self.result.unlink()
        result = self.cli(
            "flash", "--repo", str(self.repo), "--profile", "Debug_UltraZohm"
        )
        self.assertNotEqual(result.returncode, 0)
        self.assertFalse(self.result.exists())

    def test_external_script_bundle_uses_selected_workspace(self):
        bundle = self.base / "application bundle" / "tcl_scripts"
        bundle.mkdir(parents=True)
        script = bundle / "vitis_headless.tcl"
        script.write_text("# bundled entry point")
        self.script.unlink()
        self.env["UZ_CLI_TCL_DIR"] = str(bundle)
        result = self.cli("build", "--local", "--repo", str(self.repo))
        self.assertEqual(result.returncode, 0, result.stderr)
        call = json.loads(self.result.read_text())
        self.assertEqual(Path(call["args"][1]).resolve(), script.resolve())
        self.assertEqual(Path(call["cwd"]).resolve(), self.repo.resolve())
