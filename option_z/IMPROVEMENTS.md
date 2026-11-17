# Option Z — open gaps & improvement backlog

Status as of 2026-07-09, after the CP7 pass that ported the hedrive hardware
lessons (seqlock, CTO mailbox, XCP_IN generation handshake, gateway-owned CTR,
dedicated CTO queue, TX batching, deep DAQ queue — see
`uz_sw_xcp_hedrive_andi/XCP_BOTTLENECK_ANALYSIS.md` T1/T3/T8/B1/B5). Everything
below is **known and accepted** for hardware bring-up; this file is the
prioritized list of what to measure, what debt remains, and what must happen
before production-like use.

Verified already inherited (not open): the mandatory `portMEMORY_BARRIER` +
`use_task_fpu_support 2` BSP fix is present in `tcl_scripts/` and in all three
generated `FreeRTOSConfig.h` copies — the historical "A53 freezes after minutes
of traffic" bug is covered.

## 1. Measure on first hardware contact (cheap, decides the next change)

### 1.1 XCP sweep moved OUT of `ISR_Control` — implemented 2026-07-11 (CP11)
Measured with the sweep still in the ISR (via `isr_execution_time_us`,
`--stress` at 10 kHz): 16.1 µs XCP idle (engine ≈ +10 µs over baseline),
18.3 µs @ 100 B, 27.1 µs @ 1 kB, 52.9 µs @ 4 kB/cycle — linear
~10 µs base + ~10 µs/KB. Unacceptable for the **100 kHz ISR target**
(10 µs total budget), so the §1.1 lever is now implemented:

- ISR keeps ONLY `xcp_r5_event()` (the DAQ sampling copy; ~sub-µs idle,
  ~5 µs/KB measured-payload marginal).
- Everything else (command processing, queue drain → OCM, cache
  maintenance, IPI trigger) runs from the main loop via
  `xcp_r5_background()`, paced at `XCP_R5_SWEEP_PERIOD_US` (100 µs — the
  soak-validated exchange cadence; the A53 gateway sees the same IPI rate
  as before).
- queue32 (32 KB, was 8 KB) is the ISR/main boundary; its internal locks
  are pointer-arithmetic-short, and the IRQ-disabling lock that used to sit
  around the 252-byte OCM memcpy in `xcp_r5_tx_pump` is GONE (everything
  CTR-related is single-context now). New counters: `xcp_r5_queue_lost`
  (ISR out-produced the sweep — raise queue size/sweep rate),
  `xcp_r5_sweep_count` (main-loop liveness).

**Re-measure `isr_execution_time_us` after rebuild** — expected: near the
non-XCP baseline at idle, ~+5 µs/KB of measured payload when streaming.
At 100 kHz later: mind the queue sizing math in `xcptl_ocm.c`, the 1 µs DAQ
timestamp granularity (10 ticks/cycle), and the R5 heap (queueInit now
takes 32 KB of the 128 KB heap; watch `xcp_r5_init_result == -1`).

### 1.2 Declared vs real DAQ event rate — RESOLVED (CP12, 2026-08-03)
`DAQ_R5` used to declare a hardcoded 1 ms while firing at the control rate.
It now declares `XCP_R5_ISR_PERIOD_NS`, derived in `xcptl_ocm.c` from
`UZ_PWM_FREQUENCY x Interrupt_ISR_freq_factor / INTERRUPT_ADC_TO_ISR_RATIO`
(the expression `main.c` uses for `isr_samplerate_s`) — 25 µs at the 40 kHz
of the test bench, 100 µs at the repository default of 10 kHz. The A2L files
(`uz.A2L`, `gen_a2l.py`) declare the bench value of 25 µs as a constant.

