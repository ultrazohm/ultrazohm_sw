.. _dslot_i2c_runtime:

===========================================
Runtime-configurable D-Slot CPLD over I2C
===========================================

Overview
========

The ``i2c_only`` implementation provides a runtime-configurable signal router
for the MachXO2 D-Slot CPLDs used on carrier board Rev05 and Rev06.
The same VHDL design is used for all five physical D-Slots.  Only the I2C
address is changed during synthesis.

The design provides:

* independent direction selection for all 30 digital channels,
* transparent FPGA-to-D-Slot and D-Slot-to-FPGA forwarding,
* heartbeat-based safe-state gating,
* an I2C register interface with auto-increment,
* shadow registers and atomic commits,
* sequence-number protection against duplicate or incomplete commands,
* a protected configuration unlock sequence,
* a timeout for abandoned configuration attempts,
* readback of FPGA-side and D-Slot-side pin levels,
* a protected TX test mode for LED and wiring tests, and
* automated generation of five address-specific ``.bit`` and ``.jed`` files.

.. warning::

   The TX test mode is intended for commissioning and debugging.
   It replaces FPGA output values with an I2C-controlled pattern, but it does
   not bypass the heartbeat or safe-state logic.  A requested safe state still
   forces TX channels low.

Source structure
================

The implementation is composed of the following files in the
``cpld_lattice`` repository:

.. list-table::
   :header-rows: 1
   :widths: 34 66

   * - File
     - Function
   * - ``i2c_only/source/i2ctesting.vhdl``
     - Top level, register bank, direction routing, safety gating and TX test
       mode.
   * - ``i2c/source/efb_dslot.vhd``
     - Wrapper around the MachXO2 Embedded Function Block (EFB), including
       the primary I2C slave, Wishbone interface and bidirectional I2C pads.
   * - ``xo2_libraries/sio_fsm4i2c.vhd``
     - Transport state machine between the EFB Wishbone registers and the
       byte-oriented SIO interface used by the top level.
   * - ``xo2_libraries/lib_sXc.vhd``
     - Common clock/reset and D-Slot heartbeat receiver.
   * - ``tools/diamond/build_i2c_dslot_images.tcl``
     - Diamond build matrix that creates the five address-specific
       implementations.
   * - ``tools/diamond/build_i2c_dslot_images.ps1``
     - Windows wrapper that locates Diamond and starts the Tcl build.
   * - ``tools/petalinux/dslot_i2c_debug.sh``
     - Single-CPLD status and LED test.
   * - ``tools/petalinux/dslot_dual_i2c_debug.sh``
     - Coordinated test for two CPLDs.

Architecture
============

The data path has three layers:

.. mermaid::
   :align: center
   :caption: I2C-controlled D-Slot CPLD architecture

   flowchart LR
      Linux[PetaLinux i2ctransfer] -->|I2C| EFB[MachXO2 EFB I2C slave]
      EFB <-->|8-bit Wishbone| FSM[sio_fsm4i2c]
      FSM <-->|SIO byte stream| REG[Register bank and safety protocol]
      REG --> DIR[30-bit direction and TX test control]
      FPGA[FPGA pins 0..29] <--> DIR
      DIR <--> DSLOT[D-Slot pins 0..29]
      HB[S3C heartbeat] --> SAFE[Heartbeat receiver]
      SAFE --> DIR

The EFB performs the electrical I2C slave protocol.  ``sio_fsm4i2c`` converts
EFB FIFO events into byte strobes.  The top level interprets the first byte as
a register address and processes all following bytes as register data.

Top-level generics
==================

.. list-table::
   :header-rows: 1
   :widths: 30 20 50

   * - Generic
     - Default
     - Description
   * - ``G_SLOT_INDEX``
     - ``0``
     - Selects physical D-Slot D1 through D5 and its corresponding EFB I2C
       address.
   * - ``G_DEVICE_ID``
     - ``0x31``
     - Device identifier returned in register ``0x00``.
   * - ``G_COMMIT_MAGIC``
     - ``0xA5``
     - Value required to commit a direction update.
   * - ``G_UNLOCK_MAGIC_1``
     - ``0xC3``
     - First protected-access key.
   * - ``G_UNLOCK_MAGIC_2``
     - ``0x5A``
     - Second protected-access key.
   * - ``G_TEST_ENABLE_MAGIC``
     - ``0xA6``
     - Enables and commits a complete TX test pattern.
   * - ``G_TEST_DISABLE_MAGIC``
     - ``0x59``
     - Disables TX test mode.
   * - ``G_REQUIRE_SEQUENCE``
     - ``TRUE``
     - Requires every direction commit to use the previous sequence plus one.
   * - ``G_WATCHDOG_TIMEOUT_CYCLES``
     - ``31200000``
     - Timeout for an unfinished protected access, approximately 15 seconds
       at 2.08 MHz.
   * - ``G_SAFE_DIRECTION_VALUE``
     - all zero
     - Direction mask loaded after reset.  Zero configures every channel as
       D-Slot-to-FPGA input.

