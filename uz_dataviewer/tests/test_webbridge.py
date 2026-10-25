"""Tests for the web array-loading path (build a Run from typed arrays).

Mirrors what the browser's streaming CSV parser hands to Python: raw channel
headers + float arrays, with no Arrow text parse. No browser needed.
"""

from __future__ import annotations

import os
from pathlib import Path
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
    # Web exports use a fresh temporary directory, removed after download.
    state = AppState()
    webbridge.register_state(state)
    calls: dict = {}
    monkeypatch.setattr(webbridge, "IS_WEB", True)
    monkeypatch.setattr(webbridge, "download", lambda path, name: calls.update(download=(path, name)))

    webbridge.save_and_download(state, "plot_1.csv", lambda path: calls.update(emit=path))

    assert Path(calls["emit"]).name == "plot_1.csv"
    assert calls["download"] == (calls["emit"], "plot_1.csv")
    assert not Path(calls["emit"]).parent.exists()


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


def test_failed_panel_export_never_downloads_previous_data(app_state, monkeypatch):
    from uz_dataviewer.panels.fft import FftPanel
    state = app_state
    state.backend = 'pyarrow'
    state.add_run_from_arrays('input', 'input', np.arange(16)/16, {'a': np.sin(np.arange(16))}, {})
    state.fft.sources = [(1, 'a')]
    state.fft.follow_plot = -1
    panel = FftPanel()
    downloads, paths = [], []
    monkeypatch.setattr(webbridge, 'IS_WEB', True)
    monkeypatch.setattr(webbridge, 'download', lambda path, name: downloads.append(Path(path).read_text()))

    def export(path):
        paths.append(path)
        return panel._emit(state, 'fft_export', path)

    webbridge.save_and_download(state, 'fft.csv', export)
    assert len(downloads) == 1
    state.fft.follow_plot = 0
    state.fft.x_min, state.fft.x_max = 0, .01
    webbridge.save_and_download(state, 'fft.csv', export)
    assert len(downloads) == 1
    assert paths[0] != paths[1]
    assert all(not Path(path).exists() for path in paths)
    assert any('input' in e.message and 'too short' in e.message for e in state.console._entries)


def test_generated_uploads_keep_same_name_recordings_distinct(app_state, tmp_path):
    import importlib.util
    import json
    import shutil
    import subprocess
    import pytest
    from uz_dataviewer.session import to_dict, apply_dict
    node = shutil.which('node')
    if node is None:
        pytest.skip('Node.js required for generated upload handler')
    spec = importlib.util.spec_from_file_location('gen_web_upload', Path(__file__).parents[1] / 'build/gen_web.py')
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    html = module.build_html()
    start = html.index('  let nextUploadId')
    end = html.index('  // Stream-parse', start)
    harness = r'''
const fs = require('node:fs');
const root = process.argv[2];
fs.mkdirSync(root + '/uploads');
const paths = [];
const pyodide = {FS: {
  mkdir: path => fs.mkdirSync(root + path),
  writeFile: (path, data) => fs.writeFileSync(root + path, data)
}};
function pyLoad(path) { paths.push(root + path); }
(async () => {
  for (const value of [10, 20]) {
    const file = new Blob([`time;a\n0;${value}\n1;${value}\n`]);
    file.name = 'same.csv';
    await loadFull(file);
  }
  console.log(JSON.stringify(paths));
})().catch(error => { console.error(error); process.exitCode = 1; });
'''
    script = tmp_path / 'upload.cjs'
    script.write_text(html[start:end] + harness)
    result = subprocess.run([node, str(script), str(tmp_path)], check=True, capture_output=True, text=True, timeout=15)
    paths = json.loads(result.stdout)
    assert len(set(paths)) == 2
    state = app_state
    state.backend, state.loading_mode = 'pyarrow', 'memory'
    for path in paths:
        state.load_sync(path)
    assert [r.label for r in state.registry.runs] == ['same.csv', 'same.csv']
    apply_dict(state, to_dict(state))
    assert [r.signals['a'].y[0] for r in state.registry.runs] == [10, 20]


def test_uploaded_files_use_the_same_loading_policy_as_commands(app_state, tmp_path, monkeypatch):
    state = app_state
    monkeypatch.setattr(webbridge, 'IS_WEB', True)
    monkeypatch.setattr(webbridge, '_active_state', state)
    state.backend = 'pyarrow'
    path = tmp_path / 'upload.csv'
    path.write_text('time;a\n0;10\n1;20\n')
    for mode in ('memory', 'lazy'):
        for disk_cache in (False, True):
            state.commands.execute(state, 'loading_mode', [mode])
            state.commands.execute(state, 'disk_cache', [disk_cache])
            webbridge.load_uploaded(str(path))
            uploaded = state.registry.runs[-1]
            state.commands.execute(state, 'load', [str(path)])
            commanded = state.registry.runs[-1]
            assert uploaded.storage_mode == commanded.storage_mode == mode
            assert uploaded.backend == commanded.backend == 'pyarrow'
            assert getattr(uploaded.source, 'disk_cache', False) == (mode == 'lazy' and disk_cache)
            assert getattr(commanded.source, 'disk_cache', False) == (mode == 'lazy' and disk_cache)
            t, values = uploaded.read_window(['a'], 0, 1)
            np.testing.assert_array_equal(t, [0, 1])
            np.testing.assert_array_equal(values['a'], [10, 20])
