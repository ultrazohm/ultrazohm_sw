"""Save / restore the GUI state, and export / replay it as a command script.

Two complementary formats, both exposed as commands (see :mod:`commands`):

* **JSON snapshot** (``save_state`` / ``load_state``) -- the exact view: grid,
  per-cell signal assignments, plot types, link/downsample settings, FFT/Histogram config
  and the set of loaded files. Restores to the same picture, including which
  files to reload.
* **Command script** (``export_script`` / ``run_script``) -- a human-readable,
  editable ``.uzscript`` of canonical commands (``load(...)``, ``set_grid(...)``,
  ``add_signal(...)`` ...) that reproduces the session when replayed.

JSON references use explicit recording/node keys, remapped when restoring.
Scripts restore transactionally and reference explicit recording/node identities.
"""

from __future__ import annotations

import json
import math
from typing import TYPE_CHECKING

from .loader import unique_name
from .state import PlotType, XyStyle

if TYPE_CHECKING:  # pragma: no cover - typing only
    from .state import AppState, SubplotCell

SCHEMA_VERSION = 4
SCRIPT_HEADER = "# UltraZohm Data Viewer session script v4"


def ensure_extension(path: str, ext: str) -> str:
    """Return ``path`` with ``ext`` (including the leading dot) appended if missing.

    Native save dialogs (``portable_file_dialogs``) don't reliably add the filter's
    extension when the user edits the filename, so saved files can land without one.
    Matching is case-insensitive; an empty path is returned unchanged.
    """
    if path and not path.lower().endswith(ext.lower()):
        return path + ext
    return path


# -- helpers ------------------------------------------------------------------
def _ref_to_saved(state, ref):
    if ref is None:
        return None
    run = state.registry.get(ref[0])
    if run is None:
        return None
    if run.derived:
        for node in state.nodes.ordered():
            if node.out_run_id == run.id:
                return [f"node:{node.id}", ref[1]]
        raise ValueError(f"Derived run {run.label!r} has no owning node")
    return [f"run:{run.id}", ref[1]]


def clear_session(state):
    """Reset recording identities and consumers before restoring a complete session."""
    replacement = _replacement_state(state)
    for field in ("backend", "loading_mode", "disk_cache", "max_points", "link_x"):
        setattr(replacement, field, getattr(state, field))
    replacement.registry.cache.limit = state.registry.cache.limit
    state.replace_session(replacement)


def _nodes_to_list(state: "AppState") -> list[dict]:
    out = []
    for node in state.nodes.ordered():
        run = state.registry.get(node.out_run_id)
        out.append(
            {
                "id": node.id,
                "kind": node.kind,
                "name": node.name,
                "params": dict(node.params),
                "inputs": list(node.inputs),
                "ref": _ref_to_saved(state, node.ref) if node.ref else None,
                "pos": list(node.pos),
                "output_view": {"active": run.active, "time_origin": run.time_origin} if run else None,
            }
        )
    return out


# -- JSON snapshot ------------------------------------------------------------
def to_dict(state: "AppState") -> dict:
    _check_reloadable(state)
    cells = []
    for cell in state.cells:
        cells.append(
            {
                "signals": [_ref_to_saved(state, r) for r in cell.signals],
                "type": cell.plot_type.value,
                "x_lim": cell.pending_x_lim or cell.x_lim or state.plot_x_ranges.get(len(cells) + 1),
                "y_lim": cell.pending_y_lim or cell.y_lim,
                "show_samples": cell.show_samples,
                "spy": cell.spy,
                "spy_rect": list(cell.spy_rect) if cell.spy_rect else None,
                "cursors": cell.cursors,
                "cursor_x": list(cell.cursor_x) if cell.cursor_x else None,
                "export_relative": cell.export_relative,
                "xy_source": _ref_to_saved(state, cell.xy_source),
                "xy_style": cell.xy_style.value,
                "y2": [_ref_to_saved(state, r) for r in cell.y2_signals],
            }
        )
    return {
        "version": SCHEMA_VERSION,
        "grid": [state.rows, state.cols],
        "link_x": state.link_x,
        "shared_x": state.shared_x,
        "max_points": state.max_points,
        "loading_mode": state.loading_mode,
        "disk_cache": state.disk_cache,
        "backend": state.backend,
        "cache_budget_mb": state.registry.cache.limit // 1024**2,
        "runs": [{"key": f"run:{r.id}", "path": r.path,
                  "mode": r.storage_mode,
                  "backend": r.backend, "disk_cache": getattr(r.source, "disk_cache", False),
                  "time_origin": r.time_origin, "active": r.active}
                 for r in state.registry.runs if not r.derived],
        "nodes": _nodes_to_list(state),
        "cells": cells,
        "fft": {
            "sources": [_ref_to_saved(state, r) for r in state.fft.sources],
            "follow_plot": state.fft.follow_plot,
            "x_min": state.fft.x_min,
            "x_max": state.fft.x_max,
            "remove_dc": state.fft.remove_dc,
            "window": state.fft.window,
            "log_x": state.fft.log_x,
            "log_y": state.fft.log_y,
        },
        "histogram": {
            "sources": [_ref_to_saved(state, r) for r in state.histogram.sources],
            "follow_plot": state.histogram.follow_plot,
            "x_min": state.histogram.x_min,
            "x_max": state.histogram.x_max,
            "bins": state.histogram.bins,
        },
    }


