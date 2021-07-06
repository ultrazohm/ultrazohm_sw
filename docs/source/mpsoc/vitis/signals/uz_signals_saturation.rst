===================
Saturation function
===================

.. doxygenfunction:: uz_signals_saturation

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call limit the input (saturation)

  #include "uz_signals.h"
  int main(void) {
     float input = 2.0f;
     float upper_limit = 0.5f;
     float lower_limit = 0.2f;
     float output = uz_signals_saturation(input, upper_limit, lower_limit);
  }

Description
===========

Limits an input signal to the specified upper and lower saturation values.

.. tikz:: saturation wave
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw (0,0) foreach \x in {1,2,3} {-- ++(1,1) -- ++(1,-1) };
  \draw[color=blue] (0,0.25) foreach \x in {1,2,3} {-- ++(0.25,0) -- ++(0.5,0.5) -- ++(0.5,0) -- ++(0.5,-0.5)-- ++(0.25,0) };
  \node[below,color=blue,font=\footnotesize] at (3.75,0){output};
  \draw[->] (2.75,-0.25) -- (3.2,-0.25);
  \node[below,color=black,font=\footnotesize] at (2.2,0){input};
  \draw[<-] (6.25,0.25) -- (6.75,0.25);
  \node[below,color=black,font=\footnotesize] at (8,0.6){lower limit};
  \draw[<-] (5.5,0.75) -- (6.75,0.75);
  \node[below,color=black,font=\footnotesize] at (8,1.1){upper limit};

   


