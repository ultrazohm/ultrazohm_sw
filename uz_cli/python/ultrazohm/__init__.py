"""Named API v1; all device IO and logging execute in Rust."""
import json
from dataclasses import dataclass
from io import BytesIO
from ._native import (request as _request, Acquisition as _Acquisition,
                      data_query as _data_query, recording_info as _recording_info,
                      recording_data as _recording_data)


def _position(value, name, *, positive=False):
    if isinstance(value, bool) or not isinstance(value, int) or value < (1 if positive else 0):
        raise ValueError(f"{name} must be a {'positive' if positive else 'non-negative'} integer")
    return value


def _source(stream, recording):
    if stream not in ("fast", "slow"):
        raise ValueError("stream must be fast or slow")
    if recording is not None:
        _position(recording, "recording", positive=True)
    return {"stream": stream, "recording": recording}


@dataclass(frozen=True)
class DataPage:
    """Rows and an opaque cursor describing the next unread sample."""
    data: object
    cursor: dict
    start: int
    stop: int
    info: dict


class Recording:
    """A durable backend handle; usable without a running acquisition service.

    Live pending samples are accessed through Client. This handle reads published
    batches. Slow recordings expose raw updates; legacy exports are wide tables.
    """
    def __init__(self, path):
        from pathlib import Path
        self.path = str(Path(path).resolve())
        self.info()  # Validate backend/version at open.

    def info(self):
        return json.loads(_recording_info(self.path))

    def read_range(self, start, stop, *, channels=None):
        import polars as pl
        _position(start, "start")
        _position(stop, "stop")
        return pl.read_ipc_stream(BytesIO(_recording_data(self.path, start, stop, channels)))

    def iter_batches(self, batch_samples=10_000, *, channels=None):
        _position(batch_samples, "batch_samples", positive=True)
        info = self.info()
        start, stop = info["start"] or 0, info["stop"] or 0
        for first in range(start, stop, batch_samples):
            yield self.read_range(first, min(first + batch_samples, stop), channels=channels)

    def read(self, *, channels=None):
        import polars as pl
        batches = list(self.iter_batches(channels=channels))
        return pl.concat(batches) if batches else self.read_range(0, 0, channels=channels)


class Acquisition(_Acquisition):
    """Own an embedded acquisition; close it before reading finalized recordings."""

    def read_recording(self, stream="fast", recording=1):
        """Return a completed recording as a Polars DataFrame after close()."""
        return self.recording(stream, recording).read()

    def recording(self, stream="fast", recording=1):
        """Get this acquisition's durable recording handle without repeating a path."""
        _source(stream, recording)
        return Recording(self.recording_handle_path(stream, recording))

class Client:
    """Control an existing external or embedded acquisition service."""
    def __init__(self, endpoint="127.0.0.1:19740"):
        self.endpoint = endpoint

    def _call(self, op, **fields):
        return json.loads(_request(self.endpoint, json.dumps({"op": op, **fields}, allow_nan=False)))

    def connect(self, ip="192.168.1.233", port=1000):
        """Connect an offline service and apply its initial observables."""
        return self._call("connect", ip=ip, port=port)

    def start_logging(self): return self._call("start_logging")
    def stop_logging(self): return self._call("stop_logging")
    def pause_logging(self):
        """Suspend fast recording; keep acquisition/RAM and the recording open."""
        return self._call("pause_logging")
    def resume_logging(self):
        """Resume the same fast recording; timestamps retain the pause gap."""
        return self._call("resume_logging")
    def start_logging_slow_data(self): return self._call("start_logging_slow_data")
    def stop_logging_slow_data(self): return self._call("stop_logging_slow_data")
    def pause_logging_slow_data(self): return self._call("pause_logging_slow_data")
    def resume_logging_slow_data(self): return self._call("resume_logging_slow_data")
    def observables(self):
        """Return all channel assignments requested in this session; no device readback."""
        return self._call("observables")
    def catalog(self):
        """Return the service's firmware mapping and runtime profile, not device readback."""
        return self._call("catalog")
    def recordings(self):
        return self._call("recordings")["recordings"]

    def data_info(self, *, stream="fast", recording=None):
        """Available sample positions; stop is exclusive. See position_basis for live vs recorded rows."""
        return self._call("data_info", source=_source(stream, recording))["info"]

    def _read(self, selection, *, stream, recording, channels):
        import polars as pl
        command = {"op": "read_data", "query": {"source": _source(stream, recording),
                   "selection": selection, "channels": channels}}
        header, payload = _data_query(self.endpoint, json.dumps(command, allow_nan=False))
        metadata = json.loads(header)
        return DataPage(pl.read_ipc_stream(BytesIO(payload)), metadata["cursor"],
                        metadata["start"], metadata["stop"], metadata["info"])

    def tail(self, n, *, stream="fast", recording=None, channels=None):
        _position(n, "n", positive=True)
        return self._read({"kind": "tail", "count": n}, stream=stream,
                          recording=recording, channels=channels).data

    def read_range(self, start, stop, *, stream="fast", recording=None, channels=None):
        _position(start, "start")
        _position(stop, "stop")
        return self._read({"kind": "range", "start": start, "stop": stop}, stream=stream,
                          recording=recording, channels=channels).data

    def read_since(self, cursor=None, *, limit=10_000, stream=None, recording=None, channels=None):
        """Read a bounded page. Reuse page.cursor to resume without overlap.

        With no cursor, starts at the earliest currently available sample. Expired
        RAM cursors and cursors from another run or signal mapping raise an error.
        """
        _position(limit, "limit", positive=True)
        if cursor is not None:
            if not isinstance(cursor, dict):
                raise ValueError("cursor must be the dict returned by read_since")
            stream = stream or cursor.get("stream")
            if recording is None:
                recording = cursor.get("recording")
        return self._read({"kind": "since", "cursor": cursor, "limit": limit},
                          stream=stream or "fast", recording=recording, channels=channels)
    def status(self):
        """Return service status; state.platform_state is the mapped name or None."""
        return self._call("status")
    def stop(self): return self._call("stop")
    def enable_system(self): return self._call("enable_system")
    def enable_control(self): return self._call("enable_control")
    def error_reset(self): return self._call("error_reset")
    def set_variable(self, name, value): return self._call("set_variable", name=name, value=value)
    def set_observable(self, name, channel): return self._call("set_observable", name=name, channel=channel)
    def button(self, number): return self._call("button", number=number)
    def send_ack(self, enabled):
        if not isinstance(enabled, bool):
            raise TypeError("enabled must be bool")
        return self._call("send_ack", enabled=enabled)
    def shutdown(self): return self._call("shutdown")

__all__ = ["Client", "Acquisition", "Recording", "DataPage"]