Same pass added the hedrive time slices as derived rasters (see
`kXcpR5Slice`): event channels 1..4 = `daq_1ms` / `daq_10ms` / `daq_100ms` /
`daq_1s`, counted down from the ISR rate and staggered so they never fire in
the same control cycle. Slow signals no longer have to ride the ISR raster,
which is the cheapest possible bandwidth cut on the OCM/UDP path. Channel
numbers are creation order and are mirrored in `CANape/UZ_XCP/uz.A2L` — a
mismatch would silently move signals to the wrong raster, so `xcp_r5_init()`
verifies the numbering and latches `xcp_r5_init_result = -4` if it ever
shifts. DAQ table memory went 3 KB → 6 KB (`OPTION_DAQ_MEM_SIZE`) for the
five lists.

## 2. Design debt — fix only if symptoms appear

### 2.1 DAQ frames of a missed cycle — RESOLVED 2026-11-16 (consumption handshake, not yet on hardware)
What CP7 fixed (hedrive T8): a late/overlapping A53 IPI can no longer kill the
session or corrupt data — command **responses** ride the acknowledged CTO
mailbox, **commands** ride the XCP_IN generation handshake
(rewrite-until-acked), and the A53 stamps the transport counter at
transmission time. What CP7 left lossy: the **DAQ frames** of a sweep the A53
never read, because the R5 rewound the XCP_OUT chain every sweep (943 of
36.6 M cycles in the 1 h soak, `xcp_gw_ocm_cycles_missed`).
Closed on 2026-11-16 without a ring buffer: the R5 keeps a non-empty chain in
place until the A53 acknowledges its `chain_seq` (`out_ack` in the XCP_IN
header) and holds new samples in its 32 KB queue meanwhile
(`xcp_r5_out_held`); after 5 ms without the acknowledge it gives up
(`xcp_r5_out_overwritten`, gateway dead or stalled; until 2026-11-18: 50
sweeps). Since then `xcp_gw_ocm_cycles_missed` is an IPI-latency indicator,
not a loss counter.

### 2.2 Torn-read window — RESOLVED (CP7)
XCP_OUT now carries a seqlock (odd while the R5 writes, published after the
payload flush). The A53 stages all records in the IPI ISR and commits them
only if the sequence was stable — torn frames can no longer reach the
network. Discards are counted (`xcp_gw_ocm_torn`, `xcp_gw_ocm_skipped_writing`).

### 2.3 Throughput ceiling — MITIGATED (CP7), lwIP knobs remain
`xcp_gw_tx_task` now batches queued records into one ≤1400-byte UDP datagram
per `sendto` (hedrive B1; both CANape and `xcp_poll.py` parse multi-frame
datagrams), and the DAQ queue is a deep burst absorber (262144 records ≈
68 MB heap ≈ 1.5 s at 320 Mbit/s, matching hedrive's multi-second-stall
sizing; tail-drop + `xcp_gw_txq_dropped` on overflow — hedrive B5 final
form). UDP has no backpressure, so PC-side receive pauses are absorbed by
the receiver instead (`xcp_poll.py` sets a 32 MB socket buffer).
If throughput still limits: a slower raster in CANape (the engine has no DAQ
prescaler), or the parked lwIP BSP
knobs (`TCP_SND_BUF`-class tuning does not apply to UDP; pbuf/GEM BD counts
would).

### 2.4 Throughput limit — measured 2026-11-17/18 (40 kHz)
Measured with the R5 profile (`xcp_r5_prof`) and the A53 gateway profile
(mirror slots `xcp_gw_prof_*`), both printed by `xcp_poll.py --stress`:

| Cost | Value |
|---|---|
| Control ISR at 40 kHz | 62-70 % of the R5; the XCP part (`xcp_r5_event`) is ~1.2 us + ~1.8 us per KB sampled |
| R5 main loop left for XCP | the other ~30 % |
| R5 per KB of DAQ, data still cached | copy DDR queue -> OCM ~3.6 us CPU, cache flush ~1.3 us |
| R5 per KB of DAQ, data no longer cached | copy ~7.2-7.7 us CPU |
| A53 per datagram | ~12-15 us: IPI hook ~2.3 us per record, tx task ~11 us incl. ~6-7 us in `lwip_sendto` |
| A53 idle | ~40 % at 40k datagrams/s (1000 B/cycle), 55-60 % in overload |

