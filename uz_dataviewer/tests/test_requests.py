"""Coalescing request scheduler with several display workers."""
import threading
import time

from uz_dataviewer.requests import Requests
from uz_dataviewer.sources import check


def wait(condition, timeout=3):
    deadline = time.monotonic() + timeout
    while time.monotonic() < deadline:
        if condition():
            return
        time.sleep(.005)
    raise AssertionError('condition not reached')


def blocking(started, release):
    def compute(cancel):
        started.set()
        while not release.wait(.005):
            check(cancel)
        return 'slow'
    return compute


def test_slow_job_does_not_block_other_slot():
    requests = Requests(workers=2)
    started, release = threading.Event(), threading.Event()
    try:
        requests.request('a', 1, 'a', blocking(started, release))
        assert started.wait(2)
        requests.request('b', 1, 'b', lambda cancel: 'fast')
        wait(lambda: requests.ready('b', 1))
        assert not requests.ready('a', 1)
        release.set()
        wait(lambda: requests.ready('a', 1))
        assert requests.request('a', 1, 'a', None) == 'slow'
    finally:
        release.set()
        requests.close()


def test_single_worker_keeps_previous_serial_behavior():
    requests = Requests()
    started, release = threading.Event(), threading.Event()
    try:
        requests.request('a', 1, 'a', blocking(started, release))
        assert started.wait(2)
        requests.request('b', 1, 'b', lambda cancel: 'fast')
        time.sleep(.05)
        assert not requests.ready('b', 1)
        release.set()
        wait(lambda: requests.ready('b', 1))
    finally:
        release.set()
        requests.close()


def test_one_slot_never_runs_on_two_workers():
    requests = Requests(workers=4)
    running, overlap, lock = [0], [False], threading.Lock()
    release = threading.Event()

    def compute(cancel, value):
        with lock:
            running[0] += 1
            overlap[0] |= running[0] > 1
        try:
            # Ignore cancellation briefly so a replacement could overlap if allowed.
            release.wait(.05)
            return value
        finally:
            with lock:
                running[0] -= 1

    try:
        for key in range(5):
            requests.request('slot', key, 'slot', lambda cancel, key=key: compute(cancel, key))
            time.sleep(.01)
        wait(lambda: requests.ready('slot', 4))
        assert not overlap[0]
    finally:
        release.set()
        requests.close()


def test_new_key_cancels_running_job_and_close_cancels_all():
    requests = Requests(workers=2)
    cancels = []
    started = threading.Semaphore(0)

    def compute(cancel):
        cancels.append(cancel)
        started.release()
        while True:
            check(cancel)
            time.sleep(.005)

    requests.request('a', 1, 'a', compute)
    requests.request('b', 1, 'b', compute)
    assert started.acquire(timeout=2) and started.acquire(timeout=2)
    requests.request('a', 2, 'a', lambda cancel: 'replacement')
    wait(lambda: cancels[0].is_set() or cancels[1].is_set())
    wait(lambda: requests.ready('a', 2))
    requests.close()
    assert all(cancel.is_set() for cancel in cancels)
    assert not requests.pending


def test_failed_job_reports_error_and_worker_survives():
    requests = Requests(workers=2)
    try:
        def fail(cancel):
            raise SystemExit('plugin exit')
        requests.request('a', 1, 'a', fail)
        wait(lambda: requests.error('a') == 'plugin exit')
        requests.request('b', 1, 'b', lambda cancel: 'ok')
        wait(lambda: requests.ready('b', 1))
    finally:
        requests.close()
