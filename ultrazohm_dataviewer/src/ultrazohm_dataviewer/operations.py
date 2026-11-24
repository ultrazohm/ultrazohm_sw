"""Typed viewer operations and application-owned completion of background work."""

import threading
import uuid
from concurrent.futures import Future

from .application_mutations import add_signal as add_signal
from .application_mutations import link_x as link_x
from .application_mutations import set_grid as set_grid
from .client import ViewerError
from .workers import CancellableExecutor, Cancellation, cancellable_result


class Operations:
    """Lives with the application, surviving replacement of its session state.

    Both dispatch and poll belong to the application thread. IO workers prepare
    data only; registration and Future completion occur in poll.
    """

    def __init__(self, state):
        self._root_state = state
        state.viewer_operations = self
        self._target = None
        self._token = state.session_token
        self.session = uuid.uuid4().hex
        self.executor = CancellableExecutor("uz-viewer-control-io")
        self.jobs = []
        self.live = None

    def bind_live(self, workspace):
        """Expose the application's live workspace without importing GUI modules."""
        self.live = workspace

    def _live(self):
        if self.live is None:
            raise ViewerError("live_unavailable", "Live support is not enabled")
        return self.live

    def _run_scope(self):
        return 0 if self.live is not None and self.state is self.live.state else 1

    def _sync(self):
        if self._token is not self._root_state.session_token:
            self._token = self._root_state.session_token
            self.session = uuid.uuid4().hex

    @property
    def state(self):
        return self._target if self._target is not None else self._root_state

    def _reply(self, result=None):
        self._sync()
        return {"session": self.session, "result": result}

    def _run_handle(self, run):
        return {"session": self.session, "id": run.id, "view": self._run_scope()}

    def _resolve_run(self, handle):
        if (
            not isinstance(handle, dict)
            or handle.get("session") != self.session
            or type(handle.get("view", 1)) is not int
            or handle.get("view", 1) != self._run_scope()
        ):
            raise ViewerError(
                "stale_handle", "Recording belongs to another session or registry"
            )
        key = handle.get("id")
        if type(key) is not int or self.state.registry.get(key) is None:
            raise ViewerError("stale_handle", "Recording is no longer loaded")
        return key

    def dispatch(self, operation, arguments, session):
        self._sync()
        if session is not None and session != self.session:
            raise ViewerError(
                "session_replaced", "Session changed; create a new client to attach"
            )
        handlers = {
            "status": self.status,
            "list_runs": self.list_runs,
            "load": self.load,
            "list_nodes": self.list_nodes,
            "list_plots": self.list_plots,
            "node_output": self.node_output,
            "create_view": self.create_view,
            "list_views": self.list_views,
            "close_view": self.close_view,
            "set_grid": self.set_grid,
            "link_x": self.link_x,
            "add_signal": self.add_signal,
            "clear_session": self.clear_session,
            "save_session": self.save_session,
            "load_session": self.load_session,
            "convert": self.convert,
            "get_settings": self.get_settings,
            "set_setting": self.set_setting,
            "live_view": self.live_view,
            "get_view": self.get_view,
            "get_session_settings": self.get_session_settings,
            "get_analysis": self.get_analysis,
            "set_grid_ratios": self.set_grid_ratios,
            "live_status": self.live_status,
            "live_attach": self.live_attach,
            "live_detach": self.live_detach,
            "live_follow": self.live_follow,
            "live_time_depth": self.live_time_depth,
            "live_freeze": self.live_freeze,
            "save_live_view": self.save_live_view,
            "load_live_view": self.load_live_view,
        }
        arguments = dict(arguments)
        view = arguments.pop("view", None)
        try:
            if view is not None:
                command = self._root_state.commands.get(operation)
                if operation not in (
                    "list_plots",
                    "set_grid",
                    "link_x",
                    "set_max_points",
                    "list_runs",
                    "get_view",
                    "set_grid_ratios",
                ) and not (command and any(p.kind == "plot" for p in command.params)):
                    raise ValueError("This operation does not target a plot view")
                self._target = self._resolve_view(view)
            result = (
                handlers[operation](**arguments)
                if operation in handlers
                else self._registered(operation, arguments)
            )
            if isinstance(result, Future):
                result.view_id = view["id"] if view is not None else 1
                return result
            return self._reply(result)
        finally:
            self._target = None

    def _resolve_view(self, handle):
        if not isinstance(handle, dict) or handle.get("session") != self.session:
            raise ViewerError("stale_handle", "View belongs to another session")
        key = handle.get("id")
        if type(key) is not int:
            raise ValueError("View id must be an integer")
        if key == 1:
            return self._root_state
        if key == 0:
            return self._live().state
        view = self._root_state.plot_views.get(key)
        if view is None:
            raise ViewerError("stale_handle", "View is no longer open")
        view.sync(self._root_state)
        return view

    def create_view(self):
        view = self._root_state.create_plot_view()
        return {"session": self.session, "id": view.plot_window_id}

    def list_views(self):
        return [
            {
                "handle": {"session": self.session, "id": key},
                "kind": "live" if key == 0 else "offline",
                **self._view_settings(state),
            }
            for key, state in [
                (1, self._root_state),
                *self._root_state.plot_views.items(),
                *([(0, self.live.state)] if self.live is not None else []),
            ]
        ]

    def close_view(self, handle):
        view = self._resolve_view(handle)
        if handle["id"] in (0, 1):
            raise ValueError("The main and live plot views cannot be closed")
        del self._root_state.plot_views[handle["id"]]
        view.shutdown()

    def _registered(self, operation, arguments):
        from .client_methods import ViewerMethods

        method = getattr(ViewerMethods, operation, None)
        if method is None or operation.startswith("_"):
            raise ViewerError(
                "unknown_operation", f"Unknown viewer operation: {operation}"
            )
        command = self.state.commands.get(operation)
        if command is None:
            raise ViewerError(
                "unknown_operation", f"Unknown viewer operation: {operation}"
            )
        values = []
        for param, value in zip(command.params, command.bind(arguments), strict=True):
            if value is not None and param.kind in ("run", "node"):
                if param.kind == "run":
                    values.append(self._resolve_run(value))
                    continue
                if not isinstance(value, dict) or value.get("session") != self.session:
                    raise ViewerError(
                        "stale_handle", f"{param.kind} belongs to another session"
                    )
                value = value.get("id")
                if type(value) is not int:
                    raise ValueError("Handle id must be an integer")
            values.append(value)
        result = self.state.commands.execute(self.state, operation, values)
        if (
            operation in ("export_data", "fft_export", "hist_export")
            and self.state.services.exports
        ):
            source = self.state.services.exports[-1][0]
            target = Future()
            target.add_done_callback(lambda _: source.operation_cancel.set())
            self.jobs.append(
                (source, target, self.session, lambda _: arguments["path"])
            )
            return target
        if operation in ("node_add", "node_source"):
            return {"session": self.session, "id": result}
        return result

    def _preferences(self):
        if not hasattr(self._root_state, "preferences"):
            from .preferences import Preferences

            self._root_state.preferences = Preferences(self._root_state)
        return self._root_state.preferences

    def get_settings(self):
        return dict(self._preferences().values)

    def set_setting(self, name, value):
        from .preferences import DEFAULTS

        if (
            name in DEFAULTS
            and not isinstance(DEFAULTS[name], str)
            and isinstance(value, str)
        ):
            import json

            value = json.loads(value)
        self._preferences().update({name: value})
        return self.get_settings()

    def status(self):
        return {
            "grid": [self.state.rows, self.state.cols],
            "runs": len(self.state.registry.runs),
            "pending": len(self.jobs),
        }

    @staticmethod
    def _view_settings(state):
        return {
            "grid": [state.rows, state.cols],
            "row_ratios": list(state.row_ratios),
            "col_ratios": list(state.col_ratios),
            "link_x": state.link_x,
            "max_points": state.max_points,
            "shared_x": state.shared_x,
        }

    def get_view(self):
        return self._view_settings(self.state)

    def get_session_settings(self):
        state = self.state
        return {
            "backend": state.backend,
            "loading_mode": state.loading_mode,
            "disk_cache": state.disk_cache,
            "cache_budget": state.registry.cache.limit // 1024**2,
            "max_points": state.max_points,
        }

    def get_analysis(self, kind):
        if kind not in ("fft", "histogram"):
            raise ValueError("Analysis kind must be fft or histogram")
        cfg = getattr(self.state, kind)
        result = {
            name: getattr(cfg, name)
            for name in (
                "follow_plot",
                "x_min",
                "x_max",
                *(
                    ("remove_dc", "window", "log_x", "log_y")
                    if kind == "fft"
                    else ("bins",)
                ),
            )
        }
        result["x_lim"] = cfg.pending_x_lim or cfg.x_lim
        result["sources"] = [
            {"run": self._run_handle(self.state.registry.get(key)), "signal": name}
            for key, name in cfg.sources
        ]
        return result

    def live_view(self):
        self._live()
        return {"session": self.session, "id": 0}

    def live_status(self):
        return self._live().presentation_status()

    def _live_request(self, operation, **kwargs):
        workspace = self._live()
        source = workspace.request_attachment(operation, **kwargs)
        target = Future()
        target.add_done_callback(lambda _: source.cancel())

        def commit(_):
            workspace.pump()
            return workspace.presentation_status()

        self.jobs.append((source, target, self.session, commit))
        return target

    def live_attach(self, endpoint):
        return self._live_request("attach", endpoint=endpoint)

    def live_detach(self):
        return self._live_request("detach")

    def live_follow(self, enabled):
        self._live().set_follow(enabled)
        return self.live_status()

    def live_time_depth(self, seconds):
        self._live().set_time_depth(seconds)
        return self.live_status()

    def live_freeze(self):
        run = self._live().freeze(self._root_state)
        if run is None:
            raise ViewerError("no_live_data", "No live data is available")
        return self._run_handle(run)

    def save_live_view(self):
        from .live_settings import save_view_preferences

        return str(save_view_preferences(self._live()) / "live_view.json")

    def load_live_view(self):
        self._live().load_live_settings(strict=True)
        return self.live_status()

    def list_runs(self):
        return [
            {
                "handle": self._run_handle(run),
                "label": run.label,
                "path": run.path,
                "signals": list(run.signals),
                "axis_column": run.axis_column,
                "axis_domain": run.axis_domain,
                "active": run.active,
                "time_origin": run.time_origin,
            }
            for run in self.state.registry.runs
        ]

    def list_nodes(self):
        return [
            {
                "handle": {"session": self.session, "id": node.id},
                "name": node.name,
                "kind": node.kind,
                "params": dict(node.params),
                "inputs": list(node.inputs),
                "output": (
                    self._run_handle(run)
                    if (run := self.state.registry.get(node.out_run_id)) is not None
                    else None
                ),
            }
            for node in self.state.nodes.ordered()
        ]

    def list_plots(self):
        from .session import plot_cells_to_list

        def reference(ref):
            return (
                {
                    "run": self._run_handle(self.state.registry.get(ref[0])),
                    "signal": ref[1],
                }
                if ref
                else None
            )

        return plot_cells_to_list(self.state, reference)

    def node_output(self, node):
        if not isinstance(node, dict) or node.get("session") != self.session:
            raise ViewerError("stale_handle", "Node belongs to another session")
        found = self.state.nodes.get(node.get("id"))
        run = self.state.registry.get(found.out_run_id) if found is not None else None
        if run is None:
            raise ViewerError("no_output", "Node has no evaluated output")
        return self._run_handle(run)

    def load(self, path, start=None, *, axis_column=None, axis_domain=None):
        from .loader import open_file

        state = self.state
        mode, cache, directory = (
            state.loading_mode,
            state.registry.cache,
            state.cache_dir,
        )
        backend, disk_cache = state.backend, state.disk_cache
        if start is not None:
            from .validation import finite_float

            start = finite_float(start)

        def prepare(cancel):
            return open_file(
                path,
                mode,
                cache,
                directory,
                backend=backend,
                disk_cache=disk_cache,
                cancel=cancel,
                axis_column=axis_column,
                axis_domain=axis_domain,
            )

        def commit(parsed):
            if start is not None and parsed.axis_domain != "time":
                raise ValueError("Only time-domain recordings can be normalized")
            run = parsed.register(state.registry)
            if start is not None:
                run.set_time_origin(start)
            state._report_loaded(run)
            return self._run_handle(run)

        return self._submit(prepare, commit)

    def set_grid(self, rows, cols):
        self.state.commands.invoke(self.state, "set_grid", rows=rows, cols=cols)

    def link_x(self, enabled):
        self.state.commands.invoke(self.state, "link_x", on=enabled)

    def set_grid_ratios(self, rows, cols):
        self.state.commands.invoke(self.state, "set_grid_ratios", rows=rows, cols=cols)

    def add_signal(self, plot, run, signal):
        key = self._resolve_run(run)
        self.state.commands.invoke(
            self.state, "add_signal", plot=plot, run=key, signal=signal
        )

    def clear_session(self):
        from .session import clear_session

        clear_session(self.state)

    def save_session(self, path):
        from .session import save_snapshot, to_dict

        snapshot = to_dict(self.state)

        def prepare(cancel):
            save_snapshot(snapshot, path, cancel=cancel)
            return path

        return self._submit(prepare, lambda result: result)

    def convert(self, src, dst=None, *, axis_column=None, axis_domain=None):
        from .loader import convert_csv_to_parquet

        backend = self.state.backend

        def prepare(cancel):
            return str(
                convert_csv_to_parquet(
                    src,
                    dst,
                    backend=backend,
                    cancel=cancel,
                    axis_column=axis_column,
                    axis_domain=axis_domain,
                )
            )

        def commit(path):
            self.state.console.info(f"converted {src} -> {path}")
            return path

        return self._submit(prepare, commit)

    def evaluate_nodes(self, node_id=None):
        from .node_jobs import capture, fingerprint, publish
        from .nodes import _upstream, evaluate

        state = self.state
        before = fingerprint(state)
        snapshot = capture(state)
        selected = set(snapshot.nodes.nodes)
        if node_id is not None:
            selected = set()
            _upstream(snapshot.nodes, node_id, selected)

        def prepare(cancel):
            evaluate(snapshot, node_id, cancel=cancel)
            return snapshot

        def commit(result):
            if fingerprint(state) != before:
                raise ViewerError(
                    "inputs_changed",
                    "Node inputs changed during evaluation; evaluate again",
                )
            count = publish(state, result)
            errors = [
                node.error
                for node in result.nodes.nodes.values()
                if node.id in selected and node.error
            ]
            if errors:
                raise ViewerError("evaluation_failed", "; ".join(errors))
            return f"Evaluated {count} node(s)"

        return self._submit(prepare, commit)

    def compute_analysis(self, kind):
        from . import analysis_service as analysis

        state = self.state
        cfg = analysis.config(state, kind)
        key = analysis.fingerprint(state, kind)
        request = analysis.request(state, kind)
        cfg.compute_requested = False
        state.services.analysis_jobs.forget(kind)
        state.services.completed_analysis.pop(kind, None)
        previous = state.services.analysis_operations.get(kind)
        if previous is not None:
            previous.cancel()

        def commit(result):
            if analysis.fingerprint(state, kind) != key:
                raise ViewerError(
                    "inputs_changed",
                    "Analysis inputs changed during computation; compute again",
                )
            state.services.completed_analysis[kind] = (key, result)
            if len(result.series) != len(request.sources):
                raise ViewerError("analysis_failed", result.info)
            return result.info

        future = self._submit(request.compute, commit)
        state.services.analysis_operations[kind] = future
        return future

    def load_session(self, path):
        from .session import _apply_dict, read_snapshot
        from .state import AppState

        directory = self.state.cache_dir

        def prepare(cancel):
            replacement = AppState()
            replacement.cache_dir = directory
            try:
                _apply_dict(replacement, read_snapshot(path), cancel=cancel)
                from .sources import check

                check(cancel)
            except BaseException:
                replacement.shutdown()
                raise
            return replacement

        def commit(replacement):
            self.state.replace_session(replacement)

        return self._submit(prepare, commit)

    def _submit(self, prepare, commit):

        target = Future()
        canceled = threading.Event()
        target.add_done_callback(lambda _: canceled.set())

        def work(cancel):
            token = Cancellation(cancel, canceled)
            return cancellable_result(lambda: prepare(token), token, self._dispose)

        source = self.executor.submit(work, dispose=self._dispose)
        self.jobs.append((source, target, self.session, commit))
        return target

    @staticmethod
    def _dispose(result):
        if hasattr(result, "shutdown"):
            result.shutdown()

    def poll(self):
        self._sync()
        for source, target, session, commit in list(self.jobs):
            if (
                getattr(target, "view_id", 1) not in (0, 1)
                and target.view_id not in self._root_state.plot_views
            ):
                if not target.done() and target.set_running_or_notify_cancel():
                    target.set_exception(
                        ViewerError("stale_handle", "View closed during operation")
                    )
            if session != self.session:
                if not target.done() and target.set_running_or_notify_cancel():
                    target.set_exception(
                        ViewerError(
                            "session_replaced", "Session changed during operation"
                        )
                    )
                source.cancel()
            if not source.done():
                continue
            self.jobs.remove((source, target, session, commit))
            if target.done():
                self._discard(source)
                continue
            # Atomically reserve publication. Disconnects may cancel preparation,
            # but cannot cancel a future after its commit has started.
            if not target.set_running_or_notify_cancel():
                self._discard(source)
                continue
            try:
                result = commit(source.result())
                target.set_result(self._reply(result))
            except Exception as exc:
                target.set_exception(exc)

    @staticmethod
    def _discard(source):
        if not source.cancelled() and source.exception() is None:
            result = source.result()
            if hasattr(result, "shutdown"):
                result.shutdown()

    def close(self):
        for source, target, _, _ in self.jobs:
            source.cancel()
            source.add_done_callback(self._discard)
            if not target.done() and target.set_running_or_notify_cancel():
                target.set_exception(ViewerError("closed", "Viewer is closing"))
        self.jobs.clear()
        self.executor.shutdown()
