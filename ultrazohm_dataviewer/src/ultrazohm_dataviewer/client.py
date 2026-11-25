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
    """A viewer request failed; ``code`` identifies the failure category."""

    def __init__(self, code, message):
        super().__init__(message)
        self.code = code


@dataclass(frozen=True)
class RunHandle:
    """Session-scoped recording identity; ``view=0`` identifies live data.

    Offline windows share the recording registry identified by ``view=1``.
    Obtain handles from :meth:`Client.load` or :meth:`Client.list_runs`.
    """

    session: str
    id: int
    view: int = 1


@dataclass(frozen=True)
class NodeHandle:
    """Session-scoped node identity returned by node creation or inspection."""

    session: str
    id: int


@dataclass(frozen=True)
class ViewHandle:
    """Session-scoped plot view: live is 0, main is 1, additional views are 2+."""

    session: str
    id: int


class Client(ViewerMethods):
    """Control an open DataViewer from Python without importing GUI libraries.

    Args:
        endpoint: Numeric loopback host:port; defaults to
            ``UZ_DATAVIEWER_ENDPOINT`` or ``127.0.0.1:19741``.
        timeout: Socket timeout in seconds (default 120).
        token: Explicit authentication credential, or automatic local discovery.

    Calls wait for completion and raise :class:`ViewerError` on application
    failure, or a transport exception on connection failure. Calls are never
    automatically retried. Plot numbers start at 1. Omit ``view`` to target the
    main offline grid; pass :meth:`live_view` or :meth:`create_view` handles to
    target another grid. Session replacement invalidates existing handles.
    Use as a context manager to close the connection automatically.
    """

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
        """Close this client's connection; leave the viewer running."""
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
        """Return the main grid, recording count and pending operation count."""
        return self._call("status")

    def _invoke(self, operation, arguments):
        for key, value in list(arguments.items()):
            if isinstance(value, (RunHandle, NodeHandle)):
                from dataclasses import asdict

                arguments[key] = asdict(value)
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

    def list_runs(self, *, view: ViewHandle | None = None):
        """Return recording handles, signals and metadata for a view's registry."""
        result = self._call("list_runs", view=view)
        for run in result:
            run["handle"] = RunHandle(**run["handle"])
        return result

    def list_nodes(self):
        """Return nodes with handles, parameters, connections and output handles."""
        result = self._call("list_nodes")
        for node in result:
            node["handle"] = NodeHandle(**node["handle"])
            if node["output"] is not None:
                node["output"] = RunHandle(**node["output"])
        return result

    def list_plots(self, *, view: ViewHandle | None = None):
        """Return subplot assignments and current limits/tools for the selected view."""
        result = self._call("list_plots", view=view)
        for plot in result:
            references = plot["signals"] + plot["y2"]
            if plot["xy_source"] is not None:
                references.append(plot["xy_source"])
            for ref in references:
                ref["run"] = RunHandle(**ref["run"])
        return result

    def create_view(self):
        """Create an offline grid sharing loaded recordings; return its ViewHandle."""
        result = self._call("create_view")
        return ViewHandle(result["session"], result["id"])

    def list_views(self):
        """Return view handles, kinds and current layout settings, including live."""
        result = self._call("list_views")
        for view in result:
            view["handle"] = ViewHandle(**view["handle"])
        return result

    def close_view(self, handle: ViewHandle):
        """Close an additional offline view; main and live views cannot be closed."""
        return self._call("close_view", handle=handle)

    def node_output(self, node: NodeHandle):
        """Return an evaluated node's RunHandle; raise ViewerError if unavailable."""
        if not isinstance(node, NodeHandle):
            raise TypeError("node must be a NodeHandle")
        result = self._call(
            "node_output", node={"session": node.session, "id": node.id}
        )
        return RunHandle(result["session"], result["id"])

    def clear_session(self):
        """Clear offline recordings, plots and analysis, invalidating old handles."""
        return self._call("clear_session")

    def load(
        self,
        path: str,
        start: float | None = None,
        *,
        axis_column: str | None = None,
        axis_domain: str | None = None,
    ):
        """Load CSV/Parquet and return a RunHandle after registration completes.

        ``start`` optionally normalizes a time recording's origin. Use
        ``axis_column`` and ``axis_domain`` to identify nonstandard input axes.
        Paths resolve relative to the calling Python process.
        """
        result = self._call(
            "load",
            path=str(Path(path).expanduser().resolve()),
            start=start,
            axis_column=axis_column,
            axis_domain=axis_domain,
        )
        return RunHandle(result["session"], result["id"])

    def set_grid(self, rows: int, cols: int, *, view: ViewHandle | None = None):
        """Set grid dimensions (1..16 each), preserving surviving plot assignments."""
        return self._call("set_grid", rows=rows, cols=cols, view=view)

    def link_x(self, enabled: bool, *, view: ViewHandle | None = None):
        """Enable or disable linked X axes in the selected plot view."""
        return self._call("link_x", enabled=enabled, view=view)

    def add_signal(
        self, plot: int, run: RunHandle, signal: str, *, view: ViewHandle | None = None
    ):
        """Add a named signal to a 1-based plot using a handle from its registry."""
        if not isinstance(run, RunHandle):
            raise TypeError("run must be a RunHandle returned by load")
        return self._call(
            "add_signal",
            plot=plot,
            run=run,
            signal=signal,
            view=view,
        )

    def save_session(self, path: str):
        """Atomically save the offline workspace to JSON; return the saved path."""
        return self._call("save_session", path=str(Path(path).expanduser().resolve()))

    def load_session(self, path: str):
        """Restore an offline workspace transactionally, invalidating old handles."""
        return self._call("load_session", path=str(Path(path).expanduser().resolve()))

    def get_settings(self):
        """Return saved application defaults, independent of the current session."""
        return self._call("get_settings")

    def set_setting(self, name: str, value: str):
        """Set an application default; booleans and numbers also accept JSON text."""
        return self._call("set_setting", name=name, value=value)

    def live_view(self):
        """Return the live ViewHandle; raise ViewerError if live support is disabled."""
        return ViewHandle(**self._call("live_view"))

    def get_view(self, *, view: ViewHandle | None = None):
        """Return current grid, proportions, linked axes and display point budget."""
        return self._call("get_view", view=view)

    def get_session_settings(self):
        """Return current IO/cache settings, which may differ from saved defaults."""
        return self._call("get_session_settings")

    def get_analysis(self, kind: str):
        """Return current ``fft`` or ``histogram`` settings and source RunHandles."""
        result = self._call("get_analysis", kind=kind)
        for ref in result["sources"]:
            ref["run"] = RunHandle(**ref["run"])
        return result

    def set_grid_ratios(
        self, rows: list[float], cols: list[float], *, view: ViewHandle | None = None
    ):
        """Set positive relative row/column sizes; lengths must match the grid.

        Equal weights give equal sizes. Weights are normalized on the viewer.
        """
        return self._call("set_grid_ratios", rows=rows, cols=cols, view=view)

    def live_status(self):
        """Return attachment, follow/inspect, time depth and live error information."""
        return self._call("live_status")

    def live_attach(self, endpoint: str = "127.0.0.1:19740"):
        """Attach the live view to an existing acquisition service; wait for completion.

        This does not start a service or connect the device. Device operations
        belong to ``ultrazohm_cli.Client``.
        """
        return self._call("live_attach", endpoint=endpoint)

    def live_detach(self):
        """Detach the viewer, leaving acquisition and logging running."""
        return self._call("live_detach")

    def live_follow(self, enabled: bool):
        """Follow incoming data, or freeze the displayed snapshot for inspection."""
        return self._call("live_follow", enabled=enabled)

    def live_time_depth(self, seconds: float):
        """Set the displayed duration, from 0.001 seconds to the buffer capacity."""
        return self._call("live_time_depth", seconds=seconds)

    def live_freeze(self):
        """Copy live plot 1's visible interval to offline analysis; return a RunHandle.

        The copy remains in memory. Export it before saving a reloadable session.
        Raises ViewerError if no live data is available.
        """
        return RunHandle(**self._call("live_freeze"))

    def save_live_view(self):
        """Save live presentation preferences to the current workspace directory."""
        return self._call("save_live_view")

    def load_live_view(self):
        """Restore saved live presentation preferences; apply signals when available."""
        return self._call("load_live_view")
