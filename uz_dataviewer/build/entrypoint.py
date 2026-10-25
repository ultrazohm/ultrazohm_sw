"""Dedicated PyInstaller entry point.

PyInstaller runs the bundled entry script as top-level ``__main__`` with no
package context, so it must use an *absolute* import (``__main__.py``'s relative
``from .app import main`` only works under ``python -m uz_dataviewer``). The
``uz_dataviewer`` package is put on the path via the spec's ``pathex``.
"""

from __future__ import annotations

import sys

from uz_dataviewer.app import main

if __name__ == "__main__":
    import multiprocessing
    multiprocessing.freeze_support()
    if len(sys.argv) == 3 and sys.argv[1] == "--self-test":
        from frozen_self_test import run
        run(sys.argv[2])
    else:
        sys.exit(main())
