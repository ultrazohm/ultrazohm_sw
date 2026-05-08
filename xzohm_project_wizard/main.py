from __future__ import annotations

import json
import re
import sys
from copy import deepcopy
from dataclasses import dataclass
from pathlib import Path
from typing import Any

try:
    from PyQt6.QtCore import Qt
    from PyQt6.QtGui import QAction, QFont
    from PyQt6.QtWidgets import (
        QApplication,
        QComboBox,
        QDialog,
        QDialogButtonBox,
        QFileDialog,
        QFormLayout,
        QGridLayout,
        QGroupBox,
        QHBoxLayout,
        QLabel,
        QLineEdit,
        QMainWindow,
        QMessageBox,
        QPushButton,
        QPlainTextEdit,
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
except ModuleNotFoundError as error:
    if error.name != "PyQt6":
        raise
    print("PyQt6 is not installed. Run: pip install -r requirements.txt", file=sys.stderr)
    raise SystemExit(1) from error


APP_DIR = Path(__file__).resolve().parent
DATA_FILE = APP_DIR / "data" / "adapter_cards.json"
PLATFORM_FILE = APP_DIR / "data" / "platforms.json"
OUTPUT_DIR = APP_DIR / "generated"
TEMPLATE_DIR = APP_DIR / "templates"
SLOTS = ["A1", "A2", "A3", "D1", "D2", "D3", "D4", "D5"]
DIGITAL_SLOTS = ["D1", "D2", "D3", "D4", "D5"]


@dataclass
class CardDatabase:
    path: Path
    document: dict[str, Any]

    @classmethod
    def load(cls, path: Path) -> "CardDatabase":
        with path.open("r", encoding="utf-8") as json_file:
            adapter_document = json.load(json_file)
        with PLATFORM_FILE.open("r", encoding="utf-8") as json_file:
            platform_document = json.load(json_file)
        document = dict(adapter_document)
        document["platforms"] = platform_document.get("platforms", [])
        document["axi_interconnect"] = platform_document.get("axi_interconnect", {})
        return cls(path=path, document=document)

    @property
    def cards(self) -> list[dict[str, Any]]:
        return self.document.setdefault("cards", [])

    @property
    def platforms(self) -> list[dict[str, Any]]:
        return self.document.setdefault("platforms", [])

    @property
    def cpld_programs(self) -> list[dict[str, Any]]:
        return self.document.setdefault("cpld_programs", [])

    @property
    def axi_interconnect(self) -> dict[str, Any]:
        return self.document.setdefault("axi_interconnect", {})

    def save(self) -> None:
        adapter_document = {
            "schema_version": self.document.get("schema_version", 1),
            "cpld_programs": self.cpld_programs,
            "cards": self.cards,
        }
        self.path.parent.mkdir(parents=True, exist_ok=True)
        with self.path.open("w", encoding="utf-8") as json_file:
            json.dump(adapter_document, json_file, indent=2)
            json_file.write("\n")

    def card_by_id(self, card_id: str) -> dict[str, Any] | None:
        return next((card for card in self.cards if card.get("id") == card_id), None)

    def platform_by_id(self, platform_id: str) -> dict[str, Any] | None:
        return next((platform for platform in self.platforms if platform.get("id") == platform_id), None)

    def cpld_program_by_id(self, program_id: str) -> dict[str, Any] | None:
        return next((program for program in self.cpld_programs if program.get("id") == program_id), None)

    def cards_for_slot(self, slot: str) -> list[dict[str, Any]]:
        compatible = []
        for card in self.cards:
            if slot in card.get("compatible_slots", []):
                compatible.append(card)
        return compatible

    def add_card(self, card: dict[str, Any]) -> None:
        if self.card_by_id(card["id"]) is not None:
            raise ValueError(f"Card id already exists: {card['id']}")
        self.cards.append(card)
        self.cards.sort(key=lambda item: item.get("name", "").lower())
        self.save()

    def update_card(self, original_id: str, updated_card: dict[str, Any]) -> None:
        updated_id = updated_card["id"]
        for index, card in enumerate(self.cards):
            if card.get("id") != original_id and card.get("id") == updated_id:
                raise ValueError(f"Card id already exists: {updated_id}")
            if card.get("id") == original_id:
                self.cards[index] = updated_card
                self.cards.sort(key=lambda item: item.get("name", "").lower())
                self.save()
                return
        raise ValueError(f"Card id not found: {original_id}")


class SimpleTemplateRenderer:
    def render_file(self, relative_path: str, context: dict[str, Any]) -> str:
        path = (TEMPLATE_DIR / relative_path).resolve()
        if not self._is_relative_to(path, TEMPLATE_DIR.resolve()):
            raise ValueError(f"Template path is outside the template directory: {relative_path}")
        return self.render(path.read_text(encoding="utf-8"), context)

    def render(self, template: str, context: dict[str, Any]) -> str:
        return self._render_block(template, context)

    def _render_block(self, template: str, context: dict[str, Any]) -> str:
        template = self._render_for_blocks(template, context)
        template = self._render_if_blocks(template, context)
        return self._render_variables(template, context)

    def _render_for_blocks(self, template: str, context: dict[str, Any]) -> str:
        pattern = re.compile(r"{%\s*for\s+(\w+)\s+in\s+([\w.]+)\s*%}(.*?){%\s*endfor\s*%}", re.DOTALL)
        while True:
            match = pattern.search(template)
            if not match:
                return template
            item_name, list_name, body = match.groups()
            rendered = []
            for item in self._resolve(list_name, context) or []:
                child_context = dict(context)
                child_context[item_name] = item
                rendered.append(self._render_block(body, child_context))
            template = template[: match.start()] + "".join(rendered) + template[match.end() :]

    def _render_if_blocks(self, template: str, context: dict[str, Any]) -> str:
        pattern = re.compile(r"{%\s*if\s+([\w.]+)\s*%}(.*?){%\s*endif\s*%}", re.DOTALL)
        while True:
            match = pattern.search(template)
            if not match:
                return template
            name, body = match.groups()
            rendered = self._render_block(body, context) if self._resolve(name, context) else ""
            template = template[: match.start()] + rendered + template[match.end() :]

    def _render_variables(self, template: str, context: dict[str, Any]) -> str:
        pattern = re.compile(r"{{\s*([\w.]+)\s*}}")
        return pattern.sub(lambda match: str(self._resolve(match.group(1), context) or ""), template)

    def _resolve(self, name: str, context: dict[str, Any]) -> Any:
        value: Any = context
        for part in name.split("."):
            if isinstance(value, dict):
                value = value.get(part)
            else:
                value = getattr(value, part, None)
            if value is None:
                return None
        return value

    def _is_relative_to(self, path: Path, parent: Path) -> bool:
        try:
            path.relative_to(parent)
            return True
        except ValueError:
            return False


class TclGenerator:
    def __init__(self, database: CardDatabase) -> None:
        self.database = database
        self.renderer = SimpleTemplateRenderer()

    def generate(
        self,
        platform: dict[str, Any],
        assignments: dict[str, str],
        option_values: dict[str, dict[str, str]],
        cpld_assignments: dict[str, str],
        axi_config: dict[str, str],
    ) -> str:
        platform_id = platform.get("id", "")
        platform_name = platform.get("name", platform_id)
        platform_revision = platform.get("revision", "")
        configured_slots = [slot for slot, card_id in assignments.items() if card_id != "empty"]
        lines = [
            "# Auto-generated by xZohm Project Wizard.",
            "# Review before running in Vivado. This is an early scaffold.",
            "",
            self.renderer.render_file(
                "vivado_project_architecture.tcl",
                {
                    "platform_id": platform_id,
                    "platform_name": platform_name,
                    "platform_revision": platform_revision,
                    "configured_slots": [
                        {
                            "slot": slot,
                            "slot_lower": slot.lower(),
                        }
                        for slot in configured_slots
                    ],
                    "slot_cplds": [
                        {
                            "slot": slot,
                            "program_id": cpld_assignments.get(slot, "none"),
                            "program_name": (
                                self.database.cpld_program_by_id(cpld_assignments.get(slot, "none")) or {}
                            ).get("name", cpld_assignments.get(slot, "none")),
                        }
                        for slot in DIGITAL_SLOTS
                    ],
                },
            ),
        ]

        for slot in SLOTS:
            card_id = assignments.get(slot, "empty")
            card = self.database.card_by_id(card_id)
            if not card or card_id == "empty":
                lines.extend([f"# {slot}: empty", ""])
                continue
            lines.append(self._card_section(slot, card, option_values.get(slot, {})))

        lines.append(
            self.renderer.render_file(
                "axi_interconnect.tcl",
                self._axi_context(assignments, option_values, axi_config),
            )
        )

        lines.extend(
            [
                "# TODO: validate design and save block design.",
                "puts \"xZohm Project Wizard: TCL scaffold finished\"",
                "",
            ]
        )
        return "\n".join(lines)

    def _card_section(self, slot: str, card: dict[str, Any], option_values: dict[str, str]) -> str:
        slot_index = slot[1:]
        vivado = card.get("vivado", {})
        template = vivado.get("template", "cards/generic_card.tcl")
        section = [
            self.renderer.render_file(
                template,
                self._card_context(slot, slot_index, card),
            )
        ]

        for option in card.get("options", []):
            selected_choice = self._selected_choice(option, option_values)
            if selected_choice is None:
                continue
            section.append(self._option_section(slot, slot_index, option, selected_choice))

        return "\n".join(section)

    def _card_context(self, slot: str, slot_index: str, card: dict[str, Any]) -> dict[str, Any]:
        vivado = card.get("vivado", {})
        ip_cores = []
        for ip_core in vivado.get("ip_cores", []):
            instance_name = f"{ip_core.get('instance_prefix', 'ip')}_{slot.lower()}"
            ip_cores.append(
                {
                    "instance_name": instance_name,
                    "module": ip_core.get("module", ""),
                    "vlnv": ip_core.get("vlnv", ""),
                }
            )
        interfaces = []
        for interface in vivado.get("interfaces", []):
            interfaces.append(
                {
                    "name": interface.get("name_template", "{slot}").format(slot=slot, slot_index=slot_index),
                    "vlnv": interface.get("vlnv", ""),
                }
            )
        ports = []
        for port in vivado.get("ports", []):
            ports.append(
                {
                    "signal": port.get("signal", "signal"),
                    "direction": port.get("direction", "in"),
                    "pin": port.get("channel_1_pin", port.get("pin", "signal")).format(slot=slot, slot_index=slot_index),
                }
            )
        return {
            "slot": slot,
            "slot_lower": slot.lower(),
            "slot_index": slot_index,
            "card_id": card.get("id", ""),
            "card_name": card.get("name", card.get("id", "unknown card")),
            "notes": vivado.get("notes", []),
            "ip_cores": ip_cores,
            "interfaces": interfaces,
            "ports": ports,
            "driver": card.get("vitis", {}).get("driver", ""),
        }

    def _axi_context(
        self,
        assignments: dict[str, str],
        option_values: dict[str, dict[str, str]],
        axi_config: dict[str, str],
    ) -> dict[str, Any]:
        config = dict(self.database.axi_interconnect)
        config.update({key: value for key, value in axi_config.items() if value})
        axi_slots = []
        axi_connections = []
        for slot in DIGITAL_SLOTS:
            card = self.database.card_by_id(assignments.get(slot, "empty"))
            if not card:
                continue
            interfaces = self._axi_interfaces_for_card(slot, card, option_values.get(slot, {}))
            if not interfaces:
                continue
            for index, interface in enumerate(interfaces):
                interface["index"] = index
            local_name = config.get("local_smartconnect_name", "axi_smartconnect")
            axi_slots.append(
                {
                    "slot": slot,
                    "slot_lower": slot.lower(),
                    "adapter_hier_path": f"uz_digital_Adapter/{slot}_adapter",
                    "local_smartconnect_path": f"uz_digital_Adapter/{slot}_adapter/{local_name}",
                    "interface_count": len(interfaces),
                    "axi_interfaces": interfaces,
                }
            )
            for interface in interfaces:
                axi_connections.append(
                    {
                        "slot": slot,
                        "local_smartconnect_path": f"uz_digital_Adapter/{slot}_adapter/{local_name}",
                        "index": interface["index"],
                        "path": interface["path"],
                        "addr_seg": interface["addr_seg"],
                    }
                )
        return {
            "upstream_smartconnect": config.get("upstream_smartconnect", ""),
            "clock_pin": config.get("clock_pin", ""),
            "resetn_pin": config.get("resetn_pin", ""),
            "address_space": config.get("address_space", ""),
            "local_smartconnect_vlnv": config.get("local_smartconnect_vlnv", "xilinx.com:ip:smartconnect"),
            "has_axi": bool(axi_slots),
            "axi_slots": axi_slots,
            "axi_connections": axi_connections,
        }

    def _axi_interfaces_for_card(
        self,
        slot: str,
        card: dict[str, Any],
        option_values: dict[str, str],
    ) -> list[dict[str, str]]:
        slot_index = slot[1:]
        interfaces = self._format_axi_interfaces(slot, slot_index, card.get("vivado", {}).get("axi_interfaces", []))
        for option in card.get("options", []):
            selected_choice = self._selected_choice(option, option_values)
            if not selected_choice or selected_choice.get("id") == "none":
                continue
            interfaces.extend(
                self._format_axi_interfaces(
                    slot,
                    slot_index,
                    selected_choice.get("vivado", {}).get("axi_interfaces", []),
                    option_id=option.get("id", ""),
                    choice_id=selected_choice.get("id", ""),
                )
            )
        return interfaces

    def _format_axi_interfaces(
        self,
        slot: str,
        slot_index: str,
        interfaces: list[dict[str, Any]],
        option_id: str = "",
        choice_id: str = "",
    ) -> list[dict[str, str]]:
        formatted = []
        for interface in interfaces:
            context = {
                "slot": slot,
                "slot_lower": slot.lower(),
                "slot_index": slot_index,
                "option_id": option_id,
                "choice_id": choice_id,
            }
            formatted.append(
                {
                    "name": interface.get("name", "axi"),
                    "path": interface.get("path_template", "").format(**context),
                    "addr_seg": interface.get("addr_seg_template", "").format(**context),
                }
            )
        return formatted

    def _selected_choice(self, option: dict[str, Any], option_values: dict[str, str]) -> dict[str, Any] | None:
        selected_id = option_values.get(option.get("id", ""), option.get("default", ""))
        for choice in option.get("choices", []):
            if choice.get("id") == selected_id:
                return choice
        choices = option.get("choices", [])
        return choices[0] if choices else None

    def _option_section(
        self,
        slot: str,
        slot_index: str,
        option: dict[str, Any],
        choice: dict[str, Any],
    ) -> str:
        option_id = option.get("id", "option")
        choice_id = choice.get("id", "choice")
        vivado = choice.get("vivado", {})
        template = vivado.get("template", "cards/generic_card.tcl")
        if choice_id == "none":
            template = vivado.get("template", "cards/absolute_encoder_channel.tcl")
        suffix = f"{slot.lower()}_{option_id}"
        ip_cores = []
        for ip_core in vivado.get("ip_cores", []):
            instance_name = f"{ip_core.get('instance_prefix', 'ip')}_{suffix}"
            ip_cores.append(
                {
                    "instance_name": instance_name,
                    "module": ip_core.get("module", ""),
                    "vlnv": ip_core.get("vlnv", ""),
                }
            )

        ports = []
        for port in vivado.get("ports", []):
            ports.append(
                {
                    "signal": port.get("signal", "signal"),
                    "direction": port.get("direction", "in"),
                    "pin": port.get("pin", "signal").format(slot=slot, slot_index=slot_index),
                }
            )

        return self.renderer.render_file(
            template,
            {
                "slot": slot,
                "slot_lower": slot.lower(),
                "slot_index": slot_index,
                "option_id": option_id,
                "option_label": option.get("label", option_id),
                "choice_id": choice_id,
                "choice_label": choice.get("label", choice_id),
                "enabled": choice_id != "none",
                "ip_cores": ip_cores,
                "ports": ports,
                "driver": choice.get("vitis", {}).get("driver", ""),
            },
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
        self.ip_edit = QLineEdit()
        self.vlnv_edit = QLineEdit("user.org:user:module_name:1.0")
        self.driver_edit = QLineEdit()
        self.cpld_edit = QLineEdit("none")
        self.description_edit = QTextEdit()
        self.description_edit.setFixedHeight(90)
        self.vivado_edit = QPlainTextEdit()
        self.vivado_edit.setFixedHeight(150)
        self.options_edit = QPlainTextEdit()
        self.options_edit.setFixedHeight(150)

        form = QFormLayout()
        form.addRow("ID", self.id_edit)
        form.addRow("Name", self.name_edit)
        form.addRow("Family", self.family_edit)
        form.addRow("Compatible slots", self.slots_edit)
        form.addRow("IP module", self.ip_edit)
        form.addRow("IP VLNV", self.vlnv_edit)
        form.addRow("Vitis driver", self.driver_edit)
        form.addRow("Slot CPLD", self.cpld_edit)
        form.addRow("Description", self.description_edit)
        form.addRow("Vivado JSON", self.vivado_edit)
        form.addRow("Options JSON", self.options_edit)

        buttons = QDialogButtonBox(QDialogButtonBox.StandardButton.Save | QDialogButtonBox.StandardButton.Cancel)
        buttons.accepted.connect(self.accept)
        buttons.rejected.connect(self.reject)

        layout = QVBoxLayout(self)
        layout.addLayout(form)
        layout.addWidget(buttons)
        self.resize(720, 760)
        if card:
            self._load_card(card)

    def _load_card(self, card: dict[str, Any]) -> None:
        self.id_edit.setText(card.get("id", ""))
        self.name_edit.setText(card.get("name", ""))
        self.family_edit.setText(card.get("family", ""))
        self.slots_edit.setText(",".join(card.get("compatible_slots", [])))
        ip_cores = card.get("vivado", {}).get("ip_cores", [])
        first_ip = ip_cores[0] if ip_cores else {}
        self.ip_edit.setText(first_ip.get("module", ""))
        self.vlnv_edit.setText(first_ip.get("vlnv", ""))
        self.driver_edit.setText(card.get("vitis", {}).get("driver", ""))
        self.cpld_edit.setText(card.get("slot_cpld", "none"))
        self.description_edit.setPlainText(card.get("description", ""))
        self.vivado_edit.setPlainText(json.dumps(card.get("vivado", {}), indent=2))
        self.options_edit.setPlainText(json.dumps(card.get("options", []), indent=2))

    def card(self) -> dict[str, Any]:
        card_id = self.id_edit.text().strip()
        module = self.ip_edit.text().strip()
        vivado = self._json_field(self.vivado_edit, "Vivado JSON")
        options = self._json_field(self.options_edit, "Options JSON")
        if not isinstance(vivado, dict):
            raise ValueError("Vivado JSON must be a JSON object.")
        if not isinstance(options, list):
            raise ValueError("Options JSON must be a JSON array.")

        if not vivado:
            ip_cores = []
            if module:
                ip_cores.append(
                    {
                        "instance_prefix": module.lower(),
                        "module": module,
                        "vlnv": self.vlnv_edit.text().strip(),
                    }
                )
            vivado = {
                "notes": ["New card entry created from the GUI. Refine this JSON entry before relying on generated TCL."],
                "ip_cores": ip_cores,
                "interfaces": [],
                "ports": [],
            }

        slots = [slot.strip().upper() for slot in self.slots_edit.text().split(",") if slot.strip()]
        return {
            "id": card_id,
            "name": self.name_edit.text().strip() or card_id,
            "family": self.family_edit.text().strip(),
            "description": self.description_edit.toPlainText().strip(),
            "compatible_slots": slots,
            "slot_cpld": self.cpld_edit.text().strip() or "none",
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
        self.detail_combos: dict[tuple[str, str], QComboBox] = {}
        self.detail_options: dict[str, dict[str, str]] = {}

        self.stack = QStackedWidget()
        self.tree = self._build_navigation()
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
        tree.addTopLevelItem(platform)
        tree.addTopLevelItem(config)
        tree.addTopLevelItem(software_config)
        config.setExpanded(True)
        software_config.setExpanded(True)
        tree.setCurrentItem(platform)
        tree.currentItemChanged.connect(self._navigation_changed)
        return tree

    def _navigation_changed(self, current: QTreeWidgetItem | None) -> None:
        if not current:
            return
        page_by_name = {
            "Platform": 0,
            "Hardware configuration": 3,
            "Adapter cards": 1,
            "Slot CPLDs": 2,
            "AXI interconnect": 3,
            "Software configuration": 4,
            "General": 4,
            "IP core driver setup": 5,
        }
        self.stack.setCurrentIndex(page_by_name.get(current.text(0), 0))

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
        card = self.database.card_by_id(self.assignments().get(slot, "empty"))
        program_id = "none"
        if card:
            program_id = card.get("slot_cpld", "none")
        index = combo.findData(program_id)
        combo.blockSignals(True)
        combo.setCurrentIndex(index if index >= 0 else max(combo.findData("none"), 0))
        combo.blockSignals(False)

    def option_values(self) -> dict[str, dict[str, str]]:
        values: dict[str, dict[str, str]] = deepcopy(self.detail_options)
        for (slot, option_id), combo in self.detail_combos.items():
            values.setdefault(slot, {})[option_id] = combo.currentData() or ""
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
        self.stack.setCurrentIndex(0)
        self.tree.setCurrentItem(self.tree.topLevelItem(0))

    def show_adapter_cards(self) -> None:
        self.stack.setCurrentIndex(1)
        self.tree.setCurrentItem(self.tree.topLevelItem(1).child(1))

    def show_hardware_configuration(self) -> None:
        self.show_axi_interconnect()

    def show_slot_cplds(self) -> None:
        self.stack.setCurrentIndex(2)
        self.tree.setCurrentItem(self.tree.topLevelItem(1).child(2))

    def show_axi_interconnect(self) -> None:
        self.stack.setCurrentIndex(3)
        self.tree.setCurrentItem(self.tree.topLevelItem(1).child(0))

    def show_lattice_diamond_placeholder(self) -> None:
        message = QMessageBox(self)
        message.setWindowTitle("Lattice Diamond project file")
        message.setText('<span style="color: red;">To be implemented...</span>')
        message.setTextFormat(Qt.TextFormat.RichText)
        got_it = message.addButton("Got it", QMessageBox.ButtonRole.AcceptRole)
        message.setDefaultButton(got_it)
        message.exec()

    def show_card_database(self) -> None:
        self.stack.setCurrentIndex(6)

    def show_software_general(self) -> None:
        self.stack.setCurrentIndex(4)
        self.tree.setCurrentItem(self.tree.topLevelItem(2).child(0))

    def show_ip_core_driver_setup(self) -> None:
        self.stack.setCurrentIndex(5)
        self.tree.setCurrentItem(self.tree.topLevelItem(2).child(1))

    def rebuild_details(self) -> None:
        self._clear_details_layouts()
        self.detail_combos = {}
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
                    combo = QComboBox()
                    selected = self.detail_options.get(slot, {}).get(option.get("id", ""), option.get("default", ""))
                    for choice in option.get("choices", []):
                        combo.addItem(choice.get("label", choice.get("id", "")), choice.get("id", ""))
                    index = combo.findData(selected)
                    combo.setCurrentIndex(index if index >= 0 else 0)
                    key = (slot, option.get("id", ""))
                    self.detail_combos[key] = combo
                    combo.currentIndexChanged.connect(self._detail_option_changed)
                    form.addRow(option.get("label", option.get("id", "Option")), combo)
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
        return {
            "schema_version": 1,
            "platform": self.selected_platform().get("id", ""),
            "platform_revision": self.selected_platform().get("revision", ""),
            "slots": self.assignments(),
            "slot_options": self.option_values(),
            "slot_cplds": self.cpld_assignments(),
            "axi": self.axi_config(),
        }

    def load_config_document(self, document: dict[str, Any]) -> None:
        if not isinstance(document, dict):
            raise ValueError("Config must be a JSON object.")
        platform_id = document.get("platform", "")
        platform_index = self.platform_combo.findData(platform_id)
        if platform_index >= 0:
            self.platform_combo.setCurrentIndex(platform_index)
        platform_revision = str(document.get("platform_revision", ""))
        self.refresh_platform_revisions(platform_revision)

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


def main() -> int:
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    return app.exec()


if __name__ == "__main__":
    raise SystemExit(main())
