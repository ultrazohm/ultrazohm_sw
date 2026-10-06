"""JSON snapshots, replayable scripts, and visible-range plot export."""

from __future__ import annotations

import csv
import dataclasses
import json
from pathlib import Path
from typing import TYPE_CHECKING

import numpy as np

if TYPE_CHECKING:  # pragma: no cover
    from .state import ScopeAppState


SCHEMA_VERSION = 2


def _q(value: str) -> str:
    return json.dumps(str(value))


def _active_observable(state, segment_id: int) -> int | None:
    segment = state.segments.get(segment_id)
    if segment is None or not segment.active:
        return None
    return segment.observable


def _workspace_snapshot(state: "ScopeAppState") -> dict:
    data = state.workspace.to_dict()
    for window, raw_window in zip(state.workspace.windows, data["windows"]):
        for cell, raw_cell in zip(window.cells, raw_window["cells"]):
            raw_cell["observables"] = [
                obs for obs in (_active_observable(state, sid) for sid in cell.segments)
                if obs is not None
            ]
            raw_cell["y2_observables"] = [
                obs for obs in (
                    _active_observable(state, sid) for sid in cell.y2_segments
                ) if obs is not None
            ]
            raw_cell["xy_observable"] = (
                _active_observable(state, cell.xy_source)
                if cell.xy_source is not None else None
            )
            raw_cell["segments"] = []
            raw_cell["y2"] = []
            raw_cell["xy_source"] = None
    return data


def save_state(state: "ScopeAppState", path: str | Path) -> Path:
    payload = {
        "version": SCHEMA_VERSION,
        "config": dataclasses.asdict(state.config),
        "workspace": _workspace_snapshot(state),
    }
    path = Path(path)
    path.write_text(json.dumps(payload, indent=2) + "\n", encoding="utf-8")
    return path


def _seed_active_segments(state: "ScopeAppState") -> dict[int, int]:
    by_observable: dict[int, int] = {}
    for slot, ch in enumerate(state.config.channel_settings):
        if ch.observable == 0:
            continue
        segment = state.segments.start(
            slot, ch.observable, state.observable_name(ch.observable), 0,
            scale=ch.scale, offset=ch.offset, color=ch.color,
        )
        if segment is not None:
            by_observable[ch.observable] = segment.id
    return by_observable


def load_state(state: "ScopeAppState", path: str | Path) -> None:
    from .config import ScopeConfig
    from .workspace import PlotWorkspace

    if state.client is not None:
        raise ValueError("disconnect before loading a session")
    if state.logger is not None:
        raise ValueError("stop logging before loading a session")
    raw = json.loads(Path(path).read_text(encoding="utf-8"))
    # Version-1 snapshots were plain ScopeConfig dictionaries.
    config_data = raw.get("config", raw)
    state.config = ScopeConfig.from_dict(config_data)
    state.config.trigger.enabled = False
    state.detected_rate = None
    state.engine = None
    state.rebuild_ring()
    state._refresh_lifecheck_slot()
    active = _seed_active_segments(state)

    workspace_data = raw.get("workspace")
    if not isinstance(workspace_data, dict):
        return
    state.workspace = PlotWorkspace.from_dict(workspace_data)
    for window, raw_window in zip(
        state.workspace.windows, workspace_data.get("windows", [])
    ):
        for cell, spec in zip(window.cells, raw_window.get("cells", [])):
            cell.segments = [
                active[obs] for obs in spec.get("observables", []) if obs in active
            ]
            cell.y2_segments = [
                active[obs] for obs in spec.get("y2_observables", []) if obs in active
            ]
            xy = spec.get("xy_observable")
            cell.xy_source = active.get(xy)
            cell.fit_pending = True


