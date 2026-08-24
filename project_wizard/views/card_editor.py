from __future__ import annotations

"""Unused draft adapter-card editor.

The production wizard keeps the adapter-card catalog read-only for v1. The
source of truth is `project_wizard/data/adapter_cards.json`, changed through the
developer workflow and verified with golden scenarios. This dialog is kept only
as a reference draft and must not be wired into the GUI without making it
schema-complete first.
"""

import json
from copy import deepcopy
from typing import Any

from PyQt6.QtWidgets import (
    QComboBox,
    QDialog,
    QDialogButtonBox,
    QFormLayout,
    QHBoxLayout,
    QLabel,
    QLineEdit,
    QMessageBox,
    QPushButton,
    QPlainTextEdit,
    QTableWidget,
    QTableWidgetItem,
    QTabWidget,
    QTextEdit,
    QVBoxLayout,
    QWidget,
)


class CardEditorDialog(QDialog):
    def __init__(self, parent: QWidget | None = None, card: dict[str, Any] | None = None) -> None:
        super().__init__(parent)
        self.setWindowTitle("Edit adapter card" if card else "Add adapter card")
        self.original_card = deepcopy(card) if card else None
        self.id_edit = QLineEdit()
        self.name_edit = QLineEdit()
        self.family_edit = QLineEdit("digital")
        self.slots_edit = QLineEdit("D1,D2,D3,D4")
        self.driver_edit = QLineEdit()
        self.cpld_edit = QLineEdit("none")
        self.cpld_by_slot_edit = QPlainTextEdit()
        self.cpld_by_slot_edit.setFixedHeight(90)
        self.description_edit = QTextEdit()
        self.description_edit.setFixedHeight(110)
        self.notes_edit = QPlainTextEdit()
        self.notes_edit.setFixedHeight(90)
        self.constraint_disable_edit = QLineEdit("Digital_{slot}_packed.xdc")
        self.constraint_enable_edit = QLineEdit("Digital_AdapterBoard_{slot}.xdc")
        self.options_data: list[dict[str, Any]] = []
        self.current_option_index: int | None = None
        self.current_choice_index: int | None = None
        self.loading_option_editor = False
        self.option_combo = QComboBox()
        self.choice_combo = QComboBox()
        self.option_id_edit = QLineEdit()
        self.option_label_edit = QLineEdit()
        self.option_default_edit = QLineEdit()
        self.choice_id_edit = QLineEdit()
        self.choice_label_edit = QLineEdit()
        self.choice_driver_edit = QLineEdit()
        self.choice_outputs_edit = QPlainTextEdit()
        self.choice_outputs_edit.setFixedHeight(90)
        self.ip_table = self._table(["instance_name", "instance_prefix", "module", "vlnv", "clock_pins", "reset_pins"])
        self.port_table = self._table(["signal", "ip_pin", "direction", "pin", "adapter_pin_name_template", "boundary_name_template"])
        self.trigger_table = self._table(["signal", "ip_pin", "default_source", "adapter_pin_name_template", "boundary_name_template"])
        self.axi_table = self._table(["name", "path_template", "addr_seg_template"])
        self.choice_ip_table = self._table(["instance_name", "instance_prefix", "module", "vlnv", "clock_pins", "reset_pins"])
        self.choice_port_table = self._table(["signal", "ip_pin", "direction", "pin", "adapter_pin_name_template", "boundary_name_template"])
        self.choice_trigger_table = self._table(["signal", "ip_pin", "default_source", "adapter_pin_name_template", "boundary_name_template"])
        self.choice_axi_table = self._table(["name", "path_template", "addr_seg_template"])
        self.vivado_edit = QPlainTextEdit()
        self.vivado_edit.setFixedHeight(260)
        self.options_edit = QPlainTextEdit()
        self.options_edit.setFixedHeight(260)

        tabs = QTabWidget()
        tabs.addTab(self._general_tab(), "General")
        tabs.addTab(self._table_tab(self.ip_table), "IP cores")
        tabs.addTab(self._table_tab(self.port_table), "External pins")
        tabs.addTab(self._table_tab(self.trigger_table), "Triggers")
        tabs.addTab(self._table_tab(self.axi_table), "AXI")
        tabs.addTab(self._constraints_tab(), "Constraints")
        tabs.addTab(self._option_choice_tab(), "Option choices")
        tabs.addTab(self._options_tab(), "Options/channels")
        tabs.addTab(self._advanced_tab(), "Advanced JSON")

        buttons = QDialogButtonBox(QDialogButtonBox.StandardButton.Save | QDialogButtonBox.StandardButton.Cancel)
        buttons.accepted.connect(self.accept)
        buttons.rejected.connect(self.reject)

        layout = QVBoxLayout(self)
        layout.addWidget(tabs)
        layout.addWidget(buttons)
        self.resize(1000, 760)
        if card:
            self._load_card(card)
        else:
            self._add_table_row(self.ip_table, {"vlnv": "user.org:user:module_name:1.0"})
            self._refresh_option_combos()

    def _general_tab(self) -> QWidget:
        page = QWidget()
        form = QFormLayout(page)
        form.addRow("ID", self.id_edit)
        form.addRow("Name", self.name_edit)
        form.addRow("Family", self.family_edit)
        form.addRow("Compatible slots", self.slots_edit)
        form.addRow("Slot CPLD", self.cpld_edit)
        form.addRow("Slot CPLD by slot JSON", self.cpld_by_slot_edit)
        form.addRow("Vitis driver", self.driver_edit)
        form.addRow("Description", self.description_edit)
        form.addRow("Notes", self.notes_edit)
        return page

    def _constraints_tab(self) -> QWidget:
        page = QWidget()
        form = QFormLayout(page)
        form.addRow("Disable XDC", self.constraint_disable_edit)
        form.addRow("Enable XDC", self.constraint_enable_edit)
        return page

    def _advanced_tab(self) -> QWidget:
        page = QWidget()
        layout = QVBoxLayout(page)
        layout.addWidget(QLabel("Vivado JSON"))
        layout.addWidget(self.vivado_edit)
        return page

    def _options_tab(self) -> QWidget:
        page = QWidget()
        layout = QVBoxLayout(page)
        apply_button = QPushButton("Apply JSON to structured editor")
        apply_button.clicked.connect(self._load_options_from_json)
        layout.addWidget(apply_button)
        layout.addWidget(QLabel("Options JSON"))
        layout.addWidget(self.options_edit)
        return page

    def _option_choice_tab(self) -> QWidget:
        page = QWidget()
        layout = QVBoxLayout(page)

        selectors = QHBoxLayout()
        selectors.addWidget(QLabel("Option"))
        selectors.addWidget(self.option_combo)
        add_option = QPushButton("Add option")
        remove_option = QPushButton("Remove option")
        selectors.addWidget(add_option)
        selectors.addWidget(remove_option)
        selectors.addWidget(QLabel("Choice"))
        selectors.addWidget(self.choice_combo)
        add_choice = QPushButton("Add choice")
        remove_choice = QPushButton("Remove choice")
        selectors.addWidget(add_choice)
        selectors.addWidget(remove_choice)
        selectors.addStretch()
        layout.addLayout(selectors)

        option_form = QFormLayout()
        option_form.addRow("Option ID", self.option_id_edit)
        option_form.addRow("Option label", self.option_label_edit)
        option_form.addRow("Default choice", self.option_default_edit)
        layout.addLayout(option_form)

        choice_form = QFormLayout()
        choice_form.addRow("Choice ID", self.choice_id_edit)
        choice_form.addRow("Choice label", self.choice_label_edit)
        choice_form.addRow("Vitis driver", self.choice_driver_edit)
        choice_form.addRow("Exposed outputs", self.choice_outputs_edit)
        layout.addLayout(choice_form)

        nested_tabs = QTabWidget()
        nested_tabs.addTab(self._table_tab(self.choice_ip_table), "IP cores")
        nested_tabs.addTab(self._table_tab(self.choice_port_table), "External pins")
        nested_tabs.addTab(self._table_tab(self.choice_trigger_table), "Triggers")
        nested_tabs.addTab(self._table_tab(self.choice_axi_table), "AXI")
        layout.addWidget(nested_tabs)

        self.option_combo.currentIndexChanged.connect(self._option_selection_changed)
        self.choice_combo.currentIndexChanged.connect(self._choice_selection_changed)
        add_option.clicked.connect(self._add_option)
        remove_option.clicked.connect(self._remove_option)
        add_choice.clicked.connect(self._add_choice)
        remove_choice.clicked.connect(self._remove_choice)
        return page

    def _table_tab(self, table: QTableWidget) -> QWidget:
        page = QWidget()
        layout = QVBoxLayout(page)
        layout.addWidget(table)
        buttons = QHBoxLayout()
        add_button = QPushButton("Add row")
        remove_button = QPushButton("Remove selected")
        add_button.clicked.connect(lambda: self._add_table_row(table))
        remove_button.clicked.connect(lambda: self._remove_selected_rows(table))
        buttons.addWidget(add_button)
        buttons.addWidget(remove_button)
        buttons.addStretch()
        layout.addLayout(buttons)
        return page

    def _table(self, headers: list[str]) -> QTableWidget:
        table = QTableWidget(0, len(headers))
        table.setHorizontalHeaderLabels(headers)
        table.setAlternatingRowColors(True)
        table.setMinimumHeight(440)
        return table

    def _add_table_row(self, table: QTableWidget, values: dict[str, Any] | None = None) -> None:
        values = values or {}
        row = table.rowCount()
        table.insertRow(row)
        for column in range(table.columnCount()):
            key = table.horizontalHeaderItem(column).text()
            value = values.get(key, "")
            if isinstance(value, list):
                value = ", ".join(str(item) for item in value)
            table.setItem(row, column, QTableWidgetItem(str(value)))

    def _remove_selected_rows(self, table: QTableWidget) -> None:
        rows = sorted({index.row() for index in table.selectedIndexes()}, reverse=True)
        for row in rows:
            table.removeRow(row)

    def _fill_table(self, table: QTableWidget, rows: list[dict[str, Any]]) -> None:
        table.setRowCount(0)
        for row in rows:
            self._add_table_row(table, row)
        table.resizeColumnsToContents()

    def _table_rows(self, table: QTableWidget, list_fields: set[str] | None = None) -> list[dict[str, Any]]:
        list_fields = list_fields or set()
        rows = []
        for row in range(table.rowCount()):
            item: dict[str, Any] = {}
            for column in range(table.columnCount()):
                key = table.horizontalHeaderItem(column).text()
                cell = table.item(row, column)
                value = cell.text().strip() if cell else ""
                if not value:
                    continue
                if key in list_fields:
                    item[key] = [part.strip() for part in value.split(",") if part.strip()]
                else:
                    item[key] = value
            if item:
                rows.append(item)
        return rows

    def _sync_option_choice_editor(self) -> None:
        if self.loading_option_editor:
            return
        if self.current_option_index is None or self.current_option_index >= len(self.options_data):
            return
        option = self.options_data[self.current_option_index]
        option["id"] = self.option_id_edit.text().strip() or option.get("id", "option")
        option["label"] = self.option_label_edit.text().strip() or option.get("label", option["id"])
        option["default"] = self.option_default_edit.text().strip()

        choices = option.setdefault("choices", [])
        if self.current_choice_index is None or self.current_choice_index >= len(choices):
            return
        choice = choices[self.current_choice_index]
        choice["id"] = self.choice_id_edit.text().strip() or choice.get("id", "choice")
        choice["label"] = self.choice_label_edit.text().strip() or choice.get("label", choice["id"])
        vivado = dict(choice.get("vivado", {}))
        vivado["template"] = vivado.get("template", "cards/generic_adapter_card.tcl")
        vivado["ip_cores"] = self._table_rows(self.choice_ip_table, {"clock_pins", "reset_pins"})
        vivado["ports"] = self._table_rows(self.choice_port_table)
        vivado["trigger_inputs"] = self._table_rows(self.choice_trigger_table)
        vivado["axi_interfaces"] = self._table_rows(self.choice_axi_table)
        outputs = []
        for line in self.choice_outputs_edit.toPlainText().replace(",", "\n").splitlines():
            value = line.strip()
            if value:
                outputs.append(value)
        vivado["outputs"] = outputs
        choice["vivado"] = vivado
        choice["vitis"] = {"driver": self.choice_driver_edit.text().strip()}

    def _refresh_option_combos(self) -> None:
        self.loading_option_editor = True
        self.option_combo.blockSignals(True)
        self.choice_combo.blockSignals(True)
        self.option_combo.clear()
        for option in self.options_data:
            self.option_combo.addItem(option.get("label") or option.get("id", "option"))
        if self.options_data:
            self.current_option_index = 0
            self.option_combo.setCurrentIndex(0)
        else:
            self.current_option_index = None
            self.current_choice_index = None
        self.option_combo.blockSignals(False)
        self.choice_combo.blockSignals(False)
        self.loading_option_editor = False
        self._refresh_choice_combo()
        self._load_selected_option_choice()

    def _refresh_choice_combo(self) -> None:
        self.loading_option_editor = True
        self.choice_combo.blockSignals(True)
        self.choice_combo.clear()
        if self.current_option_index is not None and self.current_option_index < len(self.options_data):
            for choice in self.options_data[self.current_option_index].get("choices", []):
                self.choice_combo.addItem(choice.get("label") or choice.get("id", "choice"))
        self.current_choice_index = 0 if self.choice_combo.count() else None
        if self.choice_combo.count():
            self.choice_combo.setCurrentIndex(0)
        self.choice_combo.blockSignals(False)
        self.loading_option_editor = False

    def _option_selection_changed(self, index: int) -> None:
        if self.loading_option_editor:
            return
        self._sync_option_choice_editor()
        self.current_option_index = index if index >= 0 else None
        self._refresh_choice_combo()
        self._load_selected_option_choice()

    def _choice_selection_changed(self, index: int) -> None:
        if self.loading_option_editor:
            return
        self._sync_option_choice_editor()
        self.current_choice_index = index if index >= 0 else None
        self._load_selected_option_choice()

    def _load_selected_option_choice(self) -> None:
        self.loading_option_editor = True
        if self.current_option_index is None or self.current_option_index >= len(self.options_data):
            self.option_id_edit.clear()
            self.option_label_edit.clear()
            self.option_default_edit.clear()
            self.choice_id_edit.clear()
            self.choice_label_edit.clear()
            self.choice_driver_edit.clear()
            self.choice_outputs_edit.clear()
            self._fill_table(self.choice_ip_table, [])
            self._fill_table(self.choice_port_table, [])
            self._fill_table(self.choice_trigger_table, [])
            self._fill_table(self.choice_axi_table, [])
            self.loading_option_editor = False
            return

        option = self.options_data[self.current_option_index]
        self.option_id_edit.setText(option.get("id", ""))
        self.option_label_edit.setText(option.get("label", ""))
        self.option_default_edit.setText(option.get("default", ""))
        choices = option.get("choices", [])
        if self.current_choice_index is None or self.current_choice_index >= len(choices):
            self.choice_id_edit.clear()
            self.choice_label_edit.clear()
            self.choice_driver_edit.clear()
            self.choice_outputs_edit.clear()
            self._fill_table(self.choice_ip_table, [])
            self._fill_table(self.choice_port_table, [])
            self._fill_table(self.choice_trigger_table, [])
            self._fill_table(self.choice_axi_table, [])
            self.loading_option_editor = False
            return

        choice = choices[self.current_choice_index]
        vivado = choice.get("vivado", {})
        self.choice_id_edit.setText(choice.get("id", ""))
        self.choice_label_edit.setText(choice.get("label", ""))
        self.choice_driver_edit.setText(choice.get("vitis", {}).get("driver", ""))
        self.choice_outputs_edit.setPlainText("\n".join(vivado.get("outputs", [])))
        self._fill_table(self.choice_ip_table, vivado.get("ip_cores", []))
        self._fill_table(self.choice_port_table, vivado.get("ports", []))
        self._fill_table(self.choice_trigger_table, vivado.get("trigger_inputs", []))
        self._fill_table(self.choice_axi_table, vivado.get("axi_interfaces", []))
        self.loading_option_editor = False

    def _add_option(self) -> None:
        self._sync_option_choice_editor()
        index = len(self.options_data) + 1
        self.options_data.append(
            {
                "id": f"channel_{index}",
                "label": f"Channel {index}",
                "default": "none",
                "choices": [
                    {
                        "id": "none",
                        "label": "Not used",
                        "vivado": {"template": "cards/generic_adapter_card.tcl", "ip_cores": [], "ports": []},
                    }
                ],
            }
        )
        self._refresh_option_combos()
        self.option_combo.setCurrentIndex(len(self.options_data) - 1)

    def _remove_option(self) -> None:
        if self.current_option_index is None or self.current_option_index >= len(self.options_data):
            return
        del self.options_data[self.current_option_index]
        self._refresh_option_combos()

    def _add_choice(self) -> None:
        self._sync_option_choice_editor()
        if self.current_option_index is None:
            self._add_option()
        if self.current_option_index is None:
            return
        option = self.options_data[self.current_option_index]
        choices = option.setdefault("choices", [])
        index = len(choices) + 1
        choices.append(
            {
                "id": f"choice_{index}",
                "label": f"Choice {index}",
                "vivado": {"template": "cards/generic_adapter_card.tcl", "ip_cores": [], "ports": []},
                "vitis": {"driver": ""},
            }
        )
        self._refresh_choice_combo()
        self.choice_combo.setCurrentIndex(len(choices) - 1)

    def _remove_choice(self) -> None:
        if self.current_option_index is None or self.current_option_index >= len(self.options_data):
            return
        option = self.options_data[self.current_option_index]
        choices = option.setdefault("choices", [])
        if self.current_choice_index is None or self.current_choice_index >= len(choices):
            return
        del choices[self.current_choice_index]
        self._refresh_choice_combo()
        self._load_selected_option_choice()

    def _load_options_from_json(self) -> None:
        options = self._json_field(self.options_edit, "Options JSON")
        if not isinstance(options, list):
            QMessageBox.warning(self, "Invalid options", "Options JSON must be a JSON array.")
            return
        self.options_data = deepcopy(options)
        self._refresh_option_combos()

    def _load_card(self, card: dict[str, Any]) -> None:
        vivado = card.get("vivado", {})
        self.id_edit.setText(card.get("id", ""))
        self.name_edit.setText(card.get("name", ""))
        self.family_edit.setText(card.get("family", ""))
        self.slots_edit.setText(",".join(card.get("compatible_slots", [])))
        self.driver_edit.setText(card.get("vitis", {}).get("driver", ""))
        self.cpld_edit.setText(card.get("slot_cpld", "none"))
        self.cpld_by_slot_edit.setPlainText(json.dumps(card.get("slot_cpld_by_slot", {}), indent=2))
        self.description_edit.setPlainText(card.get("description", ""))
        self.notes_edit.setPlainText("\n".join(vivado.get("notes", [])))
        constraints = vivado.get("constraints", {})
        self.constraint_disable_edit.setText(constraints.get("disable", "Digital_{slot}_packed.xdc"))
        self.constraint_enable_edit.setText(constraints.get("enable", "Digital_AdapterBoard_{slot}.xdc"))
        self._fill_table(self.ip_table, vivado.get("ip_cores", []))
        self._fill_table(self.port_table, vivado.get("ports", []))
        self._fill_table(self.trigger_table, vivado.get("trigger_inputs", []))
        self._fill_table(self.axi_table, vivado.get("axi_interfaces", []))
        self.vivado_edit.setPlainText(json.dumps(vivado, indent=2))
        self.options_data = deepcopy(card.get("options", []))
        self.options_edit.setPlainText(json.dumps(self.options_data, indent=2))
        self._refresh_option_combos()

    def card(self) -> dict[str, Any]:
        card_id = self.id_edit.text().strip()
        advanced_vivado = self._json_field(self.vivado_edit, "Vivado JSON")
        self._sync_option_choice_editor()
        self.options_edit.setPlainText(json.dumps(self.options_data, indent=2))
        options = self._json_field(self.options_edit, "Options JSON")
        if not isinstance(advanced_vivado, dict):
            raise ValueError("Vivado JSON must be a JSON object.")
        if not isinstance(options, list):
            raise ValueError("Options JSON must be a JSON array.")
        cpld_by_slot = self._json_field(self.cpld_by_slot_edit, "Slot CPLD by slot JSON")
        if not isinstance(cpld_by_slot, dict):
            raise ValueError("Slot CPLD by slot JSON must be a JSON object.")

        vivado = dict(advanced_vivado)
        vivado["template"] = vivado.get("template", "cards/generic_adapter_card.tcl")
        vivado["notes"] = [line.strip() for line in self.notes_edit.toPlainText().splitlines() if line.strip()]
        vivado["ip_cores"] = self._table_rows(self.ip_table, {"clock_pins", "reset_pins"})
        vivado["ports"] = self._table_rows(self.port_table)
        vivado["trigger_inputs"] = self._table_rows(self.trigger_table)
        vivado["axi_interfaces"] = self._table_rows(self.axi_table)
        vivado.setdefault("interfaces", [])
        vivado["constraints"] = {
            "disable": self.constraint_disable_edit.text().strip() or "Digital_{slot}_packed.xdc",
            "enable": self.constraint_enable_edit.text().strip() or "Digital_AdapterBoard_{slot}.xdc",
        }

        slots = [slot.strip().upper() for slot in self.slots_edit.text().split(",") if slot.strip()]
        return {
            "id": card_id,
            "name": self.name_edit.text().strip() or card_id,
            "family": self.family_edit.text().strip(),
            "description": self.description_edit.toPlainText().strip(),
            "compatible_slots": slots,
            "slot_cpld": self.cpld_edit.text().strip() or "none",
            "slot_cpld_by_slot": {str(slot).upper(): str(program) for slot, program in cpld_by_slot.items() if str(program).strip()},
            "vivado": vivado,
            "options": options,
            "vitis": {
                "driver": self.driver_edit.text().strip(),
                "notes": self.original_card.get("vitis", {}).get("notes", []) if self.original_card else [],
            },
        }

    def _json_field(self, editor: QPlainTextEdit, label: str) -> Any:
        text = editor.toPlainText().strip()
        if not text:
            return {} if label == "Vivado JSON" else []
        try:
            return json.loads(text)
        except json.JSONDecodeError as error:
            raise ValueError(f"{label} is not valid JSON: {error}") from error

    def accept(self) -> None:
        if not self.id_edit.text().strip():
            QMessageBox.warning(self, "Missing ID", "Please enter a stable card ID.")
            return
        try:
            self.card()
        except ValueError as error:
            QMessageBox.warning(self, "Invalid card", str(error))
            return
        super().accept()
