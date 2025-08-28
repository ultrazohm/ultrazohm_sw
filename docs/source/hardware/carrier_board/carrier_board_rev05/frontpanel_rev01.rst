.. _frontpanelmainboard_rev01:

============================
Frontpanel Mainboard (Rev01)
============================

Fully PCB-based frontpanels are used exclusively in combination with carrier boards ≥ Rev05 (and are not compatible with earlier revisions/versions at all).

The frontpanel (FP) PCB contains the following connectors and features (cf. :ref:`carrier_board_rev5_summary` of the new carrier for a higher-level summary):

- ``X1`` is an internal PCB-based edge connector that links the FP to the carrier (connector ``X1``, cf. Frontpanel.SchDoc for details) whilst ``X2`` (`_buttonboard <https://bitbucket.org/ultrazohm/uz_frontpanel_buttonboard/>`_) and ``X12`` (`_firstfloor <https://bitbucket.org/ultrazohm/uz_frontpanel_firstfloor/>`_) link to the other frontpanel PCBs within the system
- ``X3`` is a USB-C connector that accesses the integrated, isolated USB to dual-JTAG/UART interface on the carrier board. Please refer to the :ref:`label_cpld_programming_ftdi4ch` guide for details on JTAG programming.
- ``X4`` is a dual-port Ethernet connector that exposes the on-carrier (on the left, RGMII-based) and on-FP (right-hand side, via SGMII) PHYs to the outside
- ``X5`` is the External STOP connector known from previous carrier boards (cf. :ref:`external_stop` for details). Note that pins 1 and 2 no longer are NC -- Instead, they can be configured as additional I²C I/Os (cf. ``Extra01``-``2``) by means of ``U8``.
- ``X6`` is a 15-pin D-Sub connector that provides up to 12 software- and/or up to five hardware-controlled I/Os. The former rely on a flexible I²C GPIO (cf. ``U8``) that also interfaces the :ref:`carrier_board_rev5_s3c` (via an interrupt and a reset signal). The latter are fixed-direction (3x O, 2x I) signals (``FlexIOs``) that directly interface the S³C for time- and/or safety-critical functionalities like, e.g., heartbeats (NB: as the precise requirements are highly application-specific, no default implementation is provided as by ``uz_sw`` et al.). Also note that the on-board supply is limited to 100mA for the entire isoIO circuitry, which limits the current that may be drawn externally.
- ``X7`` is an internal, 2280-sized M.2 slot that can be used to connect many off-the-shelf PCIe x1 extension cards. Due to limitations in the current ``uz_sw``, this feature requires manual PS configuration via Vivado's PCW on the software side, whilst the PCIe reference clock on the FP has to be enabled by means of ``R2``. A 5V supply is available on ``X9`` (NB: observe connector/cable pin-out and maximum supply current) if required by the M.2 PCIe card.
- ``X10`` is an internal, 2280-sized M.2 slot for a 6-Gbit/s-SATA3 SSD (which is supplied from the carrier's ``3V3_PER`` rail and, thus, subject to its limits)

.. figure:: img/fp-main_annotated.jpg
   :width: 75%
   :align: center

For pin-outs and more details (in particular w.r.t. the isoIOs), please refer to the schematic of :ref:`frontpanelmainboard_rev02` as the pin-compatible successor.

Downloads
---------

Please refer to the `uz_frontpanel_main <https://bitbucket.org/ultrazohm/uz_frontpanel_main/>`_ repository for design files, the MPNs of the components used etc.
