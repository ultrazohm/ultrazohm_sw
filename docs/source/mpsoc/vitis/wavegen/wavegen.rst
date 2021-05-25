.. _wave_generator:

==================
Waveform Generator
==================

The ``uz_wavegen`` functions can be used to create standard waveform, which, for example, can be displayed in the :ref:`JavaScope`.
Wherever the functions are called, ``uz_wavegen.h`` has to be included. 

Available waveforms
*******************

Sine wave
^^^^^^^^^

.. tikz:: sine wave
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw plot[domain=0:6,variable=\x,samples=51,smooth] (\x,{0.5*sin(deg(\x*pi))});
   
Creates a continous sine wave. For further information check the :ref:`References <wave_generator_reference_sine>`.

Function call:

.. code-block:: c

    ... = uz_wavegen_sine(amplitude, frequency_Hz);
    
Sine wave with offset
^^^^^^^^^^^^^^^^^^^^^
 
.. tikz:: sine wave with offset
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw plot[domain=0:6,variable=\x,samples=51,smooth] (\x,{0.25+0.5*sin(deg(\x*pi))});

Creates a continous sine wave with an adjustable offset. For further information check :ref:`References <wave_generator_reference_sine_offset>`. 

Function call:

.. code-block:: c

    ... = uz_wavegen_sine_with_offset(amplitude, frequency_Hz, offset);   

Sawtooth wave
^^^^^^^^^^^^^

.. tikz:: sawtooth wave
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw (0,0) foreach \x in {1,2,3} {-- ++(2,1) -- ++(0,-1) };

Creates a continous sawtooth wave. For further information check :ref:`References <wave_generator_reference_sawtooth>`.

Function call:

.. code-block:: c

    ... = uz_wavegen_sawtooth(amplitude, frequency_Hz);
    
Sawtooth wave with offset
^^^^^^^^^^^^^^^^^^^^^^^^^

.. tikz:: sawtooth wave with offset
  :align: left

  \draw [densely dotted] (0,0.25)  -- +(6,0);
  \draw (0,0) foreach \x in {1,2,3} {-- ++(2,1) -- ++(0,-1) };

Creates a continous sawtooth wave with an adjustable offset. For further information check :ref:`References <wave_generator_reference_sawtooth_offset>`.

Function call:

.. code-block:: c

    ... = uz_wavegen_sawtooth_with_offset(amplitude, frequency_Hz, offset);
    
Pulse wave
^^^^^^^^^^

.. tikz:: pulse wave
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw (0,0) foreach \x in {1,2,3} {-- ++(0,1) -- ++(1,0) -- ++(0,-1) -- ++(1,0)};

Creates a continous pulse wave. For further information check :ref:`References <wave_generator_reference_pulse>`.
  
Function call:

.. code-block:: c

    ... = uz_wavegen_pulse(amplitude, frequency_Hz, duty_cycle);

Square wave
^^^^^^^^^^^
 
.. tikz:: square wave
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw (0,0) foreach \x in {1,2,3} {-- ++(0,1) -- ++(1,0) -- ++(0,-2) -- ++(1,0)-- ++(0,1)};

Creates a continous square wave. For further information check :ref:`References <wave_generator_reference_square>`.

Function call:

.. code-block:: c

    ... = uz_wavegen_square(amplitude, frequency_Hz);

Triangle wave
^^^^^^^^^^^^^

.. tikz:: triangle wave
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw (0,0) foreach \x in {1,2,3} {-- ++(1,1) -- ++(1,-1) };

Creates a continous triangle wave. For further information check :ref:`References <wave_generator_reference_triangle>`.

Function call:

.. code-block:: c

    ... = uz_wavegen_triangle(amplitude, frequency_Hz);
    
Triangle wave with offset
^^^^^^^^^^^^^^^^^^^^^^^^^

.. tikz:: triangle wave with offset
  :align: left

  \draw [densely dotted] (0,0.25)  -- +(6,0);
  \draw (0,0) foreach \x in {1,2,3} {-- ++(1,1) -- ++(1,-1) };

Creates a continous triangle wave with an adjustable offset. For further information check :ref:`References <wave_generator_reference_triangle_offset>`.


Function call:

.. code-block:: c

    ... = uz_wavegen_triangle_with_offset(amplitude, frequency_Hz, offset);

Saturation function
^^^^^^^^^^^^^^^^^^^

.. tikz:: saturation wave
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw (0,0) foreach \x in {1,2,3} {-- ++(1,1) -- ++(1,-1) };
  \draw[color=blue] (0,0.25) foreach \x in {1,2,3} {-- ++(0.25,0) -- ++(0.5,0.5) -- ++(0.5,0) -- ++(0.5,-0.5)-- ++(0.25,0) };
  \node[below,color=blue,font=\footnotesize] at (3.8,0){output};
  \draw[->] (2.75,-0.3) -- (3.2,-0.3);
  \node[below,color=black,font=\footnotesize] at (2.2,0){input};

Limits an input signal to the upper and lower saturation values, similar to how the saturation block in matlab functions. Doesn't generate a waveform by itself. For further information check :ref:`References <wave_generator_reference_saturation>`.

Function call:

.. code-block:: c

    ... = uz_wavegen_saturation(input, upper_limit, lower_limit);

White noise function
^^^^^^^^^^^^^^^^^^^^
  
.. tikz:: white noise wave
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw plot[domain=0:6,variable=\x,samples=200,smooth] (\x,{rand});

Creates a continous white noise function. With the argument **amplitude** one can input the max value of the white noise wave. For further information check :ref:`References <wave_generator_reference_white_noise>`.
 
Function call:

.. code-block:: c

    ... = uz_wavegen_white_noise(amplitude);

Chirp function
^^^^^^^^^^^^^^

.. tikz:: chirp wave
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw plot[domain=0:5,variable=\x,samples=200,smooth] (\x+1,{sin(deg(\x^2*pi))});
  \draw(0,0)--(1,0);
  \draw[|-|](0,0.5)--(1,0.5);
  \node[font=\footnotesize] at (0.5,1){delay};
  \draw[->](1.75,1.7)--(1.75,1.2);
  \node[font=\footnotesize] at (1.75,2){start frequency};
  \draw[->](5.75,1.7)--(5.75,1.2);
  \node[font=\footnotesize] at (5.1,2){end frequency};
  \draw[|-|](1,-2)--(5.75,-2);
  \node[font=\footnotesize] at (3.3,-2.5){duration};

Creates a configurable chirp function. The parameters for configuration are the amplitude, the start and end frequency, the duration for the chirp and a delay for the start of the chirp wave.
After the duration of the chirp wave, the function ``uz_wavegen_chirp_sample()`` will return a continous sine wave with the ``end_frequency_Hz``. For the input arguments a struct is required. For further information check :ref:`References <wave_generator_reference_chirp>`.
  
In the same file, where ``uz_wavegen.h`` is included, one has to define the following statement, where **x** ist the maximum for how often ``uz_wavegen_chirp_init`` will be called.  

.. code-block:: c

    #define max_wavegen_chirp_instances x

Initialize the config file in the ``main.c``:

.. code-block:: c

    uz_wavegen_chirp* *name*;
    struct uz_wavegen_chirp_config *config* = {
    .amplitude= ...,
    .start_frequency_Hz = ...,
    .end_frequency_Hz = ...,
    .duration_Sec = ...,
    .initial_delay_Sec = ...};

Call the init function inside the main function, but before the ``while(1)``-loop.

.. code-block:: c

    int main(void) {
    ...
    *name* = uz_wavegen_chirp_init(*config*);
    ...
    while (1) {...}
    }

Function call. The first line is needed, if the function is called outside of ``main.c``:

.. code-block:: c

    extern uz_wavegen_chirp* *name*; 
    float *output* = uz_wavegen_chirp_sample(*name*);

The \*highlighted\* words are the variable names, which can be freely chosen. 

The function ``uz_wavegen_chirp_reset()`` can be used, to reset the chirp. A subsequent call of ``uz_wavegen_chirp()`` will start the chirp function from t=0 again.

Three phase sine function
^^^^^^^^^^^^^^^^^^^^^^^^^

.. tikz:: three phase sine wave
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw plot[domain=0:6,variable=\x,samples=51,smooth] (\x,{sin(deg(\x*pi))});
  \draw[color=blue] plot[domain=0:6,variable=\x,samples=51,smooth] (\x,{sin(120+deg(\x*pi))});
  \draw[color=orange] plot[domain=0:6,variable=\x,samples=51,smooth] (\x,{sin(240+deg(\x*pi))});

