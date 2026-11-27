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

### 2.1 DAQ frames of a missed cycle — RESOLVED 2026-11-16 (consumption handshake, on hardware since 2026-11-17)
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

Now (`xcptl_ocm.c`): the R5 polls the XCP_IN header at most every 5 us (CPU
cycle counter, `XCP_R5_POLL_PERIOD_US`). At 40 kHz that came to one or two
looks per gap between two control ISRs; see 2.7 for the pacing since. A new
command batch or a waiting response gets a header-only exchange at once (the
A53 rx task writes commands into XCP_IN when they arrive, not at the next
IPI); a DAQ exchange runs only on an acknowledged chain, when the oldest
waiting data is 1 ms old or 8 queue segments wait (4 since 2.6); after 1 ms
without any exchange a header-only heartbeat follows. The queue is 128 KB
(heap 256 KB).

| | before | after |
|---|---|---|
| 8 B/cycle: IPIs = datagrams per s | 9800 (80 B each) | 960 (822 B each) |
| A53 idle at 8 B/cycle | 79 % | 98 % |
| 1000 B/cycle | 47 % kept chains, 0 loss | no waits for the acknowledge, 0 loss |
| command round trip, median, 0 / 500 / 900 / 1000 B/cycle | 374 / 338 / 374 / 816 us | 238 / 308 / 558 / 590 us |
| back-to-back commands at 900 B/cycle | 315 us median, 0 loss (30 min) | 583 us median, 0 loss (10 min) |

Commands under DAQ load got slower with this change at 500-900 B/cycle.
The first version of this table listed only idle and 1000 B/cycle and hid
that; found and fixed the same day, see 2.6.

### 2.6 Command latency under DAQ load — RESOLVED 2026-11-18
Two causes, found with A/B builds and a capture on the PC's adapter
(Wireshark's dumpcap; the analysis pairs every command with its response):
- A53: the tx task, lwIP's tcpip thread and the rx task all run at
  priority 2. FreeRTOS does not preempt between equal priorities, and with
  `LWIP_TCPIP_CORE_LOCKING` `lwip_sendto` never blocks. A command that
  arrived during a burst of DAQ datagrams therefore waited in lwIP's mailbox
  until the whole burst was sent: 892 of 1000 responses arrived after a full
  burst (median 14 datagrams). The batching of 2.5 had made the bursts about
  three times longer (13 datagrams at 900 B/cycle, ~4 with the 100 us grid).
- R5: a command waits for a running DAQ copy. With 8 segments a DAQ exchange
  took 184 us at 900 B/cycle.

Fix: the tx task yields after every datagram (`xcp_gateway_a53.c`), and the
DAQ trigger is 4 queue segments instead of 8 (`xcptl_ocm.c`). No lwIP
setting changed.

Measured at 40 kHz. "Single" is `cmd_latency.py` (2000 commands per load, 2
ms apart); "back to back" is a 2 min soak at 900 B/cycle:

| Build | single, median at 0 / 500 / 900 / 1000 B (us) | back to back | IPIs/s, A53 idle at 900 B |
|---|---|---|---|
| trigger 8, tx task at 2 (`97ac9f86`) | 224 / 305 / 544 / 583 | 583 us, 1560/s | 3050, 42 % |
| trigger 8, tx task at 1 | 225 / 278 / 439 / 481 | 317 us, 2496/s | 3050, 42 % |
| trigger 4, tx task at 1 | 220 / 224 / 266 / 281 | 251 us, 3384/s | 6800, 39 % |
| trigger 2, tx task at 1 | 220 / 205 / 231 / 240 | 193 us, 4294/s | 14550, 34 % |
| **trigger 4, yield (chosen)** | 221 / 226 / 271 / 274 | 252 us, 3387/s | 6800, 37 % |

- Smaller chains copy cheaper per KB, because the data is younger and still
  in the cache: 3.5 / 3.2 / 3.1 us/KB at 900 B/cycle for 8 / 4 / 2 segments,
  2.9 instead of 3.5 at 1000 B/cycle. The R5's share in exchanges stayed at
  17-19 % for all three. The cost of smaller chains is on the A53: one IPI
  hook per chain.
- The tx task one priority lower works as well as the yield. It puts the
  task at the level of the application's priority-1 tasks, though (polled
  I2C every 50 ms, CAN), and the priority-1 builds had the largest single
  outliers (10-29 ms). The yield costs about 2 % of the A53 (shown as
  "other" in the A53 profile).
