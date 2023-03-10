.. _uz_PWM_duty_freq_detection:

=================================
PWM Dutycycle Frequency Detection
=================================

This IP core analyses a pwm input signal for measuring e.g. chip temperatures. From the Duty cycle the temperature in degree can be calculated in the software driver.
Besides the calculated temperature, the frequency, normalized PWM dutycycle, hightime and lowtime of the dutycycle are outputed.






Software driver
===============

.. doxygentypedef:: uz_PWM_duty_freq_detection_t

.. doxygenstruct:: linear_interpolation_params_t
  :members:

.. doxygenstruct:: uz_PWM_duty_freq_detection_config_t
  :members:

.. doxygenstruct:: uz_PWM_duty_freq_detection_outputs_t
  :members:

.. doxygenfunction:: uz_PWM_duty_freq_detection_update_states

User interfaces
---------------

.. doxygenfunction:: uz_PWM_duty_freq_detection_init

.. doxygenfunction:: uz_PWM_duty_freq_detection_get_outputs

Helper functions
----------------

.. doxygenfunction:: uz_PWM_duty_freq_detection_PWMdutyCycNormalized_to_DegreesCelsius


Examples
========

Example for using the ip-core with the software driver

.. code-block:: c
 :caption: Example usage

 #include "../include/uz_inverter_adapter_init.h"
 #include "xparameters.h"

  // config struct
  struct uz_PWM_duty_freq_detection_config_t config = {
      .base_address = XPAR_UZ_PWMDUTYFREQDETECTION_BASEADDR,
      .ip_clk_frequency_Hz = 100000000,
      .linear_interpolation_params.a = 162.35f,
      .linear_interpolation_params.b = 20.107f      
  };

  // output struct
  struct uz_PWM_duty_freq_detection_outputs_t outputs = {
      .PWMdutyCycNormalized = 0.0f,
      .TempDegreesCelsius = 0.0f,
      .PWMFreq = 0,
      .PWMhightime = 0,
      .PWMlowtime = 0,
  };

  // call init function
  uz_PWM_duty_freq_detection_t *pwm_duty_freq_detection_instance = uz_PWM_duty_freq_detection_init(config, outputs);

  // get output e.g. in ISR:
  outputs = uz_PWM_duty_freq_detection_get_outputs(pwm_duty_freq_detection_instance);




