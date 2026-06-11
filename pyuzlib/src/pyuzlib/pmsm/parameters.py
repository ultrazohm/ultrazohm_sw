from __future__ import annotations

from dataclasses import dataclass, field
from pathlib import Path
from typing import ClassVar

import pandas as pd


@dataclass
class PMSMParameters:
    """C-compatible PMSM machine parameters plus optional metadata."""

    R_ph_Ohm: float | None = None
    Ld_Henry: float | None = None
    Lq_Henry: float | None = None
    Psi_PM_Vs: float | None = None
    polePairs: float | None = None
    J_kg_m_squared: float | None = None
    I_max_Ampere: float | None = None
    additional_parameters: dict[str, float] = field(default_factory=dict)

    C_PARAMETER_NAMES: ClassVar[tuple[str, ...]] = (
        "R_ph_Ohm",
        "Ld_Henry",
        "Lq_Henry",
        "Psi_PM_Vs",
        "polePairs",
        "J_kg_m_squared",
        "I_max_Ampere",
    )

    @classmethod
    def from_csv(cls, csv_path: str | Path) -> "PMSMParameters":
        csv_path = Path(csv_path)
        data = pd.read_csv(csv_path)
        required_columns = {"parameter", "value"}
        missing_columns = required_columns - set(data.columns)
        if missing_columns:
            raise ValueError(f"Missing parameter CSV columns: {sorted(missing_columns)}")

        values = dict(zip(data["parameter"], data["value"], strict=False))
        c_values: dict[str, float | None] = {}
        additional_parameters: dict[str, float] = {}
        for name, value in values.items():
            value = float(value)
            if name in cls.C_PARAMETER_NAMES:
                c_values[name] = value
            else:
                additional_parameters[name] = value

        return cls(**c_values, additional_parameters=additional_parameters)

    def update(self, **values: float) -> None:
        for name, value in values.items():
            if name in self.C_PARAMETER_NAMES:
                setattr(self, name, float(value))
            else:
                self.additional_parameters[name] = float(value)

    def to_dict(self, include_additional: bool = True) -> dict[str, float | None]:
        values = {name: getattr(self, name) for name in self.C_PARAMETER_NAMES}
        if include_additional:
            values.update(self.additional_parameters)
        return values

    def to_c_dict(self) -> dict[str, float]:
        self.validate_for_c()
        return {name: float(getattr(self, name)) for name in self.C_PARAMETER_NAMES}

    def to_csv(self, csv_path: str | Path, include_additional: bool = True) -> None:
        values = self.to_dict(include_additional=include_additional)
        data = pd.DataFrame(
            [
                {"parameter": name, "value": value}
                for name, value in values.items()
                if value is not None
            ]
        )
        data.to_csv(csv_path, index=False)

    def validate_for_c(self) -> None:
        missing = [name for name in self.C_PARAMETER_NAMES if getattr(self, name) is None]
        if missing:
            raise ValueError(f"Missing PMSM parameters required by C implementation: {missing}")

        assert self.R_ph_Ohm is not None
        assert self.Ld_Henry is not None
        assert self.Lq_Henry is not None
        assert self.Psi_PM_Vs is not None
        assert self.polePairs is not None
        assert self.J_kg_m_squared is not None
        assert self.I_max_Ampere is not None

        checks = {
            "R_ph_Ohm": self.R_ph_Ohm > 0.0,
            "Ld_Henry": self.Ld_Henry > 0.0,
            "Lq_Henry": self.Lq_Henry > 0.0,
            "Psi_PM_Vs": self.Psi_PM_Vs >= 0.0,
            "polePairs": self.polePairs > 0.0 and self.polePairs % 1.0 == 0.0,
            "J_kg_m_squared": self.J_kg_m_squared > 0.0,
            "I_max_Ampere": self.I_max_Ampere > 0.0,
        }
        invalid = [name for name, is_valid in checks.items() if not is_valid]
        if invalid:
            raise ValueError(f"Invalid PMSM parameters for C implementation: {invalid}")
