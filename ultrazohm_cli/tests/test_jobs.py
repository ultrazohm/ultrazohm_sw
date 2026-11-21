"""Firmware job following preserves offsets and drains final output."""

import unittest
from unittest.mock import Mock

from ultrazohm_cli.jobs import FirmwareJob


def reply(state, offset, log=""):
    return {
        "job": {
            "state": state,
            "result": {"error": "failed"} if state == "failed" else None,
        },
        "next_offset": offset,
        "log": log,
    }


class JobTest(unittest.TestCase):
    def test_final_log_drained_and_resumed_by_another_client(self):
        client = Mock()
        client.job.side_effect = [
            reply("running", 5, "hello"),
            reply("succeeded", 10, "world"),
            reply("succeeded", 10),
        ]
        first = FirmwareJob(client, "job")
        self.assertEqual(first.poll()["log"], "hello")
        second = FirmwareJob(client, "job", first.offset)
        self.assertEqual(second.poll()["log"], "world")
        self.assertFalse(second.complete)
        second.poll()
        self.assertTrue(second.complete)
        second.raise_for_status()
        client.shutdown.assert_not_called()

    def test_disconnect_preserves_offset_and_failure_follows_final_log(self):
        client = Mock()
        client.job.side_effect = [
            OSError("disconnected"),
            reply("failed", 5, "error"),
            reply("failed", 5),
        ]
        job = FirmwareJob(client, "job")
        with self.assertRaises(OSError):
            job.poll()
        self.assertEqual(job.offset, 0)
        self.assertEqual(job.poll()["log"], "error")
        job.raise_for_status()
        job.poll()
        with self.assertRaisesRegex(RuntimeError, "failed"):
            job.raise_for_status()
