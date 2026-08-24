from __future__ import annotations

from pathlib import Path
from typing import Any, Callable

from PyQt6.QtCore import QProcess, Qt
from PyQt6.QtGui import QAction, QKeySequence, QPainter, QPalette
from PyQt6.QtWidgets import (
    QApplication,
    QComboBox,
    QCheckBox,
    QGroupBox,
    QHBoxLayout,
    QLabel,
    QLineEdit,
    QMainWindow,
    QMessageBox,
    QPlainTextEdit,
    QPushButton,
    QSplitter,
    QStackedWidget,
    QTabWidget,
    QTextEdit,
    QVBoxLayout,
    QWidget,
    QWidgetAction,
)

from ..paths import (
    CPLD_CONFIG_DIR,
    DATA_FILE,
    DIGITAL_SLOTS,
)
from ..repositories import CardDatabase
from ..services.software_generator_service import SoftwareGenerator
from ..services.system_resolver import SystemResolver
from ..theme import set_dark_mode
from ..tcl_generator import TclGenerator
from .adapter_card_details import AdapterCardDetailsWidget
from .mixins.config_workflow import ConfigWorkflowMixin
from .mixins.cpld_workflow import CpldWorkflowMixin
from .mixins.navigation import NavigationMixin
from .mixins.database_page import DatabasePageMixin
from .mixins.hardware_pages import HardwarePageMixin
from .mixins.platform_page import PlatformPageMixin
from .mixins.slot_cpld_page import SlotCpldPageMixin
from .mixins.software_pages import SoftwarePageMixin
from .mixins.tcl_generation_page import TclGenerationPageMixin
from .mixins.toolchain_page import ToolchainPageMixin
from .mixins.software_workflow import SoftwareWorkflowMixin
from .mixins.tcl_workflow import TclWorkflowMixin
from .mixins.view_state import ViewStateMixin


class MenuActionRow(QWidget):
    def __init__(self, text: str, shortcut: str, triggered: Callable[[], None], parent: QWidget | None = None) -> None:
        super().__init__(parent)
        self.triggered = triggered
        self.hovered = False
        self.setMinimumWidth(260)
        self.setMinimumHeight(28)
        self.setMouseTracking(True)

        layout = QHBoxLayout(self)
        layout.setContentsMargins(14, 4, 14, 4)
        layout.setSpacing(18)

        text_label = QLabel(text)
        shortcut_label = QLabel(shortcut)
        shortcut_font = shortcut_label.font()
        shortcut_font.setItalic(True)
        shortcut_font.setPointSize(max(1, shortcut_font.pointSize() - 1))
        shortcut_label.setFont(shortcut_font)
        shortcut_label.setStyleSheet("color: #777;")

        layout.addWidget(text_label)
        layout.addStretch(1)
        layout.addWidget(shortcut_label)

    def enterEvent(self, event) -> None:
        self.hovered = True
        self.update()
        super().enterEvent(event)

    def leaveEvent(self, event) -> None:
        self.hovered = False
        self.update()
        super().leaveEvent(event)

    def mouseReleaseEvent(self, event) -> None:
        if event.button() == Qt.MouseButton.LeftButton:
            self.triggered()
            return
        super().mouseReleaseEvent(event)

    def paintEvent(self, event) -> None:
        if self.hovered:
            painter = QPainter(self)
            painter.fillRect(self.rect(), self.palette().color(QPalette.ColorRole.Highlight))
        super().paintEvent(event)


