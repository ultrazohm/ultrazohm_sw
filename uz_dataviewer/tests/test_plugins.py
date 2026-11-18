"""External node-plugin system: loading, robustness, and round-trip."""

from __future__ import annotations

from uz_dataviewer import nodes

import sys

import numpy as np
import pytest


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


def test_partial_plugin_registration_is_rolled_back(tmp_path, clean_registry):
    before = dict(REGISTRY)
    modules = set(sys.modules)
    (tmp_path / 'partial.py').write_text(_PLUGIN + "\nraise RuntimeError('failed after registration')\n")
    assert load_plugins([str(tmp_path)]) == ()
    assert REGISTRY == before
    assert not {name for name in set(sys.modules) - modules if name.startswith('uz_plugin_')}


def test_failed_reload_preserves_module_and_cached_output(tmp_path, clean_registry, app_state):
    from uz_dataviewer.nodes import evaluate, is_stale, register_transform, TransformSpec
    path = tmp_path / 'double.py'
    path.write_text(_PLUGIN)
    load_plugins([str(tmp_path)])
    original = REGISTRY['double']
    module_name = original.compute.__module__
    original_module = sys.modules[module_name]
    run = app_state.registry.add_run('input', 'input', np.arange(8.), {'a': np.ones(8)}, {})
    source = app_state.nodes.add('source', ref=(run.id, 'a'))
    output = app_state.nodes.add('double')
    app_state.nodes.link(source.id, output.id)
    evaluate(app_state)
    with pytest.raises(ValueError, match='already registered'):
        register_transform(TransformSpec('double', lambda inputs, params: None))
    path.write_text(_PLUGIN.replace('"2"', '"300"'))
    assert load_plugins([str(tmp_path)]) == ()
    assert REGISTRY['double'] is original
    assert sys.modules[module_name] is original_module
    assert not is_stale(app_state.registry, app_state.nodes, output)
    assert evaluate(app_state) == 0
    np.testing.assert_array_equal(output.out_y, np.full(8, 2.))


def test_plugin_cannot_replace_builtin_or_leave_earlier_registrations(tmp_path, clean_registry):
    before = dict(REGISTRY)
    (tmp_path / 'collision.py').write_text(_PLUGIN + '\n' + _PLUGIN.replace('"double"', '"math"'))
    assert load_plugins([str(tmp_path)]) == ()
    assert REGISTRY == before


def test_same_filename_in_different_directories_has_distinct_modules(tmp_path, clean_registry):
    directories = [tmp_path / 'a', tmp_path / 'b']
    for directory, kind in zip(directories, ('double', 'triple')):
        directory.mkdir()
        (directory / 'plugin.py').write_text(_PLUGIN.replace('"double"', repr(kind)))
    assert set(load_plugins([str(d) for d in directories])) == {'double', 'triple'}
    assert REGISTRY['double'].compute.__module__ != REGISTRY['triple'].compute.__module__


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
    source = state.registry.runs[0]
    source.path = str(tmp_path / 'source.csv')
    np.savetxt(source.path, np.column_stack([source.time, source.signals['a'].y]), delimiter=';', header='time;a', comments='')
    data = to_dict(state)

    REGISTRY.pop("double", None)  # simulate the plugin not being installed on reload
    state2 = _state_with_run(50)
    apply_dict(state2, data)  # must not raise even though 'double' is now unknown

    node = state2.nodes.get(2)
    assert node is not None and node.kind == "double"  # placeholder kept
    assert node.inputs == [1]  # links preserved


def test_plugin_node_renders_headless(tmp_path, clean_registry, gui_frame):
    from uz_dataviewer.panels.nodes import NodesPanel

    (tmp_path / "double.py").write_text(_PLUGIN)
    load_plugins([str(tmp_path)])

    state = _state_with_run()
    _run(state, "node_source(run_1, a)", "node_add(double)",
         "node_link(node_1, node_2)", "node_eval()")
    panel = NodesPanel()
    try:
        for _ in range(3):
            gui_frame(panel, state, 'Nodes')
    finally:
        state.shutdown()

    assert any(r.derived and r.label == "node_2" for r in state.registry.runs)


