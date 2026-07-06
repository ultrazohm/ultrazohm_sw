from __future__ import annotations

from pathlib import Path

from PyQt6.QtWidgets import QApplication


DARK_STYLESHEET = """
QWidget {
    background-color: #202124;
    color: #e8eaed;
    selection-background-color: #2f6fed;
    selection-color: #ffffff;
}
QWidget:disabled,
QLabel:disabled,
QCheckBox:disabled,
QGroupBox:disabled {
    color: #8f949c;
}
QMainWindow,
QDialog {
    background-color: #202124;
}
QMenuBar,
QMenu {
    background-color: #2a2b2f;
    color: #e8eaed;
}
QMenuBar::item:selected,
QMenu::item:selected {
    background-color: #3a3d44;
}
QGroupBox {
    border: 1px solid #4a4d55;
    border-radius: 6px;
    margin-top: 10px;
    padding-top: 12px;
}
QGroupBox::title {
    subcontrol-origin: margin;
    left: 8px;
    padding: 0 4px;
}
QLineEdit,
QPlainTextEdit,
QTextEdit,
QComboBox,
QSpinBox,
QDoubleSpinBox,
QTableWidget,
QTreeWidget,
QTabWidget::pane {
    background-color: #2b2d31;
    color: #f1f3f4;
    border: 1px solid #4a4d55;
    border-radius: 4px;
}
QLineEdit:disabled,
QComboBox:disabled,
QPlainTextEdit:disabled,
QTextEdit:disabled {
    background-color: #24262a;
    color: #8f949c;
}
QPushButton {
    background-color: #34373d;
    color: #f1f3f4;
    border: 1px solid #5f6368;
    border-radius: 4px;
    padding: 5px 10px;
}
QPushButton:hover {
    background-color: #3e424a;
}
QPushButton:pressed {
    background-color: #4a4f58;
}
QPushButton:disabled {
    background-color: #27292d;
    color: #7b8088;
    border-color: #3b3e45;
}
QCheckBox::indicator {
    width: 15px;
    height: 15px;
    border: 1px solid #9aa0a6;
    border-radius: 3px;
    background-color: #2b2d31;
}
QCheckBox::indicator:hover {
    border-color: #c9d1d9;
}
QCheckBox::indicator:checked {
    background-color: #4c8bf5;
    border-color: #8ab4f8;
    image: url("__CHECKMARK_PATH__");
}
QCheckBox::indicator:checked:hover {
    background-color: #5b97f6;
}
QCheckBox::indicator:disabled {
    background-color: #24262a;
    border-color: #5f6368;
}
QHeaderView::section {
    background-color: #303238;
    color: #e8eaed;
    border: 1px solid #4a4d55;
}
QTabBar::tab {
    background-color: #2a2b2f;
    color: #dfe3ea;
    border: 1px solid #4a4d55;
    padding: 6px 10px;
}
QTabBar::tab:selected {
    background-color: #3a3d44;
}
QScrollBar:vertical,
QScrollBar:horizontal {
    background: #24262a;
    border: none;
}
QScrollBar::handle:vertical,
QScrollBar::handle:horizontal {
    background: #5f6368;
    border-radius: 4px;
}
QToolTip {
    background-color: #303238;
    color: #f1f3f4;
    border: 1px solid #5f6368;
}
"""


def set_dark_mode(app: QApplication, enabled: bool) -> None:
    checkmark_path = (Path(__file__).resolve().parent / "assets" / "checkmark.svg").as_posix()
    stylesheet = DARK_STYLESHEET.replace("__CHECKMARK_PATH__", checkmark_path) if enabled else ""
    if app.styleSheet() == stylesheet:
        return
    app.setStyleSheet(stylesheet)
