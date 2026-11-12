"""Release setup tests use synthetic GitHub responses; never publish or download."""
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from zipfile import ZipFile
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
import wheel_releases as releases
from release_ci import release_metadata

LINUX = "ultrazohm-0.2.0-cp310-abi3-manylinux_2_28_x86_64.whl"
WINDOWS = "ultrazohm-0.2.0-cp310-abi3-win_amd64.whl"


def release(channel="stable", ident=1, published="2026-01-01T00:00:00Z", **kwargs):
    return {"id": ident, "tag_name": releases.TAG_PREFIXES[channel] + str(ident),
            "draft": False, "prerelease": channel == "testing", "published_at": published,
            "assets": [], **kwargs}


def asset(name):
    return {"name": name, "browser_download_url":
            f"https://github.com/{releases.REPOSITORY}/releases/download/tag/{name}"}


class WheelReleaseTest(unittest.TestCase):
    def test_local_cli_selection_uses_mtime_and_skips_legacy(self):
        with tempfile.TemporaryDirectory() as tmp:
            paths = [Path(tmp) / name for name in [
                "ultrazohm-0.1.0-cp310-abi3-linux_x86_64.whl",
                "ultrazohm-0.1.0.dev4001-cp310-abi3-linux_x86_64.whl",
                "ultrazohm-0.1.0.dev5001-cp310-abi3-linux_x86_64.whl"]]
            for index, path in enumerate(paths):
                with ZipFile(path, "w") as wheel:
                    if index:
                        wheel.writestr("ultrazohm.dist-info/entry_points.txt",
                                       "[console_scripts]\nultrazohm = ultrazohm.cli:main\n")
                os.utime(path, (100 + index, 100 + index))
            with self.assertRaisesRegex(ValueError, "no ultrazohm console command"):
                releases.validate_cli_wheel(paths[0])
            with patch.object(releases, "compatible_wheels", return_value=paths):
                self.assertEqual(releases.local_cli_wheels(paths, sys.executable, {}),
                                 [paths[2], paths[1]])

    def test_cli_wheel_rejects_corrupt_or_wrong_entry_point(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / LINUX
            path.write_bytes(b"not a zip")
            with self.assertRaisesRegex(ValueError, "Invalid CLI wheel"):
                releases.validate_cli_wheel(path)
            with ZipFile(path, "w") as wheel:
                wheel.writestr("ultrazohm.dist-info/entry_points.txt",
                               "[console_scripts]\nother = ultrazohm.cli:main\n")
            with self.assertRaisesRegex(ValueError, "no ultrazohm console command"):
                releases.validate_cli_wheel(path)

    def test_channel_detection_and_override_fallback(self):
        for branch, expected in [("main", "stable"), ("feature/uz_cli26", "testing"),
                                 ("other", "stable"), ("", "stable")]:
            with patch.object(releases.subprocess, "run", return_value=subprocess.CompletedProcess([], 0, branch)):
                self.assertEqual(releases.detect_channel(ROOT), expected)
        with patch.object(releases.subprocess, "run", side_effect=FileNotFoundError):
            self.assertEqual(releases.detect_channel(ROOT), "stable")

    def test_channel_filter_and_publication_order(self):
        items = [release(), release("testing", 2), release(ident=3, draft=True),
                 release(ident=4, tag_name="firmware-v9"),
                 release(ident=5, published="2026-02-01T00:00:00Z")]
        fetch = lambda url: json.dumps(items).encode()
        self.assertEqual(releases.latest_release("stable", fetch)["id"], 5)
        self.assertEqual(releases.latest_release("testing", fetch)["id"], 2)
        with self.assertRaisesRegex(ValueError, "No published"):
            releases.latest_release("testing", lambda url: b"[]")

    def test_pagination(self):
        pages = [json.dumps([release(tag_name="firmware")] * 100).encode(),
                 json.dumps([release()]).encode()]
        calls = []
        def fetch(url):
            calls.append(url)
            return pages.pop(0)
        self.assertEqual(releases.latest_release("stable", fetch)["id"], 1)
        self.assertIn("page=2", calls[-1])

    def test_local_menu_includes_newest_release(self):
        wheels = [LINUX, "older.whl"]
        with patch("builtins.print") as printed:
            self.assertEqual(releases.choose_local(wheels, "testing", True, lambda _: ""), Path(LINUX))
            menu = "\n".join(str(call.args[0]) for call in printed.call_args_list)
            self.assertIn("1. Use latest local build", menu)
            self.assertIn("2. Download latest from GitHub (testing)", menu)
            self.assertNotIn("older.whl", menu)
            self.assertIsNone(releases.choose_local(wheels, "testing", True, lambda _: "2"))
            inputs = iter(["bad", "3", "1"])
            self.assertEqual(releases.choose_local(wheels, "stable", True, lambda _: next(inputs)), Path(LINUX))
        self.assertIsNone(releases.choose_local([], "stable", False))
        with self.assertRaisesRegex(ValueError, "--latest"):
            releases.choose_local(wheels, "stable", False)

    @unittest.skipUnless(importlib.util.find_spec("packaging"), "packaging required")
    def test_destination_tags_and_version_order(self):
        from packaging.tags import sys_tags
        tag = next(sys_tags())
        names = [f"ultrazohm-{version}-{tag}.whl" for version in ["0.2.0", "0.10.0", "0.3.0.dev1"]]
        result = releases.compatible_wheels(names + ["bad.whl", "ultrazohm-1.0-cp39-cp39-madeup.whl"], sys.executable, os.environ)
        self.assertEqual(result, [names[1], names[2], names[0]])

    def download_fixture(self, destination, checksum=None, compatible=True):
        content = b"synthetic wheel"
        checksum = checksum or hashlib.sha256(content).hexdigest()
        metadata = release(assets=[asset(LINUX), asset(WINDOWS), asset("SHA256SUMS")])
        def fetch(url):
            if "api.github.com" in url:
                return json.dumps([metadata]).encode()
            if url.endswith("SHA256SUMS"):
                return f"{checksum}  {LINUX}\n".encode()
            return content
        with patch.object(releases, "compatible_wheels", return_value=[LINUX] if compatible else []):
            return releases.download_latest("stable", destination, sys.executable, {}, fetch)

    def test_download_verified_and_cached(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = self.download_fixture(Path(tmp))
            self.assertEqual(path.name, LINUX)
            self.assertEqual(path.read_bytes(), b"synthetic wheel")
            self.assertEqual(list(Path(tmp).iterdir()), [path])

    def test_bad_checksum_preserves_local_wheel(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / LINUX
            path.write_bytes(b"existing wheel")
            with self.assertRaisesRegex(ValueError, "Checksum mismatch"):
                self.download_fixture(Path(tmp), "0" * 64)
            self.assertEqual(path.read_bytes(), b"existing wheel")
            self.assertEqual(list(Path(tmp).iterdir()), [path])

    def test_incompatible_release_does_not_fall_back(self):
        with tempfile.TemporaryDirectory() as tmp:
            with self.assertRaisesRegex(ValueError, "No older release"):
                self.download_fixture(Path(tmp), compatible=False)
            self.assertEqual(list(Path(tmp).iterdir()), [])

    def test_invalid_asset_origin(self):
        with self.assertRaisesRegex(ValueError, "unexpected"):
            releases.asset_url({"browser_download_url": "https://example.com/wheel.whl"})

    def test_publish_branch_guard_and_unique_versions(self):
        stable = release_metadata("main", "0.2.0", 42, 1)
        testing = release_metadata("feature/uz_cli26", "0.2.0", 42, 1)
        self.assertEqual(stable["version"], "0.2.0.post42001")
        self.assertEqual(testing["version"], "0.2.0.dev42001")
        self.assertTrue(testing["tag"].startswith("uz-cli-testing-v"))
        self.assertNotEqual(stable, release_metadata("main", "0.2.0", 42, 2))
        with self.assertRaisesRegex(ValueError, "not allowed"):
            release_metadata("other", "0.2.0", 42, 1)
