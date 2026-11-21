"""Synchronous control of an existing viewer, without GUI or numerical imports.

Calls on a client are serialized. Transport failures are never retried: a
mutation may already have committed before its response was lost.
"""

import os
import socket
import threading
from dataclasses import dataclass
from pathlib import Path

from . import control_protocol as wire
from .client_methods import ViewerMethods


class ViewerError(RuntimeError):
    def __init__(self, code, message):
        super().__init__(message)
        self.code = code


@dataclass(frozen=True)
class RunHandle:
    session: str
    id: int


@dataclass(frozen=True)
class NodeHandle:
    session: str
    id: int


@dataclass(frozen=True)
class ViewHandle:
    session: str
    id: int


class Client(ViewerMethods):
    def __init__(self, endpoint=None, *, timeout=120, token=None):
        self.endpoint = endpoint or os.environ.get(
            "UZ_DATAVIEWER_ENDPOINT", wire.DEFAULT_ENDPOINT
        )
        self._address = wire.address(self.endpoint)
        self.timeout = timeout
        self._socket = self._stream = None
        self._lock = threading.RLock()
        self._sequence = 0
        self.session = None
        self._token = token

    def __enter__(self):
        return self

    def __exit__(self, *_):
        self.close()

    def close(self):
        with self._lock:
            if self._stream is not None:
                self._stream.close()
            if self._socket is not None:
                self._socket.close()
            self._socket = self._stream = None

    def _call(self, operation, **arguments):
        with self._lock:
            from dataclasses import asdict

            arguments = {
                key: asdict(value)
                if isinstance(value, (RunHandle, NodeHandle, ViewHandle))
                else value
                for key, value in arguments.items()
            }
            self._sequence += 1
            if self._token is None:
                from .control_credentials import discover

                self._token = discover(self.endpoint)
            request = wire.encode(
                {
                    "version": wire.VERSION,
                    "id": self._sequence,
                    "operation": operation,
                    "arguments": arguments,
                    "session": self.session,
                    "token": self._token,
                }
            )
            try:
                if self._socket is None:
                    self._socket = socket.create_connection(self._address, self.timeout)
                    self._stream = self._socket.makefile("rb")
                self._socket.sendall(request)
                reply = wire.read(self._stream)
                if reply.get("id") != self._sequence:
                    raise ValueError("Mismatched viewer response")
            except (OSError, EOFError, ValueError):
                self.close()
                raise
            if "error" in reply:
                error = reply["error"]
                raise ViewerError(error["code"], error["message"])
            self.session = reply["session"]
            return reply.get("result")

    def status(self):
        return self._call("status")

    def _invoke(self, operation, arguments):
        for key, value in list(arguments.items()):
            if isinstance(value, (RunHandle, NodeHandle)):
                arguments[key] = {"session": value.session, "id": value.id}
            elif value is not None and (
                key == "path"
                or operation == "convert"
                and key in ("src", "dst")
                or operation == "load_plugins"
                and key == "dir"
            ):
                arguments[key] = str(Path(value).expanduser().resolve())
        result = self._call(operation, **arguments)
        if operation in ("node_add", "node_source"):
            return NodeHandle(result["session"], result["id"])
        return result

    def list_runs(self):
        result = self._call("list_runs")
        for run in result:
            run["handle"] = RunHandle(**run["handle"])
        return result

    def list_nodes(self):
        result = self._call("list_nodes")
        for node in result:
            node["handle"] = NodeHandle(**node["handle"])
            if node["output"] is not None:
                node["output"] = RunHandle(**node["output"])
        return result

    def list_plots(self, *, view: ViewHandle | None = None):
        result = self._call("list_plots", view=view)
        for plot in result:
            references = plot["signals"] + plot["y2"]
            if plot["xy_source"] is not None:
                references.append(plot["xy_source"])
            for ref in references:
                ref["run"] = RunHandle(**ref["run"])
        return result

    def create_view(self):
        result = self._call("create_view")
        return ViewHandle(result["session"], result["id"])

    def list_views(self):
        result = self._call("list_views")
        for view in result:
            view["handle"] = ViewHandle(**view["handle"])
        return result

    def close_view(self, handle: ViewHandle):
        return self._call("close_view", handle=handle)

    def node_output(self, node: NodeHandle):
        if not isinstance(node, NodeHandle):
            raise TypeError("node must be a NodeHandle")
        result = self._call(
            "node_output", node={"session": node.session, "id": node.id}
        )
        return RunHandle(result["session"], result["id"])

    def clear_session(self):
        return self._call("clear_session")

    def load(
        self,
        path: str,
        start: float | None = None,
        *,
        axis_column: str | None = None,
        axis_domain: str | None = None,
    ):
        result = self._call(
            "load",
            path=str(Path(path).expanduser().resolve()),
            start=start,
            axis_column=axis_column,
            axis_domain=axis_domain,
        )
        return RunHandle(result["session"], result["id"])

    def set_grid(self, rows: int, cols: int, *, view: ViewHandle | None = None):
        return self._call("set_grid", rows=rows, cols=cols, view=view)

    def link_x(self, enabled: bool, *, view: ViewHandle | None = None):
        return self._call("link_x", enabled=enabled, view=view)

    def add_signal(
        self, plot: int, run: RunHandle, signal: str, *, view: ViewHandle | None = None
    ):
        if not isinstance(run, RunHandle):
            raise TypeError("run must be a RunHandle returned by load")
        return self._call(
            "add_signal",
            plot=plot,
            run={"session": run.session, "id": run.id},
            signal=signal,
            view=view,
        )

    def save_session(self, path: str):
        return self._call("save_session", path=str(Path(path).expanduser().resolve()))

    def load_session(self, path: str):
        return self._call("load_session", path=str(Path(path).expanduser().resolve()))

    def get_settings(self):
        """Return saved application defaults, independent of the current session."""
        return self._call("get_settings")

    def set_setting(self, name: str, value: str):
        """Set an application default; booleans and numbers also accept JSON text."""
        return self._call("set_setting", name=name, value=value)