- The A53 is not the limit; it has room for ~65-70k datagrams/s.
- The R5 copy into the OCM is. The R5 BSP maps the OCM Normal write-back
  write-allocate (`platform/ZynqMP/mpu.c`), so every new XCP_OUT line is
  first read from the OCM and later cleaned back.
- Near the limit the R5 is bistable. At 40 kHz the control ISR turns the
  32 KB data cache over in ~0.3 ms (sampled signals plus queue entries).
  While the main loop copies data younger than that, the copy costs ~3.6
  us/KB and the R5 can move ~60 MB/s; once it falls behind, it copies older,
  uncached data at ~7.5 us/KB, can move only ~36 MB/s and never catches up
  while the load stays above that. At 1000 B/cycle (40 MB/s) back-to-back
  commands were enough to tip it over (15 % of the samples lost in 10 min);
  at 900 B/cycle (36 MB/s) the same load ran clean.
- Every DAQ chain waits 30-75 us for the A53's acknowledge before the next
  one may be written; during that wait the queued data ages. That wait, not
  the CPU, is what lets the data leave the cache.

Tried on 2026-11-18 and reverted (measured on the board):
- Software prefetch (PLD) in the R5 copy: cached copy 4.4 instead of 3.6
  us/KB, uncached copy unchanged.
- Cutting a stuck backlog down to fresh data (head drop): the copy stayed
  at ~7.7 us/KB, the overload throughput fell from ~250 to ~200 Mbit/s.
- At most 10 segments per DAQ exchange: copy at 7.2 us/KB already at
  1000 B/cycle, which then lost data too. The cost is not the chain size.
- Cutting a DAQ copy short for a waiting command: each cut chain needed its
  own acknowledge, and with back-to-back commands 23 % of the DAQ data was
  lost at 1000 B/cycle.

Options, not done:
1. **A ring buffer in XCP_OUT** instead of the single chain with its
   acknowledge: the R5 copies each completed queue segment at once while it
   is still cached and only stalls when the ring is full; the A53 consumes
   behind it. Removes the acknowledge wait and with it the bistability.
   Protocol change on both sides (OCM layout v4).
2. XCP_OUT write-back **no** write-allocate, as an R5 MPU region of its own
   (the A53 side unchanged): no line fills and almost no flush, estimated
   ~1 us/KB instead of ~5 on the R5. For writes that is non-cacheable
   behaviour of that window, which was ruled out for the OCM so far - needs
   a decision.
3. DMA (LPD ADMA): not available, the hardware design has no `psu_adma`.
4. Zero copy (the A53 reads the queue segments in R5 DDR): needs several
   popped but unreleased segments in queue32 (engine patch) and breaks if the
   engine clears the queue while segments are in flight.
5. Responses in the middle of a DAQ exchange: publish the header with the
   response while the chain is still open (chain_seq 0 keeps it invalid),
   then finish the chain. Commands would no longer wait for a running copy
   (~0.6 ms round trip at 1000 B/cycle instead of ~0.24 ms idle). Needs the
   header and the chain written in separate sessions in `ocm_xcp_fifo.c`.
6. A53: FreeRTOS queue items are a fixed 1402 bytes and copied twice with
   interrupts masked, five copies per record in all; a byte ring would save
   ~25 % of the A53 time per datagram. Not needed while the A53 idles ~40 %.
7. A53: a failed `lwip_sendto` is retried after one tick (10 ms at 100 Hz).
   Fine while `xcp_gw_sendto_err` stays ~0 (it does since the TX sizing of
   CP9).

