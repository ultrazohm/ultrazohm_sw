.. _uz_moving_average:

==============
Moving average
==============

This module implements a moving average filter which calculates the unweighted mean of the previous :math:`k` data points (sampling window).
The number of data points :math:`k` is adjustable during run-time with a maximum filter length which is determined during initialization of the filter.

.. math::

  \frac{1}{k}\sum^n_{i=n-k+1} p_i = \frac{p_{n-k+1} + p_{p-k+2} + ... + p_n}{k}

with the data points :math:`p` and the number of entries in the ring buffer :math:`n` [[#wiki]_]. 

To speed up the calculation and prevent looping through every member of the circular buffer a different approach is used.

.. math::

  \frac{1}{k}\sum^{n+1}_{i=n-k+2} p_i = sum_{k,prev} + \frac{1}{k}(p_{n+1} - p_{n-k+1})

Thus, for each function call the oldest value in the circular buffer (``circularBuffer`` array) will be deleted and the newest one will be added. 

Setup
=====

Configuration
-------------

.. doxygentypedef:: uz_movingAverageFilter_t

.. doxygenstruct:: uz_movingAverageFilter_config
  :members:

.. doxygenfunction:: uz_movingAverageFilter_init

The ``circularBuffer`` array has to be initialized by using the UltraZohm :ref:`uz_array` module.
The length of the array will automatically be the maximum possible length of the filter. 
I.e. if the array has 50 entries, the filter length can't be higher than 50, otherwise an assertion triggers. 
However, it is possible for the filter length to be lower than the maximum length. 

.. code-block:: c
  :linenos:
  :caption: Example to initialize the configuration struct
    
  #include "uz/uz_movingAverageFilter/uz_movingAverageFilter.h"
  int main(void) {
     struct uz_movingAverageFilter_config config_SMA = {
        .filterLength = 30U
     };
     float data [50] = {0};
     uz_array_float_t circularBuffer = {
        .length = UZ_ARRAY_SIZE(data),
        .data = &data[0]
     };
  }

Init function
-------------

During the initialization the config struct as well as the ``circularBuffer`` array have to be function arguments of the init function. 

.. code-block:: c
  :linenos:
  :caption: Example function call to init the movingAverageFilter instance.

  int main(void) {
     uz_movingAverageFilter_t* SMA_instance = uz_movingAverageFilter_init(config_SMA, circularBuffer);
  }

.. warning:: Each instance of the moving average filter requires it's own ``circularBuffer`` array!

Example of initialization for two independent moving average filters:

.. code-block:: c
  :linenos:
  :caption: Example function call to init the movingAverageFilter instance.

  #include "uz/uz_movingAverageFilter/uz_movingAverageFilter.h"
  int main(void) {
     float data_1 [50] = {0};
     uz_array_float_t circularBuffer_1 = {
        .length = UZ_ARRAY_SIZE(data_1),
        .data = &data_1[0]
     };

     float data_2 [20] = {0};
     uz_array_float_t circularBuffer_2 = {
        .length = UZ_ARRAY_SIZE(data_2),
        .data = &data_2[0]
     };
     
     struct uz_movingAverageFilter_config config_SMA_1 = {
        .filterLength = 30U
     };

     struct uz_movingAverageFilter_config config_SMA_2 = {
        .filterLength = 20U
     };

     uz_movingAverageFilter_t* SMA_instance_1 = uz_movingAverageFilter_init(config_SMA_1, circularBuffer_1);
     uz_movingAverageFilter_t* SMA_instance_2 = uz_movingAverageFilter_init(config_SMA_2, circularBuffer_2);
  }


Sample-functions
================

Two versions are implemented: 

  * .. doxygenfunction:: uz_movingAverageFilter_sample

  * .. doxygenfunction:: uz_movingAverageFilter_sample_variable_length

.. code-block:: c
  :linenos:
  :caption: Example function call

  int main(void) {
    float sample = 23.4f;
     float output_fixed_length = uz_movingAverageFilter_sample(SMA_instance, sample);
     float output_variable_length = uz_movingAverageFilter_sample_variable_length(SMA_instance, sample);
  }

Set filter length
=================

.. doxygenfunction:: uz_movingAverageFilter_set_filterLength

Changes the filter length to the input value. 
Filter length has to be equal or lower to the MAX_LENGTH and larger than 0.
Otherwise an assertion triggers.

.. code-block:: c
  :linenos:
  :caption: Example function call to reset the movingAverageFilter instance.

  int main(void) {
     uint32_t new_filter_length = 5U;
     uz_movingAverageFilter_set_filterLength(SMA_instance, new_filter_length);
  }

Reset
=====

Resets the movingAverageFilter module. All elements of the circularBuffer will be reset to 0.0f.

.. code-block:: c
  :linenos:
  :caption: Example function call to reset the movingAverageFilter instance.

  int main(void) {
     uz_movingAverageFilter_reset(SMA_instance);
  }



Sources
=======

.. [#wiki] `Moving average, Wikipedia <https://en.wikipedia.org/wiki/Moving_average>`_
