"""Real socket tests for the GUI-independent control transport."""

import io
import socket
import threading
import time
import unittest
from concurrent.futures import Future, ThreadPoolExecutor

from ultrazohm_dataviewer import Client, ViewerError
from ultrazohm_dataviewer import control_protocol as wire
from ultrazohm_dataviewer.control_server import ControlServer


class TransportTests(unittest.TestCase):
    def setUp(self):
        self.server = ControlServer("127.0.0.1:0")
        self.client = Client(self.server.endpoint, timeout=2)
        self.workers = ThreadPoolExecutor(2)

    def tearDown(self):
        self.server.close()
        self.workers.shutdown(wait=True)
        self.client.close()

    def pump(self, future, handler):
        deadline = time.monotonic() + 3
        while not future.done() and time.monotonic() < deadline:
            self.server.poll(handler)
            time.sleep(0.001)
        return future.result(timeout=0.1)

    def test_persistent_connection_and_session_roundtrip(self):
        owner = threading.get_ident()
        observed = []

        def handle(operation, arguments, session):
            self.assertEqual(threading.get_ident(), owner)
            observed.append((operation, arguments, session))
            return dict(session="session-a", result={"grid": [2, 3]})

        for _ in range(2):
            result = self.pump(self.workers.submit(self.client.status), handle)
            self.assertEqual(result["grid"], [2, 3])
        self.assertEqual(observed, [("status", {}, None), ("status", {}, "session-a")])
        self.assertEqual(len(self.server._clients), 1)

    def test_operation_error_preserves_connection(self):
        def fail(*_):
            raise ViewerError("stale_handle", "Recording removed")

        with self.assertRaises(ViewerError) as error:
            self.pump(self.workers.submit(self.client.status), fail)
        self.assertEqual(error.exception.code, "stale_handle")
        result = self.pump(
            self.workers.submit(self.client.status),
            lambda *_: dict(session="a", result=True),
        )
        self.assertTrue(result)

    def test_credentials_reject_wrong_instance_before_dispatch(self):
        other = ControlServer("127.0.0.1:0")
        try:
            for token in ("", "wrong", other.token, "non-ascii-ä"):
                with Client(self.server.endpoint, token=token, timeout=2) as client:
                    with self.assertRaises(ViewerError) as error:
                        client.status()
                    self.assertEqual(error.exception.code, "unauthorized")
                self.assertFalse(self.server.pending)
        finally:
            other.close()

    def test_credentials_are_private_and_removed_on_shutdown(self):
        import os

        from ultrazohm_dataviewer.control_credentials import discover

        path = self.server._credential_path
        self.assertEqual(discover(self.server.endpoint), self.server.token)
        if os.name != "nt":
            self.assertEqual(path.stat().st_mode & 0o077, 0)
            self.assertEqual(path.parent.stat().st_mode & 0o077, 0)
        self.server.close()
        self.assertFalse(path.exists())

    def test_deferred_operation_does_not_block_dispatch(self):
        pending = Future()
        calls = []

        def handle(*_):
            calls.append(True)
            return pending

        future = self.workers.submit(self.client.status)
        deadline = time.monotonic() + 2
        while not calls and time.monotonic() < deadline:
            self.server.poll(handle)
            time.sleep(0.001)
        self.assertTrue(calls)
        self.assertFalse(future.done())
        pending.set_result(dict(session="a", result=42))
        self.assertEqual(future.result(timeout=2), 42)

    def test_shutdown_releases_pending_client(self):
        future = self.workers.submit(self.client.status)
        deadline = time.monotonic() + 2
        while not self.server.pending and time.monotonic() < deadline:
            time.sleep(0.001)
        self.assertTrue(self.server.pending)
        self.server.close()
        with self.assertRaises((ViewerError, OSError, EOFError)):
            future.result(timeout=2)

    def test_shutdown_cancels_dispatched_work(self):
        source = Future()
        dispatched = []

        def handler(*_):
            dispatched.append(True)
            return source

        future = self.workers.submit(self.client.status)
        deadline = time.monotonic() + 2
        while not dispatched and time.monotonic() < deadline:
            self.server.poll(handler)
            time.sleep(0.001)
        self.assertTrue(dispatched)
        self.server.close()
        self.assertTrue(source.cancelled())
        with self.assertRaises((ViewerError, OSError, EOFError)):
            future.result(timeout=2)

    def test_wire_rejects_nonfinite_and_unsupported_messages(self):
        for data in [
            b'{"version":1,"value":NaN}\n',
            b'{"version":2}\n',
            b'{"version":true}\n',
            b"[]\n",
        ]:
            with self.assertRaises(ValueError):
                wire.read(io.BytesIO(data))

    def test_disconnect_cancels_deferred_operation(self):
        source = Future()
        received = []
        connection = socket.create_connection(wire.address(self.server.endpoint))
        connection.sendall(
            wire.encode(
                dict(
                    version=1,
                    id=1,
                    operation="load",
                    arguments={},
                    token=self.server.token,
                )
            )
        )

        def handler(*args):
            received.append(args)
            return source

        deadline = time.monotonic() + 2
        while not received and time.monotonic() < deadline:
            self.server.poll(handler)
            time.sleep(0.001)
        self.assertTrue(received)
        connection.close()
        deadline = time.monotonic() + 2
        while not source.cancelled() and time.monotonic() < deadline:
            time.sleep(0.001)
        self.assertTrue(source.cancelled())

    def test_pipelined_request_waits_without_spinning(self):
        from unittest.mock import patch

        from ultrazohm_dataviewer import control_server

        source = Future()
        received = []
        connection = socket.create_connection(wire.address(self.server.endpoint))
        connection.settimeout(2)

        def request(number):
            return wire.encode(
                dict(
                    version=1,
                    id=number,
                    operation="status",
                    arguments={},
                    token=self.server.token,
                )
            )

        def handler(*args):
            received.append(args)
            return source if len(received) == 1 else dict(session="a", result=2)

        try:
            connection.sendall(request(1))
            deadline = time.monotonic() + 2
            while not received and time.monotonic() < deadline:
                self.server.poll(handler)
                time.sleep(0.001)
            self.assertEqual(len(received), 1)
            with patch.object(
                control_server.select, "select", wraps=control_server.select.select
            ) as poll:
                connection.sendall(request(2))
                time.sleep(0.2)
                self.assertLess(poll.call_count, 30)
            source.set_result(dict(session="a", result=1))
            with connection.makefile("rb") as stream:
                self.assertEqual(wire.read(stream)["result"], 1)
                deadline = time.monotonic() + 2
                while len(received) < 2 and time.monotonic() < deadline:
                    self.server.poll(handler)
                    time.sleep(0.001)
                self.assertEqual(wire.read(stream)["result"], 2)
        finally:
            connection.close()


if __name__ == "__main__":
    unittest.main()