### 2.5 Exchange pacing — RESOLVED 2026-11-18 (`97ac9f86`)
Inherited decisions that were replaced:
- One sweep every 100 us (from the 10 kHz July bench, CP11) did commands,
  DAQ and the IPI in one go. Commands waited for the next sweep; a chain
  acknowledged a few microseconds after the next sweep had started was kept
  for a whole further period, which from ~1000 B/cycle cascaded into 31 KB
  chains and queue overflow while the A53 idled 40-57 %; the A53 took 10k
  IPIs/s even with nothing to do; and the pacing clock (`uz_SystemTime`
  uptime) advances only once per control ISR (25 us at 40 kHz).
- The R5 DAQ queue was 32 KB (~0.8 ms at 40 MB/s), sized for 10 kHz.

Now (`xcptl_ocm.c`, `XCP_R5_POLL_PERIOD_US`): the R5 polls the XCP_IN header
every 5 us (CPU cycle counter); a new command batch or a waiting response
gets a header-only exchange at once (the A53 rx task writes commands into
XCP_IN when they arrive, not at the next IPI); a DAQ exchange runs only on an
acknowledged chain, when the oldest waiting data is 1 ms old or 8 queue
segments wait; after 1 ms without any exchange a header-only heartbeat
follows. The queue is 128 KB (heap 256 KB).

| | before | after |
|---|---|---|
| 8 B/cycle: IPIs = datagrams per s | 9800 (80 B each) | 960 (822 B each) |
| A53 idle at 8 B/cycle | 79 % | 98 % |
| 1000 B/cycle | 47 % kept chains, 0 loss | no waits for the acknowledge, 0 loss |
| command round trip idle / 1000 B/cycle (median) | 374 / 816 us | 238 / 590 us |
| back-to-back commands at 900 B/cycle | 0 loss (30 min) | 0 loss (10 min) |

## 3. Safety scope — required before live calibration (Z5)

### 3.1 `DOWNLOAD` could write anywhere in the allow-list — including code
R5 `.text` lives in DDR, and `ApplXcpCheckMemory` has no read/write
distinction, so a stray CANape calibration write could patch running code
over UDP. **Done 2026-11-16:**
- **Write gate** (`XCP_MTA_WRITE_CHECK`, an opt-in UZ patch in
  `XcpWriteMta`; `xcp_r5_check_write()` in `xcptl_ocm.c`): every
  DOWNLOAD / SHORT_DOWNLOAD must lie completely inside `.data`, `.sdata`,
  `.sbss` or `.bss` (linker symbols). Code, constants, the ATCM vectors,
  stacks, heap and the whole OCM answer `ERR_WRITE_PROTECTED`
  (`xcp_r5_write_denied` counts them).
- **Measurement-only build**: `XCP_R5_READ_ONLY 1` (`xcp_r5.h`) refuses
  every write. CONNECT still advertises CAL/PAG, so CANape shows the
  parameters and reports the refusal on the first write.

Still open (full Z5 review): range checks per parameter, atomic adoption of
multi-byte values against the control ISR, rollback.

### 3.2 Zero authentication
`xcp_gw_rx_task` adopts whoever sends a datagram as master (`gMaster`), and
XCP has no session security here. Acceptable on the isolated lab bench only.
Mitigations if ever needed: bind gateway to a dedicated interface/subnet,
pin the master IP after first CONNECT, or XCP seed&key.

## 4. Fallback

The only fallback is `LOGGING_PATH_JAVASCOPE` (with `XCP_ENGINE_R5_ENABLE 0`),
the hardware-proven logger. The A53-hosted XCPlite server with the curated
eight-signal MEAS image (`LOGGING_PATH_XCP_LITE`) never ran on hardware and was
removed on 2026-11-16 (last present at commit c51d06c): it carried a second,
older copy of the engine (upstream V2.1.1) that would have needed its own port
on every upgrade.

## 4b. Vendored XCPlite version (upgraded 2026-11-16)

