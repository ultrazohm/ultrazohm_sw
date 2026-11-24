"""Hardware-free transport integration against a POSIX pseudo serial port."""
import base64
import json
import os
from pathlib import Path
import select
import subprocess
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]


@unittest.skipUnless(os.name == 'posix' and (ROOT / 'runtime/serial/serial/__init__.py').exists(),
                     'POSIX and bundled pySerial required; packaged loopback runs on both OSes')
class SerialTransportTest(unittest.TestCase):
    def test_receive_transmit_close_and_unplug(self):
        import pty
        for unplug in [False, True]:
            master, slave = pty.openpty()
            settings = dict(device=os.ttyname(slave), baud=115200, dataBits=8, parity='N', stopBits=1, flowControl='none')
            process = subprocess.Popen([sys.executable, '-I', '-B', str(ROOT / 'serial-terminal.py'), 'connect',
                                        '--settings', json.dumps(settings)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            def event():
                self.assertTrue(select.select([process.stdout], [], [], 5)[0], 'serial helper timed out')
                return json.loads(process.stdout.readline())
            try:
                self.assertEqual(event()['event'], 'connected')
                os.write(master, b'firmware log\r\n')
                received = bytearray()
                while len(received) < len(b'firmware log\r\n'):
                    message = event()
                    self.assertEqual(message['event'], 'data')
                    received.extend(base64.b64decode(message['data']))
                self.assertEqual(received, b'firmware log\r\n')
                process.stdin.write(json.dumps({'command':'write', 'data':base64.b64encode(b'hello\r').decode()}).encode()+b'\n')
                process.stdin.flush()
                self.assertTrue(select.select([master], [], [], 5)[0])
                self.assertEqual(os.read(master, 100), b'hello\r')
                if unplug:
                    os.close(master); master = None
                    self.assertEqual(event()['event'], 'error')
                    self.assertEqual(process.wait(timeout=5), 1)
                else:
                    process.stdin.close()
                    self.assertEqual(process.wait(timeout=5), 0)
            finally:
                if process.poll() is None: process.kill(); process.wait()
                for stream in [process.stdin,process.stdout,process.stderr]: stream.close()
                if master is not None: os.close(master)
                os.close(slave)
