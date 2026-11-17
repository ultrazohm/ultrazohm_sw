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
- The **A53** (FreeRTOS, lwIP) is a gateway without XCP knowledge. It moves XCP frames between a UDP socket and the shared on-chip memory (OCM).
- The two processors exchange frames through two fixed regions of the OCM and one inter-processor interrupt (IPI).

.. mermaid::
    :align: center
    :caption: XCP data path of the UltraZohm

    flowchart LR
      subgraph PC["PC"]
        master["XCP master<br>CANape / xcp_poll.py"]
      end
      subgraph A53["A53: FreeRTOS"]
        rx["rx task<br>UDP receive"]
        tx["tx task<br>UDP send, CTR stamp"]
        ipi["APU_IPI_ISR<br>OCM to queues"]
        rx -- "command queue" --> ipi
        ipi -- "DAQ queue<br>response queue" --> tx
      end
      subgraph OCM["OCM bank 3"]
        xin["XCP_IN<br>0xFFFFC000, 1 KB"]
        xout["XCP_OUT<br>0xFFFF4000, 32 KB"]
      end
      subgraph R5["R5: bare metal"]
        sweep["main loop<br>xcp_r5_background()"]
        isr["ISR_Control<br>xcp_r5_event()"]
        q["DAQ queue<br>32 KB"]
        vars[("R5 variables<br>Global_Data ...")]
        isr -- "sample" --> q
        q --> sweep
        vars -. "read" .-> isr
        sweep -. "read / write" .-> vars
      end
      master -- "UDP port 5556" --> rx
      tx -- "UDP" --> master
      ipi --> xin
      xin --> sweep
      sweep --> xout
      xout --> ipi
      sweep -. "IPI" .-> ipi

The same Ethernet interface and the same IPI are used by the JavaScope.
JavaScope and XCP are therefore alternatives that are selected at compile time, see :ref:`xcp_usage_select`.

What runs where on the R5
-------------------------

Only the sampling of measurement data runs inside the control interrupt.
Everything else runs in the main loop underneath it.

.. mermaid::
    :align: center
    :caption: Split of the XCP work between interrupt and main loop on the R5

    flowchart TD
      subgraph ISR["ISR_Control, every control cycle"]
        a["control algorithm"] --> b["xcp_r5_event()"]
        b --> c["copy the configured signals<br>into the DAQ queue"]
      end
      subgraph ML["main loop, one sweep every 100 us"]
        d["xcp_r5_background()"] --> e["read new commands from XCP_IN<br>and execute them"]
        e --> f["park the response in the mailbox"]
        f --> g["drain the DAQ queue into XCP_OUT"]
        g --> h["publish, trigger IPI to the A53"]
      end
      c -. "DAQ queue" .-> g

``xcp_r5_event()`` costs well below one microsecond while no measurement is running and roughly 5 µs per kilobyte of measured data per cycle.
Command execution, cache maintenance and the copy into the OCM never run in the interrupt.

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
     - derived from the control rate, about every 1 ms
   * - 2
     - ``daq_10ms``
     - about every 10 ms
   * - 3
     - ``daq_100ms``
     - about every 100 ms
   * - 4
     - ``daq_1s``
     - about every second

The slow rasters are counted down from the control rate.
If the control rate is not a multiple of 1 kHz they drift slightly; the time stamp of every sample is always the true one.

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
Four mechanisms make sure that nothing is lost or corrupted when the A53 handles the interrupt late, which happens regularly under network load.

.. list-table::
   :header-rows: 1
   :widths: 25 20 55

   * - Mechanism
     - Protects
     - How
   * - Seqlock on ``XCP_OUT``
     - everything the A53 reads
     - The R5 sets a sequence word to an odd value before it changes the region and to an even value afterwards. The A53 discards a read if the word was odd or changed during the read. Half-written data never reaches the network.
   * - Response mailbox with acknowledge
     - command responses
     - A response stays in its own slot until the A53 confirms its sequence number. A lost response would end the XCP session with a timeout.
   * - Generation handshake on ``XCP_IN``
     - commands
     - The A53 rewrites the same batch of commands on every interrupt until the R5 confirms the generation number. The R5 executes each generation exactly once.
   * - Consumption handshake on the DAQ chain
     - measurement data
     - The R5 leaves a chain of DAQ frames in place until the A53 confirms it. In the meantime new samples wait in the 32 KB queue of the R5.

