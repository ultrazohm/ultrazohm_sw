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
     float U_zk_Volts = 24.0f;
     struct uz_UVW_t UVW = {.U = 0.0f, .V = -0.866f, .W = 0.866f};
     struct uz_DutyCycle_t output = uz_FOC_generate_DutyCycles(UVW, U_zk_Volts);
  }

Description
===========

Generates the three phase DutyCycle of one sample from a UVW-signal. 
The generated PWM-signals can be directly fed to the :ref:`PWM IP-Core <ipCore_pwm>`.
The generation uses the continuous sinusoidal PWM (SPWM) modulation and is scaled to a DutyCycle from 0.0 to 1.0. 
It has an output limitation, so that the values never exceed the given range.