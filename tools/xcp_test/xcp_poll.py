#!/usr/bin/env python3
"""
xcp_poll.py - dead-simple XCP-over-UDP test client for the UltraZohm XCPlite slave.

Purpose
-------
Verify the XCPlite slave on the A53 works END TO END *without CANape and without
an A2L file*.  It opens a UDP socket, sends an XCP CONNECT, then repeatedly reads
the Phase-1 demo variables (a 1 kHz counter and a 1 Hz sine) straight out of the
target's memory with the XCP SHORT_UPLOAD command, and prints them.

If you see the counter climbing and the sine swinging between -1 and +1, the whole
stack is proven: lwIP UDP + XCP transport + protocol engine + 1 us clock + memory
access on the real Vitis toolchain.

Requirements
------------
- Python 3.7+ (standard library only -- no pip installs).
- The UltraZohm flashed with the FreeRTOS app built from THIS branch
  (LOGGING_PATH_XCP_LITE = 1) and reachable over the network.
- You need the board's IP address (see TESTING.md for how to find it).

Usage
-----
    python xcp_poll.py --ip 192.168.1.42                # connectivity: CONNECT only
    python xcp_poll.py --ip 192.168.1.42 --watch xcp_r5_cycle_count:u32
    python xcp_poll.py --ip 192.168.1.42 --daq          # DAQ smoke test (Option Z)
    python xcp_poll.py --ip 192.168.1.42 --stress       # DAQ throughput stress
    python xcp_poll.py --ip 192.168.1.42 --stress --stress-bytes 4000 --daq-seconds 60
    python xcp_poll.py --ip 192.168.1.42 --demo         # A53 demo counter/sine poll

With no mode flag it only CONNECTs and prints MAX_CTO/MAX_DTO -- that already
proves UDP + gateway + OCM + engine round-trip. The old counter/sine poll is
behind --demo because its A53 addresses are NOT valid on the Option Z R5 slave.

Variable addresses are resolved automatically from the freshly built ELF via the
Vitis 'nm' tool.  If that lookup fails (e.g. you run this on a PC without Vitis),
it falls back to the addresses baked in below -- which are only valid for the
build that produced them, so rebuild => re-resolve.
"""

import argparse
import os
import socket
import struct
import subprocess
import sys
import time

# --- XCP command / response codes -------------------------------------------
XCP_CONNECT = 0xFF
XCP_DISCONNECT = 0xFE
XCP_SHORT_UPLOAD = 0xF4
PID_RES = 0xFF   # positive response
PID_ERR = 0xFE   # error response
PID_EV = 0xFD    # event packet (async)
PID_SERV = 0xFC  # service request packet (async, e.g. SERV_TEXT)

# --- Defaults baked in from the build that created this file ----------------
# (FreeRTOS.elf, feature/xcp_lite). Override with --*-addr or let --elf resolve.
DEFAULT_ADDR = {
    "xcp_demo_counter": 0x002002B4,        # volatile uint32_t, 1 kHz up-counter
    "xcp_demo_sine": 0x002002B8,           # volatile float, 1 Hz sine [-1, +1]
    "xcp_meas_local_timestamp_us": 0x00200288,  # uint32_t (Phase 3 image ts)
    "xcp_meas_local_signal": 0x00200290,   # float[8] (Phase 3 image signals)
}

# --- Phase 3 R5->A53 MEAS image in OCM (from APU_RPU_shared.h) ---------------
# bank1 base 0xFFFD0000 + 0x100; struct = { u32 seq; u32 timestamp_us; f32 sig[8] }
OCM_IMAGE_BASE = 0xFFFD0100
OCM_SEQ_ADDR = OCM_IMAGE_BASE + 0x0
OCM_TS_ADDR = OCM_IMAGE_BASE + 0x4
OCM_SIG0_ADDR = OCM_IMAGE_BASE + 0x8

# Repo-relative default locations (this file lives in <repo>/tools/xcp_test/).
_REPO = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
DEFAULT_ELF = os.path.join(
    _REPO, "vitis", "workspace", "FreeRTOS", "Debug", "FreeRTOS.elf")
DEFAULT_ELF_R5 = os.path.join(
    _REPO, "vitis", "workspace", "Baremetal", "Debug", "Baremetal.elf")
