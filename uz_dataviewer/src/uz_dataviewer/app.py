"""Application entry point and docking layout.

Builds the VSCode-style three-zone layout with hello_imgui docking:

    +------------------------------------------------+
    |  Navigation  |        Plots / FFT (tabs)        |
    |   (left)     |            (center)              |
    |              |                                  |
    |--------------+----------------------------------|
    |               Console (bottom)                  |
    +------------------------------------------------+
"""

from __future__ import annotations

import os
import sys

from imgui_bundle import hello_imgui, imgui, immapp

from . import webbridge
from .panels.fft import FftPanel
from .panels.histogram import HistogramPanel
from .panels.navigation import NavigationPanel
from .panels.nodes import NodesPanel
from .panels.plots import PlotsPanel
from .state import AppState

try:  # portable_file_dialogs is unavailable in the browser build
    from imgui_bundle import portable_file_dialogs as pfd
except Exception:  # pragma: no cover
    pfd = None

MAIN_DOCK = "MainDockSpace"
LEFT_DOCK = "LeftSpace"
BOTTOM_DOCK = "BottomSpace"


class DataViewerApp:
    def __init__(self, initial_files: list[str] | None = None) -> None:
        self.state = AppState()
        self.navigation = NavigationPanel()
        self.plots = PlotsPanel()
        self.fft = FftPanel()
        self.histogram = HistogramPanel()
        self.nodes = NodesPanel()
        # Pending Session-menu file dialogs: (dialog, command_name, is_multi).
        self._session_dialog: tuple = ()
        # Let the browser file-input bridge reach this state (no-op on desktop).
        webbridge.register_state(self.state)
        # Load any external node plugins (optional; safe with no dir/files present).
        from . import plugins

        plugins.load_plugins(console=self.state.console)
        for path in initial_files or []:
            if not os.path.exists(path):
                self.state.console.warn(f"File not found: {path}")
            elif path.lower().endswith(".uzscript"):
                # Replay a saved session script (reproducible startup).
                self.state.commands.execute(self.state, "run_script", [path])
            else:
                self.state.request_load(path)

    # -- docking layout -----------------------------------------------------
    def _docking_splits(self) -> list[hello_imgui.DockingSplit]:
        left = hello_imgui.DockingSplit()
        left.initial_dock = MAIN_DOCK
        left.new_dock = LEFT_DOCK
        left.direction = imgui.Dir_.left
        left.ratio = 0.22

        bottom = hello_imgui.DockingSplit()
        bottom.initial_dock = MAIN_DOCK
        bottom.new_dock = BOTTOM_DOCK
        bottom.direction = imgui.Dir_.down
        bottom.ratio = 0.25

        return [left, bottom]

    def _dockable_windows(self) -> list[hello_imgui.DockableWindow]:
        nav = hello_imgui.DockableWindow()
        nav.label = "Navigation"
        nav.dock_space_name = LEFT_DOCK
        nav.gui_function = lambda: self.navigation.render(self.state)

        plots = hello_imgui.DockableWindow()
        plots.label = "Plots"
        plots.dock_space_name = MAIN_DOCK
        plots.gui_function = lambda: self.plots.render(self.state)

        fft = hello_imgui.DockableWindow()
        fft.label = "FFT"
        fft.dock_space_name = MAIN_DOCK
        fft.gui_function = lambda: self.fft.render(self.state)

        histogram = hello_imgui.DockableWindow()
        histogram.label = "Histogram"
        histogram.dock_space_name = MAIN_DOCK
        histogram.gui_function = lambda: self.histogram.render(self.state)

        nodes = hello_imgui.DockableWindow()
        nodes.label = "Nodes"
        nodes.dock_space_name = MAIN_DOCK
        nodes.gui_function = lambda: self.nodes.render(self.state)

        console = hello_imgui.DockableWindow()
        console.label = "Console"
        console.dock_space_name = BOTTOM_DOCK
        console.gui_function = lambda: self.state.console.render(self.state)

        return [nav, plots, fft, histogram, nodes, console]

    # -- Session menu (save/restore + scripting) ----------------------------
    def _show_menus(self) -> None:
        if not imgui.begin_menu("Session"):
            return
        disabled = pfd is None or bool(self._session_dialog)
        if imgui.menu_item("Save state...", "", False, not disabled)[0]:
            self._session_dialog = (
                pfd.save_file("Save state", "session.json", ["JSON (*.json)", "*.json"]),
                "save_state",
                False,
            )
        if imgui.menu_item("Load state...", "", False, not disabled)[0]:
            self._session_dialog = (
                pfd.open_file("Load state", "", ["JSON (*.json)", "*.json"]),
                "load_state",
                True,
            )
        imgui.separator()
        if imgui.menu_item("Export script...", "", False, not disabled)[0]:
            self._session_dialog = (
                pfd.save_file("Export script", "session.uzscript", ["Script (*.uzscript)", "*.uzscript"]),
                "export_script",
                False,
            )
        if imgui.menu_item("Run script...", "", False, not disabled)[0]:
            self._session_dialog = (
                pfd.open_file("Run script", "", ["Script (*.uzscript *.txt)", "*.uzscript *.txt"]),
                "run_script",
                True,
            )
        imgui.end_menu()

    def _poll_session_dialog(self) -> None:
        if not self._session_dialog:
            return
        dialog, command, is_multi = self._session_dialog
        if not dialog.ready():
            return
        result = dialog.result()
        path = (result[0] if result else "") if is_multi else result
        self._session_dialog = ()
        if path:
            try:
                self.state.commands.execute(self.state, command, [path])
            except Exception as exc:  # noqa: BLE001 - surfaced to the console
                self.state.console.error(str(exc))

    # -- native file drag-drop ---------------------------------------------
    def _install_file_drop(self) -> None:
        """Load `.csv`/`.parquet` files dropped onto the window (native, GLFW only).

        hello_imgui has no file-drop callback, so we register GLFW's directly. On the
        web build, a non-GLFW backend, or a missing `glfw` module this is a no-op and
        the **Open file(s)...** button remains the way in.
        """
        if webbridge.IS_WEB:
            return
        try:
            import glfw
            from imgui_bundle import glfw_utils

            window = glfw_utils.glfw_window_hello_imgui()
            if window is None:
                return

            def _on_drop(_window, paths) -> None:
                for p in paths:
                    if str(p).lower().endswith((".csv", ".parquet")):
                        self.state.request_load(str(p))
                    else:
                        self.state.console.warn(f"ignored dropped file (not .csv/.parquet): {p}")

            self._drop_callback = _on_drop  # keep a reference so it is not GC'd
            glfw.set_drop_callback(window, _on_drop)
        except Exception as exc:  # noqa: BLE001 - drag-drop is a nicety, never fatal
            self.state.console.warn(f"file drag-drop unavailable: {exc}")

    # -- per-frame ----------------------------------------------------------
    def _pre_new_frame(self) -> None:
        self.state.poll_pending_loads()
        self._poll_session_dialog()
        if self.state.focus_fft:
            hello_imgui.get_runner_params().docking_params.focus_dockable_window("FFT")
            self.state.focus_fft = False
        if self.state.focus_histogram:
            hello_imgui.get_runner_params().docking_params.focus_dockable_window("Histogram")
            self.state.focus_histogram = False

    # -- runner -------------------------------------------------------------
    def run(self) -> None:
        params = hello_imgui.RunnerParams()
        params.app_window_params.window_title = "UltraZohm Data Viewer"
        params.app_window_params.window_geometry.size = (1500, 900)
        params.imgui_window_params.default_imgui_window_type = (
            hello_imgui.DefaultImGuiWindowType.provide_full_screen_dock_space
        )
        params.imgui_window_params.show_status_bar = True
        params.imgui_window_params.show_menu_bar = True
        # MaterialFlat theme (per the idea list); applied via hello_imgui's
        # tweakable theme so it survives the dock layout setup.
        params.imgui_window_params.tweaked_theme.theme = (
            hello_imgui.ImGuiTheme_.material_flat
        )

        params.docking_params.docking_splits = self._docking_splits()
        params.docking_params.dockable_windows = self._dockable_windows()
        params.docking_params.layout_name = "UltraZohm"

        params.callbacks.pre_new_frame = self._pre_new_frame
        params.callbacks.show_menus = self._show_menus
        params.callbacks.before_exit = self.state.shutdown
        params.callbacks.post_init = self._install_file_drop

        addons = immapp.AddOnsParams()
        addons.with_implot = True
        # Enable the node-editor add-on for the Nodes window. Disable its own
        # settings file so the node graph (positions included) is owned entirely
        # by our AppState / command log / session, not a stray side-car json.
        from imgui_bundle import imgui_node_editor as ed

        node_cfg = ed.Config()
        node_cfg.settings_file = ""
        addons.with_node_editor_config = node_cfg
        immapp.run(params, addons)


def main(argv: list[str] | None = None) -> int:
    argv = list(sys.argv[1:] if argv is None else argv)
    app = DataViewerApp(initial_files=argv)
    app.run()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
