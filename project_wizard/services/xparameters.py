from __future__ import annotations

import re
from functools import lru_cache
from pathlib import Path


def resolve_base_address_macro(
    source_dir: Path,
    slot: str,
    interface: str,
    channel: int | None = None,
    search_xparameters: bool = True,
) -> tuple[str, str]:
    slot_lower = slot.lower()
    if interface == "temperature":
        fallback = f"XPAR_UZ_DIGITAL_ADAPTER_{slot.upper()}_ADAPTER_TEMPERATURE_CARD_INT_0_BASEADDR"
        search_terms = ["TEMP", "TEMPERATURE"]
    elif interface == "adc_ltc2311":
        fallback = f"XPAR_UZ_ANALOG_ADAPTER_{slot.upper()}_ADAPTER_{slot.upper()}_ADC_LTC2311_S00_AXI_BASEADDR"
        search_terms = ["ADC_LTC2311", "ADCLTC2311", "LTC2311"]
    elif interface == "adc_max11331":
        fallback = f"XPAR_UZ_ANALOG_ADAPTER_{slot.upper()}_ADAPTER_{slot.upper()}_ADC_MAX11331_BASEADDR"
        search_terms = ["ADC_MAX11331", "ADCMAX11331", "MAX11331"]
    elif interface == "dac8831":
        fallback = f"XPAR_UZ_ANALOG_ADAPTER_{slot.upper()}_ADAPTER_{slot.upper()}_DAC8831_BASEADDR"
        search_terms = ["DAC8831", "DAC_SPI", "DAC"]
    elif interface == "inverter_adapter":
        fallback = f"XPAR_UZ_DIGITAL_ADAPTER_{slot.upper()}_ADAPTER_UZ_D_INVERTER_ADAPTER_{slot.upper()}_BASEADDR"
        search_terms = ["INVERTER_ADAPTER", "UZ_D_INVERTER", "INVERTER"]
    elif interface == "incremental_encoder":
        if channel is None:
            fallback = f"XPAR_UZ_DIGITAL_ADAPTER_{slot.upper()}_ADAPTER_INCREMENTAL_ENCODER_{slot.upper()}_BASEADDR"
        else:
            fallback = f"XPAR_UZ_DIGITAL_ADAPTER_{slot.upper()}_ADAPTER_INCREMENTAL_ENCODER_{slot.upper()}_{channel}_BASEADDR"
        search_terms = ["INCREMENTAL_ENCODER", "INCREMENTAL", "ENCODER"]
    elif interface == "resolver_ip":
        fallback = f"XPAR_UZ_DIGITAL_ADAPTER_{slot.upper()}_ADAPTER_RESOLVER_IP_{slot.upper()}_{channel}_BASEADDR"
        search_terms = ["RESOLVER_IP", "RESOLVER_INTERFACE", "RESOLVER"]
    elif interface == "resolver_pl_interface":
        fallback = f"XPAR_UZ_DIGITAL_ADAPTER_{slot.upper()}_ADAPTER_RESOLVER_PL_INTERFACE_{slot.upper()}_{channel}_BASEADDR"
        search_terms = ["RESOLVER_PL_INTERFACE", "RESOLVER_PL"]
    elif interface == "endat":
        fallback = f"XPAR_UZ_DIGITAL_ADAPTER_{slot.upper()}_ADAPTER_UZ_ENDAT_INTERFACE_{slot.upper()}_CHANNEL_{channel}_BASEADDR"
        search_terms = ["ENDAT"]
    elif interface == "ssi":
        fallback = f"XPAR_UZ_DIGITAL_ADAPTER_{slot.upper()}_ADAPTER_UZ_SSI_INTERFACE_{slot.upper()}_CHANNEL_{channel}_BASEADDR"
        search_terms = ["SSI"]
    elif interface == "axi_gpio":
        fallback = f"XPAR_UZ_DIGITAL_ADAPTER_{slot.upper()}_ADAPTER_AXI_GPIO_{slot.upper()}_BASEADDR"
        search_terms = ["AXI_GPIO"]
    else:
        fallback = f"XPAR_{slot.upper()}_BASEADDR"
        search_terms = [interface.upper()]
    if not search_xparameters:
        return fallback, ""
    xparameters, macros = xparameter_baseaddr_macros(source_dir)
    if xparameters is None:
        return fallback, f"{slot}: xparameters.h not found. Using fallback base-address macro {fallback}."

    candidates = [
        macro
        for macro in macros
        if any(term in macro for term in search_terms)
    ]
    slot_candidates = [candidate for candidate in candidates if slot.upper() in candidate or slot_lower.upper() in candidate]
    if channel is not None:
        channel_markers = [
            f"CHANNEL_{channel}",
            f"_{slot.upper()}_{channel}_BASEADDR",
            f"_{channel}_BASEADDR",
        ]
        channel_candidates = [candidate for candidate in slot_candidates if any(marker in candidate for marker in channel_markers)]
        if channel_candidates:
            return channel_candidates[0], ""
        if interface == "incremental_encoder" and channel == 1:
            legacy_candidates = [candidate for candidate in slot_candidates if f"_{slot.upper()}_BASEADDR" in candidate]
            if legacy_candidates:
                return legacy_candidates[0], ""
        return fallback, f"{slot}: no channel {channel} {interface} BASEADDR macro found in {xparameters}. Using fallback {fallback}."
    if slot_candidates:
        return slot_candidates[0], ""
    if interface == "axi_gpio":
        return fallback, f"{slot}: no slot-specific {interface} BASEADDR macro found in {xparameters}. Using fallback {fallback}."
    if candidates:
        return candidates[0], f"{slot}: no slot-specific {interface} BASEADDR macro found. Using {candidates[0]} from {xparameters}."
    return fallback, f"{slot}: no {interface} BASEADDR macro found in {xparameters}. Using fallback {fallback}."


