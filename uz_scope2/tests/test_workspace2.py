from __future__ import annotations

from types import SimpleNamespace

import numpy as np
import pytest

from uz_scope2.config import ScopeConfig
from uz_scope2.javascope_header import parse_header
from uz_scope2.ring import ChannelRing
from uz_scope2.segments import SegmentRegistry
from uz_scope2.session import load_state, save_state
from uz_scope2.state import ScopeAppState
from uz_scope2.workspace import PlotType, PlotWorkspace


def test_segment_queries_do_not_cross_remaps_and_expire():
    ring = ChannelRing(1, 8)
    history = SimpleNamespace(pyramid=None, first_index=None)
    registry = SegmentRegistry(1)

    first = registry.start(0, 1, "JSO_first", 0)
    ring.append(np.arange(4, dtype=np.float32)[None, :])
    registry.close(0, 4)
    second = registry.start(0, 2, "JSO_second", 4)
    ring.append((100 + np.arange(4, dtype=np.float32))[None, :])

    x1, y1 = registry.query(history, ring, first.id, 0, 8, 100, 1.0)
    x2, y2 = registry.query(history, ring, second.id, 0, 8, 100, 1.0)
    assert np.array_equal(x1, np.arange(4))
    assert np.array_equal(y1, np.arange(4))
    assert np.array_equal(x2, np.arange(4, 8))
    assert np.array_equal(y2, 100 + np.arange(4))

    ring.append(np.zeros((1, 8), dtype=np.float32))
    assert [item.id for item in registry.retained(ring)] == [second.id]
    assert registry.get(first.id) is None


def test_workspace_roundtrip_and_rebind():
    workspace = PlotWorkspace()
    window = workspace.windows[0]
    window.set_grid(2, 2)
    window.follow_live = False
    cell = window.cells[0]
    cell.segments = [4, 5]
    cell.y2_segments = [5]
    cell.xy_source = 4
    cell.plot_type = PlotType.XY
    workspace.create("Diagnostics")

    restored = PlotWorkspace.from_dict(workspace.to_dict())
    assert len(restored.windows) == 2
    assert (restored.windows[0].rows, restored.windows[0].cols) == (2, 2)
    assert restored.windows[0].cells[0].plot_type is PlotType.XY
    restored.replace_segments({4: 40, 5: 50})
    assert restored.windows[0].cells[0].segments == [40, 50]
    assert restored.windows[0].cells[0].y2_segments == [50]
    assert restored.windows[0].cells[0].xy_source == 40


@pytest.fixture
def state(real_header_path, tmp_path):
    return ScopeAppState(
        config=ScopeConfig(),
        header=parse_header(real_header_path),
        settings_path=tmp_path / "settings.json",
    )


def test_commands_and_session_preserve_observable_assignments(state, tmp_path):
    first = state.acquire_observable(1)
    second = state.acquire_observable(2)
    state.commands.dispatch(state, f"add_signal(window_1, plot_1, {first.token})")
    state.commands.dispatch(state, "set_grid(window_1, 1, 2)")
    state.commands.dispatch(state, f"add_signal(window_1, plot_2, {second.token})")
    state.commands.dispatch(state, "set_axis(window_1, plot_2, signal_2, right)")
    state.commands.dispatch(state, "cursors(window_1, plot_1, true)")
    state.commands.dispatch(state, "spy(window_1, plot_1, true)")
    state.commands.dispatch(state, 'new_plot_window("Power stage")')

    path = save_state(state, tmp_path / "workspace.json")
    fresh = ScopeAppState(
        config=ScopeConfig(),
        header=state.header,
        settings_path=tmp_path / "other.json",
    )
    load_state(fresh, path)

    assert len(fresh.workspace.windows) == 2
    assert fresh.workspace.windows[1].title == "Power stage"
    left, right = fresh.workspace.windows[0].cells
    assert [fresh.segments.get(sid).observable for sid in left.segments] == [1]
    assert [fresh.segments.get(sid).observable for sid in right.segments] == [2]
    assert right.y2_segments == right.segments
    assert left.cursors and left.spy


def test_visible_range_export_uses_raw_samples(state, tmp_path):
    segment = state.acquire_observable(1)
    state.workspace.windows[0].cells[0].add(segment.id)
    data = np.zeros((state.config.channels, 20), dtype=np.float32)
    data[segment.slot] = np.arange(20, dtype=np.float32)
    state.ring.append(data)
    state.last_plot_ranges[(1, 0)] = (5 * state.timestep_s, 10 * state.timestep_s)

    out = tmp_path / "visible.csv"
    state.commands.dispatch(state, f"export_data(window_1, plot_1, {out})")
    exported = np.genfromtxt(out, delimiter=",", names=True)
    assert exported.shape == (5,)
    assert np.array_equal(exported[exported.dtype.names[1]], np.arange(5, 10))


def test_acquisition_changes_are_blocked_while_logging(state):
    state.logger = object()
    with pytest.raises(Exception, match="stop logging"):
        state.acquire_observable(1)