I2C addresses
=============

The primary MachXO2 EFB I2C slave requires address bits ``A1:A0`` to be
``01``.  Consecutive addresses such as ``0x42`` are rejected by Diamond.

.. list-table::
   :header-rows: 1
   :widths: 15 20 20 45

   * - D-Slot
     - ``G_SLOT_INDEX``
     - Address
     - Generated implementation
   * - D1
     - ``0``
     - ``0x41``
     - ``i2c_d1``
   * - D2
     - ``1``
     - ``0x45``
     - ``i2c_d2``
   * - D3
     - ``2``
     - ``0x49``
     - ``i2c_d3``
   * - D4
     - ``3``
     - ``0x4D``
     - ``i2c_d4``
   * - D5
     - ``4``
     - ``0x51``
     - ``i2c_d5``

The selected address is compiled into the EFB primitive and cannot be changed
at runtime.  Register ``0x04`` provides readback of the compiled address.

Signal routing and safety
=========================

Each bit of ``active_direction`` controls one channel:

.. list-table::
   :header-rows: 1
   :widths: 18 30 52

   * - Direction bit
     - Direction
     - VHDL behavior
   * - ``1``
     - FPGA to D-Slot (TX)
     - ``d_n <= tx_source(n) AND enable_forwarding``; the FPGA-side input
       driver is high impedance.
   * - ``0``
     - D-Slot to FPGA (RX)
     - ``fpga_n <= d_n``; the D-Slot output driver is high impedance.

``tx_source`` normally contains the sampled FPGA pin values.  In TX test mode
it contains ``active_test_pattern`` instead.

``enable_forwarding`` is the logical AND of the local forwarding request and
the inverted heartbeat safe-state request.  Therefore:

* a valid heartbeat permits TX forwarding,
* a missing, stuck or malformed heartbeat forces every TX output low,
* RX channels continue to forward their D-Slot input to the FPGA, and
* the test mode cannot override the safe-state gate.

The heartbeat input is synchronized through two flip-flops.  The receiver
accepts edges only when their spacing is between 10 and 52 clock cycles
(approximately 4.8 to 25 microseconds at 2.08 MHz).  Sixteen consecutive valid
edges are required before forwarding is enabled.  If no edge is received for
208 cycles (approximately 100 microseconds), safe state is asserted again.

SIO interface
=============

``sio_fsm4i2c`` exposes the following byte-oriented signals to the top level:

.. list-table::
   :header-rows: 1
   :widths: 25 75

   * - Signal
     - Meaning
   * - ``sio_wr1st``
     - One-clock strobe for the first byte of an I2C write transaction.  The
       top level uses this byte as the register pointer.
   * - ``sio_wrstb``
     - One-clock strobe for each following write byte.
   * - ``sio_indata``
     - Received byte corresponding to ``sio_wr1st`` or ``sio_wrstb``.
   * - ``sio_cmdbyte_valid``
     - Validation result for the first byte.  An invalid register address is
       answered with NACK.
   * - ``sio_rdack``
     - Indicates that one byte from ``sio_outdata`` was accepted for
       transmission; the register pointer is incremented.
   * - ``sio_rdcnt``
     - Becomes active after the EFB TX FIFO has been filled, indicating an
       extended read.
   * - ``sio_rdlst``
     - Marks the end of an I2C read transaction.
   * - ``sio_outdata``
     - Current register byte supplied by the top level to the EFB TX FIFO.

The register pointer auto-increments after every data write and every
acknowledged read.  This permits compact multi-byte transactions with
``i2ctransfer``.

EFB transport state machine
===========================

The state machine uses ``syn_encoding = "safe"`` so synthesis adds recovery
from illegal state encodings.  It initializes and polls both the primary and
secondary EFB I2C controllers, although the current EFB wrapper enables only
the primary controller.

