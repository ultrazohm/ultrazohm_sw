"""Native live acquisition adapter. Device IO stays in the independent CLI service.

The worker publishes immutable, bounded snapshots. The GUI never performs network
IO. Closing the viewer finalizes its owned service and sends Stop to an attached
external device. The displayed history is bounded by the service RAM buffer.
"""

from __future__ import annotations

import ipaddress
import json
import os
import subprocess
import sys
import threading
import time
import uuid
from contextlib import nullcontext
from dataclasses import dataclass, field
from pathlib import Path
from queue import Empty, Full, Queue

import numpy as np

from .sources import MemorySource, PlotData, check, envelope

# Closing the window waits this long for a viewer-owned service to finalize.
# The service runs detached, so longer finalizations complete in the background
# without freezing the closing window.
CLOSE_FINALIZE_TIMEOUT = 10


def fuzzy_names(names, query):
    """Rank substring matches first, then ordered-subsequence matches."""
    query = query.casefold().strip()
    matches = []
    for name in names:
        text = name.casefold()
        position, gaps = -1, 0
        for char in query:
            found = text.find(char, position + 1)
            if found < 0:
                break
            gaps += found - position - 1
            position = found
        else:
            matches.append(((query not in text, gaps, len(name), text), name))
    return [name for _, name in sorted(matches)]


# Rows per finest incremental display bucket kept by LiveRing for every channel;
# each coarser level merges LIVE_FACTOR buckets of the level below.
LIVE_BUCKET = 128
LIVE_FACTOR = 8


def bucket_size(level):
    return LIVE_BUCKET * LIVE_FACTOR**level


class RingSnapshot(dict):
    """Column views of retained rows plus per-bucket extrema for display.

    ``summary`` maps a channel to a list of levels; each level holds arrays of
    buffer positions (min, max, first non-finite; -1 when absent) for buckets of
    ``bucket_size(level)`` rows. Buckets are aligned to buffer positions;
    ``offset`` converts them to row indices and only buckets ending at or before
    ``valid_end`` are complete.
    """

    summary: dict
    offset: int = 0
    valid_end: int = 0


def bucket_extrema(y):
    """Positions of each bucket's first finite minimum, last finite maximum and
    first non-finite sample (-1 when a bucket has none)."""
    n = len(y)
    starts = np.arange(0, n, LIVE_BUCKET)
    lengths = np.diff(np.r_[starts, n])
    finite = np.isfinite(y)
    pos = np.arange(n)
    low = np.minimum.reduceat(np.where(finite, y, np.inf), starts)
    high = np.maximum.reduceat(np.where(finite, y, -np.inf), starts)
    mins = np.minimum.reduceat(
        np.where(finite & (y == np.repeat(low, lengths)), pos, n), starts
    )
    maxs = np.maximum.reduceat(
        np.where(finite & (y == np.repeat(high, lengths)), pos, -1), starts
    )
    gaps = np.minimum.reduceat(np.where(~finite, pos, n), starts)
    mins[mins == n] = -1
    gaps[gaps == n] = -1
    return mins, maxs, gaps


