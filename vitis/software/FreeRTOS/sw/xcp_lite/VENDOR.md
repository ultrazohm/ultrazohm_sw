# Vendored: XCPlite

**Upstream:** https://github.com/vectorgrp/XCPlite  
**License:** MIT (see `LICENSE` in this directory)  
**Upstream commit pinned:** `4fe34e4` (tag: V2.1.1)

## What is here

This directory contains a subset of XCPlite v2.1.1 sources vendored into the
UltraZohm FreeRTOS application.  XCPlite is Vector's MIT-licensed XCP-on-
Ethernet slave implementation; it replaces the non-redistributable XCP Basic
driver.

The UltraZohm-specific files live directly in this directory alongside the
vendored upstream files:

| UZ file | Purpose |
|---------|---------|
| `xcp_server_uz.c/.h` | Init, clock callback, Phase 1 demo DAQ task |
| `xcplib_uz_cfg.h` | Config override (included at end of `xcplib_cfg.h`) |
| `xcp_meas_image_a53.c/.h` | Phase 3 A53-side MEAS image handler |
| `xcp_cal_image_a53.c/.h` | Phase 4 CAL image double-buffer |

## TODO — replace file-copy with a git submodule

The current approach (manually copying a file subset) is intentional for the
initial bring-up phase: it makes the file list explicit and avoids pulling in
a submodule dependency before the integration is proven.

Once Phase 1 acceptance criteria are met (CANape connects, DAQ measures dummy
vars), migrate to a proper submodule:

```bash
git submodule add https://github.com/vectorgrp/XCPlite \
    vitis/software/FreeRTOS/sw/xcp_lite/upstream
git -C vitis/software/FreeRTOS/sw/xcp_lite/upstream checkout 4fe34e4
```

When switching to a submodule, update two things:

1. **Exclusion list** — replace the manual copy step below with a build shim
   or `.gitattributes` export-ignore that keeps the excluded files out of
   the Vitis build.
2. **Vitis import script** — update `tcl_scripts/vitis_generate_UltraZohm_workspace.tcl`
   so that `importsources` points into `upstream/` for the XCPlite sources
   while still soft-linking the UZ-specific files (`xcp_server_uz.*`,
   `xcplib_uz_cfg.h`, `xcp_meas_image_a53.*`, `xcp_cal_image_a53.*`) from
   this directory directly.

## Files copied from upstream (src/ unless noted)

```
xcplite.c / xcplite.h        Core XCP protocol engine
xcpethtl.c / xcpethtl.h     Ethernet transport layer
xcpethserver.c / xcpethserver.h  UDP server + FreeRTOS task wrapper
xcpappl.c                    ApplXcp* callback dispatch (default impls)
queue.h / queue32.c          32-bit mutex-based transport queue
platform.c / platform.h      OS/BSP adaptation (FreeRTOS + lwIP path)
cal.c / cal.h                Calibration segment helper
util.c / util.h              Utility functions
dbg_print.h                  Debug print macros
xcp.h                        XCP protocol layer types and constants (needed by cal.h, xcplite.h, etc.)
xcplib_cfg.h                 Master config (our override at end via -D flag)
xcp_cfg.h                    XCP protocol-layer tuning
xcptl_cfg.h / xcptl.h       Transport-layer tuning
xcplib_rtos_cfg.h            Reference RTOS config (not compiled; doc only)
inc/xcplib.h -> xcplib.h     Public API header
LICENSE                      MIT licence
```

### Headers copied for compilation (implementations excluded from build)

These headers are `#include`d by the vendored files above and must be present
for the compiler to succeed, but their corresponding `.c` implementations are
**not compiled** on FreeRTOS/A53 (see "Do NOT compile" note below).

```
shm.h                        Shared-memory API header (included by xcplite.h, cal.h)
persistence.h                Binary persistence API header (included by cal.c, xcplite.c)
a2l.h            (inc/)      A2L generation API header (included by xcpethserver.c)
a2l_writer.h                 A2L writer helper header (included by a2l.c)
shm.c                        SHM implementation — present for reference; DO NOT COMPILE
persistence.c                Persistence implementation — present for reference; DO NOT COMPILE
a2l.c                        A2L generator — present for reference; DO NOT COMPILE
a2l_writer.c                 A2L writer — present for reference; DO NOT COMPILE
```

