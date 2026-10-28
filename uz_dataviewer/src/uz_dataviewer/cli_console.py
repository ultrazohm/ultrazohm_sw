"""Shell-free CLI subprocesses with incremental output, polled by the GUI."""
from dataclasses import dataclass, field
import codecs
import importlib.util
import os
from pathlib import Path
import shlex
import shutil
import subprocess
import sys
import tempfile


def arguments(text, *, windows=None):
    lexer = shlex.shlex(text, posix=True)
    lexer.whitespace_split = True
    lexer.commenters = ''
    if windows is None:
        windows = os.name == 'nt'
    if windows:
        lexer.escape = ''  # Preserve Windows paths, including unquoted backslashes.
    return list(lexer)


@dataclass
class Job:
    number: int
    process: subprocess.Popen
    path: Path
    offset: int = 0
    returncode: int | None = None
    pending: str = ''
    decoder: object = field(default_factory=lambda: codecs.getincrementaldecoder('utf-8')(errors='replace'))


class CliConsole:
    """Run up to four independent debug commands; never call GUI code in a child."""
    def __init__(self, console, directory=None):
        self.console = console
        self.directory = Path(directory) if directory is not None else None
        self.jobs = []
        self.sequence = 0
        self.closed = False

    def submit(self, text, endpoint):
        return self.submit_arguments(arguments(text) or ['--help'], endpoint)

    def submit_arguments(self, args, endpoint):
        if self.closed:
            raise RuntimeError('CLI console is closed')
        if importlib.util.find_spec('ultrazohm') is None:
            self.console.error('Live is not activated.')
            return
        if getattr(sys, 'frozen', False):
            raise RuntimeError('CLI debugging requires the Python source launcher')
        if len(self.jobs) >= 4:
            raise RuntimeError('Four CLI commands are already running; wait for one to finish')
        if not any(arg == '--endpoint' or arg.startswith('--endpoint=') for arg in args):
            args = ['--endpoint', endpoint, *args]
        if self.directory is None:
            self.directory = Path(tempfile.mkdtemp(prefix='uz-cli-console-'))
        self.directory.mkdir(parents=True, exist_ok=True)
        self.sequence += 1
        path = self.directory / f'command-{self.sequence}.log'
        env = os.environ.copy()
        env['PYTHONIOENCODING'] = 'utf-8'
        options = {'start_new_session': True} if os.name != 'nt' else {
            'creationflags': subprocess.DETACHED_PROCESS | subprocess.CREATE_NEW_PROCESS_GROUP}
        with path.open('wb') as output:
            process = subprocess.Popen([sys.executable, '-u', '-m', 'ultrazohm', *args],
                stdin=subprocess.DEVNULL, stdout=output, stderr=subprocess.STDOUT, env=env, **options)
        job = Job(self.sequence, process, path)
        self.jobs.append(job)
        self.console.info(f'uz #{self.sequence} started')
        return job

    def _emit(self, job, text, final=False):
        job.pending += text
        while '\n' in job.pending:
            line, job.pending = job.pending.split('\n', 1)
            self.console.info(f'uz #{job.number}: {line.rstrip(chr(13))}')
        # Bound partial lines too, for tools that emit unusually long lines.
        while len(job.pending) > 16384:
            self.console.info(f'uz #{job.number}: {job.pending[:16384]}')
            job.pending = job.pending[16384:]
        if final and job.pending:
            self.console.info(f'uz #{job.number}: {job.pending}')
            job.pending = ''

    def poll(self):
        for job in list(self.jobs):
            with job.path.open('rb') as output:
                output.seek(job.offset)
                data = output.read(65536)
            job.offset += len(data)
            self._emit(job, job.decoder.decode(data))
            code = job.process.poll()
            if code is not None and job.offset >= job.path.stat().st_size:
                job.returncode = code
                self._emit(job, job.decoder.decode(b'', final=True), final=True)
                if code == 0:
                    self.console.ok(f'uz #{job.number} finished')
                else:
                    self.console.error(f'uz #{job.number} exited with code {code}')
                self.jobs.remove(job)

    def close(self):
        # Debug tools (including flashing) run independently of the viewer. Files
        # avoid broken pipes when it exits; active jobs keep their output logs.
        if self.closed:
            return
        self.closed = True
        if self.directory is not None and not any(job.process.poll() is None for job in self.jobs):
            shutil.rmtree(self.directory, ignore_errors=True)
        self.jobs.clear()
