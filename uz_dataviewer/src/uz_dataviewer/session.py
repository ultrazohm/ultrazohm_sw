"""Transactional JSON sessions and sequential command scripts for automation.

JSON is the only session format. Scripts execute ordinary commands against the
current state; they do not provide a second session serialization protocol.
"""

from __future__ import annotations

from . import runtime

import json
import os
import tempfile
from typing import TYPE_CHECKING

from .loader import unique_name
from .state import PlotType, XyStyle
from .validation import axis_limits, finite_float, coordinates, spy_rectangle, histogram_bins, bounded_int, display_budget, boolean

if TYPE_CHECKING:  # pragma: no cover - typing only
    from .state import AppState

SCHEMA_VERSION = 5


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
                "output_view": {"active": run.active, "time_origin": run.time_origin, "axis_domain": run.axis_domain} if run else None,
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
                "x_lim": (cell.pending_x_lim or cell.x_lim) if cell.plot_type is PlotType.XY
                         else state.plot_time_range(len(cells) + 1),
                "y_lim": cell.pending_y_lim or cell.y_lim,
                "y2_lim": cell.pending_y2_lim or cell.y2_lim,
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
            "x_lim": state.fft.pending_x_lim or state.fft.x_lim,
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
            "x_lim": state.histogram.pending_x_lim or state.histogram.x_lim,
            "sources": [_ref_to_saved(state, r) for r in state.histogram.sources],
            "follow_plot": state.histogram.follow_plot,
            "x_min": state.histogram.x_min,
            "x_max": state.histogram.x_max,
            "bins": state.histogram.bins,
        },
    }


def save_state(state: "AppState", path: str) -> None:
    data = to_dict(state)
    # Publish only a complete snapshot. A failed serialization/write/replace
    # must leave the previous session intact; use the same filesystem.
    fd, temporary = tempfile.mkstemp(prefix=".uz-session-", suffix=".tmp",
                                     dir=os.path.dirname(os.path.abspath(path)))
    try:
        with os.fdopen(fd, "w", encoding="utf-8") as fh:
            json.dump(data, fh, indent=2)
        os.replace(temporary, path)
    finally:
        if os.path.exists(temporary):
            os.unlink(temporary)


def load_state(state: "AppState", path: str) -> None:
    with open(path, encoding="utf-8") as fh:
        data = json.load(fh)
    apply_dict(state, data)


