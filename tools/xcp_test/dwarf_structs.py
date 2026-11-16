#!/usr/bin/env python3
"""
dwarf_structs.py - A2L TYPEDEF_STRUCTURE / INSTANCE blocks from an ELF's DWARF.

CANape can measure a complete C struct only if the A2L describes its layout
(ASAP2 1.7.1 TYPEDEF_STRUCTURE + INSTANCE). CANape's own "create from ELF"
gives up on the UltraZohm types (unions with anonymous inner structs, pointer
members) and leaves a meaningless scalar behind - e.g. the former
"Global_Data.aa" UBYTE measurement in CANape/UZ_XCP/uz.A2L. This script
derives the layout from the same ELF (the DWARF debug info, read through GNU
objdump --dwarf=info so no extra Python package is needed) and writes blocks
CANape accepts, in the syntax of upstream XCPlite's own A2L generator:

  /begin TYPEDEF_MEASUREMENT M_FLOAT32_IEEE "" FLOAT32_IEEE NO_COMPU_METHOD 0 0 -3.4E38 3.4E38 /end TYPEDEF_MEASUREMENT
  /begin TYPEDEF_STRUCTURE actualValues "" 0xE0
    /begin STRUCTURE_COMPONENT pwm_frequency_hz M_FLOAT32_IEEE 0x0 /end STRUCTURE_COMPONENT
    /begin STRUCTURE_COMPONENT snd_fld M_FLOAT32_IEEE 0x8C MATRIX_DIM 21 /end STRUCTURE_COMPONENT
  /end TYPEDEF_STRUCTURE
  /begin INSTANCE Global_Data.av "" actualValues 0x40059CF8 SYMBOL_LINK "Global_Data.av" 0 /end INSTANCE

Rules (what CANape can and cannot take):
  - scalars, arrays of scalars (MATRIX_DIM), nested structs, arrays of structs
  - a union becomes a TYPEDEF_STRUCTURE of its FIRST alternative only (a struct
    view and an array view of the same bytes cannot both be components); the
    skipped alternatives are named in the typedef comment
  - an anonymous struct/union member is hoisted into its parent
  - pointers, functions and bit fields are skipped (named in the comment)
  - enums become unsigned integers of their size
  - INSTANCE addresses come from the ELF and carry SYMBOL_LINK, so CANape can
    refresh them from a newer ELF like it does for the plain MEASUREMENTs

Usage (standalone):
    python dwarf_structs.py --elf ..\\..\\vitis\\workspace\\Baremetal\\Debug\\Baremetal.elf Global_Data.av Global_Data.aa
    python gen_a2l.py --struct Global_Data.av,Global_Data.aa ...      (see gen_a2l.py)
"""
import argparse
import os
import re
import subprocess
import sys

DEFAULT_OBJDUMP_R5 = r"C:\Xilinx\Vitis\2022.2\gnu\armr5\nt\gcc-arm-none-eabi\bin\armr5-none-eabi-objdump.exe"
DEFAULT_OBJDUMP_A53 = r"C:\Xilinx\Vitis\2022.2\gnu\aarch64\nt\aarch64-none\bin\aarch64-none-elf-objdump.exe"

# (encoding class, byte size) -> (A2L data type, lower limit, upper limit)
A2L_TYPES = {
    ("float", 4): ("FLOAT32_IEEE", "-3.4E38", "3.4E38"),
    ("float", 8): ("FLOAT64_IEEE", "-1.7E308", "1.7E308"),
    ("unsigned", 1): ("UBYTE", "0", "255"),
    ("unsigned", 2): ("UWORD", "0", "65535"),
    ("unsigned", 4): ("ULONG", "0", "4294967295"),
    ("unsigned", 8): ("A_UINT64", "0", "18446744073709551615"),
    ("signed", 1): ("SBYTE", "-128", "127"),
    ("signed", 2): ("SWORD", "-32768", "32767"),
    ("signed", 4): ("SLONG", "-2147483648", "2147483647"),
    ("signed", 8): ("A_INT64", "-9223372036854775808", "9223372036854775807"),
}


