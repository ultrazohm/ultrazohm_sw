"""A non-GUI Python caller can own and finalize a CLI service process."""

import socket
import tempfile
import unittest
from pathlib import Path
from unittest.mock import Mock, patch

from ultrazohm_cli import Client
from ultrazohm_cli.process import ServiceProcess

ROOT = Path(__file__).resolve().parents[2]


class ProcessTest(unittest.TestCase):
    def test_start_rejects_unrelated_service(self):
        with tempfile.TemporaryDirectory() as directory:
            child = Mock()
            child.poll.return_value = None
            client = Mock()
            client.status.return_value = {"service_id": "unrelated"}
            owner = ServiceProcess()
            with patch("ultrazohm_cli.process.subprocess.Popen", return_value=child):
                with self.assertRaisesRegex(ValueError, "Another service"):
                    owner.start(Path(directory) / "run", "", client=client)
            child.terminate.assert_called_once()
            client.shutdown.assert_not_called()
            self.assertIsNone(owner.service_id)

    def test_shutdown_passes_expected_identity(self):
        child = Mock()
        child.poll.return_value = None
        client = Mock()
        client.status.return_value = {"service_id": "owned"}
        owner = ServiceProcess(process=child, service_id="owned")
        owner.shutdown(client)
        client.shutdown.assert_called_once_with(service_id="owned")

    def test_external_service_lifetime_without_viewer(self):
        with tempfile.TemporaryDirectory() as directory:
            with socket.socket() as reserve:
                reserve.bind(("127.0.0.1", 0))
                endpoint = f"127.0.0.1:{reserve.getsockname()[1]}"
            owner = ServiceProcess()
            client = Client(endpoint)
            try:
                owner.start(Path(directory) / "run", "", repo=ROOT, endpoint=endpoint)
                self.assertTrue(owner.owns(endpoint))
                status = client.status()
                self.assertEqual(owner.service_id, status["service_id"])
                with self.assertRaisesRegex(RuntimeError, "identity mismatch"):
                    client.shutdown(service_id="another-service")
                self.assertEqual(client.status()["service_id"], owner.service_id)
                intruder = ServiceProcess()
                with self.assertRaises((ValueError, RuntimeError)):
                    intruder.start(
                        Path(directory) / "other", "", repo=ROOT, endpoint=endpoint
                    )
                self.assertIsNone(intruder.service_id)
                self.assertEqual(client.status()["service_id"], owner.service_id)
                self.assertEqual(status["state"]["user_buttons"], [False] * 8)
                replacement = Mock()
                replacement.status.return_value = {"service_id": "replacement"}
                with self.assertRaisesRegex(RuntimeError, "replaced"):
                    owner.shutdown(replacement)
                replacement.shutdown.assert_not_called()
                self.assertTrue(owner.running)
                owner.shutdown(client)
                owner.process.wait(timeout=10)
                self.assertEqual(owner.wait(), 0)
                self.assertFalse(owner.running)
                owner.shutdown(client)  # Idempotent after exit.
            finally:
                client.close()
                if owner.running:
                    owner.shutdown()
                    owner.process.wait(timeout=10)
