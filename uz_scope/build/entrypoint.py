"""Dedicated PyInstaller entry point.

PyInstaller runs the bundled entry script as top-level ``__main__`` with no
package context, so it must use an *absolute* import. The ``uz_scope`` and
``uz_dataviewer`` packages are put on the path via the spec's ``pathex``.
"""

from __future__ import annotations

import sys

from uz_scope.app import main

if __name__ == "__main__":
    sys.exit(main())
