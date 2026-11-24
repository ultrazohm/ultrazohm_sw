"""Validate the selected service and follow its flash job; all firmware control stays in CLI."""
import argparse
import os
from pathlib import Path
import sys
import time


def flash(client, monitor_type, repository, wait_seconds=0):
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
    print(f'Flashing {repository} through {client.endpoint}.', flush=True)
    print('Reconnect to ' + str(device) if device else 'No device target: program without reconnecting.', flush=True)
    job = client.firmware('flash', device=device, no_reconnect=not bool(device))
    print(f"Firmware job {job['id']}. Closing this terminal does not cancel the service job.", flush=True)
    monitor = monitor_type(client, job['id'])
    while True:
        reply = monitor.poll()
        print(reply.get('log', ''), end='', flush=True)
        if monitor.complete:
            monitor.raise_for_status()
            print('Flash UZ completed.', flush=True)
            return
        time.sleep(0.1)


def main():
    from ultrazohm_cli import Client
    from ultrazohm_cli.jobs import FirmwareJob
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--endpoint', required=True)
    parser.add_argument('--repo', type=Path, required=True)
    parser.add_argument('--wait-service', type=float, default=0)
    args = parser.parse_args()
    client = Client(args.endpoint)
    try:
        flash(client, FirmwareJob, args.repo, args.wait_service)
        return 0
    except (OSError, RuntimeError) as error:
        print(f'Flash UZ failed: {error}', file=sys.stderr)
        return 1
    finally:
        client.close()


if __name__ == '__main__':
    sys.exit(main())
