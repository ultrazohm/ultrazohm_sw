"""Plot windows: a dataviewer-style grid of cells over the session history.

Each plot window owns a rows x cols grid (independent ImPlot plots, not
subplots — the uz_dataviewer pattern) and a timebase: a "last X s" preset or
``cont`` (the axis grows from t=0).  While *attached* the x-axis follows the
live edge; any pan/zoom gesture detaches, and the Follow button re-attaches.
Data comes from :meth:`SessionHistory.query`, which stitches the full-res
ring tail with the session envelope pyramid, so panning into the past works
at any zoom.

Window 1 additionally owns Run/Stop and the trigger capture display (pin the
axes once per capture, then leave them free — unchanged semantics).
"""

from __future__ import annotations

import math
import time
from dataclasses import dataclass, field

import numpy as np
from imgui_bundle import imgui, implot

from ..config import X_MODE_CONT
from ..state import ScopeAppState

GRID_PRESETS = [(1, 1), (1, 2), (2, 1), (2, 2), (1, 3), (3, 1)]
X_MODE_PRESETS = (
    "0.05", "0.1", "0.5", "1", "2.5", "5", "10", "25", "50", X_MODE_CONT,
)
DND_SLOT = "UZ_SIGNAL"  # payload tag; the slot travels via state.dragged_slot


def _parse_color(color: str | None):
    if not color or not color.startswith("#") or len(color) != 7:
        return None
    try:
        r, g, b = (int(color[i : i + 2], 16) / 255.0 for i in (1, 3, 5))
    except ValueError:
        return None
    return imgui.ImVec4(r, g, b, 1.0)


def _finite(lo: float, hi: float) -> bool:
    return math.isfinite(lo) and math.isfinite(hi) and hi > lo


@dataclass
class _CellView:
    series: list = field(default_factory=list)  # (label, xs, ys, color, slot)
    limits: tuple[float, float] | None = None  # x-limits seen last frame


