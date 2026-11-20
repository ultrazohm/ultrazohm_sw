"""Release staging must produce matching packages without mutating sources."""

import sys
import tempfile
import tomllib
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from release_build import staged_project


class StagingTest(unittest.TestCase):
    def test_viewer_version_and_dependency_are_stamped_only_in_stage(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory) / "viewer"
            project.mkdir()
            original = '[project]\nname="ultrazohm-dataviewer"\nversion = "0.1.0"\ndependencies=["ultrazohm-cli==0.1.0"]\n'
            (project / "pyproject.toml").write_text(original)
            (project / "uv.lock").write_text("do not copy or alter")
            (project / "src").mkdir()
            (project / "src" / "asset.txt").write_text("asset")
            with staged_project(project, "0.1.88.dev0") as (stage, version):
                data = tomllib.loads((stage / "pyproject.toml").read_text())["project"]
                self.assertEqual(data["version"], version)
                self.assertEqual(data["dependencies"], ["ultrazohm-cli==0.1.88.dev0"])
                self.assertFalse((stage / "uv.lock").exists())
                self.assertEqual((stage / "src" / "asset.txt").read_text(), "asset")
            self.assertFalse(stage.exists())
            self.assertEqual((project / "pyproject.toml").read_text(), original)
            self.assertEqual((project / "uv.lock").read_text(), "do not copy or alter")

    def test_invalid_version_fails_before_build(self):
        project = Path(__file__).resolve().parents[1]
        with self.assertRaises(ValueError):
            with staged_project(project, "../../bad"):
                self.fail("invalid version accepted")
