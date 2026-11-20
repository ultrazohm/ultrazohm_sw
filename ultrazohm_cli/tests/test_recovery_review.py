"""Regression coverage for device recovery and failure cleanup."""

import socket

import test_service_jobs as jobs
from test_integration import wait_for


def test_disconnect_preserves_settings():
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


def test_configuration_failure_still_stops_device():
    t = jobs.FirmwareServiceTest()
    t.setUp()
    try:
        (t.bin / "fake.py").write_text(
            "import time\nfrom pathlib import Path\nprint('programming',flush=True)\ntime.sleep(.4)\np=Path('vitis/software/Baremetal/src/include/javascope.h')\np.write_text(p.read_text()+'\\n// harmless edit during build\\n')\nprint('programmed',flush=True)\n"
        )
        ep = t.start()
        with socket.socket() as dev:
            dev.bind(("127.0.0.1", 0))
            dev.listen()
            dev.settimeout(0.3)
            job = t.request(
                ep,
                "firmware",
                action="flash",
                request_id="header",
                device=f"127.0.0.1:{dev.getsockname()[1]}",
                no_reconnect=False,
            )["job"]
            wait_for(lambda: "programming" in t.request(ep, "job", id=job["id"])["log"])
            t.request(ep, "shutdown")
            t.processes[0][0].wait(timeout=5)
            try:
                conn, _ = dev.accept()
                conn.close()
                contacted = True
            except TimeoutError:
                contacted = False
            log = (t.repo / "artifacts" / f"firmware-{job['id']}.log").read_text()
            assert contacted
            assert t.processes[0][0].returncode != 0
            assert "headers changed" in log
    finally:
        t.doCleanups()
