"""Shared preference persistence and selection, without a viewer."""

import os
import tempfile
import unittest
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
from unittest.mock import patch

from ultrazohm_cli.configuration import (
    channel_mapping,
    load_or_seed_profile,
    resolve_xsct,
    save_profile,
    save_xsct,
)

ROOT = Path(__file__).resolve().parents[2]


class PreferencesTest(unittest.TestCase):
    def test_concurrent_seed_and_invalid_save_preserve_complete_file(self):
        mapping = channel_mapping(ROOT)
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "settings.json"
            with ThreadPoolExecutor(max_workers=8) as pool:
                values = list(
                    pool.map(lambda _: load_or_seed_profile(path, mapping), range(16))
                )
            self.assertTrue(all(value == values[0] for value in values))
            value = {**values[0], "name": "saved", "sample_period_us": 50}
            save_profile(path, value, mapping)
            before = path.read_bytes()
            self.assertEqual(load_or_seed_profile(path, mapping), value)
            with self.assertRaises(ValueError):
                save_profile(
                    path, {**value, "initial_channels": {"1": "absent"}}, mapping
                )
            self.assertEqual(path.read_bytes(), before)
            self.assertFalse(list(path.parent.glob(".uz-settings*")))

    def test_tool_precedence_and_workspace_switch_do_not_change_path(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            a, b = root / "a", root / "b"
            a.mkdir()
            b.mkdir()
            name = "xsct.cmd" if os.name == "nt" else "xsct"
            tool = root / name
            tool.touch()
            tool.chmod(0o755)
            other = root / "other"
            other.touch()
            other.chmod(0o755)
            with patch.dict(os.environ, {"PATH": ""}):
                save_xsct(tool, a)
                self.assertEqual(resolve_xsct(repo=a), tool)
                self.assertEqual(resolve_xsct(other, a), other)
                with self.assertRaises(ValueError):
                    resolve_xsct(repo=b)
                self.assertEqual(os.environ["PATH"], "")
                tool.unlink()
                with self.assertRaisesRegex(ValueError, "not found"):
                    resolve_xsct(repo=a)
                self.assertEqual(resolve_xsct(other, a), other)

    def test_native_service_reads_saved_profile_and_explicit_profile_wins(self):
        import socket

        import test_service_jobs as jobs
        from ultrazohm_cli import Acquisition

        fixture = jobs.FirmwareServiceTest()
        fixture.setUp()
        try:
            mapping = channel_mapping(fixture.repo)
            saved = fixture.repo / "artifacts/_user/settings.json"
            profile = load_or_seed_profile(saved, mapping)
            save_profile(saved, {**profile, "sample_period_us": 321}, mapping)
            endpoint = fixture.start()
            self.assertEqual(
                fixture.request(endpoint, "catalog")["profile"]["sample_period_us"], 321
            )
            explicit = fixture.base / "explicit.json"
            save_profile(explicit, {**profile, "sample_period_us": 123}, mapping)
            with socket.socket() as reserve:
                reserve.bind(("127.0.0.1", 0))
                embedded_endpoint = f"127.0.0.1:{reserve.getsockname()[1]}"
            with Acquisition(
                endpoint=embedded_endpoint,
                repo=str(fixture.repo),
                profile=str(explicit),
                output=str(fixture.base / "explicit-run"),
            ):
                self.assertEqual(
                    fixture.request(embedded_endpoint, "catalog")["profile"][
                        "sample_period_us"
                    ],
                    123,
                )
        finally:
            fixture.doCleanups()

    def test_native_build_uses_saved_tool_without_path_changes(self):
        import test_vitis_cli as tooling

        fixture = tooling.VitisCommandTest()
        fixture.setUp()
        try:
            launcher = fixture.bin / ("xsct.bat" if os.name == "nt" else "xsct")
            save_xsct(launcher, fixture.repo)
            result = fixture.cli(
                "build",
                "--local",
                "--repo",
                str(fixture.repo),
                env={**fixture.env, "PATH": ""},
            )
            self.assertEqual(result.returncode, 0, result.stderr)
            self.assertTrue(fixture.result.exists())
        finally:
            fixture.doCleanups()
