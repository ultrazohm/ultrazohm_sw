"""Left navigation: load files, activate runs, browse and drag signals.

Each loaded run is a collapsible tree node (Matlab-data-viewer style) with a
checkbox to activate/deactivate it. Signals are drag sources that can be
dropped onto any plot in the main view.
"""

from __future__ import annotations

import os

from imgui_bundle import imgui

from uz_dataviewer.core.data_store import SignalRef
from uz_dataviewer.ui.app_state import SIGNAL_PAYLOAD_TYPE, AppState

try:
    from imgui_bundle import portable_file_dialogs as pfd

    HAS_FILE_DIALOG = True
except ImportError:  # pragma: no cover - pyodide/web builds have no native dialogs
    HAS_FILE_DIALOG = False


class NavigationPanel:
    def __init__(self, state: AppState):
        self.state = state
        self._open_dialog = None
        self._manual_path = ""

    def render(self) -> None:
        self._render_load_controls()
        imgui.separator()
        self._render_run_tree()

    # ------------------------------------------------------------- loading UI

    def _render_load_controls(self) -> None:
        state = self.state
        if HAS_FILE_DIALOG:
            if imgui.button("Open file(s) ..."):
                self._open_dialog = pfd.open_file(
                    "Select javascope log files",
                    "",
                    ["Log files", "*.csv *.parquet", "All files", "*"],
                    pfd.opt.multiselect,
                )
            if self._open_dialog is not None and self._open_dialog.ready(0):
                paths = self._open_dialog.result()
                self._open_dialog = None
                if paths:
                    state.store.load_files_async(list(paths))
        else:
            # Web build: no native dialogs - load from a path in the virtual FS.
            imgui.set_next_item_width(-110)
            _, self._manual_path = imgui.input_text("##path", self._manual_path)
            imgui.same_line()
            if imgui.button("Load path") and self._manual_path.strip():
                state.store.load_files_async([self._manual_path.strip()])

        if state.store.loading:
            imgui.same_line()
            imgui.text_disabled("loading ...")

    # --------------------------------------------------------------- run tree

    def _render_run_tree(self) -> None:
        state = self.state
        if not state.store.runs:
            imgui.text_disabled("No data loaded.")
            imgui.text_wrapped(
                "Open .csv or .parquet log files recorded with the javascope, "
                "then drag signals onto a plot."
            )
            return

        remove_run_id = None
        for run_id, run in state.store.runs.items():
            imgui.push_id(run_id)

            changed, active = imgui.checkbox("##active", run.active)
            if changed:
                run.active = active
                state.console.info(
                    f"Run '{run.name}' {'activated' if active else 'deactivated'}."
                )
            if imgui.is_item_hovered():
                imgui.set_tooltip("Show/hide this run in all plots")

            imgui.same_line()
            if not run.active:
                imgui.push_style_var(imgui.StyleVar_.alpha, 0.5)
            opened = imgui.tree_node(f"{run.name}##node")
            if imgui.begin_popup_context_item("run_context"):
                if imgui.menu_item_simple("Remove run"):
                    remove_run_id = run_id
                imgui.end_popup()

            if opened:
                rate = run.sample_rate
                rate_text = f", ~{rate:,.0f} Hz" if rate else ""
                imgui.text_disabled(
                    f"{run.n_samples:,} samples, {run.duration:.6g} s{rate_text}"
                )
                imgui.text_disabled(os.path.dirname(run.path) or ".")
                for signal in run.signals:
                    self._render_signal(run_id, signal)
                imgui.tree_pop()
            if not run.active:
                imgui.pop_style_var()

            imgui.pop_id()

        if remove_run_id is not None:
            state.store.remove_run(remove_run_id)

        imgui.separator()
        imgui.text_disabled("Drag a signal onto a plot to display it.")

    def _render_signal(self, run_id: int, signal: str) -> None:
        state = self.state
        ref = SignalRef(run_id, signal)
        imgui.selectable(f"  {signal}", False)
        if imgui.begin_drag_drop_source():
            payload_id = state.store.payload_id(ref)
            imgui.set_drag_drop_payload_py_id(SIGNAL_PAYLOAD_TYPE, payload_id)
            imgui.text(f"{signal}")
            imgui.end_drag_drop_source()
        if imgui.is_item_hovered():
            imgui.set_tooltip(f"Drag onto a plot to display '{signal}'")
