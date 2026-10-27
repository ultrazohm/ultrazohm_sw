"""Native live acquisition adapter. Device IO stays in the independent CLI service.

The worker publishes immutable, bounded snapshots. The GUI never performs network
IO and closing it never shuts down the service. History is deliberately RAM-only
in this prototype; the same Client can later page a selected recording.
"""
from __future__ import annotations

from dataclasses import dataclass, field
from pathlib import Path
from queue import Empty, Full, Queue
import os
import subprocess
import sys
import threading
import time
import uuid

import numpy as np

from .sources import MemorySource, PlotData, check, envelope


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


class LiveSource(MemorySource):
    """An immutable display snapshot; decimate only the visible window."""
    def __init__(self, frame):
        t = frame['time'].to_numpy()
        channels = {n: frame[n].to_numpy() for n in frame.columns if n not in ('time', 'status')}
        super().__init__(t, channels)
        self.units = dict.fromkeys(channels, '')
        self.timestamp_resolution = 0.
        # MemorySource creates a unique identity, which invalidates display results
        # even when the user keeps the same (paused) X-axis range while data grows.

    def read_plot(self, channel, lo, hi, budget, cancel=None, *, padding=True, offset=0.):
        check(cancel)
        a, b = self.bounds(lo, hi, cancel, padding=padding, offset=offset)
        t, ys = self.read_rows([channel], a, b, cancel)
        if not len(t):
            return PlotData(t, ys[channel], 0)
        tx, y = envelope(t, ys[channel], np.arange(a, b), budget)
        return PlotData(tx, y, b - a)

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
    error: str = ''
    notice: str = ''
    attached: bool = False
    received_at: float = 0.
    activity: str = ''
    completed_commands: int = 0


