==========
Chirp wave
==========

.. doxygentypedef:: uz_wavegen_chirp

.. doxygenstruct:: uz_wavegen_chirp_config
  :members:

.. doxygenfunction:: uz_wavegen_chirp_init

.. doxygenfunction:: uz_wavegen_chirp_sample

.. doxygenfunction:: uz_wavegen_chirp_reset

Example
=======

The following define has to be set in ``uz_global_configuration.h`` to set the maximum of required instances, with ``x`` defining the maximum for how often ``uz_wavegen_chirp_init`` will be called.

.. code-block:: c

    #define UZ_WAVEGEN_CHIRP_MAX_INSTANCES x

Initialize the config file:

.. code-block:: c

   struct uz_wavegen_chirp_config config_chirp = {
           .amplitude = 2.0f,
           .start_frequency_Hz = 1.0f,
           .end_frequency_Hz = 10.0f,
           .duration_sec = 10.0f,
           .initial_delay_sec = 0.0f,
           .offset = 1.0f
   };

Call the init function:

.. code-block:: c

    int main(void) {
       uz_wavegen_chirp* chirp_instance=uz_wavegen_chirp_init(config_chirp);
       float chirp_sample=uz_wavegen_chirp_sample(chirp_instance);
    }

The function ``uz_wavegen_chirp_reset()`` resets the chirp such that it can be started again from the start frequency. 
A subsequent call of ``uz_wavegen_chirp()`` will start the chirp function from :math:`t=0` again.

Description
===========

Outputs one sample of a configurable chirp for each function call based on the global system time.
The parameters for configuration are the amplitude, the start and end frequency, the duration for the chirp and a delay for the start of the chirp wave.
After the duration of the chirp wave, the function ``uz_wavegen_chirp_sample()`` will return a normal sine wave with the ``end_frequency_Hz``. 
For the input arguments a struct is required.  

.. tikz:: chirp wave
  :align: left

  \draw [densely dotted] (0,-0.5)  -- +(6,0);
  \draw plot[domain=0:5,variable=\x,samples=200,smooth] (\x+1,{sin(deg(\x^2*pi))});
  \draw[-](0,-0.5) -- (1,-0.5);
  \draw[-](1,-0.5) -- (1,0);
  \draw[|-|](0,0.5)--(1,0.5);
  \node[font=\footnotesize] at (0.5,1){delay};
  \draw[->](1.75,1.7)--(1.75,1.2);
  \node[font=\footnotesize] at (1.75,2){start frequency};
  \draw[->](5.75,1.7)--(5.75,1.2);
  \node[font=\footnotesize] at (5.1,2){end frequency};
  \draw[|-|](1,-2)--(5.75,-2);
  \node[font=\footnotesize] at (3.3,-2.5){duration};
  \draw[|-|](-0.25,0)--(-0.25,1);
  \node[font=\footnotesize] at (-1.1,0.5){amplitude};
  \draw[|-|](-0.5,-0.5)--(-0.5,0);
  \node[font=\footnotesize] at (-1.1,-0.25){offset};