from __future__ import annotations

import csv
from dataclasses import dataclass, field, fields
from pathlib import Path
from typing import ClassVar

import pandas as pd

ParameterValue = float | str


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
    additional_parameters: dict[str, ParameterValue] = field(default_factory=dict)

    C_PARAMETER_NAMES: ClassVar[tuple[str, ...]] = ()

    @classmethod
    def from_csv(cls, csv_path: str | Path) -> "PMSMParameters":
        csv_path = Path(csv_path)
        values = cls._read_key_value_csv(csv_path)
        c_values: dict[str, float | None] = {}
        additional_parameters: dict[str, ParameterValue] = {}
        for name, value in values.items():
            if name in cls.C_PARAMETER_NAMES:
                c_values[name] = float(value)
            else:
                additional_parameters[name] = cls._parse_additional_value(value)

        return cls(**c_values, additional_parameters=additional_parameters)

    def update(self, **values: ParameterValue) -> None:
        for name, value in values.items():
            if name in self.C_PARAMETER_NAMES:
                setattr(self, name, float(value))
            else:
                self.additional_parameters[name] = self._parse_additional_value(value)

    def to_dict(self, include_additional: bool = True) -> dict[str, ParameterValue | None]:
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

    @staticmethod
    def _parse_additional_value(value: object) -> ParameterValue:
        try:
            return float(value)
        except (TypeError, ValueError):
            return str(value)

    @staticmethod
    def _read_key_value_csv(csv_path: Path) -> dict[str, str]:
        rows: list[tuple[str, str]] = []
        with csv_path.open(newline="", encoding="utf-8") as csv_file:
            reader = csv.reader(csv_file)
            try:
                header = next(reader)
            except StopIteration as exc:
                raise ValueError(f"Empty parameter CSV: {csv_path}") from exc

            if header[:2] != ["parameter", "value"]:
                raise ValueError("Parameter CSV must start with the columns 'parameter,value'")

            for row in reader:
                if not row or all(cell.strip() == "" for cell in row):
                    break
                if len(row) != 2:
                    break
                rows.append((row[0].strip(), row[1].strip()))

        return dict(rows)


PMSMParameters.C_PARAMETER_NAMES = tuple(
    dataclass_field.name
    for dataclass_field in fields(PMSMParameters)
    if dataclass_field.name != "additional_parameters"
)