class PlotWindowPanel:
    def __init__(self, index: int) -> None:
        self.index = index  # 0-based; commands and labels use index + 1
        self._cells: list[_CellView] = []
        self._next_refresh = 0.0
        self._x_range: tuple[float, float] | None = None  # attached target
        self._capture_seq = 0
        self._capture_fit = False
        self._trigger_time: float | None = None
        self._level_display: float | None = None
        self._trig_slot: int | None = None
        self._shared_x: tuple[float, float] | None = None
        self._driver = -1
        self._last_logged_x: tuple[float, float] | None = None

    # --- render ------------------------------------------------------------

    def render(self, state: ScopeAppState) -> None:
        if self.index >= len(state.config.plots):
            return
        win = state.config.plots[self.index]
        view = state.plot_view(self.index + 1)
        self._toolbar(state, win, view)

        n = win.rows * win.cols
        while len(self._cells) < n:
            self._cells.append(_CellView())
        del self._cells[n:]

        engine = state.engine if self.index == 0 else None
        capture = engine.capture if engine is not None else None
        if engine is not None and engine.capture_is_stale():
            capture = None
        self._level_display = (
            self._display_level(state, engine) if engine is not None else None
        )
        self._trig_slot = engine.channel if engine is not None else None

        now = time.monotonic()
        if capture is not None:
            if capture.sequence != self._capture_seq:
                self._capture_seq = capture.sequence
                self._rebuild_capture(state, win, capture)
                self._capture_fit = True
        else:
            self._trigger_time = None
            self._capture_seq = 0
            if view.fit_pending:
                dt = state.timestep_s
                lo = self._cont_start(state) * dt
                hi = max(state.ring.total_written * dt, lo + 1e-3)
                view.pending_x = (lo, hi)
                view.fit_pending = False
            if not state.frozen or view.pending_x is not None:
                if now >= self._next_refresh or view.pending_x is not None:
                    self._next_refresh = now + 1.0 / max(
                        state.config.refresh_hz, 1.0
                    )
                    self._rebuild(state, win, view)

        region = imgui.get_content_region_avail()
        spacing = 4.0
        cell_w = max((region.x - spacing * (win.cols - 1)) / win.cols, 50.0)
        cell_h = max((region.y - spacing * (win.rows - 1)) / win.rows, 50.0)
        for r in range(win.rows):
            for c in range(win.cols):
                i = r * win.cols + c
                imgui.begin_group()
                self._render_cell(
                    state, win, view, i, imgui.ImVec2(cell_w, cell_h),
                    capture is not None,
                )
                imgui.end_group()
                if c < win.cols - 1:
                    imgui.same_line(0.0, spacing)
        # One-shot axis forces were applied to every cell this frame.
        view.pending_x = None
        if capture is not None:
            self._capture_fit = False

    # --- toolbar -----------------------------------------------------------

    def _toolbar(self, state: ScopeAppState, win, view) -> None:
        if self.index == 0:
            if imgui.button("Run" if state.frozen else "Stop"):
                state.commands.execute(
                    state, "run" if state.frozen else "stop_scope", []
                )
            imgui.same_line()
        imgui.set_next_item_width(70)
        grid_label = f"{win.rows}x{win.cols}"
        if imgui.begin_combo("##grid", grid_label):
            for rows, cols in GRID_PRESETS:
                label = f"{rows}x{cols}"
                if imgui.selectable(label, label == grid_label)[0]:
                    state.commands.execute(
                        state, "plot_grid", [self.index + 1, rows, cols]
                    )
            imgui.end_combo()
        imgui.same_line()
        imgui.set_next_item_width(90)
        current = win.x_mode if win.x_mode == X_MODE_CONT else f"{win.x_mode} s"
        if imgui.begin_combo("##xmode", current):
            for preset in X_MODE_PRESETS:
                label = preset if preset == X_MODE_CONT else f"{preset} s"
                if imgui.selectable(label, preset == win.x_mode)[0]:
                    state.commands.execute(
                        state, "plot_xmode", [self.index + 1, preset]
                    )
            imgui.end_combo()
        imgui.same_line()
        imgui.begin_disabled(view.attached)
        if imgui.button("Follow"):
            state.commands.execute(state, "plot_follow", [self.index + 1, True])
        imgui.end_disabled()
        imgui.same_line()
        if imgui.button("Fit"):
            state.commands.execute(state, "plot_fit", [self.index + 1])
        if win.rows * win.cols > 1:
            imgui.same_line()
            changed, linked = imgui.checkbox("Link X", win.link_x)
            if changed:
                state.commands.execute(
                    state, "plot_link_x", [self.index + 1, linked]
                )
        imgui.same_line()
        changed, fixed = imgui.checkbox("Fix axis", state.fix_axis)
        if changed:
            state.commands.execute(state, "fix_axis", [fixed])
        if self.index == 0:
            imgui.same_line()
            if imgui.button("+ Plot window"):
                state.commands.execute(state, "plot_add", [])

    # --- data --------------------------------------------------------------

    @staticmethod
    def _cont_start(state: ScopeAppState) -> int:
        hist = state.history
        if hist.pyramid is not None and hist.first_index is not None:
            return hist.first_index
        return state.ring.total_written - state.ring.filled

    @staticmethod
    def _display_level(state: ScopeAppState, engine) -> float:
        """Armed trigger level in display coordinates of the source channel
        (``(level + offset) / scale``); the comparison itself stays raw —
        JavaScope parity."""
        if engine.channel >= len(state.config.channel_settings):
            return float(engine.level)
        ch = state.config.channel_settings[engine.channel]
        scale = ch.scale if abs(ch.scale) > 1e-12 else 1.0
        return (engine.level + ch.offset) / scale

    def _series_for(
        self, state: ScopeAppState, cell: int, slots, i0: int, i1: int, n_out: int
    ) -> list:
        dt = state.timestep_s
        key = f"w{self.index}c{cell}"  # disk-mode detail request coalescing
        series = []
        for slot in slots:
            if slot >= len(state.config.channel_settings):
                continue
            ch = state.config.channel_settings[slot]
            xs, ys = state.history.query(
                state.ring, slot, i0, i1, n_out, dt, key=key
            )
            if xs.size == 0:
                continue  # no data yet — implot rejects empty arrays
            if ch.offset != 0.0 or ch.scale != 1.0:
                scale = ch.scale if abs(ch.scale) > 1e-12 else 1.0
                ys = (ys + ch.offset) / scale
            name = state.observable_name(ch.observable).removeprefix("JSO_")
            series.append(
                (f"CH{slot + 1} {name}", xs, ys, _parse_color(ch.color), slot)
            )
        return series

    def _rebuild(self, state: ScopeAppState, win, view) -> None:
        dt = state.timestep_s
        end_t = state.ring.total_written * dt
        window_s = win.window_seconds()
        if view.attached:
            if window_s is None:  # cont: grow from the session start
                x0 = self._cont_start(state) * dt
                x1 = max(end_t, x0 + 1e-3)
            else:
                x1 = end_t
                x0 = x1 - window_s
            self._x_range = (x0, x1)
        else:
            self._x_range = None
        width = imgui.get_content_region_avail().x / max(win.cols, 1)
        n_out = int(max(width, 200) * 2)
        for i, slots in enumerate(win.cells):
            cv = self._cells[i]
            if view.attached:
                lo, hi = self._x_range
            elif view.pending_x is not None:
                lo, hi = view.pending_x
            elif cv.limits is not None:
                lo, hi = cv.limits
            else:
                continue  # nothing known yet; keep previous series
            i0 = int(math.floor(lo / dt))
            i1 = int(math.ceil(hi / dt)) + 1
            cv.series = self._series_for(state, i, slots, i0, i1, n_out)

    def _rebuild_capture(self, state: ScopeAppState, win, capture) -> None:
        dt = state.timestep_s
        m = capture.data.shape[1]
        t = (capture.start_index + np.arange(m, dtype=np.float64)) * dt
        self._x_range = (float(t[0]), float(t[-1]) if m else float(t[0]))
        self._trigger_time = capture.trigger_index * dt
        width = imgui.get_content_region_avail().x / max(win.cols, 1)
        n_out = int(max(width, 200) * 2)
        for i, slots in enumerate(win.cells):
            series = []
            for slot in slots:
                if slot >= capture.data.shape[0]:
                    continue
                ch = state.config.channel_settings[slot]
                xs, ys = _decimate(t, capture.data[slot], n_out)
                if xs.size == 0:
                    continue
                if ch.offset != 0.0 or ch.scale != 1.0:
                    scale = ch.scale if abs(ch.scale) > 1e-12 else 1.0
                    ys = (ys + ch.offset) / scale
                name = state.observable_name(ch.observable).removeprefix("JSO_")
                series.append(
                    (f"CH{slot + 1} {name}", xs, ys, _parse_color(ch.color), slot)
                )
            self._cells[i].series = series

    # --- one cell ----------------------------------------------------------

    def _render_cell(
        self, state: ScopeAppState, win, view, i: int,
        size: imgui.ImVec2, capture_mode: bool,
    ) -> None:
        cv = self._cells[i]
        imgui.push_id(i)
        if implot.begin_plot(f"##plot{i}", size):
            y_flags = 0 if state.fix_axis else implot.AxisFlags_.auto_fit
            implot.setup_axes("time [s]", "", 0, y_flags)
            forced = False
            if capture_mode:
                if self._capture_fit and self._x_range is not None:
                    implot.setup_axis_limits(
                        implot.ImAxis_.x1, self._x_range[0], self._x_range[1],
                        imgui.Cond_.always,
                    )
                    forced = True
            elif view.pending_x is not None:
                implot.setup_axis_limits(
                    implot.ImAxis_.x1, view.pending_x[0], view.pending_x[1],
                    imgui.Cond_.always,
                )
                forced = True
            elif view.attached:
                if self._x_range is not None and not state.frozen:
                    implot.setup_axis_limits(
                        implot.ImAxis_.x1, self._x_range[0], self._x_range[1],
                        imgui.Cond_.always,
                    )
                    forced = True
            elif (
                win.link_x
                and self._shared_x is not None
                and i != self._driver
            ):
                implot.setup_axis_limits(
                    implot.ImAxis_.x1, self._shared_x[0], self._shared_x[1],
                    imgui.Cond_.always,
                )

            limits = implot.get_plot_limits()
            lo, hi = float(limits.x.min), float(limits.x.max)
            if _finite(lo, hi):
                cv.limits = (lo, hi)

            for label, xs, ys, color, _slot in cv.series:
                if xs.size == 0:  # defensive: implot rejects empty arrays
                    continue
                if color is not None:
                    spec = implot.Spec()
                    spec.line_color = color
                    implot.plot_line(label, xs, ys, spec)
                else:
                    implot.plot_line(label, xs, ys)
                self._legend_popup(state, i, label, _slot)

            slots = win.cells[i] if i < len(win.cells) else []
            if self._level_display is not None and self._trig_slot in slots:
                horizontal = implot.Spec()
                horizontal.flags = implot.InfLinesFlags_.horizontal
                implot.plot_inf_lines(
                    "##trig_lvl",
                    np.array([self._level_display], dtype=np.float64),
                    horizontal,
                )
            if self._trigger_time is not None and self._trig_slot in slots:
                implot.plot_inf_lines(
                    "##trig_t", np.array([self._trigger_time], dtype=np.float64)
                )

            self._accept_drop(state, i)

            if implot.is_plot_hovered() and _finite(lo, hi):
                self._driver = i
                self._shared_x = (lo, hi)
                if view.attached and not capture_mode and self._is_gesture():
                    view.attached = False  # x_lim echo follows on release
                if not view.attached and not capture_mode:
                    self._maybe_echo_zoom(state, lo, hi, suppress=forced)

            if not view.attached and not capture_mode and not state.frozen:
                implot.annotation(
                    lo + (hi - lo) * 0.99,
                    float(limits.y.max),
                    imgui.ImVec4(0.9, 0.6, 0.1, 0.8),
                    imgui.ImVec2(-4, 4),
                    True,
                    "detached — Follow to re-attach",
                )
            implot.end_plot()
        imgui.pop_id()

    @staticmethod
    def _is_gesture() -> bool:
        if imgui.get_drag_drop_payload_py_id() is not None:
            return False  # a drag-and-drop is in flight, not a pan gesture
        io = imgui.get_io()
        return (
            imgui.is_mouse_dragging(0)
            or imgui.is_mouse_dragging(1)
            or io.mouse_wheel != 0.0
        )

    def _maybe_echo_zoom(
        self, state: ScopeAppState, lo: float, hi: float, *, suppress: bool
    ) -> None:
        """Echo ``x_lim`` once a pan/zoom gesture settles (dataviewer pattern)."""
        if suppress or imgui.is_mouse_down(0) or imgui.is_mouse_down(1):
            return
        span = hi - lo
        last = self._last_logged_x
        if last is not None:
            if (
                abs(last[0] - lo) < 0.005 * span
                and abs(last[1] - hi) < 0.005 * span
            ):
                return
        else:
            self._last_logged_x = (lo, hi)  # silent baseline
            return
        self._last_logged_x = (lo, hi)
        state.commands.echo(state, "x_lim", [self.index + 1, lo, hi])

    def _accept_drop(self, state: ScopeAppState, i: int) -> None:
        if implot.begin_drag_drop_target_plot():
            payload = imgui.accept_drag_drop_payload_py_id(DND_SLOT)
            if payload is not None and state.dragged_slot is not None:
                state.commands.execute(
                    state,
                    "plot_assign",
                    [self.index + 1, i + 1, state.dragged_slot + 1],
                )
            implot.end_drag_drop_target()

    def _legend_popup(
        self, state: ScopeAppState, i: int, label: str, slot: int
    ) -> None:
        if implot.begin_legend_popup(label):
            imgui.text_disabled(label)
            if imgui.menu_item("Remove from this plot", "", False)[0]:
                state.commands.execute(
                    state, "plot_unassign", [self.index + 1, i + 1, slot + 1]
                )
            implot.end_legend_popup()