def save_state(state: "AppState", path: str) -> None:
    data = to_dict(state)
    with open(path, "w", encoding="utf-8") as fh:
        json.dump(data, fh, indent=2)


def load_state(state: "AppState", path: str) -> None:
    with open(path, encoding="utf-8") as fh:
        data = json.load(fh)
    apply_dict(state, data)


def _session_backend(state, backend):
    from . import webbridge
    if webbridge.IS_WEB and backend == "polars":
        state.console.warn("Polars session opened with PyArrow in the browser.")
        return "pyarrow"
    return backend


def _replacement_state(state):
    from .state import AppState
    replacement = AppState()
    replacement.cache_dir = state.cache_dir
    return replacement


def apply_dict(state: "AppState", data: dict) -> None:
    replacement = _replacement_state(state)
    try:
        _apply_dict(replacement, data)
    except BaseException:
        replacement.shutdown()
        raise
    state.replace_session(replacement)


def _apply_dict(state: "AppState", data: dict) -> None:
    if data.get("version") != SCHEMA_VERSION:
        raise ValueError(f"Unsupported session version; expected {SCHEMA_VERSION}. Recreate old sessions.")
    specs = data.get("runs", [])
    if len({r["key"] for r in specs}) != len(specs):
        raise ValueError("Duplicate run keys in session")
    if "backend" in data:
        state.commands.execute(state, "backend", [_session_backend(state, data["backend"])])
    for command, field in (("disk_cache", "disk_cache"), ("loading_mode", "loading_mode"), ("cache_budget", "cache_budget_mb")):
        if field in data:
            state.commands.execute(state, command, [data[field]])
    run_ids = {}
    mode, backend, disk_cache = state.loading_mode, state.backend, state.disk_cache
    try:
        for spec in specs:
            state.loading_mode = spec["mode"]
            state.backend = _session_backend(state, spec["backend"])
            state.disk_cache = spec["disk_cache"]
            run = state.load_sync(spec["path"])
            if run is None:
                raise ValueError(f"Cannot restore recording: {spec['path']}")
            run.set_time_origin(spec.get("time_origin"))
            run.active = spec.get("active", True)
            run_ids[spec["key"]] = run.id
    finally:
        state.loading_mode, state.backend, state.disk_cache = mode, backend, disk_cache

    rows, cols = data.get("grid", [state.rows, state.cols])
    if int(rows) < 1 or int(cols) < 1:
        raise ValueError("Session grid dimensions must be positive")
    state.set_grid(int(rows), int(cols))
    state.link_x = bool(data.get("link_x", state.link_x))
    state.shared_x = _limits(data.get("shared_x"))
    state.max_points = int(data.get("max_points", state.max_points))
    if state.max_points < 2:
        raise ValueError("Session display budget must be at least two points")

    def _resolve(labelled) -> tuple[int, str] | None:
        if not labelled:
            return None
        key = labelled[0]
        if key.startswith("node:"):
            node = state.nodes.get(int(key.split(":", 1)[1]))
            run_id = node.out_run_id if node is not None else None
        else:
            run_id = run_ids.get(key)
        if run_id is None or state.registry.get_signal(run_id, labelled[1]) is None:
            raise ValueError(f"Cannot restore signal reference: {labelled}")
        return run_id, labelled[1]

    # Rebuild the node graph and evaluate it *before* resolving cell/analysis
    # assignments, so any references to a derived run (label == node name) resolve.
    _restore_nodes(state, data.get("nodes", []), _resolve)

    for i, spec in enumerate(data.get("cells", [])):
        if i >= len(state.cells):
            break
        cell = state.cells[i]
        cell.signals = [r for r in (_resolve(s) for s in spec.get("signals", [])) if r is not None]
        try:
            cell.plot_type = PlotType(spec.get("type", PlotType.LINE.value))
        except ValueError:
            cell.plot_type = PlotType.LINE
        cell.show_samples = bool(spec.get("show_samples", False))
        cell.spy = bool(spec.get("spy", False))
        cell.spy_rect = tuple(spec["spy_rect"]) if spec.get("spy_rect") else None
        cell.cursors = bool(spec.get("cursors", False))
        cell.cursor_x = tuple(spec["cursor_x"]) if spec.get("cursor_x") else None
        cell.export_relative = bool(spec.get("export_relative", False))
        cell.xy_source = _resolve(spec.get("xy_source"))
        try:
            cell.xy_style = XyStyle(spec.get("xy_style", XyStyle.LINE.value))
        except ValueError:
            cell.xy_style = XyStyle.LINE
        cell.y2_signals = [r for r in (_resolve(s) for s in spec.get("y2", [])) if r is not None]
        cell.pending_x_lim = _limits(spec.get("x_lim"))
        cell.x_lim = cell.pending_x_lim
        cell.pending_y_lim = _limits(spec.get("y_lim"))
        cell.y_lim = cell.pending_y_lim
        if cell.pending_x_lim and cell.plot_type is not PlotType.XY:
            state.plot_x_ranges[i + 1] = cell.pending_x_lim
        cell.fit_pending = True

    fft = data.get("fft") or {}
    state.fft.sources = [r for r in (_resolve(s) for s in fft.get("sources", [])) if r is not None]
    state.fft.follow_plot = state.validate_follow_plot(int(fft.get("follow_plot", state.fft.follow_plot)))
    state.fft.x_min = float(fft.get("x_min", state.fft.x_min))
    state.fft.x_max = float(fft.get("x_max", state.fft.x_max))
    state.fft.remove_dc = bool(fft.get("remove_dc", state.fft.remove_dc))
    state.fft.window = bool(fft.get("window", state.fft.window))
    state.fft.log_x = bool(fft.get("log_x", state.fft.log_x))
    state.fft.log_y = bool(fft.get("log_y", state.fft.log_y))

    hist = data.get("histogram") or {}
    state.histogram.sources = [r for r in (_resolve(s) for s in hist.get("sources", [])) if r is not None]
    state.histogram.follow_plot = state.validate_follow_plot(int(hist.get("follow_plot", state.histogram.follow_plot)))
    state.histogram.x_min = float(hist.get("x_min", state.histogram.x_min))
    state.histogram.x_max = float(hist.get("x_max", state.histogram.x_max))
    state.histogram.bins = int(hist.get("bins", state.histogram.bins))

    # Restoring sources alone leaves the windows blank until the user clicks
    # Compute (the panels only ever compute on request). Flag a recompute so a
    # restored session draws its spectra/bins straight away -- matching what the
    # fft_source/hist_source commands do when a script is replayed.
    state.fft.compute_requested = bool(state.fft.sources)
    state.histogram.compute_requested = bool(state.histogram.sources)


