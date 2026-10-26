"""Named API v1; all device IO and logging execute in Rust."""
import json
from io import BytesIO
from ._native import request as _request, live_data as _live_data, Acquisition as _Acquisition


class Acquisition(_Acquisition):
    """Own an embedded acquisition; close it before reading finalized recordings."""

    def read_recording(self, stream="fast", recording=1):
        """Return a completed recording as a Polars DataFrame after close()."""
        import polars as pl
        return pl.read_parquet(self.recording_path(stream, recording))

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
    def start_logging_slow_data(self): return self._call("start_logging_slow_data")
    def stop_logging_slow_data(self): return self._call("stop_logging_slow_data")
    def observables(self):
        """Return all channel assignments requested in this session; no device readback."""
        return self._call("observables")
    def get_live_data(self, last_n_samples):
        """Return an independent Polars snapshot of the last N retained fast samples."""
        import polars as pl
        if isinstance(last_n_samples, bool) or not isinstance(last_n_samples, int) or last_n_samples <= 0:
            raise ValueError("last_n_samples must be a positive integer")
        return pl.read_ipc_stream(BytesIO(_live_data(self.endpoint, last_n_samples)))
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

__all__ = ["Client", "Acquisition"]
