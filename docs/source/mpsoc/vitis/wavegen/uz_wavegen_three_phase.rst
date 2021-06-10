=========================
Three phase sine function
=========================

.. doxygentypedef:: uz_wavegen_three_phase

.. doxygenstruct:: uz_wavegen_three_phase_config
  :members:

.. doxygenfunction:: uz_wavegen_three_phase_init

.. doxygenfunction:: uz_wavegen_three_phase_sample

.. doxygenfunction:: uz_wavegen_three_phase_get_phaseU

.. doxygenfunction:: uz_wavegen_three_phase_get_phaseV

.. doxygenfunction:: uz_wavegen_three_phase_get_phaseW

Example
=======

The following define has to be set to the maximum of required instances, i.e., ``x`` is the maximum for how often ``uz_wavegen_three_phase_init`` will be called.  

.. code-block:: c

    #define UZ_WAVEGEN_THREE_PHASE_MAX_INSTANCES x

Initialize the config file:

.. code-block:: c
     
   struct uz_wavegen_three_phase_config config_three = {
           .amplitude = 2.0f,
           .frequency_Hz = 1.0f,
           .offset = 1.0f
   };
     
Call the init function:
     
.. code-block:: c
     
    int main(void) {
    uz_wavegen_three_phase* three_phase_test = uz_wavegen_three_phase_init(config_three);
    uz_wavegen_three_phase_sample(three_phase_test);
    }

After the values for the three phases at the current system time have been calculated in ``uz_wavegen_three_phase_sample()``, the value of each phase can be accessed with the following getter functions.

.. code-block:: c

    float phase_U = uz_wavegen_three_phase_get_phaseU(three_phase_test);
    float phase_V = uz_wavegen_three_phase_get_phaseV(three_phase_test);
    float phase_W = uz_wavegen_three_phase_get_phaseW(three_phase_test);

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
   


