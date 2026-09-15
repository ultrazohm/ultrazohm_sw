.. _frontpanelmainboard_rev03:

============================
Frontpanel Mainboard (Rev03)
============================

The third revision of the PCB-based frontpanel for carrier boards ≥ Rev05 adds the following features in comparison to :ref:`frontpanelmainboard_rev02`:

- I/O protection (ESDS30x) on

  - both Ethernet ("LAN") ports,
  - the External STOP connector and
  - the IsoIOs (using D-Sub ``X6``).

- The latter follows the solution on ≤Rev04 carriers, although physical pull-down resistors are set to DNP with the exception of the External STOP's channel (as software-configurable ones are available via ``U8``)
- Various production-related optimizations (functions unchanged)

Downloads
---------

- :download:`Schematic Rev03 <frontpanel/SCH_uz_frontpanel_main_Rev03Batch00_03.pdf>`
- Please refer to the `uz_frontpanel_main <https://bitbucket.org/ultrazohm/uz_frontpanel_main/>`_ repository for design files, the MPNs of the components used etc.
