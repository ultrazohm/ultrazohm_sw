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
      isr["R5 ISR_Control"] --> ring["DAQ ring in the OCM, 112 KB"]
      ring --> q2["A53 DAQ queue, 65536 segments"]
      q2 --> udp["UDP send"]
      udp --> pc["PC"]
      ring -. "full" .-> c1(["xcp_r5_queue_lost"])
      q2 -. "full" .-> c3(["xcp_gw_txq_dropped"])
      udp -. "failed after<br>all retries" .-> c4(["xcp_gw_sendto_drop"])

A datagram that could not be sent (``xcp_gw_sendto_drop``) is the only loss inside the UltraZohm that the master sees as a gap in the transport counter.
A gap with this counter unchanged was lost on the wire or in the PC.

Commands take the opposite way through the CMD ring.
A command datagram that does not fit into it is dropped and counted in ``xcp_gw_cmd_dropped``; the master repeats the command after its timeout.

To check a recording itself for lost samples, measure ``lifecheck`` (in ``CANape/UZ_XCP/uz.A2L``) on the event ``DAQ_R5``.
It counts the control cycles modulo 1000 and is refreshed right before the sampling, so consecutive samples differ by 1, from 999 back to 0.
Any other step is a loss, wherever it happened.
``javascope/check_lifecheck.py``, written for JavaScope logs, finds such steps in a CSV file with ``;`` as separator, ``.`` as decimal point, one header row and a column whose name contains ``lifecheck``.
``interrupt_counter`` is the same count without the wrap.

Reading the counters
--------------------

- **CANape**: ``CANape/UZ_XCP/uz.A2L`` contains all counters of the A53 and the loss counters of the R5, for example ``xcp_r5_queue_lost``. The other R5 counters can be added from the ELF file like any other variable.
- **xcp_poll.py**: ``--stress`` prints the change of all A53 counters and of most R5 counters over the run. A single R5 counter can be read with ``--watch <name>:u32``, a counter of the A53 with its address, for example ``--watch 0xFFFFC034:u32``.
- **gen_a2l.py**: a generated A2L file always contains the counters of the A53. ``--diag`` adds those of the R5.

The counters of the R5 are global variables of the Baremetal application.
The A53 writes its counters into the OCM at fixed addresses from ``0xFFFFC008`` on every IPI, and they are read through the R5 like any other memory.

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
   * - ``xcp_r5_sweep_gap_max_us``
     - below 1000
     - Longest time between two passes of the main loop through ``xcp_r5_background()`` since start-up, in microseconds, including the commands themselves. It is counted in whole control periods (25 µs steps at 40 kHz). A single slow pass raises it for good. A large value means that something blocks the main loop, and commands wait that long.
   * - ``xcp_r5_queue_lost``
     - 0
     - DTOs dropped because the DAQ ring was full: the A53 did not take the data fast enough. This is the loss counter for measurement data on the R5.
   * - ``xcp_r5_daq_ipis``
     - counts up
     - IPIs from the control interrupt that announced measurement data.
   * - ``xcp_r5_rsp_ipis``
     - counts up
     - IPIs from the main loop that announced responses.
   * - ``xcp_r5_cto_sent``
     - counts up
     - Command responses and events written into the RSP ring.
   * - ``xcp_r5_cto_dropped``
     - 0
     - Responses that did not fit into the RSP ring. The master sees a timeout.
   * - ``xcp_r5_cmd_records``
     - counts up
     - Command datagrams executed.
   * - ``xcp_r5_cmd_waits``
     - may count
     - Passes of the main loop that left a command waiting because the RSP ring had no room for its response yet. Delay, not loss.
   * - ``xcp_r5_cmd_oversize_drop``
     - 0
     - Commands longer than 248 bytes that were refused.
   * - ``xcp_r5_cmd_ring_bad``
     - 0
     - Corrupt records in the CMD ring that were skipped.
   * - ``xcp_r5_write_denied``
     - 0
     - Calibration writes refused by the memory access rules.
   * - ``xcp_r5_daq_budget_bytes``
     - 1250 at 40 kHz
     - The DAQ budget per control cycle, see :ref:`xcp_architecture_budget`. Not a counter.
   * - ``xcp_r5_daq_cycle_bytes``
     - below the budget
     - Bytes of the worst control cycle of the last measurement start, accepted or not. Not a counter.
   * - ``xcp_r5_daq_budget_refused``
     - 0
     - Measurement starts refused with ``ERR_DAQ_CONFIG`` because they exceeded the budget.

A53 gateway counters
--------------------