### Files intentionally excluded (not present in this directory)

| File | Reason |
|------|--------|
| `queue64f.c`, `queue64v.c` | 64-bit lockless queues — use queue32 on FreeRTOS |
| `xcpshmserver.*` | Multi-process SHM server — Linux/Windows only |
| `xcplib_no_a2l_cfg.h`, `xcplib_ptptool_cfg.h` | Unused config variants |
| `tools/` | Host-side bintool and A2L tooling — run on PC |

## Build configuration — self-contained, no `-D` flags required

Earlier notes here asked for `-D_FREE_RTOS -DOPTION_FREERTOS_LWIP
-DXCPLIB_CFG_OVERRIDE="xcplib_uz_cfg.h" -std=c11` on the Vitis app.  That proved
fragile: the Vitis `.cproject` mangles the quoting of an `#include` macro value
(so `#include XCPLIB_CFG_OVERRIDE` failed with *"expects FILENAME"*), and the
platform `#error` in `platform.h` fires *before* `xcplib_cfg.h` is even read.
The configuration is therefore made **self-contained in the vendored headers**
so the build is correct with the stock Vitis flags (no `-D` needed):

- `platform.h` defines `_FREE_RTOS` (guarded) at the very top, before the
  platform-detection `#error`, so every TU that includes it selects FreeRTOS.
- `xcplib_cfg.h` unconditionally `#include "xcplib_uz_cfg.h"` at the end (in
  addition to the still-supported `XCPLIB_CFG_OVERRIDE` path), which undefines
  `OPTION_ENABLE_TCP`, selects `OPTION_QUEUE_32`, the 1 µs arbitrary-epoch
  clock, `OPTION_FREERTOS_LWIP`, the reduced DAQ/CAL sizes, etc.
- The default Vitis std (gnu17) already provides C11 `stdatomic` and POSIX
  `strnlen`; `-std=c11` is intentionally **not** forced.

Only the include path is needed (already added by the workspace TCL,
`app config -name FreeRTOS compiler-misc -I.../FreeRTOS/sw/xcp_lite`):
```
-I"${workspace_loc:/FreeRTOS/sw/xcp_lite}"
```

**Not compiled** — excluded by renaming to a non-`.c` suffix (`.c.EXCLUDED`),
so Vitis' source scan never picks them up (no per-file "Exclude from Build"
needed): `a2l.c`, `a2l_writer.c`, `persistence.c`, `shm.c`, and `platform.c`
(renamed `platform.c.linux_EXCLUDED`).  `queue64f.c` / `queue64v.c` are simply
not vendored.

`platform.c` (renamed `platform.c.linux_EXCLUDED`) is the upstream
Linux/Windows/POSIX implementation
and cannot be compiled for AArch64 FreeRTOS because it pulls in POSIX-only
headers (`<nanosleep>`, `<pthread.h>`, `<ifaddrs.h>`, etc.) that do not exist
on the target.

The FreeRTOS replacement is `platform_freertos.c` (UZ-authored, MIT-compatible).
It provides all functions declared in `platform.h` that are needed for the
FreeRTOS/lwIP target: `sleepUs`, `sleepMs`, `mutexInit`, `mutexDestroy`,
`clockInit`, `clockGet`, `clockGetLast`, `clockGetString`, `clockGetTimeString`,
all `clockGetMonotonic*` / `clockGetRealtime*` variants, and the full lwIP UDP
socket API (`socketOpen`, `socketBind`, `socketRecvFrom`, `socketSendTo`,
`socketSetTimeout`, `socketShutdown`, `socketClose`).

`socketGetLocalAddr` is present as a no-op stub (returns false / zeroed buffers)
when `OPTION_ENABLE_GET_LOCAL_ADDR` is defined.  On the UltraZohm the IP is
assigned by the network stack; do not enable that option unless a proper
implementation is added.

`platform.h` now also recognises `XCP_PLATFORM_FREERTOS` as a FreeRTOS
detection macro (alongside the existing `FREERTOS`, `_FREE_RTOS`, etc.),
providing a fallback path for build systems that do not pass `-D_FREE_RTOS`.

## A2L generation (offline, Phase 1)

