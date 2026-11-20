"""Firmware jobs exercise the real service with a fake XSCT, never hardware."""

import json
import os
import socket
import subprocess
import time
import unittest

import test_vitis_cli as tooling
from test_integration import repository_fixture, wait_for

BIN = tooling.BIN


@unittest.skipUnless(BIN.exists(), "build Rust CLI first")
class FirmwareServiceTest(unittest.TestCase):
    cli = tooling.VitisCommandTest.cli

    def setUp(self):
        tooling.VitisCommandTest.setUp(self)
        repository_fixture(self.repo)
        self.processes = []
        self.addCleanup(self.cleanup_services)

    def cleanup_services(self):
        for process, endpoint in self.processes:
            if process.poll() is None:
                try:
                    self.request(endpoint, "shutdown")
                    process.wait(timeout=10)
                except Exception:
                    process.kill()
                    process.wait(timeout=5)

    def start(self, **env):
        with socket.socket() as reserve:
            reserve.bind(("127.0.0.1", 0))
            endpoint = f"127.0.0.1:{reserve.getsockname()[1]}"
        process = subprocess.Popen(
            [
                str(BIN),
                "--endpoint",
                endpoint,
                "serve",
                "--repo",
                str(self.repo),
                "--output",
                str(self.base / f"run-{len(self.processes)}"),
            ],
            env={**self.env, **env},
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL,
        )
        self.processes.append((process, endpoint))
        wait_for(lambda: self.request(endpoint, "status"))
        return endpoint

    def request(self, endpoint, op, **fields):
        host, port = endpoint.split(":")
        with socket.create_connection((host, int(port)), timeout=3) as connection:
            connection.sendall(
                json.dumps({"api_version": 3, "command": {"op": op, **fields}}).encode()
                + b"\n"
            )
            reply = json.loads(connection.makefile("rb").readline())
        if not reply["ok"]:
            raise RuntimeError(reply["error"])
        return reply

    def submit(self, endpoint, action="build", request_id="test", **kwargs):
        return self.request(
            endpoint,
            "firmware",
            action=action,
            request_id=request_id,
            device=None,
            no_reconnect=True,
            **kwargs,
        )["job"]

    def finished(self, endpoint, job):
        return wait_for(
            lambda: (
                reply
                if (reply := self.request(endpoint, "job", id=job["id"], offset=0))[
                    "job"
                ]["state"]
                != "running"
                else None
            )
        )

    def test_embedded_service_freezes_paths_and_uses_checkout_output(self):
        import ultrazohm_cli

        with socket.socket() as reserve:
            reserve.bind(("127.0.0.1", 0))
            endpoint = f"127.0.0.1:{reserve.getsockname()[1]}"
        original = os.getcwd()
        try:
            os.chdir(self.base)
            with ultrazohm_cli.Acquisition(
                endpoint=endpoint,
                repo=str(self.repo.relative_to(self.base)),
                xsct=str(
                    (
                        self.bin / ("xsct.bat" if os.name == "nt" else "xsct")
                    ).relative_to(self.base)
                ),
            ):
                os.chdir(original)
                status = ultrazohm_cli.Client(endpoint).status()
                self.assertEqual(status["repository"], str(self.repo))
                self.assertTrue(
                    status["output"].startswith(
                        str(self.repo / "artifacts" / "live_logs")
                    )
                )
                self.assertTrue(status["firmware_available"])
        finally:
            os.chdir(original)

    def test_flash_replaces_session_without_replacing_service(self):
        endpoint = self.start()
        before = self.request(endpoint, "status")
        job = self.submit(endpoint, "flash")
        result = self.finished(endpoint, job)
        self.assertEqual(result["job"]["state"], "succeeded", result)
        after = self.request(endpoint, "status")
        self.assertEqual(before["service_id"], after["service_id"])
        self.assertNotEqual(before["session_id"], after["session_id"])
        self.assertNotEqual(before["output"], after["output"])
        self.assertFalse(after["state"]["connected"])
        self.assertEqual(self.submit(endpoint, "flash")["id"], job["id"])
        with self.assertRaisesRegex(RuntimeError, "request ID"):
            self.submit(endpoint, "build")

    def test_failure_keeps_endpoint_available_and_cli_reports_failure(self):
        endpoint = self.start(UZ_TEST_EXIT="7")
        job = self.submit(endpoint, "flash")
        result = self.finished(endpoint, job)
        self.assertEqual(result["job"]["state"], "failed")
        self.assertIsNone(self.request(endpoint, "status")["session_id"])
        follow = self.cli("--endpoint", endpoint, "job", job["id"], "--follow")
        self.assertNotEqual(follow.returncode, 0)

    def test_build_preserves_session_and_two_services_are_independent(self):
        first, second = self.start(), self.start()
        initial = [self.request(ep, "status") for ep in (first, second)]
        job = self.submit(first)
        self.assertEqual(self.finished(first, job)["job"]["state"], "succeeded")
        for endpoint, before in zip((first, second), initial, strict=True):
            self.assertEqual(
                self.request(endpoint, "status")["session_id"], before["session_id"]
            )
        self.assertEqual(self.request(second, "jobs")["jobs"], [])

    def test_header_changes_during_programming_block_reconnect(self):
        stub = self.bin / "fake.py"
        stub.write_text(
            "from pathlib import Path\np=Path('vitis/software/Baremetal/src/include/javascope.h')\np.write_text(p.read_text()+'\\n// changed while building\\n')\n"
        )
        endpoint = self.start()
        job = self.submit(endpoint, "flash")
        result = self.finished(endpoint, job)
        self.assertEqual(result["job"]["state"], "failed")
        self.assertIn("headers changed", result["job"]["result"]["error"])
        with self.assertRaisesRegex(RuntimeError, "configuration is uncertain"):
            self.request(endpoint, "connect", ip="127.0.0.1", port=1)

    def test_workspace_lock_covers_other_services_and_local_builds(self):
        (self.bin / "fake.py").write_text(
            "import time\nprint('building',flush=True)\ntime.sleep(1)\n"
        )
        first, second = self.start(), self.start()
        job = self.submit(first)
        wait_for(lambda: "building" in self.request(first, "job", id=job["id"])["log"])
        with self.assertRaisesRegex(RuntimeError, "workspace is in use"):
            self.submit(second)
        result = self.cli("build", "--local", "--repo", str(self.repo))
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("workspace is in use", result.stderr)
        self.finished(first, job)

    def test_active_job_does_not_block_stop_and_shutdown_is_deferred(self):
        stub = self.bin / "fake.py"
        stub.write_text(
            "import time\nprint('programming', flush=True)\ntime.sleep(1)\n"
        )
        endpoint = self.start()
        job = self.submit(endpoint, "flash")
        wait_for(
            lambda: "programming" in self.request(endpoint, "job", id=job["id"])["log"]
        )
        started = time.monotonic()
        self.request(endpoint, "stop")
        self.assertLess(time.monotonic() - started, 0.5)
        with self.assertRaisesRegex(RuntimeError, "another firmware"):
            self.submit(endpoint, request_id="other")
        response = self.request(endpoint, "shutdown")
        self.assertTrue(response["deferred"])
        self.assertEqual(
            self.request(endpoint, "job", id=job["id"])["job"]["state"], "running"
        )
        self.processes[0][0].wait(timeout=10)

    def test_flash_preserves_output_parent(self):
        endpoint = self.start()
        before = self.request(endpoint, "status")["output"]
        job = self.submit(endpoint, "flash")
        self.assertEqual(self.finished(endpoint, job)["job"]["state"], "succeeded")
        from pathlib import Path

        self.assertEqual(
            Path(before).parent, Path(self.request(endpoint, "status")["output"]).parent
        )

    def test_reconnect_failure_does_not_poison_next_flash(self):
        endpoint = self.start()
        with socket.socket() as reserve:
            reserve.bind(("127.0.0.1", 0))
            port = reserve.getsockname()[1]
        job = self.request(
            endpoint,
            "firmware",
            action="flash",
            request_id="failure",
            device=f"127.0.0.1:{port}",
            no_reconnect=False,
        )["job"]
        result = wait_for(
            lambda: (
                r
                if (r := self.request(endpoint, "job", id=job["id"]))["job"]["state"]
                != "running"
                else None
            ),
            seconds=30,
        )
        self.assertEqual(result["job"]["state"], "failed")
        self.assertIsNone(self.request(endpoint, "status")["state"]["error"])
        retry = self.submit(endpoint, "flash", request_id="retry")
        self.assertEqual(self.finished(endpoint, retry)["job"]["state"], "succeeded")

    def test_device_becoming_ready_after_programming_is_retried(self):
        endpoint = self.start()
        with socket.socket() as device:
            device.bind(("127.0.0.1", 0))
            port = device.getsockname()[1]
            job = self.request(
                endpoint,
                "firmware",
                action="flash",
                request_id="late",
                device=f"127.0.0.1:{port}",
                no_reconnect=False,
            )["job"]
            wait_for(lambda: self.result.exists())
            time.sleep(0.3)
            device.listen()
            device.settimeout(5)
            connection, _ = device.accept()
            with connection:
                self.assertEqual(
                    self.finished(endpoint, job)["job"]["state"], "succeeded"
                )
                self.request(endpoint, "shutdown")
                self.processes[0][0].wait(timeout=5)

    @unittest.skipIf(
        os.name == "nt", "POSIX SIGINT delivery; Windows uses console events"
    )
    def test_signal_shutdown_stops_device_during_build(self):
        import signal

        (self.bin / "fake.py").write_text(
            "import time\nprint('building', flush=True)\ntime.sleep(2)\n"
        )
        endpoint = self.start()
        with socket.socket() as device:
            device.bind(("127.0.0.1", 0))
            device.listen()
            self.request(
                endpoint, "connect", ip="127.0.0.1", port=device.getsockname()[1]
            )
            connection, _ = device.accept()
            with connection:
                before = self.request(endpoint, "status")["state"]["commands_sent"]
                job = self.submit(endpoint)
                wait_for(
                    lambda: (
                        "building" in self.request(endpoint, "job", id=job["id"])["log"]
                    )
                )
                self.processes[0][0].send_signal(signal.SIGINT)
                connection.settimeout(1)
                data = b""
                while len(data) < (before + 1) * 8:
                    chunk = connection.recv(4096)
                    self.assertTrue(chunk)
                    data += chunk
                self.assertIsNone(self.processes[0][0].poll())
                self.processes[0][0].wait(timeout=5)

    def test_embedded_output_tracks_replacement_session_after_close(self):
        import ultrazohm_cli

        (self.bin / "fake.py").write_text("print('programmed')\n")

        with socket.socket() as reserve:
            reserve.bind(("127.0.0.1", 0))
            endpoint = f"127.0.0.1:{reserve.getsockname()[1]}"
        with ultrazohm_cli.Acquisition(
            endpoint=endpoint,
            repo=str(self.repo),
            xsct=str(self.bin / ("xsct.bat" if os.name == "nt" else "xsct")),
        ) as acquisition:
            before = acquisition.output
            job = self.submit(endpoint, "flash")
            self.assertEqual(self.finished(endpoint, job)["job"]["state"], "succeeded")
            current = self.request(endpoint, "status")["output"]
            self.assertNotEqual(before, current)
            self.assertEqual(acquisition.output, current)
        self.assertEqual(acquisition.output, current)

    def test_shutdown_waits_for_boot_and_delivers_stop(self):
        import struct

        (self.bin / "fake.py").write_text(
            "import time\nprint('programming',flush=True)\ntime.sleep(0.3)\n"
        )
        endpoint = self.start()
        with socket.socket() as device:
            device.bind(("127.0.0.1", 0))
            port = device.getsockname()[1]
            job = self.request(
                endpoint,
                "firmware",
                action="flash",
                request_id="shutdown",
                device=f"127.0.0.1:{port}",
                no_reconnect=False,
            )["job"]
            wait_for(
                lambda: (
                    "programming" in self.request(endpoint, "job", id=job["id"])["log"]
                )
            )
            self.assertTrue(self.request(endpoint, "shutdown")["deferred"])
            time.sleep(0.6)
            self.assertIsNone(self.processes[0][0].poll())
            device.listen()
            device.settimeout(3)
            connection, _ = device.accept()
            with connection:
                connection.settimeout(3)
                data = b""
                while len(data) < 8:
                    chunk = connection.recv(8 - len(data))
                    self.assertTrue(chunk)
                    data += chunk
                mapping = json.loads(
                    self.cli("channel-mapping", "--repo", str(self.repo)).stdout
                )
                self.assertEqual(
                    struct.unpack("<If", data), (mapping["commands"]["Stop"], 0.0)
                )
            self.processes[0][0].wait(timeout=5)
            self.assertEqual(self.processes[0][0].returncode, 0)

    def test_shutdown_stop_failure_is_persisted_and_exits_nonzero(self):
        (self.bin / "fake.py").write_text(
            "import time\nprint('programming',flush=True)\ntime.sleep(0.3)\n"
        )
        endpoint = self.start()
        with socket.socket() as device:
            device.bind(("127.0.0.1", 0))
            job = self.request(
                endpoint,
                "firmware",
                action="flash",
                request_id="failed-shutdown",
                device=f"127.0.0.1:{device.getsockname()[1]}",
                no_reconnect=False,
            )["job"]
            wait_for(
                lambda: (
                    "programming" in self.request(endpoint, "job", id=job["id"])["log"]
                )
            )
            self.request(endpoint, "shutdown")
            self.processes[0][0].wait(timeout=30)
        self.assertNotEqual(self.processes[0][0].returncode, 0)
        log = self.repo / "artifacts" / f"firmware-{job['id']}.log"
        self.assertIn("Stop after programming failed", log.read_text())
