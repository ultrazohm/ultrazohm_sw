===============
uz_wavegen_sine
===============

.. doxygenfunction:: uz_wavegen_sine

Example
=======

.. literalinclude:: ../../../../../vitis/software/Baremetal/test/uz/uz_wavegen/test_uz_wavegen.c
    :lines: 23-29
    :linenos:
    :language: c
    :caption: Example function call to sine wave generator

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
   


