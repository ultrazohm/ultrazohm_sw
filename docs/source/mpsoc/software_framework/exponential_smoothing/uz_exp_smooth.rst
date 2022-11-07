.. _uz_exp_smooth:
==============================
Exponential smoothing filter
==============================


Description
===========

Implemented is a simple exponential smoothing filter, which has a infinite impulse response.
The implementation is equivalent to the existing IIR-Filter (see :ref:`IIR filter`). The IIR-Filter calculate the smoothing factor with a cutoff frequency and a RC-element.
The basic implementation of the exponential smoothing filter is given by the formula[[#exponentialsmooth]_]:

.. math::    
    y_0 = x_0

.. math::  
    y[i] = \alpha \cdot y[i] + (1-\alpha) \cdot (y[i-1]^*)

.. doxygentypedef:: uz_EXP_SMOOTH_t

.. doxygenfunction:: uz_EXP_SMOOTH_init
  
.. doxygenfunction:: uz_EXP_SMOOTH_sample
Example
=======

.. code-block:: c
  :linenos:
  :caption: Example to init and sample the filter

  #include "uz_signals.h"
  int main(void) {
     float alpha = 0.3f; //smoothing factor defined by user
     uz_EXP_SMOOTH_t* test_instance = uz_EXP_SMOOTH_init(alpha);
     float unfiltered_signal = 20.0f;
     float filtered_signal = 10.0f;
     filtered_signal = uz_EXP_SMOOTH_sample(test_instance, unfiltered_signal);
  }

.. note :: The current implementation of the filter uses the first value from the unfiltered signal as the first output.


Sources
=======

.. [#exponentialsmooth] `Wikipedia, "Exponential smoothing", <https://en.wikipedia.org/wiki/Exponential_smoothing>`_