@pytest.mark.parametrize('declaration', [
    'ui=[ParamSpec.enum("choice", [])]',
    'inputs=(2, 1)', 'inputs=(0, 1000000)',
    'ui=[ParamSpec("x", "unknown")]',
    'ui=[ParamSpec.float("x"), ParamSpec.int("x")]',
    'params={"x": "nan"}, ui=[ParamSpec.float("x")]',
    'params={"x": "other"}, ui=[ParamSpec.enum("x", ["valid"])]',
])
def test_invalid_plugin_declarations_roll_back(tmp_path, clean_registry, declaration):
    before = dict(REGISTRY)
    (tmp_path / 'bad.py').write_text(_PLUGIN + f'''
@transform("invalid", {declaration})
def invalid(inputs, params):
    return inputs[0][0], inputs[0][1], ""
''')
    assert load_plugins([str(tmp_path)]) == ()
    assert REGISTRY == before


def test_nonstring_plugin_info_fails_only_its_node(app_state, monkeypatch):
    from uz_dataviewer import nodes
    monkeypatch.setitem(REGISTRY, 'bad_info', nodes.TransformSpec(
        'bad_info', lambda i, p: (*i[0], 42)))
    run = app_state.registry.add_run('a', 'a', np.arange(8.), {'a': np.ones(8)}, {})
    source = app_state.nodes.add('source', ref=(run.id, 'a'))
    bad, good = app_state.nodes.add('bad_info'), app_state.nodes.add('math')
    for node in (bad, good):
        app_state.nodes.link(source.id, node.id)
    assert nodes.evaluate(app_state) == 1
    assert 'info must be a string' in bad.error


def test_plugin_bad_dtype_does_not_abort_siblings(app_state, monkeypatch):
    s = app_state
    s.registry.add_run("a", "a", np.arange(8.0), {"a": np.ones(8)}, {})
    src = s.nodes.add("source", ref=(1, "a"))
    monkeypatch.setitem(
        nodes.REGISTRY,
        "bad_dtype",
        nodes.TransformSpec("bad_dtype", lambda i, p: (i[0][0], ["bad"] * 8, "")),
    )
    bad = s.nodes.add("bad_dtype")
    good = s.nodes.add("math")
    s.nodes.link(src.id, bad.id)
    s.nodes.link(src.id, good.id)
    assert nodes.evaluate(s) == 1
    assert bad.error and good.out_y is not None


def test_plugin_cannot_mutate_recording(app_state, monkeypatch):
    s = app_state
    run = s.registry.add_run("a", "a", np.arange(8.0), {"a": np.ones(8)}, {})
    src = s.nodes.add("source", ref=(1, "a"))
    cached = s.nodes.add("math")
    s.nodes.link(src.id, cached.id)
    assert nodes.evaluate(s) == 1

    def mutate(inputs, params):
        t, y = inputs[0]
        y *= 10
        return t, y, "mutated"

    monkeypatch.setitem(nodes.REGISTRY, "mutate", nodes.TransformSpec("mutate", mutate))
    mut = s.nodes.add("mutate")
    s.nodes.link(src.id, mut.id)
    assert nodes.evaluate(s) == 0
    assert "read-only" in mut.error
    assert np.all(run.signals["a"].y == 1) and np.all(cached.out_y == 1)
    assert not nodes.is_stale(s.registry, s.nodes, cached)


def test_documented_moving_average_handles_short_input(monkeypatch):
    import runpy
    from uz_dataviewer import api

    with monkeypatch.context() as patch:
        patch.setattr(nodes, "REGISTRY", dict(nodes.REGISTRY))
        import uz_dataviewer.plugins as plugins

        patch.setattr(plugins, "REGISTRY", nodes.REGISTRY)
        from pathlib import Path

        runpy.run_path(
            str(Path(__file__).parents[1] / "examples/plugins/moving_average.py")
        )
        t, y, _ = api.node("movavg", (np.arange(8.0), np.ones(8)))
        assert len(t) == len(y) == 8


def test_plugin_output_owns_its_buffers(app_state, monkeypatch):
    t, y = np.arange(8.0), np.ones(8, dtype=np.float32)
    monkeypatch.setitem(
        nodes.REGISTRY,
        "retained",
        nodes.TransformSpec("retained", lambda i, p: (t, y, ""), inputs=(0, 0)),
    )
    node = app_state.nodes.add("retained")
    assert nodes.evaluate(app_state) == 1
    t[:] = -1
    y[:] = 99
    np.testing.assert_array_equal(node.out_time, np.arange(8.0))
    np.testing.assert_array_equal(node.out_y, np.ones(8))
