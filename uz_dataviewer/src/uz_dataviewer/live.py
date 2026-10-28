"""Native live acquisition adapter. Device IO stays in the independent CLI service.

The worker publishes immutable, bounded snapshots. The GUI never performs network
IO and closing it never shuts down the service. History is deliberately RAM-only
in this prototype; the same Client can later page a selected recording.
"""
from __future__ import annotations

from dataclasses import dataclass, field
from contextlib import nullcontext
import ipaddress
from pathlib import Path
from queue import Empty, Full, Queue
import json
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
    variable_sends: dict = field(default_factory=dict)
    flash_config: tuple | None = None


class LiveController:
    """Single IO worker, bounded command queue, latest snapshot publication."""
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
        self.process = None
        self._owned_endpoint = None
        self._owned_shutdown_requested = False
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
        self._variable_sends = {}
        self.flashing = False
        self._flash_config = None
        self._flash_context = None
        self.messages = Queue(maxsize=2000)

    def submit(self, operation, **kwargs):
        if self.stop_event.is_set():
            raise RuntimeError('Live controller is closed')
        if self.flashing:
            raise RuntimeError('Flash UZ is already running')
        if operation == 'stop':
            self.cancel_pending_commands()
        if operation == 'flash':
            self.flashing = True
        if self.thread is None:
            self.thread = threading.Thread(target=self._work, name='uz-live', daemon=True)
            self.thread.start()
        try:
            with self.lock:
                self.commands.put_nowait((self._command_generation, operation, kwargs))
        except Full as exc:
            if operation == 'flash':
                self.flashing = False
            raise RuntimeError('Live command queue is busy') from exc

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
                from ultrazohm import Client
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
        self.revision += 1
        with self.lock:
            self.update = LiveUpdate(self.revision, self._status, self._catalog,
                                     self._assignments, self._last_source, self._epoch,
                                     self._error or self._poll_error, self._notice,
                                     self.attached, self._received_at,
                                     self._activity, self._completed_commands, self._variable_sends.copy(),
                                     self._flash_config)

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
        self.cursor = self.frame = self._last_source = self._epoch = None
        self._received_at = 0.

    def _make_client(self, endpoint):
        if endpoint != self.endpoint or self.client is None:
            self._reset()
            self._status, self._catalog, self._assignments = {}, {}, ()
            self._variable_sends = {}
            self.attached = False
            if self.client_factory is None:
                from ultrazohm import Client
                self.client = Client(endpoint)
            else:
                self.client = self.client_factory(endpoint)
            self.endpoint = endpoint

    def _start_service(self, output, mapping, profile=None, data_options=None, ack=False):
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
        if profile:
            args += ['--profile', str(profile)]
        if ack:
            args += ['--ack', 'on']
        for name in ('buffer_samples', 'segment_rows', 'flush_interval_ms', 'recording_backend'):
            if (value := (data_options or {}).get(name)) is not None:
                args += ['--'+name.replace('_', '-'), str(value)]
        options = {'stdin': subprocess.DEVNULL, 'start_new_session': True} if os.name != 'nt' else {
            'stdin': subprocess.DEVNULL,
            'creationflags': subprocess.DETACHED_PROCESS | subprocess.CREATE_NEW_PROCESS_GROUP}
        with log_path.open('ab') as log:
            self.process = subprocess.Popen(args, stdout=log, stderr=log, **options)
            self._owned_endpoint = self.endpoint
            self._owned_shutdown_requested = False
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
        if operation == 'flash':
            self._flash(kwargs)
        elif operation in ('attach', 'connect'):
            self._progress('Checking acquisition service…')
            self._make_client(kwargs['endpoint'])
            try:
                self.client.status()
            except (OSError, RuntimeError):
                if operation != 'connect':
                    raise
                self._start_service(kwargs['output'], kwargs.get('mapping', ''),
                                    kwargs.get('profile'), kwargs.get('data_options'), kwargs.get('ack', False))
            else:
                if operation == 'connect' and not (
                        self._owned_endpoint == self.endpoint and self.process is not None
                        and self.process.poll() is None):
                    raise RuntimeError('A service is already running at this endpoint. Use Existing service > Attach.')
            self._progress('Reading service configuration…')
            status = self.client.status()
            if operation == 'connect':
                if status['state']['connected']:
                    requested = (ipaddress.ip_address(kwargs['ip']), int(kwargs['port']))
                    device = status['state'].get('device', '')
                    host, _, port = device.rpartition(':')
                    try:
                        actual = (ipaddress.ip_address(host.strip('[]')), int(port))
                    except ValueError:
                        actual = None
                    if actual != requested:
                        raise RuntimeError(f'Service is already connected to {device or "an unknown device"}; '
                                           f'requested {kwargs["ip"]}:{kwargs["port"]}. '
                                           'Use Attach service for that device or a separate service endpoint.')
                else:
                    self._progress(f'Connecting to UltraZohm at {kwargs["ip"]}:{kwargs["port"]}…')
                    self.client.connect(kwargs['ip'], kwargs['port'])
                    self._reset()
            self._catalog = self.client.catalog()['profile']
            self.attached = True
            self._status = self.client.status()
            self._notice = f'Attached to acquisition service at {self.endpoint}'
            if mapping := kwargs.get('mapping'):
                try:
                    expected = json.loads(Path(mapping).expanduser().read_text(encoding='utf-8'))
                    fields = ('api_version', 'channels', 'samples_per_packet', 'observables',
                              'slow_signals', 'variables', 'commands', 'platform_state')
                    if any(expected.get(key) != self._catalog.get(key) for key in fields):
                        self._notice += (f'. The service uses a different channel mapping than {mapping}. '
                                         'Restart the service to apply the selected mapping.')
                except (OSError, ValueError) as exc:
                    self._notice += f'. Could not compare the selected channel mapping: {exc}'
        elif operation == 'detach':
            self.attached = False
            self._notice = 'Detached; the service and logging continue'
        else:
            if not self.attached:
                raise RuntimeError('Attach to a service first')
            reply = getattr(self.client, operation)(**kwargs)
            if operation == 'set_variable':
                self._variable_sends[kwargs['name']] = (time.monotonic(), kwargs['value'])
            self._notice = f'{operation}: request sent (device commands have no acknowledgment)'
            if operation == 'set_observable':
                self._reset()
            if operation == 'shutdown':
                if self.endpoint == self._owned_endpoint:
                    self._owned_shutdown_requested = True
                self.attached = False
                self._reset()
                self._status, self._catalog, self._assignments = {}, {}, ()
                self._progress('Stopping device and finalizing recordings…')
                if self.endpoint == self._owned_endpoint and self.process is not None:
                    code = self.process.wait()
                    if code:
                        raise RuntimeError(f'Service shutdown failed (exit {code}); check service.log')
                    self._notice = 'Service shut down; recordings finalized'
                else:
                    self._notice = 'Service shutdown accepted; finalization continues in the external service'

            del reply
        self._status_at = 0.

    def _wait_for(self, condition, timeout, description):
        deadline = time.monotonic() + timeout
        while time.monotonic() < deadline:
            if self.stop_event.is_set():
                raise RuntimeError('Viewer closed; flash preparation stopped')
            if condition():
                return
            self._publish()
            self.stop_event.wait(.1)
        raise RuntimeError(f'Timed out waiting for {description}')

    def _flash(self, kwargs):
        from .flashing import connection_refused, profile_for_mapping, run_flash_cli, xsct_available
        from .live_mapping import generate_mapping, repository
        if not xsct_available():
            raise RuntimeError('Vitis XSCT (xsct) is not on PATH. Load the Vitis environment and restart the viewer.')
        root = repository(kwargs.get('repo') or None)
        self._make_client(kwargs['endpoint'])
        self._poll_error = ''
        self._progress('Preparing Flash UZ…')
        try:
            status = self.client.status()
        except (OSError, RuntimeError) as exc:
            if not connection_refused(exc):
                raise
            status = None
        previous, assignments = None, None
        settings = status or {}
        if status is None and self._flash_context is not None and self._flash_context[0] == self.endpoint:
            _, previous, assignments, settings = self._flash_context
        target_ip, target_port = kwargs['ip'], kwargs['port']
        if address := settings.get('state', {}).get('device'):
            host, port = address.rsplit(':', 1)
            target_ip, target_port = host.strip('[]'), int(port)
        if status is not None:
            previous = self.client.catalog()['profile']
            if status['state'].get('connected'):
                assignments = {str(item['channel']): item['name'] for item in
                               self.client.observables()['channels'] if item['name']}
            self._flash_context = (self.endpoint, previous, assignments, settings)
            if status['state'].get('connected'):
                self._progress('Sending device Stop…')
                self.client.stop()
            self._progress('Stopping and finalizing recordings…')
            for stream, stop in (('fast', 'stop_logging'), ('slow', 'stop_logging_slow_data')):
                if status.get('logging', {}).get(stream, {}).get('phase') in ('recording', 'paused'):
                    getattr(self.client, stop)()
            def finalized():
                self._status = self.client.status()
                for info in self._status.get('logging', {}).values():
                    if info.get('phase') == 'failed':
                        raise RuntimeError(f'Recording finalization failed: {info.get("error")}')
                    if info.get('phase') in ('recording', 'paused', 'finalizing'):
                        return False
                return True
            self._wait_for(finalized, 300, 'recordings to finalize')
            self._progress('Shutting down acquisition service…')
            self.attached = False
            self.client.shutdown()
            def stopped():
                try:
                    self.client.status()
                except (OSError, RuntimeError) as exc:
                    return connection_refused(exc)
                return False
            self._wait_for(stopped, 15, 'the acquisition service to stop')
            if self.process is not None:
                self.process.wait(timeout=5)
        self.attached = False
        self._reset()
        self._status, self._catalog, self._assignments = {}, {}, ()
        if self.stop_event.is_set():
            return
        self._progress('Generating channel mapping…')
        mapping_path = generate_mapping(root, overwrite=True)
        self._message('info', f'Channel mapping regenerated: {mapping_path}')
        mapping = json.loads(mapping_path.read_text(encoding='utf-8'))
        profile, removed = profile_for_mapping(root, mapping, previous, assignments)
        if removed:
            self._message('warn', 'Removed channel assignments absent from the new mapping: '+', '.join(removed))
        output = Path(kwargs['output']).expanduser().resolve().parent / Path(new_output_directory()).name
        output.parent.mkdir(parents=True, exist_ok=True)
        profile_path = output.with_name(output.name+'.profile.json')
        profile_path.write_text(json.dumps(profile, indent=2), encoding='utf-8')
        self._flash_config = (str(mapping_path), str(output))
        self._progress('Flashing UltraZohm; see Console for progress…')
        if not run_flash_cli(root, self.endpoint, self.stop_event, self._message):
            return
        if self.stop_event.is_set():
            return
        self._progress('Reconnecting to UltraZohm…')
        self._start_service(str(output), str(mapping_path), str(profile_path),
                            settings.get('data_options'), settings.get('send_ack', False))
        last_error = ''
        def reconnected():
            nonlocal last_error
            try:
                if not self.client.status()['state'].get('connected'):
                    self.client.connect(target_ip, target_port)
                return True
            except (OSError, RuntimeError) as exc:
                last_error = str(exc)
                return False
        try:
            self._wait_for(reconnected, 20, 'UltraZohm to reconnect')
        except RuntimeError as exc:
            raise RuntimeError(f'{exc}: {last_error}') from exc
        self._command('attach', dict(endpoint=self.endpoint, mapping=str(mapping_path)))
        self._variable_sends = {}
        self._flash_context = None
        self._notice = 'Flash completed; acquisition service restarted and connected'

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
                generation, operation, kwargs = self.commands.get(timeout=self.interval)
            except Empty:
                operation = None
            if self.stop_event.is_set():
                break
            if operation is not None:
                self._error = ''
                self._progress('Connecting…' if operation == 'connect' else f'{operation}: working…')
                try:
                    # Flash checks stop_event between its preparation stages and
                    # may run a detached programmer; do not lock shutdown behind it.
                    with self._command_lock if operation != 'flash' else nullcontext():
                        with self.lock:
                            current = generation == self._command_generation
                        if current and not self.stop_event.is_set():
                            self._command(operation, kwargs)
                    self._error = ''
                except Exception as exc:
                    self._error = str(exc)
                finally:
                    if operation == 'flash':
                        self.flashing = False
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
        """Shut down a viewer-owned service; only Stop an externally owned device."""
        if self.stop_event.is_set():
            return
        self.stop_event.set()
        self.cancel_pending_commands()
        if self.thread is not None:
            self.thread.join(timeout=1)
        with self._command_lock:
            connected = self.attached and self._status.get('state', {}).get('connected', False)
            owned_endpoint = self._owned_endpoint
            owned_running = self.process is not None and self.process.poll() is None
            factory = self.client_factory
            if factory is None:
                from ultrazohm import Client
                factory = Client
            # Stop the attached external device first. Cleanup of an unrelated
            # owned service must neither delay this Stop nor skip it on error.
            if connected and (not owned_running or self.endpoint != owned_endpoint):
                try:
                    factory(self.endpoint).stop()
                except Exception as exc:
                    self._message('error', f'Device Stop on viewer close failed: {exc}')
                    print(f'Device Stop on viewer close failed: {exc}', file=sys.stderr)
            if owned_running and owned_endpoint:
                try:
                    if not self._owned_shutdown_requested:
                        factory(owned_endpoint).shutdown()
                        self._owned_shutdown_requested = True
                    code = self.process.wait()
                    if code:
                        raise RuntimeError(f'Acquisition service exited with code {code}; check service.log')
                except Exception as exc:
                    self._message('error', f'Owned service cleanup failed: {exc}')
                    print(f'Owned service cleanup failed: {exc}', file=sys.stderr)


def new_output_directory():
    return str(Path.cwd() / 'artifacts' / 'live_logs' /
               (time.strftime('%Y%m%d-%H%M%S') + '-' + uuid.uuid4().hex[:6]))
