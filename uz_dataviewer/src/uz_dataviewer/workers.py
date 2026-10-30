"""Background-worker lifecycle shared by IO and coalescing requests.

Workers are daemon threads: blocked native IO cannot prevent process exit.
Close cancels queued/active work and joins only for a bounded grace period.
Cancellation is cooperative; results must not be published after cancellation.
Submit and shutdown of CancellableExecutor belong to the application thread.
"""
from concurrent.futures import Future
from queue import Queue, Empty
import threading

from .sources import check


def join_worker(thread):
    """Give cooperative cancellation a bounded chance to release resources."""
    if thread is not None and thread is not threading.current_thread():
        thread.join(timeout=.2)


class CancellableExecutor:
    def __init__(self, name="uz-loader"):
        self.name = name
        self.queue = Queue()
        self.cancel = threading.Event()
        self.thread = None

    def submit(self, function, *args):
        future = Future()
        if self.cancel.is_set():
            future.cancel()
            return future
        self.queue.put((future, function, args))
        if self.thread is None:
            self.thread = threading.Thread(target=self._work, daemon=True, name=self.name)
            self.thread.start()
        return future

    def _work(self):
        while not self.cancel.is_set():
            item = self.queue.get()
            if item is None:
                return
            future, function, args = item
            if not future.set_running_or_notify_cancel():
                continue
            result = None
            try:
                check(self.cancel)
                result = function(*args, cancel=self.cancel)
                check(self.cancel)
                future.set_result(result)
            except BaseException as exc:
                future.set_exception(exc)
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
