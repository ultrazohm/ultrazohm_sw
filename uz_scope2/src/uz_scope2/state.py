"""Single application state for uz_scope2.

Owns the config, the network client, the sample ring, the logger and the
console/command registry.  The reader thread only touches the ring, the
logger queue and a few GIL-atomic fields; everything UI-facing happens on the
main thread (``poll_events`` drains reader-thread notifications).
"""

from __future__ import annotations

import collections
import subprocess
import sys
import time
from dataclasses import dataclass
from pathlib import Path

from uz_dataviewer.console import Console

from .acquisition import AcquisitionEngine
from .capture_log import CaptureLogger, make_column_names
from .commands import CommandError, ScopeCommandRegistry
from .history import SessionHistory
from .segments import SegmentRegistry, SignalSegment, ZERO_OBSERVABLE
from .workspace import PlotWorkspace
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


class ScopeAppState:
    def __init__(
        self,
        config: ScopeConfig | None = None,
        header: HeaderConfig | None = None,
        settings_path: str | Path | None = None,
    ) -> None:
        self.settings_path = Path(settings_path) if settings_path else Path(SETTINGS_FILENAME)
        if config is None:
            config = (
                ScopeConfig.load(self.settings_path)
                if self.settings_path.is_file()
                else ScopeConfig()
            )
        self.config = config
        self.console = Console()
        self.commands = ScopeCommandRegistry()
        self.header = header if header is not None else self._load_header()

        self.client: ScopeClient | None = None
        self.detected_rate: float | None = None
        self.ring: ChannelRing = self._make_ring()
        self.history: SessionHistory = self._make_history()
        self.segments = SegmentRegistry(self.config.channels)
        self.workspace = PlotWorkspace()
        self.dragged_observable: int | None = None
        self.dragged_segment: int | None = None
        self.last_plot_ranges: dict[tuple[int, int], tuple[float, float]] = {}
        self.lifecheck = Lifecheck()
        self.logger: CaptureLogger | None = None
        self.engine: AcquisitionEngine | None = None
        self.slowdata = SlowDataStore(self.header.slowdata if self.header else [])

        self.frozen = False
        self.fix_axis = False
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
        self.segments = SegmentRegistry(self.config.channels)

    def rebuild_ring(self) -> None:
        # The ring's absolute sample clock restarts, so the history (which is
        # anchored to it) must restart too.
        self.history.close(keep=self.config.history.keep_files)
        self.ring = self._make_ring()
        self.history = self._make_history()
        self.segments = SegmentRegistry(self.config.channels)
        self.lifecheck.reset()

    def set_geometry(self, channels: int, samples_per_packet: int) -> None:
        if self.client is not None:
            raise CommandError("disconnect before changing the frame geometry")
        if self.logger is not None:
            raise CommandError("stop logging before changing the frame geometry")
        self.config.channels = channels
        self.config.samples_per_packet = samples_per_packet
        self.config.ensure_channel_count()
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

    def connect(self) -> None:
        if self.client is not None:
            raise CommandError("already connected (disconnect first)")
        self.client = ScopeClient(
            self.config.geometry,
            self.config.ip,
            self.config.port,
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
        previous = {seg.slot: seg.id for seg in self.segments.active()}
        self.segments.close_all(self.ring.total_written)
        replacements = {}
        for slot, ch in enumerate(self.config.channel_settings):
            if ch.observable != ZERO_OBSERVABLE:
                new_segment = self.segments.start(slot, ch.observable, self.observable_name(ch.observable), self.ring.total_written, scale=ch.scale, offset=ch.offset, color=ch.color)
                if slot in previous and new_segment is not None:
                    replacements[previous[slot]] = new_segment.id
        self.workspace.replace_segments(replacements)
        # Full channel-select burst so device and config agree (JavaScope does
        # the same). With pacing on these ride the first ack slots.
        for slot, ch in enumerate(self.config.channel_settings):
            client.send_command(encode_channel_select(slot, ch.observable))
            self._trace(201 + slot, float(ch.observable), f"select CH{slot + 1}")
        self.lifecheck.reset()
        self._rate_probe = None
        self._events.append(("ok", f"connected to {client.ip}:{client.port}"))

    def _on_disconnect(self, client: ScopeClient, reason: str) -> None:
        self.segments.close_all(self.ring.total_written)
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
            logger.submit(block[self._logger_slots], start_index)

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
        if self.logger is not None:
            raise CommandError("stop logging before changing acquired signals")
        ch = self.config.channel_settings[slot]
        ch.observable = observable
        self.segments.start(slot, observable, self.observable_name(observable), self.ring.total_written, scale=ch.scale, offset=ch.offset, color=ch.color)
        self.history.note_epoch(slot, self.ring.total_written)
        self._refresh_lifecheck_slot()
        if self.client is not None:
            self.client.send_command(encode_channel_select(slot, observable))
            self._trace(201 + slot, float(observable), f"select CH{slot + 1}")

    def acquire_observable(self, observable: int) -> SignalSegment:
        if observable == ZERO_OBSERVABLE:
            raise CommandError("JSO_ZEROVALUE cannot be acquired")
        if any(ch.observable == observable for ch in self.config.channel_settings):
            raise CommandError(f"{self.observable_name(observable)} is already acquired")
        slot = next((i for i, ch in enumerate(self.config.channel_settings) if ch.observable == ZERO_OBSERVABLE), None)
        if slot is None:
            raise CommandError(f"all {self.config.channels} acquisition slots are in use")
        self.config.channel_settings[slot].visible = True
        self.select_observable(slot, observable)
        segment = self.segments.active_for_slot(slot)
        assert segment is not None
        return segment

    def release_signal(self, segment_id: int) -> int:
        segment = self.segments.get(segment_id)
        if segment is None or not segment.active:
            raise CommandError(f"signal_{segment_id} is not actively acquired")
        slot = segment.slot
        self.select_observable(slot, ZERO_OBSERVABLE)
        self.config.channel_settings[slot].visible = False
        return slot

    def retained_segments(self) -> list[SignalSegment]:
        retained = self.segments.retained(self.ring)
        self.workspace.prune_segments({seg.id for seg in retained})
        return retained

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
            column_names=tuple(self.observable_name(ch.observable) for ch in self.config.channel_settings),
        )
        self.engine.arm()
        cfg.enabled = True

    def disarm_trigger(self) -> None:
        self.engine = None
        self.config.trigger.enabled = False

    def rearm_if_armed(self) -> None:
        if self.config.trigger.enabled:
            self.arm_trigger()

    # --- logging ------------------------------------------------------------

    def start_log(self) -> Path:
        if self.logger is not None:
            raise CommandError("already logging (log_stop first)")
        self._logger_slots = [i for i, ch in enumerate(self.config.channel_settings) if ch.observable != ZERO_OBSERVABLE]
        if not self._logger_slots:
            # Preserve legacy JavaScope behavior for an empty acquisition list.
            self._logger_slots = list(range(self.config.channels))
            self._events.append(("warn", "no acquired signals; logging all hardware slots"))
        names = make_column_names([self.observable_name(self.config.channel_settings[i].observable) for i in self._logger_slots])
        self.logger = CaptureLogger(
            self.config.logging.directory,
            self.config.logging.format,
            names,
            1.0 / self.sample_rate,
            every_n=self.config.logging.every_n,
        )
        return self.logger.path

    def stop_log(self) -> str:
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
        columns = make_column_names(list(capture.column_names) if capture.column_names else [self.observable_name(ch.observable) for ch in self.config.channel_settings])
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
        self.retained_segments()
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
        self.history.close(keep=self.config.history.keep_files)
        try:
            self.config.save(self.settings_path)
        except OSError as exc:
            self.console.error(f"could not save settings: {exc}")