DEFAULT_NM = r"C:\Xilinx\Vitis\2022.2\gnu\aarch64\nt\aarch64-none\bin\aarch64-none-elf-nm.exe"
DEFAULT_NM_R5 = r"C:\Xilinx\Vitis\2022.2\gnu\armr5\nt\gcc-arm-none-eabi\bin\armr5-none-eabi-nm.exe"


def iter_tl_frames(data):
    """Yield XCP packets from a UDP payload of concatenated TL frames
    ([len u16 LE][ctr u16 LE][packet])+ -- DAQ segments carry several."""
    off = 0
    while off + 4 <= len(data):
        dlc = struct.unpack_from("<H", data, off)[0]
        if dlc == 0 or off + 4 + dlc > len(data):
            break  # padding / malformed tail
        yield data[off + 4: off + 4 + dlc]
        off += 4 + dlc


def resolve_addresses(elf_path, nm_path):
    """Return {symbol: address} read from the ELF via nm, or {} on failure."""
    if not (elf_path and os.path.isfile(elf_path)):
        return {}
    nm = nm_path if (nm_path and os.path.isfile(nm_path)) else "nm"
    try:
        out = subprocess.check_output([nm, elf_path], text=True, stderr=subprocess.DEVNULL)
    except (OSError, subprocess.CalledProcessError):
        return {}
    found = {}
    wanted = set(DEFAULT_ADDR)
    for line in out.splitlines():
        parts = line.split()
        if len(parts) >= 3 and parts[2] in wanted:
            try:
                found[parts[2]] = int(parts[0], 16)
            except ValueError:
                pass
    return found


WATCH_TYPES = {  # name -> (struct fmt, size bytes)
    "u8": ("<B", 1), "i8": ("<b", 1), "u16": ("<H", 2), "i16": ("<h", 2),
    "u32": ("<I", 4), "i32": ("<i", 4), "f32": ("<f", 4), "f64": ("<d", 8),
}


def nm_lookup(elf, nm, names):
    """Resolve symbol names -> address from an ELF via nm (for --watch).
    Tries the given nm, then the armr5 nm (for R5 ELFs), then PATH 'nm'."""
    if not (elf and os.path.isfile(elf)) or not names:
        return {}
    candidates = [c for c in (nm, DEFAULT_NM_R5, "nm")
                  if c and (c == "nm" or os.path.isfile(c))]
    want = set(names)
    for tool in candidates:
        try:
            out = subprocess.check_output([tool, elf], text=True, stderr=subprocess.DEVNULL)
        except (OSError, subprocess.CalledProcessError):
            continue
        found = {}
        for line in out.splitlines():
            p = line.split()
            if len(p) >= 3 and p[2] in want:
                try:
                    found[p[2]] = int(p[0], 16)
                except ValueError:
                    pass
        if found:
            return found
    return {}


def parse_watch(specs, elf, nm):
    """'name:u32' or '0xADDR:f32' -> [(label, addr, fmt, size)]. Default type f32.
    Names are resolved from `elf`; unresolved names are also tried against the
    R5 Baremetal.elf (the Option Z slave) as a convenience."""
    names = [s.partition(":")[0] for s in specs if not s.lower().startswith("0x")]
    syms = nm_lookup(elf, nm, names) if names else {}
    left = [n for n in names if n not in syms]
    if left and os.path.abspath(elf) != os.path.abspath(DEFAULT_ELF_R5):
        extra = nm_lookup(DEFAULT_ELF_R5, nm, left)
        if extra:
            print("[i] resolved from %s: %s" % (os.path.basename(DEFAULT_ELF_R5),
                                                ", ".join(sorted(extra))))
            syms.update(extra)
    out = []
    for sp in specs:
        body, _, typ = sp.partition(":")
        typ = (typ or "f32").lower()
        if typ not in WATCH_TYPES:
            print("[!] unknown type '%s' in '%s' (using f32)" % (typ, sp))
            typ = "f32"
        fmt, size = WATCH_TYPES[typ]
        if body.lower().startswith("0x"):
            a = int(body, 16)
        elif body in syms:
            a = syms[body]
        else:
            print("[x] cannot resolve '%s' (not 0xADDR and not in --elf)" % body)
            continue
        out.append((sp, a, fmt, size))
    return out


