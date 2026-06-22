from __future__ import annotations

import json
import html
from copy import deepcopy
from pathlib import Path
from typing import Any

from PyQt6.QtCore import QProcess, Qt, QTimer
from PyQt6.QtGui import QAction, QFont
from PyQt6.QtWidgets import (
    QApplication,
    QComboBox,
    QCheckBox,
    QFileDialog,
    QFormLayout,
    QGridLayout,
    QGroupBox,
    QHBoxLayout,
    QLabel,
    QLineEdit,
    QMainWindow,
    QMessageBox,
    QPlainTextEdit,
    QProgressDialog,
    QPushButton,
    QScrollArea,
    QSplitter,
    QStackedWidget,
    QTableWidget,
    QTableWidgetItem,
    QTabWidget,
    QTextEdit,
    QTreeWidget,
    QTreeWidgetItem,
    QVBoxLayout,
    QWidget,
)

from ..paths import APP_DIR, DATA_FILE, DIGITAL_SLOTS, OUTPUT_DIR, SLOTS
from ..models import SystemConfig
from ..repositories import CardDatabase
from ..services.card_service import default_cpld_for_card
from ..services.config_service import build_config_document
from ..services.cpld_programmer_service import generate_d_slot_xcf, read_cable_settings_from_xcf
from ..services.software_generator_service import SoftwareGenerator
from ..services.system_resolver import SystemResolver
from ..services.toolchain_service import TOOL_DEFINITIONS, detect_toolchain_executables
from ..services.vivado_service import write_vivado_run_wrapper
from ..theme import set_dark_mode
from ..tcl_generator import TclGenerator
from .card_editor import CardEditorDialog


