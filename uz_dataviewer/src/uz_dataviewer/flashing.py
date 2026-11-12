"""Vendor tool preferences and managed flashing execution."""
import json
import os
import shutil
from pathlib import Path

from .cli_console import CliConsole
from .user_paths import write_json


def xsct_available():
    names = ('xsct.exe', 'xsct.cmd', 'xsct.bat') if os.name == 'nt' else ('xsct',)
    return any(shutil.which(name) is not None for name in names)


def _valid_launcher(launcher):
    return (launcher.name.lower() in ('xsct', 'xsct.exe', 'xsct.cmd', 'xsct.bat')
            and launcher.is_file()
            and (os.name == 'nt' or os.access(launcher, os.X_OK)))


def select_xsct(path, repo=None):
    """Remember the vendor launcher and expose it to this process's children."""
    from .user_paths import data_directory
    launcher = Path(path).expanduser().resolve()
    if not _valid_launcher(launcher):
        raise ValueError('Select an executable XSCT launcher (xsct, xsct.exe, xsct.cmd or xsct.bat) in the Vitis bin directory')
    settings = data_directory(repo) / 'tools.json'
    values = _read_tools(settings) if settings.exists() else {}
    values['xsct'] = str(launcher)
    write_json(settings, values)
    _add_tool_directory(launcher.parent)


def _add_tool_directory(directory):
    entries = os.environ.get('PATH', '').split(os.pathsep)
    value = str(directory)
    os.environ['PATH'] = os.pathsep.join([value, *(entry for entry in entries if entry != value)])


def restore_xsct(repo=None):
    from .user_paths import data_directory
    settings = data_directory(repo) / 'tools.json'
    if settings.is_file():
        saved = _read_tools(settings).get('xsct')
        if not saved:
            return
        launcher = Path(saved)
        if not _valid_launcher(launcher):
            raise ValueError(f'Saved XSCT launcher no longer exists: {launcher}. Browse to select it again.')
        _add_tool_directory(launcher.parent)


def _read_tools(path):
    values = json.loads(path.read_text(encoding='utf-8'))
    if not isinstance(values, dict) or (values.get('xsct') is not None and not isinstance(values['xsct'], str)):
        raise ValueError(f'Invalid tool preferences in {path}: expected an object with an XSCT path or null')
    return values


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
