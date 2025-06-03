from elftools.elf.elffile import ELFFile
from elftools.dwarf.descriptions import describe_form_class
import csv
import sys


def get_dwarf_info(elffile):
    if not elffile.has_dwarf_info():
        print("No DWARF debug info found.")
        return None
    return elffile.get_dwarf_info()


def get_type_die_by_offset(offset, dwarfinfo):
    """Search all DIEs for a given offset."""
    for cu in dwarfinfo.iter_CUs():
        for die in cu.iter_DIEs():
            if die.offset == offset:
                return die
    return None


def resolve_struct_members(struct_die, base_addr, prefix, dwarfinfo):
    """Recursively extract members of a struct with absolute addresses."""
    members = []

    for child in struct_die.iter_children():
        if child.tag != "DW_TAG_member":
            continue

        name_attr = child.attributes.get("DW_AT_name")
        loc_attr = child.attributes.get("DW_AT_data_member_location")

        if not name_attr or not loc_attr:
            continue

        name = name_attr.value.decode("utf-8")
        form = describe_form_class(loc_attr.form)

        if form == "constant":
            offset = loc_attr.value
        elif form == "exprloc" and len(loc_attr.value) == 1:
            offset = loc_attr.value[0]
        else:
            continue

        full_name = f"{prefix}.{name}"
        abs_addr = base_addr + offset

        # Get member size
        size_attr = child.attributes.get("DW_AT_byte_size")
        size = size_attr.value if size_attr else "?"

        members.append((full_name, hex(abs_addr), size))

        # Nested structs
        if "DW_AT_type" in child.attributes:
            type_die = get_type_die_by_offset(
                child.attributes["DW_AT_type"].value, dwarfinfo
            )
            if type_die and type_die.tag == "DW_TAG_structure_type":
                nested = resolve_struct_members(
                    type_die, abs_addr, full_name, dwarfinfo
                )
                members.extend(nested)

    return members


def extract_variables_and_structs(elf_path, csv_path):
    with open(elf_path, "rb") as f:
        elffile = ELFFile(f)
        dwarfinfo = get_dwarf_info(elffile)
        if not dwarfinfo:
            return

        variables = []

        symtab = elffile.get_section_by_name(".symtab")
        if not symtab:
            print("No .symtab section found.")
            return

        for symbol in symtab.iter_symbols():
            if symbol["st_info"]["type"] != "STT_OBJECT":
                continue
            if symbol["st_shndx"] == "SHN_UNDEF":
                continue

            name = symbol.name
            addr = symbol["st_value"]
            size = symbol["st_size"]
            section_index = symbol["st_shndx"]
            section_name = (
                elffile.get_section(section_index).name
                if isinstance(section_index, int)
                else "unknown"
            )

            # Add the variable itself
            variables.append((name, hex(addr), size, section_name))

            # Try to find this variable in DWARF and expand struct members
            for cu in dwarfinfo.iter_CUs():
                for die in cu.iter_DIEs():
                    if die.tag == "DW_TAG_variable" and "DW_AT_name" in die.attributes:
                        die_name = die.attributes["DW_AT_name"].value.decode("utf-8")
                        if die_name != name:
                            continue
                        if "DW_AT_type" not in die.attributes:
                            continue

                        type_die = get_type_die_by_offset(
                            die.attributes["DW_AT_type"].value, dwarfinfo
                        )
                        if not type_die or type_die.tag != "DW_TAG_structure_type":
                            continue

                        members = resolve_struct_members(
                            type_die, addr, name, dwarfinfo
                        )
                        for m in members:
                            variables.append((m[0], m[1], m[2], section_name))
                        break  # Found match, stop searching DIEs

        # Write CSV
        with open(csv_path, "w", newline="") as f:
            writer = csv.writer(f)
            writer.writerow(["variable_name", "address", "size", "section"])
            for var in variables:
                writer.writerow(var)

        print(
            f"Exported {len(variables)} variables (including struct members) to {csv_path}"
        )


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python export_elf.py <input.elf> <output.csv>")
    else:
        extract_variables_and_structs(sys.argv[1], sys.argv[2])