class MainWindow(
    NavigationMixin,
    ToolchainPageMixin,
    PlatformPageMixin,
    HardwarePageMixin,
    TclGenerationPageMixin,
    SlotCpldPageMixin,
    SoftwarePageMixin,
    DatabasePageMixin,
    ViewStateMixin,
    CpldWorkflowMixin,
    SoftwareWorkflowMixin,
    ConfigWorkflowMixin,
    TclWorkflowMixin,
    QMainWindow,
):
    def __init__(self) -> None:
        super().__init__()
        self.setWindowTitle("Project Wizard")
        self.resize(1200, 760)
        self.database = CardDatabase.load(DATA_FILE)
        self.generator = TclGenerator(self.database)
        self.software_generator = SoftwareGenerator(self.database)
        self.system_resolver = SystemResolver(self.database)
        self.current_config_path: Path | None = None
        self.saved_config_snapshot = ""
        self.is_loading_config = True
        self.slot_combos: dict[str, QComboBox] = {}
        self.cpld_combos: dict[str, QComboBox] = {}
        self.axi_fields: dict[str, QLineEdit] = {}
        self.toolchain_fields: dict[str, QLineEdit] = {}
        self.hardware_fields: dict[str, QLineEdit] = {}
        self.hardware_checkboxes: dict[str, QCheckBox] = {}
        self.pwm_combos: dict[str, QComboBox] = {}
        self.pwm_checkboxes: dict[str, QCheckBox] = {}
        self.software_fields: dict[str, QLineEdit] = {}
        self.software_mode_combos: dict[str, QComboBox] = {}
        self.software_preset_combos: dict[str, QComboBox] = {}
        self.driver_config_mode_combos: dict[str, QComboBox] = {}
        self.driver_config_fields: dict[tuple[str, str], QLineEdit | QPlainTextEdit | QComboBox] = {}
        self.driver_config_tabs: QTabWidget | None = None
        self.driver_config_tab_layouts: dict[str, QVBoxLayout] = {}
        self.visualization_route_checkboxes: dict[str, tuple[QCheckBox, QCheckBox]] = {}
        self.visualization_tabs: QTabWidget | None = None
        self.visualization_tab_layouts: dict[str, QVBoxLayout] = {}
        self.software_preview: QPlainTextEdit | None = None
        self.software_status: QPlainTextEdit | None = None
        self.toolchain_status: QPlainTextEdit | None = None
        self.platform_cpld_group: QGroupBox | None = None
        self.platform_cpld_type_combo: QComboBox | None = None
        self.platform_nameplate_group: QGroupBox | None = None
        self.cpld_programmer_fields: dict[str, QLineEdit] = {}
        self.cpld_status: QTextEdit | None = None
        self.cpld_process: QProcess | None = None
        self.vivado_process: QProcess | None = None
        self.cpld_log_path: Path | None = None
        self.cpld_xcf_path: Path = CPLD_CONFIG_DIR / "project_wizard_slot_cplds.xcf"
        self.cpld_xcf_current = False
        self.write_cpld_button: QPushButton | None = None
        self.program_cpld_button: QPushButton | None = None
        self.import_cable_button: QPushButton | None = None
        self.tcl_disable_checkpoints_checkbox: QCheckBox | None = None
        self.tcl_remote_disable_checkpoints_checkbox: QCheckBox | None = None
        self.tcl_local_workflow_checkbox: QCheckBox | None = None
        self.tcl_remote_workflow_checkbox: QCheckBox | None = None
        self.tcl_local_workflow_content: QWidget | None = None
        self.tcl_remote_workflow_content: QWidget | None = None
        self.tcl_workflow_button: QPushButton | None = None
        self.vivado_status: QPlainTextEdit | None = None
        self.detail_options: dict[str, dict[str, str]] = {}
        self.adapter_details: AdapterCardDetailsWidget | None = None
        self.software_dependent_views_dirty = False
        self.bulk_update_disable_depth = 0
        self.dark_mode_action: QAction | None = None

        self.stack = QStackedWidget()
        self.tree = self._build_navigation()
        self.stack.addWidget(self._build_toolchain_page())
        self.stack.addWidget(self._build_platform_page())
        self.stack.addWidget(self._build_hardware_general_page())
        self.stack.addWidget(self._build_configuration_page())
        self.stack.addWidget(self._build_pwm_page())
        self.stack.addWidget(self._build_axi_interconnect_page())
        self.stack.addWidget(self._build_tcl_generation_page())
        self.stack.addWidget(self._build_slot_cpld_page())
        self.stack.addWidget(self._build_software_general_page())
        self.stack.addWidget(self._build_software_driver_page())
        self.stack.addWidget(self._build_advanced_driver_config_page())
        self.stack.addWidget(self._build_data_visualization_page())
        self.stack.addWidget(self._build_database_page())

        splitter = QSplitter()
        splitter.addWidget(self.tree)
        splitter.addWidget(self.stack)
        splitter.setSizes([250, 950])
        self.setCentralWidget(splitter)
        self._build_menu()
        try:
            self.refresh_platform_revisions()
            for slot in DIGITAL_SLOTS:
                self.prefill_cpld_for_slot(slot)
            self.reset_toolchain_config()
            self.reset_hardware_config()
            self.reset_software_config()
            self.reset_axi_config()
            self.rebuild_details()
        finally:
            self.is_loading_config = False
        self.refresh_dirty_software_dependent_views()
        self.refresh_tcl_preview()
        self.saved_config_snapshot = self.config_snapshot()

    def _build_menu(self) -> None:
        file_menu = self.menuBar().addMenu("File")

        self.add_file_menu_action(file_menu, "New config", QKeySequence.StandardKey.New, self.new_config)
        self.add_file_menu_action(file_menu, "Open config", QKeySequence.StandardKey.Open, self.open_config)
        self.add_file_menu_action(file_menu, "Save config", QKeySequence.StandardKey.Save, self.save_config)
        self.add_file_menu_action(file_menu, "Save config as", QKeySequence.StandardKey.SaveAs, self.save_config_as)

        file_menu.addSeparator()
        self.add_file_menu_action(file_menu, "Quit", QKeySequence("Ctrl+Q"), self.close)

        edit_menu = self.menuBar().addMenu("Edit")
        card_database_action = QAction("Card database", self)
        card_database_action.triggered.connect(self.show_card_database)
        edit_menu.addAction(card_database_action)

        view_menu = self.menuBar().addMenu("View")
        toolchain_action = QAction("Toolchain", self)
        toolchain_action.triggered.connect(self.show_toolchain_page)
        view_menu.addAction(toolchain_action)

        platform_action = QAction("Platform", self)
        platform_action.triggered.connect(self.show_platform_page)
        view_menu.addAction(platform_action)

        hardware_general_action = QAction("Hardware general", self)
        hardware_general_action.triggered.connect(self.show_hardware_general)
        view_menu.addAction(hardware_general_action)

        adapter_cards_action = QAction("Adapter cards", self)
        adapter_cards_action.triggered.connect(self.show_adapter_cards)
        view_menu.addAction(adapter_cards_action)

        axi_action = QAction("ADC triggers", self)
        axi_action.triggered.connect(self.show_axi_interconnect)
        view_menu.addAction(axi_action)

        tcl_generation_action = QAction("TCL generation", self)
        tcl_generation_action.triggered.connect(self.show_tcl_generation)
        view_menu.addAction(tcl_generation_action)

        slot_cplds_action = QAction("Slot CPLDs", self)
        slot_cplds_action.triggered.connect(self.show_slot_cplds)
        view_menu.addAction(slot_cplds_action)

        software_general_action = QAction("Software general", self)
        software_general_action.triggered.connect(self.show_software_general)
        view_menu.addAction(software_general_action)

        ip_driver_action = QAction("IP core driver setup", self)
        ip_driver_action.triggered.connect(self.show_ip_core_driver_setup)
        view_menu.addAction(ip_driver_action)

        advanced_driver_action = QAction("Advanced driver configuration", self)
        advanced_driver_action.triggered.connect(self.show_advanced_driver_config)
        view_menu.addAction(advanced_driver_action)

        data_visualization_action = QAction("Data visualization", self)
        data_visualization_action.triggered.connect(self.show_data_visualization)
        view_menu.addAction(data_visualization_action)

        view_menu.addSeparator()
        dark_mode_action = QAction("Dark mode", self)
        dark_mode_action.setCheckable(True)
        dark_mode_action.triggered.connect(self.set_dark_mode_enabled)
        self.dark_mode_action = dark_mode_action
        view_menu.addAction(dark_mode_action)

        help_menu = self.menuBar().addMenu("Help")
        docs_action = QAction("Docs", self)
        docs_action.triggered.connect(self.show_docs)
        help_menu.addAction(docs_action)

        info_action = QAction("Info", self)
        info_action.triggered.connect(self.show_info)
        help_menu.addAction(info_action)

    def _help_button(self, title: str, text: str) -> QPushButton:
        button = QPushButton("?")
        button.setFixedWidth(28)
        button.setToolTip(title)
        button.clicked.connect(lambda _checked=False: QMessageBox.information(self, title, text))
        return button

    def add_file_menu_action(
        self,
        menu,
        text: str,
        shortcut: QKeySequence | QKeySequence.StandardKey,
        handler: Callable[[], Any],
    ) -> QAction:
        action = QAction(text, self)
        action.setShortcut(shortcut)
        action.triggered.connect(handler)
        self.addAction(action)

        widget_action = QWidgetAction(menu)
        shortcut_text = action.shortcut().toString(QKeySequence.SequenceFormat.NativeText)

        def trigger_action() -> None:
            menu.close()
            action.trigger()

        widget_action.setDefaultWidget(MenuActionRow(text, shortcut_text, trigger_action, menu))
        menu.addAction(widget_action)
        return action

    def set_dark_mode_enabled(self, enabled: bool) -> None:
        set_dark_mode(QApplication.instance(), enabled)
        if self.dark_mode_action is not None:
            self.dark_mode_action.blockSignals(True)
            self.dark_mode_action.setChecked(enabled)
            self.dark_mode_action.blockSignals(False)

    def closeEvent(self, event) -> None:
        dialog = QMessageBox(self)
        dialog.setIcon(QMessageBox.Icon.Question)
        dialog.setWindowTitle("Quit Project Wizard")
        dialog.setText("Do you really want to quit Project Wizard?")
        quit_button = dialog.addButton("Quit", QMessageBox.ButtonRole.AcceptRole)
        cancel_button = dialog.addButton(QMessageBox.StandardButton.Cancel)
        dialog.setDefaultButton(cancel_button)
        dialog.exec()
        if dialog.clickedButton() == quit_button:
            if not self.confirm_save_config_changes("quitting"):
                event.ignore()
                return
            event.accept()
            return
        event.ignore()

