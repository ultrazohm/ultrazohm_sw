#!/usr/bin/env python3
"""
gen_a2l.py - generate a CANape-loadable A2L for the UltraZohm Option Z slave
(XCPlite engine on the R5, A53 UDP<->OCM gateway).

Link-time addresses change on every build, so the A2L is (re)generated from the
freshly built R5 ELF (Baremetal.elf).  The script reads the symbol addresses
with the Vitis 'nm' tool and emits an A2L containing:

  - MOD_COMMON (little-endian), RECORD_LAYOUTs and an identity COMPU_METHOD
  - MEASUREMENT objects for the requested R5 symbols (--symbols name:type,...)
    and, with --diag, the R5 loss/health counters; the A53 gateway counters
    mirrored into OCM are always included (fixed addresses, no ELF needed)
  - TYPEDEF_STRUCTURE + INSTANCE blocks for complete structures (--struct,
    layout from the ELF's DWARF through dwarf_structs.py)
  - an XCP IF_DATA block (UDP, port 5556) with the R5 engine's five DAQ
    rasters DAQ_R5 + daq_1ms/10ms/100ms/1s

The CANape project in CANape/UZ_XCP uses its own CANape-managed uz.A2L; this
generator is for a quick stand-alone A2L or for blocks to paste into that file.

Usage:
    python gen_a2l.py --ip 192.168.1.42 --symbols xcp_r5_cycle_count:u32 --diag
    python gen_a2l.py --ip 192.168.1.42 --diag --struct Global_Data.av
    python gen_a2l.py --struct Global_Data.av,Global_Data.aa --struct-out blocks.a2l

Notes:
  - The MEASUREMENT addresses are the load-bearing part and are always correct
    for the ELF you point at.
  - The XCP IF_DATA mirrors the settings of CANape/UZ_XCP/uz.A2L.
"""

import argparse
import os
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))  # dwarf_structs.py lives next to this file
import dwarf_structs  # noqa: E402

_REPO = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
DEFAULT_ELF = os.path.join(_REPO, "vitis", "workspace", "Baremetal", "Debug", "Baremetal.elf")
DEFAULT_NM = r"C:\Xilinx\Vitis\2022.2\gnu\armr5\nt\gcc-arm-none-eabi\bin\armr5-none-eabi-nm.exe"
DEFAULT_OUT = os.path.join(os.path.dirname(__file__), "UltraZohm_XCP.a2l")

# R5 symbols. TYPE -> (A2L datatype, lower, upper).
SYM_TYPEMAP = {
    "u8": ("UBYTE", "0", "255"), "u16": ("UWORD", "0", "65535"),
    "u32": ("ULONG", "0", "4294967295"),
    "i32": ("SLONG", "-2147483648", "2147483647"),
    "f32": ("FLOAT32_IEEE", "-3.4E38", "3.4E38"),
}

# DAQ rasters of the R5 engine, in the order xcp_r5_init() creates them
# (xcptl_ocm.c): (name, channel, TIME_CYCLE, TIME_UNIT). The unit codes are
# the ASAM ones GET_DAQ_EVENT_INFO derives from the event cycle time
# (0x02 = 100 ns, 0x04 = 10 us, 0x05 = 100 us, 0x06 = 1 ms, 0x07 = 10 ms).
# Channel 0 follows the ISR rate: 250 x 100 ns = 25 us at the default 40 kHz.
R5_EVENTS = [
    ("DAQ_R5", 0, 0xFA, 0x02),
    ("daq_1ms", 1, 0x64, 0x04),
    ("daq_10ms", 2, 0x64, 0x05),
    ("daq_100ms", 3, 0x64, 0x06),
    ("daq_1s", 4, 0x64, 0x07),
]

# A53 gateway counters, mirrored every IPI into the XCP_IN header spare words
# (vitis/software/Baremetal/src/sw/xcp_engine/ocm_xcp_fifo.h, enum
# ocm_xcp_in_diag_slot): fixed OCM addresses, independent of any build, read by
# the master through the R5 engine. Keep in sync with that enum.
A53_DIAG_ADDR = 0xFFFFC008
A53_DIAG_COUNTERS = [
    "xcp_gw_ocm_skipped_writing", "xcp_gw_ocm_torn", "xcp_gw_ocm_cycles_missed",
    "xcp_gw_ocm_capped", "xcp_gw_txq_dropped", "xcp_gw_ctoq_dropped",
    "xcp_gw_in_batches_sent", "xcp_gw_in_retry_cycles", "xcp_gw_tx_malformed_drop",
    "xcp_gw_rx_malformed_drop", "xcp_gw_sendto_err", "xcp_gw_sendto_drop",
    "xcp_gw_ipi_count", "xcp_gw_txq_level", "xcp_gw_master_lost",
]
# R5-side loss/health counters (u32 globals in xcptl_ocm.c / ocm_xcp_fifo.c),
# added with --diag.
R5_DIAG_SYMBOLS = [
    "ocm_xcp_w_dropped", "ocm_xcp_r_overrun", "xcp_r5_cto_dropped", "xcp_r5_cto_sent",
    "xcp_r5_queue_lost", "xcp_r5_tx_held", "xcp_r5_out_held", "xcp_r5_out_overwritten",
    "xcp_r5_cmd_oversize_drop", "xcp_r5_write_denied",
    "xcp_r5_in_resumed", "xcp_r5_in_generations", "xcp_r5_tx_oversize_drop",
    "xcp_r5_cycle_count", "xcp_r5_sweep_count", "xcp_r5_sweep_gap_max_us",
]