- Final build: 24/24 functional checks. Back to back for 10 min at 900
  B/cycle: 2,025,581 commands, 0 timeouts, worst 1.9 ms. At 1000 B/cycle:
  1,960,833 commands, 0 timeouts, worst 2.1 ms, R5 queue lost +0. With 8
  segments the R5 had fallen behind within the first minute of that test
  (15 % lost, 2.4). 1100 and 1200 B/cycle are still overload (copy back at
  7.5 us/KB, ~28 % lost): the limit itself did not move.
- At the PC's adapter (Npcap timestamps) the round trip is 168 us idle and
  ~220 us at 900 B/cycle; Windows and Python add 50-100 us on top. The
  board's own share idle is estimated at ~60 us, so the Realtek USB adapter
  is probably the largest part (the PC also has a PCIe Ethernet port).
- Not done: trigger 2 (another ~35-60 us for twice the A53 interrupt load).
  Responses in the middle of a DAQ exchange (2.4, option 5) would allow long
  chains without the command waiting for the copy.
- Rare lost responses, explained 2026-11-23 (2.8). One `cmd_latency.py`
  run lost 3 of 8000, the final build's soaks 0 of 4 M, and a captured run
  of 4000 commands did not reproduce it; a first baseline run (trigger 8)
  had hung on one as well. Most likely each was a response packed into a
  datagram that went out with the contents of a later one (transmit buffer
  reused under the DMA). The CANape timeout of 2026-11-23 was this.
- Tool fix on the way: `xcp_poll.py` (`_command`) and `cmd_latency.py`
  waited forever for a lost response while DAQ ran, because every DAQ
  datagram restarted the socket timeout. Both have a deadline per attempt
  now.

### 2.7 Exchange pacing on the control ISR count — 2026-11-18 (`eda40099`)
The pacing counted CPU cycles and allowed a look at XCP_IN every 5 us
(`XCP_R5_POLL_PERIOD_US`). At 40 kHz the main loop only runs in the ~8 us
between two control ISRs (the ISR takes ~17 of every 25 us). So that came
to one or two looks per gap: 40,700 looks/s at 500 B/cycle and 21,200/s at
900 B/cycle, where a DAQ copy spans about three periods. The main loop's own
work per pass is small: three button reads and an LED write through the PS
GPIO controller.

Now the time base is `uz_SystemTime`'s interrupt counter (low word). The R5
looks at the XCP_IN header on every main-loop pass. It exchanges with the
A53 at most once per control period: after an exchange, the next one waits
for the next control ISR, so there is at most one IPI per period. The 1 ms
age, the heartbeat and the 5 ms hold are counted in control periods, and
`xcp_r5_sweep_gap_max_us` has the resolution of one period. The CPU cycle
counter remains the time base of the profile only.

Tried first: one look per control period, at the first pass after each ISR.
A command that lands after that look waits for the next period, which
would be up to 100 us at 10 kHz.

Measured on 2026-11-19 with nothing else on the board. The first
comparison, on the afternoon of 2026-11-18, ran while another agent session
was using the board, and is superseded. Each build was freshly flashed, in
the order chosen, old, one-look, one-look, old, chosen, plus two earlier
runs of the chosen build. Median command round trip in us
(`cmd_latency.py`, 2000 commands per load, 40 kHz):

| Pacing | 0 B | 500 B | 900 B | 1000 B |
|---|---|---|---|---|
| cycle counter, a look at most every 5 us | 218, 221 | 221, 225 | 267, 267 | 275, 273 |
| one look per control period | 219, 221 | 222, 225 | 275, 269 | 275, 284 |
| a look every pass, one exchange per period (chosen) | 224, 213, 213, 216 | 235, 219, 222, 221 | 272, 267, 265, 266 | 896, 271, 272, 274 |

