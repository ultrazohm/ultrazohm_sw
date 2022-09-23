.. _uz_CurrentControl_sample:

===============
Sample function
===============

.. doxygenfunction:: uz_CurrentControl_sample

.. doxygenfunction:: uz_CurrentControl_sample_abc

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to calculate the CurrentControl output. CurrentControl-Instance via :ref:`init-function <uz_CurrentControl_init>`

  int main(void) {
     float V_dc_volts = 24.0f;
     float omega_el_rad_per_sec = 125.1f;
     float theta_el_rad = 1.2f;
     struct uz_3ph_dq_t i_actual_Ampere = {.d = 1.0f, .q = 2.0f, .zero = 0.0f};
     struct uz_3ph_dq_t i_reference_Ampere = {.d = 1.0f, .q = 2.0f, .zero = 0.0f};
     struct uz_3ph_dq_t v_dq_Volts = uz_CurrentControl_sample(CurrentControl_instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
     //Alternatively the sample function can output the UVW-values
     struct uz_3ph_abc_t v_abc_Volts = uz_CurrentControl_sample_abc(CurrentControl_instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec, theta_el_rad);
  }

Description
===========

Calculates one sample of the CurrentControl.

.. note::

  Either use the ``uz_CurrentControl_sample`` function to get the output voltages in the dq0-frame or use the ``uz_CurrentControl_sample_UVW`` function to get the output voltages in the UVW-system. 

.. warning::

  The sample function has to be called with the same sample time as specified in the ``samplingTime_sec`` member of the :ref:`PI-Controller configuration struct <uz_piController_config>`.

