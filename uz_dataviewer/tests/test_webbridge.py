"""Tests for the web array-loading path (build a Run from typed arrays).

Mirrors what the browser's streaming CSV parser hands to Python: raw channel
headers + float arrays, with no Arrow text parse. No browser needed.
"""

from __future__ import annotations

import os
import sys

import numpy as np

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))

from uz_dataviewer import webbridge  # noqa: E402
from uz_dataviewer.state import AppState  # noqa: E402


def test_load_columns_builds_run_from_arrays():
    state = AppState()
    webbridge.register_state(state)

    t = np.linspace(11.979, 13.979, 1000)
    names = ["CH8=8)ia", "CH15=15)Speed_rpm"]
    arrays = [np.sin(t).astype(np.float32), (1000 + np.cos(t)).astype(np.float32)]
    webbridge.load_columns("Log_stream.csv", names, arrays, t)

    run = state.registry.get(1)
    assert run is not None
    assert run.label == "Log_stream.csv"
    assert run.n_rows == 1000
    # Headers cleaned to friendly names; unit detected; dtypes normalised.
    assert set(run.signals) == {"ia", "Speed_rpm"}
    assert run.signals["Speed_rpm"].unit == "rpm"
    assert run.signals["ia"].y.dtype == np.float32
    assert run.time.dtype == np.float64
    assert abs(float(run.time[0]) - 11.979) < 1e-6


def test_load_columns_no_state_is_noop():
    webbridge.register_state(None)
    # Must not raise when no app state is registered.
    webbridge.load_columns("x.csv", ["a"], [np.zeros(3, np.float32)], np.zeros(3))


def test_save_and_download_runs_command_then_downloads(monkeypatch):
    # Web export path: write /tmp/<name> via the emit callback, then hand it to download().
    state = AppState()
    webbridge.register_state(state)
    calls: dict = {}
    monkeypatch.setattr(webbridge, "IS_WEB", True)
    monkeypatch.setattr(webbridge, "download", lambda path, name: calls.update(download=(path, name)))

    webbridge.save_and_download(state, "plot_1.csv", lambda path: calls.update(emit=path))

    assert calls["emit"] == "/tmp/plot_1.csv"
    assert calls["download"] == ("/tmp/plot_1.csv", "plot_1.csv")


def test_save_and_download_native_is_noop(monkeypatch):
    # On native the caller drives an OS save dialog; the helper must do nothing.
    state = AppState()
    monkeypatch.setattr(webbridge, "IS_WEB", False)
    called: list = []
    webbridge.save_and_download(state, "x.csv", lambda path: called.append(path))
    assert called == []


def test_save_and_download_surfaces_errors(monkeypatch):
    # A failing command goes to the console, not up the call stack.
    state = AppState()
    webbridge.register_state(state)
    monkeypatch.setattr(webbridge, "IS_WEB", True)
    monkeypatch.setattr(webbridge, "download", lambda *a: None)

    def boom(path):
        raise ValueError("export failed")

    webbridge.save_and_download(state, "x.csv", boom)  # must not raise
    errors = [e.message for e in state.console._entries if e.level == "ERROR"]
    assert any("export failed" in m for m in errors)
