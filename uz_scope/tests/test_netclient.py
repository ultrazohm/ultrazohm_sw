from __future__ import annotations

import socket
import struct
import subprocess
import sys
import threading
import time

import numpy as np
import pytest

from uz_scope.netclient import ClientCallbacks, ScopeClient
from uz_scope.protocol import (
    FrameGeometry,
    decode_command,
    encode_channel_select,
    encode_command,
)

GEOM = FrameGeometry(channels=2, samples_per_packet=3)


def make_frame(status: int, first_sample: int) -> bytes:
    n, c = GEOM.samples_per_packet, GEOM.channels
    buf = struct.pack("<I", status)
    buf += struct.pack(f"<{n}I", *range(n))
    for ch in range(c):
        buf += struct.pack(
            f"<{n}f", *[float(first_sample + ch * 1000 + s) for s in range(n)]
        )
    buf += struct.pack(f"<{n}f", *[0.0] * n)
    return buf


class DummyServer(threading.Thread):
    """Minimal frame source; optionally lock-step (recv one command per frame)."""

    def __init__(self, frames: int, lock_step: bool):
        super().__init__(daemon=True)
        self.frames = frames
        self.lock_step = lock_step
        self.received: list[bytes] = []
        self.listener = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.listener.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.listener.bind(("127.0.0.1", 0))
        self.listener.listen(1)
        self.port = self.listener.getsockname()[1]

    def run(self) -> None:
        conn, _ = self.listener.accept()
        conn.settimeout(5.0)
        try:
            for i in range(self.frames):
                conn.sendall(make_frame(status=i, first_sample=i * 10))
                if self.lock_step:
                    data = conn.recv(8)
                    if not data:
                        return
                    self.received.append(data)
        except OSError:
            pass
        finally:
            try:
                conn.shutdown(socket.SHUT_RDWR)
            except OSError:
                pass
            conn.close()
            self.listener.close()


def collect_client(server: DummyServer, ack_pacing: bool):
    frames = []
    done = threading.Event()

    def on_frames(parsed):
        frames.append(
            (parsed.status.copy(), parsed.samples.copy())
        )
        if sum(s.shape[0] for s, _ in frames) >= server.frames:
            done.set()

    client = ScopeClient(
        GEOM,
        "127.0.0.1",
        server.port,
        ack_pacing=ack_pacing,
        callbacks=ClientCallbacks(on_frames=on_frames),
        reconnect=False,
    )
    return client, frames, done


def test_receives_all_frames_in_order_no_pacing():
    server = DummyServer(frames=50, lock_step=False)
    server.start()
    client, frames, done = collect_client(server, ack_pacing=False)
    client.start()
    assert done.wait(5.0), "did not receive all frames"
    client.stop()
    server.join(5.0)

    statuses = np.concatenate([s for s, _ in frames])
    assert statuses.tolist() == list(range(50))
    first_samples = np.concatenate([smp[:, 0, 0] for _, smp in frames])
    np.testing.assert_array_equal(first_samples, np.arange(50) * 10)
    assert client.stats.frames == 50
    assert client.stats.bytes_received == 50 * GEOM.frame_bytes


def test_lock_step_pacing_and_command_delivery():
    server = DummyServer(frames=30, lock_step=True)
    server.start()
    client, frames, done = collect_client(server, ack_pacing=True)
    client.start()
    assert client.connected.wait(5.0)
    client.send_command(encode_command(25, 1.0))  # rides the next ack slot
    assert done.wait(5.0), "lock-step exchange stalled"
    client.stop()
    server.join(5.0)

    # One 8-byte command per frame (the last frame needs no ack for the
    # exchange to complete, so allow off-by-one).
    assert len(server.received) >= 29
    decoded = [decode_command(d) for d in server.received]
    assert (25, 1.0) in decoded
    assert all(cmd == (0, 0.0) for cmd in decoded if cmd != (25, 1.0))
    assert client.stats.commands_sent >= 1


def test_consumer_exception_surfaces_as_disconnect():
    server = DummyServer(frames=50, lock_step=False)
    server.start()
    reasons = []
    done = threading.Event()

    def bad_consumer(parsed):
        raise RuntimeError("boom")

    def on_disconnect(client, reason):
        reasons.append(reason)
        done.set()

    client = ScopeClient(
        GEOM,
        "127.0.0.1",
        server.port,
        ack_pacing=False,
        callbacks=ClientCallbacks(on_frames=bad_consumer, on_disconnect=on_disconnect),
        reconnect=False,
    )
    client.start()
    assert done.wait(5.0), "consumer failure never surfaced"
    client.stop()
    server.join(5.0)
    assert any("boom" in r for r in reasons)


def test_send_command_rejects_wrong_size():
    client = ScopeClient(GEOM, "127.0.0.1", 1, reconnect=False)
    with pytest.raises(ValueError):
        client.send_command(b"\x00" * 7)


def test_send_command_without_connection_raises():
    client = ScopeClient(GEOM, "127.0.0.1", 1, ack_pacing=False, reconnect=False)
    with pytest.raises(ConnectionError):
        client.send_command(b"\x00" * 8)


@pytest.mark.integration
def test_against_javascope_test_server(repo_root, tmp_path):
    """Full-stack run against the repo's lock-step test server."""
    with socket.socket() as probe:
        probe.bind(("127.0.0.1", 0))
        port = probe.getsockname()[1]

    proc = subprocess.Popen(
        [sys.executable, str(repo_root / "javascope/test_server.py"), "--port", str(port)],
        cwd=repo_root / "javascope",
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
    )
    geom = FrameGeometry(20, 15)  # test_server defaults
    statuses: list[int] = []
    ch4: list[np.ndarray] = []

    def on_frames(parsed):
        statuses.extend(int(s) for s in parsed.status)
        ch4.append(parsed.samples[:, 4, :].copy())

    client = ScopeClient(
        geom,
        "127.0.0.1",
        port,
        ack_pacing=True,
        callbacks=ClientCallbacks(on_frames=on_frames),
        reconnect=True,  # retries until the subprocess is listening
    )
    try:
        client.start()
        assert client.connected.wait(15.0), "test_server never accepted"

        deadline = time.monotonic() + 15.0
        while client.stats.frames < 20 and time.monotonic() < deadline:
            time.sleep(0.05)
        assert client.stats.frames >= 20, "no sustained frame flow"

        # My_Button_2 (id 25) sets the User LED -> status bit 3.
        client.send_command(encode_command(25, 1.0))
        deadline = time.monotonic() + 10.0
        while time.monotonic() < deadline:
            if statuses and statuses[-1] & (1 << 3):
                break
            time.sleep(0.05)
        assert statuses[-1] & (1 << 3), "User LED bit never appeared in status"

        # Select observable 0 (zero source) for channel slot 4 -> zeros on ch 4.
        client.send_command(encode_channel_select(4, 0))
        deadline = time.monotonic() + 10.0
        zeroed = False
        while time.monotonic() < deadline and not zeroed:
            time.sleep(0.1)
            if ch4 and np.all(ch4[-1] == 0.0):
                zeroed = True
        assert zeroed, "channel select had no effect"
    finally:
        client.stop()
        proc.terminate()
        proc.wait(5.0)
