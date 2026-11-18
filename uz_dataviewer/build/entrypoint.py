"""Dedicated PyInstaller entry point.

PyInstaller runs the bundled entry script as top-level ``__main__`` with no
package context, so it must use an *absolute* import (``__main__.py``'s relative
``from .cli import main`` only works under ``python -m uz_dataviewer``). The
``uz_dataviewer`` package is put on the path via the spec's ``pathex``.
"""

from __future__ import annotations

import sys


if __name__ == "__main__":
    import multiprocessing
    multiprocessing.freeze_support()
    if len(sys.argv) > 1 and sys.argv[1] == '--internal-worker':
        from uz_dataviewer.process_launcher import main
        sys.exit(main(sys.argv[2:]))
    if len(sys.argv) == 3 and sys.argv[1] == "--self-test":
        # A windowed Windows bootloader presents unhandled exceptions in a
        # modal dialog. CI cannot dismiss it, hiding the failure until timeout.
        import json
        from pathlib import Path
        import traceback
        try:
            from frozen_self_test import run
            run(sys.argv[2])
        except Exception:
            Path(sys.argv[2]).write_text(json.dumps({"ok": False, "error": traceback.format_exc()}),
                                         encoding="utf-8")
            sys.exit(1)
    else:
        from uz_dataviewer.cli import main
        sys.exit(main())
