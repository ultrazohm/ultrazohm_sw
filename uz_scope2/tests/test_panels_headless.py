"""Headless render smoke test: drive real ImGui/ImPlot frames, no GPU window."""

from __future__ import annotations

import numpy as np
import pytest

imgui_bundle = pytest.importorskip("imgui_bundle")

from uz_scope2.config import ScopeConfig  # noqa: E402
from uz_scope2.javascope_header import parse_header  # noqa: E402
from uz_scope2.state import ScopeAppState  # noqa: E402


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
    # Some live-looking data: 3 visible channels, 10k samples in the ring.
    for slot in range(3):
        state.config.channel_settings[slot].visible = True
    t = np.arange(10_000, dtype=np.float32)
    block = np.stack([np.sin(t * 0.01 * (slot + 1)) for slot in range(20)])
    state.ring.append(block.astype(np.float32))
    state.last_status = 0b1_0000_0011  # Ready | Running | MyButton5 indicator
    return state


def test_all_panels_render(gui_context, real_header_path, tmp_path):
    from imgui_bundle import imgui

    from uz_scope2.panels.channels import ChannelsPanel
    from uz_scope2.panels.control import ControlPanel
    from uz_scope2.panels.logging_panel import LoggingPanel
    from uz_scope2.panels.scope_plot import ScopePlotPanel
    from uz_scope2.panels.diagnostics import DiagnosticsPanel
    from uz_scope2.panels.slowdata_panel import SlowDataPanel
    from uz_scope2.panels.trigger import TriggerPanel

    state = make_state(real_header_path, tmp_path)
    state.slowdata.on_block(
        np.array([[1, 2]], dtype=np.int32), np.array([[7, 8]], dtype=np.uint32)
    )
    state.commands.dispatch(state, "trig_arm(on)")  # armed engine + capture path
    panels = {
        "Scope": ScopePlotPanel(),
        "Channels": ChannelsPanel(),
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

    # The scope panel actually built decimated series for the visible channels.
    assert len(panels["Scope"]._series) == 3
    label, xs, ys, _color = panels["Scope"]._series[0]
    assert label.startswith("CH1 ")
    assert xs.size > 0 and xs.size == ys.size


def test_scope_plot_renders_capture_with_crosshair_and_colors(
    gui_context, real_header_path, tmp_path
):
    """Exercises the implot.Spec paths: colored lines + trigger inf-lines."""
    from imgui_bundle import imgui

    from uz_scope2.panels.scope_plot import ScopePlotPanel

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

    panel = ScopePlotPanel()
    for _ in range(3):
        imgui.new_frame()
        imgui.begin("Scope")
        panel.render(state)
        imgui.end()
        imgui.render()
    assert panel._trigger_time is not None
    assert panel._series and panel._series[0][3] is not None  # colored line drawn


def test_scope_plot_level_line_while_armed_keeps_rolling(
    gui_context, real_header_path, tmp_path
):
    """Armed but not yet triggered: the plot keeps rolling and draws the
    level line transformed with the source channel's scale/offset."""
    from imgui_bundle import imgui

    from uz_scope2.panels.scope_plot import ScopePlotPanel

    state = make_state(real_header_path, tmp_path)
    state.config.channel_settings[0].scale = 2.0
    state.config.channel_settings[0].offset = 1.0
    state.config.trigger.channel = 1
    state.config.trigger.level = 5.0
    state.config.trigger.mode = "normal"
    state.commands.dispatch(state, "trig_arm(on)")
    assert state.engine is not None and state.engine.capture is None

    panel = ScopePlotPanel()
    for _ in range(2):
        imgui.new_frame()
        imgui.begin("Scope")
        panel.render(state)
        imgui.end()
        imgui.render()
    assert panel._level_display == pytest.approx((5.0 + 1.0) / 2.0)
    assert panel._trigger_time is None  # no capture -> no time crosshair
    assert panel._series  # rolling display still live


def test_scope_plot_auto_stale_capture_falls_back_to_rolling(
    gui_context, real_header_path, tmp_path
):
    from imgui_bundle import imgui

    from uz_scope2.panels.scope_plot import ScopePlotPanel

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

    panel = ScopePlotPanel()
    imgui.new_frame()
    imgui.begin("Scope")
    panel.render(state)
    imgui.end()
    imgui.render()
    assert panel._trigger_time is not None  # fresh capture is displayed

    # The edge source goes quiet for longer than auto_timeout.
    quiet = np.ones(500, dtype=np.float32)
    start = state.ring.total_written
    state.ring.append(np.tile(quiet, (20, 1)))
    state.engine.on_block(quiet, start)
    assert state.engine.capture_is_stale()

    imgui.new_frame()
    imgui.begin("Scope")
    panel.render(state)
    imgui.end()
    imgui.render()
    assert panel._trigger_time is None  # back to rolling
    assert panel._level_display is not None  # level line still shown
    end_t = state.ring.total_written / state.sample_rate
    assert panel._x_range[1] == pytest.approx(end_t, abs=1e-6)


def test_statusbar_renders(gui_context, real_header_path, tmp_path):
    from imgui_bundle import imgui

    from uz_scope2.panels.statusbar import StatusBar

    state = make_state(real_header_path, tmp_path)
    bar = StatusBar()
    for _ in range(2):
        imgui.new_frame()
        imgui.begin("Status")
        bar.render(state)
        imgui.end()
        imgui.render()


def test_workspace_panels_render_with_tools(gui_context, real_header_path, tmp_path):
    from imgui_bundle import imgui

    from uz_scope2.panels.signals import SignalsPanel
    from uz_scope2.panels.workspace_plot import WorkspacePlotPanel

    state = make_state(real_header_path, tmp_path)
    first = state.acquire_observable(1)
    second = state.acquire_observable(2)
    state.workspace.windows[0].cells[0].segments = [first.id, second.id]
    state.workspace.windows[0].cells[0].cursors = True
    state.workspace.windows[0].cells[0].spy = True
    block = np.zeros((state.config.channels, 200), dtype=np.float32)
    block[first.slot] = np.sin(np.arange(200) * 0.05)
    block[second.slot] = np.cos(np.arange(200) * 0.05)
    state.ring.append(block)
    state.history.on_block(block, state.ring.total_written - block.shape[1])

    signals = SignalsPanel()
    plots = WorkspacePlotPanel()
    for _ in range(3):
        imgui.new_frame()
        imgui.begin("Signals 2")
        signals.render(state)
        imgui.end()
        imgui.begin("Plots 2")
        plots.render(state, state.workspace.windows[0])
        imgui.end()
        imgui.render()

    assert plots._ranges[(1, 0)][1] > plots._ranges[(1, 0)][0]
    assert plots._cursor_text[(1, 0)].startswith("Δx=")
    assert state.workspace.windows[0].cells[0].spy_rect is not None
