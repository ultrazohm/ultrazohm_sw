.. _dslot_rev05:

===========
D-Slot CPLD
===========


General
-------

- Device: Lattice Mach XO2
- Part: LCMXO2-2000HC-4TG100C
- Designator: U4A-U4E
- Integrated Flash memory for configuration storage (bitstream)
- Programmable via JTAG, SPI (PS-SPI0) and I2C (PS-I2C0)
- No external clock source integrated on carrier

MachXO2 implementation notes
----------------------------

The Rev05+ D-Slot CPLD programs are maintained in the ``cpld_lattice`` repository below ``MACHXO2/D_Slot_CPLD_LCMXO2-2000HC-4TG100C/uz_d_slots``.
Archive and pre-heartbeat folders in the MachXO2 repository are historical snapshots only.
They represent states before the heartbeat-based safe-state handling was introduced or stabilized and are therefore not current design sources.
Do not use these archived/pre-heartbeat folders for new programming files, timing checks or implementation comparisons unless the historical state is explicitly required.
The current source of truth is the active implementation in ``uz_d_slots`` together with the shared ``xo2_libraries/lib_sXc.vhd`` helper library and the maintained implementation list below.
All active implementations use Lattice Diamond with Synplify Pro as synthesis tool and the project strategy enables VHDL-2008.
The ``Voltage_3v3_5v`` subfolder contains the maintained MachXO2 CPLD implementations for the :ref:`digitalVoltage_3v3_5v` adapter card.
Because this card defines its signal directions in four hardware groups, the CPLD repository provides the generated variants below ``Voltage_3v3_5v/voltage_8*_8*_8*_6*``.
The name encodes the direction of the four groups in D-Slot order: three groups with eight I/Os each and one group with six I/Os, e.g. ``voltage_8rx_8rx_8tx_6tx``.

The common library currently provides the clock/reset helper, tick generator, debouncer and the D-Slot heartbeat receiver.
D-Slot programs that actively drive adapter-card outputs use ``dslot_heartbeat_receiver`` to gate their output forwarding with the decoded safe-state request:

.. code-block:: vhdl

   dslot_heartbeat: ENTITY work.dslot_heartbeat_receiver
      PORT MAP (
         reqsafestate       => reqsafestate,
         safe_state_request => safe_state_request
      );

   enable_forwarding <= user_enable_forwarding AND NOT safe_state_request;

.. warning::

   Breaking change: MachXO2 D-Slot programs must no longer treat ``reqsafestate`` as a purely static logic level.
   During power-down or fault handling, the D-Slot CPLD's 1.8 V I/O supply can fall faster than the CPLD core supply.
   In this transition the CPLD can be operated outside its specified supply conditions, so a static level on ``ReqSafeState`` is not sufficient to prove normal operation.
   The heartbeat therefore defines the valid operating condition: only a continuously received and correctly timed heartbeat permits output forwarding.
   A missing, stuck or malformed heartbeat forces the D-Slot CPLD into its safe state.

   The :ref:`digitalVoltage_3v3_5v` card is a special case only when its S2 DIP switch is configured to ``use CarrierBoard``.
   In this configuration, the card uses the carrier-board ``SlotOE`` / output-enable signal directly.
   This provides a second fallback layer on the adapter card itself: the level shifter outputs are disabled by the card's output-enable path, so the card does not show the power-down glitch behavior that motivated the heartbeat-based safe-state detection for generic D-Slot programs.
   If S2 is configured to ``use Supervisors`` instead, the card behaves equivalently to the other D-Slot adapter cards with respect to this heartbeat-based safe-state handling.
   The heartbeat remains the default system-level proof of normal operation for the MachXO2 D-Slot CPLD.

If the heartbeat from the S3C is missing or invalid, ``safe_state_request`` is asserted and the D-Slot outputs are disabled.
Card-specific logic should therefore only define ``user_enable_forwarding``, optional local safety conditions and the concrete FPGA-to-adapter routing.
The shared heartbeat and safe-state handling must stay common so all D-Slot programs react consistently to S3C faults and stop requests.

.. note::

   The heartbeat is used for D-Slot programs that actively drive adapter-card outputs, i.e. general I/O, voltage-card, temperature-card and inverter-style programs.
   Pure receive/encoder signal paths do not use the heartbeat as output-enable condition because they do not actively drive the adapter-card outputs that need to be forced into the safe state.
   Some RX/encoder implementations may still contain the common heartbeat receiver template for ``SlotOK``/project consistency, but the safety-relevant heartbeat gating applies to the output-forwarding path only.

.. list-table:: Heartbeat usage by maintained MachXO2 D-Slot program
   :widths: 30 18 52
   :header-rows: 1

   * - Program / implementation
     - Heartbeat-gated output forwarding
     - Notes
   * - ``tx30``
     - Yes
     - General-purpose output/I/O forwarding from FPGA to adapter card.
   * - ``tx26_w_enable``
     - Yes
     - General-purpose output/I/O forwarding with additional user enable pattern.
   * - ``tx16_14rx``
     - Yes, for TX pins
     - Mixed TX/RX program; heartbeat gates the output-driving TX path.
   * - ``tx20_10rx``
     - Yes, for TX pins
     - Mixed TX/RX program; heartbeat gates the output-driving TX path.
   * - ``optical_14tx_4rx``
     - Yes, for TX pins
     - Mixed optical program; heartbeat gates the output-driving TX path.
   * - ``uz_d_3ph_inverter``
     - Yes
     - Inverter adapter program; gate outputs must enter the safe state when the heartbeat is missing or invalid.
   * - ``uz_d_temperature_ltc2983``
     - Yes
     - Temperature-card SPI/control lines are output-gated through the common safe-state handling.
   * - ``Voltage_3v3_5v/voltage_8*_8*_8*_6*``
     - Yes, for TX groups
     - Generated variants for the :ref:`digitalVoltage_3v3_5v` card; heartbeat gates all groups configured as outputs.
   * - ``rx30``
     - No
     - Receive-only program; no adapter output path needs heartbeat-based disabling.
   * - ``uz_d_abs_encoder``
     - No
     - Encoder signal routing is not treated as heartbeat-gated output forwarding.
   * - ``uz_d_resolver_d1_to_d4``
     - No
     - Resolver/encoder-style signal routing is not treated as heartbeat-gated output forwarding.
   * - ``uz_d_resolver_d5``
     - No
     - Resolver/encoder-style signal routing for D5 is not treated as heartbeat-gated output forwarding.
   * - ``template_dslots``
     - Yes
     - Template for new output/I/O programs; keep the heartbeat-gated ``enable_forwarding`` pattern for output-driving designs.

The MachXO2 D-Slot project contains the following maintained implementations:

- ``tx30``
- ``tx26_w_enable``
- ``rx30``
- ``optical_14tx_4rx``
- ``uz_d_3ph_inverter``
- ``uz_d_resolver_d1_to_d4``
- ``uz_d_resolver_d5``
- ``uz_d_abs_encoder``
- ``uz_d_temperature_ltc2983``
- ``tx16_14rx``
- ``tx20_10rx``
- ``Voltage_3v3_5v`` with the generated ``voltage_8*_8*_8*_6*`` variants for the :ref:`digitalVoltage_3v3_5v` card
- ``template_dslots``