def _limits(value):
    if value is None:
        return None
    lo, hi = map(float, value)
    if not math.isfinite(lo) or not math.isfinite(hi) or hi <= lo:
        raise ValueError("Axis limits must be finite and increasing")
    return lo, hi


def _restore_nodes(state: "AppState", specs: list, resolve) -> None:
    """Rebuild the node graph from a snapshot (preserving ids) and evaluate it."""
    from .nodes import NodeGraph, evaluate

    state.nodes = NodeGraph()
    for spec in sorted(specs, key=lambda s: int(s["id"])):
        saved_ref = spec.get("ref")
        if spec.get("kind") == "source" and saved_ref and saved_ref[0].startswith("node:"):
            raise ValueError("Derived signals must be connected with node_link, not source nodes")
        ref = resolve(saved_ref) if spec.get("kind") == "source" else None
        # allow_unknown keeps a node whose plugin isn't installed as a placeholder
        # (params + links preserved) rather than dropping it.
        node = state.nodes.add(
            spec["kind"], name=spec.get("name"), ref=ref, node_id=int(spec["id"]),
            allow_unknown=True,
        )
        node.params = dict(spec.get("params", {}))
        pos = spec.get("pos") or (0.0, 0.0)
        node.pos = (float(pos[0]), float(pos[1]))
    for spec in specs:  # links once every node exists
        dst = int(spec["id"])
        for slot, in_id in enumerate(spec.get("inputs", [])):
            if in_id is not None:
                state.nodes.link(int(in_id), dst, slot)
    if state.nodes.nodes:
        evaluate(state)
    for spec in specs:
        view = spec.get("output_view")
        run = state.registry.get(state.nodes.get(int(spec["id"])).out_run_id)
        if run is not None and view is not None:
            run.active = bool(view["active"])
            run.set_time_origin(view["time_origin"])


