"""Persistent settings for uz_scope: JSON schema + legacy ``properties.ini`` import.

Everything the app needs to reconnect and reproduce a session lives in one
``ScopeConfig``.  Frame geometry (channels, samples/packet) and the sample
timestep are configuration, not wire data — the protocol is headerless, so
these must match the firmware build.
"""

from __future__ import annotations

import dataclasses
import json
from dataclasses import dataclass, field
from pathlib import Path

from .javascope_header import DEFAULT_HEADER_RELPATH
from .protocol import FrameGeometry

SETTINGS_FILENAME = "uz_scope_settings.json"

LOG_FORMATS = ("parquet", "csv", "bin")
TRIGGER_EDGES = ("rising", "falling")
TRIGGER_MODES = ("auto", "normal", "single")


@dataclass
class ChannelSettings:
    observable: int = 0     # index into the JS_OberservableData enum
    visible: bool = False
    scale: float = 1.0
    offset: float = 0.0
    color: str | None = None  # '#RRGGBB' or None for auto palette


@dataclass
class TriggerSettings:
    channel: int = 0        # scope channel slot, 1-based; 0 = auto (first visible)
    edge: str = "rising"
    level: float = 0.0
    pretrigger: float = 0.5  # fraction of the capture window before the trigger
    mode: str = "auto"
    enabled: bool = False


@dataclass
class LoggingSettings:
    directory: str = "logs"
    format: str = "parquet"  # one of LOG_FORMATS
    every_n: int = 1         # log every N-th sample
    fast: bool = True        # log fast (per-ISR) channel data
    slow: bool = True        # log slowdata to the companion file
    ext_trigger: bool = False  # arm logging on status bit 12


HISTORY_MODES = ("off", "ram", "disk")

X_MODE_CONT = "cont"  # plot x-mode: full session, axis grows from t=0
MAX_PLOT_GRID = 4     # rows/cols clamp per plot window


@dataclass
class PlotWindowSettings:
    """One plot window: a rows x cols grid of cells, each a list of slots."""

    title: str = ""
    rows: int = 1
    cols: int = 1
    link_x: bool = False
    x_mode: str = "0.5"  # visible seconds as string, or X_MODE_CONT
    cells: list[list[int]] = field(default_factory=list)

    def window_seconds(self) -> float | None:
        """Preset seconds, or None for the cont (full-session) mode."""
        if self.x_mode == X_MODE_CONT:
            return None
        try:
            return max(float(self.x_mode), 1e-6)
        except ValueError:
            return 0.5

    def ensure_cells(self, channels: int) -> None:
        """Clamp the grid and reflow cells (extras merge into the last)."""
        self.rows = min(max(int(self.rows), 1), MAX_PLOT_GRID)
        self.cols = min(max(int(self.cols), 1), MAX_PLOT_GRID)
        n = self.rows * self.cols
        while len(self.cells) < n:
            self.cells.append([])
        if len(self.cells) > n:
            extra = [s for cell in self.cells[n:] for s in cell]
            del self.cells[n:]
            for s in extra:
                if s not in self.cells[-1]:
                    self.cells[-1].append(s)
        for i, cell in enumerate(self.cells):
            seen: list[int] = []
            for s in cell:
                s = int(s)
                if 0 <= s < channels and s not in seen:
                    seen.append(s)
            self.cells[i] = seen


@dataclass
class HistorySettings:
    mode: str = "ram"        # one of HISTORY_MODES
    directory: str = "history"  # disk-mode spill directory
    max_ram_bytes: int = 256 * 1024 * 1024  # envelope pyramid cap
    keep_files: bool = False  # keep the disk spill after exit
    base: int = 64           # finest envelope bucket (auto-scaled up at init)


WIDGET_KINDS = (
    "readout", "gauge", "progress", "led",
    "button", "toggle", "slider_send", "knob_send", "input_send",
)
BINDING_TYPES = ("slowdata", "send_field", "my_button", "sys_button", "status_bit")