In-tree: upstream **V2.3.4** (github vectorgrp/XCPlite main, "Dev 2.3.4",
2026-11-11), taken file-for-file from the local clone `..\xcp_lite` for every
engine file we vendor (`xcplite.c/h`, `xcp*.h`, `queue32.c`, `queue.h`,
`xcpappl.c`, `platform.h`, `util.c/h`, `dbg_print.h`, the inactive
`cal/persistence/shm/a2l/xcpeth*` headers, new `sockets.h`). The R5 glue
(`xcptl_ocm.c`, `platform_baremetal.c`, `ocm_xcp_fifo.c`) and the public API it
uses (`XcpInit/XcpStart/XcpCreateEvent/XcpEvent/XcpCommand`, the
`ApplXcp*` callbacks, `XcpTl*`) are unchanged by the upgrade. Everything R5
specific lives in `xcplib_r5_cfg.h`, applied at the end of `xcplib_cfg.h`
like upstream's own `xcplib_rtos_cfg.h` override.

What the upgrade brought in (from upstream's CHANGELOG, V2.1.1 → V2.3.4):
the remaining #126 DAQ-configuration robustness (allocation overflow and
`WRITE_DAQ_MULTIPLE` errors invalidate the whole configuration, ODT sizes are
validated before commit, `SET_DAQ_PTR` sequence check, selected lists are
validated before `START_STOP_SYNCH` start), the `XcpSetDaqListMode` link-loop
fix we had already cherry-picked, `XcpEventEnable` range checks, and the
explicit `OPTION_DAQ_EVENT_LIST` / `OPTION_SECTION_REGISTRATION` split (we use
the run-time event list, no linker sections). Behavioural change to note:
`GET_DAQ_RESOLUTION_INFO` now reports the 1 µs clock as `UNIT_1NS` with 1000
ticks per unit instead of `UNIT_1US` with 1 tick (same resolution; the A2L
keeps `0x1 SIZE_DWORD UNIT_1US TIMESTAMP_FIXED`, which is what upstream's
own A2L writer still emits).

Local patches on top of upstream, every one marked `UZ` in the source and
default-off where it touches engine behaviour (re-apply after the next
upgrade — the list is also in the session memory of the coding agent):
- `platform.h`: `ARMR5` → `_BAREMETAL` platform branch (atomics, IRQ
  critical-section mutex, no threads).
- `xcpappl.c`: `_BAREMETAL` accepted as platform, base address 0.
- `xcptl_cfg.h`: `XCPTL_MAX_DTO_SIZE` and `XCPTL_MAX_SEGMENT_SIZE` may be
  predefined (the OCM record cap is 255 B, upstream's MTU formula rounds the
  segment to a multiple of 8 — 256 would not fit; we set 252 = 4 + 248).
- `xcplib_cfg.h`: includes `xcplib_r5_cfg.h` at the end.
- `xcp_cfg.h`: `OPTION_DISABLE_DYN_ADDRESSING` switch (R5 has no
  `XcpEventExt` context to execute event-relative commands).
- `xcplite.c`: `XCP_ENABLE_MTA_RANGE_CHECK` (size check on every
  `XcpReadMta`/`XcpWriteMta`), `calcChecksum` size-0 error and
  `XCP_CHECKSUM_MAX_SIZE` cap.
- `queue32.c`: `packets_lost` read/reset under the queue lock.

The A53 no longer carries an XCPlite copy of its own (the fallback server in
`vitis/software/FreeRTOS/sw/xcp_lite/` was removed on 2026-11-16, see §4);
the R5 engine is the only vendored XCPlite tree.

The upgrade is compile-validated only (armr5 syntax + object build, external
symbols unchanged: libc, `Xil_DCacheFlushRange`, `uz_SystemTime`); it has
**not** run on hardware yet — rerun TEST_PLAN.md §1–§3 (connect, DAQ, stress)
before trusting it.

## 4c. CANape: complete structures in measurement windows (2026-11-16)

