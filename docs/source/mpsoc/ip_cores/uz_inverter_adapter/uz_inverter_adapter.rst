.. _uz_inverter_adapter:

================
Inverter Adapter
================

This IP core provides a well defined and highly sophisitcated interface for inverter adapter boards for the UltraZohm (e.g. uz_d_gan_inverter). 
It provides many useful features:

   - 6 gate signal outputs
   - 1 gate enable signal output
   - 6 over current (OC) input signals
   - 6 fault (FAULT) input signals
   - 6  pwm input signals for measuring e.g. chip temperatures.
     Duty cycle is calculated to degrees celsius in software driver
   - 4 diagnostic input signals (e.g. power good or signal valid of current amplifiers)

Hardware Interface Definition
=============================

Usage of the IP-core requires a defined pin mapping on the respective inverter adapter board, as shown in the table below.

.. _ipCore_uz_inverter_adapter_interfaces:

.. csv-table:: Defined pin mapping of adapter board
   :file: uz_inverter_adapter_pin_mapping.csv
   :widths: 40 40 60 50 50 
   :header-rows: 1

Organization of the sources
===========================

.. _folder_structure_picture:

.. figure:: img/sources.png
   :width: 300
   :align: center

   Folder structure of the sources



- ``constraint_files`` contains ready to use Vivado constraint files for usage of the adapter board interface in any digital slot D1..D4
- ``driver_ip_core`` contains the ip-core that the user interfaces with via software driver
- ``interface_definition`` contains the Vivado interface definition using the pin names from the constraint files
- ``mapping_ip_core`` contains the ip-core that maps and organizes a whole bunch of signals from the adapter board
- ``temperature_calculation`` contains excel sheets for determination of the linear interpolation equation to get temperatures in degrees celsius from a duty cycle value of a PWM signal.
  The parameters of the equation depend on the circuit design and/or the used power electronic switch and have to be determined by the adapter board developer carefully

Example Usage
=============

Vivado Block Design
-------------------

Vivado Interface
----------------

Constraints
-----------

CPLD program
------------

Keep in mind, that a proper CPLD program for this interface and respective adapter boards is required. It can be found in the ``cpld_lattice`` repository 
under ``uz_d_3ph_inverter``

Software driver
---------------

- Create hierarchy
- The trigger source is ``Interrupt_2L_min``: the define ``INTERRUPT_ISR_SOURCE_USER_CHOICE`` is set to ``1U`` in ``uz_global_configuration.h``
- The trigger ratio is set to 5 (100 kHz/20 kHz = 5): the define ``INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE`` is set to ``5U`` in ``uz_global_configuration.h``

.. code-block:: c
   :caption: Settings in uz_global_configuration.h for the example

   #define INTERRUPT_ISR_SOURCE_USER_CHOICE        1U
   #define INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE  5U
   
   #define UZ_D5_INCREMENTAL_ENCODER_RESOLUTION    5000.0f
   #define UZ_D5_MOTOR_POLE_PAIR_NUMBER            4.0f
   #define UZ_PWM_FREQUENCY                        10.0e3f

These settings result in the behavior depicted in :numref:`example_trigger_picture` (ADC interrupt in the upper subplot, interrupt of R5 in the lower subplot):

.. warning::
   * Trigger ratios other than ``1`` were only tested with trigger source ``Interrupt_2L_min``
   * Especially when using trigger sources with two ADC trigger events (e.g. ``Interrupt_2L_max_min``), the user has to take care of the resulting ADC/ISR trigger ratio

Reference
=========

.. doxygentypedef:: uz_inverter_adapter_t

.. doxygenstruct:: linear_interpolation_params_t
  :members:

.. doxygenstruct:: uz_inverter_adapter_config_t
  :members:

.. doxygenstruct:: uz_inverter_adapter_outputs_t
  :members:

.. doxygenfunction:: uz_inverter_adapter_init

.. doxygenfunction:: uz_inverter_adapter_update_states

.. doxygenfunction:: uz_inverter_adapter_get_outputs

