.. _xcp_diagnostics:

===============
XCP diagnostics
===============

The A53 stamps the XCP transport counter when it sends a datagram.
Data that was lost before this point, in one of the buffers of the UltraZohm, leaves no gap in the counter, so the XCP master cannot see such a loss.
Both processors count these events instead, and all counters can be read over XCP itself.

Where data can wait or get lost
-------------------------------

.. mermaid::
    :align: center
    :caption: Buffers on the way of the measurement data and the counter that belongs to each of them

    flowchart TB
      isr["R5 ISR_Control"] --> q1["R5 DAQ queue, 128 KB"]
      q1 --> out["XCP_OUT, 32 KB"]
      out --> q2["A53 DAQ queue, 65536 records"]
      q2 --> udp["UDP send"]
      udp --> pc["PC"]
      q1 -. "full" .-> c1(["xcp_r5_queue_lost"])
      out -. "no acknowledge<br>for 5 ms" .-> c2(["xcp_r5_out_overwritten"])
      q2 -. "full" .-> c3(["xcp_gw_txq_dropped"])
      udp -. "failed after<br>all retries" .-> c4(["xcp_gw_sendto_drop"])

A datagram that could not be sent (``xcp_gw_sendto_drop``) is the only loss inside the UltraZohm that the master sees as a gap in the transport counter.
A gap with this counter unchanged was lost on the wire or in the PC.

Reading the counters
--------------------

- **CANape**: ``CANape/UZ_XCP/uz.A2L`` contains all counters of the A53 and the loss counters of the R5, for example ``xcp_r5_queue_lost`` and ``xcp_r5_out_overwritten``. The other R5 counters can be added from the ELF file like any other variable.
- **xcp_poll.py**: ``--stress`` prints the change of all A53 counters and of most R5 counters over the run. A single R5 counter can be read with ``--watch <name>:u32``, a counter of the A53 with its address, for example ``--watch 0xFFFFC034:u32``.
- **gen_a2l.py**: a generated A2L file always contains the counters of the A53. ``--diag`` adds those of the R5.

The counters of the R5 are global variables of the Baremetal application.
The counters of the A53 are copied on every interrupt and for every command into the header of ``XCP_IN`` at fixed addresses from ``0xFFFFC008`` and are read through the R5 like any other memory.

R5 counters
-----------

.. list-table::
   :header-rows: 1
   :widths: 30 15 55

   * - Counter
     - Expected
     - Meaning
   * - ``xcp_r5_init_result``
     - 0
     - Result of ``xcp_r5_init()``. Negative: the initialisation failed and the engine is disabled. ``0x7FFFFFFF``: ``xcp_r5_init()`` was not called.
   * - ``xcp_r5_cycle_count``
     - counts up
     - One count per call of ``ISR_Control``.
   * - ``xcp_r5_sweep_count``
     - counts up
     - One count per exchange with the A53: measurement data, commands or the 1 ms heartbeat.
   * - ``xcp_r5_sweep_gap_max_us``
     - below 1000
     - Longest time between two passes of the main loop through ``xcp_r5_background()`` since start-up, in microseconds, including the exchanges themselves. It is counted in whole control periods (25 µs steps at 40 kHz). A single slow pass raises it for good. A large value means that something blocks the main loop, and commands wait that long.
   * - ``xcp_r5_queue_lost``
     - 0
     - Measurement data dropped because the DAQ queue of the R5 was full. This is the loss counter for measurement data on the R5.
   * - ``xcp_r5_tx_held``
     - may count
     - Exchanges that filled ``XCP_OUT`` completely. The rest waited in the queue. A steady increase means the measurement produces more data than the exchange can carry.
   * - ``xcp_r5_out_held``
     - may count
     - Exchanges of measurement data that were due before the A53 had acknowledged the previous chain, counted once per chain. Delay, not loss.
   * - ``xcp_r5_out_overwritten``
     - 0
     - Chains given up after 5 ms without acknowledge. Their data is lost. The gateway is not running or stalled.
   * - ``xcp_r5_cto_sent``
     - counts up
     - Command responses handed to the mailbox.
   * - ``xcp_r5_cto_dropped``
     - 0
     - Responses that could not be stored. The master sees a timeout.
   * - ``xcp_r5_in_generations``
     - counts up
     - Command batches executed.
   * - ``xcp_r5_in_resumed``
     - may count
     - Exchanges that had to interrupt a command batch because four responses were already waiting for the mailbox. The batch continues in the next exchange.
   * - ``xcp_r5_cmd_oversize_drop``
     - 0
     - Commands longer than 248 bytes that were refused.
   * - ``xcp_r5_write_denied``
     - 0
     - Calibration writes refused by the memory access rules.
   * - ``ocm_xcp_w_dropped``, ``ocm_xcp_r_overrun``, ``xcp_r5_tx_oversize_drop``
     - 0
     - Internal consistency checks of the OCM exchange.

