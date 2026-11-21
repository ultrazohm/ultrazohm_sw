"""Regression coverage for device recovery and failure cleanup."""

import os
import socket
import struct
import unittest

import test_service_jobs as jobs
from test_integration import wait_for


@unittest.skipUnless(jobs.BIN.exists(), "build Rust CLI first")
class RecoveryTest(unittest.TestCase):
    def test_disconnect_preserves_settings(self):
        t = jobs.FirmwareServiceTest()
        t.setUp()
        try:
            ep = t.start()
            with socket.socket() as dev:
                dev.bind(("127.0.0.1", 0))
                dev.listen()
                port = dev.getsockname()[1]
                t.request(ep, "connect", ip="127.0.0.1", port=port)
                conn, _ = dev.accept()
                t.request(ep, "set_observable", name="JSO_ZEROVALUE", channel=1)
                t.request(ep, "send_ack", enabled=True)
                before = t.request(ep, "observables")["channels"]
                conn.shutdown(socket.SHUT_RDWR)
                conn.close()
                disconnected = wait_for(
                    lambda: (
                        s
                        if (s := t.request(ep, "status"))["lifecycle"] == "disconnected"
                        else None
                    )
                )
                t.request(ep, "connect", ip="127.0.0.1", port=port)
                conn, _ = dev.accept()
                with conn:
                    after = t.request(ep, "observables")["channels"]
                    status = t.request(ep, "status")
                    assert disconnected["device_target"] == f"127.0.0.1:{port}"
                    assert before[0] == after[0]
                    assert status["send_ack"]
                    t.request(ep, "shutdown")
                    t.processes[0][0].wait(timeout=5)
        finally:
            t.doCleanups()

    def check_failed_flash(self, failure):
        t = jobs.FirmwareServiceTest()
        t.setUp()
        try:
            ep = t.start()
            header = t.repo / "vitis/software/Baremetal/src/include/javascope.h"
            # The old firmware treats ID 1 as Enable System. The proposed firmware
            # treats it as Stop. A failed programming attempt cannot choose between them.
            header.write_text(
                header.read_text()
                .replace("Enable_System,", "TEMP_COMMAND,")
                .replace("Stop,", "Enable_System,")
                .replace("TEMP_COMMAND,", "Stop,")
            )
            (t.bin / "fake.py").write_text(
                "import sys, os\nfrom pathlib import Path\n"
                "action=sys.argv[3]\n"
                "with Path(os.environ['UZ_TEST_INVOCATION']).open('a') as f: f.write(action+'\\n')\n"
                f"failure={failure!r}\n"
                "if (action, failure) in [('build','build-headers'), ('program-built','program-headers')]:\n"
                "    p=Path('vitis/software/Baremetal/src/include/javascope.h')\n"
                "    p.write_text(p.read_text()+'\\n// edited\\n')\n"
                "sys.exit(7 if action == failure else 0)\n"
            )
            with socket.socket() as device:
                device.bind(("127.0.0.1", 0))
                device.listen()
                device.settimeout(0.2)
                job = t.request(
                    ep,
                    "firmware",
                    action="flash",
                    request_id="fail",
                    device=f"127.0.0.1:{device.getsockname()[1]}",
                    no_reconnect=False,
                )["job"]
                result = t.finished(ep, job)["job"]
                assert result["state"] == "failed"
                expected = (
                    ["build"]
                    if failure.startswith("build")
                    else ["build", "program-built"]
                )
                assert t.result.read_text().splitlines() == expected
                if failure.startswith("program"):
                    assert "configuration is unknown" in result["result"]["error"]
                with self.assertRaises(TimeoutError):
                    device.accept()
        finally:
            t.doCleanups()

    @unittest.skipIf(
        os.name == "nt" or (hasattr(os, "geteuid") and os.geteuid() == 0),
        "Requires unprivileged POSIX permissions",
    )
    def test_session_creation_failure_uses_successfully_programmed_mapping(self):
        t = jobs.FirmwareServiceTest()
        t.setUp()
        try:
            ep = t.start()
            header = t.repo / "vitis/software/Baremetal/src/include/javascope.h"
            header.write_text(
                header.read_text()
                .replace("Enable_System,", "TEMP_COMMAND,")
                .replace("Stop,", "Enable_System,")
                .replace("TEMP_COMMAND,", "Stop,")
            )
            # Programming succeeds, but the new session directory cannot be created.
            (t.bin / "fake.py").write_text(
                "import sys\nfrom pathlib import Path\n"
                f"if sys.argv[3] == 'program-built': Path({str(t.base)!r}).chmod(0o555)\n"
            )
            with socket.socket() as device:
                device.bind(("127.0.0.1", 0))
                device.listen()
                device.settimeout(5)
                job = t.request(
                    ep,
                    "firmware",
                    action="flash",
                    request_id="output-error",
                    device=f"127.0.0.1:{device.getsockname()[1]}",
                    no_reconnect=False,
                )["job"]
                connection, _ = device.accept()
                with connection:
                    connection.settimeout(3)
                    data = b""
                    while len(data) < 8:
                        chunk = connection.recv(8 - len(data))
                        assert chunk
                        data += chunk
                assert struct.unpack("<If", data) == (1, 0.0)
                result = t.finished(ep, job)["job"]
                assert result["state"] == "failed"
                assert "Permission denied" in result["result"]["error"]
        finally:
            t.base.chmod(0o755)
            t.doCleanups()

    def test_build_failure(self):
        self.check_failed_flash("build")

    def test_program_failure(self):
        self.check_failed_flash("program-built")

    def test_build_header_change(self):
        self.check_failed_flash("build-headers")

    def test_program_header_change(self):
        self.check_failed_flash("program-headers")
