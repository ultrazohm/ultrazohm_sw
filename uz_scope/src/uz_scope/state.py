"""Single application state for uz_scope.

Owns the config, the network client, the sample ring, the logger and the
console/command registry.  The reader thread only touches the ring, the
logger queue and a few GIL-atomic fields; everything UI-facing happens on the
main thread (``poll_events`` drains reader-thread notifications).
"""

from __future__ import annotations

import collections
import subprocess
import sys
import threading
import time
from dataclasses import dataclass
from pathlib import Path

from uz_dataviewer.console import Console

from .acquisition import AcquisitionEngine
from .capture_log import CaptureLogger, make_column_names
from .commands import CommandError, ScopeCommandRegistry
from .history import SessionHistory
from .slowdata import SlowDataStore
from .config import SETTINGS_FILENAME, ScopeConfig
from .javascope_header import HeaderConfig, find_header, parse_header
from .lifecheck import Lifecheck
from .netclient import ClientCallbacks, ScopeClient
from .protocol import (
    STATUS_BIT_EXT_LOG,
    ParsedFrames,
    encode_channel_select,
    encode_command,
    status_bit,
)
from .ring import ChannelRing, ring_capacity


# Rate auto-detect (ported from ReceiveController.java:1626-1677): wait for the
# stream to settle, measure the sample rate over a window, snap to the nominal
# rate when close, else round to the nearest kHz, clamped.
RATE_DETECT_DELAY_S = 5.0
RATE_DETECT_WINDOW_S = 5.0
RATE_SNAP_FRACTION = 0.05
RATE_MAX_HZ = 200_000.0


@dataclass
class SentCommand:
    timestamp: float  # time.monotonic()
    cmd_id: int
    value: float
    label: str


@dataclass
class PlotWindowView:
    """Transient per-plot-window view state (never persisted).

    ``attached`` = the x-axis follows the live edge; any pan/zoom gesture
    detaches, the Follow button (``plot_follow``) re-attaches.  ``pending_x``
    applies explicit limits once (``x_lim`` command / zoom replay);
    ``fit_pending`` asks the panel for a one-shot fit to the data extent.
    """

    attached: bool = True
    pending_x: tuple[float, float] | None = None
    fit_pending: bool = False


