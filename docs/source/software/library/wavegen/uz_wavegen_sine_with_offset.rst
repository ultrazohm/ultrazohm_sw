=====================
Sine wave with offset
=====================

.. doxygenfunction:: uz_wavegen_sine_sample_with_offset

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to sine wave generator with offset

  #include "uz_wavegen.h"
  int main(void) {
     float amplitude = 6.0f;
     float frequency_Hz = 5.0f;
     float offset = -5.0f;
     uz_wavegen_sine_t* sine = uz_wavegen_sine_init();
     float output = uz_wavegen_sine_sample_with_offset(sine, amplitude, frequency_Hz, offset);
  }

Description
===========

This function calculates a sine wave with :math:`y=sin(2 \pi f \cdot t) + x` where :math:`x` is the offset.
The phase is tracked in the wavegen instance and advanced on each sample call.

.. tikz:: sine wave with offset
  :align: left

  \draw [densely dotted] (0,-0.5)  -- +(6,0);
  \draw plot[domain=0:6,variable=\x,samples=51,smooth] (\x,{sin(deg(\x*pi))});
  \draw[|-|](-0.25,0)--(-0.25,1);
  \node[font=\footnotesize] at (-1.1,0.5){amplitude};
  \draw[|-|](-0.5,-0.5)--(-0.5,0);
  \node[font=\footnotesize] at (-1.1,-0.25){offset};
  \draw[|->](0,-1.5)--(2,-1.5);
  \node[font=\footnotesize] at (1,-2){frequency};

   


