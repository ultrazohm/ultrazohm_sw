#!/usr/bin/env python3
"""
isr_jitter.py - record the timing of the UltraZohm control ISR in every
control cycle over XCP (Option Z) and show where its jitter comes from.

One DAQ list on DAQ_R5 carries, for every control cycle:
  - the DAQ time stamp: the start of ISR_Control (uz_SystemTime timer, 10 ns),
  - timingR5.isr_period_us, .isr_execution_time_us (of the previous cycle)
    and .interrupt_counter,
  - uz_isr_diag (include/isr_diag.h, firmware built with UZ_ISR_DIAG 1): the
    sections of the previous ISR in CPU cycles, three PMU event counts and
    what the main loop was doing when the current interrupt arrived.
Optional load that resembles a CANape measurement:
  --load-r5 N        N more bytes per cycle on DAQ_R5, read from Global_Data
  --load-1ms canape  the 23 diagnostic counters of the CANape project on
                     daq_1ms (92 bytes, 9 ODT entries); or a number of bytes

The evaluation shows the spread of execution time, period and start delay,
the average over the phase of a 1 ms period (the time slices fire once per
ms), the sections that grow in the slow cycles, and the start delay per
main-loop phase.

Requirements: Python 3.7+, no packages. Symbols come from the workspace
Baremetal.elf (--elf): flash exactly that build.

Usage:
    python isr_jitter.py --ip 192.168.1.233 --seconds 20
    python isr_jitter.py --ip 192.168.1.233 --seconds 20 --load-r5 160 --load-1ms canape
    python isr_jitter.py --ip 192.168.1.233 --pmu 0x40,0x41,0x44 --out run.bin
    python isr_jitter.py --analyze run.bin
"""

import argparse
import array
import json
import os
import socket
import struct
import subprocess
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import xcp_poll as xp  # noqa: E402

CPU_HZ = 500e6                 # R5 clock (XPAR_CPU_CORTEXR5_0_CPU_CLK_FREQ_HZ)
TIMING_LEN = 16                # timingR5: isr_period_us f32, isr_execution_time_us f32, interrupt_counter u64
DIAG_LEN = 32                  # uz_isr_diag: record (28) + entry_main_phase + 3 reserved
DIAG_PMU_EVENTS_OFF = 32       # uz_isr_diag.pmu_events (writable)
DIAG_FMT = "<I8H3HHB3x"        # seq, tic adc encoder pwm xcp xcp_base xcp_slices total, pmu[3], reserved, phase
SECTIONS = ["tic", "adc", "encoder", "pwm", "xcp", "xcp_base", "xcp_slices", "total"]
MAIN_PHASES = {0: "other", 1: "xcp pacing", 2: "xcp commands", 3: "xcp copy", 4: "xcp flush"}
PMU_NAMES = {0x01: "I-cache miss", 0x03: "D-cache miss", 0x04: "D-cache access",
             0x06: "data read", 0x07: "data write", 0x08: "instructions",
             0x40: "instr stall cyc", 0x41: "data stall cyc", 0x42: "D-cache write-back",
             0x43: "ext mem request", 0x44: "LSU stall cyc", 0x45: "store buf drain",
             0x58: "I-cache access", 0x11: "cycles"}
OCM_GW_DIAG = (0xFFFFC008, 60)  # xcp_gw_* slots 0..14 in the XCP_IN header mirror
CANAPE_1MS_R5 = ["xcp_r5_write_denied", "xcp_r5_tx_oversize_drop", "xcp_r5_sweep_gap_max_us",
                 "xcp_r5_queue_lost", "xcp_r5_out_overwritten", "xcp_r5_out_held",
                 "xcp_r5_cto_dropped", "ocm_xcp_w_dropped"]
REC = struct.Struct("<IIff%ds" % DIAG_LEN)  # ts, counter low word, period, exec, diag
MAGIC = b"ISRJITTER1\n"
MAX_ENTRY = 240


def nm_symbols(elf, nm):
    """name -> (address, size) of all sized symbols (nm -S)."""
    tool = nm if os.path.isfile(nm) else "nm"
    out = subprocess.check_output([tool, "-S", elf], text=True, stderr=subprocess.DEVNULL)
    syms = {}
    for line in out.splitlines():
        p = line.split()
        if len(p) == 4:
            try:
                syms[p[3]] = (int(p[0], 16), int(p[1], 16))
            except ValueError:
                pass
    return syms


