"""TCP client for the JavaScope stream — the ingest hot path (GUI-free).

One reader thread owns the socket: it ``recv_into``s a preallocated buffer
(releases the GIL), parses every complete frame in one vectorized call, hands
the parsed block to a callback, and — when ack pacing is on — answers with one
8-byte command per received frame (a queued user command if any, else the
zero-ack), matching the JavaScope's lock-step behaviour that
``javascope/test_server.py`` requires.  The real APU drains its RX queue
independently, so pacing can be turned off there.

Callbacks run on the reader thread and must be fast (ring append + trigger
bookkeeping); anything slow belongs on another thread.
"""

from __future__ import annotations

import collections
import socket
import threading
import time
from dataclasses import dataclass, field

from .protocol import FrameGeometry, ParsedFrames, ZERO_ACK, parse_frames

RECONNECT_BACKOFF_S = (1.0, 2.0, 5.0)


@dataclass
class NetStats:
    bytes_received: int = 0
    frames: int = 0
    samples: int = 0
    commands_sent: int = 0
    connects: int = 0
    last_rx_monotonic: float = 0.0
    connected_since: float = 0.0
    last_error: str = ""

    def snapshot(self) -> "NetStats":
        return NetStats(**vars(self))


@dataclass
class ClientCallbacks:
    """All optional; invoked on the reader thread."""

    on_frames: object = None      # fn(ParsedFrames) -> None
    on_connect: object = None     # fn(client) -> None  (queue the select burst here)
    on_disconnect: object = None  # fn(client, reason: str) -> None


class ScopeClient:
    def __init__(
        self,
        geometry: FrameGeometry,
        ip: str,
        port: int,
        *,
        ack_pacing: bool = True,
        callbacks: ClientCallbacks | None = None,
        recv_buffer_bytes: int = 4 * 1024 * 1024,
        so_rcvbuf: int = 4 * 1024 * 1024,
        reconnect: bool = True,
        connect_timeout: float = 3.0,
    ) -> None:
        self.geometry = geometry
        self.ip = ip
        self.port = port
        self.ack_pacing = ack_pacing
        self.callbacks = callbacks or ClientCallbacks()
        self.recv_buffer_bytes = max(recv_buffer_bytes, 4 * geometry.frame_bytes)
        self.so_rcvbuf = so_rcvbuf
        self.reconnect = reconnect
        self.connect_timeout = connect_timeout
        self.stats = NetStats()
        self._cmd_queue: collections.deque[bytes] = collections.deque()
        self._sock: socket.socket | None = None
        self._sock_lock = threading.Lock()
        self._stop = threading.Event()
        self._thread: threading.Thread | None = None
        self.connected = threading.Event()

    # --- lifecycle --------------------------------------------------------

    def start(self) -> None:
        if self._thread is not None and self._thread.is_alive():
            return
        self._stop.clear()
        self._thread = threading.Thread(
            target=self._run, name="uz_scope-reader", daemon=True
        )
        self._thread.start()

    def stop(self, timeout: float = 3.0) -> None:
        self._stop.set()
        self._close_socket()
        if self._thread is not None:
            self._thread.join(timeout)
            self._thread = None

    # --- commands ---------------------------------------------------------

    def send_command(self, data: bytes) -> None:
        """Send one 8-byte command; with pacing on it rides the next ack slot."""
        if len(data) != 8:
            raise ValueError(f"commands are exactly 8 bytes, got {len(data)}")
        if self.ack_pacing:
            self._cmd_queue.append(data)
            return
        with self._sock_lock:
            sock = self._sock
            if sock is None:
                raise ConnectionError("not connected")
            sock.sendall(data)
        self.stats.commands_sent += 1

    def pending_commands(self) -> int:
        return len(self._cmd_queue)

    # --- reader thread ----------------------------------------------------

    def _run(self) -> None:
        backoff_idx = 0
        while not self._stop.is_set():
            try:
                sock = self._connect()
            except OSError as exc:
                self.stats.last_error = str(exc)
                delay = RECONNECT_BACKOFF_S[
                    min(backoff_idx, len(RECONNECT_BACKOFF_S) - 1)
                ]
                backoff_idx += 1
                if not self.reconnect or self._stop.wait(delay):
                    if not self.reconnect:
                        return
                continue

            backoff_idx = 0
            self.stats.connects += 1
            self.stats.connected_since = time.monotonic()
            self.connected.set()
            if self.callbacks.on_connect:
                self.callbacks.on_connect(self)
            reason = "closed by peer"
            try:
                self._recv_loop(sock)
            except OSError as exc:
                reason = str(exc)
                self.stats.last_error = reason
            finally:
                self.connected.clear()
                self._close_socket()
                # Stale queued commands must not fire into a fresh connection.
                self._cmd_queue.clear()
                if self.callbacks.on_disconnect:
                    self.callbacks.on_disconnect(self, reason)
            if not self.reconnect:
                return

    def _connect(self) -> socket.socket:
        sock = socket.create_connection((self.ip, self.port), self.connect_timeout)
        sock.settimeout(None)
        sock.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
        try:
            sock.setsockopt(socket.SOL_SOCKET, socket.SO_RCVBUF, self.so_rcvbuf)
        except OSError:
            pass
        with self._sock_lock:
            self._sock = sock
        return sock

    def _close_socket(self) -> None:
        with self._sock_lock:
            sock, self._sock = self._sock, None
        if sock is not None:
            try:
                sock.shutdown(socket.SHUT_RDWR)
            except OSError:
                pass
            sock.close()

    def _recv_loop(self, sock: socket.socket) -> None:
        frame_bytes = self.geometry.frame_bytes
        buf = bytearray(self.recv_buffer_bytes)
        mv = memoryview(buf)
        fill = 0
        stats = self.stats
        on_frames = self.callbacks.on_frames
        while not self._stop.is_set():
            n = sock.recv_into(mv[fill:])
            if n == 0:
                return
            fill += n
            stats.bytes_received += n
            stats.last_rx_monotonic = time.monotonic()
            k, rem = divmod(fill, frame_bytes)
            if k == 0:
                continue
            parsed: ParsedFrames = parse_frames(mv[: k * frame_bytes], self.geometry)
            if on_frames is not None:
                try:
                    on_frames(parsed)
                except Exception as exc:  # noqa: BLE001
                    # A consumer bug must not silently kill the reader thread;
                    # surface it through the normal disconnect path.
                    raise OSError(f"frame consumer failed: {exc!r}") from exc
            stats.frames += k
            stats.samples += k * self.geometry.samples_per_packet
            if rem:
                # The tail is < frame_bytes; copy it to the front.
                tail = bytes(mv[k * frame_bytes : fill])
                mv[:rem] = tail
            fill = rem
            if self.ack_pacing:
                self._send_acks(sock, k)

    def _send_acks(self, sock: socket.socket, count: int) -> None:
        # One 8-byte write per frame: lock-step servers parse exactly the
        # first command of each recv, so commands must never coalesce.
        queue = self._cmd_queue
        for _ in range(count):
            try:
                data = queue.popleft()
                self.stats.commands_sent += 1
            except IndexError:
                data = ZERO_ACK
            sock.sendall(data)
