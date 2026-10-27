"""Shared base for the analysis windows (FFT, Histogram).

Both windows work the same way: you drag signals in, pick a *time window* that
either follows a chosen subplot, uses the full record, or is entered manually,
and a transform is computed on demand and overlaid for every source. This module
factors that common control flow into :class:`AnalysisPanel`.

Shared data/analysis controls and X zoom use the command registry. Reset view
and Y-axis gestures are local view actions, so the transcript is not a complete
GUI snapshot. Subclasses only supply the command name prefix,
the transform-specific options, and the per-signal compute/draw.
"""

from __future__ import annotations

from .. import runtime

from typing import TYPE_CHECKING

import numpy as np
from imgui_bundle import imgui, implot

from .. import webbridge
from ..downsample import decimate_range, visible_slice
from ..session import ensure_extension
from .base import SessionPanel
from .navigation import SIGNAL_DND_TYPE

try:  # portable_file_dialogs is unavailable in the browser build
    from imgui_bundle import portable_file_dialogs as pfd
except Exception:  # pragma: no cover
    pfd = None

if TYPE_CHECKING:  # pragma: no cover - typing only
    from ..state import AnalysisConfig, AppState


def follow_combo(label: str, follow_plot: int, n_plots: int) -> tuple[bool, int]:
    """The analysis-window time-source selector. Returns ``(changed, follow_plot)``.

    Encoding of ``follow_plot``: ``0`` = *Custom* (manual t min/max), ``-1`` =
    *Full* (the whole record), ``1..n_plots`` = follow that subplot's X range.
    """
    labels = ["Custom", "Full"] + [f"plot_{i}" for i in range(1, n_plots + 1)]
    if follow_plot == 0:
        idx = 0
    elif follow_plot == -1:
        idx = 1
    elif 1 <= follow_plot <= n_plots:
        idx = follow_plot + 1
    else:
        idx = 0
    imgui.set_next_item_width(110)
    changed, idx = imgui.combo(label, idx, labels)
    value = 0 if idx == 0 else (-1 if idx == 1 else idx - 1)
    return changed, value


