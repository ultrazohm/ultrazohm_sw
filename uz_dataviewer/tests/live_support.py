"""Small simulator helpers shared by native viewer integration tests."""
import socket
import time
from contextlib import ExitStack


def ports(count=2):
    # Keep all sockets reserved until every port has been selected.
    with ExitStack() as stack:
        sockets = [stack.enter_context(socket.socket()) for _ in range(count)]
        for sock in sockets:
            sock.bind(('127.0.0.1', 0))
        return tuple(sock.getsockname()[1] for sock in sockets)


def wait_for(function, seconds=4):
    deadline = time.monotonic() + seconds
    while time.monotonic() < deadline:
        if result := function():
            return result
        time.sleep(.01)
    raise AssertionError('condition timed out')