def split_entries(addr, size):
    out = []
    while size > 0:
        n = min(MAX_ENTRY, size)
        out.append((addr, n))
        addr += n
        size -= n
    return out


def group_odts(entries, max_dto):
    """Fill ODTs in order up to MAX_DTO - 4 (header), ODT 0 also holds the
    4-byte time stamp. Entries keep their order, so the first ones sit at
    fixed offsets of ODT 0."""
    odts, cur, room = [], [], max_dto - 8
    for e in entries:
        if cur and e[1] > room:
            odts.append(cur)
            cur, room = [], max_dto - 4
        cur.append(e)
        room -= e[1]
    odts.append(cur)
    return odts


def daq_setup(x, lists):
    """lists: [(event, odts)] -> first PID of every list. Dynamic DAQ,
    time stamps on, prescaler 1, all lists started together."""
    x._cmd_checked("FREE_DAQ", bytes([0xD6]))
    x._cmd_checked("ALLOC_DAQ", bytes([0xD5, 0]) + struct.pack("<H", len(lists)))
    for d, (_ev, odts) in enumerate(lists):
        x._cmd_checked("ALLOC_ODT", bytes([0xD4, 0]) + struct.pack("<H", d) + bytes([len(odts)]))
    for d, (_ev, odts) in enumerate(lists):
        for o, entries in enumerate(odts):
            x._cmd_checked("ALLOC_ODT_ENTRY", bytes([0xD3, 0]) + struct.pack("<H", d) + bytes([o, len(entries)]))
    for d, (_ev, odts) in enumerate(lists):
        for o, entries in enumerate(odts):
            x._cmd_checked("SET_DAQ_PTR", bytes([0xE2, 0]) + struct.pack("<H", d) + bytes([o, 0]))
            for addr, size in entries:
                x._cmd_checked("WRITE_DAQ", bytes([0xE1, 0xFF, size, 0]) + struct.pack("<I", addr))
    pids = []
    for d, (ev, _odts) in enumerate(lists):
        x._cmd_checked("SET_DAQ_LIST_MODE", bytes([0xE0, 0x10]) + struct.pack("<HH", d, ev) + bytes([1, 0]))
        resp = x._cmd_checked("START_STOP_DAQ_LIST", bytes([0xDE, 0x02]) + struct.pack("<H", d))
        pids.append(resp[1] if len(resp) > 1 else 0)
    x._cmd_checked("START_STOP_SYNCH", bytes([0xDD, 0x01]))
    return pids


def write_u32(x, addr, value):
    x._cmd_checked("SET_MTA", bytes([0xF6, 0, 0, 0]) + struct.pack("<I", addr))
    x._cmd_checked("DOWNLOAD", bytes([0xF0, 4]) + struct.pack("<I", value))


