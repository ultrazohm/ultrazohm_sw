"""Task orchestration and CI release versions; no packages are built or installed."""

import os
import re
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import tasks
from tasks import release_version


class ReleaseVersionTest(unittest.TestCase):
    def test_package_versions_agree(self):
        import tomllib

        root = Path(__file__).resolve().parents[2]

        def load(path):
            return tomllib.loads((root / path).read_text(encoding="utf-8"))

        viewer = load("ultrazohm_dataviewer/pyproject.toml")["project"]
        pins = [
            re.fullmatch(r"ultrazohm-cli==(.+)", dependency)
            for dependency in viewer["dependencies"]
        ]
        pins = [match[1] for match in pins if match]
        self.assertEqual(len(pins), 1, "viewer must pin exactly one ultrazohm-cli")
        versions = {
            "Cargo.toml": load("ultrazohm_cli/Cargo.toml")["package"]["version"],
            "ultrazohm_cli/pyproject.toml": load("ultrazohm_cli/pyproject.toml")[
                "project"
            ]["version"],
            "ultrazohm_dataviewer/pyproject.toml": viewer["version"],
            "viewer ultrazohm-cli pin": pins[0],
        }
        self.assertEqual(len(set(versions.values())), 1, versions)
        self.assertEqual(tasks.base_version(), versions["Cargo.toml"])

    def test_versions_order_by_run_and_mark_prereleases(self):
        self.assertEqual(release_version("0.2.0", "main", 42), "0.2.42")
        self.assertEqual(release_version("0.2.0", "develop", 43), "0.2.43.dev0")
        self.assertEqual(release_version("0.2.0", "feature/x", 44), "0.2.44.dev0")

    def test_versions_sort_above_the_former_post_releases(self):
        from packaging.version import Version

        newest_old = Version("0.1.0.post999999")
        self.assertGreater(Version(release_version("0.1.0", "main", 1)), newest_old)
        self.assertGreater(Version(release_version("0.1.0", "develop", 1)), newest_old)
        self.assertLess(
            Version(release_version("0.1.0", "develop", 5)),
            Version(release_version("0.1.0", "main", 5)),
        )

    def test_packages_share_the_crate_base_version(self):
        import tomllib

        root = Path(__file__).resolve().parents[2]
        for project in ("ultrazohm_cli", "ultrazohm_dataviewer"):
            metadata = tomllib.loads((root / project / "pyproject.toml").read_text())
            self.assertEqual(metadata["project"]["version"], tasks.base_version())

    def test_run_number_offset_raises_patch_numbers(self):
        with patch.object(tasks, "RUN_NUMBER_OFFSET", 100):
            self.assertEqual(release_version("0.2.0", "main", 1), "0.2.101")

    def test_invalid_input(self):
        for base, run in (("0.2", 1), ("0.2.0", 0)):
            with self.assertRaises(ValueError):
                release_version(base, "main", run)


class BuildTaskTest(unittest.TestCase):
    def test_relative_output_is_resolved_from_calling_directory(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory).resolve()
            project = root / "project"
            caller = root / "caller"
            project.mkdir()
            caller.mkdir()
            builder = root / "builder.py"
            builder.write_text(
                "import sys\nfrom pathlib import Path\n"
                'out = Path(sys.argv[sys.argv.index("--out") + 1])\n'
                'out.mkdir(parents=True, exist_ok=True)\n(out / "built.whl").touch()\n'
            )
            original = Path.cwd()
            try:
                os.chdir(caller)

                # Simulate the build tool's working directory, without Rust.
                def run(*command):
                    subprocess.run(
                        [str(arg) for arg in command], cwd=project, check=True
                    )

                with (
                    patch.object(tasks, "run", side_effect=run),
                    patch.object(
                        tasks, "maturin", return_value=[sys.executable, str(builder)]
                    ),
                ):
                    tasks.debug_wheel(SimpleNamespace(out=Path("output with spaces")))
                    sentinel = caller / "output with spaces" / "keep.txt"
                    sentinel.write_text("existing output")
                    tasks.debug_wheel(SimpleNamespace(out=Path("output with spaces")))
                    self.assertEqual(sentinel.read_text(), "existing output")
            finally:
                os.chdir(original)
            self.assertTrue((caller / "output with spaces/built.whl").is_file())
            self.assertFalse((project / "output with spaces").exists())

    def test_checks_clean_up_private_environments(self):
        environments = []

        def fresh(venv, *packages):
            self.assertTrue(venv.parent.is_dir())
            environments.append(venv)
            return tasks.venv_bin(venv, "python")

        def integration(*args):
            self.assertTrue(environments[-1].parent.is_dir())

        with (
            patch.object(tasks, "lint"),
            patch.object(tasks, "format_check"),
            patch.object(tasks, "run"),
            patch.object(tasks, "debug_wheel"),
            patch.object(tasks, "single_wheel", return_value=Path("local.whl")),
            patch.object(tasks, "fresh_venv", side_effect=fresh),
            patch.object(tasks, "integration", side_effect=integration),
        ):
            for _ in range(2):
                tasks.check(SimpleNamespace())
                self.assertFalse(environments[-1].parent.exists())
        self.assertNotEqual(environments[0], environments[1])

    def test_build_tools_use_repository_python_pin(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / ".python-version").write_text("3.12\n")
            with patch.object(tasks, "ROOT", root):
                command = tasks.maturin()
            self.assertEqual(command[command.index("--python") + 1], "3.12")


if __name__ == "__main__":
    unittest.main()


class PublicationPolicyTest(unittest.TestCase):
    def test_event_and_branch_policy(self):
        cases = [
            ("push", "main", "false", "true", "false"),
            ("push", "develop", "false", "true", "true"),
            ("push", "feature/uz_cli_dataviewer_testing", "false", "false", "true"),
            ("pull_request", "main", "true", "false", "true"),
            (
                "workflow_dispatch",
                "feature/uz_cli_dataviewer_testing",
                "true",
                "true",
                "true",
            ),
            ("workflow_dispatch", "develop", "false", "false", "true"),
        ]
        for event, branch, requested, published, prerelease in cases:
            with (
                self.subTest(event=event, branch=branch),
                tempfile.TemporaryDirectory() as directory,
            ):
                output = Path(directory) / "outputs"
                with patch.dict(
                    os.environ,
                    {
                        "GITHUB_EVENT_NAME": event,
                        "GITHUB_REF_NAME": branch,
                        "UZ_PUBLISH_PRERELEASE": requested,
                        "GITHUB_RUN_NUMBER": "99",
                        "GITHUB_OUTPUT": str(output),
                    },
                ):
                    tasks.version(None)
                values = dict(
                    line.split("=", 1) for line in output.read_text().splitlines()
                )
                self.assertEqual(values["publish"], published)
                self.assertEqual(values["prerelease"], prerelease)

    def test_manual_stable_publication_is_rejected(self):
        with patch.dict(
            os.environ,
            {
                "GITHUB_EVENT_NAME": "workflow_dispatch",
                "GITHUB_REF_NAME": "main",
                "UZ_PUBLISH_PRERELEASE": "true",
            },
        ):
            with self.assertRaises(ValueError):
                tasks.version(None)
