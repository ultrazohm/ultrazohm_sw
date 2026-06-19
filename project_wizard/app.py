from __future__ import annotations

import sys
import traceback

try:
    from PyQt6.QtWidgets import QApplication, QMessageBox
except ModuleNotFoundError as error:
    if error.name != "PyQt6":
        raise
    print("PyQt6 is not installed. Run: pip install -r requirements.txt", file=sys.stderr)
    raise SystemExit(1) from error

from .views.main_window import MainWindow
from .theme import set_dark_mode


def show_uncaught_exception(exc_type, exc_value, exc_traceback) -> None:
    details = "".join(traceback.format_exception(exc_type, exc_value, exc_traceback))
    print(details, file=sys.stderr)
    try:
        QMessageBox.critical(
            None,
            "Project Wizard error",
            "An unexpected error occurred.\n\n"
            f"{exc_type.__name__}: {exc_value}\n\n"
            "Details were also written to the console.",
        )
    except RuntimeError:
        pass


def main() -> int:
    app = QApplication(sys.argv)
    set_dark_mode(app, True)
    sys.excepthook = show_uncaught_exception
    window = MainWindow()
    window.set_dark_mode_enabled(True)
    window.show()
    return app.exec()
