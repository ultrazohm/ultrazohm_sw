.. _uz_spwm:

====================
DutyCycle generation
====================

.. doxygenfunction:: uz_spwm_abc

.. doxygenfunction:: uz_spwm_dq

.. doxygenfunction:: uz_spwm_abc_6ph

.. doxygenfunction:: uz_spwm_dq_6ph


Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to generate PWM values for three-phase systems. 

  int main(void) {
     float V_dc_volts = 24.0f;
     float theta_el_rad = 1.0f;
     struct uz_3ph_abc_t UVW = {.a = 0.0f, .b = -0.866f, .c = 0.866f};
     struct uz_DutyCycle_t output = uz_spwm_abc(UVW, V_dc_volts);
     struct uz_3ph_dq_t dq = {.d = 1.0f, .q = -0.866f, .zero = 0.0f};
     output = uz_spwm_dq(dq, V_dc_volts, theta_el_rad);
  }

Description
===========

Duty cycle generation for three- and six-phase systems.
Input is possible with abc values and dq values if electric rotor angle is provided.
The generated PWM-signals can be directly fed to the :ref:`PWM IP-Core <ipCore_pwm>`.
The generation uses the continuous sinusoidal PWM (SPWM) modulation and is scaled to a duty cycle from 0.0 to 1.0. 
It has an output limitation, so that the values never exceed the given range.
The more advanced functions for duty cycle generation can be found in :ref:`uz_spacevectormodulation`.