class MainWindow(QMainWindow):
    def __init__(self) -> None:
        super().__init__()
        self.setWindowTitle("Project Wizard")
        self.resize(1200, 760)
        self.database = CardDatabase.load(DATA_FILE)
        self.generator = TclGenerator(self.database)
        self.software_generator = SoftwareGenerator(self.database)
        self.system_resolver = SystemResolver(self.database)
        self.current_config_path: Path | None = None
        self.is_loading_config = False
        self.slot_combos: dict[str, QComboBox] = {}
        self.cpld_combos: dict[str, QComboBox] = {}
        self.axi_fields: dict[str, QLineEdit] = {}
        self.toolchain_fields: dict[str, QLineEdit] = {}
        self.hardware_fields: dict[str, QLineEdit] = {}
        self.hardware_checkboxes: dict[str, QCheckBox] = {}
        self.software_fields: dict[str, QLineEdit] = {}
        self.software_mode_combos: dict[str, QComboBox] = {}
        self.software_preset_combos: dict[str, QComboBox] = {}
        self.driver_config_mode_combos: dict[str, QComboBox] = {}
        self.driver_config_fields: dict[tuple[str, str], QLineEdit | QPlainTextEdit | QComboBox] = {}
        self.driver_config_tabs: QTabWidget | None = None
        self.driver_config_tab_layouts: dict[str, QVBoxLayout] = {}
        self.visualization_checkboxes: dict[str, QCheckBox] = {}
        self.visualization_tabs: QTabWidget | None = None
        self.visualization_tab_layouts: dict[str, QVBoxLayout] = {}
        self.software_preview: QPlainTextEdit | None = None
        self.software_status: QPlainTextEdit | None = None
        self.toolchain_status: QPlainTextEdit | None = None
        self.platform_cpld_group: QGroupBox | None = None
        self.platform_cpld_type_combo: QComboBox | None = None
        self.cpld_programmer_fields: dict[str, QLineEdit] = {}
        self.cpld_status: QTextEdit | None = None
        self.cpld_process: QProcess | None = None
        self.vivado_process: QProcess | None = None
        self.cpld_log_path: Path | None = None
        self.cpld_xcf_path: Path = OUTPUT_DIR / "project_wizard_slot_cplds.xcf"
        self.cpld_xcf_current = False
        self.write_cpld_button: QPushButton | None = None
        self.program_cpld_button: QPushButton | None = None
        self.import_cable_button: QPushButton | None = None
        self.tcl_export_checkbox: QCheckBox | None = None
        self.tcl_run_vivado_checkbox: QCheckBox | None = None
        self.tcl_workflow_button: QPushButton | None = None
        self.vivado_status: QPlainTextEdit | None = None
        self.detail_combos: dict[tuple[str, str], QComboBox] = {}
        self.detail_trigger_edits: dict[tuple[str, str], QLineEdit] = {}
        self.detail_source_edits: dict[tuple[str, str], QLineEdit] = {}
        self.detail_options: dict[str, dict[str, str]] = {}
        self.software_dependent_views_dirty = False
        self.dark_mode_action: QAction | None = None

        self.stack = QStackedWidget()
        self.tree = self._build_navigation()
        self.stack.addWidget(self._build_toolchain_page())
        self.stack.addWidget(self._build_platform_page())
        self.stack.addWidget(self._build_hardware_general_page())
        self.stack.addWidget(self._build_configuration_page())
        self.stack.addWidget(self._build_slot_cpld_page())
        self.stack.addWidget(self._build_axi_interconnect_page())
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
        self.refresh_platform_revisions()
        for slot in DIGITAL_SLOTS:
            self.prefill_cpld_for_slot(slot)
        self.reset_toolchain_config()
        self.reset_hardware_config()
        self.reset_software_config()
        self.refresh_software_preset_options()
        self.refresh_data_visualization_options()
        self.reset_axi_config()
        self.rebuild_details()
        self.refresh_tcl_preview()

    def _build_menu(self) -> None:
        file_menu = self.menuBar().addMenu("File")

        new_config_action = QAction("New config", self)
        new_config_action.triggered.connect(self.new_config)
        file_menu.addAction(new_config_action)

        open_config_action = QAction("Open config", self)
        open_config_action.triggered.connect(self.open_config)
        file_menu.addAction(open_config_action)

        save_config_action = QAction("Save config", self)
        save_config_action.triggered.connect(self.save_config)
        file_menu.addAction(save_config_action)

        save_config_as_action = QAction("Save config as", self)
        save_config_as_action.triggered.connect(self.save_config_as)
        file_menu.addAction(save_config_as_action)

        file_menu.addSeparator()
        quit_action = QAction("Quit", self)
        quit_action.triggered.connect(self.close)
        file_menu.addAction(quit_action)

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

        slot_cplds_action = QAction("Slot CPLDs", self)
        slot_cplds_action.triggered.connect(self.show_slot_cplds)
        view_menu.addAction(slot_cplds_action)

        axi_action = QAction("AXI interconnect", self)
        axi_action.triggered.connect(self.show_axi_interconnect)
        view_menu.addAction(axi_action)

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

        refresh_tcl_action = QAction("Refresh TCL preview", self)
        refresh_tcl_action.triggered.connect(self.refresh_tcl_preview)
        view_menu.addAction(refresh_tcl_action)

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

    def set_dark_mode_enabled(self, enabled: bool) -> None:
        set_dark_mode(QApplication.instance(), enabled)
        if self.dark_mode_action is not None:
            self.dark_mode_action.blockSignals(True)
            self.dark_mode_action.setChecked(enabled)
            self.dark_mode_action.blockSignals(False)

    def _build_navigation(self) -> QTreeWidget:
        tree = QTreeWidget()
        tree.setHeaderHidden(True)
        toolchain = QTreeWidgetItem(["Toolchain"])
        platform = QTreeWidgetItem(["Platform"])
        config = QTreeWidgetItem(["Hardware configuration"])
        hardware_general = QTreeWidgetItem(["General"])
        axi_interconnect = QTreeWidgetItem(["AXI interconnect"])
        adapter_cards = QTreeWidgetItem(["Adapter cards"])
        slot_cplds = QTreeWidgetItem(["Slot CPLDs"])
        config.addChild(hardware_general)
        config.addChild(axi_interconnect)
        config.addChild(adapter_cards)
        config.addChild(slot_cplds)
        software_config = QTreeWidgetItem(["Software configuration"])
        software_general = QTreeWidgetItem(["General"])
        ip_driver_setup = QTreeWidgetItem(["IP core driver setup"])
        advanced_driver_config = QTreeWidgetItem(["Advanced driver configuration"])
        data_visualization = QTreeWidgetItem(["Data visualization"])
        software_config.addChild(software_general)
        software_config.addChild(ip_driver_setup)
        software_config.addChild(advanced_driver_config)
        software_config.addChild(data_visualization)
        tree.addTopLevelItem(toolchain)
        tree.addTopLevelItem(platform)
        tree.addTopLevelItem(config)
        tree.addTopLevelItem(software_config)
        config.setExpanded(True)
        software_config.setExpanded(True)
        tree.setCurrentItem(toolchain)
        tree.currentItemChanged.connect(self._navigation_changed)
        return tree

    def _navigation_changed(self, current: QTreeWidgetItem | None) -> None:
        if not current:
            return
        if current.text(0) in {"Hardware configuration", "Software configuration"}:
            first_child = current.child(0)
            if first_child is not None:
                QTimer.singleShot(0, lambda item=first_child: self.tree.setCurrentItem(item))
                return
        page_by_name = {
            "Toolchain": 0,
            "Platform": 1,
            "Hardware configuration": 2,
            "General": 2 if current.parent() and current.parent().text(0) == "Hardware configuration" else 6,
            "Adapter cards": 3,
            "Slot CPLDs": 4,
            "AXI interconnect": 5,
            "Software configuration": 6,
            "IP core driver setup": 7,
            "Advanced driver configuration": 8,
            "Data visualization": 9,
        }
        self.stack.setCurrentIndex(page_by_name.get(current.text(0), 0))

    def _build_toolchain_page(self) -> QWidget:
        page = QWidget()
        layout = QVBoxLayout(page)

        title = QLabel("Toolchain")
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title.setFont(title_font)
        layout.addWidget(title)

        vivado_group = QGroupBox("Vivado")
        vivado_form = QFormLayout(vivado_group)
        vivado_form.addRow("Executable", self._path_picker("vivado_executable", file_mode=True))
        layout.addWidget(vivado_group)

        lattice_group = QGroupBox("Lattice CPLD")
        lattice_form = QFormLayout(lattice_group)
        lattice_form.addRow("Programmer executable", self._path_picker("lattice_programmer_executable", file_mode=True))
        lattice_hint = QLabel("Use pgrcmd.exe for command-line programming, not programmer.exe, which opens the GUI.")
        lattice_hint.setWordWrap(True)
        lattice_form.addRow("", lattice_hint)
        lattice_form.addRow("CPLD repository", self._path_picker("cpld_repository", file_mode=False))
        layout.addWidget(lattice_group)

        vitis_group = QGroupBox("Vitis")
        vitis_form = QFormLayout(vitis_group)
        vitis_form.addRow("Executable", self._path_picker("vitis_executable", file_mode=True))
        layout.addWidget(vitis_group)

        buttons = QHBoxLayout()
        detect_button = QPushButton("Detect tools")
        detect_button.setMinimumSize(180, 36)
        detect_button.clicked.connect(self.detect_toolchain_paths)
        buttons.addStretch(1)
        buttons.addWidget(detect_button)
        buttons.addStretch(1)
        layout.addLayout(buttons)

        self.toolchain_status = QPlainTextEdit()
        self.toolchain_status.setReadOnly(True)
        self.toolchain_status.setFixedHeight(120)
        layout.addWidget(self.toolchain_status)

        layout.addStretch(1)
        return page

    def _path_picker(self, key: str, file_mode: bool) -> QWidget:
        container = QWidget()
        layout = QHBoxLayout(container)
        layout.setContentsMargins(0, 0, 0, 0)
        field = QLineEdit()
        field.textChanged.connect(self.refresh_tcl_preview)
        if key in {"lattice_programmer_executable", "cpld_repository"}:
            field.textChanged.connect(self.invalidate_cpld_project_file)
        button = QPushButton("Browse...")
        button.clicked.connect(lambda: self.browse_toolchain_path(key, file_mode))
        self.toolchain_fields[key] = field
        layout.addWidget(field, 1)
        layout.addWidget(button)
        return container

    def browse_toolchain_path(self, key: str, file_mode: bool) -> None:
        field = self.toolchain_fields[key]
        start_path = field.text().strip() or str(APP_DIR)
        if file_mode:
            path_text, _ = QFileDialog.getOpenFileName(self, "Select executable", start_path, "Executables (*.exe);;All files (*)")
        else:
            path_text = QFileDialog.getExistingDirectory(self, "Select folder", start_path)
        if path_text:
            field.setText(path_text)

    def _build_hardware_general_page(self) -> QWidget:
        page = QWidget()
        layout = QVBoxLayout(page)

        title = QLabel("General")
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title.setFont(title_font)
        layout.addWidget(title)

        vivado_group = QGroupBox("Vivado project")
        vivado_form = QFormLayout(vivado_group)
        vivado_form.addRow("Project file", self._hardware_path_picker("vivado_project_file", file_mode=True))
        block_design_name = QLineEdit()
        self.hardware_fields["block_design_name"] = block_design_name
        vivado_form.addRow("Block design name", block_design_name)
        validate_checkbox = QCheckBox("Validate block design after applying TCL")
        save_checkbox = QCheckBox("Save block design after applying TCL")
        open_gui_checkbox = QCheckBox("Open Vivado GUI after applying TCL")
        disable_checkpoints_checkbox = QCheckBox("Disable BD/IP synthesis checkpoints")
        self.hardware_checkboxes["validate_block_design"] = validate_checkbox
        self.hardware_checkboxes["save_block_design"] = save_checkbox
        self.hardware_checkboxes["open_vivado_gui"] = open_gui_checkbox
        self.hardware_checkboxes["disable_bd_synth_checkpoints"] = disable_checkpoints_checkbox
        disable_checkpoints_checkbox.stateChanged.connect(lambda _state: self.guarded_refresh_tcl_preview())
        vivado_form.addRow("", validate_checkbox)
        vivado_form.addRow("", save_checkbox)
        vivado_form.addRow("", open_gui_checkbox)
        vivado_form.addRow("", disable_checkpoints_checkbox)
        hint = QLabel(
            "For manual inspection, leave saving disabled. Vivado can apply the generated TCL and validate the "
            "block design. Enable the GUI option to inspect unsaved changes before deciding whether to save. "
            "Disable synthesis checkpoints for slower but cleaner full builds when Vivado has IP checkpoint issues."
        )
        hint.setWordWrap(True)
        vivado_form.addRow("", hint)
        layout.addWidget(vivado_group)
        layout.addStretch(1)
        return page

    def _hardware_path_picker(self, key: str, file_mode: bool) -> QWidget:
        container = QWidget()
        layout = QHBoxLayout(container)
        layout.setContentsMargins(0, 0, 0, 0)
        field = QLineEdit()
        self.hardware_fields[key] = field
        button = QPushButton("Browse...")
        button.clicked.connect(lambda: self.browse_hardware_path(key, file_mode))
        layout.addWidget(field, 1)
        layout.addWidget(button)
        return container

    def browse_hardware_path(self, key: str, file_mode: bool) -> None:
        field = self.hardware_fields[key]
        start_path = field.text().strip() or str(APP_DIR.parent)
        if file_mode:
            path_text, _ = QFileDialog.getOpenFileName(
                self,
                "Select Vivado project",
                start_path,
                "Vivado project (*.xpr);;All files (*)",
            )
        else:
            path_text = QFileDialog.getExistingDirectory(self, "Select folder", start_path)
        if path_text:
            field.setText(path_text)

    def detect_toolchain_paths(self) -> None:
        results = {result.key: result for result in detect_toolchain_executables()}
        messages = []
        for key, definition in TOOL_DEFINITIONS.items():
            label = str(definition["label"])
            result = results.get(key)
            if result:
                field = self.toolchain_fields.get(key)
                if field and not field.text().strip():
                    field.setText(result.path)
                    messages.append(f"{label}: found via {result.source}: {result.path}")
                elif field:
                    messages.append(f"{label}: found via {result.source}, keeping existing value: {field.text().strip()}")
                else:
                    messages.append(f"{label}: found via {result.source}: {result.path}")
            else:
                messages.append(f"{label}: not found")
        messages.append("CPLD repository: not auto-detected")
        if self.toolchain_status:
            self.toolchain_status.setPlainText("\n".join(messages))

    def _build_placeholder_page(self, title_text: str) -> QWidget:
        page = QWidget()
        layout = QVBoxLayout(page)
        title = QLabel(title_text)
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title.setFont(title_font)
        layout.addWidget(title)
        layout.addStretch(1)
        return page

    def _build_platform_page(self) -> QWidget:
        page = QWidget()
        layout = QVBoxLayout(page)

        title = QLabel("Platform")
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title.setFont(title_font)
        layout.addWidget(title)

        group = QGroupBox("Target hardware")
        form = QFormLayout(group)
        self.platform_combo = QComboBox()
        for platform in self.database.platforms:
            self.platform_combo.addItem(platform.get("name", platform.get("id", "Unnamed platform")), platform.get("id"))
        self.platform_combo.currentIndexChanged.connect(self.platform_changed)
        form.addRow("Platform", self.platform_combo)
        self.platform_revision_combo = QComboBox()
        self.platform_revision_combo.currentIndexChanged.connect(self.platform_revision_changed)
        form.addRow("Revision", self.platform_revision_combo)
        layout.addWidget(group)

        self.platform_cpld_group = QGroupBox("CPLD type")
        cpld_layout = QVBoxLayout(self.platform_cpld_group)
        self.platform_cpld_type_combo = QComboBox()
        self.platform_cpld_type_combo.addItem("LA4128V", "la4128v")
        self.platform_cpld_type_combo.addItem("LC4256V", "lc4256v")
        self.platform_cpld_type_combo.currentIndexChanged.connect(self.platform_cpld_type_changed)
        cpld_form = QFormLayout()
        cpld_form.addRow("Rev04 CPLD type", self.platform_cpld_type_combo)
        cpld_layout.addLayout(cpld_form)
        cpld_hint = QLabel(
            "UltraZohm Rev04 can use different D-slot CPLDs. Select by system serial number:\n"
            "- LA4128V: old revisions and Rev04 systems from UZ2021-002-001-200-0001 "
            "to UZ2021-001-001-004-0004\n"
            "- LC4256V: Rev04 systems from UZ2022-001-001-401-0007 "
            "up to UZ2024-001-001-0401-0031"
        )
        cpld_hint.setWordWrap(True)
        cpld_hint.setMinimumHeight(92)
        cpld_layout.addWidget(cpld_hint)
        layout.addWidget(self.platform_cpld_group)
        layout.addStretch(1)
        return page

    def _build_software_general_page(self) -> QWidget:
        page = QWidget()
        layout = QVBoxLayout(page)

        title = QLabel("General")
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title.setFont(title_font)
        layout.addWidget(title)

        source_group = QGroupBox("Software project")
        source_form = QFormLayout(source_group)
        source_form.addRow("Source folder", self._software_path_picker("source_dir", file_mode=False))
        source_hint = QLabel(
            "Select the folder that contains globalData.h. For the current Baremetal framework this is "
            "usually vitis/software/Baremetal/src."
        )
        source_hint.setWordWrap(True)
        source_form.addRow("", source_hint)
        layout.addWidget(source_group)

        marker_group = QGroupBox("Marker-based edits")
        marker_layout = QVBoxLayout(marker_group)
        marker_hint = QLabel(
            "The wizard keeps one permanent init header/source pair per adapter slot and rewrites only "
            "Project Wizard marker blocks. Setting a slot to No software driver clears the slot-owned "
            "markers and removes its generated integration from shared marker blocks."
        )
        marker_hint.setWordWrap(True)
        marker_layout.addWidget(marker_hint)
        layout.addWidget(marker_group)

        layout.addStretch(1)
        return page

    def _build_software_driver_page(self) -> QWidget:
        page = QWidget()
        layout = QVBoxLayout(page)

        title = QLabel("IP Core Driver Setup")
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title.setFont(title_font)
        layout.addWidget(title)

        slot_group = QGroupBox("Slot software integration")
        slot_grid = QGridLayout(slot_group)
        header_font = QFont()
        header_font.setBold(True)
        for column, header in enumerate(["Slot", "Mode", "Preset"]):
            label = QLabel(header)
            label.setFont(header_font)
            slot_grid.addWidget(label, 0, column)
        for row, slot in enumerate(SLOTS, start=1):
            slot_grid.addWidget(QLabel(slot), row, 0)
            combo = QComboBox()
            combo.addItem("Follow hardware selection", "follow_hardware")
            combo.addItem("No software driver", "no_driver")
            combo.currentIndexChanged.connect(self.software_driver_selection_changed)
            self.software_mode_combos[slot] = combo
            slot_grid.addWidget(combo, row, 1)
            preset_combo = QComboBox()
            preset_combo.currentIndexChanged.connect(self.software_driver_selection_changed)
            self.software_preset_combos[slot] = preset_combo
            slot_grid.addWidget(preset_combo, row, 2)
        slot_grid.setColumnStretch(1, 1)
        slot_grid.setColumnStretch(2, 1)
        layout.addWidget(slot_group)

        buttons = QHBoxLayout()
        generate_button = QPushButton("Generate software files")
        generate_button.clicked.connect(self.generate_software_files)
        buttons.addStretch(1)
        buttons.addWidget(generate_button)
        layout.addLayout(buttons)

        self.software_preview = QPlainTextEdit()
        self.software_preview.setReadOnly(True)
        self.software_preview.setLineWrapMode(QPlainTextEdit.LineWrapMode.NoWrap)
        layout.addWidget(self.software_preview, 2)

        self.software_status = QPlainTextEdit()
        self.software_status.setReadOnly(True)
        self.software_status.setFixedHeight(120)
        layout.addWidget(self.software_status)
        return page

    def _build_advanced_driver_config_page(self) -> QWidget:
        page = QWidget()
        layout = QVBoxLayout(page)

        title = QLabel("Advanced Driver Configuration")
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title.setFont(title_font)
        layout.addWidget(title)

        advanced_hint = QLabel("Use Default for preset-generated config structs, or Custom to edit instance-specific config fields.")
        advanced_hint.setWordWrap(True)
        layout.addWidget(advanced_hint)
        self.driver_config_tabs = QTabWidget()
        self.driver_config_tab_layouts = {}
        for slot in SLOTS:
            scroll = QScrollArea()
            scroll.setWidgetResizable(True)
            content = QWidget()
            slot_layout = QVBoxLayout(content)
            slot_layout.addStretch(1)
            self.driver_config_tab_layouts[slot] = slot_layout
            scroll.setWidget(content)
            self.driver_config_tabs.addTab(scroll, slot)
        layout.addWidget(self.driver_config_tabs, 1)

        buttons = QHBoxLayout()
        generate_button = QPushButton("Generate software driver files")
        generate_button.clicked.connect(self.generate_software_files)
        buttons.addStretch(1)
        buttons.addWidget(generate_button)
        layout.addLayout(buttons)
        return page

    def _build_data_visualization_page(self) -> QWidget:
        page = QWidget()
        layout = QVBoxLayout(page)

        title = QLabel("Data Visualization")
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title.setFont(title_font)
        layout.addWidget(title)

        hint = QLabel(
            "Select generated float signals that should be registered as Javascope observable signals. "
            "The wizard writes the enum entries in javascope.h and the pointer assignments in javascope.c."
        )
        hint.setWordWrap(True)
        layout.addWidget(hint)

        self.visualization_tabs = QTabWidget()
        self.visualization_tab_layouts = {}
        for slot in SLOTS:
            scroll = QScrollArea()
            scroll.setWidgetResizable(True)
            content = QWidget()
            slot_layout = QVBoxLayout(content)
            slot_layout.addStretch(1)
            self.visualization_tab_layouts[slot] = slot_layout
            scroll.setWidget(content)
            self.visualization_tabs.addTab(scroll, slot)
        layout.addWidget(self.visualization_tabs, 1)

        action_group = QGroupBox("Software generation")
        action_layout = QVBoxLayout(action_group)
        action_hint = QLabel("The selected visualization signals are written together with the software driver integration.")
        action_hint.setWordWrap(True)
        action_layout.addWidget(action_hint)
        buttons = QHBoxLayout()
        generate_button = QPushButton("Generate software driver files")
        generate_button.clicked.connect(self.generate_software_files)
        buttons.addStretch(1)
        buttons.addWidget(generate_button)
        action_layout.addLayout(buttons)
        layout.addWidget(action_group)

        return page

    def _software_path_picker(self, key: str, file_mode: bool) -> QWidget:
        container = QWidget()
        layout = QHBoxLayout(container)
        layout.setContentsMargins(0, 0, 0, 0)
        field = QLineEdit()
        field.textChanged.connect(self.refresh_software_preview)
        button = QPushButton("Browse...")
        button.clicked.connect(lambda: self.browse_software_path(key, file_mode))
        self.software_fields[key] = field
        layout.addWidget(field, 1)
        layout.addWidget(button)
        return container

    def browse_software_path(self, key: str, file_mode: bool) -> None:
        field = self.software_fields[key]
        start_path = field.text().strip() or str(APP_DIR.parent)
        if file_mode:
            path_text, _ = QFileDialog.getOpenFileName(self, "Select file", start_path, "All files (*)")
        else:
            path_text = QFileDialog.getExistingDirectory(self, "Select folder", start_path)
        if path_text:
            field.setText(path_text)

    def _build_configuration_page(self) -> QWidget:
        page = QWidget()
        outer = QVBoxLayout(page)

        title = QLabel("Adapter Cards")
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title.setFont(title_font)
        outer.addWidget(title)

        content = QHBoxLayout()
        slot_group = self._build_slot_group()
        details_group = self._build_details_group()
        slot_group.setFixedHeight(420)
        details_group.setFixedHeight(420)
        content.addWidget(slot_group, 2)
        content.addWidget(details_group, 3)
        outer.addLayout(content)

        buttons = QHBoxLayout()
        preview_button = QPushButton("Refresh TCL Preview")
        preview_button.clicked.connect(self.refresh_tcl_preview)
        export_checkbox = QCheckBox("Export TCL")
        export_checkbox.setChecked(True)
        run_vivado_checkbox = QCheckBox("Run TCL in Vivado")
        workflow_button = QPushButton("Execute TCL workflow")
        workflow_button.clicked.connect(self.execute_tcl_workflow)
        self.tcl_export_checkbox = export_checkbox
        self.tcl_run_vivado_checkbox = run_vivado_checkbox
        self.tcl_workflow_button = workflow_button
        buttons.addStretch(1)
        buttons.addWidget(preview_button)
        buttons.addWidget(export_checkbox)
        buttons.addWidget(run_vivado_checkbox)
        buttons.addWidget(workflow_button)
        outer.addLayout(buttons)

        self.vivado_status = QPlainTextEdit()
        self.vivado_status.setReadOnly(True)
        self.vivado_status.setFixedHeight(110)
        outer.addWidget(self.vivado_status)

        self.tcl_preview = QPlainTextEdit()
        self.tcl_preview.setReadOnly(True)
        self.tcl_preview.setLineWrapMode(QPlainTextEdit.LineWrapMode.NoWrap)
        outer.addWidget(self.tcl_preview, 2)
        return page

    def _build_slot_group(self) -> QGroupBox:
        group = QGroupBox("Adapter card slots")
        grid = QGridLayout(group)
        grid.setRowStretch(len(SLOTS), 1)
        for row, slot in enumerate(SLOTS):
            label = QLabel(slot)
            label.setAlignment(Qt.AlignmentFlag.AlignRight | Qt.AlignmentFlag.AlignVCenter)
            combo = QComboBox()
            combo.setFixedHeight(24)
            self.slot_combos[slot] = combo
            self._fill_slot_combo(slot, combo)
            combo.currentIndexChanged.connect(lambda _index, selected_slot=slot: self.adapter_card_changed(selected_slot))
            grid.addWidget(label, row, 0)
            grid.addWidget(combo, row, 1)
        return group

    def _build_slot_cpld_page(self) -> QWidget:
        page = QWidget()
        page_layout = QVBoxLayout(page)
        scroll = QScrollArea()
        scroll.setWidgetResizable(True)
        content = QWidget()
        outer = QVBoxLayout(content)

        title = QLabel("Slot CPLDs")
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title.setFont(title_font)
        outer.addWidget(title)

        group = QGroupBox("Digital slot CPLD programs")
        form = QFormLayout(group)
        for slot in DIGITAL_SLOTS:
            combo = QComboBox()
            self.cpld_combos[slot] = combo
            self._fill_cpld_combo(combo)
            combo.currentIndexChanged.connect(self.refresh_tcl_preview)
            combo.currentIndexChanged.connect(self.invalidate_cpld_project_file)
            form.addRow(slot, combo)
        outer.addWidget(group)

        cable_group = QGroupBox("Lattice cable settings")
        cable_form = QFormLayout(cable_group)
        cable_defaults = {
            "cable_name": "USB2",
            "port_address": "FTUSB-1",
            "usb_id": "UltraZohm B Location",
            "tck_delay": "3",
        }
        cable_labels = {
            "cable_name": "Cable name",
            "port_address": "Port address",
            "usb_id": "USB ID",
            "tck_delay": "Clock divider",
        }
        for key, default_value in cable_defaults.items():
            edit = QLineEdit(default_value)
            edit.textChanged.connect(self.invalidate_cpld_project_file)
            self.cpld_programmer_fields[key] = edit
            cable_form.addRow(cable_labels[key], edit)
        recovery_group = QGroupBox("Cable setup recovery")
        recovery_layout = QVBoxLayout(recovery_group)
        recovery_hint = QLabel(
            "This optional path is only needed when the default cable settings do not work. "
            "Open Diamond Programmer once, select UltraZohm B Location, save an XCF, "
            "and copy or import CableName and PortAdd from that file."
        )
        recovery_hint.setWordWrap(True)
        recovery_hint.setMinimumHeight(44)
        recovery_hint.setContentsMargins(0, 4, 0, 4)
        recovery_layout.addWidget(recovery_hint)
        import_enable = QCheckBox("I want to import cable settings from an existing Diamond Programmer XCF")
        import_button = QPushButton("Import cable settings from XCF")
        import_button.setEnabled(False)
        import_enable.toggled.connect(import_button.setEnabled)
        import_button.clicked.connect(self.import_cable_settings_from_xcf)
        self.import_cable_button = import_button
        recovery_layout.addWidget(import_enable)
        recovery_layout.addWidget(import_button, alignment=Qt.AlignmentFlag.AlignRight)
        cable_form.addRow("", recovery_group)
        outer.addWidget(cable_group)

        buttons = QHBoxLayout()
        lattice_button = QPushButton("Write Lattice Diamond Programmer project file")
        lattice_button.clicked.connect(self.write_lattice_diamond_project_file)
        program_button = QPushButton("Programm CPLDs via CLI")
        program_button.clicked.connect(self.program_cplds_via_cli)
        self.write_cpld_button = lattice_button
        self.program_cpld_button = program_button
        program_button.setEnabled(False)
        buttons.addStretch(1)
        buttons.addWidget(lattice_button)
        buttons.addWidget(program_button)
        buttons.addStretch(1)
        outer.addLayout(buttons)

        self.cpld_status = QTextEdit()
        self.cpld_status.setReadOnly(True)
        self.cpld_status.setLineWrapMode(QTextEdit.LineWrapMode.NoWrap)
        self.cpld_status.setFixedHeight(180)
        outer.addWidget(self.cpld_status)
        outer.addStretch(1)
        scroll.setWidget(content)
        page_layout.addWidget(scroll)
        return page

    def _build_axi_interconnect_page(self) -> QWidget:
        page = QWidget()
        outer = QVBoxLayout(page)

        title = QLabel("AXI Interconnect")
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title.setFont(title_font)
        outer.addWidget(title)

        defaults = self.database.axi_interconnect

        def add_attachment_group(title_text: str, prefix: str) -> None:
            attachment_group = QGroupBox(title_text)
            attachment_form = QFormLayout(attachment_group)
            attachment_field_labels = [
                (f"{prefix}_upstream_smartconnect", "Upstream SmartConnect"),
                (f"{prefix}_clock_pin", "AXI clock pin"),
                (f"{prefix}_resetn_pin", "AXI resetn pin"),
                (f"{prefix}_address_space", "Address space"),
            ]
            for key, label in attachment_field_labels:
                edit = QLineEdit(str(defaults.get(key, "")))
                edit.textChanged.connect(self.refresh_tcl_preview)
                self.axi_fields[key] = edit
                attachment_form.addRow(label, edit)
            outer.addWidget(attachment_group)

        add_attachment_group("A-slot project-level AXI attachment point", "a")
        add_attachment_group("D-slot project-level AXI attachment point", "d")

        analog_group = QGroupBox("A-slot analog project-level wiring")
        analog_form = QFormLayout(analog_group)
        analog_help = {
            "analog_raw_value_target_template": (
                "Connects each generated A-slot RAW_Value vector to a project-level sink. "
                "Use {slot} as placeholder, for example uz_system/ADC_{slot}. "
                "For LTC2311 this vector must match DATA_WIDTH * CHANNELS_PER_MASTER * SPI_MASTER."
            ),
            "analog_axi2tcm_trigger_source": (
                "Normally this is one generated A-slot RAW_Valid pin. If the configured pin is not generated "
                "by the selected A-slot cards, the wizard falls back to the first generated RAW_Valid. "
                "For LTC2311 this is driven by RAW_VALID; for MAX11331 it is driven by meas_done. "
                "If no RAW_Valid exists, it uses the first conversion trigger source instead."
            ),
            "analog_axi2tcm_trigger_target": (
                "Project-level input that starts the AXI-to-TCM transfer in uz_system. "
                "The wizard connects either the selected RAW_Valid source or, if no A-slot ADC exists, "
                "the first configured conversion trigger source."
            ),
            "analog_conversion_trigger_sources": (
                "Semicolon-separated list of project-level trigger sources. The wizard connects them to the "
                "shared TRIGGER_CNV pin when A-slot ADC cards are present. The first entry is also used as "
                "AXI2TCM fallback when no RAW_Valid source exists."
            ),
            "analog_conversion_trigger_target": (
                "Shared trigger pin at the uz_analog_adapter boundary. A-slot ADC cards use this as their "
                "conversion trigger input."
            ),
        }
        analog_field_labels = [
            ("analog_raw_value_target_template", "RAW value target template"),
            ("analog_axi2tcm_trigger_source", "AXI2TCM trigger source"),
            ("analog_axi2tcm_trigger_target", "AXI2TCM trigger target"),
            ("analog_conversion_trigger_sources", "Conversion trigger sources"),
            ("analog_conversion_trigger_target", "Conversion trigger target"),
        ]
        for key, label in analog_field_labels:
            edit = QLineEdit(str(defaults.get(key, "")))
            edit.textChanged.connect(self.refresh_tcl_preview)
            self.axi_fields[key] = edit
            row = QWidget()
            row_layout = QHBoxLayout(row)
            row_layout.setContentsMargins(0, 0, 0, 0)
            help_button = QPushButton("?")
            help_button.setFixedWidth(28)
            help_button.clicked.connect(
                lambda _checked=False, title=label, text=analog_help[key]: QMessageBox.information(
                    self,
                    title,
                    text,
                )
            )
            row_layout.addWidget(edit, 1)
            row_layout.addWidget(help_button)
            analog_form.addRow(label, row)
        analog_hint = QLabel(
            "These fields make the historically grown A-slot project wiring explicit. "
            "Use semicolons for multiple conversion trigger sources."
        )
        analog_hint.setWordWrap(True)
        analog_form.addRow("", analog_hint)
        outer.addWidget(analog_group)

        local_group = QGroupBox("Local per adapter card slot AXI smartconnects")
        local_form = QFormLayout(local_group)
        local_field_labels = [
            ("local_smartconnect_vlnv", "Local SmartConnect VLNV"),
            ("local_smartconnect_name", "Local SmartConnect name"),
        ]
        for key, label in local_field_labels:
            edit = QLineEdit(str(defaults.get(key, "")))
            edit.textChanged.connect(self.refresh_tcl_preview)
            self.axi_fields[key] = edit
            local_form.addRow(label, edit)
        outer.addWidget(local_group)
        outer.addStretch(1)
        return page

    def _build_details_group(self) -> QGroupBox:
        group = QGroupBox("Selected card details")
        layout = QVBoxLayout(group)
        self.details_tabs = QTabWidget()
        self.details_tabs.setFixedHeight(380)
        self.slot_detail_pages: dict[str, QWidget] = {}
        self.slot_detail_layouts: dict[str, QVBoxLayout] = {}
        for slot in SLOTS:
            page = QWidget()
            page_layout = QVBoxLayout(page)
            page_layout.setContentsMargins(8, 8, 8, 8)
            page_layout.addStretch(1)
            scroll = QScrollArea()
            scroll.setWidgetResizable(True)
            scroll.setWidget(page)
            self.slot_detail_pages[slot] = page
            self.slot_detail_layouts[slot] = page_layout
            self.details_tabs.addTab(scroll, slot)
        layout.addWidget(self.details_tabs)
        for combo in self.slot_combos.values():
            combo.currentIndexChanged.connect(self.rebuild_details)
        return group

    def _build_database_page(self) -> QWidget:
        page = QWidget()
        layout = QVBoxLayout(page)
        title = QLabel("Adapter Card Database")
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title.setFont(title_font)
        layout.addWidget(title)

        add_button = QPushButton("Add Card")
        add_button.clicked.connect(self.add_card)
        layout.addWidget(add_button, alignment=Qt.AlignmentFlag.AlignRight)

        self.card_table = QTableWidget()
        self.card_table.setColumnCount(6)
        self.card_table.setHorizontalHeaderLabels(["ID", "Name", "Family", "Slots", "Driver", "Edit"])
        layout.addWidget(self.card_table)
        self.refresh_card_table()
        return page

    def _fill_slot_combo(self, slot: str, combo: QComboBox, selected_id: str = "empty") -> None:
        if slot.startswith("A") and selected_id == "empty":
            selected_id = "no_adapter_board"
        combo.blockSignals(True)
        combo.clear()
        for card in self.database.cards_for_slot(slot):
            combo.addItem(card.get("name", card.get("id", "Unnamed card")), card.get("id"))
        index = combo.findData(selected_id)
        combo.setCurrentIndex(index if index >= 0 else 0)
        combo.blockSignals(False)

    def _fill_cpld_combo(self, combo: QComboBox, selected_id: str = "none") -> None:
        combo.blockSignals(True)
        combo.clear()
        for program in self.database.cpld_programs:
            combo.addItem(program.get("name", program.get("id", "Unnamed program")), program.get("id"))
        index = combo.findData(selected_id)
        combo.setCurrentIndex(index if index >= 0 else 0)
        combo.blockSignals(False)

    def refresh_all_card_views(self) -> None:
        assignments = self.assignments()
        for slot, combo in self.slot_combos.items():
            self._fill_slot_combo(slot, combo, assignments.get(slot, "empty"))
        for slot in DIGITAL_SLOTS:
            self.prefill_cpld_for_slot(slot)
        self.refresh_card_table()
        self.guarded_rebuild_details()
        self.guarded_refresh_tcl_preview()

    def guarded_refresh_tcl_preview(self) -> None:
        if not self.is_loading_config:
            self.refresh_tcl_preview()

    def guarded_refresh_software_preview(self) -> None:
        if not self.is_loading_config:
            self.refresh_software_preview()

    def guarded_refresh_data_visualization_options(self, values: dict[str, str] | None = None) -> None:
        if not self.is_loading_config:
            self.refresh_data_visualization_options(values)

    def guarded_rebuild_details(self) -> None:
        if not self.is_loading_config:
            self.rebuild_details()

    def assignments(self) -> dict[str, str]:
        return {slot: combo.currentData() or "empty" for slot, combo in self.slot_combos.items()}

    def cpld_assignments(self) -> dict[str, str]:
        return {slot: combo.currentData() or "none" for slot, combo in self.cpld_combos.items()}

    def cpld_programmer_config(self, include_variant: bool = False) -> dict[str, str]:
        config = {key: field.text().strip() for key, field in self.cpld_programmer_fields.items()}
        if include_variant:
            config["cpld_variant"] = self.selected_cpld_variant()
        return config

    def platform_cpld_config(self) -> dict[str, str]:
        return {"rev04_cpld_type": self.rev04_cpld_type()}

    def axi_config(self) -> dict[str, str]:
        return {key: field.text().strip() for key, field in self.axi_fields.items()}

    def toolchain_config(self) -> dict[str, str]:
        return {key: field.text().strip() for key, field in self.toolchain_fields.items()}

    def hardware_config(self) -> dict[str, str]:
        config = {key: field.text().strip() for key, field in self.hardware_fields.items()}
        for key, checkbox in self.hardware_checkboxes.items():
            config[key] = "true" if checkbox.isChecked() else "false"
        return config

    def software_config(self) -> dict[str, str]:
        config = {key: field.text().strip() for key, field in self.software_fields.items()}
        for slot, combo in self.software_mode_combos.items():
            config[f"{slot}_mode"] = combo.currentData() or "follow_hardware"
        for slot, combo in self.software_preset_combos.items():
            config[f"{slot}_preset"] = combo.currentData() or "default"
        for instance_id, combo in self.driver_config_mode_combos.items():
            config[f"driver_config_{instance_id}_mode"] = combo.currentData() or "default"
        for (instance_id, field_id), field in self.driver_config_fields.items():
            mode_combo = self.driver_config_mode_combos.get(instance_id)
            if mode_combo is not None and mode_combo.currentData() != "custom":
                continue
            if isinstance(field, QPlainTextEdit):
                value = field.toPlainText().strip()
            elif isinstance(field, QComboBox):
                value = str(field.currentData() or "")
            else:
                value = field.text().strip()
            config[f"driver_config_{instance_id}_{field_id}"] = value
        for signal_id, checkbox in self.visualization_checkboxes.items():
            if checkbox.isChecked():
                config[f"visualize_{signal_id}"] = "true"
        return config

    def software_modes(self) -> dict[str, str]:
        return {slot: combo.currentData() or "follow_hardware" for slot, combo in self.software_mode_combos.items()}

    def software_presets(self) -> dict[str, str]:
        return {slot: combo.currentData() or "default" for slot, combo in self.software_preset_combos.items()}

    def selected_visualization_signals(self) -> set[str]:
        return {signal_id for signal_id, checkbox in self.visualization_checkboxes.items() if checkbox.isChecked()}

    def driver_config_values(self) -> dict[str, dict[str, str]]:
        values: dict[str, dict[str, str]] = {}
        for instance_id, combo in self.driver_config_mode_combos.items():
            values.setdefault(instance_id, {})["mode"] = combo.currentData() or "default"
        for (instance_id, field_id), field in self.driver_config_fields.items():
            if isinstance(field, QPlainTextEdit):
                value = field.toPlainText().strip()
            elif isinstance(field, QComboBox):
                value = str(field.currentData() or "")
            else:
                value = field.text().strip()
            values.setdefault(instance_id, {})[field_id] = value
        return values

    def load_toolchain_config(self, values: dict[str, str]) -> None:
        for key, field in self.toolchain_fields.items():
            field.blockSignals(True)
            field.setText(values.get(key, ""))
            field.blockSignals(False)

    def reset_toolchain_config(self) -> None:
        self.load_toolchain_config({})

    def load_hardware_config(self, values: dict[str, str]) -> None:
        defaults = self.default_hardware_config()
        for key, field in self.hardware_fields.items():
            field.blockSignals(True)
            field.setText(values.get(key, defaults.get(key, "")))
            field.blockSignals(False)
        for key, checkbox in self.hardware_checkboxes.items():
            checkbox.blockSignals(True)
            checkbox.setChecked(values.get(key, defaults.get(key, "false")).lower() in {"1", "true", "yes", "on"})
            checkbox.blockSignals(False)

    def reset_hardware_config(self) -> None:
        self.load_hardware_config({})

    def default_hardware_config(self) -> dict[str, str]:
        return {
            "vivado_project_file": str(APP_DIR.parent / "vivado" / "project" / "ultrazohm.xpr"),
            "block_design_name": "zusys",
            "validate_block_design": "true",
            "save_block_design": "false",
            "open_vivado_gui": "false",
            "disable_bd_synth_checkpoints": "false",
        }

    def load_software_config(self, values: dict[str, str]) -> None:
        defaults = self.default_software_config()
        for key, field in self.software_fields.items():
            field.blockSignals(True)
            field.setText(values.get(key, defaults.get(key, "")))
            field.blockSignals(False)
        for slot, combo in self.software_mode_combos.items():
            combo.blockSignals(True)
            index = combo.findData(values.get(f"{slot}_mode", "follow_hardware"))
            combo.setCurrentIndex(index if index >= 0 else 0)
            combo.blockSignals(False)
        self.refresh_software_preset_options(values, refresh_dependent=False)
        if self.is_loading_config:
            self.software_dependent_views_dirty = True
            return
        self.refresh_advanced_driver_config_options(values)
        self.refresh_data_visualization_options(values, refresh_preview=False)
        self.guarded_refresh_software_preview()

    def reset_software_config(self) -> None:
        self.load_software_config({})

    def default_software_config(self) -> dict[str, str]:
        default_source = APP_DIR.parent / "vitis" / "software" / "Baremetal" / "src"
        defaults = {"source_dir": str(default_source)}
        defaults.update({f"{slot}_mode": "follow_hardware" for slot in SLOTS})
        defaults.update({f"{slot}_preset": "default" for slot in SLOTS})
        return defaults

    def refresh_software_preset_options(self, values: dict[str, str] | None = None, refresh_dependent: bool = True) -> None:
        values = values or self.software_config()
        assignments = self.assignments()
        for slot, combo in self.software_preset_combos.items():
            selected = values.get(f"{slot}_preset", combo.currentData() or "default")
            combo.blockSignals(True)
            combo.clear()
            card_id = assignments.get(slot, "empty")
            if card_id == "uz_d_temperature_ltc2983":
                combo.addItem("Default", "default")
                combo.addItem("PT100 2-wire", "pt100_2wire")
                combo.addItem("Type K thermocouple", "type_k_thermocouple")
            elif card_id == "uz_d_absolute_encoder":
                combo.addItem("Default EnDat / SSI", "default")
            elif card_id == "analog_ltc2311_16":
                combo.addItem("Default ADC LTC2311", "default")
            elif card_id == "analog_max11331":
                combo.addItem("Default ADC MAX11331", "default")
            elif card_id == "analog_dac8831":
                combo.addItem("Default DAC8831", "default")
            else:
                combo.addItem("Default", "default")
            index = combo.findData(selected)
            combo.setCurrentIndex(index if index >= 0 else 0)
            combo.blockSignals(False)
        if refresh_dependent:
            self.refresh_advanced_driver_config_options(values)
            self.refresh_data_visualization_options(values, refresh_preview=False)

    def refresh_advanced_driver_config_options(self, values: dict[str, str] | None = None) -> None:
        if self.driver_config_tabs is None:
            return
        values = values or self.software_config()
        for layout in self.driver_config_tab_layouts.values():
            for index in reversed(range(layout.count())):
                item = layout.itemAt(index)
                widget = item.widget()
                if widget is not None:
                    widget.setParent(None)
                else:
                    layout.removeItem(item)
        self.driver_config_mode_combos.clear()
        self.driver_config_fields.clear()

        instances = self.software_generator.driver_config_instances(
            self.assignments(),
            self.option_values(),
            self.software_modes(),
            self.software_presets(),
        )
        instances_by_slot: dict[str, list[Any]] = {slot: [] for slot in SLOTS}
        for instance in instances:
            instances_by_slot.setdefault(instance.slot, []).append(instance)
        for instance in instances:
            layout = self.driver_config_tab_layouts.get(instance.slot)
            if layout is None:
                continue
            group = QGroupBox(instance.label)
            group_layout = QVBoxLayout(group)
            form = QFormLayout()
            mode_combo = QComboBox()
            mode_combo.addItem("Default", "default")
            mode_combo.addItem("Custom", "custom")
            mode_value = values.get(f"driver_config_{instance.id}_mode", "default")
            mode_index = mode_combo.findData(mode_value)
            mode_combo.setCurrentIndex(mode_index if mode_index >= 0 else 0)
            self.driver_config_mode_combos[instance.id] = mode_combo
            form.addRow("Config mode", mode_combo)

            field_widgets: list[QWidget] = []
            field_rows: dict[str, tuple[QWidget, QWidget | None]] = {}
            choice_fields: dict[str, QComboBox] = {}
            for field in instance.fields:
                if mode_value == "custom":
                    stored_value = values.get(f"driver_config_{instance.id}_{field.id}", field.default)
                else:
                    stored_value = field.default
                if field.input_type == "choice":
                    widget = QComboBox()
                    options = field.options or ((field.default, field.default),)
                    for option_value, option_label in options:
                        widget.addItem(option_label, option_value)
                    option_index = widget.findData(stored_value)
                    widget.setCurrentIndex(option_index if option_index >= 0 else 0)
                    choice_fields[field.id] = widget
                elif field.multiline:
                    widget = QPlainTextEdit()
                    widget.setPlainText(stored_value)
                    widget.setFixedHeight(95)
                else:
                    widget = QLineEdit(stored_value)
                self.driver_config_fields[(instance.id, field.id)] = widget
                field_widgets.append(widget)
                if field.help_text:
                    row = QWidget()
                    row_layout = QHBoxLayout(row)
                    row_layout.setContentsMargins(0, 0, 0, 0)
                    help_button = QPushButton("?")
                    help_button.setFixedWidth(28)
                    help_button.clicked.connect(
                        lambda _checked=False, title=field.label, text=field.help_text: QMessageBox.information(
                            self,
                            title,
                            text,
                        )
                    )
                    row_layout.addWidget(widget, 1)
                    row_layout.addWidget(help_button)
                    form.addRow(field.label, row)
                    label_widget = form.labelForField(row)
                    field_rows[field.id] = (row, label_widget)
                else:
                    form.addRow(field.label, widget)
                    label_widget = form.labelForField(widget)
                    field_rows[field.id] = (widget, label_widget)
            group_layout.addLayout(form)

            def apply_visibility(
                fields: list[Any] = instance.fields,
                rows: dict[str, tuple[QWidget, QWidget | None]] = field_rows,
                choices: dict[str, QComboBox] = choice_fields,
            ) -> None:
                for field in fields:
                    visible = True
                    for controller_id, allowed_values in field.visible_when:
                        controller = choices.get(controller_id)
                        if controller is None or str(controller.currentData()) not in set(allowed_values):
                            visible = False
                            break
                    row_widget, label_widget = rows.get(field.id, (None, None))
                    if row_widget is not None:
                        row_widget.setVisible(visible)
                    if label_widget is not None:
                        label_widget.setVisible(visible)

            def apply_mode(_index: int, combo: QComboBox = mode_combo, widgets: list[QWidget] = field_widgets) -> None:
                editable = combo.currentData() == "custom"
                for widget in widgets:
                    widget.setEnabled(editable)
                apply_visibility()
                self.guarded_refresh_software_preview()

            for choice_combo in choice_fields.values():
                choice_combo.currentIndexChanged.connect(
                    lambda _index, refresh=apply_visibility: (refresh(), self.guarded_refresh_software_preview())
                )
            mode_combo.currentIndexChanged.connect(apply_mode)
            apply_mode(mode_combo.currentIndex())
            layout.addWidget(group)

        for slot, layout in self.driver_config_tab_layouts.items():
            if not instances_by_slot.get(slot):
                label = QLabel(f"No software driver config fields for {slot}.")
                label.setWordWrap(True)
                layout.addWidget(label)
            layout.addStretch(1)

    def refresh_data_visualization_options(self, values: dict[str, str] | None = None, refresh_preview: bool = True) -> None:
        if self.visualization_tabs is None:
            return
        if values is not None and not isinstance(values, dict):
            values = None
        if values is None:
            selected = self.selected_visualization_signals()
        else:
            selected = {
                key.removeprefix("visualize_")
                for key, value in values.items()
                if key.startswith("visualize_") and str(value).lower() in {"1", "true", "yes", "on"}
            }
        for layout in self.visualization_tab_layouts.values():
            for index in reversed(range(layout.count())):
                item = layout.itemAt(index)
                widget = item.widget()
                if widget is not None:
                    widget.setParent(None)
                else:
                    layout.removeItem(item)
        self.visualization_checkboxes.clear()

        source_text = self.software_fields.get("source_dir").text().strip() if self.software_fields.get("source_dir") else ""
        source_dir = Path(source_text) if source_text else Path("<software source folder>")
        signals = self.software_generator.visualization_signals(
            source_dir,
            self.assignments(),
            self.detail_options,
            self.software_modes(),
            self.software_presets(),
        )
        signals_by_slot: dict[str, list[Any]] = {slot: [] for slot in SLOTS}
        for signal in signals:
            signals_by_slot.setdefault(signal.slot, []).append(signal)
        for signal in signals:
            slot_layout = self.visualization_tab_layouts.get(signal.slot)
            if slot_layout is None:
                continue
            checkbox = QCheckBox(signal.label)
            checkbox.setChecked(signal.signal_id in selected)
            self.visualization_checkboxes[signal.signal_id] = checkbox
            slot_layout.addWidget(checkbox)
        for slot, layout in self.visualization_tab_layouts.items():
            if not signals_by_slot.get(slot):
                label = QLabel(f"No generated visualization signals for {slot}.")
                label.setWordWrap(True)
                layout.addWidget(label)
            layout.addStretch(1)
        if refresh_preview:
            self.guarded_refresh_software_preview()

    def reset_axi_config(self) -> None:
        self.load_axi_config({str(key): str(value) for key, value in self.database.axi_interconnect.items()})

    def load_cpld_programmer_config(self, values: dict[str, str]) -> None:
        for key, field in self.cpld_programmer_fields.items():
            field.blockSignals(True)
            if key in values:
                field.setText(values[key])
            field.blockSignals(False)

    def load_platform_cpld_config(self, values: dict[str, str]) -> None:
        if not self.platform_cpld_type_combo:
            return
        cpld_type = values.get("rev04_cpld_type", "")
        if not cpld_type:
            return
        index = self.platform_cpld_type_combo.findData(cpld_type)
        if index >= 0:
            self.platform_cpld_type_combo.setCurrentIndex(index)

    def load_axi_config(self, values: dict[str, str]) -> None:
        normalized = dict(values)
        legacy_to_d_slot = {
            "upstream_smartconnect": "d_upstream_smartconnect",
            "clock_pin": "d_clock_pin",
            "resetn_pin": "d_resetn_pin",
            "address_space": "d_address_space",
        }
        for legacy_key, d_slot_key in legacy_to_d_slot.items():
            if d_slot_key not in normalized and legacy_key in normalized:
                normalized[d_slot_key] = normalized[legacy_key]
        provisional_a_defaults = {
            "a_clock_pin": "uz_system/aclk",
            "a_resetn_pin": "uz_system/aresetn",
        }
        for key, old_value in provisional_a_defaults.items():
            if normalized.get(key) == old_value:
                normalized[key] = str(self.database.axi_interconnect.get(key, ""))
        for key, field in self.axi_fields.items():
            field.blockSignals(True)
            field.setText(normalized.get(key, str(self.database.axi_interconnect.get(key, ""))))
            field.blockSignals(False)

    def adapter_card_changed(self, slot: str) -> None:
        if self.is_loading_config:
            return
        if slot in DIGITAL_SLOTS:
            self.prefill_cpld_for_slot(slot)
        self.refresh_software_preset_options(refresh_dependent=False)
        self.software_dependent_views_dirty = True
        self.guarded_refresh_tcl_preview()

    def software_driver_selection_changed(self) -> None:
        if self.is_loading_config:
            return
        self.software_dependent_views_dirty = True
        self.refresh_software_preview()

    def prefill_cpld_for_slot(self, slot: str) -> None:
        combo = self.cpld_combos.get(slot)
        if not combo:
            return
        program_id = default_cpld_for_card(self.database, self.assignments().get(slot, "empty"), slot)
        index = combo.findData(program_id)
        combo.blockSignals(True)
        combo.setCurrentIndex(index if index >= 0 else max(combo.findData("none"), 0))
        combo.blockSignals(False)

    def option_values(self) -> dict[str, dict[str, str]]:
        values: dict[str, dict[str, str]] = deepcopy(self.detail_options)
        for (slot, option_id), combo in self.detail_combos.items():
            values.setdefault(slot, {})[option_id] = combo.currentData() or ""
        for (slot, option_id), edit in self.detail_trigger_edits.items():
            values.setdefault(slot, {})[f"{option_id}_trigger_source"] = edit.text().strip()
        for (slot, field_id), edit in self.detail_source_edits.items():
            values.setdefault(slot, {})[field_id] = edit.text().strip()
        return values

    def selected_platform(self) -> dict[str, Any]:
        platform_id = self.platform_combo.currentData()
        platform = self.database.platform_by_id(platform_id)
        revision = self.platform_revision_combo.currentData() or self.platform_revision_combo.currentText()
        if platform:
            selected = dict(platform)
            selected["revision"] = revision
            return selected
        return {"id": platform_id or "", "name": self.platform_combo.currentText(), "revision": revision}

    def platform_changed(self) -> None:
        if self.is_loading_config:
            return
        previous_revision = self.platform_revision_combo.currentData() or self.platform_revision_combo.currentText()
        self.refresh_platform_revisions(previous_revision)
        self.refresh_platform_cpld_visibility()
        self.invalidate_cpld_project_file()
        self.guarded_refresh_tcl_preview()

    def platform_revision_changed(self) -> None:
        if self.is_loading_config:
            return
        self.refresh_platform_cpld_visibility()
        self.invalidate_cpld_project_file()
        self.guarded_refresh_tcl_preview()

    def platform_cpld_type_changed(self) -> None:
        if self.is_loading_config:
            return
        self.invalidate_cpld_project_file()
        self.guarded_refresh_tcl_preview()

    def refresh_platform_revisions(self, preferred_revision: str = "") -> None:
        platform = self.database.platform_by_id(self.platform_combo.currentData()) or {}
        revisions = [str(revision) for revision in platform.get("revisions", [])]
        self.platform_revision_combo.blockSignals(True)
        self.platform_revision_combo.clear()
        for revision in revisions:
            self.platform_revision_combo.addItem(revision, revision)
        index = self.platform_revision_combo.findData(preferred_revision)
        if index < 0:
            index = 0
        self.platform_revision_combo.setCurrentIndex(index if self.platform_revision_combo.count() else -1)
        self.platform_revision_combo.blockSignals(False)
        self.refresh_platform_cpld_visibility()

    def refresh_platform_cpld_visibility(self) -> None:
        if not self.platform_cpld_group:
            return
        self.platform_cpld_group.setVisible(self.is_ultrazohm_rev04())

    def is_ultrazohm_rev04(self) -> bool:
        return (self.platform_combo.currentData() == "ultrazohm") and (
            (self.platform_revision_combo.currentData() or self.platform_revision_combo.currentText()) == "Rev04"
        )

    def rev04_cpld_type(self) -> str:
        if not self.platform_cpld_type_combo:
            return "la4128v"
        return str(self.platform_cpld_type_combo.currentData() or "la4128v")

    def selected_cpld_variant(self) -> str:
        platform_id = self.platform_combo.currentData()
        revision = self.platform_revision_combo.currentData() or self.platform_revision_combo.currentText()
        if platform_id == "ultrazohm":
            if revision == "Rev04":
                return self.rev04_cpld_type()
            return "machxo2"
        if platform_id == "microzohm":
            return "microzohm"
        return "machxo2"

    def show_platform_page(self) -> None:
        self.stack.setCurrentIndex(1)
        self.tree.setCurrentItem(self.tree.topLevelItem(1))

    def show_toolchain_page(self) -> None:
        self.stack.setCurrentIndex(0)
        self.tree.setCurrentItem(self.tree.topLevelItem(0))

    def show_adapter_cards(self) -> None:
        self.stack.setCurrentIndex(3)
        self.tree.setCurrentItem(self.tree.topLevelItem(2).child(2))

    def show_hardware_configuration(self) -> None:
        self.show_hardware_general()

    def show_hardware_general(self) -> None:
        self.stack.setCurrentIndex(2)
        self.tree.setCurrentItem(self.tree.topLevelItem(2).child(0))

    def show_slot_cplds(self) -> None:
        self.stack.setCurrentIndex(4)
        self.tree.setCurrentItem(self.tree.topLevelItem(2).child(3))

    def show_axi_interconnect(self) -> None:
        self.stack.setCurrentIndex(5)
        self.tree.setCurrentItem(self.tree.topLevelItem(2).child(1))

    def import_cable_settings_from_xcf(self) -> None:
        path_text, _ = QFileDialog.getOpenFileName(
            self,
            "Import cable settings from XCF",
            str(APP_DIR),
            "Lattice Diamond Programmer project (*.xcf);;All files (*)",
        )
        if not path_text:
            return
        path = Path(path_text)
        try:
            settings = read_cable_settings_from_xcf(path)
        except (OSError, ValueError) as error:
            QMessageBox.warning(self, "Could not import cable settings", str(error))
            return

        self.load_cpld_programmer_config({key: value for key, value in settings.items() if value or key == "usb_id"})
        self.invalidate_cpld_project_file()
        imported = [
            f"Imported cable settings from {path}",
            f"CableName: {settings.get('cable_name', '')}",
            f"PortAdd: {settings.get('port_address', '')}",
            f"USBID: {settings.get('usb_id', '')}",
            f"TCKDelay: {settings.get('tck_delay', '')}",
        ]
        self.set_cpld_status("\n".join(imported))

    def write_lattice_diamond_project_file(self) -> None:
        try:
            result = self.generate_lattice_diamond_project_file()
        except (OSError, ValueError) as error:
            self.cpld_xcf_current = False
            self.refresh_cpld_program_button_state()
            self.set_cpld_status(f"Could not write Lattice Diamond Programmer project file:\n{error}")
            QMessageBox.warning(self, "Could not write project file", str(error))
            return
        messages = [
            f"Wrote {result.path}",
            f"Active slots: {', '.join(result.active_slots) if result.active_slots else 'none'}",
            f"Not programmed: {', '.join(result.inactive_slots) if result.inactive_slots else 'none'}",
        ]
        messages.extend(f"WARNING: {warning}" for warning in result.warnings)
        self.cpld_xcf_current = True
        self.refresh_cpld_program_button_state()
        self.set_cpld_status("\n".join(messages))

    def program_cplds_via_cli(self) -> None:
        if self.cpld_process and self.cpld_process.state() != QProcess.ProcessState.NotRunning:
            return
        try:
            programmer_path = Path(self.toolchain_config().get("lattice_programmer_executable", ""))
            if not programmer_path.exists():
                raise FileNotFoundError(f"Lattice Programmer executable not found: {programmer_path}")
            if not self.cpld_xcf_current or not self.cpld_xcf_path.exists():
                raise FileNotFoundError("Generate the Lattice Diamond Programmer project file before programming.")
            log_path = OUTPUT_DIR / "project_wizard_slot_cplds.log"
        except (OSError, ValueError) as error:
            self.set_cpld_status(f"Could not program CPLDs:\n{error}")
            QMessageBox.warning(self, "Could not program CPLDs", str(error))
            return

        try:
            if log_path.exists():
                log_path.unlink()
        except OSError:
            pass

        command = [str(programmer_path), "-infile", str(self.cpld_xcf_path), "-logfile", str(log_path)]
        self.cpld_log_path = log_path
        self.set_cpld_status("")
        self.append_cpld_status("Programming CPLDs via Lattice Programmer...", "#0057b8")
        self.append_cpld_status(f"Command: {' '.join(command)}")
        self.append_cpld_status(f"Project file: {self.cpld_xcf_path}")
        self.append_cpld_status(f"Log file: {log_path}")
        self.set_cpld_programming_busy(True)
        self.statusBar().showMessage("Programming CPLDs...")

        process = QProcess(self)
        self.cpld_process = process
        process.setProgram(str(programmer_path))
        process.setArguments(["-infile", str(self.cpld_xcf_path), "-logfile", str(log_path)])
        process.setWorkingDirectory(str(programmer_path.parent))
        process.readyReadStandardOutput.connect(self.read_cpld_process_stdout)
        process.readyReadStandardError.connect(self.read_cpld_process_stderr)
        process.errorOccurred.connect(self.cpld_process_error)
        process.finished.connect(self.cpld_process_finished)
        process.start()

    def generate_lattice_diamond_project_file(self):
        toolchain = self.toolchain_config()
        repository_path = Path(toolchain.get("cpld_repository", ""))
        programmer_path = Path(toolchain.get("lattice_programmer_executable", ""))
        if not repository_path.exists():
            raise FileNotFoundError(f"CPLD repository not found: {repository_path}")
        if not programmer_path.exists():
            raise FileNotFoundError(f"Lattice Programmer executable not found: {programmer_path}")
        return generate_d_slot_xcf(
            self.cpld_xcf_path,
            repository_path,
            programmer_path,
            self.cpld_assignments(),
            self.cpld_programmer_config(include_variant=True),
        )

    def set_cpld_status(self, text: str) -> None:
        if self.cpld_status:
            self.cpld_status.setPlainText(text)

    def append_cpld_status(self, text: str, color: str | None = None) -> None:
        if not self.cpld_status:
            return
        escaped = html.escape(text)
        if color:
            self.cpld_status.append(f'<span style="color: {color};">{escaped}</span>')
        else:
            self.cpld_status.append(escaped)

    def set_cpld_programming_busy(self, busy: bool) -> None:
        if self.write_cpld_button:
            self.write_cpld_button.setEnabled(not busy)
        if self.program_cpld_button:
            self.program_cpld_button.setEnabled((not busy) and self.cpld_xcf_current and self.cpld_xcf_path.exists())
            self.program_cpld_button.setText("Programming..." if busy else "Programm CPLDs via CLI")

    def invalidate_cpld_project_file(self) -> None:
        self.cpld_xcf_current = False
        self.refresh_cpld_program_button_state()

    def refresh_cpld_program_button_state(self) -> None:
        if not self.program_cpld_button:
            return
        busy = self.cpld_process is not None and self.cpld_process.state() != QProcess.ProcessState.NotRunning
        self.program_cpld_button.setEnabled((not busy) and self.cpld_xcf_current and self.cpld_xcf_path.exists())

    def read_cpld_process_stdout(self) -> None:
        if not self.cpld_process:
            return
        text = bytes(self.cpld_process.readAllStandardOutput()).decode(errors="replace")
        self.append_cpld_process_text(text)

    def read_cpld_process_stderr(self) -> None:
        if not self.cpld_process:
            return
        text = bytes(self.cpld_process.readAllStandardError()).decode(errors="replace")
        self.append_cpld_process_text(text, default_color="#c62828")

    def append_cpld_process_text(self, text: str, default_color: str | None = None) -> None:
        for line in text.splitlines():
            self.append_cpld_status(line, self.cpld_log_line_color(line) or default_color)

    def cpld_process_error(self, error: QProcess.ProcessError) -> None:
        self.append_cpld_status(f"Process error: {error.name}", "#c62828")

    def cpld_process_finished(self, exit_code: int, _exit_status: QProcess.ExitStatus) -> None:
        self.set_cpld_programming_busy(False)
        self.statusBar().clearMessage()
        self.append_cpld_status("")
        self.append_cpld_status(f"Lattice Programmer exited with code {exit_code}", "#2e7d32" if exit_code == 0 else "#c62828")
        self.append_cpld_log_file()
        if exit_code == 0:
            QMessageBox.information(self, "CPLD programming finished", "Lattice Programmer finished successfully.")
        else:
            QMessageBox.warning(self, "CPLD programming failed", f"Lattice Programmer exited with code {exit_code}.")
        self.cpld_process = None

    def append_cpld_log_file(self) -> None:
        if not self.cpld_log_path:
            return
        if not self.cpld_log_path.exists():
            self.append_cpld_status(f"Log file was not written: {self.cpld_log_path}", "#c62828")
            return
        self.append_cpld_status("")
        self.append_cpld_status(f"Log file: {self.cpld_log_path}", "#0057b8")
        log_text = self.cpld_log_path.read_text(encoding="utf-8", errors="replace")
        if not log_text.strip():
            self.append_cpld_status("No log text was written.")
            return
        for line in log_text.splitlines():
            self.append_cpld_status(line, self.cpld_log_line_color(line))

    @staticmethod
    def cpld_log_line_color(line: str) -> str | None:
        upper_line = line.upper()
        if "NO ERROR" in upper_line or "NO ERRORS" in upper_line:
            return None
        if "ERROR" in upper_line or "FAILED" in upper_line or "FAIL" in upper_line:
            return "#c62828"
        if "PASS" in upper_line or "SUCCESS" in upper_line or "SUCCESSFULLY" in upper_line:
            return "#2e7d32"
        return None

    def show_card_database(self) -> None:
        self.stack.setCurrentIndex(10)

    def show_software_general(self) -> None:
        self.stack.setCurrentIndex(6)
        self.tree.setCurrentItem(self.tree.topLevelItem(3).child(0))

    def show_ip_core_driver_setup(self) -> None:
        self.stack.setCurrentIndex(7)
        self.tree.setCurrentItem(self.tree.topLevelItem(3).child(1))

    def show_advanced_driver_config(self) -> None:
        self.refresh_dirty_software_dependent_views()
        self.stack.setCurrentIndex(8)
        self.tree.setCurrentItem(self.tree.topLevelItem(3).child(2))

    def show_data_visualization(self) -> None:
        self.refresh_dirty_software_dependent_views()
        self.stack.setCurrentIndex(9)
        self.tree.setCurrentItem(self.tree.topLevelItem(3).child(3))

    def refresh_dirty_software_dependent_views(self) -> None:
        if self.is_loading_config or not self.software_dependent_views_dirty:
            return
        values = self.software_config()
        self.refresh_advanced_driver_config_options()
        self.refresh_data_visualization_options(values, refresh_preview=False)
        self.software_dependent_views_dirty = False

    def rebuild_details(self) -> None:
        self._clear_details_layouts()
        self.detail_combos = {}
        self.detail_trigger_edits = {}
        self.detail_source_edits = {}
        assignments = self.assignments()
        for slot, card_id in assignments.items():
            page_layout = self.slot_detail_layouts[slot]
            card = self.database.card_by_id(card_id)
            if not card or card_id == "empty":
                page_layout.insertWidget(page_layout.count() - 1, QLabel(f"{slot}: Empty slot"))
                continue

            group = QGroupBox(f"{slot}: {card.get('name', card_id)}")
            group_layout = QVBoxLayout(group)
            if card.get("description"):
                description = QLabel(card.get("description", ""))
                description.setWordWrap(True)
                group_layout.addWidget(description)

            driver = card.get("vitis", {}).get("driver", "")
            if driver:
                group_layout.addWidget(QLabel(f"Vitis driver: {driver}"))
            for note in card.get("vivado", {}).get("notes", []):
                note_label = QLabel(f"Vivado: {note}")
                note_label.setWordWrap(True)
                group_layout.addWidget(note_label)

            if card.get("options"):
                form = QFormLayout()
                for option in card.get("options", []):
                    option_id = option.get("id", "")
                    combo = QComboBox()
                    selected = self.detail_options.get(slot, {}).get(option_id, option.get("default", ""))
                    for choice in option.get("choices", []):
                        combo.addItem(choice.get("label", choice.get("id", "")), choice.get("id", ""))
                    index = combo.findData(selected)
                    combo.setCurrentIndex(index if index >= 0 else 0)
                    key = (slot, option_id)
                    self.detail_combos[key] = combo
                    combo.currentIndexChanged.connect(self._detail_option_changed)

                    trigger_source = self.detail_options.get(slot, {}).get(
                        f"{option_id}_trigger_source",
                        "trigger_conversions",
                    )
                    trigger_edit = QLineEdit(trigger_source)
                    trigger_edit.setEnabled(combo.currentData() != "none")
                    trigger_edit.editingFinished.connect(self._detail_option_changed)
                    self.detail_trigger_edits[key] = trigger_edit

                    row = QWidget()
                    row_layout = QHBoxLayout(row)
                    row_layout.setContentsMargins(0, 0, 0, 0)
                    row_layout.addWidget(combo, 1)
                    row_layout.addWidget(QLabel("Trigger source"))
                    row_layout.addWidget(trigger_edit, 1)
                    form.addRow(option.get("label", option_id or "Option"), row)
                group_layout.addLayout(form)

            source_fields = card.get("vivado", {}).get("source_fields", [])
            if source_fields:
                source_group = QGroupBox("Vivado source signals")
                source_layout = QFormLayout(source_group)
                for source_field in source_fields:
                    field_id = source_field.get("id", "")
                    if not field_id:
                        continue
                    value = self.detail_options.get(slot, {}).get(field_id, source_field.get("default", ""))
                    edit = QLineEdit(value)
                    edit.setPlaceholderText(source_field.get("placeholder", "Block design pin path"))
                    if source_field.get("tooltip") or source_field.get("help"):
                        edit.setToolTip(source_field.get("tooltip", source_field.get("help", "")))
                    edit.editingFinished.connect(self._detail_option_changed)
                    self.detail_source_edits[(slot, field_id)] = edit
                    source_layout.addRow(source_field.get("label", field_id), edit)
                group_layout.addWidget(source_group)

            page_layout.insertWidget(page_layout.count() - 1, group)

        for slot in list(self.detail_options):
            if assignments.get(slot, "empty") == "empty":
                self.detail_options.pop(slot, None)
        if self.is_loading_config:
            self.software_dependent_views_dirty = True
            return
        self.refresh_software_preset_options()
        self.guarded_refresh_data_visualization_options()
        self.refresh_advanced_driver_config_options()
        self.guarded_refresh_tcl_preview()

    def _clear_details_layouts(self) -> None:
        for layout in self.slot_detail_layouts.values():
            while layout.count() > 1:
                item = layout.takeAt(0)
                widget = item.widget()
                if widget:
                    widget.deleteLater()

    def _detail_option_changed(self) -> None:
        for (slot, option_id), combo in self.detail_combos.items():
            self.detail_options.setdefault(slot, {})[option_id] = combo.currentData() or ""
            trigger_edit = self.detail_trigger_edits.get((slot, option_id))
            if trigger_edit:
                trigger_edit.setEnabled(combo.currentData() != "none")
                self.detail_options.setdefault(slot, {})[f"{option_id}_trigger_source"] = trigger_edit.text().strip()
        for (slot, field_id), edit in self.detail_source_edits.items():
            self.detail_options.setdefault(slot, {})[field_id] = edit.text().strip()
        self.software_dependent_views_dirty = True
        self.guarded_refresh_tcl_preview()

    def refresh_tcl_preview(self) -> None:
        self.tcl_preview.setPlainText(
            self.generator.generate(
                self.selected_platform(),
                self.assignments(),
                self.option_values(),
                self.cpld_assignments(),
                self.axi_config(),
                self.hardware_config(),
            )
        )
        self.refresh_software_preview()

    def refresh_software_preview(self) -> None:
        if self.software_preview is None:
            return
        source_text = self.software_fields.get("source_dir").text().strip() if self.software_fields.get("source_dir") else ""
        source_dir = Path(source_text) if source_text else Path("<software source folder>")
        self.software_preview.setPlainText(
            self.software_generator.preview(
                source_dir,
                self.assignments(),
                self.option_values(),
                self.selected_platform().get("revision", ""),
                self.software_modes(),
                self.software_presets(),
                self.selected_visualization_signals(),
                self.driver_config_values(),
            )
        )

    def generate_software_files(self) -> None:
        self.refresh_dirty_software_dependent_views()
        source_field = self.software_fields.get("source_dir")
        source_text = source_field.text().strip() if source_field else ""
        if not source_text:
            QMessageBox.warning(self, "Software source folder missing", "Please select the folder that contains globalData.h.")
            return
        source_dir = Path(source_text)
        assignments = self.assignments()
        option_values = self.option_values()
        platform_revision = self.selected_platform().get("revision", "")
        software_modes = self.software_modes()
        software_presets = self.software_presets()
        visualization_signals = self.selected_visualization_signals()
        driver_config = self.driver_config_values()
        try:
            plan = self.software_generator.build_plan(
                source_dir,
                assignments,
                option_values,
                software_modes,
                software_presets,
                visualization_signals,
                driver_config,
            )
        except (OSError, ValueError) as error:
            QMessageBox.warning(self, "Could not prepare software generation", str(error))
            return
        if plan.warnings:
            warning_box = QMessageBox(self)
            warning_box.setIcon(QMessageBox.Icon.Warning)
            warning_box.setWindowTitle("Software generation warnings")
            warning_box.setText("The software generator found warnings.")
            warning_box.setInformativeText("Continue writing files anyway?")
            warning_box.setDetailedText("\n".join(f"- {warning}" for warning in plan.warnings))
            cancel_button = warning_box.addButton("Cancel", QMessageBox.ButtonRole.RejectRole)
            continue_button = warning_box.addButton("Continue", QMessageBox.ButtonRole.AcceptRole)
            warning_box.setDefaultButton(cancel_button)
            warning_box.exec()
            if warning_box.clickedButton() != continue_button:
                if self.software_status:
                    self.software_status.setPlainText("Software generation canceled because warnings were not accepted.")
                return
        try:
            result = self.software_generator.generate(
                source_dir,
                assignments,
                option_values,
                platform_revision,
                software_modes,
                software_presets,
                visualization_signals,
                driver_config,
            )
        except (OSError, ValueError) as error:
            QMessageBox.warning(self, "Could not generate software files", str(error))
            return

        status = ["Software generation finished."]
        if result.written_files:
            status.append("Written files:")
            status.extend(f"- {path}" for path in result.written_files)
        else:
            status.append("Written files: none")
        if result.patched_files:
            status.append("Patched files:")
            status.extend(f"- {path}" for path in result.patched_files)
        else:
            status.append("Patched files: none")
        if result.warnings:
            status.append("Warnings:")
            status.extend(f"- {warning}" for warning in result.warnings)
        if self.software_status:
            self.software_status.setPlainText("\n".join(status))
        self.refresh_software_preview()

    def refresh_card_table(self) -> None:
        self.card_table.setRowCount(len(self.database.cards))
        for row, card in enumerate(self.database.cards):
            values = [
                card.get("id", ""),
                card.get("name", ""),
                card.get("family", ""),
                ", ".join(card.get("compatible_slots", [])),
                card.get("vitis", {}).get("driver", ""),
            ]
            for column, value in enumerate(values):
                self.card_table.setItem(row, column, QTableWidgetItem(value))
            edit_button = QPushButton("Edit")
            edit_button.clicked.connect(lambda _checked=False, card_id=card.get("id", ""): self.edit_card(card_id))
            self.card_table.setCellWidget(row, 5, edit_button)
        self.card_table.resizeColumnsToContents()

    def add_card(self) -> None:
        dialog = CardEditorDialog(self)
        if dialog.exec() != QDialog.DialogCode.Accepted:
            return
        try:
            self.database.add_card(dialog.card())
        except ValueError as error:
            QMessageBox.warning(self, "Could not add card", str(error))
            return
        self.refresh_all_card_views()

    def edit_card(self, card_id: str) -> None:
        card = self.database.card_by_id(card_id)
        if not card:
            QMessageBox.warning(self, "Card not found", f"Could not find card {card_id}.")
            return
        dialog = CardEditorDialog(self, card)
        if dialog.exec() != QDialog.DialogCode.Accepted:
            return
        try:
            self.database.update_card(card_id, dialog.card())
        except ValueError as error:
            QMessageBox.warning(self, "Could not save card", str(error))
            return
        self.refresh_all_card_views()

    def new_config(self) -> None:
        self.current_config_path = None
        if self.platform_combo.count() > 0:
            self.platform_combo.setCurrentIndex(0)
        self.refresh_platform_revisions()
        if self.platform_cpld_type_combo:
            self.platform_cpld_type_combo.setCurrentIndex(0)
        self.refresh_platform_cpld_visibility()
        self.detail_options = {}
        self.reset_hardware_config()
        for slot, combo in self.slot_combos.items():
            default_card_id = "no_adapter_board" if slot.startswith("A") else "empty"
            index = combo.findData(default_card_id)
            combo.setCurrentIndex(index if index >= 0 else 0)
        for slot in DIGITAL_SLOTS:
            self.prefill_cpld_for_slot(slot)
        self.refresh_software_preset_options()
        self.reset_axi_config()
        self.reset_software_config()
        self.rebuild_details()
        self.refresh_tcl_preview()

    def open_config(self) -> None:
        path_text, _ = QFileDialog.getOpenFileName(
            self,
            "Open config",
            str(APP_DIR),
            "Project Wizard config (*.pw.json);;JSON files (*.json)",
        )
        if not path_text:
            return
        path = Path(path_text)
        progress = QProgressDialog("Reading config file...", "", 0, 7, self)
        progress.setWindowTitle("Loading config")
        progress.setCancelButton(None)
        progress.setWindowModality(Qt.WindowModality.ApplicationModal)
        progress.setMinimumDuration(0)
        progress.setValue(0)
        progress.show()
        QApplication.processEvents()
        self.is_loading_config = True
        try:
            self.update_config_load_progress(progress, 1, "Parsing config file...")
            document = json.loads(path.read_text(encoding="utf-8"))
            self.load_config_document(document, progress)
        except (OSError, json.JSONDecodeError, ValueError) as error:
            self.is_loading_config = False
            progress.close()
            QMessageBox.warning(self, "Could not open config", str(error))
            return
        self.current_config_path = path
        self.is_loading_config = False
        self.update_config_load_progress(progress, 7, "Refreshing previews...")
        software = document.get("software", {})
        software_values = {str(key): str(value) for key, value in software.items()} if isinstance(software, dict) else {}
        self.refresh_software_preset_options(software_values)
        self.software_dependent_views_dirty = False
        self.refresh_tcl_preview()
        progress.close()

    def save_config(self) -> None:
        if self.current_config_path is None:
            self.save_config_as()
            return
        self.write_config(self.current_config_path)

    def save_config_as(self) -> None:
        default_path = self.current_config_path or (APP_DIR / "generated" / "project_wizard_config.pw.json")
        path_text, _ = QFileDialog.getSaveFileName(
            self,
            "Save config as",
            str(default_path),
            "Project Wizard config (*.pw.json);;JSON files (*.json)",
        )
        if not path_text:
            return
        path = Path(path_text)
        self.current_config_path = path
        self.write_config(path)

    def write_config(self, path: Path) -> None:
        try:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(json.dumps(self.config_document(), indent=2) + "\n", encoding="utf-8")
        except OSError as error:
            QMessageBox.warning(self, "Could not save config", str(error))
            return
        QMessageBox.information(self, "Config saved", f"Wrote {path}")

    def config_document(self) -> dict[str, Any]:
        self.refresh_dirty_software_dependent_views()
        return build_config_document(
            self.selected_platform(),
            self.platform_cpld_config(),
            self.toolchain_config(),
            self.hardware_config(),
            self.assignments(),
            self.option_values(),
            self.cpld_assignments(),
            self.cpld_programmer_config(),
            self.axi_config(),
            self.software_config(),
        )

    def resolved_system_model(self):
        return self.system_resolver.resolve(SystemConfig.from_document(self.config_document()))

    def update_config_load_progress(self, progress: QProgressDialog | None, value: int, message: str) -> None:
        if progress is None:
            return
        progress.setLabelText(message)
        progress.setValue(value)
        QApplication.processEvents()

    def load_config_document(self, document: dict[str, Any], progress: QProgressDialog | None = None) -> None:
        if not isinstance(document, dict):
            raise ValueError("Config must be a JSON object.")
        self.update_config_load_progress(progress, 2, "Loading platform and toolchain...")
        platform_id = document.get("platform", "")
        platform_index = self.platform_combo.findData(platform_id)
        if platform_index >= 0:
            self.platform_combo.setCurrentIndex(platform_index)
        platform_revision = str(document.get("platform_revision", ""))
        self.refresh_platform_revisions(platform_revision)

        platform_cpld = document.get("platform_cpld", {})
        if platform_cpld is None:
            platform_cpld = {}
        if not isinstance(platform_cpld, dict):
            raise ValueError("Config field 'platform_cpld' must be a JSON object.")
        self.load_platform_cpld_config({str(key): str(value) for key, value in platform_cpld.items()})
        self.refresh_platform_cpld_visibility()

        toolchain = document.get("toolchain", {})
        if toolchain is None:
            toolchain = {}
        if not isinstance(toolchain, dict):
            raise ValueError("Config field 'toolchain' must be a JSON object.")
        self.load_toolchain_config({str(key): str(value) for key, value in toolchain.items()})

        hardware = document.get("hardware", {})
        if hardware is None:
            hardware = {}
        if not isinstance(hardware, dict):
            raise ValueError("Config field 'hardware' must be a JSON object.")
        self.load_hardware_config({str(key): str(value) for key, value in hardware.items()})

        self.update_config_load_progress(progress, 3, "Loading adapter cards...")
        slots = document.get("slots", {})
        if not isinstance(slots, dict):
            raise ValueError("Config field 'slots' must be a JSON object.")
        for slot, combo in self.slot_combos.items():
            card_id = slots.get(slot, "empty")
            if slot.startswith("A") and card_id == "empty":
                card_id = "no_adapter_board"
            index = combo.findData(card_id)
            if index < 0:
                fallback_card_id = "no_adapter_board" if slot.startswith("A") else "empty"
                index = combo.findData(fallback_card_id)
            combo.setCurrentIndex(index if index >= 0 else 0)

        self.update_config_load_progress(progress, 4, "Loading adapter card details...")
        slot_options = document.get("slot_options", {})
        if not isinstance(slot_options, dict):
            raise ValueError("Config field 'slot_options' must be a JSON object.")
        self.detail_options = {
            str(slot): {str(option_id): str(value) for option_id, value in options.items()}
            for slot, options in slot_options.items()
            if isinstance(options, dict)
        }
        self.rebuild_details()

        self.update_config_load_progress(progress, 5, "Loading software configuration...")
        software = document.get("software", {})
        if software is None:
            software = {}
        if not isinstance(software, dict):
            raise ValueError("Config field 'software' must be a JSON object.")
        self.load_software_config({str(key): str(value) for key, value in software.items()})

        self.update_config_load_progress(progress, 6, "Loading CPLD and AXI settings...")
        slot_cplds = document.get("slot_cplds", {})
        if not isinstance(slot_cplds, dict):
            raise ValueError("Config field 'slot_cplds' must be a JSON object.")
        for slot, combo in self.cpld_combos.items():
            program_id = slot_cplds.get(slot)
            if program_id is None:
                self.prefill_cpld_for_slot(slot)
                continue
            index = combo.findData(program_id)
            combo.setCurrentIndex(index if index >= 0 else max(combo.findData("none"), 0))

        cpld_programmer = document.get("cpld_programmer", {})
        if cpld_programmer is None:
            cpld_programmer = {}
        if not isinstance(cpld_programmer, dict):
            raise ValueError("Config field 'cpld_programmer' must be a JSON object.")
        self.load_cpld_programmer_config({str(key): str(value) for key, value in cpld_programmer.items()})

        axi = document.get("axi", self.database.axi_interconnect)
        if not isinstance(axi, dict):
            raise ValueError("Config field 'axi' must be a JSON object.")
        self.load_axi_config({str(key): str(value) for key, value in axi.items()})

    def show_docs(self) -> None:
        QMessageBox.information(
            self,
            "Docs",
            f"Project notes are currently in:\n{APP_DIR / 'README.md'}",
        )

    def show_info(self) -> None:
        QMessageBox.information(
            self,
            "Info",
            "Project Wizard\n\nEarly PyQt sketch for configuring UltraZohm and MicroZohm projects.",
        )

    def execute_tcl_workflow(self) -> None:
        export_tcl = self.tcl_export_checkbox is None or self.tcl_export_checkbox.isChecked()
        run_vivado = self.tcl_run_vivado_checkbox is not None and self.tcl_run_vivado_checkbox.isChecked()
        if not export_tcl and not run_vivado:
            QMessageBox.warning(self, "Nothing selected", "Select Export TCL, Run TCL in Vivado, or both.")
            return
        if run_vivado and self.vivado_process and self.vivado_process.state() != QProcess.ProcessState.NotRunning:
            QMessageBox.warning(self, "Vivado is running", "A Vivado process started by the wizard is still running.")
            return

        if export_tcl:
            tcl_path = self.ask_tcl_export_path()
            if tcl_path is None:
                return
        else:
            tcl_path = OUTPUT_DIR / "project_wizard_config.tcl"

        try:
            self.write_generated_tcl(tcl_path)
        except OSError as error:
            QMessageBox.warning(self, "Could not write TCL", str(error))
            return

        if run_vivado:
            self.run_tcl_in_vivado(tcl_path)
            return

        self.show_tcl_export_result(tcl_path)

    def ask_tcl_export_path(self) -> Path | None:
        OUTPUT_DIR.mkdir(parents=True, exist_ok=True)
        default_path = OUTPUT_DIR / "project_wizard_config.tcl"
        path_text, _ = QFileDialog.getSaveFileName(self, "Export TCL", str(default_path), "TCL files (*.tcl)")
        return Path(path_text) if path_text else None

    def write_generated_tcl(self, path: Path) -> None:
        path.parent.mkdir(parents=True, exist_ok=True)
        warnings = self.generator.validation_warnings(self.assignments(), self.axi_config())
        path.write_text(
            self.generator.generate(
                self.selected_platform(),
                self.assignments(),
                self.option_values(),
                self.cpld_assignments(),
                self.axi_config(),
                self.hardware_config(),
            ),
            encoding="utf-8",
        )
        if self.vivado_status:
            self.vivado_status.setPlainText(f"Wrote TCL: {path}")

    def show_tcl_export_result(self, path: Path) -> None:
        warnings = self.generator.validation_warnings(self.assignments(), self.axi_config())
        if warnings:
            QMessageBox.warning(
                self,
                "TCL exported with warnings",
                f"Wrote {path}\n\n" + "\n".join(f"- {warning}" for warning in warnings),
            )
            return
        QMessageBox.information(self, "TCL exported", f"Wrote {path}")

    def export_tcl(self) -> None:
        if self.tcl_export_checkbox:
            self.tcl_export_checkbox.setChecked(True)
        if self.tcl_run_vivado_checkbox:
            self.tcl_run_vivado_checkbox.setChecked(False)
        self.execute_tcl_workflow()

    def run_tcl_in_vivado(self, tcl_path: Path) -> None:
        toolchain = self.toolchain_config()
        hardware = self.hardware_config()
        vivado_path = Path(toolchain.get("vivado_executable", ""))
        project_path = Path(hardware.get("vivado_project_file", ""))
        open_gui = hardware.get("open_vivado_gui", "false").lower() in {"1", "true", "yes", "on"}
        if not vivado_path.exists():
            QMessageBox.warning(self, "Vivado executable missing", f"Vivado executable not found:\n{vivado_path}")
            return
        if not project_path.exists():
            QMessageBox.warning(self, "Vivado project missing", f"Vivado project not found:\n{project_path}")
            return

        wrapper_path = OUTPUT_DIR / "project_wizard_run_vivado.tcl"
        try:
            write_vivado_run_wrapper(
                wrapper_path,
                project_path,
                tcl_path,
                hardware.get("block_design_name", "zusys"),
                hardware.get("validate_block_design", "true").lower() in {"1", "true", "yes", "on"},
                hardware.get("save_block_design", "false").lower() in {"1", "true", "yes", "on"},
                hardware.get("open_vivado_gui", "false").lower() in {"1", "true", "yes", "on"},
            )
        except OSError as error:
            QMessageBox.warning(self, "Could not write Vivado wrapper", str(error))
            return

        self.set_vivado_status(
            "\n".join(
                [
                    "Starting Vivado GUI debug run..." if open_gui else "Starting Vivado batch run...",
                    f"Vivado: {vivado_path}",
                    f"Project: {project_path}",
                    f"Generated TCL: {tcl_path}",
                    f"Wrapper TCL: {wrapper_path}",
                    "Close Vivado to finish this workflow." if open_gui else "",
                ]
            )
        )
        self.set_vivado_busy(True)
        self.statusBar().showMessage(
            "Running Vivado TCL workflow. Close Vivado to finish." if open_gui else "Running Vivado TCL workflow..."
        )
        process = QProcess(self)
        self.vivado_process = process
        vivado_args = ["-mode", "gui" if open_gui else "batch", "-source", str(wrapper_path)]
        if vivado_path.suffix.lower() in {".bat", ".cmd"}:
            process.setProgram("cmd.exe")
            process.setArguments(["/c", str(vivado_path), *vivado_args])
        else:
            process.setProgram(str(vivado_path))
            process.setArguments(vivado_args)
        process.setWorkingDirectory(str(project_path.parent))
        process.readyReadStandardOutput.connect(self.read_vivado_process_stdout)
        process.readyReadStandardError.connect(self.read_vivado_process_stderr)
        process.errorOccurred.connect(self.vivado_process_error)
        process.finished.connect(self.vivado_process_finished)
        process.start()

    def set_vivado_status(self, text: str) -> None:
        if self.vivado_status:
            self.vivado_status.setPlainText(text)

    def append_vivado_status(self, text: str) -> None:
        if self.vivado_status:
            self.vivado_status.appendPlainText(text)

    def read_vivado_process_stdout(self) -> None:
        if not self.vivado_process:
            return
        text = bytes(self.vivado_process.readAllStandardOutput()).decode(errors="replace")
        if text:
            self.append_vivado_status(text.rstrip())

    def read_vivado_process_stderr(self) -> None:
        if not self.vivado_process:
            return
        text = bytes(self.vivado_process.readAllStandardError()).decode(errors="replace")
        if text:
            self.append_vivado_status(text.rstrip())

    def vivado_process_error(self, error: QProcess.ProcessError) -> None:
        self.append_vivado_status(f"Process error: {error.name}")

    def vivado_process_finished(self, exit_code: int, _exit_status: QProcess.ExitStatus) -> None:
        self.set_vivado_busy(False)
        self.statusBar().clearMessage()
        self.append_vivado_status("")
        self.append_vivado_status(f"Vivado exited with code {exit_code}")
        if exit_code == 0:
            QMessageBox.information(self, "Vivado TCL workflow finished", "Vivado finished successfully.")
        else:
            QMessageBox.warning(self, "Vivado TCL workflow failed", f"Vivado exited with code {exit_code}.")
        self.vivado_process = None

    def set_vivado_busy(self, busy: bool) -> None:
        if self.tcl_workflow_button:
            self.tcl_workflow_button.setEnabled(not busy)
            self.tcl_workflow_button.setText("Running Vivado..." if busy else "Execute TCL workflow")