class LiveController:
    """Single IO worker, bounded command queue, latest snapshot publication."""
    def __init__(self, client_factory=None, hz=30):
        self.client_factory = client_factory
        self.interval = 1 / hz
        self.commands = Queue(maxsize=32)
        self.lock = threading.Lock()
        self.update = LiveUpdate()
        self.stop_event = threading.Event()
        self.thread = None
        self.process = None
        self.client = None
        self.endpoint = None
        self.cursor = None
        self.frame = None
        self.attached = False
        self.revision = 0
        self._status_at = 0.
        self._last_source = None
        self._epoch = None
        self._status = {}
        self._catalog = {}
        self._assignments = ()
        self._notice = ''
        self._error = ''
        self._poll_error = ''
        self._received_at = 0.
        self._activity = ''
        self._completed_commands = 0

    def submit(self, operation, **kwargs):
        if self.stop_event.is_set():
            raise RuntimeError('Live controller is closed')
        if self.thread is None:
            self.thread = threading.Thread(target=self._work, name='uz-live', daemon=True)
            self.thread.start()
        try:
            self.commands.put_nowait((operation, kwargs))
        except Full as exc:
            raise RuntimeError('Live command queue is busy') from exc

    def latest(self):
        with self.lock:
            return self.update

    def _publish(self):
        if self.stop_event.is_set():
            return
        self.revision += 1
        with self.lock:
            self.update = LiveUpdate(self.revision, self._status, self._catalog,
                                     self._assignments, self._last_source, self._epoch,
                                     self._error or self._poll_error, self._notice,
                                     self.attached, self._received_at,
                                     self._activity, self._completed_commands)

    def _progress(self, message):
        self._activity = message
        self._publish()

    def _reset(self):
        self.cursor = self.frame = self._last_source = self._epoch = None
        self._received_at = 0.

    def _make_client(self, endpoint):
        if endpoint != self.endpoint or self.client is None:
            self._reset()
            self._status, self._catalog, self._assignments = {}, {}, ()
            if self.client_factory is None:
                from ultrazohm import Client
                self.client = Client(endpoint)
            else:
                self.client = self.client_factory(endpoint)
            self.endpoint = endpoint

    def _start_service(self, output, mapping):
        self._progress('Starting local acquisition service…')
        if getattr(sys, 'frozen', False):
            raise RuntimeError('Start ultrazohm serve separately and use Attach service in the packaged viewer')
        if self.process is not None and self.process.poll() is None:
            raise RuntimeError('The launched service is still running; check its endpoint and service.log')
        output = Path(output).expanduser().resolve()
        # One output directory per service lifetime, never reuse an existing run.
        output.parent.mkdir(parents=True, exist_ok=True)
        if output.exists():
            raise ValueError('Choose a new session directory; existing recordings are never overwritten')
        log_path = output.with_name(output.name + '.service.log')
        args = [sys.executable, '-c', 'from ultrazohm.cli import main; raise SystemExit(main())',
                '--endpoint', self.endpoint, 'serve', '--output', str(output), '--format', 'parquet']
        if mapping:
            args += ['--channel-mapping', str(Path(mapping).expanduser().resolve())]
        options = {'stdin': subprocess.DEVNULL, 'start_new_session': True} if os.name != 'nt' else {
            'stdin': subprocess.DEVNULL,
            'creationflags': subprocess.DETACHED_PROCESS | subprocess.CREATE_NEW_PROCESS_GROUP}
        with log_path.open('ab') as log:
            self.process = subprocess.Popen(args, stdout=log, stderr=log, **options)
        deadline = time.monotonic() + 8
        while not self.stop_event.is_set() and time.monotonic() < deadline:
            if self.process.poll() is not None:
                raise RuntimeError(f'Service failed; see {log_path}')
            try:
                self.client.status()
                return
            except (OSError, RuntimeError):
                self.stop_event.wait(.1)
        raise RuntimeError(f'Service startup timed out; see {log_path}')

    def _command(self, operation, kwargs):
        if operation in ('attach', 'connect'):
            self._progress('Checking acquisition service…')
            self._make_client(kwargs['endpoint'])
            try:
                self.client.status()
            except (OSError, RuntimeError):
                if operation != 'connect':
                    raise
                self._start_service(kwargs['output'], kwargs.get('mapping', ''))
            self._progress('Reading service configuration…')
            self._catalog = self.client.catalog()['profile']
            self.attached = True
            if operation == 'connect' and not self.client.status()['state']['connected']:
                self._progress(f'Connecting to UltraZohm at {kwargs["ip"]}:{kwargs["port"]}…')
                self.client.connect(kwargs['ip'], kwargs['port'])
                self._reset()
            self._status = self.client.status()
            self._notice = f'Attached to acquisition service at {self.endpoint}'
        elif operation == 'detach':
            self.attached = False
            self._notice = 'Detached; the service and logging continue'
        else:
            if not self.attached:
                raise RuntimeError('Attach to a service first')
            reply = getattr(self.client, operation)(**kwargs)
            self._notice = f'{operation}: request sent (device commands have no acknowledgment)'
            if operation == 'set_observable':
                self._reset()
            if operation == 'shutdown':
                self.attached = False
                self._notice = 'Service shutdown requested; finalizing logs. Device Stop is separate.'
            del reply
        self._status_at = 0.

    def _poll(self):
        if time.monotonic() >= self._status_at:
            self._status = self.client.status()
            self._assignments = tuple(self.client.observables()['channels'])
            self._status_at = time.monotonic() + .25
        if not self._status.get('state', {}).get('connected'):
            return
        capacity = self._status['data_options']['buffer_samples']
        try:
            page = self.client.read_since(self.cursor, limit=min(capacity, 100_000))
        except RuntimeError:
            # An expired RAM cursor, reconnect, or changed mapping requires a new
            # bounded snapshot. A second failure is surfaced, never silently looped.
            self._reset()
            page = self.client.read_since(limit=min(capacity, 100_000))
            self._notice = 'Live buffer resynchronized; earlier samples are unavailable in this view'
        epoch = (page.info['run_id'], page.info['generation'])
        if epoch != self._epoch:
            self.frame = None
            self._epoch = epoch
        self.cursor = page.cursor
        if page.data.height:
            import polars as pl
            self.frame = (page.data if self.frame is None else
                          pl.concat([self.frame, page.data], rechunk=False)).tail(capacity).rechunk()
            self._last_source = LiveSource(self.frame)
            self._received_at = time.monotonic()

    def _work(self):
        while not self.stop_event.is_set():
            started = time.monotonic()
            try:
                operation, kwargs = self.commands.get(timeout=self.interval)
            except Empty:
                operation = None
            if self.stop_event.is_set():
                break
            if operation is not None:
                self._error = ''
                self._progress('Connecting…' if operation == 'connect' else f'{operation}: working…')
                try:
                    self._command(operation, kwargs)
                    self._error = ''
                except Exception as exc:
                    self._error = str(exc)
                finally:
                    self._activity = ''
                    self._completed_commands += 1
                    self._publish()
            if self.attached:
                try:
                    self._poll()
                    self._poll_error = ''
                except Exception as exc:
                    self._poll_error = str(exc)
            self._publish()
            self.stop_event.wait(max(0., self.interval - (time.monotonic() - started)))

    def close(self):
        """Detach only. A launched service intentionally outlives the viewer."""
        self.stop_event.set()
        if self.thread is not None:
            self.thread.join(timeout=1)
        # Popen is retained only for startup diagnostics, never terminate it here.


def new_output_directory():
    return str(Path.cwd() / 'artifacts' / 'live_logs' /
               (time.strftime('%Y%m%d-%H%M%S') + '-' + uuid.uuid4().hex[:6]))
