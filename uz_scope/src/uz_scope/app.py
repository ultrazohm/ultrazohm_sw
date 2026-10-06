"""Application entry point and docking layout.

    +-------------------------------------------------------+
    |   Scope [1..n] / Control / Logging | Logged variables |
    |            (center, tabs)          | / Observables    |
    |------------------------------------+------------------|
    |                  Console (bottom)                     |
    +-------------------------------------------------------+

Same shell recipe as uz_dataviewer: hello_imgui full-screen dock space,
MaterialFlat theme, and **idling disabled** — hello_imgui would otherwise drop
to ~9 fps without input, which is unusable for a live scope.
"""

from __future__ import annotations

import argparse
import socket
import sys

from imgui_bundle import hello_imgui, imgui, immapp

from .panels.control import ControlPanel
from .panels.dashboard_panel import DashboardPanel
from .panels.diagnostics import DiagnosticsPanel
from .panels.logged import LoggedVariablesPanel
from .panels.logging_panel import LoggingPanel
from .panels.observables import ObservablesPanel
from .panels.plot_windows import PlotWindowsManager
from .panels.slowdata_panel import SlowDataPanel
from .panels.statusbar import StatusBar
from .panels.trigger import TriggerPanel
from .state import ScopeAppState

MAIN_DOCK = "MainDockSpace"
RIGHT_DOCK = "RightSpace"
RIGHT_BOTTOM_DOCK = "RightBottomSpace"  # Observables, below Logged variables
BOTTOM_DOCK = "BottomSpace"

# Only one client fits the APU's single connection slot; a second local
# instance would just steal it. Advisory localhost bind as the guard.
SINGLE_INSTANCE_PORT = 47617


class ScopeApp:
    def __init__(self, state: ScopeAppState, connect_on_start: bool = False) -> None:
        self.state = state
        self.connect_on_start = connect_on_start
        self.plots = PlotWindowsManager(
            state,
            dock_space=MAIN_DOCK,
            add_window_fn=lambda win: hello_imgui.add_dockable_window(
                win, force_dockspace=True
            ),
            remove_window_fn=hello_imgui.remove_dockable_window,
        )
        self.logged = LoggedVariablesPanel()
        self.observables = ObservablesPanel()
        self.dashboard = DashboardPanel()
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
                "another uz_scope instance appears to be running — the "
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

        # Same column as Logged variables, stacked below it.
        right_bottom = hello_imgui.DockingSplit()
        right_bottom.initial_dock = RIGHT_DOCK
        right_bottom.new_dock = RIGHT_BOTTOM_DOCK
        right_bottom.direction = imgui.Dir_.down
        right_bottom.ratio = 0.5
        return [right, bottom, right_bottom]

    def _dockable_windows(self) -> list[hello_imgui.DockableWindow]:
        def window(label, dock, render):
            win = hello_imgui.DockableWindow()
            win.label = label
            win.dock_space_name = dock
            win.gui_function = render
            return win

        return self.plots.startup_windows() + [
            window("Control", MAIN_DOCK, lambda: self.control.render(self.state)),
            window("Dashboard", MAIN_DOCK, lambda: self.dashboard.render(self.state)),
            window("Trigger", MAIN_DOCK, lambda: self.trigger.render(self.state)),
            window("SlowData", MAIN_DOCK, lambda: self.slowdata.render(self.state)),
            window("Logging", MAIN_DOCK, lambda: self.logging.render(self.state)),
            window("Diagnostics", MAIN_DOCK, lambda: self.diagnostics.render(self.state)),
            window("Logged variables", RIGHT_DOCK,
                   lambda: self.logged.render(self.state)),
            window("Observables", RIGHT_BOTTOM_DOCK,
                   lambda: self.observables.render(self.state)),
            window("Console", BOTTOM_DOCK, lambda: self.state.console.render(self.state)),
        ]

    def _post_init(self) -> None:
        self._acquire_instance_lock()
        if self.state.config.auto_connect or self.connect_on_start:
            self.state.commands.dispatch(self.state, "connect")

    def run(self) -> None:
        params = hello_imgui.RunnerParams()
        params.app_window_params.window_title = "UltraZohm Scope"
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
        # v2: the window set changed (multi-plot etc.) — old layouts are
        # invalid, so a new ini name gives everyone a fresh default layout.
        params.ini_filename = "uz_scope_layout_v2.ini"

        params.docking_params.docking_splits = self._docking_splits()
        params.docking_params.dockable_windows = self._dockable_windows()
        # Bumped when the default layout changes: hello_imgui stores layouts
        # per name, so a new name re-applies the default even with an
        # existing layout ini.
        params.docking_params.layout_name = "UltraZohmScope v2"

        def pre_new_frame() -> None:
            self.state.poll_events()
            self.plots.sync()  # reconcile plot windows with config.plots

        params.callbacks.pre_new_frame = pre_new_frame
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
    # CLI flags are session-only overrides — the config is saved on exit, so
    # writing them into it would silently persist a test-server address.
    if args.ip:
        state.ip_override = args.ip
    if args.port:
        state.port_override = args.port

    # --connect is a one-off, NOT persisted (unlike the auto_connect setting).
    app = ScopeApp(state, connect_on_start=args.connect)
    app.run()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
