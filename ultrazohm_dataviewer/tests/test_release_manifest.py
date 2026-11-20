"""Reject incomplete or mismatched releases before publication."""

import json
import sys
import tempfile
import unittest
import zipfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from release_manifest import manifest


class ManifestTest(unittest.TestCase):
    def fixture(self, root, *, dependency="1.0.0", linux_tag="manylinux_2_28_x86_64"):
        for name, tag in [
            ("ultrazohm-cli", f"cp310-abi3-{linux_tag}"),
            ("ultrazohm-cli", "cp310-abi3-win_amd64"),
            ("ultrazohm-dataviewer", "py3-none-any"),
        ]:
            base = name.replace("-", "_") + "-1.0.0"
            with zipfile.ZipFile(root / f"{base}-{tag}.whl", "w") as archive:
                meta = f"Name: {name}\nVersion: 1.0.0\n"
                if name.endswith("dataviewer"):
                    meta += f"Requires-Dist: ultrazohm-cli=={dependency}\n"
                archive.writestr(f"{base}.dist-info/METADATA", meta)
                archive.writestr(f"{base}.dist-info/WHEEL", f"Tag: {tag}\n")
        for name in ("ultrazohm-cli", "ultrazohm-dataviewer"):
            (root / f"{name}-1.0.0-windows-x86_64.zip").write_bytes(b"archive")

    def test_valid_manifest_has_every_artifact_and_hash(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            self.fixture(root)
            manifest(root, "1.0.0")
            data = json.loads((root / "manifest.json").read_text())
            self.assertEqual(len(data["artifacts"]), 5)
            self.assertEqual(len((root / "SHA256SUMS").read_text().splitlines()), 5)
            self.assertTrue(all(len(a["sha256"]) == 64 for a in data["artifacts"]))

    def test_mismatched_dependency_or_platform_is_rejected(self):
        for options in (
            {"dependency": "0.9.0"},
            {"linux_tag": "manylinux_2_34_x86_64"},
        ):
            with (
                self.subTest(options=options),
                tempfile.TemporaryDirectory() as directory,
            ):
                root = Path(directory)
                self.fixture(root, **options)
                with self.assertRaises(ValueError):
                    manifest(root, "1.0.0")
                self.assertFalse((root / "manifest.json").exists())

    def test_missing_archive_is_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            self.fixture(root)
            next(root.glob("*.zip")).unlink()
            with self.assertRaises(ValueError):
                manifest(root, "1.0.0")