def record(args):
    syms = nm_symbols(args.elf, args.nm)
    if "timingR5" not in syms:
        raise SystemExit("[x] timingR5 not found in %s" % args.elf)
    have_diag = "uz_isr_diag" in syms
    entries = [(syms["timingR5"][0], TIMING_LEN)]
    if have_diag:
        entries.append((syms["uz_isr_diag"][0], DIAG_LEN))
    else:
        print("[!] uz_isr_diag not in the ELF (UZ_ISR_DIAG 0): timing only")
    if args.load_r5 > 0:
        base, size = syms[args.load_symbol]
        if args.load_r5 > size:
            print("[!] %s has %d bytes, the load reads past it" % (args.load_symbol, size))
        entries += split_entries(base, args.load_r5)
    lists = [(0, None, entries)]
    load_1ms = []
    if args.load_1ms == "canape":
        load_1ms = [split_entries(*OCM_GW_DIAG)[0]] + [(syms[n][0], 4) for n in CANAPE_1MS_R5]
    elif args.load_1ms not in ("", "none", "0"):
        load_1ms = split_entries(syms[args.load_symbol][0], int(args.load_1ms))
    if load_1ms:
        lists.append((1, None, load_1ms))

    x = xp.XcpUdp(args.ip, args.port)
    x.sock.setsockopt(socket.SOL_SOCKET, socket.SO_RCVBUF, 32 * 1024 * 1024)
    ts_a, cnt_a = array.array("I"), array.array("I")
    per_a, exe_a = array.array("f"), array.array("f")
    diag = bytearray()
    n_1ms = 0
    zero_diag = bytes(DIAG_LEN)
    try:
        info = x.connect()
        x.daq_stop()
        x.drain()
        tick_s = x.daq_timestamp_tick_s()
        if have_diag and args.pmu:
            ev = [int(v, 0) for v in args.pmu.split(",")]
            ev = (ev + [0, 0, 0])[:3]
            write_u32(x, syms["uz_isr_diag"][0] + DIAG_PMU_EVENTS_OFF, ev[0] | ev[1] << 8 | ev[2] << 16)
        pmu_events = struct.unpack("<I", x.short_upload(syms["uz_isr_diag"][0] + DIAG_PMU_EVENTS_OFF, 4))[0] \
            if have_diag else 0
        ql_addr = syms.get("xcp_r5_queue_lost", (None,))[0]
        ql0 = struct.unpack("<I", x.short_upload(ql_addr, 4))[0] if ql_addr else 0
        daq_lists = [(ev, group_odts(ent, info["max_dto"])) for ev, _n, ent in lists]
        per_cycle = sum(s for _a, s in entries)
        print("[i] DAQ_R5: %d bytes per cycle in %d ODT(s)%s" %
              (per_cycle, len(daq_lists[0][1]),
               (", daq_1ms: %d bytes" % sum(s for _a, s in load_1ms)) if load_1ms else ""))
        # DTO header [odt u8][fill u8][daq u16]: the ODT number counts from 0
        # in every list (RELATIVE_WORD_ALIGNED), so the DAQ number tells the
        # lists apart. List 0 = DAQ_R5, list 1 = daq_1ms.
        daq_setup(x, daq_lists)
        need = 8 + TIMING_LEN + (DIAG_LEN if have_diag else 0)
        print("[+] recording %g s ..." % args.seconds)
        x.sock.settimeout(0.5)
        buf = bytearray(65536)
        t_end = time.monotonic() + args.seconds
        while time.monotonic() < t_end:
            try:
                n = x.sock.recv_into(buf)
            except socket.timeout:
                continue
            o = 0
            while o + 4 <= n:
                dlc = buf[o] | buf[o + 1] << 8
                if dlc == 0 or o + 4 + dlc > n:
                    break
                p = o + 4
                if buf[p] == 0 and buf[p + 2] == 0 and buf[p + 3] == 0 and dlc >= need:
                    ts, per, exe, cnt = struct.unpack_from("<IffI", buf, p + 4)
                    ts_a.append(ts)
                    per_a.append(per)
                    exe_a.append(exe)
                    cnt_a.append(cnt)
                    diag += buf[p + 24: p + 24 + DIAG_LEN] if have_diag else zero_diag
                elif buf[p] == 0 and buf[p + 2] == 1 and buf[p + 3] == 0:
                    n_1ms += 1
                o += 4 + dlc
        x.daq_stop()
        x.drain()
        ql1 = struct.unpack("<I", x.short_upload(ql_addr, 4))[0] if ql_addr else 0
    finally:
        x.disconnect()
        x.close()
    meta = {"ip": args.ip, "seconds": args.seconds, "tick_s": tick_s, "have_diag": have_diag,
            "pmu_events": pmu_events, "bytes_r5": per_cycle,
            "bytes_1ms": sum(s for _a, s in load_1ms), "samples_1ms": n_1ms,
            "queue_lost": (ql1 - ql0) & 0xFFFFFFFF, "elf": os.path.abspath(args.elf),
            "time": time.strftime("%Y-%m-%d %H:%M:%S")}
    data = [(ts_a[i], cnt_a[i], per_a[i], exe_a[i], bytes(diag[i * DIAG_LEN:(i + 1) * DIAG_LEN]))
            for i in range(len(ts_a))]
    if args.out:
        with open(args.out, "wb") as f:
            f.write(MAGIC)
            f.write((json.dumps(meta) + "\n").encode())
            for r in data:
                f.write(REC.pack(*r))
        print("[i] written %s (%d samples)" % (args.out, len(data)))
    return meta, data


