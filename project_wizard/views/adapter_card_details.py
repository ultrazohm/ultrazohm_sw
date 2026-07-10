from __future__ import annotations

from typing import Any, Callable

from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import (
    QCheckBox,
    QComboBox,
    QFormLayout,
    QGridLayout,
    QGroupBox,
    QHBoxLayout,
    QLabel,
    QLineEdit,
    QScrollArea,
    QSizePolicy,
    QTabWidget,
    QVBoxLayout,
    QWidget,
)

from ..paths import DIGITAL_SLOTS, SLOTS
from ..repositories import CardDatabase
from ..services.software_generator_service import resolver_channel_count
from ..tcl_generator import TclGenerator


class AdapterCardDetailsWidget(QGroupBox):
    def __init__(
        self,
        database: CardDatabase,
        assignments: Callable[[], dict[str, str]],
        detail_options: dict[str, dict[str, str]],
        hardware_config: Callable[[], dict[str, str]],
        on_details_changed: Callable[[str | None, bool], None],
        is_loading_config: Callable[[], bool],
        parent: QWidget | None = None,
    ) -> None:
        super().__init__("Selected card details", parent)
        self.database = database
        self.assignments = assignments
        self.detail_options = detail_options
        self.hardware_config = hardware_config
        self.on_details_changed = on_details_changed
        self.is_loading_config = is_loading_config
        self.update_disable_depth = 0

        self.detail_combos: dict[tuple[str, str], QComboBox] = {}
        self.detail_checkboxes: dict[tuple[str, str], QCheckBox] = {}
        self.detail_trigger_edits: dict[tuple[str, str], QLineEdit] = {}
        self.detail_source_edits: dict[tuple[str, str], QLineEdit | QComboBox] = {}
        self.io_pin_rows: dict[tuple[str, str], dict[str, QWidget]] = {}

        layout = QVBoxLayout(self)
        self.tabs = QTabWidget()
        self.tabs.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Expanding)
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
            self.tabs.addTab(scroll, slot)
        layout.addWidget(self.tabs, 1)

    def set_bulk_updates_enabled(self, enabled: bool) -> None:
        if not enabled:
            self.update_disable_depth += 1
        else:
            self.update_disable_depth = max(0, self.update_disable_depth - 1)
        if (not enabled and self.update_disable_depth > 1) or (enabled and self.update_disable_depth > 0):
            return
        self.tabs.setUpdatesEnabled(enabled)
        if enabled:
            self.tabs.update()

    def rebuild_all(self) -> None:
        self.set_bulk_updates_enabled(False)
        try:
            for slot in SLOTS:
                self._clear_slot(slot)
                self._build_slot(slot)
            self._prune_empty_slot_options()
        finally:
            self.set_bulk_updates_enabled(True)

    def rebuild_slot(self, slot: str) -> None:
        self.set_bulk_updates_enabled(False)
        try:
            self._clear_slot(slot)
            self._build_slot(slot)
            self._prune_empty_slot_options()
        finally:
            self.set_bulk_updates_enabled(True)

    def clear_runtime_widgets(self) -> None:
        self.detail_combos = {}
        self.detail_checkboxes = {}
        self.detail_trigger_edits = {}
        self.detail_source_edits = {}
        self.io_pin_rows = {}

    def sync_detail_options_from_widgets(self) -> None:
        for (slot, option_id), combo in self.detail_combos.items():
            self.detail_options.setdefault(slot, {})[option_id] = combo.currentData() or ""
            trigger_edit = self.detail_trigger_edits.get((slot, option_id))
            if trigger_edit:
                self.detail_options.setdefault(slot, {})[f"{option_id}_trigger_source"] = trigger_edit.text().strip()
        for (slot, option_id), checkbox in self.detail_checkboxes.items():
            self.detail_options.setdefault(slot, {})[option_id] = "true" if checkbox.isChecked() else "false"
        for (slot, field_id), edit in self.detail_source_edits.items():
            if isinstance(edit, QComboBox):
                self.detail_options.setdefault(slot, {})[field_id] = str(edit.currentData() or "")
            else:
                self.detail_options.setdefault(slot, {})[field_id] = edit.text().strip()

    def _clear_slot(self, slot: str) -> None:
        layout = self.slot_detail_layouts[slot]
        while layout.count() > 1:
            item = layout.takeAt(0)
            widget = item.widget()
            if widget:
                widget.deleteLater()
        for mapping in (
            self.detail_combos,
            self.detail_checkboxes,
            self.detail_trigger_edits,
            self.detail_source_edits,
            self.io_pin_rows,
        ):
            for key in [key for key in mapping if key[0] == slot]:
                mapping.pop(key, None)

    def _build_slot(self, slot: str) -> None:
        assignments = self.assignments()
        card_id = assignments.get(slot, "empty")
        page_layout = self.slot_detail_layouts[slot]
        card = self.database.card_by_id(card_id)
        if not card or card_id == "empty":
            page_layout.insertWidget(page_layout.count() - 1, QLabel(f"{slot}: Empty slot"))
            return

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

        self._add_card_options(slot, card_id, card, group_layout)
        self._add_source_fields(slot, card_id, card, group_layout)

        if card.get("vivado", {}).get("io_card"):
            group_layout.addWidget(self._build_io_card_pin_group(slot, card))

        page_layout.insertWidget(page_layout.count() - 1, group)

    def _add_card_options(self, slot: str, card_id: str, card: dict[str, Any], group_layout: QVBoxLayout) -> None:
        if not card.get("options"):
            return
        form = QFormLayout()
        for option in card.get("options", []):
            option_id = option.get("id", "")
            resolver_channel = option.get("resolver_channel")
            if card_id == "uz_d_resolver" and resolver_channel:
                try:
                    if int(resolver_channel) > resolver_channel_count(slot):
                        continue
                except (TypeError, ValueError):
                    pass
            if option.get("input") == "checkbox":
                selected = str(
                    self.detail_options.get(slot, {}).get(option_id, option.get("default", "false"))
                ).strip().lower()
                checkbox = QCheckBox(option.get("text", "Enabled"))
                checkbox.setChecked(selected in {"1", "true", "yes", "on"})
                if option.get("tooltip") or option.get("help"):
                    checkbox.setToolTip(option.get("tooltip", option.get("help", "")))
                key = (slot, option_id)
                self.detail_checkboxes[key] = checkbox
                checkbox.stateChanged.connect(self._detail_option_changed)
                form.addRow(option.get("label", option_id or "Option"), checkbox)
                continue

            combo = QComboBox()
            selected = self.detail_options.get(slot, {}).get(option_id, option.get("default", ""))
            for choice in option.get("choices", []):
                combo.addItem(choice.get("label", choice.get("id", "")), choice.get("id", ""))
            index = combo.findData(selected)
            combo.setCurrentIndex(index if index >= 0 else 0)
            key = (slot, option_id)
            self.detail_combos[key] = combo
            combo.currentIndexChanged.connect(self._detail_option_changed)

            if option.get("show_trigger_source", True):
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
            else:
                form.addRow(option.get("label", option_id or "Option"), combo)
        group_layout.addLayout(form)

    def _add_source_fields(self, slot: str, card_id: str, card: dict[str, Any], group_layout: QVBoxLayout) -> None:
        source_fields = card.get("vivado", {}).get("source_fields", [])
        if not source_fields:
            return
        source_group = QGroupBox("Vivado source signals")
        source_layout = QFormLayout(source_group)
        for source_field in source_fields:
            field_id = source_field.get("id", "")
            if not field_id:
                continue
            resolver_channel = source_field.get("resolver_channel")
            if card_id == "uz_d_resolver" and resolver_channel:
                try:
                    if int(resolver_channel) > resolver_channel_count(slot):
                        continue
                except (TypeError, ValueError):
                    pass
            value = self.detail_options.get(slot, {}).get(field_id, source_field.get("default", ""))
            edit = QLineEdit(value)
            edit.setPlaceholderText(source_field.get("placeholder", "Block design pin path"))
            if source_field.get("tooltip") or source_field.get("help"):
                edit.setToolTip(source_field.get("tooltip", source_field.get("help", "")))
            edit.editingFinished.connect(self._detail_option_changed)
            self.detail_source_edits[(slot, field_id)] = edit
            source_layout.addRow(source_field.get("label", field_id), edit)
        group_layout.addWidget(source_group)

    def _build_io_card_pin_group(self, slot: str, card: dict[str, Any]) -> QGroupBox:
        group = QGroupBox("IO source and sink")
        layout = QVBoxLayout(group)
        hint = QLabel("TX pins drive the adapter board. RX pins read from the adapter board.")
        hint.setWordWrap(True)
        layout.addWidget(hint)

        directions = TclGenerator._io_card_directions(card.get("vivado", {}).get("io_card", {}), self.detail_options.get(slot, {}))
        summary = TclGenerator._io_card_context(slot, slot[1:], card, self.detail_options.get(slot, {})).get("io_summary", "")
        if summary:
            summary_label = QLabel(summary)
            summary_label.setWordWrap(True)
            layout.addWidget(summary_label)

        for group_title, start_index, end_index in self._io_card_pin_group_ranges(card, directions):
            pin_group = QGroupBox(group_title)
            grid = QGridLayout(pin_group)
            grid.addWidget(QLabel("Pin"), 0, 0)
            grid.addWidget(QLabel("Direction"), 0, 1)
            grid.addWidget(QLabel("Mode"), 0, 2)
            grid.addWidget(QLabel("Signal"), 0, 3)
            grid.addWidget(QLabel("Constant value"), 0, 4)

            for row_index, pin_index in enumerate(range(start_index, end_index), start=1):
                self._add_io_card_pin_row(slot, pin_index, directions[pin_index], grid, row_index)
            layout.addWidget(pin_group)
        return group

    def _add_io_card_pin_row(
        self,
        slot: str,
        pin_index: int,
        physical_direction: str,
        grid: QGridLayout,
        row_index: int,
    ) -> None:
        pin_id = f"io_pin_{pin_index:02d}"
        pin_name = f"Dig_{pin_index:02d}_Ch{slot[1:]}"
        mode_combo = QComboBox()
        if physical_direction == "tx":
            mode_options = [
                ("axi_gpio", "AXI GPIO"),
                ("pwm", "PWM"),
                ("source_pin", "Custom BD source"),
                ("constant", "Constant"),
            ]
        else:
            mode_options = [
                ("axi_gpio", "AXI GPIO"),
                ("top_level", "Top-level port"),
            ]
        for value, label in mode_options:
            mode_combo.addItem(label, value)
        selected_mode = self.detail_options.get(slot, {}).get(f"{pin_id}_mode", "axi_gpio")
        mode_index = mode_combo.findData(selected_mode)
        mode_combo.setCurrentIndex(mode_index if mode_index >= 0 else 0)
        mode_combo.currentIndexChanged.connect(self._detail_option_changed)
        self.detail_combos[(slot, f"{pin_id}_mode")] = mode_combo

        signal_widget = QWidget()
        signal_layout = QHBoxLayout(signal_widget)
        signal_layout.setContentsMargins(0, 0, 0, 0)
        signal_layout.setSpacing(4)
        source_edit = QLineEdit(
            self.detail_options.get(slot, {}).get(
                f"{pin_id}_source",
                f"uz_pwm/pwm_2L/uz_interlockDeadtime_{pin_index // 6}/s{pin_index % 6}_out",
            )
        )
        source_edit.setPlaceholderText("Block design pin path, e.g. uz_digital_adapter/Dig_00_Ch2")
        source_edit.editingFinished.connect(self._detail_option_changed)
        self.detail_source_edits[(slot, f"{pin_id}_source")] = source_edit
        signal_layout.addWidget(source_edit, 1)

        pwm_instance_combo = QComboBox()
        for pwm_value, pwm_label in self._io_pwm_instance_choices():
            pwm_instance_combo.addItem(pwm_label, pwm_value)
        selected_pwm_instance = self.detail_options.get(slot, {}).get(f"{pin_id}_pwm_instance", self._default_io_pwm_instance(pin_index))
        pwm_instance_index = pwm_instance_combo.findData(selected_pwm_instance)
        pwm_instance_combo.setCurrentIndex(pwm_instance_index if pwm_instance_index >= 0 else 0)
        pwm_instance_combo.currentIndexChanged.connect(self._detail_option_changed)
        self.detail_source_edits[(slot, f"{pin_id}_pwm_instance")] = pwm_instance_combo
        signal_layout.addWidget(pwm_instance_combo, 1)

        pwm_pin_combo = QComboBox()
        for pwm_pin_value, pwm_pin_label in self._io_pwm_pin_choices(str(pwm_instance_combo.currentData() or "")):
            pwm_pin_combo.addItem(pwm_pin_label, pwm_pin_value)
        selected_pwm_pin = self.detail_options.get(slot, {}).get(f"{pin_id}_pwm_pin", f"s{pin_index % 6}_out")
        pwm_pin_index = pwm_pin_combo.findData(selected_pwm_pin)
        pwm_pin_combo.setCurrentIndex(pwm_pin_index if pwm_pin_index >= 0 else 0)
        pwm_pin_combo.currentIndexChanged.connect(self._detail_option_changed)
        self.detail_source_edits[(slot, f"{pin_id}_pwm_pin")] = pwm_pin_combo
        signal_layout.addWidget(pwm_pin_combo, 1)

        constant_combo = QComboBox()
        constant_combo.addItem("Low", "0")
        constant_combo.addItem("High", "1")
        selected_constant = "1" if self.detail_options.get(slot, {}).get(f"{pin_id}_constant", "0").strip().lower() in {"1", "true", "yes", "on"} else "0"
        constant_index = constant_combo.findData(selected_constant)
        constant_combo.setCurrentIndex(constant_index if constant_index >= 0 else 0)
        constant_combo.currentIndexChanged.connect(self._detail_option_changed)
        self.detail_source_edits[(slot, f"{pin_id}_constant")] = constant_combo

        current_mode = str(mode_combo.currentData() or "")
        self.io_pin_rows[(slot, pin_id)] = {
            "mode": mode_combo,
            "source": source_edit,
            "pwm_instance": pwm_instance_combo,
            "pwm_pin": pwm_pin_combo,
            "constant": constant_combo,
        }
        self._refresh_io_pin_row_state(slot, pin_id, current_mode)

        grid.addWidget(QLabel(pin_name), row_index, 0)
        grid.addWidget(self._io_direction_indicator(physical_direction), row_index, 1)
        grid.addWidget(mode_combo, row_index, 2)
        grid.addWidget(signal_widget, row_index, 3)
        grid.addWidget(constant_combo, row_index, 4)

    def _io_card_pin_group_ranges(self, card: dict[str, Any], directions: list[str]) -> list[tuple[str, int, int]]:
        io_card = card.get("vivado", {}).get("io_card", {})
        kind = str(io_card.get("kind", ""))
        if kind == "voltage_grouped":
            ranges: list[tuple[str, int, int]] = []
            start = 0
            groups = io_card.get("groups", [])
            for group_index, group_definition in enumerate(groups, start=1):
                width = TclGenerator._config_int(group_definition.get("width", 0), default=0, minimum=0, maximum=30)
                end = min(start + width, len(directions))
                if start >= end:
                    continue
                direction = directions[start].upper()
                ranges.append((f"Group {group_index}: Dig_{start:02d}..{end - 1:02d} {direction}", start, end))
                start = end
            return ranges or [("Pins", 0, len(directions))]
        ranges = []
        start = 0
        while start < len(directions):
            direction = directions[start]
            end = start + 1
            while end < len(directions) and directions[end] == direction:
                end += 1
            label = "TX pins" if direction == "tx" else "RX pins"
            ranges.append((f"{label}: Dig_{start:02d}..{end - 1:02d}", start, end))
            start = end
        return ranges

    def _io_direction_indicator(self, physical_direction: str) -> QWidget:
        widget = QWidget()
        layout = QHBoxLayout(widget)
        layout.setContentsMargins(0, 0, 0, 0)
        layout.setSpacing(4)
        for direction in ("TX", "RX"):
            active = physical_direction.upper() == direction
            label = QLabel(direction)
            label.setAlignment(Qt.AlignmentFlag.AlignCenter)
            label.setFixedWidth(28)
            if active:
                label.setStyleSheet("font-weight: 600; color: white; background: #2f6fed; border-radius: 3px; padding: 2px;")
            else:
                label.setStyleSheet("color: #777; border: 1px solid #bbb; border-radius: 3px; padding: 2px;")
            layout.addWidget(label)
        return widget

    def _io_pwm_instance_choices(self) -> list[tuple[str, str]]:
        choices: list[tuple[str, str]] = []
        hardware = self.hardware_config()
        try:
            pwm_2l_instances = max(0, int(hardware.get("pwm_2l_instances", "0")))
        except ValueError:
            pwm_2l_instances = 0
        try:
            pwm_3l_instances = max(0, int(hardware.get("pwm_3l_instances", "0")))
        except ValueError:
            pwm_3l_instances = 0
        choices.extend((f"pwm_2l_{index}", f"PWM_2L_{index}") for index in range(pwm_2l_instances))
        choices.extend((f"pwm_3l_{index}", f"PWM_3L_{index}") for index in range(pwm_3l_instances))
        return choices or [("pwm_2l_0", "PWM_2L_0")]

    def _default_io_pwm_instance(self, pin_index: int) -> str:
        choices = self._io_pwm_instance_choices()
        preferred = f"pwm_2l_{pin_index // 6}"
        return preferred if any(value == preferred for value, _label in choices) else choices[0][0]

    @staticmethod
    def _io_pwm_pin_choices(pwm_instance: str) -> list[tuple[str, str]]:
        if pwm_instance.startswith("pwm_3l_"):
            return [(f"s{index}_out", f"s{index}_out") for index in range(12)]
        return [(f"s{index}_out", f"s{index}_out") for index in range(6)]

    def _refresh_io_pin_row_state(self, slot: str, pin_id: str, mode: str | None = None) -> None:
        row = self.io_pin_rows.get((slot, pin_id))
        if not row:
            return
        mode_combo = row.get("mode")
        if mode is None and isinstance(mode_combo, QComboBox):
            mode = str(mode_combo.currentData() or "")
        mode = mode or ""
        source_edit = row.get("source")
        pwm_instance_combo = row.get("pwm_instance")
        pwm_pin_combo = row.get("pwm_pin")
        constant_combo = row.get("constant")
        if source_edit is not None:
            source_edit.setVisible(mode == "source_pin")
            source_edit.setEnabled(mode == "source_pin")
        if pwm_instance_combo is not None:
            pwm_instance_combo.setVisible(mode == "pwm")
            pwm_instance_combo.setEnabled(mode == "pwm")
        if pwm_pin_combo is not None:
            pwm_pin_combo.setVisible(mode == "pwm")
            pwm_pin_combo.setEnabled(mode == "pwm")
        if constant_combo is not None:
            constant_combo.setVisible(mode == "constant")
            constant_combo.setEnabled(mode == "constant")

    def _refresh_io_pwm_pin_choices(self, slot: str, pin_id: str) -> None:
        row = self.io_pin_rows.get((slot, pin_id))
        if not row:
            return
        pwm_instance_combo = row.get("pwm_instance")
        pwm_pin_combo = row.get("pwm_pin")
        if not isinstance(pwm_instance_combo, QComboBox) or not isinstance(pwm_pin_combo, QComboBox):
            return
        selected_pin = str(pwm_pin_combo.currentData() or "")
        choices = self._io_pwm_pin_choices(str(pwm_instance_combo.currentData() or ""))
        pwm_pin_combo.blockSignals(True)
        pwm_pin_combo.clear()
        for value, label in choices:
            pwm_pin_combo.addItem(label, value)
        index = pwm_pin_combo.findData(selected_pin)
        pwm_pin_combo.setCurrentIndex(index if index >= 0 else 0)
        pwm_pin_combo.blockSignals(False)
        self.detail_options.setdefault(slot, {})[f"{pin_id}_pwm_pin"] = str(pwm_pin_combo.currentData() or "")

    def _detail_option_changed(self) -> None:
        changed_widget = self.sender()
        rebuild_slot: str | None = None
        cpld_may_change = False
        changed_slot: str | None = None
        changed_pin_id: str | None = None
        changed_pwm_instance_slot: str | None = None
        changed_pwm_instance_pin_id: str | None = None

        for (slot, option_id), combo in self.detail_combos.items():
            self.detail_options.setdefault(slot, {})[option_id] = combo.currentData() or ""
            if combo is changed_widget:
                changed_slot = slot
                if option_id in {"optical_variant", "rs422_variant", "io_variant"} or option_id.startswith("direction_group_"):
                    rebuild_slot = slot
                    cpld_may_change = True
                elif option_id.startswith("io_pin_") and option_id.endswith("_mode"):
                    changed_pin_id = option_id.removesuffix("_mode")
                    self._refresh_io_pin_row_state(slot, changed_pin_id, str(combo.currentData() or ""))
            trigger_edit = self.detail_trigger_edits.get((slot, option_id))
            if trigger_edit:
                trigger_edit.setEnabled(combo.currentData() != "none")
                self.detail_options.setdefault(slot, {})[f"{option_id}_trigger_source"] = trigger_edit.text().strip()

        for (slot, option_id), checkbox in self.detail_checkboxes.items():
            self.detail_options.setdefault(slot, {})[option_id] = "true" if checkbox.isChecked() else "false"

        for (slot, field_id), edit in self.detail_source_edits.items():
            if isinstance(edit, QComboBox):
                self.detail_options.setdefault(slot, {})[field_id] = str(edit.currentData() or "")
                if edit is changed_widget and field_id.startswith("io_pin_") and field_id.endswith("_pwm_instance"):
                    changed_slot = slot
                    changed_pwm_instance_slot = slot
                    changed_pwm_instance_pin_id = field_id.removesuffix("_pwm_instance")
            else:
                self.detail_options.setdefault(slot, {})[field_id] = edit.text().strip()

        if changed_pwm_instance_slot and changed_pwm_instance_pin_id:
            self._refresh_io_pwm_pin_choices(changed_pwm_instance_slot, changed_pwm_instance_pin_id)
            self._refresh_io_pin_row_state(changed_pwm_instance_slot, changed_pwm_instance_pin_id)

        if rebuild_slot and not self.is_loading_config():
            self.rebuild_slot(rebuild_slot)
        self.on_details_changed(changed_slot, cpld_may_change)

    def _prune_empty_slot_options(self) -> None:
        assignments = self.assignments()
        for slot in list(self.detail_options):
            if assignments.get(slot, "empty") == "empty":
                self.detail_options.pop(slot, None)
