"""Thread-safe message buffer backing the bottom console panel."""

from __future__ import annotations

import threading
import time
from dataclasses import dataclass, field
from enum import IntEnum


class LogLevel(IntEnum):
    DEBUG = 0
    INFO = 1
    WARNING = 2
    ERROR = 3


LEVEL_NAMES = {
    LogLevel.DEBUG: "DEBUG",
    LogLevel.INFO: "INFO",
    LogLevel.WARNING: "WARN",
    LogLevel.ERROR: "ERROR",
}


@dataclass
class LogEntry:
    level: LogLevel
    message: str
    timestamp: float = field(default_factory=time.time)

    def format(self) -> str:
        clock = time.strftime("%H:%M:%S", time.localtime(self.timestamp))
        return f"[{clock}] [{LEVEL_NAMES[self.level]:5s}] {self.message}"


class Console:
    """Bounded, thread-safe log buffer. Loader threads write, the UI reads."""

    def __init__(self, max_entries: int = 5000):
        self._lock = threading.Lock()
        self._entries: list[LogEntry] = []
        self._max_entries = max_entries
        self._revision = 0

    def log(self, level: LogLevel, message: str) -> None:
        with self._lock:
            self._entries.append(LogEntry(level, message))
            if len(self._entries) > self._max_entries:
                del self._entries[: len(self._entries) - self._max_entries]
            self._revision += 1

    def debug(self, message: str) -> None:
        self.log(LogLevel.DEBUG, message)

    def info(self, message: str) -> None:
        self.log(LogLevel.INFO, message)

    def warning(self, message: str) -> None:
        self.log(LogLevel.WARNING, message)

    def error(self, message: str) -> None:
        self.log(LogLevel.ERROR, message)

    def entries(self, min_level: LogLevel = LogLevel.DEBUG) -> list[LogEntry]:
        with self._lock:
            return [e for e in self._entries if e.level >= min_level]

    @property
    def revision(self) -> int:
        with self._lock:
            return self._revision

    def clear(self) -> None:
        with self._lock:
            self._entries.clear()
            self._revision += 1