.. mermaid::
   :align: center
   :caption: Simplified ``sio_fsm4i2c`` state transitions

   stateDiagram-v2
      [*] --> Reset
      Reset --> I2Cenable
      I2Cenable --> I2Cconfig: I2CEN written
      I2Cconfig --> I2Cidlewait: command register configured
      I2Cidlewait --> I2Cfifoflush: controller not busy
      I2Cfifoflush --> I2Cenable: initialize secondary controller
      I2Cfifoflush --> I2Ctransferwait: both FIFOs flushed
      I2Ctransferwait --> I2Cdirectioncheck: TRRDY
      I2Ctransferwait --> I2Cconfig: transfer ended
      I2Cdirectioncheck --> I2CwrXO2rx: controller receives I2C write
      I2Cdirectioncheck --> I2CrdXO2tx: controller serves I2C read
      I2CwrXO2rx --> I2CwrXO2ack
      I2CwrXO2ack --> I2Ctransferwait: valid command/data byte
      I2CwrXO2ack --> I2CwrXO2wait: invalid command byte/NACK
      I2CwrXO2wait --> I2Cconfig: bus becomes idle
      I2CrdXO2tx --> I2CrdXO2wait
      I2CrdXO2wait --> I2CrdXO2tx: next byte requested
      I2CrdXO2wait --> I2Cconfig: read transaction ended

State descriptions
------------------

.. list-table::
   :header-rows: 1
   :widths: 24 76

   * - State
     - Function
   * - ``Reset``
     - Clears the Wishbone master outputs and selects the primary controller.
   * - ``I2Cenable``
     - Writes ``I2CEN`` to the selected EFB I2C control register.
   * - ``I2Cconfig``
     - Writes ``CSDIS`` to the command register and clears the previous
       read-last indication.
   * - ``I2Cidlewait``
     - Polls the EFB status register until the controller is not busy.
   * - ``I2Cfifoflush``
     - Reads the RX data register repeatedly to discard stale FIFO bytes.
       During startup this sequence is performed for both EFB controllers.
   * - ``I2Ctransferwait``
     - Polls ``TRRDY`` and ``BUSY``.  It alternates between controllers while
       idle and detects the start or end of a transaction.
   * - ``I2Cdirectioncheck``
     - Waits four Wishbone clocks after ``TRRDY`` before evaluating ``SRW``,
       as required by the EFB timing specification.  ``SRW=1`` selects the
       I2C-read path; ``SRW=0`` selects the I2C-write path.
   * - ``I2CwrXO2rx``
     - Reads one byte from the EFB RX FIFO and generates either
       ``sio_wr1st`` or ``sio_wrstb``.
   * - ``I2CwrXO2ack``
     - Writes ACK or NACK to the EFB command register.  Only an invalid first
       command byte is rejected.
   * - ``I2CwrXO2wait``
     - Waits for the bus to become idle after an invalid command byte.
   * - ``I2CrdXO2tx``
     - Writes ``sio_outdata`` to the EFB TX FIFO and pulses ``sio_rdack``.
   * - ``I2CrdXO2wait``
     - Waits for another byte request or the end of the read transaction.

Wishbone helper functions
-------------------------

The FSM contains small helper procedures rather than duplicating bus logic:

* ``WB_GoIdle`` clears address, data, write-enable and strobe.
* ``WB_DoWrite`` starts one Wishbone write.
* ``WB_StartRead`` starts one Wishbone read.
* ``WB_IsDone`` detects ``wb_ack_i AND wb_stb_o``.
* ``WB_CheckDoneGoIdle`` detects completion and returns the bus to idle.
* ``WB_ReadAndCheckBitSet`` tests masked status-register bits.

Register map
============

Unless stated otherwise, unused bits read as zero.  Only bits 0 through 5 of
the fourth 30-bit data byte are used.