def _session_backend(state, backend):
    if runtime.IS_WEB and backend == "polars":
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
            state.disk_cache = boolean(spec["disk_cache"])
            run = state.load_sync(spec["path"])
            if run is None:
                raise ValueError(f"Cannot restore recording: {spec['path']}")
            run.set_time_origin(spec.get("time_origin"))
            run.active = boolean(spec.get("active", True))
            run_ids[spec["key"]] = run.id
    finally:
        state.loading_mode, state.backend, state.disk_cache = mode, backend, disk_cache

    rows, cols = data.get("grid", [state.rows, state.cols])
    state.set_grid(rows, cols)
    state.link_x = boolean(data.get("link_x", state.link_x))
    state.shared_x = axis_limits(*data["shared_x"]) if data.get("shared_x") is not None else None
    state.max_points = display_budget(data.get("max_points", state.max_points))

    changed_domains = set()

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
        return None if run_id in changed_domains else (run_id, labelled[1])

    # Rebuild the node graph and evaluate it *before* resolving cell/analysis
    # assignments, so any references to a derived run (label == node name) resolve.
    changed_domains = _restore_nodes(state, data.get("nodes", []), _resolve)

    for i, spec in enumerate(data.get("cells", [])):
        if i >= len(state.cells):
            break
        cell = state.cells[i]
        cell.signals = [r for r in (_resolve(s) for s in spec.get("signals", [])) if r is not None]
        cell.plot_type = PlotType(spec.get("type", PlotType.LINE.value))
        cell.show_samples = boolean(spec.get("show_samples", False))
        cell.spy = boolean(spec.get("spy", False))
        cell.spy_rect = spy_rectangle(spec["spy_rect"]) if spec.get("spy_rect") is not None else None
        cell.cursors = boolean(spec.get("cursors", False))
        cell.cursor_x = coordinates(spec["cursor_x"], 2) if spec.get("cursor_x") is not None else None
        cell.export_relative = boolean(spec.get("export_relative", False))
        cell.xy_source = _resolve(spec.get("xy_source"))
        cell.xy_style = XyStyle(spec.get("xy_style", XyStyle.LINE.value))
        for ref in (_resolve(r) for r in spec.get("y2", [])):
            if ref is not None:
                cell.set_secondary(ref, True)
        lost_axis = any(_resolve(ref) is None for ref in spec.get("signals", [])) or (
            spec.get("xy_source") is not None and cell.xy_source is None)
        for axis in ('x', 'y', 'y2'):
            limits = spec.get(f'{axis}_lim')
            if limits is not None and not lost_axis:
                cell.set_limits(axis, *limits)
        if cell.pending_x_lim and cell.plot_type is not PlotType.XY:
            state.plot_x_ranges[i + 1] = cell.pending_x_lim
        state.plot_domain(cell)  # reject snapshots mixing incompatible axes
        cell.fit_pending = True

    fft = data.get("fft") or {}
    state.fft.sources = [r for r in (_resolve(s) for s in fft.get("sources", [])) if r is not None]
    state.fft.follow_plot = bounded_int(fft.get("follow_plot", state.fft.follow_plot), -1, state.cell_count, "FFT follow plot")
    state.fft.x_min = finite_float(fft.get("x_min", state.fft.x_min))
    state.fft.x_max = finite_float(fft.get("x_max", state.fft.x_max))
    state.fft.remove_dc = boolean(fft.get("remove_dc", state.fft.remove_dc))
    state.fft.window = boolean(fft.get("window", state.fft.window))
    state.fft.log_x = boolean(fft.get("log_x", state.fft.log_x))
    state.fft.log_y = boolean(fft.get("log_y", state.fft.log_y))

    hist = data.get("histogram") or {}
    state.histogram.sources = [r for r in (_resolve(s) for s in hist.get("sources", [])) if r is not None]
    state.histogram.follow_plot = bounded_int(hist.get("follow_plot", state.histogram.follow_plot), -1, state.cell_count, "Histogram follow plot")
    state.histogram.x_min = finite_float(hist.get("x_min", state.histogram.x_min))
    state.histogram.x_max = finite_float(hist.get("x_max", state.histogram.x_max))
    state.histogram.bins = histogram_bins(hist.get("bins", state.histogram.bins))

    for cfg, spec in ((state.fft, fft), (state.histogram, hist)):
        if spec.get("x_lim") is not None:
            cfg.x_lim = cfg.pending_x_lim = axis_limits(*spec["x_lim"])

    # Restoring sources alone leaves the windows blank until the user clicks
    # Compute (the panels only ever compute on request). Flag a recompute so a
    # restored session draws its spectra/bins straight away -- matching what the
    # fft_source/hist_source commands do when a script is replayed.
    state.fft.compute_requested = bool(state.fft.sources)
    state.histogram.compute_requested = bool(state.histogram.sources)


def _restore_nodes(state: "AppState", specs: list, resolve) -> None:
    """Rebuild the node graph from a snapshot (preserving ids) and evaluate it."""
    from .nodes import NodeGraph, evaluate, publish_output

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
        pos = spec.get("pos", (0.0, 0.0))
        node.pos = coordinates(pos, 2)
    for spec in specs:  # links once every node exists
        dst = int(spec["id"])
        for slot, in_id in enumerate(spec.get("inputs", [])):
            if in_id is not None:
                state.nodes.link(int(in_id), dst, slot)
    if state.nodes.nodes:
        evaluate(state)
    changed_domains = set()
    for spec in specs:
        view = spec.get("output_view")
        node = state.nodes.get(int(spec["id"]))
        run = state.registry.get(node.out_run_id)
        if view is not None and run is None and node.is_transform:
            # Keep the output identity/assignments while editing an incomplete or
            # failed graph. The empty placeholder is blocked by the same validator
            # as stale materialized outputs and is filled in on successful eval.
            publish_output(state, node, domain=view["axis_domain"])
            run = state.registry.get(node.out_run_id)
        if run is not None and view is not None:
            run.active = boolean(view["active"])
            saved_domain = view["axis_domain"]
            if saved_domain not in {"time", "frequency"}:
                raise ValueError("Invalid saved output axis domain")
            if saved_domain != run.axis_domain:
                changed_domains.add(run.id)
            else:
                run.set_time_origin(view["time_origin"])
    return changed_domains


