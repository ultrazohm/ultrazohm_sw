"""Validate the selected service and follow its flash job; all firmware control stays in CLI."""
import argparse
import json
import uuid
import os
from pathlib import Path
import sys
import time


def flash(client, monitor_type, repository, wait_seconds=0, debug_config=None):
    deadline = time.monotonic() + wait_seconds
    while True:
        try:
            status = client.status()
            break
        except (OSError, RuntimeError):
            if time.monotonic() >= deadline:
                raise RuntimeError('CLI service is unavailable. Check the interactive CLI terminal.')
            client.close()
            time.sleep(0.2)
    actual = status.get('repository')
    if not actual or not os.path.samefile(repository, actual):
        raise RuntimeError(f'CLI service uses {actual!r}, not the selected checkout {str(repository)!r}. Close or reconfigure that service before flashing.')
    if not status.get('firmware_available'):
        raise RuntimeError('CLI service has no usable XSCT. Restart it with the selected Vitis settings.')
    if status.get('active_job'):
        raise RuntimeError('The CLI service already has a firmware job. Wait for it to finish.')
    device = status.get('state', {}).get('device') or status.get('device_target')
    request = None
    ticket = None
    if debug_config:
        config = json.loads(Path(debug_config).read_text(encoding='utf-8'))
        if config['endpoint'] != client.endpoint or not os.path.samefile(config['root'], repository):
            raise RuntimeError('Debug launcher belongs to another service or checkout. Restart the interactive CLI from this extension.')
        request = {'service_id': status['service_id'], 'request_id': str(uuid.uuid4()), 'python': sys.executable}
        ticket = Path(config['ticket'])
        temporary = ticket.with_suffix('.tmp')
        temporary.write_text(json.dumps(request), encoding='utf-8')
        temporary.replace(ticket)
        Path(config['proof']).unlink(missing_ok=True)
    print(f'Flashing {repository} through {client.endpoint}.', flush=True)
    print('Debug: leave service disconnected while both cores are paused.' if request else
          'Reconnect to ' + str(device) if device else 'No device target: program without reconnecting.', flush=True)
    accepted = complete = False
    try:
        options = {'device': device, 'no_reconnect': bool(request) or not bool(device)}
        if request:
            options['request_id'] = request['request_id']
        job = client.firmware('flash', **options)
        accepted = True
        print(f"Firmware job {job['id']}. Closing this terminal does not cancel the service job.", flush=True)
        monitor = monitor_type(client, job['id'])
        while True:
            reply = monitor.poll()
            print(reply.get('log', ''), end='', flush=True)
            if monitor.complete:
                complete = True
                monitor.raise_for_status()
                if request and (not Path(config['proof']).exists() or Path(config['proof']).read_text(encoding='utf-8').strip() != request['request_id']):
                    raise RuntimeError('The service did not use the Debug launcher. Both cores were not confirmed at main; no debugger was attached.')
                print('Debug programming completed; both cores stopped at main.' if request else 'Flash UZ completed.', flush=True)
                return
            time.sleep(0.1)
    finally:
        # A lost monitor/closed terminal does not cancel an accepted CLI job.
        # Keep its request so the later programming step still stops at main.
        if ticket and (complete or not accepted):
            ticket.unlink(missing_ok=True)


def main():
    from ultrazohm_cli import Client
    from ultrazohm_cli.jobs import FirmwareJob
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--endpoint', required=True)
    parser.add_argument('--repo', type=Path, required=True)
    parser.add_argument('--wait-service', type=float, default=0)
    parser.add_argument('--debug-config', type=Path)
    args = parser.parse_args()
    client = Client(args.endpoint)
    try:
        flash(client, FirmwareJob, args.repo, args.wait_service, args.debug_config)
        return 0
    except (OSError, RuntimeError) as error:
        print(f'Flash UZ failed: {error}', file=sys.stderr)
        return 1
    finally:
        client.close()


if __name__ == '__main__':
    sys.exit(main())
