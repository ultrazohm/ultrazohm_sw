.. _xcp_architecture:

================
XCP architecture
================

This page explains how XCP is implemented on the UltraZohm: which processor does what, how the two processors exchange data, and which guarantees the exchange gives.
Read :ref:`xcp_usage` first if you only want to measure.

Overview
--------

The XCP slave of the UltraZohm is split over both processors of the Zynq UltraScale+:

- The **R5** (bare metal, the control core) runs the XCP protocol engine. The engine is the open-source `XCPlite <https://github.com/vectorgrp/XCPlite>`_ from Vector (MIT license, upstream version 2.3.4). Because the engine runs on the R5, the XCP master addresses R5 memory directly: every variable of the R5 application with a fixed address, that is every global and every ``static`` variable, can be measured and calibrated by its address, without registering it anywhere in the code.
- The **A53** (FreeRTOS, lwIP) is a gateway. It moves XCP frames between a UDP socket and the on-chip memory (OCM) that both processors share. It does not interpret XCP commands and only knows the framing of XCP on Ethernet, that is the length and the counter in front of each message.
- The two processors exchange frames through three ring buffers in the OCM and one inter-processor interrupt (IPI) from the R5 to the A53.

.. mermaid::
    :align: center
    :caption: XCP data path of the UltraZohm

    flowchart TB
      pc["PC<br>XCP master: CANape or xcp_poll.py"]
      a53["A53, FreeRTOS<br>UDP gateway"]
      cmd["CMD ring in the OCM<br>commands, 4 KB"]
      r5["R5, bare metal<br>XCPlite engine"]
      rsp["RSP ring in the OCM<br>responses, 4 KB"]
      daq["DAQ ring in the OCM<br>measurement data, 112 KB"]
      pc <-- "UDP, port 5556" --> a53
      a53 -- "commands" --> cmd
      cmd --> r5
      r5 -- "responses" --> rsp
      r5 -- "measurement data" --> daq
      rsp --> a53
      daq --> a53
      r5 -. "IPI" .-> a53

The same Ethernet interface and the same IPI are used by the JavaScope.
JavaScope and XCP are therefore alternatives that are selected at compile time, see :ref:`xcp_usage_select`.

What runs where on the R5
-------------------------

The control interrupt writes the measurement data into the OCM itself.
The main loop only executes commands.

- **In** ``ISR_Control``, ``xcp_r5_event()`` triggers the measurement rasters of the cycle. The engine writes every DAQ message (DTO) straight into the DAQ ring in the OCM; there is no queue in between and no copy. At the end of the call, the DTOs of the cycle are cleaned from the data cache and published to the A53 together, with one write of the ring position. An IPI tells the A53 when 4 KB have been published since the last IPI or when the oldest of them is 1 ms old (``XCP_R5_DAQ_NOTIFY_BYTES`` and ``XCP_R5_DAQ_NOTIFY_US`` in ``xcptl_ocm.c``). At 300 Mbit/s that is about 8000 interrupts per second; with little data it is one per millisecond.
- **In the main loop**, ``xcp_r5_background()`` looks at the CMD ring on every pass. When nothing is new, this costs the read of one cache line. A new command is executed at once with ``XcpCommand()``. Its response is written into the RSP ring, published and signalled to the A53 with an IPI. A command runs only when the RSP ring has room for two responses of maximum size; otherwise it waits for the next pass.

Commands never run in the interrupt, and measurement data never waits for the main loop.

.. mermaid::
    :align: center
    :caption: Split of the XCP work between interrupt and main loop on the R5

    flowchart TB
      subgraph ISR["ISR_Control"]
        direction TB
        a["control algorithm"] --> b["xcp_r5_event()<br>every control cycle"]
        b --> c["the engine writes the DTOs<br>into the DAQ ring"]
        c --> d["clean the cache,<br>publish the write position"]
        d --> e["IPI when 4 KB or 1 ms<br>are waiting"]
      end
      subgraph ML["main loop"]
        direction TB
        f["xcp_r5_background()<br>on every pass"] --> g["new command<br>in the CMD ring?"]
        g --> h["XcpCommand()"]
        h --> i["response into the RSP ring,<br>publish, IPI"]
      end

The run time of ``xcp_r5_event()`` was measured on the test bench at a control rate of 40 kHz (November 2026, ODT entries of up to 240 bytes):

