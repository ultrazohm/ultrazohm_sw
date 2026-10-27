"""Application entry point and docking layout.

Default layout: Navigation above Log Browser on the left, plots and analysis
in the center, and Console below the plots.
"""

from __future__ import annotations

from . import runtime

import os
import sys

from imgui_bundle import hello_imgui, imgui, immapp

from . import webbridge
from .panels.fft import FftPanel
from .panels.histogram import HistogramPanel
from .panels.navigation import NavigationPanel
from .panels.log_browser import LogBrowserPanel
from .panels.nodes import NodesPanel
from .panels.plots import PlotsPanel
from .panels.status import StatusPanel
from .session import ensure_extension
from .state import AppState, default_data_settings

try:  # portable_file_dialogs is unavailable in the browser build
    from imgui_bundle import portable_file_dialogs as pfd
except Exception:  # pragma: no cover
    pfd = None

MAIN_DOCK = "MainDockSpace"
LEFT_DOCK = "LeftSpace"
BOTTOM_DOCK = "BottomSpace"
LOG_DOCK = "LogBrowserSpace"


class DataViewerApp:
    def __init__(self, initial_files: list[str] | None = None, loading_mode: str | None = None, backend: str | None = None, disk_cache: bool = False) -> None:
        self.state = AppState()
        self.state.disk_cache = disk_cache
        if loading_mode is not None:
            self.state.loading_mode = loading_mode
        from .loader import validate_backend
        if backend is not None:
            self.state.backend = backend
        validate_backend(self.state.backend)
        self.navigation = NavigationPanel()
        self.log_browser = LogBrowserPanel()
        self.plots = PlotsPanel()
        self.status = StatusPanel()
        self.fft = FftPanel()
        self.histogram = HistogramPanel()
        self.nodes = NodesPanel()
        self.live = None
        if not runtime.IS_WEB:
            from .panels.live import LiveWorkspace
            self.live = LiveWorkspace()
        # Pending Session-menu file dialogs: (dialog, command_name, is_multi).
        self._session_dialog: tuple = ()
        # Let the browser file-input bridge reach this state (no-op on desktop).
        webbridge.register_state(self.state)
        # Load any external node plugins (optional; safe with no dir/files present).
        from . import plugins

        plugins.load_plugins(console=self.state.console)
        # Startup arguments are ordered automation. Register recordings before
        # executing dependent scripts; GUI opens remain asynchronous.
        for path in initial_files or []:
            if not os.path.exists(path):
                self.state.console.warn(f"File not found: {path}")
                break
            command = ("load_state" if path.lower().endswith(".json") else
                       "run_script" if path.lower().endswith(".uzscript") else "load")
            try:
                self.state.commands.execute(self.state, command, [path])
            except Exception as exc:
                self.state.console.error(f"Startup stopped at {path}: {exc}")
                break

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

        logs = hello_imgui.DockingSplit()
        logs.initial_dock = LEFT_DOCK
        logs.new_dock = LOG_DOCK
        logs.direction = imgui.Dir_.down
        logs.ratio = 0.4

        return [left, bottom, logs]

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

        logs = hello_imgui.DockableWindow()
        logs.label = "Log Browser"
        logs.dock_space_name = LOG_DOCK
        logs.gui_function = lambda: self.log_browser.render(self.state)

        windows = [nav, logs, plots, fft, histogram, nodes, console]
        if self.live is not None:
            for label, dock, render in (
                ('Live Data', LEFT_DOCK, lambda: self.live.render_data(self.state)),
                ('Control', LOG_DOCK, self.live.render_control),
                ('Live Plots', MAIN_DOCK, lambda: self.live.render_plots(self.state)),
            ):
                window = hello_imgui.DockableWindow()
                window.label = label
                window.dock_space_name = dock
                window.gui_function = render
                windows.append(window)
        return windows

    # -- Session menu (save/restore + scripting) ----------------------------
    def _show_menus(self) -> None:
        if not imgui.begin_menu("Session"):
            return
        if runtime.IS_WEB:
            self._web_session_menu()
        else:
            self._native_session_menu()
        imgui.end_menu()

    def _native_session_menu(self) -> None:
        disabled = pfd is None or bool(self._session_dialog)
        # Tuple: (dialog, command, is_multi, ext). `ext` (a save's expected extension)
        # is forced onto the result if the dialog returned none; "" for the loads.
        if imgui.menu_item("Save state...", "", False, not disabled)[0]:
            self._session_dialog = (
                pfd.save_file("Save state", "session.json", ["JSON (*.json)", "*.json"]),
                "save_state",
                False,
                ".json",
            )
        if imgui.menu_item("Load state...", "", False, not disabled)[0]:
            self._session_dialog = (
                pfd.open_file("Load state", "", ["JSON (*.json)", "*.json"]),
                "load_state",
                True,
                "",
            )
        imgui.separator()
        if imgui.menu_item("Run script...", "", False, not disabled)[0]:
            self._session_dialog = (
                pfd.open_file("Run script", "", ["Script (*.uzscript *.txt)", "*.uzscript *.txt"]),
                "run_script",
                True,
                "",
            )

    def _web_session_menu(self) -> None:
        """Browser has no OS file dialog: write+download to save, a hidden file
        input to load (routed by extension in :func:`webbridge.load_uploaded_session`)."""
        if imgui.menu_item("Save state...", "", False, True)[0]:
            self._web_download("save_state", "session.json")
        if imgui.menu_item("Load state / Run script...", "", False, True)[0]:
            webbridge.trigger_session_open()

    def _web_download(self, command: str, name: str) -> None:
        webbridge.save_and_download(
            self.state, name, lambda path: self.state.commands.execute(self.state, command, [path])
        )

    def _poll_session_dialog(self) -> None:
        if not self._session_dialog:
            return
        dialog, command, is_multi, ext = self._session_dialog
        if not dialog.ready():
            return
        result = dialog.result()
        path = (result[0] if result else "") if is_multi else result
        self._session_dialog = ()
        if path and ext:  # a save: make sure the file keeps its type extension
            path = ensure_extension(path, ext)
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
        if runtime.IS_WEB:
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
        if self.live is not None:
            self.live.pump(self.state)
        self.state.poll_pending_loads()
        self._poll_session_dialog()
        if self.state.focus_fft:
            hello_imgui.get_runner_params().docking_params.focus_dockable_window("FFT")
            self.state.focus_fft = False
        if self.state.focus_histogram:
            hello_imgui.get_runner_params().docking_params.focus_dockable_window("Histogram")
            self.state.focus_histogram = False

    def _shutdown(self) -> None:
        if self.live is not None:
            self.live.close()
        self.log_browser.shutdown()
        self.state.shutdown()

    def _show_load_dialog(self) -> None:
        if not self.state.services.large_csv_requests:
            return
        request = self.state.services.large_csv_requests[0]
        title = "Large CSV log"
        if not imgui.is_popup_open(title):
            imgui.open_popup(title)
        visible, _ = imgui.begin_popup_modal(title, flags=imgui.WindowFlags_.always_auto_resize)
        if visible:
            imgui.text_unformatted("Large log, conversion to parquet recommended")
            imgui.text_unformatted(os.path.basename(request.path))
            destination = os.path.splitext(request.path)[0] + ".parquet"
            imgui.text_unformatted("Conversion saves beside the CSV and opens the Parquet file.")
            imgui.text_unformatted(f"Output: {destination}")
            exists = os.path.lexists(destination)
            if exists:
                imgui.text_unformatted("A Parquet file already exists; it will not be overwritten.")
            choice = None
            if imgui.button("Open CSV"):
                choice = "csv"
            imgui.same_line()
            imgui.begin_disabled(exists)
            if imgui.button("Convert to Parquet"):
                choice = "convert"
            imgui.end_disabled()
            if exists:
                imgui.same_line()
                if imgui.button("Open existing Parquet"):
                    choice = "existing"
            imgui.same_line()
            if imgui.button("Cancel"):
                choice = "cancel"
            if choice:
                self.state.resolve_large_csv(choice)
                imgui.close_current_popup()
            imgui.end_popup()

    def _show_status(self) -> None:
        # The framework draws its FPS/idling controls after this callback.
        # Keep one display even if its View-menu toggle is selected.
        self._runner_params.imgui_window_params.show_status_fps = False
        self.status.render(self.state)

    # -- runner -------------------------------------------------------------
    def run(self) -> None:
        params = hello_imgui.RunnerParams()
        self._runner_params = params
        params.app_window_params.window_title = "UltraZohm Data Viewer"
        params.app_window_params.window_geometry.size = (1500, 900)
        params.imgui_window_params.default_imgui_window_type = (
            hello_imgui.DefaultImGuiWindowType.provide_full_screen_dock_space
        )
        params.imgui_window_params.show_status_bar = True
        params.imgui_window_params.show_status_fps = False  # FPS and cache share our status item.
        params.imgui_window_params.remember_status_bar_settings = False
        params.imgui_window_params.show_menu_bar = True
        # Always render at full rate. hello_imgui idles to ~9 fps when there's no
        # input; for live panning/zooming of large logs we want full FPS throughout.
        params.fps_idling.enable_idling = False
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
        params.callbacks.show_gui = self._show_load_dialog
        params.callbacks.show_status = self._show_status
        params.callbacks.before_exit = self._shutdown
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
    default_backend, default_mode = default_data_settings()
    if argv and argv[0] == "convert":
        # Headless CSV->Parquet conversion: `uz-dataviewer convert big.csv ...`.
        from .loader import convert_csv_to_parquet

        import argparse
        converter = argparse.ArgumentParser(prog="uz-dataviewer convert")
        converter.add_argument("--backend", choices=("pyarrow", "polars"), default=default_backend)
        converter.add_argument("files", nargs="+")
        options = converter.parse_args(argv[1:])
        files = options.files
        for src in files:
            out = convert_csv_to_parquet(src, backend=options.backend)
            print(f"converted {src} -> {out}")
        return 0
    import argparse
    parser = argparse.ArgumentParser(description="UltraZohm Data Viewer")
    parser.add_argument("--loading-mode", choices=("memory", "lazy"), default=default_mode,
                        help=f"storage policy for opening recordings (default: {default_mode})")
    parser.add_argument("--backend", choices=("pyarrow", "polars"), default=default_backend,
                        help=f"IO backend for file loading (default: {default_backend})")
    parser.add_argument("--disk-cache", action="store_true", help="Persist measurement caches on disk (default: RAM only)")
    parser.add_argument("files", nargs="*", help="CSV, Parquet, JSON sessions, or command scripts")
    args = parser.parse_args(argv)
    app = DataViewerApp(initial_files=args.files, loading_mode=args.loading_mode, backend=args.backend, disk_cache=args.disk_cache)
    app.run()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