Symptom: a struct such as `Global_Data.aa` cannot be added to a watch /
measurement window as a whole; CANape's "create from ELF" had left a one-byte
`MEASUREMENT Global_Data.aa UBYTE` behind in `uz.A2L` (the fingerprint of a
failed structure creation), while single members like
`Global_Data.aa.A1.me.ADC_array` worked.

Two causes, both fixed in the repo:

1. **The A2L had no structure types.** CANape measures a complete struct only
   through ASAP2 1.7.1 `TYPEDEF_STRUCTURE` + `INSTANCE`, and its own ELF
   import gives up on the UltraZohm types: `Measurements`/`ConversionFactors`
   are unions with an *anonymous* inner struct (a struct view and an array
   view of the same bytes), and `DS_Data.objects` holds only pointers.
   `tools/xcp_test/dwarf_structs.py` now derives the layout from the ELF's
   DWARF (through GNU objdump, no extra Python package) and writes the
   typedefs in the syntax of upstream XCPlite's A2L generator: scalars,
   arrays (`MATRIX_DIM`), nested structs; a union becomes a typedef of its
   first alternative (named in the comment), anonymous members are hoisted,
   pointers skipped. `uz.A2L` carries the result for `Global_Data` and its
   members `rasv`, `av`, `aa` (INSTANCEs with `SYMBOL_LINK`, so CANape
   refreshes their addresses from the ELF like the plain measurements). The
   bogus UBYTE object is removed. Regenerate after a layout change:
   `python tools/xcp_test/dwarf_structs.py --elf vitis\workspace\Baremetal\Debug\Baremetal.elf Global_Data.av ...`
   or `gen_a2l.py --struct ... --struct-out blocks.a2l`.
2. **ODT entry size 248 could never fit an ODT.** The engine accepted and
   advertised `MAX_ODT_ENTRY_SIZE_DAQ` = 248 (= the whole 248-byte DTO), but an
   ODT carries at most 240 bytes (4-byte ODT/DAQ header, 4-byte timestamp in
   the first ODT). CANape merges the contiguous members of a structure into
   one ODT entry up to the advertised maximum, so a merged entry of 241..248
   bytes failed `WRITE_DAQ` with `DAQ_CONFIG` and the measurement would not
   start — single scalars never hit this. `xcplib_r5_cfg.h` sets
   `XCP_MAX_ODT_ENTRY_SIZE 240`, `uz.A2L` and `gen_a2l.py` say `0xF0`.
   (`CANape.ini` still shows the learned 248; CANape re-learns it at connect.)

Also corrected in `gen_a2l.py`: the DAQ identification field is
`IDENTIFICATION_FIELD_TYPE_RELATIVE_WORD_ALIGNED` (the engine's 4-byte
`[odt][fill][daq u16]` header, DAQ_HDR_ODT_FIL_DAQW), not `ABSOLUTE`.

Not verified in CANape itself (no CANape on the build machine): the blocks
follow upstream's CANape-validated test fixtures, the generated addresses
match what CANape wrote into its own `~uz.A2L` refresh, and the A2L parses
structurally. If CANape still refuses a structure, the message now points
at a concrete type.

## 5. Small stuff

- The checked-in A2L files (`tools/xcp_test/*.a2l`) go stale with every build
  (link addresses move). Consider gitignoring them and always regenerating
  via `gen_a2l.py`.
- `xcp_poll.py --daq` streams a single variable (1 list / 1 ODT / 1 entry).
  Extending to multiple entries/lists would make a nicer demo but adds
  nothing diagnostically.
- `ocm_xcp_fifo.c/h` is intentionally duplicated between
  `Baremetal/src/sw/xcp_engine/` and `FreeRTOS/sw/xcp_gateway/` (each app
  compiles its own copy; `ARMR5` selects the side). Keep the two copies
  byte-identical — or teach both Vitis projects to link one shared folder
  (like `vitis/software/shared/`) to remove the duplication entirely.