def _decimate(t: np.ndarray, y: np.ndarray, n_out: int):
    from uz_dataviewer.downsample import decimate_range

    xs, ys = decimate_range(t, y, None, n_out, 0, y.shape[0])
    return np.asarray(xs, dtype=np.float64), np.asarray(ys, dtype=np.float64)


class PlotWindowsManager:
    """Keeps one dockable window per ``config.plots`` entry.

    ``add_window_fn`` / ``remove_window_fn`` are injected by the app shell
    (``hello_imgui.add_dockable_window`` / ``remove_dockable_window``); tests
    pass ``None`` and drive the panels directly.  ``sync()`` runs once per
    frame (pre_new_frame) and reconciles panels with the config — window 1
    is permanent, windows 2+ are torn down and re-created on any count
    change so panel indices always match config indices.
    """

    def __init__(
        self, state: ScopeAppState, dock_space: str = "MainDockSpace",
        add_window_fn=None, remove_window_fn=None,
    ) -> None:
        self.state = state
        self.dock_space = dock_space
        self.add_window_fn = add_window_fn
        self.remove_window_fn = remove_window_fn
        self.panels: list[PlotWindowPanel] = []
        self._windows: list = []  # DockableWindows owned for the app lifetime

    def _label(self, i: int) -> str:
        return f"{self.state.config.plots[i].title}##uzplot{i}"

    def _make_window(self, i: int, panel: PlotWindowPanel):
        from imgui_bundle import hello_imgui

        win = hello_imgui.DockableWindow()
        win.label = self._label(i)
        # All plot windows start docked as tabs of the main dock space;
        # drag a tab out to float it (onto another monitor at will).
        win.dock_space_name = self.dock_space
        win.gui_function = lambda: panel.render(self.state)
        return win

    def startup_windows(self) -> list:
        """DockableWindows for every configured plot (RunnerParams setup)."""
        self.panels = [
            PlotWindowPanel(i) for i in range(len(self.state.config.plots))
        ]
        self._windows = [
            self._make_window(i, panel) for i, panel in enumerate(self.panels)
        ]
        return list(self._windows)

    def sync(self) -> None:
        want = len(self.state.config.plots)
        if want == len(self.panels):
            return
        if self.remove_window_fn is not None:
            for win in self._windows[1:]:
                self.remove_window_fn(win.label)
        del self.panels[1:]
        del self._windows[1:]
        for i in range(1, want):
            panel = PlotWindowPanel(i)
            self.panels.append(panel)
            win = self._make_window(i, panel)
            self._windows.append(win)
            if self.add_window_fn is not None:
                self.add_window_fn(win)
