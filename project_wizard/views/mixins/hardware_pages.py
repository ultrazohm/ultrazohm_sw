from __future__ import annotations

import html
import json
import platform
import subprocess
import sys
import traceback
from pathlib import Path
from typing import Any

from PyQt6.QtCore import PYQT_VERSION_STR, QT_VERSION_STR, QProcess, Qt, QTimer
from PyQt6.QtGui import QColor, QFont, QPixmap, QTextCursor
from PyQt6.QtWidgets import (
    QApplication,
    QComboBox,
    QCheckBox,
    QFileDialog,
    QFormLayout,
    QFrame,
    QGridLayout,
    QGroupBox,
    QHBoxLayout,
    QLabel,
    QLineEdit,
    QMessageBox,
    QPlainTextEdit,
    QProgressDialog,
    QPushButton,
    QScrollArea,
    QSizePolicy,
    QSplitter,
    QTabWidget,
    QTextEdit,
    QTreeWidget,
    QTreeWidgetItem,
    QVBoxLayout,
    QWidget,
)

from ...models import SystemConfig
from ...paths import (
    APP_DIR,
    CPLD_CONFIG_DIR,
    DIGITAL_SLOTS,
    LOG_DIR,
    OUTPUT_DIR,
    SLOTS,
    USER_CONFIG_DIR,
    VIVADO_BD_CONFIG_DIR,
    VIVADO_RUN_SCRIPT_DIR,
)
from ...services.config_service import build_config_document
from ...services.cpld_programmer_service import generate_d_slot_xcf, read_cable_settings_from_xcf
from ...services.toolchain_service import TOOL_DEFINITIONS, detect_toolchain_executables
from ...services.vivado_service import clear_vivado_cache, vivado_cache_targets, write_vivado_run_wrapper
from ...theme import set_dark_mode
from ...version import __version__
from ..adapter_card_details import AdapterCardDetailsWidget


TIMING_CONTROL_WIDTH = 260


