"""Dedicated PyInstaller entry point.

PyInstaller runs the bundled entry script as top-level ``__main__`` with no
package context, so it must use an *absolute* import (``__main__.py``'s relative
``from .cli import main`` only works under ``python -m ultrazohm_dataviewer``). The
``ultrazohm_dataviewer`` package is put on the path via the spec's ``pathex``.
"""

from __future__ import annotations

import sys

if __name__ == "__main__":
    import multiprocessing

    multiprocessing.freeze_support()
    if "--cli" in sys.argv[1:2]:
        sys.argv.pop(1)
        from ultrazohm_dataviewer.windows_console import initialize

        initialize()
    if len(sys.argv) > 1 and sys.argv[1] == "--internal-worker":
        from ultrazohm_dataviewer.process_launcher import main

        sys.exit(main(sys.argv[2:]))
    if len(sys.argv) == 3 and sys.argv[1] == "--self-test":
        # A windowed Windows bootloader presents unhandled exceptions in a
        # modal dialog. CI cannot dismiss it, hiding the failure until timeout.
        import json
        import traceback
        from pathlib import Path

        try:
            from frozen_self_test import run

            run(sys.argv[2])
        except Exception:
            Path(sys.argv[2]).write_text(
                json.dumps({"ok": False, "error": traceback.format_exc()}),
                encoding="utf-8",
            )
            sys.exit(1)
    else:
        from ultrazohm_dataviewer.cli import main

        sys.exit(main())
