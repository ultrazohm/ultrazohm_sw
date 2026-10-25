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
Scripts reset the session and reference deterministic run_N identifiers.
"""

from __future__ import annotations

import json
from typing import TYPE_CHECKING

from .sources import SourceColumn
from .state import PlotType, XyStyle

if TYPE_CHECKING:  # pragma: no cover - typing only
    from .state import AppState, SubplotCell

SCHEMA_VERSION = 2


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


def _script_ref(state, ref):
    if ref is None:
        return None
    from .nodes import _topo_order
    ids = [r.id for r in state.registry.runs if not r.derived]
    ids += [state.nodes.get(n).out_run_id for n in _topo_order(state.nodes)
            if state.nodes.get(n).is_transform and state.nodes.get(n).out_run_id is not None]
    if ref[0] not in ids:
        return None
    return [f"run_{ids.index(ref[0]) + 1}", ref[1]]


def clear_session(state):
    """Reset recording identities and consumers before restoring a complete session."""
    from .model import DataRegistry
    from .nodes import NodeGraph
    from .state import FftConfig, HistogramConfig
    from .loading import LoadExecutor
    state._executor.shutdown()
    state._executor = LoadExecutor()
    state._pending.clear()
    state.large_csv_requests.clear()
    state.display.retain(set())
    state.analysis_jobs.retain(set())
    state.registry = DataRegistry()
    state.nodes = NodeGraph()
    state.set_grid(1, 1)
    from .state import SubplotCell
    state.cells = [SubplotCell()]
    state.fft, state.histogram = FftConfig(), HistogramConfig()
    state.plot_x_ranges.clear()
    state.shared_x = None


def _nodes_to_list(state: "AppState") -> list[dict]:
    out = []
    for node in state.nodes.ordered():
        out.append(
            {
                "id": node.id,
                "kind": node.kind,
                "name": node.name,
                "params": dict(node.params),
                "inputs": list(node.inputs),
                "ref": _ref_to_saved(state, node.ref) if node.ref else None,
                "pos": list(node.pos),
            }
        )
    return out


# -- JSON snapshot ------------------------------------------------------------
def to_dict(state: "AppState") -> dict:
    cells = []
    for cell in state.cells:
        cells.append(
            {
                "signals": [_ref_to_saved(state, r) for r in cell.signals],
                "type": cell.plot_type.value,
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
        "max_points": state.max_points,
        "loading_mode": state.loading_mode,
        "disk_cache": state.disk_cache,
        "backend": state.backend,
        "cache_budget_mb": state.registry.cache.limit // 1024**2,
        "runs": [{"key": f"run:{r.id}", "path": r.path,
                  "mode": "lazy" if isinstance(r.time, SourceColumn) else "memory",
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
    with open(path, "w", encoding="utf-8") as fh:
        json.dump(to_dict(state), fh, indent=2)


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


def apply_dict(state: "AppState", data: dict) -> None:
    if data.get("version") != SCHEMA_VERSION:
        raise ValueError(f"Unsupported session version; expected {SCHEMA_VERSION}. Recreate old sessions.")
    specs = data.get("runs", [])
    if len({r["key"] for r in specs}) != len(specs):
        raise ValueError("Duplicate run keys in session")
    clear_session(state)
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
    state.set_grid(int(rows), int(cols))
    state.link_x = bool(data.get("link_x", state.link_x))
    state.max_points = int(data.get("max_points", state.max_points))

    def _resolve(labelled) -> tuple[int, str] | None:
        if not labelled:
            return None
        key = labelled[0]
        if key.startswith("node:"):
            node = state.nodes.get(int(key.split(":", 1)[1]))
            run_id = node.out_run_id if node is not None else None
        else:
            run_id = run_ids.get(key)
        return None if run_id is None else (run_id, labelled[1])

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
        cell.fit_pending = True

    fft = data.get("fft") or {}
    state.fft.sources = [r for r in (_resolve(s) for s in fft.get("sources", [])) if r is not None]
    state.fft.follow_plot = int(fft.get("follow_plot", state.fft.follow_plot))
    state.fft.x_min = float(fft.get("x_min", state.fft.x_min))
    state.fft.x_max = float(fft.get("x_max", state.fft.x_max))
    state.fft.remove_dc = bool(fft.get("remove_dc", state.fft.remove_dc))
    state.fft.window = bool(fft.get("window", state.fft.window))
    state.fft.log_x = bool(fft.get("log_x", state.fft.log_x))
    state.fft.log_y = bool(fft.get("log_y", state.fft.log_y))

    hist = data.get("histogram") or {}
    state.histogram.sources = [r for r in (_resolve(s) for s in hist.get("sources", [])) if r is not None]
    state.histogram.follow_plot = int(hist.get("follow_plot", state.histogram.follow_plot))
    state.histogram.x_min = float(hist.get("x_min", state.histogram.x_min))
    state.histogram.x_max = float(hist.get("x_max", state.histogram.x_max))
    state.histogram.bins = int(hist.get("bins", state.histogram.bins))

    # Restoring sources alone leaves the windows blank until the user clicks
    # Compute (the panels only ever compute on request). Flag a recompute so a
    # restored session draws its spectra/bins straight away -- matching what the
    # fft_source/hist_source commands do when a script is replayed.
    state.fft.compute_requested = bool(state.fft.sources)
    state.histogram.compute_requested = bool(state.histogram.sources)


def _restore_nodes(state: "AppState", specs: list, resolve) -> None:
    """Rebuild the node graph from a snapshot (preserving ids) and evaluate it."""
    from .nodes import NodeGraph, evaluate

    state.nodes = NodeGraph()
    for spec in sorted(specs, key=lambda s: int(s["id"])):
        ref = resolve(spec.get("ref")) if spec.get("kind") == "source" else None
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
        for in_id in spec.get("inputs", []):
            try:
                state.nodes.link(int(in_id), dst)
            except ValueError:
                pass
    if state.nodes.nodes:
        evaluate(state)


# -- command script -----------------------------------------------------------
def _arg(token: str) -> str:
    from .commands import _fmt_str

    return _fmt_str(token)


def _nodes_to_script(state: "AppState", lines: list[str]) -> None:
    """Emit node_* calls that rebuild the graph. Ids are remapped to creation
    order (1..N) so a replay into a fresh graph reproduces the same references
    even if the live graph has id gaps."""
    nodes = state.nodes.ordered()
    if not nodes:
        return
    idmap = {node.id: i + 1 for i, node in enumerate(nodes)}  # -> replay ids
    for node in nodes:
        if node.kind == "source":
            lab = _script_ref(state, node.ref)
            if not lab:
                continue
            lines.append(f"node_source({_arg(lab[0])}, {_arg(lab[1])})")
        else:
            lines.append(f"node_add({node.kind})")
        nid = idmap[node.id]
        for key, value in node.params.items():
            lines.append(f"node_set(node_{nid}, {key}, {_arg(str(value))})")
        if node.name != f"node_{node.id}":
            lines.append(f"node_rename(node_{nid}, {_arg(node.name)})")
        if node.pos != (0.0, 0.0):
            lines.append(f"node_pos(node_{nid}, {node.pos[0]:.6g}, {node.pos[1]:.6g})")
    for node in nodes:
        for in_id in node.inputs:
            if in_id in idmap:
                lines.append(f"node_link(node_{idmap[in_id]}, node_{idmap[node.id]})")
    lines.append("node_eval()")


def to_script(state: "AppState") -> list[str]:
    lines: list[str] = ["# UltraZohm Data Viewer session script v2", "clear_session()",
                        f"disk_cache({str(state.disk_cache).lower()})",
                        f"backend({_arg(state.backend)})",
                        f"loading_mode({_arg(state.loading_mode)})",
                        f"cache_budget({state.registry.cache.limit // 1024**2})"]
    for run in state.registry.runs:
        if run.derived:  # regenerated by the node section below, not a file
            continue
        mode = "lazy" if isinstance(run.time, SourceColumn) else "memory"
        lines.append(f"disk_cache({str(getattr(run.source, 'disk_cache', False)).lower()})")
        lines.append(f"backend({_arg(run.backend)})")
        lines.append(f"loading_mode({_arg(mode)})")
        if run.time_origin is not None:
            lines.append(f"load({_arg(run.path)}, {run.time_origin:.6g})")
        else:
            lines.append(f"load({_arg(run.path)})")
    lines.append(f"disk_cache({str(state.disk_cache).lower()})")
    lines.append(f"backend({_arg(state.backend)})")
    lines.append(f"loading_mode({_arg(state.loading_mode)})")
    _nodes_to_script(state, lines)
    lines.append(f"set_grid({state.rows}, {state.cols})")
    lines.append(f"set_max_points({state.max_points})")
    lines.append(f"link_x({'true' if state.link_x else 'false'})")

    for i, cell in enumerate(state.cells, start=1):
        if cell.plot_type is not PlotType.LINE:
            lines.append(f"set_plot_type(plot_{i}, {cell.plot_type.value})")
        for ref in cell.signals:
            labelled = _script_ref(state, ref)
            if labelled:
                lines.append(f"add_signal(plot_{i}, {_arg(labelled[0])}, {_arg(labelled[1])})")
        if cell.xy_source is not None:
            labelled = _script_ref(state, cell.xy_source)
            if labelled:
                lines.append(f"set_xy(plot_{i}, {_arg(labelled[0])}, {_arg(labelled[1])})")
        if cell.plot_type is PlotType.XY and cell.xy_style is not XyStyle.LINE:
            lines.append(f"set_xy_style(plot_{i}, {cell.xy_style.value})")
        for ref in cell.y2_signals:
            labelled = _script_ref(state, ref)
            if labelled:
                lines.append(f"set_axis(plot_{i}, {_arg(labelled[0])}, {_arg(labelled[1])}, right)")
        if cell.show_samples:
            lines.append(f"show_samples(plot_{i}, true)")
        if cell.spy:
            if cell.spy_rect:
                x1, y1, x2, y2 = cell.spy_rect
                lines.append(f"set_spy_rect(plot_{i}, {x1:.6g}, {y1:.6g}, {x2:.6g}, {y2:.6g})")
            else:
                lines.append(f"spy(plot_{i}, true)")
        if cell.cursors:
            if cell.cursor_x:
                lines.append(f"set_cursors(plot_{i}, {cell.cursor_x[0]:.6g}, {cell.cursor_x[1]:.6g})")
            else:
                lines.append(f"cursors(plot_{i}, true)")
        if cell.export_relative:
            lines.append(f"set_export_relative(plot_{i}, true)")

    _analysis_to_script(state, lines)
    return lines


def _fwindow_token(follow_plot: int) -> str:
    """``follow_plot`` int -> the ``fwindow`` token (custom / full / plot_N)."""
    if follow_plot == 0:
        return "custom"
    if follow_plot == -1:
        return "full"
    return f"plot_{follow_plot}"


def _analysis_to_script(state: "AppState", lines: list[str]) -> None:
    """Emit the FFT/Histogram sources *and their options*, so a replayed script
    reproduces the same window the JSON snapshot would (DC removal, Hann, log
    axes, bin count, time window) rather than silently falling back to defaults."""
    fft = state.fft
    for ref in fft.sources:
        labelled = _script_ref(state, ref)
        if labelled:
            lines.append(f"fft_source({_arg(labelled[0])}, {_arg(labelled[1])})")
    if fft.sources:
        if not fft.remove_dc:
            lines.append("fft_remove_dc(false)")
        if not fft.window:
            lines.append("fft_hann(false)")
        if fft.log_x:
            lines.append("fft_logx(true)")
        if fft.log_y:
            lines.append("fft_logy(true)")
        if fft.follow_plot != 1:
            lines.append(f"fft_follow({_fwindow_token(fft.follow_plot)})")
        if fft.follow_plot == 0:
            lines.append(f"fft_range({fft.x_min:.6g}, {fft.x_max:.6g})")

    hist = state.histogram
    for ref in hist.sources:
        labelled = _script_ref(state, ref)
        if labelled:
            lines.append(f"hist_source({_arg(labelled[0])}, {_arg(labelled[1])})")
    if hist.sources:
        if hist.bins != 50:
            lines.append(f"hist_bins({hist.bins})")
        if hist.follow_plot != 1:
            lines.append(f"hist_follow({_fwindow_token(hist.follow_plot)})")
        if hist.follow_plot == 0:
            lines.append(f"hist_range({hist.x_min:.6g}, {hist.x_max:.6g})")


def export_script(state: "AppState", path: str) -> None:
    with open(path, "w", encoding="utf-8") as fh:
        fh.write("\n".join(to_script(state)) + "\n")


def run_script(state: "AppState", path: str) -> int:
    """Replay a script file line by line; returns the number of commands run."""
    with open(path, encoding="utf-8") as fh:
        lines = fh.readlines()
    if lines and lines[0].strip() == "# UltraZohm Data Viewer session script":
        raise ValueError("Unsupported session script version; recreate old exported sessions.")
    count = 0
    for line in lines:
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        from .commands import parse_call
        name, args = parse_call(line)
        state.commands.execute(state, name, args)
        count += 1
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
    used: set[str] = set()
    for ref in cfg.sources:
        run = state.registry.get(ref[0])
        signal = state.registry.get_signal(ref[0], ref[1])
        if run is None or signal is None:
            continue
        t, values = run.read_window([ref[1]], x_min, x_max)
        result = compute_fft(t, values[ref[1]], x_min, x_max, remove_dc=cfg.remove_dc, window=cfg.window)
        if not result.ok:
            continue
        name = ref[1] if ref[1] not in used else f"{ref[1]} @ {run.label}"  # disambiguate dup names
        used.add(name)
        spectra.append((name, result.freqs, result.mag))
    if not spectra:
        raise ValueError("no spectra to export")

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
        for name, freqs, mag in spectra:
            fcol, acol = np.full(maxlen, np.nan), np.full(maxlen, np.nan)
            fcol[: len(freqs)] = freqs
            acol[: len(mag)] = mag
            columns[f"{name}_frequency"] = fcol
            columns[name] = acol
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
    used = set()
    for ref in cfg.sources:
        run = state.registry.get(ref[0])
        if run is not None and ref[1] in run.signals:
            name = ref[1] if ref[1] not in used else state.signal_label(ref)
            used.add(name)
            series.append((name, run.data_source(), ref[1], run.time_offset))
    results, _, _ = histogram_sources(series, x_min, x_max, cfg.bins)
    if not results:
        raise ValueError("no data to export")
    columns = {"bin_center": results[0][1]}
    columns.update({label: counts for label, _, counts, _ in results})
    _write_csv(columns, path, state.backend)
    return len(columns)
