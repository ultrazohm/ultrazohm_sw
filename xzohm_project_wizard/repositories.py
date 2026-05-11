from __future__ import annotations

import json
from dataclasses import dataclass
from pathlib import Path
from typing import Any

from .paths import PLATFORM_FILE


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