# -- command script -----------------------------------------------------------
def _arg(token: str) -> str:
    from .commands import _fmt_str

    return _fmt_str(token)


def _check_reloadable(state):
    for run in state.registry.runs:
        if not run.derived and not run.reloadable:
            raise ValueError(f"Cannot save session: {run.label} has no backing file. Export its data first.")


def to_script(state: "AppState") -> list[str]:
    """Render commands from the same canonical snapshot used by JSON saves."""
    data = to_dict(state)
    lines = [SCRIPT_HEADER]

    def emit(command, *values):
        args = [_arg(str(v).lower() if isinstance(v, bool) else str(v)) for v in values]
        lines.append(f"{command}({', '.join(args)})")

    run_ids = {run['key']: f"run_{i}" for i, run in enumerate(data['runs'], 1)}
    node_ids = {node['id']: i for i, node in enumerate(data['nodes'], 1)}

    def ref(saved):
        key, channel = saved
        if key.startswith('node:'):
            return f"node_output_{node_ids[int(key.split(':')[1])]}", channel
        return run_ids[key], channel

    def settings(spec):
        for command, field in (('disk_cache', 'disk_cache'), ('backend', 'backend'),
                               ('loading_mode', 'loading_mode')):
            emit(command, spec[field])

    emit('clear_session')
    settings(data)
    emit('cache_budget', data['cache_budget_mb'])
    for run in data['runs']:
        settings(dict(run, loading_mode=run['mode']))
        args = [run['path']]
        if run['time_origin'] is not None:
            args.append(run['time_origin'])
        emit('load', *args)
        emit('set_active', run_ids[run['key']], run['active'])
    settings(data)

    nodes = data['nodes']
    for node in nodes:
        nid = f"node_{node_ids[node['id']]}"
        if node['kind'] == 'source':
            if node['ref'] is None:
                raise ValueError(f"{node['name']}: source recording is missing")
            if node['ref'][0].startswith('node:'):
                raise ValueError('Derived signals must be connected with node_link, not source nodes')
            emit('node_source', *ref(node['ref']))
        else:
            emit('node_add', node['kind'])
        for key, value in node['params'].items():
            emit('node_set', nid, key, value)
        emit('node_pos', nid, *node['pos'])
    # Free default names before restoring names with gaps or swaps.
    prefix = '__restore_'
    while any(node['name'].startswith(prefix) for node in nodes):
        prefix += '_'
    for node in nodes:
        nid = node_ids[node['id']]
        emit('node_rename', f'node_{nid}', f'{prefix}{nid}')
    for node in nodes:
        nid = f"node_{node_ids[node['id']]}"
        emit('node_rename', nid, node['name'])
        for slot, upstream in enumerate(node['inputs']):
            if upstream is not None:
                emit('node_link', f'node_{node_ids[upstream]}', nid, slot)
    if nodes:
        emit('node_eval')
    for node in nodes:
        view = node['output_view']
        if view is not None:
            output = f"node_output_{node_ids[node['id']]}"
            emit('set_active', output, view['active'])
            if view['time_origin'] is not None:
                emit('normalize_time', output, view['time_origin'])

    emit('set_grid', *data['grid'])
    emit('set_max_points', data['max_points'])
    emit('link_x', data['link_x'])
    for i, cell in enumerate(data['cells'], 1):
        plot = f'plot_{i}'
        for saved in cell['signals']:
            if saved is not None:
                emit('add_signal', plot, *ref(saved))
        if cell['xy_source'] is not None:
            emit('set_xy', plot, *ref(cell['xy_source']))
        emit('set_plot_type', plot, cell['type'])
        emit('set_xy_style', plot, cell['xy_style'])
        for saved in cell['y2']:
            if saved is not None:
                emit('set_axis', plot, *ref(saved), 'right')
        emit('show_samples', plot, cell['show_samples'])
        if cell['spy_rect'] is not None:
            emit('set_spy_rect', plot, *cell['spy_rect'])
        emit('spy', plot, cell['spy'])
        if cell['cursor_x'] is not None:
            emit('set_cursors', plot, *cell['cursor_x'])
        emit('cursors', plot, cell['cursors'])
        emit('set_export_relative', plot, cell['export_relative'])
        for axis in ('x', 'y'):
            if cell[f'{axis}_lim'] is not None:
                emit(f'set_{axis}_lim', plot, *cell[f'{axis}_lim'])
    for prefix, cfg in (('fft', data['fft']), ('hist', data['histogram'])):
        for saved in cfg['sources']:
            if saved is not None:
                emit(f'{prefix}_source', *ref(saved))
        # Set the custom range even when another window is selected, so it is
        # preserved when the user switches back to Custom after restoration.
        follow = cfg['follow_plot']
        emit(f'{prefix}_follow', 'full' if follow == -1 else 'custom' if follow == 0 else f'plot_{follow}')
        emit(f'{prefix}_range', cfg['x_min'], cfg['x_max'])
    for command, field in (('fft_remove_dc', 'remove_dc'), ('fft_hann', 'window'),
                           ('fft_logx', 'log_x'), ('fft_logy', 'log_y')):
        emit(command, data['fft'][field])
    emit('hist_bins', data['histogram']['bins'])
    return lines


