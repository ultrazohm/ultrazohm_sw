"""Exercise the distributed workers against a simulator, without a GUI."""
import json
from pathlib import Path
import socket
import os
import shutil
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
            # A firmware-only workspace must work without application code/Tcl.
            firmware = directory/'firmware checkout'
            for relative in ('vitis/software/Baremetal/src/include/javascope.h',
                             'vitis/software/Baremetal/src/include/javascope_status.h',
                             'vitis/software/shared/APU_RPU_shared.h',
                             'vitis/software/FreeRTOS/main.h', 'vitis/software/FreeRTOS/defines.h'):
                source = root/relative
                if source.exists():
                    target = firmware/relative
                    target.parent.mkdir(parents=True, exist_ok=True)
                    shutil.copyfile(source, target)
            # Exercise the same nested frozen workers used after selecting a
            # workspace, including defaults that reference absent observables.
            setup = directory/'prepare_workspace.py'
            prepared = directory/'prepared.json'
            setup.write_text(
                'import json\nfrom pathlib import Path\n'
                'from uz_dataviewer.live_mapping import generate_mapping\n'
                'from uz_dataviewer.flashing import initialize_user_settings, prepare_profile\n'
                f'mapping = generate_mapping(Path({str(firmware)!r}))\n'
                'settings = initialize_user_settings(mapping)\n'
                'original = json.loads(settings.read_text())\n'
                'original["name"] = "edited-smoke-profile"\n'
                'original["initial_channels"]["4"] = "JSO_missing_smoke_observable"\n'
                'settings.write_text(json.dumps(original))\n'
                'before = settings.read_bytes()\n'
                'initialize_user_settings(mapping)\n'
                'profile, removed = prepare_profile(mapping, mapping.parent / "smoke.profile.json")\n'
                'assert settings.read_bytes() == before\n'
                'assert "JSO_missing_smoke_observable" in removed\n'
                'assert (mapping.parent / "tools.json").is_file()\n'
                f'Path({str(prepared)!r}).write_text(json.dumps({{"mapping": str(mapping), "profile": str(profile)}}))\n')
            subprocess.run([executable, '--internal-worker', 'script', str(setup)],
                           cwd=tmp, check=True, timeout=60)
            configuration = json.loads(prepared.read_text())
            mapping, profile = Path(configuration['mapping']), Path(configuration['profile'])
            assert mapping.parent == firmware/'artifacts'/'_user_standalone'
            # Validate packaged flash dispatch without running any vendor/hardware commands.
            tools = directory/'fake-tools'
            tools.mkdir()
            report = directory/'xsct.json'
            stub = tools/'xsct_stub.py'
            stub.write_text('import json, os, sys\nfrom pathlib import Path\n'
                "Path(os.environ['UZ_TEST_REPORT']).write_text(json.dumps({'args': sys.argv[1:], 'root': os.environ['UZ_WORKSPACE_ROOT']}))\n")
            if os.name == 'nt':
                launcher = tools/'xsct.cmd'
                launcher.write_text(f'@echo off\n"{sys.executable}" "{stub}" %*\n')
            else:
                import shlex
                launcher = tools/'xsct'
                launcher.write_text('#!/bin/sh\nexec ' + shlex.quote(sys.executable) + ' ' + shlex.quote(str(stub)) + ' "$@"\n')
                launcher.chmod(0o755)
            subprocess.run([executable, '--internal-worker', 'cli', 'flash', '--repo', str(firmware)],
                check=True, timeout=30, env={**os.environ, 'PATH': str(tools), 'UZ_TEST_REPORT': str(report)})
            invocation = json.loads(report.read_text())
            assert Path(invocation['root']) == firmware
            bundled_script = Path(invocation['args'][1])
            assert bundled_script.is_file() and 'tcl_scripts' in bundled_script.parts
            assert bundled_script.is_relative_to(Path(executable).parent)
            assert not (firmware/'tcl_scripts').exists()
            with (directory/'service.log').open('w') as log:
                service = subprocess.Popen([executable, '--internal-worker', 'cli', '--endpoint', endpoint,
                    'serve', '--device', f'127.0.0.1:{device_port}', '--channel-mapping', str(mapping),
                    '--profile', str(profile),
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
