"""Headless render smoke test: drive real ImGui/ImPlot frames, no GPU window."""

from __future__ import annotations

import numpy as np
import pytest

imgui_bundle = pytest.importorskip("imgui_bundle")

from uz_scope.config import ScopeConfig  # noqa: E402
from uz_scope.javascope_header import parse_header  # noqa: E402
from uz_scope.state import ScopeAppState  # noqa: E402


@pytest.fixture
def gui_context():
    from imgui_bundle import imgui, implot

    imgui.create_context()
    implot.create_context()
    io = imgui.get_io()
    io.display_size = imgui.ImVec2(1500, 900)
    io.delta_time = 1.0 / 60.0
    io.backend_flags |= imgui.BackendFlags_.renderer_has_textures
    yield
    implot.destroy_context()
    imgui.destroy_context()


def make_state(real_header_path, tmp_path) -> ScopeAppState:
    state = ScopeAppState(
        config=ScopeConfig(),
        header=parse_header(real_header_path),
        settings_path=tmp_path / "settings.json",
    )
    # Some live-looking data: 3 logged+visible channels, 10k ring samples.
    for slot in range(3):
        state.select_observable(slot, slot + 2)  # also adds to logged_slots
        state.set_slot_visible(slot, True)
    t = np.arange(10_000, dtype=np.float32)
    block = np.stack([np.sin(t * 0.01 * (slot + 1)) for slot in range(20)])
    state.ring.append(block.astype(np.float32))
    state.last_status = 0b1_0000_0011  # Ready | Running | MyButton5 indicator
    return state


def render_frames(panel, state, frames: int = 3, label: str = "Scope") -> None:
    from imgui_bundle import imgui

    for _ in range(frames):
        imgui.new_frame()
        imgui.begin(label)
        panel.render(state)
        imgui.end()
        imgui.render()


def test_all_panels_render(gui_context, real_header_path, tmp_path):
    from imgui_bundle import imgui

    from uz_scope.panels.control import ControlPanel
    from uz_scope.panels.diagnostics import DiagnosticsPanel
    from uz_scope.panels.logged import LoggedVariablesPanel
    from uz_scope.panels.logging_panel import LoggingPanel
    from uz_scope.panels.observables import ObservablesPanel
    from uz_scope.panels.plot_windows import PlotWindowPanel
    from uz_scope.panels.slowdata_panel import SlowDataPanel
    from uz_scope.panels.trigger import TriggerPanel

    state = make_state(real_header_path, tmp_path)
    state.slowdata.on_block(
        np.array([[1, 2]], dtype=np.int32), np.array([[7, 8]], dtype=np.uint32)
    )
    state.commands.dispatch(state, "trig_arm(on)")  # armed engine + capture path
    panels = {
        "Scope": PlotWindowPanel(0),
        "Logged variables": LoggedVariablesPanel(),
        "Observables": ObservablesPanel(),
        "Control": ControlPanel(),
        "Trigger": TriggerPanel(),
        "SlowData": SlowDataPanel(),
        "Logging": LoggingPanel(),
        "Diagnostics": DiagnosticsPanel(),
    }
    for _ in range(3):
        imgui.new_frame()
        for label, panel in panels.items():
            imgui.begin(label)
            panel.render(state)
            imgui.end()
        imgui.begin("Console")
        state.console.render(state)
        imgui.end()
        imgui.render()

    # Plot window 1 cell 1 built decimated series for the visible channels.
    series = panels["Scope"]._cells[0].series
    assert len(series) == 3
    label, xs, ys, _color, slot = series[0]
    assert label.startswith("CH1 ") and slot == 0
    assert xs.size > 0 and xs.size == ys.size


def test_plot_renders_capture_with_crosshair_and_colors(
    gui_context, real_header_path, tmp_path
):
    """Exercises the implot.Spec paths: colored lines + trigger inf-lines."""
    from uz_scope.panels.plot_windows import PlotWindowPanel

    state = make_state(real_header_path, tmp_path)
    state.config.channel_settings[0].color = "#ff8800"
    state.config.trigger.mode = "single"
    state.config.trigger.level = 0.0
    state.config.trigger.pretrigger = 0.0
    state.config.window_seconds = 0.01  # 100 samples at 10 kHz
    state.commands.dispatch(state, "trig_arm(on)")
    # Drive the engine directly with a step so a capture exists.
    step = np.concatenate([np.full(50, -1.0), np.ones(200)]).astype(np.float32)
    start = state.ring.total_written
    state.ring.append(np.tile(step, (20, 1)))
    state.engine.on_block(step, start)
    assert state.engine.capture is not None

    panel = PlotWindowPanel(0)
    render_frames(panel, state)
    assert panel._trigger_time is not None
    series = panel._cells[0].series
    assert series and series[0][3] is not None  # colored line drawn


def test_plot_level_line_while_armed_keeps_rolling(
    gui_context, real_header_path, tmp_path
):
    """Armed but not yet triggered: the plot keeps rolling and draws the
    level line transformed with the source channel's scale/offset."""
    from uz_scope.panels.plot_windows import PlotWindowPanel

    state = make_state(real_header_path, tmp_path)
    state.config.channel_settings[0].scale = 2.0
    state.config.channel_settings[0].offset = 1.0
    state.config.trigger.channel = 1
    state.config.trigger.level = 5.0
    state.config.trigger.mode = "normal"
    state.commands.dispatch(state, "trig_arm(on)")
    assert state.engine is not None and state.engine.capture is None

    panel = PlotWindowPanel(0)
    render_frames(panel, state, frames=2)
    assert panel._level_display == pytest.approx((5.0 + 1.0) / 2.0)
    assert panel._trigger_time is None  # no capture -> no time crosshair
    assert panel._cells[0].series  # rolling display still live