class XcpUdp:
    """Minimal XCP-on-UDP master. Transport header = <LEN u16><CTR u16> little-endian."""

    def __init__(self, ip, port, timeout=1.0):
        self.addr = (ip, port)
        self.ctr = 0
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.settimeout(timeout)

    def close(self):
        self.sock.close()

    def _command(self, packet, retries=3):
        """Send one XCP packet, return the response packet (header stripped)."""
        for _ in range(retries):
            hdr = struct.pack("<HH", len(packet), self.ctr & 0xFFFF)
            self.ctr += 1
            self.sock.sendto(hdr + packet, self.addr)
            # A datagram may hold several concatenated TL frames (e.g. a DAQ
            # segment). Skip DAQ (pid < 0xFC) and async EV/SERV; return RES/ERR.
            try:
                while True:
                    data, _src = self.sock.recvfrom(4096)
                    for pkt in iter_tl_frames(data):
                        if pkt[0] in (PID_RES, PID_ERR):
                            return pkt
            except socket.timeout:
                continue
        raise TimeoutError("no XCP response (is the board up and the IP correct?)")

    def connect(self):
        resp = self._command(bytes([XCP_CONNECT, 0x00]))
        if resp[0] != PID_RES:
            raise RuntimeError("CONNECT rejected by slave (resp=0x%02X)" % resp[0])
        # resp: [0xFF, resource, commModeBasic, maxCto, maxDto(2 LE), protoVer, transVer]
        info = {"max_cto": resp[3] if len(resp) > 3 else 0,
                "max_dto": struct.unpack_from("<H", resp, 4)[0] if len(resp) >= 6 else 0}
        return info

    def disconnect(self):
        try:
            self._command(bytes([XCP_DISCONNECT]), retries=1)
        except TimeoutError:
            pass

    def short_upload(self, address, size, ext=0):
        """XCP SHORT_UPLOAD: read `size` bytes at `address`. Returns raw bytes."""
        packet = bytes([XCP_SHORT_UPLOAD, size & 0xFF, 0x00, ext & 0xFF]) + \
            struct.pack("<I", address & 0xFFFFFFFF)
        resp = self._command(packet)
        if resp[0] != PID_RES:
            raise RuntimeError("SHORT_UPLOAD err at 0x%08X (resp=0x%02X)" % (address, resp[0]))
        return resp[1:1 + size]

    def _cmd_checked(self, name, packet):
        resp = self._command(packet)
        if resp[0] != PID_RES:
            err = resp[1] if len(resp) > 1 else 0
            raise RuntimeError("%s rejected (resp=0x%02X err=0x%02X)" % (name, resp[0], err))
        return resp

    def daq_setup_single(self, address, size, ext=0, event=0):
        """Dynamic DAQ: 1 list / 1 ODT / 1 entry on `event`, timestamped.
        Returns the FIRST_PID of the DAQ list (DTO identification byte)."""
        self._cmd_checked("FREE_DAQ", bytes([0xD6]))
        self._cmd_checked("ALLOC_DAQ", bytes([0xD5, 0x00]) + struct.pack("<H", 1))
        self._cmd_checked("ALLOC_ODT", bytes([0xD4, 0x00]) + struct.pack("<H", 0) + bytes([1]))
        self._cmd_checked("ALLOC_ODT_ENTRY",
                          bytes([0xD3, 0x00]) + struct.pack("<H", 0) + bytes([0, 1]))
        self._cmd_checked("SET_DAQ_PTR",
                          bytes([0xE2, 0x00]) + struct.pack("<H", 0) + bytes([0, 0]))
        self._cmd_checked("WRITE_DAQ",
                          bytes([0xE1, 0xFF, size & 0xFF, ext & 0xFF]) +
                          struct.pack("<I", address & 0xFFFFFFFF))
        # mode 0x10 = TIMESTAMP; daq 0; event; prescaler 1; priority 0
        self._cmd_checked("SET_DAQ_LIST_MODE",
                          bytes([0xE0, 0x10]) + struct.pack("<HH", 0, event) + bytes([1, 0]))
        resp = self._cmd_checked("START_STOP_DAQ_LIST(select)",
                                 bytes([0xDE, 0x02]) + struct.pack("<H", 0))
        first_pid = resp[1] if len(resp) > 1 else 0
        self._cmd_checked("START_STOP_SYNCH(start)", bytes([0xDD, 0x01]))
        return first_pid

    def daq_setup_stress(self, base, entry_sizes, event=0, prescaler=1):
        """Dynamic DAQ for throughput stress: 1 list, len(entry_sizes) ODTs with
        ONE entry each (entry i reads `base` + running offset), timestamped.
        Returns the FIRST_PID of the DAQ list."""
        n_odts = len(entry_sizes)
        self._cmd_checked("FREE_DAQ", bytes([0xD6]))
        self._cmd_checked("ALLOC_DAQ", bytes([0xD5, 0x00]) + struct.pack("<H", 1))
        self._cmd_checked("ALLOC_ODT",
                          bytes([0xD4, 0x00]) + struct.pack("<H", 0) + bytes([n_odts]))
        for odt in range(n_odts):
            self._cmd_checked("ALLOC_ODT_ENTRY",
                              bytes([0xD3, 0x00]) + struct.pack("<H", 0) + bytes([odt, 1]))
        off = 0
        for odt, size in enumerate(entry_sizes):
            self._cmd_checked("SET_DAQ_PTR",
                              bytes([0xE2, 0x00]) + struct.pack("<H", 0) + bytes([odt, 0]))
            self._cmd_checked("WRITE_DAQ",
                              bytes([0xE1, 0xFF, size & 0xFF, 0x00]) +
                              struct.pack("<I", (base + off) & 0xFFFFFFFF))
            off += size
        # mode 0x10 = TIMESTAMP; daq 0; event; prescaler; priority 0
        self._cmd_checked("SET_DAQ_LIST_MODE",
                          bytes([0xE0, 0x10]) + struct.pack("<HH", 0, event) +
                          bytes([prescaler & 0xFF, 0]))
        resp = self._cmd_checked("START_STOP_DAQ_LIST(select)",
                                 bytes([0xDE, 0x02]) + struct.pack("<H", 0))
        first_pid = resp[1] if len(resp) > 1 else 0
        self._cmd_checked("START_STOP_SYNCH(start)", bytes([0xDD, 0x01]))
        return first_pid

    def daq_stop(self):
        try:
            self._command(bytes([0xDD, 0x00]), retries=1)  # STOP all lists
        except TimeoutError:
            pass

    def drain(self, quiet_s=0.3, max_s=3.0):
        """Discard buffered/incoming datagrams until the line is quiet (used
        after daq_stop so command responses are not fished out of a backlog)."""
        old_to = self.sock.gettimeout()
        self.sock.settimeout(quiet_s)
        t_end = time.time() + max_s
        try:
            while time.time() < t_end:
                try:
                    self.sock.recvfrom(4096)
                except socket.timeout:
                    break
        finally:
            self.sock.settimeout(old_to)