A53 gateway counters
--------------------

.. list-table::
   :header-rows: 1
   :widths: 30 15 15 40

   * - Counter
     - Address
     - Expected
     - Meaning
   * - ``xcp_gw_ocm_skipped_writing``
     - ``0xFFFFC008``
     - may count
     - The interrupt arrived while the R5 was writing, or the R5 changed the header during the copy. The response mailbox and the acknowledges are taken with the next interrupt. The DAQ chain is read anyway.
   * - ``xcp_gw_ocm_torn``
     - ``0xFFFFC00C``
     - may count
     - The R5 rewrote the DAQ chain while the A53 was reading it. The read is discarded, and the new chain is read with the next interrupt. Rare, because the R5 rewrites a chain with data only after the A53 confirmed it.
   * - ``xcp_gw_ocm_cycles_missed``
     - ``0xFFFFC010``
     - may count
     - Exchanges of the R5 that no interrupt read. Indicates interrupt latency on the A53, not a loss.
   * - ``xcp_gw_ocm_capped``
     - ``0xFFFFC014``
     - 0
     - More than 128 records in one read. The rest of that chain is lost.
   * - ``xcp_gw_txq_dropped``
     - ``0xFFFFC018``
     - 0
     - DAQ queue of the A53 full. The network is slower than the measurement.
   * - ``xcp_gw_ctoq_dropped``
     - ``0xFFFFC01C``
     - 0
     - Response queue full. A response or an event was lost.
   * - ``xcp_gw_in_batches_sent``
     - ``0xFFFFC020``
     - counts up
     - Command batches offered to the R5.
   * - ``xcp_gw_in_retry_cycles``
     - ``0xFFFFC024``
     - may count
     - Interrupts that offered a batch again.
   * - ``xcp_gw_tx_malformed_drop``
     - ``0xFFFFC028``
     - 0
     - Record from the R5 with a broken frame structure.
   * - ``xcp_gw_rx_malformed_drop``
     - ``0xFFFFC02C``
     - 0
     - Datagram from the network with a broken frame structure or a command longer than 248 bytes, for example from a port scanner.
   * - ``xcp_gw_sendto_err``
     - ``0xFFFFC030``
     - may count
     - Send attempts that failed and were repeated.
   * - ``xcp_gw_sendto_drop``
     - ``0xFFFFC034``
     - 0
     - Datagrams dropped after all retries. The only source of transport counter gaps inside the UltraZohm.
   * - ``xcp_gw_ipi_count``
     - ``0xFFFFC038``
     - counts up
     - Interrupts handled by the gateway.
   * - ``xcp_gw_txq_level``
     - ``0xFFFFC03C``
     - 0 when idle
     - Current fill level of the DAQ queue. Not a counter.
   * - ``xcp_gw_master_lost``
     - ``0xFFFFC040``
     - 0
     - Sessions that the gateway closed because the master was unreachable.

Time profile of the R5
----------------------

The R5 also measures where its time goes.
It times every exchange and every call of ``xcp_r5_event()`` with its CPU cycle counter and keeps the sums in the global structure ``xcp_r5_prof``.
``xcp_poll.py --stress`` clears the sums before a run, reads them at the end of the run while DAQ is still running, and prints:

