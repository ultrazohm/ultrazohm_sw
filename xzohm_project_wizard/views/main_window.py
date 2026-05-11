from __future__ import annotations

import json
from copy import deepcopy
from pathlib import Path
from typing import Any

from PyQt6.QtCore import Qt
from PyQt6.QtGui import QAction, QFont
from PyQt6.QtWidgets import (
    QComboBox,
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
    QPushButton,
    QScrollArea,
    QSplitter,
    QStackedWidget,
    QTableWidget,
    QTableWidgetItem,
    QTabWidget,
    QTreeWidget,
    QTreeWidgetItem,
    QVBoxLayout,
    QWidget,
)

from ..paths import APP_DIR, DATA_FILE, DIGITAL_SLOTS, OUTPUT_DIR, SLOTS
from ..repositories import CardDatabase
from ..services.card_service import default_cpld_for_card
from ..services.config_service import build_config_document
from ..services.toolchain_service import TOOL_DEFINITIONS, detect_toolchain_executables
from ..tcl_generator import TclGenerator
from .card_editor import CardEditorDialog


class MainWindow(QMainWindow):
    def __init__(self) -> None:
        super().__init__()
        self.setWindowTitle("xZohm Project Wizard")
        self.resize(1200, 760)
        self.database = CardDatabase.load(DATA_FILE)
        self.generator = TclGenerator(self.database)
        self.current_config_path: Path | None = None
        self.slot_combos: dict[str, QComboBox] = {}
        self.cpld_combos: dict[str, QComboBox] = {}
        self.axi_fields: dict[str, QLineEdit] = {}
        self.toolchain_fields: dict[str, QLineEdit] = {}
        self.toolchain_status: QPlainTextEdit | None = None
        self.detail_combos: dict[tuple[str, str], QComboBox] = {}
        self.detail_trigger_edits: dict[tuple[str, str], QLineEdit] = {}
        self.detail_options: dict[str, dict[str, str]] = {}

        self.stack = QStackedWidget()
        self.tree = self._build_navigation()
        self.stack.addWidget(self._build_toolchain_page())
        self.stack.addWidget(self._build_platform_page())
        self.stack.addWidget(self._build_configuration_page())
        self.stack.addWidget(self._build_slot_cpld_page())
        self.stack.addWidget(self._build_axi_interconnect_page())
        self.stack.addWidget(self._build_placeholder_page("General"))
        self.stack.addWidget(self._build_placeholder_page("IP Core Driver Setup"))
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

        refresh_tcl_action = QAction("Refresh TCL preview", self)
        refresh_tcl_action.triggered.connect(self.refresh_tcl_preview)
        view_menu.addAction(refresh_tcl_action)

        help_menu = self.menuBar().addMenu("Help")
        docs_action = QAction("Docs", self)
        docs_action.triggered.connect(self.show_docs)
        help_menu.addAction(docs_action)

        info_action = QAction("Info", self)
        info_action.triggered.connect(self.show_info)
        help_menu.addAction(info_action)

    def _build_navigation(self) -> QTreeWidget:
        tree = QTreeWidget()
        tree.setHeaderHidden(True)
        toolchain = QTreeWidgetItem(["Toolchain"])
        platform = QTreeWidgetItem(["Platform"])
        config = QTreeWidgetItem(["Hardware configuration"])
        axi_interconnect = QTreeWidgetItem(["AXI interconnect"])
        adapter_cards = QTreeWidgetItem(["Adapter cards"])
        slot_cplds = QTreeWidgetItem(["Slot CPLDs"])
        config.addChild(axi_interconnect)
        config.addChild(adapter_cards)
        config.addChild(slot_cplds)
        software_config = QTreeWidgetItem(["Software configuration"])
        software_general = QTreeWidgetItem(["General"])
        ip_driver_setup = QTreeWidgetItem(["IP core driver setup"])
        software_config.addChild(software_general)
        software_config.addChild(ip_driver_setup)
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
        page_by_name = {
            "Toolchain": 0,
            "Platform": 1,
            "Hardware configuration": 4,
            "Adapter cards": 2,
            "Slot CPLDs": 3,
            "AXI interconnect": 4,
            "Software configuration": 5,
            "General": 5,
            "IP core driver setup": 6,
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
        self.platform_revision_combo.currentIndexChanged.connect(self.refresh_tcl_preview)
        form.addRow("Revision", self.platform_revision_combo)
        layout.addWidget(group)
        layout.addStretch(1)
        return page

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
        export_button = QPushButton("Export TCL")
        export_button.clicked.connect(self.export_tcl)
        buttons.addStretch(1)
        buttons.addWidget(preview_button)
        buttons.addWidget(export_button)
        outer.addLayout(buttons)

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
        outer = QVBoxLayout(page)

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
            form.addRow(slot, combo)
        outer.addWidget(group)

        buttons = QHBoxLayout()
        lattice_button = QPushButton("Write Lattice Diamond Programmer project file")
        lattice_button.clicked.connect(self.show_lattice_diamond_placeholder)
        buttons.addStretch(1)
        buttons.addWidget(lattice_button)
        buttons.addStretch(1)
        outer.addLayout(buttons)
        outer.addStretch(1)
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

        attachment_group = QGroupBox("Project-level AXI attachment point")
        attachment_form = QFormLayout(attachment_group)
        attachment_field_labels = [
            ("upstream_smartconnect", "Upstream SmartConnect"),
            ("clock_pin", "AXI clock pin"),
            ("resetn_pin", "AXI resetn pin"),
            ("address_space", "Address space"),
        ]
        for key, label in attachment_field_labels:
            edit = QLineEdit(str(defaults.get(key, "")))
            edit.textChanged.connect(self.refresh_tcl_preview)
            self.axi_fields[key] = edit
            attachment_form.addRow(label, edit)
        outer.addWidget(attachment_group)

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
        self.rebuild_details()
        self.refresh_tcl_preview()

    def assignments(self) -> dict[str, str]:
        return {slot: combo.currentData() or "empty" for slot, combo in self.slot_combos.items()}

    def cpld_assignments(self) -> dict[str, str]:
        return {slot: combo.currentData() or "none" for slot, combo in self.cpld_combos.items()}

    def axi_config(self) -> dict[str, str]:
        return {key: field.text().strip() for key, field in self.axi_fields.items()}

    def toolchain_config(self) -> dict[str, str]:
        return {key: field.text().strip() for key, field in self.toolchain_fields.items()}

    def load_toolchain_config(self, values: dict[str, str]) -> None:
        for key, field in self.toolchain_fields.items():
            field.blockSignals(True)
            field.setText(values.get(key, ""))
            field.blockSignals(False)

    def reset_toolchain_config(self) -> None:
        self.load_toolchain_config({})

    def reset_axi_config(self) -> None:
        self.load_axi_config({str(key): str(value) for key, value in self.database.axi_interconnect.items()})

    def load_axi_config(self, values: dict[str, str]) -> None:
        for key, field in self.axi_fields.items():
            field.blockSignals(True)
            field.setText(values.get(key, str(self.database.axi_interconnect.get(key, ""))))
            field.blockSignals(False)

    def adapter_card_changed(self, slot: str) -> None:
        if slot in DIGITAL_SLOTS:
            self.prefill_cpld_for_slot(slot)
        self.refresh_tcl_preview()

    def prefill_cpld_for_slot(self, slot: str) -> None:
        combo = self.cpld_combos.get(slot)
        if not combo:
            return
        program_id = default_cpld_for_card(self.database, self.assignments().get(slot, "empty"))
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
        previous_revision = self.platform_revision_combo.currentData() or self.platform_revision_combo.currentText()
        self.refresh_platform_revisions(previous_revision)
        self.refresh_tcl_preview()

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

    def show_platform_page(self) -> None:
        self.stack.setCurrentIndex(1)
        self.tree.setCurrentItem(self.tree.topLevelItem(1))

    def show_toolchain_page(self) -> None:
        self.stack.setCurrentIndex(0)
        self.tree.setCurrentItem(self.tree.topLevelItem(0))

    def show_adapter_cards(self) -> None:
        self.stack.setCurrentIndex(2)
        self.tree.setCurrentItem(self.tree.topLevelItem(2).child(1))

    def show_hardware_configuration(self) -> None:
        self.show_axi_interconnect()

    def show_slot_cplds(self) -> None:
        self.stack.setCurrentIndex(3)
        self.tree.setCurrentItem(self.tree.topLevelItem(2).child(2))

    def show_axi_interconnect(self) -> None:
        self.stack.setCurrentIndex(4)
        self.tree.setCurrentItem(self.tree.topLevelItem(2).child(0))

    def show_lattice_diamond_placeholder(self) -> None:
        message = QMessageBox(self)
        message.setWindowTitle("Lattice Diamond project file")
        message.setText('<span style="color: red;">To be implemented...</span>')
        message.setTextFormat(Qt.TextFormat.RichText)
        got_it = message.addButton("Got it", QMessageBox.ButtonRole.AcceptRole)
        message.setDefaultButton(got_it)
        message.exec()

    def show_card_database(self) -> None:
        self.stack.setCurrentIndex(7)

    def show_software_general(self) -> None:
        self.stack.setCurrentIndex(5)
        self.tree.setCurrentItem(self.tree.topLevelItem(3).child(0))

    def show_ip_core_driver_setup(self) -> None:
        self.stack.setCurrentIndex(6)
        self.tree.setCurrentItem(self.tree.topLevelItem(3).child(1))

    def rebuild_details(self) -> None:
        self._clear_details_layouts()
        self.detail_combos = {}
        self.detail_trigger_edits = {}
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
                    trigger_edit.textChanged.connect(self._detail_option_changed)
                    self.detail_trigger_edits[key] = trigger_edit

                    row = QWidget()
                    row_layout = QHBoxLayout(row)
                    row_layout.setContentsMargins(0, 0, 0, 0)
                    row_layout.addWidget(combo, 1)
                    row_layout.addWidget(QLabel("Trigger source"))
                    row_layout.addWidget(trigger_edit, 1)
                    form.addRow(option.get("label", option_id or "Option"), row)
                group_layout.addLayout(form)

            page_layout.insertWidget(page_layout.count() - 1, group)

        for slot in list(self.detail_options):
            if assignments.get(slot, "empty") == "empty":
                self.detail_options.pop(slot, None)
        self.refresh_tcl_preview()

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
        self.refresh_tcl_preview()

    def refresh_tcl_preview(self) -> None:
        self.tcl_preview.setPlainText(
            self.generator.generate(
                self.selected_platform(),
                self.assignments(),
                self.option_values(),
                self.cpld_assignments(),
                self.axi_config(),
            )
        )

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
        self.detail_options = {}
        for slot, combo in self.slot_combos.items():
            index = combo.findData("empty")
            combo.setCurrentIndex(index if index >= 0 else 0)
        for slot in DIGITAL_SLOTS:
            self.prefill_cpld_for_slot(slot)
        self.reset_axi_config()
        self.rebuild_details()
        self.refresh_tcl_preview()

    def open_config(self) -> None:
        path_text, _ = QFileDialog.getOpenFileName(
            self,
            "Open config",
            str(APP_DIR),
            "xZohm Project Wizard config (*.xzpw.json);;JSON files (*.json)",
        )
        if not path_text:
            return
        path = Path(path_text)
        try:
            document = json.loads(path.read_text(encoding="utf-8"))
            self.load_config_document(document)
        except (OSError, json.JSONDecodeError, ValueError) as error:
            QMessageBox.warning(self, "Could not open config", str(error))
            return
        self.current_config_path = path
        self.refresh_tcl_preview()

    def save_config(self) -> None:
        if self.current_config_path is None:
            self.save_config_as()
            return
        self.write_config(self.current_config_path)

    def save_config_as(self) -> None:
        default_path = self.current_config_path or (APP_DIR / "generated" / "xzohm_project_wizard_config.xzpw.json")
        path_text, _ = QFileDialog.getSaveFileName(
            self,
            "Save config as",
            str(default_path),
            "xZohm Project Wizard config (*.xzpw.json);;JSON files (*.json)",
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
        return build_config_document(
            self.selected_platform(),
            self.toolchain_config(),
            self.assignments(),
            self.option_values(),
            self.cpld_assignments(),
            self.axi_config(),
        )

    def load_config_document(self, document: dict[str, Any]) -> None:
        if not isinstance(document, dict):
            raise ValueError("Config must be a JSON object.")
        platform_id = document.get("platform", "")
        platform_index = self.platform_combo.findData(platform_id)
        if platform_index >= 0:
            self.platform_combo.setCurrentIndex(platform_index)
        platform_revision = str(document.get("platform_revision", ""))
        self.refresh_platform_revisions(platform_revision)

        toolchain = document.get("toolchain", {})
        if toolchain is None:
            toolchain = {}
        if not isinstance(toolchain, dict):
            raise ValueError("Config field 'toolchain' must be a JSON object.")
        self.load_toolchain_config({str(key): str(value) for key, value in toolchain.items()})

        slots = document.get("slots", {})
        if not isinstance(slots, dict):
            raise ValueError("Config field 'slots' must be a JSON object.")
        for slot, combo in self.slot_combos.items():
            card_id = slots.get(slot, "empty")
            index = combo.findData(card_id)
            if index < 0:
                index = combo.findData("empty")
            combo.setCurrentIndex(index if index >= 0 else 0)

        slot_options = document.get("slot_options", {})
        if not isinstance(slot_options, dict):
            raise ValueError("Config field 'slot_options' must be a JSON object.")
        self.detail_options = {
            str(slot): {str(option_id): str(value) for option_id, value in options.items()}
            for slot, options in slot_options.items()
            if isinstance(options, dict)
        }
        self.rebuild_details()

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
            "xZohm Project Wizard\n\nEarly PyQt sketch for configuring UltraZohm and MicroZohm projects.",
        )

    def export_tcl(self) -> None:
        OUTPUT_DIR.mkdir(parents=True, exist_ok=True)
        default_path = OUTPUT_DIR / "xzohm_project_wizard_config.tcl"
        path_text, _ = QFileDialog.getSaveFileName(self, "Export TCL", str(default_path), "TCL files (*.tcl)")
        if not path_text:
            return
        path = Path(path_text)
        path.write_text(
            self.generator.generate(
                self.selected_platform(),
                self.assignments(),
                self.option_values(),
                self.cpld_assignments(),
                self.axi_config(),
            ),
            encoding="utf-8",
        )
        QMessageBox.information(self, "TCL exported", f"Wrote {path}")
