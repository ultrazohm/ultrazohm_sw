.. _wave_generator:

==================
Waveform Generator
==================

The ``uz_wavegen`` functions can be used to create standard waveform, which, for example, can be displayed in the :ref:`JavaScope`.


Available waveforms
*******************

Sine wave
^^^^^^^^^

.. tikz:: sine wave
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw plot[domain=0:6,variable=\x,samples=51,smooth] (\x,{0.5*sin(deg(\x*pi))});
   
Creates a continous sine wave. 

.. list-table:: Required input arguments
   :widths: 25 25 25
   :header-rows: 1

   * - argument
     - value
     - unit
   * - amplitude
     - +/- float
     - 
   * - frequency
     - \+ float 
     - Hz

Function call:

.. code-block:: c

    ... = uz_wavegen_sine(amplitude, frequency_Hz);
    
Sine wave with offset
^^^^^^^^^^^^^^^^^^^^^
 
.. tikz:: sine wave with offset
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw plot[domain=0:6,variable=\x,samples=51,smooth] (\x,{0.25+0.5*sin(deg(\x*pi))});

Creates a continous sine wave with an adjustable offset. 

.. list-table:: Required input arguments
   :widths: 25 25 25
   :header-rows: 1

   * - argument
     - value
     - unit
   * - amplitude
     - +/- float
     - 
   * - frequency
     - \+ float 
     - Hz
   * - offset
     - +/- float
     -

Function call:

.. code-block:: c

    ... = uz_wavegen_sine_with_offset(amplitude, frequency_Hz, offset);   

Sawtooth wave
^^^^^^^^^^^^^

.. tikz:: sawtooth wave
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw (0,0) foreach \x in {1,2,3} {-- ++(2,1) -- ++(0,-1) };

Creates a continous sawtooth wave.

.. list-table:: Required input arguments
   :widths: 25 25 25
   :header-rows: 1

   * - argument
     - value
     - unit
   * - amplitude
     - +/- float
     - 
   * - frequency
     - \+ float 
     - Hz

Function call:

.. code-block:: c

    ... = uz_wavegen_sawtooth(amplitude, frequency_Hz);
    
Sawtooth wave with offset
^^^^^^^^^^^^^^^^^^^^^^^^^

.. tikz:: sawtooth wave with offset
  :align: left

  \draw [densely dotted] (0,0.25)  -- +(6,0);
  \draw (0,0) foreach \x in {1,2,3} {-- ++(2,1) -- ++(0,-1) };

Creates a continous sawtooth wave with an adjustable offset.

.. list-table:: Required input arguments
   :widths: 25 25 25
   :header-rows: 1

   * - argument
     - value
     - unit
   * - amplitude
     - +/- float
     - 
   * - frequency
     - \+ float 
     - Hz
   * - offset
     - +/- float
     -

Function call:

.. code-block:: c

    ... = uz_wavegen_sawtooth_with_offset(amplitude, frequency_Hz, offset);
    
Pulse wave
^^^^^^^^^^^^^

.. tikz:: pulse wave
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw (0,0) foreach \x in {1,2,3} {-- ++(0,1) -- ++(1,0) -- ++(0,-1) -- ++(1,0)};

Creates a continous pulse wave.

.. list-table:: Required input arguments
   :widths: 25 25 25
   :header-rows: 1

   * - argument
     - value
     - unit
   * - amplitude
     - +/- float
     - 
   * - frequency
     - \+ float 
     - Hz
   * - DutyCycle
     - float 0.0 -> 1.0
     -
  
Function call:

.. code-block:: c

    ... = uz_wavegen_pulse(amplitude, frequency_Hz, duty_cycle);

Square wave
^^^^^^^^^^^^^
 
.. tikz:: square wave
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw (0,0) foreach \x in {1,2,3} {-- ++(0,1) -- ++(1,0) -- ++(0,-2) -- ++(1,0)-- ++(0,1)};

Creates a continous square wave.

.. list-table:: Required input arguments
   :widths: 25 25 25
   :header-rows: 1

   * - argument
     - value
     - unit
   * - amplitude
     - +/- float
     - 
   * - frequency
     - \+ float 
     - Hz

Function call:

.. code-block:: c

    ... = uz_wavegen_square(amplitude, frequency_Hz);

Triangle wave
^^^^^^^^^^^^^

.. tikz:: triangle wave
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw (0,0) foreach \x in {1,2,3} {-- ++(1,1) -- ++(1,-1) };

Creates a continous triangle wave.

.. list-table:: Required input arguments
   :widths: 25 25 25
   :header-rows: 1

   * - argument
     - value
     - unit
   * - amplitude
     - +/- float
     - 
   * - frequency
     - \+ float 
     - Hz

