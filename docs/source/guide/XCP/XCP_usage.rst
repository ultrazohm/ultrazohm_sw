.. _xcp_usage:

=========
Using XCP
=========

This page shows how to switch the UltraZohm from the JavaScope to XCP, how to check the connection without CANape, and how to get an A2L file.
The implementation is explained in :ref:`xcp_architecture`.

.. _xcp_usage_select:

Select JavaScope or XCP
-----------------------

The :ref:`JavaScope <JavaScope>` and XCP use the same Ethernet interface and the same interrupt between the processors.
One of them is selected at compile time, for both processors at once, in ``vitis/software/shared/uz_logging_path.h``:

.. code-block:: c

    /* <<< select the logging path here >>> */
    #define UZ_LOGGING_PATH UZ_LOGGING_PATH_XCP        // or UZ_LOGGING_PATH_JAVASCOPE

.. mermaid::
    :align: center
    :caption: What the switch selects on each processor

    flowchart TB
      sw["UZ_LOGGING_PATH<br>shared/uz_logging_path.h"]
      sw -- "UZ_LOGGING_PATH_JAVASCOPE" --> js
      sw -- "UZ_LOGGING_PATH_XCP" --> xcp
      subgraph js["JavaScope"]
        direction TB
        js1["R5: JavaScope_update() in ISR_Control"]
        js2["A53: JavaScope TCP server"]
        js3["PC: JavaScope GUI"]
        js1 --> js2 --> js3
      end
      subgraph xcp["XCP"]
        direction TB
        x1["R5: XCPlite engine"]
        x2["A53: UDP gateway, port 5556"]
        x3["PC: CANape or xcp_poll.py"]
        x1 --> x2 --> x3
      end

After changing the switch, **build and flash both applications** (Baremetal and FreeRTOS).
The R5 publishes its setting at start-up and the A53 compares it with its own.
If the two applications on the board were built with different settings, the A53 prints a warning on the serial console when the network is up:

.. code-block:: text

    APU: Warning: logging path mismatch - APU built for XCP, RPU built for JavaScope.
    APU:          Rebuild and flash BOTH applications (shared/uz_logging_path.h).

The check compares only this setting.
It does not notice that the two applications were built from different versions of the source code.

Everything else on this page assumes ``UZ_LOGGING_PATH_XCP``.

Find the IP address
-------------------

The A53 prints the XCP endpoint on the serial console when the network is up (115200 baud, see :doc:`/guide/how_to_guides/vitis/connect_terminal`):

.. code-block:: text

    APU: XCPlite slave (UDP) at 192.168.1.233:5556
    APU:   test with  python tools/xcp_test/xcp_poll.py --ip 192.168.1.233

It also prints a line for every ``CONNECT`` and ``DISCONNECT`` it receives, with the address and port of the master:

.. code-block:: text

    APU: XCP CONNECT from 192.168.1.10:54321
    APU: XCP DISCONNECT from 192.168.1.10:54321

The line shows that the command reached the board, not that the R5 accepted it; the master reports that.
If the gateway closes a session itself because the master can no longer be reached (master supervision, see :doc:`XCP_architecture`), it prints ``APU: XCP session closed, ...`` with the reason and the address.

Check the connection without CANape
-----------------------------------

``tools/xcp_test/xcp_poll.py`` is a small XCP master.
It needs Python 3.7 or newer and no additional packages.
Variable names are resolved from ``vitis/workspace/Baremetal/Debug/Baremetal.elf`` with the ``nm`` tool of Vitis 2022.2 in its default installation folder.
For another installation pass the tool with ``--nm``.
A variable can also be given by its address (``0x...``) instead of its name.

.. code-block:: bash

    # connect only: proves Ethernet, gateway, OCM rings and engine
    python tools/xcp_test/xcp_poll.py --ip 192.168.1.233

    # read any R5 variable by name (type u8, i8, u16, i16, u32, i32, f32 or f64)
    python tools/xcp_test/xcp_poll.py --ip 192.168.1.233 --watch xcp_r5_cycle_count:u32

    # stream one variable with a real DAQ list, on raster 1 (daq_1ms)
    python tools/xcp_test/xcp_poll.py --ip 192.168.1.233 --daq --daq-event 1

    # throughput test: 2000 bytes per control cycle for 10 s, then the loss counters
    python tools/xcp_test/xcp_poll.py --ip 192.168.1.233 --stress