def export_script_lines(state: "ScopeAppState") -> list[str]:
    cfg = state.config
    lines = [
        "# uz_scope2 session script",
        f"set_ip({cfg.ip})",
        f"set_port({cfg.port})",
        f"ack_pacing({'true' if cfg.ack_pacing else 'false'})",
        f"set_geometry({cfg.channels}, {cfg.samples_per_packet})",
        f"set_timestep({cfg.timestep_usec:g})",
        f"set_window({cfg.window_seconds:g})",
        f"set_refresh({cfg.refresh_hz:g})",
    ]
    for slot, ch in enumerate(cfg.channel_settings, start=1):
        lines.append(f"ch_select({slot}, {ch.observable})")
        if ch.visible:
            lines.append(f"ch_visible({slot}, true)")
        if ch.scale != 1.0:
            lines.append(f"ch_scale({slot}, {ch.scale:g})")
        if ch.offset != 0.0:
            lines.append(f"ch_offset({slot}, {ch.offset:g})")
    trig = cfg.trigger
    lines += [
        f"trig_mode({trig.mode})",
        f"trig_source({trig.channel})",
        f"trig_edge({trig.edge})",
        f"trig_level({trig.level:g})",
        f"trig_pretrigger({trig.pretrigger:g})",
    ]
    log = cfg.logging
    lines += [
        f"log_format({log.format})",
        f"log_every({log.every_n})",
        f"log_dir({_q(log.directory)})",
        f"ext_log({'true' if log.ext_trigger else 'false'})",
    ]

    for index, window in enumerate(state.workspace.windows):
        if index == 0:
            if window.title != "Plot 1":
                lines.append(f"rename_plot_window(window_1, {_q(window.title)})")
        else:
            lines.append(f"new_plot_window({_q(window.title)})")
        lines.append(f"set_grid({window.token}, {window.rows}, {window.cols})")
        lines.append(
            f"link_x({window.token}, {'true' if window.link_x else 'false'})"
        )
        lines.append(
            f"follow_live({window.token}, {'true' if window.follow_live else 'false'})"
        )
        for plot_number, cell in enumerate(window.cells, start=1):
            plot = f"plot_{plot_number}"
            if cell.plot_type.value != "Line":
                lines.append(
                    f"set_plot_type({window.token}, {plot}, {cell.plot_type.value})"
                )
            for sid in cell.segments:
                observable = _active_observable(state, sid)
                if observable is not None:
                    lines.append(
                        f"add_observable({window.token}, {plot}, {observable})"
                    )
            if cell.xy_source is not None:
                observable = _active_observable(state, cell.xy_source)
                if observable is not None:
                    lines.append(
                        f"set_xy_observable({window.token}, {plot}, {observable})"
                    )
            if cell.xy_style.value != "Line":
                lines.append(
                    f"set_xy_style({window.token}, {plot}, {cell.xy_style.value})"
                )
            for sid in cell.y2_segments:
                observable = _active_observable(state, sid)
                if observable is not None:
                    lines.append(
                        f"set_axis_observable({window.token}, {plot}, {observable}, right)"
                    )
            if cell.show_samples:
                lines.append(f"show_samples({window.token}, {plot}, true)")
            if cell.cursors:
                lines.append(f"cursors({window.token}, {plot}, true)")
            if cell.spy:
                lines.append(f"spy({window.token}, {plot}, true)")
    return lines


def export_script(state: "ScopeAppState", path: str | Path) -> Path:
    path = Path(path)
    path.write_text("\n".join(export_script_lines(state)) + "\n", encoding="utf-8")
    return path


def run_script(state: "ScopeAppState", path: str | Path) -> int:
    lines = Path(path).read_text(encoding="utf-8").splitlines()
    executed = 0
    for line in lines:
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        state.commands.dispatch(state, line)
        executed += 1
    return executed


def export_plot(
    state: "ScopeAppState",
    window_id: int,
    plot_number: int,
    path: str | Path,
    relative: bool = False,
) -> int:
    """Export raw retained samples in a subplot's current visible X range."""
    window = state.workspace.get(window_id)
    if window is None or not 1 <= plot_number <= len(window.cells):
        raise ValueError("unknown plot")
    cell = window.cells[plot_number - 1]
    if not cell.segments:
        raise ValueError("plot has no signals")
    x_range = state.last_plot_ranges.get((window_id, plot_number - 1))
    if x_range is None:
        end = state.ring.total_written * state.timestep_s
        x_range = (end - state.config.window_seconds, end)
    start = int(np.floor(x_range[0] / state.timestep_s))
    stop = int(np.ceil(x_range[1] / state.timestep_s))
    series = []
    for sid in cell.segments:
        segment = state.segments.get(sid)
        if segment is None:
            continue
        end = state.ring.total_written if segment.stop is None else segment.stop
        oldest = state.ring.total_written - state.ring.filled
        lo, hi = max(start, segment.start, oldest), min(stop, end)
        data, got = state.ring.snapshot_range(lo, max(0, hi - lo), [segment.slot])
        if data.shape[1]:
            series.append((segment, got, data[0]))
    if not series:
        raise ValueError("visible data has expired")
    common_start = max(item[1] for item in series)
    common_stop = min(item[1] + item[2].shape[0] for item in series)
    if common_stop <= common_start:
        raise ValueError("signals have no overlapping retained range")
    time_axis = np.arange(common_start, common_stop, dtype=np.float64) * state.timestep_s
    if relative:
        time_axis -= time_axis[0]
    headers = ["time"] + [item[0].name.removeprefix("JSO_") for item in series]
    columns = [time_axis]
    for _, got, values in series:
        columns.append(values[common_start - got: common_stop - got])
    rows = np.column_stack(columns)
    with Path(path).open("w", newline="", encoding="utf-8") as handle:
        writer = csv.writer(handle)
        writer.writerow(headers)
        writer.writerows(rows)
    return rows.shape[0]

