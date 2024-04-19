.. _uz_IIR_filter:

==========
IIR filter
==========

.. doxygentypedef:: uz_IIR_Filter_t

.. doxygenenum:: uz_IIR_Filter_selection 

.. doxygenstruct:: uz_IIR_Filter_config
  :members:

.. doxygenfunction:: uz_signals_IIR_Filter_init
  
.. doxygenfunction:: uz_signals_IIR_Filter_sample

.. doxygenfunction:: uz_signals_IIR_Filter_reverse_sample

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example to init and sample the filter

  #include "uz_signals.h"
  int main(void) {
     struct uz_IIR_Filter_config config = {.selection = LowPass_first_order, .cutoff_frequency_Hz = 200.0f, .sample_frequency_Hz = 20000.0f};
     uz_IIR_Filter_t* test_instance = uz_signals_IIR_Filter_init(config);
     float unfiltered_signal = 20.0f;
     float filtered_signal = 10.0f;
     filtered_signal = uz_signals_IIR_Filter_sample(test_instance, unfiltered_signal);
     unfiltered_signal = uz_signals_IIR_Filter_reverse_sample(test_instance, filtered_signal);
  }

Description
===========

Implemented is either a simple IIR-lowpass or highpass filter of the first order. 
The reverse functions are intended, for when a filter has been previously applied to a signal and should be removed again.

For the lowpass filter [[#lowpass]_][[#lowpass2]_]:

.. math:: 

    \alpha = \frac{dt}{dt + RC}

.. math::    

    y[i] = y[i-1] + \alpha \cdot (x[i] - y[i-1])

And for the lowpass-reverse filter:

.. math:: 

    y[i] = \frac{x[i] -x[i-1]}{\alpha} + x[i-1]

For the highpass filter [[#highpass]_]:

.. math:: 

    \alpha = \frac{RC}{dt + RC}

.. math:: 

    y[i] = \alpha \cdot (y[i-1] + x[i] - x[i-1])
   
And for the highpass-reverse filter:

.. math:: 

    y[i] = \frac{x[i]}{\alpha} + y[i-1] - x[i-1]

Sources
=======

.. [#lowpass] `Weimich, "Simple Low Pass IIR Filter Implementation Using the C Language", 2020, <https://www.dsp-weimich.com/digital-signal-processing/iir-first-order-digital-filter/>`_
.. [#lowpass2] `Wikipedia, "Low-pass filter", <https://en.wikipedia.org/wiki/Low-pass_filter>`_
.. [#highpass] `Wikipedia, "High-pass filter", <https://en.wikipedia.org/wiki/High-pass_filter>`_