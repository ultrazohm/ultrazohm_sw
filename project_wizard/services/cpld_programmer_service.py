from __future__ import annotations

import re
import subprocess
from dataclasses import dataclass
from datetime import datetime
from pathlib import Path
from xml.dom import minidom
from xml.etree import ElementTree as ET

from ..paths import DIGITAL_SLOTS


D_SLOT_CPLD_DIR = Path("MACHXO2") / "D_Slot_CPLD_LCMXO2-2000HC-4TG100C"
D_SLOT_JED_DIR = D_SLOT_CPLD_DIR / "uz_d_slots"
DEFAULT_INACTIVE_PROGRAM_ID = "template_dslots"
ISPMACH_DEFAULT_INACTIVE_PROGRAM_ID = "30tx"

CPLD_VARIANTS = {
    "machxo2": {
        "base_dir": D_SLOT_JED_DIR,
        "family": "MachXO2",
        "name": "LCMXO2-2000HC",
        "idcode": "0x012bb043",
        "operation": "FLASH Erase,Program,Verify",
        "preload_length": "424",
        "io_vector": "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
        "usercode": "0x00000000",
        "access_mode": "FLASH",
        "debug_mode": False,
        "override_ues_first": False,
        "inactive_program_id": DEFAULT_INACTIVE_PROGRAM_ID,
    },
    "la4128v": {
        "base_dir": Path("ispMACH") / "LA4128V",
        "family": "ispMACH4000",
        "name": "LA4128V",
        "idcode": "0x01811043",
        "operation": "Erase,Program,Verify",
        "preload_length": "196",
        "io_vector": "0x0000000000000000000000000000000000000000000000000",
        "usercode": "0xFFFFFFFF",
        "access_mode": "JTAG",
        "debug_mode": True,
        "override_ues_first": False,
        "inactive_program_id": ISPMACH_DEFAULT_INACTIVE_PROGRAM_ID,
    },
    "lc4256v": {
        "base_dir": Path("ispMACH") / "LC4256V",
        "family": "ispMACH4000",
        "name": "LC4256V",
        "idcode": "0x11815043",
        "operation": "Erase,Program,Verify",
        "preload_length": "260",
        "io_vector": "0x00000000000000000000000000000000000000000000000000000000000000000",
        "usercode": "0xFFFFFFFF",
        "access_mode": "JTAG",
        "debug_mode": True,
        "override_ues_first": True,
        "svf_processor_all": "SVF Processor",
        "inactive_program_id": ISPMACH_DEFAULT_INACTIVE_PROGRAM_ID,
    },
}

ISPMACH_JED_FILENAMES = {
    "30tx": "uz_cpld_30tx.jed",
    "rx30": "uz_cpld_rx30.jed",
    "uz_d_3ph_inverter": "uz_d_3ph_inverter.jed",
    "uz_d_abs_encoder": "uz_d_abs_encoder.jed",
    "uz_d_resolver_d1_to_d4": str(Path("uz_d_resolver") / "digital_D1_to_D4" / "uz_cpld_uz_d_resolver_d1_to_d4.jed"),
    "uz_d_resolver_d5": str(Path("uz_d_resolver") / "digital_D5" / "uz_cpld_uz_d_resolver_d5.jed"),
    "uz_d_temperature_ltc2983": "uz_temperature_card.jed",
}

MACHXO2_JED_FILENAMES = {
    "30tx": "uz_cpld_30tx.jed",
    "rx30": "uz_cpld_rx30.jed",
}

@dataclass(frozen=True)
class GeneratedXcf:
    path: Path
    active_slots: list[str]
    inactive_slots: list[str]
    warnings: list[str]


@dataclass(frozen=True)
class ProgrammerRunResult:
    command: list[str]
    return_code: int
    stdout: str
    stderr: str
    log_text: str
    log_path: Path


def read_cable_settings_from_xcf(xcf_path: Path) -> dict[str, str]:
    tree = ET.parse(xcf_path)
    root = tree.getroot()
    cable_options = root.find("CableOptions")
    project_options = root.find("ProjectOptions")
    if cable_options is None:
        raise ValueError(f"Could not find CableOptions in {xcf_path}")

    return {
        "cable_name": _xml_text(cable_options, "CableName"),
        "port_address": _xml_text(cable_options, "PortAdd"),
        "usb_id": _xml_text(cable_options, "USBID"),
        "tck_delay": _xml_text(project_options, "TCKDelay") if project_options is not None else "",
    }


