from __future__ import annotations

from typing import Any

from ..models import ResolvedOptionChoice, ResolvedSlot, ResolvedSystemModel, SystemConfig, ValidationIssue
from ..paths import SLOTS
from ..repositories import CardDatabase


class SystemResolver:
    def __init__(self, database: CardDatabase) -> None:
        self.database = database

    def resolve(self, config: SystemConfig) -> ResolvedSystemModel:
        platform = self.database.platform_by_id(config.platform)
        slots = [self._resolve_slot(slot_name, config) for slot_name in SLOTS]
        return ResolvedSystemModel(config=config, platform=platform, slots=slots)

    def validate(self, model: ResolvedSystemModel) -> list[ValidationIssue]:
        issues: list[ValidationIssue] = []
        if model.platform is None:
            issues.append(
                ValidationIssue(
                    severity="error",
                    code="PLATFORM_UNKNOWN",
                    message=f"Unknown platform: {model.config.platform}",
                    path="platform",
                )
            )
        for slot in model.slots:
            if slot.card is None and slot.card_id not in {"empty", "no_adapter_board"}:
                issues.append(
                    ValidationIssue(
                        severity="error",
                        code="CARD_UNKNOWN",
                        message=f"{slot.name} uses unknown adapter card '{slot.card_id}'.",
                        path=f"slots.{slot.name}",
                    )
                )
                continue
            if slot.card and slot.name not in slot.card.get("compatible_slots", []):
                issues.append(
                    ValidationIssue(
                        severity="error",
                        code="CARD_SLOT_INCOMPATIBLE",
                        message=f"{slot.card_id} is not compatible with {slot.name}.",
                        path=f"slots.{slot.name}",
                    )
                )
        return issues

    def _resolve_slot(self, slot_name: str, config: SystemConfig) -> ResolvedSlot:
        card_id = config.slots.get(slot_name, "empty")
        card = self.database.card_by_id(card_id)
        option_values = config.slot_options.get(slot_name, {})
        return ResolvedSlot(
            name=slot_name,
            card_id=card_id,
            card=card,
            option_values=option_values,
            options=self._resolve_options(card, option_values),
        )

    @staticmethod
    def _resolve_options(card: dict[str, Any] | None, option_values: dict[str, str]) -> list[ResolvedOptionChoice]:
        if not card:
            return []
        resolved = []
        for option in card.get("options", []):
            option_id = str(option.get("id", ""))
            selected_choice_id = option_values.get(option_id, str(option.get("default", "")))
            choice = next(
                (candidate for candidate in option.get("choices", []) if candidate.get("id") == selected_choice_id),
                None,
            )
            if choice is None and option.get("choices"):
                choice = option["choices"][0]
            if choice is None:
                continue
            resolved.append(
                ResolvedOptionChoice(
                    option_id=option_id,
                    choice_id=str(choice.get("id", "")),
                    option=option,
                    choice=choice,
                )
            )
        return resolved
