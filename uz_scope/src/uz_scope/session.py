"""Session persistence: state snapshots and replayable ``.uzscript`` export.

A snapshot is simply the settings JSON (``ScopeConfig``); a script is the
canonical command sequence that reproduces the configuration through the
normal command layer — the uz_dataviewer pattern, so scripts can also be
typed or replayed line by line in the console.
"""

from __future__ import annotations

from pathlib import Path
from typing import TYPE_CHECKING

if TYPE_CHECKING:  # pragma: no cover
    from .state import ScopeAppState


def _q(text: str) -> str:
    """Quote for the script parser, which has no escape support — embedded
    double quotes are downgraded to single quotes."""
    return '"' + str(text).replace('"', "'") + '"'


def export_script_lines(state: "ScopeAppState") -> list[str]:
    cfg = state.config
    lines = [
        "# uz_scope session script",
        f"set_ip({cfg.ip})",
        f"set_port({cfg.port})",
        f"ack_pacing({'true' if cfg.ack_pacing else 'false'})",
        f"auto_connect({'true' if cfg.auto_connect else 'false'})",
        f"set_geometry({cfg.channels}, {cfg.samples_per_packet})",
        f"set_timestep({cfg.timestep_usec:g})",
        f"set_refresh({cfg.refresh_hz:g})",
        # dir/limit/keep first: history_mode(disk) starts the spill immediately.
        f"history_dir({_q(cfg.history.directory)})",
        f"history_limit({max(1, cfg.history.max_ram_bytes // 2**20)})",
        f"history_keep({'true' if cfg.history.keep_files else 'false'})",
        f"history_mode({cfg.history.mode})",
    ]
    # ch_select adds a slot to the logged list, so only logged slots are
    # emitted (a line per raw slot would log all 20 on replay).
    for slot in cfg.logged_slots:
        ch = cfg.channel_settings[slot]
        lines.append(f"ch_select({slot + 1}, {ch.observable})")
        if ch.visible:
            lines.append(f"ch_visible({slot + 1}, true)")
        if ch.scale != 1.0:
            lines.append(f"ch_scale({slot + 1}, {ch.scale:g})")
        if ch.offset != 0.0:
            lines.append(f"ch_offset({slot + 1}, {ch.offset:g})")
        if ch.color:
            lines.append(f"ch_color({slot + 1}, {ch.color})")
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
        f'log_dir("{log.directory}")',
        f"ext_log({'true' if log.ext_trigger else 'false'})",
    ]
    for i, win in enumerate(cfg.plots, start=1):
        if i >= 2:
            lines.append(f"plot_add({_q(win.title)})")
        lines.append(f"plot_grid({i}, {win.rows}, {win.cols})")
        lines.append(f"plot_xmode({i}, {win.x_mode})")
        if win.link_x:
            lines.append(f"plot_link_x({i}, true)")
        for c, slots in enumerate(win.cells, start=1):
            for slot in slots:
                if i == 1 and c == 1:
                    continue  # covered by ch_visible above
                lines.append(f"plot_assign({i}, {c}, {slot + 1})")
    # dash_clear makes the replay deterministic on a non-empty dashboard;
    # explicit ids keep the dash_config lines addressing the right widget.
    lines.append("dash_clear()")
    for w in cfg.dashboard.widgets:
        lines.append(
            f"dash_add({w.kind}, {w.binding_type}, {w.binding_key}, "
            f"{w.x:g}, {w.y:g}, {w.id})"
        )
        if w.label:
            lines.append(f"dash_config({w.id}, label, {_q(w.label)})")
        if w.vmin != 0.0:
            lines.append(f"dash_config({w.id}, min, {w.vmin:g})")
        if w.vmax != 1.0:
            lines.append(f"dash_config({w.id}, max, {w.vmax:g})")
        if w.fmt != "%.4g":
            lines.append(f"dash_config({w.id}, fmt, {_q(w.fmt)})")
        if w.indicator_bit >= 0:
            lines.append(f"dash_config({w.id}, bit, {w.indicator_bit})")
        if (w.w, w.h) != (170.0, 84.0):
            lines.append(f"dash_size({w.id}, {w.w:g}, {w.h:g})")
    return lines


def export_script(state: "ScopeAppState", path: str | Path) -> Path:
    path = Path(path)
    path.write_text("\n".join(export_script_lines(state)) + "\n", encoding="utf-8")
    return path


def run_script(state: "ScopeAppState", path: str | Path) -> int:
    """Dispatch every line of a script through the command layer.

    Errors are logged to the console per line (dispatch semantics) — a broken
    line does not stop the rest of the script.
    """
    lines = Path(path).read_text(encoding="utf-8").splitlines()
    executed = 0
    for line in lines:
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        state.commands.dispatch(state, line)
        executed += 1
    return executed
