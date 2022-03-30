.. _default_vivado_project:

Default Vivado project
======================

The default Vivado project uses vendor IP-Cores as well as IP-Cores from the Ultrazohm repository (:ref:`ip_cores`) to provide a starting point for the users.
It is located in ``ultrazohm_sw/vivado/project/ultrazohm.xpr`` and can be generated using the ``build.tcl`` script (see :ref:`viavdo_build_tcl`).
:numref:`default_vivado_project_picture` shows the default project.
It is split into the following different parts:

1. Inputs ports from the digital and analog adapter cards
2. The processing system (PS) with R5 and A53.
3. ``uz_system`` with clocks, interrupts, AXI infrastructure, and IP-Cores for system functions.
4. The IP-Cores to interface the adapter cards on A1, A2, and A3.
5. The ouput ports to digital and analog adapter cards.
6. The ``uz_user`` subsystem where user specific IP-Cores should be placed.
7. The IP-Cores to interface the digital adapter cards on D1, D2, D3, D4, and D5.

.. _default_vivado_project_picture:

.. figure:: vivado_default_project.png

  Default Vivado project.

The sub-blocks (*Create hierarchy* in Vivado) provide the following functionality:

uz_system
  - *smartconnect_0* to connect AXI signals to the PS
  - *uz_enable* handles enabling the output signals as well as the data mover
  - *uz_clocks* generates 100 MHz, 50 MHz, 10 MHz clocks and reset signals
  - *timer_update_64bit* is the counter used for :ref:`systemTimeR5`
  - :ref:`uz_dataMover` transfers data from PL to PS
  - *Interrupt* controls the interrupts of the R5 in the PL (:ref:`r5_interrupts`)

uz_user
  - :ref:`AXI_testIP` to use in :ref:`how_to_create_ipcore_driver` and to test AXI communication
  - Custom IP-Cores that are specific to a user project should be added in this sub-block

uz_analog_adapter
  - A1: :ref:`Analog_LTC2311_16_v3` IP-Core, IOBUF, and inversion constant (see :ref:`vivado_build_tcl_compatibility`) for :ref:`Analog_LTC2311_16_v3` (v3 and higher) adapter card
  - A2: :ref:`Analog_LTC2311_16_v3` IP-Core, IOBUF, and inversion constant (see :ref:`vivado_build_tcl_compatibility`) for :ref:`Analog_LTC2311_16_v3` (v3 and higher) adapter card
  - A3: :ref:`Analog_LTC2311_16_v3` IP-Core, IOBUF, and inversion constant (see :ref:`vivado_build_tcl_compatibility`) for :ref:`Analog_LTC2311_16_v3` (v3 and higher) adapter card

uz_digital_adapter
  - D1: :ref:`uz_pwm_ss_2l` and :ref:`uz_interlockDeadtime2L` IP-Core (adapter card agnostic, e.g., :ref:`digitalVoltage` or :ref:`dig_optical`)
  - D2: PWM module and interlock for three level inverter (adapter card agnostic, e.g., :ref:`digitalVoltage` or :ref:`dig_optical`)
  - D3: VIO for :ref:`getting_started_vio`
  - D4: not connected, interrupt signals are directly routed to D4[7:0]
  - D5: :ref:`ipCore_incremental_encoder` IP-Core for :ref:`dig_incEncoder` adapter card