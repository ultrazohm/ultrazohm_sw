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
- The **A53** (FreeRTOS, lwIP) is a gateway. It moves XCP frames between a UDP socket and the shared on-chip memory (OCM). It does not interpret XCP commands and only knows the framing of XCP on Ethernet, that is the length and the counter in front of each message.
- The two processors exchange frames through two fixed regions of the OCM and one inter-processor interrupt (IPI).

.. mermaid::
    :align: center
    :caption: XCP data path of the UltraZohm

    flowchart TB
      pc["PC<br>XCP master: CANape or xcp_poll.py"]
      a53["A53, FreeRTOS<br>UDP gateway"]
      xin["XCP_IN in the OCM<br>0xFFFFC000, 1 KB"]
      r5["R5, bare metal<br>XCPlite engine"]
      xout["XCP_OUT in the OCM<br>0xFFFF4000, 32 KB"]
      pc <-- "UDP, port 5556" --> a53
      a53 -- "commands, acknowledges" --> xin
      xin --> r5
      r5 -- "responses, measurement data" --> xout
      xout --> a53
      r5 -. "IPI after every exchange" .-> a53

The same Ethernet interface and the same IPI are used by the JavaScope.
JavaScope and XCP are therefore alternatives that are selected at compile time, see :ref:`xcp_usage_select`.

What runs where on the R5
-------------------------

Only the sampling of measurement data runs inside the control interrupt.
Everything else runs in the main loop underneath it.
The main loop performs one exchange with the A53 at most every 100 µs.
This page calls one such exchange a sweep.

.. mermaid::
    :align: center
    :caption: Split of the XCP work between interrupt and main loop on the R5

    flowchart TB
      subgraph ISR["ISR_Control"]
        direction TB
        a["control algorithm"] --> b["xcp_r5_event()<br>every control cycle"]
        b --> c["copy the configured signals<br>into the DAQ queue"]
      end
      subgraph ML["main loop"]
        direction TB
        d["xcp_r5_background()<br>one sweep per 100 us"] --> e["read new commands from XCP_IN<br>and execute them"]
        e --> f["park the response in the mailbox"]
        f --> g["drain the DAQ queue into XCP_OUT"]
        g --> h["publish, trigger IPI to the A53"]
      end
      c -. "DAQ queue" .-> g

Command execution, cache maintenance and the copy into the OCM never run in the interrupt.

For comparison, the complete exchange inside the interrupt was measured with about 10 µs plus 10 µs per kilobyte, which is why it was moved to the main loop.

The run time of ``xcp_r5_event()`` was measured on the test bench at a control rate of 40 kHz:

.. list-table::
   :header-rows: 1
   :widths: 60 40

   * - Part
     - Cost per control cycle
   * - first active ODT of the event, including the time stamp
     - about 1 µs
   * - every further ODT
     - 0.6 to 0.8 µs
   * - the measured bytes themselves
     - about 2 µs per kilobyte

Every ODT (object descriptor table, one packet of a DAQ list) becomes one DAQ message, so the cost depends on the number of ODTs much more than on the amount of data.
An ODT holds at most ``MAX_DTO`` minus 8 bytes.
Since ``MAX_DTO`` was raised from 248 to 1024 bytes, 1000 bytes per cycle fit into one ODT instead of five.
The interrupt then took 17.3 µs on average and at most 20.1 µs.
The same data in six ODTs took 18.9 µs on average, and that run already lost samples, so the full cost is higher.

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
The slow rasters are offset against each other by one control cycle.

The gateway on the A53
----------------------

The gateway consists of two tasks and a hook in the interrupt handler of the IPI.
Only the hook touches the OCM, and only the tasks use the UDP socket.
Three queues connect them.

.. mermaid::
    :align: center
    :caption: Tasks, queues and interrupt hook of the gateway on the A53

    flowchart TB
      min["UDP datagram from the master"] --> rx["rx task<br>checks the framing, remembers the master"]
      rx -- "command queue" --> isr["hook in APU_IPI_ISR<br>runs once per IPI from the R5"]
      xout["XCP_OUT"] -- "header under the seqlock,<br>chain checked by its number" --> isr
      isr -- "commands, acknowledges" --> xin["XCP_IN"]
      isr -- "response queue,<br>has priority" --> tx["tx task<br>packs datagrams, stamps the transport counter"]
      isr -- "DAQ queue,<br>65536 records" --> tx
      tx --> mout["UDP datagram to the master"]

- The **rx task** receives the datagrams of the master. It forwards a datagram only if it consists of well-formed XCP frames, and it remembers the sender as the master.
- The **hook in** ``APU_IPI_ISR`` runs once for every IPI of the R5, that is once per sweep. It reads ``XCP_OUT``, puts responses and measurement data into two separate queues and writes the next commands and its acknowledges into ``XCP_IN``.
- The **tx task** packs queued frames into datagrams of up to 1400 bytes, stamps the XCP transport counter and sends them. Responses are sent before waiting measurement data.

The DAQ queue is deep (65536 records of up to 1400 bytes, about 92 MB) to bridge stalls of the network stack.

The OCM exchange
----------------

The exchange uses the part of OCM bank 3 that the JavaScope never touches.

.. list-table::
   :header-rows: 1
   :widths: 15 15 10 60

   * - Region
     - Address
     - Size
     - Content
   * - ``XCP_OUT``
     - ``0xFFFF4000``
     - 32 KB
     - R5 to A53: header, response mailbox, chain of DAQ frames
   * - ``XCP_IN``
     - ``0xFFFFC000``
     - 1 KB
     - A53 to R5: header with acknowledges and the gateway counters, chain of command frames

