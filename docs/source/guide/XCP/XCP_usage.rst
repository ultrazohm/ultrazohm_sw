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

Check the connection without CANape
-----------------------------------

``tools/xcp_test/xcp_poll.py`` is a small XCP master.
It needs Python 3.7 or newer and no additional packages.
Variable names are resolved from ``vitis/workspace/Baremetal/Debug/Baremetal.elf`` with the ``nm`` tool of Vitis 2022.2 in its default installation folder.
For another installation pass the tool with ``--nm``.
A variable can also be given by its address (``0x...``) instead of its name.

.. code-block:: bash

    # connect only: proves Ethernet, gateway, OCM exchange and engine
    python tools/xcp_test/xcp_poll.py --ip 192.168.1.233

    # read any R5 variable by name (type u8, i8, u16, i16, u32, i32, f32 or f64)
    python tools/xcp_test/xcp_poll.py --ip 192.168.1.233 --watch xcp_r5_cycle_count:u32

    # stream one variable with a real DAQ list, on raster 1 (daq_1ms)
    python tools/xcp_test/xcp_poll.py --ip 192.168.1.233 --daq --daq-event 1

    # throughput test: 2000 bytes per control cycle for 10 s, then the loss counters
    python tools/xcp_test/xcp_poll.py --ip 192.168.1.233 --stress

The default of 2000 bytes per cycle is meant for a control rate of 10 kHz.
At 40 kHz it would be 640 Mbit/s, so choose the load with ``--stress-bytes``, for example 1000 bytes for 320 Mbit/s.
The data rate that the stress test prints at the start also assumes 10 kHz.
The summary at the end shows the real one.

The stress test prints the data rate, the gaps in the transport counter and the change of the loss counters of :ref:`xcp_diagnostics` during the run.

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
     - 4 bytes (``SIZE_DWORD``), resolution 1 µs
   * - Events
     - 0 ``DAQ_R5``, 1 ``daq_1ms``, 2 ``daq_10ms``, 3 ``daq_100ms``, 4 ``daq_1s``
   * - Command timeout ``T1``
     - 5000 ms

Measure
-------

Assign every signal to the slowest raster that is sufficient.
A measurement on ``DAQ_R5`` produces one sample per control cycle; 2000 bytes per cycle at 10 kHz are already 160 Mbit/s.

In July 2026 an earlier version of this data path ran on hardware for one hour with 325 Mbit/s of measurement data (4000 bytes per cycle at 10 kHz).
The XCP session stayed alive, and the data of about 0.003 % of the control cycles was lost at the exchange between the processors.
The consumption handshake described in :ref:`xcp_architecture` was added afterwards to remove this loss.

In November 2026 the current version was measured at a control rate of 40 kHz:

- With DAQ messages of at most 248 bytes, nothing was lost up to about 160 Mbit/s. At 320 Mbit/s about a third of the control cycles were lost.
- With the current messages of up to 1024 bytes, 320 Mbit/s (1000 bytes per cycle) ran without any loss. With XCP commands sent back to back at the same time, 900 bytes per cycle ran for 10 minutes without loss; at 1000 bytes per cycle the R5 fell behind and about 15 % of the samples were lost.
- From 1100 bytes per cycle on, the R5 no longer kept up. ``xcp_r5_queue_lost`` counted lost samples, and the throughput fell to about 250 Mbit/s.
- A command took about 0.24 ms from the PC back to the PC without a measurement and about 0.6 ms at 1000 bytes per cycle.

At a high control rate the interrupt leaves little time for the main loop, and the main loop copies the measurement data into the OCM.
The limit is then the R5, not Ethernet and not the A53, which was idle more than 40 % of the time at the limit.
Overload does not degrade gracefully: once the R5 has fallen behind, it copies data that is no longer in its cache, which costs about twice as much, so the throughput sinks below the limit and stays there until the load drops.
At 40 kHz, keep the data on ``DAQ_R5`` at or below about 900 bytes per cycle and put everything else on a slower raster. 1000 bytes per cycle work, but leave no reserve for disturbances.
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