def generate_d_slot_xcf(
    output_path: Path,
    cpld_repository: Path,
    programmer_executable: Path,
    slot_cplds: dict[str, str],
    cable_settings: dict[str, str],
) -> GeneratedXcf:
    output_path.parent.mkdir(parents=True, exist_ok=True)
    variant_id = cable_settings.get("cpld_variant", "machxo2") or "machxo2"
    if variant_id == "microzohm":
        raise ValueError("MicroZohm CPLD programming workflow is not defined yet.")
    variant = CPLD_VARIANTS.get(variant_id)
    if variant is None:
        raise ValueError(f"Unsupported D-slot CPLD variant: {variant_id}")

    active_slots: list[str] = []
    inactive_slots: list[str] = []
    warnings: list[str] = []

    root = ET.Element("ispXCF", {"version": _diamond_version_from_path(programmer_executable)})
    ET.SubElement(root, "Comment")
    chain = ET.SubElement(root, "Chain")
    ET.SubElement(chain, "Comm").text = "JTAG"

    for position, slot in enumerate(DIGITAL_SLOTS, start=1):
        program_id = slot_cplds.get(slot, "none") or "none"
        selected = program_id != "none"
        if selected:
            active_slots.append(slot)
            jed_path = _program_jed_path(cpld_repository, program_id, variant)
            if not jed_path.exists():
                raise FileNotFoundError(f"Could not find JEDEC file for {slot} / {program_id}: {jed_path}")
        else:
            inactive_slots.append(slot)
            jed_path = _program_jed_path(cpld_repository, str(variant["inactive_program_id"]), variant)
            if not jed_path.exists():
                warnings.append(f"Inactive fallback JEDEC file not found for {slot}: {jed_path}")

        _append_device(chain, position, selected, jed_path, variant)

    project_options = ET.SubElement(root, "ProjectOptions")
    ET.SubElement(project_options, "Program").text = "SEQUENTIAL"
    ET.SubElement(project_options, "Process").text = "ENTIRED CHAIN"
    ET.SubElement(project_options, "OperationOverride").text = "No Override"
    ET.SubElement(project_options, "StartTAP").text = "TLR"
    ET.SubElement(project_options, "EndTAP").text = "TLR"
    ET.SubElement(project_options, "VerifyUsercode", {"value": "FALSE"})
    ET.SubElement(project_options, "TCKDelay").text = str(cable_settings.get("tck_delay", "3") or "3")

    cable_options = ET.SubElement(root, "CableOptions")
    ET.SubElement(cable_options, "CableName").text = cable_settings.get("cable_name", "USB2") or "USB2"
    ET.SubElement(cable_options, "PortAdd").text = cable_settings.get("port_address", "FTUSB-1") or "FTUSB-1"
    ET.SubElement(cable_options, "USBID").text = cable_settings.get("usb_id", "")

    _write_xcf(output_path, root)
    return GeneratedXcf(output_path, active_slots, inactive_slots, warnings)


def run_lattice_programmer(programmer_executable: Path, xcf_path: Path, log_path: Path) -> ProgrammerRunResult:
    log_path.parent.mkdir(parents=True, exist_ok=True)
    command = [str(programmer_executable), "-infile", str(xcf_path), "-logfile", str(log_path)]
    completed = subprocess.run(
        command,
        cwd=str(programmer_executable.parent),
        capture_output=True,
        text=True,
        check=False,
    )
    try:
        log_text = log_path.read_text(encoding="utf-8", errors="replace")
    except OSError:
        log_text = ""
    return ProgrammerRunResult(command, completed.returncode, completed.stdout, completed.stderr, log_text, log_path)


