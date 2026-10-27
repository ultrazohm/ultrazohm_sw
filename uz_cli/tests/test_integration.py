"""Real CLI/service tests against the independent JavaScope Python simulator.
Run: python -m unittest discover -s uz_cli/tests -v
Set UZ_CLI_BIN for release/Windows builds. Optional Python polars validates files.
"""
import importlib.util
import json
import os
from pathlib import Path
import socket
import signal
import struct
import subprocess
import sys
import tempfile
import threading
import re
import time
import unittest

ROOT = Path(__file__).resolve().parents[2]
BIN = Path(os.environ.get("UZ_CLI_BIN", ROOT / "uz_cli/target/debug" / ("ultrazohm.exe" if os.name == "nt" else "ultrazohm")))
spec = importlib.util.spec_from_file_location("test_server", ROOT / "javascope/test_server.py")
server_module = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = server_module
spec.loader.exec_module(server_module)


def port():
    with socket.socket() as s:
        s.bind(("127.0.0.1", 0))
        return s.getsockname()[1]


def wait_for(fn, seconds=10):
    end = time.monotonic() + seconds
    while time.monotonic() < end:
        try:
            result = fn()
            if result:
                return result
        except (OSError, RuntimeError, subprocess.CalledProcessError):
            pass
        time.sleep(.03)
    raise AssertionError("timed out waiting for condition")


class SimulatorTest(unittest.TestCase):
    def test_profile_matches_current_header(self):
        profile = json.loads((ROOT / "uz_cli/channel_mappings/default.json").read_text())
        header = (ROOT / "vitis/software/Baremetal/src/include/javascope.h").read_text()
        for field, enum in [("commands", "gui_button_mapping"), ("observables", "JS_OberservableData"), ("slow_signals", "JS_SlowData")]:
            body = re.search(r"enum " + enum + r"\s*\{(.*?)\}", header, re.S)[1]
            expected = {}
            value = 0
            for token in body.split(","):
                token = token.strip()
                if "=" in token:
                    token, number = token.split("=")
                    value = int(number)
                if "ENDMARKER" not in token:
                    expected[token] = value
                value += 1
            self.assertEqual(profile[field], expected)
        self.assertEqual(server_module.CMD_ERROR_RESET, profile["commands"]["Error_Reset"])

    def test_platform_state_wire_bits(self):
        model = server_module.UltraZohmModel(1000, 50, 1, 17)
        for state in range(4):
            model.current_state = state
            for ready in [False, True]:
                model.ready_led = ready
                status = model.build_status_word()
                self.assertEqual(status >> 30, state)
                self.assertEqual(bool(status & 1), ready)

    def test_fragmented_and_coalesced_commands(self):
        m = server_module.UltraZohmModel(1000, 50, 1, 17)
        raw = struct.pack("<IfIfIf", 4, 12.5, 201, 3., 25, 0.)
        for b in raw[:11]:
            m.process_command_bytes(bytes([b]))
        m.process_command_bytes(raw[11:])
        self.assertEqual(m.send_fields[1], 12.5)
        self.assertEqual(m.selected_observables[0], 3)
        self.assertTrue(m.user_led)
        self.assertEqual(m.command_buffer, b"")
        self.assertEqual(m.get_observable_value(28), 0)
        self.assertEqual(m.get_slow_data_value(7), 0)


@unittest.skipUnless(importlib.util.find_spec("ultrazohm"), "install native wheel for Python CLI tests")
class PythonCLITest(unittest.TestCase):
    def test_module_help_version_and_parse_errors(self):
        for args, expected in [(["--help"], 0), (["--version"], 0), (["not-a-command"], 2)]:
            result=subprocess.run([sys.executable,"-m","ultrazohm",*args],capture_output=True,text=True,timeout=10)
            self.assertEqual(result.returncode, expected, result.stderr)
        result=subprocess.run([sys.executable,"-m","ultrazohm","profile"],capture_output=True,text=True,timeout=10)
        self.assertEqual(result.returncode,0,result.stderr)
        self.assertEqual(len(json.loads(result.stdout)["initial_channels"]),20)

    def test_help_returns_without_exiting_interpreter(self):
        code="from ultrazohm._native import cli_main; assert cli_main(['ultrazohm', '--help']) == 0; print('INTERPRETER_ALIVE')"
        result=subprocess.run([sys.executable,"-c",code],capture_output=True,text=True,timeout=10)
        self.assertEqual(result.returncode,0,result.stderr)
        self.assertIn("INTERPRETER_ALIVE", result.stdout)


