.. _uz_flux_maps_measuerement:

======================
Flux maps measurement
======================

.. tikz:: measurement procedure
   :libs: shapes, arrows, positioning, calc,fit, backgrounds, shadows
   :include: meas_process.tex
   :align: center
   :xscale: 70

.. _udq_2500rpm:

.. figure:: udq_2500rpm.svg
   :align: center
   :width: 100%

   test caption

:numref:`udq_2500rpm` shows result from measurement

.. math::

   \Psi_d = \frac{v_q - R_s i_q}{\omega_{el}} \\
   \Psi_q = \frac{v_d - R_s i_d}{-\omega_{el}}


.. _psidq_3000rpm:

.. figure:: psidq_3000rpm.svg
   :align: center
   :width: 100%

   test caption two

:numref:`psidq_3000rpm` shows result from measurement

Setup
=====


Configuration
-------------

In order to configure the measurement procedure, multiple configuration structs have to be initialized.



Example
^^^^^^^
    
.. code-block:: c
  :linenos:
  :caption: Example to initialize the configuration struct
    
   #include "uz/uz_ParameterID_rc/uz_ParameterID_rc.h"
   int main(void)
   {
      int status = UZ_SUCCESS;

      const struct uz_parameterID_rc_config_t rc_meas_config = {
         .abs_id_max_Amps = 6.0f,
         .abs_iq_max_Amps = 6.0f,
         .n_start_rpm = 500.0f,
         .n_stop_rpm = 3000.0f,
         .id_steps = 6U,
         .iq_steps = 6U,
         .n_steps = 5U,
         .check_temp = 1
         };


Init function
-------------

.. doxygenfunction:: _uz_parameterID_rc_init

Example
^^^^^^^



Description
^^^^^^^^^^^