"""Coalescing background requests: one queued job per consumer, no GUI calls."""

from __future__ import annotations

import threading
from collections import OrderedDict
from dataclasses import dataclass

from .sources import Cancelled, check
from .workers import join_worker


@dataclass
class Job:
    key: object
    identity: object
    function: object
    cancel: threading.Event
    continuous: bool = False


class Requests:
    """Coalescing scheduler using the shared cancellable daemon-worker lifecycle.

    Up to ``workers`` jobs run concurrently, so one slow job (for example a first
    summary build) does not hold back other consumers. A slot never runs on two
    workers at once: its replacement waits until the cancelled job has returned.
    """

    def __init__(self, synchronous=False, workers=1):
        self.synchronous = synchronous
        self.workers = max(1, int(workers))
        self.condition = threading.Condition()
        self.jobs = OrderedDict()
        self.wanted = {}
        self.results = {}
        self.errors = {}
        self.active = {}
        self.closed = False
        self.threads = []

    @property
    def pending(self):
        with self.condition:
            return bool(self.jobs or self.active)

    def request(self, slot, key, identity, function, immediate=False, continuous=False):
        run_now = None
        with self.condition:
            if self.closed:
                return None
            if self.wanted.get(slot) != key:
                self.wanted[slot] = key
                previous = self.jobs.pop(slot, None)
                if previous:
                    previous.cancel.set()
                if slot in self.active and not (
                    continuous and self.active[slot].identity == identity
                ):
                    self.active[slot].cancel.set()
                self.errors.pop(slot, None)
                job = Job(key, identity, function, threading.Event(), continuous)
                if self.synchronous or immediate:
                    run_now = job
                else:
                    self.jobs[slot] = job
                    self._spawn()
                    self.condition.notify()
            if run_now is None:
                result = self.results.get(slot)
                return result[2] if result and result[1] == identity else None
        # Immediate work runs without the lock so the worker can publish meanwhile.
        try:
            value, error = function(run_now.cancel), None
        except Exception as exc:
            value, error = None, str(exc)
        with self.condition:
            if self.wanted.get(slot) == key:
                if error is None:
                    self.results[slot] = (key, identity, value)
                else:
                    self.errors[slot] = error
            result = self.results.get(slot)
            return result[2] if result and result[1] == identity else None

    def _spawn(self):
        """Start workers up to the limit; the caller holds the condition lock.

        A worker killed by a BaseException must not stall all later requests.
        """
        self.threads = [thread for thread in self.threads if thread.is_alive()]
        if len(self.threads) < min(self.workers, len(self.jobs) + len(self.active)):
            thread = threading.Thread(target=self._work, name="uz-data", daemon=True)
            self.threads.append(thread)
            thread.start()

    def _runnable(self):
        """Oldest queued slot that is not still running a cancelled job."""
        return next((slot for slot in self.jobs if slot not in self.active), None)

    def ready(self, slot, key):
        with self.condition:
            result = self.results.get(slot)
            return result is not None and result[0] == key

    def completed(self, slot, key):
        """Consume an exact completed result without exposing worker internals."""
        with self.condition:
            result = self.results.get(slot)
            if result is not None and result[0] == key:
                self.results.pop(slot)
                return result[2]
            return None

    def error(self, slot):
        with self.condition:
            return self.errors.get(slot)

    def retain(self, slots):
        with self.condition:
            for slot in list(self.wanted):
                if slot not in slots:
                    self._forget(slot)

    def forget(self, slot):
        with self.condition:
            self._forget(slot)

    def _forget(self, slot):
        """Remove a consumer while the caller holds the condition lock."""
        self.wanted.pop(slot, None)
        self.results.pop(slot, None)
        self.errors.pop(slot, None)
        job = self.jobs.pop(slot, None)
        if job:
            job.cancel.set()
        if slot in self.active:
            self.active[slot].cancel.set()

    def _work(self):
        while True:
            with self.condition:
                self.condition.wait_for(
                    lambda: self.closed or self._runnable() is not None
                )
                if self.closed:
                    return
                slot = self._runnable()
                job = self.jobs.pop(slot)
                self.active[slot] = job
            result = None
            try:
                check(job.cancel)
                result = job.function(job.cancel)
                check(job.cancel)
                with self.condition:
                    if self.wanted.get(slot) == job.key or (
                        job.continuous
                        and slot in self.wanted
                        and not job.cancel.is_set()
                    ):
                        self.results[slot] = (job.key, job.identity, result)
            except Cancelled:
                pass
            except (
                BaseException
            ) as exc:  # plugin code may raise SystemExit; keep serving
                with self.condition:
                    if self.wanted.get(slot) == job.key:
                        self.errors[slot] = str(exc)
            finally:
                with self.condition:
                    if self.active.get(slot) is job:
                        del self.active[slot]
                    # A replacement for this slot may have been waiting for it.
                    self.condition.notify_all()
                # Do not pin the last source/analysis snapshot while the worker idles.
                job = result = None

    def close(self):
        with self.condition:
            self.closed = True
            for job in self.jobs.values():
                job.cancel.set()
            self.jobs.clear()
            self.results.clear()
            self.wanted.clear()
            self.errors.clear()
            for job in self.active.values():
                job.cancel.set()
            self.condition.notify_all()
            threads = list(self.threads)
        for thread in threads:
            join_worker(thread)
