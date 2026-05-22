from __future__ import annotations

from ..repositories import CardDatabase


def default_cpld_for_card(database: CardDatabase, card_id: str, slot: str = "") -> str:
    card = database.card_by_id(card_id)
    if not card:
        return "none"
    by_slot = card.get("slot_cpld_by_slot", {})
    if isinstance(by_slot, dict) and slot:
        slot_program = by_slot.get(slot)
        if slot_program:
            return str(slot_program)
    return str(card.get("slot_cpld", "none") or "none")
