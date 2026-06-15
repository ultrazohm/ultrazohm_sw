"""Left navigation panel: loaded runs, their signals, and drag sources.

Mirrors the Matlab data viewer workflow -- expand a run to see the channels it
logged, then drag a channel into a plot cell. The shared drag/drop payload type
is :data:`SIGNAL_DND_TYPE`; the dragged :data:`SignalRef` is stashed on the
:class:`AppState` so the plot panel can pick it up on drop.
"""

from __future__ import annotations

from imgui_bundle import imgui

from .. import webbridge
from ..state import AppState

try:  # portable_file_dialogs opens an OS dialog -- unavailable in the browser
    from imgui_bundle import portable_file_dialogs as pfd
except Exception:  # pragma: no cover
    pfd = None

SIGNAL_DND_TYPE = "UZ_SIGNAL"


class NavigationPanel:
    def __init__(self) -> None:
        self._open_dialog = None
        self._norm_target: dict[int, float] = {}  # per-run desired start time

    def _emit(self, state: AppState, name: str, *args) -> None:
        try:
            state.commands.execute(state, name, list(args))
        except Exception as exc:  # noqa: BLE001 - surfaced to the console
            state.console.error(str(exc))

    def _normalize_menu(self, state: AppState, run) -> None:
        """Per-log time-normalisation controls (in the run's context popup)."""
        on = run.time_origin is not None
        changed, on_new = imgui.checkbox("Normalize start time", on)
        target = self._norm_target.get(run.id, run.time_origin if on else 0.0)
        imgui.set_next_item_width(110)
        _, target = imgui.input_float("start at", target)
        self._norm_target[run.id] = target
        imgui.same_line()
        if imgui.small_button("Apply"):
            self._emit(state, "normalize_time", run.id, target)
        if changed:
            if on_new:
                self._emit(state, "normalize_time", run.id, target)
            else:
                self._emit(state, "reset_time", run.id)
        raw0 = float(run.time_raw[0]) if (run.time_raw is not None and run.n_rows) else 0.0
        now0 = float(run.time[0]) if run.n_rows else 0.0
        imgui.text_disabled(f"raw start {raw0:.4g}s  →  now {now0:.4g}s")

    def _poll_open_dialog(self, state: AppState) -> None:
        if self._open_dialog is None:
            return
        if not self._open_dialog.ready():
            return
        for path in self._open_dialog.result():
            state.request_load(path)
        self._open_dialog = None

    def render(self, state: AppState) -> None:
        self._poll_open_dialog(state)

        if imgui.button("Open file(s)..."):
            if webbridge.IS_WEB:
                # Browser: click the hidden HTML <input type="file">.
                webbridge.trigger_file_dialog()
            elif pfd is not None and self._open_dialog is None:
                self._open_dialog = pfd.open_file(
                    "Open log file(s)",
                    "",
                    ["Log files (*.csv *.parquet)", "*.csv *.parquet", "All files", "*"],
                    pfd.opt.multiselect,
                )
        if state.is_loading:
            imgui.same_line()
            imgui.text_colored((0.95, 0.75, 0.25, 1.0), "loading...")

        imgui.separator()
        imgui.text_disabled("Drag a signal into a plot cell")
        imgui.separator()

        if len(state.registry) == 0:
            imgui.text_wrapped("No data loaded. Use 'Open file(s)...' to load a .csv or .parquet log.")
            return

        run_to_remove: int | None = None
        for run in state.registry.runs:
            imgui.push_id(run.id)

            changed, active = imgui.checkbox("##active", run.active)
            if changed:
                self._emit(state, "set_active", run.id, active)
            imgui.same_line()
            imgui.color_button(
                "##color",
                run.color,
                imgui.ColorEditFlags_.no_tooltip | imgui.ColorEditFlags_.no_picker,
                imgui.ImVec2(12, 12),
            )
            imgui.same_line()

            node_flags = imgui.TreeNodeFlags_.span_avail_width
            opened = imgui.tree_node_ex(f"{run.label}", node_flags)
            if imgui.begin_popup_context_item("run_ctx"):
                imgui.text_disabled(run.path)
                imgui.text_disabled(f"{run.n_rows:,} rows  |  {run.duration:.3f} s")
                imgui.separator()
                self._normalize_menu(state, run)
                imgui.separator()
                if imgui.menu_item("Remove run", "", False)[0]:
                    run_to_remove = run.id
                imgui.end_popup()

            if opened:
                if not run.active:
                    imgui.text_disabled("(run deactivated)")
                for name, signal in run.signals.items():
                    ref = (run.id, name)
                    imgui.selectable(signal.label, False)
                    if run.active and imgui.begin_drag_drop_source():
                        state.dragged_ref = ref  # type: ignore[attr-defined]
                        imgui.set_drag_drop_payload_py_id(SIGNAL_DND_TYPE, 0)
                        imgui.text(f"→ {name}")
                        imgui.end_drag_drop_source()
                imgui.tree_pop()

            imgui.pop_id()

        if run_to_remove is not None:
            self._emit(state, "remove_run", run_to_remove)
