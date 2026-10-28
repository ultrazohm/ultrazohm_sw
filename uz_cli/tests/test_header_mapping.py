"""Generate real mapping JSON from repository-shaped header fixtures."""
import json
import os
from pathlib import Path
import shutil
import socket
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
BIN = Path(os.environ.get("UZ_CLI_BIN", ROOT / "uz_cli/target/debug" / ("ultrazohm.exe" if os.name == "nt" else "ultrazohm")))
HEADERS = [
    "vitis/software/Baremetal/src/include/javascope.h",
    "vitis/software/Baremetal/src/include/javascope_status.h",
    "vitis/software/shared/APU_RPU_shared.h",
    "vitis/software/FreeRTOS/main.h",
    "vitis/software/FreeRTOS/defines.h",
]


@unittest.skipUnless(BIN.exists(), "build Rust CLI first")
class HeaderMappingTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        with socket.socket() as listener:
            listener.bind(("127.0.0.1", 0))
            self.endpoint = f"127.0.0.1:{listener.getsockname()[1]}"
        self.repo = Path(self.tmp.name) / "repo with spaces"
        for name in HEADERS:
            target = self.repo / name
            target.parent.mkdir(parents=True, exist_ok=True)
            if name == HEADERS[1]:
                target.write_text("#define JAVASCOPE_PLATFORM_STATE_MASK UINT32_C(0xC0000000)\n"
                    "#define JAVASCOPE_PLATFORM_IDLE 0\n"
                    "#define JAVASCOPE_PLATFORM_RUNNING UINT32_C(0x40000000)\n"
                    "#define JAVASCOPE_PLATFORM_CONTROL UINT32_C(0x80000000)\n"
                    "#define JAVASCOPE_PLATFORM_ERROR UINT32_C(0xC0000000)\n")
            else:
                shutil.copyfile(ROOT / name, target)
        self.output = self.repo / "artifacts/channel_mappings/javascope.json"

    def run_cli(self, *args, cwd=None, input=None, env=None):
        return subprocess.run([str(BIN), *map(str, args)], cwd=cwd or self.repo,
                              input=input, env=env, capture_output=True, text=True, timeout=15)

    def test_default_paths_and_mapping_equivalence_without_tools(self):
        result = self.run_cli("create-json-from-javascope-h", cwd=self.repo / "vitis/software",
                              env={**os.environ, "PATH": ""})
        self.assertEqual(result.returncode, 0, result.stderr)
        generated = json.loads(self.output.read_text())
        result = self.run_cli("channel-mapping", env={**os.environ, "PATH": ""})
        self.assertEqual(result.returncode, 0, result.stderr)
        default = json.loads(result.stdout)
        for field in ("api_version", "channels", "samples_per_packet", "observables", "slow_signals", "variables", "commands", "platform_state"):
            self.assertEqual(generated[field], default[field], field)
        self.assertEqual(generated["repository"]["commit"], "unknown")

    def test_custom_headers_and_load_generated_mapping(self):
        header = self.repo / HEADERS[0]
        text = header.read_text().replace("\tJSO_ENDMARKER", "\tJSO_custom = 100U, // new signal\n\tJSO_next,\n\tJSO_ENDMARKER")
        text = text.replace("\tsend_field_1,", "\t speed_reference, /* new label */")
        header.write_text(text)
        geometry = self.repo / HEADERS[4]
        geometry.write_text(geometry.read_text().replace("JS_SAMPLES_PER_PACKET 15", "JS_SAMPLES_PER_PACKET 7"))
        status = self.repo / HEADERS[1]
        text = status.read_text().replace("JAVASCOPE_PLATFORM_RUNNING", "JAVASCOPE_PLATFORM_ENABLED")
        status.write_text(text)
        destination = self.repo / "custom mapping.json"
        result = self.run_cli("create-json-from-javascope-h", "--repo", self.repo, "--output", destination, cwd=self.tmp.name)
        self.assertEqual(result.returncode, 0, result.stderr)
        mapping = json.loads(destination.read_text())
        self.assertEqual(mapping["observables"]["JSO_custom"], 100)
        self.assertEqual(mapping["observables"]["JSO_next"], 101)
        self.assertEqual(mapping["variables"]["speed_reference"], 4)
        self.assertEqual(mapping["samples_per_packet"], 7)
        self.assertEqual(mapping["platform_state"]["values"]["1"], "enabled")
        # Default loading regenerates from this checkout, including local edits.
        result = self.run_cli("channel-mapping")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(json.loads(result.stdout), mapping)
        # The output is directly consumable by the CLI, without editing its schema.
        result = self.run_cli("--endpoint", self.endpoint, "serve", "--interactive",
                              "--channel-mapping", destination, "--output", self.repo / "session",
                              input="status\nshutdown\n")
        self.assertEqual(result.returncode, 0, result.stderr)

    def test_missing_checkout_has_no_bundled_fallback(self):
        result = self.run_cli("channel-mapping", cwd=self.tmp.name)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("generating firmware mapping requires a checkout", result.stderr)

    def test_bad_headers_do_not_replace_output(self):
        self.output.parent.mkdir(parents=True)
        self.output.write_text("keep existing")
        header = self.repo / HEADERS[0]
        original = header.read_text()
        for text in (
            original.replace("JSO_ISR_ExecTime_us,", "JSO_ISR_ExecTime_us = (1 << 2),"),
            original.replace("JSO_ENDMARKER", "JSO_MISSING_END"),
            original.replace("send_field_2,", "send_field_1,"),
            original + "\nJSO_ZEROVALUE=0,\nJSO_ENDMARKER\n",
        ):
            with self.subTest(text=text[-50:]):
                header.write_text(text)
                result = self.run_cli("create-json-from-javascope-h")
                self.assertNotEqual(result.returncode, 0)
                self.assertEqual(self.output.read_text(), "keep existing")
        header.write_text(original)
        (self.repo / HEADERS[1]).write_text("// malformed existing header")
        result = self.run_cli("create-json-from-javascope-h")
        self.assertNotEqual(result.returncode, 0)
        self.assertEqual(self.output.read_text(), "keep existing")

    def test_missing_status_header_generates_legacy_mapping(self):
        (self.repo / HEADERS[1]).unlink()
        result = self.run_cli('create-json-from-javascope-h')
        self.assertEqual(result.returncode, 0, result.stderr)
        mapping = json.loads(self.output.read_text())
        self.assertTrue(mapping['legacy_javascope_header'])
        self.assertIsNone(mapping['platform_state'])
        result = self.run_cli('--endpoint', self.endpoint, 'serve', '--interactive',
                              '--channel-mapping', self.output, '--output', self.repo / 'legacy-session',
                              input='status\nshutdown\n')
        self.assertEqual(result.returncode, 0, result.stderr)

    def test_interactive_command(self):
        result = self.run_cli("--endpoint", self.endpoint, "serve", "--interactive",
                              "--output", self.repo / "interactive",
                              input="create-json-from-javascope-h\nshutdown\n")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("Created channel mapping", result.stdout)
        self.assertTrue(self.output.is_file())
