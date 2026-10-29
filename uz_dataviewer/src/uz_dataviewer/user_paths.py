"""Workspace-owned viewer data, separated by source and standalone mode."""
from pathlib import Path
import json
import os
import sys
import tempfile


def data_directory(repo=None):
    if repo is not None:
        root = Path(repo).expanduser().resolve()
    else:
        # Source startup from a repository subdirectory, or standalone analysis.
        root = Path.cwd()
        for candidate in (root, *root.parents):
            if (candidate / 'vitis/software/Baremetal/src/include/javascope.h').is_file():
                root = candidate
                break
    directory = '_user_standalone' if getattr(sys, 'frozen', False) else '_user'
    path = root / 'artifacts' / directory
    path.mkdir(parents=True, exist_ok=True)
    return path


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
                os.link(temporary, path)
            except FileExistsError:
                pass
    finally:
        Path(temporary).unlink(missing_ok=True)
