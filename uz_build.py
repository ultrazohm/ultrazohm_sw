"""Cross-process locks for shared build outputs, including bind-mounted checkouts."""

import os
from contextlib import contextmanager
from pathlib import Path


@contextmanager
def build_lock(root, project):
    # Keep the lock on the shared filesystem, not in host/container-specific /tmp.
    directory = Path(root) / ".uz-build-locks"
    directory.mkdir(exist_ok=True)
    with (directory / f"{project}.lock").open("a+b") as stream:
        if stream.tell() == 0:
            stream.write(b"0")
            stream.flush()
        stream.seek(0)
        try:
            if os.name == "nt":
                import msvcrt

                msvcrt.locking(stream.fileno(), msvcrt.LK_NBLCK, 1)
            else:
                import fcntl

                fcntl.flock(stream, fcntl.LOCK_EX | fcntl.LOCK_NB)
        except OSError as error:
            raise RuntimeError(
                f"Another {project} build is using this checkout's outputs; retry when it finishes."
            ) from error
        try:
            yield
        finally:
            if os.name == "nt":
                msvcrt.locking(stream.fileno(), msvcrt.LK_UNLCK, 1)
            else:
                fcntl.flock(stream, fcntl.LOCK_UN)
    # Never unlink lock files: another process may already have one open.