@dataclass
class DashboardWidget:
    id: int = 0
    kind: str = "readout"          # one of WIDGET_KINDS
    binding_type: str = "slowdata"  # one of BINDING_TYPES
    binding_key: str = ""  # slowdata name / field "1..20" / button name / bit
    x: float = 20.0
    y: float = 20.0
    w: float = 170.0
    h: float = 84.0
    vmin: float = 0.0
    vmax: float = 1.0
    label: str = ""
    fmt: str = "%.4g"
    indicator_bit: int = -1  # status bit shown as LED (-1 = auto/none)


@dataclass
class DashboardSettings:
    next_id: int = 1
    widgets: list[DashboardWidget] = field(default_factory=list)


@dataclass
class ScopeConfig:
    version: int = 1
    # connection
    ip: str = "192.168.1.233"
    port: int = 1000
    auto_connect: bool = False
    ack_pacing: bool = True  # send one 8-byte (zero-)ack per received frame
    # frame geometry / timing (must match the firmware build)
    channels: int = 20
    samples_per_packet: int = 15
    timestep_usec: float = 100.0
    auto_detect_rate: bool = True
    header_path: str = DEFAULT_HEADER_RELPATH
    # acquisition / display
    ring_seconds: float = 10.0
    max_ring_bytes: int = 512 * 1024 * 1024
    refresh_hz: float = 30.0
    window_seconds: float = 0.5
    # sub-configs
    channel_settings: list[ChannelSettings] = field(default_factory=list)
    trigger: TriggerSettings = field(default_factory=TriggerSettings)
    logging: LoggingSettings = field(default_factory=LoggingSettings)
    history: HistorySettings = field(default_factory=HistorySettings)
    plots: list[PlotWindowSettings] = field(default_factory=list)
    # Ordered slots currently in the "Logged variables" list (<= channels).
    logged_slots: list[int] = field(default_factory=list)
    dashboard: DashboardSettings = field(default_factory=DashboardSettings)

    def __post_init__(self) -> None:
        self.ensure_channel_count()
        self.ensure_plots()
        self.ensure_logged()

    @property
    def geometry(self) -> FrameGeometry:
        return FrameGeometry(self.channels, self.samples_per_packet)

    def ensure_channel_count(self) -> None:
        """Resize ``channel_settings`` to ``channels`` entries (pad/truncate)."""
        current = len(self.channel_settings)
        if current < self.channels:
            self.channel_settings.extend(
                ChannelSettings() for _ in range(self.channels - current)
            )
        elif current > self.channels:
            del self.channel_settings[self.channels :]

    def ensure_plots(self) -> None:
        """Guarantee at least plot window 1 and normalize every grid.

        Without a ``plots`` section (fresh install or pre-v2 settings) window
        1 is synthesized from the legacy display state: its first cell shows
        the slots marked ``visible`` and its timebase is ``window_seconds``.
        """
        if not self.plots:
            first = PlotWindowSettings(x_mode=f"{self.window_seconds:g}")
            first.cells = [
                [s for s, ch in enumerate(self.channel_settings) if ch.visible]
            ]
            self.plots.append(first)
        for i, win in enumerate(self.plots):
            if not win.title:
                win.title = "Scope" if i == 0 else f"Scope {i + 1}"
            win.ensure_cells(self.channels)

    def ensure_logged(self) -> None:
        """Normalize ``logged_slots`` (dedupe, clip to the slot pool) and
        keep the invariant that every slot shown in a plot cell is logged."""
        seen: list[int] = []
        for s in self.logged_slots:
            s = int(s)
            if 0 <= s < self.channels and s not in seen:
                seen.append(s)
        for win in self.plots:
            for cell in win.cells:
                for s in cell:
                    if s not in seen:
                        seen.append(s)
        self.logged_slots = seen

    def migrate_logged_slots(self) -> None:
        """Pre-v2 settings: the logged list is every slot that was in use
        (an observable assigned or shown in the plot)."""
        self.logged_slots = [
            s
            for s, ch in enumerate(self.channel_settings)
            if ch.observable != 0 or ch.visible
        ]

    # --- JSON persistence -------------------------------------------------

    def to_json(self) -> str:
        return json.dumps(dataclasses.asdict(self), indent=2)

    def save(self, path: str | Path) -> None:
        Path(path).write_text(self.to_json() + "\n", encoding="utf-8")

    @classmethod
    def from_dict(cls, data: dict) -> "ScopeConfig":
        """Build from a dict, ignoring unknown keys (forward compatibility)."""
        cfg = cls()
        _apply_known_fields(
            cfg,
            data,
            skip=(
                "channel_settings", "trigger", "logging", "history", "plots",
                "dashboard",
            ),
        )
        if isinstance(data.get("dashboard"), dict):
            dash = data["dashboard"]
            _apply_known_fields(cfg.dashboard, dash, skip=("widgets",))
            if isinstance(dash.get("widgets"), list):
                for entry in dash["widgets"]:
                    w = DashboardWidget()
                    if isinstance(entry, dict):
                        _apply_known_fields(w, entry)
                    if w.kind in WIDGET_KINDS and w.binding_type in BINDING_TYPES:
                        cfg.dashboard.widgets.append(w)
        if isinstance(data.get("trigger"), dict):
            _apply_known_fields(cfg.trigger, data["trigger"])
        if isinstance(data.get("logging"), dict):
            _apply_known_fields(cfg.logging, data["logging"])
        if isinstance(data.get("history"), dict):
            _apply_known_fields(cfg.history, data["history"])
            if cfg.history.mode not in HISTORY_MODES:
                cfg.history.mode = "ram"
        if isinstance(data.get("channel_settings"), list):
            cfg.channel_settings = []
            for entry in data["channel_settings"]:
                ch = ChannelSettings()
                if isinstance(entry, dict):
                    _apply_known_fields(ch, entry)
                cfg.channel_settings.append(ch)
        cfg.ensure_channel_count()
        if isinstance(data.get("plots"), list):
            cfg.plots = []
            for entry in data["plots"]:
                win = PlotWindowSettings()
                if isinstance(entry, dict):
                    _apply_known_fields(win, entry, skip=("cells",))
                    if isinstance(entry.get("cells"), list):
                        win.cells = [
                            _int_list(cell)
                            for cell in entry["cells"]
                            if isinstance(cell, list)
                        ]
                cfg.plots.append(win)
        else:
            cfg.plots = []  # migrate from the legacy visible flags
        cfg.ensure_plots()
        if isinstance(data.get("logged_slots"), list):
            cfg.logged_slots = _int_list(data["logged_slots"])
        else:
            cfg.migrate_logged_slots()
        cfg.ensure_logged()
        return cfg

    @classmethod
    def load(cls, path: str | Path) -> "ScopeConfig":
        data = json.loads(Path(path).read_text(encoding="utf-8"))
        if not isinstance(data, dict):
            raise ValueError(f"{path}: settings root must be a JSON object")
        return cls.from_dict(data)


