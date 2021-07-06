=================
DeadZone function
=================

.. doxygenfunction:: uz_signals_dead_zone

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call provides region of zero output

  #include "uz_signals.h"
  int main(void) {
     float input=1.1f;
     float upper_threshold=10.5f;
     float lower_threshold=-20.5f;
     float output = uz_signals_dead_zone(input, upper_limit, lower_limit));
  }

Description
===========

The Dead Zone generates zero output within a specified region.

.. list-table:: Deadzone
   :widths: 40 25
   :header-rows: 1

   * - input
     - output
   * - input >= lower_threshold && input <= upper_threshold
     - zero
   * - input > upper_threshold
     - input - upper_threshold
   * - input < lower_threshold
     - input - lower_threshold

.. tikz:: Get_sign function 
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw [densely dotted, color=red] (0,0.5)  -- +(6,0);
  \draw [densely dotted, color=red] (0,-0.5)  -- +(6,0);
  \draw[color=blue] (0,0) {(0,-1) -- ++(6,2)};
  \node[color=blue, font=\footnotesize] at (-0.2,1){10};
  \node[color=red, font=\footnotesize] at (-0.2,0.5){5};
  \node[color=blue, font=\footnotesize] at (-0.2,0){0};
  \node[color=red, font=\footnotesize] at (-0.25,-0.5){-5};
  \node[color=blue, font=\footnotesize] at (-0.25,-1){-10};
  \draw[->](0,-1)--(0,1.5);
  \draw[color=orange] (0,0) {(0,-0.5) -- ++(1.5,0.5) -- ++(3,0)-- ++(1.5,0.5)};
  \draw[->](6,-1)--(6,1.5);
  \node[color=red, font=\footnotesize] at (7.2,0.5){upper threshold};
  \node[color=red, font=\footnotesize] at (7.2,-0.5){lower threshold};
  \node[below,color=orange,font=\footnotesize] at (3.75,-1){output};
  \draw[->] (2.75,-1.25) -- (3.2,-1.25);
  \node[below,color=blue,font=\footnotesize] at (2.2,-1){input};

   


