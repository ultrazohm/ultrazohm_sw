"""Per-instance credentials discovered by clients running as the same OS user."""
import hashlib
import os
from pathlib import Path
import stat
import tempfile

from .control_protocol import address


def credential_path(endpoint):
    identity = hashlib.sha256(str(Path.home()).encode()).hexdigest()[:16]
    directory = Path(tempfile.gettempdir()) / f'ultrazohm-dataviewer-{identity}'
    directory.mkdir(mode=0o700, exist_ok=True)
    details = directory.lstat()
    if not stat.S_ISDIR(details.st_mode):
        raise PermissionError('Viewer credential directory must not be a symbolic link')
    if os.name != 'nt' and (details.st_uid != os.getuid() or details.st_mode & 0o077):
        raise PermissionError('Viewer credential directory must be private to the current user')
    host, port = address(endpoint)
    key = hashlib.sha256(f'{host}:{port}'.encode()).hexdigest()
    return directory / f'{key}.token'


def publish(endpoint, token):
    path = credential_path(endpoint)
    temporary = None
    try:
        with tempfile.NamedTemporaryFile(mode='w', encoding='ascii', dir=path.parent,
                                         delete=False) as stream:
            temporary = Path(stream.name)
            stream.write(token)
        os.replace(temporary, path)
    finally:
        if temporary is not None:
            temporary.unlink(missing_ok=True)
    return path


def discover(endpoint):
    path = credential_path(endpoint)
    try:
        return path.read_text(encoding='ascii')
    except FileNotFoundError:
        return ''


def remove(path, token):
    try:
        if path.read_text(encoding='ascii') == token:
            path.unlink(missing_ok=True)
    except FileNotFoundError:
        pass
