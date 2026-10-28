"""Exercise the distributed workers against a simulator, without a GUI."""
import json
from pathlib import Path
import socket
import subprocess
import sys
import tempfile
import time


def port():
    with socket.socket() as sock:
        sock.bind(('127.0.0.1', 0))
        return sock.getsockname()[1]


def main():
    executable = str(Path(sys.argv[1]).resolve(strict=True))
    root = Path(__file__).resolve().parents[2]
    endpoint = f'127.0.0.1:{port()}'
    device_port = port()
    processes = []
    with tempfile.TemporaryDirectory() as tmp:
        directory = Path(tmp)
        def cli(*args):
            result = subprocess.run([executable, '--internal-worker', 'cli', '--endpoint', endpoint, *map(str, args)],
                                    capture_output=True, text=True, cwd=tmp, timeout=30)
            assert result.returncode == 0, result.stderr
            return result.stdout
        try:
            simulator = subprocess.Popen([sys.executable, str(root/'javascope/test_server.py'), '--port', str(device_port)])
            processes.append(simulator)
            for _ in range(100):
                try:
                    with socket.create_connection(('127.0.0.1', device_port), timeout=.1): break
                except OSError: time.sleep(.05)
            mapping = directory/'mapping.json'
            cli('create-json-from-javascope-h', '--repo', root, '--output', mapping)
            with (directory/'service.log').open('w') as log:
                service = subprocess.Popen([executable, '--internal-worker', 'cli', '--endpoint', endpoint,
                    'serve', '--device', f'127.0.0.1:{device_port}', '--channel-mapping', str(mapping),
                    '--output', str(directory/'recording')], cwd=tmp, stdout=log, stderr=log)
                processes.append(service)
                for _ in range(100):
                    try:
                        if json.loads(cli('status'))['state']['samples'] > 0: break
                    except (AssertionError, OSError): pass
                    time.sleep(.05)
                else: raise AssertionError((directory/'service.log').read_text())
                script = directory/'script.py'
                script.write_text('import argparse, time\nfrom ultrazohm import Client\np=argparse.ArgumentParser()\np.add_argument("--endpoint")\nu=Client(p.parse_args().endpoint)\nu.start_logging()\ntime.sleep(.3)\nu.stop_logging()\nprint("SCRIPT_OK", flush=True)\n')
                result = subprocess.run([executable, '--internal-worker', 'script', str(script), '--endpoint', endpoint],
                                        capture_output=True, text=True, cwd=tmp, timeout=30)
                assert result.returncode == 0, result.stderr
                assert 'SCRIPT_OK' in result.stdout
                cli('shutdown')
                assert service.wait(timeout=30) == 0
                assert (directory/'recording/data.parquet').is_file()
        finally:
            for process in reversed(processes):
                if process.poll() is None:
                    process.terminate()
                try: process.wait(timeout=10)
                except subprocess.TimeoutExpired:
                    process.kill()
                    process.wait()
    print('Packaged mapping, acquisition, script, logging and shutdown passed.')


if __name__ == '__main__':
    main()