class HardwarePageMixin:
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
        hint = QLabel(
            "Select the Vivado project and block design that the generated TCL should target. "
            "TCL execution options are configured on the TCL generation page."
        )
        hint.setWordWrap(True)
        vivado_form.addRow("", hint)
        layout.addWidget(vivado_group)
        layout.addStretch(1)
        return page



    def _build_pwm_page(self) -> QWidget:
        page = QWidget()
        layout = QVBoxLayout(page)

        title = QLabel("PWM / Timing / Interrupts")
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title.setFont(title_font)
        layout.addWidget(title)

        sections = QHBoxLayout()

        pwm_2l_group = QGroupBox("2L PWM")
        pwm_2l_form = QFormLayout(pwm_2l_group)
        instances_2l = QComboBox()
        for count in range(1, 11):
            instances_2l.addItem(f"{count} instance" if count == 1 else f"{count} instances", str(count))
        instances_2l.currentIndexChanged.connect(lambda _index: self.pwm_hardware_selection_changed())
        self.pwm_combos["pwm_2l_instances"] = instances_2l
        pwm_2l_form.addRow("Instances", instances_2l)

        idle_error_behavior = QComboBox()
        idle_error_behavior.addItem("Set PWM half-bridge duty-cycle values", "set_duty_cycle")
        idle_error_behavior.addItem(
            "Set tristate enable and PWM half-bridge duty-cycle values",
            "tristate_with_duty_cycle",
        )
        idle_error_behavior.currentIndexChanged.connect(lambda _index: self.pwm_hardware_selection_changed())
        self.pwm_combos["pwm_2l_idle_error_behavior"] = idle_error_behavior
        pwm_2l_form.addRow("Idle/error gate behavior", idle_error_behavior)

        idle_error_duty_hb1 = QLineEdit()
        idle_error_duty_hb1.textChanged.connect(lambda _text: self.guarded_refresh_software_preview())
        self.hardware_fields["pwm_2l_idle_error_duty_hb1"] = idle_error_duty_hb1
        pwm_2l_form.addRow("Idle/error duty HB1", idle_error_duty_hb1)
        idle_error_duty_hb2 = QLineEdit()
        idle_error_duty_hb2.textChanged.connect(lambda _text: self.guarded_refresh_software_preview())
        self.hardware_fields["pwm_2l_idle_error_duty_hb2"] = idle_error_duty_hb2
        pwm_2l_form.addRow("Idle/error duty HB2", idle_error_duty_hb2)
        idle_error_duty_hb3 = QLineEdit()
        idle_error_duty_hb3.textChanged.connect(lambda _text: self.guarded_refresh_software_preview())
        self.hardware_fields["pwm_2l_idle_error_duty_hb3"] = idle_error_duty_hb3
        pwm_2l_form.addRow("Idle/error duty HB3", idle_error_duty_hb3)
        sections.addWidget(pwm_2l_group, 1)

        pwm_3l_group = QGroupBox("3L PWM")
        pwm_3l_form = QFormLayout(pwm_3l_group)
        instances_3l = QComboBox()
        instances_3l.addItem("1 instance", "1")
        instances_3l.currentIndexChanged.connect(lambda _index: self.pwm_hardware_selection_changed())
        self.pwm_combos["pwm_3l_instances"] = instances_3l
        pwm_3l_form.addRow("Instances", instances_3l)
        sections.addWidget(pwm_3l_group, 1)

        layout.addLayout(sections)
        timing_group = QGroupBox("Global PWM timing")
        timing_form = QFormLayout(timing_group)
        timing_form.addRow(
            "INTERRUPT_ISR_SOURCE_USER_CHOICE",
            self._hardware_timing_combo(
                "interrupt_isr_source",
                [
                    ("0: Interrupt_2L_max_min", "0U"),
                    ("1: Interrupt_2L_min", "1U"),
                    ("2: Interrupt_2L_max", "2U"),
                    ("3: Interrupt_3L_start_center", "3U"),
                    ("4: Interrupt_3L_start", "4U"),
                    ("5: Interrupt_3L_center", "5U"),
                ],
                "PWM interrupt source:\n"
                "0: Interrupt_2L_max_min\n"
                "1: Interrupt_2L_min\n"
                "2: Interrupt_2L_max\n"
                "3: Interrupt_3L_start_center\n"
                "4: Interrupt_3L_start\n"
                "5: Interrupt_3L_center\n\n"
                "If a 2L PWM trigger is selected, align uz_PWM_SS_2L_config_t.trigger_source.",
            ),
        )
        timing_form.addRow(
            "INTERRUPT_ISR_TRIGGER_ON_ADC_DATA_READY",
            self._hardware_timing_combo(
                "interrupt_isr_trigger_on_adc_data_ready",
                [
                    ("0: Selected PWM event", "0U"),
                    ("1: axi2tcm_write_done", "1U"),
                ],
                "ISR trigger mode:\n"
                "0: ISR triggers on the selected PWM event\n"
                "1: ISR triggers on axi2tcm_write_done after ADC data is in TCM",
            ),
        )
        timing_form.addRow(
            "INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE",
            self._hardware_timing_field(
                "interrupt_adc_to_isr_ratio",
                "ADC-to-ISR ratio:\n"
                "1U: Trigger the ADC/ISR_Control at every PWM event.\n"
                "NU: Trigger ADC/ISR_Control only every N-th PWM event.",
            ),
        )
        timing_form.addRow(
            "ADC_TRIGGER_DELAY_IN_US",
            self._hardware_timing_field(
                "adc_trigger_delay_us",
                "ADC trigger delay:\n"
                "Unit: microseconds\n"
                "Applies in both ISR trigger modes.\n"
                "Default 0.01f is a 10 ns delay.",
            ),
        )
        timing_form.addRow(
            "UZ_PWM_FREQUENCY",
            self._hardware_timing_field("pwm_frequency", "Global PWM frequency used by generated PWM software configuration."),
        )
        timing_form.addRow(
            "UZ_PWM_DEADTIME_IN_US",
            self._hardware_timing_field("pwm_deadtime_us", "Global PWM deadtime in microseconds."),
        )
        timing_form.addRow(
            "UZ_PWM_MINIMUM_PULSE_WIDTH_IN_US",
            self._hardware_timing_field("pwm_min_pulse_width_us", "Global minimum PWM pulse width in microseconds."),
        )
        timing_hint = QLabel(
            "These values are written to uz_global_configuration.h. The PWM driver configs can reference the "
            "defines, so changing them here updates the project-wide PWM timing in one place."
        )
        timing_hint.setWordWrap(True)
        timing_form.addRow("", timing_hint)
        layout.addWidget(timing_group)

        enable_group = QGroupBox("Project-level enable")
        enable_form = QFormLayout(enable_group)
        enable_source = QLineEdit()
        enable_source.textChanged.connect(lambda _text: self.guarded_refresh_tcl_preview())
        self.hardware_fields["pwm_enable_source"] = enable_source
        enable_form.addRow("Enable_Gate source", enable_source)
        layout.addWidget(enable_group)
        hint = QLabel(
            "The wizard generates pwm_2L and pwm_3L inside an existing top-level uz_pwm hierarchy. "
            "Configure the number of PWM instances, and shared timing values here."
        )
        hint.setWordWrap(True)
        layout.addWidget(hint)
        layout.addStretch(1)
        return page



    def pwm_hardware_selection_changed(self) -> None:
        self.guarded_rebuild_details()
        self.guarded_refresh_tcl_preview()
        self.refresh_advanced_driver_config_options()
        self.guarded_refresh_software_preview()



    def _hardware_timing_field(self, key: str, help_text: str) -> QWidget:
        container = QWidget()
        layout = QHBoxLayout(container)
        layout.setContentsMargins(0, 0, 0, 0)
        field = QLineEdit()
        field.setFixedWidth(TIMING_CONTROL_WIDTH)
        field.textChanged.connect(lambda _text: self.guarded_refresh_software_preview())
        self.hardware_fields[key] = field
        help_button = QPushButton("?")
        help_button.setFixedWidth(28)
        help_button.setToolTip(help_text)
        help_button.clicked.connect(lambda: QMessageBox.information(self, "Timing define", help_text))
        layout.addWidget(field)
        layout.addWidget(help_button)
        layout.addStretch(1)
        return container



    def _hardware_timing_combo(self, key: str, items: list[tuple[str, str]], help_text: str) -> QWidget:
        container = QWidget()
        layout = QHBoxLayout(container)
        layout.setContentsMargins(0, 0, 0, 0)
        combo = QComboBox()
        combo.setFixedWidth(TIMING_CONTROL_WIDTH)
        for label, value in items:
            combo.addItem(label, value)
        combo.currentIndexChanged.connect(lambda _index: self.guarded_refresh_software_preview())
        self.pwm_combos[key] = combo
        help_button = QPushButton("?")
        help_button.setFixedWidth(28)
        help_button.setToolTip(help_text)
        help_button.clicked.connect(lambda: QMessageBox.information(self, "Timing define", help_text))
        layout.addWidget(combo)
        layout.addWidget(help_button)
        layout.addStretch(1)
        return container



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



    def _build_configuration_page(self) -> QWidget:
        page = QWidget()
        outer = QVBoxLayout(page)

        title = QLabel("Adapter Cards")
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title.setFont(title_font)
        outer.addWidget(title)

        controls = QWidget()
        controls_layout = QVBoxLayout(controls)

        content = QSplitter(Qt.Orientation.Horizontal)
        slot_group = self._build_slot_group()
        details_group = AdapterCardDetailsWidget(
            self.database,
            self.assignments,
            self.detail_options,
            self.hardware_config,
            self.adapter_detail_changed,
            lambda: self.is_loading_config,
        )
        self.adapter_details = details_group
        slot_group.setMaximumWidth(390)
        slot_group.setMinimumWidth(220)
        slot_group.setMinimumHeight(260)
        details_group.setMinimumHeight(260)
        content.addWidget(slot_group)
        content.addWidget(details_group)
        content.setStretchFactor(0, 0)
        content.setStretchFactor(1, 1)
        content.setSizes([340, 820])
        controls_layout.addWidget(content, 1)
        outer.addWidget(controls, 1)
        return page



    def _build_slot_group(self) -> QGroupBox:
        group = QGroupBox("Adapter card slots")
        grid = QGridLayout(group)
        grid.setColumnStretch(0, 0)
        grid.setColumnStretch(1, 1)
        grid.setRowStretch(len(SLOTS), 1)
        for row, slot in enumerate(SLOTS):
            label = QLabel(slot)
            label.setAlignment(Qt.AlignmentFlag.AlignRight | Qt.AlignmentFlag.AlignVCenter)
            label.setFixedWidth(24)
            combo = QComboBox()
            combo.setFixedHeight(24)
            combo.setMinimumWidth(0)
            combo.setMinimumContentsLength(24)
            combo.setSizeAdjustPolicy(QComboBox.SizeAdjustPolicy.AdjustToMinimumContentsLengthWithIcon)
            combo.setSizePolicy(QSizePolicy.Policy.Ignored, QSizePolicy.Policy.Fixed)
            self.slot_combos[slot] = combo
            self._fill_slot_combo(slot, combo)
            combo.currentIndexChanged.connect(lambda _index, selected_slot=slot: self.adapter_card_changed(selected_slot))
            grid.addWidget(label, row, 0)
            grid.addWidget(combo, row, 1)
        return group



    def _build_axi_interconnect_page(self) -> QWidget:
        page = QWidget()
        outer = QVBoxLayout(page)

        title = QLabel("ADC triggers")
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title.setFont(title_font)
        outer.addWidget(title)

        defaults = self.database.axi_interconnect
        tabs = QTabWidget()
        outer.addWidget(tabs, 1)

        def add_axi_field(form: QFormLayout, key: str, label: str, help_text: str | None = None) -> QLineEdit:
            edit = QLineEdit(str(defaults.get(key, "")))
            edit.textChanged.connect(self.refresh_tcl_preview)
            self.axi_fields[key] = edit
            if help_text is None:
                form.addRow(label, edit)
                return edit
            row = QWidget()
            row_layout = QHBoxLayout(row)
            row_layout.setContentsMargins(0, 0, 0, 0)
            help_button = QPushButton("?")
            help_button.setFixedWidth(28)
            help_button.clicked.connect(
                lambda _checked=False, title=label, text=help_text: QMessageBox.information(
                    self,
                    title,
                    text,
                )
            )
            row_layout.addWidget(edit, 1)
            row_layout.addWidget(help_button)
            form.addRow(label, row)
            return edit

        trigger_page = QWidget()
        trigger_layout = QVBoxLayout(trigger_page)
        analog_group = QGroupBox("A-slot analog trigger wiring")
        analog_form = QFormLayout(analog_group)
        analog_help = {
            "analog_axi2tcm_trigger_source": (
                "Normally this is one generated A-slot RAW_Valid pin. If the configured pin is not generated "
                "by the selected A-slot cards, the wizard falls back to the first generated RAW_Valid. "
                "For LTC2311 this is driven by RAW_VALID; for MAX11331 it is driven by new_data. "
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
            ("analog_axi2tcm_trigger_source", "AXI2TCM trigger source"),
            ("analog_axi2tcm_trigger_target", "AXI2TCM trigger target"),
            ("analog_conversion_trigger_sources", "Conversion trigger sources"),
            ("analog_conversion_trigger_target", "Conversion trigger target"),
        ]
        for key, label in analog_field_labels:
            add_axi_field(analog_form, key, label, analog_help[key])
        analog_hint = QLabel(
            "These settings define trigger wiring between generated A-slot analog signals, AXI2TCM, "
            "and the shared conversion trigger."
        )
        analog_hint.setWordWrap(True)
        analog_form.addRow("", analog_hint)
        trigger_layout.addWidget(analog_group)
        trigger_layout.addStretch(1)
        tabs.addTab(trigger_page, "ADC triggers")

        advanced_page = QWidget()
        advanced_layout = QVBoxLayout(advanced_page)
        advanced_fields: list[QLineEdit] = []
        advanced_enable = QCheckBox("Enable advanced AXI wiring edits")
        advanced_enable.setChecked(False)
        advanced_layout.addWidget(advanced_enable)

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
                advanced_fields.append(add_axi_field(attachment_form, key, label))
            advanced_layout.addWidget(attachment_group)

        add_attachment_group("A-slot project-level AXI attachment point", "a")
        add_attachment_group("D-slot project-level AXI attachment point", "d")

        local_group = QGroupBox("Local per adapter card slot AXI smartconnects")
        local_form = QFormLayout(local_group)
        local_field_labels = [
            ("local_smartconnect_vlnv", "Local SmartConnect VLNV"),
            ("local_smartconnect_name", "Local SmartConnect name"),
        ]
        for key, label in local_field_labels:
            advanced_fields.append(add_axi_field(local_form, key, label))
        advanced_layout.addWidget(local_group)
        advanced_hint = QLabel(
            "These values describe the existing UltraZohm block-design topology. They normally stay unchanged."
        )
        advanced_hint.setWordWrap(True)
        advanced_layout.addWidget(advanced_hint)
        advanced_layout.addStretch(1)
        for field in advanced_fields:
            field.setEnabled(False)
        advanced_enable.toggled.connect(lambda checked: [field.setEnabled(checked) for field in advanced_fields])
        tabs.addTab(advanced_page, "Advanced AXI wiring")
        return page
