"""Background-worker lifecycle shared by IO and coalescing requests.

Workers are daemon threads: blocked native IO cannot prevent process exit.
Close cancels queued/active work and joins only for a bounded grace period.
Cancellation is cooperative; results must not be published after cancellation.
Submit and shutdown of CancellableExecutor belong to the application thread.
"""

import threading
from concurrent.futures import Future
from queue import Empty, Queue

from .sources import check


class Cancellation:
    def __init__(self, *events):
        self.events = events

    def is_set(self):
        return any(event is not None and event.is_set() for event in self.events)


def join_worker(thread):
    """Give cooperative cancellation a bounded chance to release resources."""
    if thread is not None and thread is not threading.current_thread():
        thread.join(timeout=0.2)


def cancellable_result(produce, cancel, dispose=None):
    """Check both sides of computation; dispose results canceled before delivery."""
    check(cancel)
    result = produce()
    try:
        check(cancel)
    except BaseException:
        if dispose is not None:
            dispose(result)
        raise
    return result


class CancellableExecutor:
    def __init__(self, name="uz-loader"):
        self.name = name
        self.queue = Queue()
        self.cancel = threading.Event()
        self.thread = None

    def submit(self, function, *args, dispose=None):
        future = Future()
        if self.cancel.is_set():
            future.cancel()
            return future
        self.queue.put((future, function, args, dispose))
        if self.thread is None:
            self.thread = threading.Thread(
                target=self._work, daemon=True, name=self.name
            )
            self.thread.start()
        return future

    def _work(self):
        while not self.cancel.is_set():
            item = self.queue.get()
            if item is None:
                return
            future, function, args, dispose = item
            if not future.set_running_or_notify_cancel():
                continue
            result = None
            try:
                result = cancellable_result(
                    lambda function=function, args=args: function(
                        *args, cancel=self.cancel
                    ),
                    self.cancel,
                    dispose,
                )
                future.set_result(result)
            except BaseException as exc:
                error = exc
                if result is not None and dispose is not None:
                    try:
                        dispose(result)
                    except BaseException as cleanup_error:
                        # A cleanup failure must still complete the future;
                        # otherwise callers wait forever on a dead worker.
                        error = cleanup_error
                # A worker's SystemExit/KeyboardInterrupt must not escape when
                # the application thread retrieves the completed future.
                if not isinstance(error, Exception):
                    error = RuntimeError(f"{type(error).__name__}: {error}")
                future.set_exception(error)
            finally:
                item = future = function = args = result = None

    def shutdown(self):
        self.cancel.set()
        while True:
            try:
                item = self.queue.get_nowait()
            except Empty:
                break
            if item is not None:
                item[0].cancel()
        self.queue.put(None)
        join_worker(self.thread)