@unittest.skipUnless(BIN.exists(), "build Rust CLI first")
class IntegrationTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.endpoint = f"127.0.0.1:{port()}"
        self.device_port = port()
        self.processes = []
        self.addCleanup(self.cleanup_processes)

    def cleanup_processes(self):
        for p in reversed(self.processes):
            if p.poll() is None:
                p.terminate()
            try:
                p.wait(timeout=8)
            except subprocess.TimeoutExpired:
                p.kill()
                p.wait()

    def spawn(self, args):
        p = subprocess.Popen([str(x) for x in args], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        self.processes.append(p)
        return p

    def cli(self, *args):
        p = subprocess.run([str(BIN), "--endpoint", self.endpoint, *args], text=True, capture_output=True, timeout=8)
        if p.returncode:
            raise RuntimeError(p.stderr)
        return json.loads(p.stdout)

    def config_file(self, name, data):
        path = Path(self.tmp.name)/name
        path.write_text(json.dumps(data))
        return path

    def runtime_profile(self, initial_channels):
        data = json.loads((ROOT/"uz_cli/profiles/standard.json").read_text())
        data["initial_channels"] = initial_channels
        return data

    def start(self, legacy=False, ack="off", format="both", interactive=False, logging=True,
              profile=None, mapping=None, data_options=None):
        self.server = self.spawn([sys.executable, ROOT/"javascope/test_server.py", "--port", self.device_port,
                                 "--sample-rate", 1000, *(["--legacy-ack"] if legacy else [])])
        def ready():
            with socket.create_connection(("127.0.0.1", self.device_port), timeout=.1):
                return True
        wait_for(ready)
        self.run_dir = Path(self.tmp.name)/"run"
        args = [BIN,"--endpoint",self.endpoint,"serve","--device",f"127.0.0.1:{self.device_port}",
                "--output",self.run_dir,"--format",format,"--ack",ack]
        # Most fixtures need multiple chunks within seconds, independently of production defaults.
        if data_options is None:
            data_options = ("--segment-rows", "4096", "--flush-interval-ms", "500")
        args += list(data_options)
        if legacy and profile is None:
            profile = self.runtime_profile({})
        if profile is not None:
            args += ["--profile", self.config_file("profile.json", profile)]
        if mapping is not None:
            args += ["--channel-mapping", self.config_file("mapping.json", mapping)]
        if interactive:
            # The test polls the service before collecting prompt output. An
            # unread PIPE can fill (especially on Windows) and block the prompt
            # before it executes the commands the test is waiting for.
            self.interactive_stdout = tempfile.TemporaryFile(mode="w+t", encoding="utf-8")
            self.interactive_stderr = tempfile.TemporaryFile(mode="w+t", encoding="utf-8")
            self.addCleanup(self.interactive_stdout.close)
            self.addCleanup(self.interactive_stderr.close)
            self.service = subprocess.Popen([str(x) for x in [*args, "--interactive"]],
                                            stdin=subprocess.PIPE, stdout=self.interactive_stdout,
                                            stderr=self.interactive_stderr, text=True)
            self.processes.append(self.service)
            self.addCleanup(self.service.stdin.close)
        else:
            self.service = self.spawn(args)
        wait_for(lambda:self.cli("status"))
        if logging:
            if not legacy:
                self.cli("set-observable", "lifecheck", "1")
                self.cli("set-observable", "ISR_Period_us", "2")
            self.cli("start-logging")
            self.cli("start-logging-slow-data")

    @unittest.skipUnless(importlib.util.find_spec("ultrazohm"), "install native wheel for duration test")
    def test_default_buffer_duration_uses_configured_sample_period(self):
        from ultrazohm import Acquisition, Client
        profile = self.runtime_profile({})
        profile['sample_period_us'] = 10.0
        path = self.config_file('100khz.json', profile)
        for index, (extra, expected) in enumerate((({}, 3_000_000), ({'buffer_samples': 17}, 17))):
            acquisition = Acquisition(endpoint=self.endpoint, profile=str(path),
                                      output=str(Path(self.tmp.name)/f'duration-{index}'), **extra)
            try:
                self.assertEqual(Client(self.endpoint).status()['data_options']['buffer_samples'], expected)
            finally:
                acquisition.close()

    def test_service_catalog_matches_loaded_mapping(self):
        self.start(logging=False)
        catalog = self.cli('catalog')
        self.assertFalse(catalog['device_readback'])
        mapping = json.loads((ROOT/'uz_cli/channel_mappings/default.json').read_text())
        for field in ('observables', 'slow_signals', 'variables', 'commands'):
            self.assertEqual(catalog['profile'][field], mapping[field])
        self.assertEqual(catalog['profile']['channels'], 20)

    def test_fragmented_control_request(self):
        self.spawn([BIN, '--endpoint', self.endpoint, 'serve',
                    '--output', Path(self.tmp.name) / 'fragmented-control'])
        wait_for(lambda: self.cli('status'))
        host, port_text = self.endpoint.rsplit(':', 1)
        with socket.create_connection((host, int(port_text)), timeout=3) as sock:
            # Let accept run before sending, then split the JSON and newline.
            # Windows inherits nonblocking mode from the listener unless reset.
            time.sleep(.1)
            sock.sendall(b'{"api_version":1,"command":')
            time.sleep(.1)
            sock.sendall(b'{"op":"status"}}')
            time.sleep(.1)
            sock.sendall(b'\n')
            with sock.makefile('rb') as response:
                reply = json.loads(response.readline())
            self.assertTrue(reply['ok'])
            self.assertFalse(reply['state']['connected'])
        self.assertTrue(self.cli('status')['ok'])

    @unittest.skipUnless(importlib.util.find_spec("ultrazohm"), "install native wheel for snapshot test")
    def test_live_snapshot_without_logging_and_cli_preview(self):
        from ultrazohm import Client
        import polars as pl
        self.start(logging=False, data_options=("--buffer-samples", "960"))
        client = Client(self.endpoint)
        wait_for(lambda: client.status()["buffer_available_samples"] == 960)
        first = client.get_live_data(953)  # Exercise non-frame-aligned reads and >64 KiB responses.
        saved = first.clone()
        self.assertEqual(first.height, 953)
        self.assertEqual(first.columns[:3], ["time", "status", "JSO_ISR_ExecTime_us"])
        self.assertEqual(first.schema["status"], pl.UInt32)
        self.assertEqual(first.schema["JSO_lifecheck"], pl.Float32)
        self.assertTrue(first["time"].is_sorted())
        wait_for(lambda: client.status()["state"]["samples"] > 1500)
        second = client.get_live_data(953)
        self.assertGreater(second["time"][-1], first["time"][-1])
        self.assertTrue(first.equals(saved))
        self.assertFalse(list(self.run_dir.glob("*.parquet")))
        with self.assertRaisesRegex(RuntimeError, "only 960 available"):
            client.get_live_data(961)
        for count in (0, -1, True, 1.5):
            with self.assertRaises(ValueError):
                client.get_live_data(count)
        result = subprocess.run([str(BIN), "--endpoint", self.endpoint, "get-live-data",
                                 "--last-n-samples", "30"], capture_output=True, text=True, timeout=10)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("30 rows", result.stdout)
        self.assertIn("JSO_lifecheck", result.stdout)
        self.assertLess(len(result.stdout.splitlines()), 30)
        # Old buffered channels are discarded when requested assignments change.
        client.set_observable("lifecheck", 1)
        wait_for(lambda: client.status()["buffer_available_samples"] >= 15)
        remapped = client.get_live_data(15)
        self.assertEqual(remapped.columns[2], "JSO_lifecheck")
        self.assertEqual(remapped.columns.count("JSO_lifecheck"), 1)

    @unittest.skipUnless(importlib.util.find_spec("ultrazohm"), "install native wheel for recording test")
    def test_python_configurable_buffers_and_recording_reads(self):
        import polars as pl
        from ultrazohm import Acquisition, Client
        self.spawn([sys.executable, ROOT/"javascope/test_server.py", "--port", self.device_port,
                    "--sample-rate", "1000"])
        def ready():
            with socket.create_connection(("127.0.0.1", self.device_port), timeout=.1):
                return True
        wait_for(ready)
        output = Path(self.tmp.name)/"configured"
        a = Acquisition(f"127.0.0.1:{self.device_port}", endpoint=self.endpoint, output=str(output),
                        buffer_samples=17, segment_rows=31, flush_interval_ms=10000)
        client = Client(self.endpoint)
        try:
            wait_for(lambda: client.status()["buffer_available_samples"] == 17)
            self.assertEqual(client.get_live_data(17).height, 17)
            with self.assertRaisesRegex(RuntimeError, "only 17 available"):
                client.get_live_data(18)
            with self.assertRaisesRegex(RuntimeError, "close"):
                a.read_recording()
            client.start_logging()
            client.start_logging_slow_data()
            wait_for(lambda: len(list(output.glob("data-part-*.parquet"))) >= 2)
            for part in sorted(output.glob("data-part-*.parquet"))[:2]:
                self.assertEqual(pl.read_parquet(part).height, 45)
            client.stop_logging()
            wait_for(lambda: client.status()["logging"]["fast"]["phase"] == "complete")
            client.start_logging()
            wait_for(lambda: list(output.glob("data_0002-part-*.parquet")))
        finally:
            a.close()
        for stream, recording, filename in [("fast", 1, "data.parquet"),
                                             ("fast", 2, "data_0002.parquet"),
                                             ("slow", 1, "data_slow_data.parquet")]:
            actual=a.read_recording(stream, recording)
            if stream == "fast":
                self.assertTrue(actual.equals(pl.read_parquet(output/filename)))
            else:
                self.assertEqual(actual.columns,["time","status","observable","slow_id","slow_raw","slow_value"])
                self.assertEqual(actual.height,json.loads((output/"data_slow_data.json").read_text())["rows"])
        with self.assertRaises(RuntimeError):
            a.read_recording(recording=3)
        with self.assertRaisesRegex(ValueError, "stream"):
            a.read_recording("invalid")
        with self.assertRaisesRegex(ValueError, "positive"):
            a.read_recording(recording=0)
        metadata = output/"data.recording.json"
        info = json.loads(metadata.read_text())
        info["info"]["complete"] = False
        metadata.write_text(json.dumps(info))
        with self.assertRaisesRegex(RuntimeError, "not complete"):
            a.read_recording()

    def test_cli_flush_interval_and_invalid_buffer_options(self):
        for option in ("--buffer-samples", "--segment-rows", "--flush-interval-ms"):
            result = subprocess.run([str(BIN), "--endpoint", self.endpoint, "serve", option, "0",
                                     "--output", str(Path(self.tmp.name)/option[2:])],
                                    capture_output=True, text=True, timeout=10)
            self.assertNotEqual(result.returncode, 0)
            self.assertIn("positive", result.stderr)
        self.spawn([sys.executable, ROOT/"javascope/test_server.py", "--port", self.device_port,
                    "--sample-rate", "1000"])
        def ready():
            with socket.create_connection(("127.0.0.1", self.device_port), timeout=.1):
                return True
        wait_for(ready)
        output = Path(self.tmp.name)/"timed"
        self.spawn([BIN, "--endpoint", self.endpoint, "serve", "--device", f"127.0.0.1:{self.device_port}",
                    "--buffer-samples", "25", "--segment-rows", "1000000", "--flush-interval-ms", "50",
                    "--output", output])
        wait_for(lambda: self.cli("status"))
        self.cli("start-logging")
        wait_for(lambda: list(output.glob("data-part-*.parquet")))
        status = self.cli("status")
        self.assertEqual(status["data_options"], {"recording_backend": "parquet", "buffer_samples": 25, "segment_rows": 1000000, "flush_interval_ms": 50})
        self.assertLessEqual(status["buffer_available_samples"], 25)
        self.cli("shutdown")

    @unittest.skipUnless(importlib.util.find_spec("polars"), "install polars for segment reads")
    def test_default_recording_flushes_on_stop_before_interval(self):
        import polars as pl
        self.start(logging=False, format="parquet", data_options=())
        self.assertEqual(self.cli("status")["data_options"],
                         {"recording_backend": "parquet", "buffer_samples": 300_000, "segment_rows": 1_000_000, "flush_interval_ms": 60_000})
        before = self.cli("status")["state"]["samples"]
        self.cli("start-logging")
        wait_for(lambda: self.cli("status")["state"]["samples"] >= before + 1500)
        self.assertFalse(list(self.run_dir.glob("*.parquet")))
        self.cli("stop-logging")
        wait_for(lambda: self.cli("status")["logging"]["fast"]["phase"] == "complete")
        data = pl.read_parquet(self.run_dir/"data.parquet")
        self.assertGreater(data.height, 0)
        self.assertEqual(data.height, json.loads((self.run_dir/"data.json").read_text())["rows"])
        self.assertTrue(self.cli("status")["state"]["connected"])

    @unittest.skipUnless(importlib.util.find_spec("polars"), "install polars for segment reads")
    def test_row_flush_resets_interval_timer(self):
        import polars as pl
        self.start(logging=False, data_options=("--segment-rows", "300", "--flush-interval-ms", "500"))
        self.cli("start-logging")
        wait_for(lambda: len(list(self.run_dir.glob("data-part-*.parquet"))) >= 3)
        for part in sorted(self.run_dir.glob("data-part-*.parquet"))[:3]:
            self.assertEqual(pl.read_parquet(part).height, 300)

    @unittest.skipUnless(importlib.util.find_spec("ultrazohm"), "install native wheel for offline test")
    def test_live_data_offline_and_invalid_python_configuration(self):
        from ultrazohm import Acquisition, Client
        for option in ("buffer_samples", "segment_rows", "flush_interval_ms"):
            with self.assertRaisesRegex(RuntimeError, "positive"):
                Acquisition(endpoint=self.endpoint, **{option: 0})
        a = Acquisition(endpoint=self.endpoint, output=str(Path(self.tmp.name)/"offline-snapshot"))
        try:
            self.assertEqual(Client(self.endpoint).status()["data_options"],
                             {"recording_backend": "parquet", "buffer_samples": 300_000, "segment_rows": 1_000_000, "flush_interval_ms": 60_000})
            with self.assertRaisesRegex(RuntimeError, "not connected"):
                Client(self.endpoint).get_live_data(1)
        finally:
            a.close()
        with self.assertRaises(RuntimeError):
            a.read_recording()  # No recording was started.

    @unittest.skipUnless(importlib.util.find_spec("ultrazohm"), "install wheel for data API tests")
    def test_history_reads_unflushed_data_beyond_live_ring(self):
        from ultrazohm import Client, Recording
        self.start(logging=False, format="parquet", data_options=(
            "--buffer-samples", "17", "--segment-rows", "100000", "--flush-interval-ms", "60000"))
        client = Client(self.endpoint)
        client.start_logging()
        info = wait_for(lambda: (i if (i := client.data_info(recording=1))["start"] is not None
                                and i["stop"] - i["start"] >= 150 else None))
        self.assertIsNone(info["persisted_stop"])
        self.assertFalse(list(self.run_dir.glob("data-part-*.parquet")))
        start, stop = info["start"], info["stop"]
        df = client.read_range(start, stop, recording=1)
        self.assertEqual(df.height, stop-start)
        self.assertEqual(df["time"].to_list(), [i*100.*1e-6 for i in range(start, stop)])
        self.assertTrue(client.tail(150, recording=1).height == 150)
        with self.assertRaises(RuntimeError):
            client.read_range(start, stop)
        handle = Recording(client.status()["logging"]["fast"]["handle"])
        self.assertIsNone(handle.info()["stop"])
        client.stop_logging()
        wait_for(lambda: client.status()["logging"]["fast"]["phase"] == "complete")
        self.assertTrue(handle.info()["complete"])
        self.assertTrue(handle.read_range(start, stop).equals(df))

    @unittest.skipUnless(importlib.util.find_spec("ultrazohm"), "install wheel for data API tests")
    def test_history_pages_cross_persisted_pending_and_finalized_ranges(self):
        import polars as pl
        from ultrazohm import Client, Recording
        self.start(logging=False, format="both", data_options=(
            "--buffer-samples", "17", "--segment-rows", "300", "--flush-interval-ms", "60000"))
        client = Client(self.endpoint)
        client.start_logging()
        client.start_logging_slow_data()
        info = wait_for(lambda: (i if (i := client.data_info(recording=1))["persisted_stop"] is not None
                                and i["stop"] - i["persisted_stop"] >= 60 else None))
        start, boundary, stop = info["start"], info["persisted_stop"], info["stop"]
        mixed = client.read_range(boundary-13, stop, recording=1)
        self.assertEqual(mixed.height, stop-boundary+13)
        self.assertEqual(mixed["time"].to_list(), [i*100.*1e-6 for i in range(boundary-13,stop)])
        selected = client.read_range(start, stop, recording=1, channels=["JSO_lifecheck"])
        self.assertEqual(selected.columns, ["time", "status", "JSO_lifecheck"])
        slow = client.read_since(stream="slow", recording=1, limit=100)
        self.assertEqual(slow.data.columns, ["time", "status", "observable", "slow_id", "slow_raw", "slow_value"])
        self.assertGreater(slow.data.height, 0)
        slow_values = slow.data["slow_value"].to_list()
        client.stop_logging()
        client.stop_logging_slow_data()
        wait_for(lambda: all(client.status()["logging"][s]["phase"] == "complete" for s in ("fast", "slow")))
        final = client.data_info(recording=1)
        cursor, frames, expected = None, [], final["start"]
        while expected < final["stop"]:
            page = client.read_since(cursor, limit=73, recording=1)
            self.assertEqual(page.start, expected)
            self.assertEqual(page.data.height, page.stop-page.start)
            expected, cursor = page.stop, page.cursor
            frames.append(page.data)
        self.assertEqual(client.read_since(cursor, limit=73).data.height, 0)
        merged = pl.concat(frames)
        self.assertTrue(merged.equals(pl.read_parquet(self.run_dir/"data.parquet")))
        self.assertTrue(client.read_range(boundary-13, stop, recording=1).equals(mixed))
        handle = Recording(client.status()["logging"]["fast"]["handle"])
        self.assertTrue(handle.read().equals(merged))
        self.assertTrue(client.recordings()[0]["complete"])
        raw_slow = Recording(client.status()["logging"]["slow"]["handle"])
        self.assertEqual(raw_slow.read_range(slow.start,slow.stop)["slow_value"].to_list(),slow_values)
        # A second recording and a changed live mapping do not relabel the first run.
        client.set_observable("lifecheck",1)
        self.assertTrue(client.read_range(boundary-13, stop, recording=1).equals(mixed))
        client.start_logging()
        wait_for(lambda: client.data_info(recording=2)["stop"] is not None)
        client.stop_logging()
        wait_for(lambda: client.status()["logging"]["fast"]["phase"] == "complete")
        self.assertEqual(len(client.recordings()),3)
        client.shutdown()
        self.assertEqual(self.service.wait(timeout=8),0)
        self.assertTrue(Recording(handle.path).read().equals(merged))

    @unittest.skipUnless(importlib.util.find_spec("ultrazohm"), "install wheel for data API tests")
    def test_data_cursors_expire_and_validate_source_identity(self):
        from ultrazohm import Client
        self.start(logging=False, data_options=("--buffer-samples", "17"))
        client = Client(self.endpoint)
        wait_for(lambda: client.data_info()["stop"] is not None)
        page = client.read_since(limit=10)
        time.sleep(.08)
        with self.assertRaisesRegex(RuntimeError,"unavailable"):
            client.read_since(page.cursor)
        cursor = client.read_since().cursor
        client.set_observable("lifecheck",1)
        with self.assertRaisesRegex(RuntimeError,"generation"):
            client.read_since(cursor)
        wait_for(lambda: client.data_info()["stop"] is not None)
        cursor = client.read_since().cursor
        wrong = dict(cursor,run_id="another acquisition")
        with self.assertRaisesRegex(RuntimeError,"different run"):
            client.read_since(wrong)
        with self.assertRaisesRegex(RuntimeError,"does not exist"):
            client.data_info(recording=1)
        for value in (0,-1,True):
            with self.assertRaises(ValueError):
                client.tail(value)
        with self.assertRaises(RuntimeError):
            client.read_range(20,10)
        with self.assertRaises(ValueError):
            client.data_info(stream="missing")
        with self.assertRaises(RuntimeError):
            client.tail(1,channels=["missing"])
        # Exercise CLI metadata, query parsing, cursor output, and bounded preview.
        self.assertIn("info",self.cli("data-info"))
        result = subprocess.run([str(BIN),"--endpoint",self.endpoint,"read-since","--limit","10"],capture_output=True,text=True,timeout=8)
        self.assertEqual(result.returncode,0,result.stderr)
        self.assertIn("cursor",json.loads(result.stdout.splitlines()[0]))
        self.assertIn("10 rows",result.stdout)

    @unittest.skipUnless(importlib.util.find_spec("ultrazohm"), "install wheel for projection tests")
    def test_projection_across_disk_pending_ram_and_completed_handles(self):
        from ultrazohm import Client, Recording
        self.start(logging=False, format="parquet", data_options=(
            "--buffer-samples", "17", "--segment-rows", "300", "--flush-interval-ms", "60000"))
        client=Client(self.endpoint)
        client.start_logging()
        client.start_logging_slow_data()
        info=wait_for(lambda: (i if (i:=client.data_info(recording=1))["persisted_stop"] is not None
                              and i["stop"]-i["persisted_stop"]>=60 else None))
        lo,hi=info["persisted_stop"]-13,info["stop"]
        full=client.read_range(lo,hi,recording=1)
        channels=["JSO_lifecheck","JSO_ISR_ExecTime_us","JSO_lifecheck","time"]
        names=["time","status","JSO_lifecheck","JSO_ISR_ExecTime_us"]
        self.assertTrue(client.read_range(lo,hi,recording=1,channels=channels).equals(full.select(names)))
        self.assertTrue(client.read_range(lo,hi,recording=1,channels=[]).equals(full.select("time","status")))
        self.assertEqual(client.read_range(lo,lo,recording=1,channels=channels).schema,full.select(names).schema)
        page=client.read_since(recording=1,limit=31,channels=channels)
        self.assertEqual(page.data.columns,names)
        self.assertEqual(client.read_since(page.cursor,limit=31,channels=channels).start,page.stop)
        self.assertEqual(client.tail(1,channels=channels).columns,names)
        slow_info=wait_for(lambda:(i if (i:=client.data_info(stream="slow",recording=1))["persisted_stop"] is not None
                                   and i["stop"]-i["persisted_stop"]>=30 else None))
        slow_lo,slow_hi=slow_info["persisted_stop"]-7,slow_info["stop"]
        slow_full=client.read_range(slow_lo,slow_hi,stream="slow",recording=1)
        slow_names=["time","status","slow_value","observable","slow_id"]
        self.assertTrue(client.read_range(slow_lo,slow_hi,stream="slow",recording=1,
                                         channels=slow_names[2:]).equals(slow_full.select(slow_names)))
        client.stop_logging()
        client.stop_logging_slow_data()
        wait_for(lambda:all(client.status()["logging"][s]["phase"]=="complete" for s in ("fast","slow")))
        handles={s:Recording(client.status()["logging"][s]["handle"]) for s in ("fast","slow")}
        self.assertTrue(handles["fast"].read_range(lo,hi,channels=channels).equals(full.select(names)))
        self.assertTrue(handles["slow"].read_range(slow_lo,slow_hi,channels=slow_names[2:]).equals(slow_full.select(slow_names)))
        projected=handles["fast"].read(channels=["JSO_lifecheck"])
        self.assertTrue(projected.equals(handles["fast"].read().select("time","status","JSO_lifecheck")))
        for read in (lambda:client.read_range(lo,lo,recording=1,channels=["missing"]),
                     lambda:handles["fast"].read_range(lo,lo,channels=["missing"])):
            with self.assertRaisesRegex(RuntimeError,"unknown recording column"):
                read()
        result=subprocess.run([str(BIN),"--endpoint",self.endpoint,"read-range",str(lo),str(hi),
                               "--recording","1","--channels","JSO_lifecheck"],capture_output=True,text=True,timeout=8)
        self.assertEqual(result.returncode,0,result.stderr)
        self.assertIn("3 columns",result.stdout)

    def test_offline_retry_connect_and_log(self):
        self.run_dir=Path(self.tmp.name)/'offline'
        service=self.spawn([BIN,'--endpoint',self.endpoint,'serve','--output',self.run_dir,'--format','both'])
        status=wait_for(lambda:self.cli('status'))
        self.assertFalse(status['state']['connected'])
        self.assertIsNone(status['state']['device'])
        self.assertIsNone(status['state']['platform_state'])
        self.assertTrue(all(c['state']=='unknown' for c in self.cli('observables')['channels']))
        for command in [('start-logging',),('start-logging-slow-data',),('stop',),('set-observable','lifecheck','1')]:
            with self.assertRaisesRegex(RuntimeError,'not connected'):
                self.cli(*command)
        self.cli('send-ack','on'); self.cli('send-ack','off')
        with self.assertRaisesRegex(RuntimeError, f'could not connect to device 127.0.0.1:{self.device_port}'):
            self.cli('connect','127.0.0.1',str(self.device_port))
        with self.assertRaisesRegex(RuntimeError,'numeric'):
            self.cli('connect','invalid-ip','1000')
        with self.assertRaisesRegex(RuntimeError,'port'):
            self.cli('connect','127.0.0.1','0')
        time.sleep(5.1)
        self.assertIsNone(service.poll())
        self.assertFalse(self.cli('status')['state']['connected'])
        self.spawn([sys.executable,ROOT/'javascope/test_server.py','--port',self.device_port,'--sample-rate',1000])
        def ready():
            with socket.create_connection(('127.0.0.1',self.device_port),timeout=.1): return True
        wait_for(ready)
        self.cli('connect','127.0.0.1',str(self.device_port))
        state=wait_for(lambda:(s if (s:=self.cli('status')['state'])['frames'] else None))
        self.assertTrue(state['connected'])
        self.assertEqual(state['commands_sent'],20)
        self.assertEqual(state['device'],f'127.0.0.1:{self.device_port}')
        self.assertEqual(self.cli('observables')['channels'][2]['name'],'JSO_lifecheck')
        with self.assertRaisesRegex(RuntimeError,'already connected'):
            self.cli('connect')
        self.cli('start-logging');time.sleep(.2)
        self.cli('shutdown');self.assertEqual(service.wait(timeout=10),0)
        self.assertTrue((self.run_dir/'data.parquet').exists())
        self.assertIn('JSO_lifecheck',(self.run_dir/'data.csv').read_text().splitlines()[0])
    def test_explicit_platform_state_feedback(self):
        self.start()
        wait_for(lambda: self.cli("status")["state"]["platform_state"] == "idle")
        self.cli("enable-system")
        wait_for(lambda: self.cli("status")["state"]["platform_state"] == "running")
        self.cli("enable-control")
        wait_for(lambda: self.cli("status")["state"]["platform_state"] == "control")
        self.cli("button", "1")  # Simulator's error injection.
        wait_for(lambda: self.cli("status")["state"]["platform_state"] == "error")
        self.cli("stop")
        wait_for(lambda: self.cli("status")["state"]["platform_state"] == "idle")

    def test_platform_state_names_from_channel_mapping(self):
        mapping = json.loads((ROOT/"uz_cli/channel_mappings/default.json").read_text())
        mapping["platform_state"]["values"] = {
            "0": "waiting", "1": "enabled", "2": "regulating", "3": "fault"
        }
        self.start(mapping=mapping, logging=False)
        wait_for(lambda: self.cli("status")["state"]["platform_state"] == "waiting")
        self.cli("enable-system")
        wait_for(lambda: self.cli("status")["state"]["platform_state"] == "enabled")
        self.cli("enable-control")
        wait_for(lambda: self.cli("status")["state"]["platform_state"] == "regulating")
        self.cli("button", "1")
        wait_for(lambda: self.cli("status")["state"]["platform_state"] == "fault")

    def test_default_interactive_session(self):
        result = subprocess.run(
            [str(BIN), "--endpoint", self.endpoint], cwd=self.tmp.name,
            input="status\nshutdown\n", text=True, capture_output=True, timeout=10)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("ultrazohm>", result.stdout)
        self.assertIn('"connected": false', result.stdout)
        directories = list(Path(self.tmp.name).glob("artifacts/live_logs/*"))
        self.assertEqual(len(directories), 1)
        self.assertRegex(directories[0].name, r"^\d{8}-\d{6}-\d{9}Z$")
        metadata = json.loads((directories[0]/"run.json").read_text())
        self.assertEqual(metadata["format"], "both")
        self.assertIsNone(metadata["device"])
        self.assertFalse(list(directories[0].glob("*.parquet")))
        self.assertFalse(list(directories[0].glob("*.csv")))
        self.assertTrue(json.loads((directories[0]/"end.json").read_text())["complete"])

    def test_default_output_from_repository_subdirectory(self):
        root = Path(self.tmp.name)
        (root / "tcl_scripts").mkdir()
        (root / "tcl_scripts/vitis_headless.tcl").touch()
        (root / "vitis/software").mkdir(parents=True)
        nested = root / "uz_cli/nested"
        nested.mkdir(parents=True)
        result = subprocess.run(
            [str(BIN), "--endpoint", self.endpoint, "serve", "--interactive"],
            cwd=nested, input="shutdown\n", text=True, capture_output=True, timeout=10)
        self.assertEqual(result.returncode, 0, result.stderr)
        directories = list((root / "artifacts/live_logs").iterdir())
        self.assertEqual(len(directories), 1)
        self.assertTrue((directories[0] / "run.json").is_file())
        self.assertFalse((nested / "artifacts").exists())

    def test_offline_interactive_shutdown(self):
        result=subprocess.run([str(BIN),'--endpoint',self.endpoint,'serve','--interactive'],input='status\nshutdown\n',text=True,capture_output=True,timeout=10)
        self.assertEqual(result.returncode,0,result.stderr)
        self.assertIn('"connected": false',result.stdout)

    def test_interactive_commands_and_finalization(self):
        self.start(interactive=True)
        # Exercise output larger than a small pipe before checking command effects.
        self.service.stdin.write("help\n" * 4 + "unknown-command\nset-variable missing 1\n"
                                 "serve\nset_variable send_field_1 -12.5\n"
                                 "set-observable lifecheck 1\nsend_ack on\nbutton 2\n")
        self.service.stdin.flush()
        wait_for(lambda: self.cli("status")["state"]["status"] & 8)
        wait_for(lambda: self.cli("status")["state"]["ack_sent"] > 2)
        # Ordinary clients remain usable alongside the prompt.
        self.cli("button", "3")
        wait_for(lambda: not (self.cli("status")["state"]["status"] & 8))
        self.service.stdin.write("stop\nstatus\nobservables\n")
        self.service.stdin.flush()
        wait_for(lambda: self.cli("status")["state"]["commands_sent"] >= 5)
        self.assertIsNone(self.service.poll())
        self.service.communicate("shutdown\n", timeout=15)
        self.interactive_stdout.seek(0)
        self.interactive_stderr.seek(0)
        stdout, stderr = self.interactive_stdout.read(), self.interactive_stderr.read()
        self.assertEqual(self.service.returncode, 0, stderr)
        self.assertIn("ultrazohm> ", stdout)
        self.assertIn("sent_unconfirmed", stdout)
        self.assertIn("service_requested_assignments", stdout)
        self.assertIn("unknown-command", stderr)
        self.assertIn("serve cannot be started", stderr)
        events = [json.loads(line) for line in (self.run_dir/"commands.jsonl").read_text().splitlines()]
        self.assertTrue(any(event["wire"] == [4, -12.5] for event in events))
        self.assertTrue((self.run_dir/"data.parquet").is_file())
        self.assertTrue((self.run_dir/"data.csv").is_file())
        self.assertTrue(json.loads((self.run_dir/"end.json").read_text())["complete"])

    def test_interactive_eof_finalizes(self):
        self.start(interactive=True)
        wait_for(lambda: self.cli("status")["state"]["samples"] >= 30)
        self.service.communicate("", timeout=15)
        self.interactive_stderr.seek(0)
        stderr = self.interactive_stderr.read()
        self.assertEqual(self.service.returncode, 0, stderr)
        self.assertTrue((self.run_dir/"data.parquet").is_file())
        self.assertTrue((self.run_dir/"data.csv").is_file())

    def test_interactive_external_shutdown_does_not_wait_for_stdin(self):
        self.start(interactive=True)
        self.cli("shutdown")
        self.assertEqual(self.service.wait(timeout=15), 0)
        self.assertTrue((self.run_dir/"data.parquet").is_file())

    @unittest.skipIf(os.name == "nt", "Unix SIGINT; Windows console events need a console fixture")
    def test_interactive_ctrl_c_finalizes(self):
        self.start(interactive=True)
        wait_for(lambda: self.cli("status")["state"]["samples"] >= 30)
        self.service.send_signal(signal.SIGINT)
        self.assertEqual(self.service.wait(timeout=15), 0)
        self.assertTrue(json.loads((self.run_dir/"end.json").read_text())["complete"])
        self.assertTrue((self.run_dir/"data.parquet").is_file())
        self.assertTrue((self.run_dir/"data.csv").is_file())

    def test_interactive_disconnect_does_not_wait_for_stdin(self):
        self.start(interactive=True)
        wait_for(lambda: self.cli("status")["state"]["samples"] >= 30)
        self.server.terminate()
        self.server.wait(timeout=5)
        self.assertNotEqual(self.service.wait(timeout=15), 0)
        self.assertFalse(json.loads((self.run_dir/"end.json").read_text())["complete"])
        self.assertTrue((self.run_dir/"data.parquet").is_file())

    def test_default_initial_channels_and_exports(self):
        self.start(logging=False)
        channels=self.cli("observables")["channels"]
        self.assertEqual([row["id"] for row in channels], list(range(1,21)))
        self.assertTrue(all(row["state"] == "sent_unconfirmed" for row in channels))
        self.assertEqual(channels[2]["name"], "JSO_lifecheck")
        self.assertEqual(self.cli("status")["state"]["commands_sent"], 20)
        self.assertEqual(self.cli("status")["logging"]["fast"]["phase"], "idle")
        self.assertFalse(list(self.run_dir.glob("*.parquet")))
        events=[json.loads(line) for line in (self.run_dir/"commands.jsonl").read_text().splitlines()]
        self.assertEqual([event["wire"] for event in events], [[200+i, float(i)] for i in range(1,21)])
        self.assertTrue(all(event["source"] == "initial_channels" for event in events))
        profile=self.cli("profile")
        mapping=self.cli("channel-mapping")
        self.assertEqual(len(profile["initial_channels"]), 20)
        self.assertNotIn("observables", profile)
        self.assertNotIn("initial_channels", mapping)
        self.assertEqual(mapping["repository"]["name"], "ultrazohm/ultrazohm_sw")
        self.cli("shutdown")
        self.assertEqual(self.service.wait(timeout=15),0)

    def test_runtime_mapping_and_partial_initial_channels(self):
        mapping=json.loads((ROOT/"uz_cli/channel_mappings/default.json").read_text())
        mapping["observables"]["JSO_MY_NEW_OBSERVABLE"] = 29
        mapping["repository"] = {"name":"my/firmware", "commit":"test-commit"}
        self.start(logging=False, profile=self.runtime_profile({"5":"JSO_MY_NEW_OBSERVABLE"}), mapping=mapping)
        channels=self.cli("observables")["channels"]
        self.assertEqual(channels[4], {"channel":5,"name":"JSO_MY_NEW_OBSERVABLE","id":29,"state":"sent_unconfirmed"})
        self.assertTrue(all(row["state"] == "unknown" for row in channels if row["channel"] != 5))
        self.cli("set-observable", "JSO_MY_NEW_OBSERVABLE", "7")
        self.assertEqual(self.cli("observables")["channels"][6]["id"],29)
        events=[json.loads(line) for line in (self.run_dir/"commands.jsonl").read_text().splitlines()]
        self.assertEqual([event["wire"] for event in events], [[205,29.0],[207,29.0]])
        metadata=json.loads((self.run_dir/"run.json").read_text())
        self.assertEqual(metadata["profile"]["repository"], mapping["repository"])
        self.cli("start-logging")
        wait_for(lambda: list(self.run_dir.glob("data-part-*.parquet")))
        self.cli("stop-logging")
        wait_for(lambda: self.cli("status")["logging"]["fast"]["phase"] == "complete")
        import csv
        with (self.run_dir/"data.csv").open() as f:
            self.assertEqual(next(csv.reader(f)), ["time","status","JSO_MY_NEW_OBSERVABLE"])
        self.cli("shutdown")
        self.assertEqual(self.service.wait(timeout=15),0)

    def test_invalid_initial_selection_fails_before_connect(self):
        with socket.socket() as listener:
            listener.bind(("127.0.0.1", self.device_port))
            listener.listen(1)
            listener.settimeout(.1)
            for initial in [{"0":"lifecheck"}, {"21":"lifecheck"}, {"1":"DOES_NOT_EXIST"}]:
                path=self.config_file("invalid.json",self.runtime_profile(initial))
                result=subprocess.run([str(BIN),"--endpoint",self.endpoint,"serve","--device",
                                       f"127.0.0.1:{self.device_port}","--profile",str(path)],
                                      capture_output=True,text=True,timeout=5)
                self.assertNotEqual(result.returncode,0)
                self.assertIn("invalid initial channel",result.stderr)
                with self.assertRaises(socket.timeout):
                    listener.accept()

    def test_observable_assignments_are_session_requests(self):
        self.start(logging=False, profile=self.runtime_profile({}))
        before = self.cli("status")["state"]["commands_sent"]
        initial = self.cli("observables")
        self.assertFalse(initial["device_readback"])
        self.assertEqual([row["channel"] for row in initial["channels"]], list(range(1, 21)))
        self.assertTrue(all(row["state"] == "unknown" and row["name"] is None and row["id"] is None
                            for row in initial["channels"]))
        self.assertEqual(self.cli("status")["state"]["commands_sent"], before)
        with self.assertRaisesRegex(RuntimeError, "select at least one observable"):
            self.cli("start-logging")
        self.cli("set-observable", "lifecheck", "5")
        selected = self.cli("get-observables")
        self.assertEqual(selected["channels"][4], {
            "channel":5, "name":"JSO_lifecheck", "id":3, "state":"sent_unconfirmed"})
        self.cli("set-observable", "JSO_ISR_ExecTime_us", "5")
        selected = self.cli("observables")
        self.assertEqual(selected["channels"][4]["id"], 1)
        self.assertEqual(selected["channels"][4]["name"], "JSO_ISR_ExecTime_us")
        with self.assertRaises(RuntimeError):
            self.cli("set-observable", "missing", "5")
        self.cli("start-logging-slow-data")
        with self.assertRaisesRegex(RuntimeError, "logging is active"):
            self.cli("set-observable", "lifecheck", "5")
        self.assertEqual(self.cli("observables"), selected)
        if importlib.util.find_spec("ultrazohm"):
            from ultrazohm import Client
            self.assertEqual(Client(self.endpoint).observables(), selected)
        self.cli("shutdown")
        self.assertEqual(self.service.wait(timeout=15), 0)

    def test_explicit_independent_logging_and_observable_lock(self):
        self.start(logging=False)
        wait_for(lambda: self.cli("status")["state"]["samples"] >= 60)
        self.assertEqual(self.cli("status")["logging"]["fast"]["phase"], "idle")
        self.assertFalse(list(self.run_dir.glob("*.parquet")))
        self.cli("set-observable", "lifecheck", "1")
        self.cli("start-logging")
        before = self.cli("status")["state"]["commands_sent"]
        with self.assertRaisesRegex(RuntimeError, "setting observable is not possible when logging is active"):
            self.cli("set-observable", "ISR_Period_us", "1")
        self.assertEqual(self.cli("status")["state"]["commands_sent"], before)
        with self.assertRaisesRegex(RuntimeError, "already active"):
            self.cli("start-logging")
        self.cli("start-logging-slow-data")
        wait_for(lambda: list(self.run_dir.glob("data-part-*.parquet")))
        self.cli("stop-logging")
        wait_for(lambda: self.cli("status")["logging"]["fast"]["phase"] == "complete")
        self.assertTrue((self.run_dir/"data.csv").exists())
        self.assertEqual(self.cli("status")["logging"]["slow"]["phase"], "recording")
        with self.assertRaisesRegex(RuntimeError, "logging is active"):
            self.cli("set-observable", "ISR_Period_us", "1")
        snapshot = (self.run_dir/"data.parquet").read_bytes()
        self.cli("stop-logging-slow-data")
        wait_for(lambda: self.cli("status")["logging"]["slow"]["phase"] == "complete")
        with self.assertRaisesRegex(RuntimeError, "not active"):
            self.cli("stop-logging")
        self.cli("set-observable", "ISR_Period_us", "1")
        self.cli("start-logging")
        wait_for(lambda: list(self.run_dir.glob("data_0002-part-*.parquet")))
        self.cli("stop-logging")
        wait_for(lambda: self.cli("status")["logging"]["fast"]["phase"] == "complete")
        self.assertEqual(snapshot, (self.run_dir/"data.parquet").read_bytes())
        self.assertTrue((self.run_dir/"data_0002.parquet").exists())
        self.assertFalse((self.run_dir/"data_0002_slow_data.parquet").exists())
        metadata=json.loads((self.run_dir/"data_0002.json").read_text())
        self.assertEqual(metadata["recording"]["requested_observables"]["1"], "ISR_Period_us")
        import csv
        with (self.run_dir/"data.csv").open() as f:
            first_header=next(csv.reader(f))
        with (self.run_dir/"data_0002.csv").open() as f:
            second_header=next(csv.reader(f))
        self.assertEqual(first_header[2], "JSO_lifecheck")
        self.assertEqual(second_header[2], "JSO_ISR_Period_us")
        self.assertEqual(second_header.count("JSO_ISR_Period_us"), 1)
        self.assertFalse(any(name.startswith("ch_") for name in second_header))
        n=self.cli("status")["state"]["samples"]
        wait_for(lambda: self.cli("status")["state"]["samples"] > n)
        self.cli("shutdown")
        self.assertEqual(self.service.wait(timeout=15), 0)

    def test_slow_only_logging(self):
        self.start(logging=False)
        self.cli("start-logging-slow-data")
        wait_for(lambda: list(self.run_dir.glob("data_slow_data-part-*.parquet")))
        with self.assertRaisesRegex(RuntimeError, "logging is active"):
            self.cli("set-observable", "lifecheck", "1")
        self.cli("stop-logging-slow-data")
        wait_for(lambda: self.cli("status")["logging"]["slow"]["phase"] == "complete")
        self.assertFalse((self.run_dir/"data.parquet").exists())
        self.assertTrue((self.run_dir/"data_slow_data.csv").exists())
        self.cli("shutdown")
        self.assertEqual(self.service.wait(timeout=15), 0)

    def test_control_logging_ack_and_python(self):
        self.start()
        self.assertEqual(self.cli("set_variable", "send_field_1", "-12.5")["outcome"], "sent_unconfirmed")
        with self.assertRaisesRegex(RuntimeError, "setting observable is not possible when logging is active"):
            self.cli("set-observable", "lifecheck", "1")
        for args in [("set-variable","not_real","1"),("set-variable","send_field_1","NaN"),
                     ("set-observable","lifecheck","21"),("error-reset",)]:
            with self.assertRaises(RuntimeError): self.cli(*args)
        self.cli("button","2")
        wait_for(lambda:self.cli("status")["state"]["status"] & 8)
        self.cli("button","3")
        wait_for(lambda:not (self.cli("status")["state"]["status"] & 8))
        self.cli("enable-system")
        self.cli("enable-control")
        wait_for(lambda:self.cli("status")["state"]["status"] & 2)
        self.cli("stop")
        wait_for(lambda:not (self.cli("status")["state"]["status"] & 2))
        self.cli("send_ack","on")
        wait_for(lambda:self.cli("status")["state"]["ack_sent"]>2)
        self.cli("send_ack","off")
        before=self.cli("status")["state"]["ack_sent"]
        time.sleep(.1)
        self.assertLessEqual(self.cli("status")["state"]["ack_sent"],before+1)
        parts = wait_for(lambda:sorted(self.run_dir.glob("data-part-*.parquet")))
        first_part = parts[0]
        snapshot = first_part.read_bytes()
        wait_for(lambda:len(list(self.run_dir.glob("data-part-*.parquet"))) >= 2)
        self.assertEqual(first_part.read_bytes(),snapshot)
        self.assertFalse((self.run_dir/"data.parquet").exists())
        self.assertFalse(list(self.run_dir.glob("*.csv")))
        if importlib.util.find_spec("polars"):
            import polars as pl
            self.assertGreater(pl.read_parquet(first_part).height,0)
        if importlib.util.find_spec("ultrazohm"):
            from ultrazohm import Client
            c=Client(self.endpoint)
            c.set_variable("send_field_2",2.5)
            c.send_ack(True)
            self.assertTrue(c.status()["send_ack"])
        self.cli("shutdown")
        self.assertEqual(self.service.wait(timeout=8),0)
        self.assertEqual(set(p for p in self.run_dir.glob("*.parquet") if "-part-" not in p.name), {self.run_dir/"data.parquet", self.run_dir/"data_slow_data.parquet"})
        snapshot = (self.run_dir/"data.parquet").read_bytes()
        self.assertEqual(snapshot[:4],b"PAR1")
        self.assertEqual(snapshot[-4:],b"PAR1")
        end=json.loads((self.run_dir/"end.json").read_text())
        self.assertTrue(end["complete"],end)
        self.assertFalse(list(self.run_dir.glob("*.partial")))
        self.assertEqual(set(self.run_dir.glob("*.csv")), {self.run_dir/"data.csv", self.run_dir/"data_slow_data.csv"})
        self.assertTrue(list(self.run_dir.glob("*-part-*.parquet")))
        import csv
        rows=[]
        for p in [self.run_dir/"data.csv"]:
            with p.open() as f: rows.extend(csv.DictReader(f))
        self.assertEqual(len(rows),json.loads((self.run_dir/"data.json").read_text())["rows"])
        self.assertNotIn("sample_index", rows[0])
        self.assertNotIn("host_received_unix_ns", rows[0])
        self.assertIn("time", rows[0])
        self.assertTrue(any(float(r["JSO_lifecheck"])>0 for r in rows))
        self.assertTrue(any(float(r["JSO_ISR_Period_us"])==1000 for r in rows))
        if importlib.util.find_spec("polars"):
            import polars as pl
            parquet=pl.read_parquet(self.run_dir/"data.parquet")
            self.assertEqual(parquet.height,len(rows))
            times = parquet["time"].to_list()
            self.assertTrue(all(abs((b-a)-0.0001) < 1e-10 for a,b in zip(times,times[1:])))
            slow = pl.read_parquet(self.run_dir/"data_slow_data.parquet")
            self.assertGreater(slow.height, 0)
            self.assertNotIn("sample_index", slow.columns)
            self.assertNotIn("host_received_unix_ns", slow.columns)
            self.assertIn("time", slow.columns)
            self.assertNotIn("slow_id", parquet.columns)
            self.assertFalse(any(name.startswith("ch_") for name in parquet.columns))
            self.assertEqual(parquet.columns.count("JSO_lifecheck"), 1)
            mapping=json.loads((ROOT/"uz_cli/channel_mappings/default.json").read_text())["slow_signals"]
            names = sorted(mapping, key=mapping.get)
            self.assertEqual(slow.columns, ["time", "status", *names])
            self.assertTrue(all(slow[name].dtype == pl.Float32 for name in names))
            self.assertTrue(all(slow[name].null_count() == 0 for name in names))
            csv_slow = pl.read_csv(self.run_dir/"data_slow_data.csv",
                                   schema_overrides=slow.schema)
            from polars.testing import assert_frame_equal
            assert_frame_equal(csv_slow, slow)
            metadata = json.loads((self.run_dir/"data_slow_data.json").read_text())["recording"]
            self.assertEqual(metadata["slow_layout"], "wide_forward_filled")


    def test_csv_option_retains_final_parquet(self):
        self.start(format="csv")
        wait_for(lambda:list(self.run_dir.glob("data-part-*.parquet")))
        self.assertFalse(list(self.run_dir.glob("*.csv")))
        self.cli("shutdown")
        self.assertEqual(self.service.wait(timeout=8),0)
        self.assertTrue((self.run_dir/"data.parquet").is_file())
        self.assertTrue((self.run_dir/"data.csv").is_file())
        self.assertTrue(list(self.run_dir.glob("*-part-*.parquet")))

    def test_csv_export_failure_retains_final_parquet_and_segments(self):
        self.start(format="csv")
        wait_for(lambda:list(self.run_dir.glob("data-part-*.parquet")))
        (self.run_dir/"data.csv.partial").mkdir()
        self.cli("shutdown")
        self.assertNotEqual(self.service.wait(timeout=8),0)
        end=json.loads((self.run_dir/"end.json").read_text())
        self.assertFalse(end["complete"])
        self.assertIn("CSV export failed",end["state"]["error"])
        self.assertTrue((self.run_dir/"data.parquet").is_file())
        self.assertTrue(list(self.run_dir.glob("data-part-*.parquet")))
        self.assertFalse((self.run_dir/"data.csv").exists())

    def test_legacy_ack_toggle(self):
        self.start(legacy=True,ack="off",logging=False)
        wait_for(lambda:self.cli("status")["state"]["frames"]==1)
        time.sleep(.1)
        self.assertEqual(self.cli("status")["state"]["frames"],1)
        self.cli("send-ack","on")
        wait_for(lambda:self.cli("status")["state"]["frames"]>=5)
        self.cli("send-ack","off")
        time.sleep(.1)
        n=self.cli("status")["state"]["frames"]
        time.sleep(.1)
        self.assertEqual(self.cli("status")["state"]["frames"],n)
        self.cli("shutdown")
        self.assertEqual(self.service.wait(timeout=8),0)

    def test_control_validation_and_exclusive_run(self):
        self.start()
        with socket.create_connection(tuple(["127.0.0.1", int(self.endpoint.split(":")[1])])) as sock:
            sock.sendall(b'{"api_version":2,"command":{"op":"stop"}}\n')
            reply=json.loads(sock.makefile("rb").readline())
            self.assertFalse(reply["ok"])
        # Duplicate owner must fail before replacing the device connection.
        p=subprocess.run([str(BIN),"--endpoint",self.endpoint,"serve","--device",f"127.0.0.1:{self.device_port}"],capture_output=True,timeout=5)
        self.assertNotEqual(p.returncode,0)
        n=self.cli("status")["state"]["frames"]
        wait_for(lambda:self.cli("status")["state"]["frames"]>n)
        self.cli("shutdown")
        self.assertEqual(self.service.wait(timeout=8),0)
        p=subprocess.run([str(BIN),"--endpoint",self.endpoint,"serve","--device",f"127.0.0.1:{self.device_port}","--output",str(self.run_dir)],capture_output=True,timeout=5)
        self.assertNotEqual(p.returncode,0)

    def test_fragmented_frames_and_malformed_tail(self):
        listener=socket.socket()
        listener.bind(("127.0.0.1",self.device_port))
        listener.listen(1)
        self.addCleanup(listener.close)
        release=threading.Event()
        def peer():
            conn,_=listener.accept()
            with conn:
                remaining = 20 * 8  # Consume default startup selections before closing the fixture.
                while remaining:
                    chunk = conn.recv(remaining)
                    if not chunk:
                        return
                    remaining -= len(chunk)
                m=server_module.UltraZohmModel(1000,50,1,17)
                m.selected_observables[0]=3
                frame=server_module.generate_packet(m,15,20)
                conn.sendall(frame[:1]); time.sleep(.06)  # Cross read timeout with a partial frame.
                conn.sendall(frame[1:123]); time.sleep(.06)
                conn.sendall(frame[123:]+frame+frame)
                release.wait(5)
                invalid=bytearray(frame)
                struct.pack_into("<f",invalid,len(invalid)-4,float("nan"))
                conn.sendall(invalid)
        worker=threading.Thread(target=peer,daemon=True)
        worker.start()
        self.run_dir=Path(self.tmp.name)/"fragments"
        self.service=self.spawn([BIN,"--endpoint",self.endpoint,"serve","--device",f"127.0.0.1:{self.device_port}","--output",self.run_dir])
        wait_for(lambda:self.cli("status")["state"]["samples"]==45)
        release.set()
        self.assertNotEqual(self.service.wait(timeout=8),0)
        worker.join(timeout=2)
        end=json.loads((self.run_dir/"end.json").read_text())
        self.assertIn("invalid slow ID",end["state"]["error"])
        self.assertEqual(end["state"]["samples"],45)

    def test_disk_error_is_reported(self):
        self.start()
        # A directory where a temporary file should go forces a portable write failure.
        (self.run_dir/"data-part-00000000.parquet.partial").mkdir()
        self.assertNotEqual(self.service.wait(timeout=8),0)
        end=json.loads((self.run_dir/"end.json").read_text())
        self.assertFalse(end["complete"])
        self.assertIn("logging",end["state"]["error"])

    @unittest.skipUnless(importlib.util.find_spec("ultrazohm"), "install native wheel for embedded API test")
    def test_embedded_python_acquisition(self):
        from ultrazohm import Acquisition, Client
        self.server=self.spawn([sys.executable,ROOT/"javascope/test_server.py","--port",self.device_port])
        def ready():
            with socket.create_connection(("127.0.0.1",self.device_port),timeout=.1):
                return True
        wait_for(ready)
        run_dir=Path(self.tmp.name)/"embedded"
        profile_path=self.config_file("python-profile.json", self.runtime_profile({"5":"JSO_PYTHON_SIGNAL"}))
        mapping=json.loads((ROOT/"uz_cli/channel_mappings/default.json").read_text())
        mapping["observables"]["JSO_PYTHON_SIGNAL"] = 29
        mapping["platform_state"]["values"]["0"] = "waiting"
        mapping_path=self.config_file("python-mapping.json",mapping)
        a=Acquisition(f"127.0.0.1:{self.device_port}",endpoint=self.endpoint,output=str(run_dir),
                      profile=str(profile_path),channel_mapping=str(mapping_path),format="parquet")
        try:
            c=Client(self.endpoint)
            wait_for(lambda: c.status()["state"]["platform_state"] == "waiting")
            self.assertEqual(c.observables()["channels"][4]["name"], "JSO_PYTHON_SIGNAL")
            self.assertEqual(c.observables()["channels"][4]["id"], 29)
            c.set_observable("lifecheck",1)
            c.start_logging()
            c.start_logging_slow_data()
            wait_for(lambda:c.status()["state"]["samples"]>=30)
        finally:
            a.close()
        self.assertTrue(a.is_finished())
        self.assertTrue(json.loads((run_dir/"end.json").read_text())["complete"])
        self.assertEqual(set(p for p in run_dir.glob("*.parquet") if "-part-" not in p.name), {run_dir/"data.parquet", run_dir/"data_slow_data.parquet"})
        self.assertFalse(list(run_dir.glob("*.csv")))

    @unittest.skipUnless(importlib.util.find_spec("ultrazohm"), "install native wheel for embedded API test")
    def test_embedded_python_connect_later(self):
        from ultrazohm import Acquisition, Client
        acquisition = Acquisition(endpoint=self.endpoint, output=str(Path(self.tmp.name)/"connect-later"))
        try:
            client = Client(self.endpoint)
            self.assertFalse(client.status()["state"]["connected"])
            self.spawn([sys.executable, ROOT/"javascope/test_server.py", "--port", self.device_port])
            def ready():
                with socket.create_connection(("127.0.0.1", self.device_port), timeout=.1):
                    return True
            wait_for(ready)
            client.connect("127.0.0.1", self.device_port)
            self.assertTrue(client.status()["state"]["connected"])
            self.assertEqual(client.observables()["channels"][2]["name"], "JSO_lifecheck")
            wait_for(lambda: client.status()["state"]["samples"] > 0)
        finally:
            acquisition.close()
        self.assertTrue(acquisition.is_finished())

    @unittest.skipUnless(importlib.util.find_spec("ultrazohm"), "install native wheel for embedded API test")
    def test_embedded_python_defaults(self):
        repo = Path(self.tmp.name)/"repo"
        (repo/"tcl_scripts").mkdir(parents=True)
        (repo/"tcl_scripts/vitis_headless.tcl").touch()
        (repo/"vitis/software").mkdir(parents=True)
        cwd = repo/"uz_cli"
        cwd.mkdir()
        self.spawn([sys.executable, ROOT/"javascope/test_server.py", "--port", self.device_port])
        def ready():
            with socket.create_connection(("127.0.0.1", self.device_port), timeout=.1):
                return True
        wait_for(ready)
        code = r'''import json, sys, time
from pathlib import Path
import ultrazohm
endpoint, device_port = sys.argv[1:]
a = ultrazohm.Acquisition(endpoint=endpoint)
try:
    uz = ultrazohm.Client(endpoint)
    assert not uz.status()["state"]["connected"]
    # A second owner must fail during construction, leaving this service usable.
    try:
        ultrazohm.Acquisition(endpoint=endpoint)
    except RuntimeError:
        pass
    else:
        raise AssertionError("duplicate service unexpectedly started")
    uz.connect("127.0.0.1", int(device_port))
    uz.start_logging()
    deadline = time.monotonic() + 10
    while uz.status()["state"]["samples"] < 30:
        assert time.monotonic() < deadline
        time.sleep(.03)
finally:
    a.close()
output = Path(a.output)
assert output.parent == Path.cwd().parent/"artifacts/live_logs", output
assert (output/"data.csv").is_file()
assert (output/"data.parquet").is_file()
assert json.loads((output/"end.json").read_text())["complete"]
# Existing output directories must fail immediately too.
try:
    ultrazohm.Acquisition(endpoint=endpoint, output=str(output))
except RuntimeError:
    pass
else:
    raise AssertionError("existing output unexpectedly accepted")
'''
        subprocess.run([sys.executable, "-c", code, self.endpoint, str(self.device_port)],
                       cwd=cwd, check=True, capture_output=True, text=True, timeout=30)

    def test_disconnect_flushes_partial_batch(self):
        self.start()
        wait_for(lambda:self.cli("status")["state"]["samples"]>=30)
        self.server.terminate(); self.server.wait(timeout=5)
        self.assertNotEqual(self.service.wait(timeout=8),0)
        end=json.loads((self.run_dir/"end.json").read_text())
        self.assertFalse(end["complete"])
        self.assertEqual(set(p for p in self.run_dir.glob("*.parquet") if "-part-" not in p.name), {self.run_dir/"data.parquet", self.run_dir/"data_slow_data.parquet"})
        if importlib.util.find_spec("polars"):
            import polars as pl
            self.assertEqual(pl.read_parquet(self.run_dir/"data.parquet").height,json.loads((self.run_dir/"data.json").read_text())["rows"])


if __name__ == "__main__":
    unittest.main()
