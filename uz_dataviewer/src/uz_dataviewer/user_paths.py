"""Workspace-owned viewer data, separated by source and standalone mode."""
from pathlib import Path
import json
import os
import sys
import tempfile


HEADER = Path("vitis/software/Baremetal/src/include/javascope.h")


def find_repository(start):
    """Find a firmware checkout above a path without creating directories."""
    start = Path(start).expanduser().resolve()
    return next((root for root in (start, *start.parents)
                 if (root / HEADER).is_file()), None)


def data_directory(repo=None):
    if repo is not None:
        root = Path(repo).expanduser().resolve()
    else:
        # Source startup from a repository subdirectory, or standalone analysis.
        root = find_repository(Path.cwd()) or Path.cwd()
    directory = '_user_standalone' if getattr(sys, 'frozen', False) else '_user'
    path = root / 'artifacts' / directory
    path.mkdir(parents=True, exist_ok=True)
    return path


def publish_new(temporary, destination):
    """Publish a complete file as ``destination`` without replacing an existing one.

    Raises FileExistsError when ``destination`` exists. The caller removes
    ``temporary`` afterwards if it still exists.
    """
    if sys.platform == 'win32':
        # Windows rename refuses an existing destination and works on
        # FAT/shares without hard-link support.
        os.rename(temporary, destination)
        return
    try:
        os.link(temporary, destination)
    except FileExistsError:
        raise
    except OSError:
        # FAT, exFAT and some network shares have no hard links: check, then rename.
        if os.path.lexists(destination):
            raise FileExistsError(f'{destination} already exists') from None
        os.rename(temporary, destination)


def write_json(path, value, *, overwrite=True):
    """Publish complete JSON; optionally leave an existing destination untouched."""
    path = Path(path)
    if not overwrite and path.exists():
        return
    data = json.dumps(value, indent=2, allow_nan=False)
    fd, temporary = tempfile.mkstemp(prefix='.uz-json-', suffix='.tmp', dir=path.parent)
    try:
        with os.fdopen(fd, 'w', encoding='utf-8') as output:
            output.write(data)
        if overwrite:
            os.replace(temporary, path)
        else:
            try:
                publish_new(temporary, path)
            except FileExistsError:
                pass
    finally:
        Path(temporary).unlink(missing_ok=True)