class Die:
    __slots__ = ("off", "tag", "depth", "attrs", "children", "parent")

    def __init__(self, off, tag, depth):
        self.off, self.tag, self.depth = off, tag, depth
        self.attrs, self.children, self.parent = {}, [], None

    def name(self):
        v = self.attrs.get("DW_AT_name")
        if v is None:
            return None
        if "): " in v:
            v = v.rsplit("): ", 1)[1]
        return v.strip()

    def ref(self, attr="DW_AT_type"):
        v = self.attrs.get(attr)
        if v is None:
            return None
        m = re.search(r"<0x([0-9a-fA-F]+)>", v)
        return int(m.group(1), 16) if m else None

    def num(self, attr, default=None):
        v = self.attrs.get(attr)
        if v is None:
            return default
        m = re.match(r"\s*(0x[0-9a-fA-F]+|\d+)", v)
        return int(m.group(1), 0) if m else default


_DIE_RE = re.compile(r"^ <(\d+)><([0-9a-fA-F]+)>: Abbrev Number: (\d+)(?: \((DW_TAG_\w+)\))?")
_ATTR_RE = re.compile(r"^\s+<[0-9a-fA-F]+>\s+(DW_AT_\w+)\s*:\s*(.*)$")


def parse_objdump(text):
    """objdump --dwarf=info text -> {offset: Die}"""
    dies, stack, cur = {}, [], None
    for line in text.splitlines():
        m = _DIE_RE.match(line)
        if m:
            depth, off, abbrev, tag = int(m.group(1)), int(m.group(2), 16), int(m.group(3)), m.group(4)
            if abbrev == 0:
                cur = None
                continue
            d = Die(off, tag, depth)
            while stack and stack[-1].depth >= depth:
                stack.pop()
            if stack:
                d.parent = stack[-1]
                stack[-1].children.append(d)
            stack.append(d)
            dies[off] = d
            cur = d
            continue
        m = _ATTR_RE.match(line)
        if m and cur is not None:
            cur.attrs[m.group(1)] = m.group(2)
    return dies


def dump_dwarf(elf, objdump):
    return subprocess.check_output([objdump, "--dwarf=info", elf], text=True,
                                   errors="replace", stderr=subprocess.DEVNULL)


class TypeInfo:
    """Resolved type: kind in base/struct/union/array/pointer/enum/func/other."""

    def __init__(self, kind, die, size=0, a2l=None, name=None):
        self.kind, self.die, self.size, self.a2l, self.name = kind, die, size, a2l, name
        self.elem, self.dims = None, []  # arrays