.. list-table::
   :header-rows: 1
   :widths: 14 12 28 46

   * - Address
     - Access
     - Name
     - Description
   * - ``0x00``
     - R
     - Device ID
     - Returns ``G_DEVICE_ID`` (default ``0x31``).
   * - ``0x01``
     - R
     - Interface version
     - Current interface version, ``0x02``.
   * - ``0x02``
     - R
     - Status
     - Protocol, safety, unlock and watchdog flags described below.
   * - ``0x03``
     - R
     - Active sequence
     - Sequence number of the last accepted direction commit.
   * - ``0x04``
     - R
     - I2C address
     - Compiled EFB slave address.
   * - ``0x05``
     - R
     - Reject counter
     - Saturating count of rejected commits and test commands.
   * - ``0x08``--``0x0B``
     - R
     - Active direction
     - Applied 30-bit direction mask.
   * - ``0x0C``
     - R
     - Direction write mask
     - Bits 3:0 indicate which shadow bytes were written.
   * - ``0x0D``
     - R/W
     - Unlock key 1
     - Write ``0xC3`` to enter unlock stage 1.
   * - ``0x0E``
     - R/W
     - Unlock key 2
     - Write ``0x5A`` after key 1 to enter unlock stage 2.
   * - ``0x0F``
     - R/W
     - Pending sequence
     - Sequence number proposed for the next direction commit.
   * - ``0x10``--``0x13``
     - R/W
     - Shadow direction
     - Pending 30-bit direction mask.
   * - ``0x14``
     - R/W
     - Direction commit
     - Write ``0xA5`` to validate and atomically apply the shadow mask.
   * - ``0x20``--``0x23``
     - R
     - FPGA pin levels
     - Sampled levels at the FPGA-facing pins.
   * - ``0x24``
     - R
     - Safety status
     - Raw and decoded safety/interface signals.
   * - ``0x28``--``0x2B``
     - R
     - D-Slot pin levels
     - Sampled levels at the adapter-facing pins.
   * - ``0x30``--``0x33``
     - R/W
     - Shadow TX pattern
     - Pending 30-bit debug pattern.
   * - ``0x34``
     - R/W
     - TX test command
     - Write ``0xA6`` to enable/commit or ``0x59`` to disable.
   * - ``0x35``
     - R
     - TX test status
     - Bit 0 is test enable; bits 7:4 are the pattern write mask.
   * - ``0x38``--``0x3B``
     - R
     - Active TX pattern
     - Pattern currently replacing the FPGA TX values.

Status register ``0x02``
------------------------

.. list-table::
   :header-rows: 1
   :widths: 12 88

   * - Bit
     - Meaning when set
   * - 0
     - At least one valid direction configuration was committed.
   * - 1
     - All four direction shadow bytes have been written.
   * - 2
     - The pending sequence is valid (or sequence checking is disabled).
   * - 3
     - Heartbeat logic requests safe state.
   * - 4
     - Output forwarding is enabled.
   * - 5
     - Both unlock keys were accepted.
   * - 6
     - A protected configuration/test access is in progress.
   * - 7
     - The 15-second access-window watchdog expired.

Safety register ``0x24``
------------------------

.. list-table::
   :header-rows: 1
   :widths: 12 88

   * - Bit
     - Signal
   * - 0
     - ``pilot_in``
   * - 1
     - ``carrierrdy``
   * - 2
     - Raw ``reqsafestate`` input
   * - 3
     - Decoded ``safe_state_request``
   * - 4
     - ``sio_rdcnt``
   * - 5
     - ``sio_rdlst``

Safe direction update protocol
==============================

Direction changes use a shadow-and-commit protocol.  The active outputs do not
change until all validation conditions pass in the same commit operation.

First configuration after reset
-------------------------------

The first accepted configuration does not require the unlock keys:

1. Write sequence ``0x01`` to ``0x0F``.
2. Write all four direction bytes to ``0x10`` through ``0x13``.
3. Write ``0xA5`` to ``0x14``.

Example for all 30 channels as TX on address ``0x41``:

.. code-block:: console

   i2ctransfer -y 4 w7@0x41 0x0f 0x01 0xff 0xff 0xff 0x3f 0xa5

Later configuration changes
---------------------------

After the first configuration, every change requires both unlock keys and the
next sequence number:

.. code-block:: console

   i2ctransfer -y 4 w3@0x41 0x0d 0xc3 0x5a
   i2ctransfer -y 4 w7@0x41 0x0f 0x02 0xff 0x00 0xff 0x00 0xa5

A direction commit is rejected if:

* one or more shadow bytes are missing,
* the commit byte is not ``0xA5``,
* the sequence is not exactly ``active_sequence + 1``, or
* an existing configuration is changed without a complete unlock.

The unlock is consumed by a commit attempt regardless of success.  The reject
counter saturates at ``0xFF``.

Access-window watchdog
----------------------

Starting an unlock, direction update or test-pattern update opens the
configuration window.  If it is not completed within approximately 15
seconds, the design clears the unlock state and both shadow write masks.
The last active direction and active test pattern remain unchanged.  This
watchdog protects against abandoned partial commands; it does not require
periodic I2C traffic during normal operation.

TX test mode
============