def load(path):
    with open(path, "rb") as f:
        if f.readline() != MAGIC:
            raise SystemExit("[x] %s is not an isr_jitter.py recording" % path)
        meta = json.loads(f.readline())
        raw = f.read()
    return meta, [REC.unpack_from(raw, o) for o in range(0, len(raw) - REC.size + 1, REC.size)]


# --- evaluation ---------------------------------------------------------------

def pct(sorted_v, p):
    if not sorted_v:
        return float("nan")
    return sorted_v[min(len(sorted_v) - 1, int(round(p / 100.0 * (len(sorted_v) - 1))))]


def stats_line(name, v, unit="us"):
    s = sorted(v)
    if not s:
        return "    %-16s (no data)" % name
    mean = sum(s) / len(s)
    return ("    %-16s mean %7.2f  p50 %7.2f  p99 %7.2f  p99.9 %7.2f  max %7.2f  min %7.2f %s"
            % (name, mean, pct(s, 50), pct(s, 99), pct(s, 99.9), s[-1], s[0], unit))


def median(v):
    s = sorted(v)
    return pct(s, 50)


def fold_profile(phase, values, fold):
    sums = [0.0] * fold
    cnts = [0] * fold
    for ph, v in zip(phase, values):
        sums[ph] += v
        cnts[ph] += 1
    return [sums[i] / cnts[i] if cnts[i] else float("nan") for i in range(fold)]


def print_profile(name, prof, ref, thr):
    marks = ["%2d:%+.2f" % (i, v - ref) for i, v in enumerate(prof) if abs(v - ref) >= thr]
    print("    %-16s ref %6.2f us; phases off by >= %.2f us: %s"
          % (name, ref, thr, " ".join(marks) if marks else "none"))


