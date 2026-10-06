"""Rolling live plot.

Data refresh (default 30 Hz) is decoupled from the render rate: each refresh
takes a wrap-aware ring snapshot of the visible channels and decimates it to
~2x the plot's pixel width with uz_dataviewer's min/max envelope, so the
per-frame cost is independent of the ring size.  The display transform
``(y + offset) / scale`` is applied to the decimated points only.
"""

from __future__ import annotations

import time

import numpy as np
from imgui_bundle import imgui, implot

from uz_dataviewer.downsample import decimate_range

from ..state import ScopeAppState

WINDOW_PRESETS_S = (0.05, 0.1, 0.5, 1.0, 2.5, 5.0, 10.0, 25.0, 50.0)


def _parse_color(color: str | None):
    if not color or not color.startswith("#") or len(color) != 7:
        return None
    try:
        r, g, b = (int(color[i : i + 2], 16) / 255.0 for i in (1, 3, 5))
    except ValueError:
        return None
    return imgui.ImVec4(r, g, b, 1.0)


class ScopePlotPanel:
    def __init__(self) -> None:
        self._series: list[tuple[str, np.ndarray, np.ndarray, object]] = []
        self._next_refresh = 0.0
        self._x_range = (0.0, 1.0)
        self._capture_seq = 0
        self._capture_fit = False
        self._trigger_time: float | None = None
        self._level_display: float | None = None

    def render(self, state: ScopeAppState) -> None:
        self._toolbar(state)
        now = time.monotonic()
        engine = state.engine
        capture = engine.capture if engine is not None else None
        if engine is not None and engine.capture_is_stale():
            capture = None  # auto mode, edge source quiet -> keep rolling
        self._level_display = (
            self._display_level(state, engine) if engine is not None else None
        )
        if capture is not None:
            if capture.sequence != self._capture_seq:
                self._capture_seq = capture.sequence
                self._rebuild_capture(state, capture)
                self._capture_fit = True
        else:
            self._trigger_time = None
            # A re-armed engine restarts its sequence at 1; forget the old one
            # so the first capture of the new engine is picked up.
            self._capture_seq = 0
            if not state.frozen and now >= self._next_refresh:
                self._next_refresh = now + 1.0 / max(state.config.refresh_hz, 1.0)
                self._rebuild(state)
        if implot.begin_plot("##scope", imgui.ImVec2(-1, -1)):
            y_flags = 0 if state.fix_axis else implot.AxisFlags_.auto_fit
            implot.setup_axes("time [s]", "", 0, y_flags)
            if capture is not None:
                if self._capture_fit:
                    # Pin the axes on a fresh capture, then leave pan/zoom free.
                    implot.setup_axis_limits(
                        implot.ImAxis_.x1, self._x_range[0], self._x_range[1],
                        imgui.Cond_.always,
                    )
                    self._capture_fit = False
            elif not state.frozen:
                implot.setup_axis_limits(
                    implot.ImAxis_.x1, self._x_range[0], self._x_range[1],
                    imgui.Cond_.always,
                )
            for label, xs, ys, color in self._series:
                if color is not None:
                    spec = implot.Spec()
                    spec.line_color = color
                    implot.plot_line(label, xs, ys, spec)
                else:
                    implot.plot_line(label, xs, ys)
            if self._level_display is not None:
                # Level line whenever the trigger is armed, in display
                # coordinates of the source channel (JavaScope parity).
                horizontal = implot.Spec()
                horizontal.flags = implot.InfLinesFlags_.horizontal
                implot.plot_inf_lines(
                    "##trig_lvl",
                    np.array([self._level_display], dtype=np.float64),
                    horizontal,
                )
            if self._trigger_time is not None:
                implot.plot_inf_lines(
                    "##trig_t", np.array([self._trigger_time], dtype=np.float64)
                )
            implot.end_plot()

    @staticmethod
    def _display_level(state: ScopeAppState, engine) -> float:
        """The armed trigger level transformed like the source channel's
        plotted line — ``(level + offset) / scale`` — so the line sits on the
        displayed waveform.  The comparison itself always uses raw values,
        exactly like the JavaScope."""
        if engine.channel >= len(state.config.channel_settings):
            return float(engine.level)
        ch = state.config.channel_settings[engine.channel]
        scale = ch.scale if abs(ch.scale) > 1e-12 else 1.0
        return (engine.level + ch.offset) / scale

    def _rebuild_capture(self, state: ScopeAppState, capture) -> None:
        dt = 1.0 / state.sample_rate
        visible = [
            (slot, ch)
            for slot, ch in enumerate(state.config.channel_settings)
            if ch.visible
        ]
        m = capture.data.shape[1]
        t = (capture.start_index + np.arange(m, dtype=np.float64)) * dt
        self._x_range = (float(t[0]), float(t[-1]) if m else float(t[0]))
        self._trigger_time = capture.trigger_index * dt
        width = imgui.get_content_region_avail().x
        n_out = int(max(width, 200) * 2)
        series = []
        for slot, ch in visible:
            xs, ys = decimate_range(t, capture.data[slot], None, n_out, 0, m)
            ys = ys.astype(np.float64)
            if ch.offset != 0.0 or ch.scale != 1.0:
                ys = (ys + ch.offset) / ch.scale
            name = state.observable_name(ch.observable).removeprefix("JSO_")
            series.append(
                (f"CH{slot + 1} {name}", xs, ys, _parse_color(ch.color))
            )
        self._series = series

    def _toolbar(self, state: ScopeAppState) -> None:
        if imgui.button("Run" if state.frozen else "Stop"):
            state.commands.execute(
                state, "run" if state.frozen else "stop_scope", []
            )
        imgui.same_line()
        imgui.set_next_item_width(110)
        window = state.config.window_seconds
        if imgui.begin_combo("##window", f"{window:g} s"):
            for preset in WINDOW_PRESETS_S:
                if imgui.selectable(f"{preset:g} s", preset == window)[0]:
                    state.commands.execute(state, "set_window", [preset])
            imgui.end_combo()
        imgui.same_line()
        changed, fixed = imgui.checkbox("Fix axis", state.fix_axis)
        if changed:
            state.commands.execute(state, "fix_axis", [fixed])

    def _rebuild(self, state: ScopeAppState) -> None:
        rate = state.sample_rate
        dt = 1.0 / rate
        visible = [
            (slot, ch)
            for slot, ch in enumerate(state.config.channel_settings)
            if ch.visible
        ]
        count = max(2, int(state.config.window_seconds * rate))
        if not visible or state.ring.filled == 0:
            self._series = []
            end = state.ring.total_written * dt
            self._x_range = (end - state.config.window_seconds, end)
            return
        data, start = state.ring.snapshot(count, [slot for slot, _ in visible])
        m = data.shape[1]
        end_t = (start + m) * dt
        self._x_range = (end_t - state.config.window_seconds, end_t)
        t = (start + np.arange(m, dtype=np.float64)) * dt
        width = imgui.get_content_region_avail().x
        n_out = int(max(width, 200) * 2)
        series = []
        for row, (slot, ch) in zip(data, visible):
            xs, ys = decimate_range(t, row, None, n_out, 0, m)
            ys = ys.astype(np.float64)
            if ch.offset != 0.0 or ch.scale != 1.0:
                ys = (ys + ch.offset) / ch.scale
            name = state.observable_name(ch.observable).removeprefix("JSO_")
            series.append(
                (f"CH{slot + 1} {name}", xs, ys, _parse_color(ch.color))
            )
        self._series = series