.. list-table::
   :header-rows: 1
   :widths: 60 40

   * - Part
     - Cost per control cycle
   * - first ODT of the cycle, with the time stamp, the publishing and the IPI decision
     - about 1.5 µs
   * - every further ODT
     - about 0.5 µs
   * - the measured bytes, written into the OCM and cleaned from the cache
     - about 2.2 µs per kilobyte

Every ODT (object descriptor table, one packet of a DAQ list) becomes one DAQ message.
An ODT holds at most ``MAX_DTO`` minus 8 bytes, that is 1016 bytes.
A raster without a running DAQ list costs only two checks, so the unused rasters are free.
At 938 bytes per cycle (300 Mbit/s at 40 kHz), ``xcp_r5_event()`` took 3.6 µs on average, and the control interrupt as a whole took 73 % of the time of the R5.

Compared with the former exchange, in which the main loop copied the data into the OCM, the interrupt takes 0.4 to 0.8 µs longer at up to 1 KB per cycle.
In return it varies much less (0.7 µs instead of up to 2.3 µs between the median and the 99.9th percentile), and at 300 Mbit/s the R5 has 13 percentage points more free time.

DAQ rasters
***********

The R5 offers five measurement rasters (XCP events).
A signal that only changes slowly should be measured on a slow raster, because the control-rate raster is what costs Ethernet bandwidth.

.. list-table::
   :header-rows: 1
   :widths: 10 20 70

   * - Event
     - Name
     - Rate
   * - 0
     - ``DAQ_R5``
     - every call of ``ISR_Control``
   * - 1
     - ``daq_1ms``
     - every *n* control cycles, nominally 1 ms
   * - 2
     - ``daq_10ms``
     - every 10 *n* control cycles
   * - 3
     - ``daq_100ms``
     - every 100 *n* control cycles
   * - 4
     - ``daq_1s``
     - every 1000 *n* control cycles

*n* is the control rate divided by 1 kHz, rounded down, and at least 1.
The slow rasters are therefore exact only if the control rate is a multiple of 1 kHz.
At 12.5 kHz, for example, ``daq_1ms`` fires every 12 control cycles, which is every 0.96 ms.
The time stamp of every sample is always the true one.
The slow rasters are offset against each other by one control cycle, so two of them never fire in the same cycle as long as *n* is at least 4, that is from a control rate of 4 kHz on.

.. _xcp_architecture_budget:

DAQ budget
**********

The XCP master decides how much is measured, and too much measurement data takes the time of the main loop.
On the test bench at 40 kHz, the main loop no longer got enough time from about 2800 bytes per cycle on.
At 3125 bytes the command to stop the measurement was never executed, and only reprogramming the board recovered it.
The R5 therefore checks a measurement before it starts it:

- When the master starts the selected DAQ lists (``START_STOP_SYNCH``), the engine adds up, for every raster, the bytes that one trigger produces with all DAQ lists that run or are about to start. Every DTO counts with its 4-byte transport header, its 4-byte ODT header, the 4-byte time stamp in the first ODT and the measured bytes, rounded up to a multiple of 4.
- The worst control cycle carries the lists of ``DAQ_R5`` and those of the largest slow raster, because two slow rasters never fire in the same cycle. Below 4 kHz, all slow rasters count.
- If the worst cycle exceeds the budget, the start is refused with ``ERR_DAQ_CONFIG``, which CANape reports as an invalid DAQ configuration. ``xcp_r5_daq_budget_refused`` counts refused starts, and ``xcp_r5_daq_cycle_bytes`` holds the worst cycle of the last start request, accepted or not.

The default budget is 50,000,000 bytes per second (400 Mbit/s), divided by the control rate:

.. list-table::
   :header-rows: 1
   :widths: 40 60

   * - Control rate
     - Budget per control cycle
   * - 40 kHz
     - 1250 bytes
   * - 20 kHz
     - 2500 bytes
   * - 10 kHz
     - 5000 bytes

At 40 kHz the full budget costs the interrupt about 5 µs per cycle, a fifth of the period, and the A53 carried up to 1350 bytes per cycle without loss.
Because the budget is a data rate, the share of the R5 spent on the measured bytes stays about the same at every control rate.
The budget per cycle is set at build time with ``XCP_R5_DAQ_BUDGET_BYTES`` (the rate with ``XCP_R5_DAQ_BUDGET_BYTES_PER_S``, both in ``xcptl_ocm.c``).
``xcp_r5_daq_budget_bytes`` is a global variable, so a master can also raise the budget at run time.

