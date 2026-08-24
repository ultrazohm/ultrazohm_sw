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


class ViewStateMixin:
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


    def guarded_rebuild_slot_details(self, slot: str) -> None:
        if not self.is_loading_config and self.adapter_details is not None:
            self.adapter_details.rebuild_slot(slot)


    def set_bulk_updates_enabled(self, enabled: bool) -> None:
        if not enabled:
            self.bulk_update_disable_depth += 1
        else:
            self.bulk_update_disable_depth = max(0, self.bulk_update_disable_depth - 1)
        if (not enabled and self.bulk_update_disable_depth > 1) or (enabled and self.bulk_update_disable_depth > 0):
            return
        widgets = [self.stack, self.adapter_details]
        for widget in widgets:
            if widget is not None:
                widget.setUpdatesEnabled(enabled)
                if enabled:
                    widget.update()


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


    def require_toolchain_paths(self, requirements: list[tuple[str, str, str]], title: str) -> bool:
        toolchain = self.toolchain_config()
        missing = []
        invalid = []
        for key, label, kind in requirements:
            path_text = toolchain.get(key, "").strip()
            if not path_text:
                missing.append(label)
                continue
            path = Path(path_text)
            if kind == "file" and not path.is_file():
                invalid.append(f"{label}: {path}")
            elif kind == "directory" and not path.is_dir():
                invalid.append(f"{label}: {path}")
        if not missing and not invalid:
            return True

        messages = []
        if missing:
            messages.append("Missing Toolchain page paths:")
            messages.extend(f"- {label}" for label in missing)
        if invalid:
            if messages:
                messages.append("")
            messages.append("Configured paths were not found:")
            messages.extend(f"- {entry}" for entry in invalid)
        messages.append("")
        messages.append("Open the Toolchain page, use Detect tools or Browse..., and try again.")
        QMessageBox.warning(self, title, "\n".join(messages))
        self.show_toolchain_page()
        return False


    def hardware_config(self) -> dict[str, str]:
        config = {key: field.text().strip() for key, field in self.hardware_fields.items()}
        for key, checkbox in self.hardware_checkboxes.items():
            config[key] = "true" if checkbox.isChecked() else "false"
        for key, combo in self.pwm_combos.items():
            config[key] = str(combo.currentData() or combo.currentText())
        for key, checkbox in self.pwm_checkboxes.items():
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
        for signal_id, (javascope_checkbox, slow_data_checkbox) in self.visualization_route_checkboxes.items():
            javascope_enabled = javascope_checkbox.isChecked()
            slow_data_enabled = slow_data_checkbox.isChecked()
            if javascope_enabled and slow_data_enabled:
                config[f"visualize_{signal_id}"] = "both"
            elif javascope_enabled:
                config[f"visualize_{signal_id}"] = "javascope"
            elif slow_data_enabled:
                config[f"visualize_{signal_id}"] = "slow_data"
        return config


    def sync_tcl_workflow_sections(self) -> None:
        local_checkbox = self.tcl_local_workflow_checkbox
        remote_checkbox = self.tcl_remote_workflow_checkbox
        local_content = self.tcl_local_workflow_content
        remote_content = self.tcl_remote_workflow_content
        if not local_checkbox or not remote_checkbox or not local_content or not remote_content:
            return

        if local_checkbox.isChecked() and remote_checkbox.isChecked():
            remote_checkbox.blockSignals(True)
            remote_checkbox.setChecked(False)
            remote_checkbox.blockSignals(False)
        elif not local_checkbox.isChecked() and not remote_checkbox.isChecked():
            local_checkbox.blockSignals(True)
            local_checkbox.setChecked(True)
            local_checkbox.blockSignals(False)

        local_content.setEnabled(local_checkbox.isChecked())
        remote_content.setEnabled(remote_checkbox.isChecked())


    def sync_tcl_disable_checkpoints_checkbox(self) -> None:
        local_checkbox = self.tcl_disable_checkpoints_checkbox
        remote_checkbox = self.tcl_remote_disable_checkpoints_checkbox
        if not local_checkbox or not remote_checkbox:
            return
        remote_checkbox.blockSignals(True)
        remote_checkbox.setChecked(local_checkbox.isChecked())
        remote_checkbox.blockSignals(False)


    def software_modes(self) -> dict[str, str]:
        return {slot: combo.currentData() or "follow_hardware" for slot, combo in self.software_mode_combos.items()}


    def software_presets(self) -> dict[str, str]:
        return {slot: combo.currentData() or "default" for slot, combo in self.software_preset_combos.items()}


    def selected_visualization_signals(self) -> dict[str, str]:
        selected: dict[str, str] = {}
        for signal_id, (javascope_checkbox, slow_data_checkbox) in self.visualization_route_checkboxes.items():
            javascope_enabled = javascope_checkbox.isChecked()
            slow_data_enabled = slow_data_checkbox.isChecked()
            if javascope_enabled and slow_data_enabled:
                selected[signal_id] = "both"
            elif javascope_enabled:
                selected[signal_id] = "javascope"
            elif slow_data_enabled:
                selected[signal_id] = "slow_data"
        return selected


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
        self.sync_tcl_workflow_sections()
        self.sync_tcl_disable_checkpoints_checkbox()
        for key, combo in self.pwm_combos.items():
            combo.blockSignals(True)
            value = values.get(key, defaults.get(key, ""))
            index = combo.findData(value)
            if index < 0:
                index = combo.findText(value)
            combo.setCurrentIndex(index if index >= 0 else 0)
            combo.blockSignals(False)
        for key, checkbox in self.pwm_checkboxes.items():
            checkbox.blockSignals(True)
            checkbox.setChecked(values.get(key, defaults.get(key, "false")).lower() in {"1", "true", "yes", "on"})
            checkbox.blockSignals(False)


    def reset_hardware_config(self) -> None:
        self.load_hardware_config({})


    def default_hardware_config(self) -> dict[str, str]:
        return {
            "vivado_project_file": str(APP_DIR.parent / "vivado" / "project" / "ultrazohm.xpr"),
            "block_design_name": "zusys",
            "tcl_workflow_local": "true",
            "tcl_workflow_remote": "false",
            "validate_block_design": "true",
            "save_block_design": "true",
            "open_vivado_gui": "false",
            "disable_bd_synth_checkpoints": "false",
            "generate_bitstream": "false",
            "export_xsa_after_build": "false",
            "pwm_2l_instances": "4",
            "pwm_2l_idle_error_behavior": "tristate_with_duty_cycle",
            "pwm_2l_idle_error_duty_hb1": "0.0f",
            "pwm_2l_idle_error_duty_hb2": "0.0f",
            "pwm_2l_idle_error_duty_hb3": "0.0f",
            "pwm_3l_instances": "1",
            "pwm_enable_source": "uz_system/Enable_Gate",
            "interrupt_isr_source": "1U",
            "interrupt_isr_trigger_on_adc_data_ready": "0U",
            "interrupt_adc_to_isr_ratio": "1U",
            "adc_trigger_delay_us": "0.01f",
            "pwm_frequency": "10.0e3f",
            "pwm_deadtime_us": "1.0f",
            "pwm_min_pulse_width_us": "0.5f",
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
            elif card_id == "uz_d_incremental_encoder":
                combo.addItem("Default Incremental Encoder", "default")
            elif card_id == "uz_d_resolver":
                combo.addItem("Default Resolver", "default")
            elif card_id == "uz_d_inverter_adapter":
                combo.addItem("Default Inverter Adapter", "default")
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
            self.resolved_system_model(refresh_dependent_views=False)
        )
        instances_by_slot: dict[str, list[Any]] = {slot: [] for slot in ["PWM", *SLOTS]}
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
            if instance.driver == "axi_gpio":
                hint = QLabel(
                    "Default generates Arduino-style helper functions with AXI_GPIO_SLOT_Dx, DIG_xx, LOW, and HIGH. "
                    "Custom keeps only the raw bitmask readout in Global_Data.av.io_card_dx_state."
                )
                hint.setWordWrap(True)
                hint.setStyleSheet("color: palette(mid);")
                group_layout.addWidget(hint)

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

            def apply_mode(
                _index: int,
                combo: QComboBox = mode_combo,
                widgets: list[QWidget] = field_widgets,
                refresh_preview: bool = True,
            ) -> None:
                editable = combo.currentData() == "custom"
                for widget in widgets:
                    widget.setEnabled(editable)
                apply_visibility()
                if refresh_preview:
                    self.guarded_refresh_software_preview()

            for choice_combo in choice_fields.values():
                choice_combo.currentIndexChanged.connect(
                    lambda _index, refresh=apply_visibility: (refresh(), self.guarded_refresh_software_preview())
                )
            mode_combo.currentIndexChanged.connect(apply_mode)
            apply_mode(mode_combo.currentIndex(), refresh_preview=False)
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
            selected = {}
            for key, value in values.items():
                if not key.startswith("visualize_"):
                    continue
                route = str(value).strip().lower()
                if route in {"javascope", "slow_data", "both"}:
                    selected[key.removeprefix("visualize_")] = route
        for layout in self.visualization_tab_layouts.values():
            for index in reversed(range(layout.count())):
                item = layout.itemAt(index)
                widget = item.widget()
                if widget is not None:
                    widget.setParent(None)
                else:
                    layout.removeItem(item)
        self.visualization_route_checkboxes.clear()

        signals = self.software_generator.visualization_signals(
            self.resolved_system_model(refresh_dependent_views=False)
        )
        signals_by_slot: dict[str, list[Any]] = {slot: [] for slot in SLOTS}
        for signal in signals:
            signals_by_slot.setdefault(signal.slot, []).append(signal)
        for signal in signals:
            slot_layout = self.visualization_tab_layouts.get(signal.slot)
            if slot_layout is None:
                continue
            row = QWidget()
            row_layout = QHBoxLayout(row)
            row_layout.setContentsMargins(0, 0, 0, 0)
            label = QLabel(signal.label)
            label.setWordWrap(True)
            selected_route = selected.get(signal.signal_id, "off")
            javascope_checkbox = QCheckBox("Javascope")
            slow_data_checkbox = QCheckBox("Slow data")
            javascope_checkbox.setChecked(selected_route in {"javascope", "both"})
            slow_data_checkbox.setChecked(selected_route in {"slow_data", "both"})
            javascope_checkbox.stateChanged.connect(lambda _state: self.guarded_refresh_software_preview())
            slow_data_checkbox.stateChanged.connect(lambda _state: self.guarded_refresh_software_preview())
            self.visualization_route_checkboxes[signal.signal_id] = (javascope_checkbox, slow_data_checkbox)
            row_layout.addWidget(label, 1)
            row_layout.addWidget(javascope_checkbox)
            row_layout.addWidget(slow_data_checkbox)
            slot_layout.addWidget(row)
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
        self.guarded_rebuild_slot_details(slot)
        if slot in DIGITAL_SLOTS:
            self.prefill_cpld_for_slot(slot)
        self.refresh_software_preset_options(refresh_dependent=False)
        values = self.software_config()
        self.refresh_advanced_driver_config_options(values)
        self.refresh_data_visualization_options(values, refresh_preview=False)
        self.software_dependent_views_dirty = False
        self.guarded_refresh_software_preview()
        self.guarded_refresh_tcl_preview()


    def adapter_detail_changed(self, slot: str | None, cpld_may_change: bool) -> None:
        self.software_dependent_views_dirty = True
        if cpld_may_change and slot in DIGITAL_SLOTS:
            card = self.database.card_by_id(self.assignments().get(slot, "empty"))
            if card and card.get("vivado", {}).get("io_card"):
                self.prefill_cpld_for_slot(slot)
                self.invalidate_cpld_project_file()
        if not self.is_loading_config:
            self.refresh_advanced_driver_config_options()
            self.refresh_data_visualization_options(refresh_preview=False)
            self.guarded_refresh_software_preview()
        self.guarded_refresh_tcl_preview()


    def software_driver_selection_changed(self) -> None:
        if self.is_loading_config:
            return
        values = self.software_config()
        self.refresh_advanced_driver_config_options(values)
        self.refresh_data_visualization_options(values, refresh_preview=False)
        self.software_dependent_views_dirty = False
        self.refresh_software_preview()


    def prefill_cpld_for_slot(self, slot: str) -> None:
        combo = self.cpld_combos.get(slot)
        if not combo:
            return
        resolved_slot = self.resolved_system_model(refresh_dependent_views=False).slot(slot)
        program_id = resolved_slot.default_cpld_program if resolved_slot else "none"
        index = combo.findData(program_id)
        combo.blockSignals(True)
        combo.setCurrentIndex(index if index >= 0 else max(combo.findData("none"), 0))
        combo.blockSignals(False)


    def option_values(self) -> dict[str, dict[str, str]]:
        if self.adapter_details is not None:
            self.adapter_details.sync_detail_options_from_widgets()
        assignments = self.assignments()
        values: dict[str, dict[str, str]] = {}
        for slot, options in self.detail_options.items():
            card = self.database.card_by_id(assignments.get(slot, "empty"))
            if not card:
                continue
            allowed_keys: set[str] = set()
            for option in card.get("options", []):
                option_id = option.get("id", "")
                if option_id:
                    allowed_keys.add(option_id)
                    allowed_keys.add(f"{option_id}_trigger_source")
            for source_field in card.get("vivado", {}).get("source_fields", []):
                field_id = source_field.get("id", "")
                if field_id:
                    allowed_keys.add(field_id)
            if card.get("vivado", {}).get("io_card"):
                for pin_index in range(30):
                    allowed_keys.add(f"io_pin_{pin_index:02d}_mode")
                    allowed_keys.add(f"io_pin_{pin_index:02d}_source")
                    allowed_keys.add(f"io_pin_{pin_index:02d}_constant")
                    allowed_keys.add(f"io_pin_{pin_index:02d}_pwm_instance")
                    allowed_keys.add(f"io_pin_{pin_index:02d}_pwm_pin")
            filtered = {key: value for key, value in options.items() if key in allowed_keys}
            if filtered:
                values[slot] = filtered
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
        self.refresh_platform_nameplate_visibility()
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
        self.refresh_platform_nameplate_visibility()
        self.refresh_platform_cpld_visibility()


    def refresh_platform_nameplate_visibility(self) -> None:
        if not self.platform_nameplate_group:
            return
        self.platform_nameplate_group.setVisible(self.platform_combo.currentData() == "ultrazohm")


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
