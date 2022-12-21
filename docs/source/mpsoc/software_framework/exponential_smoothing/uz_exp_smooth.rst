.. _uz_exp_smooth:

==============================
Exponential smoothing filter
==============================

Implemented is a simple exponential smoothing filter, which has a infinite impulse response.
The implementation is equivalent to the IIR-Filter (see :ref:`IIR filter <uz_IIR_filter>`).
The IIR-Filter calculates the smoothing factor with a cutoff frequency and a RC-element.
The exponential smoothing filter uses a fixed smoothing factor, the basic implementation is given by the formula[[#exponentialsmooth]_]:

.. math::    

    y_0 &= x_0 \\
    y[i] &= \alpha \cdot y[i] + (1-\alpha) \cdot y[i-1]

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example to init and sample the filter

  #include "uz_signals.h"
  int main(void) {
     float alpha = 0.3f; //smoothing factor defined by user
     uz_exp_smooth_t* test_instance = uz_exp_smooth_init(alpha);
     float unfiltered_signal = 20.0f;
     float filtered_signal = 10.0f;
     filtered_signal = uz_exp_smooth_sample(test_instance, unfiltered_signal);
  }

.. note :: The implementation of the filter uses the first value from the unfiltered signal as the first output (first sample).

Reference
=========

.. doxygentypedef:: uz_exp_smooth_t

.. doxygenfunction:: uz_exp_smooth_init
  
.. doxygenfunction:: uz_exp_smooth_sample


Sources
=======

.. [#exponentialsmooth] `Wikipedia, "Exponential smoothing", <https://en.wikipedia.org/wiki/Exponential_smoothing>`_