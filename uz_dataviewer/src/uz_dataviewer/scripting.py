"""Process-based measurement scripts and an independent device Stop path."""
from pathlib import Path
import os
import signal
import subprocess
import tempfile
import threading

# This text is visible/editable in every template, not injected at execution.
_ENTRY_POINT = """

if __name__ == "__main__":
    import argparse
    from ultrazohm import Client

    parser = argparse.ArgumentParser(description="UltraZohm measurement")
    parser.add_argument("--endpoint", default="127.0.0.1:19740",
                        help="Acquisition service host:port")
    args = parser.parse_args()
    main(Client(args.endpoint))
"""

TEMPLATES = {
    'Blank': '''def main(uz):
    print(uz.status())
''' + _ENTRY_POINT,
    'Timed recording': '''import time


def main(uz):
    uz.start_logging()
    print("Logging started")
    time.sleep(10)
    uz.stop_logging()
    print("Logging finalizing; device state unchanged")
''' + _ENTRY_POINT,
    'Control sequence': '''import time


def main(uz):
    # Adapt the variable and value to your firmware before running.
    uz.set_variable("send_field_1", 0.0)
    uz.enable_system()
    time.sleep(1)
    uz.enable_control()
    print("Control enable sent; check the streamed platform state")
''' + _ENTRY_POINT,

}


class ScriptRunner:
    def __init__(self, client_factory=None, send_stop=None):
        self.client_factory = client_factory
        self.send_stop = send_stop
        self.process = None
        self.endpoint = None
        self.message = 'Ready'
        self.output = ''
        self._directory = None
        self._log = None
        self._stop_thread = None
        self._stop_result = None
        self._lock = threading.Lock()

    @property
    def busy(self):
        return self.process is not None or self._stop_thread is not None

    def start(self, path, endpoint):
        if self.busy:
            raise RuntimeError('A script is already running or stopping')
        self._cleanup()
        self._directory = tempfile.TemporaryDirectory(prefix='uz-script-')
        self._log = Path(self._directory.name) / 'output.log'
        options = {'start_new_session': True} if os.name != 'nt' else {
            'creationflags': subprocess.CREATE_NEW_PROCESS_GROUP}
        env = os.environ.copy()
        env['PYTHONIOENCODING'] = 'utf-8'
        script_args = [str(Path(path).resolve()), '--endpoint', endpoint]
        from .process_launcher import command as worker_command
        command = worker_command('script', *script_args)
        with self._log.open('wb') as output:
            self.process = subprocess.Popen(
                command,
                stdin=subprocess.DEVNULL, stdout=output, stderr=subprocess.STDOUT, env=env, **options)
        self.endpoint = endpoint
        self.message = 'Running'
        self.output = ''

    def stop(self):
        """Kill the script before sending Stop; logging is deliberately untouched."""
        if self._stop_thread is not None:
            return
        process, endpoint = self.process, self.endpoint
        if endpoint is None:
            raise RuntimeError('No script service endpoint is available')
        self.message = 'Stopping script and device…'

        def work():
            errors = []
            try:
                if process is not None:
                    if os.name == 'nt' and process.poll() is None:
                        subprocess.run(['taskkill', '/PID', str(process.pid), '/T', '/F'],
                                       capture_output=True, check=False)
                        if process.poll() is None:
                            process.kill()
                    elif os.name != 'nt':
                        try:
                            os.killpg(process.pid, signal.SIGKILL)
                        except ProcessLookupError:
                            pass
                    process.wait(timeout=5)
            except Exception as exc:
                errors.append(f'Script termination failed: {exc}')
            try:
                if self.send_stop is not None:
                    self.send_stop(endpoint)
                elif self.client_factory is None:
                    from ultrazohm import Client
                    client = Client(endpoint)
                    client.stop()
                else:
                    client = self.client_factory(endpoint)
                    client.stop()
            except Exception as exc:
                errors.append(f'Device Stop failed: {exc}')
            with self._lock:
                self._stop_result = '; '.join(errors) if errors else 'Script stopped; device Stop sent. Logging unchanged.'

        self._stop_thread = threading.Thread(target=work, name='uz-script-stop', daemon=True)
        self._stop_thread.start()

    def poll(self):
        if self._log is not None:
            with self._log.open('rb') as output:
                output.seek(0, 2)
                output.seek(max(0, output.tell() - 65536))
                self.output = output.read().decode('utf-8', errors='replace')
        if self._stop_thread is not None:
            with self._lock:
                result = self._stop_result
                self._stop_result = None
            if result is not None:
                self._stop_thread.join()
                self._stop_thread = None
                self.message = result
                if self.process is not None and self.process.poll() is not None:
                    self.process = None
        elif self.process is not None and (code := self.process.poll()) is not None:
            if os.name != 'nt':
                try:
                    os.killpg(self.process.pid, signal.SIGKILL)
                except ProcessLookupError:
                    pass
            self.process = None
            self.message = 'Completed; device and logging state unchanged' if code == 0 else f'Script failed (exit {code}); device and logging state unchanged'

    def _cleanup(self):
        if self._directory is not None:
            self._directory.cleanup()
            self._directory = self._log = None

    def close(self):
        if self.busy:
            self.stop()
            self._stop_thread.join()
            self.poll()
        if not self.busy:
            self._cleanup()