def test_plot_auto_stale_capture_falls_back_to_rolling(
    gui_context, real_header_path, tmp_path
):
    from uz_scope.panels.plot_windows import PlotWindowPanel

    state = make_state(real_header_path, tmp_path)
    state.config.trigger.mode = "auto"
    state.config.trigger.pretrigger = 0.0
    state.config.window_seconds = 0.01  # W=100 samples, auto_timeout=200
    state.commands.dispatch(state, "trig_arm(on)")
    step = np.concatenate([np.full(50, -1.0), np.ones(200)]).astype(np.float32)
    start = state.ring.total_written
    state.ring.append(np.tile(step, (20, 1)))
    state.engine.on_block(step, start)
    assert state.engine.capture is not None

    panel = PlotWindowPanel(0)
    render_frames(panel, state, frames=1)
    assert panel._trigger_time is not None  # fresh capture is displayed

    # The edge source goes quiet for longer than auto_timeout.
    quiet = np.ones(500, dtype=np.float32)
    start = state.ring.total_written
    state.ring.append(np.tile(quiet, (20, 1)))
    state.engine.on_block(quiet, start)
    assert state.engine.capture_is_stale()

    panel._next_refresh = 0.0  # force the next refresh tick
    render_frames(panel, state, frames=1)
    assert panel._trigger_time is None  # back to rolling
    assert panel._level_display is not None  # level line still shown
    end_t = state.ring.total_written / state.sample_rate
    assert panel._x_range[1] == pytest.approx(end_t, abs=1e-6)


def test_plot_grid_and_second_window_render(
    gui_context, real_header_path, tmp_path
):
    """A 1x2 grid in window 1 plus an independent second plot window."""
    from uz_scope.panels.plot_windows import PlotWindowPanel, PlotWindowsManager

    state = make_state(real_header_path, tmp_path)
    state.commands.dispatch(state, "plot_grid(1, 1, 2)")
    state.commands.dispatch(state, "plot_assign(1, 2, 4)")
    state.commands.dispatch(state, "plot_add(Second)")
    state.commands.dispatch(state, "plot_assign(2, 1, 5)")

    manager = PlotWindowsManager(state)
    manager.startup_windows()
    manager.sync()
    assert len(manager.panels) == 2

    for panel, label in zip(manager.panels, ("Scope", "Second")):
        panel._next_refresh = 0.0
        render_frames(panel, state, frames=2, label=label)
    win1 = manager.panels[0]
    assert len(win1._cells) == 2
    assert win1._cells[1].series and win1._cells[1].series[0][4] == 3
    win2 = manager.panels[1]
    assert win2._cells[0].series and win2._cells[0].series[0][4] == 4


def test_plot_cont_mode_and_detach_pending(
    gui_context, real_header_path, tmp_path
):
    """cont mode spans the session; x_lim detaches and fetches that range."""
    from uz_scope.panels.plot_windows import PlotWindowPanel

    state = make_state(real_header_path, tmp_path)
    state.commands.dispatch(state, "plot_xmode(1, cont)")
    panel = PlotWindowPanel(0)
    render_frames(panel, state, frames=2)
    assert panel._x_range is not None
    assert panel._x_range[0] == pytest.approx(0.0)
    end_t = state.ring.total_written / state.sample_rate
    assert panel._x_range[1] == pytest.approx(end_t, abs=1e-6)

    state.commands.dispatch(state, "x_lim(1, 0.1, 0.2)")
    view = state.plot_view(1)
    assert not view.attached and view.pending_x == (0.1, 0.2)
    panel._next_refresh = 0.0
    render_frames(panel, state, frames=1)
    assert view.pending_x is None  # consumed by the render
    series = panel._cells[0].series
    assert series
    xs = series[0][1]
    assert xs.min() >= 0.1 - 0.01 and xs.max() <= 0.2 + 0.01

    state.commands.dispatch(state, "plot_follow(1, on)")
    assert view.attached


def test_plot_renders_before_any_data_arrives(
    gui_context, real_header_path, tmp_path
):
    """Startup with visible channels but an EMPTY ring must not crash —
    implot.plot_line rejects empty arrays (field-reported crash)."""
    from uz_scope.panels.plot_windows import PlotWindowPanel

    state = ScopeAppState(
        config=ScopeConfig(),
        header=parse_header(real_header_path),
        settings_path=tmp_path / "settings.json",
    )
    for slot in range(3):
        state.select_observable(slot, slot + 2)
        state.set_slot_visible(slot, True)
    assert state.ring.filled == 0  # no connection yet
    panel = PlotWindowPanel(0)
    render_frames(panel, state, frames=2)
    assert panel._cells[0].series == []  # empty data -> no series entries

    # The trigger-capture path tolerates it too.
    state.commands.dispatch(state, "trig_arm(on)")
    render_frames(panel, state, frames=2)


def test_statusbar_renders(gui_context, real_header_path, tmp_path):
    from imgui_bundle import imgui

    from uz_scope.panels.statusbar import StatusBar

    state = make_state(real_header_path, tmp_path)
    bar = StatusBar()
    for _ in range(2):
        imgui.new_frame()
        imgui.begin("Status")
        bar.render(state)
        imgui.end()
        imgui.render()