.. list-table::
   :header-rows: 1
   :widths: 30 15 15 40

   * - Counter
     - Address
     - Expected
     - Meaning
   * - ``xcp_gw_ring_bad``
     - ``0xFFFFC008``
     - 0
     - Corrupt records in the DAQ or RSP ring that the gateway skipped.
   * - ``xcp_gw_daq_level_max``
     - ``0xFFFFC00C``
     - well below 114688
     - Highest fill level of the DAQ ring in bytes seen by an interrupt. It shows how close the R5 came to dropping measurement data. Not a counter.
   * - ``xcp_gw_cmd_dropped``
     - ``0xFFFFC010``
     - 0
     - Command datagrams dropped because the CMD ring was full. The R5 main loop does not take commands; the master repeats them.
   * - ``xcp_gw_drain_capped``
     - ``0xFFFFC014``
     - may count
     - Interrupts that left measurement data in the DAQ ring because of the limit of 32 KB per interrupt. The next interrupt takes it. Delay, not loss.
   * - ``xcp_gw_txq_dropped``
     - ``0xFFFFC018``
     - 0
     - DAQ queue of the A53 full, a segment was dropped. The A53 or the network is slower than the measurement.
   * - ``xcp_gw_ctoq_dropped``
     - ``0xFFFFC01C``
     - 0
     - Response queue full. A response or an event was lost.
   * - ``xcp_gw_cmd_records``
     - ``0xFFFFC020``
     - counts up
     - Command datagrams handed to the R5.
   * - ``xcp_gw_daq_records``
     - ``0xFFFFC024``
     - counts up
     - DTOs taken from the DAQ ring.
   * - ``xcp_gw_tx_malformed_drop``
     - ``0xFFFFC028``
     - 0
     - Segment with a broken frame structure before sending.
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
     - Current fill level of the DAQ queue in segments. Not a counter.
   * - ``xcp_gw_master_lost``
     - ``0xFFFFC040``
     - 0
     - Sessions that the gateway closed because the master was unreachable.

Time profile of the R5
----------------------

The R5 also measures where its time goes.
It times every call of ``xcp_r5_event()`` and the execution of commands with its CPU cycle counter and keeps the sums in the global structure ``xcp_r5_prof``.
``xcp_poll.py --stress`` clears the sums before a run, reads them at the end of the run while DAQ is still running, and prints:

- the run time of the control interrupt per cycle and the part of it spent in ``xcp_r5_event()``, on average and at most,
- how this part splits into writing the DTOs into the DAQ ring and publishing them (cache clean and write position),
- the data rate into the DAQ ring and the cost of sampling and publishing per KB,
- the IPIs from the control interrupt per second,
- how the time of the R5 splits into the control interrupt and the execution of commands.

The profile costs a few reads of the cycle counter per control cycle.
It is switched off with ``XCP_R5_PROFILE`` set to ``0`` in ``xcp_r5.h``.

Time profile of the A53
-----------------------

The gateway measures its own time with the system counter of the A53 and writes the sums behind its counters into the OCM.
``xcp_poll.py --stress`` prints them next to the profile of the R5:

- how the time of the A53 splits into idle time, the interrupt hook, the tx task and everything else (network stack, interrupts of the Ethernet controller, other tasks, and the task switch after every datagram of the tx task),
- the interrupts per second and the time of the interrupt hook, and per segment of measurement data the time to copy it out of the OCM and into the queue,
- the datagrams per second, their average size, the time of one ``lwip_sendto()`` call and the time of the tx task per datagram.

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
     - Serial console: is the XCP banner printed, is there a logging path mismatch warning? Does ``APU: XCP CONNECT from ...`` appear? If not, the command does not reach the board. Does the master use UDP and port 5556? Is the port blocked by a firewall on the PC? Were both applications flashed?
   * - ``CONNECT`` works, reading a variable gives ``ERR_ACCESS_DENIED``
     - The address is outside the memory of the R5. The A2L file or the ELF file does not belong to the firmware on the board.
   * - A write gives ``ERR_WRITE_PROTECTED``
     - The target is not a global or ``static`` variable (for example a constant), or the firmware was built with ``XCP_R5_READ_ONLY``.
   * - Measurement does not start, ``ERR_DAQ_CONFIG``
     - Either the measurement exceeds the DAQ budget (``xcp_r5_daq_budget_refused`` increased; compare ``xcp_r5_daq_cycle_bytes`` with ``xcp_r5_daq_budget_bytes``): measure less on ``DAQ_R5`` or move signals to a slower raster, see :ref:`xcp_architecture_budget`. Or the A2L file allows ODT entries larger than 240 bytes.
   * - Measurement does not start, ``ERR_MEMORY_OVERFLOW``
     - The measurement configuration is larger than the DAQ tables of the R5 (about 1000 signals). Measure fewer signals or raise ``OPTION_DAQ_MEM_SIZE`` in ``xcplib_r5_cfg.h``.
   * - A complete structure cannot be added in CANape
     - The A2L file needs a structure description, see :ref:`xcp_usage`.
   * - Values are plausible but shifted or wrong
     - The addresses are stale. Load the CANape project again after building, or generate the A2L file again. For a complete structure also check that its description matches the current layout, see :ref:`xcp_usage`.
   * - Gaps in the measurement, no counter of the UltraZohm changed
     - Loss in the network or in the PC. Increase the receive buffer of the PC or reduce the data rate with a slower raster.
   * - ``xcp_gw_txq_dropped`` increases
     - The A53 cannot send the datagrams fast enough. At 40 kHz the DTOs of one control cycle must fit into one datagram of 1400 bytes; measure less on ``DAQ_R5`` or move signals to a slower raster.
   * - ``xcp_r5_queue_lost`` increases
     - The A53 does not empty the DAQ ring: the gateway is stalled or not running, or more data arrives than it can carry (then ``xcp_gw_daq_level_max`` is close to 114688).
   * - Commands are slow or time out during a measurement
     - The main loop of the R5 gets too little time (``xcp_r5_sweep_gap_max_us``). Check that the DAQ budget was not raised.
   * - CANape reports a timeout during a running measurement
     - Use a command timeout ``T1`` of 5000 ms in the A2L file.
   * - Measurement stops by itself, ``xcp_gw_master_lost`` increased
     - The gateway could not send for about one second, for example because the Ethernet link was down, or the optional silence timeout expired.

The complete bring-up procedure with expected outputs is kept in ``option_z/TEST_PLAN.md`` of the repository.