def run_daq(xcp, item, seconds):
    """DAQ smoke test: stream one variable via a 1-list/1-ODT DAQ session."""
    label, a, fmt, size = item
    print("[i] DAQ target: %s @ 0x%08X (%d bytes), event 0, %gs" %
          (label, a, size, seconds))
    first_pid = xcp.daq_setup_single(a, size)
    print("[+] DAQ RUNNING (first_pid=0x%02X) -- collecting ...\n" % first_pid)
    n = 0
    shown = 0
    first_ts = last_ts = None
    t_end = time.time() + seconds
    try:
        while time.time() < t_end:
            try:
                data, _src = xcp.sock.recvfrom(4096)
            except socket.timeout:
                continue
            for pkt in iter_tl_frames(data):
                # DTO: [odt u8][fill u8][daq u16][ts u32 in ODT0][data]
                # (xcplite.c ODT_HEADER_SIZE 4, DAQ_HDR_ODT_FIL_DAQW)
                if pkt[0] != first_pid or len(pkt) < 8 + size:
                    continue
                ts = struct.unpack_from("<I", pkt, 4)[0]
                val = struct.unpack_from(fmt, pkt, 8)[0]
                if first_ts is None:
                    first_ts = ts
                last_ts = ts
                n += 1
                if shown < 10 or n % 5000 == 0:
                    print("    ts=%-12d  %s = %s" % (ts, label,
                          ("%.4f" % val) if fmt in ("<f", "<d") else str(val)))
                    shown += 1
    finally:
        xcp.daq_stop()
    if n == 0:
        print("\n[x] no DTOs received -- DAQ path broken (check ctr/framing/event)")
        return 1
    span_s = max(last_ts - first_ts, 1) / 1e6
    print("\n[+] DAQ OK: %d samples in %.2fs of target time (~%.0f Hz)" %
          (n, span_s, (n - 1) / span_s if n > 1 else 0.0))
    return 0


