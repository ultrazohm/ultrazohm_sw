"""Application entry point for the dockable UltraZohm Scope 2 GUI.

The first plot workspace is docked beside Signals; additional plot windows are
regular movable ImGui windows.  Live rendering keeps Hello ImGui idling disabled.
"""

from __future__ import annotations

import argparse
import socket
import sys

from imgui_bundle import hello_imgui, imgui, immapp

from .panels.signals import SignalsPanel
from .panels.control import ControlPanel
from .panels.diagnostics import DiagnosticsPanel
from .panels.logging_panel import LoggingPanel
from .panels.workspace_plot import WorkspacePlotPanel
from .panels.slowdata_panel import SlowDataPanel
from .panels.statusbar import StatusBar
from .panels.trigger import TriggerPanel
from .state import ScopeAppState

MAIN_DOCK = "MainDockSpace"
RIGHT_DOCK = "RightSpace"
BOTTOM_DOCK = "BottomSpace"

# Only one client fits the APU's single connection slot; a second local
# instance would just steal it. Advisory localhost bind as the guard.
SINGLE_INSTANCE_PORT = 47618


class ScopeApp:
    def __init__(self, state: ScopeAppState, connect_on_start: bool = False) -> None:
        self.state = state
        self.connect_on_start = connect_on_start
        self.scope = WorkspacePlotPanel()
        self.signals = SignalsPanel()
        self.control = ControlPanel()
        self.trigger = TriggerPanel()
        self.slowdata = SlowDataPanel()
        self.logging = LoggingPanel()
        self.diagnostics = DiagnosticsPanel()
        self.statusbar = StatusBar()
        self._instance_lock: socket.socket | None = None

    def _acquire_instance_lock(self) -> None:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            sock.bind(("127.0.0.1", SINGLE_INSTANCE_PORT))
            sock.listen(1)
            self._instance_lock = sock  # held for the app's lifetime
            self.state.single_instance = True
        except OSError:
            sock.close()
            self.state.single_instance = False
            self.state.console.warn(
                "another uz_scope2 instance appears to be running — the "
                "UltraZohm accepts only one client at a time"
            )

    def _docking_splits(self) -> list[hello_imgui.DockingSplit]:
        right = hello_imgui.DockingSplit()
        right.initial_dock = MAIN_DOCK
        right.new_dock = RIGHT_DOCK
        right.direction = imgui.Dir_.right
        right.ratio = 0.24

        bottom = hello_imgui.DockingSplit()
        bottom.initial_dock = MAIN_DOCK
        bottom.new_dock = BOTTOM_DOCK
        bottom.direction = imgui.Dir_.down
        bottom.ratio = 0.22
        return [right, bottom]

    def _dockable_windows(self) -> list[hello_imgui.DockableWindow]:
        def window(label, dock, render):
            win = hello_imgui.DockableWindow()
            win.label = label
            win.dock_space_name = dock
            win.gui_function = render
            return win

        return [
            window("Plots", MAIN_DOCK, lambda: self.scope.render(self.state, self.state.workspace.windows[0])),
            window("Control", MAIN_DOCK, lambda: self.control.render(self.state)),
            window("Trigger", MAIN_DOCK, lambda: self.trigger.render(self.state)),
            window("SlowData", MAIN_DOCK, lambda: self.slowdata.render(self.state)),
            window("Logging", MAIN_DOCK, lambda: self.logging.render(self.state)),
            window("Diagnostics", MAIN_DOCK, lambda: self.diagnostics.render(self.state)),
            window("Signals", RIGHT_DOCK, lambda: self.signals.render(self.state)),
            window("Console", BOTTOM_DOCK, lambda: self.state.console.render(self.state)),
        ]

    def _render_dynamic_plots(self) -> None:
        for window in self.state.workspace.windows[1:]:
            if not window.open:
                continue
            imgui.begin(f"{window.title}###{window.token}")
            self.scope.render(self.state, window)
            imgui.end()

    def _post_init(self) -> None:
        self._acquire_instance_lock()
        if self.state.config.auto_connect or self.connect_on_start:
            self.state.commands.dispatch(self.state, "connect")

    def run(self) -> None:
        params = hello_imgui.RunnerParams()
        params.app_window_params.window_title = "UltraZohm Scope 2"
        params.app_window_params.window_geometry.size = (1500, 900)
        params.imgui_window_params.default_imgui_window_type = (
            hello_imgui.DefaultImGuiWindowType.provide_full_screen_dock_space
        )
        params.imgui_window_params.show_status_bar = True
        params.imgui_window_params.show_menu_bar = False
        # Live plotting needs full-rate rendering; hello_imgui idles to ~9 fps
        # without input otherwise.
        params.fps_idling.enable_idling = False
        params.imgui_window_params.tweaked_theme.theme = (
            hello_imgui.ImGuiTheme_.material_flat
        )
        params.ini_filename = "uz_scope2_layout.ini"

        params.docking_params.docking_splits = self._docking_splits()
        params.docking_params.dockable_windows = self._dockable_windows()
        params.docking_params.layout_name = "UltraZohmScope"

        params.callbacks.pre_new_frame = self.state.poll_events
        params.callbacks.show_gui = self._render_dynamic_plots
        params.callbacks.show_status = lambda: self.statusbar.render(self.state)
        params.callbacks.post_init = self._post_init
        params.callbacks.before_exit = self.state.shutdown

        addons = immapp.AddOnsParams()
        addons.with_implot = True
        immapp.run(params, addons)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="UltraZohm live scope")
    parser.add_argument("--ip", help="device IP (overrides saved settings)")
    parser.add_argument("--port", type=int, help="device TCP port")
    parser.add_argument("--connect", action="store_true", help="connect on startup")
    args = parser.parse_args(sys.argv[1:] if argv is None else argv)

    state = ScopeAppState()
    if args.ip:
        state.config.ip = args.ip
    if args.port:
        state.config.port = args.port

    # --connect is a one-off, NOT persisted (unlike the auto_connect setting).
    app = ScopeApp(state, connect_on_start=args.connect)
    app.run()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