def _check_reloadable(state):
    for run in state.registry.runs:
        if not run.derived and not run.reloadable:
            raise ValueError(f"Cannot save session: {run.label} has no backing file. Export its data first.")


# -- command scripts ----------------------------------------------------------
def run_script(state: "AppState", path: str) -> int | None:
    """Run automation commands sequentially, stopping at the first error."""
    from .commands import parse_call

    with open(path, encoding="utf-8") as fh:
        lines = fh.readlines()
    if any(line.strip().startswith("# UltraZohm Data Viewer session script") for line in lines):
        raise ValueError("Generated session scripts are no longer supported; save sessions as JSON.")
    if getattr(state, 'async_exports', False):
        from .automation import start
        commands = [parse_call(line.strip()) for line in lines
                    if line.strip() and not line.strip().startswith('#')]
        start(state, commands, path)
        return None
    count = 0
    for line in lines:
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        name, args = parse_call(line)
        state.commands.execute(state, name, args)
        count += 1
    return count


# -- data export --------------------------------------------------------------
def _write_csv(columns, path, backend, cancel=None):
    import tempfile
    fd, temporary = tempfile.mkstemp(prefix=".uz-export-", suffix=".csv",
                                     dir=os.path.dirname(os.path.abspath(path)))
    os.close(fd)
    try:
        if backend == "polars":
            import polars as pl
            pl.DataFrame(columns).write_csv(temporary)
        else:
            import pandas as pd
            pd.DataFrame(columns).to_csv(temporary, index=False)
        from .sources import check
        check(cancel)
        os.replace(temporary, path)
    finally:
        if os.path.exists(temporary):
            os.unlink(temporary)


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
    run0.data_source().validate()
    time = run0.time

    # Resolve linked and explicit ranges without requiring a render first.
    own = state.plot_time_range(plot_index + 1)
    if own is not None:
        x_min = max(own[0], float(time[0]))
        x_max = min(own[1], float(time[-1]))
    else:
        x_min, x_max = float(time[0]), float(time[-1])

    channels = [ref[1] for ref in cell.signals if ref[0] == run0.id and state.registry.get_signal(*ref) is not None]
    t, values = run0.read_window(channels, x_min, x_max)
    if relative and run0.axis_domain != "time":
        raise ValueError("Relative time export requires a time-domain recording")
    columns = {run0.axis_domain: (t - t[0]) if relative and len(t) else t}
    for ref in cell.signals:
        if ref[0] != run0.id:
            state.console.warn(f"export: skipped {state.signal_label(ref)} (different time base)")
            continue
        signal = state.registry.get_signal(ref[0], ref[1])
        if signal is not None:
            # Use the plain channel name (e.g. "ia"), as in the source log -- not
            # the "ia @ Log.csv" display label.
            columns[ref[1]] = values[ref[1]]

    _write_csv(columns, path, state.backend, getattr(state, '_export_cancel', None))
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

    from .analysis import compute_signal_fft

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
        result = compute_signal_fft(run, ref[1], x_min, x_max, remove_dc=cfg.remove_dc,
                                    window=cfg.window, label=state.signal_label(ref))
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
    _write_csv(columns, path, state.backend, getattr(state, '_export_cancel', None))
    return len(columns)


def export_histogram(state: "AppState", path: str) -> int:
    """Write the Histogram window's bins to a wide CSV: ``bin_center`` + one count
    column per signal, computed over a shared value range so columns align."""

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
    _write_csv(columns, path, state.backend, getattr(state, '_export_cancel', None))
    return len(columns)
