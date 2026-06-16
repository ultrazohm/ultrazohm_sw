# Testing the UltraZohm XCPlite slave

This is the **fast path** to confirm the XCPlite-on-A53 demo works — **no CANape
and no A2L required**. A ~200-line Python script connects over UDP and reads the
demo variables straight out of the target.

## 0. Prerequisites

- FreeRTOS app built from this branch with `LOGGING_PATH_XCP_LITE = 1`
  (`vitis/software/FreeRTOS/defines.h`) — this is the default on this branch.
- Both ELFs flashed (`Baremetal.elf` on the R5, `FreeRTOS.elf` on the A53) the
  usual UltraZohm way (JTAG/Vitis run config, or boot image).
- The board on the same network as your PC.
- Python 3.7+ on your PC (standard library only — nothing to install).

## 1. Find the board's IP address

On this branch the app prints the XCP endpoint to the **serial console**
(USB-UART, 115200 8N1) right after the network comes up, e.g.:

```
APU: XCPlite slave (UDP) at 192.168.1.42:5556
APU:   test with  python tools/xcp_test/xcp_poll.py --ip 192.168.1.42
```

If you can't see the console, the board uses DHCP — find the lease on your
router, or set a static IP in the BSP/lwIP config.

## 2. Run the test client (no CANape)

From the repo root:

```bash
python tools/xcp_test/xcp_poll.py --ip 192.168.1.42
```

Expected output:

```
[i] addresses resolved from ELF: FreeRTOS.elf
[i] counter @ 0x002002B4   sine @ 0x002002B8
[i] connecting to 192.168.1.42:5556 ...
[+] CONNECTED  (MAX_CTO=248  MAX_DTO=248)
    polling -- Ctrl+C to stop

    counter       sine          ts_us
    12044         0.0628        12044318
    12244         0.8090        12244512
    12444         0.9980        12444707
    ...
```

**Pass criteria:** `CONNECTED`, the `counter` keeps increasing (~+200 per row at
the default 0.2 s poll), and `sine` swings smoothly between -1 and +1. That
proves the full stack: lwIP UDP + XCP transport + protocol engine + the 1 µs
clock + memory access on the real toolchain.

The script auto-reads the variable addresses from
`vitis/workspace/FreeRTOS/Debug/FreeRTOS.elf`. If you rebuilt and moved the ELF,
pass `--elf <path>`; if Vitis isn't on this PC, it falls back to baked-in
addresses (valid only for the matching build) — or pass `--counter-addr 0x...`.

### Troubleshooting

| Symptom | Likely cause |
|---|---|
| `no XCP response` (timeout) | wrong IP; board not booted; firewall on the PC blocking UDP; board not on `LOGGING_PATH_XCP_LITE` |
| `CONNECT rejected` | a stale XCP session — wait a second and retry, or power-cycle |
| counter not moving | the `xcp_daq` task isn't running — check the serial log for `xcp_server_uz` warnings |

## 3. (Optional) CANape path

Tonight you don't need this. When you do want CANape:

1. Generate an address-matched A2L from the current build:
   ```bash
   python tools/xcp_test/gen_a2l.py --ip 192.168.1.42
   ```
   → writes `tools/xcp_test/UltraZohm_XCP.a2l`.
2. In CANape create an **XCP** device, transport **UDP**, IP = board IP,
   port = 5556, then attach this A2L as the database.
3. Connect and add `xcp_demo_counter` / `xcp_demo_sine` to a measurement.

> The A2L's `MEASUREMENT` addresses are always correct (read from the ELF). The
> `IF_DATA XCP` block is standard but unverified against CANape's AML here; if
> CANape rejects it, configure the device transport manually in the GUI, or
> regenerate with the upstream XCPlite A2L tool (`xcp_lite/tools/bintool`), which
> emits a fully-validated `IF_DATA`.

## 4. Re-generating after a rebuild

Link addresses change whenever you rebuild. The Python client re-reads them
automatically; for CANape, re-run `gen_a2l.py` after each build.