.. warning::
   A larger budget can starve the main loop of the R5. The measurement then can no longer be stopped over XCP, and only a reset of the board ends it. Raise the budget only deliberately and check ``xcp_r5_sweep_gap_max_us`` (see :ref:`xcp_diagnostics`).

The budget protects the R5.
It does not guarantee that the A53 keeps up with every configuration, see the next section.

The gateway on the A53
----------------------

The gateway consists of two tasks and a hook in the interrupt handler of the IPI.
Only the tasks use the UDP socket.

.. mermaid::
    :align: center
    :caption: Tasks, queues and interrupt hook of the gateway on the A53

    flowchart TB
      min["UDP datagram from the master"] --> rx["rx task<br>checks the framing, remembers the master"]
      rx -- "the datagram, at once" --> cmd["CMD ring"]
      rsp["RSP ring"] --> isr["hook in APU_IPI_ISR<br>runs once per IPI from the R5"]
      daq["DAQ ring"] --> isr
      isr -- "response queue,<br>has priority" --> tx["tx task<br>sends datagrams,<br>stamps the transport counter"]
      isr -- "DAQ queue,<br>65536 segments" --> tx
      tx --> mout["UDP datagram to the master"]

- The **rx task** receives the datagrams of the master. It forwards a datagram only if it consists of well-formed XCP frames, and it remembers the sender as the master. It writes the whole datagram into the CMD ring at once, where the R5 finds it at its next pass through the main loop. When a new master connects, the responses of the previous session that are still in the RSP ring are discarded first.
- The **hook in** ``APU_IPI_ISR`` runs once for every IPI of the R5. It moves the responses from the RSP ring into the response queue. Then it packs the DTOs of the DAQ ring into segments of up to 1400 bytes, always whole DTOs, and puts them into the DAQ queue. It takes at most 32 KB per interrupt; the rest follows with the next IPI, at the latest 1 ms later. At the end it writes its counters into the OCM.
- The **tx task** sends the queued responses and segments as UDP datagrams and stamps the XCP transport counter in every frame, in the order of transmission. Responses are sent before waiting measurement data. After every datagram it lets the other tasks of its priority run, among them the rx task and the network thread of lwIP. Otherwise a command that arrives during a burst of measurement data would wait until the whole burst is sent.

The DAQ queue is deep (65536 segments of up to 1400 bytes, about 92 MB) to bridge stalls of the network stack.

The A53 sends about 60,000 to 70,000 datagrams per second at most.
At 40 kHz that is one datagram per control cycle, but not two.
The DTOs of one control cycle should therefore fit into one datagram of 1400 bytes: on the test bench, 1350 bytes per cycle (432 Mbit/s) ran without loss, while at 1400 bytes per cycle every cycle needed two datagrams and the A53 dropped data in its DAQ queue (``xcp_gw_txq_dropped``).

The datagrams are kept at 1400 bytes, below the 1472 bytes that a 1500-byte MTU allows without IP fragmentation.
1472 bytes were measured: from 1464 bytes on, one ``lwip_sendto()`` took 13 µs instead of 5.9 µs, so full datagrams would cost the A53 twice as much time.
The cause was not found; see the comment at ``XCP_GW_BATCH_BUF_SIZE`` in ``xcp_gateway_a53.c``.

The OCM
-------

The OCM has 256 KB in four banks of 64 KB and is shared by the R5 and the A53:

.. list-table::
   :header-rows: 1
   :widths: 15 15 10 60

   * - Bank
     - Address
     - Size
     - Content
   * - 0
     - ``0xFFFC0000``
     - 64 KB
     - start-up handshakes: version of the A53 (offset ``0x00``), version of the R5 (``0x40``), logging path (``0x80``); the rest is free
   * - 1
     - ``0xFFFD0000``
     - 32 KB
     - user data from the R5 to the A53
   * -
     - ``0xFFFD8000``
     - 32 KB
     - user data from the A53 to the R5
   * - 2 and 3
     - ``0xFFFE0000``
     - 128 KB
     - logging path: the XCP rings below, or the JavaScope at ``0xFFFF0000``

The XCP rings use banks 2 and 3:

