"""Test the published CLI contract and real service with fake XSCT; no hardware access."""
import argparse
import json
import os
from pathlib import Path
import re
import shlex
import shutil
import socket
import subprocess
import sys
import tempfile
import time
from importlib.metadata import version


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--extension', type=Path, required=True)
    parser.add_argument('--repository', type=Path, required=True)
    args = parser.parse_args()
    cli = shutil.which('ultrazohm-cli')
    assert cli, 'Published CLI executable missing'
    def run(*argv, check=True):
        return subprocess.run([str(a) for a in argv], text=True, capture_output=True, timeout=90, check=check)
    expected = {
        'serve': ['--repo', '--xsct', '--interactive', '--endpoint'],
        'generate': ['--local', '--repo'], 'build': ['--local', '--repo'],
        'build-clean': ['--local', '--repo'],
        'flash': ['--endpoint', '--no-reconnect'],
    }
    for command, flags in expected.items():
        help_text = run(cli, command, '--help').stdout
        for flag in flags:
            assert re.search(r'(?<!\S)' + re.escape(flag) + r'(?=\s|$)', help_text), f'{command} missing {flag}'
    from ultrazohm_cli import Client
    from ultrazohm_cli.jobs import FirmwareJob
    assert callable(Client.firmware) and callable(FirmwareJob.poll)
    with tempfile.TemporaryDirectory(prefix='uz-published-contract-') as directory:
        base = Path(directory)
        root = base / 'firmware checkout'
        for relative in ['vitis/software/Baremetal/src/include/javascope.h', 'vitis/software/Baremetal/src/include/javascope_status.h', 'vitis/software/shared/APU_RPU_shared.h', 'vitis/software/FreeRTOS/main.h', 'vitis/software/FreeRTOS/defines.h']:
            target = root / relative
            target.parent.mkdir(parents=True, exist_ok=True)
            source = args.repository / relative
            if source.exists() or not relative.endswith('/javascope_status.h'):
                shutil.copyfile(source, target)
        # No checkout Tcl: the published CLI must supply its embedded scripts.
        tools = base / 'fake tools'
        tools.mkdir()
        report = tools / 'actions.jsonl'
        failure = tools / 'fail'
        stub = tools / 'xsct.py'
        stub.write_text('import os,sys,json\nfrom pathlib import Path\n'
            'action=next(sys.argv[i+1] for i,a in enumerate(sys.argv) if a.endswith(".tcl"))\n'
            f'with open({str(report)!r},"a") as f: f.write(json.dumps(action)+"\\n")\n'
            f'if Path({str(failure)!r}).exists(): sys.exit(7)\n'
            'Path(os.environ["UZ_VITIS_COMPLETION"]).write_text(action)\n')
        xsct = tools / ('xsct.cmd' if os.name == 'nt' else 'xsct')
        xsct.write_text(f'@echo off\n"{sys.executable}" "{stub}" %*\n' if os.name == 'nt' else f'#!/bin/sh\nexec {shlex.quote(sys.executable)} {shlex.quote(str(stub))} "$@"\n')
        xsct.chmod(0o755)
        env = dict(os.environ)
        env.pop('UZ_CLI_TCL_DIR', None)
        path_key = next((k for k in env if k.lower() == 'path'), 'PATH')
        env[path_key] = str(tools) + os.pathsep + env.get(path_key, '')
        # Local firmware commands really dispatch to the fixture, rather than just parsing help.
        for command in ['generate', 'build', 'build-clean']:
            result = subprocess.run([cli, command, '--local', '--repo', str(root)], env=env, capture_output=True, text=True, timeout=60)
            assert result.returncode == 0, result.stderr
        with socket.socket() as sock:
            sock.bind(('127.0.0.1', 0))
            endpoint = f'127.0.0.1:{sock.getsockname()[1]}'
        with (base / 'service.log').open('w+') as log:
            process = subprocess.Popen([cli, '--endpoint', endpoint, 'serve', '--repo', str(root), '--xsct', str(xsct), '--interactive'], stdin=subprocess.PIPE, stdout=log, stderr=log, env=env)
            client = Client(endpoint)
            try:
                deadline = time.monotonic() + 30
                while True:
                    try:
                        status = client.status()
                        break
                    except (OSError, RuntimeError):
                        assert process.poll() is None and time.monotonic() < deadline, 'Interactive service did not start'
                        client.close()
                        time.sleep(0.2)
                assert os.path.samefile(status['repository'], root)
                assert status['firmware_available']
                helper = [sys.executable, args.extension / 'flash.py', '--endpoint', endpoint]
                other = base / 'wrong checkout'
                other.mkdir()
                before = report.read_text()
                mismatch = run(*helper, '--repo', other, check=False)
                assert mismatch.returncode != 0 and 'not the selected checkout' in mismatch.stderr, mismatch.stderr
                assert report.read_text() == before, 'Wrong checkout submitted a firmware job'
                success = run(*helper, '--repo', root, check=False)
                assert success.returncode == 0, success.stdout + success.stderr
                assert 'without reconnecting' in success.stdout
                assert [json.loads(line) for line in report.read_text().splitlines()][-2:] == ['build', 'program-built']
                failure.touch()
                failed = run(*helper, '--repo', root, check=False)
                assert failed.returncode != 0 and 'failed' in failed.stderr.lower(), failed.stdout + failed.stderr
                assert client.status()['state']['connected'] is False
            finally:
                try:
                    client.shutdown()
                except (OSError, RuntimeError):
                    pass
                client.close()
                process.stdin.close()
                try:
                    process.wait(timeout=20)
                except subprocess.TimeoutExpired:
                    process.kill()
                    process.wait()
                log.seek(0)
                print(log.read())
    print('Published CLI contract and service flash passed: ' + version('ultrazohm-cli'))


if __name__ == '__main__':
    main()