After the first successful build, run on the host PC from the xcp_lite clone:

```bat
tools\bintool\bintool.exe  --a2l --name UltraZohm_XCP ^
  --out UltraZohm_XCP.a2l ^
  vitis\software\FreeRTOS\sw\xcp_lite\xcp_server_uz.c
```

Load the resulting `.a2l` into CANape as the database for the UDP XCP slave
at `<UZ IP address>:5556`.

For the demo specifically, prefer the in-repo generator (no host build of
XCPlite needed): `python tools/xcp_test/gen_a2l.py --ip <UZ IP>` — it reads the
addresses straight from `FreeRTOS.elf`. And the simplest end-to-end smoke test
needs no A2L at all: `python tools/xcp_test/xcp_poll.py --ip <UZ IP>`.

## Upstream-edit footprint (read before migrating to a submodule)

To keep the build self-contained (Vitis passes no usable `-D` flags), a few
**upstream files were modified in place**. These are the *only* deviations from
pristine XCPlite v2.1.1, and they are the work a submodule migration must undo:

| Upstream file | In-place edit | Why |
|---|---|---|
| `platform.h` | guarded `#define _FREE_RTOS` added at top, before the platform-detection `#error` | platform must be chosen before `xcplib_cfg.h` is read |
| `xcplib_cfg.h` | unconditional `#include "xcplib_uz_cfg.h"` appended | load the UZ override without a fragile `-D` |
| `platform.h` | also recognises `XCP_PLATFORM_FREERTOS` (see above) | extra detection fallback |
| `platform.c`, `a2l.c`, `a2l_writer.c`, `persistence.c`, `shm.c` | renamed `*.c.EXCLUDED` | keep PC-only TUs out of the Vitis source scan |

Everything else under this directory is either pristine upstream or a new
UZ-authored file (`xcp_server_uz.*`, `xcplib_uz_cfg.h`, `xcp_meas_image_a53.*`,
`xcp_cal_image_a53.*`, `platform_freertos.c`).

### Recommended migration: git submodule + a forced-include shim

The two header edits exist only because Vitis can't reliably pass `-D_FREE_RTOS`
or `-DXCPLIB_CFG_OVERRIDE="…"`. Both disappear if the app force-includes one
UZ-authored header on every TU, which lets the submodule stay **pristine** (clean
`git submodule update` pulls):

1. Add the submodule, pinned to the vendored commit:
   ```bash
   git submodule add https://github.com/vectorgrp/XCPlite \
       vitis/software/FreeRTOS/sw/xcp_lite/upstream
   git -C vitis/software/FreeRTOS/sw/xcp_lite/upstream checkout 4fe34e4
   ```
2. Add a UZ-authored shim **outside** the submodule, e.g.
   `xcplib_uz_force.h`:
   ```c
   #pragma once
   #define _FREE_RTOS                         /* select platform before any include */
   #define XCPLIB_CFG_OVERRIDE "xcplib_uz_cfg.h"  /* quotes are valid here, unlike -D */
   ```
   In a header the `#include XCPLIB_CFG_OVERRIDE` quoting works, and `_FREE_RTOS`
   is defined before `platform.h` runs its detection — so **no upstream edit is
   needed**. Revert the `platform.h`/`xcplib_cfg.h` edits after this is in place.
3. Force-include it on the FreeRTOS app (in
   `vitis_generate_UltraZohm_workspace.tcl`, next to the existing
   `compiler-misc -I`):
   ```tcl
   app config -name FreeRTOS compiler-misc -include "$filename_FreeRTOS/sw/xcp_lite/xcplib_uz_force.h"
   ```
4. Exclude the PC-only `.c` files via Vitis project settings (or a
   `.cproject` `excluding=` filter set from the TCL) instead of renaming, so the
   submodule tree stays clean: `platform.c`, `a2l.c`, `a2l_writer.c`,
   `persistence.c`, `shm.c`, `queue64f.c`, `queue64v.c`, `xcpshmserver.c`.
5. Point the include path and source globs at `upstream/src` + `upstream/inc`,
   and keep the UZ-authored files in this directory (outside the submodule).

This is intentionally deferred until the demo is validated on hardware — do not
do it the same night you first flash the board.
