"""Application entry point and docking layout.

Default layout: Navigation / Live Data above Log Browser / Control on the left,
with plots and analysis above the Application log on the right.
"""

from __future__ import annotations

import os
import sys
from pathlib import Path

from imgui_bundle import hello_imgui, imgui, immapp

from .panels.fft import FftPanel
from .panels.histogram import HistogramPanel
from .panels.log_browser import LogBrowserPanel
from .panels.navigation import NavigationPanel
from .panels.nodes import NodesPanel
from .panels.plots import PlotsPanel
from .panels.status import StatusPanel
from .session import ensure_extension
from .state import AppState

try:  # optional native file dialogs
    from imgui_bundle import portable_file_dialogs as pfd
except Exception:  # pragma: no cover
    pfd = None

MAIN_DOCK = "MainDockSpace"
LEFT_DOCK = "LeftSpace"
LOG_DOCK = "LogBrowserSpace"
CONSOLE_DOCK = "ApplicationLogSpace"


class DataViewerApp:
    def __init__(
        self,
        initial_files: list[str] | None = None,
        loading_mode: str | None = None,
        backend: str | None = None,
        disk_cache: bool | None = None,
        use_live: bool = False,
        live_mapping: str = "",
        live_repo: str | None = None,
        start_live: bool = False,
    ) -> None:
        from .user_paths import data_directory, find_repository

        self._start_live = start_live

        mapping_path = (
            Path(live_mapping).expanduser().resolve() if live_mapping else None
        )
        workspace = Path(live_repo).expanduser().resolve() if live_repo else None
        if workspace is None and mapping_path:
            workspace = find_repository(mapping_path.parent)
        self.artifacts = data_directory(workspace)
        self.state = AppState()
        self._closed = False
        from .operations import Operations

        self.operations = Operations(self.state)
        self.control_server = None
        if self.artifacts is not None:
            self.state.cache_dir = os.environ.get(
                "UZ_DATAVIEWER_CACHE", str(self.artifacts / "viewer_cache")
            )
        from .panels.settings import SettingsPanel
        from .preferences import Preferences

        self.preferences = Preferences(self.state)
        self.preferences.apply()
        self.state.preferences = self.preferences
        self.settings_panel = SettingsPanel(self.preferences)
        if disk_cache is not None:
            self.state.disk_cache = disk_cache
        if loading_mode is not None:
            self.state.loading_mode = loading_mode
        from .loader import validate_backend

        if backend is not None:
            self.state.backend = backend
        validate_backend(self.state.backend)
        self.navigation = NavigationPanel()
        self.log_browser = LogBrowserPanel(
            Path(self.preferences.values["log_directory"])
            if self.preferences.values["log_directory"]
            else workspace / "artifacts"
            if workspace is not None
            else None
        )
        self.preferences.changed = self._preferences_changed
        self.plots = PlotsPanel()
        self._plot_windows = {}
        self._plot_windows_session = self.state.session_token
        self.status = StatusPanel()
        self.fft = FftPanel()
        self.histogram = HistogramPanel()
        self.nodes = NodesPanel()
        self.live = None
        self._select_initial_tabs = True
        if use_live:
            from .panels.live import LiveWorkspace

            self.live = LiveWorkspace(repo=workspace)
            self.live.mapping = str(mapping_path) if mapping_path else ""
            self.live.mapping_is_explicit = mapping_path is not None
            if live_mapping:
                self.live.load_live_settings()
            self.live.repository_selected = self._repository_selected
            if workspace is not None and not live_mapping:
                self.live.prepare_repository(workspace)
        from .panels.python import PythonPanel

        self.operations.bind_live(self.live)
        self.python_panel = PythonPanel(self)
        # Pending Session-menu file dialogs: (dialog, command_name, is_multi).
        self._session_dialog: tuple = ()
        self._session_action = None
        # Load any external node plugins (optional; safe with no dir/files present).
        from . import plugins

        plugins.load_plugins(console=self.state.console)
        # All startup files share the asynchronous GUI loading path. Its completion
        # spans axis/conversion prompts and registration before dependent scripts.
        self._startup_scripts = list(initial_files or [])
        self._startup_pending = None
        self._startup_script = False
        if any(path.lower().endswith(".uzscript") for path in self._startup_scripts):
            raise ValueError(".uzscript is no longer supported; use Python files")

        self.state.async_exports = True

    # -- docking layout -----------------------------------------------------
    def _docking_splits(self) -> list[hello_imgui.DockingSplit]:
        left = hello_imgui.DockingSplit()
        left.initial_dock = MAIN_DOCK
        left.new_dock = LEFT_DOCK
        left.direction = imgui.Dir_.left
        left.ratio = 0.30

        logs = hello_imgui.DockingSplit()
        logs.initial_dock = LEFT_DOCK
        logs.new_dock = LOG_DOCK
        logs.direction = imgui.Dir_.down
        logs.ratio = 0.4

        console = hello_imgui.DockingSplit()
        console.initial_dock = MAIN_DOCK
        console.new_dock = CONSOLE_DOCK
        console.direction = imgui.Dir_.down
        console.ratio = 0.2

        return [left, logs, console]

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
        console.label = "Application log"
        console.dock_space_name = CONSOLE_DOCK
        console.gui_function = lambda: self.state.console.render(self.state)

        logs = hello_imgui.DockableWindow()
        logs.label = "Log Browser"
        logs.dock_space_name = LOG_DOCK
        logs.gui_function = lambda: self.log_browser.render(self.state)

        python_window = hello_imgui.DockableWindow()
        python_window.label = "Python"
        python_window.dock_space_name = MAIN_DOCK
        python_window.gui_function = self.python_panel.render
        windows = [nav, logs, plots, fft, histogram, nodes, console, python_window]
        if self.live is not None:
            for label, dock, render in (
                ("Live Data", LEFT_DOCK, lambda: self.live.render_data(self.state)),
                ("Control", LOG_DOCK, self.live.render_control),
                ("Live Plots", MAIN_DOCK, lambda: self.live.render_plots(self.state)),
            ):
                window = hello_imgui.DockableWindow()
                window.label = label
                window.dock_space_name = dock
                window.gui_function = render
                windows.append(window)
        for window in windows:
            window.is_visible = window.label not in {"Python", "Application log"}
            if window.label == "Application log":
                window.is_visible = self.preferences.values["show_application_log"]
            elif window.label == "Python":
                window.is_visible = self.preferences.values["show_python"]
            window.remember_is_visible = False
        return windows

    # -- Session menu (save/restore + scripting) ----------------------------
    def _apply_window_mode(self, live: bool) -> None:
        """Select the requested tabs once without hiding or redocking other windows."""
        if live and (self.live is None or not self.live.available):
            return
        active = (
            ("Live Data", "Control", "Live Plots")
            if live
            else ("Navigation", "Log Browser", "Plots")
        )
        docking = self._runner_params.docking_params
        for window in docking.dockable_windows:
            if window.label in active:
                window.is_visible = True
        for label in active:
            docking.focus_dockable_window(label)

    def _repository_selected(self, root, directory):
        self.artifacts = directory
        self.state.cache_dir = os.environ.get(
            "UZ_DATAVIEWER_CACHE", str(directory / "viewer_cache")
        )
        if not self.preferences.values["log_directory"]:
            self.log_browser.refresh(root / "artifacts")
        if hasattr(self, "_runner_params"):
            self._runner_params.ini_filename = str(directory / "viewer.ini")

    def _preferences_changed(self, changes):
        if "log_directory" in changes:
            from .panels.log_browser import default_log_directory

            path = self.preferences.values["log_directory"]
            self.settings_panel.directory = path
            default = (
                self.artifacts.parent
                if self.artifacts.name == "_user"
                else default_log_directory()
            )
            self.log_browser.refresh(Path(path) if path else default)

    def _show_gui(self):
        self._show_load_dialog()
        self.settings_panel.render()

    def _show_app_menu_items(self) -> None:
        if imgui.menu_item("Settings", "", False)[0]:
            self.settings_panel.visible = True

    def _show_menus(self) -> None:
        # Append to Hello ImGui's existing menu, including its hidden ID
        # (docking_details.cpp::ShowViewMenu), rather than drawing a second View.
        if imgui.begin_menu("View##kdsflmkdflm"):
            imgui.separator()
            if imgui.menu_item("New plot window", "", False)[0]:
                self._new_plot_window()
            imgui.end_menu()
        if imgui.begin_menu("Mode"):
            if imgui.menu_item("Analysis", "", False)[0]:
                self._apply_window_mode(False)
            available = self.live is not None and self.live.available
            if imgui.menu_item("Live", "", False, available)[0]:
                self._apply_window_mode(True)
            imgui.end_menu()
        if not imgui.begin_menu("Session"):
            return
        self._native_session_menu()
        imgui.end_menu()

    def _new_plot_window(self, state=None):
        state = state if state is not None else self.state.create_plot_view()
        window_id = state.plot_window_id
        panel = PlotsPanel()
        window = hello_imgui.DockableWindow()
        window.label = f"Plots {window_id}"
        window.dock_space_name = MAIN_DOCK
        window.remember_is_visible = False
        window.is_visible = True

        def render():
            state.sync(self.state)
            panel.render(state)

        window.gui_function = render
        self._plot_windows[window_id] = (state, panel, window)
        hello_imgui.add_dockable_window(window, True)
        return state

    def _native_session_menu(self) -> None:
        disabled = (
            pfd is None
            or bool(self._session_dialog)
            or self._session_action is not None
        )
        # Tuple: (dialog, command, is_multi, ext). `ext` (a save's expected extension)
        # is forced onto the result if the dialog returned none; "" for the loads.
        if imgui.menu_item("Save state...", "", False, not disabled)[0]:
            self._session_dialog = (
                pfd.save_file(
                    "Save state", "session.json", ["JSON (*.json)", "*.json"]
                ),
                "save_session",
                False,
                ".json",
            )
        if imgui.menu_item("Load state...", "", False, not disabled)[0]:
            self._session_dialog = (
                pfd.open_file("Load state", "", ["JSON (*.json)", "*.json"]),
                "load_session",
                True,
                "",
            )
        imgui.separator()
        if imgui.menu_item("Run Python file...", "", False, not disabled)[0]:
            self._session_dialog = (
                pfd.open_file("Run Python file", "", ["Python (*.py)", "*.py"]),
                "run_python",
                True,
                "",
            )

    def _poll_session_dialog(self) -> None:
        if self._session_action is not None and self._session_action.done():
            try:
                self._session_action.result()
                self.state.console.info("Session operation completed")
            except Exception as exc:
                self.state.console.error(str(exc))
            self._session_action = None
        if not self._session_dialog:
            return
        dialog, command, is_multi, ext = self._session_dialog
        if not dialog.ready():
            return
        result = dialog.result()
        path = (result[0] if result else "") if is_multi else result
        self._session_dialog = ()
        if path and command == "run_python":
            self.python_panel.managed_device = False
            self.python_panel.start(path, self.python_panel.endpoint())
            return
        if path and ext:  # a save: make sure the file keeps its type extension
            path = ensure_extension(path, ext)
        if path:
            try:
                if command == "load_session":
                    # A manual replacement supersedes application-owned
                    # automation. External Python processes remain caller-owned.
                    self.python_panel.stop_owned()
                    self._startup_scripts.clear()
                    if self._startup_pending is not None:
                        self._startup_pending.cancel()
                        self._startup_pending = None
                    self._startup_script = False
                self._session_action = self.operations.dispatch(
                    command, {"path": path}, None
                )
            except Exception as exc:  # noqa: BLE001 - surfaced to the console
                self.state.console.error(str(exc))

    # -- native file drag-drop ---------------------------------------------
    def _install_file_drop(self) -> None:
        """Load `.csv`/`.parquet` files dropped onto the window (native, GLFW only).

        hello_imgui has no file-drop callback, so we register GLFW's directly. With a
        non-GLFW backend or a missing `glfw` module this is a no-op and the
        **Open file(s)...** button remains the way in.
        """
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
                        self.state.console.warn(
                            f"ignored dropped file (not .csv/.parquet): {p}"
                        )

            self._drop_callback = _on_drop  # keep a reference so it is not GC'd
            glfw.set_drop_callback(window, _on_drop)
        except Exception as exc:  # noqa: BLE001 - drag-drop is a nicety, never fatal
            self.state.console.warn(f"file drag-drop unavailable: {exc}")

    # -- per-frame ----------------------------------------------------------
    def _poll_startup(self):
        if self.control_server is None:
            return
        try:
            if self._startup_script:
                runner = self.python_panel.runner
                if runner.busy:
                    return
                self._startup_script = False
                if runner.exit_code != 0:
                    raise RuntimeError(runner.message)
            if self._startup_pending is not None:
                if not self._startup_pending.done():
                    return
                pending, self._startup_pending = self._startup_pending, None
                if pending.cancelled():
                    raise RuntimeError("Startup load cancelled")
                pending.result()
            if (
                not self._startup_scripts
                or self.python_panel.busy()
                or self.state.is_loading
            ):
                return
            path = self._startup_scripts.pop(0)
            if path.lower().endswith(".py"):
                self.python_panel.runner.start(
                    path, viewer_endpoint=self.python_panel.endpoint()
                )
                self._startup_script = True
            elif path.lower().endswith(".json"):
                self._startup_pending = self.operations.dispatch(
                    "load_session", {"path": path}, None
                )
            else:
                self._startup_pending = self.state.request_load(path)
        except Exception as exc:
            self._startup_scripts.clear()
            self.state.console.error(f"Startup stopped: {exc}")

    def enable_control(self, endpoint):
        from .control_server import ControlServer

        self.control_server = ControlServer(endpoint)
        self.state.console.info(f"Viewer control: {self.control_server.endpoint}")

    def _pre_new_frame(self) -> None:
        self.python_panel.poll()
        self._poll_startup()
        self.operations.poll()
        if self.control_server is not None:
            self.control_server.poll(self.operations.dispatch)
            if self.control_server.pending:
                hello_imgui.request_refresh()
        # Wait until restored docking/windows exist, then select the startup tabs.
        if (
            self._select_initial_tabs
            and hasattr(self, "_runner_params")
            and imgui.get_frame_count() >= 2
        ):
            self._apply_window_mode(self._start_live)
            self._select_initial_tabs = False
        if (
            self.operations.jobs
            or self.state.is_loading
            or self.state.services.display.pending
            or self.state.services.analysis_jobs.pending
            or self.state.services.exports
        ):
            hello_imgui.request_refresh()
        if self.live is not None:
            self.live.pump(self.state)
        self.state.poll_pending_loads()
        self._poll_session_dialog()
        if self._plot_windows_session is not self.state.session_token:
            for state, _, window in self._plot_windows.values():
                hello_imgui.remove_dockable_window(window.label)
                state.shutdown()
            self._plot_windows.clear()
            self._plot_windows_session = self.state.session_token
        for view_id in set(self._plot_windows) - set(self.state.plot_views):
            state, _, window = self._plot_windows.pop(view_id)
            hello_imgui.remove_dockable_window(window.label)
            state.shutdown()
        for view_id, state in self.state.plot_views.items():
            if view_id not in self._plot_windows:
                self._new_plot_window(state)
        # Hidden windows still need to publish completed exports and prune
        # assignments when a recording is removed from the shared registry.
        for state, _, _ in self._plot_windows.values():
            state.sync(self.state)
        if self.state.focus_fft:
            hello_imgui.get_runner_params().docking_params.focus_dockable_window("FFT")
            self.state.focus_fft = False
        if self.state.focus_histogram:
            hello_imgui.get_runner_params().docking_params.focus_dockable_window(
                "Histogram"
            )
            self.state.focus_histogram = False

    def _shutdown(self) -> None:
        if self._closed:
            return
        self._closed = True
        if self._session_dialog:
            self._session_dialog[0].kill()
            self._session_dialog = ()
        self.python_panel.close()
        if self.control_server is not None:
            self.control_server.close()
        self.operations.close()
        if self.live is not None:
            self.live.close()
        self.log_browser.shutdown()
        for state, _, _ in self._plot_windows.values():
            state.shutdown()
        self._plot_windows.clear()
        self.state.shutdown()

    def _show_load_dialog(self) -> None:
        self._show_axis_dialog()
        if not self.state.services.large_csv_requests:
            return
        request = self.state.services.large_csv_requests[0]
        title = "Large CSV log"
        if not imgui.is_popup_open(title):
            imgui.open_popup(title)
        visible, _ = imgui.begin_popup_modal(
            title, flags=imgui.WindowFlags_.always_auto_resize
        )
        if visible:
            imgui.text_unformatted("Large log, conversion to parquet recommended")
            imgui.text_unformatted(os.path.basename(request.path))
            destination = os.path.splitext(request.path)[0] + ".parquet"
            imgui.text_unformatted(
                "Conversion saves beside the CSV and opens the Parquet file."
            )
            imgui.text_unformatted(f"Output: {destination}")
            exists = os.path.lexists(destination)
            if exists:
                imgui.text_unformatted(
                    "A Parquet file already exists; it will not be overwritten."
                )
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

    def _show_axis_dialog(self):
        if not self.state.services.axis_requests:
            return
        request, columns, _ = self.state.services.axis_requests[0]
        if getattr(self, "_axis_request", None) is not request:
            self._axis_request = request
            self._axis_column = 0
            self._axis_domain = 0
        title = "Choose independent axis"
        if not imgui.is_popup_open(title):
            imgui.open_popup(title)
        visible, _ = imgui.begin_popup_modal(
            title, flags=imgui.WindowFlags_.always_auto_resize
        )
        if visible:
            imgui.text_unformatted(os.path.basename(request.path))
            imgui.text_unformatted("Select the independent column and its meaning.")
            _, self._axis_column = imgui.combo(
                "Column", self._axis_column, ["Choose a column", *columns]
            )
            _, self._axis_domain = imgui.combo(
                "Domain", self._axis_domain, ["Time (seconds)", "Frequency (Hz)"]
            )
            imgui.begin_disabled(self._axis_column == 0)
            if imgui.button("Open"):
                self.state.resolve_axis(
                    columns[self._axis_column - 1],
                    ("time", "frequency")[self._axis_domain],
                )
                imgui.close_current_popup()
            imgui.end_disabled()
            imgui.same_line()
            if imgui.button("Cancel"):
                self.state.resolve_axis()
                imgui.close_current_popup()
            imgui.end_popup()

    def _show_status(self) -> None:
        # The framework draws its FPS/idling controls after this callback.
        # Keep one display even if its View-menu toggle is selected.
        self._runner_params.imgui_window_params.show_status_fps = False
        self.status.render(self.state)

    # -- runner -------------------------------------------------------------
    def run(self) -> None:
        import imgui_bundle

        # Our icon overrides the stock icon; retain bundled fonts and other
        # framework assets instead of falling back to ImGui's bitmap font.
        hello_imgui.add_assets_search_path(
            str(Path(imgui_bundle.__file__).parent / "assets")
        )
        hello_imgui.set_assets_folder(str(Path(__file__).parent / "assets"))
        params = hello_imgui.RunnerParams()
        params.ini_filename = str(self.artifacts / "viewer.ini")
        params.ini_filename_use_app_window_title = False
        self._runner_params = params
        params.app_window_params.window_title = "UltraZohm Data Viewer"
        params.app_window_params.window_geometry.size = (1500, 900)
        params.app_window_params.window_geometry.window_size_state = (
            hello_imgui.WindowSizeState.maximized
        )
        params.app_window_params.restore_previous_geometry = False
        params.imgui_window_params.default_imgui_window_type = (
            hello_imgui.DefaultImGuiWindowType.provide_full_screen_dock_space
        )
        # DISPLAY can also be set under Wayland (XWayland), so require an
        # explicit X11 session before allowing detached windows on Linux.
        params.imgui_window_params.enable_viewports = sys.platform == "win32" or (
            sys.platform == "linux" and os.environ.get("XDG_SESSION_TYPE") == "x11"
        )
        params.imgui_window_params.show_status_bar = True
        params.imgui_window_params.show_status_fps = (
            False  # FPS and cache share our status item.
        )
        params.imgui_window_params.remember_status_bar_settings = False
        params.imgui_window_params.show_menu_bar = True
        # Never idle the viewer, including paused and offline views.
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
        params.callbacks.show_app_menu_items = self._show_app_menu_items
        params.callbacks.show_menus = self._show_menus
        params.callbacks.show_gui = self._show_gui
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
    """Compatibility entry point; all argument policy lives in cli.parser."""
    from .cli import main as cli_main

    return cli_main(["gui", *(sys.argv[1:] if argv is None else argv)])


def run_gui(args) -> int:
    """Launch from parsed options, resolving saved preferences only once."""
    from .preferences import Preferences

    defaults = Preferences().values
    loading_mode = getattr(args, "loading_mode", None) or defaults["loading_mode"]
    backend = getattr(args, "backend", None) or defaults["backend"]
    disk_cache = getattr(args, "disk_cache", None)
    if disk_cache is None:
        disk_cache = defaults["disk_cache"]
    # Live panels are available wherever the CLI package is installed (a
    # dependency of the viewer on Windows and Linux x86-64, bundled when frozen).
    import importlib.util

    use_live = importlib.util.find_spec("ultrazohm_cli") is not None
    from .user_paths import find_repository

    live_repo = getattr(args, "live_repo", None)
    if live_repo is None:
        detected = find_repository(Path.cwd())
        live_repo = str(detected) if detected is not None else None
    app = DataViewerApp(
        initial_files=getattr(args, "files", []),
        loading_mode=loading_mode,
        backend=backend,
        disk_cache=disk_cache,
        use_live=use_live,
        live_repo=live_repo,
        start_live=getattr(args, "live", False),
    )
    try:
        app.enable_control(args.endpoint)
        app.run()
    finally:
        app._shutdown()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
