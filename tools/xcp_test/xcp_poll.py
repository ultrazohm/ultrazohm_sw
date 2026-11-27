#!/usr/bin/env python3
"""
xcp_poll.py - dead-simple XCP-over-UDP test client for the UltraZohm Option Z
slave (XCPlite engine on the R5, A53 UDP<->OCM gateway).

Purpose
-------
Verify the XCP path END TO END *without CANape and without an A2L file*: open a
UDP socket, send an XCP CONNECT, then read any R5 variable by name (resolved
from Baremetal.elf) with SHORT_UPLOAD, stream one through a real DAQ list, or
run the DAQ throughput stress and print the ECU-side loss counters afterwards.

Requirements
------------
- Python 3.7+ (standard library only -- no pip installs).
- Both apps flashed from this branch: Baremetal with XCP_ENGINE_R5_ENABLE 1 and
  FreeRTOS with LOGGING_PATH_XCP_R5_GATEWAY 1, board reachable over the network.
- The board's IP address: the A53 prints the XCP endpoint on the serial console
  once the network is up (see option_z/TEST_PLAN.md).

Usage
-----
    python xcp_poll.py --ip 192.168.1.42                # connectivity: CONNECT only
    python xcp_poll.py --ip 192.168.1.42 --watch xcp_r5_cycle_count:u32
    python xcp_poll.py --ip 192.168.1.42 --daq          # DAQ smoke test
    python xcp_poll.py --ip 192.168.1.42 --stress       # DAQ throughput stress
    python xcp_poll.py --ip 192.168.1.42 --stress --stress-bytes 4000 --daq-seconds 60

With no mode flag it only CONNECTs and prints MAX_CTO/MAX_DTO -- that already
proves the UDP + gateway + OCM + engine round trip.

Symbol names are resolved from the freshly built R5 ELF with the Vitis 'nm'
tool (--elf / --nm to override); an address can also be given as 0xADDR.
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

# --- DAQ event channels of the Option Z R5 slave ----------------------------
# Created in xcp_r5_init() (xcptl_ocm.c) and declared in CANape/UZ_XCP/uz.A2L.
# Channel 0 runs at the control-ISR rate, 1..4 are derived time slices.
R5_EVENT_NAMES = {0: "DAQ_R5", 1: "daq_1ms", 2: "daq_10ms",
                  3: "daq_100ms", 4: "daq_1s"}

# Repo-relative default locations (this file lives in <repo>/tools/xcp_test/).
_REPO = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
DEFAULT_ELF_R5 = os.path.join(
    _REPO, "vitis", "workspace", "Baremetal", "Debug", "Baremetal.elf")
DEFAULT_ELF = DEFAULT_ELF_R5  # the Option Z slave is the R5: its ELF holds the symbols
DEFAULT_NM_R5 = r"C:\Xilinx\Vitis\2022.2\gnu\armr5\nt\gcc-arm-none-eabi\bin\armr5-none-eabi-nm.exe"
DEFAULT_NM = DEFAULT_NM_R5


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
        """Send one XCP packet, return the response packet (header stripped).
        Each attempt ends after the socket timeout even while DAQ runs: the
        DAQ datagrams keep every single recv short, so the socket timeout
        alone would wait forever for a lost response."""
        wait_s = self.sock.gettimeout() or 1.0
        for _ in range(retries):
            hdr = struct.pack("<HH", len(packet), self.ctr & 0xFFFF)
            self.ctr += 1
            self.sock.sendto(hdr + packet, self.addr)
            deadline = time.monotonic() + wait_s
            # A datagram may hold several concatenated TL frames (e.g. a DAQ
            # segment). Skip DAQ (pid < 0xFC) and async EV/SERV; return RES/ERR.
            try:
                while True:
                    data, _src = self.sock.recvfrom(4096)
                    for pkt in iter_tl_frames(data):
                        if pkt[0] in (PID_RES, PID_ERR):
                            return pkt
                    if time.monotonic() > deadline:
                        break
            except socket.timeout:
                pass
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

    def daq_timestamp_tick_s(self):
        """Duration of one DAQ timestamp tick in seconds, from
        GET_DAQ_RESOLUTION_INFO: unit = bits 4-7 of the timestamp mode (0 =
        1 ns ... 9 = 1 s, 10-12 = 1-100 ps), times the ticks per unit."""
        resp = self._cmd_checked("GET_DAQ_RESOLUTION_INFO", bytes([0xD9]))
        mode = resp[5]
        ticks = struct.unpack_from("<H", resp, 6)[0]
        unit = mode >> 4
        if (mode & 0x07) != 4:
            raise RuntimeError("DAQ timestamps are not 32-bit (mode 0x%02X)" % mode)
        return ticks * 10.0 ** (unit - 9 if unit <= 9 else unit - 22)

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

    def daq_setup_stress(self, base, odts, event=0, prescaler=1):
        """Dynamic DAQ for throughput stress: 1 list with len(odts) ODTs;
        odts[i] is the list of entry sizes of ODT i (stress_geometry). The
        entries read `base` + running offset. Timestamped.
        Returns the FIRST_PID of the DAQ list."""
        n_odts = len(odts)
        self._cmd_checked("FREE_DAQ", bytes([0xD6]))
        self._cmd_checked("ALLOC_DAQ", bytes([0xD5, 0x00]) + struct.pack("<H", 1))
        self._cmd_checked("ALLOC_ODT",
                          bytes([0xD4, 0x00]) + struct.pack("<H", 0) + bytes([n_odts]))
        for odt, entries in enumerate(odts):
            self._cmd_checked("ALLOC_ODT_ENTRY",
                              bytes([0xD3, 0x00]) + struct.pack("<H", 0) +
                              bytes([odt, len(entries)]))
        off = 0
        for odt, entries in enumerate(odts):
            self._cmd_checked("SET_DAQ_PTR",
                              bytes([0xE2, 0x00]) + struct.pack("<H", 0) + bytes([odt, 0]))
            for size in entries:  # WRITE_DAQ advances the entry pointer
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


def run_daq(xcp, item, seconds, event=0):
    """DAQ smoke test: stream one variable via a 1-list/1-ODT DAQ session."""
    label, a, fmt, size = item
    print("[i] DAQ target: %s @ 0x%08X (%d bytes), event %d (%s), %gs" %
          (label, a, size, event, R5_EVENT_NAMES.get(event, "?"), seconds))
    tick_s = xcp.daq_timestamp_tick_s()
    first_pid = xcp.daq_setup_single(a, size, event=event)
    print("[+] DAQ RUNNING (first_pid=0x%02X, timestamp tick %g s) -- collecting ...\n" %
          (first_pid, tick_s))
    n = 0
    shown = 0
    prev_ts = None
    span_ticks = 0  # unwrapped: the 32-bit timestamp wraps (every 42.9 s at 10 ns)
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
                if prev_ts is not None:
                    span_ticks += (ts - prev_ts) & 0xFFFFFFFF
                prev_ts = ts
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
    span_s = max(span_ticks, 1) * tick_s
    print("\n[+] DAQ OK: %d samples in %.2fs of target time (~%.0f Hz)" %
          (n, span_s, (n - 1) / span_s if n > 1 else 0.0))
    return 0


# R5 diagnostic counters sampled before/after a stress run (all u32; resolved
# from Baremetal.elf). The A53 gateway counters are read through their OCM
# mirror (A53_DIAG_COUNTERS below).
R5_DIAG_COUNTERS = [
    "xcp_r5_cycle_count", "xcp_r5_queue_lost", "xcp_r5_cto_sent",
    "xcp_r5_cto_dropped", "xcp_r5_cmd_records", "xcp_r5_cmd_waits",
    "xcp_r5_cmd_oversize_drop", "xcp_r5_cmd_ring_bad", "xcp_r5_daq_ipis",
    "xcp_r5_rsp_ipis",
]
R5_DIAG_ALARMS = ("xcp_r5_cto_dropped", "xcp_r5_queue_lost", "xcp_r5_cmd_ring_bad")


# A53 gateway counters, mirrored every IPI to fixed OCM addresses
# (shared/ocm_xcp_ring.h enum ocm_xcp_gw_diag_slot; keep in sync).
# Readable through the R5 engine by absolute address, no ELF needed.
A53_DIAG_ADDR = 0xFFFFC008
A53_DIAG_COUNTERS = [
    "xcp_gw_ring_bad", "xcp_gw_daq_level_max", "xcp_gw_cmd_dropped",
    "xcp_gw_drain_capped", "xcp_gw_txq_dropped", "xcp_gw_ctoq_dropped",
    "xcp_gw_cmd_records", "xcp_gw_daq_records", "xcp_gw_tx_malformed_drop",
    "xcp_gw_rx_malformed_drop", "xcp_gw_sendto_err", "xcp_gw_sendto_drop",
    "xcp_gw_ipi_count", "xcp_gw_txq_level", "xcp_gw_master_lost",
    # A53 time profile (gateway XCP_GW_PROFILE): microsecond sums and counts,
    # evaluated by print_a53_prof() instead of being listed as counters.
    "xcp_gw_prof_now_us", "xcp_gw_prof_idle_us", "xcp_gw_prof_ipi_us",
    "xcp_gw_prof_ipi_max_us", "xcp_gw_prof_chain_us", "xcp_gw_prof_enq_us",
    "xcp_gw_prof_records", "xcp_gw_prof_tx_us", "xcp_gw_prof_sendto_us",
    "xcp_gw_prof_sendto_n", "xcp_gw_prof_tx_kb", "xcp_gw_prof_sendto_max_us",
]
A53_DIAG_GAUGES = ("xcp_gw_txq_level", "xcp_gw_daq_level_max")  # levels: print the value, not a delta
A53_DIAG_ALARMS = ("xcp_gw_txq_dropped", "xcp_gw_ctoq_dropped", "xcp_gw_tx_malformed_drop",
                   "xcp_gw_rx_malformed_drop", "xcp_gw_sendto_drop", "xcp_gw_ring_bad",
                   "xcp_gw_cmd_dropped")
# OCM DAQ ring size (OCM_XCP_DAQ_DATA_LEN), for xcp_gw_daq_level_max.
DAQ_RING_BYTES = 0x1C000

# Loss the transport counter cannot show: data dropped in the ECU before the
# A53 stamps the CTR at sendto time, so the wire has no gap. A stress run
# fails if one of these moved, and also if they could not be read (the
# hidden loss is then unknown). (core, counter, what was lost)
HIDDEN_LOSS = (
    ("r5", "xcp_r5_queue_lost", "DTOs refused by the full OCM DAQ ring (R5)"),
    ("a53", "xcp_gw_txq_dropped", "DAQ segments dropped by the full A53 DAQ queue"),
)


def read_a53_diag(xcp):
    """Read the mirrored A53 gateway counters (one SHORT_UPLOAD). Returns
    {name: value}, or {} if the read failed."""
    n = len(A53_DIAG_COUNTERS)
    try:
        raw = xcp.short_upload(A53_DIAG_ADDR, 4 * n)
    except (TimeoutError, RuntimeError):
        return {}
    return dict(zip(A53_DIAG_COUNTERS, struct.unpack("<%dI" % n, raw)))


def print_a53_prof(pre, post):
    """Where the A53 spends its time (gateway XCP_GW_PROFILE): the idle probe
    gives the free CPU; IPI hook, tx task and lwip_sendto are wall times
    (they include interrupts that hit them)."""
    if not pre or not post:
        return

    def d(name):
        return (post[name] - pre[name]) & 0xFFFFFFFF

    win = d("xcp_gw_prof_now_us")
    if win == 0:
        print("    A53 gateway profile: no data (gateway built without XCP_GW_PROFILE?)")
        return

    def pct(us):
        return 100.0 * us / win

    ipis = d("xcp_gw_ipi_count")
    rec = d("xcp_gw_prof_records")
    sends = d("xcp_gw_prof_sendto_n")
    idle, ipi, tx, snd = (d("xcp_gw_prof_idle_us"), d("xcp_gw_prof_ipi_us"),
                          d("xcp_gw_prof_tx_us"), d("xcp_gw_prof_sendto_us"))
    print("    A53 gateway profile while DAQ ran (%.1f s):" % (win / 1e6))
    print("      A53 time split         idle %5.1f %%   IPI hook %5.1f %%   tx task %5.1f %%"
          "   other (lwIP RX, GEM IRQs, other tasks) %5.1f %%"
          % (pct(idle), pct(ipi), pct(tx), 100.0 - pct(idle) - pct(ipi) - pct(tx)))
    if ipis:
        print("      IPI hook               %d/s, avg %5.1f us, max %5.1f us (last full second)"
              % (ipis / (win / 1e6), ipi / ipis, post["xcp_gw_prof_ipi_max_us"]))
    if rec:
        print("      per DAQ segment        copy out of OCM %5.2f us, into the queue %5.2f us"
              "   (%.1f segments per IPI)"
              % (d("xcp_gw_prof_chain_us") / rec, d("xcp_gw_prof_enq_us") / rec,
                 rec / ipis if ipis else 0.0))
    if sends:
        kb = d("xcp_gw_prof_tx_kb")
        print("      datagrams              %d/s, avg %4.0f B; lwip_sendto avg %5.1f us, max %6.1f us;"
              " tx task per datagram %5.1f us"
              % (sends / (win / 1e6), 1024.0 * kb / sends, snd / sends,
                 post["xcp_gw_prof_sendto_max_us"], tx / sends))


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


# Largest single ODT entry the R5 engine accepts (XCP_MAX_ODT_ENTRY_SIZE in
# xcplib_r5_cfg.h, GET_DAQ_RESOLUTION_INFO MAX_ODT_ENTRY_SIZE_DAQ). WRITE_DAQ
# with a bigger entry is refused with ERR_OUT_OF_RANGE (0x22).
MAX_ODT_ENTRY_SIZE = 240


def stress_geometry(target_bytes, max_dto):
    """Layout of a stress list: one list of entry sizes per ODT. XCPlite DTO
    overhead per ODT: 4-byte header ([odt][fill][daq u16]) + 4-byte timestamp
    in ODT0 only (xcplite.c: max payload = MAX_DTO - 4 - (odt==0 ? 4 : 0)).
    Each entry is at most MAX_ODT_ENTRY_SIZE, and an ODT is filled with as
    many entries as fit. That gives the fewest ODTs for the slave's MAX_DTO,
    like CANape does, and the ODT count is what costs ISR time on the R5
    (one DAQ message per ODT and cycle)."""
    odts = []
    remaining = target_bytes
    while remaining > 0 and len(odts) < 200:
        budget = (max_dto - 4 - (4 if not odts else 0)) & ~3
        entries = []
        while remaining > 0 and budget > 0 and len(entries) < 255:
            size = min(remaining, budget, MAX_ODT_ENTRY_SIZE)
            entries.append(size)
            remaining -= size
            budget -= size
        odts.append(entries)
    return odts


# R5 transport profile (struct xcp_r5_prof, xcp_r5.h XCP_R5_PROFILE). Layout
# version 3 (OCM rings): 8 x u32, 7 x u64 = 88 bytes. Keep in sync with xcp_r5.h.
PROF_FMT = "<8I7Q"
PROF_FIELDS = ("version cpu_hz reset event_calls event_cyc_max publish_cyc_max ipis "
               "commands elapsed_cyc event_cyc sample_cyc publish_cyc daq_bytes "
               "isr_ns_all cmd_cyc").split()


def prof_reset(xcp, addr):
    """Ask the R5 to restart its profile (field `reset`, offset 8). SET_MTA +
    DOWNLOAD; the next control cycle clears the sums."""
    xcp._cmd_checked("SET_MTA", bytes([0xF6, 0, 0, 0]) + struct.pack("<I", addr + 8))
    xcp._cmd_checked("DOWNLOAD", bytes([0xF0, 4]) + struct.pack("<I", 1))


def prof_read(xcp, addr):
    raw = xcp.short_upload(addr, struct.calcsize(PROF_FMT))
    if struct.unpack_from("<I", raw)[0] != 3:
        return None  # another transport generation: no profile
    return dict(zip(PROF_FIELDS, struct.unpack(PROF_FMT, raw)))


def print_prof(p):
    """Where the R5 spends its XCP time: the XCP part of the control ISR
    (sampling into the DAQ ring, publishing), the ISR in total, and the
    command execution in the main loop."""
    hz = float(p["cpu_hz"])
    calls = p["event_calls"]
    if not calls or not hz or not p["elapsed_cyc"]:
        print("    R5 transport profile: no data")
        return

    def us(cyc):
        return 1e6 * cyc / hz

    elapsed = us(p["elapsed_cyc"])
    isr = p["isr_ns_all"] / 1000.0
    print("    R5 transport profile while DAQ ran (%.1f s, %d control cycles):" % (elapsed / 1e6, calls))
    print("      per control cycle      ISR %5.2f us; xcp_r5_event() avg %5.2f us, max %5.2f us"
          % (isr / calls, us(p["event_cyc"]) / calls, us(p["event_cyc_max"])))
    print("        of it                sampling into the ring %5.2f us, publish %5.2f us (max %5.2f us)"
          % (us(p["sample_cyc"]) / calls, us(p["publish_cyc"]) / calls, us(p["publish_cyc_max"])))
    kb = p["daq_bytes"] / 1024.0
    if kb > 0:
        print("      DAQ ring               %.1f MB = %.1f MB/s; publish %5.2f us/KB; sampling %5.2f us/KB"
              % (p["daq_bytes"] / 1e6, p["daq_bytes"] / elapsed, us(p["publish_cyc"]) / kb,
                 us(p["sample_cyc"]) / kb))
    print("      IPIs from the ISR      %d = %.0f/s" % (p["ipis"], p["ipis"] / (elapsed / 1e6)))
    print("      R5 time split          control ISR %5.1f %%   commands %5.1f %% (%d commands)"
          % (100.0 * isr / elapsed, 100.0 * us(p["cmd_cyc"]) / elapsed, p["commands"]))


class CtrCheck:
    """Exact check of the XCP transport counter of the received frames.

    The A53 stamps the counter on every frame when it sends the datagram, one
    step per frame, so a clean path delivers every value exactly once and in
    order. The check keeps the last WINDOW values: a value that leaves the
    window without having arrived is missing, one that arrives a second time
    is a duplicate, one that arrives behind a later value is late.

    Duplicates must not be offset against gaps: a datagram sent with the
    contents of a later one (the A53 transmit buffer reused before the DMA
    read it, fixed 2026-11-23) shows up as a gap followed by a backward step,
    and counting the backward frames as "late, not lost" hid the loss.
    A 16-bit counter cannot place a value more than half its range away, so
    the window is 2^15 values.
    """
    WINDOW = 1 << 15

    def __init__(self):
        self._mask = self.WINDOW - 1
        # 1 = arrived; the slots start as "arrived" because the values before
        # the first frame are not expected.
        self._seen = bytearray(b"\x01") * self.WINDOW
        self.hi = None     # newest counter value, unwrapped
        self.lost = 0      # left the window without arriving
        self.dup = 0       # arrived a second time
        self.late = 0      # arrived after a later value
        self.too_old = 0   # further back than the window: late or duplicate

    def add(self, ctr):
        hi = self.hi
        if hi is None:
            self.hi = ctr
            return
        seen = self._seen
        mask = self._mask
        d = (ctr - hi) & 0xFFFF
        if d == 1:  # the normal case
            i = (hi + 1) & mask
            if not seen[i]:
                self.lost += 1  # value hi + 1 - WINDOW never arrived
            seen[i] = 1
            self.hi = hi + 1
        elif d and d < 0x8000:  # forward with d - 1 values skipped
            for s in range(hi + 1, hi + d + 1):
                i = s & mask
                if not seen[i]:
                    self.lost += 1
                seen[i] = 0
            seen[(hi + d) & mask] = 1
            self.hi = hi + d
        else:  # the newest value again, or backwards
            back = (hi - ctr) & 0xFFFF
            if back >= self.WINDOW:
                self.too_old += 1
                return
            i = (hi - back) & mask
            if seen[i]:
                self.dup += 1
            else:
                seen[i] = 1
                self.late += 1

    def missing(self):
        """Values that have not arrived: lost for good plus those still open
        in the window (counted as lost at the end of a run)."""
        return self.lost + self._seen.count(0)


def run_stress(xcp, args, max_dto):
    """DAQ throughput stress: one wide multi-ODT list on args.daq_event (by
    default the full control rate). Verifies the CP7 gateway path under load: UDP batching
    (frames/datagram), the transport CTR of every frame (CtrCheck), and the
    R5/A53 drop counters. The CTR is stamped by the A53 at sendto time, so
    data dropped before that (HIDDEN_LOSS) leaves no gap on the wire: those
    counters fail the run on their own."""
    odts = stress_geometry(args.stress_bytes, max_dto)
    per_cycle = sum(sum(entries) for entries in odts)
    # The OCM DAQ ring holds 112 KB: what the A53 does not take in time is
    # refused at the source and counted in xcp_r5_queue_lost.
    print("[i] stress: %d B/cycle in %d ODTs (MAX_DTO %d) @ base 0x%08X, event %d (%s), %gs" %
          (per_cycle, len(odts), max_dto, args.stress_base, args.daq_event,
           R5_EVENT_NAMES.get(args.daq_event, "?"), args.daq_seconds))
    print("[i]         (at 10 kHz control rate = %.0f Mbit/s DAQ payload)" %
          (per_cycle * 10e3 * 8 / 1e6))

    diag_addrs = nm_lookup(DEFAULT_ELF_R5, args.nm, R5_DIAG_COUNTERS)
    pre = read_r5_diag(xcp, diag_addrs)
    if not pre:
        print("[!] R5 diag counters not resolvable (no Baremetal.elf?) -- skipping deltas")
    pre_a53 = read_a53_diag(xcp)
    prof_addr = nm_lookup(DEFAULT_ELF_R5, args.nm, ["xcp_r5_prof"]).get("xcp_r5_prof")
    prof = None
    if prof_addr is not None:
        try:
            prof_reset(xcp, prof_addr)
        except (TimeoutError, RuntimeError) as e:
            print("[!] R5 transport profile not resettable (%s) -- skipping it" % e)
            prof_addr = None

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

    tick_s = xcp.daq_timestamp_tick_s()
    first_pid = xcp.daq_setup_stress(args.stress_base, odts,
                                     event=args.daq_event,
                                     prescaler=args.prescaler)
    print("[+] DAQ RUNNING (first_pid=0x%02X, %d ODTs, timestamp tick %g s) -- collecting ...\n" %
          (first_pid, len(odts), tick_s))

    buf = bytearray(4096)
    dgrams = frames = payload = cycles = 0
    ctr_check = CtrCheck()
    prev_ts = None
    span_ticks = 0  # unwrapped: the 32-bit timestamp wraps (every 42.9 s at 10 ns)
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
                print("    %5.1fs  %6d dgrams/s  %7.2f Mbit/s payload  ctr missing=%d dup=%d" %
                      (now - t0, dgrams - tick_dgrams,
                       (payload - tick_payload) * 8 / 1e6,
                       ctr_check.missing(), ctr_check.dup))
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
                ctr_check.add(ctr)
                # ODT0 DTO: [odt u8][fill u8][daq u16][ts u32][data]
                if buf[off + 4] == first_pid and dlc >= 8:
                    ts = struct.unpack_from("<I", buf, off + 8)[0]
                    if prev_ts is not None:
                        span_ticks += (ts - prev_ts) & 0xFFFFFFFF
                    prev_ts = ts
                    cycles += 1
                off += 4 + dlc
    finally:
        if prof_addr is not None:
            try:  # while DAQ still runs; skipped DTOs no longer count here
                prof = prof_read(xcp, prof_addr)
            except (TimeoutError, RuntimeError):
                prof = None
        a53_prof_post = read_a53_diag(xcp)  # same window as the R5 profile
        xcp.daq_stop()
        xcp.drain()

    wall_s = max(time.monotonic() - t0, 1e-6)
    post = read_r5_diag(xcp, diag_addrs)
    post_a53 = read_a53_diag(xcp)

    print("\n[+] stress summary (%.2fs wall):" % wall_s)
    print("    datagrams        %10d   (%.0f/s, %.1f frames/datagram)" %
          (dgrams, dgrams / wall_s, frames / dgrams if dgrams else 0.0))
    print("    TL frames        %10d   (%.0f/s)" % (frames, frames / wall_s))
    print("    DAQ payload      %10d B (%.2f Mbit/s; wire ~%.2f Mbit/s)" %
          (payload, payload * 8 / wall_s / 1e6,
           (payload + 4 * frames + 42 * dgrams) * 8 / wall_s / 1e6))
    if cycles > 1:
        span_s = max(span_ticks, 1) * tick_s
        print("    event cycles     %10d   (~%.0f Hz of target time)" %
              (cycles, (cycles - 1) / span_s))
    missing = ctr_check.missing()
    bad = missing + ctr_check.dup + ctr_check.too_old
    print("    ctr missing      %10d frames (%.5f%%)%s" %
          (missing, 100.0 * missing / frames if frames else 0.0,
           "  <-- lost at/after sendto (lwIP, wire, PC rx)" if missing else ""))
    print("    ctr duplicated   %10d frames%s" %
          (ctr_check.dup, "  <-- sent twice: the A53 transmit path" if ctr_check.dup else ""))
    if ctr_check.late:
        print("    ctr late        %10d frames (arrived after a later one; CANape counts "
              "these as counter errors too)" % ctr_check.late)
    if ctr_check.too_old:
        print("    ctr too old      %10d frames (more than %d values back: late or "
              "duplicated)  <-- investigate" % (ctr_check.too_old, CtrCheck.WINDOW))
    if pre and post:
        print("    R5 counter deltas over the run:")
        for name in R5_DIAG_COUNTERS:
            if name in pre and name in post:
                d = (post[name] - pre[name]) & 0xFFFFFFFF
                flag = ""
                if d and name in R5_DIAG_ALARMS:
                    flag = "  <-- investigate"
                print("      %-24s +%d%s" % (name, d, flag))
    if pre_a53 and post_a53:
        print("    A53 gateway counter deltas over the run (OCM mirror):")
        for name in A53_DIAG_COUNTERS:
            if name.startswith("xcp_gw_prof_"):
                continue  # time profile: see print_a53_prof
            if name in pre_a53 and name in post_a53:
                if name in A53_DIAG_GAUGES:
                    extra = (" (%.1f %% of the DAQ ring)" % (100.0 * post_a53[name] / DAQ_RING_BYTES)
                             if name == "xcp_gw_daq_level_max" else " (level now)")
                    print("      %-26s  %d%s" % (name, post_a53[name], extra))
                    continue
                d = (post_a53[name] - pre_a53[name]) & 0xFFFFFFFF
                flag = ""
                if d and name in A53_DIAG_ALARMS:
                    flag = "  <-- investigate"
                print("      %-26s +%d%s" % (name, d, flag))
        print("    (on missing frames: xcp_gw_sendto_drop > 0 = ECU dropped it after retries, "
              "0 = wire/PC-side loss)")
    else:
        print("    (A53 gateway counters not readable)")
    if prof:
        print_prof(prof)
    print_a53_prof(pre_a53, a53_prof_post)
    hidden, unread = [], []
    for core, name, what in HIDDEN_LOSS:
        a, b = (pre, post) if core == "r5" else (pre_a53, post_a53)
        if a and b and name in a and name in b:
            d = (b[name] - a[name]) & 0xFFFFFFFF
            if d:
                hidden.append("%d %s (%s)" % (d, what, name))
        else:
            unread.append(name)
    if hidden:
        print("\n[x] dropped in the ECU before the transport counter (no CTR gap on the wire):")
        for line in hidden:
            print("      " + line)
    if frames == 0:
        print("\n[x] no DTOs received -- stress FAILED")
        return 1
    if bad:
        print("\n[+] stress completed WITH MISSING OR DUPLICATED FRAMES -- see counters")
        return 2
    if hidden:
        print("\n[x] stress FAILED: ECU-side DAQ loss (see above)")
        return 3
    if unread:
        print("\n[x] stress FAILED (unverified): %s not readable, ECU-side loss unknown "
              "(a starved R5 main loop takes no commands)" % ", ".join(unread))
        return 4
    print("\n[+] stress PASSED (every counter value once%s, no ECU-side drops)" %
          (", %d late" % ctr_check.late if ctr_check.late else ", in order"))
    return 0


def main():
    ap = argparse.ArgumentParser(description="Poll the UltraZohm XCPlite slave over UDP (no CANape needed).")
    ap.add_argument("--ip", required=True, help="UltraZohm board IP address")
    ap.add_argument("--port", type=int, default=5556, help="XCP UDP port (default 5556)")
    ap.add_argument("--interval", type=float, default=0.2, help="poll period in seconds (default 0.2)")
    ap.add_argument("--elf", default=DEFAULT_ELF, help="ELF to resolve symbol names from "
                    "(default: the workspace Baremetal.elf, the Option Z R5 slave)")
    ap.add_argument("--nm", default=DEFAULT_NM, help="path to nm (default: the Vitis armr5 nm)")
    ap.add_argument("--watch", action="append", default=[], metavar="NAME|0xADDR[:TYPE]",
                    help="arbitrary read (repeatable). TYPE in u8/u16/u32/i32/f32/f64 "
                         "(default f32). NAME resolved from --elf, falling back to "
                         "Baremetal.elf (the Option Z R5 engine, arbitrary addressing).")
    ap.add_argument("--daq", action="store_true",
                    help="DAQ smoke test: stream the first --watch item (default "
                         "xcp_r5_cycle_count:u32) via a real DAQ list on --daq-event")
    ap.add_argument("--daq-seconds", type=float, default=None,
                    help="capture duration (default: 3s for --daq, 10s for --stress)")
    ap.add_argument("--daq-event", type=int, default=0, choices=sorted(R5_EVENT_NAMES),
                    help="DAQ event channel for --daq/--stress: "
                         + ", ".join("%d=%s" % (k, v) for k, v in sorted(R5_EVENT_NAMES.items()))
                         + " (default 0 = control-ISR rate)")
    ap.add_argument("--stress", action="store_true",
                    help="DAQ throughput stress: one wide multi-ODT list on --daq-event "
                         "(default the control rate). Reports Mbit/s, frames/datagram "
                         "(CP7 batching), transport-CTR gaps (= lost records) and "
                         "the R5/A53 counter deltas. Exit 0 = passed, 1 = no data, "
                         "2 = CTR gaps or duplicates, 3 = ECU-side loss the CTR cannot "
                         "show (xcp_r5_queue_lost, xcp_gw_txq_dropped), 4 = those "
                         "counters not readable.")
    ap.add_argument("--stress-bytes", type=int, default=2000,
                    help="target DAQ payload bytes per control cycle (default 2000 "
                         "= 160 Mbit/s at 10 kHz; the OCM window carries ~30000 "
                         "per 100 us sweep, so Ethernet is the practical limit)")
    ap.add_argument("--stress-base", type=lambda x: int(x, 0), default=0xFFFC1000,
                    help="measurement block base address (default 0xFFFC1000: OCM bank 0 "
                         "behind the boot handshakes, 60 KB, unused at run time, allow-listed)")
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
            return run_daq(xcp, items[0], args.daq_seconds, event=args.daq_event)

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
