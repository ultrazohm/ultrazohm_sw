.. _uz_pwm_ss_2l:

=====================
PWM and SS Control V4
=====================

The IP core implements a modulation and switching state control unit that generates control signals for power electronic applications for 
three phase legs of two-level inverter topologies. Interlock and dead-time functionalities are not part of this IP core and are handled in a subsequent IP core.
If less than three phase legs are used, unused phase legs can be set to a tristate mode, where neither the top nor the bottom switch of the phase leg are active.
For higher phase numbers, multiple instances of this module can be used in the FPGA, each containing its own up-down counter. For synchronizing multiple instances, 
the counter can be fed to subsequent instances. This feature is the only difference between versions V3 and V4.
 
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
   :width: 800
   :align: center

   Example implementation in the block design

For further instances, add the IP core to your design as many times as needed and connect them accordingly.
For synchronization of instances, feed the count_out port of the first instance into the count_in port of one or several subsequent instances:

.. figure:: vivado_2instances.png
   :width: 400
   :align: center

   Example implementation in the block design with two synchronized instances

A flag for 1 cycle is active at the counter maximum and minimum value for triggering subsequent blocks or interrupts.

Vitis
*****

- The software driver is called "uz_PWM_SS_2L"
- Each instance has to be configured by a config struct:

.. code-block:: c

    struct uz_PWM_SS_2L_config_t config_1 = {
            .base_address= XPAR_GATES_PWM_AND_SS_CONTROL_V_0_BASEADDR,
            .ip_clk_frequency_Hz=100e6,
            .Tristate_HB1 = 0,
            .Tristate_HB2 = 0,
            .Tristate_HB3 = 0,
            .min_pulse_width = 0.01,
            .PWM_freq_Hz = 10e3,
            .PWM_mode = 0,
            .PWM_en = 1,
            .CntExtSrc = 0,
            .init_dutyCyc_A = 0.0,
            .init_dutyCyc_B = 0.0,
            .init_dutyCyc_C = 0.0
    };

An instance has to be initialized first and then configured:

.. code-block:: c

    PWM_SS_2L_instance_1 = uz_PWM_SS_2L_init(config_1);
    uz_PWM_SS_2L_set_config(PWM_SS_2L_instance_1);

After that it can be used in the application. For easy setting of the duty cycles, use the ``uz_PWM_SS2L_set_duty_cycle`` function.

Driver reference
================

.. doxygentypedef:: uz_PWM_SS_2L_t

.. doxygenstruct:: uz_PWM_SS_2L_config_t
  :members:

.. doxygenfunction:: uz_PWM_SS_2L_init

.. doxygenfunction:: uz_PWM_SS_2L_set_duty_cycle

.. doxygenfunction:: uz_PWM_SS_2L_set_tristate

.. doxygenfunction:: uz_PWM_SS_2L_set_PWM_mode