# R5 diagnostic counters sampled before/after a stress run (all u32; resolved
# from Baremetal.elf). The A53 gateway counters (xcp_gw_*) are NOT readable
# through the R5 slave -- check those via JTAG.
R5_DIAG_COUNTERS = [
    "xcp_r5_cycle_count", "ocm_xcp_w_dropped", "ocm_xcp_r_overrun",
    "xcp_r5_cto_sent", "xcp_r5_cto_dropped", "xcp_r5_in_generations",
    "xcp_r5_tx_oversize_drop",
]


def read_r5_diag(xcp, addrs):
    """Read the resolved diagnostic counters. Returns {name: value}."""
    out = {}
    for name in R5_DIAG_COUNTERS:
        if name in addrs:
            try:
                out[name] = struct.unpack("<I", xcp.short_upload(addrs[name], 4))[0]
            except (TimeoutError, RuntimeError):
                pass
    return out


def stress_geometry(target_bytes, max_dto):
    """Per-ODT entry sizes for a stress list. XCPlite DTO overhead per ODT:
    4-byte header ([odt][fill][daq u16]) + 4-byte timestamp in ODT0 only
    (xcplite.c: max payload = MAX_DTO - 4 - (odt==0 ? 4 : 0)). One entry per
    ODT keeps the 3 KB DAQ table memory tiny."""
    odt0_budget = (max_dto - 4 - 4) & ~3
    odt_budget = (max_dto - 4) & ~3
    sizes = []
    remaining = target_bytes
    budget = odt0_budget
    while remaining > 0 and len(sizes) < 200:
        sizes.append(min(remaining, budget))
        remaining -= sizes[-1]
        budget = odt_budget
    return sizes