- Single commands: the chosen pacing is as fast as the old one under DAQ
  load and a few microseconds faster idle. The 896 us is a run in which
  1000 B/cycle tipped into the slow copy (2.4). The one-look variant was
  up to ~10 us slower at 900-1000 B/cycle.
- DAQ throughput is the same on all three: 6808 DAQ exchanges/s at 900
  B/cycle, the same copy cost per KB and A53 idle time, no loss in any 20 s
  run. 24/24 functional checks on every run except the one with the tip
  (1472 records lost in the reconnect cycles). 40 short DAQ runs at 1000
  B/cycle (0.5 s each) per run: none of 240 lost data, on any build.
- Looks per second while DAQ runs: 53-56k at 500 B/cycle (old pacing
  40.7k, one-look 31k), 31k at 900 B (21k, 21k), 105k at 8 B (73k, 40k).
- Open: two costs of the chosen pacing that the other two do not show.
  - The control ISR is 0.2-0.5 us longer at 500 B/cycle in 6 of 8 runs
    (all 8: 16.48-17.08 us, against 16.46-16.59 us for the old pacing and
    the one-look variant in every run), and about 0.6 us longer in the
    slower state of the soaks below. Not at 8 B/cycle. The XCP
    sampling (`xcp_r5_event()`) is unchanged, so the time goes elsewhere
    in the ISR. Cause not found.
  - Back-to-back commands at 900 B/cycle for 10 min: the old pacing (2
    runs) and the one-look variant (1 run) stayed at a flat 251-253 us
    median, with 4-10 DAQ exchanges waiting for an acknowledge. The chosen
    pacing fell into a slower state in all 3 runs: once for 2 min (256-258
    us), once from minute 4 to the end (263 us; control ISR 17.56 instead of
    ~17.2 us on average; 4739 waits), and once it tipped into the slow copy
    after 4.5 min (948 us, 1.9 M records lost). At 1000 B/cycle it tipped
    after 1.5 min; the old pacing ran 10 min clean there on 2026-11-18
    (2.6).
  - The chosen pacing and the one-look variant differ only in the gate,
    three lines (checked on the flashed ELFs): the chosen one looks again
    on every later pass of a control period without an exchange. That is
    the obvious candidate, but in the 900 B/cycle soaks all three builds
    looked at XCP_IN about equally often (21-24k/s). The one-look
    variant's extra variable also shifts the R5's data by 16 bytes.
    JavaScope plays no part: with `UZ_LOGGING_PATH_XCP` the ISR calls
    `xcp_r5_event()` instead of `JavaScope_update()`.
- The rare A53 acknowledges of 220-350 us are older than this change and
  occur on every build: 295 us in a 10 min soak at 900 B/cycle on
  2026-11-17, 320 and 246 us on the morning of 2026-11-18, 348 and 320 us
  in the old pacing's 10 min soaks, and in 4 of 32 measurements on the
  quiet bench. With the other session on the board they were in 13 of 20.
  (Once the R5 has tipped into the slow copy, acknowledges are long anyway,
  because the chains are large.) Cause unknown. The R5 looks at least once
  per control period while it waits, so it is the A53 that answers late.

### 2.8 Repeated and lost datagrams: transmit buffer reused under the DMA — RESOLVED 2026-11-23 (`8fe168bf3`)
Symptom, in a CANape session at 40 kHz (the first with `lifecheck` on
`DAQ_R5`): "Ungültiger Zähler im XCP-Transport-Layer-Header" in bursts,
then "Timeout: Keine Response zur Request-Message empfangen!", which
stopped the measurement, and 46,420 backward timestamps on the bus.
Reconnecting worked.

