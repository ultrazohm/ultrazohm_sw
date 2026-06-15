"""Holds all loaded runs and coordinates background file loading.

Loading happens on a small thread pool; finished Runs (or errors) are queued
and folded into the store from the UI thread once per frame via poll().
"""

from __future__ import annotations

import os
import queue
import threading
from concurrent.futures import ThreadPoolExecutor
from dataclasses import dataclass

from uz_dataviewer.core import loader
from uz_dataviewer.core.console import Console


@dataclass(frozen=True)
class SignalRef:
    """Identifies one signal of one run; used as drag&drop payload."""

    run_id: int
    signal: str


class DataStore:
    def __init__(self, console: Console, max_workers: int = 2):
        self.console = console
        self.runs: dict[int, loader.Run] = {}
        self._next_run_id = 1
        self._executor = ThreadPoolExecutor(
            max_workers=max_workers, thread_name_prefix="uz-loader"
        )
        self._results: queue.Queue = queue.Queue()
        self._pending_count = 0
        self._pending_lock = threading.Lock()
        # imgui drag&drop payloads in python can only carry an int id; map
        # ids to SignalRefs here.
        self._payload_registry: dict[int, SignalRef] = {}
        self._payload_ids: dict[SignalRef, int] = {}
        # Bumped whenever runs are added/removed so caches can invalidate.
        self.revision = 0

    # ---------------------------------------------------------------- loading

    @property
    def loading(self) -> bool:
        with self._pending_lock:
            return self._pending_count > 0

    def load_files_async(self, paths: list[str]) -> None:
        for path in paths:
            with self._pending_lock:
                self._pending_count += 1
            self.console.info(f"Loading '{os.path.basename(path)}' ...")
            try:
                self._executor.submit(self._load_worker, path)
            except RuntimeError:
                # No thread support (e.g. pyodide/web): load synchronously.
                self._load_worker(path)

    def _load_worker(self, path: str) -> None:
        try:
            run = loader.load_file(path, run_id=0)
            self._results.put(("ok", path, run))
        except Exception as exc:
            self._results.put(("error", path, str(exc)))

    def poll(self) -> bool:
        """Fold finished loads into the store. Call once per frame. Returns
        True if anything changed."""
        changed = False
        while True:
            try:
                kind, path, payload = self._results.get_nowait()
            except queue.Empty:
                break
            with self._pending_lock:
                self._pending_count -= 1
            if kind == "error":
                self.console.error(f"Failed to load '{path}': {payload}")
                continue
            run: loader.Run = payload
            run.run_id = self._next_run_id
            self._next_run_id += 1
            self.runs[run.run_id] = run
            self.revision += 1
            changed = True
            for warning in run.warnings:
                self.console.warning(f"{run.name}: {warning}")
            rate = run.sample_rate
            rate_text = f", ~{rate:,.0f} Hz" if rate else ""
            self.console.info(
                f"Loaded '{run.name}': {run.n_samples:,} samples, "
                f"{len(run.signals)} signals, {run.duration:.6g} s{rate_text}"
            )
        return changed

    # ----------------------------------------------------------------- access

    def remove_run(self, run_id: int) -> None:
        run = self.runs.pop(run_id, None)
        if run is not None:
            self.revision += 1
            self.console.info(f"Removed '{run.name}'.")

    def get_signal(self, ref: SignalRef):
        """Return (run, time, values) or None if the ref is stale."""
        run = self.runs.get(ref.run_id)
        if run is None or ref.signal not in run.signals:
            return None
        return run, run.time, run.signals[ref.signal]

    # ------------------------------------------------------- drag&drop payloads

    def payload_id(self, ref: SignalRef) -> int:
        existing = self._payload_ids.get(ref)
        if existing is not None:
            return existing
        new_id = len(self._payload_registry) + 1
        self._payload_registry[new_id] = ref
        self._payload_ids[ref] = new_id
        return new_id

    def resolve_payload(self, payload_id: int) -> SignalRef | None:
        return self._payload_registry.get(payload_id)

    def shutdown(self) -> None:
        self._executor.shutdown(wait=False, cancel_futures=True)