def run_stress(xcp, args, max_dto):
    """DAQ throughput stress: one wide multi-ODT list on event 0 at the full
    control rate. Verifies the CP7 gateway path under load: UDP batching
    (frames/datagram), transport-CTR continuity (gaps = lost records), and the
    R5-side drop counters. hedrive reference: 160 Mbit/s sustained."""
    sizes = stress_geometry(args.stress_bytes, max_dto)
    per_cycle = sum(sizes)
    # OCM ceiling: XCP_OUT chain 7360 B minus 512 B CTO reserve, each 252 B
    # segment costs 8 B framing -> ~6500 B of DTO payload per control cycle.
    if per_cycle > 5000:
        print("[!] %d B/cycle is near/above the OCM per-cycle ceiling (~6 KB): "
              "expect ocm_xcp_w_dropped to climb" % per_cycle)
    print("[i] stress: %d B/cycle in %d ODTs @ base 0x%08X, event 0, %gs" %
          (per_cycle, len(sizes), args.stress_base, args.daq_seconds))
    print("[i]         (at 10 kHz control rate = %.0f Mbit/s DAQ payload)" %
          (per_cycle * 10e3 * 8 / 1e6))

    diag_addrs = nm_lookup(DEFAULT_ELF_R5, args.nm, R5_DIAG_COUNTERS)
    pre = read_r5_diag(xcp, diag_addrs)
    if not pre:
        print("[!] R5 diag counters not resolvable (no Baremetal.elf?) -- skipping deltas")

    # A large kernel receive buffer so the flood is not dropped PC-side: at
    # 160 Mbit/s a ~100 ms Windows scheduling hiccup already costs 2 MB.
    try:
        xcp.sock.setsockopt(socket.SOL_SOCKET, socket.SO_RCVBUF, 32 * 1024 * 1024)
    except OSError:
        pass
    try:
        print("[i] socket receive buffer: %.1f MB" %
              (xcp.sock.getsockopt(socket.SOL_SOCKET, socket.SO_RCVBUF) / 1e6))
    except OSError:
        pass

    first_pid = xcp.daq_setup_stress(args.stress_base, sizes,
                                     prescaler=args.prescaler)
    print("[+] DAQ RUNNING (first_pid=0x%02X, %d ODTs) -- collecting ...\n" %
          (first_pid, len(sizes)))

    buf = bytearray(4096)
    dgrams = frames = payload = cycles = 0
    ctr_gap_events = ctr_gap_frames = 0
    ctr_reorder = 0
    last_ctr = None
    first_ts = last_ts = None
    t0 = time.monotonic()
    t_end = t0 + args.daq_seconds
    t_tick = t0 + 1.0
    tick_payload = tick_dgrams = 0
    xcp.sock.settimeout(0.5)
    try:
        while True:
            now = time.monotonic()
            if now >= t_end:
                break
            if now >= t_tick:
                print("    %5.1fs  %6d dgrams/s  %7.2f Mbit/s payload  ctr_gaps=%d" %
                      (now - t0, dgrams - tick_dgrams,
                       (payload - tick_payload) * 8 / 1e6, ctr_gap_frames))
                t_tick += 1.0
                tick_payload, tick_dgrams = payload, dgrams
            try:
                n = xcp.sock.recv_into(buf)
            except socket.timeout:
                continue
            dgrams += 1
            off = 0
            while off + 4 <= n:
                dlc, ctr = struct.unpack_from("<HH", buf, off)
                if dlc == 0 or off + 4 + dlc > n:
                    break  # padding / malformed tail
                frames += 1
                payload += dlc
                if last_ctr is not None:
                    delta = (ctr - last_ctr) & 0xFFFF
                    if delta == 1:
                        last_ctr = ctr
                    elif delta > 0x8000:
                        # CTR went backwards: a late/reordered datagram, not a
                        # loss (its frames were already booked as a small gap
                        # when they were skipped). Keep the high-water mark.
                        ctr_reorder += 1
                    else:
                        ctr_gap_events += 1
                        ctr_gap_frames += delta - 1
                        last_ctr = ctr
                else:
                    last_ctr = ctr
                # ODT0 DTO: [odt u8][fill u8][daq u16][ts u32][data]
                if buf[off + 4] == first_pid and dlc >= 8:
                    ts = struct.unpack_from("<I", buf, off + 8)[0]
                    if first_ts is None:
                        first_ts = ts
                    last_ts = ts
                    cycles += 1
                off += 4 + dlc
    finally:
        xcp.daq_stop()
        xcp.drain()

    wall_s = max(time.monotonic() - t0, 1e-6)
    post = read_r5_diag(xcp, diag_addrs)

    print("\n[+] stress summary (%.2fs wall):" % wall_s)
    print("    datagrams        %10d   (%.0f/s, %.1f frames/datagram)" %
          (dgrams, dgrams / wall_s, frames / dgrams if dgrams else 0.0))
    print("    TL frames        %10d   (%.0f/s)" % (frames, frames / wall_s))
    print("    DAQ payload      %10d B (%.2f Mbit/s; wire ~%.2f Mbit/s)" %
          (payload, payload * 8 / wall_s / 1e6,
           (payload + 4 * frames + 42 * dgrams) * 8 / wall_s / 1e6))
    if cycles > 1 and last_ts is not None:
        span_s = max((last_ts - first_ts) & 0xFFFFFFFF, 1) / 1e6
        print("    event cycles     %10d   (~%.0f Hz of target time)" %
              (cycles, (cycles - 1) / span_s))
    net_lost = ctr_gap_frames - ctr_reorder
    print("    ctr gaps         %10d frames skipped in %d gaps%s" %
          (ctr_gap_frames, ctr_gap_events,
           "  <-- loss at/after sendto (lwIP pbuf, wire, PC rx)"
           if ctr_gap_frames else ""))
    if ctr_reorder:
        print("    ctr reordering   %10d of those arrived late (PC rx path "
              "reorders; late, not lost)" % ctr_reorder)
        print("    net lost         %10d frames (%.5f%%)  <-- the real loss" %
              (net_lost, 100.0 * net_lost / frames if frames else 0.0))
    if pre and post:
        print("    R5 counter deltas over the run:")
        for name in R5_DIAG_COUNTERS:
            if name in pre and name in post:
                d = (post[name] - pre[name]) & 0xFFFFFFFF
                flag = ""
                if d and name in ("ocm_xcp_w_dropped", "ocm_xcp_r_overrun",
                                  "xcp_r5_cto_dropped", "xcp_r5_tx_oversize_drop"):
                    flag = "  <-- investigate"
                print("      %-24s +%d%s" % (name, d, flag))
    print("    (A53 gateway counters xcp_gw_* are JTAG-only: torn/cycles_missed/"
          "txq_dropped/in_retry_cycles; on ctr gaps check xcp_gw_sendto_err: "
          ">0 = lwIP dropped it, 0 = wire/PC-side)")
    if frames == 0:
        print("\n[x] no DTOs received -- stress FAILED")
        return 1
    if net_lost < 0:
        net_lost = 0  # duplicated datagrams can over-count reordering
    print("\n[+] stress %s" % ("PASSED (no wire loss)" if net_lost == 0
                               else "completed WITH LOSS -- see counters"))
    return 0 if net_lost == 0 else 2


