======================
Hysteresis band filter
======================

.. doxygenfunction:: uz_signals_hysteresisband_filter

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to filter the input

  #include "uz_signals.h"
  int main(void) {
     float input = 2.0f;
     float upper_limit = 0.5f;
     float lower_limit = 0.2f;
     float output = uz_signals_hysteresisband_filter(input, upper_limit, lower_limit);
  }

Description
===========

Passes the input through if it is inside a hysteresis band limited by the upper and lower limit values.
Otherwise the output is 0.



.. tikz:: hysteresis band filter
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw [densely dotted, color=red] (0,1)  -- +(6,0);
  \draw [densely dotted, color=red] (0,0.5)  -- +(6,0);
  \node[color=red, font=\footnotesize] at (7.23,1){upper limit};
  \node[color=red, font=\footnotesize] at (7.23,0.5){lower limit};

  \draw[color=blue] (0,0) {(0,0) -- ++(6,1.5)};
  \node[color=blue, font=\footnotesize] at (-0.2,1){10};
  \node[color=red, font=\footnotesize] at (-0.2,0.5){5};
  \node[color=blue, font=\footnotesize] at (-0.2,0){0};

  \draw[->](0,-0.1)--(0,1.8);
  \draw[color=orange] (0,0) {(0,0.0) -- ++(2.0,0.0) -- ++(0.0,0.5) -- ++(2,0.5)-- ++(0,-1) -- ++(2.0,0.0)};
  \draw[->](6,-0.1)--(6,1.8);

  \node[below,color=orange,font=\footnotesize] at (3.77,-0.1){output};
  \draw[->] (2.75,-0.35) -- (3.2,-0.35);
  \node[below,color=blue,font=\footnotesize] at (2.2,-0.1){input};   