Creates a continous sine wave with free phases. For the input arguments a struct is required. For further information check :ref:`References <wave_generator_reference_three_phase>`.

Initialize the config file in the ``main.c``:

.. code-block:: c
     
    uz_wavegen_three_phase* *name*;
    struct uz_wavegen_three_phase_config *config* = {
    .amplitude= ...,
    .frequency_Hz = ...,
    .offset = ...};
     
Call the init function inside the main function, but before the ``while(1)``-loop.
     
.. code-block:: c
     
    int main(void) {
    ...
    *name* = uz_wavegen_three_phase_init(*config*);
    ...
    while (1) {...}
    }
     
Function call. The first line is needed, if the function is called outside of ``main.c``:
     
.. code-block:: c
     
    extern uz_wavegen_three_phase* *name*; 
    uz_wavegen_three_phase_sample(*name*);

After the values for the three phases at the current system time have been calculated in ``uz_wavegen_three_phase_sample()``, 
the value of each phase can be accessed with the following functions.

.. code-block:: c

    float *phaseU* = uz_wavegen_three_phase_get_phaseU(*name*);
    float *phaseV* = uz_wavegen_three_phase_get_phaseV(*name*);
    float *phaseW* = uz_wavegen_three_phase_get_phaseW(*name*);

The \*highlighted\* words are the variable names, which can be freely chosen. 


Reference
*********

.. _wave_generator_reference_sine:

Sine wave
^^^^^^^^^

.. doxygenfunction:: uz_wavegen_sine


.. _wave_generator_reference_sine_offset:

Sine wave with offset
^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: uz_wavegen_sine_with_offset


.. _wave_generator_reference_sawtooth:

Sawtooth wave
^^^^^^^^^^^^^

.. doxygenfunction:: uz_wavegen_sawtooth


.. _wave_generator_reference_sawtooth_offset:  

Sawtooth wave with offset
^^^^^^^^^^^^^^^^^^^^^^^^^
  
.. doxygenfunction:: uz_wavegen_sawtooth_with_offset


.. _wave_generator_reference_pulse: 

Pulse wave
^^^^^^^^^^
  
.. doxygenfunction:: uz_wavegen_pulse


.. _wave_generator_reference_square: 

Square wave
^^^^^^^^^^^
  
.. doxygenfunction:: uz_wavegen_square


.. _wave_generator_reference_triangle: 

Triangle wave
^^^^^^^^^^^^^
  
.. doxygenfunction:: uz_wavegen_triangle


.. _wave_generator_reference_triangle_offset: 

Triangle wave with offset
^^^^^^^^^^^^^^^^^^^^^^^^^
  
.. doxygenfunction:: uz_wavegen_triangle_with_offset


.. _wave_generator_reference_saturation: 

Saturation function
^^^^^^^^^^^^^^^^^^^
  
.. doxygenfunction:: uz_wavegen_saturation


.. _wave_generator_reference_white_noise: 

White noise function
^^^^^^^^^^^^^^^^^^^^
  
.. doxygenfunction:: uz_wavegen_white_noise


.. _wave_generator_reference_chirp: 

Chirp function
^^^^^^^^^^^^^^

.. doxygentypedef:: uz_wavegen_chirp

.. doxygenstruct:: uz_wavegen_chirp_config
  :members:

.. doxygenfunction:: uz_wavegen_chirp_init

.. doxygenfunction:: uz_wavegen_chirp_sample

.. doxygenfunction:: uz_wavegen_chirp_reset


.. _wave_generator_reference_three_phase:

Three phase sine function
^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygentypedef:: uz_wavegen_three_phase

.. doxygenstruct:: uz_wavegen_three_phase_config
  :members:

.. doxygenfunction:: uz_wavegen_three_phase_init

.. doxygenfunction:: uz_wavegen_three_phase_sample

.. doxygenfunction:: uz_wavegen_three_phase_get_phaseU

.. doxygenfunction:: uz_wavegen_three_phase_get_phaseV

.. doxygenfunction:: uz_wavegen_three_phase_get_phaseW