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
    python xcp_poll.py --ip 192.168.1.42
    python xcp_poll.py --ip 192.168.1.42 --port 5556 --interval 0.2

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
DEFAULT_NM = r"C:\Xilinx\Vitis\2022.2\gnu\aarch64\nt\aarch64-none\bin\aarch64-none-elf-nm.exe"


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
            # Read responses; skip async EV/SERV packets until a RES/ERR arrives.
            try:
                while True:
                    data, _src = self.sock.recvfrom(2048)
                    if len(data) < 5:
                        continue
                    resp = data[4:]  # strip <LEN><CTR>
                    if resp[0] in (PID_EV, PID_SERV):
                        continue
                    return resp
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


def main():
    ap = argparse.ArgumentParser(description="Poll the UltraZohm XCPlite slave over UDP (no CANape needed).")
    ap.add_argument("--ip", required=True, help="UltraZohm board IP address")
    ap.add_argument("--port", type=int, default=5556, help="XCP UDP port (default 5556)")
    ap.add_argument("--interval", type=float, default=0.2, help="poll period in seconds (default 0.2)")
    ap.add_argument("--elf", default=DEFAULT_ELF, help="FreeRTOS.elf to resolve symbol addresses from")
    ap.add_argument("--nm", default=DEFAULT_NM, help="path to aarch64 nm")
    ap.add_argument("--counter-addr", type=lambda x: int(x, 0), default=None)
    ap.add_argument("--sine-addr", type=lambda x: int(x, 0), default=None)
    ap.add_argument("--diag", action="store_true",
                    help="Phase 3 diagnostic: read the R5 MEAS image in OCM directly "
                         "(seq/ts @ 0xFFFD0100) and the A53-local copy, side by side")
    args = ap.parse_args()

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

    print("[i] counter @ 0x%08X   sine @ 0x%08X" %
          (addr["xcp_demo_counter"], addr["xcp_demo_sine"]))
    print("[i] connecting to %s:%d ..." % (args.ip, args.port))

    xcp = XcpUdp(args.ip, args.port)
    try:
        info = xcp.connect()
        print("[+] CONNECTED  (MAX_CTO=%d  MAX_DTO=%d)" % (info["max_cto"], info["max_dto"]))

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

        print("    polling -- Ctrl+C to stop\n")
        print("    %-12s  %-12s  %-14s" % ("counter", "sine", "ts_us"))
        while True:
            counter = struct.unpack("<I", xcp.short_upload(addr["xcp_demo_counter"], 4))[0]
            sine = struct.unpack("<f", xcp.short_upload(addr["xcp_demo_sine"], 4))[0]
            ts = struct.unpack("<I", xcp.short_upload(addr["xcp_meas_local_timestamp_us"], 4))[0]
            print("    %-12d  %-12.4f  %-14d" % (counter, sine, ts))
            time.sleep(args.interval)
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
