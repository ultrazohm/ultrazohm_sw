"""Cross-process leases for the checkout's managed Python environment."""

import hashlib
import os
import subprocess
import sys
import tempfile
import uuid
from contextlib import contextmanager
from pathlib import Path


@contextmanager
def file_lock(path):
    with path.open("a+b") as stream:
        if path.stat().st_size == 0:
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
                "The managed environment is in use; close its applications and shells first."
            ) from error
        try:
            yield
        finally:
            if os.name == "nt":
                stream.seek(0)
                msvcrt.locking(stream.fileno(), msvcrt.LK_UNLCK, 1)
            else:
                fcntl.flock(stream, fcntl.LOCK_UN)


@contextmanager
def environment_lock(root, *, use=False):
    identity = hashlib.sha256(str(Path(root).resolve()).encode()).hexdigest()
    directory = Path(tempfile.gettempdir()) / f"uz-environment-{identity}"
    directory.mkdir(exist_ok=True, mode=0o700)
    lease = directory / (uuid.uuid4().hex + ".lease")
    held = None
    try:
        with file_lock(directory / "gate"):
            if use:
                held = file_lock(lease)
                held.__enter__()
            else:
                for previous in directory.glob("*.lease"):
                    with file_lock(previous):
                        pass
                    previous.unlink(missing_ok=True)
                yield
                return
        yield
    finally:
        if held is not None:
            held.__exit__(None, None, None)
            # Reap stale leases under the gate on the next mutation. Unlinking
            # here races with a Windows scanner opening the same file.


def main():
    root, *command = sys.argv[1:]
    with environment_lock(root, use=True):
        with subprocess.Popen(command) as child:
            while True:
                try:
                    return child.wait()
                except KeyboardInterrupt:
                    continue


if __name__ == "__main__":
    raise SystemExit(main())