class StructGen:
    def __init__(self, dies):
        self.dies = dies
        self.typedef_meas = {}      # a2l type -> block text
        self.structs = []           # (typedef name, block text) in dependency order
        self.struct_by_die = {}     # die offset -> typedef name
        self.used_names = set()

    # ---------------------------------------------------------- type resolution
    def resolve(self, off, pref_name=None):
        d = self.dies.get(off)
        if d is None:
            return TypeInfo("other", None)
        if d.tag == "DW_TAG_typedef":
            return self.resolve(d.ref(), pref_name or d.name())
        if d.tag in ("DW_TAG_const_type", "DW_TAG_volatile_type"):
            return self.resolve(d.ref(), pref_name)
        if d.tag == "DW_TAG_base_type":
            enc = re.search(r"\((.*?)\)", d.attrs.get("DW_AT_encoding", "")).group(1) if "DW_AT_encoding" in d.attrs else ""
            size = d.num("DW_AT_byte_size", 0)
            cls = "float" if "float" in enc else ("unsigned" if ("unsigned" in enc or "boolean" in enc) else "signed")
            a2l = A2L_TYPES.get((cls, size))
            return TypeInfo("base", d, size, a2l, pref_name or d.name())
        if d.tag == "DW_TAG_enumeration_type":
            size = d.num("DW_AT_byte_size", 4)
            return TypeInfo("base", d, size, A2L_TYPES.get(("unsigned", size)), pref_name or d.name())
        if d.tag in ("DW_TAG_structure_type", "DW_TAG_union_type"):
            kind = "struct" if d.tag == "DW_TAG_structure_type" else "union"
            if "DW_AT_declaration" in d.attrs:  # forward declaration: find the definition by name
                nm = d.name()
                for c in self.dies.values():
                    if c.tag == d.tag and c.name() == nm and "DW_AT_declaration" not in c.attrs:
                        d = c
                        break
            return TypeInfo(kind, d, d.num("DW_AT_byte_size", 0), None, pref_name or d.name())
        if d.tag == "DW_TAG_array_type":
            t = TypeInfo("array", d, 0, None, pref_name)
            t.elem = self.resolve(d.ref())
            for c in d.children:
                if c.tag == "DW_TAG_subrange_type":
                    if "DW_AT_count" in c.attrs:
                        t.dims.append(c.num("DW_AT_count", 0))
                    else:
                        t.dims.append(c.num("DW_AT_upper_bound", -1) + 1)
            n = 1
            for x in t.dims:
                n *= x
            t.size = n * t.elem.size
            return t
        if d.tag in ("DW_TAG_pointer_type", "DW_TAG_reference_type"):
            return TypeInfo("pointer", d, d.num("DW_AT_byte_size", 4), None, pref_name)
        if d.tag == "DW_TAG_subroutine_type":
            return TypeInfo("func", d)
        return TypeInfo("other", d)

    # ---------------------------------------------------------- emission
    def meas_typedef(self, a2l):
        typ, lo, hi = a2l
        name = "M_" + typ
        if name not in self.typedef_meas:
            self.typedef_meas[name] = ('/begin TYPEDEF_MEASUREMENT %s "" %s NO_COMPU_METHOD 0 0 %s %s '
                                       '/end TYPEDEF_MEASUREMENT\n' % (name, typ, lo, hi))
        return name

    def unique_name(self, base):
        base = re.sub(r"[^A-Za-z0-9_.]", "_", base or "anon") or "anon"
        if base[0].isdigit():
            base = "T_" + base
        name, i = base, 1
        while name in self.used_names:
            i += 1
            name = "%s_%d" % (base, i)
        self.used_names.add(name)
        return name

    def components(self, tinfo, base_off, notes):
        """Flatten the members of a struct/union TypeInfo -> [(name, offset, TypeInfo)]."""
        out = []
        members = [c for c in tinfo.die.children if c.tag == "DW_TAG_member"]
        if tinfo.kind == "union" and members:
            skipped = [m.name() or "(anonymous)" for m in members[1:]]
            if skipped:
                notes.append("union %s: only the first alternative is described, skipped: %s"
                             % (tinfo.name, ", ".join(skipped)))
            members = members[:1]
        for m in members:
            if "DW_AT_bit_size" in m.attrs:
                notes.append("bit field %s skipped" % (m.name() or "?"))
                continue
            off = base_off + m.num("DW_AT_data_member_location", 0)
            t = self.resolve(m.ref())
            nm = m.name()
            if nm is None and t.kind in ("struct", "union"):
                out.extend(self.components(t, off, notes))  # anonymous: hoist
                continue
            if nm is None:
                continue
            out.append((nm, off, t))
        return out

    def ensure_struct(self, tinfo):
        """Emit the TYPEDEF_STRUCTURE for a struct/union type (once); return its name."""
        key = tinfo.die.off
        if key in self.struct_by_die:
            return self.struct_by_die[key]
        name = self.unique_name(tinfo.name)
        self.struct_by_die[key] = name  # register first: self-references cannot occur, nested ones may repeat
        notes, lines = [], []
        for cname, off, t in self.components(tinfo, 0, notes):
            dims = []
            if t.kind == "array":
                dims = t.dims
                t = t.elem
                while t.kind == "array":  # nested array dims
                    dims = dims + t.dims
                    t = t.elem
            if t.kind == "base" and t.a2l:
                tname = self.meas_typedef(t.a2l)
            elif t.kind in ("struct", "union"):
                tname = self.ensure_struct(t)
                if tname is None:
                    notes.append("%s (struct without measurable members) skipped" % cname)
                    continue
            else:
                notes.append("%s (%s) skipped" % (cname, t.kind))
                continue
            line = "  /begin STRUCTURE_COMPONENT %s %s 0x%X" % (cname, tname, off)
            if dims and (len(dims) > 1 or dims[0] > 1):
                line += " MATRIX_DIM " + " ".join(str(x) for x in dims[:3])
            lines.append(line + " /end STRUCTURE_COMPONENT\n")
        if not lines:  # nothing measurable inside (e.g. only pointers): no typedef at all
            self.struct_by_die[key] = None
            self.used_names.discard(name)
            return None
        comment = "; ".join(notes)
        block = '/begin TYPEDEF_STRUCTURE %s "%s" 0x%X\n' % (name, comment.replace('"', "'"), tinfo.size)
        block += "".join(lines) + "/end TYPEDEF_STRUCTURE\n"
        self.structs.append((name, block))
        return name

    # ---------------------------------------------------------- symbol paths
    def find_variable(self, name):
        """Defining DIE (with address) of a global variable -> (addr, type offset)."""
        for d in self.dies.values():
            if d.tag != "DW_TAG_variable" or "DW_AT_location" not in d.attrs:
                continue
            spec = self.dies.get(d.ref("DW_AT_specification")) if "DW_AT_specification" in d.attrs else None
            nm = d.name() or (spec.name() if spec else None)
            if nm != name:
                continue
            m = re.search(r"DW_OP_addr: ([0-9a-fA-F]+)", d.attrs["DW_AT_location"])
            if not m:
                continue
            toff = d.ref() if "DW_AT_type" in d.attrs else (spec.ref() if spec else None)
            return int(m.group(1), 16), toff
        return None, None

    def walk_path(self, path):
        """'var.a.b' -> (address, TypeInfo of the final member)."""
        parts = path.split(".")
        addr, toff = self.find_variable(parts[0])
        if addr is None:
            raise KeyError("variable '%s' not found (no definition with an address in the DWARF)" % parts[0])
        t = self.resolve(toff)
        for p in parts[1:]:
            m = re.match(r"^(\w+)(?:\[(\d+)\])?$", p)
            if not m:
                raise KeyError("bad path element '%s'" % p)
            mname, idx = m.group(1), m.group(2)
            if t.kind not in ("struct", "union"):
                raise KeyError("'%s' is not a struct, cannot take member '%s'" % (path, mname))
            found = None
            for cname, off, ct in self.components(t, 0, []):
                if cname == mname:
                    found = (off, ct)
                    break
            if found is None:
                raise KeyError("member '%s' not found in '%s'" % (mname, path))
            addr += found[0]
            t = found[1]
            if idx is not None:
                if t.kind != "array":
                    raise KeyError("'%s' is not an array" % mname)
                addr += int(idx) * t.elem.size
                t = t.elem
        return addr, t

    def instance_block(self, path, comment=""):
        addr, t = self.walk_path(path)
        if t.kind in ("struct", "union"):
            tname = self.ensure_struct(t)
            if tname is None:
                raise KeyError("'%s' has no measurable members (pointers/functions only)" % path)
            return ('/begin INSTANCE %s "%s" %s 0x%08X\n  SYMBOL_LINK "%s" 0\n/end INSTANCE\n'
                    % (path, comment, tname, addr, path))
        dims = []
        if t.kind == "array":
            dims, t = t.dims, t.elem
        if t.kind == "base" and t.a2l:
            typ, lo, hi = t.a2l
            s = '/begin MEASUREMENT %s "%s"\n  %s NO_COMPU_METHOD 0 0 %s %s\n  ECU_ADDRESS 0x%08X\n' % (path, comment, typ, lo, hi, addr)
            if dims and (len(dims) > 1 or dims[0] > 1):
                s += "  MATRIX_DIM " + " ".join(str(x) for x in dims[:3]) + "\n"
            return s + '  SYMBOL_LINK "%s" 0\n/end MEASUREMENT\n' % path
        raise KeyError("'%s' has an unsupported type (%s)" % (path, t.kind))