def export_script(state: "AppState", path: str) -> None:
    lines = to_script(state)
    with open(path, "w", encoding="utf-8") as fh:
        fh.write("\n".join(lines) + "\n")


def run_script(state: "AppState", path: str) -> int:
    """Replay a script file line by line; returns the number of commands run."""
    with open(path, encoding="utf-8") as fh:
        lines = fh.readlines()
    exported = bool(lines and lines[0].strip().startswith("# UltraZohm Data Viewer session script"))
    if exported and lines[0].strip() != SCRIPT_HEADER:
        raise ValueError("Unsupported session script version; recreate old exported sessions.")
    target = _replacement_state(state) if exported else state
    count = 0
    try:
        for line in lines:
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            from .commands import parse_call
            name, args = parse_call(line)
            target.commands.execute(target, name, args)
            count += 1
    except BaseException:
        if exported:
            target.shutdown()
        raise
    if exported:
        state.replace_session(target)
    return count


# -- data export --------------------------------------------------------------
def _write_csv(columns, path, backend):
    if backend == "polars":
        import polars as pl
        pl.DataFrame(columns).write_csv(path)
    else:
        import pandas as pd
        pd.DataFrame(columns).to_csv(path, index=False)


def export_data(state: "AppState", plot_index: int, path: str, relative: bool = False) -> int:
    """Write a subplot's signals to a wide CSV (``time`` + one column per signal).

    Exports the currently visible time window (the linked range when set, else the
    full extent). ``relative`` rebases the time column to start at 0 -- the legacy
    viewer's "start time at 0" option. Signals whose run differs from the first
    signal's (different time base) are skipped with a warning.
    """

    if not 0 <= plot_index < len(state.cells):
        raise ValueError(f"plot_{plot_index + 1} out of range")
    cell = state.cells[plot_index]
    if not cell.signals:
        raise ValueError(f"plot_{plot_index + 1} has no signals to export")

    run0 = state.registry.get(cell.signals[0][0])
    if run0 is None:
        raise ValueError("source run is not loaded")
    time = run0.time

    # Use *this* subplot's own visible X range (not the global linked range), so
    # it is unambiguous which plot you are exporting. Fall back to the full extent.
    own = state.plot_x_ranges.get(plot_index + 1)
    if own is not None:
        x_min = max(own[0], float(time[0]))
        x_max = min(own[1], float(time[-1]))
    else:
        x_min, x_max = float(time[0]), float(time[-1])

    channels = [ref[1] for ref in cell.signals if ref[0] == run0.id and state.registry.get_signal(*ref) is not None]
    t, values = run0.read_window(channels, x_min, x_max)
    columns = {"time": (t - t[0]) if relative and len(t) else t}
    for ref in cell.signals:
        if ref[0] != run0.id:
            state.console.warn(f"export: skipped {state.signal_label(ref)} (different time base)")
            continue
        signal = state.registry.get_signal(ref[0], ref[1])
        if signal is not None:
            # Use the plain channel name (e.g. "ia"), as in the source log -- not
            # the "ia @ Log.csv" display label.
            columns[ref[1]] = values[ref[1]]

    _write_csv(columns, path, state.backend)
    return len(columns)


