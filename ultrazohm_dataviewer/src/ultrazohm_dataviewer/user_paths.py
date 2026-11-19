"""Workspace-owned viewer data, separated by source and standalone mode."""

import json
import os
import sys
import tempfile
from pathlib import Path

HEADER = Path("vitis/software/Baremetal/src/include/javascope.h")


def find_repository(start):
    """Find a firmware checkout above a path without creating directories."""
    start = Path(start).expanduser().resolve()
    return next(
        (root for root in (start, *start.parents) if (root / HEADER).is_file()), None
    )


def user_data_directory():
    """Per-user viewer data used until a firmware checkout is known."""
    if sys.platform == "win32":
        base = (
            Path(os.environ.get("LOCALAPPDATA") or Path.home() / "AppData" / "Local")
            / "UltraZohm"
        )
    else:
        base = (
            Path(os.environ.get("XDG_DATA_HOME") or Path.home() / ".local" / "share")
            / "ultrazohm"
        )
    return base / "ultrazohm_dataviewer"


def data_directory(repo=None):
    """Viewer data: ``<checkout>/artifacts/_user`` for source and bundle alike.

    Without an explicit checkout, the one containing the working directory is
    used; outside any checkout, the per-user directory, never the working directory.
    """
    if repo is not None:
        root = Path(repo).expanduser().resolve()
    else:
        root = find_repository(Path.cwd())
    path = root / "artifacts" / "_user" if root is not None else user_data_directory()
    path.mkdir(parents=True, exist_ok=True)
    return path


def publish_new(temporary, destination):
    """Publish a complete file as ``destination`` without replacing an existing one.

    Raises FileExistsError when ``destination`` exists. The caller removes
    ``temporary`` afterwards if it still exists.
    """
    if sys.platform == "win32":
        # Windows rename refuses an existing destination and works on
        # FAT/shares without hard-link support.
        os.rename(temporary, destination)
        return
    try:
        os.link(temporary, destination)
    except FileExistsError:
        raise
    except OSError:
        # Use the OS no-replace rename, never a check followed by replacing rename.
        import ctypes
        import errno

        library = ctypes.CDLL(None, use_errno=True)
        if sys.platform.startswith("linux"):
            function = library.renameat2
            function.argtypes = [
                ctypes.c_int,
                ctypes.c_char_p,
                ctypes.c_int,
                ctypes.c_char_p,
                ctypes.c_uint,
            ]
            result = function(
                -100, os.fsencode(temporary), -100, os.fsencode(destination), 1
            )
        elif sys.platform == "darwin":
            function = library.renamex_np
            function.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_uint]
            result = function(os.fsencode(temporary), os.fsencode(destination), 4)
        else:
            raise OSError(
                errno.ENOTSUP, "Atomic publication without replacement is unsupported"
            )
        if result:
            code = ctypes.get_errno()
            raise OSError(code, os.strerror(code), str(destination))


def write_json(path, value, *, overwrite=True):
    """Publish complete JSON; optionally leave an existing destination untouched."""
    path = Path(path)
    if not overwrite and path.exists():
        return
    data = json.dumps(value, indent=2, allow_nan=False)
    fd, temporary = tempfile.mkstemp(prefix=".uz-json-", suffix=".tmp", dir=path.parent)
    try:
        with os.fdopen(fd, "w", encoding="utf-8") as output:
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
