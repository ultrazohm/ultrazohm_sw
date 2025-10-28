.. _frontpanelmainboard_rev02:

============================
Frontpanel Mainboard (Rev02)
============================

The second revision of the PCB-based frontpanel for carrier boards ≥ Rev05 adds the following features in comparison to :ref:`frontpanelmainboard_rev01`:

- The ``3V3isoIOs`` supply has been extended from ~100mA to ~1A maximum output current (for the entire subsystem -- cf. below for connector limits)
- All outgoing isoI/Os and 3V3 rails on ``X5`` (External STOP) and ``X6`` (isoIOs) are now protected against overcurrents

  - The maximum current for all 8+4+2 I²C-based I/Os (i.e., ``IO01``-``8`` and -- if used -- ``FlexIO01``-``4`` on ``X6``, and ``Extra01``-``2`` on ``X5``) is limited to 164mA typ.
  - The maximum current on the 3V3isoIOs output (connector ``X6`` pin 15) is limited to 601mA typ., and also applies to any enabled ``FlexIO`` output(s)
  - The maximum short-circuit current on the 3V3isoIOs pin of the External STOP connector is 22mA (cf. ``R44``)
  - Overcurrent conditions can be reported back to the carrier by means of an OD signal (cf. F̅A̅U̅L̅T̅) on the I²C GPIO (``U8``)

- The internal 5V output ``X9`` now uses a Molex connector (instead of a generic 2-pin spring clamp connector)
- Supply rail protection on ``X9`` (current limit at 909mA typ.)
- Various production-related optimizations (functions unchanged)

Downloads
---------

- :download:`Schematic Rev02 <frontpanel/SCH_uz_frontpanel_main_Rev02Batch00_02.pdf>`
- Please refer to the `uz_frontpanel_main <https://bitbucket.org/ultrazohm/uz_frontpanel_main/>`_ repository for design files, the MPNs of the components used etc.
