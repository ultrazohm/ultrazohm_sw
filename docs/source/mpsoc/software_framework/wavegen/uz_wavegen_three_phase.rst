=========================
Three phase sine function
=========================


.. doxygenfunction:: uz_wavegen_three_phase_sample


Example
=======

The current value of the three phases at the current system time is calculated by calling ``uz_wavegen_three_phase_sample()``.
The module uses the ``uz_3ph_abc_t`` data type from :ref:`uz_Transformation` to return all three phase values as a struct.

.. code-block:: c

    float amplitude = 2.0f;
    float frequency = 5.0f;
    float offset = 1.0f;
    uz_3ph_abc_t three_phase_sine = uz_wavegen_three_phase_sample(amplitude, frequency, offset);


Description
===========

Outputs one sample of a sine wave with three phases for each function call. 

.. tikz:: three phase sine wave
  :align: left

  \draw [densely dotted] (0,-0.5)  -- +(6,0);
  \draw plot[domain=0:6,variable=\x,samples=51,smooth] (\x,{sin(deg(\x*pi))});
  \draw[color=blue] plot[domain=0:6,variable=\x,samples=51,smooth] (\x,{sin(120+deg(\x*pi))});
  \draw[color=orange] plot[domain=0:6,variable=\x,samples=51,smooth] (\x,{sin(240+deg(\x*pi))});
  \draw[|-|](-0.25,0)--(-0.25,1);
  \node[font=\footnotesize] at (-1.1,0.5){amplitude};
  \draw[|->](0,-1.5)--(2,-1.5);
  \node[font=\footnotesize] at (1,-2){frequency};
  \draw[|-|](-0.5,-0.5)--(-0.5,0);
  \node[font=\footnotesize] at (-1.1,-0.25){offset};
   


