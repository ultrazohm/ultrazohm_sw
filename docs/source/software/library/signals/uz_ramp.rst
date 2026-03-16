=======
uz_ramp
=======

.. doxygentypedef:: uz_ramp_t

.. doxygenstruct:: uz_ramp_config
  :members:

.. doxygenfunction:: uz_ramp_init

.. doxygenfunction:: uz_ramp

.. doxygenfunction:: uz_ramp_reset

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example ramp usage for a reference signal

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
The maximum change per call is given by:

.. math::

    \Delta_{max} = slope_{max} \cdot T_s

If the remaining distance to the target is smaller than :math:`\Delta_{max}`, the output is set directly to the target value.
Otherwise, the output changes by exactly :math:`\Delta_{max}` in the direction of the target.
