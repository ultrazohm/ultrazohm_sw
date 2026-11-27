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
- Programmable via JTAG, SPI (PS-SPI0) and I²C (PS-I2C0)
- No external clock source integrated on carrier

For identifying programmed bitstreams, the following ids are assigned to the D-CPLDs:

.. _usercode_cpld_dslot:
.. csv-table:: Overview of the User Codes for D-Slots (Rev05)
  :file: interfaces/usercodedslot.csv
  :widths: 5 8 8 5
  :header-rows: 1

.. _dslot_vin_rail_fault:

VIN minimum load and rail-fault monitoring
------------------------------------------

The high-side switch of each D-slot monitors the adapter card's ``VIN`` supply
and provides the active-low ``RailnFAULT_1V8_DSLOT`` signal to the corresponding
D-slot CPLD. For reliable rail monitoring, the adapter card must draw the
required minimum current from ``VIN``.

Many adapter cards do not use the ``VIN`` rail and therefore draw no current
from it. From the perspective of the rail-monitoring circuit, such a card is
indistinguishable from an empty D-slot. Consequently,
``RailnFAULT_1V8_DSLOT`` cannot provide a valid indication of the card's supply
condition unless the adapter card applies a defined minimum load to ``VIN``.

For example, the :ref:`Digital IncrEncoder Rev04 <dig_incEncoderRev04>`
implements a permanent 10 mA LED load in the ``Power_Load_LEDs10mA.SchDoc``
schematic block. This additional load makes the inserted card detectable by the
rail-monitoring circuit and allows ``RailnFAULT_1V8_DSLOT`` to provide a valid,
reliably distinguishable status.

The D-slot CPLD reports the resulting slot status to the S3C, which performs the
system-level supervision and can request a safe state. The behavior within the
slot is defined by the programmed D-slot CPLD firmware.
The complete monitoring path is described in
:ref:`A-slot and D-slot VIN supervision <carrier_board_rev05_s3c_dslot_vin>`.
