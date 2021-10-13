=================
Get Sign function
=================

.. doxygenfunction:: uz_signals_get_sign_of_value

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call get the sign of the input

  #include "uz_signals.h"
  int main(void) {
     float output = uz_signals_get_sign_of_value(20.5f);
  }

Description
===========

Evaluates the sign of the input value. Returns 0.0f, if the input is 0.0f. Returns 1.0f, if the input is positive and returns -1.0f if the input ist negative.

.. tikz:: Get_sign function 
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw[color=blue] (0,0) {(0,1) -- ++(2,0) -- ++(0,-1)-- ++(2,0)-- ++(0,-1)-- ++(2,0)};
  \node[color=blue, font=\footnotesize] at (-0.2,1){10};
  \node[color=blue, font=\footnotesize] at (-0.2,0){0};
  \node[color=blue, font=\footnotesize] at (-0.25,-1){-10};
  \draw[->](0,-1)--(0,1.5);
  \draw[color=orange] (0,0) {(0,0.5) -- ++(2,0) -- ++(0,-0.5)-- ++(2,0)-- ++(0,-0.5)-- ++(2,0)};
  \draw[->](6,-1)--(6,1.5);
  \node[color=orange, font=\footnotesize] at (6.2,0.5){1};
  \node[color=orange, font=\footnotesize] at (6.2,0){0};
  \node[color=orange, font=\footnotesize] at (6.2,-0.5){-1};
  \node[below,color=orange,font=\footnotesize] at (3.75,-1){output};
  \draw[->] (2.75,-1.25) -- (3.2,-1.25);
  \node[below,color=blue,font=\footnotesize] at (2.2,-1){input};

   