def a2l_blocks(elf, objdump, paths, comment="", indent="    "):
    """All blocks (typedef measurements, typedef structures, instances) for the given symbol paths."""
    gen = StructGen(parse_objdump(dump_dwarf(elf, objdump)))
    instances = [gen.instance_block(p, comment) for p in paths]
    out = "".join(gen.typedef_meas.values()) + "\n"
    out += "\n".join(block for _, block in gen.structs) + "\n"
    out += "\n".join(instances)
    return "".join(indent + line + "\n" if line else "\n" for line in out.splitlines())


def main():
    ap = argparse.ArgumentParser(description="A2L TYPEDEF_STRUCTURE/INSTANCE blocks from ELF DWARF (via objdump).")
    ap.add_argument("paths", nargs="+", help="symbol paths, e.g. Global_Data.av Global_Data.aa.A1")
    ap.add_argument("--elf", required=True)
    ap.add_argument("--objdump", default=DEFAULT_OBJDUMP_R5,
                    help="GNU objdump for the ELF's architecture (default: Vitis armr5)")
    ap.add_argument("--out", default=None, help="write the blocks here instead of stdout")
    ap.add_argument("--comment", default="", help="comment string for the INSTANCE blocks")
    args = ap.parse_args()
    if not os.path.isfile(args.elf):
        print("[x] ELF not found: %s" % args.elf)
        return 1
    objdump = args.objdump if os.path.isfile(args.objdump) else "objdump"
    text = a2l_blocks(args.elf, objdump, args.paths, args.comment)
    if args.out:
        with open(args.out, "w", newline="\n") as f:
            f.write(text)
        print("[+] wrote %s" % args.out)
    else:
        sys.stdout.write(text)
    return 0


if __name__ == "__main__":
    sys.exit(main())
