.. _hardware:

========
Hardware
========


Overview
--------

The following pages introduce key components, concepts and aspects of any UltraZohm system:

.. toctree::
    :maxdepth: 1

    carrier_board/carrier_board
    adapter_cards/adapter_cards
    altium/altium
    interface_powerelectronics/interface_powerelectronics

As of 2025, there are two "major versions" of UltraZohm systems in existence:

1. Systems based on carrier boards :math:`\leq` Rev04, where

  * system power is controlled by a "0/1" power *switch* on the front panel,
  * power supply and 230V inlet are located on the SoM (i.e., when looking from the front, left-hand) side of the chassis, and
  * the front panel consists of several individual components (e.g., a dedicated cable harness per Ethernet, USB, and CAN connector).

  Please refer to the left-hand side of :ref:`frontpanel-photos` if you are unsure about the revision :)

2. Systems based on carrier boards :math:`\geq` Rev05, where

  * system power is controlled by a power *button* on the front panel (and a 230V switch on the back panel, cf. :ref:`carrier_board_rev05_04usr` and :ref:`carrier_board_rev05_s3c`),
  * power supply and 230V inlet are located on the adapter card (i.e., when looking from the front, right-hand) side of the chassis, and
  * the front panel consists of three interconnected PCBs, most notably the :ref:`Front Panel Mainboard <frontpanelmainboard_rev01>` (which links the entire assembly to the carrier).

  Please refer to the right-hand side of :ref:`frontpanel-photos` if you are unsure about the revision :)

.. _frontpanel-photos:
.. list-table:: Comparison of front panels across carrier board revisions (photos)
   :header-rows: 1
   :align: center

   * - Front panel for :math:`\leq` Rev04 carriers
     - Front panel for :math:`\geq` Rev05 carriers
   * - .. image :: hardware/frontpanel_Rev01-4UZs.jpg
          :width: 100%
     - .. image :: hardware/frontpanel_Rev05ffUZs.jpg
          :width: 100%


Adapter Cards
-------------

.. toctree::
    :maxdepth: 1
    :caption: Analog Cards

    adapter_cards/analog/LTC2311_16
    adapter_cards/analog/uz_dac8831/uz_dac8831


.. toctree::
    :maxdepth: 1
    :caption: Digital Cards

    adapter_cards/digital/optical/optical_general
    adapter_cards/digital/inc_encoder/incr_encoder_general
    adapter_cards/digital/digital_voltage/digital_voltage_general
    adapter_cards/digital/Digital_BreakoutBoard_v1
    adapter_cards/digital/encoder_v1
    adapter_cards/digital/temperature_rev02/temperature_rev02
    adapter_cards/digital/Digital_Resolver_rev01
    adapter_cards/digital/inverter/inverter_general


Additional Components
---------------------

.. toctree::
    :maxdepth: 1
    :caption: External

    adapter_cards/external/uz_per_adc_to_bnc/uz_per_adc_to_bnc_rev01
    adapter_cards/external/loopback_PCB/loopback_PCB
    adapter_cards/external/uz_per_torque_box/uz_per_torque_box
    adapter_cards/external/deskbench_terminal/deskbench_terminal
    adapter_cards/external/rj_45_breakout/rj45_breakout


.. toctree::
    :maxdepth: 1
    :caption: Internal

    adapter_cards/internal/uz_per_jtag/uz_per_jtag

.. toctree::
    :maxdepth: 1
    :caption: Deskbench

    deskbench/deskbench