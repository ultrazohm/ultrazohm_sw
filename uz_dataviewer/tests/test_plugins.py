"""External node-plugin system: loading, robustness, and round-trip."""

from __future__ import annotations

import os
import sys

import numpy as np
import pytest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))

from uz_dataviewer.nodes import REGISTRY, transform_kinds  # noqa: E402
from uz_dataviewer.plugins import load_plugins  # noqa: E402
from uz_dataviewer.session import apply_dict, to_dict  # noqa: E402
from uz_dataviewer.state import AppState  # noqa: E402

_PLUGIN = '''
import numpy as np
from uz_dataviewer.plugins import transform, ParamSpec

@transform("double", params={"k": "2"}, inputs=(1, 1), ui=[ParamSpec.float("k", "k")])
def double(inputs, params):
    t, y = inputs[0]
    return t, np.asarray(y, float) * float(params.get("k", 2)), "doubled"
'''


@pytest.fixture
def clean_registry():
    """Remove any transforms a test registers, so the global REGISTRY stays clean."""
    before = set(REGISTRY)
    yield
    for k in list(REGISTRY):
        if k not in before:
            REGISTRY.pop(k, None)


def _run(state, *lines):
    for line in lines:
        state.commands.dispatch(state, line)


def _state_with_run(n=100):
    state = AppState()
    t = np.linspace(0.0, 1.0, n)
    state.registry.add_run("L", "L", t, {"a": np.ones(n, np.float32)}, {"a": ""})
    return state


def test_plugin_loads_and_runs(tmp_path, clean_registry):
    (tmp_path / "double.py").write_text(_PLUGIN)
    new = load_plugins([str(tmp_path)])
    assert "double" in new and "double" in REGISTRY

    state = _state_with_run()
    _run(state, "node_source(run_1, a)", "node_add(double)", "node_set(node_2, k, 5)",
         "node_link(node_1, node_2)", "node_eval()")
    derived = next(r for r in state.registry.runs if r.derived)
    assert abs(float(derived.signals["out"].y.mean()) - 5.0) < 1e-5  # a(=1) * k(=5)


def test_missing_directory_is_safe(clean_registry):
    assert load_plugins(["/no/such/uz/plugin/dir"]) == ()  # no error, nothing loaded


def test_no_plugins_leaves_builtins_intact(clean_registry):
    load_plugins([])  # empty search list
    assert {"fft", "math", "filter", "shift"} <= set(transform_kinds())


def test_broken_plugin_is_skipped_and_logged(tmp_path, clean_registry):
    (tmp_path / "bad.py").write_text("raise RuntimeError('boom')\n")
    (tmp_path / "good.py").write_text(_PLUGIN.replace('"double"', '"triple"'))

    class _Console:
        def __init__(self):
            self.errors = []

        def error(self, msg):
            self.errors.append(msg)

        def ok(self, msg):
            pass

    console = _Console()
    new = load_plugins([str(tmp_path)], console=console)
    assert "triple" in new  # the good plugin still loaded
    assert any("bad.py" in e for e in console.errors)  # the broken one was reported


def test_unknown_kind_restores_as_placeholder(tmp_path, clean_registry):
    (tmp_path / "double.py").write_text(_PLUGIN)
    load_plugins([str(tmp_path)])

    state = _state_with_run(50)
    _run(state, "node_source(run_1, a)", "node_add(double)",
         "node_link(node_1, node_2)", "node_eval()")
    data = to_dict(state)

    REGISTRY.pop("double", None)  # simulate the plugin not being installed on reload
    state2 = _state_with_run(50)
    apply_dict(state2, data)  # must not raise even though 'double' is now unknown

    node = state2.nodes.get(2)
    assert node is not None and node.kind == "double"  # placeholder kept
    assert node.inputs == [1]  # links preserved


def test_plugin_node_renders_headless(tmp_path, clean_registry):
    from imgui_bundle import imgui, implot
    from imgui_bundle import imgui_node_editor as ed

    from uz_dataviewer.panels.nodes import NodesPanel

    (tmp_path / "double.py").write_text(_PLUGIN)
    load_plugins([str(tmp_path)])

    imgui.create_context()
    implot.create_context()
    io = imgui.get_io()
    io.display_size = imgui.ImVec2(1200, 800)
    io.delta_time = 1.0 / 60.0
    io.backend_flags |= imgui.BackendFlags_.renderer_has_textures
    editor = ed.create_editor()
    ed.set_current_editor(editor)

    state = _state_with_run()
    _run(state, "node_source(run_1, a)", "node_add(double)",
         "node_link(node_1, node_2)", "node_eval()")
    panel = NodesPanel()
    try:
        for _ in range(3):
            imgui.new_frame()
            imgui.begin("Nodes")
            panel.render(state)  # exercises the generic ParamSpec widget path
            imgui.end()
            imgui.render()
    finally:
        ed.destroy_editor(editor)
        implot.destroy_context()
        imgui.destroy_context()

    assert any(r.derived and r.label == "node_2" for r in state.registry.runs)