def merge_extrema(y, mins, maxs, gaps):
    """Combine LIVE_FACTOR child buckets into parents, keeping the first minimum,
    last maximum and first non-finite position of each parent."""
    groups = -(-len(mins) // LIVE_FACTOR)
    pad = groups * LIVE_FACTOR - len(mins)

    def grouped(values):
        return np.r_[values, np.full(pad, -1, np.int64)].reshape(groups, LIVE_FACTOR)

    mins, maxs, gaps = grouped(mins), grouped(maxs), grouped(gaps)
    low = np.where(mins >= 0, y[np.maximum(mins, 0)], np.inf)
    high = np.where(maxs >= 0, y[np.maximum(maxs, 0)], -np.inf)
    rows = np.arange(groups)
    # Children are ordered, so argmin picks the first minimum; reversed argmax the last maximum.
    parent_min = mins[rows, low.argmin(axis=1)]
    parent_max = maxs[rows, LIVE_FACTOR - 1 - high[:, ::-1].argmax(axis=1)]
    parent_min[~np.isfinite(low.min(axis=1))] = -1
    parent_max[~np.isfinite(high.max(axis=1))] = -1
    parent_gap = np.where(gaps >= 0, gaps, np.iinfo(np.int64).max).min(axis=1)
    parent_gap[parent_gap == np.iinfo(np.int64).max] = -1
    return parent_min, parent_max, parent_gap


class LiveRing:
    """Bounded columnar history with amortised O(page) appends.

    Columns live in buffers of twice the capacity. Appends write past every
    published snapshot; when a buffer is full, the retained tail moves into newly
    allocated buffers, so snapshots (including a frozen Inspect view) stay valid.
    Per-bucket extrema are maintained alongside, so wide follow-live windows are
    drawn from buckets instead of re-reducing every raw sample on each update.
    """

    def __init__(self, capacity):
        self.capacity = max(1, int(capacity))
        self.reset()

    def reset(self):
        self.columns, self.summary, self.end, self.length = None, None, 0, 0

    def append(self, page):
        names = list(page.columns)
        n = page.height
        if not n:
            return
        arrays = {name: page[name].to_numpy() for name in names}
        if self.columns is None or list(self.columns) != names:
            self.reset()
            self._allocate(arrays)
        if n >= self.capacity:
            self._allocate(arrays)
            for name, values in arrays.items():
                self.columns[name][: self.capacity] = values[-self.capacity :]
            self.end = self.length = self.capacity
            self._summarize(0)
            return
        first = self.end
        if self.end + n > len(next(iter(self.columns.values()))):
            keep = min(self.length, self.capacity - n)
            # Move from a position aligned to the coarsest bucket, so complete
            # buckets keep their extrema and only shift instead of a full rescan.
            # Tiny rings whose coarsest bucket exceeds the spare room rebuild instead.
            coarsest = bucket_size(len(next(iter(self.summary.values()), [()])) - 1)
            size = len(next(iter(self.columns.values())))
            start = (self.end - keep) // coarsest * coarsest
            aligned = self.end - start + n <= size
            if not aligned:
                start = self.end - keep
            old, old_summary = self.columns, self.summary
            self._allocate(arrays)
            for name, values in old.items():
                self.columns[name][: self.end - start] = values[start : self.end]
            if aligned:
                for name, levels in old_summary.items():
                    for level, (old_arrays, new_arrays) in enumerate(
                        zip(levels, self.summary[name], strict=False)
                    ):
                        shift = start // bucket_size(level)
                        count = -(-(self.end - start) // bucket_size(level))
                        for source, target in zip(old_arrays, new_arrays, strict=False):
                            values = source[shift : shift + count]
                            target[: len(values)] = np.where(
                                values >= 0, values - start, -1
                            )
            self.end = self.end - start
            first = self.end if aligned else 0
            self.length = keep
        for name, values in arrays.items():
            self.columns[name][self.end : self.end + n] = values
        self.end += n
        self.length = min(self.length + n, self.capacity)
        self._summarize(first)

    def _allocate(self, arrays):
        size = 2 * self.capacity
        self.columns = {
            name: np.empty(size, dtype=values.dtype) for name, values in arrays.items()
        }
        levels = 1
        while size // bucket_size(levels) >= LIVE_FACTOR:
            levels += 1
        self.summary = {
            name: [
                tuple(
                    np.full(size // bucket_size(level) + 1, -1, np.int64)
                    for _ in range(3)
                )
                for level in range(levels)
            ]
            for name in arrays
            if name not in ("time", "status")
        }

    def _summarize(self, first):
        """Summarize only buckets completed by this append.

        Readers use raw samples for unfinished buckets. Defer their reductions
        until complete, especially at coarse levels which can span many polls.
        Complete buckets below ``first`` never change, so published snapshots
        that reference them stay consistent.
        """
        bucket = first // LIVE_BUCKET
        lo = bucket * LIVE_BUCKET
        stop = self.end // LIVE_BUCKET * LIVE_BUCKET
        if lo == stop:
            return
        for name, levels in self.summary.items():
            y = self.columns[name]
            for target, values in zip(
                levels[0], bucket_extrema(y[lo:stop]), strict=False
            ):
                target[bucket : bucket + len(values)] = np.where(
                    values >= 0, values + lo, -1
                )
            for level in range(1, len(levels)):
                parent = first // bucket_size(level)
                parent_stop = self.end // bucket_size(level)
                if parent == parent_stop:
                    break
                start, child_stop = parent * LIVE_FACTOR, parent_stop * LIVE_FACTOR
                merged = merge_extrema(
                    y, *(values[start:child_stop] for values in levels[level - 1])
                )
                for target, values in zip(levels[level], merged, strict=False):
                    target[parent : parent + len(values)] = values

    def snapshot(self):
        """Views of the retained rows; later appends never modify them."""
        if self.columns is None or not self.length:
            return None
        start = self.end - self.length
        result = RingSnapshot(
            {name: values[start : self.end] for name, values in self.columns.items()}
        )
        result.summary, result.offset, result.valid_end = self.summary, start, self.end
        return result


def _column(frame, name):
    column = frame[name]
    return column.to_numpy() if hasattr(column, "to_numpy") else column


class LiveSource(MemorySource):
    """An immutable display snapshot; decimate only the visible window.

    Accepts a Polars frame or a mapping of NumPy columns (a :class:`LiveRing`
    snapshot). Ring snapshots also provide bucket extrema for wide windows.
    """

    def __init__(self, frame):
        names = frame.columns if hasattr(frame, "columns") else list(frame)
        t = _column(frame, "time")
        channels = {n: _column(frame, n) for n in names if n not in ("time", "status")}
        super().__init__(t, channels)
        self.units = dict.fromkeys(channels, "")
        self.timestamp_resolution = 0.0
        self._summary = getattr(frame, "summary", None)
        self._offset = getattr(frame, "offset", 0)
        self._valid_end = getattr(frame, "valid_end", 0)
        # MemorySource creates a unique identity, which invalidates display results
        # even when the user keeps the same (paused) X-axis range while data grows.

    def read_plot(
        self, channel, lo, hi, budget, cancel=None, *, padding=True, offset=0.0
    ):
        check(cancel)
        budget = max(2, int(budget))
        a, b = self.bounds(lo, hi, cancel, padding=padding, offset=offset)
        positions = self._candidates(channel, a, b, budget)
        if positions is not None:
            check(cancel)
            t, y = self.time[positions], self.channels[channel][positions]
            tx, values = envelope(t, y, positions, budget)
            return PlotData(tx, values, b - a)
        t, ys = self.read_rows([channel], a, b, cancel)
        if not len(t):
            return PlotData(t, ys[channel], 0)
        tx, y = envelope(t, ys[channel], np.arange(a, b), budget)
        return PlotData(tx, y, b - a)

    def _candidates(self, channel, a, b, budget):
        """Row indices of bucket extrema and raw edge rows, or None for raw reads.

        Buckets are used only when every output bucket spans at least one ring
        bucket, so each output min/max is still an original extreme sample.
        """
        if self._summary is None or channel not in self._summary:
            return None
        per_bucket = (b - a) / max(1, budget // 2)
        if per_bucket < LIVE_BUCKET:
            return None
        levels = self._summary[channel]
        level = 0
        while level + 1 < len(levels) and bucket_size(level + 1) <= per_bucket:
            level += 1
        valid_end = self._valid_end

        def collect(lo, hi, k):
            """Buffer positions covering [lo, hi): full level-k buckets, finer edges."""
            if lo >= hi:
                return []
            if k < 0:
                return [np.arange(lo, hi)]
            size = bucket_size(k)
            first = -(-lo // size)
            last = min(hi, valid_end) // size
            if last <= first:
                return collect(lo, hi, k - 1)
            parts = collect(lo, first * size, k - 1)
            inner = np.concatenate([values[first:last] for values in levels[k]])
            parts.append(inner[inner >= 0])
            parts.extend(collect(last * size, hi, k - 1))
            return parts

        # Window end rows keep lines reaching the plot edges, as with raw reads.
        edges = np.array([a, b - 1], np.int64) + self._offset
        positions = np.concatenate(
            [edges, *collect(a + self._offset, b + self._offset, level)]
        )
        positions.sort()
        # A constant bucket reports one sample as both minimum and maximum.
        positions = positions[np.r_[True, positions[1:] != positions[:-1]]]
        return positions - self._offset

    def prepare_summary(self, channel, cancel=None):
        check(cancel)


@dataclass(frozen=True)
class LiveUpdate:
    revision: int = 0
    status: dict = field(default_factory=dict)
    catalog: dict = field(default_factory=dict)
    assignments: tuple = ()
    source: LiveSource | None = None
    epoch: tuple | None = None
    error: str = ""
    notice: str = ""
    attached: bool = False
    received_at: float = 0.0
    activity: str = ""
    completed_commands: int = 0
    variable_sends: dict = field(default_factory=dict)


@dataclass
class OwnedService:
    """The launched process remains owned even when the viewer attaches elsewhere."""

    process: object = None
    endpoint: str | None = None
    shutdown_requested: bool = False
    log: Path | None = None
    repo: Path | None = None
    mapping: Path | None = None
    service_id: str | None = None

    @property
    def running(self):
        return self.process is not None and self.process.poll() is None

    def owns(self, endpoint):
        return self.endpoint == endpoint and self.running


def cursor_invalid(exc):
    """Whether a read failed because its cursor no longer addresses retained data."""
    return getattr(exc, "code", None) == "cursor_expired"


def action_block_reason(action, *, flashing=False, script_busy=False):
    """Shared interaction policy; connection and execution checks stay with their owners."""
    if flashing and action not in ("stop", "shutdown"):
        return "Flash UZ is running"
    if script_busy and action not in ("stop", "cli"):
        return "Manual controls are locked while the script runs"
    return ""


class LiveController:
    """Command worker and independent polling worker, latest snapshot publication.

    Commands (connect, shutdown, flash, device controls) run on one thread and
    data/status polling on another, each with its own service connection, so a
    long command never freezes live plots. The polling thread exclusively owns
    ``ring`` and ``cursor``; commands request a fresh history through ``_reset``.
    """

    def __init__(self, client_factory=None, hz=30):
        self.client_factory = client_factory
        self.interval = 1 / hz
        self.commands = Queue(maxsize=32)
        self.lock = threading.Lock()
        # Serialize commands with the independent script Stop, never with reads.
        self._command_lock = threading.Lock()
        self._command_generation = 0
        self.update = LiveUpdate()
        self.stop_event = threading.Event()
        self.thread = None
        self.poll_thread = None
        self.control_thread = None
        self.control_commands = Queue(maxsize=32)
        self._control_error = ""
        self.owned = OwnedService()
        self.client = None
        self.endpoint = None
        self._poll_client = None
        self._poll_endpoint = None
        # Commands bump this; the polling thread discards older work and history.
        self._reset_generation = 0
        self._poll_reset_seen = 0
        self.cursor = None
        # Sample position after the last displayed page; cursors stay opaque.
        self.cursor_stop = None
        self.ring = None
        self.attached = False
        self.revision = 0
        self._status_at = 0.0
        self._last_source = None
        self._epoch = None
        self._status = {}
        self._catalog = {}
        self._assignments = ()
        self._notice = ""
        self._error = ""
        self._poll_error = ""
        self._received_at = 0.0
        self._activity = ""
        self._completed_commands = 0
        self._variable_sends = {}
        self.flashing = False
        self._flash_shutdown = threading.Event()
        self.messages = Queue(maxsize=2000)

    def submit(self, operation, **kwargs):
        if self.stop_event.is_set():
            raise RuntimeError("Live controller is closed")
        if self.flashing and operation in ("stop", "shutdown"):
            self.cancel_pending_commands()
            try:
                self.control_commands.put_nowait(
                    (operation, kwargs.get("endpoint") or self.endpoint)
                )
            except Full as exc:
                raise RuntimeError("Control command queue is busy") from exc
            if self.control_thread is None:
                self.control_thread = threading.Thread(
                    target=self._control_work, name="uz-live-control", daemon=True
                )
                self.control_thread.start()
            return
        if self.flashing and operation not in ("stop", "shutdown"):
            raise RuntimeError("Flash UZ is already running")
        if operation in ("stop", "flash", "shutdown", "detach", "attach", "connect"):
            self.cancel_pending_commands()
        if operation == "flash":
            self._flash_shutdown.clear()
            self.flashing = True
        if self.thread is None:
            self.thread = threading.Thread(
                target=self._work, name="uz-live", daemon=True
            )
            self.thread.start()
            self.poll_thread = threading.Thread(
                target=self._poll_work, name="uz-live-poll", daemon=True
            )
            self.poll_thread.start()
        try:
            with self.lock:
                self.commands.put_nowait((self._command_generation, operation, kwargs))
        except Full as exc:
            if operation == "flash":
                self.flashing = False
            raise RuntimeError("Live command queue is busy") from exc

    def _control_work(self):
        """Lifecycle requests bypass flash monitoring without blocking the GUI."""
        while not self.stop_event.is_set():
            try:
                operation, endpoint = self.control_commands.get(timeout=self.interval)
            except Empty:
                continue
            with self._command_lock:
                if self.stop_event.is_set():
                    return
                try:
                    from ultrazohm_cli import Client

                    client = (self.client_factory or Client)(endpoint)
                    getattr(client, operation)()
                    if operation == "shutdown":
                        self._flash_shutdown.set()
                        if endpoint == self.owned.endpoint:
                            self.owned.shutdown_requested = True
                        self.attached = False
                        self._reset()
                        self._status, self._catalog, self._assignments = {}, {}, ()
                        self._poll_error = ""
                        self._error = ""
                        if self._await_shutdown(
                            "Stopping device and finalizing recordings…", external=False
                        ):
                            self._notice = "Service shut down; recordings finalized"
                        else:
                            self._notice = "Service shutdown accepted; finalization continues in the external service"
                    self._control_error = ""
                except Exception as exc:
                    self._control_error = f"{operation} failed: {exc}"
                    self._message("error", self._control_error)
                finally:
                    self._completed_commands += 1
                    self._publish()

    def cancel_pending_commands(self):
        """Invalidate even a command already dequeued but not yet executing."""
        with self.lock:
            self._command_generation += 1
            while True:
                try:
                    self.commands.get_nowait()
                except Empty:
                    break

    def send_stop(self, endpoint=None):
        """Finish an in-flight command before Stop, independently of data reads."""
        with self._command_lock:
            endpoint = endpoint or self.endpoint
            if self.client_factory is None:
                from ultrazohm_cli import Client

                client = Client(endpoint)
            else:
                client = self.client_factory(endpoint)
            client.stop()

    def commands_idle(self):
        """Check without blocking the GUI; canceled commands cannot execute later."""
        if not self._command_lock.acquire(blocking=False):
            return False
        self._command_lock.release()
        return True

    def latest(self):
        with self.lock:
            return self.update

    def _publish(self):
        if self.stop_event.is_set():
            return
        with self.lock:
            self.revision += 1
            self.update = LiveUpdate(
                self.revision,
                self._status,
                self._catalog,
                self._assignments,
                self._last_source,
                self._epoch,
                self._control_error or self._error or self._poll_error,
                self._notice,
                self.attached,
                self._received_at,
                self._activity,
                self._completed_commands,
                self._variable_sends.copy(),
            )

    def _message(self, level, text):
        try:
            self.messages.put_nowait((level, text))
        except Full:
            try:
                self.messages.get_nowait()
            except Empty:
                pass
            self.messages.put_nowait((level, text))

    def _progress(self, message):
        self._activity = message
        self._publish()

    def _reset(self):
        """Discard displayed history; the polling thread clears ring and cursor."""
        with self.lock:
            self._reset_generation += 1
            self._last_source = self._epoch = None
            self._received_at = 0.0

    def _make_client(self, endpoint):
        if endpoint != self.endpoint or self.client is None:
            self._reset()
            self._status, self._catalog, self._assignments = {}, {}, ()
            self._variable_sends = {}
            self.attached = False
            if self.client_factory is None:
                from ultrazohm_cli import Client

                self.client = Client(endpoint)
            else:
                self.client = self.client_factory(endpoint)
            self.endpoint = endpoint

    def _start_service(
        self,
        output,
        mapping,
        profile=None,
        data_options=None,
        ack=False,
        user_directory=None,
        repo=None,
    ):
        if repo and mapping:
            raise ValueError(
                "Choose either a firmware repository or an explicit channel mapping"
            )
        self._progress("Starting local acquisition service…")
        if self.owned.running:
            raise RuntimeError(
                "The launched service is still running; check its endpoint and service.log"
            )
        output = Path(output).expanduser().resolve()
        # One output directory per service lifetime, never reuse an existing run.
        output.parent.mkdir(parents=True, exist_ok=True)
        if output.exists():
            raise ValueError(
                "Choose a new session directory; existing recordings are never overwritten"
            )
        log_path = output.with_name(output.name + ".service.log")
        from .process_launcher import command

        args = command(
            "cli",
            "--endpoint",
            self.endpoint,
            "serve",
            "--output",
            str(output),
            "--format",
            "parquet",
        )
        if repo:
            args += ["--repo", str(Path(repo).expanduser().resolve())]
            if not profile:
                from .user_paths import data_directory

                directory = (
                    Path(user_directory) if user_directory else data_directory(repo)
                )
                saved = directory / "settings.json"
                if saved.is_file():
                    profile = saved
        elif mapping:
            args += ["--channel-mapping", str(Path(mapping).expanduser().resolve())]
            if not profile:
                from .settings import load_workspace_settings

                profile = load_workspace_settings(mapping, user_directory).path
        if profile:
            args += ["--profile", str(profile)]
        if ack:
            args += ["--ack", "on"]
        for name in (
            "buffer_samples",
            "segment_rows",
            "flush_interval_ms",
            "queue_seconds",
            "recording_backend",
        ):
            if (value := (data_options or {}).get(name)) is not None:
                args += ["--" + name.replace("_", "-"), str(value)]
        options = (
            {"stdin": subprocess.DEVNULL, "start_new_session": True}
            if os.name != "nt"
            else {
                "stdin": subprocess.DEVNULL,
                "creationflags": subprocess.DETACHED_PROCESS
                | subprocess.CREATE_NEW_PROCESS_GROUP,
            }
        )
        with log_path.open("ab") as log:
            self.owned.process = subprocess.Popen(
                args, stdout=log, stderr=log, **options
            )
            self.owned.endpoint = self.endpoint
            self.owned.repo = Path(repo).expanduser().resolve() if repo else None
            self.owned.mapping = (
                Path(mapping).expanduser().resolve() if mapping else None
            )
            self.owned.shutdown_requested = False
            self.owned.log = log_path
        deadline = time.monotonic() + 8
        while not self.stop_event.is_set() and time.monotonic() < deadline:
            if self.owned.process.poll() is not None:
                raise RuntimeError(f"Service failed; see {log_path}")
            try:
                self.owned.service_id = self.client.status()["service_id"]
                return
            except (OSError, RuntimeError):
                self.stop_event.wait(0.1)
        # A service that never answered must not block later Connect attempts.
        self._terminate_owned()
        raise RuntimeError(f"Service startup timed out; see {log_path}")

    def _terminate_owned(self):
        process = self.owned.process
        if process is None or process.poll() is not None:
            return
        process.terminate()
        try:
            process.wait(timeout=5)
        except subprocess.TimeoutExpired:
            process.kill()
            process.wait()

    def _wait_owned(self, description):
        """Wait for the owned service without blocking viewer shutdown."""
        while self.owned.process.poll() is None:
            if self.stop_event.is_set():
                return None  # close() takes over waiting for finalization
            self._progress(description)
            self.stop_event.wait(0.2)
        return self.owned.process.returncode

    def _command(self, operation, kwargs):
        if operation == "flash":
            self._flash(kwargs)
        elif operation in ("attach", "connect"):
            self._progress("Checking acquisition service…")
            self._make_client(kwargs["endpoint"])
            try:
                self.client.status()
            except (OSError, RuntimeError):
                if operation != "connect":
                    raise
                self._start_service(
                    kwargs["output"],
                    kwargs.get("mapping", ""),
                    kwargs.get("profile"),
                    kwargs.get("data_options"),
                    kwargs.get("ack", False),
                    user_directory=kwargs.get("user_directory"),
                    repo=kwargs.get("repo"),
                )
            else:
                if operation == "connect" and not (self.owned.owns(self.endpoint)):
                    raise RuntimeError(
                        "A service is already running at this endpoint. Use Existing service > Attach."
                    )
                if (
                    operation == "connect"
                    and kwargs.get("repo")
                    and Path(kwargs["repo"]).expanduser().resolve() != self.owned.repo
                ):
                    raise RuntimeError(
                        "The running service uses a different firmware repository. "
                        "Attach and shut it down before connecting with the selected repository."
                    )
                if (
                    operation == "connect"
                    and kwargs.get("mapping")
                    and Path(kwargs["mapping"]).expanduser().resolve()
                    != self.owned.mapping
                ):
                    raise RuntimeError(
                        "The running service uses a different channel mapping. "
                        "Attach and shut it down before connecting with the selected mapping."
                    )
            self._progress("Reading service configuration…")
            status = self.client.status()
            if operation == "connect":
                if status["state"]["connected"]:
                    requested = (
                        ipaddress.ip_address(kwargs["ip"]),
                        int(kwargs["port"]),
                    )
                    device = status["state"].get("device", "")
                    host, _, port = device.rpartition(":")
                    try:
                        actual = (ipaddress.ip_address(host.strip("[]")), int(port))
                    except ValueError:
                        actual = None
                    if actual != requested:
                        raise RuntimeError(
                            f"Service is already connected to {device or 'an unknown device'}; "
                            f"requested {kwargs['ip']}:{kwargs['port']}. "
                            "Use Attach service for that device or a separate service endpoint."
                        )
                else:
                    self._progress(
                        f"Connecting to UltraZohm at {kwargs['ip']}:{kwargs['port']}…"
                    )
                    self.client.connect(kwargs["ip"], kwargs["port"])
                    self._reset()
            self._catalog = (
                self.client.catalog()["profile"]
                if status.get("session_id", True)
                else {}
            )
            self.attached = True
            self._status = self.client.status()
            self._notice = f"Attached to acquisition service at {self.endpoint}"
            if mapping := kwargs.get("mapping"):
                try:
                    expected = json.loads(
                        Path(mapping).expanduser().read_text(encoding="utf-8")
                    )
                    fields = (
                        "api_version",
                        "channels",
                        "samples_per_packet",
                        "observables",
                        "slow_signals",
                        "variables",
                        "commands",
                        "platform_state",
                        "legacy_javascope_header",
                        "javascope",
                    )
                    if any(
                        expected.get(key) != self._catalog.get(key) for key in fields
                    ):
                        self._notice += (
                            f". The service uses a different channel mapping than {mapping}. "
                            "Restart the service to apply the selected mapping."
                        )
                except (OSError, ValueError) as exc:
                    self._notice += (
                        f". Could not compare the selected channel mapping: {exc}"
                    )
        elif operation == "detach":
            self.attached = False
            self._notice = "Detached; the service and logging continue"
        else:
            if not self.attached:
                raise RuntimeError("Attach to a service first")
            try:
                reply = getattr(self.client, operation)(**kwargs)
            except Exception as exc:
                from .flashing import connection_refused

                if operation != "shutdown" or not connection_refused(exc):
                    raise
                # A dead service cannot acknowledge shutdown. Release the local
                # attachment so the user can change repositories and reconnect.
                self.attached = False
                self._reset()
                self._status, self._catalog, self._assignments = {}, {}, ()
                self._poll_error = ""
                self._status_at = 0.0
                self._notice = "Detached: acquisition service unavailable; device Stop and recording finalization could not be confirmed. Check service.log."
                return
            if operation == "set_variable":
                self._variable_sends[kwargs["name"]] = (
                    time.monotonic(),
                    kwargs["value"],
                )
            self._notice = (
                f"{operation}: request sent (device commands have no acknowledgment)"
            )
            if operation == "shutdown":
                if self.endpoint == self.owned.endpoint:
                    self.owned.shutdown_requested = True
                self.attached = False
                self._reset()
                self._status, self._catalog, self._assignments = {}, {}, ()
                if self._await_shutdown(
                    "Stopping device and finalizing recordings…", external=False
                ):
                    self._notice = "Service shut down; recordings finalized"
                else:
                    self._notice = "Service shutdown accepted; finalization continues in the external service"

            del reply
        self._status_at = 0.0

    def _await_shutdown(self, description, *, external):
        """Wait after a shutdown request; the service itself sends device Stop and
        finalizes both recordings. A viewer-owned service is awaited until it exits
        and its exit code checked. Return whether completion was observed."""
        self._progress(description)
        if self.endpoint == self.owned.endpoint and self.owned.process is not None:
            code = self._wait_owned(description)
            if code:
                raise RuntimeError(
                    f"Service shutdown failed (exit {code}); check service.log"
                )
            return code is not None
        if not external:
            return False
        from .flashing import connection_refused

        def stopped():
            try:
                self.client.status()
            except (OSError, RuntimeError) as exc:
                return connection_refused(exc)
            return False

        # An external service stops listening before it finishes writing files;
        # its finalization does not involve the device.
        self._wait_for(stopped, 15, "the acquisition service to stop")
        return True

    def _wait_for(self, condition, timeout, description):
        deadline = time.monotonic() + timeout
        while time.monotonic() < deadline:
            if self.stop_event.is_set():
                raise RuntimeError("Viewer closed; flash preparation stopped")
            if condition():
                return
            self._publish()
            self.stop_event.wait(0.1)
        raise RuntimeError(f"Timed out waiting for {description}")

    def _flash(self, kwargs):
        from .flashing import connection_refused

        self._make_client(kwargs["endpoint"])
        try:
            status = self.client.status()
        except (OSError, RuntimeError) as exc:
            if not connection_refused(exc):
                raise
            self._start_service(kwargs["output"], "", "", repo=kwargs.get("repo"))
            status = self.client.status()
        self.attached = True
        if not status.get("firmware_available"):
            raise RuntimeError(
                "The selected service needs a firmware checkout and Vitis XSCT"
            )
        device = status.get("state", {}).get("device") or status.get("device_target")
        if not device:
            host = kwargs["ip"]
            device = (
                f"[{host}]:{kwargs['port']}"
                if ":" in host
                else f"{host}:{kwargs['port']}"
            )
        job = self.client.firmware("flash", device=device)
        self._message("info", f"Firmware job {job['id']} accepted by {self.endpoint}")
        offset = 0
        while not self.stop_event.is_set() and not self._flash_shutdown.is_set():
            try:
                reply = self.client.job(job["id"], offset)
            except (OSError, RuntimeError):
                if self._flash_shutdown.is_set():
                    return
                raise
            if self._flash_shutdown.is_set():
                return
            if reply["log"]:
                self._message("info", reply["log"])
            next_offset = reply["next_offset"]
            self._progress(f"Flash UZ: {reply['job']['phase']}")
            if reply["job"]["state"] != "running" and next_offset == offset:
                if reply["job"]["state"] != "succeeded":
                    raise RuntimeError(f"Firmware job failed: {reply['job']['result']}")
                self._reset()
                self._status_at = 0
                self._notice = "Flash completed; service session replaced"
                return
            offset = next_offset
            self.stop_event.wait(0.1)

    def _poll_client_for(self, endpoint):
        if self._poll_client is None or self._poll_endpoint != endpoint:
            if self.client_factory is None:
                from ultrazohm_cli import Client

                self._poll_client = Client(endpoint)
            else:
                self._poll_client = self.client_factory(endpoint)
            self._poll_endpoint = endpoint
        return self._poll_client

    def _current(self, generation):
        """Whether no command reset the live history since this poll started."""
        return generation == self._reset_generation and not self.stop_event.is_set()

    def _poll(self):
        with self.lock:
            generation, endpoint = self._reset_generation, self.endpoint
        if generation != self._poll_reset_seen:
            self.cursor = self.cursor_stop = None
            if self.ring is not None:
                self.ring.reset()
            self._poll_reset_seen = generation
        client = self._poll_client_for(endpoint)
        if time.monotonic() >= self._status_at:
            status = client.status()
            assignments = (
                tuple(client.observables()["channels"])
                if status.get("session_id", True)
                else ()
            )
            if status.get("session_id") != self._status.get("session_id"):
                self.cursor = self.cursor_stop = None
                if self.ring is not None:
                    self.ring.reset()
                self._last_source = None
                self._catalog = (
                    client.catalog()["profile"] if status.get("session_id") else {}
                )
            with self.lock:
                if not self._current(generation):
                    return
                self._status, self._assignments = status, assignments
            self._status_at = time.monotonic() + 0.25
        status = self._status
        if not status.get("state", {}).get("connected"):
            return
        capacity = status["data_options"]["buffer_samples"]
        if self.ring is None or self.ring.capacity != capacity:
            self.ring = LiveRing(capacity)
        pages = []
        try:
            page = client.read_since(self.cursor, limit=min(capacity, 100_000))
        except RuntimeError as exc:
            # Only an invalid cursor (expired RAM window, reconnect, changed mapping)
            # requires a new snapshot. Transient errors, including requests canceled
            # by Stop, keep the displayed history and are reported by the caller.
            if self.cursor is None or not cursor_invalid(exc):
                raise
            previous_stop = self.cursor_stop
            self.cursor = self.cursor_stop = None
            self.ring.reset()
            page = client.read_since(limit=min(capacity, 100_000))
            # Refresh through the previously displayed time before publishing;
            # larger histories span multiple IPC pages and must not jump backward.
            for _ in range((capacity + 99_999) // 100_000):
                if (
                    not page.data.height
                    or previous_stop is None
                    or page.stop >= previous_stop
                    or self.stop_event.is_set()
                ):
                    break
                pages.append(page)
                page = client.read_since(page.cursor, limit=min(capacity, 100_000))
            self._notice = "Live buffer resynchronized"
        pages.append(page)
        epoch = (page.info["run_id"], page.info["generation"])
        if epoch != self._epoch:
            self.ring.reset()
        self.cursor, self.cursor_stop = page.cursor, page.stop
        source = None
        if any(part.data.height for part in pages):
            for part in pages:
                self.ring.append(part.data)
            source = LiveSource(self.ring.snapshot())
        with self.lock:
            # A command (shutdown, reconnect, flash) reset the history meanwhile:
            # never publish samples from the previous session.
            if not self._current(generation):
                return
            self._epoch = epoch
            if source is not None:
                self._last_source = source
                self._received_at = time.monotonic()

    def _work(self):
        """Command thread; polling continues independently on ``_poll_work``."""
        while not self.stop_event.is_set():
            try:
                generation, operation, kwargs = self.commands.get(timeout=self.interval)
            except Empty:
                continue
            if self.stop_event.is_set():
                break
            if operation is not None:
                self._error = ""
                self._progress(
                    "Connecting…"
                    if operation == "connect"
                    else f"{operation}: working…"
                )
                try:
                    # Flash only follows a service job; shutdown must not wait for
                    # the GUI-side progress loop.
                    with self._command_lock if operation != "flash" else nullcontext():
                        with self.lock:
                            current = generation == self._command_generation
                        if current and not self.stop_event.is_set():
                            self._command(operation, kwargs)
                    self._error = ""
                except Exception as exc:
                    self._error = str(exc)
                finally:
                    if operation == "flash":
                        self.flashing = False
                    self._activity = ""
                    self._completed_commands += 1
                    self._publish()

    def _poll_work(self):
        """Poll status and samples at a fixed rate while attached, never during Flash UZ."""
        while not self.stop_event.is_set():
            started = time.monotonic()
            if self.attached and not self.flashing:
                try:
                    self._poll()
                    self._poll_error = ""
                except Exception as exc:
                    self._poll_error = str(exc)
                self._publish()
            self.stop_event.wait(max(0.0, self.interval - (time.monotonic() - started)))

    def close(self):
        """Shut down a viewer-owned service; only Stop an externally owned device."""
        if self.stop_event.is_set():
            return
        self.stop_event.set()
        self.cancel_pending_commands()
        for thread in (self.thread, self.poll_thread, self.control_thread):
            if thread is not None:
                thread.join(timeout=1)
        # Commands observe stop_event; bound the wait so a stuck command cannot hang exit.
        locked = self._command_lock.acquire(timeout=35)
        try:
            connected = self.attached
            owned_endpoint = self.owned.endpoint
            owned_running = self.owned.running
            if not connected and not (owned_running and owned_endpoint):
                return  # Unused live panels need no optional CLI backend to close.
            factory = self.client_factory
            if factory is None:
                from ultrazohm_cli import Client

                factory = Client
            # Stop the attached external device first. Cleanup of an unrelated
            # owned service must neither delay this Stop nor skip it on error.
            if connected and (not owned_running or self.endpoint != owned_endpoint):
                try:
                    factory(self.endpoint).stop()
                except Exception as exc:
                    self._message("error", f"Device Stop on viewer close failed: {exc}")
                    print(f"Device Stop on viewer close failed: {exc}", file=sys.stderr)
            if owned_running and owned_endpoint:
                try:
                    if not self.owned.shutdown_requested:
                        owned_client = factory(owned_endpoint)
                        if (
                            self.owned.service_id
                            and owned_client.status()["service_id"]
                            != self.owned.service_id
                        ):
                            raise RuntimeError(
                                "Owned service was replaced; refusing to shut down its replacement"
                            )
                        owned_client.shutdown()
                        self.owned.shutdown_requested = True
                    try:
                        code = self.owned.process.wait(timeout=CLOSE_FINALIZE_TIMEOUT)
                    except subprocess.TimeoutExpired:
                        # The service runs in its own session and keeps finalizing.
                        print(
                            "The acquisition service is still finalizing recordings in the background; "
                            f"see {self.owned.log or 'its service.log'} and the end section of run.json.",
                            file=sys.stderr,
                        )
                        return
                    if code:
                        raise RuntimeError(
                            f"Acquisition service exited with code {code}; check service.log"
                        )
                except Exception as exc:
                    self._message("error", f"Owned service cleanup failed: {exc}")
                    print(f"Owned service cleanup failed: {exc}", file=sys.stderr)
        finally:
            if locked:
                self._command_lock.release()


def new_output_directory(repo=None, *, parent=None):
    from .user_paths import data_directory

    root = Path(parent) if parent is not None else data_directory(repo) / "logs"
    return str(root / (time.strftime("%Y%m%d-%H%M%S") + "-" + uuid.uuid4().hex[:6]))