.. list-table::
   :header-rows: 1
   :widths: 22 15 13 50

   * - Region
     - Address
     - Size
     - Content
   * - DAQ ring
     - ``0xFFFE0000``
     - 112 KB
     - measurement data, from the control interrupt of the R5 to the A53
   * - A53 counters
     - ``0xFFFFC000``
     - 128 bytes
     - counters of the gateway from ``0xFFFFC008``, written by the A53, see :ref:`xcp_diagnostics`
   * - ring positions
     - ``0xFFFFC080``
     - 6 × 64 bytes
     - write and read position of each ring, each in a cache line of its own
   * - RSP ring
     - ``0xFFFFC200``
     - 4 KB
     - command responses, from the main loop of the R5 to the A53
   * - CMD ring
     - ``0xFFFFD200``
     - 4 KB
     - command datagrams, from the rx task of the A53 to the main loop of the R5

The map is defined in ``shared/APU_RPU_shared.h``, the XCP rings in ``shared/ocm_xcp_ring.h`` and the ring buffer itself in ``shared/uz_ocm_ring.h``.
Both applications include the same files.

.. warning::
   The OCM layout is the protocol between the two applications. After any change to these files, rebuild and flash **both** applications.

How the rings work
******************

Every ring has exactly one producer and one consumer, so nothing is locked and neither processor waits for the other one:

- A **record** is a 4-byte header with the length and the transport counter, followed by the message, padded to 4 bytes. DAQ and RSP records are XCP-on-Ethernet messages as they go on the wire. A CMD record is a whole received datagram. A record never wraps around the end of the ring.
- The **producer** writes its records, cleans them from its data cache and only then publishes the new write position. The **consumer** reads the write position, invalidates the new records in its cache, reads them and publishes its read position, which frees the space.
- Each position lies in a cache line of its own, and no processor ever writes a line that the other one writes. Cache maintenance is therefore enough to keep both views consistent; the OCM stays cacheable for both processors. On the R5 the cache is cleaned line by line without masking interrupts.
- A ring is **full** when the next record would reach the read position. A full DAQ ring refuses the DTO and counts it in ``xcp_r5_queue_lost``. The RSP ring cannot overflow, because a command runs only when its response fits. A full CMD ring drops the datagram and counts it in ``xcp_gw_cmd_dropped``; the master repeats the command after its timeout.
- At **start-up** each side sets its own position to the one of the other side, so the ring starts empty, whichever processor starts first. A position outside the ring, for example the content of the OCM after power-up, counts as 0.

Every record is written once and read once.
A command can neither get lost in the OCM nor be executed twice, a response is never overwritten, and half-written data is never visible, because the write position moves only after the records are complete in the OCM.
The former exchange through two fixed regions needed a seqlock, a response mailbox, command generations and an acknowledge for every chain of measurement data for these guarantees; the rings need none of them.

When the master stops the measurement or disconnects, the R5 signals the A53 and waits up to 20 ms until the DAQ ring is empty before it sends the response, so that the master receives the last samples before the response.

Command and response
********************

.. mermaid::
    :align: center
    :caption: Path of one XCP command and its response

    %%{init: {"sequence": {"mirrorActors": false, "messageMargin": 28, "actorMargin": 30, "noteMargin": 8, "boxMargin": 6, "height": 44}}}%%
    sequenceDiagram
      participant M as XCP master
      participant A as A53 gateway
      participant O as OCM
      participant R as R5 main loop
      M->>A: UDP datagram<br>with command
      Note over A: rx task checks the frames,<br>remembers the master address
      A->>O: datagram into the CMD ring,<br>publish the write position
      R->>O: next pass sees<br>the new write position
      Note over R: XcpCommand() executes
      R->>O: response into the RSP ring,<br>publish the write position
      R-->>A: IPI
      A->>O: hook takes the response,<br>publishes the read position
      A->>M: UDP datagram<br>with response

Measurement data
****************

.. mermaid::
    :align: center
    :caption: Path of measurement data through the DAQ ring

    %%{init: {"sequence": {"mirrorActors": false, "messageMargin": 28, "actorMargin": 30, "noteMargin": 8, "boxMargin": 6, "height": 44}}}%%
    sequenceDiagram
      participant I as R5 ISR_Control
      participant O as OCM
      participant A as A53 gateway
      I->>O: DTOs of the cycle<br>into the DAQ ring
      I->>O: clean the cache,<br>publish the write position
      I-->>A: IPI after 4 KB or 1 ms
      A->>O: hook packs the DTOs<br>into 1400-byte segments
      A->>O: publishes the read position,<br>the space is free again
      Note over A: tx task sends the segments<br>and stamps the transport counter
      Note over I,A: the R5 never waits: in a full ring<br>the DTO is dropped and counted

