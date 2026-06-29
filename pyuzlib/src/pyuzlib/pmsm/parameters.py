from __future__ import annotations

import csv
from dataclasses import dataclass, field, fields
from pathlib import Path
from typing import ClassVar

import pandas as pd

ParameterValue = float | int | str


@dataclass(frozen=True)
class CParameterField:
    name: str
    ctype: str


C_PARAMETER_TYPE_METADATA_KEY = "uz_pmsm_c_type"
SUPPORTED_C_PARAMETER_TYPES = ("float", "uint32_t")


def _c_parameter(*, ctype: str = "float"):
    return field(default=None, metadata={C_PARAMETER_TYPE_METADATA_KEY: ctype})


@dataclass
class PMSMParameters:
    """C-compatible PMSM machine parameters plus optional metadata."""

    machine_id: int | None = _c_parameter(ctype="uint32_t")
    R_ph_Ohm: float | None = _c_parameter()
    Ld_Henry: float | None = _c_parameter()
    Lq_Henry: float | None = _c_parameter()
    Psi_PM_Vs: float | None = _c_parameter()
    polePairs: float | None = _c_parameter()
    J_kg_m_squared: float | None = _c_parameter()
    I_max_Ampere: float | None = _c_parameter()
    I_rated_Ampere: float | None = _c_parameter()
    Torque_rated_Nm: float | None = _c_parameter()
    Torque_max_Nm: float | None = _c_parameter()
    Torque_min_Nm: float | None = _c_parameter()
    speed_rated_rpm: float | None = _c_parameter()
    speed_max_rpm: float | None = _c_parameter()
    speed_min_rpm: float | None = _c_parameter()
    V_dc_nominal_V: float | None = _c_parameter()
    I_d_max_A: float | None = _c_parameter()
    I_d_min_A: float | None = _c_parameter()
    I_q_max_A: float | None = _c_parameter()
    I_q_min_A: float | None = _c_parameter()
    additional_parameters: dict[str, ParameterValue] = field(default_factory=dict)

    C_PARAMETER_FIELDS: ClassVar[tuple[CParameterField, ...]] = ()
    C_PARAMETER_NAMES: ClassVar[tuple[str, ...]] = ()
    C_PARAMETER_TYPES: ClassVar[dict[str, str]] = {}

    @classmethod
    def from_csv(cls, csv_path: str | Path) -> "PMSMParameters":
        csv_path = Path(csv_path)
        values = cls._read_key_value_csv(csv_path)
        c_values: dict[str, float | int | None] = {}
        additional_parameters: dict[str, ParameterValue] = {}
        for name, value in values.items():
            if name in cls.C_PARAMETER_TYPES:
                c_values[name] = cls._parse_c_value(value, cls.C_PARAMETER_TYPES[name])
            else:
                additional_parameters[name] = cls._parse_additional_value(value)

        return cls(**c_values, additional_parameters=additional_parameters)

    def update(self, **values: ParameterValue) -> None:
        for name, value in values.items():
            if name in self.C_PARAMETER_TYPES:
                setattr(
                    self,
                    name,
                    self._parse_c_value(value, self.C_PARAMETER_TYPES[name]),
                )
            else:
                self.additional_parameters[name] = self._parse_additional_value(value)

    def to_dict(self, include_additional: bool = True) -> dict[str, ParameterValue | None]:
        values = {name: getattr(self, name) for name in self.C_PARAMETER_NAMES}
        if include_additional:
            values.update(self.additional_parameters)
        return values

    def to_c_dict(self) -> dict[str, float | int]:
        self.validate_for_c()
        return {
            field_spec.name: self._parse_c_value(
                getattr(self, field_spec.name),
                field_spec.ctype,
            )
            for field_spec in self.C_PARAMETER_FIELDS
        }

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

        checks = {
            "R_ph_Ohm": self.R_ph_Ohm > 0.0,
            "Ld_Henry": self.Ld_Henry > 0.0,
            "Lq_Henry": self.Lq_Henry > 0.0,
            "Psi_PM_Vs": self.Psi_PM_Vs >= 0.0,
            "polePairs": self.polePairs > 0.0 and self.polePairs % 1.0 == 0.0,
            "J_kg_m_squared": self.J_kg_m_squared > 0.0,
            "I_max_Ampere": self.I_max_Ampere > 0.0,
            "I_rated_Ampere": 0.0 < self.I_rated_Ampere <= self.I_max_Ampere,
            "Torque_rated_Nm": self.Torque_rated_Nm > 0.0,
            "Torque_max_Nm": self.Torque_max_Nm >= self.Torque_rated_Nm,
            "Torque_min_Nm": self.Torque_min_Nm <= 0.0 and self.Torque_min_Nm < self.Torque_max_Nm,
            "speed_rated_rpm": self.speed_rated_rpm > 0.0,
            "speed_max_rpm": self.speed_max_rpm >= self.speed_rated_rpm,
            "speed_min_rpm": self.speed_min_rpm <= 0.0 and self.speed_min_rpm < self.speed_max_rpm,
            "V_dc_nominal_V": self.V_dc_nominal_V > 0.0,
            "I_d_limits": self.I_d_max_A >= self.I_d_min_A,
            "I_q_limits": self.I_q_max_A >= self.I_q_min_A,
        }
        invalid = [name for name, is_valid in checks.items() if not is_valid]
        if invalid:
            raise ValueError(f"Invalid PMSM parameters for C implementation: {invalid}")

        invalid_type_values = [
            field_spec.name
            for field_spec in self.C_PARAMETER_FIELDS
            if not self._is_valid_c_value(
                getattr(self, field_spec.name),
                field_spec.ctype,
            )
        ]
        if invalid_type_values:
            raise ValueError(
                "Invalid PMSM parameter types for C implementation: "
                f"{invalid_type_values}"
            )

    @staticmethod
    def _parse_additional_value(value: object) -> ParameterValue:
        try:
            return float(value)
        except (TypeError, ValueError):
            return str(value)

    @staticmethod
    def _parse_c_value(value: object, ctype: str) -> float | int:
        if ctype == "float":
            return float(value)
        if ctype == "uint32_t":
            float_value = float(value)
            parsed_value = int(float_value)
            if float_value != parsed_value:
                raise ValueError(f"Cannot parse {value!r} as uint32_t")
            return parsed_value
        raise ValueError(f"Unsupported C parameter type: {ctype}")

    @staticmethod
    def _is_valid_c_value(value: object, ctype: str) -> bool:
        try:
            parsed_value = PMSMParameters._parse_c_value(value, ctype)
        except (TypeError, ValueError):
            return False
        if ctype == "uint32_t":
            return 0 <= parsed_value <= 0xFFFFFFFF
        return True

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


PMSMParameters.C_PARAMETER_FIELDS = tuple(
    CParameterField(
        name=dataclass_field.name,
        ctype=str(dataclass_field.metadata[C_PARAMETER_TYPE_METADATA_KEY]),
    )
    for dataclass_field in fields(PMSMParameters)
    if C_PARAMETER_TYPE_METADATA_KEY in dataclass_field.metadata
)
unsupported_c_parameter_types = [
    field_spec
    for field_spec in PMSMParameters.C_PARAMETER_FIELDS
    if field_spec.ctype not in SUPPORTED_C_PARAMETER_TYPES
]
if unsupported_c_parameter_types:
    raise ValueError(f"Unsupported PMSM C parameter fields: {unsupported_c_parameter_types}")

PMSMParameters.C_PARAMETER_NAMES = tuple(
    field_spec.name for field_spec in PMSMParameters.C_PARAMETER_FIELDS
)
PMSMParameters.C_PARAMETER_TYPES = {
    field_spec.name: field_spec.ctype for field_spec in PMSMParameters.C_PARAMETER_FIELDS
}
