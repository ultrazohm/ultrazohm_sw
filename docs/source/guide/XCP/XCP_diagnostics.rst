.. _xcp_diagnostics:

===============
XCP diagnostics
===============

The XCP transport counter on the wire is stamped by the A53 when it sends a datagram.
It is always gapless, so the XCP master cannot see data that was lost inside the UltraZohm.
Both processors count such events instead, and all counters can be read over XCP itself.

Where data can wait or get lost
-------------------------------

.. mermaid::
    :align: center
    :caption: Buffers on the way of the measurement data and the counter that belongs to each of them

    flowchart LR
      isr["R5 ISR_Control"] --> q1["R5 DAQ queue<br>32 KB"]
      q1 --> out["XCP_OUT<br>32 KB"]
      out --> q2["A53 DAQ queue<br>262144 frames"]
      q2 --> udp["UDP send"]
      udp --> pc["PC"]
      q1 -. "full" .-> c1["xcp_r5_queue_lost"]
      out -. "not acknowledged for 50 sweeps" .-> c2["xcp_r5_out_overwritten"]
      q2 -. "full" .-> c3["xcp_gw_txq_dropped"]
      udp -. "send failed after retries" .-> c4["xcp_gw_sendto_drop"]
      pc -. "gap in transport counter" .-> c5["loss on the wire or in the PC"]

A gap in the transport counter with ``xcp_gw_sendto_drop`` unchanged was lost on the wire or in the PC, not in the UltraZohm.

Reading the counters
--------------------

- **CANape**: the counters are measurement objects in ``CANape/UZ_XCP/uz.A2L``.
- **xcp_poll.py**: ``--stress`` prints the change of every counter over the run. A single counter can be read with ``--watch <name>:u32``.
- **gen_a2l.py**: ``--diag`` adds the counters to a generated A2L file.

The counters of the R5 are global variables of the Baremetal application.
The counters of the A53 are copied on every interrupt into the header of ``XCP_IN`` at fixed addresses from ``0xFFFFC008`` and are read through the R5 like any other memory.

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
     - Result of ``xcp_r5_init()``. Negative: the engine is disabled.
   * - ``xcp_r5_cycle_count``
     - counts up
     - One count per call of ``ISR_Control``.
   * - ``xcp_r5_sweep_count``
     - counts up
     - One count per exchange sweep of the main loop.
   * - ``xcp_r5_sweep_gap_max_us``
     - about 100
     - Longest time between two sweeps. A large value means that something blocks the main loop.
   * - ``xcp_r5_queue_lost``
     - 0
     - Samples dropped because the DAQ queue of the R5 was full. This is the loss counter for measurement data on the R5.
   * - ``xcp_r5_tx_held``
     - may count
     - Sweeps that filled ``XCP_OUT`` completely. The rest waited in the queue. A steady increase means the measurement produces more data than the exchange can carry.
   * - ``xcp_r5_out_held``
     - may count
     - Sweeps that kept the previous chain because the A53 had not acknowledged it yet. Delay, not loss.
   * - ``xcp_r5_out_overwritten``
     - 0
     - Chains given up after 50 sweeps without acknowledge. The gateway is not running or stalled.
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
     - Command batches that were executed over several sweeps.
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
     - The interrupt arrived while the R5 was writing. The read is repeated.
   * - ``xcp_gw_ocm_torn``
     - ``0xFFFFC00C``
     - may count
     - The R5 changed ``XCP_OUT`` during the read. The read is repeated.
   * - ``xcp_gw_ocm_cycles_missed``
     - ``0xFFFFC010``
     - may count
     - Sweeps of the R5 that no interrupt read. Indicates interrupt latency on the A53.
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
     - Response queue full.
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
     - Datagram from the network with a broken frame structure, for example from a port scanner.
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

Troubleshooting
---------------

.. list-table::
   :header-rows: 1
   :widths: 35 65

   * - Symptom
     - Check
   * - No response to ``CONNECT``
     - Serial console: is the XCP banner printed, is there a logging path mismatch warning? Is UDP port 5556 blocked by a firewall on the PC? Were both applications flashed?
   * - ``CONNECT`` works, reading a variable gives ``ERR_ACCESS_DENIED``
     - The address is outside the memory of the R5. The A2L file or the ELF file does not belong to the firmware on the board.
   * - A write gives ``ERR_WRITE_PROTECTED``
     - The target is not a global or ``static`` variable (for example a constant), or the firmware was built with ``XCP_R5_READ_ONLY``.
   * - Measurement does not start, ``DAQ_CONFIG`` error
     - The A2L file must limit ODT entries to 240 bytes.
   * - A complete structure cannot be added in CANape
     - The A2L file needs a structure description, see :ref:`xcp_usage`.
   * - Values are plausible but shifted or wrong
     - The addresses are stale. Reload the A2L file after building, or point the master to the current ELF file.
   * - Gaps in the measurement, no counter of the UltraZohm changed
     - Loss in the network or in the PC. Increase the receive buffer of the PC or reduce the data rate with a slower raster.
   * - ``xcp_r5_queue_lost`` increases
     - More data than the path can carry, or the main loop of the R5 is blocked (``xcp_r5_sweep_gap_max_us``).
   * - CANape reports a timeout during a running measurement
     - Use a command timeout ``T1`` of 5000 ms in the A2L file.
   * - Measurement stops by itself, ``xcp_gw_master_lost`` increased
     - The gateway could not send for about one second, or the optional silence timeout expired.

The complete bring-up procedure with expected outputs is kept in ``option_z/TEST_PLAN.md`` of the repository.
