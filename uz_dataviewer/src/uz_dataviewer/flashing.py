"""Shared CLI execution and profile preparation for managed viewer flashing."""
import json
import os
import shutil
import subprocess

from .cli_console import CliConsole


def xsct_available():
    names = ('xsct.exe', 'xsct.cmd', 'xsct.bat') if os.name == 'nt' else ('xsct',)
    return any(shutil.which(name) is not None for name in names)


def connection_refused(error):
    text = str(error).lower()
    return (isinstance(error, ConnectionRefusedError) or 'connection refused' in text or
            'os error 10061' in text or 'actively refused' in text)


def run_flash_cli(repo, endpoint, stop_event, emit):
    if stop_event.is_set():
        return False
    class Output:
        def info(self, text): emit('info', text)
        def ok(self, text): emit('ok', text)
        def error(self, text): emit('error', text)
    runner = CliConsole(Output())
    try:
        job = runner.submit_arguments(['flash', '--repo', str(repo)], endpoint)
        if job is None:
            raise RuntimeError('CLI wheel unavailable; live is not activated')
        while job.returncode is None:
            if stop_event.is_set():
                return False  # The detached CLI finishes programming; do not reconnect after GUI exit.
            runner.poll()
            stop_event.wait(.05)
        if job.returncode != 0:
            raise RuntimeError(f'Flashing failed (exit {job.returncode}); see Console output')
        return True
    finally:
        runner.close()


def profile_for_mapping(repo, mapping, previous, assignments):
    if previous:
        settings = previous
    else:
        from .process_launcher import command
        result = subprocess.run(command('cli', 'profile'), capture_output=True,
                                text=True, check=True, timeout=15)
        settings = json.loads(result.stdout)
    initial = assignments if assignments is not None else settings.get('initial_channels', {})
    selected, removed = {}, []
    for channel, name in initial.items():
        canonical = name if name in mapping['observables'] else f'JSO_{name}'
        if canonical in mapping['observables'] and 1 <= int(channel) <= mapping['channels']:
            selected[str(channel)] = canonical
        else:
            removed.append(name)
    if not selected:
        selected['1'] = 'JSO_ZEROVALUE'
    return {'schema_version': 1, 'name': settings.get('name', 'viewer-flash'),
            'sample_period_us': settings['sample_period_us'], 'initial_channels': selected}, removed
