import importlib.util
from pathlib import Path
import tempfile
import unittest
from unittest.mock import Mock

spec = importlib.util.spec_from_file_location('flash', Path(__file__).resolve().parents[1] / 'flash.py')
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)


class FlashTest(unittest.TestCase):
    def test_connected_service_preserves_target_and_propagates_job_failure(self):
        with tempfile.TemporaryDirectory() as directory:
            client = Mock(endpoint='127.0.0.1:19740')
            client.status.return_value = {'repository': directory, 'firmware_available': True, 'state': {'device': '192.168.1.233:1000'}}
            client.firmware.return_value = {'id': 'job-1'}
            monitor = Mock(complete=True)
            monitor.poll.return_value = {'log': 'firmware log\n'}
            monitor.raise_for_status.side_effect = RuntimeError('job failed')
            with self.assertRaisesRegex(RuntimeError, 'job failed'):
                module.flash(client, Mock(return_value=monitor), directory)
            client.firmware.assert_called_once_with('flash', device='192.168.1.233:1000', no_reconnect=False)
            client.shutdown.assert_not_called()

    def test_missing_tools_or_busy_service_never_submits(self):
        with tempfile.TemporaryDirectory() as directory:
            for fields in [{'firmware_available': False}, {'firmware_available': True, 'active_job': {'id': 'busy'}}]:
                client = Mock()
                client.status.return_value = {'repository': directory, **fields}
                with self.assertRaises(RuntimeError):
                    module.flash(client, Mock(), directory)
                client.firmware.assert_not_called()
