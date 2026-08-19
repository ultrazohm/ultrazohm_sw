from __future__ import annotations

import csv
import math
from collections.abc import Callable
from dataclasses import dataclass, field, fields
from pathlib import Path
from typing import ClassVar

import pandas as pd

ParameterValue = float | int | str

# Largest value representable in the single-precision C struct fields.
FLOAT32_MAX = 3.4028235e38


@dataclass(frozen=True)
class CParameterField:
    name: str
    ctype: str


@dataclass(frozen=True)
class ParameterConstraint:
    """One PMSM parameter constraint: machine-checkable rule plus the human-readable
    hint shown by the add_machine template generator. check is None for parameters
    without a value constraint (e.g. machine_id uniqueness is enforced by the
    catalog generator across all CSVs, not per file)."""

    name: str
    constraint: str
    description: str
    check: Callable[["PMSMParameters"], bool] | None


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
                try:
                    c_values[name] = cls._parse_c_value(value, cls.C_PARAMETER_TYPES[name])
                except (TypeError, ValueError) as exc:
                    raise ValueError(
                        f"Cannot parse value {value!r} for parameter {name!r}: {exc}"
                    ) from exc
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

        invalid = [
            constraint.name
            for constraint in PMSM_PARAMETER_CONSTRAINTS
            if constraint.check is not None and not constraint.check(self)
        ]
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
        return math.isfinite(parsed_value) and abs(parsed_value) <= FLOAT32_MAX

    @staticmethod
    def _read_key_value_csv(csv_path: Path) -> dict[str, str]:
        values: dict[str, str] = {}
        with csv_path.open(newline="", encoding="utf-8") as csv_file:
            reader = csv.reader(csv_file)
            try:
                header = next(reader)
            except StopIteration as exc:
                raise ValueError(f"Empty parameter CSV: {csv_path}") from exc

            if header[:2] != ["parameter", "value"]:
                raise ValueError("Parameter CSV must start with the columns 'parameter,value'")

            for row_number, row in enumerate(reader, start=2):
                if not row or all(cell.strip() == "" for cell in row):
                    # A blank line ends the parameter block; free-form tables appended
                    # below it are intentionally ignored.
                    break
                if len(row) != 2:
                    raise ValueError(
                        f"Malformed row {row_number} in {csv_path} "
                        f"(expected 'parameter,value'): {row!r}"
                    )
                name = row[0].strip()
                if name in values:
                    raise ValueError(f"Duplicate parameter {name!r} in {csv_path}")
                values[name] = row[1].strip()

        return values


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

# Single source of the per-parameter constraints: validate_for_c() evaluates the
# checks, and the add_machine template hints render the constraint/description
# strings. Keep in sync with uz_PMSM_config_assert in
# vitis/software/Baremetal/src/uz/uz_PMSM_config/uz_PMSM_config.c.
PMSM_PARAMETER_CONSTRAINTS: tuple[ParameterConstraint, ...] = (
    ParameterConstraint(
        "machine_id",
        "positive integer, unique across all motors",
        "stable ID reserved for future runtime machine selection",
        None,  # uniqueness is enforced across all CSVs by the catalog generator
    ),
    ParameterConstraint("R_ph_Ohm", "> 0", "phase resistance in Ohm",
                        lambda p: p.R_ph_Ohm > 0.0),
    ParameterConstraint("Ld_Henry", "> 0", "d-axis inductance in H",
                        lambda p: p.Ld_Henry > 0.0),
    ParameterConstraint("Lq_Henry", "> 0", "q-axis inductance in H",
                        lambda p: p.Lq_Henry > 0.0),
    ParameterConstraint("Psi_PM_Vs", ">= 0", "PM flux linkage in Vs",
                        lambda p: p.Psi_PM_Vs >= 0.0),
    ParameterConstraint("polePairs", "> 0, integer value", "e.g. 2, 4, 6",
                        lambda p: p.polePairs > 0.0 and p.polePairs % 1.0 == 0.0),
    ParameterConstraint("J_kg_m_squared", "> 0", "rotor inertia in kg·m²",
                        lambda p: p.J_kg_m_squared > 0.0),
    ParameterConstraint("I_max_Ampere", "> 0", "peak phase current in A",
                        lambda p: p.I_max_Ampere > 0.0),
    ParameterConstraint("I_rated_Ampere", "0 < value <= I_max_Ampere", "",
                        lambda p: 0.0 < p.I_rated_Ampere <= p.I_max_Ampere),
    ParameterConstraint("Torque_rated_Nm", "> 0", "",
                        lambda p: p.Torque_rated_Nm > 0.0),
    ParameterConstraint("Torque_max_Nm", ">= Torque_rated_Nm", "",
                        lambda p: p.Torque_max_Nm >= p.Torque_rated_Nm),
    ParameterConstraint("Torque_min_Nm", "<= 0, < Torque_max_Nm", "",
                        lambda p: p.Torque_min_Nm <= 0.0 and p.Torque_min_Nm < p.Torque_max_Nm),
    ParameterConstraint("speed_rated_rpm", "> 0", "",
                        lambda p: p.speed_rated_rpm > 0.0),
    ParameterConstraint("speed_max_rpm", ">= speed_rated_rpm", "",
                        lambda p: p.speed_max_rpm >= p.speed_rated_rpm),
    ParameterConstraint("speed_min_rpm", "<= 0, < speed_max_rpm", "",
                        lambda p: p.speed_min_rpm <= 0.0 and p.speed_min_rpm < p.speed_max_rpm),
    ParameterConstraint("V_dc_nominal_V", "> 0", "nominal DC-link voltage in V",
                        lambda p: p.V_dc_nominal_V > 0.0),
    ParameterConstraint("I_d_max_A", ">= I_d_min_A", "",
                        lambda p: p.I_d_max_A >= p.I_d_min_A),
    ParameterConstraint("I_d_min_A", "any float", "", None),
    ParameterConstraint("I_q_max_A", ">= I_q_min_A", "",
                        lambda p: p.I_q_max_A >= p.I_q_min_A),
    ParameterConstraint("I_q_min_A", "any float", "", None),
)