The layout is defined once, in ``ocm_xcp_fifo.c``.
The file exists as two identical copies, one compiled for each processor (``Baremetal/src/sw/xcp_engine`` and ``FreeRTOS/sw/xcp_gateway``).

.. warning::
   The OCM layout is the protocol between the two applications. After any change to ``ocm_xcp_fifo.c`` or ``ocm_xcp_fifo.h``, keep both copies identical and rebuild and flash **both** applications.

Neither processor waits for the other one.
Five mechanisms keep the exchange consistent when the A53 handles the interrupt late, which happens regularly under network load.
A late interrupt cannot lose a command or a response.
Measurement data is delayed by it and is only lost when a buffer overflows or the A53 does not answer for 5 ms.
Every such loss is counted, see :ref:`xcp_diagnostics`.

.. list-table::
   :header-rows: 1
   :widths: 25 20 55

   * - Mechanism
     - Protects
     - How
   * - Seqlock on the header of ``XCP_OUT``
     - command responses and acknowledges
     - The R5 sets a sequence word to an odd value before it changes the region and to an even value afterwards. The A53 discards its copy of the header and the response mailbox if the word was odd or changed during the copy, and takes it again with the next interrupt.
   * - Response mailbox with acknowledge
     - command responses
     - A response stays in its own slot until the A53 confirms its sequence number. A lost response would end the XCP session with a timeout.
   * - Generation handshake on ``XCP_IN``
     - commands
     - The A53 rewrites the same batch of commands on every interrupt until the R5 confirms the generation number. The R5 executes each generation exactly once.
   * - Consumption handshake on the DAQ chain
     - measurement data
     - The R5 leaves a chain of DAQ frames in place until the A53 confirms it, for at most 50 sweeps (5 ms). In the meantime new samples wait in the 32 KB queue of the R5.
   * - Chain number
     - measurement data
     - The R5 sets the number of the chain to 0 before it rewrites the chain and publishes the new number only when the chain is complete in the OCM. The A53 accepts a chain only if it saw the same non-zero number before and after reading it. A sweep that only keeps the chain does not change the number, so a long read of a kept chain stays valid. Half-written data never reaches the network.

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
      participant R as R5 engine
      M->>A: UDP datagram<br>with command
      Note over A: rx task checks the frame,<br>remembers the master address
      A->>O: IPI ISR writes batch<br>to XCP_IN, generation n
      R->>O: sweep reads<br>generation n
      Note over R: XcpCommand() executes
      R->>O: response into mailbox,<br>sequence s, consumed n
      R-->>A: IPI
      A->>O: IPI ISR reads mailbox,<br>acknowledges sequence s
      A->>M: UDP datagram<br>with response
      Note over A,R: until the acknowledges arrive,<br>both sides keep offering the same bytes

Measurement data
****************

.. mermaid::
    :align: center
    :caption: Path of measurement data with the consumption handshake

    %%{init: {"sequence": {"mirrorActors": false, "messageMargin": 28, "actorMargin": 30, "noteMargin": 8, "boxMargin": 6, "height": 44}}}%%
    sequenceDiagram
      participant I as R5 ISR_Control
      participant R as R5 main loop
      participant O as OCM
      participant A as A53 gateway
      I->>R: samples into<br>the DAQ queue
      R->>O: sweep k writes chain c<br>to XCP_OUT
      R-->>A: IPI
      A->>O: IPI ISR reads chain c,<br>checks that the number is still c
      A->>O: acknowledges c<br>in XCP_IN
      Note over A: tx task packs the frames<br>into datagrams and stamps<br>the transport counter
      R->>O: sweep k+1 sees the acknowledge,<br>writes chain c+1
      Note over R,A: no acknowledge yet, for example a late IPI:<br>the R5 keeps chain c and tries again one sweep later

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
   The write check protects the application from stale addresses. It does not validate values: a calibration value is applied as it is sent. A value of 1, 2 or 4 bytes is written with a single access. Larger values (``double``, arrays, structures) are not written atomically with respect to the control interrupt.

Master supervision
------------------

UDP has no connection that could break.
The gateway therefore ends an XCP session itself when it concludes that the master is gone: it sends a regular XCP ``DISCONNECT`` to the R5 engine, which stops the measurement, and it forgets the address of the master.
The next ``CONNECT`` starts a new session.

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
   * - ``Baremetal/src/sw/xcp_engine/xcplite.c`` and other upstream files
     - XCPlite engine, upstream files with a few marked ``UZ patch`` changes
   * - ``Baremetal/src/sw/xcp_engine/xcplib_r5_cfg.h``
     - all configuration of the engine for the R5
   * - ``Baremetal/src/sw/xcp_engine/xcptl_ocm.c``, ``xcp_r5.h``
     - transport layer over the OCM, the functions called by ``main.c`` and ``isr.c``, memory access rules
   * - ``Baremetal/src/sw/xcp_engine/ocm_xcp_fifo.c``
     - OCM exchange, R5 copy
   * - ``FreeRTOS/sw/xcp_gateway/ocm_xcp_fifo.c``
     - OCM exchange, identical A53 copy
   * - ``FreeRTOS/sw/xcp_gateway/xcp_gateway_a53.c``
     - UDP gateway: two tasks and the hook in ``APU_IPI_ISR``

Changes to the upstream engine files are kept minimal, are marked with ``UZ patch`` in the source and are activated through ``xcplib_r5_cfg.h``, so that a newer XCPlite release can be taken over file by file.
