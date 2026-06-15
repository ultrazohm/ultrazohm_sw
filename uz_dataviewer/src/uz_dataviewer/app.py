"""UltraZohm data viewer application: 3-pane layout (navigation left, plots
right, console bottom) built on hello_imgui docking + implot."""

from __future__ import annotations

import argparse
import os
import sys

from imgui_bundle import hello_imgui, imgui, immapp

from uz_dataviewer import __version__
from uz_dataviewer.ui.app_state import AppState
from uz_dataviewer.ui.console_panel import ConsolePanel
from uz_dataviewer.ui.navigation_panel import NavigationPanel
from uz_dataviewer.ui.plot_grid import PlotGrid


def _make_runner_params(state: AppState, smoke_frames: int = 0) -> hello_imgui.RunnerParams:
    navigation = NavigationPanel(state)
    plot_grid = PlotGrid(state)
    console = ConsolePanel(state)

    runner_params = hello_imgui.RunnerParams()
    runner_params.app_window_params.window_title = f"UltraZohm Data Viewer {__version__}"
    runner_params.app_window_params.window_geometry.size = (1600, 900)
    runner_params.app_window_params.restore_previous_geometry = True

    window_params = runner_params.imgui_window_params
    window_params.default_imgui_window_type = (
        hello_imgui.DefaultImGuiWindowType.provide_full_screen_dock_space
    )
    window_params.show_status_bar = True
    window_params.tweaked_theme.theme = hello_imgui.ImGuiTheme_.darcula_darker

    # VS-Code-like layout: console strip at the bottom, navigation on the
    # left, plots fill the remaining main space.
    split_console = hello_imgui.DockingSplit(
        "MainDockSpace", "ConsoleSpace", imgui.Dir.down, 0.22
    )
    split_navigation = hello_imgui.DockingSplit(
        "MainDockSpace", "NavigationSpace", imgui.Dir.left, 0.22
    )

    window_navigation = hello_imgui.DockableWindow(
        "Data", "NavigationSpace", navigation.render, can_be_closed_=False
    )
    window_plots = hello_imgui.DockableWindow(
        "Plots", "MainDockSpace", plot_grid.render, can_be_closed_=False
    )
    window_console = hello_imgui.DockableWindow(
        "Console", "ConsoleSpace", console.render, can_be_closed_=False
    )

    runner_params.docking_params = hello_imgui.DockingParams(
        docking_splits=[split_console, split_navigation],
        dockable_windows=[window_navigation, window_plots, window_console],
    )

    frame_counter = {"count": 0}

    def pre_new_frame() -> None:
        state.on_new_frame()
        if smoke_frames > 0:
            frame_counter["count"] += 1
            if frame_counter["count"] >= smoke_frames:
                hello_imgui.get_runner_params().app_shall_exit = True

    runner_params.callbacks.pre_new_frame = pre_new_frame
    runner_params.callbacks.before_exit = state.store.shutdown

    # Re-render only on input/load activity; keeps CPU/GPU usage low.
    runner_params.fps_idling.enable_idling = True
    return runner_params


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        prog="uz-dataviewer",
        description="UltraZohm data viewer for javascope log files (.csv / .parquet)",
    )
    parser.add_argument("files", nargs="*", help="log files to open at startup")
    parser.add_argument(
        "--smoke-frames",
        type=int,
        default=0,
        help="render N frames and exit (for automated testing)",
    )
    parser.add_argument("--version", action="version", version=__version__)
    args = parser.parse_args(argv)

    state = AppState()
    state.console.info(f"UltraZohm Data Viewer {__version__}")

    startup_files = [f for f in args.files if os.path.exists(f)]
    for missing in set(args.files) - set(startup_files):
        state.console.error(f"File not found: '{missing}'")
    if startup_files:
        state.store.load_files_async(startup_files)

    runner_params = _make_runner_params(state, smoke_frames=args.smoke_frames)
    add_ons = immapp.AddOnsParams(with_implot=True)
    immapp.run(runner_params, add_ons)
    return 0


if __name__ == "__main__":
    sys.exit(main())
