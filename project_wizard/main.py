from __future__ import annotations

import sys
from importlib import import_module
from pathlib import Path

if __package__ is None or __package__ == "":
    sys.path.insert(0, str(Path(__file__).resolve().parent.parent))

package_name = Path(__file__).resolve().parent.name
main = import_module(f"{package_name}.app").main


if __name__ == "__main__":
    raise SystemExit(main())