def analyze(meta, data, spike_us=0.5, fold=None):
    n = len(data)
    print("\n=== %d samples, %s, DAQ_R5 %d B/cycle, daq_1ms %d B (%d samples), queue_lost %d"
          % (n, meta.get("time", ""), meta["bytes_r5"], meta["bytes_1ms"],
             meta["samples_1ms"], meta["queue_lost"]))
    if n < 100:
        print("[x] too few samples")
        return
    tick_us = meta["tick_s"] * 1e6
    cnt = [r[1] for r in data]
    per = [r[2] for r in data]
    exe = [r[3] for r in data]
    gaps = sum(((cnt[i] - cnt[i - 1]) & 0xFFFFFFFF) - 1 for i in range(1, n))
    print("    cycles %d, samples missing %d" % (((cnt[-1] - cnt[0]) & 0xFFFFFFFF) + 1, gaps))

    # Start delay against the ideal grid: unwrapped time stamps fitted to
    # a + b * cycle; the residual is the ISR start relative to its grid point.
    t, acc, prev = [], 0, data[0][0]
    for r in data:
        acc += (r[0] - prev) & 0xFFFFFFFF
        prev = r[0]
        t.append(acc)
    k = [((c - cnt[0]) & 0xFFFFFFFF) for c in cnt]
    mk, mt = sum(k) / n, sum(t) / n
    b = sum((ki - mk) * (ti - mt) for ki, ti in zip(k, t)) / sum((ki - mk) ** 2 for ki in k)
    a = mt - b * mk
    res = [(ti - (a + b * ki)) * tick_us for ki, ti in zip(k, t)]
    rmin = min(res)
    lat = [v - rmin for v in res]
    period_us = b * tick_us
    if fold is None:
        fold = int(round(1000.0 / period_us)) if 0.5 <= period_us <= 1000.0 else 1
    fold = min(max(fold, 1), 2000)
    print("    period from the time stamps %.4f us (%.3f Hz); 1 ms = %d cycles" %
          (period_us, 1e6 / period_us, fold))
    print(stats_line("exec time", exe))
    print(stats_line("period", per))
    print(stats_line("start delay", lat))

    # exec of sample i belongs to cycle cnt[i] - 1; the start delay to cnt[i]
    ph_prev = [(c - 1) % fold for c in cnt]
    ph_now = [c % fold for c in cnt]
    print("\n  Average over the phase within 1 ms (cycle number mod %d):" % fold)
    print_profile("exec time", fold_profile(ph_prev, exe, fold), median(exe), 0.1)
    print_profile("start delay", fold_profile(ph_now, lat, fold), median(lat), 0.1)

    thr = median(exe) + spike_us
    spikes = [cnt[i] - 1 for i in range(n) if exe[i] > thr]
    print("\n  Execution-time spikes > p50 + %.2f us (%.2f us): %d (%.3f %% of the cycles)"
          % (spike_us, thr, len(spikes), 100.0 * len(spikes) / n))
    if len(spikes) > 1:
        iv = {}
        for i in range(1, len(spikes)):
            d = (spikes[i] - spikes[i - 1]) & 0xFFFFFFFF
            iv[d] = iv.get(d, 0) + 1
        top = sorted(iv.items(), key=lambda kv: -kv[1])[:8]
        print("    distance to the previous spike [cycles: count]: " +
              ", ".join("%d: %d" % kv for kv in top))
        ph = {}
        for s in spikes:
            ph[s % fold] = ph.get(s % fold, 0) + 1
        top = sorted(ph.items(), key=lambda kv: -kv[1])[:6]
        print("    phase within 1 ms [phase: count]: " + ", ".join("%d: %d" % kv for kv in top))

    if not meta.get("have_diag"):
        return
    dec = [struct.unpack(DIAG_FMT, r[4]) for r in data]
    aligned = sum(1 for i in range(n) if dec[i][0] == ((cnt[i] - 1) & 0xFFFFFFFF))
    print("\n  uz_isr_diag (previous cycle; aligned with exec time in %.1f %% of the samples)"
          % (100.0 * aligned / n))
    cyc_us = 1e6 / CPU_HZ
    sec = {name: [d[1 + j] * cyc_us for d in dec] for j, name in enumerate(SECTIONS)}
    for name in SECTIONS:
        print(stats_line(name, sec[name]))
    ev = meta.get("pmu_events", 0)
    pmu_names = []
    for j in range(3):
        code = (ev >> (8 * j)) & 0xFF
        pmu_names.append("pmu%d %s" % (j, PMU_NAMES.get(code, "0x%02X" % code)))
        vals = [d[9 + j] for d in dec if d[9 + j] != 0xFFFF]
        print(stats_line(pmu_names[j][:16], vals, "  (%s)" % pmu_names[j]))

    # Which section grows in the slow cycles? Once for all of them, once
    # without the cycles in which a time-slice event ran.
    tot = sec["total"]
    tmed = median(tot)
    smed = median(sec["xcp_slices"])
    meds = {name: median(sec[name]) for name in SECTIONS}
    pmeds = []
    for j in range(3):
        allv = [d[9 + j] for d in dec if d[9 + j] != 0xFFFF]
        pmeds.append(median(allv) if allv else float("nan"))

    def attribution(title, idx):
        print("\n  %s: %d (%.3f %%). Section mean in them minus the section median:"
              % (title, len(idx), 100.0 * len(idx) / n))
        if not idx:
            return
        parts = ["%s %+.2f" % (name, sum(sec[name][i] for i in idx) / len(idx) - meds[name])
                 for name in SECTIONS[:-1]]
        for j in range(3):
            vals = [dec[i][9 + j] for i in idx if dec[i][9 + j] != 0xFFFF]
            if vals:
                parts.append("pmu%d %+.1f" % (j, sum(vals) / len(vals) - pmeds[j]))
        print("    " + ", ".join(parts) + " (us; pmu in counts)")

    attribution("Slow cycles (total > p50 + %.2f us)" % spike_us,
                [i for i in range(n) if tot[i] > tmed + spike_us])
    attribution("Slow cycles without a time-slice event",
                [i for i in range(n) if tot[i] > tmed + spike_us and sec["xcp_slices"][i] < smed + 0.2])
    for name in SECTIONS[:-1]:
        top = sorted(range(n), key=lambda i: -sec[name][i])[:max(1, n // 1000)]
        if sum(sec[name][i] for i in top) / len(top) - meds[name] < 0.3:
            continue
        parts = []
        for j in range(3):
            vals = [dec[i][9 + j] for i in top if dec[i][9 + j] != 0xFFFF]
            if vals:
                parts.append("pmu%d %+.1f" % (j, sum(vals) / len(vals) - pmeds[j]))
        print("    slowest 0.1 %% of %-10s: mean %+.2f us above its median, %s"
              % (name, sum(sec[name][i] for i in top) / len(top) - meds[name], ", ".join(parts)))
    print("\n  Section average over the phase within 1 ms:")
    for name in SECTIONS:
        print_profile(name, fold_profile(ph_prev, sec[name], fold), median(sec[name]), 0.1)

    # Run time by what the main loop was doing when the ISR interrupted it:
    # sample i describes cycle cnt[i] - 1, whose entry phase came with sample
    # i - 1. Cycles with a time-slice event are left out.
    print("\n  Run time (total, no time-slice cycles) by main-loop phase the ISR interrupted (slow = > p50 + %.2f us):"
          % spike_us)
    by = {}
    for i in range(1, n):
        if ((cnt[i] - cnt[i - 1]) & 0xFFFFFFFF) == 1 and sec["xcp_slices"][i] < smed + 0.2:
            by.setdefault(dec[i - 1][13], []).append(i)
    for p in sorted(by):
        idx = by[p]
        v = sorted(tot[i] for i in idx)
        slow = sum(1 for x in v if x > tmed + spike_us)
        dm = [dec[i][10] for i in idx if dec[i][10] != 0xFFFF]
        print("    %-13s %8d cycles  p50 %6.2f  p99 %6.2f  max %6.2f us  slow %5.1f %%  pmu1 mean %5.1f"
              % (MAIN_PHASES.get(p, str(p)), len(v), pct(v, 50), pct(v, 99), v[-1],
                 100.0 * slow / len(v), sum(dm) / len(dm) if dm else float("nan")))

    # Start delay by what the main loop was doing at the interrupt.
    lmed = median(lat)
    print("\n  Start delay by main-loop phase at the interrupt (late = > p50 + 0.5 us):")
    by = {}
    for i in range(n):
        by.setdefault(dec[i][13], []).append(lat[i])
    for p in sorted(by):
        v = sorted(by[p])
        late = sum(1 for x in v if x > lmed + 0.5)
        print("    %-13s %8d samples (%5.1f %%)  p50 %5.2f  p99 %5.2f  max %5.2f us  late %6d"
              % (MAIN_PHASES.get(p, str(p)), len(v), 100.0 * len(v) / n, pct(v, 50), pct(v, 99), v[-1], late))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--ip", help="board IP address")
    ap.add_argument("--port", type=int, default=5556)
    ap.add_argument("--seconds", type=float, default=10.0, help="recording time (default 10)")
    ap.add_argument("--elf", default=xp.DEFAULT_ELF, help="R5 ELF (default: workspace Baremetal.elf)")
    ap.add_argument("--nm", default=xp.DEFAULT_NM)
    ap.add_argument("--load-r5", type=int, default=0, help="extra bytes per cycle on DAQ_R5 (from --load-symbol)")
    ap.add_argument("--load-1ms", default="none", help="'canape' (the 23 counters of the CANape project) or bytes")
    ap.add_argument("--load-symbol", default="Global_Data", help="source of the byte loads (default Global_Data)")
    ap.add_argument("--pmu", default="", help="PMU events of the 3 counters, e.g. 0x01,0x03,0x43 (default: as set)")
    ap.add_argument("--spike-us", type=float, default=0.5, help="spike threshold above the median (default 0.5)")
    ap.add_argument("--fold", type=int, default=None, help="cycles per 1 ms profile (default from the period)")
    ap.add_argument("--out", default="", help="save the recording (binary, for --analyze)")
    ap.add_argument("--analyze", default="", help="evaluate a saved recording instead of recording")
    args = ap.parse_args()
    if args.analyze:
        meta, data = load(args.analyze)
    else:
        if not args.ip:
            ap.error("--ip is required for a recording")
        meta, data = record(args)
    analyze(meta, data, args.spike_us, args.fold)
    return 0


if __name__ == "__main__":
    sys.exit(main())
