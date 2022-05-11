.. _uz_wavegen_pulse:

==========
Pulse wave
==========

.. doxygenfunction:: uz_wavegen_pulse

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to pulse wave generator

  #include "uz_wavegen.h"
  int main(void) {
     float amplitude = 8.0f;
     float frequency_Hz = 10.0f;
     float duty_cycle = 0.5f;
     float output = uz_wavegen_pulse(amplitude, frequency_Hz, duty_cycle);
  }

Description
===========

This function calculates a pulse wave with specified offset based on the global system time.

.. tikz:: pulse wave
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw (0,0) foreach \x in {1,2,3} {-- ++(0,1) -- ++(1,0) -- ++(0,-1) -- ++(1,0)};
  \draw[|-|](-0.5,0)--(-0.5,1);
  \node[font=\footnotesize] at (-1.3,0.5){amplitude};
  \draw[|-|](0,1.5)--(1,1.5);
  \node[font=\footnotesize] at (0.5,2){Duty Cycle};
  \draw[|->](0,-0.5)--(2,-0.5);
  \node[font=\footnotesize] at (1,-1){frequency};

   


