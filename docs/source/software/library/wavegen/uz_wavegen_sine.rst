=========
Sine wave
=========

.. c:type:: uz_wavegen_sine_t

.. doxygenfunction:: uz_wavegen_sine_sample

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to sine wave generator

  #include "uz_wavegen.h"
  int main(void) {
     float amplitude = 8.0f;
     float frequency_Hz = 10.0f;
     uz_wavegen_sine_t* sine = uz_wavegen_sine_init();
     float output = uz_wavegen_sine_sample(sine, amplitude, frequency_Hz);
  }

Description
===========

This function calculates a sine wave with :math:`y=sin(2 \pi f \cdot t)`.
The phase is tracked in the wavegen instance and advanced on each sample call.

.. tikz:: sine wave
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw plot[domain=0:6,variable=\x,samples=51,smooth] (\x,{sin(deg(\x*pi))});
  \draw[|-|](-0.25,0)--(-0.25,1);
  \node[font=\footnotesize] at (-1.1,0.5){amplitude};
  \draw[|->](0,-1.5)--(2,-1.5);
  \node[font=\footnotesize] at (1,-2){frequency};
   


