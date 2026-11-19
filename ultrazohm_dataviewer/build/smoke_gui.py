"""Launch the installed GUI and verify that its frame loop serves control calls."""
import os
from pathlib import Path
import socket
import subprocess
import sys
import tempfile
import time


def main():
    from ultrazohm_dataviewer import Client
    with socket.socket() as listener:
        listener.bind(('127.0.0.1', 0))
        endpoint = f'127.0.0.1:{listener.getsockname()[1]}'
    with tempfile.TemporaryDirectory(prefix='ultrazohm GUI smoke ') as directory:
        root = Path(directory)
        env = {**os.environ, 'XDG_DATA_HOME': directory, 'LOCALAPPDATA': directory,
               'UZ_DATAVIEWER_CACHE': str(root / 'cache')}
        with (root / 'gui.log').open('w+') as log:
            process = subprocess.Popen([sys.executable, '-m', 'ultrazohm_dataviewer',
                                        '--endpoint', endpoint], cwd=root, env=env,
                                       stdin=subprocess.DEVNULL, stdout=log, stderr=log)
            try:
                deadline = time.monotonic() + 45
                last_error = None
                while time.monotonic() < deadline:
                    if process.poll() is not None:
                        break
                    try:
                        with Client(endpoint, timeout=1) as viewer:
                            viewer.set_grid(2, 1)
                            status = viewer.status()
                            assert status['grid'] == [2, 1], status
                            print('Installed GUI started and served a control request.')
                            return
                    except (OSError, RuntimeError, EOFError) as error:
                        last_error = error
                    time.sleep(.1)
                log.flush()
                log.seek(0)
                raise RuntimeError(f'GUI did not become ready: {last_error}\n{log.read()}')
            finally:
                if process.poll() is None:
                    process.terminate()
                try:
                    process.wait(timeout=10)
                except subprocess.TimeoutExpired:
                    process.kill()
                    process.wait()


if __name__ == '__main__':
    main()
