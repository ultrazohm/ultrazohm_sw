import subprocess
import re
import csv

# needs settings64.sh in shell from Vitis folder, move to workspace/Baremetal/Debug and call with python dumb_gdb Baremetal.elf

GDB_CMD = "arm-none-eabi-gdb"
ELF_FILE = "Baremetal.elf"
GLOBAL_VAR = "Global_Data"


def run_gdb_commands(commands):
    cmd = [GDB_CMD, ELF_FILE, "-batch"]
    for c in commands:
        cmd.extend(["-ex", c])
    result = subprocess.run(cmd, capture_output=True, text=True)
    return result.stdout


def parse_global_data_address(gdb_output):
    # Example line: $2 = (DS_Data *) 0x40043080 <Global_Data>
    match = re.search(r"=\s*\(.*\*\)\s*(0x[0-9a-fA-F]+)", gdb_output)
    if match:
        return int(match.group(1), 16)
    else:
        raise RuntimeError("Could not find Global_Data address")


def parse_ptype_output(ptype_output):
    """
    Parses 'ptype /o TYPE' output to extract member info:
    Returns list of tuples (offset, type, name).
    """
    members = []
    member_re = re.compile(r"/\*\s*(\d+)\s*\|\s*\d+\s*\*/\s*(.+?)\s+(\w+);")
    for line in ptype_output.splitlines():
        m = member_re.search(line)
        if m:
            offset = int(m.group(1))
            typ = m.group(2).strip()
            name = m.group(3)
            members.append((offset, typ, name))
    return members


def is_struct_type(typ):
    """
    Decide if typ is a struct/union by trying to get its members via ptype /o
    If the ptype /o output has member info, it's a struct/union, else not.
    """
    output = run_gdb_commands([f"ptype /o {typ}"])
    return "{" in output and "}" in output and "/*" in output


def recursive_parse_members(base_addr, type_name, prefix=""):
    """
    Recursively parse members of type_name,
    prepend prefix to member names, and add base_addr offsets.
    Returns list of tuples: (fullname, type, absolute_address)
    """
    members = []
    ptype_output = run_gdb_commands([f"ptype /o {type_name}"])
    top_members = parse_ptype_output(ptype_output)

    for offset, typ, name in top_members:
        fullname = f"{prefix}{name}" if prefix == "" else f"{prefix}.{name}"
        abs_addr = base_addr + offset
        members.append((fullname, typ, abs_addr))

        # Recursively parse nested structs/unions
        if is_struct_type(typ):
            # Recursively add nested members
            nested = recursive_parse_members(abs_addr, typ, prefix=fullname)
            members.extend(nested)

    return members


def main():
    # Get base address of Global_Data
    addr_output = run_gdb_commands([f"print &{GLOBAL_VAR}"])
    base_addr = parse_global_data_address(addr_output)
    print(f"Global_Data base address: 0x{base_addr:x}")

    # Get Global_Data type name
    type_output = run_gdb_commands([f"whatis {GLOBAL_VAR}"])
    m = re.search(r"type = (\w+)", type_output)
    if not m:
        raise RuntimeError("Could not find type of Global_Data")
    type_name = m.group(1)
    print(f"Global_Data type: {type_name}")

    # Start with Global_Data itself as first row
    rows = [(GLOBAL_VAR, type_name, f"0x{base_addr:x}")]

    # Recursively parse members and their nested members
    members = recursive_parse_members(base_addr, type_name)
    # Format all member addresses as hex strings
    members = [(m[0], m[1], f"0x{m[2]:x}") for m in members]

    rows.extend(members)

    # Write CSV
    with open("members.csv", "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["Member", "Type", "Address"])
        writer.writerows(rows)

    print(f"Wrote {len(rows)} members (including root) to members.csv")


if __name__ == "__main__":
    main()
