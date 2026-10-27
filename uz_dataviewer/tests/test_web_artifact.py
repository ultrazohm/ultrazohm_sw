"""Failure-safe vendoring of the browser ABI wheel."""

import hashlib
import importlib.util
import io
from pathlib import Path
import urllib.request
import zipfile

import pytest


@pytest.fixture
def generator():
    path = Path(__file__).parents[1] / "build/gen_web.py"
    spec = importlib.util.spec_from_file_location("web_artifact_generator", path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def test_invalid_cached_wheel_is_replaced_atomically(generator, tmp_path, monkeypatch):
    directory = tmp_path / "local_wheels"
    directory.mkdir()
    target = directory / generator.IMGUI_BUNDLE_WHEEL
    target.write_bytes(b"partial download")
    data = io.BytesIO()
    with zipfile.ZipFile(data, "w") as archive:
        archive.writestr("imgui_bundle/__init__.py", "")
        archive.writestr("imgui_bundle.dist-info/WHEEL", "Wheel-Version: 1.0")
    payload = data.getvalue()
    monkeypatch.setattr(
        generator, "IMGUI_BUNDLE_WHEEL_SHA256", hashlib.sha256(payload).hexdigest()
    )
    monkeypatch.setattr(urllib.request, "urlopen", lambda *a, **kw: io.BytesIO(payload))
    generator._vendor_wheel(str(tmp_path))
    assert target.read_bytes() == payload
    assert sorted(directory.iterdir()) == [target]
    monkeypatch.setattr(
        urllib.request,
        "urlopen",
        lambda *a, **kw: pytest.fail("valid wheel redownloaded"),
    )
    generator._vendor_wheel(str(tmp_path))


def test_interrupted_wheel_download_does_not_publish_partial_file(
    generator, tmp_path, monkeypatch
):
    class Interrupted(io.BytesIO):
        def read(self, n=-1):
            if self.tell():
                raise OSError("connection lost")
            return super().read(n)

    monkeypatch.setattr(
        urllib.request, "urlopen", lambda *a, **kw: Interrupted(b"partial")
    )
    with pytest.raises(OSError, match="connection lost"):
        generator._vendor_wheel(str(tmp_path))
    assert not list((tmp_path / "local_wheels").iterdir())
