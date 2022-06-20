.. _uz_pwm_ss_2l:

=====================
PWM and SS Control V4
=====================

The IP core implements a modulation and switching state control unit that generates control signals for power electronic applications for three phase legs of two-level inverter topologies.
Interlock and dead-time functionalities are not part of this IP core and are handled in a subsequent IP core.
If less than three phase legs are used, unused phase legs can be set to a tristate mode, where neither the top nor the bottom switch of the phase leg are active.
For higher phase numbers, multiple instances of this module can be used in the FPGA, each containing its own up-down counter.
For synchronizing multiple instances, the counter can be fed to subsequent instances.
Furthermore, an interleaved operation is possible.
Every half-bridge can be shifted individually.
These features are the only difference between versions V3 and V4.
In the standard block design of the ultrazohm_sw framework, 4 synchronized instances of this ip core are present with respective software driver instances for controlling up to 12 half-bridge phase legs.
 
The IP core provides two general modes of operation.

- Pulse width modulator mode (PWM)
- Direct control of the switching states (SS)

In PWM mode one can choose from two different sources of reference values (duty cycles).

- Reference values can be sent from the processing system via AXI to the IP core.
- Reference values can be provided directly from within the FPGA.

The PWM mode uses a 20bit up-down counter and has been tested for switching frequencies of 100 Hz to 100 kHz.
For operation especially with lower PWM frequencies one has to adapt the bitsize of the counter.

The IP core uses asymmetrical regular sampling for generation of the pulses:

.. figure:: asymmregsampling.png
   :width: 400
   :align: center

   Asymmetric regular sampling according to Grahame Holmes: Pulse Width Modulation For Power Converters

The triangle signal respectively DutyCycle of each half-bridge can be individually shifted depending on the input. The following variables in the ``config`` -struct are used for this.

* triangle_shift_HB1
* triangle_shift_HB2
* triangle_shift_HB3

The input is fixed to ``0`` till ``1``. Whilst ``0`` represents no shift at all, ``1`` represents a shift by an entire period. 
E.g. with a PWM-frequency of :math:`f=10kHz` and :math:`T=100µs` the input ``triangle_shift_HB2 = 0.1f`` would shift the second half-bridge by :math:`10µs`. 

.. figure:: Shift_example.png
   :align: center

   Shift of HB2 by ``triangle_shift_HB2 = 0.1f`` @10kHz.

IP-Core Hardware
================

.. figure:: ip_core_overview.png
   :width: 800
   :align: center

   Test bench of PWM and SS Control IP-Core

.. figure:: phase_leg.png
   :width: 800
   :align: center

   PWM implementation of one phase leg

Example usage
=============

Vivado
******

- One instance:

.. figure:: vivado_example.png
   :width: 500
   :align: center

   Example implementation in the block design

For further instances, add the IP core to your design as many times as needed and connect them accordingly.
For synchronization of instances, feed the triangle_out port of the first instance into the triangle_in port of one or several subsequent instances:

.. figure:: vivado_2instances.png
   :width: 600
   :align: center

   Example implementation in the block design with two synchronized instances

A flag for 1 cycle is active at the counter maximum and minimum value for triggering subsequent blocks or interrupts.

Vitis
*****

- The software driver is called "uz_PWM_SS_2L"
- Each instance has to be configured by a config struct


.. note::
   * If at least two synchronized ip cores are present, both have to be configured with ``use_external_counter = enable`` 
     and connected the way shown above for correct synchronization.

.. code-block:: c

    struct uz_PWM_SS_2L_config_t config_1 = {
            .base_address= XPAR_GATES_PWM_AND_SS_CONTROL_V_0_BASEADDR,
            .ip_clk_frequency_Hz=100000000,
            .Tristate_HB1 = false,
            .Tristate_HB2 = false,
            .Tristate_HB3 = false,
            .min_pulse_width = 0.01f,
            .PWM_freq_Hz = UZ_PWM_FREQUENCY,
            .PWM_mode = normalized_input_via_AXI,
            .PWM_en = true,
            .use_external_counter = true,
            .init_dutyCyc_HB1 = 0.0f,
            .init_dutyCyc_HB2 = 0.0f,
            .init_dutyCyc_HB3 = 0.0f,
            .triangle_shift_HB1 = 0.0f,
            .triangle_shift_HB2 = 0.0f,
            .triangle_shift_HB3 = 0.0f
    };

An instance has to be initialized first and then configured:

.. code-block:: c

    PWM_SS_2L_instance_1 = uz_PWM_SS_2L_init(config_1);

After that it can be used in the application. For easy setting of the duty cycles, use the ``uz_PWM_SS2L_set_duty_cycle`` function.

Driver reference
================

.. doxygentypedef:: uz_PWM_SS_2L_t

.. doxygenenum:: uz_PWM_SS_2L_PWM_mode

.. doxygenstruct:: uz_PWM_SS_2L_config_t
  :members:

.. doxygenfunction:: uz_PWM_SS_2L_init

.. doxygenfunction:: uz_PWM_SS_2L_set_duty_cycle

.. doxygenfunction:: uz_PWM_SS_2L_set_tristate

.. doxygenfunction:: uz_PWM_SS_2L_set_PWM_mode

.. doxygenfunction:: uz_PWM_SS_2L_set_triangle_shift
