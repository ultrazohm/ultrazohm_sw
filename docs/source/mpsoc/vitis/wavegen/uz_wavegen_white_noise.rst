===========
White noise
===========

.. doxygenfunction:: uz_wavegen_white_noise

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to generate white noise 

  #include "uz_wavegen.h"
  int main(void) {
     float output = = uz_wavegen_white_noise(1.0f);
  }

Description
===========

Outputs one sample of a white noise function for each function call.
The argument ``amplitude`` limits the maximum value of the white noise function.

.. tikz:: white noise wave
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw plot[domain=0:6,variable=\x,samples=200,smooth] (\x,{rand});
  \draw[|-|](-0.25,0)--(-0.25,1);
  \node[font=\footnotesize] at (-1.1,0.5){amplitude};


   


