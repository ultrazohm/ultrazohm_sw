"""Launcher checks that do not program hardware or require GUI dependencies."""

import unittest
from unittest.mock import MagicMock, patch

from train_pt1_live import (
    completed_recording,
    configure_viewer,
    PLOTS,
    wait_until,
    wait_for_viewer,
)


class LiveLauncherTests(unittest.TestCase):
    @patch("train_pt1_live.time.sleep")
    def test_startup_rediscover_credentials_after_early_probe(self, sleep):
        process = MagicMock()
        process.poll.return_value = None
        unauthorized = RuntimeError("Invalid token")
        unauthorized.code = "unauthorized"
        clients = [MagicMock() for _ in range(3)]
        for client in clients:
            client.__enter__.return_value = client
        clients[0].status.side_effect = ConnectionRefusedError()
        clients[1].status.side_effect = unauthorized
        clients[2].status.return_value = {"runs": 0}
        factory = MagicMock(side_effect=clients)
        wait_for_viewer(factory, "127.0.0.1:19741", process, "viewer.log")
        self.assertEqual(factory.call_count, 3)
        for client in clients:
            client.status.assert_called_once()
            client.__exit__.assert_called_once()

    def test_startup_does_not_hide_application_errors(self):
        process = MagicMock()
        process.poll.return_value = None
        factory = MagicMock()
        factory.return_value.__enter__.return_value.status.side_effect = RuntimeError(
            "broken operation"
        )
        with self.assertRaisesRegex(RuntimeError, "broken operation"):
            wait_for_viewer(factory, "127.0.0.1:19741", process, "viewer.log")

    @patch("train_pt1_live.time.sleep")
    def test_waits_for_new_channel_mapping_before_assigning_live_plots(self, sleep):
        viewer = MagicMock()
        channels = tuple(
            name
            for names in PLOTS
            for name in names
            if not name.startswith("nn_update_")
        )
        viewer.list_runs.side_effect = [
            [{"handle": "upload-generation", "signals": ["JSO_nn_update_active"]}],
            [
                {
                    "handle": "training-generation",
                    "signals": [f"JSO_pt1_{n}" for n in channels]
                    + ["JSO_nn_update_received", "JSO_nn_update_expected"],
                }
            ],
        ]
        configure_viewer(viewer, channels)
        for call in viewer.add_signal.call_args_list:
            self.assertEqual(call.args[1], "training-generation")
            self.assertEqual(call.kwargs["view"], viewer.live_view.return_value)
        self.assertEqual(viewer.add_signal.call_count, len(channels) + 2)
        viewer.live_follow.assert_called_with(True)

    def test_finalization_failure_is_reported_before_learning(self):
        client = MagicMock()
        client.status.return_value = {
            "logging": {"fast": {"phase": "failed", "error": "disk full"}}
        }
        with self.assertRaisesRegex(RuntimeError, "disk full"):
            completed_recording(client)

    @patch("train_pt1_live.time.sleep")
    @patch("train_pt1_live.time.monotonic", side_effect=[0, 0, 31])
    def test_readiness_has_a_deadline(self, monotonic, sleep):
        with self.assertRaisesRegex(TimeoutError, "viewer"):
            wait_until(lambda: None, "viewer")


if __name__ == "__main__":
    unittest.main()