def resolve_device_id_macro(
    source_dir: Path,
    slot: str,
    interface: str,
    search_xparameters: bool = True,
) -> tuple[str, str]:
    if interface == "axi_gpio":
        fallback = f"XPAR_UZ_DIGITAL_ADAPTER_{slot.upper()}_ADAPTER_AXI_GPIO_{slot.upper()}_DEVICE_ID"
        search_terms = ["AXI_GPIO"]
    else:
        fallback = f"XPAR_{slot.upper()}_DEVICE_ID"
        search_terms = [interface.upper()]
    if not search_xparameters:
        return fallback, ""
    xparameters = find_xparameters(source_dir)
    if xparameters is None:
        return fallback, f"{slot}: xparameters.h not found. Using fallback device-id macro {fallback}."
    text = xparameters.read_text(encoding="utf-8", errors="ignore")
    macros = tuple(re.findall(r"^#define\s+(XPAR_[A-Z0-9_]*DEVICE_ID)\b", text, re.MULTILINE))
    candidates = [macro for macro in macros if any(term in macro for term in search_terms)]
    slot_candidates = [candidate for candidate in candidates if slot.upper() in candidate]
    if slot_candidates:
        return slot_candidates[0], ""
    if interface == "axi_gpio":
        return fallback, f"{slot}: no slot-specific {interface} DEVICE_ID macro found in {xparameters}. Using fallback {fallback}."
    if candidates:
        return candidates[0], f"{slot}: no slot-specific {interface} DEVICE_ID macro found. Using {candidates[0]} from {xparameters}."
    return fallback, f"{slot}: no {interface} DEVICE_ID macro found in {xparameters}. Using fallback {fallback}."


def resolve_pwm_base_address_macro(
    source_dir: Path, interface: str, index: int, search_xparameters: bool = True
) -> tuple[str, str]:
    if interface == "pwm_2l":
        fallback = f"XPAR_UZ_PWM_PWM_2L_PWM_AND_SS_CONTROL_V_{index}_BASEADDR"
        required_terms = ["UZ_PWM", "PWM_2L", "PWM_AND_SS_CONTROL_V"]
    elif interface == "deadtime_2l":
        fallback = f"XPAR_UZ_PWM_PWM_2L_UZ_INTERLOCKDEADTIME_{index}_BASEADDR"
        required_terms = ["UZ_PWM", "PWM_2L", "UZ_INTERLOCKDEADTIME"]
    elif interface == "pwm_3l":
        fallback = "XPAR_UZ_PWM_PWM_3L_PWM_SS_3L_IP_0_BASEADDR"
        required_terms = ["UZ_PWM", "PWM_3L", "PWM_SS_3L_IP"]
    else:
        fallback = f"XPAR_UZ_PWM_{interface.upper()}_{index}_BASEADDR"
        required_terms = ["UZ_PWM", interface.upper()]
    if not search_xparameters:
        return fallback, ""

    xparameters, macros = xparameter_baseaddr_macros(source_dir)
    if xparameters is None:
        return fallback, f"PWM: xparameters.h not found. Using fallback base-address macro {fallback}."

    indexed_suffix = f"_{index}_BASEADDR"
    candidates = [
        macro
        for macro in macros
        if all(term in macro for term in required_terms) and macro.endswith(indexed_suffix)
    ]
    if candidates:
        return candidates[0], ""

    return fallback, f"PWM: no {interface} BASEADDR macro for instance {index} found in {xparameters}. Using fallback {fallback}."


@lru_cache(maxsize=16)
def xparameter_baseaddr_macros(source_dir: Path) -> tuple[Path | None, tuple[str, ...]]:
    xparameters = find_xparameters(source_dir)
    if xparameters is None:
        return None, ()
    text = xparameters.read_text(encoding="utf-8", errors="ignore")
    macros = tuple(re.findall(r"^#define\s+(XPAR_[A-Z0-9_]*BASEADDR)\b", text, re.MULTILINE))
    return xparameters, macros


@lru_cache(maxsize=16)
def find_xparameters(source_dir: Path) -> Path | None:
    candidates = [
        source_dir / "xparameters.h",
        source_dir / "include" / "xparameters.h",
        source_dir / "xilinx" / "xparameters.h",
    ]
    for parent in source_dir.parents:
        if parent.name.lower() not in {"baremetal", "software"}:
            continue
        candidates.extend(
            [
                parent / "src" / "xparameters.h",
                parent / "src" / "include" / "xparameters.h",
                parent / "include" / "xparameters.h",
            ]
        )
        if parent.name.lower() == "software":
            vitis_root = parent.parent
            workspace_root = vitis_root / "workspace"
            candidates.extend(
                sorted(
                    workspace_root.glob(
                        "*/psu_cortexr5_0/Baremetal_domain/bsp/psu_cortexr5_0/include/xparameters.h"
                    )
                )
            )
            candidates.extend(
                sorted(
                    workspace_root.glob(
                        "*/export/*/sw/*/Baremetal_domain/bspinclude/include/xparameters.h"
                    )
                )
            )
    seen: set[Path] = set()
    for candidate in candidates:
        if candidate in seen:
            continue
        seen.add(candidate)
        if candidate.exists() and "test" not in {part.lower() for part in candidate.parts}:
            return candidate
    return None


def clear_xparameters_cache() -> None:
    xparameter_baseaddr_macros.cache_clear()
    find_xparameters.cache_clear()
