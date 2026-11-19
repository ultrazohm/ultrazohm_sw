"""Launch the installed GUI and verify that its frame loop serves control calls."""
from contextlib import contextmanager
import os
from pathlib import Path
import signal
import socket
import subprocess
import sys
import tempfile
import time


@contextmanager
def smoke_directory():
    directory = tempfile.TemporaryDirectory(prefix='ultrazohm GUI smoke ')
    try:
        yield Path(directory.name)
    finally:
        # TerminateProcess/taskkill can return before Windows releases inherited
        # file handles. Retry briefly, but still fail on a persistent leak.
        deadline = time.monotonic() + 10
        while True:
            try:
                directory.cleanup()
                break
            except PermissionError:
                if time.monotonic() >= deadline:
                    raise
                time.sleep(.1)


def main():
    from ultrazohm_dataviewer import Client
    with socket.socket() as listener:
        listener.bind(('127.0.0.1', 0))
        endpoint = f'127.0.0.1:{listener.getsockname()[1]}'
    with smoke_directory() as root:
        env = {**os.environ, 'XDG_DATA_HOME': str(root), 'LOCALAPPDATA': str(root),
               'UZ_DATAVIEWER_CACHE': str(root / 'cache')}
        with (root / 'gui.log').open('w+') as log:
            process = subprocess.Popen([sys.executable, '-m', 'ultrazohm_dataviewer',
                                        '--endpoint', endpoint], cwd=root, env=env,
                                       stdin=subprocess.DEVNULL, stdout=log, stderr=log,
                                       start_new_session=os.name != 'nt')
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
                # Windows venv launchers and GUI workers can outlive the parent
                # and retain inherited log handles. Stop the whole test tree.
                if os.name == 'nt':
                    if process.poll() is None:
                        subprocess.run(['taskkill', '/PID', str(process.pid), '/T', '/F'],
                                       timeout=10, check=True)
                else:
                    try:
                        os.killpg(process.pid, signal.SIGTERM)
                    except ProcessLookupError:
                        pass
                try:
                    process.wait(timeout=10)
                except subprocess.TimeoutExpired:
                    process.kill()
                    process.wait()


if __name__ == '__main__':
    main()
