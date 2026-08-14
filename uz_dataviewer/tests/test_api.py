"""Tests for the headless library facade (uz_dataviewer.api)."""

from __future__ import annotations

import os
import subprocess
import sys

import numpy as np

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))

import uz_dataviewer as uz  # noqa: E402
from uz_dataviewer import api  # noqa: E402


def _write_csv(tmp_path, fs=2000.0, n=4000, freq=50.0):
    t = np.arange(n) / fs
    ia = np.sin(2 * np.pi * freq * t)
    ib = np.cos(2 * np.pi * 20 * t)
    path = tmp_path / "Log_api.csv"
    lines = ["time;CH8=8)ia;CH9=9)ib;"]
    lines += [f"{t[i]:.6f};{ia[i]:.6f};{ib[i]:.6f};" for i in range(n)]
    path.write_text("\n".join(lines) + "\n")
    return path, t, ia


def test_read_returns_dataset(tmp_path):
    path, t, _ = _write_csv(tmp_path)
    data = uz.read(str(path))
    assert isinstance(data, api.Dataset)
    assert data.names == ["ia", "ib"]
    assert "ia" in data and len(data) == 2
    assert data.time.shape[0] == t.shape[0]
    np.testing.assert_allclose(data["ia"][:5], np.sin(2 * np.pi * 50 * t[:5]), atol=1e-3)
    df = data.to_dataframe()
    assert list(df.columns) == ["time", "ia", "ib"]
    assert len(df) == t.shape[0]


def test_fft_and_fft_frame_recover_tone(tmp_path):
    path, t, ia = _write_csv(tmp_path, freq=50.0)
    res = uz.fft(t, ia)  # full span by default
    assert res.ok
    assert abs(float(res.freqs[np.argmax(res.mag)]) - 50.0) < 2.0

    frame = uz.fft_frame(t, ia)
    assert list(frame.columns) == ["frequency", "amplitude"]
    peak = frame.loc[frame["amplitude"].idxmax()]
    assert abs(float(peak["frequency"]) - 50.0) < 2.0


def test_fft_frame_raises_on_empty():
    import pytest

    with pytest.raises(ValueError):
        uz.fft_frame(np.array([]), np.array([]))


def test_kinds_includes_builtins():
    assert set(uz.kinds()) >= {"fft", "math", "filter", "shift"}


def test_node_filter_attenuates_high_freq():
    t = np.linspace(0.0, 1.0, 4000)  # fs = 4000 Hz
    low = np.sin(2 * np.pi * 5 * t)
    sig = (low + np.sin(2 * np.pi * 400 * t)).astype(np.float32)
    t_out, y_out, info = uz.node("filter", (t, sig), type="low", cutoff=40, taps=201)
    interior = slice(300, -300)
    assert np.std(y_out[interior]) < 0.8  # 400 Hz term gone
    assert "low-pass" in info


def test_node_math_add_doubles():
    t, y = np.linspace(0, 1, 100), np.sin(np.linspace(0, 1, 100)).astype(np.float32)
    _, summed, _ = uz.node("math", (t, y), (t, y), op="add")
    np.testing.assert_allclose(summed, 2.0 * y, rtol=1e-5)


def test_node_unknown_kind_raises():
    import pytest

    t = np.linspace(0, 1, 10)
    with pytest.raises(ValueError, match="unknown node kind"):
        uz.node("nope", (t, t))


def test_filter_and_math_wrappers():
    t = np.linspace(0.0, 1.0, 2000)
    y = np.sin(2 * np.pi * 5 * t).astype(np.float32)
    _, yf, info = uz.api.filter(t, y, type="low", cutoff=50, taps=101)
    assert yf.shape == y.shape and "low-pass" in info
    _, ys, _ = uz.api.math((t, y), op="scale", k="2")
    np.testing.assert_allclose(ys, np.asarray(y, float) * 2, rtol=1e-5)


def test_import_is_gui_free():
    """Regression for the lazy-import fix: importing the package (and a 'pure'
    submodule) must NOT pull in imgui_bundle. Run in a fresh interpreter because
    other tests in this process import the GUI for headless rendering."""
    code = (
        "import sys; "
        "import uz_dataviewer, uz_dataviewer.analysis, uz_dataviewer.nodes; "
        "assert 'imgui_bundle' not in sys.modules, "
        "'imgui_bundle was imported by a headless import'; "
        "print('ok')"
    )
    src = os.path.join(os.path.dirname(__file__), "..", "src")
    env = dict(os.environ, PYTHONPATH=src + os.pathsep + os.environ.get("PYTHONPATH", ""))
    out = subprocess.run(
        [sys.executable, "-c", code], capture_output=True, text=True, env=env
    )
    assert out.returncode == 0, out.stderr
    assert "ok" in out.stdout