def _apply_known_fields(obj, data: dict, skip: tuple[str, ...] = ()) -> None:
    """Copy matching keys with type coercion; malformed values are skipped
    (a hand-edited settings file must not abort startup)."""
    for f in dataclasses.fields(obj):
        if f.name in skip or f.name not in data:
            continue
        value = data[f.name]
        current = getattr(obj, f.name)
        try:
            if isinstance(current, bool):
                if isinstance(value, str):
                    value = value.strip().lower() in ("1", "true", "on", "yes")
                else:
                    value = bool(value)
            elif isinstance(current, int) and not isinstance(value, bool):
                value = int(value)
            elif isinstance(current, float):
                value = float(value)
        except (TypeError, ValueError):
            continue
        setattr(obj, f.name, value)


def _int_list(seq) -> list[int]:
    """Best-effort int list (malformed entries dropped)."""
    out: list[int] = []
    for item in seq:
        try:
            out.append(int(item))
        except (TypeError, ValueError):
            continue
    return out


# --- legacy properties.ini import ----------------------------------------


@dataclass
class ImportReport:
    source: str
    applied: dict[str, str] = field(default_factory=dict)
    ignored: list[str] = field(default_factory=list)
    errors: list[str] = field(default_factory=list)


def _parse_properties(text: str) -> dict[str, str]:
    values: dict[str, str] = {}
    for raw in text.splitlines():
        line = raw.strip()
        if not line or line.startswith(("#", "!")):
            continue
        if "=" not in line:
            continue
        key, _, value = line.partition("=")
        values[key.strip()] = value.strip()
    return values