def export_fft(state: "AppState", path: str) -> int:
    """Write the FFT window's spectra to a CSV.

    A single shared ``frequency`` column + one amplitude column per signal when every
    spectrum shares the same frequency axis (the common case: signals from one run, or
    runs sampled at the same rate over the same window). When the spectra have
    **different** frequency axes -- signals from runs at different sample rates or
    window lengths -- each signal is written as its own ``<name>_frequency, <name>``
    pair (NaN-padded to the longest), so amplitudes stay paired with the correct bins.
    A single shared column would otherwise mis-align them.
    """
    import numpy as np

    from .analysis import compute_fft

    cfg = state.fft
    if not cfg.sources:
        raise ValueError("FFT window has no signals")
    x_min, x_max = state.resolve_x_window(cfg.follow_plot, (cfg.x_min, cfg.x_max), cfg.sources)

    spectra: list[tuple[str, np.ndarray, np.ndarray]] = []  # (name, freqs, mag)
    used: set[str] = {"frequency"}
    for ref in cfg.sources:
        run = state.registry.get(ref[0])
        signal = state.registry.get_signal(ref[0], ref[1])
        if run is None or signal is None:
            raise ValueError(f"Cannot export FFT: {state.signal_label(ref)} is not loaded")
        t, values = run.read_window([ref[1]], x_min, x_max)
        result = compute_fft(t, values[ref[1]], x_min, x_max, remove_dc=cfg.remove_dc, window=cfg.window)
        if not result.ok:
            raise ValueError(f"Cannot export FFT for {state.signal_label(ref)}: {result.info}")
        name = ref[1] if ref[1] not in used else f"{ref[1]} @ {run.label}"  # disambiguate dup names
        name = unique_name(name, used)
        spectra.append((name, result.freqs, result.mag))
    freqs0 = spectra[0][1]
    shared = all(f.shape == freqs0.shape and np.array_equal(f, freqs0) for _, f, _ in spectra)
    if shared:  # one `frequency` column + one amplitude column per signal
        m = min(min(len(mag) for _, _, mag in spectra), len(freqs0))
        columns: dict[str, np.ndarray] = {"frequency": freqs0[:m]}
        for name, _, mag in spectra:
            columns[name] = mag[:m]
    else:  # mixed axes -> per-signal (frequency, amplitude) pairs, NaN-padded
        maxlen = max(len(mag) for _, _, mag in spectra)
        columns = {}
        column_names = set()
        for name, freqs, mag in spectra:
            fcol, acol = np.full(maxlen, np.nan), np.full(maxlen, np.nan)
            fcol[: len(freqs)] = freqs
            acol[: len(mag)] = mag
            columns[unique_name(f"{name}_frequency", column_names)] = fcol
            columns[unique_name(name, column_names)] = acol
    _write_csv(columns, path, state.backend)
    return len(columns)


def export_histogram(state: "AppState", path: str) -> int:
    """Write the Histogram window's bins to a wide CSV: ``bin_center`` + one count
    column per signal, computed over a shared value range so columns align."""
    import numpy as np

    cfg = state.histogram
    if not cfg.sources:
        raise ValueError("Histogram window has no signals")
    x_min, x_max = state.resolve_x_window(cfg.follow_plot, (cfg.x_min, cfg.x_max), cfg.sources)

    from .analysis import histogram_sources
    series = []
    used = {"bin_center"}
    for ref in cfg.sources:
        run = state.registry.get(ref[0])
        if run is not None and ref[1] in run.signals:
            name = ref[1] if ref[1] not in used else state.signal_label(ref)
            name = unique_name(name, used)
            series.append((name, run.data_source(), ref[1], run.time_offset))
    results, _, _ = histogram_sources(series, x_min, x_max, cfg.bins)
    if not results:
        raise ValueError("no data to export")
    columns = {"bin_center": results[0][1]}
    columns.update({label: counts for label, _, counts, _ in results})
    _write_csv(columns, path, state.backend)
    return len(columns)
