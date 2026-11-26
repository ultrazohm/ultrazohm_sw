"""Recording startup regression tests; no device or CLI installation needed."""
import unittest
from unittest.mock import MagicMock, patch

from pt1_recording import wait_for_replay


class ReplayStartupTests(unittest.TestCase):
    def client(self):
        client = MagicMock()
        client.status.return_value = {
            "state": {"connected": True}, "logging": {"fast": {"phase": "recording"}}}
        return client

    @patch("pt1_recording.time.sleep")
    def test_initializing_is_retried_without_advancing_cursor(self, sleep):
        client = self.client()
        page = MagicMock()
        page.data.filter.return_value.height = 3000
        client.read_since.side_effect = [RuntimeError("recording is initializing"), page]
        wait_for_replay(client, 1, 10)
        self.assertEqual(client.read_since.call_count, 2)
        for call in client.read_since.call_args_list:
            self.assertEqual(call.args, (None,))
        sleep.assert_any_call(0.02)

    @patch("pt1_recording.time.sleep")
    @patch("pt1_recording.time.monotonic", side_effect=[0, 0, 11])
    def test_initialization_still_obeys_timeout(self, monotonic, sleep):
        client = self.client()
        client.read_since.side_effect = RuntimeError("recording is initializing")
        with self.assertRaises(TimeoutError):
            wait_for_replay(client, 1, 10)

    def test_other_recording_errors_are_not_hidden(self):
        client = self.client()
        client.read_since.side_effect = RuntimeError("disk failure")
        with self.assertRaisesRegex(RuntimeError, "disk failure"):
            wait_for_replay(client, 1, 10)

    @patch("pt1_recording.time.sleep")
    def test_later_round_reads_its_own_recording(self, sleep):
        client = self.client()
        page = MagicMock()
        page.data.filter.return_value.height = 3000
        client.read_since.return_value = page
        wait_for_replay(client, 1, 10, recording=7)
        client.read_since.assert_called_once_with(None, recording=7, limit=10000)


if __name__ == "__main__":
    unittest.main()
