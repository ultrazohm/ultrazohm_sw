=============
Sawtooth wave
=============

.. c:type:: uz_wavegen_sawtooth_t

.. doxygenfunction:: uz_wavegen_sawtooth_sample

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to sawtooth wave generator

  #include "uz_wavegen.h"
  int main(void) {
     float amplitude = 10.0f;
     float frequency_Hz = 5.0f;
     uz_wavegen_sawtooth_t* sawtooth = uz_wavegen_sawtooth_init();
     float output = uz_wavegen_sawtooth_sample(sawtooth, amplitude, frequency_Hz);
  }

Description
===========

This function calculates a sawtooth.
The phase is tracked in the wavegen instance and advanced on each sample call.

.. tikz:: sawtooth wave
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw (0,0) foreach \x in {1,2,3} {-- ++(2,1) -- ++(0,-1) };
  \draw[|-|](-0.25,0)--(-0.25,1);
  \node[font=\footnotesize] at (-1.1,0.5){amplitude};
  \draw[|->](0,-0.5)--(2,-0.5);
  \node[font=\footnotesize] at (1,-1){frequency};

   


