"""Owned CLI service processes, independent of any GUI or event loop."""

from __future__ import annotations

import os
import subprocess
import sys
import threading
import time
from dataclasses import dataclass
from pathlib import Path


@dataclass
class ServiceProcess:
    """The launched process remains owned even when the viewer attaches elsewhere."""

    process: object = None
    endpoint: str | None = None
    shutdown_requested: bool = False
    log: Path | None = None
    repo: Path | None = None
    mapping: Path | None = None
    service_id: str | None = None

    @property
    def running(self):
        return self.process is not None and self.process.poll() is None

    def owns(self, endpoint):
        return self.endpoint == endpoint and self.running

    def start(
        self,
        output,
        mapping,
        profile=None,
        data_options=None,
        ack=False,
        repo=None,
        endpoint="127.0.0.1:19740",
        client=None,
        cancel=None,
        command_prefix=None,
    ):
        if repo and mapping:
            raise ValueError(
                "Choose either a firmware repository or an explicit channel mapping"
            )
        cancel = cancel or threading.Event()
        if client is None:
            from . import Client

            client = Client(endpoint)
        if self.running:
            raise RuntimeError(
                "The launched service is still running; check its endpoint and service.log"
            )
        output = Path(output).expanduser().resolve()
        # One output directory per service lifetime, never reuse an existing run.
        output.parent.mkdir(parents=True, exist_ok=True)
        if output.exists():
            raise ValueError(
                "Choose a new session directory; existing recordings are never overwritten"
            )
        log_path = output.with_name(output.name + ".service.log")
        args = [
            *(command_prefix or [sys.executable, "-m", "ultrazohm_cli"]),
            "--endpoint",
            endpoint,
            "serve",
            "--output",
            str(output),
            "--format",
            "parquet",
        ]
        if repo:
            args += ["--repo", str(Path(repo).expanduser().resolve())]
        elif mapping:
            args += ["--channel-mapping", str(Path(mapping).expanduser().resolve())]
        if profile:
            args += ["--profile", str(profile)]
        if ack:
            args += ["--ack", "on"]
        for name in (
            "buffer_samples",
            "segment_rows",
            "flush_interval_ms",
            "queue_seconds",
            "recording_backend",
        ):
            if (value := (data_options or {}).get(name)) is not None:
                args += ["--" + name.replace("_", "-"), str(value)]
        options = (
            {"stdin": subprocess.DEVNULL, "start_new_session": True}
            if os.name != "nt"
            else {
                "stdin": subprocess.DEVNULL,
                "creationflags": subprocess.DETACHED_PROCESS
                | subprocess.CREATE_NEW_PROCESS_GROUP,
            }
        )
        with log_path.open("ab") as log:
            self.process = subprocess.Popen(args, stdout=log, stderr=log, **options)
            self.endpoint = endpoint
            self.repo = Path(repo).expanduser().resolve() if repo else None
            self.mapping = Path(mapping).expanduser().resolve() if mapping else None
            self.shutdown_requested = False
            self.log = log_path
        deadline = time.monotonic() + 8
        while not cancel.is_set() and time.monotonic() < deadline:
            if self.process.poll() is not None:
                raise RuntimeError(f"Service failed; see {log_path}")
            try:
                self.service_id = client.status()["service_id"]
                return
            except (OSError, RuntimeError):
                cancel.wait(0.1)
        # A service that never answered must not block later Connect attempts.
        self.terminate_startup()
        raise RuntimeError(f"Service startup timed out; see {log_path}")

    def terminate_startup(self):
        process = self.process
        if process is None or process.poll() is not None:
            return
        process.terminate()
        try:
            process.wait(timeout=5)
        except subprocess.TimeoutExpired:
            process.kill()
            process.wait()

    def wait(self, *, cancel=None, progress=None):
        """Wait for exit, or return None if the caller hands off finalization."""
        cancel = cancel or threading.Event()
        while self.running:
            if cancel.is_set():
                return None
            if progress:
                progress()
            cancel.wait(0.2)
        return self.process.returncode if self.process else None

    def shutdown(self, client=None):
        """Request graceful shutdown only for the service this process owns."""
        if self.shutdown_requested or not self.running:
            return
        if client is None:
            from . import Client

            client = Client(self.endpoint)
        if self.service_id and client.status()["service_id"] != self.service_id:
            raise RuntimeError(
                "Owned service was replaced; refusing to shut down its replacement"
            )
        client.shutdown()
        self.shutdown_requested = True
