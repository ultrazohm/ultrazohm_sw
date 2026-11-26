"""Extension-owned XSCT proxy. Ordinary jobs execute the unmodified launcher."""
import json
import os
from pathlib import Path
import subprocess
import sys


def read_json(path):
    return json.loads(Path(path).read_text(encoding='utf-8'))


def matching_request(config, request, status):
    job = status.get('active_job') or {}
    return (status.get('service_id') == request.get('service_id')
            and job.get('request_id') == request.get('request_id')
            and job.get('action') == 'flash'
            and job.get('state') == 'running'
            and os.path.samefile(status['repository'], config['root']))


def run(config_path, arguments, validate=False):
    config = read_json(config_path)
    script_index = next((i for i, arg in enumerate(arguments) if arg.endswith('vitis_headless.tcl')), None)
    programming = script_index is not None and arguments[script_index + 1:script_index + 2] == ['program-built']
    ticket = Path(config['ticket'])
    if programming and ticket.exists():
        request = read_json(ticket)
        if not validate:
            # flash.py supplies the interpreter from the selected PyPI CLI environment.
            # No packages are installed into the bundled base interpreter.
            return subprocess.call([request['python'], '-B', __file__, '--validate', config_path, *arguments])
        from ultrazohm_cli import Client
        client = Client(config['endpoint'])
        try:
            matches = matching_request(config, request, client.status())
        finally:
            client.close()
        if matches:
            proof = Path(config['proof'])
            proof.unlink(missing_ok=True)
            env = dict(os.environ, UZ_DEBUG_ENTRY=arguments[script_index], UZ_DEBUG_PROOF=str(proof), UZ_DEBUG_REQUEST=request['request_id'])
            arguments[script_index] = str(Path(__file__).with_name('debug-main.tcl'))
            code = subprocess.call([config['xsct'], *arguments], env=env)
            if code:
                return code
            if not proof.exists() or proof.read_text(encoding='utf-8').strip() != request['request_id']:
                raise RuntimeError('XSCT did not confirm both cores stopped at main; debugger attachment was cancelled.')
            return 0
    return subprocess.call([config['xsct'], *arguments])


if __name__ == '__main__':
    args = sys.argv[1:]
    validate = args[0:1] == ['--validate']
    if validate:
        args.pop(0)
    try:
        sys.exit(run(args[0], args[1:], validate))
    except (OSError, ValueError, RuntimeError) as error:
        print('UltraZohm debug launcher: ' + str(error), file=sys.stderr, flush=True)
        sys.exit(1)
