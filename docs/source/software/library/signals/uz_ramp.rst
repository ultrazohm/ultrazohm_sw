====
Ramp
====

.. doxygentypedef:: uz_ramp_t

.. doxygenstruct:: uz_ramp_config
  :members:

.. doxygenfunction:: uz_ramp_init

.. doxygenfunction:: uz_ramp

.. doxygenfunction:: uz_ramp_set_to_value_instant

.. doxygenfunction:: uz_ramp_reset

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example ramp usage for a speed reference signal

  #include "uz_signals.h"

  int main(void) {
     struct uz_ramp_config config = {
        .maximum_slope_per_second = 100.0f,
        .sample_time_seconds = 0.0001f,
        .initial_value = 0.0f
     };
     uz_ramp_t *speed_reference_ramp = uz_ramp_init(config);
     float reference_value = 500.0f;
     float ramped_reference = uz_ramp(speed_reference_ramp, reference_value);
  }

Description
===========

``uz_ramp`` limits the rate of change of a signal.
On every call, the output moves linearly from the current output value towards the requested reference value.
The maximum change per call :math:`\Delta_{max}` is given by:

.. math::

    \Delta_{max} = slope_{max} \cdot T_s,

where :math:`slope_{max}` is the configured maximum slope per second, and :math:`T_s` is the sample time. 
If the remaining distance to the target is smaller than :math:`\Delta_{max}`, the output is set directly to the target value.
Otherwise, the output changes by exactly :math:`\Delta_{max}` in the direction of the target.

.. figure:: ramp/ramp01.png
   :width: 100%
   :align: center

   Result of a test scenario with an input change from 0 to 1000 with a configured slope of 100 per second.

Changing the input reference_value during execution of the ramp, this changed input becomes the new target, and the ramp 
will re-aim toward the new reference_value.

.. figure:: ramp/ramp02.png
   :width: 100%
   :align: center

   Result of the test scenario above, where during execution of the ramp a new input value of 200 is provided.

.. warning::
  When not reset by calling ``uz_ramp_reset(uz_ramp_t *self)``, the ramp will keep its last output value.