The test mode replaces FPGA TX values with a 30-bit I2C pattern.  It affects
only channels configured as TX.

Enable all TX outputs:

.. code-block:: console

   i2ctransfer -y 4 w3@0x41 0x0d 0xc3 0x5a
   i2ctransfer -y 4 w6@0x41 0x30 0xff 0xff 0xff 0x3f 0xa6

Disable test mode and return to FPGA data:

.. code-block:: console

   i2ctransfer -y 4 w3@0x41 0x0d 0xc3 0x5a
   i2ctransfer -y 4 w2@0x41 0x34 0x59

The active test pattern remains latched until changed, disabled or reset.
Every enable or disable command requires a fresh unlock sequence.

Readback and diagnostics
========================

Detect devices:

.. code-block:: console

   i2cdetect -y 4

Read identity, version, status, sequence, address and rejects:

.. code-block:: console

   i2ctransfer -y 4 w1@0x41 0x00 r6

Read active direction:

.. code-block:: console

   i2ctransfer -y 4 w1@0x41 0x08 r4

Read FPGA-side and D-Slot-side pin levels:

.. code-block:: console

   i2ctransfer -y 4 w1@0x41 0x20 r4
   i2ctransfer -y 4 w1@0x41 0x28 r4

Read TX test state and pattern:

.. code-block:: console

   i2ctransfer -y 4 w1@0x41 0x35 r1
   i2ctransfer -y 4 w1@0x41 0x38 r4

Automated Diamond build
=======================

The five images are generated with one PowerShell command:

.. code-block:: powershell

   powershell -ExecutionPolicy Bypass -File `
     .\tools\diamond\build_i2c_dslot_images.ps1

The PowerShell wrapper validates the Diamond installation, project and Tcl
script before invoking ``pnmainc.exe``.

The Tcl script:

1. opens ``uz_d_slots.ldf``,
2. creates or reuses five implementation clones,
3. copies the current base ``i2ctesting.vhdl`` into every clone,
4. assigns ``G_SLOT_INDEX=0`` through ``4`` using ``HDL_PARAM``,
5. cleans previous implementation results,
6. executes ``Synthesis``, ``Translate``, ``Map``, ``PAR`` and ``Export``,
7. verifies that ``.bit`` and ``.jed`` files exist, and
8. collects them below ``uz_d_slots/i2c_dslot_images``.

The generated files are named
``uz_d_slots_i2c_d1.bit/.jed`` through
``uz_d_slots_i2c_d5.bit/.jed``.

PetaLinux debug scripts
=======================

Single-CPLD script
------------------

``dslot_i2c_debug.sh`` defaults to bus 4 and address ``0x41``.  It:

* checks that ``i2ctransfer`` is installed,
* reads identity and diagnostic registers,
* calculates the next sequence number,
* configures all 30 channels as TX,
* verifies the direction readback,
* displays forward/reverse running lights, alternating patterns and
  all-on/all-off patterns, and
* disables test mode when interrupted.

Supported commands:

.. code-block:: console

   ./dslot_i2c_debug.sh
   ./dslot_i2c_debug.sh status
   ./dslot_i2c_debug.sh stop

The bus, address and delay can be overridden:

.. code-block:: console

   BUS=4 ADDR=0x45 DELAY=0.1 ./dslot_i2c_debug.sh

Dual-CPLD script
----------------

``dslot_dual_i2c_debug.sh`` defaults to D1 (``0x41``) and D2 (``0x45``).
It independently validates and configures both CPLDs, then generates:

* synchronized running lights,
* opposing running lights,
* complementary alternating patterns, and
* alternating full-card flashes.

.. code-block:: console

   ./dslot_dual_i2c_debug.sh
   ./dslot_dual_i2c_debug.sh status
   ./dslot_dual_i2c_debug.sh stop

Both scripts install signal handlers for ``INT``, ``TERM`` and ``HUP``.
Cleanup disables the protected TX test mode so normal FPGA-driven TX data is
restored.  If an SSH terminal cannot deliver ``Ctrl+C``, run the ``stop``
command from a second session.

Limitations
===========

* The EFB I2C address is a synthesis parameter, not a runtime register.
* The register protocol currently controls direction and test data; normal TX
  data still originates from the FPGA.
* The TX test mode is not a replacement for application-level output logic.
* The implementation assumes the internal 2.08 MHz clock used by the current
  EFB and heartbeat timing.
* Upper bits 7 and 6 of every fourth 30-bit value byte are ignored.
