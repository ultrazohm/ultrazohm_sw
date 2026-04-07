=============================
Threshold evaluation function
=============================

.. doxygenfunction:: uz_signals_threshold_Evaluation

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call limit the input (saturation)

  #include "uz_signals.h"
  int main(void) {
     float input = 2.0f;
     float threshold = 0.5f;
     float output = uz_signals_threshold_Evaluation(input, threshold);
  }

Description
===========

Evaluates the input.
Sets the output to one if the input is bigger than the threshold value otherwise the output is zero.


   


