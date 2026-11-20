"""Exercise published setup resolution and switching with real uv installations."""

import importlib.util
import json
import os
import shutil
import sys
import tempfile
import unittest
import zipfile
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]


def load_setup(project):
    spec = importlib.util.spec_from_file_location(
        project + "_setup", ROOT / project / "tools/setup_env.py"
    )
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


SETUPS = {
    "cli": load_setup("ultrazohm_cli"),
    "viewer": load_setup("ultrazohm_dataviewer"),
}


def wheel(directory, name, version, dependencies=()):
    normalized = name.replace("-", "_")
    info = f"{normalized}-{version}.dist-info"
    content = {
        f"{normalized}/__init__.py": 'def main():\n    print("fixture application")\n',
        f"{info}/METADATA": (
            f"Metadata-Version: 2.1\nName: {name}\nVersion: {version}\n"
            + "".join(f"Requires-Dist: {d}\n" for d in dependencies)
        ),
        f"{info}/WHEEL": "Wheel-Version: 1.0\nGenerator: setup-test\nRoot-Is-Purelib: true\nTag: py3-none-any\n",
        f"{info}/entry_points.txt": f"[console_scripts]\n{name} = {normalized}:main\n",
    }
    content[f"{info}/RECORD"] = "".join(
        f"{path},,\n" for path in [*content, f"{info}/RECORD"]
    )
    path = directory / f"{normalized}-{version}-py3-none-any.whl"
    with zipfile.ZipFile(path, "w") as archive:
        for entry, value in content.items():
            archive.writestr(entry, value)


@unittest.skipUnless(shutil.which("uv"), "uv is required for real installer tests")
class PublishedSetupTest(unittest.TestCase):
    def test_channels_and_application_switching(self):
        with tempfile.TemporaryDirectory(prefix="uz real setup ") as directory:
            root = Path(directory)
            (root / ".python-version").write_text(sys.executable)
            for project in ("ultrazohm_cli", "ultrazohm_dataviewer"):
                (root / project / "tools").mkdir(parents=True)
                for name in (
                    "tasks.py",
                    "tools/setup_env.py",
                    "pyproject.toml",
                    "Cargo.lock",
                    "uv.lock",
                ):
                    (root / project / name).write_text("fixture")
            viewer = root / "ultrazohm_dataviewer"
            viewer.mkdir(exist_ok=True)
            (viewer / "pyproject.toml").write_text("fixture")
            (viewer / "uv.lock").write_text("fixture")
            wheels = root / "wheels"
            wheels.mkdir()
            wheel(wheels, "fixture-gui", "1.0.0")
            for version in ("1.0.0", "2.0.0.dev0"):
                wheel(wheels, "ultrazohm-cli", version)
                wheel(
                    wheels,
                    "ultrazohm-dataviewer",
                    version,
                    [f"ultrazohm-cli=={version}", "fixture-gui==1.0.0"],
                )
            config = root / "uv-test.toml"
            config.write_text("[pip]\nno-index = true\n")
            env = {
                "UV_CONFIG_FILE": str(config),
                "UV_FIND_LINKS": str(wheels),
                "UV_CACHE_DIR": str(root / "cache"),
                "UV_PYTHON_DOWNLOADS": "never",
            }
            with (
                patch.object(SETUPS["cli"], "ROOT", root),
                patch.object(SETUPS["viewer"], "ROOT", root),
                patch.dict(os.environ, env),
            ):
                for source, app, expected in [
                    ("stable", "cli", "1.0.0"),
                    ("prerelease", "viewer", "2.0.0.dev0"),
                    ("stable", "viewer", "1.0.0"),
                    ("prerelease", "cli", "2.0.0.dev0"),
                ]:
                    with self.subTest(source=source, app=app):
                        tasks = SETUPS[app]
                        tasks.setup(source)
                        state = json.loads((root / ".venv/.uz-setup.json").read_text())
                        versions = state["versions"]
                        self.assertEqual(versions["ultrazohm-cli"], expected)
                        self.assertEqual("fixture-gui" in versions, app == "viewer")
                        self.assertEqual(
                            "ultrazohm-dataviewer" in versions, app == "viewer"
                        )
                        if app == "viewer":
                            self.assertEqual(versions["ultrazohm-dataviewer"], expected)
                        self.assertEqual(
                            tasks.executable("ultrazohm-dataviewer").exists(),
                            app == "viewer",
                        )
