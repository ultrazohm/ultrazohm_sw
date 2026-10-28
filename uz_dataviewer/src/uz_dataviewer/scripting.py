"""Process-based measurement scripts and an independent device Stop path."""
from pathlib import Path
import os
import signal
import subprocess
import sys
import tempfile
import threading

TEMPLATES = {
    'Blank': '''def run(uz):
    print(uz.status())
''',
    'Timed recording': '''import time


def run(uz):
    uz.start_logging()
    print("Logging started")
    time.sleep(10)
    uz.stop_logging()
    print("Logging finalizing; device state unchanged")
''',
    'Control sequence': '''import time


def run(uz):
    # Adapt the variable and value to your firmware before running.
    uz.set_variable("send_field_1", 0.0)
    uz.enable_system()
    time.sleep(1)
    uz.enable_control()
    print("Control enable sent; check the streamed platform state")
''',
    'Sine sweep (30 s)': '''import time


def ramp(uz, field, first, last, started, duration):
    # Wall-clock interpolation avoids accumulating command/sleep delays.
    while True:
        fraction = min(1.0, max(0.0, (time.monotonic() - started) / duration))
        uz.set_variable(field, first + (last - first) * fraction)
        if fraction >= 1.0:
            return
        time.sleep(max(0.0, min(0.05, started + duration - time.monotonic())))


def run(uz):
    # Requires the Baremetal sine demo and its matching channel-mapping JSON.
    signals = ("JSO_SineDemo", "JSO_SineDemoAmplitude", "JSO_SineDemoFrequency_Hz")
    if not all(name in uz.catalog()["profile"]["observables"] for name in signals):
        raise RuntimeError("Load the sine-demo firmware and matching channel mapping first")
    if any(s["phase"] in ("recording", "finalizing") for s in uz.status()["logging"].values()):
        raise RuntimeError("Finish existing fast and slow logging before running this example")
    assignments = {s["channel"]: s["name"] for s in uz.observables()["channels"]}
    for channel, name in enumerate(signals, 1):
        if assignments.get(channel) != name:
            uz.set_observable(name, channel)
    uz.set_variable("send_field_19", 0.0)
    uz.set_variable("send_field_20", 10.0)
    uz.start_logging()
    started = time.monotonic()
    print("0-15 s: amplitude 0 -> 10, frequency 10 Hz", flush=True)
    ramp(uz, "send_field_19", 0.0, 10.0, started, 15.0)
    print("15-30 s: frequency 10 -> 50 Hz, amplitude 10", flush=True)
    ramp(uz, "send_field_20", 10.0, 50.0, started + 15.0, 15.0)
    # Sending a command does not acknowledge firmware application. Keep recording
    # until the final setpoints have returned in the sampled data.
    deadline = time.monotonic() + 2.0
    while True:
        last = uz.tail(1, channels=list(signals[1:]))
        if last[signals[1]][0] == 10.0 and last[signals[2]][0] == 50.0:
            break
        if time.monotonic() >= deadline:
            raise RuntimeError("Final sine setpoints not observed; logging remains active")
        time.sleep(0.01)
    uz.stop_logging()
    print("Sweep complete; logging finalizing. Sine remains at amplitude 10, frequency 50 Hz.")
''',
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
        if getattr(sys, 'frozen', False):
            raise RuntimeError('Python scripts require the source launcher and its Python environment')
        self._cleanup()
        self._directory = tempfile.TemporaryDirectory(prefix='uz-script-')
        self._log = Path(self._directory.name) / 'output.log'
        options = {'start_new_session': True} if os.name != 'nt' else {
            'creationflags': subprocess.CREATE_NEW_PROCESS_GROUP}
        env = os.environ.copy()
        env['PYTHONIOENCODING'] = 'utf-8'
        with self._log.open('wb') as output:
            self.process = subprocess.Popen(
                [sys.executable, '-u', '-m', 'uz_dataviewer.script_worker', str(Path(path).resolve()), endpoint],
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
