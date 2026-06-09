=========================
Sawtooth wave with offset
=========================

.. doxygenfunction:: uz_wavegen_sawtooth_sample_with_offset

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to sawtooth wave generator with offset

  #include "uz_wavegen.h"
  int main(void) {
     float amplitude = -5.0f;
     float frequency_Hz = 10.0f;
     float offset = 1.0f;
     uz_wavegen_sawtooth_t* sawtooth = uz_wavegen_sawtooth_init();
     float output = uz_wavegen_sawtooth_sample_with_offset(sawtooth, amplitude, frequency_Hz, offset);
  }

Description
===========

This function calculates a sawtooth with specified offset.
The phase is tracked in the wavegen instance and advanced on each sample call.

.. tikz:: sawtooth wave with offset
  :align: left

  \draw [densely dotted] (0,-0.5)  -- +(6,0);
  \draw (0,0) foreach \x in {1,2,3} {-- ++(2,1) -- ++(0,-1) };
  \draw[|-|](-0.25,0)--(-0.25,1);
  \node[font=\footnotesize] at (-1.1,0.5){amplitude};
  \draw[|-|](-0.5,-0.5)--(-0.5,0);
  \node[font=\footnotesize] at (-1.1,-0.25){offset};
  \draw[|->](0,-1)--(2,-1);
  \node[font=\footnotesize] at (1,-1.5){frequency};

   


