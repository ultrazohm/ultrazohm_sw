=========
Sine wave
=========

.. doxygenfunction:: uz_wavegen_sine

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to sine wave generator

  #include "uz_wavegen.h"
  int main(void) {
     float amplitude = 8.0f;
     float frequency_Hz = 10.0f;
     float duty_cycle = 0.5f;
     float output = uz_wavegen_pulse(amplitude, frequency_Hz, duty_cycle);
  }

Description
===========

This function calculates a sine wave with :math:`y=sin(2 \pi f \cdot t)` where :math:`t` is the global system time.

.. tikz:: sine wave
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw plot[domain=0:6,variable=\x,samples=51,smooth] (\x,{sin(deg(\x*pi))});
  \draw[|-|](-0.25,0)--(-0.25,1);
  \node[font=\footnotesize] at (-1.1,0.5){amplitude};
  \draw[|->](0,-1.5)--(2,-1.5);
  \node[font=\footnotesize] at (1,-2){frequency};
   


