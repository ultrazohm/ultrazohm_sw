.. _uz_FOC_DutyCycle:

====================
DutyCycle generation
====================

.. doxygenstruct:: uz_DutyCycle_t
  :members:

.. doxygenfunction:: uz_FOC_generate_DutyCycles

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to generate PWM values from a UVW-three-phase system. 

  int main(void) {
     float V_dc_volts = 24.0f;
     struct uz_3ph_abc_t UVW = {.a = 0.0f, .b = -0.866f, .c = 0.866f};
     struct uz_DutyCycle_t output = uz_FOC_generate_DutyCycles(UVW, V_dc_volts);
  }

Description
===========

Generates the three phase DutyCycle of one sample from a UVW-signal. 
The generated PWM-signals can be directly fed to the :ref:`PWM IP-Core <ipCore_pwm>`.
The generation uses the continuous sinusoidal PWM (SPWM) modulation and is scaled to a DutyCycle from 0.0 to 1.0. 
It has an output limitation, so that the values never exceed the given range.