The A53 stamps the XCP transport counter when it sends a datagram.
Data that was lost before this point, in one of the buffers of the UltraZohm, is therefore **not** visible as a counter error in the master.
Such losses are counted instead, see :ref:`xcp_diagnostics`.

Memory access rules
-------------------

The XCP master sends plain addresses, so the R5 checks every access before it touches memory.

.. list-table::
   :header-rows: 1
   :widths: 44 28 28

   * - Memory
     - Read (measure, upload)
     - Write (calibrate, download)
   * - ``.data``, ``.sdata``, ``.sbss``, ``.bss``: all global and ``static`` variables
     - yes
     - yes, unless ``XCP_R5_READ_ONLY`` is set
   * - rest of the DDR memory of the R5 (``0x40000000`` to ``0x47FF0000``): code, constants, heap, stacks
     - yes
     - no
   * - TCM (``0x0`` and ``0x20000``, 64 KB each), contains the exception vectors
     - yes
     - no
   * - OCM (``0xFFFC0000`` to ``0xFFFFFFFF``)
     - yes
     - no
   * - everything else, for example A53 memory or the PL address space
     - no
     - no

A refused read is answered with ``ERR_ACCESS_DENIED``.
A refused write is answered with ``ERR_WRITE_PROTECTED`` if the address is readable and with ``ERR_ACCESS_DENIED`` if it is not.
Without the read check, a wrong address in the A2L file would raise a data abort on the control core.

Local variables of a function live on the stack or in a register and have no fixed address.
They can neither be measured nor calibrated by name.
Declare such a variable ``static`` to make it accessible.

.. note::
   The write check protects the application from stale addresses. It does not validate values: a calibration value is applied as it is sent. A value of 1, 2 or 4 bytes is written with a single store. A value of 8 bytes (``double``, ``int64_t``) is copied with the interrupts of the R5 masked (IRQ and FIQ), so the control interrupt never sees one half new and the other half old. Larger values (arrays, structures) are not written atomically with respect to the control interrupt.

Master supervision
------------------

UDP has no connection that could break.
The gateway therefore ends an XCP session itself when it concludes that the master is gone: it sends a regular XCP ``DISCONNECT`` to the R5 engine, which stops the measurement, and it forgets the address of the master.
The next ``CONNECT`` starts a new session.
The A53 prints ``APU: XCP session closed, ...`` on the serial console with the reason and the address of the master.

- Always active: 20 datagrams in a row could not be handed to the network, each after five retries. This is the case when the Ethernet link of the UltraZohm is down, and it takes one to two seconds. It does **not** detect a master that crashed or was unplugged behind a switch, because sending still succeeds then.
- Optional: the master did not send anything for ``XCP_GATEWAY_MASTER_TIMEOUT_MS`` (``xcp_gateway_a53.h``) while the gateway was sending. This covers the second case. It is switched off by default (value 0), because the XCP standard does not oblige a master to send anything during a measurement.

Neither of the two has been tested on hardware yet.

Files
-----

.. list-table::
   :header-rows: 1
   :widths: 45 55

   * - Path below ``vitis/software``
     - Content
   * - ``shared/uz_logging_path.h``
     - the switch between JavaScope and XCP
   * - ``shared/APU_RPU_shared.h``
     - map of the OCM
   * - ``shared/uz_ocm_ring.h``
     - ring buffer in the OCM, used by both processors
   * - ``shared/ocm_xcp_ring.h``
     - the three XCP rings and the addresses of the A53 counters
   * - ``Baremetal/src/sw/xcp_engine/xcplite.c`` and other upstream files
     - XCPlite engine, upstream files with a few marked ``UZ patch`` changes
   * - ``Baremetal/src/sw/xcp_engine/xcplib_r5_cfg.h``
     - all configuration of the engine for the R5
   * - ``Baremetal/src/sw/xcp_engine/xcptl_ocm.c``, ``xcp_r5.h``
     - transport layer on the rings, the functions called by ``main.c`` and ``isr.c``, memory access rules, DAQ budget, 8-byte writes
   * - ``FreeRTOS/sw/xcp_gateway/xcp_gateway_a53.c``
     - UDP gateway: two tasks and the hook in ``APU_IPI_ISR``

Changes to the upstream engine files are kept minimal, are marked with ``UZ patch`` in the source and are activated through ``xcplib_r5_cfg.h``, so that a newer XCPlite release can be taken over file by file.
Among them are the memory access checks, the DAQ budget and the 8-byte write.