Cause: the A53 tx task packed each datagram into one static buffer
(`batch[]`, since CP7 `fe1ebd1f6`) and refilled it as soon as
`lwip_sendto()` returned. lwIP does not copy the payload. With
`LWIP_NETIF_TX_SINGLE_PBUF` 0, `lwip_sendto()` wraps the caller's buffer in
a PBUF_REF (`netbuf_ref`), and the Xilinx driver (`emacps_sgsend`) points
the TX DMA descriptor at it. The GEM reads the payload when the frame
reaches the head of its TX ring. While frames queue there, each queued
datagram goes out with whatever the buffer holds at that moment. The UDP
checksum is still correct, because the GEM computes it (TX checksum
offload), so the PC accepts these frames.

Trigger: pause frames from the PC's Realtek USB adapter. Each holds the
GEM's transmitter, and frames queue meanwhile. The GEM received 166 in a
10 min session (GEM3 statistics register 0xFF0E0164, clear-on-read, read
over JTAG without halting).

Evidence, from a 180 s capture (dumpcap on the PC's adapter) of the faulty
session:
- 515,447 board datagrams with consecutive IP IDs in capture order. lwIP
  writes the IP ID into its own header pbuf, so this is the board's send
  order: no reordering and no loss on the wire.
- 160 datagrams carried the payload of another datagram, in 8 bursts. For
  example IP IDs 52052-52059 all carry the payload that starts at CTR
  55538, and the frames with CTR 55436-55537 never left the board.
- This also fits the GEM frames_txed counter matching the adapter's
  received count in the 2026-11-17/18 runs: every frame was sent, some with
  the wrong contents.

Fix: a ring of `XLWIP_CONFIG_N_TX_DESC + 1` (513) transmit buffers, 718 KB
of `.bss`. Each datagram takes the next buffer; the ring advances only
after a successful send. A queued datagram holds at least one TX
descriptor until it has been sent, so a buffer comes round again only when
its datagram is gone. Not chosen: `LWIP_NETIF_TX_SINGLE_PBUF` 1, where lwIP
copies every datagram, because it changes the lwIP settings.

Verified 2026-11-23, CANape session at 40 kHz:
- 10 min capture, 1,717,812 board datagrams: IP IDs consecutive, 0
  repeated payloads, counter continuous, while the GEM received the 166
  pause frames above.
- Gateway counters (JTAG): `sendto_drop`, `txq_dropped` and `master_lost`
  0; `sendto_err` 1, delivered by the retry.
- CANape: 1.5 h without a warning.

This replaces earlier conclusions, all most likely this defect: the "ctr
gaps ... reordering in the PC" of 2026-11-17/18 (STATUS), the rare lost
responses (2.6), and the July "net wire loss 0.00055 %" put down to the PC
NIC (STATUS, HARDWARE VALIDATED). `xcp_poll.py --stress` offset the
duplicates against the gaps ("late, not lost") and so hid the loss. Since
`a285f569d` it checks every counter value (missing, duplicated, late). On
the capture of the faulty session the new check finds 2276 duplicated
frames and as many missing ones; the old accounting found 5 "net lost",
which are capture artefacts.

### 2.9 Control-ISR jitter from the XCP load — measured 2026-11-24, flush part RESOLVED (`6dd56602d`)

`ISR_period_us` and `ISR_execution_time_us` in a CANape recording (40 kHz,
~78 Mbit/s) showed a spike of ~2 us once per ms, smaller bumps and ~1 us of
period jitter. Measured with `tools/xcp_test/isr_jitter.py` and
`UZ_ISR_DIAG 1` (`fe3e2fdd1`, R5 cycle counter per ISR section, PMU
counts, main-loop phase at the interrupt); numbers in STATUS.md, bench run
2026-11-24.

Causes:

1. **`daq_1ms` event (the 1 ms spike).** A time-slice event with a DAQ
   list costs about 1 us, plus about 0.1 us per extra ODT entry in a cold
   cache line. The 23 diagnostic counters of the CANape project sit in 9
   places (DDR and OCM): +2.2 us every 40th cycle. An empty slice event
   costs 0.3 us.
2. **Cache flush with interrupts masked (period jitter).** RESOLVED:
   `Xil_DCacheFlushRange` masks IRQ/FIQ over the range and its DSB; the
   main loop flushed the DAQ chain with it in 1 KB pieces, and the ISR
   started up to 2 us late. The chain is now flushed line by line with
   interrupts enabled (the loop of `Xil_DCacheFlushRange` without its
   lock). Not a fix: `Xil_DCacheFlushRange` in 128 or 32 B pieces. Same
   start delay, but every call waits for its own write-back: flush CPU time
   2.36 and 4.07 us/KB instead of 1.29, the exchanges took 19.9 and 30.5 %
   of the R5 instead of 16.1 % (900 B/cycle).
3. **ISR interrupting the DAQ copy (the smaller bumps).** The copy into the
   OCM leaves write-backs in flight and evicts ISR data. The ISR then has
   about twice the D-cache misses, and its accesses to the PL wait longer:
   the BSP maps 0x80000000-0xBFFFFFFF (all PL IP cores) as strongly
   ordered (`mpu.c`), so every PL access waits until all earlier writes
   are complete. +0.3 us median, up to +1.5 us.

Open, for a decision:

- Put slow diagnostic counters on `daq_100ms` or `daq_1s`; the spike stays
  ~2 us but comes 100 or 1000 times less often.
- The PL range as Device instead of strongly ordered memory. 9.1 us of the
  16 us ISR are LSU stall cycles; the 15 PWM register writes alone take
  9.8 us (~650 ns each, each waiting for its write response). Device
  writes are posted, and Device accesses do not wait for earlier writes to
  normal memory, which would also remove most of cause 3. Platform-wide
  change: a PL write is then no longer complete when the next instruction
  runs, and PL accesses are no longer ordered against normal-memory
  accesses; whether any IP core driver relies on that has to be checked.
  Not tried.
- Remaining start delay: p99 0.5 us, max 1.1 us when the ISR hits the copy
  (queue lock, timer read behind write-backs); < 0.2 us p99 otherwise.

### 2.10 OCM rings instead of the main-loop exchange — prototype 2026-11-26 (`feature/ocm_ring`)
Option 1 of 2.4 (a ring buffer in OCM), built on the JavaScope ring
prototype (`feature/ipc_ring_buffer_v2`) generalised to variable-length
records (`shared/uz_ocm_ring.h`). Three rings (`shared/ocm_xcp_ring.h`):
DAQ (control ISR -> A53, the engine writes the DTOs in place), RSP (main
loop -> A53, responses) and CMD (A53 -> main loop, commands). The OCM map
changed with it: boot handshakes in bank 0, user data in bank 1, XCP in
banks 2+3 (`APU_RPU_shared.h`).
- Removed: queue32 (128 KB in DDR), the main-loop copy, the chain
  acknowledge and its pacing (2.5, 2.7), the seqlock, the CTO mailbox and
  the command generations (`ocm_xcp_fifo.c/.h` on both cores).
- Measured (STATUS, bench run 2026-11-26): ISR median +0.4-0.8 us up to
  ~1 KB/cycle, but the spread drops from up to 2.3 us to 0.7 us and the
  start delay p99 stays at 0.19 us under load; the R5 has 13 points more
  free time at 300 Mbit/s (40 kHz); no loss at 300 Mbit/s at 40 and 10 kHz;
  commands unchanged.
- The bistability of 2.4 (acknowledge waits, cold copy source) has no
  mechanism left: the DTOs go to OCM in the cycle they are sampled.
- Open: JavaScope on the same ring (separate PR); the publish's fixed part
  (~0.3 us per cycle even at 48 B) could be saved by publishing only every
  n-th cycle at low rates; `XCP_R5_DAQ_NOTIFY_BYTES` (4 KB) not tuned;
  ring start-up assumes the two cores do not initialise at the same
  instant (stale positions are reconciled, a simultaneous init is not).

### 2.11 Throughput limit and DAQ budget on the rings — 2026-11-27
Sweep at 40 kHz with `xcp_poll.py --stress` (STATUS, bench run 2026-11-27):
- Clean up to 1350 B per cycle (432 Mbit/s): the cycle's two DTOs share
  one 1400-byte datagram, 40k datagrams/s, A53 34 % idle. From 1400 B per
  cycle they need two datagrams, and the A53 manages only ~60-70k per
  second (~11.8 us per datagram + ~3.4 ns per byte): `xcp_gw_txq_dropped`.
  The A53, not the R5, sets the throughput limit.
- 1472-byte datagrams raised the limit to 1450 B per cycle (464 Mbit/s),
  but `lwip_sendto` took 13.1 us from 1464 bytes on instead of 5.9 us (cause
  not found), so the size went back to 1400 (`2505516ec`).
- The R5 locks itself out: at 2500 B per cycle the ISR took 22.5 of 25 us,
  from ~2800 B the main loop starved, and at 3125 B the STOP command never
  ran (only reprogramming recovered). **DAQ budget** (`14ade483d`): the
  start of a DAQ setup whose worst control cycle exceeds
  `xcp_r5_daq_budget_bytes` is refused with `ERR_DAQ_CONFIG`; default
  400 Mbit/s divided by the control rate (1250 B at 40 kHz).
- `xcp_poll.py` printed PASSED while the A53 dropped data before the
  transport counter was stamped; it now fails on `xcp_r5_queue_lost` and
  `xcp_gw_txq_dropped` (`43d4deadf`).
- Open: denser packing would raise the A53 limit (DTOs sized to fill a
  datagram, e.g. MAX_DTO ~692, cost more ODTs on the R5); the `lwip_sendto`
  step at 1464 bytes is unexplained.

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

- **8-byte values** (2026-11-27): a `double` or `int64_t` is written with
  IRQ and FIQ masked (`XCP_WRITE64`, UZ patch in `XcpWriteMta` case 8;
  `xcp_r5_write64()` in `xcptl_ocm.c`). 1-, 2- and 4-byte values were single
  stores already.

Still open (full Z5 review): range checks per parameter, consistent
adoption of values larger than 8 bytes or of several values together
(proposed: upstream calibration segments), rollback.

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
kept `0x1 SIZE_DWORD UNIT_1US TIMESTAMP_FIXED`, which is what upstream's
own A2L writer still emits). Since 2026-11-23 the DAQ clock is the 100 MHz
AXI timer of `uz_SystemTime` (`CLOCK_TICKS_PER_S` 100000000, reported as
`UNIT_1NS` with 10 ticks; A2L `0x0A SIZE_DWORD UNIT_1NS`), see STATUS.