The default of 2000 bytes per cycle is meant for a control rate of 10 kHz.
At 40 kHz it exceeds the DAQ budget of the R5 (1250 bytes per cycle, see :ref:`xcp_architecture_budget`) and the start is refused, so choose the load with ``--stress-bytes``, for example 938 bytes for 300 Mbit/s.
The stress test prints at the start how many bytes per cycle the budget counts for the chosen load.
The data rate it prints at the start assumes 10 kHz; the summary at the end shows the real one.

The stress test prints the data rate, the gaps in the transport counter and the change of the counters of :ref:`xcp_diagnostics` during the run.
Its exit code tells the result:

.. list-table::
   :header-rows: 1
   :widths: 10 90

   * - Code
     - Result
   * - 0
     - passed: every transport counter value arrived once, and no buffer of the UltraZohm dropped data
   * - 1
     - no measurement data received
   * - 2
     - gaps or duplicates in the transport counter
   * - 3
     - data dropped inside the UltraZohm before the transport counter was stamped (``xcp_r5_queue_lost`` or ``xcp_gw_txq_dropped`` increased); the master cannot see such a loss as a counter gap
   * - 4
     - these loss counters could not be read, so a hidden loss is unknown; typically the main loop of the R5 had no time to execute commands
   * - 5
     - the start was refused by the DAQ budget of the R5

A2L file
--------

The XCP master needs an A2L file that describes the variables and their addresses.
Addresses change with every build of the Baremetal application.

The repository contains a CANape project in ``CANape/UZ_XCP`` with the database ``uz.A2L``.
When the project is loaded, CANape reads ``Baremetal.elf`` from the Vitis workspace if the file has changed and updates the addresses in ``uz.A2L``.
The addresses therefore do not have to be maintained by hand.
Creating such a project from scratch is described in :doc:`CANape`.

Two points are specific to the UltraZohm:

Complete structures
    CANape cannot import the types of ``Global_Data`` on its own, because they contain unions with anonymous members and pointers.
    ``uz.A2L`` therefore already contains structure descriptions for ``Global_Data`` and its members ``rasv``, ``av`` and ``aa``, which can be added to a measurement window as a whole.

    CANape updates the addresses of these descriptions, but not their layout.
    The members and their offsets are those of the build the description was generated from.
    After changing one of these structures, and for every other structure, generate the description from the ELF file and paste it into the A2L file:

    .. code-block:: bash

        python tools/xcp_test/dwarf_structs.py --elf vitis/workspace/Baremetal/Debug/Baremetal.elf Global_Data.av

    The script uses ``objdump`` of Vitis 2022.2 in its default installation folder (``--objdump`` for another path).

Without CANape
    ``tools/xcp_test/gen_a2l.py`` writes a complete stand-alone A2L file for other XCP masters, by default to ``tools/xcp_test/UltraZohm_XCP.a2l``:

    .. code-block:: bash

        python tools/xcp_test/gen_a2l.py --ip 192.168.1.233 --diag --struct Global_Data.av \
               --symbols xcp_r5_cycle_count:u32

    The addresses in this file are those of the ELF file it was generated from.
    Generate it again after every build.

Settings that an A2L file for the UltraZohm must contain:

.. list-table::
   :header-rows: 1
   :widths: 40 60

   * - Setting
     - Value
   * - Transport
     - XCP on UDP, port 5556
   * - ``MAX_CTO`` / ``MAX_DTO``
     - 248 / 1024
   * - Byte order
     - little endian (``MSB_LAST``)
   * - Largest ODT entry
     - 240 bytes
   * - Identification field
     - ``RELATIVE_WORD_ALIGNED``
   * - Time stamp
     - 4 bytes (``SIZE_DWORD``), resolution 10 ns (``0x0A UNIT_1NS``), wraps every 42.9 s
   * - Events
     - 0 ``DAQ_R5``, 1 ``daq_1ms``, 2 ``daq_10ms``, 3 ``daq_100ms``, 4 ``daq_1s``
   * - Command timeout ``T1``
     - 5000 ms