class ScopeAppState:
    def __init__(
        self,
        config: ScopeConfig | None = None,
        header: HeaderConfig | None = None,
        settings_path: str | Path | None = None,
    ) -> None:
        self.settings_path = Path(settings_path) if settings_path else Path(SETTINGS_FILENAME)
        config_load_error: str | None = None
        if config is None:
            config = ScopeConfig()
            if self.settings_path.is_file():
                try:
                    config = ScopeConfig.load(self.settings_path)
                except Exception as exc:
                    # A hand-edited/corrupt settings file must not prevent
                    # startup — fall back to defaults and say so.
                    config_load_error = f"{type(exc).__name__}: {exc}"
        self.config = config
        self.console = Console()
        if config_load_error:
            self.console.error(
                f"could not load {self.settings_path}: {config_load_error} "
                "— using default settings"
            )
        self.commands = ScopeCommandRegistry()
        self.header = header if header is not None else self._load_header()

        self.client: ScopeClient | None = None
        self.detected_rate: float | None = None
        self.ring: ChannelRing = self._make_ring()
        self.history: SessionHistory = self._make_history()
        self.lifecheck = Lifecheck()
        self.logger: CaptureLogger | None = None
        self.engine: AcquisitionEngine | None = None
        self.slowdata = SlowDataStore(self.header.slowdata if self.header else [])

        self.frozen = False
        self.fix_axis = False
        # start_log/stop_log run from the UI thread AND the reader thread
        # (external log trigger) — serialize the logger swap.
        self._log_mutex = threading.Lock()
        self.last_status = 0
        self._prev_ext_log = False
        # An armed trigger never survives a restart — the engine is gone.
        self.config.trigger.enabled = False
        # Reader-thread -> UI notifications, drained once per frame.
        self._events: collections.deque[tuple[str, str]] = collections.deque(maxlen=64)
        # Diagnostics: last commands sent to the device (any thread appends).
        self.cmd_trace: collections.deque[SentCommand] = collections.deque(maxlen=200)
        self.last_log_path: Path | None = None
        # Rate detection probe: (t_start, samples_at_start) or None.
        self._rate_probe: tuple[float, int] | None = None
        self._rate_probe_manual = False
        # Slot whose observable is JSO_lifecheck (reader thread reads this).
        self._lifecheck_slot: int | None = None
        self._refresh_lifecheck_slot()
        # Set by the app shell: True/False once the guard port bind was tried.
        self.single_instance: bool | None = None
        # Session-only connection target (--ip/--port CLI flags); never saved.
        self.ip_override: str | None = None
        self.port_override: int | None = None
        # Transient per-plot-window view state, keyed by window index.
        self.plot_views: dict[int, PlotWindowView] = {}
        # Drag-and-drop scratch (payload data travels out-of-band, the
        # imgui payload itself is just a type tag — dataviewer idiom).
        self.dragged_slot: int | None = None
        self.dragged_observable: int | None = None
        self.dragged_binding: tuple[str, str] | None = None

    # --- derived ----------------------------------------------------------

    @property
    def sample_rate(self) -> float:
        if self.detected_rate:
            return self.detected_rate
        return 1e6 / self.config.timestep_usec

    @property
    def timestep_s(self) -> float:
        return 1.0 / self.sample_rate

    def observable_name(self, index: int) -> str:
        if self.header and 0 <= index < len(self.header.observables):
            return self.header.observables[index]
        return f"observable_{index}"

    def _load_header(self) -> HeaderConfig | None:
        path = Path(self.config.header_path)
        if not path.is_file():
            found = find_header()
            path = found if found else path
        if path.is_file():
            cfg = parse_header(path)
            for warning in cfg.warnings:
                self.console.warn(f"javascope.h: {warning}")
            self.console.info(
                f"header {path}: {len(cfg.observables)} observables, "
                f"{len(cfg.slowdata)} slowdata"
            )
            return cfg
        self.console.warn(
            f"javascope.h not found ({self.config.header_path}); "
            "observable names and command ids unavailable"
        )
        return None

    # --- ring -------------------------------------------------------------

    def _make_ring(self) -> ChannelRing:
        capacity = ring_capacity(
            self.config.channels,
            self.sample_rate,
            self.config.ring_seconds,
            self.config.max_ring_bytes,
        )
        return ChannelRing(self.config.channels, capacity)

    def _make_history(self) -> SessionHistory:
        return SessionHistory(
            self.config.history, self.config.channels, self.sample_rate
        )

    def rebuild_history(self) -> None:
        """Apply changed history settings (drops the collected session)."""
        self.history.close(keep=self.config.history.keep_files)
        self.history = self._make_history()

    def rebuild_ring(self) -> None:
        # The ring's absolute sample clock restarts, so the history (which is
        # anchored to it) must restart too.
        self.history.close(keep=self.config.history.keep_files)
        self.ring = self._make_ring()
        self.history = self._make_history()
        self.lifecheck.reset()

    def set_geometry(self, channels: int, samples_per_packet: int) -> None:
        if not 1 <= channels <= 1024:
            raise CommandError(f"channels must be 1..1024, got {channels}")
        if not 1 <= samples_per_packet <= 8192:
            raise CommandError(
                f"samples_per_packet must be 1..8192, got {samples_per_packet}"
            )
        if self.client is not None:
            raise CommandError("disconnect before changing the frame geometry")
        if self.logger is not None:
            raise CommandError("stop logging before changing the frame geometry")
        self.config.channels = channels
        self.config.samples_per_packet = samples_per_packet
        self.config.ensure_channel_count()
        self.config.ensure_plots()
        self.rebuild_ring()
        self._refresh_lifecheck_slot()

    def load_config(self, path: str | Path) -> None:
        if self.client is not None:
            raise CommandError("disconnect before loading a session")
        if self.logger is not None:
            raise CommandError("stop logging before loading a session")
        self.config = ScopeConfig.load(path)
        self.config.trigger.enabled = False
        self.detected_rate = None
        self.engine = None
        self.rebuild_ring()
        self._refresh_lifecheck_slot()

    # --- connection ---------------------------------------------------------

    def connect(self, ip: str | None = None, port: int | None = None) -> None:
        """Connect to the saved default, or to a one-off ``ip``/``port``.

        Resolution: explicit argument > session override (``--ip``/``--port``
        CLI flags) > saved config.  Only ``set_ip``/``set_port`` change the
        saved default — connecting to a test server never clobbers it.
        """
        if self.client is not None:
            raise CommandError("already connected (disconnect first)")
        self.client = ScopeClient(
            self.config.geometry,
            ip or self.ip_override or self.config.ip,
            port or self.port_override or self.config.port,
            ack_pacing=self.config.ack_pacing,
            callbacks=ClientCallbacks(
                on_frames=self._on_frames,
                on_connect=self._on_connect,
                on_disconnect=self._on_disconnect,
            ),
        )
        self.client.start()

    def disconnect(self) -> None:
        client, self.client = self.client, None
        if client is not None:
            client.stop()

    @property
    def connected(self) -> bool:
        return self.client is not None and self.client.connected.is_set()

    # --- reader-thread callbacks -------------------------------------------

    def _on_connect(self, client: ScopeClient) -> None:
        # Full channel-select burst so device and config agree (JavaScope does
        # the same). With pacing on these ride the first ack slots.
        for slot, ch in enumerate(self.config.channel_settings):
            client.send_command(encode_channel_select(slot, ch.observable))
            self._trace(201 + slot, float(ch.observable), f"select CH{slot + 1}")
        self.lifecheck.reset()
        self._rate_probe = None
        self._events.append(("ok", f"connected to {client.ip}:{client.port}"))

    def _on_disconnect(self, client: ScopeClient, reason: str) -> None:
        self._events.append(("warn", f"connection lost: {reason} (reconnecting)"))

    def _on_frames(self, parsed: ParsedFrames) -> None:
        start_index = self.ring.total_written
        k, c, n = parsed.samples.shape
        # One (k, C, N) -> (C, k*N) copy shared by ring, history and logger
        # (the reshape after transpose cannot be a view, so this is fresh
        # memory that is never mutated afterwards — safe to share queues).
        block = parsed.samples.transpose(1, 0, 2).reshape(c, k * n)
        self.ring.append(block)
        self.history.on_block(block, start_index)
        self.last_status = int(parsed.status[-1])
        engine = self.engine
        if engine is not None:
            engine.on_block(block[engine.channel], start_index)
        lc_slot = self._lifecheck_slot
        if lc_slot is not None:
            self.lifecheck.update(block[lc_slot])
        self.slowdata.on_block(parsed.slow_id, parsed.slow_raw)
        if self.config.logging.ext_trigger:
            self._ext_log_edge(status_bit(self.last_status, STATUS_BIT_EXT_LOG))
        logger = self.logger
        if logger is not None:
            logger.submit(block, start_index)

    # --- commands to the device --------------------------------------------

    def _require_client(self) -> ScopeClient:
        if self.client is None:
            raise CommandError("not connected")
        return self.client

    def button_id(self, name: str) -> int:
        if self.header:
            bid = self.header.button_id.get(name)
            if bid is not None:
                return bid
        # Canonical gui_button_mapping fallback (header unavailable).
        fallback = {"Enable_System": 1, "Enable_Control": 2, "Stop": 3,
                    "Error_Reset": 32}
        if name.startswith("My_Button_"):
            return 23 + int(name.rsplit("_", 1)[1])
        if name in fallback:
            return fallback[name]
        raise CommandError(f"Unknown button: {name}")

    def _trace(self, cmd_id: int, value: float, label: str) -> None:
        self.cmd_trace.append(SentCommand(time.monotonic(), cmd_id, value, label))

    def send_button(self, name: str, value: float = 1.0) -> None:
        cmd_id = self.button_id(name)
        self._require_client().send_command(encode_command(cmd_id, value))
        self._trace(cmd_id, value, name)

    def send_field(self, n: int, value: float) -> None:
        # Set_Send_Field_1..20 are ids 4..23 in gui_button_mapping.
        cmd_id = self.button_id(f"Set_Send_Field_{n}") if self.header else 3 + n
        self._require_client().send_command(encode_command(cmd_id, value))
        self._trace(cmd_id, value, f"Set_Send_Field_{n}")

    def select_observable(self, slot: int, observable: int) -> None:
        self.config.channel_settings[slot].observable = observable
        # A slot with an assignment is by definition a logged variable
        # (keeps ch_select scripts recreating the logged list).
        if slot not in self.config.logged_slots:
            self.config.logged_slots.append(slot)
        # Older ring/history samples on this slot belong to the previous
        # observable — clamp queries to the reassignment epoch.
        self.history.note_epoch(slot, self.ring.total_written)
        self._refresh_lifecheck_slot()
        if self.client is not None:
            self.client.send_command(encode_channel_select(slot, observable))
            self._trace(201 + slot, float(observable), f"select CH{slot + 1}")

    def _refresh_lifecheck_slot(self) -> None:
        idx = self.header.observable_index.get("JSO_lifecheck") if self.header else None
        slot = None
        if idx is not None:
            slot = next(
                (
                    i
                    for i, ch in enumerate(self.config.channel_settings)
                    if ch.observable == idx
                ),
                None,
            )
        self._lifecheck_slot = slot

    # --- trigger ------------------------------------------------------------

    def arm_trigger(self) -> None:
        cfg = self.config.trigger
        if cfg.channel >= 1:
            slot = cfg.channel - 1
        else:  # auto: first visible channel
            slot = next(
                (i for i, ch in enumerate(self.config.channel_settings) if ch.visible),
                0,
            )
        if slot >= self.config.channels:
            raise CommandError(f"trigger channel out of range: {slot + 1}")
        window = int(self.config.window_seconds * self.sample_rate)
        window = max(2, min(window, self.ring.capacity))
        self.engine = AcquisitionEngine(
            self.ring,
            channel=slot,
            edge=cfg.edge,
            level=cfg.level,
            pretrigger=cfg.pretrigger,
            window=window,
            mode=cfg.mode,
        )
        self.engine.arm()
        cfg.enabled = True

    def disarm_trigger(self) -> None:
        self.engine = None
        self.config.trigger.enabled = False

    def rearm_if_armed(self) -> None:
        if self.config.trigger.enabled:
            self.arm_trigger()

    # --- plot windows -------------------------------------------------------

    def plot_view(self, win: int) -> PlotWindowView:
        view = self.plot_views.get(win)
        if view is None:
            view = self.plot_views[win] = PlotWindowView()
        return view

    def plot_window(self, win: int):
        """1-based window index -> PlotWindowSettings (validated)."""
        if not 1 <= win <= len(self.config.plots):
            raise CommandError(
                f"plot window out of range (1..{len(self.config.plots)}): {win}"
            )
        return self.config.plots[win - 1]

    def plot_cell(self, win: int, cell: int) -> list[int]:
        window = self.plot_window(win)
        n = window.rows * window.cols
        if not 1 <= cell <= n:
            raise CommandError(f"cell out of range (1..{n}): {cell}")
        return window.cells[cell - 1]

    def set_slot_visible(self, slot: int, visible: bool) -> None:
        """Legacy 'visible' flag == membership in plot window 1, cell 1."""
        self.config.channel_settings[slot].visible = visible
        cell = self.config.plots[0].cells[0]
        if visible and slot not in cell:
            cell.append(slot)
        elif not visible and slot in cell:
            cell.remove(slot)
        # A slot shown in a plot is by definition a logged variable —
        # keeps the exported script able to reproduce its settings.
        if visible and slot not in self.config.logged_slots:
            self.config.logged_slots.append(slot)

    def plot_assign_slot(self, win: int, cell: int, slot: int) -> None:
        slots = self.plot_cell(win, cell)
        if slot not in slots:
            slots.append(slot)
        if win == 1 and cell == 1:
            self.config.channel_settings[slot].visible = True
        if slot not in self.config.logged_slots:
            self.config.logged_slots.append(slot)

    def plot_unassign_slot(self, win: int, cell: int, slot: int) -> None:
        slots = self.plot_cell(win, cell)
        if slot in slots:
            slots.remove(slot)
        if win == 1 and cell == 1:
            self.config.channel_settings[slot].visible = False

    # --- logged variables (the <= 20 firmware channel slots) ---------------

    def logged_add(self, observable: int) -> int:
        """Put an observable on the first free slot; returns the slot."""
        logged = self.config.logged_slots
        for slot in logged:
            if self.config.channel_settings[slot].observable == observable:
                return slot  # already logged — no second slot burned
        free = next(
            (s for s in range(self.config.channels) if s not in logged), None
        )
        if free is None:
            raise CommandError(
                f"all {self.config.channels} channel slots are in use — "
                "log_remove one first"
            )
        self.select_observable(free, observable)  # also appends to the list
        return free

    def logged_remove(self, slot: int) -> None:
        if slot not in self.config.logged_slots:
            raise CommandError(f"CH{slot + 1} is not in the logged list")
        self.config.logged_slots.remove(slot)
        # The slot disappears from every plot cell (and the visible flag).
        self.set_slot_visible(slot, False)
        for win in self.config.plots:
            for cell in win.cells:
                if slot in cell:
                    cell.remove(slot)

    # --- logging ------------------------------------------------------------

    def start_log(self) -> Path:
        with self._log_mutex:
            if self.logger is not None:
                raise CommandError("already logging (log_stop first)")
            names = make_column_names(
                [
                    self.observable_name(ch.observable)
                    for ch in self.config.channel_settings
                ]
            )
            self.logger = CaptureLogger(
                self.config.logging.directory,
                self.config.logging.format,
                names,
                1.0 / self.sample_rate,
                every_n=self.config.logging.every_n,
            )
            return self.logger.path

    def stop_log(self) -> str:
        with self._log_mutex:
            logger, self.logger = self.logger, None
        if logger is None:
            raise CommandError("not logging")
        path = logger.close()
        self.last_log_path = path
        stats = logger.stats
        message = f"closed {path} ({stats.rows_written:,} rows)"
        if stats.chunks_dropped:
            message += (
                f" — WARNING: {stats.chunks_dropped} chunks "
                f"({stats.samples_dropped:,} samples) dropped; "
                "use bin format for guaranteed rate"
            )
        return message

    def _ext_log_edge(self, bit: bool) -> None:
        """Status bit 12 (reader thread): rising -> start log, falling -> stop."""
        if bit and not self._prev_ext_log and self.logger is None:
            try:
                path = self.start_log()
                self._events.append(("ok", f"external trigger: logging to {path}"))
            except Exception as exc:
                self._events.append(("error", f"external log start failed: {exc}"))
        elif not bit and self._prev_ext_log and self.logger is not None:
            try:
                self._events.append(("ok", f"external trigger: {self.stop_log()}"))
            except Exception as exc:
                self._events.append(("error", f"external log stop failed: {exc}"))
        self._prev_ext_log = bit

    # --- capture export / analysis handoff ----------------------------------

    def export_capture(self, path: str | Path | None = None) -> Path:
        capture = self.engine.capture if self.engine is not None else None
        if capture is None:
            raise CommandError("no trigger capture to export")
        from .capture_log import write_capture

        if path is None:
            directory = Path(self.config.logging.directory)
            directory.mkdir(parents=True, exist_ok=True)
            stamp = time.strftime("%Y-%m-%d_%H-%M-%S")
            ext = "csv" if self.config.logging.format == "csv" else "parquet"
            path = directory / f"Capture_{stamp}.{ext}"
        columns = make_column_names(
            [self.observable_name(ch.observable) for ch in self.config.channel_settings]
        )
        path = write_capture(
            path, columns, capture.data, capture.start_index, self.timestep_s
        )
        self.last_log_path = path
        return path

    def open_in_dataviewer(self, path: str | Path | None = None) -> str:
        path = Path(path) if path is not None else self.last_log_path
        if path is None:
            raise CommandError("no log file yet — log_stop or export_capture first")
        if not Path(path).is_file():
            raise CommandError(f"file not found: {path}")
        subprocess.Popen(
            [sys.executable, "-m", "uz_dataviewer", str(path)],
            start_new_session=True,
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL,
        )
        return f"opened {path} in uz_dataviewer"

    # --- per-frame housekeeping (UI thread) ---------------------------------

    def poll_events(self) -> None:
        while self._events:
            level, message = self._events.popleft()
            getattr(self.console, level, self.console.info)(message)
        for note in self.history.poll_notes():
            self.console.warn(note)
        self._poll_rate_detect()

    def start_rate_probe(self) -> None:
        """Manual `detect_rate`: measure now, without the settle delay."""
        self.detected_rate = None
        self._rate_probe = None
        self._rate_probe_manual = True

    def _poll_rate_detect(self) -> None:
        client = self.client
        if client is None or not client.connected.is_set():
            self._rate_probe = None
            return
        wanted = self._rate_probe_manual or (
            self.config.auto_detect_rate and self.detected_rate is None
        )
        if not wanted:
            return
        now = time.monotonic()
        if self._rate_probe is None:
            delay = 0.0 if self._rate_probe_manual else RATE_DETECT_DELAY_S
            if now - client.stats.connected_since >= delay:
                self._rate_probe = (now, client.stats.samples)
            return
        t0, samples0 = self._rate_probe
        if now - t0 < RATE_DETECT_WINDOW_S:
            return
        raw = (client.stats.samples - samples0) / (now - t0)
        self._rate_probe = None
        self._rate_probe_manual = False
        if raw <= 0:
            return
        nominal = 1e6 / self.config.timestep_usec
        if abs(raw - nominal) <= RATE_SNAP_FRACTION * nominal:
            rate = nominal
        else:
            rate = min(max(1.0, round(raw / 1000.0)) * 1000.0, RATE_MAX_HZ)
        self.detected_rate = rate
        if rate == nominal:
            self.console.info(
                f"sample rate confirmed: {rate:,.0f} Hz (measured {raw:,.0f} Hz)"
            )
        else:
            self.console.warn(
                f"detected sample rate {rate:,.0f} Hz differs from the configured "
                f"{nominal:,.0f} Hz (measured {raw:,.0f} Hz); the time axis now "
                "uses the detected rate — check timestep/geometry if unexpected"
            )

    def alive(self) -> bool:
        client = self.client
        return (
            client is not None
            and client.connected.is_set()
            and time.monotonic() - client.stats.last_rx_monotonic < 0.5
        )

    def shutdown(self) -> None:
        if self.logger is not None:
            try:
                self.console.info(self.stop_log())
            except Exception:
                pass
        self.disconnect()
        try:
            self.history.close(keep=self.config.history.keep_files)
        except Exception as exc:
            # Settings must be saved even if the history teardown fails.
            self.console.error(f"history close failed: {exc}")
        try:
            self.config.save(self.settings_path)
        except OSError as exc:
            self.console.error(f"could not save settings: {exc}")
