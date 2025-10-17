===================
I²C bus assignments
===================

The per-(sub-)bus identifiers for(/on/of) Linux-enabled UltraZohm systems are listed like **[so]**.


.. _carrier_board_i2c_rev05ff:

I²C on ≥Rev05 carriers
----------------------

* I²C0 (``PS_I2C0``) **[0]**: "User bus" (``I2C_USR``) with eight-channel I²C switch

  * ``ASlots_I2C`` **[3]**: :ref:`Per-card "UZP EEPROM"s <uzpA53_cardid>`
  * ``DSlots_I2C`` **[5]**: :ref:`Per-card "UZP EEPROM"s <uzpA53_cardid>` and :ref:`card-specific functions <uzpA53_dcards>`
  * ``CPLDs_I2C`` **[4]**: Primary I²C controllers of D slot CPLDs (1V8)
  * ``I2C_SEC`` **[7]**: Secondary I²C controller of S³C (1V8)

    * On ≥Rev06 carriers, this bus also controls the I²C GPIO of the :ref:`slot disable feature <carrier_board_rev06_summary>`

  * ``I2C_FP_isoIOs`` **[2]**: IsoIOs on :ref:`frontpanelmainboard_rev01` and :ref:`frontpanelmainboard_rev02`
  * ``BP_T``/``BP_B`` **[8/6]**: Backpanels
  * Spare **[9]**: On ≥Rev06 carriers, this bus can be accessed via ``X3`` (NB: pull-up Rs needed!)
  * The multiplexer can be reset via a MIO GPIO, which is helpful in case of bus lock-ups

* I²C1 (``PS_I2C1``) **[1]**: "System bus" (``I2C_SYS``)

  * ``SOM_I2C``: SoM PLL and EEPROM
  * ``I2C_PRI``: Primary I²C controller of S³C (3V3)
  * ``I2C_SYS_3V3``: :ref:`Carrier "UZP EEPROM" <uzpA53_init>`, frontpanel (system bus; used, e.g., for the MAC EEPROM required/included on Ethernet-enabled frontpanels), and thermal management


.. _carrier_board_i2c_rev01-4:

I²C on ≤Rev04 carriers
----------------------

[for reference only, please see :ref:`carrier_board_rev04_mios` et al. and their schematics for details]

* I²C0 (``PS_I2C0_*``) **[0]**: SoM & adapter cards

  * SoM I²C (PLL and, perhaps, EEPROM)
  * A adapter card slots (3V3)
  * D adapter card slots (3V3)
  * D adapter card CPLDs (1V8, unused as of 2025)

* I²C1 (``PS_I2C1_*``) **[1]**: Outside (connector)

  * Available on ``X10`` (3V3)
  * Used by the :ref:`carrier_retrofits_i2cssds2c` board