Measure
-------

Assign every signal to the slowest raster that is sufficient.
A measurement on ``DAQ_R5`` produces one sample per control cycle; 2000 bytes per cycle at 10 kHz are already 160 Mbit/s.

Every sample carries the start of its control interrupt, read from the 100 MHz system timer of ``uz_SystemTime``.
Consecutive samples on ``DAQ_R5`` are therefore one control period apart, give or take the interrupt latency.
CANape converts the time of the UltraZohm to the clock of the PC, so the times in a recording also contain the drift between the two clocks (about 17 ppm on the test bench).

In November 2026 the current version, with the ring buffers in the OCM, was measured on the test bench:

- 300 Mbit/s ran without any loss, both at 40 kHz (938 bytes per cycle) and at 10 kHz (3750 bytes per cycle). At 40 kHz the control interrupt took 73 % of the time of the R5, and the A53 was idle 40 % of the time.
- At 40 kHz, 1350 bytes per cycle (432 Mbit/s) ran without loss. From 1400 bytes per cycle on, the DTOs of one cycle no longer fit into one datagram, and the A53 dropped data in its DAQ queue, because it sends at most 60,000 to 70,000 datagrams per second.
- From about 2800 bytes per cycle at 40 kHz, the main loop of the R5 no longer got enough time to execute commands. The DAQ budget now refuses such a measurement before it starts.
- A command took about 0.22 to 0.26 ms from the PC back to the PC in the median, with and without a running measurement.

At 40 kHz, keep the data on ``DAQ_R5`` so small that the DTOs of one cycle fit into one datagram of 1400 bytes, which is about 1350 bytes in one DAQ list, and put everything else on a slower raster.
The DAQ budget of 1250 bytes per cycle stays below this.
Each ODT also costs time in the interrupt, see :ref:`xcp_architecture`.

Calibrate
---------

A variable is calibrated by writing to its address while the application runs.
Writes are accepted for every variable with static storage duration: global variables, ``static`` variables of a file and ``static`` variables inside a function.
This includes the instances of the ``uz_`` software modules, which are stored in ``static`` arrays (usually named ``instances``).
Local variables of a function and constants (``const``) cannot be written, see the memory access rules in :ref:`xcp_architecture`.

Many modules use the same name for their ``static`` variables.
``xcp_poll.py`` and ``gen_a2l.py`` look a variable up by its name only and cannot tell such variables apart.
Use the address for them.

.. warning::
   A calibration write changes a variable of the running control application immediately. The value is not checked. Only calibrate variables whose effect on your test bench you understand.

Values of 1, 2, 4 and 8 bytes are written in one piece, so the control interrupt never sees half of a new value.
Larger blocks, for example arrays, are not, and a set of several variables that are written with separate commands changes one variable after the other.

A calibrated value is kept until the next reset.
It is not stored permanently.

To build a firmware that can only be measured, set ``XCP_R5_READ_ONLY`` to ``1`` in ``vitis/software/Baremetal/src/sw/xcp_engine/xcp_r5.h``.
Every write is then answered with ``ERR_WRITE_PROTECTED``.

Limits
------

- One XCP master at a time. The gateway serves the endpoint that sent the last valid datagram.
- No authentication. Use XCP in an isolated lab network only.
- XCP and JavaScope cannot run at the same time.
- Both applications must always be built from the same state of the repository and flashed together.
- Only memory of the R5 can be accessed. Variables of the A53 application and registers in the PL are not reachable.
- The measurement configuration is limited by the DAQ tables of the R5 (6 KB, about 1000 signals in total). A larger configuration is refused with ``ERR_MEMORY_OVERFLOW``. The size is set with ``OPTION_DAQ_MEM_SIZE`` in ``xcplib_r5_cfg.h``.
- The amount of measurement data per control cycle is limited by the DAQ budget (1250 bytes at 40 kHz, 5000 bytes at 10 kHz). A larger measurement is refused with ``ERR_DAQ_CONFIG``, see :ref:`xcp_architecture_budget`.
