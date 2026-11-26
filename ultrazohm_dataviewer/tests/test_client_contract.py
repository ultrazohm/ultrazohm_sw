"""The generated Python client matches the command specifications."""


def test_discovered_handles_work(control_session):
    import numpy as np

    from ultrazohm_dataviewer import NodeHandle, RunHandle, ViewHandle

    state, client, workers, pump = control_session
    state.registry.add_run("manual", "", np.arange(3.0), {"y": np.arange(3.0)}, {})

    def script():
        run = client.list_runs()[0]["handle"]
        assert isinstance(run, RunHandle)
        client.add_signal(1, run, "y")
        client.node_source(run, "y")
        assert isinstance(client.list_nodes()[0]["handle"], NodeHandle)
        view = client.create_view()
        assert isinstance(client.list_views()[-1]["handle"], ViewHandle)
        client.close_view(view)

    future = workers.submit(script)
    pump(future.done)
    future.result()


def test_generated_client_methods_are_current():
    import importlib.util
    from pathlib import Path

    path = Path(__file__).resolve().parents[1] / "tools" / "generate_client.py"
    spec = importlib.util.spec_from_file_location("generate_client", path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    module.main(["--check"])


def test_client_registry_contract():
    import inspect

    from ultrazohm_dataviewer.cli import parameter_kind
    from ultrazohm_dataviewer.client_methods import ViewerMethods
    from ultrazohm_dataviewer.commands import CommandRegistry

    registry = CommandRegistry()
    types = {"plot": "int", "run": "RunHandle", "node": "NodeHandle", "fwindow": "str"}
    for name, method in inspect.getmembers(ViewerMethods, inspect.isfunction):
        command = registry.get(name)
        assert command is not None, name
        params = [
            p
            for p in inspect.signature(method).parameters.values()
            if p.name not in ("self", "view")
        ]
        assert [p.name for p in params] == [p.name for p in command.params], name
        for actual, expected in zip(params, command.params, strict=False):
            assert parameter_kind(actual) == types.get(expected.kind, expected.kind), (
                name,
                actual.name,
            )
            assert (
                actual.default is not inspect.Parameter.empty
            ) == expected.optional, (name, actual.name)
        accepts_view = "view" in inspect.signature(method).parameters
        assert accepts_view == (
            any(p.kind == "plot" for p in command.params) or name == "set_max_points"
        ), name