def main():
    ap = argparse.ArgumentParser(description="Poll the UltraZohm XCPlite slave over UDP (no CANape needed).")
    ap.add_argument("--ip", required=True, help="UltraZohm board IP address")
    ap.add_argument("--port", type=int, default=5556, help="XCP UDP port (default 5556)")
    ap.add_argument("--interval", type=float, default=0.2, help="poll period in seconds (default 0.2)")
    ap.add_argument("--elf", default=DEFAULT_ELF, help="ELF to resolve symbol addresses from "
                    "(unresolved --watch names also try Baremetal.elf automatically)")
    ap.add_argument("--nm", default=DEFAULT_NM, help="path to nm (armr5 nm tried as fallback)")
    ap.add_argument("--counter-addr", type=lambda x: int(x, 0), default=None)
    ap.add_argument("--sine-addr", type=lambda x: int(x, 0), default=None)
    ap.add_argument("--demo", action="store_true",
                    help="poll the A53 Phase-1 demo counter/sine (LOGGING_PATH_XCP_LITE "
                         "builds only -- these addresses are invalid on the R5 slave!)")
    ap.add_argument("--diag", action="store_true",
                    help="Phase 3 diagnostic: read the R5 MEAS image in OCM directly "
                         "(seq/ts @ 0xFFFD0100) and the A53-local copy, side by side")
    ap.add_argument("--watch", action="append", default=[], metavar="NAME|0xADDR[:TYPE]",
                    help="arbitrary read (repeatable). TYPE in u8/u16/u32/i32/f32/f64 "
                         "(default f32). NAME resolved from --elf, falling back to "
                         "Baremetal.elf (the Option Z R5 engine, arbitrary addressing).")
    ap.add_argument("--daq", action="store_true",
                    help="DAQ smoke test: stream the first --watch item (default "
                         "xcp_r5_cycle_count:u32) via a real DAQ list on event 0")
    ap.add_argument("--daq-seconds", type=float, default=None,
                    help="capture duration (default: 3s for --daq, 10s for --stress)")
    ap.add_argument("--stress", action="store_true",
                    help="DAQ throughput stress: one wide multi-ODT list on event 0 "
                         "at the control rate. Reports Mbit/s, frames/datagram "
                         "(CP7 batching), transport-CTR gaps (= lost records) and "
                         "R5 drop-counter deltas. hedrive reference: 160 Mbit/s.")
    ap.add_argument("--stress-bytes", type=int, default=2000,
                    help="target DAQ payload bytes per control cycle (default 2000 "
                         "= 160 Mbit/s at 10 kHz; OCM ceiling ~6000)")
    ap.add_argument("--stress-base", type=lambda x: int(x, 0), default=0xFFFF0000,
                    help="measurement block base address (default 0xFFFF0000, the "
                         "unused-under-XCP JavaScope OCM bank, 64 KB, allow-listed)")
    ap.add_argument("--prescaler", type=int, default=1,
                    help="DAQ event prescaler for --stress (default 1 = full rate)")
    args = ap.parse_args()
    if args.daq_seconds is None:
        args.daq_seconds = 10.0 if args.stress else 3.0

    print("[i] connecting to %s:%d ..." % (args.ip, args.port))

    xcp = XcpUdp(args.ip, args.port)
    try:
        info = xcp.connect()
        print("[+] CONNECTED  (MAX_CTO=%d  MAX_DTO=%d)" % (info["max_cto"], info["max_dto"]))

        if args.stress:
            return run_stress(xcp, args, info["max_dto"])

        if args.daq:
            specs = args.watch if args.watch else ["xcp_r5_cycle_count:u32"]
            items = parse_watch(specs, args.elf, args.nm)
            if not items:
                print("[x] cannot resolve a DAQ target (use --watch NAME:TYPE or 0xADDR:TYPE)")
                return 1
            return run_daq(xcp, items[0], args.daq_seconds)

        if args.watch:
            # Arbitrary read (Option Z: any R5 address via the identity-mapped engine).
            items = parse_watch(args.watch, args.elf, args.nm)
            if not items:
                print("[x] no watch items resolved")
                return 1
            for (label, a, _fmt, _sz) in items:
                print("[i] %s @ 0x%08X" % (label, a))
            print("    arbitrary read -- Ctrl+C to stop\n")
            print("    " + "  ".join("%-16s" % i[0] for i in items))
            while True:
                vals = []
                for (label, a, fmt, size) in items:
                    v = struct.unpack(fmt, xcp.short_upload(a, size))[0]
                    vals.append(("%-16.4f" if fmt in ("<f", "<d") else "%-16d") % v)
                print("    " + "  ".join(vals))
                time.sleep(args.interval)

        if args.diag or args.demo:
            # These modes read A53 (FreeRTOS.elf) demo addresses -- only valid
            # against the A53 XCPlite server (LOGGING_PATH_XCP_LITE builds).
            addr = dict(DEFAULT_ADDR)
            resolved = resolve_addresses(args.elf, args.nm)
            if resolved:
                addr.update(resolved)
                print("[i] addresses resolved from ELF: %s" % os.path.basename(args.elf))
            else:
                print("[!] could not resolve from ELF; using baked-in addresses "
                      "(valid only for the matching build)")
            if args.counter_addr is not None:
                addr["xcp_demo_counter"] = args.counter_addr
            if args.sine_addr is not None:
                addr["xcp_demo_sine"] = args.sine_addr

        if args.diag:
            # Phase 3 fault localization. Read the R5 image in OCM directly, plus
            # the A53-local copy the IPI handler maintains.
            #   raw_seq/raw_ts advancing  -> R5 IS writing the OCM image
            #   local_ts == raw_ts        -> A53 IPI handler copies it correctly
            #   raw_seq == 0 (static)     -> R5 not writing (ISR_Control idle /
            #                                stale R5 build / XCP_MEAS_IMAGE_ENABLE=0)
            #   raw advancing but local_ts == 0 -> IPI not reaching A53 / copy path
            print("    OCM image @ 0x%08X (seq/ts) + A53-local copy -- Ctrl+C to stop\n" % OCM_IMAGE_BASE)
            print("    (sig0 = ISR exec time us, sig1 = ISR period us)\n")
            print("    %-12s  %-12s  %-10s  %-10s  %-12s" %
                  ("raw_seq", "raw_ts_us", "isr_exec", "isr_period", "local_ts_us"))
            while True:
                raw_seq = struct.unpack("<I", xcp.short_upload(OCM_SEQ_ADDR, 4))[0]
                raw_ts = struct.unpack("<I", xcp.short_upload(OCM_TS_ADDR, 4))[0]
                sig0 = struct.unpack("<f", xcp.short_upload(OCM_SIG0_ADDR, 4))[0]
                sig1 = struct.unpack("<f", xcp.short_upload(OCM_SIG0_ADDR + 4, 4))[0]
                local_ts = struct.unpack("<I", xcp.short_upload(addr["xcp_meas_local_timestamp_us"], 4))[0]
                print("    %-12d  %-12d  %-10.3f  %-10.3f  %-12d" %
                      (raw_seq, raw_ts, sig0, sig1, local_ts))
                time.sleep(args.interval)

        if args.demo:
            print("[i] counter @ 0x%08X   sine @ 0x%08X" %
                  (addr["xcp_demo_counter"], addr["xcp_demo_sine"]))
            print("    polling -- Ctrl+C to stop\n")
            print("    %-12s  %-12s  %-14s" % ("counter", "sine", "ts_us"))
            while True:
                counter = struct.unpack("<I", xcp.short_upload(addr["xcp_demo_counter"], 4))[0]
                sine = struct.unpack("<f", xcp.short_upload(addr["xcp_demo_sine"], 4))[0]
                ts = struct.unpack("<I", xcp.short_upload(addr["xcp_meas_local_timestamp_us"], 4))[0]
                print("    %-12d  %-12.4f  %-14d" % (counter, sine, ts))
                time.sleep(args.interval)

        # No mode flag: connectivity test only (already proved the full path:
        # UDP -> gateway -> OCM -> engine -> response). Next: --watch or --daq.
        print("[i] connect-only OK. Try:  --watch xcp_r5_cycle_count:u32   or  --daq")
    except KeyboardInterrupt:
        print("\n[i] stopping")
    except (TimeoutError, RuntimeError) as e:
        print("[x] %s" % e)
        return 1
    finally:
        xcp.disconnect()
        xcp.close()
    return 0


if __name__ == "__main__":
    sys.exit(main())