def _parse_list(value: str) -> list[str]:
    return [item.strip() for item in value.split(";")]


def _parse_bool(value: str) -> bool:
    return value.strip().lower() in ("1", "true", "on", "yes")


def import_properties(path: str | Path, cfg: ScopeConfig) -> ImportReport:
    """Apply a legacy JavaScope ``properties.ini`` onto ``cfg`` (in place)."""
    path = Path(path)
    props = _parse_properties(path.read_text(encoding="utf-8", errors="replace"))
    report = ImportReport(source=str(path))

    def applied(key: str, note: str = "") -> None:
        report.applied[key] = note or props[key]

    for key, value in props.items():
        try:
            if key == "ipAdress":
                cfg.ip = value
                applied(key)
            elif key == "MEASUREMENTS_PER_TCP_PACKET":
                cfg.samples_per_packet = int(value)
                applied(key)
            elif key == "scopeChannelNumber":
                cfg.channels = int(value)
                cfg.ensure_channel_count()
                applied(key)
            elif key == "smallestTimeStepUSEC":
                cfg.timestep_usec = float(value)
                applied(key)
            elif key == "autoDetectSamplingRate":
                cfg.auto_detect_rate = _parse_bool(value)
                applied(key)
            elif key == "triggerChannel":
                cfg.trigger.channel = int(value)
                applied(key)
            elif key == "triggerEdge":
                low = value.lower()
                if low in ("falling", "2"):
                    cfg.trigger.edge = "falling"
                else:
                    cfg.trigger.edge = "rising"
                applied(key, cfg.trigger.edge)
            elif key == "triggerValue":
                cfg.trigger.level = float(value)
                applied(key)
            elif key == "pretrigger":
                cfg.trigger.pretrigger = min(1.0, max(0.0, float(value)))
                applied(key, str(cfg.trigger.pretrigger))
            elif key == "sendZeroAckCommand":
                cfg.ack_pacing = _parse_bool(value)
                applied(key, f"ack_pacing={cfg.ack_pacing}")
            elif key == "initScaleCHx":
                for ch, item in zip(cfg.channel_settings, _parse_list(value)):
                    ch.scale = float(item)
                applied(key)
            elif key == "initOffsetCHx":
                for ch, item in zip(cfg.channel_settings, _parse_list(value)):
                    ch.offset = float(item)
                applied(key)
            elif key == "preSelectedChannelNumbers":
                for ch, item in zip(cfg.channel_settings, _parse_list(value)):
                    ch.observable = int(item)
                applied(key)
            elif key == "preSelectedChannelVisibility":
                for ch, item in zip(cfg.channel_settings, _parse_list(value)):
                    ch.visible = _parse_bool(item)
                applied(key)
            else:
                # ParameterID, ScopeDevTab, and anything unknown.
                report.ignored.append(key)
        except (ValueError, TypeError) as exc:
            report.errors.append(f"{key}: {exc}")
    return report
