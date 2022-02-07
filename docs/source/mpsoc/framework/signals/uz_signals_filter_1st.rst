================
1st order filter
================

.. doxygentypedef:: uz_Filter_1st_t

.. doxygenenum:: Filter_selection 

.. doxygenstruct:: uz_Filter_1st_config
  :members:

.. doxygenfunction:: uz_Filter_1st_init
  
.. doxygenfunction:: uz_signals_Filter_1st_sample

.. doxygenfunction:: uz_signals_Filter_1st_reverse_sample

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example to init and sample the filter

  #include "uz_signals.h"
  int main(void) {
     struct uz_Filter_1st_config config = {.selection = LowPass, cutoff_frequency_Hz = 200.0f, sample_frequency_Hz = 20000.0f};
     uz_Filter_1st_t* test_instance = uz_Filter_1st_init(config);
     float unfiltered_signal = 20.0f;
     float filtered_signal = 10.0f;
     filtered_signal = uz_signals_Filter_1st_sample(test_instance, unfiltered_signal);
     unfiltered_signal = uz_signals_Filter_1st_reverse_sample(test_instance, filtered_signal);
  }

Description
===========

Implemented is either a simple IIR-lowpass or highpass filter of the first order.

For the lowpass filter:

.. math:: 

    \alpha &= \frac{dt}{dt + RC}

    y[i] &= y[i-1] + \alpha \cdot (x[i] - y[i-1])

And for the lowpass-reverse filter:

.. math:: 

    y[i] = \frac{x[i] -x[i-1]}{\alpha} + x[i-1]

For the highpass filter:

.. math:: 

    \alpha &= \frac{RC}{dt + RC}

    y[i] &= \alpha \cdot (y[i-1] + x[i] - x[i-1])
   
And for the highpass-reverse filter:

.. math:: 

    y[i] = \frac{x[i]}{\alpha} + y[i-1] - x[i-1]