def nm_addresses(elf, nm):
    out = subprocess.check_output([nm, elf], text=True, stderr=subprocess.DEVNULL)
    addrs = {}
    for line in out.splitlines():
        p = line.split()
        if len(p) >= 3:
            addrs[p[2]] = int(p[0], 16)
    return addrs


def measurement(name, dtype, addr, comment, lower, upper, daq_event):
    return f"""    /begin MEASUREMENT {name} "{comment}"
      {dtype} identity 0 0 {lower} {upper}
      ECU_ADDRESS 0x{addr:08X}
      /begin IF_DATA XCP
        /begin DAQ_EVENT {daq_event} /end DAQ_EVENT
      /end IF_DATA
    /end MEASUREMENT
"""


def build_a2l(items, ip, port, struct_blocks=""):
    """items: [(name, addr, type)] -> a full A2L of R5 ELF symbols, the A53
    gateway counters and optional TYPEDEF_STRUCTURE/INSTANCE blocks."""
    # Every symbol may be measured on any raster; default to the fast one.
    daq_event = ("VARIABLE /begin AVAILABLE_EVENT_LIST "
                 + " ".join("EVENT 0x%04X" % ch for _, ch, _, _ in R5_EVENTS)
                 + " /end AVAILABLE_EVENT_LIST /begin DEFAULT_EVENT_LIST "
                   "EVENT 0x0000 /end DEFAULT_EVENT_LIST")
    meas = []
    for name, a, typ in items:
        dtype, lo, hi = SYM_TYPEMAP.get(typ, SYM_TYPEMAP["f32"])
        meas.append(measurement(name, dtype, a, "R5 %s" % name, lo, hi, daq_event))
    for i, name in enumerate(A53_DIAG_COUNTERS):
        meas.append(measurement(name, "ULONG", A53_DIAG_ADDR + 4 * i,
                                "A53 gateway counter (XCP_IN header mirror slot %d)" % i,
                                "0", "4294967295", daq_event))
    meas_block = "\n".join(meas)
    if struct_blocks:
        meas_block += "\n" + struct_blocks
    events = "\n".join(
        '        /begin EVENT "%s" "%s" 0x%04X DAQ 0xFF 0x%02X 0x%02X 0x00 /end EVENT'
        % (name, name, ch, cycle, unit) for name, ch, cycle, unit in R5_EVENTS)

    return f"""ASAP2_VERSION 1 71
/begin PROJECT UltraZohm "UltraZohm XCP (auto-generated by gen_a2l.py)"

  /begin HEADER "UltraZohm XCPlite engine on the R5"
    VERSION "1.0"
  /end HEADER

  /begin MODULE CPP "XCPlite engine on R5 (Option Z, arbitrary addressing)"

    /begin MOD_COMMON ""
      BYTE_ORDER MSB_LAST
      ALIGNMENT_BYTE 1
      ALIGNMENT_WORD 2
      ALIGNMENT_LONG 4
      ALIGNMENT_FLOAT32_IEEE 4
    /end MOD_COMMON

    /begin RECORD_LAYOUT RL_U32 FNC_VALUES 1 ULONG ROW_DIR DIRECT /end RECORD_LAYOUT
    /begin RECORD_LAYOUT RL_F32 FNC_VALUES 1 FLOAT32_IEEE ROW_DIR DIRECT /end RECORD_LAYOUT

    /begin COMPU_METHOD identity "1:1 identity"
      RAT_FUNC "%.6" ""
      COEFFS 0 1 0 0 0 1
    /end COMPU_METHOD

{meas_block}
    /begin IF_DATA XCP
      /begin PROTOCOL_LAYER
        0x0100
        5000 10000 0 0 0 0 0
        248 1024
        BYTE_ORDER_MSB_LAST
        ADDRESS_GRANULARITY_BYTE
        OPTIONAL_CMD GET_DAQ_CLOCK
        OPTIONAL_CMD SHORT_UPLOAD
      /end PROTOCOL_LAYER
      /begin DAQ
        DYNAMIC 0 {len(R5_EVENTS)} 0
        OPTIMISATION_TYPE_DEFAULT
        ADDRESS_EXTENSION_FREE
        IDENTIFICATION_FIELD_TYPE_RELATIVE_WORD_ALIGNED
        GRANULARITY_ODT_ENTRY_SIZE_DAQ_BYTE
        0xF0
        NO_OVERLOAD_INDICATION
        /begin TIMESTAMP_SUPPORTED
          0x1 SIZE_DWORD UNIT_1US TIMESTAMP_FIXED
        /end TIMESTAMP_SUPPORTED
{events}
      /end DAQ
      /begin XCP_ON_UDP_IP
        0x0100
        {port}
        ADDRESS "{ip}"
      /end XCP_ON_UDP_IP
    /end IF_DATA

  /end MODULE
/end PROJECT
"""