Function call:

.. code-block:: c

    ... = uz_wavegen_triangle(amplitude, frequency_Hz);
    
Triangle wave with offset
^^^^^^^^^^^^^^^^^^^^^^^^^

.. tikz:: triangle wave with offset
  :align: left

  \draw [densely dotted] (0,0.25)  -- +(6,0);
  \draw (0,0) foreach \x in {1,2,3} {-- ++(1,1) -- ++(1,-1) };

Creates a continous triangle wave with an adjustable offset.

.. list-table:: Required input arguments
   :widths: 25 25 25
   :header-rows: 1

   * - argument
     - value
     - unit
   * - amplitude
     - +/- float
     - 
   * - frequency
     - \+ float 
     - Hz
   * - offset
     - +/- offset
     - 

Function call:

.. code-block:: c

    ... = uz_wavegen_triangle(amplitude, frequency_Hz, offset);

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

Limits an input signal to the upper and lower saturation values, similar to how the saturation block in matlab functions. Doesn't generate a waveform by itself.

.. list-table:: Required input arguments
   :widths: 25 25 25
   :header-rows: 1

   * - argument
     - value
     - unit
   * - input signal
     - +/- float
     - 
   * - upper limit
     - +/- float 
     - 
   * - lower limit
     - +/- float 
     -

Function call:

.. code-block:: c

    ... = uz_wavegen_saturation(input, upper_limit, lower_limit);

White noise function
^^^^^^^^^^^^^^^^^^^^
  
.. tikz:: white noise wave
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw plot[domain=0:6,variable=\x,samples=200,smooth] (\x,{rand});

Creates a continous white noise function. With the argument **amplitude** one can input the max value of the white noise wave.

.. list-table:: Required input arguments
   :widths: 25 25 25
   :header-rows: 1

   * - argument
     - value
     - unit
   * - amplitude
     - +/- float 
     - 
 
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
After the duration of the chirp wave, the function ``uz_wavegen_chirp()`` will return a continous sinus with the ``end_frequency_Hz``. For the input arguments a struct is required.

.. list-table:: Required input arguments
   :widths: 25 25 25
   :header-rows: 1

   * - argument
     - value
     - unit
   * - amplitude
     - +/- float 
     - 
   * - start_frequency_Hz
     - \+ float 
     - Hz
   * - end_frequency_Hz
     - \+ float 
     - Hz
   * - duration
     - \+ float
     - seconds
   * - delay
     - 0 -> \+ float
     - seconds
  
Initialize the config file in the ``main.c``:

.. code-block:: c

    uz_wavegen* *name*;
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

    extern uz_wavegen* *name*; 
    float *output* = uz_wavegen_chirp(*name*);

The \*highlighted\* words are the variable names, which can be freely chosen. 

The function ``uz_wavegen_chirp_reset()`` can be used, to reset the chirp. A subsequent call of ``uz_wavegen_chirp()`` will start the chirp function from t=0 again.

Three phase sine function
^^^^^^^^^^^^^^^^^^^^^^^^^^

.. tikz:: three phase sine wave
  :align: left

  \draw [densely dotted] (0,0)  -- +(6,0);
  \draw plot[domain=0:6,variable=\x,samples=51,smooth] (\x,{sin(deg(\x*pi))});
  \draw[color=blue] plot[domain=0:6,variable=\x,samples=51,smooth] (\x,{sin(120+deg(\x*pi))});
  \draw[color=orange] plot[domain=0:6,variable=\x,samples=51,smooth] (\x,{sin(240+deg(\x*pi))});

Creates a continous sine wave with free phases. For the input arguments a struct is required.

.. list-table:: Required input arguments
   :widths: 25 25 25
   :header-rows: 1

   * - argument
     - value
     - unit
   * - amplitude
     - +/- float
     - 
   * - frequency
     - \+ float 
     - Hz
   * - offset
     - +/- float
     -

Initialize the function with:

.. code-block:: c

    struct uz_wavegen_three_phase_config *name* = {
    .amplitude = ...,
    .frequency_Hz= ...,
    .offset = ...};

    uz_wavegen_three_phase_sine* *output* = uz_wavegen_three_phase_init(*name*);

Function call:

.. code-block:: c

    uz_wavegen_three_phase(*output*);

The output for the three phases is stored in the \*output*\  struct. Access them with:

.. code-block:: c

    ... = *output*->phase_U;
    ... = *output*->phase_V;
    ... = *output*->phase_W;

The \*highlighted\* words are the variable names, which can be freely chosen. 