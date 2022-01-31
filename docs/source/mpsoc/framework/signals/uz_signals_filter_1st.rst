================
1st order filter
================

.. doxygentypedef:: uz_Filter_1st_t

.. doxygenenum:: Filter_selection 

.. doxygenstruct:: uz_Filter_1st_config
  :members:

.. doxygenfunction:: uz_Filter_1st_init
  
.. doxygenfunction:: uz_signals_Filter_1st_sample


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
     float filtered_signal = uz_signals_Filter_1st_sample(test_instance, unfiltered_signal);
  }

Description
===========

Placeholder, done according to wiki.



   