def main():
    ap = argparse.ArgumentParser(description="Generate an A2L for the UltraZohm Option Z XCP slave (R5 engine).")
    ap.add_argument("--elf", default=DEFAULT_ELF,
                    help="R5 ELF to read addresses from (default: the workspace Baremetal.elf)")
    ap.add_argument("--nm", default=DEFAULT_NM)
    ap.add_argument("--ip", default="192.168.1.42", help="board IP for the XCP_ON_UDP_IP block")
    ap.add_argument("--port", type=int, default=5556)
    ap.add_argument("--out", default=DEFAULT_OUT)
    ap.add_argument("--symbols", default=None,
                    help="comma list of R5 symbols 'name:type' (type in u8/u16/u32/i32/f32, "
                         "default f32) resolved from --elf")
    ap.add_argument("--diag", action="store_true",
                    help="also emit the R5 loss/health counters (R5_DIAG_SYMBOLS, u32) resolved "
                         "from --elf; the A53 gateway counters are always emitted (fixed OCM addresses)")
    ap.add_argument("--struct", default=None,
                    help="comma list of struct symbol paths (e.g. Global_Data.av,Global_Data.aa) "
                         "to describe as TYPEDEF_STRUCTURE + INSTANCE from the ELF's DWARF, so CANape can "
                         "measure the complete structure (tools/xcp_test/dwarf_structs.py)")
    ap.add_argument("--struct-out", default=None,
                    help="write only the --struct blocks to this file (for pasting into a "
                         "CANape-managed A2L such as CANape/UZ_XCP/uz.A2L) and exit")
    ap.add_argument("--objdump", default=dwarf_structs.DEFAULT_OBJDUMP_R5,
                    help="GNU objdump matching --elf, used by --struct (default: Vitis armr5)")
    args = ap.parse_args()

    if not os.path.isfile(args.elf):
        print("[x] ELF not found: %s" % args.elf); return 1
    nm = args.nm if os.path.isfile(args.nm) else "nm"
    addrs = nm_addresses(args.elf, nm)

    struct_blocks = ""
    if args.struct:
        objdump = args.objdump if os.path.isfile(args.objdump) else "objdump"
        struct_blocks = dwarf_structs.a2l_blocks(
            args.elf, objdump, [p.strip() for p in args.struct.split(",") if p.strip()],
            "complete structure, layout from the ELF DWARF (gen_a2l.py --struct)")
        if args.struct_out:
            with open(args.struct_out, "w", newline="\n") as f:
                f.write(struct_blocks)
            print("[+] wrote %s (TYPEDEF_STRUCTURE/INSTANCE blocks for %s)" % (args.struct_out, args.struct))
            return 0

    if not (args.symbols or args.diag or struct_blocks):
        print("[x] nothing to emit: pass --symbols NAME:TYPE,... and/or --diag and/or --struct PATH,...")
        return 1
    want = {}
    for spec in (args.symbols or "").split(","):
        if not spec.strip():
            continue
        name, _, typ = spec.strip().partition(":")
        want[name] = (typ or "f32").lower()
    if args.diag:
        for name in R5_DIAG_SYMBOLS:
            want.setdefault(name, "u32")
    items = [(n, addrs[n], t) for n, t in want.items() if n in addrs]
    missing = [n for n in want if n not in addrs]
    if missing:
        print("[!] not found in ELF: %s" % ", ".join(missing))
    if want and not items:
        print("[x] no requested symbols found in %s" % args.elf); return 1
    with open(args.out, "w", newline="\n") as f:
        f.write(build_a2l(items, args.ip, args.port, struct_blocks))
    print("[+] wrote %s (%d R5 symbols%s)" % (args.out, len(items),
                                              ", structures: " + args.struct if args.struct else ""))
    for n, a, t in items:
        print("    %-28s @ 0x%08X  %s" % (n, a, t))
    print("    XCP_ON_UDP_IP set to %s:%d  (edit --ip to match your board)" % (args.ip, args.port))
    return 0


if __name__ == "__main__":
    sys.exit(main())