- the exchanges per second, how many of them carried measurement data and how many only commands, and the wall time of one exchange,
- the wall time of each phase of an exchange: refreshing the command region, executing commands, copying DAQ data into ``XCP_OUT`` and flushing the cache,
- the copy and flush time per KB of DAQ data, once as wall time and once as CPU time without the control interrupts that hit the phase,
- how the time of the R5 splits into the control interrupt, the exchanges and the rest of the main loop,
- the run time of the control interrupt per cycle and the part of it spent in ``xcp_r5_event()``,
- how long the A53 took to acknowledge a chain of measurement data after the interrupt, and how often the R5 looked at ``XCP_IN``.

The profile costs a few reads of the cycle counter per exchange and per control cycle.
It is switched off with ``XCP_R5_PROFILE`` set to ``0`` in ``xcp_r5.h``.

Time profile of the A53
-----------------------

The gateway measures its own time with the system counter of the A53 and copies the sums into the last words of the counter area in ``XCP_IN``.
``xcp_poll.py --stress`` prints them next to the profile of the R5:

- how the time of the A53 splits into idle time, the interrupt hook, the tx task and everything else (network stack, interrupts of the Ethernet controller, other tasks, and the task switch after every datagram of the tx task),
- the time of the interrupt hook per interrupt and per record of measurement data,
- the datagrams per second, their average size, and the time of one ``lwip_sendto()`` call.

The idle time comes from a task at the idle priority that only runs when nothing else needs the processor.
The profile is switched off with ``XCP_GW_PROFILE`` set to ``0`` in ``xcp_gateway_a53.h``.

The engine contains consistency checks from upstream XCPlite, some of them in the code that runs in the control interrupt.
The Debug build of Vitis keeps them active, and a failing check stops the R5.
To measure what they cost, or to build without them, set ``XCP_R5_ENGINE_ASSERTS`` to ``0`` in ``xcplib_r5_cfg.h``.

Troubleshooting
---------------

.. list-table::
   :header-rows: 1
   :widths: 35 65

   * - Symptom
     - Check
   * - No response to ``CONNECT``
     - Serial console: is the XCP banner printed, is there a logging path mismatch warning? Does the master use UDP and port 5556? Is the port blocked by a firewall on the PC? Were both applications flashed?
   * - ``CONNECT`` works, reading a variable gives ``ERR_ACCESS_DENIED``
     - The address is outside the memory of the R5. The A2L file or the ELF file does not belong to the firmware on the board.
   * - A write gives ``ERR_WRITE_PROTECTED``
     - The target is not a global or ``static`` variable (for example a constant), or the firmware was built with ``XCP_R5_READ_ONLY``.
   * - Measurement does not start, ``ERR_DAQ_CONFIG``
     - The A2L file must limit ODT entries to 240 bytes.
   * - Measurement does not start, ``ERR_MEMORY_OVERFLOW``
     - The measurement configuration is larger than the DAQ tables of the R5 (about 1000 signals). Measure fewer signals or raise ``OPTION_DAQ_MEM_SIZE`` in ``xcplib_r5_cfg.h``.
   * - A complete structure cannot be added in CANape
     - The A2L file needs a structure description, see :ref:`xcp_usage`.
   * - Values are plausible but shifted or wrong
     - The addresses are stale. Load the CANape project again after building, or generate the A2L file again. For a complete structure also check that its description matches the current layout, see :ref:`xcp_usage`.
   * - Gaps in the measurement, no counter of the UltraZohm changed
     - Loss in the network or in the PC. Increase the receive buffer of the PC or reduce the data rate with a slower raster.
   * - ``xcp_r5_queue_lost`` increases
     - More data than the path can carry, or the main loop of the R5 is blocked (``xcp_r5_sweep_gap_max_us``).
   * - CANape reports a timeout during a running measurement
     - Use a command timeout ``T1`` of 5000 ms in the A2L file.
   * - Measurement stops by itself, ``xcp_gw_master_lost`` increased
     - The gateway could not send for about one second, for example because the Ethernet link was down, or the optional silence timeout expired.

The complete bring-up procedure with expected outputs is kept in ``option_z/TEST_PLAN.md`` of the repository.
