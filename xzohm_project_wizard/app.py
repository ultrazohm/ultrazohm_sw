from __future__ import annotations

import sys

try:
    from PyQt6.QtWidgets import QApplication
except ModuleNotFoundError as error:
    if error.name != "PyQt6":
        raise
    print("PyQt6 is not installed. Run: pip install -r requirements.txt", file=sys.stderr)
    raise SystemExit(1) from error

from .views.main_window import MainWindow


def main() -> int:
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    return app.exec()
