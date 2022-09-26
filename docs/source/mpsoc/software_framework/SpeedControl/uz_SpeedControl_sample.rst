.. _uz_SpeedControl_sample:

===============
Sample function
===============

.. doxygenfunction:: uz_SpeedControl_sample

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to calculate the SpeedControl output. SpeedControl-Instance via :ref:`init-function <uz_SpeedControl_init>`

  int main(void) {
     float omega_m_rad_per_sec = 1.5f;
     float n_ref_rpm = 500.0f;
     float torque_out = uz_SpeedControl_sample(instance, omega_m_rad_per_sec, n_ref_rpm);
  }

Description
===========

.. warning::

  The sample function has to be called with the same sample time as specified in the ``samplingTime_sec`` member of the :ref:`configuration struct <uz_piController_config>`.

Calculates the reference speed into angular frequency and calculates the latest sample of the n-PI-Controller. Output is a reference torque.
Furthermore, an external clamping signal can be set via a dedicated :ref:`set function <uz_SpeedControl_set_ext_clamping>`.