class AnalysisPanel(SessionPanel):
    """Base class wiring sources, the window selector, zoom and drag-drop together,
    all routed through commands. Subclasses set ``prefix`` / ``compute_command``."""

    prefix: str = ""           # "fft" / "hist" -> *_source/_clear/_follow/_range/_xlim/_export
    compute_command: str = ""  # "fft" / "histogram"
    x_label: str = ""
    y_label: str = ""

    def __init__(self) -> None:
        self._info: str = ""
        self._export_dialog = None
        self._computed_key: tuple | None = None  # state at last compute (stale check)
        self._last_logged_x: tuple[float, float] | None = None  # zoom echo baseline
        self._fit_pending: bool = True  # one-shot auto-fit (first show / Reset / new result)
        self._zoom_after_fit = False
        self._generation = 0
        self._analysis_pending = None
        self._display_slots = set()
        self._display_pending = False
        self._fitting: bool = False     # this frame is an auto-fit (decimate full range)

    # -- command-name helpers ----------------------------------------------
    @property
    def add_command(self) -> str:
        return f"{self.prefix}_source"

    @property
    def clear_command(self) -> str:
        return f"{self.prefix}_clear"

    @property
    def follow_command(self) -> str:
        return f"{self.prefix}_follow"

    @property
    def range_command(self) -> str:
        return f"{self.prefix}_range"

    @property
    def xlim_command(self) -> str:
        return f"{self.prefix}_xlim"

    @property
    def export_command(self) -> str:
        return f"{self.prefix}_export"

    # -- subclass hooks -----------------------------------------------------
    def config(self, state: "AppState") -> "AnalysisConfig":  # pragma: no cover - abstract
        raise NotImplementedError

    def _extra_controls(self, state: "AppState", cfg: "AnalysisConfig") -> None:
        """Draw transform-specific controls (each routed through a command)."""

    def _setup_axes(self, state: "AppState") -> None:
        """Configure axis scales etc. after ``setup_axes``, before plotting."""

    def _options_key(self, cfg: "AnalysisConfig") -> tuple:
        """The transform options that, when changed, make the result stale."""
        return ()

    def _make_request(self, state: "AppState", cfg: "AnalysisConfig", x_min: float, x_max: float):
        raise NotImplementedError  # pragma: no cover - abstract

    def _draw(self, state: "AppState") -> None:
        raise NotImplementedError  # pragma: no cover - abstract

    def _result_refs(self) -> list[tuple[int, str]]:
        return []

    def _plot_decimated(self, state: "AppState", label: str, x: np.ndarray, y: np.ndarray, source) -> None:
        """Plot a line range-decimated to the current view, so a multi-million-point
        spectrum doesn't redraw at full resolution every frame."""
        if self._fitting:
            start, stop = 0, x.shape[0]  # fit frame: limits not known yet -> full range
        else:
            lim = implot.get_plot_limits()
            start, stop = visible_slice(x, float(lim.x.min), float(lim.x.max))
        budget = max(2, min(state.max_points, int(implot.get_plot_size().x * 2)))
        identity = source.metadata.identity
        key = (identity, start, stop, budget)
        self._display_slots.add(label)
        def prepare(cancel):
            xs, ys = decimate_range(x, y, source, budget, start, stop, cancel)
            return np.ascontiguousarray(xs, np.float64), np.ascontiguousarray(ys, np.float64)
        requests = state.services.analysis_displays[self.prefix]
        result = requests.request(label, key, identity, prepare)
        if not requests.ready(label, key) and requests.error(label) is None:
            self._display_pending = True
        if result is not None:
            implot.plot_line(label, *result)
        else:
            implot.plot_dummy(label)

    # -- stale tracking -----------------------------------------------------
    def _current_key(self, state: "AppState", cfg: "AnalysisConfig") -> tuple:
        try:
            window = state.resolve_x_window(cfg.follow_plot, (cfg.x_min, cfg.x_max), cfg.sources)
        except ValueError:
            window = (cfg.x_min, cfg.x_max)
        versions = tuple((ref, state.registry.get(ref[0]).time_version,
                          state.registry.get_signal(*ref).version)
                         for ref in cfg.sources if state.registry.get_signal(*ref) is not None)
        return (versions, window[0], window[1], self._source_error(state, cfg)) + self._options_key(cfg)

    @staticmethod
    def _source_error(state, cfg):
        from ..sources import validation_error
        sources = []
        for ref in cfg.sources:
            run = state.registry.get(ref[0])
            if run is None or ref[1] not in run.signals:
                return 'Analysis source is no longer loaded'
            if run.axis_domain != "time":
                return 'Analysis windows require a time-domain recording'
            sources.append(run.data_source())
        return validation_error(sources)

    # -- shared render ------------------------------------------------------
    def _poll_export(self, state: "AppState") -> None:
        if self._export_dialog is None or not self._export_dialog.ready():
            return
        path = self._export_dialog.result()
        self._export_dialog = None
        if path:
            path = ensure_extension(path, ".csv")  # dialog may drop the extension
            self._emit(state, self.export_command, path)

    def render(self, state: "AppState") -> None:
        self._sync_session(state)
        self._poll_export(state)
        cfg = self.config(state)

        # -- controls (all routed through commands) --
        changed, value = follow_combo("Window", cfg.follow_plot, state.cell_count)
        if changed:
            self._emit(state, self.follow_command, value)
        if cfg.follow_plot == 0:
            imgui.same_line()
            imgui.set_next_item_width(110)
            c1, new_min = imgui.input_float("t min", cfg.x_min)
            imgui.same_line()
            imgui.set_next_item_width(110)
            c2, new_max = imgui.input_float("t max", cfg.x_max)
            if c1 or c2:
                self._emit(state, self.range_command, new_min, new_max)

        self._extra_controls(state, cfg)

        if imgui.button("Compute"):
            self._emit(state, self.compute_command)
        imgui.same_line()
        if imgui.button("Reset view"):
            self._fit_pending = True
            cfg.x_lim = cfg.pending_x_lim = None
        imgui.same_line()
        if imgui.button("Clear") and cfg.sources:
            self._emit(state, self.clear_command)
        imgui.same_line()
        if imgui.small_button("Export") and cfg.sources:
            name = f"{self.prefix}.csv"
            if pfd is not None and self._export_dialog is None:
                self._export_dialog = pfd.save_file(
                    f"Export {self.prefix} data", name, ["CSV (*.csv)", "*.csv"]
                )
            elif runtime.IS_WEB:  # no OS dialog in a tab -> write to FS + download
                webbridge.save_and_download(
                    state, name, lambda path: self._emit(state, self.export_command, path)
                )

        # Removed sources must disappear immediately, including while recomputing.
        if any(ref not in cfg.sources for ref in self._result_refs()):
            state.services.analysis_jobs.forget(self.prefix)
            self._analysis_pending = None
            self._results = []
            state.services.analysis_displays[self.prefix].retain(set())
            self._info = ""
            cfg.compute_requested = bool(cfg.sources)

        # -- compute on demand (command-driven; never per frame) --
        source_error = self._source_error(state, cfg)
        if source_error:
            state.services.analysis_jobs.forget(self.prefix)
            self._analysis_pending = None
            self._results = []
            state.services.analysis_displays[self.prefix].retain(set())
            self._info = source_error
            cfg.compute_requested = False
        if cfg.compute_requested:
            cfg.compute_requested = False
            x_min, x_max = state.resolve_x_window(cfg.follow_plot, (cfg.x_min, cfg.x_max), cfg.sources)
            self._generation += 1
            key = (self._generation, self._current_key(state, cfg))
            request = self._make_request(state, cfg, x_min, x_max)
            self._analysis_pending = key
            state.services.analysis_jobs.request(self.prefix, key, key, request.compute)
        if self._analysis_pending is not None:
            key = self._analysis_pending
            result = state.services.analysis_jobs.completed(self.prefix, key)
            if result is not None:
                if key[1] == self._current_key(state, cfg):
                    self._results, self._info = result.series, result.info
                    self._computed_key = key[1]
                    state.services.analysis_displays[self.prefix].retain(set())
                    self._fit_pending = True
                self._analysis_pending = None
            elif state.services.analysis_jobs.error(self.prefix) is not None:
                self._info = state.services.analysis_jobs.error(self.prefix)
                self._results = []
                state.services.analysis_displays[self.prefix].retain(set())
                self._analysis_pending = None
            else:
                imgui.text_disabled("Computing...")
        if self._analysis_pending is not None and self._analysis_pending[1] != self._current_key(state, cfg):
            state.services.analysis_jobs.forget(self.prefix)
            self._analysis_pending = None
        if not cfg.sources:
            state.services.analysis_jobs.forget(self.prefix)
            self._analysis_pending = None
            self._results = []
            state.services.analysis_displays[self.prefix].retain(set())

        # -- info + stale indicator --
        if self._info:
            imgui.text_disabled(self._info)
        if self._result_refs() and self._computed_key != self._current_key(state, cfg):
            imgui.same_line()
            imgui.text_colored((0.95, 0.75, 0.25, 1.0), "  ⚠ stale - press Compute")
        imgui.separator()

        # -- plot --
        did_set = False
        self._fitting = self._fit_pending
        if self._fit_pending:
            if cfg.x_lim is None and cfg.pending_x_lim is None:
                implot.set_next_axes_to_fit()
            else:
                implot.set_next_axis_to_fit(implot.ImAxis_.y1)
                cfg.pending_x_lim = cfg.pending_x_lim or cfg.x_lim
            self._fit_pending = False
            did_set = True
        if implot.begin_plot("##analysis", imgui.ImVec2(-1, -1)):
            implot.setup_axes(self.x_label, self.y_label)
            self._setup_axes(state)
            if cfg.pending_x_lim is not None:
                lo, hi = cfg.pending_x_lim
                implot.setup_axis_limits(implot.ImAxis_.x1, lo, hi, implot.Cond_.always)
                cfg.pending_x_lim = None
                did_set = True

            self._display_slots.clear()
            self._display_pending = False
            self._draw(state)
            state.services.analysis_displays[self.prefix].retain(self._display_slots)
            if self._display_pending:
                self._fit_pending = self._fitting
            for slot in self._display_slots:
                error = state.services.analysis_displays[self.prefix].error(slot)
                if error:
                    self._info = error

            for ref in self._result_refs():
                label = state.signal_label(ref)
                if implot.begin_legend_popup(label):
                    imgui.text_disabled(label)
                    if imgui.menu_item("Remove", "", False)[0]:
                        self._remove(state, ref)
                    implot.end_legend_popup()

            if implot.begin_drag_drop_target_plot():
                payload = imgui.accept_drag_drop_payload_py_id(SIGNAL_DND_TYPE)
                if payload is not None:
                    ref = getattr(state, "dragged_ref", None)
                    if ref is not None:
                        self._emit(state, self.add_command, ref[0], ref[1])
                implot.end_drag_drop_target()

            # Echo a *_xlim command when a pan/zoom of this plot settles.
            lim = implot.get_plot_limits()
            if implot.is_plot_hovered():
                self._maybe_echo_zoom(state, float(lim.x.min), float(lim.x.max), suppress=did_set or self._zoom_after_fit)
            elif not did_set:
                self._last_logged_x = (float(lim.x.min), float(lim.x.max))

            self._zoom_after_fit = did_set
            implot.end_plot()

    def _maybe_echo_zoom(self, state: "AppState", lo: float, hi: float, *, suppress: bool) -> None:
        from ..validation import axis_limits
        try:
            limits = axis_limits(lo, hi)
        except ValueError:
            return
        if suppress:
            self._last_logged_x = limits
            return
        if imgui.is_mouse_down(0):
            return
        span = hi - lo
        last = self._last_logged_x
        if last is not None and abs(last[0] - lo) < 0.005 * span and abs(last[1] - hi) < 0.005 * span:
            return
        first = last is None
        self._last_logged_x = (lo, hi)
        if not first:
            # The gesture has already moved ImPlot; persist it without queuing a
            # redundant axis update that would interfere with the next gesture.
            self.config(state).x_lim = limits
            state.commands.echo(state, self.xlim_command, [lo, hi])

    def _remove(self, state: "AppState", ref: tuple[int, str]) -> None:
        if ref in self.config(state).sources:
            self._emit(state, f"{self.prefix}_remove", ref[0], ref[1])