def _append_device(chain: ET.Element, position: int, selected: bool, jed_path: Path, variant: dict[str, object]) -> None:
    device = ET.SubElement(chain, "Device")
    ET.SubElement(device, "SelectedProg", {"value": "TRUE" if selected else "FALSE"})
    ET.SubElement(device, "Pos").text = str(position)
    ET.SubElement(device, "Vendor").text = "Lattice"
    ET.SubElement(device, "Family").text = str(variant["family"])
    ET.SubElement(device, "Name").text = str(variant["name"])
    ET.SubElement(device, "IDCode").text = str(variant["idcode"])
    ET.SubElement(device, "Package").text = "All"
    ET.SubElement(device, "PON").text = str(variant["name"])

    bypass = ET.SubElement(device, "Bypass")
    ET.SubElement(bypass, "InstrLen").text = "8"
    ET.SubElement(bypass, "InstrVal").text = "11111111"
    ET.SubElement(bypass, "BScanLen").text = "1"
    ET.SubElement(bypass, "BScanVal").text = "0"

    if jed_path.exists():
        ET.SubElement(device, "File").text = _xcf_path(jed_path)
        ET.SubElement(device, "FileTime").text = _file_time(jed_path)
        ET.SubElement(device, "JedecChecksum").text = _jedec_checksum(jed_path)
    ET.SubElement(device, "Operation").text = str(variant["operation"])

    option = ET.SubElement(device, "Option")
    ET.SubElement(option, "SVFVendor").text = "JTAG STANDARD"
    ET.SubElement(option, "IOState").text = "HighZ"
    ET.SubElement(option, "PreloadLength").text = str(variant["preload_length"])
    ET.SubElement(option, "IOVectorData").text = str(variant["io_vector"])
    if position > 1 or bool(variant["override_ues_first"]):
        ET.SubElement(option, "OverideUES", {"value": "TRUE"})
    if bool(variant["debug_mode"]):
        ET.SubElement(option, "DebugMode", {"value": "TRUE"})
    ET.SubElement(option, "TCKFrequency").text = "1.000000 MHz"
    svf_processor_all = variant.get("svf_processor_all")
    ET.SubElement(option, "SVFProcessor").text = str(svf_processor_all or ("SVF Processor" if position == 1 else "ispVM"))
    ET.SubElement(option, "Usercode").text = str(variant["usercode"])
    if position == 1:
        ET.SubElement(option, "AccessMode").text = str(variant["access_mode"])


def _program_jed_path(cpld_repository: Path, program_id: str, variant: dict[str, object]) -> Path:
    program = program_id.strip() or DEFAULT_INACTIVE_PROGRAM_ID
    base_dir = Path(str(variant["base_dir"]))
    if variant["name"] == "LCMXO2-2000HC":
        candidates = [
            cpld_repository / base_dir / program / f"uz_d_slots_{program}.jed",
        ]
        mapped_filename = MACHXO2_JED_FILENAMES.get(program)
        if mapped_filename:
            candidates.append(cpld_repository / base_dir / program / mapped_filename)
            candidates.append(cpld_repository / base_dir / mapped_filename)
        candidates.append(cpld_repository / base_dir / program / f"{program}.jed")
        for candidate in candidates:
            if candidate.exists():
                return candidate
        return candidates[0]
    filename = ISPMACH_JED_FILENAMES.get(program, f"{program}.jed")
    filename_path = Path(filename)
    if len(filename_path.parts) > 1:
        return cpld_repository / base_dir / filename_path
    return cpld_repository / base_dir / program / filename_path


def _diamond_version_from_path(programmer_executable: Path) -> str:
    match = re.search(r"diamond[\\/](?P<version>\d+(?:\.\d+)*)", str(programmer_executable), re.IGNORECASE)
    if match:
        return match.group("version")
    return "3.14"


def _file_time(path: Path) -> str:
    return datetime.fromtimestamp(path.stat().st_mtime).strftime("%m/%d/%y %H:%M:%S")


def _jedec_checksum(path: Path) -> str:
    text = path.read_text(encoding="latin-1", errors="ignore")
    matches = re.findall(r"\bC([0-9A-Fa-f]{4})\*", text)
    if matches:
        return f"0x{matches[-1].upper()}"
    return "0x0000"


def _xcf_path(path: Path) -> str:
    return path.resolve().as_posix()


def _write_xcf(path: Path, root: ET.Element) -> None:
    rough_xml = ET.tostring(root, encoding="utf-8")
    document = minidom.parseString(rough_xml).toprettyxml(indent="\t", encoding="utf-8").decode("utf-8")
    lines = document.splitlines()
    if lines and lines[0].startswith("<?xml"):
        lines[0] = "<?xml version='1.0' encoding='utf-8' ?>"
    lines.insert(1, '<!DOCTYPE\t\tispXCF\tSYSTEM\t"IspXCF.dtd" >')
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")


def _xml_text(parent: ET.Element, tag: str) -> str:
    child = parent.find(tag)
    if child is None or child.text is None:
        return ""
    return child.text.strip()
