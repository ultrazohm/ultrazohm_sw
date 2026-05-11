from __future__ import annotations

from ..repositories import CardDatabase


def default_cpld_for_card(database: CardDatabase, card_id: str) -> str:
    card = database.card_by_id(card_id)
    if not card:
        return "none"
    return str(card.get("slot_cpld", "none") or "none")