Local patches on top of upstream, every one marked `UZ` in the source and
default-off where it touches engine behaviour (re-apply after the next
upgrade — the list is also in the session memory of the coding agent):
- `platform.h`: `ARMR5` → `_BAREMETAL` platform branch (atomics, IRQ
  critical-section mutex, no threads).
- `xcpappl.c`: `_BAREMETAL` accepted as platform, base address 0.
- `xcptl_cfg.h`: `XCPTL_MAX_DTO_SIZE` and `XCPTL_MAX_SEGMENT_SIZE` may be
  predefined (`xcplib_r5_cfg.h` sets 1024 and 1400, the datagram size of
  the A53 gateway; upstream would derive 1472 from the MTU).
- `xcplib_cfg.h`: includes `xcplib_r5_cfg.h` at the end.
- `xcp_cfg.h`: `OPTION_DISABLE_DYN_ADDRESSING` switch (R5 has no
  `XcpEventExt` context to execute event-relative commands).
- `xcplite.c`: `XCP_ENABLE_MTA_RANGE_CHECK` (size check on every
  `XcpReadMta`/`XcpWriteMta`), `XCP_MTA_WRITE_CHECK` (write gate, 3.1),
  `calcChecksum` size-0 error and `XCP_CHECKSUM_MAX_SIZE` cap,
  `XCP_WRITE64` (8-byte writes atomic against the ISR, 3.1, 2026-11-27),
  `XCP_DAQ_START_CHECK` with `XcpGetDaqEventLoad()` (DAQ budget, 2.11,
  2026-11-27).
- `xcplite.h`: prototype of `XcpGetDaqEventLoad()`.
- `queue32.c` is no longer in the tree: the OCM rings implement the queue
  API in `xcptl_ocm.c` (2.10). Its `packets_lost` patch is obsolete.

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
