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

For identifying programmed MachXO2 bitstreams, the following TRACEIDs are assigned to the D-Slot CPLDs.
The Diamond ``UserCode`` field is not used for this mapping; the value is written to the Diamond ``TRACEID`` configuration field.
The leading ``2`` denotes the second revision of the MachXO2 D-Slot bitstreams.

.. _usercode_cpld_dslot:
.. csv-table:: Overview of the TRACEIDs for D-Slots (Rev05)
  :file: interfaces/usercodedslot.csv
  :widths: 5 8 8 8
  :header-rows: 1

MachXO2 implementation notes
----------------------------

The Rev05 D-Slot CPLD programs are maintained in the ``cpld_lattice`` repository below ``MACHXO2/D_Slot_CPLD_LCMXO2-2000HC-4TG100C/uz_d_slots``.
All active implementations use Lattice Diamond with Synplify Pro as synthesis tool and the project strategy enables VHDL-2008.
The common MachXO2 helper logic is not copied into each program anymore; it is pulled into every implementation from ``xo2_libraries/lib_sXc.vhd``.
This keeps the individual D-Slot files focused on their card-specific routing.

The common library currently provides the clock/reset helper, tick generator, debouncer and the D-Slot heartbeat receiver.
Each D-Slot design instantiates ``dslot_heartbeat_receiver`` and gates its output forwarding with the decoded safe-state request:

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

The MachXO2 D-Slot project contains the following maintained implementations:

- ``tx30``
- ``tx26_w_enable``
- ``rx30``
- ``optical_14tx_4rx``
- ``uz_d_3ph_inverter``
- ``uz_d_resolver_d1_to_d4``
- ``uz_d_resolver_d5``
- ``uz_d_abs_encoder_ssi_rev01``
- ``tx16_14rx``
- ``tx20_10rx``
- ``template_dslots``