Command and response
********************

.. mermaid::
    :align: center
    :caption: Path of one XCP command and its response

    sequenceDiagram
      participant M as XCP master
      participant A as A53 gateway
      participant O as OCM
      participant R as R5 engine
      M->>A: UDP datagram with command
      Note over A: rx task checks the frame,<br>remembers the master address
      A->>O: IPI ISR writes batch to XCP_IN,<br>generation n
      R->>O: sweep reads generation n
      Note over R: XcpCommand() executes
      R->>O: response into mailbox, sequence s,<br>consumed generation n
      R-->>A: IPI
      A->>O: IPI ISR reads mailbox,<br>acknowledges sequence s
      A->>M: UDP datagram with response
      Note over A,R: until the acknowledges arrive, both sides<br>keep offering the same bytes

Measurement data
****************

.. mermaid::
    :align: center
    :caption: Path of measurement data with the consumption handshake

    sequenceDiagram
      participant I as R5 ISR_Control
      participant R as R5 main loop
      participant O as XCP_OUT
      participant A as A53 IPI ISR
      participant T as A53 tx task
      I->>R: samples into DAQ queue
      R->>O: sweep k writes chain, chain_seq c
      R-->>A: IPI
      A->>O: read chain c under the seqlock
      A->>T: frames into DAQ queue
      A->>O: acknowledge c in XCP_IN
      T->>T: pack frames into datagrams,<br>stamp the transport counter
      R->>O: sweep k+1 sees the acknowledge,<br>writes the next chain
      Note over R,A: no acknowledge yet, for example a late IPI:<br>the R5 keeps chain c and tries again one sweep later

The A53 stamps the XCP transport counter when it sends a datagram.
The counter on the wire is therefore always gapless, and data that is lost inside the UltraZohm is **not** visible as a counter error in the master.
Such losses are counted instead, see :ref:`xcp_diagnostics`.

On the A53 the response frames use their own queue and overtake waiting measurement data.
The DAQ queue of the A53 is deep (262144 frames) to bridge stalls of the network stack.

Memory access rules
-------------------

The XCP master sends plain addresses, so the R5 checks every access before it touches memory.

.. list-table::
   :header-rows: 1
   :widths: 30 35 35

   * - Memory
     - Read (measure, upload)
     - Write (calibrate, download)
   * - ``.data``, ``.sdata``, ``.sbss``, ``.bss`` (global and ``static`` variables)
     - yes
     - yes, unless ``XCP_R5_READ_ONLY`` is set
   * - code and constants in DDR, heap, stacks
     - yes
     - no
   * - TCM (exception vectors)
     - yes
     - no
   * - OCM
     - yes
     - no
   * - everything else, for example A53 memory or the PL address space
     - no
     - no

A refused read is answered with ``ERR_ACCESS_DENIED``, a refused write with ``ERR_WRITE_PROTECTED``.
Without the read check, a wrong address in the A2L file would raise a data abort on the control core.

Local variables of a function live on the stack or in a register and have no fixed address.
They can neither be measured nor calibrated by name.
Declare such a variable ``static`` to make it accessible.

.. note::
   The write check protects the application from stale addresses. It does not validate values: a calibration value is applied as it is sent, and a value wider than one machine word is not written atomically with respect to the control interrupt.

Master supervision
------------------

UDP has no connection that could break.
The gateway therefore ends an XCP session itself when the master is no longer reachable: it sends a regular XCP ``DISCONNECT`` to the R5 engine, which stops the measurement, and it forgets the address of the master.
The next ``CONNECT`` starts a new session.

- Always active: 20 datagrams in a row could not be sent, for example because the cable was unplugged. This takes about one second.
- Optional: the master did not send anything for ``XCP_GATEWAY_MASTER_TIMEOUT_MS`` while measurement data was flowing. This is switched off by default, because the XCP standard does not oblige a master to send anything during a measurement.

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

Changes to the upstream engine files are kept minimal, are switched on only through ``xcplib_r5_cfg.h`` and are marked with ``UZ patch`` in the source, so that a newer XCPlite release can be taken over file by file.
