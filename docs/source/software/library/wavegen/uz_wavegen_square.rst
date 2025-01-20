===========
Square wave
===========

.. doxygenfunction:: uz_wavegen_square

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to square wave generator

  #include "uz_wavegen.h"
  int main(void) {
     float amplitude = 6.0f;
     float frequency_Hz = 20.0f;
     float duty_cycle = 0.5f;
     float output = uz_wavegen_square(amplitude, frequency_Hz, duty_cycle);
  }

Description
===========

This function calculates a square wave based on the global system time.

.. tikz:: square wave
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw (0,0) foreach \x in {1,2,3} {-- ++(0,1) -- ++(1,0) -- ++(0,-2) -- ++(1,0)-- ++(0,1)};
  \draw[|-|](-0.5,0)--(-0.5,1);
  \node[font=\footnotesize] at (-1.3,0.5){amplitude};
  \draw[|->](0,-1.5)--(2,-1.5);
  \node[font=\footnotesize] at (1,-2){frequency};
  \draw[|-|](0,1.5)--(1,1.5);
  \node[font=\footnotesize] at (0.5,2){Duty Cycle};

   


