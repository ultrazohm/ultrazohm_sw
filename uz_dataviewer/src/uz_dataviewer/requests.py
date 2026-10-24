"""Coalescing background requests: one queued job per consumer, no GUI calls."""
from __future__ import annotations
from collections import OrderedDict
from dataclasses import dataclass
import threading
from .sources import Cancelled, check


@dataclass
class Job:
    key: object
    identity: object
    function: object
    cancel: threading.Event


class Requests:
    def __init__(self, synchronous=False):
        self.synchronous = synchronous
        self.condition = threading.Condition()
        self.jobs = OrderedDict()
        self.wanted = {}
        self.results = {}
        self.errors = {}
        self.active = None
        self.closed = False
        self.thread = None

    @property
    def pending(self):
        with self.condition:
            return bool(self.jobs or self.active)

    def request(self, slot, key, identity, function, immediate=False):
        with self.condition:
            if self.closed:
                return None
            if self.wanted.get(slot) != key:
                self.wanted[slot] = key
                previous = self.jobs.pop(slot, None)
                if previous:
                    previous.cancel.set()
                if self.active and self.active[0] == slot:
                    self.active[1].cancel.set()
                self.errors.pop(slot, None)
                job = Job(key, identity, function, threading.Event())
                if self.synchronous or immediate:
                    try:
                        self.results[slot] = (key, identity, function(job.cancel))
                    except Exception as exc:
                        self.errors[slot] = str(exc)
                else:
                    self.jobs[slot] = job
                    if self.thread is None:
                        self.thread = threading.Thread(target=self._work, name='uz-data', daemon=True)
                        self.thread.start()
                    self.condition.notify()
            result = self.results.get(slot)
            return result[2] if result and result[1] == identity else None

    def ready(self, slot, key):
        with self.condition:
            result = self.results.get(slot)
            return result is not None and result[0] == key

    def retain(self, slots):
        with self.condition:
            for slot in list(self.wanted):
                if slot not in slots:
                    self.wanted.pop(slot, None)
                    self.results.pop(slot, None)
                    self.errors.pop(slot, None)
                    job = self.jobs.pop(slot, None)
                    if job:
                        job.cancel.set()
                    if self.active and self.active[0] == slot:
                        self.active[1].cancel.set()

    def forget(self, slot):
        with self.condition:
            self.wanted.pop(slot, None)
            self.results.pop(slot, None)
            self.errors.pop(slot, None)
            job = self.jobs.pop(slot, None)
            if job:
                job.cancel.set()
            if self.active and self.active[0] == slot:
                self.active[1].cancel.set()

    def _work(self):
        while True:
            with self.condition:
                self.condition.wait_for(lambda: self.jobs or self.closed)
                if self.closed:
                    return
                slot, job = self.jobs.popitem(last=False)
                self.active = (slot, job)
            result = None
            try:
                check(job.cancel)
                result = job.function(job.cancel)
                check(job.cancel)
                with self.condition:
                    if self.wanted.get(slot) == job.key:
                        self.results[slot] = (job.key, job.identity, result)
            except Cancelled:
                pass
            except Exception as exc:
                with self.condition:
                    if self.wanted.get(slot) == job.key:
                        self.errors[slot] = str(exc)
            finally:
                with self.condition:
                    self.active = None
                # Do not pin the last source/analysis snapshot while the worker idles.
                job = result = None

    def close(self):
        with self.condition:
            self.closed = True
            self.jobs.clear()
            self.results.clear()
            if self.active:
                self.active[1].cancel.set()
            self.condition.notify_all()
        if self.thread is not None:
            self.thread.join(timeout=2)
